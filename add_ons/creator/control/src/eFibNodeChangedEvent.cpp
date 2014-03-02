
//TODO check

/**
 * @file eFibNodeChangedEvent
 * file name: eFibNodeChangedEvent.cpp
 * @author Betti Oesterholz
 * @date 12.06.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a event for Fib object node changes.
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
 * 		pointer, before the Fib object is deleted from memory
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


#include "eFibNodeChangedEvent.h"

#include "cFibNode.h"


using namespace std;
using namespace fib::nCreator;


/**
 * constructor
 *
 * @param pInFibNode a pointer to the Fib node that was changed
 * 	@see pFibNodeChanged
 * 	@see pObject
 * @param ulInVersion the version of the Fib object for the node, when
 * 	this event was generated;
 * 	@see cFibNode::getFibObjectVersion()
 * @param pInChangedBy a pointer to the object which had changed the Fib node
 * 	@see pChangedBy
 */
eFibNodeChangedEvent::eFibNodeChangedEvent( cFibNode * pInFibNode,
	const unsigned long ulInVersion,
	const QObject * pInChangedBy ):
		eObjectDeleted( pInFibNode, false ), pFibNodeChanged( pInFibNode ),
		ulVersion( ulInVersion ), pChangedBy( pInChangedBy ),
		bJustValuesChanged( false ), bJustFibElementsChanged( true ) {
	
	if ( pInFibNode ) {
		//register as node change listener
		pInFibNode->registerNodeChangeListener( this );
	}
	
}

/**
 * copy constructor
 *
 * @param fibNodeChangedEvent the Fib node change event to copy
 */
eFibNodeChangedEvent::eFibNodeChangedEvent(
		const eFibNodeChangedEvent & fibNodeChangedEvent ):
		eObjectDeleted( fibNodeChangedEvent.getObject(),
			fibNodeChangedEvent.isDeleted() ),
		pFibNodeChanged( fibNodeChangedEvent.pFibNodeChanged ),
		ulVersion( fibNodeChangedEvent.getChangeNodeVersion() ),
		pChangedBy( fibNodeChangedEvent.getChangeBy() ),
		bJustValuesChanged( fibNodeChangedEvent.isJustValuesChanged() ),
		bJustFibElementsChanged( fibNodeChangedEvent.isJustFibElementsChanged() ) {
	
	if ( pFibNodeChanged ) {
		//register as node change listener
		pFibNodeChanged->registerNodeChangeListener( this );
	}
	
	mutexChangedFibElements.lock();
	fibNodeChangedEvent.mutexChangedFibElements.lock();
	mapChangedFibElements = fibNodeChangedEvent.mapChangedFibElements;
	mapSuperiorToChangedFibElements     =
		fibNodeChangedEvent.mapSuperiorToChangedFibElements;
	mapNotSuperiorToChangedFibElements  =
		fibNodeChangedEvent.mapNotSuperiorToChangedFibElements;
	mapContainedInChangedFibElements    =
		fibNodeChangedEvent.mapContainedInChangedFibElements;
	mapNotContainedInChangedFibElements =
		fibNodeChangedEvent.mapNotContainedInChangedFibElements;
	fibNodeChangedEvent.mutexChangedFibElements.unlock();
	mutexChangedFibElements.unlock();
	
	mutexChangedFibObjects.lock();
	fibNodeChangedEvent.mutexChangedFibObjects.lock();
	mapChangedFibObjects = fibNodeChangedEvent.mapChangedFibObjects;
	mapSuperiorToChangedFibObjects =
		fibNodeChangedEvent.mapSuperiorToChangedFibObjects;
	mapNotSuperiorToChangedFibObjects =
		fibNodeChangedEvent.mapNotSuperiorToChangedFibObjects;
	mapContainedInChangedFibObjects =
		fibNodeChangedEvent.mapContainedInChangedFibObjects;
	mapNotContainedInChangedFibObjects =
		fibNodeChangedEvent.mapNotContainedInChangedFibObjects;
	fibNodeChangedEvent.mutexChangedFibObjects.unlock();
	mutexChangedFibObjects.unlock();
}


/**
 * destructor
 */
eFibNodeChangedEvent::~eFibNodeChangedEvent(){
	
	if ( pFibNodeChanged ) {
		//unregister as node change listener
		pFibNodeChanged->unregisterNodeChangeListener( this );
	}
}


/**
 * @see setChangedNode()
 * @return a pointer to the node that was changed
 * 	@see pObject
 */
const cFibNode * eFibNodeChangedEvent::getChangedNode() const {
	
	return pFibNodeChanged;
}


/**
 * @see setChangedNode()
 * @return a pointer to the node that was changed
 * 	@see pObject
 */
cFibNode * eFibNodeChangedEvent::getChangedNode() {
	
	return pFibNodeChanged;
}



/**
 * This method sets the object for this event.
 *
 * @see pObject
 * @see pFibNodeChanged
 * @param pInFibNode a pointer to the Fib node that was changed
 */
void eFibNodeChangedEvent::setObject( cFibNode * pInFibNode ) {
	
	if ( pFibNodeChanged == pInFibNode ) {
		//correct Fib node set allready -> nothing to do
		return;
	}
	if ( pFibNodeChanged ) {
		//unregister as node change listener at old node
		pFibNodeChanged->unregisterNodeChangeListener( this );
	}
	pFibNodeChanged = pInFibNode;
	pObject = pInFibNode;
	
	if ( pInFibNode ) {
		//register as node change listener at new node
		pInFibNode->registerNodeChangeListener( this );
	}
}


/**
 * This method changes the Fib node for this event.
 *
 * @see pFibNodeChanged
 * @see pObject
 * @see getChangedNode()
 * @param pFibNodeChanged a pointer to the node that was changed
 */
void eFibNodeChangedEvent::setChangedNode( cFibNode * pFibNodeChanged ) {
	
	return setObject( pFibNodeChanged );
}



/**
 * This method adds a changed Fib element.
 * Note: If you move some Fib elements (MOVED), set also the changed
 * 	"from Fib element" as REMOVED seperatly. (The moved to Fib element
 * 	will be set to ADDED automaticly.)
 *
 * @see mapChangedFibElements
 * @param pChangedFibElement a pointer to a changed Fib element
 * @param changeType the type of change for the Fib element
 */
void eFibNodeChangedEvent::addChangedFibElement(
		const cFibElement * pChangedFibElement, const typeChange changeType ) {
	
	if ( ( pChangedFibElement == NULL ) || ( changeType == NONE ) ) {
		//nothing changed
		return;
	}
	if ( isDeleted() ) {
		//everything changed / deleted -> don't need to update anything
		return;
	}
	mutexChangedFibElements.lock();
	/*Note: Normaly the mapNotSuperiorToChangedFibElements and
	 * mapNotContainedInChangedFibElements should be empty at this point.
	 * Because they will be evalued later, if such Fib elements are searched for*/
	if ( changeType != ALL ) {
		//add to given change type
		mapChangedFibElements[ changeType ].insert( pChangedFibElement );
		//Fib elements which where not superior could now become superior
		mapNotSuperiorToChangedFibElements[ changeType ].clear();
		mapNotContainedInChangedFibElements[ changeType ].clear();
		
		//add to change type ALL
		mapChangedFibElements[ ALL ].insert( pChangedFibElement );
		//Fib elements which where not superior could now become superior
		mapNotSuperiorToChangedFibElements[ ALL ].clear();
		mapNotContainedInChangedFibElements[ ALL ].clear();
		
		if ( changeType == MOVED ) {
			/*a Fib element was moved
			 *-> add its superior as a Fib element where something was added*/
			const cFibElement * pChangedFibElementSuperior =
				pChangedFibElement->getSuperiorFibElement();
			if ( pChangedFibElementSuperior ) {
				//add to change type ADDED
				mapChangedFibElements[ ADDED ].insert( pChangedFibElementSuperior );
				//Fib elements which where not superior could now become superior
				mapNotSuperiorToChangedFibElements[ ADDED ].clear();
				mapNotContainedInChangedFibElements[ ADDED ].clear();
			}
		}
	}else{//add to all change types
		//add to change type ALL
		mapChangedFibElements[ ALL ].insert( pChangedFibElement );
		//Fib elements which where not superior could now become superior
		mapNotSuperiorToChangedFibElements[ ALL ].clear();
		mapNotContainedInChangedFibElements[ ALL ].clear();
		
		//add to change type CHANGED
		mapChangedFibElements[ CHANGED ].insert( pChangedFibElement );
		mapNotSuperiorToChangedFibElements[ CHANGED ].clear();
		mapNotContainedInChangedFibElements[ CHANGED ].clear();
		
		//add to change type DELETED
		mapChangedFibElements[ DELETED ].insert( pChangedFibElement );
		mapNotSuperiorToChangedFibElements[ DELETED ].clear();
		mapNotContainedInChangedFibElements[ DELETED ].clear();
		
		//add to change type ADDED
		mapChangedFibElements[ ADDED ].insert( pChangedFibElement );
		mapNotSuperiorToChangedFibElements[ ADDED ].clear();
		mapNotContainedInChangedFibElements[ ADDED ].clear();
		
		//add to change type MOVED
		mapChangedFibElements[ MOVED ].insert( pChangedFibElement );
		mapNotSuperiorToChangedFibElements[ MOVED ].clear();
		mapNotContainedInChangedFibElements[ MOVED ].clear();
		
		//add to change type REMOVED
		mapChangedFibElements[ REMOVED ].insert( pChangedFibElement );
		mapNotSuperiorToChangedFibElements[ REMOVED ].clear();
		mapNotContainedInChangedFibElements[ REMOVED ].clear();
		
		
		/*a Fib element was moved
		 *-> add its superior as a Fib element where something was added*/
		const cFibElement * pChangedFibElementSuperior =
			pChangedFibElement->getSuperiorFibElement();
		if ( pChangedFibElementSuperior ) {
			//add to change type ADDED
			mapChangedFibElements[ ADDED ].insert( pChangedFibElementSuperior );
			//Fib elements which where not superior could now become superior
			mapNotSuperiorToChangedFibElements[ ADDED ].clear();
			mapNotContainedInChangedFibElements[ ADDED ].clear();
		}
	}
	
	if ( bJustValuesChanged && ( changeType != CHANGED ) ) {
		//there where other things than values changed
		bJustValuesChanged = false;
	}
	mutexChangedFibElements.unlock();
}


/**
 * This method adds some changed Fib elements.
 * Note: If you move some Fib elements (MOVED), set also the changed
 * 	"from Fib element" as REMOVED seperatly. (The moved to Fib element
 * 	will be set to ADDED automaticly.)
 *
 * @see mapChangedFibElements
 * @param setChangedFibElements the set with the pointers to the changed
 * 	Fib elements
 * @param changeType the type of change for the Fib elements
 */
void eFibNodeChangedEvent::addChangedFibElements(
		const set< const cFibElement * > & setChangedFibElements,
		const typeChange changeType ) {
	
	if ( ( setChangedFibElements.empty() ) || ( changeType == NONE ) ) {
		//nothing changed
		return;
	}
	if ( isDeleted() ) {
		//everything changed / deleted -> don't need to update anything
		return;
	}
	mutexChangedFibElements.lock();
	/*Note: Normaly the mapNotSuperiorToChangedFibElements and
	 * mapNotContainedInChangedFibElements should be empty at this point.
	 * Because they will be evalued later, if such Fib elements are searched for*/
	if ( changeType != ALL ) {
		//add to given change type
		mapChangedFibElements[ changeType ].insert(
			setChangedFibElements.begin(), setChangedFibElements.end() );
		//Fib elements which where not superior could now become superior
		mapNotSuperiorToChangedFibElements[ changeType ].clear();
		mapNotContainedInChangedFibElements[ changeType ].clear();
		
		//add to change type ALL
		mapChangedFibElements[ ALL ].insert(
			setChangedFibElements.begin(), setChangedFibElements.end() );
		//Fib elements which where not superior could now become superior
		mapNotSuperiorToChangedFibElements[ ALL ].clear();
		mapNotContainedInChangedFibElements[ ALL ].clear();
		
		if ( changeType == MOVED ) {
			/*the Fib elements where moved
			 *-> add their superior as a Fib element where something was added*/
			for ( set< const cFibElement * >::const_iterator
					itrActualFibElement = setChangedFibElements.begin();
					itrActualFibElement != setChangedFibElements.end();
					itrActualFibElement++ ) {
				const cFibElement * pChangedFibElementSuperior =
					(*itrActualFibElement)->getSuperiorFibElement();
				if ( pChangedFibElementSuperior ) {
					//add to change type ADDED
					mapChangedFibElements[ ADDED ].insert( pChangedFibElementSuperior );
					//Fib elements which where not superior could now become superior
					mapNotSuperiorToChangedFibElements[ ADDED ].clear();
					mapNotContainedInChangedFibElements[ ADDED ].clear();
				}
			}
		}
	}else{//add to all change types
		//add to change type ALL
		mapChangedFibElements[ ALL ].insert(
			setChangedFibElements.begin(), setChangedFibElements.end()  );
		//Fib elements which where not superior could now become superior
		mapNotSuperiorToChangedFibElements[ ALL ].clear();
		mapNotContainedInChangedFibElements[ ALL ].clear();
		
		//add to change type CHANGED
		mapChangedFibElements[ CHANGED ].insert(
			setChangedFibElements.begin(), setChangedFibElements.end()  );
		mapNotSuperiorToChangedFibElements[ CHANGED ].clear();
		mapNotContainedInChangedFibElements[ CHANGED ].clear();
		
		//add to change type DELETED
		mapChangedFibElements[ DELETED ].insert(
			setChangedFibElements.begin(), setChangedFibElements.end()  );
		mapNotSuperiorToChangedFibElements[ DELETED ].clear();
		mapNotContainedInChangedFibElements[ DELETED ].clear();
		
		//add to change type ADDED
		mapChangedFibElements[ ADDED ].insert(
			setChangedFibElements.begin(), setChangedFibElements.end()  );
		mapNotSuperiorToChangedFibElements[ ADDED ].clear();
		mapNotContainedInChangedFibElements[ ADDED ].clear();
		
		//add to change type MOVED
		mapChangedFibElements[ MOVED ].insert(
			setChangedFibElements.begin(), setChangedFibElements.end()  );
		mapNotSuperiorToChangedFibElements[ MOVED ].clear();
		mapNotContainedInChangedFibElements[ MOVED ].clear();
		
		//add to change type REMOVED
		mapChangedFibElements[ REMOVED ].insert(
			setChangedFibElements.begin(), setChangedFibElements.end()  );
		mapNotSuperiorToChangedFibElements[ REMOVED ].clear();
		mapNotContainedInChangedFibElements[ REMOVED ].clear();
		
		
		/*the Fib elements where moved
		 *-> add their superior as a Fib element where something was added*/
		for ( set< const cFibElement * >::const_iterator
				itrActualFibElement = setChangedFibElements.begin();
				itrActualFibElement != setChangedFibElements.end();
				itrActualFibElement++ ) {
			
			const cFibElement * pChangedFibElementSuperior =
				(*itrActualFibElement)->getSuperiorFibElement();
			if ( pChangedFibElementSuperior ) {
				//add to change type ADDED
				mapChangedFibElements[ ADDED ].insert( pChangedFibElementSuperior );
				//Fib elements which where not superior could now become superior
				mapNotSuperiorToChangedFibElements[ ADDED ].clear();
				mapNotContainedInChangedFibElements[ ADDED ].clear();
			}
		}
	}
	
	if ( bJustValuesChanged && ( changeType != CHANGED ) ) {
		//there where other things than values changed
		bJustValuesChanged = false;
	}
	mutexChangedFibElements.unlock();
}


/**
 * This method adds some changed Fib elements.
 * Note: If you move some Fib elements (MOVED), set also the changed
 * 	"from Fib element" as REMOVED seperatly. (The moved to Fib element
 * 	will be set to ADDED automaticly.)
 *
 * @see mapChangedFibElements
 * @param setChangedFibElements the set with the pointers to the changed
 * 	Fib elements
 * @param changeType the type of change for the Fib elements
 */
void eFibNodeChangedEvent::addChangedFibElements(
		const set< cFibElement * > & setChangedFibElements,
		const typeChange changeType ) {
	
	if ( ( setChangedFibElements.empty() ) || ( changeType == NONE ) ) {
		//nothing changed
		return;
	}
	if ( isDeleted() ) {
		//everything changed / deleted -> don't need to update anything
		return;
	}
	mutexChangedFibElements.lock();
	/*Note: Normaly the mapNotSuperiorToChangedFibElements and
	 * mapNotContainedInChangedFibElements should be empty at this point.
	 * Because they will be evalued later, if such Fib elements are searched for*/
	if ( changeType != ALL ) {
		//add to given change type
		mapChangedFibElements[ changeType ].insert(
			setChangedFibElements.begin(), setChangedFibElements.end() );
		//Fib elements which where not superior could now become superior
		mapNotSuperiorToChangedFibElements[ changeType ].clear();
		mapNotContainedInChangedFibElements[ changeType ].clear();
		
		//add to change type ALL
		mapChangedFibElements[ ALL ].insert(
			setChangedFibElements.begin(), setChangedFibElements.end() );
		//Fib elements which where not superior could now become superior
		mapNotSuperiorToChangedFibElements[ ALL ].clear();
		mapNotContainedInChangedFibElements[ ALL ].clear();
		
		if ( changeType == MOVED ) {
			/*the Fib elements where moved
			 *-> add their superior as a Fib element where something was added*/
			for ( set< cFibElement * >::const_iterator
					itrActualFibElement = setChangedFibElements.begin();
					itrActualFibElement != setChangedFibElements.end();
					itrActualFibElement++ ) {
				const cFibElement * pChangedFibElementSuperior =
					(*itrActualFibElement)->getSuperiorFibElement();
				if ( pChangedFibElementSuperior ) {
					//add to change type ADDED
					mapChangedFibElements[ ADDED ].insert( pChangedFibElementSuperior );
					//Fib elements which where not superior could now become superior
					mapNotSuperiorToChangedFibElements[ ADDED ].clear();
					mapNotContainedInChangedFibElements[ ADDED ].clear();
				}
			}
		}
	}else{//add to all change types
		//add to change type ALL
		mapChangedFibElements[ ALL ].insert(
			setChangedFibElements.begin(), setChangedFibElements.end()  );
		//Fib elements which where not superior could now become superior
		mapNotSuperiorToChangedFibElements[ ALL ].clear();
		mapNotContainedInChangedFibElements[ ALL ].clear();
		
		//add to change type CHANGED
		mapChangedFibElements[ CHANGED ].insert(
			setChangedFibElements.begin(), setChangedFibElements.end()  );
		mapNotSuperiorToChangedFibElements[ CHANGED ].clear();
		mapNotContainedInChangedFibElements[ CHANGED ].clear();
		
		//add to change type DELETED
		mapChangedFibElements[ DELETED ].insert(
			setChangedFibElements.begin(), setChangedFibElements.end()  );
		mapNotSuperiorToChangedFibElements[ DELETED ].clear();
		mapNotContainedInChangedFibElements[ DELETED ].clear();
		
		//add to change type ADDED
		mapChangedFibElements[ ADDED ].insert(
			setChangedFibElements.begin(), setChangedFibElements.end()  );
		mapNotSuperiorToChangedFibElements[ ADDED ].clear();
		mapNotContainedInChangedFibElements[ ADDED ].clear();
		
		//add to change type MOVED
		mapChangedFibElements[ MOVED ].insert(
			setChangedFibElements.begin(), setChangedFibElements.end()  );
		mapNotSuperiorToChangedFibElements[ MOVED ].clear();
		mapNotContainedInChangedFibElements[ MOVED ].clear();
		
		//add to change type REMOVED
		mapChangedFibElements[ REMOVED ].insert(
			setChangedFibElements.begin(), setChangedFibElements.end()  );
		mapNotSuperiorToChangedFibElements[ REMOVED ].clear();
		mapNotContainedInChangedFibElements[ REMOVED ].clear();
		
		
		/*the Fib elements where moved
		 *-> add their superior as a Fib element where something was added*/
		for ( set< cFibElement * >::const_iterator
				itrActualFibElement = setChangedFibElements.begin();
				itrActualFibElement != setChangedFibElements.end();
				itrActualFibElement++ ) {
			
			const cFibElement * pChangedFibElementSuperior =
				(*itrActualFibElement)->getSuperiorFibElement();
			if ( pChangedFibElementSuperior ) {
				//add to change type ADDED
				mapChangedFibElements[ ADDED ].insert( pChangedFibElementSuperior );
				//Fib elements which where not superior could now become superior
				mapNotSuperiorToChangedFibElements[ ADDED ].clear();
				mapNotContainedInChangedFibElements[ ADDED ].clear();
			}
		}
	}
	
	if ( bJustValuesChanged && ( changeType != CHANGED ) ) {
		//there where other things than values changed
		bJustValuesChanged = false;
	}
	mutexChangedFibElements.unlock();
}


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
void eFibNodeChangedEvent::addChangedFibElements(
		const list< const cFibElement * > & liChangedFibElements,
		const typeChange changeType ) {
	
	set< const cFibElement * > setChangedFibElements;
	setChangedFibElements.insert(
		liChangedFibElements.begin(), liChangedFibElements.end() );
	
	addChangedFibElements( setChangedFibElements, changeType );
}


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
void eFibNodeChangedEvent::addChangedFibElements(
		const list< cFibElement * > & liChangedFibElements,
		const typeChange changeType ) {
	
	set< const cFibElement * > setChangedFibElements;
	setChangedFibElements.insert(
		liChangedFibElements.begin(), liChangedFibElements.end() );
	
	addChangedFibElements( setChangedFibElements, changeType );
}


/**
 * This method adds a changed Fib object.
 * Note: If you move some Fib objects (MOVED), set also the changed
 * 	"from Fib element" as REMOVED seperatly. (The moved to Fib element
 * 	will be set to ADDED automaticly.)
 *
 * @see mapChangedFibObjects
 * @param pChangedFibElement a pointer to a changed Fib object
 * @param changeType the type of change for the Fib object
 */
void eFibNodeChangedEvent::addChangedFibObject(
		const cFibElement * pChangedFibObject, const typeChange changeType ) {
	
	if ( ( pChangedFibObject == NULL ) || ( changeType == NONE ) ) {
		//nothing changed
		return;
	}
	if ( isDeleted() ) {
		//everything changed / deleted -> don't need to update anything
		return;
	}
	mutexChangedFibObjects.lock();
	//a Fib object was changed
	bJustFibElementsChanged = false;
	/*Note: Normaly the mapNotSuperiorToChangedFibObjects and
	 * mapNotContainedInChangedFibObjects should be empty at this point.
	 * Because they will be evalued later, if such Fib objects are searched for*/
	if ( changeType != ALL ) {
		//add to given change type
		mapChangedFibObjects[ changeType ].insert( pChangedFibObject );
		//Fib objects which where not superior could now become superior
		mapNotSuperiorToChangedFibObjects[ changeType ].clear();
		mapNotContainedInChangedFibObjects[ changeType ].clear();
		
		//add to change type ALL
		mapChangedFibObjects[ ALL ].insert( pChangedFibObject );
		//Fib objects which where not superior could now become superior
		mapNotSuperiorToChangedFibObjects[ ALL ].clear();
		mapNotContainedInChangedFibObjects[ ALL ].clear();
		
		if ( changeType == MOVED ) {
			/*a Fib object was moved
			 *-> add its superior as a Fib element where something was added*/
			const cFibElement * pChangedFibObjectSuperior =
				pChangedFibObject->getSuperiorFibElement();
			if ( pChangedFibObjectSuperior ) {
				//add to change type ADDED
				mapChangedFibElements[ ADDED ].insert( pChangedFibObjectSuperior );
				//Fib elements which where not superior could now become superior
				mapNotSuperiorToChangedFibElements[ ADDED ].clear();
				mapNotContainedInChangedFibElements[ ADDED ].clear();
			}
		}
	}else{//add to all change types
		//add to change type ALL
		mapChangedFibObjects[ ALL ].insert( pChangedFibObject );
		//Fib objects which where not superior could now become superior
		mapNotSuperiorToChangedFibObjects[ ALL ].clear();
		mapNotContainedInChangedFibObjects[ ALL ].clear();
		
		//add to change type CHANGED
		mapChangedFibObjects[ CHANGED ].insert( pChangedFibObject );
		mapNotSuperiorToChangedFibObjects[ CHANGED ].clear();
		mapNotContainedInChangedFibObjects[ CHANGED ].clear();
		
		//add to change type DELETED
		mapChangedFibObjects[ DELETED ].insert( pChangedFibObject );
		mapNotSuperiorToChangedFibObjects[ DELETED ].clear();
		mapNotContainedInChangedFibObjects[ DELETED ].clear();
		
		//add to change type ADDED
		mapChangedFibObjects[ ADDED ].insert( pChangedFibObject );
		mapNotSuperiorToChangedFibObjects[ ADDED ].clear();
		mapNotContainedInChangedFibObjects[ ADDED ].clear();
		
		//add to change type MOVED
		mapChangedFibObjects[ MOVED ].insert( pChangedFibObject );
		mapNotSuperiorToChangedFibObjects[ MOVED ].clear();
		mapNotContainedInChangedFibObjects[ MOVED ].clear();
		
		//add to change type REMOVED
		mapChangedFibObjects[ REMOVED ].insert( pChangedFibObject );
		mapNotSuperiorToChangedFibObjects[ REMOVED ].clear();
		mapNotContainedInChangedFibObjects[ REMOVED ].clear();
		
		
		/*a Fib object was moved
		 *-> add its superior as a Fib element where something was added*/
		const cFibElement * pChangedFibObjectSuperior =
			pChangedFibObject->getSuperiorFibElement();
		if ( pChangedFibObjectSuperior ) {
			//add to change type ADDED
			mapChangedFibElements[ ADDED ].insert( pChangedFibObjectSuperior );
			//Fib elements which where not superior could now become superior
			mapNotSuperiorToChangedFibElements[ ADDED ].clear();
			mapNotContainedInChangedFibElements[ ADDED ].clear();
		}
	}
	//there where other things than values changed
	bJustValuesChanged = false;
	
	mutexChangedFibObjects.unlock();
	
	if ( ( changeType == DELETED ) || ( changeType == ALL ) ) {
		//add all contained Fib elements as removed
		set< const cFibElement * > setDeletedFibElements;
		list< const cFibElement * > liToCheckSubobjects;
		
		liToCheckSubobjects.push_back( pChangedFibObject );
		
		const cFibElement * pActualSubobject;
		while ( ! liToCheckSubobjects.empty() ) {
			pActualSubobject = liToCheckSubobjects.front();
			liToCheckSubobjects.pop_front();
			if ( pActualSubobject == NULL ) {
				//not a valid subobject
				continue;
			}
			setDeletedFibElements.insert( pActualSubobject );
			
			list< cFibElement * > liActualSubobjects =
				pActualSubobject->getSubobjects();
			
			liToCheckSubobjects.insert( liToCheckSubobjects.end(),
				liActualSubobjects.begin(), liActualSubobjects.end() );
			
		}
		
		addChangedFibElements( setDeletedFibElements, REMOVED );
	}
	
}


/**
 * This method adds some changed Fib objects.
 * Note: If you move some Fib objects (MOVED), set also the changed
 * 	"from Fib element" as REMOVED seperatly. (The moved to Fib element
 * 	will be set to ADDED automaticly.)
 *
 * @see mapChangedFibObjects
 * @param setChangedFibElements the set with the pointers to the changed
 * 	Fib objects
 * @param changeType the type of change for the Fib objects
 */
void eFibNodeChangedEvent::addChangedFibObjects(
		const set< const cFibElement * > & setChangedFibObjects, const typeChange changeType ) {
	
	if ( ( setChangedFibObjects.empty() ) || ( changeType == NONE ) ) {
		//nothing changed
		return;
	}
	if ( isDeleted() ) {
		//everything changed / deleted -> don't need to update anything
		return;
	}
	mutexChangedFibObjects.lock();
	//a Fib object was changed
	bJustFibElementsChanged = false;
	/*Note: Normaly the mapNotSuperiorToChangedFibObjects and
	 * mapNotContainedInChangedFibObjects should be empty at this point.
	 * Because they will be evalued later, if such Fib objects are searched for*/
	if ( changeType != ALL ) {
		//add to given change type
		mapChangedFibObjects[ changeType ].insert(
			setChangedFibObjects.begin(), setChangedFibObjects.end() );
		//Fib objects which where not superior could now become superior
		mapNotSuperiorToChangedFibObjects[ changeType ].clear();
		mapNotContainedInChangedFibObjects[ changeType ].clear();
		
		//add to change type ALL
		mapChangedFibObjects[ ALL ].insert(
			setChangedFibObjects.begin(), setChangedFibObjects.end()  );
		//Fib objects which where not superior could now become superior
		mapNotSuperiorToChangedFibObjects[ ALL ].clear();
		mapNotContainedInChangedFibObjects[ ALL ].clear();
		
		if ( changeType == MOVED ) {
			/*the Fib objects where moved
			 *-> add their superior as a Fib element where something was added*/
			for ( set< const cFibElement * >::const_iterator
					itrActualFibObject = setChangedFibObjects.begin();
					itrActualFibObject != setChangedFibObjects.end();
					itrActualFibObject++ ) {
				const cFibElement * pChangedFibObjectSuperior =
					(*itrActualFibObject)->getSuperiorFibElement();
				if ( pChangedFibObjectSuperior ) {
					//add to change type ADDED
					mapChangedFibElements[ ADDED ].insert( pChangedFibObjectSuperior );
					//Fib elements which where not superior could now become superior
					mapNotSuperiorToChangedFibElements[ ADDED ].clear();
					mapNotContainedInChangedFibElements[ ADDED ].clear();
				}
			}
		}
	}else{//add to all change types
		//add to change type ALL
		mapChangedFibObjects[ ALL ].insert(
			setChangedFibObjects.begin(), setChangedFibObjects.end()  );
		//Fib objects which where not superior could now become superior
		mapNotSuperiorToChangedFibObjects[ ALL ].clear();
		mapNotContainedInChangedFibObjects[ ALL ].clear();
		
		//add to change type CHANGED
		mapChangedFibObjects[ CHANGED ].insert(
			setChangedFibObjects.begin(), setChangedFibObjects.end()  );
		mapNotSuperiorToChangedFibObjects[ CHANGED ].clear();
		mapNotContainedInChangedFibObjects[ CHANGED ].clear();
		
		//add to change type DELETED
		mapChangedFibObjects[ DELETED ].insert(
			setChangedFibObjects.begin(), setChangedFibObjects.end()  );
		mapNotSuperiorToChangedFibObjects[ DELETED ].clear();
		mapNotContainedInChangedFibObjects[ DELETED ].clear();
		
		//add to change type ADDED
		mapChangedFibObjects[ ADDED ].insert(
			setChangedFibObjects.begin(), setChangedFibObjects.end()  );
		mapNotSuperiorToChangedFibObjects[ ADDED ].clear();
		mapNotContainedInChangedFibObjects[ ADDED ].clear();
		
		//add to change type MOVED
		mapChangedFibObjects[ MOVED ].insert(
			setChangedFibObjects.begin(), setChangedFibObjects.end()  );
		mapNotSuperiorToChangedFibObjects[ MOVED ].clear();
		mapNotContainedInChangedFibObjects[ MOVED ].clear();
		
		//add to change type REMOVED
		mapChangedFibObjects[ REMOVED ].insert(
			setChangedFibObjects.begin(), setChangedFibObjects.end()  );
		mapNotSuperiorToChangedFibObjects[ REMOVED ].clear();
		mapNotContainedInChangedFibObjects[ REMOVED ].clear();
		
		
		/*the Fib objects where moved
		 *-> add their superior as a Fib element where something was added*/
		for ( set< const cFibElement * >::const_iterator
				itrActualFibObject = setChangedFibObjects.begin();
				itrActualFibObject != setChangedFibObjects.end();
				itrActualFibObject++ ) {
			
			const cFibElement * pChangedFibObjectSuperior =
				(*itrActualFibObject)->getSuperiorFibElement();
			if ( pChangedFibObjectSuperior ) {
				//add to change type ADDED
				mapChangedFibElements[ ADDED ].insert( pChangedFibObjectSuperior );
				//Fib elements which where not superior could now become superior
				mapNotSuperiorToChangedFibElements[ ADDED ].clear();
				mapNotContainedInChangedFibElements[ ADDED ].clear();
			}
		}
	}
	
	//there where other things than values changed
	bJustValuesChanged = false;
	
	mutexChangedFibObjects.unlock();
	
	if ( ( changeType == DELETED ) || ( changeType == ALL ) ) {
		//add all contained Fib elements as deleted
		set< const cFibElement * > setDeletedFibElements;
		list< const cFibElement * > liToCheckSubobjects;
		
		liToCheckSubobjects.insert( liToCheckSubobjects.end(),
			setChangedFibObjects.begin(), setChangedFibObjects.end() );
		
		const cFibElement * pActualSubobject;
		while ( ! liToCheckSubobjects.empty() ) {
			pActualSubobject = liToCheckSubobjects.front();
			liToCheckSubobjects.pop_front();
			if ( pActualSubobject == NULL ) {
				//not a valid subobject
				continue;
			}
			setDeletedFibElements.insert( pActualSubobject );
			
			list< cFibElement * > liActualSubobjects =
				pActualSubobject->getSubobjects();
			
			liToCheckSubobjects.insert( liToCheckSubobjects.end(),
				liActualSubobjects.begin(), liActualSubobjects.end() );
			
		}
		
		addChangedFibElements( setDeletedFibElements, REMOVED );
	}
}


/**
 * This method adds some changed Fib objects.
 * Note: If you move some Fib objects (MOVED), set also the changed
 * 	"from Fib element" as REMOVED seperatly. (The moved to Fib element
 * 	will be set to ADDED automaticly.)
 *
 * @see mapChangedFibObjects
 * @param setChangedFibElements the set with the pointers to the changed
 * 	Fib objects
 * @param changeType the type of change for the Fib objects
 */
void eFibNodeChangedEvent::addChangedFibObjects(
		const set< cFibElement * > & setChangedFibObjects, const typeChange changeType ) {
	
	if ( ( setChangedFibObjects.empty() ) || ( changeType == NONE ) ) {
		//nothing changed
		return;
	}
	if ( isDeleted() ) {
		//everything changed / deleted -> don't need to update anything
		return;
	}
	mutexChangedFibObjects.lock();
	//a Fib object was changed
	bJustFibElementsChanged = false;
	/*Note: Normaly the mapNotSuperiorToChangedFibObjects and
	 * mapNotContainedInChangedFibObjects should be empty at this point.
	 * Because they will be evalued later, if such Fib objects are searched for*/
	if ( changeType != ALL ) {
		//add to given change type
		mapChangedFibObjects[ changeType ].insert(
			setChangedFibObjects.begin(), setChangedFibObjects.end() );
		//Fib objects which where not superior could now become superior
		mapNotSuperiorToChangedFibObjects[ changeType ].clear();
		mapNotContainedInChangedFibObjects[ changeType ].clear();
		
		//add to change type ALL
		mapChangedFibObjects[ ALL ].insert(
			setChangedFibObjects.begin(), setChangedFibObjects.end()  );
		//Fib objects which where not superior could now become superior
		mapNotSuperiorToChangedFibObjects[ ALL ].clear();
		mapNotContainedInChangedFibObjects[ ALL ].clear();
		
		if ( changeType == MOVED ) {
			/*the Fib objects where moved
			 *-> add their superior as a Fib element where something was added*/
			for ( set< cFibElement * >::const_iterator
					itrActualFibObject = setChangedFibObjects.begin();
					itrActualFibObject != setChangedFibObjects.end();
					itrActualFibObject++ ) {
				const cFibElement * pChangedFibObjectSuperior =
					(*itrActualFibObject)->getSuperiorFibElement();
				if ( pChangedFibObjectSuperior ) {
					//add to change type ADDED
					mapChangedFibElements[ ADDED ].insert( pChangedFibObjectSuperior );
					//Fib elements which where not superior could now become superior
					mapNotSuperiorToChangedFibElements[ ADDED ].clear();
					mapNotContainedInChangedFibElements[ ADDED ].clear();
				}
			}
		}
	}else{//add to all change types
		//add to change type ALL
		mapChangedFibObjects[ ALL ].insert(
			setChangedFibObjects.begin(), setChangedFibObjects.end()  );
		//Fib objects which where not superior could now become superior
		mapNotSuperiorToChangedFibObjects[ ALL ].clear();
		mapNotContainedInChangedFibObjects[ ALL ].clear();
		
		//add to change type CHANGED
		mapChangedFibObjects[ CHANGED ].insert(
			setChangedFibObjects.begin(), setChangedFibObjects.end()  );
		mapNotSuperiorToChangedFibObjects[ CHANGED ].clear();
		mapNotContainedInChangedFibObjects[ CHANGED ].clear();
		
		//add to change type DELETED
		mapChangedFibObjects[ DELETED ].insert(
			setChangedFibObjects.begin(), setChangedFibObjects.end()  );
		mapNotSuperiorToChangedFibObjects[ DELETED ].clear();
		mapNotContainedInChangedFibObjects[ DELETED ].clear();
		
		//add to change type ADDED
		mapChangedFibObjects[ ADDED ].insert(
			setChangedFibObjects.begin(), setChangedFibObjects.end()  );
		mapNotSuperiorToChangedFibObjects[ ADDED ].clear();
		mapNotContainedInChangedFibObjects[ ADDED ].clear();
		
		//add to change type MOVED
		mapChangedFibObjects[ MOVED ].insert(
			setChangedFibObjects.begin(), setChangedFibObjects.end()  );
		mapNotSuperiorToChangedFibObjects[ MOVED ].clear();
		mapNotContainedInChangedFibObjects[ MOVED ].clear();
		
		//add to change type REMOVED
		mapChangedFibObjects[ REMOVED ].insert(
			setChangedFibObjects.begin(), setChangedFibObjects.end()  );
		mapNotSuperiorToChangedFibObjects[ REMOVED ].clear();
		mapNotContainedInChangedFibObjects[ REMOVED ].clear();
		
		
		/*the Fib objects where moved
		 *-> add their superior as a Fib element where something was added*/
		for ( set< cFibElement * >::const_iterator
				itrActualFibObject = setChangedFibObjects.begin();
				itrActualFibObject != setChangedFibObjects.end();
				itrActualFibObject++ ) {
			
			const cFibElement * pChangedFibObjectSuperior =
				(*itrActualFibObject)->getSuperiorFibElement();
			if ( pChangedFibObjectSuperior ) {
				//add to change type ADDED
				mapChangedFibElements[ ADDED ].insert( pChangedFibObjectSuperior );
				//Fib elements which where not superior could now become superior
				mapNotSuperiorToChangedFibElements[ ADDED ].clear();
				mapNotContainedInChangedFibElements[ ADDED ].clear();
			}
		}
	}
	
	//there where other things than values changed
	bJustValuesChanged = false;
	
	mutexChangedFibObjects.unlock();
	
	if ( ( changeType == DELETED ) || ( changeType == ALL ) ) {
		//add all contained Fib elements as deleted
		set< const cFibElement * > setDeletedFibElements;
		list< const cFibElement * > liToCheckSubobjects;
		
		liToCheckSubobjects.insert( liToCheckSubobjects.end(),
			setChangedFibObjects.begin(), setChangedFibObjects.end() );
		
		const cFibElement * pActualSubobject;
		while ( ! liToCheckSubobjects.empty() ) {
			pActualSubobject = liToCheckSubobjects.front();
			liToCheckSubobjects.pop_front();
			if ( pActualSubobject == NULL ) {
				//not a valid subobject
				continue;
			}
			setDeletedFibElements.insert( pActualSubobject );
			
			list< cFibElement * > liActualSubobjects =
				pActualSubobject->getSubobjects();
			
			liToCheckSubobjects.insert( liToCheckSubobjects.end(),
				liActualSubobjects.begin(), liActualSubobjects.end() );
			
		}
		
		addChangedFibElements( setDeletedFibElements, REMOVED );
	}
}


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
bool eFibNodeChangedEvent::setJustValuesChanged(
		const bool bInJustValuesChanged ) {
	
	if ( bJustValuesChanged == bInJustValuesChanged ) {
		//nothing changed
		return bJustValuesChanged;
	}
	if ( ! bInJustValuesChanged ) {
		//more than just values changed -> nothing to do
		bJustValuesChanged = false;
	}//elseif ( bInJustValuesChanged == true ) &&  ( bJustValuesChanged == false )
	
	//check if there could be just values changed
	mutexChangedFibElements.lock();
	if ( ! mapChangedFibElements[ DELETED ].empty() ) {
		//something deleted -> more than just value changed
		mutexChangedFibElements.unlock();
		return false;
	}
	if ( ! mapChangedFibElements[ ADDED ].empty() ) {
		//something added -> more than just value changed
		mutexChangedFibElements.unlock();
		return false;
	}
	if ( ! mapChangedFibElements[ MOVED ].empty() ) {
		//something moved -> more than just value changed
		mutexChangedFibElements.unlock();
		return false;
	}
	if ( ! mapChangedFibElements[ REMOVED ].empty() ) {
		//something removed -> more than just value changed
		mutexChangedFibElements.unlock();
		return false;
	}
	mutexChangedFibElements.unlock();
	mutexChangedFibObjects.lock();
	if ( ! mapChangedFibObjects[ ALL ].empty() ) {
		//Fib element structure changed -> more than just value changed
		mutexChangedFibElements.unlock();
		return false;
	}
	mutexChangedFibObjects.unlock();
	//their could be just values changed
	bJustValuesChanged = true;
	return true;
}



/**
 * @return the name of this class "eFibNodeChangedEvent"
 */
string eFibNodeChangedEvent::getName() const {
	
	return "eFibNodeChangedEvent";
}


/**
 * @see setChangeNodeVersion()
 * @return the version of the Fib object for the node, when this event
 * 	was generated
 * 	@see ulVersion
 */
unsigned long eFibNodeChangedEvent::getChangeNodeVersion() const {
	
	return ulVersion;
}


/**
 * This method sets the Fib object version number (of the Fib node)
 * for this event.
 *
 * @see ulVersion
 * @see getChangeNodeVersion();
 * @param ulChangeNodeVersion the version of the Fib object for the
 * 	node, for this event
 */
void eFibNodeChangedEvent::setChangeNodeVersion(
		const unsigned long ulChangeNodeVersion ) {
	
	ulVersion = ulChangeNodeVersion;
}



/**
 * @see setChangeBy()
 * @return a pointer to the object, which had changed the Fib node or NULL
 * 	@see pChangedBy
 */
const QObject * eFibNodeChangedEvent::getChangeBy() const {
	
	return pChangedBy;
}


/**
 * This method sets by which object the Fib object for the Fib node was
 * changed.
 *
 * @see pChangedBy
 * @see getChangeBy()
 * @param pInChangedBy a pointer to the object, which had changed the
 * 	Fib node or NULL
 */
void eFibNodeChangedEvent::setChangeBy( QObject * pInChangedBy ) {
	
	pChangedBy = pInChangedBy;
}


/**
 * Event method
 * It will be called every time a Fib node (cFibNode), at which
 * this object is registered, was changed.
 *
 * @param pFibNode a pointer to the changed Fib node
 */
void eFibNodeChangedEvent::fibNodeChangedEvent(
		const eFibNodeChangedEvent * pFibNodeChanged ) {
	
	if ( ( pFibNodeChanged != NULL ) && ( pFibNodeChanged->isDeleted() ) &&
			( pFibNodeChanged->getChangedNode() == getChangedNode() ) ) {
		//a node was deleted -> change type of this event to deleted
		setDeleted( true );
	}//else everything is OK
	
	/* TODO?
	 * adapt the changes from the given node into this node and fast forward
	 * the version number to that of the other node.
	 */
	
	//mark deleted Fib elements
	addChangedFibElements( getChangedFibElements( DELETED ), DELETED  );
	
	
}


/**
 * @see mapChangedFibElements
 * @param pFibElement a pointer to the Fib element for which to check,
 * 	if it was changed in the changed type changeType
 * @param changeType the type of change, for the Fib element
 * @return true if the given Fib element was changed, else false;
 * 	(Note: If the node was deleted (DELETED) true will be returned.)
 */
bool eFibNodeChangedEvent::isElementChanged(
		const cFibElement * pFibElement,
		const typeChange changeType ) const {
	
	if ( isDeleted() ) {
		//Fib node was deleted -> every Fib element of it was changed
		return true;
	}
	
	mutexChangedFibElements.lock();
	const map< typeChange, set< const cFibElement * > >::const_iterator
		itrFoundSetChangedFibElements = mapChangedFibElements.find( changeType );
	if( itrFoundSetChangedFibElements == mapChangedFibElements.end() ) {
		//Fib element could not be found -> Fib element was not changed
		mutexChangedFibElements.unlock();
		return false;
	}
	const set< const cFibElement * > & setFoundSetChangedFibElements =
		itrFoundSetChangedFibElements->second;
	
	if ( setFoundSetChangedFibElements.find( pFibElement ) ==
				setFoundSetChangedFibElements.end() ) {
		//Fib element could not be found -> Fib element was not changed
		mutexChangedFibElements.unlock();
		return false;
	}//else Fib element could be found -> Fib element was changed
	mutexChangedFibElements.unlock();
	return true;
}


/**
 * @see mapChangedFibElements
 * @return the change type of the given Fib element;
 * 	(Note: If the node was deleted DELETED will be returned.)
 * 	@see typeChange
 */
eFibNodeChangedEvent::typeChange eFibNodeChangedEvent::getElementChangeType(
		const cFibElement * pFibElement ) const {
	
	if ( isDeleted() ) {
		//Fib node was deleted -> every Fib element of it was deleted
		return DELETED;
	}
	
	mutexChangedFibElements.lock();
	//use reverse iterator so change type ALL will be checked last
	for ( std::map< typeChange, std::set< const cFibElement * > >::const_reverse_iterator
			itrActualChangeType = mapChangedFibElements.rbegin();
			itrActualChangeType != mapChangedFibElements.rend();
			itrActualChangeType++ ){
		
		if( itrActualChangeType->second.find( pFibElement ) !=
				itrActualChangeType->second.end() ) {
			/*Fib element could be found in change for type Fib elements
			-> Fib element was changed
			-> return its change type*/
			mutexChangedFibElements.unlock();
			return itrActualChangeType->first;
		}//else Fib element could be not found in change type Fib elements
	}
	
	mutexChangedFibElements.unlock();
	/*Fib element could not be found in any change type
	 *-> Fib element was not changed*/
	return NONE;
}


/**
 * @see mapChangedFibElements
 * @param changeType the type of change, for the Fib elements to count
 * @return the number of changed Fib elements
 */
unsigned int eFibNodeChangedEvent::getNumberOfChangedFibElements(
		const typeChange changeType ) const {
	
	mutexChangedFibElements.lock();
	
	const map< typeChange, set< const cFibElement * > >::const_iterator
		itrFoundSetChangedFibElements = mapChangedFibElements.find( changeType );
	if( itrFoundSetChangedFibElements == mapChangedFibElements.end() ) {
		//change type could not be found -> 0 Fib element for the changed type
		mutexChangedFibElements.unlock();
		return 0;
	}
	const unsigned int uiNumberOfChangedElements =
		itrFoundSetChangedFibElements->second.size();
	mutexChangedFibElements.unlock();
	
	return uiNumberOfChangedElements;
}


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
const set< const cFibElement * > eFibNodeChangedEvent::getChangedFibElements(
	const typeChange changeType ) const {
	
	mutexChangedFibElements.lock();
	const map< typeChange, set< const cFibElement * > >::const_iterator
		itrFoundSetChangedFibElements = mapChangedFibElements.find( changeType );
	if( itrFoundSetChangedFibElements == mapChangedFibElements.end() ) {
		//change type could not be found -> 0 Fib element for the changed type
		mutexChangedFibElements.unlock();
		return set< const cFibElement * > ();
	}
	const set< const cFibElement * > setOfChangedElements =
		itrFoundSetChangedFibElements->second;
	mutexChangedFibElements.unlock();
	
	return setOfChangedElements;
}


/**
 * @see mapChangedFibObjects
 * @param pFibObject a pointer to the Fib object for which to check,
 * 	if it was changed in the changed type changeType
 * @param changeType the type of change, for the Fib object
 * @return true if the given Fib objects was changed, else false;
 * 	(Note: If the node was deleted (DELETED) true will be returned.)
 */
bool eFibNodeChangedEvent::isObjectChanged( const cFibElement * pFibObject,
		const typeChange changeType ) const {
	
	if ( isDeleted() ) {
		//Fib node was deleted -> every Fib object of it was changed
		return true;
	}
	
	mutexChangedFibObjects.lock();
	const map< typeChange, set< const cFibElement * > >::const_iterator
		itrFoundSetChangedFibObjects = mapChangedFibObjects.find( changeType );
	if( itrFoundSetChangedFibObjects == mapChangedFibObjects.end() ) {
		//Fib object could not be found -> Fib object was not changed
		mutexChangedFibObjects.unlock();
		return false;
	}
	const set< const cFibElement * > & setFoundSetChangedFibObjects =
		itrFoundSetChangedFibObjects->second;
	
	if ( setFoundSetChangedFibObjects.find(
			const_cast< const cFibElement * >(pFibObject) ) ==
				setFoundSetChangedFibObjects.end() ) {
		//Fib object could not be found -> Fib object was not changed
		mutexChangedFibObjects.unlock();
		return false;
	}//else Fib object could be found -> Fib object was changed
	mutexChangedFibObjects.unlock();
	return true;
}


/**
 * @see mapChangedFibObjects
 * @return the change type of the given Fib object;
 * 	(Note: If the node was deleted DELETED will be returned.)
 * 	@see typeChange
 */
eFibNodeChangedEvent::typeChange eFibNodeChangedEvent::getObjectChangeType(
		const cFibElement * pFibObject ) const {
	
	if ( isDeleted() ) {
		//Fib node was deleted -> every Fib element of it was deleted
		return DELETED;
	}
	
	mutexChangedFibObjects.lock();
	//use reverse iterator so change type ALL will be checked last
	for ( std::map< typeChange, std::set< const cFibElement * > >::const_reverse_iterator
			itrActualChangeType = mapChangedFibObjects.rbegin();
			itrActualChangeType != mapChangedFibObjects.rend();
			itrActualChangeType++ ){
		
		if( itrActualChangeType->second.find( pFibObject ) !=
				itrActualChangeType->second.end() ) {
			/*Fib element could be found in change for type Fib objects
			-> Fib object was changed
			-> return its change type*/
			mutexChangedFibObjects.unlock();
			return itrActualChangeType->first;
		}//else Fib element could be not found in change type Fib objects
	}
	mutexChangedFibObjects.unlock();
	/*Fib object could not be found in any change type
	 *-> Fib object was not changed*/
	return NONE;
}


/**
 * @see mapChangedFibObjects
 * @param changeType the type of change, for the Fib objects to count
 * @return the number of changed Fib objects
 */
unsigned int eFibNodeChangedEvent::getNumberOfChangedFibObjects(
		const typeChange changeType ) const {
	
	mutexChangedFibObjects.lock();
	
	const map< typeChange, set< const cFibElement * > >::const_iterator
		itrFoundSetChangedFibObjects = mapChangedFibObjects.find( changeType );
	if( itrFoundSetChangedFibObjects == mapChangedFibObjects.end() ) {
		//change type could not be found -> 0 Fib objects for the changed type
		mutexChangedFibObjects.unlock();
		return 0;
	}
	const unsigned int uiNumberOfChangedObjects =
		itrFoundSetChangedFibObjects->second.size();
	mutexChangedFibObjects.unlock();
	
	return uiNumberOfChangedObjects;
}


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
const set< const cFibElement * > eFibNodeChangedEvent::getChangedFibObjects(
		const typeChange changeType ) const {
	
	mutexChangedFibObjects.lock();
	const map< typeChange, set< const cFibElement * > >::const_iterator
		itrFoundSetChangedFibObjects = mapChangedFibObjects.find( changeType );
	if( itrFoundSetChangedFibObjects == mapChangedFibObjects.end() ) {
		//change type could not be found -> 0 Fib element for the changed type
		mutexChangedFibObjects.unlock();
		return set< const cFibElement * > ();
	}
	const set< const cFibElement * > setOfChangedObjects =
		itrFoundSetChangedFibObjects->second;
	mutexChangedFibObjects.unlock();
	
	return setOfChangedObjects;
}


/**
 * @see bJustValuesChanged
 * @see setJustValuesChanged()
 * @return true if just values in Fib elements where changed, else false
 */
bool eFibNodeChangedEvent::isJustValuesChanged() const {
	
	return bJustValuesChanged;
}


/**
 * @see bJustValuesChanged
 * @see setJustValuesChanged()
 * @see mapChangedFibElements
 * @return true if just Fib elements changed, but not the Fib element
 * 	structure, else false;
 * 	(if true no other change type as CHANGED for Fib elements exists)
 */
bool eFibNodeChangedEvent::isJustFibElementsChanged() const {
	
	return bJustFibElementsChanged;
}


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
bool eFibNodeChangedEvent::isChangedBranch( const cFibElement * pFibElement,
		const typeChange changeType ) const {
	
	return isElementChanged( pFibElement, changeType ) ||
		isObjectChanged( pFibElement, changeType ) ||
		isSuperiorToChanged( pFibElement, changeType ) ||
		isContainedInChanged( pFibElement, changeType );
}


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
bool eFibNodeChangedEvent::isSuperiorToChanged( const cFibElement * pFibElement,
		const typeChange changeType ) const {
	
	if ( pFibElement == NULL ) {
		//no Fib element given -> can't be superior
		return false;
	}
	
	//check if the given Fib element was found before as superior
	mutexChangedFibElements.lock();
	
	//check if the Fib element was deleted
	std::map< typeChange, std::set< const cFibElement * > >::const_iterator
		itrDeletedFibElements = mapChangedFibElements.find( DELETED );
	if ( itrDeletedFibElements != mapChangedFibElements.end() ) {
		if ( itrDeletedFibElements->second.find( pFibElement ) !=
				itrDeletedFibElements->second.end() ) {
			//Fib element was deleted -> can't be superior to anything
			mutexChangedFibElements.unlock();
			return false;
		}
	}
	
	set< const cFibElement * > & setSuperiorToChangedFibElements =
		mapSuperiorToChangedFibElements[ changeType ];
	
	if ( setSuperiorToChangedFibElements.find( pFibElement ) !=
			setSuperiorToChangedFibElements.end() ) {
		//the given Fib element is superior to a changed Fib element
		mutexChangedFibElements.unlock();
		return true;
	}
	//check if the given Fib element was found before as not superior
	set< const cFibElement * > & setNotSuperiorToChangedFibElements =
		mapNotSuperiorToChangedFibElements[ changeType ];
	
	if ( setNotSuperiorToChangedFibElements.find( pFibElement ) !=
			setNotSuperiorToChangedFibElements.end() ) {
		//the given Fib element is not superior to a changed Fib element
		mutexChangedFibElements.unlock();
		return false;
	}
	
	mutexChangedFibObjects.lock();
	set< const cFibElement * > & setSuperiorToChangedFibObjects =
		mapSuperiorToChangedFibObjects[ changeType ];
	
	if ( setSuperiorToChangedFibObjects.find( pFibElement ) !=
			setSuperiorToChangedFibObjects.end() ) {
		//the given Fib element is superior to a changed Fib object
		mutexChangedFibObjects.unlock();
		mutexChangedFibElements.unlock();
		return true;
	}
	//check if the given Fib element was found before as not superior
	set< const cFibElement * > & setNotSuperiorToChangedFibObjects =
		mapNotSuperiorToChangedFibObjects[ changeType ];
	
	if ( setNotSuperiorToChangedFibObjects.find( pFibElement ) !=
			setNotSuperiorToChangedFibObjects.end() ) {
		//the given Fib element is not superior to a changed Fib object
		mutexChangedFibObjects.unlock();
		mutexChangedFibElements.unlock();
		return false;
	}
	
	//search the contained Fib elements, if they are changed Fib elements
	
	//the list with the subobjects to check if they are changed objects
	list< cFibElement * > liCheckSubobjects = pFibElement->getSubobjects();
	list< const cFibElement * > liCheckedSubobjects;
	liCheckedSubobjects.push_back( pFibElement );
	
	const map< typeChange, set< const cFibElement * > >::const_iterator
		itrFoundSetChangedFibElements = mapChangedFibElements.find( changeType );
	const map< typeChange, set< const cFibElement * > >::const_iterator
		itrFoundSetChangedFibObjects  = mapChangedFibObjects.find( changeType );

	if ( ( itrFoundSetChangedFibElements != mapChangedFibElements.end() ) &&
			( itrFoundSetChangedFibObjects != mapChangedFibObjects.end() ) ) {
		const set< const cFibElement * > & setChangedFibElements =
			itrFoundSetChangedFibElements->second;
		const set< const cFibElement * > & setChangedFibObjects  =
			itrFoundSetChangedFibObjects->second;
		
		const cFibElement * pActualSubobject;
		while ( ! liCheckSubobjects.empty() ) {
			//search for subobject / Fib element which was changed
			pActualSubobject = liCheckSubobjects.front();
			liCheckSubobjects.pop_front();
			liCheckedSubobjects.push_back( pActualSubobject );
			
			//check if the actual Fib element is a changed object
			if ( ( setChangedFibElements.find( pActualSubobject ) !=
					setChangedFibElements.end() ) ||
				( setSuperiorToChangedFibElements.find( pActualSubobject ) !=
					setSuperiorToChangedFibElements.end() ) ) {
				/*changed Fib element or Fib element superior to it found
				 -> the Fib elements pFibElement is superior to a changed Fib element*/
				setSuperiorToChangedFibElements.insert( pFibElement );
				/*to speed up later evaluations add superior of actual Fib element /
				 subobject to set of superior Fib elements (often found superior
				 Fib element branches will add more Fib elements to the set)*/
				setSuperiorToChangedFibElements.insert(
					pActualSubobject->getSuperiorFibElement() );
				mutexChangedFibObjects.unlock();
				mutexChangedFibElements.unlock();
				return true;
			}
			//check if the actual Fib element is a changed object
			if ( ( setChangedFibObjects.find( pActualSubobject ) !=
					setChangedFibObjects.end() ) ||
				( setSuperiorToChangedFibObjects.find( pActualSubobject ) !=
					setSuperiorToChangedFibObjects.end() ) ) {
				/*changed Fib object or Fib element superior to it found
				 -> the Fib elements pFibElement is superior to a changed Fib object*/
				setSuperiorToChangedFibObjects.insert( pFibElement );
				/*to speed up later evaluations add superior of actual Fib element /
				 subobject to set of superior Fib elements (often found superior
				 Fib element branches will add more Fib elements to the set)*/
				setSuperiorToChangedFibObjects.insert(
					pActualSubobject->getSuperiorFibElement() );
				mutexChangedFibObjects.unlock();
				mutexChangedFibElements.unlock();
				return true;
			}
		}
	} else if ( itrFoundSetChangedFibElements != mapChangedFibElements.end() ) {
		
		const set< const cFibElement * > & setChangedFibElements =
			itrFoundSetChangedFibElements->second;
		
		const cFibElement * pActualSubobject;
		while ( ! liCheckSubobjects.empty() ) {
			//search for subobject / Fib element which was changed
			pActualSubobject = liCheckSubobjects.front();
			liCheckSubobjects.pop_front();
			liCheckedSubobjects.push_back( pActualSubobject );
			
			//check if the actual Fib element is a changed object
			if ( ( setChangedFibElements.find( pActualSubobject ) !=
					setChangedFibElements.end() ) ||
				( setSuperiorToChangedFibElements.find( pActualSubobject ) !=
					setSuperiorToChangedFibElements.end() ) ) {
				/*changed Fib element or Fib element superior to it found
				 -> the Fib elements pFibElement is superior to a changed Fib element*/
				setSuperiorToChangedFibElements.insert( pFibElement );
				/*to speed up later evaluations add superior of actual Fib element /
				 subobject to set of superior Fib elements (often found superior
				 Fib element branches will add more Fib elements to the set)*/
				setSuperiorToChangedFibElements.insert(
					pActualSubobject->getSuperiorFibElement() );
				mutexChangedFibObjects.unlock();
				mutexChangedFibElements.unlock();
				return true;
			}
		}
	} else if ( itrFoundSetChangedFibObjects != mapChangedFibObjects.end() ) {
		
		const set< const cFibElement * > & setChangedFibObjects  =
			itrFoundSetChangedFibObjects->second;
		
		const cFibElement * pActualSubobject;
		while ( ! liCheckSubobjects.empty() ) {
			//search for subobject / Fib element which was changed
			pActualSubobject = liCheckSubobjects.front();
			liCheckSubobjects.pop_front();
			liCheckedSubobjects.push_back( pActualSubobject );

			//check if the actual Fib element is a changed object
			if ( ( setChangedFibObjects.find( pActualSubobject ) !=
					setChangedFibObjects.end() ) ||
				( setSuperiorToChangedFibObjects.find( pActualSubobject ) !=
					setSuperiorToChangedFibObjects.end() ) ) {
				/*changed Fib object or Fib element superior to it found
				 -> the Fib elements pFibElement is superior to a changed Fib object*/
				setSuperiorToChangedFibObjects.insert( pFibElement );
				/*to speed up later evaluations add superior of actual Fib element /
				 subobject to set of superior Fib elements (often found superior
				 Fib element branches will add more Fib elements to the set)*/
				setSuperiorToChangedFibObjects.insert(
					pActualSubobject->getSuperiorFibElement() );
				mutexChangedFibObjects.unlock();
				mutexChangedFibElements.unlock();
				return true;
			}
		}
	}//else no changed Fib elements or changed Fib objects of the change type
	
	/*-> liCheckSubobjects.empty() == true
	-> no Fib element / subobject which was changed found
	-> add all checked subobjects as not superior to changed Fib element and
	not superior to changed Fib objects*/
	setNotSuperiorToChangedFibElements.insert(
		liCheckedSubobjects.begin(), liCheckedSubobjects.end() );
	setNotSuperiorToChangedFibObjects.insert(
		liCheckedSubobjects.begin(), liCheckedSubobjects.end() );
	
	mutexChangedFibObjects.unlock();
	mutexChangedFibElements.unlock();
	return false;
}


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
bool eFibNodeChangedEvent::isContainedInChanged( const cFibElement * pFibElement,
		const typeChange changeType ) const {
	
	if ( pFibElement == NULL ) {
		//no Fib element given -> can't be contained in changed Fib element
		return false;
	}
	//check if the given Fib element was found before as contained in a changed Fib element
	mutexChangedFibElements.lock();
	//check if the Fib element was deleted
	std::map< typeChange, std::set< const cFibElement * > >::const_iterator
		itrDeletedFibElements = mapChangedFibElements.find( DELETED );
	if ( itrDeletedFibElements != mapChangedFibElements.end() ) {
		if ( itrDeletedFibElements->second.find( pFibElement ) !=
				itrDeletedFibElements->second.end() ) {
			//Fib element was deleted -> can't be contained in anything
			mutexChangedFibElements.unlock();
			return false;
		}
	}
	
	set< const cFibElement * > & setContainedInChangedFibElements =
		mapContainedInChangedFibElements[ changeType ];
	
	if ( setContainedInChangedFibElements.find( pFibElement ) !=
			setContainedInChangedFibElements.end() ) {
		//the given Fib element is contained in a changed Fib element
		mutexChangedFibElements.unlock();
		return true;
	}
	//check if the given Fib element was found before as not contained in a changed Fib element
	set< const cFibElement * > & setNotContainedInChangedFibElements =
		mapNotContainedInChangedFibElements[ changeType ];
	
	if ( setNotContainedInChangedFibElements.find( pFibElement ) !=
			setNotContainedInChangedFibElements.end() ) {
		//the given Fib element is not contained in a changed Fib element
		mutexChangedFibElements.unlock();
		return false;
	}
	
	//check if the given Fib element was found before as contained in a changed Fib element
	mutexChangedFibObjects.lock();
	set< const cFibElement * > & setContainedInChangedFibObject =
		mapContainedInChangedFibObjects[ changeType ];
	
	if ( setContainedInChangedFibObject.find( pFibElement ) !=
			setContainedInChangedFibObject.end() ) {
		//the given Fib element is contained in a changed Fib object
		mutexChangedFibObjects.unlock();
		mutexChangedFibElements.unlock();
		return true;
	}
	//check if the given Fib element was found before as not contained in a changed Fib element
	set< const cFibElement * > & setNotContainedInChangedFibObject =
		mapNotContainedInChangedFibObjects[ changeType ];
	
	if ( setNotContainedInChangedFibObject.find( pFibElement ) !=
			setNotContainedInChangedFibObject.end() ) {
		//the given Fib element is not contained in a changed Fib object
		mutexChangedFibObjects.unlock();
		mutexChangedFibElements.unlock();
		return false;
	}
	
	//search the superior Fib elements, if they are changed Fib elements
	//the list with the subobjects to check if they are changed objects
	const cFibElement * pActualSuperior = pFibElement->getSuperiorFibElement();
	list< const cFibElement * > liCheckedSuperiors;
	liCheckedSuperiors.push_back( pFibElement );
	
	const map< typeChange, set< const cFibElement * > >::const_iterator
		itrFoundSetChangedFibElements = mapChangedFibElements.find( changeType );
	const map< typeChange, set< const cFibElement * > >::const_iterator
		itrFoundSetChangedFibObjects  = mapChangedFibObjects.find( changeType );

	if ( ( itrFoundSetChangedFibElements != mapChangedFibElements.end() ) &&
			( itrFoundSetChangedFibObjects != mapChangedFibObjects.end() ) ) {
		
		const set< const cFibElement * > & setChangedFibElements =
			itrFoundSetChangedFibElements->second;
		const set< const cFibElement * > & setChangedFibObjects =
			itrFoundSetChangedFibObjects->second;
	
		while ( pActualSuperior != NULL ) {
			//search for superior Fib element which was changed
			liCheckedSuperiors.push_back( pActualSuperior );
			
			//check if the actual superior Fib element is a changed Fib element
			if ( ( setChangedFibElements.find( pActualSuperior ) !=
					setChangedFibElements.end() ) ||
				( setContainedInChangedFibElements.find( pActualSuperior ) !=
					setContainedInChangedFibElements.end() ) ) {
				/*changed Fib element or Fib element contained in it found
				 -> all checked superior Fib elements are contained in to a
				 changed Fib element*/
				setContainedInChangedFibElements.insert(
					liCheckedSuperiors.begin(), liCheckedSuperiors.end() );
				mutexChangedFibObjects.unlock();
				mutexChangedFibElements.unlock();
				return true;
			}
			//check if the actual superior Fib element is a changed Fib object
			if ( ( setChangedFibObjects.find( pActualSuperior ) !=
					setChangedFibObjects.end() ) ||
				( setContainedInChangedFibObject.find( pActualSuperior ) !=
					setContainedInChangedFibObject.end() ) ) {
				/*changed Fib object or Fib element contained in it found
				 -> all checked superior Fib elements are contained in to a
				 changed Fib object*/
				setContainedInChangedFibObject.insert(
					liCheckedSuperiors.begin(), liCheckedSuperiors.end() );
				mutexChangedFibObjects.unlock();
				mutexChangedFibElements.unlock();
				return true;
			}
			//check next superior Fib element
			pActualSuperior = pActualSuperior->getSuperiorFibElement();
		}
	} else if ( itrFoundSetChangedFibElements != mapChangedFibElements.end() ) {
		// && ( itrFoundSetChangedFibObjects == mapChangedFibObjects.end() )
		const set< const cFibElement * > & setChangedFibElements =
			itrFoundSetChangedFibElements->second;
	
		while ( pActualSuperior != NULL ) {
			//search for superior Fib element which was changed
			liCheckedSuperiors.push_back( pActualSuperior );
			
			//check if the actual superior Fib element is a changed Fib element
			if ( ( setChangedFibElements.find( pActualSuperior ) !=
					setChangedFibElements.end() ) ||
				( setContainedInChangedFibElements.find( pActualSuperior ) !=
					setContainedInChangedFibElements.end() ) ) {
				/*changed Fib element or Fib element contained in it found
				 -> all checked superior Fib elements are contained in to a
				 changed Fib element*/
				setContainedInChangedFibElements.insert(
					liCheckedSuperiors.begin(), liCheckedSuperiors.end() );
				mutexChangedFibObjects.unlock();
				mutexChangedFibElements.unlock();
				return true;
			}
			//check next superior Fib element
			pActualSuperior = pActualSuperior->getSuperiorFibElement();
		}
	} else if ( itrFoundSetChangedFibObjects != mapChangedFibObjects.end() ) {
		//&& ( itrFoundSetChangedFibElements == mapChangedFibElements.end() )
		const set< const cFibElement * > & setChangedFibObjects =
			itrFoundSetChangedFibObjects->second;
	
		while ( pActualSuperior != NULL ) {
			//search for superior Fib element which was changed
			liCheckedSuperiors.push_back( pActualSuperior );
			
			//check if the actual superior Fib element is a changed Fib object
			if ( ( setChangedFibObjects.find( pActualSuperior ) !=
					setChangedFibObjects.end() ) ||
				( setContainedInChangedFibObject.find( pActualSuperior ) !=
					setContainedInChangedFibObject.end() ) ) {
				/*changed Fib object or Fib element contained in it found
				 -> all checked superior Fib elements are contained in to a
				 changed Fib object*/
				setContainedInChangedFibObject.insert(
					liCheckedSuperiors.begin(), liCheckedSuperiors.end() );
				mutexChangedFibObjects.unlock();
				mutexChangedFibElements.unlock();
				return true;
			}
			//check next superior Fib element
			pActualSuperior = pActualSuperior->getSuperiorFibElement();
		}
	}//else no changed Fib elements or changed Fib objects of the change type
	
	/*else if ( pActualSuperior == NULL )
	-> no superior Fib element which was changed found
	-> add all checked superior Fib elements as not contained in a changed
	Fib element and not contained in a changed Fib object*/
	setNotContainedInChangedFibElements.insert(
		liCheckedSuperiors.begin(), liCheckedSuperiors.end() );
	setNotContainedInChangedFibObject.insert(
		liCheckedSuperiors.begin(), liCheckedSuperiors.end() );
	
	mutexChangedFibObjects.unlock();
	mutexChangedFibElements.unlock();
	return false;
}


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
bool eFibNodeChangedEvent::isChangedElementBranch(
		const cFibElement * pFibElement,
		const typeChange changeType ) const {
	
	return isElementChanged( pFibElement, changeType ) ||
		isSuperiorToChangedElement( pFibElement, changeType ) ||
		isContainedInChangedElement( pFibElement, changeType );
}


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
bool eFibNodeChangedEvent::isSuperiorToChangedElement(
		const cFibElement * pFibElement,
		const typeChange changeType ) const {
	
	if ( pFibElement == NULL ) {
		//no Fib element given -> can't be superior
		return false;
	}
	//check if the given Fib element was found before as superior
	mutexChangedFibElements.lock();
	//check if the Fib element was deleted
	std::map< typeChange, std::set< const cFibElement * > >::const_iterator
		itrDeletedFibElements = mapChangedFibElements.find( DELETED );
	if ( itrDeletedFibElements != mapChangedFibElements.end() ) {
		if ( itrDeletedFibElements->second.find( pFibElement ) !=
				itrDeletedFibElements->second.end() ) {
			//Fib element was deleted -> can't be superior to anything
			mutexChangedFibElements.unlock();
			return false;
		}
	}
	set< const cFibElement * > & setSuperiorToChanged =
		mapSuperiorToChangedFibElements[ changeType ];
	
	if ( setSuperiorToChanged.find( pFibElement ) != setSuperiorToChanged.end() ) {
		//the given Fib element is superior to a changed Fib element
		mutexChangedFibElements.unlock();
		return true;
	}
	//check if the given Fib element was found before as not superior
	set< const cFibElement * > & setNotSuperiorToChanged =
		mapNotSuperiorToChangedFibElements[ changeType ];
	
	if ( setNotSuperiorToChanged.find( pFibElement ) != setNotSuperiorToChanged.end() ) {
		//the given Fib element is not superior to a changed Fib element
		mutexChangedFibElements.unlock();
		return false;
	}
	//search the contained Fib elements, if they are changed Fib elements
	const map< typeChange, set< const cFibElement * > >::const_iterator
		itrFoundSetChangedFibElements = mapChangedFibElements.find( changeType );
	
	if ( itrFoundSetChangedFibElements != mapChangedFibElements.end() ) {
		
		const set< const cFibElement * > & setChangedFibElements =
			itrFoundSetChangedFibElements->second;
		//the list with the subobjects to check if they are changed objects
		list< cFibElement * > liCheckSubobjects = pFibElement->getSubobjects();
		list< const cFibElement * > liCheckedSubobjects;
		liCheckedSubobjects.push_back( pFibElement );
		const cFibElement * pActualSubobject;
		while ( ! liCheckSubobjects.empty() ) {
			//search for subobject / Fib element which was changed
			pActualSubobject = liCheckSubobjects.front();
			liCheckSubobjects.pop_front();
			liCheckedSubobjects.push_back( pActualSubobject );
			
			//check if the actual Fib element is a changed Fib element
			if ( ( setChangedFibElements.find( pActualSubobject ) !=
					setChangedFibElements.end() ) ||
				( setSuperiorToChanged.find( pActualSubobject ) !=
					setSuperiorToChanged.end() ) ) {
				/*changed Fib element or Fib element superior to it found
				 -> the Fib elements pFibElement is superior to a changed Fib element*/
				setSuperiorToChanged.insert( pFibElement );
				/*to speed up later evaluations add superior of actual Fib element /
				 subobject to set of superior Fib elements (often found superior
				 Fib element branches will add more Fib elements to the set)*/
				setSuperiorToChanged.insert( pActualSubobject->getSuperiorFibElement() );
				mutexChangedFibElements.unlock();
				return true;
			}
		}/*else if ( liCheckSubobjects.empty() )
		-> no Fib element / subobject which was changed found
		-> add all checked subobjects as not superior to changed Fib element*/
		setNotSuperiorToChanged.insert(
			liCheckedSubobjects.begin(), liCheckedSubobjects.end() );
	}//else no changed Fib elements -> no superior for them
	
	mutexChangedFibElements.unlock();
	return false;
}


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
bool eFibNodeChangedEvent::isContainedInChangedElement(
		const cFibElement * pFibElement,
		const typeChange changeType ) const {
	
	if ( pFibElement == NULL ) {
		//no Fib element given -> can't be contained in changed Fib element
		return false;
	}
	//check if the given Fib element was found before as contained in a changed Fib element
	mutexChangedFibElements.lock();
	//check if the Fib element was deleted
	std::map< typeChange, std::set< const cFibElement * > >::const_iterator
		itrDeletedFibElements = mapChangedFibElements.find( DELETED );
	if ( itrDeletedFibElements != mapChangedFibElements.end() ) {
		if ( itrDeletedFibElements->second.find( pFibElement ) !=
				itrDeletedFibElements->second.end() ) {
			//Fib element was deleted -> can't be contained in anything
			mutexChangedFibElements.unlock();
			return false;
		}
	}
	set< const cFibElement * > & setContainedInChanged =
		mapContainedInChangedFibElements[ changeType ];
	
	if ( setContainedInChanged.find( pFibElement ) != setContainedInChanged.end() ) {
		//the given Fib element is contained in a changed Fib element
		mutexChangedFibElements.unlock();
		return true;
	}
	//check if the given Fib element was found before as not contained in a changed Fib element
	set< const cFibElement * > & setNotContainedInChanged =
		mapNotContainedInChangedFibElements[ changeType ];
	
	if ( setNotContainedInChanged.find( pFibElement ) != setNotContainedInChanged.end() ) {
		//the given Fib element is not contained in a changed Fib element
		mutexChangedFibElements.unlock();
		return false;
	}
	//search the superior Fib elements, if they are changed Fib elements
	const map< typeChange, set< const cFibElement * > >::const_iterator
		itrFoundSetChangedFibElements = mapChangedFibElements.find( changeType );
	
	if ( itrFoundSetChangedFibElements != mapChangedFibElements.end() ) {
		
		const set< const cFibElement * > & setChangedFibElements =
			itrFoundSetChangedFibElements->second;
		
		//the list with the subobjects to check if they are changed objects
		const cFibElement * pActualSuperior = pFibElement->getSuperiorFibElement();
		list< const cFibElement * > liCheckedSuperiors;
		liCheckedSuperiors.push_back( pFibElement );
		
		while ( pActualSuperior != NULL ) {
			//search for superior Fib element which was changed
			liCheckedSuperiors.push_back( pActualSuperior );
			
			//check if the actual superior Fib element is a changed Fib element
			if ( ( setChangedFibElements.find( pActualSuperior ) !=
					setChangedFibElements.end() ) ||
				( setContainedInChanged.find( pActualSuperior ) !=
					setContainedInChanged.end() ) ) {
				/*changed Fib element or Fib element contained in it found
				 -> all checked superior Fib elements are contained in to a
				 changed Fib element*/
				setContainedInChanged.insert(
					liCheckedSuperiors.begin(), liCheckedSuperiors.end() );
				mutexChangedFibElements.unlock();
				return true;
			}
			//check next superior Fib element
			pActualSuperior = pActualSuperior->getSuperiorFibElement();
		}/*else if ( pActualSuperior == NULL )
		-> no superior Fib element which was changed found
		-> add all checked superior Fib elements as not contained in a changed
		Fib element*/
		setNotContainedInChanged.insert(
			liCheckedSuperiors.begin(), liCheckedSuperiors.end() );
	}//else no changed Fib elements -> nothing contained in them
	
	mutexChangedFibElements.unlock();
	return false;
}


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
bool eFibNodeChangedEvent::isChangedObjectBranch( const cFibElement * pFibObject,
		const typeChange changeType ) const {
	
	return isObjectChanged( pFibObject, changeType ) ||
		isSuperiorToChangedObject( pFibObject, changeType ) ||
		isContainedInChangedObject( pFibObject, changeType );
}


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
bool eFibNodeChangedEvent::isSuperiorToChangedObject(
		const cFibElement * pFibElement,
		const typeChange changeType ) const {
	
	if ( pFibElement == NULL ) {
		//no Fib element given -> can't be superior
		return false;
	}
	//check if the given Fib element was found before as superior
	mutexChangedFibObjects.lock();
	//check if the Fib element was deleted
	std::map< typeChange, std::set< const cFibElement * > >::const_iterator
		itrDeletedFibElements = mapChangedFibElements.find( DELETED );
	if ( itrDeletedFibElements != mapChangedFibElements.end() ) {
		if ( itrDeletedFibElements->second.find( pFibElement ) !=
				itrDeletedFibElements->second.end() ) {
			//Fib element was deleted -> can't be superior to anything
			mutexChangedFibObjects.unlock();
			return false;
		}
	}
	set< const cFibElement * > & setSuperiorToChanged =
		mapSuperiorToChangedFibObjects[ changeType ];
	
	if ( setSuperiorToChanged.find( pFibElement ) != setSuperiorToChanged.end() ) {
		//the given Fib element is superior to a changed Fib object
		mutexChangedFibObjects.unlock();
		return true;
	}
	//check if the given Fib element was found before as not superior
	set< const cFibElement * > & setNotSuperiorToChanged =
		mapNotSuperiorToChangedFibObjects[ changeType ];
	
	if ( setNotSuperiorToChanged.find( pFibElement ) != setNotSuperiorToChanged.end() ) {
		//the given Fib element is not superior to a changed Fib object
		mutexChangedFibObjects.unlock();
		return false;
	}
	//search the contained Fib elements, if they are changed Fib object
	const map< typeChange, set< const cFibElement * > >::const_iterator
		itrFoundSetChangedFibObjects = mapChangedFibObjects.find( changeType );
	
	if ( itrFoundSetChangedFibObjects != mapChangedFibObjects.end() ) {
		
		const set< const cFibElement * > & setChangedFibObjects =
			itrFoundSetChangedFibObjects->second;
		
		//the list with the subobjects to check if they are changed objects
		list< cFibElement * > liCheckSubobjects = pFibElement->getSubobjects();
		list< const cFibElement * > liCheckedSubobjects;
		liCheckedSubobjects.push_back( pFibElement );
		const cFibElement * pActualSubobject;
		while ( ! liCheckSubobjects.empty() ) {
			//search for subobject / Fib element which was changed
			pActualSubobject = liCheckSubobjects.front();
			liCheckSubobjects.pop_front();
			liCheckedSubobjects.push_back( pActualSubobject );
			
			//check if the actual Fib element is a changed Fib object
			if ( ( setChangedFibObjects.find( pActualSubobject ) !=
					setChangedFibObjects.end() ) ||
				( setSuperiorToChanged.find( pActualSubobject ) !=
					setSuperiorToChanged.end() ) ) {
				/*changed Fib element or Fib element superior to it found
				 -> the Fib elements pFibElement is superior to a changed Fib object*/
				setSuperiorToChanged.insert( pFibElement );
				/*to speed up later evaluations add superior of actual Fib element /
				 subobject to set of superior Fib elements (often found superior
				 Fib element branches will add more Fib elements to the set)*/
				setSuperiorToChanged.insert( pActualSubobject->getSuperiorFibElement() );
				mutexChangedFibObjects.unlock();
				return true;
			}
		}/*else if ( liCheckSubobjects.empty() )
		-> no Fib object / subobject which was changed found
		-> add all checked subobjects as not superior to changed Fib object*/
		setNotSuperiorToChanged.insert(
			liCheckedSubobjects.begin(), liCheckedSubobjects.end() );
	}//else no changed Fib objects -> nothing superior to them
	
	mutexChangedFibObjects.unlock();
	return false;
}


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
bool eFibNodeChangedEvent::isContainedInChangedObject(
		const cFibElement * pFibElement,
		const typeChange changeType ) const {
	
	if ( pFibElement == NULL ) {
		//no Fib element given -> can't be contained in changed Fib object
		return false;
	}
	//check if the given Fib element was found before as contained in a changed Fib object
	mutexChangedFibObjects.lock();
	//check if the Fib element was deleted
	std::map< typeChange, std::set< const cFibElement * > >::const_iterator
		itrDeletedFibElements = mapChangedFibElements.find( DELETED );
	if ( itrDeletedFibElements != mapChangedFibElements.end() ) {
		if ( itrDeletedFibElements->second.find( pFibElement ) !=
				itrDeletedFibElements->second.end() ) {
			//Fib element was deleted -> can't be contained in anything
			mutexChangedFibObjects.unlock();
			return false;
		}
	}
	set< const cFibElement * > & setContainedInChanged =
		mapContainedInChangedFibObjects[ changeType ];
	
	if ( setContainedInChanged.find( pFibElement ) != setContainedInChanged.end() ) {
		//the given Fib element is contained in a changed Fib object
		mutexChangedFibObjects.unlock();
		return true;
	}
	//check if the given Fib element was found before as not contained in a changed Fib object
	set< const cFibElement * > & setNotContainedInChanged =
		mapNotContainedInChangedFibObjects[ changeType ];
	
	if ( setNotContainedInChanged.find( pFibElement ) != setNotContainedInChanged.end() ) {
		//the given Fib element is not contained in a changed Fib object
		mutexChangedFibObjects.unlock();
		return false;
	}
	//search the superior Fib elements, if they are changed Fib objects
	const map< typeChange, set< const cFibElement * > >::const_iterator
		itrFoundSetChangedFibObjects = mapChangedFibObjects.find( changeType );
	
	if ( itrFoundSetChangedFibObjects != mapChangedFibObjects.end() ) {
		
		const set< const cFibElement * > & setChangedFibObjects =
			itrFoundSetChangedFibObjects->second;
		//the list with the subobjects to check if they are changed objects
		const cFibElement * pActualSuperior = pFibElement->getSuperiorFibElement();
		list< const cFibElement * > liCheckedSuperiors;
		liCheckedSuperiors.push_back( pFibElement );
		
		while ( pActualSuperior != NULL ) {
			//search for superior Fib element which was changed
			liCheckedSuperiors.push_back( pActualSuperior );
			
			//check if the actual superior Fib element is a changed Fib object
			if ( ( setChangedFibObjects.find( pActualSuperior ) !=
					setChangedFibObjects.end() ) ||
				( setContainedInChanged.find( pActualSuperior ) !=
					setContainedInChanged.end() ) ) {
				/*changed Fib object or Fib element contained in it found
				 -> all checked superior Fib elements are contained in a
				 changed Fib object*/
				setContainedInChanged.insert(
					liCheckedSuperiors.begin(), liCheckedSuperiors.end() );
				mutexChangedFibObjects.unlock();
				return true;
			}
			//check next superior Fib element
			pActualSuperior = pActualSuperior->getSuperiorFibElement();
		}/*else if ( pActualSuperior == NULL )
		-> no superior Fib object which was changed found
		-> add all checked superior Fib elements as not contained in a changed
		Fib object*/
		setNotContainedInChanged.insert(
			liCheckedSuperiors.begin(), liCheckedSuperiors.end() );
	}//else no changed Fib objects -> nothing contained in them
	
	mutexChangedFibObjects.unlock();
	return false;
}




























