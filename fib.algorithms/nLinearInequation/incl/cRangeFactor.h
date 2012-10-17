/**
 * @file cRangeFactor
 * file name: cRangeFactor.h
 * @author Betti Oesterholz
 * @date 09.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for a range factor.
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

#ifndef ___C_RANGE_FACTOR_H__
#define ___C_RANGE_FACTOR_H__

#include "version.h"

#include <vector>
#include <ostream>

namespace fib{

namespace algorithms{

namespace nLinearInequation{


template <class tFactors>
class cRangeFactor{
public:

	/**
	 * The minimal possible number for the factor.
	 * (if not infinity @see bMinIsInf)
	 */
	tFactors min;
	
	/**
	 * The minimal value for the factor is (negativ) infinity.
	 * @see min
	 */
	bool bMinIsInf;

	/**
	 * The maxmal possible number for the factor.
	 * (if not infinity @see bMaxIsInf)
	 */
	tFactors max;
	
	/**
	 * The maximal value for the factor is infinity.
	 * @see max
	 */
	bool bMaxIsInf;
	
	
	/**
	 * The standardconstructor for the range factor.
	 * The range for the created factor will be from negativ to positiv
	 * infinity.
	 */
	cRangeFactor();
	
	/**
	 * A constructor for the range factor.
	 *
	 * @param inMin the minimal value for the range of the factor (@see min)
	 * @param inMax the maximal value for the range of the factor (@see max)
	 */
	cRangeFactor( tFactors inMin, tFactors inMax );
	
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
	tFactors diff() const;
	
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
	bool diffIsNull() const;
	
	/**
	 * @return true if one boundery is infinity (if @see bMinIsInf or
	 * 	@see bMaxIsInf is true), else false
	 */
	bool isInf() const;
	
	/**
	 * Equal comparrisson operator for two range factors.
	 *
	 * @param rangeFactor the range factor to compare this rangefactor to
	 * @return true if the given range factor rangeFactor is equal to this
	 * 	range factor, else false
	 */
	bool operator==( const cRangeFactor & rangeFactor ) const;
	
	/**
	 * This method sets the minimal boundery of the range factor to the
	 * given value. (It will also set @see bMinIsInf to false)
	 *
	 * @see min
	 * @see bMinIsInf
	 * @param inMin the value to set the minimal boundery to
	 */
	void setMin( tFactors inMin );
	
	/**
	 * This method sets the maximal boundery of the range factor to the
	 * given value. (It will also set @see bMaxIsInf to false)
	 *
	 * @see max
	 * @see bMaxIsInf
	 * @param inMax the value to set the maximal boundery to
	 */
	void setMax( tFactors inMax );
};


};//end namespace nLinearInequation
};//end namespace algorithms
};//end namespace fib

//include template implementation
#include "../src/cRangeFactor.cpp"


#endif //___C_RANGE_FACTOR_H__
