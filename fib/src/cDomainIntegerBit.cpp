/**
 * @class cDomainIntegerBit
 * file name: cDomainIntegerBit.h
 * @author Betti Oesterholz
 * @date 17.05.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a domain for integer numbers.
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
 * This file contains the class for integer number Fib -domains.
 * The representet domain is defined by the number of bits per number
 * in the domain.
 * If B is number of bits per number, the domain {-(2^(B-1)), ..., (2^(B-1)-1)}
 * is the unscaled domain and if dScalingFactor is the scaling factor
 * { -(2^(B-1)) * dScalingFactor, ..., (2^(B-1)-1) * dScalingFactor} is
 * the scaled domain.
 *
 */
/*
History:
17.05.2010  Oesterholz  created
14.09.2011  Oesterholz  storeUnscaledValue(): store in two's complement system
01.12.2011  Oesterholz  method isInBoundaries() added
14.04.2013  Oesterholz  replacing pow with integer pow version
01.05.2013  Oesterholz  Bugfix in restore(): iBits read buffer should not const
03.09.2013  Oesterholz  using storeXmlDoubleFib() for storing  Fib double
	numbers in XML (@see storeXml() )
*/


#include "cDomainIntegerBit.h"
#include "nBitStream.h"

#include <cmath>


using namespace fib;


/**
 * The constructor for unscaled integer numer domains.
 * If iBits is number of bits per number of the domain
 * {-(2^(iBits-1)), ..., (2^(iBits-1)-1)} is the domain.
 *
 * @param iBits bits to use for numbers of the domain
 */
cDomainIntegerBit::cDomainIntegerBit( unsignedIntFib iBits ):
		cDomainIntegerBasis( (doubleFib)( 1.0 ) ),
		domainNaturalNumberBit( iBits ),
		lMaxNumber( powInt( 2, iBits - 1 ) - 1),
		lMinNumber( powInt( 2, iBits - 1 ) * -1 ),
		lNumberOfValues( lMaxNumber - lMinNumber + 1 ){
	
	if ( iBits == 0 ){
		lMaxNumber = 0;
		lMinNumber = 0;
		lNumberOfValues = 1;
	}
}


/**
 * The constructor for scaled integer numer domains.
 * If iBits is number of bits per number of the domain
 * { -(2^(B-1)) * dScalingFactor, ..., (2^(B-1)-1) * dScalingFactor}
 * is the scaled domain.
 * ({-(2^(iBits-1)), ..., (2^(iBits-1)-1)} is the unscaled domain)
 *
 * @param iBits bits to use for numbers of the domain
 * @param dScalingFactor the scaling factor of the domain
 * 	the scaling factor has to be greater 0.0
 */
cDomainIntegerBit::cDomainIntegerBit( unsignedIntFib iBits,
		doubleFib dScalingFactor ):
		cDomainIntegerBasis( dScalingFactor ),
		domainNaturalNumberBit( iBits ),
		lMaxNumber( powInt( 2, iBits - 1 ) - 1),
		lMinNumber( powInt( 2, iBits - 1 ) * -1 ),
		lNumberOfValues( lMaxNumber - lMinNumber + 1 ){

	if ( iBits == 0 ){
		lMaxNumber = 0;
		lMinNumber = 0;
		lNumberOfValues = 1;
	}
}


/**
 * The copyconstructor for integer numer domains.
 *
 * @param domain the integer number domain to copy
 */
cDomainIntegerBit::cDomainIntegerBit( const cDomainIntegerBit &domain ):
		cDomainIntegerBasis( domain.getScalingFactor() ),
		domainNaturalNumberBit( domain.domainNaturalNumberBit ),
		lMaxNumber( domain.lMaxNumber ),
		lMinNumber( domain.lMinNumber ),
		lNumberOfValues( domain.lNumberOfValues ){
	//nothing to do
}


/**
 * @return the type of the domain as an string
 */
string cDomainIntegerBit::getType() const{
	return "DomainIntegerBit";
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
bool cDomainIntegerBit::isElement( const doubleFib dValue ) const{
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
bool cDomainIntegerBit::isInBoundaries( const doubleFib dValue ) const{
	
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
 * The rounded vale will be the value with the bits distance to the
 * given value dValue. If more of these exists the smales will be
 * returned.
 *
 * @param dValue the value which should be rounded
 * @return the rounded value of dValue
 */
doubleFib cDomainIntegerBit::round( const doubleFib dValue ) const{

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
	doubleFib upperScaledBound;
	if ( 0 <= dValue ){
		upperScaledBound = (lowerUnscaledBound + 1) *
			getScalingFactor();
	}else{//( dValue < 0.0 )
		upperScaledBound = (lowerUnscaledBound - 1) *
			getScalingFactor();
	}
	
	//get number with the minimum distance
	const doubleFib distanceToLowerScaledBound = abs( dValue - lowerScaledBound );
	const doubleFib distanceToUpperScaledBound = abs( upperScaledBound - dValue );
	
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
doubleFib cDomainIntegerBit::getMaximum() const{
	
	return ((doubleFib)(lMaxNumber)) * getScalingFactor();
}


/**
 * This method returns the smalest value in the definitionarea.
 *
 * @return the smalest value in the definitionarea
 */
doubleFib cDomainIntegerBit::getMinimum() const{
	return ((doubleFib)(lMinNumber)) * getScalingFactor();
}


/**
 * This method returns the nullvalue of the definitionarea.
 * The nullvalue is the value 0 rounded to an value in the 
 * definitionarea.
 *
 * @return the nullvalue of the definitionarea
 */
doubleFib cDomainIntegerBit::getNull() const{
	
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
bool cDomainIntegerBit::isUnscaledElement( const longFib lValue ) const{
	return ( roundUnscaled( lValue ) == lValue );
}


/**
 * This method round the given value dValue to an value in the
 * unscaled definitionarea of this object.
 * The rounded vale will be the unscaled value with the bits
 * distance to the given value lValue. If more of these exists the 
 * smales will be returned.
 *
 * @param lValue the value which should be rounded
 * @return the rounded unscaled value of lValue
 */
longFib cDomainIntegerBit::roundUnscaled( const longFib lValue ) const{
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
longFib cDomainIntegerBit::getMaximumUnscaled() const{
	
	return lMaxNumber;
}


/**
 * This method returns the smalest value in the unscaled definitionarea.
 *
 * @return the smalest value in the unscaled definitionarea
 */
longFib cDomainIntegerBit::getMinimumUnscaled() const{
	return lMinNumber;
}


/**
 * This method returns the nullvalue of the unscaled definitionarea.
 * The nullvalue is the value 0 rounded to an value in the unscaled
 * definitionarea.
 *
 * @return the nullvalue of the definitionarea
 */
longFib cDomainIntegerBit::getNullUnscaled() const{

	return 0;
}


/**
 * This Method clones this object.
 *
 * @return a clone of this object
 */
cDomainIntegerBit *cDomainIntegerBit::clone() const{
	return new cDomainIntegerBit( *this );
}


/**
 * This Method checks if the given domain is equal to this domain.
 *
 * @param domain the domain to compare with
 * @return true if the given domain is equal to this domain, else false
 */
bool cDomainIntegerBit::operator==( const cDomain &domain ) const{

	if ( cDomainIntegerBasis::operator==( domain ) ){
		return (domainNaturalNumberBit ==
			((cDomainIntegerBit*)(&domain))->domainNaturalNumberBit);
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
unsignedIntFib cDomainIntegerBit::getCompressedSize() const{
	
	unsignedLongFib ulCompressedSize = 8 + 8;//size of the domain
	
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
unsignedIntFib cDomainIntegerBit::getCompressedSizeForValue() const{
	
	return domainNaturalNumberBit.getCompressedSizeForValue();
}


/**
 * This method stores this domain in the XML -format into the
 * given stream.
 *
 * @param ostream the stream where domains should be stored to
 * @return true if this domain are stored, else false
 */
bool cDomainIntegerBit::storeXml( ostream & ostream ) const{
	
	ostream<<"<integerB ";
	if ( getScalingFactor() != 1.0 ){
		//write scalingfactor
		ostream<<"scalingfactor=\"";
		storeXmlDoubleFib( ostream, getScalingFactor() );
		ostream<<"\" ";
	}
	ostream<<" bit=\""<< domainNaturalNumberBit.iBitsForDomainNumbers <<"\" />"<<endl;
	
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
intFib cDomainIntegerBit::restoreXml( const TiXmlElement * pXmlElement ){
	
	if ( pXmlElement == NULL ){
		//Error: nothing to load
		return -1;
	}
	string szElementType( pXmlElement->Value() );

	if ( szElementType != "integerB" ){
		return -2;
	}
	intFib iReturnValue = 0;
	
	//restore the attribute min
	unsignedIntFib iBits = 0;
	const char * szXmlBits = pXmlElement->Attribute( "bit" );
	if ( szXmlBits != NULL ){
		iBits = atol( szXmlBits );
	}else{
		//Warning: attribute max is missing
		iReturnValue = 2;
	}

	//restore the attribute scalingfactor
	const char * szXmlScalingFactor = pXmlElement->Attribute( "scalingfactor" );
	setXmlScaling( szXmlScalingFactor );
	
	domainNaturalNumberBit = cDomainNaturalNumberBit( iBits );
	if ( iBits != 0 ){
		lMaxNumber = powInt( 2, iBits - 1 ) - 1;
		lMinNumber = powInt( 2, iBits - 1 ) * -1;
		lNumberOfValues = lMaxNumber - lMinNumber + 1;
	}else{//( iBits == 0 ){
		lMaxNumber = 0;
		lMinNumber = 0;
		lNumberOfValues = 1;
	}
	
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
bool cDomainIntegerBit::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	char cDomainName = 0x40; //the name "integerB"
	
	if ( getScalingFactor() != 1.0 ){
		//set the bit for scaling factor
		cDomainName = cDomainName | 0x02;
	}
	bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
		&cDomainName, 8 );
	if ( ! bNameStored ){
		return false;
	}
	//store the parameter with the bits number
	const unsigned int iRBits = domainNaturalNumberBit.iBitsForDomainNumbers;
	const bool bBitParameterStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
		iRBits, (unsigned char)(8) );
	if ( ! bBitParameterStored ){
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
intFib cDomainIntegerBit::restore( cReadBits & iBitStream ){

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
	if ( (cDomainName & 0xFC) != 0x40 ){
		//warning: wrong type
		return -2;
	}
	//restore the bits number
	unsigned int iBits = 1;
	uiBitsRead = iBitStream.readBits( iBits, 8 );
	if ( ! iBitStream.getStream()->good() ){
		return -2;
	}
	if ( uiBitsRead != 8 ){
		return -2;
	}
	domainNaturalNumberBit = cDomainNaturalNumberBit( iBits );
	
	if ( iBits != 0 ){
		lMaxNumber = powInt( 2, iBits - 1 ) - 1;
		lMinNumber = powInt( 2, iBits - 1 ) * -1;
		lNumberOfValues = lMaxNumber - lMinNumber + 1;
	}else{//( iBits == 0 ){
		lMaxNumber = 0;
		lMinNumber = 0;
		lNumberOfValues = 1;
	}
	
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
bool cDomainIntegerBit::storeValue( doubleFib dValue, ostream & stream,
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
bool cDomainIntegerBit::storeUnscaledValue( longFib lValue, ostream & stream,
		char & cRestBits, unsigned char & uiRestBitPosition ) const{
	
	lValue = roundUnscaled( lValue );
	
	if ( lValue < 0 ){
		//store negative value
		return domainNaturalNumberBit.storeUnscaledValue( lNumberOfValues + lValue,
			stream, cRestBits, uiRestBitPosition );
	}//else ( 0 <= lValue )
	return domainNaturalNumberBit.storeUnscaledValue( lValue,
		stream, cRestBits, uiRestBitPosition );
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
longFib cDomainIntegerBit::restoreIntegerValue(
		cReadBits & iBitStream, intFib & outStatus ) const{
	
	const longFib lLoadedValue =
		domainNaturalNumberBit.restoreIntegerValue( iBitStream, outStatus );
	
	if ( outStatus < 0 ){
		return 0;
	}
	if ( lMaxNumber < lLoadedValue ){
		return roundUnscaled( lLoadedValue - lNumberOfValues );
	}//else ( lLoadedValue <= lMaxNumber )
	return roundUnscaled( lLoadedValue );
}





