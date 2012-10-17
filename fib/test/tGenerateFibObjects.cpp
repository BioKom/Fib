/**
 * @file tGenerateFibObjects
 * file name: tGenerateFibObjects.cpp
 * @author Betti Oesterholz
 * @date 29.12.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test generates random Fib-objects.
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
 * This test generates random Fib-objects.
 * The generated Fib-objects have to be checked manually.
 * The generatefunction of tGeneratorForFibObjects is tested:
 * 	- cFibElement * generateFibObject( unsigned int uiSize, list< pair< char, double > > liFractionOfFibElements, list< cTypeProperty > liPossiblePropertytyps, unsigned int uiNumberOfDimensions = 2, unsigned int uiAverageSubRoots = 2, unsigned int uiAverageSubRootsDepth = 1, unsigned int uiNumberOfAverageInputVariables = 1, double dFractionsOfUsedVariables = 0.5, unsigned int uiMaxVectorElementNumber = 1023 )
 *
 * call: tGenerateFibObjects [MAX_SIZE] [ITERATIONS]
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
 * Tested for Fib-elements:
 * 	- cRoot
 * 	- cPoint
 * 	- cProperty
 * 	- cList
 * 	- cArea
 * 	- cFunction
 * 	- cComment
 * 	- cIf
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 */
/*
History:
29.12.2009  Oesterholz  created
01.08.2010  Oesterholz  cComment added
21.05.2011  Oesterholz  cIf added
27.09.2011  Oesterholz  cExtObject added
14.11.2011  Oesterholz  cExtSubobject added
15.01.2012  Oesterholz  cFibSet and cFibMatrix added
*/

#include "version.h"

#include "cFibElement.h"
#include "cPoint.h"
#include "cTypeProperty.h"

#include <iostream>
#include <fstream>
#include <ostream>

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/rand/"
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


/** @def PATH_SEPERATOR the operatingsystem dependent seperator in filepath */
#ifdef linux
	#define PATH_SEPERATOR      '/'
	#define NOT_PATH_SEPERATOR  '\\'
#else//dos/windows
	#define PATH_SEPERATOR      '\\'
	#define NOT_PATH_SEPERATOR  '/'
#endif

/**
 * checks if a file for the given path exists and can be opened
 * @param path a string for the path to be cheked
 * @return true if the path exists, else false
 */
bool checkPath( char* path ){

	if  ( path==NULL ){
		return false;
	}
	ifstream test( path );
	if( test ){
		test.close();
		return true;
	}
	return false;
}

/**
 * if the path folders are not existing, this function creats them
 * @param path the string of the path that should be existing
 */
void createPath( char* path ){

	unsigned long maxC=0,count=0,count2=0;//maxC= maximal chars to read; to avoid infinity loops
	if  ( path==NULL ){
		return;
	}
	//begin with the first folder, check if the folder exists and if not creat it
	char folder[1000],mkDir[1020];
	for ( ; (maxC<100000) && (path[count]!=0) ; maxC++ ){
		//check next folder
		for ( ; (maxC<100000) && (path[count]!=0) ; maxC++ ){
			//read folder from path
			if ( path[count]==PATH_SEPERATOR){
			
				folder[count2]=PATH_SEPERATOR;
				count++;
				count2++;
				break;
			}else{
				folder[count2]=path[count];
				count++;
				count2++;
			}
		}
		folder[count2]=0;
		if ( (count2!=0) &&
				!( (count2==1) && (folder[0]==PATH_SEPERATOR) ) &&
				!( (count2==2) && (folder[0]=='.') && (folder[1]==PATH_SEPERATOR) )
				&& !(checkPath(folder)) 
				){
			// if in folder stands a valid path
			sprintf( mkDir, "mkdir %s ", folder );
			system( mkDir );
		}
		if ( path[count]==0 ){
			return;
		}
	}
}



int main(int argc, char* argv[]){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
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
	
	cout<<endl<<"This Test generates random Fib objects"<<endl;
	cout<<      "======================================"<<endl;
	cout<<"The generated fib objects have to be checked manually. ";
	cout<<"They can be found in the folder \""<< DIR_OUTPUT <<"\""<<endl;
	cout<<"The maximal size for generated Fib-objects is: "<< uiMaxSize <<endl;
	cout<<"The number of iterations per parameterset is: "<< uiIterations <<endl;
	
	createPath( (char*)(DIR_OUTPUT) );
	
	const unsigned int uiNumberOfDimensions = 2;
	
	list< pair< char, double > > liFractionOfFibElements;
	liFractionOfFibElements.push_back( make_pair( 'p', 1.0 ) );
	liFractionOfFibElements.push_back( make_pair( 'y', 1.0 ) );
	liFractionOfFibElements.push_back( make_pair( 'l', 0.4 ) );
	liFractionOfFibElements.push_back( make_pair( 'a', 0.5 ) );
	liFractionOfFibElements.push_back( make_pair( 'f', 0.5 ) );
	liFractionOfFibElements.push_back( make_pair( 'i', 0.2 ) );
	liFractionOfFibElements.push_back( make_pair( 'c', 0.2 ) );
	liFractionOfFibElements.push_back( make_pair( 'o', 0.1 ) );
	liFractionOfFibElements.push_back( make_pair( 's', 0.1 ) );
	liFractionOfFibElements.push_back( make_pair( 'v', 0.1 ) );
	liFractionOfFibElements.push_back( make_pair( 'm', 0.1 ) );
	//TODO: more Fib-elements
	
	list< cTypeProperty > liPossiblePropertytyps;
	liPossiblePropertytyps.push_back( cTypeProperty( cTypeProperty::COLOR_RGB, uiNumberOfDimensions ) );
	
	for ( unsigned int uiAverageSubRoots = 1 ; uiAverageSubRoots <= 16; uiAverageSubRoots *= 4 ){// * 3
	for ( unsigned int uiAverageSubRootsDepth = 1; uiAverageSubRootsDepth <= 4 ; uiAverageSubRootsDepth++ ){// * 4
	for ( unsigned int uiNumberOfAverageInputVariables = 0; uiNumberOfAverageInputVariables <= 10;
			uiNumberOfAverageInputVariables = (unsigned int)(uiNumberOfAverageInputVariables * 2 + 1) ){// * 4
	for ( double dFractionsOfUsedVariables = 0.0; dFractionsOfUsedVariables <= 1.0; dFractionsOfUsedVariables += 0.25 ){// * 4
	for ( unsigned int uiMaxVectorElementNumber = 7; uiMaxVectorElementNumber <= 100000;
		uiMaxVectorElementNumber = ( (uiMaxVectorElementNumber + 1) * 32 - 1 ) ){// * 4
	for ( unsigned int uiSize = 4; uiSize < uiMaxSize; uiSize *= 2 ){
	for ( unsigned int uiIteration = 1; uiIteration <= uiIterations; uiIteration++ ){
		
		char szFileNameBuffer[256];
		const unsigned int uiFractionsOfUsedVariables =
			(unsigned int)(dFractionsOfUsedVariables * 100.0);
		sprintf ( szFileNameBuffer, "%s%sS%uD%uSR%uSRD%uIV%uVF%uMV%uR%u%s",
			DIR_OUTPUT, "randGenerator", uiSize,
			uiNumberOfDimensions, uiAverageSubRoots, uiAverageSubRootsDepth,
			uiNumberOfAverageInputVariables, uiFractionsOfUsedVariables,
			uiMaxVectorElementNumber, uiIteration ,".xml" );
		
		cout<<"Generate Fib -object \""<< szFileNameBuffer<<"\". "<<flush;
		
		cFibElement * pGeneratedfibObject = generateFibObject( uiSize,
			liFractionOfFibElements, liPossiblePropertytyps, uiNumberOfDimensions,
			uiAverageSubRoots, uiAverageSubRootsDepth,
			uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
			uiMaxVectorElementNumber );
		
		if ( pGeneratedfibObject ){
			cout<<" generated "<<endl;
		}else{
			cout<<endl;
			cerr<<"Error: Generated Fib-object \""<< szFileNameBuffer <<"\" failed."<<endl;
			iReturn++;
			continue;
		}
		
		ofstream * pFile = new ofstream( szFileNameBuffer );
		
		bool bStoreSuccesfull = pGeneratedfibObject->storeXml( *pFile );
		delete pFile;
		
		if ( ! bStoreSuccesfull ){
		
/*			cout<<"The data of the generated Fib-object was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
		}else{*/
			cerr<<"Error: Storing the data of the generated Fib-object to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
			iReturn++;
		}
		cFibElement::deleteObject( pGeneratedfibObject );
	
	}}}}}}}
	
	return iReturn;
}











