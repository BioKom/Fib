
//TODO check

/**
 * @file cFibGraphicsItem
 * file name: cFibGraphicsItem.h
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


#ifndef ___FIB__NCREATOR__C_FIB_GRAPHICS_ITEM_H__
#define ___FIB__NCREATOR__C_FIB_GRAPHICS_ITEM_H__


#include "version.h"

#include "cFibElement.h"

#include "lFibNodeChanged.h"

#include <string>

#include <QList>
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QMutex>
#include <QGraphicsSceneHoverEvent>


namespace fib{

namespace nCreator{

//cyclic dependencies
class cFibGraphicsScene;

class cFibGraphicsItem: public QGraphicsItem{

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
	 * @param pParent a pointer to parent of this widget
	 */
	cFibGraphicsItem( cFibElement * pInFibObject,
		const unsigned long ulInFibNodeVersionDisplayed = 0,
		QGraphicsItem * pParent = NULL );
	
	/**
	 * parameter constructor for a graphics item for a Fib object
	 *
	 * @param pInFibObject a pointer to the Fib object object for the
	 * 	widget / item to construct
	 * 	@see pFibObject
	 * @param ulFibNodeVersionDisplayed the Fib node version of the
	 * 	Fib object, wich is displayed
	 * 	@see ulInFibNodeVersionDisplayed
	 * @param pInFibGraphicsScene a pointer to the graphic scene for this
	 * 	widget / item
	 * 	@see pFibGraphicsScene
	 * @param pParent a pointer to parent of this widget
	 */
	cFibGraphicsItem( cFibElement * pInFibObject,
		const unsigned long ulInFibNodeVersionDisplayed,
		cFibGraphicsScene * pInFibGraphicsScene,
		QGraphicsItem * pParent = NULL );
	
	/**
	 * destructor
	 */
	virtual ~cFibGraphicsItem();
	
	
	/**
	 * @return a pointer to the Fib object this widget / item represents
	 * 	@see pFibObject
	 */
	cFibElement * getFibObject();
	
	/**
	 * @return a pointer to the Fib object this widget / item represents
	 * 	@see pFibObject
	 */
	const cFibElement * getFibObject() const;
	
	
	/**
	 * @return the name of this class "cFibGraphicsItem"
	 */
	virtual std::string getName() const;
	
	
	/**
	 * @return the outer bounds of this graphic item
	 * 	@see QGraphicsItem::boundingRect()
	 */
	virtual QRectF boundingRect() const = 0;
	
	//TODO in children
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
		QList< cFibGraphicsItem * > * liOutNotUpdatedItems = NULL ) = 0;
	
	
	/**
	 * This method paints the content of this graphic item  in local
	 * coordinates.
	 * @see QGraphicsItem::paint()
	 *
	 * @param pPainter a pointer to the painter device where to paint on
	 * @param pOption a pointer to the options for painting this graphic item
	 * @param pWidget a pointer to the widget on which it is painted
	 */
	virtual void paint( QPainter * pPainter,
		const QStyleOptionGraphicsItem * pOption, QWidget * pWidget = NULL ) = 0;
	/*TODO eg
    painter->drawRect(-10, -10, 20, 20, 5, 5);*/
	
protected:
	
	/**
	 * This method creats the main options widget (pWidgetMainOptions).
	 *
	 * @see pWidgetMainOptions
	 * @return true if the main options widget was created
	 * 	(pWidgetMainOptions != 0), else false
	 */
	virtual bool createMainOptions();
	
	/**
	 * Event handler
	 * When the mouse enters this graphical item, this event method is called.
	 *
	 * @see QGraphicsItem::hoverEnterEvent()
	 * @param pEventGraphicsSceneHover a pointer to the hover event
	 */
	virtual void hoverEnterEvent( QGraphicsSceneHoverEvent * pEventGraphicsSceneHover );
	
	/**
	 * Event handler
	 * When the mouse leaves this graphical item, this event method is called.
	 *
	 * @see QGraphicsItem::hoverLeaveEvent()
	 * @param pEventGraphicsSceneHover a pointer to the hover event
	 */
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * pEventGraphicsSceneHover );
	
//members:
	
	/**
	 * A pointer to the Fib object for this widget / item.
	 * (It should be a pointer to the Fib object, which defines the
	 * Fib part object of this widget.)
	 */
	cFibElement * pFibObject;
	
	/**
	 * The version of the Fib object, wich is displayed.
	 * Every time the Fib object is changed the version number is counted up.
	 * If this number is not equal to the Fib node version number the shown
	 * Fib object needs to be updated.
	 * @see cFibNode::ulVersion
	 * @see cFibNode::fibObjectChanged()
	 */
	unsigned long ulFibNodeVersionDisplayed;
	
	/**
	 * A pointer to the Fib graphic scene for this widget / item, or NULL if
	 * non exists.
	 * @see cFibGraphicsScene
	 */
	cFibGraphicsScene * pFibGraphicsScene;
	
	/**
	 * This widget contains the main options for tis Fib object item.
	 * @see createMainOptions()
	 */
	QWidget * pWidgetMainOptions;
	
	/**
	 * The mutex for the this widget main options.
	 * @see pWidgetMainOptions
	 */
	mutable QMutex mutexMainOptions;
	

private slots:
	
	/**
	 * This slot will notify the Fib node, which contains this graphic item
	 * Fib object, that it was changed.
	 * This method should be called if the Fib object of this widget
	 * changes.
	 * @see fibNodeChangedEvent()
	 */
	void notifyNodeForChange();
	
	
};//end class cFibGraphicsItem

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_GRAPHICS_ITEM_H__





