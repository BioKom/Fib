/**
 * @file nD1
 * file name: nD1.cpp
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


#include "nD1.h"

#ifndef ___C_N_D1_CPP__
#define ___C_N_D1_CPP__

#include <iostream>

//#define PRINT_INFOS

/**
 * The save boundery for error.
 * Errors will just be counted if ther are greater than this save boundery.
 */
#define SAVE_BOUNDERY 0.0000000001

using namespace std;
using namespace fib::algorithms::nD1;


/**
 * @param dataPoint1 the first datapoint to compare with
 * @param dataPoint2 the second datapoint to compare with
 * @return true if the x position of the first point is lower than that of
 * 	the second point
 */
template <class tX, class tY>
bool lowerPosition( fib::algorithms::nD1::cDataPoint<tX, tY> dataPoint1,
		fib::algorithms::nD1::cDataPoint<tX, tY> dataPoint2 ){

	return (dataPoint1.x < dataPoint2.x);
}


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
vector< fib::algorithms::nD1::cDataPoint<tX, tY> > derivate(
		const vector< fib::algorithms::nD1::cDataPoint<tX, tY> > & vecInput ){
	
	vector< fib::algorithms::nD1::cDataPoint<tX, tY> > vecDerivate = vecInput;
	
	sort( vecDerivate.begin(), vecDerivate.end(), lowerPosition );
	
	tY minDistance = 0.0;
	long lMinDistPos = -1;
	
	//evalue the derivate
	const size_t iNumberOfDerivatePoints = vecDerivate.size() - 1;
	for ( size_t iActualValue = 0; iActualValue < iNumberOfDerivatePoints;
			iActualValue++ ){

		const tY dDistance = vecDerivate[ iActualValue ].dist(
			vecDerivate[ iActualValue + 1 ] );
		
		vecDerivate[ iActualValue ].y = (vecDerivate[ iActualValue + 1 ].y -
			vecDerivate[ iActualValue ].y) / dDistance;
	}
	//remove the last element
	vecDerivate.resize( iNumberOfDerivatePoints );
	
	return vecDerivate;
}


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
pair< vector< fib::algorithms::nD1::cDataPointRange<tX, tY> >,
	fib::algorithms::nD1::cDataPointRange<tX, tY> > derivateDist(
		const vector< fib::algorithms::nD1::cDataPointRange<tX, tY> > & vecInput ){
	
	vector< fib::algorithms::nD1::cDataPointRange<tX, tY> > vecDerivate;
	
	tY minDistance = 0.0;
	long lMinDistPos = -1;
	
	//search for the entry with the minimal distance
	for ( size_t iActualValue = 0; iActualValue < vecInput.size();
			iActualValue++ ){
		
		if ( ( abs( vecInput[ iActualValue ].maxY ) < SAVE_BOUNDERY ) &&
				( abs( vecInput[ iActualValue ].minY ) < SAVE_BOUNDERY ) ){
			continue;//skip nullvalues
		}
		
		if ( ( abs( vecInput[ iActualValue ].diff() ) < minDistance) ||
				(lMinDistPos == -1) ){
			
			minDistance = abs( vecInput[ iActualValue ].diff() );
			lMinDistPos = iActualValue;
		}
	}
	if ( lMinDistPos == -1 ){
#ifdef PRINT_INFOS
		cout<<"All ranges are 0."<<endl;
#endif
		return make_pair( vecDerivate, fib::algorithms::nD1::cDataPoint<tX, tY>() );
	}
	
	const tY minDistanceAverage = ( vecInput[ lMinDistPos ].maxY +
		vecInput[ lMinDistPos ].minY ) / 2.0;
	
#ifdef PRINT_INFOS
	cout<<"the position with the minimal range: "<<lMinDistPos<<
		"  the position is="<<vecInput[ lMinDistPos ].x<<
		"   the range average is="<<minDistanceAverage<<
		" ( "<<vecInput[ lMinDistPos ].minY <<" , "<<
			vecInput[ lMinDistPos ].maxY <<" )"<<endl;
#endif
	//evalue the derivate
	tY maxDistance;
	for ( size_t iActualValue = 0; iActualValue < vecInput.size();
			iActualValue++ ){
		
		if ( iActualValue == ((size_t)(lMinDistPos)) ){
			continue;//skip
		}
		if ( ( abs( vecInput[ iActualValue ].maxY ) < SAVE_BOUNDERY ) &&
				( abs( vecInput[ iActualValue ].minY ) < SAVE_BOUNDERY ) ){
			continue;//skip nullvalues
		}

		const tY dDistance = vecInput[ lMinDistPos ].dist( vecInput[ iActualValue ] );
		
		minDistance = (vecInput[ iActualValue ].minY - minDistanceAverage) / dDistance;
		maxDistance = (vecInput[ iActualValue ].maxY - minDistanceAverage) / dDistance;
		
		if ( maxDistance < minDistance ){
			//switch values
			const tY dTmpValue = minDistance;
			minDistance = maxDistance;
			maxDistance = dTmpValue;
		}
		vecDerivate.push_back( fib::algorithms::nD1::cDataPoint<tX, tY>( vecInput[ iActualValue ].x,
			minDistance, maxDistance ) );
		
	}
	return make_pair( vecDerivate, vecInput[ lMinDistPos ] );
}

#endif //___C_N_D1_CPP__
