/**
 * @file cFibObjectFitnessBasicAlgorithm
 * file name: cFibObjectFitnessBasicAlgorithm.cpp
 * @author Betti Oesterholz
 * @date 02.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class of fib -enviroment algorithm is for creating fib -fitness
 * objects.
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
 * @see cObjectFitness
 * @see cFibObjectFitness
 * @see cFibObjectFitnessBasic
 * This class of fib -enviroment algorithm is for creating fib -fitness
 * objects.
 * The better (higher) the fitness the better the Fib object, the more likly
 * it should live and children should be created from it.
 *
 */
/*
History:
02.03.2010  Oesterholz  created
18.04.2010  Oesterholz  evalueObject() methods changed: not a function but
	an object is given to evalue the data
30.04.2010  Oesterholz  using cEvaluePositionListMemLimit to evalue the
	given (non original) Fib objects
05.07.2010  Oesterholz  some functions moved to classes in namespace fib
02.09.2010  Oesterholz  using cEvaluePositionListLimit to evalue the
	given (non original) Fib objects
12.09.2010  Oesterholz  changes for the getOriginalPositionList() method
31.10.2012  Oesterholz  cFibObjectFitnessAlgorithm() constructor with
	input reference Fib object created
02.11.2012  Oesterholz  Bugfix: mutex for original individual
*/



#include "cFibObjectFitnessBasicAlgorithm.h"
#include "cFibIndividual.h"
#include "cFibObjectFitnessBasic.h"

#include "cRoot.h"
#include "cPoint.h"
#include "cList.h"
#include "cProperty.h"
#include "cVectorProperty.h"
#include "cVectorPosition.h"
#include "cEvaluePositionListLimit.h"


using namespace fib;
using namespace enviroment;
using namespace enviroment::fib;


/**
 * constructor
 */
cFibObjectFitnessBasicAlgorithm::cFibObjectFitnessBasicAlgorithm():
		cFibObjectFitnessAlgorithm(), dWeightDistanceToOriginal( 1.0 ),
		dWeightSize( 1.0 ), dWeightEvaluationTime( 1.0 ),
		pWorstCaseFitness( NULL ){
	
	pBestCaseFitness = new cFibObjectFitnessBasic( 0.0, 0, 0,
		dWeightDistanceToOriginal, dWeightSize, dWeightEvaluationTime, this );
	if ( pOriginalIndividual ){
		pOriginalIndividual->updateFitness( this );
	}
}


/**
 * constructor
 *
 * @see cFibObjectFitnessBasic
 * @param pInOriginalIndividual the individual with which the fitness
 * 	should be evalued;
 * 	Beware: this object won't be copied, so don't delete it as long
 * 	as this object exists
 * @param dInWeightDistanceToOriginal the weight for the distance to original value
 * @param dInWeightSize the weight for the Fib object size value
 * @param dInWeightEvaluationTime the weight for the evaluation time of
 * 	the Fib object
 */
cFibObjectFitnessBasicAlgorithm::cFibObjectFitnessBasicAlgorithm(
		cFibIndividual * pInOriginalIndividual,
		double dInWeightDistanceToOriginal, double dInWeightSize,
		double dInWeightEvaluationTime ):
		cFibObjectFitnessAlgorithm( pInOriginalIndividual ),
		dWeightDistanceToOriginal( dInWeightDistanceToOriginal ),
		dWeightSize( dInWeightSize ),
		dWeightEvaluationTime( dInWeightEvaluationTime ){
	
	pBestCaseFitness = new cFibObjectFitnessBasic( 0.0, 0, 0,
		dWeightDistanceToOriginal, dWeightSize, dWeightEvaluationTime, this );
	if ( pInOriginalIndividual != NULL ){
		pWorstCaseFitness = evalueFitness( *pInOriginalIndividual );
	}else{
		pWorstCaseFitness = NULL;
	}
	if ( pOriginalIndividual ){
		pOriginalIndividual->updateFitness( this );
	}
}


/**
 * constructor
 *
 * @see cFibObjectFitnessBasic
 * @param  pInOriginalFibElement the Fib object with which the fitness
 * 	should be evalued;
 * 	Beware: this object won't be copied, so don't delete it as long
 * 	as this object exists
 * @param dInWeightDistanceToOriginal the weight for the distance to original value
 * @param dInWeightSize the weight for the Fib object size value
 * @param dInWeightEvaluationTime the weight for the evaluation time of
 * 	the Fib object
 */
cFibObjectFitnessBasicAlgorithm::cFibObjectFitnessBasicAlgorithm(
		cFibElement * pInOriginalFibElement,
		double dInWeightDistanceToOriginal, double dInWeightSize,
		double dInWeightEvaluationTime ):
		cFibObjectFitnessAlgorithm( pInOriginalFibElement ),
		dWeightDistanceToOriginal( dInWeightDistanceToOriginal ),
		dWeightSize( dInWeightSize ),
		dWeightEvaluationTime( dInWeightEvaluationTime ){
	
	pBestCaseFitness = new cFibObjectFitnessBasic( 0.0, 0, 0,
		dWeightDistanceToOriginal, dWeightSize, dWeightEvaluationTime, this );
	
	if ( pInOriginalFibElement != NULL ){
		pWorstCaseFitness = evalueFitness( pInOriginalFibElement );
	}else{
		pWorstCaseFitness = NULL;
	}
	if ( pOriginalIndividual ){
		pOriginalIndividual->updateFitness( this );
	}
}


/**
 * constructor
 *
 * @see cFibObjectFitnessBasic
 * @param  inOriginalFibElement the fib object with which the fitness
 * 	should be evalued
 * @param dInWeightDistanceToOriginal the weight for the distance to original value
 * @param dInWeightSize the weight for the Fib object size value
 * @param dInWeightEvaluationTime the weight for the evaluation time of
 * 	the Fib object
 */
cFibObjectFitnessBasicAlgorithm::cFibObjectFitnessBasicAlgorithm(
		const cFibElement & inOriginalFibElement,
		double dInWeightDistanceToOriginal, double dInWeightSize,
		double dInWeightEvaluationTime ):
		cFibObjectFitnessAlgorithm( inOriginalFibElement ),
		dWeightDistanceToOriginal( dInWeightDistanceToOriginal ),
		dWeightSize( dInWeightSize ),
		dWeightEvaluationTime( dInWeightEvaluationTime ){
	
	pBestCaseFitness = new cFibObjectFitnessBasic( 0.0, 0, 0,
		dWeightDistanceToOriginal, dWeightSize, dWeightEvaluationTime, this );
	
	pWorstCaseFitness = evalueFitness( & inOriginalFibElement );
	if ( pOriginalIndividual ){
		pOriginalIndividual->updateFitness( this );
	}
}


/**
 * copyconstructor
 *
 * @param objectFitnessAlgorithm the cFibObjectFitnessBasicAlgorithm object to copy
 */
cFibObjectFitnessBasicAlgorithm::cFibObjectFitnessBasicAlgorithm(
		const cFibObjectFitnessBasicAlgorithm & objectFitnessAlgorithm ):
		cFibObjectFitnessAlgorithm( objectFitnessAlgorithm ),
		dWeightDistanceToOriginal( objectFitnessAlgorithm.dWeightDistanceToOriginal ),
		dWeightSize( objectFitnessAlgorithm.dWeightSize ),
		dWeightEvaluationTime( objectFitnessAlgorithm.dWeightEvaluationTime ){
	
	if ( bOriginalEvalued ){
		//evalue the dimensions for this object
		evalueOriginalDimensions();
	}
	
	if ( objectFitnessAlgorithm.pBestCaseFitness != NULL ){
		pBestCaseFitness = objectFitnessAlgorithm.pBestCaseFitness->clone();
	}else{
		pBestCaseFitness = NULL;
	}
	if ( objectFitnessAlgorithm.pWorstCaseFitness != NULL ){
		pWorstCaseFitness = objectFitnessAlgorithm.pWorstCaseFitness->clone();
	}else{
		pWorstCaseFitness = NULL;
	}
	if ( pOriginalIndividual ){
		pOriginalIndividual->updateFitness( this );
	}
}


/**
 * destructor
 */
cFibObjectFitnessBasicAlgorithm::~cFibObjectFitnessBasicAlgorithm(){
	
	if ( pBestCaseFitness ){
		delete pBestCaseFitness;
	}
	if ( pWorstCaseFitness ){
		delete pWorstCaseFitness;
	}
}


/**
 * This function evalues the fitness for the given fib -individual.
 *
 * @see pOriginalIndividual
 * @param individual the cFibIndividual for which a fitnessobject should
 * 	be created
 * @return the fitnessobject for the fitness of the given individual or
 * 	NULL, if no fitness could be created
 */
cFibObjectFitnessBasic * cFibObjectFitnessBasicAlgorithm::evalueFitness(
		const cIndividual  &individual ) const{
	
	return evalueFitness( const_cast<cFibIndividual*>((cFibIndividual*)
		&individual)->getFibObject() );
}


/**
 * This function evalues the fitness for the given fib -individual.
 *
 * @see pOriginalIndividual
 * @param individual the cFibIndividual for which a fitnessobject should
 * 	be created
 * @return the fitnessobject for the fitness of the given individual or
 * 	NULL, if no fitness could be created
 */
cFibObjectFitnessBasic * cFibObjectFitnessBasicAlgorithm::evalueFitness(
		const cFibIndividual & individual ) const{
	
	return evalueFitness( const_cast<cFibIndividual*>((cFibIndividual*)
		&individual)->getFibObject() );
}


/**
 * This function evalues the fitness for the given fib -individual.
 *
 * @see pOriginalIndividual
 * @param fibObject the Fib object for which a fitnessobject should
 * 	be created
 * @return the fitnessobject for the fitness of the given fibObject or
 * 	NULL, if no fitness could be created
 */
cFibObjectFitnessBasic * cFibObjectFitnessBasicAlgorithm::evalueFitness(
		const cFibElement * fibObject ) const{
	
	if ( fibObject == NULL ){
		return NULL;
	}

#ifdef FATURE_MAX_FITNESS_EVALUATION_TIME
	//evalue the dimensions of the original Fib object
	const long long lEvaluationTime =
		fibObject->getTimeNeed( (ulNumberOfPoints + 1000000) * 1000000 );
	
	if ( lEvaluationTime == (long long)((ulNumberOfPoints + 1000000) * 1000000) ){
		//evaluating time taks to long
		return NULL;
	}
#else
	const long long lEvaluationTime = fibObject->getTimeNeed();
#endif

	const long long lSize = fibObject->getCompressedSize();
	const double dDistanceToOriginal = evalueDistance( fibObject );
	if ( dDistanceToOriginal == -1 ){
		return NULL;
	}
	
	return new cFibObjectFitnessBasic( dDistanceToOriginal, lSize, lEvaluationTime,
		dWeightDistanceToOriginal, dWeightSize, dWeightEvaluationTime,
		const_cast<cFibObjectFitnessBasicAlgorithm *>(this) );
}


/**
 * This method evalues the difference betwean the orginal Fib object
 * and the given Fib object fibObject on an area.
 * It is the sum of the distances of all values of propertyvectorelements
 * betwean the represented and original Fib object of all positions
 * which are inside the dimension bounderies and are in fibObjectArea,
 * if given (not NULL).
 * Properties of positions that aren't evalued are taken to be 0 in all
 * vectorelements (nullvector).
 *
 * @param fibObject the Fib object to which the difference is to evalue
 * @param fibObjectArea if given (not NULL) the points/positions of
 * 	this (evalued) Fib object are the positions for which the
 * 	distance is evalued (other points will be ignored)
 * @return a value for the difference betwean the orginal Fib object
 * 	and the given Fib object fibObject, or -1.0 if an error occured
 */
double cFibObjectFitnessBasicAlgorithm::evalueDistance(
		const cFibElement * fibObject, const cFibElement * fibObjectArea ) const{
	
	DEBUG_OUT_L2(<<"cFibObjectFitnessBasicAlgorithm::evalueDistance( "<<fibObject<<", "<<fibObjectArea<<") started"<<endl);
	
//TODO mutex for pOriginalIndividual also for changing it in parents
	
	
	pthread_mutex_lock( &mutexOriginalIndividual );
	
	if ( (pOriginalIndividual == NULL) ||
			(((cFibIndividual*)pOriginalIndividual)->getFibObject() == NULL) ||
			( fibObject == NULL ) ){
		//can't evalue a distance
		pthread_mutex_unlock( &mutexOriginalIndividual );
		return -1.0;
	}
	if ( ! bOriginalEvalued ){
		//evalue the dimensions of the original Fib object
		if ( ! ( evalueOriginalDimensions() ) ){
			DEBUG_OUT_EL1( <<"Error: The original Fib object dimensions couldn't be evalued."<<endl );
			pthread_mutex_unlock( &mutexOriginalIndividual );
			return -1.0;
		}
		//evalue the fibObject fibElement
		if ( pEvaluedPositionsDataOriginal ){
			delete pEvaluedPositionsDataOriginal;
		}
		pEvaluedPositionsDataOriginal = new cEvaluePositionListLimit( ulNumberOfPoints * 2,
			pVecDomainDimension, false, 0, ulNumberOfPoints * 64 );
		
		const bool bObjectEvalued = ((cFibIndividual*)pOriginalIndividual)->
			getFibObject()->evalueObjectSimple( *pEvaluedPositionsDataOriginal );
		if ( ! bObjectEvalued ){
			DEBUG_OUT_EL1( <<"Error: The original Fib object couldn't be evalued."<<endl );
			pthread_mutex_unlock( &mutexOriginalIndividual );
			return -1.0;
		}
		pEvaluedPositionsDataOriginal->sortPositionsData();
		bOriginalEvalued = true;
	}
	pthread_mutex_unlock( &mutexOriginalIndividual );
	
	if ( (pdDirectionMinimum == NULL) || (pdDirectionMaximum == NULL) ||
			(pdDirectionScaling == NULL) || (pdDirectionSize == NULL) || 
			(pVecDomainDimension == NULL) ){
		DEBUG_OUT_EL1( <<"Error: Dimension values missing."<<endl );
		return -1.0;
	}
	
	//evalue the fibObject fibElement
	cEvaluePositionListLimit evaluedPositionData( ulNumberOfPoints * 2,
		pVecDomainDimension, true, 0, ulNumberOfPoints * 64 );

	const bool bObjectEvalued = fibObject->evalueObjectSimple( evaluedPositionData );
	if ( ! bObjectEvalued ){
		DEBUG_OUT_EL1( <<"Error: The given Fib object couldn't be evalued."<<endl );
		return -1.0;
	}
	
	if ( fibObjectArea == NULL ){
		//if no given fibObjectArea
		
		return evalueDistance( evaluedPositionData.liEvaluedPositionData );
	
	}//else if given fibObjectArea: evalue fibObjectArea

	cEvaluePositionListLimit evaluedPositionDataArea( ulNumberOfPoints * 2,
		pVecDomainDimension, false, 0, ulNumberOfPoints * 64 );

	//evalue the fibObject fibObjectArea
	const bool bAreaObjectEvalued = fibObjectArea->evalueObjectSimple( evaluedPositionDataArea );
	if ( ! bAreaObjectEvalued ){
		DEBUG_OUT_EL1( <<"Error: The given Fib object for the area couldn't be evalued."<<endl );
		return -1.0;
	}
	
	return evalueDistanceInArea( evaluedPositionData.liEvaluedPositionData,
		evaluedPositionDataArea.liEvaluedPositionData );
}



/**
 * This method evalues the difference betwean the orginal Fib object
 * and the given points with ther properties.
 * It is the sum of the distances of all values of propertyvectorelements
 * betwean the represented and original Fib object of all positions
 * which are inside the dimension bounderies.
 *
 * @param liPointWithProperties the list with the points and ther
 * 	properties for which to evalue the distance
 * @return a value for the difference betwean the orginal Fib object
 * 	and the given liPointWithProperties, or -1.0 if an error occured
 */
double cFibObjectFitnessBasicAlgorithm::evalueDistance(
	list< pair< cVectorPosition, list< cVectorProperty > > > &
		liPointWithProperties ) const{
	
	DEBUG_OUT_L2(<<"cFibObjectFitnessBasicAlgorithm::evalueDistance( "<< &liPointWithProperties<<" ) started"<<endl);
	
	pthread_mutex_lock( &mutexOriginalIndividual );

	if ( (&liPointWithProperties == NULL) ||
			(((cFibIndividual*)pOriginalIndividual)->getFibObject() == NULL) ){
		//can't evalue a distance
		pthread_mutex_unlock( &mutexOriginalIndividual );
		return -1.0;
	}
	if ( ! bOriginalEvalued ){
		//evalue the dimensions of the original Fib object
		if ( ! ( evalueOriginalDimensions() ) ){
			DEBUG_OUT_EL1( <<"Error: The original Fib object dimensions couldn't be evalued."<<endl );
			pthread_mutex_unlock( &mutexOriginalIndividual );
			return -1.0;
		}
		//evalue the fibObject fibElement
		if ( pEvaluedPositionsDataOriginal ){
			delete pEvaluedPositionsDataOriginal;
		}
		pEvaluedPositionsDataOriginal = new cEvaluePositionListLimit( ulNumberOfPoints * 2,
			pVecDomainDimension, false, 0, ulNumberOfPoints * 64 );
		
		const bool bObjectEvalued = ((cFibIndividual*)pOriginalIndividual)->
			getFibObject()->evalueObjectSimple( *pEvaluedPositionsDataOriginal );
		if ( ! bObjectEvalued ){
			DEBUG_OUT_EL1( <<"Error: The original Fib object couldn't be evalued."<<endl );
			pthread_mutex_unlock( &mutexOriginalIndividual );
			return -1.0;
		}
		pEvaluedPositionsDataOriginal->sortPositionsData();
		bOriginalEvalued = true;
	}
	if ( (pdDirectionMinimum == NULL) || (pdDirectionMaximum == NULL) ||
			(pdDirectionScaling == NULL) || (pdDirectionSize == NULL) || 
			(pVecDomainDimension == NULL) ){
		DEBUG_OUT_EL1( <<"Error: Dimension values missing."<<endl );
		pthread_mutex_unlock( &mutexOriginalIndividual );
		return -1.0;
	}
	
	cEvaluePositionList::sortPositionsData( & liPointWithProperties );
	
	list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
		itrPositionOriginal = pEvaluedPositionsDataOriginal->liEvaluedPositionData.begin();
	list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
		itrPositionGiven = liPointWithProperties.begin();
	
	//list with the background properties
	list< cVectorProperty > liBackgroundPropertiesOriginal;
	list< cVectorProperty > liBackgroundPropertiesGiven;
	
	//evalue the background properties and ignore the background properties
	if ( ( ! pEvaluedPositionsDataOriginal->liEvaluedPositionData.empty() ) &&
			(itrPositionOriginal->first.getNumberOfElements() == 0) ){
		
		liBackgroundPropertiesOriginal = itrPositionOriginal->second;
		itrPositionOriginal++;
	}
	if ( ( ! liPointWithProperties.empty() ) &&
			( itrPositionGiven->first.getNumberOfElements() == 0 ) ){
		
		liBackgroundPropertiesGiven = itrPositionGiven->second;
		itrPositionGiven++;
	}
	
	double dDistance = 0.0;
	
	unsigned long ulJustBackground = 0;
	const cVectorPosition * pOldPosition = NULL;
	const cVectorPosition * pNewPosition = NULL;
	
	while ( (itrPositionOriginal != pEvaluedPositionsDataOriginal->liEvaluedPositionData.end()) ||
			(itrPositionGiven != liPointWithProperties.end()) ){
		//for every position in the original Fib object
		
		if ( itrPositionGiven == liPointWithProperties.end() ){
			/*if equivallent position is not in the given Fib object
			-> compare original positions properties against given background*/
			//if no equivallent background properties add to nullvector
			if ( ! pVecDomainDimension->isElement( itrPositionOriginal->first ) ){
				//position not in dimension bounderies -> skip it
				itrPositionOriginal++;
				continue;
			}
			dDistance += cEvaluePositionList::distanceOfProperties(
				cEvaluePositionList::mergeProperties(
					itrPositionOriginal->second, liBackgroundPropertiesOriginal ),
				liBackgroundPropertiesGiven );
			
			pNewPosition = &(itrPositionOriginal->first);
			itrPositionOriginal++;
		}else if ( itrPositionOriginal == pEvaluedPositionsDataOriginal->liEvaluedPositionData.end() ){
			//for points in the given Fib object but not in the original Fib object
			if ( ! pVecDomainDimension->isElement( itrPositionGiven->first ) ){
				//position not in dimension bounderies -> skip it
				itrPositionGiven++;
				continue;
			}//if inside dimension bounderies
			
			/*add differnce to original background properties, if existing,
			or the nullvector*/
			dDistance += cEvaluePositionList::distanceOfProperties( liBackgroundPropertiesOriginal,
				cEvaluePositionList::mergeProperties( itrPositionGiven->second, liBackgroundPropertiesGiven ) );
			
			pNewPosition = &(itrPositionGiven->first);
			itrPositionGiven++;
		}else if ( cEvaluePositionList::lowerPositionPair( *itrPositionOriginal, *itrPositionGiven ) ){
			/*if equivallent position is not in the given Fib object
			-> compare original positions properties against given background*/
			if ( ! pVecDomainDimension->isElement( itrPositionOriginal->first ) ){
				//position not in dimension bounderies -> skip it
				itrPositionOriginal++;
				continue;
			}//if inside dimension bounderies
			
			//if no equivallent background properties add to nullvector
			dDistance += cEvaluePositionList::distanceOfProperties( 
				cEvaluePositionList::mergeProperties(
					itrPositionOriginal->second, liBackgroundPropertiesOriginal ),
				liBackgroundPropertiesGiven );
		
			pNewPosition = &(itrPositionOriginal->first);
			itrPositionOriginal++;
		}else if ( cEvaluePositionList::lowerPositionPair( *itrPositionGiven, *itrPositionOriginal ) ){
			if ( ! pVecDomainDimension->isElement( itrPositionGiven->first ) ){
				//position not in dimension bounderies -> skip it
				itrPositionGiven++;
				continue;
			}//if inside dimension bounderies
			dDistance += cEvaluePositionList::distanceOfProperties( liBackgroundPropertiesOriginal,
				cEvaluePositionList::mergeProperties( itrPositionGiven->second, liBackgroundPropertiesGiven ) );
			
			pNewPosition = &(itrPositionGiven->first);
			itrPositionGiven++;
		}else{//both are equal ( itrPositionOriginal->first == itrPositionGiven->first )
			//if equivallent position is in the given Fib object
			if ( ! pVecDomainDimension->isElement( itrPositionGiven->first ) ){
				//position not in dimension bounderies -> skip it
				itrPositionGiven++;
				itrPositionOriginal++;
				continue;
			}//if inside dimension bounderies
			dDistance += cEvaluePositionList::distanceOfProperties(
				cEvaluePositionList::mergeProperties( itrPositionOriginal->second, liBackgroundPropertiesOriginal ),
				cEvaluePositionList::mergeProperties( itrPositionGiven->second, liBackgroundPropertiesGiven ) );

			pNewPosition = &(itrPositionGiven->first);
			itrPositionGiven++;
			itrPositionOriginal++;
		}
		
		//evalue the number of backgroundpoints betwean the new and old position
		unsigned long ulPositionBetwean = 0;
		if ( pOldPosition == NULL ){
			//add the background positions till the first positions
			ulPositionBetwean += pNewPosition->getValue( 1 ) - pdDirectionMinimum[ 0 ];
			for ( unsigned int uiActualDimension = 2;
					uiActualDimension <= uiNumberOfDimensions ; uiActualDimension++ ){
				
				ulPositionBetwean *= pdDirectionSize[ uiActualDimension - 1 ];
				ulPositionBetwean += (unsigned long)((pNewPosition->getValue( uiActualDimension ) -
					pdDirectionMinimum[ uiActualDimension - 1 ]) / pdDirectionScaling[ uiActualDimension - 1 ] );
			}
			ulJustBackground += ulPositionBetwean;
			DEBUG_OUT_EL4( <<"Background to ("<< pNewPosition->getValue( 1 )<<", "<< pNewPosition->getValue( 2 )<<") " );
			DEBUG_OUT_EL4( <<" is "<< ulPositionBetwean <<" ins="<<ulJustBackground<<" ."<<endl );
		}else{
			//add the background positions betwean the old and the new point
			ulPositionBetwean += pNewPosition->getValue( 1 ) - pOldPosition->getValue( 1 );
			for ( unsigned int uiActualDimension = 2;
					uiActualDimension <= uiNumberOfDimensions ; uiActualDimension++ ){
				
				ulPositionBetwean *= pdDirectionSize[ uiActualDimension - 1 ];
				ulPositionBetwean += (long)((pNewPosition->getValue( uiActualDimension ) -
					pOldPosition->getValue( uiActualDimension )) / pdDirectionScaling[ uiActualDimension - 1 ] );
			}
			if ( 1 < ulPositionBetwean ){
				ulJustBackground += ulPositionBetwean - 1;
			}
			DEBUG_OUT_EL4( <<"Background from ("<< pOldPosition->getValue( 1 )<<", "<< pOldPosition->getValue( 2 )<<") " );
			DEBUG_OUT_EL4( <<"to ("<< pNewPosition->getValue( 1 )<<", "<< pNewPosition->getValue( 2 )<<") " );
			DEBUG_OUT_EL4( <<" is "<< ulPositionBetwean-1 <<" ins="<<ulJustBackground<<" ."<<endl );
		}
		pOldPosition = pNewPosition;
	}
	if ( pNewPosition != NULL ){
		//add the background positions from the last position till the end of the dimension area
		unsigned long ulPositionBetwean = 0;
		ulPositionBetwean += pdDirectionMaximum[ 0 ] - pNewPosition->getValue( 1 );
		for ( unsigned int uiActualDimension = 2;
				uiActualDimension <= uiNumberOfDimensions ; uiActualDimension++ ){
			
			ulPositionBetwean *= pdDirectionSize[ uiActualDimension - 1 ];
			ulPositionBetwean += (unsigned long)((pdDirectionMaximum[ uiActualDimension - 1 ] -
				pNewPosition->getValue( uiActualDimension ) ) / pdDirectionScaling[ uiActualDimension - 1 ] );
		}
		ulJustBackground += ulPositionBetwean;
		DEBUG_OUT_EL4( <<"Background from ("<< pNewPosition->getValue( 1 )<<", "<< pNewPosition->getValue( 2 )<<") " );
		DEBUG_OUT_EL4( <<" to Maximum is "<< ulPositionBetwean <<" ins="<<ulJustBackground<<" ."<<endl );
	}else{//no position evalued -> add the background positions for all positions in the dimension area
		unsigned long ulPositionBetwean = 1;
		for ( unsigned int uiActualDimension = 0;
				uiActualDimension < uiNumberOfDimensions; uiActualDimension++ ){
			
			ulPositionBetwean *= pdDirectionSize[ uiActualDimension ];
		}
		ulJustBackground += ulPositionBetwean;
		DEBUG_OUT_EL4( <<"Background all is "<< ulPositionBetwean <<" ins="<< ulJustBackground <<" ."<<endl );
	}

	/*for every point inside the dimension bounderies but not compared befor
	-> add distance of the background properties*/
	dDistance += (double)ulJustBackground * cEvaluePositionList::distanceOfProperties(
		liBackgroundPropertiesOriginal, liBackgroundPropertiesGiven );
	
	pthread_mutex_unlock( &mutexOriginalIndividual );
	return dDistance;
}



/**
 * This method evalues the difference betwean the orginal Fib object
 * and the given Fib object fibObject on an area.
 * It is the sum of the distances of all values of propertyvectorelements
 * betwean the represented and original Fib object of all positions
 * which are inside the dimension bounderies and are in fibObjectArea.
 *
 * @param liPointWithProperties the list with the points and ther
 * 	properties for which to evalue the distance
 * @param liPointWithPropertiesOfArea the points/positions of
 * 	the positions for which the distance is evalued (other points
 * 	will be ignored)
 * 	(the list< cVectorProperty > is included for consistencie, but
 * 	it is ignored in this method)
 * @return a value for the difference betwean the orginal Fib object
 * 	and the given liPointWithProperties, or -1.0 if an error occured
 */
double cFibObjectFitnessBasicAlgorithm::evalueDistanceInArea(
	list< pair< cVectorPosition, list< cVectorProperty > > > &
		liPointWithProperties,
	list< pair< cVectorPosition, list< cVectorProperty > > > &
		liPointWithPropertiesOfArea ) const{
	
	DEBUG_OUT_L2(<<"cFibObjectFitnessBasicAlgorithm::evalueDistanceInArea( "<<&liPointWithProperties<<", "<<&liPointWithPropertiesOfArea<<") started"<<endl);
	
	pthread_mutex_lock( &mutexOriginalIndividual );
	
	if ( (pOriginalIndividual == NULL) ||
			(((cFibIndividual*)pOriginalIndividual)->getFibObject() == NULL) ){
		//can't evalue a distance
		pthread_mutex_unlock( &mutexOriginalIndividual );
		return -1.0;
	}
	if ( ! bOriginalEvalued ){
		//evalue the dimensions of the original Fib object
		if ( ! ( evalueOriginalDimensions() ) ){
			DEBUG_OUT_EL1( <<"Error: The original Fib object dimensions couldn't be evalued."<<endl );
			pthread_mutex_unlock( &mutexOriginalIndividual );
			return -1.0;
		}
		//evalue the fibObject fibElement
		if ( pEvaluedPositionsDataOriginal ){
			delete pEvaluedPositionsDataOriginal;
		}
		pEvaluedPositionsDataOriginal = new cEvaluePositionListLimit( ulNumberOfPoints * 2,
			pVecDomainDimension, false, 0, ulNumberOfPoints * 64 );
		
		const bool bObjectEvalued = ((cFibIndividual*)pOriginalIndividual)->
			getFibObject()->evalueObjectSimple( *pEvaluedPositionsDataOriginal );
		if ( ! bObjectEvalued ){
			DEBUG_OUT_EL1( <<"Error: The original Fib object couldn't be evalued."<<endl );
			pthread_mutex_unlock( &mutexOriginalIndividual );
			return -1.0;
		}
		pEvaluedPositionsDataOriginal->sortPositionsData();
		bOriginalEvalued = true;
	}
	if ( (pdDirectionMinimum == NULL) || (pdDirectionMaximum == NULL) ||
			(pdDirectionScaling == NULL) || (pdDirectionSize == NULL) || 
			(pVecDomainDimension == NULL) ){
		DEBUG_OUT_EL1( <<"Error: Dimension values missing."<<endl );
		pthread_mutex_unlock( &mutexOriginalIndividual );
		return -1.0;
	}
	
	cEvaluePositionList::sortPositionsData( & liPointWithProperties );
	cEvaluePositionList::sortPositionsData( & liPointWithPropertiesOfArea, false );

	list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
		itrPositionOriginal = pEvaluedPositionsDataOriginal->liEvaluedPositionData.begin();
	list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
		itrPositionGiven = liPointWithProperties.begin();
	list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
		itrPositionAreaOriginal = liPointWithPropertiesOfArea.begin();
	
	//list with the background properties
	list< cVectorProperty > liBackgroundPropertiesOriginal;
	list< cVectorProperty > liBackgroundPropertiesGiven;
	
	//evalue the background properties and ignore the background properties
	if ( ( ! pEvaluedPositionsDataOriginal->liEvaluedPositionData.empty() ) &&
			(itrPositionOriginal->first.getNumberOfElements() == 0) ){
		
		liBackgroundPropertiesOriginal = itrPositionOriginal->second;
		itrPositionOriginal++;
	}
	if ( ( ! liPointWithProperties.empty() ) &&
			( itrPositionGiven->first.getNumberOfElements() == 0 ) ){
		
		liBackgroundPropertiesGiven = itrPositionGiven->second;
		itrPositionGiven++;
	}
	if ( ( ! liPointWithPropertiesOfArea.empty() ) &&
			( itrPositionAreaOriginal->first.getNumberOfElements() == 0 ) ){
		itrPositionAreaOriginal++;
	}
	list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
		itrPositionAreaGiven = itrPositionAreaOriginal;
	
	double dDistance = 0.0;
	
	unsigned long ulJustBackground = 0;
	
	/*evalue the count of possible backgroundpoints;
	delete non backgroundpoints later on*/
	for (; itrPositionAreaOriginal != liPointWithPropertiesOfArea.end();
			itrPositionAreaOriginal++ ){
		
		if ( pVecDomainDimension->isElement( itrPositionAreaOriginal->first ) ){
			//area position in dimension bounderies -> count it
			ulJustBackground++;
		}
	}
	itrPositionAreaOriginal = itrPositionAreaGiven;
	
	//for every position in the original Fib object and in fibObjectArea
	while ( ( (itrPositionOriginal != pEvaluedPositionsDataOriginal->liEvaluedPositionData.end()) ||
			(itrPositionGiven != liPointWithProperties.end()) ) &&
			( (itrPositionAreaOriginal != liPointWithPropertiesOfArea.end()) ||
					(itrPositionAreaGiven != liPointWithPropertiesOfArea.end()) ) ){
		//for every position in the original Fib object
		
		if ( (itrPositionGiven != liPointWithProperties.end()) &&
				(itrPositionAreaGiven == liPointWithPropertiesOfArea.end()) ){
			//no more given positions to check
			itrPositionGiven = liPointWithProperties.end();
			
		}else if ( (itrPositionOriginal != pEvaluedPositionsDataOriginal->liEvaluedPositionData.end()) &&
				(itrPositionAreaOriginal == liPointWithPropertiesOfArea.end()) ){
			//no more original positions to check
			itrPositionOriginal = pEvaluedPositionsDataOriginal->liEvaluedPositionData.end();
			
		}else if ( (itrPositionGiven == liPointWithProperties.end()) &&
				( itrPositionOriginal->first != itrPositionAreaOriginal->first ) ){
			/*go to next original position an the area*/
			if ( cEvaluePositionList::lowerPositionPair( *itrPositionAreaOriginal, *itrPositionOriginal ) ){
				itrPositionAreaOriginal++;
			}else{
				itrPositionOriginal++;
			}
		}else if ( ( itrPositionOriginal == pEvaluedPositionsDataOriginal->liEvaluedPositionData.end() ) &&
				( itrPositionGiven->first != itrPositionAreaGiven->first ) ){
			/*go to next given position an the area*/
			if ( cEvaluePositionList::lowerPositionPair( *itrPositionAreaGiven, *itrPositionGiven ) ){
				itrPositionAreaGiven++;
			}else{
				itrPositionGiven++;
			}
		}else if ( (itrPositionGiven != liPointWithProperties.end()) &&
				( itrPositionOriginal  != pEvaluedPositionsDataOriginal->liEvaluedPositionData.end() ) &&
				( ( itrPositionOriginal->first != itrPositionAreaOriginal->first ) ||
					( itrPositionGiven->first != itrPositionAreaGiven->first ) ) ){
			//go with original and the given position to the next position in the area
			if ( itrPositionOriginal->first != itrPositionAreaOriginal->first ){
				if ( cEvaluePositionList::lowerPositionPair( *itrPositionOriginal, *itrPositionAreaOriginal ) ){
					itrPositionOriginal++;
				}else{
					itrPositionAreaOriginal++;
				}
			}
			if ( itrPositionGiven->first != itrPositionAreaGiven->first ){
				if ( cEvaluePositionList::lowerPositionPair( *itrPositionGiven, *itrPositionAreaGiven ) ){
					itrPositionGiven++;
				}else{
					itrPositionAreaGiven++;
				}
			}
		}else{/*both original and given position are positions in the area
			(or one have reached ther end)*/
			if ( itrPositionGiven == liPointWithProperties.end() ){
				/*if equivallent position is not in the given Fib object
				-> compare original positions properties against given background*/
				//if no equivallent background properties add to nullvector
				if ( ! pVecDomainDimension->isElement( itrPositionOriginal->first ) ){
					//position not in dimension bounderies -> skip it
					itrPositionOriginal++;
					continue;
				}
				dDistance += cEvaluePositionList::distanceOfProperties(
					cEvaluePositionList::mergeProperties(
						itrPositionOriginal->second, liBackgroundPropertiesOriginal ),
					liBackgroundPropertiesGiven );
				
				itrPositionAreaOriginal++;
				itrPositionOriginal++;
			}else if ( itrPositionOriginal == pEvaluedPositionsDataOriginal->liEvaluedPositionData.end() ){
				//for points in the given Fib object but not in the original Fib object
				if ( ! pVecDomainDimension->isElement( itrPositionGiven->first ) ){
					//position not in dimension bounderies -> skip it
					itrPositionGiven++;
					continue;
				}//if inside dimension bounderies
				
				/*add differnce to original background properties, if existing,
				or the nullvector*/
				dDistance += cEvaluePositionList::distanceOfProperties( liBackgroundPropertiesOriginal,
					cEvaluePositionList::mergeProperties( itrPositionGiven->second, liBackgroundPropertiesGiven ) );
				
				itrPositionAreaGiven++;
				itrPositionGiven++;
			}else if ( cEvaluePositionList::lowerPositionPair( *itrPositionOriginal, *itrPositionGiven ) ){
				/*if equivallent position is not in the given Fib object
				-> compare original positions properties against given background*/
				if ( ! pVecDomainDimension->isElement( itrPositionOriginal->first ) ){
					//position not in dimension bounderies -> skip it
					itrPositionOriginal++;
					continue;
				}//if inside dimension bounderies
				
				//if no equivallent background properties add to nullvector
				dDistance += cEvaluePositionList::distanceOfProperties(
					cEvaluePositionList::mergeProperties(
						itrPositionOriginal->second, liBackgroundPropertiesOriginal ),
					liBackgroundPropertiesGiven );
			
				itrPositionAreaOriginal++;
				itrPositionOriginal++;
			}else if ( cEvaluePositionList::lowerPositionPair( *itrPositionGiven, *itrPositionOriginal ) ){
				if ( ! pVecDomainDimension->isElement( itrPositionGiven->first ) ){
					//position not in dimension bounderies -> skip it
					itrPositionGiven++;
					continue;
				}//if inside dimension bounderies
				dDistance += cEvaluePositionList::distanceOfProperties( liBackgroundPropertiesOriginal,
					cEvaluePositionList::mergeProperties( itrPositionGiven->second, liBackgroundPropertiesGiven ) );
				
				itrPositionAreaGiven++;
				itrPositionGiven++;
			}else{/*both are equal ( itrPositionOriginal->first == itrPositionGiven->first ==
					itrPositionAreaOriginal->first == itrPositionAreaGiven->first )*/
				//if equivallent position is in the given Fib object
				if ( ! pVecDomainDimension->isElement( itrPositionGiven->first ) ){
					//position not in dimension bounderies -> skip it
					itrPositionGiven++;
					itrPositionOriginal++;
					continue;
				}//if inside dimension bounderies
				dDistance += cEvaluePositionList::distanceOfProperties(
					cEvaluePositionList::mergeProperties( itrPositionOriginal->second, liBackgroundPropertiesOriginal ),
					cEvaluePositionList::mergeProperties( itrPositionGiven->second, liBackgroundPropertiesGiven ) );

				itrPositionGiven++;
				itrPositionOriginal++;
				itrPositionAreaGiven++;
				itrPositionAreaOriginal++;
			}
			//this was not a just backgroundpoint
			ulJustBackground--;
		}
	}//while

	/*for every point inside the dimension bounderies but not compared befor
	-> add distance of the background properties*/
	dDistance += (double)ulJustBackground * cEvaluePositionList::distanceOfProperties(
		liBackgroundPropertiesOriginal, liBackgroundPropertiesGiven );
	
	pthread_mutex_unlock( &mutexOriginalIndividual );
	
	return dDistance;
}




/**
 * @return the name of this class
 */
string cFibObjectFitnessBasicAlgorithm::getClassName() const{

	return "cFibObjectFitnessBasicAlgorithm";
}


/**
 * This method sets the originalindividual.
 * The originalindividual is the individual with which the fitness
 * should be evalued.
 *
 * @see getOriginalIndividual()
 * @see pOriginalIndividual
 * @param pInOriginalIndividual a point to the original individual to set
 * 	Beware: this object won't be copied, so don't delete it as long
 * 	as this object exists
 * @return true if the originalindividual is set to originalIndividum,
 * 	else false
 */
bool cFibObjectFitnessBasicAlgorithm::setOriginalIndividual(
		cIndividual * pInOriginalIndividual ){
	
	bOriginalEvalued = false;
	const bool bOriginalSet = cFibObjectFitnessAlgorithm::setOriginalIndividual(
		pInOriginalIndividual );
	
	if ( pWorstCaseFitness ){
		delete pWorstCaseFitness;
	}
	if ( getOriginalFibObject() != NULL ){
		pWorstCaseFitness = evalueFitness( getOriginalFibObject() );
	}else{
		pWorstCaseFitness = NULL;
	}
	return bOriginalSet;
}


/**
 * This method sets the originalindividual.
 * The originalindividual is the individual with which the fitness
 * should be evalued.
 *
 * @see getOriginalIndividual()
 * @see pOriginalIndividual
 * @param pInOriginalIndividual a point to the fib original individual to set
 * 	Beware: this object won't be copied, so don't delete it as long
 * 	as this object exists
 * @return true if the originalindividual is set to pInOriginalIndividual,
 * 	else false
 */
bool cFibObjectFitnessBasicAlgorithm::setOriginalIndividual(
		cFibIndividual * pInOriginalIndividual ){
	
	bOriginalEvalued = false;
	const bool bOriginalSet = cFibObjectFitnessAlgorithm::setOriginalIndividual(
		pInOriginalIndividual );
	
	if ( pWorstCaseFitness ){
		delete pWorstCaseFitness;
	}
	if ( getOriginalFibObject() != NULL ){
		pWorstCaseFitness = evalueFitness( getOriginalFibObject() );
	}else{
		pWorstCaseFitness = NULL;
	}
	return bOriginalSet;
}


/**
 * This method sets the originalindividual.
 * The originalindividual is the individual with which the fitness
 * should be evalued.
 *
 * @see getOriginalIndividual()
 * @see pOriginalIndividual
 * @param pInOriginalFibObject the Fib object with which the fitness
 * 	should be evalued;
 * 	Beware: this object won't be copied, so don't delete it as long
 * 	as this object exists
 * @return true if the originalindividual is set to pInOriginalFibObject,
 * 	else false
 */
bool cFibObjectFitnessBasicAlgorithm::setOriginalFibObject(
		cFibElement  * pInOriginalFibObject ){
	
	bOriginalEvalued = false;
	const bool bOriginalSet = cFibObjectFitnessAlgorithm::setOriginalFibObject(
		pInOriginalFibObject );
	
	if ( pWorstCaseFitness ){
		delete pWorstCaseFitness;
	}
	if ( getOriginalFibObject() != NULL ){
		pWorstCaseFitness = evalueFitness( getOriginalFibObject() );
	}else{
		pWorstCaseFitness = NULL;
	}
	return bOriginalSet;
}


/**
 * This Method clones this object.
 *
 * @return a clone of this object
 */
cFibObjectFitnessBasicAlgorithm * cFibObjectFitnessBasicAlgorithm::clone() const{

	return new cFibObjectFitnessBasicAlgorithm( *this );
}


/**
 * This Method returns the best possible fitness the algorithm can create.
 * No individual with a better/ higher fitness can be created with this
 * algorithm.
 * The best case fitness is an cFibObjectFitness object with all
 * fitnessvalues set to 0.
 *
 * @return a cFibObjectFitness object with all fitnessvalues set to 0
 */
const cFibObjectFitnessBasic * cFibObjectFitnessBasicAlgorithm::getBestFitness() const{
	
	return pBestCaseFitness;
}


/**
 * This Method returns the worst case fitness for the algorithm and
 * originalindividual.
 * An individual with the worst case fitness can easyly be created.
 * This is the fitness of the originalindividual.
 * If no originalindividual is set NULL is returned.
 *
 * @return a refernce to the fitness of the originalindividual or NULL,
 * 	ff no originalindividual is set
 */
const cFibObjectFitnessBasic * cFibObjectFitnessBasicAlgorithm::getWorstCaseFitness() const{

	return pWorstCaseFitness;
}


/**
 * @see dWeightDistanceToOriginal
 * @return the weight for the dDistanceToOriginal value
 */
double cFibObjectFitnessBasicAlgorithm::getWeightDistanceToOriginal() const{

	return dWeightDistanceToOriginal;
}

/**
 * @see dWeightSize
 * @return the weight for the lSize value
 */
double cFibObjectFitnessBasicAlgorithm::getWeightSize() const{

	return dWeightSize;
}


/**
 * @see dWeightEvaluationTime
 * @return the weight for the lEvaluationTime value
 */
double cFibObjectFitnessBasicAlgorithm::getWeightEvaluationTime() const{

	return dWeightEvaluationTime;
}






