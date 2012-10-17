/**
 * @file cDataPointRange
 * file name: cDataPointRange.h
 * @author Betti Oesterholz
 * @date 07.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for a one dimensional range datapoint.
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
 * This header specifies a class for a one dimensional range datapoint.
 * A range datapoint (x,{minY, maxY}) contains a x and an y area
 * {minY, maxY} of values in which the y value of the datapoint lays.
 *
 */
/*
History:
07.06.2010  Oesterholz  created
22.02.2011  Oesterholz  equal() method added
30.06.2011  Oesterholz  operator<() added
*/

#ifndef ___N_D_1_C_DATA_POINT_RANGE_H__
#define ___N_D_1_C_DATA_POINT_RANGE_H__

#include "version.h"


namespace fib{

namespace algorithms{

namespace nD1{


template <class tX, class tY>
class cDataPointRange{
public:

	/**
	 * The x value for the datapoint.
	 */
	tX x;
	
	/**
	 * The minimal y value for the datapoint.
	 */
	tY minY;
	
	/**
	 * The maximal y value for the datapoint.
	 */
	tY maxY;
	
	/**
	 * standardconstructor for a datapoint
	 *
	 * @param inX the @see x value for the datapoint
	 * @param inMinY the @see minY value for the datapoint
	 * @param inMaxY the @see maxY value for the datapoint
	 */
	cDataPointRange( tX inX = 0, tY inMinY = 0, tY inMaxY = 0 );
	
	/**
	 * @return the diffence betwean the minimal and maximal y value
	 * @see minY
	 * @see maxY
	 */
	tY diff() const;

	/**
	 * @param dataPoint the datapoint to which the distance in the x value
	 * 	should be evalued
	 * @return the distance of the x value of this datapoint and the given datapoint
	 * @see x
	 */
	tX dist( const cDataPointRange<tX, tY> & dataPoint ) const;

	/**
	 * @param dataPoint the range data point to compare with this
	 * @return true if this range data point is equal to the given range
	 * 	data point, else false
	 */
	bool equal( const cDataPointRange<tX, tY> & dataPoint ) const;

	/**
	 * @param dataPoint the datapoint to compare this datapoint with
	 * @return true if the x element of the this datapoint is lower or,
	 * 	if the x elements of this and the given datapoint are equal, true
	 * 	if the minY element of this datapoint is lower, else if the also
	 * 	the minY elements of this and the given datapoint are equal, true
	 * 	if the maxY element of this datapoint is lower,
	 * 	(@see x, @see minY, @see maxY)
	 */
	bool operator<( const cDataPointRange<tX, tY> & dataPoint ) const;

};


};//end namespace nD1
};//end namespace algorithms
};//end namespace fib

//include template implementation
#include "../nD1/src/cDataPointRange.cpp"


#endif //___N_D_1_C_DATA_POINT_RANGE_H__
