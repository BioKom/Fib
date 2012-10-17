/**
 * @class cClusterFunArea
 * file name: cClusterFunArea.h
 * @author Betti Oesterholz
 * @date 17.03.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the implementation for evaluing a cluster value for
 * two data points.
 * Copyright (C) @c LGPL3 2011 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This file contains the implementation for evaluing a cluster value for
 * two data points.
 *
 * An data point D can be in the cluster to an other data point C, if:
 * 	The distance is lower an maximal distance (@see dMaxDistance).
 * 	If C has more elements than D.
 */
/*
History:
17.03.2011  Oesterholz  created
*/

#ifndef ___C_CLUSTER_FUN_AREA__
#define ___C_CLUSTER_FUN_AREA__

#include "version.h"

#include <vector>
#include <cmath>


namespace fib{

namespace algorithms{

namespace nCluster{

template< class tValue >
class cClusterFunArea: public iClusterFunction< vector< tValue > >{

	/**
	 * The maximum distance of two points in an cluster.
	 */
	const tValue dMaxDistance;
	
public:
	
	/**
	 * constructor
	 *
	 * @param dInMaxDistance The maximum distance of two points in an cluster.
	 * 	(@see dMaxDistance)
	 */
	cClusterFunArea( const tValue dInMaxDistance  ):dMaxDistance( dInMaxDistance ){
		//nothing to do
	}
	
	/**
	 * destructor
	 */
	virtual ~cClusterFunArea(){
		//nothing to do
	}
	
	
	/**
	 * This operator should evalue a cluster value for two data points.
	 * The value should indicate how good it is to cluster the secound data
	 * point dataPoint to the first dataClusterCenter.
	 * An data point D can be in the cluster to an other data point C, if:
	 * 	The distance is lower an maximal distance (@see dMaxDistance).
	 * 	If C has more elements than D.
	 *
	 * @param dataClusterCenter the data point, to which to evalue the
	 * 	value that dataPoint is clustered to it
	 * @param dataPoint the data point to cluster/subsume by dataClusterCenter
	 * @return the cluster value for dataClusterCenter and dataPoint
	 */
	virtual double operator() ( const pair< vector< tValue >, unsigned long > & dataClusterCenter,
		const pair< vector< tValue >, unsigned long > & dataPoint ) const{
		
		const vector< tValue > & vecDataPointCluster = dataClusterCenter.first;
		const vector< tValue > & vecDataPoint = dataPoint.first;
		const unsigned int uiDimensions = min( vecDataPointCluster.size(),
			vecDataPoint.size() );
		
		tValue dDistance = 0;
		for ( unsigned int uiActualDimension  = 0;
				uiActualDimension < uiDimensions; uiActualDimension++ ){
			
			dDistance += abs( ((int)(vecDataPoint[ uiActualDimension ])) -
				((int)(vecDataPointCluster[ uiActualDimension ])) );
		}
		
		if ( dMaxDistance < dDistance ){
			/*distance of data points greater than the maximum distance
			-> don't cluster them*/
			return -1.0;
		}
		/*evalue:
			(dataClusterCenter.second - dataPoint.second) * dim * dMaxDistance / 2 +
			+ dim * dMaxDistance / 2 - sum( vecDataPoint[ uiActualDimension ] mod (dMaxDistance / 2) )
		with:
			dim = dataClusterCenter.first.size()
		
		explanation:
			With the part ((dataClusterCenter.second - dataPoint.second) *
			* dim * dMaxDistance / 2) any datapoint with the most elements will
			be the center of the cluster.
			If two data point have an equal number of data points the part
			(dim * dMaxDistance / 2 - sum( vecDataPoint[ uiActualDimension ]
			mod (dMaxDistance / 2) )) will arrange that, in any neighbourhood
			just one point is choosen as the cluster center
		*/
		
		const unsigned int uiHalfDimMaxDistance = ( 2 < dMaxDistance ) ?
			(dMaxDistance / 2) : 1;
		
		tValue dDistanceFactor = 0;
		for ( unsigned int uiActualDimension  = 0;
				uiActualDimension < uiDimensions; uiActualDimension++ ){
			
			dDistanceFactor += vecDataPoint[ uiActualDimension ] % uiHalfDimMaxDistance;
		}
		return (dataClusterCenter.second - dataPoint.second + 1) *
			((double)( uiDimensions )) * dMaxDistance / 2.0 + dDistanceFactor;
	}


};//class cClusterFunArea


};//end namespace nCluster
};//end namespace algorithms
};//end namespace fib


#endif //___C_CLUSTER_FUN_AREA__




