/**
 * @file cWidgetFibObjectInfo
 * file name: cWidgetFibObjectInfo.cpp
 * @author Betti Oesterholz
 * @date 09.10.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a widget for the information about a
 * Fib object.
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
 * This file implements a class for a widget for the information about a
 * Fib object.
 *
 * It should look like:
 * +-------------------------------------------------+
 * | - name @see szNameOfFibObject                   |
 * | - preview or description @see szDescription     |
 * |      - switch by parameter or click on by mouse |
 * | - number of input variables ->pic-> number of - |
 * |      subobjects ;    number of Fib elements;    |
 * |      changebel (=green or red for not changebel)|
 * +-------------------------------------------------+
 *
 */
/*
History:
09.10.2013  Oesterholz  created
*/


//switches for test proposes
//#define DEBUG


#include "cWidgetFibObjectInfo.h"

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "cFibElement.h"

#include "cTextField.h"

#include "lSelectedWidgetFibObjectInfo.h"
#include "cFibGraphicsScene.h"
#include "cFibObjectSourcePath.h"
#include "cFibObjectSourceFibDb.h"


using namespace fib::nCreator;
using namespace std;




/**
 * The standard constructor for a Fib object info widget.
 *
 * @param pInFibObjectInfo a pointer to the Fib object info object for this widget
 * 	@see pFibObjectInfo
 * @param pParent a pointer the parent of this new Fib object info widget
 */
cWidgetFibObjectInfo::cWidgetFibObjectInfo( cFibObjectInfo * pInFibObjectInfo,
		QWidget * pParent ): QFrame( pParent ),
		pFibObjectInfo( pInFibObjectInfo ), bSelected( false ),
		pLabelNameOfFibObject( NULL ), centerViewMode( ED_PREVIEW ),
		pTextDescription( NULL ),
		pScenePreviewPicture( NULL ), pViewPreviewPicture( NULL ),
		pLabelNumberOfInputVariables( NULL ), pLabelNumberOfFibElements( NULL ), pLabelNumberOfExtSubobjects( NULL ),
		pLayoutCenter( NULL ), pLayoutBottomLine( NULL ), pLayoutMain( NULL ){
	
	setLineWidth( 1 );
	setFrameStyle( QFrame::Panel | QFrame::Raised );
	
	createFibObjectInfoWidget();
}


/**
 * destructor
 */
cWidgetFibObjectInfo::~cWidgetFibObjectInfo(){
	//nothing to do
}


/**
 * This method returns a pointer to the Fib object info object of this
 * widget.
 * Note: Don't delete the returned Fib object info object.
 *
 * @see pFibObjectInfo
 * @return a pointer to the Fib object info object of this widget
 */
const cFibObjectInfo * cWidgetFibObjectInfo::getFibObjectInfo() const{
	
	return pFibObjectInfo;
}


/**
 * This method returns a pointer to the Fib object info object of this
 * widget.
 * Note: Don't delete the returned Fib object info object.
 *
 * @see pFibObjectInfo
 * @return a pointer to the Fib object info object of this widget
 */
cFibObjectInfo * cWidgetFibObjectInfo::getFibObjectInfo(){
	
	return pFibObjectInfo;
}


/**
 * @return the name of this class "cWidgetFibObjectInfo"
 */
std::string cWidgetFibObjectInfo::getName() const{
	
	return ((std::string)("cWidgetFibObjectInfo"));
}


/**
 * This method sets if this Fib object info widget is selected or not.
 *
 * @param bInSelected true if this widget is selected, else false
 */
void cWidgetFibObjectInfo::setSelected( bool bInSelected ){
	
	bSelected = bInSelected;
	if ( bSelected ){
		//highlight this widget
		setBackgroundRole( QPalette::Highlight );
		return;
	}//else
	//use default beckground role for this widget
	setBackgroundRole( QPalette::NoRole );
}


/**
 * Event method
 * It will be called every time a Fib object info object (cFibObjectInfo),
 * at which this object is registered, was changed.
 *
 * @param pFibObjectInfoChanged a pointer to the event, with the information
 * 	about the changed Fib node
 */
void cWidgetFibObjectInfo::fibObjectInfoChanged(
	const eFibObjectInfoChangedEvent * pFibObjectInfoChanged ){
	
	if ( ( pFibObjectInfoChanged == NULL ) ||
			( pFibObjectInfoChanged->getFibObjectInfo() == NULL ) ){
		//no Fib object info event -> nothing to do
		return;
	}
	if ( pFibObjectInfoChanged->getFibObjectInfo() == pFibObjectInfo ){
		//the Fib object info for the event is the Fib object info for this widget
		if ( pFibObjectInfoChanged->isDeleted() ){
			//the Fib object info object was deleted
			pFibObjectInfo = NULL;
		}//the Fib object info object was changed -> redraw this widget
		createFibObjectInfoWidget();
		return;
	}
	
}


/**
 * With this function you can register a listeners for changes for the
 * selected Fib object info widget.
 *
 * @see cWidgetFibObjectInfo::registerListenerSelectedFibObjectInfo()
 * @see unregisterListenerSelectedFibObjectInfo()
 * @see setListenersSelectedWidgetFibObjectInfo
 * @see setSelectedFibObjectInfo()
 * @see sendSelectedFibObjectInfoChange()
 * @param pSelectedFibObjectInfo a pointer to the listener for changes
 * @return true if the listener was registered, else false
 */
bool cWidgetFibObjectInfo::registerListenerSelectedFibObjectInfo(
		lSelectedWidgetFibObjectInfo * pSelectedFibObjectInfo ){
	
	DEBUG_OUT_L2(<<"cWidgetFibObjectInfo("<<this<<")::registerListenerSelectedFibObjectInfo( pSelectedFibObjectInfo="<<pSelectedFibObjectInfo<<") called"<<endl<<flush);
	if ( pSelectedFibObjectInfo == NULL ){
		//nothing to register
		return false;
	}
	mutexListenersSelectedWidgetFibObjectInfo.lock();
	const pair< set< lSelectedWidgetFibObjectInfo * >::iterator, bool >
		paListenerInserted = setListenersSelectedWidgetFibObjectInfo.insert(
			pSelectedFibObjectInfo );
	mutexListenersSelectedWidgetFibObjectInfo.unlock();
	return paListenerInserted.second;
}


/**
 * With this function you can unregister a listeners for changes for the
 * selected Fib object info widget.
 *
 * @see registerListenerSelectedFibObjectInfo()
 * @see setListenersSelectedWidgetFibObjectInfo
 * @see setSelectedFibObjectInfo()
 * @see sendSelectedFibObjectInfoChange()
 * @param pSelectedFibObjectInfo a pointer to the listener for changes
 * @return true if the listener was registered, else false
 */
bool cWidgetFibObjectInfo::unregisterListenerSelectedFibObjectInfo(
		lSelectedWidgetFibObjectInfo * pSelectedFibObjectInfo ){
	
	DEBUG_OUT_L2(<<"cWidgetFibObjectInfo("<<this<<")::unregisterListenerSelectedFibObjectInfo( pSelectedFibObjectInfo="<<pSelectedFibObjectInfo<<") called"<<endl<<flush);
	mutexListenersSelectedWidgetFibObjectInfo.lock();
	const bool bUnregistered =
		( 0 < setListenersSelectedWidgetFibObjectInfo.erase( pSelectedFibObjectInfo ) );
	mutexListenersSelectedWidgetFibObjectInfo.unlock();
	return bUnregistered;
}


/**
 * This method send a event that the selected Fib object info widget
 * has changed to all registered listeners for changes of the selected
 * Fib object info widget.
 *
 * @see registerListenerSelectedFibObjectInfo()
 * @see unregisterListenerSelectedFibObjectInfo()
 * @see setListenersSelectedWidgetFibObjectInfo
 * @see setSelectedFibObjectInfo()
 * @param pSelectedFibObjectInfo a pointer to the selected Fib object
 * 	info object (should be this), or NULL if non should be selected
 */
void cWidgetFibObjectInfo::sendSelectedFibObjectInfoChange(
		cWidgetFibObjectInfo * pSelectedFibObjectInfo ){
	
	mutexListenersSelectedWidgetFibObjectInfo.lock();
	set< lSelectedWidgetFibObjectInfo * > setTmpListenersSelectedWidgetFibObjectInfo =
		setListenersSelectedWidgetFibObjectInfo;
	mutexListenersSelectedWidgetFibObjectInfo.unlock();
	setSelected( true );
	
	for ( set< lSelectedWidgetFibObjectInfo * >::iterator
			itrChangeListener = setTmpListenersSelectedWidgetFibObjectInfo.begin();
			itrChangeListener != setTmpListenersSelectedWidgetFibObjectInfo.end();
			itrChangeListener++ ){
		
		(*itrChangeListener)->selectWidgetFibObjectInfo( pSelectedFibObjectInfo );
	}
}


/**
 * @return a hint for a good size of this widget
 */
QSize cWidgetFibObjectInfo::sizeHint() const{
	
	return QSize( 128, 96 );
}


/**
 * This method handles mouse events.
 */
void cWidgetFibObjectInfo::mousePressEvent( QMouseEvent * ){
	
	
	//this widget was clicked on
	if ( bSelected ){
		//selected before -> it is not selected now
		sendSelectedFibObjectInfoChange( NULL );
	}else{ //not selected before -> it is selected now
		sendSelectedFibObjectInfoChange( this );
	}
}


/**
 * This method will (re-)create this Fib object info widget
 * correspondending to the actual Fib object info object.
 * @see pFibObjectInfo
 */
void cWidgetFibObjectInfo::createFibObjectInfoWidget(){
	
	//delete old members
	if ( pScenePreviewPicture ){
		pScenePreviewPicture->deleteLater();
		pScenePreviewPicture = NULL;
	}
	if ( pViewPreviewPicture ){
		pViewPreviewPicture->deleteLater();
		pViewPreviewPicture = NULL;
	}
	
	if ( pFibObjectInfo ){
		//a Fib object info exists
		
		/*  This widget should look like:
		 * +-------------------------------------------------+
		 * | - name @see szNameOfFibObject                   |
		 * | - preview or description @see szDescription     |
		 * |      - switch by parameter or click on by mouse |
		 * | - number of input variables ->pic-> number of - |
		 * |      subobjects ;    number of Fib elements;    |
		 * |      changebel (=green or red for not changebel)|
		 * +-------------------------------------------------+
		 */
		QString strNameOfFibObject =
			QString( pFibObjectInfo->getFibObjectName().c_str() );
		if ( strNameOfFibObject.isEmpty() ){
			//try to use the file name as Fib object name
			cFibObjectSource * pFibObjectSource =
				pFibObjectInfo->getFibObjectSource();
			if ( pFibObjectSource ){
				const std::string szSourceTypeName = pFibObjectSource->getName();
				if ( szSourceTypeName == "cFibObjectSourcePath" ){
					
					strNameOfFibObject = QString(
						(static_cast<cFibObjectSourcePath*>(
							pFibObjectSource))->getPath().c_str());
					
				}else if ( szSourceTypeName == "cFibObjectSourceFibDb" ){
					
					strNameOfFibObject = QString( "Db " ) + QString(
						QString::number( (static_cast<cFibObjectSourceFibDb*>(
							pFibObjectSource))->getFibDbIdentifier() ) );
				}//else no name
			}
		}
		if ( pLabelNameOfFibObject == NULL ){
			//create new text label
			pLabelNameOfFibObject = new QLabel( strNameOfFibObject, this );
			pLabelNameOfFibObject->setWordWrap( true );
		}else{//adapt text of existing text label
			pLabelNameOfFibObject->setText( strNameOfFibObject );
		}
		
		if ( pTextDescription == NULL ){
			//create new description label
			pTextDescription = new cTextField(
				QString( pFibObjectInfo->getDescription().c_str() ), this );
			//pTextDescription->setWordWrapMode( QTextOption::WordWrap );
			pTextDescription->setReadOnly( true );
		}else{//adapt text of existing description label
			pTextDescription->setText(
				QString( pFibObjectInfo->getDescription().c_str() ) );
		}
		
		cFibObjectInfo * pPreview = pFibObjectInfo->getPreviewFibObjectInfo();
		
		if ( pPreview ){
			//preview exists
			cFibElement * pPreviewFibObject = pPreview->loadFibObjectFromSource();
			
			if ( pPreviewFibObject ){
				centerViewMode = ED_PREVIEW;
				pScenePreviewPicture = new cFibGraphicsScene(
					pPreviewFibObject->clone(), this );
				pViewPreviewPicture = new QGraphicsView( pScenePreviewPicture, this );
			}
		}else{//no preview exists
			centerViewMode = ED_DESCRIPTION;
		}
		
		if ( pLabelNumberOfInputVariables == NULL ){
			//create new number of input variables label
			pLabelNumberOfInputVariables = new QLabel( QString::number(
				pFibObjectInfo->getNumberOfInputVariables() ), this );
		}else{//adapt text of existing number of input variables label
			pLabelNumberOfInputVariables->setText( QString::number(
				pFibObjectInfo->getNumberOfInputVariables() ) );
		}
		if ( pLabelNumberOfFibElements == NULL ){
			//create new number of Fib elements label
			pLabelNumberOfFibElements = new QLabel( QString::number(
				pFibObjectInfo->getNumberOfFibElements() ), this );
		}else{//adapt text of existing number of Fib elements label
			pLabelNumberOfFibElements->setText( QString::number(
				pFibObjectInfo->getNumberOfFibElements() ) );
		}
		if ( pLabelNumberOfExtSubobjects == NULL ){
			//create new number of external subelements label
			pLabelNumberOfExtSubobjects = new QLabel( QString::number(
				pFibObjectInfo->getNumberOfExtSubobjects() ), this );
		}else{//adapt text of existing number of external subelements label
			pLabelNumberOfExtSubobjects->setText( QString::number(
				pFibObjectInfo->getNumberOfExtSubobjects() ) );
		}
		
		//TODO is changebel
		
		if ( pLayoutCenter == NULL ){
			pLayoutCenter = new QHBoxLayout();
			pLayoutCenter->setMargin( 1 );
			if ( ( centerViewMode == ED_PREVIEW ) && ( pViewPreviewPicture != NULL ) ){
				//show preview
				pLayoutCenter->addWidget( pViewPreviewPicture );
			}else{//show description in center view
				//show description
				centerViewMode = ED_DESCRIPTION;
				pLayoutCenter->addWidget( pTextDescription );
			}
		}
		if ( pLayoutBottomLine == NULL ){
			//create bottom line
			pLayoutBottomLine = new QHBoxLayout();
			pLayoutBottomLine->setMargin( 1 );
			//TODO create and add mini pictures
			pLayoutBottomLine->addWidget( pLabelNumberOfInputVariables );
			pLayoutBottomLine->addWidget( pLabelNumberOfExtSubobjects );
			pLayoutBottomLine->addWidget( pLabelNumberOfFibElements );
		}
		
		if ( pLayoutMain == NULL ){
			pLayoutMain = new QVBoxLayout();
			pLayoutMain->setMargin( 1 );
			pLayoutMain->addWidget( pLabelNameOfFibObject );
			
			pLayoutMain->addLayout( pLayoutCenter );
			pLayoutMain->addLayout( pLayoutBottomLine );
			
			setLayout( pLayoutMain );
		}
		
		setToolTip( QString( pFibObjectInfo->getDescription().c_str() ) );
		setAttribute( Qt::WA_AlwaysShowToolTips );
		
#ifdef DEBUG
		
		cout<<"cWidgetFibObjectInfo("<<this<<")::createFibObjectInfoWidget() "<<
			"name: "<<pFibObjectInfo->getFibObjectName()<<endl<<
			"size pLayoutMain: ("<<
				(pLayoutMain->sizeHint().width())<<", "<<
				(pLayoutMain->sizeHint().height())<<
			")  pLabelNameOfFibObject: ("<<
				(pLabelNameOfFibObject->sizeHint().width())<<", "<<
				(pLabelNameOfFibObject->sizeHint().height())<<")"<<endl<<
			" pLayoutCenter: ("<<
				(pLayoutCenter->sizeHint().width())<<", "<<
				(pLayoutCenter->sizeHint().height())<<")"<<
			"  pTextDescription: ("<<
				(pTextDescription->sizeHint().width())<<", "<<
				(pTextDescription->sizeHint().height())<<
			")"<<endl<<
			" pLayoutBottomLine: ("<<
				(pLayoutBottomLine->sizeHint().width())<<", "<<
				(pLayoutBottomLine->sizeHint().height())<<
			")"<<endl<<
			"    pLabelNumberOfInputVariables: ("<<
				(pLabelNumberOfInputVariables->sizeHint().width())<<", "<<
				(pLabelNumberOfInputVariables->sizeHint().height())<<
			") pLabelNumberOfExtSubobjects: ("<<
				(pLabelNumberOfExtSubobjects->sizeHint().width())<<", "<<
				(pLabelNumberOfExtSubobjects->sizeHint().height())<<
			") pLabelNumberOfFibElements: ("<<
				(pLabelNumberOfFibElements->sizeHint().width())<<", "<<
				(pLabelNumberOfFibElements->sizeHint().height())<<
			")"<<endl;
		
#endif //DEBUG
	}else{//a Fib object info dos not exists
		if ( pLabelNameOfFibObject ){
			//adapt text of existing text label
			pLabelNameOfFibObject->setText( QString() );
		}
		if ( pTextDescription ){
			//adapt text of existing description label
			pTextDescription->setText( QString() );
		}
		if ( pLabelNumberOfInputVariables ){
			//adapt text of existing number of input variables label
			pLabelNumberOfInputVariables->setText( QString() );
		}
		if ( pLabelNumberOfFibElements ){
			//adapt text of existing number of Fib elements label
			pLabelNumberOfFibElements->setText( QString() );
		}
		if ( pLabelNumberOfExtSubobjects ){
			//adapt text of existing number of external subelements label
			pLabelNumberOfExtSubobjects->setText( QString() );
		}
		
		//set tool tip to NULL
		setToolTip( "" );
		//don't show tool tips
		setAttribute( Qt::WA_AlwaysShowToolTips, false );
	}
	setWhatsThis( tr( "This is a Fib object you can use in your image.\n Simply drag and drop it into the image.") );
	
	update();
}
















