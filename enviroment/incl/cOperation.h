/**
 * @file cOperation
 * file name: cOperation.h
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


#ifndef ___C_OPERATION_H__
#define ___C_OPERATION_H__

#include "version.h"

#include "cOperationIdentifier.h"

#include <string>
#include <set>
#include <ctime>

#ifdef WINDOWS
	#include <windows.h>
#endif //WINDOWS


namespace enviroment{


class cOperation;

/**
 * This is the interface for objects, which want's to be notified about
 * changes in the operation running status.
 */
class ciOperationStatusChange{
public:
	/**
	 * This method is called, if the running status of the operation is changed.
	 *
	 * @see cOperation::bIsRunning
	 * @see cOperation::isRunning()
	 * @param pOperation a pointer to the operation, which status has changed
	 * @param isRunning the new running status for the operation
	 */
	virtual void operationStatusChange( cOperation * pOperation, bool isRunning ) = 0;
};


class cOperation{
private:
#ifdef WINDOWS
	/**
	 * Mutex variable for handling the set with the operation status change
	 * listeners ( @see setOperationListeners ).
	 */
	HANDLE mutexOperationStatusChange;
	
	/**
	 * Mutex variable for changing the operation run status in one step.
	 * @see bIsRunning
	 * @see bHasRun
	 */
	HANDLE mutexRunStatusChange;
	
	/**
	 * The tread for running the operation.
	 * @see start()
	 * @see run()
	 */
	HANDLE pThreadOperator;

#else //WINDOWS
	/**
	 * Mutex variable for handling the set with the operation status change
	 * listeners ( @see setOperationListeners ).
	 */
	pthread_mutex_t mutexOperationStatusChange;
	
	/**
	 * Mutex variable for changing the operation run status in one step.
	 * @see bIsRunning
	 * @see bHasRun
	 */
	pthread_mutex_t mutexRunStatusChange;
	
	/**
	 * The tread for running the operation.
	 * @see start()
	 * @see run()
	 */
	pthread_t * pThreadOperator;
#endif //WINDOWS
	
	/**
	 * If true the operation is running, else not.
	 */
	bool bIsRunning;
	
	/**
	 * If true the operation has run, else not.
	 */
	bool bHasRun;
	
protected:
	
	/**
	 * If true the operation should be stoped, else not.
	 * Beware: Check this variable in your operation implementation and
	 * 	stop the execution if the variable is true.
	 */
	bool bStop;
	
	/**
	 * The identifier for the operation.
	 */
	cOperationIdentifier operationIdentifier;
	
	/**
	 * A value for the cpu -time this operation runs.
	 */
	double dRunningTime;
	
private:
	/**
	 * The last time the cpu -time was evalued.
	 * This is needed to evalue the @see dRunningTime .
	 */
	clock_t tmLastCpuRunTime;
	
protected:

	/**
	 * The standardconstructor for the operation.
	 * It will create the operation, but won't start it.
	 *
	 * @param operationId the identifer for the operation
	 * @param szOperationDomain the type of individuals on which the
	 * 	operation will run
	 */
	cOperation( const cOperationIdentifier & operationId,
		std::string szOperationDomain = "cIndividual" );
	
public:

	/**
	 * Destructor of the class cOperation.
	 */
	virtual ~cOperation() = 0;

	/**
	 * The type of individuals on which the operation will run.
	 */
	const std::string OPERATION_DOMAIN;

	/**
	 * This method creats a new instance of this operator.
	 * Beware: You have to delete the instance after usage.
	 *
	 * @param operationId the identifer for the operation
	 * @return a pointer to a new instance of this operation
	 */
	virtual cOperation * createInstance( const cOperationIdentifier & operationId ) const = 0;

	/**
	 * This method starts the operation and returns.
	 * It dosn't wait till the operation is ended for returning.
	 * Overwrite this or the run() method to implement the operation.
	 * Beware: If overwriten call setIsRunning( false ), when the operation
	 * is done.
	 *
	 * @see run()
	 * @see stop()
	 * @see setIsRunning()
	 * @return true if the operation was started
	 */
	virtual bool start();
	
	/**
	 * This method runs the operation.
	 * It will wait till the operation is ended befor returning.
	 * Overwrite this or the start() method to implement the operation.
	 * Beware: If overwriten call setIsRunning( false ), when the operation
	 * is done.
	 *
	 * @see start()
	 * @see stop()
	 * @see setIsRunning()
	 * @return true if the operation was started
	 */
	virtual bool run();
	
	
	/**
	 * This method stops the operation and returns.
	 *
	 * @see bStop
	 * @see run()
	 * @see start()
	 * @return true if this operation is stoped, else false
	 */
	virtual bool stop();
	
	/**
	 * @see bIsRunning
	 * @see run()
	 * @see start()
	 * @see stop()
	 * @return true if this operation is running, else false
	 */
	virtual bool isRunning() const;
	
	/**
	 * @see bHasRun
	 * @see bIsRunning
	 * @see run()
	 * @see start()
	 * @see stop()
	 * @return true the operation has run, else not
	 */
	virtual bool hasRun() const;
	
	
	/**
	 * @return A value for the cpu -time this operation runs.;
	 * 	@see isRunning() gives back true for this time
	 * @see dRunningTime
	 */
	double getCpuRunTime() const;

	/**
	 * @return the (class-)name of the operation
	 */
	virtual std::string getName() const;
	
	/**
	 * @see operationIdentifier
	 * @return the identifier for this operation
	 */
	virtual const cOperationIdentifier * getOperationIdentifier() const;
	
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
	bool registerOperationRunStatusListener(
		ciOperationStatusChange * pOperationRunStatusListener );
	
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
	bool unregisterOperationRunStatusListener(
		ciOperationStatusChange * pOperationRunStatusListener );

protected:

	/**
	 * This method sets the value if this operation is running to the given
	 * value. It notifies allso objects which listen to operation status
	 * changes.
	 *
	 * @see isRunning
	 * @param bInIsRunning the value, if this operation is running
	 * @return the new value, if this operation is running
	 */
	bool setIsRunning( bool bInIsRunning );

private:
	
	/**
	 * If the run() or start() method of this class cOperation was called
	 * this filed is true.
	 * It should stop cyclic class of run() and start();
	 */
	bool bOperationStartedInRoot;
	
	/**
	 * The set with pointers to objects, which want's to be notified if the
	 * operation running status changes.
	 * @see ciOperationStatusChange
	 */
	std::set< ciOperationStatusChange * > setOperationListeners;
	
	
	/**
	 * This method runs the operation for a tread.
	 * It will wait till the operation is ended befor returning.
	 * It will simply call run().
	 *
	 * @see run()
	 * @see start()
	 * @see stop()
	 */
	static void * runTread( void * inputArg );

#ifdef WINDOWS
	/**
	 * Wraper function for windows.
	 * Wait till the given mutex is free and than locks it.
	 * @param pMutexHandle pointer to the mutex to lock.
	 */
	static void pthread_mutex_lock( HANDLE * pMutexHandle );

	/**
	 * Wraper function for windows.
	 * Unlocks the given mutex.
	 * @param pMutexHandle pointer to the mutex to unlock.
	 */
	static void pthread_mutex_unlock( HANDLE * pMutexHandle );
#endif //WINDOWS
	
	/**
	 * This function sleeps for a short period.
	 */
	static void shortSleep();

};//end class cOperation


};//end namespace enviroment

#endif //___C_OPERATION_H__







