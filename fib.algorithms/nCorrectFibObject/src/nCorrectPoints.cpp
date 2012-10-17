/**
 * @file nCorrectPoints
 * file name: nCorrectPoints.cpp
 * @author Betti Oesterholz
 * @date 18.10.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies functions for correcting points in fib -objects.
 * Copyright (C) @c GPL3 2010 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (GPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This header specifies functions for correcting points in fib -objects.
 */
/*
History:
18.10.2010  Oesterholz  created
*/


#ifndef ___N_CORRECT_POINTS_CPP__
#define ___N_CORRECT_POINTS_CPP__

#include "nCorrectPoints.h"

#include "cFibElement.h"
#include "cList.h"
#include "cTypeDimension.h"
#include "cDomains.h"
#include "cDomain.h"
#include "cDomainVectorBasis.h"
#include "cEvaluePositionList.h"
#include "cEvaluePositionListLimit.h"

#include <cmath>
#include <algorithm>

using namespace fib::algorithms::nCorrectFibObject::nCorrectPoints;
using namespace fib;



/**
 * This function corrects the wron points in pToCorrectFibObject and
 * returns corrected fib -objects.
 * For every entry in this list liDistancesCountedWrong a corrected
 * fib -object is given back.
 * Every point in the evalued pToCorrectFibObject, wich properties
 * have a greater distance as the n'th entry, in the sorted and
 * uniqe liDistancesCountedWrong, will be included in the n'th
 * returned fib -object.
 * This function will ignore points, wich are background point in both
 * the given list liPointWithPropertiesOrginal and fib -object
 * pToCorrectFibObject.
 *
 * @param liPointWithPropertiesOrginal a list with points and ther
 * 	properties, wich are correct
 * @param pToCorrectFibObject the fib -object to correct
 * @param liDistancesCountedWrong the list of distances of properties,
 * 	till which a point is not wrong;
 * 	for every entry in this list  a corrected fib -object is given back;
 * 	every point in the evalued pToCorrectFibObject, wich properties
 * 	have a greater distance as the n'th entry, in the sorted and
 * 	uniqe liDistancesCountedWrong, will be included in the n'th
 * 	returned fib -object
 * @return a list with the corrected fib -objects;
 * 	the first element of the returned list is the changed pToCorrectFibObject
 */
list<cFibElement *> fib::algorithms::nCorrectFibObject::nCorrectPoints::replaceWrongPoints(
		const list< pair< cVectorPosition, list< cVectorProperty > > > & liPointWithPropertiesOrginal,
		cFibElement * pToCorrectFibObject, list<doubleFib> liDistancesCountedWrong ){
	
	
	DEBUG_OUT_L2( <<"fib::algorithms::nCorrectFibObject::nCorrectPoints::replaceWrongPoints( liPointWithPropertiesOrginal, liDistancesCountedWrong ) started "<<endl );
	
	liDistancesCountedWrong.sort();
	liDistancesCountedWrong.unique();//remove double elements
	
	list<cFibElement *> liCorretedFibObjects;
	if ( pToCorrectFibObject == NULL ){
		//nothing to correct
		return liCorretedFibObjects;
	}
	if ( liDistancesCountedWrong.empty() ){
		//nothing to do
		return liCorretedFibObjects;
	}
	
	liCorretedFibObjects.push_back( pToCorrectFibObject );
	
	//evalue the values for the dimensions
	cDomains validDomains = pToCorrectFibObject->getValidDomains();
	cDomain * pDomainDimension = validDomains.getDomainForElement( cTypeDimension() );
	
	bool bStandardDimensionDomain = false;
	if ( pDomainDimension == NULL ){
		pDomainDimension = cTypeDimension().getStandardDomain();
		bStandardDimensionDomain = true;
	}
	const cDomainVectorBasis * pVecDomainDimension =
		(cDomainVectorBasis*)pDomainDimension;
	
	const unsignedLongFib ulNumberOfPoints = liPointWithPropertiesOrginal.size();
	cEvaluePositionListLimit evaluedPositionData( ulNumberOfPoints * 2,
		pVecDomainDimension, true, 0, ulNumberOfPoints * 64 );

	const bool bObjectEvalued = pToCorrectFibObject->evalueObjectSimple( evaluedPositionData );
	if ( ! bObjectEvalued ){
		DEBUG_OUT_EL1( <<"Error: The given fib -object couldn't be evalued."<<endl );
		return liCorretedFibObjects;
	}
	

	
	//TODO for fast evaluation: case if ( liDistancesCountedWrong.size() == 1)
		//case if ( liDistancesCountedWrong == 0.0 )
		
		//else
		
	//else
	
	while ( liCorretedFibObjects.size() < liDistancesCountedWrong.size() ){
		liCorretedFibObjects.push_back( pToCorrectFibObject->clone() );
	}
	
	//replace wrong points ( cFibObjectFitnessBasicAlgorithm::getDistance() used)
	
	list< pair< cVectorPosition, list< cVectorProperty > > > &
		liPointWithProperties = evaluedPositionData.liEvaluedPositionData;
	
	cEvaluePositionList::sortPositionsData( & liPointWithProperties );
	
	list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
		itrPositionOriginal = liPointWithPropertiesOrginal.begin();
	list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
		itrPositionGiven = liPointWithProperties.begin();
	
	//list with the background properties
	list< cVectorProperty > liBackgroundPropertiesOriginal;
	list< cVectorProperty > liBackgroundPropertiesGiven;
	
	//evalue the background properties and ignore the background properties
	if ( ( ! liPointWithPropertiesOrginal.empty() ) &&
			(itrPositionOriginal->first.getNumberOfElements() == 0) ){
		
		liBackgroundPropertiesOriginal = itrPositionOriginal->second;
		itrPositionOriginal++;
	}
	if ( ( ! liPointWithProperties.empty() ) &&
			( itrPositionGiven->first.getNumberOfElements() == 0 ) ){
		
		liBackgroundPropertiesGiven = itrPositionGiven->second;
		itrPositionGiven++;
	}
	
	doubleFib dDistance = 0.0;
	const cVectorPosition * pNewPosition = NULL;
	
	while ( (itrPositionOriginal != liPointWithPropertiesOrginal.end()) ||
			(itrPositionGiven != liPointWithProperties.end()) ){
		//for every position in the original fib -object
		
		list< cVectorProperty > liOriginalProperties;
		
		if ( itrPositionGiven == liPointWithProperties.end() ){
			/*if equivallent position is not in the given fib -object
			-> compare original positions properties against given background*/
			//if no equivallent background properties add to nullvector
			if ( ! pVecDomainDimension->isElement( itrPositionOriginal->first ) ){
				//position not in dimension bounderies -> skip it
				itrPositionOriginal++;
				continue;
			}
			liOriginalProperties = cEvaluePositionList::mergeProperties(
					itrPositionOriginal->second, liBackgroundPropertiesOriginal );
			
			dDistance = cEvaluePositionList::distanceOfProperties(
				liOriginalProperties, liBackgroundPropertiesGiven );
			
			pNewPosition = &(itrPositionOriginal->first);
			itrPositionOriginal++;
		}else if ( itrPositionOriginal == liPointWithPropertiesOrginal.end() ){
			//for points in the given fib -object but not in the original fib -object
			if ( ! pVecDomainDimension->isElement( itrPositionGiven->first ) ){
				//position not in dimension bounderies -> skip it
				itrPositionGiven++;
				continue;
			}//if inside dimension bounderies
			
			/*add differnce to original background properties, if existing,
			or the nullvector*/
			liOriginalProperties = liBackgroundPropertiesOriginal;
			
			dDistance = cEvaluePositionList::distanceOfProperties( liBackgroundPropertiesOriginal,
				cEvaluePositionList::mergeProperties( itrPositionGiven->second, liBackgroundPropertiesGiven ) );
			
			pNewPosition = &(itrPositionGiven->first);
			itrPositionGiven++;
		}else if ( cEvaluePositionList::lowerPositionPair( *itrPositionOriginal, *itrPositionGiven ) ){
			/*if equivallent position is not in the given fib -object
			-> compare original positions properties against given background*/
			if ( ! pVecDomainDimension->isElement( itrPositionOriginal->first ) ){
				//position not in dimension bounderies -> skip it
				itrPositionOriginal++;
				continue;
			}//if inside dimension bounderies
			
			//if no equivallent background properties add to nullvector
			liOriginalProperties = cEvaluePositionList::mergeProperties(
					itrPositionOriginal->second, liBackgroundPropertiesOriginal );
			
			dDistance = cEvaluePositionList::distanceOfProperties( 
				liOriginalProperties, liBackgroundPropertiesGiven );
		
			pNewPosition = &(itrPositionOriginal->first);
			itrPositionOriginal++;
		}else if ( cEvaluePositionList::lowerPositionPair( *itrPositionGiven, *itrPositionOriginal ) ){
			if ( ! pVecDomainDimension->isElement( itrPositionGiven->first ) ){
				//position not in dimension bounderies -> skip it
				itrPositionGiven++;
				continue;
			}//if inside dimension bounderies
			liOriginalProperties = liBackgroundPropertiesOriginal;
			
			dDistance = cEvaluePositionList::distanceOfProperties( liBackgroundPropertiesOriginal,
				cEvaluePositionList::mergeProperties( itrPositionGiven->second, liBackgroundPropertiesGiven ) );
			
			pNewPosition = &(itrPositionGiven->first);
			itrPositionGiven++;
		}else{//both are equal ( itrPositionOriginal->first == itrPositionGiven->first )
			//if equivallent position is in the given fib -object
			if ( ! pVecDomainDimension->isElement( itrPositionGiven->first ) ){
				//position not in dimension bounderies -> skip it
				itrPositionGiven++;
				itrPositionOriginal++;
				continue;
			}//if inside dimension bounderies
			liOriginalProperties = cEvaluePositionList::mergeProperties(
					itrPositionOriginal->second, liBackgroundPropertiesOriginal );
			
			dDistance = cEvaluePositionList::distanceOfProperties( liOriginalProperties,
				cEvaluePositionList::mergeProperties( itrPositionGiven->second, liBackgroundPropertiesGiven ) );

			pNewPosition = &(itrPositionGiven->first);
			itrPositionGiven++;
			itrPositionOriginal++;
		}

		//add point with properties if the distance is to great
		if ( liDistancesCountedWrong.front() < dDistance ){
			
			cFibElement * pCorrectPoint =
				cEvaluePositionList::toFibObject( *pNewPosition, liOriginalProperties );
			
			list< doubleFib >::const_iterator itrDistanceWrong =
				liDistancesCountedWrong.begin();
			list< cFibElement * >::iterator itrCorrectedFibObject =
				liCorretedFibObjects.begin();
			
			for ( ; (itrDistanceWrong != liDistancesCountedWrong.end()) &&
					( *itrDistanceWrong < dDistance );
					itrDistanceWrong++, itrCorrectedFibObject++ ){
				
				if ( itrDistanceWrong != liDistancesCountedWrong.begin() ){
					//create a new fib -object for the created points
					pCorrectPoint = pCorrectPoint->copy();
				}
				
				//TODO remember the next lists of the to correct fib -objects
				cList * pNextList = ((cList*)( (*itrCorrectedFibObject)->getNextFibElement( 'l' ) ) );
				if ( pNextList ){
					//add line to the end of the founded listelement
					pNextList->addUnderobject( pCorrectPoint,
						pNextList->getNumberOfUnderobjects() + 1 );
					
				}else{//create listelement as main -fib -object
					(*itrCorrectedFibObject)->insertObjectInElement(
						pCorrectPoint, 'r', 0, false, true );
				}
			}
		}
	}
	
	if ( bStandardDimensionDomain ){
		delete pDomainDimension;
	}
	
	DEBUG_OUT_L2( <<"fib::algorithms::nCorrectFibObject::nCorrectPoints::replaceWrongPoints( liPointWithPropertiesOrginal, liDistancesCountedWrong ) done "<<endl );
	return liCorretedFibObjects;
}



#endif //___N_CORRECT_POINTS_CPP__


















