/**
 * @class cPointData
 * file name: cPointData.h
 * @author Betti Oesterholz
 * @date 06.12.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the point data.
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
 * This class represents the point data for evaluating, if a point
 * is needed.
 *
 */
/*
History:
06.12.2010  Oesterholz  created
*/


#ifndef ___N_NEEDED_UNDEROBJECTS_C_POINT_DATA_H__
#define ___N_NEEDED_UNDEROBJECTS_C_POINT_DATA_H__


#include "version.h"

#include "cPositionData.h"

#include <list>


using namespace std;


namespace fib{
namespace algorithms{
namespace nEvalueFibObject{
namespace nNeededUnderobjects{


class cPointData{

public:
	
	/**
	 * A list with the underobjects which contain the position /point for
	 * the position.
	 * The number of the higher underobjects should stand at the front
	 * of the list.
	 *
	 * @see cFibElement::elementPointToObjectPoints()
	 */
	list<unsignedIntFib> liUnderObjects;
	
	/**
	 * A list with the pointers to the position data wher the property is stored.
	 */
	list<cPositionData *> liPositionData;
	
	/**
	 * If true this property is needed, else not.
	 */
	bool bPointNeeded;
	
	/**
	 * standradconstructor
	 */
	cPointData();
	
	/**
	 * This method returns if this point is needed.
	 * call evalueIfNeeded() befor using this method
	 * it will return @see bPointNeeded
	 *
	 * @return true if this point is needed, else false
	 */
	bool isNeeded() const;

	/**
	 * This method evalues if this point is needed.
	 * it will set @see bPointNeeded
	 *
	 * @return true if this point is needed, else false
	 */
	bool evalueIfNeeded();


};//end class cPointData



}//end namespace nNeededUnderobjects
}//end namespace nEvalueFibObject
}//end namespace algorithms
}//end namespace fib



#endif //___N_NEEDED_UNDEROBJECTS_C_POINT_DATA_H__
