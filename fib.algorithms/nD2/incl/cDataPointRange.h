/**
 * @file cDataPointRange
 * file name: cDataPointRange.h
 * @author Betti Oesterholz
 * @date 30.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for a two dimensional range datapoint.
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
 * This header specifies a class for a two dimensional range datapoint.
 * A range datapoint (x, y,{minZ, maxZ}) contains a x, a y and an z area
 * {minZ, maxZ} of values in which the z value of the datapoint lays.
 *
 */
/*
History:
30.06.2010  Oesterholz  created
*/

#ifndef ___N_D_2_C_DATA_POINT_RANGE_H__
#define ___N_D_2_C_DATA_POINT_RANGE_H__

#include "version.h"


namespace fib{

namespace algorithms{

namespace nD2{


template <class tX, class tY, class tZ>
class cDataPointRange{
public:

	/**
	 * The x value for the datapoint.
	 */
	tX x;
	
	/**
	 * The y value for the datapoint.
	 */
	tY y;
	
	/**
	 * The minimal y value for the datapoint.
	 */
	tZ minZ;
	
	/**
	 * The maximal y value for the datapoint.
	 */
	tZ maxZ;
	
	/**
	 * standardconstructor for a range datapoint
	 *
	 * @param inX the @see x value for the datapoint
	 * @param inY the @see y value for the datapoint
	 * @param inMinZ the @see minZ value for the datapoint
	 * @param inMaxZ the @see maxZ value for the datapoint
	 */
	cDataPointRange( tX inX = 0, tY inY = 0, tZ inMinZ = 0, tZ inMaxZ = 0 );
	
	/**
	 * @return the diffence betwean the minimal and maximal z value
	 * @see minZ
	 * @see maxZ
	 */
	tZ diff() const;

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
	tX dist( const cDataPointRange<tX, tY, tZ> & dataPoint ) const;

};


};//end namespace nD2
};//end namespace algorithms
};//end namespace fib

//include template implementation
#include "../nD2/src/cDataPointRange.cpp"


#endif //___N_D_2_C_DATA_POINT_RANGE_H__
