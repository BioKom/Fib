
//TODO check

/**
 * @file cFibNodeHandler
 * file name: cFibNodeHandler.h
 * @author Betti Oesterholz
 * @date 14.06.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for handling Fib object nodes for the
 * Fib creator application.
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
 * This file specifies a class for handling Fib object nodes for the
 * Fib creator application.
 * It should store all the Fib nodes of the application and make sure,
 * that for every Fib object there is exactly one Fib node.
 * It will link Fib nodes to there superior and lower nodes.
 * @see cFibNode::setNextSuperiorNodes
 * @see cFibNode::setNextLowerNodes
 * It will also delete Fib nodes without a listener and delete Fib object
 * roots without a Fib nodes for it or a contained Fib object.
 * So if you remove the last listener from a Fib node, which is handeled by
 * this object, you should treat the Fib node as deleted.
 *
 * @pattern singelton
 */
/*
History:
14.06.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_FIB_NODE_HANDLER_H__
#define ___FIB__NCREATOR__C_FIB_NODE_HANDLER_H__

#include "version.h"

#include "cFibNode.h"

#include <map>
#include <set>
#include <ctime>

#include <QMutex>
#include <QObject>

#include "cFibElement.h"



using namespace std;


namespace fib{

namespace nCreator{

namespace nFibNodeHandler{
	//cyclic dependencies
	class cFibNodeHandlerDeleter;
	class cThreadDeleteNodesWithoutListener;
}

class cFibNodeHandler{

friend class nFibNodeHandler::cFibNodeHandlerDeleter;
friend class nFibNodeHandler::cThreadDeleteNodesWithoutListener;

public:
	
	/**
	 * destructor
	 */
	virtual ~cFibNodeHandler();
	
	/**
	 * @return a instance of the Fib object node handler
	 */
	static cFibNodeHandler * getInstance();
	
	
	/**
	 * This method returns the Fib node for the given Fib object.
	 * If no Fib node exists till now one is created.
	 * Beware: Nodes without a listener will be deleted.
	 * 	Also root Fib objects wich don't contain a Fib object to which
	 * 	a node points, will be deleted.
	 *
	 * @see mapFibNodes
	 * @param pFibObject the Fib object for the Fib node to return
	 * @param pFibNodeChangeListener the listener for node changes of the to
	 * 	return Fib node
	 * @param bIsChangebel true (standard value) if (the Fib element
	 * 	 pFibObject of) the to create node is changebel, else false
	 * @return the Fib node for the given Fib object
	 */
	cFibNode * getNodeForFibObject( cFibElement * pFibObject,
			lFibNodeChanged * pFibNodeChangeListener,
			const bool bIsChangebel=true );
	
	/**
	 * This method checks if the given pointer points to a in this handler
	 * existing Fib node.
	 *
	 * @param pFibNode a pointer to the Fib node to check
	 * @return true if the given Fib node points to an existing Fib node
	 * 	in this handler, else false
	 */
	bool isValidNode( cFibNode * pFibNode );
	
	/**
	 * This method returns the next Fib node, which contains the given Fib
	 * object.
	 * Beware: Nodes without a listener will be deleted.
	 * 	Also root Fib objects, wich don't contain a Fib object, to which
	 * 	a node points, will be deleted.
	 *
	 * @see mapFibNodes
	 * @see getNodeForFibObject()
	 * @param pFibObject the Fib object for the Fib node to return
	 * @return the next Fib node which contains the given Fib object, or
	 * 	NULL if non exists
	 */
	cFibNode * getContainingNodeForFibObject( cFibElement * pFibObject );
	
	
	/**
	 * This method integrates the given Fib object into the given other Fib object.
	 * All not needed parts of the Fib objects will be deleted.
	 *
	 * @param pContainingNode a pointer to the node which contains the
	 * 	Fib object to replace
	 * @param pOriginalFibObjectToReplace the Fib object which to replace with
	 * 	the given other Fib object pNewFibObject
	 * @param pNewFibObject the Fib object which schould be integrated
	 * @param pChangedBy a pointer to the object which had created the new
	 * 	Fib object pNewFibObject (which called this method)
	 * @return true if the Fib object could be integrated
	 */
	bool integrateFibObjectIntoNode( cFibNode * pContainingNode,
		cFibElement * pOriginalFibObjectToReplace, cFibElement * pNewFibObject,
		const QObject * pChangedBy = NULL );
	
	/**
	 * This method locks the whole Fib object (the Fib master root object)
	 * for the given Fib node. If another thread has locked one of the
	 * Fib nodes for Fib objects for the whole Fib object of the given
	 * Fib node then this call will block until that thread has unlocked it.
	 * @see unlock( cFibNode * pFibNode )
	 * @see tryLock( cFibNode * pFibNode )
	 * @see mapFibObjectRootsMutex
	 * @see QMutex::tryLock()
	 *
	 * @param pFibNode the node for which to lock the whole Fib object
	 * @return true if the Fib object could be locked (whole Fib object exists)
	 */
	bool lock( cFibNode * pFibNode );
	
	/**
	 * This method attempts to lock the whole Fib object (the Fib master
	 * root object) for the given Fib node.
	 * This method returns true if the lock was obtained, otherwise it
	 * returns false.
	 * If another thread has locked one of the Fib object, this method will
	 * wait for at most timeout milliseconds for a Fib node to become
	 * available.
	 * Note: Passing a negative number as the timeout is equivalent to
	 * calling lock(), i.e. this method will wait forever until Fib object
	 * can be locked if timeout is negative.
	 *
	 * If the lock was obtained, the Fib object must be unlocked with unlock()
	 * before another thread can successfully lock it.
	 *
	 * @see lock()
	 * @see unlock()
	 * @see mapFibObjectRootsMutex
	 * @see QMutex::tryLock()
	 *
	 * @param pFibNode the node for which to lock the whole Fib object
	 * @param iTimeout the time an milliseconds to wait for a Fib node to
	 * 	become available
	 * @return true if the lock was obtained, otherwise it returns false
	 */
	bool tryLock( cFibNode * pFibNode, int iTimeout = 0 );
	
	/**
	 * This method unlocks the whole Fib object (the Fib master root object)
	 * for the given Fib node.
	 * Attempting to unlock a Fib object in a different thread to the one that
	 * locked it results in an error. Unlocking a Fib object that is not
	 * locked results in undefined behavior.
	 *
	 * @see lock()
	 * @see tryLock( cFibNode * pFibNode )
	 * @see mapFibObjectRootsMutex
	 * @see QMutex::unlock()
	 *
	 * @param pFibNode the node for which to unlock the whole Fib object
	 * @return true if the Fib object could be unlocked (whole Fib object exists)
	 */
	bool unlock( cFibNode * pFibNode );
	
	
protected:
	
	/**
	 * constructor for the Fib object node handler
	 */
	cFibNodeHandler();
	
	/**
	 * This method returns the mutex for the given Fib node.
	 * @see lock( cFibNode * pFibNode )
	 * @see unlock( cFibNode * pFibNode )
	 * @see tryLock( cFibNode * pFibNode )
	 * @see mapFibObjectRootsMutex
	 *
	 * @param pFibNode a pointer to the node for which to return the mutex
	 * @return a pointer to the mutex for the given Fib node, or NULL if non exists
	 */
	QMutex * getMutex( cFibNode * pFibNode );
	
	
	/**
	 * This method returns all superior Fib objects to the given Fib object,
	 * in the evaluation order.
	 * Normaly a superior Element to a given Fib object is the superior
	 * Fib element in all of the root Fib object. But if external objects
	 * are used, a superior Fib object to a subroot object are the externel
	 * object elements where the subroot object is used.
	 *
	 * @param pFibObject the Fib object for which to return the superior
	 * 	Fib objects
	 * @return a list with all superior Fib objects of the given Fib object
	 * 	pFibObject
	 */
	list<cFibElement *> getSuperiorFibElements( cFibElement * pFibObject );
	
	
	/**
	 * This method will delete all Fib nodes without listeners.
	 * It will also delete all Fib object roots without nodes for the
	 * Fib object root or a contained Fib object.
	 * @see mapFibNodes
	 * @see setFibObjectsRoot
	 */
	void deleteNodesWithoutListeners();
	
	
	
	/**
	 * This method will transfer the given Fib node and all Fib nodes for
	 * Fib objects, which the Fib object for the given Fib node contains,
	 * from one Fib object to a other Fib object.
	 * For that the path from the given node pNodeToTransfer Fib object to
	 * the (root) Fib element of the from Fib object pFromFibObject will be
	 * evalued and the Fib node will be set to a Fib object, which path to the
	 * Fib element pToFibObject is as similar as posible to the original path.
	 * If more than one path is equal, the node will be set to the first
	 * Fib object, which is (most) equal to its original Fib object.
	 * This procedure will be repeated for all Fib nodes for Fib objects
	 * containd in the given Fib nodes pNodeToTransfer Fib object.
	 *
	 * @param pNodeToTransfer a pointer to the Fib node, which and which lower
	 * 	Fib nodes to transfer, its Fib object should be contained in pFromFibObject
	 * @param pFromFibObject a pointer to the Fib object, from which to transfer
	 * 	the Fib node (pNodeToTransfer)
	 * @param pToFibObject a pointer to the Fib object, to which to transfer the
	 * 	Fib nodes (pNodeToTransfer)
	 * @return set of the pointers to the lowest nodes, which subobjects where changed
	 * 		(they have no nodes below, which contain changed subobjects)
	 */
	set< cFibNode * > transferNode( cFibNode * pNodeToTransfer,
			cFibElement * pFromFibObject, cFibElement * pToFibObject );
	
	/**
	 * This method will transfer the given Fib node and all Fib nodes for
	 * Fib objects, which the Fib object for the given Fib node contains,
	 * from one Fib object to a other Fib object.
	 * Both given Fib object have to be equal (pFromFibObject->equal( *pToFibObject )).
	 * The Fib nodes will be transfered to the Fib element in the to Fib object
	 * (pToFibObject) with the same Fib element number as the original Fib object
	 * for the Fib node. (The Fib element numbers are relativ to the pFromFibObject
	 * and pToFibObject Fib element numbers.)
	 *
	 * @param pNodeToTransfer a pointer to the Fib node, which and which lower
	 * 	Fib nodes to transfer, its Fib object should be contained in pFromFibObject
	 * @param pFromFibObject a pointer to the Fib object, from which to transfer
	 * 	the Fib node (pNodeToTransfer);
	 * 	it should be equal to pToFibObject
	 * @param pToFibObject a pointer to the Fib object, to which to transfer the
	 * 	Fib nodes (pNodeToTransfer)
	 * 	it should be equal to pFromFibObject
	 * @return true if the Fib nodes where transfered, else false
	 */
	bool transferNodeForEqualFibObject(
			cFibNode * pNodeToTransfer,
			cFibElement * pFromFibObject, cFibElement * pToFibObject );

//members
	
	/**
	 * A pointer to the node handler object.
	 */
	static cFibNodeHandler * pFibNodeHandler;
	
	/**
	 * A set with the existing Fib object roots.
	 */
	set< cFibElement * > setFibObjectsRoot;
	
	/**
	 * A set with the existing Fib nodes.
	 */
	set< cFibNode * > setFibNodes;
	
	/**
	 * The map for the existing Fib nodes.
	 * 	key: the Fib objects for the value Fib node
	 * 	value: the Fib nodes for the key Fib objects
	 */
	map< cFibElement * , cFibNode * > mapFibNodes;
	
	/**
	 * The map for the existing Fib object roots.
	 * 	key: the Fib objects for the Fib object roots
	 * 	value: the Fib object roots for the key Fib objects
	 * 		@see setFibObjectsRoot
	 */
	map< cFibElement * , cFibElement * > mapFibObjectRoots;
	
	/**
	 * The map for the existing Fib object roots.
	 * 	key: the Fib object roots for the value Fib object nodes
	 * 	value: a list with the Fib object nodes for the Fib object root
	 */
	map< cFibElement * , set< cFibNode * > > mapNodesForRoots;
	
	/**
	 * Mutex to lock access to the Fib object and Fib node data of this class.
	 * Lock the mutex if you use one of the following containers:
	 * @see setFibObjectsRoot
	 * @see setFibNodes
	 * @see mapFibNodes
	 * @see mapFibObjectRoots
	 * @see mapNodesForRoots
	 */
	QMutex mutexFibNodeHandler;
	
	/**
	 * The map for the existing Fib object roots mutexs.
	 * 	key: the Fib object roots
	 * 		@see setFibObjectsRoot
	 * 	value: the mutex for the key Fib object roots
	 * @see lock()
	 * @see tryLock()
	 * @see unlock()
	 */
	map< cFibElement * , QMutex * > mapFibObjectRootsMutex;

	/**
	 * The next time it should be tried to delete not needed nodes.
	 * @see deleteNodesWithoutListeners()
	 */
	time_t tmNextDeleteNodesAction;
	
};//end class cFibNodeHandler

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_NODE_HANDLER_H__





