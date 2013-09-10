
//TODO check

/**
 * @file cFibPlainTextEdit
 * file name: cFibPlainTextEdit.h
 * @author Betti Oesterholz
 * @date 03.07.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for the plain text (widget/sub window) view
 * of a Fib object.
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
 * This file specifies a class for the plain text (widget/sub window) view
 * of a Fib object.
 * @see cFibObjectMainWindow
 * It will display the XML representation of a Fib object.
 */
/*
History:
03.07.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_FIB_PLAIN_TEXT_EDIT_H__
#define ___FIB__NCREATOR__C_FIB_PLAIN_TEXT_EDIT_H__


#include "version.h"

#include "cFibElement.h"

#include "cFibNode.h"
#include "lFibNodeChanged.h"
#include "cFibNodeHandler.h"

#include <set>
#include <string>

#include <QPlainTextEdit>


namespace fib{

namespace nCreator{

//cyclic dependencies
class cFibObjectMainWindow;

class cFibPlainTextEdit: public QPlainTextEdit, public lFibNodeChanged{
		Q_OBJECT

protected:
	
	/**
	 * A pointer to the Fib node object for this widget.
	 */
	cFibNode * pFibNode;
	
	/**
	 * The version of the Fib object for the node, which is displayed.
	 * Every time the Fib object is changed the version number is counted up.
	 * If this number is not equal to the Fib node version number the shown
	 * Fib object needs to be updated.
	 * @see cFibNode::ulVersion
	 * @see cFibNode::fibObjectChanged()
	 */
	unsigned long ulFibNodeVersionDisplayed;
	
	
	/**
	 * A pointer to the main window for this widget, or NULL if non exists.
	 */
	cFibObjectMainWindow * pMainWindow;
	
	/*TODO
	 * if overwriting QTextDocument (setDocument( QTextDocument * document )) use
	 * QPlainTextDocumentLayout (see QTextDocument::setDocumentLayout())
	 * 
	 * - use QSyntaxHighlighter (reimplement highlightBlock())
	 */
	
public:

	/**
	 * parameter constructor for a Fib object node
	 *
	 * @param pInFibNode a pointer to the Fib node object for the widget to construct
	 * 	@see pFibNode
	 * @param pParent a pointer to parent of this widget
	 */
	cFibPlainTextEdit( cFibNode * pInFibNode, QWidget * pParent = NULL );
	
	/**
	 * parameter constructor for a Fib object node
	 *
	 * @param pInMainWindow a pointer to the main window for this widget
	 * 	@see pMainWindow
	 * @param pParent a pointer to parent of this widget
	 */
	cFibPlainTextEdit( cFibNode * pInFibNode, cFibObjectMainWindow * pInMainWindow );
	
	/**
	 * destructor
	 */
	virtual ~cFibPlainTextEdit();
	
	
	/**
	 * @return a pointer to the Fib node object this widget shows / represents
	 * 	@see pFibNode
	 */
	cFibNode * getFibNode();
	
	/**
	 * @return a const pointer to the Fib node object this widget shows / represents
	 * 	@see pFibNode
	 */
	const cFibNode * getFibNode() const;
	
	
	/**
	 * Event method
	 * It will be called every time a Fib node (cFibNode), at which
	 * this object is registered, was changed.
	 *
	 * @param pFibNode a pointer to the changed Fib node
	 */
	virtual void fibNodeChangedEvent(
		const eFibNodeChangedEvent * pFibNodeChanged );
	
	
	/**
	 * @return the name of this class "cFibPlainTextEdit"
	 */
	virtual std::string getName() const;
	
	
	/**
	 * This method will set the given Fib (node) object in this widget.
	 * Beware: If the Fib (node) object was set (returned true) the Fib node
	 * 	handler will handel the given Fib object (e. g. It will delete the
	 * 	Fib object, so don't delete it yourself).
	 * @see cFibNodeHandler
	 *
	 * @param pNewFibObject a pointer to the Fib object to set for this widget
	 * @return true if the given Fib object was set, else false
	 */
	virtual bool setFibObjectNode( cFibNode * pNewFibObjectNode );
	
protected:
	
	/**
	 * This method will read the settings for this widget and restores the
	 * widget to it.
	 * @see QSettings
	 */
	virtual void readSettings();
	
	/**
	 * This method will write the settings of this widget.
	 * @see QSettings
	 */
	virtual void writeSettings();
	
	/**
	 * This method handels close events.
	 *
	 * @param pEventClose a pointer to the close event to andle
	 */
	virtual void closeEvent( QCloseEvent * pEventClose );
	
	/**
	 * @return a hint for a good size of this widget
	 */
	virtual QSize sizeHint() const;
	
	/**
	 * This method shows the Fib object of the Fib node of this object in
	 * the Fib XML representation.
	 *
	 * @return true if the Fib object was displayed, else false
	 */
	bool showFibNode();
	
	/*TODO
	 * 	- methods to get (to store to an Xml file) and set (read from .xml
	 * 		file) the plain text of this text editor
	 */
	
private slots:
	
	/**
	 * This slot will notify the Fib node that it was changed, if the text
	 * for the Fib object was changed.
	 * This method should be called if the Fib object text of this widget
	 * changes. It will then try to read the Fib object text as a Fib
	 * object in the XML storeage format. If it can successfully convert
	 * The Fib object text into a Fib object, it will replace the Fib node
	 * Fib object with the read Fib object and notify the node that it was
	 * changed.
	 * @see fibNodeChangedEvent()
	 * @see QPlainTextEdit::textChanged()
	 */
	void notifyNodeForChange();
	
	
};//end class cFibPlainTextEdit

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_PLAIN_TEXT_EDIT_H__





