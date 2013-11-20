
//TODO check

/**
 * @file eFibObjectInfoChangedEvent
 * file name: eFibObjectInfoChangedEvent.cpp
 * @author Betti Oesterholz
 * @date 12.10.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements an event for Fib object info object changes.
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
 * This file implements an event for Fib object info object changes.
 * If a Fib object info object changes, the Fib object info object object
 * (cFibObjectInfo) for it will send an event of this type to all
 * registered listeners of the type lFibObjectInfoChanged .
 * @see cFibObjectInfo
 * @see lFibObjectInfoChanged
 */
/*
History:
12.10.2013  Oesterholz  created
*/



#include "eFibObjectInfoChangedEvent.h"

#include "cFibObjectInfo.h"


using namespace fib::nCreator;



/**
 * constructor
 *
 * @param pInFibObjectInfoChanged a pointer to the Fib object info
 * 	object that was changed
 * 	@see pFibObjectInfoChanged
 * @param bInFibObjectInfoDeleted if true the Fib object info object was
 * 	deleted, else this event dosn't mark that it was deleted
 * 	@see bFibObjectInfoDeleted
 */
eFibObjectInfoChangedEvent::eFibObjectInfoChangedEvent(
		const cFibObjectInfo * pInFibObjectInfoChanged,
		const bool bInFibObjectInfoDeleted ):
		pFibObjectInfoChanged( pInFibObjectInfoChanged ),
		bFibObjectInfoDeleted( bInFibObjectInfoDeleted ){
	//nothing to do
}


/**
 * @return the name of this class "eFibObjectInfoChangedEvent"
 */
std::string eFibObjectInfoChangedEvent::getName() const{
	
	return ((std::string)("eFibObjectInfoChangedEvent"));
}


/**
 * @return a pointer to the Fib object info object that was changed
 * 	@see pFibObjectInfoChanged
 */
const cFibObjectInfo * eFibObjectInfoChangedEvent::getFibObjectInfo() const{
	
	return pFibObjectInfoChanged;
}


/**
 * This method sets the Fib object info object for this event.
 *
 * @param pInFibObjectInfoChanged a pointer to the Fib object info
 * 	object that was changed
 * 	@see pFibObjectInfoChanged
 */
void eFibObjectInfoChangedEvent::setFibObjectInfo(
		const cFibObjectInfo * pInFibObjectInfoChanged ){
	
	pFibObjectInfoChanged = pInFibObjectInfoChanged;
}


/**
 * @return if true the Fib object info object was deleted, else this
 * 	event dosn't mark that it was deleted
 * 	@see bFibObjectInfoDeleted
 */
bool eFibObjectInfoChangedEvent::isDeleted() const{
	
	return bFibObjectInfoDeleted;
}


/**
 * This method sets if the Fib object info object was delted.
 *
 * @param bInFibObjectInfoDeleted if true the Fib object info object was
 * 	deleted, else this event dosn't mark that it was deleted
 * 	@see bFibObjectInfoDeleted
 */
void eFibObjectInfoChangedEvent::setDeleted(
		const bool bInFibObjectInfoDeleted ){
	
	bFibObjectInfoDeleted = bInFibObjectInfoDeleted;
}










