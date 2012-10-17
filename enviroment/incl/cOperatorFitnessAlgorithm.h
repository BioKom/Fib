/**
 * @file cOperatorFitnessAlgorithm
 * file name: cOperatorFitnessAlgorithm.h
 * @author Betti Oesterholz
 * @date 22.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a abstract class for gernerating the fitness for
 * operators.
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
 * This header specifies a abstract class for gernerating the fitness for
 * operators.
 * The fitness of operators is evalued by considering the information about
 * the individuals the operation has created.
 *
 * @see cOperator
 * @see cEnviroment
 * @see cChoosOperator
 */
/*
History:
22.03.2010  Oesterholz  created
*/


#ifndef ___C_OPERATION_FITNESS_ALGORITHM_H__
#define ___C_OPERATION_FITNESS_ALGORITHM_H__

#include "version.h"

#include "cOperation.h"
#include "cIndividualInfo.h"

#include <string>
#include <list>

using namespace std;

namespace enviroment{


class cOperatorFitnessAlgorithm{
public:

	/**
	 * Destructor of the class cOperatorFitnessAlgorithm.
	 */
	virtual ~cOperatorFitnessAlgorithm() = 0;

	/**
	 * This method evalues the fitness of the given operator operation new.
	 *
	 * @param operation the operator for which the fitness is to be evalued new
	 * @param liCreatedIndividualInfos a list with all informations about
	 * 	all individuals the operator has created
	 * @return the new evalued fitness of the operation
	 */
	virtual double evalueFitness( const cOperation & operation,
		const list<cIndividualInfo> &liCreatedIndividualInfos ) = 0;


	/**
	 * This method updates the fitness of the given operator operation.
	 * For this update the information this cOperatorFitnessAlgorithm
	 * object knows about the operation and the given
	 * createdIndividualInfo is considered to evalue the new fitness.
	 *
	 * @param operation the operator, for which the fitness is to be updated
	 * @param createdIndividualInfo the information about an individual
	 * 	the operator has created and which is not jet known by this
	 * 	cOperatorFitnessAlgorithm object
	 * @return the new evalued fitness of the operation
	 */
	virtual double updateFitness( const cOperation & operation,
		const cIndividualInfo &createdIndividualInfo ) = 0;

	/**
	 * This method updates the fitness of the given operator operation.
	 * For this update the information this cOperatorFitnessAlgorithm
	 * object knows about the operation and the given information in
	 * liCreatedIndividualInfos is considered to evalue the new fitness.
	 *
	 * @param operation the operator, for which the fitness is to be updated
	 * @param liCreatedIndividualInfos a list with the information about
	 * 	the individuals the operator has created and which are not jet
	 * 	known by this cOperatorFitnessAlgorithm object
	 * @return the new evalued fitness of the operation
	 */
	virtual double updateFitness( const cOperation & operation,
		const list<cIndividualInfo> &liCreatedIndividualInfos ) = 0;

	/**
	 * This method returns the fitness of the given operator operation.
	 * This also can include a new evaluation of the fitnessvalue with the
	 * information this cOperatorFitnessAlgorithm object knows about the operator.
	 *
	 * @param operation the operator for which the fitness is to be returned
	 * @return the fitness of the operation
	 */
	virtual double getFitness( const cOperation & operation ) = 0;

	/**
	 * This method returns the fitness of all operators.
	 * This also can include a new evaluation of the fitnessvalue with the
	 * information this cOperatorFitnessAlgorithm object knows about the
	 * operators.
	 *
	 * @return a list with all possible operators with ther fitness
	 */
	virtual list< pair< const cOperation*, double > > getFitness() = 0;

	/**
	 * @return the class name of this object
	 */
	virtual string getClassName() const;

	/**
	 * @return a list with all possible operators
	 */
	virtual list<const cOperation*> getPossibleOperators() const;
	
	/**
	 * @return the minimal fitness which this object can evalue
	 */
	virtual double getMinFitness() const = 0;

	/**
	 * @return the sum of all fitnessvalues of all operators
	 */
	virtual double getFitnessSum() const = 0;
	
	
	/**
	 * This method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cOperatorFitnessAlgorithm * clone() const = 0;



};//end class cOperatorFitnessAlgorithm


};//end namespace enviroment

#endif //___C_OPERATION_FITNESS_ALGORITHM_H__







