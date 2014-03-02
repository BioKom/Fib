
//TODO check

/**
 * @file cThreadSendFibElementChangedViaFibNode
 * file name: cThreadSendFibElementChangedViaFibNode.cpp
 * @author Betti Oesterholz
 * @date 08.02.2014
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This is a worker class for a thread.
 * It will send, that a Fib element changed to the Fib node of the Fib element.
 *
 *
 * Copyright (C) @c GPL3 2014 Betti Oesterholz
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
 * This is a worker class for a thread.
 * It will send, that a Fib element changed to the Fib node of the Fib element.
 *
 * @pattern worker
 * @see eFibNodeChangedEvent
 * @see fib::cFibElement
 * @see cFibNode
 * @see cFibNodeHandler
 * @see QThread
 */
/*
History:
08.02.2014  Oesterholz  created
*/



#include "cThreadSendFibElementChangedViaFibNode.h"


#include "cFibNode.h"
#include "eFibNodeChangedEvent.h"
#include "cFibNodeHandler.h"


using namespace fib::nCreator;
using namespace fib;


/**
 * The standard constructor for a worker.
 *
 * @param pInChangedFibElement a pointer to the changed Fib element
 * 	@see pChangedFibElement
 */
cThreadSendFibElementChangedViaFibNode::cThreadSendFibElementChangedViaFibNode(
		cFibElement * pInChangedFibElement ):
		pChangedFibElement( pInChangedFibElement ) {
	//nothing to do
}


/**
 * destructor
 */
cThreadSendFibElementChangedViaFibNode::~cThreadSendFibElementChangedViaFibNode() {
	//nothing to do
}


/**
 * This method will send that a Fib element changed to the Fib node of
 * the Fib element.
 */
void cThreadSendFibElementChangedViaFibNode::run() {
	
	if ( pChangedFibElement != NULL ) {
		//send node changed event
		cFibNodeHandler * pFibNodeHandler = cFibNodeHandler::getInstance();
		cFibNode * pChangedNode = pFibNodeHandler->
			getContainingNodeForFibObject( pChangedFibElement );
		
		DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::sendNodeChangedEvent() send node changed event to node "<<pChangedNode<<endl<<flush);
		pFibNodeHandler->lock( pChangedNode );
		if ( ( pChangedNode != NULL ) &&
				pFibNodeHandler->isValidNode( pChangedNode ) ) {
			//the node still exists (after the lock)
			//generate the Fib node change event
			eFibNodeChangedEvent eventNodeChanged( pChangedNode,
				pChangedNode->getFibObjectVersion(), this );
			//the defining Fib element changed
			eventNodeChanged.addChangedFibElement(
				pChangedFibElement, eFibNodeChangedEvent::CHANGED );
			//just values chaged
			eventNodeChanged.setJustValuesChanged();
			
			pFibNodeHandler->unlock( pChangedNode );
			
			pChangedNode->fibObjectChanged( eventNodeChanged );
			/*alternativ if signals are implemented
			if ( pChangedNode->fibObjectChanged( eventNodeChanged ) ) {
				//changes could be send
				emit finished();
			}else{
				emit error( "could not send the Fib vector changes via the Fib node" );
			}*/
		}else{//just unlock the Fib node
			pFibNodeHandler->unlock( pChangedNode );
		}
	}//else no Fib object -> no Fib node -> nothing to send a changed event for
	//emit error( "no Fib node -> nothing to send a changed event for" );
}





