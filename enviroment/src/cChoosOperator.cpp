/**
 * @file cChoosOperator
 * file name: cChoosOperator.cpp
 * @author Betti Oesterholz
 * @date 25.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements a class for selecting a good operator.
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
 * This file implements a class for selecting a good operator.
 * The selection method is weelselction.
 * Every operator has a propability p_i of selection which, is proportional
 * to it's fitnessvalue plus the ratio of the fitnesssum of all operations
 * divieded by the number of operations and 1000 .
 *
 * minFitness = the minimum fitness (@see cOperatorFitnessAlgorithm::getMinFitness())
 * minFitness2 = minFitness - fitnesssum / (#operations * 1000))
 * fitnesssum2 = fitnesssum - minFitness2 * #operations
 * p_i = (fitness_i - minFitness2) / fitnesssum2
 *
 * @see cOperation
 * @see cOperatorFitnessAlgorithm
 * @see cEnviroment
 */
/*
History:
25.03.2010  Oesterholz  created
06.06.2010  Oesterholz  method getClassName() added
*/


#include "cChoosOperator.h"
#include "cEnviroment.h"

#include <cstdlib>
#include <ctime>


using namespace enviroment;
using namespace std;

/**
 * standardconstructor
 */
cChoosOperator::cChoosOperator(){

	srand( time( NULL ) );
}


/**
 * Destructor of the class cChoosOperator.
 */
cChoosOperator::~cChoosOperator(){
	//nothing to do
}


/**
 * This method selects an operator. The selection method is weelselction.
 * Every operator has a propability p_i of selection which, is proportional
 * to it's fitnessvalue plus the ratio of the fitnesssum of all operations
 * divieded by the number of operations and 1000 .
 *
 * minFitness = the minimum fitness (@see cOperatorFitnessAlgorithm::getMinFitness())
 * minFitness2 = minFitness - fitnesssum / (#operations * 1000))
 * fitnesssum2 = fitnesssum - minFitness2 * #operations
 * p_i = (fitness_i - minFitness2) / fitnesssum2
 *
 * @return a pointer to the choosen operator, or NULL if non can be selected
 * 	Beware: You have to delete the returned object after usage.
 */
cOperation * cChoosOperator::choosOperator() const{

	cEnviroment * pEnviroment = cEnviroment::getInstance();
	
	if ( pEnviroment == NULL ){
		//nothing to select from
		return NULL;
	}
	
	cOperatorFitnessAlgorithm * pOpFitnessAlgorithm =
		pEnviroment->getOperatorFitnessAlgorithm();
	
	if ( pOpFitnessAlgorithm == NULL ){
		//nothing to select from
		return NULL;
	}
	list< pair< const cOperation*, double > > liOperators =
		pOpFitnessAlgorithm->getFitness();
	
	if ( liOperators.empty() ){
		return NULL;
	}

	const double dMinFitness = pOpFitnessAlgorithm->getMinFitness();
	double dFitnessSum = pOpFitnessAlgorithm->getFitnessSum();
	
	const double dMinFitness2 = dMinFitness - dFitnessSum / (liOperators.size() * 1000.0);
	const double dFitnessSum2 = dFitnessSum - dMinFitness2 * liOperators.size();
	
	cOperationIdentifier operationId( pEnviroment->getAlgorithmIdentifier() );
	if ( 0.0 < dFitnessSum2 ){
		double dSelectedOperation =
			(double)( rand() ) / (double)( RAND_MAX ) * dFitnessSum2;
		
		for ( list< pair< const cOperation*, double > >::iterator
				itrOperation = liOperators.begin();
				itrOperation != liOperators.end(); itrOperation++ ){
			
			const double dFitness = itrOperation->second - dMinFitness2;
			if ( dSelectedOperation <= dFitness ){
				//return this operation
				return itrOperation->first->createInstance( operationId );
			}//else the weel goes round
			dSelectedOperation -= dFitness;
		}/*else no operator choosen (the fitness of all operators is 0.0)
		-> all operators have equal propability to get choosen*/
	}
	unsigned long ulSelectedOperation = rand() % liOperators.size();
	
	list< pair< const cOperation*, double > >::iterator itrOperation;
	for ( itrOperation = liOperators.begin();
			(itrOperation != liOperators.end()) && (ulSelectedOperation != 0);
			itrOperation++, ulSelectedOperation-- ){
		//nothing to do
	}
	if ( ulSelectedOperation == 0 ){
		return itrOperation->first->createInstance( operationId );
	}//else
	
	return liOperators.front().first->createInstance( operationId );
}


/**
 * This method clones this object.
 *
 * @return a clone of this object
 */
cChoosOperator * cChoosOperator::clone() const{

	return new cChoosOperator( *this );
}


/**
 * @return the name of this class
 */
string cChoosOperator::getClassName() const{
	return "cChoosOperator";
}







