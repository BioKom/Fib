/**
 * @file tConditionFalse
 * file name: tConditionFalse.cpp
 * @author Betti Oesterholz
 * @date 01.05.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cConditionFalse.
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
 * This file contains the test for the class cConditionFalse, which
 * represents a false condition.
 *
 *
 * What's tested of class cConditionFalse:
 * 	- cConditionFalse( cCondition * pInSuperiorCondition = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cConditionFalse( const cConditionFalse & condition, cCondition * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- ~cConditionFalse();
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
 *
 */
/*
History:
01.05.2011  Oesterholz  created
*/

#include "version.h"

#include "cConditionFalse.h"
#include "cPoint.h"
#include "cRoot.h"
#include "cProperty.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"
#include "cTypeVariable.h"
#include "cTypeInVar.h"
#include "cVectorProperty.h"
#include "cEvaluePositionList.h"
#include "cEvalueFibElementList.h"
#include "cReadBits.h"

#include "cConditionTrue.h"

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
	
	cout<<endl<<"Running Test for cConditionFalse methods"<<endl;
	cout<<      "========================================"<<endl;

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
 * This method tests the constructor of the cConditionFalse class.
 *
 * methods tested:
 * 	- cConditionFalse( cCondition * pInSuperiorCondition = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- ~cConditionFalse();
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cConditionFalse condition"<<endl;

	cout<<"cConditionFalse underConditionFalse1;"<<endl;
	cConditionFalse underConditionFalse1;
	cFibElement * pDefiningFibElement = NULL;
	cCondition * pSuperiorCondition = NULL;
	unsigned long ulTimeNeed = 1;
	unsigned long ulCompressedSize = 4;
 
	//check the getValue() methode from cConditionFalse
	if ( underConditionFalse1.getValue() == false  ){
	
		cout<<"The condition value is correctly "<<
			underConditionFalse1.getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition value is "<<
			underConditionFalse1.getValue() <<" but should be false ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cConditionFalse
	if ( underConditionFalse1.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			underConditionFalse1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			underConditionFalse1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionFalse
	if ( underConditionFalse1.getSuperiorCondition() == pSuperiorCondition  ){
	
		cout<<"The superior condition of the condition correctly "<<
			underConditionFalse1.getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			underConditionFalse1.getSuperiorCondition() <<
			" but should be "<< pSuperiorCondition <<" ."<<endl;
		iReturn++;
	}
	
	//check the isValid() methode from cConditionFalse
	if ( underConditionFalse1.isValid() ){
	
		cout<<"The condition is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The condition is not valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cConditionFalse
	if ( underConditionFalse1.getType() == 0 ){
	
		cout<<"The condition type is correctly CONDITION_FALSE. "<<endl;
	}else{
		cerr<<"Error: The type of the condition is not CONDITION_FALSE ( 0 ), but "<<
			underConditionFalse1.getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getConditionName() methode from cConditionFalse
	if ( underConditionFalse1.getConditionName() == "false" ){
	
		cout<<"The condition name is correctly "<<
			underConditionFalse1.getConditionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the condition is not \"false\", but "<<
			underConditionFalse1.getConditionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfConditions() methode from cConditionFalse
	if ( underConditionFalse1.getNumberOfConditions() == 0 ){
	
		cout<<"The condition number of subconditions is correctly "<<
			underConditionFalse1.getNumberOfConditions() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition number of subconditions is "<<
			underConditionFalse1.getNumberOfConditions() <<" , but should be 0 ."<<endl;
		iReturn++;
	}
	//check the getNumberOfConditions() methode from cConditionFalse
	if ( underConditionFalse1.getNumberOfUnderFunctions() == 0 ){
	
		cout<<"The condition number of underconditions is correctly "<<
			underConditionFalse1.getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition number of underconditions is "<<
			underConditionFalse1.getNumberOfUnderFunctions() <<" , but should be 0 ."<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cConditionFalse
	if ( underConditionFalse1.getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the condition is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the condition is "<<
			underConditionFalse1.getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cConditionFalse
	if ( underConditionFalse1.getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the condition is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The tcompressed size of the condition is "<<
			underConditionFalse1.getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cConditionFalse
	if ( ! underConditionFalse1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 isn't used in the condition. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the condition. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cConditionFalse
	set<cFibVariable*> setUsedVariables = underConditionFalse1.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"No used variables are given back from the condition. "<<endl;
	}else{
		cerr<<"Error: Used variables are given back from the condition. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an cConditionFalse condition"<<endl;

	cout<<"cConditionFalse underConditionFalse2( &underConditionFalse1, &rootEmpty  );"<<endl;
	cConditionFalse underConditionFalse2( &underConditionFalse1, &rootEmpty );
	
	pDefiningFibElement = &rootEmpty;
	pSuperiorCondition = &underConditionFalse1;

	//check the getValue() methode from cConditionFalse
	if ( underConditionFalse2.getValue() == false  ){
	
		cout<<"The condition value is correctly "<<
			underConditionFalse2.getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition value is "<<
			underConditionFalse2.getValue() <<" but should be false ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cConditionFalse
	if ( underConditionFalse2.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			underConditionFalse2.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			underConditionFalse2.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionFalse
	if ( underConditionFalse2.getSuperiorCondition() == pSuperiorCondition  ){
	
		cout<<"The superior condition of the condition correctly "<<
			underConditionFalse2.getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			underConditionFalse2.getSuperiorCondition() <<
			" but should be "<< pSuperiorCondition <<" ."<<endl;
		iReturn++;
	}
	
	//check the isValid() methode from cConditionFalse
	if ( underConditionFalse2.isValid() ){
	
		cout<<"The condition is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The condition is not valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cConditionFalse
	if ( underConditionFalse2.getType() == cCondition::CONDITION_FALSE ){
	
		cout<<"The condition type is correctly CONDITION_FALSE. "<<endl;
	}else{
		cerr<<"Error: The type of the condition is not CONDITION_FALSE ( 0 ), but "<<
			underConditionFalse2.getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getConditionName() methode from cConditionFalse
	if ( underConditionFalse2.getConditionName() == "false" ){
	
		cout<<"The condition name is correctly "<<
			underConditionFalse2.getConditionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the condition is not \"false\", but "<<
			underConditionFalse2.getConditionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfConditions() methode from cConditionFalse
	if ( underConditionFalse2.getNumberOfConditions() == 0 ){
	
		cout<<"The condition number of subconditions is correctly "<<
			underConditionFalse2.getNumberOfConditions() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition number of subconditions is "<<
			underConditionFalse2.getNumberOfConditions() <<" , but should be 0 ."<<endl;
		iReturn++;
	}
	//check the getNumberOfConditions() methode from cConditionFalse
	if ( underConditionFalse2.getNumberOfUnderFunctions() == 0 ){
	
		cout<<"The condition number of underconditions is correctly "<<
			underConditionFalse2.getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition number of underconditions is "<<
			underConditionFalse2.getNumberOfUnderFunctions() <<" , but should be 0 ."<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cConditionFalse
	if ( underConditionFalse2.getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the condition is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the condition is "<<
			underConditionFalse2.getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cConditionFalse
	if ( underConditionFalse2.getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the condition is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The tcompressed size of the condition is "<<
			underConditionFalse2.getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cConditionFalse
	if ( ! underConditionFalse2.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 isn't used in the condition. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the condition. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cConditionFalse
	setUsedVariables = underConditionFalse2.getUsedVariables();
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
 * This method tests equal method of the cConditionFalse class.
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
	cout<<"cConditionFalse underConditionFalse1;"<<endl;
	cConditionFalse underConditionFalse1;

	cout<<"cConditionFalse underConditionFalse2;"<<endl;
	cConditionFalse underConditionFalse2;

	//condition with defining Fib-element
	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	cout<<"cConditionFalse conditionDefFE( NULL, &rootSimple1 );"<<endl;
	cConditionFalse conditionDefFE( NULL, &rootSimple1 );

	//condition with superior condition
	cout<<"cConditionFalse conditionConSup;"<<endl;
	cConditionFalse conditionConSup;
	cout<<"cConditionFalse conditionSup( & conditionConSup );"<<endl;
	cConditionFalse conditionSup( & conditionConSup );

	//condition with domains set
	cout<<"root1 rootSimple1;"<<endl;
	cRoot root1;
	
	cout<<"cTypeVariable testTypeVariable;"<<endl;
	cTypeVariable testTypeVariable;
	cout<<"cDomainNaturalNumberBit domainNat8( 8 );"<<endl;
	cDomainNaturalNumberBit domainNat8( 8 );

	cout<<"root1.getDomains()->addDomain( testTypeVariable, &domainNat8 );"<<endl;
	root1.getDomains()->addDomain( testTypeVariable, &domainNat8 );

	cout<<"cConditionFalse conditionDom( NULL, &root1 );"<<endl;
	cConditionFalse conditionDom( NULL, &root1 );

	//condition with defining Fib-element and superior condition
	cout<<"cRoot rootSimple2;"<<endl;
	cRoot rootSimple2;
	cout<<"cConditionFalse conditionSup2;"<<endl;
	cConditionFalse conditionSup2;
	cout<<"cConditionFalse conditionDefFeUf( & conditionSup2, &rootSimple2 );"<<endl;
	cConditionFalse conditionDefFeUf( & conditionSup2, &rootSimple2 );

	//compare with other conditions
	cout<<"cConditionTrue underConditionTrue;"<<endl;
	cConditionTrue underConditionTrue;


	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with underConditionFalse1
	cCondition * actualObject = &underConditionFalse1;
	string szActualObjectName = "underConditionFalse1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underConditionFalse1, "underConditionFalse1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underConditionFalse2, "underConditionFalse2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeUf, "conditionDefFeUf" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underConditionTrue, "underConditionTrue" );

	//compare with underConditionFalse2
	actualObject = &underConditionFalse2;
	szActualObjectName = "underConditionFalse2";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underConditionFalse1, "underConditionFalse1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underConditionFalse2, "underConditionFalse2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeUf, "conditionDefFeUf" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underConditionTrue, "underConditionTrue" );

	//compare with conditionDefFE
	actualObject = &conditionDefFE;
	szActualObjectName = "conditionDefFE";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underConditionFalse1, "underConditionFalse1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underConditionFalse2, "underConditionFalse2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeUf, "conditionDefFeUf" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underConditionTrue, "underConditionTrue" );

	//compare with conditionSup
	actualObject = &conditionSup;
	szActualObjectName = "conditionSup";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underConditionFalse1, "underConditionFalse1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underConditionFalse2, "underConditionFalse2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeUf, "conditionDefFeUf" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underConditionTrue, "underConditionTrue" );

	//compare with conditionDom
	actualObject = &conditionDom;
	szActualObjectName = "conditionDom";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underConditionFalse1, "underConditionFalse1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underConditionFalse2, "underConditionFalse2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeUf, "conditionDefFeUf" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underConditionTrue, "underConditionTrue" );

	//compare with conditionDefFeUf
	actualObject = &conditionDefFeUf;
	szActualObjectName = "conditionDefFeUf";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underConditionFalse1, "underConditionFalse1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underConditionFalse2, "underConditionFalse2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, conditionDefFeUf, "conditionDefFeUf" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underConditionTrue, "underConditionTrue" );

	//compare with underConditionTrue
	actualObject = &underConditionTrue;
	szActualObjectName = "underConditionTrue";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underConditionFalse1, "underConditionFalse1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underConditionFalse2, "underConditionFalse2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFE, "conditionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionSup, "conditionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDom, "conditionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, conditionDefFeUf, "conditionDefFeUf" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underConditionTrue, "underConditionTrue" );


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
	
		cout<<"The superior conditionpointer for the conditionelement is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The superior conditionpointer for the conditionelement is not NULL, but "<<
			conditionObject1.getSuperiorCondition() <<" ."<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode
	if ( conditionObject1.getDefiningFibElement() == NULL ){
	
		cout<<"The defining Fib-elementpointer for the condition is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The defining Fib-elementpointer for the condition is not NULL."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the copy methods and copyconstructor of the cConditionFalse class.
 *
 * methods tested:
 * 	- cConditionFalse( const cConditionFalse & condition, cCondition * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- cCondition * clone( cCondition * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCopy( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a simple cConditionFalse"<<endl;

	cout<<"cConditionFalse underConditionFalse1;"<<endl;
	cConditionFalse underConditionFalse1;

	cout<<"cConditionFalse underConditionFalse1CopyConstruct( underConditionFalse1 );"<<endl;
	cConditionFalse underConditionFalse1CopyConstruct( underConditionFalse1 );

	iReturn += testCompareTwoEqualObjects( underConditionFalse1CopyConstruct, "underConditionFalse1CopyConstruct", underConditionFalse1, "underConditionFalse1" );
	iReturn += testNotConnectedCondition( underConditionFalse1CopyConstruct );

	cout<<"cCondition * pUnderConditionFalse1Clone = underConditionFalse1CopyConstruct.clone();"<<endl;
	cCondition * pUnderConditionFalse1Clone = underConditionFalse1CopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pUnderConditionFalse1Clone, "pUnderConditionFalse1Clone", underConditionFalse1, "underConditionFalse1" );
	iReturn += testNotConnectedCondition( *pUnderConditionFalse1Clone );
	delete pUnderConditionFalse1Clone;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cConditionFalse with a superior condition and defining Fib-element"<<endl;

	//condition with defining Fib-element and superior condition
	cout<<"cRoot rootSimple;"<<endl;
	cRoot rootSimple;
	cout<<"cConditionFalse conditionSup;"<<endl;
	cConditionFalse conditionSup;
	cout<<"cConditionFalse conditionDefFeUf( & conditionSup, &rootSimple );"<<endl;
	cConditionFalse conditionDefFeUf( & conditionSup, &rootSimple );

	cout<<"cConditionFalse conditionDefFeUfCopyConstruct( conditionDefFeUf );"<<endl;
	cConditionFalse conditionDefFeUfCopyConstruct( conditionDefFeUf );

	iReturn += testCompareTwoEqualObjects( conditionDefFeUfCopyConstruct, "conditionDefFeUfCopyConstruct", conditionDefFeUf, "conditionDefFeUf" );
	//check the getDefiningFibElement() methode from cConditionFalse
	if ( conditionDefFeUfCopyConstruct.getDefiningFibElement() == &rootSimple  ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionDefFeUfCopyConstruct.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionDefFeUfCopyConstruct.getDefiningFibElement() <<" but should be rootSimple ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionFalse
	if ( conditionDefFeUfCopyConstruct.getSuperiorCondition() == NULL  ){
	
		cout<<"The superior condition of the condition correctly "<<
			conditionDefFeUfCopyConstruct.getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			conditionDefFeUfCopyConstruct.getSuperiorCondition() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	
	cout<<"cCondition * pConditionDefFeUfClone = conditionDefFeUfCopyConstruct.clone();"<<endl;
	cCondition * pConditionDefFeUfClone = conditionDefFeUfCopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pConditionDefFeUfClone, "pConditionDefFeUfClone", conditionDefFeUf, "conditionDefFeUf" );
	//check the getDefiningFibElement() methode from cConditionFalse
	if ( pConditionDefFeUfClone->getDefiningFibElement() == &rootSimple  ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			pConditionDefFeUfClone->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			pConditionDefFeUfClone->getDefiningFibElement() <<" but should be rootSimple ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionFalse
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cConditionFalse with a superior condition and defining Fib-element which will be changed"<<endl;

	//condition with defining Fib-element and superior condition
	cout<<"cRoot rootSimple2;"<<endl;
	cRoot rootSimple2;
	cout<<"cConditionFalse conditionSup2;"<<endl;
	cConditionFalse conditionSup2;

	cout<<"cConditionFalse conditionDefFeUfCopy2Construct( conditionDefFeUf, &conditionSup2, &rootSimple2 );"<<endl;
	cConditionFalse conditionDefFeUfCopy2Construct( conditionDefFeUf, &conditionSup2, &rootSimple2 );

	iReturn += testCompareTwoEqualObjects( conditionDefFeUfCopy2Construct, "conditionDefFeUfCopy2Construct", conditionDefFeUf, "conditionDefFeUf" );
	//check the getDefiningFibElement() methode from cConditionFalse
	if ( conditionDefFeUfCopy2Construct.getDefiningFibElement() == &rootSimple2  ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			conditionDefFeUfCopy2Construct.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			conditionDefFeUfCopy2Construct.getDefiningFibElement() <<" but should be rootSimple2 ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionFalse
	if ( conditionDefFeUfCopy2Construct.getSuperiorCondition() == &conditionSup2  ){
	
		cout<<"The superior condition of the condition correctly "<<
			conditionDefFeUfCopy2Construct.getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			conditionDefFeUfCopy2Construct.getSuperiorCondition() <<
			" but should be conditionSup2 ."<<endl;
		iReturn++;
	}
	
	cout<<"pConditionDefFeUfClone = conditionDefFeUfCopyConstruct.clone( &conditionSup2, &rootSimple2 );"<<endl;
	pConditionDefFeUfClone = conditionDefFeUfCopyConstruct.clone( &conditionSup2, &rootSimple2 );

	iReturn += testCompareTwoEqualObjects( *pConditionDefFeUfClone, "pConditionDefFeUfClone", conditionDefFeUf, "conditionDefFeUf" );
	//check the getDefiningFibElement() methode from cConditionFalse
	if ( pConditionDefFeUfClone->getDefiningFibElement() == &rootSimple2  ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			pConditionDefFeUfClone->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			pConditionDefFeUfClone->getDefiningFibElement() <<" but should be rootSimple2 ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from cConditionFalse
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
 * This method tests a in the xml -format stored cConditionFalse.
 * The condition of the cConditionFalse should be a value condition
 * ( cConditionFalse ).
 *
 * @param szFilename the name of the file wher the cConditionFalse is stored
 * @return the number of errors occured in the test
 */
int testXmlConditionFalse( const string szFilename ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored cConditionFalse:"<<endl;
	
	TiXmlDocument xmlDocConditionFalse( szFilename );
	bool loadOkay = xmlDocConditionFalse.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocConditionFalse );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlHandleRoot(0);

	pXmlElement = xmlHandle.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();
		
		const string szConditionFalseElementName = "false";
		if ( szElementName == szConditionFalseElementName ){
			cout<<"The root element is correctly named \""<< szConditionFalseElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \""<< szConditionFalseElementName <<"\"."<<endl;
			iReturn++;
		}
		
		const char * pcValue = pXmlElement->GetText();
		if ( pcValue != NULL ){
			cerr<<"Error: The element has an text."<<endl;
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
 * This method tests the storeXml() method of the cConditionFalse class.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an false condition"<<endl;

	cout<<"cConditionFalse underConditionFalse1;"<<endl;
	cConditionFalse underConditionFalse1;
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * szXmlConditionFalseFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "underConditionFalse1.xml" );
	ofstream * pFileCondition = new ofstream( szXmlConditionFalseFileName );
	
	bool bStoreSuccesfull = underConditionFalse1.storeXml( *pFileCondition );
	delete pFileCondition;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cConditionFalse was stored successfull to the file \""<< szXmlConditionFalseFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cConditionFalse to the file \""<< szXmlConditionFalseFileName <<"\" failed."<<endl;
		iReturn++;
	}
	iReturn += testXmlConditionFalse( szXmlConditionFalseFileName );
	
	TiXmlDocument xmlDocConditionFalse( szFileNameBuffer );
	bool loadOkay = xmlDocConditionFalse.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"TiXmlHandle xmlHandle2( &xmlDocConditionFalse ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDocConditionFalse );
		cout<<"cConditionFalse * pUnderConditionFalse1Loaded = cCondition::restoreXml("<<
			"xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cCondition * pUnderConditionFalse1Loaded = cCondition::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionFalse1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionFalse1Loaded, "pUnderConditionFalse1Loaded", underConditionFalse1, "underConditionFalse1" );
			iReturn += testNotConnectedCondition( * pUnderConditionFalse1Loaded );
			delete pUnderConditionFalse1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cConditionFalse conditionSup;"<<endl;
		cConditionFalse conditionSup;

		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"TiXmlHandle xmlHandle4( &xmlDocConditionFalse ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDocConditionFalse );
		cout<<"cConditionFalse pUnderConditionFalse1LoadedFull = cCondition::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionFalse1LoadedFull = cCondition::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &conditionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionFalse1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionFalse1LoadedFull, "pUnderConditionFalse1LoadedFull", underConditionFalse1, "underConditionFalse1" );
			//check the getDefiningFibElement() methode from cConditionFalse
			if ( pUnderConditionFalse1LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionFalse1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionFalse1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from cConditionFalse
			if ( pUnderConditionFalse1LoadedFull->getSuperiorCondition() == &conditionSup  ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionFalse1LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionFalse1LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionFalse1LoadedFull;
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

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an false condition"<<endl;

	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;
	
	cout<<"cConditionFalse underConditionFalse1( NULL, &root );"<<endl;
	cConditionFalse underConditionFalse1( NULL, &root );

	//test get compressed size
	unsigned int uiCompressedSize = 4;
	if ( (unsigned int)(underConditionFalse1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			underConditionFalse1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "underConditionFalse1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0x00;
	unsigned char cRestBitPosition = 0;
	cout<<"underConditionFalse1.store( *pFile, cRestBits, cRestBitPosition );"<<endl;
	bool bStoreSuccesfull = underConditionFalse1.store( *pFile, cRestBit, cRestBitPosition );
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
	const char cConditionFalse1[] = { 0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cConditionFalse1, 1 );


	cDomainSingle * pValueDomain = new cDomainNaturalNumberBit( 16 );
	cDomainSingle * pVariableDomain = new cDomainNaturalNumberBit( 3 );
	
	ifstream * pFileIn = new ifstream( szFileNameBuffer );
	if ( (pFileIn != NULL) && ( pFileIn->good() ) ){
		
		cReadBits iBitStream2( * pFileIn );
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"cConditionFalse pUnderConditionFalse1Loaded = cCondition::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cCondition * pUnderConditionFalse1Loaded = cCondition::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pValueDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionFalse1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionFalse1Loaded, "pUnderConditionFalse1Loaded", underConditionFalse1, "underConditionFalse1" );
			iReturn += testNotConnectedCondition( * pUnderConditionFalse1Loaded );
			delete pUnderConditionFalse1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cConditionFalse conditionSup;"<<endl;
		cConditionFalse conditionSup;
		
		delete pFileIn;

		pFileIn = new ifstream( szFileNameBuffer );
		cReadBits iBitStream4( * pFileIn );
		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"cConditionFalse pUnderConditionFalse1LoadedFull = cCondition::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionFalse1LoadedFull = cCondition::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&conditionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionFalse1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionFalse1LoadedFull, "pUnderConditionFalse1LoadedFull", underConditionFalse1, "underConditionFalse1" );
			//check the getDefiningFibElement() methode from cConditionFalse
			if ( pUnderConditionFalse1LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionFalse1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionFalse1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from cConditionFalse
			if ( pUnderConditionFalse1LoadedFull->getSuperiorCondition() == &conditionSup  ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionFalse1LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionFalse1LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionFalse1LoadedFull;
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

	cout<<"cConditionFalse underConditionFalse2( NULL, &root );"<<endl;
	cConditionFalse underConditionFalse2( NULL, &root );
	
	//test get compressed size
	uiCompressedSize = 4;
	if ( (unsigned int)(underConditionFalse2.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			underConditionFalse2.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "underConditionFalse2.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0x01;
	cRestBitPosition = 2;
	cout<<"underConditionFalse2.store( *pFile, cRestBit, cRestBitPosition ); "<<endl;
	bStoreSuccesfull = underConditionFalse2.store( *pFile, cRestBit, cRestBitPosition );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = 0x01;
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
	//test stored data
	const char szUnderConditionFalse2[] = { 0x01 };
	iReturn += compareBytsWithFile( szFileNameBuffer, szUnderConditionFalse2, 1 );


	pFileIn = new ifstream( szFileNameBuffer );
	if ( (pFileIn != NULL) && ( pFileIn->good() ) ){
		
		char cBuffer;
		cReadBits iBitStream2( * pFileIn );
		iBitStream2.readBits( &cBuffer, 2 );
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"cConditionFalse pUnderConditionFalse3Loaded = cCondition::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cCondition * pUnderConditionFalse3Loaded = cCondition::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pValueDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionFalse3Loaded ){
			const int iErrorsEqual = testCompareTwoEqualObjects( 
				* pUnderConditionFalse3Loaded, "pUnderConditionFalse3Loaded", underConditionFalse2, "underConditionFalse2" );
			iReturn += testNotConnectedCondition( * pUnderConditionFalse3Loaded );
			if ( iErrorsEqual != 0 ){
				cerr<<"Error: Loaded condition not equal."<<endl;
			}
			iReturn += iErrorsEqual;
			delete pUnderConditionFalse3Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cConditionFalse conditionSup;"<<endl;
		cConditionFalse conditionSup;
		
		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer );
		cReadBits iBitStream4( * pFileIn );
		iBitStream4.readBits( &cBuffer, 2 );
		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"cConditionFalse pUnderConditionFalse3LoadedFull = cCondition::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&conditionSup, &rootSimple ); "<<endl;
		cCondition * pUnderConditionFalse3LoadedFull = cCondition::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&conditionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderConditionFalse3LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderConditionFalse3LoadedFull, "pUnderConditionFalse3LoadedFull", underConditionFalse2, "underConditionFalse2" );
			//check the getDefiningFibElement() methode from cConditionFalse
			if ( pUnderConditionFalse3LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The condition defining Fib-element is correctly "<<
					pUnderConditionFalse3LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition defining Fib-element is "<<
					pUnderConditionFalse3LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorCondition() methode from cConditionFalse
			if ( pUnderConditionFalse3LoadedFull->getSuperiorCondition() == &conditionSup  ){
			
				cout<<"The superior condition of the condition correctly "<<
					pUnderConditionFalse3LoadedFull->getSuperiorCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior condition of the condition is "<<
					pUnderConditionFalse3LoadedFull->getSuperiorCondition() <<
					" but should be conditionSup="<< &conditionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderConditionFalse3LoadedFull;
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
 * This method tests the variable methods of the cConditionFalse class.
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
	
	cout<<"cConditionFalse underConditionFalse1;"<<endl;
	cConditionFalse underConditionFalse1;
	
	cout<<"cConditionFalse underConditionFalse2;"<<endl;
	cConditionFalse underConditionFalse2;

	//check the isUsedVariable() methode from cConditionFalse
	cout<<"underConditionFalse1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! underConditionFalse1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the conditionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the conditionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underConditionFalse1.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = underConditionFalse1.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"The correctly no used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The ther are used variables given back. "<<endl;
		iReturn++;
	}
	cout<<"underConditionFalse1.replaceVariable( pVariable1, pVariable1 );"<<endl;
	bool bVariableReplaced = underConditionFalse1.replaceVariable( pVariable1, pVariable1 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	
	//check the isUsedVariable() methode from cConditionFalse
	cout<<"underConditionFalse2.isUsedVariable( pVariable1 )"<<endl;
	if ( ! underConditionFalse2.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the conditionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the conditionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underConditionFalse2.getUsedVariables(); "<<endl;
	setUsedVariables = underConditionFalse2.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"The correctly no used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The ther are used variables given back. "<<endl;
		iReturn++;
	}
	cout<<"underConditionFalse2.replaceVariable( pVariable1, pVariable1 );"<<endl;
	bVariableReplaced = underConditionFalse2.replaceVariable( pVariable1, pVariable1 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests the variable methods of the cConditionFalse class.
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
	
	cout<<"cConditionFalse underConditionFalse1;"<<endl;
	cConditionFalse underConditionFalse1;
	
	cConditionFalse ufValueCorrect1;
	
	cFibElement * pDefiningFibElement = NULL;
	//check the getDefiningFibElement() methode from cConditionFalse
	if ( underConditionFalse1.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			underConditionFalse1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			underConditionFalse1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( underConditionFalse1, "underConditionFalse1", ufValueCorrect1, "correct condition" );
	
	cPoint point1;
	cout<<"underConditionFalse1.setDefiningFibElement( &point1 );"<<endl;
	underConditionFalse1.setDefiningFibElement( &point1 );
	pDefiningFibElement = &point1;
	//check the getDefiningFibElement() methode from cConditionFalse
	if ( underConditionFalse1.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			underConditionFalse1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			underConditionFalse1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( underConditionFalse1, "underConditionFalse1", ufValueCorrect1, "correct condition" );
	
	cout<<"underConditionFalse1.setDefiningFibElement( &point1 );"<<endl;
	underConditionFalse1.setDefiningFibElement( &point1 );
	pDefiningFibElement = &point1;
	//check the getDefiningFibElement() methode from cConditionFalse
	if ( underConditionFalse1.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			underConditionFalse1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			underConditionFalse1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( underConditionFalse1, "underConditionFalse1", ufValueCorrect1, "correct condition" );
	

	return iReturn;
}








