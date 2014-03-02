/**
 * @file cTextField
 * file name: cTextField.h
 * @author Betti Oesterholz
 * @date 14.12.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a widget for a text field.
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
 * This file specifies a class for a widget for a text field.
 * It uses the QT text edit class (QTextEdit), but is default not readebel
 * and sends mouse events to its parent.
 *
 * @see QTextEdit
 */
/*
History:
14.12.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_TEXT_FIELD_H__
#define ___FIB__NCREATOR__C_TEXT_FIELD_H__


#include "version.h"

#include <QTextEdit>
#include <QString>
#include <QWidget>
#include <QMouseEvent>


class cTextField: public QTextEdit{
		Q_OBJECT
public:
	
	/**
	 * The standard constructor for a text field.
	 *
	 * @see QTextEdit::QTextEdit()
	 * @param pParent a pointer the parent of this new text field
	 */
	cTextField( QWidget * pParent = NULL );
	
	/**
	 * The parameter constructor for a text field.
	 *
	 * @see QTextEdit::QTextEdit()
	 * @param szText the text for the text field to create
	 * @param pParent a pointer the parent of this new text field
	 */
	cTextField( const QString & szText, QWidget * pParent = NULL );
	
	/**
	 * destructor
	 */
	virtual ~cTextField();
	
protected:
	
	/**
	 * This method sends the mouse press event to the parent of this object
	 * and the parent class (QTextEdit).
	 *
	 * @see QTextEdit::mousePressEvent()
	 * @param pMouseEvent a pointer to the mouse press event
	 */
	virtual void mousePressEvent( QMouseEvent * pMouseEvent );
	
};//end class cTextField

#endif //___FIB__NCREATOR__C_TEXT_FIELD_H__





