/**
 * @file cFibObjectFitnessBasic
 * file name: cFibObjectFitnessBasic.h
 * @author Betti Oesterholz
 * @date 02.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents simple enviroment fib -object fitnesses.
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
 * This class represents simple enviroment fib -object fitnesses.
 * The fitness consists of tree parts the differnece to the original
 * individual, the size of the fib -object and it's time value for
 * evaluating it. This tree values are combined to a fitnessvalue.
 * Each of the values are multiplyed with ther weight and then all tree
 * are added to get the entire fitness.
 *
 * dFittness = -1 * ( dDistanceToOriginal * dWeightDistanceToOriginal +
 * 	lSize * dWeightSize + lEvaluationTime * dWeightEvaluationTime )
 */
/*
History:
02.03.2010  Oesterholz  created
*/

#include "cFibObjectFitnessBasic.h"
#include "cFibObjectFitnessBasicAlgorithm.h"


using namespace enviroment::fib;



/**
 * constructor
 *
 * @param dInFittness a value for the fitness of the object;
 * 	the higher this value is the better the fitness
 * @param dInDistanceToOriginal the distance to the original individual
 * 	@see dDistanceToOriginal
 * @param lInSize the (compressed) size of the represented fib -object
 * @param lInEvaluationTime the evaluating time of the represented fib -object
 * @param dInWeightDistanceToOriginal the weight for the lInDistanceToOriginal value
 * @param dInWeightSize the weight for the lInSize value
 * @param dInWeightEvaluationTime the weight for the lInEvaluationTime value
 * @param pInFibObjectFitnessAlgorithm the algorithm with which this
 * 	fitness was created; if NULL no algorithm had created this object;
 * 	Beware: this object won't be copied, if you delete it
 * 	getFitnessAlgorithm() will return an invalid pointer
 */
cFibObjectFitnessBasic::cFibObjectFitnessBasic( double dInDistanceToOriginal,
		unsigned long lInSize, unsigned long lInEvaluationTime, double dInWeightDistanceToOriginal,
		double dInWeightSize, double dInWeightEvaluationTime,
		cFibObjectFitnessBasicAlgorithm * pInFibObjectFitnessAlgorithm ):
		cFibObjectFitness( 0.0, pInFibObjectFitnessAlgorithm ),
		dDistanceToOriginal( dInDistanceToOriginal ),
		dWeightDistanceToOriginal( dInWeightDistanceToOriginal ),
		lSize( lInSize ), dWeightSize( dInWeightSize ),
		lEvaluationTime( lInEvaluationTime ),
		dWeightEvaluationTime( dInWeightEvaluationTime ){
	
	updateFitness();
}


/**
 * copyconstructor
 *
 * @param objectFitness the cFibObjectFitnessBasic object to copy
 */
cFibObjectFitnessBasic::cFibObjectFitnessBasic( const cFibObjectFitnessBasic & objectFitness ):
		cFibObjectFitness( objectFitness.getFitness(), objectFitness.getFitnessAlgorithm() ),
		dDistanceToOriginal( objectFitness.dDistanceToOriginal ),
		dWeightDistanceToOriginal( objectFitness.dWeightDistanceToOriginal ),
		lSize( objectFitness.lSize ), dWeightSize( objectFitness.dWeightSize ),
		lEvaluationTime( objectFitness.lEvaluationTime ),
		dWeightEvaluationTime( objectFitness.dWeightEvaluationTime ){
	//nothing to do
}


/**
 * Destructor of the class cFibObjectFitnessBasic.
 */
cFibObjectFitnessBasic::~cFibObjectFitnessBasic(){
	//nothing to do
}


/**
 * @return the name of this class
 */
string cFibObjectFitnessBasic::getClassName() const{

	return "cFibObjectFitnessBasic";
}


/**
 * @return the algorithm with which this fitness was created;
 * 	if NULL no algorithm had created this object
 */
const cFibObjectFitnessBasicAlgorithm * cFibObjectFitnessBasic::
		getFitnessAlgorithm() const{
	
	return (cFibObjectFitnessBasicAlgorithm*)(cFibObjectFitness::
		getFitnessAlgorithm());
}


/**
 * This Method clones this object.
 *
 * @return a clone of this object
 */
cFibObjectFitnessBasic * cFibObjectFitnessBasic::clone() const{

	return new cFibObjectFitnessBasic( *this );
}


/**
 * Comparisson on equal operator for two fitness objects.
 *
 * @param fitness the fitnessobject to compare this fitnessobject to
 * @return true if the fitness this object represents is equal to the
 * 	fitness the given object fitness represents
 */
bool cFibObjectFitnessBasic::operator==( const cFibObjectFitnessBasic &fitness ) const{

	if ( ! ( cFibObjectFitness::operator == ( fitness ) ) ){
		return false;
	}
	
	if ( dDistanceToOriginal != fitness.dDistanceToOriginal ){
		return false;
	}
	if ( dWeightDistanceToOriginal != fitness.dWeightDistanceToOriginal ){
		return false;
	}
	if ( lSize != fitness.lSize ){
		return false;
	}
	if ( dWeightSize != fitness.dWeightSize ){
		return false;
	}
	if ( lEvaluationTime != fitness.lEvaluationTime ){
		return false;
	}
	if ( dWeightEvaluationTime != fitness.dWeightEvaluationTime ){
		return false;
	}

	return true;
}


/**
 * @see dDistanceToOriginal
 * @return the distance to the original individual
 */
double cFibObjectFitnessBasic::getDifferenceToOriginal() const{

	return dDistanceToOriginal;
}


/**
 * This method changes the dDistanceToOriginal value.
 * dDistanceToOriginal += lDeltaToOriginal
 *
 * @see dDistanceToOriginal
 * @param dDeltaToOriginal the value about which the
 * 	dDistanceToOriginal is to change
 * @return true if the dDistanceToOriginal is changed, else false
 */
bool cFibObjectFitnessBasic::changeDifferenceToOriginal( double dDeltaToOriginal ){
	
	dDistanceToOriginal += dDeltaToOriginal;
	updateFitness();
	return true;
}


/**
 * @see dWeightDistanceToOriginal
 * @return the weight for the dDistanceToOriginal value
 */
double cFibObjectFitnessBasic::getWeightDistanceToOriginal() const{

	return dWeightDistanceToOriginal;
}


/**
 * @see lSize
 * @return the (compressed) size of the represented fib -object
 */
unsigned long cFibObjectFitnessBasic::getSize() const{

	return lSize;
}


/**
 * This method changes the lSize value.
 * lSize += lDeltaSize
 *
 * @see lSize
 * @param lDeltaSize the value about which the lSize is to change
 * @return true if the lSize is changed, else false
 */
bool cFibObjectFitnessBasic::changeSize( long lDeltaSize ){
	
	lSize += lDeltaSize;
	updateFitness();
	return true;
}


/**
 * @see dWeightSize
 * @return the weight for the lSize value
 */
double cFibObjectFitnessBasic::getWeightSize() const{

	return dWeightSize;
}


/**
 * @see lEvaluationTime
 * @return he evaluating time of the represented fib -object
 */
unsigned long cFibObjectFitnessBasic::getTime() const{

	return lEvaluationTime;
}


/**
 * This method changes the lEvaluationTime value.
 * lEvaluationTime += lDeltaEvalueTime
 *
 * @see lEvaluationTime
 * @param lDeltaSize the value about which the lEvaluationTime is to change
 * @return true if the lEvaluationTime is changed, else false
 */
bool cFibObjectFitnessBasic::changeTime( long lDeltaEvalueTime ){
	
	lEvaluationTime += lDeltaEvalueTime;
	updateFitness();
	return true;
}


/**
 * @see dWeightEvaluationTime
 * @return the weight for the lEvaluationTime value
 */
double cFibObjectFitnessBasic::getWeightEvaluationTime() const{

	return dWeightEvaluationTime;
}



/**
 * This method will update the whool fitness with the fitnessparts.
 */
void cFibObjectFitnessBasic::updateFitness(){

	dFittness = -1 * ( dDistanceToOriginal * dWeightDistanceToOriginal +
		((double)lSize) * dWeightSize +
		((double)lEvaluationTime) * dWeightEvaluationTime );
}







