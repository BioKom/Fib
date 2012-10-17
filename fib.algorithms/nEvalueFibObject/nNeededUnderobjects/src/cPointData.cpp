/**
 * @class cPointData
 * file name: cPointData.cpp
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


#include "cPointData.h"

using namespace fib::algorithms::nEvalueFibObject::nNeededUnderobjects;


/**
 * standradconstructor
 */
cPointData::cPointData():bPointNeeded( false ){
	//nothing to do
}


/**
 * This method returns if this point is needed.
 * call evalueIfNeeded() befor using this method
 * @see bPointNeeded
 *
 * @return true if this point is needed, else false
 */
bool cPointData::isNeeded() const{
	
	return bPointNeeded;
}


/**
 * @return true if this point is needed, else false
 */
bool cPointData::evalueIfNeeded(){
	
	//this point is needed, if it is needed on one position
	for ( list< cPositionData *>::const_iterator
			itrPosition = liPositionData.begin();
			itrPosition != liPositionData.end(); itrPosition++ ){
		
		if ( (*itrPosition)->isNeededPoint( this ) ){
			bPointNeeded = true;
			return true;
		}
	}//else this point is not needed on any position
	bPointNeeded = false;
	return false;
}





