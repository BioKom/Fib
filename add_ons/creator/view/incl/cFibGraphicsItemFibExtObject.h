
//TODO check

/**
 * @file cFibGraphicsItemFibExtObject
 * file name: cFibGraphicsItemFibExtObject.h
 * @author Betti Oesterholz
 * @date 20.07.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a graphics item for a Fib external object.
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
 * This file specifies a class for a graphics item for a Fib external object.
 * It will display a (part) Fib object with a external object element as
 * its leaf element as a graphic item.
 * The item correspondents to a Fib object or a part of a Fib object. For
 * this Fib object the graphic / image representation will be shown by its
 * cFibGraphicsItemFibExtObject.
 * This grapical item enables the user to change input values of the
 * lead external object it represents.
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
*/


#ifndef ___FIB__NCREATOR__C_FIB_GRAPHICS_ITEM_FIB_EXT_OBJECT_H__
#define ___FIB__NCREATOR__C_FIB_GRAPHICS_ITEM_FIB_EXT_OBJECT_H__


#include "version.h"

#include "cFibGraphicsItem.h"
#include "lScalarValueChanged.h"
#include "lFibNodeChanged.h"

#include <string>

#include <QRectF>
#include <QMap>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QMutex>


namespace fib{

//forward declarations
class cFibElement;

namespace nCreator{

//forward declarations
class cFibGraphicsScene;
class cFibInputVariable;
class cFibInputVariables;
class cWidgetFibInputVariables;
class cWidgetFibVector;
class eFibNodeChangedEvent;
class cFibNode;

class cFibGraphicsItemFibExtObject: public cFibGraphicsItem,
		public lScalarValueChanged, public lFibNodeChanged{
public:

	/**
	 * A parameter constructor for a graphics item for a Fib object.
	 *
	 * @param pInFibObject a pointer to the Fib object object for the
	 * 	widget / item to construct;
	 * 	It should have a Fib external object as its leaf element.
	 * 	@see pFibObject
	 * @param ulInFibNodeVersionDisplayed the Fib node version of the
	 * 	Fib object, wich is displayed
	 * 	@see ulFibNodeVersionDisplayed
	 * @param pInFibObjectCopy a pointer to a copy of a Fib object to copy;
	 * 	This Fib object will be shown by this object with evalueObject()
	 * 	if present, else pFibObject will be used.
	 * 	This object is responsible for deleting the Fib object copy.
	 * 	@see pFibObjectCopy
	 * @param pParent a pointer to parent of this widget
	 */
	cFibGraphicsItemFibExtObject( cFibElement * pInFibObject,
		const unsigned long ulInFibNodeVersionDisplayed = 0,
		cFibElement * pInFibObjectCopy = NULL,
		QGraphicsItem * pParent = NULL );
	
	/**
	 * A parameter constructor for a graphics item for a Fib object.
	 *
	 * @param pInFibObject a pointer to the Fib object object for the
	 * 	widget / item to construct, it should have a Fib external object
	 * 	as its leaf element
	 * 	@see pFibObject
	 * @param ulInFibNodeVersionDisplayed the Fib node version of the
	 * 	Fib object, wich is displayed
	 * 	@see ulFibNodeVersionDisplayed
	 * @param pInFibGraphicsScene a pointer to the graphic scene for this
	 * 	widget / item
	 * 	@see pFibGraphicsScene
	 * @param pInFibObjectCopy a pointer to a copy of a Fib object to copy;
	 * 	This Fib object will be shown by this object with evalueObject()
	 * 	if present, else pFibObject will be used.
	 * 	It should have a Fib external object as its leaf element.
	 * 	This object is responsible for deleting the Fib object copy.
	 * 	@see pFibObjectCopy
	 * @param pParent a pointer to parent of this widget
	 */
	cFibGraphicsItemFibExtObject( cFibElement * pInFibObject,
		const unsigned long ulInFibNodeVersionDisplayed,
		cFibGraphicsScene * pInFibGraphicsScene,
		cFibElement * pInFibObjectCopy = NULL,
		QGraphicsItem * pParent = NULL );
	
	/**
	 * destructor
	 */
	virtual ~cFibGraphicsItemFibExtObject();
	
	
	/**
	 * @return a pointer to the Fib object this widget / item represents
	 * 	@see pFibObject
	 */
	const cFibElement * getFibObjectCopy() const;
	
	
	/**
	 * @return the name of this class "cFibGraphicsItemFibExtObject"
	 */
	virtual std::string getName() const;
	
	
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
	
	/**
	 * Event method
	 * It will be called every time a Fib node (cFibNode), at which
	 * this object is registered, was changed.
	 *
	 * @param pFibNodeChanged a pointer to the event, with the information
	 * 	about the changed Fib node
	 */
	virtual void fibNodeChangedEvent(
		const eFibNodeChangedEvent * pFibNodeChanged );
	
private slots:
	
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
	
	
	/**
	 * This method creats the main options widget (pWidgetMainOptions).
	 *
	 * @see pWidgetMainOptions
	 * @return true if the main options widget was created
	 * 	(pWidgetMainOptions != 0), else false
	 */
	virtual bool createMainOptions();

//members:
	
	/**
	 * A pointer to a copy of a Fib object to copy.
	 * This Fib object will be shown by this object with evalueObject() if
	 * present, else pFibObject will be used.
	 * This object is responsible for deleting the Fib object copy.
	 * You can use this object if you want to display a part object of a
	 * Fib object, by copying the part object and providing it.
	 * Also if you want to make sure that the Fib object for this item
	 * isn't change by other parts, you can provide a copy.
	 *
	 * @see pFibObject
	 * @see cFibElement::evalueObject()
	 */
	cFibElement * pFibObjectCopy;
	
	/**
	 * The node for the Fib object copy.
	 * @see pFibObjectCopy
	 */
	cFibNode * pFibObjectCopyNode;
	
	
	/**
	 * A pointer to the input variables of the Fib object for this item, or
	 * NULL if non exists.
	 * Input variables of a Fib object are variables, which are used in the
	 * Fib object, but not defined in it. So these variables need to be
	 * set to a value in order to evalue the Fib object.
	 *
	 * @see pFibObject
	 * @see pFibInputVariablesCopy
	 */
	cWidgetFibInputVariables * pWidgetFibInputVariables;
	
	/**
	 * A pointer to the input variables of the copy Fib object for this item,
	 * or NULL if non exists.
	 * Input variables of a Fib object are variables, which are used in the
	 * Fib object, but not defined in it. So these variables need to be
	 * set to a value in order to evalue the Fib object.
	 *
	 * @see pFibObjectCopy
	 * @see pWidgetFibInputVariables
	 */
	cFibInputVariables * pFibInputVariablesCopy;
	
	/**
	 * A map for the input variables.
	 * 	key: a input variables from pWidgetFibInputVariables
	 * 	value: a input variables from pFibInputVariablesCopy
	 */
	QMap< cFibInputVariable*, cFibInputVariable* > mapInVars;
	
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
	 * The mutex for accessing pGraphicsPixmapItemForFibObject.
	 * @see pGraphicsPixmapItemForFibObject
	 */
	mutable QMutex mutexGraphicsPixmapItemForFibObject;
	
	
	/**
	 * The widget for the external object input vector.
	 * @see createMainOptions()
	 * @see pWidgetMainOptions
	 */
	cWidgetFibVector * pWidgetFibVector;
	
};//end class cFibGraphicsItemFibExtObject

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_GRAPHICS_ITEM_FIB_EXT_OBJECT_H__





