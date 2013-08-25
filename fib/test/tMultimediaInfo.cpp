/**
 * @file tMultimediaInfo
 * file name: tMultimediaInfo.cpp
 * @author Betti Oesterholz
 * @date 25.06.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cMultimediaInfo.
 *
 * Copyright (C) @c GPL3 2009 Betti Oesterholz
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
 * This file contains the test for the class cMultimediaInfo, which
 * represents the multimedia information of an root -element.
 *
 *
 *  What's tested of class tVectorChecksum:
 * 	- cMultimediaInfo( cRoot * root);
 * 	- cMultimediaInfo *clone() const;
 * 	- unsignedLongFib getFibVersion() const;
 * 	- void setFibVersion( unsignedLongFib ulFibVersion );
 * 	- unsignedLongFib getDatabaseVersion() const;
 * 	- void setDatabaseVersion( unsignedLongFib ulFibDbVersion );
 * 	- bool evalueMinVersionsNumbers();
 * 	- bool equal( const cMultimediaInfo &multimediaInfo ) const;
 * 	- bool operator==( const cMultimediaInfo & multimediaInfo) const;
 * 	- bool assignValues( const cMultimediaInfo & multimediaInfo );
 * 	- bool storeXml( ostream & ostream ) const;
 *
 */
/*
History:
25.06.2009  Oesterholz  created
17.11.2009  Oesterholz  storeXml() tested
02.08.2013  Oesterholz  assignValues() tested
*/

#include "version.h"

#include "cMultimediaInfo.h"
#include "cRoot.h"

#include "tinyxml.h"

#include <iostream>
#include <fstream>
#include <ostream>

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif



using namespace fib;
using namespace std;

int testCostructor( unsigned long & ulTestphase );
int testEvalueMinVersionsNumbers( unsigned long & ulTestphase );
int testSetVersion( unsigned long & ulTestphase );
int testClone( unsigned long & ulTestphase );
int testEqual( unsigned long & ulTestphase );
int testStoreXml( unsigned long & ulTestphase );
int testAssignValue( unsigned long & ulTestphase );


unsigned long MAX_ITERATION = 64;


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	cout<<endl<<"Running Test for cMultimediaInfo methods"<<endl;
	cout<<      "========================================"<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testEvalueMinVersionsNumbers( ulTestphase );
	iReturn += testSetVersion( ulTestphase );
	iReturn += testClone( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testAssignValue( ulTestphase );


	if ( iReturn==0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}


	return iReturn;
}


/**
 * This method tests the constructor of the cMultimediaInfo class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCostructor( unsigned long & ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cMultimediaInfo"<<endl;

	//TODO adapt root -constructor
	cRoot * masterRoot= new cRoot();

	cout<<"cMultimediaInfo multimediaInfoTest1=cMultimediaInfo( masterRoot );"<<endl;
	cMultimediaInfo multimediaInfoTest1=cMultimediaInfo( masterRoot );

	//check the getFibVersion() methode from cMultimediaInfo
	if ( multimediaInfoTest1.getFibVersion() == FIB_VERSION ){
	
		cout<<"The Fib -Versionnumber is correctly "<<FIB_VERSION<<". "<<endl;
	}else{
		cerr<<"Error: The Fib -Versionnumber is "<<
			multimediaInfoTest1.getFibVersion()<<" but should be "<<
			FIB_VERSION<<"."<<endl;
		iReturn++;
	}

	//check the getDatabaseVersion() methode from cMultimediaInfo
	if ( multimediaInfoTest1.getDatabaseVersion()==(unsignedIntFib)(FIB_DB_VERSION) ){
	
		cout<<"The Fib -Databaseversionnumber is correctly "<<FIB_DB_VERSION<<". "<<endl;
	}else{
		cerr<<"Error: The Fib -Databaseversionnumber is "<<
			multimediaInfoTest1.getDatabaseVersion()<<" but should be "<<
			FIB_DB_VERSION<<"."<<endl;
		iReturn++;
	}
	delete masterRoot;
	
	return iReturn;
}


/**
 * This method tests the evalueMinVersionsNumbers() method of the class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testEvalueMinVersionsNumbers( unsigned long & ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing method evalueMinVersionsNumbers()"<<endl;

	//TODO adapt root -constructor
	cRoot * masterRoot= new cRoot();
	cout<<"cMultimediaInfo multimediaInfoTest1=cMultimediaInfo( masterRoot );"<<endl;
	cMultimediaInfo multimediaInfoTest1=cMultimediaInfo( masterRoot );


	//check the evalueMinVersionsNumbers() methode from cMultimediaInfo
	if ( multimediaInfoTest1.evalueMinVersionsNumbers() ){
	
		cout<<"The versionnumbers could be updated."<<endl;
	}else{
		cerr<<"Error: The versionnumbers couldn't be updated."<<endl;
		iReturn++;
	}

	//check the getFibVersion() methode from cMultimediaInfo
	if ( multimediaInfoTest1.getFibVersion()==FIB_VERSION ){
	
		cout<<"The Fib -Versionnumber is correctly "<<FIB_VERSION<<". "<<endl;
	}else{
		cerr<<"Error: The Fib -Versionnumber is "<<
			multimediaInfoTest1.getFibVersion()<<" but should be "<<
			FIB_VERSION<<"."<<endl;
		iReturn++;
	}

	//check the getDatabaseVersion() methode from cMultimediaInfo
	if ( multimediaInfoTest1.getDatabaseVersion()==(unsignedIntFib)(FIB_DB_VERSION) ){
	
		cout<<"The Fib -Databaseversionnumber is correctly "<<FIB_DB_VERSION<<". "<<endl;
	}else{
		cerr<<"Error: The Fib -Databaseversionnumber is "<<
			multimediaInfoTest1.getDatabaseVersion()<<" but should be "<<
			FIB_DB_VERSION<<"."<<endl;
		iReturn++;
	}
	delete masterRoot;

	return iReturn;
}


/**
 * This method tests the setFibVersion() and setFibDbVersion()
 * methods of the class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testSetVersion( unsigned long & ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setFibVersion() method"<<endl;

	//TODO adapt root -constructor
	cRoot * masterRoot= new cRoot();
	cout<<"cMultimediaInfo multimediaInfoTest1=cMultimediaInfo( masterRoot );"<<endl;
	cMultimediaInfo multimediaInfoTest1=cMultimediaInfo( masterRoot );


	multimediaInfoTest1.setFibVersion( 2 );
	cout<<"multimediaInfoTest1.setFibVersion( 2 ) "<<endl;

	//check the getFibVersion() methode from cMultimediaInfo
	if ( multimediaInfoTest1.getFibVersion()==2 ){
	
		cout<<"The Fib -Versionnumber is correctly "<<2<<". "<<endl;
	}else{
		cerr<<"Error: The Fib -Versionnumber is "<<
			multimediaInfoTest1.getFibVersion()<<" but should be "<<
			2<<"."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setDatabaseVersion() method"<<endl;

	multimediaInfoTest1.setDatabaseVersion( 3 );
	cout<<"multimediaInfoTest1.setDatabaseVersion( 3 ) "<<endl;

	//check the getDatabaseVersion() methode from cMultimediaInfo
	if ( multimediaInfoTest1.getDatabaseVersion()==(unsignedIntFib)(3) ){
	
		cout<<"The Fib -Databaseversionnumber is correctly "<<3<<". "<<endl;
	}else{
		cerr<<"Error: The Fib -Databaseversionnumber is "<<
			multimediaInfoTest1.getDatabaseVersion()<<" but should be "<<
			3<<"."<<endl;
		iReturn++;
	}
	delete masterRoot;

	return iReturn;
}



/**
 * This method tests the clone() method of the class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testClone( unsigned long & ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the clone() method"<<endl;

	//TODO adapt root -constructor
	cRoot * masterRoot= new cRoot();
	cout<<"cMultimediaInfo multimediaInfoTest1=cMultimediaInfo( masterRoot );"<<endl;
	cMultimediaInfo multimediaInfoTest1=cMultimediaInfo( masterRoot );

	multimediaInfoTest1.setFibVersion( 2 );
	cout<<"multimediaInfoTest1.setFibVersion( 2 ) "<<endl;

	multimediaInfoTest1.setDatabaseVersion( 3 );
	cout<<"multimediaInfoTest1.setDatabaseVersion( 3 ) "<<endl;

	cout<<"cMultimediaInfo *multimediaInfoClone1=multimediaInfoTest1.clone();"<<endl;
	cMultimediaInfo *multimediaInfoClone1=multimediaInfoTest1.clone();


	cout<<endl<<"checking the clone:"<<endl;
	//check the getFibVersion() methode from cMultimediaInfo
	if ( multimediaInfoClone1->getFibVersion()==2 ){
	
		cout<<"The Fib -Versionnumber is correctly "<<2<<". "<<endl;
	}else{
		cerr<<"Error: The Fib -Versionnumber is "<<
			multimediaInfoClone1->getFibVersion()<<" but should be "<<
			2<<"."<<endl;
		iReturn++;
	}
	//check the getDatabaseVersion() methode from cMultimediaInfo
	if ( multimediaInfoClone1->getDatabaseVersion()==(unsignedIntFib)(3) ){
	
		cout<<"The Fib -Databaseversionnumber is correctly "<<3<<". "<<endl;
	}else{
		cerr<<"Error: The Fib -Databaseversionnumber is "<<
			multimediaInfoClone1->getDatabaseVersion()<<" but should be "<<
			3<<"."<<endl;
		iReturn++;
	}
	delete multimediaInfoClone1;


	cout<<endl<<"checking the original:"<<endl;
	//check the getFibVersion() methode from cMultimediaInfo
	if ( multimediaInfoTest1.getFibVersion()==2 ){
	
		cout<<"The Fib -Versionnumber is correctly "<<2<<". "<<endl;
	}else{
		cerr<<"Error: The Fib -Versionnumber is "<<
			multimediaInfoTest1.getFibVersion()<<" but should be "<<
			2<<"."<<endl;
		iReturn++;
	}
	//check the getDatabaseVersion() methode from cMultimediaInfo
	if ( multimediaInfoTest1.getDatabaseVersion()==(unsignedIntFib)(3) ){
	
		cout<<"The Fib -Databaseversionnumber is correctly "<<3<<". "<<endl;
	}else{
		cerr<<"Error: The Fib -Databaseversionnumber is "<<
			multimediaInfoTest1.getDatabaseVersion()<<" but should be "<<
			3<<"."<<endl;
		iReturn++;
	}
	delete masterRoot;

	return iReturn;
}





/**
 * This method tests the equal() method and the operator== of two given
 * cMultimediaInfo objects which are equal.
 *
 * @param multimediaInfo1 the first type to compare
 * @param szNameType1 the name of the first type to compare
 * @param multimediaInfo2 the secound type to compare to
 * @param szNameType2 the name of the secound type to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualMultimediaInfo( const cMultimediaInfo &multimediaInfo1, const string &szNameType1,
	const cMultimediaInfo &multimediaInfo2, const string &szNameType2 ){
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	if ( multimediaInfo1.equal( multimediaInfo2 ) ){
	
		cout<<"The "<<szNameType1<<" is equal to "<<szNameType2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameType1<<" is not equal to "<<
			szNameType2<<"."<<endl;
		iReturn++;
	}
	if ( multimediaInfo1==multimediaInfo2 ){
	
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
 * cMultimediaInfo objects which are not equal.
 *
 * @param multimediaInfo1 the first type to compare
 * @param szNameType1 the name of the first type to compare
 * @param multimediaInfo2 the secound type to compare to
 * @param szNameType2 the name of the secound type to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoNotEqualMultimediaInfo( const cMultimediaInfo &multimediaInfo1, const string &szNameType1,
	const cMultimediaInfo &multimediaInfo2, const string &szNameType2 ){
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	if ( ! multimediaInfo1.equal( multimediaInfo2 ) ){
	
		cout<<"The "<<szNameType1<<" is not equal to "<<szNameType2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameType1<<" is equal to "<<
			szNameType2<<"."<<endl;
		iReturn++;
	}
	if ( ! (multimediaInfo1==multimediaInfo2) ){
	
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
 * This method tests the operator==() method of the class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testEqual( unsigned long & ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the operator==() method"<<endl;

	//TODO adapt root -constructor
	cRoot * masterRoot= new cRoot();
	
	cout<<"cMultimediaInfo multimediaInfoTest1=cMultimediaInfo( masterRoot );"<<endl;
	cMultimediaInfo multimediaInfoTest1=cMultimediaInfo( masterRoot );
	multimediaInfoTest1.setFibVersion( 2 );
	cout<<"multimediaInfoTest1.setFibVersion( 2 ) "<<endl;
	multimediaInfoTest1.setDatabaseVersion( 3 );
	cout<<"multimediaInfoTest1.setDatabaseVersion( 3 ) "<<endl;

	cout<<"cMultimediaInfo multimediaInfoTest2=cMultimediaInfo( masterRoot );"<<endl;
	cMultimediaInfo multimediaInfoTest2=cMultimediaInfo( masterRoot );
	multimediaInfoTest2.setFibVersion( 2 );
	cout<<"multimediaInfoTest2.setFibVersion( 2 ) "<<endl;
	multimediaInfoTest2.setDatabaseVersion( 3 );
	cout<<"multimediaInfoTest2.setDatabaseVersion( 3 ) "<<endl;

	cout<<"cMultimediaInfo multimediaInfoTest3=cMultimediaInfo( masterRoot );"<<endl;
	cMultimediaInfo multimediaInfoTest3=cMultimediaInfo( masterRoot );
	multimediaInfoTest3.setFibVersion( 2 );
	cout<<"multimediaInfoTest3.setFibVersion( 2 ) "<<endl;
	multimediaInfoTest3.setDatabaseVersion( 5 );
	cout<<"multimediaInfoTest3.setDatabaseVersion( 5 ) "<<endl;

	cout<<"cMultimediaInfo multimediaInfoTest4=cMultimediaInfo( masterRoot );"<<endl;
	cMultimediaInfo multimediaInfoTest4=cMultimediaInfo( masterRoot );
	multimediaInfoTest4.setFibVersion( 1 );
	cout<<"multimediaInfoTest4.setFibVersion( 1 ) "<<endl;
	multimediaInfoTest4.setDatabaseVersion( 5 );
	cout<<"multimediaInfoTest4.setDatabaseVersion( 5 ) "<<endl;

	cRoot * masterRoot1= new cRoot();
	cout<<"cMultimediaInfo multimediaInfoTest5=cMultimediaInfo( masterRoot1 );"<<endl;
	cMultimediaInfo multimediaInfoTest5=cMultimediaInfo( masterRoot1 );
	multimediaInfoTest5.setFibVersion( 1 );
	cout<<"multimediaInfoTest5.setFibVersion( 1 ) "<<endl;
	multimediaInfoTest5.setDatabaseVersion( 5 );
	cout<<"multimediaInfoTest5.setDatabaseVersion( 5 ) "<<endl;
	
	cout<<"cMultimediaInfo multimediaInfoTest6=cMultimediaInfo( masterRoot );"<<endl;
	cMultimediaInfo multimediaInfoTest6=cMultimediaInfo( masterRoot );
	multimediaInfoTest6.setFibVersion( 0 );
	cout<<"multimediaInfoTest6.setFibVersion( 0 ) "<<endl;
	multimediaInfoTest6.setDatabaseVersion( 0 );
	cout<<"multimediaInfoTest6.setDatabaseVersion( 0 ) "<<endl;


	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with multimediaInfoTest1
	cMultimediaInfo *actualMultimediaInfo = &multimediaInfoTest1;
	string szActualMultimediaInfoName = "multimediaInfoTest1";
	iReturn += testCompareTwoEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest1, "multimediaInfoTest1" );
	iReturn += testCompareTwoEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest2, "multimediaInfoTest2" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest3, "multimediaInfoTest3" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest4, "multimediaInfoTest4" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest5, "multimediaInfoTest5" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest6, "multimediaInfoTest6" );

	//compare with multimediaInfoTest2
	actualMultimediaInfo = &multimediaInfoTest2;
	szActualMultimediaInfoName = "multimediaInfoTest2";
	iReturn += testCompareTwoEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest1, "multimediaInfoTest1" );
	iReturn += testCompareTwoEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest2, "multimediaInfoTest2" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest3, "multimediaInfoTest3" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest4, "multimediaInfoTest4" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest5, "multimediaInfoTest5" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest6, "multimediaInfoTest6" );
	
	//compare with multimediaInfoTest3
	actualMultimediaInfo = &multimediaInfoTest3;
	szActualMultimediaInfoName = "multimediaInfoTest3";
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest1, "multimediaInfoTest1" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest2, "multimediaInfoTest2" );
	iReturn += testCompareTwoEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest3, "multimediaInfoTest3" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest4, "multimediaInfoTest4" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest5, "multimediaInfoTest5" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest6, "multimediaInfoTest6" );
	
	//compare with multimediaInfoTest4
	actualMultimediaInfo = &multimediaInfoTest4;
	szActualMultimediaInfoName = "multimediaInfoTest4";
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest1, "multimediaInfoTest1" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest2, "multimediaInfoTest2" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest3, "multimediaInfoTest3" );
	iReturn += testCompareTwoEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest4, "multimediaInfoTest4" );
	iReturn += testCompareTwoEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest5, "multimediaInfoTest5" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest6, "multimediaInfoTest6" );
	
	//compare with multimediaInfoTest5
	actualMultimediaInfo = &multimediaInfoTest5;
	szActualMultimediaInfoName = "multimediaInfoTest5";
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest1, "multimediaInfoTest1" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest2, "multimediaInfoTest2" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest3, "multimediaInfoTest3" );
	iReturn += testCompareTwoEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest4, "multimediaInfoTest4" );
	iReturn += testCompareTwoEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest5, "multimediaInfoTest5" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest6, "multimediaInfoTest6" );
	
	//compare with multimediaInfoTest6
	actualMultimediaInfo = &multimediaInfoTest6;
	szActualMultimediaInfoName = "multimediaInfoTest6";
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest1, "multimediaInfoTest1" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest2, "multimediaInfoTest2" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest3, "multimediaInfoTest3" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest4, "multimediaInfoTest4" );
	iReturn += testCompareTwoNotEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest5, "multimediaInfoTest5" );
	iReturn += testCompareTwoEqualMultimediaInfo( *actualMultimediaInfo, szActualMultimediaInfoName, multimediaInfoTest6, "multimediaInfoTest6" );

	delete masterRoot;
	delete masterRoot1;

	return iReturn;
}



/**
 * This method tests a in the xml -format stored cMultimediaInfo.
 *
 * <multimedia_info fib_version="1" db_version="0"/>
 *
 * @param iFibVersion the fib -versionsnumber
 * @param iDbVersion the fib -database -versionsnumber
 * @return the number of errors occured in the test
 */
int testXmlVector( const string szFilename, int iFibVersion, int iDbVersion ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored vector:"<<endl;
	
	TiXmlDocument xmlDocMultimediaInfo( szFilename );
	bool loadOkay = xmlDocMultimediaInfo.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the multimediainfo was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocMultimediaInfo );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlHandleRoot(0);

	pXmlElement = xmlHandle.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();

		if ( szElementName == "multimedia_info" ){
			cout<<"The root element is correctly named \"multimedia_info\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"multimedia_info\"."<<endl;
			iReturn++;
		}
		
		int iLoadedFibVersion = 0;
		const char * szVectorXmlFibVersion = pXmlElement->Attribute( "fib_version", &iLoadedFibVersion );
		
		if ( szVectorXmlFibVersion == NULL ){
			cerr<<"Error: The multimediainfo has no fib -versionsnumber."<<endl;
			iReturn++;
		}else if ( iFibVersion == iLoadedFibVersion ) {
			cout<<"The fib -versionsnumber of the multimediainfo is correctly \""<< iFibVersion <<"\". "<<endl;
		}else{
			cerr<<"Error: The fib -versionsnumber of the multimediainfo is \""<< iLoadedFibVersion
				<<"\", but should be \""<< iFibVersion <<"\"."<<endl;
			iReturn++;
		}
		
		int iLoadedDbVersion = 0;
		const char * szVectorXmlDbVersion = pXmlElement->Attribute( "db_version", &iLoadedDbVersion );
		
		if ( szVectorXmlDbVersion == NULL ){
			cerr<<"Error: The multimediainfo has no database -versionsnumber."<<endl;
			iReturn++;
		}else if ( iDbVersion == iLoadedDbVersion ) {
			cout<<"The database -versionsnumber of the multimediainfo is correctly \""<< iDbVersion <<"\". "<<endl;
		}else{
			cerr<<"Error: The database -versionsnumber of the multimediainfo is \""<< iLoadedDbVersion
				<<"\", but should be \""<< iDbVersion <<"\"."<<endl;
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
 * This method tests the storeXml() method of the cMultimediaInfo class.
 *
 * methods tested:
 * 	- storeXml()
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStoreXml( unsigned long & ulTestphase ){

	unsigned int iReturn = 0;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an empty multimediainfo"<<endl;
	
	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;
	
	cout<<"cMultimediaInfo multimediainfo( &root );"<<endl;
	cMultimediaInfo multimediainfo( &root );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * pFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "multimediainfoEmpty.xml" );
	ofstream * file = new ofstream( pFileName );
	
	bool bStoreSuccesfull = multimediainfo.storeXml( *file );
	delete file;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< pFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< pFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlVector( pFileName, FIB_VERSION, FIB_DB_VERSION );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an multimediainfo with versionsvalues"<<endl;
	
	cout<<"cMultimediaInfo multimediainfoFib1Db2( &root );"<<endl;
	cMultimediaInfo multimediainfoFib1Db2( &root );
	
	cout<<"multimediainfoFib54Db3.setFibVersion( 1 );"<<endl;
	multimediainfoFib1Db2.setFibVersion( 1 );
	cout<<"multimediainfoFib54Db3.setDatabaseVersion( 2 );"<<endl;
	multimediainfoFib1Db2.setDatabaseVersion( 2 );
	
	szFileNameBuffer[0] = 0;
	pFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "multimediainfoFib1Db2.xml" );
	file = new ofstream( pFileName );
	
	bStoreSuccesfull = multimediainfoFib1Db2.storeXml( *file );
	delete file;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< pFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< pFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlVector( pFileName, 1, 2 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an multimediainfo with versionsvalues"<<endl;
	
	cout<<"cMultimediaInfo multimediainfoFib54Db3( &root );"<<endl;
	cMultimediaInfo multimediainfoFib54Db3( &root );
	
	cout<<"multimediainfoFib54Db3.setFibVersion( 54 );"<<endl;
	multimediainfoFib54Db3.setFibVersion( 54 );
	cout<<"multimediainfoFib54Db3.setDatabaseVersion( 3 );"<<endl;
	multimediainfoFib54Db3.setDatabaseVersion( 3 );
	
	szFileNameBuffer[0] = 0;
	pFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "multimediainfoFib54Db3.xml" );
	file = new ofstream( pFileName );
	
	bStoreSuccesfull = multimediainfoFib54Db3.storeXml( *file );
	delete file;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< pFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< pFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlVector( pFileName, 54, 3 );


	return iReturn;
}


/**
 * This method tests the assignValues() method of the cMultimediaInfo class.
 *
 * methods tested:
 * 	- bool assignValues( const cMultimediaInfo & multimediaInfo );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testAssignValue( unsigned long & ulTestphase ){

	unsigned int iReturn = 0;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the assignValues() method"<<endl;
	
	cout<<"cRoot root1;"<<flush<<endl;
	cRoot root1;
	
	cout<<"cMultimediaInfo multimediainfo( &root1 );"<<endl;
	cMultimediaInfo multimediainfo( &root1 );
	
	cout<<"cRoot root2;"<<flush<<endl;
	cRoot root2;
	
	cout<<"cMultimediaInfo multimediainfoToSet( &root2 );"<<endl;
	cMultimediaInfo multimediainfoToSet( &root2 );
	
	for ( unsigned int iteraton = 0; iteraton < MAX_ITERATION; iteraton++ ){
		
		multimediainfoToSet.setFibVersion( rand() );
		multimediainfoToSet.setDatabaseVersion( rand() );
		cout<<"changing multimediainfoToSet to version="<<
			multimediainfoToSet.getFibVersion()<<" database version="<<
			multimediainfoToSet.getDatabaseVersion()<<endl;
		cout<<"multimediainfo.assignValues( multimediainfoToSet );"<<endl;
		multimediainfo.assignValues( multimediainfoToSet );
		
		if ( ! ( multimediainfo == multimediainfoToSet ) ){
			
			cerr<<"Error: The multimediainfo is not equal to multimediainfoToSet."<<endl;
			iReturn++;
		}
		
	}
	
	return iReturn;
}





