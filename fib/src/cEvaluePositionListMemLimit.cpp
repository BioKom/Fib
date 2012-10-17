/**
 * @class cEvaluePositionListMemLimit
 * file name: cEvaluePositionListMemLimit.cpp
 * @author Betti Oesterholz
 * @date 30.04.2010
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
 */
/*
History:
30.04.2010  Oesterholz  created
*/

#include "cEvaluePositionListMemLimit.h"


using namespace fib;


/**
 * standardconstructor
 *
 * @param ulInMaximalPointsAddToList The number of positions, which
 * 	should be added to the positionslist, befor it is sorted and
 * 	reduced. (@see ulMaximalPointsAddToList)
 * @param pInVecDomainDimension The dimension domain for the positions.
 * 	No position outside this domain will be added.
 * 	If NULL no check will be executed. (@see pVecDomainDimension)
 * @param bInDeleteEmptyPoints if true points without properties will be
 * 	deleted when the positionslist is reduced, else (if false) points
 * 	without properties won't be deleted (@see bDeleteEmptyPoints)
 */
cEvaluePositionListMemLimit::cEvaluePositionListMemLimit(
		unsigned long long ulInMaximalPointsAddToList,
		const cDomainVectorBasis * pInVecDomainDimension,
		bool bInDeleteEmptyPoints ):
		cEvaluePositionList(),
		ulMaximalPointsAddToList( ulInMaximalPointsAddToList ),
		ulNewPositionsInserted( 0 ),
		bDeleteEmptyPoints( bInDeleteEmptyPoints ){
	
	if ( pInVecDomainDimension ){
		pVecDomainDimension = pInVecDomainDimension->clone();
	}else{
		pVecDomainDimension = NULL;
	}
}


/**
 * copyconstructor
 *
 * @param evaluePositionListMemLimit the cEvaluePositionListMemLimit
 * 	object to copy
 */
cEvaluePositionListMemLimit::cEvaluePositionListMemLimit(
		const cEvaluePositionListMemLimit & evaluePositionListMemLimit ):
		cEvaluePositionList( evaluePositionListMemLimit ),
		ulMaximalPointsAddToList( evaluePositionListMemLimit.ulMaximalPointsAddToList ),
		bDeleteEmptyPoints( evaluePositionListMemLimit.bDeleteEmptyPoints ){
	
	if ( evaluePositionListMemLimit.pVecDomainDimension ){
		pVecDomainDimension = evaluePositionListMemLimit.pVecDomainDimension->clone();
	}else{
		pVecDomainDimension = NULL;
	}
}


/**
 * destructor
 */
cEvaluePositionListMemLimit::~cEvaluePositionListMemLimit(){

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
bool cEvaluePositionListMemLimit::evaluePosition( const cVectorPosition & vPosition,
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
	
	//check if the positionslist should be reduced and sorted
	if ( ulMaximalPointsAddToList < ulNewPositionsInserted ){
		//sort and reduce the positions data
		ulNewPositionsInserted = 0;
		sortPositionsData( bDeleteEmptyPoints );
	}
	ulNewPositionsInserted++;

	return true;
}
