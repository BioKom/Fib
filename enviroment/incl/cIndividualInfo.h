/**
 * @file cIndividualInfo
 * file name: cIndividualInfo.h
 * @author Betti Oesterholz
 * @date 28.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for information about individals.
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
 * This header specifies a class for information about individals.
 * @see cIndividual
 *
 */
/*
History:
28.02.2010  Oesterholz  created
*/

#ifndef ___C_INDIVIDUAL_INFO_H__
#define ___C_INDIVIDUAL_INFO_H__


#include "version.h"

#include "cIndividualIdentifier.h"
#include "cOperationIdentifier.h"
#include "cObjectFitness.h"

#include <string>
#include <list>
#include <ctime>

using namespace std;

namespace enviroment{


class cIndividualInfo{

friend class cEnviroment;
friend class cIndividual;

protected:
	
	/**
	 * the identifier of a individual, wich is unique for all individuals
	 */
	cIndividualIdentifier idIndividual;
	
	/**
	 * if true the individual is living;
	 * then a object should exists for it;
	 * if false the individual info exists for giving information about an
	 * object that dosn't exists anymore
	 */
	bool bIsLiving;
	
	/**
	 * the list with the identifiers of the parent individuals of the
	 * individual for which this info is
	 */
	list<cIndividualIdentifier> liIdsParents;
	
	/**
	 * the pFitness of the individual
	 */
	cObjectFitness * pFitness;
	
	/**
	 * the name of the operation which created the individual
	 */
	string szCreatingOperationName;
	
	/**
	 * some more information about the operation which created the
	 * individual; like: parameters or used algorithms
	 */
	string szCreatingOperationInfo;
	
	/**
	 * the identifier of the operation which created the individual
	 */
	cOperationIdentifier idCreatingOperation;
	
	/**
	 * the time_t when the individual was created;
	 * this is the time_t, when the individual was inserted in the enviroment
	 */
	time_t creationTime;
	
	/**
	 * the cost for the creation of the individual;
	 * this should be a value which is sytem independent
	 */
	double dCreationOperationCost;

	/**
	 * the pFitness of the best individual, at the time_t the individual was
	 * created
	 */
	cObjectFitness * pFitnessOfBestAtCreationTime;
	
public:

	/**
	 * constructor
	 *
	 * @param ulAlgorithmIdentifier the identifier of the enviroment
	 * 	instantiation
	 * @param liIdentifierOfParents the list with the identifiers of the
	 * 	parent individuals of the individual for which this info is
	 * @param pFitness the pFitness of the individual
	 * @param szOperationName the name of the operation which created the
	 * 	individual
	 * @param szOperationInfo some more information about the operation
	 * 	which created the individual
	 * @param operationIdentifier the identifier of the operation which
	 * 	created the individual
	 * @param creationTime the time_t when the individual was created
	 * @param dOperationCost the cost for the creation of the individual
	 * @param inFitnessOfBestAtCreationTime the pFitness of the best
	 * 	individual, at the time_t the individual was created
	 */
	cIndividualInfo( unsigned long ulAlgorithmIdentifier,
		const list<cIndividualIdentifier> & liIdentifierOfParents,
		const cObjectFitness & inFitness,
		const string & szOperationName, const string & szOperationInfo,
		const cOperationIdentifier & operationIdentifier,
		time_t inCreationTime, double dOperationCost,
		const cObjectFitness * inFitnessOfBestAtCreationTime );

	/**
	 * copyconstructor
	 *
	 * @param individualInfo the cIndividualInfo to copy
	 */
	cIndividualInfo( const cIndividualInfo & individualInfo );

	/**
	 * destructor
	 */
	virtual ~cIndividualInfo();
	
	/**
	 * @see idIndividual
	 * @return the identifier of a individual
	 */
	cIndividualIdentifier getIdentifier() const;
	
	/**
	 * @see kill()
	 * @see bIsLiving
	 * @return true if the object is living, else false
	 */
	bool isLiving() const;
	
	/**
	 * @see liIdsParents
	 * @return the list with the identifiers of the parent individuals of
	 * 	the individual for which this info is
	 */
	list<cIndividualIdentifier> getIdentifiersOfParents() const;
	
	/**
	 * @see pFitness
	 * @return a pointer to the pFitness of the individual
	 */
	const cObjectFitness * getFitness() const;
	
	/**
	 * @see szCreatingOperationName
	 * @return the name of the operation which created the individual
	 */
	string getOperatorName() const;
	
	/**
	 * @see szCreatingOperationInfo
	 * @return some more information about the operation which created
	 * 	the individual
	 */
	string getOperatorInfo() const;
	
	/**
	 * @see idCreatingOperation
	 * @return the identifier of the operation which created the individual
	 */
	cOperationIdentifier getOperatorIdentifier() const;
	
	/**
	 * @see creationTime
	 * @return the time_t when the individual was created
	 */
	time_t getCreationTime() const;
	
	/**
	 * @see dCreationOperationCost
	 * @return the cost for the creation of the individual
	 */
	double getOperationCost() const;
	
	/**
	 * @see pFitnessOfBestAtCreationTime
	 * @return a pointer to the pFitness of the best individual, at the time_t
	 * 	the individual was created
	 */
	const cObjectFitness * getFitnessOfBestAtCreationTime() const;

	/**
	 * Comparisson on equal method for two cIndividualInfo objects.
	 *
	 * @param idIndividual the idIndividualobject to compare this
	 * 	idIndividualobject to
	 * @param checkIdentifiers if true (standradvalue) the identifiers will
	 * 	be checked also, else not
	 * @return true if the cIndividualInfo this object represents is
	 * 	equal to the cIndividualInfo the given object idIndividual
	 * 	represents
	 */
	virtual bool equal( const cIndividualInfo &idIndividual,
		bool checkIdentifiers=true ) const;
	
	/**
	 * Comparisson on equal operator for two cIndividualInfo objects.
	 *
	 * @param idIndividual the idIndividualobject to compare this
	 * 	idIndividualobject to
	 * @return true if the cIndividualInfo this object represents is
	 * 	equal to the cIndividualInfo the given object idIndividual
	 * 	represents
	 */
	bool operator==( const cIndividualInfo &idIndividual ) const;

	/**
	 * Comparisson on not equal operator for two cIndividualInfo objects.
	 *
	 * @param idIndividual the idIndividualobject to compare this
	 * 	idIndividualobject to
	 * @return true if the cIndividualInfo this object represents is
	 * 	not equal to the cIndividualInfo the given object idIndividual
	 * 	represents
	 */
	bool operator!=( const cIndividualInfo &idIndividual ) const;

	/**
	 * This method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cIndividualInfo * clone() const;


#ifndef TEST
protected:
#endif
	/**
	 * This method kills the individual, so it isn't living anymor.
	 * (The method dosn't change or deletes the object of the individual,
	 * but sets it's status to not living.)
	 *
	 * @see isLiving()
	 * @see bIsLiving
	 * @return true if the individal was killed, else false
	 */
	bool kill();
	

};//end class cIndividualInfo


};//end namespace enviroment

#endif //___C_INDIVIDUAL_INFO_H__







