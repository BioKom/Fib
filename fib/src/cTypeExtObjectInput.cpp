/**
 * @class cTypeExtObjectInput
 * file name: cTypeExtObjectInput.cpp
 * @author Betti Oesterholz
 * @date 21.01.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents Fib external object input type.
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
 * This file contains the basisclass of all Fib set-Element typs.
 * Fib set-Element typs are typs of the elements in an external object input.
 *
 */
/*
History:
21.01.2012  Oesterholz  created
12.02.2012  Oesterholz  restoreXml*() without restoring domain possible
18.04.2012  Oesterholz  Bugfix: replace FirstChild()->ToElement() with
	FirstChildElement()
*/



#include "cTypeExtObjectInput.h"

#include "cDomainVector.h"
#include "cDomainSingle.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainIntegerBit.h"
#include "cDomainVectorOpenEnd.h"


using namespace fib;


/**
 * The constructor for external object input typs.
 * 
 * @param uiInExtObjectIdentifier the number of the external object input domain
 * 	for which this type stands
 */
cTypeExtObjectInput::cTypeExtObjectInput( const longFib uiInExtObjectIdentifier ):
		lExtObjectIdentifier( uiInExtObjectIdentifier ){
	//nothing to do
}


/**
 * The copyconstructor for external object input typs.
 *
 * @param typeExternObject the type external object input to copy
 */
cTypeExtObjectInput::cTypeExtObjectInput( const cTypeExtObjectInput & typeExternObject ):
		lExtObjectIdentifier( typeExternObject.lExtObjectIdentifier ){
	//nothing to do
}


/**
 * This Function returns for the type of the element an number.
 * The values, which are returned, mean:
 * 	- 1: cTypeDimension
 * 	- 2: cTypeUnderArea
 * 	- 3: cTypeUnderFunction
 * 	- 5: cTypeInVar
 * 	- 6: cTypeProperty
 * 	- 10: cTypeVariable
 * 	- 11: cTypeComments
 * 	- 12: cTypeExtObject
 * 	- 13: cTypeExtSubobject
 * 	- 14: cTypeFibSet
 * 	- 15: cTypeFibMatrix
 * 	- 16: cTypeExtObjectInput
 *
 * @return for the type of the element an number
 */
unsignedIntFib cTypeExtObjectInput::getType() const{
	return 16;
}


/**
 * This method returns a pointer to a new instance of the standard
 * domain for elements of this dimension type.
 * You have to delete the returned object after usage.
 *
 * @return the standard domain for elements of this type
 */
cDomain *cTypeExtObjectInput::getStandardDomain() const{
	
	//construct the vector domain for the type: vectorOpenEnd( integerB(8) )
	vector<cDomain*> vecDomainsOpenEnd( 1 );
	vecDomainsOpenEnd[ 0 ] = new cDomainIntegerBit( 8 );
	
	cDomainVectorOpenEnd * pVectorDomain =
		new cDomainVectorOpenEnd( vecDomainsOpenEnd );
	
	delete vecDomainsOpenEnd[ 0 ];
	
	return pVectorDomain;
}


/**
 * This method checks, if this element type is compatible with the
 * given domain. Just domains which are compadible can be used for the
 * elements of this type.
 *
 * @param domain the domain, which should be compatible
 * @return true if the given domain is compatible, else false
 */
bool cTypeExtObjectInput::isCompatible( const cDomain &domain ) const{

	if ( ! domain.isVector() ){
		//not an vector domain -> it is not compatible
		return false;
	}//else if the domain is an vector domain -> chack subdomains
	
	const cDomainVectorBasis * pVecDomain =
		(cDomainVectorBasis*)&domain;
	const unsignedIntFib uiNumberofElements =
		pVecDomain->getNumberOfElements();
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= uiNumberofElements; uiActualElement++ ){
		
		const cDomain * pActualSubdomain =
			pVecDomain->getElementDomain( uiActualElement );
		if ( pActualSubdomain == NULL ){
			//no subdomain
			return false;
		}
		if ( ! pActualSubdomain->isScalar() ){
			//not a scalar domain -> not valid
			return false;
		}
	}//else all subdomains are all scalars -> domain is compatible
	return true;
}


/**
 * This method checks if the given type is equal to this type.
 *
 * @return true if the given type is equal to this type, else false
 */
bool cTypeExtObjectInput::operator==( const cTypeElement &typeElement ) const{
	 
	if ( getType() != typeElement.getType() ){
		return false;
	}
	
	return ( getExtObjectIdentifier() ==
		((cTypeExtObjectInput*)(&typeElement))->getExtObjectIdentifier() );
}


/**
 * This method clones this object.
 *
 * @return a clone of this object
 */
cTypeExtObjectInput * cTypeExtObjectInput::clone() const{
	
	return new cTypeExtObjectInput( *this );
}


/**
 * This method evaluades the size of the type element in bits in the
 * compressed file form.
 *
 * @see store()
 * @return the size of the type element in bits in the compressed form
 */
unsignedLongFib cTypeExtObjectInput::getCompressedSize() const{
	
	if ( getExtObjectIdentifier() == 0 ){
		//no identifier -> no parameter
		return 8;
	}//else
	if ( ( -129L < getExtObjectIdentifier()  ) &&
			( getExtObjectIdentifier() < 128L ) ){
		//short identifier number -> 8 bit parameter is enought
		return 8 + 8;
	}//else long identifier number -> 64 bit parameter
	return 8 + 64;
}


/**
 * This method stores this type in the XML-format into the
 * given stream.
 *
 * @param ostream the stream where domains should be stored to
 * @param domain the domain which should be stored to this type;
 * 	if a Nullpointer NULL (the standardvalue) is given, no domain
 * 	will be stored to this type
 * @return true if this type are stored, else false
 */
bool cTypeExtObjectInput::storeXml( ostream & ostream,
		const cDomain * domain ) const{
	
	ostream<<"<externObjectInput identifier=\""<< getExtObjectIdentifier()<<"\"";
	
	//if given write the domain to the stream
	if ( domain != NULL ){
		
		ostream<<">"<<endl;

		bool bDomainStored = domain->storeXml( ostream );
		if ( ! bDomainStored ){
			return false;
		}
		ostream<<"</externObjectInput>"<<endl;
	}else{
		ostream<<"/>"<<endl;
	}
	
	return true;
}


/**
 * This method restores a type with a domain in the XML -format from an
 * TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node wher the type is stored in
 * @param outStatus an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 * @param bRestoreDomain if true a domain is to be asumed in the type
 * 	element and it will be restored, else no domain will be restores
 * @return a pointer to the restored domain, or NULL if it couldn't be restored
 */
cDomain * cTypeExtObjectInput::restoreXmlWithDomain( const TiXmlElement * pXmlElement,
		intFib & outStatus, const bool bRestoreDomain ){
	
	//check the element type
	if ( pXmlElement == NULL ){
		//Error: noting to restore
		outStatus = -1;
		return NULL;
	}
	string szElementType( pXmlElement->Value() );
	if ( szElementType != "externObjectInput" ){
		//Error: wrong element type to restore
		outStatus = -2;
		return NULL;
	}
	
	int iExtObjectIdentifier = 0;
	const char * szXmlExtObjectIdentifier = pXmlElement->Attribute(
		"identifier", &iExtObjectIdentifier );
	if ( szXmlExtObjectIdentifier != NULL ){
		//identifier readed
		lExtObjectIdentifier = iExtObjectIdentifier;
	}

	if ( bRestoreDomain ){
		//restore the domain
		const TiXmlElement * pXmlElementType = NULL;
		if ( pXmlElement->FirstChild() ){
			
			pXmlElementType = pXmlElement->FirstChildElement();
		}
		const TiXmlElement * pXmlElementDomain = NULL;
		for( ; pXmlElementType != NULL;
				pXmlElementType = pXmlElementType->NextSiblingElement() ){
			
			if ( pXmlElementDomain == NULL ){
				pXmlElementDomain = pXmlElementType;
			}else{//Warning: more than one domain to restore
				outStatus = 2;
				break;
			}
		}
		//restore the domain
		cDomain * pRestoredDomain = NULL;
		if ( pXmlElementDomain ){
			int iDomainRestoreReturn = 0;
			pRestoredDomain = cDomain::restoreXml( pXmlElementDomain, iDomainRestoreReturn );
			
			if ( iDomainRestoreReturn != 0 ){
				outStatus = iDomainRestoreReturn;
			}
		}else{
			outStatus = 2;
		}
		return pRestoredDomain;
	}//end if restore domain + else no domain to return

	return NULL;
}


/**
 * This method stores this type element in the compressed Fib format
 * into the given stream.
 * It is needed because the stream can yust store byts but the size of
 * Fib elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the Fib elements.
 *
 * @see cFibElement::store
 * @param stream the stream where this type element should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if the type element is stored, else false
 */
bool cTypeExtObjectInput::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	if ( uiRestBitPosition >= 8){
		//error in input
		return false;
	}
	
	char cExtObjectName = 0xE0; //the name "externObjectInput": 1110 0 00 0

	if ( lExtObjectIdentifier == 0 ){
		//no identifier -> no parameter
		bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			&cExtObjectName, 8 );
		if ( ! bNameStored ){
			return false;
		}
	}else if ( ( -129L < lExtObjectIdentifier ) &&
			( lExtObjectIdentifier < 128L ) ){
		//short identifier -> 8 bit parameter is enought
		cExtObjectName = cExtObjectName | 0x02;
		char cParameter = lExtObjectIdentifier;
		
		const bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			&cExtObjectName, 8 );
		if ( ! bNameStored ){
			return false;
		}
		const bool bParameterStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			(unsigned char)(cParameter), 8 );
		if ( ! bParameterStored ){
			return false;
		}

	}else{
		//long identifier -> 64 bit parameter
		cExtObjectName = cExtObjectName | 0x04;
		long long lParameter = lExtObjectIdentifier;
		
		const bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			&cExtObjectName, 8 );
		if ( ! bNameStored ){
			return false;
		}
		const bool bParameterStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			lParameter, 64 );
		if ( ! bParameterStored ){
			return false;
		}
	}
	return true;
}


/**
 * This method restores a type from a bitstream, wher it is
 * stored in the compressed Fib format.
 *
 * @see store
 * @param iBitStream the stream where the type is stored in,
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
intFib cTypeExtObjectInput::restore( cReadBits & iBitStream ){
	
	//nothing to restiore just check
	if ( ! iBitStream.getStream()->good() ){
		//Error: nothing to load
		return -1;
	}

	//read the typename
	char cTypeName = 0x00;
	unsigned int uiBitsRead = iBitStream.readBits( &cTypeName, 8 );
	if ( ! iBitStream.getStream()->good() ){
		return -2;
	}
	if ( uiBitsRead != 8 ){
		return -2;
	}
	if ( (cTypeName & 0xF8) != 0xE0 ){
		//Error: wrong type
		return -2;
	}
	if ( (cTypeName & 0x06) == 0x00 ){
		//no identifier -> no parameter -> identifier is 0
		lExtObjectIdentifier = 0;
	
	}else if ( (cTypeName & 0x06) == 0x02 ){
		//short identifier -> 8 bit parameter is enought
		int iIdentifier = 0x00;
		uiBitsRead = iBitStream.readBits( iIdentifier, 8 );
		if ( ! iBitStream.getStream()->good() ){
			return -2;
		}
		if ( uiBitsRead != 8 ){
			return -2;
		}
		lExtObjectIdentifier = iIdentifier;
	
	}else if ( (cTypeName & 0x06) == 0x04 ){
		//long identifier -> 64 bit parameter
		long long lIdentifier = 0;
		uiBitsRead = iBitStream.readBits( lIdentifier, 64 );
		if ( ! iBitStream.getStream()->good() ){
			return -2;
		}
		if ( uiBitsRead != 64 ){
			return -2;
		}
		lExtObjectIdentifier = lIdentifier;
	}else{//warning: wrong parameter
		lExtObjectIdentifier = 0;
		return -2;
	}
	return 0;
}


/**
 * @return the identifier of the external object for which this type stands
 * 	@see lExtObjectIdentifier
 */
longFib cTypeExtObjectInput::getExtObjectIdentifier() const{
	
	return lExtObjectIdentifier;
}















