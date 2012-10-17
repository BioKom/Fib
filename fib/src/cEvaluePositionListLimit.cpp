/**
 * @class cEvaluePositionListLimit
 * file name: cEvaluePositionListLimit.cpp
 * @author Betti Oesterholz
 * @date 02.09.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the class for evaluing fib -objects and storing
 * the evalued data into a list.
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
 * This file contains the class for evaluing fib -objects and storing
 * the evalued data into a list (@see liEvaluedPositionData).
 * When the fib -object is evalued this method is called every time a
 * pointelement is reached. The parameter for the method are the
 * positionsvector of the point and properties of the point.
 *
 * This class restricts the memory and time used to evalue and store the
 * evalued positionsdata.
 */
/*
History:
02.09.2010  Oesterholz  created
*/

#include "cEvaluePositionListLimit.h"


using namespace fib;


/**
 * standardconstructor
 *
 * @param ulInSortEverAddedPointsList The number of positions, which
 * 	should be added to the positionslist, befor it is sorted and
 * 	reduced. (@see ulSortEverAddedPointsList) If 0 this option is
 * 	deactivated (no check will be executed).
 * @param pInVecDomainDimension The dimension domain for the positions.
 * 	No position outside this domain will be added.
 * 	If NULL no check will be executed. (@see pVecDomainDimension)
 * @param bInDeleteEmptyPoints if true points without properties will be
 * 	deleted when the positionslist is reduced, else (if false) points
 * 	without properties won't be deleted (@see bDeleteEmptyPoints)
 * @param ulInMaxPointsInList the maximum number of points in the (sorted)
 * 	list of the points evalued (@see liEvaluedPositionData); if the
 * 	sorted list @see liEvaluedPositionData has more than ulInMaxPointsInList
 * 	point, the evalue call will return false;
 * 	If ulInMaxPointsInList is 0 this option is deactivated (no check
 * 	will be executed). (@see ulMaxPointsInList)
 * @param ulInMaxEvalueCalls the maximum number of calls in the
 * 	@see evaluePosition() will be called befor it returns false; if the
 * 	evaluePosition() was called more than ulInMaxEvalueCalls times, it
 * 	will return false;
 * 	If ulInMaxEvalueCalls is 0 this option is deactivated (no check
 * 	will be executed). (@see ulMaxEvalueCalls)
 */
cEvaluePositionListLimit::cEvaluePositionListLimit(
		const unsigned long long ulInSortEverAddedPointsList,
		const cDomainVectorBasis * pInVecDomainDimension,
		const bool bInDeleteEmptyPoints,
		const unsigned long long ulInMaxPointsInList,
		const unsigned long long ulInMaxEvalueCalls ):
		cEvaluePositionList(),
		ulSortEverAddedPointsList( ulInSortEverAddedPointsList ),
		ulNewPositionsInsertedAfterLastSort( 0 ),
		bDeleteEmptyPoints( bInDeleteEmptyPoints ),
		ulMaxPointsInList( ulInMaxPointsInList ),
		ulMaxEvalueCalls( ulInMaxEvalueCalls ),
		ulEvalueCalls( 0 ){
	
	if ( pInVecDomainDimension ){
		pVecDomainDimension = pInVecDomainDimension->clone();
	}else{
		pVecDomainDimension = NULL;
	}
}


/**
 * copyconstructor
 *
 * @param evaluePositionListLimit the cEvaluePositionListLimit
 * 	object to copy
 */
cEvaluePositionListLimit::cEvaluePositionListLimit(
		const cEvaluePositionListLimit & evaluePositionListLimit ):
		cEvaluePositionList( evaluePositionListLimit ),
		ulSortEverAddedPointsList( evaluePositionListLimit.ulSortEverAddedPointsList ),
		ulNewPositionsInsertedAfterLastSort( 0 ),
		bDeleteEmptyPoints( evaluePositionListLimit.bDeleteEmptyPoints ),
		ulMaxPointsInList( evaluePositionListLimit.ulMaxPointsInList ),
		ulMaxEvalueCalls( evaluePositionListLimit.ulMaxEvalueCalls ),
		ulEvalueCalls( 0 ){
	
	if ( evaluePositionListLimit.pVecDomainDimension ){
		pVecDomainDimension = evaluePositionListLimit.pVecDomainDimension->clone();
	}else{
		pVecDomainDimension = NULL;
	}
}


/**
 * destructor
 */
cEvaluePositionListLimit::~cEvaluePositionListLimit(){

	if ( pVecDomainDimension ){
		delete pVecDomainDimension;
	}
}


/**
 * The method with wich the evalued points with ther properties are
 * inserted. Everytime a point (to evalue) is reached in the
 * evaluation, this method is called with the position and the
 * properties of the point and stores the copies of this data
 * to the end of the list @see liEvaluedPositionData .
 *
 * @see liEvaluedPositionData
 * @param vPosition the position of the point, which is evalued
 * @param vProperties a list of the properties of the point
 */
bool cEvaluePositionListLimit::evaluePosition( const cVectorPosition & vPosition,
		const list<cVectorProperty> & vProperties ){

#ifdef TEST
	ulCountOfEvalueMethodCalled++;
	if ( lNumberOfTrueEvalueCalls != -1 ){
		if ( lNumberOfTrueEvalueCalls == 0 ){
			return false;
		}
		lNumberOfTrueEvalueCalls--;
	}
#endif

	//replace variables with ther values
	pair< cVectorPosition, list< cVectorProperty > > paEvaluedData;
	paEvaluedData.first  = vPosition;
	paEvaluedData.second = vProperties;
	
	//replace position variables with ther values
	{
		const unsignedIntFib uiNumberOfElements = paEvaluedData.first.getNumberOfElements();
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= uiNumberOfElements; uiActualElement++ ){
			
			if ( paEvaluedData.first.isVariable( uiActualElement ) ){
				paEvaluedData.first.setValue( uiActualElement,
					paEvaluedData.first.getValue( uiActualElement ) );
			}
		}
	}
	if ( pVecDomainDimension ){
		//check if inside bounderies
		//discard if outside bounderis, but not if not element
		if ( ( paEvaluedData.first.getNumberOfElements() != 0 ) &&
				( ! ( pVecDomainDimension->isInBoundaries( paEvaluedData.first ) ) ) ){
			//position outside bounderies -> don't insert it
			if ( ulMaxEvalueCalls != 0 ){
				ulEvalueCalls++;
				if ( ulMaxEvalueCalls < ulEvalueCalls ){
					//maximum number of points reached
					return false;
				}
			}
			return true;
		}
	}
	//replace property variables with ther values
	for ( list<cVectorProperty>::iterator
				itrProperty = paEvaluedData.second.begin();
			itrProperty != paEvaluedData.second.end(); itrProperty++ ){
		
		const unsignedIntFib uiNumberOfElements = itrProperty->getNumberOfElements();
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= uiNumberOfElements; uiActualElement++ ){
			
			if ( itrProperty->isVariable( uiActualElement ) ){
				itrProperty->setValue( uiActualElement,
					itrProperty->getValue( uiActualElement ) );
			}
		}
	}

	liEvaluedPositionData.push_back( paEvaluedData );
	
	//check if the positionslist should be reduced and sorted (@see ulSortEverAddedPointsList)
	if ( ulSortEverAddedPointsList != 0 ){
		if ( ulSortEverAddedPointsList < ulNewPositionsInsertedAfterLastSort ){
			//sort and reduce the positions data
			ulNewPositionsInsertedAfterLastSort = 0;
			sortPositionsData( bDeleteEmptyPoints );
		}
		ulNewPositionsInsertedAfterLastSort++;
	}
	//check if the maximum number of point are reached (@see ulMaxPointsInList)
	if ( ulMaxPointsInList != 0 ){
		if ( ulMaxPointsInList < liEvaluedPositionData.size() ){
			//sort and reduce the positions data and check again
			sortPositionsData( bDeleteEmptyPoints );
			if ( ulMaxPointsInList < liEvaluedPositionData.size() ){
				//maximum number of points reached
				return false;
			}
		}
	}
	//check if the maximum evaluePosition() calls wher reached (@see ulMaxEvalueCalls)
	if ( ulMaxEvalueCalls != 0 ){
		ulEvalueCalls++;
		if ( ulMaxEvalueCalls < ulEvalueCalls ){
			//maximum number of points reached
			return false;
		}
	}

	return true;
}














