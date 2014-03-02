
//TODO check

/**
 * @file cWidgetFibVectorElement
 * file name: cWidgetFibVectorElement.cpp
 * @author Betti Oesterholz
 * @date 31.12.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a vector element widget.
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
 * This file implements a class for a vector element widget.
 * If you have a Fib element, elements of vector of it can be displayed
 * with this class for the Fib creator modul.
 * A Fib vector contains a number of element.
 *
 * @see cWidgetFibVector
 * @see cWidgetFibScalar
 * @see cFibVectorCreator
 * @see fib::cFibVector
 * @see cFibScalar
 * @see cFibVariableCreator
 * @see cFibInputVariable
 *
 * It should look like:
 * +-------------------------------+
 * | - type (choose type combobox) |
 * | - element                     |
 * +-------------------------------+
 *
 * - if the element is a variable its widget will be look like:
 * +---------------------------------------------------------+
 * | - variable name (choose variable by name from combobox) |
 * | - if possible: [show] button (= to definition)          |
 * +---------------------------------------------------------+
 *
 * - else the elements (e. g. scalar) widget will be displayed
 * 	@see iGetWidget::getWidget()
 * 
 */
/*
History:
31.12.2013  Oesterholz  created
*/


//TODO switches for test proposes
#define DEBUG


#include "cWidgetFibVectorElement.h"

#include <list>

#include <QWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QMutex>

#include "cFibVariable.h"

#include "cFibVectorCreator.h"
#include "eFibVectorChangedEvent.h"
#include "cFibVariableHandler.h"
#include "cFibInputVariable.h"
#include "cFibNodeHandler.h"
#include "cFibNode.h"




using namespace fib::nCreator;


/**
 * The standard constructor for a Fib vector element widget.
 *
 * @param pInFibVector a pointer to the Fib vector object for this widget element
 * 	@see pFibVector
 * @param uiInNumberOfElement the number of the vector element for which
 * 	this widget is (Counting starts with 1 .)
 * 	@see uiNumberOfElement
 * @param pParent a pointer the parent of this new Fib vector element widget
 */
cWidgetFibVectorElement::cWidgetFibVectorElement( cFibVectorCreator * pInFibVector,
		const unsigned int uiInNumberOfElement,
		QWidget * pParent ) : QWidget( pParent ),
		uiNumberOfElement( uiInNumberOfElement ),
		pLastSetVariable( NULL ), dLastSetValue( 0.0 ),
		pFibVector( pInFibVector ), pDefiningFibElement( NULL ), pChooseType( NULL ),
		pChooseVariable( NULL ), pMasterNode( NULL ), pElementWidget( NULL ), pLayoutMain( NULL ) {
	
	DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::cWidgetFibVectorElement( pInFibVector="<<pInFibVector<<", uiInNumberOfElement="<<uiInNumberOfElement<<", pParent="<<pParent<<" ) called"<<endl<<flush);
	
	if ( uiNumberOfElement == 0 ) {
		//ther is no zero element in the vector
		uiNumberOfElement = 1;
	}
	if ( pFibVector ) {
		if ( pFibVector->getNumberOfElements() < uiNumberOfElement ) {
			//number of element to great
			uiNumberOfElement = pFibVector->getNumberOfElements();
		}
		pFibVector->registerFibVectorChangeListener( this );
		/*this object should be adapted if the defined variable change
		 *-> it needs to listen for changes of the defining Fib elements*/
		//try to evalue master node for the change listener
		pDefiningFibElement = pFibVector->getFibElement();
		cFibNodeHandler * pNodeHandler = cFibNodeHandler::getInstance();
		if ( ( pDefiningFibElement != NULL ) && ( pNodeHandler != NULL) ){
			cFibElement * pMasterFibRoot = pDefiningFibElement->getMasterRoot();
			
			if ( pMasterFibRoot ){
				//register this as node change listener
				pMasterNode = pNodeHandler->getNodeForFibObject(
					pMasterFibRoot, this );
			}
		}
	}
	liDefinedVariables = getDefinedVariables();
	
	//create elements of this widget
	connect( this, SIGNAL(signalCreateFibVectorElementWidget()),
		this, SLOT(createFibVectorElementWidget()) );
	emit signalCreateFibVectorElementWidget();
	
	DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::cWidgetFibVectorElement( pInFibVector="<<pInFibVector<<", uiInNumberOfElement="<<uiInNumberOfElement<<", pParent="<<pParent<<" ) done"<<endl<<flush);
}


/**
 * destructor
 */
cWidgetFibVectorElement::~cWidgetFibVectorElement() {
	
	DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::~cWidgetFibVectorElement() called"<<endl<<flush);
	mutexFibVectorElement.lock();
	if ( pFibVector ){
		pFibVector->unregisterFibVectorChangeListener( this );
	}
	mutexFibVectorElement.unlock();
	mutexFibVectorElementWidget.lock();
	if ( pMasterNode ){
		pMasterNode->unregisterNodeChangeListener( this );
	}
	mutexFibVectorElementWidget.unlock();
}


/**
 * This method returns the number of the Fib vector element this widget
 * represents. (Counting starts with 1 .)
 *
 * @see uiNumberOfElement
 * @see setFibVectorElementNumber()
 * @see pFibVector
 * @return the number of the Fib vector element this widget represents
 */
unsigned int cWidgetFibVectorElement::getFibVectorElementNumber() const{
	DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::getFibVectorElementNumber()="<<uiNumberOfElement<<" called"<<endl<<flush);
	
	mutexFibVectorElement.lock();
	const unsigned int uiNumberOfElementRet = uiNumberOfElement;
	mutexFibVectorElement.unlock();
	return uiNumberOfElementRet;
}


/**
 * This method sets the number of the Fib vector element this widget
 * represents. (Counting starts with 1 .)
 *
 * @see uiNumberOfElement
 * @see getFibVectorElementNumber()
 * @see pFibVector
 * @param uiInNumberOfElement the number of the Fib vector element this
 * 	widget represents to set
 * @return true if the number could be set, else false
 */
bool cWidgetFibVectorElement::setFibVectorElementNumber( unsigned int uiInNumberOfElement ) {
	
	DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::setFibVectorElementNumber( uiInNumberOfElement="<<uiInNumberOfElement<<" ) called"<<endl<<flush);
	
	mutexFibVectorElement.lock();
	if ( uiInNumberOfElement == 0 ) {
		//ther is no zero element in the vector
		mutexFibVectorElement.unlock();
		return false;
	}
	if ( uiNumberOfElement == uiInNumberOfElement ) {
		//vector element not changed -> element already set
		mutexFibVectorElement.unlock();
		return true;
	}
	
	if ( pFibVector ) {
		if ( pFibVector->getNumberOfElements() < uiNumberOfElement ) {
			//number of element to great
			mutexFibVectorElement.unlock();
			return false;
		}//else set number of element
		
		iGetWidget * pOldElement = pFibVector->getElement( uiNumberOfElement );
		//if variable
		if ( pOldElement != NULL ) {
			if ( ( pOldElement->getName() == "cFibVariableCreator" ) ||
						( pOldElement->getName() == "cFibInputVariable" ) ) {
				//remember variable as last set variable
				pLastSetVariable = static_cast<cFibVariableCreator *>(pOldElement);
			}else if ( pOldElement->getName() == "cFibScalar" ) {
				
				dLastSetValue = static_cast<cFibScalar*>(pOldElement)->getValue();
			}
		}
	}//else set number of element
	
	uiNumberOfElement = uiInNumberOfElement;
	mutexFibVectorElement.unlock();
	return true;
}


/**
 * This method returns a pointer to the Fib vector element object of
 * this widget.
 * Note: Don't delete the returned Fib vector object.
 *
 * @see uiNumberOfElement
 * @see setFibVectorElement()
 * @see pFibVector
 * @return a const pointer to the Fib vector element object of this widget
 */
const iGetWidget * cWidgetFibVectorElement::getFibVectorElement() const {
	
	DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::getFibVectorElement() called"<<endl<<flush);
	mutexFibVectorElement.lock();
	const iGetWidget * pElementToReturn = ( pFibVector == NULL ) ? NULL :
		pFibVector->getElement( uiNumberOfElement );
	
	mutexFibVectorElement.unlock();
	DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::getFibVectorElement() done return: "<<pElementToReturn<<""<<endl<<flush);
	
	return pElementToReturn;
}


/**
 * This method returns a pointer to the Fib vector element object of
 * this widget.
 * Note: Don't delete the returned Fib vector object.
 *
 * @see pElement
 * @see setFibVectorElement()
 * @see pFibVector
 * @return a pointer to the Fib vector element object of this widget
 */
iGetWidget * cWidgetFibVectorElement::getFibVectorElement() {
	
	DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::getFibVectorElement() const called"<<endl<<flush);
	mutexFibVectorElement.lock();
	iGetWidget * pElementToReturn = ( pFibVector == NULL ) ? NULL :
		pFibVector->getElement( uiNumberOfElement );
	
	mutexFibVectorElement.unlock();
	DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::getFibVectorElement() const done return: "<<pElementToReturn<<""<<endl<<flush);
	return pElementToReturn;
}


/**
 * This method returns a pointer to the Fib vector object of this widget.
 * Note: Don't delete the returned Fib vector object.
 *
 * @see pFibVector
 * @return a const pointer to the Fib vector object of this widget
 */
const cFibVectorCreator * cWidgetFibVectorElement::getFibVector() const {
	
	mutexFibVectorElement.lock();
	const cFibVectorCreator * pFibVectorToReturn = pFibVector;
	mutexFibVectorElement.unlock();
	return pFibVectorToReturn;
}


/**
 * This method returns a pointer to the Fib vector object of this widget.
 * Note: Don't delete the returned Fib vector object.
 *
 * @see pFibVector
 * @return a pointer to the Fib vector object of this widget
 */
cFibVectorCreator * cWidgetFibVectorElement::getFibVector() {
	
	mutexFibVectorElement.lock();
	cFibVectorCreator * pFibVectorToReturn = pFibVector;
	mutexFibVectorElement.unlock();
	return pFibVectorToReturn;
}


/**
 * @return the name of this class "cWidgetFibVectorElement"
 */
std::string cWidgetFibVectorElement::getName() const {
	
	return ((std::string)("cWidgetFibVectorElement"));
}


/**
 * Event method
 * It will be called every time a Fib vector object (cFibVectorCreator), at
 * which this object is registered, was changed.
 *
 * @param pFibVectorChanged a pointer to the event, with the information
 * 	about the changed Fib node
 */
void cWidgetFibVectorElement::fibVectorChangedEvent(
		const eFibVectorChangedEvent * pFibVectorChanged ) {
	
	DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::fibVectorChangedEvent( pFibVectorChanged="<<pFibVectorChanged<<" ) called"<<endl<<flush);
	if ( ( pFibVectorChanged == NULL ) ||
			( pFibVectorChanged->getFibVector() == NULL ) ) {
		//no event of Fib vector -> nothing to do
		return;
	}
	mutexFibVectorElement.lock();
	if ( pFibVectorChanged->getFibVector() != pFibVector ) {
		//wrong Fib vector -> event not for this widget
		mutexFibVectorElement.unlock();
		return;
	}//Fib vector for this widget
	//the Fib vector for the event is the Fib vector for this widget
	if ( pFibVectorChanged->isDeleted() ) {
		//the Fib vector object was deleted
		DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::fibVectorChangedEvent( pFibVectorChanged="<<pFibVectorChanged<<" ) the Fib vector object was deleted"<<endl<<flush);
		pFibVector = NULL;
		pDefiningFibElement = NULL;
		uiNumberOfElement = 0;
		mutexFibVectorElement.unlock();
		
		mutexFibVectorElementWidget.lock();
		liDefinedVariables.clear();
		
		if ( pMasterNode ){
			//no vector -> no master node
			pMasterNode->unregisterNodeChangeListener( this );
			pMasterNode = NULL;
		}
		mutexFibVectorElementWidget.unlock();
		
		emit signalCreateFibVectorElementWidget();
		return;
	}//the Fib vector object was changed -> redraw this widget
	
	const unsigned int uiChangedElement =
		pFibVectorChanged->getNumberOfElementChanged();
	bool bSendSignalCreateFibVectorElementWidget = false;
	if ( 0 < uiChangedElement ) {
		//update vector element number
		DEBUG_OUT_L3(<<"cWidgetFibVectorElement("<<this<<")::fibVectorChangedEvent( pFibVectorChanged="<<pFibVectorChanged<<" ) update vector element number "<<uiChangedElement<<endl<<flush);
		switch ( pFibVectorChanged->getElementChangeType() ) {
			case eFibVectorChangedEvent::ADD:{
				if ( uiChangedElement <= uiNumberOfElement ) {
					//element added befor this element
					uiNumberOfElement++;
				}
			}break;
			case eFibVectorChangedEvent::REMOVE:{
				if ( uiChangedElement < uiNumberOfElement ) {
					//element removed before this element
					uiNumberOfElement--;
				}//TODO? what to do if this element was removed
			}break;
			case eFibVectorChangedEvent::REPLACE:{
				if ( uiChangedElement == uiNumberOfElement ) {
					//this element was replaced -> update this widget
					bSendSignalCreateFibVectorElementWidget = true;
				}
			}break;
			
			default:;//else do nothing
		}
	}else{// uiChangedElement == 0 -> all vector elements changed
		DEBUG_OUT_L3(<<"cWidgetFibVectorElement("<<this<<")::fibVectorChangedEvent( pFibVectorChanged="<<pFibVectorChanged<<" ) all vector elements changed"<<endl<<flush);
		if ( pFibVector ) {
			if ( pFibVector->getNumberOfElements() < uiNumberOfElement ) {
				//number of element to great
				uiNumberOfElement = pFibVector->getNumberOfElements();
			}
		}
	}
	
	mutexFibVectorElement.unlock();
	if ( bSendSignalCreateFibVectorElementWidget ) {
		emit signalCreateFibVectorElementWidget();
	}
	DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::fibVectorChangedEvent( pFibVectorChanged="<<pFibVectorChanged<<" ) done"<<endl<<flush);
}


/**
 * Event method
 * It will be called every time a variable (cFibVariableCreator),
 * at which this object is registered, was changed.
 *
 * @param pFibVariableChangedEvent a pointer to the event with the
 * 	information of the change of the Fib creator variable
 */
void cWidgetFibVectorElement::changedEvent(
		const eFibVariableCreatorChangedEvent * pFibVariableChangedEvent ) {
	
	DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::changedEvent( pFibVariableChangedEvent="<<pFibVariableChangedEvent<<") called"<<endl<<flush);
	if ( pFibVariableChangedEvent == NULL ) {
		//no event given
		return;
	}
	if ( pFibVariableChangedEvent->isDeleted() ) {
		//remove deleted variable
		cFibVariableCreator * pDeletedVariable = const_cast<cFibVariableCreator*>(
				pFibVariableChangedEvent->getObject() );
		mutexFibVectorElement.lock();
		
		if ( pLastSetVariable == pDeletedVariable ){
			//last selected variable deleted -> no last selected variable
			pLastSetVariable = NULL;
		}
		mutexFibVectorElement.unlock();
		
		mutexFibVectorElementWidget.lock();
		
		//check if a defined variable was deleted
		bool bDefinedVariableDeleted = false;
		for ( QList< cFibVariableCreator * >::iterator
				itrVariable = liDefinedVariables.begin();
				itrVariable != liDefinedVariables.end(); itrVariable++ ) {
			if ( (*itrVariable) == pDeletedVariable ) {
				//defined variable was deleted -> recreate widget
				bDefinedVariableDeleted = true;
				//evaluate new defined variables
				liDefinedVariables = getDefinedVariables();
				break;
			}
		}
		mutexFibVectorElementWidget.unlock();
		
		//check if a variable is shown (just then defined variables are important)
		if ( bDefinedVariableDeleted ){
			iGetWidget * pVectorElement = getFibVectorElement();
			if ( ( pVectorElement != NULL ) && (
					( pVectorElement->getName() == "cFibVariableCreator" ) ||
					( pVectorElement->getName() == "cFibInputVariable" ) ) ) {
				/* variable is shown
				 * -> need to update widget for changed defined variables
				 * -> recreate Fib vector element widget*/
				emit signalCreateFibVectorElementWidget();
			}
		}
	}
	DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::changedEvent( pFibVariableChangedEvent="<<pFibVariableChangedEvent<<") done"<<endl<<flush);
}


/**
 * Event method
 * It will be called every time a Fib node (cFibNode), at which
 * this object is registered, was changed.
 *
 * @param pFibNodeChangedEvent a pointer to the event, with the information
 * 	about the changed Fib node
 */
void cWidgetFibVectorElement::fibNodeChangedEvent(
		const eFibNodeChangedEvent * pFibNodeChangedEvent ) {
	
	
	DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::fibNodeChangedEvent( pFibNodeChangedEvent="<<pFibNodeChangedEvent<<") called"<<endl<<flush);
	
	if ( ( pFibNodeChangedEvent == NULL ) ||
			( pFibNodeChangedEvent->getChangedNode() == NULL ) ){
		//nothing changed
		return;
	}
	if ( pFibNodeChangedEvent->isDeleted() ){
		/*node for master Fib object for the Fib element of the the vector
		 deleted*/
		mutexFibVectorElement.lock();
		pMasterNode = NULL;
		//if master node is deleted, Fib object is deleted
		pFibVector  = NULL;
		pDefiningFibElement = NULL;
		mutexFibVectorElement.unlock();
		//recreate Fib vector element widget
		emit signalCreateFibVectorElementWidget();
		/*TODO weg (if master node is deleted, Fib object is deleted)
		mutexFibVectorElement.lock();
		if ( pFibVector ){
			//try to evalue new master node
			DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::fibNodeChangedEvent( pFibNodeChangedEvent="<<pFibNodeChangedEvent<<") try to evalue new master node for vector "<<pFibVector<<endl<<flush);
			
			cFibElement * pDefiningFibElement = pFibVector->getFibElement();
			cFibNodeHandler * pNodeHandler = cFibNodeHandler::getInstance();
			if ( ( pDefiningFibElement != NULL ) && ( pNodeHandler != NULL) ){
				cFibElement * pMasterFibRoot = pDefiningFibElement->getMasterRoot();
				
				if ( pMasterFibRoot ){
					//register this as node change listener
					pMasterNode = pNodeHandler->getNodeForFibObject(
						pMasterFibRoot, this );
				}
			}
		}
		mutexFibVectorElement.unlock();
		*/
		return;
	}

	if ( pFibNodeChangedEvent->getChangeBy() == this ){
		//nothing changed
		DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::fibNodeChangedEvent( pFibNodeChangedEvent="<<pFibNodeChangedEvent<<") done nothing changed"<<endl<<flush);
		return;
	}
	/*check if the Fib object for this vector is superior or contained in a
	 *changed Fib element or Fib object*/
	const bool bIsContainedInChanged =
		pFibNodeChangedEvent->isContainedInChanged( pDefiningFibElement  );
	const bool bIsElementChanged =
		pFibNodeChangedEvent->isElementChanged( pDefiningFibElement );
	if ( ( ! bIsElementChanged ) && ( ! bIsContainedInChanged ) ) {
		/*the Fib element for this vector is not contained in or a Fib element
		 *which was changed
		 -> this vector don't needs to be updated
		 -> everything up to date
		 -> nothing to do*/
		DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::fibNodeChangedEvent() done: everything up to date"<<endl<<flush);
		return;
	}
	mutexFibVectorElement.lock();
	bool bRecreateWidget = false;
	if ( bIsElementChanged ) {
		//the Fib element for the vector changed
		if ( pFibNodeChangedEvent->isElementChanged( pDefiningFibElement,
				eFibNodeChangedEvent::DELETED ) ) {
			//the Fib element for this graphical item was deleted
			DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::fibNodeChangedEvent() done: the defining Fib element for this graphical item was deleted"<<endl<<flush);
			pFibVector = NULL;
			pDefiningFibElement = NULL;
			mutexFibVectorElement.unlock();
			//recreate Fib vector element widget
			emit signalCreateFibVectorElementWidget();
			return;
		}
		//the vector could be moved from Fib element
		if ( pFibVector ) {
			//reevalue the defining Fib element
			pDefiningFibElement = pFibVector->getFibElement();
		}
		bRecreateWidget = true;
	}
	mutexFibVectorElement.unlock();
	
	//check if the defined variables need to be reevalued
	if ( bIsContainedInChanged ) {
		//evaluate new defined variables
		mutexFibVectorElementWidget.lock();
		QList< cFibVariableCreator * > liDefinedVariablesNew =
			getDefinedVariables();
		
		if ( liDefinedVariables != liDefinedVariablesNew ){
			//defined variables changed
			liDefinedVariables = liDefinedVariablesNew;
			//evalue actual vector element
			iGetWidget * pVectorElement = ( pFibVector == NULL ) ? NULL :
				pFibVector->getElement( uiNumberOfElement );
			if ( ( pVectorElement != NULL ) &&
					( ( pVectorElement->getName() == "cFibVariableCreator" ) ||
						( pVectorElement->getName() == "cFibInputVariable" ) ) ) {
				
				/* defined variables changed + variable is shown
				 * -> need to update widget for changed defined variables
				 * -> recreate Fib vector element widget*/
				bRecreateWidget = true;
			}//else not a vector element -> defined variables not relevant
		}
		mutexFibVectorElementWidget.unlock();
	}
	if ( bRecreateWidget ) {
		emit signalCreateFibVectorElementWidget();
	}
	
	DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::fibNodeChangedEvent( pFibNodeChangedEvent="<<pFibNodeChangedEvent<<") done"<<endl<<flush);
}


/**
 * This slot sets the type of the vector element to the given type.
 * Note: This method will also adapt the vector pFibVector.
 *
 * @see pChooseType
 * @see pFibVector
 * @param iSelectedItem the index for the selected type:
 * 	0: select value
 * 	1: select variable
 * @return true if type could be set, else false
 */
bool cWidgetFibVectorElement::slotChangeTypeTo( const int iSelectedItem ) {
	
	DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::slotChangeTypeTo( iSelectedItem="<<iSelectedItem<<" ) called"<<endl<<flush);
	//evalue pOldElement
	iGetWidget * pOldElement = getFibVectorElement();
	mutexFibVectorElement.lock();
	
	if ( pOldElement != NULL ) {
		if ( ( pOldElement->getName() == "cFibVariableCreator" ) ||
				( pOldElement->getName() == "cFibInputVariable" ) ) {
			//remember last set variable element
			pLastSetVariable = static_cast<cFibVariableCreator *>(pOldElement);
		
		}else if ( pOldElement->getName() == "cFibScalar" ) {
			dLastSetValue = static_cast< cFibScalar* >(pOldElement)->getValue();
		}
	}
	bool bElementReplaced = false;
	switch ( iSelectedItem ) {
		case 0:{//change to value
			mutexFibVectorElement.unlock();
			if ( ( pOldElement != NULL ) &&
					( pOldElement->getName() == "cFibScalar" ) ) {
				//allready a scalar value -> done
				return true;
			}
			
			if ( pFibVector ) {
				bElementReplaced = pFibVector->replaceElement(
					uiNumberOfElement, dLastSetValue );
			}
			
			emit signalCreateFibVectorElementWidget();
			return bElementReplaced;
		};
		case 1:{//change to variable
			mutexFibVectorElement.unlock();
			if ( ( pOldElement != NULL ) && (
					( pOldElement->getName() == "cFibVariableCreator" ) ||
					( pOldElement->getName() == "cFibInputVariable" ) ) ) {
				//allready a variable -> done
				return true;
			}
			
			if ( pFibVector ) {
				if ( pLastSetVariable ) {
					//reuse old variable
					bElementReplaced = pFibVector->replaceElement(
						uiNumberOfElement, pLastSetVariable );
					
					emit signalCreateFibVectorElementWidget();
				}else{//use new variable (last defined variable above)
					createFibVectorElementWidget();
					
					mutexFibVectorElement.unlock();
					mutexFibVectorElementWidget.lock();
					cFibVariableCreator * pSelectedVariable =
						( pChooseVariable == NULL ) ? NULL :
							liDefinedVariables.value( pChooseVariable->currentIndex(), NULL );
					mutexFibVectorElementWidget.unlock();
					mutexFibVectorElement.unlock();
					
					if ( pSelectedVariable != NULL ) {
						bElementReplaced = pFibVector->replaceElement(
							uiNumberOfElement, pSelectedVariable );
					}//else no Fib vector or no variable to set -> can't change
					
				}
			}//else no Fib vector -> can't change
			
			if ( ! bElementReplaced ) {
				//set back value
				mutexFibVectorElementWidget.lock();
				if ( pChooseType ){
					mutexFibVectorElementWidget.unlock();
					pChooseType->setCurrentIndex( 0 );
				}
			}
			return bElementReplaced;
		}
		default: ;//unknown type
	}
	return false;
}


/**
 * This slot sets the vector element to the given variable.
 * Note: This method will also adapt the vector pFibVector.
 *
 * @see liDefinedVariables
 * @see pChooseVariable
 * @param iSelectedItem the index for the selected variable (in
 * 	liDefinedVariables and pChooseVariable)
 * @return true if variable could be set, else false
 */
bool cWidgetFibVectorElement::slotSetSelectedVariable(
		const int iSelectedVariable ){
	
	DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::slotSetSelectedVariable( iSelectedVariable="<<iSelectedVariable<<" ) called"<<endl<<flush);
	
	mutexFibVectorElementWidget.lock();
	
	cFibVariableCreator * pNewVariable = liDefinedVariables.value(
		iSelectedVariable, NULL );
	if ( pNewVariable == NULL ) {
		//no variable to set
		mutexFibVectorElementWidget.unlock();
		DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::slotSetSelectedVariable( iSelectedVariable="<<iSelectedVariable<<" ) done: no variable to set"<<endl<<flush);
		return false;
	}
	//TODO adapt button if the variable definition can be shown
	
	
	mutexFibVectorElementWidget.unlock();
	//remember variable as last set variable
	mutexFibVectorElement.lock();
	pLastSetVariable = pNewVariable;
	mutexFibVectorElement.unlock();
	//adapt the vector
	DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::slotSetSelectedVariable( iSelectedVariable="<<iSelectedVariable<<" ) done set variable: "<<pNewVariable<<endl<<flush);
	return pFibVector->replaceElement( uiNumberOfElement, pNewVariable );
}


/**
 * This method will (re-)create this Fib vector element widget
 * correspondending to the actual Fib vector object.
 * @see pFibVector
 */
void cWidgetFibVectorElement::createFibVectorElementWidget() {
	
	DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::createFibVectorElementWidget() called for element "<<uiNumberOfElement<<endl<<flush);
	//evalue actual vector element
	iGetWidget * pVectorElement = getFibVectorElement();
	
	mutexFibVectorElementWidget.lock();
	
	//clear old elements
	liVectorElement.clear();
	if ( pElementWidget ) {
		//if existing allways delete the element widget
		pElementWidget->deleteLater();
		pElementWidget = NULL;
	}
	
	if ( pVectorElement == NULL ) {
		//no vector element -> display nothing -> delete all existing subelements
		DEBUG_OUT_L3(<<"cWidgetFibVectorElement("<<this<<")::createFibVectorElementWidget() no such vector element"<<endl<<flush);
		if ( pChooseType ) {
			pChooseType->deleteLater();
			pChooseType = NULL;
		}
		if ( pChooseVariable ) {
			pChooseVariable->deleteLater();
			pChooseVariable = NULL;
		}
		
		if ( pLayoutMain ) {
			pLayoutMain->deleteLater();
			pLayoutMain = NULL;
		}
	}else{//pVectorElement exists
		
		if ( pLayoutMain == NULL ) {
			//create new main layout
			pLayoutMain = new QVBoxLayout();
			//set the main layout
			setLayout( pLayoutMain );
		}
		//create and add choose type widget
		if ( pChooseType == NULL ) {
			pChooseType = createChooseType( pVectorElement );
			pLayoutMain->addWidget( pChooseType );
		}
		liVectorElement.push_back( pChooseType );
		
		if ( ( pVectorElement->getName() == "cFibVariableCreator" ) ||
				( pVectorElement->getName() == "cFibInputVariable" ) ) {
			//display variable dialog
			DEBUG_OUT_L3(<<"cWidgetFibVectorElement("<<this<<")::createFibVectorElementWidget() display variable dialog"<<endl<<flush);
			
			//create combo box to select variables from
			mutexFibVectorElement.lock();
			
			mutexFibVectorElement.unlock();
			
			//create category combo box
			if ( pChooseVariable ){
				//delete old combo box to choose a variable from
				pChooseVariable->deleteLater();
			}
			pChooseVariable = new QComboBox( this );
			pChooseVariable->setInsertPolicy( QComboBox::NoInsert );
			int indexSelectedVariable = 0;
			int iActualIndex = 0;
			for ( QList< cFibVariableCreator * >::const_iterator
					itrVariable = liDefinedVariables.begin();
					itrVariable != liDefinedVariables.end();
					itrVariable++, iActualIndex++ ) {
				//insert defined variable
				pChooseVariable->addItem( (*itrVariable)->getVariableName() );
				
				if ( (*itrVariable) == pLastSetVariable ){
					indexSelectedVariable = iActualIndex;
				}
			}
			connect( pChooseVariable, SIGNAL( currentIndexChanged( int ) ),
				this, SLOT( slotSetSelectedVariable( int ) ) );
			
			/*set selected variable; if no variable selected before, select first
			 *variable (last defined variable above)*/
			pChooseVariable->setCurrentIndex( indexSelectedVariable );
			
			//add the combo box to this layout
			pLayoutMain->addWidget( pChooseVariable );
			liVectorElement.push_back( pChooseVariable );
			
			//TODO create button to show actual variable definition
			
			
			
		}else{//display widget for element ( pVectorElement->getName() == "cFibScalar" )
			//create and add element widget
			pElementWidget = pVectorElement->getWidget();
			DEBUG_OUT_L3(<<"cWidgetFibVectorElement("<<this<<")::createFibVectorElementWidget() display widget for element "<<pVectorElement->getName()<<"(widget pointer "<<pElementWidget<<")"<<endl<<flush);
			if ( pElementWidget ) {
				liVectorElement.push_back( pElementWidget );
				pLayoutMain->addWidget( pElementWidget );
			}
			
		}
	}
	mutexFibVectorElementWidget.unlock();
	
	DEBUG_OUT_L2(<<"cWidgetFibVectorElement("<<this<<")::createFibVectorElementWidget() done"<<endl<<flush);
}


/**
 * This method creates the choose type subwidget of this widget.
 *
 * @see pChooseType
 * @see createFibVectorElementWidget
 * @return a pointer to the choose type widget for this element
 */
QComboBox * cWidgetFibVectorElement::createChooseType(
		const iGetWidget * pVectorElement ) const {
	
	QComboBox * pComboChooseType = new QComboBox();
	pComboChooseType->setInsertPolicy( QComboBox::NoInsert );
	
	//insert category "value"
	pComboChooseType->addItem( tr("value", "switch vector element to value") );
	//insert category "variable"
	pComboChooseType->addItem( tr("variable", "switch vector element to variable") );
	//TODO insert category "new variable"
	// pComboChooseType->addItem( tr("new variable", "create a new variable for the vector element") );
	if ( pVectorElement == NULL ) {
		//select the actual element type
		if ( pVectorElement->getName() == "cFibScalar" ) {
			
			pComboChooseType->setCurrentIndex( 0 );
			
		}else if ( ( pVectorElement->getName() == "cFibVariableCreator" ) ||
				( pVectorElement->getName() == "cFibInputVariable" ) ) {
			
			pComboChooseType->setCurrentIndex( 1 );
		}
	}
	connect( pComboChooseType, SIGNAL( currentIndexChanged( int ) ),
		this, SLOT( slotChangeTypeTo( int ) ) );
	
	return pComboChooseType;
}


/**
 * This method evalues the for the Fib vector element defined variables.
 * Note: it won't use a mutex (mutexFibVectorElementWidget).
 *
 * @return a list with the Fib creator variables of the Fib variables,
 * 	which are defined for the Fib element of the vector for this vector element
 */
QList< cFibVariableCreator * > cWidgetFibVectorElement::getDefinedVariables() {
	//get all higher defined variables
	list<cFibVariable*> liDefinedFibVariables;
	mutexFibVectorElement.lock();
	if ( pDefiningFibElement ) {
		liDefinedFibVariables =
			pDefiningFibElement->getDefinedVariables( ED_HIGHER );
	}
	mutexFibVectorElement.unlock();
	cFibVariableHandler * pVariableHandler =
		cFibVariableHandler::getInstance();
	cFibVariableCreator * pNewVariableCreator = NULL;
	
	QList< cFibVariableCreator * > liDefinedVariablesFound;
	if ( pVariableHandler ){
		for ( list<cFibVariable*>::iterator
				itrFibVariable = liDefinedFibVariables.begin();
				itrFibVariable != liDefinedFibVariables.end(); itrFibVariable++ ){
			
			pNewVariableCreator =
				pVariableHandler->getFibVariableCreatorForFibVariable(
					(*itrFibVariable), this );
			if ( pNewVariableCreator ){
				liDefinedVariablesFound.push_front( pNewVariableCreator );
			}
		}
	}
	return liDefinedVariablesFound;
}


/**
 * This method clears the defined variables (liDefinedVariables).
 * It will also unregister this object at all defined variables.
 * Note: it won't use a mutex (mutexFibVectorElementWidget).
 *
 * @see liDefinedVariables
 */
void cWidgetFibVectorElement::clearDefinedVariables(){
	//unregister this object as change listener for the variables
	for ( QList< cFibVariableCreator * >::iterator
			itrVariable = liDefinedVariables.begin();
			itrVariable != liDefinedVariables.end(); itrVariable++ ) {
		
		if ( *itrVariable ) {
			(*itrVariable)->unregisterChangeListener( this );
		}
	}
	
	liDefinedVariables.clear();
}


/**
 * @return a hint for a good size of this widget
 */
QSize cWidgetFibVectorElement::sizeHint() const {
	
	//DEBUG_OUT_L4(<<"cWidgetFibVectorElement("<<this<<")::sizeHint() called"<<endl<<flush);
	
	QSize goodSize( 0, 0 );
	
	if ( pChooseType ) {
		goodSize = pChooseType->sizeHint();
	}
	//enlarge for subelements
	for ( QList< QWidget * >::const_iterator
			itrSubelement = liVectorElement.begin();
			itrSubelement != liVectorElement.end(); itrSubelement++ ) {
		if ( *itrSubelement ) {
			//subelement exists
			const QSize sizeSubelement = (*itrSubelement)->sizeHint();
			goodSize.setWidth( max( goodSize.rwidth(), sizeSubelement.width() ) );
			goodSize.setHeight( goodSize.rheight() + sizeSubelement.height() );
		}
	}//end for enlarge for subelements
	
	return goodSize;
}






