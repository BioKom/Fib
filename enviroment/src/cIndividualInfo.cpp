/**
 * @file cIndividualInfo
 * file name: cIndividualInfo.cpp
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

#include "cIndividualInfo.h"


using namespace enviroment;


/**
 * constructor
 *
 * @param ulAlgorithmIdentifier the identifier of the enviroment
 * 	instantiation
 * @param liIdentifierOfParents the list with the identifiers of the
 * 	parent individuals of the individual for which this info is
 * @param inFitness the pFitness of the individual
 * @param szOperationName the name of the operation which created the
 * 	individual
 * @param szOperationInfo some more information about the operation
 * 	which created the individual
 * @param operationIdentifier the identifier of the operation which
 * 	created the individual
 * @param inCreationTime the time_t when the individual was created
 * @param dOperationCost the cost for the creation of the individual
 * @param pInFitnessOfBestAtCreationTime the pFitness of the best
 * 	individual, at the time_t the individual was created
 */
cIndividualInfo::cIndividualInfo( unsigned long ulAlgorithmIdentifier,
		const list<cIndividualIdentifier> & liIdentifierOfParents,
		const cObjectFitness & inFitness,
		const string & szOperationName, const string & szOperationInfo,
		const cOperationIdentifier & operationIdentifier,
		time_t inCreationTime, double dOperationCost,
		const cObjectFitness * pInFitnessOfBestAtCreationTime ):
		idIndividual( ulAlgorithmIdentifier ), bIsLiving( true ),
		szCreatingOperationName( szOperationName ),
		szCreatingOperationInfo( szOperationInfo ),
		idCreatingOperation( operationIdentifier ),
		creationTime( inCreationTime ),
		dCreationOperationCost( dOperationCost ),
		pFitnessOfBestAtCreationTime( NULL ){
	
	liIdsParents = liIdentifierOfParents;
	
	pFitness = inFitness.clone();
	if ( pInFitnessOfBestAtCreationTime ){
		pFitnessOfBestAtCreationTime = pInFitnessOfBestAtCreationTime->clone();
	}else{
		pFitnessOfBestAtCreationTime = inFitness.clone();
	}
}


/**
 * copyconstructor
 *
 * @param individualInfo the cIndividualInfo to copy
 */
cIndividualInfo::cIndividualInfo( const cIndividualInfo & individualInfo ):
		idIndividual( individualInfo.idIndividual ),
		bIsLiving( individualInfo.bIsLiving ),
		szCreatingOperationName( individualInfo.szCreatingOperationName ),
		szCreatingOperationInfo( individualInfo.szCreatingOperationInfo ),
		idCreatingOperation( individualInfo.idCreatingOperation ),
		creationTime( individualInfo.creationTime ),
		dCreationOperationCost( individualInfo.dCreationOperationCost ),
		pFitnessOfBestAtCreationTime( NULL ){
	
	liIdsParents = individualInfo.liIdsParents;
	
	pFitness = individualInfo.pFitness->clone();

	if ( individualInfo.pFitnessOfBestAtCreationTime ){
		pFitnessOfBestAtCreationTime = individualInfo.pFitnessOfBestAtCreationTime->clone();
	}else{
		pFitnessOfBestAtCreationTime = individualInfo.pFitness->clone();
	}
}


/**
 * destructor
 */
cIndividualInfo::~cIndividualInfo(){
	
	if ( pFitness ){
		delete pFitness;
	}
	if ( pFitnessOfBestAtCreationTime ){
		delete pFitnessOfBestAtCreationTime;
	}
}


/**
 * @see idIndividual
 * @return the identifier of a individual
 */
cIndividualIdentifier cIndividualInfo::getIdentifier() const{
	return idIndividual;
}

/**
 * This method kills the individual, so it isn't living anymor.
 * (The method dosn't change or deletes the object of the individual,
 * but sets it's status to not living.)
 *
 * @see isLiving()
 * @see bIsLiving
 * @return true if the individal was killed, else false
 */
bool cIndividualInfo::kill(){
	if ( ! bIsLiving ){
		return false;
	}//else
	bIsLiving = false;
	return true;
}

/**
 * @see kill()
 * @see bIsLiving
 * @return true if the object is living, else false
 */
bool cIndividualInfo::isLiving() const{
	return bIsLiving;
}


/**
 * @see liIdsParents
 * @return the list with the identifiers of the parent individuals of
 * 	the individual for which this info is
 */
list<cIndividualIdentifier> cIndividualInfo::getIdentifiersOfParents() const{
	return liIdsParents;
}


/**
 * @see pFitness
 * @return a pointer to the pFitness of the individual
 */
const cObjectFitness * cIndividualInfo::getFitness() const{
	return pFitness;
}


/**
 * @see szCreatingOperationName
 * @return the name of the operation which created the individual
 */
string cIndividualInfo::getOperatorName() const{
	return szCreatingOperationName;
}


/**
 * @see szCreatingOperationInfo
 * @return some more information about the operation which created
 * 	the individual
 */
string cIndividualInfo::getOperatorInfo() const{
	return szCreatingOperationInfo;
}


/**
 * @see idCreatingOperation
 * @return the identifier of the operation which created the individual
 */
cOperationIdentifier cIndividualInfo::getOperatorIdentifier() const{
	return idCreatingOperation;
}


/**
 * @see creationTime
 * @return the time_t when the individual was created
 */
time_t cIndividualInfo::getCreationTime() const{
	return creationTime;
}


/**
 * @see dCreationOperationCost
 * @return the cost for the creation of the individual
 */
double cIndividualInfo::getOperationCost() const{
	return dCreationOperationCost;
}


/**
 * @see pFitnessOfBestAtCreationTime
 * @return a pointer to pFitness the of the best individual, at the time_t the
 * 	individual was created
 */
const cObjectFitness * cIndividualInfo::getFitnessOfBestAtCreationTime() const{
	return pFitnessOfBestAtCreationTime;
}


/**
 * Comparisson on equal method for two cIndividualInfo objects.
 *
 * @param infoIndividual the cIndividualInfo to compare this
 * 	cIndividualInfo to
 * @param checkIdentifiers if true (standradvalue) the identifiers will
 * 	be checked also, else not
 * @return true if the cIndividualInfo this object represents is
 * 	equal to the cIndividualInfo the given object idIndividual
 * 	represents
 */
bool cIndividualInfo::equal( const cIndividualInfo &infoIndividual,
		bool checkIdentifiers ) const{

	if ( checkIdentifiers ){
		if ( idIndividual != infoIndividual.idIndividual ){
			return false;
		}
		if ( liIdsParents != infoIndividual.liIdsParents ){
			return false;
		}
		if ( idCreatingOperation != infoIndividual.idCreatingOperation ){
			return false;
		}
	}
	
	if ( bIsLiving != infoIndividual.bIsLiving ){
		return false;
	}
	if ( ! ( (*pFitness) == *(infoIndividual.pFitness) ) ){
		return false;
	}
	if ( szCreatingOperationName != infoIndividual.szCreatingOperationName ){
		return false;
	}
	if ( szCreatingOperationInfo != infoIndividual.szCreatingOperationInfo ){
		return false;
	}
	if ( creationTime != infoIndividual.creationTime ){
		return false;
	}
	if ( dCreationOperationCost != infoIndividual.dCreationOperationCost ){
		return false;
	}
	if ( ! ( (*pFitnessOfBestAtCreationTime) == *(infoIndividual.pFitnessOfBestAtCreationTime) ) ){
		return false;
	}

	return true;
}


/**
 * Comparisson on equal operator for two cIndividualInfo objects.
 *
 * @param infoIndividual the cIndividualInfo to compare this
 * 	cIndividualInfo to
 * @return true if the cIndividualInfo this object represents is
 * 	equal to the cIndividualInfo the given object idIndividual
 * 	represents
 */
bool cIndividualInfo::operator==( const cIndividualInfo &infoIndividual ) const{

	return this->equal( infoIndividual);
}


/**
 * Comparisson on not equal operator for two cIndividualInfo objects.
 *
 * @param infoIndividual the cIndividualInfo to compare this
 * 	cIndividualInfo to
 * @return true if the cIndividualInfo this object represents is
 * 	not equal to the cIndividualInfo the given object idIndividual
 * 	represents
 */
bool cIndividualInfo::operator!=( const cIndividualInfo &infoIndividual ) const{
	return ! ( this->equal( infoIndividual) );
}



/**
 * This method clones this object.
 *
 * @return a clone of this object
 */
cIndividualInfo * cIndividualInfo::clone() const{
	
	return new cIndividualInfo( *this );
}






