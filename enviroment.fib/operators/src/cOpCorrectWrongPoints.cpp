/**
 * @file cOpCorrectWrongPoints
 * file name: cOpCorrectWrongPoints.cpp
 * @author Betti Oesterholz
 * @date 15.10.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This Operator correct points, of an choosen individual, that are
 * different to the original object.
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
 * This Operator correct points, of an choosen individual, that are
 * different to the original object.
 * It will create some result individuals. Each result individual will
 * have all the wrong points, which distance to the original points is
 * greate than a treshhold, corrected.
 *
 * @see cOperationFib
 * @see cOperation
 * @see cEnviroment
 */
/*
History:
15.10.2010  Oesterholz  created
18.01.2011  Oesterholz  Bugfix: deleting individual clones with deleteObject()
*/

#include "cOpCorrectWrongPoints.h"

#include "cEnviroment.h"
#include "cObjectFitnessAlgorithm.h"
#include "cFibObjectFitnessAlgorithm.h"

#include "cFibIndividual.h"

#include "fibDatatyps.h"
#include "cFibElement.h"
#include "cTypeDimension.h"
#include "cDomains.h"
#include "cDomain.h"
#include "cDomainVectorBasis.h"

#include "nCorrectPoints.h"

#include "nReduceFibObject.h"

#include <list>
#include <ctime>
#include <cmath>

using namespace std;
using namespace fib::algorithms::nCorrectFibObject::nCorrectPoints;
using namespace fib::algorithms::nReduceFibObject;
using namespace enviroment;
using namespace enviroment::fib;




/**
 * The standardconstructor for the operation.
 * It will create the operation, but won't start it.
 *
 * @param operationId the identifer for the operation
 */
cOpCorrectWrongPoints::cOpCorrectWrongPoints( const cOperationIdentifier & operationId ):
		cOperationFib( operationId ){
	//nothing to do
}


/**
 * Destructor of the class cOpCorrectWrongPoints.
 */
cOpCorrectWrongPoints::~cOpCorrectWrongPoints(){
	//nothing to do
}


/**
 * This method creats a new instance of this operator.
 * Beware: You have to delete the instance after usage.
 *
 * @param operationId the identifer for the operation
 * @return a pointer to a new instance of this operation
 */
cOpCorrectWrongPoints * cOpCorrectWrongPoints::createInstance(
		const cOperationIdentifier & operationId ) const{
	
	return new cOpCorrectWrongPoints( operationId );
}


/**
 * This method runs the operation.
 * It will wait till the operation is ended befor returning.
 * Beware: If overwriten call setIsRunning( false ), when the operation
 * is done.
 *
 * @see start()
 * @see stop()
 * @see setIsRunning()
 * @return true if the operation was started
 */
bool cOpCorrectWrongPoints::run(){
	
	DEBUG_OUT_L1(<<getName()<<"::run() started"<<endl<<flush);
	
	if ( isRunning() || bStop ){
		//the operation runs allready
		return false;
	}
	
	cEnviroment * pEnviroment = cEnviroment::getInstance();
	
	if ( pEnviroment == NULL ){
		//no enviroment for the operation
		return false;
	}
	//check if the individualtype is correct
	if ( pEnviroment->OPERATION_DOMAIN != OPERATION_DOMAIN ){
		//wrong enviromenttype for the operation
		return false;
	}
	setIsRunning( true );
	
	DEBUG_OUT_L1(<<getName()<<"::run() getting individual"<<endl<<flush);

	//choose random fib -individual
	cFibIndividual * pIndividual = ((cFibIndividual*)(pEnviroment->getIndividual()));
	if ( pIndividual == NULL ){
		setIsRunning( false );
		return true;
	}
	
	cFibElement * pFibObject = pIndividual->getFibObject();
	if ( pFibObject == NULL ){
		
		delete pIndividual;
		setIsRunning( false );
		return true;
	}
	
	//get the original individual
	const cObjectFitnessAlgorithm * pFitnessAlgorithm =
		pEnviroment->getFitnessAlgorithm();
	
	if ( pFitnessAlgorithm == NULL ){
		//can't run
		delete pIndividual;
		setIsRunning( false );
		return false;
	}
	if ( pFitnessAlgorithm->getClassName().compare( 0, 17, "cFibObjectFitness" ) != 0 ){
		//can't run -> not an fib -enviroment
		delete pIndividual;
		setIsRunning( false );
		return false;
	}
	
	const cEvaluePositionList * pOrginalPositionsData = ((cFibObjectFitnessAlgorithm*)(
		pFitnessAlgorithm))->getOriginalPositionList();
	if ( pOrginalPositionsData == NULL ){
		delete pIndividual;
		setIsRunning( false );
		return true;
	}
	const unsignedLongFib ulNumberOfPoints = pOrginalPositionsData->liEvaluedPositionData.size();
	if ( ulNumberOfPoints < 1 ){
		delete pIndividual;
		setIsRunning( false );
		return true;
	}

	/*chose random distances of properties (betwean original and evalued),
	till which a point is wrong*/
	//choose random point
	size_t iChoosenPoint = rand() % ulNumberOfPoints;
	
	DEBUG_OUT_L2(<<"choosen point for maximal acceptebel difference: "<<iChoosenPoint<<endl<<flush);

	list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
		itrPoint = pOrginalPositionsData->liEvaluedPositionData.begin();
	for ( ; ( itrPoint != pOrginalPositionsData->liEvaluedPositionData.end() ) &&
			( 0 < iChoosenPoint );
			itrPoint++, iChoosenPoint-- ){
		//nothing to do
	}
	if ( itrPoint == pOrginalPositionsData->liEvaluedPositionData.end() ){
		DEBUG_OUT_EL2(<<"Error: Non existing point choosen"<<endl<<flush);
		delete pIndividual;
		setIsRunning( false );
		return true;
	}
	list< cVectorProperty > liActualProperties = itrPoint->second;
	liActualProperties.sort( cVectorProperty::lowerPropertyVector );
	//the maximal acceptebel difference for the properties
	const list< cVectorProperty > liPropertiesNull;
	doubleFib dMaxDifference = cEvaluePositionList::distanceOfProperties(
		liPropertiesNull, liActualProperties );
	
	//the list of distances of properties, till which a point is wrong
	list<doubleFib> liDistancesCountedWrong;
	liDistancesCountedWrong.push_back( 0.0 );
	DEBUG_OUT_L2(<<1<<"'th maximal acceptebel difference: "<<liDistancesCountedWrong.back()<<endl<<flush);
	
	if ( rand() % 4 == 0 ){
		//choose more than one distances of properties, till which a point is wrong
		unsignedIntFib uiNumberDistancesCountedWrong = 2;
		if ( rand() % 4 != 0 ){
			//use 1 till 8 DistancesCountedWrong
			uiNumberDistancesCountedWrong = (rand() % 8) + 1;
		}else{
			//use 1 till 65 DistancesCountedWrong
			uiNumberDistancesCountedWrong = (rand() % 8) * (rand() % 8 + 1) + rand() % 8 + 1;
		}
		if ( 2 <= uiNumberDistancesCountedWrong ){
			//add the choosen maximal distance
			liDistancesCountedWrong.push_back( dMaxDifference );
			DEBUG_OUT_L2(<<2<<"'th maximal acceptebel difference: "<<liDistancesCountedWrong.back()<<endl<<flush);
		}
		
		for ( unsignedIntFib uiActualDistances = 3;
				uiActualDistances <= uiNumberDistancesCountedWrong;
				uiActualDistances++ ){
			
			liDistancesCountedWrong.push_back( dMaxDifference / (doubleFib)(
				rand() % (uiNumberDistancesCountedWrong * uiNumberDistancesCountedWrong) + 1 ) );
			DEBUG_OUT_L2(<<uiActualDistances<<"'th maximal acceptebel difference: "<<liDistancesCountedWrong.back()<<endl<<flush);
		}
		liDistancesCountedWrong.sort();
		liDistancesCountedWrong.unique();//remove double elements
	}//else yust use 0.0 for DistancesCountedWrong
	
	DEBUG_OUT_L2(<<"starting replaceWrongPoints() "<<endl<<flush);
	list<cFibElement *> liCorrectedFibObjects = replaceWrongPoints(
		pOrginalPositionsData->liEvaluedPositionData,
		pFibObject, liDistancesCountedWrong );
	
	DEBUG_OUT_L2(<<"replaceWrongPoints() returned "<<liCorrectedFibObjects.size()<<" fib-objects"<<endl<<flush);
	
	if ( liCorrectedFibObjects.empty() ){
		DEBUG_OUT_EL2(<<"Error: No fib objects corrected"<<endl<<flush);
		delete pIndividual;
		setIsRunning( false );
		return false;
	}
	
	//insert the created fib -objects
	DEBUG_OUT_L2(<<"inserting fib-objects"<<endl<<flush);
	bool bAllIndividualsInserted = true;
	list<cIndividualIdentifier> liParents;
	liParents.push_back( pIndividual->getInfo()->getIdentifier() );
	while ( ! liCorrectedFibObjects.empty() ){
		
		cFibElement * pFibObjectCorrected = liCorrectedFibObjects.back();
		
		//remove from the individual overwritten underobjects
		DEBUG_OUT_L2(<<"removeOverwrittenUnderObjects()"<<endl<<flush);
		removeOverwrittenUnderObjects( *pFibObjectCorrected );
	
		//if the fib -objects was changed -> insert changed individual into the enviroment
		DEBUG_OUT_L2(<<"inserting indiviual into enviroment"<<endl<<flush);
		
		bAllIndividualsInserted &= insertFibObjectIntoEnviroment(
			pFibObjectCorrected, liParents );
		
		if ( pFibObject == pFibObjectCorrected ){
			//this is the original individual fib -object
			DEBUG_OUT_L2(<<"deleting original individual"<<endl<<flush);
			delete pIndividual;
		}else{//this is a created fib -object
			DEBUG_OUT_L2(<<"deleting individual clone"<<endl<<flush);
			pFibObjectCorrected->deleteObject();
		}
		liCorrectedFibObjects.pop_back();
	}
	setIsRunning( false );
	
	DEBUG_OUT_L1(<<getName()<<"::run() done bIndividualInserted="<<(bAllIndividualsInserted?"true":"false")<<endl<<flush);
	return bAllIndividualsInserted;
}


/**
 * @return the (class-)name of the operation
 */
string cOpCorrectWrongPoints::getName() const{
	return "cOpCorrectWrongPoints";
}





