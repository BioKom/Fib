/**
 * @file cLinearConstrainFix
 * file name: cLinearConstrainFix.h
 * @author Betti Oesterholz
 * @date 08.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for a linear constrain.
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
 * This header specifies a class for a linear constrain.
 * The number of factors are fixed in this inequiations.
 * This constrain has the implicite form:
 * 	vecBounderyFactors[0] * yu_0 + ... + vecBounderyFactors[uiNumberOfDataPoints-1] * yu_{uiNumberOfDataPoints-1}
 * 	(bGreaterEqual ? <= : =>)
 * 	constant + vecFactors[0] * x_0 + ... + vecFactors[uiNumberOfFactors-1] * x_[uiNumberOfFactors-1}
 * 	(bGreaterEqual ? <= : =>)
 * 	vecBounderyFactors[0] * yo_0 + ... + vecBounderyFactors[uiNumberOfDataPoints-1] * yo_{uiNumberOfDataPoints-1}
 *
 * Wher:
 * 	- yu_i: are the lower bounderies for the y variables
 * 	- yo_i: are the upper bounderies for the y variables
 * 	- vecBounderyFactors[i]: is the factor for the lower and upper y factors
 * 	- bGreaterEqual: is a boolean, if the inequiation sign is greater equal "<="
 * 		( if bGreaterEqual == true ) or lower equal ">=" ( if bGreaterEqual == false )
 * 	- constant: is a constant factor for the linear inequiation
 * 	- vecFactors[k]: are the factors for the x variables
 *
 * The x and the y variables are not given. (In the common case they
 * should be evalued with the help of this constrain.)
 *
 * The y bounderies are for example implemented in @see cDataPointRange.
 * This linear constrain can represent a formular for the y values with
 * linear dependent factors. (like (yu <= f(x) <= yo ) with
 * (f(x)= a_0 * g_0(x) + ... + a_n * g_n(x)) and g_i(x) formulars that
 * only depend on x)
 *
 * This class is for easily handling this formulars.
 *
 */
/*
History:
08.06.2010  Oesterholz  created
*/

#ifndef ___C_LINEAR_CONSTRAIN_FIX_H__
#define ___C_LINEAR_CONSTRAIN_FIX_H__

#include "version.h"

#include <vector>
#include <ostream>

using namespace std;


namespace fib{

namespace algorithms{

namespace nLinearInequation{


template <class tFactors>
class cLinearConstrainFix{
public:
	
	/**
	 * The number of factors vecFactors in the linear formular.
	 *
	 * @see vecFactors
	 */
	unsigned long ulNumberOfFactors;
	
	/**
	 * The number of constrain/ bounderie factors vecBounderyFactors that
	 * constrain the linear formular.
	 *
	 * @see vecBounderyFactors
	 */
	unsigned long ulNumberOfConstrainFactors;
	
	
	/*vecBounderyFactors[0] * yu_0 + ... + vecBounderyFactors[uiNumberOfDataPoints] * yu_{uiNumberOfDataPoints}
	(bGreaterEqual ? <= : =>)
	constant + vecFactors[0] * a_0 + ... + vecFactors[uiNumberOfFactors] * a_[uiNumberOfFactors}
	(bGreaterEqual ? <= : =>)
	vecBounderyFactors[0] * yo_0 + ... + vecBounderyFactors[uiNumberOfDataPoints] * yo_{uiNumberOfDataPoints}*/
	
	/**
	 * If true the sign betwean the lower bound y factors (yu) constrain
	 * and the linear formular is an greater equal sign "<=", else it's
	 * an lower equal sign ">=" . (as seen from the linear formular)
	 */
	bool bGreaterEqual;
	
	/**
	 * The factors for the linear formular.
	 *
	 * @see ulNumberOfFactors
	 */
	vector< tFactors > vecFactors;
	
	/**
	 * The constant for the linear formular.
	 */
	tFactors constant;
	
	/**
	 * The constrain/ bounderie factors for the constrain of the linear
	 * formular.
	 *
	 * @see ulNumberOfConstrainFactors
	 */
	vector< tFactors > vecBounderyFactors;
	
	
	/**
	 * standardconstructor for a linear inequiation
	 *
	 * @param uiInNumberOfFactors The number of factors @see vecFactors in the
	 * 	linear formular. @see ulNumberOfFactors
	 * @param uiInNumberOfConstrainFactors The number of constrain/ bounderie
	 * 	factors @see vecBounderyFactors that constrain the linear formular.
	 * 	@see ulNumberOfConstrainFactors
	 */
	cLinearConstrainFix( unsigned int uiInNumberOfFactors = 1,
		unsigned int uiInNumberOfConstrainFactors = 1 );

	/**
	 * This operator adds the given linear inequiation to this inequiation.
	 * If the inequiation sign (@see bGreaterEqual) is equal in both, all
	 * correspondending factors and the constant will be added, else they
	 * will be subtracted.
	 *
	 * @see operator+=()
	 * @param linInequiation the inequiation to add to this inequiation
	 * @return a reference to this inequiation
	 */
	cLinearConstrainFix & operator+( const cLinearConstrainFix & linInequiation );

	/**
	 * This operator adds the given linear inequiation to this inequiation.
	 * If the inequiation sign (@see bGreaterEqual) is equal in both, all
	 * correspondending factors and the constant will be added, else they
	 * will be subtracted.
	 *
	 * @see operator+()
	 * @param linInequiation the inequiation to add to this inequiation
	 */
	void operator+=( const cLinearConstrainFix & linInequiation );

	/**
	 * This method multiplies the inequiation with the given factor.
	 * If the factor is negativ the inequiation sign (@see bGreaterEqual)
	 * will be switcht ( bGreaterEqual = ! bGreaterEqual ).
	 *
	 * @param dValue the value, with which to multiply this inequiation
	 * @return a reference to this inequiation
	 */
	cLinearConstrainFix & mult( tFactors dValue );

	/**
	 * This method print the inequiation in a readebel form to the given
	 * output stream outputSream.
	 *
	 * @param outputSream the stream wher to print this inequiation to
	 */
	void print( ostream & outputSream );

};


};//end namespace nLinearInequation
};//end namespace algorithms
};//end namespace fib


//include template implementation
#include "../src/cLinearConstrainFix.cpp"


#endif //___C_LINEAR_CONSTRAIN_FIX_H__
