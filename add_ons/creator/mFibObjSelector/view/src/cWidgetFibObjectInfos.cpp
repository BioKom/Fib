/**
 * @file cWidgetFibObjectInfos
 * file name: cWidgetFibObjectInfos.cpp
 * @author Betti Oesterholz
 * @date 20.10.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a list of Fib object infos to select a
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
 * This file implements a class for a list of Fib object infos to select a
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
 *    - categories for the Fib objects to show in the list below,
 *    possibel category typs:
 *       - relative categories: same type (sameType), is contained (isContained), ...
 *       - absolute categories: all, typs like: objects, people, ...
 *       (first Fib object info list category list has just absolute)
 *
 * @see cWidgetFibObjectInfo
 * @see cFibObjectInfo
 * @see cFibObjectInfoHandler
 */
/*
History:
20.10.2013  Oesterholz  created
*/


//switches for test proposes
//#define DEBUG


#include "cWidgetFibObjectInfos.h"

#include "cWidgetFibObjectInfo.h"
#include "cFibObjectInfo.h"
#include "cFibObjectInfoHandler.h"
#include "cFibObjectCategory.h"


using namespace std;
using namespace fib::nCreator;


/**
 * The parameter constructor.
 *
 * @param liInPossibleCategories a list with the possible categories for
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
cWidgetFibObjectInfos::cWidgetFibObjectInfos(
		const QList< cFibObjectCategory > & liInPossibleCategories,
		const unsigned int uiInMaxFibObjectInfos, QWidget * pParent ):
		QWidget( pParent ),
		liPossibleCategories( liInPossibleCategories ),
		indexSelectedCategory( 0 ), pBaseFibObjectInfo( NULL ),
		uiMaxFibObjectInfos( uiInMaxFibObjectInfos ),
		pComboBoxCategories( NULL ), pButtonClose( NULL ), pLayoutTop( NULL ),
		pScrollAreaFibObjectInfo( NULL ),
		pSplitterFibObjectInfo( NULL ), pLayoutMain( NULL ) {
			
	DEBUG_OUT_L2(<<"cWidgetFibObjectInfos("<<this<<")::cWidgetFibObjectInfos( liInPossibleCategories, uiInMaxFibObjectInfos="<<uiInMaxFibObjectInfos<<", pParent="<<pParent<<" );"<<endl<<flush);
	
	if ( uiMaxFibObjectInfos == 0 ) {
		uiMaxFibObjectInfos = getDefaultMaxFibObjectInfos();
	}
	
	updateForCategory();
}


/**
 * The parameter constructor.
 *
 * @param liInPossibleCategories a list with the possible categories for
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
cWidgetFibObjectInfos::cWidgetFibObjectInfos(
		const QList< cFibObjectCategory > & liInPossibleCategories,
		cFibObjectInfo * pInBaseFibObjectInfo,
		const unsigned int uiInMaxFibObjectInfos, QWidget * pParent ):
		QWidget( pParent ),
		liPossibleCategories( liInPossibleCategories ), indexSelectedCategory( 0 ),
		pBaseFibObjectInfo( pInBaseFibObjectInfo ),
		uiMaxFibObjectInfos( uiInMaxFibObjectInfos ),
		pComboBoxCategories( NULL ), pButtonClose( NULL ), pLayoutTop( NULL ),
		pScrollAreaFibObjectInfo( NULL ),
		pSplitterFibObjectInfo( NULL ), pLayoutMain( NULL ) {
			
	DEBUG_OUT_L2(<<"cWidgetFibObjectInfos("<<this<<")::cWidgetFibObjectInfos( liInPossibleCategories, pInBaseFibObjectInfo="<<pInBaseFibObjectInfo<<" ,uiInMaxFibObjectInfos="<<uiInMaxFibObjectInfos<<", pParent="<<pParent<<" );"<<endl<<flush);
	
	if ( uiMaxFibObjectInfos == 0 ) {
		uiMaxFibObjectInfos = getDefaultMaxFibObjectInfos();
	}
	updateForCategory();
}


/**
 * destructor
 */
cWidgetFibObjectInfos::~cWidgetFibObjectInfos() {
	
	DEBUG_OUT_L2(<<"cWidgetFibObjectInfos("<<this<<")::~cWidgetFibObjectInfos();"<<endl <<flush);
	
	mutexFibObjectInfos.lock();
	bool bDeselectSelectedFibObjectInfo = false;
	for ( QList< cWidgetFibObjectInfo * >::iterator
			itrActualFibInfoWidget = liFibObjectInfos.begin();
			itrActualFibInfoWidget != liFibObjectInfos.end();
			itrActualFibInfoWidget++ ) {
		
		(*itrActualFibInfoWidget)->unregisterListenerSelectedFibObjectInfo( this );
		//if selected cWidgetFibObjectInfo is removed -> deselect it
		if ( pBaseFibObjectInfo == (*itrActualFibInfoWidget)->getFibObjectInfo() ) {
			//set no selected cWidgetFibObjectInfo
			bDeselectSelectedFibObjectInfo = true;
		}
		(*itrActualFibInfoWidget)->deleteLater();
	}
	liFibObjectInfos.clear();
	mutexFibObjectInfos.unlock();
	
	if ( bDeselectSelectedFibObjectInfo ) {
		//set no selected cWidgetFibObjectInfo
		sendSelectedFibObjectInfoChange( NULL );
	}
}


/**
 * @return the name of this class "cWidgetFibObjectInfos"
 */
string cWidgetFibObjectInfos::getName() const{
	
	return string("cWidgetFibObjectInfos");
}


/**
 * @return the selected category for the Fib objects of this list
 * 	@see liPossibleCategories
 * 	@see indexSelectedCategory
 */
cFibObjectCategory cWidgetFibObjectInfos::getSelectedCategory() const{
	
	DEBUG_OUT_L2(<<"cWidgetFibObjectInfos("<<this<<")::getSelectedCategory() called"<<endl <<flush);
	mutexPossibleCategories.lock();
	if ( liPossibleCategories.size() <= indexSelectedCategory ) {
		//no category exists
		mutexPossibleCategories.unlock();
		return cFibObjectCategory( QString("") );
	}//else return selected category
	
	const cFibObjectCategory fibObjectCategory(
		liPossibleCategories.at( indexSelectedCategory ) );
	mutexPossibleCategories.unlock();
	return fibObjectCategory;
}


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
bool cWidgetFibObjectInfos::setSelectedCategory(
		const cFibObjectCategory & fibObjectCategory ) {
	
	DEBUG_OUT_L2(<<"cWidgetFibObjectInfos("<<this<<")::setSelectedCategory( fibObjectCategory="<<(fibObjectCategory.getCategoryName().toStdString())<<") called"<<endl <<flush);
	
	mutexPossibleCategories.lock();
	//find category in category list
	const int indexToSelectCategory =
		liPossibleCategories.indexOf( fibObjectCategory );
	if ( indexToSelectCategory < 0 ) {
		//no such category to set
		mutexPossibleCategories.unlock();
		return false;
	}//else select found category
	if ( indexToSelectCategory == indexSelectedCategory ) {
		//category allready selected -> everything is OK -> do nothing
		mutexPossibleCategories.unlock();
		return true;
	}
	indexSelectedCategory = indexToSelectCategory;
	//adapt pComboBoxCategories if needed
	if ( pComboBoxCategories ) {
		//set selected category in the combo box
		pComboBoxCategories->setCurrentIndex( indexSelectedCategory );
	}
	mutexPossibleCategories.unlock();
	
	return updateForCategory();
}


/**
 * This method sets the selected category for the Fib objects of this list.
 * It will also load the Fib objects for the selected category, if possible.
 *
 * @see liPossibleCategories
 * @see indexSelectedCategory
 * @param inIndexSelectedCategory the index of the category to select
 * @return true if the category could be set, else false
 */
bool cWidgetFibObjectInfos::setSelectedCategory(
		const int inIndexSelectedCategory ) {
	
	DEBUG_OUT_L2(<<"cWidgetFibObjectInfos("<<this<<")::setSelectedCategory( inIndexSelectedCategory="<<inIndexSelectedCategory<<") called"<<endl <<flush);
	
	mutexPossibleCategories.lock();
	//find category in category list
	if ( ( inIndexSelectedCategory < 0 ) ||
			( liPossibleCategories.size() <= inIndexSelectedCategory ) ) {
		//no such category to set
		mutexPossibleCategories.unlock();
		return false;
	}//else select found category
	if ( inIndexSelectedCategory == indexSelectedCategory ) {
		//category allready selected -> everything is OK -> do nothing
		mutexPossibleCategories.unlock();
		return true;
	}
	indexSelectedCategory = inIndexSelectedCategory;
	//adapt pComboBoxCategories if needed
	if ( pComboBoxCategories ) {
		//set selected category in the combo box
		pComboBoxCategories->setCurrentIndex( indexSelectedCategory );
	}
	mutexPossibleCategories.unlock();
	
	return updateForCategory();
}



/**
 * @return the possible categories for the Fib objects of this list
 * 	@see liPossibleCategories
 */
QList< cFibObjectCategory > cWidgetFibObjectInfos::getPossibleCategories() const{
	
	DEBUG_OUT_L2(<<"cWidgetFibObjectInfos("<<this<<")::getPossibleCategories() called"<<endl <<flush);
	
	mutexPossibleCategories.lock();
	const QList< cFibObjectCategory > liRetPossibleCategories =
		liPossibleCategories;
	mutexPossibleCategories.unlock();
	return liRetPossibleCategories;
}


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
void cWidgetFibObjectInfos::setPossibleCategories(
		const QList< cFibObjectCategory > & liNewPossibleCategories,
		const bool bUpdateFibObjectInfos ) {
	
	DEBUG_OUT_L2(<<"cWidgetFibObjectInfos("<<this<<")::setPossibleCategories( #liNewPossibleCategories="<<liNewPossibleCategories.size()<<", bUpdateFibObjectInfos="<<bUpdateFibObjectInfos<<") called"<<endl <<flush);
	
	mutexPossibleCategories.lock();
	//evalue selected category
	const cFibObjectCategory selectedCategory(
		( indexSelectedCategory < liPossibleCategories.size() ) ?
		liPossibleCategories.at( indexSelectedCategory ) :
		QString("") );//else set empty category
	
	liPossibleCategories  = liNewPossibleCategories;
	
	//reselect old category if possible
	//find category in category list
	const int indexToSelectCategory =
		liPossibleCategories.indexOf( selectedCategory );
	if ( 0 <= indexToSelectCategory ) {
		//select found category
		indexSelectedCategory = indexToSelectCategory;
	}else{//else select first category
		indexSelectedCategory = 0;
	}
	mutexGraphicalElements.lock();
	if ( pComboBoxCategories ) {
		//adapt combo box
		pComboBoxCategories->deleteLater();
		//create category combo box
		pComboBoxCategories = new QComboBox( this );
		pComboBoxCategories->setInsertPolicy( QComboBox::NoInsert );
		for ( QList< cFibObjectCategory >::const_iterator
				itrCategory = liPossibleCategories.begin();
				itrCategory != liPossibleCategories.end(); itrCategory++ ) {
			//insert category
			pComboBoxCategories->addItem( itrCategory->getCategoryName() );
		}
		pComboBoxCategories->setCurrentIndex( indexSelectedCategory );
		connect( pComboBoxCategories, SIGNAL( currentIndexChanged( int ) ),
			this, SLOT( slotSetSelectedCategory( int ) ) );
		
		if ( pLayoutTop ) {
			pLayoutTop->addWidget( pComboBoxCategories, 0 );
		}
	}//no combo box -> nothing to adapt
	mutexGraphicalElements.unlock();
	
	mutexPossibleCategories.unlock();
	//set the new selected category
	if ( bUpdateFibObjectInfos ) {
		//update Fib object infos for new categories
		updateForCategory();
	}
}


/**
 * @see setMaxFibObjectInfos()
 * @return the maximal number of Fib object info widgets to display
 * 	( liFibObjectInfos.size() <= uiMaxFibObjectInfos)
 * 	@see uiInMaxFibObjectInfos
 * 	@see liFibObjectInfos
 */
unsigned int cWidgetFibObjectInfos::getMaxFibObjectInfos() const{
	
	return uiMaxFibObjectInfos;
}


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
 * @return the new maximal number of Fib object info widgets to display
 */
unsigned int cWidgetFibObjectInfos::setMaxFibObjectInfos(
		const unsigned int uiInMaxFibObjectInfos ) {
	
	mutexFibObjectInfos.lock();
	if ( uiInMaxFibObjectInfos == 0 ) {
		uiMaxFibObjectInfos = getDefaultMaxFibObjectInfos();
	}else{
		uiMaxFibObjectInfos = uiInMaxFibObjectInfos;
	}
	mutexFibObjectInfos.unlock();
	
	updateForCategory();
	
	return uiMaxFibObjectInfos;
}


/**
 * @see getMaxFibObjectInfos()
 * @see setMaxFibObjectInfos()
 * @return the default maximal number of Fib object info widgets to display
 * 	@see uiMaxFibObjectInfos
 * 	@see liFibObjectInfos
 */
unsigned int cWidgetFibObjectInfos::getDefaultMaxFibObjectInfos() {
	
	return 1024;
}


/**
 * This method returns the uiNumberOfFibObjectInfo'th Fib object info widget
 * of this Fib object info widget list.
 *
 * @see liFibObjectInfos
 * @see getNumberOfWidgetFibObjectInfos()
 * @param uiNumberOfFibObjectInfo the number of the Fib object info widget
 * 	to return (counting starts with 1)
 * @return a pointer to the uiNumberOfFibObjectInfo'th Fib object info widget,
 * 	or NULL if non exists
 */
cWidgetFibObjectInfo * cWidgetFibObjectInfos::getWidgetFibObjectInfo(
		const unsigned int uiNumberOfFibObjectInfo ) {
	
	mutexFibObjectInfos.lock();
	cWidgetFibObjectInfo * pFoundWidgetFibObjectInfo =
		liFibObjectInfos.value( ( uiNumberOfFibObjectInfo - 1 ) , NULL );
	mutexFibObjectInfos.unlock();
	return pFoundWidgetFibObjectInfo;
}


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
const cWidgetFibObjectInfo * cWidgetFibObjectInfos::getWidgetFibObjectInfo(
		const unsigned int uiNumberOfFibObjectInfo ) const{
	
	mutexFibObjectInfos.lock();
	const cWidgetFibObjectInfo * pFoundWidgetFibObjectInfo =
		liFibObjectInfos.value( ( uiNumberOfFibObjectInfo - 1 ) , NULL );
	mutexFibObjectInfos.unlock();
	return pFoundWidgetFibObjectInfo;
}


/**
 * @see liFibObjectInfos
 * @see getNumberOfWidgetFibObjectInfos()
 * @see getWidgetFibObjectInfo()
 * @return the list of the Fib object info widgets displayed in this widget
 */
QList< cWidgetFibObjectInfo * > cWidgetFibObjectInfos::getWidgetFibObjectInfos() {
	
	mutexFibObjectInfos.lock();
	QList< cWidgetFibObjectInfo * > liFibObjectInfosToReturn( liFibObjectInfos );
	mutexFibObjectInfos.unlock();
	return liFibObjectInfosToReturn;
}


/**
 * @see liFibObjectInfos
 * @see getNumberOfWidgetFibObjectInfos()
 * @see getWidgetFibObjectInfo()
 * @return the list of the Fib object info widgets displayed in this widget
 */
const QList< cWidgetFibObjectInfo * >
		cWidgetFibObjectInfos::getWidgetFibObjectInfos() const{
	
	mutexFibObjectInfos.lock();
	const QList< cWidgetFibObjectInfo * >
		liFibObjectInfosToReturn( liFibObjectInfos );
	mutexFibObjectInfos.unlock();
	return liFibObjectInfosToReturn;
}


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
 * 	widget list, it will be added to the end of the Fib object info
 * 	widget list (counting starts with 1)
 * @return true if the Fib object info widget was added, else false
 */
bool cWidgetFibObjectInfos::addWidgetFibObjectInfo(
		cWidgetFibObjectInfo * pWidgetFibObjectInfo,
		const unsigned int uiPosition ) {
	
	mutexFibObjectInfos.lock();
	if ( pWidgetFibObjectInfo == NULL ) {
		//no Fib object info widget to add
		mutexFibObjectInfos.unlock();
		return true;
	}
	if ( ( uiPosition == 0 ) ||
			( static_cast<unsigned int>(liFibObjectInfos.size()) < uiPosition ) ) {
		//add Fib object info widget to the end of the Fib object info widget list
		liFibObjectInfos.push_back( pWidgetFibObjectInfo );
	}else{//insert the Fib object info widget at the given position
		liFibObjectInfos.insert( uiPosition - 1 , pWidgetFibObjectInfo );
	}
	//register this as Fib object info widget change listener at Fib object info widget
	pWidgetFibObjectInfo->registerListenerSelectedFibObjectInfo( this );
	if ( pWidgetFibObjectInfo->getFibObjectInfo() == pBaseFibObjectInfo ) {
		//mark Fib object info as selected
		pWidgetFibObjectInfo->setSelected( true );
	}
	mutexFibObjectInfos.unlock();
	//recreate the widget list
	createWidgetFibObjectInfosList();
	return true;
}


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
 * @param bDeleteOld if true the removed Fib object info widget will
 * 	be deleted from memory, else not (note: you have to delete it)
 * @return true if the Fib object info widget was removed, else false
 */
bool cWidgetFibObjectInfos::removeWidgetFibObjectInfo(
		const unsigned int uiPosition, const bool bDeleteOld ) {
	
	mutexFibObjectInfos.lock();
	if ( ( uiPosition < 1 ) ||
			( static_cast<unsigned int>(liFibObjectInfos.size()) < uiPosition ) ) {
		//no such Fib object info widget to remove
		mutexFibObjectInfos.unlock();
		return false;
	}
	//evaluate the to remove Fib object info widget
	cWidgetFibObjectInfo * pRemovedFibInfoWidget =
		liFibObjectInfos.value( uiPosition - 1, NULL );
	//remove the Fib object info widget
	liFibObjectInfos.removeAt( uiPosition - 1 );
	bool bDeselectSelectedFibObjectInfo = false;
	if ( ! liFibObjectInfos.contains( pRemovedFibInfoWidget ) ) {
		/*unregister this as Fib object info widget change listener at
		Fib object info widgets*/
		pRemovedFibInfoWidget->unregisterListenerSelectedFibObjectInfo( this );
		//if selected cWidgetFibObjectInfo is removed -> deselect it
		if ( pBaseFibObjectInfo == pRemovedFibInfoWidget->getFibObjectInfo() ) {
			//set no selected cWidgetFibObjectInfo
			bDeselectSelectedFibObjectInfo = true;
		}
		if ( bDeleteOld ) {
			pRemovedFibInfoWidget->deleteLater();
		}
	}
	mutexFibObjectInfos.unlock();
	if ( bDeselectSelectedFibObjectInfo ) {
		//set no selected cWidgetFibObjectInfo
		sendSelectedFibObjectInfoChange( NULL );
	}
	//recreate the widget list
	createWidgetFibObjectInfosList();
	return true;
}


/**
 * This method removes the given Fib object info widget from this input
 * variable list.
 *
 * @see liFibObjectInfos
 * @see getNumberOfWidgetFibObjectInfos()
 * @see addWidgetFibObjectInfo()
 * @see replaceWidgetFibObjectInfo()
 * @param pWidgetFibObjectInfo the Fib object info widget to remove
 * @param bDeleteOld if true the removed Fib object info widget will
 * 	be deleted from memory, else not (note: you have to delete it)
 * @return true if the Fib object info widget was removed, else false
 */
bool cWidgetFibObjectInfos::removeWidgetFibObjectInfo(
		cWidgetFibObjectInfo * pWidgetFibObjectInfo, const bool bDeleteOld ) {
	
	mutexFibObjectInfos.lock();
	if ( ( pWidgetFibObjectInfo == NULL ) ||
			( ! liFibObjectInfos.contains( pWidgetFibObjectInfo ) ) ) {
		//no such Fib object info widget to remove
		mutexFibObjectInfos.unlock();
		return false;
	}
	
	//remove Fib object info widget
	liFibObjectInfos.removeAll( pWidgetFibObjectInfo );
	//if selected cWidgetFibObjectInfo is removed -> deselect it
	const bool bDeselectSelectedFibObjectInfo =//if true -> set no selected cWidgetFibObjectInfo
		( pBaseFibObjectInfo == pWidgetFibObjectInfo->getFibObjectInfo() );
	//unregister this as Fib object info widget change listener at Fib object info widgets
	pWidgetFibObjectInfo->unregisterListenerSelectedFibObjectInfo( this );
	if ( bDeleteOld ) {
		pWidgetFibObjectInfo->deleteLater();
	}
	mutexFibObjectInfos.unlock();
	
	if ( bDeselectSelectedFibObjectInfo ) {
		//set no selected cWidgetFibObjectInfo
		sendSelectedFibObjectInfoChange( NULL );
	}
	//recreate the widget list
	createWidgetFibObjectInfosList();
	return true;
}


/**
 * This method replaces a Fib object info widget in this Fib object info
 * widget list. It will replace the uiPosition'th Fib object info
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
 * @param bDeleteOld if true the replaced Fib object info widget will
 * 	be deleted from memory, else not (note: you have to delete it)
 * @return true if the Fib object info widget was replace, else false
 */
bool cWidgetFibObjectInfos::replaceWidgetFibObjectInfo(
		cWidgetFibObjectInfo * pWidgetFibObjectInfo,
		const unsigned int uiPosition, const bool bDeleteOld ) {
	
	mutexFibObjectInfos.lock();
	if ( ( pWidgetFibObjectInfo == NULL ) || ( uiPosition < 1 ) ||
			( static_cast<unsigned int>(liFibObjectInfos.size()) < uiPosition ) ) {
		//no such Fib object info widget to replace or non which should replace
		mutexFibObjectInfos.unlock();
		return false;
	}
	//evaluate the to remove Fib object info widget
	cWidgetFibObjectInfo * pRemovedFibInfoWidget =
		liFibObjectInfos.value( uiPosition - 1, NULL );
	//remove the Fib object info widget
	liFibObjectInfos.removeAt( uiPosition - 1 );
	bool bDeselectSelectedFibObjectInfo = false;
	if ( ! liFibObjectInfos.contains( pRemovedFibInfoWidget ) ) {
		//unregister this as Fib object info widget change listener at Fib object info widgets
		pRemovedFibInfoWidget->unregisterListenerSelectedFibObjectInfo( this );
		//if selected cWidgetFibObjectInfo is removed -> deselect it
		if ( pBaseFibObjectInfo == pRemovedFibInfoWidget->getFibObjectInfo() ) {
			//set no selected cWidgetFibObjectInfo
			bDeselectSelectedFibObjectInfo = true;
		}
		if ( bDeleteOld ) {
			pRemovedFibInfoWidget->deleteLater();
		}
	}
	
	//add the given Fib object info widget on the position
	if ( static_cast<unsigned int>(liFibObjectInfos.size()) < uiPosition ) {
		//add Fib object info widget to the end of the Fib object info widget list
		liFibObjectInfos.push_back( pWidgetFibObjectInfo );
	}else{//insert the Fib object info widget at the given position
		liFibObjectInfos.insert( uiPosition - 1 , pWidgetFibObjectInfo );
	}
	/*register this as selected Fib object info widget change listener at
	 *new Fib object info widget*/
	pWidgetFibObjectInfo->registerListenerSelectedFibObjectInfo( this );
	
	mutexFibObjectInfos.unlock();
	
	if ( pWidgetFibObjectInfo->getFibObjectInfo() == pBaseFibObjectInfo ) {
		//mark Fib object info as selected
		pWidgetFibObjectInfo->setSelected( true );
	}else{
		if ( bDeselectSelectedFibObjectInfo ) {
			//set no selected cWidgetFibObjectInfo
			sendSelectedFibObjectInfoChange( NULL );
		}
	}
	//recreate the widget list
	createWidgetFibObjectInfosList();
	return true;
}


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
 * 	deleted from memory, else not (note: you have to delete them)
 * @return true if the Fib object info widgets could be set, else false
 */
bool cWidgetFibObjectInfos::setWidgetFibObjectInfos(
		QList< cWidgetFibObjectInfo * > & liInWidgetFibObjectInfos,
		const bool bDeleteOld ) {
	
	mutexFibObjectInfos.lock();
	/*unregister this as Fib object info widget change listener at old
	Fib object info widgets*/
	bool bDeselectSelectedFibObjectInfo = false;
	for ( QList< cWidgetFibObjectInfo * >::iterator
			itrActualFibInfoWidget = liFibObjectInfos.begin();
			itrActualFibInfoWidget != liFibObjectInfos.end(); itrActualFibInfoWidget++ ) {
		
		(*itrActualFibInfoWidget)->unregisterListenerSelectedFibObjectInfo( this );
		//if selected cWidgetFibObjectInfo is removed -> deselect it
		if ( ( pBaseFibObjectInfo == (*itrActualFibInfoWidget)->getFibObjectInfo() ) &&
				( ! containsFibObjectInfo(
					pBaseFibObjectInfo, liInWidgetFibObjectInfos ) ) ) {
			//set no selected cWidgetFibObjectInfo
			bDeselectSelectedFibObjectInfo = true;
		}
		if ( bDeleteOld ) {
			(*itrActualFibInfoWidget)->deleteLater();
		}
	}
	//set the new Fib object info widgets
	liFibObjectInfos = liInWidgetFibObjectInfos;
	
	/*register this as Fib object info widget change listener at new
	 *Fib object info widgets*/
	for ( QList< cWidgetFibObjectInfo * >::iterator
			itrActualFibInfoWidget = liFibObjectInfos.begin();
			itrActualFibInfoWidget != liFibObjectInfos.end(); itrActualFibInfoWidget++ ) {
		
		(*itrActualFibInfoWidget)->registerListenerSelectedFibObjectInfo( this );
		
		if ( (*itrActualFibInfoWidget)->getFibObjectInfo() == pBaseFibObjectInfo ) {
			//mark Fib object info as selected
			(*itrActualFibInfoWidget)->setSelected( true );
			//don't deselect it
			bDeselectSelectedFibObjectInfo = false;
		}
	}
	mutexFibObjectInfos.unlock();
	
	if ( bDeselectSelectedFibObjectInfo ) {
		//set no selected cWidgetFibObjectInfo
		sendSelectedFibObjectInfoChange( NULL );
	}
	//recreate the widget list
	createWidgetFibObjectInfosList();
	
	return true;
}


/**
 * This method updates the Fib object info widget list for the actual
 * selected category.
 * It will retrive all Fib object info objects for the choosen category
 * from the Fib object info handler cFibObjectInfoHandler (with the
 * help of the pBaseFibObjectInfo if needed) and add their widgets to
 * the Fib object info widget list of this widget.
 *
 * @see cFibObjectInfoHandler
 * @return true if the Fib object info list could be updated, else false
 */
bool cWidgetFibObjectInfos::updateForCategory() {
	
	DEBUG_OUT_L2(<<"cWidgetFibObjectInfos("<<this<<")::updateForCategory() called"<<endl <<flush);
	
	//get the Fib object infos from the Fib object info handler and set them
	mutexPossibleCategories.lock();
	if ( ( indexSelectedCategory < 0 ) ||
			( liPossibleCategories.size() <= indexSelectedCategory ) ) {
		//no category selected
		mutexPossibleCategories.unlock();
		return false;
	}
	const cFibObjectCategory selectedCategory =
		liPossibleCategories.at( indexSelectedCategory );
	mutexPossibleCategories.unlock();
	
	cFibObjectInfoHandler * pFibObjectInfoHandler =
		cFibObjectInfoHandler::getInstance();
	
	if ( pFibObjectInfoHandler == NULL ) {
		//no Fib object info handler to get the Fib object info objects from
		return false;
	}
	//list with the new Fib object info objects
	list< cFibObjectInfo * > liNewFibObjectInfos;
	
	if ( selectedCategory.isAbsolute() ) {
		//category is absolute
		const list< unsigned long > liSortedFibObjectInfoIds =
			pFibObjectInfoHandler->getSortedFibObjectInfoIdsForCategory(
				selectedCategory.getCategoryName().toStdString(),
				getMaxFibObjectInfos() );
		
		liNewFibObjectInfos =
			pFibObjectInfoHandler->getFibObjectInfos( liSortedFibObjectInfoIds );
			
	}else{//category is relative
		mutexFibObjectInfos.lock();
		if ( pBaseFibObjectInfo == NULL ) {
			//no base Fib object info -> can't evalue realtiv Fib object infos
			mutexFibObjectInfos.unlock();
			return false;
		}
		//get via category connected Fib object infos
		const set< unsigned long > setConnectedFibObjects =
			pBaseFibObjectInfo->getConnectedFor(
				selectedCategory.getCategoryName().toStdString() );
		mutexFibObjectInfos.unlock();
		
		list< unsigned long > liSortedFibObjectInfoIds =
			pFibObjectInfoHandler->sortFibObjectInfoIds( setConnectedFibObjects );
		
		while( liSortedFibObjectInfoIds.size() < getMaxFibObjectInfos() ) {
			//reduce list of Fib object infos to maximum size
			liSortedFibObjectInfoIds.pop_front();
		}
		
		liNewFibObjectInfos =
			pFibObjectInfoHandler->getFibObjectInfos( liSortedFibObjectInfoIds );
	}
	mutexFibObjectInfos.lock();
	/* if the Fib object infos don't change
	 *-> don't change the Fib object info widget list*/
	bool bFibObjectInfosEqual = true;
	
	QList< cWidgetFibObjectInfo * >::iterator itrActualFibInfoWidget =
		liFibObjectInfos.begin();
	list< cFibObjectInfo * >::iterator itrActualFibInfo =
		liNewFibObjectInfos.begin();
	for ( ; ( itrActualFibInfoWidget != liFibObjectInfos.end() ) &&
				( itrActualFibInfo != liNewFibObjectInfos.end() );
			itrActualFibInfoWidget++, itrActualFibInfo++ ) {
		
		//compare Fib object info pointers
		if ( (*itrActualFibInfo) != (*itrActualFibInfoWidget)->getFibObjectInfo() ) {
			//Fib object info pointers for the position not the same
			bFibObjectInfosEqual = false;
			break;
		}
	}//end for compare Fib object infos in widget list and to set list
	if ( ( itrActualFibInfoWidget != liFibObjectInfos.end() ) ||
			( itrActualFibInfo != liNewFibObjectInfos.end() ) ) {
		//not in both list at the end -> Fib object infos in the lists not the same
		bFibObjectInfosEqual = false;
	}
	mutexFibObjectInfos.unlock();
	if ( bFibObjectInfosEqual ) {
		//if the Fib object infos are the same -> done
		return true;
	}//else
	//replace existing Fib object info widgets
	QList< cWidgetFibObjectInfo * > liNewFibObjectInfoWidgets;
	
	for ( list< cFibObjectInfo * >::iterator
			itrFibObjectInfo = liNewFibObjectInfos.begin();
			itrFibObjectInfo != liNewFibObjectInfos.end(); itrFibObjectInfo++ ) {
		
		liNewFibObjectInfoWidgets.push_front(
			new cWidgetFibObjectInfo( (*itrFibObjectInfo), this ) );
	}
	
	setWidgetFibObjectInfos( liNewFibObjectInfoWidgets );
	
	return true;
}


/**
 * This method sets the selected Fib object info.
 * It will be the base for all relativ categories.
 * Note: This object won't trigger a selected Fib object info widget event.
 * 	(No registered listeners for changes for the selected Fib object
 * 	info widget lSelectedWidgetFibObjectInfo will notified.)
 *
 * @see pBaseFibObjectInfo
 * @see liPossibleCategories
 * @param pSelectedFibObjectInfo the selected Fib object info widget to set
 */
void cWidgetFibObjectInfos::setSelectedFibObjectInfo(
		cFibObjectInfo * pSelectedFibObjectInfo ) {
	
	DEBUG_OUT_L2(<<"cWidgetFibObjectInfos("<<this<<")::setSelectedFibObjectInfo( pSelectedFibObjectInfo="<<pSelectedFibObjectInfo<<") called"<<endl <<flush);
	
	mutexFibObjectInfos.lock();
	pBaseFibObjectInfo = pSelectedFibObjectInfo;
	//mark just the selected base Fib object info
	for ( QList< cWidgetFibObjectInfo * >::iterator
			itrActualFibInfoWidget = liFibObjectInfos.begin();
			itrActualFibInfoWidget != liFibObjectInfos.end(); itrActualFibInfoWidget++ ) {
		
		(*itrActualFibInfoWidget)->setSelected(
			(*itrActualFibInfoWidget)->getFibObjectInfo() == pBaseFibObjectInfo );
	}
	
	mutexFibObjectInfos.unlock();
	updateForCategory();
}


/**
 * Event method
 * This method will be called if a Fib object info widget was
 * selected.
 *
 * @see lSelectedWidgetFibObjectInfo
 * @param pWidgetFibObjectInfo a pointer to the Fib object info
 * 	widget which was selected
 */
void cWidgetFibObjectInfos::selectWidgetFibObjectInfo(
		const cWidgetFibObjectInfo * pWidgetFibObjectInfo ) {
	
	DEBUG_OUT_L2(<<"cWidgetFibObjectInfos("<<this<<")::selectWidgetFibObjectInfo( pWidgetFibObjectInfo="<<pWidgetFibObjectInfo<<") called"<<endl <<flush);
	/*don't adapt Fib object info widgets of this widget, but
	 *relay change to all listeners for selected Fib info change*/
	sendSelectedFibObjectInfoChange( pWidgetFibObjectInfo );
}


/**
 * With this function you can register a listeners for changes of the
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
bool cWidgetFibObjectInfos::registerListenerSelectedFibObjectInfo(
		lSelectedWidgetFibObjectInfo * pSelectedFibObjectInfo ) {
	
	DEBUG_OUT_L2(<<"cWidgetFibObjectInfo("<<this <<")::registerListenerSelectedFibObjectInfo( pSelectedFibObjectInfo="<<pSelectedFibObjectInfo <<") called"<<endl<<flush);
	
	if ( pSelectedFibObjectInfo == NULL ) {
		//nothing to register
		return false;
	}
	mutexListenersSelectedWidgetFibObjectInfo.lock();
	const pair< set< lSelectedWidgetFibObjectInfo * >::iterator, bool >
		paListenerInserted = setListenersSelectedWidgetFibObjectInfo.insert(
			pSelectedFibObjectInfo );
	mutexListenersSelectedWidgetFibObjectInfo.unlock();
	return paListenerInserted.second;
}


/**
 * With this function you can unregister a listeners for changes of the
 * selected Fib object info widget.
 *
 * @see cWidgetFibObjectInfo::unregisterListenerSelectedFibObjectInfo()
 * @see registerListenerSelectedFibObjectInfo()
 * @see setListenersSelectedWidgetFibObjectInfo
 * @see mutexListenersSelectedWidgetFibObjectInfo
 * @see setSelectedFibObjectInfo()
 * @see sendSelectedFibObjectInfoChange()
 * @param pSelectedFibObjectInfo a pointer to the listener for changes
 * @return true if the listener was unregistered, else false
 */
bool cWidgetFibObjectInfos::unregisterListenerSelectedFibObjectInfo(
		lSelectedWidgetFibObjectInfo * pSelectedFibObjectInfo ) {
	
	DEBUG_OUT_L2(<<"cWidgetFibObjectInfo("<<this <<")::unregisterListenerSelectedFibObjectInfo( pSelectedFibObjectInfo="<<pSelectedFibObjectInfo <<") called"<<endl<<flush);
	
	mutexListenersSelectedWidgetFibObjectInfo.lock();
	const bool bUnregistered =
		( 0 < setListenersSelectedWidgetFibObjectInfo.erase( pSelectedFibObjectInfo ) );
	mutexListenersSelectedWidgetFibObjectInfo.unlock();
	return bUnregistered;
}



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
void cWidgetFibObjectInfos::sendSelectedFibObjectInfoChange(
		const cWidgetFibObjectInfo * pWidgetFibObjectInfo ) const{
	
	DEBUG_OUT_L2(<<"cWidgetFibObjectInfos("<<this<<")::sendSelectedFibObjectInfoChange( pWidgetFibObjectInfo="<<pWidgetFibObjectInfo<<") called"<<endl <<flush);
	
	mutexListenersSelectedWidgetFibObjectInfo.lock();
	set< lSelectedWidgetFibObjectInfo * >
		setTmpListenersSelectedWidgetFibObjectInfo =
			setListenersSelectedWidgetFibObjectInfo;
	mutexListenersSelectedWidgetFibObjectInfo.unlock();
	
	for ( set< lSelectedWidgetFibObjectInfo * >::iterator
			itrChangeListener = setTmpListenersSelectedWidgetFibObjectInfo.begin();
			itrChangeListener != setTmpListenersSelectedWidgetFibObjectInfo.end();
			itrChangeListener++ ) {
		
		(*itrChangeListener)->selectWidgetFibObjectInfo( pWidgetFibObjectInfo );
	}
}



/**
 * This method (re-)creats the scroll area with the Fib object info
 * widget list.
 *
 * @see pScrollAreaFibObjectInfo
 */
void cWidgetFibObjectInfos::createWidgetFibObjectInfosList() {
	
	DEBUG_OUT_L2(<<"cWidgetFibObjectInfos("<<this<<")::createWidgetFibObjectInfosList() called"<<endl <<flush);
	
	mutexGraphicalElements.lock();
	//delete old elements
	if ( pComboBoxCategories ) {
		pComboBoxCategories->deleteLater();
	}
	if ( pButtonClose ) {
		pButtonClose->deleteLater();
	}
	if ( pSplitterFibObjectInfo ) {
		pSplitterFibObjectInfo->deleteLater();
	}
	
	//create new entries
	mutexPossibleCategories.lock();
	//create category combo box
	pComboBoxCategories = new QComboBox( this );
	pComboBoxCategories->setInsertPolicy( QComboBox::NoInsert );
	for ( QList< cFibObjectCategory >::const_iterator
			itrCategory = liPossibleCategories.begin();
			itrCategory != liPossibleCategories.end(); itrCategory++ ) {
		//insert category
		pComboBoxCategories->addItem( itrCategory->getCategoryName() );
	}
	pComboBoxCategories->setCurrentIndex( indexSelectedCategory );
	connect( pComboBoxCategories, SIGNAL( currentIndexChanged( int ) ),
		this, SLOT( slotSetSelectedCategory( int ) ) );
	mutexPossibleCategories.unlock();
	
	//create close button
	pButtonClose = new QPushButton( tr("&Close"), this );
	pButtonClose->setCheckable( true );
	pButtonClose->setAutoDefault( false );
	connect( pButtonClose, SIGNAL( pressed() ), this, SLOT( close() ) );
	
	//create top layout
	if ( pLayoutTop == NULL ) {
		//create new top layout
		pLayoutTop = new QHBoxLayout();
	}
	pLayoutTop->addWidget( pComboBoxCategories, 0, Qt::AlignLeft );
	pLayoutTop->addWidget( pButtonClose, 0, Qt::AlignRight );
	
	//create the list with the Fib object info widgets
	pSplitterFibObjectInfo = new QSplitter( this );
	pSplitterFibObjectInfo->setOrientation( Qt::Vertical );
	pSplitterFibObjectInfo->setChildrenCollapsible( false );
	//add all Fib object info widgets
	cWidgetFibObjectInfo * pSelectedFibObjectInfo = NULL;
	for ( QList< cWidgetFibObjectInfo * >::const_iterator
			itrFibInfo = liFibObjectInfos.begin();
			itrFibInfo != liFibObjectInfos.end(); itrFibInfo++ ) {
		//add Fib object info widget
		pSplitterFibObjectInfo->addWidget( *itrFibInfo );
		
		if ( (*itrFibInfo)->getFibObjectInfo() == pBaseFibObjectInfo ) {
			//mark Fib object info as selected
			pSelectedFibObjectInfo = (*itrFibInfo);
			pSelectedFibObjectInfo->setSelected( true );
			
		}
	}
	
	//create a scroll area for the Fib info widgets
	if ( pScrollAreaFibObjectInfo == NULL ) {
		pScrollAreaFibObjectInfo = new QScrollArea( this );
		pScrollAreaFibObjectInfo->setWidgetResizable( true );
	}
	//set the splitter widget as contained in the scroll area
	pScrollAreaFibObjectInfo->setWidget( pSplitterFibObjectInfo );
	
	if ( pSelectedFibObjectInfo ) {
		//move to selected Fib object info
		pScrollAreaFibObjectInfo->ensureVisible(
			pSelectedFibObjectInfo->x(), pSelectedFibObjectInfo->y(),
			0, pSelectedFibObjectInfo->size().height() + 32 );
	}
	
	//add all to the main layout
	if ( pLayoutMain == NULL ) {
		//create new main layout
		pLayoutMain = new QVBoxLayout();
		pLayoutMain->addLayout( pLayoutTop );
		pLayoutMain->addWidget( pScrollAreaFibObjectInfo );
		//set the main layout
		setLayout( pLayoutMain );
	}
	
	mutexGraphicalElements.unlock();
	
	DEBUG_OUT_L2(<<"cWidgetFibObjectInfos("<<this<<")::createWidgetFibObjectInfosList() done"<<endl <<flush);
}


/**
 * This function checks if the Fib object info widget list contains a
 * widget for the given Fib object info.
 *
 * @param pFibObjectInfo the Fib object info for which to search in the list
 * @param liInWidgetFibObjectInfos the list with Fib object info widgets
 * 	in which to search for the widget of the give Fib object info
 * @return true if the Fib object info widget list contains a widget
 * 	for the given Fib object info, else false
 */
bool cWidgetFibObjectInfos::containsFibObjectInfo(
		const cFibObjectInfo * pFibWidgetObjectInfo,
		const QList< cWidgetFibObjectInfo * > & liInWidgetFibObjectInfos ) {
	
	for ( QList< cWidgetFibObjectInfo * >::const_iterator
			itrWidgetFibInfo = liInWidgetFibObjectInfos.begin();
			itrWidgetFibInfo != liInWidgetFibObjectInfos.end();
			itrWidgetFibInfo++ ) {
		
		if ( (*itrWidgetFibInfo)->getFibObjectInfo() == pFibWidgetObjectInfo ) {
			//widget for Fib object info found
			return true;
		}
	}
	return false;
}


/**
 * @return a hint for a good size of this widget
 */
QSize cWidgetFibObjectInfos::sizeHint() const{
	
	mutexFibObjectInfos.lock();
	if ( pComboBoxCategories ) {
		if ( pScrollAreaFibObjectInfo ) {
			//combo box and scroll area
			QSize sizeHint( pComboBoxCategories->sizeHint() );
			const QSize sizeHintScrollArea( pScrollAreaFibObjectInfo->sizeHint() );
			
			sizeHint.setWidth( max( sizeHint.width(), sizeHintScrollArea.width() ) );
			sizeHint.setHeight( sizeHint.height() + sizeHintScrollArea.height() );
			
			mutexFibObjectInfos.unlock();
			return sizeHint;
		}else{//combo box, but no scroll area
			const QSize sizeHint( pComboBoxCategories->sizeHint() );
			mutexFibObjectInfos.unlock();
			return sizeHint;
		}
	}//else no combo box
	if ( pScrollAreaFibObjectInfo ) {
		//no combo box, but scroll area
		const QSize sizeHint( pScrollAreaFibObjectInfo->sizeHint() );
		
		mutexFibObjectInfos.unlock();
		return sizeHint;
	}//else no combo box and no scroll area
	mutexFibObjectInfos.unlock();
	return QSize( 128, 128 );
}


/**
 * This slot sets the index of the actual selected category.
 *
 * @see indexSelectedCategory
 * @see liPossibleCategories
 * @see setSelectedCategory
 * @see getSelectedCategory()
 * @param inIndexSelectedCategory the index of the category to select
 */
void cWidgetFibObjectInfos::slotSetSelectedCategory(
		const int inIndexSelectedCategory ) {
	
	DEBUG_OUT_L2(<<"cWidgetFibObjectInfos("<<this<<")::slotSetSelectedCategory( inIndexSelectedCategory="<<inIndexSelectedCategory<<") called"<<endl <<flush);
	
	setSelectedCategory( inIndexSelectedCategory );
}


/**
 * This slot should be used if this widget should be closed
 * It emits the signal closeWidgetFibObjectInfos() .
 * @see closeWidgetFibObjectInfos()
 */
void cWidgetFibObjectInfos::close() {
	
	DEBUG_OUT_L2(<<"cWidgetFibObjectInfos("<<this<<")::close() called"<<endl <<flush);
	
	emit closeWidgetFibObjectInfos( this );
}












