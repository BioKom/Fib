/**
 * @file tFibObjectSourceFibDb
 * file name: tFibObjectSourceFibDb.cpp
 * @author Betti Oesterholz
 * @date 24.09.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cFibObjectSourceFibDb.
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
 * This file contains the test for the class cFibObjectSourceFibDb, which
 * is a class for information for loading a Fib object from the Fib database.
 *
 *
 * What's tested of class cFibObjectSourceFibDb:
 * 	- cFibObjectSourceFibDb( const longFib & lInFibDbIdentifier );
 * 	- cFibObjectSourceFibDb( const cFibObjectSourceFibDb & fibObjectSourceFibDb );
 * 	- cFibObjectSourceFibDb( std::istream & stream, intFib * iOutStatus = NULL );
 * 	- cFibObjectSourceFibDb( const TiXmlNode * pXmlNode, intFib * iOutStatus = NULL );
 * 	- virtual ~cFibObjectSourceFibDb();
 * 	- virtual std::string getName() const;
 * 	- longFib getFibDbIdentifier() const;
 * 	- virtual cFibObjectSourceFibDb * clone() const;
 * 	- virtual cFibElement * loadFibObject( int * iOutStatus = NULL, std::set< std::string > * pOutSetChangebelBy = NULL ) const;
 * 	- virtual bool storeFibObject( const cFibElement * pFibObject ) const;
 * 	-virtual bool checkSource() const;
 * 	- virtual bool store( std::ostream & stream ) const;
 * 	- virtual int restoreFibObjectSource( std::istream & stream );
 * 	- virtual int restoreFibObjectSource( const TiXmlNode * pXmlNode );
 * 	- static cFibObjectSourceFibDb * restore( std::istream & stream, intFib * iOutStatus = NULL );
 * 	- static cFibObjectSourceFibDb * restore( const TiXmlNode * pXmlNode, intFib * iOutStatus = NULL );
 * 	- virtual bool equal( const cFibObjectSourceFibDb & fibObjectSource ) const;
 * 	- virtual bool operator==( const cFibObjectSourceFibDb & fibObjectSource ) const;
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

#include "cFibObjectSourceFibDb.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <ctime>

#include <QObject>

#include "tinyxml.h"

#include "cFibElement.h"
#include "cPoint.h"
#include "cFibDatabase.h"


#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif


using namespace fib::nCreator;
using namespace fib;
using namespace std;


class tFibObjectSourceFibDb: public QObject{
	Q_OBJECT
	
	/**
	 * The number of iterations for the random tests.
	 */
	const unsigned long ulNumberRandomIterations;
	
public:
	
	/**
	 * standard constructor
	 */
	tFibObjectSourceFibDb():ulNumberRandomIterations( 64 ){
		
		srand( time(NULL) );
	}
	
	
private slots:
	void testCostructor_data();
	void testCostructor();
	void testEqual();
	void testStore();
	void testStoreFibObject_data();
	void testStoreFibObject();
};//end tFibObjectSourceFibDb

//Macros so that QTest::addColumn() can use the given data types
Q_DECLARE_METATYPE(string)
Q_DECLARE_METATYPE(longFib)


/**
 * This testcase tests the constructor of the cFibObjectSourceFibDb class.
 *
 * methods tested:
 * 	- cFibObjectSourceFibDb( const longFib & lInFibDbIdentifier );
 * 	- cFibObjectSourceFibDb( const cFibObjectSourceFibDb & fibObjectSourceFibDb );
 * 	- virtual ~cFibObjectSourceFibDb();
 * 	- virtual std::string getName() const;
 * 	- longFib getFibDbIdentifier() const;
 * 	- virtual cFibObjectSourceFibDb * clone() const;
 */
void tFibObjectSourceFibDb::testCostructor_data(){
	
	QTest::addColumn<string>("szName");
	QTest::addColumn<longFib>("lIdentifier");

	QTest::newRow("id17") << string("cFibObjectSourceFibDb") << ((longFib)(17));
	QTest::newRow("idm3") << string("cFibObjectSourceFibDb") << ((longFib)(-3));
	QTest::newRow("id0")  << string("cFibObjectSourceFibDb") << ((longFib)(0));
}

void tFibObjectSourceFibDb::testCostructor(){
	
	QFETCH( string, szName );
	QFETCH( longFib, lIdentifier );
	
	//test parameter constructor
	cFibObjectSourceFibDb fibObjectSourceFibDb1( lIdentifier );
	
	QCOMPARE( fibObjectSourceFibDb1.getName(), szName );
	QCOMPARE( fibObjectSourceFibDb1.getFibDbIdentifier(), lIdentifier );
	
	//test copy constructor
	cFibObjectSourceFibDb fibObjectSourceFibDb1Copy( fibObjectSourceFibDb1 );
	
	QCOMPARE( fibObjectSourceFibDb1Copy.getName(), szName );
	QCOMPARE( fibObjectSourceFibDb1Copy.getFibDbIdentifier(), lIdentifier );
	
	//test clone
	cFibObjectSourceFibDb * pFibObjectSourceFibDb1Clone =
		fibObjectSourceFibDb1.clone();
	
	QCOMPARE( pFibObjectSourceFibDb1Clone->getName(), szName );
	QCOMPARE( pFibObjectSourceFibDb1Clone->getFibDbIdentifier(), lIdentifier );
	
	delete pFibObjectSourceFibDb1Clone;
}



/**
 * This testcase tests the equal methods of the cFibObjectSourceFibDb class.
 *
 * methods tested:
 * 	- virtual bool equal( const cFibObjectSourceFibDb & fibObjectSource ) const;
 * 	- virtual bool operator==( const cFibObjectSourceFibDb & fibObjectSource ) const;
 */
void tFibObjectSourceFibDb::testEqual(){
	
	//create objects to compare
	cFibObjectSourceFibDb fibObjectSourceFibDb1V0( ((longFib)( 0 )) );
	cFibObjectSourceFibDb fibObjectSourceFibDb2V0( ((longFib)( 0 )) );
	cFibObjectSourceFibDb fibObjectSourceFibDbV3(  ((longFib)( 3 )) );
	cFibObjectSourceFibDb fibObjectSourceFibDbVm17(((longFib)( -17 )) );
	
	//fibObjectSourceFibDb1V0
	QCOMPARE( fibObjectSourceFibDb1V0.equal( fibObjectSourceFibDb2V0 ), true );
	QCOMPARE( ( fibObjectSourceFibDb1V0 == fibObjectSourceFibDb2V0 ), true );
	QCOMPARE( fibObjectSourceFibDb1V0.equal( fibObjectSourceFibDbV3 ), false );
	QCOMPARE( ( fibObjectSourceFibDb1V0 == fibObjectSourceFibDbV3 ), false );
	QCOMPARE( fibObjectSourceFibDb1V0.equal( fibObjectSourceFibDbVm17 ), false );
	QCOMPARE( ( fibObjectSourceFibDb1V0 == fibObjectSourceFibDbVm17 ), false );
	
	//fibObjectSourceFibDb2V0
	QCOMPARE( fibObjectSourceFibDb2V0.equal( fibObjectSourceFibDb1V0 ), true );
	QCOMPARE( ( fibObjectSourceFibDb2V0 == fibObjectSourceFibDb1V0 ), true );
	QCOMPARE( fibObjectSourceFibDb2V0.equal( fibObjectSourceFibDbV3 ), false );
	QCOMPARE( ( fibObjectSourceFibDb2V0 == fibObjectSourceFibDbV3 ), false );
	QCOMPARE( fibObjectSourceFibDb2V0.equal( fibObjectSourceFibDbVm17 ), false );
	QCOMPARE( ( fibObjectSourceFibDb2V0 == fibObjectSourceFibDbVm17 ), false );
	
	//fibObjectSourceFibDbV3
	QCOMPARE( fibObjectSourceFibDbV3.equal( fibObjectSourceFibDb1V0 ), false );
	QCOMPARE( ( fibObjectSourceFibDbV3 == fibObjectSourceFibDb1V0 ), false );
	QCOMPARE( fibObjectSourceFibDbV3.equal( fibObjectSourceFibDbV3 ), true );
	QCOMPARE( ( fibObjectSourceFibDbV3 == fibObjectSourceFibDbV3 ), true );
	QCOMPARE( fibObjectSourceFibDbV3.equal( fibObjectSourceFibDbVm17 ), false );
	QCOMPARE( ( fibObjectSourceFibDbV3 == fibObjectSourceFibDbVm17 ), false );
	
	//fibObjectSourceFibDbVm17
	QCOMPARE( fibObjectSourceFibDbVm17.equal( fibObjectSourceFibDb1V0 ), false );
	QCOMPARE( ( fibObjectSourceFibDbVm17 == fibObjectSourceFibDb1V0 ), false );
	QCOMPARE( fibObjectSourceFibDbVm17.equal( fibObjectSourceFibDbV3 ), false );
	QCOMPARE( ( fibObjectSourceFibDbVm17 == fibObjectSourceFibDbV3 ), false );
	QCOMPARE( fibObjectSourceFibDbVm17.equal( fibObjectSourceFibDbVm17 ), true );
	QCOMPARE( ( fibObjectSourceFibDbVm17 == fibObjectSourceFibDbVm17 ), true );
	
}



/**
 * This testcase tests the store and restore methods and constructors of
 * the cFibObjectSourceFibDb class.
 *
 * methods tested:
 * 	- cFibObjectSourceFibDb( std::istream & stream, intFib * iOutStatus = NULL );
 * 	- cFibObjectSourceFibDb( const TiXmlNode * pXmlNode, intFib * iOutStatus = NULL );
 * 	- virtual ~cFibObjectSourceFibDb();
 * 	- virtual std::string getName() const;
 * 	- longFib getFibDbIdentifier() const;
 * 	- virtual bool store( std::ostream & stream );
 * 	- virtual int restoreFibObjectSource( std::istream & stream );
 * 	- virtual int restoreFibObjectSource( const TiXmlNode * pXmlNode );
 * 	- static cFibObjectSourceFibDb * restore( std::istream & stream, intFib * iOutStatus = NULL );
 * 	- static cFibObjectSourceFibDb * restore( const TiXmlNode * pXmlNode, intFib * iOutStatus = NULL );
 *
 * What's tested of parrent class cFibObjectSource:
 * 	- static cFibObjectSource * cFibObjectSource::restore( std::istream & stream, intFib * iOutStatus = NULL );
 * 	- static cFibObjectSource * cFibObjectSource::restore( const TiXmlNode * , intFib * iOutStatus = NULL );
 */
void tFibObjectSourceFibDb::testStore(){
	
	for ( unsigned long ulIteration = 0;
			ulIteration < ulNumberRandomIterations; ulIteration++ ){
	
		//generat Fib database source object with random identifier
		const longFib lIdentifier = (longFib)( rand() %
			( ulNumberRandomIterations * 2 ) ) - ((longFib)(ulNumberRandomIterations));
		
		cFibObjectSourceFibDb fibObjectSourceFibDbToStore( lIdentifier );
		
		QCOMPARE( fibObjectSourceFibDbToStore.getName(),
			static_cast<string>("cFibObjectSourceFibDb") );
		QCOMPARE( fibObjectSourceFibDbToStore.getFibDbIdentifier(), lIdentifier );
		
		
		char szFileNameBuffer[ 256 ];
		sprintf ( szFileNameBuffer, "%s%s",
			DIR_OUTPUT, "fibObjectSourceFibDbToStore.xml" );
		{//test bool store( std::ostream & stream );
			ofstream streamOutput( szFileNameBuffer );
			
			fibObjectSourceFibDbToStore.store( streamOutput );
			
			QCOMPARE( fibObjectSourceFibDbToStore.getName(),
				static_cast<string>("cFibObjectSourceFibDb") );
			QCOMPARE( fibObjectSourceFibDbToStore.getFibDbIdentifier(), lIdentifier );
		}
		
		{//test cFibObjectSourceFibDb( std::istream & stream, intFib iOutStatus = NULL );
			intFib iOutStatus = 0;
			ifstream streamInput( szFileNameBuffer );
			cFibObjectSourceFibDb fibObjectSourceFibDbConstStrRead(
				streamInput, &iOutStatus );
			
			QCOMPARE( iOutStatus, ((intFib)(0)) );
			QCOMPARE( fibObjectSourceFibDbConstStrRead.getName(),
				static_cast<string>("cFibObjectSourceFibDb") );
			QCOMPARE( fibObjectSourceFibDbConstStrRead.getFibDbIdentifier(), lIdentifier );
		}
		{//test restoreFibObjectSource( std::istream & stream );
			ifstream streamInput( szFileNameBuffer );
			cFibObjectSourceFibDb fibObjectSourceFibDbStrRead( ((longFib)(0)) );
			const intFib iOutStatus = fibObjectSourceFibDbStrRead.
				restoreFibObjectSource( streamInput );
			
			QCOMPARE( iOutStatus, ((intFib)(0)) );
			QCOMPARE( fibObjectSourceFibDbStrRead.getName(),
				static_cast<string>("cFibObjectSourceFibDb") );
			QCOMPARE( fibObjectSourceFibDbStrRead.getFibDbIdentifier(), lIdentifier );
		}
		{//test static restore( std::istream & stream, intFib iOutStatus = NULL );
			ifstream streamInput( szFileNameBuffer );
			
			intFib iOutStatus = 0;
			cFibObjectSourceFibDb * pFibObjectSourceFibDbStrRead = NULL;
			pFibObjectSourceFibDbStrRead = cFibObjectSourceFibDb::
				restore( streamInput, &iOutStatus );
			
			if ( pFibObjectSourceFibDbStrRead != NULL ){
				QCOMPARE( iOutStatus, ((intFib)(0)) );
				QCOMPARE( pFibObjectSourceFibDbStrRead->getName(),
					static_cast<string>("cFibObjectSourceFibDb") );
				QCOMPARE( pFibObjectSourceFibDbStrRead->getFibDbIdentifier(),
					lIdentifier );
				delete pFibObjectSourceFibDbStrRead;
			}else{//if ( pFibObjectSourceFibDbStrRead == NULL )
				QFAIL( "Error: static restore() returned NULL" );
			}
		}
		{//cFibObjectSource::restore( std::istream & stream, intFib iOutStatus = NULL );
			ifstream streamInput( szFileNameBuffer );
			
			intFib iOutStatus = 0;
			cFibObjectSource * pFibObjectSourceStrRead = NULL;
			pFibObjectSourceStrRead = cFibObjectSource::
				restore( streamInput, &iOutStatus );
			
			//test the reloaded Fib object info object
			QCOMPARE( iOutStatus, 0 );
			if ( pFibObjectSourceStrRead != NULL ){
				QCOMPARE( iOutStatus, ((intFib)(0)) );
				QCOMPARE( pFibObjectSourceStrRead->getName(),
					static_cast<string>("cFibObjectSourceFibDb") );
				if ( pFibObjectSourceStrRead->getName() ==
						static_cast<string>("cFibObjectSourceFibDb") ){
					QCOMPARE( ((cFibObjectSourceFibDb*)(pFibObjectSourceStrRead))->
						getFibDbIdentifier(), lIdentifier );
				}
				delete pFibObjectSourceStrRead;
			}else{//if ( pFibObjectSourceStrRead == NULL )
				QFAIL( "Error: static restore() returned NULL" );
			}
		}
		
		{//test cFibObjectSourceFibDb( const TiXmlNode * pXmlNode, intFib iOutStatus = NULL );
			ifstream streamInput( szFileNameBuffer );
			TiXmlDocument xmlDocFibObject;
			streamInput >> xmlDocFibObject;
			
			if ( ! xmlDocFibObject.Error() ){
				intFib iOutStatus = 0;
				cFibObjectSourceFibDb fibObjectSourceFibDbConstStrRead(
						&xmlDocFibObject, &iOutStatus );
				
				QCOMPARE( iOutStatus, ((intFib)(0)) );
				QCOMPARE( fibObjectSourceFibDbConstStrRead.getName(),
					static_cast<string>("cFibObjectSourceFibDb") );
				QCOMPARE( fibObjectSourceFibDbConstStrRead.getFibDbIdentifier(),
					lIdentifier );
			}else{//error while loading to stream
				QFAIL( "Error: static restore() returned NULL" );
			}
		}
		{//test int restoreFibObjectSource( const TiXmlNode * pXmlNode );
			ifstream streamInput( szFileNameBuffer );
			TiXmlDocument xmlDocFibObject;
			streamInput >> xmlDocFibObject;
			
			if ( ! xmlDocFibObject.Error() ){
				cFibObjectSourceFibDb fibObjectSourceFibDbStrRead( ((longFib)(0)) );
				const intFib iOutStatus = fibObjectSourceFibDbStrRead.
					restoreFibObjectSource( &xmlDocFibObject );
				
				QCOMPARE( iOutStatus, ((intFib)(0)) );
				QCOMPARE( fibObjectSourceFibDbStrRead.getName(),
					static_cast<string>("cFibObjectSourceFibDb") );
				QCOMPARE( fibObjectSourceFibDbStrRead.getFibDbIdentifier(), lIdentifier );
			}else{//error while loading to stream
				QFAIL( "Error: static restore() returned NULL" );
			}
		}
		{//test static cFibObjectSourceFibDb restore( const TiXmlNode * pXmlNode, intFib iOutStatus = NULL );
			ifstream streamInput( szFileNameBuffer );
			TiXmlDocument xmlDocFibObject;
			streamInput >> xmlDocFibObject;
			
			if ( ! xmlDocFibObject.Error() ){
				intFib iOutStatus = 0;
				cFibObjectSourceFibDb * pFibObjectSourceFibDbStrRead = NULL;
				pFibObjectSourceFibDbStrRead = cFibObjectSourceFibDb::
					restore( &xmlDocFibObject, &iOutStatus );
				
				if ( pFibObjectSourceFibDbStrRead != NULL ){
					QCOMPARE( iOutStatus, ((intFib)(0)) );
					QCOMPARE( pFibObjectSourceFibDbStrRead->getName(),
						static_cast<string>("cFibObjectSourceFibDb") );
					QCOMPARE( pFibObjectSourceFibDbStrRead->getFibDbIdentifier(),
						lIdentifier );
					delete pFibObjectSourceFibDbStrRead;
				}else{//if ( pFibObjectSourceFibDbStrRead == NULL )
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
						static_cast<string>("cFibObjectSourceFibDb") );
					if ( pFibObjectSourceStrRead->getName() ==
							static_cast<string>("cFibObjectSourceFibDb") ){
						QCOMPARE( ((cFibObjectSourceFibDb*)(pFibObjectSourceStrRead))->
							getFibDbIdentifier(), lIdentifier );
					}
					delete pFibObjectSourceStrRead;
				}else{//if ( pFibObjectSourceStrRead == NULL )
					QFAIL( "Error: static restore() returned NULL" );
				}
			}else{//error while loading to stream
				QFAIL( "Error: static restore() returned NULL" );
			}
		}
		
	}//end for random iterations
}



/**
 * This testcase tests the load and store methods of the cFibObjectSourceFibDb class.
 *
 * methods tested:
 * 	- virtual cFibElement * loadFibObject( int * iOutStatus = NULL, std::set< std::string > * pOutSetChangebelBy = NULL );
 * 	- virtual bool storeFibObject( const cFibElement * pFibObject );
 * 	- virtual bool checkSource() const;
 */
void tFibObjectSourceFibDb::testStoreFibObject_data(){
	
	QTest::addColumn<longFib>("identifier");
	QTest::addColumn<bool>("bExists");

	QTest::newRow("id1") << ((longFib)(-1))    << true;
	QTest::newRow("id10") << ((longFib)(-10))  << true;
	QTest::newRow("id30")  << ((longFib)(-30)) << true;
	QTest::newRow("id90")  << ((longFib)(-90)) << true;
	QTest::newRow("idP90")  << ((longFib)(90)) << false;
}

void tFibObjectSourceFibDb::testStoreFibObject(){
	
	QFETCH( longFib, identifier );
	QFETCH( bool, bExists );
	
	//test parameter constructor
	cFibObjectSourceFibDb fibObjectSourceFibDb1( identifier );
	//test loadFibObject( iOutStatus, pOutSetChangebelBy )
	int iOutStatus = 0;
	set< std::string > setOutSetChangebelBy;
	cFibElement * pLoadedFibObject = fibObjectSourceFibDb1.loadFibObject(
		&iOutStatus, &setOutSetChangebelBy );
	
	if ( pLoadedFibObject != NULL ){
		if ( bExists ){
			QCOMPARE( iOutStatus, 0 );
			QCOMPARE( setOutSetChangebelBy, set< std::string >() );
			//check if the correct database object was returned
			cFibElement * pDbObject = fib::cFibDatabase::getInstance()->
				getFibObject( identifier );
			
			if( pDbObject == NULL ){
				QFAIL( "Error: loadFibObject() returned Fib object, but should return NULL (no such Fib database object (cFibDatabase))" );
			}else if ( ! pDbObject->equal( *pLoadedFibObject ) ){
				QFAIL( "Error: loadFibObject() returned Fib object not equal to Fib database object." );
			}
			
		}else{
			QFAIL( "Error: loadFibObject() returned Fib object, but should return NULL (no such Fib database object)" );
		}
	}else{
		if ( bExists ){
			QFAIL( "Error: loadFibObject() returned NULL, but should return Fib database object" );
		}else{
			if ( iOutStatus == 0 ){
				QFAIL( "Error: loadFibObject() returned correctly NULL, but the output status iOutStatus is 0" );
			}
		}
	}
	
	//test storeFibObject();
	QCOMPARE( fibObjectSourceFibDb1.storeFibObject( pLoadedFibObject ), false );
	
	if ( pLoadedFibObject != NULL ){
		pLoadedFibObject->deleteObject();
	}
	//try to store a other Fib object
	cPoint point;
	QCOMPARE( fibObjectSourceFibDb1.storeFibObject( &point ), false );
	
	
	//test loadFibObject() (without parameters)
	pLoadedFibObject = fibObjectSourceFibDb1.loadFibObject();
	
	if ( pLoadedFibObject != NULL ){
		if ( ! bExists ){
			QFAIL( "Error: loadFibObject() returned Fib object, but should return NULL (no such Fib database object)" );
		}
	}else{
		if ( bExists ){
			QFAIL( "Error: loadFibObject() returned NULL, but should return Fib database object" );
		}
	}
	
	if ( pLoadedFibObject != NULL ){
		pLoadedFibObject->deleteObject();
	}
	
	QCOMPARE( fibObjectSourceFibDb1.checkSource(), bExists );
	
}//end testStoreFibObject()








QTEST_APPLESS_MAIN(tFibObjectSourceFibDb)
#include "tFibObjectSourceFibDb.moc"















