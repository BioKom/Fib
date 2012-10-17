/**
 * @file cInitFibEnviroment
 * file name: cInitFibEnviroment.cpp
 * @author Betti Oesterholz
 * @date 15.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for initialization of the enviroment.
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
 * This header specifies a abstract class for initialization of the enviroment.
 * the enviroment is intialisized for optimizing fib -individuals.
 * The intialization should:
 * 	- load the originalindividual
 * 	- insert a individual into the enviroment (cEnviroment)
 * 	- call the cInitOperator
 *
 */
/*
History:
15.03.2010  Oesterholz  created
*/


#include "cInitFibEnviroment.h"
#include "cEnviroment.h"
#include "cOperationIdentifier.h"
#include "cFibObjectFitnessAlgorithm.h"
#include "cFibIndividual.h"
#include "cOperatorFitnessAlgorithm.h"


#include "cFibElement.h"

using namespace fib;
using namespace enviroment::fib;
using namespace enviroment;



/**
 * constructor of cInitFibEnviroment
 *
 * @param pFibOriginal the original individual, with which the enviroment
 * 	should be initializised
 */
cInitFibEnviroment::cInitFibEnviroment( const cRoot & pFibOriginal ){
	
	pOriginalIndividual = (cRoot*)(pFibOriginal.clone());
}


/**
 * copyconstructor of cInitFibEnviroment
 *
 * @param initFibEnviroment cInitFibEnviroment to copy
 */
cInitFibEnviroment::cInitFibEnviroment( const cInitFibEnviroment & initFibEnviroment ){

	if ( initFibEnviroment.pOriginalIndividual ){
		pOriginalIndividual = (cRoot*)(initFibEnviroment.pOriginalIndividual->clone());
	}else{
		pOriginalIndividual = NULL;
	}
}


/**
 * destructor
 */
cInitFibEnviroment::~cInitFibEnviroment(){
	
	if ( pOriginalIndividual ){
		cFibElement::deleteObject( pOriginalIndividual );
	}
}


/**
 * @return a pointer to the object which is represented by the individual
 */
bool cInitFibEnviroment::initEnviroment() const{
	
	cEnviroment * pEnviroment = cEnviroment::getInstance();
	
	if ( pEnviroment == NULL ){
		//can't initialisize
		return false;
	}
	const cObjectFitnessAlgorithm * pFitnessAlgorithm =
		pEnviroment->getFitnessAlgorithm();
	
	if ( pFitnessAlgorithm == NULL ){
		//can't initialisize
		return false;
	}
	if ( pFitnessAlgorithm->getClassName().compare( 0, 17, "cFibObjectFitness" ) != 0 ){
		//can't initialisize -> not an fib -enviroment
		return false;
	}
	if ( pOriginalIndividual ){
		//load the originalindividual
		((cFibObjectFitnessAlgorithm*)(pFitnessAlgorithm))->
			setOriginalFibObject( pOriginalIndividual );
	}
	
	//insert a individual into the enviroment (cEnviroment)
	cFibIndividual * pOriginalIndividual = ((cFibObjectFitnessAlgorithm*)(
		pFitnessAlgorithm))->getOriginalIndividual();
	
	if ( pOriginalIndividual == NULL ){
		//can't initialisize -> not original individual
		return false;
	}
	const bool bIndividualInserted =
		pEnviroment->insertIndividual( pOriginalIndividual );
	if ( ! bIndividualInserted ){
		//can't initialisize
		return false;
	}
	
	if ( pEnviroment->getOperatorFitnessAlgorithm() == NULL ){
		//the enviromentparameters arn't correct
		return false;
	}
	list<const cOperation*> liOperations =
		pEnviroment->getOperatorFitnessAlgorithm()->getPossibleOperators();
	//call the cInitOperator
	for ( list<const cOperation*>::iterator itrOperation = liOperations.begin();
			itrOperation != liOperations.end(); itrOperation++ ){
		
		if ( (*itrOperation)->getName() == "cInitOperator" ){
			
			cOperationIdentifier operationId( pEnviroment->getAlgorithmIdentifier() );
			
			cOperation * pInitOperation = (*itrOperation)->createInstance( operationId );
			
			if ( pInitOperation != NULL ){
				pInitOperation->run();
				delete pInitOperation;
			}else{//error: couldn't create the init operation
				return false;
			}
			break;
		}
	}
	return true;
}


/**
 * This method clones this object.
 *
 * @return a clone of this object
 */
cInitFibEnviroment * cInitFibEnviroment::clone() const{
	
	return new cInitFibEnviroment( * this );
}


/**
 * @return the name of this class
 */
std::string cInitFibEnviroment::getClassName() const{
	
	return "cInitFibEnviroment";
}








