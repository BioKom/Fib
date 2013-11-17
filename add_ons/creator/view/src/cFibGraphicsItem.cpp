
//TODO check

/**
 * @file cFibGraphicsItem
 * file name: cFibGraphicsItem.cpp
 * @author Betti Oesterholz
 * @date 17.07.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a abstract class for a graphics item for a Fib object.
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
 * This file specifies a abstract class for a graphics item for a Fib object.
 * It should be the parent of all graphics item classes for Fib objects.
 * It will display a (part) Fib object as an graphic item.
 * The item correspondents to a Fib object or a part of a Fib object. For
 * this Fib object the graphic / image representation will be shown by its
 * cFibGraphicsItem.
 *
 * @see QGraphicsScene
 * @see cFibGraphicsScene
 * @see QGraphicsItem
 */
/*
History:
17.07.2013  Oesterholz  created
*/



#include "cFibGraphicsItem.h"

#include "cFibGraphicsScene.h"
#include "cFibNode.h"


using namespace fib::nCreator;


/**
 * parameter constructor for a graphics item for a Fib object
 *
 * @param pInFibObject a pointer to the Fib object object for the
 * 	widget / item to construct
 * 	@see pFibObject
 * @param ulInFibNodeVersionDisplayed the Fib node version of the
 * 	Fib object, wich is displayed
 * 	@see ulFibNodeVersionDisplayed
 * @param pParent a pointer to parent of this widget
 */
cFibGraphicsItem::cFibGraphicsItem( cFibElement * pInFibObject,
		const unsigned long ulInFibNodeVersionDisplayed,
		QGraphicsItem * pParent ):QGraphicsItem( pParent ),
		pFibObject( pInFibObject ),
		ulFibNodeVersionDisplayed( ulInFibNodeVersionDisplayed ),
		pFibGraphicsScene( NULL ){
	
	//nothing to do
}


/**
 * parameter constructor for a graphics item for a Fib object
 *
 * @param pInFibObject a pointer to the Fib object object for the
 * 	widget / item to construct
 * 	@see pFibObject
 * @param ulInFibNodeVersionDisplayed the Fib node version of the
 * 	Fib object, wich is displayed
 * 	@see ulFibNodeVersionDisplayed
 * @param pInFibGraphicsScene a pointer to the graphic scene for this
 * 	widget / item
 * 	@see pFibGraphicsScene
 * @param pParent a pointer to parent of this widget
 */
cFibGraphicsItem::cFibGraphicsItem( cFibElement * pInFibObject,
		const unsigned long ulInFibNodeVersionDisplayed,
		cFibGraphicsScene * pInFibGraphicsScene,
		QGraphicsItem * pParent ):QGraphicsItem( pParent ),
		pFibObject( pInFibObject ),
		ulFibNodeVersionDisplayed( ulInFibNodeVersionDisplayed ),
		pFibGraphicsScene( pInFibGraphicsScene ){
	
	//nothing to do
}


/**
 * destructor
 */
cFibGraphicsItem::~cFibGraphicsItem(){
	
	//nothing to do
}


/**
 * @return a pointer to the Fib object this widget / item represents
 * 	@see pFibObject
 */
cFibElement * cFibGraphicsItem::getFibObject(){
	
	return pFibObject;
}


/**
 * @return a pointer to the Fib object this widget / item represents
 * 	@see pFibObject
 */
const cFibElement * cFibGraphicsItem::getFibObject() const{
	
	return pFibObject;
}


/**
 * @return the name of this class "cFibGraphicsItem"
 */
std::string cFibGraphicsItem::getName() const{
	
	return std::string( "cFibGraphicsItem" );
}


/**
 * This slot will notify the Fib node, which contains this graphic item
 * Fib object, that it was changed.
 * This method should be called if the Fib object of this widget
 * changes.
 * @see fibNodeChangedEvent()
 */
void cFibGraphicsItem::notifyNodeForChange(){
	
	if ( pFibGraphicsScene ){
		cFibNode * pFibNode = pFibGraphicsScene->getFibNode();
		if ( pFibNode == NULL ){
			//Error: no Fib node to notify
			return;
		}
		/*TODO give information what was changed (Fib object point begin + end
		+ Fib element number start + end)*/
		eFibNodeChangedEvent fibNodeChangedEvent(
			pFibNode, ulFibNodeVersionDisplayed, pFibGraphicsScene );
		
		pFibNode->fibObjectChanged( fibNodeChangedEvent );
	}
}







