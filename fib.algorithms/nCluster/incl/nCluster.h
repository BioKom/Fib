/**
 * @file nCluster
 * file name: nCluster.h
 * @author Betti Oesterholz
 * @date 17.03.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies functions to cluster data.
 * Copyright (C) @c GPL3 2011 Betti Oesterholz
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
 * This header specifies functions to cluster data.
 */
/*
History:
17.03.2011  Oesterholz  created
*/

#ifndef ___N_CLUSTER_H__
#define ___N_CLUSTER_H__


#include "version.h"

#include "iClusterFunction.h"

#include <map>



using namespace std;


namespace fib{

namespace algorithms{

namespace nCluster{

	/**
	 * This function clusters the given data.
	 * This will be done with an given formular evaluePoints.
	 * An data point D can be in the cluster to an other data point C, if
	 * 0 \< evaluePoints.evalue( C, D )
	 * If ther are more data points C_i for which the formulare is fulfilled,
	 * the data point will be mapped to the data point wher
	 * evaluePoints( C_i, D ) is the maximal.
	 *
	 * @param mapData the data to cluster
	 * 	key: the datapoint
	 * 	value: the number of elements for the data point
	 * @param evaluePoints the class for evaluing the cluster value for two
	 * 	data points
	 * @return a map with:
	 * 	-key: the data points of the given mapData
	 * 	-value: the data point, which is the center of the cluster, in
	 * 		which the key data point is;
	 * 		so the key data point should be maped to the value data point
	 */
	template< class tDataPoint >
	map< tDataPoint, tDataPoint > cluster(
		const map< tDataPoint, unsigned long > & mapData,
		const iClusterFunction< tDataPoint > & evaluePoints );



};//end namespace nCluster
};//end namespace algorithms
};//end namespace fib


//include template implementation
#define ___N_CLUSTER_H_INCLUDE__
#include "../src/nCluster.cpp"
#undef ___N_CLUSTER_H_INCLUDE__



#endif //___N_CLUSTER_H__
















