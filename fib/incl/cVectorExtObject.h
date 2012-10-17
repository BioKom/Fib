/**
 * @class cVectorExtObject
 * file name: cVectorExtObject.h
 * @author Betti Oesterholz
 * @date 22.01.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a external object element vector.
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
 * This class represents a external object element vector of the
 * Fib multimedia language.
 * It is a vector for external object element input variables.
 *
 */
/*
History:
22.01.2012  Oesterholz  created
*/

#ifndef ___C_VECTOR_EXT_OBJECT_H__
#define ___C_VECTOR_EXT_OBJECT_H__


#include "cFibVector.h"

namespace fib{

class cExtObject;//cyclic dependencie

class cVectorExtObject: public cFibVector{

public:


	/**
	 * The constructor of the external object element vector.
	 *
	 * @param iNumberOfElements the number of elements the vector should have
	 * @param pDefiningElement the Fib element which
	 * 	defines/ uses the external object element vector
	 */
	cVectorExtObject( unsignedIntFib iNumberOfElements,
		cFibElement * pDefiningExtObject=NULL );

	/**
	 * The constructor of the external object element vector.
	 *
	 * @param definingExtObject the Fib external object element which
	 * 	defines/ uses the external object element vector
	 */
	cVectorExtObject( cExtObject & definingExtObject );

	/**
	 * The copy constructor of the vector.
	 *
	 * @param vector the vector from which to copy the data
	 * @param pDefiningFibElement the Fib element which defines/ uses
	 * 	the new vector
	 */
	cVectorExtObject( const cVectorExtObject & vector,
		cFibElement * pDefiningFibElement = NULL );

	/**
	 * The constructor for restoring a vector from an TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node the vector is stored in
	 * @param outStatus An reference to an integervalue where the errorvalue
	 * 	can be stored to.
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 * @param liDefinedVariables a list with the defined variables for the
	 * 	to restore vector, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 */
	cVectorExtObject( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables );

	
	/**
	 * This constructor restores a external object element vector from the stream where
	 * it is stored in the compressed Fib format.
	 *
	 * @param iBitStream the stream where this vector is stored to in,
	 * 	because this stream is an cReadBits, any number of bits can be
	 * 	readed from it
	 * @param outStatus An reference to an integervalue where the errorvalue
	 * 	can be stored to. If the pointer is NULL no errorvalue will be
	 * 	given back.
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid stream
	 * 		- -2 loading error, invalid data in stream
	 * 		- 1 loading warning, invalid data in stream, error could be corrected
	 * 		- 2 loading warning, invalid data in stream, maybe the loaded
	 * 			object is wrong
	 * @param liDefinedVariables a list with the defined variables for the
	 * 	to restore vector, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 * @param pInVectorDomain the domain for this vector
	 * @param pInDomainVariable the domain for variables
	 * @param uiInNumberOfElements the number of elements to restore,
	 * 	if not given or 0, it will be evalued by the number of elements of
	 * 	the given domain pInVectorDomain
	 */
	cVectorExtObject( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomain * pInVectorDomain, const cDomain * pInDomainVariable,
		const unsignedIntFib uiInNumberOfElements );


	/**
	 * This method creates an instance of this vector type.
	 *
	 * @param iNumberOfVectorElements number of elements in the vector
	 * @param pDefiningElement the Fib external object element which
	 * 	defines/ uses the external object element vector
	 */
	virtual cVectorExtObject * createInstance(
		unsignedIntFib iNumberOfVectorElements,
		cFibElement * pDefiningElement = NULL ) const;
	
	/**
	 * Returns the type of the vector.
	 * You have to delete the returned object after usage.
	 *
	 * @return the type of the vector
	 */
	virtual cTypeElement * getElementType( ) const;

	/**
	 * Returns a reference to the domain of the vector or
	 * the nullpointer NULL if no domain is defined for the vector.
	 * If the nullpointer NULL is returned the standarddomain is valid for the
	 * vector.
	 *
	 * @return a reference to the vectordomain of the vector
	 */
	virtual cDomainVectorBasis * getDomain() const;

	/**
	 * Returns a reference to the standard domain of the vector.
	 * You have to delete the returned object after usage.
	 *
	 * @return a reference to the standard domain of the vector
	 */
	virtual cDomainVectorBasis * getStandardDomain() const;

	/**
	 * Returns a reference to the value domain of the vector or
	 * the nullpointer NULL if no value domain is defined for the vector.
	 * If the nullpointer NULL is returned the standarddomain is valid for the
	 * vector.
	 *
	 * @return a reference to the definitionarea of the vector
	 */
	virtual cDomainVectorBasis * getValueDomain() const;


	/**
	 * @return the name for the type of the vector
	 */
	virtual string getVectorType() const;

	/**
	 * Sets the Fib-element which defines/ uses this vector.
	 * If the given pointer is the nullpointer (standardvalue), no
	 * Fib-element defines this vector.
	 *
	 * @param pFibElement a pointer to the Fib-element which
	 * 	defines/ uses this vector
	 * @param bCheckDomains getthe domains of the defining element and
	 * 	check the vectorelements with it
	 */
	virtual void setDefiningFibElement( cFibElement * pFibElement=NULL,
		bool bCheckDomains=true );

	/**
	 * This method changes the number of Elements of this vector to the given
	 * number.
	 *
	 * @param uiNumberOfVectorElements the number of elements this vector
	 * 	should have
	 */
	virtual void resize( unsigned int uiNumberOfVectorElements );
	
};//cVectorExtObject
}//namespace fib

#endif //___C_VECTOR_EXT_OBJECT_H__






