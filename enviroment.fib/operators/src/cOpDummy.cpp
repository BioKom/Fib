/**
 * @file cOpDummy
 * file name: cOpDummy.cpp
 * @author Betti Oesterholz
 * @date 19.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for a dummy operation.
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
 * This header specifies a class for a dummy operation.
 * The operation is for testing the enviroment and do nothing.
 *
 *
 * @see cOperationFib
 * @see cOperation
 * @see cEnviroment
 */
/*
History:
19.03.2010  Oesterholz  created
15.03.2012  Oesterholz  changes for windows compatibility
*/


#include "cOpDummy.h"

#include "cEnviroment.h"


using namespace std;
using namespace enviroment;
using namespace enviroment::fib;


/**
 * The standardconstructor for the operation.
 * It will create the operation, but won't start it.
 *
 * @param operationId the identifer vor the operation
 */
cOpDummy::cOpDummy( const cOperationIdentifier & operationId ):
		cOperationFib( operationId ){
	//nothing to do
}


/**
 * Destructor of the class cOpDummy.
 */
cOpDummy::~cOpDummy(){
	//nothing to do
}


/**
 * This method creats a new instance of this operator.
 * Beware: You have to delete the instance after usage.
 *
 * @param operationId the identifer for the operation
 * @return a pointer to a new instance of this operation
 */
cOpDummy * cOpDummy::createInstance(
		const cOperationIdentifier & operationId ) const{
	
	return new cOpDummy( operationId );
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
bool cOpDummy::run(){
	
	DEBUG_OUT_L1(<<getName()<<"::run() start"<<endl<<flush);
	
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

#ifdef WINDOWS
	Sleep( 1 );
#else//WINDOWS
	struct timespec timeToWait;
	struct timespec remainingTime;
	timeToWait.tv_sec  = 0;
	timeToWait.tv_nsec = 1000000L; //1000000L = 1 ms
	nanosleep( &timeToWait, &remainingTime );
#endif//WINDOWS

	setIsRunning( false );
	return true;
}


/**
 * @return the (class-)name of the operation
 */
string cOpDummy::getName() const{
	return "cOpDummy";
}





