/**
 * @class cDomainVectorBasis
 * file name: cDomainVectorBasis.h
 * @author Betti Oesterholz
 * @date 06.07.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a vector domains.
 * Copyright (C) @c LGPL3 2009 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This file contains the basis class of all vector Fib domains.
 * It's not possible to create instances from this class.
 *
 */
/*
History:
06.07.2009  Oesterholz  created
01.12.2011  Oesterholz  method isInBoundaries() added;
	Elements can have any domain type -> cDomainSingle to cDomain
*/

#ifndef ___C_DOMAIN_VECTOR_BASIS_H__
#define ___C_DOMAIN_VECTOR_BASIS_H__


#include "version.h"
#include "fibDatatyps.h"
#include "cFibVector.h"

#include "cDomain.h"

namespace fib{


class cDomainVectorBasis: public cDomain{

public:
	
	/**
	 * @return true if the object represents a scalar domain, else false
	 */
	virtual bool isScalar() const;

	/**
	 * @return true if the object represents a vector domain, else false
	 */
	virtual bool isVector() const;
	
	
	/**
	 * This method checks if the given vector is an element of the
	 * domain. If the value dValue is an element of the
	 * domain true is returned, else false.
	 *
	 * @param fibVector the vector for which to check, if it is an element
	 * 	of the domain
	 * @return if the vector fibVector is an element of the domain true
	 * 	is returned, else false
	 */
	virtual bool isElement( const cFibVector &fibVector ) const = 0;

	/**
	 * This method checks if the given vector is inside the domain
	 * boundaries. If the value dValue is inside of the domain boundaries
	 * true is returned, else false.
	 * A vector is inside of the vector domain boudaries, if all its
	 * elements are inside ther correspondending element domain boundaries.
	 *
	 * @param fibVector the vector for which to check, if it is inside of
	 * 	the domain boundaries
	 * @return if the vector fibVector is inside of the domain boundaries
	 * 	true is returned, else false
	 */
	virtual bool isInBoundaries( const cFibVector &fibVector ) const = 0;

	/**
	 * This method round the given value vector to an vector in the
	 * domain of this object.
	 * The rounded vector will be the vector, wich elements have the minimal
	 * summed distance to the elements of the given vector fibVector. If more
	 * than one such vector exists, the vector wich first n elements have
	 * the minimal summed distance to the first n elements of the given 
	 * vector fibVector. Wher n is first the number of elements in the
	 * vector, and than is decrased to 1 in steps of 1. If again more such
	 * vectors exists, the one with the smalest k elements is choosen, wher
	 * k begins with 1 and is incrased to the number of vectorelements in
	 * the input vector.
	 * ATTENTION: The returned vector will not be deleted automaticly, you
	 * 	have to delete it.
	 *
	 * @param fibVector the vector which should be rounded
	 * @return the rounded vector of fibVector
	 */
	virtual cFibVector * round( cFibVector &fibVector ) const = 0;


	/**
	 * This method returns the number of elements in the vectors of the
	 * domain.
	 *
	 * @return the number of elements in the vectors of the domain
	 */
	virtual unsignedIntFib getNumberOfElements() const = 0;

	/**
	 * This method returns the domain of the iNumberOfElement'th element in
	 * the vectors of the domain.
	 *
	 * @param iNumberOfElement the elementnumber for which the domain is to
	 * 	return
	 * @return domain of the iNumberOfElement'th element in the vectors of
	 * 	the domain
	 */
	virtual cDomain * getElementDomain(
		const unsignedIntFib iNumberOfElement ) = 0;

	/**
	 * This method returns the domain of the iNumberOfElement'th element in
	 * the vectors of the domain.
	 *
	 * @param iNumberOfElement the elementnumber for which the domain is to
	 * 	return
	 * @return domain of the iNumberOfElement'th element in the vectors of
	 * 	the domain
	 */
	virtual const cDomain * getElementDomain(
		const unsignedIntFib iNumberOfElement ) const = 0;

	/**
	 * This Method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cDomainVectorBasis *clone() const = 0;

	
	/**
	 * This function creates creates a good domain wich contains all the
	 * vectors of the given list liVectors .
	 * A domain is better than an other domain, if it takes less storage bits
	 * to store the numbers and the domain.
	 * Beware: You have to care that the returned domain is deleted. (if
	 * 	one was returned)
	 *
	 * @param liVectors the list with the vectors, for which a domain is to create
	 * @return a new domain which contains all the given vectors liVectors
	 */
	static cDomainVectorBasis * createGoodDomain( const list< cFibVector * > & liVectors );

};//end class cDomainVectorBasis


}//end namespace fib

#endif

