
//TODO check

/**
 * @file eFibObjectInfoChangedEvent
 * file name: eFibObjectInfoChangedEvent.h
 * @author Betti Oesterholz
 * @date 12.10.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies an event for Fib object info object changes.
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
 * This file specifies an event for Fib object info object changes.
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


#ifndef ___FIB__NCREATOR__E_FIB_OBJECT_INFO_CHANGED_EVENT_H__
#define ___FIB__NCREATOR__E_FIB_OBJECT_INFO_CHANGED_EVENT_H__


#include "version.h"

#include <string>

#include <QObject>


namespace fib{

namespace nCreator{

//cyclic dependencies
class cFibObjectInfo;

class eFibObjectInfoChangedEvent{
protected:
	
	/**
	 * A pointer to the Fib object info object that was changed.
	 */
	const cFibObjectInfo * pFibObjectInfoChanged;
	
	/**
	 * If true the Fib object info object was deleted.
	 */
	bool bFibObjectInfoDeleted;
	
public:
	
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
	eFibObjectInfoChangedEvent( const cFibObjectInfo * pInFibObjectInfoChanged,
		const bool bInFibObjectInfoDeleted = false );
	
	
	/**
	 * @return the name of this class "eFibObjectInfoChangedEvent"
	 */
	std::string getName() const;
	
	
	/**
	 * @return a pointer to the Fib object info object that was changed
	 * 	@see pFibObjectInfoChanged
	 */
	const cFibObjectInfo * getFibObjectInfo() const;
	
	/**
	 * This method sets the Fib object info object for this event.
	 *
	 * @param pInFibObjectInfoChanged a pointer to the Fib object info
	 * 	object that was changed
	 * 	@see pFibObjectInfoChanged
	 */
	void setFibObjectInfo( const cFibObjectInfo * pInFibObjectInfoChanged );
	
	/**
	 * @return if true the Fib object info object was deleted, else this
	 * 	event dosn't mark that it was deleted
	 * 	@see bFibObjectInfoDeleted
	 */
	bool isDeleted() const;
	
	/**
	 * This method sets if the Fib object info object was delted.
	 *
	 * @param bInFibObjectInfoDeleted if true the Fib object info object was
	 * 	deleted, else this event dosn't mark that it was deleted
	 * 	@see bFibObjectInfoDeleted
	 */
	void setDeleted( const bool bInFibObjectInfoDeleted = true );
	
};//end class eFibObjectInfoChangedEvent

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__E_FIB_OBJECT_INFO_CHANGED_EVENT_H__





