/**
 * @class cExtObject
 * file name: cExtObject.h
 * @author Betti Oesterholz
 * @date 27.07.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the external object element.
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
 * This class represents the external objects element of the Fib-multimedialanguage.
 * It is for calling an external object.
 *
 */
/*
History:
27.07.2011  Oesterholz  created
23.01.2012  Oesterholz  input values changed to input vector
30.07.2013  Oesterholz  method assignValues() added
*/

#ifndef ___C_EXT_OBJECT_H__
#define ___C_EXT_OBJECT_H__


//#define FEATURE_C_EXT_OBJECT_USE_LIST


#include "version.h"

#include "fibDatatyps.h"

#include "cFibElement.h"
#include "cFibBranch.h"
#include "cRoot.h"
#include "cVectorExtObject.h"

#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	#include <list>
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	#include <vector>
#endif //FEATURE_C_EXT_OBJECT_USE_LIST



namespace fib{


class cExtObject: public cFibBranch{

friend class cFibElement;
friend class cFibBranch;
friend class cRoot;

private:

	/**
	 * The identifier of the external Fib-object this external element
	 * stands for.
	 */
	longFib lIdentifier;
	
	/**
	 * The vector with the input values of the external object element.
	 */
	cVectorExtObject vecInputValues;
	
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	/**
	 * The list with the subobjects the external Fib-object can use.
	 * The list element pair elements are:
	 * 	first: a pointer to the subobject to use
	 * 	second: a list with the pointers to the output variables this
	 * 		extern object element defines for the subobject
	 */
	list< pair< cFibElement * , list< cFibVariable * > > > vecSubobjects;
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	
	/**
	 * The list with the subobjects the external Fib-object can use.
	 * The list element pair elements are:
	 * 	first: a pointer to the subobject to use
	 * 	second: a list with the pointers to the output variables this
	 * 		extern object element defines for the subobject
	 */
	vector< pair< cFibElement * , vector< cFibVariable * > > > vecSubobjects;
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
	
	
public:

	/**
	 * parameterconstructor
	 *
	 * @param lInIdentifier The identifier of the external Fib-object this
	 * 	external element stands for. @see lIdentifier
	 * @param vecInInputValues the vector with the input values of this
	 * 	external element @see vecInputValues
	 * @param pInSuperiorElement the Fib-element in which this
	 * 	Fib-element is an subobject
	 */
	cExtObject( const longFib lInIdentifier,
		const cVectorExtObject & vecInInputValues,
		cFibElement * pInSuperiorElement = NULL );
	
	/**
	 * parameterconstructor
	 *
	 * @param lInIdentifier The identifier of the external Fib-object this
	 * 	external element stands for. @see lIdentifier
	 * @param uiNumberOfInputValues the number of input values of this
	 * 	external element @see vecInputValues
	 * @param pInSuperiorElement the Fib-element in which this
	 * 	Fib-element is an subobject
	 */
	cExtObject( const longFib lInIdentifier,
		const unsignedIntFib uiNumberOfInputValues=0,
		cFibElement * pInSuperiorElement = NULL );
	
	/**
	 * copyconstructor
	 * This copyconstructor constructs a copy of the given external object element.
	 * It dosn't copy other Fib-elements than the given, even if ther are
	 * in the external object element.
	 *
	 * @param extObjElement the external object element to copy
	 */
	cExtObject( const cExtObject & extObjElement );


protected:

	/**
	 * The constructor for restoring a external object element from an TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node the Fib-object is stored in
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
	 * 	to restore Fib-element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 */
	cExtObject( const TiXmlElement * pXmlElement, intFib & outStatus,
		list< cFibVariable* > & liDefinedVariables );

	/**
	 * This method restores a external object objects from the stream where it is
	 * stored in the compressed Fib-format.
	 * This method is for internal use only.
	 *
	 * @param iBitStream the stream where this external object objects is stored to in,
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
	 * 	to restore fib-element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 * @param validDomains the domains valid for restoring the fib-elements
	 * @param pNextRoot the next higher root-element for the to restore
	 * 	fib-elements, or the last restored root-element
	 */
	cExtObject( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains,
		cRoot * pNextRoot );

public:

	/**
	 * destructor
	 */
	virtual ~cExtObject();


	/**
	 * @see getTypeName
	 * @return a character for the typ of the Fib-element
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
	 * This method checks, if this Fib-element is an valid Fib-element.
	 *
	 * @return true if this Fib-element is an valid Fib-element, else false
	 */
	virtual bool isValidFibElement() const;

	/**
	 * This method evaluades the Fib-object.
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
	 * This method evaluades the Fib-object.
	 * Evertime a Fib-elements, with a type of the given type chars in
	 * liCFibElementTyps, is reached while evaluation, it is given
	 * back with the properties which it has.
	 * Ever pointelement is given back. The type chars for pointelements
	 * don't need to be in the list liCFibElementTyps.
	 *
	 * @param evalueFibElement a reference to the object with the
	 * 	evalueelement() method to evalue /store the Fib-elements and ther
	 * 	properties; everytime a Fib-element (with one of the type given
	 * 	in liCFibElementTyps) is reached in the evaluation, the method
	 * 	evalueelement() of this objects is called with the Fib-element
	 * 	and the properties of the Fib-element; @see iEvalueFibElement
	 * @param objectPoint the object point in the order of true partobjects
	 *		to evalue
	 * @param liVecProperties a list with the property vectors which should
	 * 	be global for the evalued object
	 * @param liCFibElementTyps a list with the type chars (@see getType() )
	 * 	of the Fib-elements to return
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
	 * This method evaluades the size of the Fib-object in bits in the
	 * compressed file form.
	 * The optionalpart field of external object elements will not be ignored.
	 *
	 * @see storeBit()
	 * @return the size of the Fib-object in bits in the compressed form
	 */
	virtual unsignedLongFib getCompressedSize() const;

	/**
	 * This method replace the variable pVariableOld with the variable
	 * pVariableNew in the object.
	 *
	 * @see cFibVariable
	 * @see isUsedVariable()
	 * @see isDefinedVariable()
	 * @param pVariableOld the variable to replace
	 * @param pVariableNew the variable with which the variable variableOld
	 * 	is to be replace
	 * @return true if the variable pVariableOld is replaced with pVariableNew,
	 * 	else false
	 */
	virtual bool replaceVariable( cFibVariable * pVariableOld,
		cFibVariable * pVariableNew );
	
#ifndef SWITCH_JUST_STORE_AND_EVALUE
	
	/**
	 * This method checks if the given variable is used in the given
	 * direction from this fib-element.
	 *
	 * @see cFibVariable
	 * @see isDefinedVariable()
	 * @param variable the variable to check if it is used
	 * @param direction the direction from this fib-element, in which the
	 * 	variable should be used; standardvalue is ED_POSITION so yust
	 * 	this fib-element will be checked
	 * @return true if the variable is used, else false
	 */
	virtual bool isUsedVariable( const cFibVariable *variable ,
		edDirection direction=ED_POSITION ) const;

	/**
	 * This method returns all variables used in the given direction from
	 * this fib-element.
	 *
	 * @see cFibVariable
	 * @see isUsedVariable()
	 * @see isDefinedVariable()
	 * @param direction the direction from this fib-element, in which the
	 * 	variable should be used; standardvalue is ED_POSITION so yust
	 * 	this fib-element will be checked
	 * @return the set with all variables used in the given direction from
	 * 	this fib-element
	 */
	virtual set<cFibVariable*> getUsedVariables( edDirection direction=ED_POSITION );

	
	/**
	 * @return true if this Fib-element is movebel else false
	 */
	virtual bool isMovable() const;

#endif //SWITCH_JUST_STORE_AND_EVALUE

	/**
	 * This method copies the Fib-element on the specified position.
	 * Variables which are not defined in the Fib-element but used
	 * don't change ther reference.
	 *
	 * @see getType()
	 * @param cType the type of the Fib-element to copy
	 * @param elementPoint the number of the Fib-element, in the order of
	 * 	Fib-elements of the given type cType, to copy
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	Fib-object
	 * @return the copy of the Fib-element
	 */
	virtual cFibElement * copyElement( const char cType='u', const unsignedIntFib
		elementPoint=0, bool bAbsolute=false ) const;

#ifndef SWITCH_JUST_STORE_AND_EVALUE
		
	/**
	 * This method asigns / copies the values from the given Fib element
	 * fibElement to this Fib element. This means, it will copy everything
	 * of the Fib element fibElement except pointers to other Fib elements
	 * (e. g. for subobjects), these will remain the same.
	 * For that both Fib elements have to be of the same type.
	 *
	 * @see getType()
	 * @param fibElement the Fib element, from which to assign / copy the values
	 * @return true if the values could be copied from the given Fib element
	 * 	fibElement, else false
	 */
	virtual bool assignValues( const cFibElement & fibElement );

#ifndef FEATURE_EQUAL_FIB_OBJECT
	
	/**
	 * This method checks if the given Fib-object is equal to this Fib
	 * -object.
	 * Variables can be others, but must be defined and used in equivalent
	 * Fib-elements.
	 *
	 * @param fibObject the Fib-object to which this Fib-object should be
	 * 	equal
	 * @return true if this Fib-object is equal to the given Fib-object,
	 * 	else false
	 */
	virtual bool equal( const cFibElement & fibObject ) const;

	/**
	 * This method checks if the given Fib-element is equal to this
	 * Fib-element.
	 * The subobjects arn't compared, not even ther count is compared.
	 * Used variables can be others.
	 *
	 * @param fibelement the Fib-element to which this Fib-element should be
	 * 	equal
	 * @return true if this Fib-element is equal to the given Fib-object,
	 * 	else false
	 */
	virtual bool equalElement( const cFibElement & fibelement ) const;

	/**
	 * This method checks if the given Fib-element sets the variable to
	 * the same values as this Fib-element.
	 *
	 * @param variableOwn a pointer to a defined variable in this Fib-element,
	 * 	it is compared to the equivalent variable pVariable in the given
	 * 	Fib-element fibelement
	 * @param fibelement the Fib-element to which this Fib-element should be
	 * 	compared
	 * @param variable a pointer to a defined variable in the other 
	 * 	Fib-element fibelement
	 * @return true if this Fib-element sets the variable to the same
	 * 	values as the Fib-element fibElement
	 */
	virtual bool equalValuesSet( const cFibVariable * variableOwn,
		const cFibElement & fibelement,
		const cFibVariable * variable ) const;

#endif //FEATURE_EQUAL_FIB_OBJECT
	
#endif //SWITCH_JUST_STORE_AND_EVALUE
	/**
	 * This method stores this Fib-object in the XML -format into the
	 * given stream.
	 *
	 * @param stream the stream where this Fib-object should be stored to
	 * @return true if this Fib-object is stored, else false
	 */
	virtual bool storeXml( ostream & stream ) const;


#ifndef SWITCH_JUST_STORE_AND_EVALUE
	
	/**
	 * This method inserts the given Fib-element fibelement on the
	 * specified position. The replaced Fib-element will be the subobject
	 * of the inserted Fib-element fibelement.
	 *
	 * @see getNumberOfElement()
	 * @see getNumberOfElements()
	 * @see getType()
	 * @param cType the type of the Fib-element insted of which the given
	 * 	Fib-element fibelement should be inserted
	 * @param elementPoint the number of the Fib-element, in the order of
	 * 	Fib-elements of the given type cType, in which position the given
	 * 	Fib-element fibelement should be inserted; if 0 the given
	 * 	fibelement will be inserted under this Fib-element
	 * @param fibelement the Fib-element to insert
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	Fib-object
	 * @param bCheckVariables if true (standardvalue) it will be checked if
	 * 	the variables the Fib-element defines are needed, else the 
	 * 	Fib-element will be removed even if its variables are needed elsewher
	 * @return true if the Fib-element fibelement was inserted, else false
	 */
	virtual bool insertElement( cFibElement *fibelement, const char cType='u',
		const unsignedIntFib elementPoint=0, bool bAbsolute=false,
		bool bCheckVariables=true );


	/**
	 * This method inserts the given Fib-object pFibObject on the
	 * specified position. In limb elements on the specified position a
	 * list element will be inserted, with the old Fib-object and the
	 * given Fib-object pFibObject as its subobjects.
	 *
	 * @see getNumberOfElement()
	 * @see getNumberOfElements()
	 * @see overwriteObjectWithObject()
	 * @see getType()
	 * @param cType the type of the Fib-element, on which position the 
	 * 	given Fib-object fibObject should be inserted
	 * @param elementPoint the number of the Fib-element, in the order of
	 * 	Fib-elements of the given type cType, on which position the given
	 * 	Fib-object fibObject should be inserted
	 * @param fibObject the Fib-object to insert
	 * @param first if true, the inserted object will be the first
	 * 	subobject of the new list element
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	Fib-object
	 * @return true if the Fib-object fibObject was inserted, else false
	 */
	virtual bool insertObjectInElement( cFibElement *fibObject, const char cType='u',
		const unsignedIntFib elementPoint=0, bool first=true, 
		bool bAbsolute=false );

	/**
	 * This method overwrites the Fib-object on specified position with
	 * the given Fib-object fibObject. The Fib-object on specified
	 * position will be replaced with the given Fib-object fibObject.
	 *
	 * @see getNumberOfElement()
	 * @see getNumberOfElements()
	 * @see insertObjectInElement()
	 * @see getType()
	 * @param cType the type of the Fib-element, on which position the 
	 * 	given Fib-object fibObject should be inserted
	 * @param elementPoint the number of the Fib-element, in the order of
	 * 	Fib-elements of the given type cType, on which position the given
	 * 	Fib-object fibObject should be inserted
	 * @param fibObject the Fib-object to insert
	 * @param bDeleteOld if true, delete the old Fib-object from the memory
	 * @param bAbsolute if the elementPoint is an absolute value for the wool
	 * 	Fib-object
	 * @return true if the old Fib-object was overwritten and the given 
	 * 	Fib-object fibObject was inserted, else false
	 */
	virtual bool overwriteObjectWithObject( cFibElement *fibObject, const char cType='u',
		const unsignedIntFib elementPoint=0, bool bDeleteOld=true,
		bool bAbsolute=false );

	/**
	 * This method cuts the Fib-element on the specified position.
	 * This works like removeElement(), except that the removed element is 
	 * returned.
	 *
	 * @see isDeletableelement()
	 * @see removeElement()
	 * @see getType()
	 * @param cType the type of the Fib-element to cut
	 * @param elementPoint the number of the Fib-element, in the order of
	 * 	Fib-elements of the given type cType, to cut
	 * @param bAbsolute if the elementPoint is an absolute value for the wool
	 * 	Fib-object
	 * @param bCheckVariables if true (standardvalue) it will be checked if
	 * 	the variables the Fib-element defines are needed, else the 
	 * 	Fib-element will be removed even if its variables are needed elsewher
	 * @return the pointer to the cuted Fib-element or NULL, if the Fib
	 * 	-element couldn't cut
	 */
	virtual cFibElement * cutElement( const char cType='u', const unsignedIntFib
		elementPoint=0, bool bAbsolute=false, bool bCheckVariables=true );

	/**
	 * This method moves a Fib-limb -element (cFibLimb) on the specified
	 * position over iHowfar Fib-elements.
	 * Moving is stoped if an invalid Fib-object would result (e.g. no Fib
	 * -element can be moved over an Fib-elements that defines a variable
	 * the moved Fib-element uses).
	 * Moving an Fib-element into an list element will result in an
	 * list element with the moved element in everyone of it's subobjects.
	 *
	 * @see isDeletableelement()
	 * @see removeElement()
	 * @see getType()
	 * @param cType the type of the Fib-element to move
	 * @param elementPoint the number of the Fib-element, in the order of
	 * 	Fib-elements of the given type cType, to move
	 * @param iHowfar the number of Fib-elements over which the to move
	 * 	Fib-element should be moved; if this value is positiv the Fib
	 * 	-element will be moved over Fib-elements it contains else over
	 * 	Fib-elements it is contained in
	 * @param bAbsolute if the elementPoint is an absolute value for the wool
	 * 	Fib-object
	 * @return the number of Fib-elements over which the to move Fib
	 * 	-element was moved; if this value is positiv the Fib-element
	 * 	was moved over Fib-elements it contains else over Fib-elements
	 * 	it is contained in
	 */
	virtual intFib moveLimbElement( const char cType='u', const unsignedIntFib
		elementPoint=0, const intFib iHowfar=1, bool bAbsolute=false );

#endif //SWITCH_JUST_STORE_AND_EVALUE


/*
 * external objects element methods
 */


	/**
	 * @return The identifier of the external Fib-object this external
	 * 	element stands for. @see lIdentifier
	 */
	longFib getIdentifier() const;
	
	/**
	 * This method sets identifier of the external Fib-object this external
	 * element stands for.
	 * @see lIdentifier
	 *
	 * @param lInIdentifier The to set identifier of the external Fib-object
	 * 	this external element stands for.
	 */
	void setIdentifier( const longFib lInIdentifier );
	
	/**
	 * @see vecInputValues
	 * @see getNumberOfInputValues()
	 * @see setNumberOfInputValues()
	 * @return the vector with the input values of this external object element
	 * 	@see vecInputValues
	 */
	cVectorExtObject * getInputVector();
	
	/**
	 * @see vecInputValues
	 * @see getNumberOfInputValues()
	 * @see setNumberOfInputValues()
	 * @return the vector with the input values of this external object element
	 * 	@see vecInputValues
	 */
	const cVectorExtObject * getInputVector() const;

	/**
	 * @see vecInputValues
	 * @see setNumberOfInputValues()
	 * @see getInputVector()
	 * @return the number of input values of this external element element
	 * 	@see vecInputValues
	 */
	unsignedIntFib getNumberOfInputValues() const;

	/**
	 * This method sets the number of input values, this external object
	 * element has, to the given number.
	 *
	 * @see vecInputValues
	 * @see getNumberOfInputValues()
	 * @see getInputVector()
	 * @param uiNumberOfInputValues the number of input values this external
	 * 	object element should have
	 */
	void setNumberOfInputValues(
		const unsignedIntFib uiNumberOfInputValues );

	/**
	 * @see vecSubobjects
	 * @see setNumberOfSubobject()
	 * @see getSubobject()
	 * @see setSubobject()
	 * @see addSubobject()
	 * @see deleteSubobject()
	 * @return the count of subobjects in this external object element
	 */
	unsignedIntFib getNumberOfSubobjects() const;
	
	/**
	 * This method sets the number of subobjects, this external object
	 * element have, to the given number. It will create or delete
	 * subobjects as necessary, wher created subobjects are NULL with 0
	 * output variables.
	 * The delete process will beginn on the end of the subobject list
	 * and stop if enough subobject are deleted.
	 *
	 * @see vecSubobjects
	 * @see getNumberOfSubobjects()
	 * @see getSubobject()
	 * @see setSubobject()
	 * @see addSubobject()
	 * @see deleteSubobject()
	 * @param uiNumberOfSubobjects the number of subobjects this external
	 * 	object element should have
	 * @param bDeleteOld if true, delete the old subobject from the memory
	 */
	void setNumberOfSubobjects( const unsignedIntFib uiNumberOfSubobjects,
		bool bDeleteOld=true );
	
	/**
	 * @see vecSubobjects
	 * @see setSubobject()
	 * @see getNumberOfSubobjects()
	 * @see setNumberOfSubobject()
	 * @see addSubobject()
	 * @see deleteSubobject()
	 * @param uiNumberSubobject the number of the subobject to
	 * 	return, @see vecSubobjects
	 * @return a pointer to the uiNumberSubobject'th subobject of
	 * 	this external object element or NULL if non such exists
	 */
	cFibElement * getSubobject( const unsignedIntFib uiNumberSubobject );
	
	/**
	 * This method sets the iNumberSubobject'th subobject of this
	 * external object element to the given subobject.
	 * It will create new subobjects if ther are less than uiNumberSubobject
	 * subobjects (@see setNumberOfSubobject() ).
	 * The output variables for the iNumberSubobject'th subobject won't change.
	 *
	 * @see vecSubobjects
	 * @see getSubobject()
	 * @see getNumberOfSubobjects()
	 * @see setNumberOfSubobject()
	 * @see addSubobject()
	 * @see deleteSubobject()
	 * @param uiNumberSubobject the number of the subobject to set
	 * 	(counting from 1)
	 * @param pFibObject the pointer to the uiNumberVariable'th subobject
	 * 	this external object should have
	 * @param bDeleteOld if true, delete the old subobject from the memory
	 * @return true if the subobject was set to the given subobject,
	 * 	else false
	 */
	bool setSubobject( const unsignedIntFib uiNumberSubobject,
		cFibElement* pFibObject, bool bDeleteOld=true );
	
	/**
	 * This method returns the number of output variables of the
	 * uiNumberOfSubobject extern subobject in this external object element, or
	 * 0 if the subobject dosn't exists.
	 *
	 * @see vecSubobjects
	 * @see setNumberOfOutputVariables()
	 * @see getOutputVariables()
	 * @see getOutputVariable()
	 * @param uiNumberOfSubobject the number of the subobject for which
	 * 	the number of output variables is to be returned
	 * @return the count of output variables of the uiNumberOfSubobject
	 * 	extern subobject in this external object element, or 0 if the
	 * 	subobject dosn't exists
	 */
	unsignedIntFib getNumberOfOutputVariables(
		const unsignedIntFib uiNumberOfSubobject ) const;
	
	/**
	 * This method sets the number of output variables of the
	 * uiNumberOfSubobject'th extern subobject in this external object
	 * element to the given value uiNumberOfVariables.
	 *
	 * @see vecSubobjects
	 * @see getNumberOfOutputVariables()
	 * @see getOutputVariables()
	 * @see getOutputVariable()
	 * @param uiNumberOfSubobject the number of the subobject for which
	 * 	the number of output variables is to be set
	 * @param uiNumberOfVariables the number of output variables the
	 * 	uiNumberOfSubobject'th subobject of this external object
	 * 	element should have
	 * @return the new number of output variables the
	 * 	uiNumberOfSubobject'th subobject of this external object
	 * 	element have
	 */
	unsignedIntFib setNumberOfOutputVariables(
		const unsignedIntFib uiNumberOfSubobject,
		const unsignedIntFib uiNumberOfVariables );
	
	/**
	 * This method returns a vector with the pointers to the output
	 * variables of the uiNumberOfSubobject'th subobject.
	 *
	 * @see vecSubobjects
	 * @see getOutputVariable()
	 * @see getNumberOfOutputVariables()
	 * @see setNumberOfOutputVariables()
	 * @param uiNumberOfSubobject the number of the subobject for which
	 * 	the output variables should be returned
	 * @return a vector with the pointers to the output variables of the
	 * 	uiNumberOfSubobject'th subobject, or an empty list if non exists
	 */
	vector< cFibVariable* > getOutputVariables(
		const unsignedIntFib uiNumberOfSubobject );
	
	/**
	 * This method returns a pointer to the uiNumberOfInputVariable'th
	 * output variable of the uiNumberOfSubobject'th subobject of
	 * this external object element.
	 *
	 * @see vecSubobjects
	 * @see getOutputVariables()
	 * @see getNumberOfOutputVariables()
	 * @see setNumberOfOutputVariables()
	 * @param uiNumberOfSubobject the number of the subobject for which
	 * 	the output variable should be returned
	 * @param uiNumberOfOutputVariable the number of the output variable of
	 * 	the uiNumberOfSubobject'th subobject to return
	 * @return a pointer to the uiNumberOfInputVariable'th output variable of
	 * 	the uiNumberOfSubobject'th subobject of this external object element,
	 * 	or NULL if non exists
	 */
	cFibVariable * getOutputVariable( const unsignedIntFib uiNumberOfSubobject,
		const unsignedIntFib uiNumberOfOutputVariable );

	/**
	 * This method adds the given subobject to the subobjects of this extern
	 * object element.
	 * This will fail if:
	 * 	- ther is no subobject (pSubobject==NULL)
	 *
	 * @see vecSubobjects
	 * @see getSubobject()
	 * @see setSubobject()
	 * @see deleteSubobject()
	 * @see getNumberOfSubobjects()
	 * @see setNumberOfSubobject()
	 * @see getOutputVariables()
	 * @see getNumberOfOutputVariables()
	 * @see setNumberOfOutputVariables()
	 * @param pSubobject a pointer to the subobject to add; the object
	 * 	will not be copied, so don't delete it
	 * @param uiPosition the position on which the subobject is to insert in
	 * 	this extern object element subobject vector (counting begins with 1),
	 * 	if 0 or greater the number of subobjects the subobject will be
	 * 	inserted to the end of the subobject list
	 * @param uiNumberOfOutVar the number of output variables of the subobject
	 * 	to add should have
	 * @return true if the subobject pSubobject was inserted, else false
	 */
	bool addSubobject( cFibElement * pSubobject, unsignedIntFib uiPosition = 0,
		const unsignedIntFib uiNumberOfOutVar = 0 );

	/**
	 * This method deletes the uiSubobjectNumber'th subobject in this extern
	 * object element.
	 *
	 * @see vecSubobjects
	 * @see getSubobject()
	 * @see setSubobject()
	 * @see addSubobject()
	 * @see getNumberOfSubobjects()
	 * @see setNumberOfSubobject()
	 * @see getOutputVariables()
	 * @see getNumberOfOutputVariables()
	 * @see setNumberOfOutputVariables()
	 * @param uiSubobjectNumber the number of the subobject in the subobject
	 * 	vector to delete
	 * @param bDeleteOld if true the subobject will be removed from the memory,
	 * 	else yust the reference will be removed from this extern object
	 * 	element;default is true
	 * @return true if the uiSubobjectNumber'th subobject was deleted, else false
	 */
	bool deleteSubobject( unsignedIntFib uiSubobjectNumber,
		bool bDeleteOld=true );


protected:

	/**
	 * This method stores this Fib-object in the compressed Fib-format
	 * into the given stream.
	 * It is needed because the stream can yust store byts but the size of
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
	virtual bool storeBit( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const;

	/**
	 * This method sets each variable, which is defined over an leaf,
	 * to an uniqe integer number greater than the given number
	 * uiLastVariableNumber. While storing this number can be used to
	 * identify the variable.
	 *
	 * @param uiLastVariableNumber the number which was last used, this
	 * 	means also is the greatest used, in this object
	 * @return the number which was last use, this
	 * 	means also is the greatest used, in this object
	 * 	from the method
	 */
	virtual unsignedIntFib enumerateVariablesForStoring(
		unsignedIntFib uiLastVariableNumber = 0 );
	
	/**
	 * This method cuts the connections of this Fib-element to the
	 * given Fib-element.
	 *
	 * @param pFibElement the Fib-element to which to cut the connection
	 */
	virtual void cutConnectionsTo( const cFibElement * pFibElement );

	/**
	 * This method syncronises the subobjects of this cExtObject-class with
	 * the subobjects list @see fibSubobjects of the cFibBranch class.
	 */
	void syncSubobjects();
	
	/**
	 * This method copies the connected object with the given number in the
	 * order of connected objects.
	 * For this every Fib-element, beginning from this Fib-element, that
	 * is part of the connected object will be copied.
	 * Variables which are not defined in the connected object but used
	 * don't change ther reference.
	 * It is an help method for the copy method. It dosn't update the
	 * structural information of the created Fib-object.
	 *
	 * @see copy()
	 * @param iObjectPoint the number of the connected object to copy;
	 * 	the standartvalue is 0 for coping the complet actual object
	 * @return the copy of the connected object or NULL if non such exists
	 */
	virtual cExtObject * copyInternal( const unsignedIntFib iObjectPoint = 0 ) const;

#ifndef SWITCH_JUST_STORE_AND_EVALUE
	
	/**
	 * This method checks if the given variable is defined in the given
	 * direction from this Fib-element.
	 * This is for intern use to get the correct data from
	 * isDefinedVariable() without pCallingFibElement.
	 *
	 * @see cFibVariable
	 * @see isUsedVariable()
	 * @param pVariable the variable to check if it is defined
	 * @param direction the direction from this Fib-element, in which the
	 * 	variable should be defined; standardvalue is ED_POSITION so yust
	 * 	this Fib-element will be checked
	 * @param pCallingFibElement the Fib-Element which called this method
	 * @return true if the variable is used, else false
	 */
	virtual bool isDefinedVariableInternal( const cFibVariable * pVariable,
		edDirection direction = ED_POSITION,
		const cFibElement * pCallingFibElement = NULL ) const;
	
	/**
	 * This method returns all variables defined in the given direction from
	 * this Fib-element.
	 * This is for intern use to get the correct data from
	 * getDefinedVariables() without pCallingFibElement..
	 *
	 * @see cFibVariable
	 * @see getUsedVariables()
	 * @see isDefinedVariable()
	 * @param direction the direction from this Fib-element, in which the
	 * 	variable should be used; standardvalue is ED_POSITION so yust
	 * 	this Fib-element will be checked
	 * @param pCallingFibElement the Fib-Element which called this method
	 * @return the set with all variables used in the given direction from
	 * 	this Fib-element
	 */
	virtual list< cFibVariable* > getDefinedVariablesInternal(
		edDirection direction = ED_HIGHER,
		const cFibElement * pCallingFibElement = NULL );


#ifdef FEATURE_EQUAL_FIB_OBJECT

	/**
	 * This method checks if the given Fib-object is equal to this fib
	 * -object.
	 * Variables can be others, but must be defined and used in equivalent
	 * Fib-elements.
	 *
	 * @param fibObject the Fib-object to which this Fib-object should be
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
	 * @return true if this Fib-object is equal to the given Fib-object,
	 * 	else false
	 */
	virtual bool equalInternal( const cFibElement & fibObject,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const;

	/**
	 * This method checks if the given Fib-element is equal to this fib
	 * -element.
	 * The subobjects arn't compared, not even ther count is compared.
	 * Used variables can be others.
	 *
	 * @param fibElement the Fib-element to which this Fib-element should be
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
	 * @return true if this Fib-element is equal to the given Fib-object,
	 * 	else false
	 */
	virtual bool equalElementInternal( const cFibElement & fibElement,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const;


	/**
	 * This method checks if the given Fib-element sets the variable to
	 * the same values as this Fib-element.
	 *
	 * @param variableOwn a pointer to a defined variable in this Fib-element,
	 * 	it is compared to the equivalent variable fibElement in the given
	 * 	Fib-element fibElement
	 * @param fibElement the Fib-element to which this Fib-element should be
	 * 	compared
	 * @param variable a pointer to a defined variable in the other 
	 * 	Fib-element fibElement
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
	 * @return true if this Fib-element sets the variable to the same
	 * 	values as this Fib-element
	 */
	virtual bool equalValuesSetInternal( const cFibVariable * variableOwn,
		const cFibElement & fibElement,
		const cFibVariable * variable,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const;

#endif //FEATURE_EQUAL_FIB_OBJECT

#endif //SWITCH_JUST_STORE_AND_EVALUE


};//class cExtObject
}//namespace fib

#endif //___C_EXT_OBJECT_H__






