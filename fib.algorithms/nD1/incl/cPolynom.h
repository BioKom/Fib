/**
 * @file cPolynom
 * file name: cPolynom.h
 * @author Betti Oesterholz
 * @date 07.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies methods and functions for a one dimensional
 * polynom.
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
 * This header specifies methods and functions for a one dimensional
 * polynom functions.
 * The second template parameter should always be a floating point datatype.
 *
 */
/*
History:
07.06.2010  Oesterholz  created
12.02.2011  Oesterholz  method evalueSpline() added
27.03.2011  Oesterholz  method getLastFactorIndexNotNull() added
29.12.2012  Oesterholz  FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING:
	evalueSplineIterativFast(): the glp library (extern package) linear
	solver will be used to find a spline for a vector of range data points
30.04.2013  Oesterholz  evalueSplineIterativFast() for data points with
	weights for the solver and the error
08.05.2013  Oesterholz  method reduceBits() added
*/

#ifndef ___FIB__ALGORITHMS__N_D_1_C_POLYNOM_H__
#define ___FIB__ALGORITHMS__N_D_1_C_POLYNOM_H__

#include "version.h"

#include "nD1.h"
#include "cDataPoint.h"
#include "cDataPointRange.h"
#include "cLinearEquation.h"
#include "cOneAryFunction.h"
#include "cInequation.h"

#include "cUnderFunction.h"
#include "cFibVariable.h"

#include <vector>

using namespace fib;
using namespace fib::algorithms::nLinearInequation;


namespace fib{

namespace algorithms{

namespace nD1{

template <class tX, class tY>
	class cDataPointRangeWithWeights: public cDataPointRange< tX, tY>{
public:
	/**
	 * The weight for the error value for the point in the optimize function,
	 * when evaluing the factors.
	 */
	double dWeightSolver;
	
	/**
	 * The weight for the error on the point.
	 */
	double dWeightError;
	
	/**
	 * standard constructor for a data point
	 *
	 * @param inX the @see x value for the datapoint
	 * @param inMinY the @see minY value for the datapoint
	 * @param inMaxY the @see maxY value for the datapoint
	 * @param dInWeightSolver the weight for the error value for the point
	 * 	in the optimize function @see dWeightSolver
	 * @param dInWeightError the weight for the error on the point
	 * 	@see dWeightError
	 */
	cDataPointRangeWithWeights( const tX inX = 0,
			const tY inMinY = 0, const tY inMaxY = 0,
			const double dInWeightSolver = 1.0, const double dInWeightError = 1.0 ):
		cDataPointRange< tX, tY>( inX, inMinY, inMaxY ),
		dWeightSolver( dInWeightSolver ), dWeightError( dInWeightError ){
		//nothing to do
	}
	
};//end class cDataPointRangeWithWeights


template <class tX, class tY>
class cPolynom: public cOneAryFunction<tX, tY>{

public:
	/**
	 * The factors for the polynom.
	 * @see evalue()
	 */
	vector< tY > vecFactors;

	/**
	 * Standartconstructor
	 */
	cPolynom();
	
	/**
	 * This method evalues the value of this polynom.
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
	virtual tY evalue( const tX & x ) const;

	/**
	 * This method prints this polynom to the given stream.
	 *
	 * @param outputStream the stream wher to print this polynom to
	 */
	virtual void print( ostream & outputStream ) const;
	
	/**
	 * This method evalues the error of the given datapoints to the values
	 * this polynom evalues to.
	 *
	 * The evaluation of the polynom will be done by evalue().
	 * The error will just be counted, if it is greater than the SAVE_BOUNDERY.
	 * @see evalue()
	 *
	 * @param vecInput the data for wich the error is to evalue
	 * @return a pair with two values:
	 * 	- the first value is the number of datapoints evalued wrong
	 * 	- the second value is the sum of the error of all datapoints
	 */
	virtual pair<unsigned long, tY> evalueError(
		const vector< cDataPoint< tX, tY> > & vecInput ) const;

	/**
	 * This method evalues the error of the given datapoints to the values
	 * this polynom evalues to.
	 * This function will stop the evaluation, if the maximum error maxYError
	 * was reached.
	 *
	 * The evaluation of the polynom will be done by evalue().
	 * The error will just be counted, if it is greater than the SAVE_BOUNDERY.
	 * @see evalue()
	 *
	 * @param vecInput the data for wich the error is to evalue
	 * @param maxYError the maximum error, at which the evaluation should stop;
	 * 	if maxYError is 0 the maximum error is unlimeted
	 * @return the sum of the error of all datapoints, but maximal maxYError
	 */
	virtual tY evalueErrorMax( const vector< cDataPoint< tX, tY> > & vecData,
		const tY maxYError ) const;
	
	/**
	 * This method checks the error of this polynom on the given data points.
	 *
	 * @param vecRangesForError the range data points which the polynom
	 * 	should match
	 * @param maxError the maximal error for the polynom;
	 * 	the error on the found polynom for vecRangesForError should be equal or
	 * 	less than maxError
	 * @param maxErrorPerValue the maximal error for the polynom to find on
	 * 	one data point; the error on the polynom for every data point
	 * 	in vecRangesForError should be equal or less than maxErrorPerValue
	 * @return true if the error is Ok, else false;
	 * 	the error is OK if the error sum on all data points is less than
	 * 	maxError and less than maxErrorPerValue on ever data point
	 */
	virtual bool checkError(
		const vector< fib::algorithms::nD1::cDataPointRange< tX, tY > > vecRangesForError,
		const tY maxError, const tY maxErrorPerValue ) const;

	/**
	 * This method evalues the error of the given range datapoints to the
	 * values this polynom evalues to.
	 *
	 * The evaluation of the polynom will be done by evalue().
	 * A datapoint has an error, if it lay outside the datpoint range. The
	 * error is it's distance to the neares datapoint boundery.
	 * The error will just be counted, if it is greater than the SAVE_BOUNDERY.
	 * @see evalue()
	 *
	 * @param vecInput the data for wich the error is to evalue
	 * @return a pair with two values:
	 * 	- the first value is the number of datapoints evalued wrong
	 * 	- the second value is the sum of the error of all datapoints
	 */
	virtual pair<unsigned long, tY> evalueError(
		const vector< cDataPointRange< tX, tY> > & vecInput ) const;

	/**
	 * This method evalues the error of the given datapoints to the values
	 * this polynom evalues to.
	 * This function will stop the evaluation, if the maximum error maxYError
	 * was reached.
	 *
	 * The evaluation of the polynom will be done by evalue().
	 * A datapoint has an error, if it lay outside the datpoint range. The
	 * error is it's distance to the neares datapoint boundery.
	 * The error will just be counted, if it is greater than the SAVE_BOUNDERY.
	 * @see evalue()
	 *
	 * @param vecInput the data for wich the error is to evalue
	 * @param maxYError the maximum error, at which the evaluation should stop;
	 * 	if maxYError is 0 the maximum error is unlimeted
	 * @return the sum of the error of all datapoints, but maximal maxYError
	 */
	virtual tY evalueErrorMax( const vector< cDataPointRange< tX, tY> > & vecData,
		const tY maxYError ) const;
	
	/**
	 * This function creats the linear equiations ( @see cLinearEquation )
	 * for the given datapoints.
	 * The linear equiations will have the form:
	 * 	vecData.y = x_0 + vecData.x * x_1 + vecData.x^2 * x_2 + ... +
	 * 		vecData.x^(uiMaxPolynomOrder - 1) * x_{uiMaxPolynomOrder - 1}
	 *
	 * @param vecData the with the datapoints, for which to evalue the
	 * 	linear equiations
	 * @param uiMaxPolynomOrder the maximal order of the polynom to generate
	 * 	the factor ranges for
	 * @return a vector with the linear equiations for the datapoints
	 */
	virtual vector< cLinearEquation<tY> > createLinearEquations(
		const vector< cDataPoint< tX, tY> > & vecData,
		unsigned int uiMaxPolynomOrder ) const;
	
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
	pair< cInequation< tY >, cInequation< tY > >
		createInequiationsForRangePoint(
			const cDataPointRange< tX, tY> & dataPoint,
			unsigned int uiPolynomOrder ) const;
	
	
	/**
	 * @return the index of the last factor, wich is not 0.
	 * 	(counting from 0, eg. if 0 is return the polynom is constant)
	 */
	long getLastFactorIndexNotNull() const;
	
	/**
	 * This method converts this polynom, into an fib -underfunction.
	 * Beware: You have to delete the returned fib -underfunction.
	 *
	 * @param pVariable the variable (x) for the polynom
	 * @return a pointer to the fib -underfunction, wich represents the
	 * 	same polynom as this polynom
	 */
	virtual cUnderFunction * toFibUnderFunction(
			cFibVariable * pVariable ) const;


	/**
	 * This function evalues the polynom for the given data.
	 * The evalued polynom will have the order n of the number of given
	 * datapoints.
	 *
	 * @param vecInputData the data for which to evalue the polynom
	 * @return if an polynom for the datapoints could be evalued, the factors
	 * 	of the evalued polynom in this polynom and true, else false
	 */
	virtual bool evalue( const vector< cDataPoint< tX, tY> > & vecInputData );
	
	/**
	 * This method trys to find a polynom for the given data vecData by
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
	 * @return the error of the best found function
	 * 	and the values of the evalued polynom in this polynom
	 */
	virtual tY findFunctionRand( const vector< cDataPointRange< tX, tY> > & vecInputData,
		unsigned long ulMaxIterations = 256 * 256 * 256 );
	
	/**
	 * This method evalues the a good polynom, which matches the given
	 * range data vecData.
	 * For this a polynom which evalues a low error on the given data point
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
	virtual tY evalueGoodPolynom(
		const vector< cDataPointRange< tX, tY> > & vecInputData,
		unsigned long ulTimeNeed = 1024 );

	/**
	 * This functions evalues a spline, which matches the given range vecInputData
	 * The vector vecData is the sorted vector vecInputData.
	 * vecData
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
	 * @see evalueSplineIterativFast()
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
	virtual unsigned long evalueSpline(
		const vector< cDataPointRange< tX, tY> > & vecInputData,
		unsigned int uiNumberOfParameters = 4,
		const unsigned int uiMinBitsToStoreMantissa = 1,
		const tY maxValue = 1E+36,
		const unsigned long ulMaxMemoryCost = 0 );


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
	 * 	be set to maxError * 2 / vecInputData.size()
	 * @param liWeightParameters a list with values for the weight of the
	 * 	parameters; with the weight value greater 0 it will be searched
	 * 	for a smaal parameter;
	 * 	the first element of the list is the weight for the first polynom
	 * 	factor / parameter, the second weight for the second factor and so
	 * 	on, the last n'th weight is for the n't factor and all that follow;
	 * 	if the weight list is empty the weights will be set to very smaal values;
	 * 	when searching for a solution the error is minimized and the
	 * 	spline parameter will be multiplied with this value and also minimized;
	 * 	when set to 1 a parameter increase of 1 is as bad as an error increase
	 * 	of 1, when set to 0.01 parameter increase of 100 is as bad an error increase
	 * 	of 1
	 * @return the number n of data points vecData, which the spline matches;
	 * 	the data points vecData[0] to vecData[ return - 1 ] will be
	 * 	matched by the spline
	 */
	virtual unsigned long evalueSplineIterativFast(
		const vector< cDataPointRange< tX, tY> > & vecInputData,
		unsigned int uiMaxNumberOfParameters = 4,
		const tY maxValue = 1E+36,
		const tY maxError = 0,
		const tY maxErrorPerValue = 0,
		const list< double > liWeightParameters = list< double >() );
	
	/**
	 * This functions evalues a spline, which matches all points of the
	 * given range data vecData (if possible).
	 * The y value, to wich the spline evalues the x value, will be in the
	 * bound of the range data point, so that:
	 * 	vecData[i].minY <= spline( vecData[i].x ) + error_i <= vecData[i].maxY,
	 * 	with maxError <= sum ( error_i * vecData[i].dWeightError )
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
	 * @see cPolynom::evalueSplineIterativFast()
	 * @param vecInputData the data which the returend spline should match,
	 * 	including the weight parameters for the data points;
	 * 	the dWeightError parameter influence how the error for the point
	 * 	is evalued (min difference to a point in the range multiplied by dWeightError);
	 * 	the dWeightSolver is the weight for the error given to the solver
	 * 	optimize function
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
	 * @param liWeightParameters a list with values for the weight of the
	 * 	parameters; with the weight value greater 0 it will be searched
	 * 	for a smaal parameter;
	 * 	the first element of the list is the weight for the first polynom
	 * 	factor / parameter, the second weight for the second factor and so
	 * 	on, the last n'th weight is for the n't factor and all that follow;
	 * 	if the weight list is empty the weights will be set to very smaal values;
	 * 	when searching for a solution the error is minimized and the
	 * 	spline parameter will be multiplied with this value and also minimized;
	 * 	when set to 1 a parameter increase of 1 is as bad as an error increase
	 * 	of 1, when set to 0.01 parameter increase of 100 is as bad an
	 * 	error increase of 1
	 * @return the number n of data points vecData, which the spline matches;
	 * 	the data points vecData[0] to vecData[ return - 1 ] will be
	 * 	matched by the spline
	 */
	virtual unsigned long evalueSplineIterativFast(
		const vector< cDataPointRangeWithWeights< tX, tY> > & vecInputData,
		unsigned int uiMaxNumberOfParameters = 4,
		const tY maxValue = 1E+36,
		const tY maxError = 0,
		const tY maxErrorPerValue = 0,
		const list< double > liWeightParameters = list< double >() );
	
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING

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
	 * The method should give the same result as evalueSpline() but faster.
	 * It will iterativ increase the number of parameters for the spline
	 * (from 1 to uiMaxNumberOfParameters) and will try to not use all of
	 * the given range points to find the polynom.
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
	virtual unsigned long evalueSplineIterativFast(
		const vector< cDataPointRange< tX, tY> > & vecInputData,
		unsigned int uiMaxNumberOfParameters = 4,
		const unsigned int uiMinBitsToStoreMantissa = 1,
		const tY maxValue = 1E+36,
		const tY maxError = 0,
		const unsigned long ulMaxMemoryCost = 0 );

#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
	
	//TODO check
	/**
	 * This method will try to reduce the bits of the parameters (beginning
	 * with the first parameter).
	 *
	 * @param vecRangesForError the range data points which the polynom
	 * 	should match
	 * @param maxValue the maximum possible value in all parameters
	 * 	the evalued spline will allways have parameters vecFactors[i] with
	 * 	-1 * maxValue <= vecFactors[i] <= maxValue for 0 <= i \< vecFactors.size()
	 * @param maxError the maximal error for the spline parameter to find;
	 * 	the error on the found spline for vecData will be equal or
	 * 	less than maxError (if it was equal or less befor)
	 * @param maxErrorPerValue the maximal error for the spline to find on
	 * 	one data point; the error on the interpolated spline for every data
	 * 	point in vecData will be equal or less than maxErrorPerValue
	 * 	(if it was equal or less befor);
	 * 	if maxErrorPerValue is 0 and maxError is not 0, maxErrorPerValue will
	 * 	be set to maxError * 2 / vecInputData.size()
	 */
	void reduceBits( const vector< fib::algorithms::nD1::cDataPointRange< tX, tY > >
			vecRangesForError,
		const tY maxValue, const tY maxError, const tY maxErrorPerValue );

	/**
	 * @param dataPoint the polynom to compare this polynom with
	 * @return true if the given polynom is equal to this, else false
	 * 	(@see x, @see y)
	 */
	virtual bool operator==( const cPolynom<tX, tY> & polynom ) const;

	/**
	 * @param dataPoint the polynom to compare this polynom with
	 * @return true if the given polynom is not equal to this, else false
	 * 	(@see x, @see y)
	 */
	virtual bool operator!=( const cPolynom<tX, tY> & polynom ) const;

	
};//end class cPolynom
};//end namespace nD1
};//end namespace algorithms
};//end namespace fib

//include template implementation
#include "../src/cPolynom.cpp"


#endif //___FIB__ALGORITHMS__N_D_1_C_POLYNOM_H__





