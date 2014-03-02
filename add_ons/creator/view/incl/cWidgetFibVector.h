
//TODO check

/**
 * @file cWidgetFibVector
 * file name: cWidgetFibVector.h
 * @author Betti Oesterholz
 * @date 30.11.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a vector widget.
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
 * This file specifies a class for a vector widget.
 * If you have a Fib element, vectors of it can be displayed with this
 * class for the Fib creator modul.
 * A Fib vector contains a number of scalars.
 *
 * @see cWidgetFibScalar
 * @see cFibVectorCreator
 * @see fib::cFibVector
 * @see cFibScalar
 *
 * It should look like:
 * +-------------------------------------------------+
 * | - name @see szNameOfFibObject                   |
 * | - list of elements                              |
 * +-------------------------------------------------+
 *
 */
/*
History:
30.11.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_WIDGET_FIB_VECTOR_H__
#define ___FIB__NCREATOR__C_WIDGET_FIB_VECTOR_H__


#include "version.h"

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMutex>

#include "lFibVectorChanged.h"


//forward declarations
class cFlowLayout;


namespace fib{

namespace nCreator{

//forward declarations
class cFibVectorCreator;
class eFibVectorChangedEvent;
class cWidgetFibVectorElement;

class cWidgetFibVector: public QFrame, public lFibVectorChanged{
		Q_OBJECT
public:
	
	/**
	 * The standard constructor for a Fib vector widget.
	 *
	 * @param pInFibVector a pointer to the Fib vector object for this widget
	 * 	@see pFibVector
	 * @param pParent a pointer the parent of this new Fib vector widget
	 */
	cWidgetFibVector( cFibVectorCreator * pInFibVector,
		QWidget * pParent = NULL );
	
	/**
	 * destructor
	 */
	virtual ~cWidgetFibVector();
	
	/**
	 * This method returns a pointer to the Fib vector object of this widget.
	 * Note: Don't delete the returned Fib vector object.
	 *
	 * @see pFibVector
	 * @return a const pointer to the Fib vector object of this widget
	 */
	const cFibVectorCreator * getFibVector() const;
	
	/**
	 * This method returns a pointer to the Fib vector object of this widget.
	 * Note: Don't delete the returned Fib vector object.
	 *
	 * @see pFibVector
	 * @return a pointer to the Fib vector object of this widget
	 */
	cFibVectorCreator * getFibVector();
	
	/**
	 * @return the name of this class "cWidgetFibVector"
	 */
	virtual std::string getName() const;
	
	
	/**
	 * Event method
	 * It will be called every time a Fib vector object (cFibVectorCreator), at
	 * which this object is registered, was changed.
	 *
	 * @param pFibVectorChanged a pointer to the event, with the information
	 * 	about the changed Fib node
	 */
	virtual void fibVectorChangedEvent(
		const eFibVectorChangedEvent * pFibVectorChanged );
	
	
	/**
	 * @see QWidget::minimumSize()
	 * @return the minimum size of this widgte;
	 * 	This is the smallest size that the widgte can have.
	 */
	virtual QSize minimumSize() const;
	
	/**
	 * @see QWidget::minimumSizeHint()
	 * @return the minimum size hint for this widgte;
	 * 	This is a small size that the widgte should have.
	 */
	virtual QSize minimumSizeHint() const;
	
	/**
	 * @return a hint for a good size of this widget
	 */
	virtual QSize sizeHint() const;
	
	/**
	 * This method returns a size hint for this element, if the maximum width
	 * is iMaxWidth (if -1 the maximum width is infinite).
	 *
	 * @param iMaxWidth the maximum width this widget should have,
	 * 	if -1 the maximum width is infinite
	 * @return a hint for a good size of this widget, if the maximum width
	 * 	is iMaxWidth.
	 */
	virtual QSize sizeHint( const int iMaxWidth ) const;
	
	/**
	 * This method returns a size hint for this element, if minimum
	 * iMinNumberOfElements of vector elements are shown in one line.
	 *
	 * @param iMinNumberOfElements the minimum number of vector elements to
	 * 	shown in one line
	 * @return a hint for a good size of this widget, if minimum
	 * 	iMinNumberOfElements of vector elements are shown in one line
	 */
	virtual QSize sizeHintForMinElementsInLine( const int iMinNumberOfElements ) const;
	
protected:
	
	/**
	 * This method will (re-)create this Fib vector widget
	 * correspondending to the actual Fib vector object.
	 * @see pFibVector
	 */
	virtual void createFibVectorWidget();
	
	
///members:
	
	/**
	 * A pointer to the Fib vector object this widget represents.
	 * @see getFibVector()
	 * @see createFibVectorWidget()
	 */
	cFibVectorCreator * pFibVector;
	
	/**
	 * The label for the name of the Fib vector.
	 */
	QLabel * pLabelNameOfFibVector;
	
	/**
	 * A list with the widgets for the vector elements.
	 * @see pFibVector
	 */
	QList< cWidgetFibVectorElement * > liVectorElements;
	
	/**
	 * The scroll area widget which contains the vector. (If the vector has
	 * to much elements to display in the widget, a slider will provide
	 * access to all elements.)
	 * @see pLayoutMain
	 */
	QScrollArea * pScrollArea;
	
	/**
	 * The variables to organize the layout of the widget.
	 */
	cFlowLayout * pLayoutBottomLine;
	QVBoxLayout * pLayoutMain;
	QVBoxLayout * pLayoutFrameMain;
	
	
	/**
	 * Mutex to lock access to the members of this class.
	 * Lock the mutex if you use one of the following containers:
	 * 	@see pLabelNameOfFibVector
	 * 	@see liVectorElements
	 * 	@see pLayoutBottomLine
	 * 	@see pLayoutMain
	 */
	mutable QMutex mutexFibVectorWidget;
	
};//end class cWidgetFibVector

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_WIDGET_FIB_VECTOR_H__





