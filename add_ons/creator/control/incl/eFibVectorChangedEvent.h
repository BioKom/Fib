
//TODO check

/**
 * @file eFibVectorChangedEvent
 * file name: eFibVectorChangedEvent.h
 * @author Betti Oesterholz
 * @date 30.11.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies an event for Fib vector changes.
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


#ifndef ___FIB__NCREATOR__E_FIB_VECTOR_CHANGED_EVENT_H__
#define ___FIB__NCREATOR__E_FIB_VECTOR_CHANGED_EVENT_H__


#include "version.h"

#include <string>

#include "eObjectDeleted.h"


namespace fib{

namespace nCreator{

//cyclic dependencies
class cFibVectorCreator;

class eFibVectorChangedEvent: public eObjectDeleted< cFibVectorCreator >{
public:
	
	/**
	 * An enum for the change type.
	 */
	enum enumElementChange{
		///nothing changed
		NONE,
		///element added
		ADD,
		///element removed
		REMOVE,
		///element replaced
		REPLACE,
		///name of the vector was changed
		NAME,
		///Fib element for vector was changed
		FIB_ELEMENT,
		///the Fib vector was changed
		FIB_VECTOR
	};
	
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
	explicit eFibVectorChangedEvent( const cFibVectorCreator * pInFibVectorChanged,
		const enumElementChange inElementCangeType,
		const unsigned int uiInNumberOfElement = 0 );

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
	explicit eFibVectorChangedEvent( const cFibVectorCreator * pInFibVectorChanged,
		const bool bInFibVectorDeleted );
	
	
	/**
	 * @return the name of this class "eFibVectorChangedEvent"
	 */
	virtual std::string getName() const;
	
	
	/**
	 * @return a pointer to the Fib vector that was changed
	 * 	@see pFibVectorChanged
	 */
	const cFibVectorCreator * getFibVector() const;
	
	/**
	 * This method sets the Fib vector for this event.
	 *
	 * @param pInFibVectorChanged a pointer to the Fib vector
	 * 	object that was changed
	 * 	@see pFibVectorChanged
	 */
	void setFibVector( const cFibVectorCreator * pInFibVectorChanged );
	
	/**
	 * This method sets what was changed in the vector.
	 *
	 * @param uiInNumberOfElement the position of the changed scalar
	 * 	(counting starts with 1)
	 * 	@see uiNumberOfElement
	 * @param elementCangeType the type of the change
	 * 	@see elementCangeType
	 */
	void setElementChange( const unsigned int uiInNumberOfElement,
		const enumElementChange inElementCangeType );
	
	/**
	 * @return the position of the changed scalar (counting starts with 1)
	 * 	@see uiNumberOfElement
	 */
	unsigned int getNumberOfElementChanged() const;
	
	/**
	 * @return the type of the change
	 * 	@see elementCangeType
	 */
	enumElementChange getElementChangeType() const;
	
protected:
	
	/**
	 * A pointer to the Fib vector that was changed.
	 */
	const cFibVectorCreator * pFibVectorChanged;
	
	/**
	 * The position of the changed scalar (counting starts with 1,
	 * 0 = entire vector).
	 * @see setElementChange()
	 * @see getNumberOfElementChanged()
	 * @see cFibVectorCreator::getScalar()
	 */
	unsigned int uiNumberOfElement;
	
	/**
	 * The type of the change.
	 * @see setElementChange()
	 * @see enumElementChange
	 * @see getElementChangeType()
	 */
	enumElementChange elementCangeType;
	
	
};//end class eFibVectorChangedEvent

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__E_FIB_VECTOR_CHANGED_EVENT_H__





