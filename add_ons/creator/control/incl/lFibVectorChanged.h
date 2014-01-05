
//TODO check

/**
 * @file lFibVectorChanged
 * file name: lFibVectorChanged.h
 * @author Betti Oesterholz
 * @date 31.11.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a listener interface for listening for Fib vectors
 * changes.
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
 * This file specifies a listener interface for listening for Fib vectors
 * changes. If a Fib vector changes, the Fib vector object
 * (cFibVector) for it will send a event to all registered listeners
 * of this type.
 * @pattern listener
 * @see cFibVector
 * @see eFibVectorChangedEvent
 */
/*
History:
31.11.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__L_FIB_VECTOR_CHANGED_H__
#define ___FIB__NCREATOR__L_FIB_VECTOR_CHANGED_H__


#include "version.h"

#include <string>


namespace fib{

namespace nCreator{

//forward declarations
class eFibVectorChangedEvent;

class lFibVectorChanged{
public:
	
	/**
	 * Event method
	 * It will be called every time a Fib vector (cFibVector), at which this
	 * object is registered, was changed.
	 *
	 * @param pFibVectorEvent a pointer to the event with the information of
	 * 	the change of the Fib vector
	 */
	virtual void fibVectorChangedEvent(
		const eFibVectorChangedEvent * pFibVectorEvent ) = 0;
	
	/**
	 * @return the name of this class
	 */
	virtual std::string getName() const = 0;
	
};//end class lFibVectorChanged

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__L_FIB_VECTOR_CHANGED_H__





