/**
 * @class cDomainIntegerBasis
 * file name: cDomainIntegerBasis.cpp
 * @author Betti Oesterholz
 * @date 17.05.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a basic Fib -vector.
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
 * This file contains the basisclass of all integer Fib -domains.
 * It's not possible to create instances from this class.
 *
 */
/*
History:
17.05.2009  Oesterholz  created
12.05.2010  Oesterholz  scalingfactor moved from cDomainSingle to cDomainIntegerBasis
16.05.2010  Oesterholz  getCompressedSizeForScalingFactor() added
30.04.2011  Oesterholz  scanf long for 64 bit and windows
21.08.2011  Oesterholz  createGoodDomain() returns also cDomainNaturalNumber
23.02.2013  Oesterholz  setXmlScaling() expanded for single double value
03.09.2013  Oesterholz  using readDoubleFromFunction() for restoring Fib
	double numbers in XML (@see setXmlScaling())
*/


#include "cDomainIntegerBasis.h"

#include "cDomainInteger.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainNaturalNumber.h"

#include <cmath>

using namespace fib;


/**
 * The constructor for scalar/ number domains.
 *
 * @param dInScalingFactor the scaling factor for the domain;
 * 	the scaling factor has to be greater 0.0
 */
cDomainIntegerBasis::cDomainIntegerBasis( const doubleFib dInScalingFactor ):
		dScalingFactor( abs( dInScalingFactor ) ){
	
	if ( dScalingFactor == 0.0 ){
		dScalingFactor = 1.0;
	}
}


/**
 * This method returns the scalingfactor of the domain.
 *
 * @return the scalingfactor of the domain
 */
doubleFib cDomainIntegerBasis::getScalingFactor() const{
	return dScalingFactor;
}


/**
 * This method returns the scaled value of the given value lValue.
 *
 * @param lValue the value to scale
 * @return the scaled value of the given value lValue
 */
doubleFib cDomainIntegerBasis::scale( const longFib lValue ) const{
	return (doubleFib)( roundUnscaled( lValue ) ) * getScalingFactor();
}


/**
 * This Method checks if the given domain is equal to this domain.
 *
 * @param domain the domain which should be equal to this domain
 * @return true if the given domain is equal to this domain, else false
 */
bool cDomainIntegerBasis::operator==( const cDomain &domain ) const{
	
	if ( getType()==domain.getType() ){
		return (getScalingFactor()==((cDomainIntegerBasis*)(&domain))->getScalingFactor());
	}
	return false;
}

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
doubleFib cDomainIntegerBasis::restoreValue( cReadBits & iBitStream,
		intFib & outStatus ) const{
	
	const longFib lRestoredValue =
		restoreIntegerValue( iBitStream, outStatus );
	
	return scale( lRestoredValue );
}


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
cDomainIntegerBasis * cDomainIntegerBasis::createGoodDomain(
		const list< longFib > & liValues ){
	
	if ( liValues.empty() ){
		return new cDomainNaturalNumberBit( 0 );
	}
	
	//evalue the values for an integer domain
	longFib lMinimum = liValues.front();
	longFib lMaximum = lMinimum;
	for ( list< longFib >::const_iterator itrValue = liValues.begin();
			itrValue != liValues.end(); itrValue++ ){
		
		if ( *itrValue < lMinimum ){
			lMinimum = *itrValue;
		}
		if ( lMaximum < *itrValue ){
			lMaximum = *itrValue;
		}
	}
	/*
	const unsigned long long ulNumbersInDomain =
		lMaximum - lMinimum + 1;
	const unsigned int iuBitPerInteger = getDigits( ulNumbersInDomain );
	*/
	//TODO include value domains
	
	//create integer domain
	/*TODO? weg:
	if ( ( 0 <= lMinimum ) && ( lMaximum < (lMinimum * 4) )  ){
		return new cDomainNaturalNumber( lMaximum );
	}//else
	*/
	return new cDomainInteger( lMinimum, lMaximum );
}


/**
 * This method evaluades the size for the scaling factor in bits in the
 * compressed file form.
 *
 * @see storeScalingFactor()
 * @return the size of the domain in bits in the compressed form
 */
unsigned int cDomainIntegerBasis::getCompressedSizeForScalingFactor() const{
	
	longFib lMantissa;
	longFib lExponent;
	intFib iSizeMantissa;
	intFib iSizeExponent;
	
	decomposeDoubleFib( getScalingFactor(),
		& lMantissa, & lExponent, & iSizeMantissa, & iSizeExponent );
	
	return (2 * roundUpToFullByte( max( iSizeMantissa, iSizeExponent ) ) + 8);
}


/**
 * This method stores the scalingfactor of this domain in the
 * compressed fib -format into the given stream.
 * It is needed because the stream can yust store byts but the size of
 * fib -elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the fib -elements.
 *
 * @see cFibElement::store
 * @param stream the stream where this domain should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if the scalingfactor of the domain is stored, else false
 */
bool cDomainIntegerBasis::storeScalingFactor( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	longFib lMantissa;
	longFib lExponent;
	intFib iSizeMantissa;
	intFib iSizeExponent;
	
	decomposeDoubleFib( getScalingFactor(),
		& lMantissa, & lExponent, & iSizeMantissa, & iSizeExponent );
	
	//evalue the byts needed for the mantissa and exponent field
	unsigned long uiBytesPerField =
		roundUpToFullByte( max( iSizeMantissa, iSizeExponent ) ) / 8;
	
	bool bBytesPerFieldStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, uiBytesPerField, 8 );
	if ( ! bBytesPerFieldStored ){
		return false;
	}
	long long lStoreMantissa = lMantissa;
	bool bMantissaStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, lStoreMantissa, (unsigned char)(uiBytesPerField * 8) );
	if ( ! bMantissaStored ){
		return false;
	}
	long long lStoreExponent = lExponent;
	bool bExponentStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, lStoreExponent, (unsigned char)(uiBytesPerField * 8) );
	if ( ! bExponentStored ){
		return false;
	}
	
	return true;
}

/**
 * This method restores the scalingfactore from a bitstream, wher it is
 * stored in the compressed fib -format.
 *
 * @see storeScalingFactor
 * @see restore
 * @param iBitStream the stream where the scalingfactore is stored in,
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
intFib cDomainIntegerBasis::restoreScalingFactor( cReadBits & iBitStream ){

	if ( ! iBitStream.getStream()->good() ){
		//Error: nothing to load
		return -1;
	}
	//read the typename
	unsigned int cBytsPerField = 0x00;
	unsigned int uiBitsRead = iBitStream.readBits( cBytsPerField, 8 );
	if ( ! iBitStream.getStream()->good() ){
		return -2;
	}
	if ( uiBitsRead != 8 ){
		return -2;
	}
	
	//restore the mantissa
	long long lMantissa = 0x00;
	uiBitsRead = iBitStream.readBits( lMantissa, cBytsPerField * 8 );
	if ( ! iBitStream.getStream()->good() ){
		return -2;
	}
	if ( uiBitsRead != ((unsigned int)(cBytsPerField) * 8) ){
		return -2;
	}
	
	//restore the exponent
	long long lExponent = 0x00;
	uiBitsRead = iBitStream.readBits( lExponent, cBytsPerField * 8 );
	if ( ! iBitStream.getStream()->good() ){
		return -2;
	}
	if ( uiBitsRead != ((unsigned int)(cBytsPerField) * 8) ){
		return -2;
	}

	dScalingFactor = ((doubleFib)lMantissa) * pow( 2.0, (doubleFib)lExponent );
	
	return 0;
}


/**
 * This function converts the given scalingfactor in xml -format into the
 * number it represents.
 *
 * @param szXmlScalingFactor the scalingfactor readed from an fib -xml -format
 * @return the scalingfactor szXmlScalingFactor represents
 */
doubleFib cDomainIntegerBasis::setXmlScaling( const char * szXmlScalingFactor ){
	
	if ( szXmlScalingFactor == NULL ){
		dScalingFactor = 1.0;
		return dScalingFactor;
	}
	//converting value to double
	std::pair< bool, const char * > pairOutEvalueStatus;
	dScalingFactor = readDoubleFromFunction(
		szXmlScalingFactor, &pairOutEvalueStatus );
	
	if ( ! pairOutEvalueStatus.second ){
		//Warning: Error while reading the number
		if ( dScalingFactor == 0.0 ){
			//set scaling factor to its default value
			dScalingFactor = 1.0;
		}//else a number could be restored -> use it
	}
	return dScalingFactor;
}





