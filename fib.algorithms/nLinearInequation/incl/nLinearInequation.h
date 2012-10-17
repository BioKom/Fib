/**
 * @file nLinearInequation
 * file name: nLinearInequation.h
 * @author Betti Oesterholz
 * @date 09.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies functions for linear inequation.
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
 * This header specifies functions for linear inequation.
 */
/*
History:
09.06.2010  Oesterholz  created
*/

#ifndef ___N_LINEAR_INEQUATION_H__
#define ___N_LINEAR_INEQUATION_H__

#include "version.h"

#include "cRangeFactor.h"
#include "cInequation.h"
#include "cLinearConstrainFix.h"

#include <vector>
#include <set>
#include <ostream>

using namespace std;


namespace fib{

namespace algorithms{

namespace nLinearInequation{



	/**
	 * This functions converts the given vector of inequation into a diagonal
	 * form. In this form ther exsists only one factor in the liniar formular
	 * (@see cLinearConstrainFix::vecFactors) in every inequation. For the
	 * first n inequation this factor is the n'th factor. For the remaining
	 * inequation, this factor is the last factor. (n is the number of
	 * factors @see cLinearConstrainFix::ulNumberOfFactors)
	 * The convertion is done by multiplying inequation with a number
	 * (@see cLinearConstrainFix::mult()) or adding two inequation of the
	 * vector of inequations (@see cLinearConstrainFix::operator+()).
	 *
	 * @param vecOfInequations a reference to the vector of inequation, which
	 * 	to convert into the triangle form (this is changed)
	 * @return a pointer to the converted vector of inequations
	 */
	template <class tFactors>
	vector< cLinearConstrainFix<tFactors> > & crateDiagonalForm(
		vector< cLinearConstrainFix<tFactors> > & vecOfInequations );

	/**
	 * This function nulls all factors in the liniar formular
	 * (@see cLinearConstrainFix::vecFactors) which x values are constant.
	 * (Constant x values have a range size of 0, respectivly ther bounderies
	 * are equal.)
	 * The ranges for the x values are given (vecXRanges), wher the i'th
	 * factor range correspondents to the i'th factor in the liniar formular.
	 * The factors are nulled, by multiplying the factor in the liniar
	 * formular with it's x value (the value the range for the x -factor contains).
	 *
	 * @param vecInputInequations a reference to the vector with the
	 * 	inequations, which x -factors should be nulled
	 * @param vecXRanges a vector with the ranges of the x -factors
	 * @param setOpenAFactors a refernce to the set of x -factors, which can be
	 * 	nulled; from this set the nulled factors will be removed;
	 * 	the set contains the numbers of the x -factors (counting begins with 0)
	 * @return a reference to the vector with the inequations, which x
	 * 	factors wher nulled
	 */
	template <class tFactors>
	vector< cLinearConstrainFix<tFactors> > & nullConstantXFactors(
		vector< cLinearConstrainFix<tFactors> > & vecInputInequations,
		const vector< cRangeFactor<tFactors> > & vecXRanges,
		set<unsigned long> & setOpenAFactors );

	/**
	 * This function nulls all constrain/ bounderie factors in the inequations
	 * (@see cLinearConstrainFix::vecBounderyFactors) which y values are constant.
	 * (Constant y values have a range size of 0, respectivly ther bounderies
	 * are equal.)
	 * The ranges for the y values are given (vecYRanges), wher the i'th
	 * factor range correspondents to the i'th constrain/ bounderie factor in
	 * the inequation.
	 * The factors are nulled, by multiplying the bounderie factor in the
	 * inequation with it's y value (the value the range of the y -factor contains).
	 *
	 * @param vecInputInequations a reference to the vector with the
	 * 	inequations, of which the y -factors should be nulled
	 * @param vecYRanges a vector with the ranges of the y -factors
	 * @return a reference to the vector with the inequations, which y
	 * 	-factors wher nulled
	 */
	template <class tFactors> vector< cLinearConstrainFix<tFactors> > &
		nullConstantYFactors( vector< cLinearConstrainFix<tFactors> > & vecInputInequations,
		const vector< cRangeFactor<tFactors> > & vecYRanges );

	/**
	 * This function elemitats all nullfactors from the given vector of
	 * inequations. Every -factor, that is 0 in all inequations, will be
	 * removed from all inequations. Later factors will decrase ther position.
	 * It is possible to set one factor as the last factor in the inequations.
	 *
	 * @param vecInputInequations the vector of the inequation, wher to
	 * 	remove the nullfactors
	 * @param vecFactorXMappings the new x -factor (factors in the liniar
	 * 	formular) mappings, for the inequations;
	 * 	on position i in this vector stands the position, the i'th x -factor
	 * 	in the returned inequations, has in the given inequations
	 * 	vecInputInequations (returned[k].vecFactors[ i ] ==
	 * 	vecInputInequations[k].vecFactors[ vecFactorXMappings[i] ])
	 * @param vecFactorYMappings  the new y -factor (bounderie factor)
	 * 	mappings, for the inequations;
	 * 	on position i in this vector stands the position, the i'th y -factor
	 * 	in the returned inequations, has in the given inequations
	 * 	vecInputInequations (returned[k].vecBounderyFactors[ i ] ==
	 * 	vecInputInequations[k].vecBounderyFactors[ vecFactorYMappings[i] ])
	 * @param uiLastFactor the x -factor (@see cLinearConstrainFix::vecFactors
	 * 	counting begins with 0) which should be last in the returned inequations
	 * @return a vector with the inequations wher the nullfactors are removed
	 */
	template <class tFactors>
	vector< cLinearConstrainFix<tFactors> > reduceNullFactors(
		const vector< cLinearConstrainFix<tFactors> > & vecInputInequations,
		vector< long > & vecFactorXMappings, vector< long > & vecFactorYMappings,
		unsigned long uiLastFactor = 0 );

	/**
	 * This function converts the given @see cLinearConstrainFix inequations
	 * to an equivallent set of @see cInequation inequations.
	 * For every cLinearConstrainFix two cInequation will be crated.
	 * All factors, which are 0, will be eleminated
	 *
	 * vecBounderyFactors[0] * yu_0 + ... + vecBounderyFactors[uiNumberOfDataPoints-1] * yu_{uiNumberOfDataPoints-1}
	 * (bGreaterEqual ? <= : =>)
	 * constant + vecFactors[0] * x_0 + ... + vecFactors[uiNumberOfFactors-1] * x_[uiNumberOfFactors-1}
	 * (bGreaterEqual ? <= : =>)
	 * vecBounderyFactors[0] * yo_0 + ... + vecBounderyFactors[uiNumberOfDataPoints-1] * yo_{uiNumberOfDataPoints-1}
	 * =>
	 * -1 * constant <= vecFactors[0] * z_0 + ... + vecFactors[n] * z_n
	 * constant <= -1 * vecFactors[0] * z_0 - ... - vecFactors[n] * z_n
	 *
	 * Wher:
	 * 	- vecFactors[i] is the i'th factor not 0 of the cLinearConstrainFix
	 * 		( vecBounderyFactors[0] or vecFactors[0] )
	 * 	- constant is the constant of the formular
	 *
	 * The identifiers (@see cInequation::vecIdentifiers) of the cInequation
	 * will be set to a positiv i (0 <= i), if the correspondending original
	 * factor, was the i'th factor for the inequation (x -factor,
	 * original.vecFactors[ i ] or vecOfInequations.vecFactors[ a ] with
	 * i = vecFactorXMappings[ a ] ).
	 * The identifiers will be set to a negativ i ( i < 0), if the
	 * correspondending original factor, was the (-1 * i - 1)'th bounderie
	 * factor (y -factor, original.vecBounderyFactors[ (-1 * i - 1) ] or
	 * vecOfInequations.vecBounderyFactors[ a ] with (-1 * i - 1) = vecFactorYMappings[ a ] ).
	 *
	 * @param vecOfInequations a vector with the (not original) inequations
	 * 	to convert
	 * @param vecFactorXMappings the mappings for the x -factors in
	 * 	vecOfInequations to the original x -factors
	 * @param vecFactorYMappings the mappings for the y -factors in
	 * 	vecOfInequations to the original y -factors
	 * @return a vector with the cInequation, which is equivallent to the
	 * 	given vecOfInequations
	 */
	template <class tFactors>
	vector<cInequation<tFactors> > fixInequationsToInequations(
		const vector< cLinearConstrainFix<tFactors> > & vecOfInequations,
		const vector< long > & vecFactorXMappings,
		const vector< long > & vecFactorYMappings );

	/**
	 * This function reduce the ranges for the given factors with the help of
	 * the given formulars.
	 * The reduced ranges of the factors are subsets of the given ranges.
	 * The reduction is done by checking all inequations as long as ranges change.
	 * For the check of one inequation, all it's elements except one are
	 * maximized by setting the factors to one of ther bounderies.
	 * For the not set element it is checked, wich minimum value it can have,
	 * If it's range is to big for this value, the range will be adapted to
	 * the minimal range, wich is consistent with the this value element.
	 *
	 * example inequation:
	 * 	constant <= vecFactors[0] * z_0 + ... + vecFactors[n] * z_n
	 *
	 * 	(vecFactors[0] * z_0) is an element
	 *
	 * In ever inequation no more than one factor with a infinity boundery
	 * should exists.
	 *
	 * The factor for an element is identified by the element identifier
	 * (@see cInequation::vecIdentifiers).
	 * If the identifiers (@see cInequation::vecIdentifiers) of the factor
	 * is a positiv i (0 <= i) number, the correspondending original
	 * factor, is the i'th factor for the inequation (x -factor,
	 * vecXRanges[ i ] or vecOfInequations.vecFactors[ a ] with
	 * i = vecFactorXMappings[ a ] ).
	 * If the identifiers is a negativ i ( i < 0) number, the correspondending
	 * original factor, is the (-1 * i - 1)'th bounderie
	 * factor (y -factor, vecYRanges[ (-1 * i - 1) ] or
	 * vecOfInequations.vecBounderyFactors[ a ] with (-1 * i - 1) = vecFactorYMappings[ a ] ).
	 *
	 * @see fixInequationsToInequations()
	 * @param vecOfInequations the inequations, with which to reduce the
	 * 	given ranges of the factors
	 * @param vecXRanges the x -factors ranges to reduce
	 * @param vecYRanges the y -factors ranges to reduce
	 * @return true if a boudery was chaged, else false
	 */
	template <class tFactors>
	bool reduceBounderies( const vector<cInequation<tFactors> > & vecOfInequations,
		vector< cRangeFactor<tFactors> > & vecXRanges, vector< cRangeFactor<tFactors> > & vecYRanges);

	/**
	 * This function implements a hillclimbing algorithm for finding good
	 * values for the x -factors.
	 * This function will try to minimize the error of the
	 * @see evalueErrorForFactors() function for the factors.
	 * It will choose random values for the factors which are in the
	 * correspondending range given with vecXRanges. Than it will check near
	 * points (factor values), to the best found point, if they are better.
	 * Beware: In the vecOfInequations just the i'the y -factor is 1, every
	 * 	other y -factor should have the value 0 .(@see evalueErrorForFactors)
	 * 	This is a implicite assumption, the y -factors won't be checked.
	 *
	 * @see evalueErrorForFactors
	 * @param vecOfInequations the inequations, for which to find the
	 * 	factor values
	 * @param vecXRanges the x -factors ranges, in which to find the factor
	 * 	values
	 * @param vecYRanges the y -factors ranges
	 * @param ulMaxIteration the maximal number of iterations / neibourpoints
	 * 	to check
	 * @return a pair:
	 * 	- the first element is the actual point/ values for the x -factors in
	 * 		the x ranges with the lowest found error
	 * 	- the second element is the error of this point
	 */
	template <class tFactors>
	pair< vector<tFactors>, tFactors> hillClimbingInRanges(
		const vector< cInequation<tFactors> > & vecOfInequations,
		const vector< cRangeFactor<tFactors> > & vecXRanges,
		const vector< cRangeFactor<tFactors> > & vecYRanges,
		unsigned long ulMaxIteration = 256 * 256 );

	/**
	 * This function will evalue the error for the given x -factors
	 * vecActualPoint.
	 * For this the factors are inserted into the given inequations
	 * and it is checkt, if the evalued value is outside the given
	 * y -factor bounderies, if so the difference will be added to the error.
	 * Beware: In the vecOfInequations just the i'the y -factor is 1, every
	 * 	other y -factor should have the value 0 .
	 * 	This is a implicite assumption, the y -factors won't be checked.
	 *
	 * @param vecActualPoint the x -factors values, for which to evalue the error
	 * @param vecOfInequations the inequations for which to evalue the error
	 * 	for the vecActualPoint
	 * @param vecYRanges the y -factors ranges
	 * @return the error of the vecActualPoint
	 */
	template <class tFactors>
	tFactors evalueErrorForFactors( const vector<tFactors> & vecActualPoint,
		const vector< cLinearConstrainFix<tFactors> > & vecOfInequations,
		const vector< cRangeFactor<tFactors> > & vecYRanges );

	/**
	 * This function prints the given inequations.
	 * It simply calls @see cPolyConstrainFix::print() for all given
	 * inequations.
	 *
	 * @param vecOfInequations a vector with the inequations to output
	 * @param outputStream a stream, wher to print the inequations to
	 */
	template <class tFactors> void printInequations(
		vector< cLinearConstrainFix<tFactors> > vecOfInequations,
		ostream & outputStream );


	/**
	 * This function solves the given vector of inequiations.
	 *
	 * @param vecOfInequationsInput the vector of linear inequiations to solve
	 * @return a vector with the range factors, in which contain the factors
	 * 	which solve the given linear inequiations
	 */
	template <class tY> vector< cRangeFactor<tY> > solve(
			const vector< cLinearConstrainFix<tY> > & vecOfInequationsInput );

};//end namespace nLinearInequation
};//end namespace algorithms
};//end namespace fib

//include template implementation
#include "../src/nLinearInequation.cpp"


#endif //___N_LINEAR_INEQUATION_H__
