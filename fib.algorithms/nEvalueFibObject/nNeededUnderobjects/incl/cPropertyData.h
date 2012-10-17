/**
 * @class cPropertyData
 * file name: cPropertyData.h
 * @author Betti Oesterholz
 * @date 06.12.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the property data.
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
 * This class represents the property data for evaluating, if a property
 * is needed.
 *
 */
/*
History:
06.12.2010  Oesterholz  created
*/


#ifndef ___N_NEEDED_UNDEROBJECTS_C_PROPERTY_DATA_H__
#define ___N_NEEDED_UNDEROBJECTS_C_PROPERTY_DATA_H__


#include "version.h"

#include <list>

using namespace std;


namespace fib{
namespace algorithms{
namespace nEvalueFibObject{
namespace nNeededUnderobjects{

//cyclic dependencies
class cPositionData;

class cPropertyData{

public:
	
	/**
	 * A list with the pointers to the position data wher the property is stored.
	 */
	list< cPositionData *> liPositionData;
	
	/**
	 * If true this property is needed, else not.
	 */
	bool bPropertyNeeded;
	
	/**
	 * standradconstructor
	 */
	cPropertyData();
	
	/**
	 * @return true if this property is needed, else false
	 */
	bool isNeeded();


};//end class cPropertyData



}//end namespace nNeededUnderobjects
}//end namespace nEvalueFibObject
}//end namespace algorithms
}//end namespace fib



#endif //___N_NEEDED_UNDEROBJECTS_C_PROPERTY_DATA_H__
