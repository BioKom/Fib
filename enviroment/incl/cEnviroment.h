/**
 * @file cEnviroment
 * file name: cEnviroment.h
 * @author Betti Oesterholz
 * @date 15.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for the enviroment.
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
 * This header specifies a class for the enviroment.
 * The enviroment is an genetic algorithm for optimizing individuals.
 * It is generic, so the kind of optimized individuals and what
 * optimization means is easy changebel.
 * The enviroment contains a number of individuals (the population).
 * It calls operations to create new, better individuals. The operators,
 * from which operations are created, are seperated from the enviroment
 * and are classes which are descendants of the class @see cOperation .
 * The enviroment contains a number of methods for the operations, with
 * which the operations can get the information they need to create a new
 * individual and insert it into the enviroment.
 * Beside this the enviroment works with a number of classes /parameters
 * with wich it's behaviour is changed.
 * @pattern Singleton
 *
 */
/*
History:
15.03.2010  Oesterholz  created
15.03.2012  Oesterholz  changes for windows compatibility
*/

#ifndef ___C_ENVIROMENT_H__
#define ___C_ENVIROMENT_H__

#include "version.h"

#include "cIndividual.h"
#include "cIndividualInfo.h"
#include "cOperation.h"


#include <ctime>
#include <list>
#include <set>
#include <map>

#ifdef WINDOWS
	#include <windows.h>
#endif //WINDOWS


using namespace std;

namespace enviroment{

class cInitEnviroment;//cyclic dependencie
class cEndConditionCheck;//cyclic dependencie
class cResourceCheck;//cyclic dependencie
class cIndividualSelection;//cyclic dependencie
class cMaximumReached;//cyclic dependencie
class cSelectIndividualToDelete;//cyclic dependencie
class cOperatorFitnessAlgorithm;//cyclic dependencie
class cChoosOperator;//cyclic dependencie

/**
 * Internal class for a better individual handling.
 */
class cIndividualInformation;

/**
 * Internal class for handling the operation information.
 */
class cOperationInformation;


/**
 * Listener interface for listening for new or deleted individuals.
 *
 * @see cEnviroment::registerIndividualListener()
 * @see cEnviroment::unregisterIndividualListener()
 */
class clNewIndividualListener{
public:

	/**
	 * This method is called if an new individual was added to the enviroment.
	 *
	 * @param pIndividual a pointer to the added individual
	 */
	virtual void individualAdded( const cIndividual * pIndividual ) = 0;
	
	/**
	 * This method is called if an individual was delteted from the enviroment.
	 *
	 * @param pIndividual a pointer to the delteted individual
	 */
	virtual void individualRemoved( const cIndividual * pIndividual ) = 0;
};


class cEnviroment: public ciOperationStatusChange{
protected:
	
	/**
	 * The identifier for the enviroment/ genetic algorithm.
	 * It should be unique for every enviroment, even on different computers.
	 */
	static long long lAlgorithmIdentifier;
	
	/**
	 * A pointer to the enviroment instance.
	 */
	static cEnviroment * pEnviroment;
	
	/**
	 * The tread for running the enviroment.
	 * @see start()
	 * @see stop()
	 * @see run()
	 */
#ifdef WINDOWS
	static HANDLE pThreadEnviroment;
#else //WINDOWS
	static pthread_t * pThreadEnviroment;
#endif //WINDOWS
	
	/**
	 * The container for the living individuals in the enviroment.
	 * This field is for better internal handling of individuals.
	 *
	 * initialize with: mapLivingIndividuals( compIndividualFitness )
	 */
	static map<cIndividualIdentifier, cIndividualInformation > mapLivingIndividuals;
	
	/**
	 * A list with pointers to the informations of the living individuals
	 * in the enviroment.
	 */
	static list<const cIndividualInfo*> liLivingIndividualInfos;
	
	/**
	 * If true the list with the living individuals is sorted, else not.
	 */
	static bool bLiLivingIndividualInfosSorted;
	
	/**
	 * The container for the dead individuals in the enviroment.
	 * This field is for better internal handling of individuals.
	 *
	 * initialize with: mapDeadIndividuals( compIndividualFitness )
	 */
	static map< cIndividualIdentifier, cIndividualInformation > mapDeadIndividuals;
	
	/**
	 * A list with pointers to the informations of the dead individuals
	 * in the enviroment.
	 * This list will allways be sorted with the best individuals (fitness) at the front.
	 */
	static list<const cIndividualInfo*> liDeadIndividualInfos;
	
	/**
	 * If true the list with the living individuals is sorted, else not.
	 */
	static bool bLiDeadIndividualInfosSorted;
	
	/**
	 * A map with the information for the running operations and the information
	 * for them.
	 */
	static map< cOperation * , cOperationInformation > mapRunningOperations;
	
	/**
	 * A list with the operations which are done and can be deleted.
	 */
	static list<cOperation*> liOperationsToDelete;
	
	/**
	 * The number of operations executed/ called by the enviroment.
	 */
	static unsigned long long lNumberOfCalledOperations;
	
	
	/**
	 * The time in secounds the enviroment was running.
	 * (@see isRunning() gives back true for this time)
	 */
	static double dCpuRunTime;
	
	/**
	 * The time the the cpu time was evalued the last time.
	 * This variable is for evaluing the cpu time while the enviroemnt runs.
	 */
	static time_t tmLastCpuRunTime;
	
	
	/**
	 * The time the @see start() method was called the last time.
	 */
	static time_t tmLastStartTime;
	
	/**
	 * The time the @see start() method was called the first time for this
	 * enviroment instance.
	 */
	static time_t tmFirstStartTime;

	
	/**
	 * If true the parameter for the enviroment are set, else not.
	 */
	static bool bParameterSet;
	
	/**
	 * If true the enviroment is running, else not.
	 */
	static bool bIsRunning;
	
	/**
	 * If true the enviroment should be stoped, else not.
	 */
	static bool bStopFlag;
	
	
	/**
	 * A pointer to the object for initializing the enviroment.
	 */
	static cInitEnviroment * pInitEnviroment;
	
	/**
	 * A pointer to the object for evaluing the fitness of individuals
	 * respectively the objects they represents.
	 */
	static cObjectFitnessAlgorithm * pObjectFitnessAlgorithm;
	
	/**
	 * A pointer to the object for checking the endcondition of the
	 * enviroment.
	 */
	static cEndConditionCheck * pEndCondition;
	
	/**
	 * A pointer to the object for selecting a good individual.
	 */
	static cIndividualSelection * pIndividualSelection;
	
	/**
	 * A pointer to the object for checking if individuals needs to
	 * be deleted befor adding new individuals.
	 */
	static cMaximumReached * pMaximumIndividuals;
	
	/**
	 * A pointer to the object for selecting a bad individual.
	 */
	static cSelectIndividualToDelete * pSelectIndividualToDelete;
	
	/**
	 * A pointer to the object for evaluing the fitness of operators of
	 * the enviroment and for handling them.
	 */
	static cOperatorFitnessAlgorithm * pOperationFitnessAlgorithmus;
	
	/**
	 * A pointer to the object for selecting a good operator.
	 */
	static cChoosOperator * pChoosOperator;
	
	/**
	 * A pointer to the object for checking, if more operators could be
	 * started.
	 */
	static cResourceCheck * pResourceCheck;
	
	/**
	 * This set contains pointers to all objects, which want's to be
	 * notified, if new indeviduals wher inserted into the enviroment or old
	 * wher deleted.
	 * @see clNewIndividualListener
	 */
	static set<clNewIndividualListener *> setIndividualListener;
	
	
	/**
	 * standardconstructor
	 * This is called in the getInstance() method.
	 */
	cEnviroment();

public:

	/**
	 * destructor
	 */
	virtual ~cEnviroment();

	/**
	 * The type of individuals on which the enviroment will run.
	 */
	const std::string OPERATION_DOMAIN;

	/**
	 * This method returns a pointer to an instance of the enviroment/
	 * genetic algorithm, if the parameters are set.
	 *
	 * @see setParameter()
	 * @return pointer to an instance of the enviroment/
	 * 	genetic algorithm, if the parameters are set, else NULL
	 */
	static cEnviroment * getInstance();
	
	/**
	 * This method sets the parameters for the enviroment.
	 * You can't create an instance of the enviroment, if the parameters
	 * aren't set correctly.
	 * All parameters are copied for the use in the enviroment.
	 *
	 * @see bParameterSet
	 * @see getInstance()
	 * @param pInInit A pointer to the object for initializing the
	 * 	enviroment. If NULL the initializing object isn't changed.
	 * 	@see pInitEnviroment
	 * @param pInObjectFitnessAlgorithm A pointer to the object for
	 * 	evaluing the fitness of individuals (respectively the objects
	 * 	they represents). If NULL the object for evaluing the fitnes isn't
	 * 	changed. Make sure this object /algorithm has an original
	 * 	individual set, else setParameter() will return false.
	 * 	@see pObjectFitnessAlgorithm
	 * @param pInEndCondition A pointer to the object for checking the
	 * 	endcondition of the enviroment. If Null (standardvalue)
	 * 	and no object for checking the endcondition exists an
	 * 	cEndConditionCheck object is taken to be the endcondition, else,
	 * 	if an object for checking the endcondition exists, it isn't changed.
	 * 	@see pEndCondition and @see cEndConditionCheck
	 * @param pInIndividualSelection A pointer to the object for selecting
	 * 	a good individual. If Null (standardvalue) and no object for
	 * 	selecting a good individual exists an
	 * 	@see pInIndividualSelectionWeel object is taken for selection,
	 * 	else, if an object for selecting a good individual exists, it
	 * 	isn't changed.
	 * 	@see pIndividualSelection
	 * @param pInMaximumIndividuals A pointer to the object for checking if
	 * 	individuals needs to be deleted befor adding new individuals.
	 * 	If Null (standardvalue) and no object for checking the maximal
	 * 	individuals exists an @see cMaximumReached object is taken for
	 * 	checking if the maximum number of individuals wher reached, else,
	 * 	if an object for checking the maximum number of individuals
	 * 	exists, it isn't changed.
	 * 	@see pMaximumIndividuals
	 * @param pInSelectIndividualToDelete A pointer to the object for
	 * 	selecting a bad individual. If Null (standardvalue) and no object
	 * 	for selecting a bad individual exists an
	 * 	@see cSelectIndividualToDeleteWeel object is taken for selection,
	 * 	else, if an object for selecting a bad individual exists, it
	 * 	isn't changed.
	 * 	@see pSelectIndividualToDelete
	 * @param pInOperationFitnessAlgorithmus A pointer to the object for
	 * 	evaluing the fitness of operators of the enviroment and for
	 * 	handling them. If Null (standardvalue) and no object
	 * 	for evaluing the fitness of operators exists an
	 * 	@see cOperatorFitnessAlgorithmBasic object is taken for handling
	 * 	the operators, else, if an object for evaluing the fitness of
	 * 	the operators exists, it isn't changed.
	 * 	@see pOperationFitnessAlgorithmus
	 * @param pInChoosOperator A pointer to the object for selecting a good
	 * 	operator. If Null (standardvalue) and no object for selecting a
	 * 	good operator exists an @see cChoosOperator object is taken for
	 * 	for selecting an operator, else, if an object for choosing good
	 * 	operator exists, it isn't changed.
	 * 	@see pChoosOperator
	 * @param pInResourceCheck A pointer to the object for checking if more
	 * 	operators could be started. If Null (standardvalue) and no object
	 * 	for checking if more operators could be started exists an
	 * 	@see cResourceCheck object is taken for the check, else, if an
	 * 	object for checking if more operators could be started exists, it
	 * 	isn't changed.
	 * 	@see pResourceCheck
	 * @return if all parameter could be set true, else false;
	 * 	if true was returned, @see getInstance() will return a enviroment
	 * 	instance, elso it will return NULL
	 */
	static bool setParameter( const cInitEnviroment * pInInit,
			const cObjectFitnessAlgorithm * pInObjectFitnessAlgorithm,
			const cEndConditionCheck * pInEndCondition = NULL ,
			const cIndividualSelection * pInIndividualSelection = NULL,
			const cMaximumReached * pInMaximumIndividuals = NULL,
			const cSelectIndividualToDelete * pInSelectIndividualToDelete = NULL,
			const cOperatorFitnessAlgorithm * pInOperationFitnessAlgorithmus = NULL,
			const cChoosOperator * pInChoosOperator = NULL,
			const cResourceCheck * pInResourceCheck = NULL );

	/**
	 * This method starts the enviroment and returns, without waiting
	 * that the enviroment halts.
	 * The method run() will do the work of the enviroment. So overwrite
	 * the method run() if you wan't to change the behavour of the
	 * enviroment and not this method.
	 *
	 * @see run()
	 * @see stop()
	 * @see isRunning()
	 * @return true if the enviroment was started, else false
	 */
	bool start();
	
	/**
	 * This method runs the enviroment.
	 * It will wait till the enviroment is ended befor returning.
	 * This method will do the work of the enviroment.
	 *
	 * @see start()
	 * @see stop()
	 * @see setIsRunning()
	 * @return true if the operation was started
	 */
	virtual bool run();

	/**
	 * This method stops the enviroment and returns when it halted.
	 *
	 * @see run()
	 * @see start()
	 * @see isRunning()
	 * @return true if the enviroment was stoped, else false
	 */
	virtual bool stop();
	
	/**
	 * @see start()
	 * @see stop()
	 * @return true if the enviroment is running, else false
	 */
	virtual bool isRunning() const;
	
	/**
	 * @see lAlgorithmIdentifier
	 * @return The identifier for the enviroment/ genetic algorithm.
	 */
	unsigned long long getAlgorithmIdentifier();

	/**
	 * This method returns the information about individuals in the enviroment.
	 *
	 * @param iLive a number which indicate of which kind the individuals
	 * 	should be, from which the information is to be returned;
	 * 	possible values:
	 * 		0 : return the informations of all individuals in the
	 * 			enviroment, regardless if they are living or not
	 * 		1 : return the information just of living individuals
	 * 		-1: return the information just of dead individuals
	 * 		else: an empty list is to be returned; reserved for future
	 * 		use, please don't use this
	 * @return a list with pointers to the information about the individuals
	 */
	list<const cIndividualInfo*> getIndividualInfos( short iLive = 0 ) const;
	
	/**
	 * This method returns the information for the individual with the
	 * given identifier.
	 *
	 * @param identifier the identifier for the individual, for which the
	 * 	information is to be returned
	 * @return a pointer to the information for the individual with the
	 * 	given identifier or NULL, if non exists
	 */
	const cIndividualInfo * getIndividualInfo(
		const cIndividualIdentifier & identifier ) const;
	
	/**
	 * This method returns the information for the lNumber'th best
	 * individual.
	 *
	 * @param lNumber the number of the individual to return
	 * @param iLive a number which indicate of which kind the individual
	 * 	should be, from which the information is to be returned;
	 * 	possible values:
	 * 		0 : search the informations of all individuals in the
	 * 			enviroment, regardless if they are living or not
	 * 		1 : search return the information just of living individuals
	 * 		-1: search return the information just of dead individuals
	 * 		else: an empty list is to be returned; reserved for future
	 * 		use, please don't use this
	 * @return a pointer to the information for the lNumber'th best
	 * 	individual or NULL, if non such exists
	 */
	const cIndividualInfo * getBestIndividualInfo( unsigned long lNumber = 1,
		short iLive = 1 ) const;
	
	/**
	 * This method returns a good individual from the enviroment.
	 * The selection is done by the @see pIndividualSelection object.
	 * Beware: You have to care for, that the returned individual gets
	 * deleted after usage.
	 *
	 * @see pIndividualSelection
	 * @see cIndividualSelection
	 * @return a pointer to a good individual
	 */
	cIndividual * getIndividual() const;
	
	/**
	 * This method returns the the individual with the given identifier.
	 * Beware: You have to care for, that the returned individual gets
	 * deleted after usage.
	 *
	 * @param identifier the identifier for the individual which is to be returned
	 * @return a pointer to the individual with the given identifier or
	 * 	NULL, if non exists
	 */
	cIndividual * getIndividual( const cIndividualIdentifier & identifier ) const;
	
	/**
	 * This method returns the lNumber'th best individual.
	 * Beware: You have to care for, that the returned individual gets
	 * deleted after usage.
	 *
	 * @param lNumber the number for the individual to return
	 * @return a pointer to the lNumber'th best individual or NULL, if non
	 * 	such exists
	 */
	cIndividual * getBestIndividual( unsigned long lNumber = 1 ) const;
	
	/**
	 * @return A pointer to the object for evaluing the fitness of
	 * 	individuals (respectively the objects they represents).
	 * @see pObjectFitnessAlgorithm
	 */
	static const cObjectFitnessAlgorithm * getFitnessAlgorithm();
	
	/**
	 * This method inserts a copy of the given living individual into the
	 * enviroment.
	 * The type of the individual has to be correct for this enviroment and
	 * the individual has to be correct for inserting.
	 *
	 * @param pInIndividual a pointer to the individual to insert
	 * @param pProducerOperation the operation which produced the individual,
	 * 	if NULL (standardvalue) no operation gets credit for creating the
	 * 	individual
	 * @return true if the individual was inserted, else false
	 */
	bool insertIndividual( const cIndividual * pInIndividual,
		const cOperation * pProducerOperation = NULL );
	
	/**
	 * This method returns the number of individuals in the enviroment.
	 *
	 * @param iLive a number which indicate of which kind the individuals
	 * 	should be, which are counted;
	 * 	possible values:
	 * 		0 : return the count of all individuals in the enviroment,
	 * 			regardless if they are living or not
	 * 		1 : return the count just of living individuals
	 * 		-1: return the count just of dead individuals
	 * 		else: 0 is to be returned; reserved for future use, please
	 * 			don't use this
	 * @return the count of the individuals of the given type
	 */
	unsigned long getNumberOfIndividuals( short iLive = 1 );


/*the following methods are not for the operations, but for the help
classes/ objects of the enviroment (e.g. cMaximumReached)*/
	
	/**
	 * @return the number of operations, which run at the time
	 */
	unsigned int getNumberOfRunningOperations();
	
	/**
	 * @return the number of operations executed /called by the enviroment
	 * @see lNumberOfCalledOperations
	 */
	unsigned long getNumberOfCalledOperations();
	
	/**
	 * @return the time in secounds the enviroment was running;
	 * 	@see isRunning() gives back true for this time
	 */
	double getCpuRunTime() const;
	
	/**
	 * @return the time the @see start() method was called the last time
	 * 	or 0, if non such exists
	 */
	time_t getLastStartTime() const;
	
	/**
	 * @return the time the @see start() method was called the first time
	 * 	for this enviroment or 0, if non such exists
	 */
	time_t getFirstStartTime() const;
	
	
	/**
	 * @return a pointer to the object for initializing the enviroment
	 * 	or NULL, if non such exists; @see pInitEnviroment
	 */
	static const cInitEnviroment * getInitEnviroment();

	/**
	 * @return a pointer to the object for checking the endcondition of
	 * 	the enviroment or NULL, if non such exists; @see pEndCondition
	 */
	static const cEndConditionCheck * getEndConditionCheck();
	
	/**
	 * @return a pointer to the object for selecting a good individual or
	 * 	NULL, if non such exists; @see pIndividualSelection
	 */
	static const cIndividualSelection * getIndividualSelection();
	
	/**
	 * @return a pointer to the object for checking if individuals needs to
	 * 	be deleted befor adding new individuals or NULL, if non such
	 * 	exists; @see pMaximumIndividuals
	 */
	static const cMaximumReached * getMaximumReached();
	
	/**
	 * @return a pointer to the object for selecting a bad individual or
	 * 	NULL, if non such exists; @see pSelectIndividualToDelete
	 */
	static const cSelectIndividualToDelete * getSelectIndividualToDelete();

	/**
	 * @return a pointer to the object for evaluing the fitness of
	 * 	operators of the enviroment and for handling them or NULL, if non
	 * 	such exists; @see pOperationFitnessAlgorithmus
	 */
	static cOperatorFitnessAlgorithm * getOperatorFitnessAlgorithm();
	
	/**
	 * @return a pointer to the object for selecting a good operator or
	 * 	NULL, if non such exists; @see pChoosOperator
	 */
	static const cChoosOperator * getChoosOperator();
	

	/**
	 * @return a pointer to the object for checking if more operators could
	 * 	be started or NULL, if non such exists; @see pResourceCheck
	 */
	static const cResourceCheck * getResourceCheck();


	/**
	 * This method adds the given individual listener object to the set
	 * of individual listener objects. Listeners of the set gets notified
	 * if new indeviduals wher inserted into the enviroment or old wher
	 * deleted.
	 *
	 * @see unregisterIndividualListener()
	 * @see setIndividualListener
	 * @see clNewIndividualListener
	 * @param individualListener a pointer to the individual listener
	 * 	object to add to the set of individual listeners
	 * @return true if the individual listener was added, else false
	 */
	bool registerIndividualListener( clNewIndividualListener * individualListener );
	
	/**
	 * This method removes the given individual listener object from the set
	 * of individual listener objects. Listeners of the set gets notified
	 * if new indeviduals wher inserted into the enviroment or old wher
	 * deleted.
	 *
	 * @see registerIndividualListener()
	 * @see setIndividualListener
	 * @see clNewIndividualListener
	 * @param individualListener a pointer to the individual listener
	 * 	object to removes from the set of individual listeners
	 * @return true if the individual listener was removed, else false
	 */
	bool unregisterIndividualListener( clNewIndividualListener * individualListener );

	/**
	 * This method is called, if the running status of the operation is changed.
	 *
	 * @see cOperation::bIsRunning
	 * @see cOperation::isRunning()
	 * @param pOperation a pointer to the operation, which status has changed
	 * @param isRunning the new running status for the operation
	 */
	void operationStatusChange( cOperation * pOperation, bool isRunning );

#ifndef TEST
protected:
#endif
	/**
	 * This method removes the given individual from the enviroment and
	 * delets it.
	 *
	 * @param pInIndividual a pointer to the individual to delete
	 * @return true if the given individual was deleted, else false
	 */
	bool removeIndividual( const cIndividualIdentifier pInIndividual );


private:

	/**
	 * This method stop the operation for a tread.
	 * It will wait till the operation is stoped befor returning.
	 *
	 * @see stop()
	 * @param inputArg a pointer to the operation to stop
	 */
	static void * stopOperation( void * inputArg );
	
	/**
	 * This method will delete all operations which are done (respectively
	 * stored in the @see liOperationsToDelete ).
	 */
	void deleteNotRunningOperations();

	/**
	 * This method runs the enviroment for a tread.
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

};//end class cEnviroment


};//end namespace enviroment

#endif //___C_ENVIROMENT_H__







