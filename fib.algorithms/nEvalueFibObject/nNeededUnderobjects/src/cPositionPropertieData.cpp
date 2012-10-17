/**
 * @class cPositionPropertieData
 * file name: cPositionPropertieData.cpp
 * @author Betti Oesterholz
 * @date 08.12.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * he data for a fib-propertyelement on an specific point on an specific
 * position.
 * Helperclass for the @see cPositionPointData class.
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
 * he data for a fib-propertyelement on an specific point on an specific
 * position.
 *
 */
/*
History:
08.12.2010  Oesterholz  created
*/

#include "cPositionPropertieData.h"


using namespace fib::algorithms::nEvalueFibObject::nNeededUnderobjects;
using namespace fib;


/**
 * Standardconstructor
 */
cPositionPropertieData::cPositionPropertieData():
	vecProperty( 0, (cFibElement*)NULL ),bPropertyNeeded( true ){
	//nothing to do
}


/**
 * Parameterconstructor
 *
 * @param pInProperty a pointer to the property data for this
 * 	cPositionPropertieData object (@see pProperty)
 * @param vecInProperty the property vector for this
 * 	cPositionPropertieData object (@see pProperty);
 * 	Beware: all elements should be values
 */
cPositionPropertieData::cPositionPropertieData( cPropertyData * pInProperty,
		const fib::cVectorProperty & vecInProperty ):
		pProperty( pInProperty ), vecProperty( vecInProperty ),
		bPropertyNeeded( true ){
	//nothing to do
}





