
//TODO check

/**
 * @file cFibVectorCreator
 * file name: cFibVectorCreator.cpp
 * @author Betti Oesterholz
 * @date 25.11.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a Fib vector.
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
 * This file implements a class for a Fib vector.
 * If you have a Fib element, vectors of it can be represented with this
 * class for the Fib creator modul.
 * A Fib vector contains a number of elements.
 * This class adds events and listeners to the Fib vector (cFibVector).
 * @pattern Decorator
 *
 * @see cFibVector
 * @see cFibScalar
 * @see cFibVectorCreator
 */
/*
History:
25.11.2013  Oesterholz  created
*/


//TODO switches for test proposes
#define DEBUG

#include "cFibVectorCreator.h"

#include <list>

#include <QObject>

#include "cExtObject.h"
#include "cExtSubobject.h"
#include "cTypeProperty.h"
#include "cTypeElement.h"

#include "cFibVectorHandler.h"
#include "cFibVariableHandler.h"
#include "cFibVariableCreator.h"
#include "cFibInputVariable.h"
#include "lFibVectorChanged.h"
#include "eFibVectorChangedEvent.h"
#include "cWidgetFibVector.h"
#include "cFibNodeHandler.h"
#include "cFibNode.h"


using namespace std;
using namespace fib::nCreator;


/**
 * The standard constructor for a vector.
 * It constructs a vector with no elements. (So you can add them later.)
 */
cFibVectorCreator::cFibVectorCreator(): strVectorName(""), pFibElement( NULL ),
		pFibVector( NULL ) {
	//nothing to do
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::cFibVectorCreator() called"<<endl<<flush);
}


/**
 * A parameter constructor for a vector.
 *
 * @param pInFibVector a pointer to the Fib vector of this vector,
 * 	The elements for this vector will be read from this vector.
 * 	The Fib element for this vector will be the defining Fib element
 * 	of the given vector.
 * 	@see pFibVector
 */
cFibVectorCreator::cFibVectorCreator( fib::cFibVector * pInFibVector ): strVectorName(""),
		pFibElement( NULL ), pFibVector( pInFibVector ) {
	//nothing to do
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::cFibVectorCreator( pInFibVector="<<pInFibVector<<" ) called"<<endl<<flush);
	
	if ( pInFibVector ) {
		pFibElement = pInFibVector->getDefiningFibElement();
		
		mutexFibVectorHandler.lock();
		
		cFibVariableHandler * pFibVariableHandler =
			cFibVariableHandler::getInstance();
		
		const unsignedIntFib uiNumberOfElements =
			pInFibVector->getNumberOfElements();
		
		const cTypeElement * pVectorType = pInFibVector->getElementType();
		
		if ( strVectorName.isEmpty() && ( pVectorType != NULL ) ) {
			//no vector name found yet -> use domain element name (eg. dimensions)
			switch ( pVectorType->getType() ) {
				case 1:{//cTypeDimension
					strVectorName = QObject::tr( "dimension " );
				};break;
				case 2:{//cTypeUnderArea
					strVectorName = QObject::tr( "area" );
				};break;
				case 3:{//cTypeUnderFunction
					strVectorName = QObject::tr( "subfunction" );
				};break;
				case 5:{//cTypeInVar
					strVectorName = QObject::tr( "input variables" );
				};break;
				case 6:{//cTypeProperty
					strVectorName = QObject::tr( "property " ) +
					//TODO? use property types ( cTypeProperty::getNumberOfProperty() )
						QString( static_cast<const cTypeProperty *>(
							pVectorType)->getNameOfProperty().c_str() );
				};break;
				case 10:{//cTypeVariable
					strVectorName = QObject::tr( "variable" );
				};break;
				case 11:{//cTypeComments
					strVectorName = QObject::tr( "comment" );
				};break;
				case 12:{//cTypeExtObject
					strVectorName = QObject::tr( "external object" );
				};break;
				case 13:{//cTypeExtSubobject
					strVectorName = QObject::tr( "external subobject" );
				};break;
				case 14:{//cTypeFibSet
					strVectorName = QObject::tr( "subset" );
				};break;
				case 15:{//cTypeFibMatrix
					strVectorName = QObject::tr( "matrix entry" );
				};break;
				case 16:{//cTypeExtObjectInput
					strVectorName = QObject::tr( "external object input" );
				};break;
				
				//TODO more vector types
			};//end switch vector type
		}
		
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= uiNumberOfElements; uiActualElement++ ) {
			
			if ( pInFibVector->isVariable( uiActualElement ) ) {
				
				cFibVariableCreator * pElementVariable =
					pFibVariableHandler->getFibVariableCreatorForFibVariable(
						pInFibVector->getVariable( uiActualElement ), this );
				
				if ( pElementVariable ) {
/*TODO weg:
					//variable name= variable name -> vector element name
					pElementVariable->setVariableName(
						pElementVariable->getVariableName() +
						QString(" -> ") + vecElementName );
					
*/
					registerForElement( pElementVariable );
					
					liElements.push_back( pElementVariable );
				}else{
					//Error: can't create input variable -> use scalar
					cFibScalar * pElementScalar = new cFibScalar( 0,
						QObject::tr("Variable error ") +
						QString::number( uiActualElement ) );
					liElements.push_back( pElementScalar );
					
					registerForElement( pElementScalar );
				}
			}else{//element is a scalar
				cDomain * pElementDomain =
					pInFibVector->getDomain( uiActualElement );
				cDomainSingle * pScalarDomain =
					( ( pElementDomain == NULL ) || ( ! pElementDomain->isScalar() ) ) ?
						NULL : ( static_cast<cDomainSingle*>(pElementDomain->clone()) );
				
				cFibScalar * pElementScalar = new cFibScalar(
					pInFibVector->getValue( uiActualElement ),
					getVectorElementName( uiActualElement ), pScalarDomain );
				
				liElements.push_back( pElementScalar );
				
				registerForElement( pElementScalar );
			}
		}
		if ( pVectorType ) {
			//delete vector element type
			delete pVectorType;
		}
		mutexFibVectorHandler.unlock();
	}
}


/**
 * A parameter constructor for a vector.
 *
 * @param liInElements list with element for this object
 * 	@see liElements
 * @param szVectorName the name of the vector
 * @param pInFibVector a pointer to the Fib vector of this vector
 * 	(Note: It should contain the same elements in the same order as liInElements .)
 * 	@see pFibVector
 * @param pInFibElement the Fib element for which this vector is or NULL
 * 	(The Fib element which contains the vector)
 * 	@see pFibElement
 */
cFibVectorCreator::cFibVectorCreator( QList< iGetWidget * > & liInElements,
		const QString szVectorName, fib::cFibVector * pInFibVector,
		cFibElement * pInFibElement ):
		strVectorName( szVectorName ), liElements( liInElements ),
		pFibElement( pInFibElement ), pFibVector( pInFibVector ) {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::cFibVectorCreator( liInElements, szVectorName=\""<<szVectorName.toStdString()<<"\", pInFibElement="<<pInFibElement<<" ) called"<<endl<<flush);
	
	mutexFibVectorHandler.lock();
	//register this vector as a listener for element changes
	for ( QList< iGetWidget * >::iterator itrElement = liElements.begin();
			itrElement != liElements.end(); itrElement++ ) {
		
		registerForElement( *itrElement );
	}
	mutexFibVectorHandler.unlock();
}


/**
 * destructor
 */
cFibVectorCreator::~cFibVectorCreator() {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::~cFibVectorCreator() called"<<endl<<flush);
	const eFibVectorChangedEvent fibVectorChangedEvent( this, true );
	sendFibVectorChange( &fibVectorChangedEvent );
	
	mutexFibVectorHandler.lock();
	//register this vector as a listener for element changes
	while ( ! liElements.empty() ) {
		
		removeElementFromVector( liElements.front() );
	}
	cFibVectorHandler::getInstance()->removeVector( this );
	mutexFibVectorHandler.unlock();
}



/**
 * @return the name of this class "cFibVectorCreator"
 */
std::string cFibVectorCreator::getName() const{
	
	return string( "cFibVectorCreator" );
}


/**
 * @return the name of this vector
 * 	@see strVectorName
 */
QString cFibVectorCreator::getVectorName() const{
	
	mutexFibVectorHandler.lock();
	const QString strRetVectorName = strVectorName;
	mutexFibVectorHandler.unlock();
	return strRetVectorName;
}


/**
 * This method sets the name of this vector to the given name.
 *
 * @see strVectorName
 * @param strName the name the vector should have
 */
void cFibVectorCreator::setVectorName( const QString & strName ) {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::setVectorName( strName=\""<<strName.toStdString()<<"\") called"<<endl<<flush);
	mutexFibVectorHandler.lock();
	if ( strVectorName != strName ) {
		strVectorName = strName;
		mutexFibVectorHandler.unlock();
		
		const eFibVectorChangedEvent fibVectorChangedEvent(
			this, eFibVectorChangedEvent::NAME );
		sendFibVectorChange( &fibVectorChangedEvent );
	}else{
		mutexFibVectorHandler.unlock();
	}
}


/**
 * @return the number of element in the vector
 * 	@see liElements
 */
unsigned int cFibVectorCreator::getNumberOfElements() const{
	
	mutexFibVectorHandler.lock();
	const unsigned int uiNumberOfScalars = liElements.size();
	mutexFibVectorHandler.unlock();
	return uiNumberOfScalars;
}


/**
 * This method returns the uiNumberOfElement'th element of this vector.
 *
 * @see liElements
 * @see getNumberOfElements()
 * @param uiNumberOfElement the number of the element to return
 * 	(counting starts with 1)
 * @return a pointer to the uiNumberOfElement'th element, or
 * 	NULL if non exists
 */
iGetWidget * cFibVectorCreator::getElement( const unsigned int uiNumberOfElement ) {
	
	mutexFibVectorHandler.lock();
	iGetWidget * pElement = liElements.value( uiNumberOfElement - 1, NULL );
	mutexFibVectorHandler.unlock();
	return pElement;
}


/**
 * This method returns the uiNumberOfElement'th element of this vector.
 *
 * @see liElements
 * @see getNumberOfElements()
 * @param uiNumberOfElement the number of the element to return
 * 	(counting starts with 1)
 * @return a const pointer to the uiNumberOfElement'th element,
 * 	or NULL if non exists
 */
const iGetWidget * cFibVectorCreator::getElement(
		const unsigned int uiNumberOfElement ) const{
	
	mutexFibVectorHandler.lock();
	const iGetWidget * pElement =
		liElements.value( uiNumberOfElement - 1, NULL );
	mutexFibVectorHandler.unlock();
	return pElement;
}


/**
 * @see liElements
 * @see getNumberOfElements()
 * @see getElement()
 * @return a list with the pointers to the element of this vector
 */
QList< iGetWidget * > cFibVectorCreator::getElements() {
	
	mutexFibVectorHandler.lock();
	const QList< iGetWidget * > liElementsRet = liElements;
	mutexFibVectorHandler.unlock();
	return liElementsRet;
}


/**
 * @see liElements
 * @see getNumberOfElements()
 * @see getElement()
 * @return a const list with the pointers to the element of this vector
 */
const QList< iGetWidget * > cFibVectorCreator::getElements() const{
	
	mutexFibVectorHandler.lock();
	const QList< iGetWidget * > liElementsRet = liElements;
	mutexFibVectorHandler.unlock();
	return liElementsRet;
}


/**
 * This method adds the given element to this vector.
 * This method will also adapt the Fib vector pFibVector.
 * Note: If the Fib vector can't be adapted, this method will fail.
 *
 * @see liElements
 * @see getNumberOfElements()
 * @see removeElement()
 * @see replaceElement()
 * @param pElement a pointer to the element to add
 * @param uiPosition the position where to add the element,
 * 	if 0 or greater the number of elements in this vector it will be
 * 	added to the end of the vector
 * 	(counting starts with 1)
 * @return true if the element was added, else false
 */
bool cFibVectorCreator::addElement( iGetWidget * pElement,
		const unsigned int /*uiPosition*/ ) {
	//can't add elements to this vector type
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::addElement( pElement="<<pElement<<" ) called"<<endl<<flush);
	return false;
}
/*TODO weg
bool cFibVectorCreator::addElement( iGetWidget * pElement,
		const unsigned int uiPosition ) {
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::addElement( pElement="<<pElement<<" ) called"<<endl<<flush);
	if ( pElement == NULL ) {
		//nothing to insert
		return false;
	}
	mutexFibVectorHandler.lock();
	if ( ( uiPosition < 1 ) || (
			(static_cast<unsigned int>(liElements.size())) < uiPosition ) ) {
		//add to end of element list
		liElements.append( pElement );
	}else{//insert on position
		liElements.insert( uiPosition - 1 , pElement );
	}
	
	registerForElement( pElement );
	
	//TODO adapt Fib vector
	
	
	mutexFibVectorHandler.unlock();
	
	const eFibVectorChangedEvent fibVectorChangedEvent(
		this, eFibVectorChangedEvent::ADD, uiPosition );
	sendFibVectorChange( &fibVectorChangedEvent );
	
	return true;
}
*/


/**
 * This method removes the uiPosition'th element from this vector.
 * This method will also adapt the Fib vector pFibVector.
 * Note: If the Fib vector can't be adapted, this method will fail.
 *
 * @see liElements
 * @see getNumberOfElements()
 * @see addElement()
 * @see replaceElement()
 * @param uiPosition the position where to remove the element from
 * 	(counting starts with 1)
 * @return true if the element was removed, else false
 */
bool cFibVectorCreator::removeElement( const unsigned int uiPosition ) {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::removeElement( uiPosition="<<uiPosition<<" ) called"<<endl<<flush);
	//can't remove elements from this vector type
	return false;
}
/*TODO weg
bool cFibVectorCreator::removeElement( const unsigned int uiPosition ) {
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::removeElement( uiPosition="<<uiPosition<<" ) called"<<endl<<flush);
	mutexFibVectorHandler.lock();
	if ( ( uiPosition < 1 ) ||
			( (static_cast<unsigned int>(liElements.size())) < uiPosition ) ) {
		//no such element to remove
		mutexFibVectorHandler.unlock();
		return false;
	}
	//evaluate the to remove element
	iGetWidget * pRemovedElement = liElements.value( uiPosition - 1, NULL );
	//remove the element
	liElements.removeAt( uiPosition - 1 );
	if ( ! liElements.contains( pRemovedElement ) ) {
		//remove from entire vector
		removeElementFromVector( pRemovedElement );
	}
	mutexFibVectorHandler.unlock();
	
	const eFibVectorChangedEvent fibVectorChangedEvent(
		this, eFibVectorChangedEvent::REMOVE, uiPosition );
	sendFibVectorChange( &fibVectorChangedEvent );
	
	return true;
}
*/


/**
 * This method removes the given element from this vector.
 * This method will also adapt the Fib vector pFibVector.
 * Note: If the Fib vector can't be adapted, this method will fail.
 *
 * @see liElements
 * @see getNumberOfElements()
 * @see addElement()
 * @see replaceElement()
 * @param pElement the element to remove
 * @return true if the element was removed, else false
 */
bool cFibVectorCreator::removeElement( iGetWidget * pElement ) {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::removeElement( pElement="<<pElement<<" ) called"<<endl<<flush);
	//can't remove elements from this vector type
	return false;
}
/*TODO weg
bool cFibVectorCreator::removeElement( iGetWidget * pElement ) {
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::removeElement( pElement="<<pElement<<" ) called"<<endl<<flush);
	mutexFibVectorHandler.lock();
	if ( ( pElement == NULL ) || ( ! liElements.contains( pElement ) ) ) {
		//no such element to remove
		mutexFibVectorHandler.unlock();
		return false;
	}
	
	int uiLastFoundIndex = 0;
	list< int > liFoundIndex;
	while ( true ) {
		uiLastFoundIndex = liElements.indexOf( pElement , uiLastFoundIndex );
		if ( uiLastFoundIndex < 0 ) {
			//element not found -> stop search
			break;
		}//else element found -> add index to found index and search for next
		liFoundIndex.push_back( uiLastFoundIndex );
	}
	if ( liFoundIndex.empty() ) {
		//no such element to remove
		mutexFibVectorHandler.unlock();
		return false;
	}
	
	//remove element
	removeElementFromVector( pElement );
	
	mutexFibVectorHandler.unlock();
	//send information about removed elements
	for ( list< int >::iterator itrRemovedElement = liFoundIndex.begin();
			itrRemovedElement != liFoundIndex.end(); itrRemovedElement++ ) {
		
		const eFibVectorChangedEvent fibVectorChangedEvent(
			this, eFibVectorChangedEvent::REMOVE,
			(*itrRemovedElement + 1 ) );
		sendFibVectorChange( &fibVectorChangedEvent );
	}
	
	return true;
}
*/


/**
 * This method replaces a element in this vector.
 * It will replace the uiPosition'th element in the vector with the given
 * element pElement (if possible).
 * This method will also adapt the Fib vector pFibVector.
 * Note: If the Fib vector can't be adapted, this method will fail.
 *
 * @see liElements
 * @see getNumberOfElements()
 * @see removeElement()
 * @see addElement()
 * @param uiPosition the position where to replace the element
 * 	(counting starts with 1)
 * @param pElement a pointer to the element to add, which will replace the
 * 	old element on the uiPosition'th position
 * @return true if the element was replace, else false
 */
bool cFibVectorCreator::replaceElement( const unsigned int uiPosition,
		iGetWidget * pElement ) {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::replaceElement( uiPosition="<<uiPosition<<" ,pElement="<<pElement<<" ) called"<<endl<<flush);
	mutexFibVectorHandler.lock();
	if ( ( pElement == NULL ) || ( uiPosition < 1 ) ||
			( (static_cast<unsigned int>(liElements.size())) < uiPosition ) ) {
		//no such element to replace
		mutexFibVectorHandler.unlock();
		return false;
	}
	//adapt Fib vector
	if ( pFibVector ){
		if ( pElement->getName() == "cFibScalar" ){
			//change to value
			pFibVector->setValue( uiPosition, static_cast<cFibScalar*>(
				pElement)->getValue() );
			
		}else if ( ( pElement->getName() == "cFibVectorCreator" ) ||
				( pElement->getName() == "cFibInputVariable" ) ){
			//change to variable
			pFibVector->setVariable( uiPosition, static_cast<cFibVariableCreator*>(
				pElement)->getFibVariable() );
		}else{//can't adapt vector element
			mutexFibVectorHandler.unlock();
			return false;
		}
	}//else no vector to adapt
	
	//evaluate the to remove element
	iGetWidget * pRemovedElement =
		liElements.value( uiPosition - 1, NULL );
	//remove the element
	liElements.removeAt( uiPosition - 1 );
	if ( ! liElements.contains( pRemovedElement ) ) {
		//unregister this as element change listener at elements
		removeElementFromVector( pRemovedElement );
	}
	
	//add the given element on the position
	if ( (static_cast<unsigned int>(liElements.size())) < uiPosition ) {
		//add element to the end of the element list
		liElements.push_back( pElement );
	}else{//insert the element at the given position
		liElements.insert( uiPosition - 1 , pElement );
	}
	//register this as element change listener at new elements
	registerForElement( pElement );
	
	mutexFibVectorHandler.unlock();
	
	const eFibVectorChangedEvent fibVectorChangedEvent(
		this, eFibVectorChangedEvent::REPLACE, uiPosition );
	sendFibVectorChange( &fibVectorChangedEvent );
	
	return true;
}


/**
 * This method replaces elements in this vector.
 * It will replace the pElementToReplace elements in the vector with the
 * given element pElement (if possible).
 * This method will also adapt the Fib vector pFibVector.
 * Note: If the Fib vector can't be adapted, this method will fail.
 *
 * @see liElements
 * @see getNumberOfElements()
 * @see removeElement()
 * @see addElement()
 * @param pElementToReplace a pointer to the element to replace
 * @param pElement a pointer to the element to add, which will replace the
 * 	old element pElementToReplace
 * @return true if the elements where replace, else false
 */
bool cFibVectorCreator::replaceElement( iGetWidget * pElementToReplace,
		iGetWidget * pNewElement ) {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::replaceElement( pElementToReplace="<<pElementToReplace<<", pNewElement="<<pNewElement<<" ) called"<<endl<<flush);
	mutexFibVectorHandler.lock();
	if ( ( pNewElement == NULL ) || ( pElementToReplace == NULL ) ||
			( pNewElement == pElementToReplace ) ||
			( liElements.contains( pElementToReplace ) ) ) {
		//no such element to replace
		mutexFibVectorHandler.unlock();
		return false;
	}
	//check if element in vector can be replaced
	if ( pFibVector ){
		if ( ( pNewElement->getName() != "cFibScalar" ) &&
				( pNewElement->getName() != "cFibVectorCreator" ) &&
				( pNewElement->getName() != "cFibInputVariable" ) ){
			//can't adapt vector element
			mutexFibVectorHandler.unlock();
			return false;
		}
	}
	//replace the elements
	int uiLastFoundIndex = 0;
	list< int > liFoundIndex;
	while ( true ) {
		uiLastFoundIndex = liElements.indexOf( pNewElement , uiLastFoundIndex );
		if ( uiLastFoundIndex < 0 ) {
			//element not found -> stop search
			break;
		}//else element found -> replace element, add index to found index and search for next
		liElements.replace( uiLastFoundIndex, pNewElement );
		liFoundIndex.push_back( uiLastFoundIndex );
	}
	//adapt Fib vector
	if ( pFibVector ){
		if ( pNewElement->getName() == "cFibScalar" ){
			//change to value
			for ( list< int >::iterator itrRemovedElement = liFoundIndex.begin();
					itrRemovedElement != liFoundIndex.end(); itrRemovedElement++ ) {
				
				pFibVector->setValue( (*itrRemovedElement) + 1,
					static_cast<cFibScalar*>(pNewElement)->getValue() );
			}
			
		}else{/* if ( ( pNewElement->getName() == "cFibVectorCreator" ) ||
				( pNewElement->getName() == "cFibInputVariable" ) )*/
			//change to variable
			for ( list< int >::iterator itrRemovedElement = liFoundIndex.begin();
					itrRemovedElement != liFoundIndex.end(); itrRemovedElement++ ) {
				
				pFibVector->setVariable( (*itrRemovedElement) + 1,
					static_cast<cFibVariableCreator*>(pNewElement)->getFibVariable() );
			}
		}
	}//else no vector to adapt
	
	//register this as element change listener at new elements
	registerForElement( pNewElement );
	
	/*remove / delete the pElementToReplace element +
	unregister this as element change listener at elements*/
	removeElementFromVector( pElementToReplace );
	
	mutexFibVectorHandler.unlock();
	
	//send information about removed elements
	for ( list< int >::iterator itrRemovedElement = liFoundIndex.begin();
			itrRemovedElement != liFoundIndex.end(); itrRemovedElement++ ) {
		
		const eFibVectorChangedEvent fibVectorChangedEvent(
			this, eFibVectorChangedEvent::REPLACE,
			(*itrRemovedElement + 1 ) );
		sendFibVectorChange( &fibVectorChangedEvent );
	}
	
	return true;
}

/**
 * This method replaces a element in this vector.
 * It will replace the uiPosition'th element in the vector with a scalar
 * value element with value dValue.
 * This method will also adapt the Fib vector pFibVector.
 * Note: If the Fib vector can't be adapted, this method will fail.
 *
 * @see liElements
 * @see getNumberOfElements()
 * @see removeElement()
 * @see addElement()
 * @param uiPosition the position where to replace the element
 * 	(counting starts with 1)
 * @param dValue the value for the scalar element, which will replace the
 * 	old element on the uiPosition'th position
 * @return true if the element was replace, else false
 */
bool cFibVectorCreator::replaceElement( const unsigned int uiPosition,
		const doubleFib dValue ) {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::replaceElement( uiPosition="<<uiPosition<<" , dValue="<<dValue<<" ) called"<<endl<<flush);
	mutexFibVectorHandler.lock();
	
	if ( ( uiPosition < 1 ) ||
			( (static_cast<unsigned int>(liElements.size())) < uiPosition ) ) {
		//no such element to replace
		mutexFibVectorHandler.unlock();
		return false;
	}
	//adapt Fib vector
	if ( pFibVector ){
		//change to value
		pFibVector->setValue( uiPosition, dValue );
	}//else no vector to adapt
	
	//evaluate the to remove element
	iGetWidget * pRemovedElement =
		liElements.value( uiPosition - 1, NULL );
	//remove the element
	liElements.removeAt( uiPosition - 1 );
	if ( ! liElements.contains( pRemovedElement ) ) {
		//unregister this as element change listener at elements
		removeElementFromVector( pRemovedElement );
	}
	//create the scalar element to insert
	cDomain * pElementScalarDomain =
		pFibVector->getDomain( uiPosition );
	cDomainSingle * pScalarDomain =
		( ( pElementScalarDomain == NULL ) || ( ! pElementScalarDomain->isScalar() ) ) ?
			NULL : ( static_cast<cDomainSingle*>(pElementScalarDomain->clone()) );
	
	cFibScalar * pElementScalar = new cFibScalar(
		dValue, getVectorElementName( uiPosition ), pScalarDomain );
	
	//add the scalar element on the position
	if ( (static_cast<unsigned int>(liElements.size())) < uiPosition ) {
		//add element to the end of the element list
		liElements.push_back( pElementScalar );
	}else{//insert the element at the given position
		liElements.insert( uiPosition - 1 , pElementScalar );
	}
	//register this as element change listener at new elements
	registerForElement( pElementScalar );
	
	mutexFibVectorHandler.unlock();
	
	const eFibVectorChangedEvent fibVectorChangedEvent(
		this, eFibVectorChangedEvent::REPLACE, uiPosition );
	sendFibVectorChange( &fibVectorChangedEvent );
	
	return true;
}



/**
 * This method sets the vector to the given list of elements.
 * All old element of this vector are removed and the given elements added.
 * This method will also adapt the Fib vector pFibVector.
 * Note: If the Fib vector can't be adapted, this method will fail.
 *
 * @see liElements
 * @see getNumberOfElements()
 * @see replaceElement()
 * @see removeElement()
 * @see addElement()
 * @param liInElements a list of the element this object should contain
 * @return true if the elements could be set, else false
 */
bool cFibVectorCreator::setElements( QList< iGetWidget * > & liInElements ) {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::setElements( #liInElements="<<liInElements.size()<<" ) called"<<endl<<flush);
	mutexFibVectorHandler.lock();
	
	if ( pFibVector ){
		//check if Fib vector can be adapted
		if ( pFibVector->getNumberOfElements() !=
				static_cast<unsignedIntFib>(liInElements.size()) ){
			//vectors not of the same size -> can't adapt Fib vector
			mutexFibVectorHandler.unlock();
			return false;
		}
		for ( QList< iGetWidget * >::iterator
				itrActualElement = liElements.begin();
				itrActualElement != liElements.end(); itrActualElement++ ) {
			
			const string strElementType = (*itrActualElement)->getName();
			if ( ( strElementType != "cFibScalar" ) &&
					( strElementType != "cFibVectorCreator" ) &&
					( strElementType != "cFibInputVariable" ) ){
				//can't adapt vector element -> can't adapt Fib vector
				mutexFibVectorHandler.unlock();
				return false;
			}
		}
		//adapt Fib vector
		unsignedIntFib uiActualElement = 1;
		for ( QList< iGetWidget * >::iterator
				itrActualElement = liElements.begin();
				itrActualElement != liElements.end();
				itrActualElement++, uiActualElement++ ) {
			
			if ( (*itrActualElement)->getName() == "cFibScalar" ){
				//change to value
				pFibVector->setValue( uiActualElement,
					static_cast<cFibScalar*>(*itrActualElement)->getValue() );
				
			}else{/* if ( ( (*itrActualElement)->getName() == "cFibVectorCreator" ) ||
					( (*itrActualElement)->getName() == "cFibInputVariable" ) )*/
				//change to variable
				pFibVector->setVariable( uiActualElement,
					static_cast<cFibVariableCreator*>(*itrActualElement)->getFibVariable() );
			}
		}
	}
	//unregister this as element change listener at old elements
	while ( ! liElements.empty() ) {
		
		removeElementFromVector( liElements.front() );
	}
	//set the new elements
	liElements = liInElements;
	
	//register this as element change listener at new elements
	for ( QList< iGetWidget * >::iterator
			itrActualElement = liElements.begin();
			itrActualElement != liElements.end(); itrActualElement++ ) {
		
		registerForElement( *itrActualElement );
	}
	mutexFibVectorHandler.unlock();
	//send all elements replaced
	const eFibVectorChangedEvent fibVectorChangedEvent(
		this, eFibVectorChangedEvent::REPLACE );
	sendFibVectorChange( &fibVectorChangedEvent );
	
	return true;
}


/**
 * @see setFibElement()
 * @return a pointer to the Fib element, which the vector of this
 * 	object represents or NULL if non was given
 * 	@see pFibElement
 */
cFibElement * cFibVectorCreator::getFibElement() {
	
	return pFibElement;
}


/**
 * @see setFibElement()
 * @return a const pointer to the Fib element, which the vector of this
 * 	object represents or NULL if non was given
 * 	@see pFibElement
 */
const cFibElement * cFibVectorCreator::getFibElement() const{
	
	return pFibElement;
}


/**
 * This method sets the Fib element, which the vector of this object
 * represents.
 *
 * @see pFibElement
 * @see getFibElement()
 * @param pInFibElement a pointer to the Fib element, which the vector
 * 	of this object represents or NULL if non should be stored
 */
void cFibVectorCreator::setFibElement( cFibElement * pInFibElement ) {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::setFibElement( pInFibElement="<<pInFibElement<<" ) called"<<endl<<flush);
	mutexFibVectorHandler.lock();
	if ( pFibElement != pInFibElement ) {
		//Fib element changed
		pFibElement = pInFibElement;
		mutexFibVectorHandler.unlock();
		
		//send Fib element was changed
		const eFibVectorChangedEvent fibVectorChangedEvent(
			this, eFibVectorChangedEvent::FIB_ELEMENT );
		sendFibVectorChange( &fibVectorChangedEvent );
	}else{//nothing changed
		mutexFibVectorHandler.unlock();
	}
}


/**
 * @see setFibVector()
 * @return a pointer to the Fib vector, which this vector
 * 	of this object represents or NULL if non was given
 * 	@see pFibVector
 */
fib::cFibVector * cFibVectorCreator::getFibVector() {
	
	return pFibVector;
}

/**
 * @see setFibVector()
 * @return a const pointer to the Fib vector, which this vector
 * 	of this object represents or NULL if non was given
 * 	@see pFibVector
 */
const fib::cFibVector * cFibVectorCreator::getFibVector() const{
	
	return pFibVector;
}


/**
 * This method sets the Fib vector, which the vector of this object
 * represents.
 *
 * @see pFibVector
 * @see getFibElement()
 * @param pInFibVector a pointer to the Fib vector, which this vector (of
 * 	this object) represents or NULL if non should be stored
 */
void cFibVectorCreator::setFibVector( fib::cFibVector * pInFibVector ) {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::setFibVector( pInFibVector="<<pInFibVector<<" ) called"<<endl<<flush);
	mutexFibVectorHandler.lock();
	if ( pFibVector != pInFibVector ) {
		//Fib vector changed
		pFibVector = pInFibVector;
		mutexFibVectorHandler.unlock();
		
		//send Fib vector was changed
		const eFibVectorChangedEvent fibVectorChangedEvent(
			this, eFibVectorChangedEvent::FIB_VECTOR );
		sendFibVectorChange( &fibVectorChangedEvent );
	}else{//nothing changed
		mutexFibVectorHandler.unlock();
	}
	
}


/**
 * This method assigns the value of the vector elements to the
 * Fib elements. ( pScalar->assignValues() )
 * Call this function before evaluing the Fib element for the vector.
 *
 * @see cFibScalar::assignValues()
 * @see cFibScalar::getValue()
 * @see cFibScalar::setValue()
 */
void cFibVectorCreator::assignValues() {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::assignValues() called"<<endl<<flush);
	mutexFibVectorHandler.lock();
	//call assign value for all elements in the vector
	iGetWidget * pActualElement;
	if ( pFibVector ) {
		unsignedIntFib uiActualElement = 1;
		bool bVectorChanged = false;
		for ( QList< iGetWidget * >::iterator itrElement = liElements.begin();
				itrElement != liElements.end();
				itrElement++, uiActualElement++ ) {
			
			pActualElement = (*itrElement);
			if ( pActualElement ) {
				
				if ( pActualElement->getName() == "cFibInputVariable" ) {
					//vector element is a input variable -> assign its value
					(dynamic_cast<cFibInputVariable*>(pActualElement))->assignValue();
					if ( ! pFibVector->isVariable( uiActualElement ) ) {
						//Warning: in Fib vector a value but in this vector a variable
						pFibVector->setValue( uiActualElement,
							(static_cast<cFibScalar*>(pActualElement))->getValue() );
						bVectorChanged = true;
					}
				}else if ( pActualElement->getName() == "cFibScalar" ) {
					//vector element is a scalar / value -> set value in Fib vector
					const doubleFib dValueToSet =
						(static_cast<cFibScalar*>(pActualElement))->getValue();
					if ( dValueToSet != pFibVector->getValue( uiActualElement ) ) {
						pFibVector->setValue( uiActualElement, dValueToSet );
						bVectorChanged = true;
					}
				}
			}
		}
		mutexFibVectorHandler.unlock();
		if ( bVectorChanged && ( pFibElement != NULL ) ) {
			//send node changed event
			cFibNode * pChangedNode = cFibNodeHandler::getInstance()->
				getContainingNodeForFibObject( pFibElement );
			DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::assignValues() send node changed event to node "<<pChangedNode<<endl<<flush);
			//TODO give eFibNodeChangedEvent
			if ( pChangedNode ){
				pChangedNode->fibObjectChanged();
			}
		}
		
	}else{//no Fib vector for this vector exists
		for ( QList< iGetWidget * >::iterator itrElement = liElements.begin();
				itrElement != liElements.end(); itrElement++ ) {
			
			pActualElement = (*itrElement);
			if ( pActualElement ) {
				
				if ( pActualElement->getName() == "cFibInputVariable" ) {
					//vector element is a input variable -> assign its value
					(dynamic_cast<cFibInputVariable*>(pActualElement))->assignValue();
				}
			}
		}
		mutexFibVectorHandler.unlock();
	}
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::assignValues() done"<<endl<<flush);
}


/**
 * Event method
 * It will be called every time a scalar (cFibScalar),  at which this
 * object is registered, was changed.
 *
 * @param pFibScalarEvent a pointer to the event with the information of
 * 	the change of the Fib scalar
 */
void cFibVectorCreator::fibScalarChangedEvent(
		const eFibScalarChangedEvent * pFibScalarEvent ) {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::fibScalarChangedEvent( pFibScalarEvent="<<pFibScalarEvent<<") called"<<endl<<flush);
	if ( pFibScalarEvent == NULL ) {
		//no event given
		return;
	}
	if ( pFibScalarEvent->bScalarDeleted ) {
		//remove deleted scalar
		mutexFibVectorHandler.lock();
		list< int > liReplacedElements;
		bool bVectorChanged = false;
		while ( true ) {
			const int iFoundElement =
				liElements.indexOf( const_cast< cFibScalar* >(
					pFibScalarEvent->pScalarChanged) );
			if ( iFoundElement < 0 ) {
				//element not found -> done replacing
				break;
			}//else element found -> replace it
			const int uiElementNumber = iFoundElement + 1;
			liReplacedElements.push_back( uiElementNumber );
			liElements.replace( iFoundElement , new cFibScalar(
				0.0, QObject::tr("Number ") + QString::number( uiElementNumber ) ) );
			//adapt Fib vector
			if ( ( pFibVector != NULL ) &&
					( pFibVector->isVariable( uiElementNumber ) ) ) {
				//replace variable with value 0
				pFibVector->setValue( uiElementNumber, 0.0 );
				bVectorChanged = true;
			}
		}
		mutexFibVectorHandler.unlock();
		if ( bVectorChanged && ( pFibElement != NULL ) ) {
			//send node changed event
			cFibNode * pChangedNode = cFibNodeHandler::getInstance()->
				getContainingNodeForFibObject( pFibElement );
			//TODO give eFibNodeChangedEvent
			pChangedNode->fibObjectChanged();
		}
		
		//send Fib vector element changed/replaced
		for ( list< int >::const_iterator itrElement = liReplacedElements.begin();
				itrElement != liReplacedElements.end(); itrElement++ ) {
			
			const eFibVectorChangedEvent fibVectorChangedEvent(
				this, eFibVectorChangedEvent::REPLACE, *itrElement );
			sendFibVectorChange( &fibVectorChangedEvent );
		}
	}
	//redirect event to all variables change listeners
#ifdef TODO_WEG
	//send the scalar change event to all scalar change listeners
	sendScalarChange( pFibScalarEvent );
#endif //TODO_WEG
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::fibScalarChangedEvent( pFibScalarEvent="<<pFibScalarEvent<<") done"<<endl<<flush);
}


/**
 * Event method
 * It will be called every time a scalar value (cFibScalar), at which
 * this object is registered, was changed.
 *
 * @see cFibScalar::dValue
 * @param pFibScalar a pointer to the changed Fib scalar
 */
void cFibVectorCreator::fibScalarValueChangedEvent(
		const cFibScalar * pFibScalar ) {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::fibScalarValueChangedEvent( pFibScalar="<<pFibScalar<<") called"<<endl<<flush);
	if ( pFibScalar == NULL ) {
		//no variable given
		return;
	}
	//TODO: set the vector value to the new value of the scalar
	assignValues();
	
	//redirect event to all scalar value change listeners
#ifdef TODO_WEG
	//send the scalar value change event to all scalar value change listeners
	sendScalarValueChange( pFibScalar );
#endif //TODO_WEG
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::fibScalarValueChangedEvent( pFibScalar="<<pFibScalar<<") done"<<endl<<flush);
}


/**
 * Event method
 * It will be called every time a variable (cFibVariableCreator),
 * at which this object is registered, was changed.
 *
 * @param pFibVariableChangedEvent a pointer to the event with the
 * 	information of the change of the Fib creator variable
 */
void cFibVectorCreator::changedEvent(
		const eFibVariableCreatorChangedEvent * pFibVariableChangedEvent ) {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::changedEvent( pFibVariableChangedEvent="<<pFibVariableChangedEvent<<") called"<<endl<<flush);
	if ( pFibVariableChangedEvent == NULL ) {
		//no event given
		return;
	}
	if ( pFibVariableChangedEvent->isDeleted() ) {
		//remove deleted variable
		mutexFibVectorHandler.lock();
		cFibVariableCreator * pElement = const_cast<cFibVariableCreator*>(
				pFibVariableChangedEvent->getObject() );
		
		int uiLastFoundIndex = 0;
		list< int > liFoundIndex;
		while ( true ) {
			uiLastFoundIndex = liElements.indexOf( pElement , uiLastFoundIndex );
			if ( uiLastFoundIndex < 0 ) {
				//element not found -> stop search
				break;
			}//else element found -> add index to found index and search for next
			liFoundIndex.push_back( uiLastFoundIndex );
		}
		if ( liFoundIndex.empty() ) {
			//no such element to remove
			mutexFibVectorHandler.unlock();
			return;
		}
		
		//remove element
		removeElementFromVector( pElement );
		
		mutexFibVectorHandler.unlock();
		//send information about removed elements
		for ( list< int >::iterator itrRemovedElement = liFoundIndex.begin();
				itrRemovedElement != liFoundIndex.end(); itrRemovedElement++ ) {
			
			const eFibVectorChangedEvent fibVectorChangedEvent(
				this, eFibVectorChangedEvent::REMOVE,
				(*itrRemovedElement + 1 ) );
			sendFibVectorChange( &fibVectorChangedEvent );
		}
	}
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::changedEvent( pFibVariableChangedEvent="<<pFibVariableChangedEvent<<") done"<<endl<<flush);
}


#ifdef TODO_WEG
/**
 * With this function you can register a listeners for changes for any
 * of the contained scalars.
 *
 * @see cFibScalar::registerScalarChangeListener()
 * @see unregisterScalarChangeListener()
 * @see setScalarChangeListener
 * @see sendScalarChange()
 * @param pScalarListener a pointer to the listener for changes
 * @return true if the listener was registered, else false
 */
bool cFibVectorCreator::registerScalarChangeListener(
		lScalarChanged * pScalarListener ) {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::registerScalarChangeListener( pScalarListener="<<pScalarListener<<") called"<<endl<<flush);
	if ( pScalarListener == NULL ) {
		//nothing to register
		return false;
	}
	mutexScalarChangeListener.lock();
	const pair< set< lScalarChanged * >::iterator, bool > paListenerInserted =
		setScalarChangeListener.insert( pScalarListener );
	mutexScalarChangeListener.unlock();
	return paListenerInserted.second;
}



/**
 * With this function you can unregister a listeners for changes for any
 * of the contained scalars.
 *
 * @see registerScalarChangeListener()
 * @see setScalarChangeListener
 * @see sendScalarChange()
 * @param pScalarListener a pointer to the listener for changes
 * @return true if the listener was registered, else false
 */
bool cFibVectorCreator::unregisterScalarChangeListener(
		lScalarChanged * pScalarListener ) {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::unregisterScalarChangeListener( pScalarListener="<<pScalarListener<<") called"<<endl<<flush);
	mutexScalarChangeListener.lock();
	const bool bUnregistered =
		( 0 < setScalarChangeListener.erase( pScalarListener ) );
	mutexScalarChangeListener.unlock();
	return bUnregistered;
}


/**
 * This method sents a scalar changed event to all scalar change
 * listeners of this object.
 *
 * @see setScalarChangeListener
 * @see registerScalarChangeListener()
 * @see unregisterScalarChangeListener()
 * @param pFibScalarChangedEvent the change event to send
 */
void cFibVectorCreator::sendScalarChange(
		const eFibScalarChangedEvent * pFibScalarChangedEvent ) {
	
	mutexScalarChangeListener.lock();
	for ( set< lScalarChanged * >::iterator
			itrListenerScalarChanged = setScalarChangeListener.begin();
			itrListenerScalarChanged != setScalarChangeListener.end();
			itrListenerScalarChanged++ ) {
		
		(*itrListenerScalarChanged)->fibScalarChangedEvent(
				pFibScalarChangedEvent );
	}
	mutexScalarChangeListener.unlock();
}


/**
 * With this function you can register a listeners for value changes for
 * any of the contained scalars.
 *
 * @see unregisterScalarValueChangeListener()
 * @see setScalarValueChangeListener
 * @see sendScalarValueChange()
 * @param pScalarValueListener a pointer to the listener for value changes
 * @return true if the listener was registered, else false
 */
bool cFibVectorCreator::registerScalarValueChangeListener(
		lScalarValueChanged * pScalarValueListener ) {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::registerScalarValueChangeListener( pScalarValueListener="<<pScalarValueListener<<") called"<<endl<<flush);
	if ( pScalarValueListener == NULL ) {
		//nothing to register
		return false;
	}
	mutexScalarValueChangeListener.lock();
	const pair< set< lScalarValueChanged * >::iterator, bool > paListenerInserted =
		setScalarValueChangeListener.insert( pScalarValueListener );
	mutexScalarValueChangeListener.unlock();
	return paListenerInserted.second;
}


/**
 * With this function you can unregister a listeners for value changes
 * for any of the contained scalars.
 *
 * @see registerScalarValueChangeListener()
 * @see setScalarValueChangeListener
 * @see sendScalarValueChange()
 * @param pScalarValueListener a pointer to the listener for value changes
 * @return true if the listener was registered, else false
 */
bool cFibVectorCreator::unregisterScalarValueChangeListener(
		lScalarValueChanged * pScalarValueListener ) {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::unregisterScalarValueChangeListener( pScalarValueListener="<<pScalarValueListener<<") called"<<endl<<flush);
	mutexScalarValueChangeListener.lock();
	const bool bUnregistered = ( 0 < setScalarValueChangeListener.erase(
		pScalarValueListener ) );
	mutexScalarValueChangeListener.unlock();
	return bUnregistered;
}


/**
 * This method sents a scalar value changed event to all scalar value
 * change listeners of this object.
 *
 * @see setScalarValueChangeListener
 * @see registerScalarValueChangeListener()
 * @see unregisterScalarValueChangeListener()
 */
void cFibVectorCreator::sendScalarValueChange( const cFibScalar * pFibScalar ) {
	
	mutexScalarValueChangeListener.lock();
	for ( set< lScalarValueChanged * >::iterator
			itrListenerScalarValueChanged = setScalarValueChangeListener.begin();
			itrListenerScalarValueChanged != setScalarValueChangeListener.end();
			itrListenerScalarValueChanged++ ) {
		
		(*itrListenerScalarValueChanged)->fibScalarValueChangedEvent(
			pFibScalar );
	}
	mutexScalarValueChangeListener.unlock();
}

#endif //TODO_WEG


/**
 * With this function you can register a listeners for changes in this
 * Fib vector.
 *
 * @see unregisterFibVectorChangeListener()
 * @see setFibVectorChangeListener
 * @see sendFibVectorChange()
 * @param pFibVectorListener a pointer to the listener for changes
 * @return true if the listener was registered, else false
 */
bool cFibVectorCreator::registerFibVectorChangeListener(
		lFibVectorChanged * pFibVectorListener ) {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::registerScalarValueChangeListener( pFibVectorListener="<<pFibVectorListener<<") called"<<endl<<flush);
	if ( pFibVectorListener == NULL ) {
		//nothing to register
		return false;
	}
	mutexFibVectorChangeListener.lock();
	const pair< set< lFibVectorChanged * >::iterator, bool > paListenerInserted =
		setFibVectorChangeListener.insert( pFibVectorListener );
	mutexFibVectorChangeListener.unlock();
	return paListenerInserted.second;
}


/**
 * With this function you can unregister a listeners for changes in this
 * Fib vector.
 *
 * @see registerFibVectorChangeListener()
 * @see setFibVectorChangeListener
 * @see sendFibVectorChange()
 * @param pFibVectorListener a pointer to the listener for changes
 * @return true if the listener was registered, else false
 */
bool cFibVectorCreator::unregisterFibVectorChangeListener(
		lFibVectorChanged * pFibVectorListener ) {
	
	DEBUG_OUT_L2(<<"cFibVectorCreator("<<this<<")::unregisterScalarValueChangeListener( pFibVectorListener="<<pFibVectorListener<<") called"<<endl<<flush);
	mutexFibVectorChangeListener.lock();
	const bool bUnregistered = ( 0 < setFibVectorChangeListener.erase(
		pFibVectorListener ) );
	mutexFibVectorChangeListener.unlock();
	return bUnregistered;
}


/**
 * This method sents a Fib vector changed event to all Fib vector change
 * listeners of this object.
 *
 * @see setFibVectorChangeListener
 * @see registerFibVectorChangeListener()
 * @see unregisterFibVectorChangeListener()
 * @param pFibVectorChangedEvent the change event to send
 */
void cFibVectorCreator::sendFibVectorChange(
		const eFibVectorChangedEvent * pFibVectorChangedEvent ) {
	
	DEBUG_OUT_L2(<<"cFibInputVariables("<<this<<")::sendFibVectorChange( pFibVectorChangedEvent="<<pFibVectorChangedEvent<<") called"<<endl<<flush);
	mutexFibVectorChangeListener.lock();
	for ( set< lFibVectorChanged * >::iterator
			itrListenerVectorChanged = setFibVectorChangeListener.begin();
			itrListenerVectorChanged != setFibVectorChangeListener.end();
			itrListenerVectorChanged++ ) {
		
		(*itrListenerVectorChanged)->fibVectorChangedEvent(
				pFibVectorChangedEvent );
	}
	mutexFibVectorChangeListener.unlock();
}



/**
 * This method will create a widget, which displays this object.
 * ATTENTION: You have to care that the returned widget is deleted.
 *
 * @param pParent a pointer the parent of this new Fib vector widget
 * @return a pointer to the created widget, or NULL if non could be created
 */
QWidget * cFibVectorCreator::getWidget( QWidget * pParent ) {
	
	DEBUG_OUT_L2(<<"cFibInputVariables("<<this<<")::getWidget( pParent="<<pParent<<") called"<<endl<<flush);
	return new cWidgetFibVector( this, pParent );
}


/**
 * This method returns the name for the uiPosition'th vector element.
 *
 * @param uiPosition the position where of the element for which to return
 * 	the name (counting starts with 1)
 * @return the name for the uiPosition'th vector element
 */
QString cFibVectorCreator::getVectorElementName( const unsigned int uiPosition ) const {
	
	QString vecElementName;
	const cTypeElement * pVectorType = ( pFibVector == NULL ) ? NULL :
		pFibVector->getElementType();
	
	if ( pFibElement != NULL ) {
		if ( pFibElement->getType() == 'o' ) {
			//try to get input variable name from optional part
			cRoot * pRootExternalObject = pFibElement->getAccessibleRootObject(
				static_cast<cExtObject*>( pFibElement)->getIdentifier() );
			
			if ( pRootExternalObject ) {
				const cOptionalPart * pOptionalPart =
					pRootExternalObject->getOptionalPart();
				if ( pOptionalPart != NULL ) {
					char szKeyBuffer[ 64 ];
					sprintf( szKeyBuffer, "inVar%u::name", uiPosition );
					//try to find a "inVarX::name" entry
					const list< pair<string,string> > liFoundNameEntries =
						pOptionalPart->getEntries( string( szKeyBuffer ) );
					
					if ( ! liFoundNameEntries.empty() ) {
						//a "inVarX::name" was found -> set the variable name to it
						vecElementName = QString(
							liFoundNameEntries.front().second.c_str() );
					}//else no entry found
				}//end if optional part exists
			}//end if external object exists
		}else if ( pFibElement->getType() == 's' ) {
			//try to get output variable name from optional part
			cRoot * pSuperiorRoot = pFibElement->getSuperiorRootElement();
			if ( pSuperiorRoot ) {
				const cOptionalPart * pOptionalPart =
					pSuperiorRoot->getOptionalPart();
				
				const unsigned int uiNumberSubobject =
					static_cast< const cExtSubobject * >(
						pFibElement)->getNumberSubobject();
				
				if ( pOptionalPart != NULL ) {
					char szKeyBuffer[ 64 ];
					sprintf( szKeyBuffer, "subObj%u::outVar%u::name",
						uiNumberSubobject, uiPosition );
					//try to find a "inVarX::name" entry
					const list< pair<string,string> > liFoundNameEntries =
						pOptionalPart->getEntries( string( szKeyBuffer ) );
					
					if ( ! liFoundNameEntries.empty() ) {
						/*a "subObjX::outVarX::name" was found
						 *-> set the variable name to it*/
						vecElementName = QString(
							liFoundNameEntries.front().second.c_str() );
					}//else no entry found
				}//end if optional part exists
			}//end if external object exists
			
		}
	}//end if defining Fib element exists
	if ( vecElementName.isEmpty() && ( pVectorType != NULL ) ) {
		//no vector element name found yet -> use domain element name (eg. red)
		switch ( pVectorType->getType() ) {
			case 1:{//cTypeDimension
				vecElementName = QObject::tr( "dimension " ) +
					QString::number( uiPosition );
			};break;
			case 2:{//cTypeUnderArea
				if ( uiPosition == 1 ) {
					vecElementName = QObject::tr( "lower border" );
				}else{
					vecElementName = QObject::tr( "upper border" );
				}
			};break;
			case 3:{//cTypeUnderFunction
				vecElementName = QObject::tr( "function" );
			};break;
			case 5:{//cTypeInVar
				vecElementName = QObject::tr( "input variable " ) +
					QString::number( uiPosition );
			};break;
			case 6:{//cTypeProperty
				const cTypeProperty * pTypeProperty =
					static_cast<const cTypeProperty*>( pVectorType );
				switch ( pTypeProperty->getNumberOfProperty() ) {
					case cTypeProperty::COLOR_RGB:{
						switch ( uiPosition ) {
							case 1:{
								vecElementName = QObject::tr( "red" );
							}break;
							case 2:{
								vecElementName = QObject::tr( "green" );
							}break;
							case 3:{
								vecElementName = QObject::tr( "blue" );
							}break;
						}
					}break;
					case cTypeProperty::COLOR_GRAYSCALE:{
						vecElementName = QObject::tr( "luminance" );
					}break;
					case cTypeProperty::LAYER:{
						vecElementName = QObject::tr( "layer" );
					}break;
					case cTypeProperty::TRANSPARENCY:{
						vecElementName = QObject::tr( "opaquely" );
					}break;
					
					case cTypeProperty::KELVIN:{
						vecElementName = QObject::tr( "kelvin" );
					}break;
					//TODO
					
				};//end switch property type
				if ( vecElementName.isEmpty() ) {
					//default (nothing found) -> no name
					vecElementName = QString::number( uiPosition );
				}
			};break;
			case 10:{//cTypeVariable
				vecElementName = QObject::tr( "variable " ) +
					QString::number( uiPosition );
			};break;
			case 11:{//cTypeComments
				vecElementName = QObject::tr( "comment " ) +
					QString::number( uiPosition );
			};break;
			case 12://cTypeExtObject
			case 13:{//cTypeExtSubobject
				vecElementName = QObject::tr( "output " ) +
					QString::number( uiPosition );
			};break;
			case 16:{//cTypeExtObjectInput
				vecElementName = QObject::tr( "input " ) +
					QString::number( uiPosition );
			};break;
			
			//TODO more vector types
			default:{
				vecElementName = QString::number( uiPosition );
			}
		};//end switch vector type
	}
	return vecElementName;
}




/**
 * This method register this object at the given element.
 * Note: It dosn't use a mutex.
 *
 * @param pElement a pointer to the object where to register this object
 */
void cFibVectorCreator::registerForElement( iGetWidget * pElement ) {
	
	DEBUG_OUT_L2(<<"cFibInputVariables("<<this<<")::registerForElement( pElement="<<pElement<<") called"<<endl<<flush);
	if ( pElement ) {
		const std::string szElementType = (pElement)->getName();
		if ( szElementType == "cFibScalar" ) {
			
			static_cast<cFibScalar*>((pElement))->
				registerScalarChangeListener( this );
			static_cast<cFibScalar*>((pElement))->
				registerScalarValueChangeListener( this );
			
		}else if ( szElementType == "cFibVariableCreator" ) {
			
			static_cast<cFibVariableCreator*>((pElement))->
				registerChangeListener( this );
			
		}else if ( szElementType == "cFibInputVariable" ) {
			cFibInputVariable * pFibInputVariable =
				dynamic_cast<cFibInputVariable*>(pElement);
			pFibInputVariable->registerScalarValueChangeListener( this );
			pFibInputVariable->registerScalarValueChangeListener( this );
		}//else unknown type -> cnat register
	}
}

/**
 * This method removes the given element from this vector.
 * Note: It dosn't use a mutex or send signals.
 *
 * @param pElement a pointer to the object to remove from this object
 */
void cFibVectorCreator::removeElementFromVector( iGetWidget * pElement ) {
	
	DEBUG_OUT_L2(<<"cFibInputVariables("<<this<<")::removeElementFromVector( pElement="<<pElement<<") called"<<endl<<flush);
	if ( pElement ) {
		
		const std::string szElementType = pElement->getName();
		
		if ( szElementType == "cFibScalar" ) {
			
			static_cast<cFibScalar*>((pElement))->
				unregisterScalarChangeListener( this );
			static_cast<cFibScalar*>((pElement))->
				unregisterScalarValueChangeListener( this );
			
			//delete all element elements
			delete static_cast<cFibScalar*>(pElement);
			
		}else if ( szElementType == "cFibVariableCreator" ) {
			
			static_cast<cFibVariableCreator*>((pElement))->
				unregisterChangeListener( this );
			
		}else if ( szElementType == "cFibInputVariable" ) {
			
			cFibInputVariable * pFibInputVariable =
				dynamic_cast<cFibInputVariable*>(pElement);
			pFibInputVariable->unregisterScalarValueChangeListener( this );
			pFibInputVariable->unregisterScalarValueChangeListener( this );
		}//else unknown type -> cnat ununregister
		
		liElements.removeAll( pElement );
	}
}


