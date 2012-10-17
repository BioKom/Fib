/**
 * @file cFibObjectFitnessBasic
 * file name: cFibObjectFitnessBasic.h
 * @author Betti Oesterholz
 * @date 02.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies the class of simple enviroment fib -object fitnesses.
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
 * This header specifies the class of simple enviroment fib -object fitnesses.
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

#ifndef ___C_FIB_OBJECT_FITNESS_BASIC_H__
#define ___C_FIB_OBJECT_FITNESS_BASIC_H__

#include "version.h"

#include "cFibObjectFitness.h"

#include <string>


using std::string;

namespace enviroment{
namespace fib{

//cyclic dependencies
class cFibObjectFitnessBasicAlgorithm;


class cFibObjectFitnessBasic: public cFibObjectFitness{

friend class cFibObjectFitnessBasicAlgorithm;

protected:

	/**
	 * The distance to the original individual.
	 * It is the sum of the distances of all values of propertyvectorelements
	 * betwean the represented and original fib -object of all positions
	 * which are inside the dimension bounderies.
	 */
	double dDistanceToOriginal;
	
	/**
	 * The weight for the dDistanceToOriginal value.
	 */
	double dWeightDistanceToOriginal;
	
	/**
	 * The (compressed) size of the represented fib -object.
	 *
	 * @see cFibElement::getCompressedSize()
	 */
	unsigned long lSize;
	
	/**
	 * The weight for the lSize value.
	 */
	double dWeightSize;
	
	/**
	 * The evaluating time of the represented fib -object.
	 *
	 * @see cFibElement::getTimeNeed()
	 */
	unsigned long lEvaluationTime;
	
	/**
	 * The weight for the lEvaluationTime value.
	 */
	double dWeightEvaluationTime;

#ifdef TEST
public:
#endif

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
	cFibObjectFitnessBasic( double dInDistanceToOriginal, unsigned long lInSize,
		unsigned long lInEvaluationTime, double dInWeightDistanceToOriginal=1.0,
		double dInWeightSize=1.0, double dInWeightEvaluationTime=1.0,
		cFibObjectFitnessBasicAlgorithm * pInFibObjectFitnessAlgorithm=NULL );

public:

	/**
	 * copyconstructor
	 *
	 * @param objectFitness the cObjectFitness object to copy
	 */
	cFibObjectFitnessBasic( const cFibObjectFitnessBasic & objectFitness );
	
	/**
	 * Destructor of the class cFibObjectFitnessBasic.
	 */
	virtual ~cFibObjectFitnessBasic();
	
	/**
	 * @return the name of this class
	 */
	virtual string getClassName() const;

	/**
	 * @return the algorithm with which this fitness was created;
	 * 	if NULL no algorithm had created this object
	 */
	const cFibObjectFitnessBasicAlgorithm * getFitnessAlgorithm() const;

	/**
	 * This Method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cFibObjectFitnessBasic * clone() const;
	
	/**
	 * Comparisson on equal operator for two fitness objects.
	 *
	 * @param fitness the fitnessobject to compare this fitnessobject to
	 * @return true if the fitness this object represents is equal to the
	 * 	fitness the given object fitness represents
	 */
	virtual bool operator==( const cFibObjectFitnessBasic &fitness ) const;

	/**
	 * @see dDistanceToOriginal
	 * @return the distance to the original individual
	 */
	double getDifferenceToOriginal() const;
	
	/**
	 * This method changes the dDistanceToOriginal value.
	 * dDistanceToOriginal += lDeltaToOriginal
	 *
	 * @see dDistanceToOriginal
	 * @param dDeltaToOriginal the value about which the
	 * 	dDistanceToOriginal is to change
	 * @return true if the dDistanceToOriginal is changed, else false
	 */
	bool changeDifferenceToOriginal( double dDeltaToOriginal );
	
	/**
	 * @see dWeightDistanceToOriginal
	 * @return the weight for the dDistanceToOriginal value
	 */
	double getWeightDistanceToOriginal() const;
	
	/**
	 * @see lSize
	 * @return the (compressed) size of the represented fib -object
	 */
	unsigned long getSize() const;
	
	/**
	 * This method changes the lSize value.
	 * lSize += lDeltaSize
	 *
	 * @see lSize
	 * @param lDeltaSize the value about which the lSize is to change
	 * @return true if the lSize is changed, else false
	 */
	bool changeSize( long lDeltaSize );
	
	/**
	 * @see dWeightSize
	 * @return the weight for the lSize value
	 */
	double getWeightSize() const;
	
	/**
	 * @see lEvaluationTime
	 * @return he evaluating time of the represented fib -object
	 */
	unsigned long getTime() const;
	
	/**
	 * This method changes the lEvaluationTime value.
	 * lEvaluationTime += lDeltaEvalueTime
	 *
	 * @see lEvaluationTime
	 * @param lDeltaSize the value about which the lEvaluationTime is to change
	 * @return true if the lEvaluationTime is changed, else false
	 */
	bool changeTime( long lDeltaEvalueTime );
	
	/**
	 * @see dWeightEvaluationTime
	 * @return the weight for the lEvaluationTime value
	 */
	double getWeightEvaluationTime() const;


protected:
	
	/**
	 * This method will update the whool fitness with the fitnessparts.
	 */
	virtual void updateFitness();

};//end class cFibObjectFitnessBasic

};//end namespace fib
};//end namespace enviroment

#endif //___C_FIB_OBJECT_FITNESS_BASIC_H__







