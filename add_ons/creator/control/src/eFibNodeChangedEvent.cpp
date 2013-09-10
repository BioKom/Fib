
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
 * This file implements a event for Fib object node changes.
 * If a Fib object changes, the Fib object nodes (cFibNode) for it will
 * send a event of this type to all registered listeners of type.
 * @see cFibNode
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
 * @param ulInVersion the version of the Fib object for the node, when
 * 	this event was generated;
 * 	@see cFibNode::getFibObjectVersion()
 * @param pInChangedBy a pointer to the object which had changed the Fib node
 * 	@see pChangedBy
 */
eFibNodeChangedEvent::eFibNodeChangedEvent( const cFibNode * pInFibNode,
	const unsigned long ulInVersion,
	const QObject * pInChangedBy ): pFibNodeChanged( pInFibNode ),
		ulVersion( ulInVersion ), pChangedBy( pInChangedBy ), bNodeDeleted( false ){
	//nothing to do
}


/**
 * @return the name of this class "eFibNodeChangedEvent"
 */
string eFibNodeChangedEvent::getName() const{
	
	return "eFibNodeChangedEvent";
}






