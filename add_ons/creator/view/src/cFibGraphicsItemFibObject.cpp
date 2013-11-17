
//TODO check

/**
 * @file cFibGraphicsItemFibObject
 * file name: cFibGraphicsItemFibObject.cpp
 * @author Betti Oesterholz
 * @date 28.07.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a graphics item for a Fib object.
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
 * This file implements a class for a graphics item for a Fib object.
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
28.07.2013  Oesterholz  created
*/


//TODO switches for test proposes
//#define DEBUG


#include "cFibGraphicsItemFibObject.h"

#include "cFibElement.h"

#include "cFibGraphicsScene.h"
#include "cFibInputVariable.h"
#include "cFibInputVariables.h"
#include "cWidgetFibInputVariables.h"
#include "cEvalueSimpleRGBA255QPainter.h"
#include "cEvalueSimpleRGBA255TwoQPainter.h"
#include "eFibNodeChangedEvent.h"
#include "cFibNode.h"
#include "cFibNodeHandler.h"

#include <list>

#include <QPixmap>
#include <QGraphicsPixmapItem>


using namespace std;
using namespace fib::nCreator;
using namespace fib;

/**
 * parameter constructor for a graphics item for a Fib object
 *
 * @param pInFibObject a pointer to the Fib object object for the
 * 	widget / item to construct
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
cFibGraphicsItemFibObject::cFibGraphicsItemFibObject( cFibElement * pInFibObject,
		const unsigned long ulInFibNodeVersionDisplayed,
		cFibElement * pInFibObjectCopy,
		QGraphicsItem * pParent ):
		cFibGraphicsItem( pInFibObject, ulInFibNodeVersionDisplayed, pParent ),
		pFibObjectCopy( pInFibObjectCopy ), pFibObjectCopyNode( NULL ),
		pWidgetFibInputVariables( NULL ), pFibInputVariablesCopy( NULL ),
		pGraphicsPixmapItemForFibObject( NULL ){
			
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibObject("<<this<<")::cFibGraphicsItemFibObject( pInFibObject="<<pInFibObject<<", ulInFibNodeVersionDisplayed="<<ulInFibNodeVersionDisplayed<<", pInFibObjectCopy="<<pInFibObjectCopy<<", pParent="<<pParent<<" ) called"<<endl<<flush);
	
	if ( pFibObjectCopy ){
		//if a Fib object copy exists -> get node object for it
		pFibObjectCopyNode = cFibNodeHandler::getInstance()->
			getNodeForFibObject( pFibObjectCopy, this );
		DEBUG_OUT_L3(<<"cFibGraphicsItemFibObject("<<this<<")::cFibGraphicsItemFibObject( pInFibObject="<<pInFibObject<<", ulInFibNodeVersionDisplayed="<<ulInFibNodeVersionDisplayed<<", pInFibObjectCopy="<<pInFibObjectCopy<<", pParent="<<pParent<<" ) Fib node for copy Fib object: "<<pFibObjectCopyNode<<endl<<flush);
	}
	
	//reevaluate the bounding box (boundingRectangle)
	paint( NULL, NULL );
	
	//evalue input variables
	evalueInputVariables();
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
 * @param pInFibObjectCopy a pointer to a copy of a Fib object to copy;
 * 	This Fib object will be shown by this object with evalueObject()
 * 	if present, else pFibObject will be used.
 * 	This object is responsible for deleting the Fib object copy.
 * 	@see pFibObjectCopy
 * @param pParent a pointer to parent of this widget
 */
cFibGraphicsItemFibObject::cFibGraphicsItemFibObject( cFibElement * pInFibObject,
		const unsigned long ulInFibNodeVersionDisplayed,
		cFibGraphicsScene * pInFibGraphicsScene,
		cFibElement * pInFibObjectCopy,
		QGraphicsItem * pParent ):
		cFibGraphicsItem( pInFibObject, ulInFibNodeVersionDisplayed,
			pInFibGraphicsScene, pParent ),
		pFibObjectCopy( pInFibObjectCopy ), pFibObjectCopyNode( NULL ),
		pWidgetFibInputVariables( NULL ), pFibInputVariablesCopy( NULL ),
		pGraphicsPixmapItemForFibObject( NULL ){
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibObject("<<this<<")::cFibGraphicsItemFibObject( pInFibObject="<<pInFibObject<<", pInFibGraphicsScene="<<pInFibGraphicsScene<<", ulInFibNodeVersionDisplayed="<<ulInFibNodeVersionDisplayed<<", pInFibObjectCopy="<<pInFibObjectCopy<<", pParent="<<pParent<<" ) called"<<endl<<flush);
	
	if ( pFibObjectCopy ){
		//if a Fib object copy exists -> get node object for it
		pFibObjectCopyNode = cFibNodeHandler::getInstance()->
			getNodeForFibObject( pFibObjectCopy, this );
		DEBUG_OUT_L3(<<"cFibGraphicsItemFibObject("<<this<<")::cFibGraphicsItemFibObject( pInFibObject="<<pInFibObject<<", pInFibGraphicsScene="<<pInFibGraphicsScene<<", ulInFibNodeVersionDisplayed="<<ulInFibNodeVersionDisplayed<<", pInFibObjectCopy="<<pInFibObjectCopy<<", pParent="<<pParent<<" ) Fib node for copy Fib object: "<<pFibObjectCopyNode<<endl<<flush);
	}
	
	//evalue input variables
	evalueInputVariables();
	//reevaluate the bounding box (boundingRectangle)
	paint( NULL, NULL );
	
}


/**
 * destructor
 */
cFibGraphicsItemFibObject::~cFibGraphicsItemFibObject(){
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibObject("<<this<<")::~cFibGraphicsItemFibObject() called"<<endl<<flush);
	if ( pFibObjectCopyNode ){
		//the Fib node handler will delete the copy Fib object
		DEBUG_OUT_L3(<<"cFibGraphicsItemFibObject("<<this<<")::~cFibGraphicsItemFibObject() unregister this at Fib node "<<pFibObjectCopyNode<<endl<<flush);
		pFibObjectCopyNode->unregisterNodeChangeListener( this );
		pFibObjectCopyNode = NULL;
		pFibObjectCopy = NULL;
	}
	if ( pWidgetFibInputVariables ){
		//unregister this object as a value change listener of them
		pWidgetFibInputVariables->unregisterInputVariableValueChangeListener( this );
		//delete input variables
		pWidgetFibInputVariables->deleteLater();
	}
	if ( pFibInputVariablesCopy ){
		delete pFibInputVariablesCopy;
	}
	mutexGraphicsPixmapItemForFibObject.lock();
	if ( pGraphicsPixmapItemForFibObject ){
		//delete the pixmap for the Fib object
		delete pGraphicsPixmapItemForFibObject;
	}
	mutexGraphicsPixmapItemForFibObject.unlock();
}


/**
 * @return a pointer to the Fib object this widget / item represents
 * 	@see pFibObject
 */
const cFibElement * cFibGraphicsItemFibObject::getFibObjectCopy() const{
	
	return pFibObjectCopy;
}


/**
 * @return the name of this class "cFibGraphicsItemFibObject"
 */
std::string cFibGraphicsItemFibObject::getName() const{
	
	return std::string( "cFibGraphicsItemFibObject" );
}


/**
 * @return the outer bounds of this graphic item
 * 	@see QGraphicsItem::boundingRect()
 */
QRectF cFibGraphicsItemFibObject::boundingRect() const{
	
	return boundingRectangle;
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
bool cFibGraphicsItemFibObject::updateForFibElementChange(
		const eFibNodeChangedEvent * pFibNodeChangedEvent,
		QList< cFibGraphicsItem * > * liOutNotUpdatedItems ){
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibObject("<<this<<")::updateForFibElementChange( const eFibNodeChangedEvent * pFibNodeChangedEvent, QList< cFibGraphicsItem * > * liOutNotUpdatedItems ) called"<<endl<<flush);
	if ( ( pFibNodeChangedEvent == NULL ) ||
			( pFibNodeChangedEvent->pFibNodeChanged == NULL ) ){
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
	paint( NULL, NULL );
	return bReturnValue;
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
void cFibGraphicsItemFibObject::paint( QPainter * pPainter,
	const QStyleOptionGraphicsItem * pOption, QWidget * pWidget ){
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) called"<<endl<<flush);
	
	QPixmap * pPixmapForFibObject = NULL;
	QPainter * pPainterPixmap = NULL;
	
	if ( pPainter != NULL ){
		//if Fib object should be drawn
		mutexGraphicsPixmapItemForFibObject.lock();
		DEBUG_OUT_L3(<<"cFibGraphicsItemFibObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) if Fib object should be drawn (pGraphicsPixmapItemForFibObject="<<pGraphicsPixmapItemForFibObject<<")"<<endl<<flush);
		if ( pGraphicsPixmapItemForFibObject != NULL ){
			/*if Fib object not changed and a pixmap exists for it
			 -> use pixmap to draw Fib object*/
			pGraphicsPixmapItemForFibObject->paint( pPainter, pOption, pWidget );
			DEBUG_OUT_L3(<<"cFibGraphicsItemFibObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) done use pixmap to draw Fib object"<<endl<<flush);
			mutexGraphicsPixmapItemForFibObject.unlock();
			return;
		}
		mutexGraphicsPixmapItemForFibObject.unlock();
	
		//adapt painter to draw a pixmap
		if ( boundingRectangle.isValid() ){
			//evalue size of the pixmap to draw on
			DEBUG_OUT_L3(<<"cFibGraphicsItemFibObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) evalue size of the pixmap to draw on"<<endl<<flush);
			
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
				DEBUG_OUT_L3(<<"cFibGraphicsItemFibObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) pPixmapForFibObject = new QPixmap( "<< (boundingRectangle.width() + 8) <<", "<< (boundingRectangle.height() + 8 )<<" )"<<endl<<flush);
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
	if ( pFibObjectCopy ){
		DEBUG_OUT_L3(<<"cFibGraphicsItemFibObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) evalue pFibObjectCopy"<<endl<<flush);
		/*TODO adapt: skip root objects so they don't set the input varaibles
		bFibObjectEvalued = pFibObjectCopy->evalueObjectSimple(
			*pEvalueSimpleRGBA255QPainter );
		*/
		//skip root objects
		cFibElement * pObjectToEvalue = pFibObjectCopy;
		while ( pObjectToEvalue->getType() == 'r' ){
			//top most element is root element -> skip root element
			if ( pObjectToEvalue->getNextFibElement() == NULL ){
				//no next Fib object ->can't use it
				break;
			}
			pObjectToEvalue = pObjectToEvalue->getNextFibElement();
		}
		bFibObjectEvalued =
			pObjectToEvalue->evalueObjectSimple( *pEvalueSimpleRGBA255QPainter );
		
		//TODO adapt end
		
	}else if ( pFibObject ){
		DEBUG_OUT_L3(<<"cFibGraphicsItemFibObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) evalue pFibObject"<<endl<<flush);
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
			DEBUG_OUT_L3(<<"cFibGraphicsItemFibObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) a pixmap was evalued for the Fib object"<<endl<<flush);
			
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
				DEBUG_OUT_L3(<<"cFibGraphicsItemFibObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) new bounding rectangle is contained in pixmap"<<endl<<flush);
				mutexGraphicsPixmapItemForFibObject.lock();
				if ( pGraphicsPixmapItemForFibObject ){
					//delete old graphics pixmap item
					delete pGraphicsPixmapItemForFibObject;
					pGraphicsPixmapItemForFibObject = NULL;
				}
				
				DEBUG_OUT_L3(<<"cFibGraphicsItemFibObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) create a graphic item pixmap object for the Fib objects"<<endl<<flush);
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
		DEBUG_OUT_L3(<<"cFibGraphicsItemFibObject("<<this<<")::paint() boundingRectangle=( "<<boundingRectangle.x()<<", "<<boundingRectangle.y()<<" ) w="<<boundingRectangle.width()<<" h="<<boundingRectangle.height()<<endl<<flush);
		DEBUG_OUT_L3(<<"cFibGraphicsItemFibObject("<<this<<")::paint() evalued boundingRectangle=( "<<boundingRectangleEvalued.x()<<", "<<boundingRectangleEvalued.y()<<" ) w="<<boundingRectangleEvalued.width()<<" h="<<boundingRectangleEvalued.height()<<endl<<flush);
		if ( boundingRectangle != boundingRectangleEvalued ){
			//bounding rectangle changed
			prepareGeometryChange();
			boundingRectangle = boundingRectangleEvalued;
		}
	}
	DEBUG_OUT_L4(<<"cFibGraphicsItemFibObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) delete pEvalueSimpleRGBA255QPainter"<<endl<<flush);
	delete pEvalueSimpleRGBA255QPainter;
	if ( pPainterPixmap != NULL ){
		//delete duplicate painter
		DEBUG_OUT_L4(<<"cFibGraphicsItemFibObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) delete duplicate painter"<<endl<<flush);
		delete pPainterPixmap;
		//delete pixmap object
		DEBUG_OUT_L4(<<"cFibGraphicsItemFibObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) delete pixmap object"<<endl<<flush);
		delete pPixmapForFibObject;
	}
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) done"<<endl<<flush);
}


/**
 * This slot will notify the Fib node, which contains this graphic item
 * Fib object, that it was changed.
 * This method should be called if the Fib object of this widget
 * changes.
 * @see fibNodeChangedEvent()
 */
void cFibGraphicsItemFibObject::notifyNodeForChange(){
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibObject("<<this<<")::notifyNodeForChange() called"<<endl<<flush);
	//TODO no change possible at the time -> this function shouldn't be used
	if ( pFibGraphicsScene ){
		//notyfy via the graphics scene
		pFibGraphicsScene->notifyNodeForChange();
	}
}


/**
 * Event method
 * It will be called every time a input variable value (cFibInputVariable),
 * at which this object is registered, was changed.
 *
 * @see cFibInputVariable::dValue
 * @param pFibInputVariable a pointer to the changed Fib input variable
 */
void cFibGraphicsItemFibObject::fibInputVariableValueChangedEvent(
		const cFibInputVariable * pFibInputVariable ){
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibObject("<<this <<")::fibInputVariableValueChangedEvent( pFibInputVariable="<<pFibInputVariable<<") called"<<endl<<flush);
	if ( pFibInputVariable == NULL ){
		//no input variable changed -> nothing to do
		return;
	}
	//try to set the value of the input variable for the copy Fib object
	cFibInputVariable * pFibInputVariableCopy =
		mapInVars.value( const_cast<cFibInputVariable *>(pFibInputVariable), NULL );
	if ( pFibInputVariableCopy != NULL ){
		//set the value also for the input variable copy
		DEBUG_OUT_L2(<<"cFibGraphicsItemFibObject("<<this <<")::fibInputVariableValueChangedEvent( pFibInputVariable="<<pFibInputVariable<<") set the value also for the input variable copy to "<<pFibInputVariable->getValue()<<endl<<flush);
		pFibInputVariableCopy->setValue( pFibInputVariable->getValue() );
	}
	//assign input variable values
	if ( pWidgetFibInputVariables ){
		pWidgetFibInputVariables->assignValues();
	}
	if ( pFibInputVariablesCopy ){
		pFibInputVariablesCopy->assignValues();
	}
	mutexGraphicsPixmapItemForFibObject.lock();
	if ( pGraphicsPixmapItemForFibObject ){
		//Fib object needs to be reevaluated -> delete pGraphicsPixmapItemForFibObject
		delete pGraphicsPixmapItemForFibObject;
		pGraphicsPixmapItemForFibObject = NULL;
	}
	mutexGraphicsPixmapItemForFibObject.unlock();
	//reevaluate the bounding box (boundingRectangle)
	paint( NULL, NULL );
	//redraw this item
	update( boundingRectangle );
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibObject("<<this <<")::fibInputVariableValueChangedEvent( pFibInputVariable="<<pFibInputVariable<<") done"<<endl<<flush);
}



/**
 * This method evalues the input variables vor thir object.
 */
void cFibGraphicsItemFibObject::evalueInputVariables(){
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibObject("<<this<<")::evalueInputVariables() called"<<endl<<flush);
	//evalue input variables
	if ( pWidgetFibInputVariables ){
		pWidgetFibInputVariables->unregisterInputVariableValueChangeListener( this );
		pWidgetFibInputVariables->deleteLater();
		pWidgetFibInputVariables = NULL;
	}
	if ( pFibObject ){
		pWidgetFibInputVariables = new cWidgetFibInputVariables(
				pFibObject, true, true );
	}
	if ( pFibInputVariablesCopy ){
		delete pFibInputVariablesCopy;
		pFibInputVariablesCopy = NULL;
	}
	if ( pFibObjectCopy ){
		//evalue the input variables for the copy
		pFibInputVariablesCopy = new cFibInputVariables(
			pFibObjectCopy, true, true );
	}
	if ( ( pWidgetFibInputVariables != NULL ) && ( pFibInputVariablesCopy != NULL ) ){
		//create input variables map
		const unsigned int uiNumberOfInputVariables =
			pWidgetFibInputVariables->getNumberOfInputVariables();
		
		for ( unsigned int uiActualInVar = 1;
				uiActualInVar <= uiNumberOfInputVariables; uiActualInVar++ ){
			
			mapInVars.insert(
				pWidgetFibInputVariables->getInputVariable( uiActualInVar ),
				pFibInputVariablesCopy->getInputVariable( uiActualInVar ) );
		}//end for all input variables
	}
	
	if ( pWidgetFibInputVariables ){
		//register this object as a value change listener of them
		pWidgetFibInputVariables->registerInputVariableValueChangeListener( this );
	}
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibObject("<<this<<")::evalueInputVariables() done"<<endl<<flush);
}


/**
 * Event method
 * It will be called every time a Fib node (cFibNode), at which
 * this object is registered, was changed.
 *
 * @param pFibNodeChanged a pointer to the event, with the information
 * 	about the changed Fib node
 */
void cFibGraphicsItemFibObject::fibNodeChangedEvent(
		const eFibNodeChangedEvent * pFibNodeChanged ){
	
	if ( ( pFibNodeChanged != NULL ) &&
			( pFibNodeChanged->pFibNodeChanged != NULL ) &&
			( pFibNodeChanged->pFibNodeChanged == pFibObjectCopyNode ) &&
			( pFibNodeChanged->bNodeDeleted ) ){
		
		DEBUG_OUT_L2(<<"cFibGraphicsItemFibObject("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) the Fib node object for the Fib object copy was deleted"<<endl<<flush);
		/*the Fib node object for the Fib object copy was deleted
		 -> don't use it or the Fib object copy anymore*/
		pFibObjectCopy = NULL;
		pFibObjectCopyNode = NULL;
		if ( pFibInputVariablesCopy ){
			delete pFibInputVariablesCopy;
			pFibInputVariablesCopy = NULL;
		}
	}
}








