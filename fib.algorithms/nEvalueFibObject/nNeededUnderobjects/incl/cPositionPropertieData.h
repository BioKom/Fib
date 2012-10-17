/**
 * @class cPositionPropertieData
 * file name: cPositionPropertieData.h
 * @author Betti Oesterholz
 * @date 08.12.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class stores the data for a fib-propertyelement on an specific
 * point on an specific position.
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
 * This class stores the data for a fib-propertyelement on an specific
 * point on an specific position.
 *
 */
/*
History:
08.12.2010  Oesterholz  created
*/


#ifndef ___N_NEEDED_UNDEROBJECTS_C_POSITION_PROPERTY_DATA_H__
#define ___N_NEEDED_UNDEROBJECTS_C_POSITION_PROPERTY_DATA_H__


#include "version.h"

#include "cPropertyData.h"

#include "cVectorProperty.h"


namespace fib{
namespace algorithms{
namespace nEvalueFibObject{
namespace nNeededUnderobjects{


class cPositionPropertieData{
public:
	/**
	 * The data for the propertyelement.
	 */
	cPropertyData * pProperty;
	
	/**
	 * The vector with the property values.
	 */
	fib::cVectorProperty vecProperty;
	
	/**
	 * If true this property is needed, else not.
	 */
	bool bPropertyNeeded;
	
	/**
	 * Standardconstructor
	 */
	cPositionPropertieData();

	/**
	 * Parameterconstructor
	 *
	 * @param pInProperty a pointer to the property data for this
	 * 	cPositionPropertieData object (@see pProperty)
	 * @param vecInProperty the property vector for this
	 * 	cPositionPropertieData object (@see pProperty);
	 * 	Beware: all elements should be values
	 */
	cPositionPropertieData( cPropertyData * pInProperty,
			const fib::cVectorProperty & vecInProperty );

};//end class cPositionPropertieData



}//end namespace nNeededUnderobjects
}//end namespace nEvalueFibObject
}//end namespace algorithms
}//end namespace fib



#endif //___N_NEEDED_UNDEROBJECTS_C_POSITION_PROPERTY_DATA_H__
