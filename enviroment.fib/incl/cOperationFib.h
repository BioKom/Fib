/**
 * @file cOperationFib
 * file name: cOperationFib.h
 * @author Betti Oesterholz
 * @date 19.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies the abstract basisclass for fib -operations.
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
 * This header specifies the abstract basisclass for fib -operations.
 * Overwrite the start() or run() method to implement the operation.
 *
 * Beware: If the variable bStop is true, stop the operation.
 *
 * @see cEnviroment
 */
/*
History:
19.03.2010  Oesterholz  created
*/


#ifndef ___C_OPERATION_FIB_H__
#define ___C_OPERATION_FIB_H__

#include "version.h"

#include "cOperation.h"

#include "cFibElement.h"

#include "cIndividualIdentifier.h"

namespace enviroment{
namespace fib{


class cOperationFib: public cOperation{
protected:
	
	/**
	 * The standardconstructor for the operation.
	 * It will create the operation, but won't start it.
	 *
	 * @param operationId the identifer for the operation
	 */
	cOperationFib( const cOperationIdentifier & operationId );

	/**
	 * Destructor of the class cObjectFitnessAlgorithm.
	 */
	virtual ~cOperationFib() = 0;

	/**
	 * This method creats a new instance of this operator.
	 * Beware: You have to delete the instance after usage.
	 *
	 * @param operationId the identifer for the operation
	 * @return a pointer to a new instance of this operation
	 */
	virtual cOperationFib * createInstance( const cOperationIdentifier & operationId ) const = 0;


protected:

	/**
	* This method insert the given fib object as a new individual into the
	* enviroment.
	*
	* @param fibObject the fib -object to insert
	* @param liParents a list with the identifiers of the parrent individuals
	* 	of the individual to insert
	* @return true if the individual was inserted, else false
	*/
	bool insertFibObjectIntoEnviroment( cFibElement * fibObject,
			const list<cIndividualIdentifier> liParents );

};//end class cOperationFib

};//end namespace fib
};//end namespace enviroment

#endif //___C_OPERATION_FIB_H__







