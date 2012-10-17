/**
 * @class cPositionPointData
 * file name: cPositionPointData.h
 * @author Betti Oesterholz
 * @date 08.12.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class stores the data for a fib-pointelement on an specific
 * position.
 * Helperclass for the @see cPositionData class.
 *
 * Copyright (C) @c LGPL3 2010 Betti Oesterholz
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
 * This class stores the data for a fib-pointelement on an specific
 * position.
 *
 */
/*
History:
08.12.2010  Oesterholz  created
*/


#ifndef ___N_NEEDED_UNDEROBJECTS_C_POSITION_POINT_DATA_H__
#define ___N_NEEDED_UNDEROBJECTS_C_POSITION_POINT_DATA_H__


#include "version.h"

#include "cPositionPropertieData.h"

#include <list>

using namespace std;


namespace fib{
namespace algorithms{
namespace nEvalueFibObject{
namespace nNeededUnderobjects{

//cyclic dependencie
class cPointData;


class cPositionPointData{
public:
	
	/**
	 * The data for the pointelement.
	 */
	cPointData * pPoint;
	
	/**
	 * If true this position point is needed, else not.
	 * False, if non of it's properties is needed.
	 */
	bool bPointNeeded;
	
	/**
	 * The properties for this point position data.
	 */
	list< cPositionPropertieData > liProperties;
	
	
	/**
	 * Standardconstructor
	 */
	cPositionPointData();
	
	/**
	 * This method marks the properties as not needed, which are not
	 * needed because the background is the same and can replace them.
	 *
	 * @param liRemainingBackgroundProperties the remaining background properties,
	 * 	all properties, wich are overwritten by a different property
	 * 	on this position point are removed
	 * @return true if some property was marked as not needed else false
	 */
	bool markNotNeededWithBackground(
			list< cVectorProperty > & liRemainingBackgroundProperties );
	
	/**
	 * This method checks if the given property is needed for this point position.
	 * Attention: Call @see markNotNeeded() and
	 * 	@see markNotNeededWithBackground() befor using this method.
	 *
	 * @param pProperty the property data for which to check, if it is needed
	 * @return true if the given property is needed for this position, else false
	 */
	bool isNeededProperty( const cPropertyData * pProperty ) const;
	
	/**
	 * This method checks if the given property is needed for this point position.
	 * Attention: Call @see markNotNeeded() and
	 * 	@see markNotNeededWithBackground() befor using this method.
	 *
	 * @param pInPoint the point data for which to check, if it is needed
	 * @return true if the given point is needed for this position, else false
	 */
	bool isNeededPoint( const cPointData * pInPoint );
	
};//end class cPositionPointData



}//end namespace nNeededUnderobjects
}//end namespace nEvalueFibObject
}//end namespace algorithms
}//end namespace fib



#endif //___N_NEEDED_UNDEROBJECTS_C_POSITION_POINT_DATA_H__
