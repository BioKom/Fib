/**
 * @file tConditionTwoValue
 * file name: tConditionTwoValue.cpp
 * @author Betti Oesterholz
 * @date 13.05.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the child class of class cConditionTwoValue.
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
 * This file contains the test for the class cConditionTwoValue, which
 * represents a true condition.
 *
 *
 * What's tested of class cConditionTwoValue:
 * 	- cConditionTwoValue( cCondition * pInFirstSubCondition, cCondition * pInSecondSubCondition, cCondition * pInSuperiorCondition, cFibElement * pInDefiningFibElement )
 * 	- cConditionTwoValue( const cCondition & inFirstSubCondition, const cCondition & inSecondSubCondition, cCondition * pInSuperiorCondition = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cConditionTwoValue( const cConditionTwoValue & condition, cCondition * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- ~cConditionTwoValue();
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
 * 	- cCondition * clone( cCondition * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL) const;
 * 	- cCondition * getFirstSubCondition();
 * 	- bool setFirstSubCondition( cCondition * pInSubCondition, bool bDeleteOld=true );
 * 	- bool setFirstSubCondition( const cCondition & pInSubCondition, bool bDeleteOld=true );
 * 	- cCondition * getSecondSubCondition();
 * 	- bool setSecondSubCondition( cCondition * pInSubCondition, bool bDeleteOld=true );
 * 	- bool setSecondSubCondition( const cCondition & pInSubCondition, bool bDeleteOld=true );
 *
 * conditions tested:
 * 	- cConditionOr
 * 	- cConditionAnd
 * 	- cConditionXor
 */
/*
History:
13.05.2011  Oesterholz  created
09.10.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/

#include "version.h"

#include "cConditionTwoValue.h"
#include "cConditionOr.h"
#include "cConditionAnd.h"
#include "cConditionXor.h"
#include "cConditionTrue.h"
#include "cConditionFalse.h"
#include "cConditionNot.h"
#include "cConditionGreater.h"
#include "cFunctionValue.h"
#include "cFunctionVariable.h"
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

template <class tConditionTwoValue>
	int testCostructor( unsigned long &ulTestphase );
template <class tConditionTwoValue>
	int testEqual( unsigned long &ulTestphase );
template <class tConditionTwoValue>
	int testCopy( unsigned long &ulTestphase );
template <class tConditionTwoValue>
	int testStoreXml( unsigned long &ulTestphase );
template <class tConditionTwoValue>
	int testStore( unsigned long &ulTestphase );
template <class tConditionTwoValue>
	int testSubCondition( unsigned long &ulTestphase );
template <class tConditionTwoValue>
	int testVariable( unsigned long &ulTestphase );
template <class tConditionTwoValue>
	int testDefiningFibElement( unsigned long &ulTestphase );


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	cout<<endl<<"Running Test for cConditionTwoValue methods"<<endl;
	cout<<      "==========================================="<<endl;
	cout<<      "==========================================="<<endl;

	cout<<endl<<"Running Test for cConditionOr methods"<<endl;
	cout<<      "====================================="<<endl;
	
	iReturn += testCostructor< cConditionOr >( ulTestphase );
	iReturn += testEqual< cConditionOr >( ulTestphase );
	iReturn += testCopy< cConditionOr >( ulTestphase );
	iReturn += testStoreXml< cConditionOr >( ulTestphase );
	iReturn += testStore< cConditionOr >( ulTestphase );
	iReturn += testSubCondition< cConditionOr >( ulTestphase );
	iReturn += testVariable< cConditionOr >( ulTestphase );
	iReturn += testDefiningFibElement< cConditionOr >( ulTestphase );


	cout<<endl<<endl<<"Running Test for cConditionAnd methods"<<endl;
	cout<<            "======================================"<<endl;
	
	iReturn += testCostructor< cConditionAnd >( ulTestphase );
	iReturn += testEqual< cConditionAnd >( ulTestphase );
	iReturn += testCopy< cConditionAnd >( ulTestphase );
	iReturn += testStoreXml< cConditionAnd >( ulTestphase );
	iReturn += testStore< cConditionAnd >( ulTestphase );
	iReturn += testSubCondition< cConditionAnd >( ulTestphase );
	iReturn += testVariable< cConditionAnd >( ulTestphase );
	iReturn += testDefiningFibElement< cConditionAnd >( ulTestphase );


	cout<<endl<<endl<<"Running Test for cConditionXor methods"<<endl;
	cout<<            "======================================"<<endl;
	
	iReturn += testCostructor< cConditionXor >( ulTestphase );
	iReturn += testEqual< cConditionXor >( ulTestphase );
	iReturn += testCopy< cConditionXor >( ulTestphase );
	iReturn += testStoreXml< cConditionXor >( ulTestphase );
	iReturn += testStore< cConditionXor >( ulTestphase );
	iReturn += testSubCondition< cConditionXor >( ulTestphase );
	iReturn += testVariable< cConditionXor >( ulTestphase );
	iReturn += testDefiningFibElement< cConditionXor >( ulTestphase );



	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}


/**
 * @param bFirstSubCondition the value of the first subcondition
 * @param bFirstSubCondition the value of the second subcondition
 * @return false
 */
template <class tConditionTwoValue>
		bool getCorrectValue( bool bFirstSubCondition, bool bSecondSubCondition ){
	
	return false;
}


/**
 * @param bFirstSubCondition the value of the first subcondition
 * @param bFirstSubCondition the value of the second subcondition
 * @return if bFirstSubCondition or bSecondSubCondition is true true, else false
 */
template <> bool getCorrectValue< cConditionOr >(
		bool bFirstSubCondition, bool bSecondSubCondition ){
	
	return (bFirstSubCondition || bSecondSubCondition);
}


/**
 * @param bFirstSubCondition the value of the first subcondition
 * @param bFirstSubCondition the value of the second subcondition
 * @return if bFirstSubCondition and bSecondSubCondition is true true, else false
 */
template <> bool getCorrectValue< cConditionAnd >(
		bool bFirstSubCondition, bool bSecondSubCondition ){
	
	return (bFirstSubCondition && bSecondSubCondition);
}


/**
 * @param bFirstSubCondition the value of the first subcondition
 * @param bFirstSubCondition the value of the second subcondition
 * @return if exactly one of bFirstSubCondition or bSecondSubCondition is
 * 	true true, else false
 */
template <> bool getCorrectValue< cConditionXor >(
		bool bFirstSubCondition, bool bSecondSubCondition ){
	
	return (bFirstSubCondition && ( ! bSecondSubCondition )) ||
		(( ! bFirstSubCondition ) && bSecondSubCondition );
}



/**
 * This template returns the name condition of the type of the template
 * parameter.
 *
 * @return ""
 */
template <class tConditionTwoValue> string getConditionName(){
	
	return "";
}

/**
 * This template returns the name condition of the type of the template
 * parameter.
 *
 * @return "or"
 */
template <> string getConditionName< cConditionOr >(){
	
	return "or";
}

/**
 * This template returns the name condition of the type of the template
 * parameter.
 *
 * @return "or"
 */
template <> string getConditionName< cConditionAnd >(){
	
	return "and";
}

/**
 * This template returns the name condition of the type of the template
 * parameter.
 *
 * @return "or"
 */
template <> string getConditionName< cConditionXor >(){
	
	return "xor";
}


/**
 * This template returns the type number of the condition of the type of
 * the template parameter.
 *
 * @return -1
 */
template <class tConditionTwoValue> unsignedIntFib getConditionType(){
	
	return -1;
}

/**
 * This template returns the type number of the condition of the type of
 * the template parameter.
 *
 * @return CONDITION_OR
 */
template <> unsignedIntFib getConditionType< cConditionOr >(){
	
	return cCondition::CONDITION_OR;
}

/**
 * This template returns the type number of the condition of the type of
 * the template parameter.
 *
 * @return CONDITION_AND
 */
template <> unsignedIntFib getConditionType< cConditionAnd >(){
	
	return cCondition::CONDITION_AND;
}

/**
 * This template returns the type number of the condition of the type of
 * the template parameter.
 *
 * @return CONDITION_XOR
 */
template <> unsignedIntFib getConditionType< cConditionXor >(){
	
	return cCondition::CONDITION_XOR;
}


/**
 * This template returns the type bits of the condition of the type of
 * the template parameter.
 *
 * @return 0
 */
template <class tConditionTwoValue> char getTypeBit(){

	return (char)0x00;
}

/**
 * This template returns the type bits of the condition of the type of
 * the template parameter.
 *
 * @return (char)0x02
 */
template <> char getTypeBit<cConditionOr>(){

	return (char)0x02;
}

/**
 * This template returns the type bits of the condition of the type of
 * the template parameter.
 *
 * @return (char)0x03
 */
template <> char getTypeBit<cConditionAnd>(){

	return (char)0x03;
}

/**
 * This template returns the type bits of the condition of the type of
 * the template parameter.
 *
 * @return (char)0x04
 */
template <> char getTypeBit<cConditionXor>(){

	return (char)0x04;
}





/**
 * This method tests the constructor of the cConditionTwoValue class.
 *
 * methods tested:
 * 	- cConditionTwoValue( cCondition * pInFirstSubCondition, cCondition * pInSecondSubCondition, cCondition * pInSuperiorCondition, cFibElement * pInDefiningFibElement )
 * 	- cConditionTwoValue( const cCondition & inFirstSubCondition, const cCondition & inSecondSubCondition, cCondition * pInSuperiorCondition = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- ~cConditionTwoValue();
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
template <class tConditionTwoValue>
	int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<"cRoot rootEmpty;"<<endl;
	cRoot rootEmpty;
	cout<<"rootEmpty.setNumberOfInputVariables( 10 );"<<endl;
	rootEmpty.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 =  rootEmpty.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 =  rootEmpty.getInputVariable( 1 );
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty tConditionTwoValue condition"<<endl;

	cout<<"tConditionTwoValue conditionTwoValues1( NULL, NULL );"<<endl;
	tConditionTwoValue conditionTwoValues1( NULL, NULL );
	cFibElement * pDefiningFibElement = NULL;
	cCondition * pSuperiorCondition = NULL;
	cCondition * pFirstSubCondition = NULL;
	cCondition * pSecondSubCondition = NULL;
	unsigned long ulTimeNeed = 1;
	unsigned long ulCompressedSize = 4;
 
	//check the getValue() methode from tConditionTwoValue
	if ( conditionTwoValues1.getValue() == getCorrectValue< tConditionTwoValue >( false, false ) ){
	
		cout<<"The condition value is correctly "<<
			(conditionTwoValues1.getValue()?"true":"false") <<" . "<<endl;
	}else{
		cerr<<"Error: The condition value is "<<
			(conditionTwoValues1.getValue()?"true":"false") <<" but shouldn't be ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from tConditionTwoValue
	if ( conditionTwoValues1.getDefiningFibElement() == pDefiningFibElement ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionTwoValues1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionTwoValues1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from tConditionTwoValue
	if ( conditionTwoValues1.getSuperiorCondition() == pSuperiorCondition ){
	
		cout<<"The superior condition of the condition correctly "<<
			conditionTwoValues1.getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			conditionTwoValues1.getSuperiorCondition() <<
			" but should be "<< pSuperiorCondition <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstSubCondition() methode from tConditionTwoValue
	if ( conditionTwoValues1.getFirstSubCondition() == pFirstSubCondition ){
	
		cout<<"The first subcondition of the condition correctly "<<
			conditionTwoValues1.getFirstSubCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The first subcondition of the condition is "<<
			conditionTwoValues1.getFirstSubCondition() <<
			" but should be "<< pFirstSubCondition <<" ."<<endl;
		iReturn++;
	}
	//check the getSecondSubCondition() methode from tConditionTwoValue
	if ( conditionTwoValues1.getSecondSubCondition() == pSecondSubCondition ){
	
		cout<<"The second subcondition of the condition correctly "<<
			conditionTwoValues1.getSecondSubCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The second subcondition of the condition is "<<
			conditionTwoValues1.getSecondSubCondition() <<
			" but should be "<< pSecondSubCondition <<" ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from tConditionTwoValue
	if ( ! conditionTwoValues1.isValid() ){
	
		cout<<"The condition is correctly not valid . "<<endl;
	}else{
		cerr<<"Error: The condition is valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from tConditionTwoValue
	if ( conditionTwoValues1.getType() == getConditionType<tConditionTwoValue>() ){
	
		cout<<"The condition type is correctly "<<
			getConditionType<tConditionTwoValue>()<<". "<<endl;
	}else{
		cerr<<"Error: The type of the condition is not "<<
			getConditionType<tConditionTwoValue>()<<", but "<<
			conditionTwoValues1.getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getConditionName() methode from tConditionTwoValue
	if ( conditionTwoValues1.getConditionName() == getConditionName<tConditionTwoValue>() ){
	
		cout<<"The condition name is correctly \""<<
			conditionTwoValues1.getConditionName() <<"\" . "<<endl;
	}else{
		cerr<<"Error: The name of the condition is not \""<<
			getConditionName<tConditionTwoValue>()<<"\", but \""<<
			conditionTwoValues1.getConditionName() <<"\" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfConditions() methode from tConditionTwoValue
	if ( conditionTwoValues1.getNumberOfConditions() == 2 ){
	
		cout<<"The condition number of subconditions is correctly "<<
			conditionTwoValues1.getNumberOfConditions() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition number of subconditions is "<<
			conditionTwoValues1.getNumberOfConditions() <<" , but should be 1 ."<<endl;
		iReturn++;
	}
	//check the getNumberOfConditions() methode from tConditionTwoValue
	if ( conditionTwoValues1.getNumberOfUnderFunctions() == 0 ){
	
		cout<<"The condition number of subconditions is correctly "<<
			conditionTwoValues1.getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition number of subconditions is "<<
			conditionTwoValues1.getNumberOfUnderFunctions() <<" , but should be 0 ."<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from tConditionTwoValue
	if ( conditionTwoValues1.getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the condition is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the condition is "<<
			conditionTwoValues1.getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from tConditionTwoValue
	if ( conditionTwoValues1.getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the condition is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The tcompressed size of the condition is "<<
			conditionTwoValues1.getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from tConditionTwoValue
	if ( ! conditionTwoValues1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 isn't used in the condition. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the condition. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from tConditionTwoValue
	set<cFibVariable*> setUsedVariables = conditionTwoValues1.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"No used variables are given back from the condition. "<<endl;
	}else{
		cerr<<"Error: Used variables are given back from the condition. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an tConditionTwoValue condition with all values set"<<endl;

	cout<<"cConditionFalse subConditionFalse;"<<endl;
	cConditionFalse subConditionFalse;
	
	cout<<"cConditionTrue subConditionTrue;"<<endl;
	cConditionTrue subConditionTrue;
	
	cout<<"tConditionTwoValue conditionTwoValues2( subConditionFalse, subConditionTrue, &conditionTwoValues1, &rootEmpty );"<<endl;
	tConditionTwoValue conditionTwoValues2( subConditionFalse, subConditionTrue, &conditionTwoValues1, &rootEmpty );
	
	pDefiningFibElement = &rootEmpty;
	pSuperiorCondition = &conditionTwoValues1;
	pFirstSubCondition = &subConditionFalse;
	pSecondSubCondition = &subConditionTrue;
	ulTimeNeed = 3;
	ulCompressedSize = 12;

	//check the getValue() methode from tConditionTwoValue
	if ( conditionTwoValues2.getValue() == getCorrectValue< tConditionTwoValue >( false, true ) ){
	
		cout<<"The condition value is correctly "<<
			(conditionTwoValues2.getValue()?"true":"false") <<" . "<<endl;
	}else{
		cerr<<"Error: The condition value is "<<
			(conditionTwoValues2.getValue()?"true":"false") <<" but shouldn't be ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from tConditionTwoValue
	if ( conditionTwoValues2.getDefiningFibElement() == pDefiningFibElement ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionTwoValues2.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionTwoValues2.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from tConditionTwoValue
	if ( conditionTwoValues2.getSuperiorCondition() == pSuperiorCondition ){
	
		cout<<"The superior condition of the condition correctly "<<
			conditionTwoValues2.getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			conditionTwoValues2.getSuperiorCondition() <<
			" but should be "<< pSuperiorCondition <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstSubCondition() methode from tConditionTwoValue
	if ( *(conditionTwoValues2.getFirstSubCondition()) == *pFirstSubCondition ){
	
		cout<<"The first subcondition of the condition correctly equal to"<<
			conditionTwoValues2.getFirstSubCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The first subcondition of the condition is "<<
			conditionTwoValues2.getFirstSubCondition() <<
			" but should be equal to "<< pFirstSubCondition <<" ."<<endl;
		iReturn++;
	}
	//check the getSecondSubCondition() methode from tConditionTwoValue
	if ( *(conditionTwoValues2.getSecondSubCondition()) == *pSecondSubCondition ){
	
		cout<<"The second subcondition of the condition correctly equal to"<<
			conditionTwoValues2.getSecondSubCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The second subcondition of the condition is"<<
			conditionTwoValues2.getSecondSubCondition() <<
			" but should be equal to "<< pSecondSubCondition <<" ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from tConditionTwoValue
	if ( conditionTwoValues2.isValid() ){
	
		cout<<"The condition is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The condition is not valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from tConditionTwoValue
	if ( conditionTwoValues2.getType() == getConditionType<tConditionTwoValue>() ){
	
		cout<<"The condition type is correctly "<<
			getConditionType<tConditionTwoValue>()<<" . "<<endl;
	}else{
		cerr<<"Error: The type of the condition is not "<<
			getConditionType<tConditionTwoValue>()<<", but "<<
			conditionTwoValues2.getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getConditionName() methode from tConditionTwoValue
	if ( conditionTwoValues2.getConditionName() == getConditionName<tConditionTwoValue>() ){
	
		cout<<"The condition name is correctly \""<<
			conditionTwoValues2.getConditionName() <<"\" . "<<endl;
	}else{
		cerr<<"Error: The name of the condition is not \""<<
			getConditionName<tConditionTwoValue>()<<"\", but \""<<
			conditionTwoValues2.getConditionName() <<"\" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfConditions() methode from tConditionTwoValue
	if ( conditionTwoValues2.getNumberOfConditions() == 2 ){
	
		cout<<"The condition number of subconditions is correctly "<<
			conditionTwoValues2.getNumberOfConditions() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition number of subconditions is "<<
			conditionTwoValues2.getNumberOfConditions() <<" , but should be 1 ."<<endl;
		iReturn++;
	}
	//check the getNumberOfConditions() methode from tConditionTwoValue
	if ( conditionTwoValues2.getNumberOfUnderFunctions() == 0 ){
	
		cout<<"The condition number of subconditions is correctly "<<
			conditionTwoValues2.getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition number of subconditions is "<<
			conditionTwoValues2.getNumberOfUnderFunctions() <<" , but should be 0 ."<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from tConditionTwoValue
	if ( conditionTwoValues2.getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the condition is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the condition is "<<
			conditionTwoValues2.getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from tConditionTwoValue
	if ( conditionTwoValues2.getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the condition is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The tcompressed size of the condition is "<<
			conditionTwoValues2.getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from tConditionTwoValue
	if ( ! conditionTwoValues2.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 isn't used in the condition. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the condition. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from tConditionTwoValue
	setUsedVariables = conditionTwoValues2.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"No used variables are given back from the condition. "<<endl;
	}else{
		cerr<<"Error: Used variables are given back from the condition. "<<endl;
		iReturn++;
	}



	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an tConditionTwoValue condition with all values set"<<endl;

	bool bIsValid = true;
	bool bIsPointer = true;
	bool bValueFirstSubCondition = false;
	bool bValueSecondSubCondition = false;
	tConditionTwoValue * pConditionTest = NULL;
	
	for ( unsigned int uiTestCase = 1; uiTestCase <= 11; uiTestCase++ ){
		
		/*Testcases:
			-true false
			-false false
			-true true
			
			-*true *true
			-*false *false
			-*true *false
			-*false *true
			
			-NULL true
			-true NULL
			-NULL false
			-false NULL
		*/
		switch ( uiTestCase ){
		case 1://true false
			cout<<endl<<"pConditionTest = new tConditionTwoValue( subConditionTrue, subConditionFalse, &conditionTwoValues1, &rootEmpty );"<<endl;
			pConditionTest = new tConditionTwoValue( subConditionTrue, subConditionFalse, &conditionTwoValues1, &rootEmpty );
			
			bIsPointer = false;
			bIsValid = true;
			pFirstSubCondition = &subConditionTrue;
			bValueFirstSubCondition = true;
			pSecondSubCondition = &subConditionFalse;
			bValueSecondSubCondition = false;
			ulTimeNeed = 3;
			ulCompressedSize = 12;
		break;
		case 2://false false
			cout<<endl<<"pConditionTest = new tConditionTwoValue( subConditionFalse, subConditionFalse, &conditionTwoValues1, &rootEmpty );"<<endl;
			pConditionTest = new tConditionTwoValue( subConditionFalse, subConditionFalse, &conditionTwoValues1, &rootEmpty );
			
			bIsPointer = false;
			bIsValid = true;
			pFirstSubCondition = &subConditionFalse;
			bValueFirstSubCondition = false;
			pSecondSubCondition = &subConditionFalse;
			bValueSecondSubCondition = false;
			ulTimeNeed = 3;
			ulCompressedSize = 12;
		break;
		case 3://true true
			cout<<endl<<"pConditionTest = new tConditionTwoValue( subConditionTrue, subConditionTrue, &conditionTwoValues1, &rootEmpty );"<<endl;
			pConditionTest = new tConditionTwoValue( subConditionTrue, subConditionTrue, &conditionTwoValues1, &rootEmpty );
			
			bIsPointer = false;
			bIsValid = true;
			pFirstSubCondition = &subConditionTrue;
			bValueFirstSubCondition = true;
			pSecondSubCondition = &subConditionTrue;
			bValueSecondSubCondition = true;
			ulTimeNeed = 3;
			ulCompressedSize = 12;
		break;
		
		case 4://*true *true
			bIsPointer = true;
			bIsValid = true;
			cout<<endl<<"pFirstSubCondition("<<pFirstSubCondition<<") = new cConditionTrue();"<<endl;
			pFirstSubCondition = new cConditionTrue();
			bValueFirstSubCondition = true;
			cout<<"pSecondSubCondition("<<pSecondSubCondition<<") = new cConditionTrue();"<<endl;
			pSecondSubCondition = new cConditionTrue();
			bValueSecondSubCondition = true;
			ulTimeNeed = 3;
			ulCompressedSize = 12;
			
			cout<<"pConditionTest = new tConditionTwoValue( "<<pFirstSubCondition<<
				", "<<pSecondSubCondition<<", &conditionTwoValues1, &rootEmpty );"<<endl;
			pConditionTest = new tConditionTwoValue( pFirstSubCondition, pSecondSubCondition, &conditionTwoValues1, &rootEmpty );
		break;
		case 5://*false *false
			bIsPointer = true;
			bIsValid = true;
			cout<<endl<<"pFirstSubCondition("<<pFirstSubCondition<<") = new cConditionFalse();"<<endl;
			pFirstSubCondition = new cConditionFalse();
			bValueFirstSubCondition = false;
			cout<<"pSecondSubCondition("<<pSecondSubCondition<<") = new cConditionFalse();"<<endl;
			pSecondSubCondition = new cConditionFalse();
			bValueSecondSubCondition = false;
			ulTimeNeed = 3;
			ulCompressedSize = 12;
			
			cout<<"pConditionTest = new tConditionTwoValue( "<<pFirstSubCondition<<
				", "<<pSecondSubCondition<<", &conditionTwoValues1, &rootEmpty );"<<endl;
			pConditionTest = new tConditionTwoValue( pFirstSubCondition, pSecondSubCondition, &conditionTwoValues1, &rootEmpty );
		break;
		case 6://*true *false
			bIsPointer = true;
			bIsValid = true;
			cout<<endl<<"pFirstSubCondition("<<pFirstSubCondition<<") = new cConditionTrue();"<<endl;
			pFirstSubCondition = new cConditionTrue();
			bValueFirstSubCondition = true;
			cout<<"pSecondSubCondition("<<pSecondSubCondition<<") = new cConditionFalse();"<<endl;
			pSecondSubCondition = new cConditionFalse();
			bValueSecondSubCondition = false;
			ulTimeNeed = 3;
			ulCompressedSize = 12;
			
			cout<<"pConditionTest = new tConditionTwoValue( "<<pFirstSubCondition<<
				", "<<pSecondSubCondition<<", &conditionTwoValues1, &rootEmpty );"<<endl;
			pConditionTest = new tConditionTwoValue( pFirstSubCondition, pSecondSubCondition, &conditionTwoValues1, &rootEmpty );
		break;
		case 7://*false *true
			bIsPointer = true;
			bIsValid = true;
			cout<<endl<<"pFirstSubCondition("<<pFirstSubCondition<<") = new cConditionFalse();"<<endl;
			pFirstSubCondition = new cConditionFalse();
			bValueFirstSubCondition = false;
			cout<<"pSecondSubCondition("<<pSecondSubCondition<<") = new cConditionTrue();"<<endl;
			pSecondSubCondition = new cConditionTrue();
			bValueSecondSubCondition = true;
			ulTimeNeed = 3;
			ulCompressedSize = 12;
			
			cout<<"pConditionTest = new tConditionTwoValue( "<<pFirstSubCondition<<
				", "<<pSecondSubCondition<<", &conditionTwoValues1, &rootEmpty );"<<endl;
			pConditionTest = new tConditionTwoValue( pFirstSubCondition, pSecondSubCondition, &conditionTwoValues1, &rootEmpty );
		break;
		
		case 8://NULL *true
			bIsPointer = true;
			bIsValid = false;
			pFirstSubCondition = NULL;
			bValueFirstSubCondition = false;
			cout<<endl<<"pSecondSubCondition("<<pSecondSubCondition<<") = new cConditionTrue();"<<endl;
			pSecondSubCondition = new cConditionTrue();
			bValueSecondSubCondition = true;
			ulTimeNeed = 2;
			ulCompressedSize = 8;
			
			cout<<"pConditionTest = new tConditionTwoValue( "<<pFirstSubCondition<<
				", "<<pSecondSubCondition<<", &conditionTwoValues1, &rootEmpty );"<<endl;
			pConditionTest = new tConditionTwoValue( pFirstSubCondition, pSecondSubCondition, &conditionTwoValues1, &rootEmpty );
		break;
		case 9://*true NULL
			bIsPointer = true;
			bIsValid = false;
			cout<<endl<<"pFirstSubCondition("<<pFirstSubCondition<<") = new cConditionTrue();"<<endl;
			pFirstSubCondition = new cConditionTrue();
			bValueFirstSubCondition = true;
			pSecondSubCondition = NULL;
			bValueSecondSubCondition = false;
			ulTimeNeed = 2;
			ulCompressedSize = 8;
			
			cout<<"pConditionTest = new tConditionTwoValue( "<<pFirstSubCondition<<
				", "<<pSecondSubCondition<<", &conditionTwoValues1, &rootEmpty );"<<endl;
			pConditionTest = new tConditionTwoValue( pFirstSubCondition, pSecondSubCondition, &conditionTwoValues1, &rootEmpty );
		break;
		case 10://NULL *false
			bIsPointer = true;
			bIsValid = false;
			pFirstSubCondition = NULL;
			bValueFirstSubCondition = false;
			cout<<endl<<"pSecondSubCondition("<<pSecondSubCondition<<") = new cConditionFalse();"<<endl;
			pSecondSubCondition = new cConditionFalse();
			bValueSecondSubCondition = false;
			ulTimeNeed = 2;
			ulCompressedSize = 8;
			
			cout<<"pConditionTest = new tConditionTwoValue( "<<pFirstSubCondition<<
				", "<<pSecondSubCondition<<", &conditionTwoValues1, &rootEmpty );"<<endl;
			pConditionTest = new tConditionTwoValue( pFirstSubCondition, pSecondSubCondition, &conditionTwoValues1, &rootEmpty );
		break;
		case 11://*false NULL
			bIsPointer = true;
			bIsValid = false;
			cout<<endl<<"pFirstSubCondition("<<pFirstSubCondition<<") = new cConditionFalse();"<<endl;
			pFirstSubCondition = new cConditionFalse();
			bValueFirstSubCondition = false;
			pSecondSubCondition = NULL;
			bValueSecondSubCondition = false;
			ulTimeNeed = 2;
			ulCompressedSize = 8;
			
			cout<<"pConditionTest = new tConditionTwoValue( "<<pFirstSubCondition<<
				", "<<pSecondSubCondition<<", &conditionTwoValues1, &rootEmpty );"<<endl;
			pConditionTest = new tConditionTwoValue( pFirstSubCondition, pSecondSubCondition, &conditionTwoValues1, &rootEmpty );
		break;
		
		default://error no such testcase
			cerr<<endl<<"Error: No such testcase ("<<uiTestCase<<")."<<endl;
			iReturn++;
			continue;
		}
	
		//check the getValue() methode from tConditionTwoValue
		if ( pConditionTest->getValue() == getCorrectValue< tConditionTwoValue >(
				bValueFirstSubCondition, bValueSecondSubCondition ) ){
		
			cout<<"The condition value is correctly "<<
				(pConditionTest->getValue()?"true":"false") <<" . "<<endl;
		}else{
			cerr<<"Error: The condition value is "<<
				(pConditionTest->getValue()?"true":"false") <<" but shouldn't be ."<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from tConditionTwoValue
		if ( pConditionTest->getDefiningFibElement() == pDefiningFibElement ){
		
			cout<<"The condition defining Fib-element is correctly "<<
				pConditionTest->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The condition defining Fib-element is "<<
				pConditionTest->getDefiningFibElement() <<
				" but should be "<< pDefiningFibElement <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorCondition() methode from tConditionTwoValue
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
			//check the getFirstSubCondition() methode from tConditionTwoValue
			if ( *(pConditionTest->getFirstSubCondition()) == *pFirstSubCondition ){
			
				cout<<"The first subcondition of the condition correctly equal to"<<
					pConditionTest->getFirstSubCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The first subcondition of the condition is "<<
					pConditionTest->getFirstSubCondition() <<
					" but should be equal to "<< pFirstSubCondition <<" ."<<endl;
				iReturn++;
			}
			//check the getSecondSubCondition() methode from tConditionTwoValue
			if ( *(pConditionTest->getSecondSubCondition()) == *pSecondSubCondition ){
			
				cout<<"The second subcondition of the condition correctly equal to"<<
					pConditionTest->getSecondSubCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The second subcondition of the condition is"<<
					pConditionTest->getSecondSubCondition() <<
					" but should be equal to "<< pSecondSubCondition <<" ."<<endl;
				iReturn++;
			}
		}else{
			//check the getFirstSubCondition() methode from tConditionTwoValue
			if ( pConditionTest->getFirstSubCondition() == pFirstSubCondition ){
			
				cout<<"The first subcondition of the condition correctly "<<
					pConditionTest->getFirstSubCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The first subcondition of the condition is "<<
					pConditionTest->getFirstSubCondition() <<
					" but should be "<< pFirstSubCondition <<" ."<<endl;
				iReturn++;
			}
			//check the getSecondSubCondition() methode from tConditionTwoValue
			if ( pConditionTest->getSecondSubCondition() == pSecondSubCondition ){
			
				cout<<"The second subcondition of the condition correctly "<<
					pConditionTest->getSecondSubCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The second subcondition of the condition is"<<
					pConditionTest->getSecondSubCondition() <<
					" but should be "<< pSecondSubCondition <<" ."<<endl;
				iReturn++;
			}
		}
		
		//check the isValid() methode from tConditionTwoValue
		if ( pConditionTest->isValid() == bIsValid ){
		
			cout<<"The condition is correctly "<<(bIsValid?"":"not ")<<"valid . "<<endl;
		}else{
			cerr<<"Error: The condition is "<<(bIsValid?"not ":"")<<" valid, but should be ."<<endl;
			iReturn++;
		}
		//check the getType() methode from tConditionTwoValue
		if ( pConditionTest->getType() == getConditionType<tConditionTwoValue>() ){
		
			cout<<"The condition type is correctly "<<
				getConditionType<tConditionTwoValue>()<<" . "<<endl;
		}else{
			cerr<<"Error: The type of the condition is not "<<
				getConditionType<tConditionTwoValue>()<<", but "<<
				pConditionTest->getType() <<" ."<<endl;
			iReturn++;
		}
		//check the getConditionName() methode from tConditionTwoValue
		if ( pConditionTest->getConditionName() == getConditionName<tConditionTwoValue>() ){
		
			cout<<"The condition name is correctly \""<<
				pConditionTest->getConditionName() <<"\" . "<<endl;
		}else{
			cerr<<"Error: The name of the condition is not \""<<
				getConditionName<tConditionTwoValue>()<<"\", but \""<<
				pConditionTest->getConditionName() <<"\" ."<<endl;
			iReturn++;
		}
		//check the getNumberOfConditions() methode from tConditionTwoValue
		if ( pConditionTest->getNumberOfConditions() == 2 ){
		
			cout<<"The condition number of subconditions is correctly "<<
				pConditionTest->getNumberOfConditions() <<" . "<<endl;
		}else{
			cerr<<"Error: The condition number of subconditions is "<<
				pConditionTest->getNumberOfConditions() <<" , but should be 1 ."<<endl;
			iReturn++;
		}
		//check the getNumberOfConditions() methode from tConditionTwoValue
		if ( pConditionTest->getNumberOfUnderFunctions() == 0 ){
		
			cout<<"The condition number of subconditions is correctly "<<
				pConditionTest->getNumberOfUnderFunctions() <<" . "<<endl;
		}else{
			cerr<<"Error: The condition number of subconditions is "<<
				pConditionTest->getNumberOfUnderFunctions() <<" , but should be 0 ."<<endl;
			iReturn++;
		}
		//check the getTimeNeed() methode from tConditionTwoValue
		if ( pConditionTest->getTimeNeed() == ulTimeNeed ){
		
			cout<<"The time needed to evalue the condition is correctly "<< ulTimeNeed <<" . "<<endl;
		}else{
			cerr<<"Error: The time needed to evalue the condition is "<<
				pConditionTest->getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
			iReturn++;
		}
		//check the getCompressedSize() methode from tConditionTwoValue
		if ( pConditionTest->getCompressedSize() == ulCompressedSize ){
		
			cout<<"The compressed size of the condition is correctly "<<
			ulCompressedSize <<" . "<<endl;
		}else{
			cerr<<"Error: The tcompressed size of the condition is "<<
				pConditionTest->getCompressedSize()<<" ,but should be "<<
				ulCompressedSize <<" . "<<endl;
			iReturn++;
		}
		//check the getCompressedSize() methode from tConditionTwoValue
		if ( ! pConditionTest->isUsedVariable( pVariable1 ) ){
		
			cout<<"The variable pVariable1 isn't used in the condition. "<<endl;
		}else{
			cerr<<"Error: The variable pVariable1 is used in the condition. "<<endl;
			iReturn++;
		}
		//check the getUsedVariables() methode from tConditionTwoValue
		setUsedVariables = pConditionTest->getUsedVariables();
		if ( setUsedVariables.empty() ){
		
			cout<<"No used variables are given back from the condition. "<<endl;
		}else{
			cerr<<"Error: Used variables are given back from the condition. "<<endl;
			iReturn++;
		}
		
		if ( pConditionTest ){
			delete pConditionTest;
			pConditionTest = NULL;
		}
	}//for different subconditions


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
 * This method tests equal method of the tConditionTwoValue class.
 *
 * methods tested:
 * 	- bool equal( const cFibElement & fibObject ) const
 * 	- bool operator==( const cCondition &condition ) const;
 * 	- bool operator!=( const cCondition &condition ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
template <class tConditionTwoValue>
	int testEqual( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing comparison methods for condition"<<endl;

	cout<<endl<<"Creating conditions objects to compare: "<<endl<<endl;

	//simple condition
	cout<<"tConditionTwoValue conditionTwoValues1( NULL, NULL );"<<endl;
	tConditionTwoValue conditionTwoValues1( NULL, NULL );

	cout<<"tConditionTwoValue conditionTwoValues2( NULL, NULL );"<<endl;
	tConditionTwoValue conditionTwoValues2( NULL, NULL );

	//with subcondition
	cout<<"tConditionTwoValue conditionTwoValuesTrueNULL( new cConditionTrue(), NULL );"<<endl;
	tConditionTwoValue conditionTwoValuesTrueNULL( new cConditionTrue(), NULL );

	cout<<"tConditionTwoValue conditionTwoValueFalseNULL( new cConditionFalse(), NULL );"<<endl;
	tConditionTwoValue conditionTwoValueFalseNULL( new cConditionFalse(), NULL );

	cout<<"tConditionTwoValue conditionTwoValuesNULLTrue( NULL, new cConditionTrue() );"<<endl;
	tConditionTwoValue conditionTwoValuesNULLTrue( NULL, new cConditionTrue() );

	cout<<"tConditionTwoValue conditionTwoValueNULLFalse( NULL, new cConditionFalse() );"<<endl;
	tConditionTwoValue conditionTwoValueNULLFalse( NULL, new cConditionFalse() );


	cout<<"tConditionTwoValue conditionTwoValuesTrueTrue( new cConditionTrue(), new cConditionTrue() );"<<endl;
	tConditionTwoValue conditionTwoValuesTrueTrue( new cConditionTrue(), new cConditionTrue() );

	cout<<"tConditionTwoValue conditionTwoValueFalseFalse( new cConditionFalse(), new cConditionFalse() );"<<endl;
	tConditionTwoValue conditionTwoValueFalseFalse( new cConditionFalse(), new cConditionFalse() );

	cout<<"tConditionTwoValue conditionTwoValueFalseTrue( new cConditionFalse(), new cConditionTrue() );"<<endl;
	tConditionTwoValue conditionTwoValueFalseTrue( new cConditionFalse(), new cConditionTrue() );

	cout<<"tConditionTwoValue conditionTwoValueTrueFalse( new cConditionTrue(), new cConditionFalse() );"<<endl;
	tConditionTwoValue conditionTwoValueTrueFalse( new cConditionTrue(), new cConditionFalse() );


	
	//condition with defining Fib-element
	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	cout<<"tConditionTwoValue conditionDefFE( NULL, NULL, NULL, &rootSimple1 );"<<endl;
	tConditionTwoValue conditionDefFE( NULL, NULL, NULL, &rootSimple1 );

	//condition with superior condition
	cout<<"cConditionNot conditionNotSup( NULL );"<<endl;
	cConditionNot conditionNotSup( NULL );
	cout<<"tConditionTwoValue conditionSup( NULL, NULL, & conditionNotSup );"<<endl;
	tConditionTwoValue conditionSup( NULL, NULL, & conditionNotSup );

	//condition with domains set
	cout<<"root1 rootSimple1;"<<endl;
	cRoot root1;
	
	cout<<"cTypeVariable testTypeVariable;"<<endl;
	cTypeVariable testTypeVariable;
	cout<<"cDomainNaturalNumberBit domainNat8( 8 );"<<endl;
	cDomainNaturalNumberBit domainNat8( 8 );

	cout<<"root1.getDomains()->addDomain( testTypeVariable, &domainNat8 );"<<endl;
	root1.getDomains()->addDomain( testTypeVariable, &domainNat8 );

	cout<<"tConditionTwoValue conditionDom( NULL, NULL, NULL, &root1 );"<<endl;
	tConditionTwoValue conditionDom( NULL, NULL, NULL, &root1 );

	//condition with defining Fib-element and superior condition
	cout<<"cRoot rootSimple2;"<<endl;
	cRoot rootSimple2;
	cout<<"cConditionNot conditionNotSup2( NULL );"<<endl;
	cConditionNot conditionNotSup2( NULL );
	cout<<"tConditionTwoValue conditionDefFeSc( NULL, NULL, & conditionNotSup2, &rootSimple2 );"<<endl;
	tConditionTwoValue conditionDefFeSc( NULL, NULL, & conditionNotSup2, &rootSimple2 );

	//condition with all elements set
	cout<<"cRoot rootSimple3;"<<endl;
	cRoot rootSimple3;
	cout<<"cConditionNot conditionNotSup3( NULL );"<<endl;
	cConditionNot conditionNotSup3( NULL );
	cout<<"tConditionTwoValue conditionFull( new cConditionTrue(), new cConditionFalse(), & conditionNotSup3, &rootSimple3 );"<<endl;
	tConditionTwoValue conditionFull( new cConditionTrue(), new cConditionFalse(), & conditionNotSup3, &rootSimple3 );


	//conditions of other typs
	cout<<"cConditionFalse conditionFalse;"<<endl;
	cConditionFalse conditionFalse;
	
	cout<<"cConditionNot conditionNot( conditionFalse );"<<endl;
	cConditionNot conditionNot( conditionFalse );


	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with conditionTwoValues1
	cCondition * actualObject = &conditionTwoValues1;
	string szActualObjectName = "conditionTwoValues1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueNULL, "conditionTwoValuesTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseNULL, "conditionTwoValueFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLTrue, "conditionTwoValuesNULLTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLFalse, "conditionTwoValueNULLFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueTrue, "conditionTwoValuesTrueTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseFalse, "conditionTwoValueFalseFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseTrue, "conditionTwoValueFalseTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueTrueFalse, "conditionTwoValueTrueFalse" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );

	//compare with conditionTwoValues2
	actualObject = &conditionTwoValues2;
	szActualObjectName = "conditionTwoValues2";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueNULL, "conditionTwoValuesTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseNULL, "conditionTwoValueFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLTrue, "conditionTwoValuesNULLTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLFalse, "conditionTwoValueNULLFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueTrue, "conditionTwoValuesTrueTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseFalse, "conditionTwoValueFalseFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseTrue, "conditionTwoValueFalseTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueTrueFalse, "conditionTwoValueTrueFalse" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );

	//compare with conditionTwoValuesTrueNULL
	actualObject = &conditionTwoValuesTrueNULL;
	szActualObjectName = "conditionTwoValuesTrueNULL";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueNULL, "conditionTwoValuesTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseNULL, "conditionTwoValueFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLTrue, "conditionTwoValuesNULLTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLFalse, "conditionTwoValueNULLFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueTrue, "conditionTwoValuesTrueTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseFalse, "conditionTwoValueFalseFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseTrue, "conditionTwoValueFalseTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueTrueFalse, "conditionTwoValueTrueFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );

	//compare with conditionTwoValueFalseNULL
	actualObject = &conditionTwoValueFalseNULL;
	szActualObjectName = "conditionTwoValueFalseNULL";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueNULL, "conditionTwoValuesTrueNULL" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseNULL, "conditionTwoValueFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLTrue, "conditionTwoValuesNULLTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLFalse, "conditionTwoValueNULLFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueTrue, "conditionTwoValuesTrueTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseFalse, "conditionTwoValueFalseFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseTrue, "conditionTwoValueFalseTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueTrueFalse, "conditionTwoValueTrueFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );

	//compare with conditionTwoValuesNULLTrue
	actualObject = &conditionTwoValuesNULLTrue;
	szActualObjectName = "conditionTwoValuesNULLTrue";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueNULL, "conditionTwoValuesTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseNULL, "conditionTwoValueFalseNULL" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLTrue, "conditionTwoValuesNULLTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLFalse, "conditionTwoValueNULLFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueTrue, "conditionTwoValuesTrueTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseFalse, "conditionTwoValueFalseFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseTrue, "conditionTwoValueFalseTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueTrueFalse, "conditionTwoValueTrueFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );

	//compare with conditionTwoValueNULLFalse
	actualObject = &conditionTwoValueNULLFalse;
	szActualObjectName = "conditionTwoValueNULLFalse";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueNULL, "conditionTwoValuesTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseNULL, "conditionTwoValueFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLTrue, "conditionTwoValuesNULLTrue" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLFalse, "conditionTwoValueNULLFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueTrue, "conditionTwoValuesTrueTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseFalse, "conditionTwoValueFalseFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseTrue, "conditionTwoValueFalseTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueTrueFalse, "conditionTwoValueTrueFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );

	//compare with conditionTwoValuesTrueNULL
	actualObject = &conditionTwoValuesTrueTrue;
	szActualObjectName = "conditionTwoValuesTrueTrue";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueNULL, "conditionTwoValuesTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseNULL, "conditionTwoValueFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLTrue, "conditionTwoValuesNULLTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLFalse, "conditionTwoValueNULLFalse" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueTrue, "conditionTwoValuesTrueTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseFalse, "conditionTwoValueFalseFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseTrue, "conditionTwoValueFalseTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueTrueFalse, "conditionTwoValueTrueFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );

	//compare with conditionTwoValueFalseFalse
	actualObject = &conditionTwoValueFalseFalse;
	szActualObjectName = "conditionTwoValueFalseFalse";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueNULL, "conditionTwoValuesTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseNULL, "conditionTwoValueFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLTrue, "conditionTwoValuesNULLTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLFalse, "conditionTwoValueNULLFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueTrue, "conditionTwoValuesTrueTrue" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseFalse, "conditionTwoValueFalseFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseTrue, "conditionTwoValueFalseTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueTrueFalse, "conditionTwoValueTrueFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );

	//compare with conditionTwoValueFalseTrue
	actualObject = &conditionTwoValueFalseTrue;
	szActualObjectName = "conditionTwoValueFalseTrue";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueNULL, "conditionTwoValuesTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseNULL, "conditionTwoValueFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLTrue, "conditionTwoValuesNULLTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLFalse, "conditionTwoValueNULLFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueTrue, "conditionTwoValuesTrueTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseFalse, "conditionTwoValueFalseFalse" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseTrue, "conditionTwoValueFalseTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueTrueFalse, "conditionTwoValueTrueFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );

	//compare with conditionTwoValueTrueFalse
	actualObject = &conditionTwoValueTrueFalse;
	szActualObjectName = "conditionTwoValueTrueFalse";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueNULL, "conditionTwoValuesTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseNULL, "conditionTwoValueFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLTrue, "conditionTwoValuesNULLTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLFalse, "conditionTwoValueNULLFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueTrue, "conditionTwoValuesTrueTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseFalse, "conditionTwoValueFalseFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseTrue, "conditionTwoValueFalseTrue" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValueTrueFalse, "conditionTwoValueTrueFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );

	//compare with conditionDefFE
	actualObject = &conditionDefFE;
	szActualObjectName = "conditionDefFE";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueNULL, "conditionTwoValuesTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseNULL, "conditionTwoValueFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLTrue, "conditionTwoValuesNULLTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLFalse, "conditionTwoValueNULLFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueTrue, "conditionTwoValuesTrueTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseFalse, "conditionTwoValueFalseFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseTrue, "conditionTwoValueFalseTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueTrueFalse, "conditionTwoValueTrueFalse" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );

	//compare with conditionSup
	actualObject = &conditionSup;
	szActualObjectName = "conditionSup";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueNULL, "conditionTwoValuesTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseNULL, "conditionTwoValueFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLTrue, "conditionTwoValuesNULLTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLFalse, "conditionTwoValueNULLFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueTrue, "conditionTwoValuesTrueTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseFalse, "conditionTwoValueFalseFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseTrue, "conditionTwoValueFalseTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueTrueFalse, "conditionTwoValueTrueFalse" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );

	//compare with conditionDom
	actualObject = &conditionDom;
	szActualObjectName = "conditionDom";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueNULL, "conditionTwoValuesTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseNULL, "conditionTwoValueFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLTrue, "conditionTwoValuesNULLTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLFalse, "conditionTwoValueNULLFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueTrue, "conditionTwoValuesTrueTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseFalse, "conditionTwoValueFalseFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseTrue, "conditionTwoValueFalseTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueTrueFalse, "conditionTwoValueTrueFalse" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );

	//compare with conditionDefFeSc
	actualObject = &conditionDefFeSc;
	szActualObjectName = "conditionDefFeSc";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueNULL, "conditionTwoValuesTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseNULL, "conditionTwoValueFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLTrue, "conditionTwoValuesNULLTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLFalse, "conditionTwoValueNULLFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueTrue, "conditionTwoValuesTrueTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseFalse, "conditionTwoValueFalseFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseTrue, "conditionTwoValueFalseTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueTrueFalse, "conditionTwoValueTrueFalse" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );

	//compare with conditionFull
	actualObject = &conditionFull;
	szActualObjectName = "conditionFull";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueNULL, "conditionTwoValuesTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseNULL, "conditionTwoValueFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLTrue, "conditionTwoValuesNULLTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLFalse, "conditionTwoValueNULLFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueTrue, "conditionTwoValuesTrueTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseFalse, "conditionTwoValueFalseFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseTrue, "conditionTwoValueFalseTrue" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionTwoValueTrueFalse, "conditionTwoValueTrueFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );


	//compare with conditionFalse
	actualObject = &conditionFalse;
	szActualObjectName = "conditionFalse";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueNULL, "conditionTwoValuesTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseNULL, "conditionTwoValueFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLTrue, "conditionTwoValuesNULLTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLFalse, "conditionTwoValueNULLFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueTrue, "conditionTwoValuesTrueTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseFalse, "conditionTwoValueFalseFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseTrue, "conditionTwoValueFalseTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueTrueFalse, "conditionTwoValueTrueFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );

	//compare with conditionNot
	actualObject = &conditionNot;
	szActualObjectName = "conditionNot";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValues1, "conditionTwoValues2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueNULL, "conditionTwoValuesTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseNULL, "conditionTwoValueFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesNULLTrue, "conditionTwoValuesNULLTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueNULLFalse, "conditionTwoValueNULLFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValuesTrueTrue, "conditionTwoValuesTrueTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseFalse, "conditionTwoValueFalseFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueFalseTrue, "conditionTwoValueFalseTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionTwoValueTrueFalse, "conditionTwoValueTrueFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFull, "conditionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionNot, "conditionNot" );


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
 * This method tests the copy methods and copyconstructor of the tConditionTwoValue class.
 *
 * methods tested:
 * 	- cConditionTwoValue( const cConditionTwoValue & condition, cCondition * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- cCondition * clone( cCondition * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
template <class tConditionTwoValue>
	int testCopy( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a simple tConditionTwoValue"<<endl;

	cout<<"tConditionTwoValue conditionTwoValues1( NULL, NULL );"<<endl;
	tConditionTwoValue conditionTwoValues1( NULL, NULL );

	cout<<"tConditionTwoValue conditionTwoValues1CopyConstruct( conditionTwoValues1 );"<<endl;
	tConditionTwoValue conditionTwoValues1CopyConstruct( conditionTwoValues1 );

	iReturn += testCompareTwoEqualObjects( conditionTwoValues1CopyConstruct, "conditionTwoValues1CopyConstruct", conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testNotConnectedCondition( conditionTwoValues1CopyConstruct );

	cout<<"cCondition * pUnderConditionTwoValues1Clone = conditionTwoValues1CopyConstruct.clone();"<<endl;
	cCondition * pUnderConditionTwoValues1Clone = conditionTwoValues1CopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pUnderConditionTwoValues1Clone, "pUnderConditionTwoValues1Clone", conditionTwoValues1, "conditionTwoValues1" );
	iReturn += testNotConnectedCondition( *pUnderConditionTwoValues1Clone );
	delete pUnderConditionTwoValues1Clone;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a tConditionTwoValue with a subcondition, superior condition and defining Fib-element"<<endl;
	
	//condition with defining Fib-element and superior condition
	cout<<"cRoot rootSimple;"<<endl;
	cRoot rootSimple;
	cout<<"tConditionTwoValue conditionSup( NULL, NULL );"<<endl;
	tConditionTwoValue conditionSup( NULL, NULL );
	cout<<"cConditionFalse subConditionFalse;"<<endl;
	cConditionFalse subConditionFalse;
	cout<<"cConditionFalse subConditionTrue;"<<endl;
	cConditionFalse subConditionTrue;
	cout<<"tConditionTwoValue conditionDefFeSc( subConditionFalse, subConditionTrue, & conditionSup, &rootSimple );"<<endl;
	tConditionTwoValue conditionDefFeSc( subConditionFalse, subConditionTrue, & conditionSup, &rootSimple );

	cout<<"tConditionTwoValue conditionDefFeScCopyConstruct( conditionDefFeSc );"<<endl;
	tConditionTwoValue conditionDefFeScCopyConstruct( conditionDefFeSc );

	iReturn += testCompareTwoEqualObjects( conditionDefFeScCopyConstruct, "conditionDefFeScCopyConstruct", conditionDefFeSc, "conditionDefFeSc" );
	//check the getDefiningFibElement() methode from tConditionTwoValue
	if ( conditionDefFeScCopyConstruct.getDefiningFibElement() == &rootSimple ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionDefFeScCopyConstruct.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionDefFeScCopyConstruct.getDefiningFibElement() <<" but should be rootSimple ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from tConditionTwoValue
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
	//check the getDefiningFibElement() methode from tConditionTwoValue
	if ( pConditionDefFeUfClone->getDefiningFibElement() == &rootSimple ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			pConditionDefFeUfClone->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			pConditionDefFeUfClone->getDefiningFibElement() <<" but should be rootSimple ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from tConditionTwoValue
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a tConditionTwoValue with a superior condition and defining Fib-element which will be changed"<<endl;

	//condition with defining Fib-element and superior condition
	cout<<"cRoot rootSimple2;"<<endl;
	cRoot rootSimple2;
	cout<<"tConditionTwoValue conditionSup2( NULL, NULL );"<<endl;
	tConditionTwoValue conditionSup2( NULL, NULL );

	cout<<"tConditionTwoValue conditionDefFeScCopy2Construct( conditionDefFeSc, &conditionSup2, &rootSimple2 );"<<endl;
	tConditionTwoValue conditionDefFeScCopy2Construct( conditionDefFeSc, &conditionSup2, &rootSimple2 );

	iReturn += testCompareTwoEqualObjects( conditionDefFeScCopy2Construct, "conditionDefFeScCopy2Construct", conditionDefFeSc, "conditionDefFeSc" );
	//check the getDefiningFibElement() methode from tConditionTwoValue
	if ( conditionDefFeScCopy2Construct.getDefiningFibElement() == &rootSimple2 ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionDefFeScCopy2Construct.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionDefFeScCopy2Construct.getDefiningFibElement() <<" but should be rootSimple2 ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from tConditionTwoValue
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
	//check the getDefiningFibElement() methode from tConditionTwoValue
	if ( pConditionDefFeUfClone->getDefiningFibElement() == &rootSimple2 ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			pConditionDefFeUfClone->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			pConditionDefFeUfClone->getDefiningFibElement() <<" but should be rootSimple2 ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from tConditionTwoValue
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a tConditionTwoValue with a true and false subcondition"<<endl;
	
	//condition with defining Fib-element and superior condition
	cout<<"cRoot rootSimpleTrueFalse;"<<endl;
	cRoot rootSimpleTrueFalse;
	cout<<"tConditionTwoValue conditionSup2( NULL, NULL );"<<endl;
	tConditionTwoValue conditionSu2p( NULL, NULL );
	cout<<"tConditionTwoValue conditionTrueFalse( subConditionTrue, subConditionFalse, & conditionSup2, &rootSimpleTrueFalse );"<<endl;
	tConditionTwoValue conditionTrueFalse( subConditionTrue, subConditionFalse, & conditionSup2, &rootSimpleTrueFalse );

	cout<<"tConditionTwoValue conditionTrueFalseCopyConstruct( conditionTrueFalse );"<<endl;
	tConditionTwoValue conditionTrueFalseCopyConstruct( conditionTrueFalse );

	iReturn += testCompareTwoEqualObjects( conditionTrueFalseCopyConstruct, "conditionTrueFalseCopyConstruct", conditionTrueFalse, "conditionTrueFalse" );
	//check the getDefiningFibElement() methode from tConditionTwoValue
	if ( conditionTrueFalseCopyConstruct.getDefiningFibElement() == &rootSimpleTrueFalse ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionTrueFalseCopyConstruct.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionTrueFalseCopyConstruct.getDefiningFibElement() <<" but should be rootSimpleTrueFalse ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from tConditionTwoValue
	if ( conditionTrueFalseCopyConstruct.getSuperiorCondition() == NULL ){
	
		cout<<"The superior condition of the condition correctly "<<
			conditionTrueFalseCopyConstruct.getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			conditionTrueFalseCopyConstruct.getSuperiorCondition() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	
	cout<<"cCondition * pConditionTrueFalse = conditionTrueFalseCopyConstruct.clone();"<<endl;
	cCondition * pConditionTrueFalse = conditionTrueFalseCopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pConditionTrueFalse, "pConditionTrueFalse", conditionTrueFalse, "conditionTrueFalse" );
	//check the getDefiningFibElement() methode from tConditionTwoValue
	if ( pConditionTrueFalse->getDefiningFibElement() == &rootSimpleTrueFalse ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			pConditionTrueFalse->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			pConditionTrueFalse->getDefiningFibElement() <<" but should be rootSimpleTrueFalse ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from tConditionTwoValue
	if ( pConditionTrueFalse->getSuperiorCondition() == NULL ){
	
		cout<<"The superior condition of the condition correctly "<<
			pConditionTrueFalse->getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			pConditionTrueFalse->getSuperiorCondition() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	delete pConditionTrueFalse;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a tConditionTwoValue with a NULL and false subcondition"<<endl;
	
	//condition with defining Fib-element and superior condition
	cout<<"cRoot rootSimple3;"<<endl;
	cRoot rootSimple3;
	cout<<"tConditionTwoValue conditionSup3( NULL, NULL );"<<endl;
	tConditionTwoValue conditionSup3( NULL, NULL );
	cout<<"tConditionTwoValue conditionNullFalse( NULL, new cConditionTrue(), & conditionSup3, &rootSimple3 );"<<endl;
	tConditionTwoValue conditionNullFalse( NULL, new cConditionTrue(), & conditionSup3, &rootSimple3 );

	cout<<"tConditionTwoValue conditionNullFalseCopyConstruct( conditionNullFalse );"<<endl;
	tConditionTwoValue conditionNullFalseCopyConstruct( conditionNullFalse );

	iReturn += testCompareTwoEqualObjects( conditionNullFalseCopyConstruct, "conditionNullFalseCopyConstruct", conditionNullFalse, "conditionNullFalse" );
	//check the getDefiningFibElement() methode from tConditionTwoValue
	if ( conditionNullFalseCopyConstruct.getDefiningFibElement() == &rootSimple3 ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionNullFalseCopyConstruct.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionNullFalseCopyConstruct.getDefiningFibElement() <<" but should be rootSimple3 ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from tConditionTwoValue
	if ( conditionNullFalseCopyConstruct.getSuperiorCondition() == NULL ){
	
		cout<<"The superior condition of the condition correctly "<<
			conditionNullFalseCopyConstruct.getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			conditionNullFalseCopyConstruct.getSuperiorCondition() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	
	cout<<"cCondition * pConditionNullFalse = conditionNullFalseCopyConstruct.clone();"<<endl;
	cCondition * pConditionNullFalse = conditionNullFalseCopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pConditionNullFalse, "pConditionNullFalse", conditionNullFalse, "conditionNullFalse" );
	//check the getDefiningFibElement() methode from tConditionTwoValue
	if ( pConditionNullFalse->getDefiningFibElement() == &rootSimple3 ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			pConditionNullFalse->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			pConditionNullFalse->getDefiningFibElement() <<" but should be rootSimple3 ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from tConditionTwoValue
	if ( pConditionNullFalse->getSuperiorCondition() == NULL ){
	
		cout<<"The superior condition of the condition correctly "<<
			pConditionNullFalse->getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			pConditionNullFalse->getSuperiorCondition() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	delete pConditionNullFalse;


	return iReturn;
}



/**
 * This method tests a in the xml -format stored tConditionTwoValue.
 * The condition of the tConditionTwoValue should be a value condition
 * ( tConditionTwoValue ).
 *
 * @param szFilename the name of the file wher the tConditionTwoValue is stored
 * @param ucSubCondition1 if the first subcondition is a NULL pointer (=0), a
 * 	cConditionTrue (=1) or cConditionFalse (=2)
 * @param ucSubCondition2 if the second subcondition is a NULL pointer (=0), a
 * 	cConditionTrue (=1) or cConditionFalse (=2)
 * @return the number of errors occured in the test
 */
template <class tConditionTwoValue>
	int testXmlConditionValue( const string szFilename, unsigned char ucSubCondition1=0,
			unsigned char ucSubCondition2=0 ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored tConditionTwoValue:"<<endl;
	
	TiXmlDocument xmlDotConditionTwoValue( szFilename );
	bool loadOkay = xmlDotConditionTwoValue.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDotConditionTwoValue );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlHandleRoot(0);

	pXmlElement = xmlHandle.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();
		
		const string szConditionTwoValuesElementName = getConditionName<tConditionTwoValue>();
		if ( szElementName == szConditionTwoValuesElementName ){
			cout<<"The root element is correctly named \""<< szConditionTwoValuesElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \""<< szConditionTwoValuesElementName <<"\"."<<endl;
			iReturn++;
		}
		
	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}

	//check the subconditions
	xmlHandleRoot = TiXmlHandle( pXmlElement );
	pXmlElement = xmlHandleRoot.FirstChild().Element();
	
	//check the underfunctions
	if ( pXmlElement ) {
		
		string szElementName = pXmlElement->Value();
		const string szSubconditionElementName = ((ucSubCondition1==1)?"true":"false");
		if ( szElementName == szSubconditionElementName ){
			cout<<"The subcondition is correctly named \""<< szSubconditionElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the subcondition is "<< szElementName <<" and not \""<< szSubconditionElementName <<"\"."<<endl;
			iReturn++;
		}
		
		//check second subcondition
		pXmlElement = pXmlElement->NextSiblingElement();
		//check the underfunctions
		if ( pXmlElement ) {
			
			string szElementName = pXmlElement->Value();
			const string szSubconditionElementName = ((ucSubCondition2==1)?"true":"false");
			if ( szElementName == szSubconditionElementName ){
				cout<<"The subcondition is correctly named \""<< szSubconditionElementName <<"\". "<<endl;
			
			}else{
				cerr<<"Error: The name of the subcondition is "<< szElementName <<" and not \""<< szSubconditionElementName <<"\"."<<endl;
				iReturn++;
			}
			
		}else{// pXmlElement == NULL ->no root handle
			if ( ucSubCondition2 == 0 ){
				cout<<"Ther is correctly no second subcondition. "<<endl;
			}else{
				cerr<<"Error: No subcondition handle in \""<< szFilename <<"\"."<<endl;
				iReturn++;
			}
		}
	}else{// pXmlElement == NULL ->no root handle
		if ( ucSubCondition1 == 0 ){
			cout<<"Ther is correctly no first subcondition. "<<endl;
		}else{
			cerr<<"Error: No subcondition handle in \""<< szFilename <<"\"."<<endl;
			iReturn++;
		}
	}


	return iReturn;
}



/**
 * This method tests the storeXml() method of the tConditionTwoValue class.
 * Just storing properties with no underobjects is tested.
 *
 * methods tested:
 * 	- bool storeXml( ostream &stream ) const;
 * 	- cCondition * restoreXml( const TiXmlElement * pXmlElement, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, cCondition * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
template <class tConditionTwoValue>
	int testStoreXml( unsigned long &ulTestphase ){

	unsigned int iReturn = 0;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an "<<
		getConditionName<tConditionTwoValue>()<<" condition"<<endl;

	cout<<"tConditionTwoValue conditionTwoValues1( NULL, NULL );"<<endl;
	tConditionTwoValue conditionTwoValues1( NULL, NULL );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * szXmlConditionTwoValuesFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "conditionTwoValuesNull.xml" );
	ofstream * pFileCondition = new ofstream( szXmlConditionTwoValuesFileName );
	
	bool bStoreSuccesfull = conditionTwoValues1.storeXml( *pFileCondition );
	delete pFileCondition;
	
	if ( ! bStoreSuccesfull ){
	
		cout<<"The data of the tConditionTwoValue was correctly stored not successfull to the file \""<< szXmlConditionTwoValuesFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the tConditionTwoValue to the file \""<< szXmlConditionTwoValuesFileName <<"\" was successfull."<<endl;
		iReturn++;
	}
	iReturn += testXmlConditionValue<tConditionTwoValue>( szXmlConditionTwoValuesFileName );
	
	TiXmlDocument xmlDotConditionTwoValue( szFileNameBuffer );
	bool loadOkay = xmlDotConditionTwoValue.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"TiXmlHandle xmlHandle2( &xmlDotConditionTwoValue ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDotConditionTwoValue );
		cout<<"tConditionTwoValue pUnderConditionTwoValues1Loaded = cCondition::restoreXml("<<
			"xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cCondition * pUnderConditionTwoValues1Loaded = cCondition::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus != 0 ){
		
			cout<<"The data was loaded not successfull (outStatus="<< outStatus <<"). "<<endl;
		}else{
			cerr<<"Error: Data was loaded not successfull."<<endl;
			iReturn++;
		}
		if ( pUnderConditionTwoValues1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionTwoValues1Loaded, "pUnderConditionTwoValues1Loaded", conditionTwoValues1, "conditionTwoValues1" );
			iReturn += testNotConnectedCondition( * pUnderConditionTwoValues1Loaded );
			delete pUnderConditionTwoValues1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"tConditionTwoValue conditionSup( NULL, NULL );"<<endl;
		tConditionTwoValue conditionSup( NULL, NULL );

		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"TiXmlHandle xmlHandle4( &xmlDotConditionTwoValue ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDotConditionTwoValue );
		cout<<"tConditionTwoValue pUnderConditionTwoValues1LoadedFull = cCondition::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionTwoValues1LoadedFull = cCondition::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &conditionSup, &rootSimple );
		
		if ( outStatus != 0 ){
		
			cout<<"The data was loaded not successfull (outStatus="<< outStatus <<"). "<<endl;
		}else{
			cerr<<"Error: Data was loaded not successfull."<<endl;
			iReturn++;
		}
		if ( pUnderConditionTwoValues1LoadedFull ){
			if ( (pUnderConditionTwoValues1LoadedFull->getType()) == (getConditionType<tConditionTwoValue>()) ){
				cout<<"Correctly an "<<getConditionName<tConditionTwoValue>()<<" condition restored."<<endl;
				//check the first subcondition
				if ( ((tConditionTwoValue*)pUnderConditionTwoValues1LoadedFull)->getFirstSubCondition() == NULL ){
				
					cout<<"The subcondition of the first condition correctly NULL . "<<endl;
				}else{
					cerr<<"Error: The subcondition of the first condition is NULL "<<
						" but should be NULL ."<<endl;
					iReturn++;
				}
				//check the second subcondition
				if ( ((tConditionTwoValue*)pUnderConditionTwoValues1LoadedFull)->getSecondSubCondition() == NULL ){
				
					cout<<"The subcondition of the second condition correctly NULL . "<<endl;
				}else{
					cerr<<"Error: The subcondition of the second condition is NULL "<<
						" but should be NULL ."<<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: Not an "<<getConditionName<tConditionTwoValue>()<<" condition restored."<<endl;
				iReturn++;
			}
			//check the getDefiningFibElement() methode from tConditionTwoValue
			if ( pUnderConditionTwoValues1LoadedFull->getDefiningFibElement() == &rootSimple ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionTwoValues1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionTwoValues1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from tConditionTwoValue
			if ( pUnderConditionTwoValues1LoadedFull->getSuperiorCondition() == &conditionSup ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionTwoValues1LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionTwoValues1LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionTwoValues1LoadedFull;
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
		getConditionName<tConditionTwoValue>()<<" condition with an true and a false subcondition"<<endl;
	
	cout<<"cConditionTrue subConditionTrue;"<<endl;
	cConditionTrue subConditionTrue;
	cout<<"cConditionFalse subConditionFalse;"<<endl;
	cConditionFalse subConditionFalse;
	cout<<"tConditionTwoValue conditionTwoValuesTrueFalse( subConditionTrue, subConditionFalse );"<<endl;
	tConditionTwoValue conditionTwoValuesTrueFalse( subConditionTrue, subConditionFalse );
	
	szFileNameBuffer[0] = 0;
	szXmlConditionTwoValuesFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "conditionTwoValuesTrueFalse.xml" );
	pFileCondition = new ofstream( szXmlConditionTwoValuesFileName );
	
	bStoreSuccesfull = conditionTwoValuesTrueFalse.storeXml( *pFileCondition );
	delete pFileCondition;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the tConditionTwoValue was stored successfull to the file \""<< szXmlConditionTwoValuesFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the tConditionTwoValue to the file \""<< szXmlConditionTwoValuesFileName <<"\" failed."<<endl;
		iReturn++;
	}
	iReturn += testXmlConditionValue<tConditionTwoValue>( szXmlConditionTwoValuesFileName, 1, 2 );
	
	TiXmlDocument xmlDotConditionTwoValueTrue( szFileNameBuffer );
	loadOkay = xmlDotConditionTwoValueTrue.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"TiXmlHandle xmlHandle2( &xmlDotConditionTwoValueTrue ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDotConditionTwoValueTrue );
		cout<<"tConditionTwoValue * pUnderConditionTwoValues1Loaded = cCondition::restoreXml("<<
			"xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cCondition * pUnderConditionTwoValues1Loaded = cCondition::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionTwoValues1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionTwoValues1Loaded, "pUnderConditionTwoValues1Loaded", conditionTwoValuesTrueFalse, "conditionTwoValuesTrueFalse" );
			iReturn += testNotConnectedCondition( * pUnderConditionTwoValues1Loaded );
			delete pUnderConditionTwoValues1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"tConditionTwoValue conditionSup( NULL, NULL );"<<endl;
		tConditionTwoValue conditionSup( NULL, NULL );

		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"TiXmlHandle xmlHandle4( &xmlDotConditionTwoValueTrue ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDotConditionTwoValueTrue );
		cout<<"tConditionTwoValue pUnderConditionTwoValues1LoadedFull = cCondition::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionTwoValues1LoadedFull = cCondition::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &conditionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionTwoValues1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionTwoValues1LoadedFull, "pUnderConditionTwoValues1LoadedFull", conditionTwoValuesTrueFalse, "conditionTwoValuesTrueFalse" );
			//check the getDefiningFibElement() methode from tConditionTwoValue
			if ( pUnderConditionTwoValues1LoadedFull->getDefiningFibElement() == &rootSimple ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionTwoValues1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionTwoValues1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from tConditionTwoValue
			if ( pUnderConditionTwoValues1LoadedFull->getSuperiorCondition() == &conditionSup ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionTwoValues1LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionTwoValues1LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionTwoValues1LoadedFull;
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
		getConditionName<tConditionTwoValue>()<<" condition with an false and an true subcondition"<<endl;
	
	cout<<"tConditionTwoValue conditionTwoValueFalseTrue( subConditionFalse, subConditionTrue );"<<endl;
	tConditionTwoValue conditionTwoValueFalseTrue( subConditionFalse, subConditionTrue );
	
	szFileNameBuffer[0] = 0;
	szXmlConditionTwoValuesFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "conditionTwoValueFalseTrue.xml" );
	pFileCondition = new ofstream( szXmlConditionTwoValuesFileName );
	
	bStoreSuccesfull = conditionTwoValueFalseTrue.storeXml( *pFileCondition );
	delete pFileCondition;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the tConditionTwoValue was stored successfull to the file \""<< szXmlConditionTwoValuesFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the tConditionTwoValue to the file \""<< szXmlConditionTwoValuesFileName <<"\" failed."<<endl;
		iReturn++;
	}
	iReturn += testXmlConditionValue<tConditionTwoValue>( szXmlConditionTwoValuesFileName, 2, 1 );
	
	TiXmlDocument xmlDotConditionTwoValueFalse( szFileNameBuffer );
	loadOkay = xmlDotConditionTwoValueFalse.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"TiXmlHandle xmlHandle2( &xmlDotConditionTwoValueFalse ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDotConditionTwoValueFalse );
		cout<<"tConditionTwoValue * pUnderConditionTwoValues1Loaded = cCondition::restoreXml("<<
			"xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cCondition * pUnderConditionTwoValues1Loaded = cCondition::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionTwoValues1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionTwoValues1Loaded, "pUnderConditionTwoValues1Loaded", conditionTwoValueFalseTrue, "conditionTwoValueFalseTrue" );
			iReturn += testNotConnectedCondition( * pUnderConditionTwoValues1Loaded );
			delete pUnderConditionTwoValues1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"tConditionTwoValue conditionSup( NULL, NULL );"<<endl;
		tConditionTwoValue conditionSup( NULL, NULL );

		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"TiXmlHandle xmlHandle4( &xmlDotConditionTwoValueFalse ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDotConditionTwoValueFalse );
		cout<<"tConditionTwoValue pUnderConditionTwoValues1LoadedFull = cCondition::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionTwoValues1LoadedFull = cCondition::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &conditionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionTwoValues1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionTwoValues1LoadedFull, "pUnderConditionTwoValues1LoadedFull", conditionTwoValueFalseTrue, "conditionTwoValueFalseTrue" );
			//check the getDefiningFibElement() methode from tConditionTwoValue
			if ( pUnderConditionTwoValues1LoadedFull->getDefiningFibElement() == &rootSimple ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionTwoValues1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionTwoValues1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from tConditionTwoValue
			if ( pUnderConditionTwoValues1LoadedFull->getSuperiorCondition() == &conditionSup ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionTwoValues1LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionTwoValues1LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionTwoValues1LoadedFull;
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
		getConditionName<tConditionTwoValue>()<<" condition with an true and an Null subcondition"<<endl;
	
	cout<<"tConditionTwoValue conditionTwoValueTrueNull( new cConditionTrue(), NULL );"<<endl;
	tConditionTwoValue conditionTwoValueTrueNull( new cConditionTrue(), NULL );
	
	szFileNameBuffer[0] = 0;
	szXmlConditionTwoValuesFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "conditionTwoValueTrueNull.xml" );
	pFileCondition = new ofstream( szXmlConditionTwoValuesFileName );
	
	bStoreSuccesfull = conditionTwoValueTrueNull.storeXml( *pFileCondition );
	delete pFileCondition;
	
	if ( ! bStoreSuccesfull ){
	
		cout<<"The data of the tConditionTwoValue was correctly not stored successfull to the file \""<< szXmlConditionTwoValuesFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the tConditionTwoValue to the file \""<< szXmlConditionTwoValuesFileName <<"\" successfull."<<endl;
		iReturn++;
	}
	iReturn += testXmlConditionValue<tConditionTwoValue>( szXmlConditionTwoValuesFileName, 1, 0 );
	
	TiXmlDocument xmlDotConditionTwoValueTrueNull( szFileNameBuffer );
	loadOkay = xmlDotConditionTwoValueTrueNull.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"TiXmlHandle xmlHandle2( &xmlDotConditionTwoValueTrueNull ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDotConditionTwoValueTrueNull );
		cout<<"tConditionTwoValue * pUnderConditionTwoValues1Loaded = cCondition::restoreXml("<<
			"xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cCondition * pUnderConditionTwoValues1Loaded = cCondition::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus != 0 ){
		
			cout<<"The data was loaded not successfull (outStatus="<< outStatus <<"). "<<endl;
		}else{
			cerr<<"Error: Data was loaded not successfull."<<endl;
			iReturn++;
		}
		if ( pUnderConditionTwoValues1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionTwoValues1Loaded, "pUnderConditionTwoValues1Loaded", conditionTwoValueTrueNull, "conditionTwoValueTrueNull" );
			iReturn += testNotConnectedCondition( * pUnderConditionTwoValues1Loaded );
			delete pUnderConditionTwoValues1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"tConditionTwoValue conditionSup( NULL, NULL );"<<endl;
		tConditionTwoValue conditionSup( NULL, NULL );

		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"TiXmlHandle xmlHandle4( &xmlDotConditionTwoValueTrueNull ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDotConditionTwoValueTrueNull );
		cout<<"tConditionTwoValue pUnderConditionTwoValues1LoadedFull = cCondition::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionTwoValues1LoadedFull = cCondition::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &conditionSup, &rootSimple );
		
		if ( outStatus != 0 ){
		
			cout<<"The data was loaded not successfull (outStatus="<< outStatus <<"). "<<endl;
		}else{
			cerr<<"Error: Data was loaded not successfull."<<endl;
			iReturn++;
		}
		if ( pUnderConditionTwoValues1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionTwoValues1LoadedFull, "pUnderConditionTwoValues1LoadedFull", conditionTwoValueTrueNull, "conditionTwoValueTrueNull" );
			//check the getDefiningFibElement() methode from tConditionTwoValue
			if ( pUnderConditionTwoValues1LoadedFull->getDefiningFibElement() == &rootSimple ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionTwoValues1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionTwoValues1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from tConditionTwoValue
			if ( pUnderConditionTwoValues1LoadedFull->getSuperiorCondition() == &conditionSup ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionTwoValues1LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionTwoValues1LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionTwoValues1LoadedFull;
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
template <class tConditionTwoValue>
		int testStore( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an true and false subcondition"<<endl;

	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;
	
	cout<<"cConditionTrue subConditionTrue;"<<endl;
	cConditionTrue subConditionTrue;
	cout<<"cConditionFalse subConditionFalse;"<<endl;
	cConditionFalse subConditionFalse;
	
	cout<<"tConditionTwoValue conditionTwoValues1( subConditionTrue, subConditionFalse, NULL, &root );"<<endl;
	tConditionTwoValue conditionTwoValues1( subConditionTrue, subConditionFalse, NULL, &root );

	//test get compressed size
	unsigned int uiCompressedSize = 12;
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
	short sNumberOfRestBitCorrect = 4;
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
	const char tConditionTwoValue1[] = { (char)(0xF0 | getTypeBit<tConditionTwoValue>()), (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, tConditionTwoValue1, 2 );


	cDomainSingle * pValueDomain = new cDomainNaturalNumberBit( 16 );
	cDomainSingle * pVariableDomain = new cDomainNaturalNumberBit( 3 );
	
	ifstream * pFileIn = new ifstream( szFileNameBuffer );
	if ( (pFileIn != NULL) && ( pFileIn->good() ) ){
		
		cReadBits iBitStream2( * pFileIn );
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"tConditionTwoValue pUnderConditionTwoValues1Loaded = cCondition::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cCondition * pUnderConditionTwoValues1Loaded = cCondition::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pValueDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionTwoValues1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionTwoValues1Loaded, "pUnderConditionTwoValues1Loaded", conditionTwoValues1, "conditionTwoValues1" );
			iReturn += testNotConnectedCondition( * pUnderConditionTwoValues1Loaded );
			delete pUnderConditionTwoValues1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"tConditionTwoValue conditionSup( NULL, NULL );"<<endl;
		tConditionTwoValue conditionSup( NULL, NULL );
		
		delete pFileIn;

		pFileIn = new ifstream( szFileNameBuffer );
		cReadBits iBitStream4( * pFileIn );
		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"tConditionTwoValue pUnderConditionTwoValues1LoadedFull = cCondition::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionTwoValues1LoadedFull = cCondition::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&conditionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionTwoValues1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionTwoValues1LoadedFull, "pUnderConditionTwoValues1LoadedFull", conditionTwoValues1, "conditionTwoValues1" );
			//check the getDefiningFibElement() methode from tConditionTwoValue
			if ( pUnderConditionTwoValues1LoadedFull->getDefiningFibElement() == &rootSimple ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionTwoValues1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionTwoValues1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from tConditionTwoValue
			if ( pUnderConditionTwoValues1LoadedFull->getSuperiorCondition() == &conditionSup ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionTwoValues1LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionTwoValues1LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionTwoValues1LoadedFull;
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


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an false and true subcondition"<<endl;

	cout<<"tConditionTwoValue conditionTwoValuesFalseTrue( subConditionFalse, subConditionTrue, NULL, &root );"<<endl;
	tConditionTwoValue conditionTwoValuesFalseTrue( subConditionFalse, subConditionTrue, NULL, &root );

	//test get compressed size
	uiCompressedSize = 12;
	if ( (unsigned int)(conditionTwoValuesFalseTrue.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			conditionTwoValuesFalseTrue.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "conditionTwoValuesTrue.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x00;
	cRestBitPosition = 0;
	cout<<"conditionTwoValuesFalseTrue.store( *pFile, cRestBits, cRestBitPosition );"<<endl;
	bStoreSuccesfull = conditionTwoValuesFalseTrue.store( *pFile, cRestBit, cRestBitPosition );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = (char)0x0F;
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
	const char tConditionTwoValueTrueFalse[] = { (char)(0x00 | getTypeBit<tConditionTwoValue>()), (char)0x0F };
	iReturn += compareBytsWithFile( szFileNameBuffer, tConditionTwoValueTrueFalse, 2 );
	
	pFileIn = new ifstream( szFileNameBuffer );
	if ( (pFileIn != NULL) && ( pFileIn->good() ) ){
		
		cReadBits iBitStream2( * pFileIn );
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"tConditionTwoValue pUnderConditionTwoValues1Loaded = cCondition::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cCondition * pUnderConditionTwoValues1Loaded = cCondition::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pValueDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionTwoValues1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionTwoValues1Loaded, "pUnderConditionTwoValues1Loaded", conditionTwoValuesFalseTrue, "conditionTwoValuesFalseTrue" );
			iReturn += testNotConnectedCondition( * pUnderConditionTwoValues1Loaded );
			delete pUnderConditionTwoValues1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"tConditionTwoValue conditionSup( NULL, NULL );"<<endl;
		tConditionTwoValue conditionSup( NULL, NULL );
		
		delete pFileIn;

		pFileIn = new ifstream( szFileNameBuffer );
		cReadBits iBitStream4( * pFileIn );
		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"tConditionTwoValue pUnderConditionTwoValues1LoadedFull = cCondition::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionTwoValues1LoadedFull = cCondition::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&conditionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionTwoValues1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionTwoValues1LoadedFull, "pUnderConditionTwoValues1LoadedFull", conditionTwoValuesFalseTrue, "conditionTwoValuesFalseTrue" );
			//check the getDefiningFibElement() methode from tConditionTwoValue
			if ( pUnderConditionTwoValues1LoadedFull->getDefiningFibElement() == &rootSimple ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionTwoValues1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionTwoValues1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from tConditionTwoValue
			if ( pUnderConditionTwoValues1LoadedFull->getSuperiorCondition() == &conditionSup ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionTwoValues1LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionTwoValues1LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionTwoValues1LoadedFull;
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


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with given restbit"<<endl;

	cout<<"tConditionTwoValue conditionTwoValues2( subConditionFalse, subConditionTrue, NULL, &root );"<<endl;
	tConditionTwoValue conditionTwoValues2( subConditionFalse, subConditionTrue, NULL, &root );
	
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
	ucRestBitCorrect = (char)0x3C;
	sNumberOfRestBitCorrect = 6;
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
	char cTypeBit = getTypeBit<tConditionTwoValue>();
	cTypeBit = cTypeBit << 2;
	//test stored data
	const char szUnderConditionTwoValues2[] = { (char)(0x01 | cTypeBit), (char)0x3C };
	iReturn += compareBytsWithFile( szFileNameBuffer, szUnderConditionTwoValues2, 2 );


	pFileIn = new ifstream( szFileNameBuffer );
	if ( (pFileIn != NULL) && ( pFileIn->good() ) ){
		
		char cBuffer;
		cReadBits iBitStream2( * pFileIn );
		iBitStream2.readBits( &cBuffer, 2 );
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"tConditionTwoValue pUnderConditionTwoValues3Loaded = cCondition::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cCondition * pUnderConditionTwoValues3Loaded = cCondition::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pValueDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionTwoValues3Loaded ){
			const int iErrorsEqual = testCompareTwoEqualObjects( 
				* pUnderConditionTwoValues3Loaded, "pUnderConditionTwoValues3Loaded", conditionTwoValues2, "conditionTwoValues2" );
			iReturn += testNotConnectedCondition( * pUnderConditionTwoValues3Loaded );
			if ( iErrorsEqual != 0 ){
				cerr<<"Error: Loaded condition not equal."<<endl;
			}
			iReturn += iErrorsEqual;
			delete pUnderConditionTwoValues3Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"tConditionTwoValue conditionSup( NULL, NULL );"<<endl;
		tConditionTwoValue conditionSup( NULL, NULL );
		
		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer );
		cReadBits iBitStream4( * pFileIn );
		iBitStream4.readBits( &cBuffer, 2 );
		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"tConditionTwoValue pUnderConditionTwoValues3LoadedFull = cCondition::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionTwoValues3LoadedFull = cCondition::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&conditionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionTwoValues3LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionTwoValues3LoadedFull, "pUnderConditionTwoValues3LoadedFull", conditionTwoValues2, "conditionTwoValues2" );
			//check the getDefiningFibElement() methode from tConditionTwoValue
			if ( pUnderConditionTwoValues3LoadedFull->getDefiningFibElement() == &rootSimple ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionTwoValues3LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionTwoValues3LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from tConditionTwoValue
			if ( pUnderConditionTwoValues3LoadedFull->getSuperiorCondition() == &conditionSup ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionTwoValues3LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionTwoValues3LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionTwoValues3LoadedFull;
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


	delete pValueDomain;
	delete pVariableDomain;

	return iReturn;
}


/**
 * This method tests the subcondtion methods of the tConditionTwoValue class.
 *
 * methods tested:
 * 	- cCondition * getFirstSubCondition();
 * 	- bool setFirstSubCondition( cCondition * pInSubCondition, bool bDeleteOld=true );
 * 	- bool setFirstSubCondition( const cCondition & pInSubCondition, bool bDeleteOld=true );
 * 	- cCondition * getSecondSubCondition();
 * 	- bool setSecondSubCondition( cCondition * pInSubCondition, bool bDeleteOld=true );
 * 	- bool setSecondSubCondition( const cCondition & pInSubCondition, bool bDeleteOld=true );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
template <class tConditionTwoValue>
		int testSubCondition( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the subcondtion methods ( setSubCondition( cCondition * ) )"<<endl;
	
	cout<<"cPoint point;"<<endl;
	cPoint point;
	cout<<"cRoot root( &point );"<<endl;
	cRoot root( &point );
	
	cout<<"cConditionTrue conditionTrue;"<<endl;
	cConditionTrue conditionTrue;
	cout<<"cConditionFalse conditionFalse;"<<endl;
	cConditionFalse conditionFalse;
	
	cout<<"cConditionNot conditionNot( new cConditionTrue() );"<<endl;
	cConditionNot conditionNot( new cConditionTrue() );
	
	cCondition * pFirstSubCondition = NULL;
	bool bFirstSubConditionValue = false;
	bool bFirstSubConditionIsPointer = true;
	cCondition * pSecondSubCondition = NULL;
	bool bSecondSubConditionValue = false;
	bool bSecondSubConditionIsPointer = true;
	cCondition * pOldCondition = NULL;
	cout<<"pConditionTwoValue = new tConditionTwoValue( "<<
		pFirstSubCondition<<", "<<pSecondSubCondition<<", NULL, &point );"<<endl;
	tConditionTwoValue * pConditionTwoValue = new tConditionTwoValue( NULL, NULL, NULL, &point );
	bool bIsValid = false;
	
	for ( unsigned int uiIteration = 1; uiIteration <= 256; uiIteration++ ){
		
		cout<<endl;
		if ( (rand() % 16) == 0 ){
			//create new condition
			if ( pConditionTwoValue ){
				delete pConditionTwoValue;
				pConditionTwoValue = NULL;
				pFirstSubCondition = NULL;
				pSecondSubCondition = NULL;
				bFirstSubConditionValue = false;
				bSecondSubConditionValue = false;
				bFirstSubConditionIsPointer = true;
				bSecondSubConditionIsPointer = true;
			}
			if ( rand() % 4 ){
				if ( rand() % 2 ){
					pFirstSubCondition = new cConditionTrue();
					bFirstSubConditionValue = true;
				}else{
					pFirstSubCondition = new cConditionFalse();
					bFirstSubConditionValue = false;
				}
			}
			if ( rand() % 4 ){
				if ( rand() % 2 ){
					pSecondSubCondition = new cConditionTrue();
					bSecondSubConditionValue = true;
				}else{
					pSecondSubCondition = new cConditionFalse();
					bSecondSubConditionValue = false;
				}
			}
			cout<<"pConditionTwoValue = new tConditionTwoValue( "<<
				pFirstSubCondition<<", "<<pSecondSubCondition<<", NULL, &point );"<<endl;
			pConditionTwoValue = new tConditionTwoValue( pFirstSubCondition, pSecondSubCondition, NULL, &point );
		}else{
			switch ( rand() % 20 ){
				case 0:
					//set first subcondition
					pFirstSubCondition = new cConditionTrue();
					cout<<"pFirstSubCondition("<<pFirstSubCondition<<") = new conditionTrue();"<<endl;
					bFirstSubConditionValue = true;
					bFirstSubConditionIsPointer = true;
					cout<<"pConditionTwoValue->setFirstSubCondition( "<<pFirstSubCondition<<" );"<<endl;
					pConditionTwoValue->setFirstSubCondition( pFirstSubCondition );
				break;
				case 1:
					//set first subcondition
					pFirstSubCondition = &conditionTrue;
					bFirstSubConditionValue = true;
					bFirstSubConditionIsPointer = false;
					cout<<"pConditionTwoValue->setFirstSubCondition( conditionTrue );"<<endl;
					pConditionTwoValue->setFirstSubCondition( conditionTrue );
				break;
				case 2:
					//set first subcondition
					pFirstSubCondition = new cConditionFalse();
					cout<<"pFirstSubCondition("<<pFirstSubCondition<<") = new conditionFalse();"<<endl;
					bFirstSubConditionValue = false;
					bFirstSubConditionIsPointer = true;
					cout<<"pConditionTwoValue->setFirstSubCondition( "<<pFirstSubCondition<<" );"<<endl;
					pConditionTwoValue->setFirstSubCondition( pFirstSubCondition );
				break;
				case 3:
					//set first subcondition
					pFirstSubCondition = &conditionFalse;
					bFirstSubConditionValue = false;
					bFirstSubConditionIsPointer = false;
					cout<<"pConditionTwoValue->setFirstSubCondition( conditionFalse );"<<endl;
					pConditionTwoValue->setFirstSubCondition( conditionFalse );
				break;
				case 4:
					//set first subcondition
					cout<<"pConditionTwoValue->setFirstSubCondition( NULL );"<<endl;
					pConditionTwoValue->setFirstSubCondition( NULL );
				break;
				
				//delete old = false
				case 5:
					//set first subcondition
					pFirstSubCondition = new cConditionTrue();
					cout<<"pFirstSubCondition("<<pFirstSubCondition<<") = new conditionTrue();"<<endl;
					bFirstSubConditionValue = true;
					bFirstSubConditionIsPointer = true;
					pOldCondition = pConditionTwoValue->getFirstSubCondition();
					cout<<"pConditionTwoValue->setFirstSubCondition( "<<pFirstSubCondition<<", false );"<<endl;
					pConditionTwoValue->setFirstSubCondition( pFirstSubCondition, false );
				break;
				case 6:
					//set first subcondition
					pFirstSubCondition = new cConditionFalse();
					cout<<"pFirstSubCondition("<<pFirstSubCondition<<") = new conditionFalse();"<<endl;
					bFirstSubConditionValue = false;
					bFirstSubConditionIsPointer = true;
					pOldCondition = pConditionTwoValue->getFirstSubCondition();
					cout<<"pConditionTwoValue->setFirstSubCondition( "<<pFirstSubCondition<<", false );"<<endl;
					pConditionTwoValue->setFirstSubCondition( pFirstSubCondition, false );
				break;
				case 7:
					//set first subcondition
					cout<<"pConditionTwoValue->setFirstSubCondition( NULL, false );"<<endl;
					pConditionTwoValue->setFirstSubCondition( NULL, false );
				break;
				
			
				case 8:
					//set second subcondition
					pSecondSubCondition = new cConditionTrue();
					cout<<"pSecondSubCondition("<<pSecondSubCondition<<") = new cConditionTrue();"<<endl;
					bSecondSubConditionValue = true;
					bSecondSubConditionIsPointer = true;
					cout<<"pConditionTwoValue->setSecondSubCondition( "<<pSecondSubCondition<<" );"<<endl;
					pConditionTwoValue->setSecondSubCondition( pSecondSubCondition );
				break;
				case 9:
					//set second subcondition
					pSecondSubCondition = &conditionTrue;
					bSecondSubConditionValue = true;
					bSecondSubConditionIsPointer = false;
					cout<<"pConditionTwoValue->setSecondSubCondition( conditionTrue );"<<endl;
					pConditionTwoValue->setSecondSubCondition( conditionTrue );
				break;
				case 10:
					//set second subcondition
					pSecondSubCondition = new cConditionFalse();
					cout<<"pSecondSubCondition("<<pSecondSubCondition<<") = new conditionFalse();"<<endl;
					bSecondSubConditionValue = false;
					bSecondSubConditionIsPointer = true;
					cout<<"pConditionTwoValue->setSecondSubCondition( "<<pSecondSubCondition<<" );"<<endl;
					pConditionTwoValue->setSecondSubCondition( pSecondSubCondition );
				break;
				case 11:
					//set second subcondition
					pSecondSubCondition = &conditionFalse;
					bSecondSubConditionValue = false;
					bSecondSubConditionIsPointer = false;
					cout<<"pConditionTwoValue->setSecondSubCondition( conditionFalse );"<<endl;
					pConditionTwoValue->setSecondSubCondition( conditionFalse );
				break;
				case 12:
					//set second subcondition
					cout<<"pConditionTwoValue->setSecondSubCondition( NULL );"<<endl;
					pConditionTwoValue->setSecondSubCondition( NULL );
				break;
				
				//delete old = false
				case 13:
					//set second subcondition
					pSecondSubCondition = new cConditionTrue();
					cout<<"pSecondSubCondition("<<pSecondSubCondition<<") = new conditionTrue();"<<endl;
					bSecondSubConditionValue = true;
					bSecondSubConditionIsPointer = true;
					pOldCondition = pConditionTwoValue->getSecondSubCondition();
					cout<<"pConditionTwoValue->setSecondSubCondition( "<<pSecondSubCondition<<", false );"<<endl;
					pConditionTwoValue->setSecondSubCondition( pSecondSubCondition, false );
				break;
				case 14:
					//set second subcondition
					pSecondSubCondition = new cConditionFalse();
					cout<<"pSecondSubCondition("<<pSecondSubCondition<<") = new conditionFalse();"<<endl;
					bSecondSubConditionValue = false;
					bSecondSubConditionIsPointer = true;
					pOldCondition = pConditionTwoValue->getSecondSubCondition();
					cout<<"pConditionTwoValue->setSecondSubCondition( "<<pSecondSubCondition<<", false );"<<endl;
					pConditionTwoValue->setSecondSubCondition( pSecondSubCondition, false );
				break;
				case 15:
					//set second subcondition
					cout<<"pConditionTwoValue->setSecondSubCondition( NULL, false );"<<endl;
					pConditionTwoValue->setSecondSubCondition( NULL, false );
				break;
				
				//create subsubconditions
				case 16:{
					//set second subcondition
					pFirstSubCondition = new cConditionNot( new cConditionTrue() );
					bFirstSubConditionValue = pFirstSubCondition->getValue();
					cout<<"pFirstSubCondition("<<pFirstSubCondition<<") = new cConditionNot( cConditionTrue( "<<
						pFirstSubCondition->getValue()<<" ) );"<<endl;
					bFirstSubConditionIsPointer = true;
					cout<<"pConditionTwoValue->setFirstSubCondition( "<<pFirstSubCondition<<" );"<<endl;
					pConditionTwoValue->setFirstSubCondition( pFirstSubCondition );
				}break;
				case 17:{
					//set second subcondition
					pSecondSubCondition = new cConditionNot( new cConditionTrue() );
					bSecondSubConditionValue = pSecondSubCondition->getValue();
					cout<<"pSecondSubCondition("<<pSecondSubCondition<<") = new cConditionNot( cConditionTrue( "<<
						pSecondSubCondition->getValue()<<" ) );"<<endl;
					bSecondSubConditionIsPointer = true;
					cout<<"pConditionTwoValue->setSecondSubCondition( "<<pSecondSubCondition<<" );"<<endl;
					pConditionTwoValue->setSecondSubCondition( pSecondSubCondition );
				}break;
				case 18:{
					//set second subcondition
					pFirstSubCondition = &conditionNot;
					bFirstSubConditionValue = conditionNot.getValue();
					bFirstSubConditionIsPointer = false;
					cout<<"pConditionTwoValue->setFirstSubCondition( conditionNot );"<<endl;
					pConditionTwoValue->setFirstSubCondition( conditionNot );
				}break;
				case 19:{
					//set second subcondition
					pSecondSubCondition = &conditionNot;
					bSecondSubConditionValue = conditionNot.getValue();
					bSecondSubConditionIsPointer = false;
					cout<<"pConditionTwoValue->setSecondSubCondition( conditionNot );"<<endl;
					pConditionTwoValue->setSecondSubCondition( conditionNot );
				}break;
			}
			if ( pOldCondition ){
				delete pOldCondition;
				pOldCondition = NULL;
			}
		}
		if ( ( pFirstSubCondition != NULL ) && ( pSecondSubCondition != NULL ) ){
			bIsValid = true;
		}else{
			bIsValid = false;
		}
		
		//check the getValue() methode from tConditionTwoValue
		if ( pConditionTwoValue->getValue() == getCorrectValue<tConditionTwoValue>(
				bFirstSubConditionValue, bSecondSubConditionValue ) ){
		
			cout<<"The condition value is correctly "<<
				(pConditionTwoValue->getValue()?"true":"false") <<" . "<<endl;
		}else{
			cerr<<"Error: The condition value is "<<
				(pConditionTwoValue->getValue()?"true":"false") <<" but should be "<<
				(pConditionTwoValue->getValue()?"false":"true") <<" ( first="<<
				(bFirstSubConditionValue?"true":"false")<<", second="<<
				(bSecondSubConditionValue?"true":"false")<<" )."<<endl;
			iReturn++;
		}
		if ( bFirstSubConditionIsPointer ){
			//check the getFirstSubCondition() methode from tConditionTwoValue
			if ( pConditionTwoValue->getFirstSubCondition() == pFirstSubCondition ){
			
				cout<<"The first subcondition of the condition correctly "<<
					pConditionTwoValue->getFirstSubCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The first subcondition of the condition is "<<
					pConditionTwoValue->getFirstSubCondition() <<
					" but should be "<< pFirstSubCondition <<" ."<<endl;
				iReturn++;
			}
		}else{
			//check the getFirstSubCondition() methode from tConditionTwoValue
			if ( *(pConditionTwoValue->getFirstSubCondition()) == *pFirstSubCondition ){
			
				cout<<"The first subcondition of the condition correctly equal to "<<
					pConditionTwoValue->getFirstSubCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The first subcondition of the condition is "<<
					pConditionTwoValue->getFirstSubCondition() <<
					" but should be equal to "<< pFirstSubCondition <<" ."<<endl;
				iReturn++;
			}
		}
		if ( bSecondSubConditionIsPointer ){
			//check the getFirstSubCondition() methode from tConditionTwoValue
			if ( pConditionTwoValue->getSecondSubCondition() == pSecondSubCondition ){
			
				cout<<"The second subcondition of the condition correctly "<<
					pConditionTwoValue->getSecondSubCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The second subcondition of the condition is "<<
					pConditionTwoValue->getSecondSubCondition() <<
					" but should be "<< pSecondSubCondition <<" ."<<endl;
				iReturn++;
			}
		}else{
			//check the getFirstSubCondition() methode from tConditionTwoValue
			if ( *(pConditionTwoValue->getSecondSubCondition()) == *pSecondSubCondition ){
			
				cout<<"The second subcondition of the condition correctly equal to "<<
					pConditionTwoValue->getSecondSubCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The second subcondition of the condition is "<<
					pConditionTwoValue->getSecondSubCondition() <<
					" but should be equal to "<< pSecondSubCondition <<" ."<<endl;
				iReturn++;
			}
		}
		//check the isValid() methode from tConditionTwoValue
		if ( pConditionTwoValue->isValid() == bIsValid ){
		
			cout<<"The condition is correctly "<<(bIsValid?"":"not ")<<"valid . "<<endl;
		}else{
			cerr<<"Error: The condition is "<<(bIsValid?"not ":"")<<"valid ."<<endl;
			iReturn++;
		}
		//check defining Fib-Element of sub and subsubcondition
		if ( pConditionTwoValue->getFirstSubCondition() != NULL ){
			if ( pConditionTwoValue->getFirstSubCondition()->getDefiningFibElement() == &point ){
			
				cout<<"The definig fib-element of the first subcondition is point."<<endl;
			}else{
				cerr<<"Error: The definig fib-element of the first subcondition is not point."<<endl;
				iReturn++;
			}
			if ( pConditionTwoValue->getFirstSubCondition()->getNumberOfConditions() == 1 ){
				
				cConditionNot * pSubCondition = ((cConditionNot*)(pConditionTwoValue->getFirstSubCondition()));
				
				if ( pSubCondition->getSubCondition()->getDefiningFibElement() == &point ){
				
					cout<<"The definig fib-element of the first subsubcondition is point."<<endl;
				}else{
					cerr<<"Error: The definig fib-element of the first subsubcondition is not point."<<endl;
					iReturn++;
				}
			}
		}
		if ( pConditionTwoValue->getSecondSubCondition() != NULL ){
			if ( pConditionTwoValue->getSecondSubCondition()->getDefiningFibElement() == &point ){
			
				cout<<"The definig fib-element of the second subcondition is point."<<endl;
			}else{
				cerr<<"Error: The definig fib-element of the second subcondition is not point."<<endl;
				iReturn++;
			}
			if ( pConditionTwoValue->getSecondSubCondition()->getNumberOfConditions() == 1 ){
				
				cConditionNot * pSubCondition = ((cConditionNot*)(pConditionTwoValue->getSecondSubCondition()));
				
				if ( pSubCondition->getSubCondition()->getDefiningFibElement() == &point ){
				
					cout<<"The definig fib-element of the second subsubcondition is point."<<endl;
				}else{
					cerr<<"Error: The definig fib-element of the second subsubcondition is not point."<<endl;
					iReturn++;
				}
			}
		}
		
	}
	if ( pConditionTwoValue ){
		delete pConditionTwoValue;
		pConditionTwoValue = NULL;
		pFirstSubCondition = NULL;
		pSecondSubCondition = NULL;
	}
	
	return iReturn;
}




/**
 * This method tests the variable methods of the tConditionTwoValue class.
 *
 * methods tested:
 * 	- bool isUsedVariable( const cFibVariable * variable ) const;
 * 	- set<cFibVariable*> getUsedVariables();
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
template <class tConditionTwoValue>
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
	
	cout<<"tConditionTwoValue conditionTwoValues1( NULL, NULL );"<<endl;
	tConditionTwoValue conditionTwoValues1( NULL, NULL );
	
	cout<<"cConditionFalse conditionFalse;"<<endl;
	cConditionFalse conditionFalse;
	cout<<"cConditionTrue conditionTrue;"<<endl;
	cConditionTrue conditionTrue;
	cout<<"tConditionTwoValue conditionTwoValues2( conditionFalse, conditionTrue );"<<endl;
	tConditionTwoValue conditionTwoValues2( conditionFalse, conditionTrue );

	//check the isUsedVariable() methode from tConditionTwoValue
	cout<<"conditionTwoValues1.isUsedVariable( pVariableSimple1 )"<<endl;
	if ( ! conditionTwoValues1.isUsedVariable( pVariableSimple1 ) ){
	
		cout<<"The variable pVariableSimple1 is correctly not used in the condition element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableSimple1 is used in the condition element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = conditionTwoValues1.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = conditionTwoValues1.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"The correctly no used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The ther are used variables given back. "<<endl;
		iReturn++;
	}
	cout<<"conditionTwoValues1.replaceVariable( pVariableSimple1, pVariableSimple1 );"<<endl;
	bool bVariableReplaced = conditionTwoValues1.replaceVariable( pVariableSimple1, pVariableSimple1 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	
	//check the isUsedVariable() methode from tConditionTwoValue
	cout<<"conditionTwoValues2.isUsedVariable( pVariableSimple1 )"<<endl;
	if ( ! conditionTwoValues2.isUsedVariable( pVariableSimple1 ) ){
	
		cout<<"The variable pVariableSimple1 is correctly not used in the condition element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableSimple1 is used in the condition element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = conditionTwoValues2.getUsedVariables(); "<<endl;
	setUsedVariables = conditionTwoValues2.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"The correctly no used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The ther are used variables given back. "<<endl;
		iReturn++;
	}
	cout<<"conditionTwoValues2.replaceVariable( pVariableSimple1, pVariableSimple1 );"<<endl;
	bVariableReplaced = conditionTwoValues2.replaceVariable( pVariableSimple1, pVariableSimple1 );
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
	
	cCondition * pFirstSubCondition = NULL;
	bool bFirstSubConditionValue = false;
	cFibVariable * pVariableFirstSubCondition = NULL;
	
	cCondition * pSecondSubCondition = NULL;
	bool bSecondSubConditionValue = false;
	cFibVariable * pVariableSecondSubCondition = NULL;
	
	cout<<"pConditionTwoValue = new tConditionTwoValue( "<<
		pFirstSubCondition<<", "<<pSecondSubCondition<<", NULL, &point  );"<<endl;
	tConditionTwoValue * pConditionTwoValue = new tConditionTwoValue( NULL, NULL, NULL, &point );
	bool bIsValid = false;
	
	set< cFibVariable* > setCorrectUsedVariables;
	
	for ( unsigned int uiIteration = 1; uiIteration <= 64; uiIteration++ ){
		
		cout<<endl;
		if ( (rand() % 16) == 0 ){
			//create new condition
			if ( pConditionTwoValue ){
				delete pConditionTwoValue;
				pConditionTwoValue = NULL;
				pFirstSubCondition = NULL;
				pSecondSubCondition = NULL;
				bFirstSubConditionValue = false;
				bSecondSubConditionValue = false;
				pVariableFirstSubCondition = NULL;
				pVariableSecondSubCondition = NULL;
			}
			if ( rand() % 4 ){
				if ( rand() % 4 == 0 ){
					pFirstSubCondition = new cConditionGreater(
						new cFunctionValue( domFunValues.round(
							((double)(rand() % (256 * 256))) / 256.0 ) ),
						new cFunctionValue( domFunValues.round(
							((double)(rand() % (256 * 256))) / 256.0 ) ) );
					bFirstSubConditionValue = pFirstSubCondition->getValue();
					cout<<"pFirstSubCondition("<<pFirstSubCondition<<") = new cConditionGreater( "<<
						" cFunctionValue , cFunctionValue );"<<endl;
					pVariableFirstSubCondition = NULL;
				}else{
					const size_t uiChoosenVariable = rand() % vecVariablen.size();
					pFirstSubCondition = new cConditionGreater(
						new cFunctionValue( domFunValues.round(
							((double)(rand() % (256 * 256))) / 256.0 ) ),
						new cFunctionVariable( vecVariablen[ uiChoosenVariable ] ) );
					bFirstSubConditionValue = pFirstSubCondition->getValue();
					cout<<"pFirstSubCondition("<<pFirstSubCondition<<") = new cConditionGreater( "<<
						"cFunctionValue, cFunctionVariable( pVariable"<<uiChoosenVariable<<"="<<
						vecVariablen[ uiChoosenVariable ]<<") );"<<endl;
					pVariableFirstSubCondition = vecVariablen[ uiChoosenVariable ];
				}
			}
			if ( rand() % 4 ){
				if ( rand() % 4 == 0 ){
					pSecondSubCondition = new cConditionGreater(
						new cFunctionValue( domFunValues.round(
							((double)(rand() % (256 * 256))) / 256.0 ) ),
						new cFunctionValue( domFunValues.round(
							((double)(rand() % (256 * 256))) / 256.0 ) ) );
					bSecondSubConditionValue = pSecondSubCondition->getValue();
					cout<<"pSecondSubCondition("<<pSecondSubCondition<<") = new cConditionGreater( "<<
						" cFunctionValue , cFunctionValue );"<<endl;
					pVariableSecondSubCondition = NULL;
				}else{
					const size_t uiChoosenVariable = rand() % vecVariablen.size();
					pSecondSubCondition = new cConditionGreater(
						new cFunctionVariable( vecVariablen[ uiChoosenVariable ] ),
						new cFunctionValue( domFunValues.round(
							((double)(rand() % (256 * 256))) / 256.0 ) ) );
					bSecondSubConditionValue = pSecondSubCondition->getValue();
					cout<<"pSecondSubCondition("<<pSecondSubCondition<<") = new cConditionGreater( "<<
						"cFunctionVariable( pVariable"<<uiChoosenVariable<<"="<<
						vecVariablen[ uiChoosenVariable ]<<"), cFunctionValue );"<<endl;
					pVariableSecondSubCondition = vecVariablen[ uiChoosenVariable ];
				}
			}
			cout<<"pConditionTwoValue = new tConditionTwoValue( "<<
				pFirstSubCondition<<", "<<pSecondSubCondition<<", NULL, &point  );"<<endl;
			pConditionTwoValue = new tConditionTwoValue( pFirstSubCondition, pSecondSubCondition, NULL, &point );
		}else if ( rand() % 2 ){//change subcondition
			
			if ( rand() % 4 ){
				if ( rand() % 2 ){
					//set first subcondition to variable
					const size_t uiChoosenVariable = rand() % vecVariablen.size();
					pFirstSubCondition =  new cConditionGreater(
						new cFunctionVariable( vecVariablen[ uiChoosenVariable ] ),
						new cFunctionValue( domFunValues.round(
							((double)(rand() % (256 * 256))) / 256.0 ) ) );
					bFirstSubConditionValue = pFirstSubCondition->getValue();
					cout<<"pFirstSubCondition("<<pFirstSubCondition<<") = new cConditionGreater( "<<
						"cFunctionVariable( pVariable"<<uiChoosenVariable<<"="<<
						vecVariablen[ uiChoosenVariable ]<<"), cFunctionValue );"<<endl;
					cout<<"pConditionTwoValue->setFirstSubCondition( "<<pFirstSubCondition<<" );"<<endl;
					pConditionTwoValue->setFirstSubCondition( pFirstSubCondition );
					pVariableFirstSubCondition = vecVariablen[ uiChoosenVariable ];
				}else{
					//set second subcondition to variable
					const size_t uiChoosenVariable = rand() % vecVariablen.size();
					pSecondSubCondition = new cConditionGreater(
						new cFunctionValue( domFunValues.round(
							((double)(rand() % (256 * 256))) / 256.0 ) ),
						new cFunctionVariable( vecVariablen[ uiChoosenVariable ] ) );
					bSecondSubConditionValue = pSecondSubCondition->getValue();
					cout<<"pSecondSubCondition("<<pSecondSubCondition<<") = new cConditionGreater( "<<
						"cFunctionValue, cFunctionVariable( pVariable"<<uiChoosenVariable<<"="<<
						vecVariablen[ uiChoosenVariable ]<<") );"<<endl;
					cout<<"pConditionTwoValue->setSecondSubCondition( "<<pSecondSubCondition<<" );"<<endl;
					pConditionTwoValue->setSecondSubCondition( pSecondSubCondition );
					pVariableSecondSubCondition = vecVariablen[ uiChoosenVariable ];
				}
			}else{//change to value
				if ( rand() % 2 ){
					//set first subcondition to value
					pFirstSubCondition = new cConditionGreater(
						new cFunctionValue( domFunValues.round(
							((double)(rand() % (256 * 256))) / 256.0 ) ),
						new cFunctionValue( domFunValues.round(
							((double)(rand() % (256 * 256))) / 256.0 ) ) );
					cout<<"pFirstSubCondition("<<pFirstSubCondition<<") = new cConditionGreater( "<<
						" cFunctionValue , cFunctionValue );"<<endl;
					bFirstSubConditionValue = pFirstSubCondition->getValue();
					cout<<"pConditionTwoValue->setFirstSubCondition( "<<pFirstSubCondition<<" );"<<endl;
					pConditionTwoValue->setFirstSubCondition( pFirstSubCondition );
					pVariableFirstSubCondition = NULL;
				}else{
					//set second subcondition to value
					pSecondSubCondition = new cConditionGreater(
						new cFunctionValue( domFunValues.round(
							((double)(rand() % (256 * 256))) / 256.0 ) ),
						new cFunctionValue( domFunValues.round(
							((double)(rand() % (256 * 256))) / 256.0 ) ) );
					bSecondSubConditionValue = pSecondSubCondition->getValue();
					cout<<"pSecondSubCondition("<<pSecondSubCondition<<") = new cConditionGreater( "<<
						" cFunctionValue , cFunctionValue );"<<endl;
					cout<<"pConditionTwoValue->setSecondSubCondition( "<<pSecondSubCondition<<" );"<<endl;
					pConditionTwoValue->setSecondSubCondition( pSecondSubCondition );
					pVariableSecondSubCondition = NULL;
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
					
					cout<<"pConditionTwoValue->replaceVariable( "<<(*itrToReplaceVariable)<<
						", "<< vecVariablen[ uiVariableToReplaceWith ]<<" );"<<endl;
					const bool bVariableReplaced = pConditionTwoValue->replaceVariable(
						(*itrToReplaceVariable), vecVariablen[ uiVariableToReplaceWith ] );
					if ( bVariableReplaced ){
					
						cout<<"The variable was correctly replaced. "<<endl;
					}else{
						cerr<<"Error: The variable was not replaced. "<<endl;
						iReturn++;
					}
					//update values
					if ( pVariableFirstSubCondition == (*itrToReplaceVariable) ){
						bFirstSubConditionValue = pFirstSubCondition->getValue();
						pVariableFirstSubCondition = vecVariablen[ uiVariableToReplaceWith ];
					}
					if ( pVariableSecondSubCondition == (*itrToReplaceVariable) ){
						bSecondSubConditionValue = pSecondSubCondition->getValue();
						pVariableSecondSubCondition = vecVariablen[ uiVariableToReplaceWith ];
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
					
					cout<<"pConditionTwoValue->replaceVariable( "<<
						vecVariablen[ uiVariableToReplace ]<<", "<<
						vecVariablen[ uiVariableToReplaceWith ]<<" );"<<endl;
					const bool bVariableReplaced = pConditionTwoValue->replaceVariable(
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
						
						cout<<"pConditionTwoValue->replaceVariable( NULL,"<<
							vecVariablen[ uiVariableToReplaceWith ]<<" );"<<endl;
						const bool bVariableReplaced = pConditionTwoValue->replaceVariable(
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
						
						cout<<"pConditionTwoValue->replaceVariable( "<<
							vecVariablen[ uiVariableToReplace ]<<", NULL );"<<endl;
						const bool bVariableReplaced = pConditionTwoValue->replaceVariable(
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
				if ( pVariableFirstSubCondition == (*itrToReplaceVariable) ){
					bFirstSubConditionValue = pFirstSubCondition->getValue();
				}
				if ( pVariableSecondSubCondition == (*itrToReplaceVariable) ){
					bSecondSubConditionValue = pSecondSubCondition->getValue();
				}
			}
		}
		setCorrectUsedVariables.clear();
		if ( pVariableFirstSubCondition ){
			setCorrectUsedVariables.insert( pVariableFirstSubCondition );
		}
		if ( pVariableSecondSubCondition ){
			setCorrectUsedVariables.insert( pVariableSecondSubCondition );
		}
		
		if ( ( pFirstSubCondition != NULL ) && ( pSecondSubCondition != NULL ) ){
			bIsValid = true;
		}else{
			bIsValid = false;
		}
		
		//check the isUsedVariable() methode from tConditionTwoValue
		for ( vector< cFibVariable * >::const_iterator itrVariable = vecVariablen.begin();
				itrVariable != vecVariablen.end(); itrVariable++ ){
			
			const bool bShouldBeUsedVariable = setCorrectUsedVariables.find(
					*itrVariable ) != setCorrectUsedVariables.end();
			
			cout<<"pConditionTwoValue->isUsedVariable( "<<(*itrVariable)<<" )"<<endl;
			if ( pConditionTwoValue->isUsedVariable( *itrVariable ) == bShouldBeUsedVariable ){
			
				cout<<"The variable "<<(*itrVariable)<<" is correctly "<<
					(bShouldBeUsedVariable?"":"not ")<<"used in the condition element. "<<endl;
			}else{
				cerr<<"Error: The variable "<<(*itrVariable)<<" is "<<
					(bShouldBeUsedVariable?"not ":"")<<"used in the condition element. "<<endl;
				iReturn++;
			}
		}
		//check getUsedVariables()
		cout<<"setUsedVariables = pConditionTwoValue->getUsedVariables(); "<<endl;
		set<cFibVariable*> setUsedVariables = pConditionTwoValue->getUsedVariables();
		if ( setUsedVariables == setCorrectUsedVariables ){
		
			cout<<"The correct used variables wher given back. "<<endl;
		}else{
			cerr<<"Error: Not correct used variables wher given back. "<<endl;
			setCorrectUsedVariables = setUsedVariables;
			iReturn++;
		}
		
		//check the getValue() methode from tConditionTwoValue
		if ( pConditionTwoValue->getValue() == getCorrectValue<tConditionTwoValue>(
				bFirstSubConditionValue, bSecondSubConditionValue ) ){
	
			cout<<"The condition value is correctly "<<
				(pConditionTwoValue->getValue()?"true":"false") <<" . "<<endl;
		}else{
			cerr<<"Error: The condition value is "<<
				(pConditionTwoValue->getValue()?"true":"false") <<" but should be "<<
				(pConditionTwoValue->getValue()?"false":"true") <<" ( first="<<
				(bFirstSubConditionValue?"true":"false")<<", second="<<
				(bSecondSubConditionValue?"true":"false")<<" )."<<endl;
			iReturn++;
		}
		
		//check the isValid() methode from tConditionTwoValue
		if ( pConditionTwoValue->isValid() == bIsValid ){
		
			cout<<"The condition is correctly "<<(bIsValid?"":"not ")<<"valid . "<<endl;
		}else{
			cerr<<"Error: The condition is "<<(bIsValid?"not ":"")<<"valid ."<<endl;
			iReturn++;
		}
	}
	if ( pConditionTwoValue ){
		delete pConditionTwoValue;
		pConditionTwoValue = NULL;
		pFirstSubCondition = NULL;
		pSecondSubCondition = NULL;
	}
	
	
	return iReturn;
}



/**
 * This method tests the variable methods of the tConditionTwoValue class.
 *
 * methods tested:
 * 	- void setDefiningFibElement( cFibElement *fibElement=NULL, bool bCheckDomains=true );
 * 	- cFibElement * getDefiningFibElement() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
template <class tConditionTwoValue>
	int testDefiningFibElement( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for the defining Fib-element"<<endl;
	
	cout<<"tConditionTwoValue conditionTwoValues1( NULL, NULL );"<<endl;
	tConditionTwoValue conditionTwoValues1( NULL, NULL );
	
	tConditionTwoValue conditionTwoValuesCorrect( NULL, NULL );
	
	cFibElement * pDefiningFibElement = NULL;
	//check the getDefiningFibElement() methode from tConditionTwoValue
	if ( conditionTwoValues1.getDefiningFibElement() == pDefiningFibElement ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionTwoValues1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionTwoValues1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( conditionTwoValues1, "conditionTwoValues1", conditionTwoValuesCorrect, "correct condition" );
	
	cPoint pointDef1;
	cout<<"conditionTwoValues1.setDefiningFibElement( &pointDef1 );"<<endl;
	conditionTwoValues1.setDefiningFibElement( &pointDef1 );
	pDefiningFibElement = &pointDef1;
	//check the getDefiningFibElement() methode from tConditionTwoValue
	if ( conditionTwoValues1.getDefiningFibElement() == pDefiningFibElement ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionTwoValues1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionTwoValues1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( conditionTwoValues1, "conditionTwoValues1", conditionTwoValuesCorrect, "correct condition" );
	
	cout<<"conditionTwoValues1.setDefiningFibElement( &pointDef1 );"<<endl;
	conditionTwoValues1.setDefiningFibElement( &pointDef1 );
	pDefiningFibElement = &pointDef1;
	//check the getDefiningFibElement() methode from tConditionTwoValue
	if ( conditionTwoValues1.getDefiningFibElement() == pDefiningFibElement ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionTwoValues1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionTwoValues1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( conditionTwoValues1, "conditionTwoValues1", conditionTwoValuesCorrect, "correct condition" );
	
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for the defining Fib-element on random conditions"<<endl;
	
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
	cout<<"cConditionGreater conditionGreater( funSubValue1, funSubValue1 );"<<endl;
	cConditionGreater conditionGreater( funSubValue1, funSubValue1 );
	
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
	
	cCondition * pFirstSubCondition = NULL;
	bool bFirstSubConditionValue = false;
	
	cCondition * pSecondSubCondition = NULL;
	bool bSecondSubConditionValue = false;
	
	pDefiningFibElement = &point;
	cout<<"pConditionTwoValue = new tConditionTwoValue( "<<
		pFirstSubCondition<<", "<<pSecondSubCondition<<", NULL, &point="<<
		pDefiningFibElement<<" );"<<endl;
	tConditionTwoValue * pConditionTwoValue = new tConditionTwoValue( NULL, NULL, NULL, pDefiningFibElement );
	bool bIsValid = false;
	
	for ( unsigned int uiIteration = 1; uiIteration <= 256; uiIteration++ ){
		
		cout<<endl;
		if ( (rand() % 16) == 0 ){
			//create new condition
			if ( pConditionTwoValue ){
				delete pConditionTwoValue;
				pConditionTwoValue = NULL;
				pFirstSubCondition = NULL;
				pSecondSubCondition = NULL;
				bFirstSubConditionValue = 0;
				bSecondSubConditionValue = 0;
			}
			if ( rand() % 4 ){
				//set first subcondition
				cFunctionValue funSubValue1( domFunValues.round(
					((double)(rand() % (256 * 256))) / 256.0 ) );
				cFunctionValue funSubValue2( domFunValues.round(
					((double)(rand() % (256 * 256))) / 256.0 ) );
				pFirstSubCondition = new cConditionGreater( funSubValue1, funSubValue2 );
				bFirstSubConditionValue = pFirstSubCondition->getValue();
				cout<<"pFirstSubCondition("<<pFirstSubCondition<<") = new cConditionGreater( cFunctionValue( "<<
					funSubValue1.getValue()<<" ), cFunctionValue( "<<
					funSubValue2.getValue()<<" ) );"<<endl;
			}
			if ( rand() % 4 ){
				//set second subcondition
				cFunctionValue funSubValue1( domFunValues.round(
					((double)(rand() % (256 * 256))) / 256.0 ) );
				cFunctionValue funSubValue2( domFunValues.round(
					((double)(rand() % (256 * 256))) / 256.0 ) );
				pSecondSubCondition = new cConditionGreater( funSubValue1, funSubValue2 );
				bSecondSubConditionValue = pSecondSubCondition->getValue();
				cout<<"pSecondSubCondition("<<pSecondSubCondition<<") = new cConditionGreater( cFunctionValue( "<<
					funSubValue1.getValue()<<" ), cFunctionValue( "<<
					funSubValue2.getValue()<<" ) );"<<endl;
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
			cout<<"pConditionTwoValue = new tConditionTwoValue( "<<
				pFirstSubCondition<<", "<<pSecondSubCondition<<", NULL, "<<
				pDefiningFibElement<<"  );"<<endl;
			pConditionTwoValue = new tConditionTwoValue( pFirstSubCondition, pSecondSubCondition, NULL, pDefiningFibElement );
		}else{
			switch ( rand() % 5 ){
				//create subsubconditions
				case 0:{
					//set first subcondition
					cFunctionValue funSubValue1( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					cFunctionValue funSubValue2( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					pFirstSubCondition = new cConditionGreater ( funSubValue1, funSubValue2 );
					bFirstSubConditionValue = pFirstSubCondition->getValue();
					cout<<"pFirstSubCondition("<<pFirstSubCondition<<") = new cConditionGreater( cFunctionValue( "<<
						funSubValue1.getValue()<<" ), cFunctionValue( "<<
						funSubValue2.getValue()<<" ) );"<<endl;
					cout<<"pConditionTwoValue->setFirstSubCondition( "<<pFirstSubCondition<<" );"<<endl;
					pConditionTwoValue->setFirstSubCondition( pFirstSubCondition );
				}break;
				case 1:{
					//set second subcondition
					cFunctionValue funSubValue1( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					cFunctionValue funSubValue2( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					pSecondSubCondition = new cConditionGreater ( funSubValue1, funSubValue2 );
					bSecondSubConditionValue = pSecondSubCondition->getValue();
					cout<<"pSecondSubCondition("<<pSecondSubCondition<<") = new cConditionGreater( cFunctionValue( "<<
						funSubValue1.getValue()<<" ), cFunctionValue( "<<
						funSubValue2.getValue()<<" ) );"<<endl;
					cout<<"pConditionTwoValue->setSecondSubCondition( "<<pSecondSubCondition<<" );"<<endl;
					pConditionTwoValue->setSecondSubCondition( pSecondSubCondition );
				}break;
				case 2:{
					//set first subcondition
					pFirstSubCondition = &conditionGreater;
					bFirstSubConditionValue = conditionGreater.getValue();
					cout<<"pConditionTwoValue->setFirstSubCondition( conditionGreater );"<<endl;
					pConditionTwoValue->setFirstSubCondition( conditionGreater );
				}break;
				case 3:{
					//set second subcondition
					pSecondSubCondition = &conditionGreater;
					bSecondSubConditionValue = conditionGreater.getValue();
					cout<<"pConditionTwoValue->setSecondSubCondition( conditionGreater );"<<endl;
					pConditionTwoValue->setSecondSubCondition( conditionGreater );
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
					cout<<"pConditionTwoValue->setDefiningFibElement( "<<pDefiningFibElement<<", "<<
						(bCheckValues?"true":"false")<<" );"<<endl;
					pConditionTwoValue->setDefiningFibElement( pDefiningFibElement, bCheckValues );
					if ( bCheckValues ){
						if ( pDefiningFibElement == &point1 ){
							//round to correct values
							bFirstSubConditionValue  = domIntegerBit8.round( bFirstSubConditionValue );
							bSecondSubConditionValue = domIntegerBit8.round( bSecondSubConditionValue );
						}
					}
				}break;
				
			}
		}
		if ( ( pFirstSubCondition != NULL ) && ( pSecondSubCondition != NULL ) ){
			bIsValid = pConditionTwoValue->getFirstSubCondition()->isValid() &&
				pConditionTwoValue->getSecondSubCondition()->isValid();
		}else{
			bIsValid = false;
		}
		
		//check the getValue() methode from tConditionTwoValue
		if ( pConditionTwoValue->getValue() == getCorrectValue<tConditionTwoValue>(
				bFirstSubConditionValue, bSecondSubConditionValue ) ){
	
			cout<<"The condition value is correctly "<<
				(pConditionTwoValue->getValue()?"true":"false") <<" . "<<endl;
		}else{
			cerr<<"Error: The condition value is "<<
				(pConditionTwoValue->getValue()?"true":"false") <<" but should be "<<
				(pConditionTwoValue->getValue()?"false":"true") <<" ( first="<<
				bFirstSubConditionValue<<", second="<<
				bSecondSubConditionValue<<" )."<<endl;
			iReturn++;
		}
		//check the isValid() methode from tConditionTwoValue
		if ( pConditionTwoValue->isValid() == bIsValid ){
		
			cout<<"The condition is correctly "<<(bIsValid?"":"not ")<<"valid . "<<endl;
		}else{
			cerr<<"Error: The condition is "<<(bIsValid?"not ":"")<<"valid ."<<endl;
			iReturn++;
		}
		//check defining Fib-Element of sub and subsubconditions
		if ( pConditionTwoValue->getFirstSubCondition() != NULL ){
			if ( pConditionTwoValue->getFirstSubCondition()->getDefiningFibElement() == pDefiningFibElement ){
			
				cout<<"The definig fib-element of the first subcondition is "<<
					pDefiningFibElement<<"."<<endl;
			}else{
				cerr<<"Error: The definig fib-element of the first subcondition is not "<<
					pDefiningFibElement<<"."<<endl;
				iReturn++;
			}
			if ( pConditionTwoValue->getFirstSubCondition()->getType() == cCondition::CONDITION_GREATER ){
				
				cConditionGreater * pSubCondition = ((cConditionGreater*)(pConditionTwoValue->getFirstSubCondition()));
				
				if ( pSubCondition->getFirstSubFunction()->getDefiningFibElement() == pDefiningFibElement ){
				
					cout<<"The definig fib-element of the first first subsubcondition is "<<
						pDefiningFibElement<<"."<<endl;
				}else{
					cerr<<"Error: The definig fib-element of the first first subsubcondition is not "<<
						pDefiningFibElement<<"."<<endl;
					iReturn++;
				}
				if ( pSubCondition->getSecondSubFunction()->getDefiningFibElement() == pDefiningFibElement ){
				
					cout<<"The definig fib-element of the first second subsubcondition is "<<
						pDefiningFibElement<<"."<<endl;
				}else{
					cerr<<"Error: The definig fib-element of the first second subsubcondition is not "<<
						pDefiningFibElement<<"."<<endl;
					iReturn++;
				}
			}
		}
		if ( pConditionTwoValue->getSecondSubCondition() != NULL ){
			if ( pConditionTwoValue->getSecondSubCondition()->getDefiningFibElement() == pDefiningFibElement ){
			
				cout<<"The definig fib-element of the second subcondition is "<<
					pDefiningFibElement<<"."<<endl;
			}else{
				cerr<<"Error: The definig fib-element of the second subcondition is not "<<
					pDefiningFibElement<<"."<<endl;
				iReturn++;
			}
			if ( pConditionTwoValue->getSecondSubCondition()->getType() == cCondition::CONDITION_GREATER ){
				
				cConditionGreater * pSubCondition = ((cConditionGreater*)(pConditionTwoValue->getSecondSubCondition()));
				
				if ( pSubCondition->getFirstSubFunction()->getDefiningFibElement() == pDefiningFibElement ){
				
					cout<<"The definig fib-element of the second first subsubcondition is "<<
						pDefiningFibElement<<"."<<endl;
				}else{
					cerr<<"Error: The definig fib-element of the second first subsubcondition is not "<<
						pDefiningFibElement<<"."<<endl;
					iReturn++;
				}
				if ( pSubCondition->getSecondSubFunction()->getDefiningFibElement() == pDefiningFibElement ){
				
					cout<<"The definig fib-element of the second second subsubcondition is "<<
						pDefiningFibElement<<"."<<endl;
				}else{
					cerr<<"Error: The definig fib-element of the second second subsubcondition is not "<<
						pDefiningFibElement<<"."<<endl;
					iReturn++;
				}
			}
		}
	}
	if ( pConditionTwoValue ){
		delete pConditionTwoValue;
		pConditionTwoValue = NULL;
		pFirstSubCondition = NULL;
		pSecondSubCondition = NULL;
	}
	

	return iReturn;
}












