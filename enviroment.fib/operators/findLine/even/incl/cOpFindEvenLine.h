/**
 * @file cOpFindEvenLine
 * file name: cOpFindEvenLine.h
 * @author Betti Oesterholz
 * @date 16.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This operator chooses a random point and combines it with all
 * neibourpoints in an random choosen direction with the same properties.
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
 * This operator chooses a random point and combines it with all
 * neibourpoints in an random choosen direction with the same properties,
 * with the help of an areaelement and if needed an functionelement.
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
15.06.2010  Oesterholz  created
*/


#ifndef ___C_OP_FIND_EVEN_LINE_H__
#define ___C_OP_FIND_EVEN_LINE_H__

#include "version.h"

#include "cOperationFib.h"

#include <string>


namespace enviroment{
namespace fib{


class cOpFindEvenLine: public cOperationFib{
public:

	/**
	 * The standardconstructor for the operation.
	 * It will create the operation, but won't start it.
	 *
	 * @param operationId the identifer for the operation
	 */
	cOpFindEvenLine( const cOperationIdentifier & operationId );

	/**
	 * Destructor of the class cOpFindEvenLine.
	 */
	virtual ~cOpFindEvenLine();

	/**
	 * This method creats a new instance of this operator.
	 * Beware: You have to delete the instance after usage.
	 *
	 * @param operationId the identifer for the operation
	 * @return a pointer to a new instance of this operation
	 */
	virtual cOpFindEvenLine * createInstance( const cOperationIdentifier & operationId ) const;

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


};//end class cOpFindEvenLine


};//end namespace fib
};//end namespace enviroment

#endif //___C_OP_FIND_EVEN_LINE_H__perator







