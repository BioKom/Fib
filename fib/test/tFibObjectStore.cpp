/**
 * @file tFibObjectStore
 * file name: tFibObjectStore.cpp
 * @author Betti Oesterholz
 * @date 30.01.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for testing storing and restoring Fib-objects.
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
 * This test is for testing storing and restoring Fib-objects.
 * For testing storing Fib-objects a Fib-object is stored, than
 * restored and compared with the stored Fib-object.
 *
 *
 * What's tested of class cFibElement -class:
 * 	- virtual bool storeXml( ostream &stream ) const;
 * 	- static cFibElement *restoreXml( istream &stream, intFib *outStatus=NULL );
 * 	-- static cFibElement *restoreXml( const TiXmlNode * pXmlNode, intFib *outStatus=NULL );(indirect with restoreXml( istream, ... ))
 * 	- bool store( ostream &stream ) const;
 * 	- static cFibElement *restore( istream &stream, intFib *outStatus=NULL );
 *
 *
 * Fib-elements tested:
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
 * call: tFibObjectStore [MAX_SIZE] [ITERATIONS]
 *
 * parameters:
 * 	MAX_SIZE
 * 		The maximum size, which should not oversteped when the
 * 		Fib-objects are generated.
 * 		The standardvalue is 1024.
 * 	ITERATIONS
 * 		The iterations for every parameterset. The generateFibObject() is
 * 		called I times for every parameterset.
 * 		Standardvalue is one.
 *
 *
 */
/*
History:
20.12.2009  Oesterholz  created
24.04.2010  Oesterholz  cFunction included
01.08.2010  Oesterholz  cComment added for the Xml-format
30.03.2011  Oesterholz  storing and restoring of compressed fib to binary stream
23.05.2011  Oesterholz  cIf included
18.07.2011  Oesterholz  compressed storing for comments added
28.09.2011  Oesterholz  cExtObject included
16.11.2011  Oesterholz  cExtSubobject inserted
16.01.2012  Oesterholz  cFibSet und cFibMatrix inserted
*/

#include "version.h"

#include "cList.h"
#include "cPoint.h"
#include "cProperty.h"
#include "cRoot.h"
#include "cTypeProperty.h"
#include "cTypeDimension.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainNaturalNumber.h"
#include "cDomainVector.h"
#include "cDomainVectorBasis.h"


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

int testStoreXmlOnObject( cFibElement * pFibObject );
int testStoreOnObject( cFibElement * pFibObject );



//parameters for the generator
list< pair< char, double > > liFractionOfFibElements;


//if true the stored file will be overwritten from the next stored file
bool bOverwriteFiles = true;



int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time(NULL) );
	const time_t timeStart = time( 0 );
	
	liFractionOfFibElements.push_back( make_pair( 'p', 1.0 ) );
	liFractionOfFibElements.push_back( make_pair( 'y', 1.0 ) );
	liFractionOfFibElements.push_back( make_pair( 'l', 0.4 ) );
	liFractionOfFibElements.push_back( make_pair( 'a', 0.5 ) );
	liFractionOfFibElements.push_back( make_pair( 'f', 0.5 ) );
	liFractionOfFibElements.push_back( make_pair( 'i', 0.3 ) );
	liFractionOfFibElements.push_back( make_pair( 'c', 0.2 ) );
	liFractionOfFibElements.push_back( make_pair( 'o', 0.1 ) );
	liFractionOfFibElements.push_back( make_pair( 's', 0.1 ) );
	liFractionOfFibElements.push_back( make_pair( 'v', 0.1 ) );
	liFractionOfFibElements.push_back( make_pair( 'm', 0.1 ) );
	//TODO: more Fib-elements

	
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

	cout<<endl<<"Running Test for Fib-object storing and restoring methods"<<endl;
	cout<<      "========================================================="<<endl;
	
	//test storeXml() and restoreXml()
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 1, 2 );
	//test store() and restore()
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 2, 2 );


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
 * This function tests the Fib-structur methods in random generated Fib-objects.
 *
 * methods tested with uiTestType=1 :
 * 	- virtual bool storeXml( ostream &stream ) const;
 * 	- static cFibElement *restoreXml( istream &stream, intFib *outStatus=NULL );
 * 	-- static cFibElement *restoreXml( const TiXmlNode * pXmlNode, intFib *outStatus=NULL ); (indirect with restoreXml( istream, ... ))
 *
 * methods tested with uiTestType=2 :
 * 	- virtual bool store( ostream &stream ) const;
 * 	- static cFibElement *restore( istream &stream, intFib *outStatus=NULL );
 *
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param uiMaxSize a number for the till wich size the Fib-object
 * 	generator should generate Fib-objects
 * @param uiIterations how mony Fib-objects should be generated for each
 * 	set of parameters for the Fib-object generator
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
			cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing methods for storing and restoring in the xml -format"<<endl;
		}break;
		case 2:{
			cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing methods for storing and restoring in the compressedformat"<<endl;
		}break;

		default:
			cerr<<"No test to evalue choosen"<<endl;
			iReturn++;
			return iReturn;
	}

	//generate random objects

	cout<<"The maximal size for generated Fib-objects is: "<< uiMaxSize <<endl;
	cout<<"The number of iterations per parameterset is: "<< uiIterations <<endl;
	
	for ( unsigned int uiAverageSubRoots = 1 ; uiAverageSubRoots <= 16; uiAverageSubRoots *= 4 ){// * 3
	for ( unsigned int uiAverageSubRootsDepth = 1; uiAverageSubRootsDepth <= 4 ; uiAverageSubRootsDepth *= 2 ){// * 3
	for ( unsigned int uiNumberOfAverageInputVariables = 3; uiNumberOfAverageInputVariables <= 15;
			uiNumberOfAverageInputVariables = (unsigned int)(uiNumberOfAverageInputVariables * 2 + 1) ){// * 3
	for ( double dFractionsOfUsedVariables = 0.0; dFractionsOfUsedVariables <= 1.0; dFractionsOfUsedVariables += 0.5 ){// * 3
	for ( unsigned int uiSize = pow( uiAverageSubRoots, uiAverageSubRootsDepth ) * 4; uiSize < uiMaxSize; uiSize *= uiStepSize ){
	for ( unsigned int uiIteration = 1; uiIteration <= uiIterations; uiIteration++ ){
		
		const unsigned int uiNumberOfDimensions = (rand() % 4) + 1;
		const unsigned int uiMaxVectorElementNumber = (rand() % 256 + 2) * (rand() % 256 + 2);
		const unsigned int uiNumberOfPropertyTyps = (rand() % 6) + 1;

		const cTypeProperty pPossiblePropertytyps[] = {
			cTypeProperty( 1, uiNumberOfDimensions ),
			cTypeProperty( 2, uiNumberOfDimensions ),
			cTypeProperty( 100, uiNumberOfDimensions ),
			cTypeProperty( 200, uiNumberOfDimensions ),
			cTypeProperty( 300, uiNumberOfDimensions ),
			cTypeProperty( 301, uiNumberOfDimensions ),
			cTypeProperty( 305, uiNumberOfDimensions ),
			cTypeProperty( 310, uiNumberOfDimensions ),
			cTypeProperty( 311, uiNumberOfDimensions ),
			cTypeProperty( 312, uiNumberOfDimensions ),
			cTypeProperty( 400, uiNumberOfDimensions ),
			cTypeProperty( 410, uiNumberOfDimensions ),
			cTypeProperty( 600, uiNumberOfDimensions ),
			//no existing typs
			cTypeProperty( 46, uiNumberOfDimensions ),
			cTypeProperty( 0, uiNumberOfDimensions )
		};
		//generate possible propertytyps
		list< cTypeProperty > liPossiblePropertytyps( pPossiblePropertytyps,
			pPossiblePropertytyps + sizeof( pPossiblePropertytyps ) / sizeof( cTypeProperty ) );
		while ( uiNumberOfPropertyTyps < liPossiblePropertytyps.size() ){
			//choos random propertytyp and erase it
			unsigned int uiRandom = rand() % liPossiblePropertytyps.size();
			list< cTypeProperty >::iterator itrChoosenProperty = liPossiblePropertytyps.begin();
			while ( uiRandom != 0 ){
				uiRandom--;
				itrChoosenProperty++;
			}
			liPossiblePropertytyps.erase( itrChoosenProperty );
		}

		const unsigned int uiFractionsOfUsedVariables =
			(unsigned int)(dFractionsOfUsedVariables * 100.0);

		cout<<endl<<"Generate Fib-object with size="<< uiSize <<
			" uiIteration="<< uiIteration <<
			" dimensions="<< uiNumberOfDimensions <<
			" uiAverageSubRoots="<< uiAverageSubRoots <<
			" uiAverageSubRootsDepth="<< uiAverageSubRootsDepth <<
			" uiNumberOfAverageInputVariables="<< uiNumberOfAverageInputVariables<<
			" uiFractionsOfUsedVariables="<< uiFractionsOfUsedVariables <<
			" uiMaxVectorElementNumber="<<uiMaxVectorElementNumber<<" . "<<endl<<flush;
		
		cout<<"And the properties: ";
		for ( list< cTypeProperty >::iterator itrProperty = liPossiblePropertytyps.begin();
				itrProperty != liPossiblePropertytyps.end(); itrProperty++ ){
			cout<< itrProperty->getNameOfProperty() << "; ";
		}
		cout<<endl;
		
		cFibElement * pGeneratedfibObject = generateFibObject( uiSize,
			liFractionOfFibElements, liPossiblePropertytyps, uiNumberOfDimensions,
			uiAverageSubRoots, uiAverageSubRootsDepth,
			uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
			uiMaxVectorElementNumber );
		
		/*add random domains*/
		//better random access on propertytyps
		const vector< cTypeProperty > vecPossiblePropertytyps(
			liPossiblePropertytyps.begin(), liPossiblePropertytyps.end() );
		
		for ( cRoot * pActualRoot = (cRoot *)pGeneratedfibObject; pActualRoot != NULL;
				pActualRoot = (cRoot *)(pActualRoot->getNextFibElement( 'r' )) ){
			
			unsigned int uiDomainsToAdd = rand() % (uiNumberOfPropertyTyps * 2);
			
			for ( unsigned int uiAddedDomainCount = 0;
					uiAddedDomainCount < uiDomainsToAdd; uiAddedDomainCount++ ){
				//choos random propertytype
				unsigned int uiChoosenPropertytype = rand() % uiNumberOfPropertyTyps;
				
				//generate random Domain
				vector<cDomainSingle*> vecDomainElements;
				
				cDomain * pDomainStandard = vecPossiblePropertytyps[
					uiChoosenPropertytype ].getStandardDomain();
				const unsigned int uiNumberOfVectorElements =
					((cDomainVectorBasis*)pDomainStandard)->getNumberOfElements();
				delete pDomainStandard;
				for ( unsigned int uiDomainElement = 0;
						uiDomainElement < uiNumberOfVectorElements; uiDomainElement++ ){
					
					vecDomainElements.push_back( new cDomainNaturalNumber( uiMaxVectorElementNumber +
						rand() % uiMaxVectorElementNumber ) );
				}
				cDomainVector domainVector( vecDomainElements );
				
				for ( unsigned int uiDomainElement = 0;
						uiDomainElement < vecDomainElements.size(); uiDomainElement++ ){
					
					delete vecDomainElements[ uiDomainElement ];
				}
				
				//add random to the domains or value domains
				if ( rand() % 2 == 0 ){
					pActualRoot->getDomains()->addDomain(
						vecPossiblePropertytyps[ uiChoosenPropertytype ],
						domainVector );
				}else{
					pActualRoot->getValueDomains()->addDomain(
						vecPossiblePropertytyps[ uiChoosenPropertytype ],
						domainVector );
				}
			}
		}
	
		//set standardvalues of input variables
		if ( (pGeneratedfibObject != NULL) && (pGeneratedfibObject->getType() == 'r') ){
			cRoot * pRoot = (cRoot*)pGeneratedfibObject;
			unsignedIntFib uiNumberOfInVar = pRoot->getNumberOfInputVariables();
			for ( unsignedIntFib uiActualInVar = 1;
					uiActualInVar <= uiNumberOfInVar; uiActualInVar++ ){
				
				pRoot->setStandardValueOfInputVariable( uiActualInVar, uiActualInVar );
			}
		}

		if ( pGeneratedfibObject ){
			cout<<" generated "<<endl;
		}else{
			cout<<endl;
			cerr<<"Error: Generated Fib-object failed:"<<
				" Fib-object with size="<< uiSize <<
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
				uiErrorsInTests += testStoreXmlOnObject( pGeneratedfibObject );
			}break;
			case 2:{
				uiErrorsInTests += testStoreOnObject( pGeneratedfibObject );
			}break;

		}

		iReturn += uiErrorsInTests;

		if ( uiErrorsInTests != 0 ){
			//write Fib-object wher orror occured to folder
			char szFileNameBuffer[256];
			sprintf ( szFileNameBuffer, "%s%sS%uD%uSR%uSRD%uIV%uVF%uMV%uR%uTT%u%s",
				DIR_OUTPUT, "storeErrorOrg", uiSize,
				uiNumberOfDimensions, uiAverageSubRoots, uiAverageSubRootsDepth,
				uiNumberOfAverageInputVariables, uiFractionsOfUsedVariables,
				uiMaxVectorElementNumber, uiIteration, uiTestType ,".xml" );
			
			cerr<<"Error: The Fib-object wher the error occured will be writen to the file \""<< szFileNameBuffer <<"\" ."<<endl;
			
			ofstream * pFile = new ofstream( szFileNameBuffer );
			
			bool bStoreSuccesfull = pGeneratedfibObject->storeXml( *pFile );
			delete pFile;
			
			if ( ! bStoreSuccesfull ){
	
				cerr<<"Error: Storing the data of the generated Fib-object to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
				iReturn++;
			}
		}
		cFibElement::deleteObject( pGeneratedfibObject );

	}}}}}}
	
	return iReturn;
}




/**
 * This function tests the storeXml() and restoreXml() methods an given
 * Fib-object.
 *
 * methods tested:
 * 	- virtual bool storeXml( ostream &stream ) const;
 * 	- static cFibElement *restoreXml( istream &stream, intFib *outStatus=NULL );
 * 	-- static cFibElement *restoreXml( const TiXmlNode * pXmlNode, intFib *outStatus=NULL );(indirect with restoreXml( istream, ... ))
 *
 * Fib-elements tested:
 * 	- cRoot
 * 	- cPoint
 * 	- cProperty
 * 	- cList
 *
 * @param fibObject a pointer to the Fib-object to test
 * @return the number of erros occured in the test
 */
int testStoreXmlOnObject( cFibElement * pFibObject ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	static unsigned int uiXmlFileIteration = 0;
	if ( ! bOverwriteFiles ){
		uiXmlFileIteration++;
	}
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib-object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	cFibElement * pFibObjectClone = pFibObject->clone();
	
	char szFileNameBuffer[256];
	sprintf ( szFileNameBuffer, "%s%s%u%s", DIR_OUTPUT, "storeXml", uiXmlFileIteration ,".xml" );
	
	ofstream * pOutFile = new ofstream( szFileNameBuffer );
	
	cout<<"Storing Fib-object in the Xml-format to the file "<< szFileNameBuffer <<" . ";
	
	bool bStoreSuccesfull = pFibObject->storeXml( *pOutFile );
	delete pOutFile;
	
	if ( bStoreSuccesfull ){
		cout<<"OK"<<endl;
	}else{
		cerr<<endl<<"Error: Storing the data to Xml-file of the generated Fib-object to the file \""<<
			szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	ifstream inFile( szFileNameBuffer );

	intFib outStatus = 0;
	cFibElement * pRestoredFibObject = cFibElement::restoreXml( inFile , &outStatus );
	
	if ( outStatus == 0 ){
		cout<<"Restoring Fib-object in the Xml-format from the file "<<
			szFileNameBuffer <<" successfull. "<<endl;
	}else{
		cerr<<"Error: Restoring Fib-object in the Xml-format from the file "<<
			szFileNameBuffer <<" not successfull. (return status="<< outStatus <<")"<<endl;
		iReturn++;
	}
	
	if ( pRestoredFibObject ){
		if ( ! pFibObject->equal( *pRestoredFibObject ) ){
			cerr<<"Error: The restore Fib-object dosn't equal the stored Fib-object."<<endl;
			iReturn++;
			
			static unsigned int uiRestoreIteration = 1;
			sprintf ( szFileNameBuffer, "%s%s%u%s%s", DIR_OUTPUT, "storeXml", uiRestoreIteration, "Error" ,".xml" );
			pOutFile = new ofstream( szFileNameBuffer );
			cout<<"Storing restored Fib-object in the Xml-format to the file "<< szFileNameBuffer <<" . "<<endl;
			pRestoredFibObject->storeXml( *pOutFile );
			delete pOutFile;
			uiRestoreIteration++;
		}else{
			if ( outStatus != 0 ){
				cerr<<"Error: Restoring Fib-object in the Xml-format from the file "<<
					szFileNameBuffer <<" not successfull (return status="<< outStatus <<
					"), but is equal to the original Fib object"<<endl;
				iReturn++;
			}
		}
		cFibElement::deleteObject( pRestoredFibObject );
	}else{
		cerr<<"Error: No Fib-object restored ."<<endl;
		iReturn++;
	}
	
	if ( ! pFibObject->equal( *pFibObjectClone ) ){
		cerr<<"Error: The Fib-object has changed while storing ."<<endl;
		iReturn++;
	}
	cFibElement::deleteObject( pFibObjectClone );
	
	return iReturn;
}




/**
 * This function tests the store() and restore() methods an given Fib-object.
 *
 * methods tested:
 * 	- virtual bool store( ostream &stream ) const;
 * 	- static cFibElement *restore( istream &stream, intFib *outStatus=NULL );
 *
 * Fib-elements tested:
 * 	- cRoot
 * 	- cPoint
 * 	- cProperty
 * 	- cList
 *
 * @param fibObject a pointer to the Fib-object to test
 * @return the number of erros occured in the test
 */
int testStoreOnObject( cFibElement * pFibObject ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	static unsigned int uiFileIteration = 0;
	if ( ! bOverwriteFiles ){
		uiFileIteration++;
	}
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib-object to check ."<<endl;
		iReturn++;
		return iReturn;
	}

	char szFileNameBuffer[256];
	sprintf ( szFileNameBuffer, "%s%s%u%s", DIR_OUTPUT, "store", uiFileIteration ,".fib" );
	
	ofstream * pOutFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cout<<"Storing Fib-object in the compressed Fib-format to the file "<< szFileNameBuffer <<" . ";

	bool bStoreSuccesfull = pFibObject->store( *pOutFile );
	delete pOutFile;
	
	if ( bStoreSuccesfull ){
		cout<<"OK"<<endl;
	}else{
		cerr<<endl<<"Error: Storing the data to compressed Fib-format of the generated Fib-object to the file \""<<
			szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	ifstream inFile( szFileNameBuffer, ios_base::in | ios_base::binary );

	intFib outStatus = 0;
	cFibElement * pRestoredFibObject = cFibElement::restore( inFile , &outStatus );
	
	if ( outStatus == 0 ){
		cout<<"Restoring Fib-object in the compressed Fib-format from the file "<<
			szFileNameBuffer <<" successfull. "<<endl;
	}else{
		cerr<<"Error: Restoring Fib-object in the compressed Fib-format from the file "<<
			szFileNameBuffer <<" not successfull. (return status="<< outStatus <<")"<<endl;
		iReturn++;
	}
	
	if ( pRestoredFibObject ){
		if ( ! pFibObject->equal( *pRestoredFibObject ) ){
			cerr<<"Error: The restore Fib-object dosn't equal the stored Fib-object."<<endl;
			iReturn++;
			
			static unsigned int uiRestoreIteration = 1;
			sprintf ( szFileNameBuffer, "%s%s%u%s%s", DIR_OUTPUT, "store", uiRestoreIteration, "Error" ,".xml" );
			ofstream * pOutFileXml = new ofstream( szFileNameBuffer );
			cout<<"Storing restored Fib-object in the Xml-format to the file "<< szFileNameBuffer <<" . "<<endl;
			pRestoredFibObject->storeXml( *pOutFileXml );
			delete pOutFileXml;
			uiRestoreIteration++;
		}else{
			if ( outStatus != 0 ){
				cerr<<"Error: Restoring Fib-object in the Xml-format from the file "<<
					szFileNameBuffer <<" not successfull (return status="<< outStatus <<
					"), but is is equal to the original Fib object"<<endl;
				iReturn++;
			}
		}
		cFibElement::deleteObject( pRestoredFibObject );
	}else{
		cerr<<"Error: No Fib-object restored ."<<endl;
		iReturn++;
	}
	
	return iReturn;
}














