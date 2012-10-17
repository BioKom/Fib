/**
 * @class cDomainVector
 * file name: cDomainVector.h
 * @author Betti Oesterholz
 * @date 07.07.2009
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
 * This file contains the class for vector Fib -domains.
 * A vector domain is defined with the domains of it's elements.
 *
 */
/*
History:
13.05.2009  Oesterholz  created
01.12.2011  Oesterholz  method isInBoundaries() added;
	Elements can have any domain type -> cDomainSingle to cDomain
*/

#ifndef ___C_DOMAIN_VECTOR_H__
#define ___C_DOMAIN_VECTOR_H__


#include "version.h"
#include "fibDatatyps.h"

#include "cDomainVectorBasis.h"
#include "cDomainSingle.h"

#include <vector>

using std::vector;

namespace fib{


class cDomainVector: public cDomainVectorBasis{

protected:

	/**
	 * This vector contains the domains for the elements of the 
	 * vectordomain.
	 */
	vector<cDomain*> vecElementDomains;

public:

	/**
	 * This constructor of the cDomainVector element.
	 *
	 * @param vecInElementDomains the vector with the domains for the vector
	 * 	elements
	 */
	cDomainVector( const vector<cDomain*> & vecInElementDomains );

	/**
	 * This constructor of the cDomainVector element.
	 *
	 * @param vecInElementDomains the vector with the domains for the vector
	 * 	elements
	 */
	cDomainVector( const vector<cDomainSingle*> & vecInElementDomains );

	/**
	 * This destructor of the cDomainVector element.
	 */
	virtual ~cDomainVector( );

	/**
	 * @return the type of the domain as an string
	 */
	virtual string getType() const;


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
	virtual bool isElement( const cFibVector &fibVector ) const;

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
	virtual bool isInBoundaries( const cFibVector &fibVector ) const;

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
	virtual cFibVector * round( cFibVector &fibVector ) const;


	/**
	 * This method returns the number of elements in the vectors of the
	 * domain.
	 *
	 * @return the number of elements in the vectors of the domain
	 */
	virtual unsignedIntFib getNumberOfElements() const;


	/**
	 * This method returns the domain of the iNumberOfElement'th element in
	 * the vectors of the domain.
	 *
	 * @param iNumberOfElement the elementnumber for which the domain is to
	 * 	return
	 * @return domain of the iNumberOfElement'th element in the vectors of
	 * 	the domain
	 */
	virtual cDomain * getElementDomain(
		const unsignedIntFib iNumberOfElement );

	/**
	 * This method returns the domain of the iNumberOfElement'th element in
	 * the vectors of the domain.
	 *
	 * @param iNumberOfElement the elementnumber for which the domain is to
	 * 	return
	 * @return domain of the iNumberOfElement'th element in the vectors of
	 * 	the domain
	 */
	virtual const cDomain * getElementDomain(
		const unsignedIntFib iNumberOfElement ) const;

	/**
	 * This Method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cDomainVector *clone() const;


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
		unsigned char & uiRestBitPosition ) const;

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
	virtual intFib restore( cReadBits & iBitStream );


};//end class cDomainVector


}//end namespace fib

#endif

