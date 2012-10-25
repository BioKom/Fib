/**
 * @file tEnviroment
 * file name: tEnviroment.cpp
 * @author Betti Oesterholz
 * @date 14.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cEnviroment.
 *
 * Copyright (C) @c GPL3 2010 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This file contains the test for the class cEnviroment.
 * This class is tested in the enviroment.fib modul, becaus some needed
 * classes in enviroment are pure virtual.
 *
 *
 *
 * What's tested of class cEnviroment:
 * 	- ~cEnviroment();
 * 	- const std::string OPERATION_DOMAIN;
 * 	- static cEnviroment * getInstance();
 * 	- static bool setParameter( const cInitEnviroment * pInInit, const cObjectFitnessAlgorithm * pInObjectFitnessAlgorithm, const cEndConditionCheck * pInEndCondition = NULL, const cIndividualSelection * pInIndividualSelection = NULL, const cMaximumReached * pInMaximumIndividuals = NULL, const cSelectIndividualToDelete * pInSelectIndividualToDelete = NULL, const cOperatorFitnessAlgorithm * pInOperationFitnessAlgorithmus = NULL, const cChoosOperator * pInChoosOperator = NULL, const cResourceCheck * pInResourceCheck = NULL );
 * 	- bool start();
 * 	- bool run();
 * 	- bool stop();
 * 	- bool isRunning();
 * 	- unsigned long long getAlgorithmIdentifier();
 * 	- list<const cIndividualInfo*> getIndividualInfos( short iLive = 0 ) const;
 * 	- const cIndividualInfo * getIndividualInfo( const cIndividualIdentifier & identifier ) const;
 * 	- const cIndividualInfo * getBestIndividualInfo( unsigned long lNumber = 1, short iLive = 1 ) const;
 * 	- cIndividual * getIndividual() const;
 * 	- cIndividual * getIndividual( const cIndividualIdentifier & identifier ) const;
 * 	- cIndividual * getBestIndividual( unsigned long lNumber = 1 ) const;
 * 	- static const cObjectFitnessAlgorithm * getFitnessAlgorithm();
 * 	- bool insertIndividual( const cIndividual * pInIndividual, const cOperation * pProducerOperation = NULL );
 * 	- bool removeIndividual( const cIndividual * pInIndividual );
 * 	- unsigned long getNumberOfIndividuals( short iLive = 1 );
 * 	- unsigned int getNumberOfRunningOperations();
 * 	- unsigned long getNumberOfCalledOperations();
 * 	- double getCpuRunTime() const;
 * 	- time_t getLastStartTime() const;
 * 	- time_t getFirstStartTime() const;
 * 	- static const cInitEnviroment * getInitEnviroment();
 * 	- static const cEndConditionCheck * getEndConditionCheck();
 * 	- static const cIndividualSelection * getIndividualSelection();
 * 	- static const cMaximumReached * getMaximumReached();
 * 	- static const cSelectIndividualToDelete * getSelectIndividualToDelete();
 * 	- static cOperatorFitnessAlgorithm * getOperatorFitnessAlgorithm();
 * 	- static const cChoosOperator * getChoosOperator();
 * 	- static const cResourceCheck * getResourceCheck();
 * 	- bool registerIndividualListener( clNewIndividualListener * individualListener );
 * 	- bool unregisterIndividualListener( clNewIndividualListener * individualListener );
 * 	- void operationStatusChange( cOperation * pOperation, bool isRunning );
 *
 * call: tEnviroment [MAX_SIZE] [ITERATIONS]
 *
 * parameters:
 * 	MAX_SIZE
 * 		The maximum size, which should not oversteped when the
 * 		Fib-objects are generated.
 * 		The standardvalue is 256.
 * 	ITERATIONS
 * 		The iterations for every parameterset. The generateFibObject() is
 * 		called I times for every parameterset.
 * 		Standardvalue is 256.
 */
/*
History:
14.03.2010  Oesterholz  created
15.03.2012  Oesterholz  changes for windows compatibility
25.10.2012  Oesterholz  Bugfix: delay handling improved
*/



#include "version.h"

#include "cEnviroment.h"

#include "cInitEnviroment.h"
#include "cInitFibEnviroment.h"
#include "cObjectFitness.h"
#include "cFibObjectFitnessBasic.h"
#include "cObjectFitnessAlgorithm.h"
#include "cFibObjectFitnessAlgorithm.h"
#include "cFibObjectFitnessBasicAlgorithm.h"
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
#include "cFibIndividual.h"

#include "cOpDummy.h"

#include "cRoot.h"
#include "cPoint.h"


#include <utility>
#include <iostream>
#include <ctime>
#include <cmath>
#include <set>
#include <list>
#include <pthread.h>


using namespace enviroment::fib;
using namespace enviroment;
using namespace std;


extern cFibElement * generateFibObject( unsigned int uiSize,
		unsigned long ulMaximalEvaluedPoints,
		list< pair< char, double > > liFractionOfFibElements,
		const list< cTypeProperty > & liPossiblePropertytyps,
		const unsigned int uiNumberOfDimensions,
		const unsigned int uiAverageSubRoots, const unsigned int uiAverageSubRootsDepth,
		const unsigned int uiNumberOfAverageInputVariables,
		const double dFractionsOfUsedVariables ,
		unsigned int uiMaxVectorElementNumber );


int testParameter( unsigned long &ulTestphase );
int testRun( unsigned long &ulTestphase );//+ operations
int testOperationStatusChange( unsigned long &ulTestphase );
int testPopulation( unsigned long &ulTestphase, unsigned long uiMaxIteration,
	unsigned short uiIndividualListenerTest );//+ clNewIndividualListener


unsigned long ulAlgorithmId = 1;
unsigned int uiMaxSize = 256;

int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn=0;//returnvalue of the test; the number of occured Errors

	srand( time( NULL ) );
	
	//* read input parameters
	unsigned int uiIterations = 256;
	
	if ( argc >= 2 ){
		//one parameter given; get parameter max size
		uiMaxSize = atol( argv[1] );
		if ( uiMaxSize < 4 ){
			uiMaxSize = 4;
		}
	}
	
	if ( argc >= 3 ){
		//two parameter given; read parameter iterations
		uiIterations = atol( argv[2] );
		if ( uiIterations < 1 ){
			uiIterations = 1;
		}
	}
	
	cout<<endl<<"Running Test for cEnviroment methods"<<endl;
	cout<<      "===================================="<<endl;
	
	iReturn += testParameter( ulTestphase );
	iReturn += testRun( ulTestphase );
	iReturn += testOperationStatusChange( ulTestphase );

	iReturn += testPopulation( ulTestphase, uiIterations + 4, 0 );
	iReturn += testPopulation( ulTestphase, uiIterations + 4, 1 );
	iReturn += testPopulation( ulTestphase, uiIterations / 4 + 4, 2 );
	iReturn += testPopulation( ulTestphase, uiIterations / 4 + 4, 3 );


	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}


#ifdef WINDOWS
	#include <windows.h>
#else//WINDOWS
	#include <unistd.h>
#endif//WINDOWS

/**
 * This function will sleep for the given number of milli seconds.
 *
 * @param ulMilliSecondsToSleep the milliseconds to sleep
 */
void fibMilliSleep( unsigned long ulMilliSecondsToSleep ){

#ifdef WINDOWS
	Sleep( ulMilliSecondsToSleep );
#else//WINDOWS
	
	struct timespec timeToWait;
	timeToWait.tv_sec  = ulMilliSecondsToSleep / 1000L;
	timeToWait.tv_nsec = ( ulMilliSecondsToSleep % 1000) * 1000000L; //1000000L = 1 ms
	struct timespec remainingTime;

	//for debugging:
	//cout<<"Milliseconds to sleep="<<ulMilliSecondsToSleep<<"   time now="<<time( NULL )<<endl;
	
	int iReturnNanosleep = 1;
	while ( iReturnNanosleep != 0 ){
		//for debugging:
		//cout<<"befor timeToWait.tv_sec="<<timeToWait.tv_sec<<"   timeToWait.tv_nsec="<<timeToWait.tv_nsec<<endl;

		remainingTime.tv_sec  = 0;
		remainingTime.tv_nsec = 0;
		iReturnNanosleep = nanosleep( &timeToWait, &remainingTime );
		
		/*for debugging:
		cout<<"after timeToWait.tv_sec="<<timeToWait.tv_sec<<"   timeToWait.tv_nsec="<<timeToWait.tv_nsec<<
			"  nanosleep return="<<iReturnNanosleep<<"   time now="<<time( NULL )<<endl;
		cout<<"   remainingTime.tv_sec="<<remainingTime.tv_sec<<
			"   remainingTime.tv_nsec="<<remainingTime.tv_nsec<<endl;*/
		
		if ( iReturnNanosleep != 0 ){
			//wait some more
			timeToWait = remainingTime;
		}
	}
#endif//WINDOWS
}

namespace enviroment{

	/**
	 * Testclasses for testing the enviroment
	 */
	
	class cIndividualSelectionTest: public cIndividualSelection{
	public:
		/**
		 * @return individual identifier
		 */
		virtual cIndividualIdentifier getIndividualIdentifier() const{
			static cIndividualIdentifier individualIdentifier( 321 );
			return individualIdentifier;
		}
		
		/**
		 * This method clones this object.
		 *
		 * @return a clone of this object
		 */
		virtual cIndividualSelectionTest * clone() const{
			return new cIndividualSelectionTest( *this );
		}
	};
	
	class cMaximumReachedTest: public cMaximumReached{
	public:
		/**
		* @return true if no more individuals should be added to the
		* 	enviroment, else false
		*/
		virtual bool maximumReached() const{
			return true;
		}
	
		/**
		* This method clones this object.
		*
		* @return a clone of this object
		*/
		virtual cMaximumReached * clone() const{
			return new cMaximumReachedTest( *this );
		}
	};
	
	class cMaximumReachedTestFalse: public cMaximumReached{
	public:
		/**
		* @return true if no more individuals should be added to the
		* 	enviroment, else false
		*/
		virtual bool maximumReached() const{
			return false;
		}
	
		/**
		* This method clones this object.
		*
		* @return a clone of this object
		*/
		virtual cMaximumReached * clone() const{
			return new cMaximumReachedTestFalse( *this );
		}
	};

	class cSelectIndividualToDeleteTest: public cSelectIndividualToDelete{
	public:
	
		/**
		 * @return individual identifier
		 */
		virtual cIndividualIdentifier getIndividualIdentifier() const{
			static cIndividualIdentifier individualIdentifier( 321 );
			return individualIdentifier;
		}
	
		/**
		 * This method clones this object.
		 *
		 * @return a clone of this object
		 */
		virtual cSelectIndividualToDelete * clone() const{
			return new cSelectIndividualToDeleteTest( *this );
		}
	
	
	};//end class cSelectIndividualToDelete
	
	
	class cChoosOperatorTest: public cChoosOperator{
	public:
		
		/**
		 * @return 987
		 */
		virtual cOperation * choosOperator() const{
			return (cOperation *)987;
		}
	
		/**
		 * This method clones this object.
		 *
		 * @return a clone of this object
		 */
		virtual cChoosOperator * clone() const{
			return new cChoosOperatorTest();
		}
	};//end class cChoosOperator
	
	
	class cResourceCheckTest: public cResourceCheck{
	public:
	
		/**
		 * @return false
		 */
		virtual bool enoughResources() const{
			return false;
		}
	
		/**
		 * This method clones this object.
		 *
		 * @return a clone of this object
		 */
		virtual cResourceCheck * clone() const{
			return new cResourceCheckTest();
		}
	
	
	};//end class cResourceCheckTest
	
};//namespace enviroment




/**
 * This function if the cEnviroment is empty.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int checkIfEnviromentIsEmpty(){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	//check the getInstance() methode from cEnviroment
	cout<<"cEnviroment * pEnviroment = cEnviroment::getInstance(); "<<endl;
	cEnviroment * pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment == NULL ){
	
		cout<<"No instance of the enviroment could be correctly created. "<<endl;
	}else{
		cerr<<"Error: An instance of the enviroment could be created."<<endl;
		iReturn++;
	}
	//check the getFitnessAlgorithm() methode from cEnviroment
	cout<<"const cObjectFitnessAlgorithm * pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm(); "<<endl;
	const cObjectFitnessAlgorithm * pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm();
	if ( pObjectFitnessAlgorithm == NULL ){
	
		cout<<"The object fitness algorithm of the enviroment is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The object fitness algorithm of the enviroment is not NULL."<<endl;
		iReturn++;
	}
	//check the getInitEnviroment() methode from cEnviroment
	cout<<"const cInitEnviroment * pInitEnviroment = cEnviroment::getInitEnviroment(); "<<endl;
	const cInitEnviroment * pInitEnviroment = cEnviroment::getInitEnviroment();
	if ( pInitEnviroment == NULL ){
	
		cout<<"The object for initializising the enviroment is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The object for initializising the enviroment is not NULL."<<endl;
		iReturn++;
	}
	//check the getEndConditionCheck() methode from cEnviroment
	cout<<"const cEndConditionCheck * pEndConditionCheck = cEnviroment::getEndConditionCheck(); "<<endl;
	const cEndConditionCheck * pEndConditionCheck = cEnviroment::getEndConditionCheck();
	if ( pEndConditionCheck == NULL ){
	
		cout<<"The object for the endcondition check of the enviroment is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The object for the endcondition check of the enviroment is not NULL."<<endl;
		iReturn++;
	}
	//check the getIndividualSelection() methode from cEnviroment
	cout<<"const cIndividualSelection * pIndividualSelection = cEnviroment::getIndividualSelection(); "<<endl;
	const cIndividualSelection * pIndividualSelection = cEnviroment::getIndividualSelection();
	if ( pIndividualSelection == NULL ){
	
		cout<<"The object for selecting a good individual from the enviroment is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good individual from the enviroment is not NULL."<<endl;
		iReturn++;
	}
	//check the getMaximumReached() methode from cEnviroment
	cout<<"const cMaximumReached * pMaximumReached = cEnviroment::getMaximumReached(); "<<endl;
	const cMaximumReached * pMaximumReached = cEnviroment::getMaximumReached();
	if ( pMaximumReached == NULL ){
	
		cout<<"The object for checking the maximum population size of the enviroment is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking the maximum population size of the enviroment is not NULL."<<endl;
		iReturn++;
	}
	//check the getSelectIndividualToDelete() methode from cEnviroment
	cout<<"const cSelectIndividualToDelete * pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete(); "<<endl;
	const cSelectIndividualToDelete * pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete();
	if ( pSelectIndividualToDelete == NULL ){
	
		cout<<"The object for selecting a bad individual from the enviroment is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a bad individual from the enviroment is not NULL."<<endl;
		iReturn++;
	}
	//check the getOperatorFitnessAlgorithm() methode from cEnviroment
	cout<<"const cOperatorFitnessAlgorithm * pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm(); "<<endl;
	const cOperatorFitnessAlgorithm * pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm();
	if ( pOperatorFitnessAlgorithm == NULL ){
	
		cout<<"The operation fitness algorithm of the enviroment is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The operation fitness algorithm of the enviroment is not NULL."<<endl;
		iReturn++;
	}
	//check the getChoosOperator() methode from cEnviroment
	cout<<"const cChoosOperator * pChoosOperator = cEnviroment::getChoosOperator(); "<<endl;
	const cChoosOperator * pChoosOperator = cEnviroment::getChoosOperator();
	if ( pChoosOperator == NULL ){
	
		cout<<"The object for selecting a good operation for the enviroment is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good operation for the enviroment is not NULL."<<endl;
		iReturn++;
	}
	//check the getResourceCheck() methode from cEnviroment
	cout<<"const cResourceCheck * pResourceCheck = cEnviroment::getResourceCheck(); "<<endl;
	const cResourceCheck * pResourceCheck = cEnviroment::getResourceCheck();
	if ( pResourceCheck == NULL ){
	
		cout<<"The object for checking if more operations could be started for the enviroment is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking if more operations could be started for the enviroment is not NULL."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This function tests the methods for the parameters of the
 * cEnviroment and the getInstance() method of the class.
 *
 * methods tested:
 * 	- ~cEnviroment();
 * 	- const std::string OPERATION_DOMAIN;
 * 	- static cEnviroment * getInstance();
 * 	- static bool setParameter( const cInitEnviroment * pInInit, const cObjectFitnessAlgorithm * pInObjectFitnessAlgorithm, const cEndConditionCheck * pInEndCondition = NULL, const cIndividualSelection * pInIndividualSelection = NULL, const cMaximumReached * pInMaximumIndividuals = NULL, const cSelectIndividualToDelete * pInSelectIndividualToDelete = NULL, const cOperatorFitnessAlgorithm * pInOperationFitnessAlgorithmus = NULL, const cChoosOperator * pInChoosOperator = NULL, const cResourceCheck * pInResourceCheck = NULL );
 * 	- unsigned long long getAlgorithmIdentifier();
 * 	- static const cObjectFitnessAlgorithm * getFitnessAlgorithm();
 * 	- double getCpuRunTime() const;
 * 	- time_t getLastStartTime() const;
 * 	- time_t getFirstStartTime() const;
 * 	- static const cInitEnviroment * getInitEnviroment();
 * 	- static const cEndConditionCheck * getEndConditionCheck();
 * 	- static const cIndividualSelection * getIndividualSelection();
 * 	- static const cMaximumReached * getMaximumReached();
 * 	- static const cSelectIndividualToDelete * getSelectIndividualToDelete();
 * 	- static cOperatorFitnessAlgorithm * getOperatorFitnessAlgorithm();
 * 	- static const cChoosOperator * getChoosOperator();
 * 	- static const cResourceCheck * getResourceCheck();
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testParameter( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cEnviroment static parameter class with no values set"<<endl;
	
	iReturn += checkIfEnviromentIsEmpty();


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cEnviroment with the init and object fitness object set"<<endl;
	
	cVectorPosition vecPosition( 2 );
	vecPosition.setValue( 1, 1 );
	cPoint point2( &vecPosition );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cRoot rootInit( &point2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cRoot rootInit( NULL, NULL, &point2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	rootInit.setNumberOfInputVariables( 1 );
	
	cout<<"cInitFibEnviroment initEnviroment( rootInit ); "<<endl;
	cInitFibEnviroment initEnviroment( rootInit );
	
	cout<<"cFibObjectFitnessBasicAlgorithm fibObjectAlgorithmBasic( &rootInit, 123, 2.0, 3.0 );"<<endl;
	cFibObjectFitnessBasicAlgorithm fibObjectAlgorithmBasic( &rootInit, 123, 2.0, 3.0 );
	
	//check the setParameter() methode from cEnviroment
	cout<<"bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic );"<<endl;
	bool bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic );

	if ( bParameterSet ){
	
		cout<<"The parameter could be correctly set. "<<endl;
	}else{
		cerr<<"Error: The parameter couldn't be set."<<endl;
		iReturn++;
	}

	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	cEnviroment * pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment != NULL ){
	
		cout<<"An instance of the enviroment could be correctly created. "<<endl;
	}else{
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
	}
	//check the getFitnessAlgorithm() methode from cEnviroment
	cout<<"pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm(); "<<endl;
	const cObjectFitnessAlgorithm * pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm();
	if ( pObjectFitnessAlgorithm != NULL ){
	
		if ( (fibObjectAlgorithmBasic.getWeightDistanceToOriginal() ==
				((cFibObjectFitnessBasicAlgorithm*)pObjectFitnessAlgorithm)->getWeightDistanceToOriginal()) &&
				(fibObjectAlgorithmBasic.getClassName() ==
				((cFibObjectFitnessBasicAlgorithm*)pObjectFitnessAlgorithm)->getClassName()) ){
			
			cout<<"The object fitness algorithm is correct. "<<endl;
		}else{
			cerr<<"Error: The object fitness algorithm is not correct."<<endl;
			iReturn++;
		}
		
	}else{
		cerr<<"Error: The object fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getInitEnviroment() methode from cEnviroment
	cout<<"pInitEnviroment = cEnviroment::getInitEnviroment(); "<<endl;
	const cInitEnviroment * pInitEnviroment = cEnviroment::getInitEnviroment();
	if ( pInitEnviroment != NULL ){
	
		cout<<"The object for initializising the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for initializising the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getEndConditionCheck() methode from cEnviroment
	cout<<"pEndConditionCheck = cEnviroment::getEndConditionCheck(); "<<endl;
	const cEndConditionCheck * pEndConditionCheck = cEnviroment::getEndConditionCheck();
	if ( pEndConditionCheck != NULL ){
	
		cout<<"The object for the endcondition check of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for the endcondition check of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getIndividualSelection() methode from cEnviroment
	cout<<"pIndividualSelection = cEnviroment::getIndividualSelection(); "<<endl;
	const cIndividualSelection * pIndividualSelection = cEnviroment::getIndividualSelection();
	if ( pIndividualSelection != NULL ){
	
		cout<<"The object for selecting a good individual from the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getMaximumReached() methode from cEnviroment
	cout<<"pMaximumReached = cEnviroment::getMaximumReached(); "<<endl;
	const cMaximumReached * pMaximumReached = cEnviroment::getMaximumReached();
	if ( pMaximumReached != NULL ){
	
		cout<<"The object for checking the maximum population size of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking the maximum population size of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getSelectIndividualToDelete() methode from cEnviroment
	cout<<"pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete(); "<<endl;
	const cSelectIndividualToDelete * pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete();
	if ( pSelectIndividualToDelete != NULL ){
	
		cout<<"The object for selecting a bad individual from the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a bad individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getOperatorFitnessAlgorithm() methode from cEnviroment
	cout<<"pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm(); "<<endl;
	const cOperatorFitnessAlgorithm * pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm();
	if ( pOperatorFitnessAlgorithm != NULL ){
	
		cout<<"The operation fitness algorithm of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The operation fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getChoosOperator() methode from cEnviroment
	cout<<"pChoosOperator = cEnviroment::getChoosOperator(); "<<endl;
	const cChoosOperator * pChoosOperator = cEnviroment::getChoosOperator();
	if ( pChoosOperator != NULL ){
	
		cout<<"The object for selecting a good operation for the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good operation for the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getResourceCheck() methode from cEnviroment
	cout<<"pResourceCheck = cEnviroment::getResourceCheck(); "<<endl;
	const cResourceCheck * pResourceCheck = cEnviroment::getResourceCheck();
	if ( pResourceCheck != NULL ){
	
		cout<<"The object for checking if more operations could be started for the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking if more operations could be started for the enviroment is NULL."<<endl;
		iReturn++;
	}
	if ( pEnviroment ){
		//check the OPERATION_DOMAIN methode from cEnviroment
		if ( pEnviroment->OPERATION_DOMAIN == "cFibIndividual" ){
		
			cout<<"The enviroment operation domain is correctly \"cFibIndividual\". "<<endl;
		}else{
			cerr<<"Error: The enviroment operation domain is "<< pEnviroment->OPERATION_DOMAIN <<
				" and not \"cFibIndividual\"."<<endl;
			iReturn++;
		}
		//check the getAlgorithmIdentifier() methode from cEnviroment
		if ( pEnviroment->getAlgorithmIdentifier() == ulAlgorithmId ){
		
			cout<<"The enviroment identifier is correctly "<<
				pEnviroment->getAlgorithmIdentifier() <<" . "<<endl;
		}else{
			cerr<<"Error: The enviroment identifier is "<<
				pEnviroment->getAlgorithmIdentifier() <<", but should be "<< ulAlgorithmId <<" ."<<endl;
			iReturn++;
		}
		//check the getCpuRunTime() methode from cEnviroment
		if ( pEnviroment->getCpuRunTime() == 0.0 ){
		
			cout<<"The enviroment cpu runtime is correctly "<<
				pEnviroment->getCpuRunTime() <<" s . "<<endl;
		}else{
			cerr<<"Error: The enviroment cpu runtime is "<<
				pEnviroment->getCpuRunTime() <<" s , but should be "<< 0.0 <<" s ."<<endl;
			iReturn++;
		}
		//check the getLastStartTime() methode from cEnviroment
		if ( pEnviroment->getLastStartTime() == 0 ){
		
			cout<<"The enviroment last start time is correctly "<<
				pEnviroment->getLastStartTime() <<"  . "<<endl;
		}else{
			cerr<<"Error: The enviroment last start time is "<<
				pEnviroment->getLastStartTime() <<"  , but should be "<< 0 <<" ."<<endl;
			iReturn++;
		}
		//check the getFirstStartTime() methode from cEnviroment
		if ( pEnviroment->getFirstStartTime() == 0 ){
		
			cout<<"The enviroment first start time is correctly "<<
				pEnviroment->getFirstStartTime() <<". "<<endl;
		}else{
			cerr<<"Error: The enviroment first start time is "<<
				pEnviroment->getFirstStartTime() <<", but should be "<< 0 <<" ."<<endl;
			iReturn++;
		}

		delete pEnviroment;
		ulAlgorithmId++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing deleted cEnviroment static parameters"<<endl;
	
	iReturn += checkIfEnviromentIsEmpty();


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cEnviroment with the init object set"<<endl;
	
	//check the setParameter() methode from cEnviroment
	cout<<"bParameterSet = cEnviroment::setParameter( &initEnviroment, NULL );"<<endl;
	bParameterSet = cEnviroment::setParameter( &initEnviroment, NULL );

	if ( ! bParameterSet ){
	
		cout<<"The parameter could be not correctly set. "<<endl;
	}else{
		cerr<<"Error: The parameter are correctly set, but souldn't be."<<endl;
		iReturn++;
	}
	
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment == NULL ){
	
		cout<<"An instance of the enviroment couldn't be correctly created. "<<endl;
	}else{
		cerr<<"Error: An instance of the enviroment could be created."<<endl;
		iReturn++;
	}
	//check the getFitnessAlgorithm() methode from cEnviroment
	cout<<"pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm(); "<<endl;
	pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm();
	if ( pObjectFitnessAlgorithm == NULL ){
	
		cout<<"The object fitness algorithm is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The object fitness algorithm of the enviroment is not NULL."<<endl;
		iReturn++;
	}
	//check the getInitEnviroment() methode from cEnviroment
	cout<<"pInitEnviroment = cEnviroment::getInitEnviroment(); "<<endl;
	pInitEnviroment = cEnviroment::getInitEnviroment();
	if ( pInitEnviroment != NULL ){
	
		cout<<"The object for initializising the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for initializising the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getEndConditionCheck() methode from cEnviroment
	cout<<"pEndConditionCheck = cEnviroment::getEndConditionCheck(); "<<endl;
	pEndConditionCheck = cEnviroment::getEndConditionCheck();
	if ( pEndConditionCheck != NULL ){
	
		cout<<"The object for the endcondition check of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for the endcondition check of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getIndividualSelection() methode from cEnviroment
	cout<<"pIndividualSelection = cEnviroment::getIndividualSelection(); "<<endl;
	pIndividualSelection = cEnviroment::getIndividualSelection();
	if ( pIndividualSelection != NULL ){
	
		cout<<"The object for selecting a good individual from the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getMaximumReached() methode from cEnviroment
	cout<<"pMaximumReached = cEnviroment::getMaximumReached(); "<<endl;
	pMaximumReached = cEnviroment::getMaximumReached();
	if ( pMaximumReached != NULL ){
	
		cout<<"The object for checking the maximum population size of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking the maximum population size of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getSelectIndividualToDelete() methode from cEnviroment
	cout<<"pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete(); "<<endl;
	pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete();
	if ( pSelectIndividualToDelete != NULL ){
	
		cout<<"The object for selecting a bad individual from the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a bad individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getOperatorFitnessAlgorithm() methode from cEnviroment
	cout<<"pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm(); "<<endl;
	pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm();
	if ( pOperatorFitnessAlgorithm != NULL ){
	
		cout<<"The operation fitness algorithm of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The operation fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getChoosOperator() methode from cEnviroment
	cout<<"pChoosOperator = cEnviroment::getChoosOperator(); "<<endl;
	pChoosOperator = cEnviroment::getChoosOperator();
	if ( pChoosOperator != NULL ){
	
		cout<<"The object for selecting a good operation for the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good operation for the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getResourceCheck() methode from cEnviroment
	cout<<"pResourceCheck = cEnviroment::getResourceCheck(); "<<endl;
	pResourceCheck = cEnviroment::getResourceCheck();
	if ( pResourceCheck != NULL ){
	
		cout<<"The object for checking if more operations could be started for the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking if more operations could be started for the enviroment is NULL."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cEnviroment with additionally the object fitness object set"<<endl;
	
	//check the setParameter() methode from cEnviroment
	cout<<"bParameterSet = cEnviroment::setParameter( NULL, &fibObjectAlgorithmBasic );"<<endl;
	bParameterSet = cEnviroment::setParameter( NULL, &fibObjectAlgorithmBasic );

	if ( bParameterSet ){
	
		cout<<"The parameter could be correctly set. "<<endl;
	}else{
		cerr<<"Error: The parameter couldn't be set."<<endl;
		iReturn++;
	}
	
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment != NULL ){
	
		cout<<"An instance of the enviroment could be correctly created. "<<endl;
	}else{
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
	}
	//check the getFitnessAlgorithm() methode from cEnviroment
	cout<<"pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm(); "<<endl;
	pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm();
	if ( pObjectFitnessAlgorithm != NULL ){
	
		if ( (fibObjectAlgorithmBasic.getWeightDistanceToOriginal() ==
				((cFibObjectFitnessBasicAlgorithm*)pObjectFitnessAlgorithm)->getWeightDistanceToOriginal()) &&
				(fibObjectAlgorithmBasic.getClassName() ==
				((cFibObjectFitnessBasicAlgorithm*)pObjectFitnessAlgorithm)->getClassName()) ){
			
			cout<<"The object fitness algorithm is correct. "<<endl;
		}else{
			cerr<<"Error: The object fitness algorithm is not correct."<<endl;
			iReturn++;
		}
		
	}else{
		cerr<<"Error: The object fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getInitEnviroment() methode from cEnviroment
	cout<<"pInitEnviroment = cEnviroment::getInitEnviroment(); "<<endl;
	pInitEnviroment = cEnviroment::getInitEnviroment();
	if ( pInitEnviroment != NULL ){
	
		cout<<"The object for initializising the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for initializising the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getEndConditionCheck() methode from cEnviroment
	cout<<"pEndConditionCheck = cEnviroment::getEndConditionCheck(); "<<endl;
	pEndConditionCheck = cEnviroment::getEndConditionCheck();
	if ( pEndConditionCheck != NULL ){
	
		cout<<"The object for the endcondition check of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for the endcondition check of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getIndividualSelection() methode from cEnviroment
	cout<<"pIndividualSelection = cEnviroment::getIndividualSelection(); "<<endl;
	pIndividualSelection = cEnviroment::getIndividualSelection();
	if ( pIndividualSelection != NULL ){
	
		cout<<"The object for selecting a good individual from the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getMaximumReached() methode from cEnviroment
	cout<<"pMaximumReached = cEnviroment::getMaximumReached(); "<<endl;
	pMaximumReached = cEnviroment::getMaximumReached();
	if ( pMaximumReached != NULL ){
	
		cout<<"The object for checking the maximum population size of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking the maximum population size of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getSelectIndividualToDelete() methode from cEnviroment
	cout<<"pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete(); "<<endl;
	pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete();
	if ( pSelectIndividualToDelete != NULL ){
	
		cout<<"The object for selecting a bad individual from the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a bad individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getOperatorFitnessAlgorithm() methode from cEnviroment
	cout<<"pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm(); "<<endl;
	pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm();
	if ( pOperatorFitnessAlgorithm != NULL ){
	
		cout<<"The operation fitness algorithm of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The operation fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getChoosOperator() methode from cEnviroment
	cout<<"pChoosOperator = cEnviroment::getChoosOperator(); "<<endl;
	pChoosOperator = cEnviroment::getChoosOperator();
	if ( pChoosOperator != NULL ){
	
		cout<<"The object for selecting a good operation for the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good operation for the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getResourceCheck() methode from cEnviroment
	cout<<"pResourceCheck = cEnviroment::getResourceCheck(); "<<endl;
	pResourceCheck = cEnviroment::getResourceCheck();
	if ( pResourceCheck != NULL ){
	
		cout<<"The object for checking if more operations could be started for the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking if more operations could be started for the enviroment is NULL."<<endl;
		iReturn++;
	}
	
	if ( pEnviroment ){
		//check the OPERATION_DOMAIN methode from cEnviroment
		if ( pEnviroment->OPERATION_DOMAIN == "cFibIndividual" ){
		
			cout<<"The enviroment operation domain is correctly \"cFibIndividual\". "<<endl;
		}else{
			cerr<<"Error: The enviroment operation domain is "<< pEnviroment->OPERATION_DOMAIN <<
				" and not \"cFibIndividual\"."<<endl;
			iReturn++;
		}
		//check the getAlgorithmIdentifier() methode from cEnviroment
		if ( pEnviroment->getAlgorithmIdentifier() == ulAlgorithmId ){
		
			cout<<"The enviroment identifier is correctly "<<
				pEnviroment->getAlgorithmIdentifier() <<" . "<<endl;
		}else{
			cerr<<"Error: The enviroment identifier is "<<
				pEnviroment->getAlgorithmIdentifier() <<", but should be "<< ulAlgorithmId <<" ."<<endl;
			iReturn++;
		}
		//check the getCpuRunTime() methode from cEnviroment
		if ( pEnviroment->getCpuRunTime() == 0.0 ){
		
			cout<<"The enviroment cpu runtime is correctly "<<
				pEnviroment->getCpuRunTime() <<" s . "<<endl;
		}else{
			cerr<<"Error: The enviroment cpu runtime is "<<
				pEnviroment->getCpuRunTime() <<" s , but should be "<< 0.0 <<" s ."<<endl;
			iReturn++;
		}
		//check the getLastStartTime() methode from cEnviroment
		if ( pEnviroment->getLastStartTime() == 0 ){
		
			cout<<"The enviroment last start time is correctly "<<
				pEnviroment->getLastStartTime() <<"  . "<<endl;
		}else{
			cerr<<"Error: The enviroment last start time is "<<
				pEnviroment->getLastStartTime() <<"  , but should be "<< 0 <<" ."<<endl;
			iReturn++;
		}
		//check the getFirstStartTime() methode from cEnviroment
		if ( pEnviroment->getFirstStartTime() == 0 ){
		
			cout<<"The enviroment first start time is correctly "<<
				pEnviroment->getFirstStartTime() <<". "<<endl;
		}else{
			cerr<<"Error: The enviroment first start time is "<<
				pEnviroment->getFirstStartTime() <<", but should be "<< 0 <<" ."<<endl;
			iReturn++;
		}
		delete pEnviroment;
		ulAlgorithmId++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing deleted cEnviroment static parameters"<<endl;
	
	iReturn += checkIfEnviromentIsEmpty();

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cEnviroment with the object fitness object set"<<endl;
	
	//check the setParameter() methode from cEnviroment
	cout<<"bParameterSet = cEnviroment::setParameter( NULL, &fibObjectAlgorithmBasic );"<<endl;
	bParameterSet = cEnviroment::setParameter( NULL, &fibObjectAlgorithmBasic );

	if ( ! bParameterSet ){
	
		cout<<"The parameter couldn't be correctly set. "<<endl;
	}else{
		cerr<<"Error: The parameter could be set."<<endl;
		iReturn++;
	}
	
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment == NULL ){
	
		cout<<"An instance of the enviroment couldn't be correctly created. "<<endl;
	}else{
		cerr<<"Error: An instance of the enviroment could be created."<<endl;
		iReturn++;
	}
	//check the getFitnessAlgorithm() methode from cEnviroment
	cout<<"pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm(); "<<endl;
	pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm();
	if ( pObjectFitnessAlgorithm != NULL ){
	
		if ( (fibObjectAlgorithmBasic.getWeightDistanceToOriginal() ==
				((cFibObjectFitnessBasicAlgorithm*)pObjectFitnessAlgorithm)->getWeightDistanceToOriginal()) &&
				(fibObjectAlgorithmBasic.getClassName() ==
				((cFibObjectFitnessBasicAlgorithm*)pObjectFitnessAlgorithm)->getClassName()) ){
			
			cout<<"The object fitness algorithm is correct. "<<endl;
		}else{
			cerr<<"Error: The object fitness algorithm is not correct."<<endl;
			iReturn++;
		}
		
	}else{
		cerr<<"Error: The object fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getInitEnviroment() methode from cEnviroment
	cout<<"pInitEnviroment = cEnviroment::getInitEnviroment(); "<<endl;
	pInitEnviroment = cEnviroment::getInitEnviroment();
	if ( pInitEnviroment == NULL ){
	
		cout<<"The object for initializising the enviroment is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The object for initializising the enviroment is not NULL."<<endl;
		iReturn++;
	}
	//check the getEndConditionCheck() methode from cEnviroment
	cout<<"pEndConditionCheck = cEnviroment::getEndConditionCheck(); "<<endl;
	pEndConditionCheck = cEnviroment::getEndConditionCheck();
	if ( pEndConditionCheck != NULL ){
	
		cout<<"The object for the endcondition check of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for the endcondition check of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getIndividualSelection() methode from cEnviroment
	cout<<"pIndividualSelection = cEnviroment::getIndividualSelection(); "<<endl;
	pIndividualSelection = cEnviroment::getIndividualSelection();
	if ( pIndividualSelection != NULL ){
	
		cout<<"The object for selecting a good individual from the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getMaximumReached() methode from cEnviroment
	cout<<"pMaximumReached = cEnviroment::getMaximumReached(); "<<endl;
	pMaximumReached = cEnviroment::getMaximumReached();
	if ( pMaximumReached != NULL ){
	
		cout<<"The object for checking the maximum population size of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking the maximum population size of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getSelectIndividualToDelete() methode from cEnviroment
	cout<<"pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete(); "<<endl;
	pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete();
	if ( pSelectIndividualToDelete != NULL ){
	
		cout<<"The object for selecting a bad individual from the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a bad individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getOperatorFitnessAlgorithm() methode from cEnviroment
	cout<<"pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm(); "<<endl;
	pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm();
	if ( pOperatorFitnessAlgorithm != NULL ){
	
		cout<<"The operation fitness algorithm of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The operation fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getChoosOperator() methode from cEnviroment
	cout<<"pChoosOperator = cEnviroment::getChoosOperator(); "<<endl;
	pChoosOperator = cEnviroment::getChoosOperator();
	if ( pChoosOperator != NULL ){
	
		cout<<"The object for selecting a good operation for the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good operation for the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getResourceCheck() methode from cEnviroment
	cout<<"pResourceCheck = cEnviroment::getResourceCheck(); "<<endl;
	pResourceCheck = cEnviroment::getResourceCheck();
	if ( pResourceCheck != NULL ){
	
		cout<<"The object for checking if more operations could be started for the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking if more operations could be started for the enviroment is NULL."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cEnviroment with the end condition, init and object fitness object set"<<endl;
	
	cout<<"cEndConditionCheck endCondition; "<<endl;
	cEndConditionCheck endCondition;
	
	cout<<"endCondition.setMaxOperationCalls( 123456 ); "<<endl;
	endCondition.setMaxOperationCalls( 123456 );

	//check the setParameter() methode from cEnviroment
	cout<<"bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic, &endCondition );"<<endl;
	bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic, &endCondition );

	if ( bParameterSet ){
	
		cout<<"The parameter could be correctly set. "<<endl;
	}else{
		cerr<<"Error: The parameter couldn't be set."<<endl;
		iReturn++;
	}
	
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment != NULL ){
	
		cout<<"An instance of the enviroment could be correctly created. "<<endl;
	}else{
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
	}
	//check the getFitnessAlgorithm() methode from cEnviroment
	cout<<"pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm(); "<<endl;
	pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm();
	if ( pObjectFitnessAlgorithm != NULL ){
	
		if ( (fibObjectAlgorithmBasic.getWeightDistanceToOriginal() ==
				((cFibObjectFitnessBasicAlgorithm*)pObjectFitnessAlgorithm)->getWeightDistanceToOriginal()) &&
				(fibObjectAlgorithmBasic.getClassName() ==
				((cFibObjectFitnessBasicAlgorithm*)pObjectFitnessAlgorithm)->getClassName()) ){
			
			cout<<"The object fitness algorithm is correct. "<<endl;
		}else{
			cerr<<"Error: The object fitness algorithm is not correct."<<endl;
			iReturn++;
		}
		
	}else{
		cerr<<"Error: The object fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getInitEnviroment() methode from cEnviroment
	cout<<"pInitEnviroment = cEnviroment::getInitEnviroment(); "<<endl;
	pInitEnviroment = cEnviroment::getInitEnviroment();
	if ( pInitEnviroment != NULL ){
	
		cout<<"The object for initializising the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for initializising the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getEndConditionCheck() methode from cEnviroment
	cout<<"pEndConditionCheck = cEnviroment::getEndConditionCheck(); "<<endl;
	pEndConditionCheck = cEnviroment::getEndConditionCheck();
	if ( pEndConditionCheck != NULL ){
	
		if ( (endCondition.getMaxOperationCalls() ==
				pEndConditionCheck->getMaxOperationCalls()) ){
			
			cout<<"The object for the endcondition check of the enviroment is correct. "<<endl;
		}else{
			cerr<<"Error: The object for the endcondition check of the enviroment is not correct."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The object for the endcondition check of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getIndividualSelection() methode from cEnviroment
	cout<<"pIndividualSelection = cEnviroment::getIndividualSelection(); "<<endl;
	pIndividualSelection = cEnviroment::getIndividualSelection();
	if ( pIndividualSelection != NULL ){
	
		cout<<"The object for selecting a good individual from the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getMaximumReached() methode from cEnviroment
	cout<<"pMaximumReached = cEnviroment::getMaximumReached(); "<<endl;
	pMaximumReached = cEnviroment::getMaximumReached();
	if ( pMaximumReached != NULL ){
	
		cout<<"The object for checking the maximum population size of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking the maximum population size of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getSelectIndividualToDelete() methode from cEnviroment
	cout<<"pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete(); "<<endl;
	pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete();
	if ( pSelectIndividualToDelete != NULL ){
	
		cout<<"The object for selecting a bad individual from the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a bad individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getOperatorFitnessAlgorithm() methode from cEnviroment
	cout<<"pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm(); "<<endl;
	pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm();
	if ( pOperatorFitnessAlgorithm != NULL ){
	
		cout<<"The operation fitness algorithm of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The operation fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getChoosOperator() methode from cEnviroment
	cout<<"pChoosOperator = cEnviroment::getChoosOperator(); "<<endl;
	pChoosOperator = cEnviroment::getChoosOperator();
	if ( pChoosOperator != NULL ){
	
		cout<<"The object for selecting a good operation for the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good operation for the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getResourceCheck() methode from cEnviroment
	cout<<"pResourceCheck = cEnviroment::getResourceCheck(); "<<endl;
	pResourceCheck = cEnviroment::getResourceCheck();
	if ( pResourceCheck != NULL ){
	
		cout<<"The object for checking if more operations could be started for the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking if more operations could be started for the enviroment is NULL."<<endl;
		iReturn++;
	}
	
	if ( pEnviroment ){
		//check the OPERATION_DOMAIN methode from cEnviroment
		if ( pEnviroment->OPERATION_DOMAIN == "cFibIndividual" ){
		
			cout<<"The enviroment operation domain is correctly \"cFibIndividual\". "<<endl;
		}else{
			cerr<<"Error: The enviroment operation domain is "<< pEnviroment->OPERATION_DOMAIN <<
				" and not \"cFibIndividual\"."<<endl;
			iReturn++;
		}
		//check the getAlgorithmIdentifier() methode from cEnviroment
		if ( pEnviroment->getAlgorithmIdentifier() == ulAlgorithmId ){
		
			cout<<"The enviroment identifier is correctly "<<
				pEnviroment->getAlgorithmIdentifier() <<" . "<<endl;
		}else{
			cerr<<"Error: The enviroment identifier is "<<
				pEnviroment->getAlgorithmIdentifier() <<", but should be "<< ulAlgorithmId <<" ."<<endl;
			iReturn++;
		}
		//check the getCpuRunTime() methode from cEnviroment
		if ( pEnviroment->getCpuRunTime() == 0.0 ){
		
			cout<<"The enviroment cpu runtime is correctly "<<
				pEnviroment->getCpuRunTime() <<" s . "<<endl;
		}else{
			cerr<<"Error: The enviroment cpu runtime is "<<
				pEnviroment->getCpuRunTime() <<" s , but should be "<< 0.0 <<" s ."<<endl;
			iReturn++;
		}
		//check the getLastStartTime() methode from cEnviroment
		if ( pEnviroment->getLastStartTime() == 0 ){
		
			cout<<"The enviroment last start time is correctly "<<
				pEnviroment->getLastStartTime() <<"  . "<<endl;
		}else{
			cerr<<"Error: The enviroment last start time is "<<
				pEnviroment->getLastStartTime() <<"  , but should be "<< 0 <<" ."<<endl;
			iReturn++;
		}
		//check the getFirstStartTime() methode from cEnviroment
		if ( pEnviroment->getFirstStartTime() == 0 ){
		
			cout<<"The enviroment first start time is correctly "<<
				pEnviroment->getFirstStartTime() <<". "<<endl;
		}else{
			cerr<<"Error: The enviroment first start time is "<<
				pEnviroment->getFirstStartTime() <<", but should be "<< 0 <<" ."<<endl;
			iReturn++;
		}
		delete pEnviroment;
		ulAlgorithmId++;
		
		iReturn += checkIfEnviromentIsEmpty();
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cEnviroment with the good individual selection, init and object fitness object set"<<endl;
	
	cout<<"cIndividualSelectionTest individualSelection; "<<endl;
	cIndividualSelectionTest individualSelection;

	//check the setParameter() methode from cEnviroment
	cout<<"bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic,"<<
		"NULL, &individualSelectionWeel );"<<endl;
	bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic,
		NULL, &individualSelection );

	if ( bParameterSet ){
	
		cout<<"The parameter could be correctly set. "<<endl;
	}else{
		cerr<<"Error: The parameter couldn't be set."<<endl;
		iReturn++;
	}
	
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment != NULL ){
	
		cout<<"An instance of the enviroment could be correctly created. "<<endl;
	}else{
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
	}
	//check the getFitnessAlgorithm() methode from cEnviroment
	cout<<"pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm(); "<<endl;
	pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm();
	if ( pObjectFitnessAlgorithm != NULL ){
	
		if ( (fibObjectAlgorithmBasic.getWeightDistanceToOriginal() ==
				((cFibObjectFitnessBasicAlgorithm*)pObjectFitnessAlgorithm)->getWeightDistanceToOriginal()) &&
				(fibObjectAlgorithmBasic.getClassName() ==
				((cFibObjectFitnessBasicAlgorithm*)pObjectFitnessAlgorithm)->getClassName()) ){
			
			cout<<"The object fitness algorithm is correct. "<<endl;
		}else{
			cerr<<"Error: The object fitness algorithm is not correct."<<endl;
			iReturn++;
		}
		
	}else{
		cerr<<"Error: The object fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getInitEnviroment() methode from cEnviroment
	cout<<"pInitEnviroment = cEnviroment::getInitEnviroment(); "<<endl;
	pInitEnviroment = cEnviroment::getInitEnviroment();
	if ( pInitEnviroment != NULL ){
	
		cout<<"The object for initializising the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for initializising the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getEndConditionCheck() methode from cEnviroment
	cout<<"pEndConditionCheck = cEnviroment::getEndConditionCheck(); "<<endl;
	pEndConditionCheck = cEnviroment::getEndConditionCheck();
	if ( pEndConditionCheck != NULL ){
		
		cout<<"The object for the endcondition check of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for the endcondition check of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getIndividualSelection() methode from cEnviroment
	cout<<"pIndividualSelection = cEnviroment::getIndividualSelection(); "<<endl;
	pIndividualSelection = cEnviroment::getIndividualSelection();
	if ( pIndividualSelection != NULL ){

		if ( (individualSelection.getIndividualIdentifier() ==
				pIndividualSelection->getIndividualIdentifier()) ){
			
			cout<<"The object for selecting a good individual from the enviroment is correct. "<<endl;
		}else{
			cerr<<"Error: The object for selecting a good individual from the enviroment is not correct."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The object for selecting a good individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getMaximumReached() methode from cEnviroment
	cout<<"pMaximumReached = cEnviroment::getMaximumReached(); "<<endl;
	pMaximumReached = cEnviroment::getMaximumReached();
	if ( pMaximumReached != NULL ){
	
		cout<<"The object for checking the maximum population size of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking the maximum population size of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getSelectIndividualToDelete() methode from cEnviroment
	cout<<"pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete(); "<<endl;
	pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete();
	if ( pSelectIndividualToDelete != NULL ){
	
		cout<<"The object for selecting a bad individual from the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a bad individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getOperatorFitnessAlgorithm() methode from cEnviroment
	cout<<"pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm(); "<<endl;
	pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm();
	if ( pOperatorFitnessAlgorithm != NULL ){
	
		cout<<"The operation fitness algorithm of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The operation fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getChoosOperator() methode from cEnviroment
	cout<<"pChoosOperator = cEnviroment::getChoosOperator(); "<<endl;
	pChoosOperator = cEnviroment::getChoosOperator();
	if ( pChoosOperator != NULL ){
	
		cout<<"The object for selecting a good operation for the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good operation for the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getResourceCheck() methode from cEnviroment
	cout<<"pResourceCheck = cEnviroment::getResourceCheck(); "<<endl;
	pResourceCheck = cEnviroment::getResourceCheck();
	if ( pResourceCheck != NULL ){
	
		cout<<"The object for checking if more operations could be started for the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking if more operations could be started for the enviroment is NULL."<<endl;
		iReturn++;
	}
	
	if ( pEnviroment ){
		//check the OPERATION_DOMAIN methode from cEnviroment
		if ( pEnviroment->OPERATION_DOMAIN == "cFibIndividual" ){
		
			cout<<"The enviroment operation domain is correctly \"cFibIndividual\". "<<endl;
		}else{
			cerr<<"Error: The enviroment operation domain is "<< pEnviroment->OPERATION_DOMAIN <<
				" and not \"cFibIndividual\"."<<endl;
			iReturn++;
		}
		//check the getAlgorithmIdentifier() methode from cEnviroment
		if ( pEnviroment->getAlgorithmIdentifier() == ulAlgorithmId ){
		
			cout<<"The enviroment identifier is correctly "<<
				pEnviroment->getAlgorithmIdentifier() <<" . "<<endl;
		}else{
			cerr<<"Error: The enviroment identifier is "<<
				pEnviroment->getAlgorithmIdentifier() <<", but should be "<< ulAlgorithmId <<" ."<<endl;
			iReturn++;
		}
		//check the getCpuRunTime() methode from cEnviroment
		if ( pEnviroment->getCpuRunTime() == 0.0 ){
		
			cout<<"The enviroment cpu runtime is correctly "<<
				pEnviroment->getCpuRunTime() <<" s . "<<endl;
		}else{
			cerr<<"Error: The enviroment cpu runtime is "<<
				pEnviroment->getCpuRunTime() <<" s , but should be "<< 0.0 <<" s ."<<endl;
			iReturn++;
		}
		//check the getLastStartTime() methode from cEnviroment
		if ( pEnviroment->getLastStartTime() == 0 ){
		
			cout<<"The enviroment last start time is correctly "<<
				pEnviroment->getLastStartTime() <<"  . "<<endl;
		}else{
			cerr<<"Error: The enviroment last start time is "<<
				pEnviroment->getLastStartTime() <<"  , but should be "<< 0 <<" ."<<endl;
			iReturn++;
		}
		//check the getFirstStartTime() methode from cEnviroment
		if ( pEnviroment->getFirstStartTime() == 0 ){
		
			cout<<"The enviroment first start time is correctly "<<
				pEnviroment->getFirstStartTime() <<". "<<endl;
		}else{
			cerr<<"Error: The enviroment first start time is "<<
				pEnviroment->getFirstStartTime() <<", but should be "<< 0 <<" ."<<endl;
			iReturn++;
		}
		delete pEnviroment;
		ulAlgorithmId++;
		
		iReturn += checkIfEnviromentIsEmpty();
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cEnviroment with the maximum population test, init and object fitness object set"<<endl;
	
	cout<<"cMaximumReachedTest maximumPopulation; "<<endl;
	cMaximumReachedTest maximumPopulation;

	//check the setParameter() methode from cEnviroment
	cout<<"bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic,"<<
		"NULL, NULL, &maximumPopulation );"<<endl;
	bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic,
		NULL, NULL, &maximumPopulation );

	if ( bParameterSet ){
	
		cout<<"The parameter could be correctly set. "<<endl;
	}else{
		cerr<<"Error: The parameter couldn't be set."<<endl;
		iReturn++;
	}
	
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment != NULL ){
	
		cout<<"An instance of the enviroment could be correctly created. "<<endl;
	}else{
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
	}
	//check the getFitnessAlgorithm() methode from cEnviroment
	cout<<"pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm(); "<<endl;
	pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm();
	if ( pObjectFitnessAlgorithm != NULL ){
	
		if ( (fibObjectAlgorithmBasic.getWeightDistanceToOriginal() ==
				((cFibObjectFitnessBasicAlgorithm*)pObjectFitnessAlgorithm)->getWeightDistanceToOriginal()) &&
				(fibObjectAlgorithmBasic.getClassName() ==
				((cFibObjectFitnessBasicAlgorithm*)pObjectFitnessAlgorithm)->getClassName()) ){
			
			cout<<"The object fitness algorithm is correct. "<<endl;
		}else{
			cerr<<"Error: The object fitness algorithm is not correct."<<endl;
			iReturn++;
		}
		
	}else{
		cerr<<"Error: The object fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getInitEnviroment() methode from cEnviroment
	cout<<"pInitEnviroment = cEnviroment::getInitEnviroment(); "<<endl;
	pInitEnviroment = cEnviroment::getInitEnviroment();
	if ( pInitEnviroment != NULL ){
	
		cout<<"The object for initializising the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for initializising the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getEndConditionCheck() methode from cEnviroment
	cout<<"pEndConditionCheck = cEnviroment::getEndConditionCheck(); "<<endl;
	pEndConditionCheck = cEnviroment::getEndConditionCheck();
	if ( pEndConditionCheck != NULL ){
		
		cout<<"The object for the endcondition check of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for the endcondition check of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getIndividualSelection() methode from cEnviroment
	cout<<"pIndividualSelection = cEnviroment::getIndividualSelection(); "<<endl;
	pIndividualSelection = cEnviroment::getIndividualSelection();
	if ( pIndividualSelection != NULL ){

		cout<<"The object for selecting a good individual from the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getMaximumReached() methode from cEnviroment
	cout<<"pMaximumReached = cEnviroment::getMaximumReached(); "<<endl;
	pMaximumReached = cEnviroment::getMaximumReached();
	if ( pMaximumReached != NULL ){
	
		if ( (maximumPopulation.maximumReached() ==
				pMaximumReached->maximumReached()) ){
			
			cout<<"The object for checking the maximum population size of the enviroment is correct. "<<endl;
		}else{
			cerr<<"Error: The object for checking the maximum population size of the enviroment is not correct."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The object for checking the maximum population size of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getSelectIndividualToDelete() methode from cEnviroment
	cout<<"pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete(); "<<endl;
	pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete();
	if ( pSelectIndividualToDelete != NULL ){
	
		cout<<"The object for selecting a bad individual from the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a bad individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getOperatorFitnessAlgorithm() methode from cEnviroment
	cout<<"pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm(); "<<endl;
	pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm();
	if ( pOperatorFitnessAlgorithm != NULL ){
	
		cout<<"The operation fitness algorithm of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The operation fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getChoosOperator() methode from cEnviroment
	cout<<"pChoosOperator = cEnviroment::getChoosOperator(); "<<endl;
	pChoosOperator = cEnviroment::getChoosOperator();
	if ( pChoosOperator != NULL ){
	
		cout<<"The object for selecting a good operation for the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good operation for the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getResourceCheck() methode from cEnviroment
	cout<<"pResourceCheck = cEnviroment::getResourceCheck(); "<<endl;
	pResourceCheck = cEnviroment::getResourceCheck();
	if ( pResourceCheck != NULL ){
	
		cout<<"The object for checking if more operations could be started for the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking if more operations could be started for the enviroment is NULL."<<endl;
		iReturn++;
	}
	
	if ( pEnviroment ){
		//check the OPERATION_DOMAIN methode from cEnviroment
		if ( pEnviroment->OPERATION_DOMAIN == "cFibIndividual" ){
		
			cout<<"The enviroment operation domain is correctly \"cFibIndividual\". "<<endl;
		}else{
			cerr<<"Error: The enviroment operation domain is "<< pEnviroment->OPERATION_DOMAIN <<
				" and not \"cFibIndividual\"."<<endl;
			iReturn++;
		}
		//check the getAlgorithmIdentifier() methode from cEnviroment
		if ( pEnviroment->getAlgorithmIdentifier() == ulAlgorithmId ){
		
			cout<<"The enviroment identifier is correctly "<<
				pEnviroment->getAlgorithmIdentifier() <<" . "<<endl;
		}else{
			cerr<<"Error: The enviroment identifier is "<<
				pEnviroment->getAlgorithmIdentifier() <<", but should be "<< ulAlgorithmId <<" ."<<endl;
			iReturn++;
		}
		//check the getCpuRunTime() methode from cEnviroment
		if ( pEnviroment->getCpuRunTime() == 0.0 ){
		
			cout<<"The enviroment cpu runtime is correctly "<<
				pEnviroment->getCpuRunTime() <<" s . "<<endl;
		}else{
			cerr<<"Error: The enviroment cpu runtime is "<<
				pEnviroment->getCpuRunTime() <<" s , but should be "<< 0.0 <<" s ."<<endl;
			iReturn++;
		}
		//check the getLastStartTime() methode from cEnviroment
		if ( pEnviroment->getLastStartTime() == 0 ){
		
			cout<<"The enviroment last start time is correctly "<<
				pEnviroment->getLastStartTime() <<"  . "<<endl;
		}else{
			cerr<<"Error: The enviroment last start time is "<<
				pEnviroment->getLastStartTime() <<"  , but should be "<< 0 <<" ."<<endl;
			iReturn++;
		}
		//check the getFirstStartTime() methode from cEnviroment
		if ( pEnviroment->getFirstStartTime() == 0 ){
		
			cout<<"The enviroment first start time is correctly "<<
				pEnviroment->getFirstStartTime() <<". "<<endl;
		}else{
			cerr<<"Error: The enviroment first start time is "<<
				pEnviroment->getFirstStartTime() <<", but should be "<< 0 <<" ."<<endl;
			iReturn++;
		}
		delete pEnviroment;
		ulAlgorithmId++;
		
		iReturn += checkIfEnviromentIsEmpty();
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cEnviroment with the individual to delete selection, init and object fitness object set"<<endl;
	
	cout<<"cSelectIndividualToDeleteTest selectIndividualToDelete; "<<endl;
	cSelectIndividualToDeleteTest selectIndividualToDelete;

	//check the setParameter() methode from cEnviroment
	cout<<"bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic,"<<
		"NULL, NULL, NULL, &selectIndividualToDelete );"<<endl;
	bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic,
		NULL, NULL, NULL, &selectIndividualToDelete );

	if ( bParameterSet ){
	
		cout<<"The parameter could be correctly set. "<<endl;
	}else{
		cerr<<"Error: The parameter couldn't be set."<<endl;
		iReturn++;
	}
	
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment != NULL ){
	
		cout<<"An instance of the enviroment could be correctly created. "<<endl;
	}else{
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
	}
	//check the getFitnessAlgorithm() methode from cEnviroment
	cout<<"pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm(); "<<endl;
	pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm();
	if ( pObjectFitnessAlgorithm != NULL ){
	
		if ( (fibObjectAlgorithmBasic.getWeightDistanceToOriginal() ==
				((cFibObjectFitnessBasicAlgorithm*)pObjectFitnessAlgorithm)->getWeightDistanceToOriginal()) &&
				(fibObjectAlgorithmBasic.getClassName() ==
				((cFibObjectFitnessBasicAlgorithm*)pObjectFitnessAlgorithm)->getClassName()) ){
			
			cout<<"The object fitness algorithm is correct. "<<endl;
		}else{
			cerr<<"Error: The object fitness algorithm is not correct."<<endl;
			iReturn++;
		}
		
	}else{
		cerr<<"Error: The object fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getInitEnviroment() methode from cEnviroment
	cout<<"pInitEnviroment = cEnviroment::getInitEnviroment(); "<<endl;
	pInitEnviroment = cEnviroment::getInitEnviroment();
	if ( pInitEnviroment != NULL ){
	
		cout<<"The object for initializising the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for initializising the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getEndConditionCheck() methode from cEnviroment
	cout<<"pEndConditionCheck = cEnviroment::getEndConditionCheck(); "<<endl;
	pEndConditionCheck = cEnviroment::getEndConditionCheck();
	if ( pEndConditionCheck != NULL ){
		
		cout<<"The object for the endcondition check of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for the endcondition check of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getIndividualSelection() methode from cEnviroment
	cout<<"pIndividualSelection = cEnviroment::getIndividualSelection(); "<<endl;
	pIndividualSelection = cEnviroment::getIndividualSelection();
	if ( pIndividualSelection != NULL ){

		cout<<"The object for selecting a good individual from the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getMaximumReached() methode from cEnviroment
	cout<<"pMaximumReached = cEnviroment::getMaximumReached(); "<<endl;
	pMaximumReached = cEnviroment::getMaximumReached();
	if ( pMaximumReached != NULL ){
	
		cout<<"The object for checking the maximum population size of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking the maximum population size of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getSelectIndividualToDelete() methode from cEnviroment
	cout<<"pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete(); "<<endl;
	pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete();
	if ( pSelectIndividualToDelete != NULL ){
	
		if ( (selectIndividualToDelete.getIndividualIdentifier() ==
				pSelectIndividualToDelete->getIndividualIdentifier()) ){
			
			cout<<"The object for selecting a bad individual from the enviroment is correct. "<<endl;
		}else{
			cerr<<"Error: The object for selecting a bad individual from the enviroment is not correct."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The object for selecting a bad individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getOperatorFitnessAlgorithm() methode from cEnviroment
	cout<<"pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm(); "<<endl;
	pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm();
	if ( pOperatorFitnessAlgorithm != NULL ){
	
		cout<<"The operation fitness algorithm of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The operation fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getChoosOperator() methode from cEnviroment
	cout<<"pChoosOperator = cEnviroment::getChoosOperator(); "<<endl;
	pChoosOperator = cEnviroment::getChoosOperator();
	if ( pChoosOperator != NULL ){
	
		cout<<"The object for selecting a good operation for the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good operation for the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getResourceCheck() methode from cEnviroment
	cout<<"pResourceCheck = cEnviroment::getResourceCheck(); "<<endl;
	pResourceCheck = cEnviroment::getResourceCheck();
	if ( pResourceCheck != NULL ){
	
		cout<<"The object for checking if more operations could be started for the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking if more operations could be started for the enviroment is NULL."<<endl;
		iReturn++;
	}
	
	if ( pEnviroment ){
		//check the OPERATION_DOMAIN methode from cEnviroment
		if ( pEnviroment->OPERATION_DOMAIN == "cFibIndividual" ){
		
			cout<<"The enviroment operation domain is correctly \"cFibIndividual\". "<<endl;
		}else{
			cerr<<"Error: The enviroment operation domain is "<< pEnviroment->OPERATION_DOMAIN <<
				" and not \"cFibIndividual\"."<<endl;
			iReturn++;
		}
		//check the getAlgorithmIdentifier() methode from cEnviroment
		if ( pEnviroment->getAlgorithmIdentifier() == ulAlgorithmId ){
		
			cout<<"The enviroment identifier is correctly "<<
				pEnviroment->getAlgorithmIdentifier() <<" . "<<endl;
		}else{
			cerr<<"Error: The enviroment identifier is "<<
				pEnviroment->getAlgorithmIdentifier() <<", but should be "<< ulAlgorithmId <<" ."<<endl;
			iReturn++;
		}
		//check the getCpuRunTime() methode from cEnviroment
		if ( pEnviroment->getCpuRunTime() == 0.0 ){
		
			cout<<"The enviroment cpu runtime is correctly "<<
				pEnviroment->getCpuRunTime() <<" s . "<<endl;
		}else{
			cerr<<"Error: The enviroment cpu runtime is "<<
				pEnviroment->getCpuRunTime() <<" s , but should be "<< 0.0 <<" s ."<<endl;
			iReturn++;
		}
		//check the getLastStartTime() methode from cEnviroment
		if ( pEnviroment->getLastStartTime() == 0 ){
		
			cout<<"The enviroment last start time is correctly "<<
				pEnviroment->getLastStartTime() <<"  . "<<endl;
		}else{
			cerr<<"Error: The enviroment last start time is "<<
				pEnviroment->getLastStartTime() <<"  , but should be "<< 0 <<" ."<<endl;
			iReturn++;
		}
		//check the getFirstStartTime() methode from cEnviroment
		if ( pEnviroment->getFirstStartTime() == 0 ){
		
			cout<<"The enviroment first start time is correctly "<<
				pEnviroment->getFirstStartTime() <<". "<<endl;
		}else{
			cerr<<"Error: The enviroment first start time is "<<
				pEnviroment->getFirstStartTime() <<", but should be "<< 0 <<" ."<<endl;
			iReturn++;
		}
		delete pEnviroment;
		ulAlgorithmId++;
		
		iReturn += checkIfEnviromentIsEmpty();
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cEnviroment with the operation fitness algorithm, init and object fitness object set"<<endl;
	
	cout<<"cOperatorFitnessAlgorithmBasic operatorFitness( 54.32 ); "<<endl;
	cOperatorFitnessAlgorithmBasic operatorFitness( 54.32 );

	//check the setParameter() methode from cEnviroment
	cout<<"bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic,"<<
		"NULL, NULL, NULL, NULL, &operatorFitness );"<<endl;
	bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic,
		NULL, NULL, NULL, NULL, &operatorFitness );

	if ( bParameterSet ){
	
		cout<<"The parameter could be correctly set. "<<endl;
	}else{
		cerr<<"Error: The parameter couldn't be set."<<endl;
		iReturn++;
	}
	
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment != NULL ){
	
		cout<<"An instance of the enviroment could be correctly created. "<<endl;
	}else{
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
	}
	//check the getFitnessAlgorithm() methode from cEnviroment
	cout<<"pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm(); "<<endl;
	pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm();
	if ( pObjectFitnessAlgorithm != NULL ){
	
		if ( (fibObjectAlgorithmBasic.getWeightDistanceToOriginal() ==
				((cFibObjectFitnessBasicAlgorithm*)pObjectFitnessAlgorithm)->getWeightDistanceToOriginal()) &&
				(fibObjectAlgorithmBasic.getClassName() ==
				((cFibObjectFitnessBasicAlgorithm*)pObjectFitnessAlgorithm)->getClassName()) ){
			
			cout<<"The object fitness algorithm is correct. "<<endl;
		}else{
			cerr<<"Error: The object fitness algorithm is not correct."<<endl;
			iReturn++;
		}
		
	}else{
		cerr<<"Error: The object fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getInitEnviroment() methode from cEnviroment
	cout<<"pInitEnviroment = cEnviroment::getInitEnviroment(); "<<endl;
	pInitEnviroment = cEnviroment::getInitEnviroment();
	if ( pInitEnviroment != NULL ){
	
		cout<<"The object for initializising the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for initializising the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getEndConditionCheck() methode from cEnviroment
	cout<<"pEndConditionCheck = cEnviroment::getEndConditionCheck(); "<<endl;
	pEndConditionCheck = cEnviroment::getEndConditionCheck();
	if ( pEndConditionCheck != NULL ){
		
		cout<<"The object for the endcondition check of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for the endcondition check of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getIndividualSelection() methode from cEnviroment
	cout<<"pIndividualSelection = cEnviroment::getIndividualSelection(); "<<endl;
	pIndividualSelection = cEnviroment::getIndividualSelection();
	if ( pIndividualSelection != NULL ){

		cout<<"The object for selecting a good individual from the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getMaximumReached() methode from cEnviroment
	cout<<"pMaximumReached = cEnviroment::getMaximumReached(); "<<endl;
	pMaximumReached = cEnviroment::getMaximumReached();
	if ( pMaximumReached != NULL ){
	
		cout<<"The object for checking the maximum population size of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking the maximum population size of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getSelectIndividualToDelete() methode from cEnviroment
	cout<<"pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete(); "<<endl;
	pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete();
	if ( pSelectIndividualToDelete != NULL ){
	
		cout<<"The object for selecting a bad individual from the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a bad individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getOperatorFitnessAlgorithm() methode from cEnviroment
	cout<<"pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm(); "<<endl;
	pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm();
	if ( pOperatorFitnessAlgorithm != NULL ){
	
		if ( (operatorFitness.getFaktorAllFitnessPart() ==
				((cOperatorFitnessAlgorithmBasic*)pOperatorFitnessAlgorithm)->getFaktorAllFitnessPart()) ){
			
			cout<<"The operation fitness algorithm of the enviroment is correct. "<<endl;
		}else{
			cerr<<"Error: The operation fitness algorithm of the enviroment is not correct."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The operation fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getChoosOperator() methode from cEnviroment
	cout<<"pChoosOperator = cEnviroment::getChoosOperator(); "<<endl;
	pChoosOperator = cEnviroment::getChoosOperator();
	if ( pChoosOperator != NULL ){
	
		cout<<"The object for selecting a good operation for the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good operation for the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getResourceCheck() methode from cEnviroment
	cout<<"pResourceCheck = cEnviroment::getResourceCheck(); "<<endl;
	pResourceCheck = cEnviroment::getResourceCheck();
	if ( pResourceCheck != NULL ){
	
		cout<<"The object for checking if more operations could be started for the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking if more operations could be started for the enviroment is NULL."<<endl;
		iReturn++;
	}
	
	if ( pEnviroment ){
		//check the OPERATION_DOMAIN methode from cEnviroment
		if ( pEnviroment->OPERATION_DOMAIN == "cFibIndividual" ){
		
			cout<<"The enviroment operation domain is correctly \"cFibIndividual\". "<<endl;
		}else{
			cerr<<"Error: The enviroment operation domain is "<< pEnviroment->OPERATION_DOMAIN <<
				" and not \"cFibIndividual\"."<<endl;
			iReturn++;
		}
		//check the getAlgorithmIdentifier() methode from cEnviroment
		if ( pEnviroment->getAlgorithmIdentifier() == ulAlgorithmId ){
		
			cout<<"The enviroment identifier is correctly "<<
				pEnviroment->getAlgorithmIdentifier() <<" . "<<endl;
		}else{
			cerr<<"Error: The enviroment identifier is "<<
				pEnviroment->getAlgorithmIdentifier() <<", but should be "<< ulAlgorithmId <<" ."<<endl;
			iReturn++;
		}
		//check the getCpuRunTime() methode from cEnviroment
		if ( pEnviroment->getCpuRunTime() == 0.0 ){
		
			cout<<"The enviroment cpu runtime is correctly "<<
				pEnviroment->getCpuRunTime() <<" s . "<<endl;
		}else{
			cerr<<"Error: The enviroment cpu runtime is "<<
				pEnviroment->getCpuRunTime() <<" s , but should be "<< 0.0 <<" s ."<<endl;
			iReturn++;
		}
		//check the getLastStartTime() methode from cEnviroment
		if ( pEnviroment->getLastStartTime() == 0 ){
		
			cout<<"The enviroment last start time is correctly "<<
				pEnviroment->getLastStartTime() <<"  . "<<endl;
		}else{
			cerr<<"Error: The enviroment last start time is "<<
				pEnviroment->getLastStartTime() <<"  , but should be "<< 0 <<" ."<<endl;
			iReturn++;
		}
		//check the getFirstStartTime() methode from cEnviroment
		if ( pEnviroment->getFirstStartTime() == 0 ){
		
			cout<<"The enviroment first start time is correctly "<<
				pEnviroment->getFirstStartTime() <<". "<<endl;
		}else{
			cerr<<"Error: The enviroment first start time is "<<
				pEnviroment->getFirstStartTime() <<", but should be "<< 0 <<" ."<<endl;
			iReturn++;
		}
		delete pEnviroment;
		ulAlgorithmId++;
		
		iReturn += checkIfEnviromentIsEmpty();
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cEnviroment with the choos operation algorithm, init and object fitness object set"<<endl;
	
	cout<<"cChoosOperatorTest choosOperator; "<<endl;
	cChoosOperatorTest choosOperator;

	//check the setParameter() methode from cEnviroment
	cout<<"bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic,"<<
		"NULL, NULL, NULL, NULL, NULL, &choosOperator );"<<endl;
	bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic,
		NULL, NULL, NULL, NULL, NULL, &choosOperator );

	if ( bParameterSet ){
	
		cout<<"The parameter could be correctly set. "<<endl;
	}else{
		cerr<<"Error: The parameter couldn't be set."<<endl;
		iReturn++;
	}
	
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment != NULL ){
	
		cout<<"An instance of the enviroment could be correctly created. "<<endl;
	}else{
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
	}
	//check the getFitnessAlgorithm() methode from cEnviroment
	cout<<"pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm(); "<<endl;
	pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm();
	if ( pObjectFitnessAlgorithm != NULL ){
	
		if ( (fibObjectAlgorithmBasic.getWeightDistanceToOriginal() ==
				((cFibObjectFitnessBasicAlgorithm*)pObjectFitnessAlgorithm)->getWeightDistanceToOriginal()) &&
				(fibObjectAlgorithmBasic.getClassName() ==
				((cFibObjectFitnessBasicAlgorithm*)pObjectFitnessAlgorithm)->getClassName()) ){
			
			cout<<"The object fitness algorithm is correct. "<<endl;
		}else{
			cerr<<"Error: The object fitness algorithm is not correct."<<endl;
			iReturn++;
		}
		
	}else{
		cerr<<"Error: The object fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getInitEnviroment() methode from cEnviroment
	cout<<"pInitEnviroment = cEnviroment::getInitEnviroment(); "<<endl;
	pInitEnviroment = cEnviroment::getInitEnviroment();
	if ( pInitEnviroment != NULL ){
	
		cout<<"The object for initializising the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for initializising the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getEndConditionCheck() methode from cEnviroment
	cout<<"pEndConditionCheck = cEnviroment::getEndConditionCheck(); "<<endl;
	pEndConditionCheck = cEnviroment::getEndConditionCheck();
	if ( pEndConditionCheck != NULL ){
		
		cout<<"The object for the endcondition check of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for the endcondition check of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getIndividualSelection() methode from cEnviroment
	cout<<"pIndividualSelection = cEnviroment::getIndividualSelection(); "<<endl;
	pIndividualSelection = cEnviroment::getIndividualSelection();
	if ( pIndividualSelection != NULL ){

		cout<<"The object for selecting a good individual from the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getMaximumReached() methode from cEnviroment
	cout<<"pMaximumReached = cEnviroment::getMaximumReached(); "<<endl;
	pMaximumReached = cEnviroment::getMaximumReached();
	if ( pMaximumReached != NULL ){
	
		cout<<"The object for checking the maximum population size of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking the maximum population size of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getSelectIndividualToDelete() methode from cEnviroment
	cout<<"pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete(); "<<endl;
	pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete();
	if ( pSelectIndividualToDelete != NULL ){
	
		cout<<"The object for selecting a bad individual from the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a bad individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getOperatorFitnessAlgorithm() methode from cEnviroment
	cout<<"pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm(); "<<endl;
	pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm();
	if ( pOperatorFitnessAlgorithm != NULL ){
	
		cout<<"The operation fitness algorithm of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The operation fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getChoosOperator() methode from cEnviroment
	cout<<"pChoosOperator = cEnviroment::getChoosOperator(); "<<endl;
	pChoosOperator = cEnviroment::getChoosOperator();
	if ( pChoosOperator != NULL ){
	
		if ( (choosOperator.choosOperator() ==
				pChoosOperator->choosOperator()) ){
			
			cout<<"The object for selecting a good operation for the enviroment is correct. "<<endl;
		}else{
			cerr<<"Error: The object for selecting a good operation for the enviroment is not correct."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The object for selecting a good operation for the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getResourceCheck() methode from cEnviroment
	cout<<"pResourceCheck = cEnviroment::getResourceCheck(); "<<endl;
	pResourceCheck = cEnviroment::getResourceCheck();
	if ( pResourceCheck != NULL ){
	
		cout<<"The object for checking if more operations could be started for the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking if more operations could be started for the enviroment is NULL."<<endl;
		iReturn++;
	}
	
	if ( pEnviroment ){
		//check the OPERATION_DOMAIN methode from cEnviroment
		if ( pEnviroment->OPERATION_DOMAIN == "cFibIndividual" ){
		
			cout<<"The enviroment operation domain is correctly \"cFibIndividual\". "<<endl;
		}else{
			cerr<<"Error: The enviroment operation domain is "<< pEnviroment->OPERATION_DOMAIN <<
				" and not \"cFibIndividual\"."<<endl;
			iReturn++;
		}
		//check the getAlgorithmIdentifier() methode from cEnviroment
		if ( pEnviroment->getAlgorithmIdentifier() == ulAlgorithmId ){
		
			cout<<"The enviroment identifier is correctly "<<
				pEnviroment->getAlgorithmIdentifier() <<" . "<<endl;
		}else{
			cerr<<"Error: The enviroment identifier is "<<
				pEnviroment->getAlgorithmIdentifier() <<", but should be "<< ulAlgorithmId <<" ."<<endl;
			iReturn++;
		}
		//check the getCpuRunTime() methode from cEnviroment
		if ( pEnviroment->getCpuRunTime() == 0.0 ){
		
			cout<<"The enviroment cpu runtime is correctly "<<
				pEnviroment->getCpuRunTime() <<" s . "<<endl;
		}else{
			cerr<<"Error: The enviroment cpu runtime is "<<
				pEnviroment->getCpuRunTime() <<" s , but should be "<< 0.0 <<" s ."<<endl;
			iReturn++;
		}
		//check the getLastStartTime() methode from cEnviroment
		if ( pEnviroment->getLastStartTime() == 0 ){
		
			cout<<"The enviroment last start time is correctly "<<
				pEnviroment->getLastStartTime() <<"  . "<<endl;
		}else{
			cerr<<"Error: The enviroment last start time is "<<
				pEnviroment->getLastStartTime() <<"  , but should be "<< 0 <<" ."<<endl;
			iReturn++;
		}
		//check the getFirstStartTime() methode from cEnviroment
		if ( pEnviroment->getFirstStartTime() == 0 ){
		
			cout<<"The enviroment first start time is correctly "<<
				pEnviroment->getFirstStartTime() <<". "<<endl;
		}else{
			cerr<<"Error: The enviroment first start time is "<<
				pEnviroment->getFirstStartTime() <<", but should be "<< 0 <<" ."<<endl;
			iReturn++;
		}
		delete pEnviroment;
		ulAlgorithmId++;
		
		iReturn += checkIfEnviromentIsEmpty();
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cEnviroment with the resource check, init and object fitness object set"<<endl;
	
	cout<<"cResourceCheckTest resourceCheck; "<<endl;
	cResourceCheckTest resourceCheck;

	//check the setParameter() methode from cEnviroment
	cout<<"bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic,"<<
		"NULL, NULL, NULL, NULL, NULL, NULL, &resourceCheck );"<<endl;
	bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic,
		NULL, NULL, NULL, NULL, NULL, NULL, &resourceCheck );

	if ( bParameterSet ){
	
		cout<<"The parameter could be correctly set. "<<endl;
	}else{
		cerr<<"Error: The parameter couldn't be set."<<endl;
		iReturn++;
	}
	
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment != NULL ){
	
		cout<<"An instance of the enviroment could be correctly created. "<<endl;
	}else{
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
	}
	//check the getFitnessAlgorithm() methode from cEnviroment
	cout<<"pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm(); "<<endl;
	pObjectFitnessAlgorithm = cEnviroment::getFitnessAlgorithm();
	if ( pObjectFitnessAlgorithm != NULL ){
	
		if ( (fibObjectAlgorithmBasic.getWeightDistanceToOriginal() ==
				((cFibObjectFitnessBasicAlgorithm*)pObjectFitnessAlgorithm)->getWeightDistanceToOriginal()) &&
				(fibObjectAlgorithmBasic.getClassName() ==
				((cFibObjectFitnessBasicAlgorithm*)pObjectFitnessAlgorithm)->getClassName()) ){
			
			cout<<"The object fitness algorithm is correct. "<<endl;
		}else{
			cerr<<"Error: The object fitness algorithm is not correct."<<endl;
			iReturn++;
		}
		
	}else{
		cerr<<"Error: The object fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getInitEnviroment() methode from cEnviroment
	cout<<"pInitEnviroment = cEnviroment::getInitEnviroment(); "<<endl;
	pInitEnviroment = cEnviroment::getInitEnviroment();
	if ( pInitEnviroment != NULL ){
	
		cout<<"The object for initializising the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for initializising the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getEndConditionCheck() methode from cEnviroment
	cout<<"pEndConditionCheck = cEnviroment::getEndConditionCheck(); "<<endl;
	pEndConditionCheck = cEnviroment::getEndConditionCheck();
	if ( pEndConditionCheck != NULL ){
		
		cout<<"The object for the endcondition check of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for the endcondition check of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getIndividualSelection() methode from cEnviroment
	cout<<"pIndividualSelection = cEnviroment::getIndividualSelection(); "<<endl;
	pIndividualSelection = cEnviroment::getIndividualSelection();
	if ( pIndividualSelection != NULL ){

		cout<<"The object for selecting a good individual from the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getMaximumReached() methode from cEnviroment
	cout<<"pMaximumReached = cEnviroment::getMaximumReached(); "<<endl;
	pMaximumReached = cEnviroment::getMaximumReached();
	if ( pMaximumReached != NULL ){
	
		cout<<"The object for checking the maximum population size of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for checking the maximum population size of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getSelectIndividualToDelete() methode from cEnviroment
	cout<<"pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete(); "<<endl;
	pSelectIndividualToDelete = cEnviroment::getSelectIndividualToDelete();
	if ( pSelectIndividualToDelete != NULL ){
	
		cout<<"The object for selecting a bad individual from the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a bad individual from the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getOperatorFitnessAlgorithm() methode from cEnviroment
	cout<<"pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm(); "<<endl;
	pOperatorFitnessAlgorithm = cEnviroment::getOperatorFitnessAlgorithm();
	if ( pOperatorFitnessAlgorithm != NULL ){
	
		cout<<"The operation fitness algorithm of the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The operation fitness algorithm of the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getChoosOperator() methode from cEnviroment
	cout<<"pChoosOperator = cEnviroment::getChoosOperator(); "<<endl;
	pChoosOperator = cEnviroment::getChoosOperator();
	if ( pChoosOperator != NULL ){
	
		cout<<"The object for selecting a good operation for the enviroment is correctly not NULL. "<<endl;
	}else{
		cerr<<"Error: The object for selecting a good operation for the enviroment is NULL."<<endl;
		iReturn++;
	}
	//check the getResourceCheck() methode from cEnviroment
	cout<<"pResourceCheck = cEnviroment::getResourceCheck(); "<<endl;
	pResourceCheck = cEnviroment::getResourceCheck();
	if ( pResourceCheck != NULL ){
	
		if ( (resourceCheck.enoughResources() ==
				pResourceCheck->enoughResources()) ){
			
			cout<<"The object for checking if more operations could be started for the enviroment is correct. "<<endl;
		}else{
			cerr<<"Error: The object for checking if more operations could be started for the enviroment is not correct."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The object for checking if more operations could be started for the enviroment is NULL."<<endl;
		iReturn++;
	}
	
	if ( pEnviroment ){
		//check the OPERATION_DOMAIN methode from cEnviroment
		if ( pEnviroment->OPERATION_DOMAIN == "cFibIndividual" ){
		
			cout<<"The enviroment operation domain is correctly \"cFibIndividual\". "<<endl;
		}else{
			cerr<<"Error: The enviroment operation domain is "<< pEnviroment->OPERATION_DOMAIN <<
				" and not \"cFibIndividual\"."<<endl;
			iReturn++;
		}
		//check the getAlgorithmIdentifier() methode from cEnviroment
		if ( pEnviroment->getAlgorithmIdentifier() == ulAlgorithmId ){
		
			cout<<"The enviroment identifier is correctly "<<
				pEnviroment->getAlgorithmIdentifier() <<" . "<<endl;
		}else{
			cerr<<"Error: The enviroment identifier is "<<
				pEnviroment->getAlgorithmIdentifier() <<", but should be "<< ulAlgorithmId <<" ."<<endl;
			iReturn++;
		}
		//check the getCpuRunTime() methode from cEnviroment
		if ( pEnviroment->getCpuRunTime() == 0.0 ){
		
			cout<<"The enviroment cpu runtime is correctly "<<
				pEnviroment->getCpuRunTime() <<" s . "<<endl;
		}else{
			cerr<<"Error: The enviroment cpu runtime is "<<
				pEnviroment->getCpuRunTime() <<" s , but should be "<< 0.0 <<" s ."<<endl;
			iReturn++;
		}
		//check the getLastStartTime() methode from cEnviroment
		if ( pEnviroment->getLastStartTime() == 0 ){
		
			cout<<"The enviroment last start time is correctly "<<
				pEnviroment->getLastStartTime() <<"  . "<<endl;
		}else{
			cerr<<"Error: The enviroment last start time is "<<
				pEnviroment->getLastStartTime() <<"  , but should be "<< 0 <<" ."<<endl;
			iReturn++;
		}
		//check the getFirstStartTime() methode from cEnviroment
		if ( pEnviroment->getFirstStartTime() == 0 ){
		
			cout<<"The enviroment first start time is correctly "<<
				pEnviroment->getFirstStartTime() <<". "<<endl;
		}else{
			cerr<<"Error: The enviroment first start time is "<<
				pEnviroment->getFirstStartTime() <<", but should be "<< 0 <<" ."<<endl;
			iReturn++;
		}
		delete pEnviroment;
		ulAlgorithmId++;
		
		iReturn += checkIfEnviromentIsEmpty();
	}


	return iReturn;
}


/**
 * This method runs the enviroment for a tread.
 * It will wait till the enviroment is ended befor returning.
 * It will simply call run().
 */
void * runEnviroment( void * inputArg ){
	
	((cEnviroment*)(inputArg))->run();
	
	return NULL;
}


/**
 * This function tests the methods for running the enviroment
 * cEnviroment. This includs also a check for the enviroment
 * operation handling.
 *
 * methods tested:
 * 	- static cEnviroment * getInstance();
 * 	- static bool setParameter( const cInitEnviroment * pInInit, const cObjectFitnessAlgorithm * pInObjectFitnessAlgorithm, const cEndConditionCheck * pInEndCondition = NULL, const cIndividualSelection * pInIndividualSelection = NULL, const cMaximumReached * pInMaximumIndividuals = NULL, const cSelectIndividualToDelete * pInSelectIndividualToDelete = NULL, const cOperatorFitnessAlgorithm * pInOperationFitnessAlgorithmus = NULL, const cChoosOperator * pInChoosOperator = NULL, const cResourceCheck * pInResourceCheck = NULL );
 * 	- bool start();
 * 	- bool run();
 * 	- bool stop();
 * 	- bool isRunning();
 * 	- unsigned int getNumberOfRunningOperations();
 * 	- unsigned long getNumberOfCalledOperations();
 * 	- double getCpuRunTime() const;
 * 	- time_t getLastStartTime() const;
 * 	- time_t getFirstStartTime() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testRun( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing running the enviroment cEnviroment with start()"<<endl;
	
	//set the parameters
	cVectorPosition vecPosition( 2 );
	vecPosition.setValue( 1, 1 );
	cPoint point2( &vecPosition );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cRoot rootInit( &point2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cRoot rootInit( NULL, NULL, &point2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	rootInit.setNumberOfInputVariables( 1 );
	
	cout<<"cInitFibEnviroment initEnviroment( rootInit ); "<<endl;
	cInitFibEnviroment initEnviroment( rootInit );
	
	cout<<"cFibObjectFitnessBasicAlgorithm fibObjectAlgorithmBasic( &rootInit, 1, 2.0, 3.0 );"<<endl;
	cFibObjectFitnessBasicAlgorithm fibObjectAlgorithmBasic( &rootInit, 1, 2.0, 3.0 );
	
	//check the setParameter() methode from cEnviroment
	cout<<"bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic );"<<endl;
	bool bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic );

	if ( bParameterSet ){
	
		cout<<"The parameter could be correctly set. "<<endl;
	}else{
		cerr<<"Error: The parameter couldn't be set."<<endl;
		iReturn++;
	}
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	cEnviroment * pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment != NULL ){
	
		cout<<"An instance of the enviroment could be correctly created. "<<endl;
	}else{
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
		return iReturn;
	}
	//test values of the not running operation
	
	//check the OPERATION_DOMAIN methode from cEnviroment
	if ( pEnviroment->OPERATION_DOMAIN == "cFibIndividual" ){
	
		cout<<"The enviroment operation domain is correctly \"cFibIndividual\". "<<endl;
	}else{
		cerr<<"Error: The enviroment operation domain is "<< pEnviroment->OPERATION_DOMAIN <<
			" and not \"cFibIndividual\"."<<endl;
		iReturn++;
	}
	//check the getAlgorithmIdentifier() methode from cEnviroment
	if ( pEnviroment->getAlgorithmIdentifier() == ulAlgorithmId ){
	
		cout<<"The enviroment identifier is correctly "<<
			pEnviroment->getAlgorithmIdentifier() <<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment identifier is "<<
			pEnviroment->getAlgorithmIdentifier() <<", but should be "<< ulAlgorithmId <<" ."<<endl;
		iReturn++;
	}
	//check the getCpuRunTime() methode from cEnviroment
	if ( pEnviroment->getCpuRunTime() == 0.0 ){
	
		cout<<"The enviroment cpu runtime is correctly "<<
			pEnviroment->getCpuRunTime() <<" s . "<<endl;
	}else{
		cerr<<"Error: The enviroment cpu runtime is "<<
			pEnviroment->getCpuRunTime() <<" s , but should be "<< 0.0 <<" s ."<<endl;
		iReturn++;
	}
	//check the isRunning() methode from cEnviroment
	if ( ! (pEnviroment->isRunning()) ){
	
		cout<<"The enviroment is correctly not running . "<<endl;
	}else{
		cerr<<"Error: The enviroment is running ."<<endl;
		iReturn++;
	}
	//check the getLastStartTime() methode from cEnviroment
	if ( pEnviroment->getLastStartTime() == 0 ){
	
		cout<<"The enviroment last start time is correctly "<<
			pEnviroment->getLastStartTime() <<"  . "<<endl;
	}else{
		cerr<<"Error: The enviroment last start time is "<<
			pEnviroment->getLastStartTime() <<"  , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstStartTime() methode from cEnviroment
	if ( pEnviroment->getFirstStartTime() == 0 ){
	
		cout<<"The enviroment first start time is correctly "<<
			pEnviroment->getFirstStartTime() <<". "<<endl;
	}else{
		cerr<<"Error: The enviroment first start time is "<<
			pEnviroment->getFirstStartTime() <<", but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfRunningOperations() == 0 ){
	
		cout<<"The number of running operations is correctly "<<
			pEnviroment->getNumberOfRunningOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	unsignedLongFib ulCalledOperations1 = pEnviroment->getNumberOfCalledOperations();
	if ( pEnviroment->getNumberOfCalledOperations() == 0 ){
	
		cout<<"The number of called operations is correctly "<<
			pEnviroment->getNumberOfCalledOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of called operations is "<<
			pEnviroment->getNumberOfCalledOperations() <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}

	//starting the enviroment
	cout<<"pEnviroment->start(); "<<endl;
	pEnviroment->start();
	
	{//delay if enougth enviroments are running
		fibMilliSleep( 100 );
	}
	
	//check the isRunning() methode from cEnviroment
	if ( pEnviroment->isRunning() ){
	
		cout<<"The enviroment is correctly running . "<<endl;
	}else{
		cerr<<"Error: The enviroment isn't running ."<<endl;
		iReturn++;
	}
	//check the getLastStartTime() methode from cEnviroment
	time_t tmLastStartTime = pEnviroment->getLastStartTime();
	if ( tmLastStartTime != 0 ){
	
		cout<<"The enviroment last start time is correctly not 0 . "<<endl;
	}else{
		cerr<<"Error: The enviroment last start time is "<<
			tmLastStartTime <<" , but shouldn't be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstStartTime() methode from cEnviroment
	time_t tmFirstStartTime = pEnviroment->getFirstStartTime();
	if ( tmFirstStartTime != 0 ){
	
		cout<<"The enviroment first start time is "<<
			tmFirstStartTime<<" and correctly not 0. "<<endl;
	}else{
		cerr<<"Error: The enviroment first start time is "<<
			tmFirstStartTime <<", but shouldn't be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	unsignedLongFib ulCalledOperations2 = pEnviroment->getNumberOfCalledOperations();
	if ( (pEnviroment->getNumberOfRunningOperations() != 0) ||
			( ulCalledOperations1 < ulCalledOperations2) ){
	
		cout<<"The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations()<<" and ther wher "<<
			(ulCalledOperations2 - ulCalledOperations1)<<" operations called . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" and ther wher "<<
			(ulCalledOperations2 - ulCalledOperations1)<<
			" operations called, but ther should be operations called ."<<endl;
		iReturn++;
	}

	//check the getNumberOfRunningOperations() methode from cEnviroment
	unsigned long lOperationsCalled = pEnviroment->getNumberOfCalledOperations();
	if ( lOperationsCalled != 0 ){
	
		cout<<"The number of called operations is "<<
			lOperationsCalled<<" and correctly not 0 . "<<endl;
	}else{
		cerr<<"Error: The number of called operations is "<<
			lOperationsCalled <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	{//1 second wait
		fibMilliSleep( 1100 );
	}
	//check the isRunning() methode from cEnviroment
	if ( pEnviroment->isRunning() ){
	
		cout<<"The enviroment is correctly running . "<<endl;
	}else{
		cerr<<"Error: The enviroment isn't running ."<<endl;
		iReturn++;
	}
	//check the getCpuRunTime() methode from cEnviroment
	double dCpuTime = pEnviroment->getCpuRunTime();
	if ( dCpuTime != 0.0 ){
	
		cout<<"The enviroment cpu runtime is "<<
			dCpuTime<<" and correctly not 0 s . "<<endl;
	}else{
		cerr<<"Error: The enviroment cpu runtime is "<<
			dCpuTime <<" s , but shouldn't be "<< 0.0 <<" s ."<<endl;
		cerr<<"   Last start time="<<tmLastStartTime<<" actual time="<<
			time( NULL )<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	unsignedLongFib ulCalledOperations3 = pEnviroment->getNumberOfCalledOperations();
	if ( (pEnviroment->getNumberOfRunningOperations() != 0) ||
			( ulCalledOperations2 < ulCalledOperations3) ){
	
		cout<<"The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations()<<" and ther wher "<<
			(ulCalledOperations3 - ulCalledOperations2)<<" operations called . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" and ther wher "<<
			(ulCalledOperations3 - ulCalledOperations2)<<
			" operations called, but ther should be operations called ."<<endl;
		iReturn++;
	}


	cout<<"pEnviroment->stop(); "<<endl;
	pEnviroment->stop();
	
	{//1 second wait
		fibMilliSleep( 1100 );
	}
	
	//check the getLastStartTime() methode from cEnviroment
	time_t tmLastStartTime2 = pEnviroment->getLastStartTime();
	if ( tmLastStartTime2 == tmLastStartTime ){
	
		cout<<"The enviroment last start time is correctly "<< tmLastStartTime <<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment last start time is "<<
			tmLastStartTime2 <<" , but should be "<< tmLastStartTime <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstStartTime() methode from cEnviroment
	time_t tmFirstStartTime2 = pEnviroment->getFirstStartTime();
	if ( tmFirstStartTime2 == tmFirstStartTime ){
	
		cout<<"The enviroment first start time is correctly "<<
			tmFirstStartTime2<<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment first start time is "<<
			tmFirstStartTime2 <<", but should be "<< tmFirstStartTime <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	const unsignedLongFib lOperationsCalled2 = pEnviroment->getNumberOfCalledOperations();
	if ( lOperationsCalled <= lOperationsCalled2 ){
	
		cout<<"The number of called operations is "<< lOperationsCalled2
			<<" and correctly greater equal "<< lOperationsCalled <<" . "<<endl;
	}else{
		cerr<<"Error: The number of called operations is "<< lOperationsCalled2 <<
			" , but should be greater equal "<< lOperationsCalled <<" ."<<endl;
		iReturn++;
	}
	//check the getCpuRunTime() methode from cEnviroment
	double dCpuTime2 = pEnviroment->getCpuRunTime();
	if ( dCpuTime <= dCpuTime2 ){
	
		cout<<"The enviroment cpu runtime is "<< dCpuTime2 <<
			" s and correctly greater equal "<< dCpuTime <<" s . "<<endl;
	}else{
		cerr<<"Error: The enviroment cpu runtime is "<< dCpuTime2 <<
			" s , but should be greater equal "<< dCpuTime <<" s ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfRunningOperations() == 0 ){
	
		cout<<"The number of running operations is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}

	{//1 second wait
		fibMilliSleep( 100 );
	}
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing starting the enviroment cEnviroment again"<<endl;

	//starting the enviroment again
	cout<<"pEnviroment->start(); "<<endl;
	pEnviroment->start();
	
	{//delay if enougth enviroments are running
		fibMilliSleep( 100 );
	}
	
	//check the isRunning() methode from cEnviroment
	if ( pEnviroment->isRunning() ){
	
		cout<<"The enviroment is correctly running . "<<endl;
	}else{
		cerr<<"Error: The enviroment isn't running ."<<endl;
		iReturn++;
	}
	//check the getLastStartTime() methode from cEnviroment
	time_t tmLastStartTime3 = pEnviroment->getLastStartTime();
	if ( tmLastStartTime2 < tmLastStartTime3 ){
	
		cout<<"The enviroment last start time is "<< tmLastStartTime3 <<
			" and correctly greater "<< tmLastStartTime2 <<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment last start time is "<<
			tmLastStartTime3 <<" , but should be greater "<< tmLastStartTime2 <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstStartTime() methode from cEnviroment
	time_t tmFirstStartTime3 = pEnviroment->getFirstStartTime();
	if ( tmFirstStartTime == tmFirstStartTime3 ){
	
		cout<<"The enviroment first start time is correctly "<<
			tmFirstStartTime3<<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment first start time is "<<
			tmFirstStartTime3 <<", but should be "<< tmFirstStartTime <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	const unsignedLongFib lOperationsCalled3 = pEnviroment->getNumberOfCalledOperations();
	if ( (pEnviroment->getNumberOfRunningOperations() != 0) ||
			( lOperationsCalled2 < lOperationsCalled3) ){
	
		cout<<"The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations()<<" and ther wher "<<
			(lOperationsCalled3 - lOperationsCalled2)<<" operations called . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" and ther wher "<<
			(lOperationsCalled3 - lOperationsCalled2)<<
			" operations called, but ther should be operations called ."<<endl;
		iReturn++;
	}
	//1 second wait
	{//delay if enougth enviroments are running
		fibMilliSleep( 1130 );
	}
	//check the isRunning() methode from cEnviroment
	if ( pEnviroment->isRunning() ){
	
		cout<<"The enviroment is correctly running . "<<endl;
	}else{
		cerr<<"Error: The enviroment isn't running ."<<endl;
		iReturn++;
	}
	//check the getCpuRunTime() methode from cEnviroment
	const double dCpuTime3 = pEnviroment->getCpuRunTime();
	if ( dCpuTime2 < dCpuTime3 ){
	
		cout<<"The enviroment cpu runtime is "<< dCpuTime3 <<
			" and correctly greater "<< dCpuTime2 <<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment cpu runtime is "<< dCpuTime3 <<
			" s , but should be greater "<< dCpuTime2 <<" s ."<<endl;
		iReturn++;
	}

	cout<<"pEnviroment->stop(); "<<endl;
	pEnviroment->stop();
	
	
	//check the getLastStartTime() methode from cEnviroment
	time_t tmLastStartTime4 = pEnviroment->getLastStartTime();
	if ( tmLastStartTime4 == tmLastStartTime3 ){
	
		cout<<"The enviroment last start time is correctly "<< tmLastStartTime4 <<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment last start time is "<<
			tmLastStartTime4 <<" , but should be "<< tmLastStartTime3 <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstStartTime() methode from cEnviroment
	time_t tmFirstStartTime4 = pEnviroment->getFirstStartTime();
	if ( tmFirstStartTime4 == tmFirstStartTime4 ){
	
		cout<<"The enviroment first start time is correctly "<<
			tmFirstStartTime4<<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment first start time is "<<
			tmFirstStartTime4 <<", but should be "<< tmFirstStartTime3 <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	unsigned long lOperationsCalled4 = pEnviroment->getNumberOfCalledOperations();
	if ( lOperationsCalled3 <= lOperationsCalled4 ){
	
		cout<<"The number of called operations is "<< lOperationsCalled4
			<<" and correctly greater equal "<< lOperationsCalled3 <<" . "<<endl;
	}else{
		cerr<<"Error: The number of called operations is "<< lOperationsCalled4 <<
			" , but should be greater equal "<< lOperationsCalled3 <<" ."<<endl;
		iReturn++;
	}
	//check the getCpuRunTime() methode from cEnviroment
	double dCpuTime4 = pEnviroment->getCpuRunTime();
	if ( dCpuTime3 <= dCpuTime4 ){
	
		cout<<"The enviroment cpu runtime is "<< dCpuTime4 <<
			" s and correctly greater equal "<< dCpuTime3 <<" s . "<<endl;
	}else{
		cerr<<"Error: The enviroment cpu runtime is "<< dCpuTime2 <<
			" s , but should be greater equal "<< dCpuTime3 <<" s ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfRunningOperations() == 0 ){
	
		cout<<"The number of running operations is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	
	
	delete pEnviroment;
	ulAlgorithmId++;
	iReturn += checkIfEnviromentIsEmpty();
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing running the enviroment cEnviroment with run()"<<endl;
	
	cout<<"cEndConditionCheck endCondition;"<<endl;
	cEndConditionCheck endCondition;
	cout<<"endCondition.setMaxOperationCalls( 8 );"<<endl;
	endCondition.setMaxOperationCalls( 8 );
	
	//check the setParameter() methode from cEnviroment
	cout<<"bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic, &endCondition );"<<endl;
	bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic, &endCondition );

	if ( bParameterSet ){
	
		cout<<"The parameter could be correctly set. "<<endl;
	}else{
		cerr<<"Error: The parameter couldn't be set."<<endl;
		iReturn++;
	}
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment != NULL ){
	
		cout<<"An instance of the enviroment could be correctly created. "<<endl;
	}else{
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
		return iReturn;
	}
	//test values of the not running operation
	
	//check the OPERATION_DOMAIN methode from cEnviroment
	if ( pEnviroment->OPERATION_DOMAIN == "cFibIndividual" ){
	
		cout<<"The enviroment operation domain is correctly \"cFibIndividual\". "<<endl;
	}else{
		cerr<<"Error: The enviroment operation domain is "<< pEnviroment->OPERATION_DOMAIN <<
			" and not \"cFibIndividual\"."<<endl;
		iReturn++;
	}
	//check the getAlgorithmIdentifier() methode from cEnviroment
	if ( pEnviroment->getAlgorithmIdentifier() == ulAlgorithmId ){
	
		cout<<"The enviroment identifier is correctly "<<
			pEnviroment->getAlgorithmIdentifier() <<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment identifier is "<<
			pEnviroment->getAlgorithmIdentifier() <<", but should be "<< ulAlgorithmId <<" ."<<endl;
		iReturn++;
	}
	//check the getCpuRunTime() methode from cEnviroment
	if ( pEnviroment->getCpuRunTime() == 0.0 ){
	
		cout<<"The enviroment cpu runtime is correctly "<<
			pEnviroment->getCpuRunTime() <<" s . "<<endl;
	}else{
		cerr<<"Error: The enviroment cpu runtime is "<<
			pEnviroment->getCpuRunTime() <<" s , but should be "<< 0.0 <<" s ."<<endl;
		iReturn++;
	}
	//check the isRunning() methode from cEnviroment
	if ( ! (pEnviroment->isRunning()) ){
	
		cout<<"The enviroment is correctly not running . "<<endl;
	}else{
		cerr<<"Error: The enviroment is running ."<<endl;
		iReturn++;
	}
	//check the getLastStartTime() methode from cEnviroment
	if ( pEnviroment->getLastStartTime() == 0 ){
	
		cout<<"The enviroment last start time is correctly "<<
			pEnviroment->getLastStartTime() <<"  . "<<endl;
	}else{
		cerr<<"Error: The enviroment last start time is "<<
			pEnviroment->getLastStartTime() <<"  , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstStartTime() methode from cEnviroment
	if ( pEnviroment->getFirstStartTime() == 0 ){
	
		cout<<"The enviroment first start time is correctly "<<
			pEnviroment->getFirstStartTime() <<". "<<endl;
	}else{
		cerr<<"Error: The enviroment first start time is "<<
			pEnviroment->getFirstStartTime() <<", but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfRunningOperations() == 0 ){
	
		cout<<"The number of running operations is correctly "<<
			pEnviroment->getNumberOfRunningOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfCalledOperations() == 0 ){
	
		cout<<"The number of called operations is correctly "<<
			pEnviroment->getNumberOfCalledOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of called operations is "<<
			pEnviroment->getNumberOfCalledOperations() <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}

	//running the enviroment
	cout<<"pEnviroment->run(); "<<endl;
	pEnviroment->run();
	
	//check the isRunning() methode from cEnviroment
	if ( ! (pEnviroment->isRunning()) ){
	
		cout<<"The enviroment is correctly not running . "<<endl;
	}else{
		cerr<<"Error: The enviroment is running ."<<endl;
		iReturn++;
	}
	//check the getLastStartTime() methode from cEnviroment
	time_t tmLastStartTimeRun = pEnviroment->getLastStartTime();
	if ( tmLastStartTimeRun != 0 ){
	
		cout<<"The enviroment last start time is correctly not 0 . "<<endl;
	}else{
		cerr<<"Error: The enviroment last start time is "<<
			tmLastStartTimeRun <<" , but shouldn't be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstStartTime() methode from cEnviroment
	time_t tmFirstStartTimeRun = pEnviroment->getFirstStartTime();
	if ( tmFirstStartTimeRun != 0 ){
	
		cout<<"The enviroment first start time is "<<
			tmFirstStartTimeRun <<" and correctly not 0. "<<endl;
	}else{
		cerr<<"Error: The enviroment first start time is "<<
			tmFirstStartTimeRun <<", but shouldn't be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfRunningOperations() == 0 ){
	
		cout<<"The number of running operations is correctly "<<
			pEnviroment->getNumberOfRunningOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfCalledOperations() > 8 ){
	
		cout<<"The number of called operations is "<<
			pEnviroment->getNumberOfCalledOperations()<<" and correctly greater 8 . "<<endl;
	}else{
		cerr<<"Error: The number of called operations is "<<
			pEnviroment->getNumberOfCalledOperations() <<" , but should be greater 8 ."<<endl;
		iReturn++;
	}
	
	{//1 second wait
		fibMilliSleep( 1100 );
	}
	
	//running the enviroment
	cout<<"pEnviroment->run(); "<<endl;
	pEnviroment->run();
	
	//check the isRunning() methode from cEnviroment
	if ( ! (pEnviroment->isRunning()) ){
	
		cout<<"The enviroment is correctly not running . "<<endl;
	}else{
		cerr<<"Error: The enviroment is running ."<<endl;
		iReturn++;
	}
	//check the getLastStartTime() methode from cEnviroment
	time_t tmLastStartTimeRun2 = pEnviroment->getLastStartTime();
	if ( tmLastStartTimeRun < tmLastStartTimeRun2 ){
	
		cout<<"The enviroment last start time is correctly greater "<< tmLastStartTimeRun <<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment last start time is "<<
			tmLastStartTimeRun2 <<" , but should be greater "<< tmLastStartTimeRun <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstStartTime() methode from cEnviroment
	time_t tmFirstStartTimeRun2 = pEnviroment->getFirstStartTime();
	if ( tmFirstStartTimeRun == tmFirstStartTimeRun2 ){
	
		cout<<"The enviroment first start time is correctly "<<
			tmFirstStartTimeRun <<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment first start time is "<<
			tmFirstStartTimeRun2 <<", but should be "<< tmFirstStartTimeRun <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfRunningOperations() == 0 ){
	
		cout<<"The number of running operations is correctly "<<
			pEnviroment->getNumberOfRunningOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfCalledOperations() > 8 ){
	
		cout<<"The number of called operations is "<<
			pEnviroment->getNumberOfCalledOperations()<<" and correctly greater 8 . "<<endl;
	}else{
		cerr<<"Error: The number of called operations is "<<
			pEnviroment->getNumberOfCalledOperations() <<" , but should be greater 8 ."<<endl;
		iReturn++;
	}

	delete pEnviroment;
	ulAlgorithmId++;
	iReturn += checkIfEnviromentIsEmpty();
	
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing running the enviroment cEnviroment with run() in seperate tread"<<endl;
	
	//check the setParameter() methode from cEnviroment
	cout<<"bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic );"<<endl;
	bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic );

	if ( bParameterSet ){
	
		cout<<"The parameter could be correctly set. "<<endl;
	}else{
		cerr<<"Error: The parameter couldn't be set."<<endl;
		iReturn++;
	}
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment != NULL ){
	
		cout<<"An instance of the enviroment could be correctly created. "<<endl;
	}else{
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
		return iReturn;
	}
	//test values of the not running operation
	
	//check the OPERATION_DOMAIN methode from cEnviroment
	if ( pEnviroment->OPERATION_DOMAIN == "cFibIndividual" ){
	
		cout<<"The enviroment operation domain is correctly \"cFibIndividual\". "<<endl;
	}else{
		cerr<<"Error: The enviroment operation domain is "<< pEnviroment->OPERATION_DOMAIN <<
			" and not \"cFibIndividual\"."<<endl;
		iReturn++;
	}
	//check the getAlgorithmIdentifier() methode from cEnviroment
	if ( pEnviroment->getAlgorithmIdentifier() == ulAlgorithmId ){
	
		cout<<"The enviroment identifier is correctly "<<
			pEnviroment->getAlgorithmIdentifier() <<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment identifier is "<<
			pEnviroment->getAlgorithmIdentifier() <<", but should be "<< ulAlgorithmId <<" ."<<endl;
		iReturn++;
	}
	//check the getCpuRunTime() methode from cEnviroment
	if ( pEnviroment->getCpuRunTime() == 0.0 ){
	
		cout<<"The enviroment cpu runtime is correctly "<<
			pEnviroment->getCpuRunTime() <<" s . "<<endl;
	}else{
		cerr<<"Error: The enviroment cpu runtime is "<<
			pEnviroment->getCpuRunTime() <<" s , but should be "<< 0.0 <<" s ."<<endl;
		iReturn++;
	}
	//check the isRunning() methode from cEnviroment
	if ( ! (pEnviroment->isRunning()) ){
	
		cout<<"The enviroment is correctly not running . "<<endl;
	}else{
		cerr<<"Error: The enviroment is running ."<<endl;
		iReturn++;
	}
	//check the getLastStartTime() methode from cEnviroment
	if ( pEnviroment->getLastStartTime() == 0 ){
	
		cout<<"The enviroment last start time is correctly "<<
			pEnviroment->getLastStartTime() <<"  . "<<endl;
	}else{
		cerr<<"Error: The enviroment last start time is "<<
			pEnviroment->getLastStartTime() <<"  , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstStartTime() methode from cEnviroment
	if ( pEnviroment->getFirstStartTime() == 0 ){
	
		cout<<"The enviroment first start time is correctly "<<
			pEnviroment->getFirstStartTime() <<". "<<endl;
	}else{
		cerr<<"Error: The enviroment first start time is "<<
			pEnviroment->getFirstStartTime() <<", but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfRunningOperations() == 0 ){
	
		cout<<"The number of running operations is correctly "<<
			pEnviroment->getNumberOfRunningOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	const unsignedLongFib ulCalledOperations6 = pEnviroment->getNumberOfCalledOperations();
	if ( ulCalledOperations6 == 0 ){
	
		cout<<"The number of called operations is correctly "<<
			ulCalledOperations6 <<" . "<<endl;
	}else{
		cerr<<"Error: The number of called operations is "<<
			ulCalledOperations6 <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}

	//run the enviroment in a seperate tread
#ifdef WINDOWS
	DWORD   dwThreadId = 0;
	HANDLE threadRun = CreateThread( 
		NULL, //default security attributes
		0, //use default stack size  
		(LPTHREAD_START_ROUTINE)&(runEnviroment), //thread function name
		pEnviroment, //argument to thread function 
		0, //use default creation flags 
		&dwThreadId ); //returns the thread identifier 
	cout<<"HANDLE threadRun = CreateThread( NULL, 0,"<<
		" (LPTHREAD_START_ROUTINE)&(runEnviroment), pEnviroment, 0, &dwThreadId ); "<<endl;
	
#else //WINDOWS
	pthread_t threadRun;
	cout<<"pthread_create( &threadRun, NULL, &(runEnviroment), pEnviroment ); "<<endl;
	pthread_create( &threadRun, NULL, &(runEnviroment), pEnviroment );
#endif //WINDOWS

	{//delay if enougth enviroments are running
		fibMilliSleep( 100 );
	}
	
	//check the isRunning() methode from cEnviroment
	if ( pEnviroment->isRunning() ){
	
		cout<<"The enviroment is correctly running . "<<endl;
	}else{
		cerr<<"Error: The enviroment isn't running ."<<endl;
		iReturn++;
	}
	//check the getLastStartTime() methode from cEnviroment
	time_t tmLastStartTimeTRun = pEnviroment->getLastStartTime();
	if ( tmLastStartTimeTRun != 0 ){
	
		cout<<"The enviroment last start time is correctly not 0 . "<<endl;
	}else{
		cerr<<"Error: The enviroment last start time is "<<
			tmLastStartTimeTRun <<" , but shouldn't be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstStartTime() methode from cEnviroment
	time_t tmFirstStartTimeTRun = pEnviroment->getFirstStartTime();
	if ( tmFirstStartTimeTRun != 0 ){
	
		cout<<"The enviroment first start time is "<<
			tmFirstStartTimeTRun <<" and correctly not 0. "<<endl;
	}else{
		cerr<<"Error: The enviroment first start time is "<<
			tmFirstStartTimeTRun <<", but shouldn't be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	const unsignedLongFib ulCalledOperations7 = pEnviroment->getNumberOfCalledOperations();
	if ( (pEnviroment->getNumberOfRunningOperations() != 0) ||
			( ulCalledOperations6 < ulCalledOperations7) ){
	
		cout<<"The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations()<<" and ther wher "<<
			(ulCalledOperations7 - ulCalledOperations6)<<" operations called . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" and ther wher "<<
			(ulCalledOperations7 - ulCalledOperations6)<<
			" operations called, but ther should be operations called ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	unsigned long lOperationsCalledTRun = pEnviroment->getNumberOfCalledOperations();
	if ( lOperationsCalledTRun != 0 ){
	
		cout<<"The number of called operations is "<<
			lOperationsCalledTRun <<" and correctly not 0 . "<<endl;
	}else{
		cerr<<"Error: The number of called operations is "<<
			lOperationsCalledTRun <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	{//1 second wait
		fibMilliSleep( 1100 );
	}
	//check the isRunning() methode from cEnviroment
	if ( pEnviroment->isRunning() ){
	
		cout<<"The enviroment is correctly running . "<<endl;
	}else{
		cerr<<"Error: The enviroment isn't running ."<<endl;
		iReturn++;
	}
	//check the getCpuRunTime() methode from cEnviroment
	double dCpuTimeTRun = pEnviroment->getCpuRunTime();
	if ( dCpuTimeTRun != 0.0 ){
	
		cout<<"The enviroment cpu runtime is "<<
			dCpuTimeTRun <<" and correctly not 0 s . "<<endl;
	}else{
		cerr<<"Error: The enviroment cpu runtime is "<<
			dCpuTimeTRun <<" s , but shouldn't be "<< 0.0 <<" s ."<<endl;
		iReturn++;
	}

	cout<<"pEnviroment->stop(); "<<endl;
	pEnviroment->stop();
	
	{//1 second wait
		fibMilliSleep( 1100 );
	}
	
	//check the getLastStartTime() methode from cEnviroment
	time_t tmLastStartTimeTRun2 = pEnviroment->getLastStartTime();
	if ( tmLastStartTimeTRun2 == tmLastStartTimeTRun ){
	
		cout<<"The enviroment last start time is correctly "<< tmLastStartTimeTRun <<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment last start time is "<<
			tmLastStartTimeTRun2 <<" , but should be "<< tmLastStartTimeTRun <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstStartTime() methode from cEnviroment
	time_t tmFirstStartTimeTRun2 = pEnviroment->getFirstStartTime();
	if ( tmFirstStartTimeTRun2 == tmFirstStartTimeTRun ){
	
		cout<<"The enviroment first start time is correctly "<<
			tmFirstStartTimeTRun2<<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment first start time is "<<
			tmFirstStartTimeTRun2 <<", but should be "<< tmFirstStartTimeTRun <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	unsigned long lOperationsCalledTRun2 = pEnviroment->getNumberOfCalledOperations();
	if ( lOperationsCalledTRun <= lOperationsCalledTRun2 ){
	
		cout<<"The number of called operations is "<< lOperationsCalledTRun2
			<<" and correctly greater equal "<< lOperationsCalledTRun <<" . "<<endl;
	}else{
		cerr<<"Error: The number of called operations is "<< lOperationsCalledTRun2 <<
			" , but should be greater equal "<< lOperationsCalledTRun <<" ."<<endl;
		iReturn++;
	}
	//check the getCpuRunTime() methode from cEnviroment
	double dCpuTimeTRun2 = pEnviroment->getCpuRunTime();
	if ( dCpuTimeTRun <= dCpuTimeTRun2 ){
	
		cout<<"The enviroment cpu runtime is "<< dCpuTimeTRun2 <<
			" s and correctly greater equal "<< dCpuTimeTRun <<" s . "<<endl;
	}else{
		cerr<<"Error: The enviroment cpu runtime is "<< dCpuTimeTRun2 <<
			" s , but should be greater equal "<< dCpuTimeTRun <<" s ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfRunningOperations() == 0 ){
	
		cout<<"The number of running operations is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}

	{//0.1 second wait
		fibMilliSleep( 100 );
	}
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing running the enviroment cEnviroment again in seperate tread"<<endl;

	//run the enviroment in a seperate tread
#ifdef WINDOWS
	DWORD   dwThreadId2 = 0;
	HANDLE threadRun2 = CreateThread(
		NULL, //default security attributes
		0, //use default stack size
		(LPTHREAD_START_ROUTINE)&(runEnviroment), //thread function name
		pEnviroment, //argument to thread function
		0, //use default creation flags
		&dwThreadId2 ); //returns the thread identifier
	cout<<"HANDLE threadRun2 = CreateThread( NULL, 0,"<<
		" (LPTHREAD_START_ROUTINE)&(runEnviroment), pEnviroment, 0, &dwThreadId2 ); "<<endl;
	
#else //WINDOWS
	pthread_t threadRun2;
	cout<<"pthread_create( &threadRun2, NULL, &(runEnviroment), pEnviroment ); "<<endl;
	pthread_create( &threadRun2, NULL, &(runEnviroment), pEnviroment );
#endif //WINDOWS
	
	const unsignedLongFib ulCalledOperations4 = pEnviroment->getNumberOfCalledOperations();
	
	{//delay enougth till enviroment is running
		fibMilliSleep( 100 );
	}
	
	//check the isRunning() methode from cEnviroment
	if ( pEnviroment->isRunning() ){
	
		cout<<"The enviroment is correctly running . "<<endl;
	}else{
		cerr<<"Error: The enviroment isn't running ."<<endl;
		iReturn++;
	}
	//check the getLastStartTime() methode from cEnviroment
	time_t tmLastStartTimeTRun3 = pEnviroment->getLastStartTime();
	if ( tmLastStartTimeTRun2 < tmLastStartTimeTRun3 ){
	
		cout<<"The enviroment last start time is "<< tmLastStartTimeTRun3 <<
			" and correctly greater "<< tmLastStartTimeTRun2 <<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment last start time is "<<
			tmLastStartTimeTRun3 <<" , but should be greater "<< tmLastStartTimeTRun2 <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstStartTime() methode from cEnviroment
	time_t tmFirstStartTimeTRun3 = pEnviroment->getFirstStartTime();
	if ( tmFirstStartTimeTRun == tmFirstStartTimeTRun3 ){
	
		cout<<"The enviroment first start time is correctly "<<
			tmFirstStartTimeTRun3<<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment first start time is "<<
			tmFirstStartTimeTRun3 <<", but should be "<< tmFirstStartTimeTRun <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	const unsignedLongFib ulCalledOperations5 = pEnviroment->getNumberOfCalledOperations();
	if ( (pEnviroment->getNumberOfRunningOperations() != 0) ||
			( ulCalledOperations4 < ulCalledOperations5) ){
	
		cout<<"The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations()<<" and ther wher "<<
			(ulCalledOperations5 - ulCalledOperations4)<<" operations called . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" and ther wher "<<
			(ulCalledOperations5 - ulCalledOperations4)<<
			" operations called, but ther should be operations called ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	unsigned long lOperationsCalledTRun3 = pEnviroment->getNumberOfCalledOperations();
	if ( lOperationsCalledTRun2 < lOperationsCalledTRun3 ){
	
		cout<<"The number of called operations is "<< lOperationsCalled3 <<
			" and correctly greater "<< lOperationsCalledTRun2 <<" . "<<endl;
	}else{
		cerr<<"Error: The number of called operations is "<<
			lOperationsCalledTRun3 <<" , but should be greater "<< lOperationsCalledTRun2 <<" ."<<endl;
		iReturn++;
	}
	//1 second wait
	{//delay 1 s
		fibMilliSleep( 1170 );
	}
	//check the isRunning() methode from cEnviroment
	if ( pEnviroment->isRunning() ){
	
		cout<<"The enviroment is correctly running . "<<endl;
	}else{
		cerr<<"Error: The enviroment isn't running ."<<endl;
		iReturn++;
	}
	//check the getCpuRunTime() methode from cEnviroment
	double dCpuTimeTRun3 = pEnviroment->getCpuRunTime();
	if ( dCpuTimeTRun2 < dCpuTimeTRun3 ){
	
		cout<<"The enviroment cpu runtime is "<< dCpuTimeTRun3 <<
			" and correctly greater "<< dCpuTimeTRun2 <<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment cpu runtime is "<< dCpuTimeTRun3 <<
			" s , but should be greater "<< dCpuTimeTRun2 <<" s ."<<endl;
		iReturn++;
	}

	cout<<"pEnviroment->stop(); "<<endl;
	pEnviroment->stop();
	
	
	//check the getLastStartTime() methode from cEnviroment
	time_t tmLastStartTimeTRun4 = pEnviroment->getLastStartTime();
	if ( tmLastStartTimeTRun4 == tmLastStartTimeTRun3 ){
	
		cout<<"The enviroment last start time is correctly "<< tmLastStartTimeTRun4 <<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment last start time is "<<
			tmLastStartTimeTRun4 <<" , but should be "<< tmLastStartTimeTRun3 <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstStartTime() methode from cEnviroment
	time_t tmFirstStartTimeTRun4 = pEnviroment->getFirstStartTime();
	if ( tmFirstStartTimeTRun4 == tmFirstStartTimeTRun4 ){
	
		cout<<"The enviroment first start time is correctly "<<
			tmFirstStartTimeTRun4<<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment first start time is "<<
			tmFirstStartTimeTRun4 <<", but should be "<< tmFirstStartTimeTRun3 <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	unsigned long lOperationsCalledTRun4 = pEnviroment->getNumberOfCalledOperations();
	if ( lOperationsCalledTRun3 <= lOperationsCalledTRun4 ){
	
		cout<<"The number of called operations is "<< lOperationsCalledTRun4
			<<" and correctly greater equal "<< lOperationsCalledTRun3 <<" . "<<endl;
	}else{
		cerr<<"Error: The number of called operations is "<< lOperationsCalledTRun4 <<
			" , but should be greater equal "<< lOperationsCalledTRun3 <<" ."<<endl;
		iReturn++;
	}
	//check the getCpuRunTime() methode from cEnviroment
	double dCpuTimeTRun4 = pEnviroment->getCpuRunTime();
	if ( dCpuTimeTRun3 <= dCpuTimeTRun4 ){
	
		cout<<"The enviroment cpu runtime is "<< dCpuTimeTRun4 <<
			" s and correctly greater equal "<< dCpuTimeTRun3 <<" s . "<<endl;
	}else{
		cerr<<"Error: The enviroment cpu runtime is "<< dCpuTimeTRun2 <<
			" s , but should be greater equal "<< dCpuTimeTRun3 <<" s ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfRunningOperations() == 0 ){
	
		cout<<"The number of running operations is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	
	delete pEnviroment;
	ulAlgorithmId++;
	iReturn += checkIfEnviromentIsEmpty();
	
	return iReturn;
}



/**
 * This function tests the methods for running the enviroment
 * cEnviroment. This includs also a check for the enviroment
 * operation handling.
 *
 * methods tested:
 * 	- void operationStatusChange( cOperation * pOperation, bool isRunning );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testOperationStatusChange( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the operationStatusChange() method"<<endl;
	
	//set the parameters
	cVectorPosition vecPosition( 2 );
	vecPosition.setValue( 1, 1 );
	cPoint point2( &vecPosition );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cRoot rootInit( &point2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cRoot rootInit( NULL, NULL, &point2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	rootInit.setNumberOfInputVariables( 1 );
	
	cout<<"cInitFibEnviroment initEnviroment( rootInit ); "<<endl;
	cInitFibEnviroment initEnviroment( rootInit );
	
	cout<<"cFibObjectFitnessBasicAlgorithm fibObjectAlgorithmBasic( &rootInit, 1, 2.0, 3.0 );"<<endl;
	cFibObjectFitnessBasicAlgorithm fibObjectAlgorithmBasic( &rootInit, 1, 2.0, 3.0 );
	
	//check the setParameter() methode from cEnviroment
	cout<<"bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic );"<<endl;
	bool bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic );

	if ( bParameterSet ){
	
		cout<<"The parameter could be correctly set. "<<endl;
	}else{
		cerr<<"Error: The parameter couldn't be set."<<endl;
		iReturn++;
	}
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	cEnviroment * pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment != NULL ){
	
		cout<<"An instance of the enviroment could be correctly created. "<<endl;
	}else{
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
		return iReturn;
	}
	//test values of the not running operation
	
	//check the OPERATION_DOMAIN methode from cEnviroment
	if ( pEnviroment->OPERATION_DOMAIN == "cFibIndividual" ){
	
		cout<<"The enviroment operation domain is correctly \"cFibIndividual\". "<<endl;
	}else{
		cerr<<"Error: The enviroment operation domain is "<< pEnviroment->OPERATION_DOMAIN <<
			" and not \"cFibIndividual\"."<<endl;
		iReturn++;
	}
	//check the getAlgorithmIdentifier() methode from cEnviroment
	if ( pEnviroment->getAlgorithmIdentifier() == ulAlgorithmId ){
	
		cout<<"The enviroment identifier is correctly "<<
			pEnviroment->getAlgorithmIdentifier() <<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment identifier is "<<
			pEnviroment->getAlgorithmIdentifier() <<", but should be "<< ulAlgorithmId <<" ."<<endl;
		iReturn++;
	}
	//check the getCpuRunTime() methode from cEnviroment
	if ( pEnviroment->getCpuRunTime() == 0.0 ){
	
		cout<<"The enviroment cpu runtime is correctly "<<
			pEnviroment->getCpuRunTime() <<" s . "<<endl;
	}else{
		cerr<<"Error: The enviroment cpu runtime is "<<
			pEnviroment->getCpuRunTime() <<" s , but should be "<< 0.0 <<" s ."<<endl;
		iReturn++;
	}
	//check the isRunning() methode from cEnviroment
	if ( ! (pEnviroment->isRunning()) ){
	
		cout<<"The enviroment is correctly not running . "<<endl;
	}else{
		cerr<<"Error: The enviroment is running ."<<endl;
		iReturn++;
	}
	//check the getLastStartTime() methode from cEnviroment
	if ( pEnviroment->getLastStartTime() == 0 ){
	
		cout<<"The enviroment last start time is correctly "<<
			pEnviroment->getLastStartTime() <<"  . "<<endl;
	}else{
		cerr<<"Error: The enviroment last start time is "<<
			pEnviroment->getLastStartTime() <<"  , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstStartTime() methode from cEnviroment
	if ( pEnviroment->getFirstStartTime() == 0 ){
	
		cout<<"The enviroment first start time is correctly "<<
			pEnviroment->getFirstStartTime() <<". "<<endl;
	}else{
		cerr<<"Error: The enviroment first start time is "<<
			pEnviroment->getFirstStartTime() <<", but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfRunningOperations() == 0 ){
	
		cout<<"The number of running operations is correctly "<<
			pEnviroment->getNumberOfRunningOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfCalledOperations() == 0 ){
	
		cout<<"The number of called operations is correctly "<<
			pEnviroment->getNumberOfCalledOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of called operations is "<<
			pEnviroment->getNumberOfCalledOperations() <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	
	cout<<"pEnviroment->operationStatusChange( NULL, true );"<<endl;
	pEnviroment->operationStatusChange( NULL, true );

	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfRunningOperations() == 0 ){
	
		cout<<"The number of running operations is correctly "<<
			pEnviroment->getNumberOfRunningOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfCalledOperations() == 0 ){
	
		cout<<"The number of called operations is correctly "<<
			pEnviroment->getNumberOfCalledOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of called operations is "<<
			pEnviroment->getNumberOfCalledOperations() <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	
	cout<<"pEnviroment->operationStatusChange( NULL, false );"<<endl;
	pEnviroment->operationStatusChange( NULL, false );
	
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfRunningOperations() == 0 ){
	
		cout<<"The number of running operations is correctly "<<
			pEnviroment->getNumberOfRunningOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfCalledOperations() == 0 ){
	
		cout<<"The number of called operations is correctly "<<
			pEnviroment->getNumberOfCalledOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of called operations is "<<
			pEnviroment->getNumberOfCalledOperations() <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}

	cOperationIdentifier operationId1( pEnviroment->getAlgorithmIdentifier() );
	cout<<"cOpDummy opDummy( operationId1 );"<<endl;
	cOpDummy opDummy( operationId1 );

	cout<<"pEnviroment->operationStatusChange( &opDummy, true );"<<endl;
	pEnviroment->operationStatusChange( &opDummy, true );

	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfRunningOperations() == 1 ){
	
		cout<<"The number of running operations is correctly "<<
			pEnviroment->getNumberOfRunningOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" , but should be "<< 1 <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfCalledOperations() == 1 ){
	
		cout<<"The number of called operations is correctly "<<
			pEnviroment->getNumberOfCalledOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of called operations is "<<
			pEnviroment->getNumberOfCalledOperations() <<" , but should be "<< 1 <<" ."<<endl;
		iReturn++;
	}

	cout<<"pEnviroment->operationStatusChange( &opDummy, false );"<<endl;
	pEnviroment->operationStatusChange( &opDummy, false );

	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfRunningOperations() == 0 ){
	
		cout<<"The number of running operations is correctly "<<
			pEnviroment->getNumberOfRunningOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfCalledOperations() == 1 ){
	
		cout<<"The number of called operations is correctly "<<
			pEnviroment->getNumberOfCalledOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of called operations is "<<
			pEnviroment->getNumberOfCalledOperations() <<" , but should be "<< 1 <<" ."<<endl;
		iReturn++;
	}

	cout<<"pEnviroment->operationStatusChange( &opDummy, false );"<<endl;
	pEnviroment->operationStatusChange( &opDummy, false );

	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfRunningOperations() == 0 ){
	
		cout<<"The number of running operations is correctly "<<
			pEnviroment->getNumberOfRunningOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfCalledOperations() == 1 ){
	
		cout<<"The number of called operations is correctly "<<
			pEnviroment->getNumberOfCalledOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of called operations is "<<
			pEnviroment->getNumberOfCalledOperations() <<" , but should be "<< 1 <<" ."<<endl;
		iReturn++;
	}

	cout<<"pEnviroment->operationStatusChange( &opDummy, true );"<<endl;
	pEnviroment->operationStatusChange( &opDummy, true );

	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfRunningOperations() == 1 ){
	
		cout<<"The number of running operations is correctly "<<
			pEnviroment->getNumberOfRunningOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" , but should be "<< 1 <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfCalledOperations() == 2 ){
	
		cout<<"The number of called operations is correctly "<<
			pEnviroment->getNumberOfCalledOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of called operations is "<<
			pEnviroment->getNumberOfCalledOperations() <<" , but should be "<< 2 <<" ."<<endl;
		iReturn++;
	}

	cOperationIdentifier operationId2( pEnviroment->getAlgorithmIdentifier() );
	cout<<"cOpDummy opDummy2( operationId2 );"<<endl;
	cOpDummy opDummy2( operationId2 );
	
	cout<<"pEnviroment->operationStatusChange( &opDummy2, true );"<<endl;
	pEnviroment->operationStatusChange( &opDummy2, true );

	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfRunningOperations() == 2 ){
	
		cout<<"The number of running operations is correctly "<<
			pEnviroment->getNumberOfRunningOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of running operations is "<<
			pEnviroment->getNumberOfRunningOperations() <<" , but should be "<< 2 <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfRunningOperations() methode from cEnviroment
	if ( pEnviroment->getNumberOfCalledOperations() == 3 ){
	
		cout<<"The number of called operations is correctly "<<
			pEnviroment->getNumberOfCalledOperations() <<" . "<<endl;
	}else{
		cerr<<"Error: The number of called operations is "<<
			pEnviroment->getNumberOfCalledOperations() <<" , but should be "<< 3 <<" ."<<endl;
		iReturn++;
	}

	//check the getCpuRunTime() methode from cEnviroment
	if ( pEnviroment->getCpuRunTime() == 0.0 ){
	
		cout<<"The enviroment cpu runtime is correctly "<<
			pEnviroment->getCpuRunTime() <<" s . "<<endl;
	}else{
		cerr<<"Error: The enviroment cpu runtime is "<<
			pEnviroment->getCpuRunTime() <<" s , but should be "<< 0.0 <<" s ."<<endl;
		iReturn++;
	}
	//check the isRunning() methode from cEnviroment
	if ( ! (pEnviroment->isRunning()) ){
	
		cout<<"The enviroment is correctly not running . "<<endl;
	}else{
		cerr<<"Error: The enviroment is running ."<<endl;
		iReturn++;
	}
	//check the getLastStartTime() methode from cEnviroment
	if ( pEnviroment->getLastStartTime() == 0 ){
	
		cout<<"The enviroment last start time is correctly "<<
			pEnviroment->getLastStartTime() <<"  . "<<endl;
	}else{
		cerr<<"Error: The enviroment last start time is "<<
			pEnviroment->getLastStartTime() <<"  , but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstStartTime() methode from cEnviroment
	if ( pEnviroment->getFirstStartTime() == 0 ){
	
		cout<<"The enviroment first start time is correctly "<<
			pEnviroment->getFirstStartTime() <<". "<<endl;
	}else{
		cerr<<"Error: The enviroment first start time is "<<
			pEnviroment->getFirstStartTime() <<", but should be "<< 0 <<" ."<<endl;
		iReturn++;
	}
	
	delete pEnviroment;
	ulAlgorithmId++;
	iReturn += checkIfEnviromentIsEmpty();
	
	return iReturn;
}



/**
 * Listener for listening for new or deleted individuals.
 */
class cTestIndividualListener: public clNewIndividualListener{
public:

	const cIndividual * pIndividualAdded;
	unsigned int uiIndividualsAdded;
	const cIndividual * pIndividualDeleted;
	unsigned int uiIndividualsDeleted;

	cTestIndividualListener():
			pIndividualAdded( NULL ), uiIndividualsAdded( 0 ),
			pIndividualDeleted( NULL ), uiIndividualsDeleted( 0 ){
		//nothing to do
	}

	virtual ~cTestIndividualListener(){
		//nothing to do
	}

	/**
	 * This method is called if an new individual was added to the enviroment.
	 *
	 * @param pIndividual a pointer to the added individual
	 */
	virtual void individualAdded( const cIndividual * pIndividual ){
		pIndividualAdded = pIndividual;
		uiIndividualsAdded++;
	}
	
	/**
	 * This method is called if an individual was delteted from the enviroment.
	 *
	 * @param pIndividual a pointer to the delteted individual
	 */
	virtual void individualRemoved( const cIndividual * pIndividual ){
		pIndividualDeleted = pIndividual;
		uiIndividualsDeleted++;
	}
	
	/**
	 * This method sets the class member to 0.
	 */
	void emptyValues(){
		pIndividualAdded = NULL;
		uiIndividualsAdded = 0;
		pIndividualDeleted = NULL;
		uiIndividualsDeleted = 0;
	}
};


/**
 * This function tests if the given listeners wher notified about the
 * added individual.
 *
 * @param liIndividualListeners a list with the individuallisteners to check
 * @param pAddedIndividual the individual wich should be added
 * @return the number of erros occured in the test
 */
int checkListenerIndividualAdded( list< cTestIndividualListener * > liIndividualListeners,
		const cIndividual * pAddedIndividual ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	unsigned int uiListener = 1;
	for ( list< cTestIndividualListener * >::iterator
			itrIndividualListener = liIndividualListeners.begin();
			itrIndividualListener != liIndividualListeners.end();
			itrIndividualListener++ ){
		//check if the listener was notified
		if ( (*itrIndividualListener)->pIndividualAdded != NULL ){
			if ( (*((*itrIndividualListener)->pIndividualAdded)) == (*pAddedIndividual) ){
				
				cout<<"Listener "<< uiListener <<": An equal individual was correctly inserted. "<<endl;
			}else{
				cerr<<"Error listener "<< uiListener <<": The individual inserted is wrong."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error listener "<< uiListener <<": No individual was inserted ."<<endl;
			iReturn++;
		}
		if ( (*itrIndividualListener)->uiIndividualsAdded != 1 ){
			cerr<<"Error listener "<< uiListener <<": The individual was added "<<
				(*itrIndividualListener)->uiIndividualsAdded <<" times."<<endl;
			iReturn++;
		}
		if ( ((*itrIndividualListener)->pIndividualDeleted) == NULL ){
			
			cout<<"Listener "<< uiListener <<": No individual was correctly deleted. "<<endl;
		}else{
			cerr<<"Error listener "<< uiListener <<": An individual was deleted."<<endl;
			iReturn++;
		}
		if ( (*itrIndividualListener)->uiIndividualsDeleted != 0 ){
			cerr<<"Error listener "<< uiListener <<": The individual was deleted "<<
				(*itrIndividualListener)->uiIndividualsDeleted <<" times."<<endl;
			iReturn++;
		}
		(*itrIndividualListener)->emptyValues();
	}
	
	return iReturn;
}


/**
 * This function tests if the given listeners wher notified about the
 * deleted individual.
 *
 * @param liIndividualListeners a list with the individuallisteners to check
 * @param pAddedIndividual the individual wich should be deleted
 * @return the number of erros occured in the test
 */
int checkListenerIndividualDeleted( list< cTestIndividualListener * > liIndividualListeners,
		const cIndividual * pDeletedIndividual ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	unsigned int uiListener = 1;
	for ( list< cTestIndividualListener * >::iterator
			itrIndividualListener = liIndividualListeners.begin();
			itrIndividualListener != liIndividualListeners.end();
			itrIndividualListener++, uiListener++ ){
			
		//check if the listener was notified
		if ( (*itrIndividualListener)->pIndividualDeleted != NULL ){
			if ( (*((*itrIndividualListener)->pIndividualDeleted)) == (*pDeletedIndividual) ){
				
				cout<<"Listener "<< uiListener <<": An equal individual was correctly deleted. "<<endl;
			}else{
				cerr<<"Error listener "<< uiListener <<": The individual deleted is wrong."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error listener "<< uiListener <<": No individual was deleted ."<<endl;
			iReturn++;
		}
		if ( (*itrIndividualListener)->uiIndividualsDeleted != 1 ){
			cerr<<"Error listener "<< uiListener <<": The individual was deleted "<<
				(*itrIndividualListener)->uiIndividualsDeleted <<" times."<<endl;
			iReturn++;
		}
		if ( (*itrIndividualListener)->pIndividualAdded == NULL ){
			
			cout<<"Listener "<< uiListener <<": No individual was correctly added. "<<endl;
		}else{
			cerr<<"Error listener "<< uiListener <<": An individual was added."<<endl;
			iReturn++;
		}
		if ( (*itrIndividualListener)->uiIndividualsAdded != 0 ){
			cerr<<"Error listener "<< uiListener <<": The individual was added "<<
				(*itrIndividualListener)->uiIndividualsAdded <<" times."<<endl;
			iReturn++;
		}
		(*itrIndividualListener)->emptyValues();
	}
	
	return iReturn;
}


/**
 * This function tests if the given listeners wher not notified.
 *
 * @param liIndividualListeners a list with the individuallisteners to check
 * @return the number of erros occured in the test
 */
int checkListenerIndividualEmpty( list< cTestIndividualListener * > liIndividualListeners ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<"Checking "<< liIndividualListeners.size() <<" individual listeners which shouldn't be notified. "<<endl;
	
	unsigned int uiListener = 1;
	for ( list< cTestIndividualListener * >::iterator
			itrIndividualListener = liIndividualListeners.begin();
			itrIndividualListener != liIndividualListeners.end();
			itrIndividualListener++, uiListener++ ){
			
		//check if the listener was not notified
		if ( (*itrIndividualListener)->pIndividualAdded != NULL ){
			cerr<<"Error listener "<< uiListener <<": An individual was added."<<endl;
			iReturn++;
		}
		if ( (*itrIndividualListener)->uiIndividualsAdded != 0 ){
			cerr<<"Error listener "<< uiListener <<": The individual was added "<<
				(*itrIndividualListener)->uiIndividualsAdded <<" times."<<endl;
			iReturn++;
		}
		if ( ((*itrIndividualListener)->pIndividualDeleted) != NULL ){
			cerr<<"Error listener "<< uiListener <<": An individual was deleted."<<endl;
			iReturn++;
		}
		if ( (*itrIndividualListener)->uiIndividualsDeleted != 0 ){
			cerr<<"Error listener "<< uiListener <<": The individual was deleted "<<
				(*itrIndividualListener)->uiIndividualsDeleted <<" times."<<endl;
			iReturn++;
		}
		(*itrIndividualListener)->emptyValues();
	}
	
	return iReturn;
}



/**
 * This functions compares the fitness values of the given individuals
 * and returns true if the first individualfitness is higher /better
 * than the second, else false.
 * If one individual has no fitness, it is lower. If both individuals have
 * no fitness, the identifier of the individuals are compared with lower.
 * If both fitness values are equal, the  identifier of the individuals are
 * compared with lower.
 * If one individual has no fitness and identifier it is lower.
 * If both individuals have no fitness and identifiers ther pointers are
 * compared with lower.
 *
 * @param pIndividual1 a pointer to the first individual to compare with
 * @param pIndividual2 a pointer to the second individual to compare with
 * @return true if the fitnessvalue for pIndividual1 is greater than for
 * 	pIndividual2, else false
 */
bool compIndividualFitness( const cIndividual * pIndividual1,
		const cIndividual * pIndividual2 ){
	
	if ( (pIndividual1 == NULL) || (pIndividual2 == NULL) ||
			(pIndividual1->getInfo() == NULL) || (pIndividual2->getInfo() == NULL) ){
		return (pIndividual1 < pIndividual2);
	}
	const cObjectFitness * pFitness1 = pIndividual1->getInfo()->getFitness();
	const cObjectFitness * pFitness2 = pIndividual2->getInfo()->getFitness();
	
	const cIndividualIdentifier id1 = pIndividual1->getInfo()->getIdentifier();
	const cIndividualIdentifier id2 = pIndividual2->getInfo()->getIdentifier();
	
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
 * This function checks if individual infos of all individuals and not
 * more are in both containers.
 *
 * @param setIndividuals the set with the individuals
 * @param liAllInividualInfos the individual infos for the set of individuals
 * @return true if all individual infos of the list liAllInividualInfos
 * 	and not more are in the setIndividuals
 */
bool compareWithIndividualInfos( set< const cIndividual * ,
		bool(*)( const cIndividual*, const cIndividual* ) > setIndividuals,
		list<const cIndividualInfo*> liInividualInfos ){
	
	if ( setIndividuals.size() != liInividualInfos.size() ){
		return false;
	}
	
	set< const cIndividual * , bool(*)( const cIndividual*, const cIndividual* ) >
		setIndividualsInfo( compIndividualFitness );
	for ( list<const cIndividualInfo*>::iterator itrInividualInfos =
			liInividualInfos.begin();
			itrInividualInfos != liInividualInfos.end(); itrInividualInfos++ ){
		
		const cFibIndividual * pFibIndividual =
			new cFibIndividual( NULL, **itrInividualInfos, false );
		
		setIndividualsInfo.insert( pFibIndividual );
	}
	
	bool bIsEqual = true;
	set< const cIndividual * >::const_iterator itrInividual = setIndividuals.begin();
	for ( set< const cIndividual * >::const_iterator itrInividualInfos =
				setIndividualsInfo.begin();
			(itrInividualInfos != setIndividualsInfo.end()) &&
			(itrInividual != setIndividuals.end());
			itrInividualInfos++, itrInividual++ ){
		
		if ( ( (*itrInividual) == NULL ) || ( ( (*itrInividual)->getInfo()) == NULL ) ||
				( (*itrInividualInfos) == NULL ) ||
				( ( (*itrInividualInfos)->getInfo()) == NULL ) ){
			bIsEqual = false;
			break;
		}
		
		if ( (*((*itrInividual)->getInfo())) != (*((*itrInividualInfos)->getInfo())) ){
			bIsEqual = false;
			break;
		}
	}

	for ( set< const cIndividual * >::iterator itrInividualInfos =
			setIndividualsInfo.begin();
			itrInividualInfos != setIndividualsInfo.end(); itrInividualInfos++ ){
		delete (*itrInividualInfos);
	}
	setIndividualsInfo.clear();
	
	return bIsEqual;
}


/**
 * This function tests the methods for running the enviroment
 * cEnviroment. This includs also a check for the enviroment
 * operation handling.
 *
 * methods tested:
 * 	- bool insertIndividual( const cIndividual * pInIndividual, const cOperation * pProducerOperation = NULL );
 * 	- bool removeIndividual( const cIndividual * pInIndividual );
 * 	- unsigned long getNumberOfIndividuals( short iLive = 1 );
 * 	- list<const cIndividualInfo*> getIndividualInfos( short iLive = 0 ) const;
 * 	- const cIndividualInfo * getIndividualInfo( const cIndividualIdentifier & identifier ) const;
 * 	- const cIndividualInfo * getBestIndividualInfo( unsigned long lNumber = 1, short iLive = 1 ) const;
 * 	- cIndividual * getIndividual() const;
 * 	- cIndividual * getIndividual( const cIndividualIdentifier & identifier ) const;
 * 	- cIndividual * getBestIndividual( unsigned long lNumber = 1 ) const;
 * 	- bool registerIndividualListener( clNewIndividualListener * individualListener );
 * 	- bool unregisterIndividualListener( clNewIndividualListener * individualListener );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param uiMaxIteration the maximum number of iterations for the test
 * @param uiIndividualListenerTest the typy of the individual listener
 * 	test to perform:
 * 		0: test with one individual listener
 * 		1: test with one different individual listener added twice
 * 		2: test with two different individual listeners
 *			3: test with one individual listener and one individual
 *				listeners add and remove again at the start a listener
 * @return the number of erros occured in the test
 */
int testPopulation( unsigned long &ulTestphase, unsigned long uiMaxIteration = 256,
		unsigned short uiIndividualListenerTest = 0 ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the population methods of the enviroment"<<endl;
	
	
	//parameters for the generator
	list< pair< char, double > > liFractionOfFibElements;
	liFractionOfFibElements.push_back( make_pair( 'p', 1.0 ) );
	liFractionOfFibElements.push_back( make_pair( 'y', 1.0 ) );
	liFractionOfFibElements.push_back( make_pair( 'l', 0.4 ) );
	liFractionOfFibElements.push_back( make_pair( 'a', 0.5 ) );
	liFractionOfFibElements.push_back( make_pair( 'f', 0.5 ) );
	liFractionOfFibElements.push_back( make_pair( 'c', 0.5 ) );
	//TODO: more Fib-elements
	
	unsigned int uiAverageSubRoots = (rand() % 4 + 1) * (rand() % 4 + 1) + (rand() % 4);
	unsigned int uiAverageSubRootsDepth = (rand() % 2 + 1) * (rand() % 2 + 1) + (rand() % 2);
	unsigned int uiNumberOfAverageInputVariables = (rand() % 4 + 1) * (rand() % 4 + 1) + (rand() % 4);
//	double dFractionsOfUsedVariables = ((double)(rand() % 16)) / 15.0;
	double dFractionsOfUsedVariables = 0.0;
//	unsigned int uiSize = (rand() % 1024) + 16;
	unsigned int uiSize = (rand() % uiMaxSize) + 4;
	
	const unsigned int uiNumberOfDimensions     = (rand() % 4) + 1;
	const unsigned int uiMaxVectorElementNumber = (rand() % 256 + 2) * (rand() % 256 + 2);
	const unsigned int uiNumberOfPropertyTyps   = (rand() % 6) + 1;

	const cTypeProperty pPossiblePropertytyps[] = {
		cTypeProperty( 1, uiNumberOfDimensions ),
		cTypeProperty( 2, uiNumberOfDimensions ),
		cTypeProperty( 100, uiNumberOfDimensions ),
		cTypeProperty( 200, uiNumberOfDimensions ),
		cTypeProperty( 300, uiNumberOfDimensions ),
		cTypeProperty( 301, uiNumberOfDimensions ),
		cTypeProperty( 305, uiNumberOfDimensions ),
		cTypeProperty( 310, uiNumberOfDimensions ),
		cTypeProperty( 311, uiNumberOfDimensions ),
		cTypeProperty( 312, uiNumberOfDimensions ),
		cTypeProperty( 400, uiNumberOfDimensions ),
		cTypeProperty( 410, uiNumberOfDimensions ),
		cTypeProperty( 600, uiNumberOfDimensions ),
		//no existing typs
		cTypeProperty( 46, uiNumberOfDimensions ),
		cTypeProperty( 0, uiNumberOfDimensions )
	};
	//generate possible propertytyps
	list< cTypeProperty > liPossiblePropertytyps( pPossiblePropertytyps,
		pPossiblePropertytyps + sizeof( pPossiblePropertytyps ) / sizeof( cTypeProperty ) );
	while ( uiNumberOfPropertyTyps < liPossiblePropertytyps.size() ){
		//choos random propertytyp and erase it
		unsigned int uiRandom = rand() % liPossiblePropertytyps.size();
		list< cTypeProperty >::iterator itrChoosenProperty = liPossiblePropertytyps.begin();
		while ( uiRandom != 0 ){
			uiRandom--;
			itrChoosenProperty++;
		}
		liPossiblePropertytyps.erase( itrChoosenProperty );
	}

	const unsigned int uiFractionsOfUsedVariables =
		(unsigned int)(dFractionsOfUsedVariables * 100.0);

	cout<<endl<<"Generate Fib-object with size="<< uiSize <<
		" dimensions="<< uiNumberOfDimensions <<
		" uiAverageSubRoots="<< uiAverageSubRoots <<
		" uiAverageSubRootsDepth="<< uiAverageSubRootsDepth <<
		" uiNumberOfAverageInputVariables="<< uiNumberOfAverageInputVariables<<
		" uiFractionsOfUsedVariables="<< uiFractionsOfUsedVariables <<
		" uiMaxVectorElementNumber="<<uiMaxVectorElementNumber<<" . "<<endl<<flush;
	
	cout<<"And the properties: ";
	for ( list< cTypeProperty >::iterator itrProperty = liPossiblePropertytyps.begin();
			itrProperty != liPossiblePropertytyps.end(); itrProperty++ ){
		cout<< itrProperty->getNameOfProperty() << "; ";
	}
	cout<<endl;
	
	cRoot * pOriginalFibObject = (cRoot*)generateFibObject(
		uiSize, uiSize * (log( uiSize ) + 10),
		liFractionOfFibElements, liPossiblePropertytyps, uiNumberOfDimensions,
		uiAverageSubRoots, uiAverageSubRootsDepth,
		uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
		uiMaxVectorElementNumber );
	
	if ( pOriginalFibObject == NULL ){
		cerr<<"Error: Couldn't generate an original fib object."<<endl;
		iReturn++;
		return iReturn;
	}
	
	cout<<"cInitFibEnviroment initEnviroment( *pOriginalFibObject ); "<<endl;
	cInitFibEnviroment initEnviroment( *pOriginalFibObject );
	
	cout<<"cFibObjectFitnessBasicAlgorithm fibObjectAlgorithmBasic( pOriginalFibObject, 1, 2.0, 3.0 );"<<endl;
	cFibObjectFitnessBasicAlgorithm fibObjectAlgorithmBasic( pOriginalFibObject, 1, 2.0, 3.0 );
	
	cout<<"cMaximumReachedTestFalse maximumReachedTestFalse;"<<endl;
	cMaximumReachedTestFalse maximumReachedTestFalse;
	
	//check the setParameter() methode from cEnviroment
	cout<<"bParameterSet = cEnviroment::setParameter( &initEnviroment,"<<
		"&fibObjectAlgorithmBasic, NULL, NULL, &maximumReachedTestFalse );"<<endl;
	bool bParameterSet = cEnviroment::setParameter( &initEnviroment,
		&fibObjectAlgorithmBasic, NULL, NULL, &maximumReachedTestFalse );

	if ( bParameterSet ){
	
		cout<<"The parameter could be correctly set. "<<endl;
	}else{
		cerr<<"Error: The parameter couldn't be set."<<endl;
		iReturn++;
	}
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	cEnviroment * pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment != NULL ){
	
		cout<<"An instance of the enviroment could be correctly created. "<<endl;
	}else{
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
		return iReturn;
	}
	//test values of the not running operation
	
	//check the OPERATION_DOMAIN methode from cEnviroment
	if ( pEnviroment->OPERATION_DOMAIN == "cFibIndividual" ){
	
		cout<<"The enviroment operation domain is correctly \"cFibIndividual\". "<<endl;
	}else{
		cerr<<"Error: The enviroment operation domain is "<< pEnviroment->OPERATION_DOMAIN <<
			" and not \"cFibIndividual\"."<<endl;
		iReturn++;
	}
	//check the getAlgorithmIdentifier() methode from cEnviroment
	if ( pEnviroment->getAlgorithmIdentifier() == ulAlgorithmId ){
	
		cout<<"The enviroment identifier is correctly "<<
			pEnviroment->getAlgorithmIdentifier() <<" . "<<endl;
	}else{
		cerr<<"Error: The enviroment identifier is "<<
			pEnviroment->getAlgorithmIdentifier() <<", but should be "<< ulAlgorithmId <<" ."<<endl;
		iReturn++;
	}
	//check the isRunning() methode from cEnviroment
	if ( ! (pEnviroment->isRunning()) ){
	
		cout<<"The enviroment is correctly not running . "<<endl;
	}else{
		cerr<<"Error: The enviroment is running ."<<endl;
		iReturn++;
	}
	
	/*@param uiIndividualListenerTest the typy of the individual listener
		test to perform:
			0: test with one individual listener
			1: test with one different individual listener added twice
			2: test with two different individual listeners
			3: test with one individual listener and one individual
				listeners add and remove again at the start a listener
	*/
	list< cTestIndividualListener * > liIndividualListeners;
	list< cTestIndividualListener * > liIndividualListenersOther;
	
	cTestIndividualListener * pTestIndividualListenerOther = new cTestIndividualListener();
	liIndividualListenersOther.push_back( pTestIndividualListenerOther );
	switch ( uiIndividualListenerTest ){
		case 1:{
			//add the individual listener
			cTestIndividualListener * pTestIndividualListener = new cTestIndividualListener();
			cout<<"pEnviroment->registerIndividualListener( pTestIndividualListener ); "<<endl;
			bool bIndividualListenerAdded =
				pEnviroment->registerIndividualListener( pTestIndividualListener );
			if ( bIndividualListenerAdded ){
			
				cout<<"The individuallistener was correctly added . "<<endl;
				liIndividualListeners.push_back( pTestIndividualListener );
			}else{
				cerr<<"Error: The individuallistener coldn't be added ."<<endl;
				iReturn++;
			}
			//add the same individual listener a second time
			cout<<"pEnviroment->registerIndividualListener( pTestIndividualListener ); "<<endl;
			bIndividualListenerAdded =
				pEnviroment->registerIndividualListener( pTestIndividualListener );
			if ( ! bIndividualListenerAdded ){
			
				cout<<"The individuallistener was correctly not added again. "<<endl;
			}else{
				cerr<<"Error: The same individuallistener was added again."<<endl;
				iReturn++;
			}
		}break;
		case 2:{
			//add the individual listener
			cTestIndividualListener * pTestIndividualListener = new cTestIndividualListener();
			cout<<"pEnviroment->registerIndividualListener( pTestIndividualListener ); "<<endl;
			bool bIndividualListenerAdded =
				pEnviroment->registerIndividualListener( pTestIndividualListener );
			if ( bIndividualListenerAdded ){
			
				cout<<"The individuallistener was correctly added . "<<endl;
				liIndividualListeners.push_back( pTestIndividualListener );
			}else{
				cerr<<"Error: The individuallistener coldn't be added ."<<endl;
				iReturn++;
			}
			//add the individual listener
			cTestIndividualListener * pTestIndividualListener2 = new cTestIndividualListener();
			cout<<"pEnviroment->registerIndividualListener( pTestIndividualListener2 ); "<<endl;
			bIndividualListenerAdded =
				pEnviroment->registerIndividualListener( pTestIndividualListener2 );
			if ( bIndividualListenerAdded ){
			
				cout<<"The individuallistener was correctly added . "<<endl;
				liIndividualListeners.push_back( pTestIndividualListener2 );
			}else{
				cerr<<"Error: The individuallistener coldn't be added ."<<endl;
				iReturn++;
			}
		}break;
		case 3:{//add and remove a listener
			//add the individual listener
			cTestIndividualListener * pTestIndividualListener = new cTestIndividualListener();
			cout<<"pEnviroment->registerIndividualListener( pTestIndividualListener ); "<<endl;
			bool bIndividualListenerAdded =
				pEnviroment->registerIndividualListener( pTestIndividualListener );
			if ( bIndividualListenerAdded ){
			
				cout<<"The individuallistener was correctly added . "<<endl;
				liIndividualListeners.push_back( pTestIndividualListener );
			}else{
				cerr<<"Error: The individuallistener coldn't be added ."<<endl;
				iReturn++;
			}
			//add the individual listener
			cTestIndividualListener * pTestIndividualListener2 = new cTestIndividualListener();
			cout<<"pEnviroment->registerIndividualListener( pTestIndividualListener2 ); "<<endl;
			bIndividualListenerAdded =
				pEnviroment->registerIndividualListener( pTestIndividualListener2 );
			liIndividualListenersOther.push_back( pTestIndividualListener2 );
			if ( bIndividualListenerAdded ){
			
				cout<<"The individuallistener was correctly added . "<<endl;
			}else{
				cerr<<"Error: The individuallistener coldn't be added ."<<endl;
				iReturn++;
			}
			cout<<"pEnviroment->unregisterIndividualListener( pTestIndividualListener2 ); "<<endl;
			bool bIndividualListenerDeleted =
				pEnviroment->unregisterIndividualListener( pTestIndividualListener2 );
			if ( bIndividualListenerDeleted ){
			
				cout<<"The individuallistener was correctly deleted again. "<<endl;
			}else{
				cerr<<"Error: The individuallistener coldn't be deleted again."<<endl;
				iReturn++;
			}
		}break;
		default:{
			//add the individual listener
			cTestIndividualListener * pTestIndividualListener = new cTestIndividualListener();
			cout<<"pEnviroment->registerIndividualListener( pTestIndividualListener ); "<<endl;
			bool bIndividualListenerAdded =
				pEnviroment->registerIndividualListener( pTestIndividualListener );
			if ( bIndividualListenerAdded ){
			
				cout<<"The individuallistener was correctly added . "<<endl;
				liIndividualListeners.push_back( pTestIndividualListener );
			}else{
				cerr<<"Error: The individuallistener coldn't be added ."<<endl;
				iReturn++;
			}
		}
	};
	
	cOperationIdentifier operationId1( pEnviroment->getAlgorithmIdentifier() );
	cout<<"cOpDummy opDummy( operationId1 );"<<endl;
	cOpDummy opDummy( operationId1 );
	
	unsigned long ulCountIndividualsLiving = 0;
	unsigned long ulCountIndividualsDead = 0;

	set< const cIndividual * , bool(*)( const cIndividual*, const cIndividual* ) >
		setLivingIndividuals( compIndividualFitness );
	set< const cIndividual * , bool(*)( const cIndividual*, const cIndividual* ) >
		setDeadIndividuals( compIndividualFitness );

	cFibIndividual * pIndividualDummy = NULL;
	{//create a dummy individual
		const list<cIndividualIdentifier> liParents;
		cOperationIdentifier operationId( pEnviroment->getAlgorithmIdentifier() );
		
		const cIndividualInfo * pBestIndividualInfo =
			pEnviroment->getBestIndividualInfo();
		const cObjectFitness * pBestObjectFitness = NULL;
		if ( pBestIndividualInfo ){
			pBestObjectFitness = pBestIndividualInfo->getFitness();
		}
		if ( pBestObjectFitness == NULL ){
			pBestObjectFitness =
				pEnviroment->getFitnessAlgorithm()->getBestFitness();
		}
		//generate Fib-object
		cRoot * pDummyFibObject = (cRoot*)generateFibObject(
			uiSize, uiSize * (log( uiSize ) + 10),
			liFractionOfFibElements, liPossiblePropertytyps, uiNumberOfDimensions,
			uiAverageSubRoots, uiAverageSubRootsDepth,
			uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
			uiMaxVectorElementNumber );
		
		if ( pDummyFibObject == NULL ){
			cerr<<"Error: Couldn't generate a dummy Fib-object."<<endl;
			iReturn++;
			return iReturn;
		}
		
		cout<<"pFitness = pEnviroment->getFitnessAlgorithm()->evalueFitness( pDummyFibObject ) "<<endl;
		cFibObjectFitness * pFitness = ((cFibObjectFitnessAlgorithm * )
			pEnviroment->getFitnessAlgorithm())->evalueFitness( pDummyFibObject );
		
		double dOperationCost = ((double)(rand() % 100000)) / 100.0;
		cout<<"cIndividualInfo newIndividualInfo( pEnviroment->getAlgorithmIdentifier(),"<<
			" liParents, * pFitness, \"dummy_operation\", \"dummy individual\","<<
			" * operationId, "<< time_t( NULL ) <<", "<< dOperationCost <<" ,"<<
			" pBestObjectFitness ); "<<endl;
		cIndividualInfo newIndividualInfo( pEnviroment->getAlgorithmIdentifier(),
			liParents, * pFitness, "dummy_operation", "random individual",
			operationId, time_t( NULL ), dOperationCost ,
			pBestObjectFitness );
		if ( pFitness ){
			delete pFitness;
		}
		
		cout<<"pIndividualDummy = new cFibIndividual( pDummyFibObject, newIndividualInfo ); "<<endl;
		pIndividualDummy = new cFibIndividual( pDummyFibObject, newIndividualInfo );
	}

	for ( unsigned int iteration = 0; iteration < uiMaxIteration; iteration++ ){
		//choos random if adding or removing an individual should be tested
		if ( (rand() % 2) == 0 ){
			//generate random individuals with random fitness values
			
			const list<cIndividualIdentifier> liParents;
			cOperationIdentifier operationId( pEnviroment->getAlgorithmIdentifier() );
			
			const cIndividualInfo * pBestIndividualInfo =
				pEnviroment->getBestIndividualInfo();
			const cObjectFitness * pBestObjectFitness = NULL;
			if ( pBestIndividualInfo ){
				pBestObjectFitness = pBestIndividualInfo->getFitness();
			}
			if ( pBestObjectFitness == NULL ){
				pBestObjectFitness =
					pEnviroment->getFitnessAlgorithm()->getBestFitness();
			}
			//generate Fib-object
			cRoot * pNewFibObject = (cRoot*)generateFibObject(
				uiSize, uiSize * (log( uiSize ) + 10),
				liFractionOfFibElements, liPossiblePropertytyps, uiNumberOfDimensions,
				uiAverageSubRoots, uiAverageSubRootsDepth,
				uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
				uiMaxVectorElementNumber );
			
			if ( pNewFibObject == NULL ){
				cerr<<"Error: Couldn't generate a new Fib-object."<<endl;
				iReturn++;
				continue;
			}
			
			cout<<"pFitness = pEnviroment->getFitnessAlgorithm()->evalueFitness( pNewFibObject ) "<<endl;
			cFibObjectFitness * pFitness = ((cFibObjectFitnessAlgorithm * )
				pEnviroment->getFitnessAlgorithm())->evalueFitness( pNewFibObject );
			
			double dOperationCost = ((double)(rand() % 100000)) / 100.0;
			cout<<"cIndividualInfo newIndividualInfo( pEnviroment->getAlgorithmIdentifier(),"<<
				" liParents, * pFitness, \"dummy_operation\", \"random individual\","<<
				" * operationId, "<< time_t( NULL ) <<", "<< dOperationCost <<" ,"<<
				" pBestObjectFitness ); "<<endl;
			cIndividualInfo newIndividualInfo( pEnviroment->getAlgorithmIdentifier(),
				liParents, * pFitness, "dummy_operation", "random individual",
				operationId, time_t( NULL ), dOperationCost ,
				pBestObjectFitness );
			if ( pFitness ){
				delete pFitness;
			}
		
			cout<<"cFibIndividual newIndividual( pNewFibObject, newIndividualInfo ); "<<endl;
			cFibIndividual newIndividual( pNewFibObject, newIndividualInfo );
			
			//insert the generated individual
			const cOperation * pOperation = &opDummy;
			if ( (rand() % 5) == 0 ){
				pOperation = NULL;
			}
			cout<<"pEnviroment->insertIndividual( &newIndividual, "<<pOperation<<" ); "<<endl;
			const bool bIndividualInserted =
				pEnviroment->insertIndividual( &newIndividual, pOperation );
			
			if ( ! bIndividualInserted ){
				
				cerr<<"Error: Inserting not successfull."<<endl;
				iReturn++;
				continue;
			}// bIndividualInserted == true
			//update testdata
			if ( liIndividualListeners.front()->pIndividualAdded ){
				ulCountIndividualsLiving++;
				setLivingIndividuals.insert(
					liIndividualListeners.front()->pIndividualAdded );
			}
			
			//check if the listener(s) was(/wher) notified
			iReturn += checkListenerIndividualAdded(
				liIndividualListeners, &newIndividual );
		}else{//remove random individual
			//choos random individual to delete
			const cIndividual * pIndividualToDelte = NULL;
			bool bIndividualCanBeDeleted = true;
			size_t uiLivingindividuals = setLivingIndividuals.size();
			if ( ( 0 < uiLivingindividuals ) && ( (rand() % 5) != 0) ){
				unsigned long ulChoosenIndividual = rand() % uiLivingindividuals;
				
				set< const cIndividual * >::iterator itrIndividual = setLivingIndividuals.begin();
				for ( unsigned long ulActualIndividual = 0;
						(ulActualIndividual <= ulChoosenIndividual) &&
						(itrIndividual != setLivingIndividuals.end());
						ulActualIndividual++, itrIndividual++ ){
					//select individual
				}
				if ( itrIndividual != setLivingIndividuals.end() ){
					pIndividualToDelte = *itrIndividual;
					bIndividualCanBeDeleted = true;
				}else{
					cout<<"no individual to delete "<<endl;
					if ( rand() % 3 == 0 ){
						pIndividualToDelte = NULL;
					}else{
						pIndividualToDelte = pIndividualDummy;
					}
					bIndividualCanBeDeleted = false;
				}
			}else{
				if ( rand() % 2 == 0 ){
					pIndividualToDelte = NULL;
				}else{
					if ( (rand() % 3 == 0) || setDeadIndividuals.empty() ){
						//delete dummy individual
						pIndividualToDelte = pIndividualDummy;
					}else{//choos a ded individual to remove
						unsigned long ulChoosenIndividual = rand() % setDeadIndividuals.size();
						
						set< const cIndividual * >::iterator itrIndividual = setDeadIndividuals.begin();
						for ( unsigned long ulActualIndividual = 0;
								(ulActualIndividual <= ulChoosenIndividual) &&
								(itrIndividual != setDeadIndividuals.end());
								ulActualIndividual++, itrIndividual++ ){
							//select individual
						}
						if ( itrIndividual != setDeadIndividuals.end() ){
							pIndividualToDelte = *itrIndividual;
						}else{
							pIndividualToDelte = NULL;
						}
					}
				}
				cout<<"choosing non deletebel individual "<<endl;
				bIndividualCanBeDeleted = false;
			}
			cIndividualIdentifier individualId =
				cIndividualIdentifier::getNoIndividualIdentifier();
			if ( pIndividualToDelte ){
				individualId = pIndividualToDelte->getInfo()->getIdentifier();
			}
			
			cout<<"pEnviroment->removeIndividual( "<< pIndividualToDelte <<"->getInfo()->getIdentifier() ); "<<endl;
			const bool bIndividualDeleted = pEnviroment->removeIndividual( individualId );
			if ( bIndividualDeleted != bIndividualCanBeDeleted ){
				
				cerr<<"Error: Deleting "<<(bIndividualDeleted?("not "):(""))<<
					"successfull but shouldn't be."<<endl;
				iReturn++;
				continue;
			}// bIndividualInserted == true
			//update testdata
			if ( bIndividualDeleted && (liIndividualListeners.front()->pIndividualDeleted != NULL) ){
				ulCountIndividualsLiving--;
				ulCountIndividualsDead++;
				setLivingIndividuals.erase( liIndividualListeners.front()->pIndividualDeleted );
				setDeadIndividuals.insert( liIndividualListeners.front()->pIndividualDeleted );
			}
			if ( bIndividualDeleted ){
				//check if the listener was notified
				iReturn += checkListenerIndividualDeleted(
					liIndividualListeners, pIndividualToDelte );
			}
		}
		//check if the non listener wher not notified
		iReturn += checkListenerIndividualEmpty( liIndividualListenersOther );
		
		//check the enviroment population
		
		//check getNumberOfIndividuals( iLive = 1 )
		if ( pEnviroment->getNumberOfIndividuals( 1 ) == ulCountIndividualsLiving ){
			
			cout<<"The number of living individuals is correctly "<<
				ulCountIndividualsLiving <<" . "<<endl;
		}else{
			cerr<<"Error: The number of living individuals is "<<
				pEnviroment->getNumberOfIndividuals( 1 ) <<", but should be "<<
				ulCountIndividualsLiving <<" ."<<endl;
			iReturn++;
		}
		//check getNumberOfIndividuals( iLive = -1 )
		if ( pEnviroment->getNumberOfIndividuals( -1 ) == ulCountIndividualsDead ){
			
			cout<<"The number of dead individuals is correctly "<<
				ulCountIndividualsDead <<" . "<<endl;
		}else{
			cerr<<"Error: The number of dead individuals is "<<
				pEnviroment->getNumberOfIndividuals( -1 ) <<", but should be "<<
				ulCountIndividualsDead <<" ."<<endl;
			iReturn++;
		}
		//check getNumberOfIndividuals( iLive = 0 )
		if ( pEnviroment->getNumberOfIndividuals( 0 ) ==
				(ulCountIndividualsLiving + ulCountIndividualsDead) ){
			
			cout<<"The number of living individuals is correctly "<<
				(ulCountIndividualsLiving + ulCountIndividualsDead) <<" . "<<endl;
		}else{
			cerr<<"Error: The number of living individuals is "<<
				pEnviroment->getNumberOfIndividuals( 0 ) <<", but should be "<<
				(ulCountIndividualsLiving + ulCountIndividualsDead) <<" ."<<endl;
			iReturn++;
		}

		cout<<"liLivingInividualInfos = pEnviroment->getIndividualInfos( 1 ); "<<endl;
		list<const cIndividualInfo*> liLivingInividualInfos =
			pEnviroment->getIndividualInfos( 1 );
		bool bContainersEqual = compareWithIndividualInfos( setLivingIndividuals, liLivingInividualInfos );
		if ( bContainersEqual ){
			
			cout<<"The living individual infos are correct. "<<endl;
		}else{
			cerr<<"Error: The living individual infos arn't correct."<<endl;
			iReturn++;
		}
		
		cout<<"liDeadInividualInfos = getIndividualInfos( -1 ); "<<endl;
		list<const cIndividualInfo*> liDeadInividualInfos =
			pEnviroment->getIndividualInfos( -1 );
		bContainersEqual = compareWithIndividualInfos( setDeadIndividuals, liDeadInividualInfos );
		if ( bContainersEqual ){
			
			cout<<"The dead individual infos are correct. "<<endl;
		}else{
			cerr<<"Error: The dead individual infos arn't correct."<<endl;
			iReturn++;
		}
		
		cout<<"liAllInividualInfos  = getIndividualInfos( 0 ); "<<endl;
		list<const cIndividualInfo*> liAllInividualInfos =
			pEnviroment->getIndividualInfos( 0 );
		set< const cIndividual * , bool(*)( const cIndividual*, const cIndividual* ) >
			setAllIndividuals = setLivingIndividuals;
		setAllIndividuals.insert( setDeadIndividuals.begin(), setDeadIndividuals.end() );
		bContainersEqual = compareWithIndividualInfos( setAllIndividuals, liAllInividualInfos );
		if ( bContainersEqual ){
			
			cout<<"The all individual infos are correct. "<<endl;
		}else{
			cerr<<"Error: The all individual infos arn't correct."<<endl;
			iReturn++;
		}

		if ( ! setLivingIndividuals.empty() ){
			for ( unsigned int iRetry = 0; iRetry < 16; iRetry++ ){
				
				cout<<"pRandomChoosenIndividual = pEnviroment->getIndividual(); "<<endl;
				cIndividual * pRandomChoosenIndividual = pEnviroment->getIndividual();
				if ( pRandomChoosenIndividual == NULL ){
					cerr<<"Error: No individual random choosen (NULL returned)."<<endl;
					iReturn++;
					continue;
				}
				//check if individual exists in the living individuals
				set< const cIndividual * , bool(*)( const cIndividual*, const cIndividual* ) >::iterator
				  itrIndividual = setLivingIndividuals.find( pRandomChoosenIndividual );
				
				if ( itrIndividual != setLivingIndividuals.end() ){
					cout<<"Correctly a living random individual choosen. "<<endl;
				}else if ( compIndividualFitness( fibObjectAlgorithmBasic.
						getOriginalIndividual(), pRandomChoosenIndividual ) ){
					cout<<"Correctly a living random individual (the original individual) choosen. "<<endl;
				}else{
					cerr<<"Error: No living individual random choosen."<<endl;
					iReturn++;
				}
				delete pRandomChoosenIndividual;
			}
		}
		for ( unsigned int iRetry = 0; iRetry < 16; iRetry++ ){
			//choos random individual
			short sIsLiving = (rand() % 3) - 1;
			
			const cIndividual * pChoosenIndividual = NULL;
			unsigned long lNumber = 0;
			
			if ( sIsLiving == 1 ){
				if ( setLivingIndividuals.empty() ){
					continue;//skip
				}
				//choose from living individuals
				unsigned long ulChoosenElement = rand() % setLivingIndividuals.size();
				lNumber = ulChoosenElement;
				set< const cIndividual * >::const_iterator itrInividual;
				for ( itrInividual = setLivingIndividuals.begin();
						(itrInividual != setLivingIndividuals.end()) &&
						(0 < ulChoosenElement); itrInividual++, ulChoosenElement-- ){
					//nothing to do
				}
				pChoosenIndividual = *itrInividual;
			}else if ( sIsLiving == -1 ){
				//choose from dead individuals
				if ( setDeadIndividuals.empty() ){
					continue;//skip
				}
				//choose from living individuals
				unsigned long ulChoosenElement = rand() % setDeadIndividuals.size();
				lNumber = ulChoosenElement;
				set< const cIndividual * >::const_iterator itrInividual;
				for ( itrInividual = setDeadIndividuals.begin();
						(itrInividual != setDeadIndividuals.end()) &&
						(0 < ulChoosenElement); itrInividual++, ulChoosenElement-- ){
					//nothing to do
				}
				pChoosenIndividual = *itrInividual;
			}else{//( sIsLiving == -1 )
				//choose from all individuals
				if ( setAllIndividuals.empty() ){
					continue;//skip
				}
				//choose from living individuals
				unsigned long ulChoosenElement = rand() % setAllIndividuals.size();
				lNumber = ulChoosenElement;
				set< const cIndividual * >::const_iterator itrInividual;
				for ( itrInividual = setAllIndividuals.begin();
						(itrInividual != setAllIndividuals.end()) &&
						(0 < ulChoosenElement); itrInividual++, ulChoosenElement-- ){
					//nothing to do
				}
				pChoosenIndividual = *itrInividual;
			}
			lNumber++;//counting of the best individual begins with 1
			if ( pChoosenIndividual->getInfo() == NULL ){
				cerr<<"Error: The choosen individual has no information."<<endl;
				iReturn++;
				continue;//skip
			}
			cIndividualIdentifier identifier = pChoosenIndividual->getInfo()->getIdentifier();
			//check getIndividualInfo()
			cout<<"pIndividualinfo = pEnviroment->getIndividualInfo( identifier ); "<<endl;
			const cIndividualInfo * pIndividualInfo =
				pEnviroment->getIndividualInfo( identifier );
			if ( pIndividualInfo != NULL ){
				
				if ( (*pIndividualInfo) == (*(pChoosenIndividual->getInfo())) ){
					
					cout<<"The evalued individual information for the choosen individual is correct. "<<endl;
				}else{
					cerr<<"Error: The evalued individual information for the choosen individual isn't correct."<<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: Couldn't get the individual information for the choosen individual."<<endl;
				iReturn++;
			}
			//check getIndividual()
			cout<<"pIndividual = pEnviroment->getIndividual( identifier ); "<<endl;
			cIndividual * pIndividual = pEnviroment->getIndividual( identifier );
			if ( pIndividual != NULL ){
				
				if ( (*pChoosenIndividual) == (*pIndividual) ){
					
					cout<<"The evalued individual from the enviroment is correct. "<<endl;
				}else{
					cerr<<"Error: The evalued individual from the enviroment isn't correct."<<endl;
					iReturn++;
				}
				delete pIndividual;
			}else{
				cerr<<"Error: Couldn't get the individual from the enviroment for the choosen individual."<<endl;
				iReturn++;
			}
			//check getBestIndividualInfo()
			cout<<"pIndividualinfo = pEnviroment->getBestIndividualInfo( "<< lNumber <<", "<< sIsLiving <<" ); "<<endl;
			pIndividualInfo = pEnviroment->getBestIndividualInfo( lNumber, sIsLiving );
			if ( pIndividualInfo != NULL ){
				
				if ( (*pIndividualInfo) == (*(pChoosenIndividual->getInfo())) ){
					
					cout<<"The evalued individual information for the choosen individual is correct. "<<endl;
				}else{
					cerr<<"Error: The evalued individual information for the choosen individual isn't correct."<<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: Couldn't get the individual information for the choosen individual."<<endl;
				iReturn++;
			}

			if ( sIsLiving == 1 ){
				//check getBestIndividual()
				cout<<"pIndividual = pEnviroment->getBestIndividual( lNumber ); "<<endl;
				pIndividual = pEnviroment->getBestIndividual( lNumber );
				if ( pIndividual != NULL ){
					
					if ( (*pChoosenIndividual) == (*pIndividual) ){
						
						cout<<"The evalued "<< lNumber <<"'th best individual from the enviroment is correct. "<<endl;
					}else{
						cerr<<"Error: The evalued "<< lNumber <<"'th best individual from the enviroment isn't correct."<<endl;
						iReturn++;
					}
					delete pIndividual;
				}else{
					cerr<<"Error: Couldn't get the "<< lNumber <<"'th best individual from the enviroment for the choosen individual."<<endl;
					iReturn++;
				}
			}
		}
	}
	if ( pIndividualDummy ){
		delete pIndividualDummy;
	}
	if ( pOriginalFibObject ){
		cFibElement::deleteObject( pOriginalFibObject );
	}
	//unregister the individual listeners
	switch ( uiIndividualListenerTest ){
		case 1:{
			//remove the individual listener
			cout<<"pEnviroment->unregisterIndividualListener( pTestIndividualListener ); "<<endl;
			bool bIndividualListenerDeleted =
				pEnviroment->unregisterIndividualListener( liIndividualListeners.front() );
			if ( bIndividualListenerDeleted ){
			
				cout<<"The individuallistener was correctly removed . "<<endl;
			}else{
				cerr<<"Error: The individuallistener coldn't be removed ."<<endl;
				iReturn++;
			}
			//remove the same individual listener a second time
			cout<<"pEnviroment->unregisterIndividualListener( pTestIndividualListener ); "<<endl;
			bIndividualListenerDeleted =
				pEnviroment->unregisterIndividualListener( liIndividualListeners.front() );
			if ( ! bIndividualListenerDeleted ){
			
				cout<<"The individuallistener was correctly not removed again. "<<endl;
			}else{
				cerr<<"Error: The same individuallistener was removed again."<<endl;
				iReturn++;
			}
		}break;
		case 2:{
			//remove the individual listener
			cout<<"pEnviroment->unregisterIndividualListener( pTestIndividualListener ); "<<endl;
			bool bIndividualListenerDeleted =
				pEnviroment->unregisterIndividualListener( liIndividualListeners.front() );
			if ( bIndividualListenerDeleted ){
			
				cout<<"The individuallistener was correctly removed . "<<endl;
			}else{
				cerr<<"Error: The individuallistener coldn't be removed ."<<endl;
				iReturn++;
			}
			//remove the individual listener
			cout<<"pEnviroment->unregisterIndividualListener( pTestIndividualListener2 ); "<<endl;
			bIndividualListenerDeleted =
				pEnviroment->unregisterIndividualListener( liIndividualListeners.back() );
			if ( bIndividualListenerDeleted ){
			
				cout<<"The individuallistener was correctly removed . "<<endl;
			}else{
				cerr<<"Error: The individuallistener coldn't be removed ."<<endl;
				iReturn++;
			}
		}break;
		default:{
			//remove the individual listener
			cout<<"pEnviroment->unregisterIndividualListener( pTestIndividualListener ); "<<endl;
			bool bIndividualListenerDeleted =
				pEnviroment->unregisterIndividualListener( liIndividualListeners.front() );
			if ( bIndividualListenerDeleted ){
			
				cout<<"The individuallistener was correctly removed . "<<endl;
			}else{
				cerr<<"Error: The individuallistener coldn't be removed ."<<endl;
				iReturn++;
			}
		};
	};

	
	//delete the individual listeners
	while ( ! ( liIndividualListeners.empty() ) ){

		delete liIndividualListeners.front();
		liIndividualListeners.pop_front();
	}
	while ( ! ( liIndividualListenersOther.empty() ) ){

		delete liIndividualListenersOther.front();
		liIndividualListenersOther.pop_front();
	}

	//destroy the enviroment for the next test
	delete pEnviroment;
	ulAlgorithmId++;
	iReturn += checkIfEnviromentIsEmpty();

	return iReturn;
}




































