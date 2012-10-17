/**
 * @class cVectorPosition
 * file name: cVectorPosition.h
 * @author Betti Oesterholz
 * @date 11.05.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a positions -fib -vector.
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
 * This file contains the class of all Fib -positionvectors.
 * Thes positionvectors are used in Fib pointelements, for the position of
 * the point.
 *
 */
/*
History:
11.05.2009  Oesterholz  created
*/

#ifndef ___C_VECTOR_POSITION_H__
#define ___C_VECTOR_POSITION_H__


#include "version.h"
#include "fibDatatyps.h"

#include "cFibVector.h"

using std::vector;


namespace fib{


class cVectorPosition: public cFibVector{

public:

//TODO change cFibElement to cPoint
	/**
	 * The constructor of the positionvector.
	 *
	 * @param definingPointElement the Fib -pointelement which defines/ uses
	 * 	the positionsvector
	 */
	cVectorPosition( cFibElement & definingPointElement );

	/**
	 * The constructor of the positionvector.
	 *
	 * @param iNumberOfDimensions number of elements in the vector or the dimensions
	 * @param pDefiningPointElement the Fib -pointelement which defines/ uses
	 * 	the positionsvector
	 */
	cVectorPosition( unsignedIntFib iNumberOfDimensions = 2,
		cFibElement * pDefiningPointElement = NULL );

	/**
	 * The copy constructor of the vector.
	 *
	 * @param vector the vector from which to copy the data
	 * @param definingFibElement the Fib -element which defines/ uses
	 * 	the new vector
	 */
	cVectorPosition( const cVectorPosition & vector,
		cFibElement * definingFibElement = NULL );

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
	cVectorPosition( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables );

	/**
	 * This constructor restores a positionsvector from the stream where it is
	 * stored in the compressed fib -format.
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
	 */
	cVectorPosition( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomain * pInVectorDomain, const cDomain * pInDomainVariable );


//TODO change cFibElement to cPoint
	/**
	 * This method creates an instance of this vector type.
	 *
	 * @param iNumberOfDimensions number of elements in the vector
	 * @param definingPointElement the Fib -pointelement which defines/ uses
	 * 	the positionsvector
	 */
	virtual cVectorPosition * createInstance(
		unsignedIntFib iNumberOfDimensions=2,
		cFibElement *definingPointElement=NULL ) const;

	/**
	 * Sets the Fib -element which defines/ uses this vector.
	 * If the given pointer is the nullpointer (standardvalue), no
	 * Fib -element defines this vector.
	 *
	 * @param definingFibElement a pointer to the Fib -element which
	 * 	defines/ uses this vector
	 * @param bCheckDomains getthe domains of the defining element and
	 * 	check the vectorelements with it
	 */
	virtual void setDefiningFibElement( cFibElement *fibElement=NULL,
		bool bCheckDomains=true );

	/**
	 * Returns the type of the vector.
	 * You have to delete the returned object after usage.
	 *
	 * @return the type of the vector
	 */
	virtual cTypeElement * getElementType( ) const;

	/**
	 * @return the name for the type of the vector
	 */
	virtual string getVectorType() const;


};//end class cVectorPosition


}//end namespace fib

#endif
