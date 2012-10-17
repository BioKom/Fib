/**
 * @file tConditionComparison
 * file name: tConditionComparison.cpp
 * @author Betti Oesterholz
 * @date 15.05.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the child class of class cConditionComparison.
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
 * This file contains the test for the class cConditionComparison, which
 * represents a true condition.
 *
 *
 * What's tested of class cConditionComparison:
 * 	- cConditionComparison( cUnderFunction * pInFirstSubFunction, cUnderFunction * pInSecondSubFunction, cCondition * pInSuperiorCondition, cFibElement * pInDefiningFibElement )
 * 	- cConditionComparison( const cUnderFunction & inFirstSubFunction, const cUnderFunction & inSecondSubFunction, cCondition * pInSuperiorCondition = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cConditionComparison( const cConditionComparison & condition, cCondition * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- ~cConditionComparison();
 * 	- bool isValid() const;
 * 	- bool isUsedVariable( const cFibVariable * variable ) const;
 * 	- set<cFibVariable*> getUsedVariables();
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- bool getValue() const;
 * 	- unsignedIntFib getNumberOfConditions() const;
 * 	- unsignedIntFib getNumberOfUnderFunctions() const;
 * 	- cFibElement * getDefiningFibElement() const;
 * 	- cCondition * getSuperiorCondition() const;
 * 	- void setDefiningFibElement( cFibElement *fibElement=NULL, bool bCheckDomains=true );
 * 	- unsignedLongFib getTimeNeed( unsignedLongFib lMaxTime=0 ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- cCondition * restoreXml( const TiXmlElement * pXmlElement, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, cCondition * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- bool storeXml( ostream &stream ) const;
 * 	- cCondition * restore( cReadBits & iBitStream, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, const cDomainSingle * pInValueDomain, const cDomainSingle * pInDomainVariable, cCondition * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- bool store( ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const;
 * 	- unsignedIntFib getType() const;
 * 	- string getConditionName() const;
 * 	- bool equal( const cCondition &condition ) const;
 * 	- bool operator==( const cCondition &condition ) const;
 * 	- bool operator!=( const cCondition &condition ) const;
 * 	- cConditionComparison * clone( cCondition * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL) const;
 * 	- cUnderFunction * getFirstSubFunction();
 * 	- bool setFirstSubFunction( cUnderFunction * pInSubFunction, bool bDeleteOld=true );
 * 	- bool setFirstSubFunction( const cUnderFunction & pInSubFunction, bool bDeleteOld=true );
 * 	- cUnderFunction * getSecondSubFunction();
 * 	- bool setSecondSubFunction( cUnderFunction * pInSubFunction, bool bDeleteOld=true );
 * 	- bool setSecondSubFunction( const cUnderFunction & pInSubFunction, bool bDeleteOld=true );
 *
 * conditions tested:
 * 	- cConditionEqualInteger
 * 	- cConditionLower
 * 	- cConditionGreater
 */
/*
History:
15.05.2011  Oesterholz  created
09.10.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/

#include "version.h"

#include "cConditionComparison.h"
#include "cConditionEqualInteger.h"
#include "cConditionLower.h"
#include "cConditionGreater.h"
#include "cConditionTrue.h"
#include "cConditionFalse.h"
#include "cConditionNot.h"
#include "cConditionOr.h"
#include "cFunctionValue.h"
#include "cFunctionVariable.h"
#include "cFunctionAbs.h"
#include "cPoint.h"
#include "cRoot.h"
#include "cProperty.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainRational.h"
#include "cDomainVector.h"
#include "cTypeVariable.h"
#include "cTypeInVar.h"
#include "cTypeUnderFunction.h"
#include "cTypeVariable.h"
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

template <class tConditionComparison>
	int testCostructor( unsigned long &ulTestphase );
template <class tConditionComparison>
	int testEqual( unsigned long &ulTestphase );
template <class tConditionComparison>
	int testCopy( unsigned long &ulTestphase );
template <class tConditionComparison>
	int testStoreXml( unsigned long &ulTestphase );
template <class tConditionComparison>
	int testStore( unsigned long &ulTestphase );
template <class tConditionComparison>
	int testSubFunction( unsigned long &ulTestphase );
template <class tConditionComparison>
	int testVariable( unsigned long &ulTestphase );
template <class tConditionComparison>
	int testDefiningFibElement( unsigned long &ulTestphase );


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	cout<<endl<<"Running Test for cConditionComparison methods"<<endl;
	cout<<      "==========================================="<<endl;
	cout<<      "==========================================="<<endl;

	cout<<endl<<"Running Test for cConditionEqualInteger methods"<<endl;
	cout<<      "==============================================="<<endl;
	
	iReturn += testCostructor< cConditionEqualInteger >( ulTestphase );
	iReturn += testEqual< cConditionEqualInteger >( ulTestphase );
	iReturn += testCopy< cConditionEqualInteger >( ulTestphase );
	iReturn += testStoreXml< cConditionEqualInteger >( ulTestphase );
	iReturn += testStore< cConditionEqualInteger >( ulTestphase );
	iReturn += testSubFunction< cConditionEqualInteger >( ulTestphase );
	iReturn += testVariable< cConditionEqualInteger >( ulTestphase );
	iReturn += testDefiningFibElement< cConditionEqualInteger >( ulTestphase );


	cout<<endl<<endl<<"Running Test for cConditionLower methods"<<endl;
	cout<<            "========================================"<<endl;
	
	iReturn += testCostructor< cConditionLower >( ulTestphase );
	iReturn += testEqual< cConditionLower >( ulTestphase );
	iReturn += testCopy< cConditionLower >( ulTestphase );
	iReturn += testStoreXml< cConditionLower >( ulTestphase );
	iReturn += testStore< cConditionLower >( ulTestphase );
	iReturn += testSubFunction< cConditionLower >( ulTestphase );
	iReturn += testVariable< cConditionLower >( ulTestphase );
	iReturn += testDefiningFibElement< cConditionLower >( ulTestphase );


	cout<<endl<<endl<<"Running Test for cConditionGreater methods"<<endl;
	cout<<            "=========================================="<<endl;
	
	iReturn += testCostructor< cConditionGreater >( ulTestphase );
	iReturn += testEqual< cConditionGreater >( ulTestphase );
	iReturn += testCopy< cConditionGreater >( ulTestphase );
	iReturn += testStoreXml< cConditionGreater >( ulTestphase );
	iReturn += testStore< cConditionGreater >( ulTestphase );
	iReturn += testSubFunction< cConditionGreater >( ulTestphase );
	iReturn += testVariable< cConditionGreater >( ulTestphase );
	iReturn += testDefiningFibElement< cConditionGreater >( ulTestphase );



	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}


/**
 * @param dFirstSubFunction the value of the first subfunction
 * @param dFirstSubFunction the value of the second subfunction
 * @return false
 */
template <class tConditionComparison>
		bool getCorrectValue( double dFirstSubFunction, double dSecondSubFunction ){
	
	return false;
}


/**
 * @param dFirstSubFunction the value of the first subfunction
 * @param dFirstSubFunction the value of the second subfunction
 * @return if dFirstSubFunction or dSecondSubFunction is true true, else false
 */
template <> bool getCorrectValue< cConditionEqualInteger >(
		double dFirstSubFunction, double dSecondSubFunction ){
	
	return ( roundToLongFib( dFirstSubFunction ) ==
		roundToLongFib (dSecondSubFunction ) );
}


/**
 * @param dFirstSubFunction the value of the first subfunction
 * @param dFirstSubFunction the value of the second subfunction
 * @return if dFirstSubFunction and dSecondSubFunction is true true, else false
 */
template <> bool getCorrectValue< cConditionLower >(
		double dFirstSubFunction, double dSecondSubFunction ){
	
	return ( dFirstSubFunction < dSecondSubFunction );
}


/**
 * @param dFirstSubFunction the value of the first subfunction
 * @param dFirstSubFunction the value of the second subfunction
 * @return if exactly one of dFirstSubFunction or dSecondSubFunction is
 * 	true true, else false
 */
template <> bool getCorrectValue< cConditionGreater >(
		double dFirstSubFunction, double dSecondSubFunction ){
	
	return ( dFirstSubFunction > dSecondSubFunction );
}



/**
 * This template returns the name condition of the type of the template
 * parameter.
 *
 * @return ""
 */
template <class tConditionComparison> string getConditionName(){
	
	return "";
}

/**
 * This template returns the name condition of the type of the template
 * parameter.
 *
 * @return "or"
 */
template <> string getConditionName< cConditionEqualInteger >(){
	
	return "eqInt";
}

/**
 * This template returns the name condition of the type of the template
 * parameter.
 *
 * @return "or"
 */
template <> string getConditionName< cConditionLower >(){
	
	return "lo";
}

/**
 * This template returns the name condition of the type of the template
 * parameter.
 *
 * @return "or"
 */
template <> string getConditionName< cConditionGreater >(){
	
	return "gr";
}


/**
 * This template returns the type number of the condition of the type of
 * the template parameter.
 *
 * @return -1
 */
template <class tConditionComparison> unsignedIntFib getConditionType(){
	
	return -1;
}

/**
 * This template returns the type number of the condition of the type of
 * the template parameter.
 *
 * @return CONDITION_EQUAL_INTEGER
 */
template <> unsignedIntFib getConditionType< cConditionEqualInteger >(){
	
	return cCondition::CONDITION_EQUAL_INTEGER;
}

/**
 * This template returns the type number of the condition of the type of
 * the template parameter.
 *
 * @return CONDITION_LOWER
 */
template <> unsignedIntFib getConditionType< cConditionLower >(){
	
	return cCondition::CONDITION_LOWER;
}

/**
 * This template returns the type number of the condition of the type of
 * the template parameter.
 *
 * @return CONDITION_GREATER
 */
template <> unsignedIntFib getConditionType< cConditionGreater >(){
	
	return cCondition::CONDITION_GREATER;
}


/**
 * This template returns the type bits of the condition of the type of
 * the template parameter.
 *
 * @return 0
 */
template <class tConditionComparison> char getTypeBit(){

	return (char)0x00;
}

/**
 * This template returns the type bits of the condition of the type of
 * the template parameter.
 *
 * @return (char)0x02
 */
template <> char getTypeBit<cConditionEqualInteger>(){

	return (char)0x08;
}

/**
 * This template returns the type bits of the condition of the type of
 * the template parameter.
 *
 * @return (char)0x03
 */
template <> char getTypeBit<cConditionLower>(){

	return (char)0x09;
}

/**
 * This template returns the type bits of the condition of the type of
 * the template parameter.
 *
 * @return (char)0x04
 */
template <> char getTypeBit<cConditionGreater>(){

	return (char)0x0A;
}





/**
 * This method tests the constructor of the cConditionComparison class.
 *
 * methods tested:
 * 	- cConditionComparison( cUnderFunction * pInFirstSubFunction, cUnderFunction * pInSecondSubFunction, cCondition * pInSuperiorCondition, cFibElement * pInDefiningFibElement )
 * 	- cConditionComparison( const cUnderFunction & inFirstSubFunction, const cUnderFunction & inSecondSubFunction, cCondition * pInSuperiorCondition = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- ~cConditionComparison();
 * 	- bool isValid() const;
 * 	- bool isUsedVariable( const cFibVariable * variable ) const;
 * 	- set<cFibVariable*> getUsedVariables();
 * 	- bool getValue() const;
 * 	- unsignedIntFib getNumberOfConditions() const;
 * 	- unsignedIntFib getNumberOfUnderFunctions() const;
 * 	- cFibElement * getDefiningFibElement() const;
 * 	- cCondition * getSuperiorCondition() const;
 * 	- unsignedLongFib getTimeNeed( unsignedLongFib lMaxTime=0 ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- unsignedIntFib getType() const;
 * 	- string getConditionName() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
template <class tConditionComparison>
	int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<"cRoot rootEmpty;"<<endl;
	cRoot rootEmpty;
	cout<<"rootEmpty.setNumberOfInputVariables( 10 );"<<endl;
	rootEmpty.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 = rootEmpty.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = rootEmpty.getInputVariable( 1 );
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty tConditionComparison condition"<<endl;

	cout<<"tConditionComparison conditionTwoValues1( NULL, NULL );"<<endl;
	tConditionComparison conditionTwoValues1( NULL, NULL );
	cFibElement * pDefiningFibElement = NULL;
	cCondition * pSuperiorCondition = NULL;
	cUnderFunction * pFirstSubFunction = NULL;
	cUnderFunction * pSecondSubFunction = NULL;
	unsigned long ulTimeNeed = 1;
	unsigned long ulCompressedSize = 4;
 
	//check the getValue() methode from tConditionComparison
	if ( conditionTwoValues1.getValue() == false ){
	
		cout<<"The condition value is correctly "<<
			(conditionTwoValues1.getValue()?"true":"false") <<" . "<<endl;
	}else{
		cerr<<"Error: The condition value is "<<
			(conditionTwoValues1.getValue()?"true":"false") <<" but shouldn't be ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from tConditionComparison
	if ( conditionTwoValues1.getDefiningFibElement() == pDefiningFibElement ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionTwoValues1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionTwoValues1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from tConditionComparison
	if ( conditionTwoValues1.getSuperiorCondition() == pSuperiorCondition ){
	
		cout<<"The superior condition of the condition correctly "<<
			conditionTwoValues1.getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			conditionTwoValues1.getSuperiorCondition() <<
			" but should be "<< pSuperiorCondition <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstSubFunction() methode from tConditionComparison
	if ( conditionTwoValues1.getFirstSubFunction() == pFirstSubFunction ){
	
		cout<<"The first subfunction of the condition correctly "<<
			conditionTwoValues1.getFirstSubFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The first subfunction of the condition is "<<
			conditionTwoValues1.getFirstSubFunction() <<
			" but should be "<< pFirstSubFunction <<" ."<<endl;
		iReturn++;
	}
	//check the getSecondSubFunction() methode from tConditionComparison
	if ( conditionTwoValues1.getSecondSubFunction() == pSecondSubFunction ){
	
		cout<<"The second subfunction of the condition correctly "<<
			conditionTwoValues1.getSecondSubFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The second subfunction of the condition is "<<
			conditionTwoValues1.getSecondSubFunction() <<
			" but should be "<< pSecondSubFunction <<" ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from tConditionComparison
	if ( ! conditionTwoValues1.isValid() ){
	
		cout<<"The condition is correctly not valid . "<<endl;
	}else{
		cerr<<"Error: The condition is valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from tConditionComparison
	if ( conditionTwoValues1.getType() == getConditionType<tConditionComparison>() ){
	
		cout<<"The condition type is correctly "<<
			getConditionType<tConditionComparison>()<<". "<<endl;
	}else{
		cerr<<"Error: The type of the condition is not "<<
			getConditionType<tConditionComparison>()<<", but "<<
			conditionTwoValues1.getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getConditionName() methode from tConditionComparison
	if ( conditionTwoValues1.getConditionName() == getConditionName<tConditionComparison>() ){
	
		cout<<"The condition name is correctly \""<<
			conditionTwoValues1.getConditionName() <<"\" . "<<endl;
	}else{
		cerr<<"Error: The name of the condition is not \""<<
			getConditionName<tConditionComparison>()<<"\", but \""<<
			conditionTwoValues1.getConditionName() <<"\" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfConditions() methode from tConditionComparison
	if ( conditionTwoValues1.getNumberOfConditions() == 0 ){
	
		cout<<"The condition number of subfunctions is correctly "<<
			conditionTwoValues1.getNumberOfConditions() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition number of subfunctions is "<<
			conditionTwoValues1.getNumberOfConditions() <<" , but should be 1 ."<<endl;
		iReturn++;
	}
	//check the getNumberOfConditions() methode from tConditionComparison
	if ( conditionTwoValues1.getNumberOfUnderFunctions() == 2 ){
	
		cout<<"The condition number of subfunctions is correctly "<<
			conditionTwoValues1.getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition number of subfunctions is "<<
			conditionTwoValues1.getNumberOfUnderFunctions() <<" , but should be 0 ."<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from tConditionComparison
	if ( conditionTwoValues1.getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the condition is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the condition is "<<
			conditionTwoValues1.getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from tConditionComparison
	if ( conditionTwoValues1.getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the condition is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The tcompressed size of the condition is "<<
			conditionTwoValues1.getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from tConditionComparison
	if ( ! conditionTwoValues1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 isn't used in the condition. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the condition. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from tConditionComparison
	set<cFibVariable*> setUsedVariables = conditionTwoValues1.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"No used variables are given back from the condition. "<<endl;
	}else{
		cerr<<"Error: Used variables are given back from the condition. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an tConditionComparison condition with all values set"<<endl;

	cout<<"cFunctionValue subFunctionValue1( 1 );"<<endl;
	cFunctionValue subFunctionValue1( 1 );
	
	cout<<"cFunctionValue subFunctionValue2( 2 );"<<endl;
	cFunctionValue subFunctionValue2( 2 );
	
	cout<<"tConditionComparison conditionTwoValues2( subFunctionValue1, subFunctionValue2, &conditionTwoValues1, &rootEmpty );"<<endl;
	tConditionComparison conditionTwoValues2( subFunctionValue1, subFunctionValue2, &conditionTwoValues1, &rootEmpty );
	
	pDefiningFibElement = &rootEmpty;
	pSuperiorCondition = &conditionTwoValues1;
	pFirstSubFunction = &subFunctionValue1;
	pSecondSubFunction = &subFunctionValue2;
	ulTimeNeed = 3;
	ulCompressedSize = 4 + 2 * 18;

	//check the getValue() methode from tConditionComparison
	if ( conditionTwoValues2.getValue() == getCorrectValue< tConditionComparison >(
		pFirstSubFunction->getValue(), pSecondSubFunction->getValue() ) ){
	
		cout<<"The condition value is correctly "<<
			(conditionTwoValues2.getValue()?"true":"false") <<" . "<<endl;
	}else{
		cerr<<"Error: The condition value is "<<
			(conditionTwoValues2.getValue()?"true":"false") <<" but shouldn't be ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from tConditionComparison
	if ( conditionTwoValues2.getDefiningFibElement() == pDefiningFibElement ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionTwoValues2.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionTwoValues2.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from tConditionComparison
	if ( conditionTwoValues2.getSuperiorCondition() == pSuperiorCondition ){
	
		cout<<"The superior condition of the condition correctly "<<
			conditionTwoValues2.getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			conditionTwoValues2.getSuperiorCondition() <<
			" but should be "<< pSuperiorCondition <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstSubFunction() methode from tConditionComparison
	if ( *(conditionTwoValues2.getFirstSubFunction()) == *pFirstSubFunction ){
	
		cout<<"The first subfunction of the condition correctly equal to"<<
			conditionTwoValues2.getFirstSubFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The first subfunction of the condition is "<<
			conditionTwoValues2.getFirstSubFunction() <<
			" but should be equal to "<< pFirstSubFunction <<" ."<<endl;
		iReturn++;
	}
	//check the getSecondSubFunction() methode from tConditionComparison
	if ( *(conditionTwoValues2.getSecondSubFunction()) == *pSecondSubFunction ){
	
		cout<<"The second subfunction of the condition correctly equal to"<<
			conditionTwoValues2.getSecondSubFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The second subfunction of the condition is"<<
			conditionTwoValues2.getSecondSubFunction() <<
			" but should be equal to "<< pSecondSubFunction <<" ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from tConditionComparison
	if ( ! conditionTwoValues2.isValid() ){
	
		cout<<"The condition is correctly not valid . "<<endl;
	}else{
		cerr<<"Error: The condition is valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from tConditionComparison
	if ( conditionTwoValues2.getType() == getConditionType<tConditionComparison>() ){
	
		cout<<"The condition type is correctly "<<
			getConditionType<tConditionComparison>()<<" . "<<endl;
	}else{
		cerr<<"Error: The type of the condition is not "<<
			getConditionType<tConditionComparison>()<<", but "<<
			conditionTwoValues2.getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getConditionName() methode from tConditionComparison
	if ( conditionTwoValues2.getConditionName() == getConditionName<tConditionComparison>() ){
	
		cout<<"The condition name is correctly \""<<
			conditionTwoValues2.getConditionName() <<"\" . "<<endl;
	}else{
		cerr<<"Error: The name of the condition is not \""<<
			getConditionName<tConditionComparison>()<<"\", but \""<<
			conditionTwoValues2.getConditionName() <<"\" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfConditions() methode from tConditionComparison
	if ( conditionTwoValues2.getNumberOfConditions() == 0 ){
	
		cout<<"The condition number of subfunctions is correctly "<<
			conditionTwoValues2.getNumberOfConditions() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition number of subfunctions is "<<
			conditionTwoValues2.getNumberOfConditions() <<" , but should be 1 ."<<endl;
		iReturn++;
	}
	//check the getNumberOfConditions() methode from tConditionComparison
	if ( conditionTwoValues2.getNumberOfUnderFunctions() == 2 ){
	
		cout<<"The condition number of subfunctions is correctly "<<
			conditionTwoValues2.getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition number of subfunctions is "<<
			conditionTwoValues2.getNumberOfUnderFunctions() <<" , but should be 0 ."<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from tConditionComparison
	if ( conditionTwoValues2.getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the condition is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the condition is "<<
			conditionTwoValues2.getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from tConditionComparison
	if ( conditionTwoValues2.getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the condition is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The tcompressed size of the condition is "<<
			conditionTwoValues2.getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from tConditionComparison
	if ( ! conditionTwoValues2.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 isn't used in the condition. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the condition. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from tConditionComparison
	setUsedVariables = conditionTwoValues2.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"No used variables are given back from the condition. "<<endl;
	}else{
		cerr<<"Error: Used variables are given back from the condition. "<<endl;
		iReturn++;
	}



	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an tConditionComparison condition with all values set"<<endl;

	cout<<"cFunctionValue subFunctionValuem1( -1 );"<<endl;
	cFunctionValue subFunctionValuem1( -1 );
	
	bool bIsValid = true;
	bool bIsPointer = true;
	tConditionComparison * pConditionTest = NULL;
	
	cTypeUnderFunction typeUnderFunction;
	cTypeVariable typeVariable;
	
	cout<<"cRoot rootDom;"<<endl;
	cRoot rootDom;
	
	cout<<"cDomainNaturalNumberBit domainNaturalNumberBit3( 3 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberBit3( 3 );
	cout<<"cDomainNaturalNumberBit domainNaturalNumberBit5( 5 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberBit5( 5 );
	cout<<"cDomainNaturalNumberBit domainNaturalNumberBit7( 7 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberBit7( 7 );
	
	cout<<"rootDom.getDomains()->addDomain( typeVariable, domainNaturalNumberBit3 );"<<endl;
	rootDom.getDomains()->addDomain( typeVariable, domainNaturalNumberBit3 );
	cout<<"rootDom.getDomains()->addDomain( typeUnderFunction, domainNaturalNumberBit5 );"<<endl;
	rootDom.getDomains()->addDomain( typeUnderFunction, domainNaturalNumberBit5 );
	cout<<"rootDom.getValueDomains()->addDomain( typeUnderFunction, domainNaturalNumberBit7 );"<<endl;
	rootDom.getValueDomains()->addDomain( typeUnderFunction, domainNaturalNumberBit7 );
	
	cout<<"rootDom.setNumberOfInputVariables( 10 );"<<endl;
	rootDom.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 = rootDom.getInputVariable( 1 );"<<endl;
	pVariable1 = rootDom.getInputVariable( 1 );
	
	bool bVariable1Used = false;
	
	pDefiningFibElement = &rootDom;
	
	for ( unsigned int uiTestCase = 1; uiTestCase <= 16; uiTestCase++ ){
		
		switch ( uiTestCase ){
		case 1:
			cout<<endl<<"pConditionTest = new tConditionComparison( subFunctionValue1, subFunctionValue2, &conditionTwoValues1, &rootDom );"<<endl;
			pConditionTest = new tConditionComparison( subFunctionValue1, subFunctionValue2, &conditionTwoValues1, &rootDom );
			
			bIsPointer = false;
			bIsValid = true;
			pFirstSubFunction = &subFunctionValue1;
			pSecondSubFunction = &subFunctionValue2;
			ulTimeNeed = 3;
			ulCompressedSize = 4 + 2 * 9;
		break;
		case 2:
			cout<<endl<<"pConditionTest = new tConditionComparison( subFunctionValue2, subFunctionValue2, &conditionTwoValues1, &rootDom );"<<endl;
			pConditionTest = new tConditionComparison( subFunctionValue2, subFunctionValue2, &conditionTwoValues1, &rootDom );
			
			bIsPointer = false;
			bIsValid = true;
			pFirstSubFunction = &subFunctionValue2;
			pSecondSubFunction = &subFunctionValue2;
			ulTimeNeed = 3;
			ulCompressedSize = 4 + 2 * 9;
		break;
		case 3:
			cout<<endl<<"pConditionTest = new tConditionComparison( subFunctionValuem1, subFunctionValue1, &conditionTwoValues1, &rootDom );"<<endl;
			pConditionTest = new tConditionComparison( subFunctionValuem1, subFunctionValue1, &conditionTwoValues1, &rootDom );
			
			bIsPointer = false;
			bIsValid = false;
			pFirstSubFunction = &subFunctionValuem1;
			pSecondSubFunction = &subFunctionValue1;
			ulTimeNeed = 3;
			ulCompressedSize = 4 + 2 * 9;
		break;
		
		case 4:
			bIsPointer = true;
			bIsValid = true;
			pFirstSubFunction = new cFunctionValue( 1.4 );
			cout<<endl<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionValue( 1.4 );"<<endl;
			pSecondSubFunction = new cFunctionValue( 1.4 );
			cout<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionValue( 1.4 );"<<endl;
			ulTimeNeed = 3;
			ulCompressedSize = 4 + 2 * 9;
			
			cout<<"pConditionTest = new tConditionComparison( "<<pFirstSubFunction<<
				", "<<pSecondSubFunction<<", &conditionTwoValues1, &rootDom );"<<endl;
			pConditionTest = new tConditionComparison( pFirstSubFunction, pSecondSubFunction, &conditionTwoValues1, &rootDom );
		break;
		case 5:
			bIsPointer = true;
			bIsValid = true;
			pFirstSubFunction = new cFunctionValue( 2 );
			cout<<endl<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionValue( 2 );"<<endl;
			pSecondSubFunction = new cFunctionValue( 1.9 );
			cout<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionValue( 1.9 );"<<endl;
			ulTimeNeed = 3;
			ulCompressedSize = 4 + 2 * 9;
			
			cout<<"pConditionTest = new tConditionComparison( "<<pFirstSubFunction<<
				", "<<pSecondSubFunction<<", &conditionTwoValues1, &rootDom );"<<endl;
			pConditionTest = new tConditionComparison( pFirstSubFunction, pSecondSubFunction, &conditionTwoValues1, &rootDom );
		break;
		case 6:
			bIsPointer = true;
			bIsValid = true;
			pFirstSubFunction = new cFunctionValue( 10000000 );
			cout<<endl<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionValue( 10000000 );"<<endl;
			pSecondSubFunction = new cFunctionValue( -10000000 );
			cout<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionValue( -10000000 );"<<endl;
			ulTimeNeed = 3;
			ulCompressedSize = 4 + 2 * 9;
			
			cout<<"pConditionTest = new tConditionComparison( "<<pFirstSubFunction<<
				", "<<pSecondSubFunction<<", &conditionTwoValues1, &rootDom );"<<endl;
			pConditionTest = new tConditionComparison( pFirstSubFunction, pSecondSubFunction, &conditionTwoValues1, &rootDom );
		break;
		case 7:
			bIsPointer = true;
			bIsValid = true;
			pFirstSubFunction = new cFunctionValue( -6 );
			cout<<endl<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionValue( -6 );"<<endl;
			pSecondSubFunction = new cFunctionValue( -6.1 );
			cout<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionValue( -6.1 );"<<endl;
			ulTimeNeed = 3;
			ulCompressedSize = 4 + 2 * 9;
			
			cout<<"pConditionTest = new tConditionComparison( "<<pFirstSubFunction<<
				", "<<pSecondSubFunction<<", &conditionTwoValues1, &rootDom );"<<endl;
			pConditionTest = new tConditionComparison( pFirstSubFunction, pSecondSubFunction, &conditionTwoValues1, &rootDom );
		break;
		
		case 8:
			bIsPointer = true;
			bIsValid = false;
			pFirstSubFunction = NULL;
			pSecondSubFunction = new cFunctionValue( 1.4 );
			cout<<endl<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionValue( 1.4 );;"<<endl;
			ulTimeNeed = 2;
			ulCompressedSize = 4 + 9;
			
			cout<<"pConditionTest = new tConditionComparison( "<<pFirstSubFunction<<
				", "<<pSecondSubFunction<<", &conditionTwoValues1, &rootDom );"<<endl;
			pConditionTest = new tConditionComparison( pFirstSubFunction, pSecondSubFunction, &conditionTwoValues1, &rootDom );
		break;
		case 9:
			bIsPointer = true;
			bIsValid = false;
			pFirstSubFunction = new cFunctionValue( 1 );
			cout<<endl<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionValue( 1 );"<<endl;
			pSecondSubFunction = NULL;
			ulTimeNeed = 2;
			ulCompressedSize = 4 + 9;
			
			cout<<"pConditionTest = new tConditionComparison( "<<pFirstSubFunction<<
				", "<<pSecondSubFunction<<", &conditionTwoValues1, &rootDom );"<<endl;
			pConditionTest = new tConditionComparison( pFirstSubFunction, pSecondSubFunction, &conditionTwoValues1, &rootDom );
		break;
		case 10:
			bIsPointer = true;
			bIsValid = false;
			pFirstSubFunction = NULL;
			pSecondSubFunction = new cFunctionValue( 0 );
			cout<<endl<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionValue( 0 );"<<endl;
			ulTimeNeed = 2;
			ulCompressedSize = 4 + 9;
			
			cout<<"pConditionTest = new tConditionComparison( "<<pFirstSubFunction<<
				", "<<pSecondSubFunction<<", &conditionTwoValues1, &rootDom );"<<endl;
			pConditionTest = new tConditionComparison( pFirstSubFunction, pSecondSubFunction, &conditionTwoValues1, &rootDom );
		break;
		case 11:
			bIsPointer = true;
			bIsValid = false;
			pFirstSubFunction = new cFunctionValue( 0 );
			cout<<endl<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionValue( 0 );"<<endl;
			pSecondSubFunction = NULL;
			ulTimeNeed = 2;
			ulCompressedSize = 4 + 9;
			
			cout<<"pConditionTest = new tConditionComparison( "<<pFirstSubFunction<<
				", "<<pSecondSubFunction<<", &conditionTwoValues1, &rootDom );"<<endl;
			pConditionTest = new tConditionComparison( pFirstSubFunction, pSecondSubFunction, &conditionTwoValues1, &rootDom );
		break;
		case 12:
			bIsPointer = true;
			bIsValid = true;
			pFirstSubFunction = new cFunctionValue( 0.6 );
			cout<<endl<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionValue( 0.6 );"<<endl;
			pSecondSubFunction = new cFunctionValue( 1.499 );
			cout<<endl<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionValue( 1.499 );"<<endl;
			ulTimeNeed = 3;
			ulCompressedSize = 4 + 2 * 9;
			
			cout<<"pConditionTest = new tConditionComparison( "<<pFirstSubFunction<<
				", "<<pSecondSubFunction<<", &conditionTwoValues1, &rootDom );"<<endl;
			pConditionTest = new tConditionComparison( pFirstSubFunction, pSecondSubFunction, &conditionTwoValues1, &rootDom );
		break;
		case 13:
			bIsPointer = true;
			bIsValid = true;
			pFirstSubFunction = new cFunctionValue( 0.6 );
			cout<<endl<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionValue( 0.6 );"<<endl;
			pSecondSubFunction = new cFunctionValue( 1.501 );
			cout<<endl<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionValue( 1.501 );"<<endl;
			ulTimeNeed = 3;
			ulCompressedSize = 4 + 2 * 9;
			
			cout<<"pConditionTest = new tConditionComparison( "<<pFirstSubFunction<<
				", "<<pSecondSubFunction<<", &conditionTwoValues1, &rootDom );"<<endl;
			pConditionTest = new tConditionComparison( pFirstSubFunction, pSecondSubFunction, &conditionTwoValues1, &rootDom );
		break;
		case 14:
			bIsPointer = true;
			bIsValid = false;
			pFirstSubFunction = new cFunctionValue( 5 );
			cout<<endl<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionValue( 0.6 );"<<endl;
			pSecondSubFunction = new cFunctionVariable( pVariable1 );
			cout<<endl<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionVariable( pVariable1 );"<<endl;
			ulTimeNeed = 3;
			ulCompressedSize = 4 + 9 + 5;
			bVariable1Used = true;
			
			cout<<"pConditionTest = new tConditionComparison( "<<pFirstSubFunction<<
				", "<<pSecondSubFunction<<", &conditionTwoValues1, &rootDom );"<<endl;
			pConditionTest = new tConditionComparison( pFirstSubFunction, pSecondSubFunction, &conditionTwoValues1, &rootDom );
		break;
		case 15:
			bIsPointer = true;
			bIsValid = false;
			pFirstSubFunction = new cFunctionVariable( pVariable1 );
			cout<<endl<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionVariable( pVariable1 );"<<endl;
			pSecondSubFunction = new cFunctionVariable( pVariable1 );
			cout<<endl<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionVariable( pVariable1 );"<<endl;
			ulTimeNeed = 3;
			ulCompressedSize = 4 + 5 + 5;
			bVariable1Used = true;
			
			cout<<"pConditionTest = new tConditionComparison( "<<pFirstSubFunction<<
				", "<<pSecondSubFunction<<", &conditionTwoValues1, &rootDom );"<<endl;
			pConditionTest = new tConditionComparison( pFirstSubFunction, pSecondSubFunction, &conditionTwoValues1, &rootDom );
		break;
		case 16:
			bIsPointer = true;
			bIsValid = true;
			pFirstSubFunction = new cFunctionValue( 6 );
			cout<<endl<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionValue( 0.6 );"<<endl;
			pSecondSubFunction = new cFunctionValue( 7 );
			cout<<endl<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionValue( 1.501 );"<<endl;
			ulTimeNeed = 3;
			ulCompressedSize = 4 + 2 * 9;
			bVariable1Used = false;
			
			cout<<"pConditionTest = new tConditionComparison( "<<pFirstSubFunction<<
				", "<<pSecondSubFunction<<", &conditionTwoValues1, &rootDom );"<<endl;
			pConditionTest = new tConditionComparison( pFirstSubFunction, pSecondSubFunction, &conditionTwoValues1, &rootDom );
		break;
		
		
		default://error no such testcase
			cerr<<endl<<"Error: No such testcase ("<<uiTestCase<<")."<<endl;
			iReturn++;
			continue;
		}
	
		//check the getValue() methode from tConditionComparison
		if ( ( pFirstSubFunction != NULL ) && ( pSecondSubFunction != NULL ) ){
			if ( pConditionTest->getValue() ==  getCorrectValue< tConditionComparison >(
					pFirstSubFunction->getValue(), pSecondSubFunction->getValue() )  ){
			
				cout<<"The condition value is correctly "<<
					(pConditionTest->getValue()?"true":"false") <<" . "<<endl;
			}else{
				cerr<<"Error: The condition value is "<<
					(pConditionTest->getValue()?"true":"false") <<" but shouldn't be ."<<endl;
				iReturn++;
			}
		}else{
			if ( pConditionTest->getValue() == false ){
			
				cout<<"The condition value is correctly "<<
					(pConditionTest->getValue()?"true":"false") <<" . "<<endl;
			}else{
				cerr<<"Error: The condition value is "<<
					(pConditionTest->getValue()?"true":"false") <<" but shouldn't be ."<<endl;
				iReturn++;
			}
		}
		//check the getDefiningFibElement() methode from tConditionComparison
		if ( pConditionTest->getDefiningFibElement() == pDefiningFibElement ){
		
			cout<<"The condition defining Fib-element is correctly "<<
				pConditionTest->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The condition defining Fib-element is "<<
				pConditionTest->getDefiningFibElement() <<
				" but should be "<< pDefiningFibElement <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorCondition() methode from tConditionComparison
		if ( pConditionTest->getSuperiorCondition() == pSuperiorCondition ){
		
			cout<<"The superior condition of the condition correctly "<<
				pConditionTest->getSuperiorCondition() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior condition of the condition is "<<
				pConditionTest->getSuperiorCondition() <<
				" but should be "<< pSuperiorCondition <<" ."<<endl;
			iReturn++;
		}
		if ( ! bIsPointer ){
			//check the getFirstSubFunction() methode from tConditionComparison
			if ( *(pConditionTest->getFirstSubFunction()) == *pFirstSubFunction ){
			
				cout<<"The first subfunction of the condition correctly equal to"<<
					pConditionTest->getFirstSubFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The first subfunction of the condition is "<<
					pConditionTest->getFirstSubFunction() <<
					" but should be equal to "<< pFirstSubFunction <<" ."<<endl;
				iReturn++;
			}
			//check the getSecondSubFunction() methode from tConditionComparison
			if ( *(pConditionTest->getSecondSubFunction()) == *pSecondSubFunction ){
			
				cout<<"The second subfunction of the condition correctly equal to"<<
					pConditionTest->getSecondSubFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The second subfunction of the condition is"<<
					pConditionTest->getSecondSubFunction() <<
					" but should be equal to "<< pSecondSubFunction <<" ."<<endl;
				iReturn++;
			}
		}else{
			//check the getFirstSubFunction() methode from tConditionComparison
			if ( pConditionTest->getFirstSubFunction() == pFirstSubFunction ){
			
				cout<<"The first subfunction of the condition correctly "<<
					pConditionTest->getFirstSubFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The first subfunction of the condition is "<<
					pConditionTest->getFirstSubFunction() <<
					" but should be "<< pFirstSubFunction <<" ."<<endl;
				iReturn++;
			}
			//check the getSecondSubFunction() methode from tConditionComparison
			if ( pConditionTest->getSecondSubFunction() == pSecondSubFunction ){
			
				cout<<"The second subfunction of the condition correctly "<<
					pConditionTest->getSecondSubFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The second subfunction of the condition is"<<
					pConditionTest->getSecondSubFunction() <<
					" but should be "<< pSecondSubFunction <<" ."<<endl;
				iReturn++;
			}
		}
		
		//check the isValid() methode from tConditionComparison
		if ( pConditionTest->isValid() == bIsValid ){
		
			cout<<"The condition is correctly "<<(bIsValid?"":"not ")<<"valid . "<<endl;
		}else{
			cerr<<"Error: The condition is "<<(bIsValid?"not ":"")<<" valid, but should be ."<<endl;
			iReturn++;
		}
		//check the getType() methode from tConditionComparison
		if ( pConditionTest->getType() == getConditionType<tConditionComparison>() ){
		
			cout<<"The condition type is correctly "<<
				getConditionType<tConditionComparison>()<<" . "<<endl;
		}else{
			cerr<<"Error: The type of the condition is not "<<
				getConditionType<tConditionComparison>()<<", but "<<
				pConditionTest->getType() <<" ."<<endl;
			iReturn++;
		}
		//check the getConditionName() methode from tConditionComparison
		if ( pConditionTest->getConditionName() == getConditionName<tConditionComparison>() ){
		
			cout<<"The condition name is correctly \""<<
				pConditionTest->getConditionName() <<"\" . "<<endl;
		}else{
			cerr<<"Error: The name of the condition is not \""<<
				getConditionName<tConditionComparison>()<<"\", but \""<<
				pConditionTest->getConditionName() <<"\" ."<<endl;
			iReturn++;
		}
		//check the getNumberOfConditions() methode from tConditionComparison
		if ( pConditionTest->getNumberOfConditions() == 0 ){
		
			cout<<"The condition number of subfunctions is correctly "<<
				pConditionTest->getNumberOfConditions() <<" . "<<endl;
		}else{
			cerr<<"Error: The condition number of subfunctions is "<<
				pConditionTest->getNumberOfConditions() <<" , but should be 1 ."<<endl;
			iReturn++;
		}
		//check the getNumberOfConditions() methode from tConditionComparison
		if ( pConditionTest->getNumberOfUnderFunctions() == 2 ){
		
			cout<<"The condition number of subfunctions is correctly "<<
				pConditionTest->getNumberOfUnderFunctions() <<" . "<<endl;
		}else{
			cerr<<"Error: The condition number of subfunctions is "<<
				pConditionTest->getNumberOfUnderFunctions() <<" , but should be 0 ."<<endl;
			iReturn++;
		}
		//check the getTimeNeed() methode from tConditionComparison
		if ( pConditionTest->getTimeNeed() == ulTimeNeed ){
		
			cout<<"The time needed to evalue the condition is correctly "<< ulTimeNeed <<" . "<<endl;
		}else{
			cerr<<"Error: The time needed to evalue the condition is "<<
				pConditionTest->getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
			iReturn++;
		}
		//check the getCompressedSize() methode from tConditionComparison
		if ( pConditionTest->getCompressedSize() == ulCompressedSize ){
		
			cout<<"The compressed size of the condition is correctly "<<
			ulCompressedSize <<" . "<<endl;
		}else{
			cerr<<"Error: The tcompressed size of the condition is "<<
				pConditionTest->getCompressedSize()<<" ,but should be "<<
				ulCompressedSize <<" . "<<endl;
			iReturn++;
		}
		//check the getCompressedSize() methode from tConditionComparison
		if ( pConditionTest->isUsedVariable( pVariable1 ) == bVariable1Used ){
		
			cout<<"The variable pVariable1 "<<(bVariable1Used?"is":"isn't")<<" used in the condition. "<<endl;
		}else{
			cerr<<"Error: The variable pVariable1 "<<(bVariable1Used?"isn't":"is")<<" used in the condition. "<<endl;
			iReturn++;
		}
		//check the getUsedVariables() methode from tConditionComparison
		setUsedVariables = pConditionTest->getUsedVariables();
		if ( setUsedVariables.empty() != bVariable1Used ){
		
			cout<<(bVariable1Used?"No used":"Used")<<" variables are given back from the condition. "<<endl;
		}else{
			cerr<<"Error: "<<(bVariable1Used?"Used":"No used")<<
				" variables are given back from the condition. "<<endl;
			iReturn++;
		}
		
		if ( pConditionTest ){
			delete pConditionTest;
			pConditionTest = NULL;
		}
	}//for different subfunctions


	return iReturn;
}



/**
 * This method tests the comparison methods of two given conditions, which are
 * equal.
 *
 * @param condition1 the first Fib-object to compare
 * @param szNameObject1 the name of the first Fib-object to compare
 * @param condition2 the secound Fib-object to compare to
 * @param szNameObject2 the name of the secound Fib-object to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualObjects( const cCondition &condition1, const string &szNameObject1,
	const cCondition &condition2, const string &szNameObject2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( condition1.equal( condition2 ) ){
	
		cout<<"The "<<szNameObject1<<" is equal to "<<szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" is not equal to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}
	//check operator== for cCondition
	if ( condition1 == condition2 ){
	
		cout<<"The "<<szNameObject1<<" is equal (operator==) to "<<
			szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" is not equal (operator==) to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}
	//check operator!= for cCondition
	if ( ! (condition1 != condition2) ){
	
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
 * This method tests the comparison methods of two given conditions, which are
 * not equal.
 *
 * @param condition1 the first Fib-object to compare
 * @param szNameObject1 the name of the first Fib-object to compare
 * @param condition2 the secound Fib-object to compare to
 * @param szNameObject2 the name of the secound Fib-object to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoNotEqualObjects( const cCondition &condition1, const string &szNameObject1,
	const cCondition &condition2, const string &szNameObject2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( ! condition1.equal( condition2 ) ){
	
		cout<<"The "<<szNameObject1<<" is not equal to "<<szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" is equal to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}
	//check operator== for cCondition
	if ( ! (condition1 == condition2) ){
	
		cout<<"The "<<szNameObject1<<" is not equal (operator==) to "<<
			szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" is equal (operator==) to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}

	//check operator!= for cCondition
	if ( condition1 != condition2 ){
	
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
 * This method tests equal method of the tConditionComparison class.
 *
 * methods tested:
 * 	- bool equal( const cFibElement & fibObject ) const
 * 	- bool operator==( const cCondition &condition ) const;
 * 	- bool operator!=( const cCondition &condition ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
template <class tConditionComparison>
	int testEqual( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing comparison methods for condition"<<endl;

	cout<<"cRoot rootEmpty;"<<endl;
	cRoot rootEmpty;
	cout<<"rootEmpty.setNumberOfInputVariables( 10 );"<<endl;
	rootEmpty.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 =  rootEmpty.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 =  rootEmpty.getInputVariable( 1 );
	
	cout<<endl<<"Creating conditions objects to compare: "<<endl<<endl;

	//simple condition
	cout<<"tConditionComparison conditionTwoValues1( NULL, NULL );"<<endl;
	tConditionComparison conditionTwoValues1( NULL, NULL );

	cout<<"tConditionComparison conditionTwoValues2( NULL, NULL );"<<endl;
	tConditionComparison conditionTwoValues2( NULL, NULL );

	//with subfunction
	cout<<"tConditionComparison conditionTwoValuesV1NULL( new cFunctionValue( 1 ), NULL );"<<endl;
	tConditionComparison conditionTwoValuesV1NULL( new cFunctionValue( 1 ), NULL );

	cout<<"tConditionComparison conditionTwoValuesV0NULL( new cFunctionValue( 0 ), NULL );"<<endl;
	tConditionComparison conditionTwoValuesV0NULL( new cFunctionValue( 0 ), NULL );

	cout<<"tConditionComparison conditionTwoValuesNULLV0( NULL, new cFunctionValue( 0 ) );"<<endl;
	tConditionComparison conditionTwoValuesNULLV0( NULL, new cFunctionValue( 0 ) );

	cout<<"tConditionComparison conditionTwoValueNULLVa1( NULL, new cFunctionVariable( pVariable1 ) );"<<endl;
	tConditionComparison conditionTwoValueNULLVa1( NULL, new cFunctionVariable( pVariable1 ) );


	cout<<"tConditionComparison conditionTwoValuesV1V0( new cFunctionValue( 1 ), new cFunctionValue( 0 ) );"<<endl;
	tConditionComparison conditionTwoValuesV1V0( new cFunctionValue( 1 ), new cFunctionValue( 0 ) );

	cout<<"tConditionComparison conditionTwoValueV0V1( new cFunctionValue( 0 ), new cFunctionValue( 1 ) );"<<endl;
	tConditionComparison conditionTwoValueV0V1( new cFunctionValue( 0 ), new cFunctionValue( 1 ) );

	cout<<"tConditionComparison conditionTwoValueVm1V0( new cFunctionValue( -1 ), new cFunctionValue( 0 ) );"<<endl;
	tConditionComparison conditionTwoValueVm1V0( new cFunctionValue( -1 ), new cFunctionValue( 0 ) );

	cout<<"tConditionComparison conditionTwoValueV1Va1( new cFunctionValue( 1 ), new cFunctionVariable( pVariable1 ) );"<<endl;
	tConditionComparison conditionTwoValueV1Va1( new cFunctionValue( 1 ), new cFunctionVariable( pVariable1 ) );


	
	//condition with defining Fib-element
	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	cout<<"tConditionComparison conditionDefFE( NULL, NULL, NULL, &rootSimple1 );"<<endl;
	tConditionComparison conditionDefFE( NULL, NULL, NULL, &rootSimple1 );

	//condition with superior condition
	cout<<"cConditionNot conditionNotSup( NULL );"<<endl;
	cConditionNot conditionNotSup( NULL );
	cout<<"tConditionComparison conditionSup( NULL, NULL, & conditionNotSup );"<<endl;
	tConditionComparison conditionSup( NULL, NULL, & conditionNotSup );

	//condition with domains set
	cout<<"root1 rootSimple1;"<<endl;
	cRoot root1;
	
	cout<<"cTypeVariable testTypeVariable;"<<endl;
	cTypeVariable testTypeVariable;
	cout<<"cDomainNaturalNumberBit domainNat8( 8 );"<<endl;
	cDomainNaturalNumberBit domainNat8( 8 );

	cout<<"root1.getDomains()->addDomain( testTypeVariable, &domainNat8 );"<<endl;
	root1.getDomains()->addDomain( testTypeVariable, &domainNat8 );

	cout<<"tConditionComparison conditionDom( NULL, NULL, NULL, &root1 );"<<endl;
	tConditionComparison conditionDom( NULL, NULL, NULL, &root1 );

	//condition with defining Fib-element and superior condition
	cout<<"cRoot rootSimple2;"<<endl;
	cRoot rootSimple2;
	cout<<"cConditionNot conditionNotSup2( NULL );"<<endl;
	cConditionNot conditionNotSup2( NULL );
	cout<<"tConditionComparison conditionDefFeSc( NULL, NULL, & conditionNotSup2, &rootSimple2 );"<<endl;
	tConditionComparison conditionDefFeSc( NULL, NULL, & conditionNotSup2, &rootSimple2 );

	//condition with all elements set
	cout<<"cRoot rootSimple3;"<<endl;
	cRoot rootSimple3;
	cout<<"cConditionNot conditionNotSup3( NULL );"<<endl;
	cConditionNot conditionNotSup3( NULL );
	cout<<"tConditionComparison conditionFull( new cFunctionValue( 1 ), new cFunctionVariable( pVariable1 ), & conditionNotSup3, &rootSimple3 );"<<endl;
	tConditionComparison conditionFull( new cFunctionValue( 1 ), new cFunctionVariable( pVariable1 ), & conditionNotSup3, &rootSimple3 );


	//conditions of other typs
	cout<<"cConditionFalse conditionFalse;"<<endl;
	cConditionFalse conditionFalse;
	
	cout<<"cConditionNot conditionNot( conditionFalse );"<<endl;
	cConditionNot conditionNot( conditionFalse );

	cout<<"cConditionOr conditionOr( new cConditionTrue(), new cConditionTrue() );"<<endl;
	cConditionOr conditionOr( new cConditionTrue(), new cConditionTrue() );


	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with conditionTwoValues1
	cCondition * actualObject = &conditionTwoValues1;
	string szActualObjectName = "conditionTwoValues1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1NULL, "conditionTwoValuesV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV0NULL, "conditionTwoValuesV0NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLV0, "conditionTwoValuesNULLV0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLVa1, "conditionTwoValueNULLVa1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1V0, "conditionTwoValuesV1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV0V1, "conditionTwoValueV0V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueVm1V0, "conditionTwoValueVm1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV1Va1, "conditionTwoValueV1Va1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionOr, "conditionOr" );

	//compare with conditionTwoValues2
	actualObject = &conditionTwoValues2;
	szActualObjectName = "conditionTwoValues2";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1NULL, "conditionTwoValuesV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV0NULL, "conditionTwoValuesV0NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLV0, "conditionTwoValuesNULLV0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLVa1, "conditionTwoValueNULLVa1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1V0, "conditionTwoValuesV1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV0V1, "conditionTwoValueV0V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueVm1V0, "conditionTwoValueVm1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV1Va1, "conditionTwoValueV1Va1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionOr, "conditionOr" );

	//compare with conditionTwoValuesV1NULL
	actualObject = &conditionTwoValuesV1NULL;
	szActualObjectName = "conditionTwoValuesV1NULL";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1NULL, "conditionTwoValuesV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV0NULL, "conditionTwoValuesV0NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLV0, "conditionTwoValuesNULLV0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLVa1, "conditionTwoValueNULLVa1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1V0, "conditionTwoValuesV1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV0V1, "conditionTwoValueV0V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueVm1V0, "conditionTwoValueVm1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV1Va1, "conditionTwoValueV1Va1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionOr, "conditionOr" );

	//compare with conditionTwoValuesV0NULL
	actualObject = &conditionTwoValuesV0NULL;
	szActualObjectName = "conditionTwoValuesV0NULL";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1NULL, "conditionTwoValuesV1NULL" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV0NULL, "conditionTwoValuesV0NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLV0, "conditionTwoValuesNULLV0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLVa1, "conditionTwoValueNULLVa1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1V0, "conditionTwoValuesV1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV0V1, "conditionTwoValueV0V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueVm1V0, "conditionTwoValueVm1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV1Va1, "conditionTwoValueV1Va1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionOr, "conditionOr" );

	//compare with conditionTwoValuesNULLV0
	actualObject = &conditionTwoValuesNULLV0;
	szActualObjectName = "conditionTwoValuesNULLV0";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1NULL, "conditionTwoValuesV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV0NULL, "conditionTwoValuesV0NULL" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLV0, "conditionTwoValuesNULLV0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLVa1, "conditionTwoValueNULLVa1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1V0, "conditionTwoValuesV1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV0V1, "conditionTwoValueV0V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueVm1V0, "conditionTwoValueVm1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV1Va1, "conditionTwoValueV1Va1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionOr, "conditionOr" );

	//compare with conditionTwoValueNULLVa1
	actualObject = &conditionTwoValueNULLVa1;
	szActualObjectName = "conditionTwoValueNULLVa1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1NULL, "conditionTwoValuesV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV0NULL, "conditionTwoValuesV0NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLV0, "conditionTwoValuesNULLV0" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLVa1, "conditionTwoValueNULLVa1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1V0, "conditionTwoValuesV1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV0V1, "conditionTwoValueV0V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueVm1V0, "conditionTwoValueVm1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV1Va1, "conditionTwoValueV1Va1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionOr, "conditionOr" );

	//compare with conditionTwoValuesV1NULL
	actualObject = &conditionTwoValuesV1V0;
	szActualObjectName = "conditionTwoValuesV1V0";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1NULL, "conditionTwoValuesV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV0NULL, "conditionTwoValuesV0NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLV0, "conditionTwoValuesNULLV0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLVa1, "conditionTwoValueNULLVa1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1V0, "conditionTwoValuesV1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV0V1, "conditionTwoValueV0V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueVm1V0, "conditionTwoValueVm1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV1Va1, "conditionTwoValueV1Va1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionOr, "conditionOr" );

	//compare with conditionTwoValueV0V1
	actualObject = &conditionTwoValueV0V1;
	szActualObjectName = "conditionTwoValueV0V1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1NULL, "conditionTwoValuesV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV0NULL, "conditionTwoValuesV0NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLV0, "conditionTwoValuesNULLV0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLVa1, "conditionTwoValueNULLVa1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1V0, "conditionTwoValuesV1V0" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV0V1, "conditionTwoValueV0V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueVm1V0, "conditionTwoValueVm1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV1Va1, "conditionTwoValueV1Va1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionOr, "conditionOr" );

	//compare with conditionTwoValueVm1V0
	actualObject = &conditionTwoValueVm1V0;
	szActualObjectName = "conditionTwoValueVm1V0";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1NULL, "conditionTwoValuesV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV0NULL, "conditionTwoValuesV0NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLV0, "conditionTwoValuesNULLV0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLVa1, "conditionTwoValueNULLVa1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1V0, "conditionTwoValuesV1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV0V1, "conditionTwoValueV0V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValueVm1V0, "conditionTwoValueVm1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV1Va1, "conditionTwoValueV1Va1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionOr, "conditionOr" );

	//compare with conditionTwoValueV1Va1
	actualObject = &conditionTwoValueV1Va1;
	szActualObjectName = "conditionTwoValueV1Va1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1NULL, "conditionTwoValuesV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV0NULL, "conditionTwoValuesV0NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLV0, "conditionTwoValuesNULLV0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLVa1, "conditionTwoValueNULLVa1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1V0, "conditionTwoValuesV1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV0V1, "conditionTwoValueV0V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueVm1V0, "conditionTwoValueVm1V0" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV1Va1, "conditionTwoValueV1Va1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionOr, "conditionOr" );

	//compare with conditionDefFE
	actualObject = &conditionDefFE;
	szActualObjectName = "conditionDefFE";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1NULL, "conditionTwoValuesV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV0NULL, "conditionTwoValuesV0NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLV0, "conditionTwoValuesNULLV0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLVa1, "conditionTwoValueNULLVa1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1V0, "conditionTwoValuesV1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV0V1, "conditionTwoValueV0V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueVm1V0, "conditionTwoValueVm1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV1Va1, "conditionTwoValueV1Va1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionOr, "conditionOr" );

	//compare with conditionSup
	actualObject = &conditionSup;
	szActualObjectName = "conditionSup";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1NULL, "conditionTwoValuesV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV0NULL, "conditionTwoValuesV0NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLV0, "conditionTwoValuesNULLV0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLVa1, "conditionTwoValueNULLVa1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1V0, "conditionTwoValuesV1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV0V1, "conditionTwoValueV0V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueVm1V0, "conditionTwoValueVm1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV1Va1, "conditionTwoValueV1Va1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionOr, "conditionOr" );

	//compare with conditionDom
	actualObject = &conditionDom;
	szActualObjectName = "conditionDom";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1NULL, "conditionTwoValuesV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV0NULL, "conditionTwoValuesV0NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLV0, "conditionTwoValuesNULLV0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLVa1, "conditionTwoValueNULLVa1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1V0, "conditionTwoValuesV1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV0V1, "conditionTwoValueV0V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueVm1V0, "conditionTwoValueVm1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV1Va1, "conditionTwoValueV1Va1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionOr, "conditionOr" );

	//compare with conditionDefFeSc
	actualObject = &conditionDefFeSc;
	szActualObjectName = "conditionDefFeSc";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1NULL, "conditionTwoValuesV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV0NULL, "conditionTwoValuesV0NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLV0, "conditionTwoValuesNULLV0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLVa1, "conditionTwoValueNULLVa1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1V0, "conditionTwoValuesV1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV0V1, "conditionTwoValueV0V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueVm1V0, "conditionTwoValueVm1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV1Va1, "conditionTwoValueV1Va1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionOr, "conditionOr" );

	//compare with conditionFull
	actualObject = &conditionFull;
	szActualObjectName = "conditionFull";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1NULL, "conditionTwoValuesV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV0NULL, "conditionTwoValuesV0NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLV0, "conditionTwoValuesNULLV0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLVa1, "conditionTwoValueNULLVa1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1V0, "conditionTwoValuesV1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV0V1, "conditionTwoValueV0V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueVm1V0, "conditionTwoValueVm1V0" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV1Va1, "conditionTwoValueV1Va1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionOr, "conditionOr" );


	//compare with conditionFalse
	actualObject = &conditionFalse;
	szActualObjectName = "conditionFalse";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1NULL, "conditionTwoValuesV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV0NULL, "conditionTwoValuesV0NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLV0, "conditionTwoValuesNULLV0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLVa1, "conditionTwoValueNULLVa1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1V0, "conditionTwoValuesV1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV0V1, "conditionTwoValueV0V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueVm1V0, "conditionTwoValueVm1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV1Va1, "conditionTwoValueV1Va1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionOr, "conditionOr" );

	//compare with conditionNot
	actualObject = &conditionNot;
	szActualObjectName = "conditionNot";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1NULL, "conditionTwoValuesV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV0NULL, "conditionTwoValuesV0NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLV0, "conditionTwoValuesNULLV0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLVa1, "conditionTwoValueNULLVa1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1V0, "conditionTwoValuesV1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV0V1, "conditionTwoValueV0V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueVm1V0, "conditionTwoValueVm1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV1Va1, "conditionTwoValueV1Va1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionOr, "conditionOr" );

	//compare with conditionOr
	actualObject = &conditionOr;
	szActualObjectName = "conditionOr";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1NULL, "conditionTwoValuesV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV0NULL, "conditionTwoValuesV0NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLV0, "conditionTwoValuesNULLV0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLVa1, "conditionTwoValueNULLVa1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesV1V0, "conditionTwoValuesV1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV0V1, "conditionTwoValueV0V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueVm1V0, "conditionTwoValueVm1V0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueV1Va1, "conditionTwoValueV1Va1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionOr, "conditionOr" );


	return iReturn;
}


/**
 * This method tests if the given condition is not conected to superior
 * conditions or Fib-elements.
 *
 * @param conditionObject1 the condition to check
 * @return the number of errors occured in the test
 */
int testNotConnectedCondition( const cCondition & conditionObject1 ){
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	//check the getNextFibElement() methode
	if ( conditionObject1.getSuperiorCondition() == NULL ){
	
		cout<<"The superior condition pointer for the condition element is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The superior condition pointer for the condition element is not NULL, but "<<
			conditionObject1.getSuperiorCondition() <<" ."<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode
	if ( conditionObject1.getDefiningFibElement() == NULL ){
	
		cout<<"The defining Fib-element pointer for the condition is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The defining Fib-element pointer for the condition is not NULL."<<endl;
		iReturn++;
	}
	
	return iReturn;
}



/**
 * This method tests the copy methods and copyconstructor of the tConditionComparison class.
 *
 * methods tested:
 * 	- cConditionComparison( const cConditionComparison & condition, cCondition * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- cCondition * clone( cCondition * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
template <class tConditionComparison>
	int testCopy( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a simple tConditionComparison"<<endl;

	cout<<"tConditionComparison conditionTwoValues1( NULL, NULL );"<<endl;
	tConditionComparison conditionTwoValues1( NULL, NULL );

	cout<<"tConditionComparison conditionTwoValues1CopyConstruct( conditionTwoValues1 );"<<endl;
	tConditionComparison conditionTwoValues1CopyConstruct( conditionTwoValues1 );

	iReturn += testCompareTwoEqualObjects( conditionTwoValues1CopyConstruct, "conditionTwoValues1CopyConstruct", conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testNotConnectedCondition( conditionTwoValues1CopyConstruct );

	cout<<"cCondition * pUnderConditionComparisons1Clone = conditionTwoValues1CopyConstruct.clone();"<<endl;
	cCondition * pUnderConditionComparisons1Clone = conditionTwoValues1CopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pUnderConditionComparisons1Clone, "pUnderConditionComparisons1Clone", conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testNotConnectedCondition( *pUnderConditionComparisons1Clone );
	delete pUnderConditionComparisons1Clone;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a tConditionComparison with a subfunction, superior condition and defining Fib-element"<<endl;
	
	//condition with defining Fib-element and superior condition
	cout<<"cRoot rootSimple;"<<endl;
	cRoot rootSimple;
	cout<<"tConditionComparison conditionSup( NULL, NULL );"<<endl;
	tConditionComparison conditionSup( NULL, NULL );
	cout<<"cFunctionValue subFunctionValueV1( 1 );"<<endl;
	cFunctionValue subFunctionValueV1( 1 );
	cout<<"cFunctionValue subFunctionValueV2( 2 );"<<endl;
	cFunctionValue subFunctionValueV2( 2 );
	cout<<"tConditionComparison conditionDefFeSc( subFunctionValueV1, subFunctionValueV2, & conditionSup, &rootSimple );"<<endl;
	tConditionComparison conditionDefFeSc( subFunctionValueV1, subFunctionValueV2, & conditionSup, &rootSimple );

	cout<<"tConditionComparison conditionDefFeScCopyConstruct( conditionDefFeSc );"<<endl;
	tConditionComparison conditionDefFeScCopyConstruct( conditionDefFeSc );

	iReturn += testCompareTwoEqualObjects( conditionDefFeScCopyConstruct, "conditionDefFeScCopyConstruct", conditionDefFeSc, "conditionDefFeSc" );
	//check the getDefiningFibElement() methode from tConditionComparison
	if ( conditionDefFeScCopyConstruct.getDefiningFibElement() == &rootSimple ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionDefFeScCopyConstruct.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionDefFeScCopyConstruct.getDefiningFibElement() <<" but should be rootSimple ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from tConditionComparison
	if ( conditionDefFeScCopyConstruct.getSuperiorCondition() == NULL ){
	
		cout<<"The superior condition of the condition correctly "<<
			conditionDefFeScCopyConstruct.getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			conditionDefFeScCopyConstruct.getSuperiorCondition() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	
	cout<<"cCondition * pConditionDefFeUfClone = conditionDefFeScCopyConstruct.clone();"<<endl;
	cCondition * pConditionDefFeUfClone = conditionDefFeScCopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pConditionDefFeUfClone, "pConditionDefFeUfClone", conditionDefFeSc, "conditionDefFeSc" );
	//check the getDefiningFibElement() methode from tConditionComparison
	if ( pConditionDefFeUfClone->getDefiningFibElement() == &rootSimple ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			pConditionDefFeUfClone->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			pConditionDefFeUfClone->getDefiningFibElement() <<" but should be rootSimple ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from tConditionComparison
	if ( pConditionDefFeUfClone->getSuperiorCondition() == NULL ){
	
		cout<<"The superior condition of the condition correctly "<<
			pConditionDefFeUfClone->getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			pConditionDefFeUfClone->getSuperiorCondition() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	delete pConditionDefFeUfClone;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a tConditionComparison with a superior condition and defining Fib-element which will be changed"<<endl;

	//condition with defining Fib-element and superior condition
	cout<<"cRoot rootSimple2;"<<endl;
	cRoot rootSimple2;
	cout<<"tConditionComparison conditionSup2( NULL, NULL );"<<endl;
	tConditionComparison conditionSup2( NULL, NULL );

	cout<<"tConditionComparison conditionDefFeScCopy2Construct( conditionDefFeSc, &conditionSup2, &rootSimple2 );"<<endl;
	tConditionComparison conditionDefFeScCopy2Construct( conditionDefFeSc, &conditionSup2, &rootSimple2 );

	iReturn += testCompareTwoEqualObjects( conditionDefFeScCopy2Construct, "conditionDefFeScCopy2Construct", conditionDefFeSc, "conditionDefFeSc" );
	//check the getDefiningFibElement() methode from tConditionComparison
	if ( conditionDefFeScCopy2Construct.getDefiningFibElement() == &rootSimple2 ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionDefFeScCopy2Construct.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionDefFeScCopy2Construct.getDefiningFibElement() <<" but should be rootSimple2 ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from tConditionComparison
	if ( conditionDefFeScCopy2Construct.getSuperiorCondition() == &conditionSup2 ){
	
		cout<<"The superior condition of the condition correctly "<<
			conditionDefFeScCopy2Construct.getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			conditionDefFeScCopy2Construct.getSuperiorCondition() <<
			" but should be conditionSup2 ."<<endl;
		iReturn++;
	}
	
	cout<<"pConditionDefFeUfClone = conditionDefFeScCopyConstruct.clone( &conditionSup2, &rootSimple2 );"<<endl;
	pConditionDefFeUfClone = conditionDefFeScCopyConstruct.clone( &conditionSup2, &rootSimple2 );

	iReturn += testCompareTwoEqualObjects( *pConditionDefFeUfClone, "pConditionDefFeUfClone", conditionDefFeSc, "conditionDefFeSc" );
	//check the getDefiningFibElement() methode from tConditionComparison
	if ( pConditionDefFeUfClone->getDefiningFibElement() == &rootSimple2 ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			pConditionDefFeUfClone->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			pConditionDefFeUfClone->getDefiningFibElement() <<" but should be rootSimple2 ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from tConditionComparison
	if ( pConditionDefFeUfClone->getSuperiorCondition() == &conditionSup2 ){
	
		cout<<"The superior condition of the condition correctly "<<
			pConditionDefFeUfClone->getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			pConditionDefFeUfClone->getSuperiorCondition() <<
			" but should be conditionSup2 ."<<endl;
		iReturn++;
	}
	delete pConditionDefFeUfClone;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a tConditionComparison with values 2 and 1 for the value subfunction"<<endl;
	
	//condition with defining Fib-element and superior condition
	cout<<"cRoot rootSimpleV2V1;"<<endl;
	cRoot rootSimpleV2V1;
	cout<<"tConditionComparison conditionSup2( NULL, NULL );"<<endl;
	tConditionComparison conditionSu2p( NULL, NULL );
	cout<<"tConditionComparison conditionV2V1( subFunctionValueV2, subFunctionValueV1, & conditionSup2, &rootSimpleV2V1 );"<<endl;
	tConditionComparison conditionV2V1( subFunctionValueV2, subFunctionValueV1, & conditionSup2, &rootSimpleV2V1 );

	cout<<"tConditionComparison conditionV2V1CopyConstruct( conditionV2V1 );"<<endl;
	tConditionComparison conditionV2V1CopyConstruct( conditionV2V1 );

	iReturn += testCompareTwoEqualObjects( conditionV2V1CopyConstruct, "conditionV2V1CopyConstruct", conditionV2V1, "conditionV2V1" );
	//check the getDefiningFibElement() methode from tConditionComparison
	if ( conditionV2V1CopyConstruct.getDefiningFibElement() == &rootSimpleV2V1 ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionV2V1CopyConstruct.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionV2V1CopyConstruct.getDefiningFibElement() <<" but should be rootSimpleV2V1 ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from tConditionComparison
	if ( conditionV2V1CopyConstruct.getSuperiorCondition() == NULL ){
	
		cout<<"The superior condition of the condition correctly "<<
			conditionV2V1CopyConstruct.getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			conditionV2V1CopyConstruct.getSuperiorCondition() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	
	cout<<"cCondition * pConditionV2V1 = conditionV2V1CopyConstruct.clone();"<<endl;
	cCondition * pConditionV2V1 = conditionV2V1CopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pConditionV2V1, "pConditionV2V1", conditionV2V1, "conditionV2V1" );
	//check the getDefiningFibElement() methode from tConditionComparison
	if ( pConditionV2V1->getDefiningFibElement() == &rootSimpleV2V1 ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			pConditionV2V1->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			pConditionV2V1->getDefiningFibElement() <<" but should be rootSimpleV2V1 ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from tConditionComparison
	if ( pConditionV2V1->getSuperiorCondition() == NULL ){
	
		cout<<"The superior condition of the condition correctly "<<
			pConditionV2V1->getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			pConditionV2V1->getSuperiorCondition() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	delete pConditionV2V1;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a tConditionComparison with a NULL and a value subfunction with value 0"<<endl;
	
	//condition with defining Fib-element and superior condition
	cout<<"cRoot rootSimple3;"<<endl;
	cRoot rootSimple3;
	cout<<"tConditionComparison conditionSup3( NULL, NULL );"<<endl;
	tConditionComparison conditionSup3( NULL, NULL );
	cout<<"tConditionComparison conditionNullV0( NULL, new cFunctionValue( 0 ), & conditionSup3, &rootSimple3 );"<<endl;
	tConditionComparison conditionNullV0( NULL, new cFunctionValue( 0 ), & conditionSup3, &rootSimple3 );

	cout<<"tConditionComparison conditionNullV0CopyConstruct( conditionNullV0 );"<<endl;
	tConditionComparison conditionNullV0CopyConstruct( conditionNullV0 );

	iReturn += testCompareTwoEqualObjects( conditionNullV0CopyConstruct, "conditionNullV0CopyConstruct", conditionNullV0, "conditionNullV0" );
	//check the getDefiningFibElement() methode from tConditionComparison
	if ( conditionNullV0CopyConstruct.getDefiningFibElement() == &rootSimple3 ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionNullV0CopyConstruct.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionNullV0CopyConstruct.getDefiningFibElement() <<" but should be rootSimple3 ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from tConditionComparison
	if ( conditionNullV0CopyConstruct.getSuperiorCondition() == NULL ){
	
		cout<<"The superior condition of the condition correctly "<<
			conditionNullV0CopyConstruct.getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			conditionNullV0CopyConstruct.getSuperiorCondition() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	
	cout<<"cCondition * pConditionNullV0 = conditionNullV0CopyConstruct.clone();"<<endl;
	cCondition * pConditionNullV0 = conditionNullV0CopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pConditionNullV0, "pConditionNullV0", conditionNullV0, "conditionNullV0" );
	//check the getDefiningFibElement() methode from tConditionComparison
	if ( pConditionNullV0->getDefiningFibElement() == &rootSimple3 ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			pConditionNullV0->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			pConditionNullV0->getDefiningFibElement() <<" but should be rootSimple3 ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from tConditionComparison
	if ( pConditionNullV0->getSuperiorCondition() == NULL ){
	
		cout<<"The superior condition of the condition correctly "<<
			pConditionNullV0->getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			pConditionNullV0->getSuperiorCondition() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	delete pConditionNullV0;


	return iReturn;
}



/**
 * This method tests a in the xml -format stored tConditionComparison.
 * The condition of the tConditionComparison should be a value condition
 * ( tConditionComparison ).
 *
 * @param szFilename the name of the file wher the tConditionComparison is stored
 * @param ucSubFunction1 if the first subfunction is a NULL pointer (=0), a
 * 	cFunctionValue (=1) or cFunctionVariable (=2)
 * @param ucSubFunction2 if the second subfunction is a NULL pointer (=0), a
 * 	cFunctionValue (=1) or cFunctionVariable (=2)
 * @return the number of errors occured in the test
 */
template <class tConditionComparison>
	int testXmlConditionValue( const string szFilename, unsigned char ucSubFunction1=0,
			unsigned char ucSubFunction2=0 ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored tConditionComparison:"<<endl;
	
	TiXmlDocument xmlDotConditionComparison( szFilename );
	bool loadOkay = xmlDotConditionComparison.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDotConditionComparison );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlHandleRoot(0);

	pXmlElement = xmlHandle.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();
		
		const string szConditionComparisonsElementName = getConditionName<tConditionComparison>();
		if ( szElementName == szConditionComparisonsElementName ){
			cout<<"The root element is correctly named \""<< szConditionComparisonsElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \""<< szConditionComparisonsElementName <<"\"."<<endl;
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
	
	//check the underfunctions
	if ( pXmlElement ) {
		
		string szElementName = pXmlElement->Value();
		const string szSubconditionElementName = ((ucSubFunction1==1)?"value":"variable");
		if ( szElementName == szSubconditionElementName ){
			cout<<"The subfunction is correctly named \""<< szSubconditionElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the subfunction is "<< szElementName <<" and not \""<< szSubconditionElementName <<"\"."<<endl;
			iReturn++;
		}
		
		//check second subfunction
		pXmlElement = pXmlElement->NextSiblingElement();
		//check the underfunctions
		if ( pXmlElement ) {
			
			string szElementName = pXmlElement->Value();
			const string szSubconditionElementName = ((ucSubFunction2==1)?"value":"variable");
			if ( szElementName == szSubconditionElementName ){
				cout<<"The subfunction is correctly named \""<< szSubconditionElementName <<"\". "<<endl;
			
			}else{
				cerr<<"Error: The name of the subfunction is "<< szElementName <<" and not \""<< szSubconditionElementName <<"\"."<<endl;
				iReturn++;
			}
			
		}else{// pXmlElement == NULL ->no root handle
			if ( ucSubFunction2 == 0 ){
				cout<<"Ther is correctly no second subfunction. "<<endl;
			}else{
				cerr<<"Error: No subfunction handle in \""<< szFilename <<"\"."<<endl;
				iReturn++;
			}
		}
	}else{// pXmlElement == NULL ->no root handle
		if ( ucSubFunction1 == 0 ){
			cout<<"Ther is correctly no first subfunction. "<<endl;
		}else{
			cerr<<"Error: No subfunction handle in \""<< szFilename <<"\"."<<endl;
			iReturn++;
		}
	}


	return iReturn;
}



/**
 * This method tests the storeXml() method of the tConditionComparison class.
 * Just storing properties with no underobjects is tested.
 *
 * methods tested:
 * 	- bool storeXml( ostream &stream ) const;
 * 	- cCondition * restoreXml( const TiXmlElement * pXmlElement, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, cCondition * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
template <class tConditionComparison>
	int testStoreXml( unsigned long &ulTestphase ){

	unsigned int iReturn = 0;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an "<<
		getConditionName<tConditionComparison>()<<" condition"<<endl;

	cout<<"tConditionComparison conditionComparison1( NULL, NULL );"<<endl;
	tConditionComparison conditionComparison1( NULL, NULL );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * szXmlConditionComparisonsFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "conditionComparisonNull.xml" );
	ofstream * pFileCondition = new ofstream( szXmlConditionComparisonsFileName );
	
	bool bStoreSuccesfull = conditionComparison1.storeXml( *pFileCondition );
	delete pFileCondition;
	
	if ( ! bStoreSuccesfull ){
	
		cout<<"The data of the tConditionComparison was correctly stored not successfull to the file \""<< szXmlConditionComparisonsFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the tConditionComparison to the file \""<< szXmlConditionComparisonsFileName <<"\" was successfull."<<endl;
		iReturn++;
	}
	iReturn += testXmlConditionValue<tConditionComparison>( szXmlConditionComparisonsFileName );
	
	TiXmlDocument xmlDotConditionComparison( szFileNameBuffer );
	bool loadOkay = xmlDotConditionComparison.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"TiXmlHandle xmlHandle2( &xmlDotConditionComparison ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDotConditionComparison );
		cout<<"tConditionComparison * pUnderConditionComparisons1Loaded = cCondition::restoreXml("<<
			"xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cCondition * pUnderConditionComparisons1Loaded = cCondition::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus != 0 ){
		
			cout<<"The data was loaded not successfull (outStatus="<< outStatus <<"). "<<endl;
		}else{
			cerr<<"Error: Data was loaded not successfull."<<endl;
			iReturn++;
		}
		if ( pUnderConditionComparisons1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionComparisons1Loaded, "pUnderConditionComparisons1Loaded", conditionComparison1, "conditionComparison1" );
			iReturn += testNotConnectedCondition( * pUnderConditionComparisons1Loaded );
			delete pUnderConditionComparisons1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"tConditionComparison conditionSup( NULL, NULL );"<<endl;
		tConditionComparison conditionSup( NULL, NULL );

		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"TiXmlHandle xmlHandle4( &xmlDotConditionComparison ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDotConditionComparison );
		cout<<"tConditionComparison pUnderConditionComparisons1LoadedFull = cCondition::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionComparisons1LoadedFull = cCondition::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &conditionSup, &rootSimple );
		
		if ( outStatus != 0 ){
		
			cout<<"The data was loaded not successfull (outStatus="<< outStatus <<"). "<<endl;
		}else{
			cerr<<"Error: Data was loaded not successfull."<<endl;
			iReturn++;
		}
		if ( pUnderConditionComparisons1LoadedFull ){
			if ( (pUnderConditionComparisons1LoadedFull->getType()) == (getConditionType<tConditionComparison>()) ){
				cout<<"Correctly an "<<getConditionName<tConditionComparison>()<<" condition restored."<<endl;
				//check the first subfunction
				if ( ((tConditionComparison*)pUnderConditionComparisons1LoadedFull)->getFirstSubFunction() == NULL ){
				
					cout<<"The subfunction of the first condition correctly NULL . "<<endl;
				}else{
					cerr<<"Error: The subfunction of the first condition is NULL "<<
						" but should be NULL ."<<endl;
					iReturn++;
				}
				//check the second subfunction
				if ( ((tConditionComparison*)pUnderConditionComparisons1LoadedFull)->getSecondSubFunction() == NULL ){
				
					cout<<"The subfunction of the second condition correctly NULL . "<<endl;
				}else{
					cerr<<"Error: The subfunction of the second condition is NULL "<<
						" but should be NULL ."<<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: Not an "<<getConditionName<tConditionComparison>()<<" condition restored."<<endl;
				iReturn++;
			}
			//check the getDefiningFibElement() methode from tConditionComparison
			if ( pUnderConditionComparisons1LoadedFull->getDefiningFibElement() == &rootSimple ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionComparisons1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionComparisons1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from tConditionComparison
			if ( pUnderConditionComparisons1LoadedFull->getSuperiorCondition() == &conditionSup ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionComparisons1LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionComparisons1LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionComparisons1LoadedFull;
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
		getConditionName<tConditionComparison>()<<" condition with an value 1 and a value 2 subfunction"<<endl;
	
	cout<<"cFunctionValue subFunctionValueV1( 1 );"<<endl;
	cFunctionValue subFunctionValueV1( 1 );
	cout<<"cFunctionValue subFunctionValueV2( 2 );"<<endl;
	cFunctionValue subFunctionValueV2( 2 );
	cout<<"tConditionComparison conditionComparisonTrueFalse( subFunctionValueV1, subFunctionValueV2 );"<<endl;
	tConditionComparison conditionComparisonTrueFalse( subFunctionValueV1, subFunctionValueV2 );
	
	szFileNameBuffer[0] = 0;
	szXmlConditionComparisonsFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "conditionComparisonTrueFalse.xml" );
	pFileCondition = new ofstream( szXmlConditionComparisonsFileName );
	
	bStoreSuccesfull = conditionComparisonTrueFalse.storeXml( *pFileCondition );
	delete pFileCondition;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the tConditionComparison was stored successfull to the file \""<< szXmlConditionComparisonsFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the tConditionComparison to the file \""<< szXmlConditionComparisonsFileName <<"\" failed."<<endl;
		iReturn++;
	}
	iReturn += testXmlConditionValue<tConditionComparison>( szXmlConditionComparisonsFileName, 1, 1 );
	
	TiXmlDocument xmlDotConditionComparisonTrue( szFileNameBuffer );
	loadOkay = xmlDotConditionComparisonTrue.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"TiXmlHandle xmlHandle2( &xmlDotConditionComparisonTrue ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDotConditionComparisonTrue );
		cout<<"tConditionComparison  pUnderConditionComparisons1Loaded = cCondition::restoreXml("<<
			"xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cCondition * pUnderConditionComparisons1Loaded = cCondition::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionComparisons1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionComparisons1Loaded, "pUnderConditionComparisons1Loaded", conditionComparisonTrueFalse, "conditionComparisonTrueFalse" );
			iReturn += testNotConnectedCondition( * pUnderConditionComparisons1Loaded );
			delete pUnderConditionComparisons1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"tConditionComparison conditionSup( NULL, NULL );"<<endl;
		tConditionComparison conditionSup( NULL, NULL );

		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"TiXmlHandle xmlHandle4( &xmlDotConditionComparisonTrue ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDotConditionComparisonTrue );
		cout<<"tConditionComparison pUnderConditionComparisons1LoadedFull = cCondition::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionComparisons1LoadedFull = cCondition::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &conditionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionComparisons1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionComparisons1LoadedFull, "pUnderConditionComparisons1LoadedFull", conditionComparisonTrueFalse, "conditionComparisonTrueFalse" );
			//check the getDefiningFibElement() methode from tConditionComparison
			if ( pUnderConditionComparisons1LoadedFull->getDefiningFibElement() == &rootSimple ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionComparisons1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionComparisons1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from tConditionComparison
			if ( pUnderConditionComparisons1LoadedFull->getSuperiorCondition() == &conditionSup ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionComparisons1LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionComparisons1LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionComparisons1LoadedFull;
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
		getConditionName<tConditionComparison>()<<" condition with an variable and an value subfunction"<<endl;
	
	cout<<"cRoot rootEmpty;"<<endl;
	cRoot rootEmpty;
	cout<<"rootEmpty.setNumberOfInputVariables( 1 );"<<endl;
	rootEmpty.setNumberOfInputVariables( 1 );
	cout<<"pVariable1 = rootEmpty.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 =  rootEmpty.getInputVariable( 1 );
	cout<<"pVariable1->setIntegerValue( 1 );"<<endl;
	pVariable1->setIntegerValue( 1 );
	
	list< cFibVariable * > liDefinedVariablesCorrect;
	liDefinedVariablesCorrect.push_back( pVariable1 );
	
	cout<<"cFunctionVariable subFunctionVariable1( pVariable1 );"<<endl;
	cFunctionVariable subFunctionVariable1( pVariable1 );
	
	cout<<"tConditionComparison conditionTwoValueVm1V0( subFunctionVariable1, subFunctionValueV1 );"<<endl;
	tConditionComparison conditionTwoValueVm1V0( subFunctionVariable1, subFunctionValueV1 );
	
	szFileNameBuffer[0] = 0;
	szXmlConditionComparisonsFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "conditionTwoValueVm1V0.xml" );
	pFileCondition = new ofstream( szXmlConditionComparisonsFileName );
	
	bStoreSuccesfull = conditionTwoValueVm1V0.storeXml( *pFileCondition );
	delete pFileCondition;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the tConditionComparison was stored successfull to the file \""<< szXmlConditionComparisonsFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the tConditionComparison to the file \""<< szXmlConditionComparisonsFileName <<"\" failed."<<endl;
		iReturn++;
	}
	iReturn += testXmlConditionValue<tConditionComparison>( szXmlConditionComparisonsFileName, 2, 1 );
	
	TiXmlDocument xmlDotConditionComparisonFalse( szFileNameBuffer );
	loadOkay = xmlDotConditionComparisonFalse.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables = liDefinedVariablesCorrect;
		cout<<"TiXmlHandle xmlHandle2( &xmlDotConditionComparisonFalse ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDotConditionComparisonFalse );
		cout<<"tConditionComparison * pUnderConditionComparisons1Loaded = cCondition::restoreXml("<<
			"xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cCondition * pUnderConditionComparisons1Loaded = cCondition::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionComparisons1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionComparisons1Loaded, "pUnderConditionComparisons1Loaded", conditionTwoValueVm1V0, "conditionTwoValueVm1V0" );
			iReturn += testNotConnectedCondition( * pUnderConditionComparisons1Loaded );
			delete pUnderConditionComparisons1Loaded;
		}
		if ( liDefinedVariables != liDefinedVariablesCorrect ){
			cerr<<"Error: Defined variables wher changed ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"tConditionComparison conditionSup( NULL, NULL );"<<endl;
		tConditionComparison conditionSup( NULL, NULL );

		outStatus = 0;
		liDefinedVariables = liDefinedVariablesCorrect;
		cout<<"TiXmlHandle xmlHandle4( &xmlDotConditionComparisonFalse ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDotConditionComparisonFalse );
		cout<<"tConditionComparison pUnderConditionComparisons1LoadedFull = cCondition::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionComparisons1LoadedFull = cCondition::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &conditionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionComparisons1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionComparisons1LoadedFull, "pUnderConditionComparisons1LoadedFull", conditionTwoValueVm1V0, "conditionTwoValueVm1V0" );
			//check the getDefiningFibElement() methode from tConditionComparison
			if ( pUnderConditionComparisons1LoadedFull->getDefiningFibElement() == &rootSimple ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionComparisons1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionComparisons1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from tConditionComparison
			if ( pUnderConditionComparisons1LoadedFull->getSuperiorCondition() == &conditionSup ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionComparisons1LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionComparisons1LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionComparisons1LoadedFull;
		}
		if ( liDefinedVariables != liDefinedVariablesCorrect ){
			cerr<<"Error: Defined variables wher changed ."<<endl;
			iReturn++;
		}
	
	}else{
		cerr<<"Error: Failed to load file \""<< szFileNameBuffer <<"\""<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an "<<
		getConditionName<tConditionComparison>()<<" condition with an value -1 and an Null subfunction"<<endl;
	
	cout<<"tConditionComparison conditionTwoValueTrueNull( new cFunctionValue( -1 ), NULL );"<<endl;
	tConditionComparison conditionTwoValueTrueNull( new cFunctionValue( -1 ), NULL );
	
	szFileNameBuffer[0] = 0;
	szXmlConditionComparisonsFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "conditionTwoValueTrueNull.xml" );
	pFileCondition = new ofstream( szXmlConditionComparisonsFileName );
	
	bStoreSuccesfull = conditionTwoValueTrueNull.storeXml( *pFileCondition );
	delete pFileCondition;
	
	if ( ! bStoreSuccesfull ){
	
		cout<<"The data of the tConditionComparison was correctly not stored successfull to the file \""<< szXmlConditionComparisonsFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the tConditionComparison to the file \""<< szXmlConditionComparisonsFileName <<"\" successfull."<<endl;
		iReturn++;
	}
	iReturn += testXmlConditionValue<tConditionComparison>( szXmlConditionComparisonsFileName, 1, 0 );
	
	TiXmlDocument xmlDotConditionComparisonTrueNull( szFileNameBuffer );
	loadOkay = xmlDotConditionComparisonTrueNull.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"TiXmlHandle xmlHandle2( &xmlDotConditionComparisonTrueNull ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDotConditionComparisonTrueNull );
		cout<<"tConditionComparison * pUnderConditionComparisons1Loaded = cCondition::restoreXml("<<
			"xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cCondition * pUnderConditionComparisons1Loaded = cCondition::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus != 0 ){
		
			cout<<"The data was loaded not successfull (outStatus="<< outStatus <<"). "<<endl;
		}else{
			cerr<<"Error: Data was loaded not successfull."<<endl;
			iReturn++;
		}
		if ( pUnderConditionComparisons1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionComparisons1Loaded, "pUnderConditionComparisons1Loaded", conditionTwoValueTrueNull, "conditionTwoValueTrueNull" );
			iReturn += testNotConnectedCondition( * pUnderConditionComparisons1Loaded );
			delete pUnderConditionComparisons1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"tConditionComparison conditionSup( NULL, NULL );"<<endl;
		tConditionComparison conditionSup( NULL, NULL );

		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"TiXmlHandle xmlHandle4( &xmlDotConditionComparisonTrueNull ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDotConditionComparisonTrueNull );
		cout<<"tConditionComparison pUnderConditionComparisons1LoadedFull = cCondition::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionComparisons1LoadedFull = cCondition::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &conditionSup, &rootSimple );
		
		if ( outStatus != 0 ){
		
			cout<<"The data was loaded not successfull (outStatus="<< outStatus <<"). "<<endl;
		}else{
			cerr<<"Error: Data was loaded not successfull."<<endl;
			iReturn++;
		}
		if ( pUnderConditionComparisons1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionComparisons1LoadedFull, "pUnderConditionComparisons1LoadedFull", conditionTwoValueTrueNull, "conditionTwoValueTrueNull" );
			//check the getDefiningFibElement() methode from tConditionComparison
			if ( pUnderConditionComparisons1LoadedFull->getDefiningFibElement() == &rootSimple ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionComparisons1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionComparisons1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from tConditionComparison
			if ( pUnderConditionComparisons1LoadedFull->getSuperiorCondition() == &conditionSup ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionComparisons1LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionComparisons1LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionComparisons1LoadedFull;
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
 * 	- cCondition * restore( cReadBits & iBitStream, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, const cDomainSingle * pInValueDomain, const cDomainSingle * pInDomainVariable, cCondition * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
template <class tConditionComparison>
		int testStore( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an vale 1 and 2 value subfunction"<<endl;

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
	
	cout<<"cFunctionValue underFunctionValueV1( 1.0 );"<<endl;
	cFunctionValue underFunctionValueV1( 1.0 );
	cout<<"cFunctionValue underFunctionValueV2( 2.0 );"<<endl;
	cFunctionValue underFunctionValueV2( 2.0 );
	
	
	cout<<"cConditionTrue subFunctionTrue;"<<endl;
	cConditionTrue subFunctionTrue;
	cout<<"cConditionFalse subFunctionFalse;"<<endl;
	cConditionFalse subFunctionFalse;
	
	cout<<"tConditionComparison conditionTwoValues1( underFunctionValueV1, underFunctionValueV2, NULL, &root );"<<endl;
	tConditionComparison conditionTwoValues1( underFunctionValueV1, underFunctionValueV2, NULL, &root );

	//test get compressed size
	unsigned int uiCompressedSize = 4 + 2 * (2 + 16);
	if ( (unsigned int)(conditionTwoValues1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			conditionTwoValues1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "conditionTwoValuesTrue.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = (char)0x00;
	unsigned char cRestBitPosition = 0;
	cout<<"conditionTwoValues1.store( *pFile, cRestBits, cRestBitPosition );"<<endl;
	bool bStoreSuccesfull = conditionTwoValues1.store( *pFile, cRestBit, cRestBitPosition );
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
	short sNumberOfRestBitCorrect = 0;
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
	const char tConditionComparison1[] = { (char)(0x40 | getTypeBit<tConditionComparison>()), (char)0x00, (char)0x00, (char)0x02, (char)0x00, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, tConditionComparison1, 6 );

	
	ifstream * pFileIn = new ifstream( szFileNameBuffer );
	if ( (pFileIn != NULL) && ( pFileIn->good() ) ){
		
		cReadBits iBitStream2( * pFileIn );
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"tConditionComparison pUnderConditionComparisons1Loaded = cCondition::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cCondition * pUnderConditionComparisons1Loaded = cCondition::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionComparisons1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionComparisons1Loaded, "pUnderConditionComparisons1Loaded", conditionTwoValues1, "conditionTwoValues1" );
			iReturn += testNotConnectedCondition( * pUnderConditionComparisons1Loaded );
			delete pUnderConditionComparisons1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"tConditionComparison conditionSup( NULL, NULL );"<<endl;
		tConditionComparison conditionSup( NULL, NULL );
		
		delete pFileIn;

		pFileIn = new ifstream( szFileNameBuffer );
		cReadBits iBitStream4( * pFileIn );
		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"tConditionComparison pUnderConditionComparisons1LoadedFull = cCondition::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionComparisons1LoadedFull = cCondition::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&conditionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionComparisons1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionComparisons1LoadedFull, "pUnderConditionComparisons1LoadedFull", conditionTwoValues1, "conditionTwoValues1" );
			//check the getDefiningFibElement() methode from tConditionComparison
			if ( pUnderConditionComparisons1LoadedFull->getDefiningFibElement() == &rootSimple ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionComparisons1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionComparisons1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from tConditionComparison
			if ( pUnderConditionComparisons1LoadedFull->getSuperiorCondition() == &conditionSup ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionComparisons1LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionComparisons1LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionComparisons1LoadedFull;
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

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with different domains"<<endl;

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
	
	cout<<"cFunctionValue underFunctionValueV3( 3.0 );"<<endl;
	cFunctionValue underFunctionValueV3( 3.0 );
	cout<<"cFunctionVariable underFunctionVaribleV2( pVariable2 );"<<endl;
	cFunctionVariable underFunctionVaribleV2( pVariable2 );

	cout<<"tConditionComparison conditionTwoValuesValueV3VariableV2( underFunctionValueV3, underFunctionVaribleV2, NULL, &root );"<<endl;
	tConditionComparison conditionTwoValuesValueV3VariableV2( underFunctionValueV3, underFunctionVaribleV2, NULL, &root );

	//test get compressed size
	uiCompressedSize = 4 + 8 + 6;
	if ( (unsigned int)(conditionTwoValuesValueV3VariableV2.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			conditionTwoValuesValueV3VariableV2.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "conditionTwoValuesTrue.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x00;
	cRestBitPosition = 0;
	cout<<"conditionTwoValuesValueV3VariableV2.store( *pFile, cRestBits, cRestBitPosition );"<<endl;
	bStoreSuccesfull = conditionTwoValuesValueV3VariableV2.store( *pFile, cRestBit, cRestBitPosition );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = (char)0x00;
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
	const char tConditionComparisonTrueFalse[] = { (char)(0xC0 | getTypeBit<tConditionComparison>()), (char)0x90, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, tConditionComparisonTrueFalse, 3 );
	
	pFileIn = new ifstream( szFileNameBuffer );
	if ( (pFileIn != NULL) && ( pFileIn->good() ) ){
		
		cReadBits iBitStream2( * pFileIn );
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables = liDefinedVariablesOrg;
		cout<<"tConditionComparison pUnderConditionComparisons1Loaded = cCondition::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cCondition * pUnderConditionComparisons1Loaded = cCondition::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionComparisons1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionComparisons1Loaded, "pUnderConditionComparisons1Loaded", conditionTwoValuesValueV3VariableV2, "conditionTwoValuesValueV3VariableV2" );
			iReturn += testNotConnectedCondition( * pUnderConditionComparisons1Loaded );
			delete pUnderConditionComparisons1Loaded;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: Defined variables wher changed ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"tConditionComparison conditionSup( NULL, NULL );"<<endl;
		tConditionComparison conditionSup( NULL, NULL );
		
		delete pFileIn;

		pFileIn = new ifstream( szFileNameBuffer );
		cReadBits iBitStream4( * pFileIn );
		outStatus = 0;
		liDefinedVariables = liDefinedVariablesOrg;
		cout<<"tConditionComparison pUnderConditionComparisons1LoadedFull = cCondition::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionComparisons1LoadedFull = cCondition::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&conditionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionComparisons1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionComparisons1LoadedFull, "pUnderConditionComparisons1LoadedFull", conditionTwoValuesValueV3VariableV2, "conditionTwoValuesValueV3VariableV2" );
			//check the getDefiningFibElement() methode from tConditionComparison
			if ( pUnderConditionComparisons1LoadedFull->getDefiningFibElement() == &rootSimple ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionComparisons1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionComparisons1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from tConditionComparison
			if ( pUnderConditionComparisons1LoadedFull->getSuperiorCondition() == &conditionSup ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionComparisons1LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionComparisons1LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionComparisons1LoadedFull;
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


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with given restbit"<<endl;

	cout<<"tConditionComparison conditionTwoValues2( underFunctionVaribleV2, underFunctionValueV3, NULL, &root );"<<endl;
	tConditionComparison conditionTwoValues2( underFunctionVaribleV2, underFunctionValueV3, NULL, &root );
	
	//test get compressed size
	if ( (unsigned int)(conditionTwoValues2.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			conditionTwoValues2.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "conditionTwoValues2.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x01;
	cRestBitPosition = 2;
	cout<<"conditionTwoValues2.store( *pFile, cRestBit, cRestBitPosition ); "<<endl;
	bStoreSuccesfull = conditionTwoValues2.store( *pFile, cRestBit, cRestBitPosition );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = (char)0x00;
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
	char cTypeBit = getTypeBit<tConditionComparison>();
	cTypeBit = cTypeBit << 2;
	//test stored data   000011 00 0010  01 xxxx 01
	const char szUnderConditionComparisons2[] = { (char)(0x41 | cTypeBit), (char)0xC2, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, szUnderConditionComparisons2, 3 );


	pFileIn = new ifstream( szFileNameBuffer );
	if ( (pFileIn != NULL) && ( pFileIn->good() ) ){
		
		char cBuffer;
		cReadBits iBitStream2( * pFileIn );
		iBitStream2.readBits( &cBuffer, 2 );
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables = liDefinedVariablesOrg;
		cout<<"tConditionComparison pUnderConditionComparisons3Loaded = cCondition::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cCondition * pUnderConditionComparisons3Loaded = cCondition::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionComparisons3Loaded ){
			const int iErrorsEqual = testCompareTwoEqualObjects(
				* pUnderConditionComparisons3Loaded, "pUnderConditionComparisons3Loaded", conditionTwoValues2, "conditionTwoValues2" );
			iReturn += testNotConnectedCondition( * pUnderConditionComparisons3Loaded );
			if ( iErrorsEqual != 0 ){
				cerr<<"Error: Loaded condition not equal."<<endl;
			}
			iReturn += iErrorsEqual;
			delete pUnderConditionComparisons3Loaded;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: Defined variables wher changed ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"tConditionComparison conditionSup( NULL, NULL );"<<endl;
		tConditionComparison conditionSup( NULL, NULL );
		
		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer );
		cReadBits iBitStream4( * pFileIn );
		iBitStream4.readBits( &cBuffer, 2 );
		outStatus = 0;
		liDefinedVariables = liDefinedVariablesOrg;
		cout<<"tConditionComparison pUnderConditionComparisons3LoadedFull = cCondition::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionComparisons3LoadedFull = cCondition::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&conditionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionComparisons3LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionComparisons3LoadedFull, "pUnderConditionComparisons3LoadedFull", conditionTwoValues2, "conditionTwoValues2" );
			//check the getDefiningFibElement() methode from tConditionComparison
			if ( pUnderConditionComparisons3LoadedFull->getDefiningFibElement() == &rootSimple ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionComparisons3LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionComparisons3LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from tConditionComparison
			if ( pUnderConditionComparisons3LoadedFull->getSuperiorCondition() == &conditionSup ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionComparisons3LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionComparisons3LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionComparisons3LoadedFull;
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
 * This method tests the subcondtion methods of the tConditionComparison class.
 *
 * methods tested:
 * 	- cCondition * getFirstSubFunction();
 * 	- bool setFirstSubFunction( cUnderFunction * pInSubFunction, bool bDeleteOld=true );
 * 	- bool setFirstSubFunction( const cUnderFunction & pInSubFunction, bool bDeleteOld=true );
 * 	- cCondition * getSecondSubFunction();
 * 	- bool setSecondSubFunction( cUnderFunction * pInSubFunction, bool bDeleteOld=true );
 * 	- bool setSecondSubFunction( const cUnderFunction & pInSubFunction, bool bDeleteOld=true );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
template <class tConditionComparison>
	int testSubFunction( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the subcondtion methods ( get*SubFunction() and set*SubFunction() )"<<endl;
	
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
	
	
	vector< cFibVariable * > vecVariablen;
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
	
	cout<<"pVariable1->setValue( 1.0 );"<<endl;
	pVariable1->setValue( 1.0 );
	vecVariablen.push_back( pVariable1 );
	cout<<"pVariable2->setValue( 2.0 );"<<endl;
	pVariable2->setValue( 2.0 );
	vecVariablen.push_back( pVariable2 );
	cout<<"pVariable3->setValue( 3.0 );"<<endl;
	pVariable3->setValue( 3.0 );
	vecVariablen.push_back( pVariable3 );
	cout<<"pVariable4->setValue( 4.0 );"<<endl;
	pVariable4->setValue( 4.0 );
	vecVariablen.push_back( pVariable4 );
	cout<<"pVariable5->setValue( 5.5 );"<<endl;
	pVariable5->setValue( 5.5 );
	vecVariablen.push_back( pVariable5 );
	cout<<"pVariable6->setValue( 4.0 );"<<endl;
	pVariable6->setValue( 4.0 );
	vecVariablen.push_back( pVariable6 );
	cout<<"pVariable7->setValue( -1.0 );"<<endl;
	pVariable7->setValue( -1.0 );
	vecVariablen.push_back( pVariable7 );
	cout<<"pVariable8->setValue( 2.5 );"<<endl;
	pVariable8->setValue( 2.5 );
	vecVariablen.push_back( pVariable8 );
	cout<<"pVariable9->setValue( 2.51 );"<<endl;
	pVariable9->setValue( 2.51 );
	vecVariablen.push_back( pVariable9 );
	cout<<"pVariable10->setValue( 2.49 );"<<endl;
	pVariable10->setValue( 2.49 );
	vecVariablen.push_back( pVariable10 );
	
	cout<<"cFunctionValue funValue1( 1 );"<<endl;
	cFunctionValue funValue1( 1 );
	cout<<"cFunctionVariable funVar1( pVariable1 );"<<endl;
	cFunctionVariable funVar1( pVariable1 );
	cout<<"cFunctionValue funSubValue1( 2 );"<<endl;
	cFunctionValue funSubValue1( 2 );
	cout<<"cFunctionAbs funAbs( & funSubValue1 );"<<endl;
	cFunctionAbs funAbs( & funSubValue1 );
	
	cUnderFunction * pFirstSubFunction = NULL;
	double dFirstSubFunctionValue = 0;
	bool bFirstSubFunctionIsPointer = true;
	cUnderFunction * pSecondSubFunction = NULL;
	double dSecondSubFunctionValue = 0;
	bool bSecondSubFunctionIsPointer = true;
	cUnderFunction * pOldFunction = NULL;
	cout<<"pConditionComparison = new tConditionComparison( "<<
		pFirstSubFunction<<", "<<pSecondSubFunction<<", NULL, &point  );"<<endl;
	tConditionComparison * pConditionComparison = new tConditionComparison( NULL, NULL, NULL, &point );
	bool bIsValid = false;
	
	for ( unsigned int uiIteration = 1; uiIteration <= 1024; uiIteration++ ){
		
		cout<<endl;
		if ( (rand() % 16) == 0 ){
			//create new condition
			if ( pConditionComparison ){
				delete pConditionComparison;
				pConditionComparison = NULL;
				pFirstSubFunction = NULL;
				pSecondSubFunction = NULL;
				dFirstSubFunctionValue = 0;
				dSecondSubFunctionValue = 0;
				bFirstSubFunctionIsPointer = true;
				bSecondSubFunctionIsPointer = true;
			}
			if ( rand() % 4 ){
				if ( rand() % 2 ){
					pFirstSubFunction = new cFunctionValue( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					dFirstSubFunctionValue = pFirstSubFunction->getValue();
					cout<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionValue( "<<
						pFirstSubFunction->getValue()<<" );"<<endl;
				}else{
					const size_t uiChoosenVariable = rand() % vecVariablen.size();
					pFirstSubFunction = new cFunctionVariable( vecVariablen[ uiChoosenVariable ]  );
					dFirstSubFunctionValue = pFirstSubFunction->getValue();
					cout<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionVariable( pVariable"<<
						(uiChoosenVariable + 1)<<" );"<<endl;
				}
			}
			if ( rand() % 4 ){
				if ( rand() % 2 ){
					pSecondSubFunction = new cFunctionValue( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					dSecondSubFunctionValue = pSecondSubFunction->getValue();
					cout<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionValue( "<<
						dSecondSubFunctionValue<<" );"<<endl;
				}else{
					const size_t uiChoosenVariable = rand() % vecVariablen.size();
					pSecondSubFunction = new cFunctionVariable( vecVariablen[ uiChoosenVariable ]  );
					dSecondSubFunctionValue = pSecondSubFunction->getValue();
					cout<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionVariable( pVariable"<<
						(uiChoosenVariable + 1)<<" );"<<endl;
				}
			}
			cout<<"pConditionComparison = new tConditionComparison( "<<
				pFirstSubFunction<<", "<<pSecondSubFunction<<", NULL, &point  );"<<endl;
			pConditionComparison = new tConditionComparison( pFirstSubFunction, pSecondSubFunction, NULL, &point );
		}else{
			switch ( rand() % 20 ){
				case 0:{
					//set first subfunction
					pFirstSubFunction = new cFunctionValue( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					cout<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionValue( "<<
						pFirstSubFunction->getValue()<<" );"<<endl;
					dFirstSubFunctionValue = pFirstSubFunction->getValue();
					bFirstSubFunctionIsPointer = true;
					cout<<"pConditionComparison->setFirstSubFunction( "<<pFirstSubFunction<<" );"<<endl;
					pConditionComparison->setFirstSubFunction( pFirstSubFunction );
				}break;
				case 1:{
					//set first subfunction
					pFirstSubFunction = &funValue1;
					dFirstSubFunctionValue = pFirstSubFunction->getValue();
					bFirstSubFunctionIsPointer = false;
					cout<<"pConditionComparison->setFirstSubFunction( funValue1 );"<<endl;
					pConditionComparison->setFirstSubFunction( funValue1 );
				}break;
				case 2:{
					//set first subfunction
					const size_t uiChoosenVariable = rand() % vecVariablen.size();
					pFirstSubFunction = new cFunctionVariable( vecVariablen[ uiChoosenVariable ]  );
					dFirstSubFunctionValue = pFirstSubFunction->getValue();
					cout<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionVariable( pVariable"<<
						(uiChoosenVariable + 1)<<" );"<<endl;
					dFirstSubFunctionValue = pFirstSubFunction->getValue();
					bFirstSubFunctionIsPointer = true;
					cout<<"pConditionComparison->setFirstSubFunction( "<<pFirstSubFunction<<" );"<<endl;
					pConditionComparison->setFirstSubFunction( pFirstSubFunction );
				}break;
				case 3:{
					//set first subfunction
					pFirstSubFunction = &funVar1;
					dFirstSubFunctionValue = pFirstSubFunction->getValue();
					bFirstSubFunctionIsPointer = false;
					cout<<"pConditionComparison->setFirstSubFunction( funVar1 );"<<endl;
					pConditionComparison->setFirstSubFunction( funVar1 );
				}break;
				case 4:{
					//set first subfunction
					cout<<"pConditionComparison->setFirstSubFunction( NULL );"<<endl;
					pConditionComparison->setFirstSubFunction( NULL );
				}break;
				
				//delete old = false
				case 5:{
					//set first subfunction
					pFirstSubFunction = new cFunctionValue( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					dFirstSubFunctionValue = pFirstSubFunction->getValue();
					cout<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionValue( "<<
						pFirstSubFunction->getValue()<<" );"<<endl;
					cout<<"pFirstSubFunction("<<pFirstSubFunction<<") = new funValue1();"<<endl;
					dFirstSubFunctionValue = pFirstSubFunction->getValue();
					bFirstSubFunctionIsPointer = true;
					pOldFunction = pConditionComparison->getFirstSubFunction();
					cout<<"pConditionComparison->setFirstSubFunction( "<<pFirstSubFunction<<", false );"<<endl;
					pConditionComparison->setFirstSubFunction( pFirstSubFunction, false );
				}break;
				case 6:{
					//set first subfunction
					const size_t uiChoosenVariable = rand() % vecVariablen.size();
					pFirstSubFunction = new cFunctionVariable( vecVariablen[ uiChoosenVariable ]  );
					dFirstSubFunctionValue = pFirstSubFunction->getValue();
					cout<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionVariable( pVariable"<<
						(uiChoosenVariable + 1)<<" );"<<endl;
					dFirstSubFunctionValue = pFirstSubFunction->getValue();
					bFirstSubFunctionIsPointer = true;
					pOldFunction = pConditionComparison->getFirstSubFunction();
					cout<<"pConditionComparison->setFirstSubFunction( "<<pFirstSubFunction<<", false );"<<endl;
					pConditionComparison->setFirstSubFunction( pFirstSubFunction, false );
				}break;
				case 7:{
					//set first subfunction
					cout<<"pConditionComparison->setFirstSubFunction( NULL, false );"<<endl;
					pConditionComparison->setFirstSubFunction( NULL, false );
				}break;
				
			
				case 8:{
					//set second subfunction
					pSecondSubFunction = new cFunctionValue( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					dSecondSubFunctionValue = pSecondSubFunction->getValue();
					cout<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionValue( "<<
						pSecondSubFunction->getValue()<<" );"<<endl;
					bSecondSubFunctionIsPointer = true;
					cout<<"pConditionComparison->setSecondSubFunction( "<<pSecondSubFunction<<" );"<<endl;
					pConditionComparison->setSecondSubFunction( pSecondSubFunction );
				}break;
				case 9:{
					//set second subfunction
					pSecondSubFunction = &funValue1;
					dSecondSubFunctionValue = pSecondSubFunction->getValue();
					bSecondSubFunctionIsPointer = false;
					cout<<"pConditionComparison->setSecondSubFunction( funValue1 );"<<endl;
					pConditionComparison->setSecondSubFunction( funValue1 );
				}break;
				case 10:{
					//set second subfunction
					const size_t uiChoosenVariable = rand() % vecVariablen.size();
					pSecondSubFunction = new cFunctionVariable( vecVariablen[ uiChoosenVariable ]  );
					dSecondSubFunctionValue = pSecondSubFunction->getValue();
					cout<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionVariable( pVariable"<<
						(uiChoosenVariable + 1)<<" );"<<endl;
					bSecondSubFunctionIsPointer = true;
					cout<<"pConditionComparison->setSecondSubFunction( "<<pSecondSubFunction<<" );"<<endl;
					pConditionComparison->setSecondSubFunction( pSecondSubFunction );
				}break;
				case 11:{
					//set second subfunction
					pSecondSubFunction = &funVar1;
					dSecondSubFunctionValue = pSecondSubFunction->getValue();
					bSecondSubFunctionIsPointer = false;
					cout<<"pConditionComparison->setSecondSubFunction( funVar1 );"<<endl;
					pConditionComparison->setSecondSubFunction( funVar1 );
				}break;
				case 12:{
					//set second subfunction
					cout<<"pConditionComparison->setSecondSubFunction( NULL );"<<endl;
					pConditionComparison->setSecondSubFunction( NULL );
				}break;
				
				//delete old = false
				case 13:{
					//set second subfunction
					pSecondSubFunction = new cFunctionValue( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					dSecondSubFunctionValue = pSecondSubFunction->getValue();
					cout<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionValue( "<<
						pSecondSubFunction->getValue()<<" );"<<endl;
					bSecondSubFunctionIsPointer = true;
					pOldFunction = pConditionComparison->getSecondSubFunction();
					cout<<"pConditionComparison->setSecondSubFunction( "<<pSecondSubFunction<<", false );"<<endl;
					pConditionComparison->setSecondSubFunction( pSecondSubFunction, false );
				}break;
				case 14:{
					//set second subfunction
					const size_t uiChoosenVariable = rand() % vecVariablen.size();
					pSecondSubFunction = new cFunctionVariable( vecVariablen[ uiChoosenVariable ]  );
					dSecondSubFunctionValue = pSecondSubFunction->getValue();
					cout<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionVariable( pVariable"<<
						(uiChoosenVariable + 1)<<" );"<<endl;
					bSecondSubFunctionIsPointer = true;
					pOldFunction = pConditionComparison->getSecondSubFunction();
					cout<<"pConditionComparison->setSecondSubFunction( "<<pSecondSubFunction<<", false );"<<endl;
					pConditionComparison->setSecondSubFunction( pSecondSubFunction, false );
				}break;
				case 15:{
					//set second subfunction
					cout<<"pConditionComparison->setSecondSubFunction( NULL, false );"<<endl;
					pConditionComparison->setSecondSubFunction( NULL, false );
				}break;
				
				
				//create subsubfunctions
				case 16:{
					//set first subfunction
					cFunctionValue funSubValue( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					pFirstSubFunction = new cFunctionAbs ( & funSubValue );
					dFirstSubFunctionValue = pFirstSubFunction->getValue();
					cout<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionAbs( cFunctionValue( "<<
						funSubValue.getValue()<<" ) );"<<endl;
					bFirstSubFunctionIsPointer = true;
					cout<<"pConditionComparison->setFirstSubFunction( "<<pFirstSubFunction<<" );"<<endl;
					pConditionComparison->setFirstSubFunction( pFirstSubFunction );
				}break;
				case 17:{
					//set second subfunction
					cFunctionValue funSubValue( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					pSecondSubFunction = new cFunctionAbs ( & funSubValue );
					dSecondSubFunctionValue = pSecondSubFunction->getValue();
					cout<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionAbs( cFunctionValue( "<<
						funSubValue.getValue()<<" ) );"<<endl;
					bSecondSubFunctionIsPointer = true;
					cout<<"pConditionComparison->setSecondSubFunction( "<<pSecondSubFunction<<" );"<<endl;
					pConditionComparison->setSecondSubFunction( pSecondSubFunction );
				}break;
				case 18:{
					//set first subfunction
					pFirstSubFunction = &funAbs;
					dFirstSubFunctionValue = funAbs.getValue();
					bFirstSubFunctionIsPointer = false;
					cout<<"pConditionComparison->setFirstSubFunction( funAbs );"<<endl;
					pConditionComparison->setFirstSubFunction( funAbs );
				}break;
				case 19:{
					//set second subfunction
					pSecondSubFunction = &funAbs;
					dSecondSubFunctionValue = funAbs.getValue();
					bSecondSubFunctionIsPointer = false;
					cout<<"pConditionComparison->setSecondSubFunction( funAbs );"<<endl;
					pConditionComparison->setSecondSubFunction( funAbs );
				}break;
				
			}
			if ( pOldFunction ){
				delete pOldFunction;
				pOldFunction = NULL;
			}
		}
		if ( ( pFirstSubFunction != NULL ) && ( pSecondSubFunction != NULL ) ){
			bIsValid = true;
		}else{
			bIsValid = false;
		}
		
		//check the getValue() methode from tConditionComparison
		if ( bIsValid ){
			if ( pConditionComparison->getValue() == getCorrectValue<tConditionComparison>(
					dFirstSubFunctionValue, dSecondSubFunctionValue ) ){
		
				cout<<"The condition value is correctly "<<
					(pConditionComparison->getValue()?"true":"false") <<" . "<<endl;
			}else{
				cerr<<"Error: The condition value is "<<
					(pConditionComparison->getValue()?"true":"false") <<" but should be "<<
					(pConditionComparison->getValue()?"false":"true") <<" ( first="<<
					dFirstSubFunctionValue<<", second="<<
					dSecondSubFunctionValue<<" )."<<endl;
				iReturn++;
			}
		}else{// ! bIsValid
			if ( pConditionComparison->getValue() == false ){
		
				cout<<"The condition value is correctly "<<
					(pConditionComparison->getValue()?"true":"false") <<", because it is not valid. "<<endl;
			}else{
				cerr<<"Error: The condition value is "<<
					(pConditionComparison->getValue()?"true":"false") <<" but should be "<<
					(pConditionComparison->getValue()?"false":"true") <<
					", because it is not valid."<<endl;
				iReturn++;
			}
		}
		if ( bFirstSubFunctionIsPointer ){
			//check the getFirstSubFunction() methode from tConditionComparison
			if ( pConditionComparison->getFirstSubFunction() == pFirstSubFunction ){
			
				cout<<"The first subfunction of the condition correctly "<<
					pConditionComparison->getFirstSubFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The first subfunction of the condition is "<<
					pConditionComparison->getFirstSubFunction() <<
					" but should be "<< pFirstSubFunction <<" ."<<endl;
				iReturn++;
			}
		}else{
			//check the getFirstSubFunction() methode from tConditionComparison
			if ( *(pConditionComparison->getFirstSubFunction()) == *pFirstSubFunction ){
			
				cout<<"The first subfunction of the condition correctly equal to "<<
					pConditionComparison->getFirstSubFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The first subfunction of the condition is "<<
					pConditionComparison->getFirstSubFunction() <<
					" but should be equal to "<< pFirstSubFunction <<" ."<<endl;
				iReturn++;
			}
		}
		if ( bSecondSubFunctionIsPointer ){
			//check the getFirstSubFunction() methode from tConditionComparison
			if ( pConditionComparison->getSecondSubFunction() == pSecondSubFunction ){
			
				cout<<"The second subfunction of the condition correctly "<<
					pConditionComparison->getSecondSubFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The second subfunction of the condition is "<<
					pConditionComparison->getSecondSubFunction() <<
					" but should be "<< pSecondSubFunction <<" ."<<endl;
				iReturn++;
			}
		}else{
			//check the getFirstSubFunction() methode from tConditionComparison
			if ( *(pConditionComparison->getSecondSubFunction()) == *pSecondSubFunction ){
			
				cout<<"The second subfunction of the condition correctly equal to "<<
					pConditionComparison->getSecondSubFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The second subfunction of the condition is "<<
					pConditionComparison->getSecondSubFunction() <<
					" but should be equal to "<< pSecondSubFunction <<" ."<<endl;
				iReturn++;
			}
		}
		//check the isValid() methode from tConditionComparison
		if ( pConditionComparison->isValid() == bIsValid ){
		
			cout<<"The condition is correctly "<<(bIsValid?"":"not ")<<"valid . "<<endl;
		}else{
			cerr<<"Error: The condition is "<<(bIsValid?"not ":"")<<"valid ."<<endl;
			iReturn++;
		}
		//check defining Fib-Element of sub and subsubfunctions
		if ( pConditionComparison->getFirstSubFunction() != NULL ){
			if ( pConditionComparison->getFirstSubFunction()->getDefiningFibElement() == &point ){
			
				cout<<"The definig fib-element of the first subfunction is point."<<endl;
			}else{
				cerr<<"Error: The definig fib-element of the first subfunction is not point."<<endl;
				iReturn++;
			}
			if ( pConditionComparison->getFirstSubFunction()->getNumberOfUnderFunctions() == 1 ){
				
				cFunctionOneValue * pSubFunction = ((cFunctionOneValue*)(pConditionComparison->getFirstSubFunction()));
				
				if ( pSubFunction->getUnderFunction()->getDefiningFibElement() == &point ){
				
					cout<<"The definig fib-element of the first subsubfunction is point."<<endl;
				}else{
					cerr<<"Error: The definig fib-element of the first subsubfunction is not point."<<endl;
					iReturn++;
				}
			}
		}
		if ( pConditionComparison->getSecondSubFunction() != NULL ){
			if ( pConditionComparison->getSecondSubFunction()->getDefiningFibElement() == &point ){
			
				cout<<"The definig fib-element of the second subfunction is point."<<endl;
			}else{
				cerr<<"Error: The definig fib-element of the second subfunction is not point."<<endl;
				iReturn++;
			}
			if ( pConditionComparison->getSecondSubFunction()->getNumberOfUnderFunctions() == 1 ){
				
				cFunctionOneValue * pSubFunction = ((cFunctionOneValue*)(pConditionComparison->getSecondSubFunction()));
				
				if ( pSubFunction->getUnderFunction()->getDefiningFibElement() == &point ){
				
					cout<<"The definig fib-element of the second subsubfunction is point."<<endl;
				}else{
					cerr<<"Error: The definig fib-element of the second subsubfunction is not point."<<endl;
					iReturn++;
				}
			}
		}
		
	}
	if ( pConditionComparison ){
		delete pConditionComparison;
		pConditionComparison = NULL;
		pFirstSubFunction = NULL;
		pSecondSubFunction = NULL;
	}
	
	return iReturn;
}




/**
 * This method tests the variable methods of the tConditionComparison class.
 *
 * methods tested:
 * 	- bool isUsedVariable( const cFibVariable * variable ) const;
 * 	- set<cFibVariable*> getUsedVariables();
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
template <class tConditionComparison>
		int testVariable( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the variable methods"<<endl;


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
	
	
	vector< cFibVariable * > vecVariablen;
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
	vecVariablen.push_back( pVariable1 );
	cout<<"pVariable2(="<<pVariable2<<")->setValue( 2.0 );"<<endl;
	pVariable2->setValue( 2.0 );
	vecVariablen.push_back( pVariable2 );
	cout<<"pVariable3(="<<pVariable3<<")->setValue( 3.0 );"<<endl;
	pVariable3->setValue( 3.0 );
	vecVariablen.push_back( pVariable3 );
	cout<<"pVariable4(="<<pVariable4<<")->setValue( 4.0 );"<<endl;
	pVariable4->setValue( 4.0 );
	vecVariablen.push_back( pVariable4 );
	cout<<"pVariable5(="<<pVariable5<<")->setValue( 5.5 );"<<endl;
	pVariable5->setValue( 5.5 );
	vecVariablen.push_back( pVariable5 );
	cout<<"pVariable6(="<<pVariable6<<")->setValue( 4.0 );"<<endl;
	pVariable6->setValue( 4.0 );
	vecVariablen.push_back( pVariable6 );
	cout<<"pVariable7(="<<pVariable7<<")->setValue( -1.0 );"<<endl;
	pVariable7->setValue( -1.0 );
	vecVariablen.push_back( pVariable7 );
	cout<<"pVariable8(="<<pVariable8<<")->setValue( 2.5 );"<<endl;
	pVariable8->setValue( 2.5 );
	vecVariablen.push_back( pVariable8 );
	cout<<"pVariable9(="<<pVariable9<<")->setValue( 2.51 );"<<endl;
	pVariable9->setValue( 2.51 );
	vecVariablen.push_back( pVariable9 );
	cout<<"pVariable10(="<<pVariable10<<")->setValue( 2.49 );"<<endl;
	pVariable10->setValue( 2.49 );
	vecVariablen.push_back( pVariable10 );
	
	cUnderFunction * pFirstSubFunction = NULL;
	double dFirstSubFunctionValue = 0;
	cFibVariable * pVariableFirstSubFunction = NULL;
	
	cUnderFunction * pSecondSubFunction = NULL;
	double dSecondSubFunctionValue = 0;
	cFibVariable * pVariableSecondSubFunction = NULL;
	
	cout<<"pConditionComparison = new tConditionComparison( "<<
		pFirstSubFunction<<", "<<pSecondSubFunction<<", NULL, &point  );"<<endl;
	tConditionComparison * pConditionComparison = new tConditionComparison( NULL, NULL, NULL, &point );
	bool bIsValid = false;
	
	set< cFibVariable* > setCorrectUsedVariables;
	
	for ( unsigned int uiIteration = 1; uiIteration <= 64; uiIteration++ ){
		
		cout<<endl;
		if ( (rand() % 16) == 0 ){
			//create new condition
			if ( pConditionComparison ){
				delete pConditionComparison;
				pConditionComparison = NULL;
				pFirstSubFunction = NULL;
				pSecondSubFunction = NULL;
				dFirstSubFunctionValue = 0;
				dSecondSubFunctionValue = 0;
				pVariableFirstSubFunction = NULL;
				pVariableSecondSubFunction = NULL;
			}
			if ( rand() % 4 ){
				if ( rand() % 4 == 0 ){
					pFirstSubFunction = new cFunctionValue( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					dFirstSubFunctionValue = pFirstSubFunction->getValue();
					cout<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionValue( "<<
						pFirstSubFunction->getValue()<<" );"<<endl;
					pVariableFirstSubFunction = NULL;
				}else{
					const size_t uiChoosenVariable = rand() % vecVariablen.size();
					pFirstSubFunction = new cFunctionVariable( vecVariablen[ uiChoosenVariable ]  );
					dFirstSubFunctionValue = pFirstSubFunction->getValue();
					cout<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionVariable( pVariable"<<
						(uiChoosenVariable + 1)<<" );"<<endl;
					pVariableFirstSubFunction = vecVariablen[ uiChoosenVariable ];
				}
			}
			if ( rand() % 4 ){
				if ( rand() % 4 == 0 ){
					pSecondSubFunction = new cFunctionValue( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					dSecondSubFunctionValue = pSecondSubFunction->getValue();
					cout<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionValue( "<<
						dSecondSubFunctionValue<<" );"<<endl;
					pVariableSecondSubFunction = NULL;
				}else{
					const size_t uiChoosenVariable = rand() % vecVariablen.size();
					pSecondSubFunction = new cFunctionVariable( vecVariablen[ uiChoosenVariable ]  );
					dSecondSubFunctionValue = pSecondSubFunction->getValue();
					cout<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionVariable( pVariable"<<
						(uiChoosenVariable + 1)<<" );"<<endl;
					pVariableSecondSubFunction = vecVariablen[ uiChoosenVariable ];
				}
			}
			cout<<"pConditionComparison = new tConditionComparison( "<<
				pFirstSubFunction<<", "<<pSecondSubFunction<<", NULL, &point  );"<<endl;
			pConditionComparison = new tConditionComparison( pFirstSubFunction, pSecondSubFunction, NULL, &point );
		}else if ( rand() % 2 ){//change subfunction
			
			if ( rand() % 4 ){
				if ( rand() % 2 ){
					//set first subfunction to variable
					const size_t uiChoosenVariable = rand() % vecVariablen.size();
					pFirstSubFunction = new cFunctionVariable( vecVariablen[ uiChoosenVariable ]  );
					dFirstSubFunctionValue = pFirstSubFunction->getValue();
					cout<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionVariable( pVariable"<<
						(uiChoosenVariable + 1)<<" );"<<endl;
					cout<<"pConditionComparison->setFirstSubFunction( "<<pFirstSubFunction<<" );"<<endl;
					pConditionComparison->setFirstSubFunction( pFirstSubFunction );
					pVariableFirstSubFunction = vecVariablen[ uiChoosenVariable ];
				}else{
					//set second subfunction to variable
					const size_t uiChoosenVariable = rand() % vecVariablen.size();
					pSecondSubFunction = new cFunctionVariable( vecVariablen[ uiChoosenVariable ]  );
					dSecondSubFunctionValue = pSecondSubFunction->getValue();
					cout<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionVariable( pVariable"<<
						(uiChoosenVariable + 1)<<" );"<<endl;
					cout<<"pConditionComparison->setSecondSubFunction( "<<pSecondSubFunction<<" );"<<endl;
					pConditionComparison->setSecondSubFunction( pSecondSubFunction );
					pVariableSecondSubFunction = vecVariablen[ uiChoosenVariable ];
				}
			}else{//change to value
				if ( rand() % 2 ){
					//set first subfunction to value
					pFirstSubFunction = new cFunctionValue( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					cout<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionValue( "<<
						pFirstSubFunction->getValue()<<" );"<<endl;
					dFirstSubFunctionValue = pFirstSubFunction->getValue();
					cout<<"pConditionComparison->setFirstSubFunction( "<<pFirstSubFunction<<" );"<<endl;
					pConditionComparison->setFirstSubFunction( pFirstSubFunction );
					pVariableFirstSubFunction = NULL;
				}else{
					//set second subfunction to value
					pSecondSubFunction = new cFunctionValue( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					dSecondSubFunctionValue = pSecondSubFunction->getValue();
					cout<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionValue( "<<
						pSecondSubFunction->getValue()<<" );"<<endl;
					cout<<"pConditionComparison->setSecondSubFunction( "<<pSecondSubFunction<<" );"<<endl;
					pConditionComparison->setSecondSubFunction( pSecondSubFunction );
					pVariableSecondSubFunction = NULL;
				}
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
					const size_t uiVariableToReplaceWith = rand() % vecVariablen.size();
					
					cout<<"pConditionComparison->replaceVariable( "<<(*itrToReplaceVariable)<<
						", "<< vecVariablen[ uiVariableToReplaceWith ]<<" );"<<endl;
					const bool bVariableReplaced = pConditionComparison->replaceVariable(
						(*itrToReplaceVariable), vecVariablen[ uiVariableToReplaceWith ] );
					if ( bVariableReplaced ){
					
						cout<<"The variable was correctly replaced. "<<endl;
					}else{
						cerr<<"Error: The variable was not replaced. "<<endl;
						iReturn++;
					}
					//update values
					if ( pVariableFirstSubFunction == (*itrToReplaceVariable) ){
						dFirstSubFunctionValue = vecVariablen[ uiVariableToReplaceWith ]->getValue();
						pVariableFirstSubFunction = vecVariablen[ uiVariableToReplaceWith ];
					}
					if ( pVariableSecondSubFunction == (*itrToReplaceVariable) ){
						dSecondSubFunctionValue = vecVariablen[ uiVariableToReplaceWith ]->getValue();
						pVariableSecondSubFunction = vecVariablen[ uiVariableToReplaceWith ];
					}
					
				}else if ( rand() % 2 ){
					//replace not used variable
					if ( setCorrectUsedVariables.empty() ){
						//no variable to replace -> skip
						continue;
					}
					//choose variable to replace
					size_t uiVariableToReplace = rand() % vecVariablen.size();
					if ( setCorrectUsedVariables.find( vecVariablen[ uiVariableToReplace ] )
							!= setCorrectUsedVariables.end() ){
						//variable used skip
						continue;
					}
					cout<<endl<<"replace not used variable: "<<endl;
					const size_t uiVariableToReplaceWith = rand() % vecVariablen.size();
					
					cout<<"pConditionComparison->replaceVariable( "<<
						vecVariablen[ uiVariableToReplace ]<<", "<<
						vecVariablen[ uiVariableToReplaceWith ]<<" );"<<endl;
					const bool bVariableReplaced = pConditionComparison->replaceVariable(
						vecVariablen[ uiVariableToReplace ], vecVariablen[ uiVariableToReplaceWith ] );
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
						const size_t uiVariableToReplaceWith = rand() % vecVariablen.size();
						
						cout<<"pConditionComparison->replaceVariable( NULL,"<<
							vecVariablen[ uiVariableToReplaceWith ]<<" );"<<endl;
						const bool bVariableReplaced = pConditionComparison->replaceVariable(
							NULL, vecVariablen[ uiVariableToReplaceWith ] );
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
						const size_t uiVariableToReplace = rand() % vecVariablen.size();
						
						cout<<"pConditionComparison->replaceVariable( "<<
							vecVariablen[ uiVariableToReplace ]<<", NULL );"<<endl;
						const bool bVariableReplaced = pConditionComparison->replaceVariable(
							vecVariablen[ uiVariableToReplace ], NULL );
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
				set< cFibVariable* >::const_iterator itrToReplaceVariable =
					setCorrectUsedVariables.begin();
				for ( ; ( itrToReplaceVariable != setCorrectUsedVariables.end() ) &&
						( uiVariableToReplace != 0 );
						itrToReplaceVariable++, uiVariableToReplace-- ){
					//nothing to do
				}
				(*itrToReplaceVariable)->setValue( ((double)(rand() % (256 * 256))) / 256.0 );
				//update values
				if ( pVariableFirstSubFunction == (*itrToReplaceVariable) ){
					dFirstSubFunctionValue = (*itrToReplaceVariable)->getValue();
				}
				if ( pVariableSecondSubFunction == (*itrToReplaceVariable) ){
					dSecondSubFunctionValue = (*itrToReplaceVariable)->getValue();
				}
			}
		}
		setCorrectUsedVariables.clear();
		if ( pVariableFirstSubFunction ){
			setCorrectUsedVariables.insert( pVariableFirstSubFunction );
		}
		if ( pVariableSecondSubFunction ){
			setCorrectUsedVariables.insert( pVariableSecondSubFunction );
		}
		
		if ( ( pFirstSubFunction != NULL ) && ( pSecondSubFunction != NULL ) ){
			bIsValid = true;
		}else{
			bIsValid = false;
		}
		
		//check the isUsedVariable() methode from tConditionComparison
		for ( vector< cFibVariable * >::const_iterator itrVariable = vecVariablen.begin();
				itrVariable != vecVariablen.end(); itrVariable++ ){
			
			const bool bShouldBeUsedVariable = setCorrectUsedVariables.find(
					*itrVariable ) != setCorrectUsedVariables.end();
			
			cout<<"pConditionComparison->isUsedVariable( "<<(*itrVariable)<<" )"<<endl;
			if ( pConditionComparison->isUsedVariable( *itrVariable ) == bShouldBeUsedVariable ){
			
				cout<<"The variable "<<(*itrVariable)<<" is correctly "<<
					(bShouldBeUsedVariable?"":"not ")<<"used in the condition element. "<<endl;
			}else{
				cerr<<"Error: The variable "<<(*itrVariable)<<" is "<<
					(bShouldBeUsedVariable?"not ":"")<<"used in the condition element. "<<endl;
				iReturn++;
			}
		}
		//check getUsedVariables()
		cout<<"setUsedVariables = pConditionComparison->getUsedVariables(); "<<endl;
		set<cFibVariable*> setUsedVariables = pConditionComparison->getUsedVariables();
		if ( setUsedVariables == setCorrectUsedVariables ){
		
			cout<<"The correct used variables wher given back. "<<endl;
		}else{
			cerr<<"Error: Not correct used variables wher given back. "<<endl;
			setCorrectUsedVariables = setUsedVariables;
			iReturn++;
		}
		
		//check the getValue() methode from tConditionComparison
		if ( bIsValid ){
			if ( pConditionComparison->getValue() == getCorrectValue<tConditionComparison>(
					dFirstSubFunctionValue, dSecondSubFunctionValue ) ){
		
				cout<<"The condition value is correctly "<<
					(pConditionComparison->getValue()?"true":"false") <<" . "<<endl;
			}else{
				cerr<<"Error: The condition value is "<<
					(pConditionComparison->getValue()?"true":"false") <<" but should be "<<
					(pConditionComparison->getValue()?"false":"true") <<" ( first="<<
					dFirstSubFunctionValue<<", second="<<
					dSecondSubFunctionValue<<" )."<<endl;
				iReturn++;
			}
		}else{// ! bIsValid
			if ( pConditionComparison->getValue() == false ){
		
				cout<<"The condition value is correctly "<<
					(pConditionComparison->getValue()?"true":"false") <<", because it is not valid. "<<endl;
			}else{
				cerr<<"Error: The condition value is "<<
					(pConditionComparison->getValue()?"true":"false") <<" but should be "<<
					(pConditionComparison->getValue()?"false":"true") <<
					", because it is not valid."<<endl;
				iReturn++;
			}
		}
		
		//check the isValid() methode from tConditionComparison
		if ( pConditionComparison->isValid() == bIsValid ){
		
			cout<<"The condition is correctly "<<(bIsValid?"":"not ")<<"valid . "<<endl;
		}else{
			cerr<<"Error: The condition is "<<(bIsValid?"not ":"")<<"valid ."<<endl;
			iReturn++;
		}
	}
	if ( pConditionComparison ){
		delete pConditionComparison;
		pConditionComparison = NULL;
		pFirstSubFunction = NULL;
		pSecondSubFunction = NULL;
	}
	
	return iReturn;
}



/**
 * This method tests the variable methods of the tConditionComparison class.
 *
 * methods tested:
 * 	- void setDefiningFibElement( cFibElement *fibElement=NULL, bool bCheckDomains=true );
 * 	- cFibElement * getDefiningFibElement() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
template <class tConditionComparison>
		int testDefiningFibElement( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for the defining Fib-element"<<endl;
	
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
	
	cout<<"cFunctionValue funSubValue1( 2 );"<<endl;
	cFunctionValue funSubValue1( 2 );
	cout<<"cFunctionAbs funAbs( & funSubValue1 );"<<endl;
	cFunctionAbs funAbs( & funSubValue1 );
	
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
	
	cUnderFunction * pFirstSubFunction = NULL;
	double dFirstSubFunctionValue = 0;
	cUnderFunction * pSecondSubFunction = NULL;
	double dSecondSubFunctionValue = 0;
	cFibElement * pDefiningFibElement = &point;
	cout<<"pConditionComparison = new tConditionComparison( "<<
		pFirstSubFunction<<", "<<pSecondSubFunction<<", NULL, &point="<<
		pDefiningFibElement<<" );"<<endl;
	tConditionComparison * pConditionComparison = new tConditionComparison( NULL, NULL, NULL, pDefiningFibElement );
	bool bIsValid = false;
	
	for ( unsigned int uiIteration = 1; uiIteration <= 256; uiIteration++ ){
		
		cout<<endl;
		if ( (rand() % 16) == 0 ){
			//create new condition
			if ( pConditionComparison ){
				delete pConditionComparison;
				pConditionComparison = NULL;
				pFirstSubFunction = NULL;
				pSecondSubFunction = NULL;
				dFirstSubFunctionValue = 0;
				dSecondSubFunctionValue = 0;
			}
			if ( rand() % 4 ){
				//set first subfunction
				cFunctionValue funSubValue( domFunValues.round(
					((double)(rand() % (256 * 256))) / 256.0 ) );
				pFirstSubFunction = new cFunctionAbs ( & funSubValue );
				dFirstSubFunctionValue = pFirstSubFunction->getValue();
				cout<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionAbs( cFunctionValue( "<<
					funSubValue.getValue()<<" ) );"<<endl;
			}
			if ( rand() % 4 ){
				//set second subfunction
				cFunctionValue funSubValue( domFunValues.round(
					((double)(rand() % (256 * 256))) / 256.0 ) );
				pSecondSubFunction = new cFunctionAbs ( & funSubValue );
				dSecondSubFunctionValue = pSecondSubFunction->getValue();
				cout<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionAbs( cFunctionValue( "<<
					funSubValue.getValue()<<" ) );"<<endl;
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
			cout<<"pConditionComparison = new tConditionComparison( "<<
				pFirstSubFunction<<", "<<pSecondSubFunction<<", NULL, "<<
				pDefiningFibElement<<"  );"<<endl;
			pConditionComparison = new tConditionComparison( pFirstSubFunction, pSecondSubFunction, NULL, pDefiningFibElement );
		}else{
			switch ( rand() % 5 ){
				//create subsubfunctions
				case 0:{
					//set first subfunction
					cFunctionValue funSubValue( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					pFirstSubFunction = new cFunctionAbs ( & funSubValue );
					dFirstSubFunctionValue = pFirstSubFunction->getValue();
					cout<<"pFirstSubFunction("<<pFirstSubFunction<<") = new cFunctionAbs( cFunctionValue( "<<
						funSubValue.getValue()<<" ) );"<<endl;
					cout<<"pConditionComparison->setFirstSubFunction( "<<pFirstSubFunction<<" );"<<endl;
					pConditionComparison->setFirstSubFunction( pFirstSubFunction );
				}break;
				case 1:{
					//set second subfunction
					cFunctionValue funSubValue( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					pSecondSubFunction = new cFunctionAbs ( & funSubValue );
					dSecondSubFunctionValue = pSecondSubFunction->getValue();
					cout<<"pSecondSubFunction("<<pSecondSubFunction<<") = new cFunctionAbs( cFunctionValue( "<<
						funSubValue.getValue()<<" ) );"<<endl;
					pConditionComparison->setSecondSubFunction( pSecondSubFunction );
				}break;
				case 2:{
					//set first subfunction
					pFirstSubFunction = &funAbs;
					dFirstSubFunctionValue = funAbs.getValue();
					cout<<"pConditionComparison->setFirstSubFunction( funAbs );"<<endl;
					pConditionComparison->setFirstSubFunction( funAbs );
				}break;
				case 3:{
					//set second subfunction
					pSecondSubFunction = &funAbs;
					dSecondSubFunctionValue = funAbs.getValue();
					cout<<"pConditionComparison->setSecondSubFunction( funAbs );"<<endl;
					pConditionComparison->setSecondSubFunction( funAbs );
				}break;
				case 4:{
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
					cout<<"pConditionComparison->setDefiningFibElement( "<<pDefiningFibElement<<", "<<
						(bCheckValues?"true":"false")<<" );"<<endl;
					pConditionComparison->setDefiningFibElement( pDefiningFibElement, bCheckValues );
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
		if ( ( pFirstSubFunction != NULL ) && ( pSecondSubFunction != NULL ) ){
			bIsValid = pConditionComparison->getFirstSubFunction()->isValid() &&
				pConditionComparison->getSecondSubFunction()->isValid();
		}else{
			bIsValid = false;
		}
		
		//check the getValue() methode from tConditionComparison
		if ( ( pFirstSubFunction != NULL ) && ( pSecondSubFunction != NULL ) ){
			if ( pConditionComparison->getValue() == getCorrectValue<tConditionComparison>(
					dFirstSubFunctionValue, dSecondSubFunctionValue ) ){
		
				cout<<"The condition value is correctly "<<
					(pConditionComparison->getValue()?"true":"false") <<" . "<<endl;
			}else{
				cerr<<"Error: The condition value is "<<
					(pConditionComparison->getValue()?"true":"false") <<" but should be "<<
					(pConditionComparison->getValue()?"false":"true") <<" ( first="<<
					dFirstSubFunctionValue<<", second="<<
					dSecondSubFunctionValue<<" )."<<endl;
				iReturn++;
			}
		}else{// ! bIsValid
			if ( pConditionComparison->getValue() == false ){
		
				cout<<"The condition value is correctly "<<
					(pConditionComparison->getValue()?"true":"false") <<", because it is not valid. "<<endl;
			}else{
				cerr<<"Error: The condition value is "<<
					(pConditionComparison->getValue()?"true":"false") <<" but should be "<<
					(pConditionComparison->getValue()?"false":"true") <<
					", because it is not valid."<<endl;
				iReturn++;
			}
		}
		//check the isValid() methode from tConditionComparison
		if ( pConditionComparison->isValid() == bIsValid ){
		
			cout<<"The condition is correctly "<<(bIsValid?"":"not ")<<"valid . "<<endl;
		}else{
			cerr<<"Error: The condition is "<<(bIsValid?"not ":"")<<"valid ."<<endl;
			iReturn++;
		}
		//check defining Fib-Element of sub and subsubfunctions
		if ( pConditionComparison->getFirstSubFunction() != NULL ){
			if ( pConditionComparison->getFirstSubFunction()->getDefiningFibElement() == pDefiningFibElement ){
			
				cout<<"The definig fib-element of the first subfunction is "<<
					pDefiningFibElement<<"."<<endl;
			}else{
				cerr<<"Error: The definig fib-element of the first subfunction is not "<<
					pDefiningFibElement<<"."<<endl;
				iReturn++;
			}
			if ( pConditionComparison->getFirstSubFunction()->getNumberOfUnderFunctions() == 1 ){
				
				cFunctionOneValue * pSubFunction = ((cFunctionOneValue*)(pConditionComparison->getFirstSubFunction()));
				
				if ( pSubFunction->getUnderFunction()->getDefiningFibElement() == pDefiningFibElement ){
				
					cout<<"The definig fib-element of the first subsubfunction is "<<
						pDefiningFibElement<<"."<<endl;
				}else{
					cerr<<"Error: The definig fib-element of the first subsubfunction is not "<<
						pDefiningFibElement<<"."<<endl;
					iReturn++;
				}
			}
		}
		if ( pConditionComparison->getSecondSubFunction() != NULL ){
			if ( pConditionComparison->getSecondSubFunction()->getDefiningFibElement() == pDefiningFibElement ){
			
				cout<<"The definig fib-element of the second subfunction is "<<
					pDefiningFibElement<<"."<<endl;
			}else{
				cerr<<"Error: The definig fib-element of the second subfunction is not "<<
					pDefiningFibElement<<"."<<endl;
				iReturn++;
			}
			if ( pConditionComparison->getSecondSubFunction()->getNumberOfUnderFunctions() == 1 ){
				
				cFunctionOneValue * pSubFunction = ((cFunctionOneValue*)(pConditionComparison->getSecondSubFunction()));
				
				if ( pSubFunction->getUnderFunction()->getDefiningFibElement() == pDefiningFibElement ){
				
					cout<<"The definig fib-element of the second subsubfunction is "<<
						pDefiningFibElement<<"."<<endl;
				}else{
					cerr<<"Error: The definig fib-element of the second subsubfunction is not "<<
						pDefiningFibElement<<"."<<endl;
					iReturn++;
				}
			}
		}
	}
	if ( pConditionComparison ){
		delete pConditionComparison;
		pConditionComparison = NULL;
		pFirstSubFunction = NULL;
		pSecondSubFunction = NULL;
	}
	

	return iReturn;
}












