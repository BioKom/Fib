/**
 * @class cClusterFunExp
 * file name: cClusterFunExp.h
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
 * An data point dataPoint can be in the cluster to an other data point
 * dataClusterCenter, if:
 * 	dataClusterCenter.second > dataPoint.second * dBaseFactor ^
 * 		distFunction( dataClusterCenter.first, dataPoint.first )
 * If ther are more data points C_i for which the formulare is fulfilled,
 * the data point will be mapped to the data point wher
 * C_i.second - dataPoint.second * dBaseFactor ^ distFunction( C_i.first, dataPoint.first )
 * is the maximal. (@see pDistFunction and @see dBaseFactor)
 */
/*
History:
17.03.2011  Oesterholz  created
*/

#ifndef ___C_CLUSTER_FUN_EXP__
#define ___C_CLUSTER_FUN_EXP__

#include "version.h"


namespace fib{

namespace algorithms{

namespace nCluster{

template< class tDataPoint >
class cClusterFunExp: public iClusterFunction< tDataPoint >{

	/**
	 * The functor to evalue the distance of two data points.
	 */
	const iDistFunction< tDataPoint > * pDistFunction;
	
	/**
	 * The base factor for evaluing, if an data point is subsumed.
	 */
	const double dBaseFactor;
	
public:
	
	/**
	 * constructor
	 *
	 * @param inDistFunction a reference vor the functor to evalue the distance
	 * 	of two data points; (@see pDistFunction)
	 * 	Beware: As long as this object is used inDistFunction shouldn't be
	 * 		deleted.
	 * @param dInBaseFactor the base factor for evaluing, if an data point
	 * 	is subsumed (@see dBaseFactor)
	 */
	cClusterFunExp( const iDistFunction< tDataPoint > & inDistFunction,
			const double dInBaseFactor ):
			pDistFunction( &inDistFunction ), dBaseFactor( dInBaseFactor ){
		
		//nothing to do
	}
	
	/**
	 * destructor
	 */
	virtual ~cClusterFunExp(){
		//nothing to do
	}
	
	
	/**
	 * This operator should evalue a cluster value for two data points.
	 * The value should indicate, how good it is to cluster the data
	 * point dataPoint to the dataClusterCenter.
	 *
	 * An data point dataPoint can be in the cluster to an other data point
	 * dataClusterCenter, if:
	 * 	dataClusterCenter.second > dataPoint.second * dBaseFactor ^
	 * 		distFunction( dataClusterCenter.first, dataPoint.first )
	 * If ther are more data points C_i for which the formulare is fulfilled,
	 * the data point will be mapped to the data point wher
	 * C_i.second - dataPoint.second * dBaseFactor ^ distFunction( C_i.first, dataPoint.first )
	 * is the maximal. (@see pDistFunction and @see dBaseFactor)
	 *
	 * @param dataClusterCenter the data point, to wich to evalue the
	 * 	value that dataPoint is clustered to it
	 * @param dataPoint the data point to cluster/subsume by dataClusterCenter
	 * @return the cluster value for dataClusterCenter and dataPoint
	 */
	virtual double operator() ( const pair< tDataPoint, unsigned long > & dataClusterCenter,
		const pair< tDataPoint, unsigned long > & dataPoint ) const{
		
		return dataClusterCenter.second - dataPoint.second * pow( dBaseFactor,
			(*pDistFunction)( dataClusterCenter.first, dataPoint.first ) );
	}


};//class cClusterFunExp


};//end namespace nCluster
};//end namespace algorithms
};//end namespace fib


#endif //___C_CLUSTER_FUN_EXP__




