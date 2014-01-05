
//TODO check

/**
 * @file cTextField
 * file name: cTextField.cpp
 * @author Betti Oesterholz
 * @date 14.12.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a widget for a text field.
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
 * This file implements a class for a widget for a text field.
 * It uses the QT text edit class (QTextEdit), but is default not readebel
 * and sends mouse events to its parent.
 *
 * @see QTextEdit
 */
/*
History:
14.12.2013  Oesterholz  created
*/


#include "cTextField.h"

#include <QApplication>


/**
 * The standard constructor for a text field.
 *
 * @see QTextEdit::QTextEdit()
 * @param pParent a pointer the parent of this new text field
 */
cTextField::cTextField( QWidget * pParent ): QTextEdit( pParent ) {
	//text field is only readebel
	setReadOnly( true );
}


/**
 * The parameter constructor for a text field.
 *
 * @see QTextEdit::QTextEdit()
 * @param szText the text for the text field to create
 * @param pParent a pointer the parent of this new text field
 */
cTextField::cTextField( const QString & szText, QWidget * pParent ):
		QTextEdit( szText, pParent ) {
	//text field is only readebel
	setReadOnly( true );
}


/**
 * destructor
 */
cTextField::~cTextField(){
	//nothing to do
}


/**
 * This method sends the mouse press event to the parent of this object
 * and the paranet class (QTextEdit).
 *
 * @see QTextEdit::mousePressEvent()
 * @param pMouseEvent a pointer to the mouse press event
 */
void cTextField::mousePressEvent( QMouseEvent * pMouseEvent ){
	
	if ( pMouseEvent == NULL ) {
		//no event -> nothing to do
		return;
	}
	
	QTextEdit::mousePressEvent( pMouseEvent );
	
	QWidget* pParent = parentWidget();
	if ( pParent ) {
		//parent widget exists -> send mouse press event to parrent widget
		QMouseEvent* pNewMouseEvent = new QMouseEvent(
			pMouseEvent->type(), pMouseEvent->pos(),
			pMouseEvent->button(), pMouseEvent->buttons(),
			pMouseEvent->modifiers() );
		if ( pNewMouseEvent ) {
			QApplication::postEvent( pParent, pNewMouseEvent );
		}
	}
}



