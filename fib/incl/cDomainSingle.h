/**
 * @class cDomainSingle
 * file name: cDomainSingle.h
 * @author Betti Oesterholz
 * @date 13.05.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a scalar domains.
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
 * This file contains the basisclass of all scalar Fib -domains.
 * It's not possible to create instances from this class.
 *
 */
/*
History:
13.05.2009  Oesterholz  created
12.05.2010  Oesterholz  scalingfactor moved from cDomainSingle to cDomainIntegerBasis
19.09.2010  Oesterholz  the createGoodDomain() function added
01.12.2011  Oesterholz  method isInBoundaries() added
*/

#ifndef ___C_DOMAIN_SINGLE_H__
#define ___C_DOMAIN_SINGLE_H__


#include "version.h"
#include "fibDatatyps.h"
#include "cReadBits.h"

#include "cDomain.h"

#include <list>

namespace fib{


class cDomainSingle: public cDomain{
public:

	/**
	 * @return true if the object represents a scalar domain, else false
	 */
	virtual bool isScalar() const{
		return true;
	}

	/**
	 * @return true if the object represents a vector domain, else false
	 */
	virtual bool isVector() const{
		return false;
	}

	
	/**
	 * This method checks if the given value is an element of the
	 * domain. If the value dValue is an element of the
	 * domain true is returned, else false.
	 *
	 * @param dValue the value for which to check, if it is an element of
	 * 	the domain
	 * @return if the value dValue is an element of the domain true
	 * 	is returned, else false
	 */
	virtual bool isElement( const doubleFib dValue ) const = 0;

	/**
	 * This method checks if the given value is inside the domain
	 * boundaries. If the value dValue is inside of the domain boundaries
	 * true is returned, else false.
	 * A value is inside of the vector domain boudaries, if it is greater
	 * than the minimum value minus the scaling factor and lower than the
	 * maximum value plus the scaling factor.
	 *
	 * @param dValue the value for which to check, if it is inside of
	 * 	the domain boundaries
	 * @return if the vector dValue is inside of the domain boundaries
	 * 	true is returned, else false
	 */
	virtual bool isInBoundaries( const doubleFib dValue ) const = 0;


	/**
	 * This method round the given value dValue to an value in the
	 * domain of this object.
	 * The rounded value will be the value with the minimal distance to the
	 * given value dValue. If more of these exists the smales will be
	 * returned.
	 *
	 * @param dValue the value which should be rounded
	 * @return the rounded value of dValue
	 */
	virtual doubleFib round( const doubleFib dValue ) const = 0;


	/**
	 * This method returns the biggest value in the domain.
	 *
	 * @return the biggest value in the domain
	 */
	virtual doubleFib getMaximum() const = 0;


	/**
	 * This method returns the smalest value in the domain.
	 *
	 * @return the smalest value in the domain
	 */
	virtual doubleFib getMinimum() const = 0;


	/**
	 * This method returns the nullvalue of the domain.
	 * The nullvalue is the value 0 rounded to an value in the 
	 * domain.
	 *
	 * @return the nullvalue of the domain
	 */
	virtual doubleFib getNull() const = 0;

	/**
	 * This Method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cDomainSingle *clone() const = 0;

	/**
	 * This method evaluades the size of values in the domain in bits in
	 * the compressed file form.
	 *
	 * @see store()
	 * @return the size of the domain in bits in the compressed form
	 */
	virtual unsignedIntFib getCompressedSizeForValue() const = 0;

	/**
	 * This method stores the given value dValue in the compressed
	 * fib -format for the domain into the given stream.
	 * It is needed because the stream can yust store byts but the size of
	 * fib -elements can be any number of bits. Because of that ther have to
	 * be a possibility to exchange the missing bits betwean the fib -elements.
	 *
	 * @see cFibElement::store
	 * @param dValue the value to store
	 * @param stream the stream where this domain should be stored to
	 * @param cRestBits the not yet writen bits which should be stored
	 * @param uiRestBitPosition the number of bits in the cRestBits which
	 * 	should be writen respectively containing valid information
	 * @return true if the domain is stored, else false
	 */
	virtual bool storeValue( doubleFib dValue, ostream & stream,
		char & cRestBits, unsigned char & uiRestBitPosition ) const = 0;


	/**
	 * This method restores the a value of the domain from the stream
	 * iBitStream wher it is stored in the compressed fib -format.
	 *
	 * @see storeValue
	 * @see cFibElement::restore
	 * @param iBitStream the stream where this value is stored to in,
	 * 	because this stream is an cReadBits, any number of bits can be
	 * 	readed from it
	 * @param outStatus An reference to an integervalue where the errorvalue
	 * 	can be stored to. If the pointer is NULL no errorvalue will be
	 * 	given back.
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid stream
	 * 		- -2 loading error, invalid data in stream
	 * 		- 1 loading warning, invalid data in stream, error could be corrected
	 * 		- 2 loading warning, invalid data in stream, maybe the loaded
	 * 			object is wrong
	 */
	virtual doubleFib restoreValue( cReadBits & iBitStream, intFib & outStatus ) const = 0;

	/**
	 * This function creates creates a good domain wich contains all the
	 * numbers of the given list liValues.
	 * A domain is better than an other domain, if it takes less storage bits
	 * to store the numbers and the domain.
	 * Beware: You have to care that the returned domain is deleted. (if
	 * 	one was returned)
	 *
	 * @param liValues the list with the values, for which a domain is to create
	 * @return a new domain which contains all the given values liValues
	 */
	static cDomainSingle * createGoodDomain( list< doubleFib > & liValues );


};//end class cDomainSingle


}//end namespace fib

#endif

