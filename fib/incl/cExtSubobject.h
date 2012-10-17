/**
 * @class cExtSubobject
 * file name: cExtSubobject.h
 * @author Betti Oesterholz
 * @date 06.11.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the external subobject element.
 * Copyright (C) @c LGPL3 2011 Betti Oesterholz
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
 * This class represents the external subobject element.
 * External subobject elements are for calling subobjects that are given a
 * external object element (@see cExtObject).
 *
 */
/*
History:
06.11.2011  Oesterholz  created
29.01.2011  Oesterholz  FEATURE_EXT_SUBOBJECT_INPUT_VECTOR implemented:
	the input values are now a vector of values
*/

#ifndef ___C_EXT_SUBOBJECT_H__
#define ___C_EXT_SUBOBJECT_H__


#include "version.h"

#include "fibDatatyps.h"

#include "cFibLeaf.h"
#include "cRoot.h"
#include "cFibVariable.h"


#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	#include "cVectorExtSubobject.h"
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR


namespace fib{


#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

class cExtSubobject: public cFibLeaf{

#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

class cExtSubobject: public cFibLeaf, public iVariableUser{

#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

friend class cFibElement;

private:

	/**
	 * The number of the subobject to call.
	 * @see cRoot
	 * @see cExtObject
	 */
	unsignedIntFib uiNumberOfSubobject;
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	/**
	 * The vector with the output variables for the subobject to call.
	 */
	cVectorExtSubobject vecOutputValues;
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	/**
	 * The vector with the output variables for the subobject to call.
	 */
	vector< cFibVariable * > vecOutputValues;
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

public:
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	/**
	 * parameterconstructor
	 *
	 * @param uiInNumberOfSubobject the number of the subobject to call
	 * @param vecInOutputValues the vector with the output values 
	 * 	of the subobject to call
	 * @param pInSuperiorElement the Fib element in which this
	 * 	external object element is an subobject
	 */
	cExtSubobject( unsignedIntFib uiInNumberOfSubobject,
		cVectorExtSubobject vecInOutputValues,
		cFibElement * pInSuperiorElement = NULL );
	
	/**
	 * parameterconstructor
	 *
	 * @param uiInNumberOfSubobject the number of the subobject to call
	 * @param uiNumberOfOutputVariables the number of output variables 
	 * 	of the subobject to call
	 * @param pInSuperiorElement the Fib element in which this
	 * 	external object element is an subobject
	 */
	cExtSubobject( unsignedIntFib uiInNumberOfSubobject,
		unsignedIntFib uiNumberOfOutputVariables=0,
		cFibElement * pInSuperiorElement = NULL );

#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	/**
	 * parameterconstructor
	 *
	 * @param uiInNumberOfSubobject the number of the subobject to call
	 * @param vecInOutputVariables the vector with the output variables 
	 * 	or the subobject to call
	 * @param pInSuperiorElement the Fib element in which this
	 * 	external object element is an subobject
	 */
	cExtSubobject( unsignedIntFib uiInNumberOfSubobject,
		vector< cFibVariable* > vecInOutputVariables=vector< cFibVariable* >(),
		cFibElement * pInSuperiorElement = NULL );
	
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	/**
	 * copyconstructor
	 * This copyconstructor constructs a copy of the given external object element.
	 * It dosn't copy other Fib elements than the given.
	 *
	 * @param extObjectElement the external object element to copy
	 */
	cExtSubobject( const cExtSubobject & extObjectElement );

protected:

	/**
	 * The constructor for restoring a pointelement from an TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node the Fib object is stored in
	 * @param outStatus An reference to an integervalue where the errorvalue
	 * 	can be stored to.
	 * 	possible error values are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 * @param liDefinedVariables a list with the defined variables for the
	 * 	to restore Fib element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 */
	cExtSubobject( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables );

	/**
	 * This constructor restores a pointelement from the stream where it is
	 * stored in the compressed Fib format.
	 * This method is for internal use only.
	 *
	 * @param iBitStream the stream where this pointelement is stored in,
	 * 	because this stream is an cReadBits, any number of bits can be
	 * 	readed from it
	 * @param outStatus An reference to an integervalue, where the errorvalue
	 * 	can be stored to. If the pointer is NULL no errorvalue will be
	 * 	given back.
	 * 	possible error values are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid stream
	 * 		- -2 loading error, invalid data in stream
	 * 		- 1 loading warning, invalid data in stream, error could be corrected
	 * 		- 2 loading warning, invalid data in stream, maybe the loaded
	 * 			object is wrong
	 * @param liDefinedVariables a list with the defined variables for the
	 * 	to restore Fib element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 * @param validDomains the domains valid for restoring the Fib elements
	 * @param pNextRoot the next higher root-element for the to restore
	 * 	Fib elements, or the last restored root-element
	 */
	cExtSubobject( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains,
		cRoot * pNextRoot );

public:

	/**
	 * destructor
	 */
	virtual ~cExtSubobject();

	/**
	 * This method checks, if this Fib element is an valid Fib element.
	 *
	 * @return true if this Fib element is an valid Fib element, else false
	 */
	virtual bool isValidFibElement() const;

	/**
	 * @see getTypeName
	 * @return a character for the typ of the Fib element
	 * Types are:
	 *		- u: element of unknown typ
	 *		- p: point
	 * 	- l: list-element
	 *		- y: property
	 *		- c: comment
	 *		- a: area
	 *		- f: function
	 *		- i: if-condition
	 *		- o: extern object element
	 *		- s: extern subobject element
	 *		- v: set-element
	 *		- m: matrix element
	 *		- r: root-element
	 */
	virtual char getType() const;

	/**
	 * This method evaluades the Fib object.
	 *
	 * @param evaluePosition a reference to the object with the
	 * 	evaluePosition() method to evalue /store the positions and ther
	 * 	properties; everytime a point (to evalue) is reached in the
	 * 	evaluation, this method is called with the position and the
	 * 	properties of the point; @see iEvaluePosition
	 * @param objectPoint the object point in the order of true partobjects
	 *		to evalue
	 * @param liVecProperties a list with the property vectors which should
	 * 	be global for the evalued object
	 * @return if the evalueation was successfull true, else false
	 */
	virtual bool evalueObject( iEvaluePosition & evaluePosition,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties ) const;

	/**
	 * This method evaluades the Fib object.
	 * Evertime a Fib elements, with a type of the given type chars in
	 * liCFibElementTyps, is reached while evaluation, it is given
	 * back with the properties which it has.
	 * Ever point element is given back. The type chars for point elements
	 * don't need to be in the list liCFibElementTyps.
	 *
	 * @param evalueFibElement a reference to the object with the
	 * 	evalueElement() method to evalue /store the Fib elements and ther
	 * 	properties; everytime a Fib element (with one of the type given
	 * 	in liCFibElementTyps) is reached in the evaluation, the method
	 * 	evalueElement() of this objects is called with the Fib element
	 * 	and the properties of the Fib element; @see iEvalueFibElement
	 * @param objectPoint the object point in the order of true partobjects
	 *		to evalue
	 * @param liVecProperties a list with the property vectors which should
	 * 	be global for the evalued object
	 * @param liCFibElementTyps a list with the type chars (@see getType)
	 * 	of the Fib elements to return
	 * @return if the evalueation was successfull true, else false
	 */
	virtual bool evalueObject( iEvalueFibElement & evalueFibElement,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties,
		const list<char> & liCFibElementTyps );

	/**
	 * This method evaluades a value for the time needed to evalue the
	 * object.
	 * This value should not exceed lMaxTime, if the value for the time
	 * is greater than lMaxTime the evaluation will be stopt and lMaxTime
	 * returned. If lMaxTime is 0 (for infinity) the evaluation won't be
	 * stoped, this is the standard case.
	 *
	 * @see evalueObject()
	 * @param lMaxTime the maximum time for the evaluation, the returned
	 * 	exceed this value; the value 0 stands for infinity, so the 
	 * 	evaluation won't be stoped
	 * @return a value for the time needed to evalue the object
	 */
	virtual unsignedLongFib getTimeNeed( unsignedLongFib lMaxTime=0 ) const;

	/**
	 * This method evaluades the size of the Fib object in bits in the
	 * compressed file form.
	 *
	 * @see store()
	 * @return the size of the Fib object in bits in the compressed form
	 */
	virtual unsignedLongFib getCompressedSize() const;

	/**
	 * This method checks if the given variable is used in the given
	 * direction from this Fib element.
	 *
	 * @see cFibVariable
	 * @see isDefinedVariable()
	 * @param pVariable the variable to check if it is used
	 * @param direction the direction from this Fib element, in which the
	 * 	variable should be used; standardvalue is ED_POSITION so yust
	 * 	this Fib element will be checked
	 * @return true if the variable is used, else false
	 */
	virtual bool isUsedVariable( const cFibVariable * pVariable ,
		edDirection direction=ED_POSITION ) const;

	/**
	 * This method returns all variables used in the given direction from
	 * this Fib element.
	 *
	 * @see cFibVariable
	 * @see isUsedVariable()
	 * @see isDefinedVariable()
	 * @param direction the direction from this Fib element, in which the
	 * 	variable should be used; standardvalue is ED_POSITION so yust
	 * 	this Fib element will be checked
	 * @return the set with all variables used in the given direction from
	 * 	this Fib element
	 */
	virtual set<cFibVariable*> getUsedVariables( edDirection direction=ED_POSITION );

	/**
	 * This method replace the variable variableOld with the variable
	 * variableNew in the object.
	 *
	 * @see cFibVariable
	 * @see isUsedVariable()
	 * @see isDefinedVariable()
	 * @param pVariableOld the variable to replace
	 * @param pVariableNew the variable with which the variable variableOld
	 * 	is to replace
	 * @return true if the variable variableOld is replaced with variableNew,
	 * 	else false
	 */
	virtual bool replaceVariable( cFibVariable * pVariableOld,
		cFibVariable * pVariableNew );

	/**
	 * This method copies the Fib element on the specified position.
	 * Variables which are not defined in the Fib element but used
	 * don't change ther reference.
	 *
	 * @see getType()
	 * @param cType the type of the Fib element to copy
	 * @param elementPoint the number of the Fib element, in the order of
	 * 	Fib elements of the given type cType, to copy
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	Fib object
	 * @return the copy of the Fib element
	 */
	virtual cFibElement * copyElement( const char cType='u', const unsignedIntFib
		elementPoint=0, bool bAbsolute=false ) const;

	/**
	 * This method stores this Fib object in the XML -format into the
	 * given stream.
	 *
	 * @param stream the stream where this Fib object should be stored to
	 * @return true if this Fib object is stored, else false
	 */
	virtual bool storeXml( ostream &stream ) const;



/*
 * external subobject element methods
 */
	
	/**
	 * @return the number of the subobject to call @see uiNumberOfSubobject
	 */
	unsignedIntFib getNumberSubobject() const;
	
	/**
	 * This method sets the number of the subobject to call
	 * (@see uiNumberOfSubobject).
	 *
	 * @param iInSubobjectNumber the number of the subobject to set
	 * @return if the subobject number was set true, else false
	 */
	bool setNumberSubobject( const unsignedIntFib iInSubobjectNumber );
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	/**
	 * @return the vector with the output values of this external subobject
	 * 	element
	 * @see vecOutputValues
	 */
	cVectorExtSubobject * getOutputVector();
	
	/**
	 * @return the vector with the output values of this external subobject
	 * 	element
	 * @see vecOutputValues
	 */
	const cVectorExtSubobject * getOutputVector() const;
	
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	/**
	 * @return the number of output variables of this object respectively
	 * 	the input variables for the external subobject to call
	 * 	@see vecOutputValues
	 */
	unsignedIntFib getNumberOfOutputVariables() const;
	
	/**
	 * @return the vector with the output variables of this object
	 * 	respectively the input variables for the external subobject to
	 * 	call @see vecOutputValues
	 */
	vector< cFibVariable * > getOutputVariables();
	
	/**
	 * This method sets the vector with the output variables of this object
	 * respectively the input variables for the external subobject to
	 * call (@see vecOutputValues).
	 *
	 * @param vecOutputValues the vector with the output variables of
	 * 	this object respectively the input variables for the external
	 * 	subobject to call (@see vecOutputValues)
	 * @return if the vector with the output variables was set true, else false
	 */
	bool setOutputVariables( vector< cFibVariable * > vecOutputValues );
	
	/**
	 * This method returns the uiVariableNumber'th output variable of the
	 * vector with the output variables of this object respectively the
	 * input variables for the external subobject to call
	 * @see vecOutputValues or NULL if non exists.
	 *
	 * @param uiVariableNumber the number of the output variable to set
	 * @return the uiVariableNumber'th output variable of the vector with
	 * 	the output variables of this object respectively the input
	 * 	variables for the external subobject to call
	 * 	@see vecOutputValues or NULL if non exists
	 */
	cFibVariable * getOutputVariable( const unsignedIntFib uiVariableNumber );
	
	/**
	 * This method sets the uiVariableNumber'th output variable of the
	 * vector with the output variables of this object respectively the
	 * input variables for the external subobject to call
	 * @see vecOutputValues. 
	 * It will create a new variable if ther are one less than
	 * uiVariableNumber output variables.
	 *
	 * @param uiVariableNumber the number of the output variable to set
	 * @param pOutputVariable the uiVariableNumber'th output variable of
	 * 	the vector with the output variables @see vecOutputValues to set
	 * @return true if the uiVariableNumber'th output variables was set
	 * 	else false
	 */
	bool setOutputVariable( const unsignedIntFib uiVariableNumber,
		cFibVariable * pOutputVariable );

#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR


protected:

	/**
	 * This method stores this Fib object in the compressed Fib format
	 * into the given stream.
	 * It is needed because the stream can yust store byts but the size of
	 * Fib elements can be any number of bits. Because of that ther have to
	 * be a possibility to exchange the missing bits betwean the Fib elements.
	 *
	 * @see store
	 * @param stream the stream where this Fib object should be stored to
	 * @param cRestBits the not yet writen bits which should be stored
	 * @param uiRestBitPosition the number of bits in the cRestBits which
	 * 	should be writen respectively containing valid information
	 * @return true if this Fib object is stored, else false
	 */
	virtual bool storeBit( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const;

	/**
	 * This method copies the connected object with the given number in the
	 * order of connected objects.
	 * For this every Fib element, beginning from this Fib element, that
	 * is part of the connected object, will be copied.
	 * Variables which are not defined in the connected object but used
	 * don't change ther reference.
	 * It is an help method for the copy method. It dosn't update the
	 * structural information of the created Fib object.
	 *
	 * @see copy()
	 * @param iObjectPoint the number of the connected object to copy;
	 * 	the standart value is 0 for coping the complet actual object
	 * @return the copy of the connected object or NULL if non such exists
	 */
	virtual cFibElement *copyInternal( const unsignedIntFib iObjectPoint=0 ) const;

	/**
	 * This method checks if the given Fib object is equal to this Fib
	 * object.
	 * Variables can be others, but must be defined and used in equivalent
	 * Fib elements.
	 *
	 * @param fibObject the Fib object to which this Fib object should be
	 * 	equal
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
	 * 	@see cExtObject will be compared
	 * @return true if this Fib object is equal to the given Fib object,
	 * 	else false
	 */
	virtual bool equalInternal( const cFibElement & fibObject,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const;

	/**
	 * This method checks if the given Fib element is equal to this fib
	 * -element.
	 * The subobjects arn't compared, not even ther count is compared.
	 * Used variables can be others.
	 *
	 * @param fibElement the Fib element to which this Fib element should be
	 * 	equal
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
	 * @return true if this Fib element is equal to the given Fib object,
	 * 	else false
	 */
	virtual bool equalElementInternal( const cFibElement & fibElement,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const;

#ifndef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	/**
	 * @return the Fib element which uses the variables of this element
	 */
	virtual cFibElement * getVariableUsingFibElement() const;
	
	/**
	 * This method deletes all occurencies of the given variable from this
	 * element. So the variable is not used anymore by this element.
	 * Beware: This element has to be unregistered (call
	 * unregisterUsingElement() ) at the pVariable seperatly. Do this directly
	 * befor or after calling this method.
	 *
	 * @param pVariable the variable which is to delete from this element
	 * @return true if the variable dosn't occure anymore in this element,
	 * 	else false
	 */
	virtual bool deleteVariable( cFibVariable * pVariable );
	
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

};
}//namespace fib

#endif //___C_EXT_SUBOBJECT_H__






