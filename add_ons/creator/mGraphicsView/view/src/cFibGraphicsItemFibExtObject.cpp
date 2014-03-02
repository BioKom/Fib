
//TODO check

/**
 * @file cFibGraphicsItemFibExtObject
 * file name: cFibGraphicsItemFibExtObject.cpp
 * @author Betti Oesterholz
 * @date 28.07.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a graphics item for a Fib external object.
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
 * This file implements a class for a graphics item for a Fib external object.
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
28.07.2013  Oesterholz  created
25.01.2013  Oesterholz  the graphical items will be updated, if possible,
	with the information of the Fib node change event
*/


//TODO switches for test proposes
#define DEBUG


#include "cFibGraphicsItemFibExtObject.h"

#include <list>

#include <QPixmap>
#include <QSplitter>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsSceneHoverEvent>

#include "cFibElement.h"
#include "cExtObject.h"
#include "cVectorExtObject.h"

#include "cFibGraphicsScene.h"
#include "cFibInputVariable.h"
#include "cFibInputVariables.h"
#include "cWidgetFibInputVariables.h"
#include "cWidgetFibVector.h"
#include "cEvalueSimpleRGBA255QPainter.h"
#include "cEvalueSimpleRGBA255TwoQPainter.h"
#include "eFibNodeChangedEvent.h"
#include "cFibNode.h"
#include "cFibNodeHandler.h"
#include "eFibNodeChangedEvent.h"
#include "cFibVectorCreator.h"
#include "cFibVectorHandler.h"


using namespace std;
using namespace fib::nCreator;
using namespace fib;


/*TODO implements
 * A graphical items should react to mouse events:
    - 1 second mouse over -> as long as the mouse is over: display main options for item (input values of external object + input variables of part object)
    - left click mouse -> display main options for item (input values of wxternal object + input variables of part object)
    - two left clicks mouse on same item -> display entire part object for item
 */

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
 * @param pParent a pointer to parent of this widget
 */
cFibGraphicsItemFibExtObject::cFibGraphicsItemFibExtObject( cFibElement * pInFibObject,
		const unsigned long ulInFibNodeVersionDisplayed,
		QGraphicsItem * pParent ):
		cFibGraphicsItem( pInFibObject, ulInFibNodeVersionDisplayed, pParent ),
		pWidgetFibInputVariables( NULL ),
		pGraphicsPixmapItemForFibObject( NULL ), pWidgetFibVector( NULL ){
		
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this<<")::cFibGraphicsItemFibExtObject( pInFibObject="<<pInFibObject<<", ulInFibNodeVersionDisplayed="<<ulInFibNodeVersionDisplayed<<", pParent="<<pParent<<" ) called"<<endl<<flush);
	
	//accept events that the mouse is over this item
	setAcceptHoverEvents( true );
	
	//evaluate the bounding box (boundingRectangle)
	QObject::connect( this, SIGNAL(signalReevaluateBoundingBox()),
		this, SLOT(reevaluateBoundingBox()) );
	emit signalReevaluateBoundingBox();
	
	//evalue input variables
	evalueInputVariables();
}


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
 * @param pParent a pointer to parent of this widget
 */
cFibGraphicsItemFibExtObject::cFibGraphicsItemFibExtObject( cFibElement * pInFibObject,
		const unsigned long ulInFibNodeVersionDisplayed,
		cFibGraphicsScene * pInFibGraphicsScene,
		QGraphicsItem * pParent ):
		cFibGraphicsItem( pInFibObject, ulInFibNodeVersionDisplayed,
			pInFibGraphicsScene, pParent ),
		pWidgetFibInputVariables( NULL ),
		pGraphicsPixmapItemForFibObject( NULL ), pWidgetFibVector( NULL ){
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this<<")::cFibGraphicsItemFibExtObject( pInFibObject="<<pInFibObject<<", pInFibGraphicsScene="<<pInFibGraphicsScene<<", ulInFibNodeVersionDisplayed="<<ulInFibNodeVersionDisplayed<<", pParent="<<pParent<<" ) called"<<endl<<flush);
	
	//accept events that the mouse is over this item
	setAcceptHoverEvents( true );
	
	//evaluate the bounding box (boundingRectangle)
	QObject::connect( this, SIGNAL(signalReevaluateBoundingBox()),
		this, SLOT(reevaluateBoundingBox()) );
	emit signalReevaluateBoundingBox();
	
	//evalue input variables
	evalueInputVariables();
}


/**
 * destructor
 */
cFibGraphicsItemFibExtObject::~cFibGraphicsItemFibExtObject(){
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this<<")::~cFibGraphicsItemFibExtObject() called"<<endl<<flush);
	if ( pWidgetFibInputVariables ){
		//unregister this object as a value change listener of them
		pWidgetFibInputVariables->unregisterScalarValueChangeListener( this );
		//weg delete input variables
		if ( pWidgetMainOptions == NULL ){
			pWidgetFibInputVariables->deleteLater();
		}//else the input variables will be deleted by pWidgetMainOptions
	}
	mutexGraphicsPixmapItemForFibObject.lock();
	if ( pGraphicsPixmapItemForFibObject ){
		//delete the pixmap for the Fib object
		delete pGraphicsPixmapItemForFibObject;
	}
	mutexGraphicsPixmapItemForFibObject.unlock();
}


/**
 * @return the name of this class "cFibGraphicsItemFibExtObject"
 */
std::string cFibGraphicsItemFibExtObject::getName() const{
	
	return std::string( "cFibGraphicsItemFibExtObject" );
}


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
int cFibGraphicsItemFibExtObject::type() const {
	
	return FibGraphicsItemFibExtObject;
}


/**
 * @return the outer bounds of this graphic item
 * 	@see QGraphicsItem::boundingRect()
 */
QRectF cFibGraphicsItemFibExtObject::boundingRect() const{
	
	return boundingRectangle;
}


/**
 * This method returns if the given point (local coordinates) is in
 * this item.
 *
 * @see QGraphicsItem::contains(const QPointF & point)
 * @param point the point for which to check if it is in this item
 * @return true if the point is in this item, else false
 */
bool cFibGraphicsItemFibExtObject::contains( const QPointF & point ) const{
	if ( ! boundingRectangle.contains( point ) ){
		//not in bounding rectange -> not in item
		return false;
	}//else
	mutexGraphicsPixmapItemForFibObject.lock();
	if ( pGraphicsPixmapItemForFibObject ){
		//pixmap exists -> check if point in it
		if ( ! pGraphicsPixmapItemForFibObject->contains( point ) ){
			mutexGraphicsPixmapItemForFibObject.unlock();
			return false;
		}//else return true
	}
	mutexGraphicsPixmapItemForFibObject.unlock();
	
	return true;
}

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
bool cFibGraphicsItemFibExtObject::updateForFibElementChange(
		const eFibNodeChangedEvent * pFibNodeChangedEvent,
		QList< cFibGraphicsItem * > * liOutNotUpdatedItems ){
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this<<")::updateForFibElementChange( const eFibNodeChangedEvent * pFibNodeChangedEvent, QList< cFibGraphicsItem * > * liOutNotUpdatedItems ) called"<<endl<<flush);
	if ( ( pFibNodeChangedEvent == NULL ) ||
			( pFibNodeChangedEvent->getChangedNode() == NULL ) ){
		//no Fib node -> can not update
		return false;
	}
	
	bool bReturnValue = true;
	
	if ( pFibObjectCopy ){
		//integrate changes into pFibObjectCopy
		
		//find the changed Fib elements
		
		//TODO use pFibNodeChangedEvent to speed up
		
		/*find the defining Fib element pFibObject in the copy Fib element
		(=copy of defining Fib element)*/
		/*go up in copy to first leaf or branch element and choose it as
		 *actual Fib element*/
		cFibElement * pActualFibElement = pFibObjectCopy;
		for (  ; ( pActualFibElement != NULL ) &&
					( pActualFibElement->getType() != 'o' )
					( pActualFibElement->getNumberOfSubobjects() == 1 );
				pActualFibElement = pActualFibElement->getNextFibElement() ){
			//nothing to do
		}
		if ( pActualFibElement == NULL ){
			//could not find copy of defining Fib element -> can not update this item
			if ( liOutNotUpdatedItems ){
				//add this item as Fib graphical item which could not be updated
				liOutNotUpdatedItems->append( this );
			}
			return false;
		}
		/*while actual Fib element is not the defining Fib element pFibObject
		 (they are equal if the number of contained Fib elements are equal)
		 -> take superior Fib element as actual Fib element*/
		const unsignedIntFib uiOrgNboElements = pFibObject->getNumberOfElements();
		unsignedIntFib uiActualNboElements =
			pActualFibElement->getNumberOfElements();
		while ( uiActualNboElements < uiOrgNboElements ){
			//next actual is superior of actual
			pActualFibElement = pActualFibElement->getSuperiorFibElement();
			if ( pActualFibElement == NULL ){
				//could not find copy of defining Fib element -> can not update this item
				if ( liOutNotUpdatedItems ){
					//add this item as Fib graphical item which could not be updated
					liOutNotUpdatedItems->append( this );
				}
				return false;
			}
			uiActualNboElements = pActualFibElement->getNumberOfElements();
		}/*end while actual Fib element has less contained Fib elements than
		the defining Fib element*/
		if ( uiActualNboElements != uiOrgNboElements ){
			/* == if ( uiOrgNboElements < uiActualNboElements )
			-> could not find copy of defining Fib element -> can not update this item*/
			if ( liOutNotUpdatedItems ){
				//add this item as Fib graphical item which could not be updated
				liOutNotUpdatedItems->append( this );
			}
			return false;
		}//else copy of defining Fib element = pActualFibElement
		/*list with the not equal Fib elements
			 first: original Fib element
			 second: Fib element in copy*/
		list< pair< cFibElement *, cFibElement * > > liNotEqualElements;
		/*check with cFibElement::equalElement( , false ) if supperior
		 *Fib elements of defining Fib element and its copy are equal*/
		cFibElement * pOrgFibElementToCheck  = pFibObject;
		cFibElement * pCopyFibElementToCheck = pActualFibElement;
		while ( true ){
			//check next superior Fib elements
			pOrgFibElementToCheck  = pOrgFibElementToCheck->getSuperiorFibElement();
			pCopyFibElementToCheck = pCopyFibElementToCheck->getSuperiorFibElement();
			while ( ( pCopyFibElementToCheck != NULL ) &&
				( pCopyFibElementToCheck->getType() == 'l' ) ){
				//when copy a part object superior list elements will be discarded
				pCopyFibElementToCheck =
					pCopyFibElementToCheck->getSuperiorFibElement();
			}
			if ( pOrgFibElementToCheck == NULL ){
				/*no correspondending Fib element in the original
				-> can't adapt copy Fib object*/
				if ( liOutNotUpdatedItems ){
					//add this item as Fib graphical item which could not be updated
					liOutNotUpdatedItems->append( this );
				}
				return false;
			}
			if ( pCopyFibElementToCheck == NULL ){
				/*no correspondending Fib element in the copy Fib object
				-> done for searching not equal elements*/
				break;
			}
			
			if ( ! pOrgFibElementToCheck->equalElement( *pCopyFibElementToCheck ) ){
				//Fib elements not equal
				if ( pOrgFibElementToCheck->getType() != pCopyFibElementToCheck->getType() ){
					//Fib elements have not the same type -> can't adapt copy Fib object
					if ( liOutNotUpdatedItems ){
						//add this item as Fib graphical item which could not be updated
						liOutNotUpdatedItems->append( this );
					}
					return false;
				}//else try to adapt Fib elements
				liNotEqualElements.push_front( pair< cFibElement *, cFibElement * >(
					pOrgFibElementToCheck, pCopyFibElementToCheck ) );
			}//else Fib elements equal
			
		}//end for check if superior Fib elements are equal
		/*check with cFibElement::equalElement( , false ) if all contained
		 *Fib elements of defining Fib element and its copy are equal*/
		pOrgFibElementToCheck  = pFibObject;
		pCopyFibElementToCheck = pActualFibElement;
		for ( unsignedIntFib uiActualFibElement = 0;
				( uiActualFibElement < uiOrgNboElements ) &&
				( pOrgFibElementToCheck  != NULL ) &&
				( pCopyFibElementToCheck != NULL ) ;
				uiActualFibElement++,
				pOrgFibElementToCheck  = pOrgFibElementToCheck->getNextFibElement(),
				pCopyFibElementToCheck = pCopyFibElementToCheck->getNextFibElement() ){
			
			if ( pOrgFibElementToCheck->equalElement( *pCopyFibElementToCheck ) ){
				//Fib elements not equal
				if ( pOrgFibElementToCheck->getType() != pCopyFibElementToCheck->getType() ){
					//Fib elements have not the same type -> can't adapt copy Fib object
					if ( liOutNotUpdatedItems ){
						//add this item as Fib graphical item which could not be updated
						liOutNotUpdatedItems->append( this );
					}
					return false;
				}//else try to adapt Fib elements
				liNotEqualElements.push_back( pair< cFibElement *, cFibElement * >(
					pOrgFibElementToCheck, pCopyFibElementToCheck ) );
			}//else Fib elements equal
		}
		//make Fib elements equal
		for ( list< pair< cFibElement *, cFibElement * > >::iterator
				itrNotEqualFibElements = liNotEqualElements.begin();
				itrNotEqualFibElements != liNotEqualElements.end();
				itrNotEqualFibElements++ ){
			//assign the values of the original Fib elements to the copy
			bReturnValue &= itrNotEqualFibElements->second->assignValues(
				*(itrNotEqualFibElements->first) );
		}
		
	}//end if pFibObjectCopy exists -> integrate changes into pFibObjectCopy
	mutexGraphicsPixmapItemForFibObject.lock();
	if ( pGraphicsPixmapItemForFibObject ){
		//Fib object needs to be reevaluated -> delete pGraphicsPixmapItemForFibObject
		delete pGraphicsPixmapItemForFibObject;
		pGraphicsPixmapItemForFibObject = NULL;
	}
	mutexGraphicsPixmapItemForFibObject.unlock();
	//reevaluate the bounding box (boundingRectangle)
	emit signalReevaluateBoundingBox();
	return bReturnValue;
}

#endif //TODO_WEG


/**
 * This method will update this graphical item for a change in a
 * Fib Node / Fib element.
 * It will update the bounding rectangle and other members of this class
 * for the changed Fib object if possible.
 * For that it will use the pFibNodeChangedEvent (e. g. reevaluate the
 * bounding rectangle with it).
 * Note: This method won't use a mutex.
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
bool cFibGraphicsItemFibExtObject::updateForFibNodeChange(
		const eFibNodeChangedEvent * pFibNodeChangedEvent,
		const iFibGraphicsItemFactory * /*pFibGraphicsItemFactory*/,
		const cFibElement * pUpdateForFibObject ) {
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this<<")::updateForFibNodeChange( const eFibNodeChangedEvent * pFibNodeChangedEvent, pFibGraphicsItemFactorys, pUpdateForFibObject ) called"<<endl<<flush);
	if ( ( pFibNodeChangedEvent == NULL ) || ( pUpdateForFibObject == NULL ) ||
			( pFibObject == NULL ) ) {
		//nothing to update for -> can't update
		DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this<<")::updateForFibNodeChange() done: nothing to update for -> can't update"<<endl<<flush);
		return false;
	}
	
	/*check if the Fib object for this grapical item is superior or
	 contained in a changed Fib element or Fib object*/
	if ( ! pFibNodeChangedEvent->isChangedBranch( pFibObject ) ) {
		/*the Fib object for this grapical item is not on a branch which
		 *contains a changed Fib element or Fib object
		 -> this graphical item don't need to be updated
		 -> everything up to date
		 -> nothing to do*/
		if ( pFibObject->getType() == 'o' ){
			//get external object
			const cRoot * pExternalObjectRoot =
				pFibObject->getAccessibleRootObject(
					static_cast< cExtObject * >( pFibObject )->getIdentifier() );
			
			if ( ! pFibNodeChangedEvent->isChangedBranch( pExternalObjectRoot ) ) {
				DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this<<")::updateForFibNodeChange() done: everything up to date"<<endl<<flush);
				return true;
			}
		} else {
			DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this<<")::updateForFibNodeChange() done: not an external object element"<<endl<<flush);
			return false;
		}
	}//else this branch or the external object where chenged
	if ( pFibNodeChangedEvent->isElementChanged( pFibObject,
			eFibNodeChangedEvent::DELETED ) ) {
		//the Fib element for this graphical item was deleted -> can't update
		DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this<<")::updateForFibNodeChange() done: the Fib element for this graphical item was deleted -> can't update"<<endl<<flush);
		return false;
	}
	
	/*check if the given Fib object can be converted into or can be
	 *represented by this grapical item (it contains a external object
	 *element and above the external object element just limb elements till
	 *the given Fib element pUpdateForFibObject)*/
	//search for Fib list element above given Fib element pUpdateForFibObject
	for ( const cFibElement * pActualFibElement = pUpdateForFibObject;
			pActualFibElement != NULL;
			pActualFibElement = pActualFibElement->getNextFibElement() ) {
		if ( pActualFibElement->getType() == 'o' ) {
			//Fib external object element above given Fib element pUpdateForFibObject found
			if ( pActualFibElement != pFibObject ) {
				/*the found Fib external object element is not for this
				 *Fib graphical external object element
				 -> this Fib external object graphical item can not be adapted*/
				DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this<<")::updateForFibNodeChange() done: no topmost external object element"<<endl<<flush);
				return false;
			}
			break;
		}
		if ( ( ! pActualFibElement->isLimb() ) &&
				( pActualFibElement->getType() != 'r' ) ) {
			/*the Fib element is not a limb, root or external object element
			-> this Fib external object graphical item can not be adapted*/
			DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this<<")::updateForFibNodeChange() done: the Fib element is not a limb, root or external object element"<<endl<<flush);
			return false;
		}
	}
	
	mutexGraphicsPixmapItemForFibObject.lock();
	if ( pGraphicsPixmapItemForFibObject ){
		//Fib object needs to be reevaluated -> delete pGraphicsPixmapItemForFibObject
		delete pGraphicsPixmapItemForFibObject;
		pGraphicsPixmapItemForFibObject = NULL;
	}
	mutexGraphicsPixmapItemForFibObject.unlock();
	//reevaluate the bounding box (boundingRectangle)
	emit signalReevaluateBoundingBox();
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this<<")::updateForFibNodeChange() done"<<endl<<flush);
	return true;
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
void cFibGraphicsItemFibExtObject::paint( QPainter * pPainter,
	const QStyleOptionGraphicsItem * pOption, QWidget * pWidget ){
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) called"<<endl<<flush);
	
	QPixmap * pPixmapForFibObject = NULL;
	QPainter * pPainterPixmap = NULL;
	
	if ( pPainter != NULL ){
		//if Fib object should be drawn
		mutexGraphicsPixmapItemForFibObject.lock();
		DEBUG_OUT_L3(<<"cFibGraphicsItemFibExtObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) if Fib object should be drawn (pGraphicsPixmapItemForFibObject="<<pGraphicsPixmapItemForFibObject<<")"<<endl<<flush);
		if ( pGraphicsPixmapItemForFibObject != NULL ){
			/*if Fib object not changed and a pixmap exists for it
			 -> use pixmap to draw Fib object*/
			pGraphicsPixmapItemForFibObject->paint( pPainter, pOption, pWidget );
			DEBUG_OUT_L3(<<"cFibGraphicsItemFibExtObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) done use pixmap to draw Fib object"<<endl<<flush);
			mutexGraphicsPixmapItemForFibObject.unlock();
			return;
		}
		mutexGraphicsPixmapItemForFibObject.unlock();
	
		//adapt painter to draw a pixmap
		if ( boundingRectangle.isValid() ){
			//evalue size of the pixmap to draw on
			DEBUG_OUT_L3(<<"cFibGraphicsItemFibExtObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) evalue size of the pixmap to draw on"<<endl<<flush);
			
			bool bUsePixmap = false;
			
			if ( pFibGraphicsScene ){
				const QSizeF sizePixle = pFibGraphicsScene->getPointSize();
				
				if ( ( ((qreal)((int)( sizePixle.width() ))) == sizePixle.width() ) &&
						( ((qreal)((int)( sizePixle.height() ))) == sizePixle.height() ) ){
					//if the pixle hight and width are integers
					bUsePixmap = true;
				}//else hight and width are not integers -> don't use pixmap
			}else{//default paintwidth is 1
				bUsePixmap = true;
			}
			if ( bUsePixmap ){
				//adapt painter to paint also on a pixmap
				DEBUG_OUT_L3(<<"cFibGraphicsItemFibExtObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) pPixmapForFibObject = new QPixmap( "<< (boundingRectangle.width() + 8) <<", "<< (boundingRectangle.height() + 8 )<<" )"<<endl<<flush);
				pPixmapForFibObject = new QPixmap(
					boundingRectangle.width() + 8 ,
					boundingRectangle.height() + 8 );
				
				pPixmapForFibObject->fill( QColor( 0, 0, 0, 0 ) );
				
				pPainterPixmap = new QPainter();
				pPainterPixmap->begin( pPixmapForFibObject );
			}
		}
	}//end if painter not NULL
	
	cEvalueSimpleRGBA255QPainter * pEvalueSimpleRGBA255QPainter = NULL;
	
	if ( pFibGraphicsScene ){
		//try to use the cEvalueSimpleRGBA255QPainter from the graphics scene
		const cEvalueSimpleRGBA255QPainter * pEvalueSimpleRGBA255QPainterGraphicScene =
			pFibGraphicsScene->getEvalueSimpleRGBA255QPainter();
		if ( pEvalueSimpleRGBA255QPainterGraphicScene ){
			//cEvalueSimpleRGBA255QPainter from the graphic scene exists -> use it
			if ( pPainterPixmap ){
				//use also the pixmap painter
				pEvalueSimpleRGBA255QPainter = new cEvalueSimpleRGBA255TwoQPainter(
					pPainter, pPainterPixmap, *pEvalueSimpleRGBA255QPainterGraphicScene );
				
				((cEvalueSimpleRGBA255TwoQPainter*)pEvalueSimpleRGBA255QPainter)->
					setOffsetSecondPainter( ( boundingRectangle.left() - 4 ),
						( boundingRectangle.top() - 4 ) );
				
			}else{//use just one painter
				pEvalueSimpleRGBA255QPainter = new cEvalueSimpleRGBA255QPainter(
					pPainter, *pEvalueSimpleRGBA255QPainterGraphicScene );
			}
		}
		//set the pen
		//TODO what if a point is not a quadrangle?
		pFibGraphicsScene->setPenForPointSize( pPainter );
		if ( pPainterPixmap ){
			pFibGraphicsScene->setPenForPointSize( pPainterPixmap );
		}
	}
	if ( pEvalueSimpleRGBA255QPainter == NULL ){
		//use dummy cEvalueSimpleRGBA255QPainter
		if ( pPainterPixmap ){
			//use also the pixmap painter
			pEvalueSimpleRGBA255QPainter = new cEvalueSimpleRGBA255TwoQPainter(
				pPainter, pPainterPixmap );
			
			((cEvalueSimpleRGBA255TwoQPainter*)pEvalueSimpleRGBA255QPainter)->
				setOffsetSecondPainter( ( boundingRectangle.left() - 4 ),
					( boundingRectangle.top() - 4 ) );
		}else{//use just one painter
			pEvalueSimpleRGBA255QPainter = new cEvalueSimpleRGBA255QPainter( pPainter );
		}
	}
	bool bFibObjectEvalued = false;
	//assign input variable values
	if ( pWidgetFibInputVariables ){
		pWidgetFibInputVariables->assignValues();
	}
	//assign input vector values
	if ( ( pWidgetFibVector != NULL ) &&
			( pWidgetFibVector->getFibVector() != NULL ) ){
		pWidgetFibVector->getFibVector()->assignValues();
	}
	
	if ( pFibObject ){
		DEBUG_OUT_L3(<<"cFibGraphicsItemFibExtObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) evalue pFibObject"<<endl<<flush);
		bFibObjectEvalued = pFibObject->evalueObjectSimple(
			*pEvalueSimpleRGBA255QPainter );
	}//else Error no Fib object to evalue
	if ( bFibObjectEvalued ){
		const QRectF boundingRectangleEvalued =
			pEvalueSimpleRGBA255QPainter->boundingRectangle;
		//update pGraphicsPixmapItemForFibObject if possible
		if ( pPainterPixmap ){
			pPainterPixmap->end();
			//a pixmap was evalued for the Fib object
			DEBUG_OUT_L3(<<"cFibGraphicsItemFibExtObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) a pixmap was evalued for the Fib object"<<endl<<flush);
			
			//the start point wher to start copy the pismap
			const qreal fPixmapLeftClip = boundingRectangleEvalued.x() -
					( boundingRectangle.x() - 4 );
			const qreal fPixmapTopClip = boundingRectangleEvalued.y() -
					( boundingRectangle.y() - 4 );
			
			if ( boundingRectangleEvalued.isValid() &&
					( 0 <= fPixmapLeftClip ) && ( 0 <= fPixmapTopClip ) &&
					( ( boundingRectangleEvalued.width() + fPixmapLeftClip ) <=
						boundingRectangle.width() + 8 ) &&
					( ( boundingRectangleEvalued.height() + fPixmapTopClip ) <=
						boundingRectangle.height() + 8 ) ){
				//new bounding rectangle is contained in pixmap
				DEBUG_OUT_L3(<<"cFibGraphicsItemFibExtObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) new bounding rectangle is contained in pixmap"<<endl<<flush);
				mutexGraphicsPixmapItemForFibObject.lock();
				if ( pGraphicsPixmapItemForFibObject ){
					//delete old graphics pixmap item
					delete pGraphicsPixmapItemForFibObject;
					pGraphicsPixmapItemForFibObject = NULL;
				}
				
				DEBUG_OUT_L3(<<"cFibGraphicsItemFibExtObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) create a graphic item pixmap object for the Fib objects"<<endl<<flush);
				//create a graphic item pixmap object for the Fib objects
				pGraphicsPixmapItemForFibObject = new QGraphicsPixmapItem(
					//copy the area for the Fib object
					*pPixmapForFibObject );
				pGraphicsPixmapItemForFibObject->setOffset(
					boundingRectangle.left() - 4,
					boundingRectangle.top() - 4 );
				mutexGraphicsPixmapItemForFibObject.unlock();
			}
		}//end if update pGraphicsPixmapItemForFibObject if possible
		
		//update the bounding rectangle of this class
		DEBUG_OUT_L3(<<"cFibGraphicsItemFibExtObject("<<this<<")::paint() boundingRectangle=( "<<boundingRectangle.x()<<", "<<boundingRectangle.y()<<" ) w="<<boundingRectangle.width()<<" h="<<boundingRectangle.height()<<endl<<flush);
		DEBUG_OUT_L3(<<"cFibGraphicsItemFibExtObject("<<this<<")::paint() evalued boundingRectangle=( "<<boundingRectangleEvalued.x()<<", "<<boundingRectangleEvalued.y()<<" ) w="<<boundingRectangleEvalued.width()<<" h="<<boundingRectangleEvalued.height()<<endl<<flush);
		if ( boundingRectangle != boundingRectangleEvalued ){
			//bounding rectangle changed
			prepareGeometryChange();
			boundingRectangle = boundingRectangleEvalued;
		}
	}
	DEBUG_OUT_L4(<<"cFibGraphicsItemFibExtObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) delete pEvalueSimpleRGBA255QPainter"<<endl<<flush);
	delete pEvalueSimpleRGBA255QPainter;
	if ( pPainterPixmap != NULL ){
		//delete duplicate painter
		DEBUG_OUT_L4(<<"cFibGraphicsItemFibExtObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) delete duplicate painter"<<endl<<flush);
		delete pPainterPixmap;
		//delete pixmap object
		DEBUG_OUT_L4(<<"cFibGraphicsItemFibExtObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) delete pixmap object"<<endl<<flush);
		delete pPixmapForFibObject;
	}
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) done"<<endl<<flush);
}


/**
 * This slot will notify the Fib node, which contains this graphic item
 * Fib object, that it was changed.
 * This method should be called if the Fib object of this widget
 * changes.
 * @see fibNodeChangedEvent()
 */
void cFibGraphicsItemFibExtObject::notifyNodeForChange(){
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this<<")::notifyNodeForChange() called"<<endl<<flush);
	//TODO no change possible at the time -> this function shouldn't be used
	if ( pFibGraphicsScene ){
		//notify via the graphics scene
		pFibGraphicsScene->notifyNodeForChange();
	}
}


/**
 * This method reevaluates the bounding box of this graphical item.
 *
 * @see boundingRect()
 * @see boundingRectangle
 * @see signalReevaluateBoundingBox()
 */
void cFibGraphicsItemFibExtObject::reevaluateBoundingBox() {
	
	paint( NULL, NULL );
}


/**
 * Event method
 * It will be called every time a input variable value (cFibInputVariable),
 * at which this object is registered, was changed.
 *
 * @see cFibInputVariable::dValue
 * @param pFibScalar a pointer to the changed Fib input variable
 */
void cFibGraphicsItemFibExtObject::fibScalarValueChangedEvent(
		const cFibScalar * pFibScalar ){
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this <<")::fibInputVariableValueChangedEvent( pFibScalar="<<pFibScalar<<") called"<<endl<<flush);
	if ( pFibScalar == NULL ){
		//no input variable changed -> nothing to do
		return;
	}
	mutexGraphicsPixmapItemForFibObject.lock();
	if ( pGraphicsPixmapItemForFibObject ){
		//Fib object needs to be reevaluated -> delete pGraphicsPixmapItemForFibObject
		delete pGraphicsPixmapItemForFibObject;
		pGraphicsPixmapItemForFibObject = NULL;
	}
	mutexGraphicsPixmapItemForFibObject.unlock();
	//reevaluate the bounding box (boundingRectangle)
	emit signalReevaluateBoundingBox();
	//TODO needed? redraw this item
	//update( boundingRectangle );
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this <<")::fibInputVariableValueChangedEvent( pFibScalar="<<pFibScalar<<") done"<<endl<<flush);
}



/**
 * This method evalues the input variables for this object.
 */
void cFibGraphicsItemFibExtObject::evalueInputVariables(){
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this<<")::evalueInputVariables() called"<<endl<<flush);
	//evalue input variables
	if ( pWidgetFibInputVariables ){
		pWidgetFibInputVariables->unregisterScalarValueChangeListener( this );
		pWidgetFibInputVariables->deleteLater();
		pWidgetFibInputVariables = NULL;
	}
	if ( pFibObject ){
		pWidgetFibInputVariables = new cWidgetFibInputVariables(
			pFibObject, true, true );
		
		mutexMainOptions.lock();
		if ( pWidgetMainOptions ){
			//add input variables widget to the main options widget
			static_cast<QSplitter *>(pWidgetMainOptions)->addWidget(
				pWidgetFibInputVariables );
		}
		mutexMainOptions.unlock();
	}
	
	if ( pWidgetFibInputVariables ){
		//register this object as a value change listener of them
		pWidgetFibInputVariables->registerScalarValueChangeListener( this );
	}
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this<<")::evalueInputVariables() done"<<endl<<flush);
}


/**
 * This method creats the main options widget (pWidgetMainOptions).
 *
 * @see pWidgetMainOptions
 * @return true if the main options widget was created
 * 	(pWidgetMainOptions != 0), else false
 */
bool cFibGraphicsItemFibExtObject::createMainOptions(){
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this<<")::createMainOptions() started"<<endl<<flush);
	mutexMainOptions.lock();
	if ( pWidgetMainOptions != NULL ){
		//main options widget allready existing -> do nothing
		DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this<<")::createMainOptions() done main options widget allready existing -> do nothing"<<endl<<flush);
		mutexMainOptions.unlock();
		return false;
	}
	/*create widget with input values of external object and input variables
	 *of the part object*/
	cFibElement * pFibObject = getFibObject();
	if ( ( pFibObject != NULL ) && ( pFibObject->getType() == 'o' ) ){
		//get Fib vector widget
		cExtObject * pExtObject = static_cast< cExtObject * >( pFibObject );
		
		cVectorExtObject * pVecExtObject = pExtObject->getInputVector();
		cFibVectorHandler * pFibVectorHandler = cFibVectorHandler::getInstance();
		
		if ( ( pVecExtObject != NULL ) && ( pFibVectorHandler != NULL ) ){
			cFibVectorCreator * pFibVectorExtObject =
				pFibVectorHandler->getFibVectorForFibVector( pVecExtObject );
			if ( pFibVectorExtObject ){
				pWidgetFibVector = new cWidgetFibVector( pFibVectorExtObject );
			}
		}
	}
	
	if ( ( pWidgetFibVector == NULL ) && ( pWidgetFibInputVariables == NULL ) ){
		//no options widget needed
		mutexMainOptions.unlock();
		return false;
	}
	//create the splitter widget for the subwidgets (vector + input variables)
	QSplitter * pSplitterMainOptions = new QSplitter();
	pWidgetMainOptions = pSplitterMainOptions;
	pSplitterMainOptions->setOrientation( Qt::Vertical );
	
	//evalue a good maximum size
	int iMaximumWidth  = 400;
	int iMaximumHeight = 400;
	if ( pFibGraphicsScene != NULL ) {
		const QGraphicsView * pGraphicsView =
			pFibGraphicsScene->views().first();
		if ( pGraphicsView ) {
			const QSize sizeGraphicView = pGraphicsView->size();
			iMaximumWidth = max( sizeGraphicView.width() , iMaximumWidth );
			iMaximumHeight = max( sizeGraphicView.height() , iMaximumWidth );
		}
	}
	DEBUG_OUT_L3(<<"cFibGraphicsItemFibExtObject("<<this<<")::createMainOptions() the maximum width is "<<iMaximumWidth<<endl<<flush);
	
	//size with which to enlarge the widget size
	const QSize sizeEnlargeBy( 32, 32 );
	
	if ( pWidgetFibVector ){
		//add widget for the external object vector
		pSplitterMainOptions->addWidget( pWidgetFibVector );
		
		//resize to a good size; not to big, not to smaal
		QSize sizeVectorWidget = pWidgetFibVector->sizeHint( -1 );
		
		sizeVectorWidget += sizeEnlargeBy;
		//check if inside maximum width
		if ( ( iMaximumWidth < sizeVectorWidget.width() ) &&
				( pWidgetFibVector->getFibVector() != NULL ) ) {
			//reduce width to maximum width -> do a binary search for a good size
			int iLowerBoundOfElements = 1;
			int iUpperBoundOfElements = pWidgetFibVector->getFibVector()->
				getNumberOfElements();
			int iActuaNumberOfElements;
			while ( iLowerBoundOfElements < iUpperBoundOfElements ) {
				
				if ( iLowerBoundOfElements + 1 != iUpperBoundOfElements ) {
					iActuaNumberOfElements =
						( iLowerBoundOfElements + iUpperBoundOfElements ) / 2;
				}else{/*difference of one betwean upper and lower bound
					-> last iteration -> evalue values for lower bound*/
					iActuaNumberOfElements = iLowerBoundOfElements;
					iUpperBoundOfElements  = iLowerBoundOfElements;
				}
				
				sizeVectorWidget = pWidgetFibVector->
					sizeHintForMinElementsInLine( iActuaNumberOfElements );
				sizeVectorWidget += sizeEnlargeBy;
				
				if ( iMaximumWidth < sizeVectorWidget.width() ) {
					/*width for iActuaNumberOfElements elements to big
					 -> iActuaNumberOfElements is new upper bound of width*/
					DEBUG_OUT_L3(<<"cFibGraphicsItemFibExtObject("<<this<<")::createMainOptions() width for "<<iActuaNumberOfElements<<" elements to big "<<sizeVectorWidget.width()<<endl<<flush);
					
					iUpperBoundOfElements = iActuaNumberOfElements;
				}else{/*width for iActuaNumberOfElements elements OK
					 -> iActuaNumberOfElements is new lower bound of width*/
					DEBUG_OUT_L3(<<"cFibGraphicsItemFibExtObject("<<this<<")::createMainOptions() width for "<<iActuaNumberOfElements<<" elements OK "<<sizeVectorWidget.width()<<endl<<flush);
					
					iLowerBoundOfElements = iActuaNumberOfElements;
				}
			}
		}
		if ( iMaximumHeight < sizeVectorWidget.height() ){
			//reduce height to maximum height
			sizeVectorWidget.setHeight( iMaximumHeight );
		}
		
		pSplitterMainOptions->resize( sizeVectorWidget );
	}
	if ( pWidgetFibInputVariables ){
		//add input variables widget
		pSplitterMainOptions->addWidget( pWidgetFibInputVariables );
		//enlarge for input variable widget
		QSize sizeInputVariablesWidget =
			pWidgetFibInputVariables->sizeHint( -1 );
		
		sizeInputVariablesWidget += sizeEnlargeBy;
		//check if inside maximum width
		if ( iMaximumWidth < sizeInputVariablesWidget.width() ) {
			//reduce width to maximum width -> do a binary search for a good size
			int iLowerBoundOfVariables = 1;
			int iUpperBoundOfVariables = pWidgetFibInputVariables->
				getNumberOfInputVariables();
			int iActuaNumberOfVariables;
			while ( iLowerBoundOfVariables < iUpperBoundOfVariables ) {
				
				if ( iLowerBoundOfVariables + 1 != iUpperBoundOfVariables ) {
					iActuaNumberOfVariables =
						( iLowerBoundOfVariables + iUpperBoundOfVariables ) / 2;
				}else{/*difference of one betwean upper and lower bound
					-> last iteration -> evalue values for lower bound*/
					iActuaNumberOfVariables = iLowerBoundOfVariables;
					iUpperBoundOfVariables  = iLowerBoundOfVariables;
				}
				
				sizeInputVariablesWidget = pWidgetFibInputVariables->
					sizeHintForMinElementsInLine( iActuaNumberOfVariables );
				sizeInputVariablesWidget += sizeEnlargeBy;
				
				if ( iMaximumWidth < sizeInputVariablesWidget.width() ) {
					/*width for iActuaNumberOfVariables elements to big
					 -> iActuaNumberOfVariables is new upper bound of width*/
					iUpperBoundOfVariables = iActuaNumberOfVariables;
				}else{/*width for iActuaNumberOfVariables elements OK
					 -> iActuaNumberOfVariables is new lower bound of width*/
					iLowerBoundOfVariables = iActuaNumberOfVariables;
				}
			}
		}
		//add input variables widget size to splitter size
		QSize sizeSplitterWidget = pSplitterMainOptions->size();
		
		sizeSplitterWidget.setWidth(
			max( sizeSplitterWidget.width(), sizeInputVariablesWidget.width() ) );
		sizeSplitterWidget.setHeight( min( iMaximumHeight,
			sizeSplitterWidget.height() + sizeInputVariablesWidget.height() ) );
		
		pSplitterMainOptions->resize( sizeSplitterWidget );
	}
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibExtObject("<<this<<")::createMainOptions() done"<<endl<<flush);
	mutexMainOptions.unlock();
	return true;
}











