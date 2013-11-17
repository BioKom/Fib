/**
 * @class cDomainNaturalNumber
 * file name: cDomainNaturalNumber.cpp
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
13.05.2010  Oesterholz  the ordering of bit for the compressed storing corrected
16.05.2010  Oesterholz  getCompressedSizeForScalingFactor() used
01.12.2011  Oesterholz  method isInBoundaries() added
03.09.2013  Oesterholz  using storeXmlDoubleFib() for storing  Fib double
	numbers in XML (@see storeXml() )
*/


#include "cDomainNaturalNumber.h"
#include "nBitStream.h"

#include <cmath>


using namespace fib;


/**
 * The constructor for unscaled natural numer domains.
 * If ulMaxNumber is the maximal number for the domain
 * {0, ..., ulMaxNumber} is the domain.
 *
 * @param ulMaxNumber the maximal number of the domain
 */
cDomainNaturalNumber::cDomainNaturalNumber( unsignedLongFib lInMaxNumber ):
		cDomainIntegerBasis( (doubleFib)( 1.0 ) ), ulMaxNumber( lInMaxNumber ),
		domainNaturalNumberBit( getDigits( lInMaxNumber ) ){
}


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
cDomainNaturalNumber::cDomainNaturalNumber( unsignedLongFib lInMaxNumber, doubleFib dScalingFactor ):
		cDomainIntegerBasis( dScalingFactor ), ulMaxNumber( lInMaxNumber ),
		domainNaturalNumberBit( getDigits( lInMaxNumber ) ){
}


/**
 * The copyconstructor for natural numer domains.
 *
 * @param domain the natural number domain to copy
 */
cDomainNaturalNumber::cDomainNaturalNumber( const cDomainNaturalNumber &domain ):
		cDomainIntegerBasis( domain.getScalingFactor() ),
		ulMaxNumber( domain.ulMaxNumber ),
		domainNaturalNumberBit( domain.domainNaturalNumberBit ){
//nothing to do
}


/**
 * @return the type of the domain as an string
 */
string cDomainNaturalNumber::getType() const{
	return "DomainNaturalNumber";
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
bool cDomainNaturalNumber::isElement( const doubleFib dValue ) const{
	return ( round( dValue ) == dValue );
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
bool cDomainNaturalNumber::isInBoundaries( const doubleFib dValue ) const{
	
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
doubleFib cDomainNaturalNumber::round( const doubleFib dValue ) const{

	//check if the value is outside the domain bounds
	if ( dValue <= getMinimum() ){
		return getMinimum();
	}
	if ( getMaximum() <= dValue ){
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
doubleFib cDomainNaturalNumber::getMaximum() const{
	
	return ((doubleFib)(ulMaxNumber)) * getScalingFactor();
}


/**
 * This method returns the smalest value in the definitionarea.
 *
 * @return the smalest value in the definitionarea
 */
doubleFib cDomainNaturalNumber::getMinimum() const{
	return 0.0 * getScalingFactor();
}


/**
 * This method returns the nullvalue of the definitionarea.
 * The nullvalue is the value 0 rounded to an value in the 
 * definitionarea.
 *
 * @return the nullvalue of the definitionarea
 */
doubleFib cDomainNaturalNumber::getNull() const{
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
bool cDomainNaturalNumber::isUnscaledElement( const longFib lValue ) const{
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
longFib cDomainNaturalNumber::roundUnscaled( const longFib lValue ) const{
	//check if the value is outside the domain bounds
	if ( lValue < getMinimumUnscaled() ){
		return getMinimumUnscaled();
	}
	if ( getMaximumUnscaled() < lValue ){
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
longFib cDomainNaturalNumber::getMaximumUnscaled() const{
	
	return ulMaxNumber;
}


/**
 * This method returns the smalest value in the unscaled definitionarea.
 *
 * @return the smalest value in the unscaled definitionarea
 */
longFib cDomainNaturalNumber::getMinimumUnscaled() const{
	return 0;
}


/**
 * This method returns the nullvalue of the unscaled definitionarea.
 * The nullvalue is the value 0 rounded to an value in the unscaled
 * definitionarea.
 *
 * @return the nullvalue of the definitionarea
 */
longFib cDomainNaturalNumber::getNullUnscaled() const{
	return 0;
}


/**
 * This Method clones this object.
 *
 * @return a clone of this object
 */
cDomainNaturalNumber *cDomainNaturalNumber::clone() const{
	return new cDomainNaturalNumber( *this );
}


/**
 * This Method checks if the given domain is equal to this domain.
 *
 * @param domain the domain to compare with
 * @return true if the given domain is equal to this domain, else false
 */
bool cDomainNaturalNumber::operator==( const cDomain &domain ) const{

	if ( cDomainIntegerBasis::operator==( domain ) ){
		return (ulMaxNumber == ((cDomainNaturalNumber*)(&domain))->ulMaxNumber);
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
unsignedIntFib cDomainNaturalNumber::getCompressedSize() const{
	
	unsignedLongFib ulCompressedSize = 72;//size of the domain
	
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
unsignedIntFib cDomainNaturalNumber::getCompressedSizeForValue() const{
	return domainNaturalNumberBit.getCompressedSizeForValue();
}


/**
 * This method stores this domain in the XML -format into the
 * given stream.
 *
 * @param ostream the stream where domains should be stored to
 * @return true if this domain are stored, else false
 */
bool cDomainNaturalNumber::storeXml( ostream & ostream ) const{
	
	ostream<<"<naturalNumber ";
	if ( getScalingFactor() != 1.0 ){
		//write scalingfactor
		ostream<<"scalingfactor=\"";
		storeXmlDoubleFib( ostream, getScalingFactor() );
		ostream<<"\" ";
	}
	ostream<<"max=\""<< ulMaxNumber <<"\" />"<<endl;
	
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
intFib cDomainNaturalNumber::restoreXml( const TiXmlElement * pXmlElement ){
	
	if ( pXmlElement == NULL ){
		//Error: nothing to load
		return -1;
	}
	string szElementType( pXmlElement->Value() );

	if ( szElementType != "naturalNumber" ){
		return -2;
	}
	intFib iReturnValue = 0;
	
	//restore the attribute max
	ulMaxNumber = 0;
	const char * szXmlMax = pXmlElement->Attribute( "max" );
	if ( szXmlMax != NULL ){
		ulMaxNumber = atol( szXmlMax );
	}else{
		//Warning: attribute max is missing
		iReturnValue = 2;
	}
	//restore the attribute scalingfactor
	const char * szXmlScalingFactor = pXmlElement->Attribute( "scalingfactor" );
	setXmlScaling( szXmlScalingFactor );
	
	domainNaturalNumberBit = cDomainNaturalNumberBit( getDigits( ulMaxNumber ) );
	
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
bool cDomainNaturalNumber::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	char cDomainName = 0x04; //the name "naturalNumber"
	
	if ( getScalingFactor() != 1.0 ){
		//set the bit for scaling factor
		cDomainName = cDomainName | 0x02;
	}
	bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
		&cDomainName, 8 );
	if ( ! bNameStored ){
		return false;
	}
	//store the parameter with the maximal number
	const unsigned long long ulRMaxNumber = ulMaxNumber;
	const bool bParameterStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
		ulRMaxNumber, (unsigned char)(64) );
	if ( ! bParameterStored ){
		return false;
	}

	if ( getScalingFactor() != 1.0 ){
		//store scalingfactor
		bool bScalingfactorStored = storeScalingFactor( stream, cRestBits, uiRestBitPosition );
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
intFib cDomainNaturalNumber::restore( cReadBits & iBitStream ){

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
	if ( (cDomainName & 0xFC) != 0x04 ){
		//warning: wrong type
		return -2;
	}
	//restore the maximal number
	unsignedLongFib ulMaxNumberStored = 0x00;
	uiBitsRead = iBitStream.readBits( ulMaxNumberStored, 64 );
	if ( ! iBitStream.getStream()->good() ){
		return -2;
	}
	if ( uiBitsRead != 64 ){
		return -2;
	}
	//set the domain properties
	ulMaxNumber = ulMaxNumberStored;
	domainNaturalNumberBit = cDomainNaturalNumberBit( getDigits( ulMaxNumber ) );
	
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
bool cDomainNaturalNumber::storeValue( doubleFib dValue, ostream & stream,
		char & cRestBits, unsigned char & uiRestBitPosition ) const{
	
	longFib lUnscaledValue = (longFib)( round( dValue ) / getScalingFactor() );
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
bool cDomainNaturalNumber::storeUnscaledValue( longFib lValue, ostream & stream,
		char & cRestBits, unsigned char & uiRestBitPosition ) const{
	
	return domainNaturalNumberBit.storeUnscaledValue( lValue, stream,
		cRestBits, uiRestBitPosition );
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
longFib cDomainNaturalNumber::restoreIntegerValue(
		cReadBits & iBitStream, intFib & outStatus ) const{
	
	return domainNaturalNumberBit.restoreIntegerValue( iBitStream, outStatus );
}





