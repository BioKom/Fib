
//TODO check

/**
 * @file tImageSearchData
 * file name: tImageSearchData.cpp
 * @author Betti Oesterholz
 * @date 03.04.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cImageSearchData.
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
 * This file contains the test for the class cImageSearchData, which
 * is for storing the data for a search on image data.
 *
 *
 * call: tImageSearchData [MAX_ITERATION]
 *
 * parameters:
 * 	MAX_ITERATION
 * 		The number of iterators for the random tests
 *
 *
 *
 * What's tested of class cImageSearchData:
 * 	- cImageSearchData( const unsigned long ulInWidth, const unsigned long ulInHeight );
 * 	- cImageSearchData( const iImageData * pInImageData );
 * 	- cImageSearchData( const cImageSearchData & imageSearchData );
 * 	- ~cImageSearchData();
 * 	- cImageSearchData * clone() const;
 * 	- cImageSearchData & operator=( const cImageSearchData & imageSearchData );
 * 	- unsigned long getWidth() const;
 * 	- unsigned long getHeight() const;
 * 	- const iImageData * getImageData() const;
 * 	- bool isIn( const cVectorPosition & position ) const
 * 	- bool isFound( const cVectorPosition& position ) const;
 * 	- bool isFound( const unsigned long lX, const unsigned long lY ) const;
 * 	- bool isOverlapped( const cVectorPosition& position ) const;
 * 	- bool isOverlapped( const unsigned long lX, const unsigned long lY ) const;
 * 	- bool isFoundOrOverlapped( const cVectorPosition& position ) const;
 * 	- bool isFoundOrOverlapped( const unsigned long lX, const unsigned long lY ) const;
 * 	- bool isFoundOrOverlapped( const pair< unsigned int, unsigned int> & position ) const;
 * 	- set<cVectorPosition> getFoundPoints() const;
 * 	- set<cVectorPosition> getNotFoundPoints() const;
 * 	- set<cVectorPosition> getOverlappedPoints() const;
 * 	- set<cVectorPosition> getNotOverlappedPoints() const;
 * 	- set<cVectorPosition> getNeighbours( const cVectorPosition& position ) const;
 * 	- set<cVectorPosition> getFoundNeighbours( const cVectorPosition& position ) const;
 * 	- set<cVectorPosition> getNotFoundNeighbours( const cVectorPosition& position ) const;
 * 	- set<cVectorPosition> getOverlappedNeighbours( const cVectorPosition& position ) const;
 * 	- set<cVectorPosition> getNotOverlappedNeighbours( const cVectorPosition& position ) const;
 * 	- set<cVectorPosition> getNotFoundNotOverlappedNeighbours( const cVectorPosition& position ) const;
 * 	- bool hasNotFoundNotOverlappedNeighbours( const cVectorPosition& position ) const;
 * 	- bool registerFound( const cVectorPosition & foundPoint, const bool bFound=true );
 * 	- unsigned long registerFound( const set<cVectorPosition> & setFoundPoints, const bool bFound=true );
 * 	- unsigned long registerFound( const cImageStructure * pImageStrFoundPoints, const bool bFound=true );
 * 	- bool registerOverlapped( const cVectorPosition & overlappedPoint, const bool bOverlapped=true );
 * 	- unsigned long registerOverlapped( const set<cVectorPosition> & setOverlappedPoints, const bool bOverlapped=true );
 * 	- unsigned long registerOverlapped( const cImageStructure * pImageStrOverlappedPoints, const bool bOverlapped=true );
 * 	- void foundToOverlapped();
 * 	- void clearFound();
 * 	- void clearOverlapped();
 * 	- bool isFound( const pair< unsigned int, unsigned int> & position ) const;
 * 	- bool isOverlapped( const pair< unsigned int, unsigned int> & position ) const;
 * 	- set< pair< unsigned int, unsigned int> > getFoundPointsAsPair() const;
 * 	- set< pair< unsigned int, unsigned int> > getNotFoundPointsAsPair() const;
 * 	- set< pair< unsigned int, unsigned int> > getOverlappedPointsAsPair() const;
 * 	- set< pair< unsigned int, unsigned int> > getNotOverlappedPointsAsPair() const;
 * 	- set< pair< unsigned int, unsigned int> > getNeighbours( const pair< unsigned int, unsigned int> & position ) const;
 * 	- set< pair< unsigned int, unsigned int> > getFoundNeighbours( const pair< unsigned int, unsigned int>  & position ) const;
 * 	- set< pair< unsigned int, unsigned int> > getNotFoundNeighbours( const pair< unsigned int, unsigned int> & position ) const;
 * 	- set< pair< unsigned int, unsigned int> > getOverlappedNeighbours( const pair< unsigned int, unsigned int> & position ) const;
 * 	- set< pair< unsigned int, unsigned int> > getNotOverlappedNeighbours( const pair< unsigned int, unsigned int> & position ) const;
 * 	- set< pair< unsigned int, unsigned int> > getNotFoundNotOverlappedNeighbours( const pair< unsigned int, unsigned int> & position ) const;
 * 	- bool hasNotFoundNotOverlappedNeighbours( const pair< unsigned int, unsigned int> & position ) const;
 * 	- bool registerFound( const pair< unsigned int, unsigned int> & foundPoint, const bool bFound=true );
 * 	- unsigned long registerFound( const set< pair< unsigned int, unsigned int> > & setFoundPoints, const bool bFound=true );
 * 	- bool registerOverlapped( const pair< unsigned int, unsigned int> & overlappedPoint, const bool bOverlapped=true );
 * 	- unsigned long registerOverlapped( const set< pair< unsigned int, unsigned int> > & setOverlappedPoints, const bool bOverlapped=true );
 *
 */
/*
History:
03.04.2013  Oesterholz  created
*/



#include "version.h"
#include "fibDatatyps.h"

#include "cImageStructure.h"
#include "cImageSearchData.h"


#include "cVectorPosition.h"
#include "cEvalueSimpleRGBA255.h"


#include <string>
#include <utility>
#include <list>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <ostream>
#include <cmath>
#include <ctime>

using namespace fib::algorithms::nConvertToFib::nImage::nStructureData;
using namespace fib;
using namespace std;

unsigned long MAX_ITERATION = 256;


int testMethodsRandom( unsigned long &ulTestphase );



int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test
	int iReturn = 0;//return value of the test; the number of occured Errors
	
	srand( time(NULL) );
	
	
	cout<<endl<<"Running Test for the cImageStructure methods"<<endl;
	cout<<      "============================================"<<endl;
	cout<<      "============================================"<<endl;
	
	if ( 1 < argc ){
		//two parameters given; read parameter iterators
		MAX_ITERATION = atol( argv[ 1 ] );
		if ( MAX_ITERATION < 1 ){
			MAX_ITERATION = 1;
		}
	}
	cout<<endl<<"Number of maximal iterators is "<<MAX_ITERATION<<endl;
	
	cout<<endl<<"Running Test for the cImageSearchData methods"<<endl;
	cout<<      "============================================="<<endl;
	
	//test the cImageStructure methods
	unsigned int iReturnTestCase = testMethodsRandom( ulTestphase );
	
	
	if ( iReturnTestCase == 0 ){
	
		cout<<endl<<endl<<"Test for cImageSearchData successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test for cImageSearchData failed: "<<
			iReturnTestCase<<" errors occoured"<<endl;
		iReturn += iReturnTestCase;
	}
	
	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	
	return iReturn;
}




/**
 * @param uiBorderX the border for the x or first dimension values,
 * 	all x values will be lower as this value
 * @param uiBorderY the border for the y or second dimension values,
 * 	all y values will be lower as this value
 * @return generates a random point
 */
cVectorPosition generateRandomPoint( unsigned int uiBorderX, unsigned int uiBorderY ){
	
	double dValueX = ( uiBorderX != 0 ) ? ( rand() % uiBorderX ) : 0;
	double dValueY = ( uiBorderY != 0 ) ? ( rand() % uiBorderY ) : 0;
	
	if ( rand() % 4 == 0 ){
		//add random after point part
		dValueX += ((double)(rand() % 160 - 80)) / 81.0;
		dValueY += ((double)(rand() % 160 - 80)) / 81.0;
	}
	
	cVectorPosition position( 2 );
	position.setValue( 1, dValueX );
	position.setValue( 2, dValueY );
	
	return position;
}


/**
 * @param uiNumberOfPointsToGenerate the number of points to generate
 * @param uiBorderX the border for the x or first dimension values,
 * 	all x values will be lower as this value
 * @param uiBorderY the border for the y or second dimension values,
 * 	all y values will be lower as this value
 * @return a set with the generates a random points
 */
set< cVectorPosition > generateRandomPoints( unsigned int uiNumberOfPointsToGenerate,
		unsigned int uiBorderX, unsigned int uiBorderY ){
	
	set< cVectorPosition > setGeneratedPoints;
	for ( unsigned long uiIteration = 0;
			uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
		
		setGeneratedPoints.insert( generateRandomPoint( uiBorderX, uiBorderY ) );
	}
	return setGeneratedPoints;
}




/**
 * @param uiBorderX the border for the x or first dimension values,
 * 	all x values will be lower as this value
 * @param uiBorderY the border for the y or second dimension values,
 * 	all y values will be lower as this value
 * @return generates a random point
 */
pair< unsigned int, unsigned int > generateRandomPointPair(
		unsigned int uiBorderX, unsigned int uiBorderY ){
	
	return pair< unsigned int, unsigned int >(
		( ( uiBorderX != 0 ) ? ( rand() % uiBorderX ) : 0 ),
		( ( uiBorderY != 0 ) ? ( rand() % uiBorderY ) : 0 ) );
}


/**
 * @param vecPoint the point to convert
 * @return the point as a pair of integer values
 */
pair< unsigned int, unsigned int > toPair(
		const cVectorPosition & vecPoint ){
	
	return pair< unsigned int, unsigned int >(
		roundToLongFib( vecPoint.getValue( 1 ) ),
		roundToLongFib( vecPoint.getValue( 2 ) ) );
}


/**
 * @param setPoints the set of points to convert
 * @return the point as a pair of integer values
 */
set< pair< unsigned int, unsigned int > > toPair(
		const set< cVectorPosition > & setPoints ){
	
	set< pair< unsigned int, unsigned int > > setPointPairs;
	
	for ( set< cVectorPosition >::const_iterator
			itrPoint = setPoints.begin(); itrPoint != setPoints.end(); itrPoint++ ){
		
		setPointPairs.insert( pair< unsigned int, unsigned int >(
			roundToLongFib( itrPoint->getValue( 1 ) ),
			roundToLongFib( itrPoint->getValue( 2 ) ) ) );
	}
	return setPointPairs;
}


/**
 * @param vecPoint the point to convert
 * @return the point as a Fib vector
 */
cVectorPosition toVector(
		const pair< unsigned int, unsigned int > & vecPoint ){
	
	cVectorPosition vecPosition( 2 );
	vecPosition.setValue( 1, vecPoint.first );
	vecPosition.setValue( 2, vecPoint.second );
	
	return vecPosition;
}


/**
 * @param vecPointToCheck the point to check
 * @param uiBorderX the border for the x or first dimension values,
 * 	all x values will be lower as this value
 * @param uiBorderY the border for the y or second dimension values,
 * 	all y values will be lower as this value
 * @return true if the given point is in the image search structur, else false
 */
bool checkPoint( const pair< unsigned int, unsigned int > & vecPointToCheck,
		unsigned int uiBorderX, unsigned int uiBorderY ){
	
	if ( ( uiBorderX == 0 ) || ( uiBorderY == 0 ) ){
		return false;
	}
	if ( uiBorderX <= vecPointToCheck.first ){
		return false;
	}
	if ( uiBorderY <= vecPointToCheck.second ){
		return false;
	}
	return true;
}


/**
 * @param vecPointToCheck the point to check
 * @param uiBorderX the border for the x or first dimension values,
 * 	all x values will be lower as this value
 * @param uiBorderY the border for the y or second dimension values,
 * 	all y values will be lower as this value
 * @return true if the given point is in the image search structur, else false
 */
bool checkPoint( const pair< long, long > & vecPointToCheck,
		unsigned int uiBorderX, unsigned int uiBorderY ){
	
	if ( ( uiBorderX == 0 ) || ( uiBorderY == 0 ) ){
		return false;
	}
	if ( ( vecPointToCheck.first < 0 ) || ( uiBorderX <= vecPointToCheck.first ) ){
		return false;
	}
	if ( ( vecPointToCheck.second < 0 ) || ( uiBorderY <= vecPointToCheck.second ) ){
		return false;
	}
	return true;
}


/**
 * This method prints the given points to the given stream.
 *
 * @param streamToPrintTo the points to print the points to
 * @param setPoints the points to print
 */
void printPoints( ostream & streamToPrintTo, set<cVectorPosition> setPoints ){
	
	for ( set<cVectorPosition>::iterator itrPoint = setPoints.begin();
			itrPoint != setPoints.end(); itrPoint++ ){
		
		itrPoint->storeXml( streamToPrintTo );
	}
}


/**
 * This method prints the given points to the given stream.
 *
 * @param streamToPrintTo the points to print the points to
 * @param setPoints the points to print
 */
void printPoints( ostream & streamToPrintTo,
		set< pair< unsigned int, unsigned int > > setPoints ){
	
	for ( set< pair< unsigned int, unsigned int > >::iterator
			itrPoint = setPoints.begin();
			itrPoint != setPoints.end(); itrPoint++ ){
		
		streamToPrintTo<<" ("<<itrPoint->first<<", "<<itrPoint->second<<");";
	}
	streamToPrintTo<<endl;
}


/**
 * @param vecPointToCheck the point to check
 * @param uiBorderX the border for the x or first dimension values,
 * 	all x values will be lower as this value
 * @param uiBorderY the border for the y or second dimension values,
 * 	all y values will be lower as this value
 * @return true if the given point is in the image search structur, else false
 */
bool checkPoint( const cVectorPosition & vecPointToCheck,
		unsigned int uiBorderX, unsigned int uiBorderY ){
	
	return checkPoint( toPair( vecPointToCheck ), uiBorderX, uiBorderY );
}


/**
 * This function choose a point from the given point container.
 *
 * @param pointsToChooseFrom the set from which to choose
 * @return a random point from the given set
 */
pair< unsigned int, unsigned int > chooseRandomPoint(
		const set< pair< unsigned int, unsigned int > > & pointsToChooseFrom ){
	
	if ( pointsToChooseFrom.empty() ){
		//no point to choose
		return pair< unsigned int, unsigned int >( 0,0 );
	}
	
	const unsigned int numberChoosenPoint = rand() % pointsToChooseFrom.size();
	set< pair< unsigned int, unsigned int > >::const_iterator
		itrChoosenPoint = pointsToChooseFrom.begin();
	
	for ( unsigned int uiActualPoint = 0; uiActualPoint < numberChoosenPoint;
			uiActualPoint++, itrChoosenPoint++ ){
		//nothing to do
	}
	
	return (*itrChoosenPoint);
}


/**
 * This function compares the two given points sets.
 *
 * @param setCorrectPoints the correct points to compare
 * @param setReturnedPoints the returned points to compare
 */
unsigned int comparePoints( set< pair< unsigned int, unsigned int > > setCorrectPoints,
		set< pair< unsigned int, unsigned int > > setReturnedPoints ){
	
	set< pair< unsigned int, unsigned int > > setToMuchCorrectPoints = setCorrectPoints;
	set< pair< unsigned int, unsigned int > > setToMuchReturnedPoints = setReturnedPoints;
	set< pair< unsigned int, unsigned int > > setMissingCorrectPoints;
	set< pair< unsigned int, unsigned int > > setMissingReturnedPoints;
	
	for ( set< pair< unsigned int, unsigned int > >::iterator
			itrCorrectPoint = setCorrectPoints.begin();
			itrCorrectPoint != setCorrectPoints.end(); itrCorrectPoint++ ){
		
		const unsigned int uiPointsErased =
			setToMuchReturnedPoints.erase( *itrCorrectPoint );
		if ( uiPointsErased == 0 ){
			//point not in returned points
			setMissingReturnedPoints.insert( *itrCorrectPoint );
		}
	}
	for ( set< pair< unsigned int, unsigned int > >::iterator
			itrReturnedPoint = setReturnedPoints.begin();
			itrReturnedPoint != setReturnedPoints.end(); itrReturnedPoint++ ){
		
		const unsigned int uiPointsErased =
			setToMuchCorrectPoints.erase( *itrReturnedPoint );
		if ( uiPointsErased == 0 ){
			//point not in returned points
			setMissingCorrectPoints.insert( *itrReturnedPoint );
		}
	}
	unsigned int uiError = 0;
	if ( ! setToMuchCorrectPoints.empty() ){
		cerr<<endl<<"Error: To much correct points."<<endl;
		printPoints( cerr, setToMuchCorrectPoints );
		uiError++;
	}
	if ( ! setMissingCorrectPoints.empty() ){
		cerr<<endl<<"Error: Missing correct points."<<endl;
		printPoints( cerr, setMissingCorrectPoints );
		uiError++;
	}
	if ( ! setToMuchReturnedPoints.empty() ){
		cerr<<endl<<"Error: To much returned points."<<endl;
		printPoints( cerr, setToMuchReturnedPoints );
		uiError++;
	}
	if ( ! setMissingReturnedPoints.empty() ){
		cerr<<endl<<"Error: Missing returned points."<<endl;
		printPoints( cerr, setMissingReturnedPoints );
		uiError++;
	}
	return uiError;
}


/**
 * This function compares two points.
 * The elements of the points are rounded to interger values for comparrison.
 *
 * @param point1 the first point to compare
 * @param point2 the second point to compare
 * @return if the points are equal, else false
 */
bool pointsEqual( const cVectorPosition & point1, const cVectorPosition & point2 ){
	
	const unsigned int uiNumberOfElements = point1.getNumberOfElements();
	if ( uiNumberOfElements != point2.getNumberOfElements() ){
		//points don't have equal number of elements
		return false;
	}
	
	for ( unsigned int uiActualElement = 1;
			uiActualElement <= uiNumberOfElements; uiActualElement++ ){
		
		const long lValue1 = roundToLongFib( point1.getValue( uiActualElement ) );
		const long lValue2 = roundToLongFib( point2.getValue( uiActualElement ) );
		
		if ( lValue1 != lValue2 ){
			//values not equal -> points not equal
			return false;
		}
		
	}
	return true;
}



/**
 * This function tests the cImageStructure methods to get data.
 *
 * What's tested of class cImageSearchData:
 * 	- unsigned long getWidth() const;
 * 	- unsigned long getHeight() const;
 * 	- bool isIn( const cVectorPosition & position ) const
 * 	- bool isFound( const cVectorPosition& position ) const;
 * 	- bool isFound( const unsigned long lX, const unsigned long lY ) const;
 * 	- bool isOverlapped( const cVectorPosition& position ) const;
 * 	- bool isOverlapped( const unsigned long lX, const unsigned long lY ) const;
 * 	- bool isFoundOrOverlapped( const cVectorPosition& position ) const;
 * 	- bool isFoundOrOverlapped( const unsigned long lX, const unsigned long lY ) const;
 * 	- bool isFoundOrOverlapped( const pair< unsigned int, unsigned int> & position ) const;
 * 	- set<cVectorPosition> getFoundPoints() const;
 * 	- set<cVectorPosition> getNotFoundPoints() const;
 * 	- set<cVectorPosition> getOverlappedPoints() const;
 * 	- set<cVectorPosition> getNotOverlappedPoints() const;
 * 	- set<cVectorPosition> getNeighbours( const cVectorPosition& position ) const;
 * 	- set<cVectorPosition> getFoundNeighbours( const cVectorPosition& position ) const;
 * 	- set<cVectorPosition> getNotFoundNeighbours( const cVectorPosition& position ) const;
 * 	- set<cVectorPosition> getOverlappedNeighbours( const cVectorPosition& position ) const;
 * 	- set<cVectorPosition> getNotOverlappedNeighbours( const cVectorPosition& position ) const;
 * 	- set<cVectorPosition> getNotFoundNotOverlappedNeighbours( const cVectorPosition& position ) const;
 * 	- bool hasNotFoundNotOverlappedNeighbours( const cVectorPosition& position ) const;
 * 	- bool isFound( const pair< unsigned int, unsigned int> & position ) const;
 * 	- bool isOverlapped( const pair< unsigned int, unsigned int> & position ) const;
 * 	- set< pair< unsigned int, unsigned int> > getFoundPointsAsPair() const;
 * 	- set< pair< unsigned int, unsigned int> > getNotFoundPointsAsPair() const;
 * 	- set< pair< unsigned int, unsigned int> > getOverlappedPointsAsPair() const;
 * 	- set< pair< unsigned int, unsigned int> > getNotOverlappedPointsAsPair() const;
 * 	- set< pair< unsigned int, unsigned int> > getNeighbours( const pair< unsigned int, unsigned int> & position ) const;
 * 	- set< pair< unsigned int, unsigned int> > getFoundNeighbours( const pair< unsigned int, unsigned int>  & position ) const;
 * 	- set< pair< unsigned int, unsigned int> > getNotFoundNeighbours( const pair< unsigned int, unsigned int> & position ) const;
 * 	- set< pair< unsigned int, unsigned int> > getOverlappedNeighbours( const pair< unsigned int, unsigned int> & position ) const;
 * 	- set< pair< unsigned int, unsigned int> > getNotOverlappedNeighbours( const pair< unsigned int, unsigned int> & position ) const;
 * 	- set< pair< unsigned int, unsigned int> > getNotFoundNotOverlappedNeighbours( const pair< unsigned int, unsigned int> & position ) const;
 * 	- bool hasNotFoundNotOverlappedNeighbours( const pair< unsigned int, unsigned int> & position ) const;
 *
 * @param pImageSearchStrToTest a pointer to the image search structure to test
 * @param uiWidth the correct width of the image search structure
 * @param uiHeight the correct height of the image search structure
 * @param setFoundPoints the set with the correct found points
 * @param setOverlappedPoints the set with the correct overlapped points
 * @return the number of errors occured in the test
 */
unsigned int checkSearchStructureValues(
		const cImageSearchData * pImageSearchStrToTest,
		const unsigned int uiWidth, const unsigned int uiHeight,
		const set< pair< unsigned int, unsigned int > > & setFoundPoints,
		const set< pair< unsigned int, unsigned int > > & setOverlappedPoints ){
	
	unsigned int uiErrors = 0;
	
	if ( pImageSearchStrToTest == NULL ){
		cerr<<"The image structure is NULL."<<endl;
		uiErrors++;
		return uiErrors;
	}
	if ( pImageSearchStrToTest->getWidth() != uiWidth ){
		cerr<<"The image structure width is "<<pImageSearchStrToTest->getWidth()<<
			", but should be "<<uiWidth<<" ."<<endl;
		uiErrors++;
	}
	if ( pImageSearchStrToTest->getHeight() != uiHeight ){
		cerr<<"The image structure height is "<<pImageSearchStrToTest->getHeight()<<
			", but should be "<<uiHeight<<" ."<<endl;
		uiErrors++;
	}
	//evalue not found and overlapped points
	
	set< pair< unsigned int, unsigned int > > setNotFoundPoints;
	set< pair< unsigned int, unsigned int > > setNotOverlappedPoints;
	//evalue all not found and overlapped points
	pair< unsigned int, unsigned int > paActualPoint( 0, 0 );
	for ( paActualPoint.first = 0;
			paActualPoint.first < uiWidth; paActualPoint.first++ ){
		for ( paActualPoint.second = 0;
				paActualPoint.second < uiHeight; paActualPoint.second++ ){
			
			set< pair< unsigned int, unsigned int > >::const_iterator
				itrFoundPoint = setFoundPoints.find( paActualPoint );
			
			if ( itrFoundPoint == setFoundPoints.end() ){
				//point not found
				setNotFoundPoints.insert( paActualPoint );
			}
			set< pair< unsigned int, unsigned int > >::const_iterator
				itrOverlappedPoint = setOverlappedPoints.find( paActualPoint );
			
			if ( itrOverlappedPoint == setOverlappedPoints.end() ){
				//point not overlapped
				setNotOverlappedPoints.insert( paActualPoint );
			}
		}
	}
	//evalue not found and not overlapped points
	set< pair< unsigned int, unsigned int > > setNotFoundNotOverlappedPoints =
		setNotFoundPoints;
	//delete overlapped points
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrOverlappedPoints = setOverlappedPoints.begin();
			itrOverlappedPoints != setOverlappedPoints.end(); itrOverlappedPoints++ ){
		
		setNotFoundNotOverlappedPoints.erase( *itrOverlappedPoints );
	}
	set< pair< unsigned int, unsigned int > >
		setBorderPoints;
	set< pair< unsigned int, unsigned int > >
		setNotFoundPointsToCheck( setNotFoundPoints );
	set< pair< unsigned int, unsigned int > >
		setNotOverlappedPointsToCheck( setNotOverlappedPoints );
	set< pair< unsigned int, unsigned int > >
		setNotFoundNotOverlappedPointsToCheck( setNotFoundNotOverlappedPoints );
	{//add all border points to not found points
		pair< unsigned int, unsigned int > paActualPoint( 0, 0 );
		paActualPoint.second = uiHeight;
		for ( paActualPoint.first = 0;
				paActualPoint.first < uiWidth; paActualPoint.first++ ){
			//border point
			setBorderPoints.insert( paActualPoint );
			//point not found
			setNotFoundPointsToCheck.insert( paActualPoint );
			//point not overlapped
			setNotOverlappedPointsToCheck.insert( paActualPoint );
			//point not found or not overlapped
			setNotFoundNotOverlappedPointsToCheck.insert( paActualPoint );
		}
		paActualPoint.first = uiWidth;
		for ( paActualPoint.second = 0;
				paActualPoint.second < uiHeight; paActualPoint.second++ ){
			//border point
			setBorderPoints.insert( paActualPoint );
			//point not found
			setNotFoundPointsToCheck.insert( paActualPoint );
			//point not overlapped
			setNotOverlappedPointsToCheck.insert( paActualPoint );
			//point not found or not overlapped
			setNotFoundNotOverlappedPointsToCheck.insert( paActualPoint );
		}
	}
	
	
	//check bool isIn() const
	for ( paActualPoint.first = 0;
			paActualPoint.first < uiWidth; paActualPoint.first++ ){
		for ( paActualPoint.second = 0;
				paActualPoint.second < uiHeight; paActualPoint.second++ ){
			
			if ( ! pImageSearchStrToTest->isIn( toVector( paActualPoint ) ) ){
				cerr<<"Error: The point ("<<paActualPoint.first<<", "<<
					paActualPoint.second<<") is in the image, but not marked as in. "<<
					"( isIn( const cVectorPosition ) )"<<endl;
				uiErrors++;
			}
			if ( ! pImageSearchStrToTest->isIn( paActualPoint ) ){
				cerr<<"Error: The point ("<<paActualPoint.first<<", "<<
					paActualPoint.second<<") is in the image, but not marked as in. "<<
					"( isIn( pair< unsigned int, unsigned int > ) )"<<endl;
				uiErrors++;
			}
		}
	}
	//check not isIn() const
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrNotFoundPoints = setBorderPoints.begin();
			itrNotFoundPoints != setBorderPoints.end(); itrNotFoundPoints++ ){
		
		if ( pImageSearchStrToTest->isIn( toVector( *itrNotFoundPoints ) ) ){
			cerr<<"Error: The point ("<<itrNotFoundPoints->first<<", "<<
				itrNotFoundPoints->second<<") is not in the image, but marked as in. "<<
				"( isIn( const cVectorPosition ) )"<<endl;
			uiErrors++;
		}
	}
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrNotFoundPoints = setBorderPoints.begin();
			itrNotFoundPoints != setBorderPoints.end(); itrNotFoundPoints++ ){
		
		if ( pImageSearchStrToTest->isIn( *itrNotFoundPoints ) ){
			cerr<<"Error: The point ("<<itrNotFoundPoints->first<<", "<<
				itrNotFoundPoints->second<<") is not in the image, but marked as in. "<<
				"( isIn( pair< unsigned int, unsigned int > ) )"<<endl;
			uiErrors++;
		}
	}
	
	
	//check bool isFound( const cVectorPosition& position ) const
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrFoundPoints = setFoundPoints.begin();
			itrFoundPoints != setFoundPoints.end(); itrFoundPoints++ ){
		
		if ( ! pImageSearchStrToTest->isFound( toVector( *itrFoundPoints ) ) ){
			cerr<<"Error: The point ("<<itrFoundPoints->first<<", "<<
				itrFoundPoints->second<<") is found but not marked as found. "<<
				"( isFound( const cVectorPosition ) )"<<endl;
			uiErrors++;
		}
	}
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrNotFoundPoints = setNotFoundPointsToCheck.begin();
			itrNotFoundPoints != setNotFoundPointsToCheck.end(); itrNotFoundPoints++ ){
		
		if ( pImageSearchStrToTest->isFound( toVector( *itrNotFoundPoints ) ) ){
			cerr<<"Error: The point ("<<itrNotFoundPoints->first<<", "<<
				itrNotFoundPoints->second<<") is not found but marked as found. "<<
				"( ! isFound( const cVectorPosition ) )"<<endl;
			uiErrors++;
		}
	}
	//check bool isFound( const unsigned long lX, const unsigned long lY ) const
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrFoundPoints = setFoundPoints.begin();
			itrFoundPoints != setFoundPoints.end(); itrFoundPoints++ ){
		
		if ( ! pImageSearchStrToTest->isFound( itrFoundPoints->first,
				itrFoundPoints->second ) ){
			cerr<<"Error: The point ("<<itrFoundPoints->first<<", "<<
				itrFoundPoints->second<<") is found but not marked as found. "<<
				"( isFound( const unsigned long lX, const unsigned long lY ) )"<<endl;
			uiErrors++;
		}
	}
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrNotFoundPoints = setNotFoundPointsToCheck.begin();
			itrNotFoundPoints != setNotFoundPointsToCheck.end(); itrNotFoundPoints++ ){
		
		if ( pImageSearchStrToTest->isFound( itrNotFoundPoints->first,
				itrNotFoundPoints->second ) ){
			cerr<<"Error: The point ("<<itrNotFoundPoints->first<<", "<<
				itrNotFoundPoints->second<<") is not found but marked as found. "<<
				"( ! isFound( const unsigned long lX, const unsigned long lY ) )"<<endl;
			uiErrors++;
		}
	}
	//check bool isFound( const pair< unsigned int, unsigned int> & position ) const
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrFoundPoints = setFoundPoints.begin();
			itrFoundPoints != setFoundPoints.end(); itrFoundPoints++ ){
		
		if ( ! pImageSearchStrToTest->isFound( *itrFoundPoints ) ){
			cerr<<"Error: The point ("<<itrFoundPoints->first<<", "<<
				itrFoundPoints->second<<") is found but not marked as found. "<<
				"( isFound( pair< unsigned int, unsigned int > ) )"<<endl;
			uiErrors++;
		}
	}
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrNotFoundPoints = setNotFoundPointsToCheck.begin();
			itrNotFoundPoints != setNotFoundPointsToCheck.end(); itrNotFoundPoints++ ){
		
		if ( pImageSearchStrToTest->isFound( *itrNotFoundPoints ) ){
			cerr<<"Error: The point ("<<itrNotFoundPoints->first<<", "<<
				itrNotFoundPoints->second<<") is not found but marked as found. "<<
				"( ! isFound( pair< unsigned int, unsigned int > ) )"<<endl;
			uiErrors++;
		}
	}
	
	
	//check bool isOverlapped( const cVectorPosition& position ) const
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrOverlappedPoints = setOverlappedPoints.begin();
			itrOverlappedPoints != setOverlappedPoints.end(); itrOverlappedPoints++ ){
		
		if ( ! pImageSearchStrToTest->isOverlapped( toVector( *itrOverlappedPoints ) ) ){
			cerr<<"Error: The point ("<<itrOverlappedPoints->first<<", "<<
				itrOverlappedPoints->second<<") is found but not marked as found. "<<
				"( isOverlapped( const cVectorPosition ) )"<<endl;
			uiErrors++;
		}
	}
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrNotOverlappedPoints = setNotOverlappedPointsToCheck.begin();
			itrNotOverlappedPoints != setNotOverlappedPointsToCheck.end(); itrNotOverlappedPoints++ ){
		
		if ( pImageSearchStrToTest->isOverlapped( toVector( *itrNotOverlappedPoints ) ) ){
			cerr<<"Error: The point ("<<itrNotOverlappedPoints->first<<", "<<
				itrNotOverlappedPoints->second<<") is not found but marked as found. "<<
				"( ! isOverlapped( const cVectorPosition ) )"<<endl;
			uiErrors++;
		}
	}
	//check bool isOverlapped( const unsigned long lX, const unsigned long lY ) const
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrOverlappedPoints = setOverlappedPoints.begin();
			itrOverlappedPoints != setOverlappedPoints.end(); itrOverlappedPoints++ ){
		
		if ( ! pImageSearchStrToTest->isOverlapped( itrOverlappedPoints->first,
				itrOverlappedPoints->second ) ){
			cerr<<"Error: The point ("<<itrOverlappedPoints->first<<", "<<
				itrOverlappedPoints->second<<") is found but not marked as found. "<<
				"( isOverlapped( const unsigned long lX, const unsigned long lY ) )"<<endl;
			uiErrors++;
		}
	}
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrNotOverlappedPoints = setNotOverlappedPointsToCheck.begin();
			itrNotOverlappedPoints != setNotOverlappedPointsToCheck.end(); itrNotOverlappedPoints++ ){
		
		if ( pImageSearchStrToTest->isOverlapped( itrNotOverlappedPoints->first,
				itrNotOverlappedPoints->second ) ){
			cerr<<"Error: The point ("<<itrNotOverlappedPoints->first<<", "<<
				itrNotOverlappedPoints->second<<") is not found but marked as found. "<<
				"( ! isOverlapped( const unsigned long lX, const unsigned long lY ) )"<<endl;
			uiErrors++;
		}
	}
	//check bool isOverlapped( const pair< unsigned int, unsigned int> & position ) const
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrOverlappedPoints = setOverlappedPoints.begin();
			itrOverlappedPoints != setOverlappedPoints.end(); itrOverlappedPoints++ ){
		
		if ( ! pImageSearchStrToTest->isOverlapped( *itrOverlappedPoints ) ){
			cerr<<"Error: The point ("<<itrOverlappedPoints->first<<", "<<
				itrOverlappedPoints->second<<") is found but not marked as found. "<<
				"( isOverlapped( pair< unsigned int, unsigned int > ) )"<<endl;
			uiErrors++;
		}
	}
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrNotOverlappedPoints = setNotOverlappedPointsToCheck.begin();
			itrNotOverlappedPoints != setNotOverlappedPointsToCheck.end(); itrNotOverlappedPoints++ ){
		
		if ( pImageSearchStrToTest->isOverlapped( *itrNotOverlappedPoints ) ){
			cerr<<"Error: The point ("<<itrNotOverlappedPoints->first<<", "<<
				itrNotOverlappedPoints->second<<") is not found but marked as found. "<<
				"( ! isOverlapped( pair< unsigned int, unsigned int > ) )"<<endl;
			uiErrors++;
		}
	}
	
	
	//check bool isFoundOrOverlapped( const cVectorPosition& position ) const
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrFoundPoints = setFoundPoints.begin();
			itrFoundPoints != setFoundPoints.end(); itrFoundPoints++ ){
		
		if ( ! pImageSearchStrToTest->isFoundOrOverlapped( toVector( *itrFoundPoints ) ) ){
			cerr<<"Error: The point ("<<itrFoundPoints->first<<", "<<
				itrFoundPoints->second<<") is found but not marked as found or overlapped. "<<
				"( isFoundOrOverlapped( const cVectorPosition ) )"<<endl;
			uiErrors++;
		}
	}
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrOverlappedPoints = setOverlappedPoints.begin();
			itrOverlappedPoints != setOverlappedPoints.end(); itrOverlappedPoints++ ){
		
		if ( ! pImageSearchStrToTest->isFoundOrOverlapped( toVector( *itrOverlappedPoints ) ) ){
			cerr<<"Error: The point ("<<itrOverlappedPoints->first<<", "<<
				itrOverlappedPoints->second<<") is overlapped but not marked as found or overlapped. "<<
				"( isOverlappedOrOverlapped( const cVectorPosition ) )"<<endl;
			uiErrors++;
		}
	}
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrNotFoundAndNotOverlPoints = setNotFoundNotOverlappedPointsToCheck.begin();
			itrNotFoundAndNotOverlPoints != setNotFoundNotOverlappedPointsToCheck.end();
			itrNotFoundAndNotOverlPoints++ ){
		
		if ( pImageSearchStrToTest->isFoundOrOverlapped( toVector( *itrNotFoundAndNotOverlPoints ) ) ){
			cerr<<"Error: The point ("<<itrNotFoundAndNotOverlPoints->first<<", "<<
				itrNotFoundAndNotOverlPoints->second<<") is not found or overlapped but marked as found or overlapped. "<<
				"( ! isFoundOrOverlapped( const cVectorPosition ) )"<<endl;
			uiErrors++;
		}
	}
	//check bool isFoundOrOverlapped( const unsigned long lX, const unsigned long lY ) const
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrFoundPoints = setFoundPoints.begin();
			itrFoundPoints != setFoundPoints.end(); itrFoundPoints++ ){
		
		if ( ! pImageSearchStrToTest->isFoundOrOverlapped( itrFoundPoints->first,
				itrFoundPoints->second ) ){
			cerr<<"Error: The point ("<<itrFoundPoints->first<<", "<<
				itrFoundPoints->second<<") is found but not marked as found or overlapped. "<<
				"( isFoundOrOverlapped( const unsigned long lX, const unsigned long lY ) )"<<endl;
			uiErrors++;
		}
	}
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrOverlappedPoints = setOverlappedPoints.begin();
			itrOverlappedPoints != setOverlappedPoints.end(); itrOverlappedPoints++ ){
		
		if ( ! pImageSearchStrToTest->isFoundOrOverlapped( itrOverlappedPoints->first,
				itrOverlappedPoints->second ) ){
			cerr<<"Error: The point ("<<itrOverlappedPoints->first<<", "<<
				itrOverlappedPoints->second<<") is overlapped but not marked as found or overlapped. "<<
				"( isFoundOrOverlapped( const unsigned long lX, const unsigned long lY ) )"<<endl;
			uiErrors++;
		}
	}
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrNotFoundAndNotOverlPoints = setNotFoundNotOverlappedPointsToCheck.begin();
			itrNotFoundAndNotOverlPoints != setNotFoundNotOverlappedPointsToCheck.end();
			itrNotFoundAndNotOverlPoints++ ){
		
		if ( pImageSearchStrToTest->isFoundOrOverlapped( itrNotFoundAndNotOverlPoints->first,
				itrNotFoundAndNotOverlPoints->second ) ){
			cerr<<"Error: The point ("<<itrNotFoundAndNotOverlPoints->first<<", "<<
				itrNotFoundAndNotOverlPoints->second<<") is not found or overlapped but marked as found or overlapped. "<<
				"( ! isFoundOrOverlapped( const unsigned long lX, const unsigned long lY ) )"<<endl;
			uiErrors++;
		}
	}
	//check bool isFoundOrOverlapped( const pair< unsigned int, unsigned int> & position ) const
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrFoundPoints = setFoundPoints.begin();
			itrFoundPoints != setFoundPoints.end(); itrFoundPoints++ ){
		
		if ( ! pImageSearchStrToTest->isFoundOrOverlapped( *itrFoundPoints ) ){
			cerr<<"Error: The point ("<<itrFoundPoints->first<<", "<<
				itrFoundPoints->second<<") is found but not marked as found or overlapped. "<<
				"( isFoundOrOverlapped( pair< unsigned int, unsigned int > ) )"<<endl;
			uiErrors++;
		}
	}
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrOverlappedPoints = setOverlappedPoints.begin();
			itrOverlappedPoints != setOverlappedPoints.end(); itrOverlappedPoints++ ){
		
		if ( ! pImageSearchStrToTest->isFoundOrOverlapped( *itrOverlappedPoints ) ){
			cerr<<"Error: The point ("<<itrOverlappedPoints->first<<", "<<
				itrOverlappedPoints->second<<") is overlapped but not marked as found or overlapped. "<<
				"( isFoundOrOverlapped( pair< unsigned int, unsigned int > ) )"<<endl;
			uiErrors++;
		}
	}
	for ( set< pair< unsigned int, unsigned int > >::const_iterator
			itrNotFoundAndNotOverlPoints = setNotFoundNotOverlappedPointsToCheck.begin();
			itrNotFoundAndNotOverlPoints != setNotFoundNotOverlappedPointsToCheck.end();
			itrNotFoundAndNotOverlPoints++ ){
		
		if ( pImageSearchStrToTest->isFoundOrOverlapped( *itrNotFoundAndNotOverlPoints ) ){
			cerr<<"Error: The point ("<<itrNotFoundAndNotOverlPoints->first<<", "<<
				itrNotFoundAndNotOverlPoints->second<<") is not found or overlapped but marked as found or overlapped. "<<
				"( ! isFoundOrOverlapped( pair< unsigned int, unsigned int > ) )"<<endl;
			uiErrors++;
		}
	}
	
	{//check set<cVectorPosition> getFoundPoints() const;
		const set<cVectorPosition> setFoundPointsStr =
			pImageSearchStrToTest->getFoundPoints();
		
		if ( comparePoints( setFoundPoints, toPair( setFoundPointsStr ) ) != 0 ){
			cerr<<"Error: in setFoundPointsStr = pImageSearchStrToTest->getFoundPoints();"<<endl;
			cerr<<"returned points: ";
			printPoints( cerr, setFoundPointsStr );
			uiErrors++;
		}
	}
	{//check set< pair< unsigned int, unsigned int> > getFoundPointsAsPair() const;
		const set< pair< unsigned int, unsigned int > > setFoundPointsStr =
			pImageSearchStrToTest->getFoundPointsAsPair();
		
		if ( comparePoints( setFoundPoints, setFoundPointsStr ) != 0 ){
			cerr<<"Error: in setFoundPointsStr = pImageSearchStrToTest->getFoundPoints();"<<endl;
			cerr<<"returned points: ";
			printPoints( cerr, setFoundPointsStr );
			uiErrors++;
		}
	}
	{//check set<cVectorPosition> getNotFoundPoints() const;
		const set<cVectorPosition> setNotFoundPointsStr =
			pImageSearchStrToTest->getNotFoundPoints();
		
		if ( comparePoints( setNotFoundPoints, toPair( setNotFoundPointsStr ) ) != 0 ){
			cerr<<"Error: in setNotFoundPointsStr = pImageSearchStrToTest->getNotFoundPoints();"<<endl;
			cerr<<"returned points: ";
			printPoints( cerr, setNotFoundPointsStr );
			uiErrors++;
		}
	}
	{//check set< pair< unsigned int, unsigned int> > getNotFoundPointsAsPair() const;
		const set< pair< unsigned int, unsigned int > > setNotFoundPointsStr =
			pImageSearchStrToTest->getNotFoundPointsAsPair();
		
		if ( comparePoints( setNotFoundPoints, setNotFoundPointsStr ) != 0 ){
			cerr<<"Error: in setNotFoundPointsStr = pImageSearchStrToTest->getNotFoundPointsAsPair();"<<endl;
			cerr<<"returned points: ";
			printPoints( cerr, setNotFoundPointsStr );
			uiErrors++;
		}
	}
	
	{//check set<cVectorPosition> getOverlappedPoints() const;
		const set<cVectorPosition> setOverlappedPointsStr =
			pImageSearchStrToTest->getOverlappedPoints();
		
		if ( comparePoints( setOverlappedPoints, toPair( setOverlappedPointsStr ) ) != 0 ){
			cerr<<"Error: in setOverlappedPointsStr = pImageSearchStrToTest->getOverlappedPoints();"<<endl;
			cerr<<"returned points: ";
			printPoints( cerr, setOverlappedPointsStr );
			uiErrors++;
		}
	}
	{//check set< pair< unsigned int, unsigned int> > getOverlappedPointsAsPair() const;
		const set< pair< unsigned int, unsigned int > > setOverlappedPointsStr =
			pImageSearchStrToTest->getOverlappedPointsAsPair();
		
		if ( comparePoints( setOverlappedPoints, setOverlappedPointsStr ) != 0 ){
			cerr<<"Error: in setOverlappedPointsStr = pImageSearchStrToTest->getOverlappedPoints();"<<endl;
			cerr<<"returned points: ";
			printPoints( cerr, setOverlappedPointsStr );
			uiErrors++;
		}
	}
	{//check set<cVectorPosition> getNotOverlappedPoints() const;
		const set<cVectorPosition> setNotOverlappedPointsStr =
			pImageSearchStrToTest->getNotOverlappedPoints();
		
		if ( comparePoints( setNotOverlappedPoints, toPair( setNotOverlappedPointsStr ) ) != 0 ){
			cerr<<"Error: in setNotOverlappedPointsStr = pImageSearchStrToTest->getNotOverlappedPoints();"<<endl;
			cerr<<"returned points: ";
			printPoints( cerr, setNotOverlappedPointsStr );
			uiErrors++;
		}
	}
	{//check set< pair< unsigned int, unsigned int> > getNotOverlappedPointsAsPair() const;
		const set< pair< unsigned int, unsigned int > > setNotOverlappedPointsStr =
			pImageSearchStrToTest->getNotOverlappedPointsAsPair();
		
		if ( comparePoints( setNotOverlappedPoints, setNotOverlappedPointsStr ) != 0 ){
			cerr<<"Error: in setNotOverlappedPointsStr = pImageSearchStrToTest->getNotOverlappedPointsAsPair();"<<endl;
			cerr<<"returned points: ";
			printPoints( cerr, setNotOverlappedPointsStr );
			uiErrors++;
		}
	}
	
	//neighbour tests
	const unsigned int uiNumberOfIterations = rand() % MAX_ITERATION;
	for ( unsigned long uiIteration = 0;
			uiIteration < uiNumberOfIterations; uiIteration++ ){
		
		//generate a random points for the neighbour tests
		const pair< unsigned int, unsigned int>
			paPoint = generateRandomPointPair( uiWidth + 2, uiHeight + 2 );
		//evalue the points neighbour points
		vector< pair< long, long> > vecPoint( 4, paPoint );
		vecPoint[ 0 ].first++;
		vecPoint[ 1 ].first--;
		vecPoint[ 2 ].second++;
		vecPoint[ 3 ].second--;
		
		{//check set<cVectorPosition> getNeighbours( const cVectorPosition& position ) const;
			set<cVectorPosition> setNeighbourPoints =
				pImageSearchStrToTest->getNeighbours( toVector( paPoint ) );
			
			for ( vector< pair< long, long> >::iterator itrPoint = vecPoint.begin();
					itrPoint != vecPoint.end(); itrPoint++ ){
				
				set<cVectorPosition>::iterator
					itrNeighbourPoint = setNeighbourPoints.find( toVector( *itrPoint ) );
				if ( itrNeighbourPoint != setNeighbourPoints.end() ){
					//point in returned set
					setNeighbourPoints.erase( itrNeighbourPoint );
					
					if ( ! checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						//neighbour point not in search area
						cerr<<"Error: The point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is not in the area, but was given back as neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}
				}else{//point not in returned set
					if ( checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						//neighbour point in search area (should be returned as neighbour)
						cerr<<"Error: The point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is not a neighbour of the point ("<<
							paPoint.first<<", "<<paPoint.second<<")"<<endl;
						uiErrors++;
					}
				}
			}
			if ( ! setNeighbourPoints.empty() ){
				cerr<<"Error: There wher "<<setNeighbourPoints.size()<<
					" found neighbours of the point ("<<
					paPoint.first<<", "<<paPoint.second<<") given back which aren't:"<<endl;
				printPoints( cerr, setNeighbourPoints );
				uiErrors++;
			}
		}
		{//check set< pair< unsigned int, unsigned int> > getNeighbours( const pair< unsigned int, unsigned int> & position ) const;
			set< pair< unsigned int, unsigned int> > setNeighbourPointsPair =
				pImageSearchStrToTest->getNeighbours( paPoint );
			
			for ( vector< pair< long, long> >::iterator itrPoint = vecPoint.begin();
					itrPoint != vecPoint.end(); itrPoint++ ){
				
				set< pair< unsigned int, unsigned int> >::iterator
					itrNeighbourPoint = setNeighbourPointsPair.find( *itrPoint );
				if ( itrNeighbourPoint != setNeighbourPointsPair.end() ){
					//point in returned set
					setNeighbourPointsPair.erase( itrNeighbourPoint );
					
					if ( ! checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						//neighbour point not in search area
						cerr<<"Error: The pair point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is not in the area, but was given back as neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}
				}else{//point not in returned set
					if ( checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						//neighbour point in search area (should be returned as neighbour)
						cerr<<"Error: The pair point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is not a neighbour of the point ("<<
							paPoint.first<<", "<<paPoint.second<<")"<<endl;
						uiErrors++;
					}
				}
			}
			if ( ! setNeighbourPointsPair.empty() ){
				cerr<<"Error: There wher "<<setNeighbourPointsPair.size()<<
					" found neighbours of the pair point ("<<
					paPoint.first<<", "<<paPoint.second<<") given back which aren't:"<<endl;
				printPoints( cerr, setNeighbourPointsPair );
				uiErrors++;
			}
		}
		
		{//check set<cVectorPosition> getFoundNeighbours( const cVectorPosition& position ) const;
			set<cVectorPosition> setNeighbourPoints =
				pImageSearchStrToTest->getFoundNeighbours( toVector( paPoint ) );
			
			for ( vector< pair< long, long> >::iterator itrPoint = vecPoint.begin();
					itrPoint != vecPoint.end(); itrPoint++ ){
				
				set<cVectorPosition>::iterator
					itrNeighbourPoint = setNeighbourPoints.find( toVector( *itrPoint ) );
				
				const bool bPointFound = pImageSearchStrToTest->isFound( *itrPoint );
				
				if ( itrNeighbourPoint != setNeighbourPoints.end() ){
					//point in returned set
					setNeighbourPoints.erase( itrNeighbourPoint );
					
					if ( ! checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						//neighbour point not in search area
						cerr<<"Error: The point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is not in the area, but was given back as found neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}else if ( ! bPointFound ){
						//point was not found but returned as found
						cerr<<"Error: The point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is not found, but was given back as found neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}
				}else{//point not in returned set
					if ( checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						if ( bPointFound ){
							//neighbour point in search area (should be returned as neighbour)
							cerr<<"Error: The point ("<<itrPoint->first<<","<<itrPoint->second<<
								") is a found neighbour of the point ("<<
								paPoint.first<<", "<<paPoint.second<<") but was not given back as one."<<endl;
							uiErrors++;
						}
					}
				}
			}
			if ( ! setNeighbourPoints.empty() ){
				cerr<<"Error: There wher "<<setNeighbourPoints.size()<<
					" found neighbours of the point ("<<
					paPoint.first<<", "<<paPoint.second<<") given back which aren't:"<<endl;
				printPoints( cerr, setNeighbourPoints );
				uiErrors++;
			}
		}
		{//check set< pair< unsigned int, unsigned int> > getFoundNeighbours( const pair< unsigned int, unsigned int>  & position ) const;
			set< pair< unsigned int, unsigned int> > setNeighbourPoints =
				pImageSearchStrToTest->getFoundNeighbours( paPoint );
			
			for ( vector< pair< long, long> >::iterator itrPoint = vecPoint.begin();
					itrPoint != vecPoint.end(); itrPoint++ ){
				
				set< pair< unsigned int, unsigned int> >::iterator
					itrNeighbourPoint = setNeighbourPoints.find( *itrPoint );
				
				const bool bPointFound = pImageSearchStrToTest->isFound( *itrPoint );
				
				if ( itrNeighbourPoint != setNeighbourPoints.end() ){
					//point in returned set
					setNeighbourPoints.erase( itrNeighbourPoint );
					
					if ( ! checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						//neighbour point not in search area
						cerr<<"Error: The pair point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is not in the area, but was given back as found neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}else if ( ! bPointFound ){
						//point was not found but returned as found
						cerr<<"Error: The pair point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is not found, but was given back as found neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}
				}else{//point not in returned set
					if ( checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						if ( bPointFound ){
							//neighbour point in search area (should be returned as neighbour)
							cerr<<"Error: The pair point ("<<itrPoint->first<<","<<itrPoint->second<<
								") is a found neighbour of the point ("<<
								paPoint.first<<", "<<paPoint.second<<") but was not given back as one."<<endl;
							uiErrors++;
						}
					}
				}
			}
			if ( ! setNeighbourPoints.empty() ){
				cerr<<"Error: There wher "<<setNeighbourPoints.size()<<
					" not found neighbours of the pair point ("<<
					paPoint.first<<", "<<paPoint.second<<") given back which aren't:"<<endl;
				printPoints( cerr, setNeighbourPoints );
				uiErrors++;
			}
		}
		
		{//check set<cVectorPosition> getNotFoundNeighbours( const cVectorPosition& position ) const;
			set<cVectorPosition> setNeighbourPoints =
				pImageSearchStrToTest->getNotFoundNeighbours( toVector( paPoint ) );
			
			for ( vector< pair< long, long> >::iterator itrPoint = vecPoint.begin();
					itrPoint != vecPoint.end(); itrPoint++ ){
				
				set<cVectorPosition>::iterator
					itrNeighbourPoint = setNeighbourPoints.find( toVector( *itrPoint ) );
				
				const bool bPointFound = pImageSearchStrToTest->isFound( *itrPoint );
				
				if ( itrNeighbourPoint != setNeighbourPoints.end() ){
					//point in returned set
					setNeighbourPoints.erase( itrNeighbourPoint );
					
					if ( ! checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						//neighbour point not in search area
						cerr<<"Error: The point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is not in the area, but was given back as not found neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}else if ( bPointFound ){
						//point was not found but returned as found
						cerr<<"Error: The point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is found, but was given back as not found neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}
				}else{//point not in returned set
					if ( checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						if ( ! bPointFound ){
							//neighbour point in search area (should be returned as neighbour)
							cerr<<"Error: The point ("<<itrPoint->first<<","<<itrPoint->second<<
								") is a not found neighbour of the point ("<<
								paPoint.first<<", "<<paPoint.second<<") but was not given back as one."<<endl;
							uiErrors++;
						}
					}
				}
			}
			if ( ! setNeighbourPoints.empty() ){
				cerr<<"Error: There wher "<<setNeighbourPoints.size()<<
					" not found neighbours of the point ("<<
					paPoint.first<<", "<<paPoint.second<<") given back which aren't:"<<endl;
				printPoints( cerr, setNeighbourPoints );
				uiErrors++;
			}
		}
		{//check set< pair< unsigned int, unsigned int> > getNotFoundNeighbours( const pair< unsigned int, unsigned int>  & position ) const;
			set< pair< unsigned int, unsigned int> > setNeighbourPoints =
				pImageSearchStrToTest->getNotFoundNeighbours( paPoint );
			
			for ( vector< pair< long, long> >::iterator itrPoint = vecPoint.begin();
					itrPoint != vecPoint.end(); itrPoint++ ){
				
				set< pair< unsigned int, unsigned int> >::iterator
					itrNeighbourPoint = setNeighbourPoints.find( *itrPoint );
				
				const bool bPointFound = pImageSearchStrToTest->isFound( *itrPoint );
				
				if ( itrNeighbourPoint != setNeighbourPoints.end() ){
					//point in returned set
					setNeighbourPoints.erase( itrNeighbourPoint );
					
					if ( ! checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						//neighbour point not in search area
						cerr<<"Error: The pair point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is not in the area, but was given back as not found neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}else if ( bPointFound ){
						//point was not found but returned as found
						cerr<<"Error: The pair point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is found, but was given back as not found neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}
				}else{//point not in returned set
					if ( checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						if ( ! bPointFound ){
							//neighbour point in search area (should be returned as neighbour)
							cerr<<"Error: The pair point ("<<itrPoint->first<<","<<itrPoint->second<<
								") is a not found neighbour of the point ("<<
								paPoint.first<<", "<<paPoint.second<<") but was not given back as one."<<endl;
							uiErrors++;
						}
					}
				}
			}
			if ( ! setNeighbourPoints.empty() ){
				cerr<<"Error: There wher not found neighbours of the pair point ("<<
					paPoint.first<<", "<<paPoint.second<<") given back which aren't:"<<endl;
				printPoints( cerr, setNeighbourPoints );
				uiErrors++;
			}
		}
		
		
		{//check set<cVectorPosition> getOverlappedNeighbours( const cVectorPosition& position ) const;
			set<cVectorPosition> setNeighbourPoints =
				pImageSearchStrToTest->getOverlappedNeighbours( toVector( paPoint ) );
			
			for ( vector< pair< long, long> >::iterator itrPoint = vecPoint.begin();
					itrPoint != vecPoint.end(); itrPoint++ ){
				
				set<cVectorPosition>::iterator
					itrNeighbourPoint = setNeighbourPoints.find( toVector( *itrPoint ) );
				
				const bool bPointOverlapped = pImageSearchStrToTest->isOverlapped( *itrPoint );
				
				if ( itrNeighbourPoint != setNeighbourPoints.end() ){
					//point in returned set
					setNeighbourPoints.erase( itrNeighbourPoint );
					
					if ( ! checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						//neighbour point not in search area
						cerr<<"Error: The point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is not in the area, but was given back as overlapped neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}else if ( ! bPointOverlapped ){
						//point was not overlapped but returned as overlapped
						cerr<<"Error: The point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is not overlapped, but was given back as overlapped neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}
				}else{//point not in returned set
					if ( checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						if ( bPointOverlapped ){
							//neighbour point in search area (should be returned as neighbour)
							cerr<<"Error: The point ("<<itrPoint->first<<","<<itrPoint->second<<
								") is a overlapped neighbour of the point ("<<
								paPoint.first<<", "<<paPoint.second<<") but was not given back as one."<<endl;
							uiErrors++;
						}
					}
				}
			}
			if ( ! setNeighbourPoints.empty() ){
				cerr<<"Error: There wher "<<setNeighbourPoints.size()<<
					" overlapped neighbours of the point ("<<
					paPoint.first<<", "<<paPoint.second<<") given back which aren't:"<<endl;
				printPoints( cerr, setNeighbourPoints );
				uiErrors++;
			}
		}
		{//check set< pair< unsigned int, unsigned int> > getOverlappedNeighbours( const pair< unsigned int, unsigned int>  & position ) const;
			set< pair< unsigned int, unsigned int> > setNeighbourPoints =
				pImageSearchStrToTest->getOverlappedNeighbours( paPoint );
			
			for ( vector< pair< long, long> >::iterator itrPoint = vecPoint.begin();
					itrPoint != vecPoint.end(); itrPoint++ ){
				
				set< pair< unsigned int, unsigned int> >::iterator
					itrNeighbourPoint = setNeighbourPoints.find( *itrPoint );
				
				const bool bPointOverlapped = pImageSearchStrToTest->isOverlapped( *itrPoint );
				
				if ( itrNeighbourPoint != setNeighbourPoints.end() ){
					//point in returned set
					setNeighbourPoints.erase( itrNeighbourPoint );
					
					if ( ! checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						//neighbour point not in search area
						cerr<<"Error: The pair point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is not in the area, but was given back as overlapped neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}else if ( ! bPointOverlapped ){
						//point was not overlapped but returned as overlapped
						cerr<<"Error: The pair point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is not overlapped, but was given back as overlapped neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}
				}else{//point not in returned set
					if ( checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						if ( bPointOverlapped ){
							//neighbour point in search area (should be returned as neighbour)
							cerr<<"Error: The pair point ("<<itrPoint->first<<","<<itrPoint->second<<
								") is a overlapped neighbour of the point ("<<
								paPoint.first<<", "<<paPoint.second<<") but was not given back as one."<<endl;
							uiErrors++;
						}
					}
				}
			}
			if ( ! setNeighbourPoints.empty() ){
				cerr<<"Error: There wher "<<setNeighbourPoints.size()<<
					" overlapped neighbours of the pair point ("<<
					paPoint.first<<", "<<paPoint.second<<") given back which aren't:"<<endl;
				printPoints( cerr, setNeighbourPoints );
				uiErrors++;
			}
		}
		
		{//check set<cVectorPosition> getNotOverlappedNeighbours( const cVectorPosition& position ) const;
			set<cVectorPosition> setNeighbourPoints =
				pImageSearchStrToTest->getNotOverlappedNeighbours( toVector( paPoint ) );
			
			for ( vector< pair< long, long> >::iterator itrPoint = vecPoint.begin();
					itrPoint != vecPoint.end(); itrPoint++ ){
				
				set<cVectorPosition>::iterator
					itrNeighbourPoint = setNeighbourPoints.find( toVector( *itrPoint ) );
				
				const bool bPointOverlapped = pImageSearchStrToTest->isOverlapped( *itrPoint );
				
				if ( itrNeighbourPoint != setNeighbourPoints.end() ){
					//point in returned set
					setNeighbourPoints.erase( itrNeighbourPoint );
					
					if ( ! checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						//neighbour point not in search area
						cerr<<"Error: The point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is not in the area, but was given back as not overlapped neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}else if ( bPointOverlapped ){
						//point was not overlapped but returned as overlapped
						cerr<<"Error: The point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is overlapped, but was given back as not overlapped neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}
				}else{//point not in returned set
					if ( checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						if ( ! bPointOverlapped ){
							//neighbour point in search area (should be returned as neighbour)
							cerr<<"Error: The point ("<<itrPoint->first<<","<<itrPoint->second<<
								") is a not overlapped neighbour of the point ("<<
								paPoint.first<<", "<<paPoint.second<<") but was not given back as one."<<endl;
							uiErrors++;
						}
					}
				}
			}
			if ( ! setNeighbourPoints.empty() ){
				cerr<<"Error: There wher "<<setNeighbourPoints.size()<<
					" not overlapped neighbours of the point ("<<
					paPoint.first<<", "<<paPoint.second<<") given back which aren't:"<<endl;
				printPoints( cerr, setNeighbourPoints );
				uiErrors++;
			}
		}
		{//check set< pair< unsigned int, unsigned int> > getNotOverlappedNeighbours( const pair< unsigned int, unsigned int>  & position ) const;
			set< pair< unsigned int, unsigned int> > setNeighbourPoints =
				pImageSearchStrToTest->getNotOverlappedNeighbours( paPoint );
			
			for ( vector< pair< long, long> >::iterator itrPoint = vecPoint.begin();
					itrPoint != vecPoint.end(); itrPoint++ ){
				
				set< pair< unsigned int, unsigned int> >::iterator
					itrNeighbourPoint = setNeighbourPoints.find( *itrPoint );
				
				const bool bPointOverlapped = pImageSearchStrToTest->isOverlapped( *itrPoint );
				
				if ( itrNeighbourPoint != setNeighbourPoints.end() ){
					//point in returned set
					setNeighbourPoints.erase( itrNeighbourPoint );
					
					if ( ! checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						//neighbour point not in search area
						cerr<<"Error: The pair point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is not in the area, but was given back as not overlapped neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}else if ( bPointOverlapped ){
						//point was not overlapped but returned as overlapped
						cerr<<"Error: The pair point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is overlapped, but was given back as not overlapped neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}
				}else{//point not in returned set
					if ( checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						if ( ! bPointOverlapped ){
							//neighbour point in search area (should be returned as neighbour)
							cerr<<"Error: The pair point ("<<itrPoint->first<<","<<itrPoint->second<<
								") is a not overlapped neighbour of the point ("<<
								paPoint.first<<", "<<paPoint.second<<") but was not given back as one."<<endl;
							uiErrors++;
						}
					}
				}
			}
			if ( ! setNeighbourPoints.empty() ){
				cerr<<"Error: There wher "<<setNeighbourPoints.size()<<
					" not overlapped neighbours of the pair point ("<<
					paPoint.first<<", "<<paPoint.second<<") given back which aren't:"<<endl;
				printPoints( cerr, setNeighbourPoints );
				uiErrors++;
			}
		}
		
		
		
		{//check set<cVectorPosition> getNotFoundNotOverlappedNeighbours( const cVectorPosition& position ) const;
			set<cVectorPosition> setNeighbourPoints =
				pImageSearchStrToTest->getNotFoundNotOverlappedNeighbours( toVector( paPoint ) );
			
			//check bool hasNotFoundNotOverlappedNeighbours( const cVectorPosition& position ) const;
			if ( setNeighbourPoints.empty() == pImageSearchStrToTest->
					hasNotFoundNotOverlappedNeighbours( toVector( paPoint ) ) ){
				cerr<<"Error: The point ("<<paPoint.first<<", "<<paPoint.second<<
					") has "<<(setNeighbourPoints.empty()?"no ":"")<<
					"not found and not overlapped neighbours, but "<<
					"hasNotFoundNotOverlappedNeighbours() gives back "<<
					(pImageSearchStrToTest->hasNotFoundNotOverlappedNeighbours( toVector( paPoint ) )?"true":"false")<<" ."<<endl;
				uiErrors++;
			}
			for ( vector< pair< long, long> >::iterator itrPoint = vecPoint.begin();
					itrPoint != vecPoint.end(); itrPoint++ ){
				
				set<cVectorPosition>::iterator
					itrNeighbourPoint = setNeighbourPoints.find( toVector( *itrPoint ) );
				
				const bool bPointNotFoundAndNotOverlapped =
					( ! pImageSearchStrToTest->isFound( *itrPoint ) ) &&
					( ! pImageSearchStrToTest->isOverlapped( *itrPoint ) );
				
				if ( itrNeighbourPoint != setNeighbourPoints.end() ){
					//point in returned set
					setNeighbourPoints.erase( itrNeighbourPoint );
					
					if ( ! checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						//neighbour point not in search area
						cerr<<"Error: The point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is not in the area, but was given back as not found and not overlapped neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}else if ( ! bPointNotFoundAndNotOverlapped ){
						//point was not overlapped but returned as overlapped
						cerr<<"Error: The point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is overlapped, but was given back as not found and not overlapped neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}
				}else{//point not in returned set
					if ( checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						if ( bPointNotFoundAndNotOverlapped ){
							//neighbour point in search area (should be returned as neighbour)
							cerr<<"Error: The point ("<<itrPoint->first<<","<<itrPoint->second<<
								") is a not found and not overlapped neighbour of the point ("<<
								paPoint.first<<", "<<paPoint.second<<") but was not given back as one."<<endl;
							uiErrors++;
						}
					}
				}
			}
			if ( ! setNeighbourPoints.empty() ){
				cerr<<"Error: There wher "<<setNeighbourPoints.size()<<
					" not found and not overlapped neighbours of the point ("<<
					paPoint.first<<", "<<paPoint.second<<") given back which aren't:"<<endl;
				printPoints( cerr, setNeighbourPoints );
				uiErrors++;
			}
		}
		{//check set< pair< unsigned int, unsigned int> > getNotFoundNotOverlappedNeighbours( const pair< unsigned int, unsigned int>  & position ) const;
			set< pair< unsigned int, unsigned int> > setNeighbourPoints =
				pImageSearchStrToTest->getNotFoundNotOverlappedNeighbours( paPoint );
			
			//check bool hasNotFoundNotOverlappedNeighbours( const pair< unsigned int, unsigned int> & position ) const;
			if ( setNeighbourPoints.empty() == pImageSearchStrToTest->
					hasNotFoundNotOverlappedNeighbours( paPoint ) ){
				cerr<<"Error: The pair point ("<<paPoint.first<<", "<<paPoint.second<<
					") has "<<(setNeighbourPoints.empty()?"no ":"")<<
					"not found and not overlapped neighbours, but "<<
					"hasNotFoundNotOverlappedNeighbours() gives back "<<
					(pImageSearchStrToTest->hasNotFoundNotOverlappedNeighbours( paPoint )?"true":"false")<<" ."<<endl;
				uiErrors++;
			}
			for ( vector< pair< long, long> >::iterator itrPoint = vecPoint.begin();
					itrPoint != vecPoint.end(); itrPoint++ ){
				
				set< pair< unsigned int, unsigned int> >::iterator
					itrNeighbourPoint = setNeighbourPoints.find( *itrPoint );
				
				const bool bPointNotFoundAndNotOverlapped =
					( ! pImageSearchStrToTest->isFound( *itrPoint ) ) &&
					( ! pImageSearchStrToTest->isOverlapped( *itrPoint ) );
				
				if ( itrNeighbourPoint != setNeighbourPoints.end() ){
					//point in returned set
					setNeighbourPoints.erase( itrNeighbourPoint );
					
					if ( ! checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						//neighbour point not in search area
						cerr<<"Error: The pair point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is not in the area, but was given back as not found and not overlapped neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}else if ( ! bPointNotFoundAndNotOverlapped ){
						//point was not overlapped but returned as overlapped
						cerr<<"Error: The pair point ("<<itrPoint->first<<","<<itrPoint->second<<
							") is overlapped, but was given back as not found and not overlapped neighbour of point ("<<
							paPoint.first<<", "<<paPoint.second<<") )"<<endl;
						uiErrors++;
					}
				}else{//point not in returned set
					if ( checkPoint( *itrPoint, uiWidth, uiHeight ) ){
						if ( bPointNotFoundAndNotOverlapped ){
							//neighbour point in search area (should be returned as neighbour)
							cerr<<"Error: The pair point ("<<itrPoint->first<<","<<itrPoint->second<<
								") is a not found and not overlapped neighbour of the point ("<<
								paPoint.first<<", "<<paPoint.second<<") but was not given back as one."<<endl;
							uiErrors++;
						}
					}
				}
			}
			if ( ! setNeighbourPoints.empty() ){
				cerr<<"Error: There wher "<<setNeighbourPoints.size()<<
					" not found and not overlapped neighbours of the pair point ("<<
					paPoint.first<<", "<<paPoint.second<<") given back which aren't:"<<endl;
				printPoints( cerr, setNeighbourPoints );
				uiErrors++;
			}
		}
		
	}
	
	return uiErrors;
}


/**
 * This function tests the cImageStructure methods.
 *
 *
 * What's tested of class cImageSearchData:
 * 	- cImageSearchData( const unsigned long ulInWidth, const unsigned long ulInHeight );
 * 	- cImageSearchData( const iImageData * pInImageData );
 * 	- cImageSearchData( const cImageSearchData & imageSearchData );
 * 	- ~cImageSearchData();
 * 	- cImageSearchData * clone() const;
 * 	- cImageSearchData & operator=( const cImageSearchData & imageSearchData );
 * 	- unsigned long getWidth() const;
 * 	- unsigned long getHeight() const;
 * 	- const iImageData * getImageData() const;
 * 	- bool isFound( const cVectorPosition& position ) const;
 * 	- bool isFound( const unsigned long lX, const unsigned long lY ) const;
 * 	- bool isOverlapped( const cVectorPosition& position ) const;
 * 	- bool isOverlapped( const unsigned long lX, const unsigned long lY ) const;
 * 	- bool isFoundOrOverlapped( const cVectorPosition& position ) const;
 * 	- bool isFoundOrOverlapped( const unsigned long lX, const unsigned long lY ) const;
 * 	- bool isFoundOrOverlapped( const pair< unsigned int, unsigned int> & position ) const;
 * 	- set<cVectorPosition> getFoundPoints() const;
 * 	- set<cVectorPosition> getNotFoundPoints() const;
 * 	- set<cVectorPosition> getOverlappedPoints() const;
 * 	- set<cVectorPosition> getNotOverlappedPoints() const;
 * 	- set<cVectorPosition> getNeighbours( const cVectorPosition& position ) const;
 * 	- set<cVectorPosition> getFoundNeighbours( const cVectorPosition& position ) const;
 * 	- set<cVectorPosition> getNotFoundNeighbours( const cVectorPosition& position ) const;
 * 	- set<cVectorPosition> getOverlappedNeighbours( const cVectorPosition& position ) const;
 * 	- set<cVectorPosition> getNotOverlappedNeighbours( const cVectorPosition& position ) const;
 * 	- set<cVectorPosition> getNotFoundNotOverlappedNeighbours( const cVectorPosition& position ) const;
 * 	- bool hasNotFoundNotOverlappedNeighbours( const cVectorPosition& position ) const;
 * 	- bool registerFound( const cVectorPosition & foundPoint, const bool bFound=true );
 * 	- unsigned long registerFound( const set<cVectorPosition> & setFoundPoints, const bool bFound=true );
 * 	- unsigned long registerFound( const cImageStructure * pImageStrFoundPoints, const bool bFound=true );
 * 	- bool registerOverlapped( const cVectorPosition & overlappedPoint, const bool bOverlapped=true );
 * 	- unsigned long registerOverlapped( const set<cVectorPosition> & setOverlappedPoints, const bool bOverlapped=true );
 * 	- unsigned long registerOverlapped( const cImageStructure * pImageStrOverlappedPoints, const bool bOverlapped=true );
 * 	- void foundToOverlapped();
 * 	- void clearFound();
 * 	- void clearOverlapped();
 * 	- bool isFound( const pair< unsigned int, unsigned int> & position ) const;
 * 	- bool isOverlapped( const pair< unsigned int, unsigned int> & position ) const;
 * 	- set< pair< unsigned int, unsigned int> > getFoundPointsAsPair() const;
 * 	- set< pair< unsigned int, unsigned int> > getNotFoundPointsAsPair() const;
 * 	- set< pair< unsigned int, unsigned int> > getOverlappedPointsAsPair() const;
 * 	- set< pair< unsigned int, unsigned int> > getNotOverlappedPointsAsPair() const;
 * 	- set< pair< unsigned int, unsigned int> > getNeighbours( const pair< unsigned int, unsigned int> & position ) const;
 * 	- set< pair< unsigned int, unsigned int> > getFoundNeighbours( const pair< unsigned int, unsigned int>  & position ) const;
 * 	- set< pair< unsigned int, unsigned int> > getNotFoundNeighbours( const pair< unsigned int, unsigned int> & position ) const;
 * 	- set< pair< unsigned int, unsigned int> > getOverlappedNeighbours( const pair< unsigned int, unsigned int> & position ) const;
 * 	- set< pair< unsigned int, unsigned int> > getNotOverlappedNeighbours( const pair< unsigned int, unsigned int> & position ) const;
 * 	- set< pair< unsigned int, unsigned int> > getNotFoundNotOverlappedNeighbours( const pair< unsigned int, unsigned int> & position ) const;
 * 	- bool hasNotFoundNotOverlappedNeighbours( const pair< unsigned int, unsigned int> & position ) const;
 * 	- bool registerFound( const pair< unsigned int, unsigned int> & foundPoint, const bool bFound=true );
 * 	- unsigned long registerFound( const set< pair< unsigned int, unsigned int> > & setFoundPoints, const bool bFound=true );
 * 	- bool registerOverlapped( const pair< unsigned int, unsigned int> & overlappedPoint, const bool bOverlapped=true );
 * 	- unsigned long registerOverlapped( const set< pair< unsigned int, unsigned int> > & setOverlappedPoints, const bool bOverlapped=true );
 *
 * @param ulTestphase a reference to the number for the test phase
 * @return the number of errors occured in the test
 */
int testMethodsRandom( unsigned long &ulTestphase ){
	
	int iReturn = 0;//return value of the test; the number of occured errors
	
	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing the cImageStructure methods random"<<endl;
	
	const unsigned int uiMaxImageSize = sqrt( MAX_ITERATION ) + 16;
	unsigned int uiWidth  = rand() % uiMaxImageSize;
	unsigned int uiHeight = rand() % uiMaxImageSize;
	
	cout<<"pImageSearchData = new cImageSearchData( uiWidth="<<uiWidth<<
		", uiHeight="<<uiHeight<<" );"<<endl;
	cImageSearchData * pImageSearchData =
		new cImageSearchData( uiWidth, uiHeight );
	const cImageSearchData * pImageSearchDataConst = pImageSearchData;
	
	set< pair< unsigned int, unsigned int > > setFoundPoints;
	set< pair< unsigned int, unsigned int > > setOverlappedPoints;
	
	iImageData * pImageData = NULL;
	
	{
		if ( checkSearchStructureValues( pImageSearchData,
				uiWidth, uiHeight, setFoundPoints, setOverlappedPoints ) != 0 ){
			
			iReturn++;
		}
		if ( pImageSearchDataConst->getImageData() != pImageData ){
			cerr<<"Error: The image data is wrong (it is "<<
				pImageSearchDataConst->getImageData()<<
				", but should be "<<pImageData<<")."<<endl;
			iReturn++;
		}
	}
	
	const unsigned long ulIntervallRarlyMethods =
		MAX_ITERATION / log( ((double)(MAX_ITERATION)) ) + 2;
	for ( unsigned long uiActualIteration = 0;
			uiActualIteration < MAX_ITERATION; uiActualIteration++ ){
		cout<<endl;
		//call random change method
		const unsigned int uiChangeType = rand() % ulIntervallRarlyMethods;
		
		if ( uiChangeType == 0 ){
			//call rarely
			const unsigned int uiChangeMethod = rand() % 8;
			
			switch ( uiChangeMethod ){
				case 0:{//test cImageSearchData( const unsigned long ulInWidth, const unsigned long ulInHeight );
					if ( pImageData ){
						delete pImageData;
					}
					pImageData = NULL;
					delete pImageSearchData;
					
					uiWidth  = rand() % uiMaxImageSize;
					uiHeight = rand() % uiMaxImageSize;
					
					cout<<"pImageSearchData = new cImageSearchData( uiWidth="<<uiWidth<<
						", uiHeight="<<uiHeight<<" );"<<endl;
					pImageSearchData = new cImageSearchData( uiWidth, uiHeight );
					pImageSearchDataConst = pImageSearchData;
					
					setFoundPoints.clear();
					setOverlappedPoints.clear();
				}break;
				case 1:{//test cImageSearchData( const iImageData * pInImageData );
					if ( pImageData ){
						delete pImageData;
					}
					delete pImageSearchData;
					
					uiWidth  = rand() % uiMaxImageSize;
					uiHeight = rand() % uiMaxImageSize;
					
					pImageData = new cEvalueSimpleRGBA255( uiWidth - 1, uiHeight - 1 );
					
					cout<<"pImageSearchData = new cImageSearchData( new cEvalueSimpleRGBA255( uiWidth="<<uiWidth<<
						", uiHeight="<<uiHeight<<") );"<<endl;
					pImageSearchData = new cImageSearchData( pImageData );
					pImageSearchDataConst = pImageSearchData;
					
					setFoundPoints.clear();
					setOverlappedPoints.clear();
				}break;
				
				case 2:{//test foundToOverlapped();
					cout<<"pImageSearchData->foundToOverlapped();"<<endl;
					pImageSearchData->foundToOverlapped();
					
					setOverlappedPoints.insert(
						setFoundPoints.begin(), setFoundPoints.end() );
				}break;
				case 3:{//test clearFound();
					cout<<"pImageSearchData->clearFound();"<<endl;
					pImageSearchData->clearFound();
					
					setFoundPoints.clear();
				}break;
				case 4:{//test clearOverlapped();
					cout<<"pImageSearchData->clearOverlapped();"<<endl;
					pImageSearchData->clearOverlapped();
					
					setOverlappedPoints.clear();
				}break;
				
				case 5:{//test cImageSearchData( const cImageSearchData & imageSearchData );
					cout<<"pImageSearchData = new cImageSearchData( *pImageSearchData );"<<endl;
					cImageSearchData * pImageSearchDataNew =
						new cImageSearchData( *pImageSearchData );
					
					delete pImageSearchData;
					pImageSearchData = pImageSearchDataNew;
					pImageSearchDataConst = pImageSearchData;
				}break;
				case 6:{//cImageSearchData * clone() const;
					cout<<"pImageSearchData = pImageSearchData->clone();"<<endl;
					cImageSearchData * pImageSearchDataNew = pImageSearchData->clone();
					
					delete pImageSearchData;
					pImageSearchData = pImageSearchDataNew;
					pImageSearchDataConst = pImageSearchData;
				}break;
				
				case 7:{//cImageSearchData & operator=( const cImageSearchData & imageSearchData );
					cout<<"pImageSearchDataNew = new cImageSearchData( 0, 0 );"<<endl;
					cImageSearchData * pImageSearchDataNew =
						new cImageSearchData( 0, 0 );
					cout<<"(*pImageSearchDataNew) = (*pImageSearchData);"<<endl;
					(*pImageSearchDataNew) = (*pImageSearchData);
					
					delete pImageSearchData;
					pImageSearchData = pImageSearchDataNew;
					pImageSearchDataConst = pImageSearchData;
				}break;
				
			}
		}else{//call often
			
			const unsigned int uiChangeMethod = rand() % 40;
			switch ( uiChangeMethod ){
				case 0:{//bool registerFound( const cVectorPosition & foundPoint );
					const cVectorPosition vecGeneratedPoint =
						generateRandomPoint( uiWidth + 2, uiHeight + 2 );
					cout<<"pImageSearchData->registerFound( vecGeneratedPoint=("<<
						vecGeneratedPoint.getValue( 1 )<<", "<<
						vecGeneratedPoint.getValue( 2 )<<") );"<<endl;
					const bool bPointRegistered =
						pImageSearchData->registerFound( vecGeneratedPoint );
					
					if ( bPointRegistered != checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
						cerr<<"Error: The point was "<<(bPointRegistered?"":"not ")<<
							"registered as found, but should "<<(bPointRegistered?"not ":"")<<"be."<<endl;
						iReturn++;
					}
					if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
						setFoundPoints.insert( toPair( vecGeneratedPoint ) );
					}
				}break;
				case 1:{//bool registerFound( const cVectorPosition & foundPoint, true );
					const cVectorPosition vecGeneratedPoint =
						generateRandomPoint( uiWidth + 2, uiHeight + 2 );
					cout<<"pImageSearchData->registerFound( vecGeneratedPoint=("<<
						vecGeneratedPoint.getValue( 1 )<<", "<<
						vecGeneratedPoint.getValue( 2 )<<"), true );"<<endl;
					const bool bPointRegistered =
						pImageSearchData->registerFound( vecGeneratedPoint, true );
					
					if ( bPointRegistered != checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
						cerr<<"Error: The point was "<<(bPointRegistered?"":"not ")<<
							"registered as found, but should "<<(bPointRegistered?"not ":"")<<"be."<<endl;
						iReturn++;
					}
					if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
						setFoundPoints.insert( toPair( vecGeneratedPoint ) );
					}
				}break;
				case 2:{//bool registerFound( const cVectorPosition & foundPoint, false );
					const cVectorPosition vecGeneratedPoint =
						generateRandomPoint( uiWidth + 2, uiHeight + 2 );
					cout<<"pImageSearchData->registerFound( vecGeneratedPoint=("<<
						vecGeneratedPoint.getValue( 1 )<<", "<<
						vecGeneratedPoint.getValue( 2 )<<"), false );"<<endl;
					const bool bPointRegistered =
						pImageSearchData->registerFound( vecGeneratedPoint, false );
					
					if ( bPointRegistered != checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
						cerr<<"Error: The point was "<<(bPointRegistered?"":"not ")<<
							"registered as found, but should "<<(bPointRegistered?"not ":"")<<"be."<<endl;
						iReturn++;
					}
					setFoundPoints.erase( toPair( vecGeneratedPoint ) );
				}break;
				case 3:{//bool registerFound( const cVectorPosition & foundPoint, false );
					const cVectorPosition vecChoosenPoint = toVector(
						chooseRandomPoint( setFoundPoints ) );
					cout<<"pImageSearchData->registerFound( vecChoosenPoint=("<<
						vecChoosenPoint.getValue( 1 )<<", "<<
						vecChoosenPoint.getValue( 2 )<<"), false );"<<endl;
					const bool bPointRegistered =
						pImageSearchData->registerFound( vecChoosenPoint, false );
					
					if ( bPointRegistered != checkPoint( vecChoosenPoint, uiWidth, uiHeight ) ){
						cerr<<"Error: The point was "<<(bPointRegistered?"":"not ")<<
							"registered as found, but should "<<(bPointRegistered?"not ":"")<<"be."<<endl;
						iReturn++;
					}
					setFoundPoints.erase( toPair( vecChoosenPoint ) );
				}break;
				
				case 4:{//bool registerFound( const pair< unsigned int, unsigned int> & foundPoint, const bool bFound=true );
					const pair< unsigned int, unsigned int> vecGeneratedPointPair =
						generateRandomPointPair( uiWidth + 2, uiHeight + 2 );
					cout<<"pImageSearchData->registerFound( vecGeneratedPointPair=("<<
						vecGeneratedPointPair.first<<", "<<
						vecGeneratedPointPair.second<<") );"<<endl;
					const bool bPointRegistered =
						pImageSearchData->registerFound( vecGeneratedPointPair );
					
					if ( bPointRegistered != checkPoint( vecGeneratedPointPair, uiWidth, uiHeight ) ){
						cerr<<"Error: The point was "<<(bPointRegistered?"":"not ")<<
							"registered as found, but should "<<(bPointRegistered?"not ":"")<<"be."<<endl;
						iReturn++;
					}
					if ( checkPoint( vecGeneratedPointPair, uiWidth, uiHeight ) ){
						setFoundPoints.insert( vecGeneratedPointPair );
					}
				}break;
				case 5:{//bool registerFound( const pair< unsigned int, unsigned int> & foundPoint, const bool bFound=true );
					const pair< unsigned int, unsigned int> vecGeneratedPointPair =
						generateRandomPointPair( uiWidth + 2, uiHeight + 2 );
					cout<<"pImageSearchData->registerFound( vecGeneratedPointPair=("<<
						vecGeneratedPointPair.first<<", "<<
						vecGeneratedPointPair.second<<"), true );"<<endl;
					const bool bPointRegistered =
						pImageSearchData->registerFound( vecGeneratedPointPair, true );
					
					if ( bPointRegistered != checkPoint( vecGeneratedPointPair, uiWidth, uiHeight ) ){
						cerr<<"Error: The point was "<<(bPointRegistered?"":"not ")<<
							"registered as found, but should "<<(bPointRegistered?"not ":"")<<"be."<<endl;
						iReturn++;
					}
					if ( checkPoint( vecGeneratedPointPair, uiWidth, uiHeight ) ){
						setFoundPoints.insert( vecGeneratedPointPair );
					}
				}break;
				case 6:{//bool registerFound( const pair< unsigned int, unsigned int> & foundPoint, const bool bFound=true );
					const pair< unsigned int, unsigned int> vecGeneratedPointPair =
						generateRandomPointPair( uiWidth + 2, uiHeight + 2 );
					cout<<"pImageSearchData->registerFound( vecGeneratedPointPair=("<<
						vecGeneratedPointPair.first<<", "<<
						vecGeneratedPointPair.second<<"), false );"<<endl;
					const bool bPointRegistered =
						pImageSearchData->registerFound( vecGeneratedPointPair, false );
					
					if ( bPointRegistered != checkPoint( vecGeneratedPointPair, uiWidth, uiHeight ) ){
						cerr<<"Error: The point was "<<(bPointRegistered?"":"not ")<<
							"registered as found, but should "<<(bPointRegistered?"not ":"")<<"be."<<endl;
						iReturn++;
					}
					setFoundPoints.erase( vecGeneratedPointPair );
				}break;
				case 7:{//bool registerFound( const pair< unsigned int, unsigned int> & foundPoint, const bool bFound=true );
					const pair< unsigned int, unsigned int> vecChoosenPoint =
						chooseRandomPoint( setFoundPoints );
					cout<<"pImageSearchData->registerFound( vecChoosenPoint=("<<
						vecChoosenPoint.first<<", "<<
						vecChoosenPoint.second<<"), false );"<<endl;
					const bool bPointRegistered =
						pImageSearchData->registerFound( vecChoosenPoint, false );
					
					if ( bPointRegistered != checkPoint( vecChoosenPoint, uiWidth, uiHeight ) ){
						cerr<<"Error: The point was "<<(bPointRegistered?"":"not ")<<
							"registered as found, but should "<<(bPointRegistered?"not ":"")<<"be."<<endl;
						iReturn++;
					}
					setFoundPoints.erase( vecChoosenPoint );
				}break;
				
				case 8:{//bool registerFound( const set<cVectorPosition> & setFoundPoints );
					set< cVectorPosition > setGeneratedPoints;
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					cout<<"pImageSearchData->registerFound( setGeneratedPoints={";
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const cVectorPosition vecGeneratedPoint =
							generateRandomPoint( uiWidth + 2, uiHeight + 2 );
						pair< set< cVectorPosition >::iterator, bool >
							paPointInsert = setGeneratedPoints.insert( vecGeneratedPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
					
						cout<<"("<< vecGeneratedPoint.getValue( 1 )<<", "<<
							vecGeneratedPoint.getValue( 2 )<<"); ";
						if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setFoundPoints.insert( toPair( vecGeneratedPoint ) );
						}
					}
					cout<<"} );"<<endl;
					const unsigned int uiPointRegistered =
						pImageSearchData->registerFound( setGeneratedPoints );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as found, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				case 9:{//bool registerFound( const set<cVectorPosition> & setFoundPoints, true );
					set< cVectorPosition > setGeneratedPoints;
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					cout<<"pImageSearchData->registerFound( setGeneratedPoints={";
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const cVectorPosition vecGeneratedPoint =
							generateRandomPoint( uiWidth + 2, uiHeight + 2 );
						pair< set< cVectorPosition >::iterator, bool >
							paPointInsert = setGeneratedPoints.insert( vecGeneratedPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
					
						cout<<"("<< vecGeneratedPoint.getValue( 1 )<<", "<<
							vecGeneratedPoint.getValue( 2 )<<"); ";
						if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setFoundPoints.insert( toPair( vecGeneratedPoint ) );
						}
					}
					cout<<"}, true );"<<endl;
					const unsigned int uiPointRegistered =
						pImageSearchData->registerFound( setGeneratedPoints, true );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as found, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				case 10:{//bool registerFound( const set<cVectorPosition> & setFoundPoints, false );
					set< cVectorPosition > setGeneratedPoints;
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					cout<<"pImageSearchData->registerFound( setGeneratedPoints={";
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const cVectorPosition vecGeneratedPoint =
							generateRandomPoint( uiWidth + 2, uiHeight + 2 );
						
						pair< set< cVectorPosition >::iterator, bool >
							paPointInsert = setGeneratedPoints.insert( vecGeneratedPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
						cout<<"("<< vecGeneratedPoint.getValue( 1 )<<", "<<
							vecGeneratedPoint.getValue( 2 )<<"); ";
						if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setFoundPoints.erase( toPair( vecGeneratedPoint ) );
						}
					}
					cout<<"}, false );"<<endl;
					const unsigned int uiPointRegistered =
						pImageSearchData->registerFound( setGeneratedPoints, false );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as not found, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				case 11:{//bool registerFound( const set<cVectorPosition> & setFoundPoints, false );
					set< cVectorPosition > setChoosenPoints;
					cout<<"pImageSearchData->registerFound( setChoosenPoints={";
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const cVectorPosition vecChoosenPoint =
							toVector( chooseRandomPoint( setFoundPoints ) );
						pair< set< cVectorPosition >::iterator, bool >
							paPointInsert = setChoosenPoints.insert( vecChoosenPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
					
						cout<<"("<< vecChoosenPoint.getValue( 1 )<<", "<<
							vecChoosenPoint.getValue( 2 )<<"); ";
						
						if ( checkPoint( vecChoosenPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setFoundPoints.erase( toPair( vecChoosenPoint ) );
						}
					}
					cout<<"}, false );"<<endl;
					const unsigned int uiPointRegistered =
						pImageSearchData->registerFound( setChoosenPoints, false );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as not found, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				
				
				case 12:{//bool registerFound( const cImageStructure * pImageStrFoundPoints );
					set< cVectorPosition > setGeneratedPoints;
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					cout<<"pImageSearchData->registerFound( &imageStrFoundPoints={";
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const cVectorPosition vecGeneratedPoint =
							generateRandomPoint( uiWidth + 2, uiHeight + 2 );
						pair< set< cVectorPosition >::iterator, bool >
							paPointInsert = setGeneratedPoints.insert( vecGeneratedPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
					
						cout<<"("<< vecGeneratedPoint.getValue( 1 )<<", "<<
							vecGeneratedPoint.getValue( 2 )<<"); ";
						if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setFoundPoints.insert( toPair( vecGeneratedPoint ) );
						}
					}
					cout<<"} );"<<endl;
					cImageStructure imageStrFoundPoints;
					imageStrFoundPoints.setStructurePoints( setGeneratedPoints );
					set< cVectorPosition > setStructureBorderPoints =
						generateRandomPoints( uiWidth + uiHeight + 1, uiWidth + 2, uiHeight + 2 );
					imageStrFoundPoints.setStructureBorderPoints( setStructureBorderPoints );
					set< cVectorPosition > setStructureNeighbourPoints =
						generateRandomPoints( uiWidth + uiHeight + 1, uiWidth + 2, uiHeight + 2 );
					imageStrFoundPoints.setStructureBorderPoints( setStructureNeighbourPoints );
					
					const unsigned int uiPointRegistered =
						pImageSearchData->registerFound( &imageStrFoundPoints );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as found, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				case 13:{//bool registerFound( const cImageStructure * pImageStrFoundPoints, true );
					set< cVectorPosition > setGeneratedPoints;
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					cout<<"pImageSearchData->registerFound( &imageStrFoundPoints={";
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const cVectorPosition vecGeneratedPoint =
							generateRandomPoint( uiWidth + 2, uiHeight + 2 );
						pair< set< cVectorPosition >::iterator, bool >
							paPointInsert = setGeneratedPoints.insert( vecGeneratedPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
					
						cout<<"("<< vecGeneratedPoint.getValue( 1 )<<", "<<
							vecGeneratedPoint.getValue( 2 )<<"); ";
						if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setFoundPoints.insert( toPair( vecGeneratedPoint ) );
						}
					}
					cout<<"}, true );"<<endl;
					cImageStructure imageStrFoundPoints;
					imageStrFoundPoints.setStructurePoints( setGeneratedPoints );
					set< cVectorPosition > setStructureBorderPoints =
						generateRandomPoints( uiWidth + uiHeight + 1, uiWidth + 2, uiHeight + 2 );
					imageStrFoundPoints.setStructureBorderPoints( setStructureBorderPoints );
					set< cVectorPosition > setStructureNeighbourPoints =
						generateRandomPoints( uiWidth + uiHeight + 1, uiWidth + 2, uiHeight + 2 );
					imageStrFoundPoints.setStructureBorderPoints( setStructureNeighbourPoints );
					
					const unsigned int uiPointRegistered =
						pImageSearchData->registerFound( &imageStrFoundPoints, true );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as found, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				case 14:{//bool registerFound( const cImageStructure * pImageStrFoundPoints, false );
					set< cVectorPosition > setGeneratedPoints;
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					cout<<"pImageSearchData->registerFound( &imageStrFoundPoints={";
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const cVectorPosition vecGeneratedPoint =
							generateRandomPoint( uiWidth + 2, uiHeight + 2 );
						
						pair< set< cVectorPosition >::iterator, bool >
							paPointInsert = setGeneratedPoints.insert( vecGeneratedPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
						cout<<"("<< vecGeneratedPoint.getValue( 1 )<<", "<<
							vecGeneratedPoint.getValue( 2 )<<"); ";
						if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setFoundPoints.erase( toPair( vecGeneratedPoint ) );
						}
					}
					cout<<"}, false );"<<endl;
					cImageStructure imageStrFoundPoints;
					imageStrFoundPoints.setStructurePoints( setGeneratedPoints );
					set< cVectorPosition > setStructureBorderPoints =
						generateRandomPoints( uiWidth + uiHeight + 1, uiWidth + 2, uiHeight + 2 );
					imageStrFoundPoints.setStructureBorderPoints( setStructureBorderPoints );
					set< cVectorPosition > setStructureNeighbourPoints =
						generateRandomPoints( uiWidth + uiHeight + 1, uiWidth + 2, uiHeight + 2 );
					imageStrFoundPoints.setStructureBorderPoints( setStructureNeighbourPoints );
					
					const unsigned int uiPointRegistered =
						pImageSearchData->registerFound( &imageStrFoundPoints, false );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as not found, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				case 15:{//bool registerFound( const cImageStructure * pImageStrFoundPoints, false );
					set< cVectorPosition > setChoosenPoints;
					cout<<"pImageSearchData->registerFound( &imageStrFoundPoints={";
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const cVectorPosition vecChoosenPoint =
							toVector( chooseRandomPoint( setFoundPoints ) );
						pair< set< cVectorPosition >::iterator, bool >
							paPointInsert = setChoosenPoints.insert( vecChoosenPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
					
						cout<<"("<< vecChoosenPoint.getValue( 1 )<<", "<<
							vecChoosenPoint.getValue( 2 )<<"); ";
						
						if ( checkPoint( vecChoosenPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setFoundPoints.erase( toPair( vecChoosenPoint ) );
						}
					}
					cout<<"}, false );"<<endl;
					cImageStructure imageStrFoundPoints;
					imageStrFoundPoints.setStructurePoints( setChoosenPoints );
					set< cVectorPosition > setStructureBorderPoints =
						generateRandomPoints( uiWidth + uiHeight + 1, uiWidth + 2, uiHeight + 2 );
					imageStrFoundPoints.setStructureBorderPoints( setStructureBorderPoints );
					set< cVectorPosition > setStructureNeighbourPoints =
						generateRandomPoints( uiWidth + uiHeight + 1, uiWidth + 2, uiHeight + 2 );
					imageStrFoundPoints.setStructureBorderPoints( setStructureNeighbourPoints );
					
					const unsigned int uiPointRegistered =
						pImageSearchData->registerFound( &imageStrFoundPoints, false );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as not found, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				
				
				case 16:{//bool registerFound( const set< pair< unsigned int, unsigned int> > & setFoundPoints );
					set< pair< unsigned int, unsigned int> > setGeneratedPoints;
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					cout<<"pImageSearchData->registerFound( setGeneratedPointsPair={";
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const pair< unsigned int, unsigned int> vecGeneratedPoint =
							generateRandomPointPair( uiWidth + 2, uiHeight + 2 );
						pair< set< pair< unsigned int, unsigned int> >::iterator, bool >
							paPointInsert = setGeneratedPoints.insert( vecGeneratedPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
					
						cout<<"("<< vecGeneratedPoint.first<<", "<<
							vecGeneratedPoint.second<<"); ";
						if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setFoundPoints.insert( vecGeneratedPoint );
						}
					}
					cout<<"} );"<<endl;
					const unsigned int uiPointRegistered =
						pImageSearchData->registerFound( setGeneratedPoints );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as found, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				case 17:{//bool registerFound( const set< pair< unsigned int, unsigned int> > & setFoundPoints, true );
					set< pair< unsigned int, unsigned int> > setGeneratedPoints;
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					cout<<"pImageSearchData->registerFound( setGeneratedPointsPair={";
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const pair< unsigned int, unsigned int> vecGeneratedPoint =
							generateRandomPointPair( uiWidth + 2, uiHeight + 2 );
						pair< set< pair< unsigned int, unsigned int> >::iterator, bool >
							paPointInsert = setGeneratedPoints.insert( vecGeneratedPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
					
						cout<<"("<< vecGeneratedPoint.first<<", "<<
							vecGeneratedPoint.second<<"); ";
						if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setFoundPoints.insert( vecGeneratedPoint );
						}
					}
					cout<<"}, true );"<<endl;
					const unsigned int uiPointRegistered =
						pImageSearchData->registerFound( setGeneratedPoints, true );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as found, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				case 18:{//bool registerFound( const set< pair< unsigned int, unsigned int> > & setFoundPoints, false );
					set< pair< unsigned int, unsigned int> > setGeneratedPoints;
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					cout<<"pImageSearchData->registerFound( setGeneratedPointsPair={";
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const pair< unsigned int, unsigned int> vecGeneratedPoint =
							generateRandomPointPair( uiWidth + 2, uiHeight + 2 );
						
						pair< set< pair< unsigned int, unsigned int> >::iterator, bool >
							paPointInsert = setGeneratedPoints.insert( vecGeneratedPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
						cout<<"("<< vecGeneratedPoint.first<<", "<<
							vecGeneratedPoint.second<<"); ";
						if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setFoundPoints.erase( vecGeneratedPoint );
						}
					}
					cout<<"}, false );"<<endl;
					const unsigned int uiPointRegistered =
						pImageSearchData->registerFound( setGeneratedPoints, false );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as not found, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				case 19:{//bool registerFound( const set< pair< unsigned int, unsigned int> > & setFoundPoints, false );
					set< pair< unsigned int, unsigned int> > setChoosenPoints;
					cout<<"pImageSearchData->registerFound( setChoosenPointsPair={";
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const pair< unsigned int, unsigned int> vecChoosenPoint =
							chooseRandomPoint( setFoundPoints );
						pair< set< pair< unsigned int, unsigned int> >::iterator, bool >
							paPointInsert = setChoosenPoints.insert( vecChoosenPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
					
						cout<<"("<< vecChoosenPoint.first<<", "<<
							vecChoosenPoint.second<<"); ";
						
						if ( checkPoint( vecChoosenPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setFoundPoints.erase( vecChoosenPoint );
						}
					}
					cout<<"}, false );"<<endl;
					const unsigned int uiPointRegistered =
						pImageSearchData->registerFound( setChoosenPoints, false );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as not found, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				
				
				
				
				case 20:{//bool registerOverlapped( const cVectorPosition & overlappedPoint );
					const cVectorPosition vecGeneratedPoint =
						generateRandomPoint( uiWidth + 2, uiHeight + 2 );
					cout<<"pImageSearchData->registerOverlapped( vecGeneratedPoint=("<<
						vecGeneratedPoint.getValue( 1 )<<", "<<
						vecGeneratedPoint.getValue( 2 )<<") );"<<endl;
					const bool bPointRegistered =
						pImageSearchData->registerOverlapped( vecGeneratedPoint );
					
					if ( bPointRegistered != checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
						cerr<<"Error: The point was "<<(bPointRegistered?"":"not ")<<
							"registered as overlapped, but should "<<(bPointRegistered?"not ":"")<<"be."<<endl;
						iReturn++;
					}
					if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
						setOverlappedPoints.insert( toPair( vecGeneratedPoint ) );
					}
				}break;
				case 21:{//bool registerOverlapped( const cVectorPosition & overlappedPoint, true );
					const cVectorPosition vecGeneratedPoint =
						generateRandomPoint( uiWidth + 2, uiHeight + 2 );
					cout<<"pImageSearchData->registerOverlapped( vecGeneratedPoint=("<<
						vecGeneratedPoint.getValue( 1 )<<", "<<
						vecGeneratedPoint.getValue( 2 )<<"), true );"<<endl;
					const bool bPointRegistered =
						pImageSearchData->registerOverlapped( vecGeneratedPoint, true );
					
					if ( bPointRegistered != checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
						cerr<<"Error: The point was "<<(bPointRegistered?"":"not ")<<
							"registered as overlapped, but should "<<(bPointRegistered?"not ":"")<<"be."<<endl;
						iReturn++;
					}
					if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
						setOverlappedPoints.insert( toPair( vecGeneratedPoint ) );
					}
				}break;
				case 22:{//bool registerOverlapped( const cVectorPosition & overlappedPoint, false );
					const cVectorPosition vecGeneratedPoint =
						generateRandomPoint( uiWidth + 2, uiHeight + 2 );
					cout<<"pImageSearchData->registerOverlapped( vecGeneratedPoint=("<<
						vecGeneratedPoint.getValue( 1 )<<", "<<
						vecGeneratedPoint.getValue( 2 )<<"), false );"<<endl;
					const bool bPointRegistered =
						pImageSearchData->registerOverlapped( vecGeneratedPoint, false );
					
					if ( bPointRegistered != checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
						cerr<<"Error: The point was "<<(bPointRegistered?"":"not ")<<
							"registered as overlapped, but should "<<(bPointRegistered?"not ":"")<<"be."<<endl;
						iReturn++;
					}
					setOverlappedPoints.erase( toPair( vecGeneratedPoint ) );
				}break;
				case 23:{//bool registerOverlapped( const cVectorPosition & overlappedPoint, false );
					const cVectorPosition vecChoosenPoint = toVector(
						chooseRandomPoint( setOverlappedPoints ) );
					cout<<"pImageSearchData->registerOverlapped( vecChoosenPoint=("<<
						vecChoosenPoint.getValue( 1 )<<", "<<
						vecChoosenPoint.getValue( 2 )<<"), false );"<<endl;
					const bool bPointRegistered =
						pImageSearchData->registerOverlapped( vecChoosenPoint, false );
					
					if ( bPointRegistered != checkPoint( vecChoosenPoint, uiWidth, uiHeight ) ){
						cerr<<"Error: The point was "<<(bPointRegistered?"":"not ")<<
							"registered as overlapped, but should "<<(bPointRegistered?"not ":"")<<"be."<<endl;
						iReturn++;
					}
					setOverlappedPoints.erase( toPair( vecChoosenPoint ) );
				}break;
				
				case 24:{//bool registerOverlapped( const pair< unsigned int, unsigned int> & overlappedPoint, const bool bOverlapped=true );
					const pair< unsigned int, unsigned int> vecGeneratedPointPair =
						generateRandomPointPair( uiWidth + 2, uiHeight + 2 );
					cout<<"pImageSearchData->registerOverlapped( vecGeneratedPointPair=("<<
						vecGeneratedPointPair.first<<", "<<
						vecGeneratedPointPair.second<<") );"<<endl;
					const bool bPointRegistered =
						pImageSearchData->registerOverlapped( vecGeneratedPointPair );
					
					if ( bPointRegistered != checkPoint( vecGeneratedPointPair, uiWidth, uiHeight ) ){
						cerr<<"Error: The point was "<<(bPointRegistered?"":"not ")<<
							"registered as overlapped, but should "<<(bPointRegistered?"not ":"")<<"be."<<endl;
						iReturn++;
					}
					if ( checkPoint( vecGeneratedPointPair, uiWidth, uiHeight ) ){
						setOverlappedPoints.insert( vecGeneratedPointPair );
					}
				}break;
				case 25:{//bool registerOverlapped( const pair< unsigned int, unsigned int> & overlappedPoint, const bool bOverlapped=true );
					const pair< unsigned int, unsigned int> vecGeneratedPointPair =
						generateRandomPointPair( uiWidth + 2, uiHeight + 2 );
					cout<<"pImageSearchData->registerOverlapped( vecGeneratedPointPair=("<<
						vecGeneratedPointPair.first<<", "<<
						vecGeneratedPointPair.second<<"), true );"<<endl;
					const bool bPointRegistered =
						pImageSearchData->registerOverlapped( vecGeneratedPointPair, true );
					
					if ( bPointRegistered != checkPoint( vecGeneratedPointPair, uiWidth, uiHeight ) ){
						cerr<<"Error: The point was "<<(bPointRegistered?"":"not ")<<
							"registered as overlapped, but should "<<(bPointRegistered?"not ":"")<<"be."<<endl;
						iReturn++;
					}
					if ( checkPoint( vecGeneratedPointPair, uiWidth, uiHeight ) ){
						setOverlappedPoints.insert( vecGeneratedPointPair );
					}
				}break;
				case 26:{//bool registerOverlapped( const pair< unsigned int, unsigned int> & overlappedPoint, const bool bOverlapped=true );
					const pair< unsigned int, unsigned int> vecGeneratedPointPair =
						generateRandomPointPair( uiWidth + 2, uiHeight + 2 );
					cout<<"pImageSearchData->registerOverlapped( vecGeneratedPointPair=("<<
						vecGeneratedPointPair.first<<", "<<
						vecGeneratedPointPair.second<<"), false );"<<endl;
					const bool bPointRegistered =
						pImageSearchData->registerOverlapped( vecGeneratedPointPair, false );
					
					if ( bPointRegistered != checkPoint( vecGeneratedPointPair, uiWidth, uiHeight ) ){
						cerr<<"Error: The point was "<<(bPointRegistered?"":"not ")<<
							"registered as overlapped, but should "<<(bPointRegistered?"not ":"")<<"be."<<endl;
						iReturn++;
					}
					setOverlappedPoints.erase( vecGeneratedPointPair );
				}break;
				case 27:{//bool registerOverlapped( const pair< unsigned int, unsigned int> & overlappedPoint, const bool bOverlapped=true );
					const pair< unsigned int, unsigned int> vecChoosenPoint =
						chooseRandomPoint( setOverlappedPoints );
					cout<<"pImageSearchData->registerOverlapped( vecChoosenPoint=("<<
						vecChoosenPoint.first<<", "<<
						vecChoosenPoint.second<<"), false );"<<endl;
					const bool bPointRegistered =
						pImageSearchData->registerOverlapped( vecChoosenPoint, false );
					
					if ( bPointRegistered != checkPoint( vecChoosenPoint, uiWidth, uiHeight ) ){
						cerr<<"Error: The point was "<<(bPointRegistered?"":"not ")<<
							"registered as overlapped, but should "<<(bPointRegistered?"not ":"")<<"be."<<endl;
						iReturn++;
					}
					setOverlappedPoints.erase( vecChoosenPoint );
				}break;
				
				case 28:{//bool registerOverlapped( const set<cVectorPosition> & setOverlappedPoints );
					set< cVectorPosition > setGeneratedPoints;
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					cout<<"pImageSearchData->registerOverlapped( setGeneratedPoints={";
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const cVectorPosition vecGeneratedPoint =
							generateRandomPoint( uiWidth + 2, uiHeight + 2 );
						pair< set< cVectorPosition >::iterator, bool >
							paPointInsert = setGeneratedPoints.insert( vecGeneratedPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
					
						cout<<"("<< vecGeneratedPoint.getValue( 1 )<<", "<<
							vecGeneratedPoint.getValue( 2 )<<"); ";
						if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setOverlappedPoints.insert( toPair( vecGeneratedPoint ) );
						}
					}
					cout<<"} );"<<endl;
					const unsigned int uiPointRegistered =
						pImageSearchData->registerOverlapped( setGeneratedPoints );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as overlapped, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				case 29:{//bool registerOverlapped( const set<cVectorPosition> & setOverlappedPoints, true );
					set< cVectorPosition > setGeneratedPoints;
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					cout<<"pImageSearchData->registerOverlapped( setGeneratedPoints={";
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const cVectorPosition vecGeneratedPoint =
							generateRandomPoint( uiWidth + 2, uiHeight + 2 );
						pair< set< cVectorPosition >::iterator, bool >
							paPointInsert = setGeneratedPoints.insert( vecGeneratedPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
					
						cout<<"("<< vecGeneratedPoint.getValue( 1 )<<", "<<
							vecGeneratedPoint.getValue( 2 )<<"); ";
						if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setOverlappedPoints.insert( toPair( vecGeneratedPoint ) );
						}
					}
					cout<<"}, true );"<<endl;
					const unsigned int uiPointRegistered =
						pImageSearchData->registerOverlapped( setGeneratedPoints, true );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as overlapped, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				case 30:{//bool registerOverlapped( const set<cVectorPosition> & setOverlappedPoints, false );
					set< cVectorPosition > setGeneratedPoints;
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					cout<<"pImageSearchData->registerOverlapped( setGeneratedPoints={";
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const cVectorPosition vecGeneratedPoint =
							generateRandomPoint( uiWidth + 2, uiHeight + 2 );
						
						pair< set< cVectorPosition >::iterator, bool >
							paPointInsert = setGeneratedPoints.insert( vecGeneratedPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
						cout<<"("<< vecGeneratedPoint.getValue( 1 )<<", "<<
							vecGeneratedPoint.getValue( 2 )<<"); ";
						if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setOverlappedPoints.erase( toPair( vecGeneratedPoint ) );
						}
					}
					cout<<"}, false );"<<endl;
					const unsigned int uiPointRegistered =
						pImageSearchData->registerOverlapped( setGeneratedPoints, false );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as not overlapped, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				case 31:{//bool registerOverlapped( const set<cVectorPosition> & setOverlappedPoints, false );
					set< cVectorPosition > setChoosenPoints;
					cout<<"pImageSearchData->registerOverlapped( setChoosenPoints={";
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const cVectorPosition vecChoosenPoint =
							toVector( chooseRandomPoint( setOverlappedPoints ) );
						pair< set< cVectorPosition >::iterator, bool >
							paPointInsert = setChoosenPoints.insert( vecChoosenPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
					
						cout<<"("<< vecChoosenPoint.getValue( 1 )<<", "<<
							vecChoosenPoint.getValue( 2 )<<"); ";
						
						if ( checkPoint( vecChoosenPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setOverlappedPoints.erase( toPair( vecChoosenPoint ) );
						}
					}
					cout<<"}, false );"<<endl;
					const unsigned int uiPointRegistered =
						pImageSearchData->registerOverlapped( setChoosenPoints, false );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as not overlapped, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				
				
				case 32:{//bool registerOverlapped( const cImageStructure * pImageStrOverlappedPoints );
					set< cVectorPosition > setGeneratedPoints;
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					cout<<"pImageSearchData->registerOverlapped( &imageStrOverlappedPoints={";
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const cVectorPosition vecGeneratedPoint =
							generateRandomPoint( uiWidth + 2, uiHeight + 2 );
						pair< set< cVectorPosition >::iterator, bool >
							paPointInsert = setGeneratedPoints.insert( vecGeneratedPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
					
						cout<<"("<< vecGeneratedPoint.getValue( 1 )<<", "<<
							vecGeneratedPoint.getValue( 2 )<<"); ";
						if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setOverlappedPoints.insert( toPair( vecGeneratedPoint ) );
						}
					}
					cout<<"} );"<<endl;
					cImageStructure imageStrOverlappedPoints;
					imageStrOverlappedPoints.setStructurePoints( setGeneratedPoints );
					set< cVectorPosition > setStructureBorderPoints =
						generateRandomPoints( uiWidth + uiHeight + 1, uiWidth + 2, uiHeight + 2 );
					imageStrOverlappedPoints.setStructureBorderPoints( setStructureBorderPoints );
					set< cVectorPosition > setStructureNeighbourPoints =
						generateRandomPoints( uiWidth + uiHeight + 1, uiWidth + 2, uiHeight + 2 );
					imageStrOverlappedPoints.setStructureBorderPoints( setStructureNeighbourPoints );
					
					const unsigned int uiPointRegistered =
						pImageSearchData->registerOverlapped( &imageStrOverlappedPoints );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as overlapped, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				case 33:{//bool registerOverlapped( const cImageStructure * pImageStrOverlappedPoints, true );
					set< cVectorPosition > setGeneratedPoints;
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					cout<<"pImageSearchData->registerOverlapped( &imageStrOverlappedPoints={";
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const cVectorPosition vecGeneratedPoint =
							generateRandomPoint( uiWidth + 2, uiHeight + 2 );
						pair< set< cVectorPosition >::iterator, bool >
							paPointInsert = setGeneratedPoints.insert( vecGeneratedPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
					
						cout<<"("<< vecGeneratedPoint.getValue( 1 )<<", "<<
							vecGeneratedPoint.getValue( 2 )<<"); ";
						if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setOverlappedPoints.insert( toPair( vecGeneratedPoint ) );
						}
					}
					cout<<"}, true );"<<endl;
					cImageStructure imageStrOverlappedPoints;
					imageStrOverlappedPoints.setStructurePoints( setGeneratedPoints );
					set< cVectorPosition > setStructureBorderPoints =
						generateRandomPoints( uiWidth + uiHeight + 1, uiWidth + 2, uiHeight + 2 );
					imageStrOverlappedPoints.setStructureBorderPoints( setStructureBorderPoints );
					set< cVectorPosition > setStructureNeighbourPoints =
						generateRandomPoints( uiWidth + uiHeight + 1, uiWidth + 2, uiHeight + 2 );
					imageStrOverlappedPoints.setStructureBorderPoints( setStructureNeighbourPoints );
					
					const unsigned int uiPointRegistered =
						pImageSearchData->registerOverlapped( &imageStrOverlappedPoints, true );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as overlapped, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				case 34:{//bool registerOverlapped( const cImageStructure * pImageStrOverlappedPoints, false );
					set< cVectorPosition > setGeneratedPoints;
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					cout<<"pImageSearchData->registerOverlapped( &imageStrOverlappedPoints={";
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const cVectorPosition vecGeneratedPoint =
							generateRandomPoint( uiWidth + 2, uiHeight + 2 );
						
						pair< set< cVectorPosition >::iterator, bool >
							paPointInsert = setGeneratedPoints.insert( vecGeneratedPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
						cout<<"("<< vecGeneratedPoint.getValue( 1 )<<", "<<
							vecGeneratedPoint.getValue( 2 )<<"); ";
						if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setOverlappedPoints.erase( toPair( vecGeneratedPoint ) );
						}
					}
					cout<<"}, false );"<<endl;
					cImageStructure imageStrOverlappedPoints;
					imageStrOverlappedPoints.setStructurePoints( setGeneratedPoints );
					set< cVectorPosition > setStructureBorderPoints =
						generateRandomPoints( uiWidth + uiHeight + 1, uiWidth + 2, uiHeight + 2 );
					imageStrOverlappedPoints.setStructureBorderPoints( setStructureBorderPoints );
					set< cVectorPosition > setStructureNeighbourPoints =
						generateRandomPoints( uiWidth + uiHeight + 1, uiWidth + 2, uiHeight + 2 );
					imageStrOverlappedPoints.setStructureBorderPoints( setStructureNeighbourPoints );
					
					const unsigned int uiPointRegistered =
						pImageSearchData->registerOverlapped( &imageStrOverlappedPoints, false );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as not overlapped, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				case 35:{//bool registerOverlapped( const cImageStructure * pImageStrOverlappedPoints, false );
					set< cVectorPosition > setChoosenPoints;
					cout<<"pImageSearchData->registerOverlapped( &imageStrOverlappedPoints={";
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const cVectorPosition vecChoosenPoint =
							toVector( chooseRandomPoint( setOverlappedPoints ) );
						pair< set< cVectorPosition >::iterator, bool >
							paPointInsert = setChoosenPoints.insert( vecChoosenPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
					
						cout<<"("<< vecChoosenPoint.getValue( 1 )<<", "<<
							vecChoosenPoint.getValue( 2 )<<"); ";
						
						if ( checkPoint( vecChoosenPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setOverlappedPoints.erase( toPair( vecChoosenPoint ) );
						}
					}
					cout<<"}, false );"<<endl;
					cImageStructure imageStrOverlappedPoints;
					imageStrOverlappedPoints.setStructurePoints( setChoosenPoints );
					set< cVectorPosition > setStructureBorderPoints =
						generateRandomPoints( uiWidth + uiHeight + 1, uiWidth + 2, uiHeight + 2 );
					imageStrOverlappedPoints.setStructureBorderPoints( setStructureBorderPoints );
					set< cVectorPosition > setStructureNeighbourPoints =
						generateRandomPoints( uiWidth + uiHeight + 1, uiWidth + 2, uiHeight + 2 );
					imageStrOverlappedPoints.setStructureBorderPoints( setStructureNeighbourPoints );
					
					const unsigned int uiPointRegistered =
						pImageSearchData->registerOverlapped( &imageStrOverlappedPoints, false );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as not overlapped, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				
				
				case 36:{//bool registerOverlapped( const set< pair< unsigned int, unsigned int> > & setOverlappedPoints );
					set< pair< unsigned int, unsigned int> > setGeneratedPoints;
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					cout<<"pImageSearchData->registerOverlapped( setGeneratedPointsPair={";
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const pair< unsigned int, unsigned int> vecGeneratedPoint =
							generateRandomPointPair( uiWidth + 2, uiHeight + 2 );
						pair< set< pair< unsigned int, unsigned int> >::iterator, bool >
							paPointInsert = setGeneratedPoints.insert( vecGeneratedPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
					
						cout<<"("<< vecGeneratedPoint.first<<", "<<
							vecGeneratedPoint.second<<"); ";
						if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setOverlappedPoints.insert( vecGeneratedPoint );
						}
					}
					cout<<"} );"<<endl;
					const unsigned int uiPointRegistered =
						pImageSearchData->registerOverlapped( setGeneratedPoints );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as overlapped, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				case 37:{//bool registerOverlapped( const set< pair< unsigned int, unsigned int> > & setOverlappedPoints, true );
					set< pair< unsigned int, unsigned int> > setGeneratedPoints;
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					cout<<"pImageSearchData->registerOverlapped( setGeneratedPointsPair={";
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const pair< unsigned int, unsigned int> vecGeneratedPoint =
							generateRandomPointPair( uiWidth + 2, uiHeight + 2 );
						pair< set< pair< unsigned int, unsigned int> >::iterator, bool >
							paPointInsert = setGeneratedPoints.insert( vecGeneratedPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
					
						cout<<"("<< vecGeneratedPoint.first<<", "<<
							vecGeneratedPoint.second<<"); ";
						if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setOverlappedPoints.insert( vecGeneratedPoint );
						}
					}
					cout<<"}, true );"<<endl;
					const unsigned int uiPointRegistered =
						pImageSearchData->registerOverlapped( setGeneratedPoints, true );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as overlapped, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				case 38:{//bool registerOverlapped( const set< pair< unsigned int, unsigned int> > & setOverlappedPoints, false );
					set< pair< unsigned int, unsigned int> > setGeneratedPoints;
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					cout<<"pImageSearchData->registerOverlapped( setGeneratedPointsPair={";
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const pair< unsigned int, unsigned int> vecGeneratedPoint =
							generateRandomPointPair( uiWidth + 2, uiHeight + 2 );
						
						pair< set< pair< unsigned int, unsigned int> >::iterator, bool >
							paPointInsert = setGeneratedPoints.insert( vecGeneratedPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
						cout<<"("<< vecGeneratedPoint.first<<", "<<
							vecGeneratedPoint.second<<"); ";
						if ( checkPoint( vecGeneratedPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setOverlappedPoints.erase( vecGeneratedPoint );
						}
					}
					cout<<"}, false );"<<endl;
					const unsigned int uiPointRegistered =
						pImageSearchData->registerOverlapped( setGeneratedPoints, false );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as not overlapped, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				case 39:{//bool registerOverlapped( const set< pair< unsigned int, unsigned int> > & setOverlappedPoints, false );
					set< pair< unsigned int, unsigned int> > setChoosenPoints;
					cout<<"pImageSearchData->registerOverlapped( setChoosenPointsPair={";
					unsigned int uiNumberOfPointsToGenerate = rand() %
						( uiWidth + uiHeight + 1 );
					unsigned int uiValidPoints = 0;
					for ( unsigned long uiIteration = 0;
							uiIteration < uiNumberOfPointsToGenerate; uiIteration++ ){
						
						const pair< unsigned int, unsigned int> vecChoosenPoint =
							chooseRandomPoint( setOverlappedPoints );
						pair< set< pair< unsigned int, unsigned int> >::iterator, bool >
							paPointInsert = setChoosenPoints.insert( vecChoosenPoint );
						if ( ! paPointInsert.second ){
							continue;
						}
					
						cout<<"("<< vecChoosenPoint.first<<", "<<
							vecChoosenPoint.second<<"); ";
						
						if ( checkPoint( vecChoosenPoint, uiWidth, uiHeight ) ){
							uiValidPoints++;
							setOverlappedPoints.erase( vecChoosenPoint );
						}
					}
					cout<<"}, false );"<<endl;
					const unsigned int uiPointRegistered =
						pImageSearchData->registerOverlapped( setChoosenPoints, false );
					
					if ( uiPointRegistered != uiValidPoints ){
						cerr<<"Error: There where "<<uiPointRegistered<<" points "<<
							"registered as not overlapped, but it should be "<<uiValidPoints<<" ."<<endl;
						iReturn++;
					}
				}break;
				
				
			}
		}
		
		
		//test the members of the class
		if ( checkSearchStructureValues( pImageSearchData,
				uiWidth, uiHeight, setFoundPoints, setOverlappedPoints ) != 0 ){
			
			iReturn++;
		}
		if ( pImageSearchDataConst->getImageData() != pImageData ){
			cerr<<"Error: The image data is wrong (it is "<<
				pImageSearchDataConst->getImageData()<<
				", but should be "<<pImageData<<")."<<endl;
			iReturn++;
		}
		
	}//end iterate random test
	delete pImageSearchData;
	if ( pImageData ){
		delete pImageData;
	}
	
	return iReturn;
}















