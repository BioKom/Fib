/**
 * @file cConditionNot
 * file name: cConditionNot.cpp
 * @author Betti Oesterholz
 * @date 02.05.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cConditionNot.
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
 * This file contains the test for the class cConditionNot, which
 * represents a true condition.
 *
 *
 * What's tested of class cConditionNot:
 * 	- cConditionNot( cCondition * pInSubCondition, cCondition * pInSuperiorCondition = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cConditionNot( const cCondition & pInSubCondition, cCondition * pInSuperiorCondition = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cConditionNot( const cConditionNot & condition, cCondition * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- ~cConditionNot();
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
 * 	- cCondition * getSubCondition();
 * 	- bool setSubCondition( cCondition * pInSubCondition, bool bDeleteOld=true );
 * 	- bool setSubCondition( const cCondition & pInSubCondition, bool bDeleteOld=true );
 *
 */
/*
History:
02.05.2011  Oesterholz  created
09.10.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/

#include "version.h"

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
#include "cTypeUnderFunction.h"
#include "cTypeInVar.h"
#include "cVectorProperty.h"
#include "cEvaluePositionList.h"
#include "cEvalueFibElementList.h"
#include "cReadBits.h"

#include "cConditionTrue.h"
#include "cConditionFalse.h"

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
int testSubCondition( unsigned long &ulTestphase );
int testVariable( unsigned long &ulTestphase );
int testDefiningFibElement( unsigned long &ulTestphase );



int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	cout<<endl<<"Running Test for cConditionNot methods"<<endl;
	cout<<      "========================================"<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testCopy( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );
	iReturn += testSubCondition( ulTestphase );
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
 * This method tests the constructor of the cConditionNot class.
 *
 * methods tested:
 * 	- cConditionNot( cCondition * pInSubCondition, cCondition * pInSuperiorCondition = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cConditionNot( const cCondition & pInSubCondition, cCondition * pInSuperiorCondition = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- ~cConditionNot();
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
int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<"cRoot rootEmpty;"<<endl;
	cRoot rootEmpty;
	cout<<"rootEmpty.setNumberOfInputVariables( 10 );"<<endl;
	rootEmpty.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 =  rootEmpty.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 =  rootEmpty.getInputVariable( 1 );
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cConditionNot condition"<<endl;

	cout<<"cConditionNot conditionNot1( NULL );"<<endl;
	cConditionNot conditionNot1( NULL );
	cFibElement * pDefiningFibElement = NULL;
	cCondition * pSuperiorCondition = NULL;
	cCondition * pSubCondition = NULL;
	unsigned long ulTimeNeed = 1;
	unsigned long ulCompressedSize = 4;
 
	//check the getValue() methode from cConditionNot
	if ( conditionNot1.getValue() == false  ){
	
		cout<<"The condition value is correctly "<<
			(conditionNot1.getValue()?"true":"false") <<" . "<<endl;
	}else{
		cerr<<"Error: The condition value is "<<
			(conditionNot1.getValue()?"true":"false") <<" but should be false ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cConditionNot
	if ( conditionNot1.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionNot1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionNot1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionNot1.getSuperiorCondition() == pSuperiorCondition  ){
	
		cout<<"The superior condition of the condition correctly "<<
			conditionNot1.getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			conditionNot1.getSuperiorCondition() <<
			" but should be "<< pSuperiorCondition <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionNot1.getSubCondition() == pSubCondition  ){
	
		cout<<"The subcondition of the condition correctly "<<
			conditionNot1.getSubCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The subcondition of the condition is "<<
			conditionNot1.getSubCondition() <<
			" but should be "<< pSubCondition <<" ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from cConditionNot
	if ( ! conditionNot1.isValid() ){
	
		cout<<"The condition is correctly not valid . "<<endl;
	}else{
		cerr<<"Error: The condition is valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cConditionNot
	if ( conditionNot1.getType() == 10 ){
	
		cout<<"The condition type is correctly CONDITION_NOT. "<<endl;
	}else{
		cerr<<"Error: The type of the condition is not CONDITION_NOT ( 10 ), but "<<
			conditionNot1.getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getConditionName() methode from cConditionNot
	if ( conditionNot1.getConditionName() == "not" ){
	
		cout<<"The condition name is correctly "<<
			conditionNot1.getConditionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the condition is not \"not\", but "<<
			conditionNot1.getConditionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfConditions() methode from cConditionNot
	if ( conditionNot1.getNumberOfConditions() == 1 ){
	
		cout<<"The condition number of subconditions is correctly "<<
			conditionNot1.getNumberOfConditions() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition number of subconditions is "<<
			conditionNot1.getNumberOfConditions() <<" , but should be 1 ."<<endl;
		iReturn++;
	}
	//check the getNumberOfConditions() methode from cConditionNot
	if ( conditionNot1.getNumberOfUnderFunctions() == 0 ){
	
		cout<<"The condition number of subconditions is correctly "<<
			conditionNot1.getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition number of subconditions is "<<
			conditionNot1.getNumberOfUnderFunctions() <<" , but should be 0 ."<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cConditionNot
	if ( conditionNot1.getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the condition is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the condition is "<<
			conditionNot1.getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cConditionNot
	if ( conditionNot1.getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the condition is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The tcompressed size of the condition is "<<
			conditionNot1.getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cConditionNot
	if ( ! conditionNot1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 isn't used in the condition. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the condition. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cConditionNot
	set<cFibVariable*> setUsedVariables = conditionNot1.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"No used variables are given back from the condition. "<<endl;
	}else{
		cerr<<"Error: Used variables are given back from the condition. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an cConditionNot condition with a false subcondition"<<endl;

	cout<<"cConditionFalse conditionNotFalse;"<<endl;
	cConditionFalse conditionNotFalse;
	
	cout<<"cConditionNot conditionNot2( conditionNotFalse ,&conditionNot1, &rootEmpty  );"<<endl;
	cConditionNot conditionNot2( conditionNotFalse ,&conditionNot1, &rootEmpty );
	
	pDefiningFibElement = &rootEmpty;
	pSuperiorCondition = &conditionNot1;
	pSubCondition = &conditionNotFalse;
	ulTimeNeed = 2;
	ulCompressedSize = 8;

	//check the getValue() methode from cConditionNot
	if ( conditionNot2.getValue() == true  ){
	
		cout<<"The condition value is correctly "<<
			(conditionNot2.getValue()?"true":"false") <<" . "<<endl;
	}else{
		cerr<<"Error: The condition value is "<<
			(conditionNot2.getValue()?"true":"false") <<" but should be true ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cConditionNot
	if ( conditionNot2.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionNot2.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionNot2.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionNot2.getSuperiorCondition() == pSuperiorCondition  ){
	
		cout<<"The superior condition of the condition correctly "<<
			conditionNot2.getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			conditionNot2.getSuperiorCondition() <<
			" but should be "<< pSuperiorCondition <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionNotFalse == *(conditionNot2.getSubCondition()) ){
	
		cout<<"The subcondition of the condition correctly equal to conditionNotFalse . "<<endl;
	}else{
		cerr<<"Error: The subcondition of the condition is not equal to conditionNotFalse ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from cConditionNot
	if ( conditionNot2.isValid() ){
	
		cout<<"The condition is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The condition is not valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cConditionNot
	if ( conditionNot2.getType() == cCondition::CONDITION_NOT ){
	
		cout<<"The condition type is correctly CONDITION_NOT. "<<endl;
	}else{
		cerr<<"Error: The type of the condition is not CONDITION_NOT ( 10 ), but "<<
			conditionNot2.getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getConditionName() methode from cConditionNot
	if ( conditionNot2.getConditionName() == "not" ){
	
		cout<<"The condition name is correctly "<<
			conditionNot2.getConditionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the condition is not \"not\", but "<<
			conditionNot2.getConditionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfConditions() methode from cConditionNot
	if ( conditionNot2.getNumberOfConditions() == 1 ){
	
		cout<<"The condition number of subconditions is correctly "<<
			conditionNot2.getNumberOfConditions() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition number of subconditions is "<<
			conditionNot2.getNumberOfConditions() <<" , but should be 1 ."<<endl;
		iReturn++;
	}
	//check the getNumberOfConditions() methode from cConditionNot
	if ( conditionNot2.getNumberOfUnderFunctions() == 0 ){
	
		cout<<"The condition number of subconditions is correctly "<<
			conditionNot2.getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition number of subconditions is "<<
			conditionNot2.getNumberOfUnderFunctions() <<" , but should be 0 ."<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cConditionNot
	if ( conditionNot2.getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the condition is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the condition is "<<
			conditionNot2.getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cConditionNot
	if ( conditionNot2.getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the condition is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The tcompressed size of the condition is "<<
			conditionNot2.getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cConditionNot
	if ( ! conditionNot2.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 isn't used in the condition. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the condition. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cConditionNot
	setUsedVariables = conditionNot2.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"No used variables are given back from the condition. "<<endl;
	}else{
		cerr<<"Error: Used variables are given back from the condition. "<<endl;
		iReturn++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an cConditionNot condition with a true subcondition"<<endl;

	cout<<"cConditionTrue * pSubConditionTrue = new cConditionTrue();"<<endl;
	cConditionTrue * pSubConditionTrue = new cConditionTrue();
	
	cout<<"cConditionNot conditionNot3( pSubConditionTrue ,&conditionNot1, &rootEmpty  );"<<endl;
	cConditionNot conditionNot3( pSubConditionTrue ,&conditionNot1, &rootEmpty );
	
	pDefiningFibElement = &rootEmpty;
	pSuperiorCondition = &conditionNot1;
	pSubCondition = pSubConditionTrue;
	ulTimeNeed = 2;
	ulCompressedSize = 8;

	//check the getValue() methode from cConditionNot
	if ( conditionNot3.getValue() == false  ){
	
		cout<<"The condition value is correctly "<<
			(conditionNot3.getValue()?"true":"false") <<" . "<<endl;
	}else{
		cerr<<"Error: The condition value is "<<
			(conditionNot3.getValue()?"true":"false") <<" but should be true ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cConditionNot
	if ( conditionNot3.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionNot3.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionNot3.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionNot3.getSuperiorCondition() == pSuperiorCondition  ){
	
		cout<<"The superior condition of the condition correctly "<<
			conditionNot3.getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			conditionNot3.getSuperiorCondition() <<
			" but should be "<< pSuperiorCondition <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionNot3.getSubCondition() == pSubCondition  ){
	
		cout<<"The subcondition of the condition correctly "<<
			conditionNot3.getSubCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The subcondition of the condition is "<<
			conditionNot3.getSubCondition() <<
			" but should be "<< pSubCondition <<" ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from cConditionNot
	if ( conditionNot3.isValid() ){
	
		cout<<"The condition is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The condition is not valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cConditionNot
	if ( conditionNot3.getType() == cCondition::CONDITION_NOT ){
	
		cout<<"The condition type is correctly CONDITION_NOT. "<<endl;
	}else{
		cerr<<"Error: The type of the condition is not CONDITION_NOT ( 10 ), but "<<
			conditionNot3.getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getConditionName() methode from cConditionNot
	if ( conditionNot3.getConditionName() == "not" ){
	
		cout<<"The condition name is correctly "<<
			conditionNot3.getConditionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the condition is not \"not\", but "<<
			conditionNot3.getConditionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfConditions() methode from cConditionNot
	if ( conditionNot3.getNumberOfConditions() == 1 ){
	
		cout<<"The condition number of subconditions is correctly "<<
			conditionNot3.getNumberOfConditions() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition number of subconditions is "<<
			conditionNot3.getNumberOfConditions() <<" , but should be 1 ."<<endl;
		iReturn++;
	}
	//check the getNumberOfConditions() methode from cConditionNot
	if ( conditionNot3.getNumberOfUnderFunctions() == 0 ){
	
		cout<<"The condition number of subconditions is correctly "<<
			conditionNot3.getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition number of subconditions is "<<
			conditionNot3.getNumberOfUnderFunctions() <<" , but should be 0 ."<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cConditionNot
	if ( conditionNot3.getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the condition is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the condition is "<<
			conditionNot3.getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cConditionNot
	if ( conditionNot3.getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the condition is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The tcompressed size of the condition is "<<
			conditionNot3.getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cConditionNot
	if ( ! conditionNot3.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 isn't used in the condition. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the condition. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cConditionNot
	setUsedVariables = conditionNot3.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"No used variables are given back from the condition. "<<endl;
	}else{
		cerr<<"Error: Used variables are given back from the condition. "<<endl;
		iReturn++;
	}

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
 * This method tests equal method of the cConditionNot class.
 *
 * methods tested:
 * 	- bool equal( const cFibElement & fibObject ) const
 * 	- bool operator==( const cCondition &condition ) const;
 * 	- bool operator!=( const cCondition &condition ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testEqual( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing comparison methods for condition"<<endl;

	cout<<endl<<"Creating conditions objects to compare: "<<endl<<endl;

	//simple condition
	cout<<"cConditionNot conditionNot1( NULL );"<<endl;
	cConditionNot conditionNot1( NULL );

	cout<<"cConditionNot conditionNot2( NULL );"<<endl;
	cConditionNot conditionNot2( NULL );

	//with subcondition
	cout<<"cConditionTrue subConditionTrue;"<<endl;
	cConditionTrue subConditionTrue;
	cout<<"cConditionNot conditionNotTrue( subConditionTrue );"<<endl;
	cConditionNot conditionNotTrue( subConditionTrue );

	cout<<"cConditionFalse subConditionFalse;"<<endl;
	cConditionFalse subConditionFalse;
	cout<<"cConditionNot conditionNotFalse( subConditionFalse );"<<endl;
	cConditionNot conditionNotFalse( subConditionFalse );

	
	//condition with defining Fib-element
	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	cout<<"cConditionNot conditionDefFE( NULL, NULL, &rootSimple1 );"<<endl;
	cConditionNot conditionDefFE( NULL, NULL, &rootSimple1 );

	//condition with superior condition
	cout<<"cConditionNot conditionConSup( NULL );"<<endl;
	cConditionNot conditionConSup( NULL );
	cout<<"cConditionNot conditionSup( NULL, & conditionConSup );"<<endl;
	cConditionNot conditionSup( NULL, & conditionConSup );

	//condition with domains set
	cout<<"root1 rootSimple1;"<<endl;
	cRoot root1;
	
	cout<<"cTypeVariable testTypeVariable;"<<endl;
	cTypeVariable testTypeVariable;
	cout<<"cDomainNaturalNumberBit domainNat8( 8 );"<<endl;
	cDomainNaturalNumberBit domainNat8( 8 );

	cout<<"root1.getDomains()->addDomain( testTypeVariable, &domainNat8 );"<<endl;
	root1.getDomains()->addDomain( testTypeVariable, &domainNat8 );

	cout<<"cConditionNot conditionDom( NULL, NULL, &root1 );"<<endl;
	cConditionNot conditionDom( NULL, NULL, &root1 );

	//condition with defining Fib-element and superior condition
	cout<<"cRoot rootSimple2;"<<endl;
	cRoot rootSimple2;
	cout<<"cConditionNot conditionSup2( NULL );"<<endl;
	cConditionNot conditionSup2( NULL );
	cout<<"cConditionNot conditionDefFeSc( NULL, & conditionSup2, &rootSimple2 );"<<endl;
	cConditionNot conditionDefFeSc( NULL, & conditionSup2, &rootSimple2 );

	//conditions of other typs
	cout<<"cConditionFalse conditionFalse;"<<endl;
	cConditionFalse conditionFalse;
	

	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with conditionNot1
	cCondition * actualObject = &conditionNot1;
	string szActualObjectName = "conditionNot1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionNot1, "conditionNot1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionNot2, "conditionNot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNotTrue, "conditionNotTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNotFalse, "conditionNotFalse" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );

	//compare with conditionNot2
	actualObject = &conditionNot2;
	szActualObjectName = "conditionNot2";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionNot1, "conditionNot1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionNot2, "conditionNot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNotTrue, "conditionNotTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNotFalse, "conditionNotFalse" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );

	//compare with conditionNotTrue
	actualObject = &conditionNotTrue;
	szActualObjectName = "conditionNotTrue";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot1, "conditionNot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot2, "conditionNot2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionNotTrue, "conditionNotTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNotFalse, "conditionNotFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );

	//compare with conditionNotFalse
	actualObject = &conditionNotFalse;
	szActualObjectName = "conditionNotFalse";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot1, "conditionNot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot2, "conditionNot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNotTrue, "conditionNotTrue" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionNotFalse, "conditionNotFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );

	//compare with conditionDefFE
	actualObject = &conditionDefFE;
	szActualObjectName = "conditionDefFE";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionNot1, "conditionNot1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionNot2, "conditionNot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNotTrue, "conditionNotTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNotFalse, "conditionNotFalse" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );

	//compare with conditionSup
	actualObject = &conditionSup;
	szActualObjectName = "conditionSup";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionNot1, "conditionNot1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionNot2, "conditionNot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNotTrue, "conditionNotTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNotFalse, "conditionNotFalse" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );

	//compare with conditionDom
	actualObject = &conditionDom;
	szActualObjectName = "conditionDom";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionNot1, "conditionNot1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionNot2, "conditionNot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNotTrue, "conditionNotTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNotFalse, "conditionNotFalse" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );

	//compare with conditionDefFeSc
	actualObject = &conditionDefFeSc;
	szActualObjectName = "conditionDefFeSc";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionNot1, "conditionNot1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionNot2, "conditionNot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNotTrue, "conditionNotTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNotFalse, "conditionNotFalse" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );

	//compare with conditionFalse
	actualObject = &conditionFalse;
	szActualObjectName = "conditionFalse";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot1, "conditionNot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNot2, "conditionNot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNotTrue, "conditionNotTrue" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionNotFalse, "conditionNotFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeSc, "conditionDefFeSc" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionFalse, "conditionFalse" );


	return iReturn;
}


/**
 * This method tests if the given condition is not conected to other
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
 * This method tests the copy methods and copyconstructor of the cConditionNot class.
 *
 * methods tested:
 * 	- cConditionNot( const cConditionNot & condition, cCondition * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- cCondition * clone( cCondition * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCopy( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a simple cConditionNot"<<endl;

	cout<<"cConditionNot conditionNot1( NULL );"<<endl;
	cConditionNot conditionNot1( NULL );

	cout<<"cConditionNot conditionNot1CopyConstruct( conditionNot1 );"<<endl;
	cConditionNot conditionNot1CopyConstruct( conditionNot1 );

	iReturn += testCompareTwoEqualObjects( conditionNot1CopyConstruct, "conditionNot1CopyConstruct", conditionNot1, "conditionNot1" );
	iReturn += testNotConnectedCondition( conditionNot1CopyConstruct );

	cout<<"cCondition * pUnderConditionNot1Clone = conditionNot1CopyConstruct.clone();"<<endl;
	cCondition * pUnderConditionNot1Clone = conditionNot1CopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pUnderConditionNot1Clone, "pUnderConditionNot1Clone", conditionNot1, "conditionNot1" );
	iReturn += testNotConnectedCondition( *pUnderConditionNot1Clone );
	delete pUnderConditionNot1Clone;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cConditionNot with a subcondition, superior condition and defining Fib-element"<<endl;

	//condition with defining Fib-element and superior condition
	cout<<"cRoot rootSimple;"<<endl;
	cRoot rootSimple;
	cout<<"cConditionNot conditionSup( NULL );"<<endl;
	cConditionNot conditionSup( NULL );
	cout<<"cConditionFalse subConditionFalse;"<<endl;
	cConditionFalse subConditionFalse;
	cout<<"cConditionNot conditionDefFeSc( subConditionFalse, & conditionSup, &rootSimple );"<<endl;
	cConditionNot conditionDefFeSc( subConditionFalse,& conditionSup, &rootSimple );

	cout<<"cConditionNot conditionDefFeScCopyConstruct( conditionDefFeSc );"<<endl;
	cConditionNot conditionDefFeScCopyConstruct( conditionDefFeSc );

	iReturn += testCompareTwoEqualObjects( conditionDefFeScCopyConstruct, "conditionDefFeScCopyConstruct", conditionDefFeSc, "conditionDefFeSc" );
	//check the getDefiningFibElement() methode from cConditionNot
	if ( conditionDefFeScCopyConstruct.getDefiningFibElement() == &rootSimple  ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionDefFeScCopyConstruct.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionDefFeScCopyConstruct.getDefiningFibElement() <<" but should be rootSimple ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionDefFeScCopyConstruct.getSuperiorCondition() == NULL  ){
	
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
	//check the getDefiningFibElement() methode from cConditionNot
	if ( pConditionDefFeUfClone->getDefiningFibElement() == &rootSimple  ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			pConditionDefFeUfClone->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			pConditionDefFeUfClone->getDefiningFibElement() <<" but should be rootSimple ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( pConditionDefFeUfClone->getSuperiorCondition() == NULL  ){
	
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cConditionNot with a superior condition and defining Fib-element which will be changed"<<endl;

	//condition with defining Fib-element and superior condition
	cout<<"cRoot rootSimple2;"<<endl;
	cRoot rootSimple2;
	cout<<"cConditionNot conditionSup2( NULL );"<<endl;
	cConditionNot conditionSup2( NULL );

	cout<<"cConditionNot conditionDefFeScCopy2Construct( conditionDefFeSc, &conditionSup2, &rootSimple2 );"<<endl;
	cConditionNot conditionDefFeScCopy2Construct( conditionDefFeSc, &conditionSup2, &rootSimple2 );

	iReturn += testCompareTwoEqualObjects( conditionDefFeScCopy2Construct, "conditionDefFeScCopy2Construct", conditionDefFeSc, "conditionDefFeSc" );
	//check the getDefiningFibElement() methode from cConditionNot
	if ( conditionDefFeScCopy2Construct.getDefiningFibElement() == &rootSimple2  ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionDefFeScCopy2Construct.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionDefFeScCopy2Construct.getDefiningFibElement() <<" but should be rootSimple2 ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionDefFeScCopy2Construct.getSuperiorCondition() == &conditionSup2  ){
	
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
	//check the getDefiningFibElement() methode from cConditionNot
	if ( pConditionDefFeUfClone->getDefiningFibElement() == &rootSimple2  ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			pConditionDefFeUfClone->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			pConditionDefFeUfClone->getDefiningFibElement() <<" but should be rootSimple2 ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( pConditionDefFeUfClone->getSuperiorCondition() == &conditionSup2  ){
	
		cout<<"The superior condition of the condition correctly "<<
			pConditionDefFeUfClone->getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			pConditionDefFeUfClone->getSuperiorCondition() <<
			" but should be conditionSup2 ."<<endl;
		iReturn++;
	}
	delete pConditionDefFeUfClone;


	return iReturn;
}



/**
 * This method tests a in the xml -format stored cConditionNot.
 * The condition of the cConditionNot should be a value condition
 * ( cConditionNot ).
 *
 * @param szFilename the name of the file wher the cConditionNot is stored
 * @param ucSubCondition if the subcondition is a NULL pointer (=0), a
 * 	cConditionTrue (=1) or cConditionFalse (=2)
 * @return the number of errors occured in the test
 */
int testXmlConditionNot( const string szFilename, unsigned char ucSubCondition=0 ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored cConditionNot:"<<endl;
	
	TiXmlDocument xmlDocConditionNot( szFilename );
	bool loadOkay = xmlDocConditionNot.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocConditionNot );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlHandleRoot(0);

	pXmlElement = xmlHandle.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();
		
		const string szConditionNotElementName = "not";
		if ( szElementName == szConditionNotElementName ){
			cout<<"The root element is correctly named \""<< szConditionNotElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \""<< szConditionNotElementName <<"\"."<<endl;
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
	if ( pXmlElement ) {
		
		string szElementName = pXmlElement->Value();
		const string szSubconditionElementName = ((ucSubCondition==1)?"true":"false");
		if ( szElementName == szSubconditionElementName ){
			cout<<"The subcondition is correctly named \""<< szSubconditionElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the subcondition is "<< szElementName <<" and not \""<< szSubconditionElementName <<"\"."<<endl;
			iReturn++;
		}
		
	}else{// pXmlElement == NULL ->no root handle
		if ( ucSubCondition == 0 ){
			cout<<"Ther is correctly no subcondition. "<<endl;
		}else{
			cerr<<"Error: No subcondition handle in \""<< szFilename <<"\"."<<endl;
			iReturn++;
		}
	}

	return iReturn;
}



/**
 * This method tests the storeXml() method of the cConditionNot class.
 * Just storing properties with no underobjects is tested.
 *
 * methods tested:
 * 	- bool storeXml( ostream &stream ) const;
 * 	- cCondition * restoreXml( const TiXmlElement * pXmlElement, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, cCondition * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStoreXml( unsigned long &ulTestphase ){

	unsigned int iReturn = 0;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an not condition"<<endl;

	cout<<"cConditionNot conditionNot1( NULL );"<<endl;
	cConditionNot conditionNot1( NULL );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * szXmlConditionNotFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "conditionNotNull.xml" );
	ofstream * pFileCondition = new ofstream( szXmlConditionNotFileName );
	
	bool bStoreSuccesfull = conditionNot1.storeXml( *pFileCondition );
	delete pFileCondition;
	
	if ( ! bStoreSuccesfull ){
	
		cout<<"The data of the cConditionNot was correctly stored not successfull to the file \""<< szXmlConditionNotFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cConditionNot to the file \""<< szXmlConditionNotFileName <<"\" was successfull."<<endl;
		iReturn++;
	}
	iReturn += testXmlConditionNot( szXmlConditionNotFileName );
	
	TiXmlDocument xmlDocConditionNot( szFileNameBuffer );
	bool loadOkay = xmlDocConditionNot.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"TiXmlHandle xmlHandle2( &xmlDocConditionNot ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDocConditionNot );
		cout<<"cConditionNot * pUnderConditionNot1Loaded = cCondition::restoreXml("<<
			"xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cCondition * pUnderConditionNot1Loaded = cCondition::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus != 0 ){
		
			cout<<"The data was loaded not successfull (outStatus="<< outStatus <<"). "<<endl;
		}else{
			cerr<<"Error: Data was loaded not successfull."<<endl;
			iReturn++;
		}
		if ( pUnderConditionNot1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionNot1Loaded, "pUnderConditionNot1Loaded", conditionNot1, "conditionNot1" );
			iReturn += testNotConnectedCondition( * pUnderConditionNot1Loaded );
			delete pUnderConditionNot1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cConditionNot conditionSup( NULL );"<<endl;
		cConditionNot conditionSup( NULL );

		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"TiXmlHandle xmlHandle4( &xmlDocConditionNot ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDocConditionNot );
		cout<<"cConditionNot pUnderConditionNot1LoadedFull = cCondition::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionNot1LoadedFull = cCondition::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &conditionSup, &rootSimple );
		
		if ( outStatus != 0 ){
		
			cout<<"The data was loaded not successfull (outStatus="<< outStatus <<"). "<<endl;
		}else{
			cerr<<"Error: Data was loaded not successfull."<<endl;
			iReturn++;
		}
		if ( pUnderConditionNot1LoadedFull ){
			if ( pUnderConditionNot1LoadedFull->getType() == cCondition::CONDITION_NOT ){
				cout<<"Correctly an not condition restored."<<endl;
				//check the getSuperiorCondition() methode from cConditionNot
				if ( ((cConditionNot*)pUnderConditionNot1LoadedFull)->getSubCondition() == NULL  ){
				
					cout<<"The subcondition of the condition correctly NULL . "<<endl;
				}else{
					cerr<<"Error: The subcondition of the condition is NULL "<<
						" but should be NULL ."<<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: Not an not condition restored."<<endl;
				iReturn++;
			}
			//check the getDefiningFibElement() methode from cConditionNot
			if ( pUnderConditionNot1LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionNot1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionNot1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from cConditionNot
			if ( pUnderConditionNot1LoadedFull->getSuperiorCondition() == &conditionSup  ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionNot1LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionNot1LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionNot1LoadedFull;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an not condition with an true subcondition"<<endl;
	
	cout<<"cConditionTrue subConditionTrue;"<<endl;
	cConditionTrue subConditionTrue;
	cout<<"cConditionNot conditionNotTrue( subConditionTrue );"<<endl;
	cConditionNot conditionNotTrue( subConditionTrue );
	
	szFileNameBuffer[0] = 0;
	szXmlConditionNotFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "conditionNotTrue.xml" );
	pFileCondition = new ofstream( szXmlConditionNotFileName );
	
	bStoreSuccesfull = conditionNotTrue.storeXml( *pFileCondition );
	delete pFileCondition;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cConditionNot was stored successfull to the file \""<< szXmlConditionNotFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cConditionNot to the file \""<< szXmlConditionNotFileName <<"\" failed."<<endl;
		iReturn++;
	}
	iReturn += testXmlConditionNot( szXmlConditionNotFileName, 1 );
	
	TiXmlDocument xmlDocConditionNotTrue( szFileNameBuffer );
	loadOkay = xmlDocConditionNotTrue.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"TiXmlHandle xmlHandle2( &xmlDocConditionNotTrue ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDocConditionNotTrue );
		cout<<"cConditionNot * pUnderConditionNot1Loaded = cCondition::restoreXml("<<
			"xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cCondition * pUnderConditionNot1Loaded = cCondition::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionNot1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionNot1Loaded, "pUnderConditionNot1Loaded", conditionNotTrue, "conditionNotTrue" );
			iReturn += testNotConnectedCondition( * pUnderConditionNot1Loaded );
			delete pUnderConditionNot1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cConditionNot conditionSup( NULL );"<<endl;
		cConditionNot conditionSup( NULL );

		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"TiXmlHandle xmlHandle4( &xmlDocConditionNotTrue ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDocConditionNotTrue );
		cout<<"cConditionNot pUnderConditionNot1LoadedFull = cCondition::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionNot1LoadedFull = cCondition::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &conditionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionNot1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionNot1LoadedFull, "pUnderConditionNot1LoadedFull", conditionNotTrue, "conditionNotTrue" );
			//check the getDefiningFibElement() methode from cConditionNot
			if ( pUnderConditionNot1LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionNot1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionNot1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from cConditionNot
			if ( pUnderConditionNot1LoadedFull->getSuperiorCondition() == &conditionSup  ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionNot1LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionNot1LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionNot1LoadedFull;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an not condition with an true subcondition"<<endl;
	
	cout<<"cConditionFalse subConditionFalse;"<<endl;
	cConditionFalse subConditionFalse;
	cout<<"cConditionNot conditionNotFalse( subConditionFalse );"<<endl;
	cConditionNot conditionNotFalse( subConditionFalse );
	
	szFileNameBuffer[0] = 0;
	szXmlConditionNotFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "conditionNotFalse.xml" );
	pFileCondition = new ofstream( szXmlConditionNotFileName );
	
	bStoreSuccesfull = conditionNotFalse.storeXml( *pFileCondition );
	delete pFileCondition;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cConditionNot was stored successfull to the file \""<< szXmlConditionNotFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cConditionNot to the file \""<< szXmlConditionNotFileName <<"\" failed."<<endl;
		iReturn++;
	}
	iReturn += testXmlConditionNot( szXmlConditionNotFileName, 2 );
	
	TiXmlDocument xmlDocConditionNotFalse( szFileNameBuffer );
	loadOkay = xmlDocConditionNotFalse.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"TiXmlHandle xmlHandle2( &xmlDocConditionNotFalse ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDocConditionNotFalse );
		cout<<"cConditionNot * pUnderConditionNot1Loaded = cCondition::restoreXml("<<
			"xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cCondition * pUnderConditionNot1Loaded = cCondition::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionNot1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionNot1Loaded, "pUnderConditionNot1Loaded", conditionNotFalse, "conditionNotFalse" );
			iReturn += testNotConnectedCondition( * pUnderConditionNot1Loaded );
			delete pUnderConditionNot1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cConditionNot conditionSup( NULL );"<<endl;
		cConditionNot conditionSup( NULL );

		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"TiXmlHandle xmlHandle4( &xmlDocConditionNotFalse ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDocConditionNotFalse );
		cout<<"cConditionNot pUnderConditionNot1LoadedFull = cCondition::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionNot1LoadedFull = cCondition::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &conditionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionNot1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionNot1LoadedFull, "pUnderConditionNot1LoadedFull", conditionNotFalse, "conditionNotFalse" );
			//check the getDefiningFibElement() methode from cConditionNot
			if ( pUnderConditionNot1LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionNot1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionNot1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from cConditionNot
			if ( pUnderConditionNot1LoadedFull->getSuperiorCondition() == &conditionSup  ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionNot1LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionNot1LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionNot1LoadedFull;
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
int testStore( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an true condition"<<endl;

	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;
	
	cout<<"cConditionTrue subConditionTrue;"<<endl;
	cConditionTrue subConditionTrue;
	
	cout<<"cConditionNot conditionNot1( subConditionTrue, NULL, &root );"<<endl;
	cConditionNot conditionNot1( subConditionTrue, NULL, &root );

	//test get compressed size
	unsigned int uiCompressedSize = 8;
	if ( (unsigned int)(conditionNot1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			conditionNot1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "conditionNotTrue.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = (char)0x00;
	unsigned char cRestBitPosition = 0;
	cout<<"conditionNot1.store( *pFile, cRestBits, cRestBitPosition );"<<endl;
	bool bStoreSuccesfull = conditionNot1.store( *pFile, cRestBit, cRestBitPosition );
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
	const char cConditionNot1[] = { (char)0xF1, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cConditionNot1, 2 );


	cDomainSingle * pValueDomain = new cDomainNaturalNumberBit( 16 );
	cDomainSingle * pVariableDomain = new cDomainNaturalNumberBit( 3 );
	
	ifstream * pFileIn = new ifstream( szFileNameBuffer );
	if ( (pFileIn != NULL) && ( pFileIn->good() ) ){
		
		cReadBits iBitStream2( * pFileIn );
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"cConditionNot pUnderConditionNot1Loaded = cCondition::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cCondition * pUnderConditionNot1Loaded = cCondition::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pValueDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionNot1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionNot1Loaded, "pUnderConditionNot1Loaded", conditionNot1, "conditionNot1" );
			iReturn += testNotConnectedCondition( * pUnderConditionNot1Loaded );
			delete pUnderConditionNot1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cConditionNot conditionSup( NULL );"<<endl;
		cConditionNot conditionSup( NULL );
		
		delete pFileIn;

		pFileIn = new ifstream( szFileNameBuffer );
		cReadBits iBitStream4( * pFileIn );
		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"cConditionNot pUnderConditionNot1LoadedFull = cCondition::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionNot1LoadedFull = cCondition::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&conditionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionNot1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionNot1LoadedFull, "pUnderConditionNot1LoadedFull", conditionNot1, "conditionNot1" );
			//check the getDefiningFibElement() methode from cConditionNot
			if ( pUnderConditionNot1LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionNot1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionNot1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from cConditionNot
			if ( pUnderConditionNot1LoadedFull->getSuperiorCondition() == &conditionSup  ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionNot1LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionNot1LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionNot1LoadedFull;
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

	cout<<"cConditionFalse subConditionFalse;"<<endl;
	cConditionFalse subConditionFalse;
	
	cout<<"cConditionNot conditionNot2( subConditionFalse, NULL, &root );"<<endl;
	cConditionNot conditionNot2( subConditionFalse, NULL, &root );
	
	//test get compressed size
	uiCompressedSize = 8;
	if ( (unsigned int)(conditionNot2.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			conditionNot2.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "conditionNot2.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x01;
	cRestBitPosition = 2;
	cout<<"conditionNot2.store( *pFile, cRestBit, cRestBitPosition ); "<<endl;
	bStoreSuccesfull = conditionNot2.store( *pFile, cRestBit, cRestBitPosition );
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
	const char szUnderConditionNot2[] = { (char)0x05, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, szUnderConditionNot2, 2 );


	pFileIn = new ifstream( szFileNameBuffer );
	if ( (pFileIn != NULL) && ( pFileIn->good() ) ){
		
		char cBuffer;
		cReadBits iBitStream2( * pFileIn );
		iBitStream2.readBits( &cBuffer, 2 );
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"cConditionNot pUnderConditionNot3Loaded = cCondition::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cCondition * pUnderConditionNot3Loaded = cCondition::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pValueDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionNot3Loaded ){
			const int iErrorsEqual = testCompareTwoEqualObjects( 
				* pUnderConditionNot3Loaded, "pUnderConditionNot3Loaded", conditionNot2, "conditionNot2" );
			iReturn += testNotConnectedCondition( * pUnderConditionNot3Loaded );
			if ( iErrorsEqual != 0 ){
				cerr<<"Error: Loaded condition not equal."<<endl;
			}
			iReturn += iErrorsEqual;
			delete pUnderConditionNot3Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cConditionNot conditionSup( NULL );"<<endl;
		cConditionNot conditionSup( NULL );
		
		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer );
		cReadBits iBitStream4( * pFileIn );
		iBitStream4.readBits( &cBuffer, 2 );
		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"cConditionNot pUnderConditionNot3LoadedFull = cCondition::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionNot3LoadedFull = cCondition::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&conditionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionNot3LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionNot3LoadedFull, "pUnderConditionNot3LoadedFull", conditionNot2, "conditionNot2" );
			//check the getDefiningFibElement() methode from cConditionNot
			if ( pUnderConditionNot3LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionNot3LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionNot3LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from cConditionNot
			if ( pUnderConditionNot3LoadedFull->getSuperiorCondition() == &conditionSup  ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionNot3LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionNot3LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionNot3LoadedFull;
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
 * This method tests the subcondtion methods of the cConditionNot class.
 *
 * methods tested:
 * 	- cCondition * getSubCondition();
 * 	- bool setSubCondition( cCondition * pInSubCondition, bool bDeleteOld=true );
 * 	- bool setSubCondition( const cCondition & pInSubCondition, bool bDeleteOld=true );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testSubCondition( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the subcondtion methods ( setSubCondition( cCondition * ) )"<<endl;
	
	cout<<"cConditionNot conditionNot1( NULL );"<<endl;
	cConditionNot conditionNot1( NULL );
	cCondition * pSubCondition = NULL;

	//check the getValue() methode from cConditionNot
	if ( conditionNot1.getValue() == false ){
	
		cout<<"The condition value is correctly "<<
			(conditionNot1.getValue()?"true":"false") <<" . "<<endl;
	}else{
		cerr<<"Error: The condition value is "<<
			(conditionNot1.getValue()?"true":"false") <<" but should be false ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionNot1.getSubCondition() == pSubCondition ){
	
		cout<<"The subcondition of the condition correctly "<<
			conditionNot1.getSubCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The subcondition of the condition is "<<
			conditionNot1.getSubCondition() <<
			" but should be "<< pSubCondition <<" ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from cConditionNot
	if ( ! conditionNot1.isValid() ){
	
		cout<<"The condition is correctly not valid . "<<endl;
	}else{
		cerr<<"Error: The condition is valid ."<<endl;
		iReturn++;
	}
	
	cout<<"pSubConditionFalse = new cConditionFalse();"<<endl;
	cConditionFalse * pSubConditionFalse = new cConditionFalse();
	pSubCondition = pSubConditionFalse;
	
	cout<<"conditionNot1.setSubCondition( pSubConditionFalse, false );"<<endl;
	bool bSubConditionSet = conditionNot1.setSubCondition(
		pSubConditionFalse, false );
	if ( bSubConditionSet ){
	
		cout<<"Subcondition was successfull set."<<endl;
	}else{
		cerr<<"Error: Subcondition was couldn't be set."<<endl;
		iReturn++;
	}
	
	//check the getValue() methode from cConditionNot
	if ( conditionNot1.getValue() == true ){
	
		cout<<"The condition value is correctly "<<
			(conditionNot1.getValue()?"true":"false") <<" . "<<endl;
	}else{
		cerr<<"Error: The condition value is "<<
			(conditionNot1.getValue()?"true":"false") <<" but should be false ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionNot1.getSubCondition() == pSubCondition ){
	
		cout<<"The subcondition of the condition correctly "<<
			conditionNot1.getSubCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The subcondition of the condition is "<<
			conditionNot1.getSubCondition() <<
			" but should be "<< pSubCondition <<" ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from cConditionNot
	if ( conditionNot1.isValid() ){
	
		cout<<"The condition is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The condition is not valid ."<<endl;
		iReturn++;
	}
	
	
	cout<<"conditionNot1.setSubCondition( NULL, false );"<<endl;
	bSubConditionSet = conditionNot1.setSubCondition( NULL, false );
	if ( ! bSubConditionSet ){
	
		cout<<"Subcondition was correctly not set."<<endl;
	}else{
		cerr<<"Error: Subcondition was could be set."<<endl;
		iReturn++;
	}
	
	//check the getValue() methode from cConditionNot
	if ( conditionNot1.getValue() == true ){
	
		cout<<"The condition value is correctly "<<
			(conditionNot1.getValue()?"true":"false") <<" . "<<endl;
	}else{
		cerr<<"Error: The condition value is "<<
			(conditionNot1.getValue()?"true":"false") <<" but should be false ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionNot1.getSubCondition() == pSubCondition ){
	
		cout<<"The subcondition of the condition correctly "<<
			conditionNot1.getSubCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The subcondition of the condition is "<<
			conditionNot1.getSubCondition() <<
			" but should be "<< pSubCondition <<" ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from cConditionNot
	if ( conditionNot1.isValid() ){
	
		cout<<"The condition is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The condition is not valid ."<<endl;
		iReturn++;
	}


	cout<<"pSubConditionTrue = new cConditionTrue();"<<endl;
	cConditionTrue * pSubConditionTrue = new cConditionTrue();
	pSubCondition = pSubConditionTrue;
	
	cout<<"conditionNot1.setSubCondition( pSubConditionTrue );"<<endl;
	bSubConditionSet = conditionNot1.setSubCondition( pSubConditionTrue );
	pSubConditionFalse = NULL;
	if ( bSubConditionSet ){
	
		cout<<"Subcondition was successfull set."<<endl;
	}else{
		cerr<<"Error: Subcondition was couldn't be set."<<endl;
		iReturn++;
	}
	
	//check the getValue() methode from cConditionNot
	if ( conditionNot1.getValue() == false ){
	
		cout<<"The condition value is correctly "<<
			(conditionNot1.getValue()?"true":"false") <<" . "<<endl;
	}else{
		cerr<<"Error: The condition value is "<<
			(conditionNot1.getValue()?"true":"false") <<" but should be false ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionNot1.getSubCondition() == pSubCondition ){
	
		cout<<"The subcondition of the condition correctly "<<
			conditionNot1.getSubCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The subcondition of the condition is "<<
			conditionNot1.getSubCondition() <<
			" but should be "<< pSubCondition <<" ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from cConditionNot
	if ( conditionNot1.isValid() ){
	
		cout<<"The condition is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The condition is not valid ."<<endl;
		iReturn++;
	}
	
	
	cout<<"cConditionFalse subConditionFalse;"<<endl;
	cConditionFalse subConditionFalse;
	pSubCondition = &subConditionFalse;
	
	cout<<"conditionNot1.setSubCondition( subConditionFalse );"<<endl;
	bSubConditionSet = conditionNot1.setSubCondition( subConditionFalse );
	pSubConditionFalse = NULL;
	if ( bSubConditionSet ){
	
		cout<<"Subcondition was successfull set."<<endl;
	}else{
		cerr<<"Error: Subcondition was couldn't be set."<<endl;
		iReturn++;
	}
	
	//check the getValue() methode from cConditionNot
	if ( conditionNot1.getValue() == true ){
	
		cout<<"The condition value is correctly "<<
			(conditionNot1.getValue()?"true":"false") <<" . "<<endl;
	}else{
		cerr<<"Error: The condition value is "<<
			(conditionNot1.getValue()?"true":"false") <<" but should be false ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionNot1.getSubCondition()->equal( *pSubCondition ) ){
	
		cout<<"The subcondition of the condition correctly equal to "<<
			conditionNot1.getSubCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The subcondition of the condition is not equal to "<<
			conditionNot1.getSubCondition() <<
			" but should be "<< pSubCondition <<" ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from cConditionNot
	if ( conditionNot1.isValid() ){
	
		cout<<"The condition is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The condition is not valid ."<<endl;
		iReturn++;
	}
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the subcondtion methods ( setSubCondition( cCondition & ) )"<<endl;
	
	cout<<"cConditionNot conditionNot2( NULL );"<<endl;
	cConditionNot conditionNot2( NULL );
	pSubCondition = NULL;

	//check the getValue() methode from cConditionNot
	if ( conditionNot2.getValue() == false ){
	
		cout<<"The condition value is correctly "<<
			(conditionNot2.getValue()?"true":"false") <<" . "<<endl;
	}else{
		cerr<<"Error: The condition value is "<<
			(conditionNot2.getValue()?"true":"false") <<" but should be false ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionNot2.getSubCondition() == pSubCondition ){
	
		cout<<"The subcondition of the condition correctly "<<
			conditionNot2.getSubCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The subcondition of the condition is not "<<
			conditionNot2.getSubCondition() <<
			" but should be "<< pSubCondition <<" ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from cConditionNot
	if ( ! conditionNot2.isValid() ){
	
		cout<<"The condition is correctly not valid . "<<endl;
	}else{
		cerr<<"Error: The condition is valid ."<<endl;
		iReturn++;
	}
	
	pSubCondition = &subConditionFalse;
	
	cout<<"conditionNot2.setSubCondition( subConditionFalse, false );"<<endl;
	bSubConditionSet = conditionNot2.setSubCondition(
		subConditionFalse, false );
	if ( bSubConditionSet ){
	
		cout<<"Subcondition was successfull set."<<endl;
	}else{
		cerr<<"Error: Subcondition was couldn't be set."<<endl;
		iReturn++;
	}
	
	//check the getValue() methode from cConditionNot
	if ( conditionNot2.getValue() == true ){
	
		cout<<"The condition value is correctly "<<
			(conditionNot2.getValue()?"true":"false") <<" . "<<endl;
	}else{
		cerr<<"Error: The condition value is "<<
			(conditionNot2.getValue()?"true":"false") <<" but should be false ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionNot2.getSubCondition()->equal( *pSubCondition ) ){
	
		cout<<"The subcondition of the condition correctly equal to "<<
			conditionNot2.getSubCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The subcondition of the condition is not equal to "<<
			conditionNot2.getSubCondition() <<
			" but should be "<< pSubCondition <<" ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from cConditionNot
	if ( conditionNot2.isValid() ){
	
		cout<<"The condition is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The condition is not valid ."<<endl;
		iReturn++;
	}
	
	
	cout<<"conditionNot2.setSubCondition( NULL, false );"<<endl;
	bSubConditionSet = conditionNot2.setSubCondition( NULL, false );
	if ( ! bSubConditionSet ){
	
		cout<<"Subcondition was correctly not set."<<endl;
	}else{
		cerr<<"Error: Subcondition was could be set."<<endl;
		iReturn++;
	}
	
	//check the getValue() methode from cConditionNot
	if ( conditionNot2.getValue() == true ){
	
		cout<<"The condition value is correctly "<<
			(conditionNot2.getValue()?"true":"false") <<" . "<<endl;
	}else{
		cerr<<"Error: The condition value is "<<
			(conditionNot2.getValue()?"true":"false") <<" but should be false ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionNot2.getSubCondition()->equal( *pSubCondition ) ){
	
		cout<<"The subcondition of the condition correctly equal to "<<
			conditionNot2.getSubCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The subcondition of the condition is not equal to "<<
			conditionNot2.getSubCondition() <<
			" but should be "<< pSubCondition <<" ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from cConditionNot
	if ( conditionNot2.isValid() ){
	
		cout<<"The condition is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The condition is not valid ."<<endl;
		iReturn++;
	}


	cout<<"cConditionTrue subConditionTrue"<<endl;
	cConditionTrue subConditionTrue;
	pSubCondition = &subConditionTrue;
	
	cout<<"conditionNot2.setSubCondition( subConditionTrue );"<<endl;
	bSubConditionSet = conditionNot2.setSubCondition( subConditionTrue );
	pSubCondition = &subConditionTrue;
	if ( bSubConditionSet ){
	
		cout<<"Subcondition was successfull set."<<endl;
	}else{
		cerr<<"Error: Subcondition was couldn't be set."<<endl;
		iReturn++;
	}
	
	//check the getValue() methode from cConditionNot
	if ( conditionNot2.getValue() == false ){
	
		cout<<"The condition value is correctly "<<
			(conditionNot2.getValue()?"true":"false") <<" . "<<endl;
	}else{
		cerr<<"Error: The condition value is "<<
			(conditionNot2.getValue()?"true":"false") <<" but should be false ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionNot2.getSubCondition()->equal( *pSubCondition ) ){
	
		cout<<"The subcondition of the condition correctly equal to "<<
			conditionNot2.getSubCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The subcondition of the condition is not equal to "<<
			conditionNot2.getSubCondition() <<
			" but should be "<< pSubCondition <<" ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from cConditionNot
	if ( conditionNot2.isValid() ){
	
		cout<<"The condition is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The condition is not valid ."<<endl;
		iReturn++;
	}
	
	pSubConditionFalse = new cConditionFalse();
	cout<<"conditionNot2.setSubCondition( pSubConditionFalse );"<<endl;
	bSubConditionSet = conditionNot2.setSubCondition( pSubConditionFalse );
	pSubCondition = &subConditionFalse;
	if ( bSubConditionSet ){
	
		cout<<"Subcondition was successfull set."<<endl;
	}else{
		cerr<<"Error: Subcondition was couldn't be set."<<endl;
		iReturn++;
	}
	
	//check the getValue() methode from cConditionNot
	if ( conditionNot2.getValue() == true ){
	
		cout<<"The condition value is correctly "<<
			(conditionNot2.getValue()?"true":"false") <<" . "<<endl;
	}else{
		cerr<<"Error: The condition value is "<<
			(conditionNot2.getValue()?"true":"false") <<" but should be false ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionNot2.getSubCondition()->equal( *pSubCondition ) ){
	
		cout<<"The subcondition of the condition correctly equal to "<<
			conditionNot2.getSubCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The subcondition of the condition is not equal to "<<
			conditionNot2.getSubCondition() <<
			" but should be "<< pSubCondition <<" ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from cConditionNot
	if ( conditionNot2.isValid() ){
	
		cout<<"The condition is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The condition is not valid ."<<endl;
		iReturn++;
	}
	
	//check defining Fib-Element of sub and subsubfunctions
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the subcondtion method setSubCondition() while checking the defining element"<<endl;
	
	cout<<"cPoint point; "<<endl;
	cPoint point;
	
	cout<<"cConditionNot conditionNot3( NULL, NULL, &point );"<<endl;
	cConditionNot conditionNot3( NULL, NULL, &point );
	
	pSubCondition = NULL;
	
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionNot3.getSubCondition() == pSubCondition ){
	
		cout<<"The subcondition of the condition correctly "<<
			conditionNot3.getSubCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The subcondition of the condition is not "<<
			conditionNot3.getSubCondition() <<
			" but should be "<< pSubCondition <<" ."<<endl;
		iReturn++;
	}
	cout<<"conditionNot3.setSubCondition( conditionNot2 );"<<endl;
	bSubConditionSet = conditionNot3.setSubCondition( conditionNot2 );
	pSubCondition = &conditionNot2;
	if ( bSubConditionSet ){
	
		cout<<"Subcondition was successfull set."<<endl;
	}else{
		cerr<<"Error: Subcondition was couldn't be set."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionNot3.getSubCondition()->equal( *pSubCondition ) ){
	
		cout<<"The subcondition of the condition correctly equal to "<<
			conditionNot3.getSubCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The subcondition of the condition is not equal to "<<
			conditionNot3.getSubCondition() <<
			" but should be "<< pSubCondition <<" ."<<endl;
		iReturn++;
	}
	//check defining element
	if ( conditionNot3.getDefiningFibElement() == &point ){
	
		cout<<"The defining element is correctly point. "<<endl;
	}else{
		cerr<<"Error: The defining element is correctly not point."<<endl;
		iReturn++;
	}
	if ( conditionNot3.getSubCondition()->getDefiningFibElement() == &point ){
	
		cout<<"The defining element of the subcondition is correctly point. "<<endl;
	}else{
		cerr<<"Error: The defining element of the subcondition is correctly not point."<<endl;
		iReturn++;
	}
	if ( ((cConditionNot*)(conditionNot3.getSubCondition()))->
			getSubCondition()->getDefiningFibElement() == &point ){
	
		cout<<"The defining element of the subsubcondition is correctly point. "<<endl;
	}else{
		cerr<<"Error: The defining element of the subsubcondition is correctly not point."<<endl;
		iReturn++;
	}
	
	pSubCondition = new cConditionNot( new cConditionTrue() );
	cout<<"conditionNot3.setSubCondition( pSubCondition );"<<endl;
	bSubConditionSet = conditionNot3.setSubCondition( pSubCondition );
	if ( bSubConditionSet ){
	
		cout<<"Subcondition was successfull set."<<endl;
	}else{
		cerr<<"Error: Subcondition was couldn't be set."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionNot
	if ( conditionNot3.getSubCondition() == pSubCondition ){
	
		cout<<"The subcondition of the condition correctly "<<
			conditionNot3.getSubCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The subcondition of the condition is not "<<
			conditionNot3.getSubCondition() <<
			" but should be "<< pSubCondition <<" ."<<endl;
		iReturn++;
	}
	//check defining element
	if ( conditionNot3.getDefiningFibElement() == &point ){
	
		cout<<"The defining element is correctly point. "<<endl;
	}else{
		cerr<<"Error: The defining element is correctly not point."<<endl;
		iReturn++;
	}
	if ( conditionNot3.getSubCondition()->getDefiningFibElement() == &point ){
	
		cout<<"The defining element of the subcondition is correctly point. "<<endl;
	}else{
		cerr<<"Error: The defining element of the subcondition is correctly not point."<<endl;
		iReturn++;
	}
	if ( ((cConditionNot*)(conditionNot3.getSubCondition()))->
			getSubCondition()->getDefiningFibElement() == &point ){
	
		cout<<"The defining element of the subsubcondition is correctly point. "<<endl;
	}else{
		cerr<<"Error: The defining element of the subsubcondition is correctly not point."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the variable methods of the cConditionNot class.
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
	
	cout<<"cConditionNot conditionNot1( NULL );"<<endl;
	cConditionNot conditionNot1( NULL );
	
	cout<<"cConditionFalse subConditionFalse;"<<endl;
	cConditionFalse subConditionFalse;
	cout<<"cConditionNot conditionNot2( subConditionFalse );"<<endl;
	cConditionNot conditionNot2( subConditionFalse );

	//check the isUsedVariable() methode from cConditionNot
	cout<<"conditionNot1.isUsedVariable( pVariableSimple1 )"<<endl;
	if ( ! conditionNot1.isUsedVariable( pVariableSimple1 ) ){
	
		cout<<"The variable pVariableSimple1 is correctly not used in the condition element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableSimple1 is used in the condition element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = conditionNot1.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = conditionNot1.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"The correctly no used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The ther are used variables given back. "<<endl;
		iReturn++;
	}
	cout<<"conditionNot1.replaceVariable( pVariableSimple1, pVariableSimple1 );"<<endl;
	bool bVariableReplaced = conditionNot1.replaceVariable( pVariableSimple1, pVariableSimple1 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	
	//check the isUsedVariable() methode from cConditionNot
	cout<<"conditionNot2.isUsedVariable( pVariableSimple1 )"<<endl;
	if ( ! conditionNot2.isUsedVariable( pVariableSimple1 ) ){
	
		cout<<"The variable pVariableSimple1 is correctly not used in the condition element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableSimple1 is used in the condition element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = conditionNot2.getUsedVariables(); "<<endl;
	setUsedVariables = conditionNot2.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"The correctly no used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The ther are used variables given back. "<<endl;
		iReturn++;
	}
	cout<<"conditionNot2.replaceVariable( pVariableSimple1, pVariableSimple1 );"<<endl;
	bVariableReplaced = conditionNot2.replaceVariable( pVariableSimple1, pVariableSimple1 );
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
	
	cCondition * pSubCondition = NULL;
	bool bSubConditionValue = false;
	cFibVariable * pVariableSubCondition = NULL;
	
	cout<<"pConditionNot = new cConditionNot( "<<
		pSubCondition<<", NULL, &point  );"<<endl;
	cConditionNot * pConditionNot = new cConditionNot( NULL, NULL, &point );
	bool bIsValid = false;
	
	set< cFibVariable* > setCorrectUsedVariables;
	
	for ( unsigned int uiIteration = 1; uiIteration <= 64; uiIteration++ ){
		
		cout<<endl;
		if ( (rand() % 16) == 0 ){
			//create new condition
			if ( pConditionNot ){
				delete pConditionNot;
				pConditionNot = NULL;
				pSubCondition = NULL;
				bSubConditionValue = false;
				pVariableSubCondition = NULL;
			}
			if ( rand() % 4 ){
				if ( rand() % 4 == 0 ){
					pSubCondition = new cConditionGreater(
						new cFunctionValue( domFunValues.round(
							((double)(rand() % (256 * 256))) / 256.0 ) ),
						new cFunctionValue( domFunValues.round(
							((double)(rand() % (256 * 256))) / 256.0 ) ) );
					bSubConditionValue = pSubCondition->getValue();
					cout<<"pSubCondition("<<pSubCondition<<") = new cConditionGreater( "<<
						" cFunctionValue , cFunctionValue );"<<endl;
					pVariableSubCondition = NULL;
				}else{
					const size_t uiChoosenVariable = rand() % vecVariablen.size();
					pSubCondition = new cConditionGreater(
						new cFunctionValue( domFunValues.round(
							((double)(rand() % (256 * 256))) / 256.0 ) ),
						new cFunctionVariable( vecVariablen[ uiChoosenVariable ] ) );
					bSubConditionValue = pSubCondition->getValue();
					cout<<"pSubCondition("<<pSubCondition<<") = new cConditionGreater( "<<
						"cFunctionValue, cFunctionVariable( pVariable"<<uiChoosenVariable<<"="<<
						vecVariablen[ uiChoosenVariable ]<<") );"<<endl;
					pVariableSubCondition = vecVariablen[ uiChoosenVariable ];
				}
			}
			cout<<"pConditionNot = new cConditionNot( "<<
				pSubCondition<<", NULL, &point  );"<<endl;
			pConditionNot = new cConditionNot( pSubCondition, NULL, &point );
		}else if ( rand() % 2 ){//change subcondition
			
			if ( rand() % 4 ){
				//set subcondition to variable
				const size_t uiChoosenVariable = rand() % vecVariablen.size();
				pSubCondition =  new cConditionGreater(
					new cFunctionVariable( vecVariablen[ uiChoosenVariable ] ),
					new cFunctionValue( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) ) );
				bSubConditionValue = pSubCondition->getValue();
				cout<<"pSubCondition("<<pSubCondition<<") = new cConditionGreater( "<<
					"cFunctionVariable( pVariable"<<uiChoosenVariable<<"="<<
					vecVariablen[ uiChoosenVariable ]<<"), cFunctionValue );"<<endl;
				cout<<"pConditionNot->setSubCondition( "<<pSubCondition<<" );"<<endl;
				pConditionNot->setSubCondition( pSubCondition );
				pVariableSubCondition = vecVariablen[ uiChoosenVariable ];
			}else{//change to value
				//set subcondition to value
				pSubCondition = new cConditionGreater(
					new cFunctionValue( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) ),
					new cFunctionValue( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) ) );
				cout<<"pSubCondition("<<pSubCondition<<") = new cConditionGreater( "<<
					" cFunctionValue , cFunctionValue );"<<endl;
				bSubConditionValue = pSubCondition->getValue();
				cout<<"pConditionNot->setSubCondition( "<<pSubCondition<<" );"<<endl;
				pConditionNot->setSubCondition( pSubCondition );
				pVariableSubCondition = NULL;
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
					
					cout<<"pConditionNot->replaceVariable( "<<(*itrToReplaceVariable)<<
						", "<< vecVariablen[ uiVariableToReplaceWith ]<<" );"<<endl;
					const bool bVariableReplaced = pConditionNot->replaceVariable(
						(*itrToReplaceVariable), vecVariablen[ uiVariableToReplaceWith ] );
					if ( bVariableReplaced ){
					
						cout<<"The variable was correctly replaced. "<<endl;
					}else{
						cerr<<"Error: The variable was not replaced. "<<endl;
						iReturn++;
					}
					//update values
					if ( pVariableSubCondition == (*itrToReplaceVariable) ){
						bSubConditionValue = pSubCondition->getValue();
						pVariableSubCondition = vecVariablen[ uiVariableToReplaceWith ];
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
					
					cout<<"pConditionNot->replaceVariable( "<<
						vecVariablen[ uiVariableToReplace ]<<", "<<
						vecVariablen[ uiVariableToReplaceWith ]<<" );"<<endl;
					const bool bVariableReplaced = pConditionNot->replaceVariable(
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
						
						cout<<"pConditionNot->replaceVariable( NULL,"<<
							vecVariablen[ uiVariableToReplaceWith ]<<" );"<<endl;
						const bool bVariableReplaced = pConditionNot->replaceVariable(
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
						
						cout<<"pConditionNot->replaceVariable( "<<
							vecVariablen[ uiVariableToReplace ]<<", NULL );"<<endl;
						const bool bVariableReplaced = pConditionNot->replaceVariable(
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
				if ( pVariableSubCondition == (*itrToReplaceVariable) ){
					bSubConditionValue = pSubCondition->getValue();
				}
			}
		}
		setCorrectUsedVariables.clear();
		if ( pVariableSubCondition ){
			setCorrectUsedVariables.insert( pVariableSubCondition );
		}
		
		if ( pSubCondition != NULL ){
			bIsValid = true;
		}else{
			bIsValid = false;
		}
		
		//check the isUsedVariable() methode from cConditionNot
		for ( vector< cFibVariable * >::const_iterator itrVariable = vecVariablen.begin();
				itrVariable != vecVariablen.end(); itrVariable++ ){
			
			const bool bShouldBeUsedVariable = setCorrectUsedVariables.find(
					*itrVariable ) != setCorrectUsedVariables.end();
			
			cout<<"pConditionNot->isUsedVariable( "<<(*itrVariable)<<" )"<<endl;
			if ( pConditionNot->isUsedVariable( *itrVariable ) == bShouldBeUsedVariable ){
			
				cout<<"The variable "<<(*itrVariable)<<" is correctly "<<
					(bShouldBeUsedVariable?"":"not ")<<"used in the condition element. "<<endl;
			}else{
				cerr<<"Error: The variable "<<(*itrVariable)<<" is "<<
					(bShouldBeUsedVariable?"not ":"")<<"used in the condition element. "<<endl;
				iReturn++;
			}
		}
		//check getUsedVariables()
		cout<<"setUsedVariables = pConditionNot->getUsedVariables(); "<<endl;
		set<cFibVariable*> setUsedVariables = pConditionNot->getUsedVariables();
		if ( setUsedVariables == setCorrectUsedVariables ){
		
			cout<<"The correct used variables wher given back. "<<endl;
		}else{
			cerr<<"Error: Not correct used variables wher given back. "<<endl;
			setCorrectUsedVariables = setUsedVariables;
			iReturn++;
		}
		
		//check the getValue() methode from cConditionNot
		if ( pSubCondition ){
			if ( pConditionNot->getValue() != bSubConditionValue ){
		
				cout<<"The condition value is correctly "<<
					(pConditionNot->getValue()?"true":"false") <<" . "<<endl;
			}else{
				cerr<<"Error: The condition value is "<<
					(pConditionNot->getValue()?"true":"false") <<" but should be "<<
					(pConditionNot->getValue()?"false":"true") <<" ( first="<<
					(bSubConditionValue?"true":"false")<<" )."<<endl;
				iReturn++;
			}
		}else{//no subcondition
			if ( ! pConditionNot->getValue() ){
		
				cout<<"The condition value is correctly "<<
					(pConditionNot->getValue()?"true":"false") <<" . "<<endl;
			}else{
				cerr<<"Error: The condition value is "<<
					(pConditionNot->getValue()?"true":"false") <<" but should be "<<
					(pConditionNot->getValue()?"false":"true") <<" because no subcondition."<<endl;
				iReturn++;
			}
		}
		//check the isValid() methode from cConditionNot
		if ( pConditionNot->isValid() == bIsValid ){
		
			cout<<"The condition is correctly "<<(bIsValid?"":"not ")<<"valid . "<<endl;
		}else{
			cerr<<"Error: The condition is "<<(bIsValid?"not ":"")<<"valid ."<<endl;
			iReturn++;
		}
	}
	if ( pConditionNot ){
		delete pConditionNot;
		pConditionNot = NULL;
		pSubCondition = NULL;
	}
	
	
	return iReturn;
}



/**
 * This method tests the variable methods of the cConditionNot class.
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
	
	cout<<"cConditionNot conditionNot1( NULL );"<<endl;
	cConditionNot conditionNot1( NULL );
	
	cConditionNot conditionNotCorrect( NULL );
	
	cFibElement * pDefiningFibElement = NULL;
	//check the getDefiningFibElement() methode from cConditionNot
	if ( conditionNot1.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionNot1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionNot1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( conditionNot1, "conditionNot1", conditionNotCorrect, "correct condition" );
	
	cPoint pointDef1;
	cout<<"conditionNot1.setDefiningFibElement( &pointDef1 );"<<endl;
	conditionNot1.setDefiningFibElement( &pointDef1 );
	pDefiningFibElement = &pointDef1;
	//check the getDefiningFibElement() methode from cConditionNot
	if ( conditionNot1.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionNot1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionNot1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( conditionNot1, "conditionNot1", conditionNotCorrect, "correct condition" );
	
	cout<<"conditionNot1.setDefiningFibElement( &pointDef1 );"<<endl;
	conditionNot1.setDefiningFibElement( &pointDef1 );
	pDefiningFibElement = &pointDef1;
	//check the getDefiningFibElement() methode from cConditionNot
	if ( conditionNot1.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionNot1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionNot1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( conditionNot1, "conditionNot1", conditionNotCorrect, "correct condition" );
	

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
	
	cCondition * pSubCondition = NULL;
	bool bSubConditionValue = false;
	
	pDefiningFibElement = &point;
	cout<<"pConditionNot = new cConditionNot( "<<
		pSubCondition<<", NULL, &point="<<
		pDefiningFibElement<<" );"<<endl;
	cConditionNot * pConditionNot = new cConditionNot( NULL, NULL, pDefiningFibElement );
	bool bIsValid = false;
	
	for ( unsigned int uiIteration = 1; uiIteration <= 256; uiIteration++ ){
		
		cout<<endl;
		if ( (rand() % 16) == 0 ){
			//create new condition
			if ( pConditionNot ){
				delete pConditionNot;
				pConditionNot = NULL;
				pSubCondition = NULL;
				bSubConditionValue = 0;
			}
			if ( rand() % 4 ){
				//set first subcondition
				cFunctionValue funSubValue1( domFunValues.round(
					((double)(rand() % (256 * 256))) / 256.0 ) );
				cFunctionValue funSubValue2( domFunValues.round(
					((double)(rand() % (256 * 256))) / 256.0 ) );
				pSubCondition = new cConditionGreater( funSubValue1, funSubValue2 );
				bSubConditionValue = pSubCondition->getValue();
				cout<<"pSubCondition("<<pSubCondition<<") = new cConditionGreater( cFunctionValue( "<<
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
			cout<<"pConditionNot = new cConditionNot( "<<
				pSubCondition<<", NULL, "<<
				pDefiningFibElement<<"  );"<<endl;
			pConditionNot = new cConditionNot( pSubCondition, NULL, pDefiningFibElement );
		}else{
			switch ( rand() % 3 ){
				//create subsubconditions
				case 0:{
					//set first subcondition
					cFunctionValue funSubValue1( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					cFunctionValue funSubValue2( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					pSubCondition = new cConditionGreater ( funSubValue1, funSubValue2 );
					bSubConditionValue = pSubCondition->getValue();
					cout<<"pSubCondition("<<pSubCondition<<") = new cConditionGreater( cFunctionValue( "<<
						funSubValue1.getValue()<<" ), cFunctionValue( "<<
						funSubValue2.getValue()<<" ) );"<<endl;
					cout<<"pConditionNot->setSubCondition( "<<pSubCondition<<" );"<<endl;
					pConditionNot->setSubCondition( pSubCondition );
				}break;
				case 1:{
					//set first subcondition
					pSubCondition = &conditionGreater;
					bSubConditionValue = conditionGreater.getValue();
					cout<<"pConditionNot->setSubCondition( conditionGreater );"<<endl;
					pConditionNot->setSubCondition( conditionGreater );
				}break;
				case 2:{
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
					cout<<"pConditionNot->setDefiningFibElement( "<<pDefiningFibElement<<", "<<
						(bCheckValues?"true":"false")<<" );"<<endl;
					pConditionNot->setDefiningFibElement( pDefiningFibElement, bCheckValues );
					if ( bCheckValues ){
						if ( pDefiningFibElement == &point1 ){
							//round to correct values
							bSubConditionValue  = domIntegerBit8.round( bSubConditionValue );
						}
					}
				}break;
				
			}
		}
		if ( pSubCondition != NULL ){
			bIsValid = pConditionNot->getSubCondition()->isValid();
		}else{
			bIsValid = false;
		}
		
		//check the getValue() methode from cConditionNot
		if ( pSubCondition ){
			if ( pConditionNot->getValue() != bSubConditionValue ){
		
				cout<<"The condition value is correctly "<<
					(pConditionNot->getValue()?"true":"false") <<" . "<<endl;
			}else{
				cerr<<"Error: The condition value is "<<
					(pConditionNot->getValue()?"true":"false") <<" but should be "<<
					(pConditionNot->getValue()?"false":"true") <<" ( first="<<
					(bSubConditionValue?"true":"false")<<" )."<<endl;
				iReturn++;
			}
		}else{//no subcondition
			if ( ! pConditionNot->getValue() ){
		
				cout<<"The condition value is correctly "<<
					(pConditionNot->getValue()?"true":"false") <<" . "<<endl;
			}else{
				cerr<<"Error: The condition value is "<<
					(pConditionNot->getValue()?"true":"false") <<" but should be "<<
					(pConditionNot->getValue()?"false":"true") <<" because no subcondition."<<endl;
				iReturn++;
			}
		}
		//check the isValid() methode from cConditionNot
		if ( pConditionNot->isValid() == bIsValid ){
		
			cout<<"The condition is correctly "<<(bIsValid?"":"not ")<<"valid . "<<endl;
		}else{
			cerr<<"Error: The condition is "<<(bIsValid?"not ":"")<<"valid ."<<endl;
			iReturn++;
		}
		//check defining Fib-Element of sub and subsubconditions
		if ( pConditionNot->getSubCondition() != NULL ){
			if ( pConditionNot->getSubCondition()->getDefiningFibElement() == pDefiningFibElement ){
			
				cout<<"The definig fib-element of the first subcondition is "<<
					pDefiningFibElement<<"."<<endl;
			}else{
				cerr<<"Error: The definig fib-element of the first subcondition is not "<<
					pDefiningFibElement<<"."<<endl;
				iReturn++;
			}
			if ( pConditionNot->getSubCondition()->getType() == cCondition::CONDITION_GREATER ){
				
				cConditionGreater * pSubCondition = ((cConditionGreater*)(pConditionNot->getSubCondition()));
				
				if ( pSubCondition->getFirstSubFunction()->getDefiningFibElement() == pDefiningFibElement ){
				
					cout<<"The definig fib-element of the first subsubcondition is "<<
						pDefiningFibElement<<"."<<endl;
				}else{
					cerr<<"Error: The definig fib-element of the first subsubcondition is not "<<
						pDefiningFibElement<<"."<<endl;
					iReturn++;
				}
				if ( pSubCondition->getSecondSubFunction()->getDefiningFibElement() == pDefiningFibElement ){
				
					cout<<"The definig fib-element of the second subsubcondition is "<<
						pDefiningFibElement<<"."<<endl;
				}else{
					cerr<<"Error: The definig fib-element of the second subsubcondition is not "<<
						pDefiningFibElement<<"."<<endl;
					iReturn++;
				}
			}
		}
	}
	if ( pConditionNot ){
		delete pConditionNot;
		pConditionNot = NULL;
		pSubCondition = NULL;
	}


	return iReturn;
}








