/**
 * @file cDataPoint
 * file name: cDataPoint.h
 * @author Betti Oesterholz
 * @date 07.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for a one dimensional datapoint.
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
 * This header specifies a class for a one dimensional datapoint.
 * A datapoint (x,y) is contains a x and an y value.
 *
 */
/*
History:
07.06.2010  Oesterholz  created
*/

#ifndef ___N_D_1_C_DATA_POINT_H__
#define ___N_D_1_C_DATA_POINT_H__

#include "version.h"


namespace fib{

namespace algorithms{

namespace nD1{


template <class tX, class tY>
class cDataPoint{
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
	 * standardconstructor for a datapoint
	 *
	 * @param inX the @see x value for the datapoint
	 * @param inY the @see y value for the datapoint
	 */
	cDataPoint( tX inX = 0, tY inY = 0 );
	
	/**
	 * @param dataPoint the datapoint to which the distance in the x value
	 * 	should be evalued
	 * @return the distance of the x value of this datapoint and the given datapoint
	 * @see x
	 */
	tX dist( const cDataPoint<tX, tY> & dataPoint ) const;


	/**
	 * @param dataPoint the datapoint to compare this datapoint with
	 * @return true if the given datapoint is equal to this, else false
	 * 	(@see x, @see y)
	 */
	bool operator==( const cDataPoint<tX, tY> & dataPoint ) const;

	/**
	 * @param dataPoint the datapoint to compare this datapoint with
	 * @return true if the given datapoint is not equal to this, else false
	 * 	(@see x, @see y)
	 */
	bool operator!=( const cDataPoint<tX, tY> & dataPoint ) const;

	/**
	 * @param dataPoint the datapoint to compare this datapoint with
	 * @return true if the x element of the this datapoint is lower or,
	 * 	if the x elements of this and the given datapoint are equal, true
	 * 	if the y element of this datapoint is lower, else false
	 * 	(@see x, @see y)
	 */
	bool operator<( const cDataPoint<tX, tY> & dataPoint ) const;

};


};//end namespace nD1
};//end namespace algorithms
};//end namespace fib


//include template implementation
#include "../src/cDataPoint.cpp"


#endif //___N_D_1_C_DATA_POINT_H__
