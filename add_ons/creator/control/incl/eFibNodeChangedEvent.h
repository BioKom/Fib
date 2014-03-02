
//TODO check

/**
 * @file eFibNodeChangedEvent
 * file name: eFibNodeChangedEvent.h
 * @author Betti Oesterholz
 * @date 12.06.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a event for Fib object node changes.
 *
 *
 * Copyright (C) @c GPL3 2013 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (GPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This file specifies a event for Fib object node changes.
 * If a Fib object changes, the Fib object nodes (cFibNode) for it will
 * send a event of this type to all registered listeners of type.
 *
 * Use the following methods the adapt this event, so it will carry the
 * information for the node changes:
 * 	@see addChangedFibElement()
 * 	@see addChangedFibElements()
 * 	@see addChangedFibObject()
 * 	@see addChangedFibObjects()
 * 	@see setJustValuesChanged()
 * 	@see setDeleted()
 *
 * If Fib elements are changed just their content changes, but not the
 * Fib object structure (so the Fib element subobjects also stay the same).
 * If Fib objects changes the Fib element structure changes. A changed
 * Fib object is the pointer to the defining Fib element of the first
 * Fib part object, which contains the changed Fib element structure.
 *
 * Make sure to mark every delted Fib element as DELETED:
 * 	- call addChangedFibElement*( *, DELETED ) with their pointers
 * 	- call addChangedFibObject*( *, DELETED ) with the delted Fib object
 * 		pointer, befor the Fib object is deleted from memory
 *
 * Note: If the Fib node gets invalid (the Fib object for it gets
 * deleted), this event will be obsolete and will change to a node
 * deleted event.
 *
 * @pattern event
 * @see cFibNode
 * @see addChangedFibElement()
 * @see addChangedFibElements()
 * @see addChangedFibObject()
 * @see addChangedFibObjects()
 * @see lFibNodeChanged
 */
/*
History:
12.06.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__E_FIB_NODE_CHANGED_EVENT_H__
#define ___FIB__NCREATOR__E_FIB_NODE_CHANGED_EVENT_H__


#include "version.h"

#include <string>
#include <set>
#include <list>
#include <map>

#include <QObject>
#include <QMutex>

#include "cFibElement.h"

#include "eObjectDeleted.h"
#include "lFibNodeChanged.h"


namespace fib{

namespace nCreator{

//cyclic dependencies
class cFibNode;

class eFibNodeChangedEvent: public eObjectDeleted< cFibNode >,
	public lFibNodeChanged {
public:
	
	
	/**
	 * This type (enum) is for the change type.
	 */
	enum typeChange{
		NONE = 0,///nothing changed
		ALL  = 1,///everything changed or no specific change type
		CHANGED = 2,/**if Fib element: the content of the Fib element changed (
			but not the type or its subobjects)*/
		DELETED = 3,/**Fib element or Fib object was deleted:
			- deleted Fib elements or objects do not exists anymore, so their
			  pointers or numbers can not be returned*/
		ADDED = 4,/**a Fib element or Fib object was added
			- Fib elements in which they where added as a subobject, will be
			  also marked as ADDED*/
		MOVED = 5,/**a Fib element or Fib object was moved
			- Fib elements from which and to which they where moved as a
			  subobject, will be also marked as REMOVED and ADDED respectively*/
		REMOVED = 6/**a Fib element or Fib object was removed from the Fib element
			- the next superior Fib element from which a Fib element or object
			  was deleted, will be marked with REMOVED
			- the Fib element from wich a subobject was deleted, will be
			  marked with REMOVED*/
	};
	
	/**
	 * constructor
	 *
	 * @param pInFibNode a pointer to the Fib node that was changed
	 * 	@see pFibNodeChanged
	 * 	@see pObject
	 * @param ulInVersion the version of the Fib object for the node, for
	 * 	this event;
	 * 	@see cFibNode::getFibObjectVersion()
	 * @param pInChangedBy a pointer to the object which had changed the Fib node
	 * 	@see pChangedBy
	 */
	eFibNodeChangedEvent( cFibNode * pInFibNode,
		const unsigned long ulInVersion,
		const QObject * pInChangedBy );
	
	/**
	 * copy constructor
	 *
	 * @param fibNodeChangedEvent the Fib node change event to copy
	 */
	explicit eFibNodeChangedEvent( const eFibNodeChangedEvent & fibNodeChangedEvent );
	
	/**
	 * destructor
	 */
	virtual ~eFibNodeChangedEvent();
	
	/**
	 * This method sets the object for this event.
	 *
	 * @param pInFibNode a pointer to the Fib node that was changed
	 * 	@see pObject
	 */
	void setObject( cFibNode * pInFibNode );
	
	/**
	 * This method adds a changed Fib element.
	 * Note: If you move some Fib elements (MOVED), set also the changed
	 * 	"from Fib element" as DELETED seperatly. (The moved to Fib element
	 * 	will be set to ADDED automaticly.)
	 *
	 * @see mapChangedFibElements
	 * @param pChangedFibElement a pointer to a changed Fib element
	 * @param changeType the type of change for the Fib element
	 */
	void addChangedFibElement( const cFibElement * pChangedFibElement,
		const typeChange changeType = CHANGED );
	
	/**
	 * This method adds some changed Fib elements.
	 * Note: If you move some Fib elements (MOVED), set also the changed
	 * 	"from Fib element" as DELETED seperatly. (The moved to Fib element
	 * 	will be set to ADDED automaticly.)
	 *
	 * @see mapChangedFibElements
	 * @param setChangedFibElements the set with the pointers to the changed
	 * 	Fib elements
	 * @param changeType the type of change for the Fib elements
	 */
	void addChangedFibElements( const std::set< const cFibElement * > & setChangedFibElements,
		const typeChange changeType = CHANGED );
	
	/**
	 * This method adds some changed Fib elements.
	 * Note: If you move some Fib elements (MOVED), set also the changed
	 * 	"from Fib element" as DELETED seperatly. (The moved to Fib element
	 * 	will be set to ADDED automaticly.)
	 *
	 * @see mapChangedFibElements
	 * @param setChangedFibElements the set with the pointers to the changed
	 * 	Fib elements
	 * @param changeType the type of change for the Fib elements
	 */
	void addChangedFibElements( const std::set< cFibElement * > & setChangedFibElements,
		const typeChange changeType = CHANGED ); /*{
		//TODO is reinterpret_cast is not a good idea (unknown behavior)
		addChangedFibElements( reinterpret_cast< set< const cFibElement * > & >(
			setChangedFibElements), changeType );
	}*/
	
	/**
	 * This method adds some changed Fib elements.
	 * Note: If you move some Fib elements (MOVED), set also the changed
	 * 	"from Fib element" as DELETED seperatly. (The moved to Fib element
	 * 	will be set to ADDED automaticly.)
	 *
	 * @see mapChangedFibElements
	 * @param liChangedFibElements the list with the pointers to the changed
	 * 	Fib elements
	 * @param changeType the type of change for the Fib elements
	 */
	void addChangedFibElements( const std::list< const cFibElement * > & liChangedFibElements,
		const typeChange changeType = CHANGED );
	
	/**
	 * This method adds some changed Fib elements.
	 * Note: If you move some Fib elements (MOVED), set also the changed
	 * 	"from Fib element" as DELETED seperatly. (The moved to Fib element
	 * 	will be set to ADDED automaticly.)
	 *
	 * @see mapChangedFibElements
	 * @param liChangedFibElements the list with the pointers to the changed
	 * 	Fib elements
	 * @param changeType the type of change for the Fib elements
	 */
	void addChangedFibElements( const std::list< cFibElement * > & liChangedFibElements,
		const typeChange changeType = CHANGED );
	
	
	/**
	 * This method adds a changed Fib object.
	 * Note: If you move some Fib objects (MOVED), set also the changed
	 * 	"from Fib element" as DELETED seperatly. (The moved to Fib element
	 * 	will be set to ADDED automaticly.)
	 *
	 * @see mapChangedFibObjects
	 * @param pChangedFibElement a pointer to a changed Fib object
	 * @param changeType the type of change for the Fib object
	 */
	void addChangedFibObject( const cFibElement * pChangedFibObject,
		const typeChange changeType = CHANGED );
	
	/**
	 * This method adds some changed Fib objects.
	 * Note: If you move some Fib objects (MOVED), set also the changed
	 * 	"from Fib element" as DELETED seperatly. (The moved to Fib element
	 * 	will be set to ADDED automaticly.)
	 *
	 * @see mapChangedFibObjects
	 * @param setChangedFibElements the set with the pointers to the changed
	 * 	Fib objects
	 * @param changeType the type of change for the Fib objects
	 */
	void addChangedFibObjects( const std::set< const cFibElement * > & setChangedFibObjects,
		const typeChange changeType = CHANGED );
	
	/**
	 * This method adds some changed Fib objects.
	 * Note: If you move some Fib objects (MOVED), set also the changed
	 * 	"from Fib element" as DELETED seperatly. (The moved to Fib element
	 * 	will be set to ADDED automaticly.)
	 *
	 * @see mapChangedFibObjects
	 * @param setChangedFibElements the set with the pointers to the changed
	 * 	Fib objects
	 * @param changeType the type of change for the Fib objects
	 */
	void addChangedFibObjects( const std::set< cFibElement * > & setChangedFibObjects,
		const typeChange changeType = CHANGED );
	
	
	/**
	 * This method sets that just values have changed.
	 * So you can speed up the adaption for the change.
	 * Note: You can't set it, if Fib objects where changed or other change
	 * 	types as CHANGED exists.
	 *
	 * @see bJustValuesChanged
	 * @see isJustValuesChanged()
	 * @param bInJustValuesChanged if true, it should be set, that just values
	 * 	have changed
	 * @return true if just values have changed, else false
	 */
	bool setJustValuesChanged( const bool bInJustValuesChanged = true );
	
	
	/**
	 * @return the name of this class "eFibNodeChangedEvent"
	 */
	std::string getName() const;
	
	/**
	 * @see setChangedNode()
	 * @see setObject()
	 * @return a pointer to the node that was changed
	 * 	@see pFibNodeChanged
	 */
	const cFibNode * getChangedNode() const;
	
	/**
	 * @see setChangedNode()
	 * @see setObject()
	 * @return a pointer to the node that was changed
	 * 	@see pFibNodeChanged
	 */
	cFibNode * getChangedNode();
	
	/**
	 * This method changes the Fib node for this event.
	 *
	 * @see pFibNodeChanged
	 * @see pObject
	 * @see getChangedNode()
	 * @see setObject()
	 * @param pFibNodeChanged a pointer to the node that was changed
	 */
	void setChangedNode( cFibNode * pFibNodeChanged );
	
	/**
	 * @see setChangeNodeVersion()
	 * @return the version of the Fib object for the node, when this event
	 * 	was generated
	 * 	@see ulVersion
	 */
	unsigned long getChangeNodeVersion() const;
	
	/**
	 * This method sets the Fib object version number (of the Fib node)
	 * for this event.
	 *
	 * @see ulVersion
	 * @see getChangeNodeVersion();
	 * @param ulChangeNodeVersion the version of the Fib object for the
	 * 	node, for this event
	 */
	void setChangeNodeVersion( const unsigned long ulChangeNodeVersion );
	
	/**
	 * @see setChangeBy()
	 * @return a pointer to the object, which had changed the Fib node or NULL
	 * 	@see pChangedBy
	 */
	const QObject * getChangeBy() const;
	
	/**
	 * This method sets by which object the Fib object for the Fib node was
	 * changed.
	 *
	 * @see pChangedBy
	 * @see getChangeBy()
	 * @param pInChangedBy a pointer to the object, which had changed the
	 * 	Fib node or NULL
	 */
	void setChangeBy( QObject * pInChangedBy );
	
	/**
	 * Event method
	 * It will be called every time a Fib node (cFibNode), at which
	 * this object is registered, was changed.
	 *
	 * @param pFibNode a pointer to the changed Fib node
	 */
	virtual void fibNodeChangedEvent(
		const eFibNodeChangedEvent * pFibNodeChanged );
	
	
	/**
	 * @see mapChangedFibElements
	 * @param pFibElement a pointer to the Fib element for which to check,
	 * 	if it was changed in the changed type changeType
	 * @param changeType the type of change, for the Fib element
	 * @return true if the given Fib element was changed, else false;
	 * 	(Note: If the node was deleted (DELETED) true will be returned.)
	 */
	bool isElementChanged( const cFibElement * pFibElement,
		const typeChange changeType = ALL ) const;
	
	/**
	 * @see mapChangedFibElements
	 * @return the change type of the given Fib element;
	 * 	(Note: If the node was deleted DELETED will be returned.)
	 * 	@see typeChange
	 */
	typeChange getElementChangeType( const cFibElement * pFibElement ) const;
	
	/**
	 * @see mapChangedFibElements
	 * @param changeType the type of change, for the Fib elements to count
	 * @return the number of changed Fib elements
	 */
	unsigned int getNumberOfChangedFibElements(
		const typeChange changeType = ALL ) const;
	
	/**
	 * This method returns all Fib elements, which where changed in the given
	 * change type changeType.
	 *
	 * @see mapChangedFibElements
	 * @see addChangedFibElement()
	 * @see addChangedFibElements()
	 * @see isElementChanged()
	 * @see getElementChangeType()
	 * @param changeType the type of change, for which all Fib elements
	 * 	should be returned
	 * @return a set with the pointers for all changed Fib elements for the
	 * 	given change type
	 */
	const std::set< const cFibElement * > getChangedFibElements(
		const typeChange changeType = ALL ) const;
	

	/**
	 * @see mapChangedFibObjects
	 * @param pFibObject a pointer to the Fib object for which to check,
	 * 	if it was changed in the changed type changeType
	 * @param changeType the type of change, for the Fib object
	 * @return true if the given Fib objects was changed, else false;
	 * 	(Note: If the node was deleted (DELETED) true will be returned.)
	 */
	bool isObjectChanged( const cFibElement * pFibObject,
		const typeChange changeType = ALL ) const;
	
	/**
	 * @see mapChangedFibObjects
	 * @return the change type of the given Fib object;
	 * 	(Note: If the node was deleted DELETED will be returned.)
	 * 	@see typeChange
	 */
	typeChange getObjectChangeType( const cFibElement * pFibObject ) const;
	
	/**
	 * @see mapChangedFibObjects
	 * @param changeType the type of change, for the Fib objects to count
	 * @return the number of changed Fib objects
	 */
	unsigned int getNumberOfChangedFibObjects(
		const typeChange changeType = ALL ) const;
	
	/**
	 * This method returns all Fib objects, which where changed in the given
	 * change type changeType.
	 *
	 * @see mapChangedFibObjects
	 * @see addChangedFibObject()
	 * @see addChangedFibObjects()
	 * @see isObjectChanged()
	 * @see getObjectChangeType()
	 * @param changeType the type of change, for which all Fib objects should
	 * 	be returned
	 * @return a set with the pointers for all changed Fib objects for the
	 * 	given change type
	 */
	const std::set< const cFibElement * > getChangedFibObjects(
		const typeChange changeType = ALL ) const;
	
	
	/**
	 * @see bJustValuesChanged
	 * @see setJustValuesChanged()
	 * @return true if just values in Fib elements where changed, else false
	 */
	bool isJustValuesChanged() const;
	
	/**
	 * @see bJustValuesChanged
	 * @see setJustValuesChanged()
	 * @see mapChangedFibElements
	 * @return true if just Fib elements changed, but not the Fib element
	 * 	structure, else false;
	 * 	(if true no other change type as CHANGED for Fib elements exists)
	 */
	bool isJustFibElementsChanged() const;
	
	
	/**
	 * This method checks if the given Fib element is on the same branch as
	 * a changed Fib element or Fib object.
	 * A Fib element is on the same branch as an changed Fib element, if it
	 * is superior to it, contained in it or if it is the changed Fib element.
	 *
	 * @see isSuperiorToChanged()
	 * @see isContainedInChanged()
	 * @see isElementChanged()
	 * @see isObjectChanged()
	 * @param pFibElement a pointer to a Fib element, for which to check, if
	 * 	it is on the same branch as a changed Fib element or Fib object
	 * @param changeType the change type of the changed Fib element or
	 * 	Fib object, with which the given Fib element pFibElement should be
	 * 	on the same branch
	 * @return true if the given Fib element is on the same branch as a
	 * 	changed Fib element or Fib object, else false
	 * 	( isSuperiorToChanged() || isContainedInChanged() ||
	 * 		isElementChanged() || isObjectChanged() )
	 */
	bool isChangedBranch( const cFibElement * pFibElement,
		const typeChange changeType = ALL ) const;
	
	/**
	 * This method checks if the given Fib element is a superior Fib element
	 * to a changed Fib element or Fib object.
	 * Note: Changed Fib elements are just superior in this sense, if they
	 * 	contain a changed Fib element or Fib object.
	 *
	 * @see mapChangedFibElements
	 * @see getChangedFibElements()
	 * @see getChangedFibObjects()
	 * @see isContainedInChanged()
	 * @see isSuperiorToChangedElement()
	 * @see isSuperiorToChangedObject()
	 * @see mapSuperiorToChangedFibElements
	 * @see mapNotSuperiorToChangedFibElements
	 * @see mapSuperiorToChangedFibObjects
	 * @see mapNotSuperiorToChangedFibObjects
	 * @param pFibElement a pointer to a Fib element, for which to check, if
	 * 	it is a superior Fib element to a changed Fib element or Fib object
	 * @param changeType the change type of the changed Fib element or
	 * 	Fib object, to which the given Fib element pFibElement should be
	 * 	superior
	 * @return true if the given Fib element is a superior Fib element to a
	 * 	changed Fib element or Fib object, else false
	 * 	( isSuperiorToChangedElement() || isSuperiorToChangedObject() )
	 */
	bool isSuperiorToChanged( const cFibElement * pFibElement,
		const typeChange changeType = ALL ) const;
	
	/**
	 * This method checks if the given Fib element is contained in a changed
	 * Fib element or Fib object.
	 * Note: Changed Fib elements are just contained in this sense, if they
	 * 	are contain in a changed Fib element or Fib object.
	 *
	 * @see mapChangedFibElements
	 * @see getChangedFibElements()
	 * @see getChangedFibObjects()
	 * @see isSuperiorToChanged()
	 * @see isContainedInChangedElement()
	 * @see isContainedInChangedObject()
	 * @see mapSuperiorToChangedFibElements
	 * @see mapNotSuperiorToChangedFibElements
	 * @see mapSuperiorToChangedFibObjects
	 * @see mapNotSuperiorToChangedFibObjects
	 * @param pFibElement a pointer to a Fib element, for which to check, if
	 * 	it is contained in a changed Fib element or Fib object
	 * @param changeType the change type of the changed Fib element or
	 * 	Fib object, in which the given Fib element pFibElement should be
	 * 	contained
	 * @return true if the given Fib element is contained in a changed
	 * 	Fib element or Fib object, else false
	 * 	( isContainedInChangedElement() || isContainedInChangedObject() )
	 */
	bool isContainedInChanged( const cFibElement * pFibElement,
		const typeChange changeType = ALL ) const;
	
	
	/**
	 * This method checks if the given Fib element is on the same branch as
	 * a changed Fib element.
	 * A Fib element is on the same branch as an changed Fib element, if it
	 * is superior to it, contained in it or if it is the changed Fib element.
	 *
	 * @see isSuperiorToChangedElement()
	 * @see isContainedInChangedElement()
	 * @see isElementChanged()
	 * @param pFibElement a pointer to a Fib element, for which to check, if
	 * 	it is on the same branch as a changed Fib element
	 * @param changeType the change type of the changed Fib element, with
	 * 	which the given Fib element pFibElement should be on the same branch
	 * @return true if the given Fib element is on the same branch as a
	 * 	changed Fib element, else false
	 * 	( isSuperiorToChangedElement() || isContainedInChangedElement() ||
	 * 		isElementChanged() )
	 */
	bool isChangedElementBranch( const cFibElement * pFibElement,
		const typeChange changeType = ALL ) const;
	
	/**
	 * This method checks if the given Fib element is a superior Fib element
	 * to a changed Fib element.
	 * Note: Changed Fib elements are just superior in this sense, if they
	 * 	contain a changed Fib element.
	 *
	 * @see mapChangedFibElements
	 * @see getChangedFibElements()
	 * @see isContainedInChangedElement()
	 * @see mapSuperiorToChangedFibElements
	 * @see mapNotSuperiorToChangedFibElements
	 * @param pFibElement a pointer to a Fib element, for which to check, if
	 * 	it is a superior Fib element to a changed Fib element
	 * @param changeType the change type of the changed Fib element, to
	 * 	which the given Fib element pFibElement should be superior
	 * @return true if the given Fib element is a superior Fib element to a
	 * 	changed Fib element, else false
	 */
	bool isSuperiorToChangedElement( const cFibElement * pFibElement,
		const typeChange changeType = ALL ) const;
	
	/**
	 * This method checks if the given Fib element is contained in a changed
	 * Fib element.
	 * Note: Changed Fib elements are just contained in this sense, if they
	 * 	are contain in a changed Fib element.
	 *
	 * @see mapChangedFibElements
	 * @see getChangedFibElements()
	 * @see isSuperiorToChangedElement()
	 * @see mapContainedInChangedFibElements
	 * @see mapNotContainedInChangedFibElements
	 * @param pFibElement a pointer to a Fib element, for which to check, if
	 * 	it is contained in a changed Fib element
	 * @param changeType the change type of the changed Fib element, in
	 * 	which the given Fib element pFibElement should be contained
	 * @return true if the given Fib element is contained in a changed
	 * 	Fib element, else false
	 */
	bool isContainedInChangedElement( const cFibElement * pFibElement,
		const typeChange changeType = ALL ) const;
	
	/**
	 * This method checks if the given Fib object is on the same branch as
	 * a changed Fib object.
	 * A Fib object is on the same branch as an changed Fib object, if it
	 * is superior to it, contained in it or if it is the changed Fib object.
	 *
	 * @see isSuperiorToChangedObject()
	 * @see isContainedInChangedObject()
	 * @see isObjectChanged()
	 * @param pFibObject a pointer to a Fib object, for which to check, if
	 * 	it is on the same branch as a changed Fib object
	 * @param changeType the change type of the changed Fib object, with
	 * 	which the given Fib object pFibObject should be on the same branch
	 * @return true if the given Fib object is on the same branch as a
	 * 	changed Fib object, else false
	 * 	( isSuperiorToChangedObject() || isContainedInChangedObject() ||
	 * 		isObjectChanged() )
	 */
	bool isChangedObjectBranch( const cFibElement * pFibObject,
		const typeChange changeType = ALL ) const;
	
	/**
	 * This method checks if the given Fib element is a superior Fib element
	 * to a changed Fib object.
	 * Note: Changed Fib objects are just superior in this sense, if they
	 * 	contain a changed Fib object.
	 *
	 * @see mapChangedFibObjects
	 * @see getChangedFibObjects()
	 * @see isContainedInChangedObject()
	 * @see mapSuperiorToChangedFibObjects
	 * @see mapNotSuperiorToChangedFibObjects
	 * @param pFibElement a pointer to a Fib element, for which to check, if
	 * 	it is a superior Fib element to a changed Fib object
	 * @param changeType the change type of the changed Fib object, to
	 * 	which the given Fib element pFibElement should be superior
	 * @return true if the given Fib element is a superior Fib element to a
	 * 	changed Fib object, else false
	 */
	bool isSuperiorToChangedObject( const cFibElement * pFibElement,
		const typeChange changeType = ALL ) const;
	
	/**
	 * This method checks if the given Fib element is contained in a changed
	 * Fib object.
	 * Note: Changed Fib objects are just contained in this sense, if they
	 * 	are contain in a changed Fib object.
	 *
	 * @see mapChangedFibObjects
	 * @see getChangedFibObjects()
	 * @see isSuperiorToChangedObject()
	 * @see mapContainedInChangedFibObjects
	 * @see mapNotContainedInChangedFibObjects
	 * @param pFibElement a pointer to a Fib element, for which to check, if
	 * 	it is contained in a changed Fib object
	 * @param changeType the change type of the changed Fib object, in
	 * 	which the given Fib element pFibElement should be contained
	 * @return true if the given Fib element is contained in a changed
	 * 	Fib object, else false
	 */
	bool isContainedInChangedObject( const cFibElement * pFibElement,
		const typeChange changeType = ALL ) const;
	
	
protected:
	
	/**
	 * A ponter to the changed Fib node.
	 * Note: pFibNodeChanged should be always equal to pObject .
	 * @see pObject
	 */
	cFibNode * pFibNodeChanged;
	
	/**
	 * The version of the Fib object for the node, for this event.
	 * Every time the Fib object is changed the version number is counted up.
	 * @see getChangeNodeVersion()
	 * @see setChangeNodeVersion()
	 * @see cFibNode::getFibObjectVersion()
	 */
	unsigned long ulVersion;
	
	/**
	 * A pointer to the object, which had changed the Fib node or NULL .
	 * @see getChangeBy()
	 * @see setChangeBy()
	 */
	const QObject * pChangedBy;
	
	/**
	 * If true just values have changed, else (false, which is the default) not.
	 * Note: You can't set it, if Fib objects where changed or other change
	 * 	types as CHANGED exists.
	 * Note vector elements: All vector elements should be seen as values.
	 * 	So if you set a vector element from a value to a variable
	 * 	bJustValuesChanged can be true.
	 * @see setJustValuesChanged()
	 * @see isJustValuesChanged()
	 */
	bool bJustValuesChanged;
	
	
	/**
	 * If true just Fib elements have changed, else (false) not.
	 * @see isJustFibElementsChanged()
	 */
	bool bJustFibElementsChanged;
	
	
	/*TODO weg?
	 * Mutex for this class common members.
	 * Use it for the members:
	 * 	@see ulVersion
	 * 	@see pChangedBy
	QMutex mutexFibNodeChangedEvent;
	 */
	
	
	/**
	 * The map with the pointers to the changed Fib objects.
	 * 	key: The type of the change.
	 * 	value: A set with the pointers to the changed Fib elements,
	 * 		which were changed by the key change type.
	 * 		If the change type is ALL the set should contain all
	 * 		Fib elements of all other key sets.
	 * 		There should be no set for the type NONE .
	 *
	 * @see mutexChangedFibElements
	 * @see mapSuperiorToChangedFibElements
	 * @see mapNotSuperiorToChangedFibElements
	 * @see mapContainedInChangedFibElements
	 * @see mapNotContainedInChangedFibElements
	 * @see isElementChanged()
	 * @see getElementChangeType()
	 * @see getNumberOfChangedFibElements()
	 * @see getChangedFibElements()
	 * @see addChangedFibElement()
	 * @see addChangedFibElements()
	 */
	std::map< typeChange, std::set< const cFibElement * > > mapChangedFibElements;
	
	
	/**
	 * The map with the known superior Fib elements of changed Fib elements.
	 * 	key: The type of the change.
	 * 	value: A set with the pointers to the known superior Fib elements
	 * 		of changed Fib elements, which were changed by the key change type.
	 * 		If the change type is ALL the set should contain all
	 * 		Fib elements of all other key sets.
	 * 		There should be no set for the type NONE .
	 *
	 * If you want to know if a Fib element is superior or not to a changed
	 * Fib element, first check this and the mapNotSuperiorToChangedFibElements
	 * member to evalue if it is superior. If you don't find the Fib element
	 * in the containers check the Fib object directly.
	 * The containers are for speeding up the search for superior Fib elements
	 * for changed Fib elements (it is a internal helper variable).
	 *
	 * @see mapNotSuperiorToChangedFibElements
	 * @see mutexChangedFibElements
	 * @see isSuperiorToChangedElement()
	 * @see isSuperiorToChanged()
	 * @see mapChangedFibElements
	 * @see mapContainedInChangedFibElements
	 * @see mapNotContainedInChangedFibElements
	 */
	mutable std::map< typeChange, std::set< const cFibElement * > >
		mapSuperiorToChangedFibElements;
	
	/**
	 * The map with the known not superior Fib elements of changed Fib elements.
	 * 	key: The type of the change.
	 * 	value: A set with the pointers to the known not superior Fib elements
	 * 		of changed Fib elements, which were changed by the key change type.
	 * 		If the change type is ALL the set should contain all
	 * 		Fib elements of all other key sets.
	 * 		There should be no set for the type NONE .
	 *
	 * If you want to know if a Fib element is superior or not to a changed
	 * Fib element, first check this and the mapSuperiorToChangedFibElements
	 * member to evalue if it is superior. If you don't find the Fib element
	 * in the containers check the Fib object directly.
	 * The containers are for speeding up the search for superior Fib elements
	 * for changed Fib elements (it is a internal helper variable).
	 *
	 * @see mapSuperiorToChangedFibElements
	 * @see mutexChangedFibElements
	 * @see isSuperiorToChangedElement()
	 * @see isSuperiorToChanged()
	 * @see mapChangedFibElements
	 * @see mapContainedInChangedFibElements
	 * @see mapNotContainedInChangedFibElements
	 */
	mutable std::map< typeChange, std::set< const cFibElement * > >
		mapNotSuperiorToChangedFibElements;
	
	/**
	 * The map with the known Fib elements which are contained in changed
	 * Fib elements.
	 * 	key: The type of the change.
	 * 	value: A set with the pointers to the known Fib elements which are
	 * 		contained in changed Fib elements, which were changed by the
	 * 		key change type.
	 * 		If the change type is ALL the set should contain all
	 * 		Fib elements of all other key sets.
	 * 		There should be no set for the type NONE .
	 *
	 * If you want to know if a Fib element is or is not contained in a changed
	 * Fib element, first check this and the mapNotContainedInChangedFibElements
	 * member to evalue if it is contained. If you don't find the Fib element
	 * in the containers check the Fib object directly.
	 * The containers are for speeding up the search for contained
	 * Fib elements for changed Fib elements (it is a internal helper variable).
	 *
	 * @see mapNotContainedInChangedFibElements
	 * @see mutexChangedFibElements
	 * @see isContainedInChangedElement()
	 * @see isContainedInChanged()
	 * @see mapChangedFibElements
	 * @see mapSuperiorToChangedFibElements
	 * @see mapNotSuperiorToChangedFibElements
	 */
	mutable std::map< typeChange, std::set< const cFibElement * > >
		mapContainedInChangedFibElements;
	
	/**
	 * The map with the known Fib elements which are not contained in
	 * changed Fib elements.
	 * 	key: The type of the change.
	 * 	value: A set with the pointers to the known Fib elements which are
	 * 		not contained in changed Fib elements, which were changed by
	 * 		the key change type.
	 * 		If the change type is ALL the set should contain all
	 * 		Fib elements of all other key sets.
	 * 		There should be no set for the type NONE .
	 *
	 * If you want to know if a Fib element is or is not contained in a changed
	 * Fib element, first check this and the mapNotContainedInChangedFibElements
	 * member to evalue if it is contained. If you don't find the Fib element
	 * in the containers check the Fib object directly.
	 * The containers are for speeding up the search for contained
	 * Fib elements for changed Fib elements (it is a internal helper variable).
	 *
	 * @see mapContainedInChangedFibElements
	 * @see mutexChangedFibElements
	 * @see isContainedInChangedElement()
	 * @see isContainedInChanged()
	 * @see mapChangedFibElements
	 * @see mapSuperiorToChangedFibElements
	 * @see mapNotSuperiorToChangedFibElements
	 */
	mutable std::map< typeChange, std::set< const cFibElement * > >
		mapNotContainedInChangedFibElements;
	
	
	/**
	 * Mutex for the changed Fib elements.
	 * Use it for the members:
	 * 	@see mapChangedFibElements
	 * 	@see mapSuperiorToChangedFibElements
	 * 	@see mapNotSuperiorToChangedFibElements
	 * 	@see mapContainedInChangedFibElements
	 * 	@see mapNotContainedInChangedFibElements
	 */
	mutable QMutex mutexChangedFibElements;
	
	
	/**
	 * The map with the pointers to the changed Fib objects.
	 * 	key: The type of the change.
	 * 	value: A set with the pointers to the changed Fib objects,
	 * 		which were changed by the key change type.
	 * 		If the change type is ALL the set should contain all
	 * 		Fib objects of all other key sets.
	 * 		There should be no set for the type NONE .
	 *
	 * @see mutexChangedFibObjects
	 * @see mapSuperiorToChangedFibObjects
	 * @see mapNotSuperiorToChangedFibObjects
	 * @see mapContainedInChangedFibObjects
	 * @see mapNotContainedInChangedFibObjects
	 * @see isObjectChanged()
	 * @see getObjectChangeType()
	 * @see getNumberOfChangedFibObjects()
	 * @see getChangedFibObjects()
	 * @see addChangedFibObject()
	 * @see addChangedFibObjects()
	 */
	std::map< typeChange, std::set< const cFibElement * > > mapChangedFibObjects;
	
	
	/**
	 * The map with the known superior Fib elements of changed Fib objects.
	 * 	key: The type of the change.
	 * 	value: A set with the pointers to the known superior Fib elements
	 * 		of changed Fib objects, which were changed by the key change type.
	 * 		If the change type is ALL the set should contain all
	 * 		Fib elements of all other key sets.
	 * 		There should be no set for the type NONE .
	 *
	 * If you want to know if a Fib element is superior or not to a changed
	 * Fib object, first check this and the mapNotSuperiorToChangedFibObjects
	 * member to evalue if it is superior. If you don't find the Fib element
	 * in the containers check the entire Fib object directly.
	 * The containers are for speeding up the search for superior Fib elements
	 * for changed Fib objects (it is a internal helper variable).
	 *
	 * @see mapNotSuperiorToChangedFibObjects
	 * @see mutexChangedFibObjects
	 * @see isSuperiorToChangedObject()
	 * @see isSuperiorToChanged()
	 * @see mapChangedFibObjects
	 * @see mapContainedInChangedFibObjects
	 * @see mapNotContainedInChangedFibObjects
	 */
	mutable std::map< typeChange, std::set< const cFibElement * > >
		mapSuperiorToChangedFibObjects;
	
	/**
	 * The map with the known not superior Fib elements of changed Fib objects.
	 * 	key: The type of the change.
	 * 	value: A set with the pointers to the known not superior Fib elements
	 * 		of changed Fib objects, which were changed by the key change type.
	 * 		If the change type is ALL the set should contain all
	 * 		Fib elements of all other key sets.
	 * 		There should be no set for the type NONE .
	 *
	 * If you want to know if a Fib element is superior or not to a changed
	 * Fib object, first check this and the mapSuperiorToChangedFibObjects
	 * member to evalue if it is superior. If you don't find the Fib element
	 * in the containers check the entire Fib object directly.
	 * The containers are for speeding up the search for superior Fib elements
	 * for changed Fib objects (it is a internal helper variable).
	 *
	 * @see mapSuperiorToChangedFibObjects
	 * @see mutexChangedFibObjects
	 * @see isSuperiorToChangedObject()
	 * @see isSuperiorToChanged()
	 * @see mapChangedFibObjects
	 * @see mapContainedInChangedFibObjects
	 * @see mapNotContainedInChangedFibObjects
	 */
	mutable std::map< typeChange, std::set< const cFibElement * > >
		mapNotSuperiorToChangedFibObjects;
	
	/**
	 * The map with the known Fib elements which are contained in changed
	 * Fib objects.
	 * 	key: The type of the change.
	 * 	value: A set with the pointers to the known Fib elements which are
	 * 		contained in changed Fib objects, which were changed by the
	 * 		key change type.
	 * 		If the change type is ALL the set should contain all
	 * 		Fib elements of all other key sets.
	 * 		There should be no set for the type NONE .
	 *
	 * If you want to know if a Fib element is or is not contained in a changed
	 * Fib object, first check this and the mapNotContainedInChangedFibObjects
	 * member to evalue if it is contained. If you don't find the Fib element
	 * in the containers check the entire Fib object directly.
	 * The containers are for speeding up the search for contained
	 * Fib elements for changed Fib objects (it is a internal helper variable).
	 *
	 * @see mapNotContainedInChangedFibObjects
	 * @see mutexChangedFibObjects
	 * @see isContainedInChangedObject()
	 * @see isContainedInChanged()
	 * @see mapChangedFibObjects
	 * @see mapSuperiorToChangedFibObjects
	 * @see mapNotSuperiorToChangedFibObjects
	 */
	mutable std::map< typeChange, std::set< const cFibElement * > >
		mapContainedInChangedFibObjects;
	
	/**
	 * The map with the known Fib elements which are not contained in
	 * changed Fib objects.
	 * 	key: The type of the change.
	 * 	value: A set with the pointers to the known Fib elements which are
	 * 		not contained in changed Fib objects, which were changed by
	 * 		the key change type.
	 * 		If the change type is ALL the set should contain all
	 * 		Fib elements of all other key sets.
	 * 		There should be no set for the type NONE .
	 *
	 * If you want to know if a Fib element is or is not contained in a changed
	 * Fib object, first check this and the mapNotContainedInChangedFibObjects
	 * member to evalue if it is contained. If you don't find the Fib element
	 * in the containers check the entire Fib object directly.
	 * The containers are for speeding up the search for contained
	 * Fib elements for changed Fib objects (it is a internal helper variable).
	 *
	 * @see mapContainedInChangedFibObjects
	 * @see mutexChangedFibObjects
	 * @see isContainedInChangedObject()
	 * @see isContainedInChanged()
	 * @see mapChangedFibObjects
	 * @see mapSuperiorToChangedFibObjects
	 * @see mapNotSuperiorToChangedFibObjects
	 */
	mutable std::map< typeChange, std::set< const cFibElement * > >
		mapNotContainedInChangedFibObjects;
	
	
	/**
	 * Mutex for the changed Fib objects.
	 * If used together use inside mutexChangedFibElements.
	 * Use it for the members:
	 * 	@see mapChangedFibObjects
	 * 	@see mapSuperiorToChangedFibObjects
	 * 	@see mapNotSuperiorToChangedFibObjects
	 * 	@see mapContainedInChangedFibObjects
	 * 	@see mapNotContainedInChangedFibObjects
	 * @see mutexChangedFibElements
	 */
	mutable QMutex mutexChangedFibObjects;
	
	
};//end class eFibNodeChangedEvent

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__E_FIB_NODE_CHANGED_EVENT_H__





