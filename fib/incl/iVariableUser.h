/**
 * @class iVariableUser
 * file name: iVariableUser.h
 * @author Betti Oesterholz
 * @date 16.11.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This interface is for elements that uses variables of the type
 * cFibVariable.
 * 
 * Copyright (C) @c LGPL3 2009 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * @pattern observer
 * This interface is for elements that uses variables of the type
 * cFibVariable.
 * It defines methods which variables can use to commuicate with such
 * elements.
 *
 */
/*
History:
16.11.2009  Oesterholz  created
*/

#ifndef ___I_VARIABLE_USER_H__
#define ___I_VARIABLE_USER_H__


#include "version.h"


namespace fib{


class cFibElement;//cyclic dependencie
class cFibVariable;//cyclic dependencie

class iVariableUser{

friend class cFibVariable;

protected:
	/**
	 * @return the fib -element which uses the variables of this element
	 */
	virtual cFibElement * getVariableUsingFibElement() const = 0;
	
	/**
	 * This method deletes all occurenc of the given variable from this
	 * element. So the variable is not used anymore of this element.
	 * Beware: This element has to be unregisterd (call
	 * unregisterUsingElement() ) at the pVariable seperatly. Do this directly
	 * befor or after calling this method.
	 *
	 * @param pVariable the variable which is to delete from this element
	 * @return true if the variable dosn't occure anymore in this element,
	 * 	else false
	 */
	virtual bool deleteVariable( cFibVariable * pVariable ) = 0;


};




}//namespace fib

#endif