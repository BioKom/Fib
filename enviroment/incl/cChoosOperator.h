/**
 * @file cChoosOperator
 * file name: cChoosOperator.h
 * @author Betti Oesterholz
 * @date 25.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for selecting a good operator.
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
 * This header specifies a class for selecting a good operator.
 * The selection method is weelselction.
 * Every operator has a propability p_i of selection which, is proportional
 * to it's fitnessvalue plus the ratio of the fitnesssum of all operations
 * divieded by the number of operations and 1000 .
 *
 * minFitness = the minimum fitness (@see cOperatorFitnessAlgorithm::getMinFitness())
 * minFitness2 = minFitness - fitnesssum / (#operations * 1000))
 * fitnesssum2 = fitnesssum - minFitness2 * #operations
 * p_i = (fitness_i - minFitness2) / fitnesssum2
 *
 * @see cOperation
 * @see cOperatorFitnessAlgorithm
 * @see cEnviroment
 */
/*
History:
25.03.2010  Oesterholz  created
06.06.2010  Oesterholz  method getClassName() added
*/


#ifndef ___C_CHOOS_OPERATOR_H__
#define ___C_CHOOS_OPERATOR_H__

#include "version.h"

#include "cOperation.h"
#include "cOperatorFitnessAlgorithm.h"

#include <string>


namespace enviroment{


class cChoosOperator{
public:

	/**
	 * standardconstructor
	 */
	cChoosOperator();

	/**
	 * Destructor of the class cChoosOperator.
	 */
	virtual ~cChoosOperator();

	/**
	 * This method selects an operator. The selection method is weelselction.
	 * Every operator has a propability p_i of selection which, is proportional
	 * to it's fitnessvalue plus the ratio of the fitnesssum of all operations
	 * divieded by the number of operations and 1000 .
	 *
	 * minFitness = the minimum fitness (@see cOperatorFitnessAlgorithm::getMinFitness())
	 * minFitness2 = minFitness - fitnesssum / (#operations * 1000))
	 * fitnesssum2 = fitnesssum - minFitness2 * #operations
	 * p_i = (fitness_i - minFitness2) / fitnesssum2
	 *
	 * @return a pointer to the choosen operator, or NULL if non can be selected
	 * 	Beware: You have to delete the returned object after usage.
	 */
	virtual cOperation * choosOperator() const;

	/**
	 * This method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cChoosOperator * clone() const;

	/**
	 * @return the name of this class
	 */
	virtual std::string getClassName() const;


};//end class cChoosOperator


};//end namespace enviroment

#endif //___C_CHOOS_OPERATOR_H__







