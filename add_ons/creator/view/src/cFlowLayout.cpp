/**
 * @file cFlowLayout
 * file name: cFlowLayout.cpp
 * @author Betti Oesterholz
 * @date 26.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a flow layout.
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
 * This file implements a class for a flow layout.
 * In a flow layout the subitems arrange themselves.
 * A flow layout contains a list of layout items. These items are
 * viewed in their order (first) horizontal. If they reach the layout
 * right side a new line of items will be started.
 *
 * @see QLayout
 */
/*
History:
26.08.2013  Oesterholz  created
*/


//switches for test proposes
//#define DEBUG


#include "cFlowLayout.h"

#include <list>

#include <QWidgetItem>


using namespace std;


/**
 * parameter constructor
 *
 * @param iMargin the value for the left, top, right, and bottom margins
 * 	to use around the layout
 * @param iInHorizontalSpacing the horizontal spacing (in pixles) for
 * 	the layout elements
 * 	@see iHorizontalSpacing
 * @param iInVerticalSpacing the vertical spacing (in pixles) for
 * 	the layout elements
 * 	@see iVerticalSpacing
 */
cFlowLayout::cFlowLayout( const int iMargin,
		const int iInHorizontalSpacing, const int iInVerticalSpacing ):
		iHorizontalSpacing( iInHorizontalSpacing ),
		iVerticalSpacing( iInVerticalSpacing ) {
	//set contens margins of this layout (all margins are equal)
	setContentsMargins( iMargin, iMargin, iMargin, iMargin );
}


/**
 * parameter constructor
 *
 * @param pParent a pointer to parent of this layout
 * @param iMargin the value for the left, top, right, and bottom margins
 * 	to use around the layout
 * @param iInHorizontalSpacing the horizontal spacing (in pixles) for
 * 	the layout elements
 * 	@see iHorizontalSpacing
 * @param iInVerticalSpacing the vertical spacing (in pixles) for
 * 	the layout elements
 * 	@see iVerticalSpacing
 */
cFlowLayout::cFlowLayout( QWidget * pParent, const int iMargin,
		const int iInHorizontalSpacing, const int iInVerticalSpacing ):
		QLayout( pParent ),
		iHorizontalSpacing( iInHorizontalSpacing ),
		iVerticalSpacing( iInVerticalSpacing ) {
	//set contens margins of this layout (all margins are equal)
	setContentsMargins( iMargin, iMargin, iMargin, iMargin );
}


/**
 * destructor
 */
cFlowLayout::~cFlowLayout() {
	//delete all layout items
	while ( ! liLayoutItems.empty() ) {
		if ( liLayoutItems.front() ) {
			delete liLayoutItems.front();
		}
		liLayoutItems.pop_front();
	}
}


/**
 * @return the number of items in the layout
 * 	@see liLayoutItems
 */
int cFlowLayout::count() const{
	
	return liLayoutItems.count();
}


/**
 * This method returns the item in this layout with the given index.
 *
 * @see liLayoutItems
 * @see count()
 * @see addItem()
 * @param index the index of the item to return (counting starts with 0)
 * @return a pointer to the item with the given index of this layout, or
 * 	the null pointer NULL if non exists
 */
QLayoutItem * cFlowLayout::itemAt( int index ) const{
	
	return liLayoutItems.value( index, NULL );
}


/**
 * This method adds the given layout item to this layout.
 * The item will be added to the end of the layout list.
 *
 * @see liLayoutItems
 * @see itemAt()
 * @see count()
 * @param pItem a pointer to the layout item to add
 */
void cFlowLayout::addItem( QLayoutItem * pItem ) {
	//add the item to the end of the list
	liLayoutItems.append( pItem );
}


/**
 * This method adds the given layout item to this layout on the
 * specified index position.
 * Note: This object will care that the given item will be deleted.
 * 	( except when you call: removeItem( index, bDeleteItem=false )
 *
 * @see liLayoutItems
 * @see itemAt()
 * @see count()
 * @param pItem a pointer to the layout item to add
 * @param index the index where to add item (counting starts with 0),
 * 	if the index is greater or equal the number of layout items the
 * 	item pItem will be added to the end of the layout
 */
void cFlowLayout::addItem( QLayoutItem * pItem, const unsigned int index ) {
	//add the item to the list
	if ( index < ((unsigned int)(liLayoutItems.size())) ) {
		liLayoutItems.insert( index , pItem );
	}else{
		liLayoutItems.append( pItem );
	}
}


/**
 * This method will remove the layout item on the specified index
 * position from this layout.
 *
 * @see liLayoutItems
 * @see itemAt()
 * @see count()
 * @param index the index where to remove the item from (counting starts with 0)
 * @param bDeleteItem if true the item will also be deleted from the memory;
 * 	Note: If you give false, you have to care that the item will be deleted.
 * @return if true the item was removed, else false
 */
bool cFlowLayout::removeItem( const unsigned int index, const bool bDeleteItem ) {
	
	if ( ((unsigned int)liLayoutItems.size()) <= index ) {
		//no such item
		return false;
	}
	
	if ( bDeleteItem ) {
		//remove item from item list and delete it
		QLayoutItem * pItemToDelete = liLayoutItems.takeAt( index );
		if ( pItemToDelete ) {
			delete pItemToDelete;
		}
	}else{//just remove item from item list
		liLayoutItems.removeAt( index );
	}
	
	return true;
}


/**
 * This method adds the given widget to this layout.
 * It will use the addItem() method.
 * Note: This object will care that the given widget will be deleted.
 * 	( except when you call: removeWidget( index, bDeleteItem=false )
 *
 * @see liLayoutItems
 * @see addItem()
 * @see itemAt()
 * @see count()
 * @param pWidget a pointer to the layout widget to add
 */
void cFlowLayout::addWidget( QWidget * pWidget ) {
	
	//add the item to the list
	addItem( new QWidgetItem( pWidget ) );
}


/**
 * This method adds the given widget to this layout on the
 * specified index position.
 * It will use the addItem() method.
 * Note: This object will care that the given widget will be deleted.
 * 	( except when you call: removeWidget( index, bDeleteItem=false )
 *
 * @see liLayoutItems
 * @see addItem()
 * @see itemAt()
 * @see count()
 * @param pWidget a pointer to the layout widget to add
 * @param index the index where to add widget (counting starts with 0),
 * 	if the index is greater or equal the number of layout items the
 * 	widget pWidget will be added to the end of the layout
 */
void cFlowLayout::addWidget( QWidget * pWidget, const unsigned int index ) {
	
	//add the item to the list
	addItem( new QWidgetItem( pWidget ), index );
}


/**
 * This method will remove the layout widget on the specified index
 * position from this layout.
 *
 * @see liLayoutItems
 * @see removeItem()
 * @see clear()
 * @see itemAt()
 * @see count()
 * @see takeAt()
 * @param index the index where to remove the widget from (counting starts with 0)
 * @param bDeleteItem if true the widget will also be deleted from the memory;
 * 	Note: If you give false, you have to care that the widget will be deleted.
 * @return if true the widget was removed, else false
 */
bool cFlowLayout::removeWidget( const unsigned int index, const bool bDeleteItem ) {
	
	if ( ((unsigned int)liLayoutItems.size()) <= index ) {
		//no such item
		return false;
	}
	
	QLayoutItem * pItemToRemove = liLayoutItems.at( index );
	QWidget * pWidgetToRemove = pItemToRemove->widget();
	if ( pWidgetToRemove == NULL ) {
		//the item is not a widget -> can't remove it
		return false;
	}
	
	if ( bDeleteItem ) {
		//delete widget
		delete pWidgetToRemove;
	}//else just remove item from item list
	if ( pItemToRemove ) {
		delete pItemToRemove;
	}
	liLayoutItems.removeAt( index );
	
	return true;
}


/**
 * This method will remove the layout item on the specified index
 * position from this layout and retuns a pointer to it.
 * Beware: You have to care that the returned item will be deleted.
 *
 * @see liLayoutItems
 * @see clear()
 * @see itemAt()
 * @see count()
 * @see removeItem()
 * @param index the index where to remove the item from (counting starts with 0)
 * @return a pointer to the removed item
 */
QLayoutItem * cFlowLayout::takeAt( int index ) {
	
	if ( ( index < 0 ) || ( liLayoutItems.size() <= index ) ) {
		//no such item
		return NULL;
	}
	
	QLayoutItem * pToReturnItem =
		liLayoutItems.takeAt( index );
	
	return pToReturnItem;
}


/**
 * This method removes all layout items from this layout.
 *
 * @see liLayoutItems
 * @see removeItem()
 * @see itemAt()
 * @see count()
 * @param bDeleteItem if true the items will also be deleted from the memory;
 * 	Note: if you give false, you have to care that the item will be deleted.
 */
void cFlowLayout::clear( const bool bDeleteItem ) {
	
	if ( bDeleteItem ) {
		//delete all layout items
		for ( QList<QLayoutItem *>::iterator itrItem = liLayoutItems.begin();
				itrItem != liLayoutItems.end(); itrItem++ ) {
			//delete item
			if ( *itrItem ) {
				delete (*itrItem);
			}
		}
	}//else just remove item from item list
	liLayoutItems.clear();
	
	return;
}


/**
 * @return the horizontal spacing (in pixles) for the layout elements
 * 	@see iHorizontalSpacing
 */
int cFlowLayout::horizontalSpacing() const{
	
	if ( 0 <= iHorizontalSpacing ) {
		//use set horizontal spacing
		return iHorizontalSpacing;
	}//else horizontal spacing was not given -> use good spacing (evalueGoodSpacing())
	return evalueGoodSpacing( QStyle::PM_LayoutHorizontalSpacing );
}


/**
 * @return the vertical spacing (in pixles) for the layout elements
 * 	@see iVerticalSpacing
 */
int cFlowLayout::verticalSpacing() const{
	
	if ( 0 <= iVerticalSpacing ) {
		//use set horizontal spacing
		return iVerticalSpacing;
	}//else horizontal spacing was not given -> use good spacing (evalueGoodSpacing())
	return evalueGoodSpacing( QStyle::PM_LayoutVerticalSpacing );
}


/**
 * @see QLayout::minimumSize()
 * @return the minimum size of this layout;
 * 	This is the smallest size that the layout can have.
 */
QSize cFlowLayout::minimumSize() const{
	
	QSize minSize( 0, 0 );
	for ( QList<QLayoutItem *>::const_iterator itrItem = liLayoutItems.begin();
			itrItem != liLayoutItems.end(); itrItem++ ) {
		//expand the minimum size to the maximum size of the layout items
		minSize = minSize.expandedTo( (*itrItem)->minimumSize() );
	}
	//add the margins (2 times in every direction)
	minSize += QSize( 2 * margin(), 2 * margin() );
	DEBUG_OUT_L2(<<"cFlowLayout("<<this<<")::minimumSize() done; min size=( "<<minSize.width()<<", "<<minSize.height()<<" )"<<endl<<flush);
	return minSize;
}


/**
 * @return a hint for a good size of this widget
 */
QSize cFlowLayout::sizeHint() const{
	//the minimum size is a good size
	return minimumSize();
}


/**
 * @see QLayout::expandingDirections()
 * @see sizeHint()
 * @return whether this layout can make use of more space than sizeHint();
 * 	Because this widget has fixed size it will return 0 for
 * 	@see QSizePolicy::Fixed
 */
Qt::Orientations cFlowLayout::expandingDirections() const{
	//this widget has fixed size
	return 0;
}


/**
 * @see QLayout::setGeometry()
 * @return set this item's geometry to rectangle.
 */
void cFlowLayout::setGeometry( const QRect & rectangle ) {
	
	QLayout::setGeometry( rectangle );
	createLayout( rectangle, false );
}


/**
 * @see QLayout::hasHeightForWidth()
 * @return true because this layouts preferred height depends on its width
 */
bool cFlowLayout::hasHeightForWidth() const{
	
	return true;
}


/**
 * This method returns the preferred height for this layout item, given
 * the width iWidth.
 *
 * @see QLayout::heightForWidth()
 * @param iWidth the width for which to return the preferred height
 * @return the preferred height for this layout item, given the width iWidth
 */
int cFlowLayout::heightForWidth( const int iWidth ) const{
	//evalue the height with simulated created layout
	return createLayout( QRect( 0, 0, iWidth, 0 ), true ).height();
}


/**
 * This method returns the preferred size for this layout item, given
 * the maximum width iWidth.
 * The returned size will have a smaaler width than iWidth (if
 * possible) and a height, so that all elements of the layout can be
 * displayed.
 *
 * @param iWidth the width for which to return the preferred size
 * @return the preferred size for this layout, given the maximum width iWidth
 */
QSize cFlowLayout::getSizeForMaxWidth( const int iWidth ) const{
	//evalue the height with simulated created layout
	return createLayout( QRect( 0, 0, iWidth, 0 ), true );
}


/**
 * This method returns the maximum width for iNumberOfElements following
 * elements in this flow layout.
 * It is to evalue fast a good width for this flow layout, if minimum
 * iNumberOfElements should be shown on one line.
 *
 * @see heightForWidth
 * @param iNumberOfElements the number of following elements for which
 * 	to return the maximum width
 * @return a width which is the maximum widht for all iNumberOfElements
 * 	following elements in this flow layout
 */
int cFlowLayout::getMaxWidthForMinNumberOfElements(
		const int iNumberOfElements ) const{
	
	DEBUG_OUT_L2(<<"cFlowLayout("<<this<<")::getMaxWidthForMinNumberOfElements( iNumberOfElements="<<iNumberOfElements<<" ) called"<<endl<<flush);
	//evalue the width of all elements
	list< int > liWidths;
	
	const int iXDefaultSpacing = horizontalSpacing();
	int iXSpacing;
	QWidget * pItemWidged;
	for ( QList<QLayoutItem *>::const_iterator itrItem = liLayoutItems.begin();
			itrItem != liLayoutItems.end(); itrItem++ ) {
		//evalue spacing for the element
		pItemWidged = (*itrItem)->widget();
		if ( pItemWidged == NULL ) {
			//layout item not a widget -> skip item
			continue;
		}
		//get spacing for x direction
		iXSpacing = iXDefaultSpacing;
		if ( iXDefaultSpacing == -1 ) {
			//use item spacing in x direction
			iXSpacing = pItemWidged->style()->layoutSpacing(
				QSizePolicy::DefaultType, QSizePolicy::DefaultType, Qt::Horizontal );
		}
		DEBUG_OUT_L4(<<"cFlowLayout("<<this<<")::getMaxWidthForMinNumberOfElements( iNumberOfElements="<<iNumberOfElements<<" ) width for element "<<liWidths.size()<<" is "<<(pItemWidged->sizeHint().width() + iXSpacing)<<endl<<flush);
		//append width needed for the element to width list
		liWidths.push_back( pItemWidged->sizeHint().width() + iXSpacing );
	}
	
	//evalue the maximum widht for iNumberOfElements following elements
	list< int >::const_iterator itrStartElement = liWidths.begin();
	list< int >::const_iterator itrEndElement   = itrStartElement;
	DEBUG_OUT_L4(<<"cFlowLayout("<<this<<")::getMaxWidthForMinNumberOfElements( iNumberOfElements="<<iNumberOfElements<<" ) width for fields: "<<flush);
	int iActualFieldWidth = 0;
	//evalue width of first iNumberOfElements elements
	for ( int iActualItem = 0; ( iActualItem < iNumberOfElements ) &&
			( itrEndElement != liWidths.end() );
			iActualItem++, itrEndElement++ ) {
		
		iActualFieldWidth += (*itrEndElement);
	}
	DEBUG_OUT_L4(<<iActualFieldWidth<<endl<<flush);
	
	int iMaxFieldWidth = iActualFieldWidth;
	/*evalue value of following iNumberOfElements element blocks;
	 to get the next block width value subtract the first element of the
	 old block and add the last of the new block*/
	for ( ; itrEndElement != liWidths.end();
			itrStartElement++, itrEndElement++ ) {
		
		iActualFieldWidth -= (*itrStartElement);
		iActualFieldWidth += (*itrEndElement);
		//evalue new max value
		if ( iMaxFieldWidth < iActualFieldWidth ) {
			iMaxFieldWidth = iActualFieldWidth;
		}
		DEBUG_OUT_L4(<<", "<<iActualFieldWidth<<endl<<flush);
	}
	DEBUG_OUT_L4(<<endl<<flush);
	DEBUG_OUT_L2(<<"cFlowLayout("<<this<<")::getMaxWidthForMinNumberOfElements( iNumberOfElements="<<iNumberOfElements<<" ) done; max width = "<<iMaxFieldWidth<<endl<<flush);
	return iMaxFieldWidth;
}


/**
 * This method evalues the layout.
 * It uses getContentsMargins() to calculate the area available to the
 * layout items.
 *
 * @param rectLayout the rectangle for the layout
 * @param bJustEvalue if true just evaluates the layout, without changing
 * 	the layout (the return value is evaluated, but nothing else changed)
 * @return the hight of the layout in pixles
 */
QSize cFlowLayout::createLayout(
		const QRect & rectLayout, const bool bJustEvalue ) const{
	//evalue a good start position
	int iLeftBorder;
	int iTopBorder;
	int iRightBorder;
	int iBottomBorder;
	getContentsMargins( &iLeftBorder, &iTopBorder, &iRightBorder, &iBottomBorder );
	//reduce the rectangle for the layout by the margins (can't use the margins)
	const QRect effectiveRect = rectLayout.adjusted(
		iLeftBorder, iTopBorder, 0 - iRightBorder, 0 - iBottomBorder );
	//get values for the layout item spacings
	const int uiXStartPosition = effectiveRect.x();
	//actual position
	int iXPosition = uiXStartPosition;
	int iYPosition = effectiveRect.y();
	const int iRightBorderLayout = effectiveRect.right();
	//spacing of the items (if a spacing value is -1 the item spacing will be used)
	const int iXDefaultSpacing = horizontalSpacing();
	const int iYDefaultSpacing = verticalSpacing();
	//height of the actual line
	int iLineHeight = 0;
	//declare temporary variables
	int iXSpacing;
	int iYSpacing;
	int iXPositionNext;
	//the maximal x position for an element in the created layout
	int iMaxXPosition = 0;
	//for each item -> add it to the layout
	QWidget * pItemWidged;
	for ( QList<QLayoutItem *>::const_iterator itrItem = liLayoutItems.begin();
			itrItem != liLayoutItems.end(); itrItem++ ) {
		//evalue spacing for the element
		pItemWidged = (*itrItem)->widget();
		if ( pItemWidged == NULL ) {
			//layout item not a widget -> skip item
			continue;
		}
		//get spacing for x direction
		iXSpacing = iXDefaultSpacing;
		if ( iXDefaultSpacing == -1 ) {
			//use item spacing in x direction
			iXSpacing = pItemWidged->style()->layoutSpacing(
				QSizePolicy::DefaultType, QSizePolicy::DefaultType, Qt::Horizontal );
		}
		//get spacing for y direction
		iYSpacing = iYDefaultSpacing;
		if ( iYDefaultSpacing == -1 ) {
			//use item spacing in y direction
			iYSpacing = pItemWidged->style()->layoutSpacing(
				QSizePolicy::DefaultType, QSizePolicy::DefaultType, Qt::Vertical );
		}
		//add the item to this layout
		const QSize sizeActualItem = pItemWidged->sizeHint();
		iXPositionNext = iXPosition + sizeActualItem.width() + iXSpacing;
		if ( ( iRightBorderLayout < ( iXPositionNext - iXSpacing ) ) &&
				( 0 < iLineHeight ) //-> minimum one element on each line
				) {
			//widget goes over right border -> go to next line
			if ( iMaxXPosition < iXPosition ){
				//this element has a grater x position than any element before
				iMaxXPosition = iXPosition;
			}
			iXPosition = uiXStartPosition;
			iYPosition += iLineHeight + iYSpacing;
			iXPositionNext = uiXStartPosition + sizeActualItem.width() +
				iXSpacing;
			iLineHeight = 0;
		}
		
		if ( ! bJustEvalue ) {
			//change item geometry, so it matches into the layout
			pItemWidged->setGeometry( QRect( QPoint( iXPosition, iYPosition ),
				sizeActualItem ) );
		}
		iXPosition = iXPositionNext;
		//max( iLineHeight, sizeActualItem.height() )
		iLineHeight = ( iLineHeight < sizeActualItem.height() ) ?
			sizeActualItem.height() : iLineHeight ;
	}
	if ( iMaxXPosition < iXPosition ){
		//the last element has a grater x position than any element before
		iMaxXPosition = iXPosition;
	}
	//return the width and hight of the layout
	return QSize( iMaxXPosition,
		( iYPosition + iLineHeight ) - rectLayout.y() + iBottomBorder );
}


/**
 * This method will evalue the default spacing for either the top-level
 * layouts or the sublayouts.
 * The default spacing for top-level layouts, when the parent is a
 * QWidget, will be determined by querying the style. The default
 * spacing for sublayouts, when the parent is a QLayout, will be
 * determined by querying the spacing of the parent layout.
 *
 * @param pixleMetrix the pixle metric for top-level layouts
 * @return the spacing value
 */
int cFlowLayout::evalueGoodSpacing( QStyle::PixelMetric pixleMetric ) const{
	
	QObject * pParent = this->parent();
	if ( pParent == 0 ) {
		//no parrent -> no good spacing
		return -1;
	}//else
	if ( pParent->isWidgetType() ) {
		//the parent is a widget
		QWidget * pParentWidget = static_cast<QWidget *>( pParent );
		return pParentWidget->style()->pixelMetric(
			pixleMetric, 0, pParentWidget );
	}//else
	return (static_cast<QLayout *>(pParent))->spacing();
}













