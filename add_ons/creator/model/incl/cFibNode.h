
//TODO check

/**
 * @file cFibNode
 * file name: cFibNode.h
 * @author Betti Oesterholz
 * @date 11.06.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for Fib object nodes for the Fib creator
 * application.
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
 * This file specifies a class for Fib object nodes for the Fib creator
 * application.
 * When you work with the Fib creator on a Fib object it could be a part of
 * a bigger Fib object, this class is for handling this situation.
 * So you can open a Fib object and its parts in more than one window.
 * It stores the Fib element for the Fib node, its top most root element,
 * the next and previous existing Fib nodes (to be notified on changes).
 * You can register for listening if the node (or a Fib element contained
 * in the Fib object of the node) was changed.
 * The Fib object for the node should always contain the relevant Fib
 * object information. If for an object, which represents a part of the
 * Fib object (e.g. a widget for a vector element), its members are change,
 * the object should care, that this change is writen at once into the
 * Fib object for this node, it should also send a Fib node change event.
 * TODO:
 * It also stores the area / window (cPlainArea) of the Fib object this
 * node represents and the variables the Fib object use, but which aren't
 * defined in it. (These variables are the input parameters for the Fib object.)
 *
 * Normally for every Fib object (@see pFibObject) there should be just one node.
 *
 * TODO:
 * @see cPlainArea
 */
/*
History:
11.06.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_FIB_NODE_H__
#define ___FIB__NCREATOR__C_FIB_NODE_H__


#include "version.h"

#include <set>

#include <QObject>

#include "cFibElement.h"

#include "lFibNodeChanged.h"



using namespace std;


namespace fib{

namespace nCreator{

//cyclic dependencies
class cFibNodeHandler;
//forward declarations
class cFibObjectInfo;

class cFibNode{
public:
	
	/**
	 * parameter constructor for a Fib object node
	 *
	 * @param pInFibObject a pointer to the Fib object of the node to constructor
	 * 	@see pFibObject
	 * @param bInIsChangebel true (standard value) if (the Fib element of)
	 * 	the to create node is changebel, else false
	 */
	cFibNode( cFibElement * pInFibObject, const bool bInIsChangebel=true );
	
	
	/**
	 * copy constructor
	 *
	 * @param fibNode the Fib node of which to create a copy
	 */
	cFibNode( cFibNode & fibNode );
	
	/**
	 * destructor
	 */
	~cFibNode();
	
	
	/**
	 * @return a pointer to the Fib object this node represents or
	 * 	NULL if no changebel Fib object can be returned (e.g.
	 * 	if the Fib object is not changebel)
	 * 	@see pFibObject
	 * 	@see bIsChangebel
	 */
	cFibElement * getFibObject();
	
	/**
	 * @return a const pointer to the Fib object this node represents
	 * 	@see pFibObject
	 */
	const cFibElement * getFibObjectConst() const;
	
	/**
	 * Call this method if the Fib object for this node changed.
	 * @see pFibObject
	 * @see liNodeChangedListeners
	 * @see ulVersion
	 *
	 * @param pChangedBy a pointer to the object which had changed the Fib node
	 */
	bool fibObjectChanged( const QObject * pChangedBy = NULL );
	
	/**
	 * Call this method if the Fib object for this node changed.
	 * @see pFibObject
	 * @see liNodeChangedListeners
	 * @see ulVersion
	 * @see eFibNodeChangedEvent
	 *
	 * @param fibNodeChangedEvent the event with the change information
	 */
	bool fibObjectChanged( const eFibNodeChangedEvent & fibNodeChangedEvent );
	
	
	/**
	 * @return the version of the Fib object for the node
	 * 	Every time the Fib object is changed the version number is counted up.
	 * 	@see ulVersion
	 */
	unsigned long getFibObjectVersion() const;
	
	/**
	 * @return a pointer to the master root object of the Fib object this
	 * 	node represents or NULL if no changebel Fib object can be returned
	 * 	(e.g. if the Fib object is not changebel)
	 * 	@see pMasterRoot
	 * 	@see bIsChangebel
	 */
	cFibElement * getMasterRoot();
	
	/**
	 * @return a const pointer to the master root object of the Fib object
	 * 	this node represents
	 * 	@see pMasterRoot
	 */
	const cFibElement * getMasterRootConst() const;
	
	/**
	 * @return true if (the Fib element of) this node is changebel, else false
	 * 	@see bIsChangebel
	 */
	bool isChangebel() const;
	
	/**
	 * This method inserts the Fib object for the given Fib object info
	 * into the Fib object of this Fib object node.
	 * It will be tried to insert the given Fib object as a external
	 * subobject and a subroot object (if not a same subroot object allready
	 * exists).
	 *
	 * @see cFibElement::insertObjectInElement()
	 * @see cExtObject
	 * @see cRoot::integrateSubRootObject()
	 * @param pFibObjectInfo a pointer to the Fib object info object of
	 * 	the Fib object to insert
	 * @return true if the Fib object could be inserted, else false
	 */
	bool insertFibObjectInfo( cFibObjectInfo * pFibObjectInfo );
	
	/**
	 * This method evalues the changes needed for the Fib object of this
	 * node to become the given Fib object and stores them in the Fib
	 * node change event.
	 * The method will try to evalue as less as possible changes, but if
	 * the difference is to great, it will return not minimal changes.
	 * The returned changes will always be enought to transform this
	 * Fib nodes Fib object into the given Fib object.
	 * Note: If pOutFibNodeChangedEvent is NULL, you have to care that the
	 * 	returned Fib node changed event object will be deleted.
	 * Note: This method won't use a mutex.
	 *
	 * @param pInFibObject a pointer to the Fib object, into which this
	 * 	Fib node should be transformed
	 * @param pOutFibNodeChangedEvent a pointer to the Fib node changed
	 * 	event, into which the changes should be stored, or NULL, if a
	 * 	new Fib node changed event object should be created
	 * 	(Note: You have to set the Fib node for the event.)
	 * @return A pointer to the Fib node changed event object, which
	 * 	contains the information of the changes to transver this node into
	 * 	the given Fib object, or NULL, if non could be created (e.g.
	 * 	pInFibObject is NULL).
	 * 	If pOutFibNodeChangedEvent is NULL (or not given), you have to
	 * 	care that the returned Fib node changed event object will be deleted.
	 * 	The Fib element and Fib objects, in the returned Fib node changed
	 * 	event, will point to Fib elements in pInFibObject .
	 */
	eFibNodeChangedEvent * evalueChangesToFibObject(
		const cFibElement * pInFibObject,
		eFibNodeChangedEvent * pOutFibNodeChangedEvent = NULL ) const;
	
	/**
	 * With this function you can register a listeners for changes in the
	 * Fib object for this node.
	 *
	 * @see fibObjectChanged()
	 * @see unregisterNodeChangeListener()
	 * @see liNodeChangedListeners
	 * @see sendNodeChange()
	 * @param pNodeListener a pointer to the listener for changes
	 * @return true if the listener was registered, else false
	 */
	bool registerNodeChangeListener( lFibNodeChanged * pNodeListener );
	
	/**
	 * With this function you can unregister a listeners for changes in the
	 * Fib object for this node.
	 *
	 * @see fibObjectChanged()
	 * @see registerNodeChangeListener()
	 * @see liNodeChangedListeners
	 * @see sendNodeChange()
	 * @param pNodeListener a pointer to the listener for changes
	 * @return true if the listener was registered, else false
	 */
	bool unregisterNodeChangeListener( lFibNodeChanged * pNodeListener );
	
	
protected:
	
	/**
	 * This method will increase the Fib object version number for all
	 * Fib nodes for superior Fib objects. (The supperior Fib node
	 * Fib object has to contain this Fib node Fib object.)
	 * @see ulVersion
	 * @see fibObjectChanged()
	 */
	void increaseFibObjectVersion();
	
	
	/**
	 * This method sents a node changed event to all change node listeners
	 * of this object.
	 *
	 * @see liNodeChangedListeners
	 * @see setNextSuperiorNodes
	 * @see fibObjectChanged()
	 * @param pFibNodeChangedEvent the change event to send
	 */
	void sendNodeChange( const eFibNodeChangedEvent * pFibNodeChangedEvent );
	
//members:
	
	/**
	 * The node handler is a friend.
	 */
	friend class cFibNodeHandler;
	
	/**
	 * A pointer to the Fib object of this node.
	 * This node represents this Fib object.
	 * Normally for every Fib object there should be just one node.
	 */
	cFibElement * pFibObject;
	
	/**
	 * True if (the Fib element of) this node is changebel, else false.
	 * (This node is not changebel if it is a Fib database object.)
	 */
	bool bIsChangebel;
	
	/**
	 * The version of the Fib object for the node.
	 * Every time the Fib object is changed the version number is counted up.
	 * @see fibObjectChanged();
	 */
	unsigned long ulVersion;
	
	/**
	 * The pointer to the master root object of the Fib object of this node.
	 * @see pFibObject
	 * @see cFibElement::getMasterRoot()
	 */
	cFibElement * pMasterRoot;
	
	/**
	 * A list with the listeners for changes in the Fib object for this node.
	 * @see lFibNodeChanged
	 */
	set< lFibNodeChanged * > liNodeChangedListeners;
	
	/**
	 * A list with the existing next superior Fib element nodes of this node.
	 * They will be notifyed if (the Fib element of) this node changes.
	 * @see liNodeChangedListeners
	 * @see setNextLowerNodes
	 * For superior nodes external objects will be above / superior to the
	 * sub roots they represents.
	 */
	set< cFibNode * > setNextSuperiorNodes;
	
	/**
	 * A list with the existing next lower Fib element nodes of this node.
	 * The Fib objects of this nodes will be contained in this Fib object.
	 * @see setNextSuperiorNodes
	 * For lower nodes external objects will be above / superior to the
	 * sub roots they represents.
	 */
	set< cFibNode * > setNextLowerNodes;
	
	
};//end class cFibNode

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_NODE_H__





