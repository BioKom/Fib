/**
 * @file cEnviroment
 * file name: cEnviroment.cpp
 * @author Betti Oesterholz
 * @date 28.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements a class for the enviroment.
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
 * This file implements a class for the enviroment.
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
 *
 */
/*
History:
28.03.2010  Oesterholz  created
15.03.2012  Oesterholz  changes for windows compatibility
*/

//TODO weg
//#define DEBUG

//prints a message every secound for all operations which run longer than 3 minutes
//#define DEBUG_OPERATION_LONG_TIME

/*with this switch the operations will be run and not started;
in this way they are not running as treads and don't confuse ddd*/
//#define DEBUG_RUN_OPERATIONS

//the start method won't start a new tread, but call run() directly
//#define DEBUG_START_WITOUT_TREAD


#include "cEnviroment.h"


#include "cInitEnviroment.h"
#include "cObjectFitness.h"
#include "cObjectFitnessAlgorithm.h"
#include "cEndConditionCheck.h"
#include "cResourceCheck.h"
#include "cIndividualSelection.h"
#include "cIndividualSelectionWeel.h"
#include "cMaximumReached.h"
#include "cSelectIndividualToDelete.h"
#include "cSelectIndividualToDeleteWeel.h"
#include "cOperatorFitnessAlgorithm.h"
#include "cOperatorFitnessAlgorithmBasic.h"
#include "cChoosOperator.h"

#include <utility>
#include <algorithm>
#include <pthread.h>


using namespace std;
using namespace enviroment;


namespace enviroment{

#ifdef WINDOWS
static HANDLE mutexIndividuals = CreateMutex( 
	NULL,	// default security attributes
	FALSE,	// initially not owned
	NULL);	// unnamed mutex
static HANDLE mutexOperationsRunning = CreateMutex( NULL, FALSE, NULL);
static HANDLE mutexOperationsRunningToDelete = CreateMutex( NULL, FALSE, NULL);
static HANDLE mutexDeleteOperation = CreateMutex( NULL, FALSE, NULL);
static HANDLE mutexIndividualListeners = CreateMutex( NULL, FALSE, NULL);
#else //WINDOWS
static pthread_mutex_t mutexIndividuals = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutexOperationsRunning = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutexOperationsRunningToDelete = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutexDeleteOperation = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutexIndividualListeners = PTHREAD_MUTEX_INITIALIZER;
#endif //WINDOWS



/**
 * Internal class for a better individual handling.
 */
class cIndividualInformation{
public:
	
	/**
	 * A pointer to the individual.
	 */
	cIndividual * pIndividual;
	
	/**
	 * constructor
	 *
	 * @param pInIndividual a point to the individual (@see pIndividual)
	 */
	cIndividualInformation( cIndividual * pInIndividual):
			pIndividual( pInIndividual ){
		//nothing to do
	}
	
	/**
	 * desstructor
	 */
	~cIndividualInformation(){
		
/*don't delete the individual hear; this object isn't respnsible for it,
but the enviroment destructor is
		if ( pIndividual ){
			delete pIndividual;
		}
		pIndividual = NULL;
*/
	}

};



/**
 * Internal class for handling the operation information.
 */
class cOperationInformation{
public:
	
	/**
	 * The time the operation was started.
	 */
	time_t startTime;
	
	/**
	 * A list with the individuals the operation has created.
	 */
	list<cIndividualInfo> liCreatedIndividuals;
	
	/**
	 * constructor
	 */
	cOperationInformation():
		startTime( time( 0 ) ){
		//nothing to do
	}
	
};



/**
 * This function evalues the uniqe identifier for the enviroment.
 *
 * @return the identifier for the enviroment.
 */
long long evalueAlgorithmIdentifier(){
	//TODO computer number * time * process ?
	static long long lIdentifier = 0;
	lIdentifier++;
	return lIdentifier;
}


/**
 * The identifier for the enviroment/ genetic algorithm.
 * It should be unique for every enviroment, even on different computers.
 */
long long cEnviroment::lAlgorithmIdentifier = evalueAlgorithmIdentifier();

/**
 * A pointer to the enviroment instance.
 */
cEnviroment * cEnviroment::pEnviroment = NULL;

/**
 * The tread for running the enviroment.
 * @see start()
 * @see stop()
 * @see run()
 */
#ifdef WINDOWS
HANDLE cEnviroment::pThreadEnviroment = NULL;
#else //WINDOWS
pthread_t * cEnviroment::pThreadEnviroment = NULL;
#endif //WINDOWS


/**
 * This functions compares the fitness values of the given individualinfos
 * and returns true if the first individualfitness is higher /better
 * than the second, else false.
 * If one individual has no fitness, it is lower. If both individuals have
 * no fitness, the identifier of the individuals are compared with lower.
 * If both fitness values are equal, the identifier of the individuals are
 * compared with lower.
 * If both individuals have no fitness and identifiers ther pointers are
 * compared with lower.
 *
 * @param pIndividual1 a pointer to the first individualinfo to compare with
 * @param pIndividual2 a pointer to the second individualinfo to compare with
 * @return true if the fitnessvalue for pIndividual1 is greater than for
 * 	pIndividual2, else false
 */
bool compIndividualFitness( const cIndividualInfo * pIndividual1,
		const cIndividualInfo * pIndividual2 ){
	
	if ( (pIndividual1 == NULL) || (pIndividual2 == NULL) ){
		return (pIndividual1 < pIndividual2);
	}
	const cObjectFitness * pFitness1 = pIndividual1->getFitness();
	const cObjectFitness * pFitness2 = pIndividual2->getFitness();
	
	const cIndividualIdentifier id1 = pIndividual1->getIdentifier();
	const cIndividualIdentifier id2 = pIndividual2->getIdentifier();
	
	if ( (pFitness1 == NULL) || (pFitness2 == NULL) ){
		
		if ( (pFitness1 == NULL) && (pFitness2 != NULL) ){
			//pIndividual1 is lower -> pIndividual2 is higher
			return false;
		}//else
		if ( (pFitness1 != NULL) && (pFitness2 == NULL) ){
			//pIndividual2 is lower -> pIndividual1 is higher
			return true;
		}//else (pIndividual1->getFitness() == NULL) && (pIndividual2->getFitness() == NULL)
		return (id1 < id2);
	}
	const double dFitness1 = pFitness1->getFitness();
	const double dFitness2 = pFitness2->getFitness();
	if ( dFitness1 == dFitness2 ){
		return (id1 < id2);
	}
	return (dFitness2 < dFitness1);
}


/**
 * The container for the living individuals in the enviroment.
 * This field is for better internal handling of individuals.
 *
 * initialize with: mapLivingIndividuals( compIndividualFitness )
 */
map<cIndividualIdentifier, cIndividualInformation >
	cEnviroment::mapLivingIndividuals;

/**
 * A list with pointers to the informations of the living individuals
 * in the enviroment.
 */
list<const cIndividualInfo*> cEnviroment::liLivingIndividualInfos;

/**
 * If true the list with the living individuals is sorted, else not.
 */
bool cEnviroment::bLiLivingIndividualInfosSorted = true;

/**
 * The container for the dead individuals in the enviroment.
 * This field is for better internal handling of individuals.
 *
 * initialize with: mapDeadIndividuals( compIndividualFitness )
 */
map< cIndividualIdentifier, cIndividualInformation >
		cEnviroment::mapDeadIndividuals;

/**
 * A list with pointers to the informations of the dead individuals
 * in the enviroment.
 */
list<const cIndividualInfo*> cEnviroment::liDeadIndividualInfos;

/**
 * If true the list with the living individuals is sorted, else not.
 */
bool cEnviroment::bLiDeadIndividualInfosSorted = true;

/**
 * A map with the information for the running operations and the information
 * for them.
 */
map< cOperation * , cOperationInformation > cEnviroment::mapRunningOperations;

/**
 * A list with the operations which are done and can be deleted.
 */
list<cOperation*> cEnviroment::liOperationsToDelete;

/**
 * The number of operations executed/ called by the enviroment.
 */
unsigned long long cEnviroment::lNumberOfCalledOperations = 0;


/**
 * The time in secounds the enviroment was running.
 * (@see isRunning() gives back true for this time)
 */
double cEnviroment::dCpuRunTime = 0.0;

/**
 * The time the the cpu time was evalued the last time.
 * This variable is for evaluing the cpu time while the enviroemnt runs.
 */
time_t cEnviroment::tmLastCpuRunTime = 0;

/**
 * The time the @see start() method was called the last time.
 */
time_t cEnviroment::tmLastStartTime = 0;

/**
 * The time the @see start() method was called the first time for this
 * enviroment instance.
 */
time_t cEnviroment::tmFirstStartTime = 0;


/**
 * If true the parameter for the enviroment are set, else not.
 */
bool cEnviroment::bParameterSet = false;

/**
 * If true the the enviroment is running, else not.
 */
bool cEnviroment::bIsRunning = false;

/**
 * If true the enviroment should be stoped, else not.
 */
bool cEnviroment::bStopFlag = false;;


/**
 * A pointer to the object for initializing the enviroment.
 */
cInitEnviroment * cEnviroment::pInitEnviroment = NULL;

/**
 * A pointer to the object for evaluing the fitness of individuals
 * respectively the objects they represents.
 */
cObjectFitnessAlgorithm * cEnviroment::pObjectFitnessAlgorithm = NULL;

/**
 * A pointer to the object for checking the endcondition of the
 * enviroment.
 */
cEndConditionCheck * cEnviroment::pEndCondition = NULL;

/**
 * A pointer to the object for selecting a good individual.
 */
cIndividualSelection * cEnviroment::pIndividualSelection = NULL;

/**
 * A pointer to the object for checking if individuals needs to
 * be deleted befor adding new individuals.
 */
cMaximumReached * cEnviroment::pMaximumIndividuals = NULL;

/**
 * A pointer to the object for selecting a bad individual.
 */
cSelectIndividualToDelete * cEnviroment::pSelectIndividualToDelete = NULL;

/**
 * A pointer to the object for evaluing the fitness of operators of
 * the enviroment and for handling them.
 */
cOperatorFitnessAlgorithm * cEnviroment::pOperationFitnessAlgorithmus = NULL;

/**
 * A pointer to the object for selecting a good operator.
 */
cChoosOperator * cEnviroment::pChoosOperator = NULL;

/**
 * A pointer to the object for checking, if more operators could be
 * started.
 */
cResourceCheck * cEnviroment::pResourceCheck = NULL;

/**
 * This set contains pointers to all objects, which want's to be
 * notified, if new indeviduals wher inserted into the enviroment or old
 * wher deleted.
 * @see clNewIndividualListener
 */
set<clNewIndividualListener *> cEnviroment::setIndividualListener;

};//namespace enviroment

/**
 * standardconstructor
 * This is called in the getInstance() method.
 */
cEnviroment::cEnviroment():
		OPERATION_DOMAIN( pObjectFitnessAlgorithm->getOriginalIndividual()->getClassName() ){
	
#ifdef WINDOWS
	//close mutex handles
	if ( mutexIndividuals == NULL ){
		mutexIndividuals = CreateMutex( NULL, FALSE, NULL);
	}
	if ( mutexOperationsRunning == NULL ){
		mutexOperationsRunning = CreateMutex( NULL, FALSE, NULL);
	}
	if ( mutexOperationsRunningToDelete == NULL ){
		mutexOperationsRunningToDelete = CreateMutex( NULL, FALSE, NULL);
	}
	if ( mutexDeleteOperation == NULL ){
		mutexDeleteOperation = CreateMutex( NULL, FALSE, NULL);
	}
	if ( mutexIndividualListeners == NULL ){
		mutexIndividualListeners = CreateMutex( NULL, FALSE, NULL);
	}
#endif //WINDOWS
	DEBUG_OUT_L1(<<"constructing the enviroment "<<endl<<flush);
}


/**
 * destructor
 */
cEnviroment::~cEnviroment(){
	
	DEBUG_OUT_L1(<<"~cEnviroment(): destroying the enviroment"<<endl<<flush);
	
	//stop the enviroment
	stop();
	
	if ( pThreadEnviroment != NULL ){
		//wait till tread is done and join it with this tread
#ifdef WINDOWS
		WaitForMultipleObjects( 1, &pThreadEnviroment, TRUE, INFINITE );
		//close thread handles
		CloseHandle( pThreadEnviroment );
#else //WINDOWS
		pthread_join( *pThreadEnviroment, NULL );
		delete pThreadEnviroment;
#endif //WINDOWS
		pThreadEnviroment = NULL;
	}

	pthread_mutex_lock( & mutexIndividuals );
	//destroy the individuals of the enviroment
	for ( map<cIndividualIdentifier, cIndividualInformation >::iterator
			itrIndividual = mapLivingIndividuals.begin();
			itrIndividual != mapLivingIndividuals.end(); itrIndividual++ ){
		
		if ( itrIndividual->second.pIndividual ){
			delete itrIndividual->second.pIndividual;
		}
	}
	mapLivingIndividuals.clear();
	liLivingIndividualInfos.clear();
	bLiLivingIndividualInfosSorted = true;
	
	for ( map<cIndividualIdentifier, cIndividualInformation >::iterator
			itrIndividual = mapDeadIndividuals.begin();
			itrIndividual != mapDeadIndividuals.end(); itrIndividual++ ){
		
		if ( itrIndividual->second.pIndividual ){
			delete itrIndividual->second.pIndividual;
		}
	}
	mapDeadIndividuals.clear();
	liDeadIndividualInfos.clear();
	bLiDeadIndividualInfosSorted = true;
	
	pthread_mutex_unlock( & mutexIndividuals );
	
	lNumberOfCalledOperations = 0;
	dCpuRunTime = 0.0;
	tmLastStartTime  = 0;
	tmFirstStartTime = 0;
	bParameterSet = false;
	bIsRunning = false;

	//destroy the parameter objects
	if ( pInitEnviroment != NULL ){
		delete pInitEnviroment;
		pInitEnviroment = NULL;
	}
	if ( pObjectFitnessAlgorithm != NULL ){
		delete pObjectFitnessAlgorithm;
		pObjectFitnessAlgorithm = NULL;
	}
	if ( pEndCondition != NULL ){
		delete pEndCondition;
		pEndCondition = NULL;
	}
	if ( pIndividualSelection != NULL ){
		delete pIndividualSelection;
		pIndividualSelection = NULL;
	}
	if ( pMaximumIndividuals != NULL ){
		delete pMaximumIndividuals;
		pMaximumIndividuals = NULL;
	}
	if ( pSelectIndividualToDelete != NULL ){
		delete pSelectIndividualToDelete;
		pSelectIndividualToDelete = NULL;
	}
	if ( pOperationFitnessAlgorithmus != NULL ){
		delete pOperationFitnessAlgorithmus;
		pOperationFitnessAlgorithmus = NULL;
	}
	if ( pChoosOperator != NULL ){
		delete pChoosOperator;
		pChoosOperator = NULL;
	}
	if ( pMaximumIndividuals != NULL ){
		delete pMaximumIndividuals;
		pMaximumIndividuals = NULL;
	}
	if ( pResourceCheck != NULL ){
		delete pResourceCheck;
		pResourceCheck = NULL;
	}
	
	pthread_mutex_lock( & mutexIndividualListeners );
	setIndividualListener.clear();
	pthread_mutex_unlock( & mutexIndividualListeners );
	
	pEnviroment = NULL;
	lAlgorithmIdentifier = evalueAlgorithmIdentifier();
	
	
#ifdef WINDOWS
	//close mutex handles
	CloseHandle( mutexIndividuals );
	mutexIndividuals = NULL;
	CloseHandle( mutexOperationsRunning );
	mutexOperationsRunning = NULL;
	CloseHandle( mutexOperationsRunningToDelete );
	mutexOperationsRunningToDelete = NULL;
	CloseHandle( mutexDeleteOperation );
	mutexDeleteOperation = NULL;
	CloseHandle( mutexIndividualListeners );
	mutexIndividualListeners = NULL;
#endif //WINDOWS

	DEBUG_OUT_L1(<<"~cEnviroment(): destroying the enviroment done"<<endl<<flush);
}


/**
 * This method returns a pointer to an instance of the enviroment/
 * genetic algorithm, if the parameters are set.
 *
 * @see setParameter()
 * @return pointer to an instance of the enviroment/
 * 	genetic algorithm, if the parameters are set, else NULL
 */
cEnviroment * cEnviroment::getInstance(){
	
//	DEBUG_OUT_L4(<<"cEnviroment::getInstance()"<<endl<<flush);
	
	if ( pEnviroment != NULL ){
		return pEnviroment;
	}
	if ( bParameterSet ){
		pEnviroment = new cEnviroment();
		return pEnviroment;
	}
	return NULL;
}


/**
 * This method sets the parameters for the enviroment.
 * You can't create an instance of the enviroment, if the parameters
 * aren't set correctly.
 * All parameters are copied for the use in the enviroment.
 * You can't set the parameters if the enviroment is running.
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
 * 	@see cIndividualSelectionWeel object is taken for selection,
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
 * 	instance; if the parameters couldn't be set getInstance() will
 * 	return NULL
 */
bool cEnviroment::setParameter( const cInitEnviroment * pInInit,
		const cObjectFitnessAlgorithm * pInObjectFitnessAlgorithm,
		const cEndConditionCheck * pInEndCondition,
		const cIndividualSelection * pInIndividualSelection,
		const cMaximumReached * pInMaximumIndividuals,
		const cSelectIndividualToDelete * pInSelectIndividualToDelete,
		const cOperatorFitnessAlgorithm * pInOperationFitnessAlgorithmus,
		const cChoosOperator * pInChoosOperator,
		const cResourceCheck * pInResourceCheck ){
	
	DEBUG_OUT_L2(<<"cEnviroment::setParameter()"<<endl<<flush);
	
	cEnviroment * pEnviroment = getInstance();
	if ( (pEnviroment != NULL) && ( pEnviroment->isRunning() ) ){
		//can't set parameters while the enviroment is running
		DEBUG_OUT_L2(<<"cEnviroment::setParameter() done can't set"<<endl<<flush);
		return false;
	}
	//set the object for initializing the enviroment
	if ( pInInit != NULL ){
		if ( pInitEnviroment != NULL ){
			delete pInitEnviroment;
		}
		pInitEnviroment = pInInit->clone();
	}
	//set the object for evaluing the fitness of individuals
	bool bErrorInObjectFitnessAlgorithm = false;
	if ( pInObjectFitnessAlgorithm != NULL ){
		
		if ( pInObjectFitnessAlgorithm->getOriginalIndividual() != NULL ){
			
			if ( pEnviroment != NULL ){
				if ( pEnviroment->OPERATION_DOMAIN != pInObjectFitnessAlgorithm->
						getOriginalIndividual()->getClassName() ){
					bErrorInObjectFitnessAlgorithm = true;
				}
			}
			if ( ! bErrorInObjectFitnessAlgorithm ){
				if ( pObjectFitnessAlgorithm != NULL ){
					delete pObjectFitnessAlgorithm;
				}
				pObjectFitnessAlgorithm = pInObjectFitnessAlgorithm->clone();
			}
		}else{//no original individual
			bErrorInObjectFitnessAlgorithm = true;
		}
	}
	//set the object for checking the endcondition
	if ( pInEndCondition != NULL ){
		if ( pEndCondition != NULL ){
			delete pEndCondition;
		}
		pEndCondition = pInEndCondition->clone();
	}else{
		if ( pEndCondition == NULL ){
			//both are NULL
			pEndCondition = new cEndConditionCheck();
		}
	}
	//set the object for checking the endcondition
	if ( pInIndividualSelection != NULL ){
		if ( pIndividualSelection != NULL ){
			delete pIndividualSelection;
		}
		pIndividualSelection = pInIndividualSelection->clone();
	}else{
		if ( pIndividualSelection == NULL ){
			//both are NULL
			pIndividualSelection = new cIndividualSelectionWeel();
		}
	}
	/*set the object for checking if individuals needs to be deleted befor
	adding new individuals*/
	if ( pInMaximumIndividuals != NULL ){
		if ( pMaximumIndividuals != NULL ){
			delete pMaximumIndividuals;
		}
		pMaximumIndividuals = pInMaximumIndividuals->clone();
	}else{
		if ( pMaximumIndividuals == NULL ){
			//both are NULL
			pMaximumIndividuals = new cMaximumReached();
		}
	}
	//set the object for selecting a bad individual
	if ( pInSelectIndividualToDelete != NULL ){
		if ( pSelectIndividualToDelete != NULL ){
			delete pSelectIndividualToDelete;
		}
		pSelectIndividualToDelete = pInSelectIndividualToDelete->clone();
	}else{
		if ( pSelectIndividualToDelete == NULL ){
			//both are NULL
			pSelectIndividualToDelete = new cSelectIndividualToDeleteWeel();
		}
	}
	//set the object for evaluing the fitness of operators of the enviroment
	if ( pInOperationFitnessAlgorithmus != NULL ){
		if ( pOperationFitnessAlgorithmus != NULL ){
			delete pOperationFitnessAlgorithmus;
		}
		pOperationFitnessAlgorithmus = pInOperationFitnessAlgorithmus->clone();
	}else{
		if ( pOperationFitnessAlgorithmus == NULL ){
			//both are NULL
			pOperationFitnessAlgorithmus = new cOperatorFitnessAlgorithmBasic();
		}
	}
	//set the object for selecting a good operator
	if ( pInChoosOperator != NULL ){
		if ( pChoosOperator != NULL ){
			delete pChoosOperator;
		}
		pChoosOperator = pInChoosOperator->clone();
	}else{
		if ( pChoosOperator == NULL ){
			//both are NULL
			pChoosOperator = new cChoosOperator();
		}
	}
	//set the object for checking if more operators could be started
	if ( pInResourceCheck != NULL ){
		if ( pResourceCheck != NULL ){
			delete pResourceCheck;
		}
		pResourceCheck = pInResourceCheck->clone();
	}else{
		if ( pResourceCheck == NULL ){
			//both are NULL
			pResourceCheck = new cResourceCheck();
		}
	}

	//check if all parameters are set
	bParameterSet = true;
	if ( (pInitEnviroment == NULL) || (pObjectFitnessAlgorithm == NULL) ||
			(pEndCondition == NULL) || (pIndividualSelection == NULL) ||
			(pMaximumIndividuals == NULL) || (pSelectIndividualToDelete == NULL) ||
			(pOperationFitnessAlgorithmus == NULL) ||
			(pChoosOperator == NULL) || (pResourceCheck == NULL) ){
		//one parameter is not given
		bParameterSet = false;
	}
	if ( bErrorInObjectFitnessAlgorithm ){
		bParameterSet = false;
	}
	DEBUG_OUT_L2(<<"cEnviroment::setParameter() done = "<<(bParameterSet?("true"):("false"))<<endl<<flush );
	return bParameterSet;
}


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
bool cEnviroment::start(){
	
	if ( isRunning() || bStopFlag || ( ! bParameterSet ) ||
			(pThreadEnviroment != NULL) ){
		//the enviroment runs allready
		return false;
	}
	DEBUG_OUT_L2(<<"cEnviroment::start() started"<<endl<<flush);
	//run the enviroment in a seperate tread
#ifndef DEBUG_START_WITOUT_TREAD

#ifdef WINDOWS
	DWORD   dwThreadId = 0;
	pThreadEnviroment = CreateThread( 
		NULL, //default security attributes
		0, //use default stack size  
		(LPTHREAD_START_ROUTINE)&(cEnviroment::runTread), //thread function name
		this, //argument to thread function 
		0, //use default creation flags 
		&dwThreadId ); //returns the thread identifier 
	
	const int iReturn = ( pThreadEnviroment == NULL ) ? 1 : 0 ;
#else //WINDOWS
	pThreadEnviroment = new pthread_t();
	const int iReturn = pthread_create( pThreadEnviroment, NULL, &(cEnviroment::runTread), this );
#endif //WINDOWS

#else
	runTread( this );
	const int iReturn = 0;
#endif
	if ( iReturn != 0 ){
		DEBUG_OUT_L2(<<"cEnviroment::start() done tread error"<<endl<<flush);
		return false;
	}
	DEBUG_OUT_L2(<<"cEnviroment::start() done"<<endl<<flush);
	return true;
}


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
bool cEnviroment::run(){
	
	DEBUG_OUT_L2(<<"cEnviroment::run() started"<<endl<<flush);
	
	if ( isRunning() || bStopFlag ){
		return false;
	}
	bIsRunning = true;
	if ( ! bParameterSet ){
		bIsRunning = false;
		return false;
	}
	DEBUG_OUT_L2(<<"cEnviroment::run() ok"<<endl<<flush);

	if ( tmFirstStartTime == 0 ){
		tmFirstStartTime = time( NULL );
	}
	tmLastStartTime = time( NULL );
	tmLastCpuRunTime = tmLastStartTime;
	
	//initializize the enviroment
	DEBUG_OUT_L2(<<"Init enviroment"<<endl<<flush);
	pInitEnviroment->initEnviroment();
	
	//while the enviroment isn't stoped, execute operations
	while ( ( ! bStopFlag ) && ( ! pEndCondition->endConditionCheck() ) ){
		
		if( pResourceCheck->enoughResources() ){
			//if enougth recources -> start a new operation
			cOperation * pNewOperation = pChoosOperator->choosOperator();
			if ( pNewOperation ){
				pthread_mutex_lock( & mutexOperationsRunning );
				DEBUG_OUT_L2(<<"Starting new operation "<<pNewOperation<<" of type "<<pNewOperation->getName()<<endl<<flush);
				
				pNewOperation->registerOperationRunStatusListener( this );
#ifndef DEBUG_RUN_OPERATIONS
				const bool bOperationStarted = pNewOperation->start();
				if ( bOperationStarted ){
					//the operation is running -> add it to the list of running operations
					const pair< map< cOperation * , cOperationInformation >::iterator, bool >
						paOperationInserted = mapRunningOperations.insert(
							pair< cOperation * , cOperationInformation >(
								pNewOperation, cOperationInformation() ) );
					
					if ( paOperationInserted.second ){
						lNumberOfCalledOperations++;
					}else{
						pthread_mutex_lock( & mutexOperationsRunningToDelete );
						DEBUG_OUT_L2(<<"adding operation to delete "<< pNewOperation<<endl<<flush);
						liOperationsToDelete.push_back( pNewOperation );
						pthread_mutex_unlock( & mutexOperationsRunningToDelete );
					}
				}else{
					pthread_mutex_lock( & mutexOperationsRunningToDelete );
					DEBUG_OUT_L2(<<"adding operation to delete "<< pNewOperation<<endl<<flush);
					liOperationsToDelete.push_back( pNewOperation );
					pthread_mutex_unlock( & mutexOperationsRunningToDelete );
				}
				
				DEBUG_OUT_L2(<<dec<<"New operation "<<pNewOperation<<(bOperationStarted?"":" not")<<" started"<<endl<<flush);
				DEBUG_OUT_L2(<<"Operations now running: "<<mapRunningOperations.size()<<"  operations to delete: "<<liOperationsToDelete.size()<<", number of all run operations: "<< lNumberOfCalledOperations <<endl<<flush);
				pthread_mutex_unlock( & mutexOperationsRunning );
				
				if ( ! bOperationStarted ){
					//wait befor trying again
					shortSleep();
				}
#else
				pthread_mutex_unlock( & mutexOperationsRunning );
				pNewOperation->run();
				DEBUG_OUT_L2(<<"Operations to delete: "<<liOperationsToDelete.size()<<", number of all run operations: "<< lNumberOfCalledOperations <<endl<<flush);
#endif
			}
		}else{//wait befor checking, if more operations can be started
			shortSleep();
		}
		//destroy the done operations
		deleteNotRunningOperations();
	}
	
	//wait till all operations are done
	while ( getNumberOfRunningOperations() != 0 ){
		shortSleep();
	}
	//destroy the done operations
	deleteNotRunningOperations();

	//take the time this process has run
	dCpuRunTime += time( NULL ) - tmLastCpuRunTime;

	if ( pThreadEnviroment != NULL ){
		//wait till tread is done and join it with this tread
#ifdef WINDOWS
		WaitForMultipleObjects( 1, &pThreadEnviroment, TRUE, INFINITE );
		//close thread handles
		CloseHandle( pThreadEnviroment );
#else //WINDOWS
		pthread_join( *pThreadEnviroment, NULL );
		delete pThreadEnviroment;
#endif //WINDOWS
		pThreadEnviroment = NULL;
	}
	
	bIsRunning = false;
	DEBUG_OUT_L2(<<"cEnviroment::run() done"<<endl<<flush);
	return true;
}


/**
 * This method stop the operation for a tread.
 * It will wait till the operation is stoped befor returning.
 *
 * @see stop()
 * @param inputArg a pointer to the operation to stop
 */
void * cEnviroment::stopOperation( void * inputArg ){
	
	cOperation * pOperationToStop = ((cOperation*)(inputArg));
	
	pthread_mutex_lock( & mutexDeleteOperation );
	
	pthread_mutex_lock( & mutexOperationsRunning );
	map< cOperation * , cOperationInformation >::iterator
		itrOperationRunning = mapRunningOperations.find( pOperationToStop );
	if ( itrOperationRunning == mapRunningOperations.end() ){
		//operation not running anymore
		pthread_mutex_unlock( & mutexOperationsRunning );
		pthread_mutex_unlock( & mutexDeleteOperation );
		return NULL;
	}//else operation was running and was not deleted -> stop the operation
	pthread_mutex_unlock( & mutexOperationsRunning );
	
	pOperationToStop->stop();
	
	pthread_mutex_unlock( & mutexDeleteOperation );
	
	return NULL;
}


/**
 * This method stops the enviroment and returns when it halted.
 *
 * @see run()
 * @see start()
 * @see isRunning()
 * @return true if the enviroment was stoped, else false
 */
bool cEnviroment::stop(){
		
	DEBUG_OUT_L2(<<"cEnviroment::stop()"<<endl<<flush);
	
	if ( ! isRunning() ){
		DEBUG_OUT_L2(<<"cEnviroment::stop() done not running"<<endl<<flush);
		return false;
	}
	bStopFlag = true;
	//stop and destroy the running operations
	if ( getNumberOfRunningOperations() != 0 ){
		pthread_mutex_lock( & mutexOperationsRunning );
		map< cOperation * , cOperationInformation >
			mapRunningOperationsTmp = mapRunningOperations;
		pthread_mutex_unlock( & mutexOperationsRunning );
		
		for ( map< cOperation * , cOperationInformation >::iterator
				itrOperation = mapRunningOperationsTmp.begin();
				itrOperation != mapRunningOperationsTmp.end(); itrOperation++ ){
			
#ifdef WINDOWS
			DWORD   dwThreadId = 0;
			HANDLE threadStopOperation = CreateThread( 
				NULL, //default security attributes
				0, //use default stack size  
				(LPTHREAD_START_ROUTINE)&(cEnviroment::stopOperation), //thread function name
				itrOperation->first, //argument to thread function 
				0, //use default creation flags 
				&dwThreadId ); //returns the thread identifier 
			
			CloseHandle( threadStopOperation );
#else //WINDOWS
			//stop the operation in a seperate tread
			pthread_t threadStopOperation;
			pthread_create( &threadStopOperation, NULL,
				&(cEnviroment::stopOperation), itrOperation->first );
			pthread_detach( threadStopOperation );
#endif //WINDOWS
		}
	}
	//wait till the enviroment is done
	while ( isRunning() ){
		shortSleep();
	}
		
	//wait till all operations are done
	while ( getNumberOfRunningOperations() != 0 ){
		shortSleep();
	}
	//destroy the done operations
	deleteNotRunningOperations();
	
	bStopFlag = false;
	
	DEBUG_OUT_L2(<<"cEnviroment::stop() done"<<endl<<flush);
	return true;
}


/**
 * @see start()
 * @see stop()
 * @return true if the enviroment is running, else false
 */
bool cEnviroment::isRunning() const{
	
	DEBUG_OUT_L2(<<"cEnviroment::isRunning() = "<<(bIsRunning?("true"):("false"))<<endl<<flush);
	return bIsRunning;
}


/**
 * @see lAlgorithmIdentifier
 * @return The identifier for the enviroment/ genetic algorithm.
 */
unsigned long long cEnviroment::getAlgorithmIdentifier(){
	
	DEBUG_OUT_L2(<<"cEnviroment::getAlgorithmIdentifier() = "<<lAlgorithmIdentifier<<endl<<flush);
	return lAlgorithmIdentifier;
}


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
list<const cIndividualInfo*> cEnviroment::getIndividualInfos( short iLive ) const{

	DEBUG_OUT_L2(<<"cEnviroment::getIndividualInfos( iLive="<<iLive<<")"<<endl<<flush);
	
	if ( iLive == 0 ){
		list<const cIndividualInfo*> liAllIndividualInfos = liDeadIndividualInfos;
		liAllIndividualInfos.insert( liAllIndividualInfos.begin(),
			liLivingIndividualInfos.begin(), liLivingIndividualInfos.end() );
		
		DEBUG_OUT_L2(<<"cEnviroment::getIndividualInfos() done all "<<endl<<flush);
		return liAllIndividualInfos;
	}else if ( iLive == 1 ){
	
		DEBUG_OUT_L2(<<"cEnviroment::getIndividualInfos() done living "<<endl<<flush);
		return liLivingIndividualInfos;
	}//else if ( iLive == -1 ){
	
	DEBUG_OUT_L2(<<"cEnviroment::getIndividualInfos() done dead "<<endl<<flush);
	return liDeadIndividualInfos;
}


/**
 * This method returns the information for the individual with the
 * given identifier.
 *
 * @param identifier the identifier for the individual, for which the
 * 	information is to be returned
 * @return a pointer to the information for the individual with the
 * 	given identifier or NULL, if non exists
 */
const cIndividualInfo * cEnviroment::getIndividualInfo(
		const cIndividualIdentifier & identifier ) const{
	
	pthread_mutex_lock( & mutexIndividuals );
	//search in the living individuals for the identifier
	map<cIndividualIdentifier, cIndividualInformation >::iterator
		itrIndividual = mapLivingIndividuals.find( identifier );
	
	if ( itrIndividual != mapLivingIndividuals.end() ){
		//identifier found -> return it
		const cIndividualInfo * pIndInfo = itrIndividual->second.pIndividual->getInfo();
		pthread_mutex_unlock( & mutexIndividuals );
		return pIndInfo;
	}

	//search in the dead individuals for the identifier
	itrIndividual = mapDeadIndividuals.find( identifier );
	
	if ( itrIndividual != mapDeadIndividuals.end() ){
		//identifier found -> return it
		const cIndividualInfo * pIndInfo = itrIndividual->second.pIndividual->getInfo();
		pthread_mutex_unlock( & mutexIndividuals );
		return pIndInfo;
	}
	pthread_mutex_unlock( & mutexIndividuals );
	//individual info for the identifier not found
	return NULL;
}


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
const cIndividualInfo * cEnviroment::getBestIndividualInfo(
	unsigned long lNumber, short iLive  ) const{
	
	pthread_mutex_lock( & mutexIndividuals );
	const cIndividualInfo * pIndInfo = NULL;
	if ( iLive == 1 ){
		//search in the list of living individuals
		//find the correct position
		if ( ! bLiLivingIndividualInfosSorted ){
			liLivingIndividualInfos.sort( compIndividualFitness );
			bLiLivingIndividualInfosSorted = true;
		}
		list<const cIndividualInfo*>::iterator itrIndividual =
			liLivingIndividualInfos.begin();
		for ( ; (itrIndividual != liLivingIndividualInfos.end()) && ( 1 < lNumber );
				lNumber--, itrIndividual++ ){
			//nothing to do
		}
		if ( itrIndividual != liLivingIndividualInfos.end() ){
			//correct individual found
			pIndInfo = *itrIndividual;
		}
		pthread_mutex_unlock( & mutexIndividuals );
		return pIndInfo;
	}else if ( iLive == -1 ){
		//search in the list of dead individuals
		//find the correct position
		if ( ! bLiDeadIndividualInfosSorted ){
			liDeadIndividualInfos.sort( compIndividualFitness );
			bLiDeadIndividualInfosSorted = true;
		}
		list<const cIndividualInfo*>::iterator itrIndividual =
			liDeadIndividualInfos.begin();
		for ( ; (itrIndividual != liDeadIndividualInfos.end()) && ( 1 < lNumber );
				lNumber--, itrIndividual++ ){
			//nothing to do
		}
		if ( itrIndividual != liDeadIndividualInfos.end() ){
			//correct individual found
			pIndInfo = *itrIndividual;
		}
		pthread_mutex_unlock( & mutexIndividuals );
		return pIndInfo;
	}//else if ( iLive == 0 ){
	//search in the list of all individuals
	
	//find the correct position
	if ( ! bLiLivingIndividualInfosSorted ){
		liLivingIndividualInfos.sort( compIndividualFitness );
		bLiLivingIndividualInfosSorted = true;
	}
	list<const cIndividualInfo*>::iterator itrLivingIndividual =
		liLivingIndividualInfos.begin();
	if ( ! bLiDeadIndividualInfosSorted ){
		liDeadIndividualInfos.sort( compIndividualFitness );
		bLiDeadIndividualInfosSorted = true;
	}
	list<const cIndividualInfo*>::iterator itrDeadIndividual =
		liDeadIndividualInfos.begin();
	for ( ; ((itrLivingIndividual != liLivingIndividualInfos.end()) ||
			(itrDeadIndividual != liDeadIndividualInfos.end())) &&
			( 1 < lNumber ); lNumber--){
		
		if ( itrLivingIndividual == liLivingIndividualInfos.end() ){
			itrDeadIndividual++;
			continue;
		}
		if ( itrDeadIndividual == liDeadIndividualInfos.end() ){
			itrLivingIndividual++;
			continue;
		}
		if ( compIndividualFitness( *itrLivingIndividual, *itrDeadIndividual ) ){
			//the living individual is better than the dead -> go to next living
			itrLivingIndividual++;
			continue;
		}else{//the dead individual is better than the living -> go to next dead
			itrDeadIndividual++;
			continue;
		}
	}
	if ( (itrLivingIndividual != liLivingIndividualInfos.end()) ||
			(itrDeadIndividual != liDeadIndividualInfos.end()) ){
		
		if ( (itrLivingIndividual == liLivingIndividualInfos.end()) ){
			//return dead individual
			pIndInfo = * itrDeadIndividual;
		}else if ( (itrDeadIndividual == liDeadIndividualInfos.end()) ||
				( compIndividualFitness( *itrLivingIndividual, *itrDeadIndividual ) ) ){
			//return living individual
			pIndInfo = * itrLivingIndividual;
		}else{
			//return dead individual
			pIndInfo = * itrDeadIndividual;
		}
	}//else no better lNumber'th individual exists

	pthread_mutex_unlock( & mutexIndividuals );
	return pIndInfo;
}


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
cIndividual * cEnviroment::getIndividual() const{
	
	if ( pIndividualSelection == NULL ){
		return NULL;
	}
#ifdef FEATURE_GET_INDIVIDUAL_WITH_ORIGINAL
	if ( rand() % 256 == 0 ){
		cIndividual * pIndividual = pObjectFitnessAlgorithm->
			getOriginalIndividual()->clone();
		return pIndividual;
	}
#endif
	for ( unsigned int iteration = 0; iteration < (256 * 256); iteration++ ){
		
		cIndividualIdentifier identifier = pIndividualSelection->getIndividualIdentifier();
		//search in the living individuals for the identifier
		map<cIndividualIdentifier, cIndividualInformation >::iterator
			itrIndividual = mapLivingIndividuals.find( identifier );
		if ( itrIndividual != mapLivingIndividuals.end() ){
			//identifier found -> return it
			cIndividual * pIndividual = itrIndividual->second.pIndividual->clone();
			pthread_mutex_unlock( & mutexIndividuals );
			return pIndividual;
		}
	}
	return NULL;
}


/**
 * This method returns the the individual with the given identifier.
 * Beware: You have to care for, that the returned individual gets
 * deleted after usage.
 *
 * @param identifier the identifier for the individual which is to be returned
 * @return a pointer to the individual with the given identifier or
 * 	NULL, if non exists
 */
cIndividual * cEnviroment::getIndividual( const cIndividualIdentifier & identifier ) const{
	
	pthread_mutex_lock( & mutexIndividuals );
	//search in the living individuals for the identifier
	map<cIndividualIdentifier, cIndividualInformation >::iterator
		itrIndividual = mapLivingIndividuals.find( identifier );
	if ( itrIndividual != mapLivingIndividuals.end() ){
		//identifier found -> return it
		cIndividual * pIndividual = itrIndividual->second.pIndividual->clone();
		pthread_mutex_unlock( & mutexIndividuals );
		return pIndividual;
	}
	
	//search in the dead individuals for the identifier
	itrIndividual = mapDeadIndividuals.find( identifier );
	if ( itrIndividual != mapDeadIndividuals.end() ){
		//identifier found -> return it
		cIndividual * pIndividual = itrIndividual->second.pIndividual->clone();
		pthread_mutex_unlock( & mutexIndividuals );
		return pIndividual;
	}
	pthread_mutex_unlock( & mutexIndividuals );
	//individual info for the identifier not found
	return NULL;
}


/**
 * This method returns the lNumber'th best individual.
 * Beware: You have to care for, that the returned individual gets
 * deleted after usage.
 *
 * @param lNumber the number for the individual to return
 * @return a pointer to the lNumber'th best individual or NULL, if non
 * 	such exists
 */
cIndividual * cEnviroment::getBestIndividual( unsigned long lNumber ) const{
	
	pthread_mutex_lock( & mutexIndividuals );
	//search in the list of living individuals
	const cIndividualInfo * pIndInfo = NULL;
	//search in the list of living individuals
	//find the correct position
	if ( ! bLiLivingIndividualInfosSorted ){
		liLivingIndividualInfos.sort( compIndividualFitness );
		bLiLivingIndividualInfosSorted = true;
	}
	list<const cIndividualInfo*>::iterator itrIndividualInfo =
		liLivingIndividualInfos.begin();
	for ( ; (itrIndividualInfo != liLivingIndividualInfos.end()) && ( 1 < lNumber );
			lNumber--, itrIndividualInfo++ ){
		//nothing to do
	}
	if ( itrIndividualInfo == liLivingIndividualInfos.end() ){
		//no individual found
		return NULL;
	}//else
	pIndInfo = *itrIndividualInfo;
	
	//find the correct position
	map<cIndividualIdentifier, cIndividualInformation >::const_iterator
		itrIndividual = mapLivingIndividuals.find( pIndInfo->getIdentifier() );
	if ( itrIndividual != mapLivingIndividuals.end() ){
		//identifier found -> return it
		cIndividual * pIndividual = itrIndividual->second.pIndividual->clone();
		pthread_mutex_unlock( & mutexIndividuals );
		return pIndividual;
	}
	pthread_mutex_unlock( & mutexIndividuals );
	return NULL;
}


/**
 * @return A pointer to the object for evaluing the fitness of
 * 	individuals (respectively the objects they represents).
 * @see pObjectFitnessAlgorithm
 */
const cObjectFitnessAlgorithm * cEnviroment::getFitnessAlgorithm(){
	
	return pObjectFitnessAlgorithm;
}


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
bool cEnviroment::insertIndividual( const cIndividual * pInIndividual,
		const cOperation * pProducerOperation ){
	
	DEBUG_OUT_L2(<<"cEnviroment::insertIndividual("<< pInIndividual <<", "<<pProducerOperation<<")"<<endl<<flush);
	
	if ( ( pInIndividual == NULL ) || ( pInIndividual->getObject() == NULL ) ||
			(pInIndividual->getInfo() == NULL) ||
			( pInIndividual->getClassName() != OPERATION_DOMAIN ) ){
		//no correct individual
		return false;
	}
	//create a copy of the individual
	cIndividual * pIndividualClone = pInIndividual->clone( true );
	//check the fitness of the individual
	bool bFitnessUpdated = false;
	if ( getBestIndividualInfo() ){
		bFitnessUpdated = pIndividualClone->updateFitness(
			getFitnessAlgorithm(), getBestIndividualInfo()->getFitness() );
	}else{
		bFitnessUpdated = pIndividualClone->updateFitness(
			getFitnessAlgorithm() );
	}
	if ( bFitnessUpdated ){
		DEBUG_OUT_L2(<<"cEnviroment::insertIndividual("<< pInIndividual <<", "<<pProducerOperation<<") fitnessvalue updated"<<endl<<flush);
		//TODO: add evaluation time of the fitness to the operation time
		
		//TODO: remember when and how often the fitness was updated for the operation
		
	}
	
	if ( pProducerOperation ){
		//remember the operation for the individual
		pthread_mutex_lock( & mutexOperationsRunning );
		mapRunningOperations[ const_cast<cOperation *>( pProducerOperation ) ].liCreatedIndividuals.
			push_back( *(pIndividualClone->getInfo()) );
		pthread_mutex_unlock( & mutexOperationsRunning );
	}
	//insert the new individual
	pthread_mutex_lock( & mutexIndividuals );
	
	mapLivingIndividuals.insert( make_pair( pIndividualClone->getInfo()->getIdentifier(),
		cIndividualInformation( pIndividualClone ) ) );
	//insert individual info
	liLivingIndividualInfos.push_back( pIndividualClone->getInfo() );
	bLiLivingIndividualInfosSorted = false;
	
	pthread_mutex_lock( & mutexIndividualListeners );
	//notify the listeners for population changes about the new individual
	for ( set<clNewIndividualListener *>::iterator
			itrIndividualListener = setIndividualListener.begin();
			itrIndividualListener != setIndividualListener.end(); itrIndividualListener++ ){
		
		(*itrIndividualListener)->individualAdded( pIndividualClone );
	}
	pthread_mutex_unlock( & mutexIndividualListeners );
	pthread_mutex_unlock( & mutexIndividuals );
	
	//if to much individuals are in the population
	while ( pMaximumIndividuals->maximumReached() ){
		//till the maximal numer of individuals isn't reached -> delete individual
		removeIndividual( pSelectIndividualToDelete->getIndividualIdentifier() );
	}
	
	DEBUG_OUT_L2(<<"cEnviroment::insertIndividual("<< pInIndividual <<", "<<pProducerOperation<<") done; individuals now: "<<mapLivingIndividuals.size()<<endl<<flush);
	return true;
}


/**
 * This method removes the given individual from the enviroment and
 * delets it.
 *
 * @param pInIndividual a pointer to the individual to delete
 * @return true if the given individual was deleted, else false
 */
bool cEnviroment::removeIndividual( const cIndividualIdentifier individualId ){
	
	DEBUG_OUT_L2(<<"cEnviroment::removeIndividual( individualId )"<<endl<<flush);
	
	if ( mapLivingIndividuals.size() <= 1 ){
		//can't delete the last individual
		return false;
	}
	
	pthread_mutex_lock( & mutexIndividuals );
	map<cIndividualIdentifier, cIndividualInformation >::iterator itrIndividual =
		mapLivingIndividuals.find( individualId );
	if ( itrIndividual == mapLivingIndividuals.end() ){
		//no such individual
		pthread_mutex_unlock( & mutexIndividuals );
		return false;
	}
	const cIndividual * pIndividual = itrIndividual->second.pIndividual;
	DEBUG_OUT_L2(<<"cEnviroment::removeIndividual( individualId ) can remove"<<endl<<flush);
	
	pthread_mutex_lock( & mutexIndividualListeners );
	//notify the listeners for population changes about the to deleted individual
	for ( set<clNewIndividualListener *>::iterator
			itrIndividualListener = setIndividualListener.begin();
			itrIndividualListener != setIndividualListener.end(); itrIndividualListener++ ){
		
		(*itrIndividualListener)->individualRemoved( pIndividual );
	}
	pthread_mutex_unlock( & mutexIndividualListeners );
	
	//kill the individual and move the individualinfo from the living to the dead individuals
	itrIndividual->second.pIndividual->kill();
	map<cIndividualIdentifier, cIndividualInformation >::iterator
		itrIndividualNext = itrIndividual;
	itrIndividualNext++;
	mapDeadIndividuals.insert( itrIndividual, itrIndividualNext );
	
	mapLivingIndividuals.erase( itrIndividual );
	
	list<const cIndividualInfo*>::iterator itrIndInfo = find(
		liLivingIndividualInfos.begin(), liLivingIndividualInfos.end(),
		pIndividual->getInfo() );
	if ( itrIndInfo != liLivingIndividualInfos.end() ){
		liLivingIndividualInfos.erase( itrIndInfo );
	}
	if ( pIndividual->getInfo() ){
		liDeadIndividualInfos.push_back( pIndividual->getInfo() );
		bLiDeadIndividualInfosSorted = false;
	}
	pthread_mutex_unlock( & mutexIndividuals );
	
	DEBUG_OUT_L2(<<"cEnviroment::removeIndividual( individualId ) done"<<endl<<flush);
	return true;
}



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
unsigned long cEnviroment::getNumberOfIndividuals( short iLive ){
	
	if ( iLive == 0 ){
		
		return mapLivingIndividuals.size() + mapDeadIndividuals.size();
	}else if ( iLive == 1 ){
	
		return mapLivingIndividuals.size();
	}//else if ( iLive == -1 ){
	
	return mapDeadIndividuals.size();
}


/*the following methods are not for the operations, but for the help
classes/ objects of the enviroment (e.g. cMaximumReached)*/

/**
 * @return the number of operations, which run at the time
 */
unsigned int cEnviroment::getNumberOfRunningOperations(){
	pthread_mutex_lock( & mutexOperationsRunning );
	const size_t iNumberOfRunningOperations = mapRunningOperations.size();
	pthread_mutex_unlock( & mutexOperationsRunning );

	return iNumberOfRunningOperations;
}


/**
 * @return the number of operations executed /called by the enviroment
 * @see lNumberOfCalledOperations
 */
unsigned long cEnviroment::getNumberOfCalledOperations(){
	
	return lNumberOfCalledOperations;
}


/**
 * @return the time in secounds the enviroment was running;
 * 	@see isRunning() gives back true for this time
 */
double cEnviroment::getCpuRunTime() const{
	
	if ( isRunning() ){
		//reevalue the cpu time
		const time_t tmNewLastCpuRunTime = time( NULL );
		dCpuRunTime += tmNewLastCpuRunTime - tmLastCpuRunTime;
		tmLastCpuRunTime = tmNewLastCpuRunTime;
	}
	return dCpuRunTime;
}


/**
 * @return the time the @see start() method was called the last time
 * 	or 0, if non such exists
 */
time_t cEnviroment::getLastStartTime() const{
	
	return tmLastStartTime;
}


/**
 * @return the time the @see start() method was called the first time
 * 	for this enviroment or 0, if non such exists
 */
time_t cEnviroment::getFirstStartTime() const{
	
	return tmFirstStartTime;
}


/**
 * @return a pointer to the object for initializing the enviroment
 * 	or NULL, if non such exists; @see pInitEnviroment
 */
const cInitEnviroment * cEnviroment::getInitEnviroment(){
	
	return pInitEnviroment;
}


/**
 * @return a pointer to the object for checking the endcondition of
 * 	the enviroment or NULL, if non such exists; @see pEndCondition
 */
const cEndConditionCheck * cEnviroment::getEndConditionCheck(){
	
	return pEndCondition;
}


/**
 * @return a pointer to the object for selecting a good individual or
 * 	NULL, if non such exists; @see pIndividualSelection
 */
const cIndividualSelection * cEnviroment::getIndividualSelection(){
	
	return pIndividualSelection;
}


/**
 * @return a pointer to the object for checking if individuals needs to
 * 	be deleted befor adding new individuals or NULL, if non such
 * 	exists; @see pMaximumIndividuals
 */
const cMaximumReached * cEnviroment::getMaximumReached(){
	
	return pMaximumIndividuals;
}


/**
 * @return a pointer to the object for selecting a bad individual or
 * 	NULL, if non such exists; @see pSelectIndividualToDelete
 */
const cSelectIndividualToDelete * cEnviroment::getSelectIndividualToDelete(){
	
	return pSelectIndividualToDelete;
}


/**
 * @return a pointer to the object for evaluing the fitness of
 * 	operators of the enviroment and for handling them or NULL, if non
 * 	such exists; @see pOperationFitnessAlgorithmus
 */
cOperatorFitnessAlgorithm * cEnviroment::getOperatorFitnessAlgorithm(){
	
	return pOperationFitnessAlgorithmus;
}


/**
 * @return a pointer to the object for selecting a good operator or
 * 	NULL, if non such exists; @see pChoosOperator
 */
const cChoosOperator * cEnviroment::getChoosOperator(){
	
	return pChoosOperator;
}


/**
 * @return a pointer to the object for checking if more operators could
 * 	be started or NULL, if non such exists; @see pResourceCheck
 */
const cResourceCheck * cEnviroment::getResourceCheck(){
	
	return pResourceCheck;
}



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
bool cEnviroment::registerIndividualListener(
		clNewIndividualListener * individualListener ){
	
	if ( individualListener == NULL ){
		//can't insert non object
		return false;
	}
	pthread_mutex_lock( & mutexIndividualListeners );
	pair< set<clNewIndividualListener *>::iterator, bool > paInserted =
		setIndividualListener.insert( individualListener );
	pthread_mutex_unlock( & mutexIndividualListeners );

	return paInserted.second;
}


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
bool cEnviroment::unregisterIndividualListener(
		clNewIndividualListener * individualListener ){
	
	pthread_mutex_lock( & mutexIndividualListeners );
	const size_t iElementsRemoved =
		setIndividualListener.erase( individualListener );
	pthread_mutex_unlock( & mutexIndividualListeners );
	return ( iElementsRemoved == 1);
}


/**
 * This method is called, if the running status of the operation is changed.
 *
 * @see cOperation::bIsRunning
 * @see cOperation::isRunning()
 * @param pOperation a pointer to the operation, which status has changed
 * @param isRunning the new running status for the operation
 */
void cEnviroment::operationStatusChange( cOperation * pOperation, bool isRunning ){
	
	if ( pOperation == NULL ){
		DEBUG_OUT_L2(<<"operationStatusChange( NULL ,"<<(isRunning?("true"):("false"))<<") done"<<endl<<flush);
		return;
	}
	
	pthread_mutex_lock( & mutexOperationsRunning );
	DEBUG_OUT_L2(<<"operationStatusChange( "<<pOperation <<" ,"<<(isRunning?("true"):("false"))<<")"<<endl<<flush);
	if ( isRunning ){
		//the operation is running -> add it to the list of running operations

		const pair< map< cOperation * , cOperationInformation >::iterator, bool >
			paOperationInserted = mapRunningOperations.insert(
				pair< cOperation * , cOperationInformation >(
					pOperation, cOperationInformation() )  );
		
		if ( paOperationInserted.second ){
			lNumberOfCalledOperations++;
		}

	}else{//the operation is no more running -> delete it from the list of running operations
		DEBUG_OUT_L2(<<"searching for operation "<< pOperation<<" in the running list"<<endl<<flush);
		map< cOperation * , cOperationInformation >::iterator
			itrOperation = mapRunningOperations.find( pOperation );
		if ( itrOperation != mapRunningOperations.end() ){
			DEBUG_OUT_L2(<<"erasing operation "<< pOperation<<" from the running list"<<endl<<flush);
			
			if ( pOperationFitnessAlgorithmus ){
				//TODO: evalue operation cost
				double dOperationCost = pOperation->getCpuRunTime();
				
				/*if the operation has created no individual
				-> create a blank individual for it*/
				if ( mapRunningOperations[ pOperation ].liCreatedIndividuals.empty() ){
				
					const list<cIndividualIdentifier> liParents;
					
					//evalue the fitness of the best individual at the time
					const cIndividualInfo * pBestIndividualInfo = getBestIndividualInfo();
					const cObjectFitness * pBestObjectFitness = NULL;
					if ( pBestIndividualInfo ){
						pBestObjectFitness = pBestIndividualInfo->getFitness();
					}
					if ( pBestObjectFitness == NULL ){
						pBestObjectFitness = getFitnessAlgorithm()->getBestFitness();
					}
					
					cIndividualInfo dummyIndividualInfo( getAlgorithmIdentifier(),
						liParents, * (getFitnessAlgorithm()->getWorstCaseFitness()),
						pOperation->getName(), "dummy individual",
						* (pOperation->getOperationIdentifier()),
						time_t( NULL ), dOperationCost, pBestObjectFitness );
					dummyIndividualInfo.kill();
					
					cIndividual * pDummyIndividual = new cIndividual(
						NULL, dummyIndividualInfo, false );
					
					mapRunningOperations[ pOperation ].liCreatedIndividuals.push_back( dummyIndividualInfo );
					
					pthread_mutex_lock( & mutexIndividuals );
					pthread_mutex_lock( & mutexIndividualListeners );
					//notify the listeners for population changes about the to deleted individual
					for ( set<clNewIndividualListener *>::iterator
							itrIndividualListener = setIndividualListener.begin();
							itrIndividualListener != setIndividualListener.end(); itrIndividualListener++ ){
						
						(*itrIndividualListener)->individualAdded( pDummyIndividual );
					}
					pthread_mutex_unlock( & mutexIndividualListeners );
					
					mapDeadIndividuals.insert( make_pair(
						pDummyIndividual->getInfo()->getIdentifier(),
						cIndividualInformation( pDummyIndividual ) ) );
					liDeadIndividualInfos.push_back( pDummyIndividual->getInfo() );
					bLiDeadIndividualInfosSorted = false;
					
					pthread_mutex_unlock( & mutexIndividuals );
				}
				{//TODO: check if the given operation costs for the individuals is correct
/*					double dMinOpIndividualCost = (dOperationCost) /
						( (double)(liOperationIndividuals.size()) * 16.0);
*/					
					
				}
				//reevalue the fitness of the operation
				pOperationFitnessAlgorithmus->updateFitness( *pOperation,
					mapRunningOperations[ pOperation ].liCreatedIndividuals );
				
			}
			mapRunningOperations.erase( itrOperation );
			
			pthread_mutex_lock( & mutexOperationsRunningToDelete );
			DEBUG_OUT_L2(<<"adding operation to delete "<< pOperation<<endl<<flush);
			liOperationsToDelete.push_back( pOperation );
			DEBUG_OUT_L2(<<"adding operation to delete "<< pOperation<<" done"<<endl<<flush);
			pthread_mutex_unlock( & mutexOperationsRunningToDelete );
		}
		//destroy the operation
		pOperation->unregisterOperationRunStatusListener( this );
	}
	DEBUG_OUT_L2(<<"operationStatusChange( "<<pOperation <<" ,"<<(isRunning?("true"):("false"))<<") done"<<endl<<flush);
	pthread_mutex_unlock( & mutexOperationsRunning );
}





/**
 * This method will delete all operations which are done (respectively
 * stored in the @see liOperationsToDelete ).
 */
void cEnviroment::deleteNotRunningOperations(){

	pthread_mutex_lock( & mutexDeleteOperation );
	pthread_mutex_lock( & mutexOperationsRunningToDelete );
	list< cOperation * > liStopOperations;
	while ( ! liOperationsToDelete.empty() ){
		if ( ! liOperationsToDelete.front()->isRunning() ){
			DEBUG_OUT_L2(<<"Deleting operation "<<liOperationsToDelete.front()<<endl<<flush);
			delete liOperationsToDelete.front();
			liOperationsToDelete.pop_front();
			DEBUG_OUT_L2(<<"Deleting operation done"<<endl<<flush);
		}else{//the operation is still running but should be deleted -> stop it
			liStopOperations.push_back( liOperationsToDelete.front() );
			liOperationsToDelete.pop_front();
		}
	}
	pthread_mutex_unlock( & mutexOperationsRunningToDelete );
	pthread_mutex_unlock( & mutexDeleteOperation );
	//stop the running operations to delete
	for ( list< cOperation * >::iterator itrOperation = liStopOperations.begin();
			itrOperation != liStopOperations.end(); itrOperation++ ){
		
		(*itrOperation)->stop();
		pthread_mutex_lock( & mutexDeleteOperation );
		liOperationsToDelete.push_back( (*itrOperation) );
		pthread_mutex_unlock( & mutexDeleteOperation );
	}
	
#ifdef FEATURE_CHECK_RUNNIG_OP_FOR_DELETE
	static time_t lastCheckTime = 0;
	//check every second
	const time_t actualTime = time( 0 );
	if ( lastCheckTime != actualTime ){
		lastCheckTime = actualTime;
		
		pthread_mutex_lock( & mutexOperationsRunning );
		for ( map< cOperation * , cOperationInformation >::iterator
				itrOperation = mapRunningOperations.begin();
				itrOperation != mapRunningOperations.end(); ){
			
			if ( itrOperation->first->hasRun() ){
				DEBUG_OUT_L2(<<"The operation "<<itrOperation->first->getName()<<"( "<<itrOperation->first<<" ) is no more running, but it is in the running operations list"<<endl<<flush);
				
				pthread_mutex_unlock( & mutexOperationsRunning );
				operationStatusChange( itrOperation->first, false );
				pthread_mutex_lock( & mutexOperationsRunning );
				
				itrOperation = mapRunningOperations.begin();
			}else{
#ifdef DEBUG_OPERATION_LONG_TIME
				if ( itrOperation->second.startTime < (actualTime - 180) ){
					DEBUG_OUT_L2(<<"The operation "<<itrOperation->first->getName()<<"( "<<itrOperation->first<<" ) exists more than 3 minutes (starttime: "<< itrOperation->second.startTime <<" now: "<< actualTime <<" it's "<<((itrOperation->first->isRunning())?"":"not ")<<"running and has "<<((itrOperation->first->hasRun())?"":"not ")<<"run)"<<endl<<flush);
				}
#endif
				itrOperation++;
			}
		}
		pthread_mutex_unlock( & mutexOperationsRunning );
	}
#endif
}


/**
 * This method runs the enviroment for a tread.
 * It will wait till the enviroment is ended befor returning.
 * It will simply call run().
 *
 * @see run()
 * @see start()
 * @see stop()
 */
void * cEnviroment::runTread( void * inputArg ){
	
	((cEnviroment*)(inputArg))->run();
	
	return NULL;
}


#ifdef WINDOWS
/**
 * Wraper function for windows.
 * Wait till the given mutex is free and than locks it.
 * @param pMutexHandle pointer to the mutex to lock.
 */
void cEnviroment::pthread_mutex_lock( HANDLE * pMutexHandle ){
	
	WaitForSingleObject( &pMutexHandle, INFINITE);
}

/**
 * Wraper function for windows.
 * Unlocks the given mutex.
 * @param pMutexHandle pointer to the mutex to unlock.
 */
void cEnviroment::pthread_mutex_unlock( HANDLE * pMutexHandle ){
	
	ReleaseMutex( &pMutexHandle );
}

#endif //WINDOWS

/**
 * This function sleeps for a short period.
 */
void cEnviroment::shortSleep(){
	
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




