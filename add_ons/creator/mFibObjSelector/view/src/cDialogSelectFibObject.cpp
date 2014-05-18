
//TODO check

/**
 * @file cDialogSelectFibObject
 * file name: cDialogSelectFibObject.cpp
 * @author Betti Oesterholz
 * @date 24.10.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a dialog to select a Fib object.
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
 * This file implements a class for a dialog to select a Fib object.
 *
 * It should look like:
 * +------------------------------------------------------------------+
 * |  Select database   Load database    Load Fib object    Search    |
 * |  -> pull down                                                    |
 * |  new category                                                    |
 * | +---------------------------------------------------------------+|
 * | | pull down category1   pull cat1      ...  pull catn           ||
 * | |                                                               ||
 * | | Fib obj info 1.1      Fib info 2.1        Fib info n.1        ||
 * | | Fib obj info 1.2      Fib info 2.2        Fib info n.2        ||
 * | | ...                   ...                 ...                 ||
 * | | Fib obj info 1.m      Fib info 2.m        Fib info n.m        ||
 * | +---------------------------------------------------------------+|
 * |  show   insert                                                   |
 * +------------------------------------------------------------------+
 *
 * pull down category:
 *    - categories for the Fib objects to show in the list below
 *    possibel category typs:
 *       - relative categories: same type (sameType), is contained (isContained), ...
 *       - absolute categories: all, typs like: objects, people, ...
 *       (first category list has just absolute)
 *
 * Search: search for a Fib object in the known Fib objects
 *
 * @see cWidgetFibObjectInfo
 * @see cFibObjectInfo
 * @see cFibObjectInfoHandler
 */
/*
History:
24.10.2013  Oesterholz  created
13.04.2014  Oesterholz  insertSelectedFibObject() insert selected Fib object
	info on given position
18.05.2014  Oesterholz  loadFibObject(): opens with last choosen file
*/


//TODO switches for test proposes
#define DEBUG



#include "cDialogSelectFibObject.h"

#include <QFileDialog>
#include <QSettings>

#include "cFlowLayout.h"

#include "cFibObjectInfo.h"
#include "cFibObjectSourcePath.h"
#include "cFibObjectInfoHandler.h"
#include "cWidgetFibObjectInfo.h"
#include "cWidgetFibObjectInfos.h"
#include "cFibObjectCategory.h"
#include "cMainWindowHandler.h"
#include "cFibNode.h"


using namespace fib::nCreator;
using namespace std;


/**
 * The standard constructor for the dialog to select Fib objects.
 *
 * @param pParent a pointer the parent of this new Fib object info widget
 * @param pInAssociatedNode to the associated Fib object node, or NULL if non exists
 * 	@see pAssociatedNode
 */
cDialogSelectFibObject::cDialogSelectFibObject( QWidget * pParent,
			cFibNode * pInAssociatedNode ):
		QWidget( pParent ),
		pBaseFibObjectInfo( NULL ), pScrollAreaFibObjectInfos( NULL ),
		pSplitterFibObjectInfos( NULL ), pAssociatedNode( pInAssociatedNode ),
		pButtonSelectDatabase( NULL ), pButtonLoadDatabase( NULL ),
		pButtonLoadFibObject( NULL ), pButtonSearchForFibObject( NULL ),
		pButtonNewCategory( NULL ), pLayoutTopMenue( NULL ),
		pButtonShowSelectedFibObject( NULL ), pButtonInsertSelectedFibObject( NULL ),
		pLayoutBottomMenue( NULL ), pLayoutMain( NULL ) {
	
	DEBUG_OUT_L2(<<"cDialogSelectFibObject("<<this<<")::cDialogSelectFibObject( pParent="<<pParent<<", pInAssociatedNode="<<pInAssociatedNode<<" );"<<endl<<flush);
	
	//TODO restore setting with actual categories
	
	createDialog();
}


/**
 * A constructor for the dialog to select Fib objects.
 *
 * @param pInAssociatedNode to the associated Fib object node, or NULL if non exists
 * 	@see pAssociatedNode
 */
cDialogSelectFibObject::cDialogSelectFibObject( cFibNode * pInAssociatedNode ):
		QWidget( NULL ),
		pBaseFibObjectInfo( NULL ), pScrollAreaFibObjectInfos( NULL ),
		pSplitterFibObjectInfos( NULL ), pAssociatedNode( pInAssociatedNode ),
		pButtonSelectDatabase( NULL ), pButtonLoadDatabase( NULL ),
		pButtonLoadFibObject( NULL ), pButtonSearchForFibObject( NULL ),
		pButtonNewCategory( NULL ), pLayoutTopMenue( NULL ),
		pButtonShowSelectedFibObject( NULL ), pButtonInsertSelectedFibObject( NULL ),
		pLayoutBottomMenue( NULL ), pLayoutMain( NULL ) {
	
	DEBUG_OUT_L2(<<"cDialogSelectFibObject("<<this<<")::cDialogSelectFibObject(pInAssociatedNode="<<pInAssociatedNode<<" );"<<endl<<flush);
	
	//TODO restore setting with actual categories
	
	createDialog();
}


/**
 * The destructor.
 */
cDialogSelectFibObject::~cDialogSelectFibObject() {
	
	DEBUG_OUT_L2(<<"cDialogSelectFibObject("<<this <<")::~cDialogSelectFibObject();"<<endl <<flush);
	//TODO store setting with actual categories
	
	
	mutexFibObjectInfos.lock();
	//delete all list of Fib objects infos
	for ( QList< cWidgetFibObjectInfos * >::iterator
			itrListOfFibObjects = liListsOfFibObjects.begin();
			itrListOfFibObjects != liListsOfFibObjects.end(); itrListOfFibObjects++ ) {
		
		(*itrListOfFibObjects)->unregisterListenerSelectedFibObjectInfo( this );
		(*itrListOfFibObjects)->deleteLater();
	}
	liListsOfFibObjects.clear();
	mutexFibObjectInfos.unlock();
}


/**
 * @return the name of this class "cDialogSelectFibObject"
 */
string cDialogSelectFibObject::getName() const {
	
	return "cDialogSelectFibObject";
}


/**
 * This method returns the selected Fib object info.
 * It is the base for all relativ categories.
 *
 * @see pBaseFibObjectInfo
 * @see setSelectedFibObjectInfo()
 * @return a pointer to the selected Fib object info
 */
cFibObjectInfo * cDialogSelectFibObject::getSelectedFibObjectInfo() {
	
	mutexFibObjectInfos.lock();
	cFibObjectInfo * pSelectedFibObjectInfo = pBaseFibObjectInfo;
	mutexFibObjectInfos.unlock();
	return pSelectedFibObjectInfo;
}


/**
 * This method returns the selected Fib object info.
 * It is the base for all relativ categories.
 *
 * @see pBaseFibObjectInfo
 * @see setSelectedFibObjectInfo()
 * @return a const pointer to the selected Fib object info
 */
const cFibObjectInfo * cDialogSelectFibObject::getSelectedFibObjectInfo() const {
	
	mutexFibObjectInfos.lock();
	const cFibObjectInfo * pSelectedFibObjectInfo = pBaseFibObjectInfo;
	mutexFibObjectInfos.unlock();
	return pSelectedFibObjectInfo;
}


/**
 * This method sets the selected Fib object info.
 * It will be the base for all relativ categories.
 *
 * @see pBaseFibObjectInfo
 * @see getSelectedFibObjectInfo()
 * @param pSelectedFibObjectInfo the selected Fib object info to set
 */
void cDialogSelectFibObject::setSelectedFibObjectInfo(
		cFibObjectInfo * pSelectedFibObjectInfo ) {
	
	DEBUG_OUT_L2(<<"cDialogSelectFibObject("<<this <<")::setSelectedFibObjectInfo( pSelectedFibObjectInfo="<<pSelectedFibObjectInfo<<");"<<endl <<flush);
	
	mutexFibObjectInfos.lock();
	if ( pBaseFibObjectInfo == pSelectedFibObjectInfo ) {
		//correct selected Fib object info allready set
		mutexFibObjectInfos.unlock();
		return;
	}//else set selected Fib object info
	//activate bottons for using selected Fib object just if a Fib object is selected
	if ( pSelectedFibObjectInfo == NULL ) {// && ( pBaseFibObjectInfo != NULL )
		//deactivate buttons for using selected Fib object
		mutexGraphicalElements.lock();
		if ( pButtonShowSelectedFibObject ) {
			pButtonShowSelectedFibObject->setEnabled( false );
		}
		if ( pButtonInsertSelectedFibObject ) {
			pButtonInsertSelectedFibObject->setEnabled( false );
		}
		mutexGraphicalElements.unlock();
	}else if ( pBaseFibObjectInfo == NULL ) {// && ( pSelectedFibObjectInfo != NULL )
		//activate buttons for using selected Fib object
		mutexGraphicalElements.lock();
		if ( pButtonShowSelectedFibObject ) {
			pButtonShowSelectedFibObject->setEnabled( true );
		}
		if ( pButtonInsertSelectedFibObject ) {
			pButtonInsertSelectedFibObject->setEnabled( true );
		}
		mutexGraphicalElements.unlock();
	}
	pBaseFibObjectInfo = pSelectedFibObjectInfo;
	
	/* set base Fib object info in all Fib object info lists +
	 * adapt there possible categories*/
	//the possible categories are all absolute categories plus the relativ categories
	QList< cFibObjectCategory > liPossibleCategories =
		cFibObjectInfoHandler::getInstance()->getPossibleFibObjectCategories();
	//set just absolute categories in first Fib object info list
	QList< cWidgetFibObjectInfos * >::iterator
		itrListOfFibObjects = liListsOfFibObjects.begin();
	if ( itrListOfFibObjects == liListsOfFibObjects.end() ) {
		//no first Fib object info list -> done
		mutexFibObjectInfos.unlock();
		return;
	}
	//set possible categories
	(*itrListOfFibObjects)->setPossibleCategories( liPossibleCategories, false );
	//set selected Fib object
	(*itrListOfFibObjects)->setSelectedFibObjectInfo( pBaseFibObjectInfo );
	
	itrListOfFibObjects++;
	if ( itrListOfFibObjects == liListsOfFibObjects.end() ) {
		//no second Fib object info list -> done
		mutexFibObjectInfos.unlock();
		return;
	}
	//get relativ categories (connections of selected Fib object)
	if ( pBaseFibObjectInfo != NULL ) {
		
		const std::map< string, std::set< unsigned long > > mapConnections =
			pBaseFibObjectInfo->getConnectedToMap();
		for ( std::map< string, std::set< unsigned long > >::const_reverse_iterator
				itrConnection = mapConnections.rbegin();
				itrConnection != mapConnections.rend(); itrConnection++ ) {
			//insert the relative categories at the front
			liPossibleCategories.push_front( cFibObjectCategory(
				QString( itrConnection->first.c_str() ), false ) );
		}//end for all connections
		
	}/*else if no base Fib object info or first Fib object info list
	-> use no relativ categories (connections of selected Fib object)*/
	for ( ; itrListOfFibObjects != liListsOfFibObjects.end(); itrListOfFibObjects++ ) {
		
		//set possible categories
		(*itrListOfFibObjects)->setPossibleCategories( liPossibleCategories, false );
		//set selected Fib object
		(*itrListOfFibObjects)->setSelectedFibObjectInfo( pBaseFibObjectInfo );
	}
	mutexFibObjectInfos.unlock();
}


/**
 * This method sets the selected Fib object info widget.
 * It will be the base for all relativ categories.
 *
 * @see pBaseFibObjectInfo
 * @see getSelectedFibObjectInfo()
 * @param pWidgetFibObjectInfo a pointer to the selected widget of the
 * 	Fib object info to set
 */
void cDialogSelectFibObject::setSelectedFibObjectInfo(
		cWidgetFibObjectInfo * pWidgetFibObjectInfo ) {
	
	DEBUG_OUT_L2(<<"cDialogSelectFibObject("<<this <<")::setSelectedFibObjectInfo( pWidgetFibObjectInfo="<<pWidgetFibObjectInfo<<");"<<endl <<flush);
	
	mutexFibObjectInfos.lock();
	cFibObjectInfo * pFibObjectInfo = ( pWidgetFibObjectInfo == NULL ) ? NULL :
		(const_cast<cFibObjectInfo*>(pWidgetFibObjectInfo->getFibObjectInfo() ) );
	if ( pBaseFibObjectInfo == pFibObjectInfo ) {
		//correct selected Fib object info allready set
		mutexFibObjectInfos.unlock();
		return;
	}//else set selected Fib object info
	//activate bottons for using selected Fib object just if a Fib object is selected
	if ( pFibObjectInfo == NULL ) {// && ( pBaseFibObjectInfo != NULL )
		//deactivate buttons for using selected Fib object
		mutexGraphicalElements.lock();
		if ( pButtonShowSelectedFibObject ) {
			pButtonShowSelectedFibObject->setEnabled( false );
		}
		if ( pButtonInsertSelectedFibObject ) {
			pButtonInsertSelectedFibObject->setEnabled( false );
		}
		mutexGraphicalElements.unlock();
	}else if ( pBaseFibObjectInfo == NULL ) {// && ( pFibObjectInfo != NULL )
		//activate buttons for using selected Fib object
		mutexGraphicalElements.lock();
		if ( pButtonShowSelectedFibObject ) {
			pButtonShowSelectedFibObject->setEnabled( true );
		}
		if ( pButtonInsertSelectedFibObject ) {
			pButtonInsertSelectedFibObject->setEnabled( true );
		}
		mutexGraphicalElements.unlock();
	}
	pBaseFibObjectInfo = pFibObjectInfo;
	
	/* set base Fib object info in all Fib object info lists +
	 * adapt there possible categories*/
	//the possible categories are all absolute categories plus the relativ categories
	QList< cFibObjectCategory > liPossibleCategories =
		cFibObjectInfoHandler::getInstance()->getPossibleFibObjectCategories();
	//set just absolute categories in first Fib object info list
	QList< cWidgetFibObjectInfos * >::iterator
		itrListOfFibObjects = liListsOfFibObjects.begin();
	if ( itrListOfFibObjects == liListsOfFibObjects.end() ) {
		//no first Fib object info list -> done
		mutexFibObjectInfos.unlock();
		return;
	}
	//set possible categories
	(*itrListOfFibObjects)->setPossibleCategories( liPossibleCategories, false );
	//set selected Fib object
	(*itrListOfFibObjects)->setSelectedFibObjectInfo( pWidgetFibObjectInfo );
	
	itrListOfFibObjects++;
	if ( itrListOfFibObjects == liListsOfFibObjects.end() ) {
		//no second Fib object info list -> done
		mutexFibObjectInfos.unlock();
		return;
	}
	//get relativ categories (connections of selected Fib object)
	if ( pBaseFibObjectInfo != NULL ) {
		
		const std::map< string, std::set< unsigned long > > mapConnections =
			pBaseFibObjectInfo->getConnectedToMap();
		for ( std::map< string, std::set< unsigned long > >::const_reverse_iterator
				itrConnection = mapConnections.rbegin();
				itrConnection != mapConnections.rend(); itrConnection++ ) {
			//insert the relative categories at the front
			liPossibleCategories.push_front( cFibObjectCategory(
				QString( itrConnection->first.c_str() ), false ) );
		}//end for all connections
		
	}/*else if no base Fib object info or first Fib object info list
	-> use no relativ categories (connections of selected Fib object)*/
	for ( ; itrListOfFibObjects != liListsOfFibObjects.end(); itrListOfFibObjects++ ) {
		
		//set possible categories
		(*itrListOfFibObjects)->setPossibleCategories( liPossibleCategories, false );
		//set selected Fib object
		(*itrListOfFibObjects)->setSelectedFibObjectInfo( pWidgetFibObjectInfo );
	}
	mutexFibObjectInfos.unlock();
}


/**
 * Event method
 * This method will be called if an Fib object info widget was
 * selected.
 *
 * @see lSelectedWidgetFibObjectInfo
 * @param pWidgetFibObjectInfo a pointer to the Fib object info
 * 	widget which was selected
 */
void cDialogSelectFibObject::selectWidgetFibObjectInfo(
		const cWidgetFibObjectInfo * pWidgetFibObjectInfo ) {
	
	DEBUG_OUT_L2(<<"cDialogSelectFibObject("<<this <<")::selectWidgetFibObjectInfo( pWidgetFibObjectInfo="<<pWidgetFibObjectInfo<<");"<<endl <<flush);
	
	//set new selected Fib object info
	setSelectedFibObjectInfo( const_cast<cWidgetFibObjectInfo*>(
		pWidgetFibObjectInfo ) );
}


/**
 * This method returns associated Fib object node, or NULL if non exists.
 * If you insert a selected Fib object this will be the Fib object node
 * in which Fib object it will be inserted.
 *
 * @see pAssociatedNode
 * @see setAssociatedNode()
 * @return a pointer to the associated Fib object node
 */
cFibNode * cDialogSelectFibObject::getAssociatedNode() {
	
	mutexFibObjectInfos.lock();
	cFibNode * pRetAssociatedNode = pAssociatedNode;
	mutexFibObjectInfos.unlock();
	return pRetAssociatedNode;
}


/**
 * This method returns associated Fib object node, or NULL if non exists.
 * If you insert a selected Fib object this will be the Fib object node
 * in which Fib object it will be inserted.
 *
 * @see pAssociatedNode
 * @see setAssociatedNode()
 * @return a const pointer to the associated Fib object node
 */
const cFibNode * cDialogSelectFibObject::getAssociatedNode() const {
	
	mutexFibObjectInfos.lock();
	const cFibNode * pRetAssociatedNode = pAssociatedNode;
	mutexFibObjectInfos.unlock();
	return pRetAssociatedNode;
}


/**
 * This method sets the selected Fib object info.
 * It will be the base for all relativ categories.
 *
 * @see pAssociatedNode
 * @see getAssociatedNode()
 * @param pAssociatedNode a pointer to the the associated Fib object node
 */
void cDialogSelectFibObject::setAssociatedNode( cFibNode * pAssociatedNode ) {
	
	mutexFibObjectInfos.lock();
	pAssociatedNode = pAssociatedNode;
	mutexFibObjectInfos.unlock();
}



/**
 * This slot opens a dialog to select a Fib database.
 * @see pButtonSelectDatabase
 */
void cDialogSelectFibObject::selectDatabase() {
	//TODO open dialog to select a database
	
}


/**
 * This slot opens a dialog to load a Fib object database.
 * @see pButtonLoadDatabase
 */
void cDialogSelectFibObject::loadDatabase() {
	//TODO open dialog to load a database
	
}


/**
 * This slot opens a dialog to load a Fib object.
 * @see pButtonLoadFibObject
 */
void cDialogSelectFibObject::loadFibObject() {
	
	DEBUG_OUT_L2(<<"cDialogSelectFibObject("<<this <<")::loadFibObject() started"<<endl <<flush);
	
	//open dialog to load a Fib object
	DEBUG_OUT_L2(<<"cDialogSelectFibObject("<<this<<")::loadFibObject() called"<<endl<<flush);
	
	//to set start file
	QSettings settings("Fib development", "Fib creator");
	//open file dialog
	QFileDialog fileDialog( NULL, tr("Open Fib object"), settings.value(
			"dialogSelectFibObject/fileDialog/lastFibFile",
				QDir::homePath() + QDir::separator() + "*.xml" ).toString(),
		tr("Fib XML (*.xml);;Fib compressed (*.fib)" ) );
	
	fileDialog.setFileMode( QFileDialog::ExistingFile );
	
	if ( fileDialog.exec() ) {
		//file(s) was/(where) choosen, add Fib object infos from the choosen files
		const QStringList liFileNames = fileDialog.selectedFiles();
		if ( ! liFileNames.empty() ) {
			//store actual first file as last used file
			settings.setValue("dialogSelectFibObject/fileDialog/lastFibFile", liFileNames.front() );
		}
		
		cFibObjectInfoHandler * pFibObjectInfoHandler =
			cFibObjectInfoHandler::getInstance();
		
		for ( QStringList::const_iterator itrFileName = liFileNames.begin();
				itrFileName != liFileNames.end(); itrFileName++ ) {
			
			DEBUG_OUT_L2(<<"cDialogSelectFibObject("<<this<<")::loadFibObject() opening Fib object info from file "<<(itrFileName->toStdString())<<endl<<flush);
			cFibObjectSourcePath fibObjectSourcePath( itrFileName->toStdString() );
			pFibObjectInfoHandler->addFibObjectInfo( cFibObjectInfo(
				((unsigned long)(0)), &fibObjectSourcePath ) );
			
			//update all Fib object info lists
			for ( QList< cWidgetFibObjectInfos * >::const_iterator
					itrFibInfos = liListsOfFibObjects.begin();
					itrFibInfos != liListsOfFibObjects.end(); itrFibInfos++ ) {
				//update Fib object info widget lists
				(*itrFibInfos)->updateForCategory();
			}
		}
	}//else no file was choosen
}


/**
 * This slot opens a dialog to search for a Fib object.
 * @see pButtonSearchForFibObject
 */
void cDialogSelectFibObject::searchForFibObject() {
	
	DEBUG_OUT_L2(<<"cDialogSelectFibObject("<<this <<")::searchForFibObject() started"<<endl <<flush);
	//TODO open dialog to search for a Fib object
	
}


/**
 * This slot creates a Fib object list for a new category.
 * @see pButtonNewCategory
 */
void cDialogSelectFibObject::newFibObjectCategory() {
	
	DEBUG_OUT_L2(<<"cDialogSelectFibObject("<<this <<")::newFibObjectCategory() started"<<endl <<flush);
	
	//the possible categories are all absolute categories plus the relativ categories
	QList< cFibObjectCategory > liPossibleCategories =
		cFibObjectInfoHandler::getInstance()->getPossibleFibObjectCategories();
	
	//get relativ categories (connections of selected Fib object)
	mutexFibObjectInfos.lock();
	if ( ( pBaseFibObjectInfo != NULL ) && ( ! liListsOfFibObjects.empty() ) ) {
		
		const std::map< string, std::set< unsigned long > > mapConnections =
			pBaseFibObjectInfo->getConnectedToMap();
		for ( std::map< string, std::set< unsigned long > >::const_reverse_iterator
				itrConnection = mapConnections.rbegin();
				itrConnection != mapConnections.rend(); itrConnection++ ) {
			//insert the relative categories at the front
			liPossibleCategories.push_front( cFibObjectCategory(
				QString( itrConnection->first.c_str() ), false ) );
		}//end for all connections
		
	}/*else if no base Fib object info or first Fib object info list
	-> use no relativ categories (connections of selected Fib object)*/
	//create new Fib object info list widget
	cWidgetFibObjectInfos * pWidgetFibObjectInfos =
		new cWidgetFibObjectInfos( liPossibleCategories, pBaseFibObjectInfo,
			this );
	
	connect( pWidgetFibObjectInfos,
		SIGNAL( closeWidgetFibObjectInfos( cWidgetFibObjectInfos * ) ),
		this, SLOT( closeWidgetFibObjectInfos( cWidgetFibObjectInfos * ) ) );
	
	liListsOfFibObjects.push_back( pWidgetFibObjectInfos );
	pWidgetFibObjectInfos->registerListenerSelectedFibObjectInfo( this );
	//add to pSplitterFibObjectInfos
	mutexGraphicalElements.lock();
	if ( pSplitterFibObjectInfos ) {
		pSplitterFibObjectInfos->addWidget( pWidgetFibObjectInfos );
	}
	mutexGraphicalElements.unlock();
	
	mutexFibObjectInfos.unlock();
}


/**
 * This slot close a cWidgetFibObjectInfos widget.
 * It will be removed from the list of lists of Fib object infos and
 * deleted from memory.
 *
 * @see cWidgetFibObjectInfos::closeWidgetFibObjectInfos()
 * @param pWidgetFibObjectInfos a pointer to the cWidgetFibObjectInfos
 * 	widget which should be closed
 */
void cDialogSelectFibObject::closeWidgetFibObjectInfos(
		cWidgetFibObjectInfos * pWidgetFibObjectInfos ) {
	
	DEBUG_OUT_L2(<<"cDialogSelectFibObject("<<this <<")::closeWidgetFibObjectInfos() started"<<endl <<flush);
	
	if ( pWidgetFibObjectInfos == NULL ) {
		//nothing to remove
		return;
	}
	mutexFibObjectInfos.lock();
	liListsOfFibObjects.removeAll( pWidgetFibObjectInfos );
	
	pWidgetFibObjectInfos->deleteLater();
	
	mutexFibObjectInfos.unlock();
}


/**
 * This slot will show the selected Fib object.
 * @see pButtonShowSelectedFibObject
 * @see pBaseFibObjectInfo
 * @see cMainWindowHandler
 * @see cFibObjectMainWindow
 */
void cDialogSelectFibObject::showSelectedFibObject() {
	
	DEBUG_OUT_L2(<<"cDialogSelectFibObject("<<this <<")::showSelectedFibObject() started"<<endl <<flush);
	
	//open selected Fib object info with main window handler
	mutexFibObjectInfos.lock();
	if ( pBaseFibObjectInfo ) {
		cMainWindowHandler * pMainWindowHandler =
			cMainWindowHandler::getInstance();
		
		pMainWindowHandler->getNewMainWindowForFibObjectInfo(
			pBaseFibObjectInfo, true );
	}
	mutexFibObjectInfos.unlock();
	
}


/**
 * This method will insert the selected Fib object into the associated
 * Fib Node.
 * If possible the inserted Fib object will be inserted on the given position.
 *
 * @see pButtonInsertSelectedFibObject
 * @see pBaseFibObjectInfo
 * @see pAssociatedNode
 * @see cFibNode
 * @param poiInsertPosition the position on which the Fib object should
 * 	be inserted
 * @return true if the Fib object was inserted, else false
 */
bool cDialogSelectFibObject::insertSelectedFibObject(
		const QPoint & poiInsertPosition ) {
	
	DEBUG_OUT_L2(<<"cDialogSelectFibObject("<<this <<")::insertSelectedFibObject( poiInsertPosition=("<<poiInsertPosition.x() <<","<<poiInsertPosition.y()<<") ) started"<<endl <<flush);
	
	mutexFibObjectInfos.lock();
	cFibObjectInfo * pToInsertFibObjectInfo = pBaseFibObjectInfo;
	mutexFibObjectInfos.unlock();
	if ( ( pToInsertFibObjectInfo != NULL ) && ( pAssociatedNode != NULL ) ) {
		//insert Fib object into with this associated Fib object node (of main window)
		return pAssociatedNode->insertFibObjectInfo(
			pToInsertFibObjectInfo, poiInsertPosition );
	}//else if associated Fib object node or selected Fib object exists -> do nothing
	return false;
}


/**
 * This method will insert the selected Fib object into the associated
 * Fib Node.
 * If possible the inserted Fib object will be inserted on the given position.
 *
 * @see pButtonInsertSelectedFibObject
 * @see pBaseFibObjectInfo
 * @see pAssociatedNode
 * @see cFibNode
 * @param poiInsertPosition the position on which the Fib object should
 * 	be inserted
 * @return true if the Fib object was inserted, else false
 */
bool cDialogSelectFibObject::insertSelectedFibObject(
		const QPointF & poiInsertPosition ) {
	
	DEBUG_OUT_L2(<<"cDialogSelectFibObject("<<this <<")::insertSelectedFibObject( poiInsertPosition=("<<poiInsertPosition.x() <<","<<poiInsertPosition.y()<<") ) started"<<endl <<flush);
	
	mutexFibObjectInfos.lock();
	cFibObjectInfo * pToInsertFibObjectInfo = pBaseFibObjectInfo;
	mutexFibObjectInfos.unlock();
	if ( ( pToInsertFibObjectInfo != NULL ) && ( pAssociatedNode != NULL ) ) {
		//insert Fib object into with this associated Fib object node (of main window)
		return pAssociatedNode->insertFibObjectInfo(
			pToInsertFibObjectInfo, poiInsertPosition );
	}//else if associated Fib object node or selected Fib object exists -> do nothing
	return false;
}


/**
 * This slot will insert the selected Fib object in the activ main window.
 * @see pButtonInsertSelectedFibObject
 * @see pBaseFibObjectInfo
 * @see cFibNode
 */
void cDialogSelectFibObject::insertSelectedFibObject() {
	
	DEBUG_OUT_L2(<<"cDialogSelectFibObject("<<this <<")::insertSelectedFibObject() started"<<endl <<flush);
	
	mutexFibObjectInfos.lock();
	cFibObjectInfo * pToInsertFibObjectInfo = pBaseFibObjectInfo;
	mutexFibObjectInfos.unlock();
	if ( ( pToInsertFibObjectInfo != NULL ) && ( pAssociatedNode != NULL ) ) {
		//insert Fib object into with this associated Fib object node (of main window)
		pAssociatedNode->insertFibObjectInfo( pToInsertFibObjectInfo );
	}//else if associated Fib object node or selected Fib object exists -> do nothing
}




/**
 * This method will create this dialog.
 */
void cDialogSelectFibObject::createDialog() {
	
	DEBUG_OUT_L2(<<"cDialogSelectFibObject("<<this <<")::createDialog() started"<<endl <<flush);
	
	mutexGraphicalElements.lock();
	/* widget to create;
	 * +------------------------------------------------------------------+
	 * |  Select database   Load database    Load Fib object    Search    |
	 * |  -> pull down                                                    |
	 * |  new category                                                    |
	 * | +---------------------------------------------------------------+|
	 * | | pull down category1   pull cat1      ...  pull catn           ||
	 * | |                                                               ||
	 * | | Fib obj info 1.1      Fib info 2.1        Fib info n.1        ||
	 * | | Fib obj info 1.2      Fib info 2.2        Fib info n.2        ||
	 * | | ...                   ...                 ...                 ||
	 * | | Fib obj info 1.m      Fib info 2.m        Fib info n.m        ||
	 * | +---------------------------------------------------------------+|
	 * |  show   insert                                                   |
	 * +------------------------------------------------------------------+
	*/
	
	/* crate part:
	 * |  Select database   Load database    Load Fib object    Search    |
	 * |  -> pull down                                                    |
	 * |  new category                                                    |
	 */
	pLayoutTopMenue = new cFlowLayout();
	//TODO + button and dialog for create database (choose Fib objects to export in database)
/*TODO implement dialogs for:

	pButtonSelectDatabase = new QPushButton(tr("Select &database"), this );
	pButtonSelectDatabase->setCheckable( true );
	pButtonSelectDatabase->setAutoDefault( false );
	connect( pButtonSelectDatabase, SIGNAL( pressed() ),
		this, SLOT( selectDatabase() ) );
	pLayoutTopMenue->addWidget( pButtonSelectDatabase );
	
	pButtonLoadDatabase = new QPushButton(tr("&Load database"), this );
	pButtonLoadDatabase->setCheckable( true );
	pButtonLoadDatabase->setAutoDefault( false );
	connect( pButtonLoadDatabase, SIGNAL( pressed() ),
		this, SLOT( selectDatabase() ) );
	pLayoutTopMenue->addWidget( pButtonLoadDatabase );
*/
	
	pButtonLoadFibObject = new QPushButton(tr("Load &Fib object"), this );
	pButtonLoadFibObject->setCheckable( true );
	pButtonLoadFibObject->setAutoDefault( false );
	connect( pButtonLoadFibObject, SIGNAL( pressed() ),
		this, SLOT( loadFibObject() ) );
	pLayoutTopMenue->addWidget( pButtonLoadFibObject );
	
/*TODO implement dialogs for:
	pButtonSearchForFibObject = new QPushButton(tr("&Search"), this );
	pButtonSearchForFibObject->setCheckable( true );
	pButtonSearchForFibObject->setAutoDefault( false );
	connect( pButtonSearchForFibObject, SIGNAL( pressed() ),
		this, SLOT( searchForFibObject() ) );
	pLayoutTopMenue->addWidget( pButtonSearchForFibObject );
*/
	pButtonNewCategory = new QPushButton(tr("&New category"), this );
	pButtonNewCategory->setCheckable( true );
	pButtonNewCategory->setAutoDefault( false );
	connect( pButtonNewCategory, SIGNAL( pressed() ),
		this, SLOT( newFibObjectCategory() ) );
	pLayoutTopMenue->addWidget( pButtonNewCategory );
	
	/* crate part:
	 * | +---------------------------------------------------------------+|
	 * | | pull down category1   pull cat1      ...  pull catn           ||
	 * | |                                                               ||
	 * | | Fib obj info 1.1      Fib info 2.1        Fib info n.1        ||
	 * | | Fib obj info 1.2      Fib info 2.2        Fib info n.2        ||
	 * | | ...                   ...                 ...                 ||
	 * | | Fib obj info 1.m      Fib info 2.m        Fib info n.m        ||
	 * | +---------------------------------------------------------------+|
	 */
	
	mutexFibObjectInfos.lock();
	if ( liListsOfFibObjects.empty() ) {
		DEBUG_OUT_L2(<<"cDialogSelectFibObject("<<this <<")::createDialog() add minimum one list with Fib object infos"<<endl <<flush);
	
		//add minimum one list with Fib object infos
		cFibObjectInfoHandler * pFibObjectInfoHandler =
			cFibObjectInfoHandler::getInstance();
		
		if ( pFibObjectInfoHandler ) {
			const std::string szCategoryForAll =
				cFibObjectInfoHandler::getCategoryForAll();
			const cFibObjectCategory categoryForAll(
				QString( szCategoryForAll.c_str() ), true );
			
			cWidgetFibObjectInfos * pFirstWidgetFibObjectInfos =
				new cWidgetFibObjectInfos(
					pFibObjectInfoHandler->getPossibleFibObjectCategories(),
					pBaseFibObjectInfo, this );
			
			pFirstWidgetFibObjectInfos->setSelectedCategory( categoryForAll );
			
			connect( pFirstWidgetFibObjectInfos,
				SIGNAL( closeWidgetFibObjectInfos( cWidgetFibObjectInfos * ) ),
				this, SLOT( closeWidgetFibObjectInfos( cWidgetFibObjectInfos * ) ) );
			
			pFirstWidgetFibObjectInfos->registerListenerSelectedFibObjectInfo( this );
			liListsOfFibObjects.push_back( pFirstWidgetFibObjectInfos );
		}
	}//else minimum one category exists
	
	//create the list with the lists of Fib object info widgets
	pSplitterFibObjectInfos = new QSplitter( this );
	pSplitterFibObjectInfos->setOrientation( Qt::Horizontal );
	pSplitterFibObjectInfos->setChildrenCollapsible( false );
	//add all lists of Fib object info widgets
	for ( QList< cWidgetFibObjectInfos * >::const_iterator
			itrFibInfos = liListsOfFibObjects.begin();
			itrFibInfos != liListsOfFibObjects.end(); itrFibInfos++ ) {
		//add Fib object info widget
		pSplitterFibObjectInfos->addWidget( *itrFibInfos );
	}
	//create a scroll area for the lists of Fib info widgets
	pScrollAreaFibObjectInfos = new QScrollArea( this );
	//TODO? weg:
	//pScrollAreaFibObjectInfos->setBackgroundRole( QPalette::Dark );
	pScrollAreaFibObjectInfos->setWidget( pSplitterFibObjectInfos );
	pScrollAreaFibObjectInfos->setWidgetResizable( true );
	
	mutexFibObjectInfos.unlock();
	
	
	/* crate part:
	 * |  show   insert                                                   |
	 */
	pLayoutBottomMenue = new cFlowLayout();
	mutexFibObjectInfos.lock();
	
	pButtonShowSelectedFibObject = new QPushButton(tr("&Show"), this );
	pButtonShowSelectedFibObject->setCheckable( true );
	pButtonShowSelectedFibObject->setAutoDefault( false );
	connect( pButtonShowSelectedFibObject, SIGNAL( pressed() ),
		this, SLOT( showSelectedFibObject() ) );
	//activate botton just if a Fib object is selected
	pButtonShowSelectedFibObject->setEnabled( pBaseFibObjectInfo != NULL );
	pLayoutBottomMenue->addWidget( pButtonShowSelectedFibObject );
	
	if ( pAssociatedNode ) {
		//insert button to insert selected Fib object in associated node
		pButtonInsertSelectedFibObject = new QPushButton(tr("&Insert"), this );
		pButtonInsertSelectedFibObject->setCheckable( true );
		pButtonInsertSelectedFibObject->setAutoDefault( false );
		connect( pButtonInsertSelectedFibObject, SIGNAL( pressed() ),
			this, SLOT( insertSelectedFibObject() ) );
		//activate botton just if a Fib object is selected
		pButtonInsertSelectedFibObject->setEnabled( pBaseFibObjectInfo != NULL );
		pLayoutBottomMenue->addWidget( pButtonInsertSelectedFibObject );
	}
	mutexFibObjectInfos.unlock();
	
	//insert all elements in the main layout
	pLayoutMain = new QVBoxLayout( this );
	pLayoutMain->addLayout( pLayoutTopMenue );
	pLayoutMain->addWidget( pScrollAreaFibObjectInfos );
	pLayoutMain->addLayout( pLayoutBottomMenue );
	
	setLayout( pLayoutMain );
	
	mutexGraphicalElements.unlock();
}









