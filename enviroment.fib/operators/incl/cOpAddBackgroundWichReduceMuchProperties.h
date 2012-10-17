/**
 * @file cOpAddBackgroundWichReduceMuchProperties
 * file name: cOpAddBackgroundWichReduceMuchProperties.h
 * @author Betti Oesterholz
 * @date 17.12.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This Operator adds a background which reduce much properties.
 *
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
 * This Operator searches for properties values in an random choosen
 * fib object, wich are used by a lot property elements.
 * It will chose the properties wich are most often used as the new
 * background for the fib element and remove the with the new background
 * not needed properties.
 *
 * @see cOperationFib
 * @see cOperation
 * @see cEnviroment
 * @see nEvalueFibObject::nNeededUnderobjects
 * @see nEvalueFibObject::nNeededUnderobjects::cEvalueUnderObjects
 */
/*
History:
17.12.2010  Oesterholz  created
*/


#ifndef ___C_OP_ADD_BACKGROUND_WHICH_REDUCE_MUCH_PROPERTIES_H__
#define ___C_OP_ADD_BACKGROUND_WHICH_REDUCE_MUCH_PROPERTIES_H__

#include "version.h"

#include "cOperationFib.h"

#include <string>


namespace enviroment{
namespace fib{


class cOpAddBackgroundWichReduceMuchProperties: public cOperationFib{
public:

	/**
	 * The standardconstructor for the operation.
	 * It will create the operation, but won't start it.
	 *
	 * @param operationId the identifer for the operation
	 */
	cOpAddBackgroundWichReduceMuchProperties( const cOperationIdentifier & operationId );

	/**
	 * Destructor of the class cOpAddBackgroundWichReduceMuchProperties.
	 */
	virtual ~cOpAddBackgroundWichReduceMuchProperties();

	/**
	 * This method creats a new instance of this operator.
	 * Beware: You have to delete the instance after usage.
	 *
	 * @param operationId the identifer for the operation
	 * @return a pointer to a new instance of this operation
	 */
	virtual cOpAddBackgroundWichReduceMuchProperties * createInstance( const cOperationIdentifier & operationId ) const;

	/**
	 * This method runs the operation.
	 * It will wait till the operation is ended befor returning.
	 * Beware: If overwriten call setIsRunning( false ), when the operation
	 * is done.
	 *
	 * @see start()
	 * @see stop()
	 * @see setIsRunning()
	 * @return true if the operation was started
	 */
	virtual bool run();
	
	/**
	 * @return the (class-)name of the operation
	 */
	virtual std::string getName() const;

};//end class cOpAddBackgroundWichReduceMuchProperties


};//end namespace fib
};//end namespace enviroment

#endif //___C_OP_ADD_BACKGROUND_WHICH_REDUCE_MUCH_PROPERTIES_H__







