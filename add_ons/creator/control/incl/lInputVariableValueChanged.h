/**
 * @file lInputVariableValueChanged
 * file name: lInputVariableValueChanged.h
 * @author Betti Oesterholz
 * @date 21.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a listener interface for listening for input
 * variables value changes.
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
 * This file specifies a listener interface for listening for input
 * variables value changes. If a input variable value changes, the input
 * variable object (cFibInputVariable) for it will send an event to all
 * registered listeners of this type.
 * @see cFibInputVariable
 */
/*
History:
21.08.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__L_INPUT_VARIABLE_VALUE_CHANGED_H__
#define ___FIB__NCREATOR__L_INPUT_VARIABLE_VALUE_CHANGED_H__


#include "version.h"

#include <string>


namespace fib{

namespace nCreator{

//forward declarations
class cFibInputVariable;

class lInputVariableValueChanged{
public:
	
	/**
	 * Event method
	 * It will be called every time a input variable value (cFibInputVariable)
	 * of a variable, at which this object is registered, was changed.
	 *
	 * @see cFibInputVariable::dValue
	 * @param pFibInputVariable a pointer to the changed Fib input variable
	 */
	virtual void fibInputVariableValueChangedEvent(
		const cFibInputVariable * pFibInputVariable ) = 0;
	
	/**
	 * @return the name of this class
	 */
	virtual std::string getName() const = 0;
	
};//end class lInputVariableValueChanged

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__L_INPUT_VARIABLE_VALUE_CHANGED_H__





