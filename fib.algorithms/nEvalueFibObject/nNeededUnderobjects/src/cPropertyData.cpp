/**
 * @class cPropertyData
 * file name: cPropertyData.cpp
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

#include "cPropertyData.h"

#include "cPositionData.h"


using namespace fib::algorithms::nEvalueFibObject::nNeededUnderobjects;



/**
 * standradconstructor
 */
cPropertyData::cPropertyData():bPropertyNeeded( false ){
	//nothing to do
}


/**
 * @return true if this property is needed, else false
 */
bool cPropertyData::isNeeded(){
	
	//this property is needed, if it is needed on one position
	for ( list< cPositionData *>::const_iterator
			itrPosition = liPositionData.begin();
			itrPosition != liPositionData.end(); itrPosition++ ){
		
		if ( (*itrPosition)->isNeededProperty( this ) ){
			bPropertyNeeded = true;
			return true;
		}
	}//else this property is not needed on any position
	bPropertyNeeded = false;
	return false;
}




