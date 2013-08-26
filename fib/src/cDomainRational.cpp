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
18.04.2012  Oesterholz  Bugfix: replace FirstChild()->ToElement() with
	FirstChildElement()
17.05.2013  Oesterholz  replaced (m*pow(2,e)) with composeDoubleFib() and
	m*2 with m<<1 and m72 with m>>1
22.08.2013  Oesterholz  minor changes: some const added and adding source
	namespaces for decomposeDoubleFib()
*/


#include "cDomainRational.h"

#include "cDomainNaturalNumberBit.h"
#include "nBitStream.h"

#include <cmath>


using namespace fib;


/**
 * The constructor for rational number domains.
 *
 * @param dfMantissa the domain for the mantisse of the rational domain
 * @param dfExponent the domain for the exponent of the rational domain
 */
cDomainRational::cDomainRational( const cDomainIntegerBasis &dfMantissa,
		const cDomainIntegerBasis &dfExponent ):
		cDomainRationalBasis( dfMantissa, dfExponent ){
	//nothing to do
}

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
cDomainRational::cDomainRational( const TiXmlElement * pXmlElement, intFib & outStatus ):
		cDomainRationalBasis( cDomainNaturalNumberBit( 0 ), cDomainNaturalNumberBit( 0 ) ){
	
	outStatus = restoreXml( pXmlElement );
}


/**
 * The copyconstructor for natural numer domains.
 *
 * @param domain the natural number domain to copy
 */
cDomainRational::cDomainRational( const cDomainRational &domain ):
		cDomainRationalBasis( domain ){
	//nothing to do
}


/**
 * @return the type of the domain as an string
 */
string cDomainRational::getType() const{
	return "DomainRational";
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
bool cDomainRational::isElement( const doubleFib dValue ) const{
	
/*TODO if rounding errors arn't avoidebel
	const doubleFib dSaveDistance = 0.001;
	
	longFib lMantissa;
	longFib lExponent;
	decomposeDoubleFib( dValue, lMantissa, lExponent );
	
	if ( ( ( ( ((doubleFib)lMantissa - dSaveDistance) * pow( 2.0, ((doubleFib)lExponent) ) ) < dValue ) &&
			( dValue < ( ((doubleFib)lMantissa + dSaveDistance) * pow( 2.0, ((doubleFib)lExponent) ) ) ) ) ||
			( ( abs( ((doubleFib)lMantissa) * pow( 2.0, ((doubleFib)lExponent) - dSaveDistance ) ) < abs( dValue ) ) &&
			( abs( dValue ) < abs( ((doubleFib)lMantissa) * pow( 2.0, ((doubleFib)lExponent) + dSaveDistance ) ) ) ) ){
		return true;
	}
	return false;
*/
	return ( round( dValue ) == dValue );
}



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
bool cDomainRational::isInBoundaries( const doubleFib dValue ) const{
	
	if ( dValue < getMinimum() ){
		return false;
	}
	if ( getMaximum() < dValue ){
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
doubleFib cDomainRational::round( const doubleFib dValue ) const{

	//check if the value is outside the domain bounds
	longFib lMantissa;
	longFib lExponent;
	cDomainRational::decomposeDoubleFib( dValue, lMantissa, lExponent );

	return composeDoubleFib( lMantissa, lExponent );
}


/**
 * This method returns the biggest value in the definitionarea.
 *
 * @return the biggest value in the definitionarea
 */
doubleFib cDomainRational::getMaximum() const{
	
	if ( (pDomainMantissa == NULL) || (pDomainExponent == NULL) ){
		return 0.0;
	}
	if ( 0 <= pDomainMantissa->getMaximumUnscaled() ){
		//use biggest second (exponent) factor
		return composeDoubleFib( pDomainMantissa->getMaximumUnscaled(),
			pDomainExponent->getMaximumUnscaled() );
	}//else pDomainMantissa->getMaximum() < 0
	//use smalest second (exponent) factor
	return composeDoubleFib( pDomainMantissa->getMaximumUnscaled(),
		pDomainExponent->getMinimumUnscaled() );
}


/**
 * This method returns the smalest value in the definitionarea.
 *
 * @return the smalest value in the definitionarea
 */
doubleFib cDomainRational::getMinimum() const{
	
	if ( (pDomainMantissa == NULL) || (pDomainExponent == NULL) ){
		return 0.0;
	}
	if ( 0 <= pDomainMantissa->getMinimumUnscaled() ){
		return composeDoubleFib( pDomainMantissa->getMinimumUnscaled(),
			pDomainExponent->getMinimumUnscaled() );
	}//else
	return composeDoubleFib( pDomainMantissa->getMinimumUnscaled(),
		pDomainExponent->getMaximumUnscaled() );
}


/**
 * This method returns the nullvalue of the definitionarea.
 * The nullvalue is the value 0 rounded to an value in the 
 * definitionarea.
 *
 * @return the nullvalue of the definitionarea
 */
doubleFib cDomainRational::getNull() const{
	return round( 0.0 );
}


/**
 * This Method clones this object.
 *
 * @return a clone of this object
 */
cDomainRational *cDomainRational::clone() const{
	return new cDomainRational( *this );
}


/**
 * This method evaluades the size of the domain in bits in the
 * compressed file form.
 *
 * @see store()
 * @return the size of the domain in bits in the compressed form
 */
unsignedIntFib cDomainRational::getCompressedSize() const{
	
	if ( (pDomainMantissa == NULL) || (pDomainExponent == NULL) ){
		return 0;
	}
	return 8 + pDomainMantissa->getCompressedSize() +
		pDomainExponent->getCompressedSize();
}


/**
 * This method evaluades the size of values in the domain in bits in
 * the compressed file form.
 *
 * @see store()
 * @return the size of the domain in bits in the compressed form
 */
unsignedIntFib cDomainRational::getCompressedSizeForValue() const{
	
	if ( (pDomainMantissa == NULL) || (pDomainExponent == NULL) ){
		return 0;
	}
	return pDomainMantissa->getCompressedSizeForValue() +
		pDomainExponent->getCompressedSizeForValue();
}



/**
 * This method stores this domain in the XML -format into the
 * given stream.
 *
 * @param ostream the stream where domains should be stored to
 * @return true if this domain are stored, else false
 */
bool cDomainRational::storeXml( ostream & ostream ) const{
	
	ostream<<"<rational>"<<endl;
	if ( pDomainMantissa != NULL ){
		pDomainMantissa->storeXml( ostream );
	}
	if ( pDomainExponent != NULL ){
		pDomainExponent->storeXml( ostream );
	}
	ostream<<"</rational>"<<endl;
	
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
intFib cDomainRational::restoreXml( const TiXmlElement * pXmlElement ){

	if ( pXmlElement == NULL ){
		//Error: nothing to load
		return -1;
	}
	string szElementType( pXmlElement->Value() );

	if ( szElementType != "rational" ){
		return -2;
	}
	intFib outStatus = 0;
	//restore the mantissa domain
	const TiXmlElement * pXmlElementDomain = NULL;
	if ( pXmlElement->FirstChild() ){
		
		pXmlElementDomain = pXmlElement->FirstChildElement();
		
		const cDomain * pDomMantisse = cDomain::restoreXml( pXmlElementDomain, outStatus );
		if ( outStatus < 0 ){
			return outStatus;
		}
		if ( pDomMantisse == NULL ){
			return -2;
		}
		string szDomainElementType = pDomMantisse->getType();
			
		if ( ( szDomainElementType.compare( 0, 19, "DomainNaturalNumber" ) != 0 ) &&
				(szDomainElementType.compare( 0, 13, "DomainInteger" ) != 0) ){
			return -2;
		}
		if ( pDomainMantissa ){
			delete pDomainMantissa;
		}
		pDomainMantissa = (cDomainIntegerBasis*)pDomMantisse;
	}else{
		return -2;
	}
	//restore the exponent domain
	pXmlElementDomain = pXmlElementDomain->NextSiblingElement();
	if ( pXmlElementDomain != NULL ){
		
		cDomain * pDomExponent = cDomain::restoreXml( pXmlElementDomain, outStatus );
		if ( outStatus < 0 ){
			return outStatus;
		}
		if ( pDomExponent == NULL ){
			return -2;
		}
		const string szDomainElementType = pDomExponent->getType();
		
		if ( ( szDomainElementType.compare( 0, 19, "DomainNaturalNumber" ) != 0 ) &&
				(szDomainElementType.compare( 0, 13, "DomainInteger" ) != 0) ){
			return -2;
		}
		if ( pDomainExponent ){
			delete pDomainExponent;
		}
		pDomainExponent = (cDomainIntegerBasis*)pDomExponent;
	}else{
		return -2;
	}
	
	return 0;
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
bool cDomainRational::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	if ( (pDomainMantissa == NULL) || (pDomainExponent == NULL) ){
		return 0;
	}
	char cDomainName = 0x80; //the name "rational"
	
	const bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
		&cDomainName, 8 );
	if ( ! bNameStored ){
		return false;
	}
	const bool bDomMantisse = pDomainMantissa->store( stream, cRestBits, uiRestBitPosition );
	if ( ! bDomMantisse ){
		return false;
	}
	const bool bDomExponent = pDomainExponent->store( stream, cRestBits, uiRestBitPosition );
	if ( ! bDomExponent ){
		return false;
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
intFib cDomainRational::restore( cReadBits & iBitStream ){

	if ( ! iBitStream.getStream()->good() ){
		//Error: nothing to load
		return -1;
	}
	int iReturnValue = 0;
	
	//read the typename
	unsigned char cDomainName = 0x00;
	unsigned int uiBitsRead = iBitStream.readBits( (char*)&cDomainName, 8 );
	if ( ! iBitStream.getStream()->good() ){
		return -2;
	}
	if ( uiBitsRead != 8 ){
		return -2;
	}
	if ( (cDomainName & 0xFC) != 0x80 ){
		//warning: wrong type
		return -2;
	}
	//restore the mantissa
	intFib outStatus = 0;
	cDomain * pDomMantissa = cDomain::restore( iBitStream, outStatus );
	if ( (outStatus < 0) || (pDomMantissa == NULL) ){
		return outStatus;
	}
	if ( (iReturnValue == 0) && (0 < outStatus) ){
		iReturnValue = outStatus;
	}
	string szDomainElementType = pDomMantissa->getType();
	
	if ( ( szDomainElementType.compare( 0, 19, "DomainNaturalNumber" ) != 0 ) &&
			(szDomainElementType.compare( 0, 13, "DomainInteger" ) != 0) ){
		return -2;
	}
	if ( pDomainMantissa ){
		delete pDomainMantissa;
	}
	pDomainMantissa = (cDomainIntegerBasis*)pDomMantissa;
	
	//restore the exponent
	outStatus = 0;
	cDomain * pDomExponent = cDomain::restore( iBitStream, outStatus );
	if ( (outStatus < 0) || (pDomExponent == NULL) ){
		return outStatus;
	}
	if ( (iReturnValue == 0) && (0 < outStatus) ){
		iReturnValue = outStatus;
	}
	szDomainElementType = pDomExponent->getType();
	
	if ( ( szDomainElementType.compare( 0, 19, "DomainNaturalNumber" ) != 0 ) &&
			(szDomainElementType.compare( 0, 13, "DomainInteger" ) != 0) ){
		return -2;
	}
	if ( pDomainExponent ){
		delete pDomainExponent;
	}
	pDomainExponent = (cDomainIntegerBasis*)pDomExponent;
	
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
bool cDomainRational::storeValue( doubleFib dValue, ostream & stream,
		char & cRestBits, unsigned char & uiRestBitPosition ) const{
	
	if ( (pDomainMantissa == NULL) || (pDomainExponent == NULL) ){
		return 0;
	}
	longFib lMantissa;
	longFib lExponent;
	cDomainRational::decomposeDoubleFib( dValue, lMantissa, lExponent );
	//store mantissa
	const bool bMantissaStored = pDomainMantissa->storeUnscaledValue(
		lMantissa, stream, cRestBits, uiRestBitPosition );
	if ( ! bMantissaStored ){
		return false;
	}
	//store exponent
	const bool bExponentStored = pDomainExponent->storeUnscaledValue(
		lExponent, stream, cRestBits, uiRestBitPosition );
	if ( ! bExponentStored ){
		return false;
	}
	return true;
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
 * @return the restored value
 */
doubleFib cDomainRational::restoreValue( cReadBits & iBitStream,
		intFib & outStatus ) const{
	
	if ( (pDomainMantissa == NULL) || (pDomainExponent == NULL) ){
		//error subdomain missing can't store
		return 0.0;
	}
	//restore mantissa
	const longFib lMantissa = pDomainMantissa->restoreIntegerValue(
		iBitStream, outStatus );
	if ( outStatus < 0 ){
		//error
		return 0.0;
	}
	
	//restore exponent
	const longFib lExponent = pDomainExponent->restoreIntegerValue(
		iBitStream, outStatus );
	if ( outStatus < 0 ){
		//error
		return 0.0;
	}
	return composeDoubleFib( lMantissa, lExponent );
}


/**
 * Decompses a doubleFib number into it's mantissa and exponent part.
 *
 * @param dValue the number to decompose
 * @param lInOutMantissa a pointer to the longFib field wher the mantissa
 * 	should be stored
 * @param lInOutExponent a pointer to the longFib field wher the exponent
 * 	should be stored
 */
void cDomainRational::decomposeDoubleFib( const doubleFib dValue,
		longFib & lInOutMantissa, longFib & lInOutExponent ) const{
	
	DEBUG_OUT_L3(<<"cDomainRational::decomposeDoubleFib( "<< dValue<<", lInOutMantissa, lInOutExponent ) started"<<endl);
	
	if ( (pDomainMantissa == NULL) || (pDomainExponent == NULL) ){
		lInOutMantissa = 0;
		lInOutExponent = 1;
		return;
	}
	if ( dValue <= getMinimum() ){
		if ( 0 <= pDomainMantissa->getMinimumUnscaled() ){
			lInOutMantissa = pDomainMantissa->getMinimumUnscaled();
			lInOutExponent = pDomainExponent->getMinimumUnscaled();
		}else{
			lInOutMantissa = pDomainMantissa->getMinimumUnscaled();
			lInOutExponent = pDomainExponent->getMaximumUnscaled();
		}
		DEBUG_OUT_L3(<<"cDomainRational::decomposeDoubleFib( "<< dValue<<", "<<lInOutMantissa<<", "<<lInOutExponent<<" ) done minimum returned"<<endl);
		return;
	}
	if ( getMaximum() <= dValue ){
	
		if ( 0 <= pDomainMantissa->getMaximumUnscaled() ){
			//use biggest second (exponent) factor
			lInOutMantissa = pDomainMantissa->getMaximumUnscaled();
			lInOutExponent = pDomainExponent->getMaximumUnscaled();
		}else{// pDomainMantissa->getMaximum() < 0
			//use smalest second (exponent) factor
			lInOutMantissa = pDomainMantissa->getMaximumUnscaled();
			lInOutExponent = pDomainExponent->getMinimumUnscaled();
		}
		DEBUG_OUT_L3(<<"cDomainRational::decomposeDoubleFib( "<< dValue<<", "<<lInOutMantissa<<", "<<lInOutExponent<<" ) done maximum returned"<<endl);
		return;
	}
	longFib lMantissa;
	longFib lExponent;
	fib::decomposeDoubleFib( dValue, & lMantissa, & lExponent );
	DEBUG_OUT_L3(<<"initialvalues: "<<composeDoubleFib( lMantissa, lExponent )<<"= "<<lMantissa<<" *2^"<<lExponent<<endl);
	
	//search for the neares number
	const longFib lMinExponent = pDomainExponent->getMinimumUnscaled();
	const longFib lMaxExponent = pDomainExponent->getMaximumUnscaled();
	DEBUG_OUT_L3(<<"exponent min= "<<lMinExponent<<" max= "<<lMaxExponent<<endl);
	if ( lExponent < lMinExponent ){
		const longFib lExponentMin = pDomainExponent->roundUnscaled( lExponent );
		
		lMantissa = pDomainMantissa->roundUnscaled(
			composeDoubleFib( lMantissa, (lExponent - lExponentMin ) ) );
		lExponent = lExponentMin;
		
		DEBUG_OUT_L3(<<"min exponent reached new values: "<<composeDoubleFib( lMantissa, lExponent )<<"= "<<lMantissa<<" *2^"<<lExponent<<endl);
	}else if ( lMaxExponent < lExponent ){
		const longFib lExponentMax = pDomainExponent->roundUnscaled( lExponent );
		
		lMantissa = pDomainMantissa->roundUnscaled(
			composeDoubleFib( lMantissa, ( lExponent - lExponentMax ) ) );
		lExponent = lExponentMax;
	
		DEBUG_OUT_L3(<<"max exponent reached new values: "<<composeDoubleFib( lMantissa, lExponent )<<"= "<<lMantissa<<" *2^"<<lExponent<<endl);
	}
	
	doubleFib dBestDistance = abs( dValue -
		composeDoubleFib( lMantissa, lExponent ) );
	longFib lBestMantissa = lMantissa;
	longFib lBestExponent = lExponent;
	
	longFib lOrgMantissa = lMantissa;
	longFib lOrgExponent = lExponent;
	
	const longFib lMinMatissa = pDomainMantissa->getMinimumUnscaled();
	const longFib lMaxMatissa = pDomainMantissa->getMaximumUnscaled();
	DEBUG_OUT_L3(<<"mantissa min= "<<lMinMatissa<<" max= "<<lMaxMatissa<<endl);
	
	longFib lMantissaHalf = lMantissa >> 1;
	longFib lBounderyMantisse = lMinMatissa;
	if ( lMantissa < 0 ){
		lBounderyMantisse = abs( lMaxMatissa );
	}
	DEBUG_OUT_L4(<<"searching for better than: "<<composeDoubleFib( lBestMantissa, lBestExponent )<<"= "<<lBestMantissa<<" *2^"<<lBestExponent<<endl);
	while ( (lMantissaHalf != 0) && ( lBounderyMantisse < abs( lMantissaHalf ) ) &&
			(lExponent < lMaxExponent ) ){
		//decrease precision
		lExponent++;
		lMantissa = lMantissaHalf;
		lMantissaHalf = lMantissa >> 1;
		
		const longFib lMantissaTmp = pDomainMantissa->roundUnscaled( lMantissa );
		const longFib lExponentTmp = pDomainExponent->roundUnscaled( lExponent );
		
		//check distance lower
		const doubleFib dBestDistanceTmp = abs( dValue -
			composeDoubleFib( lMantissaTmp, lExponentTmp ) );
		if ( dBestDistanceTmp < dBestDistance ){
			dBestDistance = dBestDistanceTmp;
			lBestMantissa = lMantissa;
			lBestExponent = lExponent;
			DEBUG_OUT_L4(<<"better found: "<<composeDoubleFib( lBestMantissa, lBestExponent )<<"= "<<lBestMantissa<<" *2^"<<lBestExponent<<endl);
		}
	}
	//check the other direction
	lMantissa = lOrgMantissa;
	lExponent = lOrgExponent;
	
	longFib lMantissaDouble = lMantissa << 1;
	
	lBounderyMantisse = lMaxMatissa;
	if ( lMantissa < 0 ){
		lBounderyMantisse = abs( lMinMatissa );
	}
	while ( ( abs( lMantissaDouble ) < lBounderyMantisse) && (lMinExponent < lExponent) ){
		//increase precision
		lExponent--;
		lMantissa = lMantissaDouble;
		lMantissaDouble = lMantissa << 1;
		
		const longFib lMantissaTmp = pDomainMantissa->roundUnscaled( lMantissa );
		const longFib lExponentTmp = pDomainExponent->roundUnscaled( lExponent );
		
		//check distance lower
		const doubleFib dBestDistanceTmp = abs( dValue -
			composeDoubleFib( lMantissaTmp, lExponentTmp) );
		if ( dBestDistanceTmp < dBestDistance ){
			dBestDistance = dBestDistanceTmp;
			lBestMantissa = lMantissa;
			lBestExponent = lExponent;
			DEBUG_OUT_L4(<<"better found rev : "<<composeDoubleFib( lBestMantissa, lBestExponent )<<"= "<<lBestMantissa<<" *2^"<<lBestExponent<<endl);
		}
	}
	
	//get the mantissa inside it's bonderies, if possible
	if ( lBestMantissa < lMinMatissa ){
		if ( ( 0 < lBestMantissa ) && ( 0 < lMinMatissa ) ){
			while ( lBestMantissa < lMinMatissa ){
				lBestMantissa = lBestMantissa << 1;
				lBestExponent--;
			}
		}
		if ( ( lBestMantissa < 0 ) && ( lMinMatissa < 0 ) ){
			while ( lBestMantissa < lMinMatissa ){
				lBestMantissa = lBestMantissa >> 1;
				lBestExponent++;
			}
		}
	
	}else if ( lMaxMatissa < lBestMantissa ){
		if ( ( 0 < lBestMantissa ) && ( 0 < lMaxMatissa ) ){
			while ( lMaxMatissa < lBestMantissa ){
				lBestMantissa = lBestMantissa >> 1;
				lBestExponent++;
			}
		}
		if ( ( lBestMantissa < 0 ) && ( lMaxMatissa < 0 ) ){
			while ( lMaxMatissa < lBestMantissa ){
				lBestMantissa = lBestMantissa << 1;
				lBestExponent--;
			}
		}
	}
	lInOutMantissa = pDomainMantissa->roundUnscaled( lBestMantissa );
	lInOutExponent = pDomainExponent->roundUnscaled( lBestExponent );
	
	DEBUG_OUT_L3(<<"cDomainRational::decomposeDoubleFib( "<< dValue<<", "<<lInOutMantissa<<", "<<lInOutExponent<<" ) done"<<endl);
}






