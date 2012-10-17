/**
 * @file tGeneratePictures
 * file name: tGeneratePictures.cpp
 * @author Betti Oesterholz
 * @date 31.10.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test generates random Fib pictures.
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
 * This test generates random Fib pictures.
 * 
 *
 * call: tGeneratePictures [WIDTH] [HIGH] [NUMBER_PICTURES] [MIN_PERCENT_PIXELS] [DIR_OUTPUT]
 *
 * parameters:
 * 	WIDTH
 * 		The width of the pictures to generate.
 * 		Standardvalue is 64.
 * 	HIGH
 * 		The high of the pictures to generate.
 * 		Standardvalue is 64.
 * 	NUMBER_PICTURES
 * 		The number of pictures to generate.
 * 		Standardvalue is one.
 * 	MIN_PERCENT_PIXELS
 * 		The percent of pixels in the picture which should have a color.
 * 		Standardvalue is 30 per cent.
 * 	DIR_OUTPUT
 * 		The directory wher the pictures should be writen to.
 * 		Standardvalue "test_output/rand/".
 *
 *
 */
/*
History:
31.10.2010  Oesterholz  created
21.05.2011  Oesterholz  cIf added
06.09.2011  Oesterholz  uiMaxVectorElementNumber dependent on (/is)
	maximal dimension size
14.11.2011  Oesterholz  cExtObject and cExtSubobject added
16.01.2012  Oesterholz  cFibSet and cFibMatrix added
*/

#include "version.h"

#include "cFibElement.h"
#include "cPoint.h"
#include "cTypeProperty.h"
#include "cDomainNaturalNumber.h"
#include "cDomainVector.h"
#include "cEvaluePositionListLimit.h"

#include <iostream>
#include <fstream>
#include <ostream>

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/rand/"
#endif


using namespace fib;
using namespace std;


extern cFibElement * generateFibObject( unsigned int uiSize, unsigned long ulMaximalEvaluedPoints,
		list< pair< char, double > > liFractionOfFibElements,
		const list< cTypeProperty > & liPossiblePropertytyps,
		const vector<unsigned long> & vecDimensions,
		const unsigned int uiAverageSubRoots, const unsigned int uiAverageSubRootsDepth,
		const unsigned int uiNumberOfAverageInputVariables,
		const double dFractionsOfUsedVariables,
		unsigned long uiMaxVectorElementNumber );


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
void createPath( const char* path ){

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
	
//call: tGeneratePictures [WIDTH] [HIGH] [NUMBER_PICTURES] [MIN_PERCENT_PIXELS] [DIR_OUTPUT]
	
	//* read input parameters
	vector<unsigned long> vecDimensions( 2, 16 );
	unsigned long ulNumberOfPictures = 1;
	unsigned long ulNumberOfPoints = (vecDimensions[ 0 ] * vecDimensions[ 1 ]);
	unsigned long ulMinColorPixels = ulNumberOfPoints * 3 / 10;
	
	const char * szDirOutput = DIR_OUTPUT;
	
	if ( argc >= 2 ){
		//one parameter given; get parameter max x size
		vecDimensions[ 0 ] = atol( argv[ 1 ] );
		if ( vecDimensions[ 0 ] < 1 ){
			vecDimensions[ 0 ] = 1;
		}
	}
	if ( argc >= 3 ){
		//two parameter given; get parameter max y size
		vecDimensions[ 1 ] = atol( argv[ 2 ] );
		if ( vecDimensions[ 1 ] < 1 ){
			vecDimensions[ 1 ] = 1;
		}
	}
	ulNumberOfPoints = (vecDimensions[ 0 ] * vecDimensions[ 1 ]);
	if ( argc >= 4 ){
		//tree parameter given; read parameter for the number of to generate pictures
		ulNumberOfPictures = atol( argv[ 3 ] );
		if ( ulNumberOfPictures < 1 ){
			ulNumberOfPictures = 1;
		}
	}
	if ( argc >= 5 ){
		//tree parameter given; read parameter for the minimum percent of generated colored pixeld
		ulMinColorPixels = ulNumberOfPoints * atol( argv[ 4 ] ) / 100;
		if ( ulMinColorPixels < 1 ){
			ulMinColorPixels = 1;
		}
		if ( ulNumberOfPoints < ulMinColorPixels ){
			ulMinColorPixels = ulNumberOfPoints;
		}
	}
	if ( argc >= 6 ){
		//tree parameter given; read parameter for output directory
		szDirOutput = argv[ 5 ];
	}
	
	cout<<endl<<"This Test generates random Fib pictures"<<endl;
	cout<<      "======================================="<<endl;
	cout<<"They can be found in the folder \""<< szDirOutput <<"\""<<endl;
	cout<<"The generated Fib -pictures width is "<< vecDimensions[ 0 ] <<" and high is "<< vecDimensions[ 1 ]<<" ."<<endl;
	cout<<"The number of pictures to generate is "<< ulNumberOfPictures<<" with minimum "<<ulMinColorPixels<<" colored pixels."<<endl;
	
	createPath( szDirOutput );
	
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
	//TODO: more Fib -elements
	
	list< cTypeProperty > liPossiblePropertytyps;
	liPossiblePropertytyps.push_back( cTypeProperty( cTypeProperty::COLOR_RGB, 2 ) );
	
	
	const unsigned int uiNumberOfAverageInputVariables = 0;
	const unsigned long uiMaxVectorElementNumber = (vecDimensions[ 0 ] < vecDimensions[ 1 ])?
		vecDimensions[ 1 ] : vecDimensions[ 0 ]; //=max(vecDimensions[ 0 ] < vecDimensions[ 1 ])
	unsigned long ulStoredPictur = 0;
	
	vector<cDomainSingle*> vecDomainsDimension( 2, ((cDomainSingle*)NULL) );
	
	for ( unsigned int uiActualDimensions = 0;
			uiActualDimensions < 2; uiActualDimensions++ ){
		
		vecDomainsDimension[ uiActualDimensions ] =
			new cDomainNaturalNumber( vecDimensions[ uiActualDimensions ] );
	}
	const cDomainVector vectorDomainDimension( vecDomainsDimension );
	
	for ( unsigned int uiActualDimensions = 0;
			uiActualDimensions < 2; uiActualDimensions++ ){
		
		delete vecDomainsDimension[ uiActualDimensions ];
	}
	
	while ( ulStoredPictur < ulNumberOfPictures ){
		for ( unsigned int uiAverageSubRoots = 1 ; uiAverageSubRoots <= 16; uiAverageSubRoots *= 4 ){// * 3
			cout<<"average sub roots now: "<<uiAverageSubRoots<<endl;
		for ( unsigned int uiAverageSubRootsDepth = 1; uiAverageSubRootsDepth <= 4 ; uiAverageSubRootsDepth++ ){// * 4
			cout<<" average sub root depth now: "<<uiAverageSubRootsDepth<<endl;
		for ( double dFractionsOfUsedVariables = 0.0; dFractionsOfUsedVariables <= 1.0; dFractionsOfUsedVariables += 0.25 ){// * 4
			cout<<"  average fraction of used variables now: "<<dFractionsOfUsedVariables<<endl;
		for ( unsigned int uiSize = 4; uiSize < ulNumberOfPoints; uiSize *= 2 ){
			cout<<"   average size now: "<<uiSize<<"  ";
			
			cFibElement * pGeneratedFibObject = generateFibObject( uiSize, uiSize * uiSize,
				liFractionOfFibElements, liPossiblePropertytyps, vecDimensions,
				uiAverageSubRoots, uiAverageSubRootsDepth,
				uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
				uiMaxVectorElementNumber );
			
			if ( pGeneratedFibObject ){
				cout<<"generated "<<flush;
			}else{
				cout<<endl;
				cerr<<"Error: Generating the random Fib object failed."<<endl<<flush;
				iReturn++;
				continue;
			}
			
//TODO weg
//cout<<"cEvaluePositionListLimit evaluedPositionsDataOriginal( "<<ulNumberOfPoints * 2<<", "<<&vectorDomainDimension<<", true, 0, "<<ulNumberOfPoints * 64<<" );"<<endl<<flush;
			
			//check if the generated pictur has enougth points
			cEvaluePositionListLimit evaluedPositionsDataOriginal( ulNumberOfPoints * 2,
				&vectorDomainDimension, true, 0, ulNumberOfPoints * 64 );
//TODO weg
//cout<<"starting evaluation "<<endl<<flush;
			
			const bool bObjectEvalued = pGeneratedFibObject->evalueObjectSimple(
				evaluedPositionsDataOriginal );
			if ( ! bObjectEvalued ){
				cout<<endl;
				cerr<<"    The generated Fib object couldn't be evalued. (Maybe too much points to evalue.)"<<endl<<flush;
				cFibElement::deleteObject( pGeneratedFibObject );
				iReturn = 1;
				continue;
			}
			evaluedPositionsDataOriginal.sortPositionsData();
			
			const unsigned long ulPixelsGenerated =
				evaluedPositionsDataOriginal.liEvaluedPositionData.size();
			
			if ( ulPixelsGenerated < ulMinColorPixels){
				cFibElement::deleteObject( pGeneratedFibObject );
				cout<<endl;
				cout<<"    Not enougth colored points generated (generated colored points: "<< ulPixelsGenerated <<") retry"<<endl<<flush;
				continue;
			}
			//pictur has enougth colored points -> save it
			ulStoredPictur++;
			char szFileNameBuffer[ 256 ];
			sprintf ( szFileNameBuffer, "%s%s%lu%s",
				szDirOutput, "randPictur", ulStoredPictur ,".xml" );
			cout<<endl<<"Saving Fib picture \""<< szFileNameBuffer<<
				"\". (generated colored points: "<< ulPixelsGenerated <<")"<<endl<<flush;
			
			ofstream * pFile = new ofstream( szFileNameBuffer );
			
			bool bStoreSuccesfull = pGeneratedFibObject->storeXml( *pFile );
			delete pFile;
			
			if ( ! bStoreSuccesfull ){
			
	/*			cout<<"The data of the generated Fib -object was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
			}else{*/
				cout<<endl;
				cerr<<"Error: Storing the data of the generated Fib object to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
				iReturn++;
			}
			cFibElement::deleteObject( pGeneratedFibObject );
			
			if ( ulNumberOfPictures <= ulStoredPictur ){
				return iReturn;
			}
			cout<<endl;
		}}}}
	}
	cout<<endl<<"Generating done; Number of stored pictures:"<<ulStoredPictur<<flush;
	
	return iReturn;
}











