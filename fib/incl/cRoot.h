/**
 * @class cRoot
 * file name: cRoot.h
 * @author Betti Oesterholz
 * @date 05.07.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the root-Fib-element.
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
 * This class represents the root-element of the Fib-multimedialanguage.
 * It holds the information for the enviroment of the Fib-Object, like
 * number of dimensions and domains.
 *
 */
/*
History:
05.07.2009  Oesterholz  created
13.12.2009  Oesterholz  storePropertyType() and createStorePropertyOrder() implemented
18.04.2010  Oesterholz  evalueObject() methods changed: not a function but
	an object is given to evalue the data
27.09.2010  Oesterholz  generateNeededDomains() method added
07.08.2011  Oesterholz  isDefinedVariable() and getDefinedVariables() with
	pCallingFibElement
09.08.2011  Oesterholz  changes for cExtObject: (new: liPExtObjectElm,
	setCallingFibElement(), unsetCallingFibElement() )
15.08.2011  Oesterholz  syncUnderobjects() renamed to syncSubobjects()
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
07.11.2011  Oesterholz  ExternUnderObjects to ExternSubobjects
29.01.2011  Oesterholz  FEATURE_EXT_SUBOBJECT_INPUT_VECTOR implemented:
	the input values are now a vector of values;
	getValidDomains() + getValidPureValueDomains() bInherit added
22.11.2012  Oesterholz  Bugfix: a root element can be called more than one
	time by external objects
*/

#ifndef ___C_ROOT_H__
#define ___C_ROOT_H__


#include "version.h"

#include "fibDatatyps.h"

#include "cFibElement.h"
#include "cFibBranch.h"
#include "cMultimediaInfo.h"
#include "cOptionalPart.h"
#include "cDomains.h"
#include "cVectorChecksum.h"
#include "cTypeProperty.h"

#include <list>
#include <set>


namespace fib{

//cyclic dependencies
class cExtObject;
class cFibDatabase;


class cRoot: public cFibBranch{

friend class cFibElement;
friend class cProperty;
friend class cFibBranch;
friend class cExtObject;
friend class cExtSubobject;

private:

	/**
	 * The main -Fib object of this root-object.
	 * The pointer to the main -Fib object should also be stored as the
	 * first element in the fibUnderObjects property of the cFibBranch
	 * class. So a lot methods can be implemented ther and don't have to
	 * overwritten in this cRoot class.
	 */
	cFibElement * pMainFibObject;

	/**
	 * The sub -root-objects of this root-object.
	 * The first element of the pair is the sub -root-object identifier
	 * and the secound a pointer to the sub -root-object.
	 * The pointers to the sub -root-objects should also be stored in the
	 * same order in the fibUnderObjects property of the cFibBranch class.
	 * So a lot methods can be implemented ther and don't have to
	 * overwritten in this cRoot class.
	 */
	list< pair< longFib, cRoot * > > liSubRootObjects;

	/**
	 * The multimediainfo of this root-element.
	 */
	cMultimediaInfo multimediaInfo;
	
	/**
	 * The optionalpart of this root-element.
	 */
	cOptionalPart optionalPart;

	/**
	 * The domains of this root-element.
	 */
	cDomains domains;

	/**
	 * The domains for elementvalues of this root-element.
	 */
	cDomains valueDomains;

	/**
	 * The pointer to the checksumvektor of this root-element or NULL if
	 * non such exists.
	 */
	cVectorChecksum * pChecksum;

	/**
	 * This list contains the input variables of the root-element.
	 * The first value of an entry pair ist the Variable and the secound
	 * is the standardvalue for the variable.
	 */
	list< pair< cFibVariable *, doubleFib > > liInputVariables;
	
#ifndef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
//TODO remove
	/**
	 * This is the list for extern subobjects.
	 * The list entries are the number of output varaibles for the extern
	 * subobjects.
	 */
	list< unsignedIntFib > liExternSubobjects;
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	/**
	 * This set contains the identifiers of used database objects.
	 */
	set< longFib > setDatabaseIdentifiers;

//the next filed are for intern evaluation

	/**
	 * The propertytypes, in the order they will be counted when stored.
	 * This list will be created when storeBit() is called, so the
	 * properties can be stored.
	 * This is not real class data, but helpdata for storing. (const
	 * methods shouldn't fear to change this.)
	 *
	 * @see storeBit()
	 */
	list< cTypeProperty > liStorePropertyOrder;
	
	/**
	 * The stored input variables of this root-object.
	 * It is neccessary to store the values of the input variables, while
	 * storing the object, because the values of the input variables will be
	 * set to ther number for storing, but the values of the input variables
	 * could be change from a user beforhand and shouldn't change while
	 * storing.
	 * This is not real class data, but helpdata for storing. (const
	 * methods shouldn't fear to change this.)
	 *
	 * @see backupVariablesValues()
	 */
	list< list< cFibVariable * > > liLiStoredInputVariables;
	
	/**
	 * A pointer to the extern object element which calls /uses this
	 * root-object.
	 * @see cExtObject
	 * @see getCallingExtObject()
	 * @see setCallingFibElement()
	 * @see unsetCallingFibElement()
	 * @see evalueObject()
	 */
	list< cExtObject * > liPExtObjectElm;
	
	/**
	 * The stored input variables of this root-object.
	 * It is neccessary to store the values of the input variables, while
	 * storing the object, because the values of the input variables will be
	 * set to ther number for storing, but the values of the input variables
	 * could be change from a user beforhand and shouldn't change while
	 * storing.
	 * This is not real class data, but helpdata for storing. (const
	 * methods shouldn't fear to change this.)
	 *
	 * @see cExtObject
	 * @see liPExtObjectElm()
	 * @see setCallingFibElement()
	 * @see unsetCallingFibElement()
	 * @see evalueObject()
	 */
	list< list< cFibVariable * > > liLiStoredBelowVariables;
	
	
	/**
	 * The object for the Fib database.
	 */
	static cFibDatabase * pFibDatabase;
	
public:

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	
	/**
	 * parameterconstructor
	 *
	 * @param pInMainFibObject the main Fib object of this root-element
	 * @param pInSuperiorRootElement the root-Element in which this
	 * 	root-element is an subobject
	 */
	cRoot( cFibElement * pInMainFibObject = NULL,
		cRoot * pInSuperiorRootElement = NULL );
	
#else //FEATURE_SIMPLE_CONSTRUCTOR
	
	/**
	 * parameterconstructor
	 *
	 * @param pInSuperiorRootElement the root-Element in which this
	 * 	root-element is an subobject
	 * @param pInPreviousFibElement the Fib Element which stands in th order
	 * 	of Fib-elements befor this Fib-element
	 * @param pInMainFibObject the main Fib object of this root-element
	 */
	cRoot( cRoot * pInSuperiorRootElement = NULL,
		cFibElement * pInPreviousFibElement = NULL,
		cFibElement * pInMainFibObject = NULL );

#endif //FEATURE_SIMPLE_CONSTRUCTOR

	/**
	 * copyconstructor
	 * This copyconstructor constructs a copy of the given root-Element.
	 * It dosn't copy other root-elements than the given, even if ther are
	 * in the root-element.
	 *
	 * @param rootElement the root-element to copy
	 */
	cRoot( const cRoot &rootElement );


protected:

	/**
	 * The constructor for restoring a rootyelement from an TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node the Fib object is stored in
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
	 * 	to restore Fib element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 */
	cRoot( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables );


	/**
	 * This method restores a rootobject from the stream where it is
	 * stored in the compressed Fib format.
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
	 * 	Fib elements, or the last restored root-element;
	 * 	if NULL the next Fib element restored will be an root-element
	 */
	cRoot( cReadBits & iBitStream, intFib & outStatus, cRoot * pNextRoot );

public:

	/**
	 * desstructor
	 */
	virtual ~cRoot();


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
	 * This method checks, if this Fib element is an valid Fib element.
	 *
	 * @return true if this Fib element is an valid Fib element, else false
	 */
	virtual bool isValidFibElement() const;
	
	/**
	 * This method checks, if all Fib-elements of this Fib-object
	 * have the subobjects they need to be correct.
	 *
	 * @return true if all Fib-elements of this Fib-object have the
	 * 	subobjects they need to be correct, else false
	 */
	virtual bool hasUnderAllObjects() const;

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
	 * This method evaluades the size of the Fib-object in bits in the
	 * compressed file form.
	 * The optionalpart field of root-elements will not be ignored.
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
	 * @param bWriteOptionalPart if true the size of the optionalpart is
	 * 	evalued, else it is ignored
	 * @return the size of the Fib-object in bits in the compressed form
	 */
	virtual unsignedLongFib getCompressedSize( bool bWriteOptionalPart ) const;
	
	/**
	 * @return true if this Fib element is movebel else false
	 */
	virtual bool isMovable() const;


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
	 * 	Fib object
	 * @return the copy of the Fib element
	 */
	virtual cFibElement *copyElement( const char cType='u', const unsignedIntFib
		elementPoint=0, bool bAbsolute=false ) const;

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
	 * This method checks if the given Fib element is equal to this fib
	 * -element.
	 * The subobjects arn't compared, not even ther count is compared.
	 * Used variables can be others.
	 *
	 * @param fibElement the Fib element to which this Fib element should be
	 * 	equal
	 * @return true if this Fib element is equal to the given Fib object,
	 * 	else false
	 */
	virtual bool equalElement( const cFibElement & fibElement ) const;

	/**
	 * This method checks if the given Fib-element sets the variable to
	 * the same values as this Fib element.
	 *
	 * @param variableOwn a pointer to a defined variable in this Fib element,
	 * 	it is compared to the equivalent variable fibElement in the given
	 * 	Fib element fibElement
	 * @param fibElement the Fib-element to which this Fib-element should be
	 * 	compared
	 * @param variable a pointer to a defined variable in the other 
	 * 	Fib element fibElement
	 * @return true if this Fib-element sets the variable to the same
	 * 	values as this Fib element
	 */
	virtual bool equalValuesSet( const cFibVariable * variableOwn,
		const cFibElement & fibElement,
		const cFibVariable * variable ) const;

#endif //FEATURE_EQUAL_FIB_OBJECT

	/**
	 * This method stores this Fib-object in the XML -format into the
	 * given stream.
	 *
	 * @param stream the stream where this Fib-object should be stored to
	 * @return true if this Fib-object is stored, else false
	 */
	virtual bool storeXml( ostream &stream ) const;


	/**
	 * This method inserts the given Fib-element fibElement on the
	 * specified position. The replaced Fib-element will be the subobject
	 * of the inserted Fib-element fibElement.
	 *
	 * @see getNumberOfElement()
	 * @see getNumberOfElements()
	 * @see getType()
	 * @param cType the type of the Fib-element insted of which the given
	 * 	Fib-element fibElement should be inserted
	 * @param elementPoint the number of the Fib-element, in the order of
	 * 	Fib-elements of the given type cType, in which position the given
	 * 	Fib-element fibElement should be inserted; if 0 the given
	 * 	fibElement will be inserted under this Fib-element
	 * @param fibElement the Fib-element to insert
	 * @param bAbsolute if the lNumber is an absolute value for the wool
	 * 	Fib object
	 * @param bCheckVariables if true (standardvalue) it will be checked if
	 * 	the variables the Fib-element defines are needed, else the 
	 * 	Fib-element will be removed even if its variables are needed elsewher
	 * @return true if the Fib-element fibElement was inserted, else false
	 */
	virtual bool insertElement( cFibElement *fibElement, const char cType='u',
		const unsignedIntFib elementPoint=0, bool bAbsolute=false,
		bool bCheckVariables=true );


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
	 * 	Fib object
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
	 * 	Fib object
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
	 * @see isDeletableElement()
	 * @see removeElement()
	 * @see getType()
	 * @param cType the type of the Fib-element to cut
	 * @param elementPoint the number of the Fib-element, in the order of
	 * 	Fib-elements of the given type cType, to cut
	 * @param bAbsolute if the elementPoint is an absolute value for the wool
	 * 	Fib object
	 * @param bCheckVariables if true (standardvalue) it will be checked if
	 * 	the variables the Fib element defines are needed, else the 
	 * 	Fib element will be removed even if its variables are needed elsewher
	 * @return the pointer to the cuted Fib-element or NULL, if the Fib
	 * 	-element couldn't cut
	 */
	virtual cFibElement *cutElement( const char cType='u', const unsignedIntFib
		elementPoint=0, bool bAbsolute=false, bool bCheckVariables=true );

	/**
	 * This method moves a Fib-limb -element (cFibLimb) on the specified
	 * position over iHowfar Fib-elements.
	 * Moving is stoped if an invalid Fib-object would result (e.g. no Fib
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
	 * 	Fib-element should be moved; if this value is positiv the Fib
	 * 	-element will be moved over Fib-elements it contains else over
	 * 	Fib-elements it is contained in
	 * @param bAbsolute if the elementPoint is an absolute value for the wool
	 * 	Fib object
	 * @return the number of Fib-Elements over which the to move Fib
	 * 	-element was moved; if this value is positiv the Fib-element
	 * 	was moved over Fib-elements it contains else over Fib-elements
	 * 	it is contained in
	 */
	virtual intFib moveLimbElement( const char cType='u', const unsignedIntFib 
		elementPoint=0, const intFib iHowfar=1, bool bAbsolute=false );


	/**
	 * @see szDatabasePath
	 * @return a string to the actual set database path, the string is empty
	 * 	if no database path is set
	 */
	static std::string getDatabasePath();
	
	/**
	 * This function sets the Fib database path to the given path if possible.
	 *
	 * @see szDatabasePath
	 * @param szInDatabasePath the path to the folder with the Fib database
	 * 	objects
	 * @return true if the given Fib database path exists and was set, else
	 * 	false and the database path is not changed
	 */
	static bool setDatabasePath( const char * szInDatabasePath );
	
	/**
	 * This function sets the Fib database path to the given path if posible.
	 *
	 * @see szDatabasePath
	 * @param szInDatabasePath the path to the folder with the Fib database
	 * 	objects
	 * @return true if the given Fib database path exists and was set, else
	 * 	false and the database path is not changed
	 */
	static bool setDatabasePath( const std::string szInDatabasePath );
	
	
	/**
	 * This method returns the identifiers of all root-objects of this
	 * object.
	 *
	 * @return the identifiers of all root-objects of this object
	 */
	virtual list<longFib> getAllRootObjectIdentifiers() const;

	/**
	 * This method returns the identifiers of all database objects, in the
	 * actual database.
	 *
	 * @return the identifiers of all database objects
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
	virtual cRoot * getRootObject( longFib lIdentifier );

	/**
	 * This method returns the identifiers of all from this Fib-element
	 * accessible root-objects of this object.
	 *
	 * @return the identifiers of all accessible root-objects
	 */
	virtual list<longFib> getAllAccessibleRootObjectIdentifiers() const;

	/**
	 * This method returns the from this Fib-element accessible root
	 * -object for the given identifier. If non such exists the Nullpoint 
	 * NULL is returned.
	 *
	 * @param lIdentifier the identifier of the root-object to return
	 * @return the accessible root-object for the given identifier or NULL
	 * 	if non such exists
	 */
	virtual cRoot * getAccessibleRootObject( longFib lIdentifier );


	/**
	 * This method returns the domains that are valid for this Fib-element.
	 *
	 * @return the domains that are valid for this Fib-element
	 */
	virtual cDomains getValidDomains() const;

	/**
	 * This method returns the domains that are valid for this Fib-element.
	 *
	 * @param bInherit if true just inherited domains of this root element will
	 * 	be returned else if false all domains will be returned
	 * @return the domains that are valid for this Fib-element
	 */
	virtual cDomains getValidDomains( const bool bInherit ) const;

	/**
	 * This method returns the value domains that are valid for this
	 * Fib element.
	 * Just value domains are returned.
	 *
	 * @see getValidValueDomains()
	 * @see getValidDomains()
	 * @param bInherit if true just inherited domains of this root element will
	 * 	be returned else if false all domains will be returned
	 * @return the value domains that are valid for this Fib-element
	 */
	cDomains getValidPureValueDomains( const bool bInherit = false ) const;

	/**
	 * This method returns the domains for value that are valid for this
	 * Fib element.
	 * Missing value domains are added from the (non value) domains.
	 *
	 * @see getValidPureValueDomains()
	 * @see getValidDomains()
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


/*
 * Root -element methods
 */

	/**
	 * This method sets the main -Fib object to the given pInMainFibObject.
	 *
	 * @param pInMainFibObject a pointer to the main -Fib object to set
	 * @return true if the main -Fib object is set to pInMainFibObject, else false
	 */
	bool setMainFibObject( cFibElement * pInMainFibObject );

	/**
	 * @return a pointer to the multimediainfo of this root-element
	 */
	cMultimediaInfo * getMultimediaInfo();

	/**
	 * @return a pointer to the optionalpart of this root-element or
	 * 	NULL if non such exists.
	 */
	cOptionalPart * getOptionalPart();

	/**
	 * @return a pointer to the domains of this root-element
	 */
	cDomains * getDomains();

	/**
	 * @return a pointer to the compressed/ value domains of this
	 * 	root-element
	 */
	cDomains * getValueDomains();

	/**
	 * This method generates all domains, wich are needed to store this
	 * Fib-object.
	 * Most generated domains are added as value domains of this root-element.
	 *
	 * the generated domains are for the typs:
	 * 	- cTypeArea
	 * 	- cTypeUnderFunction
	 * 	- cTypeExtObject
	 * 	- cTypeExtSubobject (added as domains if wrong exists)
	 * 	- cTypeFibSet
	 * 	- cTypeFibMatrix
	 * 
	 * @param bAddAllValueDomains if true all domains, which are added as value
	 * 	domains, are added without checking if they are needed
	 */
	void generateNeededDomains( const bool bAddAllValueDomains = false );

	/**
	 * @return the count of input variables for the main Fib object of
	 * 	this root-object
	 */
	unsignedIntFib getNumberOfInputVariables() const;

	/**
	 * This method sets the number of input variables, the main Fib object
	 * of this root-object should have, to the given number. It will
	 * create or delete variables as necessary.
	 * Standardvalue of new varibles is the nullvalue of the standarddomain
	 * for input variables. Variables which are still in use can't be 
	 * deleted. The delete process will beginn on the end of the input 
	 * variablen list and stop if enght variables are deleted or an
	 * variable can't be deleted.
	 * 
	 * @param uiNumberOfInputVariables the number of input variables the main
	 * 	Fib object of this root-object should have
	 * @return true if the number of input variables is set to the given
	 * 	value, else false
	 */
	bool setNumberOfInputVariables( unsignedIntFib uiNumberOfInputVariables );

	/**
	 * @return a list with the input variables of this root-object.
	 */
	list<cFibVariable*> getInputVariables();

	/**
	 * @param uiNumberOfInputVariable the number of the input variable to
	 * 	return
	 * @return the uiNumberOfInputVariable input variable of this root-object
	 */
	cFibVariable * getInputVariable( unsignedIntFib uiNumberOfInputVariable );

	/**
	 * @param uiNumberOfInputVariable the number of the input variable for
	 * 	which the standardvalue is to be return
	 * @return the standardvalue of the uiNumberOfInputVariable
	 * 	input variable of this root-object
	 */
	doubleFib getStandardValueOfInputVariable(
		unsignedIntFib uiNumberOfInputVariable ) const;

	/**
	 * This Method sets the standardvalue of uiNumberOfInputVariable
	 * input variable.
	 *
	 * @param uiNumberOfInputVariable the number of the input variable for
	 * 	which the standardvalue is to be set
	 * @param dValue the value to which the standardvalue is to be set
	 * @return true if the standardvalue of the uiNumberOfInputVariable
	 * 	input variable of this root-object is set do dValue,
	 * 	else false
	 */
	bool setStandardValueOfInputVariable(
		unsignedIntFib uiNumberOfInputVariable, doubleFib dValue );


	
	/**
	 * @return the count of extern subobjects this root-object has
	 */
	unsignedIntFib getNumberOfExternSubobjects() const;

	/**
	 * This method returns the number of output variables of the
	 * uiNumberOfExtSubobject'th extern subobject in this root-object, or
	 * 0 if the subobject dosn't exists.
	 *
	 * @param uiNumberOfExtSubobject the number of the subobject for which
	 * 	the number of output variables is to be returned
	 * @return the count of output variables of the uiNumberOfExtSubobject'th
	 * 	extern subobject in this root-object, or 0 if the
	 * 	subobject dosn't exists
	 */
	unsignedIntFib getNumberOfOutputVariables(
		unsignedIntFib uiNumberOfExtSubobject ) const;

#ifndef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	/**
	 * This method sets the number of the extern subobjects this 
	 * root-object has to the given value uiNumberOfExternUnderObjects.
	 * It automaticly creates or delets extern subobjects to or from the
	 * end of the extern subobjectslist, till uiNumberOfExternUnderObjects
	 * subobjects exsists or the operation is not possible.
	 * Underobjects wich are still in use/ still exists in the main -fib
	 * -object of this root-object can't be deleted.
	 * The number of output variables of the created subobjects will be
	 * set to 0.
	 *
	 * @param uiNumberOfExternUnderObjects the number of extern
	 * 	subobjects this root-object should have
	 * @return true if the number of extern subobjects is set to
	 * 	uiNumberOfExternUnderObjects, else false
	 */
	bool setNumberOfExternSubobjects(
		unsignedIntFib uiNumberOfExternUnderObjects );

	/**
	 * This method sets the number of output variables of the
	 * uiNumberOfUnderObject extern subobject in this root-object to 
	 * the given value uiNumberOfVariables.
	 *
	 * @param uiNumberOfUnderObject the number of the subobject for which
	 * 	the number of output variables is to be set
	 * @param uiNumberOfVariables the number of output variables the
	 * 	uiNumberOfUnderObject subobject of this root-object should have
	 * @return true if the number of output variables of the
	 * 	uiNumberOfUnderObject subobject was set to uiNumberOfVariables,
	 * 	else false
	 */
	bool setNumberOfOutputVariables(
		unsignedIntFib uiNumberOfUnderObject,
		unsignedIntFib uiNumberOfVariables );

#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	/**
	 * This method checks the extern subobject of this root-object.
	 * It is checked if:
	 * 	- every subobject in main -Fib object of this root-object
	 * 	is also defined in the root-object
	 * 	- the number of output variables in the definition and the
	 * 	subobject Fib element(s) are the same
	 * 	- ever subobject which is defined in this root-object is used
	 * 	somewhere in the main -Fib object
	 *
	 * @param iErrorNumber a pointer to an integerfild, wher an errornumber
	 * 	can be stored; or NULL (standardvalue) if no errornumber should
	 * 	be given back
	 * 	possible errornumbers:
	 * 		- 0 no error, everything is OK
	 * 		- -1 no main -Fib object
	 * 		- -10 an subobject definition is missing
	 * 		- -11 different number of output variables
	 * 		- -12 not every defined subobject is used
	 * 		- -13 the numbers of the subobjects dosn't go from 1 till n
	 * @return the number of the first not correct extern subobject in
	 * 	this root-object or 0 if every subobject is OK
	 */
	unsignedIntFib checkExternSubobjects(
		intFib * iErrorNumber=NULL );

	/**
	 * This method generates the extern subobject definitions for this
	 * root-object.
	 * possible errors which aborts the generation process:
	 * 	- the number of output variables in the the subobject
	 *		Fib elements are not the same
	 * 	-the numbers of the subobjects dosn't go from 1 till n
	 *
	 * @param iErrorNumber a pointer to an integerfild, wher an errornumber
	 * 	can be stored; or NULL (standardvalue) if no errornumber should
	 * 	be given back
	 * 	possible errornumbers:
	 * 		- 0 no error, everything is OK
	 * 		- -1 no main -Fib object
	 * 		- -11 different number of output variables
	 * 		- -13 the numbers of the subobjects dosn't go from 1 till n
	* @return the number of the first not correct extern subobject in
	* 	this root-object or 0 if every subobject is OK
	 */
	unsignedIntFib generateExternSubobjectsDefinitions(
		intFib * iErrorNumber=NULL );


	/**
	 * @return the count of sub -root-objects in this root-object
	 */
	unsignedIntFib getNumberOfSubRootObjects() const;

	/**
	 * This method returns the uiNumberOfUnderObject sub -root-object
	 * of this root-element or the pair <0,NULL>, if non such exists.
	 * The returned pair first element is the identifier of the sub -root
	 * -object and the secound is a pointer to the sub -root-object.
	 *
	 * @param uiNumberOfUnderObject the number of the sub -root-object to
	 * 	return
	 * @return the uiNumberOfUnderObject't sub -root-objects of this
	 * 	root-object as an (idenitifier, root-object -pointer) -pair or
	 * 	the pair <0,NULL>, if non such exists
	 */
	pair<longFib, cRoot*> getSubRootObject( unsignedIntFib uiNumberOfUnderObject );


	/**
	 * This method returns the number of the sub -root-object with the
	 * identifier lIdentifier in this root-element or 0 if non such exists.
	 *
	 * @param lIdentifier identifier of the sub -root-object for which
	 * 	the number should be returned return
	 * @return the number of the sub -root-object with the identifier
	 * 	lIdentifier in this root-element or 0 if non such exists
	 */
	unsignedIntFib getSubRootObjectNumber( longFib lIdentifier ) const;

	/**
	 * This method returns the sub -root-object with the identifier
	 * lIdentifier in this root-element or NULL if non such exists.
	 *
	 * @param lIdentifier identifier of the sub -root-object which
	 * 	should be returned return
	 * @return the sub -root-object with the identifier lIdentifier
	 * 	in this root-element or NULL if non such exists
	 */
	cRoot * getSubRootObjectForIdentifier( longFib lIdentifier );

	/**
	 * This method adds the given root-object to the sub -root-object
	 * -list of this root-element.
	 * This will fail if:
	 * 	- ther is no root-object (rootObject=NULL)
	 * 	- the identifier lIdentifier is allready in use somewher in this
	 * 	wool object
	 *
	 * @param lIdentifier the identifier the root-object should have
	 * @param pRootObject a pointer to the root-object to add; the object
	 * 	will not be copied, so don't delete it
	 * @param uiPosition the position on which the root-object is to insert
	 * 	in this root-element sub -object -list (counting begins with 1)
	 * @return true if the root-object pRootObject was inserted, else false
	 */
	bool addSubRootObject( longFib lIdentifier, cRoot * pRootObject,
		unsignedIntFib uiPosition=0 );


	/**
	 * This method deletes the uiSubRootObjectNumber'th sub -root-object
	 * in this root-element.
	 *
	 * @param uiSubRootObjectNumber the number of the sub -root-object in
	 * 	the sub -root-object -list to delete
	 * @param bDeleteOld if true the sub -root-object will be removed from
	 * 	the memory, else yust the reference will be removed from this
	 * 	root-element; default is true
	 * @return true if the uiSubRootObjectNumber'th sub root-object was
	 * 	deleted, else false
	 */
	bool deleteSubRootObject( unsignedIntFib uiSubRootObjectNumber,
		bool bDeleteOld=true );

	/**
	 * This method returns all identifiers of all sub -root-objects in
	 * this root-element.
	 *
	 * @return all identifiers of all sub -root-objects in this root-element
	 */
	list< longFib > getAllSubRootObjectIdentifiers() const;
	
	
	/**
	 * @return a set with all database identifiers that are given in this
	 * 	root-element as used database objects 
	 * 	@see setDatabaseIdentifiers
	 */
	set< longFib > getUsedDatabaseIdentifiers() const;
	
	/**
	 * This method adds the given database identifier to the used database 
	 * identifiers of this root-element.
	 * @see setDatabaseIdentifiers
	 * 
	 * @param lIdentifier the identifer of a database object to add as used
	 * 	by this root-element
	 */
	void addUsedDatabaseIdentifier( const longFib lIdentifier );

	/**
	 * This method deletes the given database identifier from the used 
	 * database identifiers of this root-element.
	 * @see setDatabaseIdentifiers
	 * 
	 * @param lIdentifier the identifer of a database object to delete
	 * @return true if the identifier was deleted, else false
	 */
	bool deleteUsedDatabaseIdentifier( const longFib lIdentifier );

	
	/**
	 * @return the checksumvektor of this root-element or NULL if no such
	 * 	exists
	 */
	cVectorChecksum * getChecksum();

	/**
	 * This method sets the checksumm for this root-element.
	 * If no checksumvektor or a NULL -pointer is given, the checksum
	 * property for this root-element is disabled.
	 *
	 * @param checksum the checksumvektor this root-element should have;
	 * 	if NULL (standardvalue ) the checksum will be disabled for this
	 * 	root-element
	 */
	void setChecksum( const cVectorChecksum * checksum = NULL);
	
	
protected:

	/**
	 * This method stores this Fib-object in the compressed Fib-format
	 * into the given stream.
	 * It is needed becouse the stream can yust store byts but the size of
	 * Fib elements can be any number of bits. Because of that ther have to
	 * be a possibility to exchange the missing bits betwean the Fib elements.
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
	 * This method stores this Fib-object in the compressed Fib-format
	 * into the given stream.
	 * It is needed becouse the stream can yust store byts but the size of
	 * Fib elements can be any number of bits. Because of that ther have to
	 * be a possibility to exchange the missing bits betwean the Fib elements.
	 *
	 * @see store
	 * @param stream the stream where this Fib-object should be stored to
	 * @param cRestBits the not yet writen bits which should be stored
	 * @param uiRestBitPosition the number of bits in the cRestBits which
	 * 	should be writen respectively containing valid information
	 * @param bWriteOptionalPart if true the optionalpart is written
	 * @return true if this Fib-object is stored, else false
	 */
	virtual bool storeBit( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition, bool bWriteOptionalPart ) const;

#ifdef FEATURE_FAST_UPDATE

	/**
	 * This method cuts the connections of this Fib element to the
	 * given Fib element.
	 *
	 * @param pFibElement the Fib element to which to cut the connection
	 */
	virtual void cutConnectionsTo( const cFibElement * pFibElement );
	
	/**
	 * This method updates the Fib element counters of all branchelements in
		 * this branchelement.
	 *
	 * @return the numbers with which the Fib element counters wher updated
	 */
	virtual cFibObjectCounts updateCounters();

#endif //FEATURE_FAST_UPDATE

	/**
	 * This method stores the actual variables of this root element, so
	 * they can restored later.
	 * This method also restores the variable values. Yust one set of values
	 * can be stored.
	 *
	 * @param bStoreValues is true the variables values will be stored, else
	 * 	the stored variables will be restored.
	 */
	void backupVariablesValues( bool bStoreValues = true );

	/**
	 * This method syncronises the subobjects of this cRoot -class with
	 * the subobjectslist fibUnderObjects of the cFibBranch class.
	 */
	void syncSubobjects();
	
	/**
	 * This method returns the identifiers of all root-objects in the
	 * direction down of this root-element.
	 *
	 * @see getAllRootObjectIdentifiers()
	 * @return the identifiers of all root-objects in the direction down
	 */
	list<longFib> getAllDownRootObjectIdentifiers() const;

	/**
	 * This method returns the root-object in the direction down for the
	 * given identifier.
	 * If non such exists the Nullpoint NULL is returned.
	 *
	 * @param lIdentifier the identifier of the root-object to return
	 * @return the root-object for the given identifier or NULL if non
	 * 	such exists
	 */
	cRoot * getRootObjectDown( longFib lIdentifier );

	/**
	 * This method returns the identifiers of all from this Fib-element
	 * accessible root-objects of this object.
	 *
	 * @param pRoot a pointer to the root element, for which the
	 * 	root-elements should be accessible
	 * @return the identifiers of all accessible root-objects
	 */
	list<longFib> getAllAccessibleRootObjectIdentifiers( const cRoot *pRoot ) const;

	/**
	 * This method returns the from this Fib-element accessible root
	 * -object for the given identifier. If non such exists the Nullpoint 
	 * NULL is returned.
	 *
	 * @param pRoot a pointer to the root element, for which the
	 * 	root-elements should be accessible
	 * @param lIdentifier the identifier of the root-object to return
	 * @return the accessible root-object for the given identifier or NULL
	 * 	if non such exists
	 */
	cRoot * getAccessibleRootObject( longFib lIdentifier, const cRoot *pRoot  );


	/**
	 * This method creates the propertytypelist, with the propertytypes in the
	 * order they will be counted when stored.
	 *
	 * @see storeBit()
	 * @see liStorePropertyOrder
	 */
	bool createStorePropertyOrder();

	/**
	 * This method evalues the bits needed to store a property type.
	 *
	 * @see storeBit()
	 * @see storePropertyType()
	 * @see createStorePropertyOrder()
	 * @see liStorePropertyOrder
	 */
	unsignedIntFib getBitsForStoredPropertyType() const;

	/**
	 * This method stores the given propertytype in the compressed file format.
	 *
	 * @see restorePropertyType()
	 * @see storeBit()
	 * @see createStorePropertyOrder()
	 * @see liStorePropertyOrder
	 * @param stream the stream where this Fib-object should be stored to
	 * @param cRestBits the not yet writen bits which should be stored
	 * @param uiRestBitPosition the number of bits in the cRestBits which
	 * 	should be writen respectively containing valid information
	 * @param propertyType the propertytype to store
	 * @return true if this Fib-object is stored, else false
	 */
	bool storePropertyType( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition, const cTypeProperty & propertyType ) const;

	/**
	 * This method restores a propertytype from a stream in the compressed file format.
	 *
	 * @see storePropertyType()
	 * @see storeBit()
	 * @see createStorePropertyOrder()
	 * @see liStorePropertyOrder
	 * @param iBitStream the stream where this propertytype is stored to in,
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
	 * @return the restored property or the propertytype NONE if it couldn't be restored
	 */
	cTypeProperty restorePropertyType( cReadBits & iBitStream, intFib & outStatus ) const;
	
	
	/**
	 * This method exports the comment values into the optional part.
	 * It also enumerates the comments.
	 * This functionality is for compressed storing of an Fib object.
	 * @see storeBit()
	 * @see cRoot( cReadBits & iBitStream, intFib & outStatus, cRoot * pNextRoot )
	 * @return a pointer to an optional part with the comments texts in it;
	 * 	Beware: You have to delete it after usage
	 */
	cOptionalPart * exportCommentsIntoOptionalPart();

	/**
	 * This method removes all comment values from the optional part,
	 * which wher stored ther for compressed storing.
	 * It will also put the extracted comments into ther commentelements.
	 * @see vecComments
	 * @see getCommentValues()
	 * @see storeBit()
	 * @see cRoot( cReadBits & iBitStream, intFib & outStatus, cRoot * pNextRoot )
	 */
	void extractCommentsFromOptionalPart();

	
	/**
	 * This method copies the connected object with the given number in the
	 * order of connected objects.
	 * For this every Fib-element, beginning from this Fib-element, that
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
	virtual cRoot * copyInternal( const unsignedIntFib iObjectPoint=0 ) const;

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
	
	
	/**
	 * This method returns the extern object element which calls /uses this
	 * root-object.
	 *
	 * @see liPExtObjectElm
	 * @see setCallingFibElement()
	 * @see unsetCallingFibElement()
	 * @see cExtObject
	 * @see evalueObject()
	 * @return extern object element which calls /uses this root-object
	 * 	(if NULL non exists)
	 */
	cExtObject * getCallingExtObject();

	/**
	 * This method sets the given extern object element as the element
	 * which calls /uses this root-object.
	 *
	 * @see liPExtObjectElm
	 * @see unsetCallingFibElement()
	 * @see cExtObject
	 * @see evalueObject()
	 * @param pInExtObjectElm extern object element which calls /uses this
	 * 	root-object (if NULL @see unsetCallingFibElement() will be called)
	 */
	void setCallingFibElement( cExtObject * pInExtObjectElm );
	
	/**
	 * This Method unsets the actual calling / using Fib-element.
	 * @see liPExtObjectElm
	 * @see setCallingFibElement()
	 * @see evalueObject()
	 */
	void unsetCallingFibElement();
	
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

};
}//namespace fib

#endif //___C_ROOT_H__






