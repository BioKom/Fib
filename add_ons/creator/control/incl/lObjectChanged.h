/**
 * @file lObjectChanged
 * file name: lObjectChanged.h
 * @author Betti Oesterholz
 * @date 20.12.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a listener template interface for listening for
 * changes in an object.
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
 * This file specifies a listener template interface for listening for
 * changes in an object.
 * @pattern listener
 */
/*
History:
20.12.2013  Oesterholz  created
*/


#ifndef ___L_OBJECT_CHANGED_H__
#define ___L_OBJECT_CHANGED_H__


#include "version.h"

#include <string>


template< class tEvent > class lObjectChanged{
public:
	
	/**
	 * Event method
	 * It will be called every time the object, at which this object is
	 * registered, was changed.
	 *
	 * @param pEvent a pointer to the chang event
	 */
	virtual void changedEvent( const tEvent * pEvent ) = 0;
	
	/**
	 * @return the name of this class
	 */
	virtual std::string getName() const = 0;
	
};//end class lObjectChanged

#endif //___L_OBJECT_CHANGED_H__





