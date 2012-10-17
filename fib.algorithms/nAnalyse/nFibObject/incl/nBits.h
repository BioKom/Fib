/**
 * @file nBits
 * file name: nBits.h
 * @author Betti Oesterholz
 * @date 14.03.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies functions to analyse the fib-objects to get bit counts.
 * Copyright (C) @c GPL3 2011 Betti Oesterholz
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
 * This header specifies functions to analyse the fib-objects to get bit
 * counts.
 */
/*
History:
14.03.2011  Oesterholz  created
*/

#ifndef ___N_ANALYSE__N_FIB_OBJECT__N_BITS_H__
#define ___N_ANALYSE__N_FIB_OBJECT__N_BITS_H__


#include "version.h"

#include "cFibElement.h"

#include <ostream>



using namespace std;
using namespace fib;


namespace fib{

namespace algorithms{

namespace nAnalyse{

namespace nFibObject{

namespace nBits{

	/**
	 * This function returns the minimal number of bits needed to store the
	 * mantissa values, of all underfunction values in the given fib-object.
	 *
	 * @param pFibObject the fib object to analyse
	 * @return a pair with:
	 * 	-first: the minimal number of bits needed to store the mantissa values
	 * 	-second: the number of values in functions
	 */
	pair< unsigned int, unsigned long > evalueMaxFunctionValuesMantissaBits(
		const cFibElement * pFibObject );


};//end namespace nBits
};//end namespace nFibObject
};//end namespace nAnalyse
};//end namespace algorithms
};//end namespace fib


#endif //___N_ANALYSE__N_FIB_OBJECT__N_BITS_H__