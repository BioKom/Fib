
//TODO check

/**
 * @file cFibObjectMainWindow
 * file name: cFibObjectMainWindow.h
 * @author Betti Oesterholz
 * @date 21.06.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for the main window of a Fib object.
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
 * This file specifies a class for the main window of a Fib object.
 * The window will be associated to a Fib object it shows via a Fib node.
 * @see cFibNode
 * It will display as a central widget a graphical view of the Fib object
 * associated with it.
 */
/*
History:
21.06.2013  Oesterholz  created
13.04.2014  Oesterholz  insertSelectedFibObject() insert selected Fib object
*/


#ifndef ___FIB__NCREATOR__C_FIB_OBJECT_MAIN_WINDOW_H__
#define ___FIB__NCREATOR__C_FIB_OBJECT_MAIN_WINDOW_H__


#include "version.h"

#include <QMap>

#include <QMainWindow>
#include <QDockWidget>
#include <QAction>
#include <QMenu>
#include <QCloseEvent>
#include <QGraphicsView>

#include "lFibNodeChanged.h"


namespace fib{

//forward declarations
class cFibElement;

namespace nCreator{

//cyclic dependencies
class cMainWindowHandler;

//forward declarations
class cFibNode;
class cFibNodeHandler;
class cFibPlainTextEdit;
class cWidgetFibInputVariables;
class cFibGraphicsScene;
class cDialogSelectFibObject;


class cFibObjectMainWindow: public QMainWindow, public lFibNodeChanged{
		Q_OBJECT

friend class cMainWindowHandler;
public:
	
	/**
	 * parameter constructor for a Fib object node
	 *
	 * @param pInFibObject a pointer to the Fib object for the window to construct
	 * 	@see pFibNode
	 * @param bInIsChangebel true (standard value) if (the Fib element of)
	 * 	the to create node is changebel, else false
	 */
	explicit cFibObjectMainWindow( cFibElement * pInFibObject, const bool bInIsChangebel=true );
	
	/**
	 * parameter constructor for a Fib object node
	 *
	 * @param pInFibNode a pointer to the Fib node object for the window to construct
	 * 	@see pFibNode
	 */
	explicit cFibObjectMainWindow( cFibNode * pInFibNode );
	
	/**
	 * destructor
	 */
	virtual ~cFibObjectMainWindow();
	
	
	/**
	 * @return a pointer to the Fib node object this window shows represents
	 * 	@see pFibNode
	 */
	cFibNode * getFibNode();
	
	/**
	 * @return a const pointer to the Fib node object this window shows represents
	 * 	@see pFibNode
	 */
	const cFibNode * getFibNode() const;
	
	
	/**
	 * Event method
	 * It will be called every time a Fib node (cFibNode), at which
	 * this object is registered, was changed.
	 *
	 * @param pFibNode a pointer to the changed Fib node
	 */
	virtual void fibNodeChangedEvent(
		const eFibNodeChangedEvent * pFibNodeChanged );
	
	
	/**
	 * @return the name of this class "cFibObjectMainWindow"
	 */
	virtual std::string getName() const;
	
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
	virtual bool setFibObjectNode( cFibNode * pNewFibObjectNode );
	
	
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
	virtual void setInputVariablesWidgetForCentralGrapical(
		cWidgetFibInputVariables * pNewWidgetFibInputVariables );
	
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
	virtual bool insertSelectedFibObject( const QPoint & poiInsertPosition );
	
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
	virtual bool insertSelectedFibObject( const QPointF & poiInsertPosition );
	
signals:
	/**
	 * This signal signals whether the document shown in the window has
	 * unsaved changes.
	 *
	 * @see QWidget::windowModified
	 * @see QWidget::setWindowModified()
	 * @param bWindowModified if true the document shown in the window has
	 * 	unsaved changes, else not
	 */
	void signalWindowModified( const bool bWindowModified );
	
protected:
	
	/**
	 * This method opens a Fib plain text edit window for this window Fib node.
	 * @see pFibPlainTextEdit
	 * @see pFibNode
	 *
	 * @return true if a Fib plain text edit window could be opened, else false
	 */
	bool openPlainTextEdit();
	
	/**
	 * This method closes a Fib plain text edit window of this window.
	 * @see pFibPlainTextEdit
	 *
	 * @return true if a Fib plain text edit window could be closed, else false
	 */
	bool closePlainTextEdit();
	
	/**
	 * This method opens a subwindow (QDockWidget) for selecting / choosing
	 * Fib objects.
	 * @see pDialogSelectFibObject
	 *
	 * @return true if the choose Fib object dialog could be opened, else false
	 */
	bool openDialogSelectFibObject();
	
	/**
	 * This method a subwindow (QDockWidget) for selecting / choosing
	 * Fib objects.
	 * @see pDialogSelectFibObject
	 *
	 * @return true if the choose Fib object dialog could be closed, else false
	 */
	bool closeDialogSelectFibObject();
	
	/**
	 * This method creates the widgets used in this window.
	 */
	virtual void createSubWidgets();
	
	/**
	 * This method creates the actions used in this window.
	 */
	virtual void createActions();
	
	/**
	 * This method creates the menu used in this window.
	 */
	virtual void createMenus();
	
	/**
	 * This method creates the tool bar used in this window.
	 */
	virtual void createToolBars();
	
	/**
	 * This method creates the status bar used in this window.
	 */
	virtual void createStatusBar();
	
	/**
	 * This method will read the settings for this window and restores the
	 * window to it.
	 * @see QSettings
	 */
	virtual void readSettings();
	
	/**
	 * This method will write the settings of this window.
	 * @see QSettings
	 */
	virtual void writeSettings();
	
	/**
	 * This method handels close events.
	 *
	 * @param pEventClose a pointer to the close event to andle
	 */
	virtual void closeEvent( QCloseEvent * pEventClose );
	
	/**
	 * This method asks, if the Fib object was modified, if the Fib object
	 * should be saved.
	 *
	 * @return true if the user says it is Ok, else false (user cancels)
	 */
	virtual bool maybeSave();
	
	/**
	 * This method will restore a Fib object from the file with the given path
	 * into this window.
	 *
	 * @param szFibObjectPath the path to the Fib object file to restore
	 * @return true if a Fib object was restored, else false
	 */
	bool loadFibObject( const QString & szFibObjectPath );
	
	/**
	 * This method will store the Fib object for the window into the given file.
	 *
	 * @param strFilePath the filename (and path) wher to store the Fib object to
	 * @return true if the Fib object was store, else false
	 */
	bool storeFibObject( const QString & strFilePath );
	
	/**
	 * This method will set the current file name for the Fib object (without
	 * loading it).
	 * @see strCurFilePath
	 * @see loadFibObject()
	 *
	 * @param strFileName the file name to set
	 */
	virtual void setCurrentFile( const QString & strFileName );
	
	/**
	 * This function will return the file name without the folder path.
	 *
	 * @param strFullFilePath the full file path (including folder part)
	 * @return the file name without the folder path
	 */
	QString strippedName( const QString & strFullFilePath );
	
	/**
	 * @return a hint for a good size of this window
	 */
	virtual QSize sizeHint() const;
	
//Fib object methods
	
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
	virtual bool setFibObject( cFibElement * pNewFibObject );
	
	

//members
	
	/**
	 * A pointer to the Fib node object for this window
	 */
	cFibNode * pFibNode;
	
	
	/**
	 * The main graphics scene where the Fib object is shown.
	 * @see pFibNode
	 * @see pFibObjectGraphicsView
	 * TODO set  Qt::WA_OpaquePaintEvent for QGraphicsView (overwrite all background)
	 */
	cFibGraphicsScene * pFibObjectGraphicsScene;
	
	/**
	 * The main graphics view for the graphics scene where the Fib object is
	 * shown.
	 * @see pFibObjectGraphicsScene
	 */
	QGraphicsView * pFibObjectGraphicsView;
	
	/**
	 * The central widget of this main window.
	 * It should contain the main graphical wiew (or scene) and the input
	 * variable widget of the main graphical scene.
	 * If NULL no input variable widget of the main graphical scene exists
	 * and the graphical view will be used directly as the central widget of
	 * this main window.
	 *
	 * @see pFibObjectGraphicsScene
	 * @see pFibObjectGraphicsView
	 */
	QWidget * pCentralWidget;
	
	
	/**
	 * A mep of the open dock widgets of this window.
	 */
	QMap< QWidget *, QDockWidget * > mapOpenDockWidgets;
	
	/**
	 * A subwindow (QDockWidget) for editing Fib objects in (Fib XML) plain text.
	 */
	cFibPlainTextEdit * pFibPlainTextEdit;
	
	/**
	 * A subwindow (QDockWidget) for selecting / choosing Fib objects.
	 * @see cDialogSelectFibObject
	 * @see openDialogSelectFibObject()
	 * @see closeDialogSelectFibObject()
	 */
	cDialogSelectFibObject * pDialogSelectFibObject;
	
	
	/**
	 * The name of the current loaded Fib object.
	 */
	QString strCurFilePath;
	
	///file menu
	QMenu * pMenuFile;
	///edit menu
	QMenu * pMenuEdit;
	///edit menu
	QMenu * pMenuWindow;
	///help menu
	QMenu * pMenuHelp;
	///modus menu
	QMenu * pMenuModus;
	///file tool bar
	QToolBar * pToolBarFile;
	///edit tool bar
	QToolBar * pToolBarEdit;
	
	/**
	 * Actions
	 */
	///action for new Fib object
	QAction * pActNew;
	///action for open file for loading Fib object
	QAction * pActOpen;
	///action for saving Fib object
	QAction * pActSave;
	///action for saving Fib object with given file name
	QAction * pActSaveAs;
	///action for close this window
	QAction * pActCloseWindow;
	///action for exit the application
	QAction * pActExit;
	
	///action for cuting part Fib object
	QAction * pActCut;
	///action for copy part Fib object
	QAction * pActCopy;
	///action for inserting a copied part Fib object
	QAction * pActPaste;
	
	/**
	 * Action to togle the Fib plain text view.
	 * @see pFibPlainTextEdit
	 * @see toglePlainTextWindow()
	 **/
	QAction * pActTogleShowPlaintext;
	
	///action for show about this application information
	QAction * pActAbout;
	
	/**
	 * Action for changing the mouse mode to pointing.
	 * @see cFibCreatorStatiHandler::setMouseModeToPointing()
	 */
	QAction * pActMouseModePointing;
	
	/**
	 * Action for changing the mouse mode to drawing.
	 * @see cFibCreatorStatiHandler::setMouseModeToDrawing()
	 */
	QAction * pActMouseModeDrawing;
	
	
private slots:
	
	/**
	 * This slot is called if a new file for a new Fib object should be crated.
	 */
	void newFile();
	
	/**
	 * This slot is called if a new Fib object should be crated.
	 */
	void newFibObject();
	
	/**
	 * This slot is called if a Fib object should be loaded from a file.
	 *
	 * @return true if a new Fib object was loaded, else false
	 */
	bool open();
	
	/**
	 * This slot is called if a Fib object should be stored to the actual set file.
	 * @see strCurFilePath
	 * @see storeFibObject()
	 * @see saveAs()
	 *
	 * @return true if the Fib object was saved, else false
	 */
	bool save();
	
	/**
	 * This slot is called if a Fib object should be stored to a file, which
	 * should be specified.
	 * @see strCurFilePath
	 * @see storeFibObject()
	 * @see save()
	 *
	 * @return true if the Fib object was saved, else false
	 */
	bool saveAs();
	
	/**
	 * This slot will close this window.
	 */
	bool closeWindow();
	
	/**
	 * This slot will action to togle the Fib plain text view.
	 *
	 * @see pFibPlainTextEdit
	 * @see openPlainTextEdit()
	 * @see closePlainTextEdit()
	 * @return true if the plain text view is shown, else false
	 */
	bool toglePlainTextWindow();
	
	/**
	 * This slot will action to togle the dialog to choose Fib objects view.
	 *
	 * @see pDialogSelectFibObject
	 * @see openDialogSelectFibObject()
	 * @see closeDialogSelectFibObject()
	 * @return true if the dialog to choose Fib objects is shown, else false
	 */
	bool togleDialogSelectFibObject();
	
	/**
	 * This slot shows the about (this application) information.
	 */
	void about();
	
};//end class cFibObjectMainWindow

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_OBJECT_MAIN_WINDOW_H__





