/**
 * @file tFibObject
 * file name: tFibObject.cpp
 * @author Betti Oesterholz
 * @date 20.12.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for testing Fib objects.
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
 * This test is for testing Fib objects.
 * The methods Fib object methods that are not for the Fib elementstructur,
 * evaluing or storing a Fib object are tested with this test.
 *
 *
 * What's tested of class cFibElement -classes:
 * 	- string getTypeName( char cType );
 * 	- list<longFib> getAllRootObjectIdentifiers() const;
 * 	- list<longFib> getAllDatabaseObjectIdentifiers() const;
 * 	- cRoot *getRootObject( longFib lIdentifier );
 * 	- list<longFib> getAllAccessibleRootObjectIdentifiers() const;
 * 	- cRoot *getAccessibleRootObject( longFib lIdentifier );
 * 	- cDomains getValidDomains() const;
 * 	- cDomains getValidValueDomains() const;
 * 	- unsignedIntFib getNumberOfDimensions() const;
 * 	- unsignedIntFib getDimensionMapping( unsignedIntFib iDimensionNumber ) const;
 *
 * 	- void cRoot::generateNeededDomains()
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * call: tFibObject [MAX_SIZE] [ITERATIONS]
 *
 * parameters:
 * 	MAX_SIZE
 * 		The maximum size, which should not oversteped when the
 * 		Fib objects are generated.
 * 		The standardvalue is 1024.
 * 	ITERATIONS
 * 		The iterations for every parameterset. The generateFibObject() is
 * 		called I times for every parameterset.
 * 		Standardvalue is one.
 *
 */
/*
History:
20.12.2009  Oesterholz  created
01.08.2010  Oesterholz  cComment added
30.09.2010  Oesterholz  cRoot::generateNeededDomains() added
30.03.2011  Oesterholz  storing and restoring of compressed fib to binary stream
23.05.2011  Oesterholz  cIf added
25.08.2011  Oesterholz  cTypeUnderArea to cTypeSubarea
05.10.2011  Oesterholz  cExtObject included
16.11.2011  Oesterholz  cExtSubobject inserted
30.11.2011  Oesterholz  cFibDatabase inserted
30.12.2011  Oesterholz  Bugfix: comment has type char 'c'
02.01.2011  Oesterholz  cTypeSubarea changed to cTypeArea
16.01.2012  Oesterholz  cFibSet and cFibMatrix added
04.02.2012  Oesterholz  domain inheritance changed
*/

#include "version.h"

#include "cList.h"
#include "cPoint.h"
#include "cProperty.h"
#include "cArea.h"
#include "cFunction.h"
#include "cIf.h"
#include "cRoot.h"
#include "cTypeProperty.h"
#include "cTypeDimension.h"
#include "cTypeUnderFunction.h"
#include "cTypeArea.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainNaturalNumber.h"
#include "cDomainVector.h"
#include "cDomainVectorBasis.h"
#include "cFibDatabase.h"


#include <algorithm>
#include <iostream>
#include <fstream>
#include <ostream>
#include <cmath>
#include <ctime>

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif


using namespace fib;
using namespace std;


extern cFibElement * generateFibObject( unsigned int uiSize,
		list< pair< char, double > > liFractionOfFibElements,
		const list< cTypeProperty > & liPossiblePropertytyps,
		const unsigned int uiNumberOfDimensions,
		const unsigned int uiAverageSubRoots, const unsigned int uiAverageSubRootsDepth,
		const unsigned int uiNumberOfAverageInputVariables,
		const double dFractionsOfUsedVariables ,
		unsigned int uiMaxVectorElementNumber );


int testStructurRandom( unsigned long &ulTestphase, unsigned int uiMaxSize, unsigned int uiIterations, unsigned int uiTestType, unsigned int uiStepSize );

int testGetTypeName( unsigned long &ulTestphase );

int testRootEnviromentOnObject( cFibElement * pFibObject );

int testRootGenerateNeededDomains( cFibElement * pFibObject );


//parameters for the generator
const unsigned int uiNumberOfDimensions = 2;

list< cTypeProperty > liPossiblePropertytyps;
const unsigned int uiMaxVectorElementNumber = 1023;

list< pair< char, double > > liFractionOfFibElements;

//if true the stored file will be overwritten from the next stored file
bool bOverwriteFiles = true;


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time(NULL) );
	const time_t timeStart = time( 0 );
	
	liPossiblePropertytyps.push_back( cTypeProperty( cTypeProperty::COLOR_RGB, uiNumberOfDimensions ) );
	liPossiblePropertytyps.push_back( cTypeProperty( cTypeProperty::SOUND, uiNumberOfDimensions ) );
	
	liFractionOfFibElements.push_back( make_pair( 'p', 1.0 ) );
	liFractionOfFibElements.push_back( make_pair( 'y', 1.0 ) );
	liFractionOfFibElements.push_back( make_pair( 'a', 0.5 ) );
	liFractionOfFibElements.push_back( make_pair( 'f', 0.5 ) );
	liFractionOfFibElements.push_back( make_pair( 'i', 0.3 ) );
	liFractionOfFibElements.push_back( make_pair( 'l', 0.5 ) );
	liFractionOfFibElements.push_back( make_pair( 'o', 0.1 ) );
	liFractionOfFibElements.push_back( make_pair( 's', 0.1 ) );
	liFractionOfFibElements.push_back( make_pair( 'v', 0.1 ) );
	liFractionOfFibElements.push_back( make_pair( 'm', 0.1 ) );
	//TODO: more Fib elements
	
	//this must be last because it will be removed
	liFractionOfFibElements.push_back( make_pair( 'c', 0.2 ) );

	
	//* read input parameters
	unsigned int uiMaxSize = 1024;
	unsigned int uiIterations = 1;
	
	if ( argc >= 2 ){
		//one parameter given; get parameter max size
		uiMaxSize = atol( argv[1] );
		if ( uiMaxSize < 4 ){
			uiMaxSize = 4;
		}
	}
	
	if ( argc >= 3 ){
		//two parameter given; read parameter iterations
		uiIterations = atol( argv[2] );
		if ( uiIterations < 1 ){
			uiIterations = 1;
		}
	}

	cout<<endl<<"Running Test for Fib object non structure methods"<<endl;
	cout<<      "================================================="<<endl;

	iReturn += testGetTypeName( ulTestphase );
	
	//test basic root-enviroment methods
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 1, 4 );

	//test the cRoot::generateNeededDomains() method
	liFractionOfFibElements.pop_back();
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 2, 8 );


	cout<<endl<<endl<<"Test duration "<<(time( 0 ) - timeStart)<<" seconds (or "<<
		(time( 0 ) - timeStart)/60<<" minutes)"<<endl;
	if ( iReturn == 0 ){
	
		cout<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}



/**
 * This function tests the Fib structur methods in random generated Fib objects.
 *
 * methods tested with uiTestType=1 :
 * 	- list<longFib> getAllRootObjectIdentifiers() const;
 * 	- list<longFib> getAllDatabaseObjectIdentifiers() const;
 * 	- cRoot *getRootObject( longFib lIdentifier );
 * 	- list<longFib> getAllAccessibleRootObjectIdentifiers() const;
 * 	- cRoot *getAccessibleRootObject( longFib lIdentifier );
 * 	- cDomains getValidDomains() const;
 * 	- cDomains getValidValueDomains() const;
 * 	- unsignedIntFib getNumberOfDimensions() const;
 * 	- unsignedIntFib getDimensionMapping( unsignedIntFib iDimensionNumber ) const;
 *
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param uiMaxSize a number for the till wich size the Fib object
 * 	generator should generate Fib objects
 * @param uiIterations how mony Fib objects should be generated for each
 * 	set of parameters for the Fib object generator
 * @param uiTestType the type of thest that should be performed (see above)
 * @param uiStepSize the number with which the to generate size is multiplyted each step
 * @return the number of erros occured in the test
 */
int testStructurRandom( unsigned long &ulTestphase, unsigned int uiMaxSize,
		unsigned int uiIterations, unsigned int uiTestType = 1,
		unsigned int uiStepSize = 2 ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	ulTestphase++;
	switch ( uiTestType ){
		case 1:{
			cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing methods to check the enviroment generated by the rootelements on random generated Fib objects"<<endl;
		}break;
		case 2:{
			cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the generateNeededDomains() method of the class cRoot"<<endl;
		}break;

		default:
			cerr<<"Error: No test to evalue choosen"<<endl;
			iReturn++;
			return iReturn;
	}

	//generate random objects

	cout<<"The maximal size for generated Fib objects is: "<< uiMaxSize <<endl;
	cout<<"The number of iterations per parameterset is: "<< uiIterations <<endl;
	
	for ( unsigned int uiAverageSubRoots = 1 ; uiAverageSubRoots <= 16; uiAverageSubRoots *= 4 ){// * 3
	for ( unsigned int uiAverageSubRootsDepth = 1; uiAverageSubRootsDepth <= 4 ; uiAverageSubRootsDepth *= 2 ){// * 3
	for ( unsigned int uiNumberOfAverageInputVariables = 3; uiNumberOfAverageInputVariables <= 15;
			uiNumberOfAverageInputVariables = (unsigned int)(uiNumberOfAverageInputVariables * 2 + 1) ){// * 3
	for ( double dFractionsOfUsedVariables = 0.0; dFractionsOfUsedVariables <= 1.0; dFractionsOfUsedVariables += 0.5 ){// * 3
	for ( unsigned int uiSize = pow( uiAverageSubRoots, uiAverageSubRootsDepth ) * 4; uiSize < uiMaxSize; uiSize *= uiStepSize ){
	for ( unsigned int uiIteration = 1; uiIteration <= uiIterations; uiIteration++ ){
		
		const unsigned int uiFractionsOfUsedVariables =
			(unsigned int)(dFractionsOfUsedVariables * 100.0);

		cout<<endl<<"Generate Fib object with size="<< uiSize <<
			" uiIteration="<< uiIteration <<
			" dimensions="<< uiNumberOfDimensions <<
			" uiAverageSubRoots="<< uiAverageSubRoots <<
			" uiAverageSubRootsDepth="<< uiAverageSubRootsDepth <<
			" uiNumberOfAverageInputVariables="<< uiNumberOfAverageInputVariables<<
			" uiFractionsOfUsedVariables="<< uiFractionsOfUsedVariables <<
			" uiMaxVectorElementNumber="<<uiMaxVectorElementNumber<<" . "<<flush;
		
		cFibElement * pGeneratedfibObject = generateFibObject( uiSize,
			liFractionOfFibElements, liPossiblePropertytyps, uiNumberOfDimensions,
			uiAverageSubRoots, uiAverageSubRootsDepth,
			uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
			uiMaxVectorElementNumber );
		
		if ( pGeneratedfibObject ){
			cout<<" generated "<<endl;
		}else{
			cout<<endl;
			cerr<<"Error: Generated Fib object failed:"<<
				" Fib object with size="<< uiSize <<
				" uiIteration="<< uiIteration <<
				" dimensions="<< uiNumberOfDimensions <<
				" uiAverageSubRoots="<< uiAverageSubRoots <<
				" uiAverageSubRootsDepth="<< uiAverageSubRootsDepth <<
				" uiNumberOfAverageInputVariables="<< uiNumberOfAverageInputVariables<<
				" uiFractionsOfUsedVariables="<< uiFractionsOfUsedVariables <<
				" uiMaxVectorElementNumber="<<uiMaxVectorElementNumber<<" . "<<flush;
			iReturn++;
			
			continue;
		}
		unsigned int uiErrorsInTests = 0;
		switch ( uiTestType ){
			case 1:{
				uiErrorsInTests += testRootEnviromentOnObject( pGeneratedfibObject );
			}break;
			case 2:{
				uiErrorsInTests += testRootGenerateNeededDomains( pGeneratedfibObject );
			}break;

		}

		iReturn += uiErrorsInTests;

		if ( uiErrorsInTests != 0 ){
			//write Fib object wher orror occured to folder
			char szFileNameBuffer[256];
			sprintf ( szFileNameBuffer, "%s%sS%uD%uSR%uSRD%uIV%uVF%uMV%uR%uTT%u%s",
				DIR_OUTPUT, "objectError", uiSize,
				uiNumberOfDimensions, uiAverageSubRoots, uiAverageSubRootsDepth,
				uiNumberOfAverageInputVariables, uiFractionsOfUsedVariables,
				uiMaxVectorElementNumber, uiIteration, uiTestType ,".xml" );
			
			cerr<<"Error: The Fib object wher the error occured will be writen to the file \""<< szFileNameBuffer <<"\" ."<<endl;
			
			ofstream * pFile = new ofstream( szFileNameBuffer );
			
			bool bStoreSuccesfull = pGeneratedfibObject->storeXml( *pFile );
			delete pFile;
			
			if ( ! bStoreSuccesfull ){
	
				cerr<<"Error: Storing the data of the generated Fib object to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
				iReturn++;
			}
		}
		cFibElement::deleteObject( pGeneratedfibObject );

	}}}}}}
	
	return iReturn;
}



/**
 * This function tests the getTypeName() method.
 *
 * methods tested:
 * 	- string getTypeName( char cType );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cPoint
 * 	- cProperty
 * 	- cList
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testGetTypeName( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cPoint point;
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing getTypeName()"<<endl<<endl;
	
	if ( point.getTypeName('u') != "unknown" ){
		cerr<<"Error: For the type 'u' "<< point.getTypeName('u') <<
			" was given back and not unknown. "<< endl;
		iReturn++;
	}
	if ( point.getTypeName('p') != "point" ){
		cerr<<"Error: For the type 'p' "<< point.getTypeName('p') <<
			" was given back and not point. "<< endl;
		iReturn++;
	}
	if ( point.getTypeName('y') != "property" ){
		cerr<<"Error: For the type 'y' "<< point.getTypeName('y') <<
			" was given back and not property. "<< endl;
		iReturn++;
	}
	if ( point.getTypeName('c') != "comment" ){
		cerr<<"Error: For the type 'c' "<< point.getTypeName('c') <<
			" was given back and not comment. "<< endl;
		iReturn++;
	}
	if ( point.getTypeName('a') != "area" ){
		cerr<<"Error: For the type 'a' "<< point.getTypeName('a') <<
			" was given back and not area. "<< endl;
		iReturn++;
	}
	if ( point.getTypeName('f') != "function" ){
		cerr<<"For the type 'f' "<< point.getTypeName('f') <<
			" was given back and not function. "<< endl;
		iReturn++;
	}
	if ( point.getTypeName('i') != "if" ){
		cerr<<"Error: For the type 'i' "<< point.getTypeName('i') <<
			" was given back and not if. "<< endl;
		iReturn++;
	}
	if ( point.getTypeName('o') != "extern object" ){
		cerr<<"Error: For the type 'o' "<< point.getTypeName('o') <<
			" was given back and not extern object. "<< endl;
		iReturn++;
	}
	if ( point.getTypeName('s') != "extern subobject" ){
		cerr<<"Error: For the type 's' "<< point.getTypeName('s') <<
			" was given back and not extern subobject. "<< endl;
		iReturn++;
	}
	if ( point.getTypeName('v') != "set-element" ){
		cerr<<"Error: For the type 'v' "<< point.getTypeName('v') <<
			" was given back and not set-element. "<< endl;
		iReturn++;
	}
	if ( point.getTypeName('m') != "matrix element" ){
		cerr<<"Error: For the type 'm' "<< point.getTypeName('m') <<
			" was given back and not matrix element. "<< endl;
		iReturn++;
	}
	if ( point.getTypeName('r') != "root" ){
		cerr<<"Error: For the type 'r' "<< point.getTypeName('r') <<
			" was given back and not root. "<< endl;
		iReturn++;
	}

	if ( point.getTypeName('x') != "unknown" ){
		cerr<<"Error: For the type 'x' "<< point.getTypeName('x') <<
			" was given back and not unknown. "<< endl;
		iReturn++;
	}
	if ( iReturn == 0){
		cout<<"The method getTypeName() works correct."<<endl;
	}
	return iReturn;
}


/**
 * This functions compares tow sub -root -element.
 *
 * @param paFirstSubRoot the first sub -root -element to compare
 * @param paSecondSubRoot the second sub -root -element to compare
 * @return true if the sub -root -element of the first pair has an lower
 * 	Fib element number than the sub -root -element of the second pair,
 * 	else false
 */
bool lowerFibElementNumber( pair<longFib, cRoot*> paFirstSubRoot,
		pair<longFib, cRoot*> paSecondSubRoot ){

	return (paFirstSubRoot.second->getNumberOfElement() <
		paSecondSubRoot.second->getNumberOfElement() );
}


/**
 * This function tests the root enviroment methods for an given Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- list<longFib> getAllDatabaseObjectIdentifiers() const
 * 	- list<longFib> getAllRootObjectIdentifiers() const;
 * 	- cRoot *getRootObject( longFib lIdentifier );
 * 	- list<longFib> getAllAccessibleRootObjectIdentifiers() const;
 * 	- cRoot *getAccessibleRootObject( longFib lIdentifier );
 * 	- cDomains getValidDomains() const;
 * 	- cDomains getValidValueDomains() const;
 * 	- unsignedIntFib getNumberOfDimensions() const;
 * 	- unsignedIntFib getDimensionMapping( unsignedIntFib iDimensionNumber ) const;
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cPoint
 * 	- cProperty
 * 	- cList
 *
 * @param fibObject a pointer to the Fib object to test
 * @return the number of erros occured in the test
 */
int testRootEnviromentOnObject( cFibElement * pFibObject ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
		
	//when database is implemented
	list<longFib> liDBIdentifiers;
	//check the getInstance() methode from cFibDatabase
	cFibDatabase * pFibDatabase = cFibDatabase::getInstance();
	if ( pFibDatabase != NULL ){
		liDBIdentifiers = pFibDatabase->getAllDatabaseObjectIdentifiers();
	}
	
	//evalue all rootobject identifiers of the Fib object
	list< pair<longFib, cRoot*> > liAllRootPairs;
	for ( cRoot * pActualRoot = (cRoot *)pFibObject; pActualRoot != NULL;
			pActualRoot = (cRoot *)(pActualRoot->getNextFibElement( 'r' )) ){
		
		unsignedIntFib uiSubRoots = pActualRoot->getNumberOfSubRootObjects();
		for ( unsignedIntFib uiActualSubRoot = 1; uiActualSubRoot <= uiSubRoots;
				uiActualSubRoot++ ){
			liAllRootPairs.push_back( pActualRoot->getSubRootObject( uiActualSubRoot ) );
		}
	}
	liAllRootPairs.sort( lowerFibElementNumber );
	
	list<longFib> liAllRootIdentifiers;
	longFib lMaxIdentifier = 0;
	longFib lMinIdentifier = 0;
	for ( list< pair<longFib, cRoot*> >::iterator itrIdentifier = liAllRootPairs.begin();
			itrIdentifier != liAllRootPairs.end(); itrIdentifier++ ){
		
		liAllRootIdentifiers.push_back( itrIdentifier->first );
		
		lMaxIdentifier = std::max( lMaxIdentifier, itrIdentifier->first );
		lMinIdentifier = std::min( lMinIdentifier, itrIdentifier->first );
	}
	liAllRootIdentifiers.insert( liAllRootIdentifiers.end(),
		liDBIdentifiers.begin(), liDBIdentifiers.end() );
	for ( list< longFib >::iterator itrIdentifier = liDBIdentifiers.begin();
			itrIdentifier != liDBIdentifiers.end(); itrIdentifier++ ){
		
		lMaxIdentifier = std::max( lMaxIdentifier, (*itrIdentifier) );
		lMinIdentifier = std::min( lMinIdentifier, (*itrIdentifier) );
	}
	
	cout<<"Count of all sub -root -objects: "<< liAllRootIdentifiers.size() <<
		"  (max="<< lMaxIdentifier <<" min="<< lMinIdentifier <<" )"<<endl;
	
	/*add domains to the sub -root -objects so they can be identified
	domains with property type 1000 + x and domain cDomainNaturalNumberBit( X )
	value domains with property type 2000 + x and domain cDomainNaturalNumberBit( 1000 + X )
	*/
	cTypeProperty typePropertyMain( 1000 );
	cDomainNaturalNumber naturalNumberMain( 0 );
	((cRoot*)pFibObject)->getDomains()->addDomain(
		typePropertyMain, naturalNumberMain );
	
	cTypeProperty typeValuePropertyMain( 2000 );
	cDomainNaturalNumberBit valueNaturalNumberBitMain( 1000 );
	((cRoot*)pFibObject)->getValueDomains()->addDomain(
		typeValuePropertyMain, valueNaturalNumberBitMain );
	
	unsigned int uiSubRootNumber = 1;
	for ( list< pair<longFib, cRoot*> >::iterator itrIdentifier = liAllRootPairs.begin();
			itrIdentifier != liAllRootPairs.end();
			itrIdentifier++, uiSubRootNumber++ ){
		
		cTypeProperty typeProperty( 1000 + uiSubRootNumber );
		cDomainNaturalNumber naturalNumber( uiSubRootNumber );
		((cRoot*)itrIdentifier->second)->getDomains()->addDomain(
			typeProperty, naturalNumber );
		
		cTypeProperty typeValueProperty( 2000 + uiSubRootNumber );
		cDomainNaturalNumber valueNaturalNumber( 1000 + uiSubRootNumber );
		((cRoot*)pFibObject)->getValueDomains()->addDomain(
			typeValueProperty, valueNaturalNumber );
		
		
		cTypeDimension typeDimensionMain( uiSubRootNumber );
		((cRoot*)itrIdentifier->second)->getDomains()->addDomain(
			typeDimensionMain, naturalNumber );
	}
	
	//choos some random elementpoints and check the enviroment from ther
	for ( unsigned int uiIteration = 1;
			uiIteration <= uiNumberOfAllFibElements / 100 + 10; uiIteration++ ){
		
		unsigned int uiNumberOfCallingFibElement = rand() % uiNumberOfAllFibElements + 1;
		cFibElement * pCallingFibElement = pFibObject->getFibElement(
			uiNumberOfCallingFibElement );
		const cFibElement * pCallingFibElementConst = pCallingFibElement;
		
		cout<<"Testing the root-enviromen methods from the "<<
			pCallingFibElement->getNumberOfElement() <<" of the type "<<
			pCallingFibElement->getType() <<" ."<<endl;
		
		//check getAllDatabaseObjectIdentifiers()
		list<longFib> liLocaleDBIdentifiers =
			pCallingFibElementConst->getAllDatabaseObjectIdentifiers();
		if ( liLocaleDBIdentifiers != liDBIdentifiers ){
			cerr<<"Error: Wrong database identifiers are given back."<<endl;
			cerr<<"  count correct database identifiers:"<< liDBIdentifiers.size() <<
				"  returned database identifiers: "<< liLocaleDBIdentifiers.size() <<endl;
			iReturn++;
		}
		
		//check getAllRootObjectIdentifiers()
		list<longFib> liLocaleAllRootIdentifiers =
			pCallingFibElementConst->getAllRootObjectIdentifiers();
		if ( liLocaleAllRootIdentifiers != liAllRootIdentifiers ){
			cerr<<"Error: Wrong all identifiers are given back."<<endl;
			cerr<<"  count correct all identifiers:"<< liLocaleAllRootIdentifiers.size() <<
				"  returned all identifiers: "<< liAllRootIdentifiers.size() <<endl;
			iReturn++;
		}
		//check getRootObject()
		for ( list< pair<longFib, cRoot*> >::iterator itrIdentifier = liAllRootPairs.begin();
				itrIdentifier != liAllRootPairs.end(); itrIdentifier++ ){
			
			cRoot * pActualSubRoot = pCallingFibElement->getRootObject(
				itrIdentifier->first );
			if ( pActualSubRoot != itrIdentifier->second ){
				cerr<<"Error: Wrong sub -root -object for the identifier "<<
					itrIdentifier->first <<" is given back."<<
					"(wrong="<< pActualSubRoot <<" correct="<<
					itrIdentifier->second <<")"<<endl;
				iReturn++;
			}
		}
		cRoot * pNoSubRoot = pCallingFibElement->getRootObject( lMaxIdentifier + 1 );
		if ( pNoSubRoot ){
			cerr<<"Error: A sub -root -object for the identifier "<<
				lMaxIdentifier + 1 <<" is given back, but it shouldn't "<<
				"(NULL would be correct)."<<endl;
			iReturn++;
		}
		pNoSubRoot = pCallingFibElement->getRootObject( lMinIdentifier - 1 );
		if ( pNoSubRoot ){
			cerr<<"Error: A sub -root -object for the identifier "<<
				lMinIdentifier - 1 <<" is given back, but it shouldn't "<<
				"(NULL would be correct)."<<endl;
			iReturn++;
		}
		//check getAllAccessibleRootObjectIdentifiers()
		list<longFib> liAllAccessibleRoot = pCallingFibElementConst->
			getAllAccessibleRootObjectIdentifiers();
		//check all sub -root identifiers after the actual callingelement
		cRoot * pActualRoot = NULL;
		if ( pCallingFibElement->getType() == 'r' ){
			pActualRoot = (cRoot *)(pCallingFibElement);
		}else{
			pActualRoot = (cRoot *)(pCallingFibElement->getFibElement( 'r', -1));
		}
		unsignedIntFib uiCallingRootElementNumber = pActualRoot->getNumberOfElement();
		
		list<longFib>::iterator itrNextAccessibeRoot = liAllAccessibleRoot.begin();
		/*liSuperiorRoots -> all roots superior to the calling Fib element,
		the lower the root the farther back it is in the list*/
		list<cRoot*> liSuperiorRoots;
		const cRoot * pRootForCallingFibElement = pActualRoot;
		
		for ( ;pActualRoot != NULL;
				pActualRoot = (cRoot *)(pActualRoot->getSuperiorFibElement()) ){
			
			liSuperiorRoots.push_front( pActualRoot );
			
			unsignedIntFib uiSubRoots = pActualRoot->getNumberOfSubRootObjects();
			for ( unsignedIntFib uiActualSubRoot = 1; uiActualSubRoot <= uiSubRoots;
					uiActualSubRoot++ ){
				
				pair<longFib, cRoot*> paActualSubRoot = pActualRoot->
					getSubRootObject( uiActualSubRoot );
				
				if ( uiCallingRootElementNumber
						< paActualSubRoot.second->getNumberOfElement() ){
					
					if ( itrNextAccessibeRoot == liAllAccessibleRoot.end() ){
						cerr<<"Error: The accessible sub -root with identifier "<<
							paActualSubRoot.first <<" should be found, but "<<
							"no identifier was found."<<endl;
						iReturn++;
					}else if ( paActualSubRoot.first == (*itrNextAccessibeRoot) ){
						itrNextAccessibeRoot++;
					}else{
						cerr<<"Error: The accessible sub -root with identifier "<<
							paActualSubRoot.first <<" should be found, but found "<<
							"was the identifier "<< (*itrNextAccessibeRoot) <<"."<<endl;
						iReturn++;
					}
				}
			}
		}
		
		//check getAccessibleRootObject()
		for ( list< pair<longFib, cRoot*> >::iterator itrIdentifier = liAllRootPairs.begin();
				itrIdentifier != liAllRootPairs.end(); itrIdentifier++ ){
			
			cRoot * pActualSubRoot = pCallingFibElement->getAccessibleRootObject(
				itrIdentifier->first );
				
			list<longFib>::iterator itrFoundAccessible = find(
				liAllAccessibleRoot.begin(), liAllAccessibleRoot.end(),
				itrIdentifier->first);
			
			if ( itrFoundAccessible != liAllAccessibleRoot.end() ){
				//sub -root -object is accessible
				if ( pActualSubRoot != itrIdentifier->second ){
					cerr<<"Error: Wrong accessible sub -root -object for the identifier "<<
						itrIdentifier->first <<" is given back."<<
						"(wrong="<< pActualSubRoot <<" correct="<<
						itrIdentifier->second <<")"<<endl;
					iReturn++;
				}
			}else{//sub -root -object is not accessible
				if ( pActualSubRoot != NULL ){
					cerr<<"Error: A accessible sub -root -object for the identifier "<<
						itrIdentifier->first <<" is given back."<<
						"(wrong="<< pActualSubRoot <<" correct=NULL)"<<endl;
					iReturn++;
				}
			}
		}
		pNoSubRoot = pCallingFibElement->getAccessibleRootObject( lMaxIdentifier + 1 );
		if ( pNoSubRoot ){
			cerr<<"Error: A accessible sub -root -object for the identifier "<<
				lMaxIdentifier + 1 <<" is given back, but it shouldn't "<<
				"(NULL would be correct)."<<endl;
			iReturn++;
		}
		pNoSubRoot = pCallingFibElement->getAccessibleRootObject( lMinIdentifier - 1 );
		if ( pNoSubRoot ){
			cerr<<"Error: A accessible sub -root -object for the identifier "<<
				lMinIdentifier - 1 <<" is given back, but it shouldn't "<<
				"(NULL would be correct)."<<endl;
			iReturn++;
		}
		
		//check methods for getting the domains
		//evalue the domains and valuedomains
		cDomains accessibleDomains;
		cDomains accessibleValueDomains;
		for ( list<cRoot*>::iterator itrRoot = liSuperiorRoots.begin();
				itrRoot != liSuperiorRoots.end(); itrRoot++ ){
			
			const unsigned int uiNumberOfDomains = (*itrRoot)->getDomains()->
				getNumberOfDomains();
			for ( unsigned int uiActualDomain = 1;
					uiActualDomain <= uiNumberOfDomains; uiActualDomain++ ){
				
				if ( ( pRootForCallingFibElement == (*itrRoot) ) ||
						((*itrRoot)->getDomains()->getType( uiActualDomain ))->isInherited() ){
					//just add domains which are inherited for superior roots for calling root
					accessibleDomains.addDomain(
						*((*itrRoot)->getDomains()->getType( uiActualDomain ) ),
						(*itrRoot)->getDomains()->getDomain( uiActualDomain ) );
				}
			}
			const unsigned int uiNumberOfValueDomains = (*itrRoot)->
				getValueDomains()->getNumberOfDomains();
			for ( unsigned int uiActualDomain = 1;
					uiActualDomain <= uiNumberOfValueDomains; uiActualDomain++ ){
				
				if ( ( pRootForCallingFibElement == (*itrRoot) ) ||
						((*itrRoot)->getValueDomains()->getType( uiActualDomain ) )->isInherited() ){
					//just add domains which are inherited for superior roots for calling root
					accessibleValueDomains.addDomain(
						*((*itrRoot)->getValueDomains()->getType( uiActualDomain ) ),
						(*itrRoot)->getValueDomains()->getDomain( uiActualDomain ) );
				}
			}
		}
		for ( unsigned int uiActualDomain = 1; uiActualDomain <=
				accessibleDomains.getNumberOfDomains(); uiActualDomain++ ){
			
			if ( accessibleValueDomains.getDomainForElement(
					*(accessibleDomains.getType( uiActualDomain ) ) ) == NULL ){
				//add missing domain to the value domains
				accessibleValueDomains.addDomain(
					*(accessibleDomains.getType( uiActualDomain ) ),
					accessibleDomains.getDomain( uiActualDomain ) );
			}
		}

		cDomains validDomains = pCallingFibElement->getValidDomains();
		if ( ! (validDomains == accessibleDomains) ){
			cerr<<"Error: The valid domains are not correct."<<endl;
			cerr<<"   Ther are "<< validDomains.getNumberOfDomains() <<
				" domains given back, but "<<
				accessibleDomains.getNumberOfDomains() <<
				" would be correct." <<endl;
			{//store the domains
				static unsigned long ulDomainNumber = 1;
				char szFileNameBuffer[256];
				sprintf ( szFileNameBuffer, "%s%s%lu%s",
					DIR_OUTPUT, "domains", ulDomainNumber ,"Correct.xml" );
				cerr<<"Error: The correct domains will be writen to the file \""<< szFileNameBuffer <<"\" ."<<endl;
				ofstream * pFile = new ofstream( szFileNameBuffer );
				accessibleDomains.storeXml( *pFile );
				delete pFile;
				sprintf ( szFileNameBuffer, "%s%s%lu%s",
					DIR_OUTPUT, "domains", ulDomainNumber ,"Wrong.xml" );
				cerr<<"Error: The wrong domains will be writen to the file \""<< szFileNameBuffer <<"\" ."<<endl;
				pFile = new ofstream( szFileNameBuffer );
				validDomains.storeXml( *pFile );
				delete pFile;
				ulDomainNumber++;
			}
			iReturn++;
		}
		cDomains validValueDomains = pCallingFibElement->getValidValueDomains();
		if ( ! (validValueDomains == accessibleValueDomains) ){
			cerr<<"Error: The valid value domains are not correct."<<endl;
			cerr<<"   Ther are "<< validValueDomains.getNumberOfDomains() <<
				" domains given back, but "<<
				accessibleValueDomains.getNumberOfDomains() <<
				" would be correct." <<endl;
			iReturn++;
			{//store the domains
				static unsigned long ulValueDomainNumber = 1;
				char szFileNameBuffer[256];
				sprintf ( szFileNameBuffer, "%s%s%lu%s",
					DIR_OUTPUT, "valueDomains", ulValueDomainNumber ,"Correct.xml" );
				cerr<<"Error: The correct value domains will be writen to the file \""<< szFileNameBuffer <<"\" ."<<endl;
				ofstream * pFile = new ofstream( szFileNameBuffer );
				accessibleValueDomains.storeXml( *pFile );
				delete pFile;
				sprintf ( szFileNameBuffer, "%s%s%lu%s",
					DIR_OUTPUT, "valueDomains", ulValueDomainNumber ,"Wrong.xml" );
				cerr<<"Error: The wrong value domains will be writen to the file \""<< szFileNameBuffer <<"\" ."<<endl;
				pFile = new ofstream( szFileNameBuffer );
				validValueDomains.storeXml( *pFile );
				delete pFile;
				ulValueDomainNumber++;
			}
		}
		//check getNumberOfDimensions()
		cTypeDimension typeDimension;
		cDomainVectorBasis * pDomainDimension = ((cDomainVectorBasis*)
			( accessibleDomains.getDomainForElement( typeDimension ) ) );
		unsigned int uiNumberOfDimensions =
			pCallingFibElementConst->getNumberOfDimensions();
		if ( pDomainDimension == NULL ){
			cerr<<"Error: No dimension domain."<<endl;
			iReturn++;
		}else if ( pDomainDimension->getNumberOfElements() != uiNumberOfDimensions ){
			cerr<<"Error: getNumberOfDimensions() returns "<<
				uiNumberOfDimensions <<" for the number of dimensions, but "<<
				pDomainDimension->getNumberOfElements() <<" is correct."<<endl;
			iReturn++;
		}
		unsignedIntFib uiDimensionMapping = pCallingFibElementConst->
			getDimensionMapping( uiNumberOfDimensions );
		if ( uiDimensionMapping != uiNumberOfDimensions ){
			cerr<<"Error: The "<< uiNumberOfDimensions <<" dimension mapping is "<<
				uiDimensionMapping <<" and not "<< uiNumberOfDimensions <<" ."<<endl;
			iReturn++;
		}
		uiDimensionMapping = pCallingFibElementConst->getDimensionMapping(
			uiNumberOfDimensions + 1 );
		if ( uiDimensionMapping != 0 ){
			cerr<<"Error: The "<< uiNumberOfDimensions + 1 <<" dimension mapping is "<<
				uiDimensionMapping <<" and not "<< 0 <<" ."<<endl;
			iReturn++;
		}
	}

	return iReturn;
}



/**
 * This function tests the generateNeededDomains() method for an given
 * Fib object.
 *
 * methods tested:
 * 	- void cRoot::generateNeededDomains()
 *
 * @param fibObject a pointer to the Fib object to test
 * @return the number of erros occured in the test
 */
int testRootGenerateNeededDomains( cFibElement * pFibObject ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	if ( pFibObject->getType() != 'r' ){
		cerr<<"Error: The top most Fib element is not root -element."<<endl;
		iReturn++;
		return iReturn;
	}
	//remove the area and function domains from all root -elements
	cRoot * pMasterRoot = (cRoot*)pFibObject;
	for ( cRoot * pRoot = pMasterRoot; pRoot != NULL;
			pRoot = (cRoot*)(pRoot->getNextFibElement( 'r')) ){
		
		pRoot->getDomains()->deleteDomain( cTypeUnderFunction() );
		pRoot->getDomains()->deleteDomain( cTypeArea() );
	}
	
	//call generateNeededDomains() on the master -root -element
	cout<<"Generate the needed domains for the Fib object. "<<endl;
	pMasterRoot->generateNeededDomains();
	
	//store and restore the generated fib object in the compressed file format
	static unsigned int uiFileIteration = 0;
	if ( ! bOverwriteFiles ){
		uiFileIteration++;
	}

	char szFileNameBuffer[256];
	sprintf ( szFileNameBuffer, "%s%s%u%s", DIR_OUTPUT, "store", uiFileIteration ,".fib" );
	
	ofstream * pOutFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cout<<"Storing Fib object in the compressed Fib format to the file "<< szFileNameBuffer <<" . "<<endl;

	bool bStoreSuccesfull = pFibObject->store( *pOutFile );
	delete pOutFile;
	
	if ( ! bStoreSuccesfull ){

		cerr<<"Error: Storing the data to compressed Fib format of the generated Fib object to the file \""<<
			szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	ifstream inFile( szFileNameBuffer, ios_base::in | ios_base::binary );

	intFib outStatus = 0;
	cFibElement * pRestoredFibObject = cFibElement::restore( inFile , &outStatus );
	
	if ( outStatus == 0 ){
		cout<<"Restoring Fib object in the compressed Fib format from the file "<<
			szFileNameBuffer <<" successfull. "<<endl;
	}else{
		cerr<<"Error: Restoring Fib object in the compressed Fib format from the file "<<
			szFileNameBuffer <<" not successfull. (return status="<< outStatus <<")"<<endl;
		iReturn++;
	}
	
	//check if the restored Fib object is equal to the stored Fib object
	if ( pRestoredFibObject ){
		if ( ! pFibObject->equal( *pRestoredFibObject ) ){
			cerr<<"Error: The restore Fib object dosn't equal the stored Fib object."<<endl;
			iReturn++;
			
			static unsigned int uiRestoreIteration = 1;
			sprintf ( szFileNameBuffer, "%s%s%u%s%s", DIR_OUTPUT, "store", uiRestoreIteration, "Error" ,".xml" );
			ofstream * pOutFileXml = new ofstream( szFileNameBuffer );
			cout<<"Storing restored Fib object in the Xml -format to the file "<< szFileNameBuffer <<" . "<<endl;
			pRestoredFibObject->storeXml( *pOutFileXml );
			delete pOutFileXml;
			uiRestoreIteration++;
		}
		cFibElement::deleteObject( pRestoredFibObject );
	}else{
		cerr<<"Error: No Fib object restored ."<<endl;
		iReturn++;
	}
	
	return iReturn;
}














