
//TODO check

/**
 * @file cFibPlainTextEdit
 * file name: cFibPlainTextEdit.cpp
 * @author Betti Oesterholz
 * @date 03.07.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for the plain text (widget/sub window) view
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
 * This file implements a class for the plain text (widget/sub window) view
 * of a Fib object.
 * @see cFibObjectMainWindow
 * It will display the XML representation of a Fib object.
 */
/*
History:
03.07.2013  Oesterholz  created
*/


//TODO switches for test proposes
//#define DEBUG
//#define DEBUG_FIB_OBJECT


#include "cFibPlainTextEdit.h"

#include <sstream>

#include <QSettings>
#include <QStatusBar>
#include <QPoint>
#include <QSize>

#include "cFibObjectMainWindow.h"
#include "eFibNodeChangedEvent.h"


using namespace std;

using namespace fib::nCreator;


/**
 * parameter constructor for a Fib object node
 *
 * @param pInFibNode a pointer to the Fib node object for the widget to construct
 * 	@see pFibNode
 * @param pParent a pointer to parent of this widget
 */
cFibPlainTextEdit::cFibPlainTextEdit( cFibNode * pInFibNode, QWidget * pParent ):
		QPlainTextEdit( pParent ), pFibNode( pInFibNode ) {
	
	DEBUG_OUT_L2(<<"cFibPlainTextEdit("<<this<<")::cFibPlainTextEdit( pInFibNode="<<pInFibNode<<", pParent="<<pParent<<") called"<<endl<<flush);

	if ( pFibNode ) {
		pFibNode->registerNodeChangeListener( this );
	}
	//restore the old session
	readSettings();
	
	//show the set Fib object
	connect( this, SIGNAL(signalShowFibNode()), this, SLOT(showFibNode()) );
	emit signalShowFibNode();
	
	//connect document changes with the slot for updating the Fib object
	connect( document(), SIGNAL( contentsChanged() ),
		this, SLOT( notifyNodeForChange() ) );
}


/**
 * parameter constructor for a Fib object node
 *
 * @param pInMainWindow a pointer to the main window for this widget
 * 	@see pMainWindow
 * @param pParent a pointer to parent of this widget
 */
cFibPlainTextEdit::cFibPlainTextEdit( cFibNode * pInFibNode,
			cFibObjectMainWindow * pInMainWindow ):
		QPlainTextEdit( pInMainWindow ), pFibNode( pInFibNode ),
		pMainWindow( pInMainWindow ) {
	
	DEBUG_OUT_L2(<<"cFibPlainTextEdit("<<this<<")::cFibPlainTextEdit( pInFibNode="<<pInFibNode<<", pInMainWindow="<<pInMainWindow<<") called"<<endl<<flush);
	
	if ( pFibNode ) {
		pFibNode->registerNodeChangeListener( this );
	}
	//restore the old session
	readSettings();
	
	//show the set Fib object
	connect( this, SIGNAL(signalShowFibNode()), this, SLOT(showFibNode()) );
	emit signalShowFibNode();
	
	//connect document changes with the slot for updating the Fib object
	connect( document(), SIGNAL( contentsChanged() ),
		this, SLOT( notifyNodeForChange() ) );
}



/**
 * destructor
 */
cFibPlainTextEdit::~cFibPlainTextEdit() {
	//nothing to do
	DEBUG_OUT_L2(<<"cFibPlainTextEdit("<<this<<")::~cFibPlainTextEdit() called"<<endl<<flush);
	if ( pFibNode ) {
		pFibNode->unregisterNodeChangeListener( this );
	}
}


/**
 * @return a pointer to the Fib node object this widget shows / represents
 * 	@see pFibNode
 */
cFibNode * cFibPlainTextEdit::getFibNode() {
	
	return pFibNode;
}


/**
 * @return a const pointer to the Fib node object this widget shows / represents
 * 	@see pFibNode
 */
const cFibNode * cFibPlainTextEdit::getFibNode() const{
	
	return pFibNode;
}


/**
 * Event method
 * It will be called every time a Fib node (cFibNode), at which
 * this object is registered, was changed.
 *
 * @param pFibNode a pointer to the changed Fib node
 */
void cFibPlainTextEdit::fibNodeChangedEvent(
	const eFibNodeChangedEvent * pFibNodeChanged ) {
	
	DEBUG_OUT_L4(<<"cFibPlainTextEdit("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<") called"<<endl<<flush);
	if ( pFibNodeChanged == NULL ) {
		//no Fib node change event
		return;
	}
	//evalue if change should be displayed
	const cFibNode * pChangedNode = pFibNodeChanged->getChangedNode();
	if ( pChangedNode ) {
		
		if ( pFibNodeChanged->isDeleted() && ( pChangedNode == pFibNode ) ) {
			/*node of this plain text view deleted
			 *-> set NULL as this this plain text view node*/
			DEBUG_OUT_L4(<<"cFibPlainTextEdit("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<") done set NULL as this this plain text view node"<<endl<<flush);
			
			setFibObjectNode( NULL );
			
			DEBUG_OUT_L4(<<"cFibPlainTextEdit("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<") done node of this plain text view deleted"<<endl<<flush);
			return;
		}//else this plain text view node not deleted
		
		if ( pFibNodeChanged->getChangeBy() != this ) {
			//if not this node called
			//check the node version getFibObjectVersion()
			if ( pChangedNode->getFibObjectVersion() !=
					ulFibNodeVersionDisplayed ) {
				//version is not equal to displayed Fib object version
				emit signalShowFibNode();
			}
		}
	}//else don't display node again
	DEBUG_OUT_L4(<<"cFibPlainTextEdit("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<") done"<<endl<<flush);
}


/**
 * @return the name of this class "cFibPlainTextEdit"
 */
string cFibPlainTextEdit::getName() const{
	
	return string( "cFibPlainTextEdit" );
}


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
bool cFibPlainTextEdit::setFibObjectNode( cFibNode * pNewFibObjectNode ) {
	
	DEBUG_OUT_L2(<<"cFibPlainTextEdit("<<this<<")::setFibObjectNode( pNewFibObjectNode="<<pNewFibObjectNode<<") called"<<endl<<flush);
	
#ifdef DEBUG_FIB_OBJECT
	cout<<"cFibPlainTextEdit("<<this<<")::setFibObjectNode( pNewFibObjectNode ) pNewFibObjectNode:"<<endl;
	if ( pNewFibObjectNode && ( pNewFibObjectNode->getFibObject() != NULL ) ) {
		pNewFibObjectNode->getFibObject()->storeXml( cout );
	}else{
		cout<<"NULL";
	}
	cout<<"done"<<endl<<flush;
#endif //DEBUG_FIB_OBJECT
	
	if ( pFibNode ) {
		pFibNode->unregisterNodeChangeListener( this );
	}
	pFibNode = pNewFibObjectNode;
	if ( pFibNode ) {
		pFibNode->registerNodeChangeListener( this );
	}
	emit signalShowFibNode();
	return true;
}



/**
 * This method will read the settings for this widget and restores the
 * widget to it.
 * @see QSettings
 */
void cFibPlainTextEdit::readSettings() {
	
	QSettings settings("Fib development", "Fib creator");
	QPoint pos = settings.value("fibPlainTextWindow/pos", QPoint( 0, 0 ) ).toPoint();
	QSize size = settings.value("fibPlainTextWindow/size", sizeHint() ).toSize();
	resize( size );
	move( pos);
}


/**
 * This method will write the settings of this widget.
 * @see QSettings
 */
void cFibPlainTextEdit::writeSettings() {
	
	QSettings settings("Fib development", "Fib creator");
	settings.setValue("fibPlainTextWindow/pos", pos() );
	settings.setValue("fibPlainTextWindow/size", size() );
}


/**
 * This method handels close events.
 *
 * @param pEventClose a pointer to the close event to andle
 */
void cFibPlainTextEdit::closeEvent( QCloseEvent * pEventClose ) {
	
	DEBUG_OUT_L2(<<"cFibPlainTextEdit("<<this<<")::closeEvent() called"<<endl<<flush);
	
	//TODO check if the Fib object was stored in node
	
	//if ( fibObjectDataSave() ) {
		//Fib object is save
		writeSettings();
		pEventClose->accept();
	/*}else{//Fib object not saved -> ignore close event
		pEventClose->ignore();
	}*/
}


/**
 * @return a hint for a good size of this widget
 */
QSize cFibPlainTextEdit::sizeHint() const{
	
	return QSize( 400, 480 );
}


/**
 * This method shows the Fib object of the Fib node of this object in
 * the Fib XML representation.
 *
 * @return true if the Fib object was displayed, else false
 */
bool cFibPlainTextEdit::showFibNode() {
	
	DEBUG_OUT_L2(<<"cFibPlainTextEdit("<<this<<")::showFibNode() called"<<endl<<flush);
	
#ifdef DEBUG_FIB_OBJECT
	cout<<"cFibPlainTextEdit("<<this<<")::showFibNode() pFibNode:"<<endl;
	if ( pFibNode && ( pFibNode->getFibObject() != NULL ) ) {
		pFibNode->getFibObject()->storeXml( cout );
	}else{
		cout<<"NULL";
	}
	cout<<"done"<<endl<<flush;
#endif //DEBUG_FIB_OBJECT
	
	QTextDocument * pDocument = document();
	if ( pDocument == NULL ) {
		//no document -> cant set text
		DEBUG_OUT_EL2(<<"cFibPlainTextEdit("<<this<<")::showFibNode() done no document -> cant set text"<<endl<<flush);
		return false;
	}
	if ( ( pFibNode == NULL ) || ( pFibNode->getFibObject() == NULL ) ) {
		//create emty document
		DEBUG_OUT_L2(<<"cFibPlainTextEdit("<<this<<")::showFibNode() create emty document"<<endl<<flush);
		pDocument->setPlainText( QString() );
		return true;
	}
	
	//write nodes Fib object as XML plaintext to the document
	//lock Fib node (Fib object master root)
	cFibNodeHandler * pFibNodeHandler = cFibNodeHandler::getInstance();
	pFibNodeHandler->lock( pFibNode );
	
	//store the Fib object in the XML representation
	std::ostringstream streamFibObject;
	
	const bool bFibObjectStored = pFibNode->getFibObject()->storeXml(
		streamFibObject );
	const unsigned long ulFibNodeVersionToDisplayed = pFibNode->getFibObjectVersion();
	
	pFibNodeHandler->unlock( pFibNode );
	
	if ( bFibObjectStored ) {
		//Fib object stored in XML -> show the stores Fib object
		pDocument->setPlainText( QString( streamFibObject.str().c_str() ) );
		//update displayed Fib object version number
		ulFibNodeVersionDisplayed = ulFibNodeVersionToDisplayed;
	}
	
	DEBUG_OUT_L2(<<"cFibPlainTextEdit("<<this<<")::showFibNode() done"<<endl<<flush);
	return true;
}
/*TODO
 * 	- method to integrate a (changed) Fib object parts
 * 		(? from Fib element number to element number)
 * 	- methods to get (to store to an Xml file) and set (read from .xml
 * 		file) the plain text of this text editor
 */



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
void cFibPlainTextEdit::notifyNodeForChange() {
	
	DEBUG_OUT_L2(<<"cFibPlainTextEdit("<<this<<")::notifyNodeForChange() called"<<endl<<flush);
	
	QTextDocument * pDocument = document();
	if ( pDocument == NULL ) {
		//no document -> can't set text
		DEBUG_OUT_L4(<<"cFibPlainTextEdit("<<this<<")::notifyNodeForChange() no document -> can't set text"<<endl<<flush);
		return;
	}
	
	//try to read the Fib object from the document
	istringstream streamFibObject( pDocument->toPlainText().toStdString() );
	
	intFib iOutStatus = 0;
	
	DEBUG_OUT_L4(<<"cFibElement * pRestoredFibObject = cFibElement::restoreXml( streamFibObject, &iOutStatus );"<<endl<<flush);
	cFibElement * pRestoredFibObject =
		cFibElement::restoreXml( streamFibObject, &iOutStatus );
	DEBUG_OUT_L4(<<"   done"<<endl<<flush);
	
	if ( ( pRestoredFibObject == NULL ) || ( iOutStatus < 0 ) ) {
		//error while restoring -> don't set Fib object
		if ( pMainWindow ) {
			//set status text in the main window
			pMainWindow->statusBar()->showMessage(
				tr("Fib object in text window contains errors"), 2000 );
		}
		DEBUG_OUT_L4(<<"cFibPlainTextEdit("<<this<<")::notifyNodeForChange() error while restoring -> don't set Fib object"<<endl<<flush);
		return;
	}
	if ( 0 < iOutStatus ) {
		// if warning -> write status message
		if ( pMainWindow ) {
			//set status text in the main window
			pMainWindow->statusBar()->showMessage(
				tr("Fib object in text window contains warnings"), 2000 );
		}
		DEBUG_OUT_L4(<<"cFibPlainTextEdit("<<this<<")::notifyNodeForChange() warning -> write status message"<<endl<<flush);
	}
	/*if read Fib object is not equal to Fib node Fib object
	-> replace Fib node Fib object with read Fib object and notify node of change*/
	DEBUG_OUT_L4(<<"cFibNodeHandler * pFibNodeHandler = cFibNodeHandler::getInstance();"<<endl<<flush);
	cFibNodeHandler * pFibNodeHandler = cFibNodeHandler::getInstance();
	
	if ( pFibNode == NULL ) {
		//create new Fib node
		cFibNode * pNewFibNode = pFibNodeHandler->getNodeForFibObject(
			pRestoredFibObject, this );
		//register as Fib node in parent, if no Fib node is registered in it
		if ( pMainWindow ) {
			//set status text in the main window
			pMainWindow->setFibObjectNode( pNewFibNode );
		}
		return;
	}
	
	DEBUG_OUT_L4(<<"pFibNodeHandler->integrateFibObjectIntoNode( pFibNode, pFibNode->getFibObject(), pRestoredFibObject="<<pRestoredFibObject<<" );"<<endl<<flush);
	pFibNodeHandler->integrateFibObjectIntoNode( pFibNode,
		pFibNode->getFibObject(), pRestoredFibObject, this );
	
	DEBUG_OUT_L2(<<"cFibPlainTextEdit("<<this<<")::notifyNodeForChange() done"<<endl<<flush);
}











