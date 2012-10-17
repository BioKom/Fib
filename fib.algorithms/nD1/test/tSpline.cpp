/**
 * @file tSpline
 * file name: tSpline.cpp
 * @author Betti Oesterholz
 * @date 30.06.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cSpline.
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
 * This file contains the test for the class cSpline, which
 * represents splines.
 *
 *
 * What's tested of class cSpline:
 * 	- tY evalue( const tX & x ) const;
 * 	- void print( ostream & outputStream ) const;
 * 	- pair<unsigned long, tY> evalueError( const vector< cDataPoint< tX, tY> > & vecInput ) const;
 * 	- tY evalueErrorMax( const vector< cDataPoint< tX, tY> > & vecData, const tY maxYError ) const;
 * 	- pair<unsigned long, tY> evalueError( const vector< cDataPointRange< tX, tY> > & vecInput ) const;
 * 	- tY evalueErrorMax( const vector< cDataPointRange< tX, tY> > & vecData, const tY maxYError ) const;
 * 	- template<class tY> cUnderFunction * toFibUnderFunction( cFibVariable * pVariable );
 * 	- virtual bool evalue( const vector< cDataPoint< tX, tY> > & vecData );
 * 	- unsigned long evalueSpline( const vector< cDataPointRange< tX, tY> > & vecData, unsigned int uiMaxNumberOfParameters, const unsigned int uiMinBitsToStoreMantissa, const tY maxValue, const tY maxError, const unsigned long ulMaxMemoryCost );
 * 	- bool operator==( const cSpline<tX, tY> & spline ) const;
 * 	- bool operator!=( const cSpline<tX, tY> & spline ) const;
 *
 *
 * call: tSpline [ITERATIONS]
 *
 * parameters:
 * 	ITERATIONS
 * 		The iterations for the test with random generated datapoints.
 * 		Standardvalue is 256.
 */
/*
History:
30.06.2011  Oesterholz  created (copy of test tPolynom.cpp)
27.09.2012  Oesterholz  FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING:
	evalueSpline(): the glp library (extern package) linear solver will be
	used to find a spline for a vector of range data points
*/

//TODO for test
//#define DEBUG


#include "cSpline.h"

#include "cPolynom.h"
#include "cFibVariable.h"
#include "cUnderFunction.h"
#include "cFunctionValue.h"
#include "cFunctionVariable.h"
#include "cFunctionIf.h"
#include "cFunctionAdd.h"
#include "cFunctionMult.h"
#include "cFunctionExp.h"

#include <ctime>
#include <stack>
#include <algorithm>


using namespace fib;
using namespace std;
using namespace fib::algorithms::nD1;

int testEvalue( unsigned long &ulTestphase );
int testSplineToFibUnderFunction( unsigned long &ulTestphase );
int testSplineEvalue( unsigned long &ulTestphase, int & iWarnings );
int testEvalueSpline( unsigned long &ulTestphase, int & iWarnings );


unsigned long MAX_ITERATION = 256;


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

	cout<<endl<<"Running Test for cSpline methods"<<endl;
	cout<<      "================================"<<endl;
	
	iWarnings += testEvalue( ulTestphase );
	iReturn += testSplineToFibUnderFunction( ulTestphase );
	iReturn += testSplineEvalue( ulTestphase, iWarnings );
	iReturn += testEvalueSpline( ulTestphase, iWarnings );

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
 * This function tests the mothods for evaluing the spline of the class
 * cSpline for a given spline.
 *
 * metods tested:
 * 	- tY evalue( const tX & x ) const;
 * 	- pair<unsigned long, tY> evalueError( const vector< cDataPoint< tX, tY> > & vecInput ) const;
 * 	- tY evalueErrorMax( const vector< cDataPoint< tX, tY> > & vecData, const tY maxYWarning ) const;
 * 	- pair<unsigned long, tY> evalueError( const vector< cDataPointRange< tX, tY> > & vecInput ) const;
 * 	- tY evalueErrorMax( const vector< cDataPointRange< tX, tY> > & vecData, const tY maxYWarning ) const;
 *
 * @param spline the spline for wich to check the evalue methods
 * @param vecX a vector with the x (input) values for the spline to evalue
 * @param vecCorrectY a vector with the correct y (output) values to
 * 	which the given vecX values should be evalued by the given spline:
 * 		vecCorrectY[i] = spline.evalue( vecX[i] )
 * @return the number of warnings occured in the test
 */
template< class tX, class tY > int testEvalue( const cSpline< tX, tY > & spline,
		const vector< tX > vecX, const vector< tY > vecCorrectY ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Warnings
	//check the evalue function
	int iWarningsEvalue = 0;
	cout<<"Checking evalue() method:"<<endl;
	const unsigned int uiNumberOfGivenValues =
		min( vecX.size(), vecCorrectY.size() );
	for ( unsigned int uiActualValue = 0;
			uiActualValue < uiNumberOfGivenValues; uiActualValue++ ){
		
		if ( spline.evalue( vecX[ uiActualValue ] ) != vecCorrectY[ uiActualValue ] ){
			cerr<<"Warning: The value "<< vecX[ uiActualValue ] <<
				" is evalued to "<< spline.evalue( vecX[ uiActualValue ] ) <<
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
	
	pair<unsigned long, tY> paWarning = spline.evalueError( vecInputData );
	if ( ( paWarning.first != 0 ) || ( paWarning.second != ((tY)(0)) ) ){
		cerr<<"Warning: The method evalueError() of the spline evalues "<<
			paWarning.first<<" wrong data points with a error sum of "<<
			paWarning.second<<" on the input data (wich should be correct) ."<<endl;
		iWarningsEvalueWarning++;
	}
	for ( unsigned int uiActualValue = 0;
			uiActualValue < uiNumberOfGivenValues; uiActualValue++ ){
			
		vector< cDataPoint< tX, tY> > vecOneInputData;
		vecOneInputData.push_back( cDataPoint< tX, tY >( vecX[ uiActualValue ],
			 vecCorrectY[ uiActualValue ] ) );
		
		pair<unsigned long, tY> paWarningOne = spline.evalueError( vecOneInputData );
		if ( ( paWarningOne.first != 0 ) || ( paWarningOne.second != ((tY)(0)) ) ){
			cerr<<"Warning: The method evalueError() of the spline evalues "<<
				paWarningOne.first<<" wrong data points with a error sum of "<<
				paWarningOne.second<<" on the "<<uiActualValue<<
				" input data point =("<<vecX[ uiActualValue ]<<","<<
				vecCorrectY[ uiActualValue ]<<") (wich should be correct) ."<<endl;
			iWarningsEvalueWarning++;
		}
	}
	tY error = spline.evalueErrorMax( vecInputData, 10 );
	if ( error != ((tY)(0))  ){
		cerr<<"Warning: The method evalueErrorMax() of the spline evalues "<<
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
			
			tY correctY = spline.evalue( x );
			tY y = correctY;
			if ( rand() % 2 ){
				//add random error
				tY yWarning = randomValue( ((tY)(10000)) );
				
				if ( ! compareDoubleTest( yWarning, ((tY)(0.0)) ) ){
					//add to wrong points because difference is enougth
					y += yWarning;
					correctWarningOnPoints += abs( yWarning );
					uiWrongPoints++;
				}
			}//else add no random error
			
			vecGeneratedData.push_back( cDataPoint< tX, tY >( x, y ) );
		}
		
		paWarning = spline.evalueError( vecGeneratedData );
		if ( paWarning.first != uiWrongPoints ){
			cerr<<"Warning: The method evalueError() of the spline evalues "<<
				paWarning.first<<" wrong data points, but it should be "<<uiWrongPoints<<" ."<<endl;
			iWarningsEvalueWarning++;
		}
		if ( ! compareDoubleTest( paWarning.second, correctWarningOnPoints ) ){
			cerr<<"Warning: The method evalueError() of the spline evalues a error sum of "<<
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
			
			error = spline.evalueErrorMax( vecGeneratedData, maxWarning );
			if ( ! compareDoubleTest( error, correctMaxWarningOnPoints )  ){
				cerr<<"Warning: The method evalueErrorMax() of the spline evalues a error sum of "<<
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
	
	paWarning = spline.evalueError( vecInputDataRange );
	if ( ( paWarning.first != 0 ) || ( paWarning.second != ((tY)(0)) ) ){
		cerr<<"Warning: The method evalueError() of the spline evalues "<<
			paWarning.first<<" wrong data points with a error sum of "<<
			paWarning.second<<" on the input data (wich should be correct) ."<<endl;
		iWarningsEvalueWarningRange++;
	}
	error = spline.evalueErrorMax( vecInputDataRange, 10 );
	if ( error != ((tY)(0))  ){
		cerr<<"Warning: The method evalueErrorMax() of the spline evalues "<<
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
			
			tY correctY = spline.evalue( x );
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
		
		paWarning = spline.evalueError( vecGeneratedData );
		if ( paWarning.first != uiWrongPoints ){
			cerr<<"Warning: The method evalueError() of the spline evalues "<<
				paWarning.first<<" wrong data points, but it should be "<<uiWrongPoints<<" ."<<endl;
			iWarningsEvalueWarningRange++;
		}
		if ( ! compareDoubleTest( paWarning.second, correctWarningOnPoints ) ){
			cerr<<"Warning: The method evalueError() of the spline evalues a error sum of "<<
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
			
			error = spline.evalueErrorMax( vecGeneratedData, maxWarning );
			if ( ! compareDoubleTest( error, correctMaxWarningOnPoints )  ){
				cerr<<"Warning: The method evalueErrorMax() of the spline evalues a error sum of "<<
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
 * This function tests the mothods for evaluing the spline of the class
 * cSpline.
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

	cout<<endl<<"Testing the mothods for evaluing the spline"<<endl;
	cout<<endl<<"ATTENTION: Please check the printed splines manually"<<endl;
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing a constant spline: y = 8"<<endl;
	
	cout<<"cSpline< int, float > splineConst8; y = 8"<<endl;
	cSpline< int, float > splineConst8;
	
	cPolynom< int, float > polyConst8;
	polyConst8.vecFactors.push_back( 8 );
	
	splineConst8.vecPolynoms.push_back( polyConst8 );
	
	cout<<"splineConst8.print():"<<endl;
	splineConst8.print( cout );
	
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
	
	iReturn += testEvalue( splineConst8, vecIntX, vecFloatY );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing a spline: y = 4 + x"<<endl;
	
	cout<<"cSpline< float, float > spline4p1; y = 4 + x"<<endl;
	cSpline< float, float > spline4p1;
	
	cPolynom< float, float > poly4p1;
	poly4p1.vecFactors.push_back( 4 );
	poly4p1.vecFactors.push_back( 1 );
	
	spline4p1.vecPolynoms.push_back( poly4p1 );
	
	cout<<"spline4p1.print():"<<endl;
	spline4p1.print( cout );
	
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
	
	iReturn += testEvalue( spline4p1, vecFloatX, vecFloatY );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing a spline: y = -1 + 2 * x + 3 * x^2"<<endl;
	
	cout<<"cSpline< float, double > spline1p5p2p3; y = -1 + 2 * x + 3 * x^2"<<endl;
	cSpline< float, double > spline1p5p2p3;
	cPolynom< float, double > polym1p5p2p3;
	polym1p5p2p3.vecFactors.push_back( -1.5 );
	polym1p5p2p3.vecFactors.push_back( 2.0 );
	polym1p5p2p3.vecFactors.push_back( 3.0 );
	
	spline1p5p2p3.vecPolynoms.push_back( polym1p5p2p3 );
	
	cout<<"spline1p5p2p3.print():"<<endl;
	spline1p5p2p3.print( cout );
	
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
	
	iReturn += testEvalue( spline1p5p2p3, vecFloatX, vecDoubleY );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing a spline: y = 3.5 - 0.5 * x + 1.5 * x^2"<<endl;
	
	cout<<"cSpline< double, double > spline3d5pm0d5p1d5;y = 3.5 - 0.5 * x + 1.5 * x^2"<<endl;
	cSpline< double, double > spline3d5pm0d5p1d5;
	cPolynom< double, double > polym3d5pm0d5p1d;
	polym3d5pm0d5p1d.vecFactors.push_back( 3.5 );
	polym3d5pm0d5p1d.vecFactors.push_back( -0.5 );
	polym3d5pm0d5p1d.vecFactors.push_back( 1.5 );
	
	spline3d5pm0d5p1d5.vecPolynoms.push_back( polym3d5pm0d5p1d );

	cout<<"spline3d5pm0d5p1d5.print():"<<endl;
	spline3d5pm0d5p1d5.print( cout );
	
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
	
	iReturn += testEvalue( spline3d5pm0d5p1d5, vecDoubleX, vecDoubleY );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing a spline with two polynoms and one border"<<endl;
	
	cout<<"cSpline< double, double > spline3p2B2P3d5pm0d5p1d5;  y = 3 + 2 * x; from 2; y = 3.5 - 0.5 * x + 1.5 * x^2 "<<endl;
	cSpline< double, double > spline3p2B2P3d5pm0d5p1d5;
	
	cPolynom< double, double > poly3p2;
	poly3p2.vecFactors.push_back( 3 );
	poly3p2.vecFactors.push_back( 2 );
	
	spline3p2B2P3d5pm0d5p1d5.vecPolynoms.push_back( poly3p2 );
	spline3p2B2P3d5pm0d5p1d5.vecBorders.push_back( 2.0 );
	spline3p2B2P3d5pm0d5p1d5.vecPolynoms.push_back( polym3d5pm0d5p1d );

	cout<<"spline3p2B2P3d5pm0d5p1d5.print():"<<endl;
	spline3p2B2P3d5pm0d5p1d5.print( cout );
	
	vecDoubleX.clear();
	vecDoubleY.clear();
	vecDoubleX.push_back( -10 );vecDoubleY.push_back( -17 );
	vecDoubleX.push_back( -5 );vecDoubleY.push_back( -7 );
	vecDoubleX.push_back( -2 );vecDoubleY.push_back( -1 );
	vecDoubleX.push_back( -1 );vecDoubleY.push_back( 1 );
	vecDoubleX.push_back( 0 );vecDoubleY.push_back( 3 );
	vecDoubleX.push_back( 0.5 );vecDoubleY.push_back( 4 );
	vecDoubleX.push_back( 1 );vecDoubleY.push_back( 5 );
	vecDoubleX.push_back( 2.0 );vecDoubleY.push_back( 8.5 );//= 3.5 - 0.5 * x + 1.5 * x^2; but 3 + 2 * x = 7
	vecDoubleX.push_back( 3 );vecDoubleY.push_back( 3.5 - 0.5 * 3.0 + 1.5 * 9.0 );
	vecDoubleX.push_back( 5 );vecDoubleY.push_back( 3.5 - 0.5 * 5.0 + 1.5 * 25.0 );
	vecDoubleX.push_back( 7 );vecDoubleY.push_back( 3.5 - 0.5 * 7.0 + 1.5 * 49.0 );
	vecDoubleX.push_back( 10 );vecDoubleY.push_back( 3.5 - 0.5 * 10.0 + 1.5 * 100.0 );
	vecDoubleX.push_back( 100 );vecDoubleY.push_back( 3.5 - 0.5 * 100.0 + 1.5 * 10000.0 );
	
	iReturn += testEvalue( spline3p2B2P3d5pm0d5p1d5, vecDoubleX, vecDoubleY );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing a spline with tree polynoms and two borders"<<endl;
	
	cout<<"cSpline< double, double > spline3p2B2P3d5pm0d5p1d5B8Pm8;  y = 3 + 2 * x; from 2; y = 3.5 - 0.5 * x + 1.5 * x^2; from 8; y = -4 "<<endl;
	cSpline< double, double > spline3p2B2P3d5pm0d5p1d5B8Pm8;
	
	cPolynom< double, double > polym4;
	polym4.vecFactors.push_back( -4 );
	
	spline3p2B2P3d5pm0d5p1d5B8Pm8.vecPolynoms.push_back( poly3p2 );
	spline3p2B2P3d5pm0d5p1d5B8Pm8.vecBorders.push_back( 2.0 );
	spline3p2B2P3d5pm0d5p1d5B8Pm8.vecPolynoms.push_back( polym3d5pm0d5p1d );
	spline3p2B2P3d5pm0d5p1d5B8Pm8.vecBorders.push_back( 8.0 );
	spline3p2B2P3d5pm0d5p1d5B8Pm8.vecPolynoms.push_back( polym4 );

	cout<<"spline3p2B2P3d5pm0d5p1d5B8Pm8.print():"<<endl;
	spline3p2B2P3d5pm0d5p1d5B8Pm8.print( cout );
	
	vecDoubleX.clear();
	vecDoubleY.clear();
	vecDoubleX.push_back( -10 );vecDoubleY.push_back( -17 );
	vecDoubleX.push_back( -5 );vecDoubleY.push_back( -7 );
	vecDoubleX.push_back( -2 );vecDoubleY.push_back( -1 );
	vecDoubleX.push_back( -1 );vecDoubleY.push_back( 1 );
	vecDoubleX.push_back( 0 );vecDoubleY.push_back( 3 );
	vecDoubleX.push_back( 0.5 );vecDoubleY.push_back( 4 );
	vecDoubleX.push_back( 1 );vecDoubleY.push_back( 5 );
	vecDoubleX.push_back( 2.0 );vecDoubleY.push_back( 8.5 );//= 3.5 - 0.5 * x + 1.5 * x^2; but 3 + 2 * x = 7
	vecDoubleX.push_back( 3 );vecDoubleY.push_back( 3.5 - 0.5 * 3.0 + 1.5 * 9.0 );
	vecDoubleX.push_back( 5 );vecDoubleY.push_back( 3.5 - 0.5 * 5.0 + 1.5 * 25.0 );
	vecDoubleX.push_back( 7 );vecDoubleY.push_back( 3.5 - 0.5 * 7.0 + 1.5 * 49.0 );
	vecDoubleX.push_back( 8 );vecDoubleY.push_back( -4 );
	vecDoubleX.push_back( 9 );vecDoubleY.push_back( -4 );
	vecDoubleX.push_back( 10 );vecDoubleY.push_back( -4 );
	vecDoubleX.push_back( 100 );vecDoubleY.push_back( -4 );
	
	iReturn += testEvalue( spline3p2B2P3d5pm0d5p1d5B8Pm8, vecDoubleX, vecDoubleY );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing a spline with four polynoms and tree borders"<<endl;
	
	cout<<"cSpline< double, double > splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8;  y = -3 - 0.1 * x ; from -2.5; y = 3 + 2 * x; from 2; y = 3.5 - 0.5 * x + 1.5 * x^2; from 8; y = -4 "<<endl;
	cSpline< double, double > splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8;
	
	cPolynom< double, double > polym3pm0d1;
	polym3pm0d1.vecFactors.push_back( -3 );
	polym3pm0d1.vecFactors.push_back( -0.1 );
	
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8.vecPolynoms.push_back( polym3pm0d1 );
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8.vecBorders.push_back( -2.5 );
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8.vecPolynoms.push_back( poly3p2 );
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8.vecBorders.push_back( 2.0 );
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8.vecPolynoms.push_back( polym3d5pm0d5p1d );
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8.vecBorders.push_back( 8.0 );
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8.vecPolynoms.push_back( polym4 );

	cout<<"splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8.print():"<<endl;
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8.print( cout );
	
	vecDoubleX.clear();
	vecDoubleY.clear();
	vecDoubleX.push_back( -10 );vecDoubleY.push_back( -2.0 );
	vecDoubleX.push_back( -5 );vecDoubleY.push_back( -2.5 );
	vecDoubleX.push_back( -3 );vecDoubleY.push_back( -2.7 );
	vecDoubleX.push_back( -2.5 );vecDoubleY.push_back( -2 );
	vecDoubleX.push_back( -2 );vecDoubleY.push_back( -1 );
	vecDoubleX.push_back( -1 );vecDoubleY.push_back( 1 );
	vecDoubleX.push_back( 0 );vecDoubleY.push_back( 3 );
	vecDoubleX.push_back( 0.5 );vecDoubleY.push_back( 4 );
	vecDoubleX.push_back( 1 );vecDoubleY.push_back( 5 );
	vecDoubleX.push_back( 2.0 );vecDoubleY.push_back( 8.5 );//= 3.5 - 0.5 * x + 1.5 * x^2; but 3 + 2 * x = 7
	vecDoubleX.push_back( 3 );vecDoubleY.push_back( 3.5 - 0.5 * 3.0 + 1.5 * 9.0 );
	vecDoubleX.push_back( 5 );vecDoubleY.push_back( 3.5 - 0.5 * 5.0 + 1.5 * 25.0 );
	vecDoubleX.push_back( 7 );vecDoubleY.push_back( 3.5 - 0.5 * 7.0 + 1.5 * 49.0 );
	vecDoubleX.push_back( 8 );vecDoubleY.push_back( -4 );
	vecDoubleX.push_back( 9 );vecDoubleY.push_back( -4 );
	vecDoubleX.push_back( 10 );vecDoubleY.push_back( -4 );
	vecDoubleX.push_back( 100 );vecDoubleY.push_back( -4 );
	
	iReturn += testEvalue( splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8, vecDoubleX, vecDoubleY );

	return iReturn;
}


/**
 * This function checks if the given spline pSpline and underfunction
 * pSplineFunction represents the same spline function.
 *
 * @param pSpline the spline as an @see cSpline object
 * @param pSplineFunction the spline as an @see cUnderFunction object
 * @ param pVariableX the variable for the spline
 * @return the number of errors occured in the test
 */
int isEqualSpline( const cSpline< double, double > * pSpline,
		cUnderFunction * pSplineFunction, cFibVariable * pVariableX ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	//evalue the non if underfunctions and ther border of pSplineFunction
	stack< const cUnderFunction * > stkOpenUnderFunctions;
	stkOpenUnderFunctions.push( pSplineFunction );
	stack< double > stkOpenBorders;
	
	unsigned int uiActualPolynom = 0;
	
	while ( ! stkOpenUnderFunctions.empty() ){
		if ( pSpline->vecPolynoms.size() <= uiActualPolynom ){
			cerr<<"Error: To much subfunctions found, existing "<<
				pSpline->vecPolynoms.size()<<" found "<<(uiActualPolynom + 1)<<endl;
			iReturn++;
			break;
		}
		
		const cUnderFunction * pActualUnderfunction =
			stkOpenUnderFunctions.top();
		stkOpenUnderFunctions.pop();
		if ( pActualUnderfunction->getType() == cUnderFunction::FUNCTION_IF ){
		
			const cFunctionIf * pActualIfUnderfunction =
				(const cFunctionIf *)(pActualUnderfunction);
			stkOpenUnderFunctions.push( pActualIfUnderfunction->getSecondUnderFunction() );
			stkOpenUnderFunctions.push( pActualIfUnderfunction->getFirstUnderFunction() );
			
			stkOpenBorders.push( ((const cFunctionValue *)(((const cConditionLower *)(
				pActualIfUnderfunction->getCondition()))->getSecondSubFunction()))->getValue() );
			
		}else{//no if underfunction
			/*compare evalued underfunction and border with the actual underfunction
			and border of the @see cSpline object pSpline*/
			
			cUnderFunction * pActualUnderfunctionSpline =
				pSpline->vecPolynoms[ uiActualPolynom ].toFibUnderFunction( pVariableX );
			
			//check actual subfunction
			if ( pActualUnderfunctionSpline ){
				if ( ! ( (* pActualUnderfunction ) == (* pActualUnderfunctionSpline ) ) ){
					cerr<<"Error: The generated "<<uiActualPolynom+1<<
						"'th underfunction is not correct: "<<endl;
					pActualUnderfunction->storeXml( cerr );
					cerr<<"Correct: "<<endl;
					pActualUnderfunctionSpline->storeXml( cerr );
					iReturn++;
				}
				delete pActualUnderfunctionSpline;
			}else{
				cerr<<"Error: No "<<uiActualPolynom+1<<"'th underfunction returned."<<endl;
				iReturn++;
			}
			//check actual border
			if ( uiActualPolynom < pSpline->vecBorders.size() ){
				const double dActualBorder = stkOpenBorders.top();
				stkOpenBorders.pop();
				if ( dActualBorder != pSpline->vecBorders[ uiActualPolynom ] ){
					cerr<<"Error: The generated "<<uiActualPolynom+1<<
						"'th underfunction has not the correct border, it is "<<
						dActualBorder<<" but should be "<<pSpline->vecBorders[ uiActualPolynom ]<<endl;
				}
			}else{
				if ( ! stkOpenBorders.empty() ){
					cerr<<"Error: The generated "<<uiActualPolynom+1<<
						"'th underfunction has not the correct border, it is "<<
						stkOpenBorders.top()<<" but should be not existing."<<endl;
					stkOpenBorders.pop();
				}
			}
			
			uiActualPolynom++;
		}
		
	}//end while underfunctions to check exists
	
	
	return iReturn;
}




/**
 * This function tests the toFibUnderFunction() function of the
 * cSpline class.
 *
 * metods tested:
 * 	- template<class tY> cUnderFunction * toFibUnderFunction( cFibVariable * pVariable );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testSplineToFibUnderFunction( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the toFibUnderFunction() on an spline with no polynoms"<<endl;
	
	cout<<"cFibVariable * pVariableX = new cFibVariable( NULL );"<<endl;
	cFibVariable * pVariableX = new cFibVariable( NULL );
	pVariableX->setIntegerValue( 1 );
	
	cout<<"cSpline< long, double > spline;"<<endl;
	cSpline< long, double > spline;
	
	cout<<"pResultUnderfunction = spline.toFibUnderFunction( pVariableX )"<<endl;
	cUnderFunction * pResultUnderfunction = spline.toFibUnderFunction(
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the toFibUnderFunction() on an spline with one 0'ary polynom"<<endl;
	
	cout<<"spline.vecPolynoms.push_back( cPolynom< long, double >() );"<<endl;
	spline.vecPolynoms.push_back( cPolynom< long, double >() );
	
	cout<<"pResultUnderfunction = spline.toFibUnderFunction( pVariableX )"<<endl;
	pResultUnderfunction = spline.toFibUnderFunction( pVariableX );
	
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the toFibUnderFunction() on an spline with one 1'ary polynom"<<endl;
	
	cout<<"spline.vecPolynoms.back().vecFactors.push_back( 2.2 );"<<endl;
	spline.vecPolynoms.back().vecFactors.push_back( 2.2 );
	cout<<"pResultUnderfunction = spline.toFibUnderFunction( pVariableX )"<<endl;
	pResultUnderfunction = spline.toFibUnderFunction( pVariableX );
	
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the toFibUnderFunction() on an spline with one 2'ary polynom"<<endl;
	
	cout<<"spline.vecPolynoms.back().vecFactors.push_back( 3.3 );"<<endl;
	spline.vecPolynoms.back().vecFactors.push_back( 3.3 );
	cout<<"pResultUnderfunction = spline.toFibUnderFunction( pVariableX )"<<endl;
	pResultUnderfunction = spline.toFibUnderFunction( pVariableX );
	
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the toFibUnderFunction() on an spline with one 3'ary polynom"<<endl;
	
	cout<<"spline.vecPolynoms.back().vecFactors.push_back( -4.4 );"<<endl;
	spline.vecPolynoms.back().vecFactors.push_back( -4.4 );
	cout<<"pResultUnderfunction = spline.toFibUnderFunction( pVariableX )"<<endl;
	pResultUnderfunction = spline.toFibUnderFunction( pVariableX );
	
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the toFibUnderFunction() on an spline with one 4'ary polynom"<<endl;
	
	cout<<"spline.vecPolynoms.back().vecFactors.push_back( 15 );"<<endl;
	spline.vecPolynoms.back().vecFactors.push_back( 15 );
	cout<<"pResultUnderfunction = spline.toFibUnderFunction( pVariableX )"<<endl;
	pResultUnderfunction = spline.toFibUnderFunction( pVariableX );
	
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


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the toFibUnderFunction() on an spline with two polynoms and one border"<<endl;
	
	cout<<"cSpline< double, double > spline3p2B2P3d5pm0d5p1d5;  y = 3 + 2 * x; from 2; y = 3.5 - 0.5 * x + 1.5 * x^2 "<<endl;
	cSpline< double, double > spline3p2B2P3d5pm0d5p1d5;
	
	cPolynom< double, double > poly3p2;
	poly3p2.vecFactors.push_back( 3 );
	poly3p2.vecFactors.push_back( 2 );
	cPolynom< double, double > polym3d5pm0d5p1d;
	polym3d5pm0d5p1d.vecFactors.push_back( 3.5 );
	polym3d5pm0d5p1d.vecFactors.push_back( -0.5 );
	polym3d5pm0d5p1d.vecFactors.push_back( 1.5 );
	
	spline3p2B2P3d5pm0d5p1d5.vecPolynoms.push_back( poly3p2 );
	spline3p2B2P3d5pm0d5p1d5.vecBorders.push_back( 2.0 );
	spline3p2B2P3d5pm0d5p1d5.vecPolynoms.push_back( polym3d5pm0d5p1d );
	
	cout<<"pResultUnderfunction = spline3p2B2P3d5pm0d5p1d5.toFibUnderFunction( pVariableX )"<<endl;
	pResultUnderfunction = spline3p2B2P3d5pm0d5p1d5.toFibUnderFunction( pVariableX );
	
	
	cUnderFunction * pUnderFunction1 = poly3p2.toFibUnderFunction( pVariableX );
	cUnderFunction * pUnderFunction2 = polym3d5pm0d5p1d.toFibUnderFunction( pVariableX );
	
	cFunctionIf fun3p2B2P3d5pm0d5p1d5( new cConditionLower(
		new cFunctionVariable( pVariableX ), new cFunctionValue( 2.0 ) ),
		pUnderFunction1, pUnderFunction2 );
	
	//check the generated underfunction
	if ( pResultUnderfunction ){
		if ( fun3p2B2P3d5pm0d5p1d5 == (* pResultUnderfunction ) ){
		
			cout<<"The generated underfunction is correct. "<<endl;
		}else{
			cerr<<"Error: The generated underfunction is not correct: "<<endl;
			pResultUnderfunction->storeXml( cerr );
			cerr<<"Correct: "<<endl;
			fun3p2B2P3d5pm0d5p1d5.storeXml( cerr );
			iReturn++;
		}
		delete pResultUnderfunction;
	}else{
		cerr<<"Error: No underfunction returned."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the toFibUnderFunction() on an spline with tree polynoms and two borders"<<endl;
	
	cout<<"cSpline< double, double > spline3p2B2P3d5pm0d5p1d5B8Pm8;  y = 3 + 2 * x; from 2; y = 3.5 - 0.5 * x + 1.5 * x^2; from 8; y = -4 "<<endl;
	cSpline< double, double > spline3p2B2P3d5pm0d5p1d5B8Pm8;
	
	cPolynom< double, double > polym4;
	polym4.vecFactors.push_back( -4 );
	
	spline3p2B2P3d5pm0d5p1d5B8Pm8.vecPolynoms.push_back( poly3p2 );
	spline3p2B2P3d5pm0d5p1d5B8Pm8.vecBorders.push_back( 2.0 );
	spline3p2B2P3d5pm0d5p1d5B8Pm8.vecPolynoms.push_back( polym3d5pm0d5p1d );
	spline3p2B2P3d5pm0d5p1d5B8Pm8.vecBorders.push_back( 8.0 );
	spline3p2B2P3d5pm0d5p1d5B8Pm8.vecPolynoms.push_back( polym4 );

	cout<<"pResultUnderfunction = spline3p2B2P3d5pm0d5p1d5B8Pm8.toFibUnderFunction( pVariableX )"<<endl;
	pResultUnderfunction = spline3p2B2P3d5pm0d5p1d5B8Pm8.toFibUnderFunction( pVariableX );
	
	
	pUnderFunction1 = poly3p2.toFibUnderFunction( pVariableX );
	pUnderFunction2 = polym3d5pm0d5p1d.toFibUnderFunction( pVariableX );
	cUnderFunction * pUnderFunction3 = polym4.toFibUnderFunction( pVariableX );
	
	cFunctionIf fun3p2B2P3d5pm0d5p1d5B8Pm8( new cConditionLower(
			new cFunctionVariable( pVariableX ), new cFunctionValue( 2.0 ) ),
		pUnderFunction1,
		new cFunctionIf( new cConditionLower(
				new cFunctionVariable( pVariableX ), new cFunctionValue( 8.0 ) ),
			pUnderFunction2, pUnderFunction3 ) );
	
	//check the generated underfunction
	if ( pResultUnderfunction ){
		if ( fun3p2B2P3d5pm0d5p1d5B8Pm8 == (* pResultUnderfunction ) ){
		
			cout<<"The generated underfunction is correct. "<<endl;
		}else{
			cerr<<"Error: The generated underfunction is not correct: "<<endl;
			pResultUnderfunction->storeXml( cerr );
			cerr<<"Correct: "<<endl;
			fun3p2B2P3d5pm0d5p1d5B8Pm8.storeXml( cerr );
			iReturn++;
		}
		delete pResultUnderfunction;
	}else{
		cerr<<"Error: No underfunction returned."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the toFibUnderFunction() on an spline with four polynoms and tree borders"<<endl;
	
	cout<<"cSpline< double, double > splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8;  y = -3 - 0.1 * x ; from -2.5; y = 3 + 2 * x; from 2; y = 3.5 - 0.5 * x + 1.5 * x^2; from 8; y = -4 "<<endl;
	cSpline< double, double > splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8;
	
	cPolynom< double, double > polym3pm0d1;
	polym3pm0d1.vecFactors.push_back( -3 );
	polym3pm0d1.vecFactors.push_back( -0.1 );
	
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8.vecPolynoms.push_back( polym3pm0d1 );
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8.vecBorders.push_back( -2.5 );
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8.vecPolynoms.push_back( poly3p2 );
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8.vecBorders.push_back( 2.0 );
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8.vecPolynoms.push_back( polym3d5pm0d5p1d );
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8.vecBorders.push_back( 8.0 );
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8.vecPolynoms.push_back( polym4 );
	
	cout<<"pResultUnderfunction = splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8.toFibUnderFunction( pVariableX )"<<endl;
	pResultUnderfunction = splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8.toFibUnderFunction( pVariableX );
	
	
	pUnderFunction1 = polym3pm0d1.toFibUnderFunction( pVariableX );
	pUnderFunction2 = poly3p2.toFibUnderFunction( pVariableX );
	pUnderFunction3 = polym3d5pm0d5p1d.toFibUnderFunction( pVariableX );
	cUnderFunction * pUnderFunction4 = polym4.toFibUnderFunction( pVariableX );
	
	cFunctionIf fun3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8( new cConditionLower(
			new cFunctionVariable( pVariableX ), new cFunctionValue( 2.0 ) ),
		new cFunctionIf( new cConditionLower(
				new cFunctionVariable( pVariableX ), new cFunctionValue( -2.5 ) ),
			pUnderFunction1, pUnderFunction2 ),
		new cFunctionIf( new cConditionLower(
				new cFunctionVariable( pVariableX ), new cFunctionValue( 8.0 ) ),
			pUnderFunction3, pUnderFunction4 ));
	
	//check the generated underfunction
	if ( pResultUnderfunction ){
		if ( fun3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8 == (* pResultUnderfunction ) ){
		
			cout<<"The generated underfunction is correct. "<<endl;
		}else{
			cerr<<"Error: The generated underfunction is not correct: "<<endl;
			pResultUnderfunction->storeXml( cerr );
			cerr<<"Correct: "<<endl;
			fun3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm8.storeXml( cerr );
			iReturn++;
		}
		delete pResultUnderfunction;
	}else{
		cerr<<"Error: No underfunction returned."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the toFibUnderFunction() on an spline with 5 polynoms"<<endl;
	
	cout<<"cSpline< double, double > splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm4B15P4;  y = -3 - 0.1 * x ; from -2.5; y = 3 + 2 * x; from 2; y = 3.5 - 0.5 * x + 1.5 * x^2; from 8; y = -4, form 15: y=4 "<<endl;
	cSpline< double, double > splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm4B15P4;
	
	cPolynom< double, double > poly4;
	poly4.vecFactors.push_back( 4 );
	
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm4B15P4.vecPolynoms.push_back( polym3pm0d1 );
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm4B15P4.vecBorders.push_back( -2.5 );
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm4B15P4.vecPolynoms.push_back( poly3p2 );
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm4B15P4.vecBorders.push_back( 2.0 );
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm4B15P4.vecPolynoms.push_back( polym3d5pm0d5p1d );
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm4B15P4.vecBorders.push_back( 8.0 );
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm4B15P4.vecPolynoms.push_back( polym4 );
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm4B15P4.vecBorders.push_back( 15.0 );
	splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm4B15P4.vecPolynoms.push_back( poly4 );
	
	cout<<"pResultUnderfunction = splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm4B15P4.toFibUnderFunction( pVariableX )"<<endl;
	pResultUnderfunction = splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm4B15P4.toFibUnderFunction( pVariableX );
	
	if ( pResultUnderfunction ){
		const int iReturnTmp = isEqualSpline( &splinem3pm0d1Bm2d5P3p2B2P3d5pm0d5p1d5B8Pm4B15P4, pResultUnderfunction, pVariableX );
	
		if ( 0 < iReturnTmp ){
			iReturn += iReturnTmp;
			
			cerr<<"Error: The generated underfunction is not correct: "<<endl;
			pResultUnderfunction->storeXml( cerr );
			cout<<endl;
		}
		delete pResultUnderfunction;
	}else{
		cerr<<"Error: No underfunction returned."<<endl;
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the toFibUnderFunction() on an spline with 10 polynoms"<<endl;
	
	cout<<"cSpline< double, double > splinemPoly10; ...; y = -3 - 0.1 * x ; from -2.5; y = 3 + 2 * x; from 2; y = 3.5 - 0.5 * x + 1.5 * x^2; from 8; y = -4, form 15: y=4; ... "<<endl;
	cSpline< double, double > splinePoly10;
	
	cPolynom< double, double > poly7;
	poly7.vecFactors.push_back( 7 );
	
	cPolynom< double, double > poly3p6;
	poly3p6.vecFactors.push_back( 3 );
	poly3p6.vecFactors.push_back( 6 );
	
	cPolynom< double, double > polyNULL;
	
	cPolynom< double, double > poly4d2pm3;
	poly4d2pm3.vecFactors.push_back( 4.2 );
	poly4d2pm3.vecFactors.push_back( -3.0 );
	
	cPolynom< double, double > poly541pm6pm2;
	poly541pm6pm2.vecFactors.push_back( 541 );
	poly541pm6pm2.vecFactors.push_back( -6 );
	poly541pm6pm2.vecFactors.push_back( -2 );

	splinePoly10.vecPolynoms.push_back( poly3p6 );
	splinePoly10.vecBorders.push_back( -6.47 );
	splinePoly10.vecPolynoms.push_back( poly7 );
	splinePoly10.vecBorders.push_back( -4 );
	splinePoly10.vecPolynoms.push_back( polym3pm0d1 );
	splinePoly10.vecBorders.push_back( -2.5 );
	splinePoly10.vecPolynoms.push_back( poly3p2 );
	splinePoly10.vecBorders.push_back( 2.0 );
	splinePoly10.vecPolynoms.push_back( polym3d5pm0d5p1d );
	splinePoly10.vecBorders.push_back( 8.0 );
	splinePoly10.vecPolynoms.push_back( polym4 );
	splinePoly10.vecBorders.push_back( 15.0 );
	splinePoly10.vecPolynoms.push_back( poly4 );
	splinePoly10.vecBorders.push_back( 15.1 );
	splinePoly10.vecPolynoms.push_back( polyNULL );
	splinePoly10.vecBorders.push_back( 100.1 );
	splinePoly10.vecPolynoms.push_back( poly4d2pm3 );
	splinePoly10.vecBorders.push_back( 5874.21 );
	splinePoly10.vecPolynoms.push_back( poly541pm6pm2 );
	
	cout<<"pResultUnderfunction = splinePoly10.toFibUnderFunction( pVariableX )"<<endl;
	pResultUnderfunction = splinePoly10.toFibUnderFunction( pVariableX );
	
	if ( pResultUnderfunction ){
		const int iReturnTmp = isEqualSpline( &splinePoly10, pResultUnderfunction, pVariableX );
		
		if ( 0 < iReturnTmp ){
			iReturn += iReturnTmp;
			
			cerr<<"Error: The generated underfunction is not correct: "<<endl;
			pResultUnderfunction->storeXml( cerr );
			cout<<endl;
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
 * This function tests the evalue( vector ) function of the cSpline class.
 *
 * metods tested:
 * 	- void evalue( const vector< cDataPoint< tX, tY> > & vecData );
 * 	- bool operator==( const cSpline<tX, tY> & spline ) const;
 * 	- bool operator!=( const cSpline<tX, tY> & spline ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param iWarnings a reference to the integer variable for the warnings
 * @return the number of errors occured in the test
 */
int testSplineEvalue( unsigned long &ulTestphase, int & iWarnings ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalue() method for creating a spline for no data point"<<endl;
	
	cout<<"cSpline< int, float> splineIntFloat;"<<endl;
	cSpline< int, float> splineIntFloat;
	
	cPolynom< int, float> polyIntFloat;
	polyIntFloat.vecFactors.push_back( 17 );
	splineIntFloat.vecPolynoms.push_back( polyIntFloat );
	
	cout<<"vector< cDataPoint< int, float> > vecIntFloatDataPoints: {}"<<endl;
	vector< cDataPoint< int, float> > vecIntFloatDataPoints;
	
	cout<<"splineIntFloat.evalue( vecIntFloatDataPoints );"<<endl;
	bool bSplineFound = splineIntFloat.evalue( vecIntFloatDataPoints );
	
	cSpline< int, float> splineIntFloatCorrect;
	splineIntFloatCorrect.vecPolynoms.push_back( cPolynom< int, float>() );
	splineIntFloatCorrect.vecPolynoms.front().vecFactors.push_back( 17 );
	
	if ( ! bSplineFound ){
		if ( splineIntFloatCorrect == splineIntFloat ){
			cout<<"The spline is correct."<<endl;
		}else{
			cerr<<"Error: The spline is wrong."<<endl;
			cerr<<"It is:"<<endl;
			splineIntFloat.print( cerr );
			cerr<<"But should be:"<<endl;
			splineIntFloatCorrect.print( cerr );
			iReturn++;
		}
	}else{
		cerr<<"Error: A spline could be evalued for no data points."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalue() method for creating a spline for the data point: {(1, 1)}"<<endl;
	
	cout<<"vecIntFloatDataPoints: {(1, 1)}"<<endl;
	vecIntFloatDataPoints.push_back( cDataPoint< int, float>( 1 ,1 ) );
	
	cout<<"splineIntFloat.evalue( vecIntFloatDataPoints );"<<endl;
	bSplineFound = splineIntFloat.evalue( vecIntFloatDataPoints );
	
	splineIntFloatCorrect.vecPolynoms.front().vecFactors.clear();
	splineIntFloatCorrect.vecPolynoms.front().vecFactors.push_back( 1 );
	
	if ( bSplineFound ){
		if ( splineIntFloatCorrect == splineIntFloat ){
			cout<<"The created spline is correct."<<endl;
		}else{
			cerr<<"Error: The created spline is wrong."<<endl;
			cerr<<"It is:"<<endl;
			splineIntFloat.print( cerr );
			cerr<<"But should be:"<<endl;
			splineIntFloatCorrect.print( cerr );
			iReturn++;
		}
	}else{
		cerr<<"Error: No spline could be evalued."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalue() method for creating a spline for the data point: {(2.5, 3.2)}"<<endl;
	
	cout<<"cSpline< double, double > spline;"<<endl;
	cSpline< double, double > spline;
	
	cout<<"vector< cDataPoint< double, double > > vecDataPoints: {(2.5, 3.2)}"<<endl;
	vector< cDataPoint< double, double > > vecDataPoints;
	vecDataPoints.push_back( cDataPoint< double, double >(2.5, 3.2) );
	
	cout<<"spline.evalue( vecDataPoints );"<<endl;
	bSplineFound = spline.evalue( vecDataPoints );
	
	cSpline< double, double > splineCorrect;
	splineCorrect.vecPolynoms.push_back( cPolynom< double, double >() );
	splineCorrect.vecPolynoms.front().vecFactors.push_back( 3.2 );
	
	if ( bSplineFound ){
		if ( splineCorrect == spline ){
			cout<<"The created spline is correct."<<endl;
		}else{
			cerr<<"Error: The created spline is wrong."<<endl;
			cerr<<"It is:"<<endl;
			spline.print( cerr );
			cerr<<"But should be:"<<endl;
			splineCorrect.print( cerr );
			iReturn++;
		}
	}else{
		cerr<<"Error: No spline could be evalued."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalue() method for creating a spline for the data points: {(3, 3.5)) (5.5, -1.5}"<<endl;
	
	cout<<"vecDataPoints: {(3, 3.5) (5.5, -1.5)}"<<endl;
	vecDataPoints.clear();
	vecDataPoints.push_back( cDataPoint< double, double >(3, 3.5) );
	vecDataPoints.push_back( cDataPoint< double, double >(5.5, -1.5) );
	
	cout<<"spline.evalue( vecDataPoints );"<<endl;
	bSplineFound = spline.evalue( vecDataPoints );
	
	splineCorrect.vecPolynoms.front().vecFactors.clear();
	splineCorrect.vecPolynoms.front().vecFactors.push_back( 9.5 );
	splineCorrect.vecPolynoms.front().vecFactors.push_back( -2.0 );
	
	if ( bSplineFound ){
		if ( splineCorrect == spline ){
			cout<<"The created spline is correct."<<endl;
		}else{
			cerr<<"Error: The created spline is wrong."<<endl;
			cerr<<"It is:"<<endl;
			spline.print( cerr );
			cerr<<"But should be:"<<endl;
			splineCorrect.print( cerr );
			iReturn++;
		}
	}else{
		cerr<<"Error: No spline could be evalued."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalue() method for creating a spline for the data points: {( -0.8, 0.76 ) ( 4, -5 ) ( -3.5, -16.25)}"<<endl;
	
	cout<<"vecDataPoints: {( -0.8, 0.76 ) ( 4, -5 ) ( -3.5, -16.25)}"<<endl;
	vecDataPoints.clear();
	vecDataPoints.push_back( cDataPoint< double, double >( -0.8, 0.76 ) );
	vecDataPoints.push_back( cDataPoint< double, double >( 4, -5 ) );
	vecDataPoints.push_back( cDataPoint< double, double >( -3.5, -16.25 ) );
	
	cout<<"spline.evalue( vecDataPoints );"<<endl;
	bSplineFound = spline.evalue( vecDataPoints );
	
	splineCorrect.vecPolynoms.front().vecFactors.clear();
	splineCorrect.vecPolynoms.front().vecFactors.push_back( 3.0 );
	splineCorrect.vecPolynoms.front().vecFactors.push_back( 2.0 );
	splineCorrect.vecPolynoms.front().vecFactors.push_back( -1.0 );
	
	if ( bSplineFound ){
		if ( splineCorrect == spline ){
			cout<<"The created spline is correcly: "<<endl;
			spline.print( cout );
		}else{
			cerr<<"Error: The created spline is wrong."<<endl;
			cerr<<"It is:"<<endl;
			spline.print( cerr );
			cerr<<"But should be:"<<endl;
			splineCorrect.print( cerr );
			iReturn++;
		}
	}else{
		cerr<<"Error: No spline could be evalued."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalue() method for creating a spline for the data points with duplicates: {( 2, -2 ) (3, -0.5) ( 4, 2 ) (3, -0.5) ( 4, 2 ) ( 4, 2 )}"<<endl;
	
	cout<<"vecDataPoints: {( 2, -2 ) (3, -0.5) ( 4, 2 ) (3, -0.5) ( 4, 2 ) ( 4, 2 )}"<<endl;
	vecDataPoints.clear();
	vecDataPoints.push_back( cDataPoint< double, double >( 2, -2 ) );
	vecDataPoints.push_back( cDataPoint< double, double >(3, -0.5) );
	vecDataPoints.push_back( cDataPoint< double, double >( 4, 2 ) );
	vecDataPoints.push_back( cDataPoint< double, double >(3, -0.5) );
	vecDataPoints.push_back( cDataPoint< double, double >( 4, 2 ) );
	vecDataPoints.push_back( cDataPoint< double, double >( 4, 2 ) );
	
	cout<<"spline.evalue( vecDataPoints );"<<endl;
	bSplineFound = spline.evalue( vecDataPoints );
	
	splineCorrect.vecPolynoms.front().vecFactors.clear();
	splineCorrect.vecPolynoms.front().vecFactors.push_back( -2.0 );
	splineCorrect.vecPolynoms.front().vecFactors.push_back( -1.0 );
	splineCorrect.vecPolynoms.front().vecFactors.push_back( 0.5 );
	
	if ( bSplineFound ){
		if ( splineCorrect == spline ){
			cout<<"The created spline is correcly: "<<endl;
			spline.print( cout );
		}else{
			cerr<<"Error: The created spline is wrong."<<endl;
			cerr<<"It is:"<<endl;
			spline.print( cerr );
			cerr<<"But should be:"<<endl;
			splineCorrect.print( cerr );
			iReturn++;
		}
	}else{
		cerr<<"Error: No spline could be evalued."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalue() method for creating a spline for the data points: {(3, 7) (3, 2)} wich cant be part of one spline"<<endl;
	
	cout<<"vecDataPoints: {(3, 7) (3, 2)}"<<endl;
	vecDataPoints.clear();
	vecDataPoints.push_back( cDataPoint< double, double >(3, 7) );
	vecDataPoints.push_back( cDataPoint< double, double >(3, 2) );
	
	cout<<"spline.evalue( vecDataPoints );"<<endl;
	bSplineFound = spline.evalue( vecDataPoints );
	
	if ( ! bSplineFound ){
		if ( splineCorrect == spline ){
			cout<<"The spline couldn't be evalued for the datapoints. The spline is unchanged, it is correcly: "<<endl;
			spline.print( cout );
		}else{
			cerr<<"Error: The spline could be evalued for the datapoints, but shouldnt be."<<endl;
			cerr<<"It is:"<<endl;
			spline.print( cerr );
			cerr<<"But should be:"<<endl;
			splineCorrect.print( cerr );
			iReturn++;
		}
	}else{
		cerr<<"Error: No spline could be evalued."<<endl;
		iReturn++;
	}

	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalue() method for creating random splines"<<endl;
	
	cout<<"cSpline< double, double > splineRand;"<<endl;
	cSpline< double, double > splineRand;
	
	for ( unsigned int uiIteration = 0; uiIteration < (MAX_ITERATION / 16 + 1); uiIteration++ ){
		
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating "<<uiIteration<<"'th random splines"<<endl;
		
		const unsigned int uiDataPointsToGenerate = rand() % 5;
		cout<<"vector< cDataPoint< double, double > > vecDataPoints (size="<<
			uiDataPointsToGenerate<<"): {";
		vector< cDataPoint< double, double > > vecDataPoints;
		set< double > setXValues;
		
		bool bSplineCanBeEvalued = (uiDataPointsToGenerate != 0);
		for ( unsigned int uiGeneratedDataPoints = 0;
				uiGeneratedDataPoints < uiDataPointsToGenerate;
				uiGeneratedDataPoints++ ){
			
			double x = randomValue( 1000.0 );
			double y = randomValue( 1000.0 );
			
			if ( setXValues.find( x ) != setXValues.end() ){
				//the x value was generated befor -> no spline can be created
				bSplineCanBeEvalued = false;
			}else{//new x value
				setXValues.insert( x );
			}
			cout<<"("<<x<<","<<y<<") ";
			vecDataPoints.push_back( cDataPoint< double, double >( x, y ) );
		}
		cout<<"} "<<endl;
		
		const cSpline< double, double > splineRandOld( splineRand );
		
		cout<<"splineRand.evalue( vecDataPoints );"<<endl;
		bool bSplineFound = splineRand.evalue( vecDataPoints );
		
		if ( bSplineCanBeEvalued ){
			if ( bSplineFound ){
				/*bSplineCanBeEvalued == bSplineFound == true
				-> check if the spline match the data points*/
				bool bDataPointWrong = false;
				for ( unsigned int uiActualDataPoints = 0;
						uiActualDataPoints < uiDataPointsToGenerate;
						uiActualDataPoints++ ){
					
					if ( ! compareDoubleTest( vecDataPoints[ uiActualDataPoints ].y,
							splineRand.evalue( vecDataPoints[ uiActualDataPoints ].x ) ) ){
						
						bDataPointWrong = true;
						cerr<<"Warning: The "<<uiActualDataPoints<<"'th data point ("<<
							vecDataPoints[ uiActualDataPoints ].x<<", "<<
							vecDataPoints[ uiActualDataPoints ].y<<
							") is not matched by the spline ("<<
							vecDataPoints[ uiActualDataPoints ].x<<", "<<
							splineRand.evalue( vecDataPoints[ uiActualDataPoints ].x )<<
							"), diff in y is "<<( vecDataPoints[ uiActualDataPoints ].y -
								splineRand.evalue( vecDataPoints[ uiActualDataPoints ].x ) )<<" ."<<endl;
					}
				}
				if ( bDataPointWrong ){
					cerr<<"Warning: The spline dosn't match all the data points."<<endl;
					cerr<<"It is:"<<endl;
					splineRand.print( cerr );
					iWarnings++;
				}
			}else{
				cerr<<"Error: The spline couldn't be evalued for the datapoints, but should be."<<endl;
				cerr<<"It is:"<<endl;
				splineRand.print( cerr );
				iReturn++;
			}
		}else{//not bSplineCanBeEvalued
			if ( bSplineFound || ( splineRandOld != splineRand ) ){
				cerr<<"Error: The spline could be evalued for the datapoints, but shouldn't be."<<endl;
				cerr<<"It is:"<<endl;
				splineRand.print( cerr );
				cerr<<"But should be:"<<endl;
				splineRandOld.print( cerr );
				iReturn++;
			}
		}
		
		if ( ( splineRand.vecPolynoms == splineRandOld.vecPolynoms ) &&
				compareVectorDouble( splineRand.vecBorders,
					splineRandOld.vecBorders ) ){
			//vector factors not changed
			if ( ! ( splineRandOld == splineRand ) ){
				cerr<<"Error: The spline is not changed, but is not equal ( not == ) to the old spline."<<endl;
				iReturn++;
			}
			if ( splineRandOld != splineRand ){
				cerr<<"Error: The spline is not changed, but is not equal ( != ) to the old spline."<<endl;
				iReturn++;
			}
		}else{//vector factors changed
			if ( splineRandOld == splineRand ){
				cerr<<"Error: The spline is changed, but is equal ( == ) to the old spline."<<endl;
				iReturn++;
			}
			if ( ! ( splineRandOld != splineRand ) ){
				cerr<<"Error: The spline is changed, but is not not  equal ( not != ) to the old spline."<<endl;
				iReturn++;
			}
		}
	}

	return iReturn;
}



/**
 * This function tests the evalueSpline() function of the cSpline class.
 *
 * metods tested:
 * 	- unsigned long evalueSpline( const vector< cDataPointRange< tX, tY> > & vecData, unsigned int uiMaxNumberOfParameters, const unsigned int uiMinBitsToStoreMantissa, const tY maxValue, const tY maxError, const unsigned long ulMaxMemoryCost);
 * 	- bool operator==( const cSpline<tX, tY> & spline ) const;
 * 	- bool operator!=( const cSpline<tX, tY> & spline ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param iWarnings a reference to the integer variable for the warnings
 * @return the number of errors occured in the test
 */
int testEvalueSpline( unsigned long &ulTestphase, int & iWarnings ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalueSpline( vector< cDataPointRange< tX, tY> > ) method for creating random splines of type domain(x) = int and domain(y) = double"<<endl;
	
	cout<<"cSpline< int, double > splineRandIntDouble;"<<endl;
	cSpline< int, double > splineRandIntDouble;
	
	unsigned long ulSplinesGenerated = 0;
	unsigned int uiMaxParameter = 3;
	unsigned long ulNextParameterIncrease = 8;
	
	for ( unsigned int uiIteration = 0; uiIteration < (MAX_ITERATION / 16 + 1); uiIteration++ ){
		
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating "<<uiIteration<<"'th random spline (int, double)"<<endl;
		
		ulSplinesGenerated++;
		if ( ulNextParameterIncrease < ulSplinesGenerated ){
			//increase max dimension with 1
			uiMaxParameter++;
			ulNextParameterIncrease *= ulNextParameterIncrease;
		}
		
		
		cSpline< int, double > generatorSplineIntDouble;
		
		unsigned int uiNumberOfSubPolynoms = 0;
		if ( rand() % 32 ){
			uiNumberOfSubPolynoms = rand() % uiMaxParameter + 1;
		}//else uiNumberOfParameters = 0;
		unsigned int uiNumberOfGeneratorSplineSubPolynoms = uiNumberOfSubPolynoms;
		unsigned int uiNumberOfAllParameters = 0;
		//generate sub-polynoms
		for ( unsigned int uiActualPolynom = 0;
				uiActualPolynom < uiNumberOfGeneratorSplineSubPolynoms; uiActualPolynom++){
			
			cPolynom< int, double > generatorPolynomIntDouble;
			
			unsigned int uiNumberOfGeneratorSplineFactors = 0;
			if ( rand() % 32 ){
				uiNumberOfGeneratorSplineFactors = rand() % uiMaxParameter + 1;
			}//else uiNumberOfParameters = 0;
			uiNumberOfAllParameters += uiNumberOfGeneratorSplineFactors;
		
			if ( ( (rand() % 8) == 0) ){
				//use generator spline with diffent number of factors
				uiNumberOfGeneratorSplineFactors = rand() % uiMaxParameter + 1;
			}
			if ( uiNumberOfGeneratorSplineFactors == 0 ){
				uiNumberOfGeneratorSplineFactors = 1;
			}
			double dMaxFactorValue = 10000.0;
			for ( unsigned int uiActualFactor = 0;
					uiActualFactor < uiNumberOfGeneratorSplineFactors; uiActualFactor++){
				
				generatorPolynomIntDouble.vecFactors.push_back(
					randomValue( dMaxFactorValue ) );
				if ( 8.0 < dMaxFactorValue ){
					dMaxFactorValue /= 8.0;
				}
			}
			generatorSplineIntDouble.vecPolynoms.push_back( generatorPolynomIntDouble );
		}
		//generate borders
		for ( unsigned int uiActualPolynom = 1;
				uiActualPolynom < uiNumberOfGeneratorSplineSubPolynoms; uiActualPolynom++){
			
			generatorSplineIntDouble.vecBorders.push_back(
				randomValue( 10000.0 ) );
		}
		sort( generatorSplineIntDouble.vecBorders.begin(),
			generatorSplineIntDouble.vecBorders.end() );
		
		cout<<"Spline from which the datapoints are generated:"<<endl;
		generatorSplineIntDouble.print( cout );
		
		unsigned int uiDataPointsToGenerate = 0;
		if ( rand() % 32 ){
			uiDataPointsToGenerate = rand() % ( (rand() % 64) + 1 ) + 1;
		}//else  uiDataPointsToGenerate = 0;
		bool bXIsRandom = ((rand() % 8) == 0);
		cout<<"vector< cDataPointRange< double, double > > vecDataPoints (size="<<
			uiDataPointsToGenerate<<")"<<(bXIsRandom?" random ":"")<<": {"<<flush;
		vector< cDataPointRange< int, double > > vecDataPoints;
		
		int iLastX = ((int)(uiDataPointsToGenerate)) / -2;
		const int uiMaxXValueForRandGenerator = 8 * uiDataPointsToGenerate;
		
		double dMaxYValue = 0.0;
		double dMinYValue = 0.0;
		
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
			
			const double y = generatorSplineIntDouble.evalue( x );
			const double minY = y - absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			double maxY = y + absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			if ( ( rand() % 32 ) == 0 ){
				maxY = minY + absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			}
			if ( maxY <= minY ){
				maxY = minY + 0.0001;
			}
			
			cout<<"("<<flush<<x<<", "<<minY<<" till "<<maxY<<") "<<flush;
			vecDataPoints.push_back( cDataPointRange< int, double >( x, minY, maxY ) );
			
			dMinYValue = ( minY < dMinYValue ) ? minY : dMinYValue;
			dMaxYValue = ( dMaxYValue < maxY ) ? maxY : dMaxYValue;
		}
		cout<<"} "<<endl<<flush;
		
		const double dMaxAbsYValue = ( dMaxYValue < ( 0.0 - dMinYValue ) ) ?
			( 0.0 - dMinYValue ) : dMaxYValue;

		const cSpline< int, double > splineRandIntDoubleOld( splineRandIntDouble );
		
		unsigned int uiNumberOfParameters = 0;
		if ( rand() % 32 ){
			uiNumberOfParameters = rand() % uiMaxParameter + 1;
		}//else uiNumberOfParameters = 0;
		
#ifndef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		const unsigned int uiMinBitsToStoreMantissa = rand() % 32;
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		double maxValue = abs( randomValue( 1000000.0 ) ) + 1000.0;
		if ( (rand() % 8) == 0 ){
			maxValue = randomValue( 1000000.0 );
		}
		if ( uiNumberOfParameters == 1 ){
			/*with const polynoms max value must be greater as all y values to
			find a valid spline*/
			maxValue = ( maxValue < dMaxAbsYValue ) ?
				( dMaxAbsYValue + maxValue ) : maxValue ;
		}
		

#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		cout<<endl<<"splineRandIntDouble.evalueSpline( vecDataPoints, uiNumberOfParameters="<<
			uiNumberOfParameters<<", maxValue="<<maxValue<<");"<<endl<<endl;
		unsigned long uiPointsIncluded = splineRandIntDouble.evalueSpline(
			vecDataPoints, uiNumberOfParameters, maxValue );
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		cout<<endl<<"splineRandIntDouble.evalueSpline( vecDataPoints, uiNumberOfParameters="<<
			uiNumberOfParameters<<", uiMinBitsToStoreMantissa="<<
			uiMinBitsToStoreMantissa<<" , maxValue="<<maxValue<<");"<<endl<<endl;
		unsigned long uiPointsIncluded = splineRandIntDouble.evalueSpline(
			vecDataPoints, uiNumberOfParameters, uiMinBitsToStoreMantissa, maxValue );
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		
		if ( 0 < uiPointsIncluded ){
			cout<<"Founded spline is for the "<<uiPointsIncluded<<" first "<<
				( (uiPointsIncluded == uiDataPointsToGenerate)?"(=all) ":"" )<<
				"range data points:"<<endl;
			splineRandIntDouble.print( cout );
		}else{
			cout<<"No new spline generated."<<endl;
		}
		
		if ( uiDataPointsToGenerate < uiPointsIncluded ){
			cerr<<"Error: Ther wher "<<uiPointsIncluded<<" but only "<<
				uiDataPointsToGenerate<<" points to include ."<<endl;
			iReturn++;
		}
		
		vector< cDataPointRange< int, double > > vecDataPointsCorrect =
			vecDataPoints;
		sort( vecDataPointsCorrect.begin(), vecDataPointsCorrect.end() );
		if ( 0 < uiPointsIncluded ){
			
			for ( unsigned int uiActualPolynom = 0;
					uiActualPolynom < splineRandIntDouble.vecPolynoms.size(); uiActualPolynom++ ){
					
				if ( ( 0 < uiNumberOfParameters ) &&
						(uiNumberOfParameters < splineRandIntDouble.vecPolynoms[ uiActualPolynom ].vecFactors.size()) ){
					cerr<<"Error: The "<<uiActualPolynom<<"'th polynom has "<<
						splineRandIntDouble.vecPolynoms[ uiActualPolynom ].vecFactors.size()<<
						" parameters, but should have maximal "<<uiNumberOfParameters<<" ."<<endl;
					iReturn++;
				}
				for ( unsigned int uiActualFactor = 0;
						uiActualFactor < splineRandIntDouble.vecPolynoms[ uiActualPolynom ].vecFactors.size();
						uiActualFactor++ ){
					
					if ( maxValue < abs( splineRandIntDouble.vecPolynoms[ uiActualPolynom ].vecFactors[ uiActualFactor ] * 0.999 ) ){
						cerr<<"Error: The "<<uiActualPolynom<<"'th polynom has as the "<<uiActualFactor<<
							"'th factor ("<<splineRandIntDouble.vecPolynoms[ uiActualPolynom ].vecFactors[ uiActualFactor ]<<
							") greater than the maxValue of "<<maxValue<<" ."<<endl;
						iReturn++;
					}
				}
			}
			
			
			/* check if the spline match the range data points*/
			if ( uiPointsIncluded < uiDataPointsToGenerate ){
				cerr<<"Warning: Not all points included into the spline. Points included "<<
					uiPointsIncluded<<", but points to include: "<<uiDataPointsToGenerate<<endl;
				iWarnings++;
				
				vecDataPointsCorrect.resize( uiPointsIncluded );
			}
			
			pair< unsigned long, double > paError = splineRandIntDouble.evalueError(
				vecDataPointsCorrect );
			
			if ( paError.first != 0 ){
				cerr<<"Warning: The spline dosn't match the "<<uiPointsIncluded<<
					" first range data points.";
				cerr<<" Ther are "<<paError.first<<" wrong points with a error sum of "<<
					paError.second<<" ."<<endl;
				iWarnings++;
				
				for ( unsigned int uiActualDataPoint = 0;
						uiActualDataPoint < vecDataPoints.size();
						uiActualDataPoint++ ){
					
					vector< cDataPointRange< int, double > > vecActualDataPoint;
					vecActualDataPoint.push_back( vecDataPoints[ uiActualDataPoint ] );
					
					paError = splineRandIntDouble.evalueError( vecActualDataPoint );
					if ( paError.first != 0 ){
						cerr<<"Warning: The spline dosn't match the "<<uiActualDataPoint<<
							"'th range data point ("<<vecDataPoints[ uiActualDataPoint ].x<<
							", "<<vecDataPoints[ uiActualDataPoint ].minY<<" till "<<
							vecDataPoints[ uiActualDataPoint ].maxY<<
							") . The error of it is "<< paError.second<<" ."<<endl;
					}
				}//end for all data points
			}
			
			if ( uiPointsIncluded < uiDataPointsToGenerate ){
				vector< cDataPointRange< int, double > > vecFirstDataPointWrong =
					vecDataPoints;
				vecFirstDataPointWrong.push_back( vecDataPoints[ uiPointsIncluded ] );
				
				paError = splineRandIntDouble.evalueError( vecFirstDataPointWrong );
				
				if ( paError.first == 0 ){
					cerr<<"Error: The spline dos match the "<<uiPointsIncluded<<
						"'th range data point, but shouldn't."<<endl;
					iReturn++;
				}
			}
		}else{// uiPointsIncluded == 0
			if ( (0 < uiDataPointsToGenerate) && ( 0.0 < maxValue ) && ( 0 < uiNumberOfParameters ) ){
				if ( (vecDataPointsCorrect[ 0 ].minY < maxValue) &&
						( (-1.0 * vecDataPointsCorrect[ 0 ].maxY) < maxValue) ){
					cerr<<"Error: Ther wher range data points generated, but non included."<<endl;
					iReturn++;
				}
			}
			if ( splineRandIntDoubleOld != splineRandIntDouble ){
				cerr<<"Error: The spline was changed for the datapoints, but shouldn't be (because non evalued)."<<endl;
				cerr<<"It should be unchanged:"<<endl;
				splineRandIntDoubleOld.print( cerr );
				iReturn++;
			}
		}

		if ( ( splineRandIntDouble.vecPolynoms == splineRandIntDoubleOld.vecPolynoms ) &&
				compareVectorDouble( splineRandIntDouble.vecBorders,
					splineRandIntDoubleOld.vecBorders ) ){
			//vector factors not changed
			if ( ! ( splineRandIntDoubleOld == splineRandIntDouble ) ){
				cerr<<"Error: The spline is not changed, but is not equal ( not == ) to the old spline."<<endl;
				iReturn++;
			}
			if ( splineRandIntDoubleOld != splineRandIntDouble ){
				cerr<<"Error: The spline is not changed, but is not equal ( != ) to the old spline."<<endl;
				iReturn++;
			}
		}else{//vector factors changed
			if ( splineRandIntDoubleOld == splineRandIntDouble ){
				cerr<<"Error: The spline is changed, but is equal ( == ) to the old spline."<<endl;
				iReturn++;
			}
			if ( ! ( splineRandIntDoubleOld != splineRandIntDouble ) ){
				cerr<<"Error: The spline is changed, but is not not  equal ( not != ) to the old spline."<<endl;
				iReturn++;
			}
		}
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalueSpline( vector< cDataPointRange< tX, tY> > ) method for creating random splines of type domain(x) = double and domain(y) = double"<<endl;
	
	cout<<"cSpline< double, double > splineRandDoubleDouble;"<<endl;
	cSpline< double, double > splineRandDoubleDouble;
	
	ulSplinesGenerated = 0;
	uiMaxParameter = 3;
	ulNextParameterIncrease = 8;
	
	for ( unsigned int uiIteration = 0; uiIteration < (MAX_ITERATION / 16 + 1); uiIteration++ ){
		
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating "<<uiIteration<<"'th random spline (double, double)"<<endl;
		
		ulSplinesGenerated++;
		if ( ulNextParameterIncrease < ulSplinesGenerated ){
			//increase max dimension with 1
			uiMaxParameter++;
			ulNextParameterIncrease *= ulNextParameterIncrease;
		}
		
		cSpline< double, double > generatorSplineDoubleDouble;
		
		unsigned int uiNumberOfSubPolynoms = 0;
		if ( rand() % 32 ){
			uiNumberOfSubPolynoms = rand() % uiMaxParameter + 1;
		}//else uiNumberOfParameters = 0;
		unsigned int uiNumberOfGeneratorSplineSubPolynoms = uiNumberOfSubPolynoms;
		unsigned int uiNumberOfAllParameters = 0;
		//generate sub-polynoms
		for ( unsigned int uiActualPolynom = 0;
				uiActualPolynom < uiNumberOfGeneratorSplineSubPolynoms; uiActualPolynom++){
			
			cPolynom< double, double > generatorPolynomDoubleDouble;
			
			unsigned int uiNumberOfGeneratorSplineFactors = 0;
			if ( rand() % 32 ){
				uiNumberOfGeneratorSplineFactors = rand() % uiMaxParameter + 1;
			}//else uiNumberOfParameters = 0;
			uiNumberOfAllParameters += uiNumberOfGeneratorSplineFactors;
		
			if ( ( (rand() % 8) == 0) ){
				//use generator spline with diffent number of factors
				uiNumberOfGeneratorSplineFactors = rand() % uiMaxParameter + 1;
			}
			if ( uiNumberOfGeneratorSplineFactors == 0 ){
				uiNumberOfGeneratorSplineFactors = 1;
			}
			double dMaxFactorValue = 10000.0;
			for ( unsigned int uiActualFactor = 0;
					uiActualFactor < uiNumberOfGeneratorSplineFactors; uiActualFactor++){
				
				generatorPolynomDoubleDouble.vecFactors.push_back(
					randomValue( dMaxFactorValue ) );
				if ( 8.0 < dMaxFactorValue ){
					dMaxFactorValue /= 8.0;
				}
			}
			generatorSplineDoubleDouble.vecPolynoms.push_back( generatorPolynomDoubleDouble );
		}
		//generate borders
		for ( unsigned int uiActualPolynom = 1;
				uiActualPolynom < uiNumberOfGeneratorSplineSubPolynoms; uiActualPolynom++){
			
			generatorSplineDoubleDouble.vecBorders.push_back(
				randomValue( 10000.0 ) );
		}
		sort( generatorSplineDoubleDouble.vecBorders.begin(),
			generatorSplineDoubleDouble.vecBorders.end() );
		
		cout<<"Spline from which the datapoints are generated:"<<endl;
		generatorSplineDoubleDouble.print( cout );
		
		unsigned int uiDataPointsToGenerate = 0;
		if ( rand() % 32 ){
			uiDataPointsToGenerate = rand() % ( (rand() % 64) + 1 ) + 1;
		}//else  uiDataPointsToGenerate = 0;
		//if bXIsRandom is true the x is generated random, else in increased
		bool bXIsRandom = ((rand() % 8) == 0);
		cout<<"vector< cDataPointRange< double, double > > vecDataPoints (size="<<
			uiDataPointsToGenerate<<")"<<(bXIsRandom?" random ":"")<<": {"<<flush;
		vector< cDataPointRange< double, double > > vecDataPoints;
		
		double iLastX = ((int)(uiDataPointsToGenerate)) / -2;
		const double dMaxXValueForRandGenerator = 8 * uiDataPointsToGenerate;
		
		double dMaxYValue = 0.0;
		double dMinYValue = 0.0;
		
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
			
			const double y = generatorSplineDoubleDouble.evalue( x );
			const double minY = y - absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			double maxY = y + absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			if ( ( rand() % 32 ) == 0 ){
				maxY = minY + absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			}
			if ( maxY <= minY ){
				maxY = minY + 0.0001;
			}
			
			cout<<"("<<flush<<x<<", "<<minY<<" till "<<maxY<<") "<<flush;
			vecDataPoints.push_back( cDataPointRange< double, double >( x, minY, maxY ) );
			
			dMinYValue = ( minY < dMinYValue ) ? minY : dMinYValue;
			dMaxYValue = ( dMaxYValue < maxY ) ? maxY : dMaxYValue;
		}
		cout<<"} "<<endl<<flush;
		
		const double dMaxAbsYValue = ( dMaxYValue < ( 0.0 - dMinYValue ) ) ?
			( 0.0 - dMinYValue ) : dMaxYValue;
		
		const cSpline< double, double > splineRandDoubleDoubleOld( splineRandDoubleDouble );
		
		unsigned int uiNumberOfParameters = 0;
		if ( rand() % 32 ){
			uiNumberOfParameters = rand() % uiMaxParameter + 1;
		}//else uiNumberOfParameters = 0;
		
#ifndef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		const unsigned int uiMinBitsToStoreMantissa = rand() % 32;
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		double maxValue = abs( randomValue( 1000000.0 ) ) + 1000.0;
		if ( (rand() % 8) == 0 ){
			maxValue = randomValue( 1000000.0 );
		}
		if ( uiNumberOfParameters == 1 ){
			/*with const polynoms max value must be greater as all y values to
			find a valid spline*/
			maxValue = ( maxValue < dMaxAbsYValue ) ?
				( dMaxAbsYValue + maxValue ) : maxValue ;
		}

#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		cout<<endl<<"splineRandDoubleDouble.evalueSpline( vecDataPoints, uiNumberOfParameters="<<
			uiNumberOfParameters<<",  maxValue="<<maxValue<<");"<<endl<<endl;
		unsigned long uiPointsIncluded = splineRandDoubleDouble.evalueSpline(
			vecDataPoints, uiNumberOfParameters, maxValue );
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		cout<<endl<<"splineRandDoubleDouble.evalueSpline( vecDataPoints, uiNumberOfParameters="<<
			uiNumberOfParameters<<", uiMinBitsToStoreMantissa="<<
			uiMinBitsToStoreMantissa<<" , maxValue="<<maxValue<<");"<<endl<<endl;
		unsigned long uiPointsIncluded = splineRandDoubleDouble.evalueSpline(
			vecDataPoints, uiNumberOfParameters, uiMinBitsToStoreMantissa, maxValue );
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		
		if ( 0 < uiPointsIncluded ){
			cout<<"Founded spline is for the "<<uiPointsIncluded<<" first "<<
				( (uiPointsIncluded == uiDataPointsToGenerate)?"(=all) ":"" )<<
				"range data points:"<<endl;
			splineRandDoubleDouble.print( cout );
		}else{
			cout<<"No new spline generated."<<endl;
		}
		
		if ( uiDataPointsToGenerate < uiPointsIncluded ){
			cerr<<"Error: Ther wher "<<uiPointsIncluded<<" but only "<<
				uiDataPointsToGenerate<<" points to include ."<<endl;
			iReturn++;
		}
		
		vector< cDataPointRange< double, double > > vecDataPointsCorrect =
			vecDataPoints;
		sort( vecDataPointsCorrect.begin(), vecDataPointsCorrect.end() );
		if ( 0 < uiPointsIncluded ){
			
			for ( unsigned int uiActualPolynom = 0;
					uiActualPolynom < splineRandDoubleDouble.vecPolynoms.size(); uiActualPolynom++ ){
					
				if ( ( 0 < uiNumberOfParameters ) &&
						(uiNumberOfParameters < splineRandDoubleDouble.vecPolynoms[ uiActualPolynom ].vecFactors.size()) ){
					cerr<<"Error: The "<<uiActualPolynom<<"'th polynom has "<<
						splineRandDoubleDouble.vecPolynoms[ uiActualPolynom ].vecFactors.size()<<
						" parameters, but should have maximal "<<uiNumberOfParameters<<" ."<<endl;
					iReturn++;
				}
				for ( unsigned int uiActualFactor = 0;
						uiActualFactor < splineRandDoubleDouble.vecPolynoms[ uiActualPolynom ].vecFactors.size();
						uiActualFactor++ ){
					
					if ( maxValue < abs( splineRandDoubleDouble.vecPolynoms[ uiActualPolynom ].vecFactors[ uiActualFactor ] * 0.999 ) ){
						cerr<<"Error: The "<<uiActualPolynom<<"'th polynom has as the "<<uiActualFactor<<
							"'th factor ("<<splineRandDoubleDouble.vecPolynoms[ uiActualPolynom ].vecFactors[ uiActualFactor ]<<
							") greater than the maxValue of "<<maxValue<<" ."<<endl;
						iReturn++;
					}
				}
			}
			
			/* check if the spline match the range data points*/
			if ( uiPointsIncluded < uiDataPointsToGenerate ){
				cerr<<"Warning: Not all points included into the spline. Points included "<<
					uiPointsIncluded<<", but points to include: "<<uiDataPointsToGenerate<<endl;
				iWarnings++;
				
				vecDataPointsCorrect.resize( uiPointsIncluded );
			}
			
			pair< unsigned long, double > paError = splineRandDoubleDouble.evalueError(
				vecDataPointsCorrect );
			
			if ( paError.first != 0 ){
				cerr<<"Warning: The spline dosn't match the "<<uiPointsIncluded<<
					" first range data points.";
				cerr<<" Ther are "<<paError.first<<" wrong points with a error sum of "<<
					paError.second<<" ."<<endl;
				iWarnings++;
				
				for ( unsigned int uiActualDataPoint = 0;
						uiActualDataPoint < vecDataPoints.size();
						uiActualDataPoint++ ){
					
					vector< cDataPointRange< double, double > > vecActualDataPoint;
					vecActualDataPoint.push_back( vecDataPoints[ uiActualDataPoint ] );
					
					paError = splineRandDoubleDouble.evalueError( vecActualDataPoint );
					if ( paError.first != 0 ){
						cerr<<"Warning: The spline dosn't match the "<<uiActualDataPoint<<
							"'th range data point ("<<vecDataPoints[ uiActualDataPoint ].x<<
							", "<<vecDataPoints[ uiActualDataPoint ].minY<<" till "<<
							vecDataPoints[ uiActualDataPoint ].maxY<<
							") . The error of it is "<< paError.second<<" ."<<endl;
					}
				}//end for all data points
			}
			
			if ( uiPointsIncluded < uiDataPointsToGenerate ){
				vector< cDataPointRange< double, double > > vecFirstDataPointWrong =
					vecDataPoints;
				vecFirstDataPointWrong.push_back( vecDataPoints[ uiPointsIncluded ] );
				
				paError = splineRandDoubleDouble.evalueError( vecFirstDataPointWrong );
				
				if ( paError.first == 0 ){
					cerr<<"Error: The spline dos match the "<<uiPointsIncluded<<
						"'th range data point, but shouldn't."<<endl;
					iReturn++;
				}
			}
		}else{// uiPointsIncluded == 0
			if ( (0 < uiDataPointsToGenerate) && ( 0.0 < maxValue ) && ( 0 < uiNumberOfParameters ) ){
				if ( (vecDataPointsCorrect[ 0 ].minY < maxValue) &&
						( (-1.0 * vecDataPointsCorrect[ 0 ].maxY) < maxValue) ){
					cerr<<"Error: Ther wher range data points generated, but non included."<<endl;
					iReturn++;
				}
			}
			if ( splineRandDoubleDoubleOld != splineRandDoubleDouble ){
				cerr<<"Error: The spline was changed for the datapoints, but shouldn't be (because non evalued)."<<endl;
				cerr<<"It should be unchanged:"<<endl;
				splineRandDoubleDoubleOld.print( cerr );
				iReturn++;
			}
		}

		if ( ( splineRandDoubleDouble.vecPolynoms == splineRandDoubleDoubleOld.vecPolynoms ) &&
				compareVectorDouble( splineRandDoubleDouble.vecBorders,
					splineRandDoubleDoubleOld.vecBorders ) ){
			//vector factors not changed
			if ( ! ( splineRandDoubleDoubleOld == splineRandDoubleDouble ) ){
				cerr<<"Error: The spline is not changed, but is not equal ( not == ) to the old spline."<<endl;
				iReturn++;
			}
			if ( splineRandDoubleDoubleOld != splineRandDoubleDouble ){
				cerr<<"Error: The spline is not changed, but is not equal ( != ) to the old spline."<<endl;
				iReturn++;
			}
		}else{//vector factors changed
			if ( splineRandDoubleDoubleOld == splineRandDoubleDouble ){
				cerr<<"Error: The spline is changed, but is equal ( == ) to the old spline."<<endl;
				iReturn++;
			}
			if ( ! ( splineRandDoubleDoubleOld != splineRandDoubleDouble ) ){
				cerr<<"Error: The spline is changed, but is not not  equal ( not != ) to the old spline."<<endl;
				iReturn++;
			}
		}
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the evalueSpline( vector< cDataPointRange< tX, tY> > ) method for creating random splines; a maximal error (maxError) value is given"<<endl;
	
	cout<<"cSpline< double, double > splineRandDoubleDouble2;"<<endl;
	cSpline< double, double > splineRandDoubleDouble2;
	
	ulSplinesGenerated = 0;
	uiMaxParameter = 3;
	ulNextParameterIncrease = 8;
	
	for ( unsigned int uiIteration = 0; uiIteration < (MAX_ITERATION / 16 + 1); uiIteration++ ){
		
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating "<<uiIteration<<"'th random splines (maxError given)"<<endl;
		
		ulSplinesGenerated++;
		if ( ulNextParameterIncrease < ulSplinesGenerated ){
			//increase max dimension with 1
			uiMaxParameter++;
			ulNextParameterIncrease *= ulNextParameterIncrease;
		}
		
		
		cSpline< double, double > generatorSplineDoubleDouble;
		
		unsigned int uiNumberOfSubPolynoms = 0;
		if ( rand() % 32 ){
			uiNumberOfSubPolynoms = rand() % uiMaxParameter + 1;
		}//else uiNumberOfParameters = 0;
		unsigned int uiNumberOfGeneratorSplineSubPolynoms = uiNumberOfSubPolynoms;
		unsigned int uiNumberOfAllParameters = 0;
		//generate sub-polynoms
		for ( unsigned int uiActualPolynom = 0;
				uiActualPolynom < uiNumberOfGeneratorSplineSubPolynoms; uiActualPolynom++){
			
			cPolynom< double, double > generatorPolynomDoubleDouble;
			
			unsigned int uiNumberOfGeneratorSplineFactors = 0;
			if ( rand() % 32 ){
				uiNumberOfGeneratorSplineFactors = rand() % uiMaxParameter + 1;
			}//else uiNumberOfParameters = 0;
			uiNumberOfAllParameters += uiNumberOfGeneratorSplineFactors;
		
			if ( ( (rand() % 8) == 0) ){
				//use generator spline with diffent number of factors
				uiNumberOfGeneratorSplineFactors = rand() % uiMaxParameter + 1;
			}
			if ( uiNumberOfGeneratorSplineFactors == 0 ){
				uiNumberOfGeneratorSplineFactors = 1;
			}
			double dMaxFactorValue = 10000.0;
			for ( unsigned int uiActualFactor = 0;
					uiActualFactor < uiNumberOfGeneratorSplineFactors; uiActualFactor++){
				
				generatorPolynomDoubleDouble.vecFactors.push_back(
					randomValue( dMaxFactorValue ) );
				if ( 8.0 < dMaxFactorValue ){
					dMaxFactorValue /= 8.0;
				}
			}
			generatorSplineDoubleDouble.vecPolynoms.push_back( generatorPolynomDoubleDouble );
		}
		//generate borders
		for ( unsigned int uiActualPolynom = 1;
				uiActualPolynom < uiNumberOfGeneratorSplineSubPolynoms; uiActualPolynom++){
			
			generatorSplineDoubleDouble.vecBorders.push_back(
				randomValue( 10000.0 ) );
		}
		sort( generatorSplineDoubleDouble.vecBorders.begin(),
			generatorSplineDoubleDouble.vecBorders.end() );
		
		cout<<"Spline from which the datapoints are generated:"<<endl;
		generatorSplineDoubleDouble.print( cout );
		
		unsigned int uiDataPointsToGenerate = 0;
		if ( rand() % 32 ){
			uiDataPointsToGenerate = rand() % ( (rand() % 64) + 1 ) + 1;
		}//else  uiDataPointsToGenerate = 0;
		//if bXIsRandom is true the x is generated random, else in increased
		bool bXIsRandom = ((rand() % 8) == 0);
		cout<<"vector< cDataPointRange< double, double > > vecDataPoints (size="<<
			uiDataPointsToGenerate<<")"<<(bXIsRandom?" random ":"")<<": {"<<flush;
		vector< cDataPointRange< double, double > > vecDataPoints;
		
		double iLastX = ((int)(uiDataPointsToGenerate)) / -2;
		const double dMaxXValueForRandGenerator = 8 * uiDataPointsToGenerate;
		
		double dMaxYValue = 0.0;
		double dMinYValue = 0.0;
		
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
			
			const double y = generatorSplineDoubleDouble.evalue( x );
			const double minY = y - absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			double maxY = y + absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			if ( ( rand() % 32 ) == 0 ){
				maxY = minY + absF( randomValue( absF( y ) / 100.0 + 1.0 ) );
			}
			if ( maxY <= minY ){
				maxY = minY + 0.0001;
			}
			
			cout<<"("<<flush<<x<<", "<<minY<<" till "<<maxY<<") "<<flush;
			vecDataPoints.push_back( cDataPointRange< double, double >( x, minY, maxY ) );
			
			dMinYValue = ( minY < dMinYValue ) ? minY : dMinYValue;
			dMaxYValue = ( dMaxYValue < maxY ) ? maxY : dMaxYValue;
		}
		cout<<"} "<<endl<<flush;
		
		const double dMaxAbsYValue = ( dMaxYValue < ( 0.0 - dMinYValue ) ) ?
			( 0.0 - dMinYValue ) : dMaxYValue;
		
		const cSpline< double, double > splineRandDoubleDouble2Old( splineRandDoubleDouble2 );
		
		unsigned int uiNumberOfParameters = 0;
		if ( rand() % 32 ){
			uiNumberOfParameters = rand() % uiMaxParameter + 1;
		}//else uiNumberOfParameters = 0;
#ifndef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		const unsigned int uiMinBitsToStoreMantissa = rand() % 32;
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		double maxValue = abs( randomValue( 1000000.0 ) ) + 1000.0;
		if ( (rand() % 8) == 0 ){
			maxValue = randomValue( 1000000.0 );
		}
		if ( uiNumberOfParameters == 1 ){
			/*with const polynoms max value must be greater as all y values to
			find a valid spline*/
			maxValue = ( maxValue < dMaxAbsYValue ) ?
				( dMaxAbsYValue + maxValue ) : maxValue ;
		}
		
		double dMaxError = randomValue( 1000000.0 );
		if ( rand() % 16 ){
			dMaxError = abs( dMaxError );
		}
		
#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		cout<<endl<<"splineRandDoubleDouble2.evalueSpline( vecDataPoints, uiNumberOfParameters="<<
			uiNumberOfParameters<<", maxValue="<<maxValue<<", dMaxError="<<dMaxError<<");"<<endl<<endl<<flush;
		unsigned long uiPointsIncluded = splineRandDoubleDouble2.evalueSpline(
			vecDataPoints, uiNumberOfParameters, maxValue, dMaxError );
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		cout<<endl<<"splineRandDoubleDouble2.evalueSpline( vecDataPoints, uiNumberOfParameters="<<
			uiNumberOfParameters<<", uiMinBitsToStoreMantissa="<<
			uiMinBitsToStoreMantissa<<" , maxValue="<<maxValue<<", dMaxError="<<dMaxError<<");"<<endl<<endl<<flush;
		unsigned long uiPointsIncluded = splineRandDoubleDouble2.evalueSpline(
			vecDataPoints, uiNumberOfParameters, uiMinBitsToStoreMantissa, maxValue, dMaxError );
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
		
		if ( 0 < uiPointsIncluded ){
			cout<<"Founded spline is for the "<<uiPointsIncluded<<" first "<<
				( (uiPointsIncluded == uiDataPointsToGenerate)?"(=all) ":"" )<<
				"range data points:"<<endl<<flush;
			splineRandDoubleDouble2.print( cout );
		}else{
			cout<<"No new spline generated."<<endl<<flush;
		}
		
		if ( uiDataPointsToGenerate < uiPointsIncluded ){
			cerr<<"Error: Ther wher "<<uiPointsIncluded<<" but only "<<
				uiDataPointsToGenerate<<" points to include ."<<endl;
			iReturn++;
		}
		
		vector< cDataPointRange< double, double > > vecDataPointsCorrect =
			vecDataPoints;
		sort( vecDataPointsCorrect.begin(), vecDataPointsCorrect.end() );
		if ( 0 < uiPointsIncluded ){
			
			for ( unsigned int uiActualPolynom = 0;
					uiActualPolynom < splineRandDoubleDouble2.vecPolynoms.size(); uiActualPolynom++ ){
					
				if ( ( 0 < uiNumberOfParameters ) &&
						(uiNumberOfParameters < splineRandDoubleDouble2.vecPolynoms[ uiActualPolynom ].vecFactors.size()) ){
					cerr<<"Error: The "<<uiActualPolynom<<"'th polynom has "<<
						splineRandDoubleDouble2.vecPolynoms[ uiActualPolynom ].vecFactors.size()<<
						" parameters, but should have maximal "<<uiNumberOfParameters<<" ."<<endl;
					iReturn++;
				}
				for ( unsigned int uiActualFactor = 0;
						uiActualFactor < splineRandDoubleDouble2.vecPolynoms[ uiActualPolynom ].vecFactors.size();
						uiActualFactor++ ){
					
					if ( maxValue < abs( splineRandDoubleDouble2.vecPolynoms[ uiActualPolynom ].vecFactors[ uiActualFactor ] * 0.999 ) ){
						cerr<<"Error: The "<<uiActualPolynom<<"'th polynom has as the "<<uiActualFactor<<
							"'th factor ("<<splineRandDoubleDouble2.vecPolynoms[ uiActualPolynom ].vecFactors[ uiActualFactor ]<<
							") greater than the maxValue of "<<maxValue<<" ."<<endl;
						iReturn++;
					}
				}
			}
			
			/* check if the spline match the range data points*/
			if ( uiPointsIncluded < uiDataPointsToGenerate ){
				cerr<<"Warning: Not all points included into the spline. Points included "<<
					uiPointsIncluded<<", but points to include: "<<uiDataPointsToGenerate<<endl;
				iWarnings++;
				
				vecDataPointsCorrect.resize( uiPointsIncluded );
			}
			
			pair< unsigned long, double > paError = splineRandDoubleDouble2.evalueError(
				vecDataPointsCorrect );
			
			if ( dMaxError < (paError.second * 0.99) ){
				cerr<<"Warning: The spline dosn't match the "<<uiPointsIncluded<<
					" first range data points.";
				cerr<<" Ther are "<<paError.first<<" wrong points with a error sum of "<<
					paError.second<<" ."<<endl;
				iWarnings++;
				
#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
				const double dMaxErrorPerValue = ( dMaxError == 0.0 ) ? 0.0000001 :
					( ( dMaxError / ((double)vecDataPoints.size()) ) * 1.01 );
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
				
				for ( unsigned int uiActualDataPoint = 0;
						uiActualDataPoint < vecDataPoints.size();
						uiActualDataPoint++ ){
					
					vector< cDataPointRange< double, double > > vecActualDataPoint;
					vecActualDataPoint.push_back( vecDataPoints[ uiActualDataPoint ] );
					
					paError = splineRandDoubleDouble2.evalueError( vecActualDataPoint );
#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
					if ( dMaxErrorPerValue < paError.first ){
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
					if ( paError.first != 0 ){
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
						cerr<<"Warning: The spline dosn't match the "<<uiActualDataPoint<<
							"'th range data point ("<<vecDataPoints[ uiActualDataPoint ].x<<
							", "<<vecDataPoints[ uiActualDataPoint ].minY<<" till "<<
							vecDataPoints[ uiActualDataPoint ].maxY<<
							") . The error of it is "<< paError.second<<" ."<<endl;
					}
				}//end for all data points
			}
			
			if ( uiPointsIncluded < uiDataPointsToGenerate ){
				vector< cDataPointRange< double, double > > vecFirstDataPointWrong =
					vecDataPoints;
				vecFirstDataPointWrong.push_back( vecDataPoints[ uiPointsIncluded ] );
				
				paError = splineRandDoubleDouble2.evalueError( vecFirstDataPointWrong );
				
				if ( paError.first == 0 ){
					cerr<<"Error: The spline dos match the "<<uiPointsIncluded<<
						"'th range data point, but shouldn't."<<endl;
					iReturn++;
				}
			}
		}else{// uiPointsIncluded == 0
			if ( (0 < uiDataPointsToGenerate) && ( 0.0 < maxValue ) &&
					( 0 < uiNumberOfParameters ) && ( 0.0 <= dMaxError ) ){
				if ( (vecDataPointsCorrect[ 0 ].minY < maxValue) &&
						( (-1.0 * vecDataPointsCorrect[ 0 ].maxY) < maxValue) ){
					cerr<<"Error: Ther wher range data points generated, but non included."<<endl;
					iReturn++;
				}
			}
			if ( splineRandDoubleDouble2Old != splineRandDoubleDouble2 ){
				cerr<<"Error: The spline was changed for the datapoints, but shouldn't be (because non evalued)."<<endl;
				cerr<<"It should be unchanged:"<<endl;
				splineRandDoubleDouble2Old.print( cerr );
				iReturn++;
			}
		}

		if ( ( splineRandDoubleDouble2.vecPolynoms == splineRandDoubleDouble2Old.vecPolynoms ) &&
				compareVectorDouble( splineRandDoubleDouble2.vecBorders,
					splineRandDoubleDouble2Old.vecBorders ) ){
			//vector factors not changed
			if ( ! ( splineRandDoubleDouble2Old == splineRandDoubleDouble2 ) ){
				cerr<<"Error: The spline is not changed, but is not equal ( not == ) to the old spline."<<endl;
				iReturn++;
			}
			if ( splineRandDoubleDouble2Old != splineRandDoubleDouble2 ){
				cerr<<"Error: The spline is not changed, but is not equal ( != ) to the old spline."<<endl;
				iReturn++;
			}
		}else{//vector factors changed
			if ( splineRandDoubleDouble2Old == splineRandDoubleDouble2 ){
				cerr<<"Error: The spline is changed, but is equal ( == ) to the old spline."<<endl;
				iReturn++;
			}
			if ( ! ( splineRandDoubleDouble2Old != splineRandDoubleDouble2 ) ){
				cerr<<"Error: The spline is changed, but is not not  equal ( not != ) to the old spline."<<endl;
				iReturn++;
			}
		}
	}




	return iReturn;
}










