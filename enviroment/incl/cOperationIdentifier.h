/**
 * @file cOperationIdentifier
 * file name: cOperationIdentifier.h
 * @author Betti Oesterholz
 * @date 26.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for identifiers for operations.
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
 * This header specifies a class for identifiers for operations.
 * The identifier is a unique object for all possible operations.
 * @see cOperation
 *
 */
/*
History:
26.02.2010  Oesterholz  created
*/

#ifndef ___C_OPERATION_IDENTIFIER_H__
#define ___C_OPERATION_IDENTIFIER_H__

#include "version.h"


namespace enviroment{


class cOperationIdentifier{

protected:
	
	/**
	 * the identifier of a operation, wich is unique for all operations
	 * in one enviroment instantiation
	 */
	unsigned long long ulOperationIdentifier;
	
	/**
	 * the identifier of the enviroment instantiation, so this identifier
	 * is unique, even for different enviroment instantiations
	 */
	unsigned long long ulAlgorithmIdentifier;

public:

	/**
	 * constructor
	 *
	 * @param ulInAlgorithmIdentifier the identifier of the enviroment
	 * 	instantiation
	 */
	cOperationIdentifier( unsigned long long ulInAlgorithmIdentifier );


	/**
	 * Comparisson on equal method for two cOperationIdentifier objects.
	 *
	 * @param idOperation the idOperationobject to compare this
	 * 	idOperationobject to
	 * @return true if the cOperationIdentifier this object represents is
	 * 	equal to the cOperationIdentifier the given object idOperation
	 * 	represents
	 */
	bool equal( const cOperationIdentifier &idOperation ) const;
	
	/**
	 * Comparisson on equal operator for two cOperationIdentifier objects.
	 *
	 * @param idOperation the idOperationobject to compare this
	 * 	idOperationobject to
	 * @return true if the cOperationIdentifier this object represents is
	 * 	equal to the cOperationIdentifier the given object idOperation
	 * 	represents
	 */
	bool operator==( const cOperationIdentifier &idOperation ) const;

	/**
	 * Comparisson on not equal operator for two cOperationIdentifier objects.
	 *
	 * @param idOperation the idOperationobject to compare this
	 * 	idOperationobject to
	 * @return true if the cOperationIdentifier this object represents is
	 * 	not equal to the cOperationIdentifier the given object idOperation
	 * 	represents
	 */
	bool operator!=( const cOperationIdentifier &idOperation ) const;

private:

	/**
	 * @return a operation identifier that wasn't used bevor
	 */
	static unsigned long long getNewOperationIdentifier();



};//end class cOperationIdentifier



};//end namespace enviroment

#endif //___C_OPERATION_IDENTIFIER_H__







