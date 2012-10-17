/**
 * @class cDomain
 * file name: cDomain.cpp
 * @author Betti Oesterholz
 * @date 01.08.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents an abstract domain.
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
 * This file contains the basisclass of all Fib -domains. It's not
 * possible to create instances from this class.
 *
 */
/*
History:
01.08.2009  Oesterholz  created
13.05.2010  Oesterholz  the ordering of bits for the compressed storing corrected;
	cDomainRational included
01.08.2009  Oesterholz  cDomainIntegerBit and cDomainInteger included
01.08.2009  Oesterholz  cDomainVectorOpenEnd included
09.02.2012  Oesterholz  isReference() added
25.02.2012  Oesterholz  cDomainReference included
*/

#include "cDomain.h"

#include "cDomainNaturalNumberBit.h"
#include "cDomainNaturalNumber.h"
#include "cDomainIntegerBit.h"
#include "cDomainInteger.h"
#include "cDomainRational.h"
#include "cDomainVector.h"
#include "cDomainVectorOpenEnd.h"
#include "cDomainReference.h"

#include "cTypeVariable.h"

using namespace fib;

/**
 * destructor
 */
cDomain::~cDomain(){
	//pure virtual -> don nothing
}


/**
 * @return true if the object represents a scalar domain, else false
 */
bool cDomain::isScalar() const{
	//standard the domain is not a scalar domain
	return false;
}


/**
 * @return true if the object represents a vector domain, else false
 */
bool cDomain::isVector() const{
	//standard the domain is not a vector domain
	return false;
}


/**
 * @return true if the object represents a reference domain, else false
 * 	@see cDomainReference
 */
bool cDomain::isReference() const{
	//standard the domain is not a reference domain
	return false;
}


/**
 * This Method checks if the given domain is equal to this domain.
 *
 * @param domain the domain which should be equal to this domain
 * @return true if the given domain is equal to this domain, else false
 */
bool cDomain::equal( const cDomain &domain ) const{
	return ( (*this) == domain );
}


/**
 * This Method checks if the given domain is equal to this domain.
 *
 * @param domain the domain which should be equal to this domain
 * @return true if the given domain is equal to this domain, else false
 */
bool cDomain::operator==( const cDomain &domain ) const{
	return getType() == domain.getType();
}


/**
 * This method restores a domain in the XML -format from an TinyXml element.
 *
 * @pattern Factory Method
 * @param pXmlNode a pointer to the TinyXml node wher the domain is stored in
 * @param outStatus an integervalue with the errorvalue
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 * @return the pointers to the restored domain, if non could be restored
 * 	the returned pointer is NULL
 */
cDomain * cDomain::restoreXml( const TiXmlElement * pXmlElement, intFib & outStatus ){

	if ( pXmlElement == NULL ){
		//Error: nothing to load
		outStatus = -1;
		return NULL;
	}
	cDomain * pDomainRestore     = NULL;
	
	string szElementType( pXmlElement->Value() );
	
	intFib iReturnValue = 0;
	if ( szElementType == "naturalNumberB" ){
		pDomainRestore = new cDomainNaturalNumberBit( 0 );
		iReturnValue = pDomainRestore->restoreXml( pXmlElement );
		
	}else if ( szElementType == "naturalNumber" ){
		pDomainRestore = new cDomainNaturalNumber( 0 );
		iReturnValue = pDomainRestore->restoreXml( pXmlElement );
		
	}else if ( szElementType == "integerB" ){
		pDomainRestore = new cDomainIntegerBit( 0 );
		iReturnValue = pDomainRestore->restoreXml( pXmlElement );
		
	}else if ( szElementType == "integer" ){
		pDomainRestore = new cDomainInteger( 0, 0 );
		iReturnValue = pDomainRestore->restoreXml( pXmlElement );
		
	}else if ( szElementType == "rational" ){
		pDomainRestore = new cDomainRational( pXmlElement, outStatus );
		
	}else if ( szElementType == "vector" ){
		vector<cDomain*> vElementDomains;
		pDomainRestore = new cDomainVector( vElementDomains );
		iReturnValue = pDomainRestore->restoreXml( pXmlElement );
		
	}else if ( szElementType == "vectorOpenEnd" ){
		vector<cDomain*> vElementDomains;
		pDomainRestore = new cDomainVectorOpenEnd( vElementDomains );
		iReturnValue = pDomainRestore->restoreXml( pXmlElement );
		
	}else if ( szElementType == "domainReference" ){
		pDomainRestore = new cDomainReference( cTypeVariable() );
		iReturnValue = pDomainRestore->restoreXml( pXmlElement );
		
	}else{//Warning: no domain to restore
		outStatus = 2;
	}//TODO more domains
	
	if ( iReturnValue < 0 ){
		outStatus = iReturnValue;
	}else if ( (iReturnValue != 0) && (outStatus == 0) ){
		outStatus = iReturnValue;
	}
	return pDomainRestore;
}




/**
 * This method restores a domain from a bitstream, wher it is
 * stored in the compressed fib -format.
 *
 * @pattern Factory Method
 * @see store
 * @param iBitStream the stream where the domain is stored in,
 * 	because the stream is an cReadBits, any number of bits can be
 * 	readed from it
 * @param outStatus an integervalue with the errorvalue
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 * @return a pointer to the restored domain or NULL
 */
cDomain * cDomain::restore( cReadBits & iBitStream, intFib & outStatus ){

	if ( ! iBitStream.getStream()->good() ){
		//Error: nothing to load
		outStatus = -1;
		return NULL;
	}
	cDomain * pDomainRestore = NULL;
	
	//read the domainname
	char cDomainName = 0x00;
	unsigned int uiBitsRead = iBitStream.readBits( &cDomainName, 8 );
	if ( ! iBitStream.getStream()->good() ){
		outStatus = -2;
		return NULL;
	}
	if ( uiBitsRead != 8 ){
		outStatus = -2;
		return NULL;
	}
	iBitStream.rollbackBits( 8 );

	/*till now no 64 bit domainnames so ignore bit 1 and ignore 2
	because scalingfactor is loaded in the domain classes*/
	const unsigned char cDomainNamePure = cDomainName & 0xFC;

	intFib iReturnValue = 0;
	if ( cDomainNamePure == 0x00 ){
		pDomainRestore = new cDomainNaturalNumberBit( 0 );
		iReturnValue = pDomainRestore->restore( iBitStream );
		
	}else if ( cDomainNamePure == 0x04 ){
		pDomainRestore = new cDomainNaturalNumber( 0 );
		iReturnValue = pDomainRestore->restore( iBitStream );

	}else if ( cDomainNamePure == 0x40 ){
		pDomainRestore = new cDomainIntegerBit( 0 );
		iReturnValue = pDomainRestore->restore( iBitStream );
		
	}else if ( cDomainNamePure == 0x44 ){
		pDomainRestore = new cDomainInteger( 0, 0 );
		iReturnValue = pDomainRestore->restore( iBitStream );

	}else if ( cDomainNamePure == 0x80 ){
		pDomainRestore = new cDomainRational( cDomainNaturalNumber( 0 ),
			cDomainNaturalNumber( 0 ) );
		iReturnValue = pDomainRestore->restore( iBitStream );
	
	}else if ( (cDomainNamePure == 0xC0) || (cDomainNamePure == 0xC4) ){
		vector<cDomain*> vElementDomains;
		pDomainRestore = new cDomainVector( vElementDomains );
		iReturnValue = pDomainRestore->restore( iBitStream );
	
	}else if ( (cDomainNamePure == 0xE0) || (cDomainNamePure == 0xE4) ){
		vector<cDomain*> vElementDomains;
		pDomainRestore = new cDomainVectorOpenEnd( vElementDomains );
		iReturnValue = pDomainRestore->restore( iBitStream );
	
	}else if ( cDomainNamePure == 0xF0 ){
		pDomainRestore = new cDomainReference( cTypeVariable() );
		iReturnValue = pDomainRestore->restore( iBitStream );
	
	}else{//Warning: no domain to restore
		iReturnValue = -2;
	}//TODO more domains

	if ( iReturnValue < 0 ){
		outStatus = iReturnValue;
	}else if ( (iReturnValue != 0) && (outStatus == 0) ){
		outStatus = iReturnValue;
	}
	return pDomainRestore;
}















