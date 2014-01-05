
//TODO check

/**
 * @file cWidgetFibVectorElement
 * file name: cWidgetFibVectorElement.h
 * @author Betti Oesterholz
 * @date 31.12.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a vector element widget.
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
 * This file specifies a class for a vector element widget.
 * If you have a Fib element, elements of vector of it can be displayed
 * with this class for the Fib creator modul.
 * A Fib vector contains a number of element.
 *
 * @see cWidgetFibVector
 * @see cWidgetFibScalar
 * @see cFibVectorCreator
 * @see fib::cFibVector
 * @see cFibScalar
 *
 * It should look like:
 * +-------------------------------+
 * | - type (choose type combobox) |
 * | - element                     |
 * +-------------------------------+
 *
 * - if the element is a variable its widget will be look like:
 * +---------------------------------------------------------+
 * | - variable name (choose variable by name from combobox) |
 * | - if possible: [show] button (= to definition)          |
 * +---------------------------------------------------------+
 *
 * - else the elements (e. g. scalar) widget will be displayed
 * 	@see iGetWidget::getWidget()
 * 
 */
/*
History:
31.12.2013  Oesterholz  created
*/

#ifndef ___FIB__NCREATOR__C_WIDGET_FIB_VECTOR_ELEMENT_H__
#define ___FIB__NCREATOR__C_WIDGET_FIB_VECTOR_ELEMENT_H__


#include "version.h"

#include <QWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QMutex>
#include <QList>

#include "fibDatatyps.h"

#include "iGetWidget.h"
#include "lFibVectorChanged.h"
#include "cFibVariableCreator.h"
#include "lFibNodeChanged.h"


namespace fib{

namespace nCreator{

//forward declarations
class cFibVectorCreator;
class eFibVectorChangedEvent;
class cFibNode;


class cWidgetFibVectorElement: public QWidget, public lFibVectorChanged,
		public lFibVariableCreatorChanged, public lFibNodeChanged{
		Q_OBJECT
public:
	
	/**
	 * The standard constructor for a Fib vector element widget.
	 *
	 * @param pInFibVector a pointer to the Fib vector object for this widget element
	 * 	@see pFibVector
	 * @param uiInNumberOfElement the number of the vector element for which
	 * 	this widget is (Counting starts with 1 .)
	 * 	@see uiNumberOfElement
	 * @param pParent a pointer the parent of this new Fib vector element widget
	 */
	cWidgetFibVectorElement( cFibVectorCreator * pInFibVector,
		const unsigned int uiInNumberOfElement,
		QWidget * pParent = NULL );

	/**
	 * destructor
	 */
	virtual ~cWidgetFibVectorElement();
	
	/**
	 * This method returns the number of the Fib vector element this widget
	 * represents. (Counting starts with 1 .)
	 *
	 * @see uiNumberOfElement
	 * @see setFibVectorElementNumber()
	 * @see pFibVector
	 * @return the number of the Fib vector element this widget represents
	 */
	unsigned int getFibVectorElementNumber() const;
	
	/**
	 * This method sets the number of the Fib vector element this widget
	 * represents. (Counting starts with 1 .)
	 *
	 * @see uiNumberOfElement
	 * @see getFibVectorElementNumber()
	 * @see pFibVector
	 * @param uiInNumberOfElement the number of the Fib vector element this
	 * 	widget represents to set
	 * @return true if the number could be set, else false
	 */
	bool setFibVectorElementNumber( unsigned int uiInNumberOfElement );

	/**
	 * This method returns a pointer to the Fib vector element object of
	 * this widget.
	 * Note: Don't delete the returned Fib vector object.
	 *
	 * @see uiNumberOfElement
	 * @see setFibVectorElement()
	 * @see pFibVector
	 * @return a const pointer to the Fib vector element object of this widget
	 */
	const iGetWidget * getFibVectorElement() const;
	
	/**
	 * This method returns a pointer to the Fib vector element object of
	 * this widget.
	 * Note: Don't delete the returned Fib vector object.
	 *
	 * @see uiNumberOfElement
	 * @see setFibVectorElement()
	 * @see pFibVector
	 * @return a pointer to the Fib vector element object of this widget
	 */
	iGetWidget * getFibVectorElement();

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
	 * @return the name of this class "cWidgetFibVectorElement"
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
	 * Event method
	 * It will be called every time a input variable (cFibInputVariable),
	 * at which this object is registered,was changed.
	 *
	 * @param pFibVariableChangedEvent a pointer to the event with the
	 * 	information of the change of the Fib input variable
	 */
	virtual void changedEvent(
		const eFibVariableCreatorChangedEvent * pFibVariableChangedEvent );

	/**
	 * Event method
	 * It will be called every time a Fib node (cFibNode), at which
	 * this object is registered, was changed.
	 *
	 * @param pFibNodeChanged a pointer to the event, with the information
	 * 	about the changed Fib node
	 */
	virtual void fibNodeChangedEvent(
		const eFibNodeChangedEvent * pFibNodeChanged );
	
protected slots:
	
	
	/**
	 * This slot sets the type of the vector element to the given type.
	 * Note: This method will also adapt the vector pFibVector.
	 *
	 * @see pChooseType
	 * @see pFibVector
	 * @param iSelectedItem the index for the selected type:
	 * 	0: select value
	 * 	1: select variable
	 * @return true if type could be set, else false
	 */
	bool slotChangeTypeTo( const int iSelectedItem );
	
	/**
	 * This slot sets the vector element to the given variable.
	 * Note: This method will also adapt the vector pFibVector.
	 *
	 * @see liDefinedVariables
	 * @see pChooseVariable
	 * @param iSelectedItem the index for the selected variable (in
	 * 	liDefinedVariables and pChooseVariable)
	 * @return true if variable could be set, else false
	 */
	bool slotSetSelectedVariable( const int iSelectedVariable );
	
protected:
	
	/**
	 * This method will (re-)create this Fib vector element widget
	 * correspondending to the actual Fib vector object.
	 * @see pFibVector
	 */
	virtual void createFibVectorElementWidget();
	
	/**
	 * This method creates the choose type subwidget of this widget.
	 *
	 * @see pChooseType
	 * @see createFibVectorElementWidget
	 * @param pVectorElement the vector element for which to create the widget
	 * @return a pointer to the choose type widget for this element
	 */
	virtual QComboBox * createChooseType( const iGetWidget * pVectorElement ) const;
	
	/**
	 * This method evalues the for the Fib vector element defined variables.
	 * Note: it won't use a mutex (mutexFibVectorElementWidget).
	 *
	 * @return a list with the Fib creator variables of the Fib variables,
	 * 	which are defined for the Fib element of the vector for this vector element
	 */
	QList< cFibVariableCreator * > getDefinedVariables();
	
	/**
	 * This method clears the defined variables (liDefinedVariables).
	 * It will also unregister this object at all defined variables.
	 * Note: it won't use a mutex (mutexFibVectorElementWidget).
	 *
	 * @see liDefinedVariables
	 */
	void clearDefinedVariables();
	
	/**
	 * @return a hint for a good size of this widget
	 */
	virtual QSize sizeHint() const;
	
	
///members:
	
	/**
	 * The number of the Fib vector element this widget represents.
	 * (Counting starts with 1 , 0 stands for: not a valid vector element.)
	 * @see pFibVector
	 * @see getFibVectorElementNumber()
	 * @see setFibVectorElementNumber()
	 * @see getFibVectorElement()
	 * @see setFibVectorElement()
	 * @see createFibVectorElementWidget()
	 */
	unsigned int uiNumberOfElement;
	
#ifdef TODO_WEG
	/**
	 * A pointer to the Fib vector element object this widget represents.
	 * @see getFibVectorElement()
	 * @see setFibVectorElement()
	 * @see createFibVectorElementWidget()
	 */
	//TODO change to number
	iGetWidget * pElement;
#endif //TODO_WEG
	
	/**
	 * A pointer to the last set variable element widget of this vector
	 * element widget, or NULL.
	 * If you change the vector element type back to a variable, the
	 * last set variable will be reset.
	 * @see getFibVectorElement()
	 * @see setFibVectorElement()
	 * @see createFibVectorElementWidget()
	 */
	cFibVariableCreator * pLastSetVariable;
	
	/**
	 * The last set value of this vector element widget.
	 * If you change the vector element type back to a value, the
	 * last set value will be reset.
	 * @see getFibVectorElement()
	 * @see setFibVectorElement()
	 * @see createFibVectorElementWidget()
	 */
	doubleFib dLastSetValue;
	
	
	/**
	 * A pointer to the Fib vector object this widget represents.
	 * @see getFibVector()
	 * @see createFibVectorElementWidget()
	 */
	cFibVectorCreator * pFibVector;
	
	/**
	 * Mutex to lock access to the (non widget) members of this class.
	 * Lock the mutex if you use one of the following containers:
	 * 	@see uiNumberOfElement
	 * 	@see pLastSetVariable
	 * 	@see pFibVector
	 */
	mutable QMutex mutexFibVectorElement;
	
	
	/**
	 * The combo box to choose the vector element type from.
	 * Possible types are:
	 * 	- value
	 * 	- variable
	 * 	-(TODO) new variable
	 * @see liDefinedVariables
	 * @see mutexFibVectorElementWidget
	 */
	QComboBox * pChooseType;
	
	
	/**
	 * The combo box with the variable names which can be choosen.
	 * If NULL this vector element is not for a variable.
	 * The order is the same as in liDefinedVariables .
	 * @see liDefinedVariables
	 * @see mutexFibVectorElementWidget
	 */
	QComboBox * pChooseVariable;
	
	/**
	 * The list with the for the vector defined variables, in the reversed
	 * order of their definition (highest defined variable at the end of list).
	 * The combo box to choose a variable will contain the variable names
	 * in the same order. If pChooseVariable is NULL (element not for a variable)
	 * @see pChooseVariable
	 * @see mutexFibVectorElementWidget
	 */
	QList< cFibVariableCreator * > liDefinedVariables;
	
	/**
	 * The top most node for the Fib object for the vector.
	 * The widget needs to know it so it  can react if the defined
	 * variables in node change.
	 * @see liDefinedVariables
	 * @see mutexFibVectorElementWidget
	 */
	cFibNode * pMasterNode;
	
	/**
	 * If not NULL the widget for the element.
	 * @see iGetWidget::getWidget()
	 * @see getFibVectorElement()
	 * @see mutexFibVectorElementWidget
	 */
	QWidget * pElementWidget;
	
	/**
	 * A list with the widgets for the vector element.
	 * It contains all elements of this widget:
	 * 	- pChooseType
	 * 	- if existing pChooseVariable
	 * 	- if existing the widget for the element
	 * 		@see iGetWidget::getWidget()
	 * 	-(TODO) if existing the button the display the variable definition
	 * Beware: Don't delete the elements of this list, delete the elements
	 * 	via their member pointers ( e.g. pChooseType->deleteLater()).
	 * @see pFibVector
	 * @see mutexFibVectorElementWidget
	 */
	QList< QWidget * > liVectorElement;
	
	/**
	 * The variable to organize the layout of the widget.
	 * It will display (in this order):
	 * 	@see pChooseType
	 * 	@see liVectorElement
	 * @see mutexFibVectorElementWidget
	 *
	 */
	QVBoxLayout * pLayoutMain;
	
	
	/**
	 * Mutex to lock access to the members of this class.
	 * Lock the mutex if you use one of the following containers:
	 * 	@see pChooseType
	 * 	@see pChooseVariable
	 * 	@see liDefinedVariables
	 * 	@see liVectorElement
	 * 	@see pLayoutMain
	 */
	mutable QMutex mutexFibVectorElementWidget;
	
};//end class cWidgetFibVectorElement

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_WIDGET_FIB_VECTOR_ELEMENT_H__





