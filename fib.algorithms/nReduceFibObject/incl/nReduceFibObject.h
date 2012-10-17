/**
 * @file nReduceFibObject
 * file name: nReduceFibObject.h
 * @author Betti Oesterholz
 * @date 14.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies functions for reducing fib -objects.
 * Copyright (C) @c GPL3 2010 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (GPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This header specifies functions for reducing fib -objects.
 * This is done be removing Fib -elements or / and fib -underobjects from
 * fib objects.
 */
/*
History:
14.06.2010  Oesterholz  created
20.11.2010  Oesterholz  removeOverwrittenProperies() added
*/

#ifndef ___N_REDUCE_FIB_OBJECT_H__
#define ___N_REDUCE_FIB_OBJECT_H__

#include "version.h"

#include "cFibElement.h"


namespace fib{

namespace algorithms{

namespace nReduceFibObject{

	/**
	 * This function removes from the given fib -object all underobjects
	 * which point properties are overwritten and so not necessary.
	 *
	 * @param fibElementToReduce a reference to the fib -object to reduce;
	 * 	this fib -object will be changed
	 * @return if the given fib -object was reduced true, else (the
	 * 	fib -object wasn't changed) false
	 */
	bool removeOverwrittenUnderObjects( cFibElement & fibElementToReduce  );


	/**
	 * This function removes from the given fib -object all underobjects
	 * which point properties are overwritten or overwrite the background but
	 * are equal to it, ther are not necessary. Than it removes all all
	 * properties, which are not are not necessary
	 *
	 * @param fibElementToReduce a reference to the fib -object to reduce;
	 * 	this fib -object will be changed
	 * @return if the given fib -object was reduced true, else (the
	 * 	fib -object wasn't changed) false
	 */
	bool removeOverwrittenProperties( cFibElement & fibElementToReduce );
		
};//end namespace nReduceFibObject
};//end namespace algorithms
};//end namespace fib

//include template implementation
#include "../src/nReduceFibObject.cpp"


#endif //___N_REDUCE_FIB_OBJECT_H__
