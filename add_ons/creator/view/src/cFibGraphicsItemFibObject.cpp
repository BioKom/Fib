
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
#define DEBUG


#include "cFibGraphicsItemFibObject.h"

#include "cFibGraphicsScene.h"
#include "cEvalueSimpleRGBA255QPainter.h"

#include <list>

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
		pFibObjectCopy( pInFibObjectCopy ), pWidgetFibInputVariables( NULL ),
		pFibInputVariablesCopy( NULL ){
			
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibObject("<<this<<")::cFibGraphicsItemFibObject( pInFibObject="<<pInFibObject<<", ulInFibNodeVersionDisplayed="<<ulInFibNodeVersionDisplayed<<", cFibElement * pInFibObjectCopy="<<pInFibObjectCopy<<", QGraphicsItem * pParent="<<pParent<<" ) called"<<endl<<flush);
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
		pFibObjectCopy( pInFibObjectCopy ), pWidgetFibInputVariables( NULL ),
		pFibInputVariablesCopy( NULL ){
	DEBUG_OUT_L2(<<"cFibGraphicsItemFibObject("<<this<<")::cFibGraphicsItemFibObject( pInFibObject="<<pInFibObject<<", pInFibGraphicsScene="<<pInFibGraphicsScene<<" ulInFibNodeVersionDisplayed="<<ulInFibNodeVersionDisplayed<<", cFibElement * pInFibObjectCopy="<<pInFibObjectCopy<<", QGraphicsItem * pParent"<<pParent<<" ) called"<<endl<<flush);
	
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
	if ( pFibObjectCopy ){
		pFibObjectCopy->deleteObject();
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
	
	DEBUG_OUT_L3(<<"cFibGraphicsItemFibObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) called"<<endl<<flush);
	
	cEvalueSimpleRGBA255QPainter * pEvalueSimpleRGBA255QPainter = NULL;
	
	if ( pFibGraphicsScene ){
		//try to use the cEvalueSimpleRGBA255QPainter from the graphics scene
		const cEvalueSimpleRGBA255QPainter * pEvalueSimpleRGBA255QPainterGraphicScene =
			pFibGraphicsScene->getEvalueSimpleRGBA255QPainter();
		if ( pEvalueSimpleRGBA255QPainterGraphicScene ){
			//cEvalueSimpleRGBA255QPainter from the graphic scene exists -> use it
			pEvalueSimpleRGBA255QPainter = new cEvalueSimpleRGBA255QPainter(
				pPainter, *pEvalueSimpleRGBA255QPainterGraphicScene );
		}
		//set the pen
		//TODO what if a point is not a quadrangle?
		pFibGraphicsScene->setPenForPointSize( pPainter );
	}
	if ( pEvalueSimpleRGBA255QPainter == NULL ){
		//use dummy cEvalueSimpleRGBA255QPainter
		pEvalueSimpleRGBA255QPainter = new cEvalueSimpleRGBA255QPainter( pPainter );
	}
	bool bFibObjectEvalued = false;
	if ( pFibObjectCopy ){
		DEBUG_OUT_L3(<<"cFibGraphicsItemFibObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) evalue pFibObjectCopy"<<endl<<flush);
		/*TODO adapt: skip root objects so they dont set the input varaibles
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
		//update the bounding rectangle of this class
		DEBUG_OUT_L3(<<"cFibGraphicsItemFibObject("<<this<<")::paint() boundingRectangle=( "<<boundingRectangle.x()<<", "<<boundingRectangle.y()<<" ) "<<boundingRectangle.width()<<","<<boundingRectangle.height()<<endl<<flush);
		DEBUG_OUT_L3(<<"cFibGraphicsItemFibObject("<<this<<")::paint() evalued boundingRectangle=( "<<pEvalueSimpleRGBA255QPainter->boundingRectangle.x()<<", "<<pEvalueSimpleRGBA255QPainter->boundingRectangle.y()<<" ) "<<pEvalueSimpleRGBA255QPainter->boundingRectangle.width()<<","<<pEvalueSimpleRGBA255QPainter->boundingRectangle.height()<<endl<<flush);
		if ( boundingRectangle != pEvalueSimpleRGBA255QPainter->boundingRectangle ){
			//bounding rectangle changed
			prepareGeometryChange();
			boundingRectangle = pEvalueSimpleRGBA255QPainter->boundingRectangle;
		}
	}
	
	DEBUG_OUT_L3(<<"cFibGraphicsItemFibObject("<<this<<")::paint( pPainter="<<pPainter<<", pOption="<<pOption<<", pWidget="<<pWidget<<" ) done"<<endl<<flush);
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










