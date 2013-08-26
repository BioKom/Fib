/**
 * @class cPoint
 * file name: cPoint.h
 * @author Betti Oesterholz
 * @date 26.11.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the point -Fib element.
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
 * This class represents the pointelement of the Fib multimedialanguage.
 * It represents the position on which the properties, from higer in this
 * Fib limb, should be.
 * If the positionsvector of the point is empty. the properties are for
 * the background. If ther is no positionsvector the properties are discarded.
 *
 */
/*
History:
26.11.2009  Oesterholz  created
18.04.2010  Oesterholz  evalueObject() methods changed: not a function but
	an object is given to evalue the data
08.03.2011  Oesterholz  method for const getPosition() added
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
30.07.2013  Oesterholz  method assignValues() added
*/

#ifndef ___C_POINT_H__
#define ___C_POINT_H__


#include "version.h"

#include "fibDatatyps.h"

#include "cFibLeaf.h"
#include "cRoot.h"
#include "cVectorPosition.h"


namespace fib{


class cPoint: public cFibLeaf{

friend class cFibElement;

private:

	/**
	 * The positionsvector for this point.
	 * If NULL this point has no positionsvector, all properties will be
	 * discarded.
	 */
	cVectorPosition * pVectorPosition;

public:

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	
	/**
	 * parameterconstructor
	 *
	 * @param pInVectorPosition a pointer to the positionsvector for the
	 * 	point or NULL if the point shouldn'd have a positionsvector
	 * @param pInSuperiorelement the Fib element in which this
	 * 	point -element is an underobject
	 */
	cPoint( const cVectorPosition * pInVectorPosition = NULL,
		cFibElement * pInSuperiorelement = NULL );
	
#else //FEATURE_SIMPLE_CONSTRUCTOR
	
	/**
	 * parameterconstructor
	 *
	 * @param pInVectorPosition a pointer to the positionsvector for the
	 * 	point ore NULL if the point shouldn'd have a positionsvector
	 * @param pInSuperiorelement the Fib element in which this
	 * 	point -element is an underobject
	 * @param pInPreviousFibElement the Fib element which stands in th order
	 * 	of Fib elements befor this Fib element
	 * @param pInNextFibElement the Fib element which stands in th order
	 * 	of Fib elements after this Fib element
	 */
	cPoint( const cVectorPosition * pInVectorPosition = NULL,
		cFibElement * pInSuperiorelement = NULL,
		cFibElement * pInPreviousFibElement = NULL,
		cFibElement * pInNextFibElement = NULL );

#endif //FEATURE_SIMPLE_CONSTRUCTOR

	/**
	 * copyconstructor
	 * This copyconstructor constructs a copy of the given point -element.
	 * It dosn't copy other point -elements than the given, even if ther are
	 * in the point -element.
	 *
	 * @param pointelement the point -element to copy
	 */
	cPoint( const cPoint &pointelement );

protected:

	/**
	 * The constructor for restoring a pointelement from an TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node wher the Fib object is stored in
	 * @param outStatus An reference to an integervalue where the errorvalue
	 * 	can be stored to.
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlelement
	 * 		- -2 loading error, invalid data in pXmlelement
	 * 		- 1 loading warning, invalid data in pXmlelement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlelement, maybe the loaded
	 * 			object is wrong
	 * @param liDefinedVariables a list with the defined variables for the
	 * 	to restore Fib element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 */
	cPoint( const TiXmlElement * pXmlelement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables );

	/**
	 * This constructor restores a pointelement from the stream where it is
	 * stored in the compressed Fib format.
	 * This method is for internal use only.
	 *
	 * @param iBitStream the stream where this pointelement is stored to in,
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
	 * 	to restore Fib element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 * @param validDomains the domains valid for restoring the Fib elements
	 */
	cPoint( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains );

public:

	/**
	 * desstructor
	 */
	virtual ~cPoint();


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
	 * Ever pointelement is given back. The type chars for pointelements
	 * don't need to be in the list liCFibElementTyps.
	 *
	 * @param evalueFibElement a reference to the object with the
	 * 	evalueelement() method to evalue /store the Fib elements and ther
	 * 	properties; everytime a Fib element (with one of the type given
	 * 	in liCFibElementTyps) is reached in the evaluation, the method
	 * 	evalueelement() of this objects is called with the Fib element
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
	 * The optionalpart field of point -elements will be ignored.
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
	 * @param variable the variable to check if it is used
	 * @param direction the direction from this Fib element, in which the
	 * 	variable should be used; standardvalue is ED_POSITION so yust
	 * 	this Fib element will be checked
	 * @return true if the variable is used, else false
	 */
	virtual bool isUsedVariable( const cFibVariable *variable ,
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
	 * @param variableOld the variable to replace
	 * @param variableNew the variable with which the variable variableOld
	 * 	is to replace
	 * @return true if the variable variableOld is replaced with variableNew,
	 * 	else false
	 */
	virtual bool replaceVariable( cFibVariable *variableOld,
		cFibVariable *variableNew );

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
	 * This method checks if the given Fib object is equal to this Fib
	 * -object.
	 * Variables can be others, but must be defined and used in equivalent
	 * Fib elements.
	 *
	 * @param fibObject the Fib object to which this Fib object should be
	 * 	equal
	 * @return true if this Fib object is equal to the given Fib object,
	 * 	else false
	 */
	virtual bool equal( const cFibElement & fibObject ) const;
	
	/**
	 * This method checks if the given Fib element is equal to this fib
	 * -element.
	 * The underobjects arn't compared, not even ther count is compared.
	 * Used variables can be others.
	 *
	 * @param fibelement the Fib element to which this Fib element should be
	 * 	equal
	 * @return true if this Fib element is equal to the given Fib object,
	 * 	else false
	 */
	virtual bool equalelement( const cFibElement & fibelement ) const;
	
#endif // FEATURE_EQUAL_FIB_OBJECT

	/**
	 * This method stores this Fib object in the XML -format into the
	 * given stream.
	 *
	 * @param stream the stream where this Fib object should be stored to
	 * @return true if this Fib object is stored, else false
	 */
	virtual bool storeXml( ostream &stream ) const;



/*
 * Point -element methods
 */


	/**
	 * @return a pointer to the positionsvector of this pointelement or
	 * 	NULL if the point has no positionsvector
	 */
	virtual cVectorPosition * getPosition();

	/**
	 * @return a pointer to the positionsvector of this pointelement or
	 * 	NULL if the point has no positionsvector
	 */
	virtual const cVectorPosition * getPosition() const;

	/**
	 * This sets the positionsvector of this point.
	 * The given positionsvector is copied befor inserting it in this point.
	 * If the positionsvector of the point is empty. the properties are for
	 * the background.
	 * If ther is no positionsvector the properties are discarded at this point.
	 *
	 * @param vecPositon the positionsvector this point should have
	 */
	virtual void setPosition( const cVectorPosition *vecPositon=NULL );

protected:

	/**
	 * This method stores this Fib object in the compressed Fib format
	 * into the given stream.
	 * It is needed becouse the stream can yust store byts but the size of
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
	 * is part of the connected object will be copied.
	 * Variables which are not defined in the connected object but used
	 * don't change ther reference.
	 * It is an helpmethod for the copy method. It dosn't update the
	 * structural information of the created Fib object.
	 *
	 * @param iObjectPoint the number of the connected object to copy;
	 * 	the standartvalue is 0 for coping the complet actual object
	 * @return the copy of the connected object or NULL if non such exists
	 */
	virtual cFibElement *copyInternal( const unsignedIntFib iObjectPoint=0 ) const;
	
#ifdef FEATURE_EQUAL_FIB_OBJECT

	/**
	 * This method checks if the given Fib object is equal to this fib
	 * -object.
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
	 * 	cExtObject will be compared
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
	 * @param fibelement the Fib element to which this Fib element should be
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
	virtual bool equalElementInternal( const cFibElement & fibelement,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const;

#endif //FEATURE_EQUAL_FIB_OBJECT

};
}//namespace fib

#endif //___C_POINT_H__






