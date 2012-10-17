/**
 * @file cObjectFitnessAlgorithm
 * file name: cObjectFitnessAlgorithm.cpp
 * @author Betti Oesterholz
 * @date 26.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies the abstract basisclass of enviroment object
 * creating fitness objects.
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
 * This header specifies the abstract basisclass of enviroment algorithm
 * for creating fitness objects.
 * The better (higher) the fitness the better the object, the more likly
 * it should live and children should be created from it.
 *
 */
/*
History:
26.02.2010  Oesterholz  created
*/


#include "cObjectFitnessAlgorithm.h"

using namespace enviroment;


/**
 * constructor
 */
cObjectFitnessAlgorithm::cObjectFitnessAlgorithm():
		pOriginalIndividual( NULL ){
	//nothing to do
}


/**
 * constructor
 *
 * @param pInOriginalIndividual the individual, with which the fitness
 * 	should be evalued
 * 	Beware: this object won't be copied, so don't delete it as long
 * 	as this object exists
 */
cObjectFitnessAlgorithm::cObjectFitnessAlgorithm( cIndividual * pInOriginalIndividual ):
		pOriginalIndividual( pInOriginalIndividual ){
	//nothing to do
}


/**
 * copyconstructor
 *
 * @param objectFitnessAlgorithm the cObjectFitnessAlgorithm object to copy
 */
cObjectFitnessAlgorithm::cObjectFitnessAlgorithm( const cObjectFitnessAlgorithm &
		objectFitnessAlgorithm ):
		pOriginalIndividual( objectFitnessAlgorithm.pOriginalIndividual ){
	//nothing to do
}

/**
 * Destructor of the class cObjectFitnessAlgorithm.
 */
cObjectFitnessAlgorithm::~cObjectFitnessAlgorithm(){
	//nothing to do
}


/**
 * @return the name of this class
 */
string cObjectFitnessAlgorithm::getClassName() const{
	return "cObjectFitnessAlgorithm";
}

/**
 * This method sets the originalindividual.
 * The originalindividual is the individual with which the fitness
 * should be evalued.
 *
 * @see getOriginalIndividual()
 * @see pOriginalIndividual
 * @param pInOriginalIndividual a point to the the originalindividual to set
 * 	Beware: this object won't be copied, so don't delete it as long
 * 	as this object exists
 * @return true if the originalindividual is set to originalIndividum,
 * 	else false
 */
bool cObjectFitnessAlgorithm::setOriginalIndividual( cIndividual * pInOriginalIndividual ){
	pOriginalIndividual = pInOriginalIndividual;
	return true;
}


/**
 * @see setOriginalIndividual()
 * @see pOriginalIndividual
 * @return a pointer to the originalindividual or NULL if non exists
 * 	The originalindividual is the individual with which the
 * 	fitness is evalued.
 */
cIndividual * cObjectFitnessAlgorithm::getOriginalIndividual(){
	return pOriginalIndividual;
}

/**
 * @see setOriginalIndividual()
 * @see pOriginalIndividual
 * @return a pointer to the originalindividual or NULL if non exists
 * 	The originalindividual is the individual with which the
 * 	fitness is evalued.
 */
const cIndividual * cObjectFitnessAlgorithm::getOriginalIndividual() const{

	return pOriginalIndividual;
}







