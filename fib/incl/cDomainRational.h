/**
 * @class cDomainRational
 * file name: cDomainRational.h
 * @author Betti Oesterholz
 * @date 13.05.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the class for rational Fib -domains.
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
 * This file contains the class for rational Fib -domains.
 * Rational numbers are composed of two numbers the mantissa and the exponent.
 * The number is: mantissa * 2^exponent
 * This domain stores the numbers for the mantisa and exponent as two
 * cDomainIntegerBasis numbers.
 *
 */
/*
History:
13.05.2009  Oesterholz  created
01.12.2011  Oesterholz  method isInBoundaries() added
*/

#ifndef ___C_DOMAIN_REAL_H__
#define ___C_DOMAIN_REAL_H__


#include "version.h"

#include "cDomainRationalBasis.h"


namespace fib{


class cDomainRational: public cDomainRationalBasis{
public:

	/**
	 * The constructor for rational number domains.
	 *
	 * @param dfMantissa the domain for the mantisse of the rational domain
	 * @param dfExponent the domain for the exponent of the rational domain
	 */
	cDomainRational( const cDomainIntegerBasis &dfMantissa,
		const cDomainIntegerBasis &dfExponent );

	/**
	 * This constructor restores a domain in the XML -format from an TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node wher the domain is stored in
	 * @param outStatus an integervalue with the errorvalue
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 */
	cDomainRational( const TiXmlElement * pXmlElement, intFib & outStatus );

	/**
	 * The copyconstructor for natural numer domains.
	 *
	 * @param domain the rational number domain to copy
	 */
	cDomainRational( const cDomainRational &domain );

	/**
	 * @return the type of the domain as an string
	 */
	virtual string getType() const;
	
	/**
	 * This method checks if the given value is an element of the
	 * domain. If the value dValue is an element of the
	 * domain true is returned, else false.
	 *
	 * @param dValue the value for which to check, if it is an element of
	 * 	the domain
	 * @return if the value dValue is an element of the domain true
	 * 	true is returned, else false
	 */
	virtual bool isElement( const doubleFib dValue ) const;

	/**
	 * This method checks if the given value is inside the domain
	 * boundaries. If the value dValue is inside of the domain boundaries
	 * true is returned, else false.
	 * A value is inside of the vector domain boudaries, if it is greater
	 * than the minimum value and lower than the maximum value.
	 *
	 * @param dValue the value for which to check, if it is inside of
	 * 	the domain boundaries
	 * @return if the vector dValue is inside of the domain boundaries
	 * 	true is returned, else false
	 */
	virtual bool isInBoundaries( const doubleFib dValue ) const;


	/**
	 * This method round the given value dValue to an value in the
	 * domain of this object.
	 * The rounded vale will be the value with the minimal distance to the
	 * given value dValue. If more of these exists the smales will be
	 * returned.
	 *
	 * @param dValue the value which should be rounded
	 * @return the rounded value of dValue
	 */
	virtual doubleFib round( const doubleFib dValue ) const;


	/**
	 * This method returns the biggest value in the domain.
	 *
	 * @return the biggest value in the domain
	 */
	doubleFib getMaximum( ) const ;


	/**
	 * This method returns the smalest value in the domain.
	 *
	 * @return the smalest value in the domain
	 */
	virtual doubleFib getMinimum( ) const;


	/**
	 * This method returns the nullvalue of the domain.
	 * The nullvalue is the value 0 rounded to an value in the 
	 * domain.
	 *
	 * @return the nullvalue of the domain
	 */
	virtual doubleFib getNull( ) const;


	/**
	 * This Method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cDomainRational *clone() const;

	/**
	 * This method evaluades the size of the domain in bits in the
	 * compressed file form.
	 *
	 * @see store()
	 * @return the size of the domain in bits in the compressed form
	 */
	virtual unsignedIntFib getCompressedSize() const;

	/**
	 * This method evaluades the size of values in the domain in bits in
	 * the compressed file form.
	 *
	 * @see store()
	 * @return the size of the domain in bits in the compressed form
	 */
	virtual unsignedIntFib getCompressedSizeForValue() const;

	/**
	 * This method stores this domain in the XML -format into the
	 * given stream.
	 *
	 * @param ostream the stream where domains should be stored to
	 * @return true if this domain are stored, else false
	 */
	virtual bool storeXml( ostream & ostream ) const;
	
	/**
	 * This method restores a domain in the XML -format from an TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node wher the domain is stored in
	 * @return an integervalue with the errorvalue
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 */
	virtual intFib restoreXml( const TiXmlElement * pXmlElement ) ;

	/**
	 * This method stores this domain in the compressed fib -format
	 * into the given stream.
	 * It is needed because the stream can yust store byts but the size of
	 * fib -elements can be any number of bits. Because of that ther have to
	 * be a possibility to exchange the missing bits betwean the fib -elements.
	 *
	 * @see cFibElement::store
	 * @param stream the stream where this domain should be stored to
	 * @param cRestBits the not yet writen bits which should be stored
	 * @param uiRestBitPosition the number of bits in the cRestBits which
	 * 	should be writen respectively containing valid information
	 * @return true if the domain is stored, else false
	 */
	virtual bool store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const;
	
	/**
	 * This method restores a domain from a bitstream, wher it is
	 * stored in the compressed fib -format.
	 *
	 * @see store
	 * @param iBitStream the stream where the domain is stored in,
	 * 	because the stream is an cReadBits, any number of bits can be
	 * 	readed from it
	 * @return an integervalue with the errorvalue
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 */
	virtual intFib restore( cReadBits & iBitStream );

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
		char & cRestBits, unsigned char & uiRestBitPosition ) const;

	/**
	 * This method restores the a unscaled integer value of the domain from
	 * the stream iBitStream, wher it is stored in the compressed fib -format.
	 *
	 * @see storeValue
	 * @see restoreValue
	 * @see storeUnscaledValue
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
	 * @return the restored value
	 */
	virtual doubleFib restoreValue( cReadBits & iBitStream, intFib & outStatus ) const;


protected:

	/**
	 * Decompses a doubleFib number into it's mantissa and exponent part.
	 *
	 * @param dNumber the number to decompose
	 * @param lInOutMantissa a pointer to the longFib field wher the mantissa
	 * 	should be stored
	 * @param lInOutExponent a pointer to the longFib field wher the exponent
	 * 	should be stored
	 */
	void decomposeDoubleFib( const doubleFib dNumber,
		longFib & lInOutMantissa, longFib & lInOutExponent ) const;



};//end class cDomainRational


}//end namespace fib

#endif
