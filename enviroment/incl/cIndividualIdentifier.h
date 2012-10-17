/**
 * @file cIndividualIdentifier
 * file name: cIndividualIdentifier.h
 * @author Betti Oesterholz
 * @date 26.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for identifiers for individals.
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
 * This header specifies a class for identifiers for individals.
 * The identifier is a unique object for all possible individuals.
 * @see cIndividual 
 *
 */
/*
History:
26.02.2010  Oesterholz  created
*/

#ifndef ___C_INDIVIDUAL_IDENTIFIER_H__
#define ___C_INDIVIDUAL_IDENTIFIER_H__

#include "version.h"


namespace enviroment{


class cIndividualIdentifier{

protected:
	
	/**
	 * the identifier of a individual, wich is unique for all individuals
	 * in one enviroment instantiation
	 */
	unsigned long long ulIndividualIdentifier;
	
	/**
	 * the identifier of the enviroment instantiation, so this identifier
	 * is unique, even for different enviroment instantiations
	 */
	unsigned long long ulAlgorithmIdentifier;


	/**
	 * constructor
	 *
	 * @param ulInIndividualIdentifier the identifier of the individual
	 * @param ulInAlgorithmIdentifier the identifier of the enviroment
	 * 	instantiation
	 */
	cIndividualIdentifier( unsigned long long ulInIndividualIdentifier,
		unsigned long long ulInAlgorithmIdentifier );

public:

	/**
	 * constructor
	 *
	 * @param ulInAlgorithmIdentifier the identifier of the enviroment
	 * 	instantiation
	 */
	cIndividualIdentifier( unsigned long long ulInAlgorithmIdentifier );
	
	/**
	 * @return a identifier for no individual; this will be lower ever
	 * 	other identifier
	 */
	static cIndividualIdentifier & getNoIndividualIdentifier();
	
	/**
	 * Comparisson on equal method for two cIndividualIdentifier objects.
	 *
	 * @param idIndividual the idIndividualobject to compare this
	 * 	idIndividualobject to
	 * @return true if the cIndividualIdentifier this object represents is
	 * 	equal to the cIndividualIdentifier the given object idIndividual
	 * 	represents
	 */
	bool equal( const cIndividualIdentifier &idIndividual ) const;
	
	/**
	 * Comparisson on equal operator for two cIndividualIdentifier objects.
	 *
	 * @param idIndividual the idIndividualobject to compare this
	 * 	idIndividualobject to
	 * @return true if the cIndividualIdentifier this object represents is
	 * 	equal to the cIndividualIdentifier the given object idIndividual
	 * 	represents
	 */
	bool operator==( const cIndividualIdentifier &idIndividual ) const;

	/**
	 * Comparisson on not equal operator for two cIndividualIdentifier objects.
	 *
	 * @param idIndividual the idIndividualobject to compare this
	 * 	idIndividualobject to
	 * @return true if the cIndividualIdentifier this object represents is
	 * 	not equal to the cIndividualIdentifier the given object idIndividual
	 * 	represents
	 */
	bool operator!=( const cIndividualIdentifier &idIndividual ) const;

	/**
	 * Comparisson on lower operator for two identifier objects.
	 * An identifier is lower, if it's algorithm identifier
	 * (@see ulAlgorithmIdentifier) is lower or the algorithm identifiers
	 * are equal and the individual identifier (@see ulIndividualIdentifier)
	 * is lower.
	 *
	 * This method is mainly for sorting individuals.
	 *
	 * @see ulAlgorithmIdentifier
	 * @see ulIndividualIdentifier
	 * @param identifier the identifier to compare this identifier to
	 * @return true identifier is lower than the given identifier, else false
	 */
	bool operator<( const cIndividualIdentifier &identifier ) const;


private:

	/**
	 * @return a individual identifier that wasn't used bevor
	 */
	static unsigned long long getNewIndividualIdentifier();



};//end class cIndividualIdentifier



};//end namespace enviroment

#endif //___C_INDIVIDUAL_IDENTIFIER_H__







