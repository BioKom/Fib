/**
 * @file cRangeFactor
 * file name: cRangeFactor.cpp
 * @author Betti Oesterholz
 * @date 09.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implemants a class for a range factor.
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
 * This header specifies a class for a range factor.
 * A range factor specifies a range, wich contains the possible values for
 * a factor.
 * This kind of factor can be used, if the value for factor can not be
 * evalued, but it can be narrowed down to a range.
 *
 */
/*
History:
09.06.2010  Oesterholz  created
*/


#include "cRangeFactor.h"

#ifndef ___C_RANGE_FACTOR_CPP__
#define ___C_RANGE_FACTOR_CPP__



using namespace fib::algorithms::nLinearInequation;


/**
 * The standardconstructor for the range factor.
 * The range for the created factor will be from negativ to positiv
 * infinity.
 */
template <class tFactors> cRangeFactor<tFactors>::cRangeFactor():
		min( 0.0 ), bMinIsInf( true ), max( 0.0 ), bMaxIsInf( true ){
	//nothing to do
}


/**
 * A constructor for the range factor.
 *
 * @param inMin the minimal value for the range of the factor (@see min)
 * @param inMax the maximal value for the range of the factor (@see max)
 */
template <class tFactors> cRangeFactor<tFactors>::cRangeFactor(
		tFactors inMin, tFactors inMax ):
		min( inMin ), bMinIsInf( false ), max( inMax ), bMaxIsInf( false ){
	//nothing to do
}


/**
 * This method will evalue the size of the range, if not one boundery
 * is infinifty.
 * Beware: Check with @see isInf() if the range size is infinity,
 * if you are not shure, befor using this method.
 *
 * @see diffIsNull()
 * @see isInf()
 * @see min
 * @see max
 * @return the difference betwean the minimal and maximal value in the
 * 	range of the factor, respectively the size of the range;
 */
template <class tFactors> tFactors cRangeFactor<tFactors>::diff() const{
	return ( max - min );
}


/**
 * This method will return true if the size of the range is 0, if not
 * one boundery is infinifty.
 *
 * @see diff()
 * @see isInf()
 * @see min
 * @see max
 * @return true if the difference betwean the minimal and maximal value
 * 	is 0, respectively if the bounderies have not the same value,
 * 	else false is returned
 */
template <class tFactors> bool cRangeFactor<tFactors>::diffIsNull() const{
	return (( ! isInf() ) && ( max == min ));
}


/**
 * @return true if one boundery is infinity (if @see bMinIsInf or
 * 	@see bMaxIsInf is true), else false
 */
template <class tFactors> bool cRangeFactor<tFactors>::isInf() const{
	return (bMinIsInf || bMaxIsInf);
}


/**
 * Equal comparrisson operator for two range factors.
 *
 * @param rangeFactor the range factor to compare this rangefactor to
 * @return true if the given range factor rangeFactor is equal to this
 * 	range factor, else false
 */
template <class tFactors> bool cRangeFactor<tFactors>::operator==(
		const cRangeFactor & rangeFactor ) const{
	
	return ( min == rangeFactor.min ) && ( max == rangeFactor.max ) &&
		( bMinIsInf == rangeFactor.bMinIsInf ) &&
		( bMaxIsInf == rangeFactor.bMaxIsInf );
}


/**
 * This method sets the minimal boundery of the range factor to the
 * given value. (It will also set @see bMinIsInf to false)
 *
 * @see min
 * @see bMinIsInf
 * @param inMin the value to set the minimal boundery to
 */
template <class tFactors> void cRangeFactor<tFactors>::setMin( tFactors inMin ){
	min = inMin;
	bMinIsInf = false;
}


/**
 * This method sets the maximal boundery of the range factor to the
 * given value. (It will also set @see bMaxIsInf to false)
 *
 * @see max
 * @see bMaxIsInf
 * @param inMax the value to set the maximal boundery to
 */
template <class tFactors> void cRangeFactor<tFactors>::setMax( tFactors inMax ){
	max = inMax;
	bMaxIsInf = false;
}


#endif //___C_RANGE_FACTOR_CPP__


