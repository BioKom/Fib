/**
 * @file cSpline
 * file name: cSpline.h
 * @author Betti Oesterholz
 * @date 25.06.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for a one dimensional spline.
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
 * This header specifies a class for a one dimensional spline.
 * A spline is a interpolation of a function by polynome (@see cPolynom).
 * The second template parameter should always be a floating point datatype.
 *
 */
/*
History:
25.06.2011  Oesterholz  created
24.09.2012  Oesterholz  FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING:
	evalueSpline(): the glp library (extern package) linear solver will be
	used to find a spline for a vector of range data points
*/

#ifndef ___N_D_1_C_SPLINE_H__
#define ___N_D_1_C_SPLINE_H__

#include "version.h"

#include "nD1.h"
#include "cDataPoint.h"
#include "cPolynom.h"
#include "cOneAryFunction.h"

#include "cUnderFunction.h"
#include "cFibVariable.h"

#include <vector>

using namespace fib;
using namespace fib::algorithms::nLinearInequation;


namespace fib{

namespace algorithms{

namespace nD1{

template <class tX, class tY>
class cSpline: public cOneAryFunction<tX, tY>{

#ifdef TEST
public:
#else //TEST
protected:
#endif //TEST
	/**
	 * The the polynomes of the spline.
	 * The interpolate the function betwean ther borders.
	 * The i'th polynom vecPolynoms[ i ] interpolats the function betwaen
	 * the border i - 1 vecBorders[ i-1 ] (inclusive it) to border i
	 * vecBorders[ i ] (exclusive it).
	 * The first and last polynom are unbound.
	 * So ther have to be one border less as ther are splines.
	 * @see cPolynom
	 * @see vecBorders
	 * @see evalue()
	 */
	vector< cPolynom< tX, tY> > vecPolynoms;

	/**
	 * The the borders for the polynoms of the spline.
	 * The interpolate the function betwean ther borders.
	 * The i'th polynom vecPolynoms[ i ] interpolats the function betwaen
	 * the border i - 1 vecBorders[ i-1 ] (inclusive it) to border i
	 * vecBorders[ i ] (exclusive it).
	 * The first and last polynom are unbound.
	 * So ther have to be one border less as ther are splines.
	 * All borders have to be sorted in increasing order.
	 * 	vecBorders[ i ] \< vecBorders[ i + 1 ]
	 * @see vecPolynoms
	 * @see evalue()
	 */
	vector< tY > vecBorders;


public:


	/**
	 * Standartconstructor
	 */
	cSpline();
	
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
	virtual tY evalue( const tX & x ) const;

	/**
	 * This method prints this spline to the given stream.
	 *
	 * @param outputStream the stream wher to print this spline to
	 */
	virtual void print( ostream & outputStream ) const;
	
	/**
	 * This method evalues the error of the given datapoints to the values
	 * this spline evalues to.
	 *
	 * The evaluation of the spline will be done by evalue().
	 * The error will just be counted, if it is greater than the SAVE_BOUNDERY.
	 * @see evalue()
	 *
	 * @param vecInputData the data for wich the error is to evalue
	 * @return a pair with two values:
	 * 	- the first value is the number of datapoints evalued wrong
	 * 	- the second value is the sum of the error of all datapoints
	 */
	virtual pair<unsigned long, tY> evalueError(
		const vector< cDataPoint< tX, tY> > & vecInputData ) const;

	/**
	 * This method evalues the error of the given datapoints to the values
	 * this spline evalues to.
	 * This function will stop the evaluation, if the maximum error maxYError
	 * was reached.
	 *
	 * The evaluation of the spline will be done by evalue().
	 * The error will just be counted, if it is greater than the SAVE_BOUNDERY.
	 * @see evalue()
	 *
	 * @param vecInputData the data for wich the error is to evalue
	 * @param maxYError the maximum error, at which the evaluation should stop;
	 * 	if maxYError is 0 the maximum error is unlimeted
	 * @return the sum of the error of all datapoints, but maximal maxYError
	 */
	virtual tY evalueErrorMax( const vector< cDataPoint< tX, tY> > & vecData,
		const tY maxYError ) const;

	/**
	 * This method evalues the error of the given range datapoints to the
	 * values this spline evalues to.
	 *
	 * The evaluation of the spline will be done by evalue().
	 * A datapoint has an error, if it lay outside the datpoint range. The
	 * error is it's distance to the neares datapoint boundery.
	 * The error will just be counted, if it is greater than the SAVE_BOUNDERY.
	 * @see evalue()
	 *
	 * @param vecInputData the data for wich the error is to evalue
	 * @return a pair with two values:
	 * 	- the first value is the number of datapoints evalued wrong
	 * 	- the second value is the sum of the error of all datapoints
	 */
	virtual pair<unsigned long, tY> evalueError(
		const vector< cDataPointRange< tX, tY> > & vecInputData ) const;

	/**
	 * This method evalues the error of the given datapoints to the values
	 * this spline evalues to.
	 * This function will stop the evaluation, if the maximum error maxYError
	 * was reached.
	 *
	 * The evaluation of the spline will be done by evalue().
	 * A datapoint has an error, if it lay outside the datpoint range. The
	 * error is it's distance to the neares datapoint boundery.
	 * The error will just be counted, if it is greater than the SAVE_BOUNDERY.
	 * @see evalue()
	 *
	 * @param vecInputData the data for wich the error is to evalue
	 * @param maxYError the maximum error, at which the evaluation should stop;
	 * 	if maxYError is 0 the maximum error is unlimeted
	 * @return the sum of the error of all datapoints, but maximal maxYError
	 */
	virtual tY evalueErrorMax( const vector< cDataPointRange< tX, tY> > & vecData,
		const tY maxYError ) const;
	
	/**
	 * This method converts this spline, into an fib-underfunction.
	 * Beware: You have to delete the returned fib-underfunction.
	 *
	 * @param pVariable the variable (x) for the spline
	 * @return a pointer to the fib-underfunction, wich represents the
	 * 	same spline as this spline
	 */
	virtual cUnderFunction * toFibUnderFunction(
			cFibVariable * pVariable ) const;


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
	virtual bool evalue( const vector< cDataPoint< tX, tY> > & vecData );
	
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
	virtual unsigned long evalueSpline(
		const vector< cDataPointRange< tX, tY> > & vecInputData,
		unsigned int uiMaxNumberOfParameters = 4,
		const tY maxValue = 1E+36,
		const tY maxError = 0,
		const tY maxErrorPerValue = 0,
		const double dWeightParameter = 0.0000000001 );

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
	virtual unsigned long evalueSpline(
		const vector< cDataPointRange< tX, tY> > & vecInputData,
		unsigned int uiMaxNumberOfParameters = 4,
		const unsigned int uiMinBitsToStoreMantissa = 1,
		const tY maxValue = 1E+36,
		const tY maxError = 0,
		const unsigned long ulMaxMemoryCost = 0 );

#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING


	/**
	 * @param dataPoint the spline to compare this spline with
	 * @return true if the given spline is equal to this, else false
	 * 	(@see x, @see y)
	 */
	virtual bool operator==( const cSpline<tX, tY> & spline ) const;

	/**
	 * @param dataPoint the spline to compare this spline with
	 * @return true if the given spline is not equal to this, else false
	 * 	(@see x, @see y)
	 */
	virtual bool operator!=( const cSpline<tX, tY> & spline ) const;

	/**
	 * @return the a const pointer to the vector with the polynoms of this
	 * 	spline (@see vecPolynoms)
	 */
	const vector< cPolynom< tX, tY> > * getPolynoms() const;
	
	/**
	 * @return the a const pointer to the vector with the borders of this
	 * 	spline (@see vecBorders)
	 */
	const vector< tY > * getBorders() const;

/*TODO
	cPolynom * getPolynom( unsigned int uiNumber )
	tY getBorder( unsigned int uiNumber )
	
	bool setPolynom( unsigned int uiNumber, const cPolynom & polynome )
	bool setBorder( unsigned int uiNumber, const tY & border )
	
	
	 * Add border in correct position
	 *
	bool addPolynom( const cPolynom & polynome, const tY & border )
	
*/

protected:
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
	cUnderFunction * generateSubfunctionTree(
		const vector< const cPolynom< tX, tY> * > & vecInPolynoms,
		const vector< tY > & vecInBorders,
		cFibVariable * pVariable ) const;


};//end class cSpline
};//end namespace nD1
};//end namespace algorithms
};//end namespace fib

//include template implementation
#include "../src/cSpline.cpp"


#endif //___N_D_1_C_SPLINE_H__





