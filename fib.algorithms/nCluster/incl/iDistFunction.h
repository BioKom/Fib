/**
 * @class iDistFunction
 * file name: iDistFunction.h
 * @author Betti Oesterholz
 * @date 17.03.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the interface for evaluing a distance of two data points.
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
 * This file contains the interface for evaluing a distance of two data points.
 * Every class which implements this interface have to implement the operator().
 * This operator should evalue the distance for two data points.
 */
/*
History:
17.03.2011  Oesterholz  created
*/

#ifndef ___I_DIST_FUNCTION__
#define ___I_DIST_FUNCTION__

#include "version.h"


namespace fib{

namespace algorithms{

namespace nCluster{

template< class tDataPoint >
class iDistFunction{
public:
	
	/**
	 * pure virtual destructor
	 */
	virtual ~iDistFunction(){
		//nothing to do
	}
	
	/**
	 * This function should evalue the distance of two data points.
	 *
	 * @param dataPoint1 the first data point to evalue the distance to
	 * @param dataPoint2 the second data point to evalue the distance from
	 * @return a value for the distance betwean dataPoint1 and dataPoint2
	 */
	virtual double operator() ( const tDataPoint & dataPoint1,
		const tDataPoint & dataPoint2 ) const = 0;

};//class iDistFunction


};//end namespace nCluster
};//end namespace algorithms
};//end namespace fib


#endif //___I_DIST_FUNCTION__




