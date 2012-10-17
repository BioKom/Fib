/**
 * @file cSpline
 * file name: cSpline.h
 * @author Betti Oesterholz
 * @date 25.06.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements a class for a one dimensional spline.
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
 * This file implements a class for a one dimensional spline.
 * A spline is a interpolation of a function by polynome (@see cPolynom).
 * The second template parameter should always be a floating point datatype.
 *
 */
/*
History:
25.06.2011  Oesterholz  created
18.09.2012  Oesterholz  FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING:
	evalueSpline(): the glp library (extern package) linear solver will be
	used to find a spline for a vector of range data points
*/



#ifndef ___N_D_1_C_SPLINE_CPP__
#define ___N_D_1_C_SPLINE_CPP__

#include "../incl/cSpline.h"

#include "nLinearEquation.h"
#include "cLinearEquation.h"
#include "cInequation.h"
#include "cHyperplaneBodyFull.h"
#include "cHyperplaneBodySimple.h"

#include "cFunctionValue.h"
#include "cFunctionVariable.h"
#include "cFunctionIf.h"
#include "cConditionLower.h"


#include <iostream>
#include <algorithm>

#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
	#include "mutexGlpkSolver.inc"
	#include <glpk.h>
	#include <limits.h>
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING


//for debugging
//#define DEBUG_C_SPLINE
//#define DEBUG_C_SPLINE_EVALUE

#ifdef DEBUG_C_SPLINE
	#include <float.h>
#endif

using namespace fib::algorithms::nD1;
using namespace fib::algorithms::nDn;
using namespace fib::algorithms::nLinearEquation;


/**
 * Standartconstructor
 */
template <class tX, class tY> fib::algorithms::nD1::cSpline<tX, tY>::cSpline():
		vecPolynoms(), vecBorders(){
	//nothing to do
}


/**
 * This method evalues the value of this spline.
 * For this the polynom in which borders the value is will be evalued.
 *
 * @see vecPolynoms
 * @see vecBorders
 * @see cPolynom::evalue()
 * @param x the input value for the spline
 * @return the evalued value f( x )
 */
template <class tX, class tY> tY fib::algorithms::nD1::cSpline<tX, tY>::
		evalue( const tX & x ) const{

#ifdef DEBUG_C_SPLINE_EVALUE
	cout<<"fib::algorithms::nD1::cSpline<tX, tY>::evalue( x="<<x<<" ) started"<<endl<<flush;
#endif //DEBUG_C_SPLINE_EVALUE
	if ( vecPolynoms.empty() ){
#ifdef DEBUG_C_SPLINE_EVALUE
		cout<<"fib::algorithms::nD1::cSpline<tX, tY>::evalue( x="<<x<<
			" ) done no polynome found y=0"<<endl<<flush;
#endif //DEBUG_C_SPLINE_EVALUE
		return ((tY)(0));
	}
	if ( vecBorders.empty() ){
#ifdef DEBUG_C_SPLINE_EVALUE
		cout<<"fib::algorithms::nD1::cSpline<tX, tY>::evalue( x="<<x<<
			" ) done no borders found y="<<vecPolynoms[ 0 ].evalue( x )<<endl<<flush;
#endif //DEBUG_C_SPLINE_EVALUE
		return vecPolynoms[ 0 ].evalue( x );
	}
	const unsigned int uiNumberOfPolynoms = vecPolynoms.size();
	
	unsigned int uiIndexLowerBorder = 0;
	tY dLowerBorder = vecBorders[ 0 ];
	unsigned int uiIndexUpperBorder = uiNumberOfPolynoms - 2;
	tY dUpperBorder = vecBorders[ uiIndexUpperBorder ];
	
	if ( x < dLowerBorder ){
		//x for first polynom
#ifdef DEBUG_C_SPLINE_EVALUE
		cout<<"evalue( x="<<x<<" ) done x for first polynom y="<<
			vecPolynoms[ 0 ].evalue( x )<<endl<<flush;
#endif //DEBUG_C_SPLINE_EVALUE
		return vecPolynoms[ 0 ].evalue( x );
	}//else
	if ( dUpperBorder <= x ){
		//x for last polynom
#ifdef DEBUG_C_SPLINE_EVALUE
		cout<<"evalue( x="<<x<<" ) done x for last polynom y="<<
			vecPolynoms[ uiNumberOfPolynoms - 1 ].evalue( x )<<endl<<flush;
#endif //DEBUG_C_SPLINE_EVALUE
		return vecPolynoms[ uiNumberOfPolynoms - 1 ].evalue( x );
	}//else ( lower border < upper border )
#ifdef DEBUG_C_SPLINE_EVALUE
	cout<<"starting log border search: index lower border="<<uiIndexLowerBorder<<
		"  index upper border="<<uiIndexUpperBorder<<endl<<flush;
#endif //DEBUG_C_SPLINE_EVALUE
	while ( uiIndexLowerBorder != uiIndexUpperBorder ){
		
		if ( (uiIndexLowerBorder + 1) == uiIndexUpperBorder ){
#ifdef DEBUG_C_SPLINE_EVALUE
			cout<<"evalue( x="<<x<<" ) lower border and upper border are neibours y="<<
				vecPolynoms[ uiIndexUpperBorder ].evalue( x )<<endl<<flush;
#endif //DEBUG_C_SPLINE_EVALUE
			return vecPolynoms[ uiIndexUpperBorder ].evalue( x );
		}//else the uiIndexUpperBorde is minimum two greater than uiIndexLowerBorder
		const unsigned int uiIndexMiddleBorder =
			( uiIndexLowerBorder + uiIndexUpperBorder ) / 2;
		/* uiIndexUpperBorde is minimum two greater than uiIndexLowerBorder
		 -> uiIndexMiddleBorder is minimum one greater as lower border and
			minimum one lower than upper border */
		const tY dMiddleBorder = vecBorders[ uiIndexMiddleBorder ];
#ifdef DEBUG_C_SPLINE_EVALUE
		cout<<"index middle border="<<uiIndexMiddleBorder<<"  border value="<<dMiddleBorder<<endl<<flush;
#endif //DEBUG_C_SPLINE_EVALUE
		if ( dMiddleBorder <= x ){
			//x is above the middle border -> the middle border is the new lower border
			uiIndexLowerBorder = uiIndexMiddleBorder;
			dLowerBorder = dMiddleBorder;
		}else{/*x is below the middle border
			-> the middle border is the new upper border*/
			uiIndexUpperBorder = uiIndexMiddleBorder;
			dUpperBorder = dMiddleBorder;
		}
#ifdef DEBUG_C_SPLINE_EVALUE
		cout<<"next log border search: index lower border="<<uiIndexLowerBorder<<
			"  index upper border="<<uiIndexUpperBorder<<endl<<flush;
#endif //DEBUG_C_SPLINE_EVALUE
	}
#ifdef DEBUG_C_SPLINE_EVALUE
	cout<<"fib::algorithms::nD1::cSpline<tX, tY>::evalue( x="<<x<<" ) done: error no border found y=0"<<endl<<flush;
#endif //DEBUG_C_SPLINE_EVALUE
	return ((tY)(0));
}


/**
 * This function prints this spline to the given stream.
 *
 * @param outputStream the stream wher to print this spline to
 */
template <class tX, class tY> void fib::algorithms::nD1::cSpline<tX, tY>::
	print( ostream & outputStream ) const{
	
	if ( vecPolynoms.empty() ){
		outputStream<<"no spline"<<endl;
		return;
	}//else
	outputStream<<"first :";
	vecPolynoms[ 0 ].print( outputStream );
	const unsigned int uiNumberOfPolynoms = vecPolynoms.size();
	for ( unsigned int uiActualPolynom = 1;
			uiActualPolynom < uiNumberOfPolynoms; uiActualPolynom++ ){
		
		outputStream<<"from "<<vecBorders[ uiActualPolynom - 1 ]<<" :";
		vecPolynoms[ uiActualPolynom ].print( outputStream );
	}
	outputStream<<endl;
}


/**
 * This functions evalues the error of the given datapoints to the values
 * this spline evalues to.
 *
 * The evaluation of the spline will be done by evalue().
 * The error will just be counted, if it is greater than a real small value.
 * @see evalue()
 *
 * @param vecInputData the data for which the error is to evalue
 * @return a pair with two values:
 * 	- the first value is the number of datapoints evalued wrong
 * 	- the second value is the sum of the error of all datapoints
 */
template <class tX, class tY> pair<unsigned long, tY>
	fib::algorithms::nD1::cSpline<tX, tY>::evalueError(
		const vector< cDataPoint< tX, tY> > & vecInputData ) const{
	
	const size_t uiDataSize = vecInputData.size();
	tY dError = 0.0;
	unsigned long ulWrongValues = 0;
	
	if ( vecPolynoms.empty() ){
		//no polynoms -> compare with constant 0
		for ( size_t iActualValue = 0; iActualValue < uiDataSize;
				iActualValue++ ){
		
			const tY y = vecInputData[ iActualValue ].y;
			if ( ! compareDouble( y, ((tY)(0)) ) ){
				dError += absF( y );
				ulWrongValues++;
			}
		}
		return make_pair( ulWrongValues, dError );
	}//else ther are polynoms
	
	vector< cDataPoint< tX, tY> > vecSortedInputData( vecInputData );
	sort( vecSortedInputData.begin(), vecSortedInputData.end() );
	
	const unsigned int uiNumberOfBorders = vecBorders.size();
	unsigned int uiActualPolynom = 0;
	
	for ( size_t iActualValue = 0; iActualValue < uiDataSize;
			iActualValue++ ){
		
		//search for next polynom for the datapoint
		while ( ( uiActualPolynom < uiNumberOfBorders ) &&
				( vecBorders[ uiActualPolynom ] <= vecSortedInputData[ iActualValue ].x ) ){
			
			uiActualPolynom++;
		}
		
		const tY dSplineValue = vecPolynoms[ uiActualPolynom ].evalue(
			vecSortedInputData[ iActualValue ].x );
		
		const tY y = vecSortedInputData[ iActualValue ].y;
		
		if ( ! compareDouble( y, dSplineValue ) ){
			dError += absF( dSplineValue - y );
			ulWrongValues++;
		}
	}

	return make_pair( ulWrongValues, dError );
}


/**
 * This functions evalues the error of the given datapoints to the values
 * this spline evalues to.
 * This function will stop the evaluation, if the maximum error maxYError
 * was reached.
 *
 * The evaluation of the spline will be done by evalue().
 * The error will just be counted, if it is greater than the a real small value.
 * @see evalue()
 *
 * @param vecInputData the data for wich the error is to evalue
 * @param maxYError the maximum error, at which the evaluation should stop;
 * 	if maxYError is 0 the maximum error is unlimeted
 * @return the sum of the error of all datapoints, but maximal maxYError
 */
template <class tX, class tY> tY fib::algorithms::nD1::cSpline<tX, tY>::
	evalueErrorMax( const vector< cDataPoint< tX, tY> > & vecInputData,
		const tY maxYError ) const{
	
	
	const size_t uiDataSize = vecInputData.size();
	tY dError = 0.0;
	
	if ( vecPolynoms.empty() ){
		//no polynoms -> compare with constant 0
		for ( size_t iActualValue = 0; iActualValue < uiDataSize;
				iActualValue++ ){
		
			const tY y = vecInputData[ iActualValue ].y;
			if ( ! compareDouble( y, ((tY)(0)) ) ){
				dError += absF( y );
			}
			if ( (maxYError <= dError) && (0.0 < maxYError) ){
				//max error reached
				return maxYError;
			}
		}
		return dError;
	}//else ther are polynoms
	
	vector< cDataPoint< tX, tY> > vecSortedInputData( vecInputData );
	sort( vecSortedInputData.begin(), vecSortedInputData.end() );
	
	const unsigned int uiNumberOfBorders = vecBorders.size();
	unsigned int uiActualPolynom = 0;
	
	for ( size_t iActualValue = 0; iActualValue < uiDataSize;
			iActualValue++ ){
		
		//search for next polynom for the datapoint
		while ( ( uiActualPolynom < uiNumberOfBorders ) &&
				( vecBorders[ uiActualPolynom ] <= vecSortedInputData[ iActualValue ].x ) ){
			
			uiActualPolynom++;
		}
		
		const tY dSplineValue = vecPolynoms[ uiActualPolynom ].evalue(
			vecSortedInputData[ iActualValue ].x );
		
		const tY y = vecSortedInputData[ iActualValue ].y;
		
		if ( ! compareDouble( y, dSplineValue ) ){
			dError += absF( dSplineValue - y );
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
 * values this spline evalues to.
 *
 * The evaluation of the spline will be done by evalue().
 * A datapoint has an error, if it lay outside the datpoint range. The
 * error is it's distance to the neares datapoint boundery.
 * The error will just be counted, if it is greater than the a real small value.
 * @see evalue()
 *
 * @param vecInputData the data for wich the error is to evalue
 * @return a pair with two values:
 * 	- the first value is the number of datapoints evalued wrong
 * 	- the second value is the sum of the error of all datapoints
 */
template <class tX, class tY> pair<unsigned long, tY>
	fib::algorithms::nD1::cSpline<tX, tY>::evalueError(
		const vector< cDataPointRange< tX, tY> > & vecInputData ) const{
	
	const size_t uiDataSize = vecInputData.size();
	tY dError = 0.0;
	unsigned long ulWrongValues = 0;
	
	if ( vecPolynoms.empty() ){
		//no polynoms -> compare with constant 0
		for ( size_t iActualValue = 0; iActualValue < uiDataSize;
				iActualValue++ ){
			
			const tY minY = vecInputData[ iActualValue ].minY;
			const tY maxY = vecInputData[ iActualValue ].maxY;
			
			if ( ((tY)(0)) < minY){
				dError += minY;
				ulWrongValues++;
			}else if ( maxY < ((tY)(0)) ){
				dError -= maxY;
				ulWrongValues++;
			}
		}
		return make_pair( ulWrongValues, dError );
	}//else ther are polynoms
	
	vector< cDataPointRange< tX, tY> > vecSortedInputData( vecInputData );
	sort( vecSortedInputData.begin(), vecSortedInputData.end() );
	
	const unsigned int uiNumberOfBorders = vecBorders.size();
	unsigned int uiActualPolynom = 0;
	
	for ( size_t iActualValue = 0; iActualValue < uiDataSize;
			iActualValue++ ){
		
		//search for next polynom for the datapoint
		while ( ( uiActualPolynom < uiNumberOfBorders ) &&
				( vecBorders[ uiActualPolynom ] <= vecSortedInputData[ iActualValue ].x ) ){
			
			uiActualPolynom++;
		}
		
		const tY dSplineValue = vecPolynoms[ uiActualPolynom ].evalue(
			vecSortedInputData[ iActualValue ].x );
		
		const tY minY = vecSortedInputData[ iActualValue ].minY;
		const tY maxY = vecSortedInputData[ iActualValue ].maxY;
		
		if ( dSplineValue < minY){
			dError += minY - dSplineValue;
			ulWrongValues++;
		}else if ( maxY < dSplineValue ){
			dError += dSplineValue - maxY;
			ulWrongValues++;
		}
	}

	return make_pair( ulWrongValues, dError );
}


/**
 * This functions evalues the error of the given datapoints to the values
 * this spline evalues to.
 * This function will stop the evaluation, if the maximum error maxYError
 * was reached.
 *
 * The evaluation of the spline will be done by evalue().
 * A datapoint has an error, if it lay outside the datpoint range. The
 * error is it's distance to the neares datapoint boundery.
 * The error will just be counted, if it is greater than the a real small value.
 * @see evalue()
 *
 * @param vecInputData the data for wich the error is to evalue
 * @param maxYError the maximum error, at which the evaluation should stop;
 * 	if maxYError is 0 the maximum error is unlimeted
 * @return the sum of the error of all datapoints, but maximal maxYError
 */
template <class tX, class tY> tY fib::algorithms::nD1::cSpline<tX, tY>::
	evalueErrorMax( const vector< cDataPointRange< tX, tY> > & vecInputData,
		const tY maxYError ) const{
	
	const size_t uiDataSize = vecInputData.size();
	tY dError = 0.0;
	
	if ( vecPolynoms.empty() ){
		//no polynoms -> compare with constant 0
		for ( size_t iActualValue = 0; iActualValue < uiDataSize;
				iActualValue++ ){
			
			const tY minY = vecInputData[ iActualValue ].minY;
			const tY maxY = vecInputData[ iActualValue ].maxY;
			
			if ( ((tY)(0)) < minY){
				dError += minY;
			}else if ( maxY < ((tY)(0)) ){
				dError -= maxY;
			}
			if ( (maxYError <= dError) && (0.0 < maxYError) ){
				//max error reached
				return maxYError;
			}
		}
		return dError;
	}//else ther are polynoms
	
	vector< cDataPointRange< tX, tY> > vecSortedInputData( vecInputData );
	sort( vecSortedInputData.begin(), vecSortedInputData.end() );
	
	const unsigned int uiNumberOfBorders = vecBorders.size();
	unsigned int uiActualPolynom = 0;
	
	for ( size_t iActualValue = 0; iActualValue < uiDataSize;
			iActualValue++ ){
		
		//search for next polynom for the datapoint
		while ( ( uiActualPolynom < uiNumberOfBorders ) &&
				( vecBorders[ uiActualPolynom ] <= vecSortedInputData[ iActualValue ].x ) ){
			
			uiActualPolynom++;
		}
		
		const tY dSplineValue = vecPolynoms[ uiActualPolynom ].evalue(
			vecSortedInputData[ iActualValue ].x );
		
		const tY minY = vecSortedInputData[ iActualValue ].minY;
		const tY maxY = vecSortedInputData[ iActualValue ].maxY;
		
		if ( dSplineValue < minY){
			dError += minY - dSplineValue;
		}else if ( maxY < dSplineValue ){
			dError += dSplineValue - maxY;
		}
		if ( (maxYError <= dError) && (0.0 < maxYError) ){
			//max error reached
			return maxYError;
		}
	}

	return dError;
}


/**
 * This function converts this spline, into an fib-underfunction.
 * Beware: You have to delete the returned fib-underfunction.
 *
 * @param pVariable the variable (x) for the spline
 * @return a pointer to the fib-underfunction, wich represents the
 * 	same spline as this spline
 */
template <class tX, class tY> cUnderFunction * fib::algorithms::nD1::cSpline<tX, tY>::
	toFibUnderFunction( cFibVariable * pVariable ) const{
	
	if ( vecPolynoms.empty() ){
		return new cFunctionValue( 0.0 );
	}
	
	/*- for each polynom create its underfunction
	- combine the created underfunctions with if underfunctions, which seperate them at ther borders
	
	In the created subfunction the first and last polynom will be in the
	second layer of if-functions (if enough polynoms exists).
	The remaining polynoms will be distributed in an balanced tree of if
	subfunctions.
	*/
	const unsigned int uiNumberOfBorders = vecBorders.size();
	if ( uiNumberOfBorders == 0 ){
		//no borders -> just one polynom
		return vecPolynoms[ 0 ].toFibUnderFunction( pVariable );
	}//else
	if ( uiNumberOfBorders <= 3 ){
		
		if ( uiNumberOfBorders == 1 ){
			
			cCondition * pBorderCondition = new cConditionLower(
				new cFunctionVariable( pVariable ),
				new cFunctionValue( vecBorders[ 0 ] ) );
			cUnderFunction * pFunctionLower  = vecPolynoms[ 0 ].toFibUnderFunction( pVariable );
			cUnderFunction * pFunctionHigher = vecPolynoms[ 1 ].toFibUnderFunction( pVariable );
			
			return new cFunctionIf( pBorderCondition, pFunctionLower, pFunctionHigher );
		}//else
		if ( uiNumberOfBorders == 2 ){
			cCondition * pBorderConditionLower = new cConditionLower(
				new cFunctionVariable( pVariable ),
				new cFunctionValue( vecBorders[ 0 ] ) );
			cCondition * pBorderConditionHigher = new cConditionLower(
				new cFunctionVariable( pVariable ),
				new cFunctionValue( vecBorders[ 1 ] ) );
			cUnderFunction * pFunctionLower  = vecPolynoms[ 0 ].toFibUnderFunction( pVariable );
			cUnderFunction * pFunctionMiddle = vecPolynoms[ 1 ].toFibUnderFunction( pVariable );
			cUnderFunction * pFunctionHigher = vecPolynoms[ 2 ].toFibUnderFunction( pVariable );
			
			return new cFunctionIf( pBorderConditionLower, pFunctionLower,
				new cFunctionIf( pBorderConditionHigher, pFunctionMiddle, pFunctionHigher ) );
		}//else
		if ( uiNumberOfBorders == 3 ){
			cCondition * pBorderCondition0 = new cConditionLower(
				new cFunctionVariable( pVariable ),
				new cFunctionValue( vecBorders[ 0 ] ) );
			cCondition * pBorderCondition1 = new cConditionLower(
				new cFunctionVariable( pVariable ),
				new cFunctionValue( vecBorders[ 1 ] ) );
			cCondition * pBorderCondition2 = new cConditionLower(
				new cFunctionVariable( pVariable ),
				new cFunctionValue( vecBorders[ 2 ] ) );
			cUnderFunction * pFunction0 = vecPolynoms[ 0 ].toFibUnderFunction( pVariable );
			cUnderFunction * pFunction1 = vecPolynoms[ 1 ].toFibUnderFunction( pVariable );
			cUnderFunction * pFunction2 = vecPolynoms[ 2 ].toFibUnderFunction( pVariable );
			cUnderFunction * pFunction3 = vecPolynoms[ 3 ].toFibUnderFunction( pVariable );
			
			return new cFunctionIf( pBorderCondition1,
				new cFunctionIf( pBorderCondition0, pFunction0, pFunction1 ),
				new cFunctionIf( pBorderCondition2, pFunction2, pFunction3 ) );
		}//not possible -> unreachebel
	}
	const unsigned int uiIndexMiddleBorder = uiNumberOfBorders / 2;
	
	cCondition * pBorderConditionLower = new cConditionLower(
		new cFunctionVariable( pVariable ),
		new cFunctionValue( vecBorders[ 0 ] ) );
	cCondition * pBorderConditionMiddle = new cConditionLower(
		new cFunctionVariable( pVariable ),
		new cFunctionValue( vecBorders[ uiIndexMiddleBorder ] ) );
	cCondition * pBorderConditionHigher = new cConditionLower(
		new cFunctionVariable( pVariable ),
		new cFunctionValue( vecBorders[ uiNumberOfBorders - 1 ] ) );
	
	
	cUnderFunction * pFunction0 = vecPolynoms[ 0 ].toFibUnderFunction( pVariable );
	cUnderFunction * pFunction3 = vecPolynoms[ uiNumberOfBorders ].toFibUnderFunction( pVariable );
	
	vector< const cPolynom< tX, tY> * > vecPolynomsLower;
	vector< tY > vecBordersLower;
	vector< const cPolynom< tX, tY> * > vecPolynomsHigher;
	vector< tY > vecBordersHigher;
	
	for ( unsigned int uiActualPolynom = 1;
			uiActualPolynom < uiIndexMiddleBorder; uiActualPolynom++ ){
		
		vecPolynomsLower.push_back( &(vecPolynoms[ uiActualPolynom ]) );
		vecBordersLower.push_back( vecBorders[ uiActualPolynom ] );
	}
	vecPolynomsLower.push_back( &(vecPolynoms[ uiIndexMiddleBorder ]) );
	
	for ( unsigned int uiActualPolynom = uiIndexMiddleBorder + 1;
			uiActualPolynom < (uiNumberOfBorders - 1); uiActualPolynom++ ){
		
		vecPolynomsHigher.push_back( &(vecPolynoms[ uiActualPolynom ]) );
		vecBordersHigher.push_back( vecBorders[ uiActualPolynom ] );
	}
	vecPolynomsHigher.push_back( &(vecPolynoms[ uiNumberOfBorders - 1 ]) );
	
	
	cUnderFunction * pFunction1 = generateSubfunctionTree( vecPolynomsLower, vecBordersLower, pVariable );
	cUnderFunction * pFunction2 = generateSubfunctionTree( vecPolynomsHigher, vecBordersHigher, pVariable );
	
	
	return new cFunctionIf( pBorderConditionMiddle,
		new cFunctionIf( pBorderConditionLower, pFunction0, pFunction1 ),
		new cFunctionIf( pBorderConditionHigher, pFunction2, pFunction3 ) );
}


/**
 * This function evalues the function for the given data.
 * The evalued function will have the order n of the number of given
 * datapoints.
 * It will call @see cPolynom::evalue( vecData ) and add the created polynom.
 *
 * @param vecData the data for which to evalue the function
 * @return if the function for the datapoints could be evalued: the
 * 	elements of the evalued function in this function and true, else
 * 	false and the elements of this function not changed
 */
template<class tX, class tY> bool fib::algorithms::nD1::cSpline<tX, tY>::
		evalue( const vector< cDataPoint< tX, tY> > & vecData ){
	
	
	cPolynom<tX, tY> evaluedPolynom;
	const bool bPolyEvalued = evaluedPolynom.evalue( vecData );
	
	if ( ! bPolyEvalued ){
		return false;
	}//polynom succesfull evalued
	
	vecPolynoms.clear();
	vecBorders.clear();
	
	vecPolynoms.push_back( evaluedPolynom );
	
	return true;
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
 * The evalued spline (this spline) consists of a number of polynoms
 * seperated by border points.
 * The evalued polynoms (@see cPolynom) will have the form:
 * 	y = vecFactors[ 0 ] + vecFactors[ 1 ] * x +
 * 	vecFactors[ 2 ] * x^2 + ... +
 * 	vecFactors[ uiNumberOfParameters - 1 ] *
 * 		x^(uiNumberOfParameters - 1)
 * The upper border point of a polynom is the first point at wich the
 * polynom dosn't match the given data vecData anymore.
 *
 * The method will iterativ increase the number of parameters for the
 * polynoms (from 1 to uiMaxNumberOfParameters) and will try to not use
 * all of the given range points to find the polynoms.
 *
 * @see evalue()
 * @see cPolynom::evalueSplineIterativFast()
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
 * 	be set to maxError / vecInputData.size()
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
template<class tX, class tY> unsigned long fib::algorithms::nD1::cSpline<tX, tY>::
	evalueSpline(
		const vector< cDataPointRange< tX, tY> > & vecInputData,
		unsigned int uiMaxNumberOfParameters,
		const tY maxValue,
		const tY maxError,
		const tY maxErrorPerValue,
		const double dWeightParameter ){
	
#ifdef DEBUG_C_SPLINE
	cout<<"cSpline<tX, tY>::evalueSpline( vecInputData, uiMaxNumberOfParameters="<<
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
	
	//remember last best spline
	vector< cPolynom< tX, tY> > vecOldPolynoms( vecPolynoms );
	vector< tY > vecOldBorders( vecBorders );
	
	vecPolynoms.clear();
	vecBorders.clear();
	
	vector< cDataPointRange< tX, tY> > vecData( vecInputData );
	sort( vecData.begin(), vecData.end() );
	
	//for the indexs counting starts at 1, 0 stands for no data point
	//a good polynom is a polynom, which dos not exceed its share of the error
	/*index of the last data point for which a good polynom was found;
	init with 0 for: no good data point found jet*/
	unsigned long ulIndexLastGoodDataPoint = 0;
	/*the index of the first data point, which should be integrated into the
	next polynom*/
	unsigned long ulIndexDataPointActualPolynomStart = 1;
	
	double dLastErrorSum = 0.0;
	
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
#ifdef DEBUG_C_SPLINE
	lpControlParameter.msg_lev = GLP_MSG_ALL; //(default: GLP MSG ALL)
#else
	lpControlParameter.msg_lev = GLP_OFF;  //= no output = glp_term_out( GLP_OFF );
#endif //DEBUG_C_SPLINE
	//simplex iteration limit
	lpControlParameter.it_lim  = (100000000 < INT_MAX) ? 100000000 : INT_MAX;
	//time limit in  milli seconds
	lpControlParameter.tm_lim  = 10000;//=10 s ; default INT_MAX
	
	//presolver: disable because also non optimal solutions are needed
	lpControlParameter.presolve = GLP_OFF;
	
	while ( ulIndexLastGoodDataPoint <= ulNumberOfDataPoints ){
		//while some points missing in the spline
		
#ifdef DEBUG_C_SPLINE
		cout<<endl<<"Trying to find a new polynom beginning at point "<<
			ulIndexLastGoodDataPoint<<" (error sum till last found polynom="<<dLastErrorSum<<")."<<endl;
#endif
		
		/*the index of the data point, wich could not be integrated into the
		next polynom to generate*/
		unsigned long ulIndexToMuchDataPoint = ulNumberOfDataPoints + 1;
		
		/*the index of the last data point which should be integrated into the
		actual to generate polynom*/
		//step 1: (= ulNumberOfDataPoints - 1) try to find spline for all data points
		unsigned long ulActualIndexOfLastDataPoint = ulNumberOfDataPoints;
		
		cPolynom<tX, tY> actualPolynom;
		tY errorSumActualPolynom = ((tY)(0.0));
		
		//if for the actual points a spline was found
		bool bSplineFound = false;
		
		//while next good polynom not found
		while ( ulIndexDataPointActualPolynomStart <= ulActualIndexOfLastDataPoint ){
			/* convert actual data points to glp problem;
			data points for actual polynom form ulIndexDataPointActualPolynomStart
			till ulActualIndexOfLastDataPoint*/
			
#ifdef DEBUG_C_SPLINE
			cout<<endl<<"Creating linear program for "<<
				(1 + ulActualIndexOfLastDataPoint - ulIndexDataPointActualPolynomStart)<<
				" data points (from index "<<ulIndexDataPointActualPolynomStart<<
				" to index "<<ulActualIndexOfLastDataPoint<<")."<<endl<<flush;
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
					( m = 1 + ulActualIndexOfLastDataPoint - ulIndexDataPointActualPolynomStart )
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

	//TODO check
		
			const unsigned long ulDataPointsToInclude = 1 +
				ulActualIndexOfLastDataPoint - ulIndexDataPointActualPolynomStart;
			
			glp_add_rows( pLinearProblem, ulDataPointsToInclude );
			//set y_i
			//index starting from 0 of the actual data point
			unsigned long ulIndexDataPoint =
				ulIndexDataPointActualPolynomStart - 1;
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
			ulIndexDataPoint = ulIndexDataPointActualPolynomStart - 1;
			for ( unsigned long ulActualRow = 1;
					ulActualRow <= ulDataPointsToInclude; ulActualRow++ ){
				
#ifdef DEBUG_C_SPLINE
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
				
#ifdef DEBUG_C_SPLINE
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
			
#ifdef DEBUG_C_SPLINE
			cout<<endl<<"start solving problem with "<<
				 glp_get_num_rows( pLinearProblem )<<" rows and "<<
				 glp_get_num_cols( pLinearProblem )<<" columns"<<endl<<flush;
#endif
			// solve problem with simplex glp solver
			const int uiResultSimplex = glp_simplex( pLinearProblem, & lpControlParameter );
			
			
			const int iProblemStatus = glp_get_status( pLinearProblem );
			
#ifdef DEBUG_C_SPLINE
			cout<<endl<<"LP solver returned;"<<endl<<flush;
			if ( ( iProblemStatus == GLP_OPT ) ||
					( iProblemStatus == GLP_FEAS ) ){
				cout<<"   the solution is OK"<<endl<<flush;
			}
			switch ( iProblemStatus ){
				case GLP_OPT:   cout<<"solution is optimal"<<endl;break;
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
#ifdef DEBUG_C_SPLINE
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
				
				for ( unsigned long ulActualCol = uiNumberOfParameterColumns + 1;
						ulActualCol <= ulNumberOfColumns; ulActualCol++ ){
					
					const double dErrorActualValue =
						glp_get_col_prim( pLinearProblem, ulActualCol );
					
					const double dAbsErrorActualValue = ( dErrorActualValue < 0.0 ) ?
						( 0.0 - dErrorActualValue ) : dErrorActualValue;
					
					dErrorSumNewPolynom += dAbsErrorActualValue;
					
					if ( ( maxError * ( ((double)ulActualIndexOfLastDataPoint) /
								((double)ulNumberOfDataPoints) ) <
								( dLastErrorSum + dErrorSumNewPolynom ) ) ||
							( dMaxErrorPerValue < dAbsErrorActualValue ) ){
						//error to great
#ifdef DEBUG_C_SPLINE
						cout<<endl<<"Dismiss found polynom, error to great: "<<
							"dErrorSumNewPolynom="<<dErrorSumNewPolynom<<" (maxError="<<
							maxError<<") dAbsErrorActualValue="<<dAbsErrorActualValue<<
							" (dMaxErrorPerValue="<<dMaxErrorPerValue<<")"<<endl;
#endif
						bErrorOk = false;
						break;
					}
				}
				
#ifdef DEBUG_C_SPLINE
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
					while ( ( ! actualPolynom.vecFactors.empty() ) &&
							( actualPolynom.vecFactors.back() == 0.0 ) ){
						
						actualPolynom.vecFactors.pop_back();
					}
					errorSumActualPolynom = ((tY)(dErrorSumNewPolynom));
					
#ifdef DEBUG_C_SPLINE
					cout<<endl<<"Polynom OK (error sum "<<dErrorSumNewPolynom<<") :"<<endl;
					actualPolynom.print( cout );
#endif
				}
			}else{//LP problem could not be solved
#ifdef DEBUG_C_SPLINE
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
				points and the last data points for wich not a good spline was found */
#ifdef DEBUG_C_SPLINE
				cout<<endl<<"Found polynom acepted, for data points till index: "<<
					ulActualIndexOfLastDataPoint<<endl;
#endif
				ulIndexLastGoodDataPoint = ulActualIndexOfLastDataPoint;
				
				const unsigned long ulDeltaBetweanLastGoodAndToMuch =
					ulIndexToMuchDataPoint - ulIndexLastGoodDataPoint;
				
				if ( ulDeltaBetweanLastGoodAndToMuch <= 1 ){
					/*no data points between last good and to much
					-> can't find more data points -> stop evaluation*/
#ifdef DEBUG_C_SPLINE
					cout<<endl<<"no data points between last good and to much "<<
						"-> can't find more data points -> stop evaluation"<<endl;
#endif
					break;
				}
				
				ulActualIndexOfLastDataPoint += ulDeltaBetweanLastGoodAndToMuch / 2;
			}else{/*if no spline found or error is to great on actual data points
				-> reduce number of data points for the spline
				-> try to find spline for data points till the middle of actual data
				points and the last data points for wich a good spline was found */
#ifdef DEBUG_C_SPLINE
				cout<<endl<<"found polynom not acepted, for data points till index: "<<
					ulActualIndexOfLastDataPoint<<endl;
#endif
				ulIndexToMuchDataPoint = ulActualIndexOfLastDataPoint;
				
				const unsigned long ulDeltaBetweanLastGoodAndToMuch =
					ulIndexToMuchDataPoint - ulIndexLastGoodDataPoint;
					
				if ( ulDeltaBetweanLastGoodAndToMuch <= 1 ){
					/*no data points between last good and to much
					-> can't omit more data points -> stop evaluation*/
#ifdef DEBUG_C_SPLINE
					cout<<endl<<"no data points between last good and to much "<<
						"-> can't omit more data points -> stop evaluation"<<endl;
#endif
					break;
				}
				
				ulActualIndexOfLastDataPoint -= ulDeltaBetweanLastGoodAndToMuch / 2;
			}
			
		}//end while polynom not found
		
		if ( actualPolynom.vecFactors.empty() ){
			//warning: no new spline found -> no new data points found
#ifdef DEBUG_C_SPLINE
			cout<<endl<<"Warning: no new data points / spline found"<<endl;
#endif
			break;
		}
		//add last found polynom
#ifdef DEBUG_C_SPLINE
		cout<<endl<<"add last found polynom:"<<endl;
		actualPolynom.print( cout );
#endif
		dLastErrorSum += errorSumActualPolynom;
		//add actual polynom to the spline
		if ( ! vecPolynoms.empty() ){
			//add next not found data point to border
#ifdef DEBUG_C_SPLINE
			cout<<endl<<"Add border: "<< vecData[ ulIndexDataPointActualPolynomStart ].x <<endl;
#endif
			vecBorders.push_back( vecData[ ulIndexDataPointActualPolynomStart - 1 ].x );
		}//else don't add border point for last spline for the data points
		vecPolynoms.push_back( actualPolynom );
		
		ulIndexDataPointActualPolynomStart = ulIndexLastGoodDataPoint + 1;
	}//end while some points missing in the spline
	
	if ( ulIndexLastGoodDataPoint == 0 ){
		vecPolynoms = vecOldPolynoms;
		vecBorders  = vecOldBorders;
	}
#ifdef DEBUG_C_SPLINE
	cout<<"actual spline: ";
	print( cout );
	cout<<"cSpline<tX, tY>::evalueSpline( vecInputData, uiMaxNumberOfParameters="<<
		uiMaxNumberOfParameters<<" , maxValue="<<maxValue<<
		", maxError="<<maxError<<" ,dMaxErrorPerValue="<<
		dMaxErrorPerValue<<" ) done; points matched: "<<(ulIndexLastGoodDataPoint + 1)<<endl;
#endif
	return ulIndexLastGoodDataPoint;
}


#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING

/**
 * This functions evalues a spline, which matches all points of the
 * given range data vecData (if possible).
 * The y value, to wich the spline evalues the x value, will be in the
 * bound of the range data point, so that:
 * 	vecData[i].minY <= spline( vecData[i].x ) + error_i <= vecData[i].maxY,
 * 	with maxError <= sum error_i
 * 	for i = 0 till vecData.size()
 *
 * The evalued spline (this spline) consists of a number of polynoms
 * seperated by border points.
 * The evalued polynoms (@see cPolynom) will have the form:
 * 	y = vecFactors[ 0 ] + vecFactors[ 1 ] * x +
 * 	vecFactors[ 2 ] * x^2 + ... +
 * 	vecFactors[ uiNumberOfParameters - 1 ] *
 * 		x^(uiNumberOfParameters - 1)
 * The upper border point of a polynom is the first point at wich the
 * polynom dosn't match the given data vecData anymore.
 *
 * The method will iterativ increase the number of parameters for the
 * polynoms (from 1 to uiMaxNumberOfParameters) and will try to not use
 * all of the given range points to find the polynoms.
 *
 * @see evalue()
 * @see cPolynom::evalueSplineIterativFast()
 * @param vecInputData the data which the returend spline should match
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
 * 	the evalued spline will allways have parameters vecFactors[i] with
 * 	-1 * maxValue <= vecFactors[i] <= maxValue for 0 <= i \< vecFactors.size()
 * @param maxError the maximal error for the spline to find;
 * 	the error on the interpolated spline for vecData will be equal or
 * 	less than maxError
 * @param ulMaxMemoryCost a number for the maximum memory cost this
 * 	method is allowed to use; if 0 the maximum memory cost is unbounded
 * @return the number n of data points vecData, which the spline matches;
 * 	the data points vecData[0] to vecData[ return - 1 ] will be
 * 	matched by the spline
 */
template<class tX, class tY> unsigned long fib::algorithms::nD1::cSpline<tX, tY>::
	evalueSpline(
		const vector< cDataPointRange< tX, tY> > & vecInputData,
		unsigned int uiMaxNumberOfParameters,
		const unsigned int uiMinBitsToStoreMantissa,
		const tY maxValue,
		const tY maxError,
		const unsigned long ulMaxMemoryCost ){
	
#ifdef DEBUG_C_SPLINE
	cout<<"cSpline<tX, tY>::evalueSpline( vecInputData, uiMaxNumberOfParameters="<<
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
	
	vector< cPolynom< tX, tY> > vecOldPolynoms( vecPolynoms );
	vector< tY > vecOldBorders( vecBorders );
	
	vecPolynoms.clear();
	vecBorders.clear();
	
	unsigned long ulFirstPointNotMatched = 0;
	tY lastErrorSum = 0;
	
	while ( ulFirstPointNotMatched < ulNumberOfDataPoints ){
		//while some points missing in the spline
		
		/*map with the last errors for the to approximate range data points;
		Elements:
			- error for the range data point
			- the range data point*/
		multimap< tY, const cDataPointRange< tX, tY > * > mmapActualPointErrors;
		tY actualErrorSum = lastErrorSum;
		
		set< const cDataPointRange< tX, tY > * > setPointsIntegratedLastTime;
		
		unsigned int uiNumberOfActualParameters = 0;
		
		cPolynom<tX, tY> actualPolynom;
		
		unsigned long ulNumberOfActualPoints = vecData.size();
			
		cPolynom<tX, tY> lastCorrectPolynom;
		lastCorrectPolynom.vecFactors.push_back( 0 );
		unsigned long ulNumberOfMaxPointsMatched = ulFirstPointNotMatched;
		unsigned long ulFirstPointNotMatchebel = vecData.size();
		
		cHyperplaneBody< tY > * pHyperplaneBody = NULL;
		
#ifdef DEBUG_C_SPLINE
		cout<<endl<<"Trying to find a new polynom beginning at point "<<
			ulFirstPointNotMatched<<" (actual error="<<actualErrorSum<<")."<<endl;
#endif
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
#ifdef DEBUG_C_SPLINE
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
#ifdef DEBUG_C_SPLINE
					cout<<"evaluing points to integrate at the start"<<endl;
#endif
					set< size_t > setPointToAddIndexes;
					vecPointsToAdd.push_back( &( vecData[ ulFirstPointNotMatched ] ) );
					setPointToAddIndexes.insert( ulFirstPointNotMatched );
					if ( ulFirstPointNotMatched + 1 < vecData.size() ){
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
					reduce the error and create the polynom*/
#ifdef DEBUG_C_SPLINE
					cout<<"using points, wich wher integrated in the last hyperbody to integrate at the start"<<endl;
#endif
					vecPointsToAdd = vector< const cDataPointRange< tX, tY > * >(
						setPointsIntegratedLastTime.begin(), setPointsIntegratedLastTime.end() );
				}
				//fill mmapActualPointErrors
				set< const cDataPointRange< tX, tY > * > setPointsToAdd(
					vecPointsToAdd.begin(), vecPointsToAdd.end() );
				mmapActualPointErrors.clear();
				for ( size_t uiActualDataPoint = ulFirstPointNotMatched;
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
				//error on actual points to hight
				ulFirstPointNotMatchebel = ulNumberOfActualPoints;
				//decrase number of actual points
				unsigned long ulDeltaPoints =
					(ulNumberOfActualPoints - ulNumberOfMaxPointsMatched) / 2;
				if ( ( ulDeltaPoints <= 1 ) && ( 1 < uiNumberOfActualParameters ) &&
						( ulFirstPointNotMatched < ulNumberOfMaxPointsMatched ) ){
					//no big improvement to the last best polynom
#ifdef DEBUG_C_SPLINE1
					cout<<"error to great on last iteration, but no big improvement to the last best polynom "<<
						"( decrase number of actual points from "<<ulNumberOfActualPoints<<
						" to "<<(ulNumberOfActualPoints - ulDeltaPoints)<<
						" for polynom with "<<uiNumberOfActualParameters<<" parameters)"<<endl;
#endif
					bStopEvaluation = true;
					break;
				}
				if ( ulDeltaPoints == 0 ){
					//be shure to decrase the ulNumberOfActualPoints
					ulDeltaPoints = 1;
				}
#ifdef DEBUG_C_SPLINE
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
				vecPointsToAdd.push_back( &( vecData[ ulFirstPointNotMatched ] ) );
				setPointToAddIndexes.insert( ulFirstPointNotMatched );
				if ( ulFirstPointNotMatched + 1 < ulNumberOfActualPoints ){
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
				for ( size_t uiActualDataPoint = ulFirstPointNotMatched;
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
#ifdef DEBUG_C_SPLINE
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
					
					const tY dPolynomValue = actualPolynom.evalue(
						vecData[ uiActualDataPoint ].x );
					
					tY errorOfActualPoint = 0;
					if ( dPolynomValue < vecData[ uiActualDataPoint ].minY ){
						//the actual point is not matched by the spline
						errorOfActualPoint = vecData[ uiActualDataPoint ].minY - dPolynomValue;
						actualErrorSum += errorOfActualPoint;
						
					}else if ( vecData[ uiActualDataPoint ].maxY < dPolynomValue ){
						//the actual point is not matched by the spline
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
#ifdef DEBUG_C_SPLINE
				cout<<"add "<<vecPointsToAdd.size()<<" vecPointsToAdd points to match to hyperbody"<<endl;
#endif
				for ( typename vector< const cDataPointRange< tX, tY > * >::const_iterator
						itrDataPoint = vecPointsToAdd.begin();
						itrDataPoint != vecPointsToAdd.end(); itrDataPoint++ ){
					//for every range data point
					
					//create the inequiations for the range data point
					const pair< cInequation< tY >, cInequation< tY > >
						paIneqiuations = actualPolynom.createInequiationsForRangePoint(
							(**itrDataPoint), uiNumberOfActualParameters );
					
					//try to add the inequiations for the range data point
					bool bDataPointAdded = pHyperplaneBody->addInequiation(
						paIneqiuations.first );
#ifdef DEBUG_C_SPLINE
					cout<<"Actual range data point ("<<(**itrDataPoint).x<<
						","<<(**itrDataPoint).minY<<" till "<<
						(**itrDataPoint).maxY<<") "<<
						(bDataPointAdded?"added":"not added")<<", with inequiation:"<<endl;
					paIneqiuations.first.print( cout );
#endif
#ifdef DEBUG_PRINT_HYPERBODY
					cout<<"new hyperbody after adding first inequiation:"<<endl;
					pHyperplaneBody->print( cout );
#endif
					if ( bDataPointAdded ){
						bDataPointAdded &= pHyperplaneBody->addInequiation(
							paIneqiuations.second );
#ifdef DEBUG_C_SPLINE
						cout<<"Actual range data point ("<<(**itrDataPoint).x<<
							","<<(**itrDataPoint).minY<<" till "<<
							(**itrDataPoint).maxY<<") "<<
							(bDataPointAdded?"added":"not added")<<", with inequiations:"<<endl;
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
#ifdef DEBUG_C_SPLINE
					cout<<"Border points in hyperplane: "<<pHyperplaneBody->getNumberOfBorderPoints()<<endl;
#endif
					if ( ( ulMaxMemoryCost != 0) &&
							( ulMaxMemoryCost < pHyperplaneBody->getNumberOfBorderPoints() ) ){
						//the evaluation casts to much memory -> stop it
#ifdef DEBUG_C_SPLINE
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
				
				actualErrorSum = lastErrorSum;
				mmapActualPointErrors.clear();
				unsigned long ulMatchedPoints = ulFirstPointNotMatched;
				//check if this spline approximate more than the ulPointsAdded points
				for ( size_t uiActualPoint = ulFirstPointNotMatched;
						uiActualPoint < ulNumberOfActualPoints; uiActualPoint++ ){
					//check if next data point is approximated by the spline
					const cDataPointRange< tX, tY > & dataPoint =
						vecData[ uiActualPoint ];
					
					const tY dPolynomValue = actualPolynom.evalue( dataPoint.x );
			
					tY errorOfActualPoint = 0;
					if ( dPolynomValue < dataPoint.minY ){
						//the actual point is not matched by the spline
						errorOfActualPoint = dataPoint.minY - dPolynomValue;
						actualErrorSum += errorOfActualPoint;
						
					}else if ( dataPoint.maxY < dPolynomValue ){
						//the actual point is not matched by the spline
						errorOfActualPoint = dPolynomValue - dataPoint.maxY;
						actualErrorSum += errorOfActualPoint;
					}
					if ( actualErrorSum <= maxError ){
						//the actual point is matched by the spline
						ulMatchedPoints++;
					}//else the actual point isn't matched by the spline
					if ( ( errorOfActualPoint != 0 ) &&
							( setPointsIntegratedLastTime.find( & dataPoint ) ==
								setPointsIntegratedLastTime.end() ) ){
						//map to points to check for error
						mmapActualPointErrors.insert( make_pair(
							errorOfActualPoint, & dataPoint ) );
					}
				}
				
#ifdef DEBUG_C_SPLINE
				cout<<"error of the actual polynom: "<<actualErrorSum<<endl;
#endif
				if ( ( actualErrorSum <= maxError ) &&
						( ulNumberOfMaxPointsMatched < ulMatchedPoints ) ){
					lastCorrectPolynom = actualPolynom;
					ulNumberOfMaxPointsMatched = ulMatchedPoints;
#ifdef DEBUG_C_SPLINE
					cout<<"storing actual polynom as last correct polynom "<<endl;
					lastCorrectPolynom.print( cout );
#endif
					if ( mmapActualPointErrors.size() == ulFirstPointNotMatchebel ){
						/*if all matchebel points are matched -> done*/
#ifdef DEBUG_C_SPLINE
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
#ifdef DEBUG_C_SPLINE
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
#ifdef DEBUG_C_SPLINE
				const tY actualError = itrBiggestErrorPoint->first;
				cout<<"biggest error: "<<actualError<<endl<<flush;
#endif
				if ( itrBiggestErrorPoint->first == 0 ){
					//no points with error exists
#ifdef DEBUG_C_SPLINE
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
					paIneqiuations = actualPolynom.createInequiationsForRangePoint(
						dataPoint, uiNumberOfActualParameters );
				
				//try to add the inequiations for the range data point
				bool bDataPointAdded = pHyperplaneBody->addInequiation(
					paIneqiuations.first );
#ifdef DEBUG_C_SPLINE
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
#ifdef DEBUG_C_SPLINE
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
#ifdef DEBUG_C_SPLINE
				cout<<"Border points in hyperplane:"<<pHyperplaneBody->getNumberOfBorderPoints()<<endl;
#endif
				if ( ( ulMaxMemoryCost != 0) &&
						( ulMaxMemoryCost < pHyperplaneBody->getNumberOfBorderPoints() ) ){
					//the evaluation casts to much memory -> stop it
#ifdef DEBUG_C_SPLINE
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
				
				actualErrorSum = lastErrorSum;
				mmapActualPointErrors.clear();
				unsigned long ulMatchedPoints = ulFirstPointNotMatched;
				//check if this spline approximate more than the ulPointsAdded points
				for ( size_t uiActualPoint = ulFirstPointNotMatched;
						uiActualPoint < ulNumberOfActualPoints; uiActualPoint++ ){
					//check if next data point is approximated by the spline
					const cDataPointRange< tX, tY > & dataPoint =
						vecData[ uiActualPoint ];
					
					const tY dPolynomValue = actualPolynom.evalue( dataPoint.x );
			
					tY errorOfActualPoint = 0;
					if ( dPolynomValue < dataPoint.minY ){
						//the actual point is not matched by the spline
						errorOfActualPoint = dataPoint.minY - dPolynomValue;
						actualErrorSum += errorOfActualPoint;
						
					}else if ( dataPoint.maxY < dPolynomValue ){
						//the actual point is not matched by the spline
						errorOfActualPoint = dPolynomValue - dataPoint.maxY;
						actualErrorSum += errorOfActualPoint;
					}
					if ( actualErrorSum <= maxError ){
						//the actual point is matched by the spline
						ulMatchedPoints++;
					}//else the actual point isn't matched by the spline
					if ( ( errorOfActualPoint != 0 ) &&
							( setPointsIntegratedLastTime.find( & dataPoint ) ==
								setPointsIntegratedLastTime.end() ) ){
						//map to points to check for error
						mmapActualPointErrors.insert( make_pair(
							errorOfActualPoint, & dataPoint ) );
					}
				}
#ifdef DEBUG_C_SPLINE
				cout<<"error of the actual polynom after adding error point: "<<actualErrorSum<<endl;
#endif
				if ( ( actualErrorSum <= maxError ) &&
						( ulNumberOfMaxPointsMatched < ulMatchedPoints ) ){
					lastCorrectPolynom = actualPolynom;
					ulNumberOfMaxPointsMatched = ulMatchedPoints;
#ifdef DEBUG_C_SPLINE
					cout<<"storing actual polynom as last correct spline "<<endl;
					lastCorrectPolynom.print( cout );
#endif
					if ( mmapActualPointErrors.size() == ulFirstPointNotMatchebel ){
						/*if all matchebel points are matched -> done*/
#ifdef DEBUG_C_SPLINE
						cout<<"all points are matched -> done"<<endl;
#endif
						bStopEvaluation = true;
					}
					break;
				}
			}
#ifdef DEBUG_C_SPLINE
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
#ifdef DEBUG_C_SPLINE
		cout<<"evaluing next spline polynom done "<<endl;
#endif
		if ( pHyperplaneBody ){
			delete pHyperplaneBody;
		}
		
#ifdef DEBUG_C_SPLINE
		cout<<"adding range data points wich fulfill this spline"<<endl;
#endif
		actualErrorSum = lastErrorSum;
		unsigned long ulMatchedPoints = ulFirstPointNotMatched;
		//check if this spline approximate more than the ulPointsAdded points
		while ( ulMatchedPoints < ulNumberOfDataPoints ){
			//check if next data point is approximated by the spline
			
			const cDataPointRange< tX, tY > & dataPoint =
				vecData[ ulMatchedPoints ];
			
			const tY dSplineValue = lastCorrectPolynom.evalue( dataPoint.x );
			
			tY actualPointError = 0.0;
			if ( dSplineValue < dataPoint.minY ){
				//the actual point is not matched by the spline
				actualPointError = dataPoint.minY - dSplineValue;
				
			}else if ( dataPoint.maxY < dSplineValue ){
				//the actual point is not matched by the spline
				actualPointError = dSplineValue - dataPoint.maxY;
			}
			if ( maxError < (actualErrorSum + actualPointError) ){
				break;
			}/*else the actual point is matched by the spline
			-> treat it as added*/
			actualErrorSum += actualPointError;
			ulMatchedPoints++;
		}
		if ( ulFirstPointNotMatched < ulMatchedPoints ){
			//add new found polynom
			if ( ! vecPolynoms.empty() ){
				vecBorders.push_back( vecData[ ulFirstPointNotMatched ].x );
			}
#ifdef DEBUG_C_SPLINE
			cout<<"Adding polynom for points "<<ulFirstPointNotMatched<<
				" to "<<ulMatchedPoints<<" from border ";
			if ( ! vecPolynoms.empty() ){
				cout<<vecData[ ulFirstPointNotMatched ].x<<": ";
			}else{
				cout<<"negativ infinity: ";
			}
			lastCorrectPolynom.print( cout );
#endif
			vecPolynoms.push_back( lastCorrectPolynom );
			vecPolynoms.back().vecFactors = lastCorrectPolynom.vecFactors;
			
			ulFirstPointNotMatched = ulMatchedPoints;
			lastErrorSum = actualErrorSum;
		}else{//error no points matched
#ifdef DEBUG_C_SPLINE
			cout<<"Not enough new points added for new polynom. Old points matched "<<
				ulFirstPointNotMatched<<", but new points matched "<<ulMatchedPoints<<
				" . Stopping evaluation of more polynoms."<<endl;
#endif
			break;
		}
	}//end while some points missing
	
	if ( ulFirstPointNotMatched == 0 ){
		vecPolynoms = vecOldPolynoms;
		vecBorders  = vecOldBorders;

	}
#ifdef DEBUG_C_SPLINE
	cout<<"actual spline: ";
	print( cout );
	cout<<"cSpline<tX, tY>::evalueSpline( vecData, uiMaxNumberOfParameters="<<
		uiMaxNumberOfParameters<<", uiMinBitsToStoreMantissa="<<
		uiMinBitsToStoreMantissa<<", maxValue="<<maxValue<<
		", maxError="<<maxError<<" ,ulMaxMemoryCost="<<
		ulMaxMemoryCost<<" ) done; points matched: "<<ulFirstPointNotMatched<<endl;
#endif
	return ulFirstPointNotMatched;
}

#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING


/**
 * @param dataPoint the spline to compare this spline with
 * @return true if the given spline is equal to this, else false
 * 	(@see x, @see y)
 */
template<class tX, class tY> bool fib::algorithms::nD1::cSpline<tX, tY>::
		operator==( const cSpline<tX, tY> & spline ) const{
	
	return ( vecPolynoms == spline.vecPolynoms ) &&
		( vecBorders == spline.vecBorders );
}


/**
 * @param dataPoint the spline to compare this spline with
 * @return true if the given spline is not equal to this, else false
 * 	(@see x, @see y)
 */
template<class tX, class tY> bool fib::algorithms::nD1::cSpline<tX, tY>::
		operator!=( const cSpline<tX, tY> & spline ) const{
	
	return ! ( (*this) == spline );
}



/**
 * @return the a const pointer to the vector with the polynoms of this
 * 	spline (@see vecPolynoms)
 */
template<class tX, class tY> const vector< cPolynom< tX, tY> > *
		fib::algorithms::nD1::cSpline<tX, tY>::getPolynoms() const{
	
	return & vecPolynoms;
}


/**
 * @return the a const pointer to the vector with the borders of this
 * 	spline (@see vecBorders)
 */
template<class tX, class tY> const vector< tY > *
		fib::algorithms::nD1::cSpline<tX, tY>::getBorders() const{
	
	return & vecBorders;
}


//protected:


/**
 * This function generates an subfunction for the given part spline
 * as an balanced tree of if subfunctions.
 *
 * @param vecInPolynoms the vector with the polynoms for the splines
 * 	@see vecPolynoms
 * @param vecInBorders the vector with the borders for the splines
 * 	@see vecBorders
 * @param pVariable the variable (x) for the spline
 * @return the subfunction for the given spline
 */
template<class tX, class tY> cUnderFunction *
	fib::algorithms::nD1::cSpline<tX, tY>::generateSubfunctionTree(
		const vector< const cPolynom< tX, tY> * > & vecInPolynoms,
		const vector< tY > & vecInBorders,
		cFibVariable * pVariable ) const{
	
	const unsigned int uiNumberOfPolynoms = vecInPolynoms.size();
	if ( uiNumberOfPolynoms == 0 ){
		return NULL;
	}//else
	if ( uiNumberOfPolynoms == 1 ){
		return vecInPolynoms[ 0 ]->toFibUnderFunction( pVariable );
	}//else
	//seperate the polynoms into two sets of nearky equal size
	
	const unsigned int uiIndexMiddlePolynom = uiNumberOfPolynoms / 2 - 1;
	
	vector< const cPolynom< tX, tY> * > vecPolynomsLower;
	vector< tY > vecBordersLower;
	vector< const cPolynom< tX, tY> * > vecPolynomsHigher;
	vector< tY > vecBordersHigher;
	
	for ( unsigned int uiActualPolynom = 0;
			uiActualPolynom < uiIndexMiddlePolynom; uiActualPolynom++ ){
		
		vecPolynomsLower.push_back( vecInPolynoms[ uiActualPolynom ] );
		vecBordersLower.push_back( vecInBorders[ uiActualPolynom ] );
	}
	vecPolynomsLower.push_back( vecInPolynoms[ uiIndexMiddlePolynom ] );
	
	for ( unsigned int uiActualPolynom = uiIndexMiddlePolynom + 1;
			uiActualPolynom < uiNumberOfPolynoms - 1; uiActualPolynom++ ){
		
		vecPolynomsHigher.push_back( vecInPolynoms[ uiActualPolynom ] );
		vecBordersHigher.push_back( vecInBorders[ uiActualPolynom ] );
	}
	vecPolynomsHigher.push_back( vecInPolynoms[ uiNumberOfPolynoms - 1 ] );
	
	cCondition * pBorderConditionMiddle = new cConditionLower(
		new cFunctionVariable( pVariable ),
		new cFunctionValue( vecInBorders[ uiIndexMiddlePolynom ] ) );
	
	cUnderFunction * pFunctionLower  = generateSubfunctionTree( vecPolynomsLower, vecBordersLower, pVariable );
	cUnderFunction * pFunctionHigher = generateSubfunctionTree( vecPolynomsHigher, vecBordersHigher, pVariable );
	
	return new cFunctionIf( pBorderConditionMiddle, pFunctionLower, pFunctionHigher );
}





#endif //___N_D_1_C_SPLINE_CPP__
















