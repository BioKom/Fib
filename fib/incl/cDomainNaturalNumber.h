/**
 * @class cDomainNaturalNumber
 * file name: cDomainNaturalNumber.h
 * @author Betti Oesterholz
 * @date 21.12.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a domain for natural numbers.
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
 * This file contains the class for natural number Fib -domains.
 * The representet domain is defined by the maximal number in the domain.
 * If N is the maximal number, the domain {0, ..., N} is the
 * unscaled domain and if dScalingFactor is the scaling factor
 * { 0*dScalingFactor, ..., N * dScalingFactor} is the scaled
 * domain.
 *
 */
/*
History:
21.12.2009  Oesterholz  created
01.12.2011  Oesterholz  method isInBoundaries() added
*/

#ifndef ___C_DOMAIN_NATURAL_NUMBER_H__
#define ___C_DOMAIN_NATURAL_NUMBER_H__


#include "version.h"

#include "cDomainIntegerBasis.h"
#include "cDomainNaturalNumberBit.h"


namespace fib{


class cDomainNaturalNumber: public cDomainIntegerBasis{
protected:

	/**
	 * The maximal number of the natural numbers in this domain.
	 */
	unsignedLongFib ulMaxNumber;
	
	/**
	 * The cDomainNaturalNumber uses a cDomainNaturalNumberBit domain for
	 * storing values.
	 */
	cDomainNaturalNumberBit domainNaturalNumberBit;
	
public:

	/**
	 * The constructor for unscaled natural numer domains.
	 * If ulMaxNumber is the maximal number for the domain
	 * {0, ..., ulMaxNumber} is the domain.
	 *
	 * @param ulMaxNumber the maximal number of the domain
	 */
	cDomainNaturalNumber( unsignedLongFib ulMaxNumber );


	/**
	 * The constructor for scaled natural numer domains.
	 * If ulMaxNumber is the maximal number for the domain
	 * { 0*dScalingFactor, ..., ulMaxNumber * dScalingFactor} the scaled
	 * domain.
	 *
	 * @param ulMaxNumber the maximal number of the domain
	 * @param dScalingFactor the scaling factor of the domain
	 * 	the scaling factor has to be greater 0.0
	 */
	cDomainNaturalNumber( unsignedLongFib ulMaxNumber, doubleFib dScalingFactor );

	/**
	 * The copyconstructor for natural numer domains.
	 *
	 * @param domain the  natural number domain to copy
	 */
	cDomainNaturalNumber( const cDomainNaturalNumber &domain );

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
	 * than the minimum value minus the scaling factor and lower than the
	 * maximum value plus the scaling factor.
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
	doubleFib getMaximum() const ;


	/**
	 * This method returns the smalest value in the domain.
	 *
	 * @return the smalest value in the domain
	 */
	virtual doubleFib getMinimum() const;


	/**
	 * This method returns the nullvalue of the domain.
	 * The nullvalue is the value 0 rounded to an value in the 
	 * domain.
	 *
	 * @return the nullvalue of the domain
	 */
	virtual doubleFib getNull() const;


	/**
	 * This method checks if the given value is an element of the
	 * unscaled domain. If the value lValue is an element of the
	 * unscaled domain true is returned, else false.
	 *
	 * @param lValue the value for which to check, if it is an element of
	 * 	the unscaled domain
	 * @return if the value dValue is an element of the unscaled
	 * 	domain true true is returned, else false
	 */
	virtual bool isUnscaledElement( const longFib lValue ) const;


	/**
	 * This method round the given value dValue to an value in the
	 * unscaled domain of this object.
	 * The rounded vale will be the unscaled value with the minimal
	 * distance to the given value lValue. If more of these exists the 
	 * smales will be returned.
	 *
	 * @param lValue the value which should be rounded
	 * @return the rounded unscaled value of lValue
	 */
	virtual longFib roundUnscaled( const longFib lValue ) const;


	/**
	 * This method returns the biggest value in the unscaled domain.
	 *
	 * @return the biggest value in the unscaled domain
	 */
	virtual longFib getMaximumUnscaled() const;


	/**
	 * This method returns the smalest value in the unscaled domain.
	 *
	 * @return the smalest value in the unscaled domain
	 */
	virtual longFib getMinimumUnscaled() const;


	/**
	 * This method returns the nullvalue of the unscaled domain.
	 * The nullvalue is the value 0 rounded to an value in the unscaled
	 * domain.
	 *
	 * @return the nullvalue of the domain
	 */
	virtual longFib getNullUnscaled() const;

	/**
	 * This Method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cDomainNaturalNumber *clone() const;


	/**
	 * This Method checks if the given domain is equal to this domain.
	 *
	 * @param domain the domain which should be equal to this domain
	 * @return true if the given domain is equal to this domain, else false
	 */
	virtual bool operator==( const cDomain &domain ) const;


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
	 * This method stores the given unscaled value lValue in the compressed
	 * fib -format for the domain into the given stream.
	 * It is needed because the stream can yust store byts but the size of
	 * fib -elements can be any number of bits. Because of that ther have to
	 * be a possibility to exchange the missing bits betwean the fib -elements.
	 *
	 * @see cFibElement::store
	 * @param lValue the value to store
	 * @param stream the stream where this domain should be stored to
	 * @param cRestBits the not yet writen bits which should be stored
	 * @param uiRestBitPosition the number of bits in the cRestBits which
	 * 	should be writen respectively containing valid information
	 * @return true if the domain is stored, else false
	 */
	virtual bool storeUnscaledValue( longFib lValue, ostream & stream,
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
	 * @return the unscaled restored value
	 */
	virtual longFib restoreIntegerValue( cReadBits & iBitStream, intFib & outStatus ) const;

};//end class cDomainNaturalNumber


}//end namespace fib

#endif
