/**
 * @file eFibVectorChangedEvent
 * file name: eFibVectorChangedEvent.cpp
 * @author Betti Oesterholz
 * @date 30.11.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements an event for Fib vector changes.
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
 * This file implements an event for Fib vector changes.
 * If a Fib vector changes, the Fib vector object (cFibVectorCreator) for
 * it will send an event of this type to all registered listeners of the
 * type lFibVectorChanged .
 * @pattern event
 * @see cFibVectorCreator
 * @see lFibVectorChanged
 */
/*
History:
30.11.2013  Oesterholz  created
*/



#include "eFibVectorChangedEvent.h"

#include <string>

#include <QObject>

#include "cFibVectorCreator.h"


using namespace fib::nCreator;


/**
 * The standard constructor of this class.
 *
 * @param pInFibVectorChanged a pointer to the Fib vector
 * 	object that was changed
 * 	@see pFibVectorChanged
 * @param elementCangeType the type of the change
 * 	@see elementCangeType
 * @param uiInNumberOfElement the position of the changed scalar
 * 	(counting starts with 1, 0 = entire vector)
 * 	@see uiNumberOfElement
 */
eFibVectorChangedEvent::eFibVectorChangedEvent(
		const cFibVectorCreator * pInFibVectorChanged,
		const enumElementChange inElementCangeType,
		const unsigned int uiInNumberOfElement ):
		eObjectDeleted< cFibVectorCreator >( pInFibVectorChanged ),
		pFibVectorChanged( pInFibVectorChanged ),
		uiNumberOfElement( uiInNumberOfElement ),
		elementCangeType( inElementCangeType ) {
	//noting to do
}


/**
 * A parameter constructor of this class.
 *
 * @param pInFibVectorChanged a pointer to the Fib vector
 * 	object that was changed
 * 	@see pFibVectorChanged
 * @param bInFibVectorDeleted if true the Fib vector was
 * 	deleted, else this event dosn't mark that it was deleted
 * 	@see bFibVectorDeleted
 */
eFibVectorChangedEvent::eFibVectorChangedEvent(
		const cFibVectorCreator * pInFibVectorChanged,
		const bool bInFibVectorDeleted ):
		eObjectDeleted< cFibVectorCreator >( pInFibVectorChanged, bInFibVectorDeleted ),
		pFibVectorChanged( pInFibVectorChanged ),
		uiNumberOfElement( 0 ),
		elementCangeType( NONE ) {
	//noting to do
}



/**
 * @return the name of this class "eFibVectorChangedEvent"
 */
std::string eFibVectorChangedEvent::getName() const {
	
	return std::string( "eFibVectorChangedEvent" );
}


/**
 * @return a pointer to the Fib vector that was changed
 * 	@see pFibVectorChanged
 */
const cFibVectorCreator * eFibVectorChangedEvent::getFibVector() const {
	
	return pFibVectorChanged;
}


/**
 * This method sets the Fib vector for this event.
 *
 * @param pInFibVectorChanged a pointer to the Fib vector
 * 	object that was changed
 * 	@see pFibVectorChanged
 */
void eFibVectorChangedEvent::setFibVector(
		const cFibVectorCreator * pInFibVectorChanged ) {
	
	pFibVectorChanged = pInFibVectorChanged;
}


/**
 * This method sets what was changed in the vector.
 *
 * @param uiInNumberOfElement the position of the changed scalar
 * 	(counting starts with 1, 0 = entire vector)
 * 	@see uiNumberOfElement
 * @param inElementCangeType the type of the change
 * 	@see elementCangeType
 */
void eFibVectorChangedEvent::setElementChange(
		const unsigned int uiInNumberOfElement,
		const enumElementChange inElementCangeType ) {
	
	uiNumberOfElement = uiInNumberOfElement;
	elementCangeType  = inElementCangeType;
}


/**
 * @return the position of the changed scalar (counting starts with 1,
 * 	0 = entire vector)
 * 	@see uiNumberOfElement
 */
unsigned int eFibVectorChangedEvent::getNumberOfElementChanged() const {
	
	return uiNumberOfElement;
}


/**
 * @return the type of the change
 * 	@see elementCangeType
 */
eFibVectorChangedEvent::enumElementChange
		eFibVectorChangedEvent::getElementChangeType() const {
	
	return elementCangeType;
}








