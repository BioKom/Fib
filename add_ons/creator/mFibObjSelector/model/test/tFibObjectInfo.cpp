
//TODO check


/**
 * @file tFibObjectInfo
 * file name: tFibObjectInfo.cpp
 * @author Betti Oesterholz
 * @date 03.10.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cFibObjectInfo.
 *
 *
 * Copyright (C) @c GPL3 2013 Betti Oesterholz
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
 * This file contains the test for the class cFibObjectInfo, which
 * is a class for information about a Fib object.
 *
 *
 * What's tested of class cFibObjectInfo:
 * 	-TODO cFibObjectInfo( const unsigned long ulInIdentifier, const cFibObjectSource * pInFibObjectSource );
 * 	- cFibObjectInfo( istream & stream, int * iOutStatus=NULL );
 * 	- cFibObjectInfo( const TiXmlNode * pXmlNode, int * iOutStatus=NULL );
 * 	- cFibObjectInfo( const unsigned long ulInIdentifier, const string szInNameOfFibObject = "", const string szInDescription = "", const cFibObjectSource * pInFibObjectSource = NULL, const set< string > setChangeableBy = set< string >() );
 * 	- cFibObjectInfo( const cFibObjectInfo & fibObjectInfo );
 * 	- cFibObjectInfo( const unsigned long ulInIdentifier, const cFibObjectInfo & fibObjectInfo );
 * 	- ~cFibObjectInfo();
 * 	- cFibObjectInfo * clone() const;
 * 	- cFibObjectInfo * clone( const unsigned long ulInIdentifier ) const;
 * 	- string getName() const;
 * 	- unsigned long getIdentifier() const;
 * 	- void setIdentifier( const unsigned long ulNewIdentifier );
 * 	- string getFibObjectName() const;
 * 	- void setFibObjectName( const string & szFibObjectName );
 * 	- string getDescription() const;
 * 	- void setDescription( const string & szFibObjectDescription );
 * 	- cFibObjectSource * getFibObjectSource();
 * 	- const cFibObjectSource * getFibObjectSource() const;
 * 	- bool setFibObjectSource( const cFibObjectSource * pInFibObjectSource );
 * 	- cFibElement * loadFibObjectFromSource( int * iOutStatus = NULL );
 * 	- bool deleteLoadedFibObject();
 * 	-TODO bool extractInfoFromLoadedFibObject();
 * 	- std::set< std::string > getCategories() const;
 * 	- void setCategories( const std::set< std::string > & setInCategories );
 * 	- void addCategory( const std::string & strCategory );
 * 	- bool removeCategory( const std::string & strCategory );
 * 	- map< string, set< unsigned long > > getConnectedToMap() const;
 * 	- set< unsigned long > getConnectedFor( const string & szKey ) const;
 * 	- void addConnectionTo( const string & szKey, const unsigned long ulConnectedId );
 * 	- void addConnectionTo( const string & szKey, const set< unsigned long > & setNotConnectedIds );
 * 	- bool removeConnectionTo( const string & szKey, const unsigned long ulConnectedId );
 * 	- unsigned int removeConnectionTo( const string & szKey, const set< unsigned long > & setNotConnectedIds );
 * 	- vector< pair< time_t, unsigned long > > getLastUsedTimes() const;
 * 	- void setFibObjectUsed( time_t timestamp = 0 );
 * 	- set< string > getChangeableBy() const;
 * 	- bool canChange( const string & szUser ) const;
 * 	- void addUserWhichCanChange( const string & szUser );
 * 	- bool removeUserWhichCanChange( const string & szUser );
 * 	- void setNumberOfFibElements( const unsigned long ulInNumberOfFibElements );
 * 	- unsigned long getNumberOfFibElements() const;
 * 	- void setNumberOfInputVariables( const unsigned long ulInNumberOfInputVariables );
 * 	- unsigned long getNumberOfInputVariables() const;
 * 	- void setNumberOfExtSubobjects( const unsigned long ulInNumberOfExtSubobjects );
 * 	- unsigned long getNumberOfExtSubobjects() const;
 * 	- bool store( ostream & stream );
 * 	- int restoreFibObjectInfo( istream & stream );
 * 	- int restoreFibObjectInfo( const TiXmlNode * pXmlNode );
 * 	- static cFibObjectInfo * restore( istream & stream, int * iOutStatus=NULL );
 * 	- static cFibObjectInfo * restore( const TiXmlNode * pXmlNode, int * iOutStatus=NULL );
 *
 */
/*
History:
03.10.2013  Oesterholz  created
*/




#include <QtTest/QtTest>

#include "version.h"

#include "cFibObjectInfo.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <vector>
#include <ctime>

#include <QObject>
#include <QString>

#include "tinyxml.h"

#include "cFibElement.h"
#include "cPoint.h"
#include "cVectorPosition.h"

#include "cFibObjectSourcePath.h"
#include "cFibObjectSourceFibDb.h"


#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif



using namespace fib::nCreator;
using namespace fib;
using namespace std;


class tFibObjectInfo: public QObject{
	Q_OBJECT
	
	/**
	 * The number of iterations for the random tests.
	 */
	const unsigned long ulNumberRandomIterations;

public:
	
	/**
	 * standard constructor
	 */
	tFibObjectInfo():ulNumberRandomIterations( 64 ){
		
		srand( time(NULL) );
	}
	
	
private slots:
	void testCostructor_data();
	void testCostructor();
	void testIdentifier();
	void testName_data();
	void testName();
	void testDescription_data();
	void testDescription();
	void testFibObjectSource();
	void testConnectionTo();
	void testUsedTimes();
	void testUserCanChange();
	void testNumberOfFibElements();
	void testNumberOfInputVariables();
	void testNumberOfExtSubobjects();
	void testCategories();
	void testReStore_data();
	void testReStore();
	void testLoadFibObject_data();
	void testLoadFibObject();
	
};//end tFibObjectInfo

//create a single argument out of two comma seperated parts
#define SINGLE_ARG2(A,B) A,B

//Macros so that QTest::addColumn() can use the given data types
Q_DECLARE_METATYPE(string)
Q_DECLARE_METATYPE(set< string >)
Q_DECLARE_METATYPE(set< unsigned long >)
Q_DECLARE_METATYPE(list< time_t >)
Q_DECLARE_METATYPE( SINGLE_ARG2(map< string, set< unsigned long > >) )



/**
 * This testcase tests the constructor of the cFibObjectInfo class.
 *
 * methods tested:
 * 	- cFibObjectInfo( const unsigned long ulInIdentifier, const string szInNameOfFibObject = "", const string szInDescription = "", const cFibObjectSource * pInFibObjectSource = NULL, const set< string > setChangeableBy = set< string >() );
 * 	- cFibObjectInfo( const cFibObjectInfo & fibObjectInfo );
 * 	- cFibObjectInfo * clone() const;
 * 	- cFibObjectInfo( const unsigned long ulInIdentifier, const cFibObjectInfo & 
 * 	- cFibObjectInfo * clone( const unsigned long ulInIdentifier ) const;
 * 	- ~cFibObjectInfo();
 * 	- string getName() const;
 * 	- unsigned long getIdentifier() const;
 * 	- string getFibObjectName() const;
 * 	- string getDescription() const;
 * 	- cFibObjectSource * getFibObjectSource();
 * 	- set< string > getChangeableBy() const;
 */
void tFibObjectInfo::testCostructor_data(){
	
	QTest::addColumn< unsigned long >("ulIdentifier");
	QTest::addColumn< string >("szNameOfFibObject");
	QTest::addColumn< string >("szDescription");
	//use dummy pointer for the Fib object source object
	QTest::addColumn< int >("iFibObjectSource");
	QTest::addColumn< set< string > >("setChangeableBy");

	set< string > setChangeableBy;
	
	QTest::newRow("empty") << (unsigned long)(0) <<
		string("") << string("") << int(0) << setChangeableBy;
	QTest::newRow("with name") << (unsigned long)(1) <<
		string("number one") << string("") << int(0) << setChangeableBy;
	QTest::newRow("with description") << (unsigned long)(2) <<
		string("number 2") << string("test case par2 \ntesting") <<
		int(NULL) << setChangeableBy;
	QTest::newRow("with source") << (unsigned long)(33) <<
		string("zzz") << string("and more \ntesting with source set") <<
		1 << setChangeableBy;
	
	setChangeableBy.insert( "me" );
	setChangeableBy.insert( "you" );
	QTest::newRow("with change by") << (unsigned long)(33) <<
		string("zzz") << string("and more \ntesting with source set") <<
		2 << setChangeableBy;
}

void tFibObjectInfo::testCostructor(){
	
	QFETCH( unsigned long, ulIdentifier );
	QFETCH( string, szNameOfFibObject );
	QFETCH( string, szDescription );
	QFETCH( int, iFibObjectSource );
	QFETCH( set< string >, setChangeableBy );
	const cFibObjectSource * pFibObjectSource = NULL;
	
	switch( iFibObjectSource ){
		//case 0: pFibObjectSource = NULL;
		case 1: pFibObjectSource = new cFibObjectSourceFibDb( 1 ); break;
		case 2: pFibObjectSource = new cFibObjectSourcePath( "~/test/test" ); break;
	}//end switch iFibObjectSource
	
	//test parameter constructor with one parameter
	cFibObjectInfo fibObjectInfoPar1( ulIdentifier );
	
	//check getName()
	QCOMPARE( fibObjectInfoPar1.getName(), string("cFibObjectInfo") );
	//check getIdentifier()
	QCOMPARE( fibObjectInfoPar1.getIdentifier(), ulIdentifier );
	//check getFibObjectName()
	QCOMPARE( fibObjectInfoPar1.getFibObjectName(), string("") );
	//check getDescription()
	QCOMPARE( fibObjectInfoPar1.getDescription(), string("") );
	//check getFibObjectSource()
	QCOMPARE( fibObjectInfoPar1.getFibObjectSource(), ((cFibObjectSource*)(NULL)) );
	//check getChangeableBy()
	QCOMPARE( fibObjectInfoPar1.getChangeableBy(), set< string >() );
	
	
	//test parameter constructor with two parameters
	cFibObjectInfo fibObjectInfoPar2( ulIdentifier, szNameOfFibObject );
	
	//check getName()
	QCOMPARE( fibObjectInfoPar2.getName(), string("cFibObjectInfo") );
	//check getIdentifier()
	QCOMPARE( fibObjectInfoPar2.getIdentifier(), ulIdentifier );
	//check getFibObjectName()
	QCOMPARE( fibObjectInfoPar2.getFibObjectName(), szNameOfFibObject );
	//check getDescription()
	QCOMPARE( fibObjectInfoPar2.getDescription(), string("") );
	//check getFibObjectSource()
	QCOMPARE( fibObjectInfoPar2.getFibObjectSource(), ((cFibObjectSource*)(NULL)) );
	//check getChangeableBy()
	QCOMPARE( fibObjectInfoPar2.getChangeableBy(), set< string >() );
	
	
	//test parameter constructor with tree parameters
	cFibObjectInfo fibObjectInfoPar3( ulIdentifier, szNameOfFibObject,
		szDescription );
	
	//check getName()
	QCOMPARE( fibObjectInfoPar3.getName(), string("cFibObjectInfo") );
	//check getIdentifier()
	QCOMPARE( fibObjectInfoPar3.getIdentifier(), ulIdentifier );
	//check getFibObjectName()
	QCOMPARE( fibObjectInfoPar3.getFibObjectName(), szNameOfFibObject );
	//check getDescription()
	QCOMPARE( fibObjectInfoPar3.getDescription(), szDescription );
	//check getFibObjectSource()
	QCOMPARE( fibObjectInfoPar3.getFibObjectSource(), ((cFibObjectSource*)(NULL)) );
	//check getChangeableBy()
	QCOMPARE( fibObjectInfoPar3.getChangeableBy(), set< string >() );
	
	
	//test parameter constructor with four parameters
	cFibObjectInfo fibObjectInfoPar4( ulIdentifier, szNameOfFibObject,
		szDescription, pFibObjectSource );
	
	//check getName()
	QCOMPARE( fibObjectInfoPar4.getName(), string("cFibObjectInfo") );
	//check getIdentifier()
	QCOMPARE( fibObjectInfoPar4.getIdentifier(), ulIdentifier );
	//check getFibObjectName()
	QCOMPARE( fibObjectInfoPar4.getFibObjectName(), szNameOfFibObject );
	//check getDescription()
	QCOMPARE( fibObjectInfoPar4.getDescription(), szDescription );
	//check getFibObjectSource()
	if ( pFibObjectSource ){
		QCOMPARE( *(fibObjectInfoPar4.getFibObjectSource()), *pFibObjectSource );
	}else{//pFibObjectSource == NULL
		QCOMPARE( fibObjectInfoPar4.getFibObjectSource(),
			((cFibObjectSource*)(NULL)) );
	}
	//check getChangeableBy()
	QCOMPARE( fibObjectInfoPar4.getChangeableBy(), set< string >() );
	
	
	//test parameter constructor with five parameters
	cFibObjectInfo fibObjectInfoPar5( ulIdentifier, szNameOfFibObject,
		szDescription, pFibObjectSource, setChangeableBy );
	
	//check getName()
	QCOMPARE( fibObjectInfoPar5.getName(), string("cFibObjectInfo") );
	//check getIdentifier()
	QCOMPARE( fibObjectInfoPar5.getIdentifier(), ulIdentifier );
	//check getFibObjectName()
	QCOMPARE( fibObjectInfoPar5.getFibObjectName(), szNameOfFibObject );
	//check getDescription()
	QCOMPARE( fibObjectInfoPar5.getDescription(), szDescription );
	//check getFibObjectSource()
	if ( pFibObjectSource ){
		QCOMPARE( *(fibObjectInfoPar5.getFibObjectSource()), *pFibObjectSource );
	}else{//pFibObjectSource == NULL
		QCOMPARE( fibObjectInfoPar5.getFibObjectSource(),
			((cFibObjectSource*)(NULL)) );
	}
	//check getChangeableBy()
	QCOMPARE( fibObjectInfoPar5.getChangeableBy(), setChangeableBy );
	
	
	//test cFibObjectInfo( const cFibObjectInfo & fibObjectInfo );
	cFibObjectInfo fibObjectInfoPar5Copy( fibObjectInfoPar5 );
	
	//check getName()
	QCOMPARE( fibObjectInfoPar5Copy.getName(), string("cFibObjectInfo") );
	//check getIdentifier()
	QCOMPARE( fibObjectInfoPar5Copy.getIdentifier(), ulIdentifier );
	//check getFibObjectName()
	QCOMPARE( fibObjectInfoPar5Copy.getFibObjectName(), szNameOfFibObject );
	//check getDescription()
	QCOMPARE( fibObjectInfoPar5Copy.getDescription(), szDescription );
	//check getFibObjectSource()
	if ( pFibObjectSource ){
		QCOMPARE( *(fibObjectInfoPar5Copy.getFibObjectSource()), *pFibObjectSource );
	}else{//pFibObjectSource == NULL
		QCOMPARE( fibObjectInfoPar5Copy.getFibObjectSource(),
			((cFibObjectSource*)(NULL)) );
	}
	//check getChangeableBy()
	QCOMPARE( fibObjectInfoPar5Copy.getChangeableBy(), setChangeableBy );
	
	
	//test cFibObjectInfo * clone() const;
	cFibObjectInfo * pFibObjectInfoPar5Clone = fibObjectInfoPar5.clone();
	
	//check getName()
	QCOMPARE( pFibObjectInfoPar5Clone->getName(), string("cFibObjectInfo") );
	//check getIdentifier()
	QCOMPARE( pFibObjectInfoPar5Clone->getIdentifier(), ulIdentifier );
	//check getFibObjectName()
	QCOMPARE( pFibObjectInfoPar5Clone->getFibObjectName(), szNameOfFibObject );
	//check getDescription()
	QCOMPARE( pFibObjectInfoPar5Clone->getDescription(), szDescription );
	//check getFibObjectSource()
	if ( pFibObjectSource ){
		QCOMPARE( *(pFibObjectInfoPar5Clone->getFibObjectSource()), *pFibObjectSource );
	}else{//pFibObjectSource == NULL
		QCOMPARE( pFibObjectInfoPar5Clone->getFibObjectSource(),
			((cFibObjectSource*)(NULL)) );
	}
	//check getChangeableBy()
	QCOMPARE( pFibObjectInfoPar5Clone->getChangeableBy(), setChangeableBy );
	
	
	if ( pFibObjectInfoPar5Clone ){
		//delete the set Fib object source
		delete pFibObjectInfoPar5Clone;
	}
	
	
	//test cFibObjectInfo( const cFibObjectInfo & fibObjectInfo );
	cFibObjectInfo fibObjectInfoPar5CopyId( ulIdentifier + 13, fibObjectInfoPar5 );
	
	//check getName()
	QCOMPARE( fibObjectInfoPar5CopyId.getName(), string("cFibObjectInfo") );
	//check getIdentifier()
	QCOMPARE( fibObjectInfoPar5CopyId.getIdentifier(), ulIdentifier + 13 );
	//check getFibObjectName()
	QCOMPARE( fibObjectInfoPar5CopyId.getFibObjectName(), szNameOfFibObject );
	//check getDescription()
	QCOMPARE( fibObjectInfoPar5CopyId.getDescription(), szDescription );
	//check getFibObjectSource()
	if ( pFibObjectSource ){
		QCOMPARE( *(fibObjectInfoPar5CopyId.getFibObjectSource()), *pFibObjectSource );
	}else{//pFibObjectSource == NULL
		QCOMPARE( fibObjectInfoPar5CopyId.getFibObjectSource(),
			((cFibObjectSource*)(NULL)) );
	}
	//check getChangeableBy()
	QCOMPARE( fibObjectInfoPar5CopyId.getChangeableBy(), setChangeableBy );
	
	
	//test cFibObjectInfo * clone() const;
	cFibObjectInfo * pFibObjectInfoPar5CloneId =
		fibObjectInfoPar5.clone( ulIdentifier + 17 );
	
	//check getName()
	QCOMPARE( pFibObjectInfoPar5CloneId->getName(), string("cFibObjectInfo") );
	//check getIdentifier()
	QCOMPARE( pFibObjectInfoPar5CloneId->getIdentifier(), ulIdentifier + 17 );
	//check getFibObjectName()
	QCOMPARE( pFibObjectInfoPar5CloneId->getFibObjectName(), szNameOfFibObject );
	//check getDescription()
	QCOMPARE( pFibObjectInfoPar5CloneId->getDescription(), szDescription );
	//check getFibObjectSource()
	if ( pFibObjectSource ){
		QCOMPARE( *(pFibObjectInfoPar5CloneId->getFibObjectSource()), *pFibObjectSource );
	}else{//pFibObjectSource == NULL
		QCOMPARE( pFibObjectInfoPar5CloneId->getFibObjectSource(),
			((cFibObjectSource*)(NULL)) );
	}
	//check getChangeableBy()
	QCOMPARE( pFibObjectInfoPar5CloneId->getChangeableBy(), setChangeableBy );
	
	
	if ( pFibObjectInfoPar5CloneId ){
		//delete the set Fib object source
		delete pFibObjectInfoPar5CloneId;
	}
	
	
	
	if ( pFibObjectSource ){
		//delete the set Fib object source
		delete pFibObjectSource;
	}
	
}



/**
 * This testcase tests the identifier methods of the cFibObjectInfo class.
 *
 * methods tested:
 * 	- unsigned long getIdentifier() const;
 * 	- void setIdentifier( const unsigned long ulNewIdentifier );
 */
void tFibObjectInfo::testIdentifier(){
	
	cFibObjectInfo * pFibObjectInfo = new cFibObjectInfo( (unsigned long)(0) );
	
	for ( unsigned long ulIteration = 0;
			ulIteration < ulNumberRandomIterations; ulIteration++ ){
	
		//generat Fib database source object with random identifier
		const unsigned long ulIdentifier = (unsigned long)(
			rand() % ulNumberRandomIterations );
		
		if ( ( rand() % 16 ) != 0 ){
			//set identifier with setIdentifier()
			pFibObjectInfo->setIdentifier( ulIdentifier );
		}else{//create new cFibObjectInfo
			if ( pFibObjectInfo ){
				delete pFibObjectInfo;
			}
			pFibObjectInfo = new cFibObjectInfo( ulIdentifier );
		}
		
		//check getIdentifier()
		QCOMPARE( pFibObjectInfo->getIdentifier(), ulIdentifier );
		//check getName()
		QCOMPARE( pFibObjectInfo->getName(), string("cFibObjectInfo") );
		//check getFibObjectName()
		QCOMPARE( pFibObjectInfo->getFibObjectName(), string("") );
		//check getDescription()
		QCOMPARE( pFibObjectInfo->getDescription(), string("") );
		//check getFibObjectSource()
		QCOMPARE( pFibObjectInfo->getFibObjectSource(),
			((cFibObjectSource*)(NULL)) );
		//check getChangeableBy()
		QCOMPARE( pFibObjectInfo->getChangeableBy(), set< string >() );
		
	}//end for random iterations
	if ( pFibObjectInfo ){
		delete pFibObjectInfo;
	}
}


/**
 * This testcase tests the name methods of the cFibObjectInfo class.
 *
 * methods tested:
 * 	- string getFibObjectName() const;
 * 	- void setFibObjectName( const string & szFibObjectName );
 */
void tFibObjectInfo::testName_data(){
	
	QTest::addColumn< string >("szNameOfFibObject");
	
	QTest::newRow("empty") << string("");
	QTest::newRow("test1") << string("test1");
	QTest::newRow("dummy name 1") << string("dummy name 1");
	QTest::newRow("kdu&\nki g< >") << string("kdu&\nki g< >");
}

void tFibObjectInfo::testName(){
	
	QFETCH( string, szNameOfFibObject );
	
	//test parameter constructor with one parameter
	cFibObjectInfo fibObjectInfo( 0, "dummy" );
	
	//check getName()
	QCOMPARE( fibObjectInfo.getName(), string("cFibObjectInfo") );
	//check getIdentifier()
	QCOMPARE( fibObjectInfo.getIdentifier(), ((unsigned long)(0)) );
	//check getFibObjectName()
	QCOMPARE( fibObjectInfo.getFibObjectName(), string("dummy") );
	//check getDescription()
	QCOMPARE( fibObjectInfo.getDescription(), string("") );
	//check getFibObjectSource()
	QCOMPARE( fibObjectInfo.getFibObjectSource(), ((cFibObjectSource*)(NULL)) );
	//check getChangeableBy()
	QCOMPARE( fibObjectInfo.getChangeableBy(), set< string >() );
	

	//use setFibObjectName()
	fibObjectInfo.setFibObjectName( szNameOfFibObject );
	
	//check getName()
	QCOMPARE( fibObjectInfo.getName(), string("cFibObjectInfo") );
	//check getIdentifier()
	QCOMPARE( fibObjectInfo.getIdentifier(), ((unsigned long)(0)) );
	//check getFibObjectName()
	QCOMPARE( fibObjectInfo.getFibObjectName(), szNameOfFibObject );
	//check getDescription()
	QCOMPARE( fibObjectInfo.getDescription(), string("") );
	//check getFibObjectSource()
	QCOMPARE( fibObjectInfo.getFibObjectSource(), ((cFibObjectSource*)(NULL)) );
	//check getChangeableBy()
	QCOMPARE( fibObjectInfo.getChangeableBy(), set< string >() );
	
}




/**
 * This testcase tests the description methods of the cFibObjectInfo class.
 *
 * methods tested:
 * 	- string getDescription() const;
 * 	- void setDescription( const string & szFibObjectDescription );
 */
void tFibObjectInfo::testDescription_data(){
	
	QTest::addColumn< string >("szDescriptionOfFibObject");
	
	QTest::newRow("empty") << string("");
	QTest::newRow("test1") << string("test1");
	QTest::newRow("dummy name 1") << string("dummy name 1");
	QTest::newRow("kdu&\nki g< >") << string("kdu&\nki g< >");
}

void tFibObjectInfo::testDescription(){
	
	QFETCH( string, szDescriptionOfFibObject );
	
	//test parameter constructor with one parameter
	cFibObjectInfo fibObjectInfo( 0, "dummy", "description" );
	
	//check getName()
	QCOMPARE( fibObjectInfo.getName(), string("cFibObjectInfo") );
	//check getIdentifier()
	QCOMPARE( fibObjectInfo.getIdentifier(), ((unsigned long)(0)) );
	//check getFibObjectName()
	QCOMPARE( fibObjectInfo.getFibObjectName(), string("dummy") );
	//check getDescription()
	QCOMPARE( fibObjectInfo.getDescription(), string("description") );
	//check getFibObjectSource()
	QCOMPARE( fibObjectInfo.getFibObjectSource(), ((cFibObjectSource*)(NULL)) );
	//check getChangeableBy()
	QCOMPARE( fibObjectInfo.getChangeableBy(), set< string >() );
	

	//use setFibObjectName()
	fibObjectInfo.setDescription( szDescriptionOfFibObject );
	
	//check getName()
	QCOMPARE( fibObjectInfo.getName(), string("cFibObjectInfo") );
	//check getIdentifier()
	QCOMPARE( fibObjectInfo.getIdentifier(), ((unsigned long)(0)) );
	//check getFibObjectName()
	QCOMPARE( fibObjectInfo.getFibObjectName(), string("dummy") );
	//check getDescription()
	QCOMPARE( fibObjectInfo.getDescription(), szDescriptionOfFibObject );
	//check getFibObjectSource()
	QCOMPARE( fibObjectInfo.getFibObjectSource(), ((cFibObjectSource*)(NULL)) );
	//check getChangeableBy()
	QCOMPARE( fibObjectInfo.getChangeableBy(), set< string >() );
	
}



/**
 * This testcase tests the Fib object source methods of the cFibObjectInfo class.
 *
 * methods tested:
 * 	- cFibObjectSource * getFibObjectSource();
 * 	- const cFibObjectSource * getFibObjectSource() const;
 * 	- bool setFibObjectSource( const cFibObjectSource * pInFibObjectSource );
 */
void tFibObjectInfo::testFibObjectSource(){
	
	//test parameter constructor with one parameter
	cFibObjectInfo fibObjectInfo( 0, "dummy", "description" );
	
	cFibObjectSource * pFibObjectSource = NULL;
	//check getName()
	QCOMPARE( fibObjectInfo.getName(), string("cFibObjectInfo") );
	//check getIdentifier()
	QCOMPARE( fibObjectInfo.getIdentifier(), ((unsigned long)(0)) );
	//check getFibObjectName()
	QCOMPARE( fibObjectInfo.getFibObjectName(), string("dummy") );
	//check getDescription()
	QCOMPARE( fibObjectInfo.getDescription(), string("description") );
	//check getFibObjectSource()
	if ( pFibObjectSource ){
		QCOMPARE( *(fibObjectInfo.getFibObjectSource()), *pFibObjectSource );
		QCOMPARE( *(((const cFibObjectInfo*)(&fibObjectInfo))->getFibObjectSource()),
			*((const cFibObjectSource*)(pFibObjectSource)) );
	}else{//pFibObjectSource == NULL
		QCOMPARE( fibObjectInfo.getFibObjectSource(),
			((const cFibObjectSource*)(NULL)) );
		QCOMPARE( (((const cFibObjectInfo*)(&fibObjectInfo))->getFibObjectSource()),
			((const cFibObjectSource*)(NULL)) );
	}
	//check getChangeableBy()
	QCOMPARE( fibObjectInfo.getChangeableBy(), set< string >() );
	
	pFibObjectSource = new cFibObjectSourceFibDb( 1 );
	
	//use setFibObjectName()
	fibObjectInfo.setFibObjectSource( pFibObjectSource );
	
	//check getName()
	QCOMPARE( fibObjectInfo.getName(), string("cFibObjectInfo") );
	//check getIdentifier()
	QCOMPARE( fibObjectInfo.getIdentifier(), ((unsigned long)(0)) );
	//check getFibObjectName()
	QCOMPARE( fibObjectInfo.getFibObjectName(), string("dummy") );
	//check getDescription()
	QCOMPARE( fibObjectInfo.getDescription(), string("description") );
	//check getFibObjectSource()
	if ( pFibObjectSource ){
		QCOMPARE( *(fibObjectInfo.getFibObjectSource()), *pFibObjectSource );
		QCOMPARE( *((((const cFibObjectInfo*)(&fibObjectInfo))->getFibObjectSource())),
			*((const cFibObjectSource*)(pFibObjectSource)) );
	}else{//pFibObjectSource == NULL
		QCOMPARE( fibObjectInfo.getFibObjectSource(),
			((const cFibObjectSource*)(NULL)) );
		QCOMPARE( (((const cFibObjectInfo*)(&fibObjectInfo))->getFibObjectSource()),
			((const cFibObjectSource*)(NULL)) );
	}
	//check getChangeableBy()
	QCOMPARE( fibObjectInfo.getChangeableBy(), set< string >() );
	
	
	if ( pFibObjectSource ){
		//delete the set Fib object source
		delete pFibObjectSource;
	}
	pFibObjectSource = new cFibObjectSourcePath( "~/test/test" );
	
	//use setFibObjectName()
	fibObjectInfo.setFibObjectSource( pFibObjectSource );
	
	//check getName()
	QCOMPARE( fibObjectInfo.getName(), string("cFibObjectInfo") );
	//check getIdentifier()
	QCOMPARE( fibObjectInfo.getIdentifier(), ((unsigned long)(0)) );
	//check getFibObjectName()
	QCOMPARE( fibObjectInfo.getFibObjectName(), string("dummy") );
	//check getDescription()
	QCOMPARE( fibObjectInfo.getDescription(), string("description") );
	//check getFibObjectSource()
	if ( pFibObjectSource ){
		QCOMPARE( *(fibObjectInfo.getFibObjectSource()), *pFibObjectSource );
		QCOMPARE( *((((const cFibObjectInfo*)(&fibObjectInfo))->getFibObjectSource())),
			*((const cFibObjectSource*)(pFibObjectSource)) );
	}else{//pFibObjectSource == NULL
		QCOMPARE( fibObjectInfo.getFibObjectSource(),
			((const cFibObjectSource*)(NULL)) );
		QCOMPARE( (((const cFibObjectInfo*)(&fibObjectInfo))->getFibObjectSource()),
			((const cFibObjectSource*)(NULL)) );
	}
	//check getChangeableBy()
	QCOMPARE( fibObjectInfo.getChangeableBy(), set< string >() );
	
	if ( pFibObjectSource ){
		//delete the set Fib object source
		delete pFibObjectSource;
	}
	
}


/**
 * This testcase tests the connection to methods of the cFibObjectInfo class.
 *
 * methods tested:
 * 	- map< string, set< unsigned long > > getConnectedToMap() const;
 * 	- set< unsigned long > getConnectedFor( const string & szKey ) const;
 * 	- void addConnectionTo( const string & szKey, const unsigned long ulConnectedId );
 * 	- void addConnectionTo( const string & szKey, const set< unsigned long > & setNotConnectedIds );
 * 	- bool removeConnectionTo( const string & szKey, const unsigned long ulConnectedId );
 * 	- unsigned int removeConnectionTo( const string & szKey, const set< unsigned long > & setNotConnectedIds );
 */
void tFibObjectInfo::testConnectionTo(){
	
	unsigned long ulIdentifier = 0;
	cFibObjectInfo * pFibObjectInfo = new cFibObjectInfo( ulIdentifier );
	
	map< string, set< unsigned long > > mapCorrectConnections;
	
	vector< string > vecPossibleConnectionTypes;
	vecPossibleConnectionTypes.push_back( "" );
	vecPossibleConnectionTypes.push_back( "type" );
	vecPossibleConnectionTypes.push_back( "unknown" );
	vecPossibleConnectionTypes.push_back( "basic" );
	vecPossibleConnectionTypes.push_back( "isPoint" );
	vecPossibleConnectionTypes.push_back( "color" );
	vecPossibleConnectionTypes.push_back( "size" );
	vecPossibleConnectionTypes.push_back( "style" );
	vecPossibleConnectionTypes.push_back( "more \n text" );
	vecPossibleConnectionTypes.push_back( "typeX::pp+!\"§$%&/()=?><" );
	
	for ( unsigned long ulIteration = 0;
			ulIteration < ulNumberRandomIterations; ulIteration++ ){
		
		if ( ( rand() % 64 ) != 0 ){
			
			string szKey = "";
			if ( mapCorrectConnections.empty() || ( rand() % 2 ) ){
				//change random connection
				szKey = vecPossibleConnectionTypes[
					rand() % vecPossibleConnectionTypes.size() ];
			}else{//change existing connection
				map< string, set< unsigned long > >::const_iterator
					itrChoosenKey = mapCorrectConnections.begin();
				for ( unsigned int iChoosenKey = rand() % mapCorrectConnections.size();
						( 0 < iChoosenKey ); iChoosenKey--, itrChoosenKey++ ){
					//nothing to do
				}
				szKey = itrChoosenKey->first;
			}
			if ( rand() % 2 ){
				/*use one identifier:
					- void addConnectionTo( const string & szKey, const unsigned long ulConnectedId );
					- bool removeConnectionTo( const string & szKey, const unsigned long ulConnectedId );
				 */
				//choose identifier
				unsigned long ulChoosenIdentifier = rand() % ulNumberRandomIterations;
				if ( rand() % 2 ){
					//try to choose existing identifier for the key
					map< string, set< unsigned long > >::const_iterator
						itrChoosenKey = mapCorrectConnections.find( szKey );
					if ( ( itrChoosenKey != mapCorrectConnections.end() ) &&
							( ! itrChoosenKey->second.empty() ) ){
						//key exists + identifiers for key exists
						set< unsigned long >::const_iterator
							itrChoosenId =  itrChoosenKey->second.begin();
						for ( unsigned int uiChoosenId = itrChoosenKey->second.size();
								0 < uiChoosenId; uiChoosenId--, itrChoosenId++ ){
							//nothing to do
						}
						ulChoosenIdentifier = *itrChoosenId;
					}
				}
				if ( rand() % 2 ){
					//void addConnectionTo( const string & szKey, const unsigned long ulConnectedId );
					pFibObjectInfo->addConnectionTo( szKey, ulChoosenIdentifier );
					
					mapCorrectConnections[ szKey ].insert( ulChoosenIdentifier );
					
				}else{//bool removeConnectionTo( const string & szKey, const unsigned long ulConnectedId );
					bool bConnectionExists = false;
					map< string, set< unsigned long > >::iterator
						itrConnection = mapCorrectConnections.find( szKey );
						
					if ( itrConnection != mapCorrectConnections.end() ){
						bConnectionExists = ( 0 < itrConnection->second.erase(
							ulChoosenIdentifier ) );
						
						if ( itrConnection->second.empty() ){
							//no entries for connection type -> remove connection type
							mapCorrectConnections.erase( itrConnection );
						}
					}
					
					QCOMPARE( pFibObjectInfo->removeConnectionTo(
						szKey, ulChoosenIdentifier ), bConnectionExists );
				}
				
			}else{/*use set of identifier:
				- void addConnectionTo( const string & szKey, const set< unsigned long > & setNotConnectedIds );
				- unsigned int removeConnectionTo( const string & szKey, const set< unsigned long > & setNotConnectedIds );
				*/
				//choose identifiers
				set< unsigned long > setChoosenIdentifiers;
				
				map< string, set< unsigned long > >::iterator
					itrChoosenKey = mapCorrectConnections.find( szKey );
				
				for ( unsigned int uiIdentifiersToChoose =
						rand() % ulNumberRandomIterations;
						( 0 < uiIdentifiersToChoose ); uiIdentifiersToChoose-- ){
					
					unsigned long ulChoosenIdentifier = rand() % ulNumberRandomIterations;
					//try to choose existing identifier for the key
					if ( ( rand() % 2 != 0 ) &&
							( itrChoosenKey != mapCorrectConnections.end() ) &&
							( ! itrChoosenKey->second.empty() ) ){
						//key exists + identifiers for key exists
						set< unsigned long >::const_iterator
							itrChoosenId =  itrChoosenKey->second.begin();
						for ( unsigned int uiChoosenId = itrChoosenKey->second.size();
								0 < uiChoosenId; uiChoosenId--, itrChoosenId++ ){
							//nothing to do
						}
						ulChoosenIdentifier = *itrChoosenId;
					}
					setChoosenIdentifiers.insert( ulChoosenIdentifier );
				}
				
				if ( rand() % 2 ){
					//void addConnectionTo( const string & szKey, const unsigned long ulConnectedId );
					pFibObjectInfo->addConnectionTo( szKey, setChoosenIdentifiers );
					
					mapCorrectConnections[ szKey ].insert(
						setChoosenIdentifiers.begin(), setChoosenIdentifiers.end() );
					
				}else{//bool removeConnectionTo( const string & szKey, const unsigned long ulConnectedId );
					unsigned int uiIdentifiersToRemove = 0;
					if ( itrChoosenKey != mapCorrectConnections.end() ){
						//existing key choosen
						for ( set< unsigned long >::const_iterator
								itrIdentifier = setChoosenIdentifiers.begin();
								itrIdentifier != setChoosenIdentifiers.end();
								itrIdentifier++ ){
							
							uiIdentifiersToRemove +=
								itrChoosenKey->second.erase( (*itrIdentifier) );
						}
						
						if ( itrChoosenKey->second.empty() ){
							//no entries for connection type -> remove connection type
							mapCorrectConnections.erase( itrChoosenKey );
						}
					}//end if existing key choosen
					
					QCOMPARE( pFibObjectInfo->removeConnectionTo(
						szKey, setChoosenIdentifiers ), uiIdentifiersToRemove );
				}
			}
			
		}else{//create new cFibObjectInfo
			if ( pFibObjectInfo ){
				delete pFibObjectInfo;
			}
			ulIdentifier = (unsigned long)( rand() % ulNumberRandomIterations );
			pFibObjectInfo = new cFibObjectInfo( ulIdentifier );
			
			mapCorrectConnections.clear();
		}
		
		const map< string, set< unsigned long > >
			mapReturnedConnections = pFibObjectInfo->getConnectedToMap();
		
		if ( mapReturnedConnections.size() != mapCorrectConnections.size() ){
			QFAIL( ((QString("Error: Number of entries in the connection map not correct (retuned: %1; correct: %2).")).arg(
					mapReturnedConnections.size() ).arg(
					mapCorrectConnections.size() )).toStdString().c_str() );
		}
		map< string, set< unsigned long > >::const_iterator
			itrCorrectConnection = mapCorrectConnections.begin();
		for ( map< string, set< unsigned long > >::const_iterator
				itrReturnedConnection = mapReturnedConnections.begin();
				itrReturnedConnection != mapReturnedConnections.end();
				itrReturnedConnection++, itrCorrectConnection++ ){
			//test the key
			if ( itrReturnedConnection->first != itrCorrectConnection->first ){
				QWARN( ((QString("Error: The returned key \"%1\" not equal to the correct key \"%2\".")).arg(
					QString(itrReturnedConnection->first.c_str()) ).arg(
					QString(itrCorrectConnection->first.c_str()) )).toStdString().c_str() );
				continue;
			}
			if ( itrReturnedConnection->second.size() !=
					itrCorrectConnection->second.size() ){
				QWARN( ((QString("Error: The number of identifer for the %1 key is %2 but should be %3 .")).arg( itrReturnedConnection->first.c_str() ).arg(
					itrReturnedConnection->second.size() ).arg(
					itrCorrectConnection->second.size() )).toStdString().c_str() );
			}
			if ( itrReturnedConnection->second !=
					itrCorrectConnection->second ){
				QWARN( ((QString("Error: The identifers for the %1 key are not equal.")).arg( itrReturnedConnection->first.c_str() )).toStdString().c_str() );
			}
		}
		
		//check getConnectedToMap()
		QCOMPARE( mapReturnedConnections, mapCorrectConnections );
		
		//check getConnectedFor()
		for ( map< string, set< unsigned long > >::const_iterator
				itrConnection = mapCorrectConnections.begin();
				itrConnection != mapCorrectConnections.end(); itrConnection++ ){
			
			QCOMPARE( pFibObjectInfo->getConnectedFor( itrConnection->first ),
				itrConnection->second );
		}
		
		//check getIdentifier()
		QCOMPARE( pFibObjectInfo->getIdentifier(), ulIdentifier );
		//check getName()
		QCOMPARE( pFibObjectInfo->getName(), string("cFibObjectInfo") );
		//check getFibObjectName()
		QCOMPARE( pFibObjectInfo->getFibObjectName(), string("") );
		//check getDescription()
		QCOMPARE( pFibObjectInfo->getDescription(), string("") );
		//check getFibObjectSource()
		QCOMPARE( pFibObjectInfo->getFibObjectSource(),
			((cFibObjectSource*)(NULL)) );
		//check getChangeableBy()
		QCOMPARE( pFibObjectInfo->getChangeableBy(), set< string >() );
		
	}//end for random iterations
	if ( pFibObjectInfo ){
		delete pFibObjectInfo;
	}
}


/**
 * This testcase tests the time used methods of the cFibObjectInfo class.
 *
 * methods tested:
 * 	-vector< pair< time_t, unsigned long > > getLastUsedTimes() const;
 * 	- void setFibObjectUsed( time_t timestamp = 0 );
 */
void tFibObjectInfo::testUsedTimes(){
	
	const unsigned int uiMaxTimeStamps = 9;
	
	unsigned long ulIdentifier = 123;
	cFibObjectInfo * pFibObjectInfo = new cFibObjectInfo( ulIdentifier );
	
	//check getLastUsedTimes()
	QCOMPARE( pFibObjectInfo->getLastUsedTimes().empty(), true );
	
	//check getIdentifier()
	QCOMPARE( pFibObjectInfo->getIdentifier(), ulIdentifier );
	//check getName()
	QCOMPARE( pFibObjectInfo->getName(), string("cFibObjectInfo") );
	//check getFibObjectName()
	QCOMPARE( pFibObjectInfo->getFibObjectName(), string("") );
	//check getDescription()
	QCOMPARE( pFibObjectInfo->getDescription(), string("") );
	//check getFibObjectSource()
	QCOMPARE( pFibObjectInfo->getFibObjectSource(),
		((cFibObjectSource*)(NULL)) );
	//check getChangeableBy()
	QCOMPARE( pFibObjectInfo->getChangeableBy(), set< string >() );
	
	
	time_t tmlastUsed = time( NULL );
	
	for ( unsigned long ulIteration = 0;
			ulIteration < ( 1024 + ulNumberRandomIterations ); ulIteration++ ){
		//generate random time stamp
		tmlastUsed += rand() % 64;
		//set generated time stamp
		pFibObjectInfo->setFibObjectUsed( tmlastUsed );
		
		const vector< pair< time_t, unsigned long > >
			veclastUsedTimes = pFibObjectInfo->getLastUsedTimes();
		
		if ( veclastUsedTimes.empty() ){
			QFAIL( "Error: No timestamps returned, but some set." );
		}
		
		unsigned long ulMinEntries = 0;
		unsigned long ulMaxEntries = 1;
		
		const unsigned int uiNumberOfTimestamps = veclastUsedTimes.size();
		vector< pair< time_t, unsigned long > >::const_iterator
			itrTimeStamp = veclastUsedTimes.begin();
		time_t tmlastTimeStamp = itrTimeStamp->first;
		
		for ( unsigned int uiActualTimeStamp = 1;
				( uiActualTimeStamp <= uiNumberOfTimestamps ) &&
					( itrTimeStamp != veclastUsedTimes.end() );
				uiActualTimeStamp++, itrTimeStamp++ ){
			//check number of timestamps in intervall
			if ( itrTimeStamp->second < ulMinEntries ){
				QFAIL( ((QString("Error: The actual %1 number of timestamps (%2) is to low (lower %3).")).arg( uiActualTimeStamp ).arg(
					itrTimeStamp->second ).arg( ulMinEntries )).toStdString().c_str() );
			}
			if ( uiActualTimeStamp < uiNumberOfTimestamps ){
				if ( ulMaxEntries < itrTimeStamp->second ){
					QFAIL( ((QString("Error: The actual %1 number of timestamps (%1) is to great (lower %2).")).arg( uiActualTimeStamp ).arg(
						itrTimeStamp->second ).arg( ulMaxEntries )).toStdString().c_str() );
				}
			}//else the last intervall can contain infinit timestamps
			//check order of time stamps
			if ( tmlastTimeStamp < itrTimeStamp->first ){
				QFAIL( "Error: The next timestamp entry is not before (or equal) the last timestamp entry." );
			}
			
			ulMinEntries = ulMaxEntries;
			ulMaxEntries = ulMaxEntries * 2;
			
			tmlastTimeStamp = itrTimeStamp->first;
		}//check all returned timestamps
		if ( uiMaxTimeStamps < uiNumberOfTimestamps ){
			QFAIL( "Error: There where more than maximum number of timestamps returned." );
		}
		
		//check getIdentifier()
		QCOMPARE( pFibObjectInfo->getIdentifier(), ulIdentifier );
		//check getName()
		QCOMPARE( pFibObjectInfo->getName(), string("cFibObjectInfo") );
		//check getFibObjectName()
		QCOMPARE( pFibObjectInfo->getFibObjectName(), string("") );
		//check getDescription()
		QCOMPARE( pFibObjectInfo->getDescription(), string("") );
		//check getFibObjectSource()
		QCOMPARE( pFibObjectInfo->getFibObjectSource(),
			((cFibObjectSource*)(NULL)) );
		//check getChangeableBy()
		QCOMPARE( pFibObjectInfo->getChangeableBy(), set< string >() );
		
	}//end for random iterations
	
	//set some random timestamps
	unsigned long ulRandIntervalle = time( NULL ) * 2 + 10000;
	for ( unsigned long ulIteration = 0;
			ulIteration < ( 1024 + ulNumberRandomIterations ); ulIteration++ ){
		//generate random time stamp
		tmlastUsed = rand() % ulRandIntervalle;
		//set generated time stamp
		pFibObjectInfo->setFibObjectUsed( tmlastUsed );
		
		const vector< pair< time_t, unsigned long > >
			veclastUsedTimes = pFibObjectInfo->getLastUsedTimes();
		
		if ( veclastUsedTimes.empty() ){
			QFAIL( "Error: No timestamps returned, but some set." );
		}
		unsigned long ulMaxEntries = 1;
		
		const unsigned int uiNumberOfTimestamps = veclastUsedTimes.size();
		vector< pair< time_t, unsigned long > >::const_iterator
			itrTimeStamp = veclastUsedTimes.begin();
		time_t tmlastTimeStamp = itrTimeStamp->first;
		
		for ( unsigned int uiActualTimeStamp = 1;
				( uiActualTimeStamp <= uiNumberOfTimestamps ) &&
					( itrTimeStamp != veclastUsedTimes.end() );
				uiActualTimeStamp++, itrTimeStamp++ ){
			//check number of timestamps in intervall
			//Note: Can't garante minimum number of entries for random
			if ( uiActualTimeStamp < uiNumberOfTimestamps ){
				if ( ulMaxEntries < itrTimeStamp->second ){
					QFAIL( ((QString("Error: The actual %1 number of timestamps (%1) is to great (lower %2).")).arg( uiActualTimeStamp ).arg(
						itrTimeStamp->second ).arg( ulMaxEntries )).toStdString().c_str() );
				}
			}//else the last intervall can contain infinit timestamps
			//check order of time stamps
			if ( tmlastTimeStamp < itrTimeStamp->first ){
				QFAIL( "Error: The next timestamp entry is not before (or equal) the last timestamp entry." );
			}
			
			ulMaxEntries = ulMaxEntries * 2;
			
			tmlastTimeStamp = itrTimeStamp->first;
		}//check all returned timestamps
		if ( uiMaxTimeStamps < uiNumberOfTimestamps ){
			QFAIL( "Error: There where more than maximum number of timestamps returned." );
		}
		
		//check getIdentifier()
		QCOMPARE( pFibObjectInfo->getIdentifier(), ulIdentifier );
		//check getName()
		QCOMPARE( pFibObjectInfo->getName(), string("cFibObjectInfo") );
		//check getFibObjectName()
		QCOMPARE( pFibObjectInfo->getFibObjectName(), string("") );
		//check getDescription()
		QCOMPARE( pFibObjectInfo->getDescription(), string("") );
		//check getFibObjectSource()
		QCOMPARE( pFibObjectInfo->getFibObjectSource(),
			((cFibObjectSource*)(NULL)) );
		//check getChangeableBy()
		QCOMPARE( pFibObjectInfo->getChangeableBy(), set< string >() );
		
	}//end for random iterations
	
	//test actual timestamp setFibObjectUsed()
	ulIdentifier = 546;
	cFibObjectInfo fibObjectInfoActualTime( ulIdentifier );
	const time_t tmActualTimeStamp = time( NULL );
	
	fibObjectInfoActualTime.setFibObjectUsed();
	
	const vector< pair< time_t, unsigned long > >
		veclastUsedTimes = fibObjectInfoActualTime.getLastUsedTimes();
	if ( veclastUsedTimes.size() != 1 ){
		QFAIL( "Error: After setting just actual time not just one entry exists." );
	}else{
		if ( ( veclastUsedTimes[ 0 ].first < tmActualTimeStamp ) ||
				( ( tmActualTimeStamp + 10 ) < veclastUsedTimes[ 0 ].first ) ){
			QFAIL( "Error: Actual time not correctly set." );
		}
		if ( veclastUsedTimes[ 0 ].second != 1  ){
			QFAIL( ((QString("Error: After setting just actual time not just one timestamp exists, but %1 .")).arg(
				veclastUsedTimes[ 0 ].second )).toStdString().c_str() );
		}
	}
	
	//check getIdentifier()
	QCOMPARE( fibObjectInfoActualTime.getIdentifier(), ulIdentifier );
	//check getName()
	QCOMPARE( fibObjectInfoActualTime.getName(), string("cFibObjectInfo") );
	//check getFibObjectName()
	QCOMPARE( fibObjectInfoActualTime.getFibObjectName(), string("") );
	//check getDescription()
	QCOMPARE( fibObjectInfoActualTime.getDescription(), string("") );
	//check getFibObjectSource()
	QCOMPARE( fibObjectInfoActualTime.getFibObjectSource(),
		((cFibObjectSource*)(NULL)) );
	//check getChangeableBy()
	QCOMPARE( fibObjectInfoActualTime.getChangeableBy(), set< string >() );

	
	if ( pFibObjectInfo ){
		delete pFibObjectInfo;
	}
}


/**
 * This testcase tests the "user can change" methods of the cFibObjectInfo class.
 *
 * methods tested:
 * 	- set< string > getChangeableBy() const;
 * 	- bool canChange( const string & szUser ) const;
 * 	- void addUserWhichCanChange( const string & szUser );
 * 	- bool removeUserWhichCanChange( const string & szUser );
 */
void tFibObjectInfo::testUserCanChange(){
	
	unsigned long ulIdentifier = 0;
	cFibObjectInfo * pFibObjectInfo = new cFibObjectInfo( ulIdentifier );
	const cFibObjectInfo * pFibObjectInfoConst = pFibObjectInfo;
	
	set< string > setCorrectUsers;
	
	vector< string > vecPossibleUsers;
	vecPossibleUsers.push_back( "" );
	vecPossibleUsers.push_back( "all" );
	vecPossibleUsers.push_back( "unknown" );
	vecPossibleUsers.push_back( "hugo" );
	vecPossibleUsers.push_back( "biokom" );
	vecPossibleUsers.push_back( "color" );
	vecPossibleUsers.push_back( "size" );
	vecPossibleUsers.push_back( "style" );
	vecPossibleUsers.push_back( "more \n text" );
	vecPossibleUsers.push_back( "typeX::pp+!\"§$%&/()=?><" );
	//if true all user can change ("all" is in the user can change set)
	bool bAllCanChange = false;
	
	for ( unsigned long ulIteration = 0;
			ulIteration < ulNumberRandomIterations; ulIteration++ ){
		
		if ( ( rand() % 64 ) != 0 ){
			
			string szUser = "";
			if ( setCorrectUsers.empty() || ( rand() % 2 ) ){
				//change random connection
				szUser = vecPossibleUsers[
					rand() % vecPossibleUsers.size() ];
			}else{//change existing connection
				set< string>::const_iterator itrChoosenKey = setCorrectUsers.begin();
				for ( unsigned int iChoosenKey = rand() % setCorrectUsers.size();
						( 0 < iChoosenKey ); iChoosenKey--, itrChoosenKey++ ){
					//nothing to do
				}
				szUser = (*itrChoosenKey);
			}
			/*use one identifier:
				-void addUserWhichCanChange( const string & szUser );
				-bool removeUserWhichCanChange( const string & szUser );
			 */
			if ( rand() % 2 ){
				//void addUserWhichCanChange( const string & szUser );
				pFibObjectInfo->addUserWhichCanChange( szUser );
				
				setCorrectUsers.insert( szUser );
				if ( szUser == "all" ){
					bAllCanChange = true;
				}
				
			}else{//bool removeUserWhichCanChange( const string & szUser );
				bool bUserExists = ( 0 < setCorrectUsers.erase( szUser ) );
				
				QCOMPARE( pFibObjectInfo->removeUserWhichCanChange( szUser ),
					bUserExists );
				
				if ( szUser == "all" ){
					bAllCanChange = false;
				}
			}
		}else{//create new cFibObjectInfo
			if ( pFibObjectInfo ){
				delete pFibObjectInfo;
			}
			ulIdentifier = (unsigned long)( rand() % ulNumberRandomIterations );
			pFibObjectInfo = new cFibObjectInfo( ulIdentifier );
			pFibObjectInfoConst = pFibObjectInfo;
			
			setCorrectUsers.clear();
			bAllCanChange = false;
		}
		//set< string > getChangeableBy() const;
		const set< string > setReturnedUsers = pFibObjectInfoConst->getChangeableBy();
		
		if ( setReturnedUsers.size() != setCorrectUsers.size() ){
			QFAIL( ((QString("Error: Number of entries in the\"user can change\" not correct (retuned: %1; correct: %2).")).arg(
					setReturnedUsers.size() ).arg(
					setCorrectUsers.size() )).toStdString().c_str() );
		}
		
		//check canChange()
		for ( vector< string >::const_iterator
				itrPossibleUser = vecPossibleUsers.begin();
				itrPossibleUser != vecPossibleUsers.end(); itrPossibleUser++ ){
			
			if ( setCorrectUsers.find( *itrPossibleUser ) == setCorrectUsers.end() ){
				//user can not change
				if ( ! bAllCanChange ){
					QCOMPARE( pFibObjectInfo->canChange( *itrPossibleUser ), false );
				}else{//all user can change
					QCOMPARE( pFibObjectInfo->canChange( *itrPossibleUser ), true );
				}
				if ( setReturnedUsers.find( *itrPossibleUser ) != setReturnedUsers.end() ){
					QFAIL( ((QString("Error: The user \"%1\" can not change, but returned as can change.")).arg( QString( itrPossibleUser->c_str() ) )
						).toStdString().c_str() );
				}
			}else{//user can change
				QCOMPARE( pFibObjectInfo->canChange( *itrPossibleUser ), true );
				
				if ( setReturnedUsers.find( *itrPossibleUser ) == setReturnedUsers.end() ){
					QFAIL( ((QString("Error: The user \"%1\" can change, but not returned as can change.")).arg( QString( itrPossibleUser->c_str() ) )
						).toStdString().c_str() );
				}
			}
		}
		
		//check getIdentifier()
		QCOMPARE( pFibObjectInfo->getIdentifier(), ulIdentifier );
		//check getName()
		QCOMPARE( pFibObjectInfo->getName(), string("cFibObjectInfo") );
		//check getFibObjectName()
		QCOMPARE( pFibObjectInfo->getFibObjectName(), string("") );
		//check getDescription()
		QCOMPARE( pFibObjectInfo->getDescription(), string("") );
		//check getFibObjectSource()
		QCOMPARE( pFibObjectInfo->getFibObjectSource(),
			((cFibObjectSource*)(NULL)) );
		
	}//end for random iterations
	if ( pFibObjectInfo ){
		delete pFibObjectInfo;
	}
}



/**
 * This functions tests the store and restore Fib object info methods.
 *
 * methods tested:
 * 	- cFibObjectInfo( istream & stream, int * iOutStatus=NULL );
 * 	- cFibObjectInfo( const TiXmlNode * pXmlNode, int * iOutStatus=NULL );
 * 	- bool store( ostream & stream );
 * 	- int restoreFibObjectInfo( istream & stream );
 * 	- int restoreFibObjectInfo( const TiXmlNode * pXmlNode );
 * 	- static cFibObjectInfo * restore( istream & stream, int * iOutStatus=NULL );
 * 	- static cFibObjectInfo * restore( const TiXmlNode * pXmlNode, int * iOutStatus=NULL );
 */
void tFibObjectInfo::testReStore_data(){
	
	QTest::addColumn< unsigned long >("ulIdentifier");
	QTest::addColumn< string >("szName");
	QTest::addColumn< string >("szDescription");
	QTest::addColumn< int >("iFibObjectSource");
	QTest::addColumn< set< string > >("setChangeableBy");
	QTest::addColumn< map< string, set< unsigned long > > >("mapConnectedTo");
	QTest::addColumn< list< time_t > >("liLastUsed");
	QTest::addColumn< set< string > >("setCategories");

	set< string > setChangeableBy;
	set< string > setCategories;//TODO
	map< string, set< unsigned long > > mapConnectedTo;
	list< time_t > liLastUsed;
	
	QTest::newRow("empty") << (unsigned long)(0) <<
		string("") << string("") << int(0) << setChangeableBy<<
		mapConnectedTo << liLastUsed<<setCategories;
	QTest::newRow("id1") << (unsigned long)(1) <<
		string("id1") << string("Fib object with identifier 1") <<
		int(0) << setChangeableBy<<
		mapConnectedTo << liLastUsed<<setCategories;
	QTest::newRow("id2") << (unsigned long)(2) <<
		string("incl. source") << string("Fib object with Fib source object") <<
		int(1) << setChangeableBy<<
		mapConnectedTo << liLastUsed<<setCategories;
	
	setChangeableBy.insert("BioKom");
	setChangeableBy.insert("Betti");
	QTest::newRow("id3") << (unsigned long)(3) <<
		string("user") << string("Fib object with users given which can use it") <<
		int(1) << setChangeableBy<<
		mapConnectedTo << liLastUsed<<setCategories;
	
	setChangeableBy.insert("all users i like");
	mapConnectedTo["type"].insert( 3 );
	mapConnectedTo["type"].insert( 1 );
	mapConnectedTo["size"].insert( 1 );
	mapConnectedTo["size"].insert( 444 );
	QTest::newRow("id4") << (unsigned long)(4) <<
		string("connections") <<
		string("Fib object with connections to other Fib objects given") <<
		int(2) << setChangeableBy<<
		mapConnectedTo << liLastUsed<<setCategories;
	
	
	mapConnectedTo["type"].insert( 15 );
	mapConnectedTo["size of known"].insert( 6 );
	liLastUsed.push_back( 10000 );
	liLastUsed.push_back( 10001 );
	liLastUsed.push_back( 10001 );
	liLastUsed.push_back( 10020 );
	liLastUsed.push_back( 10030 );
	liLastUsed.push_back( 10041 );
	liLastUsed.push_back( 10042 );
	QTest::newRow("id5") << (unsigned long)(5) <<
		string("last used") <<
		string("Fib object with last used times given") <<
		int(2) << setChangeableBy<<
		mapConnectedTo << liLastUsed<<setCategories;
	
	setChangeableBy.insert("specials!§$%/()=?`1234567890ß´+#äüö-.,|");
	mapConnectedTo["specials!§$%/()=?`1234567890ß´+#äüö-.,|"].insert( 15 );
	liLastUsed.push_back( 10100 );
	liLastUsed.push_back( 10123 );
	liLastUsed.push_back( 10124 );
	liLastUsed.push_back( 10144 );
	liLastUsed.push_back( 10155 );
	liLastUsed.push_back( 10166 );
	liLastUsed.push_back( 10177 );
	QTest::newRow("id6") << (unsigned long)(6) <<
		string("special chars!§$%/()=?1234567890ß+#äüö-.,|") <<
		string("Fib object with used specials chars!§$%/()=?`1234567890ß´+#äüö-.,|") <<
		int(1) << setChangeableBy<<
		mapConnectedTo << liLastUsed<<setCategories;
	
	setCategories.insert("isObject");
	setCategories.insert("isPerson");
	QTest::newRow("id6") << (unsigned long)(6) <<
		string("categories") <<
		string("Fib object with categories given") <<
		int(2) << setChangeableBy<<
		mapConnectedTo << liLastUsed<<setCategories;
}

void tFibObjectInfo::testReStore(){
	
	//load the test data
	QFETCH( unsigned long, ulIdentifier );
	QFETCH( string, szName );
	QFETCH( string, szDescription );
	QFETCH( int, iFibObjectSource );
	QFETCH( set< string >, setChangeableBy );
	QFETCH( SINGLE_ARG2(map< string, set< unsigned long > >), mapConnectedTo );
	QFETCH( list< time_t >, liLastUsed );
	QFETCH( set< string >, setCategories );
	
	//create a Fib object info with the data
	
	cFibObjectSource * pFibObjectSource = NULL;
	switch( iFibObjectSource ){
		//case 0: pFibObjectSource = NULL;
		case 1: pFibObjectSource = new cFibObjectSourceFibDb( 1 ); break;
		case 2: pFibObjectSource = new cFibObjectSourcePath( "~/test/test" ); break;
	}//end switch iFibObjectSource
	
	cFibObjectInfo fibObjectSourceFibDbToStore( ulIdentifier,
		szName, szDescription, pFibObjectSource, setChangeableBy );
	//set the connection data
	for ( map< string, set< unsigned long > >::const_iterator
			itrConnection = mapConnectedTo.begin();
			itrConnection != mapConnectedTo.end(); itrConnection++ ){
		fibObjectSourceFibDbToStore.addConnectionTo(
			itrConnection->first, itrConnection->second );
	}
	//set the last used times
	for ( list< time_t >::const_iterator
			itrTimeStamp = liLastUsed.begin();
			itrTimeStamp != liLastUsed.end(); itrTimeStamp++ ){
		fibObjectSourceFibDbToStore.setFibObjectUsed( *itrTimeStamp );
	}
	//set the category data
	fibObjectSourceFibDbToStore.setCategories( setCategories );
	
	//store the created object
	char szFileNameBuffer[ 256 ];
	sprintf ( szFileNameBuffer, "%s%s",
		DIR_OUTPUT, "fibObjectInfoToStore.xml" );
	{//test bool store( std::ostream & stream );
		ofstream streamOutput( szFileNameBuffer );
		
		fibObjectSourceFibDbToStore.store( streamOutput );
		
		//check getName()
		QCOMPARE( fibObjectSourceFibDbToStore.getName(), string("cFibObjectInfo") );
		//check getIdentifier()
		QCOMPARE( fibObjectSourceFibDbToStore.getIdentifier(), ulIdentifier );
		//check getFibObjectName()
		QCOMPARE( fibObjectSourceFibDbToStore.getFibObjectName(), szName );
		//check getDescription()
		QCOMPARE( fibObjectSourceFibDbToStore.getDescription(), szDescription );
		//check getFibObjectSource()
		if ( pFibObjectSource ){
			QCOMPARE( *(fibObjectSourceFibDbToStore.getFibObjectSource()), *pFibObjectSource );
			QCOMPARE( *((((const cFibObjectInfo*)(&
				fibObjectSourceFibDbToStore))->getFibObjectSource())),
				*((const cFibObjectSource*)(pFibObjectSource)) );
		}else{//pFibObjectSource == NULL
			QCOMPARE( fibObjectSourceFibDbToStore.getFibObjectSource(),
				((const cFibObjectSource*)(NULL)) );
			QCOMPARE( (((const cFibObjectInfo*)(&fibObjectSourceFibDbToStore))->getFibObjectSource()),
				((const cFibObjectSource*)(NULL)) );
		}
		//check getChangeableBy()
		QCOMPARE( fibObjectSourceFibDbToStore.getChangeableBy(), setChangeableBy );
		//check getConnectedToMap()
		QCOMPARE( fibObjectSourceFibDbToStore.getConnectedToMap(), mapConnectedTo );
		//check getCategories()
		QCOMPARE( fibObjectSourceFibDbToStore.getCategories(), setCategories );
	}
	
	{//test cFibObjectInfo( istream & stream, int * iOutStatus=NULL );
		ifstream streamInput( szFileNameBuffer );
		int iOutStatus = 0;
		cFibObjectInfo fibObjectInfoLoaded( streamInput, &iOutStatus );
		
		//test the reloaded Fib object info object
		QCOMPARE( iOutStatus, 0 );
		
		//check getName()
		QCOMPARE( fibObjectInfoLoaded.getName(), string("cFibObjectInfo") );
		//check getIdentifier()
		QCOMPARE( fibObjectInfoLoaded.getIdentifier(),
			fibObjectSourceFibDbToStore.getIdentifier() );
		//check getFibObjectName()
		QCOMPARE( fibObjectInfoLoaded.getFibObjectName(),
			fibObjectSourceFibDbToStore.getFibObjectName() );
		//check getDescription()
		QCOMPARE( fibObjectInfoLoaded.getDescription(),
			fibObjectSourceFibDbToStore.getDescription() );
		//check getFibObjectSource()
		if ( pFibObjectSource ){
			QCOMPARE( *(fibObjectInfoLoaded.getFibObjectSource()), *pFibObjectSource );
			QCOMPARE( *((((const cFibObjectInfo*)(&
				fibObjectInfoLoaded))->getFibObjectSource())),
				*((const cFibObjectSource*)(pFibObjectSource)) );
		}else{//pFibObjectSource == NULL
			QCOMPARE( fibObjectInfoLoaded.getFibObjectSource(),
				((const cFibObjectSource*)(NULL)) );
			QCOMPARE( (((const cFibObjectInfo*)(&fibObjectInfoLoaded))->getFibObjectSource()),
				((const cFibObjectSource*)(NULL)) );
		}
		//check getChangeableBy()
		QCOMPARE( fibObjectInfoLoaded.getChangeableBy(),
			fibObjectSourceFibDbToStore.getChangeableBy() );
		//check getConnectedToMap()
		QCOMPARE( fibObjectInfoLoaded.getConnectedToMap(),
			fibObjectSourceFibDbToStore.getConnectedToMap() );
		//check getLastUsedTimes()
		QCOMPARE( fibObjectInfoLoaded.getLastUsedTimes(),
			fibObjectSourceFibDbToStore.getLastUsedTimes() );
		//check getCategories()
		QCOMPARE( fibObjectSourceFibDbToStore.getCategories(), setCategories );
	}
	{//test cFibObjectInfo( const TiXmlNode * pXmlNode, int * iOutStatus=NULL );
		ifstream streamInput( szFileNameBuffer );
		TiXmlDocument xmlDocFibObject;
		streamInput >> xmlDocFibObject;
		
		if ( xmlDocFibObject.Error() ){
			//error while loading to stream
			QFAIL( "Error: could not convert stream to TiXmlDocument ." );
		}
		int iOutStatus = 0;
		cFibObjectInfo fibObjectInfoLoaded( &xmlDocFibObject, &iOutStatus );
		
		//test the reloaded Fib object info object
		QCOMPARE( iOutStatus, 0 );
		
		//check getName()
		QCOMPARE( fibObjectInfoLoaded.getName(), string("cFibObjectInfo") );
		//check getIdentifier()
		QCOMPARE( fibObjectInfoLoaded.getIdentifier(),
			fibObjectSourceFibDbToStore.getIdentifier() );
		//check getFibObjectName()
		QCOMPARE( fibObjectInfoLoaded.getFibObjectName(),
			fibObjectSourceFibDbToStore.getFibObjectName() );
		//check getDescription()
		QCOMPARE( fibObjectInfoLoaded.getDescription(),
			fibObjectSourceFibDbToStore.getDescription() );
		//check getFibObjectSource()
		if ( pFibObjectSource ){
			QCOMPARE( *(fibObjectInfoLoaded.getFibObjectSource()), *pFibObjectSource );
			QCOMPARE( *((((const cFibObjectInfo*)(&
				fibObjectInfoLoaded))->getFibObjectSource())),
				*((const cFibObjectSource*)(pFibObjectSource)) );
		}else{//pFibObjectSource == NULL
			QCOMPARE( fibObjectInfoLoaded.getFibObjectSource(),
				((const cFibObjectSource*)(NULL)) );
			QCOMPARE( (((const cFibObjectInfo*)(&fibObjectInfoLoaded))->getFibObjectSource()),
				((const cFibObjectSource*)(NULL)) );
		}
		//check getChangeableBy()
		QCOMPARE( fibObjectInfoLoaded.getChangeableBy(),
			fibObjectSourceFibDbToStore.getChangeableBy() );
		//check getConnectedToMap()
		QCOMPARE( fibObjectInfoLoaded.getConnectedToMap(),
			fibObjectSourceFibDbToStore.getConnectedToMap() );
		//check getLastUsedTimes()
		QCOMPARE( fibObjectInfoLoaded.getLastUsedTimes(),
			fibObjectSourceFibDbToStore.getLastUsedTimes() );
		//check getCategories()
		QCOMPARE( fibObjectSourceFibDbToStore.getCategories(),
			fibObjectSourceFibDbToStore.getCategories() );
	}
	{//test int restoreFibObjectInfo( istream & stream );
		ifstream streamInput( szFileNameBuffer );
		cFibObjectInfo fibObjectInfoLoaded( ((unsigned long)(0)) );
		const int iOutStatus = fibObjectInfoLoaded.restoreFibObjectInfo(
			streamInput );
		
		//test the reloaded Fib object info object
		QCOMPARE( iOutStatus, 0 );
		
		//check getName()
		QCOMPARE( fibObjectInfoLoaded.getName(), string("cFibObjectInfo") );
		//check getIdentifier()
		QCOMPARE( fibObjectInfoLoaded.getIdentifier(),
			fibObjectSourceFibDbToStore.getIdentifier() );
		//check getFibObjectName()
		QCOMPARE( fibObjectInfoLoaded.getFibObjectName(),
			fibObjectSourceFibDbToStore.getFibObjectName() );
		//check getDescription()
		QCOMPARE( fibObjectInfoLoaded.getDescription(),
			fibObjectSourceFibDbToStore.getDescription() );
		//check getFibObjectSource()
		if ( pFibObjectSource ){
			QCOMPARE( *(fibObjectInfoLoaded.getFibObjectSource()), *pFibObjectSource );
			QCOMPARE( *((((const cFibObjectInfo*)(&
				fibObjectInfoLoaded))->getFibObjectSource())),
				*((const cFibObjectSource*)(pFibObjectSource)) );
		}else{//pFibObjectSource == NULL
			QCOMPARE( fibObjectInfoLoaded.getFibObjectSource(),
				((const cFibObjectSource*)(NULL)) );
			QCOMPARE( (((const cFibObjectInfo*)(&fibObjectInfoLoaded))->getFibObjectSource()),
				((const cFibObjectSource*)(NULL)) );
		}
		//check getChangeableBy()
		QCOMPARE( fibObjectInfoLoaded.getChangeableBy(),
			fibObjectSourceFibDbToStore.getChangeableBy() );
		//check getConnectedToMap()
		QCOMPARE( fibObjectInfoLoaded.getConnectedToMap(),
			fibObjectSourceFibDbToStore.getConnectedToMap() );
		//check getLastUsedTimes()
		QCOMPARE( fibObjectInfoLoaded.getLastUsedTimes(),
			fibObjectSourceFibDbToStore.getLastUsedTimes() );
		//check getCategories()
		QCOMPARE( fibObjectSourceFibDbToStore.getCategories(),
			fibObjectSourceFibDbToStore.getCategories() );
	}
	{//test int restoreFibObjectInfo( const TiXmlNode * pXmlNode );
		ifstream streamInput( szFileNameBuffer );
		TiXmlDocument xmlDocFibObject;
		streamInput >> xmlDocFibObject;
		
		if ( xmlDocFibObject.Error() ){
			//error while loading to stream
			QFAIL( "Error: could not convert stream to TiXmlDocument ." );
		}
		cFibObjectInfo fibObjectInfoLoaded( ((unsigned long)(0)) );
		const int iOutStatus = fibObjectInfoLoaded.restoreFibObjectInfo(
			&xmlDocFibObject );
		
		//test the reloaded Fib object info object
		QCOMPARE( iOutStatus, 0 );
		
		//check getName()
		QCOMPARE( fibObjectInfoLoaded.getName(), string("cFibObjectInfo") );
		//check getIdentifier()
		QCOMPARE( fibObjectInfoLoaded.getIdentifier(),
			fibObjectSourceFibDbToStore.getIdentifier() );
		//check getFibObjectName()
		QCOMPARE( fibObjectInfoLoaded.getFibObjectName(),
			fibObjectSourceFibDbToStore.getFibObjectName() );
		//check getDescription()
		QCOMPARE( fibObjectInfoLoaded.getDescription(),
			fibObjectSourceFibDbToStore.getDescription() );
		//check getFibObjectSource()
		if ( pFibObjectSource ){
			QCOMPARE( *(fibObjectInfoLoaded.getFibObjectSource()), *pFibObjectSource );
			QCOMPARE( *((((const cFibObjectInfo*)(&
				fibObjectInfoLoaded))->getFibObjectSource())),
				*((const cFibObjectSource*)(pFibObjectSource)) );
		}else{//pFibObjectSource == NULL
			QCOMPARE( fibObjectInfoLoaded.getFibObjectSource(),
				((const cFibObjectSource*)(NULL)) );
			QCOMPARE( (((const cFibObjectInfo*)(&fibObjectInfoLoaded))->getFibObjectSource()),
				((const cFibObjectSource*)(NULL)) );
		}
		//check getChangeableBy()
		QCOMPARE( fibObjectInfoLoaded.getChangeableBy(),
			fibObjectSourceFibDbToStore.getChangeableBy() );
		//check getConnectedToMap()
		QCOMPARE( fibObjectInfoLoaded.getConnectedToMap(),
			fibObjectSourceFibDbToStore.getConnectedToMap() );
		//check getLastUsedTimes()
		QCOMPARE( fibObjectInfoLoaded.getLastUsedTimes(),
			fibObjectSourceFibDbToStore.getLastUsedTimes() );
		//check getCategories()
		QCOMPARE( fibObjectSourceFibDbToStore.getCategories(),
			fibObjectSourceFibDbToStore.getCategories() );
	}
	
	{//test cFibObjectInfo( istream & stream, int * iOutStatus=NULL );
		ifstream streamInput( szFileNameBuffer );
		int iOutStatus = 0;
		cFibObjectInfo * pFibObjectInfoLoaded =
			cFibObjectInfo::restore( streamInput, &iOutStatus );
		
		//test the reloaded Fib object info object
		QCOMPARE( iOutStatus, 0 );
		if ( pFibObjectInfoLoaded == NULL ){
			//error while loading to stream
			QFAIL( "Error: static restore() returned NULL" );
		}
		
		//check getName()
		QCOMPARE( pFibObjectInfoLoaded->getName(), string("cFibObjectInfo") );
		//check getIdentifier()
		QCOMPARE( pFibObjectInfoLoaded->getIdentifier(),
			fibObjectSourceFibDbToStore.getIdentifier() );
		//check getFibObjectName()
		QCOMPARE( pFibObjectInfoLoaded->getFibObjectName(),
			fibObjectSourceFibDbToStore.getFibObjectName() );
		//check getDescription()
		QCOMPARE( pFibObjectInfoLoaded->getDescription(),
			fibObjectSourceFibDbToStore.getDescription() );
		//check getFibObjectSource()
		if ( pFibObjectSource ){
			QCOMPARE( *(pFibObjectInfoLoaded->getFibObjectSource()), *pFibObjectSource );
			QCOMPARE( *((((const cFibObjectInfo*)(
				pFibObjectInfoLoaded))->getFibObjectSource())),
				*((const cFibObjectSource*)(pFibObjectSource)) );
		}else{//pFibObjectSource == NULL
			QCOMPARE( pFibObjectInfoLoaded->getFibObjectSource(),
				((const cFibObjectSource*)(NULL)) );
			QCOMPARE( (((const cFibObjectInfo*)(
				pFibObjectInfoLoaded))->getFibObjectSource()),
				((const cFibObjectSource*)(NULL)) );
		}
		//check getChangeableBy()
		QCOMPARE( pFibObjectInfoLoaded->getChangeableBy(),
			fibObjectSourceFibDbToStore.getChangeableBy() );
		//check getConnectedToMap()
		QCOMPARE( pFibObjectInfoLoaded->getConnectedToMap(),
			fibObjectSourceFibDbToStore.getConnectedToMap() );
		//check getLastUsedTimes()
		QCOMPARE( pFibObjectInfoLoaded->getLastUsedTimes(),
			fibObjectSourceFibDbToStore.getLastUsedTimes() );
		//check getCategories()
		QCOMPARE( fibObjectSourceFibDbToStore.getCategories(),
			fibObjectSourceFibDbToStore.getCategories() );
		
		if ( pFibObjectInfoLoaded ){
			//delete the set Fib object info object
			delete pFibObjectInfoLoaded;
		}
	}
	{//static cFibObjectInfo * restore( const TiXmlNode * pXmlNode, int * iOutStatus=NULL );
		ifstream streamInput( szFileNameBuffer );
		TiXmlDocument xmlDocFibObject;
		streamInput >> xmlDocFibObject;
		
		if ( xmlDocFibObject.Error() ){
			//error while loading to stream
			QFAIL( "Error: could not convert stream to TiXmlDocument ." );
		}
		int iOutStatus = 0;
		cFibObjectInfo * pFibObjectInfoLoaded =
			cFibObjectInfo::restore( &xmlDocFibObject, &iOutStatus );
		
		//test the reloaded Fib object info object
		QCOMPARE( iOutStatus, 0 );
		
		if ( pFibObjectInfoLoaded == NULL ){
			//error while loading to stream
			QFAIL( "Error: static restore() returned NULL" );
		}
		
		//check getName()
		QCOMPARE( pFibObjectInfoLoaded->getName(), string("cFibObjectInfo") );
		//check getIdentifier()
		QCOMPARE( pFibObjectInfoLoaded->getIdentifier(),
			fibObjectSourceFibDbToStore.getIdentifier() );
		//check getFibObjectName()
		QCOMPARE( pFibObjectInfoLoaded->getFibObjectName(),
			fibObjectSourceFibDbToStore.getFibObjectName() );
		//check getDescription()
		QCOMPARE( pFibObjectInfoLoaded->getDescription(),
			fibObjectSourceFibDbToStore.getDescription() );
		//check getFibObjectSource()
		if ( pFibObjectSource ){
			QCOMPARE( *(pFibObjectInfoLoaded->getFibObjectSource()), *pFibObjectSource );
			QCOMPARE( *((((const cFibObjectInfo*)(
				pFibObjectInfoLoaded))->getFibObjectSource())),
				*((const cFibObjectSource*)(pFibObjectSource)) );
		}else{//pFibObjectSource == NULL
			QCOMPARE( pFibObjectInfoLoaded->getFibObjectSource(),
				((const cFibObjectSource*)(NULL)) );
			QCOMPARE( (((const cFibObjectInfo*)(
				pFibObjectInfoLoaded))->getFibObjectSource()),
				((const cFibObjectSource*)(NULL)) );
		}
		//check getChangeableBy()
		QCOMPARE( pFibObjectInfoLoaded->getChangeableBy(),
			fibObjectSourceFibDbToStore.getChangeableBy() );
		//check getConnectedToMap()
		QCOMPARE( pFibObjectInfoLoaded->getConnectedToMap(),
			fibObjectSourceFibDbToStore.getConnectedToMap() );
		//check getLastUsedTimes()
		QCOMPARE( pFibObjectInfoLoaded->getLastUsedTimes(),
			fibObjectSourceFibDbToStore.getLastUsedTimes() );
		//check getCategories()
		QCOMPARE( fibObjectSourceFibDbToStore.getCategories(),
			fibObjectSourceFibDbToStore.getCategories() );
		
		if ( pFibObjectInfoLoaded ){
			//delete the set Fib object info object
			delete pFibObjectInfoLoaded;
		}
	}
	
	if ( pFibObjectSource ){
		//delete the set Fib object source
		delete pFibObjectSource;
	}
	
}


/**
 * This testcase tests the number of Fib elements value methods of the
 * cFibObjectInfo class.
 *
 * methods tested:
 * 	- void setNumberOfFibElements( const unsigned long ulInNumberOfFibElements );
 * 	- unsigned long getNumberOfFibElements() const;
 */
void tFibObjectInfo::testNumberOfFibElements(){
	
	cFibObjectInfo * pFibObjectInfo = new cFibObjectInfo( (unsigned long)(0) );
	unsigned long ulIdentifier = 0;
	unsigned long ulNumberOfFibElements = 0;
	
	for ( unsigned long ulIteration = 0;
			ulIteration < ulNumberRandomIterations; ulIteration++ ){
		
		if ( ( rand() % 16 ) != 0 ){
			//set for Fib object info object with random number of Fib elements value
			ulNumberOfFibElements = (unsigned long)(
				rand() % ulNumberRandomIterations );
			//set number of Fib elements value with setNumberOfFibElements()
			pFibObjectInfo->setNumberOfFibElements( ulNumberOfFibElements );
		}else{//create new cFibObjectInfo
			if ( pFibObjectInfo ){
				delete pFibObjectInfo;
			}
			ulIdentifier = (unsigned long)( rand() % ulNumberRandomIterations );
			pFibObjectInfo = new cFibObjectInfo( ulIdentifier );
			ulNumberOfFibElements = 0;
		}
		
		//check getNumberOfFibElements()
		QCOMPARE( pFibObjectInfo->getNumberOfFibElements(), ulNumberOfFibElements );
		//check getIdentifier()
		QCOMPARE( pFibObjectInfo->getIdentifier(), ulIdentifier );
		//check getName()
		QCOMPARE( pFibObjectInfo->getName(), string("cFibObjectInfo") );
		//check getFibObjectName()
		QCOMPARE( pFibObjectInfo->getFibObjectName(), string("") );
		//check getDescription()
		QCOMPARE( pFibObjectInfo->getDescription(), string("") );
		//check getFibObjectSource()
		QCOMPARE( pFibObjectInfo->getFibObjectSource(),
			((cFibObjectSource*)(NULL)) );
		//check getChangeableBy()
		QCOMPARE( pFibObjectInfo->getChangeableBy(), set< string >() );
		
	}//end for random iterations
	if ( pFibObjectInfo ){
		delete pFibObjectInfo;
	}
}


/**
 * This testcase tests the number of input variables value methods of the
 * cFibObjectInfo class.
 *
 * methods tested:
 * 	- void setNumberOfInputVariables( const unsigned long ulInNumberOfInputVariables );
 * 	- unsigned long getNumberOfInputVariables() const;
 */
void tFibObjectInfo::testNumberOfInputVariables(){
	
	cFibObjectInfo * pFibObjectInfo = new cFibObjectInfo( (unsigned long)(0) );
	unsigned long ulIdentifier = 0;
	unsigned long ulNumberOfInputVariables = 0;
	
	for ( unsigned long ulIteration = 0;
			ulIteration < ulNumberRandomIterations; ulIteration++ ){
		
		if ( ( rand() % 16 ) != 0 ){
			//set for Fib object info object with random number of Fib elements value
			ulNumberOfInputVariables = (unsigned long)(
				rand() % ulNumberRandomIterations );
			//set number of Fib elements value with setNumberOfInputVariables()
			pFibObjectInfo->setNumberOfInputVariables( ulNumberOfInputVariables );
		}else{//create new cFibObjectInfo
			if ( pFibObjectInfo ){
				delete pFibObjectInfo;
			}
			ulIdentifier = (unsigned long)( rand() % ulNumberRandomIterations );
			pFibObjectInfo = new cFibObjectInfo( ulIdentifier );
			ulNumberOfInputVariables = 0;
		}
		
		//check getNumberOfInputVariables()
		QCOMPARE( pFibObjectInfo->getNumberOfInputVariables(), ulNumberOfInputVariables );
		//check getIdentifier()
		QCOMPARE( pFibObjectInfo->getIdentifier(), ulIdentifier );
		//check getName()
		QCOMPARE( pFibObjectInfo->getName(), string("cFibObjectInfo") );
		//check getFibObjectName()
		QCOMPARE( pFibObjectInfo->getFibObjectName(), string("") );
		//check getDescription()
		QCOMPARE( pFibObjectInfo->getDescription(), string("") );
		//check getFibObjectSource()
		QCOMPARE( pFibObjectInfo->getFibObjectSource(),
			((cFibObjectSource*)(NULL)) );
		//check getChangeableBy()
		QCOMPARE( pFibObjectInfo->getChangeableBy(), set< string >() );
		
	}//end for random iterations
	if ( pFibObjectInfo ){
		delete pFibObjectInfo;
	}
}


/**
 * This testcase tests the number of external subobjects value methods of
 * the cFibObjectInfo class.
 *
 * methods tested:
 * 	- void setNumberOfExtSubobjects( const unsigned long ulInNumberOfExtSubobjects );
 * 	- unsigned long getNumberOfExtSubobjects() const;
 */
void tFibObjectInfo::testNumberOfExtSubobjects(){
	
	cFibObjectInfo * pFibObjectInfo = new cFibObjectInfo( (unsigned long)(0) );
	unsigned long ulIdentifier = 0;
	unsigned long ulNumberOfExtSubobjects = 0;
	
	for ( unsigned long ulIteration = 0;
			ulIteration < ulNumberRandomIterations; ulIteration++ ){
		
		if ( ( rand() % 16 ) != 0 ){
			//set for Fib object info object with random number of Fib elements value
			ulNumberOfExtSubobjects = (unsigned long)(
				rand() % ulNumberRandomIterations );
			//set number of Fib elements value with setNumberOfExtSubobjects()
			pFibObjectInfo->setNumberOfExtSubobjects( ulNumberOfExtSubobjects );
		}else{//create new cFibObjectInfo
			if ( pFibObjectInfo ){
				delete pFibObjectInfo;
			}
			ulIdentifier = (unsigned long)( rand() % ulNumberRandomIterations );
			pFibObjectInfo = new cFibObjectInfo( ulIdentifier );
			ulNumberOfExtSubobjects = 0;
		}
		
		//check getNumberOfExtSubobjects()
		QCOMPARE( pFibObjectInfo->getNumberOfExtSubobjects(), ulNumberOfExtSubobjects );
		//check getIdentifier()
		QCOMPARE( pFibObjectInfo->getIdentifier(), ulIdentifier );
		//check getName()
		QCOMPARE( pFibObjectInfo->getName(), string("cFibObjectInfo") );
		//check getFibObjectName()
		QCOMPARE( pFibObjectInfo->getFibObjectName(), string("") );
		//check getDescription()
		QCOMPARE( pFibObjectInfo->getDescription(), string("") );
		//check getFibObjectSource()
		QCOMPARE( pFibObjectInfo->getFibObjectSource(),
			((cFibObjectSource*)(NULL)) );
		//check getChangeableBy()
		QCOMPARE( pFibObjectInfo->getChangeableBy(), set< string >() );
		
	}//end for random iterations
	if ( pFibObjectInfo ){
		delete pFibObjectInfo;
	}
}




/**
 * This testcase tests the categories methods of the cFibObjectInfo class.
 *
 * methods tested:
 * 	- std::set< std::string > getCategories() const;
 * 	- void setCategories( const std::set< std::string > & setInCategories );
 * 	- void addCategory( const std::string & strCategory );
 * 	- bool removeCategory( const std::string & strCategory );
 */
void tFibObjectInfo::testCategories(){
	
	unsigned long ulIdentifier = 0;
	cFibObjectInfo * pFibObjectInfo = new cFibObjectInfo( ulIdentifier );
	const cFibObjectInfo * pFibObjectInfoConst = pFibObjectInfo;
	
	set< string > setCorrectCategories;
	
	vector< string > vecPossibleCategories;
	vecPossibleCategories.push_back( "" );
	vecPossibleCategories.push_back( "isPointobject" );
	vecPossibleCategories.push_back( "unknown" );
	vecPossibleCategories.push_back( "isObject" );
	vecPossibleCategories.push_back( "biokom" );
	vecPossibleCategories.push_back( "isPerson" );
	vecPossibleCategories.push_back( "size" );
	vecPossibleCategories.push_back( "style" );
	vecPossibleCategories.push_back( "more \n text" );
	vecPossibleCategories.push_back( "typeX::pp+!\"§$%&/()=?><" );
	//if true all category can change ("all" is in the category can change set)
	
	for ( unsigned long ulIteration = 0;
			ulIteration < ulNumberRandomIterations; ulIteration++ ){
		
		if ( ( rand() % 64 ) != 0 ){
			
			string szCategory = "";
			if ( setCorrectCategories.empty() || ( rand() % 2 ) ){
				//change random connection
				szCategory = vecPossibleCategories[
					rand() % vecPossibleCategories.size() ];
			}else{//change existing connection
				set< string>::const_iterator itrChoosenKey = setCorrectCategories.begin();
				for ( unsigned int iChoosenKey = rand() % setCorrectCategories.size();
						( 0 < iChoosenKey ); iChoosenKey--, itrChoosenKey++ ){
					//nothing to do
				}
				szCategory = (*itrChoosenKey);
			}
			/*use one identifier:
				-void addCategory( const string & szCategory );
				-bool removeCategory( const string & szCategory );
			 */
			if ( rand() % 2 ){
				//void addCategory( const string & szCategory );
				pFibObjectInfo->addCategory( szCategory );
				
				setCorrectCategories.insert( szCategory );
				
			}else{//bool removeCategory( const string & szCategory );
				bool bCategoryExists = ( 0 < setCorrectCategories.erase( szCategory ) );
				
				QCOMPARE( pFibObjectInfo->removeCategory( szCategory ),
					bCategoryExists );
			}
		}else{
			if ( rand() % 2 ){
				//test setCategories()
				//generate new random category list
				set< string > setNewCategories;
				const unsigned int uiCategoriesToChoose =
					rand() % vecPossibleCategories.size();
				for ( unsigned int uiActualCategory = 0;
						uiActualCategory < uiCategoriesToChoose; uiActualCategory++ ){
					string szCategory = "";
					if ( setCorrectCategories.empty() || ( rand() % 2 ) ){
						//change random connection
						setNewCategories.insert( vecPossibleCategories[
							rand() % vecPossibleCategories.size() ] );
					}else{//change existing connection
						set< string>::const_iterator itrChoosenKey = setCorrectCategories.begin();
						for ( unsigned int iChoosenKey = rand() % setCorrectCategories.size();
								( 0 < iChoosenKey ); iChoosenKey--, itrChoosenKey++ ){
							//nothing to do
						}
						setNewCategories.insert( *itrChoosenKey );
					}
				}//end for generate new random category list
				pFibObjectInfo->setCategories( setNewCategories );
				
				setCorrectCategories = setNewCategories;
			}else{//construct a new Fib object info cFibObjectInfo
				if ( pFibObjectInfo ){
					delete pFibObjectInfo;
				}
				ulIdentifier = (unsigned long)( rand() % ulNumberRandomIterations );
				pFibObjectInfo = new cFibObjectInfo( ulIdentifier );
				pFibObjectInfoConst = pFibObjectInfo;
				
				setCorrectCategories.clear();
			}
		}
		//set< string > getCategories() const;
		const set< string > setReturnedCategories =
			pFibObjectInfoConst->getCategories();
		
		if ( setReturnedCategories.size() != setCorrectCategories.size() ){
			QFAIL( ((QString("Error: Number of entries in the\"category can change\" not correct (retuned: %1; correct: %2).")).arg(
					setReturnedCategories.size() ).arg(
					setCorrectCategories.size() )).toStdString().c_str() );
		}
		
		for ( vector< string >::const_iterator
				itrPossibleCategory = vecPossibleCategories.begin();
				itrPossibleCategory != vecPossibleCategories.end();
				itrPossibleCategory++ ){
			
			if ( setCorrectCategories.find( *itrPossibleCategory ) ==
					setCorrectCategories.end() ){
				//not category
				if ( setReturnedCategories.find( *itrPossibleCategory ) !=
						setReturnedCategories.end() ){
					QFAIL( ((QString("Error: In the category \"%1\", but returned as category.")).arg( QString( itrPossibleCategory->c_str() ) )
						).toStdString().c_str() );
				}
			}else{//category
				if ( setReturnedCategories.find( *itrPossibleCategory ) == setReturnedCategories.end() ){
					QFAIL( ((QString("Error: In the category \"%1\", but not returned as category.")).arg( QString( itrPossibleCategory->c_str() ) )
						).toStdString().c_str() );
				}
			}
		}
		
		//check getIdentifier()
		QCOMPARE( pFibObjectInfo->getIdentifier(), ulIdentifier );
		//check getName()
		QCOMPARE( pFibObjectInfo->getName(), string("cFibObjectInfo") );
		//check getFibObjectName()
		QCOMPARE( pFibObjectInfo->getFibObjectName(), string("") );
		//check getDescription()
		QCOMPARE( pFibObjectInfo->getDescription(), string("") );
		//check getFibObjectSource()
		QCOMPARE( pFibObjectInfo->getFibObjectSource(),
			((cFibObjectSource*)(NULL)) );
		//check getChangeableBy()
		QCOMPARE( pFibObjectInfo->getChangeableBy(), set< string >() );
		
	}//end for random iterations
	if ( pFibObjectInfo ){
		delete pFibObjectInfo;
	}
}



/**
 * This testcase tests the store and restore for Fib objects methods of the
 * cFibObjectSourcePath class.
 *
 * methods tested:
 * 	- cFibElement * loadFibObjectFromSource( int * iOutStatus = NULL );
 * 	- bool deleteLoadedFibObject();
 */
void tFibObjectInfo::testLoadFibObject_data(){
	
	QTest::addColumn<string>("szPath");
	QTest::addColumn<bool>("bExists");

	QTest::newRow("point.xml") << string("./testObjects/fibObjDummy/point.xml")<< true;
	QTest::newRow("point.fib") << string("./testObjects/fibObjDummy/point.fib")<< true;
	QTest::newRow("notExisting") << string("./testObjects/fibObjDummy/notExisting.fib")<< false;
}

void tFibObjectInfo::testLoadFibObject(){
	
	QFETCH( string, szPath );
	QFETCH( bool, bExists );
	
	//use parameter constructor
	cFibObjectSourcePath fibObjectSourcePath1( szPath );
	
	cFibObjectInfo fibObjectInfo( 1, "load", "load test", &fibObjectSourcePath1 );
	
	set< string > setCorrectChangebelBy;
	if ( bExists ){
		//Fib object exists -> correct can change users are "all" users
		setCorrectChangebelBy.insert( "all" );
	}
	//test deleteLoadedFibObject()
	QCOMPARE( fibObjectInfo.deleteLoadedFibObject(), false );
	
	//test loadFibObject( iOutStatus, pOutSetChangebelBy )
	int iOutStatus = 0;
	cFibElement * pLoadedFibObject = fibObjectInfo.loadFibObjectFromSource(
		&iOutStatus );
	
	if ( pLoadedFibObject != NULL ){
		if ( bExists ){
			QCOMPARE( iOutStatus, 0 );
		}else{
			QFAIL( "Error: loadFibObject() returned Fib object, but should return NULL (no such path Fib object)" );
		}
	}else{
		if ( bExists ){
			QFAIL( "Error: loadFibObject() returned NULL, but should return path Fib object" );
		}else{
			if ( iOutStatus == 0 ){
				QFAIL( "Error: loadFibObject() returned correctly NULL, but the output status iOutStatus is 0" );
			}
		}
	}
	//check getName()
	QCOMPARE( fibObjectInfo.getName(), string("cFibObjectInfo") );
	//check getIdentifier()
	QCOMPARE( fibObjectInfo.getIdentifier(), ((unsigned long)(1)) );
	//check getFibObjectName()
	QCOMPARE( fibObjectInfo.getFibObjectName(), string("load") );
	//check getDescription()
	QCOMPARE( fibObjectInfo.getDescription(), string("load test") );
	//test getFibObjectSource()
	if ( ! ( fibObjectSourcePath1 == (*(fibObjectInfo.getFibObjectSource())) ) ){
		QFAIL( "Error: loadFibObject() changed the set Fib object source" );
	}
	//check getChangeableBy()
	QCOMPARE( fibObjectInfo.getChangeableBy(), setCorrectChangebelBy );
	
	//test loadFibObject( iOutStatus, pOutSetChangebelBy )
	cFibElement * pLoadedFibObject2 = fibObjectInfo.loadFibObjectFromSource(
		&iOutStatus );
	
	QCOMPARE( pLoadedFibObject, pLoadedFibObject2 );
	if ( pLoadedFibObject2 != NULL ){
		if ( bExists ){
			QCOMPARE( iOutStatus, 0 );
		}else{
			QFAIL( "Error: loadFibObject() returned Fib object, but should return NULL (no such path Fib object)" );
		}
	}else{
		if ( bExists ){
			QFAIL( "Error: loadFibObject() returned NULL, but should return path Fib object" );
		}else{
			if ( iOutStatus == 0 ){
				QFAIL( "Error: loadFibObject() returned correctly NULL, but the output status iOutStatus is 0" );
			}
		}
	}
	//check getName()
	QCOMPARE( fibObjectInfo.getName(), string("cFibObjectInfo") );
	//check getIdentifier()
	QCOMPARE( fibObjectInfo.getIdentifier(), ((unsigned long)(1)) );
	//check getFibObjectName()
	QCOMPARE( fibObjectInfo.getFibObjectName(), string("load") );
	//check getDescription()
	QCOMPARE( fibObjectInfo.getDescription(), string("load test") );
	//test getFibObjectSource()
	if ( ! ( fibObjectSourcePath1 == (*(fibObjectInfo.getFibObjectSource())) ) ){
		QFAIL( "Error: loadFibObject() changed the set Fib object source" );
	}
	//check getChangeableBy()
	QCOMPARE( fibObjectInfo.getChangeableBy(), setCorrectChangebelBy );
	
	
	//test deleteLoadedFibObject()
	QCOMPARE( fibObjectInfo.deleteLoadedFibObject(), bExists );
	//test deleteLoadedFibObject()
	QCOMPARE( fibObjectInfo.deleteLoadedFibObject(), false );
	
	
	//test loadFibObject()
	pLoadedFibObject2 = fibObjectInfo.loadFibObjectFromSource();
	
	if ( pLoadedFibObject2 != NULL ){
		if ( ! bExists ){
			QFAIL( "Error: loadFibObject() returned Fib object, but should return NULL (no such path Fib object)" );
		}
	}else{
		if ( bExists ){
			QFAIL( "Error: loadFibObject() returned NULL, but should return path Fib object" );
		}
	}
	//check getName()
	QCOMPARE( fibObjectInfo.getName(), string("cFibObjectInfo") );
	//check getIdentifier()
	QCOMPARE( fibObjectInfo.getIdentifier(), ((unsigned long)(1)) );
	//check getFibObjectName()
	QCOMPARE( fibObjectInfo.getFibObjectName(), string("load") );
	//check getDescription()
	QCOMPARE( fibObjectInfo.getDescription(), string("load test") );
	//test getFibObjectSource()
	if ( ! ( fibObjectSourcePath1 == (*(fibObjectInfo.getFibObjectSource())) ) ){
		QFAIL( "Error: loadFibObject() changed the set Fib object source" );
	}
	//check getChangeableBy()
	QCOMPARE( fibObjectInfo.getChangeableBy(), setCorrectChangebelBy );
	
	
}//end testStoreFibObject()










/** TODO
 * 	-TODO bool extractInfoFromLoadedFibObject();
 * 	-TODO cFibObjectInfo( const unsigned long ulInIdentifier, const cFibObjectSource * pInFibObjectSource );
 */





QTEST_APPLESS_MAIN(tFibObjectInfo)
#include "tFibObjectInfo.moc"















