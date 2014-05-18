
//TODO check

/**
 * @file cFibObjectMainWindow
 * file name: cFibObjectMainWindow.cpp
 * @author Betti Oesterholz
 * @date 21.06.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for the main window of a Fib object.
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
 * This file implements a class for the main window of a Fib object.
 * The window will be associated to a Fib object it shows via a Fib node.
 * @see cFibNode
 * It will display as a central widget a graphical view of the Fib object
 * associated with it.
 */
/*
History:
21.06.2013  Oesterholz  created
13.04.2014  Oesterholz  insertSelectedFibObject() added
18.05.2014  Oesterholz  saveAs(): opens with last choosen file
*/


//TODO switches for test proposes
#define DEBUG
//#define DEBUG_FIB_OBJECT


#include "cFibObjectMainWindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QSettings>
#include <QVBoxLayout>
#include <QStyle>

#include <fstream>

#include "cFibElement.h"
#include "cRoot.h"

#include "cFibNode.h"
#include "cFibNodeHandler.h"
#include "cFibCreatorStatiHandler.h"
#include "eFibNodeChangedEvent.h"
#include "cMainWindowHandler.h"
#include "cFibGraphicsScene.h"
#include "cWidgetFibInputVariables.h"
#include "cFibPlainTextEdit.h"
#include "cFibGraphicsScene.h"
#include "cDialogSelectFibObject.h"



using namespace std;

using namespace fib::nCreator;
using namespace fib;



/**
 * parameter constructor for a Fib object node
 *
 * @param pInFibObject a pointer to the Fib object for the window to construct
 * 	@see pFibNode
 * @param bInIsChangebel true (standard value) if (the Fib element of)
 * 	the to create node is changebel, else false
 */
cFibObjectMainWindow::cFibObjectMainWindow( cFibElement * pInFibObject,
		const bool bInIsChangebel ):pFibNode( cFibNodeHandler::getInstance()->
			getNodeForFibObject( pInFibObject, this, bInIsChangebel ) ),
		pFibObjectGraphicsScene( NULL ), pFibObjectGraphicsView( NULL ),
		pCentralWidget( NULL ),
		pFibPlainTextEdit( NULL ), pDialogSelectFibObject( NULL ),
		strCurFilePath("") {
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::cFibObjectMainWindow( pInFibObject="<<pInFibObject<<") called"<<endl<<flush);
	
#ifdef DEBUG_FIB_OBJECT
	cout<<"cFibObjectMainWindow("<<this<<")::cFibObjectMainWindow( pInFibObject ) pInFibObject:"<<endl;
	if ( pInFibObject ) {
		pInFibObject->storeXml( cout );
	}else{
		cout<<"NULL";
	}
	cout<<"done"<<endl<<flush;
#endif //DEBUG_FIB_OBJECT
	
	setWindowTitle("Fib creator [*]");
	createSubWidgets();
	createActions();
	createMenus();
	createToolBars();
	createStatusBar();
	
	//restore the old session
	readSettings();
	
	connect( this, SIGNAL(signalWindowModified( bool )),
		this, SLOT(setWindowModified( bool )) );
	
	DEBUG_OUT_L3(<<"cFibObjectMainWindow("<<this<<")::cFibObjectMainWindow( pInFibObject="<<pInFibObject<<") done"<<endl<<flush);
}


/**
 * parameter constructor for a Fib object node
 *
 * @param pInFibNode a pointer to the Fib node object for the window to construct
 * 	@see pFibNode
 */
cFibObjectMainWindow::cFibObjectMainWindow( cFibNode * pInFibNode ):
		pFibNode( pInFibNode ),
		pFibObjectGraphicsScene( NULL ), pFibObjectGraphicsView( NULL ),
		pCentralWidget( NULL ),
		pFibPlainTextEdit( NULL ), pDialogSelectFibObject( NULL ),
		strCurFilePath("") {
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::cFibObjectMainWindow( pInFibNode="<<pInFibNode<<") called"<<endl<<flush);
	
#ifdef DEBUG_FIB_OBJECT
	cout<<"cFibObjectMainWindow("<<this<<")::cFibObjectMainWindow( pInFibNode ) Fib object :"<<endl;
	if ( pInFibNode && ( pInFibNode->getFibObjectConst() ) ) {
		pInFibNode->getFibObjectConst()->storeXml( cout );
	}else{
		cout<<"NULL";
	}
	cout<<endl;
#endif //DEBUG_FIB_OBJECT
	
	//create the graphic view of the Fib node
	pFibObjectGraphicsScene = new cFibGraphicsScene( pFibNode, this );
	
	setCentralWidget( new QGraphicsView( pFibObjectGraphicsScene, this ) );
	
	//create subwindows
	openDialogSelectFibObject();
	openPlainTextEdit();
	
	setWindowTitle("Fib creator [*]");
	createSubWidgets();
	createActions();
	createMenus();
	createToolBars();
	createStatusBar();
	
	//restore the old session
	readSettings();
	
	if ( pFibNode ) {
		pFibNode->registerNodeChangeListener( this );
	}
}


/**
 * destructor
 */
cFibObjectMainWindow::~cFibObjectMainWindow() {
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::~cFibObjectMainWindow() called"<<endl<<flush);
	
	//store the old session
	writeSettings();
	
	if ( pFibNode ) {
		pFibNode->unregisterNodeChangeListener( this );
	}
	//unregister this window at the main window handler
	cMainWindowHandler::unregisterMainWindowStatic( this );
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::~cFibObjectMainWindow() done"<<endl<<flush);
}


/**
 * @return a pointer to the Fib node object this window shows represents
 * 	@see pFibNode
 */
cFibNode * cFibObjectMainWindow::getFibNode() {
	
	return pFibNode;
}


/**
 * @return a const pointer to the Fib node object this window shows represents
 * 	@see pFibNode
 */
const cFibNode * cFibObjectMainWindow::getFibNode() const {
	
	return pFibNode;
}



/**
 * Event method
 * It will be called every time a Fib node (cFibNode), at which
 * this object is registered, was changed.
 *
 * @param pFibNode a pointer to the changed Fib node
 */
void cFibObjectMainWindow::fibNodeChangedEvent(
		const eFibNodeChangedEvent * pFibNodeChanged ) {
	
	
	if ( ( pFibNodeChanged != NULL ) && pFibNodeChanged->isDeleted() &&
			( pFibNodeChanged->getChangedNode() == pFibNode ) ) {
		/*node of this main window deleted
		 *-> set NULL as this this main window node*/
		pFibNode = NULL;
		return;
	}//else this main window node was not deleted
	
	emit signalWindowModified( true );
}


/**
 * @return the name of this class "cFibObjectMainWindow"
 */
std::string cFibObjectMainWindow::getName() const {
	
	return std::string( "cFibObjectMainWindow" );
}


/**
 * This method opens a Fib plain text edit window for this window Fib node.
 * @see pFibPlainTextEdit
 * @see pFibNode
 *
 * @return true if a Fib plain text edit window is open, else false
 */
bool cFibObjectMainWindow::openPlainTextEdit() {
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::openPlainTextEdit() called"<<endl<<flush);
	if ( pFibNode == NULL ) {
		//no Fib node to set
		DEBUG_OUT_L3(<<"cFibObjectMainWindow("<<this<<")::openPlainTextEdit() done no Fib node to set"<<endl<<flush);
		return false;
	}//else Fib node for this window exists
	if ( pFibPlainTextEdit == NULL ) {
		DEBUG_OUT_L3(<<"cFibObjectMainWindow("<<this<<")::openPlainTextEdit() create new plain text sub window"<<endl<<flush);
		pFibPlainTextEdit = new cFibPlainTextEdit( pFibNode, this );
		
		QDockWidget * pDockWidget = new QDockWidget( tr("Fib XML"), this );
		pDockWidget->setAllowedAreas(
			Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
		pDockWidget->setWidget( pFibPlainTextEdit );
		addDockWidget( Qt::RightDockWidgetArea, pDockWidget );
		
		mapOpenDockWidgets.insert( pFibPlainTextEdit, pDockWidget );
		
		return true;
	}/*else Fib plain text edit window already exists for this window
	-> just set node for it*/
	if ( pFibPlainTextEdit->getFibNode() == pFibNode ) {
		//correct node allready set -> nothing to do
		DEBUG_OUT_L3(<<"cFibObjectMainWindow("<<this<<")::openPlainTextEdit() correct node allready set -> nothing to do"<<endl<<flush);
		return true;
	}
	//set Fib node of this window
	DEBUG_OUT_L3(<<"cFibObjectMainWindow("<<this<<")::openPlainTextEdit() set Fib node of this window"<<endl<<flush);
	pFibPlainTextEdit->setFibObjectNode( pFibNode );
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::openPlainTextEdit() done"<<endl<<flush);
	return true;
}


/**
 * This method closes a Fib plain text edit window of this window.
 * @see pFibPlainTextEdit
 *
 * @return true if a Fib plain text edit window is closed, else false
 */
bool cFibObjectMainWindow::closePlainTextEdit() {
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::closePlainTextEdit() called"<<endl<<flush);
	if ( pFibPlainTextEdit == NULL ) {
		//Fib plain text edit window allready closed
		return true;
	}
	//delete Fib plain text edit window
	DEBUG_OUT_L3(<<"cFibObjectMainWindow("<<this<<")::closePlainTextEdit() delete Fib plain text edit window"<<endl<<flush);
	delete pFibPlainTextEdit;
	pFibPlainTextEdit = NULL;
	//find dock widget to delete it
	DEBUG_OUT_L3(<<"cFibObjectMainWindow("<<this<<")::closePlainTextEdit() find dock widget to delete it"<<endl<<flush);
	QMap< QWidget *, QDockWidget * >::iterator itrPlainTextDockWidget =
		mapOpenDockWidgets.find( pFibPlainTextEdit );
	if ( itrPlainTextDockWidget != mapOpenDockWidgets.end() ) {
		/*Error: no dock widget for Fib plain text edit window
		-> Fib plain text edit window should not exists*/
		return true;
	}//else dock widget for Fib plain text edit window found -> delete them
	//delete dock widget
	DEBUG_OUT_L3(<<"cFibObjectMainWindow("<<this<<")::closePlainTextEdit() delete dock widget"<<endl<<flush);
	QDockWidget * pDockWidget = itrPlainTextDockWidget.value();
	DEBUG_OUT_L4(<<"cFibObjectMainWindow("<<this<<")::closePlainTextEdit() removeDockWidget( pDockWidget )"<<endl<<flush);
	removeDockWidget( pDockWidget );
	DEBUG_OUT_L4(<<"cFibObjectMainWindow("<<this<<")::closePlainTextEdit() delete pDockWidget"<<endl<<flush);
	delete pDockWidget;
	DEBUG_OUT_L4(<<"cFibObjectMainWindow("<<this<<")::closePlainTextEdit() delete pDockWidget"<<endl<<flush);
	mapOpenDockWidgets.erase( itrPlainTextDockWidget );
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::closePlainTextEdit() done"<<endl<<flush);
	return true;
}

//TODO rework more methods for pDialogSelectFibObject

/**
 * This method opens a subwindow (QDockWidget) for selecting / choosing
 * Fib objects.
 * @see pDialogSelectFibObject
 *
 * @return true if the choose Fib object dialog could be opened, else false
 */
bool cFibObjectMainWindow::openDialogSelectFibObject() {
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::openDialogSelectFibObject() called"<<endl<<flush);
	if ( pDialogSelectFibObject == NULL ) {
		DEBUG_OUT_L3(<<"cFibObjectMainWindow("<<this<<")::openDialogSelectFibObject() create dialog to choose Fib object"<<endl<<flush);
		pDialogSelectFibObject = new cDialogSelectFibObject( this, pFibNode );
		
		QDockWidget * pDockWidget = new QDockWidget( tr("Choose Fib object"), this );
		pDockWidget->setAllowedAreas(
			Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
		pDockWidget->setWidget( pDialogSelectFibObject );
		addDockWidget( Qt::LeftDockWidgetArea, pDockWidget );
		
		mapOpenDockWidgets.insert( pDialogSelectFibObject, pDockWidget );
		
		return true;
	}/*else dialog to choose Fib object already exists for this window
	-> just set node for it*/
	if ( pDialogSelectFibObject->getAssociatedNode() == pFibNode ) {
		//correct node allready set -> nothing to do
		DEBUG_OUT_L3(<<"cFibObjectMainWindow("<<this<<")::openDialogSelectFibObject() correct node allready set -> nothing to do"<<endl<<flush);
		return true;
	}
	//set Fib node of this window
	DEBUG_OUT_L3(<<"cFibObjectMainWindow("<<this<<")::openDialogSelectFibObject() set Fib node of this window"<<endl<<flush);
	pDialogSelectFibObject->setAssociatedNode( pFibNode );
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::openDialogSelectFibObject() done"<<endl<<flush);
	return true;
}


/**
 * This method a subwindow (QDockWidget) for selecting / choosing
 * Fib objects.
 * @see pDialogSelectFibObject
 *
 * @return true if the choose Fib object dialog could be closed, else false
 */
bool cFibObjectMainWindow::closeDialogSelectFibObject() {
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::closeDialogSelectFibObject() called"<<endl<<flush);
	if ( pDialogSelectFibObject == NULL ) {
		//dialog to choose Fib object allready closed
		return true;
	}
	//delete dialog to choose Fib object
	DEBUG_OUT_L3(<<"cFibObjectMainWindow("<<this<<")::closeDialogSelectFibObject() delete dialog to choose Fib object"<<endl<<flush);
	delete pDialogSelectFibObject;
	pDialogSelectFibObject = NULL;
	//find dock widget to delete it
	DEBUG_OUT_L3(<<"cFibObjectMainWindow("<<this<<")::closeDialogSelectFibObject() find dock widget to delete it"<<endl<<flush);
	QMap< QWidget *, QDockWidget * >::iterator itrPlainTextDockWidget =
		mapOpenDockWidgets.find( pDialogSelectFibObject );
	if ( itrPlainTextDockWidget != mapOpenDockWidgets.end() ) {
		/*Error: no dock widget for dialog to choose Fib object
		-> dialog to choose Fib object should not exists*/
		return true;
	}//else dock widget for dialog to choose Fib object found -> delete them
	//delete dock widget
	DEBUG_OUT_L3(<<"cFibObjectMainWindow("<<this<<")::closeDialogSelectFibObject() delete dock widget"<<endl<<flush);
	QDockWidget * pDockWidget = itrPlainTextDockWidget.value();
	DEBUG_OUT_L4(<<"cFibObjectMainWindow("<<this<<")::closeDialogSelectFibObject() removeDockWidget( pDockWidget )"<<endl<<flush);
	removeDockWidget( pDockWidget );
	DEBUG_OUT_L4(<<"cFibObjectMainWindow("<<this<<")::closeDialogSelectFibObject() delete pDockWidget"<<endl<<flush);
	delete pDockWidget;
	DEBUG_OUT_L4(<<"cFibObjectMainWindow("<<this<<")::closeDialogSelectFibObject() delete pDockWidget"<<endl<<flush);
	mapOpenDockWidgets.erase( itrPlainTextDockWidget );
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::closeDialogSelectFibObject() done"<<endl<<flush);
	return true;
}



/**
 * This method creates the widgets used in this window.
 */
void cFibObjectMainWindow::createSubWidgets() {
	
	//remember old widgets
	cFibGraphicsScene * pOldFibObjectGraphicsScene = pFibObjectGraphicsScene;
	QGraphicsView * pOldFibObjectGraphicsView = pFibObjectGraphicsView;
	QWidget * pOldCentralWidget = pCentralWidget;
	
	//create the graphic view of the Fib node
	pFibObjectGraphicsScene = new cFibGraphicsScene( pFibNode, this );
	pFibObjectGraphicsView = new QGraphicsView( pFibObjectGraphicsScene, this );
	
	/*put the graphic view into a widged with the input variables of the
	 *graphical scene if needed*/
	cWidgetFibInputVariables * pInputVariablesWidged =
		pFibObjectGraphicsScene->getInputVariablesWidget();
	
	if ( pInputVariablesWidged ) {
		
		pCentralWidget = new QWidget( this );
		QVBoxLayout * pLayoutCentralWidget = new QVBoxLayout( pCentralWidget );
		pLayoutCentralWidget->setMargin( 0 );
		pLayoutCentralWidget->addWidget( pFibObjectGraphicsView );
		pLayoutCentralWidget->addWidget( pInputVariablesWidged );
		pCentralWidget->setLayout( pLayoutCentralWidget );
		
		setCentralWidget( pCentralWidget );
	}else{//central widged not needed
		setCentralWidget( pFibObjectGraphicsView );
	}
	
	if ( pOldFibObjectGraphicsScene != NULL ) {
		//delete the old graphic scene
		pOldFibObjectGraphicsScene->deleteLater();
	}
	if ( pOldFibObjectGraphicsView != NULL ) {
		//delete the old graphic view
		pOldFibObjectGraphicsView->deleteLater();
	}
	if ( pOldCentralWidget != NULL ) {
		//delete central widget
		pOldCentralWidget->deleteLater();
	}
	
	//create subwindows
	DEBUG_OUT_L3(<<"cFibObjectMainWindow("<<this<<")::cFibObjectMainWindow() create subwindows"<<endl<<flush);
	openDialogSelectFibObject();
	openPlainTextEdit();
}



/**
 * This method creates the actions used in this window.
 */
void cFibObjectMainWindow::createActions() {
	//TODO include recources ":/images/*.png"
	
	
	/*
	 * TODO
	 * QStyle()
	 * QIcon QStyle::standardIcon ( StandardPixmap standardIcon, const QStyleOption * option = 0, const QWidget * widget = 0 ) const
	 * 
	 * QStyle::SP_FileIcon
	 * QStyle::SP_DialogHelpButton
	 * QStyle::SP_DialogOpenButton 	41 	Icon for a standard Open button in a QDialogButtonBox.
	QStyle::SP_DialogSaveButton 	42 	Icon for a standard Save button in a QDialogButtonBox.
	QStyle::SP_DialogCloseButton 	43 	Icon for a standard Close button in a QDialogButtonBox.
	QStyle::SP_DialogApplyButton 	44 	Icon for a standard Apply button in a QDialogButtonBox.
	QStyle::SP_DialogResetButton 	45 	Icon for a standard Reset button in a QDialogButtonBox.
	QStyle::SP_DialogDiscardButton
	QStyle::SP_ArrowBack 	53 	Equivalent to SP_ArrowLeft when the current layout direction is Qt::LeftToRight, otherwise SP_ArrowRight.
	QStyle::SP_ArrowForward 	54 	Equivalent to SP_ArrowRight when the current layout direction is Qt::LeftToRight, otherwise SP_ArrowLeft.
	 */
	//QStyle style;
	
	//action for new Fib object
	//TODO
	pActNew = new QAction( QIcon(":/images/icon/iconNew.png"), tr("&New"), this );
	//pActNew = new QAction( style.standardIcon(  ), tr("&New"), this );
	
	pActNew->setShortcuts( QKeySequence::New );
	pActNew->setStatusTip( tr("Create a new Fib object") );
	connect( pActNew, SIGNAL( triggered() ), this, SLOT( newFibObject() ) );
	//action for open file for loading Fib object
	//TODO
	pActOpen = new QAction( QIcon(":/images/icon/iconOpen.png"), tr("&Open..."), this );
	//pActOpen = new QAction( style.standardIcon( QStyle::SP_FileIcon ), tr("&Open"), this );
	
	pActOpen->setShortcuts( QKeySequence::Open );
	pActOpen->setStatusTip( tr("Open an existing Fib object file") );
	connect( pActOpen, SIGNAL( triggered() ), this, SLOT( open() ) );
	//action for saving Fib object
	//TODO
	pActSave = new QAction( QIcon::fromTheme("document-save", QIcon(":images/icon/iconSave.png") ),
		tr("&Save"), this );
	//pActSave = new QAction( style.standardIcon( QStyle::SP_DialogSaveButton ), tr("&Save"), this );
	
	pActSave->setShortcuts( QKeySequence::Save );
	pActSave->setStatusTip( tr("Save the Fib object to disk") );
	connect( pActSave, SIGNAL( triggered() ), this, SLOT( save() ) );
	//action for saving Fib object with given file name
	pActSaveAs = new QAction( QIcon(":/images/icon/iconSaveAs.png"), tr("Save &As..."), this );
	pActSaveAs->setShortcuts( QKeySequence::SaveAs );
	pActSaveAs->setStatusTip( tr("Save the Fib object under a new name") );
	connect( pActSaveAs, SIGNAL( triggered() ), this, SLOT( saveAs() ) );
	//TODO
	//action for exit the application
	pActExit = new QAction( tr("E&xit"), this );
	pActExit->setShortcuts( QKeySequence::Quit );
	pActExit->setStatusTip( tr("Exit the application") );
	connect ( pActExit, SIGNAL( triggered() ), this, SLOT( close() ) );
	
	//action for close this window
	pActCloseWindow = new QAction( tr("Close"), this );
	//pActCloseWindow->setShortcuts( QKeySequence::Quit );
	pActCloseWindow->setStatusTip( tr("Close the window") );
	connect ( pActCloseWindow, SIGNAL( triggered() ), this, SLOT( closeWindow() ) );
	/*TODO implement?
	//action for cuting part Fib object
	pActCut = new QAction( QIcon(":/images/icon/iconCut.png"), tr("Cu&t"), this );
	pActCut->setShortcuts( QKeySequence::Cut);
	pActCut->setStatusTip( tr("Cut the current selection's contents to the "
		"clipboard") );
	//TODO implement actions connections:
	//connect( pActCut, SIGNAL( triggered() ), pFibObjectGraphicsScene, SLOT( cut() ) );
	//action for copy part Fib object
	pActCopy = new QAction( QIcon(":/images/icon/iconCopy.png"), tr("&Copy"), this );
	pActCopy->setShortcuts( QKeySequence::Copy);
	pActCopy->setStatusTip( tr("Copy the current selection's contents to the "
		"clipboard") );
	//connect( pActCopy, SIGNAL( triggered() ), pFibObjectGraphicsScene, SLOT( copy() ) );
	//action for inserting a copied part Fib object
	pActPaste = new QAction( QIcon(":/images/icon/iconPaste.png"), tr("&Paste"), this );
	pActPaste->setShortcuts( QKeySequence::Paste);
	pActPaste->setStatusTip( tr("Paste the clipboard's contents into the current "
		"selection") );
	//connect( pActPaste, SIGNAL( triggered() ), pFibObjectGraphicsScene, SLOT( paste() ) );
	
	//TODO delete Fib object
	*/
	
	//create action to togle the Fib plain text view
	pActTogleShowPlaintext = new QAction( QIcon::fromTheme("accessories-text-editor",
		QIcon(":/images/icon/iconPlaintext.png") ), tr("&Plain text view"), this );
	//TODO?: pActTogleShowPlaintext->setShortcuts( QKeySequence::Paste);
	pActTogleShowPlaintext->setStatusTip( tr("Togels the plain text view ") );
	connect( pActTogleShowPlaintext, SIGNAL( triggered() ), this, SLOT( toglePlainTextWindow() ) );
	
	//TODO for pDialogSelectFibObject
	//togleDialogSelectFibObject()
	
	//action for show about this application information
	pActAbout = new QAction( tr("&About"), this );
	pActAbout->setStatusTip( tr("Show the application's About box") );
	connect( pActAbout, SIGNAL( triggered() ), this, SLOT( about() ) );
	
	//deactivate the actions to copy Fib subobjects
	/*TODO impement signals in pFibObjectGraphicsScene copyAvailable()
	 ? The Fib node should hold the copyAvailable() signal ?
	 */
	/*TODO implement?
	pActCut->setEnabled( false );
	connect( pFibObjectGraphicsScene, SIGNAL( copyAvailable(bool) ),
		pActCut, SLOT( setEnabled(bool) ) );
	pActCopy->setEnabled( false );
	connect( pFibObjectGraphicsScene, SIGNAL( copyAvailable(bool) ),
		pActCopy, SLOT( setEnabled(bool) ) );
	*/
	
	
	//action for saving Fib object
	//TODO
	/*two modes:
	 *	- select item: ":images/icon/iconMousePointing.png"
	 * - draw object: QIcon::fromTheme("insert-object") or ":images/icon/iconMouseDrawing.png"*/
	pActMouseModePointing = new QAction( QIcon(":images/icon/iconMousePointing.png"),
		tr("Mouse &pointing"), this );
	//pActMouseModePointing->setShortcuts( QKeySequence::Save );
	pActMouseModePointing->setStatusTip( tr("Change mouse mode to pointer (for selecting objects)") );
	connect( pActMouseModePointing, SIGNAL( triggered() ),
		cFibCreatorStatiHandler::getInstance(),
		SLOT( setMouseModeToPointing() ) );
	
	pActMouseModeDrawing = new QAction( QIcon::fromTheme( "insert-object",
		QIcon(":images/icon/iconMouseDrawing.png") ),
		tr("Mouse &drawing"), this );
	//pActMouseModeDrawing->setShortcuts( QKeySequence::Save );
	pActMouseModeDrawing->setStatusTip( tr("Change mouse mode to drawing (for drawing objects)") );
	connect( pActMouseModeDrawing, SIGNAL( triggered() ),
		cFibCreatorStatiHandler::getInstance(),
		SLOT( setMouseModeToDrawing() ) );
	
}


/**
 * This method creates the menu used in this window.
 */
void cFibObjectMainWindow::createMenus() {
	//create file menu
	pMenuFile = menuBar()->addMenu( tr("&File") );
	pMenuFile->addAction( pActNew );
	pMenuFile->addAction( pActOpen );
	pMenuFile->addAction( pActSave );
	pMenuFile->addAction( pActSaveAs );
	pMenuFile->addSeparator();
	pMenuFile->addAction( pActCloseWindow );
	pMenuFile->addAction( pActExit );
	//create edit menu
	pMenuEdit = menuBar()->addMenu( tr("&Edit") );
	/*TODO implement?
	pMenuEdit->addAction( pActCut );
	pMenuEdit->addAction( pActCopy );
	pMenuEdit->addAction( pActPaste );
	*/
	//TODO add menu for other Fib object views
	//create edit menu
	pMenuEdit = menuBar()->addMenu( tr("&Window") );
	pMenuEdit->addAction( pActTogleShowPlaintext );
	
	
	//create modus menu
	pMenuModus = menuBar()->addMenu( tr("&Modus") );
	pMenuModus->addAction( pActMouseModePointing );
	pMenuModus->addAction( pActMouseModeDrawing );
	
	
	//add seperator (for Motif-based styles, there help should be on right side)
	menuBar()->addSeparator();
	//create help menu
	pMenuHelp = menuBar()->addMenu( tr("&Help") );
	//TODO help page: pMenuHelp->addAction(aboutQtAct);
	pMenuHelp->addAction( pActAbout);
	
	
}


/**
 * This method creates the tool bar used in this window.
 */
void cFibObjectMainWindow::createToolBars() {
	//tool bar for mode actions
	pToolBarFile = addToolBar( tr("Modus") );
	pToolBarFile->addAction( pActMouseModePointing );
	pToolBarFile->addAction( pActMouseModeDrawing );
	//tool bar for file actions
	pToolBarFile = addToolBar( tr("File") );
	pToolBarFile->addAction( pActNew );
	pToolBarFile->addAction( pActOpen );
	pToolBarFile->addAction( pActSave );
	//tool bar for edit actions
	pToolBarEdit = addToolBar( tr("Edit") );
	/*TODO implement?
	pToolBarEdit->addAction( pActCut );
	pToolBarEdit->addAction( pActCopy );
	pToolBarEdit->addAction( pActPaste );
	*/
	//TODO add tool bar for other Fib object views
	//TODO into  tool bar for other Fib object views
	pToolBarFile->addAction( pActTogleShowPlaintext );
	
}


/**
 * This method creates the status bar used in this window.
 */
void cFibObjectMainWindow::createStatusBar() {
	statusBar()->showMessage(tr("Ready"));
	/*show state of Fib object: valid,
		 invalid: no root, Fib objects missing, Variables missing, ...
		 warning: domains missing, values to great, subobject outside bounderies, ...
	.. */
}


/**
 * This method will read the settings for this window and restores the
 * window to it.
 * @see QSettings
 */
void cFibObjectMainWindow::readSettings() {
	
	QSettings settings("Fib development", "Fib creator");
	QPoint pos = settings.value("mainWindow/pos", QPoint( 0, 0 ) ).toPoint();
	QSize size = settings.value("mainWindow/size", sizeHint() ).toSize();
	resize( size );
	move( pos);
}


/**
 * This method will write the settings of this window.
 * @see QSettings
 */
void cFibObjectMainWindow::writeSettings() {
	
	QSettings settings("Fib development", "Fib creator");
	settings.setValue("mainWindow/pos", pos() );
	settings.setValue("mainWindow/size", size() );
}



/**
 * This method handels close events.
 *
 * @param pEventClose a pointer to the close event to andle
 */
void cFibObjectMainWindow::closeEvent( QCloseEvent * pEventClose ) {
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::closeEvent( pEventClose="<<pEventClose<<") called"<<endl<<flush);
	//check if the Fib object should be saved
	if ( maybeSave() ) {
		//Fib object is save
		writeSettings();
		cMainWindowHandler::closeMainWindowStatic( this );
		pEventClose->accept();
	}else{//Fib object not saved -> ignore close event
		pEventClose->ignore();
	}
}


/**
 * This slot is called if a new file for a new Fib object should be crated.
 */
void cFibObjectMainWindow::newFile() {
	
	//TODO? difference to newFibObject()
	
	if ( isWindowModified() ) {
		//if unsaved changes -> create new window with empty Fib object
		cMainWindowHandler::createNewMainWindowForEmptyFibObjectStatic();
		
	}else{//set empty Fib object in this window
		cFibElement * pEmptyFibObject =
			cMainWindowHandler::getEmptyFibObjectStatic();
#ifdef DEBUG_FIB_OBJECT
		cout<<"cFibObjectMainWindow("<<this<<")::newFile() created empty Fib object:"<<endl;
		if ( pEmptyFibObject ) {
			pEmptyFibObject->storeXml( cout );
		}else{
			cout<<"NULL";
		}
		cout<<endl;
#endif //DEBUG_FIB_OBJECT
		if ( pEmptyFibObject == NULL ) {
			//no new Fib object created
			return;
		}
		setFibObject( pEmptyFibObject );
	}
	setCurrentFile("");
}


/**
 * This slot is called if a new Fib object should be crated.
 */
void cFibObjectMainWindow::newFibObject() {
	
	//TODO? difference to newFibObject()
	
	if ( maybeSave() ) {
		//old Fib object saved -> set empty Fib object in this window
		cFibElement * pEmptyFibObject =
			cMainWindowHandler::getEmptyFibObjectStatic();
#ifdef DEBUG_FIB_OBJECT
		cout<<"cFibObjectMainWindow("<<this<<")::newFibObject() created empty Fib object:"<<endl;
		if ( pEmptyFibObject ) {
			pEmptyFibObject->storeXml( cout );
		}else{
			cout<<"NULL";
		}
		cout<<endl;
#endif //DEBUG_FIB_OBJECT
		if ( pEmptyFibObject == NULL ) {
			//no new Fib object created
			return;
		}
		setFibObject( pEmptyFibObject );
	}
	setCurrentFile("");
}


/**
 * This slot is called if a Fib object should be loaded from a file.
 *
 * @return true if a new Fib object was loaded, else false
 */
bool cFibObjectMainWindow::open() {
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::open() called"<<endl<<flush);
	if ( isWindowModified() ) {
		//if unsaved changes -> create new window with loaded Fib object
		return ( cMainWindowHandler::openMainWindowForFibObjectFromFileStatic() != NULL );
	}//else set loaded Fib object in this window
	string strLoadedFibObject( "" );
	
	cFibElement * pLoadedFibObject =
		cMainWindowHandler::openFibObjectFromFileStatic( &strLoadedFibObject );
#ifdef DEBUG_FIB_OBJECT
	cout<<"cFibObjectMainWindow("<<this<<")::open() loaded Fib object:"<<endl;
	if ( pLoadedFibObject ) {
		pLoadedFibObject->storeXml( cout );
	}else{
		cout<<"NULL";
	}
	cout<<endl;
#endif //DEBUG_FIB_OBJECT
	if ( pLoadedFibObject == NULL ) {
		//no new Fib object loaded
		DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::open() done no new Fib object loaded"<<endl<<flush);
		return false;
	}//Fib object loaded
	strCurFilePath = strLoadedFibObject.c_str();
	if ( setFibObject( pLoadedFibObject ) ) {
		DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::open() done new Fib object loaded and set"<<endl<<flush);
		return true;
	}//else Fib object not set -> delete it
	pLoadedFibObject->deleteObject();
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::open() done else Fib object not set"<<endl<<flush);
	return false;
}


/**
 * This slot is called if a Fib object should be stored to the actual set file.
 * @see strCurFilePath
 * @see storeFibObject()
 * @see saveAs()
 *
 * @return true if the Fib object was saved, else false
 */
bool cFibObjectMainWindow::save() {
	if ( strCurFilePath.isEmpty() ) {
		//ask for file name
		return saveAs();
	}//else just save Fib object
	return storeFibObject( strCurFilePath );
}


/**
 * This slot is called if a Fib object should be stored to a file, which
 * should be specified.
 * @see strCurFilePath
 * @see storeFibObject()
 * @see save()
 *
 * @return true if the Fib object was saved, else false
 */
bool cFibObjectMainWindow::saveAs() {
	//ask for a file name for the file where to store the Fib object
	//to set start file
	QSettings settings("Fib development", "Fib creator");
	QFileDialog fileDialogSaveAs( this, tr("Save Fib object"), settings.value(
			"mainWindow/fileDialog/lastFile",
				QDir::homePath() + QDir::separator() + "*.xml" ).toString() );
	fileDialogSaveAs.setNameFilter(tr("Fib XML (*.xml);;Fib compressed (*.fib)"));
	fileDialogSaveAs.setAcceptMode( QFileDialog::AcceptSave );
	
	fileDialogSaveAs.setFileMode( QFileDialog::AnyFile );
	
	if ( fileDialogSaveAs.exec() ) {
		//a file was choosen
		QStringList liFileNames = fileDialogSaveAs.selectedFiles();
		if ( liFileNames.size() != 1 ) {
			//not one file choosen -> return NULL
			return NULL;
		}
		//store Fib object to file
		if ( liFileNames.front().isEmpty() ) {
			//no file name choosen -> can't save
			return false;
		}
		//store actual file as last used file
		settings.setValue("mainWindow/fileDialog/lastFile", liFileNames.front() );
		
		return storeFibObject( liFileNames.front() );
	}//else
	
	return false;
}


/**
 * This slot will close this window.
 */
bool cFibObjectMainWindow::closeWindow() {
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::closeWindow() called"<<endl<<flush);
	if ( maybeSave() ) {
		//old Fib object saved -> close this window
		cMainWindowHandler::closeMainWindowStatic( this );
		
		return true;
	}//else don't close
	return false;
}


/**
 * This slot will action to togle the Fib plain text view.
 *
 * @return true if the plain text view is shown, else false
 */
bool cFibObjectMainWindow::toglePlainTextWindow() {
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::toglePlainTextWindow() called"<<endl<<flush);
	if ( ( pFibPlainTextEdit == NULL ) || ( ! pFibPlainTextEdit->isVisible() ) ) {
		//no plain text view exists or is open -> open it
		return openPlainTextEdit();
	}//else close plain text view
	return ( ! closePlainTextEdit() );
}


/**
 * This slot will action to togle the dialog to choose Fib objects view.
 *
 * @see pDialogSelectFibObject
 * @see openDialogSelectFibObject()
 * @see closeDialogSelectFibObject()
 * @return true if the dialog to choose Fib objects is shown, else false
 */
bool cFibObjectMainWindow::togleDialogSelectFibObject() {
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::togleDialogSelectFibObject() called"<<endl<<flush);
	if ( ( pDialogSelectFibObject == NULL ) ||
			( ! pDialogSelectFibObject->isVisible() ) ) {
		//no the dialog to choose Fib objects exists or is open -> open it
		return openDialogSelectFibObject();
	}//else close the dialog to choose Fib objects
	return ( ! closeDialogSelectFibObject() );
}


/**
 * This slot shows the about (this application) information.
 */
void cFibObjectMainWindow::about() {
	QMessageBox::about( this, tr("About Fib creator"),
		tr("<b>Fib creator</b> is an application to create Fib objects."
			"The Fib creator is free software (GNU GPL3 "
			"<a href='http://www.gnu.org/licenses/'>www.gnu.org/licenses/</a>"
			"You can find information about Fib and the Fib creator online "
			"on the Fib web page <a href='http://www.Fib-development.org/'>www.Fib-development.org</a>"
			"and the Fib github repository "
			"<a href='http://www.github.com/BioKom/Fib/'>www.github.com/BioKom/Fib/</a> .") );
}


/**
 * This method asks, if the Fib object was modified, if the Fib object
 * should be saved.
 *
 * @return true if the user says it is Ok, else false (user cancels)
 */
bool cFibObjectMainWindow::maybeSave() {
	
	//check if the Fib object was modified
	if ( isWindowModified() )  {
		//if the Fib object was modified -> ask if chenges should be saved
		QMessageBox::StandardButton buttonMaybeSave;
		buttonMaybeSave = QMessageBox::warning( this, tr("Fib creator"),
			tr("The Fib object has been modified.\n"
				"Do you want to save your changes?"),
			QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel );
		//check pushed button result
		if ( buttonMaybeSave == QMessageBox::Save ) {
			//try to save the Fib object
			return save();
		}else if ( buttonMaybeSave == QMessageBox::Cancel ) {
			//abort action
			return false;
		}else{//Fib object should not be saved (buttonMaybeSave==QMessageBox::Discard)
			return true;
		}
	}//else the Fib object was not modified -> don't need to save
	return true;
}


/**
 * This method will restore a Fib object from the file with the given path
 * into this window.
 *
 * @param szFibObjectPath the path to the Fib object file to restore
 * @return true if a Fib object was restored, else false
 */
bool cFibObjectMainWindow::loadFibObject( const QString & szFibObjectPath ) {
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::loadFibObject() called"<<endl<<flush);
	if ( ! maybeSave() ) {
		//if unsaved changes -> create new window with loaded Fib object
		return false;
	}//else load the Fib object into this window
	cFibElement * pLoadedFibObject =
		cMainWindowHandler::openFibObjectFromFileStatic(
			szFibObjectPath.toStdString() );
#ifdef DEBUG_FIB_OBJECT
		cout<<"cFibObjectMainWindow("<<this<<
			")::loadFibObject( szFibObjectPath="<<
			szFibObjectPath.toStdString()<<") loaded Fib object:"<<endl;
		if ( pLoadedFibObject ) {
			pLoadedFibObject->storeXml( cout );
		}else{
			cout<<"NULL";
		}
		cout<<endl;
#endif //DEBUG_FIB_OBJECT
	if ( pLoadedFibObject == NULL ) {
		//no Fib object loaded
		DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::loadFibObject() done no Fib object loaded"<<endl<<flush);
		return false;
	}
	setFibObject( pLoadedFibObject );
	
	setCurrentFile( szFibObjectPath );
	statusBar()->showMessage( tr("Fib object loaded"), 2000 );
	setWindowModified( false );
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::loadFibObject() done Fib object loaded and set"<<endl<<flush);
	return true;
}

/**
 * This method will store the Fib object for the window into the given file.
 *
 * @param strFilePath the filename (and path) wher to store the Fib object to
 * @return true if the Fib object was store, else false
 */
bool cFibObjectMainWindow::storeFibObject( const QString & strFilePath ) {
	
	if ( ( pFibNode == NULL ) || ( pFibNode->getMasterRoot() == NULL ) ) {
		//no Fib object to store given
		QMessageBox msgBox( this );
		msgBox.setWindowTitle("Fib creator save Fib object");
		msgBox.setText( tr( "No Fib object to store to \"%1\"." ).
			arg( strFilePath ) );
		msgBox.setIcon( QMessageBox::Critical );
		msgBox.exec();
		return false;
	}
	
	if ( strFilePath.isEmpty() ) {
		//no file name given
		QMessageBox msgBox( this );
		msgBox.setWindowTitle("Fib creator save Fib object");
		msgBox.setText( tr( "Error: Cannot write file \"%1\"." ).
			arg( strFilePath ) );
		msgBox.setIcon( QMessageBox::Critical );
		msgBox.exec();
		return false;
	}
	//pointer for the to stored Fib object
	cFibElement * pFibObjectToStore = pFibNode->getMasterRoot();
#ifdef DEBUG_FIB_OBJECT
	cout<<"cFibObjectMainWindow("<<this<<")::storeFibObject( strFilePath="<<
		strFilePath.toStdString()<<") Fib object to store:"<<endl;
	if ( pFibObjectToStore ) {
		pFibObjectToStore->storeXml( cout );
	}else{
		cout<<"NULL";
	}
	cout<<endl;
#endif //DEBUG_FIB_OBJECT
	
	//store depending on file ending
	if ( strFilePath.endsWith( ".xml", Qt::CaseInsensitive ) ) {
		//TODO if XML editor is given -> update editor text and write it
		
		//store to file in Xml format
		ofstream outFile( strFilePath.toStdString().c_str() );
		
		//storing Fib object in the Xml format to the file strFilePath
		statusBar()->showMessage( tr("storing Fib object in XML") );
		const bool bStoreSuccesfull = pFibObjectToStore->storeXml( outFile );
		
		if ( ! bStoreSuccesfull ) {
			//Error
			QMessageBox msgBox( this );
			msgBox.setWindowTitle("Fib creator save Fib object");
			msgBox.setText( tr( "Error: Storing the Fib object "
				"in Fib XML format to file \"%1\" failed." ).
				arg( strFilePath ) );
			msgBox.setIcon( QMessageBox::Critical );
			msgBox.exec();
			statusBar()->showMessage(
				tr("Error: storing Fib object in XML"), 2000 );
			return false;
		}//else storing OK
	}else{//store to file in compressed format
		if ( pFibNode->isChangebel() ) {
			//generate the domains Fib object needs
			if ( pFibObjectToStore->getType() == 'r' ) {
				((cRoot*)pFibObjectToStore)->generateNeededDomains();
				pFibNode->fibObjectChanged( this );
			}
		}
		ofstream outFile( strFilePath.toStdString().c_str(),
			ios_base::out | ios_base::binary );
		
		//storing Fib object in the compressed format to the file strFilePath
		statusBar()->showMessage( tr("storing Fib object in compressed format") );
		const bool bStoreSuccesfull = pFibObjectToStore->store( outFile );
		
		if ( ! bStoreSuccesfull ) {
			//Error
			QMessageBox msgBox( this );
			msgBox.setWindowTitle("Fib creator save Fib object");
			msgBox.setText( tr( "Error: Storing the Fib object "
				"in Fib compressed format to file \"%1\" failed." ).
				arg( strFilePath ) );
			msgBox.setIcon( QMessageBox::Critical );
			msgBox.exec();
			statusBar()->showMessage(
				tr("Error: storing Fib object in compressed format"), 2000 );
			return false;
		}//else storing OK
	}//end if store depending on file ending
	//Fib object stored
	setCurrentFile( strFilePath );
	statusBar()->showMessage(
		tr("Fib object stored"), 2000 );
	
	setWindowModified( false );
	return true;
}


/**
 * This method will set the current file name for the Fib object (without
 * loading it).
 * @see strCurFilePath
 * @see loadFibObject()
 *
 * @param strFileName the file name to set
 */
void cFibObjectMainWindow::setCurrentFile( const QString & strFileName ) {
	
	strCurFilePath = strFileName;
	//Fib object not stored in new set file (use loadFibObject())
	
	QString strShownName = strippedName( strCurFilePath );
	if ( strShownName.isEmpty() ) {
		//no valid file name given
		strShownName = tr( "untitled" );
	}
	setWindowFilePath( strShownName );
	//TODO? window=Fib object modified?
	setWindowModified( true );
}


/**
 * This function will return the file name without the folder path.
 *
 * @param strFullFilePath the full file path (including folder part)
 * @return the file name without the folder path
 */
QString cFibObjectMainWindow::strippedName( const QString & strFullFilePath ) {
	
	return QFileInfo( strFullFilePath ).fileName();
}


/**
 * This method will set the given Fib object in this window.
 * Beware: If the Fib object was set (returned true) the Fib node handler
 * 	will handel the given Fib object (e. g. It will delete the Fib object,
 * 	so don't delete it yourself).
 * @see cFibNodeHandler
 *
 * @param pNewFibObject a pointer to the Fib object to set for this window
 * @return true if the given Fib object was set, else false
 */
bool cFibObjectMainWindow::setFibObject( cFibElement * pNewFibObject ) {
	
#ifdef DEBUG_FIB_OBJECT
	cout<<"cFibObjectMainWindow("<<this<<")::setFibObject( pNewFibObject ) new Fib object to set:"<<endl;
	if ( pNewFibObject ) {
		pNewFibObject->storeXml( cout );
	}else{
		cout<<"NULL";
	}
	cout<<endl;
#endif //DEBUG_FIB_OBJECT
	//evalue the Fib node object for the Fib object
	cFibNode * pNewFibNode = cFibNodeHandler::getInstance()->getNodeForFibObject(
		pNewFibObject, this );
	
	if ( pNewFibNode == NULL ) {
		//no node for the Fib object
		return false;
	}
	//set the created Fib node object
	return setFibObjectNode( pNewFibNode );
}


/**
 * This method will set the given Fib (node) object in this window.
 * Beware: If the Fib (node) object was set (returned true) the Fib node
 * 	handler will handel the given Fib object (e. g. It will delete the
 * 	Fib object, so don't delete it yourself).
 * @see cFibNodeHandler
 *
 * @param pNewFibObject a pointer to the Fib object to set for this window
 * @return true if the given Fib object was set, else false
 */
bool cFibObjectMainWindow::setFibObjectNode( cFibNode * pNewFibObjectNode ) {
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::setFibObjectNode( pNewFibObjectNode="<<pNewFibObjectNode<<" ) called"<<endl<<flush);
#ifdef DEBUG_FIB_OBJECT
	cout<<"cFibObjectMainWindow("<<this<<")::setFibObjectNode( pNewFibObjectNode ) Fib object :"<<endl;
	if ( pNewFibObjectNode && ( pNewFibObjectNode->getFibObjectConst() ) ) {
		pNewFibObjectNode->getFibObjectConst()->storeXml( cout );
	}else{
		cout<<"NULL";
	}
	cout<<endl;
#endif //DEBUG_FIB_OBJECT
	if ( pNewFibObjectNode == NULL ) {
		//no node given -> can't set
		DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::setFibObjectNode( pNewFibObjectNode="<<pNewFibObjectNode<<" ) done: no node given -> can't set"<<endl<<flush);
		return false;
	}
	if ( pFibNode == pNewFibObjectNode ) {
		//correct node set -> nothing to do
		DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::setFibObjectNode( pNewFibObjectNode="<<pNewFibObjectNode<<" ) done: correct node set (set="<<pFibNode<<" to set="<<pNewFibObjectNode<<") -> nothing to do"<<endl<<flush);
		return true;
	}
	cFibNode * pFibNodeOld = pFibNode;
	
	pFibNode = pNewFibObjectNode;
	pFibNode->registerNodeChangeListener( this );
	if ( pFibNodeOld ) {
		pFibNodeOld->unregisterNodeChangeListener( this );
	}
	//also set for all subwindows (= child elements)
	if ( pFibPlainTextEdit ) {
		//set for Fib plain text edit window
		DEBUG_OUT_L3(<<"cFibObjectMainWindow("<<this<<")::setFibObjectNode( pNewFibObjectNode="<<pNewFibObjectNode<<" ) set for Fib plain text edit window"<<endl<<flush);
		pFibPlainTextEdit->setFibObjectNode( pFibNode );
	}
	//set and update pFibObjectGraphicsScene
	if ( pFibObjectGraphicsScene ) {
		DEBUG_OUT_L3(<<"cFibObjectMainWindow("<<this<<")::setFibObjectNode( pNewFibObjectNode="<<pNewFibObjectNode<<" ) set and update pFibObjectGraphicsScene"<<endl<<flush);
		pFibObjectGraphicsScene->setFibObjectNode( pNewFibObjectNode );
		//addapt the size of the central widget
		DEBUG_OUT_L3(<<"cFibObjectMainWindow("<<this<<")::setFibObjectNode( pNewFibObjectNode="<<pNewFibObjectNode<<" ) addapt the size of the central widget"<<endl<<flush);
		QWidget * pLocalCentralWidget = centralWidget();
		if ( pLocalCentralWidget ) {
			//TODO dosn't work
			//adapt size of central widget
			const QSize sizeMainWindow  = size();
			
			QSize sizeMainCentralWidget = pLocalCentralWidget->size();
			
			const int iWidthMainWindowHalf =  ( sizeMainWindow.width() / 2 );
			const int iWidthGraphicsScene  = pFibObjectGraphicsScene->width();
			if ( ( sizeMainCentralWidget.width() < iWidthMainWindowHalf ) &&
					( sizeMainCentralWidget.width() < iWidthGraphicsScene ) ) {
				/*new central widget width =
				 *   min( iWidthMainWindowHalf, iWidthGraphicsScene )*/
				DEBUG_OUT_L4(<<"new central widget width = min( iWidthMainWindowHalf="<<iWidthMainWindowHalf<<", iWidthGraphicsScene="<<iWidthGraphicsScene<<" )"<<endl<<flush);
				sizeMainCentralWidget.setWidth(
					(iWidthMainWindowHalf < iWidthGraphicsScene) ?
					iWidthMainWindowHalf : iWidthGraphicsScene );
			}
			const int iHeightMainWindowHalf =  ( sizeMainWindow.height() / 2 );
			const int iHeightGraphicsScene  = pFibObjectGraphicsScene->height();
			if ( ( sizeMainCentralWidget.height() < iHeightMainWindowHalf ) &&
					( sizeMainCentralWidget.height() < iHeightGraphicsScene ) ) {
				/*new central widget height =
				 *   min( iHeightMainWindowHalf, iHeightGraphicsScene )*/
				DEBUG_OUT_L4(<<"new central widget width = min( iHeightMainWindowHalf="<<iHeightMainWindowHalf<<", iHeightGraphicsScene="<<iHeightGraphicsScene<<" )"<<endl<<flush);
				sizeMainCentralWidget.setHeight(
					(iHeightMainWindowHalf < iHeightGraphicsScene) ?
					iHeightMainWindowHalf : iHeightGraphicsScene );
			}
			
			DEBUG_OUT_L4(<<"pLocalCentralWidget->resize( sizeMainCentralWidget=("<<sizeMainCentralWidget.width()<<", "<<sizeMainCentralWidget.height()<<") );"<<endl<<flush);
			pLocalCentralWidget->resize( sizeMainCentralWidget );
		}
	}//end if set and update pFibObjectGraphicsScene
	
	DEBUG_OUT_L4(<<"cFibObjectMainWindow("<<this<<")::setFibObjectNode( pNewFibObjectNode="<<pNewFibObjectNode<<" ): setWindowModified( false );"<<endl<<flush);
	setWindowModified( false );
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::setFibObjectNode( pNewFibObjectNode="<<pNewFibObjectNode<<" ) done"<<endl<<flush);
	return true;
}


/**
 * This method sets the input variable widgets for the central grapical
 * view / scene.
 *
 * @see pFibNode
 * @see pWidgetInputVariables
 * @see evalueInputVariables()
 * @see getNumberOfInputVariables()
 * @param pWidgetFibInputVariables a pointer to the widget with the
 * 	input variables to set
 * 	Beware: This object will handle the given widget object (e.g. it
 * 		will delete it).
 */
void cFibObjectMainWindow::setInputVariablesWidgetForCentralGrapical(
		cWidgetFibInputVariables * pNewWidgetFibInputVariables ) {
	
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this <<")::setInputVariablesWidgetForCentralGrapical( pNewWidgetFibInputVariables="<<pNewWidgetFibInputVariables<<" ) called"<<endl<<flush);
	//remember old widgets
	QWidget * pOldCentralWidget = pCentralWidget;
	
	/*put the graphic view into a widged with the input variables of the
	 *graphical scene if needed*/
	if ( pNewWidgetFibInputVariables ) {
		DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this <<")::setInputVariablesWidgetForCentralGrapical( pNewWidgetFibInputVariables="<<pNewWidgetFibInputVariables<<" ) central widged needed"<<endl<<flush);
		
		pCentralWidget = new QWidget( this );
		QVBoxLayout * pLayoutCentralWidget = new QVBoxLayout( pCentralWidget );
		pLayoutCentralWidget->setMargin( 0 );
		pLayoutCentralWidget->addWidget( pFibObjectGraphicsView );
		pLayoutCentralWidget->addWidget( pNewWidgetFibInputVariables );
		pCentralWidget->setLayout( pLayoutCentralWidget );
		
		setCentralWidget( pCentralWidget );
	}else{//central widged not needed
		DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this <<")::setInputVariablesWidgetForCentralGrapical( pNewWidgetFibInputVariables="<<pNewWidgetFibInputVariables<<" ) central widged not needed (no input variables widget)"<<endl<<flush);
		setCentralWidget( pFibObjectGraphicsView );
	}
	
	if ( pOldCentralWidget != NULL ) {
		//delete old central widget
		DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this <<")::setInputVariablesWidgetForCentralGrapical( pNewWidgetFibInputVariables="<<pNewWidgetFibInputVariables<<" ) delete old central widget"<<endl<<flush);
		pOldCentralWidget->deleteLater();
	}
	DEBUG_OUT_L2(<<"cFibObjectMainWindow("<<this<<")::setInputVariablesWidgetForCentralGrapical( pNewWidgetFibInputVariables="<<pNewWidgetFibInputVariables<<" ) done"<<endl<<flush);
}


/**
 * This method will insert the selected Fib object into the associated
 * (/represented) Fib Node.
 * If possible the inserted Fib object will be inserted on the given position.
 *
 * @see cFibNode::insertSelectedFibObject()
 * @see pFibNode
 * @see pDialogSelectFibObject
 * @see getFibNode()
 * @param poiInsertPosition the position on which the Fib object should
 * 	be inserted
 * @return true if the Fib object was inserted, else false
 */
bool cFibObjectMainWindow::insertSelectedFibObject(
		const QPoint & poiInsertPosition ) {
	
	if ( pDialogSelectFibObject ) {
		//redirect call to  pDialogSelectFibObject
		return pDialogSelectFibObject->insertSelectedFibObject( poiInsertPosition );
	}//no selected Fib object -> can't insert
	return false;
}


/**
 * This method will insert the selected Fib object into the associated
 * (/represented) Fib Node.
 * If possible the inserted Fib object will be inserted on the given position.
 *
 * @see cFibNode::insertSelectedFibObject()
 * @see pFibNode
 * @see pDialogSelectFibObject
 * @see getFibNode()
 * @param poiInsertPosition the position on which the Fib object should
 * 	be inserted
 * @return true if the Fib object was inserted, else false
 */
bool cFibObjectMainWindow::insertSelectedFibObject(
		const QPointF & poiInsertPosition ) {
	
	if ( pDialogSelectFibObject ) {
		//redirect call to  pDialogSelectFibObject
		return pDialogSelectFibObject->insertSelectedFibObject( poiInsertPosition );
	}//no selected Fib object -> can't insert
	return false;
}



/**
 * @return a hint for a good size of this window
 */
QSize cFibObjectMainWindow::sizeHint() const {
	
	return QSize( 640, 480 );
}


















