/**
 * @file nCluster
 * file name: nCluster.cpp
 * @author Betti Oesterholz
 * @date 17.03.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header impelements functions to cluster data.
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
 * This header impelements functions to cluster data.
 */
/*
History:
17.03.2011  Oesterholz  created
*/



#include "nCluster.h"


#ifndef ___N_CLUSTER_CPP__
#define ___N_CLUSTER_CPP__

#include <set>
#include <cmath>

using namespace fib::algorithms::nCluster;


/*debugging:
#define DEBUG
#undef ___DEBUG_OUT_H__
#include "debugOut.inc"
*/


/**
 * This function clusters the given data.
 * This will be done with an given formular evaluePoints.
 * An data point D can be in the cluster to an other data point C, if
 * 0 \< evaluePoints( C, D )
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
	map< tDataPoint, tDataPoint > fib::algorithms::nCluster::cluster(
		const map< tDataPoint, unsigned long > & mapData,
		const iClusterFunction< tDataPoint > & evaluePoints ){

	DEBUG_OUT_L1(<<endl<<"fib::algorithms::nCluster::cluster( #mapData="<<mapData.size()<<", evaluePoints ) started"<<endl);
	if ( mapData.empty() ){
		DEBUG_OUT_L2(<<"fib::algorithms::nCluster::cluster( #mapData="<<mapData.size()<<", evaluePoints ) done -> nothing to map"<<endl);
		return map< tDataPoint, tDataPoint >();
	}
#ifdef FEATURE_NCLUSTER_CLUSTER_IN_ONE_STEP

	/*map for the data points
		key: the data point D
		value: a pair for the subsuming data point
			first: the data point T, which subsumes D
			second: the value: evaluePoints( T, D )
	*/
	typedef map< const tDataPoint *, pair< const tDataPoint *, double > > typeMapSubsum;
	typeMapSubsum mapSubsum;
	//for ever data point D, evalue with which data points it can be clustered
	for ( typename map< tDataPoint, unsigned long >::const_iterator
			itrDataPoint = mapData.begin();
			itrDataPoint != mapData.end(); itrDataPoint++ ){
		/*for every other data point C evalue: evaluePoints.evalue( C, D )*/
		typename map< tDataPoint, unsigned long >::const_iterator
			itrDataPointCompare = itrDataPoint;
		itrDataPointCompare++;
		for ( ; itrDataPointCompare != mapData.end(); itrDataPointCompare++ ){
			
			//DEBUG_OUT_L4(<<"evalue if point "<<&dataPointCompare<<" to subsumes point "<<&dataPoint<<endl<<flush);
			if ( *itrDataPoint == *itrDataPointCompare ){
				//point can't subsume itself
				continue;
			}
			const double dS = evaluePoints( *itrDataPointCompare, *itrDataPoint );
			
			if ( dS <= 0 ){
				//can't be subsumed by this point
				continue;
			}//else 0 < S dataPoint can be subsumed by dataPointCompare point
			
			//DEBUG_OUT_L4(<<"maping point "<<&dataPointCompare<<" to subsume point "<<&dataPoint<<" with value "<<dS<<endl<<flush);
			const tDataPoint * pDataPointCompare = &(itrDataPointCompare->first);
			const tDataPoint * pDataPoint = &(itrDataPoint->first);
			//data point dataPointCompare subsumes dataPoint (=subsumed)
			typename typeMapSubsum::iterator itrSubsumingPoint =
				mapSubsum.find( pDataPoint );
			
			if ( itrSubsumingPoint == mapSubsum.end() ){
				//subsuming point entry dosn't exists
				mapSubsum.insert( pair< const tDataPoint *, pair< const tDataPoint *, double > >(
				 pDataPoint, make_pair( pDataPointCompare, dS ) ) );
				
			}else{//subsuming point entry exists -> replace if dS is bigger
				if ( itrSubsumingPoint->second.second < dS ){
					//the actual point itrDataPointCompare subsumes itrDataPoint
					itrSubsumingPoint->second.first  = pDataPointCompare;
					itrSubsumingPoint->second.second = dS;
				}
			}
		}//end for itrDataPointCompare
	}//end for itrDataPoint
	//map points wich are mapped to a mapped point
	for ( typename typeMapSubsum::iterator itrDataPoint = mapSubsum.begin();
			itrDataPoint != mapSubsum.end(); itrDataPoint++ ){
		
		while ( true ){
			//check if the subsuming point is subsumed itself
			typename typeMapSubsum::iterator itrSubsumingPoint =
				mapSubsum.find( itrDataPoint->second.first );
			if ( itrSubsumingPoint == mapSubsum.end() ){
				//point which subsumes is not subsumed itself
				break;
			}else{//point which subsumes is subsumed itself
				if ( itrDataPoint->second.first != itrSubsumingPoint->second.first ){
					/*subsuming point is subsumed
					-> replace it by subsuming subsuming point*/
					const double dS = evaluePoints( *(mapData.find( *(itrSubsumingPoint->second.first) )),
						*(mapData.find( *(itrDataPoint->first) )) );
					
					if ( dS <= 0 ){
						//can't be subsumed by this point
						//set subsuming point to subsume itself
						itrSubsumingPoint->second.first = itrSubsumingPoint->first;
						break;
					}//else 0 < S dataPoint can be subsumed by itrSubsumingPoint->second.first point
					itrDataPoint->second.first = itrSubsumingPoint->second.first;
				}else{//point subsumes itself
					break;
				}
			}
		}
	}
	//create the cluster mapping
	map< tDataPoint, tDataPoint > mapClusterMapping;
	DEBUG_OUT_L2(<<"create the cluster mapping"<<endl<<flush);
	for ( typename typeMapSubsum::iterator itrDataPoint = mapSubsum.begin();
			itrDataPoint != mapSubsum.end(); itrDataPoint++ ){
		
		mapClusterMapping.insert( pair< tDataPoint, tDataPoint >(
			*(itrDataPoint->first), *(itrDataPoint->second.first) ) );
	}
	//insert all missing data points
	for ( typename map< tDataPoint, unsigned long >::const_iterator
			itrDataPoint = mapData.begin();
			itrDataPoint != mapData.end(); itrDataPoint++ ){
		
		const tDataPoint & dataPoint = itrDataPoint->first;
		if ( mapClusterMapping.find( dataPoint ) == mapClusterMapping.end() ){
			/*point is not subsumed by an other point
			->it subsumes itself*/
			mapClusterMapping.insert( pair< tDataPoint, tDataPoint >(
				dataPoint, dataPoint ) );
		}
	}
	
#else //FEATURE_NCLUSTER_CLUSTER_IN_ONE_STEP

	/*map for the data points
		key: the data point D
		value: a pair with the subsumed and subsuming data points
			first: a map with the data points S subsumed by the data point D
				key: the subsumed data points S, which is subsumed by D
				value: the value: evaluePoints( D, S )
			second: a map with the subsuming data point T, which subsume D
				key: the data point T, which subsumes D
				value: the value: evaluePoints( T, D )
	*/
	typedef map< const tDataPoint *, pair< map< const tDataPoint *, double >,
		map< const tDataPoint *, double > > > typeMapSubsum;
	typeMapSubsum mapSubsum;
	//for ever data point D, evalue with which data points it can be clustered
	for ( typename map< tDataPoint, unsigned long >::const_iterator
			itrDataPoint = mapData.begin();
			itrDataPoint != mapData.end(); itrDataPoint++ ){
		/*for every other data point C evalue: evaluePoints.evalue( C, D )*/
		typename map< tDataPoint, unsigned long >::const_iterator
			itrDataPointCompare = itrDataPoint;
		itrDataPointCompare++;
		for ( ; itrDataPointCompare != mapData.end(); itrDataPointCompare++ ){
			
			const tDataPoint & dataPointCompare = itrDataPointCompare->first;
			const tDataPoint & dataPoint = itrDataPoint->first;
			//DEBUG_OUT_L4(<<"evalue if point "<<&dataPointCompare<<" to subsumes point "<<&dataPoint<<endl<<flush);
			
			if ( (& dataPoint) == (& dataPointCompare) ){
				//point can*t subsume itself
				continue;
			}
			const double dS = evaluePoints( *itrDataPointCompare, *itrDataPoint );
			
			if ( dS <= 0 ){
				//can't be subsumed by this point
				continue;
			}//else 0 < S dataPoint can be subsumed by dataPointCompare point
			
			//DEBUG_OUT_L4(<<"maping point "<<&dataPointCompare<<" to subsume point "<<&dataPoint<<" with value "<<dS<<endl<<flush);
			//data point dataPointCompare subsumes dataPoint (=subsumed)
			typename typeMapSubsum::iterator itrSubsumingPoint =
				mapSubsum.find( &dataPointCompare );
			if ( itrSubsumingPoint == mapSubsum.end() ){
				//subsuming point entry dosn't exists
				map< const tDataPoint *, double > mapSubsumedPoint;
				mapSubsumedPoint.insert( pair< const tDataPoint *, double >(
				 &dataPoint, dS ) );
				
				mapSubsum.insert( make_pair( &dataPointCompare,
					make_pair( mapSubsumedPoint, map< const tDataPoint *, double >() ) ) );
			}else{//subsuming point entry exists
				itrSubsumingPoint->second.first.insert( pair< const tDataPoint *, double >(
					&dataPoint, dS ) );
			}
			//data point dataPoint is subsumed by dataPointCompare (=subsuming)
			typename typeMapSubsum::iterator itrSubsumedPoint =
				mapSubsum.find( &dataPoint );
			if ( itrSubsumedPoint == mapSubsum.end() ){
				//subsuming point entry dosn't exists
				map< const tDataPoint *, double > mapSubsumingPoint;
				mapSubsumingPoint.insert( pair< const tDataPoint *, double >(
				 &dataPointCompare, dS ) );
				
				mapSubsum.insert( make_pair( &dataPoint,
					make_pair( map< const tDataPoint *, double >(), mapSubsumingPoint ) ) );
			}else{//subsuming point entry exists
				itrSubsumedPoint->second.second.insert( pair< const tDataPoint *, double >(
					&dataPointCompare, dS ) );
			}
		}//end for itrDataPointCompare
	}//end for itrDataPoint
	DEBUG_OUT_L2(<<"map with subsuming and subsumed points created"<<endl<<flush);
	
	//add mapping for not subsumed data points (they map to themself)
	set< const tDataPoint * > setNotSubsumed;
	//insert all data points
	for ( typename map< tDataPoint, unsigned long >::const_iterator
			itrDataPoint = mapData.begin();
			itrDataPoint != mapData.end(); itrDataPoint++ ){
		
		setNotSubsumed.insert( &(itrDataPoint->first) );
	}
	//remove data points for which an mapping exists
	for ( typename typeMapSubsum::iterator itrDataPoint = mapSubsum.begin();
			itrDataPoint != mapSubsum.end(); itrDataPoint++ ){
		
		//data point is subsumed or subsuming -> remove it from not subsumed
		setNotSubsumed.erase( itrDataPoint->first );
	}
	map< tDataPoint, tDataPoint > mapClusterMapping;
	for ( typename set< const tDataPoint * >::const_iterator
			itrNotSubsumed = setNotSubsumed.begin();
			itrNotSubsumed != setNotSubsumed.end(); itrNotSubsumed++ ){
		
		//point is its own cluster center
		mapClusterMapping.insert( pair< tDataPoint, tDataPoint >(
			**itrNotSubsumed, **itrNotSubsumed ) );
	}
	
	DEBUG_OUT_L2(<<"evalue subsuming points"<<endl<<flush);
	//while all data points are not subsumed
	bool bSomeDataPointsToSubsume = true;
	while ( bSomeDataPointsToSubsume ){
		
		bSomeDataPointsToSubsume = false;
		/*erase all data points, which don't subsume, and add them to ther
		cluster data point*/
		set< const tDataPoint * > setSubsumed;
		for ( typename typeMapSubsum::iterator itrDataPoint = mapSubsum.begin();
				itrDataPoint != mapSubsum.end(); itrDataPoint++ ){
			
			if ( itrDataPoint->second.first.empty() ){
				//data point don't subsume any other data points
				if ( itrDataPoint->second.second.empty() ){
					//error: data point not subsumed or subsuming -> skip it
					continue;
				}
				//subsume point and mark it as subsumed
				const tDataPoint * pSubsumedDataPoint = itrDataPoint->first;
				
				setSubsumed.insert( pSubsumedDataPoint );
				
				map< const tDataPoint *, double > & mapSubsumingPoints =
					itrDataPoint->second.second;
				//evalue data point, which subsumes the actual point
				double dMaxS = 0;
				const tDataPoint * pDataPointWithMaxS = NULL;
				for ( typename map< const tDataPoint *, double >::const_iterator
						itrSubsumingDataPoint = mapSubsumingPoints.begin();
						itrSubsumingDataPoint != mapSubsumingPoints.end();
						itrSubsumingDataPoint++ ){
					
					if ( dMaxS < itrSubsumingDataPoint->second ){
						dMaxS = itrSubsumingDataPoint->second;
						pDataPointWithMaxS = itrSubsumingDataPoint->first;
					}
				}
				//erase data point from all not subsuming data points
				for ( typename map< const tDataPoint *, double >::const_iterator
						itrSubsumingDataPoint = mapSubsumingPoints.begin();
						itrSubsumingDataPoint != mapSubsumingPoints.end();
						itrSubsumingDataPoint++ ){
					
					const tDataPoint * pSubsumingDataPoint =
						itrSubsumingDataPoint->first;
					
					if ( pDataPointWithMaxS == pSubsumingDataPoint ){
						//the subsuming data point -> skip it
						continue;
					}
					mapSubsum[ pSubsumingDataPoint ].first.erase( pSubsumedDataPoint );
				}
			}//else data point subsume other data points
		}
		if ( ! setSubsumed.empty() ){
			//ther are data points to subsume
			bSomeDataPointsToSubsume = true;
		}
		//remove subsumed data points, from the mapSubsum
		for ( typename set< const tDataPoint * >::iterator
				itrNotSubsumed = setSubsumed.begin();
				itrNotSubsumed != setSubsumed.end(); itrNotSubsumed++ ){
			
			//erase subsumed data point
			mapSubsum.erase( *itrNotSubsumed );
		}
	}
	//create the cluster mapping
	DEBUG_OUT_L2(<<"create the cluster mapping"<<endl<<flush);
	for ( typename typeMapSubsum::iterator itrDataPoint = mapSubsum.begin();
			itrDataPoint != mapSubsum.end(); itrDataPoint++ ){
		
		//point is center of its own cluster
		const tDataPoint * pClusterCenterDataPoint = itrDataPoint->first;
		mapClusterMapping.insert( pair< tDataPoint, tDataPoint >(
			*pClusterCenterDataPoint, *pClusterCenterDataPoint ) );
		//add all connections for subsumed data to cluster
		map< const tDataPoint *, double > & mapSubsumedPoints =
			itrDataPoint->second.first;
		
		for ( typename map< const tDataPoint *, double >::const_iterator
				itrSubsumdDataPoint = mapSubsumedPoints.begin();
				itrSubsumdDataPoint != mapSubsumedPoints.end();
				itrSubsumdDataPoint++ ){
			
			mapClusterMapping.insert( pair< tDataPoint, tDataPoint >(
				*(itrSubsumdDataPoint->first), *pClusterCenterDataPoint ) );
		}
	}
	
#endif //FEATURE_NCLUSTER_CLUSTER_IN_ONE_STEP
	DEBUG_OUT_L1(<<"fib::algorithms::nCluster::cluster( #mapData="<<mapData.size()<<", evaluePoints ) done"<<endl);
	return mapClusterMapping;
}




#endif //___N_CLUSTER_CPP__









