/**
 * @class cDomainRationalBasis
 * file name: cDomainRationalBasis.h
 * @author Betti Oesterholz
 * @date 12.05.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a domain for rational numbers.
 * Copyright (C) @c LGPL3 2010 Betti Oesterholz
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
 * This file contains the basisclass of all rational Fib -domains.
 * It's not possible to create instances from this class.
 * Rational numbers are composed of two numbers the mantissa and the exponent.
 * The number is: mantissa * 2^exponent
 *
 */
/*
History:
12.05.2010  Oesterholz  created
*/

#ifndef ___C_DOMAIN_REAL_BASIS_H__
#define ___C_DOMAIN_REAL_BASIS_H__

#include "version.h"
#include "fibDatatyps.h"

#include "cDomainSingle.h"
#include "cDomainIntegerBasis.h"


namespace fib{


class cDomainRationalBasis: public cDomainSingle{
protected:
	
	/**
	 * The domain for the mantisse of the rational domain.
	 */
	cDomainIntegerBasis * pDomainMantissa;
	
	/**
	 * The domain for the exponent of the rational domain.
	 */
	cDomainIntegerBasis * pDomainExponent;
	
	
	/**
	 * The constructor for rational number domains.
	 *
	 * @param dfMantissa the domain for the mantisse of the rational domain
	 * @param dfExponent the domain for the exponent of the rational domain
	 */
	cDomainRationalBasis( const cDomainIntegerBasis &dfMantissa,
		const cDomainIntegerBasis &dfExponent );

	/**
	 * The copyconstructor for rational number domains.
	 *
	 * @param domainRational the domain to copy
	 */
	cDomainRationalBasis( const cDomainRationalBasis &domainRational );

	/**
	 * The desstructor for rational number domains.
	 */
	virtual ~cDomainRationalBasis();


public:


	/**
	 * This Method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cDomainRationalBasis *clone() const = 0;
	
	/**
	 * This Method checks if the given domain is equal to this domain.
	 *
	 * @param domain the domain to compare with
	 * @return true if the given domain is equal to this domain, else false
	 */
	virtual bool operator==( const cDomain &domain ) const;

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
	 * @param outStatus An reference to an rationalvalue where the errorvalue
	 * 	can be stored to. If the pointer is NULL no errorvalue will be
	 * 	given back.
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid stream
	 * 		- -2 loading error, invalid data in stream
	 * 		- 1 loading warning, invalid data in stream, error could be corrected
	 * 		- 2 loading warning, invalid data in stream, maybe the loaded
	 * 			object is wrong
	 * @return the restored value
	 */
	virtual doubleFib restoreValue( cReadBits & iBitStream, intFib & outStatus ) const = 0;
	
	/**
	 * @return a pointer to the mantissa domain of this rational domain
	 * 	@see pDomainMantissa
	 */
	const cDomainIntegerBasis * getMantissaDomain() const;
	
	/**
	 * @return a pointer to the exponent domain of this rational domain
	 * 	@see pDomainExponent
	 */
	const cDomainIntegerBasis * getExponentDomain() const;
	
};//end class cDomainRationalBasis


}//end namespace fib

#endif
