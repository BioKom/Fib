/**
 * @class cDomainElement
 * file name: cDomainElement.cpp
 * @author Betti Oesterholz
 * @date 06.06.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents an abstract domain element of an domain list.
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
 * This class represents an abstract domain element of an domain list in an
 * root -element. The domain element consist of an domain and an type for
 * the doamin.
 *
 */
/*
History:
06.06.2009  Oesterholz  created
22.02.2012  Oesterholz  method isCompatible() added
*/

#include "cDomainElement.h"


using namespace fib;

/**
 * The constructor for domain elements.
 *
 * @param typeElement the type of the element this domain element
 * 	represents
 * @param domain the domain for this domain element;
 * 	if it is Nullpointer NULL (the standard value) as the domain
 * 	or the given domain is not compatible to the geven type typeElement
 * 	the standard domain of the TypeElement will be set
 */
cDomainElement::cDomainElement( const cTypeElement &typeElementIn,
		const cDomain & domainIn ){

	typeElement = typeElementIn.clone();

	if ( isCompatible( typeElementIn, domainIn ) ){
		domain = domainIn.clone();
	}else{
		domain = typeElementIn.getStandardDomain();
	}
	bDomainIsCopy = true;
}


/**
 * The constructor for domain elements.
 *
 * @param typeElement the type of the element this domain element
 * 	represents
 * @param domain a pointer to the domain for this domain element;
 * 	if it is Nullpointer NULL (the standard value) as the domain
 * 	or the given domain is not compatible to the given type typeElement
 * 	the standard domain of the typeElement will be set
 */
cDomainElement::cDomainElement( const cTypeElement &typeElementIn,
		cDomain * domainIn ){

	typeElement = typeElementIn.clone();

	if ( (domainIn != NULL) && ( isCompatible( typeElementIn, *domainIn ) ) ){
		domain = domainIn;
		bDomainIsCopy = false;
	}else{
		domain = typeElementIn.getStandardDomain();
		bDomainIsCopy = true;
	}
}

/**
 * The copyconstructor for domain elements.
 *
 * @param domainElement the domain element to copy
 */
cDomainElement::cDomainElement( const cDomainElement &domainElement ){

	typeElement = domainElement.getElementType()->clone();
	
	if ( domainElement.bDomainIsCopy ){
		domain = domainElement.getDomain()->clone();
	}else{
		domain = domainElement.getDomain();
	}
	bDomainIsCopy = domainElement.bDomainIsCopy;
}


/**
 * The destructor for domain elements.
 */
cDomainElement::~cDomainElement(){
	//delete the object the class pointer points to
	if ( typeElement != NULL ){
		delete typeElement;
	}
	if ( (domain != NULL) && bDomainIsCopy ){
		delete domain;
	}
}


/**
 * @return the type of the element this domain element represents
 */
cTypeElement *cDomainElement::getElementType() const{
	return typeElement;
}

/**
 * @return a reference to the domain of this domain element;
 * 	so you can adapt the domain
 */
cDomain *cDomainElement::getDomain() const{
	return domain;
}

/**
 * This method sets the domain of this domain element to the given 
 * domain.
 *
 * @param definitionArea the domain for this domain element
 * @return true if the given domain is set, else false
 */
bool cDomainElement::setDomain( const cDomain & domainIn ){

	if ( isCompatible( *typeElement, domainIn ) ){
	
		if ( ((domain) != NULL) && bDomainIsCopy ){
			delete (domain);
		}
		domain = domainIn.clone();
		bDomainIsCopy = true;
		
		return true;
	}//else

	return false;
}

/**
 * This method sets the domain of this domain element to the given 
 * domain.
 * The giving domain won't be copied befor inserted.
 *
 * @param domain a pointer to the domain for this domain element
 * @return true if the given domain is set, else false
 */
bool cDomainElement::setDomain( cDomain * pInDomain ){

	if ( isCompatible( *typeElement, *pInDomain ) ){
	
		if ( (domain != NULL) && bDomainIsCopy ){
			delete (domain);
		}
		domain = pInDomain;
		bDomainIsCopy = false;
		
		return true;
	}//else

	return false;
}


/**
 * This method evaluades the size of the domain element in bits in the
 * compressed file form.
 *
 * @see store()
 * @return the size of the domain element in bits in the compressed form
 */
unsignedLongFib cDomainElement::getCompressedSize() const{
	
	unsignedLongFib ulCompressedSize =
		getElementType()->getCompressedSize() +
		getDomain()->getCompressedSize();
	return ulCompressedSize;
}

/**
 * This method stores this domain element in the XML -format into the
 * given stream.
 *
 * @param ostream the stream where domains should be stored to
 * @return true if this domain element are stored, else false
 */
bool cDomainElement::storeXml( ostream & ostream ) const{
	
	return getElementType()->storeXml( ostream, getDomain() );
}

/**
 * This method stores this domain element in the compressed Fib -format
 * into the given stream.
 * It is needed because the stream can yust store byts but the size of
 * fib -elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the fib -elements.
 *
 * @see cFibElement::store
 * @param stream the stream where this domains should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if the domain element is stored, else false
 */
bool cDomainElement::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
		
	bool bElementTypeStored = getElementType()->store( stream, cRestBits,
		uiRestBitPosition );
	if ( ! bElementTypeStored ){
		return false;
	}
	bool bDomainStored = getDomain()->store( stream, cRestBits,
		uiRestBitPosition);
	if ( ! bDomainStored ){
		return false;
	}

	return true;
}


/**
 * This method checks if the given domain is compatible with the given
 * type.
 * Reference domains (cDomainReference) are compatible with all typs.
 * @see cDomainReference
 *
 * @param typeElement the type for which to check if the domain is compatible
 * @param domain the domain which should be compatible with the given type typeElement
 * @return true if the given domain is compatible with the type typeElement
 */
bool cDomainElement::isCompatible( const cTypeElement &typeElement,
		const cDomain & domain ){
	
	
	if ( domain.isReference() ){
		//reference domains (cDomainReference) are compatible with all typs
		return true;
	}//else no reference domain
	
	return typeElement.isCompatible( domain );
}

