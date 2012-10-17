/**
 * @file cOperation
 * file name: cOperation.cpp
 * @author Betti Oesterholz
 * @date 19.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies the abstract basisclass for operations.
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
 * This header specifies the abstract basisclass for operations.
 * Overwrite the start() or run() method to implement the operation.
 *
 * Beware: If the variable bStop is true, stop the operation.
 *
 * @see cEnviroment
 */
/*
History:
19.03.2010  Oesterholz  created
15.03.2012  Oesterholz  changes for windows compatibility
*/

//TODO weg
//#define DEBUG

#include "cOperation.h"

#include "cEnviroment.h"

#include <string>

#include <ctime>
#include <pthread.h>

#ifdef DEBUG
	#include <cerrno>
	
	static long long lOperationTreadsRunning = 0;
#endif

using namespace std;
using namespace enviroment;



/**
 * The standardconstructor for the operation.
 * It will create the operation, but won't start it.
 *
 * @param operationId the identifer vor the operation
 * @param szOperationDomain the type of individuals on which the
 * 	operation will run
 */
cOperation::cOperation( const cOperationIdentifier & operationId,
		string szOperationDomain ): pThreadOperator( NULL ),
		bIsRunning( false ), bHasRun( false ), bStop( false ),
		operationIdentifier( operationId ),
		dRunningTime( 0.01 ), tmLastCpuRunTime( 0 ),
		OPERATION_DOMAIN( szOperationDomain ),
		bOperationStartedInRoot( false ){
	
	//init mutex variables
#ifdef WINDOWS
	//close mutex handles
	if ( mutexOperationStatusChange == NULL ){
		mutexOperationStatusChange = CreateMutex( NULL, FALSE, NULL);
	}
	if ( mutexRunStatusChange == NULL ){
		mutexRunStatusChange = CreateMutex( NULL, FALSE, NULL);
	}
#else//WINDOWS
	pthread_mutex_init( &mutexOperationStatusChange, NULL);
	pthread_mutex_init( &mutexRunStatusChange, NULL);
#endif//WINDOWS
}


/**
 * Destructor of the class cOperation.
 */
cOperation::~cOperation(){
	
#ifdef WINDOWS
	if ( pThreadOperator != NULL ){
		//wait till tread is done and join it with this tread
		WaitForMultipleObjects( 1, &pThreadOperator, TRUE, INFINITE );
		//close thread handles
		CloseHandle( pThreadOperator );
	}
	//close mutex handles
    CloseHandle( mutexOperationStatusChange );
	mutexOperationStatusChange = NULL;
    CloseHandle( mutexRunStatusChange );
	mutexRunStatusChange = NULL;

#else //WINDOWS
	if ( pThreadOperator != NULL ){
		//wait till tread is done and join it with this tread
		pthread_join( *pThreadOperator, NULL);

		delete pThreadOperator;
	}
	//destroy the mutexs
	pthread_mutex_lock( & mutexOperationStatusChange );
	pthread_mutex_unlock( & mutexOperationStatusChange );
	pthread_mutex_destroy( &mutexOperationStatusChange );
	
	pthread_mutex_lock( & mutexRunStatusChange );
	pthread_mutex_unlock( & mutexRunStatusChange );
	pthread_mutex_destroy( &mutexRunStatusChange );
#endif //WINDOWS
}


/**
 * This method starts the operation and returns.
 * It dosn't wait till the operation is ended for returning.
 * Overwrite this or the run() method to implement the operation.
 * Beware: If overwriten set bIsRunning to false, when the operation is done.
 *
 * @see run()
 * @see stop()
 * @return true if the operation was started
 */
bool cOperation::start(){
	
	if ( isRunning() || hasRun() || bStop || bOperationStartedInRoot ){
		//the operation runs allready
		DEBUG_OUT_L2(<<"Operation "<<((isRunning())?"is running ":"not running ")<<((hasRun())?"has run ":"has not run ")<<(bStop?"stoped ":"not stopped ")<<(bOperationStartedInRoot?"started in root":"not started in root")<<endl<<flush);
		return false;
	}
	cEnviroment * pEnviroment = cEnviroment::getInstance();
	
	if ( pEnviroment == NULL ){
		//no enviroment for the operation
		DEBUG_OUT_L2(<<"Enviroment is NULL."<<endl<<flush);
		return false;
	}
	//check if the individualtype is correct
	if ( pEnviroment->OPERATION_DOMAIN != OPERATION_DOMAIN ){
		//wrong enviromenttype for the operation
		DEBUG_OUT_L2(<<"Thread could not started. Operation domain false."<<endl<<flush);
		return false;
	}
	if ( pThreadOperator != NULL ){
		DEBUG_OUT_L2(<<"Thread was created allready."<<endl<<flush);
		return false;
	}
	bOperationStartedInRoot = true;
	
#ifdef WINDOWS
	DWORD   dwThreadId = 0;
	pThreadOperator = CreateThread( 
		NULL, //default security attributes
		0, //use default stack size  
		(LPTHREAD_START_ROUTINE)&(cOperation::runTread), //thread function name
		this, //argument to thread function 
		0, //use default creation flags 
		&dwThreadId ); //returns the thread identifier 
	
	const int iReturn = ( pThreadOperator == NULL ) ? 1 : 0 ;
#else //WINDOWS
	pThreadOperator = new pthread_t();
	//run the operation in a seperate tread
	int iReturn = pthread_create( pThreadOperator, NULL, &(cOperation::runTread), this );
#endif //WINDOWS
	
	DEBUG_OUT_L2(<<"Operation treads running:"<<lOperationTreadsRunning<<endl<<flush);
	
	bOperationStartedInRoot = false;
	if ( iReturn != 0 ){
		DEBUG_OUT_L2(<<"Thread could not started. Return code "<<iReturn<<" ("<<((iReturn==EINVAL)?"attribute invalid":"")<<((iReturn==EAGAIN)?"not enougth resources":"")<<" )."<<endl<<flush);
		return false;
	}
	return true;
}


/**
 * This method runs the operation.
 * It will wait till the operation is ended befor returning.
 * Overwrite this or the start() method to implement the operation.
 * Beware: If overwriten set bIsRunning to false, when the operation is done.
 *
 * @see start()
 * @see stop()
 * @return true if the operation was started
 */
bool cOperation::run(){

	if ( isRunning() || bStop || bOperationStartedInRoot ){
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
	bOperationStartedInRoot = true;
	//start the operation and wait till it's done
	if ( ! start() ){
		bOperationStartedInRoot = false;
		return false;
	}
	//wait till the operation is done
	while ( isRunning() ){
		shortSleep();
	}
	
	bOperationStartedInRoot = false;
	return true;
}


/**
 * This method stops the operation and returns.
 *
 * @see bStop
 * @see run()
 * @see start()
 * @return true if this operation is stoped, else false
 */
bool cOperation::stop(){
	
	if ( ! isRunning() ){
		//nothing to stop
		return false;
	}
	bStop = true;
	
	//wait till the operation is done
	while ( isRunning() ){
		shortSleep();
	}
	
	bStop = false;
	return true;
}


/**
 * @see bIsRunning
 * @see run()
 * @see start()
 * @see stop()
 * @return true if this operation is running, else false
 */
bool cOperation::isRunning() const{
	
	return bIsRunning;
}


/**
 * @see bHasRun
 * @see bIsRunning
 * @see run()
 * @see start()
 * @see stop()
 * @return true the operation has run, else not
 */
bool cOperation::hasRun() const{

	return bHasRun;
}


/**
 * @return the (class-)name of the operation
 */
string cOperation::getName() const{
	return "cOperation";
}


/**
 * @see operationIdentifier
 * @return the identifier for this operation
 */
const cOperationIdentifier * cOperation::getOperationIdentifier() const{

	return &operationIdentifier;
}


/**
 * This method adds the given operation running status listener object
 * to the set of running status listener objects. Listeners of the set
 * gets notified if the running status of this object/ operation changes.
 *
 * @see unregisterOperationRunStatusListener()
 * @see setOperationListeners
 * @see ciOperationStatusChange
 * @param pOperationRunStatusListener a pointer to the operation running
 * 	status listener object to add to the set of operation running listeners
 * @return true if the operation running listener was added, else false
 */
bool cOperation::registerOperationRunStatusListener(
		ciOperationStatusChange * pOperationRunStatusListener ){
	
	if ( pOperationRunStatusListener == NULL ){
		//can't insert non object
		return false;
	}
	pthread_mutex_lock( & mutexOperationStatusChange );
	pair< set<ciOperationStatusChange*>::iterator, bool > paInserted =
		setOperationListeners.insert( pOperationRunStatusListener );
	pthread_mutex_unlock( & mutexOperationStatusChange );

	return paInserted.second;
}


/**
 * This method removes the given operation running status listener object
 * from the set of running status listener objects. Listeners of the set
 * gets notified if the running status of this object/ operation changes.
 *
 * @see registerOperationRunStatusListener()
 * @see setOperationListeners
 * @see ciOperationStatusChange
 * @param pOperationRunStatusListener a pointer to the operation running
 * 	status listener object to removes from the set of operation
 * 	running listeners
 * @return true if the operation running listener was removed, else false
 */
bool cOperation::unregisterOperationRunStatusListener(
		ciOperationStatusChange * pOperationRunStatusListener ){
	
	pthread_mutex_lock( & mutexOperationStatusChange );
	const size_t iElementsRemoved =
		setOperationListeners.erase( pOperationRunStatusListener );
	pthread_mutex_unlock( & mutexOperationStatusChange );
	return ( iElementsRemoved == 1);
}


/**
 * This method sets the value if this operation is running to the given
 * value. It notifies allso objects which listen to operation status
 * changes.
 *
 * @see isRunning
 * @param bInIsRunning the value, if this operation is running
 * @return the new value, if this operation is running
 */
bool cOperation::setIsRunning( bool bInIsRunning ){
	
	pthread_mutex_lock( & mutexRunStatusChange );
	if ( bIsRunning != bInIsRunning ){
		//notify the listeners for operation status changes about the change
		pthread_mutex_lock( & mutexOperationStatusChange );
		//copy the listener set, so it can't change while the listeners get notyfied
		set<ciOperationStatusChange*> setOperationListenersTmp = setOperationListeners;
		pthread_mutex_unlock( & mutexOperationStatusChange );
		
		for ( set<ciOperationStatusChange*>::iterator
				itrOpRunListener = setOperationListenersTmp.begin();
				itrOpRunListener != setOperationListenersTmp.end(); itrOpRunListener++ ){
			
			(*itrOpRunListener)->operationStatusChange( this, bInIsRunning );
		}
		{//remember the operation runtime
			if ( bInIsRunning ){
				//the operation was started
				tmLastCpuRunTime = clock();
			}else{//the operation was stoped
				dRunningTime += clock() - tmLastCpuRunTime;
				tmLastCpuRunTime = 0;
			}
		}
		if ( bIsRunning ){
			//the operation is running but now ends it run
			bHasRun = true;
		}
		bIsRunning = bInIsRunning;
	}
	pthread_mutex_unlock( & mutexRunStatusChange );
	return bIsRunning;
}


/**
 * @return A value for the cpu -time this operation runs.;
 * 	@see isRunning() gives back true for this time
 * @see dRunningTime
 */
double cOperation::getCpuRunTime() const{
	
	if ( isRunning() ){
		//reevalue the cpu time
		const clock_t tmNewLastCpuRunTime = clock();
		(const_cast<cOperation*>(this))->dRunningTime +=
			tmNewLastCpuRunTime - tmLastCpuRunTime;
		(const_cast<cOperation*>(this))->tmLastCpuRunTime = tmNewLastCpuRunTime;
	}
	return dRunningTime;
}


/**
 * This method runs the operation for a tread.
 * It will wait till the operation is ended befor returning.
 * It will simply call run().
 *
 * @see run()
 * @see start()
 * @see stop()
 */
void * cOperation::runTread( void * inputArg ){
	
#ifdef DEBUG
	lOperationTreadsRunning++;
#endif
	
	((cOperation*)(inputArg))->run();
	
#ifdef DEBUG
	lOperationTreadsRunning--;
#endif

#ifndef WINDOWS
	//exit tread
	pthread_exit(NULL);
#endif //WINDOWS
	
	return NULL;
}


#ifdef WINDOWS
/**
 * Wraper function for windows.
 * Wait till the given mutex is free and than locks it.
 * @param pMutexHandle pointer to the mutex to lock.
 */
void cOperation::pthread_mutex_lock( HANDLE * pMutexHandle ){
	
	WaitForSingleObject( &pMutexHandle, INFINITE);
}

/**
 * Wraper function for windows.
 * Unlocks the given mutex.
 * @param pMutexHandle pointer to the mutex to unlock.
 */
void cOperation::pthread_mutex_unlock( HANDLE * pMutexHandle ){
	
	ReleaseMutex( &pMutexHandle );
}
#endif //WINDOWS


/**
 * This function sleeps for a short period.
 */
void cOperation::shortSleep(){
	
#ifdef WINDOWS
	Sleep( 10 );
#else//WINDOWS
	static struct timespec timeToWait;
	timeToWait.tv_sec  = 0;
	timeToWait.tv_nsec = 10000000L; //= 10 ms
	static struct timespec remainingTime;
	nanosleep( &timeToWait, &remainingTime );
#endif//WINDOWS
}






