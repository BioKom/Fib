/**
 * @class cPositionPointData
 * file name: cPositionPointData.cpp
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


#include "cPositionPointData.h"

#include "cPointData.h"


using namespace fib::algorithms::nEvalueFibObject::nNeededUnderobjects;


/**
 * Standardconstructor
 */
cPositionPointData::cPositionPointData():bPointNeeded( true ){
	//nothing to do
}


/**
 * This method marks the properties as not needed, which are not
 * needed because the background is the same and can replace them.
 *
 * @param liRemainingBackgroundProperties the remaining background properties,
 * 	all properties, wich are overwritten by a different property
 * 	on this position point are removed
 * @return true if some property was marked as not needed else false
 */
bool cPositionPointData::markNotNeededWithBackground(
		list< cVectorProperty > & liRemainingBackgroundProperties ){
	
	/*check if the remaining not overwritten properties are not
	needed because of the backgraund propertie*/
	
	bool bSomeMarked = false;
	/*check if a property is overwirtten by a later added property*/
	for ( list< cPositionPropertieData >::iterator
			itrPropertyPosition = liProperties.begin();
			itrPropertyPosition != liProperties.end(); itrPropertyPosition++ ){
		
		//this property will be overwritten
		if ( ! (itrPropertyPosition->pProperty->bPropertyNeeded) ){
			continue;
		}
		const cVectorProperty * pActualProperty = &(itrPropertyPosition->vecProperty);
		cTypeProperty * typeOfProperty = (cTypeProperty*)(
			pActualProperty->getElementType());
		list<cTypeProperty> liOverwritenTyps = typeOfProperty->getOverwritenTyps();
		if ( ! liOverwritenTyps.empty() ){
			//for all background properties
			for ( list<cVectorProperty>::iterator
					itrPropertiesBackground = liRemainingBackgroundProperties.begin();
					itrPropertiesBackground != liRemainingBackgroundProperties.end(); ){
				
				if ( (itrPropertyPosition->bPropertyNeeded) &&
						(*itrPropertiesBackground) == (*pActualProperty) ){
						/*if this property is (needed and) equal to the background
					-> it is not needed*/
					itrPropertyPosition->bPropertyNeeded = false;
					bSomeMarked = true;
				}
				
				//check if the background property is overwritten
				cTypeProperty * typeOfPropertyBackground = (cTypeProperty*)(
					itrPropertiesBackground->getElementType());
				bool bRemoveBackgroundProperty = false;
				for ( list<cTypeProperty>::iterator itrPropertyType = liOverwritenTyps.begin();
						itrPropertyType != liOverwritenTyps.end(); itrPropertyType++ ){
					
					if ( typeOfPropertyBackground->equalElementType( *itrPropertyType ) ){
						/*the background property is overwritten
						-> remove it, because it can't be used later*/
						bRemoveBackgroundProperty = true;
						break;
					}
				}
				if ( bRemoveBackgroundProperty ){
					/*the background property is overwritten
					-> remove it, because it can't be used later*/
					itrPropertiesBackground =
						liRemainingBackgroundProperties.erase( itrPropertiesBackground );
				}else{//check next background property
					itrPropertiesBackground++;
				}
				delete typeOfPropertyBackground;
			}
		}
		delete typeOfProperty;
	}
	return bSomeMarked;
}


/**
 * This method checks if the given property is needed for this point position.
 * Attention: Call @see markNotNeeded() and
 * 	@see markNotNeededWithBackground() befor using this method.
 *
 * @param pProperty the property data for which to check, if it is needed
 * @return true if the given property is needed for this position, else false
 */
bool cPositionPointData::isNeededProperty( const cPropertyData * pProperty ) const{
	
	for ( list< cPositionPropertieData >::const_iterator
			itrPropertyData = liProperties.begin();
			itrPropertyData != liProperties.end(); itrPropertyData++ ){
	
		if ( (itrPropertyData->pProperty == pProperty) &&
				(itrPropertyData->bPropertyNeeded) ){
			//the property is needed
			return true;
		}
	}
	return false;
}


/**
 * This method checks if the given property is needed for this point position.
 * Attention: Call @see markNotNeeded() and
 * 	@see markNotNeededWithBackground() befor using this method.
 *
 * @param pInPoint the point data for which to check, if it is needed
 * @return true if the given point is needed for this position, else false
 */
bool cPositionPointData::isNeededPoint( const cPointData * pInPoint ){
		
		if ( pInPoint != pPoint ){
			//not this point -> point not needed for this position
			return false;
		}//else this is the correct point
		//if a property on this point is needed -> the point is needed
		for ( list< cPositionPropertieData >::const_iterator
				itrPropertyData = liProperties.begin();
				itrPropertyData != liProperties.end(); itrPropertyData++ ){
		
			if ( itrPropertyData->bPropertyNeeded ){
				//the property is needed
				bPointNeeded = true;
				return true;
			}
	}//no property needed -> the point on this position is not needed
	bPointNeeded = false;
	return false;
}





