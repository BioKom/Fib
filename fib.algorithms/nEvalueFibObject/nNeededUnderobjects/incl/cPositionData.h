/**
 * @class cPositionData
 * file name: cPositionData.h
 * @author Betti Oesterholz
 * @date 08.12.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class contains the data for one position.
 * Helperclass for the @see cEvalueUnderObjects class.
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
 * This class contains the data for one position.
 * Helperclass for the @see cEvalueUnderObjects class.
 *
 */
/*
History:
08.12.2010  Oesterholz  created
*/


#ifndef ___N_NEEDED_UNDEROBJECTS_C_POSITION_DATA_H__
#define ___N_NEEDED_UNDEROBJECTS_C_POSITION_DATA_H__


#include "version.h"

#include "cPositionPointData.h"

#include "cVectorProperty.h"

#include <list>

using std::list;


namespace fib{
namespace algorithms{
namespace nEvalueFibObject{
namespace nNeededUnderobjects{


class cPositionData{
public:
	
	/**
	 * A list with the evalued properties.
	 * Every overwritten property except the last can be deleted.
	 */
	list< cPositionPointData > liData;
	
	
	/**
	 * This method marks not needed properties .
	 * Every overwritten property except the last can be deleted.
	 *
	 * @return true if some property was marked as not needed, else false
	 */
	bool markNotNeeded();
	
	/**
	 * This method marks properties as not needed, which are not
	 * needed because the background is the same and can replace them.
	 *
	 * @param liBackgroundProperties the background properties
	 * @return true if some property was marked as not needed, else false
	 */
	bool markNotNeededWithBackground(
			const list< fib::cVectorProperty > & liBackgroundProperties );
	
	/**
	 * This method checks if the given property is needed for this position.
	 * Attention: Call @see markNotNeeded() and
	 * 	@see markNotNeededWithBackground() befor using this method.
	 *
	 * @param pProperty the property data for which to check, if it is needed
	 * @return true if the given property is needed, else false
	 */
	bool isNeededProperty( const cPropertyData * pProperty ) const;
	
	/**
	 * This method checks if the given point is needed for this position.
	 * Attention: Call @see markNotNeeded() befor using this method.
	 *
	 * @param pPoint the point data for which to check, if it is needed
	 * @return true if the given point is needed, else false
	 */
	bool isNeededPoint( const cPointData * pPoint );
	
	/**
	 * This method returns all properties of this position.
	 *
	 * @return a list with all property vectors of this position
	 */
	list< fib::cVectorProperty > getAllProperties() const;

};//class cPositionData



}//end namespace nNeededUnderobjects
}//end namespace nEvalueFibObject
}//end namespace algorithms
}//end namespace fib



#endif //___N_NEEDED_UNDEROBJECTS_C_POSITION_DATA_H__
