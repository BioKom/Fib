/**
 * @file tFibObjectSourcePath
 * file name: tFibObjectSourcePath.cpp
 * @author Betti Oesterholz
 * @date 24.09.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cFibObjectSourcePath.
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
 * This file contains the test for the class cFibObjectSourcePath, which
 * is a class for information for loading a Fib object from a given path.
 *
 *
 * What's tested of class cFibObjectSourcePath:
 * 	- cFibObjectSourcePath( const longFib & lInFibDbIdentifier );
 * 	- cFibObjectSourcePath( const std::string & szInPath );
 * 	- cFibObjectSourcePath( std::istream & stream, intFib * iOutStatus = NULL );
 * 	- cFibObjectSourcePath( const TiXmlNode * pXmlNode, intFib * iOutStatus = NULL );
 * 	- virtual ~cFibObjectSourcePath();
 * 	- virtual std::string getName() const;
 * 	- std::string getPath() const;
 * 	- virtual cFibObjectSourcePath * clone() const;
 * 	- virtual cFibElement * loadFibObject( int * iOutStatus = NULL, std::set< std::string > * pOutSetChangebelBy = NULL ) const;
 * 	- virtual bool storeFibObject( const cFibElement * pFibObject ) const;
 * 	- virtual bool checkSource() const;
 * 	- virtual bool store( std::ostream & stream ) const;
 * 	- virtual int restoreFibObjectSource( std::istream & stream );
 * 	- virtual int restoreFibObjectSource( const TiXmlNode * pXmlNode );
 * 	- static cFibObjectSourcePath * restore( std::istream & stream, intFib * iOutStatus = NULL );
 * 	- static cFibObjectSourcePath * restore( const TiXmlNode * pXmlNode, intFib * iOutStatus = NULL );
 * 	- virtual bool equal( const cFibObjectSourcePath & fibObjectSource ) const;
 * 	- virtual bool operator==( const cFibObjectSourcePath & fibObjectSource ) const;
 *
 * What's tested of parrent class cFibObjectSource:
 * 	- static cFibObjectSource * cFibObjectSource::restore( std::istream & stream, intFib * iOutStatus = NULL );
 * 	- static cFibObjectSource * cFibObjectSource::restore( const TiXmlNode * pXmlNode, intFib * iOutStatus = NULL );
 *
 */
/*
History:
24.09.2013  Oesterholz  created
*/

#include <QtTest/QtTest>

#include "version.h"

#include "cFibObjectSourcePath.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <ctime>

#include <QObject>

#include "tinyxml.h"

#include "cFibElement.h"
#include "cPoint.h"
#include "cVectorPosition.h"
#include "cFibDatabase.h"


#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif


using namespace fib::nCreator;
using namespace fib;
using namespace std;


class tFibObjectSourcePath: public QObject{
	Q_OBJECT

public:
	
	/**
	 * standard constructor
	 */
	tFibObjectSourcePath(){
		
		srand( time(NULL) );
	}
	
	
private slots:
	void testCostructor_data();
	void testCostructor();
	void testEqual();
	void testStore_data();
	void testStore();
	void testStoreFibObject_data();
	void testStoreFibObject();
	void testStoreRestoreFibObject_data();
	void testStoreRestoreFibObject();
};//end tFibObjectSourcePath

//macros so that QTest::addColumn() can use the given data types
Q_DECLARE_METATYPE(string)


/**
 * This testcase tests the constructor of the cFibObjectSourcePath class.
 *
 * methods tested:
 * 	- cFibObjectSourcePath( const std::string & szInPath );
 * 	- cFibObjectSourcePath( const cFibObjectSourcePath & fibObjectSourcePath );
 * 	- virtual ~cFibObjectSourcePath();
 * 	- virtual std::string getName() const;
 * 	- std::string getPath() const;
 * 	- virtual cFibObjectSourcePath * clone() const;
 */
void tFibObjectSourcePath::testCostructor_data(){
	
	QTest::addColumn<string>("szName");
	QTest::addColumn<string>("szPath");

	QTest::newRow("empty") << string("cFibObjectSourcePath") << string("");
	QTest::newRow("/home/biokom/") <<
		string("cFibObjectSourcePath") << string("/home/biokom/");
	QTest::newRow("/home/biokom/fib/testObj1.xml") <<
		string("cFibObjectSourcePath") << string("/home/biokom/fib/testObj1.xml");
	QTest::newRow("testObj2.fib")  << string("cFibObjectSourcePath") << string("testObj2.fib");
}

void tFibObjectSourcePath::testCostructor(){
	
	QFETCH( string, szName );
	QFETCH( string, szPath );
	//test parameter constructor
	cFibObjectSourcePath fibObjectSourcePath1( szPath );
	
	QCOMPARE( fibObjectSourcePath1.getName(), szName );
	QCOMPARE( fibObjectSourcePath1.getPath(), szPath );
	
	//test copy constructor
	cFibObjectSourcePath fibObjectSourcePath1Copy( fibObjectSourcePath1 );
	
	QCOMPARE( fibObjectSourcePath1Copy.getName(), szName );
	QCOMPARE( fibObjectSourcePath1Copy.getPath(), szPath );
	
	//test clone
	cFibObjectSourcePath * pFibObjectSourcePath1Clone =
		fibObjectSourcePath1.clone();
	
	QCOMPARE( pFibObjectSourcePath1Clone->getName(), szName );
	QCOMPARE( pFibObjectSourcePath1Clone->getPath(), szPath );
	
	delete pFibObjectSourcePath1Clone;
}



/**
 * This testcase tests the equal methods of the cFibObjectSourcePath class.
 *
 * methods tested:
 * 	- virtual bool equal( const cFibObjectSourcePath & fibObjectSource ) const;
 * 	- virtual bool operator==( const cFibObjectSourcePath & fibObjectSource ) const;
 */
void tFibObjectSourcePath::testEqual(){
	
	//create objects to compare
	cFibObjectSourcePath fibObjectSourcePath1V0( "" );
	cFibObjectSourcePath fibObjectSourcePath2V0( "" );
	cFibObjectSourcePath fibObjectSourcePathVhello( "hello.xml" );
	cFibObjectSourcePath fibObjectSourcePathVHello( "Hello.xml" );
	
	//fibObjectSourcePath1V0
	QCOMPARE( fibObjectSourcePath1V0.equal( fibObjectSourcePath2V0 ), true );
	QCOMPARE( ( fibObjectSourcePath1V0 == fibObjectSourcePath2V0 ), true );
	QCOMPARE( fibObjectSourcePath1V0.equal( fibObjectSourcePathVhello ), false );
	QCOMPARE( ( fibObjectSourcePath1V0 == fibObjectSourcePathVhello ), false );
	QCOMPARE( fibObjectSourcePath1V0.equal( fibObjectSourcePathVHello ), false );
	QCOMPARE( ( fibObjectSourcePath1V0 == fibObjectSourcePathVHello ), false );
	
	//fibObjectSourcePath2V0
	QCOMPARE( fibObjectSourcePath2V0.equal( fibObjectSourcePath1V0 ), true );
	QCOMPARE( ( fibObjectSourcePath2V0 == fibObjectSourcePath1V0 ), true );
	QCOMPARE( fibObjectSourcePath2V0.equal( fibObjectSourcePathVhello ), false );
	QCOMPARE( ( fibObjectSourcePath2V0 == fibObjectSourcePathVhello ), false );
	QCOMPARE( fibObjectSourcePath2V0.equal( fibObjectSourcePathVHello ), false );
	QCOMPARE( ( fibObjectSourcePath2V0 == fibObjectSourcePathVHello ), false );
	
	//fibObjectSourcePathVhello
	QCOMPARE( fibObjectSourcePathVhello.equal( fibObjectSourcePath1V0 ), false );
	QCOMPARE( ( fibObjectSourcePathVhello == fibObjectSourcePath1V0 ), false );
	QCOMPARE( fibObjectSourcePathVhello.equal( fibObjectSourcePathVhello ), true );
	QCOMPARE( ( fibObjectSourcePathVhello == fibObjectSourcePathVhello ), true );
	QCOMPARE( fibObjectSourcePathVhello.equal( fibObjectSourcePathVHello ), false );
	QCOMPARE( ( fibObjectSourcePathVhello == fibObjectSourcePathVHello ), false );
	
	//fibObjectSourcePathVHello
	QCOMPARE( fibObjectSourcePathVHello.equal( fibObjectSourcePath1V0 ), false );
	QCOMPARE( ( fibObjectSourcePathVHello == fibObjectSourcePath1V0 ), false );
	QCOMPARE( fibObjectSourcePathVHello.equal( fibObjectSourcePathVhello ), false );
	QCOMPARE( ( fibObjectSourcePathVHello == fibObjectSourcePathVhello ), false );
	QCOMPARE( fibObjectSourcePathVHello.equal( fibObjectSourcePathVHello ), true );
	QCOMPARE( ( fibObjectSourcePathVHello == fibObjectSourcePathVHello ), true );
	
}



/**
 * This testcase tests the store and restore methods of the
 * cFibObjectSourcePath class.
 *
 * methods tested:
 * 	- cFibObjectSourcePath( std::istream & stream, intFib * iOutStatus = NULL );
 * 	- cFibObjectSourcePath( const TiXmlNode * pXmlNode, intFib * iOutStatus = NULL );
 * 	- virtual ~cFibObjectSourcePath();
 * 	- virtual std::string getName() const;
 * 	- std::string getPath() const;
 * 	- virtual bool store( std::ostream & stream );
 * 	- virtual int restoreFibObjectSource( std::istream & stream );
 * 	- virtual int restoreFibObjectSource( const TiXmlNode * pXmlNode );
 * 	- static cFibObjectSourcePath * restore( std::istream & stream, intFib * iOutStatus = NULL );
 * 	- static cFibObjectSourcePath * restore( const TiXmlNode * pXmlNode, intFib * iOutStatus = NULL );
 *
 * What's tested of parrent class cFibObjectSource:
 * 	- static cFibObjectSource * cFibObjectSource::restore( std::istream & stream, intFib * iOutStatus = NULL );
 * 	- static cFibObjectSource * cFibObjectSource::restore( const TiXmlNode * , intFib * iOutStatus = NULL );
 */
void tFibObjectSourcePath::testStore_data(){
	
	QTest::addColumn<string>("szPath");

	QTest::newRow("empty") << string("");
	QTest::newRow("/home/biokom/") << string("/home/biokom/");
	QTest::newRow("/home/biokom/fib/testObj1.xml") << string("/home/biokom/fib/testObj1.xml");
	QTest::newRow("testObj2.fib")  << string("testObj2.fib");
	QTest::newRow("c:\\fib\\testObj1.xml") << string("c:\\fib\\testObj1.xml");
	QTest::newRow("test_Obj?.*")  << string("test_Obj?.*");
	QTest::newRow("test Obj...*<>")  << string("test Obj...*<>");
}


void tFibObjectSourcePath::testStore(){
	

	QFETCH( string, szPath );

	cFibObjectSourcePath fibObjectSourcePathToStore( szPath );
	
	QCOMPARE( fibObjectSourcePathToStore.getName(),
		((string)("cFibObjectSourcePath")) );
	QCOMPARE( fibObjectSourcePathToStore.getPath(), szPath );
	
	
	char szFileNameBuffer[ 256 ];
	sprintf ( szFileNameBuffer, "%s%s",
		DIR_OUTPUT, "fibObjectSourcePathToStore.xml" );
	{//test bool store( std::ostream & stream );
		ofstream streamOutput( szFileNameBuffer );
		
		fibObjectSourcePathToStore.store( streamOutput );
		
		QCOMPARE( fibObjectSourcePathToStore.getName(),
			((string)("cFibObjectSourcePath")) );
		QCOMPARE( fibObjectSourcePathToStore.getPath(), szPath );
	}
	
	{//test cFibObjectSourcePath( std::istream & stream, intFib iOutStatus = NULL );
		intFib iOutStatus = 0;
		ifstream streamInput( szFileNameBuffer );
		cFibObjectSourcePath fibObjectSourcePathConstStrRead(
			streamInput, &iOutStatus );
		
		QCOMPARE( iOutStatus, ((intFib)(0)) );
		QCOMPARE( fibObjectSourcePathConstStrRead.getName(),
			((string)("cFibObjectSourcePath")) );
		QCOMPARE( fibObjectSourcePathConstStrRead.getPath(), szPath );
	}
	{//test restoreFibObjectSource( std::istream & stream );
		ifstream streamInput( szFileNameBuffer );
		cFibObjectSourcePath fibObjectSourcePathStrRead( ((longFib)(0)) );
		const intFib iOutStatus = fibObjectSourcePathStrRead.
			restoreFibObjectSource( streamInput );
		
		QCOMPARE( iOutStatus, ((intFib)(0)) );
		QCOMPARE( fibObjectSourcePathStrRead.getName(),
			((string)("cFibObjectSourcePath")) );
		QCOMPARE( fibObjectSourcePathStrRead.getPath(), szPath );
	}
	{//test static restore( std::istream & stream, intFib iOutStatus = NULL );
		ifstream streamInput( szFileNameBuffer );
		
		intFib iOutStatus = 0;
		cFibObjectSourcePath * pFibObjectSourcePathStrRead = NULL;
		pFibObjectSourcePathStrRead = cFibObjectSourcePath::
			restore( streamInput, &iOutStatus );
		
		if ( pFibObjectSourcePathStrRead != NULL ){
			QCOMPARE( iOutStatus, ((intFib)(0)) );
			QCOMPARE( pFibObjectSourcePathStrRead->getName(),
				((string)("cFibObjectSourcePath")) );
			QCOMPARE( pFibObjectSourcePathStrRead->getPath(), szPath );
			delete pFibObjectSourcePathStrRead;
		}else{//if ( pFibObjectSourcePathStrRead == NULL )
			QFAIL( "Error: static restore() returned NULL" );
		}
	}
	{//cFibObjectSource::restore( std::istream & stream, intFib iOutStatus = NULL );
		ifstream streamInput( szFileNameBuffer );
		
		intFib iOutStatus = 0;
		cFibObjectSource * pFibObjectSourceStrRead = NULL;
		pFibObjectSourceStrRead = cFibObjectSource::
			restore( streamInput, &iOutStatus );
		
		if ( pFibObjectSourceStrRead != NULL ){
			QCOMPARE( iOutStatus, ((intFib)(0)) );
			QCOMPARE( pFibObjectSourceStrRead->getName(),
				((string)("cFibObjectSourcePath")) );
			if ( pFibObjectSourceStrRead->getName() ==
					((string)("cFibObjectSourcePath")) ){
				QCOMPARE( ((cFibObjectSourcePath*)(pFibObjectSourceStrRead))->
					getPath(), szPath );
			}
			delete pFibObjectSourceStrRead;
		}else{//if ( pFibObjectSourceStrRead == NULL )
			QFAIL( "Error: static restore() returned NULL" );
		}
	}
	
	{//test cFibObjectSourcePath( const TiXmlNode * pXmlNode, intFib iOutStatus = NULL );
		ifstream streamInput( szFileNameBuffer );
		TiXmlDocument xmlDocFibObject;
		streamInput >> xmlDocFibObject;
		
		if ( ! xmlDocFibObject.Error() ){
			intFib iOutStatus = 0;
			cFibObjectSourcePath fibObjectSourcePathConstStrRead(
					&xmlDocFibObject, &iOutStatus );
			
			QCOMPARE( iOutStatus, ((intFib)(0)) );
			QCOMPARE( fibObjectSourcePathConstStrRead.getName(),
				((string)("cFibObjectSourcePath")) );
			QCOMPARE( fibObjectSourcePathConstStrRead.getPath(),
				szPath );
		}else{//error while loading to stream
			QFAIL( "Error: static restore() returned NULL" );
		}
	}
	{//test int restoreFibObjectSource( const TiXmlNode * pXmlNode );
		ifstream streamInput( szFileNameBuffer );
		TiXmlDocument xmlDocFibObject;
		streamInput >> xmlDocFibObject;
		
		if ( ! xmlDocFibObject.Error() ){
			cFibObjectSourcePath fibObjectSourcePathStrRead( ((longFib)(0)) );
			const intFib iOutStatus = fibObjectSourcePathStrRead.
				restoreFibObjectSource( &xmlDocFibObject );
			
			QCOMPARE( iOutStatus, ((intFib)(0)) );
			QCOMPARE( fibObjectSourcePathStrRead.getName(),
				((string)("cFibObjectSourcePath")) );
			QCOMPARE( fibObjectSourcePathStrRead.getPath(), szPath );
		}else{//error while loading to stream
			QFAIL( "Error: static restore() returned NULL" );
		}
	}
	{//test static cFibObjectSourcePath restore( const TiXmlNode * pXmlNode, intFib iOutStatus = NULL );
		ifstream streamInput( szFileNameBuffer );
		TiXmlDocument xmlDocFibObject;
		streamInput >> xmlDocFibObject;
		
		if ( ! xmlDocFibObject.Error() ){
			intFib iOutStatus = 0;
			cFibObjectSourcePath * pFibObjectSourcePathStrRead = NULL;
			pFibObjectSourcePathStrRead = cFibObjectSourcePath::
				restore( &xmlDocFibObject, &iOutStatus );
			
			if ( pFibObjectSourcePathStrRead != NULL ){
				QCOMPARE( iOutStatus, ((intFib)(0)) );
				QCOMPARE( pFibObjectSourcePathStrRead->getName(),
					((string)("cFibObjectSourcePath")) );
				QCOMPARE( pFibObjectSourcePathStrRead->getPath(),
					szPath );
				delete pFibObjectSourcePathStrRead;
			}else{//if ( pFibObjectSourcePathStrRead == NULL )
				QFAIL( "Error: static restore() returned NULL" );
			}
		}else{//error while loading to stream
			QFAIL( "Error: static restore() returned NULL" );
		}
	}
	{//test static cFibObjectSource * cFibObjectSource::restore( const * TiXmlNode, intFib * iOutStatus = NULL );
		ifstream streamInput( szFileNameBuffer );
		TiXmlDocument xmlDocFibObject;
		streamInput >> xmlDocFibObject;
		
		if ( ! xmlDocFibObject.Error() ){
			intFib iOutStatus = 0;
			cFibObjectSource * pFibObjectSourceStrRead = NULL;
			pFibObjectSourceStrRead = cFibObjectSource::
				restore( &xmlDocFibObject, &iOutStatus );
			
			if ( pFibObjectSourceStrRead != NULL ){
				QCOMPARE( iOutStatus, ((intFib)(0)) );
				QCOMPARE( pFibObjectSourceStrRead->getName(),
					((string)("cFibObjectSourcePath")) );
				if ( pFibObjectSourceStrRead->getName() ==
						((string)("cFibObjectSourcePath")) ){
					QCOMPARE( ((cFibObjectSourcePath*)(pFibObjectSourceStrRead))->
						getPath(), szPath );
				}
				delete pFibObjectSourceStrRead;
			}else{//if ( pFibObjectSourceStrRead == NULL )
				QFAIL( "Error: static restore() returned NULL" );
			}
		}else{//error while loading to stream
			QFAIL( "Error: static restore() returned NULL" );
		}
	}
	
}



/**
 * This testcase tests the store and restore for Fib objects methods of the
 * cFibObjectSourcePath class.
 *
 * methods tested:
 * 	- virtual cFibElement * loadFibObject( int * iOutStatus = NULL, std::set< std::string > * pOutSetChangebelBy = NULL );
 * 	- virtual bool storeFibObject( const cFibElement * pFibObject );
 * 	- virtual bool checkSource() const;
 */
void tFibObjectSourcePath::testStoreFibObject_data(){
	
	QTest::addColumn<string>("szPath");
	QTest::addColumn<bool>("bExists");

	QTest::newRow("point.xml") << string("./testObjects/fibObjDummy/point.xml")<< true;
	QTest::newRow("point.fib") << string("./testObjects/fibObjDummy/point.fib")<< true;
	QTest::newRow("notExisting") << string("./testObjects/fibObjDummy/notExisting.fib")<< false;
}

void tFibObjectSourcePath::testStoreFibObject(){
	
	QFETCH( string, szPath );
	QFETCH( bool, bExists );
	
	//test parameter constructor
	cFibObjectSourcePath fibObjectSourcePath1( szPath );
	//test loadFibObject( iOutStatus, pOutSetChangebelBy )
	int iOutStatus = 0;
	set< std::string > setOutSetChangebelBy;
	cFibElement * pLoadedFibObject = fibObjectSourcePath1.loadFibObject(
		&iOutStatus, &setOutSetChangebelBy );
	
	if ( pLoadedFibObject != NULL ){
		if ( bExists ){
			QCOMPARE( iOutStatus, 0 );
			
			set< std::string > setCanChange;
			setCanChange.insert("all");
			QCOMPARE( setOutSetChangebelBy, setCanChange );
			
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
	
	//test storeFibObject();
	QCOMPARE( fibObjectSourcePath1.storeFibObject( pLoadedFibObject ), bExists );
	
	if ( pLoadedFibObject != NULL ){
		pLoadedFibObject->deleteObject();
	}
	
	//test loadFibObject() (without parameters)
	pLoadedFibObject = fibObjectSourcePath1.loadFibObject();
	
	if ( pLoadedFibObject != NULL ){
		if ( ! bExists ){
			QFAIL( "Error: loadFibObject() returned Fib object, but should return NULL (no such path Fib object)" );
		}
	}else{
		if ( bExists ){
			QFAIL( "Error: loadFibObject() returned NULL, but should return path Fib object" );
		}
	}
	if ( pLoadedFibObject != NULL ){
		pLoadedFibObject->deleteObject();
	}
	
	QCOMPARE( fibObjectSourcePath1.checkSource(), bExists );
	
}//end testStoreFibObject()




/**
 * This testcase tests the store and restore for Fib objects methods of the
 * cFibObjectSourcePath class.
 *
 * methods tested:
 * 	- virtual cFibElement * loadFibObject( int * iOutStatus = NULL, std::set< std::string > * pOutSetChangebelBy = NULL );
 * 	- virtual bool storeFibObject( const cFibElement * pFibObject );
 */
void tFibObjectSourcePath::testStoreRestoreFibObject_data(){
	
	QTest::addColumn<string>("szPath");
	
	QTest::newRow("point.xml") << string( DIR_OUTPUT ) + "point.xml";
	QTest::newRow("point.fib") << string( DIR_OUTPUT ) + "point.fib";
	QTest::newRow("point.grm") << string( DIR_OUTPUT ) + "point.grm";
}

void tFibObjectSourcePath::testStoreRestoreFibObject(){
	
	QFETCH( string, szPath );
	
	//create a point object
	cVectorPosition vecPosition( 2 );
	vecPosition.setValue( 1, 3 );
	
	cPoint pointToStore( &vecPosition );
	const cRoot fibObjectToStore( &pointToStore );
	
	//create path Fib object source object
	cFibObjectSourcePath fibObjectSourcePath( szPath );
	
	//test storeFibObject();
	QCOMPARE( fibObjectSourcePath.storeFibObject( &fibObjectToStore ), true );
	
	
	//test loadFibObject( iOutStatus, pOutSetChangebelBy )
	int iOutStatus = 0;
	set< std::string > setOutSetChangebelBy;
	cFibElement * pLoadedFibObject = fibObjectSourcePath.loadFibObject(
		&iOutStatus, &setOutSetChangebelBy );
	
	if ( pLoadedFibObject != NULL ){
		QCOMPARE( iOutStatus, 0 );
		
		set< std::string > setCanChange;
		setCanChange.insert("all");
		QCOMPARE( setOutSetChangebelBy, setCanChange );
		
		if( ! fibObjectToStore.equal( *pLoadedFibObject ) ){
			QFAIL( "Error: The loaded Fib object is not equal to the inital point" );
		}
		
		cFibElement * pMainFibObject = pLoadedFibObject->getNextFibElement();
		if ( ( pMainFibObject->getType() == 'p' ) &&
				( ((cPoint*)(pMainFibObject))->getPosition() ) ){
			((cPoint*)(pMainFibObject))->getPosition()->setValue( 1, 5 );
		}else{
			QFAIL( "Error: Can't set the paint vector value of the restored Fib object." );
		}
	}else{//no Fib object could be loaded
		QFAIL( "Error: loadFibObject() returned NULL, but should return a Fib object" );
	}
	
	
	//test storeFibObject();
	QCOMPARE( fibObjectSourcePath.storeFibObject( pLoadedFibObject ), true );
	
	
	//test loadFibObject() (without parameters)
	cFibElement * pReloadedFibObject = fibObjectSourcePath.loadFibObject(
		&iOutStatus, &setOutSetChangebelBy );
	
	if ( pReloadedFibObject != NULL ){
		
		QCOMPARE( iOutStatus, 0 );
		
		set< std::string > setCanChange;
		setCanChange.insert("all");
		QCOMPARE( setOutSetChangebelBy, setCanChange );
		
		if( ! pLoadedFibObject->equal( *pReloadedFibObject ) ){
			QFAIL( "Error: The reloaded Fib object is not equal to the changed point" );
		}
		
		pReloadedFibObject->deleteObject();
	}else{// pReloadedFibObject == NULL
		QFAIL( "Error: loadFibObject() returned NULL, but should return a Fib object (reload)" );
	}
	if ( pLoadedFibObject != NULL ){
		pLoadedFibObject->deleteObject();
	}
	
}//end testStoreFibObject()





QTEST_APPLESS_MAIN(tFibObjectSourcePath)
#include "tFibObjectSourcePath.moc"















