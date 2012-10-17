/**
 * @file cDataPoint
 * file name: cDataPoint.h
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


#include "../nD2/incl/cDataPointRange.h"

#include <cmath>

#ifndef ___N_D_2_C_DATA_POINT_RANGE_CPP__
#define ___N_D_2_C_DATA_POINT_RANGE_CPP__

using namespace std;


using namespace fib::algorithms;



/**
 * standardconstructor for a range datapoint
 *
 * @param inX the @see x value for the datapoint
 * @param inY the @see y value for the datapoint
 * @param inMinZ the @see minZ value for the datapoint
 * @param inMaxZ the @see maxZ value for the datapoint
 */
template <class tX, class tY, class tZ> nD2::cDataPointRange<tX, tY, tZ>::
	cDataPointRange( tX inX, tY inY, tZ inMinZ, tZ inMaxZ ):
		x( inX ), y( inY ), minZ( inMinZ ), maxZ( inMaxZ ){
		
	if ( inMaxZ < inMinZ ){
		minZ = inMaxZ;
		maxZ = inMinZ;
	}
}


/**
 * @return the diffence betwean the minimal and maximal z value
 * @see minZ
 * @see maxZ
 */
template <class tX, class tY, class tZ> tZ nD2::cDataPointRange<tX, tY, tZ>::diff() const{
	return ( maxZ - minZ );
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
template <class tX, class tY, class tZ> tX nD2::cDataPointRange<tX, tY, tZ>::dist(
		const nD2::cDataPointRange<tX, tY, tZ> & dataPoint ) const{
	
	const tX xDistance = x - dataPoint.x;
	const tY yDistance = y - dataPoint.x;
	
	return (tX)( sqrt( xDistance * xDistance + (tX)(yDistance * yDistance) ) );
}

#endif //___N_D_2_C_DATA_POINT_RANGE_CPP__

