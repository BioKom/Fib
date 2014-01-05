/**
 * @file eFibScalarChangedEvent
 * file name: eFibScalarChangedEvent.h
 * @author Betti Oesterholz
 * @date 19.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a event for scalar changes.
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
 * This file implements a event for scalar changes.
 * If a scalar changes, the scalar object (cFibScalar)
 * for it will send an event of this type to all registered listeners of
 * the type lScalarChanged .
 * @see cFibScalar
 * @see lScalarChanged
 */
/*
History:
19.08.2013  Oesterholz  created
*/


#include "eFibScalarChangedEvent.h"

#include "cFibScalar.h"


using namespace std;
using namespace fib::nCreator;



/**
 * constructor
 *
 * @param pInScalarChanged a pointer to the scalar that was changed
 * 	@see pScalarChanged
 */
eFibScalarChangedEvent::eFibScalarChangedEvent(
		const cFibScalar * pInScalarChanged ):
		pScalarChanged( pInScalarChanged ),
		bScalarDeleted( false ){
	//nothing to do
}


/**
 * @return the name of this class "eFibScalarChangedEvent"
 */
string eFibScalarChangedEvent::getName() const{
	
	return "eFibScalarChangedEvent";
}






