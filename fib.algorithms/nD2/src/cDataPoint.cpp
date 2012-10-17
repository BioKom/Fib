/**
 * @file nD2::cDataPoint
 * file name: nD2::cDataPoint.cpp
 * @author Betti Oesterholz
 * @date 30.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements a class for a two dimensional datapoint.
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
 * This header specifies a class for a two dimensional datapoint.
 * A datapoint (x,y,z) is contains a x, a y and an z value.
 *
 */
/*
History:
30.06.2010  Oesterholz  created
*/


#include "../nD2/incl/cDataPoint.h"

#include <cmath>

#ifndef ___N_D_2_C_DATA_POINT_CPP__
#define ___N_D_2_C_DATA_POINT_CPP__

using namespace std;

using namespace fib::algorithms;



/**
 * standardconstructor for a datapoint
 *
 * @param inX the @see x value for the datapoint
 * @param inY the @see y value for the datapoint
 * @param inZ the @see z value for the datapoint
 */
template <class tX, class tY, class tZ> nD2::cDataPoint<tX, tY, tZ>::
	cDataPoint( tX inX, tY inY, tZ inZ ):
		x( inX ), y( inY ), z( inZ ){
	//nothing to do
}


/**
 * This method evalues the distance to an oter datapoint.
 * The distance is the euclidean distance:
 * 	((x - dataPoint.x)^2 + (y - dataPoint.x)^2)^(1/2)
 *
 * @param dataPoint the datapoint to which the distance in the x
 * 	and y value should be evalued
 * @return the euclidean distance of this datapoint and the given datapoint
 * @see x
 * @see y
 */
template <class tX, class tY, class tZ> tX nD2::cDataPoint<tX, tY, tZ>::dist(
		const nD2::cDataPoint<tX, tY, tZ> & dataPoint ) const{
	
	const tX xDistance = x - dataPoint.x;
	const tY yDistance = y - dataPoint.x;
	
	return (tX)( sqrt( xDistance * xDistance + (tX)(yDistance * yDistance) ) );
}


#endif //___N_D_2_C_DATA_POINT_CPP__
