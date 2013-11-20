
//TODO check

/**
 * @file cWidgetFibObjectInfo
 * file name: cWidgetFibObjectInfo.cpp
 * @author Betti Oesterholz
 * @date 09.10.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for the information about a Fib object.
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
 * This file implements a class for the information about a Fib object.
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


//TODO switches for test proposes
#define DEBUG


#include "cWidgetFibObjectInfo.h"

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "cFibElement.h"

#include "cFibObjectInfo.h"
#include "lSelectedWidgetFibObjectInfo.h"
#include "cFibGraphicsScene.h"


using namespace fib::nCreator;
using namespace std;




/**
 * standard constructor for a Fib object info widget
 *
 * @param pInFibObjectInfo a pointer to the Fib object info object for this widget
 * 	@see pFibObjectInfo
 * @param pParent a pointer the parent of this new Fib object info widget
 */
cWidgetFibObjectInfo::cWidgetFibObjectInfo( cFibObjectInfo * pInFibObjectInfo,
		QWidget * pParent ):QFrame( pParent ),
		pFibObjectInfo( pInFibObjectInfo ),
		pLabelNameOfFibObject( NULL ), centerViewMode( ED_PREVIEW ),
		pLabelDescription( NULL ),
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
 * @param bSelected true if this widget is selected, else false
 */
void cWidgetFibObjectInfo::setSelected( bool bSelected ){
	
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
 * It will be called every time a Fib Fib object info object
 * (cFibObjectInfo), at which this object is registered, was changed.
 *
 * @param pFibObjectInfoChanged a pointer to the event, with the information
 * 	about the changed Fib node
 */
void cWidgetFibObjectInfo::fibObjectInfoChanged(
	const eFibObjectInfoChangedEvent * pFibObjectInfoChanged ){
	
	if ( ( pFibObjectInfoChanged == NULL ) ||
			( pFibObjectInfoChanged->getFibObjectInfo() == NULL ) ){
		//no event of Fib object info -> nothing to do
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
 * has changed to this to all registered listeners for changes of the
 * selected Fib object info widget.
 *
 * @see registerListenerSelectedFibObjectInfo()
 * @see unregisterListenerSelectedFibObjectInfo()
 * @see setListenersSelectedWidgetFibObjectInfo
 * @see setSelectedFibObjectInfo()
 */
void cWidgetFibObjectInfo::sendSelectedFibObjectInfoChange(){
	
	mutexListenersSelectedWidgetFibObjectInfo.lock();
	set< lSelectedWidgetFibObjectInfo * > setTmpListenersSelectedWidgetFibObjectInfo =
		setListenersSelectedWidgetFibObjectInfo;
	mutexListenersSelectedWidgetFibObjectInfo.unlock();
	setSelected( true );
	
	for ( set< lSelectedWidgetFibObjectInfo * >::iterator
			itrChangeListener = setTmpListenersSelectedWidgetFibObjectInfo.begin();
			itrChangeListener != setTmpListenersSelectedWidgetFibObjectInfo.end();
			itrChangeListener++ ){
		
		(*itrChangeListener)->selectWidgetFibObjectInfo( this );
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
	
	//this widget was clicked on -> it is selected
	sendSelectedFibObjectInfoChange();
}


/**
 * This method will (re-)create this Fib object info widget
 * correspondending to the actual Fib object info object.
 * @see pFibObjectInfo
 */
void cWidgetFibObjectInfo::createFibObjectInfoWidget(){
	
	//delete old members
	if ( pScenePreviewPicture ){
		delete pScenePreviewPicture;
		pScenePreviewPicture = NULL;
	}
	if ( pViewPreviewPicture ){
		delete pViewPreviewPicture;
		pViewPreviewPicture = NULL;
	}
	
	if ( pFibObjectInfo ){
		//a Fib object info exists
		
		/*  Tis widget should look like:
		 * +-------------------------------------------------+
		 * | - name @see szNameOfFibObject                   |
		 * | - preview or description @see szDescription     |
		 * |      - switch by parameter or click on by mouse |
		 * | - number of input variables ->pic-> number of - |
		 * |      subobjects ;    number of Fib elements;    |
		 * |      changebel (=green or red for not changebel)|
		 * +-------------------------------------------------+
		 */
		if ( pLabelNameOfFibObject == NULL ){
			//create new text label
			pLabelNameOfFibObject = new QLabel(
				QString( pFibObjectInfo->getFibObjectName().c_str() ), this );
			pLabelNameOfFibObject->setWordWrap( true );
		}else{//adapt text of existing text label
			pLabelNameOfFibObject->setText(
				QString( pFibObjectInfo->getFibObjectName().c_str() ) );
		}
		
		if ( pLabelDescription == NULL ){
			//create new description label
			pLabelDescription = new QLabel(
				QString( pFibObjectInfo->getDescription().c_str() ), this );
			pLabelDescription->setWordWrap( true );
		}else{//adapt text of existing description label
			pLabelDescription->setText(
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
				//show preview
				pLayoutCenter->addWidget( pLabelDescription );
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
			
			/*TODO switch:*/
			pLayoutMain->addLayout( pLayoutCenter );
			pLayoutMain->addLayout( pLayoutBottomLine );
			
			/*TODO weg:
			pLayoutMain->addWidget( pLabelDescription );
			pLayoutMain->addWidget( pLabelNumberOfInputVariables );
			pLayoutMain->addWidget( pLabelNumberOfExtSubobjects );
			pLayoutMain->addWidget( pLabelNumberOfFibElements );
			*/
			
			
			
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
			"  pLabelDescription: ("<<
				(pLabelDescription->sizeHint().width())<<", "<<
				(pLabelDescription->sizeHint().height())<<
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
		if ( pLabelDescription ){
			//adapt text of existing description label
			pLabelDescription->setText( QString() );
		}
		if ( pLabelNumberOfInputVariables ){
			//adapt text of existing number of input variables label
			pLabelNumberOfInputVariables->setText( QString::number( 0 ) );
		}
		if ( pLabelNumberOfFibElements ){
			//adapt text of existing number of Fib elements label
			pLabelNumberOfFibElements->setText( QString::number( 0 ) );
		}
		if ( pLabelNumberOfExtSubobjects ){
			//adapt text of existing number of external subelements label
			pLabelNumberOfExtSubobjects->setText( QString::number( 0 ) );
		}
		
		//set tool tip to NULL
		setToolTip( "" );
		setAttribute( Qt::WA_AlwaysShowToolTips );
	}
	setWhatsThis( tr( "This is a Fib object you can use in your image.\n Simply drag and drop it into the image.") );
	
	update();
}
















