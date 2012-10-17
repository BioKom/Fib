/**
 * @file cFibObjectFitnessBasicAlgorithm
 * file name: cFibObjectFitnessBasicAlgorithm.h
 * @author Betti Oesterholz
 * @date 02.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies the simple class of fib -enviroment algorithm
 * creating fib -fitness objects.
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
 * @see cFibObjectFitness
 * @see cFibObjectFitnessBasic
 * @see cObjectFitnessAlgorithm
 * This header specifies the simple class of fib -enviroment algorithm
 * for creating fib -fitness objects.
 * The better (higher) the fitness the better the fib -object, the more likly
 * it should live and children should be created from it.
 *
 */
/*
History:
02.03.2010  Oesterholz  created
18.04.2010  Oesterholz  evalueObject() methods changed: not a function but
	an object is given to evalue the data
30.04.2010  Oesterholz  using cEvaluePositionListMemLimit to evalue the
	given (non original) fib -objects
05.07.2010  Oesterholz  some functions moved to classes in namespace fib
12.09.2010  Oesterholz  changes for the getOriginalPositionList() method
*/

#ifndef ___C_FIB_OBJECT_FITNESS_BASIC_ALGORITHMUS_H__
#define ___C_FIB_OBJECT_FITNESS_BASIC_ALGORITHMUS_H__

#include "version.h"

#include "cFibObjectFitnessAlgorithm.h"
#include "cFibObjectFitnessBasic.h"

#include "cRoot.h"

#include <string>


using std::string;

namespace enviroment{
namespace fib{


class cFibIndividual;//cyclic dependencie


class cFibObjectFitnessBasicAlgorithm: public cFibObjectFitnessAlgorithm{

protected:
	
	/**
	 * The weight for the dDistanceToOriginal value.
	 */
	double dWeightDistanceToOriginal;
	
	/**
	 * The weight for the lSize value.
	 */
	double dWeightSize;
	
	/**
	 * The weight for the lEvaluationTime value.
	 */
	double dWeightEvaluationTime;
	
//helpvariable members

	/**
	 * A pointer to the best possible fitness the algorithm can create.
	 * No individual with a better/ higher fitness can be created with this
	 * algorithm.
	 * The best case fitness is an cFibObjectFitness object with all
	 * fitnessvalues set to 0.
	 */
	mutable cFibObjectFitnessBasic * pBestCaseFitness;
	
	/**
	 * A pointer to the worst case fitness for the algorithm and
	 * originalindividual.
	 * An individual with the worst case fitness can easily be created.
	 * This is the fitness of the originalindividual.
	 * If no originalindividual is set NULL is returned.
	 */
	mutable cFibObjectFitnessBasic * pWorstCaseFitness;

public:
	
	/**
	 * constructor
	 */
	cFibObjectFitnessBasicAlgorithm();
	
	/**
	 * constructor
	 *
	 * @see cFibObjectFitnessBasic
	 * @param pInOriginalIndividual the individual with which the fitness
	 * 	should be evalued;
	 * 	Beware: this object won't be copied, so don't delete it as long
	 * 	as this object exists
	 * @param dInWeightDistanceToOriginal the weight for the distance to original value
	 * @param dInWeightSize the weight for the fib -object size value
	 * @param dInWeightEvaluationTime the weight for the evaluation time of
	 * 	the fib -object
	 */
	cFibObjectFitnessBasicAlgorithm( cFibIndividual * pInOriginalIndividual,
		double dInWeightDistanceToOriginal=1.0, double dInWeightSize=1.0,
		double dInWeightEvaluationTime=1.0 );

	/**
	 * constructor
	 *
	 * @see cFibObjectFitnessBasic
	 * @param  pOriginalFibElement the fib -object with which the fitness
	 * 	should be evalued;
	 * 	Beware: this object won't be copied, so don't delete it as long
	 * 	as this object exists
	 * @param dInWeightDistanceToOriginal the weight for the distance to original value
	 * @param dInWeightSize the weight for the fib -object size value
	 * @param dInWeightEvaluationTime the weight for the evaluation time of
	 * 	the fib -object
	 */
	cFibObjectFitnessBasicAlgorithm( cFibElement * pOriginalFibElement,
		double dInWeightDistanceToOriginal=1.0, double dInWeightSize=1.0,
		double dInWeightEvaluationTime=1.0 );

	/**
	 * copyconstructor
	 *
	 * @param objectFitnessAlgorithm the cFibObjectFitnessBasicAlgorithm object to copy
	 */
	cFibObjectFitnessBasicAlgorithm( const cFibObjectFitnessBasicAlgorithm &
		objectFitnessAlgorithm );

	/**
	 * destructor
	 */
	virtual ~cFibObjectFitnessBasicAlgorithm();

	/**
	 * This function evalues the fitness for the given fib -individual.
	 * Beware: You have to delete the returned fitness after usage.
	 *
	 * @see pOriginalIndividual
	 * @param individual the cFibIndividual for which a fitnessobject should
	 * 	be created
	 * @return the fitnessobject for the fitness of the given individual or
	 * 	NULL, if no fitness could be created
	 */
	virtual cFibObjectFitnessBasic * evalueFitness( const cIndividual & individual ) const;

	/**
	 * This function evalues the fitness for the given fib -individual.
	 * Beware: You have to delete the returned fitness after usage.
	 *
	 * @see pOriginalIndividual
	 * @param individual the cFibIndividual for which a fitnessobject should
	 * 	be created
	 * @return the fitnessobject for the fitness of the given individual or
	 * 	NULL, if no fitness could be created
	 */
	virtual cFibObjectFitnessBasic * evalueFitness( const cFibIndividual & individual ) const;
	
	/**
	 * This function evalues the fitness for the given fib -individual.
	 * Beware: You have to delete the returned fitness after usage.
	 *
	 * @see pOriginalIndividual
	 * @param fibObject the fib -object for which a fitnessobject should
	 * 	be created
	 * @return the fitnessobject for the fitness of the given fibObject or
	 * 	NULL, if no fitness could be created
	 */
	virtual cFibObjectFitnessBasic * evalueFitness( const cFibElement * fibObject ) const;

	/**
	 * This method evalues the difference betwean the orginal fib -object
	 * and the given fib -object fibObject on an area.
	 * It is the sum of the distances of all values of propertyvectorelements
	 * betwean the represented and original fib -object of all positions
	 * which are inside the dimension bounderies and are in fibObjectArea,
	 * if given (not NULL).
	 *
	 * @param fibObject the fib -object to which the difference is to evalue
	 * @param fibObjectArea if given (not NULL) the points/positions of
	 * 	this (evalued) fib -object are the positions for which the
	 * 	distance is evalued (other points will be ignored)
	 * @return a value for the difference betwean the orginal fib -object
	 * 	and the given fib -object fibObject, or -1.0 if an error occured
	 */
	virtual double evalueDistance( const cFibElement *fibElement,
		const cFibElement *fibElementArea=NULL  ) const;

	/**
	 * This method evalues the difference betwean the orginal fib -object
	 * and the given points with ther properties.
	 * It is the sum of the distances of all values of propertyvectorelements
	 * betwean the represented and original fib -object of all positions
	 * which are inside the dimension bounderies.
	 *
	 * @param liPointWithProperties the list with the points and ther
	 * 	properties for which to evalue the distance
	 * @return a value for the difference betwean the orginal fib -object
	 * 	and the given liPointWithProperties, or -1.0 if an error occured
	 */
	virtual double evalueDistance( list< pair< cVectorPosition,
		list< cVectorProperty > > > & liPointWithProperties ) const;

	/**
	 * This method evalues the difference betwean the orginal fib -object
	 * and the given fib -object fibObject on an area.
	 * It is the sum of the distances of all values of propertyvectorelements
	 * betwean the represented and original fib -object of all positions
	 * which are inside the dimension bounderies and are in fibObjectArea.
	 *
	 * @param liPointWithProperties the list with the points and ther
	 * 	properties for which to evalue the distance
	 * @param liPointWithPropertiesOfArea the points/positions of
	 * 	the positions for which the distance is evalued (other points
	 * 	will be ignored)
	 * 	(the list< cVectorProperty > is included for consistencie, but
	 * 	it is ignored in this method)
	 * @return a value for the difference betwean the orginal fib -object
	 * 	and the given liPointWithProperties, or -1.0 if an error occured
	 */
	virtual double evalueDistanceInArea( list< pair< cVectorPosition,
			list< cVectorProperty > > > & liPointWithProperties,
		list< pair< cVectorPosition, list< cVectorProperty > > > &
			liPointWithPropertiesOfArea ) const;
	
	/**
	 * @return the name of this class
	 */
	virtual string getClassName() const;
	
	/**
	 * This method sets the originalindividual.
	 * The originalindividual is the individual with which the fitness
	 * should be evalued.
	 *
	 * @see getOriginalIndividual()
	 * @see pOriginalIndividual
	 * @param pInOriginalIndividual a point to the originalindividual to set
	 * 	Beware: this object won't be copied, so don't delete it as long
	 * 	as this object exists
	 * @return true if the originalindividual is set to originalIndividum,
	 * 	else false
	 */
	virtual bool setOriginalIndividual( cIndividual  * pInOriginalIndividual );
	
	/**
	 * This method sets the originalindividual.
	 * The originalindividual is the individual with which the fitness
	 * should be evalued.
	 *
	 * @see getOriginalIndividual()
	 * @see pOriginalIndividual
	 * @param pInOriginalIndividual a point to the fib -originalindividual to set
	 * 	Beware: this object won't be copied, so don't delete it as long
	 * 	as this object exists
	 * @return true if the originalindividual is set to pInOriginalIndividual,
	 * 	else false
	 */
	virtual bool setOriginalIndividual( cFibIndividual  * pInOriginalIndividual );

	/**
	 * This method sets the originalindividual.
	 * The originalindividual is the individual with which the fitness
	 * should be evalued.
	 *
	 * @see getOriginalIndividual()
	 * @see pOriginalIndividual
	 * @param pInOriginalFibObject the fib -object with which the fitness
	 * 	should be evalued;
	 * 	Beware: this object won't be copied, so don't delete it as long
	 * 	as this object exists
	 * @return true if the originalindividual is set to pInOriginalFibObject,
	 * 	else false
	 */
	virtual bool setOriginalFibObject( cFibElement  * pInOriginalFibObject );

	/**
	 * This Method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cFibObjectFitnessBasicAlgorithm * clone() const;

	/**
	 * This Method returns the best possible fitness the algorithm can create.
	 * No individual with a better/ higher fitness can be created with this
	 * algorithm.
	 * The best case fitness is an cFibObjectFitness object with all
	 * fitnessvalues set to 0.
	 *
	 * @return a cFibObjectFitness object with all fitnessvalues set to 0
	 */
	virtual const cFibObjectFitnessBasic * getBestFitness() const;

	/**
	 * This Method returns the worst case fitness for the algorithm and
	 * originalindividual.
	 * An individual with the worst case fitness can easyly be created.
	 * This is the fitness of the originalindividual.
	 * If no originalindividual is set NULL is returned.
	 *
	 * @return a refernce to the fitness of the originalindividual or NULL,
	 * 	ff no originalindividual is set
	 */
	virtual const cFibObjectFitnessBasic * getWorstCaseFitness() const;


	/**
	 * @see dWeightDistanceToOriginal
	 * @return the weight for the dDistanceToOriginal value
	 */
	double getWeightDistanceToOriginal() const;
	
	/**
	 * @see dWeightSize
	 * @return the weight for the lSize value
	 */
	double getWeightSize() const;
	
	/**
	 * @see dWeightEvaluationTime
	 * @return the weight for the lEvaluationTime value
	 */
	double getWeightEvaluationTime() const;

	
	
};//end class cFibObjectFitnessBasicAlgorithm

};//end namespace fib
};//end namespace enviroment

#endif //___C_FIB_OBJECT_FITNESS_BASIC_ALGORITHMUS_H__







