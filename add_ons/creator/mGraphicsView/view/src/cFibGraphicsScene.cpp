
//TODO check

/**
 * @file cFibGraphicsScene
 * file name: cFibGraphicsScene.cpp
 * @author Betti Oesterholz
 * @date 18.07.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for the graphics view of a Fib object.
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
 * This file implements a class for the graphics view of a Fib object.
 * It will display the Fib object as an graphic scene / image.
 * For that it will analyse a Fib objects, create and add Fib graphic items
 * cFibGraphicsItem for its parts, so that in the end all Fib graphic
 * items together will look like the image the Fib object represents.
 * The cFibGraphicsItem can provide means to interact with them and via
 * them with the Fib object.
 *
 * @see cFibObjectMainWindow
 * @see QGraphicsScene
 * @see cFibGraphicsItem
 * @see QGraphicsItem
 * @see QGraphicsView
 * @pattern Factory Method
 * @see iFibGraphicsItemFactory
 * @see cFibGraphicsItemImageFactory
 */
/*
History:
18.07.2013  Oesterholz  created
25.01.2013  Oesterholz  the graphical items will be updated, if possible,
	with the information of the Fib node change event
13.04.2014  Oesterholz  mousePressEvent() insert selected Fib object
*/


//TODO switches for test proposes
#define DEBUG


#include "cFibGraphicsScene.h"

#include "cFibElement.h"
#include "cFibVariable.h"
#include "cDomain.h"
#include "cDomains.h"
#include "cDomain.h"
#include "cDomainSingle.h"
#include "cDomainIntegerBasis.h"
#include "cDomainVectorBasis.h"
#include "cTypeDimension.h"
#include "cTypeProperty.h"

#include "cFibObjectMainWindow.h"
#include "nFibObjectTools.h"
#include "cFibGraphicsItemImageFactory.h"
#include "cFibNode.h"
#include "cFibNodeHandler.h"
#include "eFibNodeChangedEvent.h"
#include "cFibGraphicsItem.h"
#include "cWidgetFibInputVariables.h"
#include "cEvalueSimpleRGBA255QPainter.h"
#include "cFibCreatorStatiHandler.h"

#include <QPainter>
#include <QPen>
#include <QBrush>


using namespace fib::nCreator;
using namespace fib;


/**
 * parameter constructor for a graphics view of a Fib object
 *
 * @param pInFibNode a pointer to the Fib node object for the widget to construct
 * 	@see pFibNode
 * @param pParent a pointer to parent of this widget
 */
cFibGraphicsScene::cFibGraphicsScene( cFibNode * pInFibNode, QWidget * pParent ):
		QGraphicsScene( pParent ), pFibNode( NULL ),
		ulFibNodeVersionDisplayed( 0 ), pWidgetFibInputVariables( NULL ),
		pMainWindow( NULL ), pEvalueSimpleRGBA255QPainter( NULL ),
		pFibRootNode( NULL ),
		dPointWidth( 1.0 ), dPointHeight( 1.0 ),
		dDirection1Minimum( 0.0 ), dDirection1Maximum( 0.0 ),
		dDirection2Minimum( 0.0 ), dDirection2Maximum( 0.0 ) {
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::cFibGraphicsScene( pInFibNode="<<pInFibNode<<", pParent="<<pParent<<" ) called"<<endl<<flush);
	
	connect( this, SIGNAL(signalEvalueInputVariable()),
		this, SLOT(evalueInputVariables()) );
	connect( this, SIGNAL(signalEvalueGraphicsItemsFromFibNode()),
		this, SLOT(evalueGraphicsItemsFromFibNode()) );
	
	setFibObjectNode( pInFibNode );
}


/**
 * parameter constructor for a graphics view of a Fib object
 *
 * @param pInFibNode a pointer to the Fib node object for the widget to construct
 * 	@see pFibNode
 * @param pInMainWindow a pointer to the main window for this widget
 * 	@see pMainWindow
 */
cFibGraphicsScene::cFibGraphicsScene( cFibNode * pInFibNode,
		cFibObjectMainWindow * pInMainWindow ):
		QGraphicsScene( pInMainWindow ), pFibNode( NULL ),
		ulFibNodeVersionDisplayed( 0 ), pWidgetFibInputVariables( NULL ),
		pMainWindow( pInMainWindow ), pEvalueSimpleRGBA255QPainter( NULL ),
		pFibRootNode( NULL ), dPointWidth( 1.0 ), dPointHeight( 1.0 ),
		dDirection1Minimum( 0.0 ), dDirection1Maximum( 0.0 ),
		dDirection2Minimum( 0.0 ), dDirection2Maximum( 0.0 ) {
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::cFibGraphicsScene( pInFibNode="<<pInFibNode<<", pInMainWindow="<<pInMainWindow<<" ) called"<<endl<<flush);
	
	connect( this, SIGNAL(signalEvalueInputVariable()),
		this, SLOT(evalueInputVariables()) );
	connect( this, SIGNAL(signalEvalueGraphicsItemsFromFibNode()),
		this, SLOT(evalueGraphicsItemsFromFibNode()) );
	
	setFibObjectNode( pInFibNode );
}

/**
 * A parameter constructor for a graphics view of a Fib object
 *
 * @param pInFibObject a pointer to the Fib object for the widget to
 * 	construct, the node for it will be used as the Fib node for this
 * 	Fib graphic scene; use this constructor if you need a listener for
 * 	node changes (this object will be added as a listener)
 * 	@see pFibNode
 * 	@see cFibNodeHandler::getNodeForFibObject()
 * @param pParent a pointer to parent of this widget
 */
cFibGraphicsScene::cFibGraphicsScene( cFibElement * pInFibObject,
			QWidget * pParent ):
		QGraphicsScene( pParent ), pFibNode( NULL ),
		ulFibNodeVersionDisplayed( 0 ), pWidgetFibInputVariables( NULL ),
		pMainWindow( NULL ), pEvalueSimpleRGBA255QPainter( NULL ),
		pFibRootNode( NULL ),
		dPointWidth( 1.0 ), dPointHeight( 1.0 ),
		dDirection1Minimum( 0.0 ), dDirection1Maximum( 0.0 ),
		dDirection2Minimum( 0.0 ), dDirection2Maximum( 0.0 ) {
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::cFibGraphicsScene( pInFibNode="<<pInFibObject<<", pParent="<<pParent<<" ) called"<<endl<<flush);
	
	connect( this, SIGNAL(signalEvalueInputVariable()),
		this, SLOT(evalueInputVariables()) );
	connect( this, SIGNAL(signalEvalueGraphicsItemsFromFibNode()),
		this, SLOT(evalueGraphicsItemsFromFibNode()) );
	
	cFibNode * pInFibNode = cFibNodeHandler::getInstance()->
		getNodeForFibObject( pInFibObject, this );
	setFibObjectNode( pInFibNode );
}



/**
 * destructor
 */
cFibGraphicsScene::~cFibGraphicsScene() {
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::~cFibGraphicsScene() called"<<endl<<flush);
	
	if ( pFibNode ) {
		pFibNode->unregisterNodeChangeListener( this );
	}
	if ( pFibRootNode ) {
		pFibRootNode->unregisterNodeChangeListener( this );
	}
	if ( pWidgetFibInputVariables ) {
		//delete the widget for the input variables
		pWidgetFibInputVariables->deleteLater();
	}
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::~cFibGraphicsScene() done"<<endl<<flush);
}



/**
 * @return a pointer to the Fib node object this widget shows / represents
 * 	@see pFibNode
 */
cFibNode * cFibGraphicsScene::getFibNode() {
	
	return pFibNode;
}


/**
 * @return a const pointer to the Fib node object this widget shows / represents
 * 	@see pFibNode
 */
const cFibNode * cFibGraphicsScene::getFibNode() const {
	
	return pFibNode;
}


/**
 * This method will set the given Fib (node) object in this widget.
 * Beware: If the Fib (node) object was set (returned true) the Fib node
 * 	handler will handel the given Fib object (e. g. It will delete the
 * 	Fib object, so don't delete it yourself).
 * @see cFibNodeHandler
 *
 * @param pNewFibObject a pointer to the Fib object to set for this widget
 * @return true if the given Fib object was set, else false
 */
bool cFibGraphicsScene::setFibObjectNode( cFibNode * pNewFibObjectNode ) {
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::setFibObjectNode( pNewFibObjectNode="<<pNewFibObjectNode<<") called"<<endl<<flush);
	
	if ( pNewFibObjectNode == NULL ) {
		
		return false;
	}
	bool bReturnValue = true;
	
	if ( pFibNode ) {
		pFibNode->unregisterNodeChangeListener( this );
	}
	pFibNode = pNewFibObjectNode;
	pFibNode->registerNodeChangeListener( this );
	
	//set pFibRootNode
	if ( pFibRootNode ) {
		pFibRootNode->unregisterNodeChangeListener( this );
	}
	pFibRootNode = cFibNodeHandler::getInstance()->
		 getNodeForFibObject( pFibNode->getMasterRoot(), this );
	pFibRootNode->registerNodeChangeListener( this );
	//update pEvalueSimpleRGBA255QPainter
	updateEvalueFibObjectForPainter();
	updateForDimensionChange();
	
	bReturnValue &= evalueInputVariables();
	bReturnValue &= evalueGraphicsItemsFromFibNode();
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::setFibObjectNode( pNewFibObjectNode="<<pNewFibObjectNode<<") done"<<endl<<flush);
	return bReturnValue;
}


/**
 * Event method
 * It will be called every time a Fib node (cFibNode), at which
 * this object is registered, was changed.
 *
 * @param pFibNode a pointer to the changed Fib node
 */
void cFibGraphicsScene::fibNodeChangedEvent(
		const eFibNodeChangedEvent * pFibNodeChanged ) {
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<") called"<<endl<<flush);
	
	const cFibNode * pChangedNode = pFibNodeChanged->getChangedNode();
	if ( ( pFibNodeChanged == NULL ) || ( pChangedNode == NULL ) ) {
		//nothing changed
		return;
	}
	if ( pFibNodeChanged->isDeleted() && ( pChangedNode == pFibNode ) ) {
		/*node of this graphic scene deleted
		 *-> set NULL as this this graphic scene node*/
		pFibNode = NULL;
		//update pEvalueSimpleRGBA255QPainter
		updateEvalueFibObjectForPainter();
		updateForDimensionChange();
		
		emit signalEvalueInputVariable();
		emit signalEvalueGraphicsItemsFromFibNode();
		
		DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<") done node deleted"<<endl<<flush);
		return;
	}//else this graphic scene node was not deleted

	if ( pFibNodeChanged->getChangeBy() == this ) {
		//nothing changed
		DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<") done nothing changed"<<endl<<flush);
		return;
	}
	//check if the event is for pFibRootNode
	if ( pFibRootNode != pFibNode ) {
		//this graphical scene is not for the root node of the Fib object
		if ( pChangedNode == pFibRootNode ) {
			/*the Fib master root object was changed (there should be an
			 *extra event if the node for this graphical scene changes,
			 *so just update the dimensions in this event call)*/
			updateEvalueFibObjectForPainter();
			updateForDimensionChange();
			
			update();
			DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<") done the Fib master root object was changed"<<endl<<flush);
			return;
		}
		if ( ( pChangedNode != pFibNode ) ||
				( pChangedNode->getFibObjectVersion() == ulFibNodeVersionDisplayed ) ) {
			//nothing changed for the Fib node of this graphical scene
			DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<") done the Fib master root object nothing changed"<<endl<<flush);
			return;
		}
	}else{//the Fib node and Fib root node for this graphical scene are the same
		if ( ( pChangedNode != pFibNode ) ||
				( pChangedNode->getFibObjectVersion() == ulFibNodeVersionDisplayed ) ) {
			//nothing changed for the Fib node of this graphical scene
			return;
		}
		//the Fib master root object was changed
		updateEvalueFibObjectForPainter();
		updateForDimensionChange();
	}
	
	emit signalEvalueInputVariable();
	
	//try to update the Fib graphic items
	cFibGraphicsItemImageFactory fibGraphicsItemImageFactory(
		ulFibNodeVersionDisplayed, this );
	
	//for all sub graphic items
	//TODO not all items, but top level items (add deleteObject() for items)
	bool bAllUpdated = true;
	//lock Fib node to create the Fib graphic items
	cFibNodeHandler * pFibNodeHandler = cFibNodeHandler::getInstance();
	if ( pFibNodeHandler ) {
		pFibNodeHandler->lock( pChangedNode );
		if ( ! pFibNodeHandler->isValidNode( pChangedNode ) ) {
			//can't update for not valid node
			pFibNodeHandler->unlock( pChangedNode );
			emit signalEvalueGraphicsItemsFromFibNode();
			return;
		}
	}
	mutexFibParts.lock();
	const cFibElement * pUpdateForFibObject = pFibNode->getFibObject();
	for ( QList< cFibGraphicsItem * >::iterator
			itrActualItem = liFibParts.begin();
			itrActualItem != liFibParts.end(); itrActualItem++ ) {
		
		DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<") update Fib graphic item "<<(*itrActualItem)<<" with type "<<(*itrActualItem)->type()<<" ("<<((*itrActualItem)->type() - (QGraphicsItem::UserType + 1024) )<<")"<<endl<<flush);
		if ( ! (*itrActualItem)->updateForFibNodeChange( pFibNodeChanged,
					&fibGraphicsItemImageFactory, pUpdateForFibObject ) ) {
			//the Fib graphic item could not be updated -> update them (/all)
			DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<") the Fib graphic item "<<(*itrActualItem)<<" could not be updated"<<endl<<flush);
			bAllUpdated = false;
			break;//done, all updated
		}
	}
	mutexFibParts.unlock();
	if ( pFibNodeHandler ) {
		pFibNodeHandler->unlock( pChangedNode );
	}
	if ( ! bAllUpdated ) {
		//recreate all graphic items
		DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<") recreate all graphic items ( signalEvalueGraphicsItemsFromFibNode() )"<<endl<<flush);
		emit signalEvalueGraphicsItemsFromFibNode();
	}
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<") done"<<endl<<flush);
}


/**
 * This method will return the number of input variables for the Fib
 * object for the Fib node.
 *
 * @see pFibNode
 * @see pWidgetFibInputVariables
 * @see evalueInputVariables()
 * @see getInputVariablesWidget()
 * @return the number of input variables for the Fib object for the Fib node
 */
unsigned int cFibGraphicsScene::getNumberOfInputVariables() const {
	
	mutexFibParts.lock();
	const unsigned int ulInputVariables = ( pWidgetFibInputVariables != NULL) ?
		pWidgetFibInputVariables->getNumberOfInputVariables() : 0;
	mutexFibParts.unlock();
	
	return ulInputVariables;
}


/**
 * This method sets the input variable widgets.
 *
 * @see pFibNode
 * @see pWidgetFibInputVariables
 * @see evalueInputVariables()
 * @see getNumberOfInputVariables()
 * @param pWidgetFibInputVariables a pointer to the widget with the
 * 	input variables to set
 * 	Beware: This object will handle the given widget object (e.g. it will delete it).
 */
void cFibGraphicsScene::setInputVariablesWidget(
		cWidgetFibInputVariables * pNewWidgetFibInputVariables ) {
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::setInputVariablesWidget( pNewWidgetFibInputVariables="<<pNewWidgetFibInputVariables<<") called"<<endl<<flush);
	if ( pNewWidgetFibInputVariables == pWidgetFibInputVariables ) {
		//input variables already set
		DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::setInputVariablesWidget( pNewWidgetFibInputVariables="<<pNewWidgetFibInputVariables<<") done input variables already set"<<endl<<flush);
		return;
	}
	
	//if NULL unset old widget
	if ( pMainWindow ) {
		//set new widget in main Fib object window
		pMainWindow->setInputVariablesWidgetForCentralGrapical(
			pNewWidgetFibInputVariables );
	}
	cWidgetFibInputVariables * pOldWidgetFibInputVariables =
		pWidgetFibInputVariables;
		
	pWidgetFibInputVariables = pNewWidgetFibInputVariables;
	
	if ( pOldWidgetFibInputVariables ) {
		DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::setInputVariablesWidget( pNewWidgetFibInputVariables="<<pNewWidgetFibInputVariables<<") delete old input variables ("<<pOldWidgetFibInputVariables<<")"<<endl<<flush);
		pOldWidgetFibInputVariables->deleteLater();
	}
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::setInputVariablesWidget( pNewWidgetFibInputVariables="<<pNewWidgetFibInputVariables<<") done"<<endl<<flush);
}


/**
 * @see pFibNode
 * @see pWidgetFibInputVariables
 * @see evalueInputVariables()
 * @see getNumberOfInputVariables()
 * @return a pointer to the widget with the input variables
 */
cWidgetFibInputVariables * cFibGraphicsScene::getInputVariablesWidget() {
	
	return pWidgetFibInputVariables;
}


/**
 * @see pFibNode
 * @see pWidgetFibInputVariables
 * @see evalueInputVariables()
 * @see getNumberOfInputVariables()
 * @return a pointer to the widget with the input variables
 */
const cWidgetFibInputVariables * cFibGraphicsScene::getInputVariablesWidget() const {
	
	return pWidgetFibInputVariables;
}


/**
 * @return the name of this class "cFibGraphicsScene"
 */
std::string cFibGraphicsScene::getName() const {
	
	return std::string( "cFibGraphicsScene" );
}


/**
 * This method evalue the input variables for the Fib object for the
 * Fib node.
 * It will evalue all variables used in the Fib object, but not defined
 * in it.
 * New input variables will be set to the default value 0 .
 *
 * @see pFibNode
 * @see pWidgetFibInputVariables
 * @see getNumberOfInputVariables()
 * @see getInputVariablesWidget()
 * @return true if the input variables for the Fib object for the node
 * 	could be set, else false (and no input variables set)
 */
bool cFibGraphicsScene::evalueInputVariables() {
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::evalueInputVariables() called"<<endl<<flush);
	
	if ( ( pFibNode == NULL ) || ( pFibNode->getFibObject() == NULL ) ) {
		//no Fib object -> no input variables
		DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::evalueInputVariables() done no Fib objects"<<endl<<flush);
		
		mutexFibParts.lock();
		setInputVariablesWidget( NULL );
		mutexFibParts.unlock();
		return false;
	}
	cFibNodeHandler * pFibNodeHandler = cFibNodeHandler::getInstance();
	
	DEBUG_OUT_L3(<<"cFibGraphicsScene("<<this<<")::evalueInputVariables() lock node "<<pFibNode<<" mutex"<<endl<<flush);
	pFibNodeHandler->lock( pFibNode );
	DEBUG_OUT_L3(<<"cFibGraphicsScene("<<this<<")::evalueInputVariables() Fib parts mutex lock"<<endl<<flush);
	mutexFibParts.lock();
	//evalue the input variables of the Fib object
	DEBUG_OUT_L3(<<"cFibGraphicsScene("<<this<<")::evalueInputVariables() evalue the input variables of the Fib object"<<endl<<flush);
	
	cWidgetFibInputVariables * pNewWidgetFibInputVariables =
		new cWidgetFibInputVariables( pFibNode->getFibObject(), true );
	
	if ( pNewWidgetFibInputVariables->getNumberOfInputVariables() == 0 ) {
		//no input variables -> input variables widget not needed -> delete it
		DEBUG_OUT_L3(<<"cFibGraphicsScene("<<this<<")::evalueInputVariables() no input variables -> input variables widget not needed -> delete it"<<endl<<flush);
		delete pNewWidgetFibInputVariables;
		pNewWidgetFibInputVariables = NULL;
	}
	
	mutexFibParts.unlock();
	pFibNodeHandler->unlock( pFibNode );
	
	setInputVariablesWidget( pNewWidgetFibInputVariables );
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::evalueInputVariables() done"<<endl<<flush);
	return true;
}


/**
 * @return a hint for a good size of this widget
 */
QSize cFibGraphicsScene::sizeHint() const {
	
	return QSize( 640, 480 );
}


/**
 * This method will evalue the grapical items for the Fib object of this
 * scene and include them in this grapical scene.
 * At the end this graphical scene will display the Fib object.
 *
 * @see QList <QGraphicsItem *> QGraphicsScene::items()
 * @see liFibParts
 * @see iFibGraphicsItemFactory
 * @see cFibGraphicsItemImageFactory
 * @see cFibGraphicsItem
 * @return true if the Fib object was displayed, else false
 */
bool cFibGraphicsScene::evalueGraphicsItemsFromFibNode() {
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::evalueGraphicsItemsFromFibNode() called"<<endl<<flush);
	
	//remove old items
	mutexFibParts.lock();
	
	DEBUG_OUT_L3(<<"cFibGraphicsScene("<<this<<")::evalueGraphicsItemsFromFibNode() deleting "<<items().size()<<" old items"<<endl<<flush);
	for ( QList< cFibGraphicsItem * >::iterator
			itrActualItem = liFibParts.begin();
			itrActualItem != liFibParts.end(); itrActualItem++ ) {
		//delete the old item (and all its childs and remove from this graphical scene)
		delete *itrActualItem;
	}
	liFibParts.clear();
	//TODO add item for the Fib image size borders (dDirection1Minimum, ...)
	
	//set the input variables to there values, to create the graphics items
	DEBUG_OUT_L3(<<"cFibGraphicsScene("<<this<<")::evalueGraphicsItemsFromFibNode() set the input variables to there values, to create the graphics items"<<endl<<flush);
	if ( pWidgetFibInputVariables ) {
		pWidgetFibInputVariables->assignValues();
	}
	
	if ( ( pFibNode == NULL ) || ( pFibNode->getFibObject() == NULL ) ) {
		//no Fib object -> nothing to show
		//update this grapic scene
		mutexFibParts.unlock();
		update();
		
		return false;
	}
	
	
	//create the graphics items
	cFibGraphicsItemImageFactory fibGraphicsItemImageFactory(
		ulFibNodeVersionDisplayed, this );
	//lock Fib node to create the Fib graphic items
	cFibNodeHandler * pFibNodeHandler = cFibNodeHandler::getInstance();
	if ( pFibNodeHandler ) {
		pFibNodeHandler->lock( pFibNode );
		if ( ! pFibNodeHandler->isValidNode( pFibNode ) ) {
			//can't update for not valid node
			pFibNodeHandler->unlock( pFibNode );
			mutexFibParts.unlock();
			update();
			return false;
		}
	}
	cFibGraphicsItem * pFibGraphicsItem =
		fibGraphicsItemImageFactory( pFibNode->getFibObject() );
	if ( pFibNodeHandler ) {
		pFibNodeHandler->unlock( pFibNode );
	}
	
	if ( pFibGraphicsItem ) {
		addItem( pFibGraphicsItem );
		liFibParts.push_back( pFibGraphicsItem );
	}
	mutexFibParts.unlock();
	//update this grapic scene
	update();
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::evalueGraphicsItemsFromFibNode() done (#items "<<items().size()<<")"<<endl<<flush);
	return true;
}


/**
 * This method sets the input variables to there values, so that the
 * Fib object can be evalued.
 * @see pWidgetFibInputVariables
 */
void cFibGraphicsScene::setInputVariables() {
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::setInputVariables() called"<<endl<<flush);
	mutexFibParts.lock();
	if ( pWidgetFibInputVariables ) {
		pWidgetFibInputVariables->assignValues();
	}
	mutexFibParts.unlock();
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::setInputVariables() done"<<endl<<flush);
}


/**
 * This slot will notify the Fib node that it was changed, if the scene
 * for the Fib object was changed.
 * This method should be called if the Fib object scene of this widget
 * changes. It will then try to create the Fib object of this scene.
 * If it was successfull, it will adapt / replace the Fib node
 * Fib object with the Fib object of this scene and notify the node that
 * it was changed.
 * @see fibNodeChangedEvent()
 */
void cFibGraphicsScene::notifyNodeForChange() {
	//TODO
	
	if ( pFibNode ) {
		pFibNode->fibObjectChanged( this );
	}
	return;
}


/**
 * This slot will notify the Fib node that it was changed, if the scene
 * for the Fib object was changed.
 * This method should be called if the Fib object scene of this widget
 * changes. It will then try to create the Fib object of this scene.
 * If it was successfull, it will adapt / replace the Fib node
 * Fib object with the Fib object of this scene and notify the node that
 * it was changed.
 * @see fibNodeChangedEvent()
 *
 * @param fibNodeChangedEvent the information for the change event
 */
void cFibGraphicsScene::notifyNodeForChange(
		const eFibNodeChangedEvent & fibNodeChangedEvent ) {
	//TODO
	
	if ( pFibNode ) {
		pFibNode->fibObjectChanged( fibNodeChangedEvent );
	}
	return;
}


/**
 * This method will update evalue Fib object with painter object
 * pEvalueSimpleRGBA255QPainter.
 *
 * @see pEvalueSimpleRGBA255QPainter
 * @see dPointWidth
 * @see dPointHeight
 * @see pFibNode
 * @return true if the evalue Fib object with painter object
 * 	pEvalueSimpleRGBA255QPainter was changed, else false
 */
bool cFibGraphicsScene::updateEvalueFibObjectForPainter() {
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() called"<<endl<<flush);
	//update pEvalueSimpleRGBA255QPainter
	if ( pFibNode == NULL ) {
		//no Fib object with domains
		DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() done no Fib object with domains"<<endl<<flush);
		return false;
	}
	
	cFibNodeHandler * pFibNodeHandler = cFibNodeHandler::getInstance();
	
	DEBUG_OUT_L3(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() node "<<pFibNode<<" lock"<<endl<<flush);
	pFibNodeHandler->lock( pFibNode );
	DEBUG_OUT_L3(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() Fib parts lock"<<endl<<flush);
	mutexFibParts.lock();
	cFibElement * pGraphicSceneFibObject = pFibNode->getFibObject();
	if ( pGraphicSceneFibObject == NULL ) {
		//no Fib object with domains
		pFibNodeHandler->unlock( pFibNode );
		mutexFibParts.unlock();
		return false;
	}
	if ( pEvalueSimpleRGBA255QPainter == NULL ) {
		//create a pEvalueSimpleRGBA255QPainter object
		DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() create a init pEvalueSimpleRGBA255QPainter object"<<endl<<flush);
		pEvalueSimpleRGBA255QPainter = new cEvalueSimpleRGBA255QPainter( NULL );
	}
	
//TODO do as default
#define DEFAULT_EVALUE_FIB_OBJECT

#ifdef DEFAULT_EVALUE_FIB_OBJECT
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() evaluing old values"<<endl<<flush);
	const qreal dOldScalingFactorAlpha =
		pEvalueSimpleRGBA255QPainter->getScalingFactorAlpha();
	const qreal dOldScalingFactorRed =
		pEvalueSimpleRGBA255QPainter->getScalingFactorRed();
	const qreal dOldScalingFactorGreen =
		pEvalueSimpleRGBA255QPainter->getScalingFactorGreen();
	const qreal dOldScalingFactorBlue =
		pEvalueSimpleRGBA255QPainter->getScalingFactorBlue();
	const qreal dOldScalingFactorGrayscale =
		pEvalueSimpleRGBA255QPainter->getScalingFactorGrayscale();
	
	qreal dNewScalingFactorAlpha = 1.0;
	qreal dNewScalingFactorRed   = 1.0;
	qreal dNewScalingFactorGreen = 1.0;
	qreal dNewScalingFactorBlue  = 1.0;
	qreal dNewScalingFactorGrayscale = 1.0;
	
	//TODO accepted values are betwean 0.0 and 1.0
	
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() get domains"<<endl<<flush);
	const cDomains domainsValid = pGraphicSceneFibObject->getValidDomains();
	
	pFibNodeHandler->unlock( pFibNode );
	mutexFibParts.unlock();
	
	//check if the RGB color domain where changed
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() check if the RGB color domain where changed"<<endl<<flush);
	cDomain * pDomainRGBColor = domainsValid.getDomainForElement(
		cTypeProperty( cTypeProperty::COLOR_RGB ) );
	
	if ( ( pDomainRGBColor != NULL ) &&
			( pDomainRGBColor->isVector() ) ) {
		//get RGB color scaling factors
		const cDomainVectorBasis * pVecDomainColorRgb =
			(const cDomainVectorBasis*)pDomainRGBColor;
		
		//get red scaling factor
		const cDomainSingle * pColorRedDomain   = (cDomainSingle*)(
			pVecDomainColorRgb->getElementDomain( 1 ) );
		
		dNewScalingFactorRed = 1.0 / pColorRedDomain->getMaximum();
		
		//get green scaling factor
		const cDomainSingle * pColorGreenDomain = (cDomainSingle*)(
			pVecDomainColorRgb->getElementDomain( 1 ) );
		
		dNewScalingFactorGreen = 1.0 / pColorGreenDomain->getMaximum();
		
		//get blue scaling factor
		const cDomainSingle * pColorBlueDomain = (cDomainSingle*)(
			pVecDomainColorRgb)->getElementDomain( 1 );
		
		dNewScalingFactorBlue = 1.0 / pColorBlueDomain->getMaximum();
	}
	
	//check if the grayscale color domain where changed
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() check if the grayscale color domain where changed"<<endl<<flush);
	cDomain * pDomainGrayscaleNew = domainsValid.getDomainForElement(
		cTypeProperty( cTypeProperty::COLOR_GRAYSCALE ) );
	
	if ( pDomainGrayscaleNew ) {
		//get new grayscale color scaling factor
		dNewScalingFactorGrayscale = 1.0 /
			((cDomainSingle*)(pDomainGrayscaleNew))->getMaximum();
	}
	//check if the transparency domain where changed
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() check if the transparency domain where changed"<<endl<<flush);
	cDomain * pDomainTransparencyNew = domainsValid.getDomainForElement(
		cTypeProperty( cTypeProperty::TRANSPARENCY ) );
	
	if ( pDomainTransparencyNew ) {
		//get new transparency scaling factor
		dNewScalingFactorAlpha = 1.0 /
			((cDomainSingle*)(pDomainTransparencyNew))->getMaximum();
	}
	
	
	//if a scaling factor was changed -> update pEvalueSimpleRGBA255QPainter
	if ( ( dOldScalingFactorAlpha != dNewScalingFactorAlpha ) ||
			( dOldScalingFactorRed != dNewScalingFactorRed ) ||
			( dOldScalingFactorGreen != dNewScalingFactorGreen ) ||
			( dOldScalingFactorBlue != dNewScalingFactorBlue ) ||
			( dOldScalingFactorGrayscale != dNewScalingFactorGrayscale ) ) {
		
		DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() new pEvalueSimpleRGBA255QPainter(NULL, dNewScalingFactorAlpha="<<dNewScalingFactorAlpha<<", dNewScalingFactorRed="<<dNewScalingFactorRed<<", dNewScalingFactorGreen="<<dNewScalingFactorGreen<<", dNewScalingFactorBlue="<<dNewScalingFactorBlue<<", dNewScalingFactorGrayscale="<<dNewScalingFactorGrayscale<<" )"<<endl<<flush);
	
		delete pEvalueSimpleRGBA255QPainter;
		pEvalueSimpleRGBA255QPainter = new cEvalueSimpleRGBA255QPainter( NULL,
			dDirection2Maximum,
			dNewScalingFactorAlpha, dNewScalingFactorRed,
			dNewScalingFactorGreen, dNewScalingFactorBlue,
			dNewScalingFactorGrayscale );
		return true;
	}
	
#else //DEFAULT_EVALUE_FIB_OBJECT

	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() evaluing old values"<<endl<<flush);
	const qreal dOldScalingFactorAlpha =
		pEvalueSimpleRGBA255QPainter->getScalingFactorAlpha();
	const qreal dOldScalingFactorRed =
		pEvalueSimpleRGBA255QPainter->getScalingFactorRed();
	const qreal dOldScalingFactorGreen =
		pEvalueSimpleRGBA255QPainter->getScalingFactorGreen();
	const qreal dOldScalingFactorBlue =
		pEvalueSimpleRGBA255QPainter->getScalingFactorBlue();
	const qreal dOldScalingFactorGrayscale =
		pEvalueSimpleRGBA255QPainter->getScalingFactorGrayscale();
	
	qreal dNewScalingFactorAlpha = 1.0;
	qreal dNewScalingFactorRed   = 1.0;
	qreal dNewScalingFactorGreen = 1.0;
	qreal dNewScalingFactorBlue  = 1.0;
	qreal dNewScalingFactorGrayscale = 1.0;
	
	//TODO accepted values are betwean 0.0 and 1.0
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() get domains"<<endl<<flush);
	const cDomains domainsValid = pGraphicSceneFibObject->getValidDomains();
	
	pFibNodeHandler->unlock( pFibNode );
	mutexFibParts.unlock();
	
	//check if the RGB color domain where changed
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() check if the RGB color domain where changed"<<endl<<flush);
	cDomain * pDomainRGBColor = domainsValid.getDomainForElement(
		cTypeProperty( cTypeProperty::COLOR_RGB ) );
	
	if ( ( pDomainRGBColor != NULL ) &&
			( pDomainRGBColor->isVector() ) ) {
		//get RGB color scaling factors
		const cDomainVectorBasis * pVecDomainColorRgb =
			(const cDomainVectorBasis*)pDomainRGBColor;
		//get red scaling factor
		const cDomainSingle * pColorRedDomain   = (cDomainSingle*)(
			pVecDomainColorRgb->getElementDomain( 1 ) );
		
		const string szDomainElementTypeRed = pColorRedDomain->getType();
		if ( ( szDomainElementTypeRed.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
					(szDomainElementTypeRed.compare( 0, 13, "DomainInteger" ) == 0) ) {
			//cDomainIntegerBasis
			dNewScalingFactorRed =
				((cDomainIntegerBasis*)pColorRedDomain)->getScalingFactor();
		}
		//get green scaling factor
		const cDomainSingle * pColorGreenDomain = (cDomainSingle*)(
			pVecDomainColorRgb->getElementDomain( 2 ) );
		
		const string szDomainElementTypeGreen = pColorGreenDomain->getType();
		if ( ( szDomainElementTypeGreen.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
					(szDomainElementTypeGreen.compare( 0, 13, "DomainInteger" ) == 0) ) {
			//cDomainIntegerBasis
			dNewScalingFactorGreen =
				((cDomainIntegerBasis*)pColorGreenDomain)->getScalingFactor();
		}
		//get blue scaling factor
		const cDomainSingle * pColorBlueDomain  = (cDomainSingle*)(
			pVecDomainColorRgb->getElementDomain( 3 ) );
		
		const string szDomainElementTypeBlue = pColorBlueDomain->getType();
		if ( ( szDomainElementTypeBlue.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
					(szDomainElementTypeBlue.compare( 0, 13, "DomainInteger" ) == 0) ) {
			//cDomainIntegerBasis
			dNewScalingFactorBlue =
				((cDomainIntegerBasis*)pColorBlueDomain)->getScalingFactor();
		}
	}
	
	//check if the grayscale color domain where changed
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() check if the grayscale color domain where changed"<<endl<<flush);
	cDomain * pDomainGrayscaleNew = domainsValid.getDomainForElement(
		cTypeProperty( cTypeProperty::COLOR_GRAYSCALE ) );
	
	if ( pDomainGrayscaleNew ) {
		const string szDomainElementTypeGrayscale = pDomainGrayscaleNew->getType();
		if ( ( szDomainElementTypeGrayscale.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
					(szDomainElementTypeGrayscale.compare( 0, 13, "DomainInteger" ) == 0) ) {
			//get new grayscale color scaling factor
			dNewScalingFactorGrayscale =
				((cDomainIntegerBasis*)pDomainGrayscaleNew)->getScalingFactor();
		}
	}
	//check if the transparency domain where changed
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() check if the transparency domain where changed"<<endl<<flush);
	cDomain * pDomainTransparencyNew = domainsValid.getDomainForElement(
		cTypeProperty( cTypeProperty::TRANSPARENCY ) );
	
	if ( pDomainTransparencyNew ) {
		const string szDomainElementTypeTransparency = pDomainTransparencyNew->getType();
		if ( ( szDomainElementTypeTransparency.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
					(szDomainElementTypeTransparency.compare( 0, 13, "DomainInteger" ) == 0) ) {
			//get new transparency scaling factor
			dNewScalingFactorAlpha =
				((cDomainIntegerBasis*)pDomainTransparencyNew)->getScalingFactor();
		}
	}
	
	
	//if a scaling factor was changed -> update pEvalueSimpleRGBA255QPainter
	if ( ( dOldScalingFactorAlpha != dNewScalingFactorAlpha ) ||
			( dOldScalingFactorRed != dNewScalingFactorRed ) ||
			( dOldScalingFactorGreen != dNewScalingFactorGreen ) ||
			( dOldScalingFactorBlue != dNewScalingFactorBlue ) ||
			( dOldScalingFactorGrayscale != dNewScalingFactorGrayscale ) ) {
		
		DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() new pEvalueSimpleRGBA255QPainter(NULL, dNewScalingFactorAlpha="<<dNewScalingFactorAlpha<<", dNewScalingFactorRed="<<dNewScalingFactorRed<<", dNewScalingFactorGreen="<<dNewScalingFactorGreen<<", dNewScalingFactorBlue="<<dNewScalingFactorBlue<<", dNewScalingFactorGrayscale="<<dNewScalingFactorGrayscale<<" )"<<endl<<flush);
	
		delete pEvalueSimpleRGBA255QPainter;
		pEvalueSimpleRGBA255QPainter = new cEvalueSimpleRGBA255QPainter( NULL,
			dNewScalingFactorAlpha, dNewScalingFactorRed,
			dNewScalingFactorGreen, dNewScalingFactorBlue,
			dNewScalingFactorGrayscale );
		return true;
	}
#endif //DEFAULT_EVALUE_FIB_OBJECT
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() done"<<endl<<flush);
	return true;
}


/**
 * This method will change the values of this graphics view according the
 * dimension domain of the displayed Fib object.
 * This method will update the point size for a point of the displayed
 * Fib object. If you call setPenForPointSize() the pen will be set to the
 * evalued point size.
 * It will also update the image borders.
 *
 * @see dPointWidth
 * @see dPointHeight
 * @see dDirection1Minimum
 * @see dDirection1Maximum
 * @see dDirection2Minimum
 * @see dDirection2Maximum
 * @see setPenForPointSize()
 * @return true if the dimensions for the Fib object could be evaluated,
 * 	else false
 */
bool cFibGraphicsScene::updateForDimensionChange() {

	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateForDimensionChange() called"<<endl<<flush);
	//update pEvalueSimpleRGBA255QPainter
	if ( pFibNode == NULL ) {
		//no Fib object with domains -> set dimension to 0 and point size to 1
		dPointWidth  = 1.0;
		dPointHeight = 1.0;
		dDirection1Minimum = 0.0;
		dDirection1Maximum = 0.0;
		dDirection2Minimum = 0.0;
		dDirection2Maximum = 0.0;
		
		DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateForDimensionChange() done no Fib object: dPointWidth="<<dPointWidth<<"  dPointHeight="<<dPointHeight<<"  dimension 1 min="<<dDirection1Minimum<<" max="<<dDirection1Maximum<<"  dimension 2 min="<<dDirection2Minimum<<" max="<<dDirection2Maximum<<""<<endl<<flush);
		return false;
	}
	
	cFibElement * pGraphicSceneFibObject = pFibNode->getFibObject();
	if ( pGraphicSceneFibObject == NULL ) {
		//no Fib object with domains
		return false;
	}
	
	cDomain * pDomainDimension = pGraphicSceneFibObject->
		getValidDomains().getDomainForElement( cTypeDimension() );
	
	if ( pDomainDimension == NULL ) {
		DEBUG_OUT_EL1( <<"Error: No dimension domain."<<endl; );
		return false;
	}
	cDomainVectorBasis * pVecDomainDimension = (cDomainVectorBasis*)pDomainDimension;
	
	if ( pVecDomainDimension->getNumberOfElements() != 2 ) {
		DEBUG_OUT_EL1( <<"Error: No 2 dimensional dimension domain in Fib object."<<endl; );
		return false;
	}
	if ( ( ! pVecDomainDimension->getElementDomain( 1 )->isScalar() ) ||
			( ! pVecDomainDimension->getElementDomain( 2 )->isScalar() ) ) {
		DEBUG_OUT_EL1( <<"Error: A dimension subdomain in the Fib object is not a scalar."<<endl; );
		return false;
	}
	//TODO implement if directions (horizontal, vertical) are switched + also switch in cEvalueSimpleRGBA255QPainter
	
	cDomainSingle * pDirection1Domain = (cDomainSingle*)(
		pVecDomainDimension->getElementDomain( 1 ) );
	cDomainSingle * pDirection2Domain = (cDomainSingle*)(
		pVecDomainDimension->getElementDomain( 2 ) );
	//evalue the values for direction 1
	dDirection1Minimum = pDirection1Domain->getMinimum();
	dDirection1Maximum = pDirection1Domain->getMaximum();
	dPointWidth = 1.0;
	const string szDomainElementTypeDim1 = pDirection1Domain->getType();
	if ( ( szDomainElementTypeDim1.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
			( szDomainElementTypeDim1.compare( 0, 13, "DomainInteger" ) == 0 ) ) {
		//cDomainIntegerBasis
		dPointWidth = ((cDomainIntegerBasis*)pDirection1Domain)->getScalingFactor();
	}
	//check if the painter should be updated
	if ( ( pEvalueSimpleRGBA255QPainter != NULL ) &&
			( dDirection2Maximum != pDirection2Domain->getMaximum() ) ) {
		//height changed -> update painter
		pEvalueSimpleRGBA255QPainter->setHeight(
			pDirection2Domain->getMaximum() );
	}
	//evalue the values for direction 2
	dDirection2Minimum = pDirection2Domain->getMinimum();
	dDirection2Maximum = pDirection2Domain->getMaximum();
	
	
	dPointHeight = 1.0;
	const string szDomainElementTypeDim2 = pDirection2Domain->getType();
	if ( ( szDomainElementTypeDim2.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
			( szDomainElementTypeDim2.compare( 0, 13, "DomainInteger" ) == 0 ) ) {
		//cDomainIntegerBasis
		dPointHeight = ((cDomainIntegerBasis*)pDirection2Domain)->getScalingFactor();
	}
	//set the scene rectangle
	setSceneRect( dDirection1Minimum, dDirection2Minimum,
		dDirection1Maximum - dDirection1Minimum,
		dDirection2Maximum - dDirection2Minimum );
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateForDimensionChange() done dPointWidth="<<dPointWidth<<"  dPointHeight="<<dPointHeight<<"  dimension 1 min="<<dDirection1Minimum<<" max="<<dDirection1Maximum<<"  dimension 2 min="<<dDirection2Minimum<<" max="<<dDirection2Maximum<<""<<endl<<flush);
	return true;
}


/**
 * This method will return a pointer cEvalueSimpleRGBA255QPainter
 * template for this graphic scene.
 * If existing, this painter will contain the enviroment / domain
 * information to paint a Fib object into this graphic scene.
 * The object can be used with the template constructor of the
 * cEvalueSimpleRGBA255QPainter to construct a cEvalueSimpleRGBA255QPainter
 * object which has the correct enviroment parameters set and uses
 * the actual painter (QPainter) object.
 * If you use this cEvalueSimpleRGBA255QPainter template, you have still
 * to adapt the QPainter for painting (e.g. you have to set the QPainter
 * pen ( setPen() ) to the correct values (e. g. width) vor drawing points.)
 *
 * @see pEvalueSimpleRGBA255QPainter
 * @see cEvalueSimpleRGBA255QPainter( QPainter * pInPainter, const cEvalueSimpleRGBA255QPainter & evalueSimpleRGBA255 );
 * @see QPainter
 * @see pFibRootNode
 * @return return a pointer cEvalueSimpleRGBA255QPainter
 * 	template for this graphic scene, or NULL if non exists
 */
const cEvalueSimpleRGBA255QPainter *
		cFibGraphicsScene::getEvalueSimpleRGBA255QPainter() const {
	
	return pEvalueSimpleRGBA255QPainter;
}


/**
 * This method will set the pen of the given to match the pixle / point
 * dimensions of the Fib object of displayed Fib object.
 *
 * @see dPointWidth
 * @see dPointHeight
 * @see updateForDimensionChange()
 * @see pFibNode
 * @return true if the pen was set, else false
 */
bool cFibGraphicsScene::setPenForPointSize( QPainter * pPainter ) const {
	
	if ( pPainter == NULL ) {
		//no painter given -> can't set pen
		return false;
	}
	//set QPainter pen for dimension scaling
	pPainter->setPen( QPen( QBrush(), dPointWidth ) );
	
	//TODO what to do with dPointHeight
	/*
	 * 	QPainter::setPen(Qt::PenStyle style Qt::SolidLine  )
	QPainter::setPen( QPen::QPen( QBrush() , qreal width=1, Qt::PenStyle style = Qt::SolidLine, Qt::PenCapStyle cap = Qt::SquareCap, Qt::PenJoinStyle join = Qt::BevelJoin ) )
	 */
	return true;
}


/**
 * This method returns the size of a point.
 *
 * @see dPointWidth
 * @see dPointHeight
 * @see setPenForPointSize()
 * @see updateForDimensionChange()
 * @see pFibNode
 * @return the size of a point
 */
QSizeF cFibGraphicsScene::getPointSize() const {
	
	return QSizeF( dPointWidth, dPointHeight );
}


/**
 * The event handler for mouse press events.
 *
 * @see QGraphicsScene::mousePressEvent
 * @param pMouseEvent the mouse press event
 */
void cFibGraphicsScene::mousePressEvent( QGraphicsSceneMouseEvent * pMouseEvent ) {
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::mousePressEvent() started"<<endl<<flush);
	
	if ( ( cFibCreatorStatiHandler::getActualMouseMode() ==
				cFibCreatorStatiHandler::DRAWING ) &&
			( pMainWindow != NULL ) && ( pMouseEvent != NULL ) ) {
		//mouse mode is drawing -> try to draw actual selected item
		DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::mousePressEvent() mouse mode is drawin, insert object at ("<<pMouseEvent->scenePos().x()<<","<<pMouseEvent->scenePos().y()<<")"<<endl<<flush);
		pMainWindow->insertSelectedFibObject( pMouseEvent->scenePos() );
		return;
	}
	
	//can not be handeled -> call inherited mouse press event handler
	QGraphicsScene::mousePressEvent( pMouseEvent );
}






