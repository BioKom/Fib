/**
 * @file cIndividualSelectionWeel
 * file name: cIndividualSelectionWeel.cpp
 * @author Betti Oesterholz
 * @date 17.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for selecting a good individual.
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
 * This header specifies a class for selecting a good individual from the
 * enviroment.
 * The selection method is weelselction.
 * Every individual has a propability of selection which is proportional
 * to it's fitnessvalue or a minimum propability, if it's fitness is below
 * the minimum/ worst case fitness.
 * The minimum probability p_min is: p_min = 1 / (#individuals * 1024)
 * 	(#individuals = the count of individuals to select from)
 *
 * @see cEnviroment
 */
/*
History:
17.03.2010  Oesterholz  created
06.06.2010  Oesterholz  method getClassName() added
*/

#include "cIndividualSelectionWeel.h"

#include "cEnviroment.h"
#include "cObjectFitnessAlgorithm.h"

#include <list>
#include <cstdlib>
#include <ctime>


using namespace enviroment;
using namespace std;



/**
 * standardconstructor
 */
cIndividualSelectionWeel::cIndividualSelectionWeel(){

	srand( time( NULL ) );
}


/**
 * Destructor of the class cIndividualSelectionWeel.
 */
cIndividualSelectionWeel::~cIndividualSelectionWeel(){
	//nothing to do
}


/**
 * @return a pointer to the selected individualdentifier, or the identifier
 * 	for no individual (@see cIndividualIdentifier::getNoIndividualIdentifier())
 */
cIndividualIdentifier cIndividualSelectionWeel::getIndividualIdentifier() const{

	cEnviroment * pEnviroment = cEnviroment::getInstance();
	
	if ( pEnviroment == NULL ){
		//nothing to select from
		return cIndividualIdentifier::getNoIndividualIdentifier();;
	}
	//evalue the individuals to select from
	list<const cIndividualInfo*> liAllLivingIndividualsInfos =
		pEnviroment->getIndividualInfos( 1 );
	if ( liAllLivingIndividualsInfos.empty() ){
		//no individuals to select
		return cIndividualIdentifier::getNoIndividualIdentifier();;
	}
	
	//evalue for every individual the propability to be selected
	const size_t iCountofIndividuals = liAllLivingIndividualsInfos.size();
	const double dMinPropability = 1.0 / ((double)(iCountofIndividuals) * 1024.0);
	
	/*the vector to store the propability to;
	first pair element: the identifier of the individual
	second pair element: the propability of the individual*/
	list< pair< cIndividualIdentifier, double > > liIdividualPropabilities;
	//the sum to normalize the propabilities
	double dPropabilitySum = 0;
	
	for ( list<const cIndividualInfo*>::iterator itrIndividualInfo =
			liAllLivingIndividualsInfos.begin();
			(itrIndividualInfo != liAllLivingIndividualsInfos.end() );
			itrIndividualInfo++ ){
		
		const cObjectFitness * pFitness = (*itrIndividualInfo)->getFitness();
		
		if ( pFitness == NULL ){
			//no fitness for the individual -> skip individual
			continue;
		}
		double dPropability = 0.0;
		if ( (pFitness->getFitnessAlgorithm() != NULL) &&
				(pFitness->getFitnessAlgorithm()->getWorstCaseFitness() != NULL) ){
			
			const double dMinFitness =
				pFitness->getFitnessAlgorithm()->getWorstCaseFitness()->getFitness();
			
			dPropability = pFitness->getFitness() - dMinFitness;
			
			if ( dPropability < 0.0 ){
				dPropability = 0.0;
			}
		}//else{ pobability is dMinPropability }
		liIdividualPropabilities.push_back( make_pair(
			(*itrIndividualInfo)->getIdentifier(), dPropability ) );
		dPropabilitySum += dPropability;
	}
	if ( dPropabilitySum <= 0.0 ){
		//beware of division trought 0
		dPropabilitySum = dMinPropability * (double)(iCountofIndividuals);
	}
	//set minimum propabilities
	for ( list< pair< cIndividualIdentifier, double > >::iterator
			itrPropability = liIdividualPropabilities.begin();
			(itrPropability != liIdividualPropabilities.end() );
			itrPropability++ ){
		
		if ( (itrPropability->second / dPropabilitySum) < dMinPropability ){
			const double dOldPropability = itrPropability->second;
			itrPropability->second = dMinPropability * dPropabilitySum;
			dPropabilitySum += dMinPropability * dPropabilitySum - dOldPropability;
		}
	}
	
	//select a roandom individual (weelselection)
	double dSelectedIndividual =
		(double)( rand() ) / (double)( RAND_MAX ) * dPropabilitySum;
	for ( list< pair< cIndividualIdentifier, double > >::iterator
			itrPropability = liIdividualPropabilities.begin();
			(itrPropability != liIdividualPropabilities.end() );
			itrPropability++ ){
		
		if ( dSelectedIndividual < itrPropability->second ){
			
			return itrPropability->first;
		}
		dSelectedIndividual -= itrPropability->second;
	}

	return liIdividualPropabilities.front().first;
}

/**
 * This method clones this object.
 *
 * @return a clone of this object
 */
cIndividualSelectionWeel * cIndividualSelectionWeel::clone() const{

	return new cIndividualSelectionWeel( *this );
}


/**
 * @return the name of this class
 */
string cIndividualSelectionWeel::getClassName() const{
	return "cIndividualSelectionWeel";
}



