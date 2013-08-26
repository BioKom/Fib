/**
 * @class cIf
 * file name: cIf.h
 * @author Betti Oesterholz
 * @date 20.04.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the fib if-element.
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
 * This class represents the fib if-element.
 * An if-element contains an condition and two subobjects, for the true
 * case and the false case of the condition.
 * If the condition is true the subobject for the true case will be
 * evalued, else the subobject for the false case.
 *
 */
/*
History:
20.04.2011  Oesterholz  created
21.08.2011  Oesterholz  syncUnderobjects() renamed to syncSubobjects()
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
30.07.2013  Oesterholz  method assignValues() added
*/

#ifndef ___C_IF_H__
#define ___C_IF_H__


#include "version.h"

#include "fibDatatyps.h"

#include "cFibBranch.h"
#include "cRoot.h"
#include "cCondition.h"
#include "cFibVariable.h"

namespace fib{


class cIf: public cFibBranch{

friend class cFibElement;
friend class cFibBranch;

private:

	/**
	 * The condition of the if-element.
	 */
	cCondition * pCondition;
	
	/**
	 * The true case for this if-element.
	 * If the condition is true the subobject for the true case will be
	 * evalued,
	 * @see getTrueCase()
	 * @see setTrueCase()
	 */
	cFibElement * pFibObjectTrue;

	/**
	 * The false case for this if-element.
	 * If the condition is false the subobject for the false case will be
	 * evalued,
	 * @see getFalseCase()
	 * @see setFalseCase()
	 */
	cFibElement * pFibObjectFalse;

public:

	
	/**
	 * parameterconstructor
	 *
	 * @param inCondition the condition this function should have
	 * @param pInUnderobjectTrueCase the fib-element, which is the underobject of
	 * 	this fib-element for the true case;
	 * 	(it also stands next in the order of fib-elements)
	 * @param pInUnderobjectFalseCase the fib-element, which is the
	 * 	underobject of this fib-element for the false case
	 * @param pInSuperiorElement the fib-element, in which this
	 * 	if-element is an underobject
	 */
	cIf( const cCondition & inCondition,
		cFibElement * pInUnderobjectTrueCase = NULL,
		cFibElement * pInUnderobjectFalseCase = NULL,
		cFibElement * pInSuperiorElement = NULL );


	/**
	 * copyconstructor
	 * This copyconstructor constructs a copy of the given if-element.
	 * It dosn't copy other fib-elements than the given, even if ther are
	 * in the if-element.
	 *
	 * @param ifElement the if-element to copy
	 */
	cIf( const cIf & ifElement );

protected:

	/**
	 * The constructor for restoring a if-object from an TinyXml element.
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
	cIf( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables );

	/**
	 * This constructor restores a if-object from the stream where it is
	 * stored in the compressed fib-format.
	 * This method is for internal use only.
	 *
	 * @param iBitStream the stream wher the if-object is stored to in,
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
	cIf( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains,
		cRoot * pNextRoot );


public:

	/**
	 * destructor
	 */
	~cIf();
	
	/**
	 * This method checks, if this Fib-element is an valid Fib-element.
	 *
	 * @return true if this Fib-element is an valid Fib-element, else false
	 */
	virtual bool isValidFibElement() const;
	
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
	 * This method evaluades the fib -object.
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
	 * This method evaluades the fib -object.
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
	 * The optionalpart field of function -elements will be ignored.
	 *
	 * @see store()
	 * @return the size of the fib-object in bits in the compressed form
	 */
	virtual unsignedLongFib getCompressedSize() const;

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
	 * This method copies the fib-element on the specified position.
	 * Variables which are not defined in the fib-element but used
	 * don't change ther reference.
	 *
	 * @see getType()
	 * @param cType the type of the fib-element to copy
	 * @param elementPoint the number of the fib-element, in the order of
	 * 	Fib -elements of the given type cType, to copy
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	fib -object
	 * @return the copy of the fib-element
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
	 * @return true if this fib-element is equal to the given fib -object,
	 * 	else false
	 */
	virtual bool equalElement( const cFibElement & fibElement ) const;

#endif //FEATURE_EQUAL_FIB_OBJECT

	/**
	 * This method stores this fib-object in the XML -format into the
	 * given stream.
	 *
	 * @param stream the stream where this fib-object should be stored to
	 * @return true if this fib-object is stored, else false
	 */
	virtual bool storeXml( ostream &stream ) const;


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
	 * This method inserts the given Fib-object fibObject on the
	 * specified position. On the specified position a listelement will
	 * be inserted, with the old Fib-object and the given Fib-object
	 * fibObject as its underobjects.
	 *
	 * @see getNumberOfElement()
	 * @see getNumberOfElements()
	 * @see overwriteObjectWithObject()
	 * @see getType()
	 * @param cType the type of the Fib -element, on which position the 
	 * 	given Fib-object fibObject should be inserted
	 * @param elementPoint the number of the Fib -element, in the order of
	 * 	Fib -elements of the given type cType, on which position the given
	 * 	Fib-object fibObject should be inserted
	 * @param fibObject the Fib-object to insert
	 * @param first if true, the inserted object will be the first
	 * 	underobject of the new listelement
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	fib -object
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
	 * @param cType the type of the Fib -element, on which position the 
	 * 	given Fib-object fibObject should be inserted
	 * @param elementPoint the number of the Fib -element, in the order of
	 * 	Fib -elements of the given type cType, on which position the given
	 * 	Fib-object fibObject should be inserted
	 * @param fibObject the Fib-object to insert
	 * @param bDeleteOld if true, delete the old Fib-object from the memory
	 * @param bAbsolute if the elementPoint is an absolute value for the wool
	 * 	fib -object
	 * @return true if the old Fib-object was overwritten and the given 
	 * 	Fib-object fibObject was inserted, else false
	 */
	virtual bool overwriteObjectWithObject( cFibElement *fibObject, const char cType='u',
		const unsignedIntFib elementPoint=0, bool bDeleteOld=true,
		bool bAbsolute=false );

	/**
	 * This method checks, if all Fib -elements of this Fib -object
	 * have the underobjects they need to be correct.
	 *
	 * @return true if all Fib -elements of this Fib -object have the
	 * 	underobjects they need to be correct, else false
	 */
	virtual bool hasUnderAllObjects() const;
	
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
	 * @param bCheckVariables if true (standardvalue) it will be checked if
	 * 	the variables the Fib-element defines are needed, else the 
	 * 	Fib-element will be removed even if its variables are needed elsewher
	 * @return the pointer to the cuted Fib-element or NULL, if the Fib
	 * 	-element couldn't cut
	 */
	virtual cFibElement *cutElement( const char cType='u', const unsignedIntFib
		elementPoint=0, bool bAbsolute=false, bool bCheckVariables=true );

/*
 * if-element methods
 */
	
	/**
	 * @return the condition of this if-element
	 */
	cCondition * getCondition() const;
	
	/**
	 * This method sets the given condition as the condition of
	 * this if-element.
	 * (The given condition is copied befor it is set.)
	 *
	 * @param condition a reference to the to set condition
	 * @return true if the condition was set, else false
	 */
	bool setCondition( const cCondition & condition );
	
	/**
	 * @return the true case of this if-element or NULL, if non exist
	 */
	cFibElement * getTrueCase();

	/**
	 * This method sets the given Fib-object as the true case for this
	 * this if-element.
	 *
	 * @param fibObjectTrue the new true case Fib-object to set
	 * @param bDeleteOld if true, delete the old Fib-object from the memory
	 * @return true if the true case was set, else false
	 */
	bool setTrueCase( cFibElement * fibObjectTrue, bool bDeleteOld=true );

	/**
	 * @return the false case of this if-element or NULL, if non exist
	 */
	cFibElement * getFalseCase();

	/**
	 * This method sets the given Fib-object as the false case for this
	 * this if-element.
	 *
	 * @param fibObjectFalse the new false case Fib-object to set
	 * @param bDeleteOld if true, delete the old Fib-object from the memory
	 * @return true if the false case was set else false
	 */
	bool setFalseCase( cFibElement * fibObjectFalse, bool bDeleteOld=true );

protected:

	/**
	 * This method stores this fib-object in the compressed Fib -format
	 * into the given stream.
	 * It is needed becouse the stream can yust store byts but the size of
	 * fib-elements can be any number of bits. Because of that ther have to
	 * be a possibility to exchange the missing bits betwean the fib-elements.
	 * Beware: You need to call storeBit() of the root -elements with the
	 * domain for the function or the function will not be readebel.
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
	 * This method copies the connected object with the given number in the
	 * order of connected objects.
	 * For this every fib-element, beginning from this fib-element, that
	 * is part of the connected object will be copied.
	 * Variables which are not defined in the connected object but used
	 * don't change ther reference.
	 * It is an helpmethod for the copy method. It dosn't update the
	 * structural information of the created fib -object.
	 *
	 * @param iObjectPoint the number of the connected object to copy;
	 * 	the standartvalue is 0 for coping the complet actual object
	 * @return the copy of the connected object or NULL if non such exists
	 */
	virtual cFibElement *copyInternal( const unsignedIntFib iObjectPoint=0 ) const;

	/**
	 * This method syncronises the underobjects of this cIf-class with
	 * the underobjectslist fibUnderObjects of the cFibBranch class.
	 */
	void syncSubobjects();
	
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

#endif //___C_IF_H__






