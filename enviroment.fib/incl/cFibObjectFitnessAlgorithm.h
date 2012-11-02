/**
 * @file cFibObjectFitnessAlgorithm
 * file name: cFibObjectFitnessAlgorithm.h
 * @author Betti Oesterholz
 * @date 26.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies the abstract basisclass of fib -enviroment algorithm
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
 * @see cObjectFitnessAlgorithm
 * This header specifies the abstract basisclass of fib -enviroment algorithm
 * for creating fib -fitness objects.
 * The better (higher) the fitness the better the Fib object, the more likly
 * it should live and children should be created from it.
 *
 */
/*
History:
26.02.2010  Oesterholz  created
12.09.2010  Oesterholz  getOriginalPositionList() method implemented
31.10.2012  Oesterholz  cFibObjectFitnessAlgorithm() constructor with
	input reference Fib object created
*/

#ifndef ___C_FIB_OBJECT_FITNESS_ALGORITHMUS_H__
#define ___C_FIB_OBJECT_FITNESS_ALGORITHMUS_H__

#include "version.h"

#include "cObjectFitnessAlgorithm.h"
#include "cFibObjectFitness.h"
#include "cEvaluePositionList.h"


#include "cRoot.h"

#include <string>


using std::string;

namespace enviroment{
namespace fib{


class cFibIndividual;//cyclic dependencie


class cFibObjectFitnessAlgorithm: public cObjectFitnessAlgorithm{
protected:
	
	/**
	 * the root -elements of original object, without ther
	 * main -Fib objects (they are replaced by empty points)
	 */
	cRoot * pOriginalRoots;
	
	/**
	 * if true the original individual is given as an fib object cFibElement
	 * and not an cFibIndividual
	 */
	bool bOriginalIsFibObject;
	
	/**
	 * The evalued position list of the original Fib object or NULL, if
	 * non exists.
	 */
	mutable cEvaluePositionList * pEvaluedPositionsDataOriginal;
	
	/**
	 * If true the positionsdata of the original Fib object
	 * liEvaluedPositionsDataOriginal was evalued, else false.
	 */
	mutable bool bOriginalEvalued;

	/**
	 * The number of dimensions of the original fib object.
	 * This is evalued with the method @see evalueOriginalDimensions().
	 *
	 * @see pdDirectionMinimum
	 * @see pdDirectionMaximum
	 * @see pdDirectionScaling
	 * @see pdDirectionSize
	 * @see bStandardDimensionDomain
	 * @see pVecDomainDimension
	 */
	mutable unsigned int uiNumberOfDimensions;
	
	/**
	 * The minimum value for the dimensions of the original fib object.
	 * This is evalued with the method @see evalueOriginalDimensions().
	 * This is an array of size @see uiNumberOfDimensions .
	 *
	 * @see uiNumberOfDimensions
	 * @see pdDirectionMaximum
	 * @see pdDirectionScaling
	 * @see pdDirectionSize
	 * @see bStandardDimensionDomain
	 * @see pVecDomainDimension
	 */
	mutable doubleFib * pdDirectionMinimum;
	
	/**
	 * The maximum value for the dimensions of the original fib object.
	 * This is evalued with the method @see evalueOriginalDimensions().
	 * This is an array of size @see uiNumberOfDimensions .
	 *
	 * @see uiNumberOfDimensions
	 * @see pdDirectionMinimum
	 * @see pdDirectionScaling
	 * @see pdDirectionSize
	 * @see bStandardDimensionDomain
	 * @see pVecDomainDimension
	 */
	mutable doubleFib * pdDirectionMaximum;
	
	/**
	 * The scalingfactor for the dimensions of the original fib object.
	 * This is evalued with the method @see evalueOriginalDimensions().
	 * This is an array of size @see uiNumberOfDimensions .
	 *
	 * @see uiNumberOfDimensions
	 * @see pdDirectionMinimum
	 * @see pdDirectionMaximum
	 * @see pdDirectionSize
	 * @see bStandardDimensionDomain
	 * @see pVecDomainDimension
	 */
	mutable doubleFib * pdDirectionScaling;
	
	/**
	 * The number of values in the dimensions of the original fib object.
	 * This is evalued with the method @see evalueOriginalDimensions().
	 * This is an array of size @see uiNumberOfDimensions .
	 *
	 * @see uiNumberOfDimensions
	 * @see pdDirectionMinimum
	 * @see pdDirectionMaximum
	 * @see pdDirectionScaling
	 * @see bStandardDimensionDomain
	 * @see pVecDomainDimension
	 */
	mutable doubleFib * pdDirectionSize;
	
	/**
	 * This value is true if the dimension domain ( @see pVecDomainDimension )
	 * is the standarddomain for dimensions .
	 * This is evalued with the method @see evalueOriginalDimensions().
	 *
	 * @see uiNumberOfDimensions
	 * @see pdDirectionMinimum
	 * @see pdDirectionMaximum
	 * @see pdDirectionScaling
	 * @see pdDirectionSize
	 * @see pVecDomainDimension
	 */
	mutable bool bStandardDimensionDomain;
	
	/**
	 * This is a pointer to the dimension domain.
	 * This is evalued with the method @see evalueOriginalDimensions().
	 *
	 * @see uiNumberOfDimensions
	 * @see pdDirectionMinimum
	 * @see pdDirectionMaximum
	 * @see pdDirectionScaling
	 * @see pdDirectionSize
	 * @see bStandardDimensionDomain
	 */
	mutable cDomainVectorBasis * pVecDomainDimension;

	/**
	 * The number of points in the original multimediaobject.
	 */
	mutable unsigned long long ulNumberOfPoints;

public:

	/**
	 * constructor
	 */
	cFibObjectFitnessAlgorithm();
	
	/**
	 * constructor
	 *
	 * @param pInOriginalIndividual the individual with which the fitness
	 * 	should be evalued;
	 * 	Beware: this object won't be copied, so don't delete it as long
	 * 	as this object exists
	 */
	cFibObjectFitnessAlgorithm( cFibIndividual * pInOriginalIndividual );

	/**
	 * constructor
	 *
	 * @param pInOriginalFibObject the Fib object with which the fitness
	 * 	should be evalued;
	 * 	Beware: this object won't be copied, so don't delete it as long
	 * 	as this object exists
	 */
	cFibObjectFitnessAlgorithm( cFibElement * pInOriginalFibObject );

	/**
	 * constructor
	 *
	 * @param inOriginalFibObject the fib object with which the fitness
	 * 	should be evalued;
	 */
	cFibObjectFitnessAlgorithm( const cFibElement & inOriginalFibObject );

	/**
	 * copyconstructor
	 *
	 * @param objectFitnessAlgorithm the cFibObjectFitnessAlgorithm object to copy
	 */
	cFibObjectFitnessAlgorithm( const cFibObjectFitnessAlgorithm &
		objectFitnessAlgorithm );

	/**
	 * destructor
	 */
	virtual ~cFibObjectFitnessAlgorithm();

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
	virtual cFibObjectFitness * evalueFitness( const cFibIndividual & individual ) const = 0;

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
	virtual cFibObjectFitness * evalueFitness( const cFibElement * fibObject ) const = 0;

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
	 * @param pInOriginalIndividual a point to the fib -originalindividual to set
	 * 	Beware: this object won't be copied, so don't delete it as long
	 * 	as this object exists
	 * @return true if the originalindividual is set to pInOriginalIndividual,
	 * 	else false
	 */
	virtual bool setOriginalIndividual( cIndividual * pInOriginalIndividual );
	
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
	virtual bool setOriginalIndividual( cFibIndividual * pInOriginalIndividual );

	/**
	 * This method sets the originalindividual.
	 * The originalindividual is the individual with which the fitness
	 * should be evalued.
	 *
	 * @see getOriginalIndividual()
	 * @see pOriginalIndividual
	 * @param pInOriginalFibObject the Fib object with which the fitness
	 * 	should be evalued;
	 * 	Beware: this object won't be copied, so don't delete it as long
	 * 	as this object exists
	 * @return true if the originalindividual is set to pInOriginalFibObject,
	 * 	else false
	 */
	virtual bool setOriginalFibObject( cFibElement * pInOriginalFibObject );

	/**
	 * @see setOriginalIndividual()
	 * @see getOriginalIndividual()
	 * @return a pointer to the originalindividual or NULL if non exists;
	 * 	The originalindividual is the individual with which the
	 * 	fitness is evalued.
	 */
	cFibIndividual * getOriginalIndividual();

	/**
	 * @see setOriginalFibObject()
	 * @see getOriginalIndividual()
	 * @return a pointer to the originalindividual or NULL if non exists
	 * 	The originalindividual is the individual with which the
	 * 	fitness is evalued.
	 */
	const cFibElement * getOriginalFibObject();
	
	/**
	 * @see setOriginalIndividual()
	 * @see getOriginalIndividual()
	 * @see pOriginalIndividual
	 * @return a pointer to the originalindividual root -elements
	 * 	or NULL if non exists;
	 * 	The originalindividual is the individual with which the
	 * 	fitness is evalued. This methods will yust return ther
	 * 	root -elements, with the main -Fib objects set to NULL.
	 */
	const cRoot * getOriginalIndividualRoot();

	/**
	 * This Method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cFibObjectFitnessAlgorithm * clone() const = 0;
	
	/**
	 * This Method returns the best possible fitness the algorithm can create.
	 * No individual with a better/ higher fitness can be created with this
	 * algorithm.
	 * Normaly this would be an indivudual which represents the original
	 * individual perfectly and don't use recources.
	 * If no best possible fitness can be evalued NULL is returned.
	 *
	 * @return a refernce to the best possible fitness or NULL, if non can be creted
	 */
	virtual const cFibObjectFitness * getBestFitness() const = 0;

	/**
	 * This Method returns the worst case fitness for the algorithm and
	 * originalindividual.
	 * An individual with the worst case fitness can easyly be created.
	 * Normaly this would be the fitness of the originalindividual.
	 * If no worst case fitness can be evalued NULL is returned.
	 *
	 * @return a refernce to the worst case fitness or NULL, if non can be created
	 */
	virtual const cFibObjectFitness * getWorstCaseFitness() const = 0;
	
	/**
	 * @return the evalued positionslist of the original Fib object or
	 * 	NULL, if no exists
	 */
	const cEvaluePositionList * getOriginalPositionList() const;
	
	
protected:

	/**
	 * This function extracts the root -element tree from the Fib object.
	 * The root -elements will have the same structur as in the given
	 * Fib object, but  empty points for ther main -Fib objects.
	 * Beware: delete the returnd fib object after usage.
	 *
	 * @param pFibObject the Fib object wher to extract the root -elements
	 * @return a Fib object with just root -elements of the given
	 * 	Fib object pFibObject
	 */
	cRoot * createRootTree( const cFibElement * pFibObject );

	/**
	 * This method evalues the dimensions variables for the original Fib object.
	 *
	 * evalued class members are:
	 * @see uiNumberOfDimensions;
	 * @see pdDirectionMinimum;
	 * @see pdDirectionMaximum;
	 * @see pdDirectionScaling;
	 * @see pdDirectionSize;
	 * @see bStandardDimensionDomain
	 * @see pVecDomainDimension
	 *
	 * @return true if the evaluation was successfull, else false
	 */
	bool evalueOriginalDimensions() const;
};//end class cFibObjectFitnessAlgorithm

};//end namespace fib
};//end namespace enviroment

#endif //___C_FIB_OBJECT_FITNESS_ALGORITHMUS_H__







