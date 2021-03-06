/**
 * @file cFlowLayout
 * file name: cFlowLayout.h
 * @author Betti Oesterholz
 * @date 26.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a flow layout.
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
 * This file specifies a class for a flow layout.
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


#ifndef ___cFlowLayout_H__
#define ___cFlowLayout_H__


#include "version.h"


#include <QLayout>
#include <QRect>
#include <QWidget>
#include <QStyle>



class cFlowLayout : public QLayout{
protected:
	
	/**
	 * The list with the layout items contained in this flow layout.
	 * @see count()
	 * @see itemAt()
	 * @see addItem()
	 * @see removeItem()
	 * @see takeAt()
	 */
	QList<QLayoutItem *> liLayoutItems;
	
	/**
	 * The horizontal spacing (in pixles) for the layout elements.
	 * @see horizontalSpacing()
	 * @see createLayout()
	 * @see minimumSize()
	 */
	int iHorizontalSpacing;
	
	/**
	 * The vertical spacing (in pixles) for the layout elements.
	 * @see verticalSpacing()
	 * @see createLayout()
	 * @see minimumSize()
	 */
	int iVerticalSpacing;
	
public:
	
	/**
	 * parameter constructor
	 *
	 * @param iMargin the value for the left, top, right, and bottom margins
	 * 	to use around the layout
	 * @param iInHorizontalSpacing the horizontal spacing (in pixles) for
	 * 	the layout elements (-1 = evalue good spacing)
	 * 	@see iHorizontalSpacing
	 * @param iInVerticalSpacing the vertical spacing (in pixles) for
	 * 	the layout elements (-1 = evalue good spacing)
	 * 	@see iVerticalSpacing
	 */
	cFlowLayout( const int iMargin = -1,
		const int iInHorizontalSpacing = -1, const int iInVerticalSpacing = -1 );
	
	/**
	 * parameter constructor
	 *
	 * @param pParent a pointer to parent of this layout
	 * @param iMargin the value for the left, top, right, and bottom margins
	 * 	to use around the layout
	 * @param iInHorizontalSpacing the horizontal spacing (in pixles) for
	 * 	the layout elements (-1 = evalue good spacing)
	 * 	@see iHorizontalSpacing
	 * @param iInVerticalSpacing the vertical spacing (in pixles) for
	 * 	the layout elements (-1 = evalue good spacing)
	 * 	@see iVerticalSpacing
	 */
	explicit cFlowLayout( QWidget * pParent, const int iMargin = -1,
		const int iInHorizontalSpacing = -1, const int iInVerticalSpacing = -1 );
	
	/**
	 * destructor
	 */
	virtual ~cFlowLayout();
	
	
	/**
	 * @return the number of items in the layout
	 * 	@see liLayoutItems
	 */
	virtual int count() const;
	
	/**
	 * This method returns the item in this layout with the given index.
	 *
	 * @see liLayoutItems
	 * @see count()
	 * @see addItem()
	 * @see removeItem()
	 * @see takeAt()
	 * @param index the index of the item to return (counting starts with 0)
	 * @return a pointer to the item with the given index of this layout, or
	 * 	the null pointer NULL if non exists
	 */
	virtual QLayoutItem * itemAt( int index ) const;
	
	/**
	 * This method adds the given layout item to this layout.
	 * The item will be added to the end of the layout item list.
	 *
	 * @see liLayoutItems
	 * @see itemAt()
	 * @see count()
	 * @see removeItem()
	 * @see takeAt()
	 * @param pItem a pointer to the layout item to add
	 */
	void addItem( QLayoutItem * pItem );
	
	/**
	 * This method adds the given layout item to this layout on the
	 * specified index position.
	 * Note: This object will care that the given item will be deleted.
	 * 	( except when you call: removeItem( index, bDeleteItem=false )
	 *
	 * @see liLayoutItems
	 * @see itemAt()
	 * @see count()
	 * @see removeItem()
	 * @see takeAt()
	 * @param pItem a pointer to the layout item to add
	 * @param index the index where to add item (counting starts with 0),
	 * 	if the index is greater or equal the number of layout items, the
	 * 	item pItem will be added to the end of the layout item list
	 */
	void addItem( QLayoutItem * pItem, const unsigned int index );
	
	/**
	 * This method will remove the layout item on the specified index
	 * position from this layout.
	 *
	 * @see liLayoutItems
	 * @see clear()
	 * @see itemAt()
	 * @see count()
	 * @see takeAt()
	 * @param index the index where to remove the item from (counting starts with 0)
	 * @param bDeleteItem if true the item will also be deleted from the memory;
	 * 	Note: If you give false, you have to care that the item will be deleted.
	 * @return if true the item was removed, else false
	 */
	bool removeItem( const unsigned int index, const bool bDeleteItem=false );
	
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
	void addWidget( QWidget * pWidget );
	
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
	 * 	widget pWidget will be added to the end of the layout item list
	 */
	void addWidget( QWidget * pWidget, const unsigned int index );
	
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
	 * @param bDeleteItem if true the item widget will also be deleted from the memory;
	 * 	Note: If you give false, you have to care that the item widget will be deleted.
	 * @return if true the widget was removed, else false
	 */
	bool removeWidget( const unsigned int index, const bool bDeleteItem=false );
	
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
	 virtual QLayoutItem * takeAt( int index );
	
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
	void clear( const bool bDeleteItem=false );
	
	/**
	 * @return the horizontal spacing (in pixles) for the layout elements
	 * 	@see iHorizontalSpacing
	 */
	virtual int horizontalSpacing() const;
	
	/**
	 * @return the vertical spacing (in pixles) for the layout elements
	 * 	@see iVerticalSpacing
	 */
	virtual int verticalSpacing() const;
	
	/**
	 * @see QLayout::minimumSize()
	 * @return the minimum size of this layout;
	 * 	This is the smallest size that the layout can have.
	 */
	virtual QSize minimumSize() const;
	
	/**
	 * @return a hint for a good size of this widget
	 */
	virtual QSize sizeHint() const;
	
	/**
	 * @see QLayout::expandingDirections()
	 * @see sizeHint()
	 * @return whether this layout can make use of more space than sizeHint();
	 * 	Because this widget has fixed size it will return 0 for
	 * 	@see QSizePolicy::Fixed
	 */
	virtual Qt::Orientations expandingDirections() const;
	
	/**
	 * @see QLayout::setGeometry()
	 * @return set this item's geometry to rectangle.
	 */
	virtual void setGeometry( const QRect & rectangle );
	
	/**
	 * @see QLayout::hasHeightForWidth()
	 * @return true because this layouts preferred height depends on its width
	 */
	virtual bool hasHeightForWidth() const;
	
	/**
	 * This method returns the preferred height for this layout item, given
	 * the width iWidth.
	 *
	 * @see QLayout::heightForWidth()
	 * @param iWidth the width for which to return the preferred height
	 * @return the preferred height for this layout, given the width iWidth
	 */
	virtual int heightForWidth( const int iWidth ) const;
	
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
	virtual QSize getSizeForMaxWidth( const int iWidth ) const;
	
	/**
	 * This method returns the maximum width for iNumberOfElements following
	 * elements in this flow layout.
	 * It is to evalue fast a good width for this flow layout, if minimum
	 * iNumberOfElements should be shown on one line.
	 *
	 * @see heightForWidth
	 * @param iNumberOfElements the number of following elements for which
	 * 	to return the maximum width
	 * @return a width wich is the maximum widht for all iNumberOfElements
	 * 	following elements in this flow layout
	 */
	int getMaxWidthForMinNumberOfElements( const int iNumberOfElements ) const;
	

protected:
	
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
	virtual QSize createLayout( const QRect & rectLayout,
		const bool bJustEvalue = true ) const;
	
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
	int evalueGoodSpacing( QStyle::PixelMetric pixleMetric ) const;

};//end class cFlowLayout


#endif //___cFlowLayout_H__





