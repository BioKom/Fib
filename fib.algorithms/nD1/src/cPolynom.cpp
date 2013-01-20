/**
 * @file cPolynom
 * file name: cPolynom.cpp
 * @author Betti Oesterholz
 * @date 07.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements a class for a one dimensional polynom.
 * Copyright (C) @c GPL3 2010 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (GPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This file implements a class with methods and functions for a one
 * dimensional polynom functions.
 * The second template parameter should always be a floating point datatype.
 *
 */
/*
History:
07.06.2010  Oesterholz  created
12.02.2011  Oesterholz  method evalueSpline() added
12.02.2011  Oesterholz  FEATURE_ND1_POLYNOM_TO_HORN_SCHEMA_FIB_UNDERFUNCTION implemented
27.03.2011  Oesterholz  method getLastFactorIndexNotNull() added
09.04.2011  Oesterholz  method cHyperplaneBody replaced by cHyperplaneBodyFull
	and cHyperplaneBodySimple
29.12.2012  Oesterholz  FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING:
	evalueSplineIterativFast(): the glp library (extern package) linear
	solver will be used to find a spline for a vector of range data points
*/



#ifndef ___N_D_1_C_POLYNOM_CPP__
#define ___N_D_1_C_POLYNOM_CPP__

#include "../incl/cPolynom.h"
#include "../incl/cPolynomRange.h"

#include "nLinearEquation.h"
#include "cLinearEquation.h"
#include "cHyperplaneBodyFull.h"
#include "cHyperplaneBodySimple.h"

#include "cFunctionValue.h"
#include "cFunctionVariable.h"
#include "cFunctionAdd.h"
#include "cFunctionMult.h"
#include "cFunctionExp.h"


#include <iostream>

#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
	#include "mutexGlpkSolver.inc"
	#include <glpk.h>
	#include <limits.h>
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING


//for debugging
#define DEBUG_C_POLYNOM
//#define DEBUG_C_POLYNOM_EVALUE

//#define PRINT_INFOS

#ifdef PRINT_INFOS
	#define PRINT_INFOS_FIND_POLYNOM_RAND
#endif


using namespace fib::algorithms::nD1;
using namespace fib::algorithms::nDn;
using namespace fib::algorithms::nLinearEquation;


/**
 * Standartconstructor
 */
template <class tX, class tY> fib::algorithms::nD1::cPolynom<tX, tY>::cPolynom():
		vecFactors(){
	//nothing to do
}


/**
 * This function evalues the value of this polynom.
 *
 * The evalued function is:
 * f( x ) = vecFactors[ 0 ] + vecFactors[ 1 ] * x +
 * 	vecFactors[ 2 ] * x^2 + ... +
 * 	vecFactors[ vecFactors.size() - 1 ] *
 * 		x^(vecFactors.size() - 1)
 *
 * @param x the input value for the polynom
 * @return the evalued value f( x )
 */
template <class tX, class tY> tY fib::algorithms::nD1::cPolynom<tX, tY>::
		evalue( const tX & x ) const{
	
	const unsigned int uiFactors = vecFactors.size();
	if ( uiFactors == 0 ){
		return 0;
	}
	tY value = 0.0;
	tY xmAPotenz = 1.0;
	
	for ( unsigned int uiActualFactor = 0; uiActualFactor < uiFactors;
			uiActualFactor++ ){

		value += vecFactors[ uiActualFactor ] * xmAPotenz;
		
		xmAPotenz *= ((tY)(x));
	}
	return value;
}


/**
 * This function prints this polynom to the given stream.
 *
 * @param outputStream the stream wher to print this polynom to
 */
template <class tX, class tY> void fib::algorithms::nD1::cPolynom<tX, tY>::
	print( ostream & outputStream ) const{
	
	const unsigned int uiFactors = vecFactors.size();
	bool bPrintAdd = false;
	outputStream<<"fp( x ) = ";
	for ( unsigned int uiActualFactor = 0;
			uiActualFactor < uiFactors; uiActualFactor++ ){
		
		if ( vecFactors[ uiActualFactor ] == 0 ){
			continue;//skip
		}
		
		if ( bPrintAdd ){
			outputStream<<" + ";
		}
		outputStream<< vecFactors[ uiActualFactor ] <<
			" * x^"<< uiActualFactor;
		
		bPrintAdd = true;
	}
	outputStream<<endl;
}


/**
 * This functions evalues the error of the given datapoints to the values
 * this polynom evalues to.
 *
 * The evaluation of the polynom will be done by evalue().
 * The error will just be counted, if it is greater than a real small value.
 * @see evalue()
 *
 * @param vecInput the data for wich the error is to evalue
 * @return a pair with two values:
 * 	- the first value is the number of datapoints evalued wrong
 * 	- the second value is the sum of the error of all datapoints
 */
template <class tX, class tY> pair<unsigned long, tY>
	fib::algorithms::nD1::cPolynom<tX, tY>::evalueError(
		const vector< cDataPoint< tX, tY> > & vecInput ) const{
	
	tY dError = 0.0;
	unsigned long ulWrongValues = 0;
	
	for ( size_t iActualValue = 0; iActualValue < vecInput.size();
			iActualValue++ ){
		
		const tY dPolynomValue = evalue( vecInput[ iActualValue ].x );
		
		const tY y = vecInput[ iActualValue ].y;
		
		if ( ! compareDouble( y, dPolynomValue ) ){
			dError += absF( dPolynomValue - y );
			ulWrongValues++;
		}
	}

	return make_pair( ulWrongValues, dError );
}


/**
 * This functions evalues the error of the given datapoints to the values
 * this polynom evalues to.
 * This function will stop the evaluation, if the maximum error maxYError
 * was reached.
 *
 * The evaluation of the polynom will be done by evalue().
 * The error will just be counted, if it is greater than the a real small value.
 * @see evalue()
 *
 * @param vecInput the data for wich the error is to evalue
 * @param maxYError the maximum error, at which the evaluation should stop;
 * 	if maxYError is 0 the maximum error is unlimeted
 * @return the sum of the error of all datapoints, but maximal maxYError
 */
template <class tX, class tY> tY fib::algorithms::nD1::cPolynom<tX, tY>::
	evalueErrorMax( const vector< cDataPoint< tX, tY> > & vecData,
		const tY maxYError ) const{
	
	tY dError = 0.0;
	
	for ( size_t iActualValue = 0; iActualValue < vecData.size();
			iActualValue++ ){
		
		const tY dPolynomValue = evalue( vecData[ iActualValue ].x );
		
		const tY y = vecData[ iActualValue ].y;
		
		if ( ! compareDouble( y, dPolynomValue ) ){
			dError += absF( dPolynomValue - y );
		}
		if ( (maxYError <= dError) && (0.0 < maxYError) ){
			//max error reached
			return maxYError;
		}
	}
	return dError;
}


/**
 * This functions evalues the error of the given range datapoints to the
 * values this polynom evalues to.
 *
 * The evaluation of the polynom will be done by evalue().
 * A datapoint has an error, if it lay outside the datpoint range. The
 * error is it's distance to the neares datapoint boundery.
 * The error will just be counted, if it is greater than the a real small value.
 * @see evalue()
 *
 * @param vecInput the data for wich the error is to evalue
 * @return a pair with two values:
 * 	- the first value is the number of datapoints evalued wrong
 * 	- the second value is the sum of the error of all datapoints
 */
template <class tX, class tY> pair<unsigned long, tY>
	fib::algorithms::nD1::cPolynom<tX, tY>::evalueError(
		const vector< cDataPointRange< tX, tY> > & vecInput ) const{
	
	tY dError = 0.0;
	unsigned long ulWrongValues = 0;
	
	for ( size_t iActualValue = 0; iActualValue < vecInput.size();
			iActualValue++ ){
		
		const tY dPolynomValue = evalue( vecInput[ iActualValue ].x );
		
		const tY minY = vecInput[ iActualValue ].minY;
		const tY maxY = vecInput[ iActualValue ].maxY;
		
		if ( dPolynomValue < minY){
			dError += minY - dPolynomValue;
			ulWrongValues++;
		}else if ( maxY < dPolynomValue ){
			dError += dPolynomValue - maxY;
			ulWrongValues++;
		}
	}

	return make_pair( ulWrongValues, dError );
}


/**
 * This functions evalues the error of the given datapoints to the values
 * this polynom evalues to.
 * This function will stop the evaluation, if the maximum error maxYError
 * was reached.
 *
 * The evaluation of the polynom will be done by evalue().
 * A datapoint has an error, if it lay outside the datpoint range. The
 * error is it's distance to the neares datapoint boundery.
 * The error will just be counted, if it is greater than the a real small value.
 * @see evalue()
 *
 * @param vecInput the data for wich the error is to evalue
 * @param maxYError the maximum error, at which the evaluation should stop;
 * 	if maxYError is 0 the maximum error is unlimeted
 * @return the sum of the error of all datapoints, but maximal maxYError
 */
template <class tX, class tY> tY fib::algorithms::nD1::cPolynom<tX, tY>::
	evalueErrorMax( const vector< cDataPointRange< tX, tY> > & vecData,
		const tY maxYError ) const{
	
	tY dError = 0.0;
	
	for ( size_t iActualValue = 0; iActualValue < vecData.size();
			iActualValue++ ){
		
		const tY dPolynomValue = evalue( vecData[ iActualValue ].x );
		
		const tY minY = vecData[ iActualValue ].minY;
		const tY maxY = vecData[ iActualValue ].maxY;
		if ( dPolynomValue < minY){
			dError += minY - dPolynomValue;
		}else if ( maxY < dPolynomValue ){
			dError += dPolynomValue - maxY;
		}
		if ( (maxYError <= dError) && (0.0 < maxYError) ){
			//max error reached
			return maxYError;
		}
	}
	return dError;
}


/**
 * This methods creats the linear equiations ( @see cLinearEquation )
 * for the given datapoints.
 * The linear equiations will have the form (for each data point):
 * 	vecData.y = x_0 + vecData.x * x_1 + vecData.x^2 * x_2 + ... +
 * 		vecData.x^(uiMaxPolynomOrder - 1) * x_{uiMaxPolynomOrder - 1}
 *
 * @param vecData the with the datapoints, for which to evalue the
 * 	linear equiations
 * @param uiMaxPolynomOrder the maximal order of the polynom to generate
 * 	the factor ranges for
 * @return a vector with the linear equiations for the datapoints
 */
template <class tX, class tY> vector< cLinearEquation<tY> >
	fib::algorithms::nD1::cPolynom<tX, tY>::createLinearEquations(
		const vector< cDataPoint< tX, tY> > & vecData,
		unsigned int uiMaxPolynomOrder ) const{
	
	
	const unsigned long ulNumberOfDataPoints = vecData.size();
	
	vector< cLinearEquation<tY> > vecOfEquations( ulNumberOfDataPoints,
		cLinearEquation<tY>( uiMaxPolynomOrder ) );
	
	for( unsigned long iActualDataPoint = 0;
			iActualDataPoint < ulNumberOfDataPoints; iActualDataPoint++ ){
		
		//set the values for the x / a_i factors
		const tX x = vecData[ iActualDataPoint ].x;
		tY dFactor = 1.0;
		for ( unsigned int uiActualFactor = 0; uiActualFactor < uiMaxPolynomOrder;
				uiActualFactor++ ){
			
			vecOfEquations[ iActualDataPoint ].vecFactors[ uiActualFactor ] =
				dFactor;
			dFactor *= x;
		}
		//set the y value
		vecOfEquations[ iActualDataPoint ].constant =
			vecData[ iActualDataPoint ].y;
	}
#ifdef PRINT_INFOS
	printEquations( vecOfEquations, cout );
#endif
	return vecOfEquations;
}


/**
 * This function creats the two inequiations for the range data point.
 * This inequiations restrict the values in the same way as the range
 * data point and have the form:
 * 	minY <= a_0 + a_1 * x + a_2 * x^2 + ...
 * 		... + a_{uiPolynomOrder-1} * x^(uiPolynomOrder-1)
 * and
 * 	-1 * maxY <= -1 * a_0 - a_1 * x - a_2 * x^2 - ...
 * 		... - a_{uiPolynomOrder-1} * x^(uiPolynomOrder-1)
 *
 * @param dataPoint the range datapoint, for which to create the
 * 	inequiations
 * @param uiPolynomOrder the order for the polynom, which builds the
 * 	inequiations
 * @return the two polynom inequiations as a pair, which restrict the
 * 	values in the same way as the range datapoint
 */
template <class tX, class tY> pair< cInequation< tY >, cInequation< tY > >
		fib::algorithms::nD1::cPolynom<tX, tY>::createInequiationsForRangePoint(
			const cDataPointRange< tX, tY> & dataPoint,
			unsigned int uiPolynomOrder ) const{
	
	//create first inequiation
	cInequation< tY > inequiation1;
	inequiation1.constant = dataPoint.minY;
	inequiation1.vecFactors = vector< tY >( uiPolynomOrder, 0 );
	
	tY actualXPower = 1.0;
	const tY x = dataPoint.x;
	for ( unsigned int uiActualFactor = 0; uiActualFactor < uiPolynomOrder;
			uiActualFactor++ ){
		
		inequiation1.vecFactors[ uiActualFactor ] = actualXPower;
		actualXPower *= x;
	}
	//create second inequiation
	cInequation< tY > inequiation2;
	inequiation2.constant = -1.0 * dataPoint.maxY;
	inequiation2.vecFactors = vector< tY >( uiPolynomOrder, 0 );
	
	actualXPower = -1.0;
	for ( unsigned int uiActualFactor = 0; uiActualFactor < uiPolynomOrder;
			uiActualFactor++ ){
		
		inequiation2.vecFactors[ uiActualFactor ] = actualXPower;
		actualXPower *= x;
	}
	
	return make_pair( inequiation1, inequiation2 );
}


/**
 * @return the index of the last factor, wich is not 0
 * 	(counting from 0, eg. if 0 is return the polynom is constant)
 * 	if -1 is returned all factors are 0
 */
template <class tX, class tY> long fib::algorithms::nD1::cPolynom<tX, tY>::
		getLastFactorIndexNotNull() const{
	
	long lLastFactorNotNull = vecFactors.size() - 1;
	while ( ( 0 <= lLastFactorNotNull ) &&
			isEqualNull( vecFactors[ lLastFactorNotNull ] ) ){
		
		lLastFactorNotNull--;
	}
	return lLastFactorNotNull;
}


/**
 * This function converts this polynom, into an fib -underfunction.
 * Beware: You have to delete the returned fib -underfunction.
 *
 * @param pVariable the variable (x) for the polynom
 * @return a pointer to the fib -underfunction, wich represents the
 * 	same polynom as this polynom
 */
template <class tX, class tY> cUnderFunction * fib::algorithms::nD1::cPolynom<tX, tY>::
	toFibUnderFunction( cFibVariable * pVariable ) const{
	
	if ( vecFactors.empty() ){
		return new cFunctionValue( 0.0 );
	}
	cUnderFunction * pUnderFunction = NULL;
#ifdef FEATURE_ND1_POLYNOM_TO_HORN_SCHEMA_FIB_UNDERFUNCTION
	/* f( x ) = vecFactors[ 0 ] + x * ( vecFactors[ 1 ] + x * (vecFactors[ 2 ] + ... +
		vecFactors[ vecFactors.size() - 1 ] * x */
	//find last factor not 0
	const long lLastFactorNotNull = getLastFactorIndexNotNull();
	
	if ( lLastFactorNotNull < 0 ){
		//all factors are 0
		return new cFunctionValue( 0.0 );
	}
	cFunctionVariable underFunctionX( pVariable );
	{//add underfunction for last factor
		pUnderFunction = new cFunctionValue( (doubleFib)(vecFactors[ lLastFactorNotNull ] ) );
	}
	cUnderFunction * pLastUnderFunction = NULL;
	for ( long lActualFactor = (lLastFactorNotNull - 1); 0 <= lActualFactor;
			lActualFactor-- ){
		
		pLastUnderFunction = pUnderFunction;
		
		if ( ! isEqualNull( vecFactors[ lActualFactor ] ) ){
			pUnderFunction = new cFunctionAdd(
				cFunctionValue( (doubleFib)(vecFactors[ lActualFactor ] ) ),
				cFunctionMult( underFunctionX, *pUnderFunction ) );
		}else{
			pUnderFunction = new cFunctionMult( underFunctionX, *pUnderFunction );
		}
		
		delete pLastUnderFunction;
	}
	
#else //FEATURE_ND1_POLYNOM_TO_HORN_SCHEMA_FIB_UNDERFUNCTION
	/* f( x ) = vecFactors[ 0 ] + vecFactors[ 1 ] * x + vecFactors[ 2 ] * x^2 + ... +
		vecFactors[ vecFactors.size() - 1 ] * x^(vecFactors.size() - 1) */
	//create the factors of the polynom
	list< cUnderFunction * > liFactors;
	for ( size_t iActualFactor = 0; iActualFactor < vecFactors.size();
			iActualFactor++ ){
		
		if ( isEqualNull( vecFactors[ iActualFactor ] ) ){
			//skip 0 factors
			continue;
		}
		if ( iActualFactor == 0 ){//vecFactors[ 0 ]
			liFactors.push_back( new cFunctionValue( (doubleFib)(vecFactors[ 0 ] ) ) );
		}else if ( iActualFactor == 1 ){
			//vecFactors[ 1 ] * x
			cFunctionValue underFunctionA1( (doubleFib)(vecFactors[ 1 ] ) );
			cFunctionVariable underFunctionX( pVariable );
			liFactors.push_back( new cFunctionMult( underFunctionA1, underFunctionX ) );
		}else{// ( 1 < iActualFactor )
			cFunctionValue underFunctionAi( (doubleFib)(vecFactors[ iActualFactor ] ) );
			cFunctionVariable underFunctionX( pVariable );
			cFunctionValue underFunctionExponent( (doubleFib)( iActualFactor ) );
			liFactors.push_back( new cFunctionMult( underFunctionAi,
				cFunctionExp( underFunctionX, underFunctionExponent ) ) );
		}
	}
	//combine the factors of the underfunction
	for ( list< cUnderFunction * >::iterator itrFactor = liFactors.begin();
			itrFactor != liFactors.end(); itrFactor++ ){
		
		if ( pUnderFunction ){
			//add new factor to the existing factors
			cUnderFunction * pUnderFunctionNew =
				new cFunctionAdd( *pUnderFunction, **itrFactor );
			
			delete pUnderFunction;
			delete (*itrFactor);
			pUnderFunction = pUnderFunctionNew;
			
		}else{
			pUnderFunction = (*itrFactor);
		}
	}
#endif //FEATURE_ND1_POLYNOM_TO_HORN_SCHEMA_FIB_UNDERFUNCTION
	if ( pUnderFunction == NULL ){
		return new cFunctionValue( 0.0 );
	}
	
	return pUnderFunction;
}



/**
 * This function evalues the polynom for the given data.
 * The evalued polynom will have the order n of the number of given
 * datapoints.
 *
 * @param vecInputData the data for which to evalue the polynom
 * @return if an polynom for the datapoints could be evalued, the factors
 * 	of the evalued polynom in this polynom and true, else false
 * 	and the factors of this polynom dosn't changed
 */
template<class tX, class tY> bool
	fib::algorithms::nD1::cPolynom<tX, tY>::evalue(
		const vector< cDataPoint< tX, tY> > & vecInputData ){

	//create equations for n rondom choosen points
	vector< cDataPoint< tX, tY> > vecData( vecInputData );
	sort( vecData.begin(), vecData.end() );
	const unsigned int uiPolynomOrder = vecData.size();
	
	if ( uiPolynomOrder == 0 ){
		//no data points -> nothing to do
		return false;
	}
	vector< cLinearEquation<tY> > vecOfEquationsOriginal =
		createLinearEquations( vecData, uiPolynomOrder );
	
	//create the triangle form
	vector< cLinearEquation<tY> > vecOfEquationsTriangle =
		crateDiagonalForm( vecOfEquationsOriginal );
#ifdef PRINT_INFOS
	cout<<endl<<"Polynom in triangle form:"<<endl;
	printEquations( vecOfEquationsTriangle, cout );
#endif
	for ( unsigned int uiActualFactor = 0; uiActualFactor < uiPolynomOrder;
			uiActualFactor++ ){
		
		if ( ! vecOfEquationsTriangle[ uiActualFactor ].isSolvebel() ){
			/*equiation system not solvebel
			-> no polynom for the datapoints exists*/
			return false;
		}
	}
	//get the a_i factors
	vecFactors.clear();
	for ( unsigned int uiActualFactor = 0; uiActualFactor < uiPolynomOrder;
			uiActualFactor++ ){
		
		if ( ! vecOfEquationsTriangle[ uiActualFactor ].isNull() ){
			//store the actual factor
			vecFactors.push_back(
				vecOfEquationsTriangle[ uiActualFactor ].constant );
		}else{//all following factors are 0
			break;
		}
	}
	return true;
}


/**
 * This function trys to find a polynom for the given data vecData by
 * choosen n random points from vecData and create a polynom of order n
 * for them.
 * The number n will at the beginning be 1 and then canged random in an
 * reange near the best found polynomorder till now.
 * The creation of the polynom from random datapoints is tryed
 * ulMaxIterations times and the polynom with the smales error on the data
 * is returned.
 *
 * @see evalue() for the type of the polynom
 * @param vecInputData the data which the returend polynom should match
 * @param ulMaxIterations the maximal number of iterations / polynoms to
 * 	generate
 * @return the error of the best found function;
 * 	and the values of the evalued polynom in this polynom
 */
template<class tX, class tY> tY
	fib::algorithms::nD1::cPolynom<tX, tY>::findFunctionRand(
		const vector< cDataPointRange< tX, tY> > & vecInputData,
		unsigned long ulMaxIterations ){
	
	vector< cDataPointRange< tX, tY> > vecData( vecInputData );
	sort( vecData.begin(), vecData.end() );
	
	vector< tY > vecActualPolyFactors( 1 );
	tY dActualPolynomError = -1.0;
	
	for ( unsigned long ulIteration = 0; ulIteration < ulMaxIterations; ulIteration++ ){
#ifdef PRINT_INFOS
		cout<<endl<<"Iteration:"<<ulIteration<<endl;
#endif
		//choose the polynom order n
		unsigned int uiPolynomOrder = 1;
		if ( dActualPolynomError == 0.0 ){
			//reduce polynomorder
			uiPolynomOrder = rand() % vecActualPolyFactors.size() + 1;
		}else{
			uiPolynomOrder = rand() % (vecActualPolyFactors.size() + 5) + 1;
		}
		
		//create equations for n rondom choosen points
		vector< cDataPoint< tX, tY> > vecRandDataPoints;
		for( unsigned long iActualDataPoint = 1;
				iActualDataPoint < uiPolynomOrder; iActualDataPoint++ ){
			
			const unsigned long uiRandomPoint = rand() % vecData.size();
			
			cDataPoint< tX, tY> randDataPoint;
			
			//set the values for the x / a_i factors
			randDataPoint.x = vecData[ uiRandomPoint ].x;
			
			//set the y value to a random value in the y area
			randDataPoint.y =
				vecData[ uiRandomPoint ].minY +
				(vecData[ uiRandomPoint ].maxY - vecData[ uiRandomPoint ].minY) *
				(((tY)(rand() % 256 * 256)) / (256.0 * 256.0));
			
			vecRandDataPoints.push_back( randDataPoint );
		}
		cPolynom newPolynom;
		newPolynom.evalue( vecRandDataPoints );
		
		//evalueErrorMax
		const tY dNewPolynomError = newPolynom.evalueErrorMax( vecData,
			dActualPolynomError );
		
		if ( ( dNewPolynomError < dActualPolynomError ) || ( dActualPolynomError < 0.0 ) ){
			
			vecFactors = newPolynom.vecFactors;
			dActualPolynomError = dNewPolynomError;
		
#ifdef PRINT_INFOS_FIND_POLYNOM_RAND
			cout<<endl<<"Actual polynom (with error: "<< dActualPolynomError <<
				" in iteration "<< ulIteration <<"):"<<endl;
			print( cout );
#endif
		}
	}
	vecFactors = vecActualPolyFactors;
	
	return dActualPolynomError;
}


/**
 * This functions evalues the a good polynom which matches the given
 * range data vecInputData
 * The vector vecData is the sorted vector vecInputData.
 * for this a polynom which evalues a low error on the given data point
 * ranges is evalued.
 *
 * @see evalue()
 * @param vecInputData the data which the returend polynom should match
 * @param ulTimeNeed a value for the time, wich can be used to optimize
 * 	the result, the (additional) evaluation time will scale linear with
 * 	this factor
 * @return the factors of the evalued polynom in this polynom and
 * 	the error for the evalued polynom on the given data
 */
template<class tX, class tY>
	tY fib::algorithms::nD1::cPolynom<tX, tY>::evalueGoodPolynom(
		const vector< cDataPointRange< tX, tY> > & vecInputData,
		unsigned long ulTimeNeed ){
	
	vector< cDataPointRange< tX, tY> > vecData( vecInputData );
	sort( vecData.begin(), vecData.end() );
	
	//evalue the upper border
	cPolynomRange<tX, tY> lastRangePolynom;
	cPolynomRange<tX, tY> newRangePolynom;
	for ( unsigned int uiActualPolynomOrder = 1;
			uiActualPolynomOrder <= vecData.size();
			uiActualPolynomOrder++ ){
		//search for the first polynom with some degree of freedom
		newRangePolynom.evalue( vecData, uiActualPolynomOrder );
		if ( ! newRangePolynom.getRangeSizeSumIsNull() ){
			//first polynom with some degree of freedom
			break;
		}
		lastRangePolynom = newRangePolynom;
	}
	//choose from the two polynoms the one with the minimal error on the data
	
	//convert range polynoms to polynoms
	cPolynom<tX, tY> smalerPolynom;
	const size_t iSmalerPolynomFactors = lastRangePolynom.vecFactors.size();
	for ( size_t iActPolyFac = 0 ; iActPolyFac < iSmalerPolynomFactors;
			iActPolyFac++ ){
		smalerPolynom.vecFactors.push_back(
			lastRangePolynom.vecFactors[ iActPolyFac ].min );
	}
	
	//find good factors for the (bigger) range polynom
	const size_t uiBiggerPolynomOrder = newRangePolynom.vecFactors.size();
	vector< cLinearConstrainFix<tY> > vecOfInequationsOriginal( vecData.size(),
		cLinearConstrainFix<tY>( uiBiggerPolynomOrder, vecData.size() ) );
	vector< cRangeFactor<tY> > vecYRanges;
	const size_t iNumberOfDatapoints = vecData.size();
	for( size_t iActualDataPoint = 0; iActualDataPoint < iNumberOfDatapoints;
			iActualDataPoint++ ){
		
		//set the values for the x/ a_i factors
		const tY dX = vecData[ iActualDataPoint ].x;
		tY dFactor = ((tY)(1.0));
		for ( unsigned long uiActualFactor = 0; uiActualFactor < uiBiggerPolynomOrder;
				uiActualFactor++ ){
			
			vecOfInequationsOriginal[ iActualDataPoint ].
				vecFactors[ uiActualFactor ] = dFactor;
			dFactor *= dX;
		}
		//set the lower and upper y bounds
		vecOfInequationsOriginal[ iActualDataPoint ].vecBounderyFactors[ iActualDataPoint ] = 1.0;
		
		vecYRanges.push_back( cRangeFactor<tY>(
			vecData[ iActualDataPoint ].minY, vecData[ iActualDataPoint ].maxY ) );
	}
	vector< cRangeFactor<tY> > vecXRanges = newRangePolynom.vecFactors;
	
	pair< vector<tY>, tY> paRetBiggerPolyFactors = hillClimbingInRanges(
		vecOfInequationsOriginal, vecXRanges, vecYRanges, ulTimeNeed );
	
	const pair<unsigned long, tY> paSmalerPolynomError = smalerPolynom.evalueError( vecData );
	
#ifdef PRINT_INFOS
	cout<<endl<<"smaler polynom (Error="<< paSmalerPolynomError.second <<") :";
	smalerPolynom.print( cout );
	cout<<"bigger polynom (Error="<< paRetBiggerPolyFactors.second <<"):";
	cPolynom<tX, tY> biggerPolynomTmp;
	biggerPolynomTmp.vecFactors = paRetBiggerPolyFactors.first;
	biggerPolynomTmp.print( cout );
#endif
	
	if ( paRetBiggerPolyFactors.second < paSmalerPolynomError.second ){
		//return bigger polynom
		vecFactors = paRetBiggerPolyFactors.first;
		return paRetBiggerPolyFactors.second;
	}//else return smaler polynom
	vecFactors = smalerPolynom.vecFactors;
	return paSmalerPolynomError.second;
}


/**
 * This functions evalues a spline, which matches the given range data
 * vecInputData
 * The vector vecData is the sorted vector vecInputData.
 * The y value, to wich the spline evalues the x value, will be in the
 * bound of the range data point, so that:
 * 	vecData[i].minY <= spline( vecData[i].x ) <= vecData[i].maxY,
 * 	for i = 0 till n, with n <= vecData.size()
 * The first sorted n range data points will be matched by the spline.
 * The first sorted n+1'th data points can't be matched by a spline/polynom
 * with uiNumberOfParameters parameters.
 * The evalued spline (this polynom) will have the form:
 * 	y = vecFactors[ 0 ] + vecFactors[ 1 ] * x +
 * 	vecFactors[ 2 ] * x^2 + ... +
 * 	vecFactors[ uiNumberOfParameters - 1 ] *
 * 		x^(uiNumberOfParameters - 1)
 *
 * @see evalue()
 * @param vecInputData the data which the returend polynom should match
 * @param uiNumberOfParameters the number of parameters for the spline;
 * 	Don't choose this number to big, because the evaluation time will
 * 	grow exponentialy with this number. Even splines with 8
 * 	parameters will take some time.
 * @param uiMinBitsToStoreMantissa the minimal number of bits to store
 * 	the mantissa of the parameters, when the parameter is in the
 * 	form: mantissa * 2^exponent ;
 * 	the method will try to reduce the bits, to store a parameter of the
 * 	returned vector, to the uiMinBitsToStoreMantissa value;
 * 	if uiMinBitsToStoreMantissa is 0, no optimization for the mantissa
 * 	bits will be done
 * @param maxValue the maximum possible value in all parameters
 * 	the evalued polynom will allways have parameters vecFactors[i] with
 * 	-1 * maxValue <= vecFactors[i] <= maxValue for 0 <= i \< vecFactors.size()
 * @param ulMaxMemoryCost a number for the maximum memory cost this
 * 	method is allowed to use; if 0 the maximum memory cost is unbounded
 * @return the number n of data points vecData, which the spline matches;
 * 	the sorted data points vecData[0] to vecData[ return - 1 ] will be
 * 	matched by the spline
 */
template<class tX, class tY> unsigned long
	fib::algorithms::nD1::cPolynom<tX, tY>::evalueSpline(
		const vector< cDataPointRange< tX, tY> > & vecInputData,
		unsigned int uiNumberOfParameters,
		const unsigned int uiMinBitsToStoreMantissa,
		const tY maxValue, const unsigned long ulMaxMemoryCost ){

#ifdef DEBUG_C_POLYNOM
	cout<<"cPolynom<tX, tY>::evalueSpline( vecData, uiNumberOfParameters="<<
		uiNumberOfParameters<<", uiMinBitsToStoreMantissa="<<
		uiMinBitsToStoreMantissa<<", maxValue="<<maxValue<<
		", ulMaxMemoryCost="<<ulMaxMemoryCost<<" ) started"<<endl;
#endif
	if ( uiNumberOfParameters == 0 ){
		//can't create spline with 0 parameters, which match datapoints
		return 0;
	}
	if ( maxValue <= ((tY)(0.0)) ){
		//can't create spline with this maximum value
		return 0;
	}
	const unsigned long ulNumberOfDataPoints = vecInputData.size();
	
	if ( ulNumberOfDataPoints == 0 ){
		return 0;
	}
	
	vector< cDataPointRange< tX, tY> > vecData( vecInputData );
	sort( vecData.begin(), vecData.end() );
	
	unsigned long ulPointsAdded = 0;
	//create a empty hyperplane body
	cHyperplaneBody< tY > * pHyperplaneBody = NULL;
	if ( (256 * 256 * 256) < maxValue ){
		
		pHyperplaneBody = new cHyperplaneBodyFull< tY >( uiNumberOfParameters, maxValue );
	}else{
		pHyperplaneBody = new cHyperplaneBodySimple< tY >( uiNumberOfParameters, maxValue );
	}
	
	while ( ulPointsAdded < ulNumberOfDataPoints ){
		//for every range data point
		
		//create the inequiations for the range data point
		const pair< cInequation< tY >, cInequation< tY > >
			paIneqiuations = createInequiationsForRangePoint(
				vecData[ ulPointsAdded ], uiNumberOfParameters );
		
		//try to add the inequiations for the range data point
		bool bDataPointAdded = pHyperplaneBody->addInequiation(
			paIneqiuations.first );
//#define DEBUG_C_POLYNOM
#ifdef DEBUG_C_POLYNOM
		cout<<"Actual range data point ("<<vecData[ ulPointsAdded ].x<<
			","<<vecData[ ulPointsAdded ].minY<<" till "<<
			vecData[ ulPointsAdded ].maxY<<") "<<
			(bDataPointAdded?"added":"not added")<<", with inequiations:"<<endl;
		paIneqiuations.first.print( cout );
		paIneqiuations.second.print( cout );
#endif
#ifdef DEBUG_PRINT_HYPERBODY
		cout<<"new hyperbody after adding first inequiation:"<<endl;
		pHyperplaneBody->print( cout );
#endif
		if ( bDataPointAdded ){
			bDataPointAdded &= pHyperplaneBody->addInequiation(
				paIneqiuations.second );
		}
#ifdef DEBUG_C_POLYNOM
		cout<<"Actual range data point ("<<vecData[ ulPointsAdded ].x<<
			","<<vecData[ ulPointsAdded ].minY<<" till "<<
			vecData[ ulPointsAdded ].maxY<<") "<<
			(bDataPointAdded?"added":"not added")<<", with inequiations:"<<endl;
		paIneqiuations.first.print( cout );
		paIneqiuations.second.print( cout );
#endif
#ifdef DEBUG_PRINT_HYPERBODY
		cout<<"new hyperbody:"<<endl;
		pHyperplaneBody->print( cout );
#endif
		if ( ! bDataPointAdded ){
			/*if the inequiations couldn't be added
			-> done adding range data points*/
			break;
		}
		ulPointsAdded++;
#ifdef DEBUG_C_POLYNOM
		cout<<"Border points in hyperplane:"<<pHyperplaneBody->getNumberOfBorderPoints()<<endl;
#endif
		if ( ( ulMaxMemoryCost != 0) &&
				( ulMaxMemoryCost < pHyperplaneBody->getNumberOfBorderPoints() ) ){
			//the evaluation casts to much memory -> stop it
#ifdef DEBUG_C_POLYNOM
			cout<<"memory cost to higth"<<endl;
#endif
			break;
		}
	}
	if ( ulPointsAdded == 0 ){
#ifdef DEBUG_C_POLYNOM
		cout<<"no point added"<<endl;
#endif
		delete pHyperplaneBody;
		return 0;
	}
	
	//evalue the solution
#ifdef DEBUG_C_POLYNOM
	cout<<"extracting factors from the hyperbody"<<endl;
//#ifdef DEBUG_PRINT_HYPERBODY
	cout<<"actual hyperbody:"<<endl;
	pHyperplaneBody->print( cout );
//#endif
#endif
	vecFactors = pHyperplaneBody->getPointInBody( uiMinBitsToStoreMantissa );
	
	if ( vecFactors.empty() ){
		vecFactors.push_back( 0 );
	}
	
#ifdef DEBUG_C_POLYNOM
	cout<<"adding range data points wich fulfill this polynom"<<endl;
#endif
	//check if this polynom approximate more than the ulPointsAdded points
	while ( ulPointsAdded < ulNumberOfDataPoints ){
		//check if next data point is approximated by the polynom
		
		const tY dPolynomValue = evalue( vecData[ ulPointsAdded ].x );

		if ( dPolynomValue < vecData[ ulPointsAdded ].minY){
			//the actual point is not matched by the polynom
			break;
		}else if ( vecData[ ulPointsAdded ].maxY < dPolynomValue ){
			//the actual point is not matched by the polynom
			break;
		}/*else the actual point is matched by the polynom
		-> treat it as added*/
		ulPointsAdded++;
	}
#ifdef DEBUG_C_POLYNOM
	cout<<"cPolynom<tX, tY>::evalueSpline( vecData, uiNumberOfParameters="<<
		uiNumberOfParameters<<", uiMinBitsToStoreMantissa="<<
		uiMinBitsToStoreMantissa<<", maxValue="<<maxValue<<
		", ulMaxMemoryCost="<<ulMaxMemoryCost<<" ) done; point added: "<<ulPointsAdded<<endl;
#endif
	
	delete pHyperplaneBody;
	return ulPointsAdded;
}



#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING

/**
 * This functions evalues a spline, which matches all points of the
 * given range data vecData (if possible).
 * The y value, to wich the spline evalues the x value, will be in the
 * bound of the range data point, so that:
 * 	vecData[i].minY <= spline( vecData[i].x ) + error_i <= vecData[i].maxY,
 * 	with maxError <= sum error_i
 * 	for i = 0 till vecData.size()
 *
 * The evalued spline (this polynom) will have the form:
 * The evalued polynoms (@see cPolynom) will have the form:
 * 	y = vecFactors[ 0 ] + vecFactors[ 1 ] * x +
 * 	vecFactors[ 2 ] * x^2 + ... +
 * 	vecFactors[ uiNumberOfParameters - 1 ] *
 * 		x^(uiNumberOfParameters - 1)
 *
 * The method will iterativ increase the number of parameters for the
 * polynoms (from 1 to uiMaxNumberOfParameters) and will try to use
 * all of the given range points to find the polynoms.
 *
 * @see evalue()
 * @see sSpline::evalueSplineIterativFast()
 * @param vecInputData the data which the returend spline should match
 * @param uiMaxNumberOfParameters the number of parameters for the spline;
 * 	Don't choose this number to big, because the evaluation time will
 * 	grow exponentialy with this number. Even splines with 8
 * 	parameters will take some time.
 * @param maxValue the maximum possible value in all parameters
 * 	the evalued spline will allways have parameters vecFactors[i] with
 * 	-1 * maxValue <= vecFactors[i] <= maxValue for 0 <= i \< vecFactors.size()
 * @param maxError the maximal error for the spline to find;
 * 	the error on the interpolated spline for vecData will be equal or
 * 	less than maxError
 * @param maxErrorPerValue the maximal error for the spline to find on
 * 	one data point; the error on the interpolated spline for every data
 * 	point in vecData will be equal or less than maxErrorPerValue;
 * 	if maxErrorPerValue is 0 and maxError is not 0, maxErrorPerValue will
 * 	be set to maxError * 2 / vecInputData.size()
 * @param dWeightParameter a value for the weight of the parameters;
 * 	with this value greater 0 it will be searched for smaal parameter;
 * 	when searching for a solution the error is minimized and the
 * 	spline parameter will be multiplied with this value and also minimized;
 * 	when set to 1 a parameter increas of 1 is as bad as an error increas
 * 	of 1, when set to 0.01 parameter increas of 100 is as bad an error increas
 * 	of 1
 * @return the number n of data points vecData, which the spline matches;
 * 	the data points vecData[0] to vecData[ return - 1 ] will be
 * 	matched by the spline
 */
template<class tX, class tY> unsigned long fib::algorithms::nD1::cPolynom<tX, tY>::
	evalueSplineIterativFast(
		const vector< cDataPointRange< tX, tY> > & vecInputData,
		unsigned int uiMaxNumberOfParameters,
		const tY maxValue,
		const tY maxError,
		const tY maxErrorPerValue,
		const double dWeightParameter ){
	
#ifdef DEBUG_C_POLYNOM
	cout<<"cPolynom<tX, tY>::evalueSpline( vecInputData, uiMaxNumberOfParameters="<<
		uiMaxNumberOfParameters<<" , maxValue="<<maxValue<<
		", maxError="<<maxError<<" ,maxErrorPerValue="<<
		maxErrorPerValue<<" ) started "<<endl<<flush;
#endif
	if ( uiMaxNumberOfParameters == 0 ){
		//can't create spline with 0 parameters, which match datapoints
		return 0;
	}
	if ( maxValue <= ((tY)(0.0)) ){
		//can't create spline with this maximum value
		return 0;
	}
	if ( maxError < ((tY)(0.0)) ){
		//can't create spline with negativ maximum error
		return 0;
	}
	if ( maxErrorPerValue < ((tY)(0.0)) ){
		//can't create spline with negativ maximum error
		return 0;
	}
	const unsigned long ulNumberOfDataPoints = vecInputData.size();
	
	if ( ulNumberOfDataPoints == 0 ){
		return 0;
	}
	/*if maxErrorPerValue is 0 and maxError is not 0, maxErrorPerValue will
	be set to maxError / vecInputData.size()*/
	const double dMaxErrorPerValue = ( maxErrorPerValue != ((tY)(0.0)) ) ?
			maxErrorPerValue : ( maxError == ((tY)(0.0)) ) ? 0.0 :
				( (maxError * 2.0) / ((double)ulNumberOfDataPoints) );
	
	vector< cDataPointRange< tX, tY> > vecData( vecInputData );
	sort( vecData.begin(), vecData.end() );
	
	//for the indexs counting starts at 1, 0 stands for no data point
	//a good polynom is a polynom, which dos not exceed its share of the error
	/*index of the last data point for which a good polynom was found;
	init with 0 for: no good data point found jet*/
	unsigned long ulIndexLastGoodDataPoint = 0;
	
	//init LP parameters
	glp_smcp lpControlParameter;
	//init glp parameters with default parameters
	glp_init_smcp( & lpControlParameter );
	/*default parameters:
	lpControlParameter.meth = GLP_PRIMAL;
	lpControlParameter.pricing = GLP_PT_PSE;
	lpControlParameter.r_test  = GLP_RT_HAR;
	lpControlParameter.tol_bnd = 1e-7;
	lpControlParameter.tol_dj  = 1e-7;
	lpControlParameter.tol_piv = 1e-10;
	lpControlParameter.obj_ll  = -DBL_MAX;
	lpControlParameter.obj_ul  = +DBL_MAX;
	lpControlParameter.out_frq = 200;
	lpControlParameter.out_dly = 0;
	*/
	//output
#ifdef DEBUG_C_POLYNOM
	lpControlParameter.msg_lev = GLP_MSG_ALL; //(default: GLP MSG ALL)
#else
	lpControlParameter.msg_lev = GLP_OFF;  //= no output = glp_term_out( GLP_OFF );
#endif //DEBUG_C_POLYNOM
	//simplex iteration limit
	lpControlParameter.it_lim  = (100000000 < INT_MAX) ? 100000000 : INT_MAX;
	//time limit in  milli seconds
	lpControlParameter.tm_lim  = 10000;//=10 s ; default INT_MAX
	
	//presolver: disable because also non optimal solutions are needed
	lpControlParameter.presolve = GLP_OFF;
	
#ifdef DEBUG_C_POLYNOM
	cout<<endl<<"Trying to find a new polynom beginning at point "<<
		ulIndexLastGoodDataPoint<<" ."<<endl;
#endif
	
	/*the index of the data point, wich could not be integrated into the
	next polynom to generate*/
	unsigned long ulIndexToMuchDataPoint = ulNumberOfDataPoints + 1;
	
	/*the index of the last data point which should be integrated into the
	actual to generate polynom*/
	//step 1: (= ulNumberOfDataPoints - 1) try to find spline for all data points
	unsigned long ulActualIndexOfLastDataPoint = ulNumberOfDataPoints;
	
	cPolynom<tX, tY> actualPolynom;
	
	//if for the actual points a spline was found
	bool bSplineFound = false;
	
	//while next good polynom not found
	while ( true ){
		/* convert actual data points to glp problem;
		data points for actual polynom form 1 till ulActualIndexOfLastDataPoint*/
		
#ifdef DEBUG_C_POLYNOM
		cout<<endl<<"Creating linear program for "<<
			ulActualIndexOfLastDataPoint<<
			" data points (from index 1 to index "<<ulActualIndexOfLastDataPoint<<")."<<endl<<flush;
#endif
#ifdef FEATURE_GLPK_USE_MUTEX_LINAR_PROBLEM_SOLVING
	
#ifdef WINDOWS
		WaitForSingleObject( & mutexGlpkSolver, INFINITE);
#else //WINDOWS
		pthread_mutex_lock( & mutexGlpkSolver );
#endif //WINDOWS
		
#endif //FEATURE_GLPK_USE_MUTEX_LINAR_PROBLEM_SOLVING
		
		//create glp problem
		glp_prob * pLinearProblem = NULL;
		pLinearProblem = glp_create_prob();
		
		//set problem to minimize
		glp_set_obj_dir( pLinearProblem, GLP_MIN );
		
		/* Problem to solve:
			y_i = a_0 + a_1 * x_i + ... + a_n * x_i^2 +
					b_0 + b_1 * x_i + ... + b_n * x_i^2 + e_i + t_i
			with:
				0 =< a_p =< maxValue
				-maxValue =< b_p =< 0
			
			minimize: z = e_1 + ... + e_m - t_1 - ... - t_m +
				Ep * a_0 + ... + Ep * a_n - Ep * b_0 - ... - Ep * b_n
				wher Ep (= dWeightParameter) is a smaal value
			
			for data points ( { y_min =< y_i =< y_max }, x_i ) for i = 1 ... m
				( m = ulActualIndexOfLastDataPoint )
			wher n is the number of polynom factors and e_i are the positiv
			and t_i the negativ errors
			
			find: a_p and b_p with p = 0 ... n
			constrains:
				y_min =< y_i <= y_max
				0 =< e_i =< dMaxErrorPerValue
				-dMaxErrorPerValue =< t_i =< 0
			
			column = ( n + 1 ) * 2 + m * 2 (= for each a_p, b_p, e_i and t_i )
				= uiMaxNumberOfParameters * 2 + m * 2
			rows   = m (= for each data point)
		*/
	
		const unsigned long ulDataPointsToInclude = ulActualIndexOfLastDataPoint;
		
		glp_add_rows( pLinearProblem, ulDataPointsToInclude );
		//set y_i
		//index starting from 0 of the actual data point
		unsigned long ulIndexDataPoint = 0;
		for ( unsigned long ulActualRow = 1;
				ulActualRow <= ulDataPointsToInclude; ulActualRow++ ){
			
			//glp_set_row_name( pLinearProblem, ulActualRow, "y_ulActualRow" );
			const cDataPointRange< tX, tY> & actualRangeDataPoint =
				vecData[ ulIndexDataPoint ];
			ulIndexDataPoint++;
			
			glp_set_row_bnds( pLinearProblem, ulActualRow,
				( ( actualRangeDataPoint.minY != actualRangeDataPoint.maxY ) ?
					GLP_DB : GLP_FX ),
				actualRangeDataPoint.minY, actualRangeDataPoint.maxY );
		}
		
		const unsigned long uiNumberOfParameterColumns =
			uiMaxNumberOfParameters * 2;
		const unsigned long ulNumberOfColumns =
			uiNumberOfParameterColumns + ulDataPointsToInclude * 2;
		glp_add_cols( pLinearProblem, ulNumberOfColumns );
		
		//set a_p and b_p
		const double maxNegValue = ( maxValue == 0.0 ) ? 0.0 :
			( 0 - ((double)maxValue) );
		const double dNegWeightParameter = 0 - dWeightParameter;
		const int iValueBoundType = ( maxNegValue != maxValue ) ?
			GLP_DB : GLP_FX;
		for ( unsigned long ulActualCol = 1;
				ulActualCol <= uiNumberOfParameterColumns; ulActualCol++ ){
			
			//glp_set_col_name( pLinearProblem, 1, "a_(ulActualCol-1)" );
			glp_set_col_bnds( pLinearProblem, ulActualCol, iValueBoundType,
				0.0, maxValue );
			glp_set_obj_coef( pLinearProblem, ulActualCol, dWeightParameter );
			
			ulActualCol++;
			//glp_set_col_name( pLinearProblem, 1, "b_(ulActualCol-1)" );
			glp_set_col_bnds( pLinearProblem, ulActualCol, iValueBoundType,
				maxNegValue, 0.0 );
			glp_set_obj_coef( pLinearProblem, ulActualCol, dNegWeightParameter );
		}
		
		//set e_i and t_i
		const double maxNegErrorPerValue = ( dMaxErrorPerValue != 0.0 ) ?
			( 0.0 - dMaxErrorPerValue ) : 0.0;
		const int iErrorBoundType = ( dMaxErrorPerValue != 0.0 ) ?
			GLP_DB : GLP_FX;
		for ( unsigned long ulActualCol = uiNumberOfParameterColumns + 1;
				ulActualCol <= ulNumberOfColumns; ulActualCol++ ){
			//e_i
			//glp_set_col_name( pLinearProblem, ulActualCol, "e_(ulActualCol - uiMaxNumberOfParameters )" );
			glp_set_col_bnds( pLinearProblem, ulActualCol, iErrorBoundType,
				0.0, dMaxErrorPerValue );
			glp_set_obj_coef( pLinearProblem, ulActualCol, 1.0 );
			//t_i
			ulActualCol++;
			glp_set_col_bnds( pLinearProblem, ulActualCol, iErrorBoundType,
				maxNegErrorPerValue, 0.0 );
			glp_set_obj_coef( pLinearProblem, ulActualCol, -1.0 );
		}
		
		const unsigned long ulNumberOfFactors =
			ulDataPointsToInclude * ( uiNumberOfParameterColumns + 2 );
		/* = ulDataPointsToInclude * uiNumberOfParameterColumns +
				2 * ulDataPointsToInclude
			= number x_i factors for a_p and b_p + number e_i factors
			( for every x_i ther are ( 2 * uiMaxNumberOfParameters )
			factors)*/
		//index 0 not used
		int indexRow[ ulNumberOfFactors + 1 ];
		int indexColumn[ ulNumberOfFactors + 1 ];
		double factorX[ ulNumberOfFactors + 1 ];
		
		/*set x_i factors in:
			y_i = a_0 + a_1 * x_i + ... + a_n * x_i^2 +
					b_0 + b_1 * x_i + ... + b_n * x_i^2 + e_i + t_m */
		unsigned long ulActualIndex = 1;
		//index of the actual data point starting from 0
		ulIndexDataPoint = 0;
		for ( unsigned long ulActualRow = 1;
				ulActualRow <= ulDataPointsToInclude; ulActualRow++ ){
			
#ifdef DEBUG_C_POLYNOM
			cout<<endl<<"(y_"<<ulIndexDataPoint<<" = "<<
				vecData[ ulIndexDataPoint ].minY<<" ... "<<
				vecData[ ulIndexDataPoint ].maxY<<") = ";
#endif
			const double actualXValue =
				((double)(vecData[ ulIndexDataPoint ].x));
			double actualXFactor = 1.0;
			ulIndexDataPoint++;
			//for every parameter
			for ( unsigned long ulActualCol = 1;
					ulActualCol <= uiNumberOfParameterColumns; ulActualCol++ ){
				
				indexRow[ ulActualIndex ]    = ulActualRow;
				indexColumn[ ulActualIndex ] = ulActualCol;
				factorX[ ulActualIndex ]     = actualXFactor;
				ulActualIndex++;
				
				ulActualCol++;
				indexRow[ ulActualIndex ]    = ulActualRow;
				indexColumn[ ulActualIndex ] = ulActualCol;
				factorX[ ulActualIndex ]     = actualXFactor;
				ulActualIndex++;
			
#ifdef DEBUG_C_POLYNOM
				cout<<"a_"<<((ulActualCol-1)/2)<<" * "<<actualXFactor<<
					" - b_"<<((ulActualCol-1)/2)<<" * "<<actualXFactor<<" + ";
#endif
				actualXFactor *= actualXValue;
			}
		}
		/*set e_i factors and t_i factors to 1 in
			y_i = a_0 + a_1 * x_i + ... + a_n * x_i^2 +
					b_0 + b_1 * x_i + ... + b_n * x_i^2 + e_i + t_m */
		unsigned long ulActualCol = uiNumberOfParameterColumns + 1;
		for ( unsigned long ulActualRow = 1;
				ulActualRow <= ulDataPointsToInclude; ulActualRow++ ){
				//e_i
				indexRow[ ulActualIndex ]    = ulActualRow;
				indexColumn[ ulActualIndex ] = ulActualCol;
				factorX[ ulActualIndex ]     = 1.0;
				ulActualIndex++;
				ulActualCol++;
				//t_i
				indexRow[ ulActualIndex ]    = ulActualRow;
				indexColumn[ ulActualIndex ] = ulActualCol;
				factorX[ ulActualIndex ]     = 1.0;
				ulActualIndex++;
				ulActualCol++;
		}
		//store the data into the lp problem
		glp_load_matrix( pLinearProblem, ulNumberOfFactors,
			indexRow, indexColumn, factorX );
		
#ifdef DEBUG_C_POLYNOM
		cout<<endl<<"start solving problem with "<<
				glp_get_num_rows( pLinearProblem )<<" rows and "<<
				glp_get_num_cols( pLinearProblem )<<" columns"<<endl<<flush;
#endif
		// solve problem with simplex glp solver
		const int uiResultSimplex = glp_simplex( pLinearProblem, & lpControlParameter );
		
		
		const int iProblemStatus = glp_get_status( pLinearProblem );
		
#ifdef DEBUG_C_POLYNOM
		cout<<endl<<"LP solver returned;"<<endl<<flush;
		if ( ( iProblemStatus == GLP_OPT ) ||
				( iProblemStatus == GLP_FEAS ) ){
			cout<<"   the solution is OK"<<endl<<flush;
		}
		switch ( iProblemStatus ){
			case GLP_OPT:    cout<<"solution is optimal"<<endl;break;
			case GLP_FEAS:   cout<<"solution is feasible"<<endl;break;
			case GLP_INFEAS: cout<<"solution is infeasible"<<endl;break;
			case GLP_NOFEAS: cout<<"problem has no feasible solution"<<endl;break;
			case GLP_UNBND:  cout<<"problem has unbounded solutionl"<<endl;break;
			case GLP_UNDEF:  cout<<"solution is undefined"<<endl;break;
			default: cout<<"problem status unknown"<<endl;break;
		}
#endif
		
		if ( ( ( uiResultSimplex == 0 ) || //solution found
					( uiResultSimplex == GLP_EITLIM ) || //stop because of iteration limit -> check error
					( uiResultSimplex == GLP_ETMLIM ) )  //stop because of time limit -> check error
				&&
				( ( iProblemStatus == GLP_OPT ) || //optimal solution found
					( iProblemStatus == GLP_FEAS )  //check non optimal solution also
				) ){
			//The LP problem instance has been successfully solved or limit reached.
			/*GLP_EITLIM: The search was prematurely terminated, because the
				simplex iteration limit has been exceeded.
			GLP_ETMLIM: The search was prematurely terminated, because the
				time limit has been exceeded.*/
#ifdef DEBUG_C_POLYNOM
			switch ( uiResultSimplex ){
				case 0:   cout<<endl<<"solution found; evalue actual error"<<endl;break;
				case GLP_EITLIM: cout<<endl<<"iteration limit reached; evalue actual error"<<endl;break;
				case GLP_ETMLIM: cout<<endl<<"time limit reached; evalue actual error"<<endl;break;
				default: cout<<"solver result status unknown (uiResultSimplex="<<uiResultSimplex<<")"<<endl;break;
			}
#endif
			//get result of the solver
			//evalue actual error
			double dErrorSumNewPolynom = 0.0;
			bool bErrorOk = true;
			
			const double dMaxErrorForSpline = ((double)maxError) *
				( ((double)ulActualIndexOfLastDataPoint) /
					((double)ulNumberOfDataPoints) );
			
			for ( unsigned long ulActualCol = uiNumberOfParameterColumns + 1;
					ulActualCol <= ulNumberOfColumns; ulActualCol++ ){
				
				const double dErrorActualValue =
					glp_get_col_prim( pLinearProblem, ulActualCol );
				
				const double dAbsErrorActualValue = ( dErrorActualValue < 0.0 ) ?
					( 0.0 - dErrorActualValue ) : dErrorActualValue;
				
				dErrorSumNewPolynom += dAbsErrorActualValue;
				
				if ( ( dMaxErrorForSpline < dErrorSumNewPolynom ) ||
						( dMaxErrorPerValue < dAbsErrorActualValue ) ){
					//error to great
#ifdef DEBUG_C_POLYNOM
					cout<<endl<<"Dismiss found polynom, error to great: "<<
						"dErrorSumNewPolynom="<<dErrorSumNewPolynom<<" (maxError="<<
						maxError<<") dAbsErrorActualValue="<<dAbsErrorActualValue<<
						" (dMaxErrorPerValue="<<dMaxErrorPerValue<<")"<<endl;
#endif
					bErrorOk = false;
					break;
				}
			}
			
#ifdef DEBUG_C_POLYNOM
			cout<<endl<<"error sum: "<<dErrorSumNewPolynom<<endl;
#endif
			if ( bErrorOk ){
				
				bSplineFound = true;
				//set polynom factors
				actualPolynom.vecFactors.clear();
				for ( unsigned long ulActualCol = 1;
						ulActualCol <= uiNumberOfParameterColumns;
						ulActualCol += 2 ){
					
					const double dActualFactor =
						glp_get_col_prim( pLinearProblem, ulActualCol ) +
						glp_get_col_prim( pLinearProblem, ulActualCol + 1 );
					
					actualPolynom.vecFactors.push_back( dActualFactor );
				}
				//remove all higher polynom factors which are 0
				while ( ( 1 < actualPolynom.vecFactors.size() ) && //don't remove constant
						( actualPolynom.vecFactors.back() == 0.0 ) ){
					
					actualPolynom.vecFactors.pop_back();
				}
				
#ifdef DEBUG_C_POLYNOM
				cout<<endl<<"Polynom OK (error sum "<<dErrorSumNewPolynom<<") :"<<endl;
				actualPolynom.print( cout );
#endif
			}
		}else{//LP problem could not be solved
#ifdef DEBUG_C_POLYNOM
			cout<<endl<<"LP problem could not be solved"<<endl;
#endif
			/* possible returns:
			GLP_EBADB: Unable to start the search, because the initial basis speci-
			fied in the problem object is invalid—the number of basic
			(auxiliary and structural) variables is not the same as the
			number of rows in the problem object.
			GLP_ESING: Unable to start the search, because the basis matrix corre-
			sponding to the initial basis is singular within the working
			precision.
			GLP_ECOND: Unable to start the search, because the basis matrix cor-
			responding to the initial basis is ill-conditioned, i.e. its
			condition number is too large.
			GLP_EBOUND: Unable to start the search, because some double-bounded
			(auxiliary or structural) variables have incorrect bounds.
			GLP_EFAIL: The search was prematurely terminated due to the solver
			failure.
			GLP_EOBJLL: The search was prematurely terminated, because the ob-
			jective function being maximized has reached its lower
			limit and continues decreasing (the dual simplex only).
			GLP_EOBJUL: The search was prematurely terminated, because the ob-
			jective function being minimized has reached its upper
			limit and continues increasing (the dual simplex only).
			GLP_ENOPFS: The LP problem instance has no primal feasible solution
			(only if the LP presolver is used).
			GLP_ENODFS: The LP problem instance has no dual feasible solution
			(only if the LP presolver is used).
			*/
			bSplineFound = false;
		}
		//delete problem instance
		glp_delete_prob( pLinearProblem);
#ifdef FEATURE_GLPK_USE_MUTEX_LINAR_PROBLEM_SOLVING
		
#ifdef WINDOWS
		ReleaseMutex( & mutexGlpkSolver );
#else //WINDOWS
		pthread_mutex_unlock( & mutexGlpkSolver );
#endif //WINDOWS
		
#endif //FEATURE_GLPK_USE_MUTEX_LINAR_PROBLEM_SOLVING
		
		
		if ( bSplineFound ){
			//last error is not greater as the max error -> add data points
			/* if for the actual points a good spline was found
			-> try to find spline for data points till the middle of actual data
			point and the last data points for wich not a good spline was found */
#ifdef DEBUG_C_POLYNOM
			cout<<endl<<"Found polynom acepted, for data points till index: "<<
				ulActualIndexOfLastDataPoint<<endl;
#endif
			ulIndexLastGoodDataPoint = ulActualIndexOfLastDataPoint;
			
			const unsigned long ulDeltaBetweanLastGoodAndToMuch =
				ulIndexToMuchDataPoint - ulIndexLastGoodDataPoint;
			
			if ( ulDeltaBetweanLastGoodAndToMuch <= 1 ){
				/*no data points between last good and to much
				-> can't find more data points -> stop evaluation*/
#ifdef DEBUG_C_POLYNOM
				cout<<endl<<"no data points between last good and to much "<<
					"-> can't find more data points -> stop evaluation"<<endl;
#endif
				break;
			}
			
			ulActualIndexOfLastDataPoint += ulDeltaBetweanLastGoodAndToMuch / 2;
		}else{/*if no spline found or error is to great on actual data points
			-> reduce number of data points for the spline
			-> try to find spline for data points till the middle of actual data
			point and the last data points for wich a good spline was found */
#ifdef DEBUG_C_POLYNOM
			cout<<endl<<"found polynom not acepted, for data points till index: "<<
				ulActualIndexOfLastDataPoint<<endl;
#endif
			ulIndexToMuchDataPoint = ulActualIndexOfLastDataPoint;
			
			const unsigned long ulDeltaBetweanLastGoodAndToMuch =
				ulIndexToMuchDataPoint - ulIndexLastGoodDataPoint;
				
			if ( ulDeltaBetweanLastGoodAndToMuch <= 1 ){
				/*no data points between last good and to much
				-> can't omit more data points -> stop evaluation*/
#ifdef DEBUG_C_POLYNOM
				cout<<endl<<"no data points between last good and to much "<<
					"-> can't omit more data points -> stop evaluation"<<endl;
#endif
				break;
			}
			
			ulActualIndexOfLastDataPoint -= ulDeltaBetweanLastGoodAndToMuch / 2;
		}
		
	}//end while polynom not found
	
	if ( ! actualPolynom.vecFactors.empty() ){
		//add last found polynom
#ifdef DEBUG_C_POLYNOM
		cout<<endl<<"add last found polynom:"<<endl;
		actualPolynom.print( cout );
#endif
		vecFactors = actualPolynom.vecFactors;
	}//else keep old polynom
#ifdef DEBUG_C_POLYNOM
	else{
		//warning: no new spline found -> no new data points found
		cout<<endl<<"Warning: no new data points / spline found"<<endl;
	}
#endif
	
#ifdef DEBUG_C_POLYNOM
	cout<<"actual polynom: ";
	print( cout );
	cout<<"cPolynom<tX, tY>::evalueSpline( vecInputData, uiMaxNumberOfParameters="<<
		uiMaxNumberOfParameters<<" , maxValue="<<maxValue<<
		", maxError="<<maxError<<" ,dMaxErrorPerValue="<<
		dMaxErrorPerValue<<" ) done; points matched: "<<(ulIndexLastGoodDataPoint + 1)<<endl;
#endif
	return ulIndexLastGoodDataPoint;
}


#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING


/**
 * This functions evalues a spline, which matches the given range data
 * vecData.
 * The y value, to wich the spline evalues the x value, will be in the
 * bound of the range data point, so that:
 * 	vecData[i].minY <= spline( vecData[i].x ) <= vecData[i].maxY,
 * 	for i = 0 till n, with n <= vecData.size()
 * The first sorted n range data points will be matched by the spline.
 * The first sorted n+1'th data points can't be matched by a spline/polynom
 * with uiNumberOfParameters parameters.
 * The evalued spline (this polynom) will have the form:
 * 	y = vecFactors[ 0 ] + vecFactors[ 1 ] * x +
 * 	vecFactors[ 2 ] * x^2 + ... +
 * 	vecFactors[ uiNumberOfParameters - 1 ] *
 * 		x^(uiNumberOfParameters - 1)
 *
 * The method should give the same result as evalueSpline() but faster.
 * It will iterativ increase the number of parameters for the spline
 * (from 1 to uiMaxNumberOfParameters) and will try not to use all of
 * the given range data points to find the polynom.
 *
 * @see evalue()
 * @see evalueSpline()
 * @param vecInputData the data which the returend polynom should match
 * @param uiMaxNumberOfParameters the number of parameters for the spline;
 * 	Don't choose this number to big, because the evaluation time will
 * 	grow exponentialy with this number. Even splines with 8
 * 	parameters will take some time.
 * @param uiMinBitsToStoreMantissa the minimal number of bits to store
 * 	the mantissa of the parameters, when the parameter is in the
 * 	form: mantissa * 2^exponent ;
 * 	the method will try to reduce the bits, to store a parameter of the
 * 	returned vector, to the uiMinBitsToStoreMantissa value;
 * 	if uiMinBitsToStoreMantissa is 0, no optimization for the mantissa
 * 	bits will be done
 * @param maxValue the maximum possible value in all parameters
 * 	the evalued polynom will allways have parameters vecFactors[i] with
 * 	-1 * maxValue <= vecFactors[i] <= maxValue for 0 <= i \< vecFactors.size()
 * @param maxError the maximal error for the polynom to find;
 * 	the error on the interpolated polynom for vecData will be equal or
 * 	less than maxError
 * @param ulMaxMemoryCost a number for the maximum memory cost this
 * 	method is allowed to use; if 0 the maximum memory cost is unbounded
 * @return the number n of data points vecData, which the spline matches;
 * 	the sorted data points vecData[0] to vecData[ return - 1 ] will be
 * 	matched by the spline
 */
template<class tX, class tY> unsigned long fib::algorithms::nD1::cPolynom<tX, tY>::
	evalueSplineIterativFast(
		const vector< cDataPointRange< tX, tY> > & vecInputData,
		unsigned int uiMaxNumberOfParameters,
		const unsigned int uiMinBitsToStoreMantissa,
		const tY maxValue,
		const tY maxError,
		const unsigned long ulMaxMemoryCost ){
	
	
#ifdef DEBUG_C_POLYNOM
	cout<<"cPolynom<tX, tY>::evalueSplineIterativFast( vecData, uiMaxNumberOfParameters="<<
		uiMaxNumberOfParameters<<", uiMinBitsToStoreMantissa="<<
		uiMinBitsToStoreMantissa<<", maxValue="<<maxValue<<
		", maxError="<<maxError<<" ,ulMaxMemoryCost="<<
		ulMaxMemoryCost<<" ) started "<<endl;
#endif
	if ( uiMaxNumberOfParameters == 0 ){
		//can't create spline with 0 parameters, which match datapoints
		return 0;
	}
	if ( maxValue <= ((tY)(0.0)) ){
		//can't create spline with this maximum value
		return 0;
	}
	if ( maxError < ((tY)(0.0)) ){
		//can't create spline with negativ maximum error
		return 0;
	}
	const unsigned long ulNumberOfDataPoints = vecInputData.size();
	
	if ( ulNumberOfDataPoints == 0 ){
		return 0;
	}

	vector< cDataPointRange< tX, tY> > vecData( vecInputData );
	sort( vecData.begin(), vecData.end() );
	
	/*map with the last errors for the to approximate range data points;
	Elements:
		- error for the range data point
		- the range data point*/
	multimap< tY, const cDataPointRange< tX, tY > * > mmapActualPointErrors;
	tY actualErrorSum = 0;
	
	set< const cDataPointRange< tX, tY > * > setPointsIntegratedLastTime;
	
	unsigned int uiNumberOfActualParameters = 0;
	
	cPolynom<tX, tY> actualPolynom;
	
	unsigned long ulNumberOfActualPoints = vecData.size();
		
	cPolynom<tX, tY> lastCorrectPolynom;
	lastCorrectPolynom.vecFactors.push_back( 0 );
	unsigned long ulNumberOfMaxPointsMatched = 0;
	unsigned long ulFirstPointNotMatchebel = vecData.size();
	
	cHyperplaneBody< tY > * pHyperplaneBody = NULL;
			
	//while polynom not found
	bool bStopEvaluation = false;
	while ( ! bStopEvaluation ){
		/*
		- first try to increase number of parameters till all points matched
		- if not all actual points matched by the polynom:
			reduce number of actual points, till all are matched
		*/
		
		vector< const cDataPointRange< tX, tY > * > vecPointsToAdd;
		
		if ( uiNumberOfActualParameters < uiMaxNumberOfParameters ){
		//increase number of parameters
			uiNumberOfActualParameters++;
#ifdef DEBUG_C_POLYNOM
			cout<<"increasing number of parameters to "<<uiNumberOfActualParameters<<endl;
#endif
			//create a empty hyperplane body
			if ( pHyperplaneBody ){
				delete pHyperplaneBody;
			}
			if ( (256 * 256 * 256) < maxValue ){
				
				pHyperplaneBody = new cHyperplaneBodyFull< tY >(
					uiNumberOfActualParameters, maxValue );
			}else{
				pHyperplaneBody = new cHyperplaneBodySimple< tY >(
					uiNumberOfActualParameters, maxValue );
			}
			
			const unsigned long ulPointsToInitialIntegrate =
				(2 * uiNumberOfActualParameters + 3);
			if ( ( uiNumberOfActualParameters == 1 ) ||
					( setPointsIntegratedLastTime.size() <= ulPointsToInitialIntegrate ) ){
				/*if first iteration or less than ulPointsToInitialIntegrate
				points integrated in the last iteration:
					- evalue the first 2 * uiActualNumberOfParameters + 3 points to
					approximate (the point at the begin of the to approximate vector
					of range data points, the one at the end and points in the middle
					of the biggest intervalls betwean choosen points)*/
#ifdef DEBUG_C_POLYNOM
				cout<<"evaluing points to integrate at the start"<<endl;
#endif
				set< size_t > setPointToAddIndexes;
				vecPointsToAdd.push_back( &( vecData.front() ) );
				setPointToAddIndexes.insert( 0 );
				if ( 1 < vecData.size() ){
					vecPointsToAdd.push_back( &( vecData.back() ) );
					setPointToAddIndexes.insert( vecData.size() - 1 );
					
					while ( vecPointsToAdd.size() < ulPointsToInitialIntegrate ){
						
						bool bPointAdded = false;
						set< size_t > setPointToAddIndexesNew =
							setPointToAddIndexes;
						
						for ( set< size_t >::const_iterator
								itrIndex = setPointToAddIndexes.begin();
								itrIndex != setPointToAddIndexes.end(); itrIndex++ ){
							
							set< size_t >::const_iterator itrIndexNext = itrIndex;
							itrIndexNext++;
							if ( itrIndexNext == setPointToAddIndexes.end() ){
								//end of set reached -> done
								break;
							}
							const size_t uiToAddIndex = ( (*itrIndex) + (*itrIndexNext) ) / 2;
							if ( setPointToAddIndexesNew.find( uiToAddIndex ) ==
									setPointToAddIndexesNew.end()  ){
								//the index was not added befor
								bPointAdded = true;
								vecPointsToAdd.push_back( &( vecData[ uiToAddIndex ] ) );
								setPointToAddIndexesNew.insert( uiToAddIndex );
							}
						}
						if ( ! bPointAdded ){
							break;
						}
						setPointToAddIndexes = setPointToAddIndexesNew;
					}
				}
			}else{/*not first iteration:
				- take the points wich wher integrated in the last hyperbody to
				reduce the error and create the spline*/
#ifdef DEBUG_C_POLYNOM
				cout<<"using points, wich wher integrated in the last hyperbody to integrate at the start"<<endl;
#endif
				vecPointsToAdd = vector< const cDataPointRange< tX, tY > * >(
					setPointsIntegratedLastTime.begin(), setPointsIntegratedLastTime.end() );
			}
			//fill mmapActualPointErrors
			set< const cDataPointRange< tX, tY > * > setPointsToAdd(
				vecPointsToAdd.begin(), vecPointsToAdd.end() );
			mmapActualPointErrors.clear();
			for ( size_t uiActualDataPoint = 0;
					uiActualDataPoint < ulNumberOfActualPoints; uiActualDataPoint++ ){
				
				const cDataPointRange< tX, tY > * pActualDataPoint =
					&( vecData[ uiActualDataPoint ] );
				
				if ( setPointsToAdd.find( pActualDataPoint ) ==
						setPointsToAdd.end() ){
					//point not to add on default -> add points to the error points
					mmapActualPointErrors.insert( make_pair( 0, pActualDataPoint ) );
				}
			}
			setPointsIntegratedLastTime.clear();
			
		}else if ( maxError < actualErrorSum ){
			
			ulFirstPointNotMatchebel = ulNumberOfActualPoints;
			//decrase number of actual points
			unsigned long ulDeltaPoints =
				(ulNumberOfActualPoints - ulNumberOfMaxPointsMatched) / 2;
			if ( ulDeltaPoints == 0 ){
				ulDeltaPoints = 1;
			}
#ifdef DEBUG_C_POLYNOM
			cout<<"error to great on last iteration -> decrase number of actual points from "<<
				ulNumberOfActualPoints<<" to "<<(ulNumberOfActualPoints - ulDeltaPoints)<<endl;
#endif
			ulNumberOfActualPoints -= ulDeltaPoints;
			
			if ( ulNumberOfActualPoints < 1 ){
				bStopEvaluation = true;
				break;
			}
			if ( ulNumberOfActualPoints <= ulNumberOfMaxPointsMatched ){
				//can't match more points
				break;
			}
			//create a empty hyperplane body
			if ( pHyperplaneBody ){
				delete pHyperplaneBody;
			}
			if ( (256 * 256 * 256) < maxValue ){
				
				pHyperplaneBody = new cHyperplaneBodyFull< tY >(
					uiNumberOfActualParameters, maxValue );
			}else{
				pHyperplaneBody = new cHyperplaneBodySimple< tY >(
					uiNumberOfActualParameters, maxValue );
			}
			
			/*evalue the first 2 * uiActualNumberOfParameters + 3 points to
			approximate (the point at the begin of the to approximate vector
			of range data points, the one at the end and points in the middle
			of the biggest intervalls betwean choosen points)*/
			set< size_t > setPointToAddIndexes;
			vecPointsToAdd.push_back( &( vecData.front() ) );
			setPointToAddIndexes.insert( 0 );
			if ( 1 < ulNumberOfActualPoints ){
				vecPointsToAdd.push_back( &( vecData[ ulNumberOfActualPoints - 1 ] ) );
				setPointToAddIndexes.insert( ulNumberOfActualPoints - 1 );
				
				const unsigned long ulPointsToInitialIntegrate =
					(2 * uiNumberOfActualParameters + 3);
				while ( vecPointsToAdd.size() < ulPointsToInitialIntegrate ){
					
					bool bPointAdded = false;
					set< size_t > setPointToAddIndexesNew =
						setPointToAddIndexes;
					
					for ( set< size_t >::const_iterator
							itrIndex = setPointToAddIndexes.begin();
							itrIndex != setPointToAddIndexes.end(); itrIndex++ ){
						
						set< size_t >::const_iterator itrIndexNext = itrIndex;
						itrIndexNext++;
						if ( itrIndexNext == setPointToAddIndexes.end() ){
							//end of set reached -> done
							break;
						}
						const size_t uiToAddIndex = ( (*itrIndex) + (*itrIndexNext) ) / 2;
						if ( setPointToAddIndexesNew.find( uiToAddIndex ) ==
								setPointToAddIndexesNew.end()  ){
							//the index was not added befor
							bPointAdded = true;
							vecPointsToAdd.push_back( &( vecData[ uiToAddIndex ] ) );
							setPointToAddIndexesNew.insert( uiToAddIndex );
						}
					}
					if ( ! bPointAdded ){
						break;
					}
					setPointToAddIndexes = setPointToAddIndexesNew;
				}
			}
			//fill mmapActualPointErrors
			set< const cDataPointRange< tX, tY > * > setPointsToAdd(
				vecPointsToAdd.begin(), vecPointsToAdd.end() );
			mmapActualPointErrors.clear();
			for ( size_t uiActualDataPoint = 0;
					uiActualDataPoint < ulNumberOfActualPoints; uiActualDataPoint++ ){
				
				const cDataPointRange< tX, tY > * pActualDataPoint =
					&( vecData[ uiActualDataPoint ] );
				
				if ( setPointsToAdd.find( pActualDataPoint ) ==
						setPointsToAdd.end() ){
					//point not to add on default -> add points to the error points
					mmapActualPointErrors.insert( make_pair( 0, pActualDataPoint ) );
				}
			}
			setPointsIntegratedLastTime.clear();
		
		}else{/*if last actual points wher all matched
			-> increase number of actual points*/
			unsigned long ulDeltaPoints =
				(ulFirstPointNotMatchebel - ulNumberOfActualPoints) / 2;
			if ( ulDeltaPoints == 0 ){
				ulDeltaPoints = 1;
			}
			const unsigned long ulNumberOfOldActualPoints = ulNumberOfActualPoints;
			ulNumberOfActualPoints += ulDeltaPoints;
#ifdef DEBUG_C_POLYNOM
			cout<<"in last actual points wher all matched -> increase number of actual points from "<<
				ulNumberOfOldActualPoints<<" to "<<ulNumberOfActualPoints<<endl;
#endif
			if ( ulFirstPointNotMatchebel <= ulNumberOfActualPoints ){
				//can't match more points
				break;
			}
			/*add points to match
			-> enlarge mmapActualPointErrors to actual points*/
			for ( size_t uiActualDataPoint = ulNumberOfOldActualPoints;
					uiActualDataPoint < ulNumberOfActualPoints;
					uiActualDataPoint++ ){
				
				const tY dPolynomValue = actualPolynom.evalue( vecData[ uiActualDataPoint ].x );
				
				tY errorOfActualPoint = 0;
				if ( dPolynomValue < vecData[ uiActualDataPoint ].minY ){
					//the actual point is not matched by the polynom
					errorOfActualPoint = vecData[ uiActualDataPoint ].minY - dPolynomValue;
					actualErrorSum += errorOfActualPoint;
					
				}else if ( vecData[ uiActualDataPoint ].maxY < dPolynomValue ){
					//the actual point is not matched by the polynom
					errorOfActualPoint = dPolynomValue - vecData[ uiActualDataPoint ].maxY;
					actualErrorSum += errorOfActualPoint;
				}
				
				mmapActualPointErrors.insert( make_pair( errorOfActualPoint,
					&( vecData[ uiActualDataPoint ] ) ) );
			}
		}
		
		//add vecPointsToAdd points to match to hyperbody
		bool bPointsNotAdded = false;
		if ( ! vecPointsToAdd.empty() ){
#ifdef DEBUG_C_POLYNOM
			cout<<"add vecPointsToAdd points to match to hyperbody"<<endl;
#endif
			for ( typename vector< const cDataPointRange< tX, tY > * >::const_iterator
					itrDataPoint = vecPointsToAdd.begin();
					itrDataPoint != vecPointsToAdd.end(); itrDataPoint++ ){
				//for every range data point
				
				//create the inequiations for the range data point
				const pair< cInequation< tY >, cInequation< tY > >
					paIneqiuations = createInequiationsForRangePoint(
						(**itrDataPoint), uiNumberOfActualParameters );
				
				//try to add the inequiations for the range data point
				bool bDataPointAdded = pHyperplaneBody->addInequiation(
					paIneqiuations.first );
#ifdef DEBUG_C_POLYNOM
				cout<<"Actual range data point ("<<(**itrDataPoint).x<<
					","<<(**itrDataPoint).minY<<" till "<<
					(**itrDataPoint).maxY<<") "<<
					(bDataPointAdded?"added":"not added")<<", with inequiations:"<<endl;
				paIneqiuations.first.print( cout );
				paIneqiuations.second.print( cout );
#endif
#ifdef DEBUG_PRINT_HYPERBODY
				cout<<"new hyperbody after adding first inequiation:"<<endl;
				pHyperplaneBody->print( cout );
#endif
				if ( bDataPointAdded ){
					bDataPointAdded &= pHyperplaneBody->addInequiation(
						paIneqiuations.second );
#ifdef DEBUG_C_POLYNOM
					cout<<"Actual range data point ("<<(**itrDataPoint).x<<
						","<<(**itrDataPoint).minY<<" till "<<
						(**itrDataPoint).maxY<<") "<<
						(bDataPointAdded?"added":"not added")<<", with inequiations:"<<endl;
					paIneqiuations.first.print( cout );
					paIneqiuations.second.print( cout );
#endif
#ifdef DEBUG_PRINT_HYPERBODY
					cout<<"new hyperbody:"<<endl;
					pHyperplaneBody->print( cout );
#endif
				}
				if ( ! bDataPointAdded ){
					/*if the inequiations couldn't be added
					-> done adding range data points*/
					bPointsNotAdded = true;
					break;
				}
				setPointsIntegratedLastTime.insert( *itrDataPoint );
#ifdef DEBUG_C_POLYNOM
				cout<<"Border points in hyperplane: "<<pHyperplaneBody->getNumberOfBorderPoints()<<endl;
#endif
				if ( ( ulMaxMemoryCost != 0) &&
						( ulMaxMemoryCost < pHyperplaneBody->getNumberOfBorderPoints() ) ){
					//the evaluation casts to much memory -> stop it
#ifdef DEBUG_C_POLYNOM
					cout<<"memory cost to higth"<<endl;
#endif
					bStopEvaluation = true;
					break;
				}
			}
			if ( bStopEvaluation ){
				break;
			}
			//evalue error for remaining points
			actualPolynom.vecFactors = pHyperplaneBody->getPointInBody( uiMinBitsToStoreMantissa );
			
			if ( actualPolynom.vecFactors.empty() ){
				actualPolynom.vecFactors.push_back( 0 );
			}
			
			actualErrorSum = 0;
			mmapActualPointErrors.clear();
			unsigned long ulMatchedPoints = 0;
			//check if this polynom approximate more than the ulPointsAdded points
			for ( size_t uiActualPoint = 0;
					uiActualPoint < ulNumberOfActualPoints; uiActualPoint++ ){
				//check if next data point is approximated by the polynom
				const cDataPointRange< tX, tY > & dataPoint =
					vecData[ uiActualPoint ];
				
				const tY dPolynomValue = actualPolynom.evalue( dataPoint.x );
		
				tY errorOfActualPoint = 0;
				if ( dPolynomValue < dataPoint.minY ){
					//the actual point is not matched by the polynom
					errorOfActualPoint = dataPoint.minY - dPolynomValue;
					actualErrorSum += errorOfActualPoint;
					
				}else if ( dataPoint.maxY < dPolynomValue ){
					//the actual point is not matched by the polynom
					errorOfActualPoint = dPolynomValue - dataPoint.maxY;
					actualErrorSum += errorOfActualPoint;
				}
				if ( actualErrorSum <= maxError ){
					//the actual point is matched by the polynom
					ulMatchedPoints++;
				}//else the actual point isn't matched by the polynom
				if ( ( errorOfActualPoint != 0 ) &&
						( setPointsIntegratedLastTime.find( & dataPoint ) ==
							setPointsIntegratedLastTime.end() ) ){
					//map to points to check for error
					mmapActualPointErrors.insert( make_pair(
						errorOfActualPoint, & dataPoint ) );
				}
			}
			
#ifdef DEBUG_C_POLYNOM
			cout<<"error of the actual polynom: "<<actualErrorSum<<endl;
#endif
			if ( ( actualErrorSum <= maxError ) &&
					( ulNumberOfMaxPointsMatched < ulMatchedPoints )  ){
				lastCorrectPolynom = actualPolynom;
				ulNumberOfMaxPointsMatched = ulMatchedPoints;
#ifdef DEBUG_C_POLYNOM
				cout<<"storing actual polynom as last correct polynom "<<endl;
				lastCorrectPolynom.print( cout );
#endif
				if ( mmapActualPointErrors.size() == ulFirstPointNotMatchebel ){
					/*if all matchebel points are matched -> done*/
#ifdef DEBUG_C_POLYNOM
					cout<<"all points are matched -> done"<<endl;
#endif
					bStopEvaluation = true;
					break;
				}
				//all actual points matched -> take more points
				continue;
			}
		}
		if ( bStopEvaluation ){
			break;
		}
		if ( bPointsNotAdded ){
			continue;
		}
#ifdef DEBUG_C_POLYNOM
		cout<<"integrating points with maximal error on actual polynom "<<
			"(ther are "<<mmapActualPointErrors.size()<<" points)"<<endl<<flush;
#endif
		//integrate missing data points
		while ( ( ! bPointsNotAdded ) && ( maxError < actualErrorSum ) &&
				( ! mmapActualPointErrors.empty() ) && ( ! bStopEvaluation ) ){
			/*while the error sum of the points is greater maxError and not
			all actual points are matched*/
			
			typename multimap< tY, const cDataPointRange< tX, tY > * >::iterator
				itrBiggestErrorPoint = mmapActualPointErrors.end();
			itrBiggestErrorPoint--;
#ifdef DEBUG_C_POLYNOM
			const tY actualError = itrBiggestErrorPoint->first;
			cout<<"biggest error: "<<actualError<<endl<<flush;
#endif
			if ( itrBiggestErrorPoint->first == 0 ){
				//no points with error exists
#ifdef DEBUG_C_POLYNOM
				cout<<"no points with error exists"<<endl<<flush;
#endif
				break;
			}
			
			//add point with the biggest error to the hyperbody
			const cDataPointRange< tX, tY > & dataPoint =
				*(itrBiggestErrorPoint->second);
			mmapActualPointErrors.erase( itrBiggestErrorPoint );
			
			//create the inequiations for the range data point
			const pair< cInequation< tY >, cInequation< tY > >
				paIneqiuations = createInequiationsForRangePoint(
					dataPoint, uiNumberOfActualParameters );
			
			//try to add the inequiations for the range data point
			bool bDataPointAdded = pHyperplaneBody->addInequiation(
				paIneqiuations.first );
#ifdef DEBUG_C_POLYNOM
			cout<<"Actual range data point ("<<dataPoint.x<<
				","<<dataPoint.minY<<" till "<<
				dataPoint.maxY<<" with error "<<actualError<<") "<<
				(bDataPointAdded?"added":"not added")<<", with inequiations:"<<endl<<flush;
			paIneqiuations.first.print( cout );
			paIneqiuations.second.print( cout );
#endif
#ifdef DEBUG_PRINT_HYPERBODY
			cout<<"new hyperbody after adding first inequiation:"<<endl;
			pHyperplaneBody->print( cout );
#endif
			if ( bDataPointAdded ){
				bDataPointAdded &= pHyperplaneBody->addInequiation(
					paIneqiuations.second );
#ifdef DEBUG_C_POLYNOM
				cout<<"Actual range data point ("<<dataPoint.x<<
					","<<dataPoint.minY<<" till "<<
					dataPoint.maxY<<") "<<
					(bDataPointAdded?"added":"not added")<<", with inequiations:"<<endl;
				paIneqiuations.first.print( cout );
				paIneqiuations.second.print( cout );
#endif
#ifdef DEBUG_PRINT_HYPERBODY
				cout<<"new hyperbody:"<<endl;
				pHyperplaneBody->print( cout );
#endif
			}
			if ( bDataPointAdded ){
				/*if the inequiations could be added*/
				setPointsIntegratedLastTime.insert( & dataPoint );
			}else{
				bPointsNotAdded = true;
			}
#ifdef DEBUG_C_POLYNOM
			cout<<"Border points in hyperplane:"<<pHyperplaneBody->getNumberOfBorderPoints()<<endl;
#endif
			if ( ( ulMaxMemoryCost != 0) &&
					( ulMaxMemoryCost < pHyperplaneBody->getNumberOfBorderPoints() ) ){
				//the evaluation casts to much memory -> stop it
#ifdef DEBUG_C_POLYNOM
				cout<<"memory cost to higth"<<endl;
#endif
				bStopEvaluation = true;
				break;
			}
			if ( bPointsNotAdded ){
				break;
			}
			
			//evalue error for remaining points
			actualPolynom.vecFactors = pHyperplaneBody->getPointInBody( uiMinBitsToStoreMantissa );
			
			if ( actualPolynom.vecFactors.empty() ){
				actualPolynom.vecFactors.push_back( 0 );
			}
			
			actualErrorSum = 0;
			mmapActualPointErrors.clear();
			unsigned long ulMatchedPoints = 0;
			//check if this polynom approximate more than the ulPointsAdded points
			for ( size_t uiActualPoint = 0;
					uiActualPoint < ulNumberOfActualPoints; uiActualPoint++ ){
				//check if next data point is approximated by the polynom
				const cDataPointRange< tX, tY > & dataPoint =
					vecData[ uiActualPoint ];
				
				const tY dPolynomValue = actualPolynom.evalue( dataPoint.x );
		
				tY errorOfActualPoint = 0;
				if ( dPolynomValue < dataPoint.minY ){
					//the actual point is not matched by the polynom
					errorOfActualPoint = dataPoint.minY - dPolynomValue;
					actualErrorSum += errorOfActualPoint;
					
				}else if ( dataPoint.maxY < dPolynomValue ){
					//the actual point is not matched by the polynom
					errorOfActualPoint = dPolynomValue - dataPoint.maxY;
					actualErrorSum += errorOfActualPoint;
				}
				if ( actualErrorSum <= maxError ){
					//the actual point is matched by the polynom
					ulMatchedPoints++;
				}//else the actual point isn't matched by the polynom
				if ( ( errorOfActualPoint != 0 ) &&
						( setPointsIntegratedLastTime.find( & dataPoint ) ==
							setPointsIntegratedLastTime.end() ) ){
					//map to points to check for error
					mmapActualPointErrors.insert( make_pair(
						errorOfActualPoint, & dataPoint ) );
				}
			}
#ifdef DEBUG_C_POLYNOM
			cout<<"error of the actual polynom after adding error point: "<<actualErrorSum<<endl;
#endif
			if ( actualErrorSum <= maxError ){
				lastCorrectPolynom = actualPolynom;
				ulNumberOfMaxPointsMatched = max( ulNumberOfMaxPointsMatched, ulMatchedPoints );
#ifdef DEBUG_C_POLYNOM
				cout<<"storing actual polynom as last correct polynom "<<endl;
				lastCorrectPolynom.print( cout );
#endif
				if ( mmapActualPointErrors.size() == ulFirstPointNotMatchebel ){
					/*if all matchebel points are matched -> done*/
#ifdef DEBUG_C_POLYNOM
					cout<<"all points are matched -> done"<<endl;
#endif
					bStopEvaluation = true;
				}
				break;
			}
		}
#ifdef DEBUG_C_POLYNOM
		cout<<"done integrating points with maximal error on actual polynom; actual error sum "<<actualErrorSum<<endl<<flush;
#endif
		if ( bStopEvaluation ){
			break;
		}
		/*if in the iteration befor all actual points wher matched
		(increase number of actual points = vecPointsToAdd.empty() ),
		but not in theas
		-> no more points matchebel -> done*/
		if ( vecPointsToAdd.empty() && ( maxError < actualErrorSum ) ){
				bStopEvaluation = true;
				break;
		}
	}
#ifdef DEBUG_C_POLYNOM
	cout<<"evaluing polynom done "<<endl;
#endif
	if ( pHyperplaneBody ){
		delete pHyperplaneBody;
	}
	
#ifdef DEBUG_C_POLYNOM
	cout<<"adding range data points wich fulfill this polynom"<<endl;
#endif
	actualErrorSum = 0;
	unsigned long ulMatchedPoints = 0;
	//check if this polynom approximate more than the ulPointsAdded points
	while ( ulMatchedPoints < ulNumberOfDataPoints ){
		//check if next data point is approximated by the polynom
		
		const cDataPointRange< tX, tY > & dataPoint =
			vecData[ ulMatchedPoints ];
		
		const tY dPolynomValue = lastCorrectPolynom.evalue( dataPoint.x );

		if ( dPolynomValue < dataPoint.minY ){
			//the actual point is not matched by the polynom
			actualErrorSum += dataPoint.minY - dPolynomValue;
			
		}else if ( dataPoint.maxY < dPolynomValue ){
			//the actual point is not matched by the polynom
			actualErrorSum += dPolynomValue - dataPoint.maxY;
		}
		if ( maxError < actualErrorSum ){
			break;
		}/*else the actual point is matched by the polynom
		-> treat it as added*/
		ulMatchedPoints++;
	}
	if ( 0 < ulMatchedPoints ){
		vecFactors = lastCorrectPolynom.vecFactors;
	}
#ifdef DEBUG_C_POLYNOM
	cout<<"actual polynom: ";
	print( cout );
	cout<<"cPolynom<tX, tY>::evalueSplineIterativFast( vecData, uiMaxNumberOfParameters="<<
		uiMaxNumberOfParameters<<", uiMinBitsToStoreMantissa="<<
		uiMinBitsToStoreMantissa<<", maxValue="<<maxValue<<
		", maxError="<<maxError<<" ,ulMaxMemoryCost="<<
		ulMaxMemoryCost<<" ) done; points matched: "<<ulMatchedPoints<<endl;
#endif
	return max( ulMatchedPoints, ulNumberOfMaxPointsMatched );
}

#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING



/**
 * @param dataPoint the polynom to compare this polynom with
 * @return true if the given polynom is equal to this, else false
 * 	(@see x, @see y)
 */
template<class tX, class tY> bool fib::algorithms::nD1::cPolynom<tX, tY>::
		operator==( const cPolynom<tX, tY> & polynom ) const{
	
	return compareVectorDouble( vecFactors, polynom.vecFactors );
}


/**
 * @param dataPoint the polynom to compare this polynom with
 * @return true if the given polynom is not equal to this, else false
 * 	(@see x, @see y)
 */
template<class tX, class tY> bool fib::algorithms::nD1::cPolynom<tX, tY>::
		operator!=( const cPolynom<tX, tY> & polynom ) const{
	
	return ! ( (*this) == polynom );
}


#endif //___N_D_1_C_POLYNOM_CPP__
















