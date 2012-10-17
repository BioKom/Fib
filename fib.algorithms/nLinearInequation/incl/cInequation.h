/**
 * @file cInequation
 * file name: cInequation.h
 * @author Betti Oesterholz
 * @date 09.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for a inequiation.
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
 * This header specifies a class for a inequiation.
 * The inequiation has the form:
 * constant <= vecFactors[0] * x_0 + ... + vecFactors[n] * x_n
 *
 * The elements are:
 * 	- constant: a constant for the inequiation
 * 	- vecFactors[i]: the factors for the inequiation
 * 	- x_i: variables for the inequiation, theas are not given explicite
 *
 * You can give the factors identifiers to relate them to other formulars.
 */
/*
History:
09.06.2010  Oesterholz  created
26.01.2011  Oesterholz  method evalue() added
03.04.2011  Oesterholz  method evalueValue() added
*/

#ifndef ___C_INEQUATION_H__
#define ___C_INEQUATION_H__

#include "version.h"

#include <vector>
#include <ostream>

using namespace std;


namespace fib{

namespace algorithms{

namespace nLinearInequation{


template <class tFactors>
class cInequation{
public:
	
	/**
	 * The constant factor for the inequiation.
	 */
	tFactors constant;
	
	/**
	 * The factors for the inequiation.
	 */
	vector< tFactors > vecFactors;
	
	/**
	 * This vector contains the identifiers for the factors.
	 * It should contain exactly the same number of elements as
	 * @see vecFactors, so the i'th element is the i'th identifier for
	 * the i'th factor in vecFactors.
	 *
	 * @see vecFactors
	 */
	vector< long > vecIdentifiers;
	
	
	/**
	 * standardconstructor
	 */
	cInequation();
	
	/**
	 * This method print the inequiation in a readebel form to the given
	 * output stream outputSream.
	 *
	 * @param outputSream the stream wher to print this inequiation to
	 */
	void print( ostream & outputStream ) const;
	
	/**
	 * This method evalues the inequiation for the given values.
	 * constant <= vecFactors[0] * vecValues[0] + ... + vecFactors[n] * vecValues[n]
	 *
	 * @return true if the inequiation is true for the values, else false
	 */
	bool evalue( const vector< tFactors > & vecValues ) const;
	
	/**
	 * This method evalues the inequiation for the given values.
	 * constant <= vecFactors[0] * vecValues[0] + ... + vecFactors[n] * vecValues[n]
	 *
	 * @return vecFactors[0] * vecValues[0] + ... + vecFactors[n] * vecValues[n] - constant;
	 * 	if the value is negativ the inequiation is not fulfilled, else it is
	 * 	fulfilled
	 */
	tFactors evalueValue( const vector< tFactors > & vecValues ) const;

	/**
	 * @return true if the given inequiation is the same as this inequiation,
	 * 	else false;
	 * 	two inequiations are the same, if all factors and the constant of
	 * 	one inequiation multiplyed ba a fixed constant are the same to
	 * 	the other inequiation
	 */
	bool sameInequiation( const cInequation< tFactors > & inequiation  ) const;
	
	/**
	 * @return true if the given inequiation is the same as this inequiation
	 * 	except that the constant (or operator) sign is switched, else false;
	 * 	two inequiations are the same, if all factors and the constant of
	 * 	one inequiation multiplyed ba a fixed constant are the same to
	 * 	the other inequiation
	 */
	bool antiInequiation( const cInequation< tFactors > & inequiation  ) const;
	
	/**
	 * @return true if the inequiation is fulfilled for all values, else false
	 */
	bool isTrue() const;
	
	/**
	 * @return true if the inequiation is not fulfilled for all values
	 */
	bool isFalse() const;
	
};


};//end namespace nLinearInequation
};//end namespace algorithms
};//end namespace fib

//include template implementation
#include "../src/cInequation.cpp"


#endif //___C_INEQUATION_H__
