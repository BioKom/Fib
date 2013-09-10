
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
 * @see convertToFibGraphicsItem()
 */
/*
History:
18.07.2013  Oesterholz  created
*/


//TODO switches for test proposes
#define DEBUG


#include "cFibGraphicsScene.h"

#include "cFibObjectMainWindow.h"
#include "nFibObjectTools.h"
#include "cFibGraphicsItemFibList.h"
#include "cFibGraphicsItemFibObject.h"

#include "cDomains.h"
#include "cDomain.h"
#include "cDomainSingle.h"
#include "cDomainIntegerBasis.h"
#include "cDomainVectorBasis.h"
#include "cTypeDimension.h"
#include "cTypeProperty.h"

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
		dDirection2Minimum( 0.0 ), dDirection2Maximum( 0.0 ){
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::cFibGraphicsScene( pInFibNode="<<pInFibNode<<", pParent="<<pParent<<" ) called"<<endl<<flush);
	
	evalueInputVariables();
	evalueGraphicsItemsFromFibNode();
	
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
		dDirection2Minimum( 0.0 ), dDirection2Maximum( 0.0 ){
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::cFibGraphicsScene( pInFibNode="<<pInFibNode<<", pInMainWindow="<<pInMainWindow<<" ) called"<<endl<<flush);
	
	evalueInputVariables();
	evalueGraphicsItemsFromFibNode();
	
	setFibObjectNode( pInFibNode );
}


/**
 * destructor
 */
cFibGraphicsScene::~cFibGraphicsScene(){
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::~cFibGraphicsScene() called"<<endl<<flush);
	
	if ( pFibNode ){
		pFibNode->unregisterNodeChangeListener( this );
	}
	if ( pFibRootNode ){
		pFibRootNode->unregisterNodeChangeListener( this );
	}
	if ( pWidgetFibInputVariables ){
		//delete the widget for the input variables
		pWidgetFibInputVariables->deleteLater();
	}
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::~cFibGraphicsScene() done"<<endl<<flush);
}



/**
 * @return a pointer to the Fib node object this widget shows / represents
 * 	@see pFibNode
 */
cFibNode * cFibGraphicsScene::getFibNode(){
	
	return pFibNode;
}


/**
 * @return a const pointer to the Fib node object this widget shows / represents
 * 	@see pFibNode
 */
const cFibNode * cFibGraphicsScene::getFibNode() const{
	
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
bool cFibGraphicsScene::setFibObjectNode( cFibNode * pNewFibObjectNode ){
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::setFibObjectNode( pNewFibObjectNode="<<pNewFibObjectNode<<") called"<<endl<<flush);
	
	if ( pNewFibObjectNode == NULL ){
		
		return false;
	}
	bool bReturnValue = true;
	
	if ( pFibNode ){
		pFibNode->unregisterNodeChangeListener( this );
	}
	pFibNode = pNewFibObjectNode;
	pFibNode->registerNodeChangeListener( this );
	
	//set pFibRootNode
	if ( pFibRootNode ){
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
		const eFibNodeChangedEvent * pFibNodeChanged ){
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<") called"<<endl<<flush);
	
	if ( ( pFibNodeChanged == NULL ) ||
			( pFibNodeChanged->pFibNodeChanged == NULL ) ){
		//nothing changed
		return;
	}
	if ( pFibNodeChanged->bNodeDeleted &&
			( pFibNodeChanged->pFibNodeChanged == pFibNode ) ){
		/*node of this graphic scene deleted
		 *-> set NULL as this this graphic scene node*/
		pFibNode = NULL;
		//update pEvalueSimpleRGBA255QPainter
		updateEvalueFibObjectForPainter();
		updateForDimensionChange();
		
		evalueInputVariables();
		evalueGraphicsItemsFromFibNode();
		
		DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<") done node deleted"<<endl<<flush);
		return;
	}//else this graphic scene node was not deleted

	if (  pFibNodeChanged->pChangedBy == this ){
		//nothing changed
		DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<") done nothing changed"<<endl<<flush);
		return;
	}
	//check if the event is for pFibRootNode
	if ( pFibRootNode != pFibNode ){
		if ( pFibNodeChanged->pFibNodeChanged == pFibRootNode ){
			//the Fib master root object was changed
			updateEvalueFibObjectForPainter();
			updateForDimensionChange();
			
			update();
			DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<") done the Fib master root object was changed"<<endl<<flush);
			return;
		}
		if ( ( pFibNodeChanged->pFibNodeChanged->getFibObjectVersion() ==
					ulFibNodeVersionDisplayed ) ){
			//nothing changed
			DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<") done the Fib master root object nothing changed"<<endl<<flush);
			return;
		}
	}else{//the Fib node and Fib rood naode are the same
		if ( ( pFibNodeChanged->pFibNodeChanged->getFibObjectVersion() ==
					ulFibNodeVersionDisplayed ) ){
			//nothing changed
			return;
		}
		//the Fib master root object was changed
		updateEvalueFibObjectForPainter();
		updateForDimensionChange();
	}
	
	
	//TODO just update changed parts
	
	evalueInputVariables();
	evalueGraphicsItemsFromFibNode();
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<") done"<<endl<<flush);
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
bool cFibGraphicsScene::evalueInputVariables(){
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::evalueInputVariables() called"<<endl<<flush);
	
	if ( ( pFibNode == NULL ) || ( pFibNode->getFibObject() == NULL ) ){
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
	DEBUG_OUT_L3(<<"cFibGraphicsScene("<<this<<")::evalueInputVariables() lock Fib parts mutex"<<endl<<flush);
	mutexFibParts.lock();
	//evalue the input variables of the Fib object
	DEBUG_OUT_L3(<<"cFibGraphicsScene("<<this<<")::evalueInputVariables() evalue the input variables of the Fib object"<<endl<<flush);
	
	cWidgetFibInputVariables * pNewWidgetFibInputVariables = new
		cWidgetFibInputVariables( pFibNode->getFibObject(), true );
	
	if ( pNewWidgetFibInputVariables->getNumberOfInputVariables() == 0 ){
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
 * This method will return the number of input variables for the Fib
 * object for the Fib node.
 *
 * @see pFibNode
 * @see pWidgetFibInputVariables
 * @see evalueInputVariables()
 * @see getInputVariablesWidget()
 * @return the number of input variables for the Fib object for the Fib node
 */
unsigned int cFibGraphicsScene::getNumberOfInputVariables() const{
	
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
		cWidgetFibInputVariables * pNewWidgetFibInputVariables ){
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::setInputVariablesWidget( pNewWidgetFibInputVariables="<<pNewWidgetFibInputVariables<<") called"<<endl<<flush);
	if ( pNewWidgetFibInputVariables == pWidgetFibInputVariables ){
		//input variables already set
		DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::setInputVariablesWidget( pNewWidgetFibInputVariables="<<pNewWidgetFibInputVariables<<") done input variables already set"<<endl<<flush);
		return;
	}
	
	//if NULL unset old widget
	if ( pMainWindow ){
		//set new widget in main Fib object window
		pMainWindow->setInputVariablesWidgetForCentralGrapical(
			pNewWidgetFibInputVariables );
	}
	cWidgetFibInputVariables * pOldWidgetFibInputVariables =
		pWidgetFibInputVariables;
		
	pWidgetFibInputVariables = pNewWidgetFibInputVariables;
	
	if ( pOldWidgetFibInputVariables ){
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
cWidgetFibInputVariables * cFibGraphicsScene::getInputVariablesWidget(){
	
	return pWidgetFibInputVariables;
}


/**
 * @see pFibNode
 * @see pWidgetFibInputVariables
 * @see evalueInputVariables()
 * @see getNumberOfInputVariables()
 * @return a pointer to the widget with the input variables
 */
const cWidgetFibInputVariables * cFibGraphicsScene::getInputVariablesWidget() const{
	
	return pWidgetFibInputVariables;
}


#ifdef TODO_WEG

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
 * @see getInputVariables()
 * @see getInputVariable()
 * @see getValueForInputVariable()
 * @see setValueForInputVariable()
 * @return true if the input variables for the Fib object for the node
 * 	could be set, else false (and no input variables set)
 */
bool cFibGraphicsScene::evalueInputVariables(){
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::evalueInputVariables() called"<<endl<<flush);
	
	if ( ( pFibNode == NULL ) || ( pFibNode->getFibObject() == NULL ) ){
		//no Fib object -> no input variables
		DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::evalueInputVariables() done no Fib objects"<<endl<<flush);
		
		mutexFibParts.lock();
		pWidgetFibInputVariables.clear();
		mutexFibParts.unlock();
		return false;
	}
	cFibNodeHandler * pFibNodeHandler = cFibNodeHandler::getInstance();
	
	DEBUG_OUT_L3(<<"cFibGraphicsScene("<<this<<")::evalueInputVariables() lock node "<<pFibNode<<" mutex"<<endl<<flush);
	pFibNodeHandler->lock( pFibNode );
	DEBUG_OUT_L3(<<"cFibGraphicsScene("<<this<<")::evalueInputVariables() lock Fib parts mutex"<<endl<<flush);
	mutexFibParts.lock();
	//evalue the input variables of the Fib object
	DEBUG_OUT_L3(<<"cFibGraphicsScene("<<this<<")::evalueInputVariables() evalue the input variables of the Fib object"<<endl<<flush);
	list< cFibVariable * > liNewInputVariables =
		nFibObjectTools::evalueInputVariables( pFibNode->getFibObject() );
	
	//merge the new input variables with the old input variables
	DEBUG_OUT_L3(<<"cFibGraphicsScene("<<this<<")::evalueInputVariables() merge the new input variables with the old input variable"<<endl<<flush);
	list< pair< cFibVariable *, doubleFib > > pWidgetFibInputVariablesOld =
		pWidgetFibInputVariables;
	pWidgetFibInputVariables.clear();
	
	for ( list< cFibVariable * >::iterator
			itrNewVariable = liNewInputVariables.begin();
			itrNewVariable != liNewInputVariables.end(); itrNewVariable++ ){
		//try to evalue the old default value for the input variable
		list< pair< cFibVariable *, doubleFib > >::iterator
			itrOldInputVariable = pWidgetFibInputVariablesOld.begin();
		for ( ; itrOldInputVariable != pWidgetFibInputVariablesOld.end();
				itrOldInputVariable++ ){
			
			if ( itrOldInputVariable->first == (*itrNewVariable) ){
				/*old input variable is new input variable
				-> default value found -> stop search*/
				break;
			}
		}//end for find old default value
		if ( itrOldInputVariable != pWidgetFibInputVariablesOld.end() ){
			//default value found for the input variable -> use it
			pWidgetFibInputVariables.push_back( pair< cFibVariable *, doubleFib >(
				(*itrNewVariable), itrOldInputVariable->second ) );
			//don't need the old variable again -> delete it (to speed up the search)
			pWidgetFibInputVariablesOld.erase( itrOldInputVariable );
		}else{/*else no old default value found for the input variable
			-> set 0 as default value */
			pWidgetFibInputVariables.push_back( pair< cFibVariable *, doubleFib >(
				(*itrNewVariable), 0 ) );
		}
	}
	
	mutexFibParts.unlock();
	pFibNodeHandler->unlock( pFibNode );
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::evalueInputVariables() done"<<endl<<flush);
	return true;
}


/**
 * This method will return the number of input variables for the Fib
 * object for the Fib node.
 *
 * @see pFibNode
 * @see pWidgetFibInputVariables
 * @see evalueInputVariables()
 * @see getInputVariables()
 * @see getInputVariable()
 * @see getValueForInputVariable()
 * @see setValueForInputVariable()
 * @return the number of input variables for the Fib object for the Fib node
 */
unsigned int cFibGraphicsScene::getNumberOfInputVariables() const{
	
	mutexFibParts.lock();
	const unsigned int ulInputVariables = pWidgetFibInputVariables.size();
	mutexFibParts.unlock();
	
	return ulInputVariables;
}


/**
 * This method will retur a list of all input variables for the Fib
 * object for the Fib node.
 *
 * @see pFibNode
 * @see pWidgetFibInputVariables
 * @see evalueInputVariables()
 * @see getNumberOfInputVariables()
 * @see getInputVariable()
 * @see getValueForInputVariable()
 * @see setValueForInputVariable()
 * @return a list of all input variables for the Fib object for the Fib node
 */
list< cFibVariable * > cFibGraphicsScene::getInputVariables(){
	//evalue list with input variables
	mutexFibParts.lock();
	list< cFibVariable * > liRetInputVariables;
	
	for ( list< pair< cFibVariable *, doubleFib > >::iterator
			itrActualInputVariable = pWidgetFibInputVariables.begin();
			itrActualInputVariable != pWidgetFibInputVariables.end(); itrActualInputVariable++ ){
		
		liRetInputVariables.push_back( itrActualInputVariable->first );
	}
	mutexFibParts.unlock();
	
	return liRetInputVariables;
}


/**
 * This method will return the uiNumberOfVariable'th input variable for
 * the Fib object for the Fib node.
 *
 * @see pFibNode
 * @see pWidgetFibInputVariables
 * @see evalueInputVariables()
 * @see getNumberOfInputVariables()
 * @see getInputVariables()
 * @see getValueForInputVariable()
 * @see setValueForInputVariable()
 * @param uiNumberOfVariable the number of the input variable to return
 * 	(counting starts at 1)
 * @return uiNumberOfVariable'th input variable for the Fib object for
 * 	the Fib node, or NULL if non exists
 */
cFibVariable * cFibGraphicsScene::getInputVariable(
		const unsigned int uiNumberOfVariable ){
	//evalue input variable
	mutexFibParts.lock();
	
	list< pair< cFibVariable *, doubleFib > >::iterator itrToReturnVariable =
		getListElement( pWidgetFibInputVariables, uiNumberOfVariable );
	
	cFibVariable * pToReturnVariable =
		( itrToReturnVariable != pWidgetFibInputVariables.end() ) ?
		itrToReturnVariable->first ://input variable found
		NULL;//else input variable not found -> return NULL
		
	mutexFibParts.unlock();
	
	return pToReturnVariable;
}


/**
 * This method returns the value for the uiNumberOfVariable'th input
 * variable.
 *
 * @see pFibNode
 * @see pWidgetFibInputVariables
 * @see evalueInputVariables()
 * @see getNumberOfInputVariables()
 * @see getInputVariables()
 * @see getInputVariable()
 * @see setValueForInputVariable()
 * @param uiNumberOfVariable the number of the input variable, which
 * 	value to return (counting starts at 1)
 * @return the value of the uiNumberOfVariable'th input variable, or 0
 * 	if no uiNumberOfVariable'th input variable exists
 */
doubleFib cFibGraphicsScene::getValueForInputVariable(
	const unsigned int uiNumberOfVariable ) const{
	//evalue input variable
	mutexFibParts.lock();
	
	list< pair< cFibVariable *, doubleFib > >::const_iterator itrToReturnVariable =
		getListElement( pWidgetFibInputVariables, uiNumberOfVariable );
	
	doubleFib dToReturnValue =
		( itrToReturnVariable != pWidgetFibInputVariables.end() ) ?
		itrToReturnVariable->second ://input variable found
		0;//else input variable not found -> return 0
		
	mutexFibParts.unlock();
	
	return dToReturnValue;
}


/**
 * This method sets the value for the uiNumberOfVariable'th input
 * variable.
 *
 * @see pFibNode
 * @see pWidgetFibInputVariables
 * @see evalueInputVariables()
 * @see getNumberOfInputVariables()
 * @see getInputVariables()
 * @see getInputVariable()
 * @see getValueForInputVariable()
 * @param uiNumberOfVariable the number of the input variable, which
 * 	value to set (counting starts at 1)
 * @param dValue the value for the uiNumberOfVariable'th input variable
 * @return true if the value could be set, else false (e. g. no such
 * 	input variablse)
 */
bool cFibGraphicsScene::setValueForInputVariable(
	const unsigned int uiNumberOfVariable, const doubleFib dValue ){
	//evalue input variable
	mutexFibParts.lock();
	
	list< pair< cFibVariable *, doubleFib > >::iterator itrToReturnVariable =
		getListElement( pWidgetFibInputVariables, uiNumberOfVariable );
	
	const bool bVariableFound = ( itrToReturnVariable != pWidgetFibInputVariables.end() );
	if ( bVariableFound ){
		//input variable found -> set value
		itrToReturnVariable->second = dValue;
	}//else input variable not found -> can't set value
		
	mutexFibParts.unlock();
	
	return bVariableFound;
}
#endif //TODO_WEG


/**
 * @return the name of this class "cFibGraphicsScene"
 */
std::string cFibGraphicsScene::getName() const{
	
	return std::string( "cFibGraphicsScene" );
}


/**
 * @return a hint for a good size of this widget
 */
QSize cFibGraphicsScene::sizeHint() const{
	
	return QSize( 640, 480 );
}


/**
 * This method shows the Fib object of the Fib node of this object in
 * the Fib XML representation.
 * TODO: Just (re-)show parts of liFibParts, which have changed (or moved)
 *
 * @see QList <QGraphicsItem *> QGraphicsScene::items()
 * @see liFibParts
 * @see convertToFibGraphicsItem()
 * @see cFibGraphicsItem
 * @return true if the Fib object was displayed, else false
 */
bool cFibGraphicsScene::evalueGraphicsItemsFromFibNode(){
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::evalueGraphicsItemsFromFibNode() called"<<endl<<flush);
	
	//remove old items
	QList< QGraphicsItem * > liOldItems = items();
	
	for ( QList< QGraphicsItem * >::iterator
			itrActualItem = liOldItems.begin();
			itrActualItem != liOldItems.end(); itrActualItem++ ){
		//remove the old item
		removeItem( *itrActualItem );
		delete *itrActualItem;
	}
	//TODO add item for the Fib image size borders (dDirection1Minimum, ...)
	
	//set the input variables to there values, to create the graphics items
	setInputVariables();
	
	if ( ( pFibNode == NULL ) || ( pFibNode->getFibObject() == NULL ) ){
		//no Fib object -> nothing to show
		//update this grapic scene
		update();
		
		return false;
	}
	
	
	//create the graphics item
	cFibGraphicsItem * pFibGraphicsItem =
		convertToFibGraphicsItem( pFibNode->getFibObject() );
	
	addItem( pFibGraphicsItem );
	//update this grapic scene
	update();
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::evalueGraphicsItemsFromFibNode() done"<<endl<<flush);
	return true;
}


/**
 * This method sets the input variables to there values, so that the
 * Fib object can be evalued.
 * @see pWidgetFibInputVariables
 */
void cFibGraphicsScene::setInputVariables(){
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::setInputVariables() called"<<endl<<flush);
	mutexFibParts.lock();
	if ( pWidgetFibInputVariables ){
		pWidgetFibInputVariables->assignValues();
	}
	mutexFibParts.unlock();
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::setInputVariables() done"<<endl<<flush);
}


/**
 * This function will convert the given Fib object into Fib graphic
 * items, so that all Fib graphic items together will look like the
 * image the Fib object represents.
 *
 * @pattern Factory Method
 * @see cFibGraphicsItem
 * @see QGraphicsItem
 * @see pFibNode
 * @param pFibObject the Fib object to convert to Fib graphic items;
 * 	this Fib object should be part object of the Fib object of the
 * 	Fib node pFibNode of this class
 * @return a list of Fib graphic items cFibGraphicsItem for the given
 * 	Fib object or an empty list, if the Fib object could not be converted
 */
cFibGraphicsItem * cFibGraphicsScene::convertToFibGraphicsItem(
		cFibElement * pFibObject ){
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::convertToFibGraphicsItem( pFibObject="<<pFibObject<<") called"<<endl<<flush);
	if ( pFibObject == NULL ){
		//nothing to convert
		DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::convertToFibGraphicsItem( pFibObject="<<pFibObject<<") done no Fib object"<<endl<<flush);
		return NULL;
	}
	/* alt 1 use recursion
	 * - for actual Fib element:
	 * 	- if Fib element is limb element -> check next Fib element (getNextFibElement())
	 * 	- if Fib element is list element -> create cFibGraphicsItemFibList
	 * 		element for it and add the cFibGraphicsItem for every subobject
	 * 		of it, the cFibGraphicsItem are creating by calling the method
	 * 		recursively
	 * 	- if Fib element is root element -> check main Fib object of it
	 * 		(=next Fib element: getNextFibElement())
	 * 	- else -> create cFibGraphicsItemFibObject for it
	 * 
	 */
	if ( pFibObject->isLimb() ){
		//if Fib element is limb element -> use next Fib element to convert
		DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::convertToFibGraphicsItem( pFibObject="<<pFibObject<<") Fib element is limb element"<<endl<<flush);
		return convertToFibGraphicsItem( pFibObject->getNextFibElement() );
	}//else
	const char cType = pFibObject->getType();
	
	switch ( cType ){
		case 'l':{/* if Fib element is list element
			-> create cFibGraphicsItemFibList element for it and add the
				cFibGraphicsItem for every subobject of it, the
				cFibGraphicsItem are creating by calling the method recursively*/
			DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::convertToFibGraphicsItem( pFibObject="<<pFibObject<<") Fib element is list element"<<endl<<flush);
			QList< cFibGraphicsItem * > liSubitems;
			list< cFibElement * > liSubobjects = pFibObject->getSubobjects();
			for ( list< cFibElement * >::iterator
					itrActualSubobject = liSubobjects.begin();
					itrActualSubobject != liSubobjects.end(); itrActualSubobject++ ){
				
				cFibGraphicsItem * pConvertedItem = convertToFibGraphicsItem(
					*itrActualSubobject );
				
				if ( pConvertedItem ){
					liSubitems.push_back( pConvertedItem );
				}
			}
			return new cFibGraphicsItemFibList( pFibObject, ulFibNodeVersionDisplayed,
				this, liSubitems );
		}break;
		case 'r':{//if Fib element is root element -> convert the main Fib object of it
			DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::convertToFibGraphicsItem( pFibObject="<<pFibObject<<") Fib element is root element"<<endl<<flush);
			return convertToFibGraphicsItem( pFibObject->getNextFibElement() );
		}break;
		default://else -> create cFibGraphicsItemFibObject for it
			DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::convertToFibGraphicsItem( pFibObject="<<pFibObject<<") else convert to cFibGraphicsItemFibObject"<<endl<<flush);
			//evalue the object point for the Fib element
			const unsignedIntFib uiObjectPoint =
				pFibObject->getNumberOfObjectPoint();
				
			cFibElement * pTopMostFibElement = pFibObject->getMasterRoot();
			//evalue the defining Fib element for the object point
			const unsignedIntFib uiDefiningFibElementPoint =
				pTopMostFibElement->objectPointToElementPoint( uiObjectPoint, true );
			
			cFibElement * pDefiningFibElement =
				pTopMostFibElement->getFibElement( uiDefiningFibElementPoint );
			
			cFibElement * pPartObjectCopy =
				pTopMostFibElement->copy( uiObjectPoint );
			
			return new cFibGraphicsItemFibObject( pDefiningFibElement,
				ulFibNodeVersionDisplayed, this, pPartObjectCopy );
	}//end switch Fib element type
	//Error: should not happen
	DEBUG_OUT_EL2(<<"cFibGraphicsScene("<<this<<")::convertToFibGraphicsItem( pFibObject="<<pFibObject<<") done no known Fib element"<<endl<<flush);
	return NULL;
	
	
	
#ifdef DELETE_LATER
//TODO delete later?
	/* alt 2 use recursion
	 * - for actual Fib element
	 * 	- if Fib element is limb element -> check next Fib element (getNextFibElement())
	 * 	- if Fib element is leaf element (one subobject) -> create
	 * 		cFibGraphicsItem for it
	 * 	- if Fib element is branch element -> create cFibGraphicsItemGroup
	 * 		element for it and add the cFibGraphicsItem for every subobject
	 * 		of it, the cFibGraphicsItem are creating by calling the method
	 * 		recursively
	 * 
	 */
	/* alt 3:
	- if given Fib object is a root element use its main Fib object as the
		starting point:
	- for every start point search for all subobjects for leafs and convert
		them to seperate cFibGraphicsItem's:
		- serach for subobjects to convert:
			- if limb (isLeaf()==true or one subobject) check next element
			- if branch use every subobject as a new starting point
			- if leaf or external object get the object point and mark it as
				to use object point ( cFibElement::getNumberOfObjectPoint() )
	- end if no Fib objects points to search exists anymore
	- convert all found to use object points to cFibGraphicsItem's
		- copy the object point ( cFibElement::copy( iObjectPoint ) )
		- create a new cFibGraphicsItem with the copied Fib object
	 */
#endif //DELETE_LATER
	
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
void cFibGraphicsScene::notifyNodeForChange(){
	//TODO
	
	if ( pFibNode ){
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
		const eFibNodeChangedEvent & fibNodeChangedEvent ){
	//TODO
	
	if ( pFibNode ){
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
bool cFibGraphicsScene::updateEvalueFibObjectForPainter(){
	
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() called"<<endl<<flush);
	//update pEvalueSimpleRGBA255QPainter
	if ( pFibNode == NULL ){
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
	if ( pGraphicSceneFibObject == NULL ){
		//no Fib object with domains
		pFibNodeHandler->unlock( pFibNode );
		mutexFibParts.unlock();
		return false;
	}
	if ( pEvalueSimpleRGBA255QPainter == NULL ){
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
			( pDomainRGBColor->isVector() ) ){
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
	
	if ( pDomainGrayscaleNew ){
		//get new grayscale color scaling factor
		dNewScalingFactorGrayscale = 1.0 /
			((cDomainSingle*)(pDomainGrayscaleNew))->getMaximum();
	}
	//check if the transparency domain where changed
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() check if the transparency domain where changed"<<endl<<flush);
	cDomain * pDomainTransparencyNew = domainsValid.getDomainForElement(
		cTypeProperty( cTypeProperty::TRANSPARENCY ) );
	
	if ( pDomainTransparencyNew ){
		//get new transparency scaling factor
		dNewScalingFactorAlpha = 1.0 /
			((cDomainSingle*)(pDomainTransparencyNew))->getMaximum();
	}
	
	
	//if a scaling factor was changed -> update pEvalueSimpleRGBA255QPainter
	if ( ( dOldScalingFactorAlpha != dNewScalingFactorAlpha ) ||
			( dOldScalingFactorRed != dNewScalingFactorRed ) ||
			( dOldScalingFactorGreen != dNewScalingFactorGreen ) ||
			( dOldScalingFactorBlue != dNewScalingFactorBlue ) ||
			( dOldScalingFactorGrayscale != dNewScalingFactorGrayscale ) ){
		
		DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() new pEvalueSimpleRGBA255QPainter(NULL, dNewScalingFactorAlpha="<<dNewScalingFactorAlpha<<", dNewScalingFactorRed="<<dNewScalingFactorRed<<", dNewScalingFactorGreen="<<dNewScalingFactorGreen<<", dNewScalingFactorBlue="<<dNewScalingFactorBlue<<", dNewScalingFactorGrayscale="<<dNewScalingFactorGrayscale<<" )"<<endl<<flush);
	
		delete pEvalueSimpleRGBA255QPainter;
		pEvalueSimpleRGBA255QPainter = new cEvalueSimpleRGBA255QPainter( NULL,
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
			( pDomainRGBColor->isVector() ) ){
		//get RGB color scaling factors
		const cDomainVectorBasis * pVecDomainColorRgb =
			(const cDomainVectorBasis*)pDomainRGBColor;
		//get red scaling factor
		const cDomainSingle * pColorRedDomain   = (cDomainSingle*)(
			pVecDomainColorRgb->getElementDomain( 1 ) );
		
		const string szDomainElementTypeRed = pColorRedDomain->getType();
		if ( ( szDomainElementTypeRed.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
					(szDomainElementTypeRed.compare( 0, 13, "DomainInteger" ) == 0) ){
			//cDomainIntegerBasis
			dNewScalingFactorRed =
				((cDomainIntegerBasis*)pColorRedDomain)->getScalingFactor();
		}
		//get green scaling factor
		const cDomainSingle * pColorGreenDomain = (cDomainSingle*)(
			pVecDomainColorRgb->getElementDomain( 2 ) );
		
		const string szDomainElementTypeGreen = pColorGreenDomain->getType();
		if ( ( szDomainElementTypeGreen.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
					(szDomainElementTypeGreen.compare( 0, 13, "DomainInteger" ) == 0) ){
			//cDomainIntegerBasis
			dNewScalingFactorGreen =
				((cDomainIntegerBasis*)pColorGreenDomain)->getScalingFactor();
		}
		//get blue scaling factor
		const cDomainSingle * pColorBlueDomain  = (cDomainSingle*)(
			pVecDomainColorRgb->getElementDomain( 3 ) );
		
		const string szDomainElementTypeBlue = pColorBlueDomain->getType();
		if ( ( szDomainElementTypeBlue.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
					(szDomainElementTypeBlue.compare( 0, 13, "DomainInteger" ) == 0) ){
			//cDomainIntegerBasis
			dNewScalingFactorBlue =
				((cDomainIntegerBasis*)pColorBlueDomain)->getScalingFactor();
		}
	}
	
	//check if the grayscale color domain where changed
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() check if the grayscale color domain where changed"<<endl<<flush);
	cDomain * pDomainGrayscaleNew = domainsValid.getDomainForElement(
		cTypeProperty( cTypeProperty::COLOR_GRAYSCALE ) );
	
	if ( pDomainGrayscaleNew ){
		const string szDomainElementTypeGrayscale = pDomainGrayscaleNew->getType();
		if ( ( szDomainElementTypeGrayscale.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
					(szDomainElementTypeGrayscale.compare( 0, 13, "DomainInteger" ) == 0) ){
			//get new grayscale color scaling factor
			dNewScalingFactorGrayscale =
				((cDomainIntegerBasis*)pDomainGrayscaleNew)->getScalingFactor();
		}
	}
	//check if the transparency domain where changed
	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateEvalueFibObjectForPainter() check if the transparency domain where changed"<<endl<<flush);
	cDomain * pDomainTransparencyNew = domainsValid.getDomainForElement(
		cTypeProperty( cTypeProperty::TRANSPARENCY ) );
	
	if ( pDomainTransparencyNew ){
		const string szDomainElementTypeTransparency = pDomainTransparencyNew->getType();
		if ( ( szDomainElementTypeTransparency.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
					(szDomainElementTypeTransparency.compare( 0, 13, "DomainInteger" ) == 0) ){
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
			( dOldScalingFactorGrayscale != dNewScalingFactorGrayscale ) ){
		
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
bool cFibGraphicsScene::updateForDimensionChange(){

	DEBUG_OUT_L2(<<"cFibGraphicsScene("<<this<<")::updateForDimensionChange() called"<<endl<<flush);
	//update pEvalueSimpleRGBA255QPainter
	if ( pFibNode == NULL ){
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
	if ( pGraphicSceneFibObject == NULL ){
		//no Fib object with domains
		return false;
	}
	
	cDomain * pDomainDimension = pGraphicSceneFibObject->
		getValidDomains().getDomainForElement( cTypeDimension() );
	
	if ( pDomainDimension == NULL ){
		DEBUG_OUT_EL1( <<"Error: No dimension domain."<<endl; );
		return false;
	}
	cDomainVectorBasis * pVecDomainDimension = (cDomainVectorBasis*)pDomainDimension;
	
	if ( pVecDomainDimension->getNumberOfElements() != 2 ){
		DEBUG_OUT_EL1( <<"Error: No 2 dimensional dimension domain in Fib object."<<endl; );
		return false;
	}
	if ( ( ! pVecDomainDimension->getElementDomain( 1 )->isScalar() ) ||
			( ! pVecDomainDimension->getElementDomain( 2 )->isScalar() ) ){
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
			( szDomainElementTypeDim1.compare( 0, 13, "DomainInteger" ) == 0 ) ){
		//cDomainIntegerBasis
		dPointWidth = ((cDomainIntegerBasis*)pDirection1Domain)->getScalingFactor();
	}
	//evalue the values for direction 2
	dDirection2Minimum = pDirection2Domain->getMinimum();
	dDirection2Maximum = pDirection2Domain->getMaximum();
	dPointHeight = 1.0;
	const string szDomainElementTypeDim2 = pDirection2Domain->getType();
	if ( ( szDomainElementTypeDim2.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
			( szDomainElementTypeDim2.compare( 0, 13, "DomainInteger" ) == 0 ) ){
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
		cFibGraphicsScene::getEvalueSimpleRGBA255QPainter() const{
	
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
bool cFibGraphicsScene::setPenForPointSize( QPainter * pPainter ) const{
	
	if ( pPainter == NULL ){
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







