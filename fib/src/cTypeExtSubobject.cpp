/**
 * @class cTypeExtSubobject
 * file name: cTypeExtSubobject.cpp
 * @author Betti Oesterholz
 * @date 06.11.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents an Fib external subobject type.
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
 * This file contains the class of Fib external subobject type.
 * Fib external subobject type are typs for the number of external subobjects, when
 * they are stored. When saving external subobjects they will be numbered serially,
 * the numbers of the external subobjects will come from the domain for the
 * cTypeExtSubobject. The external subobjectsstrings will be exported to the root
 * optional part.
 *
 */
/*
History:
06.11.2011  Oesterholz  created
29.01.2011  Oesterholz  FEATURE_EXT_SUBOBJECT_INPUT_VECTOR implemented:
	the input values are now a vector of values
31.01.2012  Oesterholz  isInherited() method added
12.02.2012  Oesterholz  restoreXml*() without restoring domain possible
18.04.2012  Oesterholz  Bugfix: replace FirstChild()->ToElement() with
	FirstChildElement()
*/


#include "cTypeExtSubobject.h"

#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"

#include "nBitStream.h"

using namespace fib;


#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

/**
 * Standardconstructor for the external subobjects type.
 * 
 * @param uiInNumberExtSubobject the number of the subobject for which the
 * 	type is @see uiNumberExtSubobject
 */
cTypeExtSubobject::cTypeExtSubobject( const unsignedIntFib uiInNumberExtSubobject ):
		uiNumberExtSubobject( uiInNumberExtSubobject ){
	//nothing to do
}


/**
 * Copy constructor for the external subobjects type.
 * 
 * @param typeExtSubobject the cTypeExtSubobject to copy
 */
cTypeExtSubobject::cTypeExtSubobject( const cTypeExtSubobject & typeExtSubobject ):
		uiNumberExtSubobject( typeExtSubobject.uiNumberExtSubobject ){
	//nothing to do
}

#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

/**
 * Standardconstructor for the external subobjects type.
 */
cTypeExtSubobject::cTypeExtSubobject(){
	//nothing to do
}


/**
 * Copy constructor for the external subobjects type.
 * 
 * @param typeExtSubobject the cTypeExtSubobject to copy
 */
cTypeExtSubobject::cTypeExtSubobject( const cTypeExtSubobject & typeExtSubobject ){
	//nothing to do
}

#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR


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
unsignedIntFib cTypeExtSubobject::getType() const{
	
	return 13;
}


/**
 * This method checks, if this element type is compatible with the
 * given domain. Just domains which are compadible can be used for the
 * elements of this type.
 *
 * @param domain the domain, which should be compatible
 * @return true if the given domain is compatible, else false
 */
bool cTypeExtSubobject::isCompatible( const cDomain &domain ) const{

#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
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
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//this type is compatible to conter domains
	if ( isCounterDomain( &domain ) ){
		//subdomain is not a counter domain
		return true;
	}//else not compatible
	return false;
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
}


/**
 * This Method returns a pointer to a new instance of the standart
 * domain for elements of this type.
 * You have to delete the returned object after usage.
 *
 * @return the standart domain for elements of this type
 */
cDomain * cTypeExtSubobject::getStandardDomain() const{
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//construct the vector domain for the type: vector( 0 )
	vector<cDomain*> vecDomainE0( 0 );
	
	cDomainVector * pVectorDomain =
		new cDomainVector( vecDomainE0 );
	
	return pVectorDomain;

#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	return new cDomainNaturalNumberBit( 4 );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
}


/**
 * This Method checks if the given type is equal to this type.
 *
 * @return true if the given type is equal to this type, else false
 */
bool cTypeExtSubobject::operator==( const cTypeElement & typeElement ) const{
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	if ( getType() != typeElement.getType() ){
		return false;
	}
	
	return ( getNumberOfExtSubobject() ==
		((cTypeExtSubobject*)(&typeElement))->getNumberOfExtSubobject() );

#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	return (getType() == typeElement.getType());
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
}


/**
 * This Method clones this object.
 *
 * @return a clone of this object
 */
cTypeExtSubobject * cTypeExtSubobject::clone() const{
	
	return new cTypeExtSubobject( *this );
}

/**
 * This method evaluades the size of the typeelement in bits in the
 * compressed file form.
 *
 * @see store()
 * @return the size of the typeelement in bits in the compressed form
 */
unsignedLongFib cTypeExtSubobject::getCompressedSize() const{

#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	if ( getNumberOfExtSubobject() == 0 ){
		//no external subobjec -> no parameter
		return 8;
	}//else
	if ( getNumberOfExtSubobject() < 256 ){
		//short external subobject number -> 8 bit parameter is enought
		return 8 + 8;
	}//else long external subobjec number -> 64 bit parameter
	return 8 + 64;
	
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	return 8;
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
}

/**
 * This method stores this type in the XML -format into the
 * given stream.
 *
 * @param ostream the stream where domains should be stored to
 * @param domain the domain which should be stored to this type;
 * 	if a Nullpointer NULL (the standardvalue) is given, no domain
 * 	will be stored to this type
 * @return true if this type are stored, else false
 */
bool cTypeExtSubobject::storeXml( ostream & ostream,
		const cDomain * domain ) const{
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	ostream<<"<externSubobject number=\""<<getNumberOfExtSubobject()<<"\"";
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	ostream<<"<externSubobject";
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	//if given write the domain to the stream
	if ( domain != NULL ){
		
		ostream<<">"<<endl;

		bool bDomainStored = domain->storeXml( ostream );
		if ( ! bDomainStored ){
			return false;
		}
		ostream<<"</externSubobject>"<<endl;
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
cDomain * cTypeExtSubobject::restoreXmlWithDomain( const TiXmlElement * pXmlElement,
		intFib & outStatus, const bool bRestoreDomain ){
	
	//check the element type
	if ( pXmlElement == NULL ){
		//Error: noting to restore
		outStatus = -1;
		return NULL;
	}
	string szElementType( pXmlElement->Value() );
	if ( szElementType != "externSubobject" ){
		//Error: wrong element type to restore
		outStatus = -2;
		return NULL;
	}
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	int iExtSubobjectNumber = 0;
	const char * szXmlExtSubobjectNumber = pXmlElement->Attribute(
		"number", &iExtSubobjectNumber );
	if ( szXmlExtSubobjectNumber != NULL ){
		//external subobject number readed
		uiNumberExtSubobject = iExtSubobjectNumber;
	}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
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
 * This method stores this typeelement in the compressed Fib format
 * into the given stream.
 * It is needed because the stream can yust store byts but the size of
 * Fib elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the Fib elements.
 *
 * @see cFibElement::store
 * @param stream the stream where this typeelement should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if the typeelement is stored, else false
 */
bool cTypeExtSubobject::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	if ( uiRestBitPosition >= 8){
		//error in input
		return false;
	}
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	char cExtObjectName = 0xC8; //the name "externSubobject"

	if ( uiNumberExtSubobject == 0 ){
		//no external subobject number -> no parameter
		bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			&cExtObjectName, 8 );
		if ( ! bNameStored ){
			return false;
		}
	}else if (  uiNumberExtSubobject < 256 ){
		//short external subobject number -> 8 bit parameter is enought
		cExtObjectName = cExtObjectName | 0x02;
		unsigned char cParameter = uiNumberExtSubobject;
		
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
		//long external subobject number -> 64 bit parameter
		cExtObjectName = cExtObjectName | 0x04;
		unsigned long long lParameter = uiNumberExtSubobject;
		
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
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	char cExtObjectName = 0xC8; //the name "externSubobject"

	bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
		&cExtObjectName, 8 );
	if ( ! bNameStored ){
		return false;
	}

#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

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
intFib cTypeExtSubobject::restore( cReadBits & iBitStream ){
	
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
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	if ( (cTypeName & 0xF8) != 0xC8 ){
		//Error: wrong type
		return -2;
	}
	if ( (cTypeName & 0x06) == 0x00 ){
		//no external subobject number -> no parameter -> external subobject number is 0
		uiNumberExtSubobject = 0;
	
	}else if ( (cTypeName & 0x06) == 0x02 ){
		//short external subobject number -> 8 bit parameter is enought
		unsigned int iExtSubobjNumber = 0x00;
		uiBitsRead = iBitStream.readBits( iExtSubobjNumber, 8 );
		if ( ! iBitStream.getStream()->good() ){
			return -2;
		}
		if ( uiBitsRead != 8 ){
			return -2;
		}
		uiNumberExtSubobject = iExtSubobjNumber;
	
	}else if ( (cTypeName & 0x06) == 0x04 ){
		//long external subobject number -> 64 bit parameter
		unsigned long lExtSubobjNumber = 0;
		uiBitsRead = iBitStream.readBits( lExtSubobjNumber, 64 );
		if ( ! iBitStream.getStream()->good() ){
			return -2;
		}
		if ( uiBitsRead != 64 ){
			return -2;
		}
		uiNumberExtSubobject = lExtSubobjNumber;
	}else{//warning: wrong parameter
		uiNumberExtSubobject = 0;
		return -2;
	}
	
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	if ( cTypeName != 0xC8 ){
		//warning: wrong type
		return 2;
	}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	return 0;
}


/**
 * @return true if domains of this type are inerted else false
 */
bool cTypeExtSubobject::isInherited() const{
	///domains for external subobjects are not inerhited
	return false;
}


#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
/**
 * @return the number of the subobject for which the type is
 * @see uiNumberExtSubobject;
 */
unsignedIntFib cTypeExtSubobject::getNumberOfExtSubobject() const{
	
	return uiNumberExtSubobject;
}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR






