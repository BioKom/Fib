/**
 * @file cHyperplaneBody
 * file name: cHyperplaneBody.h
 * @author Betti Oesterholz
 * @date 28.01.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for a body with hyperplanes as its borders.
 * @pattern strategy
 *
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
 * This header specifies a class for a body with hyperplanes as its borders.
 * This body is defined by inequiations, all points wich fulfill the
 * inequiations are part of the body.
 *
 * Beware of the curse of dimensions! The complexity of the body will
 * grow exponential with the number of dimensions. For example, just the
 * number of border points of a newly created body will be 2^uiDimensions .
 *
 * @see cHyperplane
 * @see cInequation
 */
/*
History:
28.01.2011  Oesterholz  created
27.02.2011  Oesterholz  method getNumberOfBorderPoints() added
03.04.2011  Oesterholz  reimplemented with optimized algorithm
*/

#ifndef ___C_HYPERPLANE_BODY_H__
#define ___C_HYPERPLANE_BODY_H__


#include "version.h"

#include "cHyperplane.h"
#include "cInequation.h"

#include <vector>
#include <set>
#include <list>
#include <ostream>



using namespace std;
using namespace fib::algorithms::nLinearInequation;


namespace fib{

namespace algorithms{

namespace nDn{


template <class tFactors>
class cHyperplaneBody{
protected:
	
	/**
	 * the dimensions of the space for the hyperbody;
	 * all added inequiations should have this much factors
	 *
	 * Beware of the curse of dimensions! The complexity of the body will
	 * grow exponential with the number of dimensions. For example, just the
	 * number of border points of a newly created body will be 2^uiDimensions .
	 */
	const unsigned int uiDimensions;
	
public:
	/**
	 * standard constructor
	 *
	 * @param uiInDimensions the dimensions of the space for the hyperbody;
	 * 	all added inequiations should have this much factors
	 * 	@see uiDimensions
	 */
	cHyperplaneBody( unsigned int uiInDimensions );
	
	
	/**
	 * standard destructor
	 */
	virtual ~cHyperplaneBody();
	
	/**
	 * With this method the hyperplane body can be restricted by the given
	 * inequiation, if the inequiation dosn't remove the body.
	 * If ther are points in this hyperplane body exists wich fulfill the
	 * inequiation, an hyperplane for the inequiation is created and added
	 * to this hyperplane body.
	 * 
	 * @see addInequiations()
	 * @see cInequation
	 * @see cInequation::cHyperplane( const cInequation & inequation )
	 *
	 * @return if true this body was restricted by the given inequiation,
	 * 	else the inequiation would remove this body
	 */
	virtual bool addInequiation( const cInequation< tFactors > & inequiation ) = 0;
	
	/**
	 * The inequiations of the given list of inequiations are added with
	 * @see addInequiation() till this method returns false or all
	 * inequiations are added.
	 * @see addInequiation()
	 * @see cInequation
	 *
	 * @return the number of inequiations added to this body, befor a
	 *		inequiation (vecInequiation[ return - 1 ]) would remove this body
	 */
	unsigned long addInequiations( const vector< cInequation< tFactors > > &
		vecInequiations );
	
	/**
	 * @return the number of the dimensions for the hyperplane body
	 */
	unsigned int getDimensions() const;
	
	/**
	 * @return the number of border points of the body
	 */
	virtual unsigned long getNumberOfBorderPoints() const = 0;
	
	/**
	 * @return a vector with the border points of the body
	 */
	virtual vector< vector< tFactors > > getBorderPoints() const = 0;
	
	/**
	 * This method checks if the given point is part of the hyperbody.
	 * If the point is on one of the borders of the hyperbody or inside it,
	 * it is part of the hyperbody.
	 *
	 * @param vecPoint the point to check
	 * @return true if the point vecPoint is part of the hyperbody, else false
	 */
	virtual bool isPart( const vector< tFactors > & vecPoint ) const = 0;
	
	/**
	 * This method evalues a point in the body.
	 * This point will have:
	 * 	- as much as possible of its last elements set to 0
	 *
	 * @param uiMinBitsToStoreMantissa the minimal number of bits to store
	 * 	the mantissa of a vector element, when the element is in the
	 * 	form: mantissa * 2^exponent ;
	 * 	the method will try to reduce the bits, to store a element of the
	 * 	returned vector, to this value;
	 * 	if uiMinBitsToStoreMantissa is 0 the center points will be returned
	 * 	directly and no bits will be reduced
	 * @return a point in the body
	 */
	vector< tFactors > getPointInBody(
		const unsigned int uiMinBitsToStoreMantissa = 1 ) const;
	
	
	/**
	 * This method print the hyperplane in a readebel form to the given
	 * output stream outputSream.
	 *
	 * @param outputSream the stream wher to print this inequation to
	 */
	virtual void print( ostream & outputStream ) const = 0;

	/**
	 * This method duplicates this whole hyperplane body.
	 *
	 * @return the cloned/ duplicates hyperplane body
	 */
	virtual cHyperplaneBody< tFactors > * clone() const = 0;

};


};//end namespace nDn
};//end namespace algorithms
};//end namespace fib

//include template implementation
#include "../src/cHyperplaneBody.cpp"


#endif //___C_HYPERPLANE_BODY_H__
