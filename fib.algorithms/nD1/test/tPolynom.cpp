/**
 * @file tPolynom
 * file name: tPolynom.cpp
 * @author Betti Oesterholz
 * @date 13.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cPolynom.
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
 * This file contains the test for the class cPolynom, which
 * represents polynoms.
 *
 *
 * What's tested of class cPolynom:
 * 	- tY evalue( const tX & x ) const;
 * 	- void print( ostream & outputStream ) const;
 * 	- pair<unsigned long, tY> evalueError( const vector< cDataPoint< tX, tY> > & vecInput ) const;
 * 	- tY evalueErrorMax( const vector< cDataPoint< tX, tY> > & vecData, const tY maxYError ) const;
 * 	- pair<unsigned long, tY> evalueError( const vector< cDataPointRange< tX, tY> > & vecInput ) const;
 * 	- tY evalueErrorMax( const vector< cDataPointRange< tX, tY> > & vecData, const tY maxYError ) const;
 * 	- vector< cLinearEquation<tY> > createLinearEquations( const vector< cDataPoint< tX, tY> > & vecData, unsigned int uiMaxPolynomOrder ) const;
 * 	- pair< cInequation< tY >, cInequation< tY > > createInequiationsForRangePoint( const cDataPointRange< tX, tY> & dataPoint, unsigned int uiPolynomOrder ) const;
 * 	- template<class tY> cUnderFunction * toFibUnderFunction( cFibVariable * pVariable );
 * 	- void evalue( const vector< cDataPoint< tX, tY> > & vecData );
 * 	-(TODO) tY evalueGoodPolynom( const vector< cDataPointRange< tX, tY> > & vecData, unsigned long ulTimeNeed = 1024 );
 * 	- unsigned long evalueSpline( const vector< cDataPointRange< tX, tY> > & vecData, unsigned int uiNumberOfParameters = 4, const unsigned int uiMinBitsToStoreMantissa = 1 );
  * 	-(TODO) unsigned long evalueSpline( const vector< cDataPointRange< tX, tY> > & vecData, unsigned int uiNumberOfParameters = 4, const unsigned int uiMinBitsToStoreMantissa = 1, const unsigned long ulMaxMemoryCost );
* 	- unsigned long evalueSplineIterativFast( const vector< cDataPointRange< tX, tY> > & vecData, unsigned int uiMaxNumberOfParameters, const unsigned int uiMinBitsToStoreMantissa, const tY maxValue, const tY maxError, const unsigned long ulMaxMemoryCost );
 * 	- bool operator==( const cPolynom<tX, tY> & polynom ) const;
 * 	- bool operator!=( const cPolynom<tX, tY> & polynom ) const;
 *
 *
 * Tested outside of this test:
 * 	- nD1::cPolynom::findFunctionRand() tested with:
 * 		fib.algorithms/test/t_nD1_cPolynom_findPolynomRand.cpp
 *
 *
 * call: tPolynom [ITERATIONS]
 *
 * parameters:
 * 	ITERATIONS
 * 		The iterations for the test with random generated datapoints.
 * 		Standardvalue is 256.
 */
/*
History:
13.02.2011  Oesterholz  created; test of t_nD1_nPolynom.cpp imported
13.02.2011  Oesterholz  test function testEvalueSplineIterativFast() added
29.12.2012  Oesterholz  FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING:
	evalueSpline(): the glp library (extern package) linear solver will be
	used to find a spline for a vector of range data points
*/

//TODO weg
//#define DEBUG


#include "cPolynom.h"

#include "cFibVariable.h"
#include "cUnderFunction.h"
#include "cFunctionValue.h"
#include "cFunctionVariable.h"
#include "cFunctionAdd.h"
#include "cFunctionMult.h"
#include "cFunctionExp.h"

#include <ctime>
#include <algorithm>


using namespace fib;
using namespace std;
using namespace fib::algorithms::nD1;

int testEvalue( unsigned long &ulTestphase );
int testPolynomToFibUnderFunction( unsigned long &ulTestphase );
int testCreateLinearEquations( unsigned long &ulTestphase );
int testCreateInequiationsForRangePoint( unsigned long &ulTestphase );
int testEvaluePolynom( unsigned long &ulTestphase, int & iWarnings );
int testEvalueSpline( unsigned long &ulTestphase, int & iWarnings );
int testEvalueSplineIterativFast( unsigned long &ulTestphase, int & iWarnings );



unsigned long MAX_ITERATION = 256;
//error allways good because of evaluation inexactnesses
const double ERROR_ALLWAYS_OK = 0.0000000001;

int main(int argc,char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured errors
	int iWarnings = 0;//returnvalue of the test; the number of occured warnings
	
	srand( time( NULL ) );

	if ( argc >= 2 ){
		//one parameter given; read parameter iterations
		MAX_ITERATION = atol( argv[1] );
		if ( MAX_ITERATION < 1 ){
			MAX_ITERATION = 1;
		}
	}

	cout<<endl<<"Running Test for cPolynom methods"<<endl;
	cout<<      "================================="<<endl;

	iWarnings += testEvalue( ulTestphase );
	iReturn += testPolynomToFibUnderFunction( ulTestphase );
	iReturn += testCreateLinearEquations( ulTestphase );
	iReturn += testCreateInequiationsForRangePoint( ulTestphase );
	iReturn += testEvaluePolynom( ulTestphase, iWarnings );
	iReturn += testEvalueSpline( ulTestphase, iWarnings );
	iReturn += testEvalueSplineIterativFast( ulTestphase, iWarnings );



	if ( (iReturn == 0) && ( iWarnings == 0 ) ){
	
		cout<<endl<<endl<<"Test successfull: no errors or warnings occoured"<<endl;
	}else if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Warning: No errors but "<<iWarnings<<" warnings occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors and "<<iWarnings<<" warnings occoured"<<endl;
	}

	return iReturn;
};




/**
 * This functions compares two double numbers.
 * Really small differences will be ignored.
 *
 * @param dValue1 the first number to compare
 * @param dValue2 the second number to compare
 * @return true if the first number is equal to the second, else false
 */
bool compareDoubleTest( const double & dValue1, const double & dValue2 ){
	
	if ( (-0.0000001 < dValue1) && ( dValue1 < 0.0000001 ) ){
		//both 0 ?
		return (-0.0000001 < dValue2) && ( dValue2 < 0.0000001 );
	}
	const double dDiff = absF( 0.0000001 * dValue1 );

	return ( dValue1 - dDiff < dValue2 ) && ( dValue2 < dValue1 + dDiff );
}


/**
 * This functions compares two double numbers.
 * Really small differences will be ignored.
 *
 * @param dValue1 the first number to compare
 * @param dValue2 the second number to compare
 * @return true if the first number is equal to the second, else false
 */
bool compareDoubleTest( const float & dValue1, const float & dValue2 ){
	
	if ( isEqualNull( dValue1 ) ){
		//both 0 ?
		return ( isEqualNull( dValue2 ) );
	}
	const double dDiff = absF( 0.00001 * dValue1 );

	return ( dValue1 - dDiff < dValue2 ) && ( dValue2 < dValue1 + dDiff );
}


/**
 * @param maxValue the maximum value to generate
 * @return a random integer value betwean -uiMaxValue and uiMaxValue
 */
int randomValue( int iMaxValue ){

	return ( rand() % (iMaxValue * 2 + 1) ) - iMaxValue;
}


/**
 * @param maxValue the maximum value to generate
 * @return a random floating point value betwean -uiMaxValue and uiMaxValue
 */
float randomValue( const float & maxValue ){
	
	const float fMaxValue = ( 1 < maxValue ) ? maxValue : 1;
	const long long lMaxValueSqr = fMaxValue * fMaxValue;
	
	return ((float)((((long long)(rand()) * ((long long)(rand()) + ((long long)(rand())))) %
			(lMaxValueSqr * 32 + 1) ) - lMaxValueSqr)) / (fMaxValue * 32);
}


/**
 * @param maxValue the maximum value to generate
 * @return a random floating point value betwean -uiMaxValue and uiMaxValue
 */
double randomValue( const double & maxValue ){
	
	const double dMaxValue = ( 1 < maxValue ) ? maxValue : 1;
	const long long lMaxValueSqr = dMaxValue * dMaxValue;
	
	return ((double)((((long long)(rand()) * ((long long)(rand()) + ((long long)(rand())))) %
			(lMaxValueSqr * 32 + 1) ) - lMaxValueSqr)) / (dMaxValue * 32);
}


/**
 * This function tests the mothods for evaluing the polynom of the class
 * cPolynom for a given polynom.
 *
 * metods tested:
 * 	- tY evalue( const tX & x ) const;
 * 	- pair<unsigned long, tY> evalueError( const vector< cDataPoint< tX, tY> > & vecInput ) const;
 * 	- tY evalueErrorMax( const vector< cDataPoint< tX, tY> > & vecData, const tY maxYWarning ) const;
 * 	- pair<unsigned long, tY> evalueError( const vector< cDataPointRange< tX, tY> > & vecInput ) const;
 * 	- tY evalueErrorMax( const vector< cDataPointRange< tX, tY> > & vecData, const tY maxYWarning ) const;
 *
 * @param polynom the polynom for wich to check the evalue methods
 * @param vecX a vector with the x (input) values for the polynom to evalue
 * @param vecCorrectY a vector with the correct y (output) values to
 * 	which the given vecX values should be evalued by the given polynom:
 * 		vecCorrectY[i] = polynom.evalue( vecX[i] )
 * @return the number of warnings occured in the test
 */
template< class tX, class tY > int testEvalue( const cPolynom< tX, tY > & polynom,
		const vector< tX > vecX, const vector< tY > vecCorrectY ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Warnings
	//check the evalue function
	int iWarningsEvalue = 0;
	cout<<"Checking evalue() method:"<<endl;
	const unsigned int uiNumberOfGivenValues =
		min( vecX.size(), vecCorrectY.size() );
	for ( unsigned int uiActualValue = 0;
			uiActualValue < uiNumberOfGivenValues; uiActualValue++ ){
		
		if ( polynom.evalue( vecX[ uiActualValue ] ) != vecCorrectY[ uiActualValue ] ){
			cerr<<"Warning: The value "<< vecX[ uiActualValue ] <<
				" is evalued to "<< polynom.evalue( vecX[ uiActualValue ] ) <<
				", but should be evalued to "<< vecCorrectY[ uiActualValue ] <<" ."<<endl;
			iWarningsEvalue++;
		}
	}
	if ( iWarningsEvalue == 0 ){
		cout<<"   OK"<<endl;
	}else{
		iReturn++;
	}
	//test evalueError() and evalueErrorMax()
	cout<<"Checking evalueError() and evalueErrorMax() methods:"<<endl;
	int iWarningsEvalueWarning = 0;
	vector< cDataPoint< tX, tY> > vecInputData;
	for ( unsigned int uiActualValue = 0;
			uiActualValue < uiNumberOfGivenValues; uiActualValue++ ){
		
		vecInputData.push_back( cDataPoint< tX, tY >( vecX[ uiActualValue ],
			 vecCorrectY[ uiActualValue ] ) );
	}
	
	pair<unsigned long, tY> paWarning = polynom.evalueError( vecInputData );
	if ( ( paWarning.first != 0 ) || ( paWarning.second != ((tY)(0)) ) ){
		cerr<<"Warning: The method evalueError() of the polynom evalues "<<
			paWarning.first<<" wrong data points with a error sum of "<<
			paWarning.second<<" on the input data (wich should be correct) ."<<endl;
		iWarningsEvalueWarning++;
	}
	tY error = polynom.evalueErrorMax( vecInputData, 10 );
	if ( error != ((tY)(0))  ){
		cerr<<"Warning: The method evalueErrorMax() of the polynom evalues "<<
			" a error sum of "<<error<<" on the input data (wich should be correct) ."<<endl;
		iWarningsEvalueWarning++;
	}
	//evalue on random generated data
	for ( unsigned int iteration = 0; iteration < MAX_ITERATION; iteration++ ){
		//generate random data points and check them
		unsigned int uiPointsToGenerate = rand() % MAX_ITERATION;
		
		vector< cDataPoint< tX, tY> > vecGeneratedData;
		tY correctWarningOnPoints = 0;
		unsigned int uiWrongPoints = 0;
		for ( unsigned int uiPointsGenerated = 0;
				uiPointsGenerated < uiPointsToGenerate; uiPointsGenerated++ ){
			
			//generate random x value
			tX x = randomValue( ((tX)(10000)) );
			
			tY correctY = polynom.evalue( x );
			tY y = correctY;
			if ( rand() % 2 ){
				//add random error
				tY yWarning = randomValue( ((tY)(10000)) );
				
				if ( yWarning != ((tY)(0.0)) ){
					y += yWarning;
					correctWarningOnPoints += abs( yWarning );
					uiWrongPoints++;
				}
			}//else add no random error
			
			vecGeneratedData.push_back( cDataPoint< tX, tY >( x, y ) );
		}
		
		paWarning = polynom.evalueError( vecGeneratedData );
		if ( paWarning.first != uiWrongPoints ){
			cerr<<"Warning: The method evalueError() of the polynom evalues "<<
				paWarning.first<<" wrong data points, but it should be "<<uiWrongPoints<<" ."<<endl;
			iWarningsEvalueWarning++;
		}
		if ( ! compareDoubleTest( paWarning.second, correctWarningOnPoints ) ){
			cerr<<"Warning: The method evalueError() of the polynom evalues a error sum of "<<
				paWarning.second<<", but it should be "<< correctWarningOnPoints <<
				" (diff="<<(paWarning.second - correctWarningOnPoints)<<") ."<<endl;
			iWarningsEvalueWarning++;
		}
		
		for ( unsigned int uiEvaluationMaxWarning = 0;
				uiEvaluationMaxWarning < 32; uiEvaluationMaxWarning++ ){
			
			const tY errorMult = abs( randomValue( ((tY)(100)) ) );
			const tY maxWarning = errorMult * correctWarningOnPoints;
			const tY correctMaxWarningOnPoints = ( errorMult != 0.0 )?
				min( maxWarning, correctWarningOnPoints ):correctWarningOnPoints;
			
			//cout<<"errorMult: "<<errorMult<<"  maxWarning: "<<maxWarning<<"  correctWarningOnPoints: "<<correctWarningOnPoints<<endl;
			
			error = polynom.evalueErrorMax( vecGeneratedData, maxWarning );
			if ( ! compareDoubleTest( error, correctMaxWarningOnPoints )  ){
				cerr<<"Warning: The method evalueErrorMax() of the polynom evalues a error sum of "<<
					error<<", but it should be "<< correctMaxWarningOnPoints <<
					" (diff="<<(error-correctMaxWarningOnPoints)<<")"<<endl;
				iWarningsEvalueWarning++;
			}
		}
	}
	if ( iWarningsEvalueWarning == 0 ){
		cout<<"   OK"<<endl;
	}else{
		iReturn++;
	}
	
	//test evalueError() and evalueErrorMax() for ranges
	cout<<"Checking evalueError() and evalueErrorMax() methods on range data points:"<<endl;
	int iWarningsEvalueWarningRange = 0;
	vector< cDataPointRange< tX, tY> > vecInputDataRange;
	for ( unsigned int uiActualValue = 0;
			uiActualValue < uiNumberOfGivenValues; uiActualValue++ ){
		
		vecInputDataRange.push_back( cDataPointRange< tX, tY >( vecX[ uiActualValue ],
			 vecCorrectY[ uiActualValue ], vecCorrectY[ uiActualValue ] ) );
	}
	
	paWarning = polynom.evalueError( vecInputDataRange );
	if ( ( paWarning.first != 0 ) || ( paWarning.second != ((tY)(0)) ) ){
		cerr<<"Warning: The method evalueError() of the polynom evalues "<<
			paWarning.first<<" wrong data points with a error sum of "<<
			paWarning.second<<" on the input data (wich should be correct) ."<<endl;
		iWarningsEvalueWarningRange++;
	}
	error = polynom.evalueErrorMax( vecInputDataRange, 10 );
	if ( error != ((tY)(0))  ){
		cerr<<"Warning: The method evalueErrorMax() of the polynom evalues "<<
			" a error sum of "<<error<<" on the input data (wich should be correct) ."<<endl;
		iWarningsEvalueWarningRange++;
	}
	//evalue on random generated data
	for ( unsigned int iteration = 0; iteration < MAX_ITERATION; iteration++ ){
		//generate random data points and check them
		unsigned int uiPointsToGenerate = rand() % MAX_ITERATION;
		
		vector< cDataPointRange< tX, tY> > vecGeneratedData;
		tY correctWarningOnPoints = 0;
		unsigned int uiWrongPoints = 0;
		for ( unsigned int uiPointsGenerated = 0;
				uiPointsGenerated < uiPointsToGenerate; uiPointsGenerated++ ){
			
			//generate random x value
			tX x = randomValue( ((tX)(10000)) );
			
			tY correctY = polynom.evalue( x );
			tY minY = correctY - randomValue( ((tX)(100)) );
			tY maxY = minY + abs( randomValue( ((tX)(100)) ) );
			
			if ( correctY < minY ){
				//add random error
				tY yWarning = minY - correctY;
				
				correctWarningOnPoints += yWarning;
				uiWrongPoints++;
			}else if ( maxY < correctY ){
				//add random error
				tY yWarning = correctY - maxY;
				
				correctWarningOnPoints += yWarning;
				uiWrongPoints++;
			}//else no error
			
			vecGeneratedData.push_back( cDataPointRange< tX, tY >( x, minY, maxY ) );
		}
		
		paWarning = polynom.evalueError( vecGeneratedData );
		if ( paWarning.first != uiWrongPoints ){
			cerr<<"Warning: The method evalueError() of the polynom evalues "<<
				paWarning.first<<" wrong data points, but it should be "<<uiWrongPoints<<" ."<<endl;
			iWarningsEvalueWarningRange++;
		}
		if ( ! compareDoubleTest( paWarning.second, correctWarningOnPoints ) ){
			cerr<<"Warning: The method evalueError() of the polynom evalues a error sum of "<<
				paWarning.second<<", but it should be "<< correctWarningOnPoints <<
				" (diff="<<(paWarning.second - correctWarningOnPoints)<<")."<<endl;
			iWarningsEvalueWarningRange++;
		}
		
		for ( unsigned int uiEvaluationMaxWarning = 0;
				uiEvaluationMaxWarning < 32; uiEvaluationMaxWarning++ ){
			
			const tY errorMult = abs( randomValue( ((tY)(100)) ) );
			const tY maxWarning = errorMult * correctWarningOnPoints;
			const tY correctMaxWarningOnPoints = ( errorMult != 0.0 )?
				min( maxWarning, correctWarningOnPoints ):correctWarningOnPoints;
			
			//cout<<"errorMult: "<<errorMult<<"  maxWarning: "<<maxWarning<<"  correctWarningOnPoints: "<<correctWarningOnPoints<<endl;
			
			error = polynom.evalueErrorMax( vecGeneratedData, maxWarning );
			if ( ! compareDoubleTest( error, correctMaxWarningOnPoints )  ){
				cerr<<"Warning: The method evalueErrorMax() of the polynom evalues a error sum of "<<
					error<<", but it should be "<< correctMaxWarningOnPoints <<
					" (diff="<<(error - correctMaxWarningOnPoints)<<")."<<endl;
				iWarningsEvalueWarningRange++;
			}
		}
	}
	if ( iWarningsEvalueWarningRange == 0 ){
		cout<<"   OK"<<endl;
	}else{
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This function tests the mothods for evaluing the polynom of the class
 * cPolynom.
 *
 * metods tested:
 * 	- tY evalue( const tX & x ) const;
 * 	- void print( ostream & outputStream ) const;
 * 	- pair<unsigned long, tY> evalueError( const vector< cDataPoint< tX, tY> > & vecInput ) const;
 * 	- tY evalueErrorMax( const vector< cDataPoint< tX, tY> > & vecData, const tY maxYError ) const;
 * 	- pair<unsigned long, tY> evalueError( const vector< cDataPointRange< tX, tY> > & vecInput ) const;
 * 	- tY evalueErrorMax( const vector< cDataPointRange< tX, tY> > & vecData, const tY maxYError ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of warnings occured in the test
 */
int testEvalue( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured warnings

	cout<<endl<<"Testing the mothods for evaluing the polynom"<<endl;
	cout<<endl<<"ATTENTION: Pleas check the printed polynoms manually"<<endl;
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing a constant polynom: y = 8"<<endl;
	
	cout<<"cPolynom< int, float > polynomConst8; y = 8"<<endl;
	cPolynom< int, float > polynomConst8;
	polynomConst8.vecFactors.push_back( 8 );
	
	cout<<"polynomConst8.print():"<<endl;
	polynomConst8.print( cout );
	
	vector< int > vecIntX;
	vector< float > vecFloatY;
	vecIntX.push_back( -10 );vecFloatY.push_back( 8 );
	vecIntX.push_back( -5 );vecFloatY.push_back( 8 );
	vecIntX.push_back( -2 );vecFloatY.push_back( 8 );
	vecIntX.push_back( -1 );vecFloatY.push_back( 8 );
	vecIntX.push_back( 0 );vecFloatY.push_back( 8 );
	vecIntX.push_back( 1 );vecFloatY.push_back( 8 );
	vecIntX.push_back( 2 );vecFloatY.push_back( 8 );
	vecIntX.push_back( 3 );vecFloatY.push_back( 8 );
	vecIntX.push_back( 5 );vecFloatY.push_back( 8 );
	vecIntX.push_back( 7 );vecFloatY.push_back( 8 );
	vecIntX.push_back( 10 );vecFloatY.push_back( 8 );
	vecIntX.push_back( 100 );vecFloatY.push_back( 8 );
	
	iReturn += testEvalue( polynomConst8, vecIntX, vecFloatY );
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing a polynom: y = 4 + x"<<endl;
	
	cout<<"cPolynom< float, float > polynom4p1; y = 4 + x"<<endl;
	cPolynom< float, float > polynom4p1;
	polynom4p1.vecFactors.push_back( 4 );
	polynom4p1.vecFactors.push_back( 1 );
	
	cout<<"polynom4p1.print():"<<endl;
	polynom4p1.print( cout );
	
	vector< float > vecFloatX;
	vecFloatY.clear();
	vecFloatX.push_back( -10 );vecFloatY.push_back( -6 );
	vecFloatX.push_back( -5 );vecFloatY.push_back( -1 );
	vecFloatX.push_back( -2 );vecFloatY.push_back( 2 );
	vecFloatX.push_back( -1 );vecFloatY.push_back( 3 );
	vecFloatX.push_back( 0 );vecFloatY.push_back( 4 );
	vecFloatX.push_back( 0.5 );vecFloatY.push_back( 4.5 );
	vecFloatX.push_back( 1 );vecFloatY.push_back( 5 );
	vecFloatX.push_back( 2 );vecFloatY.push_back( 6 );
	vecFloatX.push_back( 3 );vecFloatY.push_back( 7 );
	vecFloatX.push_back( 5 );vecFloatY.push_back( 9 );
	vecFloatX.push_back( 7 );vecFloatY.push_back( 11 );
	vecFloatX.push_back( 10 );vecFloatY.push_back( 14 );
	vecFloatX.push_back( 100 );vecFloatY.push_back( 104 );
	
	iReturn += testEvalue( polynom4p1, vecFloatX, vecFloatY );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing a polynom: y = -1 + 2 * x + 3 * x^2"<<endl;
	
	cout<<"cPolynom< float, double > polynom1p2p3; y = -1 + 2 * x + 3 * x^2"<<endl;
	cPolynom< float, double > polynom1p2p3;
	polynom1p2p3.vecFactors.push_back( -1.5 );
	polynom1p2p3.vecFactors.push_back( 2.0 );
	polynom1p2p3.vecFactors.push_back( 3.0 );
	
	cout<<"polynom1p2p3.print():"<<endl;
	polynom1p2p3.print( cout );
	
	vecFloatX.clear();
	vector< double > vecDoubleY;
	vecFloatX.push_back( -10 );vecDoubleY.push_back( -1.5 - 20.0 + 3.0 * 100.0  );
	vecFloatX.push_back( -5 );vecDoubleY.push_back( -1.5 - 10.0 + 75.0 );
	vecFloatX.push_back( -2 );vecDoubleY.push_back( -1.5 - 4.0 + 12.0 );
	vecFloatX.push_back( -1 );vecDoubleY.push_back( -1.5 - 2.0 + 3.0 );
	vecFloatX.push_back( 0 );vecDoubleY.push_back( -1.5 );
	vecFloatX.push_back( 0.5 );vecDoubleY.push_back( -1.5 + 1.0 + 0.75 );
	vecFloatX.push_back( 1 );vecDoubleY.push_back( -1.5 + 2.0 + 3.0 );
	vecFloatX.push_back( 2 );vecDoubleY.push_back( -1.5 + 4.0 + 12.0 );
	vecFloatX.push_back( 3 );vecDoubleY.push_back( -1.5 + 6.0 + 27.0 );
	vecFloatX.push_back( 5 );vecDoubleY.push_back( -1.5 + 10.0 + 75.0 );
	vecFloatX.push_back( 7 );vecDoubleY.push_back( -1.5 + 14.0 + 3.0 * 7.0 * 7.0 );
	vecFloatX.push_back( 10 );vecDoubleY.push_back( -1.5 + 20.0 + 300.0 );
	vecFloatX.push_back( 100 );vecDoubleY.push_back( -1.5 + 200.0 + 30000.0 );
	
	iReturn += testEvalue( polynom1p2p3, vecFloatX, vecDoubleY );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing a polynom: y = 3.5 - 0.5 * x + 1.5 * x^2"<<endl;
	
	cout<<"cPolynom< double, double > polynom3d5pm0d5p1d5;y = 3.5 - 0.5 * x + 1.5 * x^2"<<endl;
	cPolynom< double, double > polynom3d5pm0d5p1d5;
	polynom3d5pm0d5p1d5.vecFactors.push_back( 3.5 );
	polynom3d5pm0d5p1d5.vecFactors.push_back( -0.5 );
	polynom3d5pm0d5p1d5.vecFactors.push_back( 1.5 );
	
	cout<<"polynom3d5pm0d5p1d5.print():"<<endl;
	polynom3d5pm0d5p1d5.print( cout );
	
	vector< double > vecDoubleX;
	vecDoubleY.clear();
	vecDoubleX.push_back( -10 );vecDoubleY.push_back( 3.5 - 0.5 * -10.0 + 1.5 * 100.0  );
	vecDoubleX.push_back( -5 );vecDoubleY.push_back( 3.5 - 0.5 * -5.0 + 1.5 * 25.0 );
	vecDoubleX.push_back( -2 );vecDoubleY.push_back( 3.5 - 0.5 * -2.0 + 1.5 * 4.0 );
	vecDoubleX.push_back( -1 );vecDoubleY.push_back( 3.5 + 0.5 + 1.5 );
	vecDoubleX.push_back( 0 );vecDoubleY.push_back( 3.5 );
	vecDoubleX.push_back( 0.5 );vecDoubleY.push_back( 3.5 - 0.5 * 0.5 + 1.5 * 0.25 );
	vecDoubleX.push_back( 1 );vecDoubleY.push_back( 3.5 - 0.5 + 1.5 );
	vecDoubleX.push_back( 2 );vecDoubleY.push_back( 3.5 - 0.5 * 2.0 + 1.5 * 4.0 );
	vecDoubleX.push_back( 3 );vecDoubleY.push_back( 3.5 - 0.5 * 3.0 + 1.5 * 9.0 );
	vecDoubleX.push_back( 5 );vecDoubleY.push_back( 3.5 - 0.5 * 5.0 + 1.5 * 25.0 );
	vecDoubleX.push_back( 7 );vecDoubleY.push_back( 3.5 - 0.5 * 7.0 + 1.5 * 49.0 );
	vecDoubleX.push_back( 10 );vecDoubleY.push_back( 3.5 - 0.5 * 10.0 + 1.5 * 100.0 );
	vecDoubleX.push_back( 100 );vecDoubleY.push_back( 3.5 - 0.5 * 100.0 + 1.5 * 10000.0 );
	
	iReturn += testEvalue( polynom3d5pm0d5p1d5, vecDoubleX, vecDoubleY );

	return iReturn;
}



/**
 * This function tests the toFibUnderFunction() function of the
 * cPolynom class.
 *
 * metods tested:
 * 	- template<class tY> cUnderFunction * toFibUnderFunction( cFibVariable * pVariable );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testPolynomToFibUnderFunction( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the toFibUnderFunction() on an 0'ary polynom"<<endl;
	
	cout<<"cFibVariable * pVariableX = new cFibVariable( NULL );"<<endl;
	cFibVariable * pVariableX = new cFibVariable( NULL );
	pVariableX->setIntegerValue( 1 );
	
	cout<<"cPolynom< long, double > polynom;"<<endl;
	cPolynom< long, double > polynom;
	cout<<"pResultUnderfunction = polynom.toFibUnderFunction( pVariableX )"<<endl;
	cUnderFunction * pResultUnderfunction = polynom.toFibUnderFunction(
		pVariableX );
	
	cFunctionValue funValue0( 0.0 );
	
	//check the generated underfunction
	if ( pResultUnderfunction ){
		if ( funValue0 == (* pResultUnderfunction ) ){
		
			cout<<"The generated underfunction is correct. "<<endl;
		}else{
			cerr<<"Error: The generated underfunction is not correct: ";
			pResultUnderfunction->storeXml( cerr );
			iReturn++;
		}
		delete pResultUnderfunction;
	}else{
		cerr<<"Error: No underfunction returned."<<endl;
		iReturn++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the toFibUnderFunction() on an 1'ary polynom"<<endl;
	
	cout<<"polynom.vecFactors.push_back( 2.2 );"<<endl;
	polynom.vecFactors.push_back( 2.2 );
	cout<<"pResultUnderfunction = polynom.toFibUnderFunction( pVariableX )"<<endl;
	pResultUnderfunction = polynom.toFibUnderFunction( pVariableX );
	
	cFunctionValue funValue2p2( 2.2 );
	
	//check the generated underfunction
	if ( pResultUnderfunction ){
		if ( funValue2p2 == (* pResultUnderfunction ) ){
		
			cout<<"The generated underfunction is correct. "<<endl;
		}else{
			cerr<<"Error: The generated underfunction is not correct: "<<endl;
			pResultUnderfunction->storeXml( cerr );
			iReturn++;
		}
		delete pResultUnderfunction;
	}else{
		cerr<<"Error: No underfunction returned."<<endl;
		iReturn++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the toFibUnderFunction() on an 2'ary polynom"<<endl;
	
	cout<<"polynom.vecFactors.push_back( 3.3 );"<<endl;
	polynom.vecFactors.push_back( 3.3 );
	cout<<"pResultUnderfunction = polynom.toFibUnderFunction( pVariableX )"<<endl;
	pResultUnderfunction = polynom.toFibUnderFunction( pVariableX );
	
#ifdef FEATURE_ND1_POLYNOM_TO_HORN_SCHEMA_FIB_UNDERFUNCTION
	cFunctionAdd fun2Ary( cFunctionValue( 2.2 ),
		cFunctionMult( cFunctionVariable( pVariableX ), cFunctionValue( 3.3 ) ) );
#else //FEATURE_ND1_POLYNOM_TO_HORN_SCHEMA_FIB_UNDERFUNCTION
	cFunctionAdd fun2Ary( cFunctionValue( 2.2 ),
		cFunctionMult( cFunctionValue( 3.3 ), cFunctionVariable( pVariableX ) ) );
#endif //FEATURE_ND1_POLYNOM_TO_HORN_SCHEMA_FIB_UNDERFUNCTION
	
	//check the generated underfunction
	if ( pResultUnderfunction ){
		if ( fun2Ary == (* pResultUnderfunction ) ){
		
			cout<<"The generated underfunction is correct. "<<endl;
		}else{
			cerr<<"Error: The generated underfunction is not correct: "<<endl;
			pResultUnderfunction->storeXml( cerr );
			iReturn++;
		}
		delete pResultUnderfunction;
	}else{
		cerr<<"Error: No underfunction returned."<<endl;
		iReturn++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the toFibUnderFunction() on an 3'ary polynom"<<endl;
	
	cout<<"polynom.vecFactors.push_back( -4.4 );"<<endl;
	polynom.vecFactors.push_back( -4.4 );
	cout<<"pResultUnderfunction = polynom.toFibUnderFunction( pVariableX )"<<endl;
	pResultUnderfunction = polynom.toFibUnderFunction( pVariableX );
	
#ifdef FEATURE_ND1_POLYNOM_TO_HORN_SCHEMA_FIB_UNDERFUNCTION
	cFunctionAdd fun3Ary( cFunctionAdd( cFunctionValue( 2.2 ),
		cFunctionMult( cFunctionVariable( pVariableX ),
			cFunctionAdd( cFunctionValue( 3.3 ),
				cFunctionMult( cFunctionVariable( pVariableX ),
					cFunctionValue( -4.4 ) ) ) ) ) );
#else //FEATURE_ND1_POLYNOM_TO_HORN_SCHEMA_FIB_UNDERFUNCTION
	cFunctionAdd fun3Ary( cFunctionAdd( cFunctionValue( 2.2 ),
		cFunctionMult( cFunctionValue( 3.3 ), cFunctionVariable( pVariableX ) ) ),
		cFunctionMult( cFunctionValue( -4.4 ), cFunctionExp(
			cFunctionVariable( pVariableX ), cFunctionValue( 2.0 ) ) ) );
#endif //FEATURE_ND1_POLYNOM_TO_HORN_SCHEMA_FIB_UNDERFUNCTION
	
	//check the generated underfunction
	if ( pResultUnderfunction ){
		if ( fun3Ary == (* pResultUnderfunction ) ){
		
			cout<<"The generated underfunction is correct. "<<endl;
		}else{
			cerr<<"Error: The generated underfunction is not correct: "<<endl;
			pResultUnderfunction->storeXml( cerr );
			iReturn++;
		}
		delete pResultUnderfunction;
	}else{
		cerr<<"Error: No underfunction returned."<<endl;
		iReturn++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the toFibUnderFunction() on an 4'ary polynom"<<endl;
	
	cout<<"polynom.vecFactors.push_back( 15 );"<<endl;
	polynom.vecFactors.push_back( 15 );
	cout<<"pResultUnderfunction = polynom.toFibUnderFunction( pVariableX )"<<endl;
	pResultUnderfunction = polynom.toFibUnderFunction( pVariableX );
	
#ifdef FEATURE_ND1_POLYNOM_TO_HORN_SCHEMA_FIB_UNDERFUNCTION
	cFunctionAdd fun4Ary( cFunctionAdd( cFunctionValue( 2.2 ),
		cFunctionMult( cFunctionVariable( pVariableX ),
			cFunctionAdd( cFunctionValue( 3.3 ),
				cFunctionMult( cFunctionVariable( pVariableX ),
					cFunctionAdd( cFunctionValue( -4.4 ),
						cFunctionMult( cFunctionVariable( pVariableX ), cFunctionValue( 15 ) )
					) ) ) ) ) );
#else //FEATURE_ND1_POLYNOM_TO_HORN_SCHEMA_FIB_UNDERFUNCTION
	cFunctionAdd fun4Ary( cFunctionAdd( cFunctionAdd( cFunctionValue( 2.2 ),
		cFunctionMult( cFunctionValue( 3.3 ), cFunctionVariable( pVariableX ) ) ),
		cFunctionMult( cFunctionValue( -4.4 ), cFunctionExp(
			cFunctionVariable( pVariableX ), cFunctionValue( 2.0 ) ) ) ),
		cFunctionMult( cFunctionValue( 15 ), cFunctionExp(
			cFunctionVariable( pVariableX ), cFunctionValue( 3.0 ) ) ) );
#endif //FEATURE_ND1_POLYNOM_TO_HORN_SCHEMA_FIB_UNDERFUNCTION
	
	//check the generated underfunction
	if ( pResultUnderfunction ){
		if ( fun4Ary == (* pResultUnderfunction ) ){
		
			cout<<"The generated underfunction is correct. "<<endl;
		}else{
			cerr<<"Error: The generated underfunction is not correct: "<<endl;
			pResultUnderfunction->storeXml( cerr );
			iReturn++;
		}
		delete pResultUnderfunction;
	}else{
		cerr<<"Error: No underfunction returned."<<endl;
		iReturn++;
	}
	
	
	delete pVariableX;
	
	return iReturn;
}



/**
 * This function tests the createLinearEquations() function of the
 * cPolynom class for more than one datapoint.
 * ATTENTION: The creation of a linear equiation of one datapoint should
 * be tested outside this function, becaus it is used to verify the created
 * equiations of this test.
 *
 * metods tested:
 * 	- vector< cLinearEquation<tY> > createLinearEquations( const vector< cDataPoint< tX, tY> > & vecData, unsigned int uiMaxPolynomOrder ) const;
 *
 * @param vecDataPoints the data points for which to create the inequiations
 * @param uiPolynomOrder the polynom order of the to create equiations
 * @return the number of errors occured in the test
 */
int checkCreateLinearEquations( const vector< cDataPoint< double, double > > &
		vecDataPoints, const unsigned int uiPolynomOrder ){
	
	int iReturn = 0;
	
	cPolynom< double, double > polynom;
	
	cout<<"vector< cLinearEquation<double> > vecLinearEquiations ="<<
		" polynom.createLinearEquations( vecDataPoints, "<<uiPolynomOrder<<" );"<<endl;
	vector< cLinearEquation<double> > vecLinearEquiations =
		polynom.createLinearEquations( vecDataPoints, uiPolynomOrder );
	
	const unsigned int uiNumberOfDataPoints =
		vecDataPoints.size();
	if ( uiNumberOfDataPoints != vecLinearEquiations.size() ){
		cerr<<"Error: Ther wher "<< vecLinearEquiations.size() <<
			" linear equiations evalued, but ther should be "<<
			uiNumberOfDataPoints<<" . "<<endl;
		iReturn++;
		return iReturn;
	}
	for ( unsigned int uiActualDataPoint = 0;
			uiActualDataPoint < uiNumberOfDataPoints; uiActualDataPoint++ ){
		
		//check the created equiations by creating them one by one and comparing them
		vector< cDataPoint< double, double > > vecDataPoint;
		vecDataPoint.push_back( vecDataPoints[ uiActualDataPoint ] );
		
		vector< cLinearEquation<double> > vecLinearEquiation =
			polynom.createLinearEquations( vecDataPoint, uiPolynomOrder );
		
		if ( ! ( compareDouble( vecLinearEquiation[ 0 ].constant,
					vecLinearEquiations[ uiActualDataPoint ].constant ) &&
				compareVectorDouble( vecLinearEquiation[ 0 ].vecFactors,
					vecLinearEquiations[ uiActualDataPoint ].vecFactors ) ) ){
			
			cout<<"Error: The "<<uiActualDataPoint<<"'th created equiation is wrong."<<endl;
			cout<<"It is:"<<endl;
			vecLinearEquiations[ uiActualDataPoint ].print( cerr );
			cout<<"But should be:"<<endl;
			vecLinearEquiation[ 0 ].print( cerr );
			iReturn++;
		}
	}
	if ( iReturn == 0 ){
		cout<<"   OK"<<endl;
	}
	
	return iReturn;
}


/**
 * This function tests the createLinearEquations() function of the
 * cPolynom class.
 *
 * metods tested:
 * 	- vector< cLinearEquation<tY> > createLinearEquations( const vector< cDataPoint< tX, tY> > & vecData, unsigned int uiMaxPolynomOrder ) const;
 * 	- bool operator==( const cPolynom<tX, tY> & polynom ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCreateLinearEquations( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the testCreateLinearEquations() on no datapoints"<<endl;
	
	cout<<"cPolynom< int, float> polynomIntFloat;"<<endl;
	cPolynom< int, float> polynomIntFloat;
	
	cout<<"vector< cDataPoint< int, float> > vecIntFloatDataPoints: {}"<<endl;
	vector< cDataPoint< int, float> > vecIntFloatDataPoints;
	
	cout<<"vecFloatLinearEquiations = polynomIntFloat.createLinearEquations( vecIntFloatDataPoints, 0 );"<<endl;
	vector< cLinearEquation<float> > vecFloatLinearEquiations =
		polynomIntFloat.createLinearEquations( vecIntFloatDataPoints, 0 );
	
	if ( vecFloatLinearEquiations.empty() ){
		cout<<"Ther wher correctly no linear equiations evalued. "<<endl;
	}else{
		cerr<<"Error: Ther wher "<< vecFloatLinearEquiations.size() <<
			" linear equiations evalued, but ther should be non. "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecFloatLinearEquiations = polynomIntFloat.createLinearEquations( vecIntFloatDataPoints, 1 );"<<endl;
	vecFloatLinearEquiations = polynomIntFloat.createLinearEquations( vecIntFloatDataPoints, 1 );
	
	if ( vecFloatLinearEquiations.empty() ){
		cout<<"Ther wher correctly no linear equiations evalued. "<<endl;
	}else{
		cerr<<"Error: Ther wher "<< vecFloatLinearEquiations.size() <<
			" linear equiations evalued, but ther should be non. "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecFloatLinearEquiations = polynomIntFloat.createLinearEquations( vecIntFloatDataPoints, 5 );"<<endl;
	vecFloatLinearEquiations = polynomIntFloat.createLinearEquations( vecIntFloatDataPoints, 5 );
	
	if ( vecFloatLinearEquiations.empty() ){
		cout<<"Ther wher correctly no linear equiations evalued. "<<endl;
	}else{
		cerr<<"Error: Ther wher "<< vecFloatLinearEquiations.size() <<
			" linear equiations evalued, but ther should be non. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the testCreateLinearEquations() on the datapoint (1, 1)"<<endl;
	
	cout<<"vecIntFloatDataPoints: {(1, 1)}"<<endl;
	vecIntFloatDataPoints.push_back( cDataPoint< int, float>(1, 1) );
	
	cout<<"vecFloatLinearEquiations = polynomIntFloat.createLinearEquations( vecIntFloatDataPoints, 0 );"<<endl;
	vecFloatLinearEquiations =
		polynomIntFloat.createLinearEquations( vecIntFloatDataPoints, 0 );
	
	cLinearEquation<float> correctFloatEquiation( 0, 1.0 );
	//correctFloatEquiation.constant = 1.0;
	//no correctFloatEquiation.vecFactors
	
	if ( vecFloatLinearEquiations.size() == vecIntFloatDataPoints.size()  ){
		cout<<"Ther wher correctly "<<vecIntFloatDataPoints.size()<<
			" linear equiations evalued. "<<endl;
		
		if ( compareDouble( vecFloatLinearEquiations[ 0 ].constant,
					correctFloatEquiation.constant ) &&
				compareVectorDouble( vecFloatLinearEquiations[ 0 ].vecFactors,
					correctFloatEquiation.vecFactors ) ){
			cout<<"The created equiation is correct."<<endl;
		}else{
			cerr<<"Error: The created equiation is wrong."<<endl;
			cerr<<"It is:"<<endl;
			vecFloatLinearEquiations[ 0 ].print( cerr );
			cerr<<"But should be:"<<endl;
			correctFloatEquiation.print( cerr );
			iReturn++;
		}
		
	}else{
		cerr<<"Error: Ther wher "<< vecFloatLinearEquiations.size() <<
			" linear equiations evalued, but it should be "<<
			vecIntFloatDataPoints.size()<<". "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecFloatLinearEquiations = polynomIntFloat.createLinearEquations( vecIntFloatDataPoints, 1 );"<<endl;
	vecFloatLinearEquiations =
		polynomIntFloat.createLinearEquations( vecIntFloatDataPoints, 1 );
	
	//correctFloatEquiation.constant = 1.0;
	correctFloatEquiation.vecFactors.push_back( 1.0 );
	
	if ( vecFloatLinearEquiations.size() == vecIntFloatDataPoints.size()  ){
		cout<<"Ther wher correctly "<<vecIntFloatDataPoints.size()<<
			" linear equiations evalued. "<<endl;
		
		if ( compareDouble( vecFloatLinearEquiations[ 0 ].constant,
					correctFloatEquiation.constant ) &&
				compareVectorDouble( vecFloatLinearEquiations[ 0 ].vecFactors,
					correctFloatEquiation.vecFactors ) ){
			cout<<"The created equiation is correct."<<endl;
		}else{
			cerr<<"Error: The created equiation is wrong."<<endl;
			cerr<<"It is:"<<endl;
			vecFloatLinearEquiations[ 0 ].print( cerr );
			cerr<<"But should be:"<<endl;
			correctFloatEquiation.print( cerr );
			iReturn++;
		}
		
	}else{
		cerr<<"Error: Ther wher "<< vecFloatLinearEquiations.size() <<
			" linear equiations evalued, but it should be "<<
			vecIntFloatDataPoints.size()<<". "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecFloatLinearEquiations = polynomIntFloat.createLinearEquations( vecIntFloatDataPoints, 2 );"<<endl;
	vecFloatLinearEquiations =
		polynomIntFloat.createLinearEquations( vecIntFloatDataPoints, 2 );
	
	//correctFloatEquiation.constant = 1.0;
	correctFloatEquiation.vecFactors.push_back( 1.0 );
	
	if ( vecFloatLinearEquiations.size() == vecIntFloatDataPoints.size()  ){
		cout<<"Ther wher correctly "<<vecIntFloatDataPoints.size()<<
			" linear equiations evalued. "<<endl;
		
		if ( compareDouble( vecFloatLinearEquiations[ 0 ].constant,
					correctFloatEquiation.constant ) &&
				compareVectorDouble( vecFloatLinearEquiations[ 0 ].vecFactors,
					correctFloatEquiation.vecFactors ) ){
			cout<<"The created equiation is correct."<<endl;
		}else{
			cerr<<"Error: The created equiation is wrong."<<endl;
			cerr<<"It is:"<<endl;
			vecFloatLinearEquiations[ 0 ].print( cerr );
			cerr<<"But should be:"<<endl;
			correctFloatEquiation.print( cerr );
			iReturn++;
		}
		
	}else{
		cerr<<"Error: Ther wher "<< vecFloatLinearEquiations.size() <<
			" linear equiations evalued, but it should be "<<
			vecIntFloatDataPoints.size()<<". "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecFloatLinearEquiations = polynomIntFloat.createLinearEquations( vecIntFloatDataPoints, 3 );"<<endl;
	vecFloatLinearEquiations =
		polynomIntFloat.createLinearEquations( vecIntFloatDataPoints, 3 );
	
	//correctFloatEquiation.constant = 1.0;
	correctFloatEquiation.vecFactors.push_back( 1.0 );
	
	if ( vecFloatLinearEquiations.size() == vecIntFloatDataPoints.size()  ){
		cout<<"Ther wher correctly "<<vecIntFloatDataPoints.size()<<
			" linear equiations evalued. "<<endl;
		
		if ( compareDouble( vecFloatLinearEquiations[ 0 ].constant,
					correctFloatEquiation.constant ) &&
				compareVectorDouble( vecFloatLinearEquiations[ 0 ].vecFactors,
					correctFloatEquiation.vecFactors ) ){
			cout<<"The created equiation is correct."<<endl;
		}else{
			cerr<<"Error: The created equiation is wrong."<<endl;
			cerr<<"It is:"<<endl;
			vecFloatLinearEquiations[ 0 ].print( cerr );
			cerr<<"But should be:"<<endl;
			correctFloatEquiation.print( cerr );
			iReturn++;
		}
		
	}else{
		cerr<<"Error: Ther wher "<< vecFloatLinearEquiations.size() <<
			" linear equiations evalued, but it should be "<<
			vecIntFloatDataPoints.size()<<". "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecFloatLinearEquiations = polynomIntFloat.createLinearEquations( vecIntFloatDataPoints, 5 );"<<endl;
	vecFloatLinearEquiations =
		polynomIntFloat.createLinearEquations( vecIntFloatDataPoints, 5 );
	
	//correctFloatEquiation.constant = 1.0;
	correctFloatEquiation.vecFactors.push_back( 1.0 );
	correctFloatEquiation.vecFactors.push_back( 1.0 );
	
	if ( vecFloatLinearEquiations.size() == vecIntFloatDataPoints.size()  ){
		cout<<"Ther wher correctly "<<vecIntFloatDataPoints.size()<<
			" linear equiations evalued. "<<endl;
		
		if ( compareDouble( vecFloatLinearEquiations[ 0 ].constant,
					correctFloatEquiation.constant ) &&
				compareVectorDouble( vecFloatLinearEquiations[ 0 ].vecFactors,
					correctFloatEquiation.vecFactors ) ){
			cout<<"The created equiation is correct."<<endl;
		}else{
			cerr<<"Error: The created equiation is wrong."<<endl;
			cerr<<"It is:"<<endl;
			vecFloatLinearEquiations[ 0 ].print( cerr );
			cerr<<"But should be:"<<endl;
			correctFloatEquiation.print( cerr );
			iReturn++;
		}
		
	}else{
		cerr<<"Error: Ther wher "<< vecFloatLinearEquiations.size() <<
			" linear equiations evalued, but it should be "<<
			vecIntFloatDataPoints.size()<<". "<<endl;
		iReturn++;
	}



	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the testCreateLinearEquations() on the datapoint (2, 3)"<<endl;
	
	cout<<"cPolynom< float, double > polynomFloatDouble;"<<endl;
	cPolynom< float, double > polynomFloatDouble;
	
	cout<<"vector< cDataPoint< float, double > > vecFloatDoubleDataPoints: {(2, 3)}"<<endl;
	vector< cDataPoint< float, double > > vecFloatDoubleDataPoints;
	vecFloatDoubleDataPoints.push_back( cDataPoint< float, double>(2, 3) );
	
	cout<<"vector< cLinearEquation<double> > vecDoubleLinearEquiations ="<<
		" polynomIntFloat.createLinearEquations( vecFloatDoubleDataPoints, 0 );"<<endl;
	vector< cLinearEquation<double> > vecDoubleLinearEquiations =
		polynomFloatDouble.createLinearEquations( vecFloatDoubleDataPoints, 0 );
	
	cLinearEquation<double> correctDoubleEquiation( 0, 3.0 );
	//no correctDoubleEquiation.vecFactors
	
	if ( vecDoubleLinearEquiations.size() == vecFloatDoubleDataPoints.size()  ){
		cout<<"Ther wher correctly "<<vecFloatDoubleDataPoints.size()<<
			" linear equiations evalued. "<<endl;
		
		if ( compareDouble( vecDoubleLinearEquiations[ 0 ].constant,
					correctDoubleEquiation.constant ) &&
				compareVectorDouble( vecDoubleLinearEquiations[ 0 ].vecFactors,
					correctDoubleEquiation.vecFactors ) ){
			cout<<"The created equiation is correct."<<endl;
		}else{
			cerr<<"Error: The created equiation is wrong."<<endl;
			cerr<<"It is:"<<endl;
			vecDoubleLinearEquiations[ 0 ].print( cerr );
			cerr<<"But should be:"<<endl;
			correctDoubleEquiation.print( cerr );
			iReturn++;
		}
		
	}else{
		cerr<<"Error: Ther wher "<< vecDoubleLinearEquiations.size() <<
			" linear equiations evalued, but it should be "<<
			vecFloatDoubleDataPoints.size()<<". "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecDoubleLinearEquiations = polynomIntFloat.createLinearEquations( vecFloatDoubleDataPoints, 1 );"<<endl;
	vecDoubleLinearEquiations =
		polynomFloatDouble.createLinearEquations( vecFloatDoubleDataPoints, 1 );
	
	correctDoubleEquiation.vecFactors.push_back( 1.0 );
	
	if ( vecDoubleLinearEquiations.size() == vecFloatDoubleDataPoints.size()  ){
		cout<<"Ther wher correctly "<<vecFloatDoubleDataPoints.size()<<
			" linear equiations evalued. "<<endl;
		
		if ( compareDouble( vecDoubleLinearEquiations[ 0 ].constant,
					correctDoubleEquiation.constant ) &&
				compareVectorDouble( vecDoubleLinearEquiations[ 0 ].vecFactors,
					correctDoubleEquiation.vecFactors ) ){
			cout<<"The created equiation is correct."<<endl;
		}else{
			cerr<<"Error: The created equiation is wrong."<<endl;
			cerr<<"It is:"<<endl;
			vecDoubleLinearEquiations[ 0 ].print( cerr );
			cerr<<"But should be:"<<endl;
			correctDoubleEquiation.print( cerr );
			iReturn++;
		}
		
	}else{
		cerr<<"Error: Ther wher "<< vecDoubleLinearEquiations.size() <<
			" linear equiations evalued, but it should be "<<
			vecFloatDoubleDataPoints.size()<<". "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecDoubleLinearEquiations = polynomIntFloat.createLinearEquations( vecFloatDoubleDataPoints, 2 );"<<endl;
	vecDoubleLinearEquiations =
		polynomFloatDouble.createLinearEquations( vecFloatDoubleDataPoints, 2 );
	
	correctDoubleEquiation.vecFactors.push_back( 2.0 );
	
	if ( vecDoubleLinearEquiations.size() == vecFloatDoubleDataPoints.size()  ){
		cout<<"Ther wher correctly "<<vecFloatDoubleDataPoints.size()<<
			" linear equiations evalued. "<<endl;
		
		if ( compareDouble( vecDoubleLinearEquiations[ 0 ].constant,
					correctDoubleEquiation.constant ) &&
				compareVectorDouble( vecDoubleLinearEquiations[ 0 ].vecFactors,
					correctDoubleEquiation.vecFactors ) ){
			cout<<"The created equiation is correct."<<endl;
		}else{
			cerr<<"Error: The created equiation is wrong."<<endl;
			cerr<<"It is:"<<endl;
			vecDoubleLinearEquiations[ 0 ].print( cerr );
			cerr<<"But should be:"<<endl;
			correctDoubleEquiation.print( cerr );
			iReturn++;
		}
		
	}else{
		cerr<<"Error: Ther wher "<< vecDoubleLinearEquiations.size() <<
			" linear equiations evalued, but it should be "<<
			vecFloatDoubleDataPoints.size()<<". "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecDoubleLinearEquiations = polynomIntFloat.createLinearEquations( vecFloatDoubleDataPoints, 3 );"<<endl;
	vecDoubleLinearEquiations =
		polynomFloatDouble.createLinearEquations( vecFloatDoubleDataPoints, 3 );
	
	correctDoubleEquiation.vecFactors.push_back( 4.0 );
	
	if ( vecDoubleLinearEquiations.size() == vecFloatDoubleDataPoints.size()  ){
		cout<<"Ther wher correctly "<<vecFloatDoubleDataPoints.size()<<
			" linear equiations evalued. "<<endl;
		
		if ( compareDouble( vecDoubleLinearEquiations[ 0 ].constant,
					correctDoubleEquiation.constant ) &&
				compareVectorDouble( vecDoubleLinearEquiations[ 0 ].vecFactors,
					correctDoubleEquiation.vecFactors ) ){
			cout<<"The created equiation is correct."<<endl;
		}else{
			cerr<<"Error: The created equiation is wrong."<<endl;
			cerr<<"It is:"<<endl;
			vecDoubleLinearEquiations[ 0 ].print( cerr );
			cerr<<"But should be:"<<endl;
			correctDoubleEquiation.print( cerr );
			iReturn++;
		}
		
	}else{
		cerr<<"Error: Ther wher "<< vecDoubleLinearEquiations.size() <<
			" linear equiations evalued, but it should be "<<
			vecFloatDoubleDataPoints.size()<<". "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecDoubleLinearEquiations = polynomIntFloat.createLinearEquations( vecFloatDoubleDataPoints, 5 );"<<endl;
	vecDoubleLinearEquiations =
		polynomFloatDouble.createLinearEquations( vecFloatDoubleDataPoints, 5 );
	
	correctDoubleEquiation.vecFactors.push_back( 8.0 );
	correctDoubleEquiation.vecFactors.push_back( 16.0 );
	
	if ( vecDoubleLinearEquiations.size() == vecFloatDoubleDataPoints.size()  ){
		cout<<"Ther wher correctly "<<vecFloatDoubleDataPoints.size()<<
			" linear equiations evalued. "<<endl;
		
		if ( compareDouble( vecDoubleLinearEquiations[ 0 ].constant,
					correctDoubleEquiation.constant ) &&
				compareVectorDouble( vecDoubleLinearEquiations[ 0 ].vecFactors,
					correctDoubleEquiation.vecFactors ) ){
			cout<<"The created equiation is correct."<<endl;
		}else{
			cerr<<"Error: The created equiation is wrong."<<endl;
			cerr<<"It is:"<<endl;
			vecDoubleLinearEquiations[ 0 ].print( cerr );
			cerr<<"But should be:"<<endl;
			correctDoubleEquiation.print( cerr );
			iReturn++;
		}
		
	}else{
		cerr<<"Error: Ther wher "<< vecDoubleLinearEquiations.size() <<
			" linear equiations evalued, but it should be "<<
			vecFloatDoubleDataPoints.size()<<". "<<endl;
		iReturn++;
	}



	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the testCreateLinearEquations() on the datapoint (-3, 1.5)"<<endl;
	
	cout<<"cPolynom< double, double > polynomDoubleDouble;"<<endl;
	cPolynom< double, double > polynomDoubleDouble;
	
	cout<<"vector< cDataPoint< double, double > > vecDoubleDoubleDataPoints: {(-3, 1.5)}"<<endl;
	vector< cDataPoint< double, double > > vecDoubleDoubleDataPoints;
	vecDoubleDoubleDataPoints.push_back( cDataPoint< double, double>(-3, 1.5) );
	
	cout<<"vector< cLinearEquation<double> > vecDoubleLinearEquiations ="<<
		" polynomIntDouble.createLinearEquations( vecDoubleDoubleDataPoints, 0 );"<<endl;
	vecDoubleLinearEquiations =
		polynomDoubleDouble.createLinearEquations( vecDoubleDoubleDataPoints, 0 );
	
	correctDoubleEquiation.constant = 1.5;
	correctDoubleEquiation.vecFactors.clear();
	
	if ( vecDoubleLinearEquiations.size() == vecDoubleDoubleDataPoints.size()  ){
		cout<<"Ther wher correctly "<<vecDoubleDoubleDataPoints.size()<<
			" linear equiations evalued. "<<endl;
		
		if ( compareDouble( vecDoubleLinearEquiations[ 0 ].constant,
					correctDoubleEquiation.constant ) &&
				compareVectorDouble( vecDoubleLinearEquiations[ 0 ].vecFactors,
					correctDoubleEquiation.vecFactors ) ){
			cout<<"The created equiation is correct."<<endl;
		}else{
			cerr<<"Error: The created equiation is wrong."<<endl;
			cerr<<"It is:"<<endl;
			vecDoubleLinearEquiations[ 0 ].print( cerr );
			cerr<<"But should be:"<<endl;
			correctDoubleEquiation.print( cerr );
			iReturn++;
		}
		
	}else{
		cerr<<"Error: Ther wher "<< vecDoubleLinearEquiations.size() <<
			" linear equiations evalued, but it should be "<<
			vecDoubleDoubleDataPoints.size()<<". "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecDoubleLinearEquiations = polynomIntDouble.createLinearEquations( vecDoubleDoubleDataPoints, 1 );"<<endl;
	vecDoubleLinearEquiations =
		polynomDoubleDouble.createLinearEquations( vecDoubleDoubleDataPoints, 1 );
	
	correctDoubleEquiation.vecFactors.push_back( 1.0 );
	
	if ( vecDoubleLinearEquiations.size() == vecDoubleDoubleDataPoints.size()  ){
		cout<<"Ther wher correctly "<<vecDoubleDoubleDataPoints.size()<<
			" linear equiations evalued. "<<endl;
		
		if ( compareDouble( vecDoubleLinearEquiations[ 0 ].constant,
					correctDoubleEquiation.constant ) &&
				compareVectorDouble( vecDoubleLinearEquiations[ 0 ].vecFactors,
					correctDoubleEquiation.vecFactors ) ){
			cout<<"The created equiation is correct."<<endl;
		}else{
			cerr<<"Error: The created equiation is wrong."<<endl;
			cerr<<"It is:"<<endl;
			vecDoubleLinearEquiations[ 0 ].print( cerr );
			cerr<<"But should be:"<<endl;
			correctDoubleEquiation.print( cerr );
			iReturn++;
		}
		
	}else{
		cerr<<"Error: Ther wher "<< vecDoubleLinearEquiations.size() <<
			" linear equiations evalued, but it should be "<<
			vecDoubleDoubleDataPoints.size()<<". "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecDoubleLinearEquiations = polynomIntDouble.createLinearEquations( vecDoubleDoubleDataPoints, 2 );"<<endl;
	vecDoubleLinearEquiations =
		polynomDoubleDouble.createLinearEquations( vecDoubleDoubleDataPoints, 2 );
	
	correctDoubleEquiation.vecFactors.push_back( -3.0 );
	
	if ( vecDoubleLinearEquiations.size() == vecDoubleDoubleDataPoints.size()  ){
		cout<<"Ther wher correctly "<<vecDoubleDoubleDataPoints.size()<<
			" linear equiations evalued. "<<endl;
		
		if ( compareDouble( vecDoubleLinearEquiations[ 0 ].constant,
					correctDoubleEquiation.constant ) &&
				compareVectorDouble( vecDoubleLinearEquiations[ 0 ].vecFactors,
					correctDoubleEquiation.vecFactors ) ){
			cout<<"The created equiation is correct."<<endl;
		}else{
			cerr<<"Error: The created equiation is wrong."<<endl;
			cerr<<"It is:"<<endl;
			vecDoubleLinearEquiations[ 0 ].print( cerr );
			cerr<<"But should be:"<<endl;
			correctDoubleEquiation.print( cerr );
			iReturn++;
		}
		
	}else{
		cerr<<"Error: Ther wher "<< vecDoubleLinearEquiations.size() <<
			" linear equiations evalued, but it should be "<<
			vecDoubleDoubleDataPoints.size()<<". "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecDoubleLinearEquiations = polynomIntDouble.createLinearEquations( vecDoubleDoubleDataPoints, 3 );"<<endl;
	vecDoubleLinearEquiations =
		polynomDoubleDouble.createLinearEquations( vecDoubleDoubleDataPoints, 3 );
	
	correctDoubleEquiation.vecFactors.push_back( 9.0 );
	
	if ( vecDoubleLinearEquiations.size() == vecDoubleDoubleDataPoints.size()  ){
		cout<<"Ther wher correctly "<<vecDoubleDoubleDataPoints.size()<<
			" linear equiations evalued. "<<endl;
		
		if ( compareDouble( vecDoubleLinearEquiations[ 0 ].constant,
					correctDoubleEquiation.constant ) &&
				compareVectorDouble( vecDoubleLinearEquiations[ 0 ].vecFactors,
					correctDoubleEquiation.vecFactors ) ){
			cout<<"The created equiation is correct."<<endl;
		}else{
			cerr<<"Error: The created equiation is wrong."<<endl;
			cerr<<"It is:"<<endl;
			vecDoubleLinearEquiations[ 0 ].print( cerr );
			cerr<<"But should be:"<<endl;
			correctDoubleEquiation.print( cerr );
			iReturn++;
		}
		
	}else{
		cerr<<"Error: Ther wher "<< vecDoubleLinearEquiations.size() <<
			" linear equiations evalued, but it should be "<<
			vecDoubleDoubleDataPoints.size()<<". "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecDoubleLinearEquiations = polynomIntDouble.createLinearEquations( vecDoubleDoubleDataPoints, 5 );"<<endl;
	vecDoubleLinearEquiations =
		polynomDoubleDouble.createLinearEquations( vecDoubleDoubleDataPoints, 5 );
	
	correctDoubleEquiation.vecFactors.push_back( -27.0 );
	correctDoubleEquiation.vecFactors.push_back( 27.0 * 3.0 );
	
	if ( vecDoubleLinearEquiations.size() == vecDoubleDoubleDataPoints.size()  ){
		cout<<"Ther wher correctly "<<vecDoubleDoubleDataPoints.size()<<
			" linear equiations evalued. "<<endl;
		
		if ( compareDouble( vecDoubleLinearEquiations[ 0 ].constant,
					correctDoubleEquiation.constant ) &&
				compareVectorDouble( vecDoubleLinearEquiations[ 0 ].vecFactors,
					correctDoubleEquiation.vecFactors ) ){
			cout<<"The created equiation is correct."<<endl;
		}else{
			cerr<<"Error: The created equiation is wrong."<<endl;
			cerr<<"It is:"<<endl;
			vecDoubleLinearEquiations[ 0 ].print( cerr );
			cerr<<"But should be:"<<endl;
			correctDoubleEquiation.print( cerr );
			iReturn++;
		}
		
	}else{
		cerr<<"Error: Ther wher "<< vecDoubleLinearEquiations.size() <<
			" linear equiations evalued, but it should be "<<
			vecDoubleDoubleDataPoints.size()<<". "<<endl;
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the testCreateLinearEquations() on the datapoints: {(2, 1), (-3.5, 5)}:"<<endl;
	
	cout<<"vecDoubleDoubleDataPoints = {(2, 1), (-3.5, 5)}"<<endl;
	vecDoubleDoubleDataPoints.clear();
	vecDoubleDoubleDataPoints.push_back( cDataPoint< double, double>(2, 1) );
	vecDoubleDoubleDataPoints.push_back( cDataPoint< double, double>(-3.5, 5) );
	
	
	iReturn += checkCreateLinearEquations( vecDoubleDoubleDataPoints, 0 );
	iReturn += checkCreateLinearEquations( vecDoubleDoubleDataPoints, 1 );
	iReturn += checkCreateLinearEquations( vecDoubleDoubleDataPoints, 2 );
	iReturn += checkCreateLinearEquations( vecDoubleDoubleDataPoints, 3 );
	iReturn += checkCreateLinearEquations( vecDoubleDoubleDataPoints, 5 );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the testCreateLinearEquations() on the datapoints: {(-0.2, -6) (3, 2):(4, -0.7) (10, -7) (-3.3, 2)}:"<<endl;
	
	cout<<"vecDoubleDoubleDataPoints = {(-0.2, -6) (3, 2) (4, -0.7) (10, -7) (-3.3, 2) (3, 2)}"<<endl;
	vecDoubleDoubleDataPoints.clear();
	vecDoubleDoubleDataPoints.push_back( cDataPoint< double, double>(-0.2, -6) );
	vecDoubleDoubleDataPoints.push_back( cDataPoint< double, double>(3, 2) );
	vecDoubleDoubleDataPoints.push_back( cDataPoint< double, double>(4, -0.7) );
	vecDoubleDoubleDataPoints.push_back( cDataPoint< double, double>(10, -7) );
	vecDoubleDoubleDataPoints.push_back( cDataPoint< double, double>(-3.3, 2) );
	vecDoubleDoubleDataPoints.push_back( cDataPoint< double, double>(3, 2) );
	
	
	iReturn += checkCreateLinearEquations( vecDoubleDoubleDataPoints, 0 );
	iReturn += checkCreateLinearEquations( vecDoubleDoubleDataPoints, 1 );
	iReturn += checkCreateLinearEquations( vecDoubleDoubleDataPoints, 2 );
	iReturn += checkCreateLinearEquations( vecDoubleDoubleDataPoints, 3 );
	iReturn += checkCreateLinearEquations( vecDoubleDoubleDataPoints, 5 );
	
	
	return iReturn;
}



/**
 * This function tests the createInequiationsForRangePoint() function of
 * the cPolynom class.
 *
 * metods tested:
 * 	- pair< cInequation< tY >, cInequation< tY > > createInequiationsForRangePoint( const cDataPointRange< tX, tY> & dataPoint, unsigned int uiPolynomOrder ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCreateInequiationsForRangePoint( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the createInequiationsForRangePoint() for range data point: (1, 2 to 3)"<<endl;
	
	cout<<"cPolynom< int, float> polynomIntFloat;"<<endl;
	cPolynom< int, float> polynomIntFloat;
	
	cout<<"cDataPointRange< int, float> intFloatRangeDataPoints(1, 2, 3)"<<endl;
	cDataPointRange< int, float> intFloatRangeDataPoints(1, 2, 3);
	
	cout<<"paFloatInequiations = polynomIntFloat.createInequiationsForRangePoint( intFloatRangeDataPoints, 0 );"<<endl;
	pair< cInequation< float >, cInequation< float > > paFloatInequiations =
		polynomIntFloat.createInequiationsForRangePoint( intFloatRangeDataPoints, 0 );
	
	cInequation< float > inequiationCorrect1;
	inequiationCorrect1.constant = 2;
	cInequation< float > inequiationCorrect2;
	inequiationCorrect2.constant = -3;
	
	if ( compareDouble( inequiationCorrect1.constant,
				paFloatInequiations.first.constant ) &&
			compareVectorDouble( inequiationCorrect1.vecFactors,
				paFloatInequiations.first.vecFactors ) ){
		cout<<"The created first inequiation is correct."<<endl;
	}else{
		cerr<<"Error: The created first inequiation is wrong."<<endl;
		cerr<<"It is:"<<endl;
		paFloatInequiations.first.print( cerr );
		cerr<<"But should be:"<<endl;
		inequiationCorrect1.print( cerr );
		iReturn++;
	}
	
	if ( compareDouble( inequiationCorrect2.constant,
				paFloatInequiations.second.constant ) &&
			compareVectorDouble( inequiationCorrect2.vecFactors,
				paFloatInequiations.second.vecFactors ) ){
		cout<<"The created second inequiation is correct."<<endl;
	}else{
		cerr<<"Error: The created second inequiation is wrong."<<endl;
		cerr<<"It is:"<<endl;
		paFloatInequiations.second.print( cerr );
		cerr<<"But should be:"<<endl;
		inequiationCorrect2.print( cerr );
		iReturn++;
	}


	cout<<"paFloatInequiations = polynomIntFloat.createInequiationsForRangePoint( intFloatRangeDataPoints, 1 );"<<endl;
	paFloatInequiations =
		polynomIntFloat.createInequiationsForRangePoint( intFloatRangeDataPoints, 1 );
	
	inequiationCorrect1.vecFactors.push_back( 1 );
	inequiationCorrect2.vecFactors.push_back( -1 );
	
	if ( compareDouble( inequiationCorrect1.constant,
				paFloatInequiations.first.constant ) &&
			compareVectorDouble( inequiationCorrect1.vecFactors,
				paFloatInequiations.first.vecFactors ) ){
		cout<<"The created first inequiation is correct."<<endl;
	}else{
		cerr<<"Error: The created first inequiation is wrong."<<endl;
		cerr<<"It is:"<<endl;
		paFloatInequiations.first.print( cerr );
		cerr<<"But should be:"<<endl;
		inequiationCorrect1.print( cerr );
		iReturn++;
	}
	
	if ( compareDouble( inequiationCorrect2.constant,
				paFloatInequiations.second.constant ) &&
			compareVectorDouble( inequiationCorrect2.vecFactors,
				paFloatInequiations.second.vecFactors ) ){
		cout<<"The created second inequiation is correct."<<endl;
	}else{
		cerr<<"Error: The created second inequiation is wrong."<<endl;
		cerr<<"It is:"<<endl;
		paFloatInequiations.second.print( cerr );
		cerr<<"But should be:"<<endl;
		inequiationCorrect2.print( cerr );
		iReturn++;
	}

	cout<<"paFloatInequiations = polynomIntFloat.createInequiationsForRangePoint( intFloatRangeDataPoints, 2 );"<<endl;
	paFloatInequiations =
		polynomIntFloat.createInequiationsForRangePoint( intFloatRangeDataPoints, 2 );
	
	inequiationCorrect1.vecFactors.push_back( 1 );
	inequiationCorrect2.vecFactors.push_back( -1 );
	
	if ( compareDouble( inequiationCorrect1.constant,
				paFloatInequiations.first.constant ) &&
			compareVectorDouble( inequiationCorrect1.vecFactors,
				paFloatInequiations.first.vecFactors ) ){
		cout<<"The created first inequiation is correct."<<endl;
	}else{
		cerr<<"Error: The created first inequiation is wrong."<<endl;
		cerr<<"It is:"<<endl;
		paFloatInequiations.first.print( cerr );
		cerr<<"But should be:"<<endl;
		inequiationCorrect1.print( cerr );
		iReturn++;
	}
	
	if ( compareDouble( inequiationCorrect2.constant,
				paFloatInequiations.second.constant ) &&
			compareVectorDouble( inequiationCorrect2.vecFactors,
				paFloatInequiations.second.vecFactors ) ){
		cout<<"The created second inequiation is correct."<<endl;
	}else{
		cerr<<"Error: The created second inequiation is wrong."<<endl;
		cerr<<"It is:"<<endl;
		paFloatInequiations.second.print( cerr );
		cerr<<"But should be:"<<endl;
		inequiationCorrect2.print( cerr );
		iReturn++;
	}

	cout<<"paFloatInequiations = polynomIntFloat.createInequiationsForRangePoint( intFloatRangeDataPoints, 3 );"<<endl;
	paFloatInequiations =
		polynomIntFloat.createInequiationsForRangePoint( intFloatRangeDataPoints, 3 );
	
	inequiationCorrect1.vecFactors.push_back( 1 );
	inequiationCorrect2.vecFactors.push_back( -1 );
	
	if ( compareDouble( inequiationCorrect1.constant,
				paFloatInequiations.first.constant ) &&
			compareVectorDouble( inequiationCorrect1.vecFactors,
				paFloatInequiations.first.vecFactors ) ){
		cout<<"The created first inequiation is correct."<<endl;
	}else{
		cerr<<"Error: The created first inequiation is wrong."<<endl;
		cerr<<"It is:"<<endl;
		paFloatInequiations.first.print( cerr );
		cerr<<"But should be:"<<endl;
		inequiationCorrect1.print( cerr );
		iReturn++;
	}
	
	if ( compareDouble( inequiationCorrect2.constant,
				paFloatInequiations.second.constant ) &&
			compareVectorDouble( inequiationCorrect2.vecFactors,
				paFloatInequiations.second.vecFactors ) ){
		cout<<"The created second inequiation is correct."<<endl;
	}else{
		cerr<<"Error: The created second inequiation is wrong."<<endl;
		cerr<<"It is:"<<endl;
		paFloatInequiations.second.print( cerr );
		cerr<<"But should be:"<<endl;
		inequiationCorrect2.print( cerr );
		iReturn++;
	}

	cout<<"paFloatInequiations = polynomIntFloat.createInequiationsForRangePoint( intFloatRangeDataPoints, 5 );"<<endl;
	paFloatInequiations =
		polynomIntFloat.createInequiationsForRangePoint( intFloatRangeDataPoints, 5 );
	
	inequiationCorrect1.vecFactors.push_back( 1 );
	inequiationCorrect1.vecFactors.push_back( 1 );
	inequiationCorrect2.vecFactors.push_back( -1 );
	inequiationCorrect2.vecFactors.push_back( -1 );
	
	if ( compareDouble( inequiationCorrect1.constant,
				paFloatInequiations.first.constant ) &&
			compareVectorDouble( inequiationCorrect1.vecFactors,
				paFloatInequiations.first.vecFactors ) ){
		cout<<"The created first inequiation is correct."<<endl;
	}else{
		cerr<<"Error: The created first inequiation is wrong."<<endl;
		cerr<<"It is:"<<endl;
		paFloatInequiations.first.print( cerr );
		cerr<<"But should be:"<<endl;
		inequiationCorrect1.print( cerr );
		iReturn++;
	}
	
	if ( compareDouble( inequiationCorrect2.constant,
				paFloatInequiations.second.constant ) &&
			compareVectorDouble( inequiationCorrect2.vecFactors,
				paFloatInequiations.second.vecFactors ) ){
		cout<<"The created second inequiation is correct."<<endl;
	}else{
		cerr<<"Error: The created second inequiation is wrong."<<endl;
		cerr<<"It is:"<<endl;
		paFloatInequiations.second.print( cerr );
		cerr<<"But should be:"<<endl;
		inequiationCorrect2.print( cerr );
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the createInequiationsForRangePoint() for range data point: (-0.5,-3.3 to 7.7)"<<endl;
	
	cout<<"cPolynom< double, double> polynomDoubleDouble;"<<endl;
	cPolynom< double, double> polynomDoubleDouble;
	
	cout<<"cDataPointRange< double, double> intDoubleRangeDataPoints(-0.5,-3.3, 7.7)"<<endl;
	cDataPointRange< double, double> intDoubleRangeDataPoints(-0.5,-3.3, 7.7);
	
	cout<<"paDoubleInequiations = polynomDoubleDouble.createInequiationsForRangePoint( intDoubleRangeDataPoints, 0 );"<<endl;
	pair< cInequation< double >, cInequation< double > > paDoubleInequiations =
		polynomDoubleDouble.createInequiationsForRangePoint( intDoubleRangeDataPoints, 0 );
	
	cInequation< double > inequiationDoubleCorrect1;
	inequiationDoubleCorrect1.constant = -3.3;
	cInequation< double > inequiationDoubleCorrect2;
	inequiationDoubleCorrect2.constant = -7.7;
	
	if ( compareDouble( inequiationDoubleCorrect1.constant,
				paDoubleInequiations.first.constant ) &&
			compareVectorDouble( inequiationDoubleCorrect1.vecFactors,
				paDoubleInequiations.first.vecFactors ) ){
		cout<<"The created first inequiation is correct."<<endl;
	}else{
		cerr<<"Error: The created first inequiation is wrong."<<endl;
		cerr<<"It is:"<<endl;
		paDoubleInequiations.first.print( cerr );
		cerr<<"But should be:"<<endl;
		inequiationDoubleCorrect1.print( cerr );
		iReturn++;
	}
	
	if ( compareDouble( inequiationDoubleCorrect2.constant,
				paDoubleInequiations.second.constant ) &&
			compareVectorDouble( inequiationDoubleCorrect2.vecFactors,
				paDoubleInequiations.second.vecFactors ) ){
		cout<<"The created second inequiation is correct."<<endl;
	}else{
		cerr<<"Error: The created second inequiation is wrong."<<endl;
		cerr<<"It is:"<<endl;
		paDoubleInequiations.second.print( cerr );
		cerr<<"But should be:"<<endl;
		inequiationDoubleCorrect2.print( cerr );
		iReturn++;
	}


	cout<<"paDoubleInequiations = polynomDoubleDouble.createInequiationsForRangePoint( intDoubleRangeDataPoints, 1 );"<<endl;
	paDoubleInequiations =
		polynomDoubleDouble.createInequiationsForRangePoint( intDoubleRangeDataPoints, 1 );
	
	inequiationDoubleCorrect1.vecFactors.push_back( 1 );
	inequiationDoubleCorrect2.vecFactors.push_back( -1 );
	
	if ( compareDouble( inequiationDoubleCorrect1.constant,
				paDoubleInequiations.first.constant ) &&
			compareVectorDouble( inequiationDoubleCorrect1.vecFactors,
				paDoubleInequiations.first.vecFactors ) ){
		cout<<"The created first inequiation is correct."<<endl;
	}else{
		cerr<<"Error: The created first inequiation is wrong."<<endl;
		cerr<<"It is:"<<endl;
		paDoubleInequiations.first.print( cerr );
		cerr<<"But should be:"<<endl;
		inequiationDoubleCorrect1.print( cerr );
		iReturn++;
	}
	
	if ( compareDouble( inequiationDoubleCorrect2.constant,
				paDoubleInequiations.second.constant ) &&
			compareVectorDouble( inequiationDoubleCorrect2.vecFactors,
				paDoubleInequiations.second.vecFactors ) ){
		cout<<"The created second inequiation is correct."<<endl;
	}else{
		cerr<<"Error: The created second inequiation is wrong."<<endl;
		cerr<<"It is:"<<endl;
		paDoubleInequiations.second.print( cerr );
		cerr<<"But should be:"<<endl;
		inequiationDoubleCorrect2.print( cerr );
		iReturn++;
	}

	cout<<"paDoubleInequiations = polynomDoubleDouble.createInequiationsForRangePoint( intDoubleRangeDataPoints, 2 );"<<endl;
	paDoubleInequiations =
		polynomDoubleDouble.createInequiationsForRangePoint( intDoubleRangeDataPoints, 2 );
	
	inequiationDoubleCorrect1.vecFactors.push_back( -0.5 );
	inequiationDoubleCorrect2.vecFactors.push_back( 0.5 );
	
	if ( compareDouble( inequiationDoubleCorrect1.constant,
				paDoubleInequiations.first.constant ) &&
			compareVectorDouble( inequiationDoubleCorrect1.vecFactors,
				paDoubleInequiations.first.vecFactors ) ){
		cout<<"The created first inequiation is correct."<<endl;
	}else{
		cerr<<"Error: The created first inequiation is wrong."<<endl;
		cerr<<"It is:"<<endl;
		paDoubleInequiations.first.print( cerr );
		cerr<<"But should be:"<<endl;
		inequiationDoubleCorrect1.print( cerr );
		iReturn++;
	}
	
	if ( compareDouble( inequiationDoubleCorrect2.constant,
				paDoubleInequiations.second.constant ) &&
			compareVectorDouble( inequiationDoubleCorrect2.vecFactors,
				paDoubleInequiations.second.vecFactors ) ){
		cout<<"The created second inequiation is correct."<<endl;
	}else{
		cerr<<"Error: The created second inequiation is wrong."<<endl;
		cerr<<"It is:"<<endl;
		paDoubleInequiations.second.print( cerr );
		cerr<<"But should be:"<<endl;
		inequiationDoubleCorrect2.print( cerr );
		iReturn++;
	}

	cout<<"paDoubleInequiations = polynomDoubleDouble.createInequiationsForRangePoint( intDoubleRangeDataPoints, 3 );"<<endl;
	paDoubleInequiations =
		polynomDoubleDouble.createInequiationsForRangePoint( intDoubleRangeDataPoints, 3 );
	
	inequiationDoubleCorrect1.vecFactors.push_back( 0.25 );
	inequiationDoubleCorrect2.vecFactors.push_back( -0.25 );
	
	if ( compareDouble( inequiationDoubleCorrect1.constant,
				paDoubleInequiations.first.constant ) &&
			compareVectorDouble( inequiationDoubleCorrect1.vecFactors,
				paDoubleInequiations.first.vecFactors ) ){
		cout<<"The created first inequiation is correct."<<endl;
	}else{
		cerr<<"Error: The created first inequiation is wrong."<<endl;
		cerr<<"It is:"<<endl;
		paDoubleInequiations.first.print( cerr );
		cerr<<"But should be:"<<endl;
		inequiationDoubleCorrect1.print( cerr );
		iReturn++;
	}
	
	if ( compareDouble( inequiationDoubleCorrect2.constant,
				paDoubleInequiations.second.constant ) &&
			compareVectorDouble( inequiationDoubleCorrect2.vecFactors,
				paDoubleInequiations.second.vecFactors ) ){
		cout<<"The created second inequiation is correct."<<endl;
	}else{
		cerr<<"Error: The created second inequiation is wrong."<<endl;
		cerr<<"It is:"<<endl;
		paDoubleInequiations.second.print( cerr );
		cerr<<"But should be:"<<endl;
		inequiationDoubleCorrect2.print( cerr );
		iReturn++;
	}

	cout<<"paDoubleInequiations = polynomDoubleDouble.createInequiationsForRangePoint( intDoubleRangeDataPoints, 5 );"<<endl;
	paDoubleInequiations =
		polynomDoubleDouble.createInequiationsForRangePoint( intDoubleRangeDataPoints, 5 );
	
	inequiationDoubleCorrect1.vecFactors.push_back( -0.125 );
	inequiationDoubleCorrect1.vecFactors.push_back( 0.0625 );
	inequiationDoubleCorrect2.vecFactors.push_back( 0.125 );
	inequiationDoubleCorrect2.vecFactors.push_back( -0.0625 );
	
	if ( compareDouble( inequiationDoubleCorrect1.constant,
				paDoubleInequiations.first.constant ) &&
			compareVectorDouble( inequiationDoubleCorrect1.vecFactors,
				paDoubleInequiations.first.vecFactors ) ){
		cout<<"The created first inequiation is correct."<<endl;
	}else{
		cerr<<"Error: The created first inequiation is wrong."<<endl;
		cerr<<"It is:"<<endl;
		paDoubleInequiations.first.print( cerr );
		cerr<<"But should be:"<<endl;
		inequiationDoubleCorrect1.print( cerr );
		iReturn++;
	}
	
	if ( compareDouble( inequiationDoubleCorrect2.constant,
				paDoubleInequiations.second.constant ) &&
			compareVectorDouble( inequiationDoubleCorrect2.vecFactors,
				paDoubleInequiations.second.vecFactors ) ){
		cout<<"The created second inequiation is correct."<<endl;
	}else{
		cerr<<"Error: The created second inequiation is wrong."<<endl;
		cerr<<"It is:"<<endl;
		paDoubleInequiations.second.print( cerr );
		cerr<<"But should be:"<<endl;
		inequiationDoubleCorrect2.print( cerr );
		iReturn++;
	}
	
	return iReturn;
}



/**
 * This function tests the evalue( vector ) function of the cPolynom class.
 *
 * metods tested:
 * 	- void evalue( const vector< cDataPoint< tX, tY> > & vecData );
 * 	- bool operator==( const cPolynom<tX, tY> & polynom ) const;
 * 	- bool operator!=( const cPolynom<tX, tY> & polynom ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param iWarnings a reference to the integer variable for the warnings
 * @return the number of errors occured in the test
 */
int testEvaluePolynom( unsigned long &ulTestphase, int & iWarnings ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalue() method for creating a polynom for no data point"<<endl;
	
	cout<<"cPolynom< int, float> polynomIntFloat;"<<endl;
	cPolynom< int, float> polynomIntFloat;
	polynomIntFloat.vecFactors.push_back( 17 );
	
	cout<<"vector< cDataPoint< int, float> > vecIntFloatDataPoints: {}"<<endl;
	vector< cDataPoint< int, float> > vecIntFloatDataPoints;
	
	cout<<"polynomIntFloat.evalue( vecIntFloatDataPoints );"<<endl;
	bool bPolynomFound = polynomIntFloat.evalue( vecIntFloatDataPoints );
	
	cPolynom< int, float> polynomIntFloatCorrect;
	polynomIntFloatCorrect.vecFactors.push_back( 17 );
	
	if ( ! bPolynomFound ){
		if ( polynomIntFloatCorrect == polynomIntFloat ){
			cout<<"The polynom is correct."<<endl;
		}else{
			cerr<<"Error: The polynom is wrong."<<endl;
			cerr<<"It is:"<<endl;
			polynomIntFloat.print( cerr );
			cerr<<"But should be:"<<endl;
			polynomIntFloatCorrect.print( cerr );
			iReturn++;
		}
	}else{
		cerr<<"Error: A polynom could be evalued for no data points."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalue() method for creating a polynom for the data point: {(1, 1)}"<<endl;
	
	cout<<"vecIntFloatDataPoints: {(1, 1)}"<<endl;
	vecIntFloatDataPoints.push_back( cDataPoint< int, float>( 1 ,1 ) );
	
	cout<<"polynomIntFloat.evalue( vecIntFloatDataPoints );"<<endl;
	bPolynomFound = polynomIntFloat.evalue( vecIntFloatDataPoints );
	
	polynomIntFloatCorrect.vecFactors.clear();
	polynomIntFloatCorrect.vecFactors.push_back( 1 );
	
	if ( bPolynomFound ){
		if ( polynomIntFloatCorrect == polynomIntFloat ){
			cout<<"The created polynom is correct."<<endl;
		}else{
			cerr<<"Error: The created polynom is wrong."<<endl;
			cerr<<"It is:"<<endl;
			polynomIntFloat.print( cerr );
			cerr<<"But should be:"<<endl;
			polynomIntFloatCorrect.print( cerr );
			iReturn++;
		}
	}else{
		cerr<<"Error: No polynom could be evalued."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalue() method for creating a polynom for the data point: {(2.5, 3.2)}"<<endl;
	
	cout<<"cPolynom< double, double > polynom;"<<endl;
	cPolynom< double, double > polynom;
	
	cout<<"vector< cDataPoint< double, double > > vecDataPoints: {(2.5, 3.2)}"<<endl;
	vector< cDataPoint< double, double > > vecDataPoints;
	vecDataPoints.push_back( cDataPoint< double, double >(2.5, 3.2) );
	
	cout<<"polynom.evalue( vecDataPoints );"<<endl;
	bPolynomFound = polynom.evalue( vecDataPoints );
	
	cPolynom< double, double > polynomCorrect;
	polynomCorrect.vecFactors.push_back( 3.2 );
	
	if ( bPolynomFound ){
		if ( polynomCorrect == polynom ){
			cout<<"The created polynom is correct."<<endl;
		}else{
			cerr<<"Error: The created polynom is wrong."<<endl;
			cerr<<"It is:"<<endl;
			polynom.print( cerr );
			cerr<<"But should be:"<<endl;
			polynomCorrect.print( cerr );
			iReturn++;
		}
	}else{
		cerr<<"Error: No polynom could be evalued."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalue() method for creating a polynom for the data points: {(3, 3.5)) (5.5, -1.5}"<<endl;
	
	cout<<"vecDataPoints: {(3, 3.5) (5.5, -1.5)}"<<endl;
	vecDataPoints.clear();
	vecDataPoints.push_back( cDataPoint< double, double >(3, 3.5) );
	vecDataPoints.push_back( cDataPoint< double, double >(5.5, -1.5) );
	
	cout<<"polynom.evalue( vecDataPoints );"<<endl;
	bPolynomFound = polynom.evalue( vecDataPoints );
	
	polynomCorrect.vecFactors.clear();
	polynomCorrect.vecFactors.push_back( 9.5 );
	polynomCorrect.vecFactors.push_back( -2.0 );
	
	if ( bPolynomFound ){
		if ( polynomCorrect == polynom ){
			cout<<"The created polynom is correct."<<endl;
		}else{
			cerr<<"Error: The created polynom is wrong."<<endl;
			cerr<<"It is:"<<endl;
			polynom.print( cerr );
			cerr<<"But should be:"<<endl;
			polynomCorrect.print( cerr );
			iReturn++;
		}
	}else{
		cerr<<"Error: No polynom could be evalued."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalue() method for creating a polynom for the data points: {( -0.8, 0.76 ) ( 4, -5 ) ( -3.5, -16.25)}"<<endl;
	
	cout<<"vecDataPoints: {( -0.8, 0.76 ) ( 4, -5 ) ( -3.5, -16.25)}"<<endl;
	vecDataPoints.clear();
	vecDataPoints.push_back( cDataPoint< double, double >( -0.8, 0.76 ) );
	vecDataPoints.push_back( cDataPoint< double, double >( 4, -5 ) );
	vecDataPoints.push_back( cDataPoint< double, double >( -3.5, -16.25 ) );
	
	cout<<"polynom.evalue( vecDataPoints );"<<endl;
	bPolynomFound = polynom.evalue( vecDataPoints );
	
	polynomCorrect.vecFactors.clear();
	polynomCorrect.vecFactors.push_back( 3.0 );
	polynomCorrect.vecFactors.push_back( 2.0 );
	polynomCorrect.vecFactors.push_back( -1.0 );
	
	if ( bPolynomFound ){
		if ( polynomCorrect == polynom ){
			cout<<"The created polynom is correcly: "<<endl;
			polynom.print( cout );
		}else{
			cerr<<"Error: The created polynom is wrong."<<endl;
			cerr<<"It is:"<<endl;
			polynom.print( cerr );
			cerr<<"But should be:"<<endl;
			polynomCorrect.print( cerr );
			iReturn++;
		}
	}else{
		cerr<<"Error: No polynom could be evalued."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalue() method for creating a polynom for the data points with duplicates: {( 2, -2 ) (3, -0.5) ( 4, 2 ) (3, -0.5) ( 4, 2 ) ( 4, 2 )}"<<endl;
	
	cout<<"vecDataPoints: {( 2, -2 ) (3, -0.5) ( 4, 2 ) (3, -0.5) ( 4, 2 ) ( 4, 2 )}"<<endl;
	vecDataPoints.clear();
	vecDataPoints.push_back( cDataPoint< double, double >( 2, -2 ) );
	vecDataPoints.push_back( cDataPoint< double, double >(3, -0.5) );
	vecDataPoints.push_back( cDataPoint< double, double >( 4, 2 ) );
	vecDataPoints.push_back( cDataPoint< double, double >(3, -0.5) );
	vecDataPoints.push_back( cDataPoint< double, double >( 4, 2 ) );
	vecDataPoints.push_back( cDataPoint< double, double >( 4, 2 ) );
	
	cout<<"polynom.evalue( vecDataPoints );"<<endl;
	bPolynomFound = polynom.evalue( vecDataPoints );
	
	polynomCorrect.vecFactors.clear();
	polynomCorrect.vecFactors.push_back( -2.0 );
	polynomCorrect.vecFactors.push_back( -1.0 );
	polynomCorrect.vecFactors.push_back( 0.5 );
	
	if ( bPolynomFound ){
		if ( polynomCorrect == polynom ){
			cout<<"The created polynom is correcly: "<<endl;
			polynom.print( cout );
		}else{
			cerr<<"Error: The created polynom is wrong."<<endl;
			cerr<<"It is:"<<endl;
			polynom.print( cerr );
			cerr<<"But should be:"<<endl;
			polynomCorrect.print( cerr );
			iReturn++;
		}
	}else{
		cerr<<"Error: No polynom could be evalued."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalue() method for creating a polynom for the data points: {(3, 7) (3, 2)} wich cant be part of one polynom"<<endl;
	
	cout<<"vecDataPoints: {(3, 7) (3, 2)}"<<endl;
	vecDataPoints.clear();
	vecDataPoints.push_back( cDataPoint< double, double >(3, 7) );
	vecDataPoints.push_back( cDataPoint< double, double >(3, 2) );
	
	cout<<"polynom.evalue( vecDataPoints );"<<endl;
	bPolynomFound = polynom.evalue( vecDataPoints );
	
	if ( ! bPolynomFound ){
		if ( polynomCorrect == polynom ){
			cout<<"The polynom couldn't be evalued for the datapoints. The polynom is unchanged, it is correcly: "<<endl;
			polynom.print( cout );
		}else{
			cerr<<"Error: The polynom could be evalued for the datapoints, but shouldnt be."<<endl;
			cerr<<"It is:"<<endl;
			polynom.print( cerr );
			cerr<<"But should be:"<<endl;
			polynomCorrect.print( cerr );
			iReturn++;
		}
	}else{
		cerr<<"Error: No polynom could be evalued."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalue() method for creating random polynoms"<<endl;
	
	cout<<"cPolynom< double, double > polynomRand;"<<endl;
	cPolynom< double, double > polynomRand;
	
	for ( unsigned int uiIteration = 0; uiIteration < (MAX_ITERATION / 16 + 1); uiIteration++ ){
		
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating "<<uiIteration<<"'th random polynoms"<<endl;
		
		const unsigned int uiDataPointsToGenerate = rand() % 5;
		cout<<"vector< cDataPoint< double, double > > vecDataPoints (size="<<
			uiDataPointsToGenerate<<"): {";
		vector< cDataPoint< double, double > > vecDataPoints;
		set< double > setXValues;
		
		bool bPolynomCanBeEvalued = (uiDataPointsToGenerate != 0);
		for ( unsigned int uiGeneratedDataPoints = 0;
				uiGeneratedDataPoints < uiDataPointsToGenerate;
				uiGeneratedDataPoints++ ){
			
			double x = randomValue( 1000.0 );
			double y = randomValue( 1000.0 );
			
			if ( setXValues.find( x ) != setXValues.end() ){
				//the x value was generated befor -> no polynom can be created
				bPolynomCanBeEvalued = false;
			}else{//new x value
				setXValues.insert( x );
			}
			cout<<"("<<x<<","<<y<<") ";
			vecDataPoints.push_back( cDataPoint< double, double >( x, y ) );
		}
		cout<<"} "<<endl;
		
		const cPolynom< double, double > polynomRandOld( polynomRand );
		
		cout<<"polynomRand.evalue( vecDataPoints );"<<endl;
		bool bPolynomFound = polynomRand.evalue( vecDataPoints );
		
		if ( bPolynomCanBeEvalued ){
			if ( bPolynomFound ){
				/*bPolynomCanBeEvalued == bPolynomFound == true
				-> check if the polynom match the data points*/
				bool bDataPointWrong = false;
				for ( unsigned int uiActualDataPoints = 0;
						uiActualDataPoints < uiDataPointsToGenerate;
						uiActualDataPoints++ ){
					
					if ( ! compareDoubleTest( vecDataPoints[ uiActualDataPoints ].y,
							polynomRand.evalue( vecDataPoints[ uiActualDataPoints ].x ) ) ){
						
						bDataPointWrong = true;
						cerr<<"Warning: The "<<uiActualDataPoints<<"'th data point ("<<
							vecDataPoints[ uiActualDataPoints ].x<<", "<<
							vecDataPoints[ uiActualDataPoints ].y<<
							") is not matched by the polynom ("<<
							vecDataPoints[ uiActualDataPoints ].x<<", "<<
							polynomRand.evalue( vecDataPoints[ uiActualDataPoints ].x )<<
							"), diff in y is "<<( vecDataPoints[ uiActualDataPoints ].y -
								polynomRand.evalue( vecDataPoints[ uiActualDataPoints ].x ) )<<" ."<<endl;
					}
				}
				if ( bDataPointWrong ){
					cerr<<"Warning: The polynom dosn't match all the data points."<<endl;
					cerr<<"It is:"<<endl;
					polynomRand.print( cerr );
					iWarnings++;
				}
			}else{
				cerr<<"Error: The polynom couldn't be evalued for the datapoints, but should be."<<endl;
				cerr<<"It is:"<<endl;
				polynomRand.print( cerr );
				iReturn++;
			}
		}else{//not bPolynomCanBeEvalued
			if ( bPolynomFound || ( polynomRandOld != polynomRand ) ){
				cerr<<"Error: The polynom could be evalued for the datapoints, but shouldn't be."<<endl;
				cerr<<"It is:"<<endl;
				polynomRand.print( cerr );
				cerr<<"But should be:"<<endl;
				polynomRandOld.print( cerr );
				iReturn++;
			}
		}
		if ( compareVectorDouble( polynomRand.vecFactors,
				polynomRandOld.vecFactors ) ){
			//vector factors not changed
			if ( ! ( polynomRandOld == polynomRand ) ){
				cerr<<"Error: The polynom is not changed, but is not equal ( not == ) to the old polynom."<<endl;
				iReturn++;
			}
			if ( polynomRandOld != polynomRand ){
				cerr<<"Error: The polynom is not changed, but is not equal ( != ) to the old polynom."<<endl;
				iReturn++;
			}
		}else{//vector factors changed
			if ( polynomRandOld == polynomRand ){
				cerr<<"Error: The polynom is changed, but is equal ( == ) to the old polynom."<<endl;
				iReturn++;
			}
			if ( ! ( polynomRandOld != polynomRand ) ){
				cerr<<"Error: The polynom is changed, but is not not  equal ( not != ) to the old polynom."<<endl;
				iReturn++;
			}
		}
	}
	return iReturn;
}







/**
 * This function tests the evalueSpline() function of the cPolynom class.
 *
 * metods tested:
 * 	- unsigned long evalueSpline( const vector< cDataPointRange< tX, tY> > & vecData, unsigned int uiNumberOfParameters = 4, const unsigned int uiMinBitsToStoreMantissa = 1 );
 * 	- bool operator==( const cPolynom<tX, tY> & polynom ) const;
 * 	- bool operator!=( const cPolynom<tX, tY> & polynom ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param iWarnings a reference to the integer variable for the warnings
 * @return the number of errors occured in the test
 */
int testEvalueSpline( unsigned long &ulTestphase, int & iWarnings ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalueSpline() method for creating random polynoms of type domain(x) = int and domain(y) = double"<<endl;
	
	cout<<"cPolynom< int, double > polynomRandIntDouble;"<<endl;
	cPolynom< int, double > polynomRandIntDouble;
	
	unsigned long ulSplinesGenerated = 0;
	unsigned int uiMaxParameter = 3;
	unsigned long ulNextParameterIncrease = 8;
	
	for ( unsigned int uiIteration = 0; uiIteration < (MAX_ITERATION / 16 + 1); uiIteration++ ){
		
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating "<<uiIteration<<"'th random polynom"<<endl;
		
		ulSplinesGenerated++;
		if ( ulNextParameterIncrease < ulSplinesGenerated ){
			//increase max dimension with 1
			uiMaxParameter++;
			ulNextParameterIncrease *= ulNextParameterIncrease;
		}
		
		unsigned int uiNumberOfParameters = 0;
		if ( rand() % 32 ){
			uiNumberOfParameters = rand() % uiMaxParameter + 1;
		}//else uiNumberOfParameters = 0;
		
		cPolynom< int, double > generatorPolynomIntDouble;
		
		unsigned int uiNumberOfGeneratorPolynomFactors = uiNumberOfParameters;
		
		if ( ( (rand() % 8) == 0) ){
			//use generator polynom with diffent number of factors
			uiNumberOfGeneratorPolynomFactors = rand() % uiMaxParameter + 1;
		}
		if ( uiNumberOfGeneratorPolynomFactors == 0 ){
			uiNumberOfGeneratorPolynomFactors = 1;
		}
		double dMaxFactorValue = 10000.0;
		for ( unsigned int uiActualFactor = 0;
				uiActualFactor < uiNumberOfGeneratorPolynomFactors; uiActualFactor++){
			
			generatorPolynomIntDouble.vecFactors.push_back(
				randomValue( dMaxFactorValue ) );
			if ( 8.0 < dMaxFactorValue ){
				dMaxFactorValue /= 8.0;
			}
		}
		cout<<"Polynom from which the datapoints are generated:"<<endl;
		generatorPolynomIntDouble.print( cout );
		
		unsigned int uiDataPointsToGenerate = 0;
		if ( rand() % 32 ){
			uiDataPointsToGenerate = rand() % ( (rand() % 64) + 1 ) + 1;
		}//else  uiDataPointsToGenerate = 0;
		cout<<"vector< cDataPointRange< int, double > > vecDataPoints (size="<<
			uiDataPointsToGenerate<<"): {";
		vector< cDataPointRange< int, double > > vecDataPoints;
		
		//if bXIsRandom is true the x is generated random, else in increased
		bool bXIsRandom = ((rand() % 8) == 0);
		int iLastX = ((int)(uiDataPointsToGenerate)) / -2;
		const int uiMaxXValueForRandGenerator = 8 * uiDataPointsToGenerate;
		
		for ( unsigned int uiGeneratedDataPoints = 0;
				uiGeneratedDataPoints < uiDataPointsToGenerate;
				uiGeneratedDataPoints++ ){
			
			int x;
			if ( bXIsRandom ){
				x = randomValue( uiMaxXValueForRandGenerator );
			}else{
				if ( rand() % 32 ){
					x = iLastX + 1;
				}else{
					x = iLastX + rand() % ( (rand() % 32) + 1 );
				}
			}
			iLastX = x;
			
			const double y = generatorPolynomIntDouble.evalue( x );
			const double minY = y - absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			double maxY = y + absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			if ( ( rand() % 32 ) == 0 ){
				maxY = minY + absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			}
			if ( maxY <= minY ){
				maxY = minY + 0.0001;
			}
			
			cout<<"("<<x<<", "<<minY<<" till "<<maxY<<") ";
			vecDataPoints.push_back( cDataPointRange< int, double >( x, minY, maxY ) );
		}
		cout<<"} "<<endl;
		
		const cPolynom< int, double > polynomRandIntDoubleOld( polynomRandIntDouble );
		
		const unsigned int uiMinBitsToStoreMantissa = rand() % 32;
		double maxValue = abs( randomValue( 1000000.0 ) ) + 1000.0;
		if ( (rand() % 8) == 0 ){
			maxValue = randomValue( 1000000.0 );
		}
		
		cout<<endl<<"polynomRandIntDouble.evalueSpline( vecDataPoints, uiNumberOfParameters="<<
			uiNumberOfParameters<<", uiMinBitsToStoreMantissa="<<
			uiMinBitsToStoreMantissa<<" , maxValue="<<maxValue<<");"<<endl<<endl;
		unsigned long uiPointsIncluded = polynomRandIntDouble.evalueSpline(
			vecDataPoints, uiNumberOfParameters, uiMinBitsToStoreMantissa, maxValue );
		
		if ( 0 < uiPointsIncluded ){
			cout<<"Founded polynom is for the "<<uiPointsIncluded<<" first "<<
				( (uiPointsIncluded == uiDataPointsToGenerate)?"(=all) ":"" )<<
				"range data points:"<<endl;
			polynomRandIntDouble.print( cout );
		}else{
			cout<<"No new polynom generated."<<endl;
		}
		
		if ( uiDataPointsToGenerate < uiPointsIncluded ){
			cerr<<"Error: Ther wher "<<uiPointsIncluded<<" but only "<<
				uiDataPointsToGenerate<<" points to include ."<<endl;
			iReturn++;
		}
		
		if ( 0 < uiPointsIncluded ){
			
			if ( ( 0 < uiNumberOfParameters ) &&
					(uiNumberOfParameters < polynomRandIntDouble.vecFactors.size()) ){
				cerr<<"Error: The polynom has "<<polynomRandIntDouble.vecFactors.size()<<
					" parameters, but should have maximal "<<uiNumberOfParameters<<" ."<<endl;
				iReturn++;
			}
			for ( unsigned int uiActualFactor = 0;
					uiActualFactor < polynomRandIntDouble.vecFactors.size(); uiActualFactor++ ){
				
				if ( maxValue < abs( polynomRandIntDouble.vecFactors[ uiActualFactor ] * 0.999 ) ){
					cerr<<"Error: The polynom has as the "<<uiActualFactor<<
						"'th factor ("<<polynomRandIntDouble.vecFactors[ uiActualFactor ]<<
						") greater than the maxValue of "<<maxValue<<" ."<<endl;
					iReturn++;
				}
			}
			/* check if the polynom match the range data points*/
			vector< cDataPointRange< int, double > > vecDataPointsCorrect =
				vecDataPoints;
			sort( vecDataPointsCorrect.begin(), vecDataPointsCorrect.end() );
			if ( uiPointsIncluded < uiDataPointsToGenerate ){
				vecDataPointsCorrect.resize( uiPointsIncluded );
			}
			
			pair< unsigned long, double > paError = polynomRandIntDouble.evalueError(
				vecDataPointsCorrect );
			
			if ( paError.first != 0 ){
				cerr<<"Warning: The polynom dosn't match the "<<uiPointsIncluded<<
					" first range data points.";
				cerr<<" Ther are "<<paError.first<<" wrong points with a error sum of "<<
					paError.second<<" ."<<endl;
				iWarnings++;
			}
			
			if ( uiPointsIncluded < uiDataPointsToGenerate ){
				vector< cDataPointRange< int, double > > vecFirstDataPointWrong =
					vecDataPoints;
				vecFirstDataPointWrong.push_back( vecDataPoints[ uiPointsIncluded ] );
				
				paError = polynomRandIntDouble.evalueError( vecFirstDataPointWrong );
				
				if ( paError.first == 0 ){
					cerr<<"Error: The polynom dos match the "<<uiPointsIncluded<<
						"'th range data point, but shouldn't."<<endl;
					iReturn++;
				}
			}
		}else{// uiPointsIncluded == 0
			if ( (0 < uiDataPointsToGenerate) && ( 0.0 < maxValue ) && ( 0 < uiNumberOfParameters ) ){
				if ( (vecDataPoints[ 0 ].minY < maxValue) &&
						( (-1.0 * vecDataPoints[ 0 ].maxY) < maxValue) ){
					cerr<<"Error: Ther wher range data points generated, but non included."<<endl;
					iReturn++;
				}
			}
			if ( polynomRandIntDoubleOld != polynomRandIntDouble ){
				cerr<<"Error: The polynom was changed for the datapoints, but shouldn't be (because non evalued)."<<endl;
				cerr<<"It should be unchanged:"<<endl;
				polynomRandIntDoubleOld.print( cerr );
				iReturn++;
			}
		}

		if ( compareVectorDouble( polynomRandIntDouble.vecFactors,
				polynomRandIntDoubleOld.vecFactors ) ){
			//vector factors not changed
			if ( ! ( polynomRandIntDoubleOld == polynomRandIntDouble ) ){
				cerr<<"Error: The polynom is not changed, but is not equal ( not == ) to the old polynom."<<endl;
				iReturn++;
			}
			if ( polynomRandIntDoubleOld != polynomRandIntDouble ){
				cerr<<"Error: The polynom is not changed, but is not equal ( != ) to the old polynom."<<endl;
				iReturn++;
			}
		}else{//vector factors changed
			if ( polynomRandIntDoubleOld == polynomRandIntDouble ){
				cerr<<"Error: The polynom is changed, but is equal ( == ) to the old polynom."<<endl;
				iReturn++;
			}
			if ( ! ( polynomRandIntDoubleOld != polynomRandIntDouble ) ){
				cerr<<"Error: The polynom is changed, but is not not  equal ( not != ) to the old polynom."<<endl;
				iReturn++;
			}
		}
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalueSpline() method for creating random polynoms of type domain(x) = double and domain(y) = double"<<endl;
	
	cout<<"cPolynom< double, double > polynomRandDoubleDouble;"<<endl;
	cPolynom< double, double > polynomRandDoubleDouble;
	
	ulSplinesGenerated = 0;
	uiMaxParameter = 3;
	ulNextParameterIncrease = 8;
	
	for ( unsigned int uiIteration = 0; uiIteration < (MAX_ITERATION / 16 + 1); uiIteration++ ){
		
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating "<<uiIteration<<"'th random polynoms"<<endl;
		
		ulSplinesGenerated++;
		if ( ulNextParameterIncrease < ulSplinesGenerated ){
			//increase max dimension with 1
			uiMaxParameter++;
			ulNextParameterIncrease *= ulNextParameterIncrease;
		}
		
		unsigned int uiNumberOfParameters = 0;
		if ( rand() % 32 ){
			uiNumberOfParameters = rand() % uiMaxParameter + 1;
		}//else uiNumberOfParameters = 0;
		cPolynom< double, double > generatorPolynomDoubleDouble;
		
		unsigned int uiNumberOfGeneratorPolynomFactors = uiNumberOfParameters;
		
		if ( ( (rand() % 8) == 0) ){
			//use generator polynom with diffent number of factors
			uiNumberOfGeneratorPolynomFactors = rand() % uiMaxParameter + 1;
		}
		if ( uiNumberOfGeneratorPolynomFactors == 0 ){
			uiNumberOfGeneratorPolynomFactors = 1;
		}
		double dMaxFactorValue = 10000.0;
		for ( unsigned int uiActualFactor = 0;
				uiActualFactor < uiNumberOfGeneratorPolynomFactors; uiActualFactor++){
			
			generatorPolynomDoubleDouble.vecFactors.push_back(
				randomValue( dMaxFactorValue ) );
			if ( 8.0 < dMaxFactorValue ){
				dMaxFactorValue /= 8.0;
			}
		}
		cout<<"Polynom from which the datapoints are generated:"<<endl;
		generatorPolynomDoubleDouble.print( cout );
		
		unsigned int uiDataPointsToGenerate = 0;
		if ( rand() % 32 ){
			uiDataPointsToGenerate = rand() % ( (rand() % 64) + 1 ) + 1;
		}//else  uiDataPointsToGenerate = 0;
		cout<<"vector< cDataPointRange< double, double > > vecDataPoints (size="<<
			uiDataPointsToGenerate<<"): {";
		vector< cDataPointRange< double, double > > vecDataPoints;
		
		//if bXIsRandom is true the x is generated random, else in increased
		bool bXIsRandom = ((rand() % 8) == 0);
		double iLastX = ((int)(uiDataPointsToGenerate)) / -2;
		const double dMaxXValueForRandGenerator = 8 * uiDataPointsToGenerate;
		
		for ( unsigned int uiGeneratedDataPoints = 0;
				uiGeneratedDataPoints < uiDataPointsToGenerate;
				uiGeneratedDataPoints++ ){
			
			double x;
			if ( bXIsRandom ){
				x = randomValue( dMaxXValueForRandGenerator );
			}else{
				if ( rand() % 32 ){
					x = iLastX + 1.0;
				}else{
					x = iLastX + randomValue( dMaxXValueForRandGenerator / 32.0 + 4.0 );
				}
			}
			iLastX = x;
			
			const double y = generatorPolynomDoubleDouble.evalue( x );
			const double minY = y - absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			double maxY = y + absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			if ( ( rand() % 32 ) == 0 ){
				maxY = minY + absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			}
			if ( maxY <= minY ){
				maxY = minY + 0.0001;
			}
			
			cout<<"("<<x<<", "<<minY<<" till "<<maxY<<") ";
			vecDataPoints.push_back( cDataPointRange< double, double >( x, minY, maxY ) );
		}
		cout<<"} "<<endl;
		
		const cPolynom< double, double > polynomRandDoubleDoubleOld( polynomRandDoubleDouble );
		
		const unsigned int uiMinBitsToStoreMantissa = rand() % 32;
		double maxValue = abs( randomValue( 1000000.0 ) ) + 1000.0;
		if ( (rand() % 8) == 0 ){
			maxValue = randomValue( 1000000.0 );
		}
		
		cout<<endl<<"polynomRandDoubleDouble.evalueSpline( vecDataPoints, uiNumberOfParameters="<<
			uiNumberOfParameters<<", uiMinBitsToStoreMantissa="<<
			uiMinBitsToStoreMantissa<<" , maxValue="<<maxValue<<");"<<endl<<endl;
		unsigned long uiPointsIncluded = polynomRandDoubleDouble.evalueSpline(
			vecDataPoints, uiNumberOfParameters, uiMinBitsToStoreMantissa, maxValue );
		
		if ( 0 < uiPointsIncluded ){
			cout<<"Founded polynom is for the "<<uiPointsIncluded<<" first "<<
				( (uiPointsIncluded == uiDataPointsToGenerate)?"(=all) ":"" )<<
				"range data points:"<<endl;
			polynomRandDoubleDouble.print( cout );
		}else{
			cout<<"No new polynom generated."<<endl;
		}
		
		if ( uiDataPointsToGenerate < uiPointsIncluded ){
			cerr<<"Error: Ther wher "<<uiPointsIncluded<<" but only "<<
				uiDataPointsToGenerate<<" points to include ."<<endl;
			iReturn++;
		}
		
		if ( 0 < uiPointsIncluded ){
			
			if ( ( 0 < uiNumberOfParameters ) &&
					(uiNumberOfParameters < polynomRandDoubleDouble.vecFactors.size()) ){
				cerr<<"Error: The polynom has "<<polynomRandDoubleDouble.vecFactors.size()<<
					" parameters, but should have maximal "<<uiNumberOfParameters<<" ."<<endl;
				iReturn++;
			}
			for ( unsigned int uiActualFactor = 0;
					uiActualFactor < polynomRandDoubleDouble.vecFactors.size(); uiActualFactor++ ){
				
				if ( maxValue < abs( polynomRandDoubleDouble.vecFactors[ uiActualFactor ] * 0.999 ) ){
					cerr<<"Error: The polynom has as the "<<uiActualFactor<<
						"'th factor ("<<polynomRandDoubleDouble.vecFactors[ uiActualFactor ]<<
						") greater than the maxValue of "<<maxValue<<" ."<<endl;
					iReturn++;
				}
			}
			/* check if the polynom match the range data points*/
			vector< cDataPointRange< double, double > > vecDataPointsCorrect =
				vecDataPoints;
			sort( vecDataPointsCorrect.begin(), vecDataPointsCorrect.end() );
			if ( uiPointsIncluded < uiDataPointsToGenerate ){
				vecDataPointsCorrect.resize( uiPointsIncluded );
			}
			
			pair< unsigned long, double > paError = polynomRandDoubleDouble.evalueError(
				vecDataPointsCorrect );
			
			if ( paError.first != 0 ){
				cerr<<"Warning: The polynom dosn't match the "<<uiPointsIncluded<<
					" first range data points.";
				cerr<<" Ther are "<<paError.first<<" wrong points with a error sum of "<<
					paError.second<<" ."<<endl;
				iWarnings++;
			}
			
			if ( uiPointsIncluded < uiDataPointsToGenerate ){
				vector< cDataPointRange< double, double > > vecFirstDataPointWrong =
					vecDataPoints;
				vecFirstDataPointWrong.push_back( vecDataPoints[ uiPointsIncluded ] );
				
				paError = polynomRandDoubleDouble.evalueError( vecFirstDataPointWrong );
				
				if ( paError.first == 0 ){
					cerr<<"Error: The polynom dos match the "<<uiPointsIncluded<<
						"'th range data point, but shouldn't."<<endl;
					iReturn++;
				}
			}
		}else{// uiPointsIncluded == 0
			if ( (0 < uiDataPointsToGenerate) && ( 0.0 < maxValue ) && ( 0 < uiNumberOfParameters ) ){
				if ( (vecDataPoints[ 0 ].minY < maxValue) &&
						( (-1.0 * vecDataPoints[ 0 ].maxY) < maxValue) ){
					cerr<<"Error: Ther wher range data points generated, but non included."<<endl;
					iReturn++;
				}
			}
			if ( polynomRandDoubleDoubleOld != polynomRandDoubleDouble ){
				cerr<<"Error: The polynom was changed for the datapoints, but shouldn't be (because non evalued)."<<endl;
				cerr<<"It should be unchanged:"<<endl;
				polynomRandDoubleDoubleOld.print( cerr );
				iReturn++;
			}
		}

		if ( compareVectorDouble( polynomRandDoubleDouble.vecFactors,
				polynomRandDoubleDoubleOld.vecFactors ) ){
			//vector factors not changed
			if ( ! ( polynomRandDoubleDoubleOld == polynomRandDoubleDouble ) ){
				cerr<<"Error: The polynom is not changed, but is not equal ( not == ) to the old polynom."<<endl;
				iReturn++;
			}
			if ( polynomRandDoubleDoubleOld != polynomRandDoubleDouble ){
				cerr<<"Error: The polynom is not changed, but is not equal ( != ) to the old polynom."<<endl;
				iReturn++;
			}
		}else{//vector factors changed
			if ( polynomRandDoubleDoubleOld == polynomRandDoubleDouble ){
				cerr<<"Error: The polynom is changed, but is equal ( == ) to the old polynom."<<endl;
				iReturn++;
			}
			if ( ! ( polynomRandDoubleDoubleOld != polynomRandDoubleDouble ) ){
				cerr<<"Error: The polynom is changed, but is not not  equal ( not != ) to the old polynom."<<endl;
				iReturn++;
			}
		}
	}

	return iReturn;
}



/**
 * This function tests the evalueSpline() function of the cPolynom class.
 *
 * metods tested:
 * 	- unsigned long evalueSplineIterativFast( const vector< cDataPointRange< tX, tY> > & vecData, unsigned int uiMaxNumberOfParameters, const unsigned int uiMinBitsToStoreMantissa, const tY maxValue, const tY maxError, const unsigned long ulMaxMemoryCost);
 * 	- bool operator==( const cPolynom<tX, tY> & polynom ) const;
 * 	- bool operator!=( const cPolynom<tX, tY> & polynom ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param iWarnings a reference to the integer variable for the warnings
 * @return the number of errors occured in the test
 */
int testEvalueSplineIterativFast( unsigned long &ulTestphase, int & iWarnings ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalueSplineIterativFast() method for creating random polynoms of type domain(x) = int and domain(y) = double"<<endl;
	
	cout<<"cPolynom< int, double > polynomRandIntDouble;"<<endl;
	cPolynom< int, double > polynomRandIntDouble;
	
	unsigned long ulSplinesGenerated = 0;
	unsigned int uiMaxParameter = 3;
	unsigned long ulNextParameterIncrease = 8;
	
	for ( unsigned int uiIteration = 0; uiIteration < (MAX_ITERATION / 16 + 1); uiIteration++ ){
		
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating "<<uiIteration<<"'th random polynom"<<endl;
		
		ulSplinesGenerated++;
		if ( ulNextParameterIncrease < ulSplinesGenerated ){
			//increase max dimension with 1
			uiMaxParameter++;
			ulNextParameterIncrease *= ulNextParameterIncrease;
		}
		
		unsigned int uiNumberOfParameters = 0;
		if ( rand() % 32 ){
			uiNumberOfParameters = rand() % uiMaxParameter + 1;
		}//else uiNumberOfParameters = 0;
		
		cPolynom< int, double > generatorPolynomIntDouble;
		
		unsigned int uiNumberOfGeneratorPolynomFactors = uiNumberOfParameters;
		
		if ( ( (rand() % 8) == 0) ){
			//use generator polynom with diffent number of factors
			uiNumberOfGeneratorPolynomFactors = rand() % uiMaxParameter + 1;
		}
		if ( uiNumberOfGeneratorPolynomFactors == 0 ){
			uiNumberOfGeneratorPolynomFactors = 1;
		}
		double dMaxFactorValue = 10000.0;
		for ( unsigned int uiActualFactor = 0;
				uiActualFactor < uiNumberOfGeneratorPolynomFactors; uiActualFactor++){
			
			generatorPolynomIntDouble.vecFactors.push_back(
				randomValue( dMaxFactorValue ) );
			if ( 8.0 < dMaxFactorValue ){
				dMaxFactorValue /= 8.0;
			}
		}
		cout<<"Polynom from which the datapoints are generated:"<<endl;
		generatorPolynomIntDouble.print( cout );
		
		unsigned int uiDataPointsToGenerate = 0;
		if ( rand() % 32 ){
			uiDataPointsToGenerate = rand() % ( (rand() % 64) + 1 ) + 1;
		}//else  uiDataPointsToGenerate = 0;
		cout<<"vector< cDataPointRange< int, double > > vecDataPoints (size="<<
			uiDataPointsToGenerate<<"): {";
		vector< cDataPointRange< int, double > > vecDataPoints;
		
		//if bXIsRandom is true the x is generated random, else in increased
		bool bXIsRandom = ((rand() % 8) == 0);
		int iLastX = ((int)(uiDataPointsToGenerate)) / -2;
		const int uiMaxXValueForRandGenerator = 8 * uiDataPointsToGenerate;
		
		for ( unsigned int uiGeneratedDataPoints = 0;
				uiGeneratedDataPoints < uiDataPointsToGenerate;
				uiGeneratedDataPoints++ ){
			
			int x;
			if ( bXIsRandom ){
				x = randomValue( uiMaxXValueForRandGenerator );
			}else{
				if ( rand() % 32 ){
					x = iLastX + 1;
				}else{
					x = iLastX + rand() % ( (rand() % 32) + 1 );
				}
			}
			iLastX = x;
			
			const double y = generatorPolynomIntDouble.evalue( x );
			const double minY = y - absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			double maxY = y + absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			if ( ( rand() % 32 ) == 0 ){
				maxY = minY + absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			}
			if ( maxY <= minY ){
				maxY = minY + 0.0001;
			}
			
			cout<<"("<<x<<", "<<minY<<" till "<<maxY<<") ";
			vecDataPoints.push_back( cDataPointRange< int, double >( x, minY, maxY ) );
		}
		cout<<"} "<<endl;
		
		const cPolynom< int, double > polynomRandIntDoubleOld( polynomRandIntDouble );
		
		double maxValue = abs( randomValue( 1000000.0 ) ) + 1000.0;
		if ( (rand() % 8) == 0 ){
			maxValue = randomValue( 1000000.0 );
		}
		
#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		cout<<endl<<"polynomRandIntDouble.evalueSplineIterativFast( vecDataPoints, uiNumberOfParameters="<<
			uiNumberOfParameters<<", maxValue="<<maxValue<<");"<<endl<<endl;
		unsigned long uiPointsIncluded = polynomRandIntDouble.evalueSplineIterativFast(
			vecDataPoints, uiNumberOfParameters, maxValue );
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		const unsigned int uiMinBitsToStoreMantissa = rand() % 32;
		cout<<endl<<"polynomRandIntDouble.evalueSplineIterativFast( vecDataPoints, uiNumberOfParameters="<<
			uiNumberOfParameters<<", uiMinBitsToStoreMantissa="<<
			uiMinBitsToStoreMantissa<<" , maxValue="<<maxValue<<");"<<endl<<endl;
		unsigned long uiPointsIncluded = polynomRandIntDouble.evalueSplineIterativFast(
			vecDataPoints, uiNumberOfParameters, uiMinBitsToStoreMantissa, maxValue );
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		
		if ( 0 < uiPointsIncluded ){
			cout<<"Founded polynom is for the "<<uiPointsIncluded<<" first "<<
				( (uiPointsIncluded == uiDataPointsToGenerate)?"(=all) ":"" )<<
				"range data points:"<<endl;
			polynomRandIntDouble.print( cout );
		}else{
			cout<<"No new polynom generated."<<endl;
		}
		
		if ( uiDataPointsToGenerate < uiPointsIncluded ){
			cerr<<"Error: Ther wher "<<uiPointsIncluded<<" but only "<<
				uiDataPointsToGenerate<<" points to include ."<<endl;
			iReturn++;
		}
		
		if ( 0 < uiPointsIncluded ){
			
			if ( ( 0 < uiNumberOfParameters ) &&
					(uiNumberOfParameters < polynomRandIntDouble.vecFactors.size()) ){
				cerr<<"Error: The polynom has "<<polynomRandIntDouble.vecFactors.size()<<
					" parameters, but should have maximal "<<uiNumberOfParameters<<" ."<<endl;
				iReturn++;
			}
			for ( unsigned int uiActualFactor = 0;
					uiActualFactor < polynomRandIntDouble.vecFactors.size(); uiActualFactor++ ){
				
				if ( maxValue < abs( polynomRandIntDouble.vecFactors[ uiActualFactor ] * 0.999 ) ){
					cerr<<"Error: The polynom has as the "<<uiActualFactor<<
						"'th factor ("<<polynomRandIntDouble.vecFactors[ uiActualFactor ]<<
						") greater than the maxValue of "<<maxValue<<" ."<<endl;
					iReturn++;
				}
			}
			/* check if the polynom match the range data points*/
			vector< cDataPointRange< int, double > > vecDataPointsCorrect =
				vecDataPoints;
			sort( vecDataPointsCorrect.begin(), vecDataPointsCorrect.end() );
			if ( uiPointsIncluded < uiDataPointsToGenerate ){
				vecDataPointsCorrect.resize( uiPointsIncluded );
			}
			
			pair< unsigned long, double > paError = polynomRandIntDouble.evalueError(
				vecDataPointsCorrect );
			
			if ( ERROR_ALLWAYS_OK < paError.second ){
				cerr<<"Warning: The polynom dosn't match the "<<uiPointsIncluded<<
					" first range data points.";
				cerr<<" Ther are "<<paError.first<<" wrong points with a error sum of "<<
					paError.second<<" ."<<endl;
				iWarnings++;
			}
			
			if ( uiPointsIncluded < uiDataPointsToGenerate ){
				vector< cDataPointRange< int, double > > vecFirstDataPointWrong =
					vecDataPoints;
				vecFirstDataPointWrong.push_back( vecDataPoints[ uiPointsIncluded ] );
				
				paError = polynomRandIntDouble.evalueError( vecFirstDataPointWrong );
				
				if ( paError.first == 0 ){
					cerr<<"Error: The polynom dos match the "<<uiPointsIncluded<<
						"'th range data point, but shouldn't."<<endl;
					iReturn++;
				}
			}
		}else{// uiPointsIncluded == 0
			if ( (0 < uiDataPointsToGenerate) && ( 0.0 < maxValue ) && ( 0 < uiNumberOfParameters ) ){
				if ( (vecDataPoints[ 0 ].minY < maxValue) &&
						( (-1.0 * vecDataPoints[ 0 ].maxY) < maxValue) ){
					cerr<<"Error: Ther wher range data points generated, but non included."<<endl;
					iReturn++;
				}
			}
			if ( polynomRandIntDoubleOld != polynomRandIntDouble ){
				cerr<<"Error: The polynom was changed for the datapoints, but shouldn't be (because non evalued)."<<endl;
				cerr<<"It should be unchanged:"<<endl;
				polynomRandIntDoubleOld.print( cerr );
				iReturn++;
			}
		}

		if ( compareVectorDouble( polynomRandIntDouble.vecFactors,
				polynomRandIntDoubleOld.vecFactors ) ){
			//vector factors not changed
			if ( ! ( polynomRandIntDoubleOld == polynomRandIntDouble ) ){
				cerr<<"Error: The polynom is not changed, but is not equal ( not == ) to the old polynom."<<endl;
				iReturn++;
			}
			if ( polynomRandIntDoubleOld != polynomRandIntDouble ){
				cerr<<"Error: The polynom is not changed, but is not equal ( != ) to the old polynom."<<endl;
				iReturn++;
			}
		}else{//vector factors changed
			if ( polynomRandIntDoubleOld == polynomRandIntDouble ){
				cerr<<"Error: The polynom is changed, but is equal ( == ) to the old polynom."<<endl;
				iReturn++;
			}
			if ( ! ( polynomRandIntDoubleOld != polynomRandIntDouble ) ){
				cerr<<"Error: The polynom is changed, but is not not  equal ( not != ) to the old polynom."<<endl;
				iReturn++;
			}
		}
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalueSplineIterativFast() method for creating random polynoms of type domain(x) = double and domain(y) = double"<<endl;
	
	cout<<"cPolynom< double, double > polynomRandDoubleDouble;"<<endl;
	cPolynom< double, double > polynomRandDoubleDouble;
	
	ulSplinesGenerated = 0;
	uiMaxParameter = 3;
	ulNextParameterIncrease = 8;
	
	for ( unsigned int uiIteration = 0; uiIteration < (MAX_ITERATION / 16 + 1); uiIteration++ ){
		
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating "<<uiIteration<<"'th random polynoms"<<endl;
		
		ulSplinesGenerated++;
		if ( ulNextParameterIncrease < ulSplinesGenerated ){
			//increase max dimension with 1
			uiMaxParameter++;
			ulNextParameterIncrease *= ulNextParameterIncrease;
		}
		
		unsigned int uiNumberOfParameters = 0;
		if ( rand() % 32 ){
			uiNumberOfParameters = rand() % uiMaxParameter + 1;
		}//else uiNumberOfParameters = 0;
		cPolynom< double, double > generatorPolynomDoubleDouble;
		
		unsigned int uiNumberOfGeneratorPolynomFactors = uiNumberOfParameters;
		
		if ( ( (rand() % 8) == 0) ){
			//use generator polynom with diffent number of factors
			uiNumberOfGeneratorPolynomFactors = rand() % uiMaxParameter + 1;
		}
		if ( uiNumberOfGeneratorPolynomFactors == 0 ){
			uiNumberOfGeneratorPolynomFactors = 1;
		}
		double dMaxFactorValue = 10000.0;
		for ( unsigned int uiActualFactor = 0;
				uiActualFactor < uiNumberOfGeneratorPolynomFactors; uiActualFactor++){
			
			generatorPolynomDoubleDouble.vecFactors.push_back(
				randomValue( dMaxFactorValue ) );
			if ( 8.0 < dMaxFactorValue ){
				dMaxFactorValue /= 8.0;
			}
		}
		cout<<"Polynom from which the datapoints are generated:"<<endl;
		generatorPolynomDoubleDouble.print( cout );
		
		unsigned int uiDataPointsToGenerate = 0;
		if ( rand() % 32 ){
			uiDataPointsToGenerate = rand() % ( (rand() % 64) + 1 ) + 1;
		}//else  uiDataPointsToGenerate = 0;
		cout<<"vector< cDataPointRange< double, double > > vecDataPoints (size="<<
			uiDataPointsToGenerate<<"): {";
		vector< cDataPointRange< double, double > > vecDataPoints;
		
		//if bXIsRandom is true the x is generated random, else in increased
		bool bXIsRandom = ((rand() % 8) == 0);
		double iLastX = ((int)(uiDataPointsToGenerate)) / -2;
		const double dMaxXValueForRandGenerator = 8 * uiDataPointsToGenerate;
		
		for ( unsigned int uiGeneratedDataPoints = 0;
				uiGeneratedDataPoints < uiDataPointsToGenerate;
				uiGeneratedDataPoints++ ){
			
			double x;
			if ( bXIsRandom ){
				x = randomValue( dMaxXValueForRandGenerator );
			}else{
				if ( rand() % 32 ){
					x = iLastX + 1.0;
				}else{
					x = iLastX + randomValue( dMaxXValueForRandGenerator / 32.0 + 4.0 );
				}
			}
			iLastX = x;
			
			const double y = generatorPolynomDoubleDouble.evalue( x );
			const double minY = y - absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			double maxY = y + absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			if ( ( rand() % 32 ) == 0 ){
				maxY = minY + absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			}
			if ( maxY <= minY ){
				maxY = minY + 0.0001;
			}
			
			cout<<"("<<x<<", "<<minY<<" till "<<maxY<<") ";
			vecDataPoints.push_back( cDataPointRange< double, double >( x, minY, maxY ) );
		}
		cout<<"} "<<endl;
		
		const cPolynom< double, double > polynomRandDoubleDoubleOld( polynomRandDoubleDouble );
		
		double maxValue = abs( randomValue( 1000000.0 ) ) + 1000.0;
		if ( (rand() % 8) == 0 ){
			maxValue = randomValue( 1000000.0 );
		}
		
#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		cout<<endl<<"polynomRandDoubleDouble.evalueSplineIterativFast( vecDataPoints, uiNumberOfParameters="<<
			uiNumberOfParameters<<", maxValue="<<maxValue<<");"<<endl<<endl;
		unsigned long uiPointsIncluded = polynomRandDoubleDouble.evalueSplineIterativFast(
			vecDataPoints, uiNumberOfParameters, maxValue );
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		const unsigned int uiMinBitsToStoreMantissa = rand() % 32;
		cout<<endl<<"polynomRandDoubleDouble.evalueSplineIterativFast( vecDataPoints, uiNumberOfParameters="<<
			uiNumberOfParameters<<", uiMinBitsToStoreMantissa="<<
			uiMinBitsToStoreMantissa<<" , maxValue="<<maxValue<<");"<<endl<<endl;
		unsigned long uiPointsIncluded = polynomRandDoubleDouble.evalueSplineIterativFast(
			vecDataPoints, uiNumberOfParameters, uiMinBitsToStoreMantissa, maxValue );
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		
		if ( 0 < uiPointsIncluded ){
			cout<<"Founded polynom is for the "<<uiPointsIncluded<<" first "<<
				( (uiPointsIncluded == uiDataPointsToGenerate)?"(=all) ":"" )<<
				"range data points:"<<endl;
			polynomRandDoubleDouble.print( cout );
		}else{
			cout<<"No new polynom generated."<<endl;
		}
		
		if ( uiDataPointsToGenerate < uiPointsIncluded ){
			cerr<<"Error: Ther wher "<<uiPointsIncluded<<" but only "<<
				uiDataPointsToGenerate<<" points to include ."<<endl;
			iReturn++;
		}
		
		if ( 0 < uiPointsIncluded ){
			
			if ( ( 0 < uiNumberOfParameters ) &&
					(uiNumberOfParameters < polynomRandDoubleDouble.vecFactors.size()) ){
				cerr<<"Error: The polynom has "<<polynomRandDoubleDouble.vecFactors.size()<<
					" parameters, but should have maximal "<<uiNumberOfParameters<<" ."<<endl;
				iReturn++;
			}
			for ( unsigned int uiActualFactor = 0;
					uiActualFactor < polynomRandDoubleDouble.vecFactors.size(); uiActualFactor++ ){
				
				if ( maxValue < abs( polynomRandDoubleDouble.vecFactors[ uiActualFactor ] * 0.999 ) ){
					cerr<<"Error: The polynom has as the "<<uiActualFactor<<
						"'th factor ("<<polynomRandDoubleDouble.vecFactors[ uiActualFactor ]<<
						") greater than the maxValue of "<<maxValue<<" ."<<endl;
					iReturn++;
				}
			}
			/* check if the polynom match the range data points*/
			vector< cDataPointRange< double, double > > vecDataPointsCorrect =
				vecDataPoints;
			sort( vecDataPointsCorrect.begin(), vecDataPointsCorrect.end() );
			if ( uiPointsIncluded < uiDataPointsToGenerate ){
				vecDataPointsCorrect.resize( uiPointsIncluded );
			}
			
			pair< unsigned long, double > paError = polynomRandDoubleDouble.evalueError(
				vecDataPointsCorrect );
			
			if ( ERROR_ALLWAYS_OK < paError.second ){
				cerr<<"Warning: The polynom dosn't match the "<<uiPointsIncluded<<
					" first range data points.";
				cerr<<" Ther are "<<paError.first<<" wrong points with a error sum of "<<
					paError.second<<" ."<<endl;
				iWarnings++;
			}
			
			if ( uiPointsIncluded < uiDataPointsToGenerate ){
				vector< cDataPointRange< double, double > > vecFirstDataPointWrong =
					vecDataPoints;
				vecFirstDataPointWrong.push_back( vecDataPoints[ uiPointsIncluded ] );
				
				paError = polynomRandDoubleDouble.evalueError( vecFirstDataPointWrong );
				
				if ( paError.first == 0 ){
					cerr<<"Error: The polynom dos match the "<<uiPointsIncluded<<
						"'th range data point, but shouldn't."<<endl;
					iReturn++;
				}
			}
		}else{// uiPointsIncluded == 0
			if ( (0 < uiDataPointsToGenerate) && ( 0.0 < maxValue ) && ( 0 < uiNumberOfParameters ) ){
				if ( (vecDataPoints[ 0 ].minY < maxValue) &&
						( (-1.0 * vecDataPoints[ 0 ].maxY) < maxValue) ){
					cerr<<"Error: Ther wher range data points generated, but non included."<<endl;
					iReturn++;
				}
			}
			if ( polynomRandDoubleDoubleOld != polynomRandDoubleDouble ){
				cerr<<"Error: The polynom was changed for the datapoints, but shouldn't be (because non evalued)."<<endl;
				cerr<<"It should be unchanged:"<<endl;
				polynomRandDoubleDoubleOld.print( cerr );
				iReturn++;
			}
		}

		if ( compareVectorDouble( polynomRandDoubleDouble.vecFactors,
				polynomRandDoubleDoubleOld.vecFactors ) ){
			//vector factors not changed
			if ( ! ( polynomRandDoubleDoubleOld == polynomRandDoubleDouble ) ){
				cerr<<"Error: The polynom is not changed, but is not equal ( not == ) to the old polynom."<<endl;
				iReturn++;
			}
			if ( polynomRandDoubleDoubleOld != polynomRandDoubleDouble ){
				cerr<<"Error: The polynom is not changed, but is not equal ( != ) to the old polynom."<<endl;
				iReturn++;
			}
		}else{//vector factors changed
			if ( polynomRandDoubleDoubleOld == polynomRandDoubleDouble ){
				cerr<<"Error: The polynom is changed, but is equal ( == ) to the old polynom."<<endl;
				iReturn++;
			}
			if ( ! ( polynomRandDoubleDoubleOld != polynomRandDoubleDouble ) ){
				cerr<<"Error: The polynom is changed, but is not not  equal ( not != ) to the old polynom."<<endl;
				iReturn++;
			}
		}
	}




	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalueSplineIterativFast() method for creating random polynoms; a maximal error (maxError) value is given"<<endl;
	
	cout<<"cPolynom< double, double > polynomRandDoubleDouble2;"<<endl;
	cPolynom< double, double > polynomRandDoubleDouble2;
	
	ulSplinesGenerated = 0;
	uiMaxParameter = 3;
	ulNextParameterIncrease = 8;
	
	for ( unsigned int uiIteration = 0; uiIteration < (MAX_ITERATION / 16 + 1); uiIteration++ ){
		
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating "<<uiIteration<<"'th random polynoms"<<endl;
		
		ulSplinesGenerated++;
		if ( ulNextParameterIncrease < ulSplinesGenerated ){
			//increase max dimension with 1
			uiMaxParameter++;
			ulNextParameterIncrease *= ulNextParameterIncrease;
		}
		
		unsigned int uiNumberOfParameters = 0;
		if ( rand() % 32 ){
			uiNumberOfParameters = rand() % uiMaxParameter + 1;
		}//else uiNumberOfParameters = 0;
		cPolynom< double, double > generatorPolynomDoubleDouble;
		
		unsigned int uiNumberOfGeneratorPolynomFactors = uiNumberOfParameters;
		
		if ( ( (rand() % 8) == 0) ){
			//use generator polynom with diffent number of factors
			uiNumberOfGeneratorPolynomFactors = rand() % uiMaxParameter + 1;
		}
		if ( uiNumberOfGeneratorPolynomFactors == 0 ){
			uiNumberOfGeneratorPolynomFactors = 1;
		}
		double dMaxFactorValue = 10000.0;
		for ( unsigned int uiActualFactor = 0;
				uiActualFactor < uiNumberOfGeneratorPolynomFactors; uiActualFactor++){
			
			generatorPolynomDoubleDouble.vecFactors.push_back(
				randomValue( dMaxFactorValue ) );
			if ( 8.0 < dMaxFactorValue ){
				dMaxFactorValue /= 8.0;
			}
		}
		cout<<"Polynom from which the datapoints are generated:"<<endl;
		generatorPolynomDoubleDouble.print( cout );
		
		unsigned int uiDataPointsToGenerate = 0;
		if ( rand() % 32 ){
			uiDataPointsToGenerate = rand() % ( (rand() % 64) + 1 ) + 1;
		}//else  uiDataPointsToGenerate = 0;
		cout<<"vector< cDataPointRange< double, double > > vecDataPoints (size="<<
			uiDataPointsToGenerate<<"): {";
		vector< cDataPointRange< double, double > > vecDataPoints;
		
		//if bXIsRandom is true the x is generated random, else in increased
		bool bXIsRandom = ((rand() % 8) == 0);
		double iLastX = ((int)(uiDataPointsToGenerate)) / -2;
		const double dMaxXValueForRandGenerator = 8 * uiDataPointsToGenerate;
		
		for ( unsigned int uiGeneratedDataPoints = 0;
				uiGeneratedDataPoints < uiDataPointsToGenerate;
				uiGeneratedDataPoints++ ){
			
			double x;
			if ( bXIsRandom ){
				x = randomValue( dMaxXValueForRandGenerator );
			}else{
				if ( rand() % 32 ){
					x = iLastX + 1.0;
				}else{
					x = iLastX + randomValue( dMaxXValueForRandGenerator / 32.0 + 4.0 );
				}
			}
			iLastX = x;
			
			const double y = generatorPolynomDoubleDouble.evalue( x );
			const double minY = y - absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			double maxY = y + absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			if ( ( rand() % 32 ) == 0 ){
				maxY = minY + absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			}
			if ( maxY <= minY ){
				maxY = minY + 0.0001;
			}
			
			cout<<"("<<x<<", "<<minY<<" till "<<maxY<<") ";
			vecDataPoints.push_back( cDataPointRange< double, double >( x, minY, maxY ) );
		}
		cout<<"} "<<endl;
		
		const cPolynom< double, double > polynomRandDoubleDouble2Old( polynomRandDoubleDouble2 );
		
		double maxValue = abs( randomValue( 1000000.0 ) ) + 1000.0;
		if ( (rand() % 8) == 0 ){
			maxValue = randomValue( 1000000.0 );
		}
		
		double dMaxError = randomValue( 1000000.0 );
		if ( rand() % 16 ){
			dMaxError = abs( dMaxError );
		}
		
#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		cout<<endl<<"polynomRandDoubleDouble2.evalueSplineIterativFast( vecDataPoints, uiNumberOfParameters="<<
			uiNumberOfParameters<<", maxValue="<<maxValue<<", dMaxError="<<dMaxError<<");"<<endl<<endl;
		unsigned long uiPointsIncluded = polynomRandDoubleDouble2.evalueSplineIterativFast(
			vecDataPoints, uiNumberOfParameters, maxValue, dMaxError );
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		const unsigned int uiMinBitsToStoreMantissa = rand() % 32;
		cout<<endl<<"polynomRandDoubleDouble2.evalueSplineIterativFast( vecDataPoints, uiNumberOfParameters="<<
			uiNumberOfParameters<<", uiMinBitsToStoreMantissa="<<
			uiMinBitsToStoreMantissa<<" , maxValue="<<maxValue<<", dMaxError="<<dMaxError<<");"<<endl<<endl;
		unsigned long uiPointsIncluded = polynomRandDoubleDouble2.evalueSplineIterativFast(
			vecDataPoints, uiNumberOfParameters, uiMinBitsToStoreMantissa, maxValue, dMaxError );
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		
		if ( 0 < uiPointsIncluded ){
			cout<<"Founded polynom is for the "<<uiPointsIncluded<<" first "<<
				( (uiPointsIncluded == uiDataPointsToGenerate)?"(=all) ":"" )<<
				"range data points:"<<endl;
			polynomRandDoubleDouble2.print( cout );
		}else{
			cout<<"No new polynom generated."<<endl;
		}
		
		if ( uiDataPointsToGenerate < uiPointsIncluded ){
			cerr<<"Error: Ther wher "<<uiPointsIncluded<<" but only "<<
				uiDataPointsToGenerate<<" points to include ."<<endl;
			iReturn++;
		}
		
		if ( 0 < uiPointsIncluded ){
			
			if ( ( 0 < uiNumberOfParameters ) &&
					(uiNumberOfParameters < polynomRandDoubleDouble2.vecFactors.size()) ){
				cerr<<"Error: The polynom has "<<polynomRandDoubleDouble2.vecFactors.size()<<
					" parameters, but should have maximal "<<uiNumberOfParameters<<" ."<<endl;
				iReturn++;
			}
			for ( unsigned int uiActualFactor = 0;
					uiActualFactor < polynomRandDoubleDouble2.vecFactors.size(); uiActualFactor++ ){
				
				if ( maxValue < abs( polynomRandDoubleDouble2.vecFactors[ uiActualFactor ] * 0.999 ) ){
					cerr<<"Error: The polynom has as the "<<uiActualFactor<<
						"'th factor ("<<polynomRandDoubleDouble2.vecFactors[ uiActualFactor ]<<
						") greater than the maxValue of "<<maxValue<<" ."<<endl;
					iReturn++;
				}
			}
			/* check if the polynom match the range data points*/
			vector< cDataPointRange< double, double > > vecDataPointsCorrect =
				vecDataPoints;
			sort( vecDataPointsCorrect.begin(), vecDataPointsCorrect.end() );
			if ( uiPointsIncluded < uiDataPointsToGenerate ){
				vecDataPointsCorrect.resize( uiPointsIncluded );
			}
			
			pair< unsigned long, double > paError = polynomRandDoubleDouble2.evalueError(
				vecDataPointsCorrect );
			
			if ( ( dMaxError + ERROR_ALLWAYS_OK ) < (paError.second * 0.99) ){
				cerr<<"Warning: The polynom dosn't match the "<<uiPointsIncluded<<
					" first range data points.";
				cerr<<" Ther are "<<paError.first<<" wrong points with a error sum of "<<
					paError.second<<" ."<<endl;
				iWarnings++;
			}
			
			if ( uiPointsIncluded < uiDataPointsToGenerate ){
				vector< cDataPointRange< double, double > > vecFirstDataPointWrong =
					vecDataPoints;
				vecFirstDataPointWrong.push_back( vecDataPoints[ uiPointsIncluded ] );
				
				paError = polynomRandDoubleDouble2.evalueError( vecFirstDataPointWrong );
				
				if ( paError.first == 0 ){
					cerr<<"Error: The polynom dos match the "<<uiPointsIncluded<<
						"'th range data point, but shouldn't."<<endl;
					iReturn++;
				}
			}
		}else{// uiPointsIncluded == 0
			if ( (0 < uiDataPointsToGenerate) && ( 0.0 < maxValue ) &&
					( 0 < uiNumberOfParameters ) && ( 0.0 <= dMaxError ) ){
				if ( (vecDataPoints[ 0 ].minY < maxValue) &&
						( (-1.0 * vecDataPoints[ 0 ].maxY) < maxValue) ){
					cerr<<"Error: Ther wher range data points generated, but non included."<<endl;
					iReturn++;
				}
			}
			if ( polynomRandDoubleDouble2Old != polynomRandDoubleDouble2 ){
				cerr<<"Error: The polynom was changed for the datapoints, but shouldn't be (because non evalued)."<<endl;
				cerr<<"It should be unchanged:"<<endl;
				polynomRandDoubleDouble2Old.print( cerr );
				iReturn++;
			}
		}

		if ( compareVectorDouble( polynomRandDoubleDouble2.vecFactors,
				polynomRandDoubleDouble2Old.vecFactors ) ){
			//vector factors not changed
			if ( ! ( polynomRandDoubleDouble2Old == polynomRandDoubleDouble2 ) ){
				cerr<<"Error: The polynom is not changed, but is not equal ( not == ) to the old polynom."<<endl;
				iReturn++;
			}
			if ( polynomRandDoubleDouble2Old != polynomRandDoubleDouble2 ){
				cerr<<"Error: The polynom is not changed, but is not equal ( != ) to the old polynom."<<endl;
				iReturn++;
			}
		}else{//vector factors changed
			if ( polynomRandDoubleDouble2Old == polynomRandDoubleDouble2 ){
				cerr<<"Error: The polynom is changed, but is equal ( == ) to the old polynom."<<endl;
				iReturn++;
			}
			if ( ! ( polynomRandDoubleDouble2Old != polynomRandDoubleDouble2 ) ){
				cerr<<"Error: The polynom is changed, but is not not  equal ( not != ) to the old polynom."<<endl;
				iReturn++;
			}
		}
	}

/*TODO:
evalueSplineIterativFast( const vector< cDataPointRange< tX, tY> > & vecData, unsigned int uiMaxNumberOfParameters, const unsigned int uiMinBitsToStoreMantissa, const tY maxValue, const tY maxError, const unsigned long ulMaxMemoryCost );

for not standard ulMaxMemoryCost

*/

	return iReturn;
}














