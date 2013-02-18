/**
 * @class cFibVector
 * file name: cFibVector.h
 * @author Betti Oesterholz
 * @date 02.05.2009
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
 * This file contains the basisclass of all Fib-vectors.  It's not
 * possible to create instances from this class.
 * Thes vectors are used in Fib-elements. A vector contains a fixed
 * number of elements. Every element is an value or an Fib-Variable.
 *
 */
/*
History:
17.04.2009  Oesterholz  created
05.07.2010  Oesterholz  lowerVector() moved her from cEvaluePositionList
	and operator<() added
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
03.12.2011  Oesterholz  changes for cDomainVectorOpenEnd (store + restore
	of more elements than in the domain)
11.12.2011  Oesterholz  getCompressedSize() and store() method with
	parameters for domains added
02.01.2011  Oesterholz  cFibMatrix added
17.02.2013  Oesterholz FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE implemented
*/

#ifndef ___C_FIB_VECTOR_H__
#define ___C_FIB_VECTOR_H__


#include "version.h"
#include "fibDatatyps.h"
#include "cReadBits.h"

#include "cFibVariable.h"
#include "cTypeElement.h"
#include "cDomainSingle.h"

#include "tinyxml.h"

#include <vector>
#include <list>
#include <map>
#include <sstream>
#include <ostream>
#include <istream>


using std::vector;

namespace fib{


class cFibElement;//cyclic dependencie
class cDomainVectorBasis;//cyclic dependencie


class cFibVector: public iVariableUser{

friend class cDomainVector;
friend class cDomainVectorOpenEnd;
friend class cArea;
friend class cProperty;
friend class cPoint;
friend class cExtObject;
friend class cExtSubobject;
friend class cFibSet;
friend class cFibMatrix;

protected:

	/**
	 * the type fore the type of the vectorelements
	 */
	enum eVectorType{
		VALUE,
		VARIABLE
	};
	
	/**
	 * the vector with the type of the vectorelements
	 */
	vector<eVectorType> liVectorType;

	/**
	 * the vector with the values of the vectorelements
	 */
	vector<doubleFib> liVectorValues;

	/**
	 * the vector with the variables of the vectorelements
	 */
	vector<cFibVariable*> liVectorVariable;
	
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	/**
	 * The number of elements in the vector.
	 * @see liVectorType
	 * @see liVectorValues
	 * @see liVectorVariable
	 */
	unsignedIntFib uiNumberOfElements;
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	
	/**
	 * the Fib-element which defines/ uses the vector
	 */
	cFibElement *pDefiningFibElement;


protected:


	/**
	 * The constructor of the vector.
	 *
	 * @param iNumberOfVectorElements number of elements in the vector
	 * @param definingFibElement the Fib-element which defines/ uses
	 * 	the new vector
	 */
	cFibVector( unsignedIntFib iNumberOfVectorElements = 1,
		cFibElement * definingFibElement = NULL );

	/**
	 * The copy constructor of the vector.
	 *
	 * @param vector the vector from which to copy the data
	 * @param definingFibElement the Fib-element which defines/ uses
	 * 	the new vector
	 */
	cFibVector( const cFibVector & vector,
		cFibElement *definingFibElement = NULL );

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
	cFibVector( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables );

	/**
	 * This constructor restores a poisitionsvector from the stream where it is
	 * stored in the compressed Fib-format.
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
	cFibVector( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomain * pInVectorDomain, const cDomain * pInDomainVariable,
		const unsignedIntFib uiInNumberOfElements = 0 );

	/**
	 * This method creates an instance of this vector type.
	 *
	 * @param iNumberOfVectorElements number of elements in the vector
	 * @param definingFibElement the Fib-element which defines/ uses
	 * 	the vector
	 */
	virtual cFibVector * createInstance(
		unsignedIntFib iNumberOfVectorElements=1,
		cFibElement *definingFibElement=NULL ) const = 0;

public:

	/**
	 * The destructor of the vector.
	 */
	virtual ~cFibVector();

	/**
	 * Returns the number of elements the vector contains.
	 *
	 * @return the number of elements the vector contains
	 */
	unsignedIntFib getNumberOfElements() const;


	/**
	 * Returns if the iNumberElement'te vectorelement is an variable.
	 *
	 * @param iNumberElement the number of the element, for which is to
	 * 	check if it is an variable
	 * @return true if the iNumberElement'te vectorelement is an variable,
	 * 	else false
	 */
	virtual bool isVariable( unsignedIntFib iNumberElement ) const;

	/**
	 * This method checks if the given variable is used in this vector.
	 *
	 * @see cFibVariable
	 * @param variable the variable to check if it is used
	 * @return true if the variable is used, else false
	 */
	virtual bool isUsedVariable( const cFibVariable *variable ) const;
	
	/**
	 * This method returns all variables used in this vector.
	 *
	 * @see cFibVariable
	 * @return all variables used in this vector
	 */
	virtual set<cFibVariable*> getUsedVariables();

	/**
	 * This method replace the variable variableOld with the variable
	 * variableNew in the vector.
	 *
	 * @see cFibVariable
	 * @see isVariable()
	 * @see isUsedVariable()
	 * @param variableOld the variable to replace
	 * @param variableNew the variable with which the variable variableOld
	 * 	is to replace
	 * @return true if the variable variableOld is replaced with variableNew,
	 * 	else false
	 */
	virtual bool replaceVariable( cFibVariable *variableOld,
		cFibVariable *variableNew );

	/**
	 * Returns the value of the iNumberElement'te vectorelement or
	 * Nullvalue if non such exists.
	 *
	 * @param iNumberElement the number of the element, which value is to
	 * 	return
	 * @return the value of the iNumberElement'te vectorelement or 0 if non
	 * 	such exists
	 */
	virtual doubleFib getValue( unsignedIntFib iNumberElement ) const;


	/**
	 * Sets the value of the iNumberElement'te vectorelement.
	 *
	 * @param iNumberElement the number of the element, which value is to
	 * 	set
	 * @param dValue the value to set
	 * @return true if the iNumberElement'te vectorelement is set to the
	 * 	given value dValue, else false
	 */
	virtual bool setValue( unsignedIntFib iNumberElement, doubleFib dValue );


	/**
	 * Returns the variable of the iNumberElement'te vectorelement or the
	 * Nullpointer NULL, if the iNumberElement'te vectorelement isn't an
	 * variable.
	 *
	 * @param iNumberElement the number of the element, which variable is
	 * 	to return
	 * @return the variable of the iNumberElement'te vectorelement or the
	 * 	Nullpointer NULL, if the iNumberElement'te vectorelement isn't an
	 * 	variable.
	 */
	virtual cFibVariable * getVariable( unsignedIntFib iNumberElement );


	/**
	 * Sets the variable of the iNumberElement'te vectorelement.
	 *
	 * @param iNumberElement the number of the element, where the variable is
	 * 	to set
	 * @param pVariable the variable to set
	 * @return true if the iNumberElement'te vectorelement is set to the
	 * 	given variable pVariable, else false
	 */
	virtual bool setVariable( unsignedIntFib iNumberElement, cFibVariable *pVariable );


	/**
	 * Returns the type of the vector.
	 * You have to delete the returned object after usage.
	 *
	 * @return the type of the vector
	 */
	virtual cTypeElement * getElementType() const = 0;


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
	 * Returns a reference to the value domain of the vector or
	 * the nullpointer NULL if no value domain is defined for the vector.
	 * If the nullpointer NULL is returned the standarddomain is valid for the
	 * vector.
	 *
	 * @return a reference to the definitionarea of the vector
	 */
	virtual cDomainVectorBasis * getValueDomain() const;


	/**
	 * Returns a reference to the domain the iNumberElement'te
	 * vectorelement or the nullpointer NULL if non exists.
	 *
	 * @param iNumberElement the number of the element, which
	 * 	definitionarea is to return
	 * @return a reference to the definitionarea of the iNumberElement'te
	 * 	vectorelement
	 */
	virtual cDomain * getDomain( unsignedIntFib iNumberElement ) const;

	/**
	 * Returns a reference to the standard domain of the vector.
	 * You have to delete the returned object after usage.
	 *
	 * @return a reference to the standard domain of the vector
	 */
	virtual cDomainVectorBasis * getStandardDomain() const;

	/**
	 * Returns a reference to the domain for variables of the vector.
	 * You have to delete the returned object after usage.
	 *
	 * @return a reference to the domain for variables of the vector
	 */
	virtual cDomainSingle * getVariableDomain() const;

	/**
	 * @return the Fib-element which defines/ uses this vector or
	 * 	a Nullpointer NULL if non such Fib-element exists
	 */
	cFibElement * getDefiningFibElement( ) const;


	/**
	 * Sets the Fib-element which defines/ uses this vector.
	 * If the given pointer is the nullpointer (standardvalue), no
	 * Fib-element defines this vector.
	 *
	 * @param definingFibElement a pointer to the Fib-element which
	 * 	defines/ uses this vector
	 * @param bCheckDomains getthe domains of the defining element and
	 * 	check the vectorelements with it
	 */
	virtual void setDefiningFibElement( cFibElement *fibElement=NULL,
		bool bCheckDomains=true );

	/**
	 * This method evaluades the size of the Fib-object in bits in the
	 * compressed file form.
	 *
	 * @see store()
	 * @return the size of the Fib-object in bits in the compressed form
	 */
	virtual unsignedLongFib getCompressedSize() const;
	
	/**
	 * This method evaluades the size of the Fib-object in bits in the
	 * compressed file form.
	 *
	 * @see store()
	 * @param valueVectorDomain the domain for this vector
	 * @param variableDomain the domain for variables
	 * @return the size of the Fib-object in bits in the compressed form
	 */
	virtual unsignedLongFib getCompressedSize(
		const cDomainVectorBasis & valueVectorDomain,
		const cDomainSingle & variableDomain ) const;

	/**
	 * This method stores this Fib-object in the compressed Fib-format
	 * into the given stream.
	 * It is needed becouse the stream can yust store byts but the size of
	 * Fib-elements can be any number of bits. Because of that ther have to
	 * be a possibility to exchange the missing bits betwean the Fib-elements.
	 *
	 * @see store
	 * @param stream the stream where this Fib-object should be stored to
	 * @param cRestBits the not yet writen bits which should be stored
	 * @param uiRestBitPosition the number of bits in the cRestBits which
	 * 	should be writen respectively containing valid information
	 * @return true if this Fib-object is stored, else false
	 */
	virtual bool store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const;

	/**
	 * This method stores this Fib-object in the compressed Fib-format
	 * into the given stream.
	 * It is needed becouse the stream can yust store byts but the size of
	 * Fib-elements can be any number of bits. Because of that ther have to
	 * be a possibility to exchange the missing bits betwean the Fib-elements.
	 *
	 * @see store
	 * @param stream the stream where this Fib-object should be stored to
	 * @param cRestBits the not yet writen bits which should be stored
	 * @param uiRestBitPosition the number of bits in the cRestBits which
	 * 	should be writen respectively containing valid information
	 * @param valueVectorDomain the domain for this vector
	 * @param variableDomain the domain for variables
	 * @return true if this Fib-object is stored, else false
	 */
	virtual bool store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition,
		const cDomainVectorBasis & valueVectorDomain,
		const cDomainSingle & variableDomain ) const;

	/**
	 * This method stores this vector in the XML -format into the
	 * given stream.
	 * Variables should have ther number as ther value.
	 *
	 * @param stream the stream where this vectorshould be
	 * 	stored to
	 * @return true if this vector is stored, else false
	 */
	virtual bool storeXml( ostream &stream ) const;

	/**
	 * @return the name for the type of the vector
	 */
	virtual string getVectorType() const = 0;

#ifdef FEATURE_EQUAL_FIB_OBJECT
	
	/**
	 * This Method checks if the given vector is equal to this vector.
	 *
	 * @param vector the vector to compare with this vector
	 * @param bCheckExternalObjects if true the external objects of
	 * 	cExtObject will be compared
	 * @return true if the given vector is equal to this vector, else false
	 */
	virtual bool equal( const cFibVector &vector,
		const bool bCheckExternalObjects=true ) const;

#else //FEATURE_EQUAL_FIB_OBJECT
	
	/**
	 * This Method checks if the given vector is equal to this vector.
	 *
	 * @param vector the vector to compare with this vector
	 * @return true if the given vector is equal to this vector, else false
	 */
	virtual bool equal( const cFibVector &vector ) const;

#endif //FEATURE_EQUAL_FIB_OBJECT

	/**
	 * This Method checks if the given vector is equal to this vector.
	 *
	 * @param vector the vector to compare with this vector
	 * @return true if the given vector is equal to this vector, else false
	 */
	virtual bool operator==( const cFibVector &vector ) const;

	/**
	 * This Method checks if the given vector is not equal to this vector.
	 *
	 * @param vector the vector to compare with this vector
	 * @return true if the given vector is not equal to this vector, else false
	 */
	bool operator!=( const cFibVector &vector ) const;

	/**
	 * This Method makes this vectorelements equal to the correspondending
	 * vectorelements of the given vector.
	 * The type of the vector won't be changed.
	 *
	 * @param vector the vector to copy
	 */
	virtual cFibVector & operator=( const cFibVector &vector );

	/**
	 * This function compares on lower this vector with the given Fib-vector.
	 * A vector is lower, if it has less elements than the other vector or
	 * it's i'th element is lower and all j'th elements with i > j are equal.
	 *
	 * @see lowerVector()
	 * @param vector the vector to compare
	 * @return true if this vector is lower than that of vector, else false
	 */
	virtual bool operator<( const cFibVector & vector ) const;
	
	/**
	 * This function compares two Fib-vectors.
	 * A vector is lower, if it has less elements than the other vector or
	 * it's i'th element is lower and all j'th elements with i > j are equal.
	 *
	 * @param vector1 the first vector to compare
	 * @param vector2 the second vector to compare
	 * @return true if the vector1 is lower than that of vector2, else false
	 */
	static bool lowerVector( const cFibVector & vector1, const cFibVector & vector2 );


protected:

	/**
	 * @return the Fib-element which uses the variables of this element
	 */
	virtual cFibElement * getVariableUsingFibElement() const;
	
	/**
	 * This method deletes all occurenc of the given variable from this
	 * element. So the variable is not used anymore of this element.
	 * Beware: This element has to be unregisterd (call
	 * unregisterUsingElement() ) at the pVariable seperatly. Do this directly
	 * befor or after calling this method.
	 *
	 * @param pVariable the variable which is to delete from this element
	 * @return true if the variable dosn't occure anymore in this element,
	 * 	else false
	 */
	virtual bool deleteVariable( cFibVariable * pVariable );

#ifdef FEATURE_EQUAL_FIB_OBJECT
	
	/**
	 * This Method checks if the given variable is equal to this variable.
	 *
	 * @param vector the vector to compare with this vector
	 * @param mapEqualRootObjects the root objects of this object that wher
	 * 	already checked as equal
	 * 	map entries:
	 * 		key: the root-element of this Fib object that was checked
	 * 		value: the to the key correspondending root-element of the
	 * 			fibObject that was checked and which is equal to the key
	 * 		root-element
	 * 	(it is empty if bCheckExternalObjects == false)
	 * @param mapEqualDefinedVariables the Fib elements that defines
	 * 	variables and are equal;
	 * 	map entries:
	 * 		key: the Fib element of this Fib object that was checked
	 * 		value: the to the key correspondending Fib element of the
	 * 			fibObject that was checked and which sets its defined
	 * 			variables to the same values as the key Fib element
	 * @param bCheckExternalObjects if true the external objects of
	 * 	cExtObject will be compared
	 * @return true if the given variable is equal to this variable, else false
	 */
	virtual bool equalInternal( const cFibVector &vector,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const;

#endif //FEATURE_EQUAL_FIB_OBJECT

};//end class cFibVector


}//end namespace fib

#endif
