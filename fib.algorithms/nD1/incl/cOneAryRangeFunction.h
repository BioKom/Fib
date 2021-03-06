/**
 * @file cOneAryRangeFunction
 * file name: cOneAryRangeFunction.h
 * @author Betti Oesterholz
 * @date 15.07.2010
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
 * This header specifies a abstract class for a one ary functions which
 * factors lay in an range.
 *
 */
/*
History:
15.07.2010  Oesterholz  created
*/

#ifndef ___N_D_1_C_ONE_ARY_RANGE_FUNCTION_H__
#define ___N_D_1_C_ONE_ARY_RANGE_FUNCTION_H__

#include "version.h"

#include "nD1.h"
#include "cRangeFactor.h"
#include "cDataPointRange.h"
#include "cLinearConstrainFix.h"

#include "cUnderFunction.h"
#include "cFibVariable.h"

#include <vector>

using namespace fib::algorithms::nLinearInequation;
using namespace fib;

namespace fib{

namespace algorithms{

namespace nD1{

template <class tX, class tY>
class cOneAryRangeFunction{

public:

	/**
	 * This method prints the given this polynom to the given stream.
	 *
	 * @param outputStream the stream wher to print this polynom to
	 */
	virtual void print( ostream & outputStream ) const = 0;
	
	/**
	 * This functions evalues the ranges for the possible factors for a
	 * polynom which matches the given data vecData.
	 * The returned ranges don't have to include the factors for polynom
	 * which match the data, if ther isn't a possible polynome of the maximal
	 * range given for the data.
	 *
	 * @see evalue()
	 * @param vecData the data which the returend polynom should match
	 * @param uiMaxPolynomOrder the maximal order of the polynom to generate
	 * 	the factor ranges for
	 * @return ranges in which the factors of a polynom should lay, if
	 * 	possible (@see evalue()) in this cOneAryRangeFunction
	 */
	virtual void evalue(
		const vector< cDataPointRange< tX, tY> > & vecData,
		unsigned int uiMaxPolynomOrder ) = 0;
	
	
	/**
	 * @return the sum of the ranges of this function
	 */
	virtual tY getRangeSizeSum() const = 0;
	
	/**
	 * @return if the sum of the ranges of this function is 0
	 */
	virtual bool getRangeSizeSumIsNull() const = 0;

};//end class cOneAryRangeFunction
};//end namespace nD1
};//end namespace algorithms
};//end namespace fib



#endif //___N_D_1_C_ONE_ARY_RANGE_FUNCTION_H__
