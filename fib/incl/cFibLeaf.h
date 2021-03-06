/**
 * @class cFibLeaf
 * file name: cFibLeaf.h
 * @author Betti Oesterholz
 * @date 26.11.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a Fib -element, which are leafs.
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
 * This file contains the basisclass of all Fib -elements, which are
 * leafs. Leafes can have no underobject.
 * It's not possible to create instances from this class.
 *
 * If the structur of the fib -object is changed just set the underobjects
 * and call updateAllValues() from a position wher the highest fib -element
 * can be reached. The updateAllValues()  method will make the conections.
 * If you remove conections you have to be more carefull.
 *
 */
/*
History:
26.11.2009  Oesterholz  created
06.01.2010  Oesterholz  getAllFibElements() uses now getAllFibElementsFromPosition()
07.08.2011  Oesterholz  isDefinedVariable() and getDefinedVariables() with
	pCallingFibElement
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
*/


#ifndef ___C_FIB_LEAF_H__
#define ___C_FIB_LEAF_H__

#include "version.h"
#include "fibDatatyps.h"

#include "cFibElement.h"
#include "cVectorPosition.h"
#include "cVectorProperty.h"
#include "cFibVariable.h"
#include "cDomains.h"

#include <list>
#include <ostream>
#include <istream>



using std::list;
using std::ostream;
using std::istream;

using namespace fib;

namespace fib{




class cFibLeaf: public cFibElement{
protected:


#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	
	/**
	 * parameterconstructor
	 *
	 * @param pInSuperiorElement the fib -Element in which this fib -element
	 * 	is the underobject
	 */
	cFibLeaf( cFibElement * pInSuperiorElement = NULL );

#else //FEATURE_SIMPLE_CONSTRUCTOR

	/**
	 * parameterconstructor
	 *
	 * @param pInSuperiorElement the fib -Element in which this fib -element
	 * 	is the underobject
	 * @param pInPreviousFibElement the fib -Element which stands in th order
	 * 	of Fib -elements befor this Fib -element
	 * @param pInNextFibElement the fib -Element which stands in th order
	 * 	of Fib -elements behind this Fib -element
	 */
	cFibLeaf( cFibElement * pInSuperiorElement = NULL,
		cFibElement * pInPreviousFibElement = NULL,
		cFibElement * pInNextFibElement = NULL );

#endif //FEATURE_SIMPLE_CONSTRUCTOR

	/**
	 * copyconstructor
	 * This copyconstructor constructs a copy of this Fib -Element.
	 * It dosn't copy other fib -elements than this, even if ther are in this
	 * fib -element.
	 *
	 * @param fibLeafElement the Fib -element to copy
	 */
	cFibLeaf( const cFibLeaf & fibLeafElement );


public:

	/**
	 * This method checks, if this fib -element is an valid fib -element.
	 *
	 * @return true if this fib -element is an valid fib -element, else false
	 */
	virtual bool isValidFibElement() const;
	
#ifdef FEATURE_FAST_UPDATE

	/**
	 * This method returns the next fib -element in the order of fib -elements.
	 *
	 * @return a pointer to the next fib -element in the order of fib -elements
	 *		or the NULL pointer if non such exists
	 */
	virtual cFibElement *getNextFibElement();

	/**
	 * This method returns the next fib -element in the order of 
	 * fib -elements with the given type cTyp.
	 *
	 * @param cType the type of the fib -element to return
	 * @return a pointer to the next fib -element in the order of 
	 * 	fib -elements with the given type or the NULL pointer if non such
	 * 	exists
	 */
	virtual cFibElement * getNextFibElement( char cType );

	/**
	 * This method returns the lNumber'th fib -element in the order of
	 * fib -elements.
	 *
	 * @param lNumber the number of the fib -Element to return
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	fib -object
	 * @return a pointer to the lNumber'th fib -element in the order of
	 * 	fib -elements or the NULL pointer if non such exists
	 */
	virtual cFibElement * getConstFibElement( longFib lNumber,
		bool bAbsolute=false ) const;

	/**
	 * This method returns the lNumber'th fib -element in the order of
	 * fib -elements of the given type cTyp with the given type cTyp.
	 *
	 * @param lNumber the number of the fib -element to return
	 * @param cType the type of the fib -element to return
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	fib -object
	 * @return a pointer to the lNumber'th fib -element in the order of
	 * 	fib -elements with the given type or the NULL pointer if non such
	 * 	exists
	 */
	virtual cFibElement * getConstFibElement( char cType, longFib lNumber,
		bool bAbsolute=false ) const;

#endif
	
	/**
	 * This method returns the number of subobjects in this Fib element.
	 * (e. g. limb elements have one subobject)
	 *
	 * @see getSubobject()
	 * @see getSubobjects()
	 * @return the number of subobjects in this Fib element
	 */
	virtual unsignedIntFib getNumberOfSubobjects() const;
	
	/**
	 * This method returns the uiNumberOfSubobject'th subobject of this
	 * Fib element.
	 *
	 * @see getNumberOfSubobjects()
	 * @see getSubobjects()
	 * @param uiNumberOfSubobject the number of the subobject to return
	 * @return a pointer to the uiNumberOfSubobject'th subobject of this
	 * 	Fib element, or the null pointer NULL if non exists
	 */
	virtual cFibElement * getSubobject( const unsignedIntFib uiNumberOfSubobject = 1 );
	
	/**
	 * This method returns the uiNumberOfSubobject'th subobject of this
	 * Fib element.
	 *
	 * @see getNumberOfSubobjects()
	 * @see getSubobjects()
	 * @param uiNumberOfSubobject the number of the subobject to return
	 * @return a pointer to the uiNumberOfSubobject'th subobject of this
	 * 	Fib element, or the null pointer NULL if non exists
	 */
	virtual const cFibElement * getSubobject(
		const unsignedIntFib uiNumberOfSubobject = 1 ) const;
	
	/**
	 * This method returns all subobjects of this Fib element.
	 *
	 * @see getNumberOfSubobjects()
	 * @see getSubobject()
	 * @return a list with all the subobjects of this Fib element
	 */
	virtual list< cFibElement * > getSubobjects();
	
	/**
	 * This method returns all subobjects of this Fib element.
	 *
	 * @see getNumberOfSubobjects()
	 * @see getSubobject()
	 * @return a list with all the subobjects of this Fib element
	 */
	virtual const list< cFibElement * > getSubobjects() const;
	
	
	/**
	 * This method checks if the given variable is used in the given
	 * direction from this Fib -element.
	 *
	 * @see cFibVariable
	 * @see isDefinedVariable()
	 * @param variable the variable to check if it is used
	 * @param direction the direction from this Fib -element, in which the
	 * 	variable should be used; standardvalue is ED_POSITION so yust
	 * 	this Fib -element will be checked
	 * @return true if the variable is used, else false
	 */
	virtual bool isUsedVariable( const cFibVariable *variable ,
		edDirection direction=ED_POSITION ) const;

	/**
	 * This method returns all variables used in the given direction from
	 * this Fib -element.
	 *
	 * @see cFibVariable
	 * @see isUsedVariable()
	 * @see isDefinedVariable()
	 * @param direction the direction from this Fib -element, in which the
	 * 	variable should be used; standardvalue is ED_POSITION so yust
	 * 	this Fib -element will be checked
	 * @return the set with all variables used in the given direction from
	 * 	this Fib -element
	 */
	virtual set<cFibVariable*> getUsedVariables( edDirection direction=ED_POSITION );


#ifdef FEATURE_FAST_UPDATE

	/**
	 * This method returns the number of this fib -element in the order of
	 * fib -Elements or order of fib -Elements of the same type if bOfType
	 * is true.
	 *
	 * @see getNumberOfElements()
	 * @param bOfType if true the returned number is the number the order
	 * 	of fib -elements of the same type as this fib -Element, else in
	 * 	the order of all fib -elements
	 * @return the number of this fib -element in the order of fib
	 * 	-Elements or order of fib -Elements of the same type if bOfType
	 * 	is true
	 */
	virtual unsignedIntFib getNumberOfElement( bool bOfType=false ) const;

	/**
	 * This method returns the number of this fib -element in the order of
	 * move points.
	 *
	 * @see getNumberOfMovePoints()
	 * @return the number of this fib -element in the order of move points
	 */
	virtual unsignedIntFib getNumberOfMovePoint() const;

#endif //FEATURE_FAST_UPDATE

	/**
	 * This method returns the number of Fib -elements of a type in this Fib
	 * -object.
	 *
	 * @see getType()
	 * @see getNumberOfElement()
	 * @param cType the character of the type ( @see getType() ), for which
	 * 	the elements should be counted; u (the standartvalue) stands for
	 * 	Fib -Elements of any type
	 * @return the number of Fib -elements of a type in the Fib -object
	 */
	virtual unsignedIntFib getNumberOfElements( char cType='u' ) const;

	/**
	 * This method returns the number of move points in this Fib -object.
	 *
	 * @see getNumberOfMovePoint()
	 * @return the number of move points in this Fib -object
	 */
	virtual unsignedIntFib getNumberOfMovePoints() const;

	/**
	* @return true if this fib -element is movebel else false
	*/
	virtual bool isMovable() const;

	/**
	 * This method returns the number of object points in this Fib -object.
	 *
	 * @see getNumberOfObjectPoint()
	 * @return the number of object points in this Fib -object
	 */
	virtual unsignedIntFib getNumberOfObjectPoints() const;

	/**
	 * This method returns the number of the Fib -element over wich the
	 * objectPoint object point is defined.
	 *
	 * @see getNumberOfElement()
	 * @see getNumberOfElements()
	 * @see getNumberOfObjectPoint()
	 * @see getNumberOfObjectPoints()
	 * @param uiObjectPoint the number of the object point for which the
	 * 	definig Fib -element number should be returned
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	fib -object
	 * @return the number of the Fib -element over wich the objectPoint
	 * 	object point is defined
	 */
	virtual unsignedIntFib objectPointToElementPoint( const unsignedIntFib
		uiObjectPoint, bool bAbsolute=false ) const;

	/**
	 * This method inserts the given Fib -element fibElement on the
	 * specified position. The replaced Fib -element will be the underobject
	 * of the inserted Fib -element fibElement.
	 *
	 * @see getNumberOfElement()
	 * @see getNumberOfElements()
	 * @see getType()
	 * @param cType the type of the Fib -element insted of which the given
	 * 	Fib -element fibElement should be inserted
	 * @param elementPoint the number of the Fib -element, in the order of
	 * 	Fib -elements of the given type cType, in which position the given
	 * 	Fib -element fibElement should be inserted; if 0 the given
	 * 	fibElement will be inserted under this Fib -element
	 * @param fibElement the Fib -element to insert
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	fib -object
	 * @param bCheckVariables if true (standardvalue) it will be checked if
	 * 	the variables the fib -element defines are needed, else the 
	 * 	fib -element will be removed even if its variables are needed elsewher
	 * @return true if the Fib -element fibElement was inserted, else false
	 */
	virtual bool insertElement( cFibElement *fibElement, const char cType='u',
		const unsignedIntFib elementPoint=0, bool bAbsolute=false,
		bool bCheckVariables=true );

	/**
	 * This method inserts the given Fib -object fibObject on the
	 * specified position. On the specified position a listelement will
	 * be inserted, with the old Fib -object and the given Fib -object
	 * fibObject as its underobjects.
	 *
	 * @see getNumberOfElement()
	 * @see getNumberOfElements()
	 * @see overwriteObjectWithObject()
	 * @see getType()
	 * @param cType the type of the Fib -element, on which position the 
	 * 	given Fib -object fibObject should be inserted
	 * @param elementPoint the number of the Fib -element, in the order of
	 * 	Fib -elements of the given type cType, on which position the given
	 * 	Fib -object fibObject should be inserted
	 * @param fibObject the Fib -object to insert
	 * @param first if true, the inserted object will be the first
	 * 	underobject of the new listelement
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	fib -object
	 * @return true if the Fib -object fibObject was inserted, else false
	 */
	virtual bool insertObjectInElement( cFibElement *fibObject, const char cType='u',
		const unsignedIntFib elementPoint=0, bool first=true, 
		bool bAbsolute=false );

	/**
	 * This method overwrites the Fib -object on specified position with
	 * the given Fib -object fibObject. The Fib -object on specified
	 * position will be replaced with the given Fib -object fibObject.
	 *
	 * @see getNumberOfElement()
	 * @see getNumberOfElements()
	 * @see insertObjectInElement()
	 * @see getType()
	 * @param cType the type of the Fib -element, on which position the 
	 * 	given Fib -object fibObject should be inserted
	 * @param elementPoint the number of the Fib -element, in the order of
	 * 	Fib -elements of the given type cType, on which position the given
	 * 	Fib -object fibObject should be inserted
	 * @param fibObject the Fib -object to insert
	 * @param bDeleteOld if true, delete the old Fib -object from the memory
	 * @param bAbsolute if the elementPoint is an absolute value for the wool
	 * 	fib -object
	 * @return true if the old Fib -object was overwritten and the given 
	 * 	Fib -object fibObject was inserted, else false
	 */
	virtual bool overwriteObjectWithObject( cFibElement *fibObject, const char cType='u',
		const unsignedIntFib elementPoint=0, bool bDeleteOld=true,
		bool bAbsolute=false );

	/**
	 * This method removes the connected object with the given number in
	 * the order of connected object points.
	 * For this the defining underobject in an listelement will be removed.
	 * If the listelement contains after the operation yust one underobject,
	 * the listelement will be replaced with the underobject.
	 *
	 * @param objectPoint the number of the connected object to remove
	 * @param bDeleteOld if true, delete the connected object from the
	 * 	memory, else yust remove it's pointers
	 * @param bAbsolute if the objectPoint is an absolute value for the wool
	 * 	fib -object
	 * @return true if the connected Fib -object was removed, else false
	 */
	virtual bool removeObject( const unsignedIntFib objectPoint,
		bool bDeleteOld=true, bool bAbsolute=false );

	/**
	 * This method checks, if all Fib -elements of this Fib -object
	 * have the underobjects they need to be correct.
	 *
	 * @return true if all Fib -elements of this Fib -object have the
	 * 	underobjects they need to be correct, else false
	 */
	virtual bool hasUnderAllObjects( ) const;

	/**
	 * This method checks, if the Fib -element on the specified position
	 * is deletable.
	 * An deletable Fib -element doesn't make the Fib -object invalid if
	 * it is deleted (e.g. points- and listelements are never deletable).
	 *
	 * @see removeElement()
	 * @see cutElement()
	 * @see getType()
	 * @param cType the type of the Fib -element to check
	 * @param elementPoint the number of the Fib -element, in the order of
	 * 	Fib -elements of the given type cType, to check
	 * @param bAbsolute if the elementPoint is an absolute value for the wool
	 * 	fib -object
	 * @param bCheckVariables if true (standardvalue) it will be checked if
	 * 	the variables the fib -element defines are needed, else the 
	 * 	fib -element will be removed even if its variables are needed elsewher
	 * @return true if the Fib -element is deletable, else false
	 */
	virtual bool isRemovableElement( const char cType='u', const unsignedIntFib
		elementPoint=0, bool bAbsolute=false, bool bCheckVariables=true ) const;

	/**
	 * This method cuts the Fib -element on the specified position.
	 * This works like removeElement(), except that the removed element is 
	 * returned.
	 *
	 * @see isDeletableElement()
	 * @see removeElement()
	 * @see getType()
	 * @param cType the type of the Fib -element to cut
	 * @param elementPoint the number of the Fib -element, in the order of
	 * 	Fib -elements of the given type cType, to cut
	 * @param bAbsolute if the elementPoint is an absolute value for the wool
	 * 	fib -object
	 * @param bCheckVariables if true (standardvalue) it will be checked if
	 * 	the variables the fib -element defines are needed, else the 
	 * 	fib -element will be removed even if its variables are needed elsewher
	 * @return the pointer to the cuted Fib -element or NULL, if the Fib
	 * 	-element couldn't cut
	 */
	virtual cFibElement *cutElement( const char cType='u', const unsignedIntFib
		elementPoint=0, bool bAbsolute=false, bool bCheckVariables=true );

#ifdef FEATURE_FAST_UPDATE
	/**
	 * This method deletes this given fib -object with all the fib
	 * elements it contains and is contained in. The memory for the fib
	 * -object is freed.
	 */
	virtual void deleteObject();
#endif //FEATURE_FAST_UPDATE

	/**
	 * This method moves a Fib -limb -element (cFibLimb) on the specified
	 * position over iHowfar Fib -elements.
	 * Moving is stoped if an invalid Fib -object would result (e.g. no Fib
	 * -element can be moved over an Fib -elements that defines a variable
	 * the moved Fib -element uses).
	 * Moving an Fib -element into an listelement will result in an
	 * listelement with the moved element in everyone of it's underobjects.
	 *
	 * @see isDeletableElement()
	 * @see removeElement()
	 * @see getType()
	 * @param cType the type of the Fib -element to move
	 * @param elementPoint the number of the Fib -element, in the order of
	 * 	Fib -elements of the given type cType, to move
	 * @param iHowfar the number of Fib -elements over which the to move
	 * 	Fib -element should be moved; if this value is positiv the Fib
	 * 	-element will be moved over Fib -elements it contains else over
	 * 	Fib -elements it is contained in
	 * @param bAbsolute if the elementPoint is an absolute value for the wool
	 * 	fib -object
	 * @return the number of Fib -Elements over which the to move Fib
	 * 	-element was moved; if this value is positiv the Fib -element
	 * 	was moved over Fib -elements it contains else over Fib -elements
	 * 	it is contained in
	 */
	virtual intFib moveLimbElement( const char cType='u', const unsignedIntFib 
		elementPoint=0, const intFib iHowfar=1, bool bAbsolute=false );

#ifndef FEATURE_EQUAL_FIB_OBJECT

	/**
	 * This method checks if the given Fib -object is equal to this Fib
	 * -object.
	 * Variables can be others, but must be defined and aused in equivalent
	 * Fib -elements.
	 *
	 * @param fibObject the Fib -object to which this Fib -object should be
	 * 	equal
	 * @return true if this Fib -object is equal to the given Fib -object,
	 * 	else false
	 */
	virtual bool equal( const cFibElement & fibObject ) const;

#endif //FEATURE_EQUAL_FIB_OBJECT

	/**
	 * @return this method returns true if this fib -element is an
	 * 	leafelement, alse false
	 */
	virtual bool isLeaf() const;

protected:

#ifdef FEATURE_FAST_UPDATE
	
	/**
	 * This method is a helpmethod for getNumberOfElement() .
	 * Basicly it counts the number of fib -elements of the given type befor
	 * the given fib -element pLastFibElement .
	 *
	 * @see getNumberOfElement()
	 * @see getNumberOfElements()
	 * @param pLastFibElement a pointer to the fib -element which called this
	 * 	method last
	 * @param cType the type of the fib -elements, for which to evalue the count,
	 * 	if 'u' fib -elements of all typs are counted
	 * @return the number of fib -elements of the given type cType befor the
	 * 	given fib -element pLastFibElement
	 */
	virtual unsignedIntFib getNumberOfElementUp( const cFibElement * pLastFibElement,
		const char cType ) const;
	
	/**
	 * This method is a helpmethod for getNumberOfMovePoint() .
	 * Basicly it counts the number of move points befor the given
	 * fib -element pLastFibElement .
	 *
	 * @see getNumberOfMovePoint()
	 * @see getNumberOfMovePoints()
	 * @param pLastFibElement a pointer to the fib -element which called this
	 * 	method last
	 * @return the number of movepoints befor the given fib -element pLastFibElement
	 */
	virtual unsignedIntFib getNumberOfMovePointUp(
		const cFibElement * pLastFibElement ) const;
	
	/**
	 * This method returns the next fib -element in the order of
	 * fib -elements which is above the given fib element.
	 * This method is used, if the method @see getNextFibElement() reaches
	 * an leaf in the object tree.
	 *
	 * @see getNextFibElement()
	 * @param pLastFibElement the fib -element relativ to which the next
	 * 	fib -element should lay
	 * @return a pointer to the next fib -element in the order of fib -elements
	 *		or the NULL pointer if non such exists
	 */
	virtual cFibElement * getNextFibElementUp( const cFibElement * pLastFibElement );

	/**
	 * This method returns the next fib -element in the order of
	 * fib -elements which is above the given fib element.
	 * This method is used, if the method @see getNextFibElement() reaches
	 * an leaf in the object tree.
	 *
	 * @see getNextFibElement()
	 * @param pLastFibElement the fib -element relativ to which the next
	 * 	fib -element should lay
	 * @param cType the type of the fib -element to return
	 * @return a pointer to the next fib -element in the order of fib -elements
	 *		or the NULL pointer if non such exists
	 */
	virtual cFibElement * getNextFibElementUp( const cFibElement * pLastFibElement,
		char cType );

	/**
	 * This method returns the lNumber'th fib -element in the order of
	 * fib -elements which is above the given fib -element.
	 * This method is used, if the method @see getConstFibElement() reaches
	 * an leaf in the object tree.
	 *
	 * @see getConstFibElementUp()
	 * @param pLastFibElement the fib -element relativ to which the next
	 * 	fib -element should lay
	 * @param lNumber the number of the fib -Element to return
	 * @return a pointer to the next fib -element in the order of fib -elements
	 *		or the NULL pointer if non such exists
	 */
	virtual cFibElement * getConstFibElementUp( const cFibElement * pLastFibElement,
		longFib lNumber ) const;

	/**
	 * This method returns the lNumber'th fib -element in the order of
	 * fib -elements  of the given type cTyp with the given type cTyp
	 * which is above the given fib -element.
	 * This method is used, if the method @see getConstFibElement() reaches
	 * an leaf in the object tree.
	 *
	 * @see getConstFibElementUp()
	 * @param pLastFibElement the fib -element relativ to which the next
	 * 	fib -element should lay
	 * @param cType the type of the fib -element to return
	 * @param lNumber the number of the fib -Element to return
	 * @return a pointer to the next fib -element in the order of fib -elements
	 *		or the NULL pointer if non such exists
	 */
	virtual cFibElement * getConstFibElementUp( const cFibElement * pLastFibElement,
		char cType, longFib lNumber ) const;

#endif //FEATURE_FAST_UPDATE

#ifndef FEATURE_NO_REGISTER_NEW_FIB_
	/**
	 * With this method a new Fib -element in the Fib -Object is registert
	 * by the other Fib -elements in the Fib -Object.
	 *
	 * @param newFibElement the new Fib -element to register
	 * @param uINumberOfFibElement the number of the new Fib -element in the
	 * 	order of all Fib -Elements in the Fib -object
	 * @param bDirectionUp the direction in which the registration of the
	 * 	new Fib -element is performed in the Fib -object tree;
	 * 	from the position on which the new Fib -Element is added the
	 * 	method is called for both directions
	 * @return true if the registration was successfull, else false
	 */
	virtual bool registerNewFibElement( cFibElement *newFibElement,
		unsignedIntFib uINumberOfFibElement, bool bDirectionUp );


	/**
	 * With this method a new part Fib -object in the Fib -Object is
	 * registert by the other Fib -elements in the Fib -Object.
	 *
	 * @param newFibObject the new part Fib -object to register
	 * @param uILowerNumberOfFibElements the number of the Fib -element in the
	 * 	new part Fib -object with the lowest number in the order of all
	 * 	Fib -Elements in the entire Fib -object
	 * @param uIUpperNumberOfFibElements the number of the Fib -element in the
	 * 	new part Fib -object with the highest number in the order of all
	 * 	Fib -Elements in the entire Fib -object
	 * @param bDirectionUp the direction in which the registration of the
	 * 	new part Fib -object is performed in the Fib -object tree;
	 * @return true if the registration was successfull, else false
	 */
	virtual bool registerNewFibObject( cFibElement *newFibObject,
		unsignedIntFib uILowerNumberOfFibElements,
		unsignedIntFib uIUpperNumberOfFibElements, bool bDirectionUp );
#endif //FEATURE_NO_REGISTER_NEW_FIB_

#ifndef FEATURE_FAST_UPDATE
	
	/**
	 * This method updates the values/ properties off all fib -elements in
	 * this fib -object beginning with this fib -element.
	 * Every underobject should have all it's underobjects.
	 *
	 * @param previosFibElement the prvios fib -element to this fib -element
	 * 	in the order of fib -elements; if it is NULL ther is no previos
	 * 	fib -element to this
	 * @param pNextArm the next arm fib -object in the next higher
	 * 	fib -brancheelement
	 * @return a pointer to the last evalued fib -element;
	 * 	if NULL an error has occured
	 */
	virtual cFibElement* updateValues( cFibElement * previosFibElement=NULL,
		cFibElement * pNextArm=NULL );

	/**
	 * This method returns the number of the next connected object point
	 * in the order of connected object points that conntains this Fib
	 * -element.
	 *
	 * @param uINumberOfStartFibElement the number, in the order of all
	 * 	fib -elements, of the fib -element for which the connected object
	 * 	point is to return
	 * @see getNumberOfObjectPoint
	 * @see getNumberOfObjectPoints()
	 * @return the number of the next connected object point for this Fib 
	 * 	-element
	 */
	virtual unsignedIntFib getNumberOfObjectPoint(
		unsignedIntFib uINumberOfStartFibElement ) const;

	/**
	 * This method returns the numbers of all object points that contain the
	 * elementPoint Fib -element.
	 *
	 * @see elementPointToObjectPoints()
	 * @see getNumberOfElement()
	 * @see getNumberOfElements()
	 * @see getNumberOfObjectPoint()
	 * @see getNumberOfObjectPoints()
	 * @see getType()
	 * @param referenceFibObject the fib -element for which the object points
	 * 	are to returned
	 * @param uiLastObjectPoint the number of the last object point to the
	 * 	referenceFibObject
	 * @return a list of the numbers of all object points that contain the
	 * 	elementPoint Fib -element of the type cType
	 */
	virtual list<unsignedIntFib> elementPointToObjectPoints(
			const cFibElement *referenceFibObject,
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
		unsignedIntFib uiLastVariableNumber = 0 );

	/**
	 * This method returns a number of (lNumberOfMaxReturnedElements)
	 * Fib -elements beginning from the actual Fib -element in the
	 * given direction of the given type cType.
	 * The actual fib -element will never be included in the returned list.
	 *
	 * @param cType the type of the Fib -elements to return;
	 * 	'w' stands for wrong/ not correct fib -elements
	 * @param direction the direction, beginning from the reference 
	 * 	Fib -element, in which the to return Fib -elements should stand
	 * @param lNumberOfMaxReturnedElements the maximal number of 
	 * 	Fib -elements to return
	 * @return a list with the pointers to the to returning Fib -elements
	 */
	virtual list<cFibElement*> getAllFibElementsFromPosition( char cType,
		edDirection direction, unsignedLongFib lNumberOfMaxReturnedElements );

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

#endif //FEATURE_EQUAL_FIB_OBJECT

};//end class cFibLeaf


}//end namespace fib

#endif


