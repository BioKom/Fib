/**
 * @class cDomainReference
 * file name: cDomainReference.cpp
 * @author Betti Oesterholz
 * @date 09.02.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a domain wich refer to a domain of an other type.
 * Copyright (C) @c LGPL3 2012 Betti Oesterholz
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
 * This class represents a domain wich refer to a domain of an other type.
 * It is a internal reference for the class @see cDomains .
 *
 */
/*
History:
09.02.2012  Oesterholz  created
18.04.2012  Oesterholz  Bugfix: replace FirstChild()->ToElement() with
	FirstChildElement()
*/


#include "cDomainReference.h"
#include "nBitStream.h"

#include <cmath>


using namespace fib;



/**
 * The constructor for unscaled integer number domains.
 * If lInMinNumber is the minimal number and ulMaxNumber the
 * maximal number of the domain
 * {lInMinNumber, ..., ulMaxNumber} is the domain.
 *
 * @param inOriginalType a reference the type of the element to which
 * 	domain this domain refer to @see pOriginalType
 * @param vecInElementDomains The subdomain of the domain of the element
 * 	to which it is refered. The element with index i is a subdomain of
 * 	the domain with index i-1 . @see vecElementDomains
 */
cDomainReference::cDomainReference( const cTypeElement & inOriginalType,
		const vector<unsignedIntFib> vecInElementDomains ):
		pOriginalType( NULL ), vecElementDomains( vecInElementDomains ){
	
	if ( (&inOriginalType) != NULL ){
		pOriginalType = inOriginalType.clone();
	}
}


/**
 * The copy constructor for reference domain.
 *
 * @param domain the reference domain to copy
 */
cDomainReference::cDomainReference( const cDomainReference & domain ):
		pOriginalType( NULL ), vecElementDomains( domain.vecElementDomains ){
	
	if ( domain.pOriginalType ){
		pOriginalType = domain.pOriginalType->clone();
	}
}


/**
 * destructor
 */
cDomainReference::~cDomainReference(){
	
	if ( pOriginalType ){
		delete pOriginalType;
	}
}


/**
 * @return true if the object represents a reference domain, else false
 * 	@see cDomainReference
 */
bool cDomainReference::isReference() const{
	return true;
}


/**
 * @return the type of the domain as an string
 */
string cDomainReference::getType() const{
	return "DomainReference";
}


/**
 * This Method clones this object.
 *
 * @return a clone of this object
 */
cDomainReference *cDomainReference::clone() const{
	return new cDomainReference( *this );
}


/**
 * This Method checks if the given domain is equal to this domain.
 *
 * @param domain the domain to compare with
 * @return true if the given domain is equal to this domain, else false
 */
bool cDomainReference::operator==( const cDomain &domain ) const{

	if ( cDomain::operator == ( domain ) ){
		
		cDomainReference * pDomainReference = (cDomainReference*)(&domain);
		
		if ( ( pOriginalType == NULL ) ||
				( pDomainReference->pOriginalType == NULL ) ){
			//one type element is NULL -> check if both are NULL
			if ( pOriginalType != pDomainReference->pOriginalType ){
				//domain typs not equal (=NULL)
				return false;
			}
		}else{//both element typs not NULL
			if ( ! pOriginalType->equal( *(pDomainReference->pOriginalType) ) ){
				return false;
			}
		}
		//compare domain element numbers
		return vecElementDomains == (pDomainReference->vecElementDomains);
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
unsignedIntFib cDomainReference::getCompressedSize() const{
	
	unsignedLongFib ulCompressedSize = 8 + 1;//size of the domain + first startbit
	
	if ( pOriginalType ){
		//add bits for type it is refered to
		ulCompressedSize += pOriginalType->getCompressedSize();
	}
	
	if ( ! vecElementDomains.empty() ){
		//add bits for the element subdomain
		unsigned int uiBitsForElementDomains = 0;
		//evalue maximum bits needed for a subdomain number
		for ( vector<unsignedIntFib>::const_iterator
				itrActualSubdomain = vecElementDomains.begin();
				itrActualSubdomain != vecElementDomains.end();
				itrActualSubdomain++ ){
			
			const unsigned int uiBitsForActualElementDomain =
				getDigits( *itrActualSubdomain );
			if ( uiBitsForElementDomains < uiBitsForActualElementDomain ){
				uiBitsForElementDomains = uiBitsForActualElementDomain;
			}
		}
		//add bit for domain element startbit
		uiBitsForElementDomains++;
		
		/*bits for: number of bits per element + first element startbit +
			+ bit for domain element plus startbit*/
		ulCompressedSize += 8 +
			uiBitsForElementDomains * vecElementDomains.size();
	}//end if numbers of element subdomains exists

	return ulCompressedSize;
}


/**
 * This method stores this domain in the XML format into the
 * given stream.
 *
 * @param ostream the stream where domains should be stored to
 * @return true if this domain are stored, else false
 */
bool cDomainReference::storeXml( ostream & ostream ) const{
	
	ostream<<"<domainReference";
	if ( ! vecElementDomains.empty() ){
		//write attribute for the subdomain
		vector<unsignedIntFib>::const_iterator itrActualSubdomain =
			vecElementDomains.begin();
		ostream<<" subdomain=\""<<(*itrActualSubdomain);
		itrActualSubdomain++;
		for ( ; itrActualSubdomain != vecElementDomains.end();
				itrActualSubdomain++ ){
			
			ostream<<"."<<(*itrActualSubdomain);
		}
		ostream<<"\" ";
	}//end if numbers of element subdomains exists
	ostream<<">"<<endl;

	if ( pOriginalType ){
		//write to which type it is refered to
		pOriginalType->storeXml( ostream );
	}else{//Error: dosn't refer to anything
		return false;
	}
	ostream<<"</domainReference>";
	
	return true;
}


/**
 * This method restores a domain in the XML format from an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node wher the domain is stored in
 * @return an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 */
intFib cDomainReference::restoreXml( const TiXmlElement * pXmlElement ){
	
	if ( pXmlElement == NULL ){
		//Error: nothing to load
		return -1;
	}
	string szElementType( pXmlElement->Value() );

	if ( szElementType != "domainReference" ){
		return -2;
	}
	intFib iReturnValue = 0;
	//clear old member values
	vecElementDomains.clear();
	if ( pOriginalType ){
		delete pOriginalType;
		pOriginalType = NULL;
	}
	//restore the attribute subdomain
	const char * szSubDomain= pXmlElement->Attribute( "subdomain" );
	if ( szSubDomain != NULL ){
		//read subdomain numbers
		vecElementDomains.push_back( atol( szSubDomain ) );
		//search for the point
		const char * szNextPoint = strchr( szSubDomain, '.' );
		while ( szNextPoint != NULL ){
			//go to the beginning of the next number
			szNextPoint++;
			//read next number
			vecElementDomains.push_back( atol( szNextPoint ) );
			//search for the next point
			szNextPoint = strchr( szNextPoint, '.' );
		}
	}
	
	//restore type element name
	const TiXmlElement * pSubXmlElement = NULL;
	if ( pXmlElement->FirstChild() ){
		
		pSubXmlElement = pXmlElement->FirstChildElement();
		
		if ( pSubXmlElement ){
			//restore type of the element to which it is refered to
			intFib outStatus = 0;
			pOriginalType = cTypeElement::restoreXmlType( pSubXmlElement, outStatus );
			
			if ( outStatus != 0 ){
				//loading not OK
				if ( outStatus < 0 ){
					//error while loading type element
					return outStatus;
				}//else warning while loading type element
				if ( iReturnValue == 0 ){
					iReturnValue = outStatus;
				}
			}
			
		}else{//Error: not a valid reference
			return -2;
		}
	}else{//Error: not a valid reference
		return -2;
	}
	
	return iReturnValue;
}


/**
 * This method stores this domain in the compressed Fib format
 * into the given stream.
 * It is needed because the stream can yust store byts but the size of
 * Fib elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the Fib elements.
 *
 * @see cFibElement::store
 * @param stream the stream where this domain should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits, which
 * 	should be writen respectively containing valid information
 * @return true if the domain is stored, else false
 */
bool cDomainReference::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	if ( pOriginalType == NULL ){//Error: dosn't refer to anything
		return false;
	}

	char cDomainName = 0xF0; //the name "domainReference"
	
	const bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
		&cDomainName, 8 );
	if ( ! bNameStored ){
		return false;
	}
	
	const bool bTypeStored = pOriginalType->store( stream, cRestBits, uiRestBitPosition );
	if ( ! bTypeStored ){
		return false;
	}
	
	const char cStartBit0 = 0x00;
	const char cStartBit1 = 0xFF;
	if ( vecElementDomains.empty() ){
		//store startbit with 0
		const bool bStartbitStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			&cStartBit0, 1 );
		if ( ! bStartbitStored ){
			return false;
		}
	}else{//store subelement numbers
		//store startbit with 1
		bool bStartbitStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			&cStartBit1, 1 );
		if ( ! bStartbitStored ){
			return false;
		}
		//evalue number of bits per domain element number
		unsigned int uiBitsForElementDomains = 0;
		//evalue maximum bits needed for a subdomain number
		for ( vector<unsignedIntFib>::const_iterator
				itrActualSubdomain = vecElementDomains.begin();
				itrActualSubdomain != vecElementDomains.end();
				itrActualSubdomain++ ){
			
			const unsigned int uiBitsForActualElementDomain =
				getDigits( *itrActualSubdomain );
			if ( uiBitsForElementDomains < uiBitsForActualElementDomain ){
				uiBitsForElementDomains = uiBitsForActualElementDomain;
			}
		}
		//store number of bits per domain element number
		const bool bNumberOfBitsStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			uiBitsForElementDomains, 8 );
		if ( ! bNumberOfBitsStored ){
			return false;
		}
		//store first subelement number
		vector<unsignedIntFib>::const_iterator
			itrActualSubdomain = vecElementDomains.begin();
		
		bool bNumberSubelementStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			(*itrActualSubdomain), uiBitsForElementDomains );
		if ( ! bNumberSubelementStored ){
			return false;
		}
		//store remaining subelement numbers
		itrActualSubdomain++;
		for ( ; itrActualSubdomain != vecElementDomains.end();
				itrActualSubdomain++ ){
			
			//store startbit with 1
			bStartbitStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
				&cStartBit1, 1 );
			if ( ! bStartbitStored ){
				return false;
			}
			//store next subelement number
			bNumberSubelementStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
				(*itrActualSubdomain), uiBitsForElementDomains );
			if ( ! bNumberSubelementStored ){
				return false;
			}
		}//end for store remaining subelement numbers
		bStartbitStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			&cStartBit0, 1 );
		if ( ! bStartbitStored ){
			return false;
		}
	}//end if subelement numbers to store
	
	return true;
}


/**
 * This method restores a domain from a bitstream, wher it is
 * stored in the compressed Fib format.
 *
 * @see store
 * @param iBitStream the stream where the domain is stored in,
 * 	because the stream is an cReadBits, any number of bits can be
 * 	readed from it
 * @return an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 */
intFib cDomainReference::restore( cReadBits & iBitStream ){

	if ( ! iBitStream.getStream()->good() ){
		//Error: nothing to load
		return -1;
	}
	int iReturnValue = 0;
	
	//read the domain name
	char cDomainName = 0x00;
	unsigned int uiBitsRead = iBitStream.readBits( &cDomainName, 8 );
	if ( ! iBitStream.getStream()->good() ){
		return -2;
	}
	if ( uiBitsRead != 8 ){
		//Error: wrong number of bits read -> wrong domain
		return -2;
	}
	if ( (cDomainName & 0xFC) != 0xF0 ){
		//Error: wrong domain
		return -2;
	}
	//restore type
	if ( pOriginalType != NULL ){
		delete pOriginalType;
		pOriginalType = NULL;
	}
	intFib outStatus = 0;
	
	pOriginalType = cTypeElement::restore( iBitStream, outStatus );
	if ( outStatus < 0 ){
		//Error while loading type
		return outStatus;
	}
	if ( pOriginalType == NULL ){
		//Error: no type loaded
		return -2;
	}
	if ( ( 0 < outStatus ) && ( iReturnValue == 0 ) ){
		//remember warning
		iReturnValue = outStatus;
	}
	
	//read first startbit
	char cStarterBit = 0x00;
	uiBitsRead = iBitStream.readBits( &cStarterBit, 1 );
	if ( ! iBitStream.getStream()->good() ){
		return -2;
	}
	if ( uiBitsRead != 1 ){
		//Error: wrong number of bits read
		return -2;
	}
	vecElementDomains.clear();
	if ( cStarterBit != 0x00 ){
		//read the number of bits for the domain element numbers
		unsigned int uiBitsForElementDomains = 0;
		uiBitsRead = iBitStream.readBits( uiBitsForElementDomains, 8 );
		if ( ! iBitStream.getStream()->good() ){
			return -2;
		}
		if ( uiBitsRead != 8 ){
			//Error: wrong number of bits read
			return -2;
		}
		unsignedIntFib uiDomainElementNumber = 0;
		while ( cStarterBit != 0x00 ){
			//read next domain element number
			uiBitsRead = iBitStream.readBits( uiDomainElementNumber,
				uiBitsForElementDomains );
			if ( ! iBitStream.getStream()->good() ){
				return -2;
			}
			if ( uiBitsRead != uiBitsForElementDomains ){
				//Error: wrong number of bits read
				return -2;
			}
			vecElementDomains.push_back( uiDomainElementNumber );
			
			//read next startbit
			uiBitsRead = iBitStream.readBits( &cStarterBit, 1 );
			if ( ! iBitStream.getStream()->good() ){
				return -2;
			}
			if ( uiBitsRead != 1 ){
				//Error: wrong number of bits read
				return -2;
			}
		}//read all domain element numbers till startbit is 0
	}//end if read domain element numbers
	
	return iReturnValue;
}


/**
 * This method returns a pointer to the type of the element to which
 * domain this domain refer to.
 *
 * @see pOriginalType
 * @return a pointer to the type of the element to which
 * 	domain this domain refer to
 */
const cTypeElement * cDomainReference::getTypeElement() const{
	
	return pOriginalType;
}


/**
 * @return The subdomain of the domain of the element to which it is
 * 	refered to. The element with index i is a subdomain of the domain
 * 	with index i-1 .
 * @see vecElementDomains
 */
const vector<unsignedIntFib> & cDomainReference::getElement() const{
	
	return vecElementDomains;
}





