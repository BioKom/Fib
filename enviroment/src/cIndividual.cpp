/**
 * @file cIndividual
 * file name: cIndividual.cpp
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
 */
/*
History:
28.02.2010  Oesterholz  created
*/


#include "cIndividual.h"

#include "cObjectFitnessAlgorithm.h"

using namespace enviroment;


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
cIndividual::cIndividual( void * pInObject, const cIndividualInfo &
		inIndividalInfo, bool bInDeleteObjectOnDestruction ):
		pObject( pInObject ), individalInfo( inIndividalInfo ),
		bDeleteObjectOnDestruction( bInDeleteObjectOnDestruction ){
	//nothing to do
}


/**
 * copyconstructor
 * Beware: it down't copy the contained object
 *
 * @param individual the individual to copy
 */
cIndividual::cIndividual( const cIndividual & individual ):
		pObject( individual.pObject ), individalInfo( individual.individalInfo ),
		bDeleteObjectOnDestruction( false ){
	//nothing to do
}


/**
 * destructor
 * It deletes the objekt to the individual.
 */
cIndividual::~cIndividual(){
	//nothing to do
}


/**
 * @return a pointer to the object which is represented by the individual
 */
void * cIndividual::getObject(){
	return pObject;
}


/**
 * @return a pointer to the object which is represented by the individual
 */
const void * cIndividual::getObject() const{
	return pObject;
}


/**
 * @return a pointer to the information for the individual
 */
cIndividualInfo * cIndividual::getInfo(){
	return & individalInfo;
}


/**
 * @return a pointer to the information for the individual
 */
const cIndividualInfo * cIndividual::getInfo() const{
	return & individalInfo;
}


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
bool cIndividual::updateFitness( const cObjectFitnessAlgorithm * pInFitnessAlgorithm,
		const cObjectFitness * pBestObjectFitness ){
	
	const cObjectFitnessAlgorithm * pFitnessAlgorithm = pInFitnessAlgorithm;
	if ( pInFitnessAlgorithm == NULL ){
		/*no fitnessalgorithm given to update the fitness with
		-> try to use the fitnessallgorithm from the existing fitness*/
		if ( (individalInfo.pFitness == NULL) ||
				(individalInfo.pFitness->getFitnessAlgorithm() == NULL) ){
			//can't update the fitness
			return false;
		}
		pFitnessAlgorithm = individalInfo.pFitness->getFitnessAlgorithm();
	}
	bool bReturnValue = false;
	if ( pBestObjectFitness ){
		if ( individalInfo.pFitnessOfBestAtCreationTime == NULL ){
			//update the best individual fitness
			individalInfo.pFitnessOfBestAtCreationTime = pBestObjectFitness->clone();
			bReturnValue = true;
		}else if ( ! ( (*pBestObjectFitness) == (*(individalInfo.pFitnessOfBestAtCreationTime)) ) ){
			//update the best individual fitness
			delete individalInfo.pFitnessOfBestAtCreationTime;
			individalInfo.pFitnessOfBestAtCreationTime = pBestObjectFitness->clone();
			bReturnValue = true;
		}
	}
	//update the fitness
	cObjectFitness * pFitnessNew = pFitnessAlgorithm->evalueFitness( *this );
	
	if ( ! ( (*pFitnessNew) == (*(individalInfo.pFitness)) ) ){
		if ( individalInfo.pFitness != NULL ){
			delete individalInfo.pFitness;
		}
		individalInfo.pFitness = pFitnessNew;
		return true;
	}//else
	delete pFitnessNew;
	return bReturnValue;
}


/**
 * Comparisson on equal method for two cIndividual objects.
 *
 * @param individual the cIndividual to compare this
 * 	individual to
 * @param checkIdentifiers if true (standradvalue) the identifiers will
 * 	be checked allso, else not
 * @return true if the cIndividual this object represents is
 * 	equal to the cIndividual the given object individual
 * 	represents
 */
bool cIndividual::equal( const cIndividual &individual, bool checkIdentifiers ) const{
	
	
	if ( getClassName() != individual.getClassName() ){
		return false;
	}
	
	if ( ! (individalInfo.equal( individual.individalInfo, checkIdentifiers ) ) ){
		return false;
	}

	return true;
}


/**
 * Comparisson on equal operator for two cIndividual objects.
 *
 * @param individual the cIndividual to compare this
 * 	individual to
 * @return true if the cIndividual this object represents is
 * 	equal to the cIndividual the given object individual
 * 	represents
 */
bool cIndividual::operator==( const cIndividual &individual ) const{
	
	return ( this->equal( individual ) );
}


/**
 * Comparisson on not equal operator for two cIndividual objects.
 *
 * @param idIndividual the cIndividual to compare this
 * 	individual to
 * @return true if the cIndividual this object represents is
 * 	not equal to the cIndividual the given object individual
 * 	represents
 */
bool cIndividual::operator!=( const cIndividual &individual ) const{
	
	return ! ( this->equal( individual ) );
}


/**
 * @return the name of this class
 */
string cIndividual::getClassName() const{

	return "cIndividual";
}


/**
 * This method clones this individual inclusive the containing object.
 *
 * @return a clone of this object
 */
cIndividual * cIndividual::clone() const{

	return new cIndividual( *this );
}


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
cIndividual * cIndividual::clone( bool bCloneObject ) const{
	
	//TODO: can't clone the object because it's class is unknown
	return new cIndividual( *this );
}


/**
 * This method kills the individual, so it isn't living anymor.
 *
 * @see cIndividualInfo::isLiving()
 * @see cIndividualInfo::bIsLiving
 * @return true if the individal was killed, else false
 */
bool cIndividual::kill(){
	
	pObject = NULL;
	bDeleteObjectOnDestruction = false;
	
	return individalInfo.kill();
}



