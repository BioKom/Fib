/**
 * @file nCorrectPoints
 * file name: nCorrectPoints.h
 * @author Betti Oesterholz
 * @date 18.10.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies functions for correcting points in fib -objects.
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
 * This header specifies functions for correcting points in fib -objects.
 */
/*
History:
18.10.2010  Oesterholz  created
*/

#ifndef ___N_CORRECT_POINTS_H__
#define ___N_CORRECT_POINTS_H__

#include "version.h"

#include "cFibElement.h"
#include "cList.h"


namespace fib{

namespace algorithms{

namespace nCorrectFibObject{

namespace nCorrectPoints{

	
	/**
	 * This function corrects the wron points in pToCorrectFibObject and
	 * returns corrected fib -objects.
	 * For every entry in this list liDistancesCountedWrong a corrected
	 * fib -object is given back.
	 * Every point in the evalued pToCorrectFibObject, wich properties
	 * have a greater distance as the n'th entry, in the sorted and
	 * uniqe liDistancesCountedWrong, will be included in the n'th
	 * returned fib -object.
	 * This function will ignore points, wich are background point in both
	 * the given list liPointWithPropertiesOrginal and fib -object
	 * pToCorrectFibObject.
	 *
	 * @param liPointWithPropertiesOrginal a list with points and ther
	 * 	properties, wich are correct
	 * @param pToCorrectFibObject the fib -object to correct
	 * @param liDistancesCountedWrong the list of distances of properties,
	 * 	till which a point is not wrong;
	 * 	for every entry in this list  a corrected fib -object is given back;
	 * 	every point in the evalued pToCorrectFibObject, wich properties
	 * 	have a greater distance as the n'th entry, in the sorted and
	 * 	uniqe liDistancesCountedWrong, will be included in the n'th
	 * 	returned fib -object
	 * @return a list with the corrected fib -objects;
	 * 	the first element of the returned list is the changed pToCorrectFibObject
	 */
	list<cFibElement *> replaceWrongPoints(
		const list< pair< cVectorPosition, list< cVectorProperty > > > & liPointWithPropertiesOrginal,
		cFibElement * pToCorrectFibObject, list<doubleFib> liDistancesCountedWrong );
	


};//end namespace nCorrectPoints
};//end namespace nCorrectFibObject
};//end namespace algorithms
};//end namespace fib


#endif //___N_CORRECT_POINTS_H__
