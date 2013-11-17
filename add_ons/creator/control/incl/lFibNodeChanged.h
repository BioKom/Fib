
//TODO check

/**
 * @file lFibNodeChanged
 * file name: lFibNodeChanged.h
 * @author Betti Oesterholz
 * @date 12.06.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a listener interface for listening for Fib object
 * node changes.
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
 * This file specifies a listener interface for listening for Fib object
 * node changes. If a Fib object changes, the Fib object nodes (cFibNode)
 * for it will send a event to all registered listeners of this type.
 * @see cFibNode
 * @see eFibNodeChangedEvent
 */
/*
History:
12.06.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__L_FIB_NODE_CHANGED_H__
#define ___FIB__NCREATOR__L_FIB_NODE_CHANGED_H__


#include "version.h"

#include "eFibNodeChangedEvent.h"

#include <string>


namespace fib{

namespace nCreator{


class lFibNodeChanged{
public:
	
	/**
	 * Event method
	 * It will be called every time a Fib node (cFibNode), at which
	 * this object is registered, was changed.
	 *
	 * @param pFibNodeChanged a pointer to the event, with the information
	 * 	about the changed Fib node
	 */
	virtual void fibNodeChangedEvent(
		const eFibNodeChangedEvent * pFibNodeChanged ) = 0;
	
	
	/**
	 * @return the name of this class "lFibNodeChanged"
	 */
	virtual std::string getName() const = 0;
	
};//end class lFibNodeChanged

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__L_FIB_NODE_CHANGED_H__





