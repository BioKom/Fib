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


#include "../nD1/incl/cDataPointRange.h"

#include "fibDatatyps.h"


#ifndef ___N_D_1_C_DATA_POINT_RANGE_CPP__
#define ___N_D_1_C_DATA_POINT_RANGE_CPP__


using namespace fib::algorithms;
using namespace fib;



/**
 * standardconstructor for a datapoint
 *
 * @param inX the @see x value for the datapoint
 * @param inMinY the @see minY value for the datapoint
 * @param inMaxY the @see maxY value for the datapoint
 */
template <class tX, class tY> nD1::cDataPointRange<tX, tY>::cDataPointRange(
		tX inX, tY inMinY, tY inMaxY ):
		x( inX ), minY( inMinY ), maxY( inMaxY ) {
		
	if ( inMaxY < inMinY ){
		minY = inMaxY;
		maxY = inMinY;
	}
}


/**
 * @return the diffence betwean the minimal and maximal y value
 * @see minY
 * @see maxY
 */
template <class tX, class tY> tY nD1::cDataPointRange<tX, tY>::diff() const{
	return ( maxY - minY );
}


/**
 * @param dataPoint the datapoint to which the distance in the x value
 * 	should be evalued
 * @return the distance of the x value of this datapoint and the given datapoint
 * @see x
 */
template <class tX, class tY> tX nD1::cDataPointRange<tX, tY>::dist(
		const  cDataPointRange<tX, tY> & dataPoint ) const{
	return dataPoint.x - x;
}


/**
 * @param dataPoint the range data point to compare with this
 * @return true if this range data point is equal to the given range
 * 	data point, else false
 */
template <class tX, class tY> bool nD1::cDataPointRange<tX, tY>::equal(
		const cDataPointRange<tX, tY> & dataPoint ) const{
	
	return (x == dataPoint.x) &&
		( minY == dataPoint.minY ) && ( maxY == dataPoint.maxY );
}


/**
 * @param dataPoint the datapoint to compare this datapoint with
 * @return true if the x element of the this datapoint is lower or,
 * 	if the x elements of this and the given datapoint are equal, true
 * 	if the minY element of this datapoint is lower, else if the also
 * 	the minY elements of this and the given datapoint are equal, true
 * 	if the maxY element of this datapoint is lower,
 * 	(@see x, @see minY, @see maxY)
 */
template <class tX, class tY> bool nD1::cDataPointRange<tX, tY>::operator<(
		const nD1::cDataPointRange<tX, tY> & dataPoint ) const{
	
	if ( x < dataPoint.x ){
		return true;
	}//else
	if ( dataPoint.x < x ){
		return false;
	}//else
	
	//if ( x == dataPoint.x )
	return ( minY < dataPoint.minY ) || ( ( minY == dataPoint.minY ) && ( maxY < dataPoint.maxY ) );
}




#endif //___N_D_1_C_DATA_POINT_RANGE_CPP__

