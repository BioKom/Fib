/**
 * @class cTypeFibSet
 * file name: cTypeFibSet.cpp
 * @author Betti Oesterholz
 * @date 04.12.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents Fib set-element typ.
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
 * This file contains the basisclass of all Fib set-element typs.
 * Fib set-element typs are typs of the elements in an set-element.
 *
 */
/*
History:
04.12.2011  Oesterholz  created
12.02.2012  Oesterholz  restoreXml*() without restoring domain possible
18.04.2012  Oesterholz  Bugfix: replace FirstChild()->ToElement() with
	FirstChildElement()
*/



#include "cTypeFibSet.h"

#include "cDomainVector.h"
#include "cDomainSingle.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainIntegerBit.h"
#include "cDomainVectorOpenEnd.h"


using namespace fib;


/**
 * The constructor for set-element typs.
 * 
 * @param uiInNumberOfDomain the number of the set-element domain
 * 	for which this type stands
 */
cTypeFibSet::cTypeFibSet( const unsignedIntFib uiInNumberOfDomain ):
		uiNumberOfDomain( uiInNumberOfDomain ){
	//nothing to do
}


/**
 * The copyconstructor for set-element typs.
 *
 * @param typeExternObject the type set-element to copy
 */
cTypeFibSet::cTypeFibSet( const cTypeFibSet & typeExternObject ):
		uiNumberOfDomain( typeExternObject.uiNumberOfDomain ){
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
unsignedIntFib cTypeFibSet::getType() const{
	return 14;
}


/**
 * This method returns a pointer to a new instance of the standard
 * domain for elements of this dimension type.
 * You have to delete the returned object after usage.
 *
 * @return the standard domain for elements of this type
 */
cDomain *cTypeFibSet::getStandardDomain() const{
	
	/*construct the vectordomain for the type
		vector( 3, naturalNumberB(8), naturalNumberB(32), vectorOpenEnd( 1, IntegerB(32) ) )*/
	
	vector<cDomain*> vecDomains( 3 );
	
	vecDomains[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains[ 1 ] = new cDomainNaturalNumberBit( 32 );

	vector<cDomain*> vecDomainsOpenEnd( 1 );
	vecDomainsOpenEnd[ 0 ] = new cDomainIntegerBit( 32 );
	vecDomains[ 2 ] = new cDomainVectorOpenEnd( vecDomainsOpenEnd );
	
	cDomainVector * pVectorDomain = new cDomainVector( vecDomains );
	
	delete vecDomains[ 0 ];
	delete vecDomains[ 1 ];
	delete vecDomainsOpenEnd[ 0 ];
	delete vecDomains[ 2 ];
	
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
bool cTypeFibSet::isCompatible( const cDomain &domain ) const{

	const string szDomainType = domain.getType();
	
	if ( szDomainType.compare( 0, 12, "DomainVector" ) != 0 ){
		//not an vectordomain -> it is not compatible
		return false;
	}/*else if the domain is an vector domain
	-> first domain should be an integer and the remaining 3 natural numbers*/
	cDomainVectorBasis * pVectorDomain = ((cDomainVectorBasis*)(&domain));
	
	const unsignedIntFib uiNumberOfDomainVectorElements =
		pVectorDomain->getNumberOfElements();

	if ( uiNumberOfDomainVectorElements != 3 ){
		//not 3 subdomains -> it is not compatible
		return false;
	}
	
	const cDomain * pDomainElement1 = pVectorDomain->getElementDomain( 1 );
	if ( ! isCounterDomain( pDomainElement1 ) ){
		//subdomain is not a counter domain
		return false;
	}//else check remaining subdomain
	const cDomain * pDomainElement2 = pVectorDomain->getElementDomain( 2 );
	if ( ! isCounterDomain( pDomainElement2 ) ){
		//subdomain is not a counter domain
		return false;
	}//else check remaining subdomain
	const cDomain * pDomainElement3 = pVectorDomain->getElementDomain( 3 );
	if ( ( pDomainElement3 == NULL ) || ( ! pDomainElement3->isVector() ) ){
		//subdomain missing or isn't a vector domain -> it is not compatible
		return false;
	}//else check remaining subdomain

	return true;
}


/**
 * This method checks if the given type is equal to this type.
 *
 * @return true if the given type is equal to this type, else false
 */
bool cTypeFibSet::operator==( const cTypeElement &typeElement ) const{
	 
	if ( getType() != typeElement.getType() ){
		return false;
	}
	
	return ( getNumberOfDomain() ==
		((cTypeFibSet*)(&typeElement))->getNumberOfDomain() );
}


/**
 * This method clones this object.
 *
 * @return a clone of this object
 */
cTypeFibSet * cTypeFibSet::clone() const{
	return new cTypeFibSet( *this );
}


/**
 * This method evaluades the size of the type element in bits in the
 * compressed file form.
 *
 * @see store()
 * @return the size of the type element in bits in the compressed form
 */
unsignedLongFib cTypeFibSet::getCompressedSize() const{
	
	if ( getNumberOfDomain() == 0 ){
		//no domain number -> no parameter
		return 8;
	}//else
	if ( getNumberOfDomain() < 256 ){
		//short domain number -> 8 bit parameter is enought
		return 8 + 8;
	}//else long domain number -> 64 bit parameter
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
bool cTypeFibSet::storeXml( ostream & ostream,
		const cDomain * domain ) const{
	
	ostream<<"<setElement";
	
	if ( getNumberOfDomain() != 0 ){
		//writ domain number
		ostream<<" domainNr=\""<< getNumberOfDomain()<<"\"";
	}
	
	//if given write the domain to the stream
	if ( domain != NULL ){
		
		ostream<<">"<<endl;

		bool bDomainStored = domain->storeXml( ostream );
		if ( ! bDomainStored ){
			return false;
		}
		ostream<<"</setElement>"<<endl;
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
cDomain * cTypeFibSet::restoreXmlWithDomain( const TiXmlElement * pXmlElement,
		intFib & outStatus, const bool bRestoreDomain ){
	
	//check the element type
	if ( pXmlElement == NULL ){
		//Error: noting to restore
		outStatus = -1;
		return NULL;
	}
	string szElementType( pXmlElement->Value() );
	if ( szElementType != "setElement" ){
		//Error: wrong element type to restore
		outStatus = -2;
		return NULL;
	}
	
	int iNumberOfDomain = 0;
	const char * szXmlNumberOfDomain = pXmlElement->Attribute(
		"domainNr", &iNumberOfDomain );
	if ( szXmlNumberOfDomain != NULL ){
		//number of domain readed
		uiNumberOfDomain = iNumberOfDomain;
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
bool cTypeFibSet::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	if ( uiRestBitPosition >= 8){
		//error in input
		return false;
	}
	
	char cInVarName = 0xD0; //the name "setElement": 1101 0 00 0

	if ( uiNumberOfDomain == 0 ){
		//no domain number -> no parameter
		bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			&cInVarName, 8 );
		if ( ! bNameStored ){
			return false;
		}
	}else if ( uiNumberOfDomain < 256 ){
		//short domain number -> 8 bit parameter is enought
		cInVarName = cInVarName | 0x02;
		unsigned char cParameter = uiNumberOfDomain;
		
		bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			&cInVarName, 8 );
		if ( ! bNameStored ){
			return false;
		}
		bool bParameterStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			(unsigned long)(cParameter), 8 );
		if ( ! bParameterStored ){
			return false;
		}

	}else{
		//long domain number -> 64 bit parameter
		cInVarName = cInVarName | 0x04;
		unsigned long long ulParameter = uiNumberOfDomain;
		
		bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			&cInVarName, 8 );
		if ( ! bNameStored ){
			return false;
		}
		bool bParameterStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			ulParameter, 64 );
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
intFib cTypeFibSet::restore( cReadBits & iBitStream ){
	
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
	if ( (cTypeName & 0xF8) != 0xD0 ){
		//warning: wrong type
		return -2;
	}
	if ( (cTypeName & 0x06) == 0x00 ){
		//no domain number -> no parameter -> domain number is 0
		uiNumberOfDomain = 0;
	
	}else if ( (cTypeName & 0x06) == 0x02 ){
		//short domain number -> 8 bit parameter is enought
		unsignedIntFib uiNumberDomain = 0x00;
		uiBitsRead = iBitStream.readBits( uiNumberDomain, 8 );
		if ( ! iBitStream.getStream()->good() ){
			return -2;
		}
		if ( uiBitsRead != 8 ){
			return -2;
		}
		uiNumberOfDomain = uiNumberDomain;
	
	}else if ( (cTypeName & 0x06) == 0x04 ){
		//long domain number -> 64 bit parameter
		unsignedLongFib ulNumberDomain = 0;
		uiBitsRead = iBitStream.readBits( ulNumberDomain, 64 );
		if ( ! iBitStream.getStream()->good() ){
			return -2;
		}
		if ( uiBitsRead != 64 ){
			return -2;
		}
		uiNumberOfDomain = ulNumberDomain;
	}else{//warning: wrong parameter
		uiNumberOfDomain = 0;
		return -2;
	}
	return 0;
}


/**
 * @return the number of the domain for which this type stands
 * 	@see uiNumberOfDomain
 */
unsignedIntFib cTypeFibSet::getNumberOfDomain() const{
	
	return uiNumberOfDomain;
}
















