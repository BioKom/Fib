/**
 * @class cVectorProperty
 * file name: cVectorProperty.h
 * @author Betti Oesterholz
 * @date 05.07.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a property vector.
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
 * This class represents a property vector of the Fib -multimedialanguage.
 * It is a vector for properties.
 *
 */
/*
History:
21.06.2009  Oesterholz  created
05.07.2010  Oesterholz  lowerPropertyVector() moved her from cEvaluePositionList
	and operator<() added;
	distanceOfProperty() and distanceOfPropertyToNull() moved from
	cFibObjectFitnessBasicAlgorithm to hear and distanceToProperty() and 
	distanceOfPropertyToNull() added
17.12.2010  Oesterholz  isOverwritenVector() method added
18.12.2010  Oesterholz  isOverwriting() and isEvalued() methods added
16.03.2013  Oesterholz  clone() method added
*/

#ifndef ___C_VECTOR_PROPERTY_H__
#define ___C_VECTOR_PROPERTY_H__


#include "version.h"
#include "fibDatatyps.h"

#include "cDomainVectorBasis.h"
#include "cTypeProperty.h"

namespace fib{


class cVectorProperty: public cFibVector{

protected:
	unsignedIntFib uiPropertyType;

public:

//TODO ? change cFibElement to cProperty
	/**
	 * The constructor of the propertyvector.
	 *
	 * @param uiPropertyType a number for the type of the property,
	 * 	this should be a type with a correct standard domain
	 * @param pDefiningPropertyElement the Fib -propertyelement which
	 * 	defines/ uses the propertyvector
	 */
	cVectorProperty( unsignedIntFib uiPropertyType,
		cFibElement *pDefiningPropertyElement=NULL );

	/**
	 * The copy constructor of the vector.
	 *
	 * @param vector the vector from which to copy the data
	 * @param definingFibElement the Fib -element which defines/ uses
	 * 	the new vector
	 */
	cVectorProperty( const cVectorProperty & vector,
		cFibElement *pDefiningFibElement = NULL );

	/**
	 * The constructor of the propertyvector.
	 *
	 * @param uiPropertyType a number for the type of the property
	 * @param iNumberOfElements number of elements in the vector
	 * @param pDefiningPropertyElement the Fib -propertyelement which
	 * 	defines/ uses the propertyvector
	 */
	cVectorProperty( unsignedIntFib uiPropertyType,
		unsignedIntFib iNumberOfElements,
		cFibElement *pDefiningPropertyElement=NULL );
	
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
	cVectorProperty( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables );

	/**
	 * This constructor restores a propertyvector from the stream where it is
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
	 * @param uiInPropertyType a number for the type of the property
	 */
	cVectorProperty( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomain * pInVectorDomain, const cDomain * pInDomainVariable,
		unsignedIntFib uiInPropertyType );



	/**
	 * The constructor of the propertyvector.
	 *
	 * @param typeProperty the type this propertyvector should have
	 */
	cVectorProperty( const cTypeProperty & typeProperty );


	/**
	 * This method clones this object.
	 *
	 * @return a pointer to the clone of this object
	 */
	virtual cVectorProperty * clone() const;

//TODO change cFibElement to cProperty
	/**
	 * This method creates an instance of this vector type.
	 *
	 * @param iNumberOfElements number of elements in the vector
	 * @param definingPropertyElement the Fib -propertyelement which
	 * 	defines/ uses the propertyvector
	 */
	virtual cVectorProperty * createInstance(
		unsignedIntFib iNumberOfElements=2,
		cFibElement *definingPropertyElement=NULL ) const;

	/**
	 * Returns the type of the vector.
	 * You have to delete the returned object after usage.
	 *
	 * @return the type of the vector
	 */
	virtual cTypeElement * getElementType() const;

	/**
	 * This method returns a number for the type of the property.
	 * @see cTypeProperty
	 *
	 * @return a number for the type of the property
	 */
	virtual unsignedIntFib getPropertyType() const;
	
	/**
	 * This method checks if the given vector is overwritten by this vector.
	 *
	 * @param vectorToCheck the vector to check, if it is overwritten
	 * @return true if vectorToCheck is overwritten by this vector, else false
	 */
	bool isOverwritenVector( const cVectorProperty & vectorToCheck ) const;

	/**
	 * This function checks if the this property vector overwrites property vectors.
	 *
	 * @return if the given vector overwrites vector true, else false
	 */
	bool isOverwriting() const;
	
	/**
	* @return this method returnes true, if the property of this vector is
	 * 	for evaluating a fib -object, else false is returned
	 */
	bool isEvalued() const;

	/**
	 * @return the name for the type of the vector
	 */
	virtual string getVectorType() const;

	/**
	 * This Method makes this vectorelements equal to the correspondending
	 * vectorelements of the given vector.
	 * The type of the vector won't be changed.
	 * The type of the propertie will be adapted.
	 *
	 * @param vector the vector to copy
	 */
	virtual cVectorProperty & operator=( const cFibVector &vector );
	
	/**
	 * This function compares this propertyvector with the given propertyvector.
	 * Propertyvectors is lower if it's propertypvalues is lower than the
	 * propertyvectors of the other vector or its propertypvalues is equal, but
	 * if it has less elements than the other vector or it's i'th element is
	 * lower and all j'th elements with i > j are equal.
	 *
	 * @see cFibVector::lowerVector()
	 * @see lowerPropertyVector()
	 * @param vector the property to compare this with
	 * @return true if this propertyvectors is lower than the
	 * 	propertyvectors vector, else false
	 */
	bool operator<( const cVectorProperty & vector ) const;
	
	/**
	 * This function compares two propertyvectors.
	 * Propertyvectors is lower if it's propertypvalues is lower than the
	 * propertyvectors of the other vector or its propertypvalues is equal, but
	 * if it has less elements than the other vector or it's i'th element is
	 * lower and all j'th elements with i > j are equal.
	 *
	 * @see cFibVector::lowerVector()
	 * @param vector1 the first property to compare
	 * @param vector2 the second property to compare
	 * @return true if the propertyvectors vector1 is lower than that
	 * 	of vector2, else false
	 */
	static bool lowerPropertyVector( const cVectorProperty & vector1,
		const cVectorProperty & vector2 );
	
	/**
	 * This function evalues the distance of this property to the given
	 * property of the same type.
	 * This distance is the sum of the differnece of the property
	 * vectorelements
	 *
	 *	@param property the first propertyvector
	 * @return the sum of differneces betwean the vectorelements in this
	 * 	property and the given property
	 */
	doubleFib distanceToProperty( const cVectorProperty & property ) const;
	
	/**
	 * This function evalues the distance of two properties of the same type.
	 * This distance is the sum of the differnece of the property
	 * vectorelements
	 *
	 *	@param property1 the first propertyvector
	 *	@param property2 the second propertyvector
	 * @return the sum of differneces betwean the vectorelements in property1
	 * 	and property2
	 */
	static doubleFib distanceOfProperty( const cVectorProperty & property1,
		const cVectorProperty & property2 );
	
	/**
	 * This function evalues the distance of the this property to a
	 * property of the same type, wher all vectorelements are 0.
	 * This distance is the sum of the differnece of the property
	 * vectorelements
	 *
	 *	@param property the propertyvector
	 * @return the sum of differneces betwean the vectorelements in property
	 * 	and the nullvector of the same type with all vectorelements 0
	 */
	doubleFib distanceOfPropertyToNull() const;
	
	/**
	 * This function evalues the distance of the given property to a
	 * property of the same type, wher all vectorelements are 0.
	 * This distance is the sum of the differnece of the property
	 * vectorelements
	 *
	 *	@param property the propertyvector
	 * @return the sum of differneces betwean the vectorelements in property
	 * 	and the nullvector of the same type with all vectorelements 0
	 */
	static doubleFib distanceOfPropertyToNull( const cVectorProperty & property );


};//cVectorProperty
}//namespace fib

#endif //___C_VECTOR_PROPERTY_H__






