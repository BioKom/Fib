/**
 * @class cTypeExtSubobject
 * file name: cTypeExtSubobject.h
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
*/

#ifndef ___C_TYPE_EXT_SUBOBJECT_H__
#define ___C_TYPE_EXT_SUBOBJECT_H__


#include "cTypeElement.h"


namespace fib{


class cTypeExtSubobject: public cTypeElement{

protected:
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	/**
	 * The number of the subobject for which the type is.
	 */
	unsignedIntFib uiNumberExtSubobject;
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	
public:

#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	/**
	 * Standardconstructor for the external subobjects type.
	 * 
	 * @param uiInNumberExtSubobject the number of the subobject for which
	 * 	the type is @see uiNumberExtSubobject
	 */
	cTypeExtSubobject( const unsignedIntFib uiInNumberExtSubobject );

#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTO
	
	/**
	 * Standardconstructor for the external subobjects type.
	 */
	cTypeExtSubobject();
	
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	/**
	 * Copy constructor for the external subobjects type.
	 * 
	 * @param typeExtSubobject the cTypeExtSubobject to copy
	 */
	cTypeExtSubobject( const cTypeExtSubobject & typeExtSubobject );

	
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
	virtual unsignedIntFib getType() const;


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
	 * This Method checks if the given type is equal to this type.
	 *
	 * @return true if the given type is equal to this type, else false
	 */
	virtual bool operator==( const cTypeElement &typeElement ) const;


	/**
	 * This Method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cTypeExtSubobject *clone() const;

	/**
	 * This method evaluades the size of the typeelement in bits in the
	 * compressed file form.
	 *
	 * @see store()
	 * @return the size of the typeelement in bits in the compressed form
	 */
	virtual unsignedLongFib getCompressedSize() const;

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
		const cDomain * domain = NULL ) const;

	/**
	 * This method restores a type with a domain in the XML -format from an
	 * TinyXml element.
	 *
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
		intFib & outStatus, const bool bRestoreDomain = true );

	/**
	 * This method stores this type element in the compressed Fib format
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
	virtual bool store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const;

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
	virtual intFib restore( cReadBits & iBitStream );

	/**
	 * @return true if domains of this type are inerted else false
	 */
	virtual bool isInherited() const;
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	/**
	 * @return the number of the subobject for which the type is
	 * @see uiNumberExtSubobject;
	 */
	unsignedIntFib getNumberOfExtSubobject() const;
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR


};//end class cTypeExtSubobject


}//end namespace Fib

#endif //___C_TYPE_EXT_SUBOBJECT_H__
