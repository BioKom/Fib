/**
 * @class cComment
 * file name: cComment.h
 * @author Betti Oesterholz
 * @date 26.07.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the fib-commentelement.
 * Copyright (C) @c LGPL3 2010 Betti Oesterholz
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
 * This class represents the commentelement of the fib-multimedialanguage.
 * An commentelement contains a key- value- pair. Both key and value are
 * strings. The key is the key /identifier for the comment type. (e.g. an
 * key could be "autor" to indicate, that this value is the name of the
 * author of the underobject.)
 * The value is the commentvalue for the key and underobject.
 *
 */
/*
History:
26.07.2010  Oesterholz  created
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
03.06.2013  Oesterholz  SWITCH_JUST_STORE_AND_EVALUE implemented
30.07.2013  Oesterholz  method assignValues() added
*/

#ifndef ___C_COMMENT_H__
#define ___C_COMMENT_H__


#include "version.h"

#include "fibDatatyps.h"

#include "cFibLimb.h"
#include "cRoot.h"
#include "cVectorArea.h"
#include "cFibVariable.h"

#include <string>

using namespace std;

namespace fib{


class cComment: public cFibLimb{

friend class cFibElement;
friend class cRoot;

private:

	/**
	 * The key for the comment.
	 */
	string szKey;
	
	/**
	 * The value for the comment.
	 */
	string szValue;

#ifdef TEST
public:
#endif

	/**
	 * The number for storing the comment in the compressed file format.
	 */
	unsignedLongFib ulCommentNumber;

public:

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	
	/**
	 * parameterconstructor
	 *
	 * @param szInKey the key for the comment ( @see szKey )
	 * @param szInValue the value for the comment ( @see szValue )
	 * @param pInUnderobject the fib-element which is the underobject of
	 * 	this fib-element (it also stands next in the order of fib-elements)
	 * @param pInSuperiorElement the fib-element in which this
	 * 	commentelement is an underobject
	 */
	cComment( const string & szInKey, const string & szInValue,
		cFibElement * pInUnderobject = NULL,
		cFibElement * pInSuperiorElement = NULL );
	
#else //FEATURE_SIMPLE_CONSTRUCTOR
	
	/**
	 * parameterconstructor
	 *
	 * @param szInKey the key for the comment ( @see szKey )
	 * @param szInValue the value for the comment ( @see szValue )
	 * @param pInSuperiorElement the fib-element in which this
	 * 	commentelement is an underobject
	 * @param pInPreviousFibElement the fib-element, which stands in the order
	 * 	of fib-elements befor this fib-element
	 * @param pInUnderobject the fib-element which is the underobject of
	 * 	this fib-element (it also stands next in the order of fib-elements)
	 */
	cComment( const string & szInKey, const string & szInValue,
		cFibElement * pInSuperiorElement = NULL,
		cFibElement * pInPreviousFibElement = NULL,
		cFibElement * pInUnderobject = NULL );

#endif //FEATURE_SIMPLE_CONSTRUCTOR


	/**
	 * copyconstructor
	 * This copyconstructor constructs a copy of the given commentelement.
	 * It dosn't copy other commentelements than the given, even if ther are
	 * in the commentelement.
	 *
	 * @param commentElement the commentelement to copy
	 */
	cComment( const cComment &commentElement );

protected:

	/**
	 * The constructor for restoring a commentobject from an TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node wher the fib-object is stored in
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
	 * 	to restore fib-element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 */
	cComment( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables );

	/**
	 * This constructor restores a commentobject from the stream where it is
	 * stored in the compressed fib-format.
	 * This method is for internal use only.
	 *
	 * @param iBitStream the stream wher the commentobject is stored to in,
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
	 * @param pNextRoot the next higher root -element for the to restore
	 * 	fib-elements, or the last restored root -element
	 */
	cComment( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains,
		cRoot * pNextRoot );


public:

	/**
	 * @see getTypeName
	 * @return a character for the typ of the fib-element
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
	 * This method evaluades the fib-object.
	 *
	 * @param evaluePosition a reference to the object with the
	 * 	evaluePosition() method to evalue /store the positions and ther
	 * 	properties; everytime a point (to evalue) is reached in the
	 * 	evaluation, this method is called with the position and the
	 * 	properties of the point; @see iEvaluePosition
	 * @param objectPoint the object point in the order of true partobjects
	 * 	to evalue
	 * @param liVecProperties a list with the property vectors which should
	 * 	be global for the evalued object
	 * @return if the evalueation was successfull true, else false
	 */
	virtual bool evalueObject( iEvaluePosition & evaluePosition,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties ) const;

	/**
	 * This method evaluades the fib-object.
	 * Evertime a fib-elements, with a type of the given type chars in
	 * liCFibElementTyps, is reached while evaluation, it is given
	 * back with the properties which it has.
	 * Ever pointelement is given back. The type chars for pointelements
	 * don't need to be in the list liCFibElementTyps.
	 *
	 * @param evalueFibElement a reference to the object with the
	 * 	evalueElement() method to evalue /store the fib-elements and ther
	 * 	properties; everytime a fib-element (with one of the type given
	 * 	in liCFibElementTyps) is reached in the evaluation, the method
	 * 	evalueElement() of this objects is called with the fib-element
	 * 	and the properties of the fib-element; @see iEvalueFibElement
	 * @param objectPoint the object point in the order of true partobjects
	 * 	to evalue
	 * @param liVecProperties a list with the property vectors which should
	 * 	be global for the evalued object
	 * @param liCFibElementTyps a list with the type chars (@see getType)
	 * 	of the fib-elements to return
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
	 * This method evaluades the size of the fib-object in bits in the
	 * compressed file form.
	 * The optionalpart field of commentelements will be ignored.
	 *
	 * @see store()
	 * @return the size of the fib-object in bits in the compressed form
	 */
	virtual unsignedLongFib getCompressedSize() const;
	
	/**
	 * This method copies the fib-element on the specified position.
	 * Variables which are not defined in the fib-element but used
	 * don't change ther reference.
	 *
	 * @see getType()
	 * @param cType the type of the fib-element to copy
	 * @param elementPoint the number of the fib-element, in the order of
	 * 	fib-elements of the given type cType, to copy
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	fib-object
	 * @return the copy of the fib-element
	 */
	virtual cFibElement *copyElement( const char cType='u', const unsignedIntFib
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
	 * This method checks if the given fib-object is equal to this Fib
	 * -object.
	 * Variables can be others, but must be defined and used in equivalent
	 * fib-elements.
	 *
	 * @param fibObject the fib-object to which this fib-object should be
	 * 	equal
	 * @return true if this fib-object is equal to the given fib-object,
	 * 	else false
	 */
	virtual bool equal( const cFibElement & fibObject ) const;
	
	/**
	 * This method checks if the given fib-element is equal to this fib
	 * -element.
	 * The underobjects arn't compared, not even ther count is compared.
	 * Used variables can be others.
	 *
	 * @param fibElement the fib-element to which this fib-element should be
	 * 	equal
	 * @return true if this fib-element is equal to the given fib-object,
	 * 	else false
	 */
	virtual bool equalElement( const cFibElement & fibElement ) const;

#endif //FEATURE_EQUAL_FIB_OBJECT
	
#endif //SWITCH_JUST_STORE_AND_EVALUE
	
	/**
	 * This method stores this fib-object in the XML -format into the
	 * given stream.
	 *
	 * @param stream the stream where this fib-object should be stored to
	 * @return true if this fib-object is stored, else false
	 */
	virtual bool storeXml( ostream &stream ) const;



/*
 * commentelement methods
 */
	
	/**
	 * @return the key of the comment ( @see szKey )
	 */
	string getKey() const;

	/**
	 * @param szInKey the key for the comment ( @see szKey )
	 */
	void setKey( const string & szInKey );

	/**
	 * @return the value of the comment ( @see szValue )
	 */
	string getValue() const;

	/**
	 * @param szInValue the value for the comment ( @see szValue )
	 */
	void setValue( const string & szInValue );



protected:

	/**
	 * This method stores this fib-object in the compressed fib-format
	 * into the given stream.
	 * It is needed becouse the stream can yust store byts but the size of
	 * fib-elements can be any number of bits. Because of that ther have to
	 * be a possibility to exchange the missing bits betwean the fib-elements.
	 * Beware: You need to call storeBit() of the root -elements with the
	 * domain for the comment or the comment will not be readebel.
	 *
	 * @see store
	 * @param stream the stream where this fib-object should be stored to
	 * @param cRestBits the not yet writen bits which should be stored
	 * @param uiRestBitPosition the number of bits in the cRestBits which
	 * 	should be writen respectively containing valid information
	 * @return true if this fib-object is stored, else false
	 */
	virtual bool storeBit( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const;

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
	 * This method copies the connected object with the given number in the
	 * order of connected objects.
	 * For this every fib-element, beginning from this fib-element, that
	 * is part of the connected object will be copied.
	 * Variables which are not defined in the connected object but used
	 * don't change ther reference.
	 * It is an helpmethod for the copy method. It dosn't update the
	 * structural information of the created fib-object.
	 *
	 * @param iObjectPoint the number of the connected object to copy;
	 * 	the standartvalue is 0 for coping the complet actual object
	 * @return the copy of the connected object or NULL if non such exists
	 */
	virtual cFibElement *copyInternal( const unsignedIntFib iObjectPoint=0 ) const;

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

#endif //FEATURE_EQUAL_FIB_OBJECT


};
}//namespace fib

#endif //___C_COMMENT_H__






