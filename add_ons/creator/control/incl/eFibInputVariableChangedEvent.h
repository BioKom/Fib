
//TODO check

/**
 * @file eFibInputVariableChangedEvent
 * file name: eFibInputVariableChangedEvent.h
 * @author Betti Oesterholz
 * @date 19.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a event for for input variables changes.
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
 * This file specifies a event for for input variables changes.
 * If a input variable changes, the input variable object (cFibInputVariable)
 * for it will send a event of this type to all registered listeners of type.
 * @see cFibInputVariable
 * @see lInputVariableChanged
 */
/*
History:
19.08.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__E_FIB_INPUT_VARIABLE_CHANGED_EVENT_H__
#define ___FIB__NCREATOR__E_FIB_INPUT_VARIABLE_CHANGED_EVENT_H__


#include "version.h"

#include <string>

#include <QObject>


namespace fib{

namespace nCreator{

//cyclic dependencies
class cFibInputVariable;

class eFibInputVariableChangedEvent{
public:
	
	/**
	 * A pointer to the input variable that was changed.
	 */
	const cFibInputVariable * pInputVariableChanged;
	
	/**
	 * If true the input variable was deleted.
	 */
	bool bInputVariableDeleted;
	
	
	/**
	 * constructor
	 *
	 * @param pInInputVariableChanged a pointer to the input variable that was changed
	 * 	@see pInputVariableChanged
	 */
	eFibInputVariableChangedEvent( const cFibInputVariable * pInInputVariableChanged );
	
	/**
	 * @return the name of this class "eFibInputVariableChangedEvent"
	 */
	std::string getName() const;
	
};//end class eFibInputVariableChangedEvent

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__E_FIB_INPUT_VARIABLE_CHANGED_EVENT_H__





