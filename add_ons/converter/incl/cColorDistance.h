/**
 * @class cColorDistance
 * file name: cColorDistance.h
 * @author Betti Oesterholz
 * @date 18.03.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the implementation for evaluing a distance of two colors.
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
 * This file contains the implementation for evaluing a distance of two colors.
 * The distance of two colors is the sum of ther element distances.
 */
/*
History:
18.03.2011  Oesterholz  created
*/

#ifndef ___C_COLOR_DISTANCE__
#define ___C_COLOR_DISTANCE__

#include "version.h"
#include "iDistFunction.h"


namespace nConvertToFib{


class cColorDistance: public fib::algorithms::nCluster::iDistFunction< vector< unsigned int > >{
public:
	
	/**
	 * destructor
	 */
	virtual ~cColorDistance(){
		//nothing to do
	}
	
	/**
	 * This function evalue the distance of two colors.
	 * The distance of two colors is the sum of ther element distances.
	 *
	 * @param color1 the first color to evalue the distance to
	 * @param color2 the second color to evalue the distance from
	 * @return a value for the distance betwean color1 and color2
	 */
	virtual double operator() ( const vector< unsigned int > & color1,
			const vector< unsigned int > & color2 ) const{
		
		const unsigned int uiDimensions = min( color1.size(), color2.size() );
		
		unsigned long ulDistance = 0;
		for ( unsigned int uiActualDimension  = 0;
				uiActualDimension < uiDimensions; uiActualDimension++ ){
			
			ulDistance += std::abs( ((int)(color1[ uiActualDimension ])) -
				((int)(color2[ uiActualDimension ])) );
		}
		return ulDistance;
	}


};//class cColorDistance


};//end namespace nConvertToFib


#endif //___C_COLOR_DISTANCE__



