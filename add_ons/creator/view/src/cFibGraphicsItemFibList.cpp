
//TODO check

/**
 * @file cFibGraphicsItemFibList
 * file name: cFibGraphicsItemFibList.cpp
 * @author Betti Oesterholz
 * @date 28.07.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a graphics item for a Fib list object.
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
 * This file implements a class for a graphics item for a Fib list object.
 * It will display a (part) list Fib object as a graphic item.
 * The item correspondents to a list Fib object. For this list Fib object
 * the graphic / image representation will be shown by its
 * cFibGraphicsItemFibList.
 * A list Fib object is a Fib object with a Fib list element as its top
 * most Fib element. It contains some (part) Fib objects, wich will be
 * contained in this object as cFibGraphicsItem objects. This class
 * is a child of QGraphicsItemGroup, so that it can containe some
 * cFibGraphicsItem objects.
 *
 * @see cFibElement::evalueObject()
 * @see QGraphicsItemGroup
 * @see cFibGraphicsItem
 * @see QGraphicsScene
 * @see cFibGraphicsScene
 * @see QGraphicsItem
 */
/*
History:
03.08.2013  Oesterholz  created
*/



#include "cFibGraphicsItemFibList.h"

#include "cFibGraphicsScene.h"


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
 * @param liInSubitems a list with the graphical subitems of this
 * 	graphical list item @see liSubitems
 * @param pParent a pointer to parent of this widget
 */
cFibGraphicsItemFibList::cFibGraphicsItemFibList( cFibElement * pInFibObject,
		const unsigned long ulInFibNodeVersionDisplayed,
		QList< cFibGraphicsItem * > liInSubitems,
		QGraphicsItem * pParent ):
		cFibGraphicsItem( pInFibObject, ulInFibNodeVersionDisplayed, pParent ),
		liSubitems(){
	//add all given subitems
	addSubitems( liInSubitems );
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
 * @param liInSubitems a list with the graphical subitems of this
 * 	graphical list item @see liSubitems
 * @param pParent a pointer to parent of this widget
 */
cFibGraphicsItemFibList::cFibGraphicsItemFibList( cFibElement * pInFibObject,
		const unsigned long ulInFibNodeVersionDisplayed,
		cFibGraphicsScene * pInFibGraphicsScene,
		QList< cFibGraphicsItem * > liInSubitems,
		QGraphicsItem * pParent ):
		cFibGraphicsItem( pInFibObject, ulInFibNodeVersionDisplayed,
			pInFibGraphicsScene, pParent ),
		liSubitems(){
	//add all given subitems
	addSubitems( liInSubitems );
}


/**
 * destructor
 */
cFibGraphicsItemFibList::~cFibGraphicsItemFibList(){
	//TODO what to do with the subitems liSubitems
}



/**
 * @return the name of this class "cFibGraphicsItemFibList"
 */
std::string cFibGraphicsItemFibList::getName() const{
	
	return std::string( "cFibGraphicsItemFibList" );
}


/**
 * @return the outer bounds of this graphic item
 * 	@see QGraphicsItem::boundingRect()
 */
QRectF cFibGraphicsItemFibList::boundingRect() const{
	
	return boundingRectangle;
}


/**
 * This method will evaluate the bounding rectangle for this list
 * graphic item. For that it will evaluate the smaalest bounding
 * rectangle, which contains all subitem bounding rectangles.
 * @see boundingRectangle
 * @see liSubitems
 * @see liSubitems::boundingRect()
 */
void cFibGraphicsItemFibList::evaluateBoundingRect(){
	
	QRectF boudingRectangleNew;
	if ( liSubitems.empty() ){
		//bounding rectangle should be empty
		boudingRectangleNew = QRectF();
	}else{
	
		QList< cFibGraphicsItem * >::iterator itrActualItem = liSubitems.begin();
		//create the init bounding box
		for ( ; itrActualItem != liSubitems.end(); itrActualItem++ ){
			if ( *itrActualItem ){
				boudingRectangleNew = (*itrActualItem)->boundingRect();
				break;//just the first item determines the init bounding box
			}
		}
		for ( ; itrActualItem != liSubitems.end(); itrActualItem++ ){
			if ( *itrActualItem ){
				boudingRectangleNew.united( (*itrActualItem)->boundingRect() );
			}
		}
	}
	if ( boundingRectangle != boudingRectangleNew ){
		//bounding rectangle changed
		prepareGeometryChange();
		boundingRectangle = boudingRectangleNew;
	}
}


/**
 * This method will enlarge the bounding rectangle of this list
 * graphic item, so it contains the given bounding rectangle.
 *
 * @see boundingRectangle
 * @param rectangle the rectangle to include the the bounding rectangle
 * 	 of this list graphic item
 */
void cFibGraphicsItemFibList::enlargeBoundingRect( const QRectF & rectangle ){
	
	if ( liSubitems.empty() ){
		//no bounding rectangle exists befor -> create one
		if ( boundingRectangle != rectangle ){
			//bounding rectangle changed
			prepareGeometryChange();
			boundingRectangle = rectangle;
		}
		return;
	}//else if needed enlarge existing bounding rectangle
	if ( ! boundingRectangle.contains( rectangle ) ){
		/*rectangle not in existing bounding rectangle
		 *-> enlarge existing bounding rectangle*/
		prepareGeometryChange();
		boundingRectangle.united( rectangle );
	}
}


/**
 * This method will update this graphical item for a change in a
 * Fib element.
 * It will update the bounding rectangle and other members of this class
 * for the changed Fib object if possible.
 * For that it will use the pFibObject (e. g. reevaluate the bounding
 * rectangle with it).
 *
 * @see pFibObject
 * @see boundingRect()
 * @param pFibNodeChangedEvent a pointer to the change event with the
 * 	information of the change or the null pointer NULL
 * @param liOutNotUpdatedItems if not the null pointer NULL: a list to
 * 	store pointers to the cFibGraphicsItem which could not be updated
 * 	(if the return falue is false, you can use this list to adapt
 * 	this graphical item)
 * @return true if this element could be updated, else false
 * 	If false is returned, you should create a new graphical item
 * 	for the changed parts and replace this graphical item with it.
 */
bool cFibGraphicsItemFibList::updateForFibElementChange(
		const eFibNodeChangedEvent * pFibNodeChangedEvent,
		QList< cFibGraphicsItem * > * liOutNotUpdatedItems ){
	
	//TODO check if the order of subitems changed
	
	//notify all subitems
	if ( liOutNotUpdatedItems ){
		bool bAllFibObjectsUpdated = true;
		for ( QList< cFibGraphicsItem * >::iterator
				itrActualItem = liSubitems.begin();
				itrActualItem != liSubitems.end(); itrActualItem++ ){
			
			if ( *itrActualItem ){
				if ( ! ( (*itrActualItem)->updateForFibElementChange(
						pFibNodeChangedEvent, liOutNotUpdatedItems ) ) ){
					//item could not be updated -> remember it
					liOutNotUpdatedItems->push_back( *itrActualItem );
					bAllFibObjectsUpdated = false;
				}
			}
		}
		if ( ! bAllFibObjectsUpdated ){
			//this item could not be updated
			liOutNotUpdatedItems->push_back( this );
		}
	}else{//no liOutNotUpdatedItems exists
		for ( QList< cFibGraphicsItem * >::iterator
				itrActualItem = liSubitems.begin();
				itrActualItem != liSubitems.end(); itrActualItem++ ){
			
			if ( *itrActualItem ){
				(*itrActualItem)->updateForFibElementChange(
						pFibNodeChangedEvent, liOutNotUpdatedItems );
			}
		}
	}
	
	//adapt bounding rectangle
	evaluateBoundingRect();
	
	return false;
}


/**
 * This method paints the content of this graphic item  in local
 * coordinates.
 * @see QGraphicsItem::paint()
 *
 * @param pPainter a pointer to the painter device where to paint on
 * @param pOption a pointer to the options for painting this graphic item
 * @param pWidget a pointer to the widget on which it is painted
 */
void cFibGraphicsItemFibList::paint( QPainter * pPainter,
		const QStyleOptionGraphicsItem * pOption, QWidget * pWidget ){
	
	//paint all subitems
	for ( QList< cFibGraphicsItem * >::iterator
			itrActualItem = liSubitems.begin();
			itrActualItem != liSubitems.end(); itrActualItem++ ){
		
		if ( *itrActualItem ){
			(*itrActualItem)->paint( pPainter, pOption, pWidget );
		}
	}
}


/*
* list element methods
*/

/**
 * @see liSubitems
 * @return the number of subitems of this graphical list item
 */
unsigned int cFibGraphicsItemFibList::getNumberOfSubitems() const{
	
	return liSubitems.size();
}


/**
 * This method return the iNumberOfSubitem'th subitem of this
 * graphical list item.
 *
 * @see liSubitems
 * @see getNumberOfSubitems()
 * @see getSubitems()
 * @param iNumberOfSubitem the number of the subitem to return
 * 	(couning starts with 1)
 * @return iNumberOfSubitem'th subitem of this graphical list item or
 * 	NULL, if non such exists
 */
cFibGraphicsItem * cFibGraphicsItemFibList::getSubitem(
		const unsigned int uiNumberOfSubitem ){
	
	return liSubitems.value( uiNumberOfSubitem - 1, NULL );
}


/**
 * This method return the iNumberOfSubitem'th subitem of this
 * graphical list item.
 *
 * @see liSubitems
 * @see getNumberOfSubitems()
 * @see getSubitems()
 * @param iNumberOfSubitem the number of the subitem to return
 * 	(couning starts with 1)
 * @return iNumberOfSubitem'th subitem of this graphical list item or
 * 	NULL, if non such exists
 */
const cFibGraphicsItem * cFibGraphicsItemFibList::getSubitem(
		const unsigned int uiNumberOfSubitem ) const{
	
	return liSubitems.value( uiNumberOfSubitem - 1, NULL );
}


/**
 * This method returns a number of subitems from this graphical list item,
 * beginning from a first subitem.
 *
 * @see liSubitems
 * @see getSubitem()
 * @see getNumberOfSubitems()
 * @param iNumberOfFirstSubitem the number of the first subitem
 * 	to return (couning starts with 1)
 * @param iNumberOfToReturnSubitems the number /count of subitems
 * 	to return; if 0 or greater equal the count of subitems from
 * 	first subitem, all subitems to the list end will be returned
 * @return a list with the subitems to return
 */
QList< cFibGraphicsItem * > cFibGraphicsItemFibList::getSubitems(
		const unsigned int uiNumberOfFirstSubitem,
		const unsigned int uiNumberOfToReturnSubitems ){
	
	if ( ( uiNumberOfFirstSubitem == 0 ) ||
			( ((unsigned int)liSubitems.size()) < uiNumberOfFirstSubitem ) ){
		//no first item -> return empty list
		return QList< cFibGraphicsItem * >();
	}
	
	return liSubitems.mid( uiNumberOfFirstSubitem - 1,
		( uiNumberOfToReturnSubitems != 0 ) ? uiNumberOfToReturnSubitems : -1 );
}


/**
 * This method adds the subitem pSubitem on the given position
 * iPosition to this graphical list item.
 *
 * @see liSubitems
 * @see addSubitems()
 * @see getNumberOfSubitems()
 * @see getSubitem()
 * @see getSubitems()
 * @param pSubitem a pointer to the subitem to add to the graphical list item
 * @param iPosition the position on which to add the subitem, if
 * 	this number is greater than the number of subitems in the
 * 	graphical list item or 0, the subitem will be added to the end of the
 * 	graphical list item list (couning starts with 1)
 * @return true if the subitem was added, else false
 */
bool cFibGraphicsItemFibList::addSubitem( cFibGraphicsItem * pSubitem,
		const unsigned int uiPosition ){
	
	if ( pSubitem == NULL ){
		//no subitem to insert
		return false;
	}
	//adapt bounding rectangle
	enlargeBoundingRect( pSubitem->boundingRect() );
	pSubitem->setParentItem( this );
	
	liSubitems.insert( ( ( uiPosition == 0 ) ||
			( ((unsigned int)liSubitems.size()) < uiPosition ) ) ?
		( liSubitems.size() ): (uiPosition - 1) , pSubitem );
	
	return true;
}


/**
 * This method adds the subitems liSubitems on the given position
 * iPosition to this graphical list item.
 *
 * @see liSubitems
 * @see addSubitem()
 * @see getNumberOfSubitems()
 * @see getSubitems()
 * @param liSubitem the list with the pointers to the subitems
 * 	to add to the graphical list item
 * @param iPosition the position on which to add the subitems, if
 * 	this number is greater than the number of subitems in the
 * 	graphical list item, the subitems will be added to the end of the
 * 	graphical list item list (couning starts with 1)
 * @return the number of subitems added
 */
unsigned int cFibGraphicsItemFibList::addSubitems(
		QList<cFibGraphicsItem*> liSubitemsToAdd,
		const unsigned int uiPosition ){
	
	if ( liSubitems.empty() ){
		//given subitems to add are new subitems liSubitems
		for ( QList<cFibGraphicsItem*>::iterator
				itrItemToInsert = liSubitemsToAdd.begin();
				itrItemToInsert != liSubitemsToAdd.end(); itrItemToInsert++ ){
			
			if ( (*itrItemToInsert) == NULL ){
				//no item to insert
				continue;
			}
			//insert actual item
			liSubitems.push_back( *itrItemToInsert );
			(*itrItemToInsert)->setParentItem( this );
		}
		//evaluate the bounding rectangle
		evaluateBoundingRect();
		return liSubitems.size();
	}//else subitems allredy exists
	
	
	//go to the position wher to insert
	QList< cFibGraphicsItem * >::iterator itrInsertPosition =
		liSubitems.end();
	if ( ( 0 < uiPosition ) && ( uiPosition < ((unsigned int)liSubitems.size()) ) ){
		itrInsertPosition = liSubitems.begin();
		for ( unsigned int uiActualPosition = 1;
				uiActualPosition < uiPosition; uiActualPosition++ ){
			itrInsertPosition++;
		}
	}
	
	for ( QList<cFibGraphicsItem*>::iterator
			itrItemToInsert = liSubitemsToAdd.begin();
			itrItemToInsert != liSubitemsToAdd.end(); itrItemToInsert++ ){
		
		if ( (*itrItemToInsert) == NULL ){
			//no item to insert
			continue;
		}
		//adapt bounding rectangle
		enlargeBoundingRect( (*itrItemToInsert)->boundingRect() );
		(*itrItemToInsert)->setParentItem( this );
		//insert actual item
		itrInsertPosition = liSubitems.insert( itrInsertPosition , *itrItemToInsert );
		itrInsertPosition++;
	}
	
	return liSubitemsToAdd.size();
}


/**
 * This method deletes the subitem pSubitem on the given
 * position iPositionSubitem from this graphical list item.
 *
 * @see liSubitems
 * @see getNumberOfSubitems()
 * @see getSubitems()
 * @see deleteSubitems()
 * @see addSubitem()
 * @param iPositionSubitem the position from which to delete the
 * 	subitem (couning starts with 1)
 * @param bDeleteOld if true, delete the old subitem from the memory
 * 	(use false if you want to reuse the item)
 * @return true if the subitem was deleted, else false
 */
bool cFibGraphicsItemFibList::deleteSubitem( const unsigned int uiPositionSubitem,
		const bool bDeleteOld ){
	
	if ( ( 0 < uiPositionSubitem ) &&
			( uiPositionSubitem <= ((unsigned int)liSubitems.size()) ) ){
		const unsigned int index = uiPositionSubitem - 1;
		if ( bDeleteOld ){
			delete liSubitems.at( index );
		}
		liSubitems.removeAt( index );
		//adapt bounding rectangle
		evaluateBoundingRect();
		return true;
	}
	
	return false;
}


/**
 * This method deletes a number of subitems from this graphical list item,
 * beginning from a first subitem.
 *
 * @see liSubitems
 * @see deleteSubitem()
 * @see getSubitem()
 * @see getNumberOfSubitems()
 * @see getSubitems()
 * @see addSubitems()
 * @param iNumberOfFirstSubitem the number of the first subitem
 * 	to delete (couning starts with 1)
 * @param iNumberOfToDeleteSubitems the number / count of subitems
 * 	to delete; if 0 or greater equal the count of subitems from
 * 	first subitem, all subitems to the listend will be deleted
 * @param bDeleteOld if true, delete the old subitems from the memory
 * 	(use false if you want to reuse the item)
 * @return true if the subitems where deleted, else false
 */
bool cFibGraphicsItemFibList::deleteSubitems(
		const unsigned int uiNumberOfFirstSubitem,
		const unsigned int uiNumberOfToDeleteSubitems,
		const bool bDeleteOld ){
	
	if ( uiNumberOfToDeleteSubitems == 0 ){
		//no subitem to delete
		return true;
	}
	
	//find first and last position to delete
	QList< cFibGraphicsItem * >::iterator itrFirstToDelete =
		liSubitems.begin();
	for ( unsigned int uiActualItem = 1;
			( uiActualItem < uiNumberOfFirstSubitem ) &&
			( itrFirstToDelete != liSubitems.end() );
			uiActualItem++, itrFirstToDelete++ ){
		//nothing to do
	}
	if ( itrFirstToDelete == liSubitems.end() ){
		//no subitem to delete
		return true;
	}
	
	QList< cFibGraphicsItem * >::iterator itrFirstToNotDelete = itrFirstToDelete;
	for ( unsigned int uiActualItem = 0;
			( uiActualItem < uiNumberOfToDeleteSubitems ) &&
			( itrFirstToNotDelete != liSubitems.end() );
			uiActualItem++, itrFirstToNotDelete++ ){
		//nothing to do
	}
	if ( bDeleteOld ){
		//delete items betwean itrFirstToDelete and itrFirstToNotDelete from memory
		for ( QList<cFibGraphicsItem*>::iterator
				itrItemToDelete = itrFirstToDelete;
				itrItemToDelete != itrFirstToNotDelete; itrItemToDelete++ ){
			
			delete (*itrItemToDelete);
		}
	}
	
	liSubitems.erase( itrFirstToDelete, itrFirstToNotDelete );
	//adapt bounding rectangle
	evaluateBoundingRect();
	return true;
}


/**
 * This method replaces all subitems of this graphical list item with
 * the given subitems liSubitems.
 *
 * @see liSubitems
 * @see getSubitems()
 * @see deleteSubitem()
 * @see deleteSubitems()
 * @see addSubitems()
 * @param liInSubitems the list with the pointers to the subitems,
 * 	with which to replace the existing subitems of the graphical list item
 * @param bDeleteOld if true, delete the old subitems from the memory
 * 	(use false if you want to reuse the item)
 * @return true if the replacing was successfull, else false
 */
bool cFibGraphicsItemFibList::replaceAllSubitems(
		QList<cFibGraphicsItem*> liInSubitems,
		const bool bDeleteOld ){
	
	if ( bDeleteOld ){
		//delete all old items from memory
		for ( QList<cFibGraphicsItem*>::iterator
				itrItemToDelete = liSubitems.begin();
				itrItemToDelete != liSubitems.end(); itrItemToDelete++ ){
			
			delete (*itrItemToDelete);
		}
	}
	
	liSubitems.clear();
	addSubitems( liInSubitems );
	return true;
}



/**
 * This slot will notify the Fib node, which contains this graphic item
 * Fib object, that it was changed.
 * This method should be called if the Fib object of this widget
 * changes.
 * @see fibNodeChangedEvent()
 */
void cFibGraphicsItemFibList::notifyNodeForChange(){
	
	//TODO no change possible at the time -> this function shouldn't be used
	if ( pFibGraphicsScene ){
		//notyfy via the graphics scene
		pFibGraphicsScene->notifyNodeForChange();
	}
}

















