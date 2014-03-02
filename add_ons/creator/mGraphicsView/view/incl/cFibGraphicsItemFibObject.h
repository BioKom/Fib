
//TODO check

/**
 * @file cFibGraphicsItemFibObject
 * file name: cFibGraphicsItemFibObject.h
 * @author Betti Oesterholz
 * @date 20.07.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a graphics item for a Fib object.
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
 * This file specifies a class for a graphics item for a Fib object.
 * It will display a (part) Fib object as a graphic item.
 * The item correspondents to a Fib object or a part of a Fib object. For
 * this Fib object the graphic / image representation will be shown by its
 * cFibGraphicsItemFibObject.
 *
 * @see cFibElement::evalueObject()
 * @see cFibGraphicsItem
 * @see QGraphicsScene
 * @see cFibGraphicsScene
 * @see QGraphicsItem
 */
/*
History:
20.07.2013  Oesterholz  created
25.01.2013  Oesterholz  the graphical items will be updated, if possible,
	with the information of the Fib node change event
*/


#ifndef ___FIB__NCREATOR__C_FIB_GRAPHICS_ITEM_FIB_OBJECT_H__
#define ___FIB__NCREATOR__C_FIB_GRAPHICS_ITEM_FIB_OBJECT_H__


#include "version.h"

#include <string>

#include <QObject>
#include <QRectF>
#include <QMap>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QMutex>

#include "cFibGraphicsItem.h"
#include "lScalarValueChanged.h"
#include "lFibNodeChanged.h"


namespace fib{

//forward declarations
class cFibElement;

namespace nCreator{

//forward declarations
class cFibGraphicsScene;
class cFibInputVariable;
class cFibInputVariables;
class cWidgetFibInputVariables;
class eFibNodeChangedEvent;
class cFibNode;

class cFibGraphicsItemFibObject: public QObject, public cFibGraphicsItem,
		public lScalarValueChanged{
		Q_OBJECT
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
	cFibGraphicsItemFibObject( cFibElement * pInFibObject,
		const unsigned long ulInFibNodeVersionDisplayed = 0,
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
	 * @param pParent a pointer to parent of this widget
	 */
	cFibGraphicsItemFibObject( cFibElement * pInFibObject,
		const unsigned long ulInFibNodeVersionDisplayed,
		cFibGraphicsScene * pInFibGraphicsScene,
		QGraphicsItem * pParent = NULL );
	
	/**
	 * destructor
	 */
	virtual ~cFibGraphicsItemFibObject();
	
	/**
	 * @return the name of this class "cFibGraphicsItemFibObject"
	 */
	virtual std::string getName() const;
	
	/**
	 * This method returns a number for the type of the graphical item.
	 * Note: The type number of Fib graphical items is betwaen (including)
	 * 	 QGraphicsItem::UserType + 1024 and
	 * 	 QGraphicsItem::UserType + 2047
	 *
	 * @see typeFibGraphicsItems
	 * @see QGraphicsItem::type()
	 * @return a number for the type of the graphical item
	 */
	virtual int type() const;
	
	/**
	 * @return the outer bounds of this graphic item
	 * 	@see QGraphicsItem::boundingRect()
	 */
	virtual QRectF boundingRect() const;
	
	/**
	 * This method returns if the given point (local coordinates) is in
	 * this item.
	 *
	 * @see QGraphicsItem::contains(const QPointF & point)
	 * @param point the point for which to check if it is in this item
	 * @return true if the point is in this item, else false
	 */
	virtual bool contains( const QPointF & point ) const;
	
#ifdef TODO_WEG
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
#endif //TODO_WEG
	
	/**
	 * This method will update this graphical item for a change in a
	 * Fib Node / Fib element.
	 * It will update the bounding rectangle and other members of this class
	 * for the changed Fib object if possible.
	 * For that it will use the pFibNodeChangedEvent (e. g. reevaluate the
	 * bounding rectangle with it).
	 *
	 * @see pFibObject
	 * @see boundingRect()
	 * @param pFibNodeChangedEvent a pointer to the change event with the
	 * 	information of the change
	 * @param pFibGraphicsItemFactory a pointer to the Fib graphical item
	 * 	factory, to create sub graphical items, which can not be updated
	 * @param pUpdateForFibObject the Fib object for which this graphical
	 * 	item should be updated (which it should represent)
	 * @return true if this element could be updated, else false
	 * 	If false is returned, you should create a new graphical item
	 * 	for the changed parts and replace this graphical item with it.
	 */
	virtual bool updateForFibNodeChange(
		const eFibNodeChangedEvent * pFibNodeChangedEvent,
		const iFibGraphicsItemFactory * pFibGraphicsItemFactory,
		const cFibElement * pUpdateForFibObject );
	
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
		const QStyleOptionGraphicsItem * pOption, QWidget * pWidget = NULL );
	
	/**
	 * Event method
	 * It will be called every time a input variable value (cFibInputVariable),
	 * at which this object is registered, was changed.
	 *
	 * @see cFibInputVariable::dValue
	 * @param pFibScalar a pointer to the changed Fib input variable
	 */
	virtual void fibScalarValueChangedEvent(
		const cFibScalar * pFibScalar );
	
signals:
	
	/**
	 * This signal triggers the reevaluation of the bounding box.
	 * @see reevaluateBoundingBox()
	 */
	void signalReevaluateBoundingBox();
	
private slots:
	
	/**
	 * This method reevaluates the bounding box of this graphical item.
	 *
	 * @see boundingRect()
	 * @see boundingRectangle
	 * @see signalReevaluateBoundingBox()
	 */
	void reevaluateBoundingBox();
	
	/**
	 * This slot will notify the Fib node, which contains this graphic item
	 * Fib object, that it was changed.
	 * This method should be called if the Fib object of this widget
	 * changes.
	 * @see fibNodeChangedEvent()
	 */
	void notifyNodeForChange();
	
protected:
	
	/**
	 * This method evalues the input variables for this object.
	 */
	void evalueInputVariables();
	

//members:
	
	
	/**
	 * A pointer to the input variables of the Fib object for this item, or
	 * NULL if non exists.
	 * Input variables of a Fib object are variables, which are used in the
	 * Fib object, but not defined in it. So these variables need to be
	 * set to a value in order to evalue the Fib object.
	 *
	 * @see pFibObject
	 */
	cWidgetFibInputVariables * pWidgetFibInputVariables;
	
	/**
	 * The bounding rectangle for the Fib object.
	 */
	QRectF boundingRectangle;
	
	
	/**
	 * A buffer for the Fib object.
	 * If not NULL it contains the pixmap for the Fib object.
	 * @see mutexGraphicsPixmapItemForFibObject
	 */
	QGraphicsPixmapItem * pGraphicsPixmapItemForFibObject;
	
	/**
	 * The mutex for acessing pGraphicsPixmapItemForFibObject.
	 * @see pGraphicsPixmapItemForFibObject
	 */
	mutable QMutex mutexGraphicsPixmapItemForFibObject;
	
};//end class cFibGraphicsItemFibObject

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_GRAPHICS_ITEM_FIB_OBJECT_H__





