/**
 * @class cDomainVectorOpenEnd
 * file name: cDomainVectorOpenEnd.cpp
 * @author Betti Oesterholz
 * @date 03.12.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a vector domain.
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
 * This file contains the class for vector Fib-domains for variable domains.
 * A vector domain is defined with the domains of it's elements.
 * see vectorOpenEnd( E , D_1, ... , D_E)
 * This is the domain for vectors with E or more elements, in wich the i'th
 * element has the domain D_i, for i lower E, and else the domain D_E. 
 * This domain is for elements, which can contain vectors of diffent sizes.
 * The number of elements in the vector should be determined by the
 * containing fib-element. 
 *
 *//*
History:
03.12.2011  Oesterholz  created
18.04.2012  Oesterholz  Bugfix: replace FirstChild()->ToElement() with
	FirstChildElement()
*/

#include "cDomainVectorOpenEnd.h"

using namespace fib;

/**
 * This constructor of the cDomainVectorOpenEnd element.
 *
 * @param vecInElementDomains the vector with the domains for the vector
 * 	elements
 */
cDomainVectorOpenEnd::cDomainVectorOpenEnd( const vector<cDomain*> & vecInElementDomains ):
	vecElementDomains( vecInElementDomains.size() ){

	for ( unsigned long actualElement = 0;
			actualElement < vecInElementDomains.size(); actualElement++ ){

		this->vecElementDomains[ actualElement ] =
			vecInElementDomains[ actualElement ]->clone();
	}

}


/**
 * This constructor of the cDomainVectorOpenEnd element.
 *
 * @param vecInElementDomains the vector with the domains for the vector
 * 	elements
 */
cDomainVectorOpenEnd::cDomainVectorOpenEnd( const vector<cDomainSingle*> & vecInElementDomains ):
	vecElementDomains( vecInElementDomains.size() ){

	for ( unsigned long actualElement = 0;
			actualElement < vecInElementDomains.size(); actualElement++ ){

		this->vecElementDomains[ actualElement ] =
			vecInElementDomains[ actualElement ]->clone();
	}

}


/**
 * This destructor of the cDomainVectorOpenEnd element.
 */
cDomainVectorOpenEnd::~cDomainVectorOpenEnd(){

	for ( unsigned long actualElement = 0;
			actualElement < vecElementDomains.size(); actualElement++ ){

		delete vecElementDomains[ actualElement ];
	}
}


/**
 * @return the type of the domain as an string
 */
string cDomainVectorOpenEnd::getType() const{
	
	return "DomainVectorOpenEnd";
}


/**
 * This method checks if the given vector is an element of the
 * domain. If the value dValue is an element of the
 * domain true is returned, else false.
 *
 * @param fibVector the vector for which to check, if it is an element
 * 	of the domain
 * @return if the vector fibVector is an element of the domain true
 * 	is returned, else false
 */
bool cDomainVectorOpenEnd::isElement( const cFibVector &fibVector ) const{

	if ( fibVector.getNumberOfElements() < vecElementDomains.size() ){
		/*the vector has not the correct size, it is missing elements
		-> it isn't an element of the domain*/
		return false;
	}
	const unsigned long ulVectorElements = fibVector.getNumberOfElements();
	for ( unsigned long ulActualElement = 1;
			ulActualElement <= ulVectorElements; ulActualElement++ ){
		
		if ( fibVector.isVariable( ulActualElement ) ){
			//skip variables
			continue;
		}
		const cDomain * pElementDomain = getElementDomain( ulActualElement );
		if ( pElementDomain != NULL ){
			
			if ( pElementDomain->isScalar() ){
				const cDomainSingle * pElementDomainScalar =
					(const cDomainSingle *)pElementDomain;
				if ( ! (pElementDomainScalar->isElement(
						fibVector.getValue( ulActualElement ) ) ) ){
					/*the vectorelement is not in the domain for the element
					-> the vector is not in this vectordomain*/
					return false;
				}
			/*TODO if vectors can contain other vectors
			}else{
				const cDomainVectorBasis * pElementDomainVector =
					(const cDomainVectorBasis *)pElementDomain;
				if ( ! (cDomainVectorBasis->isElement(
						fibVector.getValue( ulActualElement ) ) ) ){
					//the vectorelement is not in the domain for the element
					//-> the vector is not in this vectordomain
					return false;
				}
			*/
			}
		}else{//no domain for this element
			return false;
		}
	}

	//all checks are positiv
	return true;
}


/**
 * This method checks if the given vector is inside the domain
 * boundaries. If the value dValue is inside of the domain boundaries
 * true is returned, else false.
 * A vector is inside of the vector domain boudaries, if all its
 * elements are inside ther correspondending element domain boundaries.
 *
 * @param fibVector the vector for which to check, if it is inside of
 * 	the domain boundaries
 * @return if the vector fibVector is inside of the domain boundaries
 * 	true is returned, else false
 */
bool cDomainVectorOpenEnd::isInBoundaries( const cFibVector &fibVector ) const{

	if ( fibVector.getNumberOfElements() < vecElementDomains.size() ){
		/*the vector has not the correct size, it is missing elements
		-> it isn't an element of the domain*/
		return false;
	}
	const unsigned long ulVectorElements = fibVector.getNumberOfElements();
	for ( unsigned long ulActualElement = 1;
			ulActualElement <= ulVectorElements; ulActualElement++ ){
		
		if ( fibVector.isVariable( ulActualElement ) ){
			//skip variables
			continue;
		}
		const cDomain * pElementDomain = getElementDomain( ulActualElement );
		
		if ( pElementDomain != NULL ){
			
			if ( pElementDomain->isScalar() ){
				const cDomainSingle * pElementDomainScalar =
					(const cDomainSingle *)pElementDomain;
				if ( ! (pElementDomainScalar->isInBoundaries(
						fibVector.getValue( ulActualElement ) ) ) ){
					/*the vectorelement is not in the domain for the element
					-> the vector is not in this vectordomain*/
					return false;
				}
			/*TODO if vectors can contain other vectors
			}else{
				const cDomainVectorBasis * pElementDomainVector =
					(const cDomainVectorBasis *)pElementDomain;
				if ( ! (cDomainVectorBasis->isInBoundaries(
						fibVector.getValue( ulActualElement ) ) ) ){
					//the vectorelement is not in the domain for the element
					//-> the vector is not in this vectordomain
					return false;
				}
			*/
			}
		}else{//no domain for this element
			return false;
		}
	}

	//all checks are positiv
	return true;
}


/**
 * This method round the given value vector to an vector in the
 * domain of this object.
 * The rounded vector will be the vector, wich elements have the minimal
 * summed distance to the elements of the given vector fibVector. If more
 * than one such vector exists, the vector wich first n elements have
 * the minimal summed distance to the first n elements of the given 
 * vector fibVector. Wher n is first the number of elements in the
 * vector, and than is decrased to 1 in steps of 1. If again more such
 * vectors exists, the one with the smalest k elements is choosen, wher
 * k begins with 1 and is incrased to the number of vectorelements in
 * the input vector.
 * ATTENTION: The returned vector will not be deleted automaticly, you
 * 	have to delete it.
 *
 * @param fibVector the vector which should be rounded
 * @return the rounded vector of fibVector
 */
cFibVector * cDomainVectorOpenEnd::round( cFibVector &fibVector ) const{
	
	const unsignedIntFib uiNumberOfElementsToCreate =
		( fibVector.getNumberOfElements() < vecElementDomains.size() )?
			vecElementDomains.size() : fibVector.getNumberOfElements();
	
	cFibVector * roundedVector = fibVector.createInstance(
		uiNumberOfElementsToCreate );
	
	unsignedIntFib iNumberElement;
	for ( iNumberElement = 1;
			iNumberElement <= fibVector.getNumberOfElements() &&
			iNumberElement <= roundedVector->getNumberOfElements();
			iNumberElement++ ){
		
		if ( fibVector.isVariable( iNumberElement ) ){
			/*the element is an variable
			-> just insert it in rounded vector*/
			roundedVector->setVariable( iNumberElement,
				fibVector.getVariable( iNumberElement ) );
		}else{
			/*the element is an value 
			-> insert the rounded value in the rounded vector*/
			const cDomain * pElementDomain =
				getElementDomain( iNumberElement );
			if ( pElementDomain != NULL ){
				
				if ( pElementDomain->isScalar() ){
					
					const cDomainSingle * pElementDomainScalar =
						(const cDomainSingle *)pElementDomain;
					
					roundedVector->setValue( iNumberElement,
						pElementDomainScalar->round(
							fibVector.getValue( iNumberElement ) ) );
				/*TODO if vectors can contain other vectors
				}else{
					const cDomainVectorBasis * pElementDomainVector =
						(const cDomainVectorBasis *)pElementDomain;
					if ( ! (cDomainVectorBasis->isInBoundaries(
							fibVector.getValue( actualElement + 1 ) ) ) ){
						//the vectorelement is not in the domain for the element
						//-> the vector is not in this vectordomain
						return false;
					}
				*/
				}
			}
		}
	}
	//round missing elements
	for ( ; iNumberElement <= roundedVector->getNumberOfElements();
			iNumberElement++ ){
		
		/*the element is an value 
		-> insert the rounded value in the rounded vector*/
		const cDomain * pElementDomain = getElementDomain( iNumberElement );
		if ( pElementDomain != NULL ){
			
			if ( pElementDomain->isScalar() ){
				
				const cDomainSingle * pElementDomainScalar =
					(const cDomainSingle *)pElementDomain;
				
				roundedVector->setValue( iNumberElement,
					pElementDomainScalar->round( 0 ) );
			/*TODO if vectors can contain other vectors
			}else{
				const cDomainVectorBasis * pElementDomainVector =
					(const cDomainVectorBasis *)pElementDomain;
				if ( ! (cDomainVectorBasis->isInBoundaries(
						fibVector.getValue( actualElement + 1 ) ) ) ){
					//the vectorelement is not in the domain for the element
					//-> the vector is not in this vectordomain
					return false;
				}
			*/
			}
		}
	}

	return roundedVector;
}


/**
 * This method returns the number of elements in the vectors of the
 * domain.
 *
 * @return the number of elements in the vectors of the domain
 */
unsignedIntFib cDomainVectorOpenEnd::getNumberOfElements() const{
	
	return (unsignedIntFib)( vecElementDomains.size() );
}


/**
 * This method returns the domain of the iNumberOfElement'th element in
 * the vectors of the domain.
 *
 * @param iNumberOfElement the elementnumber for which the domain is to
 * 	return
 * @return domain of the iNumberOfElement'th element in the vectors of
 * 	the domain
 */
cDomain * cDomainVectorOpenEnd::getElementDomain( 
		const unsignedIntFib iNumberOfElement ){
	
	if ( iNumberOfElement < 1 ){
		//no such element
		return NULL;
	}
	if ( vecElementDomains.size() <= iNumberOfElement ){
		//return last domain
		return vecElementDomains.back();
	}
	
	return vecElementDomains[ iNumberOfElement - 1 ];
}


/**
 * This method returns the domain of the iNumberOfElement'th element in
 * the vectors of the domain.
 *
 * @param iNumberOfElement the elementnumber for which the domain is to
 * 	return
 * @return domain of the iNumberOfElement'th element in the vectors of
 * 	the domain
 */
const cDomain * cDomainVectorOpenEnd::getElementDomain( 
		const unsignedIntFib iNumberOfElement ) const{
	
	if ( iNumberOfElement < 1 ){
		//no such element
		return NULL;
	}
	if ( vecElementDomains.size() <= iNumberOfElement ){
		//return last domain
		return vecElementDomains.back();
	}
	
	return vecElementDomains[ iNumberOfElement - 1 ];
}


/**
 * This Method clones this object.
 *
 * @return a clone of this object
 */
cDomainVectorOpenEnd * cDomainVectorOpenEnd::clone() const{

	return new cDomainVectorOpenEnd( vecElementDomains );
}


/**
 * This Method checks if the given domain is equal to this domain.
 *
 * @return true if the given domain is equal to this domain, else false
 */
bool cDomainVectorOpenEnd::operator==( const cDomain &domain ) const{

	if ( getType() == domain.getType() ){
		//same type -> check all the vector elements
		cDomainVectorOpenEnd *otherDomainVector = const_cast<cDomainVectorOpenEnd*>( (cDomainVectorOpenEnd*)(&domain) );
		cDomainVectorOpenEnd *thisDomainVector = const_cast<cDomainVectorOpenEnd*>(this);
		
		if ( getNumberOfElements() != otherDomainVector->getNumberOfElements() ){
			return false;
		}
		
		for ( unsigned long actualElement = 1; 
				actualElement <= getNumberOfElements(); actualElement++ ){
			
			if ( ! ((*(thisDomainVector->getElementDomain( actualElement ))) ==
					(*(otherDomainVector->getElementDomain( actualElement )) ) ) ){
				return false;
			}
		}
		//all vector domain elements are equal
		return true;
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
unsignedIntFib cDomainVectorOpenEnd::getCompressedSize() const{
	
	unsignedLongFib ulCompressedSize = 8;//size of the domain name
	
	if ( getNumberOfElements() < 256 ){
		ulCompressedSize += 8;//size of the number of elements parameter
	}else{
		ulCompressedSize += 64;//size of the number of elements parameter
	}
	
	//add the size of the single element domains
	const unsigned long ulNumberOfElements = getNumberOfElements();
	for ( unsigned long actualElement = 1;
			actualElement <= ulNumberOfElements; actualElement++ ){
		
		ulCompressedSize += getElementDomain( actualElement )->getCompressedSize();
	}

	return ulCompressedSize;
}

/**
 * This method stores this domain in the XML -format into the
 * given stream.
 *
 * @param ostream the stream where domains should be stored to
 * @return true if this domain are stored, else false
 */
bool cDomainVectorOpenEnd::storeXml( ostream & ostream ) const{
	
	ostream<<"<vectorOpenEnd elements=\""<< getNumberOfElements() <<"\">"<<endl;
	
	//store the single elementdomains
	for ( unsigned long actualElement = 1;
			actualElement <= getNumberOfElements(); actualElement++ ){
		
		const bool bDomainStored = getElementDomain( actualElement )->storeXml( ostream );
		
		if ( ! bDomainStored ){
			return false;
		}
	}
	ostream<<"</vectorOpenEnd>"<<endl;
	
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
intFib cDomainVectorOpenEnd::restoreXml( const TiXmlElement * pXmlElement ){
	
	if ( pXmlElement == NULL ){
		//Error: nothing to load
		return -1;
	}
	string szElementType( pXmlElement->Value() );

	if ( szElementType != "vectorOpenEnd" ){
		return -2;
	}
	intFib iReturnValue = 0;
	
	//restore the attribute elements
	int iCountOfElements = 0;
	const char * szXmlCountOfElements = pXmlElement->Attribute(
		"elements", &iCountOfElements );
	if ( szXmlCountOfElements == NULL ){
		//Warning: attribute elements is missing
		iReturnValue = 2;
	}
	//restore subdomains
	const TiXmlElement * pXmlElementSubDomain = NULL;
	if ( pXmlElement->FirstChild() ){
		
		pXmlElementSubDomain = pXmlElement->FirstChildElement();
	}
	int iActualSubDomain = 0;
	for( iActualSubDomain = 0; pXmlElementSubDomain != NULL;
			pXmlElementSubDomain = pXmlElementSubDomain->NextSiblingElement() ){
		
		cDomain * pXmlElementDomain = cDomain::restoreXml(
			pXmlElementSubDomain, iReturnValue );
		
		if ( pXmlElementDomain != NULL ){
		
			vecElementDomains.push_back( pXmlElementDomain );
			iActualSubDomain++;
		}else{//Warning: one domain not restored
			if ( iReturnValue == 0 ){
				iReturnValue = 2;
			}
		}
	}
	if ( iActualSubDomain != iCountOfElements ){
		//Warning: number of subdomains incorrect
		if ( iReturnValue == 0 ){
			iReturnValue = 2;
		}
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
bool cDomainVectorOpenEnd::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	unsigned long long ulNumberOfDomains = getNumberOfElements();
	
	char cDomainName = 0xE0; //the name "vectorOpenEnd"
	if ( 256 <= ulNumberOfDomains ){
		//domain with 64 bit parameter
		cDomainName = 0xE4;
	}
	
	bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
		& cDomainName, 8 );
	if ( ! bNameStored ){
		return false;
	}
	//store the number of the domains
	
	bool bNumberOfDomainsStored = false;
	if ( ulNumberOfDomains < 256 ){
		//store 8 Bit parameter
		bNumberOfDomainsStored = nBitStream::store( stream, cRestBits,
			uiRestBitPosition, ulNumberOfDomains, 8 );
	}else{
		//store 64 Bit parameter
		bNumberOfDomainsStored = nBitStream::store( stream, cRestBits,
			uiRestBitPosition, ulNumberOfDomains, 64 );
	}
	if ( ! bNumberOfDomainsStored ){
		return false;
	}
	
	//store the single elementdomains
	for ( unsigned long ulActualElement = 1;
			ulActualElement <= getNumberOfElements(); ulActualElement++ ){
		
		const bool bDomainStored = getElementDomain( ulActualElement )->store(
			stream, cRestBits, uiRestBitPosition );
		
		if ( ! bDomainStored ){
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
intFib cDomainVectorOpenEnd::restore( cReadBits & iBitStream ){

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
	if ( ((cDomainName & 0xFC) != 0xE0) && ((cDomainName & 0xFC) != 0xE4) ){
		//warning: wrong type
		return -2;
	}
	unsignedLongFib ulNumberOfElements = 0;
	if ((cDomainName & 0xFC) == 0xE0 ){
		//vector with maximal 2^8 = 256 elements -> 8 Bit Sizeparameter
		uiBitsRead = iBitStream.readBits( ulNumberOfElements, 8 );
		if ( ! iBitStream.getStream()->good() ){
			return -2;
		}
		if ( uiBitsRead != 8 ){
			return -2;
		}
	}else{
		//vector with maximal 2^64 elements -> 8 Bit Sizeparameter
		uiBitsRead = iBitStream.readBits( ulNumberOfElements, 64 );
		if ( ! iBitStream.getStream()->good() ){
			return -2;
		}
		if ( uiBitsRead != 64 ){
			return -2;
		}
	}
	
	//restore the single elementdomains
	for ( unsigned long ulActualElement = 1;
			ulActualElement <= ulNumberOfElements; ulActualElement++ ){
		//restore the element domain
		intFib outStatus = 0;
		cDomain * pRestoredDomain = cDomain::restore( iBitStream, outStatus );
		if ( outStatus < 0 ){
			if ( pRestoredDomain ){
				delete pRestoredDomain;
			}
			return outStatus;
		}
		if ( pRestoredDomain == NULL ){
			//no domain to insert
			iReturnValue = 2;
			continue;
		}
		
		if ( (iReturnValue == 0) && (outStatus != 0) ){
			iReturnValue = outStatus;
		}
		vecElementDomains.push_back( (cDomainSingle*)pRestoredDomain );
	}
	return iReturnValue;
}


















