
//TODO check

/**
 * @file cWidgetFibInputVariable
 * file name: cWidgetFibInputVariable.h
 * @author Betti Oesterholz
 * @date 27.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a widget for a Fib input variable.
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
 * This file specifies a class for a widget for a Fib input variable.
 * It will display one input variable. This input variable is represented
 * by a name and a value.
 *
 * @see cFibInputVariable
 * @see cFibVariable
 */
/*
History:
27.08.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_WIDGET_FIB_INPUT_VARIABLE_H__
#define ___FIB__NCREATOR__C_WIDGET_FIB_INPUT_VARIABLE_H__


#include "version.h"

#include "cRoot.h"

#include "cFibInputVariable.h"
#include "lInputVariableChanged.h"

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>


using namespace std;


namespace fib{

namespace nCreator{

class cWidgetFibInputVariable: public QWidget, public lInputVariableChanged{
		Q_OBJECT
protected:
	
	/**
	 * A pointer to the input variable this widget shows.
	 */
	cFibInputVariable * pFibInputVariable;
	
	
	/**
	 * The label for the input variable name.
	 */
	QLabel * pLabelVariable;
	
	/**
	 * The field for the value of the input varaible.
	 */
	QLineEdit * pLineEditValue;
	
	/**
	 * The button to decrase the variable value.
	 */
	QPushButton * pButtonDecrease;
	
	/**
	 * The button to incrase the variable value.
	 */
	QPushButton * pButtonIncrease;
	
	
	/**
	 * The variables to organize the layout of the dialog.
	 */
	QVBoxLayout * pLayoutMain;
	QHBoxLayout * pLayoutValue;
	
	
public:
	
	/**
	 * standard constructor for a Fib object node
	 *
	 * @param pInFibInputVariable a pointer to the input variable to display
	 * @param pParent a pointer the parent of this new Fib object dialog window
	 */
	cWidgetFibInputVariable( cFibInputVariable * pInFibInputVariable,
		QWidget * pParent = NULL );
	
	/**
	 * destructor
	 */
	virtual ~cWidgetFibInputVariable();
	
	/**
	 * @return the pointer to the input variable for the widget
	 */
	cFibInputVariable * getFibInputVariable();
	
	/**
	 * @return the pointer to the input variable for the widget
	 */
	const cFibInputVariable * getFibInputVariable() const;
	
	/**
	 * Event method
	 * It will be called every time a input variable (cFibInputVariable),
	 * at which this object is registered,was changed.
	 *
	 * @param pFibInputVariableEvent a pointer to the event with the
	 * 	information of the change of the Fib input variable
	 */
	virtual void fibInputVariableChangedEvent(
		const eFibInputVariableChangedEvent * pFibInputVariableEvent );

	
	/**
	 * @return the name of this class "cWidgetFibInputVariable"
	 */
	virtual std::string getName() const;
	
protected:
	
	/**
	 * @return a hint for a good size of this window
	 */
	virtual QSize sizeHint() const;
	
protected slots:
	
	/**
	 * This method sets the value of the Fi input variable to the given value.
	 *
	 * @see pFibInputVariable
	 * @param strNewValue the string which contains the to set value for
	 * 	the variable
	 * @return true if the readed value could be set, else false
	 */
	bool setVariableValue( const QString & strNewValue );
	
	
};//end class cWidgetFibInputVariable

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_WIDGET_FIB_INPUT_VARIABLE_H__





