/**
 * @file tFunctionTwoValue
 * file name: tFunctionTwoValue.cpp
 * @author Betti Oesterholz
 * @date 02.05.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the children class of cFunctionTwoValue.
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
 * This file contains the test for the children class of cFunctionTwoValue, which
 * represents a value Fib -underfunction.
 *
 *
 * What's tested of class cFunctionTwoValue:
 * 	- cFunctionTwoValue( cUnderFunction & firstUnderfunction, cUnderFunction & secondUnderfunction, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cFunctionTwoValue( const cFunctionTwoValue & underfunction, cUnderFunction * pInSuperiorFunction = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- cFunctionTwoValue( const TiXmlElement * pXmlElement, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	-cFunctionTwoValue( cReadBits & iBitStream, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, const cDomainSingle * pInDomainValue, const cDomainSingle * pInDomainVariable, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- ~cFunctionTwoValue();
 * 	- cUnderFunction * getFirstUnderFunction();
 * 	- void setFirstUnderFunction( const cUnderFunction & underFunction, bool bDeleteOld=true );
 * 	- cUnderFunction * getSecondUnderFunction();
 * 	- void setSecondUnderFunction( const cUnderFunction & underFunction, bool bDeleteOld=true );
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
 * tested two values underfunctions:
 * 	- cFunctionAdd
 * 	- cFunctionSub
 * 	- cFunctionMult
 * 	- cFunctionDiv
 * 	- cFunctionExp
 * 	- cFunctionMin
 * 	- cFunctionMax
 *
 * from other mudules tested two values underfunctions:
 * 	- cFunctionIf
 * 	- cFunctionDelay
 *
 */
/*
History:
02.05.2010  Oesterholz  created
02.05.2010  Oesterholz  comparisson of getValue() values with savety bounderies
04.04.2011  Oesterholz  storing to binary stream
*/

#include "version.h"

#include "cFunctionAdd.h"
#include "cFunctionSub.h"
#include "cFunctionMult.h"
#include "cFunctionDiv.h"
#include "cFunctionExp.h"
#include "cFunctionMin.h"
#include "cFunctionMax.h"


#include "cFunctionTwoValue.h"
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
#include <cmath>

#include "tCompareBits.inc"

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif



using namespace fib;
using namespace std;


template <class tUnderFunctionTwoValue> int testCostructor(
	unsigned long &ulTestphase, const tUnderFunctionTwoValue &function );
template <class tUnderFunctionTwoValue> int testUnderfunctions(
	unsigned long &ulTestphase, const tUnderFunctionTwoValue &function );
template <class tUnderFunctionTwoValue> int testEqual(
	unsigned long &ulTestphase, const tUnderFunctionTwoValue &function );
template <class tUnderFunctionTwoValue> int testCopy(
	unsigned long &ulTestphase, const tUnderFunctionTwoValue &function );
template <class tUnderFunctionTwoValue> int testStoreXml(
	unsigned long &ulTestphase, const tUnderFunctionTwoValue &function );
template <class tUnderFunctionTwoValue> int testStore(
	unsigned long &ulTestphase, const tUnderFunctionTwoValue &function );
template <class tUnderFunctionTwoValue> int testVariable(
	unsigned long &ulTestphase, const tUnderFunctionTwoValue &function );
template <class tUnderFunctionTwoValue> int testDefiningFibElement(
	unsigned long &ulTestphase, const tUnderFunctionTwoValue &function );
template <class tUnderFunctionTwoValue> int testValue(
	unsigned long &ulTestphase, const tUnderFunctionTwoValue &function );



/** the type of the actual underfunction which is tested */
unsigned int uiActualUnderfunctionType = 0;


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	cout<<endl<<"Running Test for methods of the childclasses of cFunctionTwoValue"<<endl;
	cout<<      "================================================================="<<endl;
	cout<<      "================================================================="<<endl;
	
	for ( unsigned int iType = 1; iType <= 7; iType++ ){
		
		cFunctionValue firstUnderfunction( 1.0 );
		cFunctionValue secondUnderfunction( 1.0 );
		
		switch ( iType ){
			case 1:{
				cout<<endl<<"Running Test for methods of the class of cFunctionAdd"<<endl;
				cout<<      "====================================================="<<endl;
				uiActualUnderfunctionType = 1;
				cFunctionAdd function( firstUnderfunction, secondUnderfunction );
				
				iReturn += testCostructor( ulTestphase, function );
				iReturn += testEqual( ulTestphase, function );
				iReturn += testUnderfunctions( ulTestphase, function );
				iReturn += testCopy( ulTestphase, function  );
				iReturn += testStoreXml( ulTestphase, function  );
				iReturn += testStore( ulTestphase, function  );
				iReturn += testVariable( ulTestphase, function  );
				iReturn += testDefiningFibElement( ulTestphase, function  );
				iReturn += testValue( ulTestphase, function  );

			}break;
			case 2:{
				cout<<endl<<"Running Test for methods of the class of cFunctionSub"<<endl;
				cout<<      "====================================================="<<endl;
				uiActualUnderfunctionType = 2;
				cFunctionSub function( firstUnderfunction, secondUnderfunction );
				
				iReturn += testCostructor( ulTestphase, function );
				iReturn += testEqual( ulTestphase, function  );
				iReturn += testUnderfunctions( ulTestphase, function );
				iReturn += testCopy( ulTestphase, function  );
				iReturn += testStoreXml( ulTestphase, function  );
				iReturn += testStore( ulTestphase, function  );
				iReturn += testVariable( ulTestphase, function  );
				iReturn += testDefiningFibElement( ulTestphase, function  );
				iReturn += testValue( ulTestphase, function  );

			}break;
			case 3:{
				cout<<endl<<"Running Test for methods of the class of cFunctionMult"<<endl;
				cout<<      "======================================================"<<endl;
				uiActualUnderfunctionType = 3;
				cFunctionMult function( firstUnderfunction, secondUnderfunction );
				
				iReturn += testCostructor( ulTestphase, function );
				iReturn += testEqual( ulTestphase, function  );
				iReturn += testUnderfunctions( ulTestphase, function );
				iReturn += testCopy( ulTestphase, function  );
				iReturn += testStoreXml( ulTestphase, function  );
				iReturn += testStore( ulTestphase, function  );
				iReturn += testVariable( ulTestphase, function  );
				iReturn += testDefiningFibElement( ulTestphase, function  );
				iReturn += testValue( ulTestphase, function  );

			}break;
			case 4:{
				cout<<endl<<"Running Test for methods of the class of cFunctionDiv"<<endl;
				cout<<      "====================================================="<<endl;
				uiActualUnderfunctionType = 4;
				cFunctionDiv function( firstUnderfunction, secondUnderfunction );
				
				iReturn += testCostructor( ulTestphase, function );
				iReturn += testEqual( ulTestphase, function  );
				iReturn += testUnderfunctions( ulTestphase, function );
				iReturn += testCopy( ulTestphase, function  );
				iReturn += testStoreXml( ulTestphase, function  );
				iReturn += testStore( ulTestphase, function  );
				iReturn += testVariable( ulTestphase, function  );
				iReturn += testDefiningFibElement( ulTestphase, function  );
				iReturn += testValue( ulTestphase, function  );

			}break;
			case 5:{
				cout<<endl<<"Running Test for methods of the class of cFunctionExp"<<endl;
				cout<<      "====================================================="<<endl;
				uiActualUnderfunctionType = 5;
				cFunctionExp function( firstUnderfunction, secondUnderfunction );
				
				iReturn += testCostructor( ulTestphase, function );
				iReturn += testEqual( ulTestphase, function  );
				iReturn += testUnderfunctions( ulTestphase, function );
				iReturn += testCopy( ulTestphase, function  );
				iReturn += testStoreXml( ulTestphase, function  );
				iReturn += testStore( ulTestphase, function  );
				iReturn += testVariable( ulTestphase, function  );
				iReturn += testDefiningFibElement( ulTestphase, function  );
				iReturn += testValue( ulTestphase, function  );

			}break;
			case 6:{
				cout<<endl<<"Running Test for methods of the class of cFunctionMin"<<endl;
				cout<<      "====================================================="<<endl;
				uiActualUnderfunctionType = 6;
				cFunctionMin function( firstUnderfunction, secondUnderfunction );
				
				iReturn += testCostructor( ulTestphase, function );
				iReturn += testEqual( ulTestphase, function  );
				iReturn += testUnderfunctions( ulTestphase, function );
				iReturn += testCopy( ulTestphase, function  );
				iReturn += testStoreXml( ulTestphase, function  );
				iReturn += testStore( ulTestphase, function  );
				iReturn += testVariable( ulTestphase, function  );
				iReturn += testDefiningFibElement( ulTestphase, function  );
				iReturn += testValue( ulTestphase, function  );

			}break;
			case 7:{
				cout<<endl<<"Running Test for methods of the class of cFunctionMax"<<endl;
				cout<<      "====================================================="<<endl;
				uiActualUnderfunctionType = 7;
				cFunctionMax function( firstUnderfunction, secondUnderfunction );
				
				iReturn += testCostructor( ulTestphase, function );
				iReturn += testEqual( ulTestphase, function  );
				iReturn += testUnderfunctions( ulTestphase, function );
				iReturn += testCopy( ulTestphase, function  );
				iReturn += testStoreXml( ulTestphase, function  );
				iReturn += testStore( ulTestphase, function  );
				iReturn += testVariable( ulTestphase, function  );
				iReturn += testDefiningFibElement( ulTestphase, function  );
				iReturn += testValue( ulTestphase, function  );

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
	const doubleFib dSaveBoundery = min( dSaveBoundery1, dSaveBoundery2 );
	
	if ( (dValue1 - dSaveBoundery <= dValue2) &&
			(dValue1 <= dValue2 + dSaveBoundery) ){
		return true;
	}
	return false;
}


/**
 * @return the actual underfunction type number
 * 	@see cUnderFunction::getType()
 * 	@see uiActualUnderfunctionType
 */
unsignedIntFib getActualFunctionType(){

	switch ( uiActualUnderfunctionType ){
	
		case 1: return cUnderFunction::FUNCTION_ADD;//cFunctionAdd
		case 2: return cUnderFunction::FUNCTION_SUB;//cFunctionSub
		case 3: return cUnderFunction::FUNCTION_MULT;//cFunctionMult
		case 4: return cUnderFunction::FUNCTION_DIV;//cFunctionDiv
		case 5: return cUnderFunction::FUNCTION_EXP;//cFunctionExp
		case 6: return cUnderFunction::FUNCTION_MIN;//cFunctionMin
		case 7: return cUnderFunction::FUNCTION_MAX;//cFunctionMax
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
	
		case 1: return "add";//cFunctionAdd
		case 2: return "sub";//cFunctionSub
		case 3: return "mult";//cFunctionMult
		case 4: return "div";//cFunctionDiv
		case 5: return "exp";//cFunctionExp
		case 6: return "min";//cFunctionMin
		case 7: return "max";//cFunctionMax
	}
	return "";
}


/**
 * This function evalues the value for the actual underfunction type if
 * the both values are given.
 *
 * @param dValue1 the first value (value of the first underfunction) for
 * 	the function to evalue
 * @param dValue2 the second value (value of the second underfunction) for
 * 	the function to evalue
 * @return the value for the actual underfunction
 */
doubleFib getActualFunctionValue( doubleFib dValue1, doubleFib dValue2 ){

	switch ( uiActualUnderfunctionType ){
	
		case 1: return (dValue1 + dValue2);//cFunctionAdd
		case 2: return (dValue1 - dValue2);//cFunctionSub
		case 3: return (dValue1 * dValue2);//cFunctionMult
		case 4:{;//cFunctionDiv
			if ( dValue2 == 0.0 ){
				return 0.0;
			}//else
			return (dValue1 / dValue2);
		}break;
		case 5:{
			if ( (dValue1 == 0.0) && (dValue2 < 0.0) ){
				//1/0 not defined -> 0
				return 0.0;
			}
			return pow( dValue1, dValue2 );//cFunctionExp
		}break;
		case 6: return std::min( dValue1, dValue2 );//cFunctionMin
		case 7: return std::max( dValue1, dValue2 );//cFunctionMax
	}
	return 0.0;
}


/**
 * This function returns the compressed underfunction initiation for the
 * actual underfunction type.
 * The initiation is returned without the leading 0x03, for initiation
 * of 2'ary underfunctions.
 *
 * @return the compressed underfunction initiation for the actual
 * 	underfunction type
 */
unsigned char getActualFunctionCInitiation(){

	switch ( uiActualUnderfunctionType ){
	
		case 1: return 0x00;//cFunctionAdd
		case 2: return 0x01;//cFunctionSub
		case 3: return 0x02;//cFunctionMult
		case 4: return 0x03;//cFunctionDiv
		case 5: return 0x04;//cFunctionExp
		case 6: return 0x05;//cFunctionMin
		case 7: return 0x06;//cFunctionMax
	}
	return 0x00;
}


/**
 * This function returns bits for the compressed underfunction initiation
 * for the actual underfunction type.
 * This also includes the 2 bits for the initiation for the leading 0x03,
 * for initiation of 2'ary underfunctions.
 *
 * @return the bits for the compressed underfunction initiation
 */
unsigned int getActualFunctionCInitiationBits(){

	return 5;
}


/**
 * This function adds the compressed underfunction initiation for the
 * actual underfunction type.
 * This also includes the initiation for the leading 0x03, for initiation
 * of 2'ary underfunctions.
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
	unsigned int uiBitsToShift = 2 + 3 + uiNullShift;
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
	//add the two value underfunction initiator
	pcBuffer[ (uiNullShift / 8) ] = pcBuffer[ (uiNullShift / 8) ] | (0x03 << (uiNullShift % 8) );
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
 * This method tests the constructor of the cFunctionTwoValue class.
 *
 * methods tested:
 * 	- cFunctionTwoValue( cUnderFunction & firstUnderfunction, cUnderFunction & secondUnderfunction, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- ~cFunctionTwoValue();
 * 	- cUnderFunction * getFirstUnderFunction();
 * 	- cUnderFunction * getSecondUnderFunction();
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
 * @param tUnderFunctionTwoValue the type of the tested cFunctionTwoValue
 * 	is of the type of this object
 * @return the number of erros occured in the test
 */
template <class tUnderFunctionTwoValue> int testCostructor(
	unsigned long &ulTestphase, const tUnderFunctionTwoValue &function ){

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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cFunctionTwoValue underfunction"<<endl;

	cout<<"cFunctionValue underFunctionValue1( 1.0 );"<<endl;
	cFunctionValue underFunctionValue1( 1.0 );
	cout<<"cFunctionValue underFunctionValue2( 2.0 );"<<endl;
	cFunctionValue underFunctionValue2( 2.0 );
	
	cout<<"tUnderFunctionTwoValue underFunctionTwoValue1( underFunctionValue1, underFunctionValue2 );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue1( underFunctionValue1, underFunctionValue2 );
	
	cUnderFunction * pFirstUnderfunction = &underFunctionValue1;
	cUnderFunction * pSecondUnderfunction = &underFunctionValue2;
	double dValue = getActualFunctionValue( pFirstUnderfunction->getValue(),
		pSecondUnderfunction->getValue() );
	cFibElement * pDefiningFibElement = NULL;
	cUnderFunction * pSuperiorUnderFunction = NULL;
	cTypeUnderFunction typeUnderFunction;
	cDomain * pUnderFunctionDomain = NULL;
	cDomain * pValueDomain = NULL;
	cDomain * pStandardDomain = typeUnderFunction.getStandardDomain();
	cTypeVariable typeVariable;
	cDomain * pVariableDomain = typeVariable.getStandardDomain();
	unsigned long ulTimeNeed = 1 + pFirstUnderfunction->getTimeNeed() +
		 pSecondUnderfunction->getTimeNeed();
	unsigned long ulCompressedSize = 5 + pFirstUnderfunction->getCompressedSize() +
		 pSecondUnderfunction->getCompressedSize();	
 
	//check the getValue() methode from cFunctionTwoValue
	if ( isEqual( underFunctionTwoValue1.getValue(), dValue )  ){
	
		cout<<"The underfunction value is correctly "<<
			underFunctionTwoValue1.getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction value is "<<
			underFunctionTwoValue1.getValue() <<" but should be "<< dValue <<" ."<<endl;
		iReturn++;
	}
	//check the underfunctions
	//check getFirstUnderFunction()
	if ( underFunctionTwoValue1.getFirstUnderFunction() != NULL  ){
	
		if ( underFunctionTwoValue1.getFirstUnderFunction() != pFirstUnderfunction  ){
		
			cout<<"The first underfunction dosn't points to the object set as the first underfunction . "<<endl;
		}else{
			cerr<<"Error: The first underfunction points to the object set as the first underfunction."<<endl;
			iReturn++;
		}
		if ( *(underFunctionTwoValue1.getFirstUnderFunction()) == *pFirstUnderfunction  ){
		
			cout<<"The first underfunction is equal to the underfunction set as the first underfunction . "<<endl;
		}else{
			cerr<<"Error: The first underfunction isn't equal to the underfunction set as the first underfunction."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The first underfunction is NULL ."<<endl;
		iReturn++;
	}
	//check getSecondUnderFunction()
	if ( underFunctionTwoValue1.getSecondUnderFunction() != NULL  ){
	
		if ( underFunctionTwoValue1.getSecondUnderFunction() != pSecondUnderfunction  ){
		
			cout<<"The second underfunction dosn't points to the object set as the second underfunction . "<<endl;
		}else{
			cerr<<"Error: The second underfunction points to the object set as the second underfunction."<<endl;
			iReturn++;
		}
		if ( *(underFunctionTwoValue1.getSecondUnderFunction()) == *pSecondUnderfunction  ){
		
			cout<<"The second underfunction is equal to the underfunction set as the second underfunction . "<<endl;
		}else{
			cerr<<"Error: The second underfunction isn't equal to the underfunction set as the second underfunction."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The second underfunction is NULL ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionTwoValue
	if ( underFunctionTwoValue1.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			underFunctionTwoValue1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			underFunctionTwoValue1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
	if ( underFunctionTwoValue1.getSuperiorUnderFunction() == pSuperiorUnderFunction  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			underFunctionTwoValue1.getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			underFunctionTwoValue1.getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	
	//check the isValid() methode from cFunctionTwoValue
	if ( ! underFunctionTwoValue1.isValid() ){
	
		cout<<"The underfunction is correctly not valid . "<<endl;
	}else{
		cerr<<"Error: The underfunction is valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cFunctionTwoValue
	if ( underFunctionTwoValue1.getType() == getActualFunctionType() ){
	
		cout<<"The underfunction type is correctly FUNCTION_VARIABLE. "<<endl;
	}else{
		cerr<<"Error: The type of the underfunction is not FUNCTION_VARIABLE ( "<<
			cUnderFunction::FUNCTION_VARIABLE <<" ), but "<<
			underFunctionTwoValue1.getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getUnderFunctionName() methode from cFunctionTwoValue
	if ( underFunctionTwoValue1.getUnderFunctionName() == getActualFunctionName() ){
	
		cout<<"The underfunction name is correctly "<<
			underFunctionTwoValue1.getUnderFunctionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the underfunction is not \"variable\", but "<<
			underFunctionTwoValue1.getUnderFunctionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfUnderFunctions() methode from cFunctionTwoValue
	if ( underFunctionTwoValue1.getNumberOfUnderFunctions() == 2 ){
	
		cout<<"The underfunction number of underfunctions is correctly "<<
			underFunctionTwoValue1.getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction number of underfunctions is "<<
			underFunctionTwoValue1.getNumberOfUnderFunctions() <<" , but should be 2 ."<<endl;
		iReturn++;
	}
	//check the getElementType() methode from cFunctionTwoValue
	cTypeElement * pTypeOfUnderFunction = underFunctionTwoValue1.getElementType();
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
	//check the getDomain() methode from cFunctionTwoValue
	cDomain * pRetUnderFunctionDomain = underFunctionTwoValue1.getDomain();
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
	//check the getValueDomain() methode from cFunctionTwoValue
	cDomain * pRetValueDomain = underFunctionTwoValue1.getValueDomain();
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
	//check the getStandardDomain() methode from cFunctionTwoValue
	cDomain * pRetStandardDomain = underFunctionTwoValue1.getStandardDomain();
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
	//check the getVariableDomain() methode from cFunctionTwoValue
	cDomain * pRetVariableDomain = underFunctionTwoValue1.getVariableDomain();
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
	//check the getTimeNeed() methode from cFunctionTwoValue
	if ( underFunctionTwoValue1.getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the function is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the function is "<<
			underFunctionTwoValue1.getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionTwoValue
	if ( underFunctionTwoValue1.getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the function is "<<
			underFunctionTwoValue1.getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	if ( ! underFunctionTwoValue1.isUsedVariable( pVariableX ) ){
	
		cout<<"The variable pVariableX isn't used in the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableX is used in the underfunction. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cFunctionTwoValue
	set<cFibVariable*> setUsedVariables = underFunctionTwoValue1.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"Ther are correctly no used variables are given back from the underfunction. "<<endl;
	}else{
		cerr<<"Error: Ther are used variables are given back from the underfunction. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an full cFunctionTwoValue underfunction, testing the included underFunctionTwoValue1"<<endl;

	cout<<"cFunctionVariable underFunctionVariable1( pVariable1 );"<<endl;
	cFunctionVariable underFunctionVariable1( pVariable1 );
	
	cout<<"tUnderFunctionTwoValue underFunctionTwoValue2( "<<
		"underFunctionVariable1, underFunctionTwoValue1, NULL, &rootEmpty );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue2( underFunctionVariable1,
		underFunctionTwoValue1, NULL, &rootEmpty );
	
	cFunctionTwoValue * pFunctionToTest = (cFunctionTwoValue*)
		underFunctionTwoValue2.getSecondUnderFunction();
	
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
	
	pFirstUnderfunction = &underFunctionValue1;
	pSecondUnderfunction = &underFunctionValue2;
	dValue = getActualFunctionValue( pFirstUnderfunction->getValue(),
		pSecondUnderfunction->getValue() );
	pDefiningFibElement = &rootEmpty;
	pSuperiorUnderFunction = &underFunctionTwoValue2;
	pUnderFunctionDomain = &domainNaturalNumberBit5;
	pValueDomain = &domainNaturalNumberBit7;
	delete pVariableDomain;
	pVariableDomain = domainNaturalNumberBit3.clone();
	ulTimeNeed = 1 + pFirstUnderfunction->getTimeNeed() +
		 pSecondUnderfunction->getTimeNeed();
	ulCompressedSize = 5 + 9 + 9;
 
	//check the getValue() methode from cFunctionTwoValue
	if ( isEqual( pFunctionToTest->getValue(), dValue ) ){
	
		cout<<"The underfunction value is correctly "<<
			pFunctionToTest->getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction value is "<<
			pFunctionToTest->getValue() <<" but should be "<< dValue <<" ."<<endl;
		iReturn++;
	}
	//check the underfunctions
	//check getFirstUnderFunction()
	if ( pFunctionToTest->getFirstUnderFunction() != NULL  ){
	
		if ( pFunctionToTest->getFirstUnderFunction() != pFirstUnderfunction  ){
		
			cout<<"The first underfunction dosn't points to the object set as the first underfunction . "<<endl;
		}else{
			cerr<<"Error: The first underfunction points to the object set as the first underfunction."<<endl;
			iReturn++;
		}
		if ( *(pFunctionToTest->getFirstUnderFunction()) == *pFirstUnderfunction  ){
		
			cout<<"The first underfunction is equal to the underfunction set as the first underfunction . "<<endl;
		}else{
			cerr<<"Error: The first underfunction isn't equal to the underfunction set as the first underfunction."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The first underfunction is NULL ."<<endl;
		iReturn++;
	}
	//check getSecondUnderFunction()
	if ( pFunctionToTest->getSecondUnderFunction() != NULL  ){
	
		if ( pFunctionToTest->getSecondUnderFunction() != pSecondUnderfunction  ){
		
			cout<<"The second underfunction dosn't points to the object set as the second underfunction . "<<endl;
		}else{
			cerr<<"Error: The second underfunction points to the object set as the second underfunction."<<endl;
			iReturn++;
		}
		if ( *(pFunctionToTest->getSecondUnderFunction()) == *pSecondUnderfunction  ){
		
			cout<<"The second underfunction is equal to the underfunction set as the second underfunction . "<<endl;
		}else{
			cerr<<"Error: The second underfunction isn't equal to the underfunction set as the second underfunction."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The second underfunction is NULL ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionTwoValue
	if ( pFunctionToTest->getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			pFunctionToTest->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			pFunctionToTest->getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
	if ( pFunctionToTest->getSuperiorUnderFunction() == pSuperiorUnderFunction  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			pFunctionToTest->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			pFunctionToTest->getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	
	//check the isValid() methode from cFunctionTwoValue
	if ( pFunctionToTest->isValid() ){
	
		cout<<"The underfunction is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The underfunction is not valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cFunctionTwoValue
	if ( pFunctionToTest->getType() == getActualFunctionType() ){
	
		cout<<"The underfunction type is correctly FUNCTION_VARIABLE. "<<endl;
	}else{
		cerr<<"Error: The type of the underfunction is not FUNCTION_VARIABLE ( "<<
			cUnderFunction::FUNCTION_VARIABLE <<" ), but "<<
			pFunctionToTest->getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getUnderFunctionName() methode from cFunctionTwoValue
	if ( pFunctionToTest->getUnderFunctionName() == getActualFunctionName() ){
	
		cout<<"The underfunction name is correctly "<<
			pFunctionToTest->getUnderFunctionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the underfunction is not \"variable\", but "<<
			pFunctionToTest->getUnderFunctionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfUnderFunctions() methode from cFunctionTwoValue
	if ( pFunctionToTest->getNumberOfUnderFunctions() == 2 ){
	
		cout<<"The underfunction number of underfunctions is correctly "<<
			pFunctionToTest->getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction number of underfunctions is "<<
			pFunctionToTest->getNumberOfUnderFunctions() <<" , but should be 2 ."<<endl;
		iReturn++;
	}
	//check the getElementType() methode from cFunctionTwoValue
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
	//check the getDomain() methode from cFunctionTwoValue
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
	//check the getValueDomain() methode from cFunctionTwoValue
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
	//check the getStandardDomain() methode from cFunctionTwoValue
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
	//check the getVariableDomain() methode from cFunctionTwoValue
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
	//check the getTimeNeed() methode from cFunctionTwoValue
	if ( pFunctionToTest->getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the function is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the function is "<<
			pFunctionToTest->getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionTwoValue
	if ( pFunctionToTest->getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the function is "<<
			pFunctionToTest->getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	if ( ! pFunctionToTest->isUsedVariable( pVariableX ) ){
	
		cout<<"The variable pVariableX isn't used in the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableX is used in the underfunction. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cFunctionTwoValue
	setUsedVariables = pFunctionToTest->getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"Ther are correctly no used variables are given back from the underfunction. "<<endl;
	}else{
		cerr<<"Error: Ther are used variables are given back from the underfunction. "<<endl;
		iReturn++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the highest underFunctionTwoValue2"<<endl;

	pFunctionToTest = (cFunctionTwoValue*) &underFunctionTwoValue2;
	
	pFirstUnderfunction = &underFunctionVariable1;
	pSecondUnderfunction = &underFunctionTwoValue1;
	dValue = getActualFunctionValue( pFirstUnderfunction->getValue(),
		pSecondUnderfunction->getValue() );
	pDefiningFibElement = &rootEmpty;
	pSuperiorUnderFunction = NULL;
	pUnderFunctionDomain = &domainNaturalNumberBit5;
	pValueDomain = &domainNaturalNumberBit7;
	delete pVariableDomain;
	pVariableDomain = domainNaturalNumberBit3.clone();
	ulTimeNeed = 1 + pFirstUnderfunction->getTimeNeed() +
		 pSecondUnderfunction->getTimeNeed();
	ulCompressedSize = 5 + 5 + (5 + 9 + 9);
	
	set<cFibVariable*> setUsedVariablesCorrect;
	setUsedVariablesCorrect.insert( pVariable1 );
	
	//check the getValue() methode from cFunctionTwoValue
	if ( isEqual( pFunctionToTest->getValue(), dValue ) ){
	
		cout<<"The underfunction value is correctly "<<
			pFunctionToTest->getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction value is "<<
			pFunctionToTest->getValue() <<" but should be "<< dValue <<" ."<<endl;
		iReturn++;
	}
	//check the underfunctions
	//check getFirstUnderFunction()
	if ( pFunctionToTest->getFirstUnderFunction() != NULL  ){
	
		if ( pFunctionToTest->getFirstUnderFunction() != pFirstUnderfunction  ){
		
			cout<<"The first underfunction dosn't points to the object set as the first underfunction . "<<endl;
		}else{
			cerr<<"Error: The first underfunction points to the object set as the first underfunction."<<endl;
			iReturn++;
		}
		if ( *(pFunctionToTest->getFirstUnderFunction()) == *pFirstUnderfunction  ){
		
			cout<<"The first underfunction is equal to the underfunction set as the first underfunction . "<<endl;
		}else{
			cerr<<"Error: The first underfunction isn't equal to the underfunction set as the first underfunction."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The first underfunction is NULL ."<<endl;
		iReturn++;
	}
	//check getSecondUnderFunction()
	if ( pFunctionToTest->getSecondUnderFunction() != NULL  ){
	
		if ( pFunctionToTest->getSecondUnderFunction() != pSecondUnderfunction  ){
		
			cout<<"The second underfunction dosn't points to the object set as the second underfunction . "<<endl;
		}else{
			cerr<<"Error: The second underfunction points to the object set as the second underfunction."<<endl;
			iReturn++;
		}
		if ( *(pFunctionToTest->getSecondUnderFunction()) == *pSecondUnderfunction  ){
		
			cout<<"The second underfunction is equal to the underfunction set as the second underfunction . "<<endl;
		}else{
			cerr<<"Error: The second underfunction isn't equal to the underfunction set as the second underfunction."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The second underfunction is NULL ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionTwoValue
	if ( pFunctionToTest->getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			pFunctionToTest->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			pFunctionToTest->getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
	if ( pFunctionToTest->getSuperiorUnderFunction() == pSuperiorUnderFunction  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			pFunctionToTest->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			pFunctionToTest->getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	
	//check the isValid() methode from cFunctionTwoValue
	if ( ! pFunctionToTest->isValid() ){
	
		cout<<"The underfunction is correctly not valid . "<<endl;
	}else{
		cerr<<"Error: The underfunction is valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cFunctionTwoValue
	if ( pFunctionToTest->getType() == getActualFunctionType() ){
	
		cout<<"The underfunction type is correctly FUNCTION_VARIABLE. "<<endl;
	}else{
		cerr<<"Error: The type of the underfunction is not FUNCTION_VARIABLE ( "<<
			cUnderFunction::FUNCTION_VARIABLE <<" ), but "<<
			pFunctionToTest->getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getUnderFunctionName() methode from cFunctionTwoValue
	if ( pFunctionToTest->getUnderFunctionName() == getActualFunctionName() ){
	
		cout<<"The underfunction name is correctly "<<
			pFunctionToTest->getUnderFunctionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the underfunction is not \"variable\", but "<<
			pFunctionToTest->getUnderFunctionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfUnderFunctions() methode from cFunctionTwoValue
	if ( pFunctionToTest->getNumberOfUnderFunctions() == 2 ){
	
		cout<<"The underfunction number of underfunctions is correctly "<<
			pFunctionToTest->getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction number of underfunctions is "<<
			pFunctionToTest->getNumberOfUnderFunctions() <<" , but should be 2 ."<<endl;
		iReturn++;
	}
	//check the getElementType() methode from cFunctionTwoValue
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
	//check the getDomain() methode from cFunctionTwoValue
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
	//check the getValueDomain() methode from cFunctionTwoValue
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
	//check the getStandardDomain() methode from cFunctionTwoValue
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
	//check the getVariableDomain() methode from cFunctionTwoValue
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
	//check the getTimeNeed() methode from cFunctionTwoValue
	if ( pFunctionToTest->getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the function is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the function is "<<
			pFunctionToTest->getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionTwoValue
	if ( pFunctionToTest->getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the function is "<<
			pFunctionToTest->getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	if ( ! pFunctionToTest->isUsedVariable( pVariableX ) ){
	
		cout<<"The variable pVariableX isn't used in the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableX is used in the underfunction. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cFunctionTwoValue
	setUsedVariables = pFunctionToTest->getUsedVariables();
	if ( setUsedVariables == setUsedVariablesCorrect ){
	
		cout<<"The correct used variables are given back from the underfunction. "<<endl;
	}else{
		cerr<<"Error: The used variables are given back from the underfunction arn't correct. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an full cFunctionTwoValue underfunction with depth 3, testing the included underFunctionTwoValue1"<<endl;

	cout<<"cFunctionVariable underFunctionVariable2( pVariable2 );"<<endl;
	cFunctionVariable underFunctionVariable2( pVariable2 );
	
	cout<<"tUnderFunctionTwoValue underFunctionTwoValue3( "<<
		"underFunctionTwoValue2, underFunctionVariable2, NULL, &point1 );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue3( underFunctionTwoValue2,
		underFunctionVariable2, NULL, &point1 );
	
	pFunctionToTest = (cFunctionTwoValue*)((cFunctionTwoValue*)
		underFunctionTwoValue3.getFirstUnderFunction())->getSecondUnderFunction();
	
	pFirstUnderfunction = &underFunctionValue1;
	pSecondUnderfunction = &underFunctionValue2;
	dValue = getActualFunctionValue( pFirstUnderfunction->getValue(),
		pSecondUnderfunction->getValue() );
	pDefiningFibElement = &point1;
	pSuperiorUnderFunction = underFunctionTwoValue3.getFirstUnderFunction();
	pUnderFunctionDomain = &domainNaturalNumberBit5;
	pValueDomain = &domainNaturalNumberBit7;
	ulTimeNeed = 1 + pFirstUnderfunction->getTimeNeed() +
		 pSecondUnderfunction->getTimeNeed();
	
	ulCompressedSize = 5 + 9 + 9;
	
	setUsedVariablesCorrect.clear();
	
	//check the getValue() methode from cFunctionTwoValue
	if ( isEqual( pFunctionToTest->getValue(), dValue ) ){
	
		cout<<"The underfunction value is correctly "<<
			pFunctionToTest->getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction value is "<<
			pFunctionToTest->getValue() <<" but should be "<< dValue <<" ."<<endl;
		iReturn++;
	}
	//check the underfunctions
	//check getFirstUnderFunction()
	if ( pFunctionToTest->getFirstUnderFunction() != NULL  ){
	
		if ( pFunctionToTest->getFirstUnderFunction() != pFirstUnderfunction  ){
		
			cout<<"The first underfunction dosn't points to the object set as the first underfunction . "<<endl;
		}else{
			cerr<<"Error: The first underfunction points to the object set as the first underfunction."<<endl;
			iReturn++;
		}
		if ( *(pFunctionToTest->getFirstUnderFunction()) == *pFirstUnderfunction  ){
		
			cout<<"The first underfunction is equal to the underfunction set as the first underfunction . "<<endl;
		}else{
			cerr<<"Error: The first underfunction isn't equal to the underfunction set as the first underfunction."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The first underfunction is NULL ."<<endl;
		iReturn++;
	}
	//check getSecondUnderFunction()
	if ( pFunctionToTest->getSecondUnderFunction() != NULL  ){
	
		if ( pFunctionToTest->getSecondUnderFunction() != pSecondUnderfunction  ){
		
			cout<<"The second underfunction dosn't points to the object set as the second underfunction . "<<endl;
		}else{
			cerr<<"Error: The second underfunction points to the object set as the second underfunction."<<endl;
			iReturn++;
		}
		if ( *(pFunctionToTest->getSecondUnderFunction()) == *pSecondUnderfunction  ){
		
			cout<<"The second underfunction is equal to the underfunction set as the second underfunction . "<<endl;
		}else{
			cerr<<"Error: The second underfunction isn't equal to the underfunction set as the second underfunction."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The second underfunction is NULL ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionTwoValue
	if ( pFunctionToTest->getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			pFunctionToTest->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			pFunctionToTest->getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
	if ( pFunctionToTest->getSuperiorUnderFunction() == pSuperiorUnderFunction  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			pFunctionToTest->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			pFunctionToTest->getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	
	//check the isValid() methode from cFunctionTwoValue
	if ( pFunctionToTest->isValid() ){
	
		cout<<"The underfunction is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The underfunction is not valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cFunctionTwoValue
	if ( pFunctionToTest->getType() == getActualFunctionType() ){
	
		cout<<"The underfunction type is correctly FUNCTION_VARIABLE. "<<endl;
	}else{
		cerr<<"Error: The type of the underfunction is not FUNCTION_VARIABLE ( "<<
			cUnderFunction::FUNCTION_VARIABLE <<" ), but "<<
			pFunctionToTest->getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getUnderFunctionName() methode from cFunctionTwoValue
	if ( pFunctionToTest->getUnderFunctionName() == getActualFunctionName() ){
	
		cout<<"The underfunction name is correctly "<<
			pFunctionToTest->getUnderFunctionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the underfunction is not \"variable\", but "<<
			pFunctionToTest->getUnderFunctionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfUnderFunctions() methode from cFunctionTwoValue
	if ( pFunctionToTest->getNumberOfUnderFunctions() == 2 ){
	
		cout<<"The underfunction number of underfunctions is correctly "<<
			pFunctionToTest->getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction number of underfunctions is "<<
			pFunctionToTest->getNumberOfUnderFunctions() <<" , but should be 2 ."<<endl;
		iReturn++;
	}
	//check the getElementType() methode from cFunctionTwoValue
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
	//check the getDomain() methode from cFunctionTwoValue
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
	//check the getValueDomain() methode from cFunctionTwoValue
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
	//check the getStandardDomain() methode from cFunctionTwoValue
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
	//check the getVariableDomain() methode from cFunctionTwoValue
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
	//check the getTimeNeed() methode from cFunctionTwoValue
	if ( pFunctionToTest->getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the function is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the function is "<<
			pFunctionToTest->getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionTwoValue
	if ( pFunctionToTest->getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the function is "<<
			pFunctionToTest->getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	if ( ! pFunctionToTest->isUsedVariable( pVariableX ) ){
	
		cout<<"The variable pVariableX isn't used in the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableX is used in the underfunction. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cFunctionTwoValue
	setUsedVariables = pFunctionToTest->getUsedVariables();
	if ( setUsedVariables == setUsedVariablesCorrect ){
	
		cout<<"The correct used variables are given back from the underfunction. "<<endl;
	}else{
		cerr<<"Error: The used variables are given back from the underfunction arn't correct. "<<endl;
		iReturn++;
	}
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the constructed full cFunctionTwoValue underfunction with depth 3, testing the included underFunctionTwoValue2"<<endl;
	
	pFunctionToTest = (cFunctionTwoValue*)underFunctionTwoValue3.getFirstUnderFunction();
	
	pFirstUnderfunction = &underFunctionVariable1;
	pSecondUnderfunction = &underFunctionTwoValue1;
	dValue = getActualFunctionValue( pFirstUnderfunction->getValue(),
		pSecondUnderfunction->getValue() );
	pDefiningFibElement = &point1;
	pSuperiorUnderFunction = &underFunctionTwoValue3;
	pUnderFunctionDomain = &domainNaturalNumberBit5;
	pValueDomain = &domainNaturalNumberBit7;
	delete pVariableDomain;
	pVariableDomain = domainNaturalNumberBit3.clone();
	ulTimeNeed = 1 + pFirstUnderfunction->getTimeNeed() +
		 pSecondUnderfunction->getTimeNeed();
	
	ulCompressedSize = 5 + 5 + (5 + 9 + 9);
	
	setUsedVariablesCorrect.insert( pVariable1 );
	
	//check the getValue() methode from cFunctionTwoValue
	if ( isEqual( pFunctionToTest->getValue(), dValue ) ){
	
		cout<<"The underfunction value is correctly "<<
			pFunctionToTest->getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction value is "<<
			pFunctionToTest->getValue() <<" but should be "<< dValue <<" ."<<endl;
		iReturn++;
	}
	//check the underfunctions
	//check getFirstUnderFunction()
	if ( pFunctionToTest->getFirstUnderFunction() != NULL  ){
	
		if ( pFunctionToTest->getFirstUnderFunction() != pFirstUnderfunction  ){
		
			cout<<"The first underfunction dosn't points to the object set as the first underfunction . "<<endl;
		}else{
			cerr<<"Error: The first underfunction points to the object set as the first underfunction."<<endl;
			iReturn++;
		}
		if ( *(pFunctionToTest->getFirstUnderFunction()) == *pFirstUnderfunction  ){
		
			cout<<"The first underfunction is equal to the underfunction set as the first underfunction . "<<endl;
		}else{
			cerr<<"Error: The first underfunction isn't equal to the underfunction set as the first underfunction."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The first underfunction is NULL ."<<endl;
		iReturn++;
	}
	//check getSecondUnderFunction()
	if ( pFunctionToTest->getSecondUnderFunction() != NULL  ){
	
		if ( pFunctionToTest->getSecondUnderFunction() != pSecondUnderfunction  ){
		
			cout<<"The second underfunction dosn't points to the object set as the second underfunction . "<<endl;
		}else{
			cerr<<"Error: The second underfunction points to the object set as the second underfunction."<<endl;
			iReturn++;
		}
		if ( *(pFunctionToTest->getSecondUnderFunction()) == *pSecondUnderfunction  ){
		
			cout<<"The second underfunction is equal to the underfunction set as the second underfunction . "<<endl;
		}else{
			cerr<<"Error: The second underfunction isn't equal to the underfunction set as the second underfunction."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The second underfunction is NULL ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionTwoValue
	if ( pFunctionToTest->getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			pFunctionToTest->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			pFunctionToTest->getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
	if ( pFunctionToTest->getSuperiorUnderFunction() == pSuperiorUnderFunction  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			pFunctionToTest->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			pFunctionToTest->getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	
	//check the isValid() methode from cFunctionTwoValue
	if ( pFunctionToTest->isValid() ){
	
		cout<<"The underfunction is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The underfunction is not valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cFunctionTwoValue
	if ( pFunctionToTest->getType() == getActualFunctionType() ){
	
		cout<<"The underfunction type is correctly FUNCTION_VARIABLE. "<<endl;
	}else{
		cerr<<"Error: The type of the underfunction is not FUNCTION_VARIABLE ( "<<
			cUnderFunction::FUNCTION_VARIABLE <<" ), but "<<
			pFunctionToTest->getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getUnderFunctionName() methode from cFunctionTwoValue
	if ( pFunctionToTest->getUnderFunctionName() == getActualFunctionName() ){
	
		cout<<"The underfunction name is correctly "<<
			pFunctionToTest->getUnderFunctionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the underfunction is not \"variable\", but "<<
			pFunctionToTest->getUnderFunctionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfUnderFunctions() methode from cFunctionTwoValue
	if ( pFunctionToTest->getNumberOfUnderFunctions() == 2 ){
	
		cout<<"The underfunction number of underfunctions is correctly "<<
			pFunctionToTest->getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction number of underfunctions is "<<
			pFunctionToTest->getNumberOfUnderFunctions() <<" , but should be 2 ."<<endl;
		iReturn++;
	}
	//check the getElementType() methode from cFunctionTwoValue
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
	//check the getDomain() methode from cFunctionTwoValue
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
	//check the getValueDomain() methode from cFunctionTwoValue
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
	//check the getStandardDomain() methode from cFunctionTwoValue
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
	//check the getVariableDomain() methode from cFunctionTwoValue
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
	//check the getTimeNeed() methode from cFunctionTwoValue
	if ( pFunctionToTest->getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the function is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the function is "<<
			pFunctionToTest->getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionTwoValue
	if ( pFunctionToTest->getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the function is "<<
			pFunctionToTest->getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	if ( ! pFunctionToTest->isUsedVariable( pVariableX ) ){
	
		cout<<"The variable pVariableX isn't used in the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableX is used in the underfunction. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cFunctionTwoValue
	setUsedVariables = pFunctionToTest->getUsedVariables();
	if ( setUsedVariables == setUsedVariablesCorrect ){
	
		cout<<"The correct used variables are given back from the underfunction. "<<endl;
	}else{
		cerr<<"Error: The used variables are given back from the underfunction arn't correct. "<<endl;
		iReturn++;
	}
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the constructed full cFunctionTwoValue underfunction with depth 3, testing the included underFunctionTwoValue3"<<endl;
	
	pFunctionToTest = (cFunctionTwoValue*)&underFunctionTwoValue3;
	
	pFirstUnderfunction = &underFunctionTwoValue2;
	pSecondUnderfunction = &underFunctionVariable2;
	dValue = getActualFunctionValue( pFirstUnderfunction->getValue(),
		pSecondUnderfunction->getValue() );
	pDefiningFibElement = &point1;
	pSuperiorUnderFunction = NULL;
	pUnderFunctionDomain = &domainNaturalNumberBit5;
	pValueDomain = &domainNaturalNumberBit7;
	delete pVariableDomain;
	pVariableDomain = domainNaturalNumberBit3.clone();
	ulTimeNeed = 1 + pFirstUnderfunction->getTimeNeed() +
		 pSecondUnderfunction->getTimeNeed();
	
	ulCompressedSize = 5 + 5 +( 5 + 5 + (5 + 9 + 9) );
	
	setUsedVariablesCorrect.insert( pVariable2 );
	
	//check the getValue() methode from cFunctionTwoValue
	if ( isEqual( pFunctionToTest->getValue(), dValue ) ){
	
		cout<<"The underfunction value is correctly "<<
			pFunctionToTest->getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction value is "<<
			pFunctionToTest->getValue() <<" but should be "<< dValue <<" ."<<endl;
		iReturn++;
	}
	//check the underfunctions
	//check getFirstUnderFunction()
	if ( pFunctionToTest->getFirstUnderFunction() != NULL  ){
	
		if ( pFunctionToTest->getFirstUnderFunction() != pFirstUnderfunction  ){
		
			cout<<"The first underfunction dosn't points to the object set as the first underfunction . "<<endl;
		}else{
			cerr<<"Error: The first underfunction points to the object set as the first underfunction."<<endl;
			iReturn++;
		}
		if ( *(pFunctionToTest->getFirstUnderFunction()) == *pFirstUnderfunction  ){
		
			cout<<"The first underfunction is equal to the underfunction set as the first underfunction . "<<endl;
		}else{
			cerr<<"Error: The first underfunction isn't equal to the underfunction set as the first underfunction."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The first underfunction is NULL ."<<endl;
		iReturn++;
	}
	//check getSecondUnderFunction()
	if ( pFunctionToTest->getSecondUnderFunction() != NULL  ){
	
		if ( pFunctionToTest->getSecondUnderFunction() != pSecondUnderfunction  ){
		
			cout<<"The second underfunction dosn't points to the object set as the second underfunction . "<<endl;
		}else{
			cerr<<"Error: The second underfunction points to the object set as the second underfunction."<<endl;
			iReturn++;
		}
		if ( *(pFunctionToTest->getSecondUnderFunction()) == *pSecondUnderfunction  ){
		
			cout<<"The second underfunction is equal to the underfunction set as the second underfunction . "<<endl;
		}else{
			cerr<<"Error: The second underfunction isn't equal to the underfunction set as the second underfunction."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The second underfunction is NULL ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionTwoValue
	if ( pFunctionToTest->getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			pFunctionToTest->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			pFunctionToTest->getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
	if ( pFunctionToTest->getSuperiorUnderFunction() == pSuperiorUnderFunction  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			pFunctionToTest->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			pFunctionToTest->getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	
	//check the isValid() methode from cFunctionTwoValue
	if ( pFunctionToTest->isValid() ){
	
		cout<<"The underfunction is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The underfunction is not valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cFunctionTwoValue
	if ( pFunctionToTest->getType() == getActualFunctionType() ){
	
		cout<<"The underfunction type is correctly FUNCTION_VARIABLE. "<<endl;
	}else{
		cerr<<"Error: The type of the underfunction is not FUNCTION_VARIABLE ( "<<
			cUnderFunction::FUNCTION_VARIABLE <<" ), but "<<
			pFunctionToTest->getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getUnderFunctionName() methode from cFunctionTwoValue
	if ( pFunctionToTest->getUnderFunctionName() == getActualFunctionName() ){
	
		cout<<"The underfunction name is correctly "<<
			pFunctionToTest->getUnderFunctionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the underfunction is not \"variable\", but "<<
			pFunctionToTest->getUnderFunctionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfUnderFunctions() methode from cFunctionTwoValue
	if ( pFunctionToTest->getNumberOfUnderFunctions() == 2 ){
	
		cout<<"The underfunction number of underfunctions is correctly "<<
			pFunctionToTest->getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction number of underfunctions is "<<
			pFunctionToTest->getNumberOfUnderFunctions() <<" , but should be 2 ."<<endl;
		iReturn++;
	}
	//check the getElementType() methode from cFunctionTwoValue
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
	//check the getDomain() methode from cFunctionTwoValue
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
	//check the getValueDomain() methode from cFunctionTwoValue
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
	//check the getStandardDomain() methode from cFunctionTwoValue
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
	//check the getVariableDomain() methode from cFunctionTwoValue
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
	//check the getTimeNeed() methode from cFunctionTwoValue
	if ( pFunctionToTest->getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the function is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the function is "<<
			pFunctionToTest->getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionTwoValue
	if ( pFunctionToTest->getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the function is "<<
			pFunctionToTest->getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	if ( ! pFunctionToTest->isUsedVariable( pVariableX ) ){
	
		cout<<"The variable pVariableX isn't used in the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableX is used in the underfunction. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cFunctionTwoValue
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
	//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
	if ( pUnderfunction->getSuperiorUnderFunction() == pSuperiorUnderFunction  ){
	
		cout<<"   The superior underfunction of the underfunction correctly "<<
			pUnderfunction->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"   Error: The superior underfunction of the underfunction is "<<
			pUnderfunction->getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionTwoValue
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
 * cFunctionTwoValue class.
 *
 * methods tested:
 * 	- cUnderFunction * getFirstUnderFunction();
 * 	- void setFirstUnderFunction( const cUnderFunction & underFunction, bool bDeleteOld=true );
 * 	- cUnderFunction * getSecondUnderFunction();
 * 	- void setSecondUnderFunction( const cUnderFunction & underFunction, bool bDeleteOld=true );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param tUnderFunctionTwoValue the type of the tested cFunctionTwoValue
 * 	is of the type of this object
 * @return the number of erros occured in the test
 */
template <class tUnderFunctionTwoValue> int testUnderfunctions(
	unsigned long &ulTestphase, const tUnderFunctionTwoValue &function ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing method for setting the first underfunction"<<endl;
	
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
	
	cout<<"tUnderFunctionTwoValue underFunctionTwoValue1( underFunctionValue1, underFunctionValue2, NULL, &point1 );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue1( underFunctionValue1, underFunctionValue2, NULL, &point1 );

	cout<<"tUnderFunctionTwoValue underFunctionTwoValue2( underFunctionValue3, underFunctionValue4, NULL, &point2 );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue2( underFunctionValue3, underFunctionValue4, NULL, &point2 );


	cout<<"checking: underFunctionTwoValue1.getFirstUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue1.getFirstUnderFunction(),
		&underFunctionValue1, &underFunctionTwoValue1, &point1 );
	cout<<"checking: underFunctionTwoValue1.getSecondUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue1.getSecondUnderFunction(),
		&underFunctionValue2, &underFunctionTwoValue1, &point1 );
	
	cout<<"checking: underFunctionTwoValue2.getFirstUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue2.getFirstUnderFunction(),
		&underFunctionValue3, &underFunctionTwoValue2, &point2 );
	cout<<"checking: underFunctionTwoValue2.getSecondUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue2.getSecondUnderFunction(),
		&underFunctionValue4, &underFunctionTwoValue2, &point2 );


	cout<<endl<<"underFunctionTwoValue1.setFirstUnderFunction( underFunctionTwoValue2 );"<<endl;
	underFunctionTwoValue1.setFirstUnderFunction( underFunctionTwoValue2 );

	cout<<"checking: underFunctionTwoValue1.getFirstUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue1.getFirstUnderFunction(),
		&underFunctionTwoValue2, &underFunctionTwoValue1, &point1 );
	
	if ( underFunctionTwoValue1.getFirstUnderFunction() ){
		cout<<"checking: underFunctionTwoValue1.getFirstUnderFunction()->getFirstUnderFunction()"<<endl;
		iReturn += checkUnderFunction( ((cFunctionTwoValue*)(
			underFunctionTwoValue1.getFirstUnderFunction()))->getFirstUnderFunction(),
			&underFunctionValue3, underFunctionTwoValue1.getFirstUnderFunction(), &point1 );
		cout<<"checking: underFunctionTwoValue1.getSecondUnderFunction()->getFirstUnderFunction()"<<endl;
		iReturn += checkUnderFunction( ((cFunctionTwoValue*)(
			underFunctionTwoValue1.getFirstUnderFunction()))->getSecondUnderFunction(),
			&underFunctionValue4, underFunctionTwoValue1.getFirstUnderFunction(), &point1 );
	}
	cout<<"checking: underFunctionTwoValue1.getSecondUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue1.getSecondUnderFunction(),
		&underFunctionValue2, &underFunctionTwoValue1, &point1 );

	cout<<endl<<"underFunctionTwoValue1.setSecondUnderFunction( underFunctionTwoValue2 );"<<endl;
	underFunctionTwoValue1.setSecondUnderFunction( underFunctionTwoValue2 );

	cout<<"checking: underFunctionTwoValue1.getFirstUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue1.getFirstUnderFunction(),
		&underFunctionTwoValue2, &underFunctionTwoValue1, &point1 );
	
	if ( underFunctionTwoValue1.getFirstUnderFunction() ){
		cout<<"checking: underFunctionTwoValue1.getFirstUnderFunction()->getFirstUnderFunction()"<<endl;
		iReturn += checkUnderFunction( ((cFunctionTwoValue*)(
			underFunctionTwoValue1.getFirstUnderFunction()))->getFirstUnderFunction(),
			&underFunctionValue3, underFunctionTwoValue1.getFirstUnderFunction(), &point1 );
		cout<<"checking: underFunctionTwoValue1.getFirstUnderFunction()->getFirstUnderFunction()"<<endl;
		iReturn += checkUnderFunction( ((cFunctionTwoValue*)(
			underFunctionTwoValue1.getFirstUnderFunction()))->getSecondUnderFunction(),
			&underFunctionValue4, underFunctionTwoValue1.getFirstUnderFunction(), &point1 );
	}
	cout<<"checking: underFunctionTwoValue1.getSecondUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue1.getSecondUnderFunction(),
		&underFunctionTwoValue2, &underFunctionTwoValue1, &point1 );
	
	if ( underFunctionTwoValue1.getSecondUnderFunction() ){
		cout<<"checking: underFunctionTwoValue1.getSecondUnderFunction()->getFirstUnderFunction()"<<endl;
		iReturn += checkUnderFunction( ((cFunctionTwoValue*)(
			underFunctionTwoValue1.getSecondUnderFunction()))->getFirstUnderFunction(),
			&underFunctionValue3, underFunctionTwoValue1.getSecondUnderFunction(), &point1 );
		cout<<"checking: underFunctionTwoValue1.getSecondUnderFunction()->getSecondUnderFunction()"<<endl;
		iReturn += checkUnderFunction( ((cFunctionTwoValue*)(
			underFunctionTwoValue1.getSecondUnderFunction()))->getSecondUnderFunction(),
			&underFunctionValue4, underFunctionTwoValue1.getSecondUnderFunction(), &point1 );
	}


	cout<<endl<<"tUnderFunctionTwoValue underFunctionTwoValue2_Copy( underFunctionValue3, underFunctionValue4, NULL, NULL );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue2_Copy( underFunctionValue3, underFunctionValue4, NULL, NULL );
	cout<<"underFunctionTwoValue2.setSecondUnderFunction( underFunctionTwoValue1 );"<<endl;
	underFunctionTwoValue2.setSecondUnderFunction( underFunctionTwoValue1 );
	
	cout<<"checking: underFunctionTwoValue2.getFirstUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue2.getFirstUnderFunction(),
		&underFunctionValue3, &underFunctionTwoValue2, &point2 );
	
	cout<<"checking: underFunctionTwoValue2.getSecondUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue2.getSecondUnderFunction(),
		&underFunctionTwoValue1, &underFunctionTwoValue2, &point2 );
	if ( underFunctionTwoValue2.getSecondUnderFunction() ){
		cout<<"checking: underFunctionTwoValue2.getSecondUnderFunction()->getFirstUnderFunction()"<<endl;
		iReturn += checkUnderFunction( ((cFunctionTwoValue*)(
			underFunctionTwoValue2.getSecondUnderFunction()))->getFirstUnderFunction(),
			&underFunctionTwoValue2_Copy, underFunctionTwoValue2.getSecondUnderFunction(), &point2 );
		cout<<"checking: underFunctionTwoValue2.getSecondUnderFunction()->getSecondUnderFunction()"<<endl;
		iReturn += checkUnderFunction( ((cFunctionTwoValue*)(
			underFunctionTwoValue2.getSecondUnderFunction()))->getSecondUnderFunction(),
			&underFunctionTwoValue2_Copy, underFunctionTwoValue2.getSecondUnderFunction(), &point2 );
	}

	cout<<endl<<"tUnderFunctionTwoValue underFunctionTwoValue3( underFunctionValue1, underFunctionValue4 );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue3( underFunctionValue1, underFunctionValue4 );
	cout<<"underFunctionTwoValue2.setFirstUnderFunction( underFunctionTwoValue3 );"<<endl;
	underFunctionTwoValue2.setFirstUnderFunction( underFunctionTwoValue3 );
	
	cout<<"checking: underFunctionTwoValue2.getFirstUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue2.getFirstUnderFunction(),
		&underFunctionTwoValue3, &underFunctionTwoValue2, &point2 );
	if ( underFunctionTwoValue2.getFirstUnderFunction() ){
		cout<<"checking: underFunctionTwoValue2.getFirstUnderFunction()->getFirstUnderFunction()"<<endl;
		iReturn += checkUnderFunction( ((cFunctionTwoValue*)(
			underFunctionTwoValue2.getFirstUnderFunction()))->getFirstUnderFunction(),
			&underFunctionValue1, underFunctionTwoValue2.getFirstUnderFunction(), &point2 );
		cout<<"checking: underFunctionTwoValue2.getFirstUnderFunction()->getSecondUnderFunction()"<<endl;
		iReturn += checkUnderFunction( ((cFunctionTwoValue*)(
			underFunctionTwoValue2.getFirstUnderFunction()))->getSecondUnderFunction(),
			&underFunctionValue4, underFunctionTwoValue2.getFirstUnderFunction(), &point2 );
	}
	
	cout<<"checking: underFunctionTwoValue2.getSecondUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue2.getSecondUnderFunction(),
		&underFunctionTwoValue1, &underFunctionTwoValue2, &point2 );
	if ( underFunctionTwoValue2.getSecondUnderFunction() ){
		cout<<"checking: underFunctionTwoValue2.getSecondUnderFunction()->getFirstUnderFunction()"<<endl;
		iReturn += checkUnderFunction( ((cFunctionTwoValue*)(
			underFunctionTwoValue2.getSecondUnderFunction()))->getFirstUnderFunction(),
			&underFunctionTwoValue2_Copy, underFunctionTwoValue2.getSecondUnderFunction(), &point2 );
		cout<<"checking: underFunctionTwoValue2.getSecondUnderFunction()->getSecondUnderFunction()"<<endl;
		iReturn += checkUnderFunction( ((cFunctionTwoValue*)(
			underFunctionTwoValue2.getSecondUnderFunction()))->getSecondUnderFunction(),
			&underFunctionTwoValue2_Copy, underFunctionTwoValue2.getSecondUnderFunction(), &point2 );
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
 * This method tests equal method of the cFunctionTwoValue classes.
 *
 * methods tested:
 * 	- bool equal( const cFibElement & fibObject ) const
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param tUnderFunctionTwoValue the type of the tested cFunctionTwoValue
 * 	is of the type of this object
 * @return the number of erros occured in the test
 */
template <class tUnderFunctionTwoValue> int testEqual(
	unsigned long &ulTestphase, const tUnderFunctionTwoValue &function ){

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
	
	cout<<"tUnderFunctionTwoValue underFunctionTwoValue1V1_V2( underFunctionValue1_V1, underFunctionValue1_V2 );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue1V1_V2( underFunctionValue1_V1, underFunctionValue1_V2 );
	
	cout<<"tUnderFunctionTwoValue underFunctionTwoValue2V1_V2( underFunctionValue2_V1, underFunctionValue1_V2 );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue2V1_V2( underFunctionValue2_V1, underFunctionValue1_V2 );

	cout<<"tUnderFunctionTwoValue underFunctionTwoValue1V2_V1( underFunctionValue1_V2, underFunctionValue1_V1 );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue1V2_V1( underFunctionValue1_V2, underFunctionValue1_V1 );

	cout<<"tUnderFunctionTwoValue underFunctionTwoValue1V1_V1( underFunctionValue1_V1, underFunctionValue1_V1 );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue1V1_V1( underFunctionValue1_V1, underFunctionValue1_V1 );

	//functions with variables
	cout<<"cFunctionVariable underFunctionVriable1_V1( pVariable1 );"<<endl;
	cFunctionVariable underFunctionVriable1_V1( pVariable1 );
	cout<<"cFunctionVariable underFunctionVriable1_V2( pVariable2 );"<<endl;
	cFunctionVariable underFunctionVriable1_V2( pVariable2 );
	cout<<"cFunctionVariable underFunctionVriable2_V2( pVariable2 );"<<endl;
	cFunctionVariable underFunctionVriable2_V2( pVariable2 );
	cout<<"cFunctionVariable underFunctionVriable1_V3( pVariable3 );"<<endl;
	cFunctionVariable underFunctionVriable1_V3( pVariable3 );

	cout<<"tUnderFunctionTwoValue underFunctionTwoValue1_X1_X2( underFunctionVriable1_V1, underFunctionVriable1_V2 );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue1_X1_X2(  underFunctionVriable1_V1, underFunctionVriable1_V2 );

	cout<<"tUnderFunctionTwoValue underFunctionTwoValue2_X1_X2( underFunctionVriable1_V1, underFunctionVriable2_V2 );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue2_X1_X2(  underFunctionVriable1_V1, underFunctionVriable2_V2 );

	cout<<"tUnderFunctionTwoValue underFunctionTwoValue1_X2_X1( underFunctionVriable2_V2, underFunctionVriable1_V1 );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue1_X2_X1(  underFunctionVriable2_V2, underFunctionVriable1_V1 );

	cout<<"tUnderFunctionTwoValue underFunctionTwoValue1_X3_X2( underFunctionVriable1_V3, underFunctionVriable2_V2 );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue1_X3_X2(  underFunctionVriable1_V3, underFunctionVriable2_V2 );


	//function with defining fib -element
	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	cout<<"tUnderFunctionTwoValue underFunctionTwoValueDE1_V1_V2( underFunctionValue1_V1, underFunctionValue1_V2, NULL, &rootSimple1 );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValueDE1_V1_V2( underFunctionValue1_V1, underFunctionValue1_V2, NULL, &rootSimple1 );
	
	//function with superior underfunction
	cout<<"cFunctionValue underFunctionSup( 3.33 );"<<endl;
	cFunctionValue underFunctionSup( 3.333 );
	cout<<"tUnderFunctionTwoValue underFunctionTwoValueSup1_V1_V2( underFunctionValue1_V1, underFunctionValue1_V2, & underFunctionSup );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValueSup1_V1_V2( underFunctionValue1_V1, underFunctionValue1_V2, & underFunctionSup );

	//underfunction with domains set
	cout<<"root1 rootSimple1;"<<endl;
	cRoot root1;
	
	cout<<"cTypeUnderFunction testTypeUnderFunction;"<<endl;
	cTypeUnderFunction testTypeUnderFunction;
	cout<<"cDomainNaturalNumberBit domainNat8( 8 );"<<endl;
	cDomainNaturalNumberBit domainNat8( 8 );

	cout<<"root1.getDomains()->addDomain( testTypeUnderFunction, &domainNat8 );"<<endl;
	root1.getDomains()->addDomain( testTypeUnderFunction, &domainNat8 );

	cout<<"tUnderFunctionTwoValue underFunctionTwoValueDom1_V1_V2( underFunctionValue1_V1, underFunctionValue1_V2, NULL, &root1 );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValueDom1_V1_V2( underFunctionValue1_V1, underFunctionValue1_V2, NULL, &root1 );
	
	//function with defining fib -element and superior underfunction
	cout<<"cRoot rootSimple2;"<<endl;
	cRoot rootSimple2;
	cout<<"cFunctionValue underFunctionSup2( 5.0 );"<<endl;
	cFunctionValue underFunctionSup2( 5.0 );
	
	cout<<"tUnderFunctionTwoValue underFunctionTwoValueSupDE1_V1_V2( underFunctionValue1_V1, underFunctionValue1_V2, & underFunctionSup2, &rootSimple2 );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValueSupDE1_V1_V2( underFunctionValue1_V1, underFunctionValue1_V2, & underFunctionSup2, &rootSimple2 );


	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with underFunctionTwoValue1V1_V2
	cUnderFunction * actualObject = &underFunctionTwoValue1V1_V2;
	string szActualObjectName = "underFunctionTwoValue1V1_V2";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V2, "underFunctionTwoValue1V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2V1_V2, "underFunctionTwoValue2V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V2_V1, "underFunctionTwoValue1V2_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V1, "underFunctionTwoValue1V1_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X1_X2, "underFunctionTwoValue1_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2_X1_X2, "underFunctionTwoValue2_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X2_X1, "underFunctionTwoValue1_X2_X1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X3_X2, "underFunctionTwoValue1_X3_X2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDE1_V1_V2, "underFunctionTwoValueDE1_V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSup1_V1_V2, "underFunctionTwoValueSup1_V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDom1_V1_V2, "underFunctionTwoValueDom1_V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSupDE1_V1_V2, "underFunctionTwoValueSupDE1_V1_V2" );

	//compare with underFunctionTwoValue2V1_V2
	actualObject = &underFunctionTwoValue2V1_V2;
	szActualObjectName = "underFunctionTwoValue2V1_V2";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V2, "underFunctionTwoValue1V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2V1_V2, "underFunctionTwoValue2V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V2_V1, "underFunctionTwoValue1V2_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V1, "underFunctionTwoValue1V1_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X1_X2, "underFunctionTwoValue1_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2_X1_X2, "underFunctionTwoValue2_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X2_X1, "underFunctionTwoValue1_X2_X1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X3_X2, "underFunctionTwoValue1_X3_X2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDE1_V1_V2, "underFunctionTwoValueDE1_V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSup1_V1_V2, "underFunctionTwoValueSup1_V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDom1_V1_V2, "underFunctionTwoValueDom1_V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSupDE1_V1_V2, "underFunctionTwoValueSupDE1_V1_V2" );

	//compare with underFunctionTwoValue2V1_V2
	actualObject = &underFunctionTwoValue1V2_V1;
	szActualObjectName = "underFunctionTwoValue1V2_V1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V2, "underFunctionTwoValue1V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2V1_V2, "underFunctionTwoValue2V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V2_V1, "underFunctionTwoValue1V2_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V1, "underFunctionTwoValue1V1_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X1_X2, "underFunctionTwoValue1_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2_X1_X2, "underFunctionTwoValue2_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X2_X1, "underFunctionTwoValue1_X2_X1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X3_X2, "underFunctionTwoValue1_X3_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDE1_V1_V2, "underFunctionTwoValueDE1_V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSup1_V1_V2, "underFunctionTwoValueSup1_V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDom1_V1_V2, "underFunctionTwoValueDom1_V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSupDE1_V1_V2, "underFunctionTwoValueSupDE1_V1_V2" );

	//compare with underFunctionTwoValue1V1_V1
	actualObject = &underFunctionTwoValue1V1_V1;
	szActualObjectName = "underFunctionTwoValue1V1_V1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V2, "underFunctionTwoValue1V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2V1_V2, "underFunctionTwoValue2V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V2_V1, "underFunctionTwoValue1V2_V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V1, "underFunctionTwoValue1V1_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X1_X2, "underFunctionTwoValue1_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2_X1_X2, "underFunctionTwoValue2_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X2_X1, "underFunctionTwoValue1_X2_X1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X3_X2, "underFunctionTwoValue1_X3_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDE1_V1_V2, "underFunctionTwoValueDE1_V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSup1_V1_V2, "underFunctionTwoValueSup1_V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDom1_V1_V2, "underFunctionTwoValueDom1_V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSupDE1_V1_V2, "underFunctionTwoValueSupDE1_V1_V2" );

	//compare with underFunctionTwoValue1_X1_X2
	actualObject = &underFunctionTwoValue1_X1_X2;
	szActualObjectName = "underFunctionTwoValue1_X1_X2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V2, "underFunctionTwoValue1V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2V1_V2, "underFunctionTwoValue2V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V2_V1, "underFunctionTwoValue1V2_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V1, "underFunctionTwoValue1V1_V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X1_X2, "underFunctionTwoValue1_X1_X2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2_X1_X2, "underFunctionTwoValue2_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X2_X1, "underFunctionTwoValue1_X2_X1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X3_X2, "underFunctionTwoValue1_X3_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDE1_V1_V2, "underFunctionTwoValueDE1_V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSup1_V1_V2, "underFunctionTwoValueSup1_V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDom1_V1_V2, "underFunctionTwoValueDom1_V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSupDE1_V1_V2, "underFunctionTwoValueSupDE1_V1_V2" );

	//compare with underFunctionTwoValue2_X1_X2
	actualObject = &underFunctionTwoValue2_X1_X2;
	szActualObjectName = "underFunctionTwoValue2_X1_X2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V2, "underFunctionTwoValue1V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2V1_V2, "underFunctionTwoValue2V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V2_V1, "underFunctionTwoValue1V2_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V1, "underFunctionTwoValue1V1_V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X1_X2, "underFunctionTwoValue1_X1_X2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2_X1_X2, "underFunctionTwoValue2_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X2_X1, "underFunctionTwoValue1_X2_X1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X3_X2, "underFunctionTwoValue1_X3_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDE1_V1_V2, "underFunctionTwoValueDE1_V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSup1_V1_V2, "underFunctionTwoValueSup1_V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDom1_V1_V2, "underFunctionTwoValueDom1_V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSupDE1_V1_V2, "underFunctionTwoValueSupDE1_V1_V2" );

	//compare with underFunctionTwoValue1_X2_X1
	actualObject = &underFunctionTwoValue1_X2_X1;
	szActualObjectName = "underFunctionTwoValue1_X2_X1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V2, "underFunctionTwoValue1V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2V1_V2, "underFunctionTwoValue2V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V2_V1, "underFunctionTwoValue1V2_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V1, "underFunctionTwoValue1V1_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X1_X2, "underFunctionTwoValue1_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2_X1_X2, "underFunctionTwoValue2_X1_X2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X2_X1, "underFunctionTwoValue1_X2_X1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X3_X2, "underFunctionTwoValue1_X3_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDE1_V1_V2, "underFunctionTwoValueDE1_V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSup1_V1_V2, "underFunctionTwoValueSup1_V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDom1_V1_V2, "underFunctionTwoValueDom1_V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSupDE1_V1_V2, "underFunctionTwoValueSupDE1_V1_V2" );

	//compare with underFunctionTwoValue1_X3_X2
	actualObject = &underFunctionTwoValue1_X3_X2;
	szActualObjectName = "underFunctionTwoValue1_X3_X2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V2, "underFunctionTwoValue1V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2V1_V2, "underFunctionTwoValue2V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V2_V1, "underFunctionTwoValue1V2_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V1, "underFunctionTwoValue1V1_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X1_X2, "underFunctionTwoValue1_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2_X1_X2, "underFunctionTwoValue2_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X2_X1, "underFunctionTwoValue1_X2_X1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X3_X2, "underFunctionTwoValue1_X3_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDE1_V1_V2, "underFunctionTwoValueDE1_V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSup1_V1_V2, "underFunctionTwoValueSup1_V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDom1_V1_V2, "underFunctionTwoValueDom1_V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSupDE1_V1_V2, "underFunctionTwoValueSupDE1_V1_V2" );

	//compare with underFunctionTwoValueDE1_V1_V2
	actualObject = &underFunctionTwoValueDE1_V1_V2;
	szActualObjectName = "underFunctionTwoValueDE1_V1_V2";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V2, "underFunctionTwoValue1V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2V1_V2, "underFunctionTwoValue2V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V2_V1, "underFunctionTwoValue1V2_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V1, "underFunctionTwoValue1V1_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X1_X2, "underFunctionTwoValue1_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2_X1_X2, "underFunctionTwoValue2_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X2_X1, "underFunctionTwoValue1_X2_X1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X3_X2, "underFunctionTwoValue1_X3_X2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDE1_V1_V2, "underFunctionTwoValueDE1_V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSup1_V1_V2, "underFunctionTwoValueSup1_V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDom1_V1_V2, "underFunctionTwoValueDom1_V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSupDE1_V1_V2, "underFunctionTwoValueSupDE1_V1_V2" );

	//compare with underFunctionTwoValueSup1_V1_V2
	actualObject = &underFunctionTwoValueSup1_V1_V2;
	szActualObjectName = "underFunctionTwoValueSup1_V1_V2";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V2, "underFunctionTwoValue1V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2V1_V2, "underFunctionTwoValue2V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V2_V1, "underFunctionTwoValue1V2_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V1, "underFunctionTwoValue1V1_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X1_X2, "underFunctionTwoValue1_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2_X1_X2, "underFunctionTwoValue2_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X2_X1, "underFunctionTwoValue1_X2_X1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X3_X2, "underFunctionTwoValue1_X3_X2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDE1_V1_V2, "underFunctionTwoValueDE1_V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSup1_V1_V2, "underFunctionTwoValueSup1_V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDom1_V1_V2, "underFunctionTwoValueDom1_V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSupDE1_V1_V2, "underFunctionTwoValueSupDE1_V1_V2" );

	//compare with underFunctionTwoValueDom1_V1_V2
	actualObject = &underFunctionTwoValueDom1_V1_V2;
	szActualObjectName = "underFunctionTwoValueDom1_V1_V2";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V2, "underFunctionTwoValue1V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2V1_V2, "underFunctionTwoValue2V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V2_V1, "underFunctionTwoValue1V2_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V1, "underFunctionTwoValue1V1_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X1_X2, "underFunctionTwoValue1_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2_X1_X2, "underFunctionTwoValue2_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X2_X1, "underFunctionTwoValue1_X2_X1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X3_X2, "underFunctionTwoValue1_X3_X2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDE1_V1_V2, "underFunctionTwoValueDE1_V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSup1_V1_V2, "underFunctionTwoValueSup1_V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDom1_V1_V2, "underFunctionTwoValueDom1_V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSupDE1_V1_V2, "underFunctionTwoValueSupDE1_V1_V2" );

	//compare with underFunctionTwoValueSupDE1_V1_V2
	actualObject = &underFunctionTwoValueSupDE1_V1_V2;
	szActualObjectName = "underFunctionTwoValueSupDE1_V1_V2";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V2, "underFunctionTwoValue1V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2V1_V2, "underFunctionTwoValue2V1_V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V2_V1, "underFunctionTwoValue1V2_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1V1_V1, "underFunctionTwoValue1V1_V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X1_X2, "underFunctionTwoValue1_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue2_X1_X2, "underFunctionTwoValue2_X1_X2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X2_X1, "underFunctionTwoValue1_X2_X1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValue1_X3_X2, "underFunctionTwoValue1_X3_X2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDE1_V1_V2, "underFunctionTwoValueDE1_V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSup1_V1_V2, "underFunctionTwoValueSup1_V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueDom1_V1_V2, "underFunctionTwoValueDom1_V1_V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionTwoValueSupDE1_V1_V2, "underFunctionTwoValueSupDE1_V1_V2" );


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
 * This method tests the copy methods and copyconstructor of the cFunctionTwoValue class.
 *
 * methods tested:
 * 	- cFunctionTwoValue( const cFunctionTwoValue & underfunction, cUnderFunction * pInSuperiorFunction = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- cUnderFunction * clone( cUnderFunction * pInSuperiorUnderFunction = NULL, cFibElement *pInDefiningFibElement = NULL) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param tUnderFunctionTwoValue the type of the tested cFunctionTwoValue
 * 	is of the type of this object
 * @return the number of erros occured in the test
 */
template <class tUnderFunctionTwoValue> int testCopy(
	unsigned long &ulTestphase, const tUnderFunctionTwoValue &function ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a simple cFunctionTwoValue"<<endl;
	
	cout<<"cFunctionValue underFunctionValue1_V1( 1.0 );"<<endl;
	cFunctionValue underFunctionValue1_V1( 1.0 );
	cout<<"cFunctionValue underFunctionValue1_V2( 2.0 );"<<endl;
	cFunctionValue underFunctionValue1_V2( 2.0 );
	
	cout<<"tUnderFunctionTwoValue ufTwoValue1V1_V2( underFunctionValue1_V1, underFunctionValue1_V2 );"<<endl;
	tUnderFunctionTwoValue ufTwoValue1V1_V2( underFunctionValue1_V1, underFunctionValue1_V2 );

	cout<<"tUnderFunctionTwoValue ufTwoValue1V1_V2CopyConstruct( ufTwoValue1V1_V2 );"<<endl;
	tUnderFunctionTwoValue ufTwoValue1V1_V2CopyConstruct( ufTwoValue1V1_V2 );

	iReturn += testCompareTwoEqualObjects( ufTwoValue1V1_V2CopyConstruct, "ufTwoValue1V1_V2CopyConstruct", ufTwoValue1V1_V2, "ufTwoValue1V1_V2" );
	iReturn += testNotConnectedUnderFunction( ufTwoValue1V1_V2CopyConstruct );
	cout<<"checking: ufTwoValue1V1_V2CopyConstruct.getFirstUnderFunction()"<<endl;
	iReturn += checkUnderFunction( ufTwoValue1V1_V2CopyConstruct.getFirstUnderFunction(),
		ufTwoValue1V1_V2.getFirstUnderFunction(), &ufTwoValue1V1_V2CopyConstruct, NULL );
	cout<<"checking: ufTwoValue1V1_V2CopyConstruct.getSecondUnderFunction()"<<endl;
	iReturn += checkUnderFunction( ufTwoValue1V1_V2CopyConstruct.getSecondUnderFunction(),
		ufTwoValue1V1_V2.getSecondUnderFunction(), &ufTwoValue1V1_V2CopyConstruct, NULL );

	cout<<endl<<"cFunctionTwoValue * pUfTwoValue1V1_V2Clone = ufTwoValue1V1_V2CopyConstruct.clone();"<<endl;
	cFunctionTwoValue * pUfTwoValue1V1_V2Clone = ufTwoValue1V1_V2CopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pUfTwoValue1V1_V2Clone, "pUfTwoValue1V1_V2Clone", ufTwoValue1V1_V2, "ufTwoValue1V1_V2" );
	iReturn += testNotConnectedUnderFunction( *pUfTwoValue1V1_V2Clone );
	cout<<"checking: pUfTwoValue1V1_V2Clone->getFirstUnderFunction()"<<endl;
	iReturn += checkUnderFunction( pUfTwoValue1V1_V2Clone->getFirstUnderFunction(),
		ufTwoValue1V1_V2.getFirstUnderFunction(), pUfTwoValue1V1_V2Clone, NULL );
	cout<<"checking: pUfTwoValue1V1_V2Clone->getSecondUnderFunction()"<<endl;
	iReturn += checkUnderFunction( pUfTwoValue1V1_V2Clone->getSecondUnderFunction(),
		ufTwoValue1V1_V2.getSecondUnderFunction(), pUfTwoValue1V1_V2Clone, NULL );
	delete pUfTwoValue1V1_V2Clone;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cFunctionTwoValue with variable underfunctions"<<endl;

	cout<<"cRoot rootEmpty;"<<endl;
	cRoot rootEmpty;
	cout<<"rootEmpty.setNumberOfInputVariables( 10 );"<<endl;
	rootEmpty.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 =  rootEmpty.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 =  rootEmpty.getInputVariable( 1 );
	cout<<"pVariable2 =  rootEmpty.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 =  rootEmpty.getInputVariable( 2 );
	
	cout<<"cFunctionVariable underFunctionVariable1_V1( pVariable1 );"<<endl;
	cFunctionVariable underFunctionVariable1_V1( pVariable1 );
	cout<<"cFunctionVariable underFunctionVariable1_V2( pVariable2 );"<<endl;
	cFunctionVariable underFunctionVariable1_V2( pVariable2 );
	
	cout<<"tUnderFunctionTwoValue ufTwoVariable1V1_V2( underFunctionVariable1_V1, underFunctionVariable1_V2 );"<<endl;
	tUnderFunctionTwoValue ufTwoVariable1V1_V2( underFunctionVariable1_V1, underFunctionVariable1_V2 );

	cout<<"tUnderFunctionTwoValue ufTwoVariable1V1_V2CopyConstruct( ufTwoVariable1V1_V2 );"<<endl;
	tUnderFunctionTwoValue ufTwoVariable1V1_V2CopyConstruct( ufTwoVariable1V1_V2 );

	iReturn += testCompareTwoEqualObjects( ufTwoVariable1V1_V2CopyConstruct, "ufTwoVariable1V1_V2CopyConstruct", ufTwoVariable1V1_V2, "ufTwoVariable1V1_V2" );
	iReturn += testNotConnectedUnderFunction( ufTwoVariable1V1_V2CopyConstruct );
	cout<<"checking: ufTwoVariable1V1_V2CopyConstruct.getFirstUnderFunction()"<<endl;
	iReturn += checkUnderFunction( ufTwoVariable1V1_V2CopyConstruct.getFirstUnderFunction(),
		ufTwoVariable1V1_V2.getFirstUnderFunction(), &ufTwoVariable1V1_V2CopyConstruct, NULL );
	cout<<"checking: ufTwoVariable1V1_V2CopyConstruct.getSecondUnderFunction()"<<endl;
	iReturn += checkUnderFunction( ufTwoVariable1V1_V2CopyConstruct.getSecondUnderFunction(),
		ufTwoVariable1V1_V2.getSecondUnderFunction(), &ufTwoVariable1V1_V2CopyConstruct, NULL );

	cout<<endl<<"cFunctionTwoValue * pUfTwoVariable1V1_V2Clone = ufTwoVariable1V1_V2CopyConstruct.clone();"<<endl;
	cFunctionTwoValue * pUfTwoVariable1V1_V2Clone = ufTwoVariable1V1_V2CopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pUfTwoVariable1V1_V2Clone, "pUfTwoVariable1V1_V2Clone", ufTwoVariable1V1_V2, "ufTwoVariable1V1_V2" );
	iReturn += testNotConnectedUnderFunction( *pUfTwoVariable1V1_V2Clone );
	cout<<"checking: pUfTwoVariable1V1_V2Clone->getFirstUnderFunction()"<<endl;
	iReturn += checkUnderFunction( pUfTwoVariable1V1_V2Clone->getFirstUnderFunction(),
		ufTwoVariable1V1_V2.getFirstUnderFunction(), pUfTwoVariable1V1_V2Clone, NULL );
	cout<<"checking: pUfTwoVariable1V1_V2Clone->getSecondUnderFunction()"<<endl;
	iReturn += checkUnderFunction( pUfTwoVariable1V1_V2Clone->getSecondUnderFunction(),
		ufTwoVariable1V1_V2.getSecondUnderFunction(), pUfTwoVariable1V1_V2Clone, NULL );
	delete pUfTwoVariable1V1_V2Clone;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cFunctionTwoValue with a superior underfunction and defining fib -element"<<endl;

	//function with defining fib -element and superior underfunction
	cout<<"cRoot rootSimple;"<<endl;
	cRoot rootSimple;
	cout<<"cFunctionValue underFunctionSup( 325.142 );"<<endl;
	cFunctionValue underFunctionSup( 325.142 );

	cout<<"tUnderFunctionTwoValue ufTwoDefUf1V1_V2( underFunctionValue1_V1, underFunctionValue1_V2, &underFunctionSup, &rootSimple );"<<endl;
	tUnderFunctionTwoValue ufTwoDefUf1V1_V2( underFunctionValue1_V1, underFunctionValue1_V2, &underFunctionSup, &rootSimple );

	cout<<"tUnderFunctionTwoValue ufTwoDefUf1V1_V2CopyConstruct( ufTwoDefUf1V1_V2 );"<<endl;
	tUnderFunctionTwoValue ufTwoDefUf1V1_V2CopyConstruct( ufTwoDefUf1V1_V2 );

	iReturn += testCompareTwoEqualObjects( ufTwoDefUf1V1_V2CopyConstruct, "ufTwoDefUf1V1_V2CopyConstruct", ufTwoDefUf1V1_V2, "ufTwoDefUf1V1_V2" );
	cout<<"checking: ufTwoDefUf1V1_V2CopyConstruct"<<endl;
	iReturn += checkUnderFunction( &ufTwoDefUf1V1_V2CopyConstruct,
		&ufTwoValue1V1_V2, NULL, &rootSimple );
	cout<<"checking: ufTwoDefUf1V1_V2CopyConstruct.getFirstUnderFunction()"<<endl;
	iReturn += checkUnderFunction( ufTwoDefUf1V1_V2CopyConstruct.getFirstUnderFunction(),
		ufTwoDefUf1V1_V2.getFirstUnderFunction(), &ufTwoDefUf1V1_V2CopyConstruct, &rootSimple );
	cout<<"checking: ufTwoDefUf1V1_V2CopyConstruct.getSecondUnderFunction()"<<endl;
	iReturn += checkUnderFunction( ufTwoDefUf1V1_V2CopyConstruct.getSecondUnderFunction(),
		ufTwoDefUf1V1_V2.getSecondUnderFunction(), &ufTwoDefUf1V1_V2CopyConstruct, &rootSimple );

	cout<<endl<<"cFunctionTwoValue * pUfTwoDefUf1V1_V2Clone = ufTwoDefUf1V1_V2CopyConstruct.clone();"<<endl;
	cFunctionTwoValue * pUfTwoDefUf1V1_V2Clone = ufTwoDefUf1V1_V2CopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pUfTwoDefUf1V1_V2Clone, "pUfTwoDefUf1V1_V2Clone", ufTwoDefUf1V1_V2, "ufTwoDefUf1V1_V2" );
	cout<<"checking: pUfTwoDefUf1V1_V2Clone"<<endl;
	iReturn += checkUnderFunction( pUfTwoDefUf1V1_V2Clone,
		&ufTwoValue1V1_V2, NULL, &rootSimple );
	cout<<"checking: pUfTwoDefUf1V1_V2Clone->getFirstUnderFunction()"<<endl;
	iReturn += checkUnderFunction( pUfTwoDefUf1V1_V2Clone->getFirstUnderFunction(),
		ufTwoDefUf1V1_V2.getFirstUnderFunction(), pUfTwoDefUf1V1_V2Clone, &rootSimple );
	cout<<"checking: pUfTwoDefUf1V1_V2Clone->getSecondUnderFunction()"<<endl;
	iReturn += checkUnderFunction( pUfTwoDefUf1V1_V2Clone->getSecondUnderFunction(),
		ufTwoDefUf1V1_V2.getSecondUnderFunction(), pUfTwoDefUf1V1_V2Clone, &rootSimple );
	delete pUfTwoDefUf1V1_V2Clone;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cFunctionTwoValue with a superior underfunction and defining fib -element which will be changed"<<endl;

	//function with defining fib -element and superior underfunction
	cout<<"cRoot rootSimple2;"<<endl;
	cRoot rootSimple2;
	cout<<"cFunctionValue underFunctionSup2( 42.0 );"<<endl;
	cFunctionValue underFunctionSup2( 42.0 );

	cout<<"tUnderFunctionTwoValue ufTwoDefUf2V1_V2( underFunctionValue1_V1, underFunctionValue1_V2, &underFunctionSup, &rootSimple );"<<endl;
	tUnderFunctionTwoValue ufTwoDefUf2V1_V2( underFunctionValue1_V1, underFunctionValue1_V2, &underFunctionSup, &rootSimple );

	cout<<"tUnderFunctionTwoValue ufTwoDefUf2V1_V2CopyConstruct( ufTwoDefUf2V1_V2, &underFunctionSup2, &rootSimple2 );"<<endl;
	tUnderFunctionTwoValue ufTwoDefUf2V1_V2CopyConstruct( ufTwoDefUf2V1_V2, &underFunctionSup2, &rootSimple2 );

	iReturn += testCompareTwoEqualObjects( ufTwoDefUf2V1_V2CopyConstruct, "ufTwoDefUf2V1_V2CopyConstruct", ufTwoDefUf2V1_V2, "ufTwoDefUf2V1_V2" );
	cout<<"checking: ufTwoDefUf2V1_V2CopyConstruct"<<endl;
	iReturn += checkUnderFunction( &ufTwoDefUf2V1_V2CopyConstruct,
		&ufTwoValue1V1_V2, &underFunctionSup2, &rootSimple2 );
	cout<<"checking: ufTwoDefUf2V1_V2CopyConstruct.getFirstUnderFunction()"<<endl;
	iReturn += checkUnderFunction( ufTwoDefUf2V1_V2CopyConstruct.getFirstUnderFunction(),
		ufTwoDefUf2V1_V2.getFirstUnderFunction(), &ufTwoDefUf2V1_V2CopyConstruct, &rootSimple2 );
	cout<<"checking: ufTwoDefUf2V1_V2CopyConstruct.getSecondUnderFunction()"<<endl;
	iReturn += checkUnderFunction( ufTwoDefUf2V1_V2CopyConstruct.getSecondUnderFunction(),
		ufTwoDefUf2V1_V2.getSecondUnderFunction(), &ufTwoDefUf2V1_V2CopyConstruct, &rootSimple2 );

	cout<<endl<<"cFunctionTwoValue * pUfTwoDefUf2V1_V2Clone = ufTwoDefUf2V1_V2CopyConstruct.clone( &underFunctionSup2, &rootSimple2);"<<endl;
	cFunctionTwoValue * pUfTwoDefUf2V1_V2Clone = ufTwoDefUf2V1_V2CopyConstruct.clone( &underFunctionSup2, &rootSimple2);

	iReturn += testCompareTwoEqualObjects( *pUfTwoDefUf2V1_V2Clone, "pUfTwoDefUf2V1_V2Clone", ufTwoDefUf2V1_V2, "ufTwoDefUf2V1_V2" );
	cout<<"checking: pUfTwoDefUf2V1_V2Clone"<<endl;
	iReturn += checkUnderFunction( pUfTwoDefUf2V1_V2Clone,
		&ufTwoValue1V1_V2, &underFunctionSup2, &rootSimple2 );
	cout<<"checking: pUfTwoDefUf2V1_V2Clone->getFirstUnderFunction()"<<endl;
	iReturn += checkUnderFunction( pUfTwoDefUf2V1_V2Clone->getFirstUnderFunction(),
		ufTwoDefUf2V1_V2.getFirstUnderFunction(), pUfTwoDefUf2V1_V2Clone, &rootSimple2 );
	cout<<"checking: pUfTwoDefUf2V1_V2Clone->getSecondUnderFunction()"<<endl;
	iReturn += checkUnderFunction( pUfTwoDefUf2V1_V2Clone->getSecondUnderFunction(),
		ufTwoDefUf2V1_V2.getSecondUnderFunction(), pUfTwoDefUf2V1_V2Clone, &rootSimple2 );
	delete pUfTwoDefUf2V1_V2Clone;


	return iReturn;
}



/**
 * This method tests a in the xml -format stored cFunctionTwoValue.
 * The underfunctions of the cFunctionTwoValue should be two value underfunction
 * ( cFunctionValue ).
 *
 * @param szFilename the name of the file wher the cFunctionTwoValue is stored
 * @param dValue1 the value of the first underfunction
 * @param dValue2 the value of the second underfunction
 * @return the number of errors occured in the test
 */
int testXmlFunctionTwoValue( const string szFilename, double dValue1, double dValue2 ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored cFunctionTwoValue:"<<endl;
	
	TiXmlDocument xmlDocFunctionTwoValue( szFilename );
	bool loadOkay = xmlDocFunctionTwoValue.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocFunctionTwoValue );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlHandleRoot(0);

	pXmlElement = xmlHandle.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();
		
		const string szFunctionTwoValueElementName = getActualFunctionName();
		if ( szElementName == szFunctionTwoValueElementName ){
			cout<<"The function is correctly named \""<< szFunctionTwoValueElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the function is "<< szElementName <<" and not \""<< szFunctionTwoValueElementName <<"\"."<<endl;
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
	
	//check the first underfunctions
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
			if ( dXmlValue == dValue1 ){
				cout<<"The value of the element is correct."<<endl;
			}else{
				cerr<<"Error: The value of the element should be : "<<
					dValue1 <<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The element text is not a number."<<endl;
			iReturn++;
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No first underfunction handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}

	//check the first underfunctions
	pXmlElement = pXmlElement->NextSiblingElement();
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
			if ( dXmlValue == dValue2 ){
				cout<<"The value of the element is correct."<<endl;
			}else{
				cerr<<"Error: The value of the element should be : "<<
					dValue2 <<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The element text is not a number."<<endl;
			iReturn++;
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No first underfunction handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}


	
	return iReturn;
}



/**
 * This method tests the storeXml() method of the cFunctionTwoValue class.
 * Just storing properties with no underobjects is tested.
 *
 * methods tested:
 * 	- bool storeXml( ostream &stream ) const;
 * 	-  cFunctionTwoValue( const TiXmlElement * pXmlElement, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cUnderFunction * restoreXml( const TiXmlElement * pXmlElement, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, cUnderFunction * pInSuperiorFunction = NULL, cFibElement *pInDefiningFibElement = NULL );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param tUnderFunctionTwoValue the type of the tested cFunctionTwoValue
 * 	is of the type of this object
 * @return the number of errors occured in the test
 */
template <class tUnderFunctionTwoValue> int testStoreXml(
	unsigned long &ulTestphase, const tUnderFunctionTwoValue &function ){

	unsigned int iReturn = 0;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an underfunction with valuefunctions with 1.0 and 2.0"<<endl;
		
	cout<<"list<cFibVariable*> liDefinedVariables;"<<endl;
	list<cFibVariable*> liDefinedVariables;
	list<cFibVariable*> liDefinedVariablesOrg;

	cout<<"cFunctionValue underFunctionValue1( 1.0 );"<<endl;
	cFunctionValue underFunctionValue1( 1.0 );
	cout<<"cFunctionValue underFunctionValue2( 2.0 );"<<endl;
	cFunctionValue underFunctionValue2( 2.0 );

	cout<<"tUnderFunctionTwoValue underFunctionTwoValue1V1_V2( underFunctionValue1, underFunctionValue2 );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue1V1_V2( underFunctionValue1, underFunctionValue2 );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * szXmlFunctionTwoValueFileName = strcat( strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), getActualFunctionName().c_str() ), "1V1_V2.xml" );
	ofstream * pFileUnderFunction = new ofstream( szXmlFunctionTwoValueFileName );
	
	bool bStoreSuccesfull = underFunctionTwoValue1V1_V2.storeXml( *pFileUnderFunction );
	delete pFileUnderFunction;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFunctionTwoValue was stored successfull to the file \""<< szXmlFunctionTwoValueFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFunctionTwoValue to the file \""<< szXmlFunctionTwoValueFileName <<"\" failed."<<endl;
		iReturn++;
	}
	iReturn += testXmlFunctionTwoValue( szXmlFunctionTwoValueFileName, underFunctionValue1.getValue(), underFunctionValue2.getValue() );
	
	TiXmlDocument xmlDocFunctionTwoValue( szFileNameBuffer );
	bool loadOkay = xmlDocFunctionTwoValue.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		cout<<"TiXmlHandle xmlHandle( &xmlDocFunctionTwoValue ); "<<endl;
		TiXmlHandle xmlHandle( &xmlDocFunctionTwoValue );
		cout<<"tUnderFunctionTwoValue underFunctionTwoValue1Loaded( xmlHandle.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		tUnderFunctionTwoValue underFunctionTwoValue1Loaded( xmlHandle.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionTwoValue1Loaded.getType() == getActualFunctionType() ){
		
			cout<<"The loaded underfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded underfunction has the type "<<
				underFunctionTwoValue1Loaded.getType() <<" , but should have the type "<<
				getActualFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionTwoValue1Loaded, "underFunctionTwoValue1Loaded", underFunctionTwoValue1V1_V2, "underFunctionTwoValue1V1_V2" );
		iReturn += testNotConnectedUnderFunction( underFunctionTwoValue1Loaded );
		cout<<"checking: underFunctionTwoValue1Loaded.getFirstUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionTwoValue1Loaded.getFirstUnderFunction(),
			&underFunctionValue1, &underFunctionTwoValue1Loaded, NULL );
		cout<<"checking: underFunctionTwoValue1Loaded.getSecondUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionTwoValue1Loaded.getSecondUnderFunction(),
			&underFunctionValue2, &underFunctionTwoValue1Loaded, NULL );

		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle2( &xmlDocFunctionTwoValue ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDocFunctionTwoValue );
		cout<<"cFunctionTwoValue underFunctionTwoValue1Loaded( xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cUnderFunction * pUnderFunctionTwoValue1Loaded = cUnderFunction::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionTwoValue1Loaded ){
			if ( pUnderFunctionTwoValue1Loaded->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionTwoValue1Loaded->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionTwoValue1Loaded, "pUnderFunctionTwoValue1Loaded", underFunctionTwoValue1V1_V2, "underFunctionTwoValue1V1_V2" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionTwoValue1Loaded );
			cout<<"checking: pUnderFunctionTwoValue1Loaded->getFirstUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionTwoValue*)pUnderFunctionTwoValue1Loaded)->getFirstUnderFunction(),
				&underFunctionValue1, pUnderFunctionTwoValue1Loaded, NULL );
			cout<<"checking: pUnderFunctionTwoValue1Loaded->getSecondUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionTwoValue*)pUnderFunctionTwoValue1Loaded)->getSecondUnderFunction(),
				&underFunctionValue2, pUnderFunctionTwoValue1Loaded, NULL );
			delete pUnderFunctionTwoValue1Loaded;
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
		cout<<"TiXmlHandle xmlHandle3( &xmlDocFunctionTwoValue ); "<<endl;
		TiXmlHandle xmlHandle3( &xmlDocFunctionTwoValue );
		cout<<"tUnderFunctionTwoValue underFunctionTwoValue1LoadedFull( xmlHandle3.FirstChildElement().Element(), "<<
			"outStatus, liDefinedVariables, &underFunctionSup, &rootSimple ); "<<endl;
		tUnderFunctionTwoValue underFunctionTwoValue1LoadedFull( xmlHandle3.FirstChildElement().Element(),
			outStatus, liDefinedVariables, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionTwoValue1LoadedFull.getType() == getActualFunctionType() ){
		
			cout<<"The loaded underfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded underfunction has the type "<<
				underFunctionTwoValue1LoadedFull.getType() <<" , but should have the type "<<
				getActualFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionTwoValue1LoadedFull,
			"underFunctionTwoValue1LoadedFull", underFunctionTwoValue1V1_V2, "underFunctionTwoValue1V1_V2" );
		//check the getDefiningFibElement() methode from cFunctionTwoValue
		if ( underFunctionTwoValue1LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionTwoValue1LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionTwoValue1LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
		if ( underFunctionTwoValue1LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionTwoValue1LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionTwoValue1LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		cout<<"checking: underFunctionTwoValue1LoadedFull.getFirstUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionTwoValue1LoadedFull.getFirstUnderFunction(),
			&underFunctionValue1, &underFunctionTwoValue1LoadedFull, &rootSimple );
		cout<<"checking: underFunctionTwoValue1LoadedFull.getSecondUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionTwoValue1LoadedFull.getSecondUnderFunction(),
			&underFunctionValue2, &underFunctionTwoValue1LoadedFull, &rootSimple );

		
		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle4( &xmlDocFunctionTwoValue ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDocFunctionTwoValue );
		cout<<"cFunctionTwoValue pUnderFunctionTwoValue1LoadedFull = cUnderFunction::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionTwoValue1LoadedFull = cUnderFunction::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionTwoValue1LoadedFull ){
			if ( pUnderFunctionTwoValue1LoadedFull->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionTwoValue1LoadedFull->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionTwoValue1LoadedFull, "pUnderFunctionTwoValue1LoadedFull", underFunctionTwoValue1V1_V2, "underFunctionTwoValue1V1_V2" );
			//check the getDefiningFibElement() methode from cFunctionTwoValue
			if ( pUnderFunctionTwoValue1LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionTwoValue1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionTwoValue1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
			if ( pUnderFunctionTwoValue1LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionTwoValue1LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionTwoValue1LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			cout<<"checking: pUnderFunctionTwoValue1LoadedFull->getFirstUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionTwoValue*)pUnderFunctionTwoValue1LoadedFull)->getFirstUnderFunction(),
				&underFunctionValue1, pUnderFunctionTwoValue1LoadedFull, &rootSimple );
			cout<<"checking: pUnderFunctionTwoValue1LoadedFull->getSecondUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionTwoValue*)pUnderFunctionTwoValue1LoadedFull)->getSecondUnderFunction(),
				&underFunctionValue2, pUnderFunctionTwoValue1LoadedFull, &rootSimple );
			
			delete pUnderFunctionTwoValue1LoadedFull;
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

	cout<<"cFunctionValue underFunctionValue3( 3.0 );"<<endl;
	cFunctionValue underFunctionValue3( 3.0 );
	cout<<"cFunctionValue underFunctionValue4( -4.0 );"<<endl;
	cFunctionValue underFunctionValue4( -4.0 );
	
	cout<<"cRoot rootSimple;"<<endl;
	cRoot rootSimple;
	cout<<"cFunctionValue underFunctionSup1( 5.0 );"<<endl;
	cFunctionValue underFunctionSup1( 5.0 );

	cout<<"tUnderFunctionTwoValue underFunctionTwoValue2( underFunctionValue3, underFunctionValue4, &underFunctionSup1, &rootSimple );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue2( underFunctionValue3, underFunctionValue4, &underFunctionSup1, &rootSimple );
	
	szFileNameBuffer[0] = 0;
	szXmlFunctionTwoValueFileName = strcat( strcat( strcat( szFileNameBuffer, (char*)DIR_OUTPUT ),
		getActualFunctionName().c_str() ), "2.xml" );
	pFileUnderFunction = new ofstream( szXmlFunctionTwoValueFileName );
	
	bStoreSuccesfull = underFunctionTwoValue2.storeXml( *pFileUnderFunction );
	delete pFileUnderFunction;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFunctionTwoValue was stored successfull to the file \""<< szXmlFunctionTwoValueFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFunctionTwoValue to the file \""<< szXmlFunctionTwoValueFileName <<"\" failed."<<endl;
		iReturn++;
	}
	iReturn += testXmlFunctionTwoValue( szXmlFunctionTwoValueFileName, underFunctionValue3.getValue(), underFunctionValue4.getValue() );
	
	TiXmlDocument xmlDocFunctionTwoValue2( szFileNameBuffer );
	loadOkay = xmlDocFunctionTwoValue2.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		cout<<"TiXmlHandle xmlHandle( &xmlDocFunctionTwoValue2 ); "<<endl;
		TiXmlHandle xmlHandle( &xmlDocFunctionTwoValue2 );
		cout<<"tUnderFunctionTwoValue underFunctionTwoValue1Loaded( xmlHandle.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		tUnderFunctionTwoValue underFunctionTwoValue1Loaded( xmlHandle.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionTwoValue1Loaded.getType() == getActualFunctionType() ){
		
			cout<<"The loaded underfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded underfunction has the type "<<
				underFunctionTwoValue1Loaded.getType() <<" , but should have the type "<<
				getActualFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionTwoValue1Loaded, "underFunctionTwoValue1Loaded", underFunctionTwoValue2, "underFunctionTwoValue2" );
		iReturn += testNotConnectedUnderFunction( underFunctionTwoValue1Loaded );
		cout<<"checking: underFunctionTwoValue1Loaded.getFirstUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionTwoValue1Loaded.getFirstUnderFunction(),
			&underFunctionValue3, &underFunctionTwoValue1Loaded, NULL );
		cout<<"checking: underFunctionTwoValue1Loaded.getSecondUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionTwoValue1Loaded.getSecondUnderFunction(),
			&underFunctionValue4, &underFunctionTwoValue1Loaded, NULL );

		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle2( &xmlDocFunctionTwoValue2 ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDocFunctionTwoValue2 );
		cout<<"cFunctionTwoValue underFunctionTwoValue1Loaded( xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cUnderFunction * pUnderFunctionTwoValue1Loaded = cUnderFunction::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionTwoValue1Loaded ){
			if ( pUnderFunctionTwoValue1Loaded->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionTwoValue1Loaded->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			if ( pUnderFunctionTwoValue1Loaded->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionTwoValue1Loaded->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionTwoValue1Loaded, "pUnderFunctionTwoValue1Loaded", underFunctionTwoValue2, "underFunctionTwoValue2" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionTwoValue1Loaded );
			cout<<"checking: pUnderFunctionTwoValue1Loaded->getFirstUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionTwoValue*)pUnderFunctionTwoValue1Loaded)->getFirstUnderFunction(),
				&underFunctionValue3, pUnderFunctionTwoValue1Loaded, NULL );
			cout<<"checking: pUnderFunctionTwoValue1Loaded->getSecondUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionTwoValue*)pUnderFunctionTwoValue1Loaded)->getSecondUnderFunction(),
				&underFunctionValue4, pUnderFunctionTwoValue1Loaded, NULL );
			delete pUnderFunctionTwoValue1Loaded;
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
		cout<<"TiXmlHandle xmlHandle3( &xmlDocFunctionTwoValue2 ); "<<endl;
		TiXmlHandle xmlHandle3( &xmlDocFunctionTwoValue2 );
		cout<<"tUnderFunctionTwoValue underFunctionTwoValue1LoadedFull( xmlHandle3.FirstChildElement().Element(), "<<
			"outStatus, liDefinedVariables, &underFunctionSup, &rootSimple ); "<<endl;
		tUnderFunctionTwoValue underFunctionTwoValue1LoadedFull( xmlHandle3.FirstChildElement().Element(),
			outStatus, liDefinedVariables, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionTwoValue1LoadedFull.getType() == getActualFunctionType() ){
		
			cout<<"The loaded underfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded underfunction has the type "<<
				underFunctionTwoValue1LoadedFull.getType() <<" , but should have the type "<<
				getActualFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionTwoValue1LoadedFull,
			"underFunctionTwoValue1LoadedFull", underFunctionTwoValue2, "underFunctionTwoValue2" );
		//check the getDefiningFibElement() methode from cFunctionTwoValue
		if ( underFunctionTwoValue1LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionTwoValue1LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionTwoValue1LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
		if ( underFunctionTwoValue1LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionTwoValue1LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionTwoValue1LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		cout<<"checking: underFunctionTwoValue1LoadedFull.getFirstUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionTwoValue1LoadedFull.getFirstUnderFunction(),
			&underFunctionValue3, &underFunctionTwoValue1LoadedFull, &rootSimple );
		cout<<"checking: underFunctionTwoValue1LoadedFull.getSecondUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionTwoValue1LoadedFull.getSecondUnderFunction(),
			&underFunctionValue4, &underFunctionTwoValue1LoadedFull, &rootSimple );

		
		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle4( &xmlDocFunctionTwoValue2 ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDocFunctionTwoValue2 );
		cout<<"cFunctionTwoValue pUnderFunctionTwoValue1LoadedFull = cUnderFunction::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionTwoValue1LoadedFull = cUnderFunction::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionTwoValue1LoadedFull ){
			if ( pUnderFunctionTwoValue1LoadedFull->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionTwoValue1LoadedFull->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionTwoValue1LoadedFull, "pUnderFunctionTwoValue1LoadedFull", underFunctionTwoValue2, "underFunctionTwoValue2" );
			//check the getDefiningFibElement() methode from cFunctionTwoValue
			if ( pUnderFunctionTwoValue1LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionTwoValue1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionTwoValue1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
			if ( pUnderFunctionTwoValue1LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionTwoValue1LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionTwoValue1LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			cout<<"checking: pUnderFunctionTwoValue1LoadedFull->getFirstUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionTwoValue*)pUnderFunctionTwoValue1LoadedFull)->getFirstUnderFunction(),
				&underFunctionValue3, pUnderFunctionTwoValue1LoadedFull, &rootSimple );
			cout<<"checking: pUnderFunctionTwoValue1LoadedFull->getSecondUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionTwoValue*)pUnderFunctionTwoValue1LoadedFull)->getSecondUnderFunction(),
				&underFunctionValue4, pUnderFunctionTwoValue1LoadedFull, &rootSimple );
			
			delete pUnderFunctionTwoValue1LoadedFull;
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
 * 	-cFunctionTwoValue( cReadBits & iBitStream, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, const cDomainSingle * pInDomainValue, const cDomainSingle * pInDomainVariable, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cUnderFunction * restore( cReadBits & iBitStream, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, const cDomainSingle * pInValueDomain, const cDomainSingle * pInDomainVariable, cUnderFunction * pInSuperiorFunction = NULL, cFibElement *pInDefiningFibElement = NULL );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param tUnderFunctionTwoValue the type of the tested cFunctionTwoValue
 * 	is of the type of this object
 * @return the number of errors occured in the test
 */
template <class tUnderFunctionTwoValue> int testStore(
	unsigned long &ulTestphase, const tUnderFunctionTwoValue &function ){

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
	cout<<"cFunctionValue underFunctionValue2( 2.0 );"<<endl;
	cFunctionValue underFunctionValue2( 2.0 );

	cout<<"tUnderFunctionTwoValue underFunctionTwoValue1( underFunctionValue1, underFunctionValue2, NULL, &root );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue1( underFunctionValue1, underFunctionValue2, NULL, &root );

	//test get compressed size
	unsigned int uiCompressedSize = 5 + 2 * (2 + 16);
	if ( (unsigned int)(underFunctionTwoValue1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the function is "<<
			underFunctionTwoValue1.getCompressedSize() << ", but should be "<<
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
	cout<<"underFunctionTwoValue1.store( *pFile, cRestBits, cRestBitPosition );"<<endl;
	bool bStoreSuccesfull = underFunctionTwoValue1.store( *pFile, cRestBit, cRestBitPosition );
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
	unsigned char cFunctionTwoValue1[] = { 0x04, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	addCInitiationForActualFunction( cFunctionTwoValue1, 5 );
	iReturn += compareBytsWithFile( szFileNameBuffer, (char*)cFunctionTwoValue1, 5 + 1 );

	char cFunctionName = 0x00;
	ifstream * pFileIn = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
	if ( (pFileIn != NULL) && ( pFileIn->good() ) ){
		
		cReadBits iBitStream( * pFileIn );
		iBitStream.readBits( &cFunctionName, getActualFunctionCInitiationBits() );
		intFib outStatus = 0;
		cout<<"tUnderFunctionTwoValue underFunctionTwoValue1Loaded( iBitStream, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		tUnderFunctionTwoValue underFunctionTwoValue1Loaded( iBitStream, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionTwoValue1Loaded.getType() == getActualFunctionType() ){
		
			cout<<"The loaded underfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded underfunction has the type "<<
				underFunctionTwoValue1Loaded.getType() <<" , but should have the type "<<
				getActualFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionTwoValue1Loaded, "underFunctionTwoValue1Loaded", underFunctionTwoValue1, "underFunctionTwoValue1" );
		iReturn += testNotConnectedUnderFunction( underFunctionTwoValue1Loaded );
		cout<<"checking: underFunctionTwoValue1Loaded.getFirstUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionTwoValue1Loaded.getFirstUnderFunction(),
			&underFunctionValue1, &underFunctionTwoValue1Loaded, NULL );
		cout<<"checking: underFunctionTwoValue1Loaded.getSecondUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionTwoValue1Loaded.getSecondUnderFunction(),
			&underFunctionValue2, &underFunctionTwoValue1Loaded, NULL );

		delete pFileIn;
		ifstream * pFileIn = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
		cReadBits iBitStream2( * pFileIn );
		outStatus = 0;
		cout<<"cFunctionTwoValue pUnderFunctionTwoValue1Loaded = cUnderFunction::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cUnderFunction * pUnderFunctionTwoValue1Loaded = cUnderFunction::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionTwoValue1Loaded ){
			if ( pUnderFunctionTwoValue1Loaded->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionTwoValue1Loaded->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionTwoValue1Loaded, "pUnderFunctionTwoValue1Loaded", underFunctionTwoValue1, "underFunctionTwoValue1" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionTwoValue1Loaded );
			cout<<"checking: pUnderFunctionTwoValue1Loaded->getFirstUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionTwoValue*)pUnderFunctionTwoValue1Loaded)->getFirstUnderFunction(),
				&underFunctionValue1, pUnderFunctionTwoValue1Loaded, NULL );
			cout<<"checking: pUnderFunctionTwoValue1Loaded->getSecondUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionTwoValue*)pUnderFunctionTwoValue1Loaded)->getSecondUnderFunction(),
				&underFunctionValue2, pUnderFunctionTwoValue1Loaded, NULL );
			delete pUnderFunctionTwoValue1Loaded;
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
		
		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
		cReadBits iBitStream3( * pFileIn );
		iBitStream3.readBits( &cFunctionName, getActualFunctionCInitiationBits() );
		outStatus = 0;
		cout<<"tUnderFunctionTwoValue underFunctionTwoValue1LoadedFull( iBitStream3, "<<
			"outStatus, liDefinedVariables, pValueDomain, pVariableDomain, &underFunctionSup, &rootSimple ); "<<endl;
		tUnderFunctionTwoValue underFunctionTwoValue1LoadedFull( iBitStream3,
			outStatus, liDefinedVariables, pValueDomain, pVariableDomain, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionTwoValue1LoadedFull.getType() == getActualFunctionType() ){
		
			cout<<"The loaded underfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded underfunction has the type "<<
				underFunctionTwoValue1LoadedFull.getType() <<" , but should have the type "<<
				getActualFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionTwoValue1LoadedFull,
			"underFunctionTwoValue1LoadedFull", underFunctionTwoValue1, "underFunctionTwoValue1" );
		//check the getDefiningFibElement() methode from cFunctionTwoValue
		if ( underFunctionTwoValue1LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionTwoValue1LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionTwoValue1LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
		if ( underFunctionTwoValue1LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionTwoValue1LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionTwoValue1LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		cout<<"checking: underFunctionTwoValue1LoadedFull.getFirstUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionTwoValue1LoadedFull.getFirstUnderFunction(),
			&underFunctionValue1, &underFunctionTwoValue1LoadedFull, &rootSimple );
		cout<<"checking: underFunctionTwoValue1LoadedFull.getSecondUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionTwoValue1LoadedFull.getSecondUnderFunction(),
			&underFunctionValue2, &underFunctionTwoValue1LoadedFull, &rootSimple );
		
		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
		cReadBits iBitStream4( * pFileIn );
		outStatus = 0;
		cout<<"cFunctionTwoValue pUnderFunctionTwoValue1LoadedFull = cUnderFunction::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionTwoValue1LoadedFull = cUnderFunction::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionTwoValue1LoadedFull ){
			if ( pUnderFunctionTwoValue1LoadedFull->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionTwoValue1LoadedFull->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionTwoValue1LoadedFull, "pUnderFunctionTwoValue1LoadedFull", underFunctionTwoValue1, "underFunctionTwoValue1" );
			//check the getDefiningFibElement() methode from cFunctionTwoValue
			if ( pUnderFunctionTwoValue1LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionTwoValue1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionTwoValue1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
			if ( pUnderFunctionTwoValue1LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionTwoValue1LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionTwoValue1LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			cout<<"checking: pUnderFunctionTwoValue1LoadedFull->getFirstUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionTwoValue*)pUnderFunctionTwoValue1LoadedFull)->getFirstUnderFunction(),
				&underFunctionValue1, pUnderFunctionTwoValue1LoadedFull, &rootSimple );
			cout<<"checking: pUnderFunctionTwoValue1LoadedFull->getSecondUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionTwoValue*)pUnderFunctionTwoValue1LoadedFull)->getSecondUnderFunction(),
				&underFunctionValue2, pUnderFunctionTwoValue1LoadedFull, &rootSimple );
			
			delete pUnderFunctionTwoValue1LoadedFull;
		}else{
			cerr<<"Error: No underfunction loaded ."<<endl;
			iReturn++;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: The defined variables wher changed ."<<endl;
			iReturn++;
		}
		delete pFileIn;
	
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
	cout<<"cFunctionValue underFunctionValue4( 4.0 );"<<endl;
	cFunctionValue underFunctionValue4( 4.0 );

	cout<<"tUnderFunctionTwoValue underFunctionTwoValue2( underFunctionValue3, underFunctionValue4, NULL, &root );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue2( underFunctionValue3, underFunctionValue4, NULL, &root );
	
	//test get compressed size
	uiCompressedSize = 5 + 2 * (2 + 6);
	if ( (unsigned int)(underFunctionTwoValue2.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the function is "<<
			underFunctionTwoValue2.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( strcat( szFileNameBuffer, (char*)DIR_OUTPUT ),
		getActualFunctionName().c_str() ), "2.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0x00;
	cRestBitPosition = 0;
	cout<<"underFunctionTwoValue2.store( *pFile, cRestBit, cRestBitPosition ); "<<endl;
	bStoreSuccesfull = underFunctionTwoValue2.store( *pFile, cRestBit, cRestBitPosition );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	unsigned char szUnderFunctionTwoValue2[] = { 0x0C, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00 };
	addCInitiationForActualFunction( szUnderFunctionTwoValue2, 2 );
	iReturn += compareBytsWithFile( szFileNameBuffer, (char*)szUnderFunctionTwoValue2, (uiCompressedSize - 1) / 8 + 1 );
	
	ucRestBit = cRestBit;
	ucRestBitCorrect = szUnderFunctionTwoValue2[ (uiCompressedSize) / 8 ];
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

	pFileIn = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
	if ( (pFileIn != NULL) && ( pFileIn->good() ) ){
		
		cReadBits iBitStream( * pFileIn );
		iBitStream.readBits( &cFunctionName, getActualFunctionCInitiationBits() );
		intFib outStatus = 0;
		cout<<"tUnderFunctionTwoValue underFunctionTwoValue2Loaded( iBitStream, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		tUnderFunctionTwoValue underFunctionTwoValue2Loaded( iBitStream, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionTwoValue2Loaded.getType() == getActualFunctionType() ){
		
			cout<<"The loaded underfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded underfunction has the type "<<
				underFunctionTwoValue2Loaded.getType() <<" , but should have the type "<<
				getActualFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionTwoValue2Loaded, "underFunctionTwoValue2Loaded", underFunctionTwoValue2, "underFunctionTwoValue2" );
		iReturn += testNotConnectedUnderFunction( underFunctionTwoValue2Loaded );
		cout<<"checking: underFunctionTwoValue2Loaded.getFirstUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionTwoValue2Loaded.getFirstUnderFunction(),
			&underFunctionValue3, &underFunctionTwoValue2Loaded, NULL );
		cout<<"checking: underFunctionTwoValue2Loaded.getSecondUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionTwoValue2Loaded.getSecondUnderFunction(),
			&underFunctionValue4, &underFunctionTwoValue2Loaded, NULL );

		delete pFileIn;
		ifstream * pFileIn = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
		cReadBits iBitStream2( * pFileIn );
		outStatus = 0;
		cout<<"cFunctionTwoValue pUnderFunctionTwoValue2Loaded = cUnderFunction::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cUnderFunction * pUnderFunctionTwoValue2Loaded = cUnderFunction::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionTwoValue2Loaded ){
			if ( pUnderFunctionTwoValue2Loaded->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionTwoValue2Loaded->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionTwoValue2Loaded, "pUnderFunctionTwoValue2Loaded", underFunctionTwoValue2, "underFunctionTwoValue2" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionTwoValue2Loaded );
			cout<<"checking: pUnderFunctionTwoValue2Loaded->getFirstUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionTwoValue*)pUnderFunctionTwoValue2Loaded)->getFirstUnderFunction(),
				&underFunctionValue3, pUnderFunctionTwoValue2Loaded, NULL );
			cout<<"checking: pUnderFunctionTwoValue2Loaded->getSecondUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionTwoValue*)pUnderFunctionTwoValue2Loaded)->getSecondUnderFunction(),
				&underFunctionValue4, pUnderFunctionTwoValue2Loaded, NULL );
			delete pUnderFunctionTwoValue2Loaded;
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
		
		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
		cReadBits iBitStream3( * pFileIn );
		iBitStream3.readBits( &cFunctionName, getActualFunctionCInitiationBits() );
		outStatus = 0;
		cout<<"tUnderFunctionTwoValue underFunctionTwoValue2LoadedFull( iBitStream3, "<<
			"outStatus, liDefinedVariables, pValueDomain, pVariableDomain, &underFunctionSup, &rootSimple ); "<<endl;
		tUnderFunctionTwoValue underFunctionTwoValue2LoadedFull( iBitStream3,
			outStatus, liDefinedVariables, pValueDomain, pVariableDomain, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionTwoValue2LoadedFull.getType() == getActualFunctionType() ){
		
			cout<<"The loaded underfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded underfunction has the type "<<
				underFunctionTwoValue2LoadedFull.getType() <<" , but should have the type "<<
				getActualFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionTwoValue2LoadedFull,
			"underFunctionTwoValue2LoadedFull", underFunctionTwoValue2, "underFunctionTwoValue2" );
		//check the getDefiningFibElement() methode from cFunctionTwoValue
		if ( underFunctionTwoValue2LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionTwoValue2LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionTwoValue2LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
		if ( underFunctionTwoValue2LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionTwoValue2LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionTwoValue2LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		cout<<"checking: underFunctionTwoValue2LoadedFull.getFirstUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionTwoValue2LoadedFull.getFirstUnderFunction(),
			&underFunctionValue3, &underFunctionTwoValue2LoadedFull, &rootSimple );
		cout<<"checking: underFunctionTwoValue2LoadedFull.getSecondUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionTwoValue2LoadedFull.getSecondUnderFunction(),
			&underFunctionValue4, &underFunctionTwoValue2LoadedFull, &rootSimple );
		
		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
		cReadBits iBitStream4( * pFileIn );
		outStatus = 0;
		cout<<"cFunctionTwoValue pUnderFunctionTwoValue2LoadedFull = cUnderFunction::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionTwoValue2LoadedFull = cUnderFunction::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionTwoValue2LoadedFull ){
			if ( pUnderFunctionTwoValue2LoadedFull->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionTwoValue2LoadedFull->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionTwoValue2LoadedFull, "pUnderFunctionTwoValue2LoadedFull", underFunctionTwoValue2, "underFunctionTwoValue2" );
			//check the getDefiningFibElement() methode from cFunctionTwoValue
			if ( pUnderFunctionTwoValue2LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionTwoValue2LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionTwoValue2LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
			if ( pUnderFunctionTwoValue2LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionTwoValue2LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionTwoValue2LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			cout<<"checking: pUnderFunctionTwoValue2LoadedFull->getFirstUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionTwoValue*)pUnderFunctionTwoValue2LoadedFull)->getFirstUnderFunction(),
				&underFunctionValue3, pUnderFunctionTwoValue2LoadedFull, &rootSimple );
			cout<<"checking: pUnderFunctionTwoValue2LoadedFull->getSecondUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionTwoValue*)pUnderFunctionTwoValue2LoadedFull)->getSecondUnderFunction(),
				&underFunctionValue4, pUnderFunctionTwoValue2LoadedFull, &rootSimple );
			
			delete pUnderFunctionTwoValue2LoadedFull;
		}else{
			cerr<<"Error: No underfunction loaded ."<<endl;
			iReturn++;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: The defined variables wher changed ."<<endl;
			iReturn++;
		}
		delete pFileIn;
	
	}else{
		cerr<<"Error: Failed to load file \""<< szFileNameBuffer <<"\""<<endl;
		iReturn++;
	}


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with given restbit"<<endl;

	cout<<"tUnderFunctionTwoValue underFunctionTwoValue3( underFunctionValue3, underFunctionValue4, NULL, &root );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue3( underFunctionValue3, underFunctionValue4, NULL, &root );
	
	//test get compressed size
	uiCompressedSize = 5 + 2 * (2 + 6);
	if ( (unsigned int)(underFunctionTwoValue3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the function is "<<
			underFunctionTwoValue3.getCompressedSize() << ", but should be "<<
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
	cout<<"underFunctionTwoValue3.store( *pFile, cRestBit, cRestBitPosition ); "<<endl;
	bStoreSuccesfull = underFunctionTwoValue3.store( *pFile, cRestBit, cRestBitPosition );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	unsigned char szUnderFunctionTwoValue3[] = { 0x0C, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00 };
	addCInitiationForActualFunction( szUnderFunctionTwoValue3, 2, cRestBitPositionOrginal );
	szUnderFunctionTwoValue3[ 0 ] = szUnderFunctionTwoValue3[ 0 ] | 0x01;
	iReturn += compareBytsWithFile( szFileNameBuffer, (char*)szUnderFunctionTwoValue3, (uiCompressedSize + cRestBitPositionOrginal) / 8 + 1 );
	
	ucRestBit = cRestBit;
	ucRestBitCorrect = szUnderFunctionTwoValue3[ (uiCompressedSize + cRestBitPositionOrginal ) / 8 ];
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

	pFileIn = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
	if ( (pFileIn != NULL) && ( pFileIn->good() ) ){
		
		cReadBits iBitStream( * pFileIn );
		long cBuffer;
		iBitStream.readBits( cBuffer, ((unsigned int)(cRestBitPositionOrginal + getActualFunctionCInitiationBits())) );
		intFib outStatus = 0;
		cout<<"tUnderFunctionTwoValue underFunctionTwoValue3Loaded( iBitStream, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		tUnderFunctionTwoValue underFunctionTwoValue3Loaded( iBitStream, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionTwoValue3Loaded.getType() == getActualFunctionType() ){
		
			cout<<"The loaded underfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded underfunction has the type "<<
				underFunctionTwoValue3Loaded.getType() <<" , but should have the type "<<
				getActualFunctionType() <<" ."<<endl;
			iReturn++;
		}
		int iErrorsEqual = testCompareTwoEqualObjects( underFunctionTwoValue3Loaded, "underFunctionTwoValue3Loaded", underFunctionTwoValue3, "underFunctionTwoValue3" );
		iReturn += testNotConnectedUnderFunction( underFunctionTwoValue3Loaded );
		if ( iErrorsEqual != 0 ){
			cerr<<"Error: Loaded underfunction not equal (value="<<
				underFunctionTwoValue3Loaded.getValue() <<")."<<endl;
		}
		iReturn += iErrorsEqual;
		cout<<"checking: underFunctionTwoValue3Loaded.getFirstUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionTwoValue3Loaded.getFirstUnderFunction(),
			&underFunctionValue3, &underFunctionTwoValue3Loaded, NULL );
		cout<<"checking: underFunctionTwoValue3Loaded.getSecondUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionTwoValue3Loaded.getSecondUnderFunction(),
			&underFunctionValue4, &underFunctionTwoValue3Loaded, NULL );

		delete pFileIn;
		ifstream * pFileIn = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
		cReadBits iBitStream2( * pFileIn );
		iBitStream2.readBits( cBuffer, ((unsigned int)(cRestBitPositionOrginal)) );
		outStatus = 0;
		cout<<"cFunctionTwoValue pUnderFunctionTwoValue3Loaded = cUnderFunction::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cUnderFunction * pUnderFunctionTwoValue3Loaded = cUnderFunction::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionTwoValue3Loaded ){
			if ( pUnderFunctionTwoValue3Loaded->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionTwoValue3Loaded->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			iErrorsEqual = testCompareTwoEqualObjects( * pUnderFunctionTwoValue3Loaded, "pUnderFunctionTwoValue3Loaded", underFunctionTwoValue3, "underFunctionTwoValue3" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionTwoValue3Loaded );
			if ( iErrorsEqual != 0 ){
				cerr<<"Error: Loaded underfunction not equal (value="<<
					underFunctionTwoValue3Loaded.getValue() <<")."<<endl;
			}
			iReturn += iErrorsEqual;
			cout<<"checking: pUnderFunctionTwoValue3Loaded->getFirstUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionTwoValue*)pUnderFunctionTwoValue3Loaded)->getFirstUnderFunction(),
				&underFunctionValue3, pUnderFunctionTwoValue3Loaded, NULL );
			cout<<"checking: pUnderFunctionTwoValue3Loaded->getSecondUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionTwoValue*)pUnderFunctionTwoValue3Loaded)->getSecondUnderFunction(),
				&underFunctionValue4, pUnderFunctionTwoValue3Loaded, NULL );
			delete pUnderFunctionTwoValue3Loaded;
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
		
		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
		cReadBits iBitStream3( * pFileIn );
		iBitStream3.readBits( cBuffer, ((unsigned int)(cRestBitPositionOrginal + getActualFunctionCInitiationBits())) );
		outStatus = 0;
		cout<<"tUnderFunctionTwoValue underFunctionTwoValue3LoadedFull( iBitStream3, "<<
			"outStatus, liDefinedVariables, pValueDomain, pVariableDomain, &underFunctionSup, &rootSimple ); "<<endl;
		tUnderFunctionTwoValue underFunctionTwoValue3LoadedFull( iBitStream3,
			outStatus, liDefinedVariables, pValueDomain, pVariableDomain, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionTwoValue3LoadedFull.getType() == getActualFunctionType() ){
		
			cout<<"The loaded underfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded underfunction has the type "<<
				underFunctionTwoValue3LoadedFull.getType() <<" , but should have the type "<<
				getActualFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionTwoValue3LoadedFull,
			"underFunctionTwoValue3LoadedFull", underFunctionTwoValue3, "underFunctionTwoValue3" );
		//check the getDefiningFibElement() methode from cFunctionTwoValue
		if ( underFunctionTwoValue3LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionTwoValue3LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionTwoValue3LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
		if ( underFunctionTwoValue3LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionTwoValue3LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionTwoValue3LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		cout<<"checking: underFunctionTwoValue3LoadedFull.getFirstUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionTwoValue3LoadedFull.getFirstUnderFunction(),
			&underFunctionValue3, &underFunctionTwoValue3LoadedFull, &rootSimple );
		cout<<"checking: underFunctionTwoValue3LoadedFull.getSecondUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionTwoValue3LoadedFull.getSecondUnderFunction(),
			&underFunctionValue4, &underFunctionTwoValue3LoadedFull, &rootSimple );
		
		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
		cReadBits iBitStream4( * pFileIn );
		iBitStream4.readBits( cBuffer, ((unsigned int)(cRestBitPositionOrginal)) );
		outStatus = 0;
		cout<<"cFunctionTwoValue pUnderFunctionTwoValue3LoadedFull = cUnderFunction::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionTwoValue3LoadedFull = cUnderFunction::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionTwoValue3LoadedFull ){
			if ( pUnderFunctionTwoValue3LoadedFull->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionTwoValue3LoadedFull->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionTwoValue3LoadedFull, "pUnderFunctionTwoValue3LoadedFull", underFunctionTwoValue3, "underFunctionTwoValue3" );
			//check the getDefiningFibElement() methode from cFunctionTwoValue
			if ( pUnderFunctionTwoValue3LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionTwoValue3LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionTwoValue3LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
			if ( pUnderFunctionTwoValue3LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionTwoValue3LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionTwoValue3LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			cout<<"checking: pUnderFunctionTwoValue3LoadedFull->getFirstUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionTwoValue*)pUnderFunctionTwoValue3LoadedFull)->getFirstUnderFunction(),
				&underFunctionValue3, pUnderFunctionTwoValue3LoadedFull, &rootSimple );
			cout<<"checking: pUnderFunctionTwoValue3LoadedFull->getSecondUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionTwoValue*)pUnderFunctionTwoValue3LoadedFull)->getSecondUnderFunction(),
				&underFunctionValue4, pUnderFunctionTwoValue3LoadedFull, &rootSimple );
			delete pUnderFunctionTwoValue3LoadedFull;
		}else{
			cerr<<"Error: No underfunction loaded ."<<endl;
			iReturn++;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: The defined variables wher changed ."<<endl;
			iReturn++;
		}
		delete pFileIn;
	
	}else{
		cerr<<"Error: Failed to load file \""<< szFileNameBuffer <<"\""<<endl;
		iReturn++;
	}


	delete pVariableDomain;
	delete pValueDomain;

	return iReturn;
}



/**
 * This method tests the variable methods of the cFunctionTwoValue class.
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
 * @param tUnderFunctionTwoValue the type of the tested cFunctionTwoValue
 * 	is of the type of this object
 * @return the number of erros occured in the test
 */
template <class tUnderFunctionTwoValue> int testVariable(
	unsigned long &ulTestphase, const tUnderFunctionTwoValue &function ){

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

	cout<<"tUnderFunctionTwoValue underFunctionTwoValue1( underFunctionVariable1, underFunctionVariable2 );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue1( underFunctionVariable1, underFunctionVariable2 );
	set<cFibVariable*> setCorrectUsedVariables;
	setCorrectUsedVariables.insert( pVariable1 );
	setCorrectUsedVariables.insert( pVariable2 );
	
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable1 )"<<endl;
	if ( underFunctionTwoValue1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable2 )"<<endl;
	if ( underFunctionTwoValue1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable3 )"<<endl;
	if ( ! underFunctionTwoValue1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionTwoValue1.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = underFunctionTwoValue1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the getValue() method"<<endl;

	//check the getValue() methode from cFunctionTwoValue
	cout<<"pVariable1->setValue( 2.0 );"<<endl;
	pVariable1->setValue( 2.0 );
	cout<<"pVariable1->setValue( 5.0 );"<<endl;
	pVariable1->setValue( 5.0 );
	double dValue = getActualFunctionValue( underFunctionVariable1.getValue(), underFunctionVariable2.getValue() );
	cout<<"underFunctionTwoValue1.getValue()"<<endl;
	if ( isEqual( underFunctionTwoValue1.getValue(), dValue ) ){
	
		cout<<"The the value "<< underFunctionTwoValue1.getValue() <<
			" was correctly returned by the underfunction. "<<endl;
	}else{
		cerr<<"Error: The the value "<< underFunctionTwoValue1.getValue() <<
			" was returned by the underfunction, but it should be "<< dValue <<" . "<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the replaceVariable() method"<<endl;
	
	cout<<"underFunctionTwoValue1.replaceVariable( pVariable2, pVariable3 );"<<endl;
	bool bVariableReplaced = underFunctionTwoValue1.replaceVariable( pVariable2, pVariable3 );
	setCorrectUsedVariables.erase( pVariable2 );
	setCorrectUsedVariables.insert( pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable1 )"<<endl;
	if ( underFunctionTwoValue1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable3 )"<<endl;
	if ( underFunctionTwoValue1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable2 )"<<endl;
	if ( ! underFunctionTwoValue1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionTwoValue1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionTwoValue1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<endl<<"underFunctionTwoValue1.replaceVariable( pVariable2, pVariable4 );"<<endl;
	bVariableReplaced = underFunctionTwoValue1.replaceVariable( pVariable2, pVariable4 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable3 )"<<endl;
	if ( underFunctionTwoValue1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable4 )"<<endl;
	if ( ! underFunctionTwoValue1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionTwoValue1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionTwoValue1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<endl<<"underFunctionTwoValue1.replaceVariable( pVariable3, pVariable3 );"<<endl;
	bVariableReplaced = underFunctionTwoValue1.replaceVariable( pVariable3, pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable1 )"<<endl;
	if ( underFunctionTwoValue1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable3 )"<<endl;
	if ( underFunctionTwoValue1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable4 )"<<endl;
	if ( ! underFunctionTwoValue1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionTwoValue1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionTwoValue1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<endl<<"underFunctionTwoValue1.replaceVariable( NULL, pVariable1 );"<<endl;
	bVariableReplaced = underFunctionTwoValue1.replaceVariable( NULL, pVariable1 );
	if ( ! bVariableReplaced ){
	
		cout<<"The variable was correctly not replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was replaced. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable1 )"<<endl;
	if ( underFunctionTwoValue1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable3 )"<<endl;
	if ( underFunctionTwoValue1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable4 )"<<endl;
	if ( ! underFunctionTwoValue1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionTwoValue1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionTwoValue1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<endl<<"underFunctionTwoValue1.replaceVariable( pVariable3, NULL );"<<endl;
	bVariableReplaced = underFunctionTwoValue1.replaceVariable( pVariable3, NULL );
	if ( ! bVariableReplaced ){
	
		cout<<"The variable was correctly not replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was replaced. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable1 )"<<endl;
	if ( underFunctionTwoValue1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable3 )"<<endl;
	if ( underFunctionTwoValue1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable4 )"<<endl;
	if ( ! underFunctionTwoValue1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionTwoValue1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionTwoValue1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<endl<<"underFunctionTwoValue1.replaceVariable( pVariable1, pVariable3 );"<<endl;
	bVariableReplaced = underFunctionTwoValue1.replaceVariable( pVariable1, pVariable3 );
	setCorrectUsedVariables.erase( pVariable1 );
	setCorrectUsedVariables.insert( pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable3 )"<<endl;
	if ( underFunctionTwoValue1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! underFunctionTwoValue1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable4 )"<<endl;
	if ( ! underFunctionTwoValue1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionTwoValue1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionTwoValue1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<endl<<"underFunctionTwoValue1.replaceVariable( pVariable3, pVariable4 );"<<endl;
	bVariableReplaced = underFunctionTwoValue1.replaceVariable( pVariable3, pVariable4 );
	setCorrectUsedVariables.erase( pVariable3 );
	setCorrectUsedVariables.insert( pVariable4 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable4 )"<<endl;
	if ( underFunctionTwoValue1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable4 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable4 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! underFunctionTwoValue1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionTwoValue
	cout<<"underFunctionTwoValue1.isUsedVariable( pVariable3 )"<<endl;
	if ( ! underFunctionTwoValue1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionTwoValue1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionTwoValue1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests the defining fib -element methods of the cFunctionTwoValue class.
 *
 * methods tested:
 * 	- void setDefiningFibElement( cFibElement *fibElement=NULL, bool bCheckDomains=true );
 * 	- cFibElement * getDefiningFibElement() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param tUnderFunctionTwoValue the type of the tested cFunctionTwoValue
 * 	is of the type of this object
 * @return the number of erros occured in the test
 */
template <class tUnderFunctionTwoValue> int testDefiningFibElement(
	unsigned long &ulTestphase, const tUnderFunctionTwoValue &function ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for the defining fib -element"<<endl;
	
	cout<<"cFunctionValue underFunctionValue1( 8.0 );"<<endl;
	cFunctionValue underFunctionValue1( 8.0 );
	cout<<"cFunctionValue underFunctionValue2( -1.0 );"<<endl;
	cFunctionValue underFunctionValue2( -1.0 );

	cout<<"tUnderFunctionTwoValue underFunctionTwoValue1( underFunctionValue1, underFunctionValue2 );"<<endl;
	tUnderFunctionTwoValue underFunctionTwoValue1( underFunctionValue1, underFunctionValue2 );
	
	cout<<"tUnderFunctionTwoValue ufValueCorrect1( underFunctionValue1, underFunctionValue2 );"<<endl;
	tUnderFunctionTwoValue ufValueCorrect1( underFunctionValue1, underFunctionValue2 );

	cFibElement * pDefiningFibElement = NULL;
	//check the getDefiningFibElement() methode from cFunctionTwoValue
	cout<<"checking: underFunctionTwoValue1"<<endl;
	iReturn += checkUnderFunction( &underFunctionTwoValue1,
		&ufValueCorrect1, NULL, pDefiningFibElement );
	cout<<"checking: underFunctionTwoValue1.getFirstUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue1.getFirstUnderFunction(),
		&underFunctionValue1, &underFunctionTwoValue1, pDefiningFibElement );
	cout<<"checking: underFunctionTwoValue1.getSecondUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue1.getSecondUnderFunction(),
		&underFunctionValue2, &underFunctionTwoValue1, pDefiningFibElement );

	cPoint point1;
	cout<<"underFunctionTwoValue1.setDefiningFibElement( &point1 );"<<endl;
	underFunctionTwoValue1.setDefiningFibElement( &point1 );
	pDefiningFibElement = &point1;
	cout<<"checking: underFunctionTwoValue1"<<endl;
	iReturn += checkUnderFunction( &underFunctionTwoValue1,
		&ufValueCorrect1, NULL, pDefiningFibElement );
	cout<<"checking: underFunctionTwoValue1.getFirstUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue1.getFirstUnderFunction(),
		&underFunctionValue1, &underFunctionTwoValue1, pDefiningFibElement );
	cout<<"checking: underFunctionTwoValue1.getSecondUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue1.getSecondUnderFunction(),
		&underFunctionValue2, &underFunctionTwoValue1, pDefiningFibElement );
	
	cout<<"underFunctionTwoValue1.setDefiningFibElement( &point1 );"<<endl;
	underFunctionTwoValue1.setDefiningFibElement( &point1 );
	pDefiningFibElement = &point1;
	cout<<"checking: underFunctionTwoValue1"<<endl;
	iReturn += checkUnderFunction( &underFunctionTwoValue1,
		&ufValueCorrect1, NULL, pDefiningFibElement );
	cout<<"checking: underFunctionTwoValue1.getFirstUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue1.getFirstUnderFunction(),
		&underFunctionValue1, &underFunctionTwoValue1, pDefiningFibElement );
	cout<<"checking: underFunctionTwoValue1.getSecondUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue1.getSecondUnderFunction(),
		&underFunctionValue2, &underFunctionTwoValue1, pDefiningFibElement );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for the defining fib -element with domains set"<<endl;
	
	cout<<"cRoot root;"<<endl;
	cRoot root;
	
	cout<<"cTypeUnderFunction testTypeUnderFunction;"<<endl;
	cTypeUnderFunction testTypeUnderFunction;
	
	//create vector domain with two elements
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

	cout<<"underFunctionTwoValue1.setDefiningFibElement( &root, false );"<<endl;
	underFunctionTwoValue1.setDefiningFibElement( &root, false );
	pDefiningFibElement = &root;
	cout<<"checking: underFunctionTwoValue1"<<endl;
	iReturn += checkUnderFunction( &underFunctionTwoValue1,
		&ufValueCorrect1, NULL, pDefiningFibElement );
	cout<<"checking: underFunctionTwoValue1.getFirstUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue1.getFirstUnderFunction(),
		&underFunctionValue1, &underFunctionTwoValue1, pDefiningFibElement );
	cout<<"checking: underFunctionTwoValue1.getSecondUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue1.getSecondUnderFunction(),
		&underFunctionValue2, &underFunctionTwoValue1, pDefiningFibElement );


	cout<<"cFunctionValue underFunctionValue7( 7.0 );"<<endl;
	cFunctionValue underFunctionValue7( 7.0 );
	cout<<"cFunctionValue underFunctionValue0( 0.0 );"<<endl;
	cFunctionValue underFunctionValue0( 0.0 );

	cout<<"tUnderFunctionTwoValue ufValueCorrect2( underFunctionValue7, underFunctionValue0 );"<<endl;
	tUnderFunctionTwoValue ufValueCorrect2( underFunctionValue7, underFunctionValue0 );

	cout<<"underFunctionTwoValue1.setDefiningFibElement( &root, true );"<<endl;
	underFunctionTwoValue1.setDefiningFibElement( &root, true );
	pDefiningFibElement = &root;
	cout<<"checking: underFunctionTwoValue1"<<endl;
	iReturn += checkUnderFunction( &underFunctionTwoValue1,
		&ufValueCorrect2, NULL, pDefiningFibElement );
	cout<<"checking: underFunctionTwoValue1.getFirstUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue1.getFirstUnderFunction(),
		&underFunctionValue7, &underFunctionTwoValue1, pDefiningFibElement );
	cout<<"checking: underFunctionTwoValue1.getSecondUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionTwoValue1.getSecondUnderFunction(),
		&underFunctionValue0, &underFunctionTwoValue1, pDefiningFibElement );

	
	return iReturn;
}



/**
 * This method tests the getValue() method of the cFunctionTwoValue class.
 *
 * methods tested:
 * 	- void getValue();
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param tUnderFunctionTwoValue the type of the tested cFunctionTwoValue
 * 	is of the type of this object
 * @return the number of erros occured in the test
 */
template <class tUnderFunctionTwoValue> int testValue(
	unsigned long &ulTestphase, const tUnderFunctionTwoValue &function ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the method getValue() method on some fixed values"<<endl;
	
	//test getValue() an standardvalues
	list< pair< doubleFib, doubleFib > > liStandardValues;
	liStandardValues.push_back( make_pair( 0.0, 0.0 ) );
	liStandardValues.push_back( make_pair( 1.0, 0.0 ) );
	liStandardValues.push_back( make_pair( 0.0, 1.0 ) );
	liStandardValues.push_back( make_pair( 1.0, 1.0 ) );
	liStandardValues.push_back( make_pair( 1000.0, 1.0 ) );
	liStandardValues.push_back( make_pair( 1.0, 1000.0 ) );
	liStandardValues.push_back( make_pair( 1000.0, 1000.0 ) );
	liStandardValues.push_back( make_pair( 0.0001, 1.0 ) );
	liStandardValues.push_back( make_pair( 1.0, 0.0001 ) );
	liStandardValues.push_back( make_pair( 0.0001, 0.0001 ) );
	liStandardValues.push_back( make_pair( -1.0, 0.0 ) );
	liStandardValues.push_back( make_pair( 0.0, -1.0 ) );
	liStandardValues.push_back( make_pair( -1.0, -1.0 ) );
	liStandardValues.push_back( make_pair( -1000.0, -1.0 ) );
	liStandardValues.push_back( make_pair( -1.0, -1000.0 ) );
	liStandardValues.push_back( make_pair( -1000.0, -1000.0 ) );
	liStandardValues.push_back( make_pair( -0.0001, -1.0 ) );
	liStandardValues.push_back( make_pair( -1.0, -0.0001 ) );
	liStandardValues.push_back( make_pair( -0.0001, -0.0001 ) );
	
	for ( list< pair< doubleFib, doubleFib > >::iterator
			itrUf = liStandardValues.begin(); itrUf != liStandardValues.end();
			itrUf++ ){
		
		cFunctionValue ufunction1( itrUf->first );
		cFunctionValue ufunction2( itrUf->second );
		doubleFib dResult = getActualFunctionValue( itrUf->first, itrUf->second );
		
		tUnderFunctionTwoValue ufTwoValue( ufunction1, ufunction2 );
		
		if ( isEqual( dResult, ufTwoValue.getValue() ) ){
		
			cout<<"The result from "<< itrUf->first <<" and "<< itrUf->second <<
				" is correctly "<< ufTwoValue.getValue() <<" . "<<endl;
		}else{
			cerr<<"Error: The result from "<< itrUf->first <<" and "<< itrUf->second <<
				" is "<< ufTwoValue.getValue() <<" , but should be "<< dResult <<" . "<<endl;
			iReturn++;
		}
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the method getValue() method on some random values"<<endl;
	//test getValue() on random values
	
	for ( unsigned int iteration = 0; iteration <= 1000; iteration++ ){
		
		doubleFib dValue1 = (double)(rand() % 2000000 - 1000000) / 1000.0;
		doubleFib dValue2 = (double)(rand() % 2000000 - 1000000) / 1000.0;
		cFunctionValue ufunction1( dValue1 );
		cFunctionValue ufunction2( dValue2);
		doubleFib dResult = getActualFunctionValue( dValue1, dValue2 );
		
		tUnderFunctionTwoValue ufTwoValue( ufunction1, ufunction2 );
		
		if ( isEqual( dResult, ufTwoValue.getValue() ) ){
		
			cout<<"The result from "<< dValue1 <<" and "<< dValue2 <<
				" is correctly "<< ufTwoValue.getValue() <<" . "<<endl;
		}else{
			cerr<<"Error: The result from "<< dValue1 <<" and "<< dValue2 <<
				" is "<< ufTwoValue.getValue() <<" , but should be "<< dResult <<" . "<<endl;
			iReturn++;
		}
	}
	
	return iReturn;
}











