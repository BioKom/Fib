/**
 * @file cFibObjectFitness
 * file name: cFibObjectFitness.cpp
 * @author Betti Oesterholz
 * @date 28.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies the abstract basisclass of enviroment fib -object
 * fitnesses.
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
 * This header specifies the abstract basisclass of enviroment fib -object
 * fitnesses. This represents the fitness of a fib -object which is a
 * individuum in fib genetic algorithm (enviroment).
 * The better (higher) the fitness the better the fib -object, the more likly
 * it should live and children should be created from it.
 *
 */
/*
History:
28.02.2010  Oesterholz  created
*/

#include "cFibObjectFitness.h"

#include "cFibObjectFitnessAlgorithm.h"


using namespace enviroment::fib;


/**
 * constructor
 *
 * @param dInFittness a value for the fitness of the object;
 * 	the higher this value is the better the fitness
 * @param pInFibObjectFitnessAlgorithm the algorithm with which this
 * 	fitness was created; if NULL no algorithm had created this object
 * 	Beware: this object won't be copied, if you delete it
 * 	getFitnessAlgorithm() will return an invalid pointer
 */
cFibObjectFitness::cFibObjectFitness( double dInFittness,
		const cFibObjectFitnessAlgorithm * pInFibObjectFitnessAlgorithm ):
		cObjectFitness( dInFittness, pInFibObjectFitnessAlgorithm ){
	//nothing to do
}


/**
 * copyconstructor
 *
 * @param objectFitness the cFibObjectFitness object to copy
 */
cFibObjectFitness::cFibObjectFitness( const cFibObjectFitness & objectFitness ):
		cObjectFitness( objectFitness ){
	//nothing to do
}


/**
 * Destructor of the class cFibObjectFitness.
 */
cFibObjectFitness::~cFibObjectFitness(){
	//nothing to do
}


/**
 * @return the name of this class
 */
string cFibObjectFitness::getClassName() const{
	return "cFibObjectFitness";
}


/**
 * @return the algorithm with which this fitness was created;
 * 	if NULL no algorithm had created this object
 */
const cFibObjectFitnessAlgorithm *
		cFibObjectFitness::getFitnessAlgorithm() const{
	
	return (cFibObjectFitnessAlgorithm * )cObjectFitness::getFitnessAlgorithm();
}


/**
 * This Method clones this object.
 *
 * @return a clone of this object
 */
cFibObjectFitness * cFibObjectFitness::clone() const{
	
	return (cFibObjectFitness * )cObjectFitness::clone();
}


/**
 * Comparisson on equal operator for two fitness objects.
 *
 * @param fitness the fitnessobject to compare this fitnessobject to
 * @return true if the fitness this object represents is equal to the
 * 	fitness the given object fitness represents
 */
bool cFibObjectFitness::operator==( const cFibObjectFitness &fitness ) const{
	
	return (cFibObjectFitnessAlgorithm * )cObjectFitness::operator==( fitness );
}








