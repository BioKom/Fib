
//TODO check

/**
 * @file cWidgetFibObjectInfos
 * file name: cWidgetFibObjectInfos.h
 * @author Betti Oesterholz
 * @date 18.10.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a list of Fib object infos to select a
 * Fib object from.
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
 * This file specifies a class for a list of Fib object infos to select a
 * Fib object from.
 *
 * It should look like:
 *
 * +---------------------+
 * | pull down category  |
 * |                     |
 * | Fib obj info 1      |
 * | Fib obj info 2      |
 * | ...                 |
 * | Fib obj info m      |
 * +---------------------+
 *
 * pull down category:
 *    - categories for the Fib objects to show in the list below
 *    possibel category typs:
 *       - relative categories: same type (sameType), is contained (isContained), ...
 *       - absolute categories: all, typs like: objects, people, ...
 *       (first category list has just absolute)
 *
 * @see cWidgetFibObjectInfo
 * @see cFibObjectInfo
 * @see cFibObjectInfoHandler
 */
/*
History:
18.10.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_WIDGET_FIB_OBJECT_INFOS_H__
#define ___FIB__NCREATOR__C_WIDGET_FIB_OBJECT_INFOS_H__


#include "version.h"

#include <string>
#include <set>

#include <QObject>
#include <QWidget>
#include <QList>
#include <QMutex>
#include <QComboBox>
#include <QScrollArea>
#include <QSplitter>
#include <QSplitter>
#include <QPushButton>
#include <QHBoxLayout>

#include "lSelectedWidgetFibObjectInfo.h"


namespace fib{

namespace nCreator{

//forward declarations
class cWidgetFibObjectInfo;
class cFibObjectCategory;
class cFibObjectInfo;


class cWidgetFibObjectInfos: public QWidget,
		public lSelectedWidgetFibObjectInfo{
	Q_OBJECT
public:
	
	/**
	 * The parameter constructor.
	 *
	 * @see liInPossibleCategories a list with the possible categories for
	 * 	the Fib objects of this list.
	 * 	Note: The first category of the list will be selected
	 * 	@see liPossibleCategories
	 * @param uiInMaxFibObjectInfos the maximal number of Fib object info
	 * 	widgets to display ( liFibObjectInfos.size() <= uiMaxFibObjectInfos),
	 * 	if 0 the default value will be taken
	 * 	@see uiInMaxFibObjectInfos
	 * 	@see liFibObjectInfos
	 * @param pParent a pointer the parent of this new Fib object info widget
	 */
	explicit cWidgetFibObjectInfos(
		const QList< cFibObjectCategory > & liInPossibleCategories,
		const unsigned int uiInMaxFibObjectInfos = 0,
		QWidget * pParent = NULL );
	
	/**
	 * The parameter constructor.
	 *
	 * @see liInPossibleCategories a list with the possible categories for
	 * 	the Fib objects of this list.
	 * 	Note: The first category of the list will be selected
	 * 	@see liPossibleCategories
	 * @param pInBaseFibObjectInfo If this list is for a relativ category,
	 * 	the Fib object info object to which it is relativ (e. g. to which
	 * 	it is the same type).
	 * 	@see pBaseFibObjectInfo
	 * @param uiInMaxFibObjectInfos the maximal number of Fib object info
	 * 	widgets to display ( liFibObjectInfos.size() <= uiMaxFibObjectInfos),
	 * 	if 0 the default value will be taken
	 * 	@see uiInMaxFibObjectInfos
	 * 	@see liFibObjectInfos
	 * @param pParent a pointer the parent of this new Fib object info widget
	 */
	cWidgetFibObjectInfos(
		const QList< cFibObjectCategory > & liInPossibleCategories,
		cFibObjectInfo * pInBaseFibObjectInfo,
		const unsigned int uiInMaxFibObjectInfos = 0,
		QWidget * pParent = NULL );
	
	/**
	 * The destructor
	 */
	virtual ~cWidgetFibObjectInfos();
	
	/**
	 * @return the name of this class "cWidgetFibObjectInfos"
	 */
	virtual std::string getName() const;
	
	/**
	 * @return the selected category for the Fib objects of this list
	 * 	@see liPossibleCategories
	 * 	@see indexSelectedCategory
	 */
	virtual cFibObjectCategory getSelectedCategory() const;
	
	/**
	 * This method sets the selected category for the Fib objects of this list.
	 * It will also load the Fib objects for the selected category, if possible.
	 *
	 * @see liPossibleCategories
	 * @see indexSelectedCategory
	 * @param fibObjectCategory the selected category for the Fib objects of
	 * 	this list to set
	 * @return true if the category could be set, else false
	 */
	virtual bool setSelectedCategory( const cFibObjectCategory & fibObjectCategory );
	
	/**
	 * This method sets the selected category for the Fib objects of this list.
	 * It will also load the Fib objects for the selected category, if possible.
	 *
	 * @see liPossibleCategories
	 * @see indexSelectedCategory
	 * @param inIndexSelectedCategory the index of the category to select
	 * @return true if the category could be set, else false
	 */
	virtual bool setSelectedCategory( const int inIndexSelectedCategory );

	/**
	 * @return the possible category for the Fib objects of this list
	 * 	@see liPossibleCategories
	 */
	virtual QList< cFibObjectCategory > getPossibleCategories() const;
	
	/**
	 * This methods sets the possible category for the Fib objects of this
	 * list to the given categories.
	 * If possible the selected category will stay the same, else it will be
	 * set to the first category.
	 *
	 * @see liPossibleCategories
	 * @param liNewPossibleCategories a list with the possible category to set
	 * @param bUpdateFibObjectInfos if true the Fib object info objects
	 * 	will be updated
	 * 	@see pBaseFibObjectInfo
	 */
	virtual void setPossibleCategories(
		const QList< cFibObjectCategory > & liNewPossibleCategories,
		const bool bUpdateFibObjectInfos = true );
	
	
	/**
	 * @see setMaxFibObjectInfos()
	 * @return the maximal number of Fib object info widgets to display
	 * 	( liFibObjectInfos.size() <= uiMaxFibObjectInfos)
	 * 	@see uiInMaxFibObjectInfos
	 * 	@see liFibObjectInfos
	 */
	unsigned int getMaxFibObjectInfos() const;
	
	/**
	 * This method sets the maximum number of Fib object info widgets to
	 * display ( liFibObjectInfos.size() <= uiMaxFibObjectInfos).
	 *
	 * @see getMaxFibObjectInfos()
	 * @see uiInMaxFibObjectInfos
	 * @see liFibObjectInfos
	 * @param uiInMaxFibObjectInfos the maximal number of Fib object info
	 * 	widgets to display ( liFibObjectInfos.size() <= uiMaxFibObjectInfos),
	 * 	if 0 the default value will be taken
	 */
	unsigned int setMaxFibObjectInfos( const unsigned int uiInMaxFibObjectInfos = 0 );
	
	/**
	 * This method returns the uiNumberOfFibObjectInfo'th Fib object info widget
	 * of this Fib object info widget list.
	 *
	 * @see liFibObjectInfos
	 * @see getNumberOfWidgetFibObjectInfos()
	 * @param uiNumberOfFibObjectInfo the number of the Fib object info widget to return
	 * 	(counting starts with 1)
	 * @return a pointer to the uiNumberOfFibObjectInfo'th Fib object info widget,
	 * 	or NULL if non exists
	 */
	virtual cWidgetFibObjectInfo * getWidgetFibObjectInfo(
		const unsigned int uiNumberOfFibObjectInfo );
	
	
	/**
	 * This method returns the uiNumberOfFibObjectInfo'th Fib object info widget
	 * of this Fib object info widget list.
	 *
	 * @see liFibObjectInfos
	 * @see getNumberOfWidgetFibObjectInfos()
	 * @param uiNumberOfFibObjectInfo the number of the Fib object info widget to return
	 * 	(counting starts with 1)
	 * @return a const pointer to the uiNumberOfFibObjectInfo'th Fib object info widget,
	 * 	or NULL if non exists
	 */
	virtual const cWidgetFibObjectInfo * getWidgetFibObjectInfo(
		const unsigned int uiNumberOfFibObjectInfo ) const;
	
	/**
	 * @see liFibObjectInfos
	 * @see getNumberOfWidgetFibObjectInfos()
	 * @see getWidgetFibObjectInfo()
	 * @return the list of the Fib object info widgets displayed in this widget
	 */
	virtual QList< cWidgetFibObjectInfo * > getWidgetFibObjectInfos();
	
	/**
	 * @see liFibObjectInfos
	 * @see getNumberOfWidgetFibObjectInfos()
	 * @see getWidgetFibObjectInfo()
	 * @return the list of the Fib object info widgets displayed in this widget
	 */
	virtual const QList< cWidgetFibObjectInfo * > getWidgetFibObjectInfos() const;
	
	/**
	 * This method adds the given Fib object info widget to this Fib object
	 * info widget list.
	 *
	 * @see liFibObjectInfos
	 * @see getNumberOfWidgetFibObjectInfos()
	 * @see removeWidgetFibObjectInfo()
	 * @see replaceWidgetFibObjectInfo()
	 * @param pWidgetFibObjectInfo a pointer to the Fib object info widget to add
	 * @param uiPosition the position where to add the Fib object info widget,
	 * 	if 0 or greater the number of Fib object info widgets in this
	 * 	widget list it will be added to the end of the Fib object info
	 * 	widget list (counting starts with 1)
	 * @return true if the Fib object info widget was added, else false
	 */
	virtual bool addWidgetFibObjectInfo( cWidgetFibObjectInfo * pWidgetFibObjectInfo,
		const unsigned int uiPosition = 0 );
	
	/**
	 * This method removes the uiPosition'th Fib object info widget from
	 * this widget list.
	 *
	 * @see liFibObjectInfos
	 * @see getNumberOfWidgetFibObjectInfos()
	 * @see addWidgetFibObjectInfo()
	 * @see replaceWidgetFibObjectInfo()
	 * @param uiPosition the position where to remove the Fib object info
	 * 	widget from (counting starts with 1)
	 * @param bDeleteOld if true the removed Fib object info widgets will
	 * 	be deleted from memory, else not (note: you have to delte it)
	 * @return true if the Fib object info widget was removed, else false
	 */
	virtual bool removeWidgetFibObjectInfo( const unsigned int uiPosition,
		const bool bDeleteOld = true );
	
	/**
	 * This method removes the given Fib object info widget from this input
	 * variable list.
	 *
	 * @see liFibObjectInfos
	 * @see getNumberOfWidgetFibObjectInfos()
	 * @see addWidgetFibObjectInfo()
	 * @see replaceWidgetFibObjectInfo()
	 * @param pWidgetFibObjectInfo the Fib object info widget to remove
	 * @param bDeleteOld if true the removed Fib object info widgets will
	 * 	be deleted from memory, else not (note: you have to delte it)
	 * @return true if the Fib object info widget was removed, else false
	 */
	virtual bool removeWidgetFibObjectInfo(
		cWidgetFibObjectInfo * pWidgetFibObjectInfo, const bool bDeleteOld = true );
	
	/**
	 * This method replaces a Fib object info widget in this Fib object info
	 * widget list.  It will replace the uiPosition'th Fib object info
	 * widget in the Fib object info list with the given Fib object info
	 * widget pWidgetFibObjectInfo (if possible).
	 *
	 * @see liFibObjectInfos
	 * @see getNumberOfWidgetFibObjectInfos()
	 * @see removeWidgetFibObjectInfo()
	 * @see addWidgetFibObjectInfo()
	 * @param pWidgetFibObjectInfo a pointer to the Fib object info widget
	 * 	to add, which will replace the old Fib object info widget on the
	 * 	uiPosition'th position
	 * @param uiPosition the position where to replace the Fib object info
	 * 	widget (counting starts with 1)
	 * @param bDeleteOld if true the replaced Fib object info widgets will
	 * 	be deleted from memory, else not (note: you have to delte it)
	 * @return true if the Fib object info widget was replace, else false
	 */
	virtual bool replaceWidgetFibObjectInfo(
		cWidgetFibObjectInfo * pWidgetFibObjectInfo,
		const unsigned int uiPosition, const bool bDeleteOld = true );
	
	/**
	 * This method sets the list of Fib object info widgets to the given list.
	 * All old Fib object info widgets of this list are removed and the
	 * given Fib object info widgets added.
	 *
	 * @see liFibObjectInfos
	 * @see getNumberOfWidgetFibObjectInfos()
	 * @see replaceWidgetFibObjectInfo()
	 * @see removeWidgetFibObjectInfo()
	 * @see addWidgetFibObjectInfo()
	 * @param liInWidgetFibObjectInfos a list of the Fib object info widgets
	 * 	this object should display
	 * @param bDeleteOld if true the old Fib object info widgets will be
	 * 	deleted from memory, else not (note: you have to delte them)
	 * @return true if the Fib object info widgets could be set, else false
	 */
	virtual bool setWidgetFibObjectInfos(
		QList< cWidgetFibObjectInfo * > & liInWidgetFibObjectInfos,
		const bool bDeleteOld = true );
	
	
	/**
	 * This method updates this Fib object info widget list for the actual
	 * selected category.
	 * It will retrive all Fib object info objects for the choosen category
	 * from the Fib object info handler cFibObjectInfoHandler (with the
	 * help of the pBaseFibObjectInfo if needed) and add their widgets to
	 * the Fib object info widget list of this widget.
	 *
	 * @see cFibObjectInfoHandler
	 * @return true if the Fib object info list could be updted, else false
	 */
	virtual bool updateForCategory();
	
	
	/**
	 * This method sets the selected Fib object info.
	 * It will be the base for all relativ categories.
	 * Note: This object won't trigger an selected Fib object info widget event.
	 * 	(No registered listeners for changes for the selected Fib object
	 * 	info widget lSelectedWidgetFibObjectInfo will notified.)
	 *
	 * @see pBaseFibObjectInfo
	 * @see liPossibleCategories
	 * @param pSelectedFibObjectInfo the selected Fib object info widget to set
	 */
	void setSelectedFibObjectInfo(
		cFibObjectInfo * pSelectedFibObjectInfo = NULL );
	
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
	 * With this function you can register a listeners for changes for the
	 * selected Fib object info widget.
	 *
	 * @see cWidgetFibObjectInfo::registerListenerSelectedFibObjectInfo()
	 * @see unregisterListenerSelectedFibObjectInfo()
	 * @see setListenersSelectedWidgetFibObjectInfo
	 * @see mutexListenersSelectedWidgetFibObjectInfo
	 * @see setSelectedFibObjectInfo()
	 * @see sendSelectedFibObjectInfoChange()
	 * @param pSelectedFibObjectInfo a pointer to the listener for changes
	 * @return true if the listener was registered, else false
	 */
	bool registerListenerSelectedFibObjectInfo(
		lSelectedWidgetFibObjectInfo * pSelectedFibObjectInfo );
	
	/**
	 * With this function you can unregister a listeners for changes for the
	 * selected Fib object info widget.
	 *
	 * @see cWidgetFibObjectInfo::unregisterListenerSelectedFibObjectInfo()
	 * @see registerListenerSelectedFibObjectInfo()
	 * @see setListenersSelectedWidgetFibObjectInfo
	 * @see mutexListenersSelectedWidgetFibObjectInfo
	 * @see setSelectedFibObjectInfo()
	 * @see sendSelectedFibObjectInfoChange()
	 * @param pSelectedFibObjectInfo a pointer to the listener for changes
	 * @return true if the listener was registered, else false
	 */
	bool unregisterListenerSelectedFibObjectInfo(
		lSelectedWidgetFibObjectInfo * pSelectedFibObjectInfo );
	
signals:
	
	/**
	 * This signal sends that a cWidgetFibObjectInfos widget should be closed.
	 *
	 * @see pButtonClose
	 * @see close()
	 * @param pWidgetFibObjectInfos a pointer to the cWidgetFibObjectInfos
	 * 	widget which should be closed
	 */
	void closeWidgetFibObjectInfos( cWidgetFibObjectInfos * pWidgetFibObjectInfos );
	
protected:
	
	/**
	 * This method send a event that the selected Fib object info widget
	 * has changed to all registered listeners for changes of the selected
	 * Fib object info widget.
	 *
	 * @see cWidgetFibObjectInfo::unregisterListenerSelectedFibObjectInfo()
	 * @see registerListenerSelectedFibObjectInfo()
	 * @see unregisterListenerSelectedFibObjectInfo()
	 * @see setListenersSelectedWidgetFibObjectInfo
	 * @see mutexListenersSelectedWidgetFibObjectInfo
	 * @see setSelectedFibObjectInfo()
	 */
	void sendSelectedFibObjectInfoChange(
		const cWidgetFibObjectInfo * pWidgetFibObjectInfo ) const;
	
	/**
	 * This method (re-)creats the scroll area with the Fib object info
	 * widget list.
	 *
	 * @see pScrollAreaFibObjectInfo
	 */
	virtual void createWidgetFibObjectInfosList();
	
	
	/**
	 * This function checks if the Fib object info widget list contains a
	 * widget for the given Fib object info.
	 *
	 * @param pFibObjectInfo the Fib object info for wich to search in the list
	 * @param liInWidgetFibObjectInfos the list with Fib object info widgets
	 * 	in which the seach for the widget of the give Fib object info
	 * @return true if the Fib object info widget list contains a widget
	 * 	for the given Fib object info, else false
	 */
	static bool containsFibObjectinfo(
		const cFibObjectInfo * pFibWidgetObjectInfo,
		const QList< cWidgetFibObjectInfo * > & liInWidgetFibObjectInfos );
	
	
	/**
	 * @return a hint for a good size of this widget
	 */
	virtual QSize sizeHint() const;
	
//members
	
	/**
	 * A list with the possible categories for the Fib object infos
	 * to show in this list.
	 * @see indexSelectedCategory
	 * @see pComboBoxCategories
	 */
	QList< cFibObjectCategory > liPossibleCategories;
	
	/**
	 * The index of the actual selected category.
	 * @see liPossibleCategories
	 * @see getSelectedCategory()
	 * @see slotSetSelectedCategory()
	 */
	int indexSelectedCategory;
	
	/**
	 * Mutex to lock access to the list of categories to display.
	 * Lock the mutex if you use one of the following containers:
	 * @see liPossibleCategories
	 * @see indexSelectedCategory
	 * @see pBaseFibObjectInfo
	 */
	mutable QMutex mutexPossibleCategories;

	/**
	 * If this list is for a relativ category, the Fib object info object
	 * to which it is relativ (e. g. to which it is the same type).
	 * @see setListenersSelectedWidgetFibObjectInfo
	 * @see setSelectedFibObjectInfo()
	 */
	cFibObjectInfo * pBaseFibObjectInfo;
	
	
	/**
	 * The list of Fib object info widgets to display in this widget.
	 * @see getNumberOfWidgetFibObjectInfos()
	 * @see getWidgetFibObjectInfos()
	 * @see getWidgetFibObjectInfo()
	 * @see replaceWidgetFibObjectInfo()
	 * @see removeWidgetFibObjectInfo()
	 * @see addWidgetFibObjectInfo()
	 * @see setWidgetFibObjectInfos()
	 */
	QList< cWidgetFibObjectInfo * > liFibObjectInfos;

	/**
	 * Mutex to lock access to the list of Fib object info widgets to display.
	 * Lock the mutex if you use one of the following containers:
	 * @see liFibObjectInfos
	 * @see uiMaxFibObjectInfos
	 * @see getMaxFibObjectInfos()
	 */
	mutable QMutex mutexFibObjectInfos;
	
	/**
	 * The maximal number of Fib object info widgets to display
	 * ( liFibObjectInfos.size() <= uiMaxFibObjectInfos).
	 * @see liFibObjectInfos
	 * @see getMaxFibObjectInfos()
	 * @see setMaxFibObjectInfos()
	 */
	unsigned int uiMaxFibObjectInfos;
	
	
	/**
	 * The set with the listeners for changes of the selected Fib object
	 * info widget.
	 * @see cWidgetFibObjectInfo::unregisterListenerSelectedFibObjectInfo()
	 * @see registerListenerSelectedFibObjectInfo()
	 * @see unregisterListenerSelectedFibObjectInfo()
	 * @see sendSelectedFibObjectInfoChange()
	 * @see mutexListenersSelectedWidgetFibObjectInfo
	 * @see setSelectedFibObjectInfo()
	 */
	std::set< lSelectedWidgetFibObjectInfo * > setListenersSelectedWidgetFibObjectInfo;
	
	/**
	 * Mutex to lock access to the listeners for changes of the selected
	 * Fib object info widget.
	 * Lock the mutex if you use one of the following containers:
	 * @see setInputVariableChangeListener
	 */
	mutable QMutex mutexListenersSelectedWidgetFibObjectInfo;

//elements to display this widget
	
	/**
	 * The combo box to choose the categories from.
	 * @see liPossibleCategories
	 */
	QComboBox * pComboBoxCategories;
	
	/**
	 * The button to close this widget.
	 */
	QPushButton * pButtonClose;
	
	/**
	 * The layout for the top of this widget.
	 * It contains the combo box for the categories at its right and the
	 * close button an the left.
	 * @see pComboBoxCategories
	 * @see pButtonClose
	 */
	QHBoxLayout * pLayoutTop;
	
	/**
	 * This area is for scrolling the list of Fib object infos.
	 * It contains the splitter with all Fib object info widgets.
	 * @see liFibObjectInfos
	 * @see pSplitterFibObjectInfo
	 */
	QScrollArea * pScrollAreaFibObjectInfo;
	
	/**
	 * The splitter with the Fib object info widgets.
	 * @see liFibObjectInfos
	 * @see pScrollAreaFibObjectInfo
	 */
	QSplitter * pSplitterFibObjectInfo;
	
	/**
	 * The layout for the Fib object info objects.
	 * It contains the top layout at its top and the scroll area for the
	 * Fib object info widgets at its bottom.
	 * @see pLayoutTop
	 * @see pScrollAreaFibObjectInfo
	 */
	QVBoxLayout * pLayoutMain;
	
	/**
	 * Mutex to lock access to the graphical elements to display.
	 * Lock the mutex if you use one of the following containers:
	 * @see pComboBoxCategories
	 * @see pButtonClose
	 * @see pLayoutTop
	 * @see pScrollAreaFibObjectInfo
	 * @see pSplitterFibObjectInfo
	 * @see pLayoutMain
	 */
	mutable QMutex mutexGraphicalElements;

private slots:
	
	/**
	 * This slot sets the index of the actual selected category.
	 *
	 * @see indexSelectedCategory
	 * @see liPossibleCategories
	 * @see setSelectedCategory
	 * @see getSelectedCategory()
	 * @param inIndexSelectedCategory the index of the category to select
	 */
	void slotSetSelectedCategory( const int inIndexSelectedCategory );
	
	/**
	 * This slot should be used if this widget should be closed.
	 * It emits the signal closeWidgetFibObjectInfos() .
	 * @see closeWidgetFibObjectInfos()
	 */
	void close();
	
};//end class cWidgetFibObjectInfos

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_WIDGET_FIB_OBJECT_INFOS_H__





