
//TODO check

/**
 * @file cWidgetFibScalar
 * file name: cWidgetFibScalar.h
 * @author Betti Oesterholz
 * @date 27.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a widget for a Fib scalar.
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
 * This file specifies a class for a widget for a Fib scalar.
 * It will display one scalar. This scalar is represented
 * by a name and a value.
 *
 * @see cFibScalar
 * @see cFibVariable
 */
/*
History:
27.08.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_WIDGET_FIB_SCALAR_H__
#define ___FIB__NCREATOR__C_WIDGET_FIB_SCALAR_H__


#include "version.h"

#include "cRoot.h"

#include "cFibScalar.h"
#include "lScalarChanged.h"

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

class cWidgetFibScalar: public QWidget, public lScalarChanged{
		Q_OBJECT
public:
	
	/**
	 * The standard constructor for a Fib scalar widget.
	 *
	 * @param pInFibScalar a pointer to the scalar to display
	 * @param pParent a pointer the parent of this new Fib scalar widget
	 */
	cWidgetFibScalar( cFibScalar * pInFibScalar,
		QWidget * pParent = NULL );
	
	/**
	 * destructor
	 */
	virtual ~cWidgetFibScalar();
	
	/**
	 * @return the pointer to the scalar for the widget
	 */
	cFibScalar * getFibScalar();
	
	/**
	 * @return the pointer to the scalar for the widget
	 */
	const cFibScalar * getFibScalar() const;
	
	/**
	 * Event method
	 * It will be called every time a scalar (cFibScalar), at which this
	 * object is registered, was changed.
	 *
	 * @param pFibScalarEvent a pointer to the event with the
	 * 	information of the change of the Fib scalar
	 */
	virtual void fibScalarChangedEvent(
		const eFibScalarChangedEvent * pFibScalarEvent );

	
	/**
	 * @return the name of this class "cWidgetFibScalar"
	 */
	virtual std::string getName() const;
	
public slots:
	
	/**
	 * This method sets the value of the Fib scalar to the given value.
	 *
	 * @see pFibScalar
	 * @param strNewValue the string which contains the to set value for
	 * 	the scalar
	 * @return true if the readed value could be set, else false
	 */
	bool setScalarValue( const QString & strNewValue );
	
protected:
	
	/**
	 * @return a hint for a good size of this window
	 */
	virtual QSize sizeHint() const;
	
//members:
	
	/**
	 * A pointer to the scalar this widget shows.
	 */
	cFibScalar * pFibScalar;
	
	
	/**
	 * The label for the scalar name.
	 */
	QLabel * pLabelVariable;
	
	/**
	 * The field for the value of the scalar.
	 */
	QLineEdit * pLineEditValue;
	
	/**
	 * The button to decrase the scalar value.
	 */
	QPushButton * pButtonDecrease;
	
	/**
	 * The button to incrase the scalar value.
	 */
	QPushButton * pButtonIncrease;
	
	
	/**
	 * The scalars to organize the layout of the dialog.
	 */
	QVBoxLayout * pLayoutMain;
	QHBoxLayout * pLayoutValue;
	
	
};//end class cWidgetFibScalar

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_WIDGET_FIB_SCALAR_H__





