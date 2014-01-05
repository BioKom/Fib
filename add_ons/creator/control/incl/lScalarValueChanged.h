/**
 * @file lScalarValueChanged
 * file name: lScalarValueChanged.h
 * @author Betti Oesterholz
 * @date 21.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a listener interface for listening for scalars value
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
 * This file specifies a listener interface for listening for scalars value
 * changes. If a scalar value changes, the scalar object (cFibScalar) for
 * it will send an event to all registered listeners of this type.
 * @pattern listener
 * @see cFibScalar
 */
/*
History:
21.08.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__L_SCALAR_VALUE_CHANGED_H__
#define ___FIB__NCREATOR__L_SCALAR_VALUE_CHANGED_H__


#include "version.h"

#include <string>


namespace fib{

namespace nCreator{

//forward declarations
class cFibScalar;

class lScalarValueChanged{
public:
	
	/**
	 * Event method
	 * It will be called every time a scalar value (cFibScalar)
	 * of a scalar, at which this object is registered, was changed.
	 *
	 * @see cFibScalar::dValue
	 * @param pFibScalar a pointer to the changed Fib scalar
	 */
	virtual void fibScalarValueChangedEvent(
		const cFibScalar * pFibScalar ) = 0;
	
	/**
	 * @return the name of this class
	 */
	virtual std::string getName() const = 0;
	
};//end class lScalarValueChanged

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__L_SCALAR_VALUE_CHANGED_H__




