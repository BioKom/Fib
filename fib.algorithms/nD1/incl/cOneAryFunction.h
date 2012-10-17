/**
 * @file cOneAryFunction
 * file name: cOneAryFunction.h
 * @author Betti Oesterholz
 * @date 15.076.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a abstract class for a one ary functions.
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
 * This header specifies a abstract class for a one ary functions.
 *
 */
/*
History:
15.07.2010  Oesterholz  created
*/

#ifndef ___N_D_1_C_ONE_ARY_FUNCTION_H__
#define ___N_D_1_C_ONE_ARY_FUNCTION_H__

#include "version.h"

#include "nD1.h"
#include "cDataPoint.h"
#include "cLinearEquation.h"

#include "cUnderFunction.h"
#include "cFibVariable.h"

#include <vector>

using namespace fib;

namespace fib{

namespace algorithms{

namespace nD1{

template <class tX, class tY>
class cOneAryFunction{

public:

	/**
	 * This method evalues the value of this function.
	 *
	 * @param x the input value for the function
	 * @return the evalued value f( x )
	 */
	virtual tY evalue( const tX & x ) const = 0;

	/**
	 * This method prints the given this function to the given stream.
	 *
	 * @param outputStream the stream wher to print this function to
	 */
	virtual void print( ostream & outputStream ) const = 0;
	
	/**
	 * This method evalues the error of the given datapoints to the values
	 * this function evalues to.
	 *
	 * The evaluation of the function will be done by evalue().
	 * The error will just be counted, if it is greater than the SAVE_BOUNDERY.
	 * @see evalue()
	 *
	 * @param vecInput the data for wich the error is to evalue
	 * @return a pair with two values:
	 * 	- the first value is the number of datapoints evalued wrong
	 * 	- the second value is the sum of the error of all datapoints
	 */
	virtual pair<unsigned long, tY> evalueError(
		const vector< cDataPoint< tX, tY> > & vecInput ) const = 0;

	/**
	 * This method evalues the error of the given datapoints to the values
	 * this function evalues to.
	 * This function will stop the evaluation, if the maximum error maxYError
	 * was reached.
	 *
	 * The evaluation of the function will be done by evalue().
	 * The error will just be counted, if it is greater than the SAVE_BOUNDERY.
	 * @see evalue()
	 *
	 * @param vecInput the data for wich the error is to evalue
	 * @param maxYError the maximum error, at which the evaluation should stop
	 * @return the sum of the error of all datapoints, but maximal maxYError
	 */
	virtual tY evalueErrorMax( const vector< cDataPoint< tX, tY> > & vecData,
		const tY maxYError ) const = 0;

	/**
	 * This method evalues the error of the given range datapoints to the
	 * values this function evalues to.
	 *
	 * The evaluation of the function will be done by evalue().
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
		const vector< cDataPointRange< tX, tY> > & vecInput ) const = 0;

	/**
	 * This method evalues the error of the given datapoints to the values
	 * this function evalues to.
	 * This function will stop the evaluation, if the maximum error maxYError
	 * was reached.
	 *
	 * The evaluation of the function will be done by evalue().
	 * A datapoint has an error, if it lay outside the datpoint range. The
	 * error is it's distance to the neares datapoint boundery.
	 * The error will just be counted, if it is greater than the SAVE_BOUNDERY.
	 * @see evalue()
	 *
	 * @param vecInput the data for wich the error is to evalue
	 * @param maxYError the maximum error, at which the evaluation should stop
	 * @return the sum of the error of all datapoints, but maximal maxYError
	 */
	virtual tY evalueErrorMax( const vector< cDataPointRange< tX, tY> > & vecData,
		const tY maxYError ) const = 0;
	
	/**
	 * This function converts this function, into an fib -underfunction.
	 * Beware: You have to delete the returned fib -underfunction.
	 *
	 * @param pVariable the variable (x) for the function
	 * @return a pointer to the fib -underfunction, wich represents the
	 * 	same function as this function
	 */
	virtual cUnderFunction * toFibUnderFunction(
			cFibVariable * pVariable ) const = 0;


	/**
	 * This function evalues the function for the given data.
	 * The evalued function will have the order n of the number of given
	 * datapoints.
	 *
	 * @param vecData the data for which to evalue the function
	 * @return if the function for the datapoints could be evalued: the
	 * 	factors of the evalued function in this function and true, else
	 * 	false and the factors of this function not changed
	 */
	virtual bool evalue( const vector< cDataPoint< tX, tY> > & vecData ) = 0;
	

	
};//end class cOneAryFunction
};//end namespace nD1
};//end namespace algorithms
};//end namespace fib



#endif //___N_D_1_C_ONE_ARY_FUNCTION_H__
