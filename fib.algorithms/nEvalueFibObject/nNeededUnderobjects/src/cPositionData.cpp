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


#include "cPositionData.h"

using namespace std;

using namespace fib::algorithms::nEvalueFibObject::nNeededUnderobjects;
using namespace fib;

/**
 * This method marks not needed properties .
 * Every overwritten property except the last can be deleted.
 *
 * @return true if some property was marked as not needed, else false
 */
bool cPositionData::markNotNeeded(){
		
	bool bSomeMarked = false;
	/*check if a property is overwirtten by a later added property*/
	bool bLastProperty = true;//for skipping the last property
	for ( list< cPositionPointData >::reverse_iterator
			itrData = liData.rbegin(); itrData != liData.rend();
			itrData++ ){
	
		list< cPositionPropertieData >::reverse_iterator
			itrPropertyCheck = itrData->liProperties.rbegin();
		if ( bLastProperty ){
			if ( itrPropertyCheck == itrData->liProperties.rend() ){
				//no properties for the point -> check next point
				continue;
			}
			//skip last property
			itrPropertyCheck++;
			bLastProperty = false;
		}
		for ( ; itrPropertyCheck != itrData->liProperties.rend();
				itrPropertyCheck++ ){
			
			if ( ! itrPropertyCheck->bPropertyNeeded ){
				//allready marked -> skip it
				continue;
			}
			const cVectorProperty * pActualProperty =
				&(itrPropertyCheck->vecProperty);
			cTypeProperty * typeOfProperty = (cTypeProperty*)(
				pActualProperty->getElementType());
			bool bNotOverwritten = true;
			
			//check the next property
			bool bCheckNextedProperty = false;
			for ( list< cPositionPointData >::reverse_iterator
					itrDataLater = liData.rbegin(); itrDataLater != liData.rend();
					itrDataLater++ ){
				for ( list< cPositionPropertieData >::reverse_iterator
						itrPropertyLater = itrDataLater->liProperties.rbegin();
						itrPropertyLater != itrDataLater->liProperties.rend();
						itrPropertyLater++ ){
					
					if (itrPropertyLater == itrPropertyCheck){
						//the checked property was reached
						bCheckNextedProperty = true;
						break;
					}
					//this property will be overwritten
					if ( ! (itrPropertyLater->pProperty->bPropertyNeeded) ){
						continue;
					}
					
					const cVectorProperty * pActualPropertyLater =
						&(itrPropertyLater->vecProperty);
					cTypeProperty * typeOfPropertyLater = (cTypeProperty*)(
						pActualPropertyLater->getElementType());
					/*if this is a property that overwrite properties of the same type
					-> mark properties that this overwrites from the property list*/
					const list<cTypeProperty> liOverwritenTyps =
						typeOfPropertyLater->getOverwritenTyps();
					
					for ( list<cTypeProperty>::const_iterator itrPropertyType = liOverwritenTyps.begin();
							itrPropertyType != liOverwritenTyps.end(); itrPropertyType++ ){
						
						if ( typeOfProperty->equalElementType( *itrPropertyType ) ){
							bNotOverwritten = false;
							break;
						}
					}
					delete typeOfPropertyLater;
					if ( ! bNotOverwritten ){
						//else the property is overwriten -> it is not needed
						itrPropertyCheck->bPropertyNeeded = false;
						bSomeMarked = true;
						//check the next propertyvector
						bCheckNextedProperty = true;
						break;
					}
				}
				if ( bCheckNextedProperty ){
					break;
				}
			}
			delete typeOfProperty;
		}
	}
	return bSomeMarked;
}


/**
 * This method marks properties as not needed, which are not
 * needed because the background is the same and can replace them.
 *
 * @param liBackgroundProperties the background properties
 * @return true if some property was marked as not needed, else false
 */
bool cPositionData::markNotNeededWithBackground(
		const list< cVectorProperty > & liBackgroundProperties ){
	
	list< cVectorProperty > liRemainingBackgroundProperties =
		liBackgroundProperties;
	
	bool bChanges = false;
	for ( list< cPositionPointData >::iterator itrData = liData.begin();
			itrData != liData.end(); itrData++ ){
	
		bChanges |= itrData->markNotNeededWithBackground(
			liRemainingBackgroundProperties );
	}
	return bChanges;
}


/**
 * This method checks if the given property is needed for this position.
 * Attention: Call @see markNotNeeded() and
 * 	@see markNotNeededWithBackground() befor using this method.
 *
 * @param pProperty the property data for which to check, if it is needed
 * @return true if the given property is needed, else false
 */
bool cPositionData::isNeededProperty( const cPropertyData * pProperty ) const{
	
	for ( list< cPositionPointData >::const_iterator itrData = liData.begin();
			itrData != liData.end(); itrData++ ){
	
		if ( itrData->isNeededProperty( pProperty ) ){
			//the property is needed
			return true;
		}
	}
	return false;
}


/**
 * This method checks if the given point is needed for this position.
 * Attention: Call @see markNotNeeded() befor using this method.
 *
 * @param pPoint the point data for which to check, if it is needed
 * @return true if the given point is needed, else false
 */
bool cPositionData::isNeededPoint( const cPointData * pPoint ){
	
	for ( list< cPositionPointData >::iterator itrData = liData.begin();
			itrData != liData.end(); itrData++ ){
	
		if ( itrData->isNeededPoint( pPoint ) ){
			//the point is needed
			return true;
		}
	}
	return false;
}


/**
 * This method returns all properties of this position.
 *
 * @return a list with all property vectors of this position
 */
list< cVectorProperty > cPositionData::getAllProperties() const{
	
	list< cVectorProperty > liAllProperties;
	for ( list< cPositionPointData >::const_iterator itrData = liData.begin();
			itrData != liData.end(); itrData++ ){
		
		for( list< cPositionPropertieData >::const_iterator
				itrProperty = itrData->liProperties.begin();
				itrProperty != itrData->liProperties.end(); itrProperty++ ){
			
			liAllProperties.push_back(  itrProperty->vecProperty );
		}
	}
	return liAllProperties;
}






