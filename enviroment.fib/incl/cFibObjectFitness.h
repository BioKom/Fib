/**
 * @file cFibObjectFitness
 * file name: cFibObjectFitness.h
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

#ifndef ___C_FIB_OBJECT_FITNESS_H__
#define ___C_FIB_OBJECT_FITNESS_H__

#include "version.h"

#include "cObjectFitness.h"

#include <string>


using std::string;

namespace enviroment{
namespace fib{

//cyclic dependencies
class cFibObjectFitnessAlgorithm;


class cFibObjectFitness: public cObjectFitness{

friend class cFibObjectFitnessAlgorithm;

protected:

	/**
	 * constructor
	 *
	 * @param dInFittness a value for the fitness of the object;
	 * 	the higher this value is the better the fitness
	 * @param pInFibObjectFitnessAlgorithm the algorithm with which this
	 * 	fitness was created; if NULL no algorithm had created this object;
	 * 	Beware: this object won't be copied, if you delete it
	 * 	getFitnessAlgorithm() will return an invalid pointer
	 */
	cFibObjectFitness( double dInFittness,
		const cFibObjectFitnessAlgorithm * pInFibObjectFitnessAlgorithm=NULL );

public:

	/**
	 * copyconstructor
	 *
	 * @param objectFitness the cObjectFitness object to copy
	 */
	cFibObjectFitness( const cFibObjectFitness & objectFitness );

	/**
	 * Destructor of the class cFibObjectFitness.
	 */
	virtual ~cFibObjectFitness();

	/**
	 * @return the name of this class
	 */
	virtual string getClassName() const;

	/**
	 * @return the algorithm with which this fitness was created;
	 * 	if NULL no algorithm had created this object
	 */
	const cFibObjectFitnessAlgorithm * getFitnessAlgorithm() const;

	/**
	 * This Method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cFibObjectFitness * clone() const;
	
	/**
	 * Comparisson on equal operator for two fitness objects.
	 *
	 * @param fitness the fitnessobject to compare this fitnessobject to
	 * @return true if the fitness this object represents is equal to the
	 * 	fitness the given object fitness represents
	 */
	virtual bool operator==( const cFibObjectFitness &fitness ) const;




};//end class cFibObjectFitness

};//end namespace fib
};//end namespace enviroment

#endif //___C_FIB_OBJECT_FITNESS_H__







