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

#include "cIndividualIdentifier.h"


using namespace enviroment;

/**
 * constructor
 *
	 * @param ulInIndividualIdentifier the identifier of the individual
 * @param ulInAlgorithmIdentifier the identifier of the enviroment
 * 	instantiation
 */
cIndividualIdentifier::cIndividualIdentifier(
		unsigned long long ulInIndividualIdentifier,
		unsigned long long ulInAlgorithmIdentifier ):
		ulIndividualIdentifier( ulInIndividualIdentifier ),
		ulAlgorithmIdentifier( ulInAlgorithmIdentifier ){
	//nothing to do
}


/**
 * constructor
 *
 * @param ulInAlgorithmIdentifier the identifier of the enviroment
 * 	instantiation
 */
cIndividualIdentifier::cIndividualIdentifier( unsigned long long
		ulInAlgorithmIdentifier ):
		ulIndividualIdentifier( getNewIndividualIdentifier() ),
		ulAlgorithmIdentifier( ulInAlgorithmIdentifier ){
	//nothing to do
}


/**
 * @return a identifier for no individual; this will be lower ever
 * 	other identifier
 */
cIndividualIdentifier & cIndividualIdentifier::getNoIndividualIdentifier(){
	
	static cIndividualIdentifier noIndividualIdentifier( 0,0 );
	return noIndividualIdentifier;
}


/**
 * Comparisson on equal method for two cIndividualIdentifier objects.
 *
 * @param idIndividual the idIndividualobject to compare this
 * 	idIndividualobject to
 * @return true if the cIndividualIdentifier this object represents is
 * 	equal to the cIndividualIdentifier the given object idIndividual
 * 	represents
 */
bool cIndividualIdentifier::equal( const cIndividualIdentifier &idIndividual ) const{

	return ((*this) == idIndividual);
}
	
/**
 * Comparisson on equal operator for two cIndividualIdentifier objects.
 *
 * @param idIndividual the idIndividualobject to compare this
 * 	idIndividualobject to
 * @return true if the cIndividualIdentifier this object represents is
 * 	equal to the cIndividualIdentifier the given object idIndividual
 * 	represents
 */
bool cIndividualIdentifier::operator==( const cIndividualIdentifier &idIndividual ) const{

	return ((ulAlgorithmIdentifier == idIndividual.ulAlgorithmIdentifier) &&
		(ulIndividualIdentifier == idIndividual.ulIndividualIdentifier));
}


/**
 * Comparisson on not equal operator for two cIndividualIdentifier objects.
 *
 * @param idIndividual the idIndividualobject to compare this
 * 	idIndividualobject to
 * @return true if the cIndividualIdentifier this object represents is
 * 	not equal to the cIndividualIdentifier the given object idIndividual
 * 	represents
 */
bool cIndividualIdentifier::operator!=( const cIndividualIdentifier &idIndividual ) const{

	return ! ((*this) == idIndividual);
}


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
bool cIndividualIdentifier::operator<( const cIndividualIdentifier &identifier ) const{
	
	if ( ulAlgorithmIdentifier == identifier.ulAlgorithmIdentifier ){
		return (ulIndividualIdentifier < identifier.ulIndividualIdentifier);
	}
	return (ulAlgorithmIdentifier < identifier.ulAlgorithmIdentifier);
}



/**
 * @return a individual identifier that wasn't used bevor
 */
unsigned long long cIndividualIdentifier::getNewIndividualIdentifier(){
	
	/**
	 * the last used identifier for a individual;
	 * This number is incremented for every new identifier
	 */
	static unsigned long long ulLastUsedIndividualIdentifier = 0;
	ulLastUsedIndividualIdentifier++;
	
	return ulLastUsedIndividualIdentifier;
}

