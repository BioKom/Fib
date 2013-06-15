/**
 * @class cFibElement
 * file name: cFibElement.h
 * @author Betti Oesterholz
 * @date 17.04.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a basic Fib-element.
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
 * This file contains the basisclass of all Fib-elements. It's not 
 * possible to create instances from this class.
 * The Fib-elements are the elements of the Fib-multimedialanguage.
 * The class cFibElement defines methods to change the structur of an
 * Fib-object/-tree.
 *
 * If the structur of the Fib-object is changed just set the subobjects
 * and call updateAllValues() from a position wher the highest Fib-element
 * can be reached. The updateAllValues()  method will make the conections.
 * If you remove conections you have to be more carefull.
 *
 */
/*
History:
17.04.2009  Oesterholz  created
06.01.2010  Oesterholz  getAllFibElements() uses now getAllFibElementsFromPosition()
18.04.2010  Oesterholz  evalueObject() methods changed: not a function but
	an object is given to evalue the data
14.03.2011  Oesterholz  getNextFibElement() const added
07.08.2011  Oesterholz  isDefinedVariable() and getDefinedVariables() with
	pCallingFibElement
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
11.12.2011  Oesterholz  cFibSet added
02.01.2012  Oesterholz  cFibMatrix added
19.05.2013  Oesterholz  SWITCH_JUST_STORE_AND_EVALUE implemented
*/


#ifndef ___C_FIB_ELEMENT_H__
#define ___C_FIB_ELEMENT_H__

#include "version.h"
#include "fibDatatyps.h"
#include "cReadBits.h"

#include "cVectorPosition.h"
#include "cVectorProperty.h"
#include "cFibVariable.h"
#include "cDomains.h"

#include "iEvaluePosition.h"
#include "iEvalueFibElement.h"

#include "tinyxml.h"

#include <list>
#include <map>
#include <ostream>
#include <istream>


using std::list;
using std::ostream;
using std::istream;

using namespace fib;

namespace fib{

enum edDirection{
	ED_ALL,
	ED_POSITION,
	ED_BELOW,
	ED_HIGHER,
	ED_BELOW_EQUAL,
	ED_HIGHER_EQUAL
};

class cRoot;//cyclic dependencie
class cFibLeaf;//cyclic dependencie
class VectorProperty;//cyclic dependencie
class cList;//cyclic dependencie


class cFibElement{
protected:

friend class cFibBranch;
friend class cFibLimb;
friend class cFibLeaf;
friend class cRoot;
friend class cList;
friend class cIf;
friend class cProperty;
friend class cArea;
friend class cFunction;
friend class cComment;
friend class cExtObject;
friend class cFibSet;
friend class cFibMatrix;
friend class cFibVariable;

	/**
	 * the Fib-element in which this Fib-element is the subobject or
	 * the Nullpointer NULL if ther is non such
	 */
	cFibElement *pSuperiorElement;


#ifndef FEATURE_FAST_UPDATE

	
	/**
	 * the previous Fib-element in the order of Fib-elements or the
	 * Nullpointer NULL if ther is non such
	 */
	cFibElement * pPreviousFibElement;
	
	/**
	 * the next Fib-element in the order of Fib-elements or the
	 * Nullpointer NULL if ther is non such
	 */
	cFibElement * pNextFibElement;
	
	/**
	 * the next root-element;
	 * This is the next root-element this Element is contained in.
	 */
	cRoot * pNextRootElement;

	/**
	 * the number of this Fib-element in the order of all Fib-elements
	 */
	unsignedIntFib uINumberOfFibElement;

#endif //FEATURE_FAST_UPDATE


#ifdef FEATURE_SIMPLE_CONSTRUCTOR

	/**
	 * parameterconstructor
	 *
	 * @param pInSuperiorElement the Fib-Element in which this Fib-element
	 * 	is the subobject
	 */
	cFibElement( cFibElement * pInSuperiorElement = NULL );

#else //FEATURE_SIMPLE_CONSTRUCTOR

	/**
	 * parameterconstructor
	 *
	 * @param pInSuperiorElement the Fib-Element in which this Fib-element
	 * 	is the subobject
	 * @param pInPreviousFibElement the Fib-Element which stands in th order
	 * 	of Fib-elements befor this Fib-element
	 * @param pInNextFibElement the Fib-Element which stands in th order
	 * 	of Fib-elements behind this Fib-element
	 */
	cFibElement( cFibElement * pInSuperiorElement = NULL,
		cFibElement * pInPreviousFibElement = NULL,
		cFibElement * pInNextFibElement = NULL );
		
#endif //FEATURE_SIMPLE_CONSTRUCTOR


	/**
	 * copyconstructor
	 * This copyconstructor constructs a copy of of the given Fib-Element.
	 * It dosn't copy other Fib-elements than the given, even if ther are
	 * in the Fib-element.
	 *
	 * @param fibElement the Fib-element to copy
	 */
	cFibElement( const cFibElement &fibElement );

public:
	/**
	 * destructor
	 */
	virtual ~cFibElement();


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
	virtual char getType() const = 0;
	
	/**
	 * This function converts a element type character into a string with 
	 * the element name.
	 *
	 * @see getType
	 * @param cType a character for the type of a Fib-element, like the
	 *		getTyp() returns it
	 * @return a string with the name of the Fib-element for the given character
	 */
	static string getTypeName( char cType );
	
	/**
	 * This method checks, if this Fib-element is an valid Fib-element.
	 *
	 * @return true if this Fib-element is an valid Fib-element, else false
	 */
	virtual bool isValidFibElement() const = 0;

	/**
	 * This method returns the superior Fib-element of this Fib-element.
	 *
	 * @return the superior Fib-element of this Fib-element or the NULL 
	 * 	pointer, if non such exists
	 */
	virtual cFibElement * getSuperiorFibElement();


#ifdef FEATURE_FAST_UPDATE
	
	/**
	 * This method returns the next Fib-element in the order of Fib-elements.
	 *
	 * @return a pointer to the next Fib-element in the order of Fib-elements
	 *		or the NULL pointer if non such exists
	 */
	virtual cFibElement * getNextFibElement() = 0;
	
	/**
	 * This method returns the next Fib-element in the order of Fib-elements.
	 *
	 * @return a pointer to the next Fib-element in the order of Fib-elements
	 * 	or the NULL pointer if non such exists
	 */
	const cFibElement * getNextFibElement() const;
	
	/**
	 * This method returns the next Fib-element in the order of 
	 * Fib-elements with the given type cTyp.
	 *
	 * @param cType the type of the Fib-element to return
	 * @return a pointer to the next Fib-element in the order of 
	 * 	Fib-elements with the given type or the NULL pointer if non such
	 * 	exists
	 */
	virtual cFibElement * getNextFibElement( char cType ) = 0;

	/**
	 * This method returns the lNumber'th Fib-element in the order of
	 * Fib-elements with the given type cTyp.
	 *
	 * @param lNumber the number of the Fib-Element to return
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	Fib-object
	 * @return a pointer to the lNumber'th Fib-element in the order of
	 * 	Fib-elements or the NULL pointer if non such exists
	 */
	virtual cFibElement * getConstFibElement( longFib lNumber,
		bool bAbsolute=false ) const = 0;
	
	/**
	 * This method returns the lNumber'th Fib-element in the order of
	 * Fib-elements of the given type cTyp with the given type cTyp.
	 *
	 * @param lNumber the number of the Fib-element to return
	 * @param cType the type of the Fib-element to return
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	Fib-object
	 * @return a pointer to the lNumber'th Fib-element in the order of
	 * 	Fib-elements with the given type or the NULL pointer if non such
	 * 	exists
	 */
	virtual cFibElement * getConstFibElement( char cType, longFib lNumber,
		bool bAbsolute=false ) const = 0;

#else //FEATURE_FAST_UPDATE

	/**
	 * This method returns the next Fib-element in the order of Fib-elements.
	 *
	 * @return a pointer to the next Fib-element in the order of Fib-elements
	 *		or the NULL pointer if non such exists
	 */
	virtual cFibElement * getNextFibElement();

	/**
	 * This method returns the next Fib-element in the order of 
	 * Fib-elements with the given type cTyp.
	 *
	 * @param cType the type of the Fib-element to return
	 * @return a pointer to the next Fib-element in the order of 
	 * 	Fib-elements with the given type or the NULL pointer if non such
	 * 	exists
	 */
	virtual cFibElement * getNextFibElement( char cType );

	/**
	 * This method returns the lNumber'th Fib-element in the order of
	 * Fib-elements.
	 *
	 * @param lNumber the number of the Fib-Element to return
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	Fib-object
	 * @return a pointer to the lNumber'th Fib-element in the order of
	 * 	Fib-elements or the NULL pointer if non such exists
	 */
	virtual cFibElement * getConstFibElement( longFib lNumber,
		bool bAbsolute=false ) const;

	/**
	 * This method returns the lNumber'th Fib-element in the order of
	 * Fib-elements of the given type cTyp with the given type cTyp.
	 *
	 * @param cType the type of the Fib-element to return
	 * @param lNumber the number of the Fib-element to return
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	Fib-object
	 * @return a pointer to the lNumber'th Fib-element in the order of
	 * 	Fib-elements with the given type or the NULL pointer if non such
	 * 	exists
	 */
	virtual cFibElement * getConstFibElement( char cType, longFib lNumber,
		bool bAbsolute=false ) const;

#endif //FEATURE_FAST_UPDATE
	
	/**
	 * This method returns the lNumber'th Fib-element in the order of
	 * Fib-elements.
	 *
	 * @param lNumber the number of the Fib-Element to return
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	Fib-object
	 * @return a pointer to the lNumber'th Fib-element in the order of
	 * 	Fib-elements or the NULL pointer if non such exists
	 */
	cFibElement *getFibElement( longFib lNumber,
		bool bAbsolute=false );

	/**
	 * This method returns the lNumber'th Fib-element in the order of
	 * Fib-elements of the given type cTyp with the given type cTyp.
	 *
	 * @param cType the type of the Fib-element to return
	 * @param lNumber the number of the Fib-element to return
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	Fib-object
	 * @return a pointer to the lNumber'th Fib-element in the order of
	 * 	Fib-elements with the given type or the NULL pointer if non such
	 * 	exists
	 */
	cFibElement *getFibElement( char cType, longFib lNumber,
		bool bAbsolute=false );

#ifndef SWITCH_JUST_STORE_AND_EVALUE
	/**
	 * This method returns a number of (lNumberOfMaxReturnedElements)
	 * Fib-elements beginning from the reference Fib-element in the
	 * given direction of the given type cType.
	 *
	 * @param cTypeBasis the type of the reference Fib-element
	 * @param lNumber the number of the reference Fib-element to return
	 * @param cType the type of the Fib-elements to return;
	 * 	'w' stands for wrong/ not correct Fib-elements
	 * @param direction the direction, beginning from the reference 
	 * 	Fib-element, in which the to return Fib-elements should stand
	 * @param lNumberOfMaxReturnedElements the maximal number of 
	 * 	Fib-elements to return
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	Fib-object
	 * @return a list with the pointers to the to returning Fib-elements
	 */
	list<cFibElement*> getAllFibElements( char cTypeBasis='u',
		longFib lNumber=1, char cType='u', edDirection direction=ED_ALL,
		unsignedLongFib lNumberOfMaxReturnedElements=0, bool bAbsolute=false );

#endif //SWITCH_JUST_STORE_AND_EVALUE
	
	/**
	 * This method evaluades the Fib-object.
	 *
	 * @pattern strategy
	 * @param evaluePosition a reference to the object with the
	 * 	evaluePosition() method to evalue /store the positions and ther
	 * 	properties; everytime a point (to evalue) is reached in the
	 * 	evaluation, this method is called with the position and the
	 * 	properties of the point; @see iEvaluePosition
	 * @param objectPoint the object point in the order of true partobjects
	 *		to evalue
	 * @return if the evalueation was successfull true, else false
	 */
	bool evalueObjectSimple( iEvaluePosition & evaluePosition,
		const unsignedIntFib objectPoint = 0 ) const;


	/**
	 * This method evaluades the Fib-object.
	 *
	 * @pattern strategy
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
		list<cVectorProperty> & liVecProperties ) const = 0;

	/**
	 * This method evaluades the Fib-object.
	 * Evertime a Fib-elements, with a type of the given type chars in
	 * liCFibElementTyps, is reached while evaluation, it is given
	 * back with the properties which it has.
	 * Ever pointelement is given back. The type chars for pointelements
	 * don't need to be in the list liCFibElementTyps.
	 *
	 * @pattern strategy
	 * @param evalueFibElement a reference to the object with the
	 * 	evalueElement() method to evalue /store the Fib-elements and ther
	 * 	properties; everytime a Fib-element (with one of the type given
	 * 	in liCFibElementTyps) is reached in the evaluation, the method
	 * 	evalueElement() of this objects is called with the Fib-element
	 * 	and the properties of the Fib-element; @see iEvalueFibElement
	 * @param objectPoint the object point in the order of true partobjects
	 *		to evalue
	 * @param liCFibElementTyps a list with the type chars (@see getType)
	 * 	of the Fib-elements to return
	 * @return if the evalueation was successfull true, else false
	 */
	bool evalueObjectSimple( iEvalueFibElement & evalueFibElement,
		const unsignedIntFib objectPoint = 0,
		const list<char> liCFibElementTyps = list<char>() );
	
	/**
	 * This method evaluades the Fib-object.
	 * Evertime a Fib-elements, with a type of the given type chars in
	 * liCFibElementTyps, is reached while evaluation, it is given
	 * back with the properties which it has.
	 * Ever pointelement is given back. The type chars for pointelements
	 * don't need to be in the list liCFibElementTyps.
	 *
	 * @pattern strategy
	 * @param evalueFibElement a reference to the object with the
	 * 	evalueElement() method to evalue /store the Fib-elements and ther
	 * 	properties; everytime a Fib-element (with one of the type given
	 * 	in liCFibElementTyps) is reached in the evaluation, the method
	 * 	evalueElement() of this objects is called with the Fib-element
	 * 	and the properties of the Fib-element; @see iEvalueFibElement
	 * @param objectPoint the object point in the order of true partobjects
	 *		to evalue
	 * @param liVecProperties a list with the property vectors which should
	 * 	be global for the evalued object
	 * @param liCFibElementTyps a list with the type chars (@see getType)
	 * 	of the Fib-elements to return
	 * @return if the evalueation was successfull true, else false
	 */
	virtual bool evalueObject( iEvalueFibElement & evalueFibElement,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties,
		const list<char> & liCFibElementTyps ) = 0;


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
	virtual unsignedLongFib getTimeNeed( unsignedLongFib lMaxTime=0 ) const = 0;

	/**
	 * This method evaluades the size of the Fib-object in bits in the
	 * compressed file form.
	 * The optionalpart field of root-elements will be ignored.
	 *
	 * @see store()
	 * @return the size of the Fib-object in bits in the compressed form
	 */
	virtual unsignedLongFib getCompressedSize() const = 0;

#ifndef SWITCH_JUST_STORE_AND_EVALUE
	
	/**
	 * This method checks if the given variable is used in the given
	 * direction from this Fib-element.
	 *
	 * @see cFibVariable
	 * @see isDefinedVariable()
	 * @param variable the variable to check if it is used
	 * @param direction the direction from this Fib-element, in which the
	 * 	variable should be used; standard value is ED_POSITION so yust
	 * 	this Fib-element will be checked
	 * @return true if the variable is used, else false
	 */
	virtual bool isUsedVariable( const cFibVariable *variable ,
		edDirection direction=ED_POSITION ) const = 0;

	/**
	 * This method returns all variables used in the given direction from
	 * this Fib-element.
	 *
	 * @see cFibVariable
	 * @see isDefinedVariable()
	 * @param direction the direction from this Fib-element, in which the
	 * 	variable should be used; standard value is ED_POSITION so yust
	 * 	this Fib-element will be checked
	 * @return the set with all variables used in the given direction from
	 * 	this Fib-element
	 */
	virtual set<cFibVariable*> getUsedVariables( edDirection direction=ED_POSITION ) = 0;

	/**
	 * This method checks if the given variable is defined in the given
	 * direction from this Fib-element.
	 *
	 * @see cFibVariable
	 * @see isUsedVariable()
	 * @param variable the variable to check if it is defined
	 * @param direction the direction from this Fib-element, in which the
	 * 	variable should be defined; standard value is ED_POSITION so yust
	 * 	this Fib-element will be checked
	 * @return true if the variable is defined, else false
	 */
	virtual bool isDefinedVariable( const cFibVariable *variable ,
		edDirection direction=ED_POSITION ) const;

	/**
	 * This method returns all variables defined in the given direction from
	 * this Fib-element.
	 *
	 * @see cFibVariable
	 * @see getUsedVariables()
	 * @see isDefinedVariable()
	 * @param direction the direction from this Fib-element, in which the
	 * 	variable should be defined; standard value is ED_HIGHER so yust
	 * 	higher Fib-elements will be checked
	 * @return the set with all variables defined in the given direction from
	 * 	this Fib-element
	 */
	virtual list<cFibVariable*> getDefinedVariables( edDirection direction=ED_HIGHER );

	/**
	 * This method checks if the variables in the given variableset are
	 * defined in the given direction from this Fib-element.
	 *
	 * @see cFibVariable
	 * @see isUsedVariable()
	 * @param setVariable the set with the  variable to check, if it is defined
	 * @param direction the direction from this Fib-element, in which the
	 * 	variables should be defined; standard value is ED_HIGHER so yust
	 * 	higher Fib-elements will be checked
	 * @return true if the variables is are all defined, else false
	 */
	bool variablesAreDefined( const set<cFibVariable*> & setVariable ,
		edDirection direction=ED_HIGHER ) const;

#endif //SWITCH_JUST_STORE_AND_EVALUE

	/**
	 * This method replace the variable variableOld with the variable
	 * variableNew in the object.
	 * Don't touch variable definitions, just the uses of the varaible
	 * variableOld will be changed.
	 *
	 * @see cFibVariable
	 * @see isUsedVariable()
	 * @see isDefinedVariable()
	 * @param variableOld the variable to replace
	 * @param variableNew the variable with which the variable variableOld
	 * 	is to replace
	 * @return true if the variable variableOld is replaced with variableNew,
	 * 	else false
	 */
	virtual bool replaceVariable( cFibVariable *variableOld,
		cFibVariable *variableNew ) = 0;
		

#ifdef FEATURE_FAST_UPDATE

	/**
	 * This method returns the number of this Fib-element in the order of
	 * Fib-Elements or order of Fib-Elements of the same type if bOfType
	 * is true.
	 *
	 * @see getNumberOfElements()
	 * @param bOfType if true the returned number is the number the order
	 * 	of Fib-elements of the same type as this Fib-Element, else in
	 * 	the order of all Fib-elements
	 * @return the number of this Fib-element in the order of fib
	 * 	-Elements or order of Fib-Elements of the same type if bOfType
	 * 	is true
	 */
	virtual unsignedIntFib getNumberOfElement( bool bOfType=false ) const = 0;
	
	/**
	 * This method returns the number of this Fib-element in the order of
	 * move points.
	 *
	 * @see getNumberOfMovePoints()
	 * @return the number of this Fib-element in the order of move points
	 */
	virtual unsignedIntFib getNumberOfMovePoint() const = 0;
	
#else //FEATURE_FAST_UPDATE

	/**
	 * This method returns the number of this Fib-element in the order of
	 * Fib-Elements or order of Fib-Elements of the same type if bOfType
	 * is true.
	 *
	 * @see getNumberOfElements()
	 * @param bOfType if true the returned number is the number the order
	 * 	of Fib-elements of the same type as this Fib-Element, else in
	 * 	the order of all Fib-elements
	 * @return the number of this Fib-element in the order of fib
	 * 	-Elements or order of Fib-Elements of the same type if bOfType
	 * 	is true
	 */
	virtual unsignedIntFib getNumberOfElement( bool bOfType=false ) const;

	/**
	 * This method returns the number of this Fib-element in the order of
	 * move points.
	 *
	 * @see getNumberOfMovePoints()
	 * @return the number of this Fib-element in the order of move points
	 */
	virtual unsignedIntFib getNumberOfMovePoint() const;

#endif //FEATURE_FAST_UPDATE

	
	/**
	 * This method returns the number of the next connected object point
	 * in the order of connected object points that conntains this fib
	 * -element.
	 *
	 * @see getNumberOfObjectPoints()
	 * @return the number of the next connected object point for this fib 
	 * 	-element
	 */
	virtual unsignedIntFib getNumberOfObjectPoint() const;
	
	/**
	 * This method returns the number of Fib-elements of a type in this fib
	 * -object.
	 *
	 * @see getType()
	 * @see getNumberOfElement()
	 * @param cType the character of the type ( @see getType() ), for which
	 * 	the elements should be counted; u (the standartvalue) stands for
	 * 	Fib-Elements of any type
	 * @return the number of Fib-elements of a type in the Fib-object
	 */
	virtual unsignedIntFib getNumberOfElements( char cType='u' ) const = 0;

	/**
	 * This method returns the number of move points in this Fib-object.
	 *
	 * @see getNumberOfMovePoint()
	 * @return the number of move points in this Fib-object
	 */
	virtual unsignedIntFib getNumberOfMovePoints() const = 0;
	
	/**
	 * This method returns the number of object points in this Fib-object.
	 *
	 * @see getNumberOfObjectPoint()
	 * @return the number of object points in this Fib-object
	 */
	virtual unsignedIntFib getNumberOfObjectPoints() const = 0;
	
#ifndef SWITCH_JUST_STORE_AND_EVALUE

	/**
	 * This method converts the number of the elementPoint Fib-element
	 * of the type cType in this Fib-object to the number it has in the
	 * order of all Fib-elements.
	 *
	 * @see getNumberOfElement()
	 * @see getNumberOfElements()
	 * @see getType()
	 * @param cType the type the original Fib-element has
	 * @param elementPoint the number of the original Fib-element in the
	 * 	order of Fib-elements of the type cType
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	Fib-object
	 * @return the number of the elementPoint Fib-element of the type
	 * 	cType in this Fib-object has in the order of all Fib-elements
	 */
	virtual unsignedIntFib typeElementPointToElementPoint( const char cType,
		const unsignedIntFib elementPoint, bool bAbsolute=false ) const;

	/**
	 * This method returns the numbers of all object points that contain the
	 * elementPoint Fib-element of the type cType.
	 *
	 * @see getNumberOfElement()
	 * @see getNumberOfElements()
	 * @see getNumberOfObjectPoint()
	 * @see getNumberOfObjectPoints()
	 * @see getType()
	 * @param cType the type the Fib-element has
	 * @param elementPoint the number of the Fib-element in the order of
	 * 	Fib-elements of the type cType
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	Fib-object
	 * @return a list of the numbers of all object points that contain the
	 * 	elementPoint Fib-element of the type cType
	 */
	virtual list<unsignedIntFib> elementPointToObjectPoints( const char cType,
		const unsignedIntFib elementPoint, bool bAbsolute=false ) const;

	/**
	 * This method returns the numbers of all object points that contain the
	 * elementPoint Fib-element of the type cType.
	 *
	 * @see getNumberOfElement()
	 * @see getNumberOfElements()
	 * @see getNumberOfObjectPoint()
	 * @see getNumberOfObjectPoints()
	 * @see getType()
	 * @param pFibElement the Fib-element for which the object points
	 * 	are to evalue
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	Fib-object
	 * @return a list of the numbers of all object points that contain the
	 * 	elementPoint Fib-element of the type cType
	 */
	virtual list<unsignedIntFib> getObjectPointsForElement(
		const cFibElement * pFibElement, bool bAbsolute=false ) const;

	/**
	 * This method returns the number of the Fib-element over wich the
	 * objectPoint object point is defined.
	 *
	 * @see getNumberOfElement()
	 * @see getNumberOfElements()
	 * @see getNumberOfObjectPoint()
	 * @see getNumberOfObjectPoints()
	 * @param uiObjectPoint the number of the object point for which the
	 * 	definig Fib-element number should be returned
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	Fib-object
	 * @return the number of the Fib-element over wich the objectPoint
	 * 	object point is defined
	 */
	virtual unsignedIntFib objectPointToElementPoint( const unsignedIntFib 
		uiObjectPoint, bool bAbsolute=false ) const = 0;

	/**
	 * This method inserts the given Fib-element fibElement on the
	 * specified position. The replaced Fib-element will be the subobject
	 * of the inserted Fib-element fibElement.
	 *
	 * @see getNumberOfElement()
	 * @see getNumberOfElements()
	 * @see getType()
	 * @param cType the type of the Fib-element instead of which the given
	 * 	Fib-element fibElement should be inserted
	 * @param elementPoint the number of the Fib-element, in the order of
	 * 	Fib-elements of the given type cType, in which position the given
	 * 	Fib-element fibElement should be inserted; if 0 the given
	 * 	fibElement will be inserted under this Fib-element
	 * @param fibElement the Fib-element to insert
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	Fib-object
	 * @param bCheckVariables if true (standard value) it will be checked if
	 * 	the variables the Fib-element defines are needed, else the 
	 * 	Fib-element will be removed even if its variables are needed elsewher
	 * @return true if the Fib-element fibElement was inserted, else false
	 */
	virtual bool insertElement( cFibElement *fibElement, const char cType='u',
		const unsignedIntFib elementPoint=0, bool bAbsolute=false,
		bool bCheckVariables=true ) = 0;

#endif //SWITCH_JUST_STORE_AND_EVALUE

	/**
	 * This method inserts the given Fib-object fibObject on the
	 * specified position. On the specified position a listelement will
	 * be inserted, with the old Fib-object and the given Fib-object
	 * fibObject as its subobjects.
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
	 * 	subobject of the new listelement
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	Fib-object
	 * @return true if the Fib-object fibObject was inserted, else false
	 */
	virtual bool insertObjectInElement( cFibElement *fibObject, const char cType='u',
		const unsignedIntFib elementPoint=0, bool first=true, 
		bool bAbsolute=false ) = 0;

#ifndef SWITCH_JUST_STORE_AND_EVALUE
	
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
		bool bAbsolute=false ) = 0;

	/**
	 * This method removes the connected object with the given number in
	 * the order of connected object points.
	 * For this the defining subobject in an listelement will be removed.
	 * If the listelement contains after the operation yust one subobject,
	 * the listelement will be replaced with the subobject.
	 *
	 * @param objectPoint the number of the connected object to remove
	 * @param bDeleteOld if true, delete the connected object from the
	 * 	memory, else yust remove it's pointers
	 * @param bAbsolute if the objectPoint is an absolute value for the wool
	 * 	Fib-object
	 * @return true if the connected Fib-object was removed, else false
	 */
	virtual bool removeObject( const unsignedIntFib objectPoint,
		bool bDeleteOld=true, bool bAbsolute=false ) = 0;

#endif //SWITCH_JUST_STORE_AND_EVALUE
	
	/**
	 * This method checks, if all Fib-elements of this Fib-object
	 * have the subobjects they need to be correct.
	 *
	 * @return true if all Fib-elements of this Fib-object have the
	 * 	subobjects they need to be correct, else false
	 */
	virtual bool hasUnderAllObjects() const = 0;

#ifndef SWITCH_JUST_STORE_AND_EVALUE
	
	/**
	 * This method checks, if the Fib-element on the specified position
	 * is deletable.
	 * An deletable Fib-element doesn't make the Fib-object invalid if
	 * it is deleted (e.g. points- and listelements are never deletable).
	 *
	 * @see removeElement()
	 * @see cutElement()
	 * @see getType()
	 * @param cType the type of the Fib-element to check
	 * @param elementPoint the number of the Fib-element, in the order of
	 * 	Fib-elements of the given type cType, to check
	 * @param bAbsolute if the elementPoint is an absolute value for the wool
	 * 	Fib-object
	 * @param bCheckVariables if true (standard value) it will be checked if
	 * 	the variables the Fib-element defines are needed, else the 
	 * 	Fib-element will be removed even if its variables are needed elsewher
	 * @return true if the Fib-element is deletable, else false
	 */
	virtual bool isRemovableElement( const char cType='u', const unsignedIntFib
		elementPoint=0, bool bAbsolute=false, bool bCheckVariables=true ) const;

	/**
	 * This method removes the Fib-element on the specified position.
	 *
	 * @see isDeletableElement()
	 * @see getType()
	 * @param cType the type of the Fib-element to remove
	 * @param elementPoint the number of the Fib-element, in the order of
	 * 	Fib-elements of the given type cType, to remove
	 * @param bAbsolute if the elementPoint is an absolute value for the wool
	 * 	Fib-object
	 * @param bCheckVariables if true (standard value) it will be checked if
	 * 	the variables the Fib-element defines are needed, else the 
	 * 	Fib-element will be removed even if its variables are needed elsewher
	 * @return true if the Fib-element was removed, else false
	 */
	virtual bool removeElement(  const char cType='u', const unsignedIntFib 
		elementPoint=0, bool bAbsolute=false, bool bCheckVariables=true );

	/**
	 * This method cuts the Fib-element on the specified position.
	 * This works like removeElement(), except that the removed element is
	 * returned.
	 *
	 * @see isDeletableElement()
	 * @see removeElement()
	 * @see getType()
	 * @param cType the type of the Fib-element to cut
	 * @param elementPoint the number of the Fib-element, in the order of
	 * 	Fib-elements of the given type cType, to cut
	 * @param bAbsolute if the elementPoint is an absolute value for the wool
	 * 	Fib-object
	 * @param bCheckVariables if true (standard value) it will be checked if
	 * 	the variables the Fib-element defines are needed, else the 
	 * 	Fib-element will be removed even if its variables are needed elsewher
	 * @return the pointer to the cuted Fib-element or NULL, if the fib
	 * 	-element couldn't cut
	 */
	virtual cFibElement *cutElement( const char cType='u', const unsignedIntFib
		elementPoint=0, bool bAbsolute=false, bool bCheckVariables=true ) = 0;

#endif //SWITCH_JUST_STORE_AND_EVALUE
		
#ifdef FEATURE_FAST_UPDATE
	
	/**
	 * This method deletes this given Fib-object with all the fib
	 * elements it contains and is contained in. The memory for the fib
	 * -object is freed.
	 */
	virtual void deleteObject() = 0;
	
	/**
	 * This method deletes the whool given Fib-object with all the fib
	 * elements it contains and is contained in. The memory for the fib
	 * -object is freed.
	 *
	 * @param fibObject the Fib-object to delete
	 */
	static void deleteObject( cFibElement * fibObject );

#else //FEATURE_FAST_UPDATE
	/**
	 * This method deletes the whool given Fib-object with all the fib
	 * elements it contains and is contained in. The memory for the fib
	 * -object is freed.
	 *
	 * @param fibObject the Fib-object to delete
	 */
	static void deleteObject( cFibElement * fibObject );
#endif //FEATURE_FAST_UPDATE

#ifndef SWITCH_JUST_STORE_AND_EVALUE
	/**
	 * @return true if this Fib-element is movebel else false
	 */
	virtual bool isMovable() const;

	/**
	 * This method moves a Fib-limb -element (cFibLimb) on the specified
	 * position over iHowfar Fib-elements.
	 * Moving is stoped if an invalid Fib-object would result (e.g. no fib
	 * -element can be moved over an Fib-elements that defines a variable
	 * the moved Fib-element uses).
	 * Moving an Fib-element into an listelement will result in an
	 * listelement with the moved element in everyone of it's subobjects.
	 *
	 * @see isDeletableElement()
	 * @see removeElement()
	 * @see getType()
	 * @param cType the type of the Fib-element to move
	 * @param elementPoint the number of the Fib-element, in the order of
	 * 	Fib-elements of the given type cType, to move
	 * @param iHowfar the number of Fib-elements over which the to move
	 * 	Fib-element should be moved; if this value is positiv the fib
	 * 	-element will be moved over Fib-elements it contains else over
	 * 	Fib-elements it is contained in
	 * @param bAbsolute if the elementPoint is an absolute value for the wool
	 * 	Fib-object
	 * @return the number of Fib-Elements over which the to move fib
	 * 	-element was moved; if this value is positiv the Fib-element
	 * 	was moved over Fib-elements it contains else over Fib-elements
	 * 	it is contained in
	 */
	virtual intFib moveLimbElement( const char cType='u', const unsignedIntFib 
		elementPoint=0, const intFib iHowfar=1, bool bAbsolute=false ) = 0;

#endif //SWITCH_JUST_STORE_AND_EVALUE
	
	/**
	 * This method duplicates the whole Fib-object, beginning with it's
	 * highest root-element (the one which contains all the other elements).
	 *
	 * @return the cloned/ duplicates Fib-object
	 */
	virtual cFibElement *clone( ) const;

	/**
	 * This method copies the connected object with the given number in the
	 * order of connected objects.
	 * For this every Fib-element, beginning from this Fib-element, that
	 * is part of the connected object will be copied.
	 * Variables which are not defined in the connected object but used
	 * don't change ther reference.
	 *
	 * @param iObjectPoint the number of the connected object to copy;
	 * 	the standartvalue is 0 for coping the complet actual object
	 * @return the copy of the connected object or NULL if non such exists
	 */
	virtual cFibElement *copy( const unsignedIntFib iObjectPoint=0 ) const;

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
	virtual cFibElement *copyElement( const char cType='u', const unsignedIntFib
		elementPoint=0, bool bAbsolute=false ) const = 0;

#ifndef SWITCH_JUST_STORE_AND_EVALUE

#ifdef FEATURE_EQUAL_FIB_OBJECT
	/**
	 * This method checks if the given Fib-object is equal to this fib
	 * -object.
	 * Variables can be others, but must be defined and used in equivalent
	 * Fib-elements.
	 *
	 * @see equalInternal()
	 * @param fibObject the Fib-object to which this Fib-object should be
	 * 	equal
	 * @param bCheckExternalObjects if true the external objects of
	 * 	cExtObject will be compared
	 * @return true if this Fib-object is equal to the given Fib-object,
	 * 	else false
	 */
	virtual bool equal( const cFibElement & fibObject,
		const bool bCheckExternalObjects=true ) const;
	
	/**
	 * This method checks if the given Fib-element is equal to this fib
	 * -element.
	 * The subobjects arn't compared, not even ther count is compared.
	 * Used variables can be others.
	 *
	 * @param fibElement the Fib-element to which this Fib-element should be
	 * 	equal
	 * @param bCheckExternalObjects if true the external objects of
	 * 	cExtObject will be compared
	 * @return true if this Fib-element is equal to the given Fib-object,
	 * 	else false
	 */
	virtual bool equalElement( const cFibElement & fibElement,
		const bool bCheckExternalObjects=true ) const;

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
	 * @param bCheckExternalObjects if true the external objects of
	 * 	cExtObject will be compared
	 * @return true if this Fib-element sets the variable to the same
	 * 	values as this Fib-element
	 */
	virtual bool equalValuesSet( const cFibVariable * variableOwn,
		const cFibElement & fibElement,
		const cFibVariable * variable,
		const bool bCheckExternalObjects=true ) const;

#else //FEATURE_EQUAL_FIB_OBJECT

	/**
	 * This method checks if the given Fib-object is equal to this fib
	 * -object.
	 * Variables can be others, but must be defined and used in equivalent
	 * Fib-elements.
	 *
	 * @param fibObject the Fib-object to which this Fib-object should be
	 * 	equal
	 * @return true if this Fib-object is equal to the given Fib-object,
	 * 	else false
	 */
	virtual bool equal( const cFibElement & fibObject ) const = 0;

	/**
	 * This method checks if the given Fib-element is equal to this fib
	 * -element.
	 * The subobjects arn't compared, not even ther count is compared.
	 * Used variables can be others.
	 *
	 * @param fibElement the Fib-element to which this Fib-element should be
	 * 	equal
	 * @return true if this Fib-element is equal to the given Fib-object,
	 * 	else false
	 */
	virtual bool equalElement( const cFibElement & fibElement ) const = 0;

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
	 * @return true if this Fib-element sets the variable to the same
	 * 	values as this Fib-element
	 */
	virtual bool equalValuesSet( const cFibVariable * variableOwn,
		const cFibElement & fibElement,
		const cFibVariable * variable ) const;

#endif //FEATURE_EQUAL_FIB_OBJECT

#endif//SWITCH_JUST_STORE_AND_EVALUE

	/**
	 * This method stores this Fib-object in the XML -format into the
	 * given stream.
	 *
	 * @param stream the stream where this Fib-object should be stored to
	 * @return true if this Fib-object is stored, else false
	 */
	virtual bool storeXml( ostream &stream ) const = 0;
	
	/**
	 * This method restores this Fib-object from the stream where it is
	 * stored in the XML -format.
	 *
	 * @pattern Factory Method
	 * @param stream the stream where the Fib-object is stored in
	 * @param outStatus An pointer to an integervalue where the errorvalue
	 * 	can be stored to. If the pointer is NULL no errorvalue will be
	 * 	given back.
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid stream
	 * 		- -2 loading error, invalid data in stream
	 * 		- 1 loading warning, invalid data in stream, error could be corrected
	 * 		- 2 loading warning, invalid data in stream, maybe the loaded
	 * 			object is wrong
	 * @return the readed Fib-object or the Nullpointer NULL, if reading
	 * 	was not possible
	 */
	static cFibElement *restoreXml( istream &stream, intFib *outStatus=NULL );

	/**
	 * This method restores this Fib-object from the TinyXml handle where
	 * it is stored.
	 *
	 * @pattern Factory Method
	 * @param pXmlNode a pointer to the TinyXml node the Fib-object is stored in
	 * @param outStatus An pointer to an integervalue where the errorvalue
	 * 	can be stored to. If the pointer is NULL no errorvalue will be
	 * 	given back.
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid node
	 * 		- -2 loading error, invalid data in node
	 * 		- 1 loading warning, invalid data in node, error could be corrected
	 * 		- 2 loading warning, invalid data in node, maybe the loaded
	 * 			object is wrong
	 * @return the readed Fib-object or the Nullpointer NULL, if reading
	 * 	was not possible
	 */
	static cFibElement *restoreXml( const TiXmlNode * pXmlNode, intFib *outStatus=NULL );

	/**
	 * This method restores this Fib-object from the TinyXml node where
	 * it is stored.
	 *
	 * @pattern Factory Method
	 * @param pXmlNode a pointer to the TinyXml node the Fib-object is stored in
	 * @param outStatus An reference to an integervalue where the errorvalue
	 * 	can be stored to.
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid node
	 * 		- -2 loading error, invalid data in node
	 * 		- 1 loading warning, invalid data in node, error could be corrected
	 * 		- 2 loading warning, invalid data in node, maybe the loaded
	 * 			object is wrong
	 * @param liDefinedVariables a list with the defined variables for the
	 * 	to restore Fib-element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 * @return the readed Fib -object or the Nullpointer NULL, if reading
	 * 	was not possible
	 */
	static cFibElement * restoreXml( const TiXmlNode * pXmlNode,
		intFib &outStatus, list<cFibVariable*> & liDefinedVariables );


	/**
	 * This method stores this Fib-object in the compressed Fib-format
	 * into the given stream.
	 *
	 * @param stream the stream where this Fib-object should be stored to
	 * @return true if this Fib-object is stored, else false
	 */
	virtual bool store( ostream &stream ) const;

	/**
	 * This method restores this Fib-object from the stream where it is
	 * stored in the compressed Fib-format.
	 *
	 * @pattern Factory Method
	 * @param stream the stream where this Fib-object is stored to in
	 * @param outStatus An pointer to an integervalue where the errorvalue
	 * 	can be stored to. If the pointer is NULL no errorvalue will be
	 * 	given back.
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid stream
	 * 		- -2 loading error, invalid data in stream
	 * 		- 1 loading warning, invalid data in stream, error could be corrected
	 * 		- 2 loading warning, invalid data in stream, maybe the loaded
	 * 			object is wrong
	 * @return the readed Fib-object or the Nullpointer NULL, if reading
	 * 	was not possible
	 */
	static cFibElement *restore( istream &stream, intFib *outStatus=NULL );

	/**
	 * @return a pointer to the next superior root element or NULL, if non
	 * 	such exists
	 */
	virtual cRoot * getSuperiorRootElement();
	
	/**
	 * @return a pointer to the next superior root element or NULL, if non
	 * 	such exists
	 */
	virtual const cRoot * getSuperiorRootElement() const;

	/**
	 * This method returns the identifiers of all root-objects of this
	 * object.
	 *
	 * @return the identifiers of all root-objects of this object
	 */
	virtual list<longFib> getAllRootObjectIdentifiers() const;

	/**
	 * This method returns the identifiers of all database -objects, in the
	 * actual database.
	 *
	 * @return the identifiers of all database -objects
	 */
	virtual list<longFib> getAllDatabaseObjectIdentifiers() const;

	/**
	 * This method returns the root-object for the given identifier.
	 * If non such exists the Nullpoint NULL is returned.
	 *
	 * @param lIdentifier the identifier of the root-object to return
	 * @return the root-object for the given identifier or NULL if non
	 * 	such exists
	 */
	virtual cRoot *getRootObject( longFib lIdentifier );

	/**
	 * This method returns the identifiers of all from this Fib-element
	 * accessible root-objects of this object.
	 *
	 * @return the identifiers of all accessible root-objects
	 */
	virtual list<longFib> getAllAccessibleRootObjectIdentifiers() const;

	/**
	 * This method returns the from this Fib-element accessible root
	 * -object for the given identifier. If non such exists the Nullpointer
	 * NULL is returned.
	 *
	 * @param lIdentifier the identifier of the root-object to return
	 * @return the accessible root-object for the given identifier or NULL
	 * 	if non such exists
	 */
	virtual cRoot *getAccessibleRootObject( longFib lIdentifier );

	/**
	 * This method returns the domains that are valid for this Fib-element.
	 *
	 * @return the domains that are valid for this Fib-element
	 */
	virtual cDomains getValidDomains() const;

	/**
	 * This method returns the value domains that are valid for this 
	 * Fib-element.
	 *
	 * @return the value domains that are valid for this Fib-element
	 */
	virtual cDomains getValidValueDomains() const;

	/**
	 * This method returns the number of dimensions in this
	 * Fib-Multimediaobject.
	 *
	 * @return the number of dimensions in
	 */
	virtual unsignedIntFib getNumberOfDimensions() const;

	/**
	 * This method returns in which direction the iDimensionNumber dimension
	 * is mapped.
	 *
	 * @param iDimensionNumber the number of the dimension for which the
	 * 	mapping is to be returned
	 * @return the direction in which the iDimensionNumber dimension is
	 * 	mapped
	 */
	virtual unsignedIntFib getDimensionMapping( unsignedIntFib iDimensionNumber ) const;

	/**
	 * @return this method returns true if this Fib-element is an
	 * 	branchelement, alse false
	 */
	virtual bool isBranch() const;

	/**
	 * @return this method returns true if this Fib-element is an
	 * 	limbelement, alse false
	 */
	virtual bool isLimb() const;

	/**
	 * @return this method returns true if this Fib-element is an
	 * 	leafelement, alse false
	 */
	virtual bool isLeaf() const;


protected:

#ifdef FEATURE_FAST_UPDATE
	
	/**
	 * This method is a helpmethod for getNumberOfElement() .
	 * Basicly it counts the number of Fib-elements of the given type befor
	 * the given Fib-element pLastFibElement .
	 *
	 * @see getNumberOfElement()
	 * @see getNumberOfElements()
	 * @param pLastFibElement a pointer to the Fib-element which called this
	 * 	method last
	 * @param cType the type of the Fib-elements, for which to evalue the count,
	 * 	if 'u' Fib-elements of all typs are counted
	 * @return the number of Fib-elements of the given type cType befor the
	 * 	given Fib-element pLastFibElement
	 */
	virtual unsignedIntFib getNumberOfElementUp( const cFibElement * pLastFibElement,
		const char cType ) const = 0;
	
	/**
	 * This method is a helpmethod for getNumberOfMovePoint() .
	 * Basicly it counts the number of move points befor the given
	 * Fib-element pLastFibElement .
	 *
	 * @see getNumberOfMovePoint()
	 * @see getNumberOfMovePoints()
	 * @param pLastFibElement a pointer to the Fib-element which called this
	 * 	method last
	 * @return the number of movepoints befor the given Fib-element pLastFibElement
	 */
	virtual unsignedIntFib getNumberOfMovePointUp(
		const cFibElement * pLastFibElement ) const = 0;
	
	/**
	 * This method returns the next Fib-element in the order of
	 * Fib-elements which is above the given fib element.
	 * This method is used, if the method @see getNextFibElement() reaches
	 * an leaf in the object tree.
	 *
	 * @see getNextFibElement()
	 * @param pLastFibElement the Fib-element relativ to which the next
	 * 	Fib-element should lay
	 * @return a pointer to the next Fib-element in the order of Fib-elements
	 *		or the NULL pointer if non such exists
	 */
	virtual cFibElement *getNextFibElementUp( const cFibElement * pLastFibElement ) = 0;

	/**
	 * This method returns the next Fib-element in the order of
	 * Fib-elements which is above the given fib element.
	 * This method is used, if the method @see getNextFibElement() reaches
	 * an leaf in the object tree.
	 *
	 * @see getNextFibElement()
	 * @param pLastFibElement the Fib-element relativ to which the next
	 * 	Fib-element should lay
	 * @param cType the type of the Fib-element to return
	 * @return a pointer to the next Fib-element in the order of Fib-elements
	 *		or the NULL pointer if non such exists
	 */
	virtual cFibElement * getNextFibElementUp( const cFibElement * pLastFibElement,
		char cType ) = 0;

	/**
	 * This method returns the lNumber'th Fib-element in the order of
	 * Fib-elements which is above the given Fib-element.
	 * This method is used, if the method @see getConstFibElement() reaches
	 * an leaf in the object tree.
	 *
	 * @see getConstFibElementUp()
	 * @param pLastFibElement the Fib-element relativ to which the next
	 * 	Fib-element should lay
	 * @param lNumber the number of the Fib-Element to return
	 * @return a pointer to the next Fib-element in the order of Fib-elements
	 *		or the NULL pointer if non such exists
	 */
	virtual cFibElement * getConstFibElementUp( const cFibElement * pLastFibElement,
		longFib lNumber ) const = 0;

	/**
	 * This method returns the lNumber'th Fib-element in the order of
	 * Fib-elements of the given type cTyp with the given type cTyp which is
	 * above the given Fib-element.
	 * This method is used, if the method @see getConstFibElement() reaches
	 * an leaf in the object tree.
	 *
	 * @see getConstFibElementUp()
	 * @param pLastFibElement the Fib-element relativ to which the next
	 * 	Fib-element should lay
	 * @param cType the type of the Fib-element to return
	 * @param lNumber the number of the Fib-Element to return
	 * @return a pointer to the next Fib-element in the order of Fib-elements
	 *		or the NULL pointer if non such exists
	 */
	virtual cFibElement * getConstFibElementUp( const cFibElement * pLastFibElement,
		char cType, longFib lNumber ) const = 0;

#endif //FEATURE_FAST_UPDATE

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
	virtual bool storeBit( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const = 0;
	
	/**
	 * This method restores this Fib-object from the TinyXml node where
	 * it is stored.
	 *
	 * @param pXmlNode a pointer to the TinyXml node the Fib-object is stored in
	 * @param outStatus An reference to an integervalue where the errorvalue
	 * 	can be stored to.
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid node
	 * 		- -2 loading error, invalid data in node
	 * 		- 1 loading warning, invalid data in node, error could be corrected
	 * 		- 2 loading warning, invalid data in node, maybe the loaded
	 * 			object is wrong
	 * @param liDefinedVariables a list with the defined variables for the
	 * 	to restore Fib-element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 * @return the readed Fib -object or the Nullpointer NULL, if reading
	 * 	was not possible
	 */
	static cFibElement * restoreXmlInternal( const TiXmlNode * pXmlNode,
		intFib &outStatus, list<cFibVariable*> & liDefinedVariables );

	/**
	 * This method restores a rootobject from the stream where it is
	 * stored in the compressed Fib-format.
	 * This method is for internal use only.
	 *
	 * @param iBitStream the stream where this rootobject is stored to in,
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
	 * @param pNextRoot the next higher root-element for the to restore
	 * 	Fib-elements, or the last restored root-element;
	 * 	if NULL the next Fib-element restored will be an root-element
	 * @return the readed rootobject or the Nullpointer NULL, if reading
	 * 	was not possible
	 */
	static cRoot * restoreRootInternal( cReadBits & iBitStream, intFib & outStatus,
			cRoot * pNextRoot );
	
	/**
	 * This method restores a (non root) Fib-object from the stream where it is
	 * stored in the compressed Fib -format.
	 * This method is for internal use only.
	 *
	 * @param iBitStream the stream where this Fib-object is stored to in,
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
	 * 	to restore Fib-element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 * @param validDomains the domains valid for restoring the Fib-elements
	 * @param pNextRoot the next higher root-element for the to restore
	 * 	Fib-elements, or the last restored root-element
	 * @return the readed Fib -object or the Nullpointer NULL, if reading
	 * 	was not possible
	 */
	static cFibElement * restoreInternal( cReadBits & iBitStream, intFib & outStatus,
			list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains,
			cRoot * pNextRoot );

#ifndef FEATURE_NO_REGISTER_NEW_FIB_
	/**
	 * With this method a new Fib-element in the Fib-Object is registert
	 * by the other Fib-elements in the Fib-Object.
	 *
	 * @param newFibElement the new Fib-element to register
	 * @param uINumberOfFibElement the number of the new Fib-element in the
	 * 	order of all Fib-Elements in the Fib-object
	 * @param bDirectionUp the direction in which the registration of the
	 * 	new Fib-element is performed in the Fib-object tree;
	 * 	from the position on which the new Fib-Element is added the
	 * 	method is called for both directions
	 * @return true if the registration was successfull, else false
	 */
	virtual bool registerNewFibElement( cFibElement *newFibElement,
		unsignedIntFib uINumberOfFibElement, bool bDirectionUp ) = 0;


	/**
	 * With this method a new part Fib-object in the Fib-Object is
	 * registert by the other Fib-elements in the Fib-Object.
	 *
	 * @param newfibObject the new part Fib-object to register
	 * @param uILowerNumberOfFibElements the number of the Fib-element in the
	 * 	new part Fib-object with the lowest number in the order of all
	 * 	Fib-Elements in the entire Fib-object
	 * @param uIUpperNumberOfFibElements the number of the Fib-element in the
	 * 	new part Fib-object with the highest number in the order of all
	 * 	Fib-Elements in the entire Fib-object
	 * @param bDirectionUp the direction in which the registration of the
	 * 	new part Fib-object is performed in the Fib-object tree;
	 * @return true if the registration was successfull, else false
	 */
	virtual bool registerNewFibObject( cFibElement *newfibObject,
		unsignedIntFib uILowerNumberOfFibElements,
		unsignedIntFib uIUpperNumberOfFibElements, bool bDirectionUp ) = 0;
#endif //FEATURE_NO_REGISTER_NEW_FIB_

	/**
	 * This method updates the values/ properties off all Fib-elements in
	 * the whool Fib-object this Fib-element is part of.
	 *
	 * The highest Fib-element needs to be reachebel from this 
	 * Fib-element and every subobject should have all it's subobjects.
	 */
	virtual bool updateAllValues();


#ifdef FEATURE_FAST_UPDATE

	/**
	 * This method cuts the connections of this Fib-element to the
	 * given Fib-element.
	 *
	 * @param pFibElement the Fib-element to which to cut the connection
	 */
	virtual void cutConnectionsTo( const cFibElement * pFibElement );
	
	/**
	 * This method returns the number of the next connected object point
	 * in the order of connected object points that conntains the given
	 * Fib-element pLastFibElement.
	 *
	 * @param pLastFibElement a point to the Fib-elements for which the
	 * 	connected object point is to return
	 * @see getNumberOfObjectPoint()
	 * @see getNumberOfObjectPoints()
	 * @return the number of the next connected object point for the given
	 * 	Fib-element
	 */
	virtual unsignedIntFib getNumberOfObjectPointUp(
		const cFibElement * pLastFibElement ) const;
	
	/**
	 * This method returns the numbers of all object points that contain the
	 * elementPoint Fib -element.
	 *
	 * @see getNumberOfElement()
	 * @see getNumberOfElements()
	 * @see getNumberOfObjectPoint()
	 * @see getNumberOfObjectPoints()
	 * @see getType()
	 * @param pLastFibElement a point to the Fib-elements for which the
	 * 	connected object points are to return
	 * @param pFirstFibElement the Fib-element for which this method was
	 * 	called ( the reference Fib-element)
	 * @return a list of the numbers of all object points that contain the
	 * 	elementPoint Fib -element of the type cType
	 */
	virtual list<unsignedIntFib> elementPointToObjectPointsUp(
		const cFibElement * pLastFibElement,
		const cFibElement * pFirstFibElement ) const;

#else //FEATURE_FAST_UPDATE

	/**
	 * This method cuts the connections of this Fib-element to other
	 * Fib-elements.
	 *
	 * @param direction the direction into which the connections are to be
	 * 	cutted
	 * 	ED_HIGHER, ED_HIGHER_EQUAL, ED_ALL: will cut the conection to
	 * 		superior and previous Fib-elements
	 * 	ED_BELOW, ED_BELOW_EQUAL, ED_ALL: will cut the conection to
	 * 		next- Fib-element and the subobjects
	 */
	virtual void cutConnections( edDirection direction=ED_ALL );

	/**
	 * This method updates the values/ properties off all Fib-elements in
	 * this Fib-object beginning with this Fib-element.
	 * Every subobject should have all it's subobjects.
	 *
	 * @param previosFibElement the prvios Fib-element to this Fib-element
	 * 	in the order of Fib-elements; if it is NULL ther is no previos
	 * 	Fib-element to this
	 * @param pNextArm the next arm Fib-object in the next higher
	 * 	Fib-brancheelement
	 * @return a pointer to the last evalued Fib-element;
	 * 	if NULL an error has occured
	 */
	virtual cFibElement* updateValues( cFibElement * previosFibElement=NULL,
		cFibElement * pNextArm=NULL );
	
	/**
	 * This method returns the number of the next connected object point
	 * in the order of connected object points that conntains this fib
	 * -element.
	 *
	 * @param uINumberOfStartFibElement the number, in the order of all
	 * 	Fib-elements, of the Fib-element for which the connected object
	 * 	point is to return
	 * @see getNumberOfObjectPoint
	 * @see getNumberOfObjectPoints()
	 * @return the number of the next connected object point for this fib 
	 * 	-element
	 */
	virtual unsignedIntFib getNumberOfObjectPoint(
		unsignedIntFib uINumberOfStartFibElement ) const;

	/**
	 * This method returns the numbers of all object points that contain the
	 * elementPoint Fib-element of the type cType.
	 *
	 * @see elementPointToObjectPoints()
	 * @see getNumberOfElement()
	 * @see getNumberOfElements()
	 * @see getNumberOfObjectPoint()
	 * @see getNumberOfObjectPoints()
	 * @see getType()
	 * @param referencefibObject the Fib-element for which the object points
	 * 	are to returned
	 * @param uiLastObjectPoint the number of the last object point to the
	 * 	referencefibObject
	 * @return a list of the numbers of all object points that contain the
	 * 	elementPoint Fib-element of the type cType
	 */
	virtual list<unsignedIntFib> elementPointToObjectPoints(
			const cFibElement *referencefibObject,
			const unsignedIntFib uiLastObjectPoint  ) const;

#endif //FEATURE_FAST_UPDATE


	/**
	 * This method sets the each variable, which is defined over an leaf,
	 * to an uniqe integer number greater than the given number
	 * uiLastVariableNumber. While storing this number can be stored to
	 * identify the variable.
	 *
	 * @param uiLastVariableNumber the number which was last use, this
	 * 	means also is the greatest used, in this limb.
	 * @return the number which was last use, this
	 * 	means also is the greatest used, in this limb
	 * 	from the method
	 */
	virtual unsignedIntFib enumerateVariablesForStoring(
		unsignedIntFib uiLastVariableNumber = 0 ) = 0;


#ifndef SWITCH_JUST_STORE_AND_EVALUE
		
	/**
	 * This method moves a Fib-limb -element (cFibLimb) on the specified
	 * position over uiHowfar Fib-elements up.
	 * Moving is stoped if an invalid Fib-object would result (e.g. no fib
	 * -element can be moved over an Fib-elements that defines a variable
	 * the moved Fib-element uses).
	 * Moving an Fib-element into an listelement will result in an
	 * listelement with the moved element in everyone of it's subobjects.
	 *
	 * @see moveLimbElement()
	 * @see isDeletableElement()
	 * @see removeElement()
	 * @see getType()
	 * @param cType the type of the Fib-element to move
	 * @param elementPoint the number of the Fib-element, in the order of
	 * 	Fib-elements of the given type cType, to move
	 * @param uiHowfar the number of Fib-elements over which the to move
	 * 	Fib-element should be moved up
	 * @param bAbsolute if the elementPoint is an absolute value for the wool
	 * 	Fib-object
	 * @return the number of Fib-Elements over which the to move fib
	 * 	-element was moved
	 */
	intFib moveLimbElementUp( const char cType = 'u', const unsignedIntFib 
		elementPoint = 0, const unsignedIntFib uiHowfar=1, bool bAbsolute=false );

#endif //SWITCH_JUST_STORE_AND_EVALUE
	
	/**
	 * This method copies the connected object with the given number in the
	 * order of connected objects.
	 * For this every Fib-element, beginning from this Fib-element, that
	 * is part of the connected object will be copied.
	 * Variables which are not defined in the connected object but used
	 * don't change ther reference.
	 * It is an helpmethod for the copy method. It dosn't update the
	 * structural information of the created Fib-object.
	 *
	 * @param iObjectPoint the number of the connected object to copy;
	 * 	the standartvalue is 0 for coping the complet actual object
	 * @return the copy of the connected object or NULL if non such exists
	 */
	virtual cFibElement *copyInternal( const unsignedIntFib iObjectPoint=0 ) const = 0;

#ifndef SWITCH_JUST_STORE_AND_EVALUE
	
	/**
	 * This method returns a number of (lNumberOfMaxReturnedElements)
	 * Fib-elements beginning from the actual Fib-element in the
	 * given direction of the given type cType.
	 * The actual Fib-element will never be included in the returned list.
	 *
	 * @param cType the type of the Fib-elements to return;
	 * 	'w' stands for wrong/ not correct Fib-elements
	 * @param direction the direction, beginning from the reference 
	 * 	Fib-element, in which the to return Fib-elements should stand
	 * @param lNumberOfMaxReturnedElements the maximal number of 
	 * 	Fib-elements to return
	 * @return a list with the pointers to the to returning Fib-elements
	 */
	virtual list<cFibElement*> getAllFibElementsFromPosition( char cType,
		edDirection direction, unsignedLongFib lNumberOfMaxReturnedElements ) = 0;
	
#endif //SWITCH_JUST_STORE_AND_EVALUE
	
	/**
	 * @return the highest Fib-element in the wool Fib-object this
	 * 	Fib-element is part of
	 */
	cFibElement * getMasterRoot();

	/**
	 * @return the highest Fib-element in the wool Fib-object this
	 * 	Fib-element is part of
	 */
	cFibElement * getMasterRoot() const;

#ifndef SWITCH_JUST_STORE_AND_EVALUE
	
	/**
	 * This method checks if the given variable is defined in the given
	 * direction from this Fib-element.
	 * This is for intern use to get the correct data from
	 * isDefinedVariable() without pCallingFibElement.
	 *
	 * @see cFibVariable
	 * @see isUsedVariable()
	 * @param variable the variable to check if it is defined
	 * @param direction the direction from this Fib-element, in which the
	 * 	variable should be defined; standard value is ED_POSITION so yust
	 * 	this Fib-element will be checked
	 * @param pCallingFibElement the Fib-Element which called this method
	 * @return true if the variable is used, else false
	 */
	virtual bool isDefinedVariableInternal( const cFibVariable * variable,
		edDirection direction = ED_POSITION,
		const cFibElement * pCallingFibElement = NULL ) const = 0;
	
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
	 * 	variable should be used; standard value is ED_POSITION so yust
	 * 	this Fib-element will be checked
	 * @param pCallingFibElement the Fib-Element which called this method
	 * @return the set with all variables used in the given direction from
	 * 	this Fib-element
	 */
	virtual list< cFibVariable* > getDefinedVariablesInternal(
		edDirection direction = ED_HIGHER,
		const cFibElement * pCallingFibElement = NULL ) = 0;

#ifdef FEATURE_EQUAL_FIB_OBJECT

	/**
	 * This method checks if the given Fib-object is equal to this fib
	 * -object.
	 * Variables can be others, but must be defined and used in equivalent
	 * Fib-elements.
	 *
	 * @see equal()
	 * @see equalElementInternal
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
		const bool bCheckExternalObjects ) const = 0;

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
		const bool bCheckExternalObjects ) const = 0;


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


};//end class cFibElement


}//end namespace fib

#endif


