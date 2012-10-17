/**
 * @class cTypeExtObject
 * file name: cTypeExtObject.cpp
 * @author Betti Oesterholz
 * @date 22.07.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents Fib-external object typ.
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
 * This file contains the basisclass of all Fib-external object typs.
 * Fib-external object typs are typs of the elements in an Fib
 * -external object.
 *
 */
/*
History:
22.07.2011  Oesterholz  created
05.01.2012  Oesterholz  externObjekt to externObject
12.02.2012  Oesterholz  restoreXml*() without restoring domain possible
18.04.2012  Oesterholz  Bugfix: replace FirstChild()->ToElement() with
	FirstChildElement()
*/



#include "cTypeExtObject.h"

#include "cDomainVector.h"
#include "cDomainSingle.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainIntegerBit.h"


using namespace fib;


/**
 * The constructor for external object typs.
 */
cTypeExtObject::cTypeExtObject(){
	//nothing to do
}


/**
 * The copyconstructor for external object typs.
 *
 * @param typeExternObject the type external object to copy
 */
cTypeExtObject::cTypeExtObject( const cTypeExtObject & typeExternObject ){
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
unsignedIntFib cTypeExtObject::getType() const{
	return 12;
}


/**
 * This Method returns a pointer to a new instance of the standard
 * domain for elements of this dimension type.
 * You have to delete the returned object after usage.
 *
 * @return the standard domain for elements of this type
 */
cDomain *cTypeExtObject::getStandardDomain() const{
	
	/*construct the vectordomain for the type
		vector( 4 , integerB(32), naturalNumberB(4), naturalNumberB(2), naturalNumberB(2), )*/

	cDomainVector *vectorDomain;
	vector<cDomainSingle*> vecDomains( 4 );
	
	vecDomains[ 0 ] = new cDomainIntegerBit( 32 );
	vecDomains[ 1 ] = new cDomainNaturalNumberBit( 4 );
	vecDomains[ 2 ] = new cDomainNaturalNumberBit( 2 );
	vecDomains[ 3 ] = new cDomainNaturalNumberBit( 2 );
	
	vectorDomain = new cDomainVector( vecDomains );
	
	for ( unsignedIntFib uiActualSubdomain = 0; uiActualSubdomain < 4;
			uiActualSubdomain++ ){
			
		delete vecDomains[ uiActualSubdomain ];
	}
	return vectorDomain;
}


/**
 * This method checks, if this element type is compatible with the
 * given domain. Just domains which are compadible can be used for the
 * elements of this type.
 *
 * @param domain the domain, which should be compatible
 * @return true if the given domain is compatible, else false
 */
bool cTypeExtObject::isCompatible( const cDomain &domain ) const{

	const string szDomainType = domain.getType();
	
	if ( szDomainType.compare( 0, 12, "DomainVector" ) != 0 ){
		//not an vectordomain -> it is not compatible
		return false;
	}/*else if the domain is an vector domain
	-> first domain should be an integer and the remaining 3 natural numbers*/
	cDomainVectorBasis * pVectorDomain = ((cDomainVectorBasis*)(&domain));
	
	const unsignedIntFib uiNumberOfDomainVectorElements =
		pVectorDomain->getNumberOfElements();

	if ( uiNumberOfDomainVectorElements != 4 ){
		//not four subdomains -> it is not compatible
		return false;
	}
	
	const cDomain * pDomainElement1 = pVectorDomain->getElementDomain( 1 );
	if ( pDomainElement1 == NULL ){
		//subdomain missing
		return false;
	}
	const string szDomain1Type = pDomainElement1->getType();
	if ( (szDomain1Type.compare( 0, 19, "DomainNaturalNumber") != 0) &&
			(szDomain1Type.compare( 0, 13, "DomainInteger") != 0) ){
		//if the first subdomain isn't an integer number domain it is not compatible
		return false;
	}//else check remaining 3 subdomains

	for ( unsignedIntFib uiActualSubdomain = 2; uiActualSubdomain <= 4;
			uiActualSubdomain++ ){
		
		const cDomain * pActualDomainElement = pVectorDomain->getElementDomain( uiActualSubdomain );
	
		if ( ! isCounterDomain( pActualDomainElement ) ){
			//subdomain is not a counter domain
			return false;
		}//else check remaining subdomains
	}//else domain compatible
	return true;
}


/**
 * This Method checks if the elementtype of the given type is equal to
 * the elementtype of this type.
 * Two elementtype are not equal if ther are for different Fib-elements.
 *
 * @param typeElement the typeelement to compare with this typeelement
 * @return true if the elementtype of the given type is equal to the
 * 	elementtype of this type, else false
 */
bool cTypeExtObject::equalElementType( const cTypeElement & typeElement ) const{
	//all dimension types are vor the same typeelement
	return ( getType() == typeElement.getType() );
}


/**
 * This Method checks if the given type is equal to this type.
 *
 * @return true if the given type is equal to this type, else false
 */
bool cTypeExtObject::operator==( const cTypeElement &typeElement ) const{
	 
	 return getType() == typeElement.getType();
}


/**
 * This Method clones this object.
 *
 * @return a clone of this object
 */
cTypeExtObject * cTypeExtObject::clone() const{
	return new cTypeExtObject( *this );
}


/**
 * This method evaluades the size of the typeelement in bits in the
 * compressed file form.
 *
 * @see store()
 * @return the size of the typeelement in bits in the compressed form
 */
unsignedLongFib cTypeExtObject::getCompressedSize() const{
	
	return 8;
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
bool cTypeExtObject::storeXml( ostream & ostream,
		const cDomain * domain ) const{
	
	ostream<<"<externObject";
	
	//if given write the domain to the stream
	if ( domain != NULL ){
		
		ostream<<">"<<endl;

		bool bDomainStored = domain->storeXml( ostream );
		if ( ! bDomainStored ){
			return false;
		}
		ostream<<"</externObject>"<<endl;
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
cDomain * cTypeExtObject::restoreXmlWithDomain( const TiXmlElement * pXmlElement,
		intFib & outStatus, const bool bRestoreDomain ){
	
	//check the element type
	if ( pXmlElement == NULL ){
		//Error: noting to restore
		outStatus = -1;
		return NULL;
	}
	string szElementType( pXmlElement->Value() );
	if ( szElementType != "externObject" ){
		//Error: wrong element type to restore
		outStatus = -2;
		return NULL;
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
	}//end if restore domain

	return NULL;
}


/**
 * This method stores this typeelement in the compressed Fib-format
 * into the given stream.
 * It is needed because the stream can yust store byts but the size of
 * Fib-elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the Fib-elements.
 *
 * @see cFibElement::store
 * @param stream the stream where this typeelement should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if the typeelement is stored, else false
 */
bool cTypeExtObject::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	if ( uiRestBitPosition >= 8){
		//error in input
		return false;
	}
	
	char cInVarName = 0xC0; //the name "externObject": 1100 0 00 0

	bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
		&cInVarName, 8 );
	if ( ! bNameStored ){
		return false;
	}
	return true;
}


/**
 * This method restores a type from a bitstream, wher it is
 * stored in the compressed Fib-format.
 *
 * @see store
 * @param iBitStream the stream where the type is stored in,
 * 	because the stream is an cReadBits, any number of bits can be
 * 	readed from it
 * @return an integervalue with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 */
intFib cTypeExtObject::restore( cReadBits & iBitStream ){
	
	//nothing to restiore just check
	if ( ! iBitStream.getStream()->good() ){
		//Error: nothing to load
		return -1;
	}

	//read the typename
	unsigned char cTypeName = 0x00;
	unsigned int uiBitsRead = iBitStream.readBits( (char*)&cTypeName, 8 );
	if ( ! iBitStream.getStream()->good() ){
		return -2;
	}
	if ( uiBitsRead != 8 ){
		return -2;
	}
	if ( cTypeName != 0xC0 ){
		//warning: wrong type
		return 2;
	}
	return 0;
}














