/**
 * @file cObjectFitness
 * file name: cObjectFitness.h
 * @author Betti Oesterholz
 * @date 26.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies the abstract basisclass of enviroment object
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
 * This header specifies the abstract basisclass of enviroment object
 * fitnesses. This represents the fitness of a object which is a
 * individuum in genetic algorithm (enviroment).
 * The better (higher) the fitness the better the object, the more likly
 * it should live and children should be created from it.
 *
 */
/*
History:
26.02.2010  Oesterholz  created
*/

#ifndef ___C_OBJECT_FITNESS_H__
#define ___C_OBJECT_FITNESS_H__

#include "version.h"

#include <string>


using std::string;

namespace enviroment{

//cyclic dependencies
class cObjectFitnessAlgorithm;


class cObjectFitness{

friend class cObjectFitnessAlgorithm;

protected:
	
	/**
	 * a value for the fitness of the object; the higher this value is the
	 * better the fitness of the associated object
	 */
	double dFittness;
	
	/**
	 * the algorithm with which this fitness was created;
	 * if NULL no algorithm had created this object
	 */
	const cObjectFitnessAlgorithm * pObjectFitnessAlgorithm;

	/**
	 * constructor
	 *
	 * @param dInFittness a value for the fitness of the object;
	 * 	the higher this value is the better the fitness
	 * @param pInObjectFitnessAlgorithm the algorithm with which this
	 * 	fitness was created; if NULL no algorithm had created this object;
	 * 	Beware: this object won't be copied, if you delete it
	 * 	getFitnessAlgorithm() will return an invalid pointer
	 */
	cObjectFitness( double dInFittness,
		const cObjectFitnessAlgorithm * pInObjectFitnessAlgorithm=NULL );

public:

	/**
	 * copyconstructor
	 *
	 * @param objectFitness the cObjectFitness object to copy
	 */
	cObjectFitness( const cObjectFitness & objectFitness );
	
	/**
	 * Destructor of the class cObjectFitnessAlgorithm.
	 */
	virtual ~cObjectFitness();

	/**
	 * @return a value for the fitness of the associated object;
	 * 	the higher this value is the better the fitness
	 */
	virtual double getFitness() const;

	/**
	 * @return the name of this class
	 */
	virtual string getClassName() const;

	/**
	 * @return the algorithm with which this fitness was created;
	 * 	if NULL no algorithm had created this object
	 */
	const cObjectFitnessAlgorithm * getFitnessAlgorithm() const;

	/**
	 * This Method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cObjectFitness * clone() const;
	
	/**
	 * Comparisson on equal method for two fitness objects.
	 *
	 * @param fitness the fitnessobject to compare this fitnessobject to
	 * @return true if the fitness this object represents is equal to the
	 * 	fitness the given object fitness represents
	 */
	virtual bool equal( const cObjectFitness &fitness ) const;
	
	/**
	 * Comparisson on equal operator for two fitness objects.
	 *
	 * @param fitness the fitnessobject to compare this fitnessobject to
	 * @return true if the fitness this object represents is equal to the
	 * 	fitness the given object fitness represents
	 */
	virtual bool operator==( const cObjectFitness &fitness ) const;

	/**
	 * Comparisson on lower operator for two fitness objects.
	 *
	 * @param fitness the fitnessobject to compare this fitnessobject to
	 * @return true if the fitness this object represents is lower to the
	 * 	fitness the given object fitness represents; the higher the
	 * 	fitness is, the better is the fitness of the associated object
	 */
	virtual bool operator<( const cObjectFitness &fitness ) const;



};//end class cObjectFitness


};//end namespace enviroment

#endif //___C_OBJECT_FITNESS_H__







