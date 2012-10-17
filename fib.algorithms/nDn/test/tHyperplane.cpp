/**
 * @file tHyperplane
 * file name: tHyperplane.cpp
 * @author Betti Oesterholz
 * @date 10.01.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cHyperplane.
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
 * This file contains the test for the class cHyperplane, which
 * represents a hyperplane.
 *
 *
 * What's tested of class cHyperplane:
 * 	- cHyperplane();
 * 	- cHyperplane( const vector< tFactors > & vecInBase, const vector< vector< tFactors > > & vecInDirections );
 * 	- cHyperplane( const nLinearInequation::cInequation< tFactors > & inequation );
 * 	- vector< tFactors > getBase( const vector< tFactors > & vecInBase ) const;
 * 	- void setBase( const vector< tFactors > & vecInBase );
 * 	- vector< tFactors > getDirection( const unsigned int uiDirection ) const;
 * 	- vector< vector< tFactors > > getDirections() const;
 * 	- unsigned int getNumberOfDirections() const;
 * 	- bool addDirection( const vector< tFactors > & vecInDirection );
 * 	- unsigned int addDirections( vector< vector< tFactors > > vecInDirections );
 * 	- bool deleteDirection( unsigned int uiDirection );
 * 	- unsigned int getNumberOfDimensions() const;
 * 	- unsigned int setNumberOfDimensions( unsigned int uiDimensionality );
 * 	- bool equal( const cHyperplane< tFactors > & hyperplane ) const;
 * 	- void makeDirectionsIndependent();
 * 	- void convertToFormOne();
 * 	- cHyperplane< tFactors > * evalueIntersection( const cHyperplane< tFactors > & hyperplane ) const;
 * 	- void print( ostream & outputStream ) const;
 *
 *
 * call: tHyperplane [ITERATIONS]
 *
 * parameters:
 * 	ITERATIONS
 * 		The iterations for the test with random generated hyperplanes.
 * 		Standardvalue is 256.
 *
 */
/*
History:
10.01.2011  Oesterholz  created
*/

//TODO weg
//#define DEBUG


#include "version.h"

#include "cHyperplane.h"
#include "cInequation.h"

#include "../test/tCompareBits.inc"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <ctime>
#include <string>


using namespace std;

using namespace fib::algorithms::nDn;
using namespace fib::algorithms::nLinearInequation;


int testCostructor( unsigned long &ulTestphase );
int testBase( unsigned long &ulTestphase );
int testDirections( unsigned long &ulTestphase );
int testDimensions( unsigned long &ulTestphase );
int testEqual( unsigned long &ulTestphase );
int testMakeDirectionsIndependent( unsigned long &ulTestphase );
int testIntersection( unsigned long &ulTestphase );
int testConvertToFormOne( unsigned long &ulTestphase );


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

	cout<<endl<<"Running Test for cHyperplane methods"<<endl;
	cout<<      "===================================="<<endl;
	
	iReturn += testCostructor( ulTestphase );
	iReturn += testBase( ulTestphase );
	iReturn += testDirections( ulTestphase );
	iReturn += testDimensions( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testMakeDirectionsIndependent( ulTestphase );

	//still open TODO because of rounding errors:
	iReturn += testIntersection( ulTestphase );
	iReturn += testConvertToFormOne( ulTestphase );

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
template< class tElements >
void printVector( ostream & outputStream, const vector< tElements > & vector ){
	
	outputStream<<"( ";
	for ( unsigned int uiDimension = 0; uiDimension < vector.size();
			uiDimension++ ){
		
		outputStream<< vector[ uiDimension ] <<", ";
	}
	outputStream<<")^T"<<endl;
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
 * This function tests the constructor of the cHyperplane class.
 *
 * methods tested:
 * 	- cHyperplane();
 * 	- cHyperplane( const vector< tFactors > & vecInBase, const vector< vector< tFactors > > & vecInDirections );
 * 	- cHyperplane( const nLinearInequation::cInequation< tFactors > & inequation );
 * 	- vector< tFactors > getBase( const vector< tFactors > & vecInBase ) const;
 * 	- vector< vector< tFactors > > getDirections() const;
 * 	- unsigned int getNumberOfDirections() const;
 * 	- unsigned int getNumberOfDimensions() const;
 * 	- void print( ostream & outputStream ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"Testing the constructors, please check the printed hyperplanes"<<endl;
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty hyperplane"<<endl;

	cout<<"vector< double > vecEmptyBase;"<<endl;
	vector< double > vecEmptyBase;
	cout<<"vector< vector< double > > vecEmptyDirections;"<<endl;
	vector< vector< double > > vecEmptyDirections;
	
	cout<<"cHyperplane< double > emptyHyperplane;"<<endl;
	cHyperplane< double > emptyHyperplane;
	
	//check the getNumberOfDirections() methode from cHyperplane
	if ( emptyHyperplane.getNumberOfDirections() == 0 ){
	
		cout<<"The hyperplane has correctly 0 direction vectors. "<<endl;
	}else{
		cerr<<"Error: The hyperplane has "<<emptyHyperplane.getNumberOfDirections()<<
			" direction vectors, but should have 0 ."<<endl;
		iReturn++;
	}
	//check the getNumberOfDimensions() methode from cHyperplane
	if ( emptyHyperplane.getNumberOfDimensions() == 0 ){
	
		cout<<"The hyperplane is correctly for 0 dimensions. "<<endl;
	}else{
		cerr<<"Error: The hyperplane is for "<<emptyHyperplane.getNumberOfDirections()<<
			" dimensions, but should be for 0 ."<<endl;
		iReturn++;
	}
	//check the getBase() methode from cHyperplane
	cout<<"testBase = emptyHyperplane.getBase();"<<endl;
	vector< double > testBase = emptyHyperplane.getBase();
	if ( testBase.empty() ){
	
		cout<<"The hyperplane has correctly base vector with no dimensions. "<<endl;
	}else{
		cerr<<"Error: The hyperplane has a base vector with dimensions."<<endl;
		iReturn++;
	}
	//check the getDirections() methode from cHyperplane
	cout<<"testDirections = emptyHyperplane.getDirections();"<<endl;
	vector< vector< double > > testDirections = emptyHyperplane.getDirections();
	if ( vecEmptyDirections == testDirections ){
	
		cout<<"The hyperplane has the correct direction vectors. "<<endl;
	}else{
		cerr<<"Error: The hyperplane has not the correct direction vectors."<<endl;
		iReturn++;
	}
	cout<<"emptyHyperplane.print( cout ) "<<endl;
	emptyHyperplane.print( cout );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty hyperplane with parameters"<<endl;

	cout<<"cHyperplane< double > emptyHyperplaneParam( vecEmptyBase, vecEmptyDirections );"<<endl;
	cHyperplane< double > emptyHyperplaneParam( vecEmptyBase, vecEmptyDirections );
	
	//check the getNumberOfDirections() methode from cHyperplane
	if ( emptyHyperplaneParam.getNumberOfDirections() == 0 ){
	
		cout<<"The hyperplane has correctly 0 direction vectors. "<<endl;
	}else{
		cerr<<"Error: The hyperplane has "<<emptyHyperplaneParam.getNumberOfDirections()<<
			" direction vectors, but should have 0 ."<<endl;
		iReturn++;
	}
	//check the getNumberOfDimensions() methode from cHyperplane
	if ( emptyHyperplaneParam.getNumberOfDimensions() == 0 ){
	
		cout<<"The hyperplane is correctly for 0 dimensions. "<<endl;
	}else{
		cerr<<"Error: The hyperplane is for "<<emptyHyperplaneParam.getNumberOfDirections()<<
			" dimensions, but should be for 0 ."<<endl;
		iReturn++;
	}
	//check the getBase() methode from cHyperplane
	cout<<"testBase = emptyHyperplaneParam.getBase();"<<endl;
	testBase = emptyHyperplaneParam.getBase();
	if ( testBase.empty() ){
	
		cout<<"The hyperplane has correctly base vector with no dimensions. "<<endl;
	}else{
		cerr<<"Error: The hyperplane has a base vector with dimensions."<<endl;
		iReturn++;
	}
	//check the getDirections() methode from cHyperplane
	cout<<"testDirections = emptyHyperplaneParam.getDirections();"<<endl;
	testDirections = emptyHyperplaneParam.getDirections();
	if ( vecEmptyDirections == testDirections ){
	
		cout<<"The hyperplane has the correct direction vectors. "<<endl;
	}else{
		cerr<<"Error: The hyperplane has not the correct direction vectors."<<endl;
		iReturn++;
	}
	cout<<"emptyHyperplaneParam.print( cout ) "<<endl;
	emptyHyperplaneParam.print( cout );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an hyperplane for float and two directions"<<endl;
	
	cout<<"vector< float > vecBase2;"<<endl;
	vector< float > vecBase2( 1, -1.0 );
	
	vector< float > vecBase2Correct( 3, 0.0 );
	vecBase2Correct[ 0 ] = -1.0;
	
	cout<<"vector< vector< double > > vecDirections2;"<<endl;
	vector< vector< float > > vecDirections2;
	cout<<"vector< float > vecDirection1( 1, 1.0 );"<<endl;
	vector< float > vecDirection1( 1, 1.0 );
	vecDirections2.push_back( vecDirection1 );
	cout<<"vector< float > vecDirection2( 3, 2.0 );"<<endl;
	vector< float > vecDirection2( 3, 2.0 );
	vecDirection2[ 1 ] = 1;
	vecDirections2.push_back( vecDirection2 );

	vector< vector< float > > vecDirections2Correct;
	vecDirection1.resize( 3, 0.0 );
	vecDirections2Correct.push_back( vecDirection1 );
	vecDirections2Correct.push_back( vecDirection2 );

	cout<<"cHyperplane< float > hyperplane2( vecBase2, vecDirections2 );"<<endl;
	cHyperplane< float > hyperplane2( vecBase2, vecDirections2 );
	
	//check the getNumberOfDirections() methode from cHyperplane
	if ( hyperplane2.getNumberOfDirections() == 2 ){
	
		cout<<"The hyperplane has correctly "<<
			hyperplane2.getNumberOfDirections()<<" direction vectors. "<<endl;
	}else{
		cerr<<"Error: The hyperplane has "<<hyperplane2.getNumberOfDirections()<<
			" direction vectors, but should have 2 ."<<endl;
		iReturn++;
	}
	//check the getNumberOfDimensions() methode from cHyperplane
	if ( hyperplane2.getNumberOfDimensions() == 3 ){
	
		cout<<"The hyperplane is correctly for "<<
			hyperplane2.getNumberOfDimensions()<<" dimensions. "<<endl;
	}else{
		cerr<<"Error: The hyperplane is for "<<hyperplane2.getNumberOfDirections()<<
			" dimensions, but should be for 3 ."<<endl;
		iReturn++;
	}
	//check the getBase() methode from cHyperplane
	cout<<"testBaseF = hyperplane2.getBase();"<<endl;
	vector< float > testBaseF = hyperplane2.getBase();
	if ( vecBase2Correct == testBaseF ){
	
		cout<<"The hyperplane has correct base vector. "<<endl;
	}else{
		cerr<<"Error: The hyperplane has not the correct base vector (dim="<<
			testBaseF.size() <<")."<<endl;
		iReturn++;
	}
	//check the getDirections() methode from cHyperplane
	cout<<"testDirectionsF = hyperplane2.getDirections();"<<endl;
	vector< vector< float > > testDirectionsF = hyperplane2.getDirections();
	if ( vecDirections2Correct == testDirectionsF ){
	
		cout<<"The hyperplane has the correct direction vectors. "<<endl;
	}else{
		cerr<<"Error: The hyperplane has not the correct direction vectors."<<endl;
		iReturn++;
	}
	cout<<"hyperplane2.print( cout ) "<<endl;
	hyperplane2.print( cout );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an hyperplane with a given inequation (1 <= 2 * x_1 + 6 * x_2)"<<endl;
	
	/*inequation: 1 <= 2 * x_1 + 6 * x_2   -> (N=(2,6)^T)
		-> 0 = 1 - ( (2, 6)^T * X )*/
	cout<<"cInequation< double > inequation;"<<endl;
	cInequation< double > inequation;
	cout<<"inequation.constant = 1.0; "<<endl;
	inequation.constant = 1.0;
	cout<<"inequation.vecFactors.push_back( 2.0 ); "<<endl;
	inequation.vecFactors.push_back( 2.0 );
	cout<<"inequation.vecFactors.push_back( 6.0 );"<<endl;
	inequation.vecFactors.push_back( 6.0 );
	
	vector< double > vecBaseInequationCorrect( 2, 0.0 );
	vecBaseInequationCorrect[ 0 ] = ((double)0.05);
	vecBaseInequationCorrect[ 1 ] = ((double)0.15);
	
	vector< vector< double > > vecDirectionsInequationCorrect;
	vector< double > vecDirectionInequation( 2, 0.0 );
	vecDirectionInequation[ 0 ] = 1.0;
	vecDirectionInequation[ 1 ] = ((double)-1.0)/ ((double)3.0);
	vecDirectionsInequationCorrect.push_back( vecDirectionInequation );
	
	cout<<"cHyperplane< double > hyperplaneInequation( inequation );"<<endl;
	cHyperplane< double > hyperplaneInequation( inequation );

	//check the getNumberOfDirections() methode from cHyperplane
	if ( hyperplaneInequation.getNumberOfDirections() == 1 ){
	
		cout<<"The hyperplane has correctly "<<
			hyperplaneInequation.getNumberOfDirections()<<" direction vectors. "<<endl;
	}else{
		cerr<<"Error: The hyperplane has "<<hyperplaneInequation.getNumberOfDirections()<<
			" direction vectors, but should have 1 ."<<endl;
		iReturn++;
	}
	//check the getNumberOfDimensions() methode from cHyperplane
	if ( hyperplaneInequation.getNumberOfDimensions() == 2 ){
	
		cout<<"The hyperplane is correctly for "<<
			hyperplaneInequation.getNumberOfDimensions()<<" dimensions. "<<endl;
	}else{
		cerr<<"Error: The hyperplane is for "<<hyperplaneInequation.getNumberOfDirections()<<
			" dimensions, but should be for 2 ."<<endl;
		iReturn++;
	}
	//check the getBase() methode from cHyperplane
	cout<<"testBase = hyperplaneInequation.getBase();"<<endl;
	testBase = hyperplaneInequation.getBase();
	
	//check with compare vectors with double range comparrison
	if ( compareVectorDouble( vecBaseInequationCorrect, testBase ) ){
	
		cout<<"The hyperplane has correct base vector. "<<endl;
	}else{
		cerr<<"Error: The hyperplane has not the correct base vector (dim="<<
			testBase.size() <<")."<<endl;
		cerr<<"Base given back: ";
		printVector( cerr , testBase );
		cerr<<"Correct base:    ";
		printVector( cerr , vecBaseInequationCorrect );
		iReturn++;
	}
	//check the getDirections() methode from cHyperplane
	cout<<"testDirections = hyperplaneInequation.getDirections();"<<endl;
	testDirections = hyperplaneInequation.getDirections();
	if ( vecDirectionsInequationCorrect == testDirections ){
	
		cout<<"The hyperplane has the correct direction vectors. "<<endl;
	}else{
		cerr<<"Error: The hyperplane has not the correct direction vectors."<<endl;
		iReturn++;
	}

	cout<<"hyperplaneInequation.print( cout ) "<<endl;
	hyperplaneInequation.print( cout );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an hyperplane with a given inequation (12 <= 2 * x_1 + 3 * x_2 + 5 * x_3)"<<endl;
	
	cout<<"cInequation< double > inequation2;"<<endl;
	cInequation< double > inequation2;
	cout<<"inequation2.constant = 12.0; "<<endl;
	inequation2.constant = 12.0;
	cout<<"inequation2.vecFactors.push_back( 2.0 ); "<<endl;
	inequation2.vecFactors.push_back( 2.0 );
	cout<<"inequation2.vecFactors.push_back( 3.0 );"<<endl;
	inequation2.vecFactors.push_back( 3.0 );
	cout<<"inequation2.vecFactors.push_back( 5.0 );"<<endl;
	inequation2.vecFactors.push_back( 5.0 );
	
	vecBaseInequationCorrect.resize( 3, 0.0 );
	//2^2 + 3^2 + 5^2 = 38
	vecBaseInequationCorrect[ 0 ] = ((double)12.0 * 2.0)/((double)38.0);
	vecBaseInequationCorrect[ 1 ] = ((double)12.0 * 3.0)/((double)38.0);
	vecBaseInequationCorrect[ 2 ] = ((double)12.0 * 5.0)/((double)38.0);
	
	vecDirectionsInequationCorrect.clear();
	vecDirectionInequation.resize( 3, 0.0 );
	vecDirectionInequation[ 0 ] = 1.0;
	vecDirectionInequation[ 1 ] = 0.0;
	vecDirectionInequation[ 2 ] = ((double)-2.0)/ ((double)5.0);
	vecDirectionsInequationCorrect.push_back( vecDirectionInequation );
	vecDirectionInequation[ 0 ] = 0.0;
	vecDirectionInequation[ 1 ] = 1.0;
	vecDirectionInequation[ 2 ] = ((double)-3.0)/ ((double)5.0);
	vecDirectionsInequationCorrect.push_back( vecDirectionInequation );
	
	
	cout<<"cHyperplane< double > hyperplaneInequation2( inequation2 );"<<endl;
	cHyperplane< double > hyperplaneInequation2( inequation2 );

	//check the getNumberOfDirections() methode from cHyperplane
	if ( hyperplaneInequation2.getNumberOfDirections() == 2 ){
	
		cout<<"The hyperplane has correctly "<<
			hyperplaneInequation2.getNumberOfDirections()<<" direction vectors. "<<endl;
	}else{
		cerr<<"Error: The hyperplane has "<<hyperplaneInequation2.getNumberOfDirections()<<
			" direction vectors, but should have 2 ."<<endl;
		iReturn++;
	}
	//check the getNumberOfDimensions() methode from cHyperplane
	if ( hyperplaneInequation2.getNumberOfDimensions() == 3 ){
	
		cout<<"The hyperplane is correctly for "<<
			hyperplaneInequation2.getNumberOfDimensions()<<" dimensions. "<<endl;
	}else{
		cerr<<"Error: The hyperplane is for "<<hyperplaneInequation2.getNumberOfDirections()<<
			" dimensions, but should be for 3 ."<<endl;
		iReturn++;
	}
	//check the getBase() methode from cHyperplane
	cout<<"testBase = hyperplaneInequation2.getBase();"<<endl;
	testBase = hyperplaneInequation2.getBase();
	
	//check with compare vectors with double range comparrison
	if ( compareVectorDouble( vecBaseInequationCorrect, testBase ) ){
	
		cout<<"The hyperplane has correct base vector. "<<endl;
	}else{
		cerr<<"Error: The hyperplane has not the correct base vector (dim="<<
			testBase.size() <<")."<<endl;
		cerr<<"Base given back: ";
		printVector( cerr , testBase );
		cerr<<"Correct base:    ";
		printVector( cerr , vecBaseInequationCorrect );
		iReturn++;
	}
	//check the getDirections() methode from cHyperplane
	cout<<"testDirections = hyperplaneInequation2.getDirections();"<<endl;
	testDirections = hyperplaneInequation2.getDirections();
	if ( vecDirectionsInequationCorrect == testDirections ){
	
		cout<<"The hyperplane has the correct direction vectors. "<<endl;
	}else{
		cerr<<"Error: The hyperplane has not the correct direction vectors."<<endl;
		iReturn++;
	}

	cout<<"hyperplaneInequation2.print( cout ) "<<endl;
	hyperplaneInequation2.print( cout );


	return iReturn;
}


/**
 * This function tests the base vector methods of the cHyperplane class.
 *
 * methods tested:
 * 	- vector< tFactors > getBase( const vector< tFactors > & vecInBase ) const;
 * 	- void setBase( const vector< tFactors > & vecInBase );
 * 	- unsigned int setNumberOfDimensions( unsigned int uiDimensionality );
 * 	- vector< vector< tFactors > > getDirections() const;
 * 	- unsigned int getNumberOfDirections() const;
 * 	- unsigned int getNumberOfDimensions() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testBase( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setting random new bases for hyperplane"<<endl;
	
	vector< double > vecBaseCorrect( 2, 0.0 );
	
	vector< vector< double > > vecDirectionsCorrect;
	vector< double > vecDirection1( 2, 0.0 );
	vecDirection1[ 0 ] = 1;
	vecDirectionsCorrect.push_back( vecDirection1 );
	vector< double > vecDirection2( 2, 0.0 );
	vecDirection2[ 1 ] = 1;
	vecDirectionsCorrect.push_back( vecDirection2 );

	cout<<"cHyperplane< double > hyperplane( vecBaseCorrect, vecDirectionsCorrect );"<<endl;
	cHyperplane< double > hyperplane( vecBaseCorrect, vecDirectionsCorrect );
	
	unsigned int uiNumberOfDimensions = 2;
	
	for ( unsigned int uiIteration = 0; uiIteration < MAX_ITERATION; uiIteration++ ){
		
		cout<<endl<<"Generating the new base vector:"<<endl;
		unsigned int uiNumberOfDimensionsNew = uiNumberOfDimensions;
		bool bDimensionalityChanged = false;
		if ( rand() % 8 == 0 ){
			//set new base more and less dimensions
			uiNumberOfDimensionsNew = (rand() % (rand() % 64 + 1) );
			cout<<"Changing dimensionality from "<<uiNumberOfDimensions<<
				" to "<<uiNumberOfDimensionsNew<<endl;
			
			if ( uiNumberOfDimensions < uiNumberOfDimensionsNew ){
				//increase the number of dimensions
				uiNumberOfDimensions = uiNumberOfDimensionsNew;
				bDimensionalityChanged = true;
			}else if ( (uiNumberOfDimensionsNew < uiNumberOfDimensions) &&
					(rand() % 4) ){
				//change the number of dimensions downwards
				hyperplane.setNumberOfDimensions( uiNumberOfDimensionsNew );
				uiNumberOfDimensions = uiNumberOfDimensionsNew;
				bDimensionalityChanged = true;
			}
			
		}//else set new base same dimensions
		vector< double > vecBaseNew( uiNumberOfDimensions, 0.0 );
		for ( unsigned int uiActualDimension = 0; 
				uiActualDimension < uiNumberOfDimensions; uiActualDimension++ ){
			
			if ( rand() % 4 ){
				//generate random double number
				vecBaseNew[ uiActualDimension ] = (((double)rand()) * ((double)rand()) -
					(256.0 * 256.0 * 256.0 * 256.0)) / ((double)(rand() + 1));
			}else{//generate random integer number
				vecBaseNew[ uiActualDimension ] = rand() - (256 * 256);
			}
		}
		cout<<"new base vector vecBaseNew = ";
		printVector( cout, vecBaseNew );
		vecBaseCorrect = vecBaseNew;
		
		if ( uiNumberOfDimensionsNew != uiNumberOfDimensions ){
			vecBaseCorrect.resize( uiNumberOfDimensions, 0.0 );
		}
		if ( bDimensionalityChanged ){
			/*set new dimensions vor the correct vectors
			-> resize the direction vector dimensions*/
			for ( unsigned int uiActualDirection = 0;
					uiActualDirection < vecDirectionsCorrect.size(); uiActualDirection++ ){
				
				vecDirectionsCorrect[ uiActualDirection ].resize( uiNumberOfDimensions, 0.0 );
			}
		}
		
		cout<<"hyperplane.setBase( vecBaseNew );"<<endl;
		hyperplane.setBase( vecBaseNew );
		
		//check the base vector
		//check the getBase() methode from cHyperplane
		cout<<"testBase = hyperplane.getBase();"<<endl;
		vector< double > testBase = hyperplane.getBase();
		//check with compare vectors with double range comparrison
		if ( compareVectorDouble( vecBaseCorrect, testBase ) ){
		
			cout<<"The hyperplane has correct base vector. "<<endl;
		}else{
			cerr<<"Error: The hyperplane has not the correct base vector (dim="<<
				testBase.size() <<")."<<endl;
			cerr<<"Base given back: ";
			printVector( cerr , testBase );
			cerr<<"Correct base:    ";
			printVector( cerr , vecBaseCorrect );
			iReturn++;
		}
		
		//check the getNumberOfDimensions() methode from cHyperplane
		if ( hyperplane.getNumberOfDimensions() == uiNumberOfDimensions ){
		
			cout<<"The hyperplane is correctly for "<<
				hyperplane.getNumberOfDimensions()<<" dimensions. "<<endl;
		}else{
			cerr<<"Error: The hyperplane is for "<<hyperplane.getNumberOfDirections()<<
				" dimensions, but should be for "<<uiNumberOfDimensions<<" ."<<endl;
			iReturn++;
		}
		//check the getNumberOfDirections() methode from cHyperplane
		if ( hyperplane.getNumberOfDirections() == 2 ){
		
			cout<<"The hyperplane has correctly "<<
				hyperplane.getNumberOfDirections()<<" direction vectors. "<<endl;
		}else{
			cerr<<"Error: The hyperplane has "<<hyperplane.getNumberOfDirections()<<
				" direction vectors, but should have 2 ."<<endl;
			iReturn++;
		}
		//check the direction vectors
		//check the getDirections() methode from cHyperplane
		cout<<"testDirections = hyperplane.getDirections();"<<endl;
		vector< vector< double > > testDirections = hyperplane.getDirections();
		if ( vecDirectionsCorrect == testDirections ){
		
			cout<<"The hyperplane has the correct direction vectors. "<<endl;
		}else{
			cerr<<"Error: The hyperplane has not the correct direction vectors."<<endl;
			iReturn++;
		}
	}
	
	return iReturn;
}


/**
 * This function tests the direction vector methods of the cHyperplane class.
 *
 * methods tested:
 * 	- vector< tFactors > getDirection( const unsigned int uiDirection ) const;
 * 	- vector< vector< tFactors > > getDirections() const;
 * 	- unsigned int getNumberOfDirections() const;
 * 	- bool addDirection( const vector< tFactors > & vecInDirection );
 * 	- unsigned int addDirections( vector< vector< tFactors > > vecInDirections );
 * 	- bool deleteDirection( unsigned int uiDirection );
 * 	- unsigned int getNumberOfDimensions() const;
 * 	- unsigned int setNumberOfDimensions( unsigned int uiDimensionality );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testDirections( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setting random new bases for hyperplane"<<endl;
	
	vector< double > vecBaseCorrect( 2, 0.0 );
	
	vector< vector< double > > vecDirectionsCorrect;
	vector< double > vecDirection1( 2, 0.0 );
	vecDirection1[ 0 ] = 1;
	vecDirectionsCorrect.push_back( vecDirection1 );
	vector< double > vecDirection2( 2, 0.0 );
	vecDirection2[ 1 ] = 1;
	vecDirectionsCorrect.push_back( vecDirection2 );

	cout<<"cHyperplane< double > hyperplane( vecBaseCorrect, vecDirectionsCorrect );"<<endl;
	cHyperplane< double > hyperplane( vecBaseCorrect, vecDirectionsCorrect );
	
	unsigned int uiNumberOfDimensions = 2;
	unsigned int uiNumberOfDirections = 2;
	const vector< double > vecEmpty;
	
	for ( unsigned int uiIteration = 0; uiIteration < MAX_ITERATION * 8; uiIteration++ ){
		
		if ( rand() % ( uiNumberOfDirections + 1) ){
			//delete direction vectors
			unsigned int uiDirectionToDelete =
				rand() % (uiNumberOfDirections + 2);
			
			cout<<"hyperplane.deleteDirection( uiDirectionToDelete );"<<endl;
			bool bDirectionDeleted = hyperplane.deleteDirection( uiDirectionToDelete );
			
			if ( ( 0 < uiDirectionToDelete ) &&
					( uiDirectionToDelete <= uiNumberOfDirections ) ){
				//an direction was deleted
				
				if ( ! bDirectionDeleted ){
					cerr<<"Error: An direction was not deleted, but should be."<<endl;
					iReturn++;
				}
				vector< vector< double > >::iterator itActualDirection =
					vecDirectionsCorrect.begin();
				while ( (1 < uiDirectionToDelete) &&
						( itActualDirection != vecDirectionsCorrect.end() ) ){
					itActualDirection++;
					uiDirectionToDelete--;
				}
				if ( itActualDirection != vecDirectionsCorrect.end() ){
					vecDirectionsCorrect.erase( itActualDirection );
					uiNumberOfDirections--;
				}
			}else{//direction shouldn't be deleted
				if ( bDirectionDeleted ){
					cerr<<"Error: An direction was deleted, but should not be."<<endl;
					iReturn++;
				}

			}
		}else if ( rand() % 4 ){
			//add new direction vector
			cout<<endl<<"Generating the new direction vector:"<<endl;
			unsigned int uiNumberOfDimensionsNew = uiNumberOfDimensions;
			bool bDimensionalityIncreased = false;
			bool bDimensionalityDecreased = false;
			if ( rand() % 16 == 0 ){
				//set new base more and less dimensions
				uiNumberOfDimensionsNew = (rand() % (rand() % 64 + 1) );
				cout<<"Changing dimensionality from "<<uiNumberOfDimensions<<
					" to "<<uiNumberOfDimensionsNew<<endl;
				
				if ( uiNumberOfDimensions < uiNumberOfDimensionsNew ){
					//increase the number of dimensions
					bDimensionalityIncreased = true;
				}else if ( (uiNumberOfDimensionsNew < uiNumberOfDimensions) &&
						(rand() % 4) ){
					//change the number of dimensions downwards
					cout<<"Changing hyperplane dimensions to "<<uiNumberOfDimensionsNew<<endl;
					hyperplane.setNumberOfDimensions( uiNumberOfDimensionsNew );
					bDimensionalityDecreased = true;
				}
			}//else set new base same dimensions
			vector< double > vecDirectionNew( uiNumberOfDimensionsNew, 0.0 );
			bool bCanAddDirection = false;
			if ( rand() % 32 ){
				for ( unsigned int uiActualDimension = 0; 
						uiActualDimension < uiNumberOfDimensionsNew; uiActualDimension++ ){
					
					if ( rand() % 4 ){
						//generate random double number
						vecDirectionNew[ uiActualDimension ] = (((double)rand()) * ((double)rand()) -
							(256.0 * 256.0 * 256.0 * 256.0)) / ((double)(rand() + 1));
					}else{//generate random integer number
						vecDirectionNew[ uiActualDimension ] = rand() - (256 * 256);
					}
					if ( vecDirectionNew[ uiActualDimension ] != 0.0 ){
						bCanAddDirection = true;
					}
				}
			}//else try to add direction with yust 0
			cout<<"new direction vector vecDirectionNew = ";
			printVector( cout, vecDirectionNew );
			
			if ( (bDimensionalityIncreased && bCanAddDirection) || bDimensionalityDecreased ){
				
				uiNumberOfDimensions = uiNumberOfDimensionsNew;
				
				vecBaseCorrect.resize( uiNumberOfDimensions, 0.0 );
				
				/*set new dimensions vor the correct vectors
				-> resize the direction vector dimensions*/
				for ( unsigned int uiActualDirection = 0;
						uiActualDirection < vecDirectionsCorrect.size(); uiActualDirection++ ){
					
					vecDirectionsCorrect[ uiActualDirection ].resize( uiNumberOfDimensions, 0.0 );
				}
			}
			cout<<"hyperplane.addDirection( vecDirectionNew );"<<endl;
			bool bDirectionAdded = hyperplane.addDirection( vecDirectionNew );
			
			if ( bCanAddDirection ){
				if ( uiNumberOfDimensionsNew < uiNumberOfDimensions ){
					//enlarge correct direction vector to the hyperplane number of dimensions
					vecDirectionNew.resize( uiNumberOfDimensions, 0.0 );
				}
				vecDirectionsCorrect.push_back( vecDirectionNew );
				uiNumberOfDirections++;
			}
			
			if ( bDirectionAdded == bCanAddDirection ){
				cout<<"The direction vector was correctly "<<
					(bDirectionAdded?"added":"not added")<<". "<<endl;
			}else{
				cerr<<"Error: The direction vector was "<<
					(bDirectionAdded?"added":"not added")<<" but should be "<<
					(bCanAddDirection?"added":"not added")<<"."<<endl;
				iReturn++;
			}
		}else{
			//add new direction vectors
			unsigned int uiDirectionsToAdd = rand() % ((rand() % 256) + 1);
			vector< vector< double > > vecDirectionsToAdd;
			unsigned int uiDirectionsThatCanBeAdded = 0;
			vector< vector< double > > vecDirectionsThatCanBeAdded;
			bool bDimensionalityChanged = false;
			unsigned int uiNewMaxDimension = 0;
			unsigned int uiNewMinDimension = uiNumberOfDimensions;
			
			cout<<endl<<"Generating the new direction vectors:"<<endl;
			
			for( unsigned int uiActualDirection = 1;
					uiActualDirection <= uiDirectionsToAdd; uiActualDirection++ ){
				
				unsigned int uiNumberOfDimensionsNew = uiNumberOfDimensions;
				
				if ( rand() % ( 8 * uiDirectionsToAdd ) == 0 ){
					//set new base more and less dimensions
					uiNumberOfDimensionsNew = (rand() % (rand() % 64 + 1) );
					cout<<"Changing dimensionality from "<<uiNumberOfDimensions<<
						" to "<<uiNumberOfDimensionsNew<<endl;
					
					bDimensionalityChanged = true;
					/*if ( uiNumberOfDimensions < uiNumberOfDimensionsNew ){
						//increase the number of dimensions
						bDimensionalityChanged = true;
					}else */
					if ( (uiNumberOfDimensionsNew < uiNumberOfDimensions) &&
							(rand() % (4 * uiDirectionsToAdd)) ){
						//change the number of dimensions downwards
						cout<<"Reducing dimesnionality of the hyperplane to: "<<uiNumberOfDimensionsNew<<endl;
						uiNewMinDimension = uiNumberOfDimensionsNew;
					}
				}//else set new base same dimensions
				
				vector< double > vecDirectionNew( uiNumberOfDimensionsNew, 0.0 );
				bool bCanAddDirection = false;
				if ( rand() % 32 ){
					for ( unsigned int uiActualDimension = 0; 
							uiActualDimension < uiNumberOfDimensionsNew; uiActualDimension++ ){
						
						if ( rand() % 4 ){
							//generate random double number
							vecDirectionNew[ uiActualDimension ] = (((double)rand()) * ((double)rand()) -
								(256.0 * 256.0 * 256.0 * 256.0)) / ((double)( rand() + 1 ));
						}else{//generate random integer number
							vecDirectionNew[ uiActualDimension ] = rand() - (256 * 256);
						}
						if ( vecDirectionNew[ uiActualDimension ] != 0.0 ){
							bCanAddDirection = true;
						}
					}
				}//else try to add direction with yust 0
				cout<<"new direction "<<uiActualDirection<<"'th vector = ";
				printVector( cout, vecDirectionNew );
				
				if ( bCanAddDirection ){
					vecDirectionsThatCanBeAdded.push_back( vecDirectionNew );
					uiDirectionsThatCanBeAdded++;
					uiNewMaxDimension = std::max( uiNewMaxDimension, uiNumberOfDimensionsNew );
				}
				vecDirectionsToAdd.push_back( vecDirectionNew );
			}
			if ( bDimensionalityChanged && ( 0 < uiDirectionsThatCanBeAdded ) ){
				
				if ( uiNewMinDimension < uiNumberOfDimensions ){
					//reduce the dimensions of the hyperplane first
					cout<<"Reducing the dimensions for the hyperplane to: "<<uiNewMinDimension<<endl;
					hyperplane.setNumberOfDimensions( uiNewMinDimension );
					
					vecBaseCorrect.resize( uiNewMinDimension, 0.0 );
					/*set new dimensions vor the correct vectors
					-> resize the direction vector dimensions*/
					for ( unsigned int uiActualDirection = 0;
							uiActualDirection < vecDirectionsCorrect.size(); uiActualDirection++ ){
						
						vecDirectionsCorrect[ uiActualDirection ].resize( uiNewMinDimension, 0.0 );
					}
				}else{//min dimension dosn't changed
					uiNewMaxDimension = std::max( uiNewMaxDimension, uiNumberOfDimensions );
				}
				cout<<"Adapting correct dimensions to max: "<<uiNewMaxDimension<<endl;
				vecDirectionsCorrect.insert( vecDirectionsCorrect.end(),
					vecDirectionsThatCanBeAdded.begin(), vecDirectionsThatCanBeAdded.end() );
				uiNumberOfDirections += uiDirectionsThatCanBeAdded;
				
				uiNumberOfDimensions = uiNewMaxDimension;
				
				vecBaseCorrect.resize( uiNumberOfDimensions, 0.0 );
				/*set new dimensions vor the correct vectors
				-> resize the direction vector dimensions*/
				for ( unsigned int uiActualDirection = 0;
						uiActualDirection < vecDirectionsCorrect.size(); uiActualDirection++ ){
					
					vecDirectionsCorrect[ uiActualDirection ].resize( uiNumberOfDimensions, 0.0 );
				}
			}else{
				vecDirectionsCorrect.insert( vecDirectionsCorrect.end(),
					vecDirectionsThatCanBeAdded.begin(), vecDirectionsThatCanBeAdded.end() );
				uiNumberOfDirections += uiDirectionsThatCanBeAdded;
			}
			cout<<"hyperplane.addDirections( vecDirectionsToAdd );"<<endl;
			unsigned int uiDirectionsAdded = hyperplane.addDirections( vecDirectionsToAdd );
			
			if ( uiDirectionsThatCanBeAdded == uiDirectionsAdded ){
				cout<<"Ther wher correctly "<<uiDirectionsThatCanBeAdded<<" direction vectors was added. "<<endl;
			}else{
				cerr<<"Error: Ther wher "<<uiDirectionsAdded<< " direction vectors added, but it should be "<<
					uiDirectionsThatCanBeAdded<<". "<<endl;
				iReturn++;
			}
		}
		//check the direction vectors
		if ( vecDirectionsCorrect.size() < uiNumberOfDirections ){
			cerr<<"Error: Internal error vecDirectionsCorrect.size() < uiNumberOfDirections."<<endl;
			uiNumberOfDirections = vecDirectionsCorrect.size();
			iReturn++;
		}
		//check the getNumberOfDirections() methode from cHyperplane
		if ( hyperplane.getNumberOfDirections() == uiNumberOfDirections ){
		
			cout<<"The hyperplane has correctly "<<
				hyperplane.getNumberOfDirections()<<" direction vectors. "<<endl;
		}else{
			cerr<<"Error: The hyperplane has "<<hyperplane.getNumberOfDirections()<<
				" direction vectors, but should have "<<vecDirectionsCorrect.size()<<" ."<<endl;
			uiNumberOfDirections = hyperplane.getNumberOfDirections();
			iReturn++;
		}
		for ( unsigned int uiActualDirection = 1;
				uiActualDirection <= uiNumberOfDirections; uiActualDirection++ ){
		
			//check the getDirection() methode from cHyperplane
			cout<<"direction = hyperplane.getDirection( uiActualDirection );"<<endl;
			vector< double > direction = hyperplane.getDirection( uiActualDirection );
			//check with compare vectors with double range comparrison
			if ( compareVectorDouble( vecDirectionsCorrect[ uiActualDirection - 1 ], direction ) ){
			
				cout<<"The hyperplane has correct "<<uiActualDirection<<"'th direction vector. "<<endl;
			}else{
				cerr<<"Error: The hyperplane has not the correct "<<
					uiActualDirection<<"'th direction vector (dim="<<
					direction.size() <<")."<<endl;
				cerr<<"Direction given back: ";
				printVector( cerr , direction );
				cerr<<"Correct direction:    ";
				printVector( cerr , vecDirectionsCorrect[ uiActualDirection - 1 ] );
				iReturn++;
			}
		}
		//check the getDirection() methode bounderies
		cout<<"direction0 = hyperplane.getDirection( 0 );"<<endl;
		vector< double > direction0 = hyperplane.getDirection( 0 );
		//check with compare vectors with double range comparrison
		if ( compareVectorDouble( vecEmpty, direction0 ) ){
		
			cout<<"The hyperplane gives back correctly an empty vector for the 0'th direction. "<<endl;
		}else{
			cerr<<"Error: The hyperplane gives back correctly an non empty vector for the 0'th direction. "<<endl;
			cerr<<"Direction given back: ";
			printVector( cerr , direction0 );
			iReturn++;
		}
		cout<<"directionLast = hyperplane.getDirection( "<<uiNumberOfDirections + 1<<" );"<<endl;
		vector< double > directionLast = hyperplane.getDirection( uiNumberOfDirections + 1 );
		//check with compare vectors with double range comparrison
		if ( compareVectorDouble( vecEmpty, directionLast ) ){
		
			cout<<"The hyperplane gives back correctly an empty vector for the 0'th direction. "<<endl;
		}else{
			cerr<<"Error: The hyperplane gives back correctly an non empty vector for the 0'th direction. "<<endl;
			cerr<<"Direction given back: ";
			printVector( cerr , directionLast );
			iReturn++;
		}
		
		//check the getDirections() methode from cHyperplane
		cout<<"testDirections = hyperplane.getDirections();"<<endl;
		vector< vector< double > > testDirections = hyperplane.getDirections();
		if ( compareVectorVectorDouble( vecDirectionsCorrect, testDirections ) ){
		
			cout<<"The hyperplane has the correct direction vectors. "<<endl;
		}else{
			cerr<<"Error: The hyperplane has not the correct direction vectors."<<endl;
			vecDirectionsCorrect = testDirections;//actualisize the directions
			iReturn++;
		}
		//check the getNumberOfDimensions() methode from cHyperplane
		if ( hyperplane.getNumberOfDimensions() == uiNumberOfDimensions ){
		
			cout<<"The hyperplane is correctly for "<<
				hyperplane.getNumberOfDimensions()<<" dimensions. "<<endl;
		}else{
			cerr<<"Error: The hyperplane is for "<<hyperplane.getNumberOfDirections()<<
				" dimensions, but should be for "<<uiNumberOfDimensions<<" ."<<endl;
			iReturn++;
		}
		
		//check the base vector
		//check the getBase() methode from cHyperplane
		cout<<"testBase = hyperplane.getBase();"<<endl;
		vector< double > testBase = hyperplane.getBase();
		//check with compare vectors with double range comparrison
		if ( compareVectorDouble( vecBaseCorrect, testBase ) ){
		
			cout<<"The hyperplane has correct base vector. "<<endl;
		}else{
			cerr<<"Error: The hyperplane has not the correct base vector (dim="<<
				testBase.size() <<")."<<endl;
			cerr<<"Base given back: ";
			printVector( cerr , testBase );
			cerr<<"Correct base:    ";
			printVector( cerr , vecBaseCorrect );
			iReturn++;
		}
	}
	
	return iReturn;
}







/**
 * This function tests the dimensions methods of the cHyperplane class.
 *
 * methods tested:
 * 	- unsigned int getNumberOfDimensions() const;
 * 	- unsigned int setNumberOfDimensions( unsigned int uiDimensionality );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testDimensions( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setting random new number of dimensions for hyperplane"<<endl;
	
	vector< double > vecBase( 4, 0.0 );
	
	vector< vector< double > > vecDirections;{
		vector< double > vecDirection1( 4, 0.0 );
		vecDirection1[ 0 ] = 1.0;
		vecDirections.push_back( vecDirection1 );
		vecDirection1[ 1 ] = 1.0;
		vecDirections.push_back( vecDirection1 );
		vecDirection1[ 2 ] = 1.0;
		vecDirections.push_back( vecDirection1 );
	}
	cout<<"cHyperplane< double > hyperplane( vecBase, vecDirections );"<<endl;
	cHyperplane< double > hyperplane( vecBase, vecDirections );
	
	unsigned int uiNumberOfDimensions = 4;
	unsigned int uiNumberOfDirections = 3;
	
	for ( unsigned int uiIteration = 0; uiIteration < (MAX_ITERATION / 8 + 1); uiIteration++ ){
		
		//set new base more and less dimensions
		const unsigned int uiNumberOfDimensionsNew = (rand() % (rand() % 64 + 1) );
		cout<<"Changing dimensionality from "<<uiNumberOfDimensions<<
			" to "<<uiNumberOfDimensionsNew<<endl;

		cout<<"hyperplane.setNumberOfDimensions( uiNumberOfDimensionsNew );"<<endl;
		unsigned int uiRetNumberOfDimensions =
			hyperplane.setNumberOfDimensions( uiNumberOfDimensionsNew );
		uiNumberOfDimensions = uiRetNumberOfDimensions;
		
		if ( uiRetNumberOfDimensions != uiNumberOfDimensionsNew ){
			
			cerr<<"Error: The number of dimensions should be set to "<<
				uiNumberOfDimensionsNew<<", but was set to "<<uiRetNumberOfDimensions<<" ."<<endl;
			iReturn++;
		}
	//check the hyperplane

		//check the getNumberOfDimensions() methode from cHyperplane
		if ( hyperplane.getNumberOfDimensions() == uiNumberOfDimensions ){
		
			cout<<"The hyperplane is correctly for "<<
				hyperplane.getNumberOfDimensions()<<" dimensions. "<<endl;
		}else{
			cerr<<"Error: The hyperplane is for "<<hyperplane.getNumberOfDirections()<<
				" dimensions, but should be for "<<uiNumberOfDimensions<<" ."<<endl;
			iReturn++;
		}

		//check the getNumberOfDirections() methode from cHyperplane
		if ( hyperplane.getNumberOfDirections() != uiNumberOfDirections ){
			cerr<<"Error: The hyperplane has "<<hyperplane.getNumberOfDirections()<<
				" direction vectors, but should have "<<uiNumberOfDirections<<" ."<<endl;
			uiNumberOfDirections = hyperplane.getNumberOfDirections();
			iReturn++;
		}
		//check the hyperplane vectors
		//check the getBase() methode from cHyperplane
		const vector< double > testBase = hyperplane.getBase();
		//check with compare vectors with double range comparrison
		if ( testBase.size() != uiNumberOfDimensions ){
			cerr<<"Error: The hyperplane has not the correct base vector number of dimensions, it is "<<
				testBase.size()<<", but should be "<<uiNumberOfDimensions<<" ."<<endl;
			iReturn++;
		}
		for ( unsigned int uiActualDirection = 1;
				uiActualDirection <= uiNumberOfDirections; uiActualDirection++ ){
		
			//check the getDirection() methode from cHyperplane
			const vector< double > vecDirectionRet = hyperplane.getDirection( uiActualDirection );
			//check with compare vectors with double range comparrison
			if ( vecDirectionRet.size() != uiNumberOfDimensions ){
				cerr<<"Error: The hyperplane has not the correct "<<
					uiActualDirection<<"'th direction vector number of dimensions, it is "<<
					vecDirectionRet.size()<<", but should be "<<uiNumberOfDimensions<<" ."<<endl;
				iReturn++;
			}
		}
	}
	
	return iReturn;
}



/**
 * This function tests the equal() method of two given hyperplanes, which are
 * equal.
 *
 * @param hyperplane1 the first hyperplane to compare
 * @param szNameHyperplane1 the name of the first hyperplane to compare
 * @param hyperplane2 the secound hyperplane to compare to
 * @param szNameHyperplane2 the name of the secound hyperplane to compare
 * @return the number of errors occured in the test
 */
template <class tFactors >
int testCompareTwoEqualHyperplanes( const cHyperplane<tFactors> &hyperplane1, const string &szNameHyperplane1,
	const cHyperplane<tFactors> &hyperplane2, const string &szNameHyperplane2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<"Comparing the "<<szNameHyperplane1<<" and "<<szNameHyperplane2<<" with equal. "<<endl;
	if ( ! hyperplane1.equal( hyperplane2 ) ){
		cerr<<"Error: The "<<szNameHyperplane1<<" is not equal to "<<
			szNameHyperplane2<<"."<<endl;
		iReturn++;
	}
	if ( ! hyperplane2.equal( hyperplane1 ) ){
		cerr<<"Error: The "<<szNameHyperplane2<<" is not equal to "<<
			szNameHyperplane1<<"."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This function tests the equal() method of two given hyperplanes, which are
 * not equal.
 *
 * @param hyperplane1 the first hyperplane to compare
 * @param szNameHyperplane1 the name of the first hyperplane to compare
 * @param hyperplane2 the secound hyperplane to compare to
 * @param szNameHyperplane2 the name of the secound hyperplane to compare
 * @return the number of errors occured in the test
 */
template <class tFactors >
int testCompareTwoNotEqualHyperplanes( const cHyperplane<tFactors> &hyperplane1, const string &szNameHyperplane1,
	const cHyperplane<tFactors> &hyperplane2, const string &szNameHyperplane2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<"Comparing the "<<szNameHyperplane1<<" and "<<szNameHyperplane2<<" with not equal. "<<endl;
	if ( hyperplane1.equal( hyperplane2 ) ){
		cerr<<"Error: The "<<szNameHyperplane1<<" is equal to "<<
			szNameHyperplane2<<"."<<endl;
		iReturn++;
	}
	if ( hyperplane2.equal( hyperplane1 ) ){
		cerr<<"Error: The "<<szNameHyperplane2<<" is equal to "<<
			szNameHyperplane1<<"."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This function tests the equal method of the cHyperplane class.
 *
 * methods tested:
 * 	- bool equal( const cHyperplane< tFactors > & hyperplane ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testEqual( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the equal method hyperplanes"<<endl<<endl;

	cout<<"vector< double > vecEmptyBase;"<<endl;
	vector< double > vecEmptyBase;
	cout<<"vector< vector< double > > vecEmptyDirections;"<<endl;
	vector< vector< double > > vecEmptyDirections;
	cout<<"cHyperplane< double > emptyHyperplane1( vecEmptyBase, vecEmptyDirections );"<<endl<<endl;
	cHyperplane< double > emptyHyperplane1( vecEmptyBase, vecEmptyDirections );
	
	
	cout<<"vector< double > vecBaseD1V0( 1, 0 );"<<endl;
	vector< double > vecBaseD1V0( 1, 0 );
	cout<<"cHyperplane< double > emptyHyperplaneD1( vecBaseD1V0, vecEmptyDirections );"<<endl<<endl;
	cHyperplane< double > emptyHyperplaneD1( vecBaseD1V0, vecEmptyDirections );
	
	cout<<"vector< double > vecBaseD1V1( 1, 1 );"<<endl;
	vector< double > vecBaseD1V1( 1, 1 );
	cout<<"cHyperplane< double > hyperplaneD1B1( vecBaseD1V1, vecEmptyDirections );"<<endl<<endl;
	cHyperplane< double > hyperplaneD1B1( vecBaseD1V1, vecEmptyDirections );
	
	
	//3D
	cout<<"vector< double > vecBaseD3V0( 3, 0 );"<<endl;
	vector< double > vecBaseD3V0( 3, 0 );
	cout<<"cHyperplane< double > hyperplaneD3B3V0( vecBaseD3V0, vecEmptyDirections );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3B3V0( vecBaseD3V0, vecEmptyDirections );
	
	
	cout<<"vector< double > vecBaseD3V1( 3, 1 );"<<endl;
	vector< double > vecBaseD3V1( 3, 1 );
	cout<<"cHyperplane< double > hyperplaneD3B3V1( vecBaseD3V1, vecEmptyDirections );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3B3V1( vecBaseD3V1, vecEmptyDirections );



	cout<<"vector< vector< double > > vecDirectionsD3DV0_1DV1_1;"<<endl;
	vector< vector< double > > vecDirectionsD3DV0_1DV1_1;
	cout<<"vector< double > vecDirectionD3V0_1( 3, 0.0 );"<<endl;
	vector< double > vecDirectionD3V0_1( 3, 0.0 );
	vecDirectionD3V0_1[ 0 ] = 1;
	vecDirectionsD3DV0_1DV1_1.push_back( vecDirectionD3V0_1 );
	cout<<"vector< double > vecDirectionD3V1_1( 3, 0.0 );"<<endl;
	vector< double > vecDirectionD3V1_1( 3, 0.0 );
	vecDirectionD3V1_1[ 1 ] = 1;
	vecDirectionsD3DV0_1DV1_1.push_back( vecDirectionD3V1_1 );
	cout<<"cHyperplane< double > hyperplaneD3B3V1D3DV0_1DV1_1( vecBaseD3V1, vecDirectionsD3DV0_1DV1_1 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3B3V1D3DV0_1DV1_1( vecBaseD3V1, vecDirectionsD3DV0_1DV1_1 );
	
	
	cout<<"vector< vector< double > > vecDirectionsD3DV1_1DV0_1;={{0, 1, 0}, {1, 0, 0}"<<endl;
	vector< vector< double > > vecDirectionsD3DV1_1DV0_1;
	vecDirectionsD3DV1_1DV0_1.push_back( vecDirectionD3V1_1 );
	vecDirectionsD3DV1_1DV0_1.push_back( vecDirectionD3V0_1 );
	cout<<"cHyperplane< double > hyperplaneD3B3V1DV1_1DV0_1( vecBaseD3V1, vecDirectionsD3DV1_1DV0_1 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3B3V1DV1_1DV0_1( vecBaseD3V1, vecDirectionsD3DV1_1DV0_1 );


	cout<<"vector< vector< double > > vecDirectionsD3DV0_3DV1_5p5;"<<endl;
	vector< vector< double > > vecDirectionsD3DV0_3DV1_5p5;
	cout<<"vector< double > vecDirectionD3V0_3( 3, 0.0 );={3, 0, 0}"<<endl;
	vector< double > vecDirectionD3V0_3( 3, 0.0 );
	vecDirectionD3V0_3[ 0 ] = 3;
	vecDirectionsD3DV0_3DV1_5p5.push_back( vecDirectionD3V0_3 );
	cout<<"vector< double > vecDirectionD3V1_5p5( 3, 0.0 );={0, 5.5, 0}"<<endl;
	vector< double > vecDirectionD3V1_5p5( 3, 0.0 );
	vecDirectionD3V1_5p5[ 1 ] = 5.5;
	vecDirectionsD3DV0_3DV1_5p5.push_back( vecDirectionD3V1_5p5 );
	cout<<"cHyperplane< double > hyperplaneD3B3V1DV0_3DV1_5p5( vecBaseD3V1, vecDirectionsD3DV0_3DV1_5p5 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3B3V1DV0_3DV1_5p5( vecBaseD3V1, vecDirectionsD3DV0_3DV1_5p5 );


	cout<<"vector< vector< double > > vecDirectionsD3DV0_3V1_7DV0_m1p1V1_5p5;"<<endl;
	vector< vector< double > > vecDirectionsD3DV0_3V1_7DV0_m1p1V1_5p5;
	cout<<"vector< double > vecDirectionD3V0_3V1_7( 3, 0.0 );={3, 7, 0.0}"<<endl;
	vector< double > vecDirectionD3V0_3V1_7( 3, 0.0 );
	vecDirectionD3V0_3V1_7[ 0 ] = 3;
	vecDirectionD3V0_3V1_7[ 1 ] = 7;
	vecDirectionsD3DV0_3V1_7DV0_m1p1V1_5p5.push_back( vecDirectionD3V0_3V1_7 );
	cout<<"vector< double > vecDirectionD3V0_m1p1V1_5p5( 3, 0.0 );={-1.1, 5.5, 0.0}"<<endl;
	vector< double > vecDirectionD3V0_m1p1V1_5p5( 3, 0.0 );
	vecDirectionD3V0_m1p1V1_5p5[ 0 ] = -1.1;
	vecDirectionD3V0_m1p1V1_5p5[ 1 ] = 5.5;
	vecDirectionsD3DV0_3V1_7DV0_m1p1V1_5p5.push_back( vecDirectionD3V0_m1p1V1_5p5 );
	cout<<"cHyperplane< double > hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5( vecBaseD3V1, vecDirectionsD3DV0_3V1_7DV0_m1p1V1_5p5 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5( vecBaseD3V1, vecDirectionsD3DV0_3V1_7DV0_m1p1V1_5p5 );


	cout<<"vector< vector< double > > vecDirectionsD3DV0_1DV0_1V1_1DV1_1;={{1,0,0}{1,1,0}{0,1,0}}"<<endl;
	vector< vector< double > > vecDirectionsD3DV0_1DV0_1V1_1DV1_1;
	vecDirectionsD3DV0_1DV0_1V1_1DV1_1.push_back( vecDirectionD3V0_1 );
	cout<<"vector< double > vecDirectionD3V0_1V1_1( 3, 0.0 );"<<endl;
	vector< double > vecDirectionD3V0_1V1_1( 3, 0.0 );
	vecDirectionD3V0_1V1_1[ 0 ] = 1;
	vecDirectionD3V0_1V1_1[ 1 ] = 1;
	vecDirectionsD3DV0_1DV0_1V1_1DV1_1.push_back( vecDirectionD3V0_1V1_1 );
	vecDirectionsD3DV0_1DV0_1V1_1DV1_1.push_back( vecDirectionD3V1_1 );
	cout<<"cHyperplane< double > hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1( vecBaseD3V1, vecDirectionsD3DV0_1DV0_1V1_1DV1_1 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1( vecBaseD3V1, vecDirectionsD3DV0_1DV0_1V1_1DV1_1 );


	cout<<"vector< double > vecBaseD3V1V0_2( 3, 1 );"<<endl;
	vector< double > vecBaseD3V1V0_2( 3, 1 );
	vecBaseD3V1V0_2[ 0 ] = 2;
	cout<<"cHyperplane< double > hyperplaneD3V1V0_2( vecBaseD3V1V0_2, vecDirectionsD3DV0_1DV1_1 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3V1V0_2( vecBaseD3V1V0_2, vecDirectionsD3DV0_1DV1_1 );


	cout<<"vector< double > vecBaseD3V1V1_3p3( 3, 1 );"<<endl;
	vector< double > vecBaseD3V1V1_3p3( 3, 1 );
	vecBaseD3V1V1_3p3[ 1 ] = 3.3;
	cout<<"cHyperplane< double > hyperplaneD3V1V1_3p3( vecBaseD3V1V1_3p3, vecDirectionsD3DV0_1DV1_1 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3V1V1_3p3( vecBaseD3V1V1_3p3, vecDirectionsD3DV0_1DV1_1 );
	
	//not equal to hyperplaneD3B3V1 different base
	cout<<"vector< double > vecBaseD3V1V2_3p3( 3, 1 );"<<endl;
	vector< double > vecBaseD3V1V2_3p3( 3, 1 );
	vecBaseD3V1V2_3p3[ 2 ] = 3.3;
	cout<<"cHyperplane< double > hyperplaneD3V1V2_3p3( vecBaseD3V1V2_3p3, vecDirectionsD3DV0_1DV1_1 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3V1V2_3p3( vecBaseD3V1V2_3p3, vecDirectionsD3DV0_1DV1_1 );
	
	//not equal to hyperplaneD3B3V1
	cout<<"vector< double > vecBaseD3V1V2_2( 3, 1 );={1, 1, 2}"<<endl;
	vector< double > vecBaseD3V1V2_2( 3, 1 );
	vecBaseD3V1V2_2[ 2 ] = 2;
	cout<<"cHyperplane< double > hyperplaneD3V1V2_2( vecBaseD3V1V2_2, vecDirectionsD3DV0_1DV1_1 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3V1V2_2( vecBaseD3V1V2_2, vecDirectionsD3DV0_1DV1_1 );
	
	//not equal to hyperplaneD3B3V1
	cout<<"vector< vector< double > > vecDirectionsD3DV0_1V1_1DV0_3V1_3;={{1,1,0}{3,3,0}}"<<endl;
	vector< vector< double > > vecDirectionsD3DV0_1V1_1DV0_3V1_3;
	vecDirectionsD3DV0_1V1_1DV0_3V1_3.push_back( vecDirectionD3V0_1V1_1 );
	cout<<"vector< double > vecDirectionD3V0_3V1_3( 3, 0.0 );={3, 3, 0}"<<endl;
	vector< double > vecDirectionD3V0_3V1_3( 3, 0.0 );
	vecDirectionD3V0_3V1_3[ 0 ] = 3;
	vecDirectionD3V0_3V1_3[ 1 ] = 3;
	vecDirectionsD3DV0_1V1_1DV0_3V1_3.push_back( vecDirectionD3V0_3V1_3 );
	cout<<"cHyperplane< double > hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3( vecBaseD3V1, vecDirectionsD3DV0_1V1_1DV0_3V1_3 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3( vecBaseD3V1, vecDirectionsD3DV0_1V1_1DV0_3V1_3 );

	
	cout<<endl<<"Starting comparisson: "<<endl;
	//compare with emptyHyperplane1
	cHyperplane<double> *actualHyperplane = &emptyHyperplane1;
	string szActualHyperplaneName = "emptyHyperplane1";
	cout<<endl<<"Compare with: "<<szActualHyperplaneName<<endl;
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplane1, "emptyHyperplane1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplaneD1, "emptyHyperplaneD1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD1B1, "hyperplaneD1B1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V0, "hyperplaneD3B3V0" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1, "hyperplaneD3B3V1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1D3DV0_1DV1_1, "hyperplaneD3B3V1D3DV0_1DV1_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV1_1DV0_1, "hyperplaneD3B3V1DV1_1DV0_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3DV1_5p5, "hyperplaneD3B3V1DV0_3DV1_5p5" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5, "hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1, "hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_2, "hyperplaneD3V1V2_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V0_2, "hyperplaneD3V1V0_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V1_3p3, "hyperplaneD3V1V1_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_3p3, "hyperplaneD3V1V2_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_2, "hyperplaneD3V1V2_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3, "hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3" );
	
	//compare with emptyHyperplaneD1
	actualHyperplane = &emptyHyperplaneD1;
	szActualHyperplaneName = "emptyHyperplaneD1";
	cout<<endl<<"Compare with: "<<szActualHyperplaneName<<endl;
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplane1, "emptyHyperplane1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplaneD1, "emptyHyperplaneD1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD1B1, "hyperplaneD1B1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V0, "hyperplaneD3B3V0" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1, "hyperplaneD3B3V1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1D3DV0_1DV1_1, "hyperplaneD3B3V1D3DV0_1DV1_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV1_1DV0_1, "hyperplaneD3B3V1DV1_1DV0_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3DV1_5p5, "hyperplaneD3B3V1DV0_3DV1_5p5" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5, "hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1, "hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_2, "hyperplaneD3V1V2_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V0_2, "hyperplaneD3V1V0_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V1_3p3, "hyperplaneD3V1V1_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_3p3, "hyperplaneD3V1V2_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_2, "hyperplaneD3V1V2_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3, "hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3" );

	//compare with hyperplaneD1B1
	actualHyperplane = &hyperplaneD1B1;
	szActualHyperplaneName = "hyperplaneD1B1";
	cout<<endl<<"Compare with: "<<szActualHyperplaneName<<endl;
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplane1, "emptyHyperplane1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplaneD1, "emptyHyperplaneD1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD1B1, "hyperplaneD1B1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V0, "hyperplaneD3B3V0" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1, "hyperplaneD3B3V1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1D3DV0_1DV1_1, "hyperplaneD3B3V1D3DV0_1DV1_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV1_1DV0_1, "hyperplaneD3B3V1DV1_1DV0_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3DV1_5p5, "hyperplaneD3B3V1DV0_3DV1_5p5" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5, "hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1, "hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_2, "hyperplaneD3V1V2_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V0_2, "hyperplaneD3V1V0_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V1_3p3, "hyperplaneD3V1V1_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_3p3, "hyperplaneD3V1V2_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_2, "hyperplaneD3V1V2_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3, "hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3" );

	//compare with hyperplaneD3B3V0
	actualHyperplane = &hyperplaneD3B3V0;
	szActualHyperplaneName = "hyperplaneD3B3V0";
	cout<<endl<<"Compare with: "<<szActualHyperplaneName<<endl;
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplane1, "emptyHyperplane1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplaneD1, "emptyHyperplaneD1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD1B1, "hyperplaneD1B1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V0, "hyperplaneD3B3V0" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1, "hyperplaneD3B3V1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1D3DV0_1DV1_1, "hyperplaneD3B3V1D3DV0_1DV1_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV1_1DV0_1, "hyperplaneD3B3V1DV1_1DV0_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3DV1_5p5, "hyperplaneD3B3V1DV0_3DV1_5p5" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5, "hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1, "hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_2, "hyperplaneD3V1V2_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V0_2, "hyperplaneD3V1V0_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V1_3p3, "hyperplaneD3V1V1_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_3p3, "hyperplaneD3V1V2_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_2, "hyperplaneD3V1V2_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3, "hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3" );

	//compare with hyperplaneD3B3V1
	actualHyperplane = &hyperplaneD3B3V1;
	szActualHyperplaneName = "hyperplaneD3B3V1";
	cout<<endl<<"Compare with: "<<szActualHyperplaneName<<endl;
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplane1, "emptyHyperplane1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplaneD1, "emptyHyperplaneD1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD1B1, "hyperplaneD1B1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V0, "hyperplaneD3B3V0" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1, "hyperplaneD3B3V1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1D3DV0_1DV1_1, "hyperplaneD3B3V1D3DV0_1DV1_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV1_1DV0_1, "hyperplaneD3B3V1DV1_1DV0_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3DV1_5p5, "hyperplaneD3B3V1DV0_3DV1_5p5" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5, "hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1, "hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_2, "hyperplaneD3V1V2_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V0_2, "hyperplaneD3V1V0_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V1_3p3, "hyperplaneD3V1V1_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_3p3, "hyperplaneD3V1V2_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_2, "hyperplaneD3V1V2_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3, "hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3" );

	//compare with hyperplaneD3B3V1D3DV0_1DV1_1
	actualHyperplane = &hyperplaneD3B3V1D3DV0_1DV1_1;
	szActualHyperplaneName = "hyperplaneD3B3V1D3DV0_1DV1_1";
	cout<<endl<<"Compare with: "<<szActualHyperplaneName<<endl;
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplane1, "emptyHyperplane1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplaneD1, "emptyHyperplaneD1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD1B1, "hyperplaneD1B1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V0, "hyperplaneD3B3V0" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1, "hyperplaneD3B3V1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1D3DV0_1DV1_1, "hyperplaneD3B3V1D3DV0_1DV1_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV1_1DV0_1, "hyperplaneD3B3V1DV1_1DV0_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3DV1_5p5, "hyperplaneD3B3V1DV0_3DV1_5p5" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5, "hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1, "hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V0_2, "hyperplaneD3V1V0_2" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V1_3p3, "hyperplaneD3V1V1_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_3p3, "hyperplaneD3V1V2_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_2, "hyperplaneD3V1V2_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3, "hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3" );

	//compare with hyperplaneD3B3V1DV1_1DV0_1
	actualHyperplane = &hyperplaneD3B3V1DV1_1DV0_1;
	szActualHyperplaneName = "hyperplaneD3B3V1DV1_1DV0_1";
	cout<<endl<<"Compare with: "<<szActualHyperplaneName<<endl;
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplane1, "emptyHyperplane1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplaneD1, "emptyHyperplaneD1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD1B1, "hyperplaneD1B1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V0, "hyperplaneD3B3V0" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1, "hyperplaneD3B3V1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1D3DV0_1DV1_1, "hyperplaneD3B3V1D3DV0_1DV1_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV1_1DV0_1, "hyperplaneD3B3V1DV1_1DV0_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3DV1_5p5, "hyperplaneD3B3V1DV0_3DV1_5p5" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5, "hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1, "hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V0_2, "hyperplaneD3V1V0_2" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V1_3p3, "hyperplaneD3V1V1_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_3p3, "hyperplaneD3V1V2_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_2, "hyperplaneD3V1V2_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3, "hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3" );

	//compare with hyperplaneD3B3V1DV0_3DV1_5p5
	actualHyperplane = &hyperplaneD3B3V1DV0_3DV1_5p5;
	szActualHyperplaneName = "hyperplaneD3B3V1DV0_3DV1_5p5";
	cout<<endl<<"Compare with: "<<szActualHyperplaneName<<endl;
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplane1, "emptyHyperplane1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplaneD1, "emptyHyperplaneD1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD1B1, "hyperplaneD1B1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V0, "hyperplaneD3B3V0" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1, "hyperplaneD3B3V1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1D3DV0_1DV1_1, "hyperplaneD3B3V1D3DV0_1DV1_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV1_1DV0_1, "hyperplaneD3B3V1DV1_1DV0_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3DV1_5p5, "hyperplaneD3B3V1DV0_3DV1_5p5" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5, "hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1, "hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V0_2, "hyperplaneD3V1V0_2" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V1_3p3, "hyperplaneD3V1V1_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_3p3, "hyperplaneD3V1V2_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_2, "hyperplaneD3V1V2_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3, "hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3" );

	//compare with hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5
	actualHyperplane = &hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5;
	szActualHyperplaneName = "hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5";
	cout<<endl<<"Compare with: "<<szActualHyperplaneName<<endl;
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplane1, "emptyHyperplane1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplaneD1, "emptyHyperplaneD1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD1B1, "hyperplaneD1B1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V0, "hyperplaneD3B3V0" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1, "hyperplaneD3B3V1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1D3DV0_1DV1_1, "hyperplaneD3B3V1D3DV0_1DV1_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV1_1DV0_1, "hyperplaneD3B3V1DV1_1DV0_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3DV1_5p5, "hyperplaneD3B3V1DV0_3DV1_5p5" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5, "hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1, "hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V0_2, "hyperplaneD3V1V0_2" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V1_3p3, "hyperplaneD3V1V1_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_3p3, "hyperplaneD3V1V2_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_2, "hyperplaneD3V1V2_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3, "hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3" );

	//compare with hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1
	actualHyperplane = &hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1;
	szActualHyperplaneName = "hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1";
	cout<<endl<<"Compare with: "<<szActualHyperplaneName<<endl;
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplane1, "emptyHyperplane1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplaneD1, "emptyHyperplaneD1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD1B1, "hyperplaneD1B1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V0, "hyperplaneD3B3V0" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1, "hyperplaneD3B3V1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1D3DV0_1DV1_1, "hyperplaneD3B3V1D3DV0_1DV1_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV1_1DV0_1, "hyperplaneD3B3V1DV1_1DV0_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3DV1_5p5, "hyperplaneD3B3V1DV0_3DV1_5p5" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5, "hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1, "hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V0_2, "hyperplaneD3V1V0_2" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V1_3p3, "hyperplaneD3V1V1_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_3p3, "hyperplaneD3V1V2_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_2, "hyperplaneD3V1V2_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3, "hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3" );

	//compare with hyperplaneD3V1V0_2
	actualHyperplane = &hyperplaneD3V1V0_2;
	szActualHyperplaneName = "hyperplaneD3V1V0_2";
	cout<<endl<<"Compare with: "<<szActualHyperplaneName<<endl;
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplane1, "emptyHyperplane1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplaneD1, "emptyHyperplaneD1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD1B1, "hyperplaneD1B1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V0, "hyperplaneD3B3V0" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1, "hyperplaneD3B3V1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1D3DV0_1DV1_1, "hyperplaneD3B3V1D3DV0_1DV1_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV1_1DV0_1, "hyperplaneD3B3V1DV1_1DV0_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3DV1_5p5, "hyperplaneD3B3V1DV0_3DV1_5p5" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5, "hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1, "hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V0_2, "hyperplaneD3V1V0_2" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V1_3p3, "hyperplaneD3V1V1_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_3p3, "hyperplaneD3V1V2_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_2, "hyperplaneD3V1V2_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3, "hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3" );

	//compare with hyperplaneD3V1V1_3p3
	actualHyperplane = &hyperplaneD3V1V1_3p3;
	szActualHyperplaneName = "hyperplaneD3V1V1_3p3";
	cout<<endl<<"Compare with: "<<szActualHyperplaneName<<endl;
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplane1, "emptyHyperplane1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplaneD1, "emptyHyperplaneD1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD1B1, "hyperplaneD1B1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V0, "hyperplaneD3B3V0" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1, "hyperplaneD3B3V1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1D3DV0_1DV1_1, "hyperplaneD3B3V1D3DV0_1DV1_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV1_1DV0_1, "hyperplaneD3B3V1DV1_1DV0_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3DV1_5p5, "hyperplaneD3B3V1DV0_3DV1_5p5" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5, "hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1, "hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V0_2, "hyperplaneD3V1V0_2" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V1_3p3, "hyperplaneD3V1V1_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_3p3, "hyperplaneD3V1V2_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_2, "hyperplaneD3V1V2_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3, "hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3" );

	//compare with hyperplaneD3V1V2_3p3
	actualHyperplane = &hyperplaneD3V1V2_3p3;
	szActualHyperplaneName = "hyperplaneD3V1V2_3p3";
	cout<<endl<<"Compare with: "<<szActualHyperplaneName<<endl;
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplane1, "emptyHyperplane1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplaneD1, "emptyHyperplaneD1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD1B1, "hyperplaneD1B1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V0, "hyperplaneD3B3V0" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1, "hyperplaneD3B3V1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1D3DV0_1DV1_1, "hyperplaneD3B3V1D3DV0_1DV1_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV1_1DV0_1, "hyperplaneD3B3V1DV1_1DV0_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3DV1_5p5, "hyperplaneD3B3V1DV0_3DV1_5p5" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5, "hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1, "hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V0_2, "hyperplaneD3V1V0_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V1_3p3, "hyperplaneD3V1V1_3p3" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_3p3, "hyperplaneD3V1V2_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_2, "hyperplaneD3V1V2_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3, "hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3" );

	//compare with hyperplaneD3V1V2_2
	actualHyperplane = &hyperplaneD3V1V2_2;
	szActualHyperplaneName = "hyperplaneD3V1V2_2";
	cout<<endl<<"Compare with: "<<szActualHyperplaneName<<endl;
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplane1, "emptyHyperplane1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplaneD1, "emptyHyperplaneD1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD1B1, "hyperplaneD1B1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V0, "hyperplaneD3B3V0" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1, "hyperplaneD3B3V1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1D3DV0_1DV1_1, "hyperplaneD3B3V1D3DV0_1DV1_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV1_1DV0_1, "hyperplaneD3B3V1DV1_1DV0_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3DV1_5p5, "hyperplaneD3B3V1DV0_3DV1_5p5" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5, "hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1, "hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V0_2, "hyperplaneD3V1V0_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V1_3p3, "hyperplaneD3V1V1_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_3p3, "hyperplaneD3V1V2_3p3" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_2, "hyperplaneD3V1V2_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3, "hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3" );

	//compare with hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3
	actualHyperplane = &hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3;
	szActualHyperplaneName = "hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3";
	cout<<endl<<"Compare with: "<<szActualHyperplaneName<<endl;
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplane1, "emptyHyperplane1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, emptyHyperplaneD1, "emptyHyperplaneD1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD1B1, "hyperplaneD1B1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V0, "hyperplaneD3B3V0" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1, "hyperplaneD3B3V1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1D3DV0_1DV1_1, "hyperplaneD3B3V1D3DV0_1DV1_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV1_1DV0_1, "hyperplaneD3B3V1DV1_1DV0_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3DV1_5p5, "hyperplaneD3B3V1DV0_3DV1_5p5" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5, "hyperplaneD3B3V1DV0_3V1_7DV0_m1p1V1_5p5" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1, "hyperplaneD3B3V1DV0_1DV0_1V1_1DV1_1" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V0_2, "hyperplaneD3V1V0_2" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V1_3p3, "hyperplaneD3V1V1_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_3p3, "hyperplaneD3V1V2_3p3" );
	iReturn += testCompareTwoNotEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3V1V2_2, "hyperplaneD3V1V2_2" );
	iReturn += testCompareTwoEqualHyperplanes( *actualHyperplane, szActualHyperplaneName, hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3, "hyperplaneD3B3V1DV0_1V1_1DV0_3V1_3" );
	

	return iReturn;
}



/**
 * This function tests the makeDirectionsIndependent() method of the cHyperplane class.
 *
 * methods tested:
 * 	- void makeDirectionsIndependent();
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testMakeDirectionsIndependent( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the makeDirectionsIndependent() method of hyperplanes"<<endl<<endl;
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the makeDirectionsIndependent() method of hyperplanes, on hyperplane with two independent directions"<<endl<<endl;
	
	cout<<"vector< vector< double > > vecDirectionsD3;={{1,0,0}{0,1,0}}"<<endl;
	vector< double > vecBaseD3V1( 3, 1 );
	
	vector< vector< double > > vecDirectionsD3;
	vector< double > vecDirectionD3( 3, 0.0 );
	vecDirectionD3[ 0 ] = 1;
	vecDirectionsD3.push_back( vecDirectionD3 );
	vecDirectionD3[ 0 ] = 0;
	vecDirectionD3[ 1 ] = 1;
	vecDirectionsD3.push_back( vecDirectionD3 );
	
	unsigned int uiNumberOfDimensions = 3;
	unsigned int uiNumberOfIndependentDirections = 2;
	
	cout<<"cHyperplane< double > hyperplaneD3( vecBaseD3V1, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3( vecBaseD3V1, vecDirectionsD3 );

	cout<<"hyperplaneD3.makeDirectionsIndependent();"<<endl<<endl;
	hyperplaneD3.makeDirectionsIndependent();
	
	//check the getNumberOfDirections() methode from cHyperplane
	if ( hyperplaneD3.getNumberOfDirections() == uiNumberOfIndependentDirections ){
	
		cout<<"The hyperplane has the correct number of direction vectors "<<
			uiNumberOfIndependentDirections<<" . "<<endl;
	}else{
		cerr<<"Error: The hyperplane has not the correct number of direction"<<
			" vectors, ther are "<<hyperplaneD3.getNumberOfDirections()<<
			", but should be "<<uiNumberOfIndependentDirections<<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfDimensions() methode from cHyperplane
	if ( hyperplaneD3.getNumberOfDimensions() == uiNumberOfDimensions ){
	
		cout<<"The hyperplane has the correct number of dimensions "<<
			uiNumberOfDimensions<<" . "<<endl;
	}else{
		cerr<<"Error: The hyperplane has not the correct number of dimensions"<<
			" vectors, ther are "<<hyperplaneD3.getNumberOfDimensions()<<
			", but should be "<<uiNumberOfDimensions<<" ."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the makeDirectionsIndependent() method of hyperplanes, on hyperplane with 3 dependent directions"<<endl<<endl;
	
	cout<<"vecDirectionsD3;={{3,7,0}{0,4,0}{6,0,0}}"<<endl;
	
	vecDirectionsD3.clear();
	vecDirectionD3[ 0 ] = 3;
	vecDirectionD3[ 1 ] = 7;
	vecDirectionD3[ 2 ] = 0;
	vecDirectionsD3.push_back( vecDirectionD3 );
	vecDirectionD3[ 0 ] = 0;
	vecDirectionD3[ 1 ] = 4;
	vecDirectionD3[ 2 ] = 0;
	vecDirectionsD3.push_back( vecDirectionD3 );
	vecDirectionD3[ 0 ] = 6;
	vecDirectionD3[ 1 ] = 0;
	vecDirectionD3[ 2 ] = 0;
	vecDirectionsD3.push_back( vecDirectionD3 );
	
	uiNumberOfDimensions = 3;
	uiNumberOfIndependentDirections = 2;
	
	cout<<"cHyperplane< double > hyperplane1D3( vecBaseD3V1, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > hyperplane1D3( vecBaseD3V1, vecDirectionsD3 );
	cHyperplane< double > * hyperplaneTest = &hyperplane1D3;
	
	cout<<"hyperplaneTest->makeDirectionsIndependent();"<<endl<<endl;
	hyperplaneTest->makeDirectionsIndependent();
	
	//check the getNumberOfDirections() methode from cHyperplane
	if ( hyperplaneTest->getNumberOfDirections() == uiNumberOfIndependentDirections ){
	
		cout<<"The hyperplane has the correct number of direction vectors "<<
			uiNumberOfIndependentDirections<<" . "<<endl;
	}else{
		cerr<<"Error: The hyperplane has not the correct number of direction"<<
			" vectors, ther are "<<hyperplaneTest->getNumberOfDirections()<<
			", but should be "<<uiNumberOfIndependentDirections<<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfDimensions() methode from cHyperplane
	if ( hyperplaneTest->getNumberOfDimensions() == uiNumberOfDimensions ){
	
		cout<<"The hyperplane has the correct number of dimensions "<<
			uiNumberOfDimensions<<" . "<<endl;
	}else{
		cerr<<"Error: The hyperplane has not the correct number of dimensions"<<
			" vectors, ther are "<<hyperplaneTest->getNumberOfDimensions()<<
			", but should be "<<uiNumberOfDimensions<<" ."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the makeDirectionsIndependent() method of hyperplanes, on hyperplane with 2 dependent directions"<<endl<<endl;
	
	cout<<"vecDirectionsD3;={{0,0,-1.2}{0,0,6.5}}"<<endl;
	
	vecDirectionsD3.clear();
	vecDirectionD3[ 0 ] = 0;
	vecDirectionD3[ 1 ] = 0;
	vecDirectionD3[ 2 ] = -1.2;
	vecDirectionsD3.push_back( vecDirectionD3 );
	vecDirectionD3[ 0 ] = 0;
	vecDirectionD3[ 1 ] = 0;
	vecDirectionD3[ 2 ] = 6.5;
	vecDirectionsD3.push_back( vecDirectionD3 );
	
	uiNumberOfIndependentDirections = 1;
	
	cout<<"cHyperplane< double > hyperplane2D3( vecBaseD3V1, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > hyperplane2D3( vecBaseD3V1, vecDirectionsD3 );
	hyperplaneTest = &hyperplane2D3;
	
	cout<<"hyperplaneTest->makeDirectionsIndependent();"<<endl<<endl;
	hyperplaneTest->makeDirectionsIndependent();
	
	//check the getNumberOfDirections() methode from cHyperplane
	if ( hyperplaneTest->getNumberOfDirections() == uiNumberOfIndependentDirections ){
	
		cout<<"The hyperplane has the correct number of direction vectors "<<
			uiNumberOfIndependentDirections<<" . "<<endl;
	}else{
		cerr<<"Error: The hyperplane has not the correct number of direction"<<
			" vectors, ther are "<<hyperplaneTest->getNumberOfDirections()<<
			", but should be "<<uiNumberOfIndependentDirections<<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfDimensions() methode from cHyperplane
	if ( hyperplaneTest->getNumberOfDimensions() == uiNumberOfDimensions ){
	
		cout<<"The hyperplane has the correct number of dimensions "<<
			uiNumberOfDimensions<<" . "<<endl;
	}else{
		cerr<<"Error: The hyperplane has not the correct number of dimensions"<<
			" vectors, ther are "<<hyperplaneTest->getNumberOfDimensions()<<
			", but should be "<<uiNumberOfDimensions<<" ."<<endl;
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the makeDirectionsIndependent() method of hyperplanes, on hyperplane with 2 independent directions"<<endl<<endl;
	
	cout<<"vecDirectionsD3;={{0,1,3}{0,5,4}}"<<endl;
	
	vecDirectionsD3.clear();
	vecDirectionD3[ 0 ] = 0;
	vecDirectionD3[ 1 ] = 1;
	vecDirectionD3[ 2 ] = 3;
	vecDirectionsD3.push_back( vecDirectionD3 );
	vecDirectionD3[ 0 ] = 0;
	vecDirectionD3[ 1 ] = 5;
	vecDirectionD3[ 2 ] = 4;
	vecDirectionsD3.push_back( vecDirectionD3 );
	
	uiNumberOfIndependentDirections = 2;
	
	cout<<"cHyperplane< double > hyperplane3D3( vecBaseD3V1, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > hyperplane3D3( vecBaseD3V1, vecDirectionsD3 );
	hyperplaneTest = &hyperplane3D3;
	
	cout<<"hyperplaneTest->makeDirectionsIndependent();"<<endl<<endl;
	hyperplaneTest->makeDirectionsIndependent();
	
	//check the getNumberOfDirections() methode from cHyperplane
	if ( hyperplaneTest->getNumberOfDirections() == uiNumberOfIndependentDirections ){
	
		cout<<"The hyperplane has the correct number of direction vectors "<<
			uiNumberOfIndependentDirections<<" . "<<endl;
	}else{
		cerr<<"Error: The hyperplane has not the correct number of direction"<<
			" vectors, ther are "<<hyperplaneTest->getNumberOfDirections()<<
			", but should be "<<uiNumberOfIndependentDirections<<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfDimensions() methode from cHyperplane
	if ( hyperplaneTest->getNumberOfDimensions() == uiNumberOfDimensions ){
	
		cout<<"The hyperplane has the correct number of dimensions "<<
			uiNumberOfDimensions<<" . "<<endl;
	}else{
		cerr<<"Error: The hyperplane has not the correct number of dimensions"<<
			" vectors, ther are "<<hyperplaneTest->getNumberOfDimensions()<<
			", but should be "<<uiNumberOfDimensions<<" ."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the makeDirectionsIndependent() method of hyperplanes, on hyperplane with 5 dependent (with 3 independent) directions and 5 dimensions"<<endl<<endl;
	
	vector< double > vecBaseD5V1( 5, -3.3 );
	
	cout<<"vector< vector< double > > vecDirectionsD5;={{3,2,1,0,7}{0,1,0,5,7}{7,0,3,12,6}{1,-3,1,17,-1}{1,-1,1,27,13}}"<<endl;
	vector< vector< double > > vecDirectionsD5;
	vector< double > vecDirectionD5( 5, 0.0 );
	vecDirectionD5[ 0 ] = 3;
	vecDirectionD5[ 1 ] = 2;
	vecDirectionD5[ 2 ] = 1;
	vecDirectionD5[ 3 ] = 0;
	vecDirectionD5[ 4 ] = 7;
	vecDirectionsD5.push_back( vecDirectionD5 );
	vecDirectionD5[ 0 ] = 0;
	vecDirectionD5[ 1 ] = 1;
	vecDirectionD5[ 2 ] = 0;
	vecDirectionD5[ 3 ] = 5;
	vecDirectionD5[ 4 ] = 7;
	vecDirectionsD5.push_back( vecDirectionD5 );
	vecDirectionD5[ 0 ] = 7;
	vecDirectionD5[ 1 ] = 0;
	vecDirectionD5[ 2 ] = 3;
	vecDirectionD5[ 3 ] = 12;
	vecDirectionD5[ 4 ] = 6;
	vecDirectionsD5.push_back( vecDirectionD5 );
	vecDirectionD5[ 0 ] = 1; //=3 * -2 + 0 + 7
	vecDirectionD5[ 1 ] = -3;//=2 * -2 + 1 + 0
	vecDirectionD5[ 2 ] = 1; //=1 * -2 + 0 + 3
	vecDirectionD5[ 3 ] = 17;//=0 * -2 + 5 + 12
	vecDirectionD5[ 4 ] = -1;//=7 * -2 + 7 + 6
	vecDirectionsD5.push_back( vecDirectionD5 );
	vecDirectionD5[ 0 ] = 1;
	vecDirectionD5[ 1 ] = -1;
	vecDirectionD5[ 2 ] = 1;
	vecDirectionD5[ 3 ] = 27;
	vecDirectionD5[ 4 ] = 13;
	vecDirectionsD5.push_back( vecDirectionD5 );
	
	uiNumberOfDimensions = 5;
	uiNumberOfIndependentDirections = 3;
	
	cout<<"cHyperplane< double > hyperplane1D5( vecBaseD5V1, vecDirectionsD5 );"<<endl<<endl;
	cHyperplane< double > hyperplane1D5( vecBaseD5V1, vecDirectionsD5 );
	hyperplaneTest = &hyperplane1D5;
	
	cout<<"hyperplaneTest->makeDirectionsIndependent();"<<endl<<endl;
	hyperplaneTest->makeDirectionsIndependent();
	
	//check the getNumberOfDirections() methode from cHyperplane
	if ( hyperplaneTest->getNumberOfDirections() == uiNumberOfIndependentDirections ){
	
		cout<<"The hyperplane has the correct number of direction vectors "<<
			uiNumberOfIndependentDirections<<" . "<<endl;
	}else{
		cerr<<"Error: The hyperplane has not the correct number of direction"<<
			" vectors, ther are "<<hyperplaneTest->getNumberOfDirections()<<
			", but should be "<<uiNumberOfIndependentDirections<<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfDimensions() methode from cHyperplane
	if ( hyperplaneTest->getNumberOfDimensions() == uiNumberOfDimensions ){
	
		cout<<"The hyperplane has the correct number of dimensions "<<
			uiNumberOfDimensions<<" . "<<endl;
	}else{
		cerr<<"Error: The hyperplane has not the correct number of dimensions"<<
			" vectors, ther are "<<hyperplaneTest->getNumberOfDimensions()<<
			", but should be "<<uiNumberOfDimensions<<" ."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * @return a random integer number betwean (256 * 128 - 1) and (-256 * 128)
 */
long randIntFactor(){
	
	return (rand() % (256 * 256)) - 256 * 128;
	/*
	return ((double)((rand() % (256 * 256)) - 256 * 128)) /
		((double)( (rand() % 256) + 1 ));*/
}

/**
 * This function tests the evalueIntersection() method of the cHyperplane class.
 *
 * methods tested:
 * 	- cHyperplane< tFactors > * evalueIntersection( const cHyperplane< tFactors > & hyperplane ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testIntersection( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<endl<<"Testing the evalueIntersection() method of the cHyperplane class"<<endl;
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing intersection of two equal points"<<endl;
	
	cout<<"vector< vector< double > > vecBaseD3( 3, 0);={-1,1,2}"<<endl;
	vector< double > vecBaseD3( 3, 0);
	vecBaseD3[ 0 ] = -1;
	vecBaseD3[ 1 ] = 1;
	vecBaseD3[ 2 ] = 2;
	
	cout<<"vector< vector< double > > vecDirectionsD3Empty;={}"<<endl;
	vector< vector< double > > vecDirectionsD3Empty;
	
	cout<<"cHyperplane< double > hyperplaneD3_1( vecBaseD3, vecDirectionsD3Empty );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3_1( vecBaseD3, vecDirectionsD3Empty );

	cout<<"cHyperplane< double > hyperplaneD3_2( vecBaseD3, vecDirectionsD3Empty );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3_2( vecBaseD3, vecDirectionsD3Empty );
	
	cout<<"pHyperplaneD3Inters = hyperplaneD3_1.evalueIntersection( hyperplaneD3_2 );"<<endl<<endl;
	cHyperplane< double > * pHyperplaneD3Inters = hyperplaneD3_1.evalueIntersection( hyperplaneD3_2 );
	
	if ( pHyperplaneD3Inters != NULL ){
		if ( hyperplaneD3_1.equal( *pHyperplaneD3Inters ) ){
		
			cout<<"The intersection of the hyperplanes is correctly equal to the hyperplanes. "<<endl;
		}else{
			cerr<<"Error: The intersection of the hyperplanes is not equal to the hyperplanes ."<<endl;
			cerr<<"Hyperplane 1:"<<endl;
			hyperplaneD3_1.print( cerr );
			cerr<<endl<<"Hyperplane 2:"<<endl;
			hyperplaneD3_2.print( cerr );
			cerr<<endl<<"Intersection:"<<endl;
			pHyperplaneD3Inters->print( cerr );
			cerr<<endl;
			iReturn++;
		}
		delete pHyperplaneD3Inters;
	}else{
		cerr<<"Error: No intersection could be evalued."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing intersection of to not equal points"<<endl;
	
	cout<<"vecBaseD3={1,2,-1}"<<endl;
	vecBaseD3[ 0 ] = 1;
	vecBaseD3[ 1 ] = 2;
	vecBaseD3[ 2 ] = -1;
	
	cout<<"cHyperplane< double > hyperplaneD3_3( vecBaseD3, vecDirectionsD3Empty );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3_3( vecBaseD3, vecDirectionsD3Empty );

	cout<<"pHyperplaneD3Inters = hyperplaneD3_1.evalueIntersection( hyperplaneD3_3 );"<<endl<<endl;
	pHyperplaneD3Inters = hyperplaneD3_1.evalueIntersection( hyperplaneD3_3 );
	
	if ( pHyperplaneD3Inters != NULL ){
		
		cerr<<"Error: An intersection hyperplanes could be evalued."<<endl;
		cerr<<"Hyperplane 1:"<<endl;
		hyperplaneD3_1.print( cerr );
		cerr<<endl<<"Hyperplane 2:"<<endl;
		hyperplaneD3_3.print( cerr );
		cerr<<endl<<"Intersection:"<<endl;
		pHyperplaneD3Inters->print( cerr );
		cerr<<endl;
		iReturn++;
		delete pHyperplaneD3Inters;
	}else{
		cout<<"The intersection of the hyperplanes could correctly not be evalued. "<<endl;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : intersection of two equal lines"<<endl;
	
	cout<<"vecBaseD3={1,2,3}"<<endl;
	vecBaseD3[ 0 ] = 1;
	vecBaseD3[ 1 ] = 2;
	vecBaseD3[ 2 ] = 2;
	cout<<"vector< vector< double > > vecDirectionsD3;={{3,2,4}}"<<endl;
	vector< vector< double > > vecDirectionsD3;
	vector< double > vecDirectionD3( 3, 0.0 );
	vecDirectionD3[ 0 ] = 3;
	vecDirectionD3[ 1 ] = 2;
	vecDirectionD3[ 2 ] = 4;
	vecDirectionsD3.push_back( vecDirectionD3 );
	
	cout<<"cHyperplane< double > hyperplaneD3_4( vecBaseD3, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3_4( vecBaseD3, vecDirectionsD3 );

	cout<<"vecBaseD3={-2,0,-2}"<<endl;
	vecBaseD3[ 0 ] = -2;
	vecBaseD3[ 1 ] = 0;
	vecBaseD3[ 2 ] = -2;
	cout<<"vecDirectionsD3={{6,4,8}}"<<endl;
	vecDirectionsD3.clear();
	vecDirectionD3[ 0 ] = 6;
	vecDirectionD3[ 1 ] = 4;
	vecDirectionD3[ 2 ] = 8;
	vecDirectionsD3.push_back( vecDirectionD3 );
	
	cout<<"cHyperplane< double > hyperplaneD3_5( vecBaseD3, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3_5( vecBaseD3, vecDirectionsD3 );

	cout<<"pHyperplaneD3Inters = hyperplaneD3_4.evalueIntersection( hyperplaneD3_5 );"<<endl<<endl;
	pHyperplaneD3Inters = hyperplaneD3_4.evalueIntersection( hyperplaneD3_5 );
	
	if ( pHyperplaneD3Inters != NULL ){
		if ( hyperplaneD3_4.equal( *pHyperplaneD3Inters ) ){
		
			cout<<"The intersection of the hyperplanes is correctly equal to the hyperplanes. "<<endl;
		}else{
			cerr<<"Error: The intersection of the hyperplanes is not equal to the hyperplanes ."<<endl;
			cerr<<"Hyperplane 1:"<<endl;
			hyperplaneD3_4.print( cerr );
			cerr<<endl<<"Hyperplane 2:"<<endl;
			hyperplaneD3_5.print( cerr );
			cerr<<endl<<"Intersection:"<<endl;
			pHyperplaneD3Inters->print( cerr );
			cerr<<endl;
			iReturn++;
		}
		delete pHyperplaneD3Inters;
	}else{
		cerr<<"Error: No intersection could be evalued."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : intersection of two parallel lines (empty intersection)"<<endl;
	
	cout<<"vecBaseD3={-2,0,-1}"<<endl;
	vecBaseD3[ 0 ] = -2;
	vecBaseD3[ 1 ] = 0;
	vecBaseD3[ 2 ] = -1;
	cout<<"vecDirectionsD3={{6,4,8}}"<<endl;
	vecDirectionsD3.clear();
	vecDirectionD3[ 0 ] = 6;
	vecDirectionD3[ 1 ] = 4;
	vecDirectionD3[ 2 ] = 8;
	vecDirectionsD3.push_back( vecDirectionD3 );
	
	cout<<"cHyperplane< double > hyperplaneD3_6( vecBaseD3, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3_6( vecBaseD3, vecDirectionsD3 );

	cout<<"pHyperplaneD3Inters = hyperplaneD3_4.evalueIntersection( hyperplaneD3_6 );"<<endl<<endl;
	pHyperplaneD3Inters = hyperplaneD3_4.evalueIntersection( hyperplaneD3_6 );
	
	if ( pHyperplaneD3Inters != NULL ){
		
		cerr<<"Error: An intersection hyperplanes could be evalued."<<endl;
		cerr<<"Hyperplane 1:"<<endl;
		hyperplaneD3_4.print( cerr );
		cerr<<endl<<"Hyperplane 2:"<<endl;
		hyperplaneD3_6.print( cerr );
		cerr<<endl<<"Intersection:"<<endl;
		pHyperplaneD3Inters->print( cerr );
		cerr<<endl;
		iReturn++;
		delete pHyperplaneD3Inters;
	}else{
		cout<<"The intersection of the hyperplanes could correctly not be evalued. "<<endl;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : intersection of two lines, when intersection is a point"<<endl;
	
	cout<<"vecBaseD3={1,2,1}"<<endl;
	vecBaseD3[ 0 ] = 1;
	vecBaseD3[ 1 ] = 2;
	vecBaseD3[ 2 ] = 1;
	vecDirectionsD3.clear();
	cout<<"cHyperplane< double > intersectionPointD3_1( vecBaseD3, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > intersectionPointD3_1( vecBaseD3, vecDirectionsD3 );
	
	cout<<"vecBaseD3={9,6,-1}"<<endl;
	vecBaseD3[ 0 ] = 9;
	vecBaseD3[ 1 ] = 6;
	vecBaseD3[ 2 ] = -1;
	cout<<"vecDirectionsD3={{4,2,-1}}"<<endl;
	vecDirectionD3[ 0 ] = 4;
	vecDirectionD3[ 1 ] = 2;
	vecDirectionD3[ 2 ] = -1;
	vecDirectionsD3.push_back( vecDirectionD3 );
	
	cout<<"cHyperplane< double > hyperplaneD3_7( vecBaseD3, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3_7( vecBaseD3, vecDirectionsD3 );

	cout<<"vecBaseD3={0,2.5,-0.5}"<<endl;
	vecBaseD3[ 0 ] = 0;
	vecBaseD3[ 1 ] = 2.5;
	vecBaseD3[ 2 ] = -0.5;
	cout<<"vecDirectionsD3={{2,-1,3}}"<<endl;
	vecDirectionsD3.clear();
	vecDirectionD3[ 0 ] = 2;
	vecDirectionD3[ 1 ] = -1;
	vecDirectionD3[ 2 ] = 3;
	vecDirectionsD3.push_back( vecDirectionD3 );
	
	cout<<"cHyperplane< double > hyperplaneD3_8( vecBaseD3, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3_8( vecBaseD3, vecDirectionsD3 );

	cout<<"pHyperplaneD3Inters = hyperplaneD3_7.evalueIntersection( hyperplaneD3_8 );"<<endl<<endl;
	pHyperplaneD3Inters = hyperplaneD3_7.evalueIntersection( hyperplaneD3_8 );
	
	if ( pHyperplaneD3Inters != NULL ){
		if ( intersectionPointD3_1.equal( *pHyperplaneD3Inters ) ){
		
			cout<<"The intersection of the hyperplanes is correctly equal to the point. "<<endl;
		}else{
			cerr<<"Error: The intersection of the hyperplanes is not equal to the point ."<<endl;
			cerr<<"Hyperplane 1:"<<endl;
			hyperplaneD3_7.print( cerr );
			cerr<<endl<<"Hyperplane 2:"<<endl;
			hyperplaneD3_8.print( cerr );
			cerr<<endl<<"Intersection:"<<endl;
			pHyperplaneD3Inters->print( cerr );
			cerr<<endl;
			iReturn++;
		}
		delete pHyperplaneD3Inters;
	}else{
		cerr<<"Error: No intersection could be evalued."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : intersection of a lines and a plane, intersection is point"<<endl;
	
	cout<<"vecBaseD3={3,1,-2}"<<endl;
	vecBaseD3[ 0 ] = 3;
	vecBaseD3[ 1 ] = 1;
	vecBaseD3[ 2 ] = -2;
	vecDirectionsD3.clear();
	cout<<"cHyperplane< double > intersectionPointD3_2( vecBaseD3, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > intersectionPointD3_2( vecBaseD3, vecDirectionsD3 );
	
	cout<<"vecBaseD3={7,9,-4}"<<endl;
	vecBaseD3[ 0 ] = 7;
	vecBaseD3[ 1 ] = 9;
	vecBaseD3[ 2 ] = -4;
	cout<<"vecDirectionsD3={{2,4,-1}}"<<endl;
	vecDirectionsD3.clear();
	vecDirectionD3[ 0 ] = 2;
	vecDirectionD3[ 1 ] = 4;
	vecDirectionD3[ 2 ] = -1;
	vecDirectionsD3.push_back( vecDirectionD3 );
	
	cout<<"cHyperplane< double > hyperplaneD3_9( vecBaseD3, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3_9( vecBaseD3, vecDirectionsD3 );

	cout<<"vecBaseD3={4,5,2}"<<endl;
	vecBaseD3[ 0 ] = 4;
	vecBaseD3[ 1 ] = 5;
	vecBaseD3[ 2 ] = 2;
	cout<<" vecDirectionsD3={{3,2,4}{1,-1,0}}"<<endl;
	vecDirectionsD3.clear();
	vecDirectionD3[ 0 ] = 3;
	vecDirectionD3[ 1 ] = 2;
	vecDirectionD3[ 2 ] = 4;
	vecDirectionsD3.push_back( vecDirectionD3 );
	vecDirectionD3[ 0 ] = 1;
	vecDirectionD3[ 1 ] = -1;
	vecDirectionD3[ 2 ] = 0;
	vecDirectionsD3.push_back( vecDirectionD3 );
	cout<<"cHyperplane< double > hyperplaneD3_10( vecBaseD3, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3_10( vecBaseD3, vecDirectionsD3 );

	cout<<"pHyperplaneD3Inters = hyperplaneD3_9.evalueIntersection( hyperplaneD3_10 );"<<endl<<endl;
	pHyperplaneD3Inters = hyperplaneD3_9.evalueIntersection( hyperplaneD3_10 );
	
	if ( pHyperplaneD3Inters != NULL ){
		if ( intersectionPointD3_2.equal( *pHyperplaneD3Inters ) ){
		
			cout<<"The intersection of the hyperplanes is correctly equal to the point intersectionPointD3_2. "<<endl;
		}else{
			cerr<<"Error: The intersection of the hyperplanes is not equal to the point intersectionPointD3_2."<<endl;
			cerr<<"Hyperplane 1:"<<endl;
			hyperplaneD3_9.print( cerr );
			cerr<<endl<<"Hyperplane 2:"<<endl;
			hyperplaneD3_10.print( cerr );
			cerr<<endl<<"Intersection:"<<endl;
			pHyperplaneD3Inters->print( cerr );
			cerr<<endl;
			iReturn++;
		}
		delete pHyperplaneD3Inters;
	}else{
		cerr<<"Error: No intersection could be evalued."<<endl;
		iReturn++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : intersection of a plane and a lines (which are parallel -> empty intersection)"<<endl;
	
	cout<<"vecBaseD3={4,5.1,2}"<<endl;
	vecBaseD3[ 0 ] = 4;
	vecBaseD3[ 1 ] = 5.1;
	vecBaseD3[ 2 ] = 2;
	cout<<"vecDirectionsD3={{3,7,8}}"<<endl;
	vecDirectionsD3.clear();
	vecDirectionD3[ 0 ] = 3;
	vecDirectionD3[ 1 ] = 7;
	vecDirectionD3[ 2 ] = 8;
	vecDirectionsD3.push_back( vecDirectionD3 );
	
	cout<<"cHyperplane< double > hyperplaneD3_11( vecBaseD3, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3_11( vecBaseD3, vecDirectionsD3 );


	cout<<"pHyperplaneD3Inters = hyperplaneD3_11.evalueIntersection( hyperplaneD3_10 );"<<endl<<endl;
	pHyperplaneD3Inters = hyperplaneD3_11.evalueIntersection( hyperplaneD3_10 );
	
	if ( pHyperplaneD3Inters != NULL ){
		
		cerr<<"Error: An intersection hyperplanes could be evalued."<<endl;
		cerr<<"Hyperplane 1:"<<endl;
		hyperplaneD3_10.print( cerr );
		cerr<<endl<<"Hyperplane 2:"<<endl;
		hyperplaneD3_11.print( cerr );
		cerr<<endl<<"Intersection:"<<endl;
		pHyperplaneD3Inters->print( cerr );
		cerr<<endl;
		iReturn++;
		delete pHyperplaneD3Inters;
	}else{
		cout<<"The intersection of the hyperplanes could correctly not be evalued. "<<endl;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : intersection of a plane and a lines (line on plane -> intersection is line )"<<endl;
	
	cout<<"vecBaseD3={-2,6,-2}"<<endl;
	vecBaseD3[ 0 ] = -2;
	vecBaseD3[ 1 ] = 6;
	vecBaseD3[ 2 ] = -2;
	cout<<"vecDirectionsD3={{0.5,-3,-2}}"<<endl;
	vecDirectionsD3.clear();
	vecDirectionD3[ 0 ] = 0.5;
	vecDirectionD3[ 1 ] = -3;
	vecDirectionD3[ 2 ] = -2;
	vecDirectionsD3.push_back( vecDirectionD3 );
	
	cout<<"cHyperplane< double > hyperplaneD3_12( vecBaseD3, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3_12( vecBaseD3, vecDirectionsD3 );


	cout<<"pHyperplaneD3Inters = hyperplaneD3_12.evalueIntersection( hyperplaneD3_10 );"<<endl<<endl;
	pHyperplaneD3Inters = hyperplaneD3_12.evalueIntersection( hyperplaneD3_10 );
	
	if ( pHyperplaneD3Inters != NULL ){
		if ( hyperplaneD3_12.equal( *pHyperplaneD3Inters ) ){
		
			cout<<"The intersection of the hyperplanes is correctly equal to the line hyperplaneD3_12. "<<endl;
		}else{
			cerr<<"Error: The intersection of the hyperplanes is not equal to the line hyperplaneD3_12."<<endl;
			cerr<<"Hyperplane 1:"<<endl;
			hyperplaneD3_10.print( cerr );
			cerr<<endl<<"Hyperplane 2:"<<endl;
			hyperplaneD3_12.print( cerr );
			cerr<<endl<<"Intersection:"<<endl;
			pHyperplaneD3Inters->print( cerr );
			cerr<<endl;
			iReturn++;
		}
		delete pHyperplaneD3Inters;
	}else{
		cerr<<"Error: No intersection could be evalued."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : intersection of two planes, intersection is line"<<endl;
	
	cout<<"vecBaseD3={5,3,-11}"<<endl;
	vecBaseD3[ 0 ] = 5;
	vecBaseD3[ 1 ] = 3;
	vecBaseD3[ 2 ] = -11;
	cout<<"vecDirectionsD3={{0,8,7}}"<<endl;
	vecDirectionsD3.clear();
	vecDirectionD3[ 0 ] = 0;
	vecDirectionD3[ 1 ] = 8;
	vecDirectionD3[ 2 ] = 7;
	vecDirectionsD3.push_back( vecDirectionD3 );
	cout<<"cHyperplane< double > intersectionLineD3_1( vecBaseD3, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > intersectionLineD3_1( vecBaseD3, vecDirectionsD3 );
	
	cout<<"vecBaseD3={2,9,1}"<<endl;
	vecBaseD3[ 0 ] = 2;
	vecBaseD3[ 1 ] = 9;
	vecBaseD3[ 2 ] = 1;
	cout<<"vecDirectionsD3={{2,4,-1}{-1,2,4}}"<<endl;
	vecDirectionsD3.clear();
	vecDirectionD3[ 0 ] = 2;
	vecDirectionD3[ 1 ] = 4;
	vecDirectionD3[ 2 ] = -1;
	vecDirectionsD3.push_back( vecDirectionD3 );
	vecDirectionD3[ 0 ] = -1;
	vecDirectionD3[ 1 ] = 2;
	vecDirectionD3[ 2 ] = 4;
	vecDirectionsD3.push_back( vecDirectionD3 );
	
	cout<<"cHyperplane< double > hyperplaneD3_13( vecBaseD3, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3_13( vecBaseD3, vecDirectionsD3 );

	cout<<"vecBaseD3={5,7,7.5}"<<endl;
	vecBaseD3[ 0 ] = 5;
	vecBaseD3[ 1 ] = 7;
	vecBaseD3[ 2 ] = -7.5;
	cout<<" vecDirectionsD3={{4,2,3}{-2,3,2}}"<<endl;
	vecDirectionsD3.clear();
	vecDirectionD3[ 0 ] = 4;
	vecDirectionD3[ 1 ] = 2;
	vecDirectionD3[ 2 ] = 3;
	vecDirectionsD3.push_back( vecDirectionD3 );
	vecDirectionD3[ 0 ] = -2;
	vecDirectionD3[ 1 ] = 3;
	vecDirectionD3[ 2 ] = 2;
	vecDirectionsD3.push_back( vecDirectionD3 );
	cout<<"cHyperplane< double > hyperplaneD3_14( vecBaseD3, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3_14( vecBaseD3, vecDirectionsD3 );

	cout<<"pHyperplaneD3Inters = hyperplaneD3_13.evalueIntersection( hyperplaneD3_14 );"<<endl<<endl;
	pHyperplaneD3Inters = hyperplaneD3_13.evalueIntersection( hyperplaneD3_14 );
	
	if ( pHyperplaneD3Inters != NULL ){
		if ( intersectionLineD3_1.equal( *pHyperplaneD3Inters ) ){
		
			cout<<"The intersection of the hyperplanes is correctly equal to the point intersectionLineD3_1. "<<endl;
		}else{
			cerr<<"Error: The intersection of the hyperplanes is not equal to the point intersectionLineD3_1."<<endl;
			cerr<<"Hyperplane 1:"<<endl;
			hyperplaneD3_13.print( cerr );
			cerr<<endl<<"Hyperplane 2:"<<endl;
			hyperplaneD3_14.print( cerr );
			cerr<<endl<<"Intersection:"<<endl;
			pHyperplaneD3Inters->print( cerr );
			cerr<<endl;
			iReturn++;
		}
		delete pHyperplaneD3Inters;
	}else{
		cerr<<"Error: No intersection could be evalued."<<endl;
		iReturn++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : intersection two planes which are parallel (-> empty intersection)"<<endl;
	
	cout<<"vecBaseD3={6,8,-8}"<<endl;
	vecBaseD3[ 0 ] = 6;
	vecBaseD3[ 1 ] = 8;
	vecBaseD3[ 2 ] = -8;
	cout<<"vecDirectionsD3={{0,8,7}{-7,-10,7}}"<<endl;
	vecDirectionsD3.clear();
	vecDirectionD3[ 0 ] = 0;
	vecDirectionD3[ 1 ] = 8;
	vecDirectionD3[ 2 ] = 7;
	vecDirectionsD3.push_back( vecDirectionD3 );
	vecDirectionD3[ 0 ] = -7;
	vecDirectionD3[ 1 ] = -10;
	vecDirectionD3[ 2 ] = 7;
	vecDirectionsD3.push_back( vecDirectionD3 );

	cout<<"cHyperplane< double > hyperplaneD3_15( vecBaseD3, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3_15( vecBaseD3, vecDirectionsD3 );

	cout<<"pHyperplaneD3Inters = hyperplaneD3_15.evalueIntersection( hyperplaneD3_13 );"<<endl<<endl;
	pHyperplaneD3Inters = hyperplaneD3_15.evalueIntersection( hyperplaneD3_13 );
	
	if ( pHyperplaneD3Inters != NULL ){
		
		cerr<<"Error: An intersection hyperplanes could be evalued."<<endl;
		cerr<<"Hyperplane 1:"<<endl;
		hyperplaneD3_15.print( cerr );
		cerr<<endl<<"Hyperplane 2:"<<endl;
		hyperplaneD3_13.print( cerr );
		cerr<<endl<<"Intersection:"<<endl;
		pHyperplaneD3Inters->print( cerr );
		cerr<<endl;
		iReturn++;
		delete pHyperplaneD3Inters;
	}else{
		cout<<"The intersection of the hyperplanes could correctly not be evalued. "<<endl;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : intersection two planes which are equal (intersection the plane)"<<endl;

	cout<<"vecBaseD3={-2,1,3}"<<endl;
	vecBaseD3[ 0 ] = -2;
	vecBaseD3[ 1 ] = 1;
	vecBaseD3[ 2 ] = 3;
	cout<<"vecDirectionsD3={{2,4,-1}{-1,2,4}}"<<endl;
	vecDirectionsD3.clear();
	vecDirectionD3[ 0 ] = 4;
	vecDirectionD3[ 1 ] = 0;
	vecDirectionD3[ 2 ] = -9;
	vecDirectionsD3.push_back( vecDirectionD3 );
	vecDirectionD3[ 0 ] = 1;
	vecDirectionD3[ 1 ] = 6;
	vecDirectionD3[ 2 ] = 3;
	vecDirectionsD3.push_back( vecDirectionD3 );

	cout<<"cHyperplane< double > hyperplaneD3_16( vecBaseD3, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3_16( vecBaseD3, vecDirectionsD3 );

	cout<<"pHyperplaneD3Inters = hyperplaneD3_13.evalueIntersection( hyperplaneD3_16 );"<<endl<<endl;
	pHyperplaneD3Inters = hyperplaneD3_13.evalueIntersection( hyperplaneD3_16 );
	
	if ( pHyperplaneD3Inters != NULL ){
		if ( hyperplaneD3_13.equal( *pHyperplaneD3Inters ) ){
		
			cout<<"The intersection of the hyperplanes is correctly equal to the line hyperplaneD3_13. "<<endl;
		}else{
			cerr<<"Error: The intersection of the hyperplanes is not equal to the line hyperplaneD3_13."<<endl;
			cerr<<"Hyperplane 1:"<<endl;
			hyperplaneD3_13.print( cerr );
			cerr<<endl<<"Hyperplane 2:"<<endl;
			hyperplaneD3_16.print( cerr );
			cerr<<endl<<"Intersection:"<<endl;
			pHyperplaneD3Inters->print( cerr );
			cerr<<endl;
			iReturn++;
		}
		delete pHyperplaneD3Inters;
	}else{
		cerr<<"Error: No intersection could be evalued."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : intersection of two planes, intersection is line"<<endl;
	
	cout<<"vecBaseD3={8,0,0}"<<endl;
	vecBaseD3[ 0 ] = 8;
	vecBaseD3[ 1 ] = 0;
	vecBaseD3[ 2 ] = 8;
	cout<<"vecDirectionsD3={{0,1,0}}"<<endl;
	vecDirectionsD3.clear();
	vecDirectionD3[ 0 ] = 0;
	vecDirectionD3[ 1 ] = 1;
	vecDirectionD3[ 2 ] = 0;
	vecDirectionsD3.push_back( vecDirectionD3 );
	cout<<"cHyperplane< double > intersectionLineD3_2( vecBaseD3, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > intersectionLineD3_2( vecBaseD3, vecDirectionsD3 );
	
	cout<<"vecBaseD3={8,0,0}"<<endl;
	vecBaseD3[ 0 ] = 8;
	vecBaseD3[ 1 ] = 0;
	vecBaseD3[ 2 ] = 0;
	cout<<"vecDirectionsD3={{0,1,0}{0,0,1}}"<<endl;
	vecDirectionsD3.clear();
	vecDirectionD3[ 0 ] = 0;
	vecDirectionD3[ 1 ] = 1;
	vecDirectionD3[ 2 ] = 0;
	vecDirectionsD3.push_back( vecDirectionD3 );
	vecDirectionD3[ 0 ] = 0;
	vecDirectionD3[ 1 ] = 0;
	vecDirectionD3[ 2 ] = 1;
	vecDirectionsD3.push_back( vecDirectionD3 );
	
	cout<<"cHyperplane< double > hyperplaneD3_17( vecBaseD3, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3_17( vecBaseD3, vecDirectionsD3 );

	cout<<"vecBaseD3={0,0,8}"<<endl;
	vecBaseD3[ 0 ] = 0;
	vecBaseD3[ 1 ] = 0;
	vecBaseD3[ 2 ] = 8;
	cout<<" vecDirectionsD3={{1,0,0}{0,1,0}}"<<endl;
	vecDirectionsD3.clear();
	vecDirectionD3[ 0 ] = 1;
	vecDirectionD3[ 1 ] = 0;
	vecDirectionD3[ 2 ] = 0;
	vecDirectionsD3.push_back( vecDirectionD3 );
	vecDirectionD3[ 0 ] = 0;
	vecDirectionD3[ 1 ] = 1;
	vecDirectionD3[ 2 ] = 0;
	vecDirectionsD3.push_back( vecDirectionD3 );
	cout<<"cHyperplane< double > hyperplaneD3_18( vecBaseD3, vecDirectionsD3 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD3_18( vecBaseD3, vecDirectionsD3 );

	cout<<"pHyperplaneD3Inters = hyperplaneD3_18.evalueIntersection( hyperplaneD3_17 );"<<endl<<endl;
	pHyperplaneD3Inters = hyperplaneD3_18.evalueIntersection( hyperplaneD3_17 );
	
	if ( pHyperplaneD3Inters != NULL ){
		if ( intersectionLineD3_2.equal( *pHyperplaneD3Inters ) ){
		
			cout<<"The intersection of the hyperplanes is correctly equal to the point intersectionLineD3_2. "<<endl;
		}else{
			cerr<<"Error: The intersection of the hyperplanes is not equal to the point intersectionLineD3_2."<<endl;
			cerr<<"Hyperplane 1:"<<endl;
			hyperplaneD3_17.print( cerr );
			cerr<<endl<<"Hyperplane 2:"<<endl;
			hyperplaneD3_18.print( cerr );
			cerr<<endl<<"Intersection:"<<endl;
			pHyperplaneD3Inters->print( cerr );
			cerr<<endl;
			iReturn++;
		}
		delete pHyperplaneD3Inters;
	}else{
		cerr<<"Error: No intersection could be evalued."<<endl;
		iReturn++;
	}
	
	cout<<"pHyperplaneD3Inters = hyperplaneD3_17.evalueIntersection( hyperplaneD3_18 );"<<endl<<endl;
	pHyperplaneD3Inters = hyperplaneD3_17.evalueIntersection( hyperplaneD3_18 );
	
	if ( pHyperplaneD3Inters != NULL ){
		if ( intersectionLineD3_2.equal( *pHyperplaneD3Inters ) ){
		
			cout<<"The intersection of the hyperplanes is correctly equal to the point intersectionLineD3_2. "<<endl;
		}else{
			cerr<<"Error: The intersection of the hyperplanes is not equal to the point intersectionLineD3_2."<<endl;
			cerr<<"Hyperplane 1:"<<endl;
			hyperplaneD3_17.print( cerr );
			cerr<<endl<<"Hyperplane 2:"<<endl;
			hyperplaneD3_18.print( cerr );
			cerr<<endl<<"Intersection:"<<endl;
			pHyperplaneD3Inters->print( cerr );
			cerr<<endl;
			iReturn++;
		}
		delete pHyperplaneD3Inters;
	}else{
		cerr<<"Error: No intersection could be evalued."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : intersection of two 2 dimensional planes in 4 dimensional space, intersection is an point"<<endl;

	cout<<"vecBaseD4={1,2,4,8}"<<endl;
	vector< double > vecBaseD4( 4, 0.0 );
	vecBaseD4[ 0 ] = 1;
	vecBaseD4[ 1 ] = 2;
	vecBaseD4[ 2 ] = 4;
	vecBaseD4[ 3 ] = 8;
	cout<<"vecDirectionsD4={{1,0,2,4}{0,1,4,2}}"<<endl;
	vector< vector< double > > vecDirectionsD4;
	vector< double > vecDirectionD4( 4, 0.0 );
	vecDirectionD4[ 0 ] = 1;
	vecDirectionD4[ 1 ] = 0;
	vecDirectionD4[ 2 ] = 2;
	vecDirectionD4[ 3 ] = 4;
	vecDirectionsD4.push_back( vecDirectionD4 );
	vecDirectionD4[ 0 ] = 0;
	vecDirectionD4[ 1 ] = 1;
	vecDirectionD4[ 2 ] = 4;
	vecDirectionD4[ 3 ] = 2;
	vecDirectionsD4.push_back( vecDirectionD4 );
	cout<<"cHyperplane< double > hyperplaneD4_1( vecBaseD4, vecDirectionsD4 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD4_1( vecBaseD4, vecDirectionsD4);

	cout<<"vecBaseD4={2,2,2,2}"<<endl;
	vecBaseD4[ 0 ] = 2;
	vecBaseD4[ 1 ] = 2;
	vecBaseD4[ 2 ] = 2;
	vecBaseD4[ 3 ] = 2;
	cout<<"vecDirectionsD4={{0,1,0,2}{0,0,1,8}}"<<endl;
	vecDirectionsD4.clear();
	vecDirectionD4[ 0 ] = 0;
	vecDirectionD4[ 1 ] = 1;
	vecDirectionD4[ 2 ] = 0;
	vecDirectionD4[ 3 ] = 2;
	vecDirectionsD4.push_back( vecDirectionD4 );
	vecDirectionD4[ 0 ] = 0;
	vecDirectionD4[ 1 ] = 0;
	vecDirectionD4[ 2 ] = 1;
	vecDirectionD4[ 3 ] = 8;
	vecDirectionsD4.push_back( vecDirectionD4 );
	cout<<"cHyperplane< double > hyperplaneD4_2( vecBaseD4, vecDirectionsD4 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD4_2( vecBaseD4, vecDirectionsD4);

	cout<<"pHyperplaneD4Inters = hyperplaneD4_1.evalueIntersection( hyperplaneD4_2 );"<<endl<<endl;
	cHyperplane< double > * pHyperplaneD4Inters = hyperplaneD4_1.evalueIntersection( hyperplaneD4_2 );
	
	cout<<"vecBaseD4={2, 1.3125, 3.25, 10.625}"<<endl;
	vecBaseD4[ 0 ] = 2;
	vecBaseD4[ 1 ] = 1.3125;
	vecBaseD4[ 2 ] = 3.25;
	vecBaseD4[ 3 ] = 10.625;
	cout<<"vecDirectionsD4={}"<<endl;
	vecDirectionsD4.clear();
	cout<<"cHyperplane< double > intersectionPointD4_1( vecBaseD4, vecDirectionsD4 );"<<endl<<endl;
	cHyperplane< double > intersectionPointD4_1( vecBaseD4, vecDirectionsD4);
	
	if ( pHyperplaneD4Inters != NULL ){
		if ( intersectionPointD4_1.equal( *pHyperplaneD4Inters ) ){
		
			cout<<"The intersection of the hyperplanes is correctly equal to the point intersectionPointD4_1. "<<endl;
		}else{
			cerr<<"Error: The intersection of the hyperplanes is not equal to the point intersectionPointD4_1."<<endl;
			cerr<<"Hyperplane 1:"<<endl;
			hyperplaneD4_1.print( cerr );
			cerr<<endl<<"Hyperplane 2:"<<endl;
			hyperplaneD4_2.print( cerr );
			cerr<<endl<<"Intersection:"<<endl;
			pHyperplaneD4Inters->print( cerr );
			cerr<<endl;
			iReturn++;
		}
		delete pHyperplaneD4Inters;
	}else{
		cerr<<"Error: No intersection could be evalued."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : intersection of two 2 dimensional planes in 4 dimensional space, intersection is an point"<<endl;

	cout<<"vecBaseD4={1,2,4,8}"<<endl;
	vecBaseD4[ 0 ] = 1;
	vecBaseD4[ 1 ] = 2;
	vecBaseD4[ 2 ] = 4;
	vecBaseD4[ 3 ] = 8;
	cout<<"vecDirectionsD4={{1,0,4,2}{0,1,4,4}}"<<endl;
	vecDirectionsD4.clear();
	vecDirectionD4[ 0 ] = 1;
	vecDirectionD4[ 1 ] = 0;
	vecDirectionD4[ 2 ] = 4;
	vecDirectionD4[ 3 ] = 2;
	vecDirectionsD4.push_back( vecDirectionD4 );
	vecDirectionD4[ 0 ] = 0;
	vecDirectionD4[ 1 ] = 1;
	vecDirectionD4[ 2 ] = 4;
	vecDirectionD4[ 3 ] = 4;
	vecDirectionsD4.push_back( vecDirectionD4 );
	cout<<"cHyperplane< double > hyperplaneD4_3( vecBaseD4, vecDirectionsD4 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD4_3( vecBaseD4, vecDirectionsD4);

	cout<<"vecBaseD4={4,4,4,4}"<<endl;
	vecBaseD4[ 0 ] = 4;
	vecBaseD4[ 1 ] = 4;
	vecBaseD4[ 2 ] = 4;
	vecBaseD4[ 3 ] = 4;
	cout<<"vecDirectionsD4={{1,0,0,2}{0,0,1,8}}"<<endl;
	vecDirectionsD4.clear();
	vecDirectionD4[ 0 ] = 1;
	vecDirectionD4[ 1 ] = 0;
	vecDirectionD4[ 2 ] = 0;
	vecDirectionD4[ 3 ] = 2;
	vecDirectionsD4.push_back( vecDirectionD4 );
	vecDirectionD4[ 0 ] = 0;
	vecDirectionD4[ 1 ] = 0;
	vecDirectionD4[ 2 ] = 1;
	vecDirectionD4[ 3 ] = 8;
	vecDirectionsD4.push_back( vecDirectionD4 );
	cout<<"cHyperplane< double > hyperplaneD4_4( vecBaseD4, vecDirectionsD4 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD4_4( vecBaseD4, vecDirectionsD4);

	cout<<"pHyperplaneD4Inters = hyperplaneD4_3.evalueIntersection( hyperplaneD4_4 );"<<endl<<endl;
	pHyperplaneD4Inters = hyperplaneD4_3.evalueIntersection( hyperplaneD4_4 );
	
	cout<<"vecBaseD4={-0.4375, 4, 6.25, 13.125}"<<endl;
	vecBaseD4[ 0 ] = -0.4375;
	vecBaseD4[ 1 ] = 4;
	vecBaseD4[ 2 ] = 6.25;
	vecBaseD4[ 3 ] = 13.125;
	cout<<"vecDirectionsD4={}"<<endl;
	vecDirectionsD4.clear();
	cout<<"cHyperplane< double > intersectionPointD4_2( vecBaseD4, vecDirectionsD4 );"<<endl<<endl;
	cHyperplane< double > intersectionPointD4_2( vecBaseD4, vecDirectionsD4);
	
	if ( pHyperplaneD4Inters != NULL ){
		if ( intersectionPointD4_2.equal( *pHyperplaneD4Inters ) ){
		
			cout<<"The intersection of the hyperplanes is correctly equal to the point intersectionPointD4_2. "<<endl;
		}else{
			cerr<<"Error: The intersection of the hyperplanes is not equal to the point intersectionPointD4_2."<<endl;
			cerr<<"Hyperplane 1:"<<endl;
			hyperplaneD4_3.print( cerr );
			cerr<<endl<<"Hyperplane 2:"<<endl;
			hyperplaneD4_4.print( cerr );
			cerr<<endl<<"Intersection:"<<endl;
			pHyperplaneD4Inters->print( cerr );
			cerr<<endl;
			iReturn++;
		}
		delete pHyperplaneD4Inters;
	}else{
		cerr<<"Error: No intersection could be evalued."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : intersection of two 2 dimensional planes in 4 dimensional space, intersection is a point"<<endl;

	cout<<"vecBaseD4={1,8,4,2}"<<endl;
	vecBaseD4[ 0 ] = 1;
	vecBaseD4[ 1 ] = 8;
	vecBaseD4[ 2 ] = 4;
	vecBaseD4[ 3 ] = 2;
	cout<<"vecDirectionsD4={{1,0,2,0}{0,1,4,0}}"<<endl;
	vecDirectionsD4.clear();
	vecDirectionD4[ 0 ] = 1;
	vecDirectionD4[ 1 ] = 0;
	vecDirectionD4[ 2 ] = 2;
	vecDirectionD4[ 3 ] = 0;
	vecDirectionsD4.push_back( vecDirectionD4 );
	vecDirectionD4[ 0 ] = 0;
	vecDirectionD4[ 1 ] = 1;
	vecDirectionD4[ 2 ] = 4;
	vecDirectionD4[ 3 ] = 0;
	vecDirectionsD4.push_back( vecDirectionD4 );
	cout<<"cHyperplane< double > hyperplaneD4_5( vecBaseD4, vecDirectionsD4 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD4_5( vecBaseD4, vecDirectionsD4);

	cout<<"vecBaseD4={2,4,2,1}"<<endl;
	vecBaseD4[ 0 ] = 2;
	vecBaseD4[ 1 ] = 4;
	vecBaseD4[ 2 ] = 2;
	vecBaseD4[ 3 ] = 1;
	cout<<"vecDirectionsD4={{1,0,0,2}{0,0,1,4}}"<<endl;
	vecDirectionsD4.clear();
	vecDirectionD4[ 0 ] = 1;
	vecDirectionD4[ 1 ] = 0;
	vecDirectionD4[ 2 ] = 0;
	vecDirectionD4[ 3 ] = 2;
	vecDirectionsD4.push_back( vecDirectionD4 );
	vecDirectionD4[ 0 ] = 0;
	vecDirectionD4[ 1 ] = 0;
	vecDirectionD4[ 2 ] = 1;
	vecDirectionD4[ 3 ] = 4;
	vecDirectionsD4.push_back( vecDirectionD4 );
	cout<<"cHyperplane< double > hyperplaneD4_6( vecBaseD4, vecDirectionsD4 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD4_6( vecBaseD4, vecDirectionsD4);

	cout<<"pHyperplaneD4Inters = hyperplaneD4_5.evalueIntersection( hyperplaneD4_6 );"<<endl<<endl;
	pHyperplaneD4Inters = hyperplaneD4_5.evalueIntersection( hyperplaneD4_6 );
	
	cout<<"vecBaseD4={6.9, 4, -0.2, 2}"<<endl;
	vecBaseD4[ 0 ] = 6.9;
	vecBaseD4[ 1 ] = 4;
	vecBaseD4[ 2 ] = -0.2;
	vecBaseD4[ 3 ] = 2;
	cout<<"vecDirectionsD4={}"<<endl;
	vecDirectionsD4.clear();
	cout<<"cHyperplane< double > intersectionPointD4_3( vecBaseD4, vecDirectionsD4 );"<<endl<<endl;
	cHyperplane< double > intersectionPointD4_3( vecBaseD4, vecDirectionsD4);
	
	if ( pHyperplaneD4Inters != NULL ){
		if ( intersectionPointD4_3.equal( *pHyperplaneD4Inters ) ){
		
			cout<<"The intersection of the hyperplanes is correctly equal to the point intersectionPointD4_3. "<<endl;
		}else{
			cerr<<"Error: The intersection of the hyperplanes is not equal to the point intersectionPointD4_3."<<endl;
			cerr<<"Hyperplane 1:"<<endl;
			hyperplaneD4_5.print( cerr );
			cerr<<endl<<"Hyperplane 2:"<<endl;
			hyperplaneD4_6.print( cerr );
			cerr<<endl<<"Intersection:"<<endl;
			pHyperplaneD4Inters->print( cerr );
			cerr<<endl;
			iReturn++;
		}
		delete pHyperplaneD4Inters;
	}else{
		cerr<<"Error: No intersection could be evalued."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : intersection of two 2 dimensional planes in 4 dimensional space, intersection is a line"<<endl;

	cout<<"vecBaseD4={1, 8, 4, 0}"<<endl;
	vecBaseD4[ 0 ] = 1;
	vecBaseD4[ 1 ] = 8;
	vecBaseD4[ 2 ] = 4;
	vecBaseD4[ 3 ] = 0;
	cout<<"vecDirectionsD4={{1, 0, 0.5, 0}{0, 0, 0, 1}}"<<endl;
	vecDirectionsD4.clear();
	vecDirectionD4[ 0 ] = 1;
	vecDirectionD4[ 1 ] = 0;
	vecDirectionD4[ 2 ] = 0.5;
	vecDirectionD4[ 3 ] = 0;
	vecDirectionsD4.push_back( vecDirectionD4 );
	vecDirectionD4[ 0 ] = 0;
	vecDirectionD4[ 1 ] = 0;
	vecDirectionD4[ 2 ] = 0;
	vecDirectionD4[ 3 ] = 1;
	vecDirectionsD4.push_back( vecDirectionD4 );
	cout<<"cHyperplane< double > hyperplaneD4_7( vecBaseD4, vecDirectionsD4 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD4_7( vecBaseD4, vecDirectionsD4);

	cout<<"vecBaseD4={4, 2, 4, 12}"<<endl;
	vecBaseD4[ 0 ] = 4;
	vecBaseD4[ 1 ] = 2;
	vecBaseD4[ 2 ] = 4;
	vecBaseD4[ 3 ] = 12;
	cout<<"vecDirectionsD4={{1, 0, 0.5, 2}{0, 1, 0.25, 0.5}}"<<endl;
	vecDirectionsD4.clear();
	vecDirectionD4[ 0 ] = 1;
	vecDirectionD4[ 1 ] = 0;
	vecDirectionD4[ 2 ] = 0.5;
	vecDirectionD4[ 3 ] = 2;
	vecDirectionsD4.push_back( vecDirectionD4 );
	vecDirectionD4[ 0 ] = 0;
	vecDirectionD4[ 1 ] = 1;
	vecDirectionD4[ 2 ] = 0.25;
	vecDirectionD4[ 3 ] = 0.5;
	vecDirectionsD4.push_back( vecDirectionD4 );
	cout<<"cHyperplane< double > hyperplaneD4_8( vecBaseD4, vecDirectionsD4 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD4_8( vecBaseD4, vecDirectionsD4);

	cout<<"pHyperplaneD4Inters = hyperplaneD4_7.evalueIntersection( hyperplaneD4_8 );"<<endl<<endl;
	pHyperplaneD4Inters = hyperplaneD4_7.evalueIntersection( hyperplaneD4_8 );
	cout<<"vecBaseD4={-3, 8, 2, 1}"<<endl;
	vecBaseD4[ 0 ] = -3;
	vecBaseD4[ 1 ] = 8;
	vecBaseD4[ 2 ] = 2;
	vecBaseD4[ 3 ] = 1;
	cout<<"vecDirectionsD4={{1, 0, 0.5, 2}}"<<endl;
	vecDirectionsD4.clear();
	vecDirectionD4[ 0 ] = 1;
	vecDirectionD4[ 1 ] = 0;
	vecDirectionD4[ 2 ] = 0.5;
	vecDirectionD4[ 3 ] = 2;
	vecDirectionsD4.push_back( vecDirectionD4 );
	cout<<"cHyperplane< double > intersectionPointD4_4( vecBaseD4, vecDirectionsD4 );"<<endl<<endl;
	cHyperplane< double > intersectionPointD4_4( vecBaseD4, vecDirectionsD4);
	
	if ( pHyperplaneD4Inters != NULL ){
		if ( intersectionPointD4_4.equal( *pHyperplaneD4Inters ) ){
		
			cout<<"The intersection of the hyperplanes is correctly equal to the point intersectionPointD4_4. "<<endl;
		}else{
			cerr<<"Error: The intersection of the hyperplanes is not equal to the point intersectionPointD4_4."<<endl;
			cerr<<"Hyperplane 1:"<<endl;
			hyperplaneD4_7.print( cerr );
			cerr<<endl<<"Hyperplane 2:"<<endl;
			hyperplaneD4_8.print( cerr );
			cerr<<endl<<"Intersection:"<<endl;
			pHyperplaneD4Inters->print( cerr );
			cerr<<endl;
			iReturn++;
		}
		delete pHyperplaneD4Inters;
	}else{
		cerr<<"Error: No intersection could be evalued."<<endl;
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : intersection of two 2 dimensional planes in 4 dimensional space, with no intersection"<<endl;

	cout<<"vecBaseD4={1, 8, 4, 0}"<<endl;
	vecBaseD4[ 0 ] = 1;
	vecBaseD4[ 1 ] = 8;
	vecBaseD4[ 2 ] = 4;
	vecBaseD4[ 3 ] = 0;
	cout<<"vecDirectionsD4={{1, 0, 0.5 ,0}{0, 0, 0, 1}}"<<endl;
	vecDirectionsD4.clear();
	vecDirectionD4[ 0 ] = 1;
	vecDirectionD4[ 1 ] = 0;
	vecDirectionD4[ 2 ] = 0.5;
	vecDirectionD4[ 3 ] = 0;
	vecDirectionsD4.push_back( vecDirectionD4 );
	vecDirectionD4[ 0 ] = 0;
	vecDirectionD4[ 1 ] = 0;
	vecDirectionD4[ 2 ] = 0;
	vecDirectionD4[ 3 ] = 1;
	vecDirectionsD4.push_back( vecDirectionD4 );
	cout<<"cHyperplane< double > hyperplaneD4_9( vecBaseD4, vecDirectionsD4 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD4_9( vecBaseD4, vecDirectionsD4);

	cout<<"vecBaseD4={2, 4, 8, 4}"<<endl;
	vecBaseD4[ 0 ] = 2;
	vecBaseD4[ 1 ] = 4;
	vecBaseD4[ 2 ] = 8;
	vecBaseD4[ 3 ] = 4;
	cout<<"vecDirectionsD4={{1, 0, 0.5, 2}{0, 1, 0, 0.5}}"<<endl;
	vecDirectionsD4.clear();
	vecDirectionD4[ 0 ] = 1;
	vecDirectionD4[ 1 ] = 0;
	vecDirectionD4[ 2 ] = 0.5;
	vecDirectionD4[ 3 ] = 2;
	vecDirectionsD4.push_back( vecDirectionD4 );
	vecDirectionD4[ 0 ] = 0;
	vecDirectionD4[ 1 ] = 1;
	vecDirectionD4[ 2 ] = 0;
	vecDirectionD4[ 3 ] = 0.5;
	vecDirectionsD4.push_back( vecDirectionD4 );
	cout<<"cHyperplane< double > hyperplaneD4_10( vecBaseD4, vecDirectionsD4 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD4_10( vecBaseD4, vecDirectionsD4);

	cout<<"pHyperplaneD4Inters = hyperplaneD4_10.evalueIntersection( hyperplaneD4_9 );"<<endl<<endl;
	pHyperplaneD4Inters = hyperplaneD4_10.evalueIntersection( hyperplaneD4_9 );
	
	if ( pHyperplaneD4Inters != NULL ){
		
		cerr<<"Error: An intersection hyperplanes could be evalued."<<endl;
		cerr<<"Hyperplane 1:"<<endl;
		hyperplaneD4_9.print( cerr );
		cerr<<endl<<"Hyperplane 2:"<<endl;
		hyperplaneD4_10.print( cerr );
		cerr<<endl<<"Intersection:"<<endl;
		pHyperplaneD4Inters->print( cerr );
		cerr<<endl;
		iReturn++;
		delete pHyperplaneD4Inters;
	}else{
		cout<<"The intersection of the hyperplanes could correctly not be evalued. "<<endl;
	}



//#ifdef TODO_COMMENT_IN
/*intersect hyperplane with an equal hyperplane
	- create random hyperplane H
	- create copy of hyperplane Hc and change it by:
	-- add to base vector random combination of multiple of direction vectors
	-- replace direction vectors with multiple of them
	-- create new direction vectors by combining multiple of the old direction vectors
	-- replace direction vectors by an permutation of them
	- intersect hyperplane H and change copy Hc of it
	- intersection should be equal to the random hyperplane H
*/
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : intersection two equal hyperplanes (intersection is the hyperplanes)"<<endl;
	
	for ( unsigned int uiIteration = 0; uiIteration < (MAX_ITERATION / 8 + 1); uiIteration++ ){
		
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : intersection two equal hyperplanes, iteration: "<<uiIteration<<endl;
		//create random hyperplane H=hyperplaneD3_rand1
		unsigned int uiNumberOfDimensions = (rand() % (rand() % 64 + 1) );
		
		vector< double > vecBase( uiNumberOfDimensions, 0.0 );
		for ( unsigned int uiActualDimension = 0; 
				uiActualDimension < uiNumberOfDimensions; uiActualDimension++ ){
			
			if ( rand() % 4 ){
				//generate random double number
				vecBase[ uiActualDimension ] = (((double)rand()) * ((double)rand()) -
					(256.0 * 256.0 * 256.0 * 256.0)) / ((double)( rand() + 1 ));
			}else{//generate random integer number
				vecBase[ uiActualDimension ] = rand() - (256 * 256);
			}
		}
		vector< vector< double > > vecDirections;
		const unsigned int uiDirectionsToGenerate = ( rand() % ((rand() % 128) + 1) ) % ((rand() % 128) + 1);
		for( unsigned int uiActualDirection = 0;
				uiActualDirection < uiDirectionsToGenerate; uiActualDirection++ ){
			
			vector< double > vecDirection( uiNumberOfDimensions, 0.0 );
			for ( unsigned int uiActualDimension = 0;
					uiActualDimension < uiNumberOfDimensions; uiActualDimension++ ){
				
				if ( rand() % 4 ){
					//generate random double number
					vecDirection[ uiActualDimension ] = (((double)rand()) * ((double)rand()) -
						(256.0 * 256.0 * 256.0 * 256.0)) / ((double)( rand() + 1 ));
				}else{//generate random integer number
					vecDirection[ uiActualDimension ] = randIntFactor();
				}
			}
			vecDirections.push_back( vecDirection );
		}
		if ( ! vecDirections.empty()  ){

			const unsigned int uiNumberOfDirections = vecDirections.size();
			cout<<"create new direction vectors by combining multiple of the old direction vectors"<<endl<<flush;
			const unsigned int uiDirectionsToGenerateNew = ( rand() % ((rand() % 64) + 1) ) % ((rand() % 64) + 1);
			for( unsigned int uiActualDirection = 0;
					uiActualDirection < uiDirectionsToGenerateNew; uiActualDirection++ ){
				//take some random vector as the base direction vector
				vector< double > vecDirection = vecDirections[ rand() % vecDirections.size() ];
				
				for( unsigned int uiActualDirection = 0;
						uiActualDirection < uiNumberOfDirections; uiActualDirection++ ){
					
					if ( rand() % 4 ){
						//add some directions
						continue;
					}
					const double dFactor = randIntFactor();
					if ( isEqualNull( dFactor ) ){
						continue;
					}
					for ( unsigned int uiActualDimension = 0;
							uiActualDimension < uiNumberOfDimensions; uiActualDimension++ ){
						
						addToFirst( vecDirection[ uiActualDimension ], dFactor *
							vecDirections[ uiActualDirection ][ uiActualDimension ] );
					}
				}
				vecDirections.push_back( vecDirection );
			}
		}
		cout<<"cHyperplane< double > hyperplane_rand1( vecBase, vecDirections );"<<endl<<endl;
		const cHyperplane< double > hyperplane_rand1( vecBase, vecDirections );

		//evalue the independent directions
		cHyperplane< double > hyperplane_rand1Independent = hyperplane_rand1;
		hyperplane_rand1Independent.makeDirectionsIndependent();
		vecDirections = hyperplane_rand1Independent.getDirections();
		const unsigned int uiNumberOfDirections = vecDirections.size();
		cout<<"independent directions: "<<uiNumberOfDirections<<endl<<flush;
	//create copy of hyperplane Hc and change it
/*TODO: didn't work because of rounding errors (?)
		cout<<"add to base vector random combination of multiple of direction vectors"<<endl<<flush;
		//add to base vector random combination of multiple of direction vectors
		for( unsigned int uiActualDirection = 0;
				uiActualDirection < uiNumberOfDirections; uiActualDirection++ ){
			
			if ( rand() % 4 ){
				//add some directions
				continue;
			}
			const double dFactor = randIntFactor();
			if ( isEqualNull( dFactor ) ){
				continue;
			}
			
			for ( unsigned int uiActualDimension = 0;
					uiActualDimension < uiNumberOfDimensions; uiActualDimension++ ){
				addToFirst( vecBase[ uiActualDimension ], dFactor *
					vecDirections[ uiActualDirection ][ uiActualDimension ] );
			}
		}
		cout<<"replace direction vectors with multiple of them"<<endl<<flush;
		//replace direction vectors with multiple of them
		for( unsigned int uiActualDirection = 0;
				uiActualDirection < uiNumberOfDirections; uiActualDirection++ ){
			
			if ( rand() % 4 ){
				//add some directions
				continue;
			}
			const double dFactor = randIntFactor();
			if ( isEqualNull( dFactor ) ){
				continue;
			}
			
			for ( unsigned int uiActualDimension = 0;
					uiActualDimension < uiNumberOfDimensions; uiActualDimension++ ){
				vecDirections[ uiActualDirection ][ uiActualDimension ] *= dFactor;
			}
		}
*/
		//create new direction vectors by combining multiple of the old direction vectors
		if ( ! vecDirections.empty()  ){
			cout<<"create new direction vectors by combining multiple of the old direction vectors"<<endl<<flush;
			const unsigned int uiDirectionsToGenerateNew = ( rand() % ((rand() % 64) + 1) ) % ((rand() % 64) + 1);
			for( unsigned int uiActualDirection = 0;
					uiActualDirection < uiDirectionsToGenerateNew; uiActualDirection++ ){
				//take some random vector as the base direction vector
				vector< double > vecDirection = vecDirections[ rand() % vecDirections.size() ];
				
/*TODO: didn't work because of rounding errors (?)
				for( unsigned int uiActualDirection = 0;
						uiActualDirection < uiNumberOfDirections; uiActualDirection++ ){
					
					if ( rand() % 4 ){
						//add some directions
						continue;
					}
					const double dFactor = randIntFactor();
					if ( isEqualNull( dFactor ) ){
						continue;
					}
					for ( unsigned int uiActualDimension = 0;
							uiActualDimension < uiNumberOfDimensions; uiActualDimension++ ){
						
						addToFirst( vecDirection[ uiActualDimension ], dFactor *
							vecDirections[ uiActualDirection ][ uiActualDimension ] );
					}
				}
*/
				vecDirections.push_back( vecDirection );
			}
/*TODO: didn't work because of rounding errors (?)
			//replace direction vectors by an permutation of them
			cout<<"replace direction vectors by an permutation of them"<<endl<<flush;
			const unsigned int uiNumberOfDirectionsNew = vecDirections.size();
			for( unsigned int uiActualDirection = 0;
					uiActualDirection < (uiNumberOfDirectionsNew * 4); uiActualDirection++ ){
				//switch random directions
				const unsigned int uiDirection1 = rand() % vecDirections.size();
				const unsigned int uiDirection2 = rand() % vecDirections.size();
				if ( uiDirection1 == uiDirection2 ){
					continue;
				}
				const vector< double > vecDirectionTmp = vecDirections[ uiDirection1 ];
				vecDirections[ uiDirection1 ] = vecDirections[ uiDirection2 ];
				vecDirections[ uiDirection2 ] = vecDirectionTmp;
			}
*/
		}
		
		cout<<"cHyperplane< double > hyperplane_rand2( vecBase, vecDirections );"<<endl<<flush<<endl;
		const cHyperplane< double > hyperplane_rand2( vecBase, vecDirections );
		
		cout<<"Random hyperplane 1:"<<endl;
		hyperplane_rand1.print( cout );
		cout<<endl<<"Random hyperplane 2:"<<endl;
		hyperplane_rand2.print( cout );
		
		//intersect hyperplane H and change copy Hc of it
		cout<<endl<<"Evaluing intersection (which should be equal to both hyperplanes):"<<endl<<flush;
		cHyperplane< double > * pHyperplaneInters = NULL;
		if ( rand() % 2 ){
			cout<<"pHyperplaneInters = hyperplane_rand2.evalueIntersection( hyperplane_rand1 );"<<endl<<endl<<flush;
			pHyperplaneInters = hyperplane_rand2.evalueIntersection( hyperplane_rand1 );
		}else{
			cout<<"pHyperplaneInters = hyperplane_rand1.evalueIntersection( hyperplane_rand2 );"<<endl<<endl<<flush;
			pHyperplaneInters = hyperplane_rand1.evalueIntersection( hyperplane_rand2 );
		}
		
		if ( pHyperplaneInters != NULL ){
			if ( hyperplane_rand1.equal( *pHyperplaneInters ) ){
			
				//intersection should be equal to the random hyperplane H
				cout<<"The intersection of the hyperplanes is correctly equal to the line hyperplane_rand1. "<<endl<<flush;
			}else{
				cerr<<"Error: The intersection of the hyperplanes is not equal to the line hyperplane_rand1."<<endl<<flush;
				cerr<<endl<<"Intersection:"<<endl;
				pHyperplaneInters->print( cerr );
				
				cout<<endl<<"Random hyperplane 1 form one:"<<endl;
				cHyperplane< double > hyperplane_rand1_formOne = hyperplane_rand1;
				hyperplane_rand1_formOne.convertToFormOne();
				hyperplane_rand1_formOne.print( cout );
				cout<<endl<<"Random hyperplane 2 form one:"<<endl;
				cHyperplane< double > hyperplane_rand2_formOne = hyperplane_rand2;
				hyperplane_rand2_formOne.convertToFormOne();
				hyperplane_rand2_formOne.print( cout );
				cerr<<endl;
				iReturn++;
			}
			delete pHyperplaneInters;
		}else{
			cerr<<"Error: No intersection could be evalued."<<endl<<flush;
			iReturn++;
		}
	}
	

/*intersect hyperplane wher one hyperplane is part of the other
	- create random hyperplane H
	- create copy of hyperplane Hc and change it by:
	-- add to base vector random combination of multiple of direction vectors
	-- remove some direction vectors
	-- replace direction vectors with multiple of them
	-- create new direction vectors by combining multiple of the old direction vectors
	-- replace direction vectors by an permutation of them
	- intersect hyperplane H and change copy Hc of it
	- intersection should be equal to the random hyperplane H
*/
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : intersection two hyperplanes, wher one hyperplane is part of the other"<<endl;
	for ( unsigned int uiIteration = 0; uiIteration < (MAX_ITERATION / 8 + 1); uiIteration++ ){
		
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : intersection two hyperplanes, wher one hyperplane is part of the other, iteration: "<<uiIteration<<endl;
		//create random hyperplane H=hyperplaneD3_rand1
		unsigned int uiNumberOfDimensions = (rand() % (rand() % 64 + 1) );
		
		vector< double > vecBase( uiNumberOfDimensions, 0.0 );
		for ( unsigned int uiActualDimension = 0; 
				uiActualDimension < uiNumberOfDimensions; uiActualDimension++ ){
			
			if ( rand() % 4 ){
				//generate random double number
				vecBase[ uiActualDimension ] = (((double)rand()) * ((double)rand()) -
					(256.0 * 256.0 * 256.0 * 256.0)) / ((double)( rand() + 1 ));
			}else{//generate random integer number
				vecBase[ uiActualDimension ] = rand() - (256 * 256);
			}
		}
		vector< vector< double > > vecDirections;
		const unsigned int uiDirectionsToGenerate = ( rand() % ((rand() % 128) + 1) ) % ((rand() % 128) + 1);
		for( unsigned int uiActualDirection = 0;
				uiActualDirection < uiDirectionsToGenerate; uiActualDirection++ ){
			
			vector< double > vecDirection( uiNumberOfDimensions, 0.0 );
			for ( unsigned int uiActualDimension = 0; 
					uiActualDimension < uiNumberOfDimensions; uiActualDimension++ ){
				
				if ( rand() % 4 ){
					//generate random double number
					vecDirection[ uiActualDimension ] = (((double)rand()) * ((double)rand()) -
						(256.0 * 256.0 * 256.0 * 256.0)) / ((double)( rand() + 1 ));
				}else{//generate random integer number
					vecDirection[ uiActualDimension ] = rand() - (256 * 256);
				}
			}
			vecDirections.push_back( vecDirection );
		}
		
		cout<<"cHyperplane< double > hyperplane_rand1( vecBase, vecDirections );"<<endl<<endl;
		const cHyperplane< double > hyperplane_rand1( vecBase, vecDirections );

/*TODO: didn't work because of rounding errors (?)
	//create copy of hyperplane Hc and change it
		cout<<"add to base vector random combination of multiple of direction vectors"<<endl<<flush;
		//add to base vector random combination of multiple of direction vectors
		for( unsigned int uiActualDirection = 0;
				uiActualDirection < uiDirectionsToGenerate; uiActualDirection++ ){
			
			if ( rand() % 4 ){
				//add some directions
				continue;
			}
			const double dFactor = randIntFactor();
			if ( isEqualNull( dFactor ) ){
				continue;
			}
			
			for ( unsigned int uiActualDimension = 0;
					uiActualDimension < uiNumberOfDimensions; uiActualDimension++ ){
				
				addToFirst( vecBase[ uiActualDimension ], dFactor *
					vecDirections[ uiActualDirection ][ uiActualDimension ] );
			}
		}
*/
		if ( ! vecDirections.empty()  ){
			//remove some direction vectors
			const unsigned uiNumberOfDirectionsToRemove = ( rand() % vecDirections.size() ) + 1;
			cout<<"removing "<<uiNumberOfDirectionsToRemove<<" direction vectors"<<endl<<flush;
			
			for( unsigned int uiRemovedDirections = 0;
					uiRemovedDirections < uiNumberOfDirectionsToRemove;
					uiRemovedDirections++ ){
				
				const unsigned int uiDirectionToRemove = rand() % vecDirections.size();
				//find direction to remove
				vector< vector< double > >::iterator itrDirectionToRemove =
					vecDirections.begin();
				for( unsigned int uiActualDirection = 0;
						(uiActualDirection < uiDirectionToRemove) &&
						(itrDirectionToRemove != vecDirections.end());
						uiActualDirection++, itrDirectionToRemove++ ){
					//nothing to do
				}
				if ( itrDirectionToRemove != vecDirections.end() ){
					//remove direction
					vecDirections.erase( itrDirectionToRemove );
				}
			}
		}
		if ( ! vecDirections.empty()  ){
/*TODO: didn't work because of rounding errors (?)
			cout<<"replace direction vectors with multiple of them"<<endl<<flush;
			const unsigned int uiNumberOfDirections = vecDirections.size();
			//replace direction vectors with multiple of them
			for( unsigned int uiActualDirection = 0;
					uiActualDirection < uiNumberOfDirections; uiActualDirection++ ){
				
				if ( rand() % 4 ){
					//add some directions
					continue;
				}
				const double dFactor = randIntFactor();
				if ( isEqualNull( dFactor ) ){
					continue;
				}
				
				for ( unsigned int uiActualDimension = 0;
						uiActualDimension < uiNumberOfDimensions; uiActualDimension++ ){
					vecDirections[ uiActualDirection ][ uiActualDimension ] *= dFactor;
				}
			}
*/
			//create new direction vectors by combining multiple of the old direction vectors
/*TODO: didn't work because of rounding errors (?)
			cout<<"create new direction vectors by combining multiple of the old direction vectors"<<endl<<flush;
			const unsigned int uiDirectionsToGenerateNew = ( rand() % ((rand() % 64) + 1) ) % ((rand() % 64) + 1);
			for( unsigned int uiActualDirection = 0;
					uiActualDirection < uiDirectionsToGenerateNew; uiActualDirection++ ){
				//take some random vector as the base direction vector
				vector< double > vecDirection = vecDirections[ rand() % vecDirections.size() ];
				
				for( unsigned int uiActualDirection = 0;
						uiActualDirection < uiNumberOfDirections; uiActualDirection++ ){
					
					if ( rand() % 4 ){
						//add some directions
						continue;
					}
					const double dFactor = randIntFactor();
					if ( isEqualNull( dFactor ) ){
						continue;
					}
					for ( unsigned int uiActualDimension = 0;
							uiActualDimension < uiNumberOfDimensions; uiActualDimension++ ){
						
						addToFirst( vecDirection[ uiActualDimension ], dFactor *
							vecDirections[ uiActualDirection ][ uiActualDimension ] );
					}
				}
				vecDirections.push_back( vecDirection );
			}
*/
/*TODO: didn't work because of rounding errors (?)
			//replace direction vectors by an permutation of them
			cout<<"replace direction vectors by an permutation of them"<<endl<<flush;
			const unsigned int uiNumberOfDirectionsNew = vecDirections.size();
			for( unsigned int uiActualDirection = 0;
					uiActualDirection < (uiNumberOfDirectionsNew * 4);
					uiActualDirection++ ){
				//switch random directions
				const unsigned int uiDirection1 = rand() % uiNumberOfDirectionsNew;
				const unsigned int uiDirection2 = rand() % uiNumberOfDirectionsNew;
				if ( uiDirection1 == uiDirection2 ){
					continue;
				}
				const vector< double > vecDirectionTmp = vecDirections[ uiDirection1 ];
				vecDirections[ uiDirection1 ] = vecDirections[ uiDirection2 ];
				vecDirections[ uiDirection2 ] = vecDirectionTmp;
			}
*/
		}

		cout<<"cHyperplane< double > hyperplane_rand2( vecBase, vecDirections );"<<endl<<flush<<endl;
		const cHyperplane< double > hyperplane_rand2( vecBase, vecDirections );
		
		cout<<"Random hyperplane 1:"<<endl;
		hyperplane_rand1.print( cout );
		cout<<endl<<"Random hyperplane 2:"<<endl;
		hyperplane_rand2.print( cout );
		
		//intersect hyperplane H and change copy Hc of it
		cout<<endl<<"Evaluing intersection:"<<endl<<flush;
		cHyperplane< double > * pHyperplaneInters = NULL;
		if ( rand() % 2 ){
			cout<<"pHyperplaneInters = hyperplane_rand2.evalueIntersection( hyperplane_rand1 );"<<endl<<endl<<flush;
			pHyperplaneInters = hyperplane_rand2.evalueIntersection( hyperplane_rand1 );
		}else{
			cout<<"pHyperplaneInters = hyperplane_rand1.evalueIntersection( hyperplane_rand2 );"<<endl<<endl<<flush;
			pHyperplaneInters = hyperplane_rand1.evalueIntersection( hyperplane_rand2 );
		}
		
		if ( pHyperplaneInters != NULL ){
			if ( hyperplane_rand2.equal( *pHyperplaneInters ) ){
			
				//intersection should be equal to the random hyperplane H
				cout<<"The intersection of the hyperplanes is correctly equal to the line hyperplane_rand2. "<<endl<<flush;
			}else{
				cerr<<"Error: The intersection of the hyperplanes is not equal to the line hyperplane_rand2."<<endl<<flush;
				cerr<<endl<<"Intersection:"<<endl;
				pHyperplaneInters->print( cerr );
				cerr<<endl;
				iReturn++;
			}
			delete pHyperplaneInters;
		}else{
			cerr<<"Error: No intersection could be evalued."<<endl<<flush;
			iReturn++;
		}
	}
//#endif //TODO_COMMENT_IN
		
/*TODO
create two random hyperplanes + create ther intersection
	- check if the intersection of them has as the intersection with them itself
*/

	return iReturn;
}



/**
 * This function evalues the dot product of the two given vectors.
 * (dotProduct = vector1[0] * vector2[0] + ... + vector1[n] * vector2[n]
 * n = vector1.size() )
 *
 * @param vector1 the first vector to evalue the dot product for
 * @param vector1 the second vector to evalue the dot product for
 * @return the dot product of the two given vectors
 */
template< class tDouble > tDouble dotProduct( const vector<tDouble> & vector1,
		const vector<tDouble> & vector2 ){
	
	unsigned int uiNumberOfOlements = min( vector1.size(), vector2.size() );
	tDouble dDotProduct = ((tDouble)(0.0));
	
	for ( unsigned int uiActualElement = 0;
			uiActualElement < uiNumberOfOlements; uiActualElement++ ){
		
		const tDouble actualFactor = vector1[ uiActualElement ] * vector2[ uiActualElement ];
		
		if ( ! ( compareDouble( dDotProduct, ((tDouble)(-1)) * actualFactor ) ) ){
			dDotProduct += actualFactor;
		}else{//the dot product is 0
			dDotProduct = ((tDouble)(0.0));
		}
	}
	return dDotProduct;
}


/**
 * This function checks if the given hyperplane is in one form and equal
 * to the original hyperplane.
 * Hyperplane form: Y = B + D_1 * x_1 + D_2 * x_2 + ... + D_d * x_d
 * In form One:
 * 	- B point on the hyperplane as the base vector, with |B| minimal
 * 	- D_i are the independent hyperplane direction vectors
 * 		D_i = ( h_i.1, ..., h_i.{o_i}, ..., h_i.d )^T
 * 		with h_i.1= ...= h_i.o_i - 1} = 0, h_i.{o_i} = 1 and
 * 		o_{i-1} \< o_i, for 1 \< i (o_{i-1} is for D_{i-1} )
 *
 * @param hyperplaneInOneForm the hyperplane which should be in one form
 * @param originalHyperplane the original hyperplane, which was
 * 	transformed into the one form
 * @return the number of errors ocured in this test
 */
template< class tDouble > int checkOneForm(
		const cHyperplane< tDouble > & hyperplaneInOneForm,
		const cHyperplane< tDouble > & originalHyperplane ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	//check if the hyperplane is equal to the original hyperplane
	if ( ! hyperplaneInOneForm.equal( originalHyperplane ) ){
		cerr<<"Error: The hyperplane is not equal to the original hyperplane ."<<endl;
		iReturn++;
	}
	//check if the dimensionality is equal with that of the original hyperplane
	const unsigned int uiNumberOfDimensions =
		originalHyperplane.getNumberOfDimensions();
	if ( hyperplaneInOneForm.getNumberOfDimensions() != uiNumberOfDimensions ){
		
		cerr<<"Error: The hyperplane has the wrong number of dimensions."<<endl;
		cerr<<"   it is: "<< hyperplaneInOneForm.getNumberOfDimensions() <<
			", but should be: "<< uiNumberOfDimensions <<endl;
		iReturn++;
	}
	const vector< vector< tDouble > > directionVectors =
		hyperplaneInOneForm.getDirections();
	const unsigned int uiNumberOfDirections = directionVectors.size();
	const vector< tDouble > vecBase = hyperplaneInOneForm.getBase();
	
	if ( vecBase.size() != uiNumberOfDimensions ){
		
		cerr<<"Error: The hyperplane base vector has the wrong number of dimensions."<<endl;
		cerr<<"   it is: "<< vecBase.size() <<", but should be: "<< uiNumberOfDimensions <<endl;
		iReturn++;
	}
	for ( unsigned int uiActualDirection = 0;
			uiActualDirection < uiNumberOfDirections; uiActualDirection++ ){
		
		if ( directionVectors[ uiActualDirection ].size() != uiNumberOfDimensions ){
			
			cerr<<"Error: The hyperplane "<<uiActualDirection<<
				"'th direction has the wrong number of dimensions."<<endl;
			cerr<<"   it is: "<< directionVectors[ uiActualDirection ].size() <<
				", but should be: "<< uiNumberOfDimensions <<endl;
			iReturn++;
		}
	}
	
	//check if the base vector is in the original hyperplane (check with intersection)
	cHyperplane< tDouble > pointForBaseVector( vecBase, vector< vector< tDouble > >() );
	cHyperplane< tDouble > * pIntersection = originalHyperplane.evalueIntersection(
		pointForBaseVector );
	
	if ( pIntersection == NULL ){
		cerr<<"Error: The base vector of the hyperplane is not in the original hyperplane."<<endl;
		iReturn++;
	}else{
		if ( ! pointForBaseVector.equal( *pIntersection ) ){
			cerr<<"Error: The base vector of the hyperplane is not in the original "<<
				"hyperplane. (error intersetion evalued wrong)"<<endl;
			iReturn++;
		}
		delete pIntersection;
	}
	//check if the base vector is at rigth angle (have the vector product 0) to all direction vectors
	for ( unsigned int uiActualDirection = 0;
			uiActualDirection < uiNumberOfDirections; uiActualDirection++ ){
		
		if ( dotProduct( vecBase , directionVectors[ uiActualDirection ] ) != 0 ){
			cerr<<"Error: The "<<uiActualDirection<<"'th direction of the "<<
				"hyperplane is not at rigth angle with the base vector."<<endl;
			iReturn++;
		}
	}
	//check if all vectors in the hyperplane are at rigth angle (have the vector product 0) to one another
	for ( unsigned int uiActualDirection1 = 0;
			uiActualDirection1 < uiNumberOfDirections; uiActualDirection1++ ){
		
		for ( unsigned int uiActualDirection2 = uiActualDirection1 + 1;
				uiActualDirection2 < uiNumberOfDirections; uiActualDirection2++ ){
		
			if ( dotProduct( directionVectors[ uiActualDirection1 ],
					directionVectors[ uiActualDirection2 ] ) != 0 ){
				cerr<<"Error: The "<<uiActualDirection1<<"'th direction of the "<<
					"hyperplane is not at rigth angle with the "<<
					uiActualDirection2<<"'th direction vector."<<endl;
				iReturn++;
			}
		}
	}
	//check if the direction vectors have ther first 1 later as the previos direction vector
	unsigned int uiFirstOne = 0;
	
	for ( unsigned int uiActualElement = 0;
			uiActualElement < directionVectors[ 0 ].size() ; uiActualElement++ ){
		
		if ( directionVectors[ 0 ][ uiActualElement ] == ((tDouble)(0.0)) ){
			continue;//check next element
		}//else
		if ( compareDouble( directionVectors[ 0 ][ uiActualElement ], ((tDouble)(1)) ) ){
			//actual element is 1
			uiFirstOne = uiActualElement;
			break;
		}//else
		cerr<<"Error: The "<<0<<"'th direction of the hyperplane has as the "<<
			uiActualElement<<"'th element "<< directionVectors[ 0 ][ uiActualElement ]<<
			" , but should have 1."<<endl;
		iReturn++;
	}
	for ( unsigned int uiActualDirection = 1;
			uiActualDirection < uiNumberOfDirections; uiActualDirection++ ){
		
		for ( unsigned int uiActualElement = 0;
				uiActualElement < directionVectors[ uiActualDirection ].size() ; uiActualElement++ ){
			
			if ( directionVectors[ uiActualDirection ][ uiActualElement ] == ((tDouble)(0.0)) ){
				continue;//check next element
			}//else
			if ( compareDouble( directionVectors[ uiActualDirection ][ uiActualElement ], ((tDouble)(1)) ) ){
				//actual element is 1
				if ( uiActualElement <= uiFirstOne ){
					cerr<<"Error: The "<<uiActualDirection<<"'th direction of the hyperplane has as the "<<
						uiActualElement<<"'th element 1 , but the "<<(uiActualDirection - 1)<<
						"'th direction has it allready as the "<<uiFirstOne<<"'th element."<<endl;
					iReturn++;
				}
				uiFirstOne = uiActualElement;
				break;
			}//else 
			cerr<<"Error: The "<<uiActualDirection<<"'th direction of the hyperplane has as the "<<
				uiActualElement<<"'th element "<<directionVectors[ uiActualDirection ][ uiActualElement ]<<
				" , but should have 1."<<endl;
			iReturn++;
		}
	}
	
	return iReturn;
}


/**
 * This function tests the convertToFormOne() method of the cHyperplane class.
 *
 * methods tested:
 * 	- void convertToFormOne();
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testConvertToFormOne( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the convertToFormOne() method of hyperplanes"<<endl<<endl;
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the convertToFormOne() method of hyperplanes, on hyperplane with 4 dimensions and 3 independent directions"<<endl<<endl;
	
	vector< double > vecBaseD4V1( 4, 1 );
	
	cout<<"vector< vector< double > > vecDirectionsD4;={{1,0,0}{0,1,0}{0,0,1}}"<<endl;
	vector< vector< double > > vecDirectionsD4;
	vector< double > vecDirectionD4( 4, 0.0 );
	vecDirectionD4[ 0 ] = 1;
	vecDirectionsD4.push_back( vecDirectionD4 );
	vecDirectionD4[ 0 ] = 0;
	vecDirectionD4[ 1 ] = 1;
	vecDirectionsD4.push_back( vecDirectionD4 );
	vecDirectionD4[ 1 ] = 0;
	vecDirectionD4[ 2 ] = 1;
	vecDirectionsD4.push_back( vecDirectionD4 );

	cout<<"cHyperplane< double > hyperplaneD4( vecBaseD4V1, vecDirectionsD4 );"<<endl<<endl;
	cHyperplane< double > hyperplaneD4( vecBaseD4V1, vecDirectionsD4 );
	
	const cHyperplane< double > hyperplaneD4Org = hyperplaneD4;

	cout<<"hyperplaneD4.convertToFormOne();"<<endl<<endl;
	hyperplaneD4.convertToFormOne();
	
	iReturn += checkOneForm( hyperplaneD4, hyperplaneD4Org );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : create random hyperplanes, convert and check one form "<<endl;
	
	//create random hyperplanes, convert and check one form
	for ( unsigned int uiIteration = 0; uiIteration < MAX_ITERATION; uiIteration++ ){
		
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : create random hyperplanes, convert and check one form, iteration: "<<uiIteration<<endl;
		//create random hyperplane H=hyperplaneD3_rand1
		unsigned int uiNumberOfDimensions = (rand() % (rand() % 64 + 1) );
		
		vector< double > vecBase( uiNumberOfDimensions, 0.0 );
		for ( unsigned int uiActualDimension = 0;
				uiActualDimension < uiNumberOfDimensions; uiActualDimension++ ){
			
			if ( rand() % 4 ){
				//generate random double number
				vecBase[ uiActualDimension ] = (((double)rand()) * ((double)rand()) -
					(256.0 * 256.0 * 256.0 * 256.0)) / ((double)( rand() + 1 ));
			}else{//generate random integer number
				vecBase[ uiActualDimension ] = rand() - (256 * 256);
			}
		}
		vector< vector< double > > vecDirections;
		const unsigned int uiDirectionsToGenerate = ( rand() % ((rand() % 128) + 1) ) % ((rand() % 128) + 1);
		for( unsigned int uiActualDirection = 0;
				uiActualDirection < uiDirectionsToGenerate; uiActualDirection++ ){
			
			vector< double > vecDirection( uiNumberOfDimensions, 0.0 );
			for ( unsigned int uiActualDimension = 0; 
					uiActualDimension < uiNumberOfDimensions; uiActualDimension++ ){
				
				if ( rand() % 4 ){
					//generate random double number
					vecDirection[ uiActualDimension ] = (((double)rand()) * ((double)rand()) -
						(256.0 * 256.0 * 256.0 * 256.0)) / ((double)( rand() + 1 ));
				}else{//generate random integer number
					vecDirection[ uiActualDimension ] = rand() - (256 * 256);
				}
			}
			vecDirections.push_back( vecDirection );
		}
		
		cout<<"cHyperplane< double > hyperplane_rand1( vecBase, vecDirections );"<<endl<<endl;
		cHyperplane< double > hyperplane_rand1( vecBase, vecDirections );
		
		cout<<"hyperplane_rand1.convertToFormOne();"<<endl<<endl;
		hyperplane_rand1.convertToFormOne();
		
		cout<<"check one form:"<<endl;
		const int iReturnCheck = checkOneForm( hyperplaneD4, hyperplaneD4Org );
		
		if ( iReturnCheck == 0 ){
			cout<<"   OK"<<endl;
		}else{
			iReturn += iReturnCheck;
		}
	}
/*TODO???
	outside checkOneForm():
		-- the vector of direction vectors are equal
		-- the base vectors are equal
*/
	
	return iReturn;
}





















