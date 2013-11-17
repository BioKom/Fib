
//TODO check

/**
 * @file cFibGraphicsItemFibList
 * file name: cFibGraphicsItemFibList.h
 * @author Betti Oesterholz
 * @date 28.07.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a graphics item for a Fib list object.
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
 * This file specifies a class for a graphics item for a Fib list object.
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
28.07.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_FIB_GRAPHICS_ITEM_FIB_LIST_H__
#define ___FIB__NCREATOR__C_FIB_GRAPHICS_ITEM_FIB_LIST_H__


#include "version.h"

#include "cFibElement.h"

#include "cFibGraphicsItem.h"

#include <string>

#include <QList>
#include <QRectF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>


namespace fib{

namespace nCreator{

//cyclic dependencies
class cFibGraphicsScene;

class cFibGraphicsItemFibList: public cFibGraphicsItem{
	
	/**
	 * A list with the graphical subitems of this graphical list item.
	 */
	QList< cFibGraphicsItem * > liSubitems;
	
	/**
	 * The bounding rectangle for the Fib object.
	 */
	QRectF boundingRectangle;
	
public:

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
	cFibGraphicsItemFibList( cFibElement * pInFibObject,
		const unsigned long ulInFibNodeVersionDisplayed = 0,
		QList< cFibGraphicsItem * > liInSubitems = QList< cFibGraphicsItem * >(),
		QGraphicsItem * pParent = NULL );
	
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
	cFibGraphicsItemFibList( cFibElement * pInFibObject,
		const unsigned long ulInFibNodeVersionDisplayed,
		cFibGraphicsScene * pInFibGraphicsScene,
		QList< cFibGraphicsItem * > liInSubitems = QList< cFibGraphicsItem * >(),
		QGraphicsItem * pParent = NULL );
	
	/**
	 * destructor
	 */
	virtual ~cFibGraphicsItemFibList();
	
	
	/**
	 * @return the name of this class "cFibGraphicsItemFibList"
	 */
	virtual std::string getName() const;
	
	
	/**
	 * @return the outer bounds of this graphic item
	 * 	@see QGraphicsItem::boundingRect()
	 */
	virtual QRectF boundingRect() const;
	
	/**
	 * This method will evaluate the bounding rectangle for this list
	 * graphic item. For that it will evaluate the smaalest bounding
	 * rectangle, which contains all subitem bounding rectangles.
	 * @see boundingRectangle
	 * @see liSubitems
	 * @see liSubitems::boundingRect()
	 */
	void evaluateBoundingRect();
	
	/**
	 * This method will enlarge the bounding rectangle of this list
	 * graphic item, so it contains the given bounding rectangle.
	 *
	 * @see boundingRectangle
	 * @param rectangle the rectangle to include the the bounding rectangle
	 * 	 of this list graphic item
	 */
	void enlargeBoundingRect( const QRectF & rectangle );
	
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
	virtual bool updateForFibElementChange(
		const eFibNodeChangedEvent * pFibNodeChangedEvent = NULL,
		QList< cFibGraphicsItem * > * liOutNotUpdatedItems = NULL );
	
	
	/**
	 * This method paints the content of this graphic item in local
	 * coordinates.
	 * @see QGraphicsItem::paint()
	 *
	 * @param pPainter a pointer to the painter device where to paint on
	 * @param pOption a pointer to the options for painting this graphic item
	 * @param pWidget a pointer to the widget on which it is painted
	 */
	virtual void paint( QPainter * pPainter,
		const QStyleOptionGraphicsItem * pOption, QWidget * pWidget = NULL );
	
/*
 * list element methods
 */

	/**
	 * @see liSubitems
	 * @return the number of subitems of this graphical list item
	 */
	virtual unsigned int getNumberOfSubitems() const;

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
	virtual cFibGraphicsItem * getSubitem( const unsigned int uiNumberOfSubitem = 1 );

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
	virtual const cFibGraphicsItem * getSubitem(
		const unsigned int uiNumberOfSubitem = 1 ) const;

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
	virtual QList< cFibGraphicsItem * > getSubitems(
		const unsigned int uiNumberOfFirstSubitem = 1,
		const unsigned int uiNumberOfToReturnSubitems = 0 );

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
	 * 	graphical list item or 0, the subitem will be added to the end of
	 * 	the graphical list item list (couning starts with 1)
	 * @return true if the subitem was added, else false
	 */
	virtual bool addSubitem( cFibGraphicsItem * pSubitem,
		const unsigned int uiPosition = 1 );

	/**
	 * This method adds the subitems liSubitems on the given position
	 * iPosition to this graphical list item.
	 *
	 * @see liSubitems
	 * @see addSubitem()
	 * @see getNumberOfSubitems()
	 * @see getSubitems()
	 * @param liSubitemsToAdd the list with the pointers to the subitems
	 * 	to add to the graphical list item
	 * @param iPosition the position on which to add the subitems, if
	 * 	this number is greater than the number of subitems in the
	 * 	graphical list item, the subitems will be added to the end of the
	 * 	graphical list item list (couning starts with 1)
	 * @return the number of subitems added
	 */
	virtual unsigned int addSubitems( QList<cFibGraphicsItem*> liSubitemsToAdd,
		const unsigned int uiPosition = 1 );

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
	virtual bool deleteSubitem( const unsigned int uiPositionSubitem,
		const bool bDeleteOld = true );
	
	
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
	virtual bool deleteSubitems(
		const unsigned int uiNumberOfFirstSubitem = 3,
		const unsigned int uiNumberOfToDeleteSubitems = 0,
		const bool bDeleteOld = true );

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
	virtual bool replaceAllSubitems( QList<cFibGraphicsItem*> liInSubitems,
		const bool bDeleteOld = true );
	
	
	
private slots:
	
	/**
	 * This slot will notify the Fib node, which contains this graphic item
	 * Fib object, that it was changed.
	 * This method should be called if the Fib object of this widget
	 * changes.
	 * @see fibNodeChangedEvent()
	 */
	void notifyNodeForChange();
	
	
};//end class cFibGraphicsItemFibList

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_GRAPHICS_ITEM_FIB_LIST_H__





