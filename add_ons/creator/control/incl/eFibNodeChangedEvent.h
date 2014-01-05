
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
 * @pattern event
 * @see cFibNode
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

#include <QObject>


namespace fib{

namespace nCreator{

//cyclic dependencies
class cFibNode;

class eFibNodeChangedEvent{
public:
	
	/**
	 * A pointer to the Fib node that was changed.
	 */
	const cFibNode * pFibNodeChanged;
	
	
	/**
	 * The version of the Fib object for the node, when this event was generated.
	 * Every time the Fib object is changed the version number is counted up.
	 * @see cFibNode::getFibObjectVersion()
	 */
	const unsigned long ulVersion;
	
	/**
	 * A pointer to the object which had changed the Fib node.
	 */
	const QObject * pChangedBy;
	
	/**
	 * If true the node is deleted.
	 */
	bool bNodeDeleted;
	
	
	/** TODO?
	 * Number of Fib object containing all changes (with highest Fib object number)
	 * unsigned int uiFibObjectNumber;
	 * 
	 * Number of First changed Fib element (Fib Element containing all
	 * changed Fib elements) + pointer to changed element (to check if this
	 * change was the last change)
	 * unsigned int uiFibElementNumber;
	 * 
	 * enum changeType{ CHANGED_ELEMENT, DELETED_ELEMENTS, ADDED_ELEMENTS, MOVED_ELEMENT }
	 */
	
	/**
	 * constructor
	 *
	 * @param pInFibNode a pointer to the Fib node that was changed
	 * 	@see pFibNodeChanged
	 * @param ulInVersion the version of the Fib object for the node, when
	 * 	this event was generated;
	 * 	@see cFibNode::getFibObjectVersion()
	 * @param pInChangedBy a pointer to the object which had changed the Fib node
	 * 	@see pChangedBy
	 */
	eFibNodeChangedEvent( const cFibNode * pInFibNode,
		const unsigned long ulInVersion,
		const QObject * pInChangedBy );
	
	/**
	 * @return the name of this class "eFibNodeChangedEvent"
	 */
	std::string getName() const;
	
};//end class eFibNodeChangedEvent

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__E_FIB_NODE_CHANGED_EVENT_H__





