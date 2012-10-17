/**
 * @file tHyperplaneBody
 * file name: tHyperplaneBody.cpp
 * @author Betti Oesterholz
 * @date 20.01.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class tHyperplaneBody.
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
 * This file contains the test for the class tHyperplaneBody, which
 * represents a body defined by inequiations and the border hyperplanes
 * they create.
 *
 *
 * What's tested of class cHyperplane:
 * 	- cHyperplaneBody( unsigned int uiInDimensions, const tFactors maxValue );
 * 	- bool addInequiation( const cInequation< tFactors > & inequiation );
 * 	- unsigned long addInequiations( const vector< cInequation< tFactors > > & vecInequiations );
 * 	- vector< vector< tFactors > > getBorderPoints() const;
 * 	- bool isPart( const vector< tFactors > & vecPoint ) const;
 * 	- vector< tFactors > getPointInBody( const unsigned int uiMinBitsToStoreMantissa ) const;
 * 	- void print( ostream & outputStream ) const;
 *
 *
 * call: tHyperplaneBody [ITERATIONS]
 *
 * parameters:
 * 	ITERATIONS
 * 		The iterations for the test with random generated hyperplanes.
 * 		Standardvalue is 256.
 *
 */
/*
History:
20.01.2011  Oesterholz  created
05.04.2011  Oesterholz  test for addin 0 inequiations added
10.04.2011  Oesterholz  cHyperplaneBody split into cHyperplaneBodySimple
	and cHyperplaneBodyFull
*/

//TODO weg
//#define DEBUG


#include "version.h"

#include "cHyperplaneBodySimple.h"
#include "cHyperplaneBodyFull.h"
#include "cInequation.h"

#include "../test/tCompareBits.inc"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <ctime>
#include <cmath>
#include <string>
#include <set>


using namespace std;

using namespace fib::algorithms::nDn;
using namespace fib::algorithms::nLinearInequation;


template<class tHyperplaneBody>
	int testCostructor( unsigned long &ulTestphase,
		double dStandardMaxValue );
template<class tHyperplaneBody>
	int testAddInequiation( unsigned long &ulTestphase );



unsigned long MAX_ITERATION = 256;


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );

	if ( argc >= 2 ){
		//one parameter given; read parameter iterations
		MAX_ITERATION = atol( argv[1] );
		if ( MAX_ITERATION < 1 ){
			MAX_ITERATION = 1;
		}
	}

	cout<<endl<<"Running Test for cHyperplaneBodySimple methods"<<endl;
	cout<<      "=============================================="<<endl;
	const time_t timeStartSimple = time (NULL);
	
	iReturn += testCostructor< cHyperplaneBodySimple< double > >( ulTestphase, 256 * 256 * 256 );
	iReturn += testAddInequiation< cHyperplaneBodySimple< double > >( ulTestphase );
	
	cout<<endl<<"Running Test for cHyperplaneBodyFull methods"<<endl;
	cout<<      "============================================"<<endl;
	
	const time_t timeStartFull = time (NULL);
	iReturn += testCostructor< cHyperplaneBodyFull< double > >( ulTestphase, 1E+36 );
	iReturn += testAddInequiation< cHyperplaneBodyFull< double > >( ulTestphase );
	
	const time_t timeEndFull = time (NULL);
	
	cout<<"Second needed to test cHyperplaneBodySimple: "<<
		( timeStartFull - timeStartSimple )<<endl;
	cout<<"Second needed to test cHyperplaneBodyFull  : "<<
		( timeEndFull - timeStartFull )<<endl;

	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}


/**
 * This function prints the given vector to the given output stream.
 *
 * @param outputStream the output stream to print the vector to
 * @param vector the vector to print
 */
template< class tElements > void printVector( ostream & outputStream,
		const vector< tElements > & vector ){
	
	outputStream<<"( ";
	for ( unsigned int uiDimension = 0; uiDimension < vector.size();
			uiDimension++ ){
		
		outputStream<< vector[ uiDimension ] <<", ";
	}
	outputStream<<")^T"<<endl;
}


/**
 * This function prints the given vector to the given output stream.
 *
 * @param outputStream the output stream to print the vector to
 * @param vector the vector to print
 */
template< class tElements > void printVecVector( ostream & outputStream,
		const vector< vector< tElements > > & vecVector ){
	
	for ( unsigned int uiVector = 0; uiVector < vecVector.size();
			uiVector++ ){
		
		outputStream<<"vector "<<uiVector<<" : ";
		printVector( outputStream, vecVector[ uiVector ] );
	}
}


/**
 * This functions compares two vectors of vectors with double numbers.
 * Realy small differences betwean the vector element numbers will be ignored.
 *
 * @param vecVector1 the first vector of vectors to compare
 * @param vecVector2 the second vector of vectors to compare
 * @return true if the first vector of vectors is equal to the second, else false
 */
template<class tDouble>
bool compareVectorVectorDouble( const vector< vector< tDouble > > & vecVector1,
		const vector< vector< tDouble > > & vecVector2 ){
	
	if ( vecVector1.size() != vecVector2.size() ){
		//not the same number of elements -> vectors not equal
		return false;
	}
	size_t uiNumberOfElements = vecVector1.size();
	
	for ( size_t uiActualElement = 0; uiActualElement < uiNumberOfElements;
			uiActualElement++ ){
		
		if ( ! compareVectorDouble( vecVector1[ uiActualElement ], vecVector2[ uiActualElement ] ) ){
			//actual vector element not equal -> vectors not equal
			return false;
		}
	}//else all vector elements equal
	return true;
}


/**
 * This function checks if the given vectors of points is in the given body.
 *
 * @param body the body, which should be contain the points
 * @param vecPoints a vector with the to check points
 * @return the number of errors occured in the test
 */
template<class tDouble>
unsigned int checkIfPointsAreInBody( const cHyperplaneBody< tDouble > & body,
		vector< vector< tDouble > >  vecPoints ){
	
	unsigned long uiPointsNotPart = 0;
	
	for ( vector< vector< double > >::iterator
			itrCorrectPoint = vecPoints.begin();
			itrCorrectPoint != vecPoints.end(); itrCorrectPoint++ ){
		
		if ( ! body.isPart( *itrCorrectPoint ) ){
			uiPointsNotPart++;
			if ( uiPointsNotPart < 5 ){
				cerr<<"Error: The point is not part of the body:";
				printVector( cerr, *itrCorrectPoint );
			}
		}
	}
	if ( 0 < uiPointsNotPart ){
		if ( 4 < uiPointsNotPart ){
			cerr<<"Error: Ther wher "<<uiPointsNotPart<<" points not part of the body. (yust the first 4 are printed)";
		}
		return 1;
	}//else
	return 0;
}

/**
 * This function checks if the given vectors of points is not in the given body.
 *
 * @param body the body, which should be not contain the points
 * @param vecPoints a vector with the to check points
 * @return the number of errors occured in the test
 */
template<class tDouble>
unsigned int checkIfPointsAreNotInBody( const cHyperplaneBody< tDouble > & body,
		vector< vector< tDouble > > vecPoints ){
	
	unsigned long uiPointsPart = 0;
	
	for ( vector< vector< double > >::iterator
			itrCorrectPoint = vecPoints.begin();
			itrCorrectPoint != vecPoints.end(); itrCorrectPoint++ ){
		
		if ( body.isPart( *itrCorrectPoint ) ){
			uiPointsPart++;
			if ( uiPointsPart < 5 ){
				cerr<<"Error: The point is part of the body:";
				printVector( cerr, *itrCorrectPoint );
			}
		}
	}
	if ( 0 < uiPointsPart ){
		if ( 4 < uiPointsPart ){
			cerr<<"Error: Ther wher "<<uiPointsPart<<" points part of the body. (yust the first 4 are printed)";
		}
		return 1;
	}//else
	return 0;
}


/**
 * This function checks if the given vectors of border points are equal.
 *
 * @param vecVecCorrectBorderpoints a vector with the correct border points
 * @param vecVecCorrectBorderpoints a vector with the to check border points
 * @return the number of errors occured in the test
 */
template<class tDouble>
unsigned int checkBorderPoints( vector< vector< tDouble > > vecVecCorrectBorderpoints,
		vector< vector< tDouble > > vecVecBorderPoints){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( vecVecCorrectBorderpoints.size() != vecVecBorderPoints.size() ){
		
		cerr<<"Error: Ther should be "<<vecVecCorrectBorderpoints.size()<<
			" border points, but ther are "<<vecVecBorderPoints.size()<<" ."<<endl;
		iReturn++;
	}
	
	for ( vector< vector< double > >::iterator
			itrCorrectBorderPoint = vecVecCorrectBorderpoints.begin();
			itrCorrectBorderPoint != vecVecCorrectBorderpoints.end(); ){
		
		bool bPointFound = false;
		for ( vector< vector< double > >::iterator
				itrBorderPoint = vecVecBorderPoints.begin();
				itrBorderPoint != vecVecBorderPoints.end(); ){
			
			if ( compareVectorDouble( (*itrCorrectBorderPoint), (*itrBorderPoint) ) ){
				//correct border point found
				itrCorrectBorderPoint = vecVecCorrectBorderpoints.erase(
					itrCorrectBorderPoint );
				itrBorderPoint = vecVecBorderPoints.erase(
					itrBorderPoint );
				bPointFound = true;
				break;
			}else{
				itrBorderPoint++;
			}
		}
		if ( ! bPointFound ){
			//check next correct border point
			itrCorrectBorderPoint++;
		}
	}
	
	if ( vecVecCorrectBorderpoints.empty() && vecVecBorderPoints.empty() ){
	
		cout<<"The hyperplane has the correct border points. "<<endl;
	}else{
		cerr<<"Error: The hyperplane has the wrong border points."<<endl;
		cerr<<"Not found border points in corrects border points:"<<endl;
		printVecVector( cerr, vecVecBorderPoints );
		cerr<<endl<<"Not found correct border points in border points:"<<endl;
		printVecVector( cerr, vecVecCorrectBorderpoints );
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This function generates random points inside a body of a hypercubus,
 * with all points wich elements absolut value are lower equal the given
 * maximum. ( p=(x_1,...,x_d), |x_i| <= maxValue )
 *
 * @param uiDimensions the number of dimensions for the hypercubus
 * @param maxValue the maximum value for the absolut point element values
 * 	of the hypercubus
 * @param uiNumberOfPointsToGenerate the number of random points to generate
 * @return a vector with uiNumberOfPoints random points in the hypercubus
 */
template<class tDouble>
vector< vector< tDouble > > generateRandCubusPoints(
		const unsigned int uiDimensions, const tDouble maxValue,
		const unsigned long uiNumberOfPointsToGenerate = 1024 ){
	
	if ( uiDimensions == 0 ){
		//non dimensional hypercubus dosn't have points
		return vector< vector< tDouble > >();
	}
	if ( maxValue == ((tDouble)(0)) ){
		//hypercubus dosn't have points
		return vector< vector< tDouble > >();
	}
	
	vector< vector< tDouble > > vecPointsGenerated;
	while ( vecPointsGenerated.size() < uiNumberOfPointsToGenerate ){
		
		vector< tDouble > vecNewPoint( uiDimensions, ((tDouble)(0)) );
		
		for ( unsigned int uiActualDimension = 0;
				uiActualDimension < uiDimensions; uiActualDimension++ ){
			
			vecNewPoint[ uiActualDimension ] =
				((tDouble)rand()) * maxValue / ((tDouble)RAND_MAX);
		}
		
		vecPointsGenerated.push_back( vecNewPoint );
	}
	
	return vecPointsGenerated;
}


/**
 * This functions retuns all points of the given list, wich fullfill the
 * given inequiation.
 *
 * @param inequiation the inequiation, which the points should fullfill
 * @param vecPoints a vector with the to check points
 * @return all points of the given list, wich fullfill the given inequiation
 */
template<class tDouble>
vector< vector< tDouble > > evalueValidPoints(
		const cInequation< tDouble > & inequiation,
		vector< vector< tDouble > >  vecPoints ){
	
	vector< vector< tDouble > > vecPointsWichFulfill;
	
	for ( vector< vector< double > >::iterator
			itrCorrectPoint = vecPoints.begin();
			itrCorrectPoint != vecPoints.end(); itrCorrectPoint++ ){
		
		if ( inequiation.evalue( *itrCorrectPoint ) ){
			
			vecPointsWichFulfill.push_back( *itrCorrectPoint );
		}
	}
	
	return vecPointsWichFulfill;
}


/**
 * This functions retuns all points of the given list, wich fullfill the
 * given inequiation.
 *
 * @param inequiation the inequiation, which the points should fullfill
 * @param vecPoints a vector with the to check points
 * @param vecOutPointsNotValid the vector for the points, which dosn't fulfill the inequiation
 * @return all points of the given list, wich fullfill the given inequiation
 */
template<class tDouble>
vector< vector< tDouble > > evalueValidPoints(
		const cInequation< tDouble > & inequiation,
		vector< vector< tDouble > >  vecPoints,
		vector< vector< tDouble > > & vecOutPointsNotValid ){
	
	vector< vector< tDouble > > vecPointsWichFulfill;
	
	for ( vector< vector< double > >::iterator
			itrCorrectPoint = vecPoints.begin();
			itrCorrectPoint != vecPoints.end(); itrCorrectPoint++ ){
		
		if ( inequiation.evalue( *itrCorrectPoint ) ){
			
			vecPointsWichFulfill.push_back( *itrCorrectPoint );
		}else{
			
			vecOutPointsNotValid.push_back( *itrCorrectPoint );
		}
	}
	
	return vecPointsWichFulfill;
}


/**
 * This function tests the constructor of the cHyperplane class.
 *
 * methods tested:
 * 	- tHyperplaneBody( unsigned int uiInDimensions, const tFactors maxValue );
 * 	- bool isPart( const vector< tFactors > & vecPoint ) const;
 * 	- void print( ostream & outputStream ) const;
 * 	- vector< vector< tFactors > > getBorderPoints() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param dStandardMaxValue the standard maximal value for constructed cHyperplaneBody
 * @return the number of errors occured in the test
 */
template<class tHyperplaneBody >
int testCostructor( unsigned long &ulTestphase,
		double dStandardMaxValue ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"Testing the constructors, please check the printed hyperplanes"<<endl;
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a simple hyperplane body in one dimension"<<endl;

	cout<<"tHyperplaneBody hyperplaneBodyEmpty( 1 );"<<endl;
	tHyperplaneBody hyperplaneBodyEmpty( 1 );
	
	cout<<"vecVecBorderPoints = hyperplaneBodyEmpty.getBorderPoints();"<<endl;
	vector< vector< double > > vecVecBorderPoints =
		hyperplaneBodyEmpty.getBorderPoints();
	
	vector< vector< double > > vecVecCorrectBorderpoints( 2,
		vector< double >( 1 ) );
	
	vecVecCorrectBorderpoints[ 0 ][ 0 ] = dStandardMaxValue;
	vecVecCorrectBorderpoints[ 1 ][ 0 ] = -1.0 * dStandardMaxValue;
	
	iReturn += checkBorderPoints( vecVecCorrectBorderpoints, vecVecBorderPoints);
	iReturn += checkIfPointsAreInBody( hyperplaneBodyEmpty, vecVecCorrectBorderpoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyEmpty,
		generateRandCubusPoints( 1, vecVecCorrectBorderpoints[ 0 ][ 0 ] ) );
	

	cout<<"hyperplaneBodyEmpty.print( cout );"<<endl;
	hyperplaneBodyEmpty.print( cout );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a simple hyperplane body in one dimension and changed maximal bounderies"<<endl;

	cout<<"tHyperplaneBody hyperplaneBodyD1Max20( 1, 20 );"<<endl;
	tHyperplaneBody hyperplaneBodyD1Max20( 1, 20 );
	
	cout<<"vecVecBorderPoints = hyperplaneBodyD1Max20.getBorderPoints();"<<endl;
	vecVecBorderPoints = hyperplaneBodyD1Max20.getBorderPoints();
	
	vecVecCorrectBorderpoints[ 0 ][ 0 ] = 20;
	vecVecCorrectBorderpoints[ 1 ][ 0 ] = -20;
	
	iReturn += checkBorderPoints( vecVecCorrectBorderpoints, vecVecBorderPoints);
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD1Max20, vecVecCorrectBorderpoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD1Max20,
		generateRandCubusPoints( 1, vecVecCorrectBorderpoints[ 0 ][ 0 ] ) );
	
	cout<<"hyperplaneBodyD1Max20.print( cout ):"<<endl;
	hyperplaneBodyD1Max20.print( cout );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a simple hyperplane body in two dimension"<<endl;

	cout<<"tHyperplaneBody hyperplaneBodyD2Max10( 2, 10 );"<<endl;
	tHyperplaneBody hyperplaneBodyD2Max10( 2, 10 );
	
	cout<<"vecVecBorderPoints = hyperplaneBodyD2Max10.getBorderPoints();"<<endl;
	vecVecBorderPoints = hyperplaneBodyD2Max10.getBorderPoints();
	
	vecVecCorrectBorderpoints = vector< vector< double > >( 4, vector< double >( 2 ) );
	vecVecCorrectBorderpoints[ 0 ][ 0 ] = 10;
	vecVecCorrectBorderpoints[ 0 ][ 1 ] = 10;
	vecVecCorrectBorderpoints[ 1 ][ 0 ] = -10;
	vecVecCorrectBorderpoints[ 1 ][ 1 ] = -10;
	vecVecCorrectBorderpoints[ 2 ][ 0 ] = 10;
	vecVecCorrectBorderpoints[ 2 ][ 1 ] = -10;
	vecVecCorrectBorderpoints[ 3 ][ 0 ] = -10;
	vecVecCorrectBorderpoints[ 3 ][ 1 ] = 10;
	
	iReturn += checkBorderPoints( vecVecCorrectBorderpoints, vecVecBorderPoints);
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD2Max10, vecVecCorrectBorderpoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD2Max10,
		generateRandCubusPoints( 2, vecVecCorrectBorderpoints[ 0 ][ 0 ] ) );
	
	cout<<"hyperplaneBodyD2Max10.print( cout ):"<<endl;
	hyperplaneBodyD2Max10.print( cout );
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a simple hyperplane body in tree dimension"<<endl;

	cout<<"tHyperplaneBody hyperplaneBodyD3Max256( 3, 256 );"<<endl;
	tHyperplaneBody hyperplaneBodyD3Max256( 3, 256 );
	
	cout<<"vecVecBorderPoints = hyperplaneBodyD3Max256.getBorderPoints();"<<endl;
	vecVecBorderPoints = hyperplaneBodyD3Max256.getBorderPoints();
	
	vecVecCorrectBorderpoints = vector< vector< double > >( 8, vector< double >( 3 ) );
	vecVecCorrectBorderpoints[ 0 ][ 0 ] = 256;
	vecVecCorrectBorderpoints[ 0 ][ 1 ] = 256;
	vecVecCorrectBorderpoints[ 0 ][ 2 ] = 256;
	
	vecVecCorrectBorderpoints[ 1 ][ 0 ] = 256;
	vecVecCorrectBorderpoints[ 1 ][ 1 ] = -256;
	vecVecCorrectBorderpoints[ 1 ][ 2 ] = 256;
	
	vecVecCorrectBorderpoints[ 2 ][ 0 ] = 256;
	vecVecCorrectBorderpoints[ 2 ][ 1 ] = 256;
	vecVecCorrectBorderpoints[ 2 ][ 2 ] = -256;
	
	vecVecCorrectBorderpoints[ 3 ][ 0 ] = 256;
	vecVecCorrectBorderpoints[ 3 ][ 1 ] = -256;
	vecVecCorrectBorderpoints[ 3 ][ 2 ] = -256;
	
	vecVecCorrectBorderpoints[ 4 ][ 0 ] = -256;
	vecVecCorrectBorderpoints[ 4 ][ 1 ] = 256;
	vecVecCorrectBorderpoints[ 4 ][ 2 ] = 256;
	
	vecVecCorrectBorderpoints[ 5 ][ 0 ] = -256;
	vecVecCorrectBorderpoints[ 5 ][ 1 ] = -256;
	vecVecCorrectBorderpoints[ 5 ][ 2 ] = 256;
	
	vecVecCorrectBorderpoints[ 6 ][ 0 ] = -256;
	vecVecCorrectBorderpoints[ 6 ][ 1 ] = 256;
	vecVecCorrectBorderpoints[ 6 ][ 2 ] = -256;
	
	vecVecCorrectBorderpoints[ 7 ][ 0 ] = -256;
	vecVecCorrectBorderpoints[ 7 ][ 1 ] = -256;
	vecVecCorrectBorderpoints[ 7 ][ 2 ] = -256;
	
	iReturn += checkBorderPoints( vecVecCorrectBorderpoints, vecVecBorderPoints);
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD3Max256, vecVecCorrectBorderpoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD3Max256,
		generateRandCubusPoints( 3, vecVecCorrectBorderpoints[ 0 ][ 0 ] ) );
	
	cout<<"hyperplaneBodyD3Max256.print( cout ):"<<endl;
	hyperplaneBodyD3Max256.print( cout );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a simple hyperplane body in four dimension"<<endl;

	cout<<"tHyperplaneBody hyperplaneBodyD4Max0p25( 4, 256 );"<<endl;
	tHyperplaneBody hyperplaneBodyD4Max0p25( 4, 0.25 );
	
	cout<<"vecVecBorderPoints = hyperplaneBodyD4Max0p25.getBorderPoints();"<<endl;
	vecVecBorderPoints = hyperplaneBodyD4Max0p25.getBorderPoints();
	
	vecVecCorrectBorderpoints = vector< vector< double > >( 16, vector< double >( 4 ) );
	vecVecCorrectBorderpoints[ 0 ][ 0 ] = 0.25;
	vecVecCorrectBorderpoints[ 0 ][ 1 ] = 0.25;
	vecVecCorrectBorderpoints[ 0 ][ 2 ] = 0.25;
	vecVecCorrectBorderpoints[ 0 ][ 3 ] = 0.25;
	
	vecVecCorrectBorderpoints[ 1 ][ 0 ] = 0.25;
	vecVecCorrectBorderpoints[ 1 ][ 1 ] = -0.25;
	vecVecCorrectBorderpoints[ 1 ][ 2 ] = 0.25;
	vecVecCorrectBorderpoints[ 1 ][ 3 ] = 0.25;
	
	vecVecCorrectBorderpoints[ 2 ][ 0 ] = 0.25;
	vecVecCorrectBorderpoints[ 2 ][ 1 ] = 0.25;
	vecVecCorrectBorderpoints[ 2 ][ 2 ] = -0.25;
	vecVecCorrectBorderpoints[ 2 ][ 3 ] = 0.25;
	
	vecVecCorrectBorderpoints[ 3 ][ 0 ] = 0.25;
	vecVecCorrectBorderpoints[ 3 ][ 1 ] = -0.25;
	vecVecCorrectBorderpoints[ 3 ][ 2 ] = -0.25;
	vecVecCorrectBorderpoints[ 3 ][ 3 ] = 0.25;
	
	vecVecCorrectBorderpoints[ 4 ][ 0 ] = -0.25;
	vecVecCorrectBorderpoints[ 4 ][ 1 ] = 0.25;
	vecVecCorrectBorderpoints[ 4 ][ 2 ] = 0.25;
	vecVecCorrectBorderpoints[ 4 ][ 3 ] = 0.25;
	
	vecVecCorrectBorderpoints[ 5 ][ 0 ] = -0.25;
	vecVecCorrectBorderpoints[ 5 ][ 1 ] = -0.25;
	vecVecCorrectBorderpoints[ 5 ][ 2 ] = 0.25;
	vecVecCorrectBorderpoints[ 5 ][ 3 ] = 0.25;
	
	vecVecCorrectBorderpoints[ 6 ][ 0 ] = -0.25;
	vecVecCorrectBorderpoints[ 6 ][ 1 ] = 0.25;
	vecVecCorrectBorderpoints[ 6 ][ 2 ] = -0.25;
	vecVecCorrectBorderpoints[ 6 ][ 3 ] = 0.25;
	
	vecVecCorrectBorderpoints[ 7 ][ 0 ] = -0.25;
	vecVecCorrectBorderpoints[ 7 ][ 1 ] = -0.25;
	vecVecCorrectBorderpoints[ 7 ][ 2 ] = -0.25;
	vecVecCorrectBorderpoints[ 7 ][ 3 ] = 0.25;
	
	vecVecCorrectBorderpoints[ 8 ][ 0 ] = 0.25;
	vecVecCorrectBorderpoints[ 8 ][ 1 ] = 0.25;
	vecVecCorrectBorderpoints[ 8 ][ 2 ] = 0.25;
	vecVecCorrectBorderpoints[ 8 ][ 3 ] = -0.25;
	
	vecVecCorrectBorderpoints[ 9 ][ 0 ] = 0.25;
	vecVecCorrectBorderpoints[ 9 ][ 1 ] = -0.25;
	vecVecCorrectBorderpoints[ 9 ][ 2 ] = 0.25;
	vecVecCorrectBorderpoints[ 9 ][ 3 ] = -0.25;
	
	vecVecCorrectBorderpoints[ 10 ][ 0 ] = 0.25;
	vecVecCorrectBorderpoints[ 10 ][ 1 ] = 0.25;
	vecVecCorrectBorderpoints[ 10 ][ 2 ] = -0.25;
	vecVecCorrectBorderpoints[ 10 ][ 3 ] = -0.25;
	
	vecVecCorrectBorderpoints[ 11 ][ 0 ] = 0.25;
	vecVecCorrectBorderpoints[ 11 ][ 1 ] = -0.25;
	vecVecCorrectBorderpoints[ 11 ][ 2 ] = -0.25;
	vecVecCorrectBorderpoints[ 11 ][ 3 ] = -0.25;
	
	vecVecCorrectBorderpoints[ 12 ][ 0 ] = -0.25;
	vecVecCorrectBorderpoints[ 12 ][ 1 ] = 0.25;
	vecVecCorrectBorderpoints[ 12 ][ 2 ] = 0.25;
	vecVecCorrectBorderpoints[ 12 ][ 3 ] = -0.25;
	
	vecVecCorrectBorderpoints[ 13 ][ 0 ] = -0.25;
	vecVecCorrectBorderpoints[ 13 ][ 1 ] = -0.25;
	vecVecCorrectBorderpoints[ 13 ][ 2 ] = 0.25;
	vecVecCorrectBorderpoints[ 13 ][ 3 ] = -0.25;
	
	vecVecCorrectBorderpoints[ 14 ][ 0 ] = -0.25;
	vecVecCorrectBorderpoints[ 14 ][ 1 ] = 0.25;
	vecVecCorrectBorderpoints[ 14 ][ 2 ] = -0.25;
	vecVecCorrectBorderpoints[ 14 ][ 3 ] = -0.25;
	
	vecVecCorrectBorderpoints[ 15 ][ 0 ] = -0.25;
	vecVecCorrectBorderpoints[ 15 ][ 1 ] = -0.25;
	vecVecCorrectBorderpoints[ 15 ][ 2 ] = -0.25;
	vecVecCorrectBorderpoints[ 15 ][ 3 ] = -0.25;

	iReturn += checkBorderPoints( vecVecCorrectBorderpoints, vecVecBorderPoints);
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD4Max0p25, vecVecCorrectBorderpoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD4Max0p25,
		generateRandCubusPoints( 4, vecVecCorrectBorderpoints[ 0 ][ 0 ] ) );
	
	cout<<"hyperplaneBodyD4Max0p25.print( cout ):"<<endl;
	hyperplaneBodyD4Max0p25.print( cout );

	return iReturn;
}



/**
 * This function tests the addInequiation() methods of the cHyperplane class.
 *
 * methods tested:
 * 	- tHyperplaneBody( unsigned int uiInDimensions, const tFactors maxValue = 1E+36 );
 * 	- bool addInequiation( const cInequation< tFactors > & inequiation );
 * 	- unsigned long addInequiations( const vector< cInequation< tFactors > > & vecInequiations );
 * 	- vector< vector< tFactors > > getBorderPoints() const;
 * 	- bool isPart( const vector< tFactors > & vecPoint ) const;
 * 	- vector< tFactors > getPointInBody( const unsigned int uiMinBitsToStoreMantissa ) const;
 * 	- void print( ostream & outputStream ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
template<class tHyperplaneBody>
int testAddInequiation( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing methods for adding inequiations; please check the printed bodys manually"<<endl;
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing addInequiation()"<<endl;
	
	cout<<"tHyperplaneBody hyperplaneBodyD2Max255( 2, 255 );"<<endl;
	tHyperplaneBody hyperplaneBodyD2Max255( 2, 255 );
	
	cout<<"vecVecBorderPoints = hyperplaneBodyD2Max255.getBorderPoints();"<<endl;
	vector< vector< double > > vecVecBorderPoints =
		hyperplaneBodyD2Max255.getBorderPoints();
	
	vector< vector< double > > vecVecCorrectBorderpoints =
		vector< vector< double > >( 4, vector< double >( 2 ) );
	vecVecCorrectBorderpoints[ 0 ][ 0 ] = 255;
	vecVecCorrectBorderpoints[ 0 ][ 1 ] = 255;
	vecVecCorrectBorderpoints[ 1 ][ 0 ] = -255;
	vecVecCorrectBorderpoints[ 1 ][ 1 ] = -255;
	vecVecCorrectBorderpoints[ 2 ][ 0 ] = 255;
	vecVecCorrectBorderpoints[ 2 ][ 1 ] = -255;
	vecVecCorrectBorderpoints[ 3 ][ 0 ] = -255;
	vecVecCorrectBorderpoints[ 3 ][ 1 ] = 255;
	
	vector< vector< double > > randomPointsInBody =
		generateRandCubusPoints( 2, vecVecCorrectBorderpoints[ 0 ][ 0 ] );
	
	//check points in the body
	iReturn += checkBorderPoints( vecVecCorrectBorderpoints, vecVecBorderPoints);
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD2Max255, vecVecCorrectBorderpoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD2Max255, randomPointsInBody );
	
	cout<<"hyperplaneBodyD2Max255.print( cout );"<<endl;
	hyperplaneBodyD2Max255.print( cout );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing adding restricting inequiation"<<endl;
	
	//insert an inequiation
	cout<<"cInequation< double > inequiation: -200 <= x_0"<<endl;
	cInequation< double > inequiation;
	inequiation.constant = -200;
	
	inequiation.vecFactors = vector< double >( 2, 0.0 );
	inequiation.vecFactors[ 0 ] = 1;
	
	vecVecCorrectBorderpoints[ 1 ][ 0 ] = -200;
	vecVecCorrectBorderpoints[ 3 ][ 0 ] = -200;
	
	randomPointsInBody = evalueValidPoints( inequiation, randomPointsInBody );
	
	cout<<"hyperplaneBodyD2Max255.addInequiation( inequiation );"<<endl;
	bool bInequiationAdded = hyperplaneBodyD2Max255.addInequiation( inequiation );
	
	if ( bInequiationAdded ){
		cout<<"The inequiation was correctly successfully added."<<endl;
	}else{
		cerr<<"Error: The inequiation not successfully added."<<endl;
		iReturn++;
	}
	vecVecBorderPoints = hyperplaneBodyD2Max255.getBorderPoints();
	//check points in the body
	iReturn += checkBorderPoints( vecVecCorrectBorderpoints, vecVecBorderPoints);
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD2Max255, vecVecCorrectBorderpoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD2Max255, randomPointsInBody );
	
	cout<<"hyperplaneBodyD2Max255.print( cout );"<<endl;
	hyperplaneBodyD2Max255.print( cout );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing try to add inequiation which would remove the body"<<endl;
	//insert an inequiation
	cout<<"inequiation: 300 <= x_0"<<endl;
	inequiation.constant = 300;
	inequiation.vecFactors[ 0 ] = 1;
	
	cout<<"hyperplaneBodyD2Max255.addInequiation( inequiation );"<<endl;
	bInequiationAdded = hyperplaneBodyD2Max255.addInequiation( inequiation );
	
	if ( ! bInequiationAdded ){
		cout<<"The inequiation was correctly not added."<<endl;
	}else{
		cerr<<"Error: The inequiation successfully added."<<endl;
		iReturn++;
	}
	//check points in the body
	vecVecBorderPoints = hyperplaneBodyD2Max255.getBorderPoints();
	iReturn += checkBorderPoints( vecVecCorrectBorderpoints, vecVecBorderPoints);
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD2Max255, vecVecCorrectBorderpoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD2Max255, randomPointsInBody );

	cout<<"hyperplaneBodyD2Max255.print( cout );"<<endl;
	hyperplaneBodyD2Max255.print( cout );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing adding non restricting inequiation"<<endl;
	
	//insert an inequiation
	cout<<"inequiation: -200 <= x_0"<<endl;
	inequiation.constant = -200;
	inequiation.vecFactors[ 0 ] = 1;
	
	cout<<"hyperplaneBodyD2Max255.addInequiation( inequiation );"<<endl;
	bInequiationAdded = hyperplaneBodyD2Max255.addInequiation( inequiation );
	
	if ( bInequiationAdded ){
		cout<<"The inequiation was correctly successfully added."<<endl;
	}else{
		cerr<<"Error: The inequiation not successfully added."<<endl;
		iReturn++;
	}
	//check points in the body
	vecVecBorderPoints = hyperplaneBodyD2Max255.getBorderPoints();
	iReturn += checkBorderPoints( vecVecCorrectBorderpoints, vecVecBorderPoints);
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD2Max255, vecVecCorrectBorderpoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD2Max255, randomPointsInBody );
	
	cout<<"hyperplaneBodyD2Max255.print( cout );"<<endl;
	hyperplaneBodyD2Max255.print( cout );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing adding diagonal inequiation"<<endl;
	
	//insert an inequiation
	cout<<"inequiation: -100 <= x_0 + 2 * x_1 "<<endl;
	inequiation.constant = -100;
	
	inequiation.vecFactors = vector< double >( 2, 0.0 );
	inequiation.vecFactors[ 0 ] = 1;
	inequiation.vecFactors[ 1 ] = 2;

	vecVecCorrectBorderpoints[ 0 ][ 0 ] = 255;
	vecVecCorrectBorderpoints[ 0 ][ 1 ] = 255;
	vecVecCorrectBorderpoints[ 1 ][ 0 ] = -200;
	vecVecCorrectBorderpoints[ 1 ][ 1 ] = 50;
	vecVecCorrectBorderpoints[ 2 ][ 0 ] = 255;
	vecVecCorrectBorderpoints[ 2 ][ 1 ] = -177.5;
	vecVecCorrectBorderpoints[ 3 ][ 0 ] = -200;
	vecVecCorrectBorderpoints[ 3 ][ 1 ] = 255;

	
	randomPointsInBody = evalueValidPoints( inequiation, randomPointsInBody );
	
	cout<<"hyperplaneBodyD2Max255.addInequiation( inequiation );"<<endl;
	bInequiationAdded = hyperplaneBodyD2Max255.addInequiation( inequiation );
	
	if ( bInequiationAdded ){
		cout<<"The inequiation was correctly successfully added."<<endl;
	}else{
		cerr<<"Error: The inequiation not successfully added."<<endl;
		iReturn++;
	}
	vecVecBorderPoints = hyperplaneBodyD2Max255.getBorderPoints();
	//check points in the body
	iReturn += checkBorderPoints( vecVecCorrectBorderpoints, vecVecBorderPoints);
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD2Max255, vecVecCorrectBorderpoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD2Max255, randomPointsInBody );
	
	cout<<"hyperplaneBodyD2Max255.print( cout );"<<endl;
	hyperplaneBodyD2Max255.print( cout );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing adding two inequiation to create a triangle"<<endl;
	
/*
A inequiation: -100 <= x_0 + 2 * x_1 
B inequiation: -100 <= -2 * x_0 + -1 * x_1 
	-> 2 * x_0 + x_1 <= 100
C inequiation: -110 <= -5.5 * x_1
	-> x_1 <= 20

A * 2 + B : -300 <= 3 * x_1
		-> x_1 = -100
		-> x_0 = 100
*/
	
	//insert an inequiation
	cout<<"inequiation: -100 <= -2 * x_0 + -1 * x_1 "<<endl;
	inequiation.constant = -100;
	
	inequiation.vecFactors = vector< double >( 2, 0.0 );
	inequiation.vecFactors[ 0 ] = -2;
	inequiation.vecFactors[ 1 ] = -1;
	vector< cInequation< double > > vecInequiations;
	cout<<"vecInequiations.push_back( inequiation )"<<endl;
	vecInequiations.push_back( inequiation );
	randomPointsInBody = evalueValidPoints( inequiation, randomPointsInBody );
	
	
	cout<<"inequiation: -110 <= -5.5 * x_1 -> x_1 <= 20"<<endl;
	inequiation.constant = -110;
	inequiation.vecFactors = vector< double >( 2, 0.0 );
	inequiation.vecFactors[ 0 ] = 0;
	inequiation.vecFactors[ 1 ] = -5.5;
	cout<<"vecInequiations.push_back( inequiation )"<<endl;
	vecInequiations.push_back( inequiation );
	randomPointsInBody = evalueValidPoints( inequiation, randomPointsInBody );
	
	vecVecCorrectBorderpoints.resize( 3 );
	vecVecCorrectBorderpoints[ 0 ][ 0 ] = 100;
	vecVecCorrectBorderpoints[ 0 ][ 1 ] = -100;
	vecVecCorrectBorderpoints[ 1 ][ 0 ] = -140;
	vecVecCorrectBorderpoints[ 1 ][ 1 ] = 20;
	vecVecCorrectBorderpoints[ 2 ][ 0 ] = 40;
	vecVecCorrectBorderpoints[ 2 ][ 1 ] = 20;
	
	cout<<"hyperplaneBodyD2Max255.addInequiations( vecInequiations );"<<endl;
	unsigned int uiInequiationsAdded =
		hyperplaneBodyD2Max255.addInequiations( vecInequiations );
	
	if ( uiInequiationsAdded == 2 ){
		cout<<"The "<<uiInequiationsAdded<<" inequiations wher correctly successfully added."<<endl;
	}else{
		cerr<<"Error: The two inequiations wher not successfully added, but it wher "<<
			uiInequiationsAdded<<" added."<<endl;
		iReturn++;
	}
	vecVecBorderPoints = hyperplaneBodyD2Max255.getBorderPoints();
	//check points in the body
	iReturn += checkBorderPoints( vecVecCorrectBorderpoints, vecVecBorderPoints);
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD2Max255, vecVecCorrectBorderpoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD2Max255, randomPointsInBody );
	
	cout<<"hyperplaneBodyD2Max255.print( cout );"<<endl;
	hyperplaneBodyD2Max255.print( cout );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing adding inequiation with just one factor"<<endl;
/*
A inequiation: -100 <= x_0 + 2 * x_1 
B inequiation: -100 <= -2 * x_0 + -1 * x_1 
	-> 2 * x_0 + x_1 <= 100
C inequiation: -110 <= -5.5 * x_1
	-> x_1 <= 20
D inequiation: -150 <= -3 * x_0 -> x_0 <= 50

A * 2 + B : -300 <= 3 * x_1
		-> x_1 = -100
		-> x_0 = 100
*/
	//insert an inequiation
	cout<<"inequiation: -150 <= -3 * x_0 -> x_0 <= 50"<<endl;
	inequiation.constant = -150;
	
	inequiation.vecFactors = vector< double >( 1, 0.0 );
	inequiation.vecFactors[ 0 ] = -3;
	
	randomPointsInBody = evalueValidPoints( inequiation, randomPointsInBody );
	
	vecVecCorrectBorderpoints.push_back( vector< double >( 2, 0.0 ) );
	vecVecCorrectBorderpoints[ 0 ][ 0 ] = 50;
	vecVecCorrectBorderpoints[ 0 ][ 1 ] = -75;
	vecVecCorrectBorderpoints[ 1 ][ 0 ] = -140;
	vecVecCorrectBorderpoints[ 1 ][ 1 ] = 20;
	vecVecCorrectBorderpoints[ 2 ][ 0 ] = 40;
	vecVecCorrectBorderpoints[ 2 ][ 1 ] = 20;
	vecVecCorrectBorderpoints[ 3 ][ 0 ] = 50;
	vecVecCorrectBorderpoints[ 3 ][ 1 ] = 0;
	
	cout<<"hyperplaneBodyD2Max255.addInequiation( inequiation );"<<endl;
	bInequiationAdded = hyperplaneBodyD2Max255.addInequiation( inequiation );
	
	if ( bInequiationAdded ){
		cout<<"The inequiation was correctly successfully added."<<endl;
	}else{
		cerr<<"Error: The inequiation not successfully added."<<endl;
		iReturn++;
	}
	vecVecBorderPoints = hyperplaneBodyD2Max255.getBorderPoints();
	//check points in the body
	iReturn += checkBorderPoints( vecVecCorrectBorderpoints, vecVecBorderPoints);
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD2Max255, vecVecCorrectBorderpoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD2Max255, randomPointsInBody );
	
	cout<<"hyperplaneBodyD2Max255.print( cout );"<<endl;
	hyperplaneBodyD2Max255.print( cout );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing adding inequiation wich leaves only one line"<<endl;
/*
A inequiation: -100 <= x_0 + 2 * x_1 
*/
	//insert the inequiation
	cout<<"inequiation: 100 <= -1 * x_0 - 2 * x_1"<<endl;
	inequiation.constant = 100;
	
	inequiation.vecFactors = vector< double >( 2, 0.0 );
	inequiation.vecFactors[ 0 ] = -1;
	inequiation.vecFactors[ 1 ] = -2;
	
	randomPointsInBody = evalueValidPoints( inequiation, randomPointsInBody );
	
	vecVecCorrectBorderpoints.resize( 2 );
	vecVecCorrectBorderpoints[ 0 ][ 0 ] = 50;
	vecVecCorrectBorderpoints[ 0 ][ 1 ] = -75;
	vecVecCorrectBorderpoints[ 1 ][ 0 ] = -140;
	vecVecCorrectBorderpoints[ 1 ][ 1 ] = 20;
	
	cout<<"hyperplaneBodyD2Max255.addInequiation( inequiation );"<<endl;
	bInequiationAdded = hyperplaneBodyD2Max255.addInequiation( inequiation );
	
	if ( bInequiationAdded ){
		cout<<"The inequiation was correctly successfully added."<<endl;
	}else{
		cerr<<"Error: The inequiation not successfully added."<<endl;
		iReturn++;
	}
	vecVecBorderPoints = hyperplaneBodyD2Max255.getBorderPoints();
	//check points in the body
	iReturn += checkBorderPoints( vecVecCorrectBorderpoints, vecVecBorderPoints);
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD2Max255, vecVecCorrectBorderpoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD2Max255, randomPointsInBody );
	
	cout<<"hyperplaneBodyD2Max255.print( cout );"<<endl;
	hyperplaneBodyD2Max255.print( cout );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing adding inequiation wich leaves only one point"<<endl;
/*
A inequiation: -100 <= x_0 + 2 * x_1 
*/
	//insert the inequiation
	cout<<"inequiation: 0 <= 1.5 * x_0 + x_1"<<endl;
	inequiation.constant = 0;
	
	inequiation.vecFactors = vector< double >( 2, 0.0 );
	inequiation.vecFactors[ 0 ] = 1.5;
	inequiation.vecFactors[ 1 ] = 1;
	
	randomPointsInBody = evalueValidPoints( inequiation, randomPointsInBody );
	
	vecVecCorrectBorderpoints.resize( 1 );
	vecVecCorrectBorderpoints[ 0 ][ 0 ] = 50;
	vecVecCorrectBorderpoints[ 0 ][ 1 ] = -75;
	
	cout<<"hyperplaneBodyD2Max255.addInequiation( inequiation );"<<endl;
	bInequiationAdded = hyperplaneBodyD2Max255.addInequiation( inequiation );
	
	if ( bInequiationAdded ){
		cout<<"The inequiation was correctly successfully added."<<endl;
	}else{
		cerr<<"Error: The inequiation not successfully added."<<endl;
		iReturn++;
	}
	vecVecBorderPoints = hyperplaneBodyD2Max255.getBorderPoints();
	//check points in the body
	iReturn += checkBorderPoints( vecVecCorrectBorderpoints, vecVecBorderPoints);
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD2Max255, vecVecCorrectBorderpoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD2Max255, randomPointsInBody );
	
	cout<<"hyperplaneBodyD2Max255.print( cout );"<<endl;
	hyperplaneBodyD2Max255.print( cout );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing 3 dimensional body to add 0 inequiations ( 0 <= y_i )"<<endl;
	
	cout<<"tHyperplaneBody hyperplaneBodyD3Max100( 3, 100 );"<<endl;
	tHyperplaneBody hyperplaneBodyD3Max100( 3, 100 );
	
	cout<<"vecVecBorderPoints = hyperplaneBodyD3Max100.getBorderPoints();"<<endl;
	vecVecBorderPoints = hyperplaneBodyD3Max100.getBorderPoints();
	randomPointsInBody = generateRandCubusPoints( 3, 100.0 );
	randomPointsInBody.push_back( vector< double >( 3, 0.0 ) );
	
	//check points in the body
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD3Max100, vecVecBorderPoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD3Max100, randomPointsInBody );
	
	cout<<"hyperplaneBodyD3Max100.print( cout );"<<endl;
	hyperplaneBodyD3Max100.print( cout );
	
	
	//insert an inequiation
	cout<<"inequiation: 0 <= x_0"<<endl;
	inequiation.constant = 0;
	
	inequiation.vecFactors = vector< double >( 3, 0.0 );
	inequiation.vecFactors[ 0 ] = 1;
	
	randomPointsInBody = evalueValidPoints( inequiation, randomPointsInBody );
	
	cout<<"hyperplaneBodyD3Max100.addInequiation( inequiation );"<<endl;
	bInequiationAdded = hyperplaneBodyD3Max100.addInequiation( inequiation );
	
	if ( bInequiationAdded ){
		cout<<"The inequiation was correctly successfully added."<<endl;
	}else{
		cerr<<"Error: The inequiation not successfully added."<<endl;
		iReturn++;
	}
	vecVecBorderPoints = hyperplaneBodyD3Max100.getBorderPoints();
	//check points in the body
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD3Max100, vecVecBorderPoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD3Max100, randomPointsInBody );
	
	cout<<"hyperplaneBodyD3Max100.print( cout );"<<endl;
	hyperplaneBodyD3Max100.print( cout );
	
	
	//insert an inequiation
	cout<<"inequiation: 0 <= -1 *x_0"<<endl;
	inequiation.constant = 0;
	inequiation.vecFactors = vector< double >( 3, 0.0 );
	inequiation.vecFactors[ 0 ] = -1;
	
	randomPointsInBody = evalueValidPoints( inequiation, randomPointsInBody );
	
	cout<<"hyperplaneBodyD3Max100.addInequiation( inequiation );"<<endl;
	bInequiationAdded = hyperplaneBodyD3Max100.addInequiation( inequiation );
	
	if ( bInequiationAdded ){
		cout<<"The inequiation was correctly successfully added."<<endl;
	}else{
		cerr<<"Error: The inequiation not successfully added."<<endl;
		iReturn++;
	}
	vecVecBorderPoints = hyperplaneBodyD3Max100.getBorderPoints();
	//check points in the body
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD3Max100, vecVecBorderPoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD3Max100, randomPointsInBody );
	
	cout<<"hyperplaneBodyD3Max100.print( cout );"<<endl;
	hyperplaneBodyD3Max100.print( cout );
	
	
	//insert an inequiation
	cout<<"inequiation: 0 <= x_1"<<endl;
	inequiation.constant = 0;
	inequiation.vecFactors = vector< double >( 3, 0.0 );
	inequiation.vecFactors[ 1 ] = 1;
	
	randomPointsInBody = evalueValidPoints( inequiation, randomPointsInBody );
	
	cout<<"hyperplaneBodyD3Max100.addInequiation( inequiation );"<<endl;
	bInequiationAdded = hyperplaneBodyD3Max100.addInequiation( inequiation );
	
	if ( bInequiationAdded ){
		cout<<"The inequiation was correctly successfully added."<<endl;
	}else{
		cerr<<"Error: The inequiation not successfully added."<<endl;
		iReturn++;
	}
	vecVecBorderPoints = hyperplaneBodyD3Max100.getBorderPoints();
	//check points in the body
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD3Max100, vecVecBorderPoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD3Max100, randomPointsInBody );
	
	//cout<<"hyperplaneBodyD3Max100.print( cout );"<<endl;
	//hyperplaneBodyD3Max100.print( cout );
	
	//insert an inequiation
	cout<<"inequiation: 0 <= -1 * x_1"<<endl;
	inequiation.constant = 0;
	inequiation.vecFactors = vector< double >( 3, 0.0 );
	inequiation.vecFactors[ 1 ] = -1;
	
	randomPointsInBody = evalueValidPoints( inequiation, randomPointsInBody );
	
	cout<<"hyperplaneBodyD3Max100.addInequiation( inequiation );"<<endl;
	bInequiationAdded = hyperplaneBodyD3Max100.addInequiation( inequiation );
	
	if ( bInequiationAdded ){
		cout<<"The inequiation was correctly successfully added."<<endl;
	}else{
		cerr<<"Error: The inequiation not successfully added."<<endl;
		iReturn++;
	}
	vecVecBorderPoints = hyperplaneBodyD3Max100.getBorderPoints();
	//check points in the body
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD3Max100, vecVecBorderPoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD3Max100, randomPointsInBody );
	
	cout<<"hyperplaneBodyD3Max100.print( cout );"<<endl;
	hyperplaneBodyD3Max100.print( cout );


	//insert an inequiation
	cout<<"inequiation: 0 <= x_2"<<endl;
	inequiation.constant = 0;
	inequiation.vecFactors = vector< double >( 3, 0.0 );
	inequiation.vecFactors[ 2 ] = 1;
	
	randomPointsInBody = evalueValidPoints( inequiation, randomPointsInBody );
	
	cout<<"hyperplaneBodyD3Max100.addInequiation( inequiation );"<<endl;
	bInequiationAdded = hyperplaneBodyD3Max100.addInequiation( inequiation );
	
	if ( bInequiationAdded ){
		cout<<"The inequiation was correctly successfully added."<<endl;
	}else{
		cerr<<"Error: The inequiation not successfully added."<<endl;
		iReturn++;
	}
	vecVecBorderPoints = hyperplaneBodyD3Max100.getBorderPoints();
	//check points in the body
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD3Max100, vecVecBorderPoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD3Max100, randomPointsInBody );
	
	//cout<<"hyperplaneBodyD3Max100.print( cout );"<<endl;
	//hyperplaneBodyD3Max100.print( cout );
	
	//insert an inequiation
	cout<<"inequiation: 0 <= -1 * x_2"<<endl;
	inequiation.constant = 0;
	inequiation.vecFactors = vector< double >( 3, 0.0 );
	inequiation.vecFactors[ 2 ] = -1;
	
	randomPointsInBody = evalueValidPoints( inequiation, randomPointsInBody );
	
	cout<<"hyperplaneBodyD3Max100.addInequiation( inequiation );"<<endl;
	bInequiationAdded = hyperplaneBodyD3Max100.addInequiation( inequiation );
	
	if ( bInequiationAdded ){
		cout<<"The inequiation was correctly successfully added."<<endl;
	}else{
		cerr<<"Error: The inequiation not successfully added."<<endl;
		iReturn++;
	}
	vecVecBorderPoints = hyperplaneBodyD3Max100.getBorderPoints();
	//check points in the body
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD3Max100, vecVecBorderPoints );
	iReturn += checkIfPointsAreInBody( hyperplaneBodyD3Max100, randomPointsInBody );
	
	cout<<"hyperplaneBodyD3Max100.print( cout );"<<endl;
	hyperplaneBodyD3Max100.print( cout );
	
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing on random generated bodys and inequiations"<<endl;
	
	unsigned long ulBodiesGenerated = 0;
	unsigned long ulInequiationsGenerated = 0;
	unsigned long ulInequiationsAdded = 0;
	
	unsigned int uiDimensionMaxIncrease = 1;
	unsigned long ulNextDimensionIncrease = 8;
	
	//test on random generated bodys and inequiations
	for ( unsigned int uIterationBodies = 1;
			uIterationBodies <= (MAX_ITERATION / 32 + 1); uIterationBodies++ ){
		//generate new body
		cout<<endl<<"TESTPASE "<<ulTestphase<<" :Generating "<<uIterationBodies<<"'th new hyperplane body "<<endl;
		
		ulBodiesGenerated++;
		if ( ulNextDimensionIncrease < ulBodiesGenerated ){
			//increase max dimension with 1
			uiDimensionMaxIncrease++;
			ulNextDimensionIncrease *= ulNextDimensionIncrease;
		}
		
		unsigned int uiNumberOfDimensions = 0;
		if ( rand() % 32 ){
			uiNumberOfDimensions = rand() % ( (rand() % uiDimensionMaxIncrease) + 4 ) + 1;
		}//else uiNumberOfDimensions = 0
		const double dMaxValue = ((double)(rand())) / ((double)(rand() + 1));
		const double dNegMaxValue = -1.0 * dMaxValue;
		
		cout<<"tHyperplaneBody bodyRand( "<<uiNumberOfDimensions<<", "<<dMaxValue<<" );"<<endl;
		tHyperplaneBody bodyRand( uiNumberOfDimensions, dMaxValue );
		
		cout<<"vecVecBorderPoints = bodyRand.getBorderPoints();"<<endl;
		vector< vector< double > > vecVecBorderPoints = bodyRand.getBorderPoints();
		
		if ( ( dMaxValue == 0.0 ) || ( uiNumberOfDimensions == 0 ) ){
			if ( vecVecBorderPoints.empty() ){
				cout<<"Correctly no border points/body generated."<<endl;
			}else{
				cerr<<"Error: Ther wher border points/a body generated."<<endl;
				iReturn++;
			}
			//skipp this (non) body
			continue;
		}
		
		/*check border points:
			- ther are 2 ^ uiNumberOfDimensions border points
			- ther element values are dMaxValue or -1 * dMaxValue
			- ther are no duplicate border points*/
		//check ther are 2 ^ uiNumberOfDimensions border points
		if ( vecVecBorderPoints.size() == pow( 2, uiNumberOfDimensions) ){
			cout<<"Ther are correctly "<<vecVecBorderPoints.size()<<
				" border points."<<endl;
		}else{
			cerr<<"Error: Ther are "<<vecVecBorderPoints.size()<<
				" border points, but it should be "<<pow( 2, uiNumberOfDimensions)<<" ."<<endl;
			iReturn++;
		}
		{//ther are no duplicate border points
			set< vector< double > > setVecBorderpoints( vecVecBorderPoints.begin(),
				vecVecBorderPoints.end() );
			if ( vecVecBorderPoints.size() != setVecBorderpoints.size() ){
				cerr<<"Error: Ther are "<<(vecVecBorderPoints.size() -
					setVecBorderpoints.size())<<" duplicate border points ."<<endl;
				iReturn++;
			}
		}
		//ther element values are dMaxValue or -1 * dMaxValue
		for ( unsigned int uiBorderPoint = 0;
				uiBorderPoint < vecVecBorderPoints.size(); uiBorderPoint++ ){
			
			if ( vecVecBorderPoints[ uiBorderPoint ].size() == uiNumberOfDimensions ){
				for ( unsigned int uiActualElement = 0;
						uiActualElement < uiNumberOfDimensions; uiActualElement++ ){
					
					const double dActualElement = 
						vecVecBorderPoints[ uiBorderPoint ][ uiActualElement ];
					if ( ( dActualElement != dMaxValue ) &&
							( dActualElement != dNegMaxValue ) ){
						cerr<<"Error: The "<<uiBorderPoint<<"'th border point has as the "<<
							uiActualElement<<"'th element not the max value "<<
							dMaxValue<<", but the value "<<dActualElement<<" ."<<endl;
						printVector( cerr, vecVecBorderPoints[ uiBorderPoint ] );
						iReturn++;
					}
				}
			}else{
				cerr<<"Error: The "<<uiBorderPoint<<"'th border point has not "<<
					uiNumberOfDimensions<<" elements."<<endl;
				printVector( cerr, vecVecBorderPoints[ uiBorderPoint ] );
				iReturn++;
			}
		}
		vector< vector< double > > randomPointsInBody =
			generateRandCubusPoints( uiNumberOfDimensions,
				vecVecBorderPoints[ 0 ][ 0 ], vecVecBorderPoints.size() * 256 );
		
		//insert border points in to check points
		randomPointsInBody.insert( randomPointsInBody.end(),
			vecVecBorderPoints.begin(), vecVecBorderPoints.end() );
	
		//test if in constructed (non restricted) body are all points
		cout<<"Random points generated in body: "<<randomPointsInBody.size()<<endl;
		
		iReturn += checkIfPointsAreInBody( bodyRand, randomPointsInBody );
		
		//restrict body with inequiations, for that generate and insert random inequiations
		for ( unsigned int iterationInequiation = 1;
			 	iterationInequiation <= ((MAX_ITERATION / 16 * uiNumberOfDimensions + 1));
			 	iterationInequiation++ ){
			//generate random inequiation(s)
			const bool bAddOneInequiation = rand() % 2;
			unsigned int uiInequiationsToAdd = 1;
			cout<<endl<<"Iteration "<<iterationInequiation<<" for "<<uIterationBodies<<
				"'th random body (dim="<<uiNumberOfDimensions<<"): Generating "<<
				uiInequiationsToAdd<<" random inequiations to add "<<endl<<flush;
			if ( ! bAddOneInequiation ){
				//use addInequiations()
				uiInequiationsToAdd = rand() % (uiNumberOfDimensions + 32);
			}
			vector< cInequation< double > > vecInequiationsToAdd( uiInequiationsToAdd );
			for ( unsigned int uiCreatedInequiations = 0;
					uiCreatedInequiations < uiInequiationsToAdd;
					uiCreatedInequiations++ ){
				
				cInequation< double > & inequiation =
					vecInequiationsToAdd[ uiCreatedInequiations ];
				
				inequiation.constant =
					( ((double)(rand())) / ((double)(RAND_MAX)) ) * dMaxValue;
				if ( rand() % 2 ){
					
					inequiation.constant = inequiation.constant *
						((double)(rand() % 64)) / 4.0;
				}
				
				unsigned int uiToCreateFactors = uiNumberOfDimensions;
				if ( (rand() % uiInequiationsToAdd) == 0 ){
					/*create inequiation with from number of dimensions
					different number of factors*/
					uiToCreateFactors = rand() % (uiNumberOfDimensions * 2);
				}
				
				inequiation.vecFactors = vector< double >( uiToCreateFactors, 0.0 );
				for ( unsigned int uiCreatedFactor = 0;
						uiCreatedFactor < uiToCreateFactors; uiCreatedFactor++ ){
					
					inequiation.vecFactors[ uiCreatedFactor ] =
						((double)(rand())) / ((double)(rand() + 1));
				}
			}//end for uiCreatedInequiations
			
			//try to add inequiation(s)
			unsigned int uiAddedInequiations = 0;
			if ( bAddOneInequiation ){
				cout<<"bodyRand.addInequiation( inequiationToAdd )"<<endl<<flush;
				bool bInequiationAdded =
					bodyRand.addInequiation( vecInequiationsToAdd[ 0 ] );
				
				if ( bInequiationAdded ){
					uiAddedInequiations = 1;
				}
			}else{
				cout<<"bodyRand.addInequiations( vecInequiationsToAdd )"<<endl<<flush;
				uiAddedInequiations =
					bodyRand.addInequiations( vecInequiationsToAdd );
			}
			cout<<"Ther wher "<<uiAddedInequiations<<" inerquiations from "<<
				uiInequiationsToAdd<<" inequiations added."<<endl<<flush;
			ulInequiationsGenerated += uiInequiationsToAdd;
			ulInequiationsAdded += uiAddedInequiations;
			/*update random points in body, for that remove all points which
			dosn't fulfill inequiation*/
			vector< vector< double > > randomPointsNotInBody;
			for ( unsigned int uiActualInequiation = 0;
					uiActualInequiation < uiAddedInequiations; uiActualInequiation++ ){
				
				randomPointsInBody = evalueValidPoints(
					vecInequiationsToAdd[ uiActualInequiation ], randomPointsInBody,
					randomPointsNotInBody );
			}
			{//test if in restrict body are all remaining points
				unsigned int iReturnTmp = checkIfPointsAreInBody( bodyRand, randomPointsInBody );
				iReturnTmp += checkIfPointsAreNotInBody( bodyRand, randomPointsNotInBody );
				if ( iReturnTmp != 0 ){
					cerr<<endl<<"Inequiations added: "<<endl;
					for ( unsigned int uiActualInequiation = 0;
							uiActualInequiation < uiAddedInequiations; uiActualInequiation++ ){
						
						vecInequiationsToAdd[ uiActualInequiation ].print( cerr );
					}
					cerr<<endl<<"Inequiations not added: "<<endl;
					for ( unsigned int uiActualInequiation = uiAddedInequiations;
							uiActualInequiation < uiInequiationsToAdd; uiActualInequiation++ ){
						
						vecInequiationsToAdd[ uiActualInequiation ].print( cerr );
					}
					cerr<<endl<<"Actual body wher points: ";
					bodyRand.print( cerr );
					iReturn++;
				}
			}
			if ( uiAddedInequiations != uiInequiationsToAdd ){
				/*not all inequiations wher added
				-> the not added inequiation should remove all remaining random points*/
				const vector< vector< double > > randomPointsInNoBody = evalueValidPoints(
					vecInequiationsToAdd[ uiAddedInequiations ], randomPointsInBody );
				
				if ( ! randomPointsInNoBody.empty() ){
					cerr<<"Error: The "<<uiAddedInequiations<<"'th inequiation "<<
						"was not added because it removes the body, but it leaves "<<
						randomPointsInNoBody.size()<<" points in the body."<<endl;
					cerr<<"Not added inequiation: ";
					vecInequiationsToAdd[ uiAddedInequiations ].print( cerr );
					cerr<<endl<<"Body wher the inequiation should remove all points: ";
					bodyRand.print( cerr );
					iReturn++;
				}
			}
			//check if all body border points have as a maximum dMaxValue
			const vector< vector< double > > borderPoints =
				bodyRand.getBorderPoints();
			
			const double dUpperBorder = dMaxValue * 1.01;
			const double dLowerBorder = dMaxValue * -1.01;
			
			unsigned int uiNumberOfWrongBourderPoints = 0;
			for ( vector< vector< double > >::const_iterator
					itrBorderPoint = borderPoints.begin();
					itrBorderPoint != borderPoints.end(); itrBorderPoint++ ){
				
				for ( vector< double >::const_iterator
						itrElement = itrBorderPoint->begin();
						itrElement != itrBorderPoint->end(); itrElement++ ){
					
					if ( ( *itrElement < dLowerBorder ) || ( dUpperBorder < *itrElement ) ){
						
						cerr<<"Error: The border point is outside the maximum boundery of the body."<<endl;
						cerr<<"border point: ";
						printVector( cerr, * itrBorderPoint );
						uiNumberOfWrongBourderPoints++;
					}
				}
			}
			if ( uiNumberOfWrongBourderPoints != 0 ){
				cerr<<endl<<"Inequiations added: "<<endl;
				for ( unsigned int uiActualInequiation = 0;
						uiActualInequiation < uiAddedInequiations; uiActualInequiation++ ){
					
					vecInequiationsToAdd[ uiActualInequiation ].print( cerr );
				}
				cerr<<endl<<"Inequiations not added: "<<endl;
				for ( unsigned int uiActualInequiation = uiAddedInequiations;
						uiActualInequiation < uiInequiationsToAdd; uiActualInequiation++ ){
					
					vecInequiationsToAdd[ uiActualInequiation ].print( cerr );
				}
				cerr<<endl<<"Body wher the inequiation should remove the "<<
					uiNumberOfWrongBourderPoints<<" border points: ";
				bodyRand.print( cerr );
				iReturn++;
			}
			
			//check if the with getPointInBody() returned point is part of the body
			unsigned int uiMaxBitsNeededForMatissa = rand() % 32;
			cout<<"check pointInBody = bodyRand.getPointInBody("<<
				uiMaxBitsNeededForMatissa<<"); "<<endl<<flush;
			const vector< double > pointInBody =
				bodyRand.getPointInBody( uiMaxBitsNeededForMatissa );
			cerr<<"returned point in body:"<<endl;
			printVector( cout, pointInBody );
			if ( ! bodyRand.isPart( pointInBody ) ){
					cerr<<"pointInBody = bodyRand.getPointInBody();"<<endl;
					cerr<<"Error: The returned point is not part of the body."<<endl;
					cerr<<"Point:"<<endl;
					printVector( cerr, pointInBody );
					cerr<<"Body:"<<endl;
					bodyRand.print( cerr );
					iReturn++;
			}

		}
	}
	
	cout<<endl<<"Testing on random generated bodys and inequiations done."<<endl;
	cout<<"   bodies generated:       "<<ulBodiesGenerated<<endl;
	cout<<"   inequiations generated: "<<ulBodiesGenerated<<endl;
	cout<<"   inequiations added:     "<<ulInequiationsAdded<<endl<<endl;
	

	return iReturn;
}

























