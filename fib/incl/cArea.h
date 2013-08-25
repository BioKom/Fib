/**
 * @class cArea
 * file name: cArea.h
 * @author Betti Oesterholz
 * @date 14.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the fib -areaelement.
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
 * This class represents the areaelement of the Fib -multimedialanguage.
 * An areaelement contains a list with subareas which build the area.
 * It defines a variable which runs over the values of the areas.
 * The variable takes all integervalues in the subareas of the area.
 *
 */
/*
History:
14.02.2010  Oesterholz  created
18.04.2010  Oesterholz  evalueObject() methods changed: not a function but
	an object is given to evalue the data
07.08.2011  Oesterholz  isDefinedVariable() and getDefinedVariables() with
	pCallingFibElement
25.08.2011  Oesterholz  underarea to subarea
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
30.07.2013  Oesterholz  method assignValues() added
*/

#ifndef ___C_AREA_H__
#define ___C_AREA_H__


#include "version.h"

#include "fibDatatyps.h"

#include "cFibLimb.h"
#include "cRoot.h"
#include "cVectorArea.h"
#include "cFibVariable.h"

namespace fib{


class cArea: public cFibLimb{

friend class cFibElement;

private:

	/**
	 * The list with the subareas of the area element.
	 */
	list<cVectorArea> liSubAreas;
	
	/**
	 *The variable which this areaelement defines.
	 */
	cFibVariable variableDefined;

public:

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	
	/**
	 * parameterconstructor
	 *
	 * @param inVectorArea the subareavector this area should have
	 * @param pInUnderobject the fib -element which is the underobject of
	 * 	this fib -element (it also stands next in the order of fib -elements)
	 * @param pInSuperiorElement the fib -element in which this
	 * 	area -element is an underobject
	 */
	cArea( const cVectorArea & inVectorArea,
		cFibElement * pInUnderobject = NULL,
		cFibElement * pInSuperiorElement = NULL );
	
#else //FEATURE_SIMPLE_CONSTRUCTOR
	
	/**
	 * parameterconstructor
	 *
	 * @param inVectorArea the subareavector this area should have
	 * @param pInSuperiorElement the fib -element in which this
	 * 	area -element is an underobject
	 * @param pInPreviousFibElement the fib -element, which stands in the order
	 * 	of fib -elements befor this fib -element
	 * @param pInUnderobject the fib -element which is the underobject of
	 * 	this fib -element (it also stands next in the order of fib -elements)
	 */
	cArea( const cVectorArea & inVectorArea,
		cFibElement * pInSuperiorElement = NULL,
		cFibElement * pInPreviousFibElement = NULL,
		cFibElement * pInUnderobject = NULL );

#endif //FEATURE_SIMPLE_CONSTRUCTOR


	/**
	 * copyconstructor
	 * This copyconstructor constructs a copy of the given areaelement.
	 * It dosn't copy other area -elements than the given, even if ther are
	 * in the area -element.
	 *
	 * @param areaElement the area -element to copy
	 */
	cArea( const cArea &areaElement );

protected:

	/**
	 * The constructor for restoring a areaobject from an TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node wher the fib -object is stored in
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
	cArea( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables );

	/**
	 * This constructor restores a areaobject from the stream where it is
	 * stored in the compressed fib -format.
	 * This method is for internal use only.
	 *
	 * @param iBitStream the stream wher the areaobject is stored to in,
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
	 */
	cArea( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains,
		cRoot * pNextRoot );


public:

	/**
	 * @see getTypeName
	 * @return a character for the typ of the fib -element
	 * Types are:
	 *		- u: element of unknown typ
	 *		- p: point
	 * 	- l: listelement
	 *		- y: property
	 *		- c: comment
	 *		- a: area
	 *		- f: function
	 *		- i: if -condition
	 *		- o: extern object element
	 *		- s: extern underobject element
	 *		- r: root -element
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
	 * 	to evalue
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
	 * This method evaluades the size of the Fib -object in bits in the
	 * compressed file form.
	 * The optionalpart field of area -elements will be ignored.
	 *
	 * @see store()
	 * @return the size of the Fib -object in bits in the compressed form
	 */
	virtual unsignedLongFib getCompressedSize() const;

	/**
	 * This method checks if the given variable is used in the given
	 * direction from this fib -element.
	 *
	 * @see cFibVariable
	 * @see isDefinedVariable()
	 * @param variable the variable to check if it is used
	 * @param direction the direction from this fib -element, in which the
	 * 	variable should be used; standardvalue is ED_POSITION so yust
	 * 	this fib -element will be checked
	 * @return true if the variable is used, else false
	 */
	virtual bool isUsedVariable( const cFibVariable *variable ,
		edDirection direction=ED_POSITION ) const;

	/**
	 * This method returns all variables used in the given direction from
	 * this fib -element.
	 *
	 * @see cFibVariable
	 * @see isUsedVariable()
	 * @see isDefinedVariable()
	 * @param direction the direction from this fib -element, in which the
	 * 	variable should be used; standardvalue is ED_POSITION so yust
	 * 	this fib -element will be checked
	 * @return the set with all variables used in the given direction from
	 * 	this fib -element
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
	 * This method copies the fib -element on the specified position.
	 * Variables which are not defined in the fib -element but used
	 * don't change ther reference.
	 *
	 * @see getType()
	 * @param cType the type of the fib -element to copy
	 * @param elementPoint the number of the fib -element, in the order of
	 * 	Fib -elements of the given type cType, to copy
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	fib -object
	 * @return the copy of the fib -element
	 */
	virtual cFibElement *copyElement( const char cType='u', const unsignedIntFib
		elementPoint=0, bool bAbsolute=false ) const;

	/**
	 * This method assignss / copies the values from the given Fib element
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
	 * This method checks if the given Fib -object is equal to this Fib
	 * -object.
	 * Variables can be others, but must be defined and used in equivalent
	 * fib -elements.
	 *
	 * @param fibObject the Fib -object to which this Fib -object should be
	 * 	equal
	 * @return true if this Fib -object is equal to the given Fib -object,
	 * 	else false
	 */
	virtual bool equal( const cFibElement & fibObject ) const;
	
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
 * Area -element methods
 */
	
	/**
	 * @return the number of subareas this areaelement consists of
	 */
	unsignedIntFib getNumberOfSubareas() const;
	
	/**
	 * This method returns a pointer to the iSubarea'th subarea of this
	 * areaelement.
	 *
	 * @param iSubarea the number of the subarea to return (counting begins with 1)
	 * @return a pointer to the iSubarea'th subarea, or NULL if non such exists
	 */
	cVectorArea * getSubarea( unsignedIntFib iSubarea=1 );
	
	/**
	 * This method adds the given subarea to the existing subareas.
	 *
	 * @param underArea a reference to the to add subarea
	 * @param uiPosition the position wher the underArea should be added
	 * 	(counting begins with 1); if 0 the underArea will be added to the
	 * 	end of the subarea list
	 * @return true if the underArea was added, else false
	 */
	bool addSubarea( const cVectorArea &underArea, unsignedIntFib uiPosition=0 );
	
	/**
	 * This method deletes the uiSubareaPosition'th subarea from the
	 * existing subareas.
	 *
	 * @param uiSubareaPosition the position wher the underArea should be
	 * 	deleted (counting begins with 1)
	 * @return true if the subarea was deleted, else false
	 */
	bool deleteSubarea( unsignedIntFib uiSubareaPosition );
	
	/**
	 * This method sorts the subareas.
	 *
	 * when sorted the subarealist will fullfill the following constrains:
	 * 	- if the a suarea as two values as it's bounderies, the first
	 * 	  value will be lower than the second
	 * 	- every subareas which have overlaped will be combined to one new
	 * 	  subarea
	 * 	- the subarealist will be sorted in increasing order; subarea
	 * 	  with lower bounderies will be on the front of the subarealist
	 * While sorting bounderies which are given by variables will be ignored.
	 *
	 * @return true if the subareas are sorted, else false
	 */
	bool sort();
	
	/**
	 * @return a pointer to the variable this areaelement defines
	 */
	cFibVariable * getDefinedVariable();


protected:

	/**
	 * This method stores this Fib -object in the compressed Fib -format
	 * into the given stream.
	 * It is needed becouse the stream can yust store byts but the size of
	 * fib -elements can be any number of bits. Because of that ther have to
	 * be a possibility to exchange the missing bits betwean the fib -elements.
	 * Beware: You need to call storeBit() of the root -elements with the
	 * domain for the area or the area will not be readebel.
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
	 * For this every fib -element, beginning from this fib -element, that
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
		map< const cRoot *, const cRoot * > & setEqualRootObjects,
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
		map< const cRoot *, const cRoot * > & setEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const;

#endif //FEATURE_EQUAL_FIB_OBJECT

};
}//namespace fib

#endif //___C_AREA_H__






