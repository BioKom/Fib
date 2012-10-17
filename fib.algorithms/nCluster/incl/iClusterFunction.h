/**
 * @class iClusterFunction
 * file name: iClusterFunction.h
 * @author Betti Oesterholz
 * @date 17.03.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the interface for evaluing a cluster value for two data points.
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
 * This file contains the interface for evaluing a cluster value for two data points.
 * Every class, which implements this interface have to implement the operator().
 * This operator should evalue a value for two data points.
 * The value should indicate, how good it is to cluster the second data
 * point dataPoint to the first dataClusterCenter.
 * If dataPoint should be clustered to dataClusterCenter the returned value should be
 * greater 0, else it should be lower or equal 0.
 * The function should have the following properties:
 * 	- 0 \< operator( dataClusterCenter, dataPoint ) -> operator( dataPoint, dataClusterCenter ) \< 0
 * 	- operator( dataClusterCenter, dataPoint ) \< 0 -> 0 \< operator( dataPoint, dataClusterCenter )
 * 	- 0 \< operator( dataClusterCenter, dataPoint ) and 0 \< operator( dataPoint, data3 )
 * 		-> evalue( dataPoint, data3 ) \< evalue( dataClusterCenter, data3 )
 * If some of theas conditions are not given, the clustering result may
 * be not predictebel (undesired).
 */
/*
History:
17.03.2011  Oesterholz  created
*/

#ifndef ___I_CLUSTER_FUNCTION__
#define ___I_CLUSTER_FUNCTION__

#include "version.h"

#include <utility>


namespace fib{

namespace algorithms{

namespace nCluster{

template< class tDataPoint >
class iClusterFunction{
public:
	
	/**
	 * pure virtual destructor
	 */
	virtual ~iClusterFunction(){
		//nothing to do
	}
	
	/**
	 * This operator should evalue a cluster value for two data points.
	 * The value should indicate how good it is to cluster the secound data
	 * point dataPoint to the first dataClusterCenter.
	 * If dataPoint should be clustered to dataClusterCenter the returned value should be
	 * greater 0, else it should be lower or equal 0.
	 * The function should have the following properties:
	 * 	- 0 \< evalue( dataClusterCenter, dataPoint ) -> evalue( dataPoint, dataClusterCenter ) \< 0
	 * 	- evalue( dataClusterCenter, dataPoint ) \< 0 -> 0 \< evalue( dataPoint, dataClusterCenter )
	 * 	- 0 \< evalue( dataClusterCenter, dataPoint ) and 0 \< evalue( dataPoint, data3 )
	 * 		-> evalue( dataPoint, data3 ) \< evalue( dataClusterCenter, data3 )
	 * If some of theas conditions are not given, the clustering result may
	 * be not predictebel (undesired).
	 *
	 * @param dataClusterCenter the data point, to which to evalue the
	 * 	value that dataPoint is clustered to it
	 * @param dataPoint the data point to cluster/subsume by dataClusterCenter
	 * @return the cluster value for dataClusterCenter and dataPoint
	 */
	virtual double operator() ( const std::pair< tDataPoint, unsigned long > & dataClusterCenter,
		const std::pair< tDataPoint, unsigned long > & dataPoint ) const = 0;

};//class iClusterFunction


};//end namespace nCluster
};//end namespace algorithms
};//end namespace fib


#endif //___I_CLUSTER_FUNCTION__




