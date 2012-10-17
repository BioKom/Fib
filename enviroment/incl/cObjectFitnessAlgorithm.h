/**
 * @file cObjectFitnessAlgorithm
 * file name: cObjectFitnessAlgorithm.h
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

#ifndef ___C_OBJECT_FITNESS_ALGORITHMUS_H__
#define ___C_OBJECT_FITNESS_ALGORITHMUS_H__

#include "version.h"

#include "cObjectFitness.h"

#include <string>


using std::string;

namespace enviroment{


class cIndividual;//cyclic dependencie


class cObjectFitnessAlgorithm{

protected:
	
	/**
	 * The individual with which the fitness should be evalued.
	 * The more similar the given individual is to this (originalIndividual)
	 * the higher its fitness will be, if it's other properties (e.g. size)
	 * are the same.
	 */
	cIndividual * pOriginalIndividual;
	
public:

	/**
	 * constructor
	 */
	cObjectFitnessAlgorithm();
	
	/**
	 * constructor
	 *
	 * @param pInOriginalIndividual the individual with which the fitness
	 * 	should be evalued;
	 * 	Beware: this object won't be copied, so don't delete it as long
	 * 	as this object exists
	 */
	cObjectFitnessAlgorithm( cIndividual * pInOriginalIndividual );

	/**
	 * copyconstructor
	 *
	 * @param objectFitnessAlgorithm the cObjectFitnessAlgorithm object to copy
	 */
	cObjectFitnessAlgorithm( const cObjectFitnessAlgorithm &
		objectFitnessAlgorithm );

	/**
	 * Destructor of the class cObjectFitnessAlgorithm.
	 */
	virtual ~cObjectFitnessAlgorithm() = 0;

	/**
	 * This function evalues the fitness for the given individual.
	 * Beware: You have to delete the returned fitness after usage.
	 *
	 * @see pOriginalIndividual
	 * @param individual the cIndividual for which a fitnessobject should
	 * 	be created
	 * @return a pointer to a fitnessobject for the fitness of the given individual or
	 * 	NULL, if no fitness could be created
	 */
	virtual cObjectFitness * evalueFitness( const cIndividual & individual ) const = 0;

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
	 * @see setOriginalIndividual()
	 * @see pOriginalIndividual
	 * @return a pointer to the originalindividual or NULL if non exists
	 * 	The originalindividual is the individual with which the
	 * 	fitness is evalued.
	 */
	cIndividual * getOriginalIndividual();

	/**
	 * @see setOriginalIndividual()
	 * @see pOriginalIndividual
	 * @return a pointer to the originalindividual or NULL if non exists
	 * 	The originalindividual is the individual with which the
	 * 	fitness is evalued.
	 */
	const cIndividual * getOriginalIndividual() const;

	/**
	 * This Method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cObjectFitnessAlgorithm * clone() const = 0;

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
	virtual const cObjectFitness * getBestFitness() const = 0;

	/**
	 * This Method returns the worst case fitness for the algorithm and
	 * originalindividual.
	 * An individual with the worst case fitness can easyly be created.
	 * Normaly this would be the fitness of the originalindividual.
	 * If no worst case fitness can be evalued NULL is returned.
	 *
	 * @return a refernce to the worst case fitness or NULL, if non can be created
	 */
	virtual const cObjectFitness * getWorstCaseFitness() const = 0;

};//end class cObjectFitnessAlgorithm


};//end namespace enviroment

#endif //___C_OBJECT_FITNESS_ALGORITHMUS_H__







