/**
 * @file cOpRemoveOverwrittenUnderObjects
 * file name: cOpRemoveOverwrittenUnderObjects.cpp
 * @author Betti Oesterholz
 * @date 15.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This operator removes from a random choosen fib -object all underobjects
 * which point properties are overwritten and so not necessary.
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
 * This operator removes from a random choosen fib -object all underobjects
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


#include "cOpRemoveOverwrittenUnderObjects.h"

#include "cEnviroment.h"

#include "cFibIndividual.h"

#include "nReduceFibObject.h"

#include <ctime>


using namespace std;
using namespace fib::algorithms::nReduceFibObject;
using namespace enviroment;
using namespace enviroment::fib;

/**
 * The standardconstructor for the operation.
 * It will create the operation, but won't start it.
 *
 * @param operationId the identifer for the operation
 */
cOpRemoveOverwrittenUnderObjects::cOpRemoveOverwrittenUnderObjects( const cOperationIdentifier & operationId ):
		cOperationFib( operationId ){
	//nothing to do
}


/**
 * Destructor of the class cOpRemoveOverwrittenUnderObjects.
 */
cOpRemoveOverwrittenUnderObjects::~cOpRemoveOverwrittenUnderObjects(){
	//nothing to do
}


/**
 * This method creats a new instance of this operator.
 * Beware: You have to delete the instance after usage.
 *
 * @param operationId the identifer for the operation
 * @return a pointer to a new instance of this operation
 */
cOpRemoveOverwrittenUnderObjects * cOpRemoveOverwrittenUnderObjects::createInstance(
		const cOperationIdentifier & operationId ) const{
	
	return new cOpRemoveOverwrittenUnderObjects( operationId );
}


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
bool cOpRemoveOverwrittenUnderObjects::run(){
	
	DEBUG_OUT_L1(<<getName()<<"::run()"<<endl<<flush);
	
	if ( isRunning() || bStop ){
		//the operation runs allready
		return false;
	}
	
	cEnviroment * pEnviroment = cEnviroment::getInstance();
	
	if ( pEnviroment == NULL ){
		//no enviroment for the operation
		return false;
	}
	//check if the individualtype is correct
	if ( pEnviroment->OPERATION_DOMAIN != OPERATION_DOMAIN ){
		//wrong enviromenttype for the operation
		return false;
	}
	setIsRunning( true );
	
	DEBUG_OUT_L1(<<getName()<<"::run()"<<endl<<flush);

	//choose random fib -individual
	cFibIndividual * pIndividual = ((cFibIndividual*)(pEnviroment->getIndividual()));
	
	//remove from the individual overwritten underobjects
	const bool bUnderobjectRemoved = removeOverwrittenUnderObjects(
		( *( pIndividual->getFibObject() ) ) );
	
	if ( ! bUnderobjectRemoved ){
		delete pIndividual;
		setIsRunning( false );
		return true;
	}
	//if underobjects wher removed -> insert changed individual into the enviroment
	
	list<cIndividualIdentifier> liParents;
	liParents.push_back( pIndividual->getInfo()->getIdentifier() );
	
	const bool bIndividualInserted = insertFibObjectIntoEnviroment(
		pIndividual->getFibObject(), liParents );
	
	setIsRunning( false );
	return bIndividualInserted;
}


/**
 * @return the (class-)name of the operation
 */
string cOpRemoveOverwrittenUnderObjects::getName() const{
	return "cOpRemoveOverwrittenUnderObjects";
}





