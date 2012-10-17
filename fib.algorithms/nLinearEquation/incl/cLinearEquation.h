/**
 * @file cLinearEquation
 * file name: cLinearEquation.h
 * @author Betti Oesterholz
 * @date 11.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for a equiation.
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
 * This header specifies a class for a equiation.
 * The equiation has the form:
 * constant = vecFactors[0] * x_0 + ... + vecFactors[n] * x_n
 *
 * The elements are:
 * 	- constant: a constant for the equiation
 * 	- vecFactors[i]: the factors for the equiation
 * 	- x_i: variables for the equiation, theas are not given explicite
 *
 */
/*
History:
11.06.2010  Oesterholz  created
20.01.2011  Oesterholz  Methods isNull(), isSolvebel() and
	getNumberOfFactorsNotNull() added
*/

#ifndef ___C_LINEAR_EQUATION_H__
#define ___C_LINEAR_EQUATION_H__

#include "version.h"

#include <vector>
#include <ostream>

using namespace std;


namespace fib{

namespace algorithms{

namespace nLinearEquation{


template <class tFactors>
class cLinearEquation{
public:
	/**
	 * The constant factor for the equiation.
	 */
	tFactors constant;
	
	/**
	 * The factors for the equiation.
	 */
	vector< tFactors > vecFactors;
	
	
	/**
	 * standardconstructor
	 *
	 * @param uiInNumberOfFactors the number of factors in the to create
	 * 	equiation (they will be initialisized with 1)
	 * @param inConstant the constant for the equiation (@see constant)
	 */
	cLinearEquation( unsigned long uiInNumberOfFactors = 1,
		tFactors inConstant = 0.0 );

	/**
	 * This operator adds the given linear equiation to this equiation.
	 * For this all correspondending factors and the constant will be added.
	 *
	 * @see operator+=()
	 * @param linInequiation the inequiation to add to this inequiation
	 * @return a reference to this inequiation
	 */
	cLinearEquation & operator+( const  cLinearEquation & equiation );

	/**
	 * This operator adds the given linear equiation to this equiation.
	 * For this all correspondending factors and the constant will be added.
	 *
	 * @see operator+()
	 * @param linInequiation the inequiation to add to this inequiation
	 */
	void operator+=( const  cLinearEquation & equiation );

	/**
	 * This method multiplies the inequiation with the given factor.
	 *
	 * @param value the value, with which to multiply this inequiation
	 * @return a reference to this inequiation
	 */
	cLinearEquation & mult( tFactors value );
	
	/**
	 * @return true if all factors and the constant are 0, else false
	 */
	bool isNull() const;
	
	/**
	 * @return true if the equiation is solvebel, else false (all factors
	 * 	are 0, but the constant is not 0)
	 */
	bool isSolvebel() const;

	/**
	 * @return the number of factors which are not 0
	 */
	unsigned long getNumberOfFactorsNotNull() const;

	/**
	 * This method print the inequiation in a readebel form to the given
	 * output stream outputSream.
	 *
	 * @param outputStream the stream wher to print this inequiation to
	 */
	void print( ostream & outputStream );
	
};


};//end namespace nLinearEquation
};//end namespace algorithms
};//end namespace fib

//include template implementation
#include "../src/cLinearEquation.cpp"



#endif //___C_LINEAR_EQUATION_H__
