/**
 * @class cDomainReference
 * file name: cDomainReference.h
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
*/

#ifndef ___C_DOMAIN_REFERENCE_H__
#define ___C_DOMAIN_REFERENCE_H__


#include "version.h"

#include "cDomain.h"

#include "cTypeElement.h"


namespace fib{


class cDomainReference: public cDomain{
protected:
	
	/**
	 * The type of the element to which domain this domain refer to.
	 */
	cTypeElement * pOriginalType;

	/**
	 * The subdomain of the domain of the element to which it is refered.
	 * The element with index i is a subdomain of the domain with index i-1 .
	 */
	vector<unsignedIntFib> vecElementDomains;
	
public:

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
	cDomainReference( const cTypeElement & inOriginalType,
		const vector<unsignedIntFib> vecInElementDomains=vector<unsignedIntFib>() );
	
	/**
	 * The copy constructor for the reference domain.
	 *
	 * @param domain the  reference domain to copy
	 */
	cDomainReference( const cDomainReference &domain );

	/**
	 * destructor
	 */
	~cDomainReference();

	/**
	 * @return true if the object represents a reference domain, else false
	 * 	@see cDomainReference
	 */
	virtual bool isReference() const;

	/**
	 * @return the type of the domain as a string
	 */
	virtual string getType() const;
	

	/**
	 * This Method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cDomainReference * clone() const;
	
	/**
	 * This Method checks if the given domain is equal to this domain.
	 *
	 * @param domain the domain which should be equal to this domain
	 * @return true if the given domain is equal to this domain, else false
	 */
	virtual bool operator==( const cDomain &domain ) const;


	/**
	 * This method evaluades the size of the domain in bits in the
	 * compressed file form.
	 *
	 * @see store()
	 * @return the size of the domain in bits in the compressed form
	 */
	virtual unsignedIntFib getCompressedSize() const;

	/**
	 * This method stores this domain in the XML -format into the
	 * given stream.
	 *
	 * @param ostream the stream where domains should be stored to
	 * @return true if this domain are stored, else false
	 */
	virtual bool storeXml( ostream & ostream ) const;
	
	/**
	 * This method restores a domain in the XML -format from an TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node wher the domain is stored in
	 * @return an integer value with the errorvalue
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 */
	virtual intFib restoreXml( const TiXmlElement * pXmlElement ) ;

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
	virtual bool store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const;
	
	/**
	 * This method restores a domain from a bitstream, wher it is
	 * stored in the compressed Fib format.
	 *
	 * @see store
	 * @param iBitStream the stream where the domain is stored in,
	 * 	because the stream is an cReadBits, any number of bits can be
	 * 	readed from it
	 * @return an integer value with the errorvalue
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 */
	virtual intFib restore( cReadBits & iBitStream );

	
	/**
	 * This method returns a pointer to the type of the element to which
	 * domain this domain refer to.
	 *
	 * @see pOriginalType
	 * @return a pointer to the type of the element to which
	 * 	domain this domain refer to
	 */
	const cTypeElement * getTypeElement() const;
	
	/**
	 * @see vecElementDomains
	 * @return The subdomain of the domain of the element to which it is
	 * 	refered to. The element with index i is a subdomain of the domain
	 * 	with index i-1 .
	 */
	const vector<unsignedIntFib> & getElement() const;
	
	
};//end class cDomainReference


}//end namespace fib

#endif
