/**
 * @file cIndividual
 * file name: cIndividual.h
 * @author Betti Oesterholz
 * @date 28.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for a individal.
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
 * This header specifies a class for a individals.
 * An individal is an central object on which the genetic algorithm
 * (enviroment) works.
 *
 * @see cEnviroment
 *
 */
/*
History:
28.02.2010  Oesterholz  created
*/

#ifndef ___C_INDIVIDUAL_H__
#define ___C_INDIVIDUAL_H__

#include "version.h"

#include "cIndividualInfo.h"


namespace enviroment{


class cIndividual{

friend class cEnviroment;

protected:
	
	/**
	 * The object which is represented by the individual.
	 */
	void * pObject;
	
	/**
	 * the information for the individual
	 */
	cIndividualInfo individalInfo;

	/**
	 * the information for the individual
	 */
	bool bDeleteObjectOnDestruction;
	
public:

	/**
	 * constructor
	 *
	 * @param pInObject the object which is represented by the individual;
	 * 	this object won't be copied but destructed when the individual is
	 * 	destructed if bInDeleteObjectOnDestruction is true
	 * @param inIndividalInfo the information for the individual
	 * @param bInDeleteObjectOnDestruction if true delete the object
	 * 	(pInObject) when the individual is deleted
	 */
	cIndividual( void * pInObject, const cIndividualInfo & inIndividalInfo,
		bool bInDeleteObjectOnDestruction=true );

	/**
	 * copyconstructor
	 * Beware: it down't copy the contained object
	 *
	 * @param individual the individual to copy
	 */
	cIndividual( const cIndividual & individual );

	/**
	 * destructor
	 * It deletes the objekt to the individual.
	 */
	virtual ~cIndividual();
	
	/**
	 * @return a pointer to the object which is represented by the individual
	 */
	virtual void * getObject();
	
	/**
	 * @return a pointer to the object which is represented by the individual
	 */
	virtual const void * getObject() const;
	
	/**
	 * @return a pointer to the information for the individual
	 */
	cIndividualInfo * getInfo();

	/**
	 * @return a pointer to the information for the individual
	 */
	const cIndividualInfo * getInfo() const;
	
	/**
	 * This method updates the fitness of the individual.
	 *
	 * @see getFitness()
	 * @param pInFitnessAlgorithm the fitnessalgorithm with which to update
	 * 	the fitness, if NULL it will be tryed to use an existing fitnessalgorithm
	 * @param pBestObjectFitness if given, the fitness of the best individual
	 * 	at creation time (else NULL)
	 * 	@see cIndividualInfo::pFitnessOfBestAtCreationTime
	 * @return true if the fitness was changed, else false
	 */
	bool updateFitness( const cObjectFitnessAlgorithm * pInFitnessAlgorithm = NULL,
		const cObjectFitness * pBestObjectFitness = NULL );

	/**
	 * Comparisson on equal method for two cIndividual objects.
	 *
	 * @param individual the cIndividual to compare this
	 * 	idIndividualobject to
	 * @param checkIdentifiers if true (standradvalue) the identifiers will
	 * 	be checked also, else not
	 * @return true if the cIndividual this object represents is
	 * 	equal to the cIndividual the given object individual
	 * 	represents
	 */
	virtual bool equal( const cIndividual &individual, bool checkIdentifiers=true ) const;
	
	/**
	 * Comparisson on equal operator for two cIndividual objects.
	 *
	 * @param individual the cIndividual to compare this
	 * 	idIndividualobject to
	 * @return true if the cIndividual this object represents is
	 * 	equal to the cIndividual the given object individual
	 * 	represents
	 */
	bool operator==( const cIndividual &individual ) const;

	/**
	 * Comparisson on not equal operator for two cIndividual objects.
	 *
	 * @param individual the cIndividual to compare this
	 * 	idIndividualobject to
	 * @param checkIdentifiers if true (standradvalue) the identifiers will
	 * 	be checked allso, else not
	 * @return true if the cIndividual this object represents is
	 * 	not equal to the cIndividual the given object individual
	 * 	represents
	 */
	bool operator!=( const cIndividual &individual ) const;

	/**
	 * @return the name of this class
	 */
	virtual string getClassName() const;

	/**
	 * This method clones this individual inclusive the containing object.
	 *
	 * @return a clone of this object
	 */
	virtual cIndividual * clone() const;

	/**
	 * This method clones this individual inclusive the containing object.
	 * Beware: You have to overwrite this method in every direct child class.
	 *
	 * @return a clone of this object
	 * @param bCloneObject if true the object will be cloned and
	 * 	@see bInDeleteObjectOnDestruction will be set to true, if false
	 * 	the object won't be cloned and @see bInDeleteObjectOnDestruction
	 * 	will be set to false
	 */
	virtual cIndividual * clone( bool bCloneObject ) const;


#ifndef TEST
protected:
#endif
	/**
	 * This method kills the individual, so it isn't living anymor.
	 *
	 * @see cIndividualInfo::isLiving()
	 * @see cIndividualInfo::bIsLiving
	 * @return true if the individal was killed, else false
	 */
	virtual bool kill();

};//end class cIndividual


};//end namespace enviroment

#endif //___C_INDIVIDUAL_H__







