/**
 * @file cOperationFib
 * file name: cOperationFib.h
 * @author Betti Oesterholz
 * @date 19.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies the abstract basisclass for fib -operations.
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
 * This header specifies the abstract basisclass for fib -operations.
 * Overwrite the start() or run() method to implement the operation.
 *
 * Beware: If the variable bStop is true, stop the operation.
 *
 * @see cOperation
 * @see cEnviroment
 */
/*
History:
19.03.2010  Oesterholz  created
*/


#include "cOperationFib.h"

#include "cEnviroment.h"
#include "cFibIndividual.h"
#include "cFibObjectFitness.h"
#include "cFibObjectFitnessAlgorithm.h"

#include "operators.h"


using namespace enviroment;
using namespace enviroment::fib;


/**
 * The standardconstructor for the operation.
 * It will create the operation, but won't start it.
 *
 * @param operationId the identifer vor the operation
 */
cOperationFib::cOperationFib( const cOperationIdentifier & operationId ):
		cOperation( operationId, "cFibIndividual" ){
	//nothing to do
}


/**
 * Destructor of the class cOperationFib.
 */
cOperationFib::~cOperationFib(){
	//nothing to do
}


/**
 * This method insert the given fib object as a new individual into the
 * enviroment.
 *
 * @param fibObject the fib -object to insert
 * @param liParents a list with the identifiers of the parrent individuals
 * 	of the individual to insert
 * @return true if the individual was inserted, else false
 */
bool cOperationFib::insertFibObjectIntoEnviroment( cFibElement * fibObject,
		const list<cIndividualIdentifier> liParents ){
	
	cEnviroment * pEnviroment = cEnviroment::getInstance();
	
	if ( pEnviroment == NULL ){
		//no enviroment for the operation
		return false;
	}
	
	cFibObjectFitnessAlgorithm * pFitnessAlgorithm =
		( ( cFibObjectFitnessAlgorithm * )( pEnviroment->getFitnessAlgorithm() ) );
	if ( pFitnessAlgorithm == NULL ){
		return false;
	}
	
	cFibObjectFitness * pNewFitness =
		pFitnessAlgorithm->evalueFitness( fibObject );
	
	const cIndividualInfo * pBestIndividualInfo = pEnviroment->getBestIndividualInfo();
	const cObjectFitness * pBestFitness = NULL;
	if ( pBestIndividualInfo ){
		pBestFitness = pBestIndividualInfo->getFitness();
	}else{
		pBestFitness = pNewFitness;
	}
	
	cIndividualInfo newIndividualInfo( pEnviroment->getAlgorithmIdentifier(),
			liParents, *pNewFitness,
			getName(), "", *(getOperationIdentifier()),
			time_t( NULL ), getCpuRunTime(),
			pBestFitness );
	
	delete pNewFitness;
	
	cFibIndividual newIndividual( fibObject, newIndividualInfo, false );
	
	return pEnviroment->insertIndividual( &newIndividual, this );
}









