/**
 * @class cDomainNaturalNumberBit
 * file name: cDomainNaturalNumberBit.cpp
 * @author Betti Oesterholz
 * @date 21.05.2009
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
 * This file contains the class for natural number Fib -domains which
 * domain is given by the number of bits used to save them.
 * If B is the number of Bits for the domain {0, ..., 2^B-1} is the 
 * unscaled domain and if dScalingFactor is the scaling factor
 * { 0*dScalingFactor, ..., (2^iBits-1) * dScalingFactor} is the scaled
 * domain.
 *
 */
/*
History:
21.05.2009  Oesterholz  created
13.05.2010  Oesterholz  the ordering of bit for the compressed storing corrected
16.05.2010  Oesterholz  getCompressedSizeForScalingFactor() used
01.12.2011  Oesterholz  method isInBoundaries() added
03.09.2013  Oesterholz  using storeXmlDoubleFib() for storing  Fib double
	numbers in XML (@see storeXml() )
*/


#include "cDomainNaturalNumberBit.h"
#include "nBitStream.h"

#include <cmath>


using namespace fib;


/**
 * The constructor for unscaled natural numer domains.
 * If iBits is the number of Bits for the domain {0, ..., 2^iBits-1} is
 * the domain.
 *
 * @param iBits bits to use for numbers of the domain
 */
cDomainNaturalNumberBit::cDomainNaturalNumberBit( unsignedIntFib iBits ):
		cDomainIntegerBasis( (doubleFib)( 1.0 ) ), iBitsForDomainNumbers( iBits ){
}


/**
 * The constructor for scaled natural numer domains.
 * If iBits is the number of Bits for the domain {0, ..., 2^iBits-1} is
 * the unscaled domain and { 0*dScalingFactor, ..., (2^iBits-1) *
 * dScalingFactor} the scaled domain.
 *
 * @param iBits bits to use for numbers of the domain
 * @param dScalingFactor the scaling factor of the domain
 * 	the scaling factor has to be greater 0.0
 */
cDomainNaturalNumberBit::cDomainNaturalNumberBit( unsignedIntFib iBits,
		doubleFib dScalingFactor ):
		cDomainIntegerBasis( dScalingFactor ),
		iBitsForDomainNumbers( iBits ){
}


/**
 * The copyconstructor for natural numer domains.
 *
 * @param domain the natural number domain to copy
 */
cDomainNaturalNumberBit::cDomainNaturalNumberBit(
		const cDomainNaturalNumberBit &domain ):
		cDomainIntegerBasis( domain.getScalingFactor() ),
		iBitsForDomainNumbers( domain.iBitsForDomainNumbers ){
//nothing to do
}


/**
 * @return the type of the domain as an string
 */
string cDomainNaturalNumberBit::getType() const{
	return "DomainNaturalNumberBit";
}


/**
 * This method checks if the given value is an element of the
 * definitionarea. If the value dValue is an element of the
 * definitionarea true is returned, else false.
 *
 * @param dValue the value for which to check, if it is an element of
 * 	the definitionarea
 * @return if the value dValue is an element of the definitionarea true
 * 	true is returned, else false
 */
bool cDomainNaturalNumberBit::isElement( const doubleFib dValue ) const{
	return ( round( dValue )==dValue );
}


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
bool cDomainNaturalNumberBit::isInBoundaries( const doubleFib dValue ) const{
	
	if ( dValue < getMinimum() - getScalingFactor() ){
		return false;
	}
	if ( getMaximum() + getScalingFactor() < dValue ){
		return false;
	}
	return true;
}


/**
 * This method round the given value dValue to an value in the
 * definitionarea of this object.
 * The rounded vale will be the value with the minimal distance to the
 * given value dValue. If more of these exists the smales will be
 * returned.
 *
 * @param dValue the value which should be rounded
 * @return the rounded value of dValue
 */
doubleFib cDomainNaturalNumberBit::round( const doubleFib dValue ) const{

	//check if the value is outside the domain bounds
	if ( dValue<=getMinimum() ){
		return getMinimum();
	}
	if ( getMaximum()<=dValue ){
		return getMaximum();
	}

	//get next numbers in the domain
	const longFib lowerUnscaledBound = dValue / getScalingFactor();
	const doubleFib lowerScaledBound = lowerUnscaledBound * getScalingFactor();
	const doubleFib upperScaledBound = (lowerUnscaledBound + 1) *
		getScalingFactor();
	
	//get number with the minimum distance
	const doubleFib distanceToLowerScaledBound = dValue - lowerScaledBound;
	const doubleFib distanceToUpperScaledBound = upperScaledBound - dValue;
	
	//return value with the minimum distance
	if (distanceToLowerScaledBound <= distanceToUpperScaledBound){
		/*the lower bound has a smaler or equal distance to the dValue than
		upper bound -> return the lower bound*/
		return lowerScaledBound;
	}//else
	return upperScaledBound;
}


/**
 * This method returns the biggest value in the definitionarea.
 *
 * @return the biggest value in the definitionarea
 */
doubleFib cDomainNaturalNumberBit::getMaximum() const{

	doubleFib dMaximumUnscaled = 1.0;

	for ( unsignedIntFib iBit = 0; iBit < iBitsForDomainNumbers; iBit++ ){
		dMaximumUnscaled *= 2.0;
	}
	
	return (dMaximumUnscaled - 1.0) * getScalingFactor();
}


/**
 * This method returns the smalest value in the definitionarea.
 *
 * @return the smalest value in the definitionarea
 */
doubleFib cDomainNaturalNumberBit::getMinimum() const{
	return 0.0 * getScalingFactor();
}


/**
 * This method returns the nullvalue of the definitionarea.
 * The nullvalue is the value 0 rounded to an value in the 
 * definitionarea.
 *
 * @return the nullvalue of the definitionarea
 */
doubleFib cDomainNaturalNumberBit::getNull() const{
	return 0.0 * getScalingFactor();
}


/**
 * This method checks if the given value is an element of the
 * unscaled definitionarea. If the value dValue is an element of the
 * unscaled definitionarea true is returned, else false.
 *
 * @param lValue the value for which to check, if it is an element of
 * 	the unscaled definitionarea
 * @return if the value dValue is an element of the unscaled
 * 	definitionarea true true is returned, else false
 */
bool cDomainNaturalNumberBit::isUnscaledElement( const longFib lValue ) const{
	return ( roundUnscaled( lValue ) == lValue );
}


/**
 * This method round the given value dValue to an value in the
 * unscaled definitionarea of this object.
 * The rounded vale will be the unscaled value with the minimal
 * distance to the given value lValue. If more of these exists the 
 * smales will be returned.
 *
 * @param lValue the value which should be rounded
 * @return the rounded unscaled value of lValue
 */
longFib cDomainNaturalNumberBit::roundUnscaled( const longFib lValue ) const{
	//check if the value is outside the domain bounds
	if ( lValue < getMinimumUnscaled() ){
		return getMinimumUnscaled();
	}
	if ( ((unsignedLongFib)getMaximumUnscaled()) < ((unsignedLongFib)lValue) ){
		return getMaximumUnscaled();
	}
	//else the value is in the domain
	return lValue;
}


/**
 * This method returns the biggest value in the unscaled definitionarea.
 *
 * @return the biggest value in the unscaled definitionarea
 */
longFib cDomainNaturalNumberBit::getMaximumUnscaled() const{

	longFib lMaximumUnscaled = 1;

	for ( unsignedIntFib iBit = 0; iBit < iBitsForDomainNumbers; iBit++ ){
		lMaximumUnscaled *= 2;
	}
	
	return (lMaximumUnscaled - 1);
}


/**
 * This method returns the smalest value in the unscaled definitionarea.
 *
 * @return the smalest value in the unscaled definitionarea
 */
longFib cDomainNaturalNumberBit::getMinimumUnscaled() const{
	return 0;
}


/**
 * This method returns the nullvalue of the unscaled definitionarea.
 * The nullvalue is the value 0 rounded to an value in the unscaled
 * definitionarea.
 *
 * @return the nullvalue of the definitionarea
 */
longFib cDomainNaturalNumberBit::getNullUnscaled() const{
	return 0;
}


/**
 * This Method clones this object.
 *
 * @return a clone of this object
 */
cDomainNaturalNumberBit *cDomainNaturalNumberBit::clone() const{
	return new cDomainNaturalNumberBit( *this );
}


/**
 * This Method checks if the given domain is equal to this domain.
 *
 * @param domain the domain to compare with
 * @return true if the given domain is equal to this domain, else false
 */
bool cDomainNaturalNumberBit::operator==( const cDomain &domain ) const{

	if ( cDomainIntegerBasis::operator==( domain ) ){
		return (iBitsForDomainNumbers==((cDomainNaturalNumberBit*)(&domain))->iBitsForDomainNumbers);
	}
	return false;
}


/**
 * This method evaluades the size of the domain in bits in the
 * compressed file form.
 *
 * @see store()
 * @return the size of the domain in bits in the compressed form
 */
unsignedIntFib cDomainNaturalNumberBit::getCompressedSize() const{
	
	unsignedLongFib ulCompressedSize = 16;//size of the domain
	
	if ( getScalingFactor() != (doubleFib)( 1.0 ) ){
		//add bits for scaling factor
		ulCompressedSize += getCompressedSizeForScalingFactor();
	}

	return ulCompressedSize;

}


/**
 * This method evaluades the size of values in the domain in bits in
 * the compressed file form.
 *
 * @see store()
 * @return the size of the domain in bits in the compressed form
 */
unsignedIntFib cDomainNaturalNumberBit::getCompressedSizeForValue() const{
	return iBitsForDomainNumbers;
}


/**
 * This method stores this domain in the XML -format into the
 * given stream.
 *
 * @param ostream the stream where domains should be stored to
 * @return true if this domain are stored, else false
 */
bool cDomainNaturalNumberBit::storeXml( ostream & ostream ) const{
	
	ostream<<"<naturalNumberB ";
	if ( getScalingFactor() != 1.0 ){
		//write scalingfactor
		ostream<<"scalingfactor=\"";
		storeXmlDoubleFib( ostream, getScalingFactor() );
		ostream<<"\" ";
	}
	ostream<<"bit=\""<< iBitsForDomainNumbers <<"\" />"<<endl;
	
	return true;
}


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
intFib cDomainNaturalNumberBit::restoreXml( const TiXmlElement * pXmlElement ){
	
	if ( pXmlElement == NULL ){
		//Error: nothing to load
		return -1;
	}
	string szElementType( pXmlElement->Value() );

	if ( szElementType != "naturalNumberB" ){
		return -2;
	}
	intFib iReturnValue = 0;
	
	//restore the attribute bit
	int iNumberOfBits = 0;
	const char * szXmlNumberOfBits = pXmlElement->Attribute(
		"bit", &iNumberOfBits );
	if ( szXmlNumberOfBits == NULL ){
		//Warning: attribute bits is missing
		iReturnValue = 2;
	}
	iBitsForDomainNumbers = iNumberOfBits;
	
	//restore the attribute scalingfactor
	const char * szXmlScalingFactor = pXmlElement->Attribute( "scalingfactor" );
	setXmlScaling( szXmlScalingFactor );
	
	return iReturnValue;
}


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
bool cDomainNaturalNumberBit::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	char cDomainName = 0x00; //the name "naturalNumberB"
	
	if ( getScalingFactor() != 1.0 ){
		//set the bit for scaling factor
		cDomainName = cDomainName | 0x02;
	}
	const bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
		&cDomainName, 8 );
	if ( ! bNameStored ){
		return false;
	}
	//store the parameter with the bit per domain number
	const unsigned long ulBitsPerNumber = iBitsForDomainNumbers;
	const bool bParameterStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, ulBitsPerNumber, (unsigned char)(8) );
	if ( ! bParameterStored ){
		return false;
	}

	if ( getScalingFactor() != 1.0 ){
		//store scalingfactor
		const bool bScalingfactorStored = storeScalingFactor( stream,
			cRestBits, uiRestBitPosition );
		if ( ! bScalingfactorStored ){
			return false;
		}
	}

	return true;
}


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
intFib cDomainNaturalNumberBit::restore( cReadBits & iBitStream ){

	if ( ! iBitStream.getStream()->good() ){
		//Error: nothing to load
		return -1;
	}
	int iReturnValue = 0;
	
	//read the typename
	char cDomainName = 0x00;
	unsigned int uiBitsRead = iBitStream.readBits( &cDomainName, 8 );
	if ( ! iBitStream.getStream()->good() ){
		return -2;
	}
	if ( uiBitsRead != 8 ){
		return -2;
	}
	if ( (cDomainName & 0xFC) != 0x00 ){
		//warning: wrong type
		return -2;
	}
	//restore the bits per domain number
	unsigned int cBitsPerNumber = 0x00;
	uiBitsRead = iBitStream.readBits( cBitsPerNumber, 8 );
	if ( ! iBitStream.getStream()->good() ){
		return -2;
	}
	if ( uiBitsRead != 8 ){
		return -2;
	}
	iBitsForDomainNumbers = cBitsPerNumber;
	
	if ( (cDomainName & 0x02) == 0x02 ){
		//restore the scalingfactor
		iReturnValue = restoreScalingFactor( iBitStream );
	}else{
		dScalingFactor = 1.0;
	}
	return iReturnValue;
}


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
bool cDomainNaturalNumberBit::storeValue( doubleFib dValue, ostream & stream,
		char & cRestBits, unsigned char & uiRestBitPosition ) const{
	
	const longFib lUnscaledValue = (longFib)( round( dValue ) / getScalingFactor() );
	return storeUnscaledValue( lUnscaledValue, stream, cRestBits, uiRestBitPosition);
}

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
bool cDomainNaturalNumberBit::storeUnscaledValue( longFib lValue, ostream & stream,
		char & cRestBits, unsigned char & uiRestBitPosition ) const{
	
	unsigned long long ulValue = roundUnscaled( lValue );
	
	return nBitStream::store( stream, cRestBits, uiRestBitPosition,
		ulValue, iBitsForDomainNumbers );
}


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
longFib cDomainNaturalNumberBit::restoreIntegerValue(
		cReadBits & iBitStream, intFib & outStatus ) const{
	
	if ( iBitsForDomainNumbers == 0 ){
		//no bits for number -> number is 0 every time
		return 0;
	}
	const unsigned int uiBytesToRead = (iBitsForDomainNumbers + 7) / 8;
	if ( sizeof(unsigned long long) < uiBytesToRead ){
		//can't restore such big number
		outStatus = -2;
		return 0;
	}

	unsigned long long ulReadedNumber = 0;
	const unsigned int uiBitsRead = iBitStream.readBits( ulReadedNumber ,
		iBitsForDomainNumbers );

	if ( uiBitsRead != iBitsForDomainNumbers ){
		outStatus = -2;
		return 0;
	}
	
	return ulReadedNumber;
}






