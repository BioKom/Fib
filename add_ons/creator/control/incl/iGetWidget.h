/**
 * @file iGetWidget
 * file name: iGetWidget.h
 * @author Betti Oesterholz
 * @date 30.11.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a interface for classes which create there own widget.
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
 * This file specifies a interface for classes which create there own widget.
 * For some objects (which are not widgets) you will need a widget to
 * display them. These objects can provide a method to create the widget
 * for them. This interface can be used to identify all such objects.
 * @pattern interface
 * @see cFibScalar
 * @see eFibScalarChangedEvent
 */
/*
History:
30.11.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__I_GET_WIDGET_H__
#define ___FIB__NCREATOR__I_GET_WIDGET_H__


#include "version.h"

#include <string>

#include <QWidget>


namespace fib{

namespace nCreator{

class iGetWidget{
public:
	
	/**
	 * This method will create a widget, which displays this object.
	 * ATTENTION: You have to care that the returned widget is deleted.
	 *
	 * @param pParent a pointer the parent of the to create widget
	 * @return a pointer to the created widget, or NULL if non could be created
	 */
	virtual QWidget * getWidget( QWidget * pParent = NULL ) = 0;
	
	/**
	 * @return the name of the class
	 */
	virtual std::string getName() const = 0;
	
};//end class iGetWidget

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__I_GET_WIDGET_H__





