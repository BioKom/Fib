/**
 * @class cTypeElement
 * file name: cTypeElement.h
 * @author Betti Oesterholz
 * @date 02.06.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents an abstract Fib -vectorelementtype.
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
 * This file contains the basisclass of all Fib -vectorelementtyps.
 * Fib -vectorelementtyps are typs of the elements in an Fib -vector (e.g.
 * for an underarea vector the type of the elements is underarea).
 *
 */
/*
History:
02.06.2009  Oesterholz  created
31.01.2012  Oesterholz  isInherited() method added
12.02.2012  Oesterholz  restoreXml*() without restoring domain possible
*/

#ifndef ___C_TYPE_ELEMENT_H__
#define ___C_TYPE_ELEMENT_H__


#include "version.h"
#include "fibDatatyps.h"
#include "cReadBits.h"

#include "cDomain.h"

#include "tinyxml.h"

#include <ostream>
#include <istream>


namespace fib{


class cTypeElement{

public:

	/**
	 * destructor
	 */
	virtual ~cTypeElement() = 0;
	
	/**
	 * This Function returns for the type of the element an number.
	 * The values, which are returned, mean:
	 * 	- 1:  cTypeDimension
	 * 	- 2:  cTypeUnderArea
	 * 	- 3:  cTypeUnderFunction
	 * 	- 5:  cTypeInVar
	 * 	- 6:  cTypeProperty
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
	virtual unsignedIntFib getType() const = 0;


	/**
	 * This method checks, if this element type is compatible with the
	 * given domain. Just domains which are compadible can be used for the
	 * elements of this type.
	 *
	 * @param domain the domain, which should be compatible
	 * @return true if the given domain is compatible, else false
	 */
	virtual bool isCompatible( const cDomain &domain ) const;


	/**
	 * This Method returns a pointer to a new instance of the standart
	 * domain for elements of this type.
	 * You have to delete the returned object after usage.
	 *
	 * @return the standart domain for elements of this type
	 */
	virtual cDomain *getStandardDomain( ) const;


	/**
	 * This Method checks if the elementtype of the given type is equal to
	 * the elementtype of this type.
	 * Two elementtype are not equal if ther are for different fib -elements.
	 *
	 * @param typeElement the typeelement to compare with this typeelement
	 * @return true if the elementtype of the given type is equal to the
	 * 	elementtype of this type, else false
	 */
	virtual bool equalElementType( const cTypeElement & typeElement ) const;

	/**
	 * This Method checks if the given type is equal to this type.
	 *
	 * @param typeElement the typeelement to compare with this typeelement
	 * @return true if the given type is equal to this type, else false
	 */
	virtual bool equal( const cTypeElement &typeElement ) const;

	/**
	 * This Method checks if the given type is equal to this type.
	 *
	 * @param typeElement the typeelement to compare with this typeelement
	 * @return true if the given type is equal to this type, else false
	 */
	virtual bool operator==( const cTypeElement &typeElement ) const;


	/**
	 * This Method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cTypeElement *clone() const = 0;

	/**
	 * This method evaluades the size of the typeelement in bits in the
	 * compressed file form.
	 *
	 * @see store()
	 * @return the size of the typeelement in bits in the compressed form
	 */
	virtual unsignedLongFib getCompressedSize() const = 0;

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
	virtual bool storeXml( ostream & ostream,
		const cDomain * domain = NULL ) const = 0;

	/**
	 * This method restores a type in the XML -format from a TinyXml element.
	 *
	 * @pattern Factory Method
	 * @param pXmlNode a pointer to the TinyXml node wher the type is stored in
	 * @param outStatus an integer value with the errorvalue
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 * @return the pointer to the restored type, if it could be restored
	 * 	else it is a NULL pointer
	 */
	static cTypeElement * restoreXmlType(
		const TiXmlElement * pXmlElement, intFib & outStatus );

	/**
	 * This method restores a type with a domain in the XML -format from an
	 * TinyXml element.
	 *
	 * @pattern Factory Method
	 * @param pXmlNode a pointer to the TinyXml node wher the type is stored in
	 * @param outStatus an integer value with the errorvalue
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 * @param bRestoreDomain if true a domain is to be asumed in the type
	 * 	element and it will be restored, else no domain will be restores
	 * @return a pair with the pointers to the restored type and domain
	 * 	if one couldn't be restored it's pointer is NULL
	 */
	static pair< cTypeElement * , cDomain * > restoreXmlTypeWithDomain(
		const TiXmlElement * pXmlElement, intFib & outStatus,
		const bool bRestoreDomain = true );

	/**
	 * This method restores a type with a domain in the XML -format from an
	 * TinyXml element.
	 *
	 * @pattern Factory Method
	 * @param pXmlNode a pointer to the TinyXml node wher the type is stored in
	 * @param outStatus an integer value with the errorvalue
	 * 	possible errorvalues are:
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
	virtual cDomain * restoreXmlWithDomain( const TiXmlElement * pXmlElement,
		intFib & outStatus, const bool bRestoreDomain = true ) = 0;

	/**
	 * This method stores this typeelement in the compressed fib -format
	 * into the given stream.
	 * It is needed because the stream can yust store byts but the size of
	 * fib -elements can be any number of bits. Because of that ther have to
	 * be a possibility to exchange the missing bits betwean the fib -elements.
	 *
	 * @see restore
	 * @see cFibElement::store
	 * @param stream the stream where this typeelement should be stored to
	 * @param cRestBits the not yet writen bits which should be stored
	 * @param uiRestBitPosition the number of bits in the cRestBits which
	 * 	should be writen respectively containing valid information
	 * @return true if the typeelement is stored, else false
	 */
	virtual bool store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const = 0;

	/**
	 * This method restores a type from a bitstream, wher it is
	 * stored in the compressed fib -format.
	 *
	 * @see store
	 * @param iBitStream the stream where the type is stored in,
	 * 	because the stream is an cReadBits, any number of bits can be
	 * 	readed from it
	 * @param outStatus an integer value with the errorvalue
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 * @return a pointer to the restored type or NULL
	 */
	static cTypeElement * restore( cReadBits & iBitStream, intFib & outStatus );

	/**
	 * This method restores a type from a bitstream, wher it is
	 * stored in the compressed fib -format.
	 *
	 * @see store
	 * @param iBitStream the stream where the type is stored in,
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
	virtual intFib restore( cReadBits & iBitStream ) = 0;
	
	/**
	 * @return true if domains of this type are inerted else false
	 */
	virtual bool isInherited() const;

protected:
	
	/**
	 * @return true if the given domain is a domain for counters (it only
	 * 	contains positiv numbers), else false
	 */
	static bool isCounterDomain( const cDomain * pDomain );

};//end class cTypeElement


}//end namespace fib

#endif //___C_TYPE_ELEMENT_H__
