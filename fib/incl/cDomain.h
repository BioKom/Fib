/**
 * @class cDomain
 * file name: cDomain.h
 * @author Betti Oesterholz
 * @date 13.05.2009
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
13.05.2009  Oesterholz  created
09.02.2012  Oesterholz  isReference() added
*/

#ifndef ___C_DOMAIN_H__
#define ___C_DOMAIN_H__


#include "version.h"

#include "nBitStream.h"
#include "fibDatatyps.h"
#include "cReadBits.h"

#include "tinyxml.h"

#include <string>
#include <ostream>
#include <istream>


using std::string;

namespace fib{


class cDomain{

public:

	/**
	 * destructor
	 */
	virtual ~cDomain() = 0;
	
	/**
	 * @return the type of the domain as an string
	 */
	virtual string getType() const = 0;
	
	/**
	 * @return true if the object represents a scalar domain, else false
	 */
	virtual bool isScalar() const;

	/**
	 * @return true if the object represents a vector domain, else false
	 */
	virtual bool isVector() const;

	/**
	 * @return true if the object represents a reference domain, else false
	 * 	@see cDomainReference
	 */
	virtual bool isReference() const;

	/**
	 * This Method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cDomain *clone() const = 0;
	
	/**
	 * This Method checks if the given domain is equal to this domain.
	 *
	 * @param domain the domain which should be equal to this domain
	 * @return true if the given domain is equal to this domain, else false
	 */
	virtual bool equal( const cDomain &domain ) const;

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
	virtual unsignedIntFib getCompressedSize() const = 0;

	/**
	 * This method stores this domain in the XML -format into the
	 * given stream.
	 *
	 * @param ostream the stream where domains should be stored to
	 * @return true if this domain are stored, else false
	 */
	virtual bool storeXml( ostream & ostream ) const = 0;


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
	static cDomain * restoreXml( const TiXmlElement * pXmlElement,
		intFib & outStatus );

	/**
	 * This method restores a domain in the XML -format from an TinyXml element.
	 *
	 * @pattern Factory Method
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
	virtual intFib restoreXml( const TiXmlElement * pXmlElement ) = 0;

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
	virtual bool store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const = 0;


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
	static cDomain * restore( cReadBits & iBitStream, intFib & outStatus );

	/**
	 * This method restores a domain from a bitstream, wher it is
	 * stored in the compressed fib -format.
	 *
	 * @pattern Factory Method
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
	virtual intFib restore( cReadBits & iBitStream ) = 0;


};//end class cDomain


}//end namespace fib

#endif
