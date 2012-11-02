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
15.03.2010  Oesterholz  in initEnviroment() lokal pOriginalIndividual
	changed to pIndOriginalIndividual
*/

//TODO weg
//#define DEBUG


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
	
	DEBUG_OUT_L2(<<"cInitFibEnviroment("<<this<<")::initEnviroment() start"<<endl<<flush);
	
	DEBUG_OUT_L2(<<"cInitFibEnviroment("<<this<<")::initEnviroment(): get enviroment"<<endl<<flush);
	cEnviroment * pEnviroment = cEnviroment::getInstance();
	
	if ( pEnviroment == NULL ){
		//can't initialisize
		DEBUG_OUT_EL2(<<"cInitFibEnviroment("<<this<<")::initEnviroment() done; Error: can't initialisize, no enviroment"<<endl<<flush);
		return false;
	}
	DEBUG_OUT_L2(<<"cInitFibEnviroment("<<this<<")::initEnviroment(): get fitness algorithm"<<endl<<flush);
	const cObjectFitnessAlgorithm * pFitnessAlgorithm =
		pEnviroment->getFitnessAlgorithm();
	
	if ( pFitnessAlgorithm == NULL ){
		//can't initialisize
		DEBUG_OUT_EL2(<<"cInitFibEnviroment("<<this<<")::initEnviroment() done; Error: can't initialisize, no fitness algorithm"<<endl<<flush);
		return false;
	}
	if ( pFitnessAlgorithm->getClassName().compare( 0, 17, "cFibObjectFitness" ) != 0 ){
		//can't initialisize -> not an fib -enviroment
		DEBUG_OUT_EL2(<<"cInitFibEnviroment("<<this<<")::initEnviroment() done; Error: can't initialisize -> not an fib enviroment, but "<<pFitnessAlgorithm->getClassName()<<endl<<flush);
		return false;
	}
	if ( pOriginalIndividual ){
		//load the original individual
		DEBUG_OUT_L2(<<"cInitFibEnviroment("<<this<<")::initEnviroment(): load the original individual ("<<pOriginalIndividual<<") into the fitness algorithm ("<<pFitnessAlgorithm<<")"<<endl<<flush);
		((cFibObjectFitnessAlgorithm*)(pFitnessAlgorithm))->
			setOriginalFibObject( pOriginalIndividual );
	}
	
	//insert a individual into the enviroment (cEnviroment)
	DEBUG_OUT_L2(<<"cInitFibEnviroment("<<this<<")::initEnviroment(): get original individual"<<endl<<flush);
	cFibIndividual * pIndOriginalIndividual = ((cFibObjectFitnessAlgorithm*)(
		pFitnessAlgorithm))->getOriginalIndividual();
		
	DEBUG_OUT_L2(<<"cInitFibEnviroment("<<this<<")::initEnviroment(): the original individual ("<<pIndOriginalIndividual<<") will be used"<<endl<<flush);
	
	if ( pIndOriginalIndividual == NULL ){
		//can't initialisize -> not original individual
		DEBUG_OUT_EL2(<<"cInitFibEnviroment("<<this<<")::initEnviroment() done; Error: can't initialisize -> not original individual"<<endl<<flush);
		return false;
	}
	DEBUG_OUT_L2(<<"cInitFibEnviroment("<<this<<")::initEnviroment(): set the original individual ("<<pIndOriginalIndividual<<") for the the enviroment"<<endl<<flush);
	const bool bIndividualInserted =
		pEnviroment->insertIndividual( pIndOriginalIndividual );
	if ( ! bIndividualInserted ){
		//can't initialisize
		DEBUG_OUT_EL2(<<"cInitFibEnviroment("<<this<<")::initEnviroment() done; Error: can't initialisize"<<endl<<flush);
		return false;
	}
	
	if ( pEnviroment->getOperatorFitnessAlgorithm() == NULL ){
		//the enviroment parameters arn't correct
		DEBUG_OUT_EL2(<<"cInitFibEnviroment("<<this<<")::initEnviroment() done; Error: the enviroment parameters arn't correct"<<endl<<flush);
		return false;
	}
	DEBUG_OUT_L2(<<"cInitFibEnviroment("<<this<<")::initEnviroment(): get list of possible operators"<<endl<<flush);
	list<const cOperation*> liOperations =
		pEnviroment->getOperatorFitnessAlgorithm()->getPossibleOperators();
	//call the cInitOperator
	for ( list<const cOperation*>::iterator itrOperation = liOperations.begin();
			itrOperation != liOperations.end(); itrOperation++ ){
		
		if ( (*itrOperation)->getName() == "cInitOperator" ){
			
			DEBUG_OUT_L2(<<"cInitFibEnviroment("<<this<<")::initEnviroment(): create init operator ("<<(*itrOperation)<<")"<<endl<<flush);
			
			cOperationIdentifier operationId( pEnviroment->getAlgorithmIdentifier() );
			
			cOperation * pInitOperation = (*itrOperation)->createInstance( operationId );
			
			if ( pInitOperation != NULL ){
				DEBUG_OUT_L2(<<"cInitFibEnviroment("<<this<<")::initEnviroment(): call init operator ("<<(*itrOperation)<<")"<<endl<<flush);
				pInitOperation->run();
				delete pInitOperation;
			}else{//error: couldn't create the init operation
				DEBUG_OUT_EL2(<<"cInitFibEnviroment("<<this<<")::initEnviroment() done; Error: couldn't create the init operation"<<endl<<flush);
				
				return false;
			}
			break;
		}
	}
	
	DEBUG_OUT_L2(<<"cInitFibEnviroment("<<this<<")::initEnviroment() done"<<endl<<flush);
	
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








