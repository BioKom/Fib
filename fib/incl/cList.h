/**
 * @class cList
 * file name: cList.h
 * @author Betti Oesterholz
 * @date 16.12.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the list -Fib -element.
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
 * This class represents the listelement of the Fib -multimedialanguage.
 * It represents a list of fib -objects.
 *
 */
/*
History:
16.12.2009  Oesterholz  created
18.04.2010  Oesterholz  evalueObject() methods changed: not a function but
	an object is given to evalue the data
05.09.2010  Oesterholz  replaceAllUnderobjects() added
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
30.07.2013  Oesterholz  method assignValues() added
*/

#ifndef ___C_LIST_H__
#define ___C_LIST_H__


#include "version.h"

#include "fibDatatyps.h"

#include "cFibBranch.h"


namespace fib{


class cList: public cFibBranch{

friend class cFibElement;

public:


#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	
	/**
	 * parameterconstructor
	 *
	 * @param pFibObject1 the fib -Element which is the first underobject of
	 * 	this list-lement (it also stands next in the order of fib -elements)
	 * @param pFibObject2 the fib -Element which is the secound underobject of
	 * 	this listelement
	 * @param pInSuperiorElement the fib -Element in which this
	 * 	list -element is an underobject
	 */
	cList( cFibElement * pFibObject1, cFibElement * pFibObject2,
		cFibElement * pInSuperiorElement = NULL );

	/**
	 * parameterconstructor
	 *
	 * @param liUnderObjects the list with the underobjects for the listelement
	 * @param pInSuperiorElement the fib -Element in which this
	 * 	list -element is an underobject
	 */
	cList( list< cFibElement * > liUnderObjects, cFibElement * pInSuperiorElement = NULL );

#else //FEATURE_SIMPLE_CONSTRUCTOR
	
	/**
	 * parameterconstructor
	 *
	 * @param pFibObject1 the fib -Element which is the first underobject of
	 * 	this list-lement (it also stands next in the order of fib -elements)
	 * @param pFibObject2 the fib -Element which is the secound underobject of
	 * 	this listelement
	 * @param pInSuperiorElement the fib -Element in which this
	 * 	list -element is an underobject
	 * @param pInPreviousFibElement the fib -Element which stands in th order
	 * 	of Fib -elements befor this Fib -element
	 */
	cList( cFibElement * pFibObject1, cFibElement * pFibObject2,
		cFibElement * pInSuperiorElement = NULL,
		cFibElement * pInPreviousFibElement = NULL );

#endif //FEATURE_SIMPLE_CONSTRUCTOR

	/**
	 * copyconstructor
	 * This copyconstructor constructs a copy of the given list -Element.
	 * It dosn't copy other list -elements than the given, even if ther are
	 * in the list -element.
	 *
	 * @param listElement the list -element to copy
	 */
	cList( const cList &listElement );

protected:

	/**
	 * The constructor for restoring a listobject from an TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node the wher fib -object is stored in
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
	 * 	to restore fib -element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 */
	cList( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables );

	/**
	 * This constructor restores a listobject from the stream where it is
	 * stored in the compressed fib -format.
	 * This method is for internal use only.
	 *
	 * @param iBitStream the stream wher this listobject is stored to in,
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
	 * 	to restore fib -element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 * @param validDomains the domains valid for restoring the fib -elements
	 * @param pNextRoot the next higher root -element for the to restore
	 * 	fib -elements, or the last restored root -element
	 * @param uiBitsForUnderobjectCount the number of bits of the count of
	 * 	the underobjects for the listelement
	 */
	cList( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains,
		cRoot * pNextRoot, unsignedIntFib uiBitsForUnderobjectCount = 0 );


public:

	/**
	 * @see getTypeName
	 * @return a character for the typ of the Fib -element
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
	 * This method checks, if this fib -element is an valid fib -element.
	 *
	 * @return true if this fib -element is an valid fib -element, else false
	 */
	virtual bool isValidFibElement() const;

	/**
	 * This method evaluades the fib -object.
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
	 * This method evaluades the fib -object.
	 * Evertime a fib -elements, with a type of the given type chars in
	 * liCFibElementTyps, is reached while evaluation, it is given
	 * back with the properties which it has.
	 * Ever pointelement is given back. The type chars for pointelements
	 * don't need to be in the list liCFibElementTyps.
	 *
	 * @param evalueFibElement a reference to the object with the
	 * 	evalueElement() method to evalue /store the fib -elements and ther
	 * 	properties; everytime a fib -element (with one of the type given
	 * 	in liCFibElementTyps) is reached in the evaluation, the method
	 * 	evalueElement() of this objects is called with the fib -element
	 * 	and the properties of the fib -element; @see iEvalueFibElement
	 * @param objectPoint the object point in the order of true partobjects
	 *		to evalue
	 * @param liVecProperties a list with the property vectors which should
	 * 	be global for the evalued object
	 * @param liCFibElementTyps a list with the type chars (@see getType)
	 * 	of the fib -elements to return
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
	 * This method checks, if all Fib -elements of this Fib -object
	 * have the underobjects they need to be correct.
	 *
	 * @return true if all Fib -elements of this Fib -object have the
	 * 	underobjects they need to be correct, else false
	 */
	virtual bool hasUnderAllObjects() const;

	/**
	 * This method evaluades the size of the Fib -object in bits in the
	 * compressed file form.
	 * The optionalpart field of list -elements will be ignored.
	 *
	 * @see store()
	 * @return the size of the Fib -object in bits in the compressed form
	 */
	virtual unsignedLongFib getCompressedSize() const;

	/**
	 * This method copies the Fib -element on the specified position.
	 * Variables which are not defined in the Fib -element but used
	 * don't change ther reference.
	 *
	 * @see getType()
	 * @param cType the type of the Fib -element to copy
	 * @param elementPoint the number of the Fib -element, in the order of
	 * 	Fib -elements of the given type cType, to copy
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	fib -object
	 * @return the copy of the fib -element
	 */
	virtual cFibElement *copyElement( const char cType='u', const unsignedIntFib
		elementPoint=0, bool bAbsolute=false ) const;

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
	 * This method checks if the given fib -element is equal to this fib
	 * -element.
	 * The underobjects arn't compared, not even ther count is compared.
	 * Used variables can be others.
	 *
	 * @param fibElement the fib -element to which this fib -element should be
	 * 	equal
	 * @return true if this fib -element is equal to the given fib -object,
	 * 	else false
	 */
	virtual bool equalElement( const cFibElement & fibElement ) const;

#endif //FEATURE_EQUAL_FIB_OBJECT

	/**
	 * This method stores this Fib -object in the XML -format into the
	 * given stream.
	 *
	 * @param stream the stream where this Fib -object should be stored to
	 * @return true if this Fib -object is stored, else false
	 */
	virtual bool storeXml( ostream &stream ) const;


/*
 * List -element methods
 */

	/**
	 * @return the number of underobjects of this listelement
	 */
	virtual unsignedIntFib getNumberOfUnderobjects() const;

	/**
	 * This method return the iNumberOfUnderobject'th underobject of this
	 * listelement.
	 *
	 * @param iNumberOfUnderobject the number of the underobject to return
	 * @return iNumberOfUnderobject'th underobject of this listelement or
	 * 	NULL, if non such exists
	 */
	virtual cFibElement * getUnderobject( unsignedIntFib iNumberOfUnderobject=1 );

	/**
	 * This method returns a number of underobjects from this listelement,
	 * beginning from a first underobject.
	 *
	 * @see getUnderobject()
	 * @param iNumberOfFirstUnderobject the number of the first underobject
	 * 	to return
	 * @param iNumberOfToReturnUnderobjects the number /count of underobjects
	 * 	to return; if 0 or greater equal the count of underobjects from
	 * 	first underobject, all underobjects to the listend  will be returned
	 * @return a list with the underobjects to return
	 */
	virtual list< cFibElement * > getUnderobjects(
		unsignedIntFib iNumberOfFirstUnderobject=1,
		unsignedIntFib iNumberOfToReturnUnderobjects=0 );

	/**
	 * This method adds the underobject pUnderobject on the given position
	 * iPosition to this listelement.
	 *
	 * @param pUnderobject a pointer to the underobject to add to the listelement
	 * @param iPosition the position on which to add the underobject, if
	 * 	this number is greater than the number of underobjects in the
	 * 	listelement, the underobject will be added to the end of the listelement
	 * @return true if the underobject was added, else false
	 */
	virtual bool addUnderobject( cFibElement * pUnderobject, unsignedIntFib iPosition=1 );

	/**
	 * This method adds the underobjects liUnderobjects on the given position
	 * iPosition to this listelement.
	 *
	 * @param liUnderobject the list with the pointers to the underobjects
	 * 	to add to the listelement
	 * @param iPosition the position on which to add the underobjects, if
	 * 	this number is greater than the number of underobjects in the
	 * 	listelement, the underobjects will be added to the end of the listelement
	 * @return the number of underobjects added
	 */
	virtual unsignedIntFib addUnderobjects( list<cFibElement*> liUnderobjects,
		unsignedIntFib iPosition=1 );

	/**
	 * This method deleted the underobject pUnderobject on the given
	 * position iPositionUnderobject from this listelement.
	 *
	 * @param iPositionUnderobject the position from which to delete the
	 * 	underobject
	 * @param bDeleteOld if true, delete the old Fib -object from the memory
	 * @return true if the underobject was deleted, else false
	 */
	virtual bool deleteUnderobject( unsignedIntFib iPositionUnderobject,
		bool bDeleteOld=true );
	
	
#ifdef FEATURE_FAST_UPDATE
	/**
	 * This method deletes a number of underobjects from this listelement,
	 * beginning from a first underobject.
	 *
	 * @see getUnderobject()
	 * @param iNumberOfFirstUnderobject the number of the first underobject
	 * 	to delete
	 * @param iNumberOfToDeleteUnderobjects the number /count of underobjects
	 * 	to delete; if 0 or greater equal the count of underobjects from
	 * 	first underobject, all underobjects to the listend  will be deleted
	 * @param bDeleteOld if true, delete the old fib -underobjects from the memory
	 * @return true if the underobject wher deleted, else false
	 */
	virtual bool deleteUnderobjects(
		unsignedIntFib iNumberOfFirstUnderobject=3,
		unsignedIntFib iNumberOfToDeleteUnderobjects=0, bool bDeleteOld=true );

	/**
	 * This method replaces all underobjects of this listelement with the
	 * given underobjects liUnderobjects.
	 *
	 * @param liUnderobject the list with the pointers to the underobjects,
	 * 	with which to replace the existing underobjects of the listelement
	 * @param bDeleteOld if true, delete the old fib -underobjects from the memory
	 * @return true if the replacing was successfull, else false
	 */
	virtual bool replaceAllUnderobjects( list<cFibElement*> liUnderobjects,
		bool bDeleteOld=true );
	
#endif //FEATURE_FAST_UPDATE


protected:

	/**
	 * This method stores this Fib -object in the compressed Fib -format
	 * into the given stream.
	 * It is needed becouse the stream can yust store byts but the size of
	 * fib -elements can be any number of bits. Because of that ther have to
	 * be a possibility to exchange the missing bits betwean the fib -elements.
	 * Beware: You need to call storeBit() of the root -elements with the
	 * domain for the list or the list will not be readebel.
	 *
	 * @see store
	 * @param stream the stream where this Fib -object should be stored to
	 * @param cRestBits the not yet writen bits which should be stored
	 * @param uiRestBitPosition the number of bits in the cRestBits which
	 * 	should be writen respectively containing valid information
	 * @return true if this Fib -object is stored, else false
	 */
	virtual bool storeBit( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const;

	/**
	 * This method copies the connected object with the given number in the
	 * order of connected objects.
	 * For this every Fib -element, beginning from this Fib -element, that
	 * is part of the connected object will be copied.
	 * Variables which are not defined in the connected object but used
	 * don't change ther reference.
	 * It is an helpmethod for the copy method. It dosn't update the
	 * structural information of the created fib -object.
	 *
	 * @param iObjectList the number of the connected object to copy;
	 * 	the standartvalue is 0 for coping the complet actual object
	 * @return the copy of the connected object or NULL if non such exists
	 */
	virtual cFibElement * copyInternal( const unsignedIntFib iObjectList=0 ) const;

#ifdef FEATURE_EQUAL_FIB_OBJECT

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

#endif //FEATURE_EQUAL_FIB_OBJECT

};
}//namespace fib

#endif






