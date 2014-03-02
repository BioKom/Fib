/**
 * @file cWidgetFibInputVariables
 * file name: cWidgetFibScalars.h
 * @author Betti Oesterholz
 * @date 28.07.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a list of input variable widgets.
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
 * This file specifies a class for a list of input variable widgets.
 * If you have a Fib object, the input variables of it are root object
 * input variables or variables used in the Fib object but not defined in it.
 * With this class you can display these.
 *
 * @see cWidgetFibScalar
 * @see cFibInputVariable
 * @see cFibVariable
 */
/*
History:
28.07.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_WIDGET_FIB_INPUT_VARIABLES_H__
#define ___FIB__NCREATOR__C_WIDGET_FIB_INPUT_VARIABLES_H__


#include "version.h"

#include "cFibInputVariables.h"

#include <string>

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QScrollArea>
#include <QVBoxLayout>


//forward declarations
class cFlowLayout;


namespace fib{

namespace nCreator{

//forward declarations
class cFibInputVariable;


class cWidgetFibInputVariables: public QWidget,
		public cFibInputVariables{
public:

	/**
	 * The standard constructor for a list of input variable widgets.
	 * It constructs a list of input variables with no input variables. (So
	 * you can add them later.)
	 */
	cWidgetFibInputVariables();

	/**
	 * A parameter constructor for a list of input variables widgets.
	 *
	 * @param liInInputVariables list with input variables for this object
	 * 	@see inputVariables
	 * @param pInFibObject the Fib object for which the input variables are or NULL
	 * 	@see pFibObject
	 */
	explicit cWidgetFibInputVariables(
		QList< cFibInputVariable * > & liInInputVariables,
		cFibElement * pInFibObject = NULL );
	
	/**
	 * A parameter constructor for a list of input variable widgets.
	 *
	 * @param pInFibObject the Fib object for which the input variables are or NULL
	 * 	@see pFibObject
	 * @param bFindInputVariables if true it will evalue the input variables
	 * 	for the given Fib object.
	 * 	It will evalue all variables used in the Fib object, but not
	 * 	defined in it. Also input variables are input variables of the
	 * 	root element pFibObject, if pFibObject is a root element.
	 * 	@see nFibObjectTools::evalueInputVariables()
	 * 	Also the list will be updated for input variables changes.
	 * 	If bFindInputVariables is false, this constructor constructs a
	 * 	list of input variables with no input variables. (So you can add
	 * 	them later.)
	 * @param bTillRoot if true searches for input variables in the Fib
	 * 	object for pFibObject till the root Fib element (Fib element
	 * 	with no superior), else the input variables for pFibObject will
	 * 	be returned
	 */
	explicit cWidgetFibInputVariables( cFibElement * pInFibObject,
		const bool bFindInputVariables = true, const bool bTillRoot = false );
	
	/**
	 * The copy constructor for a list of input variable widgets.
	 *
	 * @param fibInputVariables the input variables widget to copy
	 */
	cWidgetFibInputVariables( cWidgetFibInputVariables & fibInputVariables );
	
	/**
	 * destructor
	 */
	virtual ~cWidgetFibInputVariables();
	
	
	/**
	 * @return the name of this class "cWidgetFibInputVariables"
	 */
	virtual std::string getName() const;
	
	
	/**
	 * This method adds the given input variable to this input variable list.
	 *
	 * @see inputVariables
	 * @see getNumberOfInputVariables()
	 * @see removeInputVariable()
	 * @see replaceInputVariable()
	 * @param pInputVariable a pointer to the input variable to add
	 * @param uiPosition the position where to add the input variable,
	 * 	if 0 or greater the number of input variables in this input
	 * 	variable list it will be added to the end of the input variable list
	 * 	(counting starts with 1)
	 * @return true if the input variable was added, else false
	 */
	virtual bool addInputVariable( cFibInputVariable * pInputVariable,
		const unsigned int uiPosition = 0 );
	
	/**
	 * This method removes the uiPosition'th input variable from this input
	 * variable list.
	 *
	 * @see inputVariables
	 * @see getNumberOfInputVariables()
	 * @see addInputVariable()
	 * @see replaceInputVariable()
	 * @param uiPosition the position where to remove the input variable from
	 * 	(counting starts with 1)
	 * @return true if the input variable was removed, else false
	 */
	virtual bool removeInputVariable( const unsigned int uiPosition );
	
	/**
	 * This method removes the given input variable from this input
	 * variable list.
	 *
	 * @see inputVariables
	 * @see getNumberOfInputVariables()
	 * @see addInputVariable()
	 * @see replaceInputVariable()
	 * @param pInputVariable the input variable to remove
	 * @return true if the input variable was removed, else false
	 */
	virtual bool removeInputVariable( cFibInputVariable * pInputVariable );
	
	/**
	 * This method replaces a input variable in this input variable list.
	 * It will replace the uiPosition'th input variable in the input
	 * variable list with the given input variable pInputVariable (if possible).
	 *
	 * @see inputVariables
	 * @see getNumberOfInputVariables()
	 * @see removeInputVariable()
	 * @see addInputVariable()
	 * @param pInputVariable a pointer to the input variable to add,
	 * 	which will replace the old input variable on the uiPosition'th position
	 * @param uiPosition the position where to replace the input variable,
	 * 	(counting starts with 1)
	 * @return true if the input variable was replace, else false
	 */
	virtual bool replaceInputVariable( cFibInputVariable * pInputVariable,
		const unsigned int uiPosition );
	
	/**
	 * This method sets the list of input variables to the given list.
	 * All old input variables of this list are removed and the given input
	 * variables added.
	 *
	 * @see inputVariables
	 * @see getNumberOfInputVariables()
	 * @see replaceInputVariable()
	 * @see removeInputVariable()
	 * @see addInputVariable()
	 * @param liInInputVariables a list of the input variables this object
	 * 	should contain
	 * @return true if the input variables could be set, else false
	 */
	virtual bool setInputVariables( QList< cFibInputVariable * > & liInInputVariables );
	
	
	/**
	 * Event method
	 * It will be called every time a input variable (cFibInputVariable),
	 * at which this object is registered, was changed.
	 *
	 * @param pFibVariableChangedEvent a pointer to the event with the
	 * 	information of the change of the Fib input variable
	 */
	virtual void changedEvent(
		const eFibVariableCreatorChangedEvent * pFibVariableChangedEvent );
	
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
	 * iMinNumberOfVariables of input variables are shown in one line.
	 *
	 * @param iMinNumberOfVariables the minimum number of input variables to
	 * 	shown in one line
	 * @return a hint for a good size of this widget, if minimum
	 * 	iMinNumberOfVariables of input variables are shown in one line
	 */
	virtual QSize sizeHintForMinElementsInLine( const int iMinNumberOfVariables ) const;
	
protected:
	
	/**
	 * A list with input variables and there widgets.
	 */
	QMap< cFibInputVariable *, QWidget * > mapInputVariables;
	
	/**
	 * The layout for the input variables.
	 */
	cFlowLayout * pInputVariableLayout;
	
	/**
	 * The scroll area widget which contains the input variables.
	 * (If the input variables has to much variables to display in the
	 * widget, a slider will provide access to all variables.)
	 * @see pLayoutMain
	 */
	QScrollArea * pScrollArea;
	
	/**
	 * The variables to organize the layout of the widget.
	 */
	QVBoxLayout * pLayoutMain;
	
};//end class cWidgetFibInputVariables

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_WIDGET_FIB_INPUT_VARIABLES_H__





