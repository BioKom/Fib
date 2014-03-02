
//TODO check

/**
 * @file cDialogSelectFibObject
 * file name: cDialogSelectFibObject.h
 * @author Betti Oesterholz
 * @date 18.10.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a dialog to select a Fib object.
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
 * This file specifies a class for a dialog to select a Fib object.
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
18.10.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_DIALOG_SELECT_FIB_OBJECT_H__
#define ___FIB__NCREATOR__C_DIALOG_SELECT_FIB_OBJECT_H__


#include "version.h"

#include <string>

#include <QObject>
#include <QList>
#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QSplitter>
#include <QVBoxLayout>
#include <QMutex>

#include "lSelectedWidgetFibObjectInfo.h"


//forward declarations
class cFlowLayout;

namespace fib{

namespace nCreator{

//forward declarations
class cWidgetFibObjectInfos;
class cFibNode;
class cFibObjectInfo;

class cDialogSelectFibObject: public QWidget,
		public lSelectedWidgetFibObjectInfo{
	Q_OBJECT
public:

	/**
	 * The standard constructor for the dialog to select Fib objects.
	 *
	 * @param pParent a pointer the parent of this new Fib object info widget
	 * @param pInAssociatedNode to the associated Fib object node, or NULL if non exists
	 * 	@see pAssociatedNode
	 */
	cDialogSelectFibObject( QWidget * pParent = NULL,
		cFibNode * pInAssociatedNode = NULL );
	
	/**
	 * A constructor for the dialog to select Fib objects.
	 *
	 * @param pInAssociatedNode to the associated Fib object node, or NULL if non exists
	 * 	@see pAssociatedNode
	 */
	cDialogSelectFibObject( cFibNode * pInAssociatedNode );
	
	/**
	 * The destructor.
	 */
	virtual ~cDialogSelectFibObject();
	
	
	/**
	 * @return the name of this class "cDialogSelectFibObject"
	 */
	virtual std::string getName() const;
	
	
	/**
	 * This method returns the selected Fib object info.
	 * It is the base for all relativ categories.
	 *
	 * @see pBaseFibObjectInfo
	 * @see setSelectedFibObjectInfo()
	 * @return a pointer to the selected Fib object info
	 */
	cFibObjectInfo * getSelectedFibObjectInfo();

	/**
	 * This method returns the selected Fib object info.
	 * It is the base for all relativ categories.
	 *
	 * @see pBaseFibObjectInfo
	 * @see setSelectedFibObjectInfo()
	 * @return a const pointer to the selected Fib object info
	 */
	const cFibObjectInfo * getSelectedFibObjectInfo() const;

	/**
	 * This method sets the selected Fib object info.
	 * It will be the base for all relativ categories.
	 *
	 * @see pBaseFibObjectInfo
	 * @see getSelectedFibObjectInfo()
	 * @param pSelectedFibObjectInfo a pointer to the selected Fib object
	 * 	info to set
	 */
	void setSelectedFibObjectInfo(
		cFibObjectInfo * pSelectedFibObjectInfo = NULL );
	
	/**
	 * This method sets the selected Fib object info widget.
	 * It will be the base for all relativ categories.
	 *
	 * @see pBaseFibObjectInfo
	 * @see getSelectedFibObjectInfo()
	 * @param pWidgetFibObjectInfo a pointer to the selected widget of the
	 * 	Fib object info to set
	 */
	void setSelectedFibObjectInfo(
		cWidgetFibObjectInfo * pWidgetFibObjectInfo = NULL );
	
	/**
	 * Event method
	 * This method will be called if an Fib object info widget was
	 * selected.
	 *
	 * @see lSelectedWidgetFibObjectInfo
	 * @param pWidgetFibObjectInfo a pointer to the Fib object info
	 * 	widget which was selected
	 */
	virtual void selectWidgetFibObjectInfo(
		const cWidgetFibObjectInfo * pWidgetFibObjectInfo );
	
	
	/**
	 * This method returns associated Fib object node, or NULL if non exists.
	 * If you insert a selected Fib object this will be the Fib object node
	 * in which Fib object it will be inserted.
	 *
	 * @see pAssociatedNode
	 * @see setAssociatedNode()
	 * @return a pointer to the associated Fib object node
	 */
	cFibNode * getAssociatedNode();

	/**
	 * This method returns associated Fib object node, or NULL if non exists.
	 * If you insert a selected Fib object this will be the Fib object node
	 * in which Fib object it will be inserted.
	 *
	 * @see pAssociatedNode
	 * @see setAssociatedNode()
	 * @return a const pointer to the associated Fib object node
	 */
	const cFibNode * getAssociatedNode() const;

	/**
	 * This method sets the selected Fib object info.
	 * It will be the base for all relativ categories.
	 *
	 * @see pAssociatedNode
	 * @see getAssociatedNode()
	 * @param pAssociatedNode a pointer to the the associated Fib object node
	 */
	void setAssociatedNode( cFibNode * pAssociatedNode = NULL );
	
protected slots:
	
	/**
	 * This slot opens a dialog to select a Fib database.
	 * @see pButtonSelectDatabase
	 */
	void selectDatabase();
	
	/**
	 * This slot opens a dialog to load a Fib object database.
	 * @see pButtonLoadDatabase
	 */
	void loadDatabase();
	
	/**
	 * This slot opens a dialog to load a Fib object.
	 * @see pButtonLoadFibObject
	 */
	void loadFibObject();
	
	/**
	 * This slot opens a dialog to search for a Fib object.
	 * @see pButtonSearchForFibObject
	 */
	void searchForFibObject();
	
	/**
	 * This slot creates a Fib object list for a new category.
	 * @see pButtonNewCategory
	 */
	void newFibObjectCategory();
	
	/**
	 * This slot close a cWidgetFibObjectInfos widget.
	 * It will be removed from the list of lists of Fib object infos and
	 * deleted from memory.
	 *
	 * @see cWidgetFibObjectInfos::closeWidgetFibObjectInfos()
	 * @param pWidgetFibObjectInfos a pointer to the cWidgetFibObjectInfos
	 * 	widget which should be closed
	 */
	void closeWidgetFibObjectInfos( cWidgetFibObjectInfos * pWidgetFibObjectInfos );
	
	/**
	 * This slot will show the selected Fib object.
	 * @see pButtonShowSelectedFibObject
	 * @see pBaseFibObjectInfo
	 * @see cMainWindowHandler
	 * @see cFibObjectMainWindow
	 */
	void showSelectedFibObject();
	
	/**
	 * This slot will insert the selected Fib object in the activ main window.
	 * @see pButtonInsertSelectedFibObject
	 * @see pBaseFibObjectInfo
	 * @see cFibNode
	 */
	void insertSelectedFibObject();
	
protected:
	
//members
	
	/**
	 * The base Fib object info for all relativ categories (the Fib object
	 * info object to which they are relativ, e. g. to which it is the same type).
	 * @see getSelectedFibObjectInfo
	 * @see setSelectedFibObjectInfo()
	 */
	cFibObjectInfo * pBaseFibObjectInfo;
	
	/**
	 * The list with the list of Fib objects (infos) to choose from.
	 *
	 * The data for the part:
	 * | +---------------------------------------------------------------+|
	 * | | pull down category1   pull cat1      ...  pull catn           ||
	 * | |                                                               ||
	 * | | Fib obj info 1.1      Fib info 2.1        Fib info n.1        ||
	 * | | Fib obj info 1.2      Fib info 2.2        Fib info n.2        ||
	 * | | ...                   ...                 ...                 ||
	 * | | Fib obj info 1.m      Fib info 2.m        Fib info n.m        ||
	 * | +---------------------------------------------------------------+|
	 */
	QList< cWidgetFibObjectInfos * > liListsOfFibObjects;
	
	/*TODO implement a way to delete a existing Fib object info list
	 signal closeWidgetFibObjectInfos( this ) in cWidgetFibObjectInfos
	 */
	
	/**
	 * This area is for scrolling the lists of list of Fib object infos.
	 * It contains the splitter with all Fib object info widgets.
	 * @see liListsOfFibObjects
	 * @see pSplitterFibObjectInfos
	 */
	QScrollArea * pScrollAreaFibObjectInfos;
	
	/**
	 * The splitter with the list Fib object info widgets.
	 * @see liListsOfFibObjects
	 * @see pScrollAreaFibObjectInfos
	 */
	QSplitter * pSplitterFibObjectInfos;

	/**
	 * A pointer to the associated Fib object node, or NULL if non exists.
	 * If you insert a selected Fib object this will be the Fib object node
	 * in which Fib object it will be inserted.
	 * @see insertSelectedFibObject()
	 * @see getAssociatedNode()
	 * @see setAssociatedNode()
	 */
	cFibNode * pAssociatedNode;
	
	/**
	 * Mutex to lock access to the list of Fib object info objects.
	 * Lock the mutex if you use one of the following containers:
	 * @see liListsOfFibObjects
	 * @see pScrollAreaFibObjectInfos
	 * @see pSplitterFibObjectInfos
	 * @see pBaseFibObjectInfo
	 * @see pAssociatedNode
	 */
	mutable QMutex mutexFibObjectInfos;
	
	/**
	 * Top menue:
	 * |  Select database   Load database    Load Fib object    Search    |
	 * |  -> pull down                                                    |
	 * |  new category                                                    |
	 */
	/// The pointer to the button to select a Fib object database.
	QPushButton * pButtonSelectDatabase;
	
	/// The pointer to the button to load a Fib object database.
	QPushButton * pButtonLoadDatabase;
	
	/// The pointer to the button to load a Fib object.
	QPushButton * pButtonLoadFibObject;
	
	/// The pointer to the button to search for a Fib object.
	QPushButton * pButtonSearchForFibObject;
	
	/// The pointer to the button to create a Fib object list for a new category.
	QPushButton * pButtonNewCategory;
	
	
	/**
	 * The layout for the top menue.
	 * It contains:
	 * 	@see pButtonSelectDatabase
	 * 	@see pButtonLoadDatabase
	 * 	@see pButtonLoadFibObject
	 * 	@see pButtonSearchForFibObject
	 * 	@see pButtonNewCategory
	 */
	cFlowLayout * pLayoutTopMenue;
	
	/**
	 * Bottom menue:
	 * |  show   insert                                                   |
	 */
	
	/**
	 * The pointer to the button to show the selected Fib object.
	 * @see pBaseFibObjectInfo
	 */
	QPushButton * pButtonShowSelectedFibObject;
	
	/**
	 * The pointer to the button to insert the selected Fib object.
	 * @see pBaseFibObjectInfo
	 */
	QPushButton * pButtonInsertSelectedFibObject;
	
	/**
	 * The layout for the bottom menue.
	 * It contains:
	 * 	@see pButtonShowSelectedFibObject
	 * 	@see pButtonInsertSelectedFibObject
	 */
	cFlowLayout * pLayoutBottomMenue;
	
	/**
	 * The layout for the dialoge to select a Fib object.
	 * @see pLayoutTopMenue
	 * @see pScrollAreaFibObjectInfos
	 * @see pLayoutBottomMenue
	 */
	QVBoxLayout * pLayoutMain;
	
	/**
	 * Mutex to lock access to the graphical elements to display.
	 * Lock the mutex if you use one of the following containers:
	 * @see pLayoutMain
	 * @see pLayoutTopMenue
	 * 	@see pButtonSelectDatabase
	 * 	@see pButtonLoadDatabase
	 * 	@see pButtonLoadFibObject
	 * 	@see pButtonSearchForFibObject
	 * 	@see pButtonNewCategory
	 * @see pScrollAreaFibObjectInfos
	 * @see pSplitterFibObjectInfos
	 * @see pLayoutBottomMenue
	 * 	@see pButtonShowSelectedFibObject
	 * 	@see pButtonInsertSelectedFibObject
	 */
	mutable QMutex mutexGraphicalElements;
	

private:
	
	/**
	 * This method will create this dialog.
	 */
	void createDialog();
	
};//end class cDialogSelectFibObject

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_DIALOG_SELECT_FIB_OBJECT_H__





