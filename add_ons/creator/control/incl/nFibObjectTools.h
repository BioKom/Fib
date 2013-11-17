
//TODO check

/**
 * @file nFibObjectTools
 * file name: nFibObjectTools.h
 * @author Betti Oesterholz
 * @date 19.07.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a namespace with basic functions or tools for Fib objects.
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
 * This file specifies a namespace with basic functions or tools for Fib objects.
 *
 */
/*
History:
19.07.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__N_FIB_OBJECT_TOOLS_H__
#define ___FIB__NCREATOR__N_FIB_OBJECT_TOOLS_H__


#include "version.h"

#include "cFibElement.h"

#include <list>



namespace fib{

namespace nCreator{

namespace nFibObjectTools{

	/**
	 * This function will evalue the input variables for the given
	 * Fib object.
	 * It will evalue all variables used in the Fib object, but not defined
	 * in it. Also input variables are input variables of the root element
	 * pFibObject, if pFibObject is a root element.
	 *
	 * @param pFibObject the pointer to the Fib object, for which to evalue
	 * 	the input variables
	 * @param bTillRoot if true searches for input variables in the Fib
	 * 	object for pFibObject till the root Fib element (Fib element
	 * 	with no superior), else the input variables for pFibObject will
	 * 	be returned
	 * @return a list with the (pointers to) the input variables of the
	 * 	given Fib object;
	 * 	First it will contain the input variables of the root element
	 * 	pFibObject, if pFibObject is a root element.
	 */
	list< cFibVariable * > evalueInputVariables( cFibElement * pFibObject,
		const bool bTillRoot=false );
	
};//end namespace nFibObjectTools
};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__N_FIB_OBJECT_TOOLS_H__





