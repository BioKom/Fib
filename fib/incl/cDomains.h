/**
 * @class cDomains
 * file name: cDomains.h
 * @author Betti Oesterholz
 * @date 09.06.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a list of domains.
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
 * This class represents a list of domains for an root -element.
 * The domain list consists of a number of domains with a type for which
 * they apply. No two domains can be for the same type.
 *
 */
/*
History:
09.06.2009  Oesterholz  created
12.02.2012  Oesterholz  methods for changed cDomainReference
11.03.2012  Oesterholz  getDirectDomainForElement() added
23.09.2012  Oesterholz  Warning removed: virtual destructor added
*/

#ifndef ___C_DOMAINS_H__
#define ___C_DOMAINS_H__

#include "version.h"

#include "fibDatatyps.h"
#include "cReadBits.h"

#include "cDomain.h"
#include "cTypeElement.h"
#include "cDomainElement.h"
#include "cDomainReference.h"
#include "cDomainIntegerBit.h"

#include <list>
#include <map>
#include <string>
#include <ostream>
#include <istream>



using std::list;
using std::string;

namespace fib{


class cDomains{
protected:

	/**
	 * the list with the domains for this domain list
	 */
	list<cDomainElement> domainElements;
	
	
//next part is needed for the cDomainReference
	/**
	 * The standard domain when no other domain is aviable.
	 * (not mutable: cDomainIntegerBit can't be changed ;) )
	 */
	mutable cDomainIntegerBit standardDomain;
	
	/**
	 * A map with the standard domains which wher created for returning
	 * a domain reference.
	 */
	mutable list<cDomainElement> standardDomains;
	
public:

	/**
	 * The constructor for the domain list.
	 */
	cDomains();

	/**
	 * The desstructor for the domain list.
	 */
	virtual ~cDomains();

	/**
	 * @return the number of domains in the domain list
	 */
	unsignedIntFib getNumberOfDomains() const;


	/**
	 * This method returns the domain on the given position iDomainNumber
	 * in the domain list.
	 * If the domain on the position is a reference domain @see cDomainReference
	 * the domain to which it is refered to will be returned.
	 *
	 * @param iDomainNumber the position on which the domain to
	 * 	return stands in the domain list (the counting begins with 1)
	 * @return a reference to the iDomainNumber'th domain (so you can adopt
	 * 	the domain) of this domain list or the Nullpointer NULL if non
	 * 	such exists;
	 */
	cDomain * getDomain( unsignedIntFib iDomainNumber ) const;


	/**
	 * This method returns the type on the given position iTypeNumber
	 * in the domain list.
	 *
	 * @param iTypeNumber the position on which the type to
	 * 	return stands in the domain list (the counting begins with 1)
	 * @return a reference to the iTypeNumber'th type of this domain list or
	 * 	the Nullpointer NULL if non such exists;
	 */
	cTypeElement * getType( unsignedIntFib iTypeNumber ) const;


	/**
	 * This method returns the domain for the given type from the
	 * domain list.
	 * If the domain for the type is a reference domain @see cDomainReference
	 * the domain to which it is refered to will be returned.
	 *
	 * @param type the type for which the domain is to return
	 * @return a reference to the domain (so you can adopt the domain) of
	 * 	this domain list for elements of the given type or the Nullpointer
	 * 	NULL if non such exists;
	 */
	cDomain * getDomainForElement( const cTypeElement &type ) const;


	/**
	 * This method returns the direct domain on the given position
	 * iDomainNumber in the domain list, without evaluating it.
	 * Since some domains (ie cDomainReference) are evalued by methods like
	 * getDomain(), this method will return the domain directly without
	 * evaluing it.
	 *
	 * @see getDomain()
	 * @see getDomainForElement()
	 * @param iDomainNumber the position on which the direct domain to
	 * 	return stands in the domain list (the counting begins with 1)
	 * @return a reference to the iDomainNumber'th direct domain (so you
	 * 	can adopt the domain) of this domain list or the Nullpointer
	 * 	NULL if non such exists;
	 */
	cDomain * getDirectDomain( const unsignedIntFib iDomainNumber ) const;

	/**
	 * This method returns the direct domain for the given type
	 * in the domain list, without evaluating it.
	 * Since some domains (ie cDomainReference) are evalued by methods like
	 * getDomainForElement(), this method will return the domain directly
	 * without evaluing it.
	 *
	 * @see getDomain()
	 * @see getDomainForElement()
	 * @param type the type for which the domain is to return
	 * @return a reference to the direct domain (so you can adopt the domain)
	 * 	of the gifen type of this domain list or the Nullpointer
	 * 	NULL if non such exists;
	 */
	cDomain * getDirectDomainForElement( const cTypeElement &type ) const;

	/**
	 * This method returns the domain to which the given reference domain
	 * refers to.
	 * If no domain to which it is refered can be found the standard domain
	 * for the pDomainReference type will be returned.
	 *
	 * @param pDomainReference reference domain for which the domain is to
	 * 	be returned
	 * @param pTypeElementForWhich a pointer to the type element for which the
	 * 	domain should be
	 * @return a pointer to the domain (so you can adopt the domain) for
	 * 	the reference domain or the Nullpointer NULL if non such exists
	 */
	cDomain * getDomainForReferenceDomain( cDomainReference * pDomainReference,
		cTypeElement * pTypeElementForWhich = NULL ) const;
	
	
	/**
	 * This method adds a given domain for the given type to the domain list.
	 * If an domain for the element allready exists, it is replaced.
	 *
	 * @param type the type for which the domain is to add
	 * @param domain the domain for the given type
	 * @return the number of the position on which the new domain stands in
	 * 	the domain list or 0 if the domain wasn't inserted
	 */
	unsignedIntFib addDomain( const cTypeElement &type, const cDomain &domain );
	
	/**
	 * This method adds a given domain for the given type to the domain list.
	 * If an domain for the element allready exists, it is replaced.
	 * This add method dosn't copy the domain, befor adding it.
	 *
	 * @param type the type for which the domain is to add
	 * @param domain a pointer to the domain for the given type
	 * @return the number of the position on which the new domain stands in
	 * 	the domain list or 0 if the domain wasn't inserted
	 */
	unsignedIntFib addDomain( const cTypeElement &type, cDomain * domain );


	/**
	 * This method sets the domain for the given type to the standarddomain
	 * of the type. If no entry for the type exists, an entry is added.
	 *
	 * @param type the type for which the domain is to set to the
	 * 	standarddomain
	 * @return the number of the position on which the type stands in
	 * 	the domain list
	 */
	unsignedIntFib setStandardDomain( const cTypeElement &type );


	/**
	 * This method deletes the domain on the given position iDomainNumber
	 * in the domain list.
	 *
	 * @param iDomainNumber the position on which the domain to
	 * 	delete stands in the domain list (the counting begins with 1)
	 * @return true if the domain on the position is deleted, else false
	 */
	bool deleteDomain( unsignedIntFib iDomainNumber );


	/**
	 * This method deletes the domain for the given type from the
	 * domain list.
	 *
	 * @param type the type for which the domain is to delete
	 * @return true if the domain for the given type is deleted, else false
	 */
	bool deleteDomain( const cTypeElement &type );


	/**
	 * This Method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cDomains *clone() const;


	/**
	 * This method evaluades the size of the domains in bits in the
	 * compressed file form.
	 *
	 * @see store()
	 * @return the size of the domains in bits in the compressed form
	 */
	virtual unsignedLongFib getCompressedSize() const;
	
	/**
	 * This method stores this domains in the XML -format into the
	 * given stream.
	 *
	 * @param ostream the stream where domains should be stored to
	 * @param szName the name the writen XML -element should have
	 * @return true if this domains are stored, else false
	 */
	virtual bool storeXml( ostream & ostream, string szName=string("domains") ) const;

	/**
	 * This method restores this optionalpart in the XML -format from an
	 * an TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node wher the domains are stored in
	 * @return an integervalue with the errorvalue
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 */
	virtual intFib restoreXml( const TiXmlElement * pXmlElement );

	/**
	 * This method stores this domains in the compressed Fib -format
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
	 * @return true if the domains are stored, else false
	 */
	virtual bool store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const;

	/**
	 * This method restores the domains from a bitstream, wher it is
	 * stored in the compressed fib -format.
	 *
	 * @see store
	 * @see cFibElement::store
	 * @param iBitStream the stream where this domains is stored in,
	 * 	because this stream is an cReadBits, any number of bits can be
	 * 	readed from it
	 * @return the errorvalue
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid stream
	 * 		- -2 loading error, invalid data in stream
	 * 		- 1 loading warning, invalid data in stream, error could be corrected
	 * 		- 2 loading warning, invalid data in stream, maybe the loaded
	 * 			object is wrong
	 */
	virtual intFib restore( cReadBits & iBitStream );

	/**
	 * This Method checks if the given domains is equal to this domains.
	 *
	 * @param domains the domains to compare with this
	 * @return true if the given domains is equal to this
	 * 	domains, else false
	 */
	virtual bool equal( const cDomains &domains ) const;

	/**
	 * This method checks if the given domains is equal to this domains.
	 *
	 * @param domains the domains to compare with this
	 * @return true if the given domains is equal to this
	 * 	domains, else false
	 */
	virtual bool operator==( const cDomains &domains ) const;

	/**
	 * This operator makes this domains equal to the given domains.
	 *
	 * @param domains the domains to which this should be equal
	 * @return a refernce to this domain
	 */
	virtual cDomains & operator=( const cDomains &domains );
	
	
};//end class cDomains


}//end namespace fib

#endif //___C_DOMAINS_H__
