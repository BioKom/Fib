/**
 * @file nLinearEquation
 * file name: nLinearEquation.h
 * @author Betti Oesterholz
 * @date 11.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies functions for linear inequiation.
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
 * This header specifies functions for linear inequiation.
 */
/*
History:
11.06.2010  Oesterholz  created
*/

#ifndef ___N_LINEAR_EQUATION_H__
#define ___N_LINEAR_EQUATION_H__

#include "version.h"

#include "cLinearEquation.h"

#include <vector>
#include <ostream>

namespace fib{

namespace algorithms{

namespace nLinearEquation{


	/**
	 * This functions converts the given vector of equation into a diagonal
	 * form. In this form ther exsists only one factor in the liniar formular
	 * (@see cLinearEquation::vecFactors) in every equation. For the
	 * first n equation this factor is the n'th factor. For the remaining
	 * equation, this factor is the last factor. (n is the number of
	 * factors @see cLinearEquation::vecFactors.size())
	 * The convertion is done by multiplying equation with a number
	 * (@see cLinearEquation::mult()) or adding two equation of the
	 * vector of equations (@see cLinearEquation::operator+()).
	 *
	 * @param vecOfEquations a reference to the vector of equation, which
	 * 	to convert into the diagonal form (this is changed)
	 * @return a pointer to the converted vector of equations
	 */
	template <class tFactors>
	vector< cLinearEquation<tFactors> > & crateDiagonalForm(
		vector< cLinearEquation<tFactors> > & vecOfEquations );

	/**
	 * This function prints the given inequiations.
	 * It simply calls @see cPolyConstrainFix::print() for all given
	 * inequiations.
	 *
	 * @param vecOfInequations a vector with the inequiations to output
	 * @param outputStream a stream, wher to print the inequiations to
	 */
	template <class tFactors> void printEquations(
		vector< cLinearEquation<tFactors> > vecOfInequations,
		ostream & outputStream );



};//end namespace nLinearEquation
};//end namespace algorithms
};//end namespace fib

//include template implementation
#include "../src/nLinearEquation.cpp"


#endif //___N_LINEAR_EQUATION_H__
