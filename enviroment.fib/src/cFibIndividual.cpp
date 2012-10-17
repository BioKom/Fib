/**
 * @file cFibIndividual
 * file name: cFibIndividual.cpp
 * @author Betti Oesterholz
 * @date 01.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for a fib -individal.
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
 * This header specifies a class for a fib -individals.
 * An individal is an central object on which the genetic algorithm
 * (enviroment) works.
 * It contains a fib -object with it's information.
 *
 */
/*
History:
01.03.2010  Oesterholz  created
*/


#include "cFibIndividual.h"


using namespace enviroment::fib;


/**
 * constructor
 *
 * @param pInFibObject the fib -object which is represented by the individual;
 * 	this fib -object won't be copied but destructed when the individual is
 * 	destructed if bInDeleteObjectOnDestruction is true
 * @param inIndividalInfo the information for the individual
 * @param bInDeleteObjectOnDestruction if true delete the object
 * 	(pInObject) when the individual is deleted
 */
cFibIndividual::cFibIndividual( cFibElement * pInFibObject,
		const cIndividualInfo & inIndividalInfo,
		bool bInDeleteObjectOnDestruction ):
		cIndividual( pInFibObject, inIndividalInfo, bInDeleteObjectOnDestruction),
		pFibObject( pInFibObject ){
	//nothing to do
}


/**
 * constructor
 * A copy of the contained fib individual is also done.
 *
 * @param fibIndividual the fib -individual to copy
 */
cFibIndividual::cFibIndividual( const cFibIndividual & fibIndividual ):
	cIndividual( fibIndividual ){
	
	bDeleteObjectOnDestruction = fibIndividual.bDeleteObjectOnDestruction;
	
	if ( fibIndividual.pFibObject != NULL ){
		if ( bDeleteObjectOnDestruction ){
			pFibObject = fibIndividual.pFibObject->clone();
		}else{
			pFibObject = fibIndividual.pFibObject;
		}
	}else{
		pFibObject = NULL;
	}
	pObject = pFibObject;
}


/**
 * destructor
 * It deletes the objekt to the individual.
 */
cFibIndividual::~cFibIndividual(){
	
	if ( bDeleteObjectOnDestruction && (pFibObject != NULL) ){
		cFibElement::deleteObject( pFibObject );
	}
}


/**
 * @return a pointer to the object which is represented by the individual
 */
cFibElement * cFibIndividual::getFibObject(){

	return pFibObject;
}


/**
 * @return a pointer to the object which is represented by the individual
 */
const cFibElement * cFibIndividual::getFibObject() const{

	return pFibObject;
}


/**
 * @return the name of this class
 */
string cFibIndividual::getClassName() const{

	return "cFibIndividual";
}


/**
 * Comparisson on equal method for two cIndividual objects.
 *
 * @param individual the cIndividual to compare this
 * 	idIndividualobject to
 * @param checkIdentifiers if true (standradvalue) the identifiers will
 * 	be checked allso, else not
 * @return true if the cIndividual this object represents is
 * 	equal to the cIndividual the given object individual
 * 	represents
 */
bool cFibIndividual::equal( const cIndividual &individual,
		bool checkIdentifiers ) const{

	if ( ! cIndividual::equal( individual, checkIdentifiers ) ){
		return false;
	}
	if ( pFibObject != NULL ){
		if ( ((cFibIndividual*)&individual)->getFibObject() == NULL ){
			//not both individuals have no fib -object
			return false;
		}
		if ( ! (pFibObject->equal( *(((cFibIndividual*)&individual)->getFibObject()) )) ){
			return false;
		}
	}else{
		if ( ((cFibIndividual*)&individual)->getFibObject() != NULL ){
			//not both individuals have no fib -object
			return false;
		}
	}
	
	return true;
}


/**
 * This method clones this individual inclusive the containing object.
 *
 * @return a clone of this object
 */
cFibIndividual * cFibIndividual::clone() const{

	return new cFibIndividual( *this );
}


/**
 * This method clones this individual inclusive the containing object.
 *
 * @return a clone of this object
 * @param bCloneObject if true the object will be cloned and
 * 	@see bInDeleteObjectOnDestruction will be set to true, if false
 * 	the object won't be cloned and @see bInDeleteObjectOnDestruction
 * 	will be set to false
 */
cFibIndividual * cFibIndividual::clone( bool bCloneObject ) const{
	
	if ( bCloneObject ){
		return new cFibIndividual( pFibObject->clone(),
			individalInfo, true );
	}//else
	return new cFibIndividual( pFibObject,
		individalInfo, false );
}


/**
 * This method kills the individual, so it isn't living anymor.
 *
 * @see cIndividualInfo::isLiving()
 * @see cIndividualInfo::bIsLiving
 * @return true if the individal was killed, else false
 */
bool cFibIndividual::kill(){
	
	
	if ( bDeleteObjectOnDestruction && (pFibObject != NULL) ){
		cFibElement::deleteObject( pFibObject );
	}
	pFibObject = NULL;
	
	return cIndividual::kill();
}



