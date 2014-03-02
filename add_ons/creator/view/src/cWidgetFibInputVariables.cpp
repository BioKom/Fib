/**
 * @file cWidgetFibInputVariables
 * file name: cWidgetFibInputVariables.cpp
 * @author Betti Oesterholz
 * @date 23.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a list of variable widgets.
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
 * This file implements a class for a list of variable widgets.
 * If you have a Fib object, the input variables of it are root object
 * input variables or variables used in the Fib object but not defined in it.
 * With this class you can display these.
 *
 * @see cFibInputVariable
 * @see cFibVariable
 */
/*
History:
23.08.2013  Oesterholz  created
*/

//switches for debugging proposes
#define DEBUG

#include "cWidgetFibInputVariables.h"

#include <QScrollBar>

#include "cWidgetFibScalar.h"
#include "cFlowLayout.h"
#include "nFibObjectTools.h"
#include "cFibInputVariable.h"


using namespace fib::nCreator;
using namespace fib;



/**
 * The standard constructor for a list of input variable widgets.
 * It constructs a list of input variables with no input variables. (So
 * you can add them later.)
 */
cWidgetFibInputVariables::cWidgetFibInputVariables():cFibInputVariables(){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::cWidgetFibInputVariables() called"<<endl<<flush);
	pInputVariableLayout = new cFlowLayout( this );
	//create scroll area
	pScrollArea = new QScrollArea();
	pScrollArea->setWidgetResizable( true );
	pScrollArea->setWidget( new QWidget() );
	pScrollArea->widget()->setLayout( pInputVariableLayout );
	//create the frame layout
	pLayoutMain = new QVBoxLayout();
	pLayoutMain->addWidget( pScrollArea );
	setLayout( pLayoutMain );
}


/**
 * A parameter constructor for a list of input variables widgets.
 *
 * @param liInInputVariables list with input variables for this object
 * 	@see inputVariables
 * @param pInFibObject the Fib object for which the input variables are or NULL
 * 	@see pFibObject
 */
cWidgetFibInputVariables::cWidgetFibInputVariables(
		QList< cFibInputVariable * > & liInInputVariables,
		cFibElement * pInFibObject ):
		cFibInputVariables( liInInputVariables, pInFibObject ){
			
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::cWidgetFibInputVariables( liInInputVariables, pInFibObject="<<pInFibObject<<") called"<<endl<<flush);
	//create input variable widgets
	mutexFibInputVariables.lock();
	pInputVariableLayout = new cFlowLayout( this );
	for ( QList< cFibInputVariable * >::iterator
			itrActualInVar = inputVariables.begin();
			itrActualInVar != inputVariables.end(); itrActualInVar++ ){
		
		if ( mapInputVariables.constFind( *itrActualInVar ) ==
				mapInputVariables.constEnd() ){
			//the variable was not registered before
			mapInputVariables.insert( *itrActualInVar,
				(*itrActualInVar)->getWidget( this ) );
		}
		pInputVariableLayout->addWidget( mapInputVariables[ *itrActualInVar ] );
	}
	//create scroll area
	pScrollArea = new QScrollArea();
	pScrollArea->setWidgetResizable( true );
	pScrollArea->setWidget( new QWidget() );
	pScrollArea->widget()->setLayout( pInputVariableLayout );
	//create the frame layout
	pLayoutMain = new QVBoxLayout();
	pLayoutMain->addWidget( pScrollArea );
	setLayout( pLayoutMain );
	
	mutexFibInputVariables.unlock();
}


/**
 * A parameter constructor for a list of input variable widgets.
 *
 * @param pInFibObject the Fib object for which the input variables are or NULL
 * 	@see pFibObject
 * @param bFindInputVariables if true it will evalue the input variables
 * 	for the given Fib object.
 * 	It will evalue all variables used in the Fib object, but not
 * 	defined in it. Also input variables are input variables of the
 * 	root element pFibObject, if pFibObject is a root element.
 * 	@see nFibObjectTools::evalueInputVariables()
 * 	Also the list will be updated for input variables changes.
 * 	If bFindInputVariables is false, this constructor constructs a
 * 	list of input variables with no input variables. (So you can add
 * 	them later.)
 * @param bTillRoot if true searches for input variables in the Fib
 * 	object for pFibObject till the root Fib element (Fib element
 * 	with no superior), else the input variables for pFibObject will
 * 	be returned
 */
cWidgetFibInputVariables::cWidgetFibInputVariables( cFibElement * pInFibObject,
		const bool bFindInputVariables, const bool bTillRoot ):
		cFibInputVariables( pInFibObject, bFindInputVariables, bTillRoot ){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::cWidgetFibInputVariables( pInFibObject="<<pInFibObject<<", bFindInputVariables="<<(bFindInputVariables?"true":"false")<<") called"<<endl<<flush);
	//create input variable widgets
	mutexFibInputVariables.lock();
	pInputVariableLayout = new cFlowLayout( this );
	for ( QList< cFibInputVariable * >::iterator
			itrActualInVar = inputVariables.begin();
			itrActualInVar != inputVariables.end(); itrActualInVar++ ){
		
		if ( mapInputVariables.constFind( *itrActualInVar ) ==
				mapInputVariables.constEnd() ){
			//the variable was not registered before
			mapInputVariables.insert( *itrActualInVar,
				(*itrActualInVar)->getWidget( this ) );
		}
		pInputVariableLayout->addWidget( mapInputVariables[ *itrActualInVar ] );
	}
	//create scroll area
	pScrollArea = new QScrollArea();
	pScrollArea->setWidgetResizable( true );
	pScrollArea->setWidget( new QWidget() );
	pScrollArea->widget()->setLayout( pInputVariableLayout );
	//create the frame layout
	pLayoutMain = new QVBoxLayout();
	pLayoutMain->addWidget( pScrollArea );
	setLayout( pLayoutMain );

	mutexFibInputVariables.unlock();
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::cWidgetFibInputVariables( pInFibObject="<<pInFibObject<<", bFindInputVariables="<<(bFindInputVariables?"true":"false")<<") done "<<inputVariables.size()<<" input variables created"<<endl<<flush);
}


/**
 * The copy constructor for a list of input variable widgets.
 *
 * @param fibInputVariables the input variables to copy
 */
cWidgetFibInputVariables::cWidgetFibInputVariables(
		cWidgetFibInputVariables & fibInputVariables ):
	QWidget( fibInputVariables.parentWidget() ),
	cFibInputVariables( fibInputVariables ){
		
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::cWidgetFibInputVariables( fibInputVariables ) called"<<endl<<flush);
	//create input variable widgets
	mutexFibInputVariables.lock();
	pInputVariableLayout = new cFlowLayout( this );
	for ( QList< cFibInputVariable * >::iterator
			itrActualInVar = inputVariables.begin();
			itrActualInVar != inputVariables.end(); itrActualInVar++ ){
		
		if ( mapInputVariables.constFind( *itrActualInVar ) ==
				mapInputVariables.constEnd() ){
			//the variable was not registered before
			mapInputVariables.insert( *itrActualInVar,
				(*itrActualInVar)->getWidget( this ) );
		}
		pInputVariableLayout->addWidget( mapInputVariables[ *itrActualInVar ] );
	}
	//create scroll area
	pScrollArea = new QScrollArea();
	pScrollArea->setWidgetResizable( true );
	pScrollArea->setWidget( new QWidget() );
	pScrollArea->widget()->setLayout( pInputVariableLayout );
	//create the frame layout
	pLayoutMain = new QVBoxLayout();
	pLayoutMain->addWidget( pScrollArea );
	setLayout( pLayoutMain );

	mutexFibInputVariables.unlock();
}


/**
 * destructor
 */
cWidgetFibInputVariables::~cWidgetFibInputVariables(){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::~cWidgetFibInputVariables() called"<<endl<<flush);
	//unregister this as input variable change listener at input variables
	mutexFibInputVariables.lock();
	for ( QMap< cFibInputVariable *, QWidget * >::iterator
			itrActualInVar = mapInputVariables.begin();
			itrActualInVar != mapInputVariables.end(); itrActualInVar++ ){
		//delete input variable widget
		if ( itrActualInVar.value() ){
			delete itrActualInVar.value();
		}
	}
	mutexFibInputVariables.unlock();
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::~cWidgetFibInputVariables() done"<<endl<<flush);
}


/**
 * @return the name of this class "cWidgetFibInputVariables"
 */
std::string cWidgetFibInputVariables::getName() const{
	
	return std::string( "cWidgetFibInputVariables" );
}


/**
 * This method adds the given input variable to this input variable list.
 *
 * @see inputVariables
 * @see getNumberOfInputVariables()
 * @see removeInputVariable()
 * @see replaceInputVariable()
 * @param pInputVariable a pointer to the input variable to add
 * @param uiPosition the position where to add the input variable,
 * 	if 0 or greater the number of input variables in this input
 * 	variable list it will be added to the end of the input variable list
 * 	(counting starts with 1)
 * @return true if the input variable was added, else false
 */
bool cWidgetFibInputVariables::addInputVariable( cFibInputVariable * pInputVariable,
		const unsigned int uiPosition ){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::addInputVariable( pInputVariable="<<pInputVariable<<") called"<<endl<<flush);
	if ( cFibInputVariables::addInputVariable( pInputVariable, uiPosition ) ){
	
		mutexFibInputVariables.lock();
		if ( mapInputVariables.constFind( pInputVariable ) ==
				mapInputVariables.constEnd() ){
			//the variable was not registered before
			mapInputVariables.insert( pInputVariable,
				pInputVariable->getWidget( this ) );
		}
		pInputVariableLayout->addWidget(
			mapInputVariables[ pInputVariable ], uiPosition - 1 );
		mutexFibInputVariables.unlock();
		return true;
	}
	return false;
}


/**
 * This method removes the uiPosition'th input variable from this input
 * variable list.
 *
 * @see inputVariables
 * @see getNumberOfInputVariables()
 * @see addInputVariable()
 * @see replaceInputVariable()
 * @param uiPosition the position where to remove the input variable from
 * 	(counting starts with 1)
 * @return true if the input variable was removed, else false
 */
bool cWidgetFibInputVariables::removeInputVariable( const unsigned int uiPosition ){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::removeInputVariable( uiPosition="<<uiPosition<<") called"<<endl<<flush);
	mutexFibInputVariables.lock();
	if ( ( uiPosition < 1 ) ||
			( static_cast<unsigned int>(inputVariables.size()) < uiPosition ) ){
		//no such input variable to remove
		mutexFibInputVariables.unlock();
		return false;
	}
	cFibInputVariable * pInputVariable = inputVariables.at( uiPosition - 1 );
	mutexFibInputVariables.unlock();
	
	if ( cFibInputVariables::removeInputVariable( uiPosition ) ){
		//Fib input variable was removed
		mutexFibInputVariables.lock();
		if ( ! inputVariables.contains( pInputVariable ) ){
			//the input variable dosn't exist anymore -> remove the widget for it
			QMap< cFibInputVariable *, QWidget * >::iterator
				itrVariable = mapInputVariables.find( pInputVariable );
			
			if ( itrVariable.value() ){
				delete (itrVariable.value());
			}
			mapInputVariables.erase( itrVariable );
		}
		pInputVariableLayout->removeWidget( uiPosition - 1, false );
		mutexFibInputVariables.unlock();
		return true;
	}
	return false;
}


/**
 * This method removes the given input variable from this input
 * variable list.
 *
 * @see inputVariables
 * @see getNumberOfInputVariables()
 * @see addInputVariable()
 * @see replaceInputVariable()
 * @param pInputVariable the input variable to remove
 * @return true if the input variable was removed, else false
 */
bool cWidgetFibInputVariables::removeInputVariable(
		cFibInputVariable * pInputVariable ){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::removeInputVariable( pInputVariable="<<pInputVariable<<") called"<<endl<<flush);
	if ( cFibInputVariables::removeInputVariable( pInputVariable ) ){
		//Fib input variable was removed
		mutexFibInputVariables.lock();
		//the input variable dosn't exist anymore -> remove the widget for it
		QMap< cFibInputVariable *, QWidget * >::iterator
			itrVariable = mapInputVariables.find( pInputVariable );
		
		delete (itrVariable.value());
		mapInputVariables.erase( itrVariable );
		//update the layout
		pInputVariableLayout->clear();
		for ( QList< cFibInputVariable * >::iterator
				itrActualInVar = inputVariables.begin();
				itrActualInVar != inputVariables.end(); itrActualInVar++ ){
			
			pInputVariableLayout->addWidget( mapInputVariables[ *itrActualInVar ] );
		}
		
		mutexFibInputVariables.unlock();
		return true;
	}
	return false;
}


/**
 * This method replaces a input variable in this input variable list.
 * It will replace the uiPosition'th input variable in the input
 * variable list with the given input variable pInputVariable (if possible).
 *
 * @see inputVariables
 * @see getNumberOfInputVariables()
 * @see removeInputVariable()
 * @see addInputVariable()
 * @param pInputVariable a pointer to the input variable to add,
 * 	which will replace the old input variable on the uiPosition'th position
 * @param uiPosition the position where to replace the input variable,
 * 	(counting starts with 1)
 * @return true if the input variable was replace, else false
 */
bool cWidgetFibInputVariables::replaceInputVariable( cFibInputVariable * pInputVariable,
		const unsigned int uiPosition ){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::replaceInputVariable( pInputVariable="<<pInputVariable<<", uiPosition="<<uiPosition<<") called"<<endl<<flush);
	mutexFibInputVariables.lock();
	if ( ( uiPosition < 1 ) ||
			( static_cast<unsigned int>(inputVariables.size()) < uiPosition ) ){
		//no such input variable to remove
		mutexFibInputVariables.unlock();
		return false;
	}
	cFibInputVariable * pRemovedInputVariable = inputVariables.at(
		uiPosition - 1 );
	mutexFibInputVariables.unlock();
	if ( cFibInputVariables::replaceInputVariable( pInputVariable, uiPosition ) ){
		//Fib input variable was removed
		mutexFibInputVariables.lock();
		//update the layout
		pInputVariableLayout->removeWidget( uiPosition - 1, false );
		
		if ( ! inputVariables.contains( pRemovedInputVariable ) ){
			//the input variable dosn't exist anymore -> remove the widget for it
			QMap< cFibInputVariable *, QWidget * >::iterator
				itrVariable = mapInputVariables.find( pRemovedInputVariable );
			
			if ( itrVariable.value() ){
				delete (itrVariable.value());
			}
			mapInputVariables.erase( itrVariable );
		}
		if ( mapInputVariables.constFind( pInputVariable ) ==
				mapInputVariables.constEnd() ){
			//the variable was not registered before
			mapInputVariables.insert( pInputVariable,
				pInputVariable->getWidget( this ) );
		}
		//update the layout
		pInputVariableLayout->addWidget(
			mapInputVariables[ pInputVariable ], uiPosition - 1 );
		
		mutexFibInputVariables.unlock();
		return true;
	}
	return false;
}


/**
 * This method sets the list of input variables to the given list.
 * All old input variables of this list are removed and the given input
 * variables added.
 *
 * @see inputVariables
 * @see getNumberOfInputVariables()
 * @see replaceInputVariable()
 * @see removeInputVariable()
 * @see addInputVariable()
 * @param liInInputVariables a list of the input variables this object
 * 	should contain
 * @return true if the input variables could be set, else false
 */
bool cWidgetFibInputVariables::setInputVariables(
		QList< cFibInputVariable * > & liInInputVariables ){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::setInputVariables( liInInputVariables=#"<<liInInputVariables.size()<<") called"<<endl<<flush);
	if ( cFibInputVariables::setInputVariables( liInInputVariables ) ){
		mutexFibInputVariables.lock();
		//delete old input variable widgets
		for ( QMap< cFibInputVariable *, QWidget * >::iterator
				itrActualInVar = mapInputVariables.begin();
				itrActualInVar != mapInputVariables.end(); itrActualInVar++ ){
			//delete input variable widget
			if ( itrActualInVar.value() ){
				delete (itrActualInVar.value());
			}
		}
		mapInputVariables.clear();
		//update the layout
		pInputVariableLayout->clear();
		//create widgets for new input variable
		for ( QList< cFibInputVariable * >::iterator
				itrActualInVar = inputVariables.begin();
				itrActualInVar != inputVariables.end(); itrActualInVar++ ){
			
			if ( mapInputVariables.constFind( *itrActualInVar ) ==
					mapInputVariables.constEnd() ){
				//the variable was not registered before
				mapInputVariables.insert( *itrActualInVar,
					(*itrActualInVar)->getWidget( this ) );
			}
			//update the layout
			pInputVariableLayout->addWidget( mapInputVariables[ *itrActualInVar ] );
		}
		mutexFibInputVariables.unlock();
		return true;
	}
	return false;
}


/**
 * Event method
 * It will be called every time a input variable (cFibInputVariable),
 * at which this object is registered, was changed.
 *
 * @param pFibVariableChangedEvent a pointer to the event with the
 * 	information of the change of the Fib input variable
 */
void cWidgetFibInputVariables::changedEvent(
		const eFibVariableCreatorChangedEvent * pFibVariableChangedEvent ){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::changedEvent( pFibVariableChangedEvent="<<pFibVariableChangedEvent<<") called"<<endl<<flush);
	if ( pFibVariableChangedEvent == NULL ){
		//no event given
		return;
	}
	if ( pFibVariableChangedEvent->isDeleted() ){
		//remove deleted input variable
		DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::changedEvent( pFibVariableChangedEvent="<<pFibVariableChangedEvent<<") remove deleted input variable"<<endl<<flush);
		mutexFibInputVariables.lock();
		cFibInputVariable * pInputVariable = const_cast<cFibInputVariable*>(
			static_cast<const cFibInputVariable * >(
				pFibVariableChangedEvent->getObject()) );
		inputVariables.removeAll( pInputVariable );
		
		//the input variable don't exist anymore -> remove the widget for it
		QMap< cFibInputVariable *, QWidget * >::iterator
			itrVariable = mapInputVariables.find( pInputVariable );
		if ( itrVariable.value() ){
			delete (itrVariable.value());
		}
		mapInputVariables.erase( itrVariable );
		//update the layout
		pInputVariableLayout->clear();
		for ( QList< cFibInputVariable * >::iterator
				itrActualInVar = inputVariables.begin();
				itrActualInVar != inputVariables.end(); itrActualInVar++ ){
			
			pInputVariableLayout->addWidget( mapInputVariables[ *itrActualInVar ] );
		}
		
		mutexFibInputVariables.unlock();
	}
	cFibInputVariables::changedEvent( pFibVariableChangedEvent );
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::changedEvent( pFibVariableChangedEvent="<<pFibVariableChangedEvent<<") done"<<endl<<flush);
}


/**
 * @see QWidget::minimumSize()
 * @return the minimum size of this widgte;
 * 	This is the smallest size that the widgte can have.
 */
QSize cWidgetFibInputVariables::minimumSize() const{
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::minimumSize() called"<<endl<<flush);
	mutexFibInputVariables.lock();
	if ( inputVariables.empty() || ( pInputVariableLayout == NULL) ) {
		/*no input variable or no input variables layout
		 *-> minimum size of element is empty area*/
		mutexFibInputVariables.unlock();
		DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::minimumSize() done; minimum size of element is empty area"<<endl<<flush);
		return QSize( 0, 0 );
	}
	mutexFibInputVariables.unlock();
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::minimumSize() done minimum size =("<<pInputVariableLayout->minimumSize().width()<<", "<<pInputVariableLayout->minimumSize().height()<<" )"<<endl<<flush);
	return pInputVariableLayout->minimumSize();
}


/**
 * @see QWidget::minimumSizeHint()
 * @return the minimum size hint for this widgte;
 * 	This is a small size that the widgte should have.
 */
QSize cWidgetFibInputVariables::minimumSizeHint() const{
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::minimumSizeHint() called"<<endl<<flush);
	return minimumSize();
}


/**
 * @return a hint for a good size of this widget
 */
QSize cWidgetFibInputVariables::sizeHint() const {
	
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
QSize cWidgetFibInputVariables::sizeHint( const int iMaxWidth ) const {
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::sizeHint( iMaxWidth="<<iMaxWidth<<" ) called"<<endl<<flush);
	
	QSize sizeWidget( 0, 0 );
	
	if ( pInputVariableLayout ) {
		if ( iMaxWidth == -1 ){
			//evalue size for all widgets in pInputVariableLayout
			const int iWidthForElements = pInputVariableLayout->
				getMaxWidthForMinNumberOfElements( pInputVariableLayout->count() );
			
			sizeWidget = pInputVariableLayout->getSizeForMaxWidth( iWidthForElements );
			
			DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::sizeHint( iMaxWidth="<<iMaxWidth<<" ) size for "<<pInputVariableLayout->count()<<" elements =("<<sizeWidget.width()<<", "<<sizeWidget.height()<<"), (max width for elements "<<iWidthForElements<<")"<<endl<<flush);
		}else{//evalue size for maximum width iMaxWidth
			sizeWidget = pInputVariableLayout->getSizeForMaxWidth( iMaxWidth );
			
			DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::sizeHint( iMaxWidth="<<iMaxWidth<<" ) size for "<<iMaxWidth<<" max width =("<<sizeWidget.width()<<", "<<sizeWidget.height()<<")"<<endl<<flush);
		}
	}
	
	if ( pScrollArea ) {
		const QScrollBar * pScrollBarVertical =
			pScrollArea->verticalScrollBar();
		if ( pScrollBarVertical ) {
			sizeWidget.setWidth( sizeWidget.width() +
				pScrollBarVertical->sizeHint().width() );
		}
	}
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::sizeHint( iMaxWidth="<<iMaxWidth<<" ) done size =("<<sizeWidget.width()<<", "<<sizeWidget.height()<<")"<<endl<<flush);
	return sizeWidget;
}


/**
 * This method returns a size hint for this element, if minimum
 * iMinNumberOfVariables of input variables are shown in one line.
 *
 * @param iMinNumberOfVariables the minimum number of input variables to
 * 	shown in one line
 * @return a hint for a good size of this widget, if minimum
 * 	iMinNumberOfVariables of input variables are shown in one line
 */
QSize cWidgetFibInputVariables::sizeHintForMinElementsInLine(
		const int iMinNumberOfVariables ) const {
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::sizeHintForMinElementsInLine( iMinNumberOfVariables="<<iMinNumberOfVariables<<" ) called"<<endl<<flush);
	
	QSize sizeWidget( 0, 0 );
	
	if ( pInputVariableLayout ) {
		const int iWidthForElements = pInputVariableLayout->
			getMaxWidthForMinNumberOfElements( iMinNumberOfVariables );
		
		sizeWidget = pInputVariableLayout->getSizeForMaxWidth( iWidthForElements );
	}
	
	if ( pScrollArea ) {
		const QScrollBar * pScrollBarVertical =
			pScrollArea->verticalScrollBar();
		if ( pScrollBarVertical ) {
			sizeWidget.setWidth( sizeWidget.width() +
				pScrollBarVertical->sizeHint().width() );
		}
	}
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::sizeHintForMinElementsInLine( iMinNumberOfVariables="<<iMinNumberOfVariables<<" ) done size =("<<sizeWidget.width()<<", "<<sizeWidget.height()<<")"<<endl<<flush);
	return sizeWidget;
}














