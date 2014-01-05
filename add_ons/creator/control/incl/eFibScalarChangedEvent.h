/**
 * @file eFibScalarChangedEvent
 * file name: eFibScalarChangedEvent.h
 * @author Betti Oesterholz
 * @date 19.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a event for input variables changes.
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
 * This file implements a event for input variables changes.
 * If a input variable changes, the input variable object (cFibScalar)
 * for it will send an event of this type to all registered listeners of
 * the type lScalarChanged .
 * @see cFibScalar
 * @see lScalarChanged
 */
/*
History:
19.08.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__E_FIB_SCALAR_CHANGED_EVENT_H__
#define ___FIB__NCREATOR__E_FIB_SCALAR_CHANGED_EVENT_H__


#include "version.h"

#include <string>

#include <QObject>


namespace fib{

namespace nCreator{

//cyclic dependencies
class cFibScalar;

class eFibScalarChangedEvent{
public:
	
	/**
	 * A pointer to the input variable that was changed.
	 */
	const cFibScalar * pScalarChanged;
	
	/**
	 * If true the input variable was deleted.
	 */
	bool bScalarDeleted;
	
	
	/**
	 * constructor
	 *
	 * @param pInScalarChanged a pointer to the input variable that was changed
	 * 	@see pScalarChanged
	 */
	eFibScalarChangedEvent( const cFibScalar * pInScalarChanged );
	
	/**
	 * @return the name of this class "eFibScalarChangedEvent"
	 */
	std::string getName() const;
	
};//end class eFibScalarChangedEvent

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__E_FIB_SCALAR_CHANGED_EVENT_H__





