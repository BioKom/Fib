/**
 * @file nD1
 * file name: nD1.h
 * @author Betti Oesterholz
 * @date 07.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies functions for a one dimensional data.
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
 * This header specifies functions for a one dimensional data.
 *
 */
/*
History:
07.06.2010  Oesterholz  created
*/

#ifndef ___C_N_D1_H__
#define ___C_N_D1_H__


#include "version.h"

#include "./cDataPoint.h"
#include "./cDataPointRange.h"

#include <vector>
#include <algorithm>

using namespace std;


namespace fib{

namespace algorithms{

namespace nD1{


	/**
	 * This function evaluats a derivate of a vector with datapoints.
	 * To evalue the derivate the differnce in the y values of to
	 * neibourpoints is divided with ther distance.
	 *
	 * @param vecInput the vector with the range data points, for which the
	 * 	derivate is to be evalued
	 * @return the vector with derivate range datapoints
	 */
	template <class tX, class tY>
	vector< cDataPoint<tX, tY> > derivate(
		const vector< cDataPoint<tX, tY> > & vecInput );


	/**
	 * This function evaluats a derivate of a vector with range datapoints.
	 * To evalue the derivate a point with the minimal range size is choosen
	 * as the devolopment point. For every other point the maximal and minimal
	 * distance betwean two bounderies of the point and the devolopment point
	 * is evalued and divided by the distance betwean the points.
	 *
	 * @param vecInput the vector with the range data points, for which the
	 * 	derivate is to be evalued
	 * @return a pair with it's elements:
	 * 	- the first element is the vector with derivate range datapoints
	 * 	- the second element is the devolopment point which was choosen
	 */
	template <class tX, class tY> 
	pair< vector< cDataPointRange<tX, tY> >, cDataPointRange<tX, tY> > derivateDist(
		const vector< cDataPointRange<tX, tY> > & vecInput );




};//end namespace nD1
};//end namespace algorithms
};//end namespace fib

//include template implementation
#include "../src/nD1.cpp"



#endif //___C_N_D1_H__
