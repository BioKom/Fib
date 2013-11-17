/**
 * @file eFibInputVariableChangedEvent
 * file name: eFibInputVariableChangedEvent.h
 * @author Betti Oesterholz
 * @date 19.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a event for input variables changes.
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
 * If a input variable changes, the input variable object (cFibInputVariable)
 * for it will send an event of this type to all registered listeners of
 * the type lInputVariableChanged .
 * @see cFibInputVariable
 * @see lInputVariableChanged
 */
/*
History:
19.08.2013  Oesterholz  created
*/


#include "eFibInputVariableChangedEvent.h"

#include "cFibInputVariable.h"


using namespace std;
using namespace fib::nCreator;



/**
 * constructor
 *
 * @param pInInputVariableChanged a pointer to the input variable that was changed
 * 	@see pInputVariableChanged
 */
eFibInputVariableChangedEvent::eFibInputVariableChangedEvent(
		const cFibInputVariable * pInInputVariableChanged ):
		pInputVariableChanged( pInInputVariableChanged ),
		bInputVariableDeleted( false ){
	//nothing to do
}


/**
 * @return the name of this class "eFibInputVariableChangedEvent"
 */
string eFibInputVariableChangedEvent::getName() const{
	
	return "eFibInputVariableChangedEvent";
}






