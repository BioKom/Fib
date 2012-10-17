/**
 * @file cOpFindEvenLineAll
 * file name: cOpFindEvenLineAll.h
 * @author Betti Oesterholz
 * @date 27.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This operator combines all neibourpoints in one dimension with the same
 * properties.
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
 * This operator combines all neibourpoints in one dimension with the same
 * properties.
 * In an last step it removes from the created fib -object all underobjects
 * which point properties are overwritten and so not necessary.
 *
 *
 * @see cOperationFib
 * @see cOperation
 * @see cEnviroment
 */
/*
History:
27.06.2010  Oesterholz  created
*/


#ifndef ___C_OP_FIND_EVEN_LINE_ALL_H__
#define ___C_OP_FIND_EVEN_LINE_ALL_H__

#include "version.h"

#include "cOperationFib.h"

#include <string>


namespace enviroment{
namespace fib{


class cOpFindEvenLineAll: public cOperationFib{
public:

	/**
	 * The standardconstructor for the operation.
	 * It will create the operation, but won't start it.
	 *
	 * @param operationId the identifer for the operation
	 */
	cOpFindEvenLineAll( const cOperationIdentifier & operationId );

	/**
	 * Destructor of the class cOpFindEvenLineAll.
	 */
	virtual ~cOpFindEvenLineAll();

	/**
	 * This method creats a new instance of this operator.
	 * Beware: You have to delete the instance after usage.
	 *
	 * @param operationId the identifer for the operation
	 * @return a pointer to a new instance of this operation
	 */
	virtual cOpFindEvenLineAll * createInstance( const cOperationIdentifier & operationId ) const;

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


};//end class cOpFindEvenLineAll


};//end namespace fib
};//end namespace enviroment

#endif //___C_OP_FIND_EVEN_LINE_ALL_H__perator







