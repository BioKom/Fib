
//TODO check

/**
 * @file cWidgetFibVector
 * file name: cWidgetFibVector.cpp
 * @author Betti Oesterholz
 * @date 02.12.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a vector widget.
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
 * This file implements a class for a vector widget.
 * If you have a Fib element, vectors of it can be displayed with this
 * class for the Fib creator modul.
 * A Fib vector contains a number of scalars.
 *
 * @see cWidgetFibScalar
 * @see cFibVectorCreator
 * @see fib::cFibVector
 * @see cFibScalar
 *
 * It should look like:
 * +-------------------------------------------------+
 * | - name @see szNameOfFibObject                   |
 * | - list of elements                              |
 * +-------------------------------------------------+
 *
 */
/*
History:
02.12.2013  Oesterholz  created
*/


//switches for test proposes
#define DEBUG


#include <QScrollBar>

#include "cWidgetFibVector.h"

#include "cFlowLayout.h"
#include "cFibVectorCreator.h"
#include "eFibVectorChangedEvent.h"
#include "cWidgetFibVectorElement.h"


using namespace std;
using namespace fib::nCreator;

/**
 * The standard constructor for a Fib vector widget.
 *
 * @param pInFibVector a pointer to the Fib vector object for this widget
 * 	@see pFibVector
 * @param pParent a pointer the parent of this new Fib vector widget
 */
cWidgetFibVector::cWidgetFibVector( cFibVectorCreator * pInFibVector,
		QWidget * pParent ):QFrame( pParent ),
		pFibVector( pInFibVector ),
		pLabelNameOfFibVector( NULL ), pScrollArea( NULL ),
		pLayoutBottomLine( NULL ), pLayoutMain( NULL ), pLayoutFrameMain( NULL ) {
	
	DEBUG_OUT_L2(<<"cWidgetFibVector("<<this<<")::cWidgetFibVector( pInFibVector="<<pInFibVector<<", pParent="<<pParent<<" ) called"<<endl<<flush);
	setLineWidth( 1 );
	setFrameStyle( QFrame::Panel | QFrame::Raised );
	
	if ( pFibVector ) {
		pFibVector->registerFibVectorChangeListener( this );
	}
	
	createFibVectorWidget();
}


/**
 * destructor
 */
cWidgetFibVector::~cWidgetFibVector() {
	DEBUG_OUT_L2(<<"cWidgetFibVector("<<this<<")::~cWidgetFibVector() called"<<endl<<flush);
	
	if ( pFibVector ) {
		pFibVector->unregisterFibVectorChangeListener( this );
	}
}



/**
 * This method returns a pointer to the Fib vector object of this widget.
 * Note: Don't delete the returned Fib vector object.
 *
 * @see pFibVector
 * @return a const pointer to the Fib vector object of this widget
 */
const cFibVectorCreator * cWidgetFibVector::getFibVector() const {
	
	DEBUG_OUT_L2(<<"cWidgetFibVector("<<this<<")::getFibVector() ="<<pFibVector<<" called"<<endl<<flush);
	return pFibVector;
}


/**
 * This method returns a pointer to the Fib vector object of this widget.
 * Note: Don't delete the returned Fib vector object.
 *
 * @see pFibVector
 * @return a pointer to the Fib vector object of this widget
 */
cFibVectorCreator * cWidgetFibVector::getFibVector() {
	
	DEBUG_OUT_L2(<<"cWidgetFibVector("<<this<<")::getFibVector() ="<<pFibVector<<" called"<<endl<<flush);
	return pFibVector;
}


/**
 * @return the name of this class "cWidgetFibVector"
 */
string cWidgetFibVector::getName() const {
	
	return ((std::string)("cWidgetFibVector"));
}


/**
 * Event method
 * It will be called every time a Fib vector object (cFibVectorCreator), at
 * which this object is registered, was changed.
 *
 * @param pFibVectorChanged a pointer to the event, with the information
 * 	about the changed Fib node
 */
void cWidgetFibVector::fibVectorChangedEvent(
		const eFibVectorChangedEvent * pFibVectorChanged ) {
	
	DEBUG_OUT_L2(<<"cWidgetFibVector("<<this<<")::fibVectorChangedEvent( pFibVectorChanged="<<pFibVectorChanged<<" ) called"<<endl<<flush);
	if ( ( pFibVectorChanged == NULL ) ||
			( pFibVectorChanged->getFibVector() == NULL ) ) {
		//no event of Fib vector -> nothing to do
		return;
	}
	if ( pFibVectorChanged->getFibVector() != pFibVector ) {
		//wrong Fib vector -> event not for this widget
		return;
	}//Fib vector for this widget
	//the Fib vector for the event is the Fib vector for this widget
	if ( pFibVectorChanged->isDeleted() ) {
		//the Fib vector object was deleted
		pFibVector = NULL;
		createFibVectorWidget();
		return;
	}//the Fib vector object was changed -> redraw this widget
	
	
	switch ( pFibVectorChanged->getElementChangeType() ) {
		//update vector elements
		case eFibVectorChangedEvent::ADD:{
			const unsigned int uiChangedElement =
				pFibVectorChanged->getNumberOfElementChanged();
			if ( uiChangedElement == 0 ) {
				//0 = all elements
				createFibVectorWidget();
				break;
			}
			mutexFibVectorWidget.lock();
			iGetWidget * pActualElement =
				pFibVector->getElement( uiChangedElement );
			if ( pActualElement ) {
				//add the widget for the element
				cWidgetFibVectorElement * pActualElementWidget =
					new cWidgetFibVectorElement( pFibVector, uiChangedElement );
				liVectorElements.insert(
					uiChangedElement - 1, pActualElementWidget );
				pLayoutBottomLine->addWidget(
					pActualElementWidget, uiChangedElement - 1 );
			}//else no element -> do nothing
			mutexFibVectorWidget.unlock();
		}break;
		case eFibVectorChangedEvent::REMOVE:{
			const unsigned int uiChangedElement =
				pFibVectorChanged->getNumberOfElementChanged();
			if ( uiChangedElement == 0 ) {
				//0 = all elements
				createFibVectorWidget();
				break;
			}
			mutexFibVectorWidget.lock();
			QWidget * pActualElementWidget =
				liVectorElements.value( uiChangedElement - 1, NULL );
			if ( pActualElementWidget ) {
				pActualElementWidget->deleteLater();
			}
			mutexFibVectorWidget.unlock();
		}break;
#ifdef TODO_WEG
		//TODO? not needed cWidgetFibVectorElement changes itself?
		case eFibVectorChangedEvent::REPLACE:{
			const unsigned int uiChangedElement =
				pFibVectorChanged->getNumberOfElementChanged();
			if ( uiChangedElement == 0 ) {
				//0 = all elements
				createFibVectorWidget();
				break;
			}
			mutexFibVectorWidget.lock();
			//remove old element widget
			QWidget * pActualElementWidget =
				liVectorElements.value( uiChangedElement - 1, NULL );
			if ( pActualElementWidget ) {
				pActualElementWidget->deleteLater();
			}
			//add new element widget
			iGetWidget * pActualElement =
				pFibVector->getElement( uiChangedElement );
			if ( pActualElement ) {
				//add the widget for the element
				QWidget * pActualElementWidget = pActualElement->getWidget();
				liVectorElements.insert(
					uiChangedElement - 1, pActualElementWidget );
				pLayoutBottomLine->addWidget(
					pActualElementWidget, uiChangedElement - 1 );
			}//else no element -> do nothing
			mutexFibVectorWidget.unlock();
		}break;
#endif //TODO_WEG
		
		case eFibVectorChangedEvent::NAME:{//update name of vector
			const QString strVectorName = pFibVector->getVectorName();
			mutexFibVectorWidget.lock();
			if ( ! strVectorName.isEmpty() ) {
				if ( pLabelNameOfFibVector == NULL ) {
					//create new label for the vector name
					pLabelNameOfFibVector = new QLabel(
						strVectorName, this );
					//recreate main layout
					if ( pLayoutMain != NULL ) {
						//delete old main layout
						pLayoutMain->deleteLater();
					}
					pLayoutMain = new QVBoxLayout();
					
					pLayoutMain->addWidget( pLabelNameOfFibVector );
					pLayoutMain->addLayout( pLayoutBottomLine );
					
					setLayout( pLayoutMain );
					
				}else{//adapt label for the vector name
					pLabelNameOfFibVector->setText( strVectorName );
				}
			}else{//no (== empty) vector name
				if ( pLabelNameOfFibVector != NULL ) {
					//remove label for the vector name
					pLabelNameOfFibVector->deleteLater();
					pLabelNameOfFibVector = NULL;
				}
			}
			mutexFibVectorWidget.unlock();
		}break;
		default:;
		//else do nothing
	}
}


/**
 * This method will (re-)create this Fib vector widget
 * correspondending to the actual Fib vector object.
 * @see pFibVector
 */
void cWidgetFibVector::createFibVectorWidget() {
	
	DEBUG_OUT_L2(<<"cWidgetFibVector("<<this<<")::createFibVectorWidget() called"<<endl<<flush);
	mutexFibVectorWidget.lock();
	//delete all element widgets
	for ( QList< cWidgetFibVectorElement * >::iterator
			itrElement = liVectorElements.begin();
			itrElement != liVectorElements.end(); itrElement++ ) {
		(*itrElement)->deleteLater();
	}
	liVectorElements.clear();
	
	if ( pFibVector == NULL ) {
		//no Fib vector -> nothing to display
		pLayoutBottomLine->deleteLater();
		pLayoutBottomLine = NULL;
		pLayoutMain->deleteLater();
		pLayoutMain = NULL;
		mutexFibVectorWidget.unlock();
		return;
	}
	//create widget for the vector name
	const QString strVectorName = pFibVector->getVectorName();
	if ( ! strVectorName.isEmpty() ) {
		if ( pLabelNameOfFibVector == NULL ) {
			//create new label for the vector name
			pLabelNameOfFibVector = new QLabel(
				strVectorName, this );
		}else{//adapt label for the vector name
			pLabelNameOfFibVector->setText( strVectorName );
		}
	}else{//no (==empty) vector name
		if ( pLabelNameOfFibVector != NULL ) {
			//remove label for the vector name
			pLabelNameOfFibVector->deleteLater();
			pLabelNameOfFibVector = NULL;
		}
	}
	//create the widgets for the vector elements
	if ( pLayoutBottomLine == NULL ) {
		pLayoutBottomLine = new cFlowLayout();
	}
	const unsigned int uiNumberOfElements = pFibVector->getNumberOfElements();
	
	for ( unsigned int uiActualElement = 1;
			uiActualElement <= uiNumberOfElements; uiActualElement++ ) {
		
		cWidgetFibVectorElement * pActualElementWidget =
			new cWidgetFibVectorElement( pFibVector, uiActualElement );
			
		liVectorElements.push_back( pActualElementWidget );
		pLayoutBottomLine->addWidget( pActualElementWidget );
	}
	//create main layout
	if ( pLayoutMain != NULL ) {
		//delete old main layout
		pLayoutMain->deleteLater();
	}
	pLayoutMain = new QVBoxLayout();
	
	if ( pLabelNameOfFibVector ) {
		pLayoutMain->addWidget( pLabelNameOfFibVector );
	}
	pLayoutMain->addLayout( pLayoutBottomLine );
	
	//create the frame layout
	if ( pLayoutFrameMain == NULL ) {
		pLayoutFrameMain = new QVBoxLayout();
		setLayout( pLayoutFrameMain );
	}
	//create scroll area
	if ( pScrollArea == NULL ) {
		//create a new slider widget
		pScrollArea = new QScrollArea();
		pScrollArea->setWidgetResizable( true );
		pScrollArea->setWidget( new QWidget() );
		pLayoutFrameMain->addWidget( pScrollArea );
	}
	pScrollArea->widget()->setLayout( pLayoutMain );
	
	mutexFibVectorWidget.unlock();
}


/**
 * @see QWidget::minimumSize()
 * @return the minimum size of this widgte;
 * 	This is the smallest size that the widgte can have.
 */
QSize cWidgetFibVector::minimumSize() const{
	
	DEBUG_OUT_L2(<<"cWidgetFibVector("<<this<<")::minimumSize() called"<<endl<<flush);
	mutexFibVectorWidget.lock();
	if ( liVectorElements.empty() || ( pLayoutBottomLine == NULL) ) {
		/*no vector elements or no vector elements layout
		 *-> minimum size of element is empty area*/
		mutexFibVectorWidget.unlock();
		return QSize( 0, 0 );
	}
	
	QSize minimumSize = pLayoutBottomLine->minimumSize();
	if ( pLabelNameOfFibVector ){
		//add minimum size for vector name label
		const QSize minSizeLabelName = pLabelNameOfFibVector->minimumSize();
		minimumSize.setWidth( max( minimumSize.width(),
			minSizeLabelName.width() ) );
		minimumSize.setHeight( minimumSize.height() +
			minSizeLabelName.height() );
	}
	mutexFibVectorWidget.unlock();
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::minimumSize() done minimum size =("<<minimumSize.width()<<", "<<minimumSize.height()<<" )"<<endl<<flush);
	return minimumSize;
}


/**
 * @see QWidget::minimumSizeHint()
 * @return the minimum size hint for this widgte;
 * 	This is a small size that the widgte should have.
 */
QSize cWidgetFibVector::minimumSizeHint() const{
	
	DEBUG_OUT_L2(<<"cWidgetFibVector("<<this<<")::minimumSizeHint() called"<<endl<<flush);
	return minimumSize();
}


/**
 * @return a hint for a good size of this widget
 */
QSize cWidgetFibVector::sizeHint() const {
	
	return sizeHint( -1 );
}


/**
 * This method returns a size hint for this element, if the maximum width
 * is iMaxWidth (if -1 the maximum width is infinite).
 *
 * @param iMaxWidth the maximum width this widget should have,
 * 	if -1 the maximum width is infinite
 * @return a hint for a good size of this widget, if the maximum width
 * 	is iMaxWidth.
 */
QSize cWidgetFibVector::sizeHint( const int iMaxWidth ) const {
	
	DEBUG_OUT_L2(<<"cWidgetFibVector("<<this<<")::sizeHint( iMaxWidth="<<iMaxWidth<<" ) called"<<endl<<flush);
	
	QSize sizeWidget( 0, 0 );
	
	if ( pLayoutBottomLine ) {
		if ( iMaxWidth == -1 ){
			//evalue size for all widgets in pLayoutBottomLine
			const int iWidthForElements = pLayoutBottomLine->
				getMaxWidthForMinNumberOfElements( pLayoutBottomLine->count() );
			
			sizeWidget = pLayoutBottomLine->getSizeForMaxWidth( iWidthForElements );
			
			DEBUG_OUT_L2(<<"cWidgetFibVector("<<this<<")::sizeHint( iMaxWidth="<<iMaxWidth<<" ) size for "<<pLayoutBottomLine->count()<<" elements =("<<sizeWidget.width()<<", "<<sizeWidget.height()<<"), (max width for elements "<<iWidthForElements<<")"<<endl<<flush);
		}else{//evalue size for maximum width iMaxWidth
			sizeWidget = pLayoutBottomLine->getSizeForMaxWidth( iMaxWidth );
			
			DEBUG_OUT_L2(<<"cWidgetFibVector("<<this<<")::sizeHint( iMaxWidth="<<iMaxWidth<<" ) size for "<<iMaxWidth<<" max width =("<<sizeWidget.width()<<", "<<sizeWidget.height()<<")"<<endl<<flush);
		}
	}
	if ( pLabelNameOfFibVector ) {
		const QSize sizeLabelNameOfFibVector =
			pLabelNameOfFibVector->sizeHint();
		
		sizeWidget.setHeight(
			sizeWidget.height() + sizeLabelNameOfFibVector.height() );
		sizeWidget.setWidth(
			max( sizeWidget.width(), sizeLabelNameOfFibVector.width() ) );
	}
	
	if ( pScrollArea ) {
		const QScrollBar * pScrollBarVertical =
			pScrollArea->verticalScrollBar();
		if ( pScrollBarVertical ) {
			sizeWidget.setWidth( sizeWidget.width() +
				pScrollBarVertical->sizeHint().width() );
		}
	}
	
	DEBUG_OUT_L2(<<"cWidgetFibVector("<<this<<")::sizeHint( iMaxWidth="<<iMaxWidth<<" ) done size =("<<sizeWidget.width()<<", "<<sizeWidget.height()<<")"<<endl<<flush);
	return sizeWidget;
}


/**
 * This method returns a size hint for this element, if minimum
 * iMinNumberOfElements of vector elements are shown in one line.
 *
 * @param iMinNumberOfElements the minimum number of vector elements to
 * 	shown in one line
 * @return a hint for a good size of this widget, if minimum
 * 	iMinNumberOfElements of vector elements are shown in one line
 */
QSize cWidgetFibVector::sizeHintForMinElementsInLine(
		const int iMinNumberOfElements ) const {
	
	DEBUG_OUT_L2(<<"cWidgetFibVector("<<this<<")::sizeHintForMinElementsInLine( iMinNumberOfElements="<<iMinNumberOfElements<<" ) called"<<endl<<flush);
	
	QSize sizeWidget( 0, 0 );
	
	if ( pLayoutBottomLine ) {
		const int iWidthForElements = pLayoutBottomLine->
			getMaxWidthForMinNumberOfElements( iMinNumberOfElements );
		
		sizeWidget = pLayoutBottomLine->getSizeForMaxWidth( iWidthForElements );
		
		DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::sizeHintForMinElementsInLine( iMinNumberOfElements="<<iMinNumberOfElements<<" ) size for "<<iMinNumberOfElements<<" elements =("<<sizeWidget.width()<<", "<<sizeWidget.height()<<"), (max width for elements "<<iWidthForElements<<")"<<endl<<flush);
	}
	if ( pLabelNameOfFibVector ) {
		const QSize sizeLabelNameOfFibVector =
			pLabelNameOfFibVector->sizeHint();
		
		sizeWidget.setHeight(
			sizeWidget.height() + sizeLabelNameOfFibVector.height() );
		sizeWidget.setWidth(
			max( sizeWidget.width(), sizeLabelNameOfFibVector.width() ) );
	}
	
	if ( pScrollArea ) {
		const QScrollBar * pScrollBarVertical =
			pScrollArea->verticalScrollBar();
		if ( pScrollBarVertical ) {
			sizeWidget.setWidth( sizeWidget.width() +
				pScrollBarVertical->sizeHint().width() );
		}
	}
	
	DEBUG_OUT_L2(<<"cWidgetFibVector("<<this<<")::sizeHintForMinElementsInLine( iMinNumberOfElements="<<iMinNumberOfElements<<" ) done size =("<<sizeWidget.width()<<", "<<sizeWidget.height()<<")"<<endl<<flush);
	return sizeWidget;
}




