/**
 * @class cVectorArea
 * file name: cVectorArea.h
 * @author Betti Oesterholz
 * @date 13.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a basic Fib-vector.
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
 * This file contains the class of all Fib-subareavectors.
 * Thes subareavectors are used in Fib areaelements, for the subarea of
 * the point.
 * The lowerbound of the subarea is allways the first element of the
 * vector and the upperbound the second, even if the first value is
 * greater then the second.
 *
 */
/*
History:
13.02.2010  Oesterholz  created
25.08.2011  Oesterholz  underarea to subarea
02.01.2012  Oesterholz  changes for cTypeArea and cFibMatrix
16.03.2013  Oesterholz  clone() method added
*/

#ifndef ___C_VECTOR_AREA_H__
#define ___C_VECTOR_AREA_H__


#include "version.h"
#include "fibDatatyps.h"

#include "cFibVector.h"

using std::vector;


namespace fib{


class cVectorArea: public cFibVector{

public:


	/**
	 * The constructor of the subareavector.
	 *
	 * @param pInDefiningElement the Fib-element which
	 * 	defines/ uses the checksum -property -vector
	 */
	cVectorArea( cFibElement * pInDefiningElement = NULL );

	/**
	 * The copy constructor of the vector.
	 *
	 * @param vector the vector from which to copy the data
	 * @param pInDefiningElement the Fib-element which defines/ uses
	 * 	the new vector
	 */
	cVectorArea( const cVectorArea & vector,
		cFibElement * pInDefiningElement = NULL );

	/**
	 * parameterconstructor
	 *
	 * @param lLowerBound the lower bound value to set
	 * @param lUpperBound the upper bound value to set
	 * @param pInDefiningElement the Fib-element which defines/ uses
	 * 	the new vector
	 */
	cVectorArea( longFib lLowerBound, longFib lUpperBound,
		cFibElement * pInDefiningElement = NULL );
	
	/**
	 * parameterconstructor
	 *
	 * @param lLowerBound the lower bound value to set
	 * @param pVariableUpperBound the upper bound variable to set
	 * @param pInDefiningElement the Fib-element which defines/ uses
	 * 	the new vector
	 */
	cVectorArea( longFib lLowerBound, cFibVariable * pVariableUpperBound,
		cFibElement * pInDefiningElement = NULL );
	
	/**
	 * parameterconstructor
	 *
	 * @param pVariableLowerBound the lower bound variable to set
	 * @param lUpperBound the upper bound value to set
	 * @param pInDefiningElement the Fib-element which defines/ uses
	 * 	the new vector
	 */
	cVectorArea( cFibVariable * pVariableLowerBound, longFib lUpperBound,
		cFibElement * pInDefiningElement = NULL );
	
	/**
	 * parameterconstructor
	 *
	 * @param pVariableLowerBound the lower bound variable to set
	 * @param pVariableUpperBound the upper bound variable to set
	 * @param pInDefiningElement the Fib-element which defines/ uses
	 * 	the new vector
	 */
	cVectorArea( cFibVariable * pVariableLowerBound, cFibVariable * pVariableUpperBound,
		cFibElement * pInDefiningElement = NULL );


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
	cVectorArea( const TiXmlElement * pXmlElement, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables );

	/**
	 * This constructor restores a subareasvector from the stream where it is
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
	cVectorArea( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomain * pInVectorDomain, const cDomain * pInDomainVariable );



	/**
	 * This method clones this object.
	 *
	 * @return a pointer to the clone of this object
	 */
	virtual cVectorArea * clone() const;

//TODO change cFibElement to cPoint
	/**
	 * This method creates an instance of this vector type.
	 *
	 * @param iNumberOfElements number of elements in the vector (this will
	 * 	be ignored for the subareavector)
	 * @param definingAreaElement the Fib-areaelement which defines/ uses
	 * 	the subareasvector
	 */
	virtual cVectorArea * createInstance(
		unsignedIntFib iNumberOfElements=2,
		cFibElement *definingAreaElement=NULL ) const;

	/**
	 * Sets the Fib-element which defines/ uses this vector.
	 * If the given pointer is the nullpointer (standardvalue), no
	 * Fib-element defines this vector.
	 *
	 * @param pInDefiningElement a pointer to the Fib-element which
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
	virtual cTypeElement * getElementType() const;
	
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


//subarea methods
	/**
	 * @return the lower bound of the subarea
	 */
	longFib getLowerBound() const;
	
	/**
	 * @return the upper bound of the subarea
	 */
	longFib getUpperBound() const;
	
	/**
	 * @return all values which are in the subarea
	 */
	list<longFib> getAreaValues() const;
	
	/**
	 * This method sets the lower bound of the subarea to the given value.
	 *
	 * @param lValue the lower bound to set
	 * @return true if the lower bound is set to the given value lValue,
	 * 	else false
	 */
	bool setLowerBoundValue( longFib lValue );
	
	/**
	 * This method sets the upper bound of the subarea to the given value.
	 *
	 * @param lValue the upper bound to set
	 * @return true if the upper bound is set to the given value lValue,
	 * 	else false
	 */
	bool setUpperBoundValue( longFib lValue );
	
	/**
	 * This method sets the lower bound of the subarea to the given variable.
	 *
	 * @param pVariable the lower bound variable to set
	 * @return true if the lower bound is set to the given variable
	 * 	pVariable, else false
	 */
	bool setLowerBoundVariable( cFibVariable *pVariable );
	
	/**
	 * This method sets the upper bound of the subarea to the given variable.
	 *
	 * @param pVariable the upper bound variable to set
	 * @return true if the upper bound is set to the given variable
	 * 	pVariable, else false
	 */
	bool setUpperBoundVariable( cFibVariable *pVariable );

	/**
	 * This Method makes this vectorelements equal to the correspondending
	 * vectorelements of the given vector.
	 * The type of the vector and the number of elements won't be changed.
	 *
	 * @param vector the vector to copy
	 */
	virtual cVectorArea & operator=( const cFibVector &vector );

};//end class cVectorArea


}//end namespace fib

#endif
