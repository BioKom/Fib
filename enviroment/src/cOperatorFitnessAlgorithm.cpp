/**
 * @file cOperatorFitnessAlgorithm
 * file name: cOperatorFitnessAlgorithm.cpp
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
 * @see cEnviroment
 */
/*
History:
22.03.2010  Oesterholz  created
*/


#include "version.h"

#include "cOperatorFitnessAlgorithm.h"


using namespace std;

using namespace enviroment;

//defined in the automatic generated operations.h
extern unsigned long ulNumberOfOperations;
extern const cOperation * arrayOperations[];


/**
 * Destructor of the class cOperatorFitnessAlgorithm.
 */
cOperatorFitnessAlgorithm::~cOperatorFitnessAlgorithm(){
	//nothing to do
}


/**
 * @return the class name of this object
 */
string cOperatorFitnessAlgorithm::getClassName() const{
	return "cOperatorFitnessAlgorithm";
}

/**
 * @return a list with all possible operators
 */
list<const cOperation*> cOperatorFitnessAlgorithm::getPossibleOperators() const{
	
	static list<const cOperation*> liOperations;
	static bool bListOperationsInitialisized = false;
	
	if ( ! bListOperationsInitialisized ){
		for ( unsigned int uiActualoperation = 0;
				uiActualoperation < ulNumberOfOperations; uiActualoperation++ ){
			
			liOperations.push_back( arrayOperations[ uiActualoperation ] );
		}
		bListOperationsInitialisized = true;
	}
	return liOperations;
}








