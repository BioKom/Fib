/**
 * @file tEndConditionCheck
 * file name: tEndConditionCheck.cpp
 * @author Betti Oesterholz
 * @date 15.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cEndConditionCheck.
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
 * This file contains the test for the class cEndConditionCheck.
 *
 *
 *  What's tested of class cEndConditionCheck:
 * 	- cEndConditionCheck();
 * 	- cEndConditionCheck( const cEndConditionCheck & endConditionCheck );
 * 	- ~cEndConditionCheck();
 * 	- string getClassName() const;
 * 	- bool endConditionCheck();
 * 	- cObjectFitness * getMaxFitness() const;
 * 	- bool setMaxFitness( cObjectFitness * fitness=NULL );
 * 	- unsigned long getMaxOperationCalls() const;
 * 	- bool setMaxOperationCalls( unsigned long lMaxCalls=0 );
 * 	- double getMaxCpuRuntime() const;
 * 	- double setMaxCpuRuntime( double dMaxCpuTime=-1.0 );
 * 	- double getMaxRuntime() const;
 * 	- bool setMaxRuntime( double dMaxTime=-1.0 );
 * 	- time_t getMaxDate() const;
 * 	- bool setMaxDate( time_t tMaxDate=0 );
 * 	- EndConditionCheck * clone() const;
 *
 */
/*
History:
14.03.2010  Oesterholz  created
16.09.2010  Oesterholz  getClassName() added
24.11.2011  Oesterholz  wait some time befor check isRunning() of enviroment
15.03.2012  Oesterholz  changes for windows compatibility
26.10.2012  Oesterholz  fibMilliSleep() delay handling improved (from tEnviroment)
*/

#include "version.h"

#include "cEndConditionCheck.h"

#include "cEnviroment.h"
#include "cInitFibEnviroment.h"
#include "cFibObjectFitnessBasic.h"
#include "cFibObjectFitnessBasicAlgorithm.h"
#include "cEndConditionCheck.h"
#include "cResourceCheck.h"
#include "cFibIndividual.h"

#include "cRoot.h"
#include "cPoint.h"

#include <utility>
#include <iostream>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>


using namespace enviroment::fib;
using namespace enviroment;
using namespace std;

int testParameter( unsigned long &ulTestphase );
int testEndConditionCheck( unsigned long &ulTestphase );
int testCopy( unsigned long &ulTestphase );


int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	

	cout<<endl<<"Running Test for cEndConditionCheck methods"<<endl;
	cout<<      "==========================================="<<endl;

	iReturn += testParameter( ulTestphase );
	iReturn += testEndConditionCheck( ulTestphase );
	iReturn += testCopy( ulTestphase );


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


/**
 * This function tests parameter of the given cEndConditionCheck object
 * are set to the given values.
 *
 * methods tested:
 * 	- cObjectFitness * getMaxFitness() const;
 * 	- unsigned long getMaxOperationCalls() const;
 * 	- double getMaxCpuRuntime() const;
 * 	- double getMaxRuntime() const;
 * 	- time_t getMaxDate() const;
 *
 * @param pEndCondition a pointer to the the endcondition object to check
 * @param pMaxFitness the maximal fitness the endcondition should have
 * @param ulMaxOperationCalls the maximal number of operation calls for
 * 	the endcondition to hold
 * @param dMaxCpuRuntime the maximal cpu -time the enviroment should run
 * @param dMaxRuntime the maximal runtime the enviroment should run
 * @param tmMaxDate the maximal date/ time till which the enviroment should run
 * @return the number of erros occured in the test
 */
int checkParameter( const cEndConditionCheck * const pEndCondition,
		cObjectFitness * pMaxFitness, unsigned long ulMaxOperationCalls,
		double dMaxCpuRuntime, double dMaxRuntime, time_t tmMaxDate ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( pEndCondition == NULL ){
		cerr<<"Error: No endcondition to check given."<<endl;
		iReturn++;
		return iReturn;
	}
	if ( pEndCondition->getClassName() == "cEndConditionCheck" ){
	
		cout<<"The classname is correctly \"cEndConditionCheck\" . "<<endl;
	}else{
		cerr<<"Error: The classname is \""<<pEndCondition->getClassName()<<
			"\", but should be correctly \"cEndConditionCheck\"."<<endl;
		iReturn++;
	}
	//check the maximal fitness
	if ( pMaxFitness == NULL ){
		if ( (pEndCondition->getMaxFitness()) == NULL ){
		
			cout<<"The maximal fitness of the endcondition is correctly NULL. "<<endl;
		}else{
			cerr<<"Error: The maximal fitness of the endcondition isn't NULL, but should be."<<endl;
			iReturn++;
		}
	}else{
		if ( (pEndCondition->getMaxFitness()) != NULL ){
			if ( (*(pEndCondition->getMaxFitness())) == *pMaxFitness ){
			
				cout<<"The maximal fitness of the endcondition is correct. "<<endl;
			}else{
				cerr<<"Error: The maximal fitness of the endcondition isn't correct."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The maximal fitness of the endcondition is NULL, but should be."<<endl;
			iReturn++;
		}
	}
	//check the maximal number of operation calls
	if ( (pEndCondition->getMaxOperationCalls()) == ulMaxOperationCalls ){
	
		cout<<"The maximal number of operation calls is correctly "<<
			ulMaxOperationCalls <<". "<<endl;
	}else{
		cerr<<"Error: The maximal number of operation calls is "<<
			(pEndCondition->getMaxOperationCalls()) <<", but should be "<<
			ulMaxOperationCalls <<"."<<endl;
		iReturn++;
	}
	//check the maximal cpu -time
	if ( 0.0 <= dMaxCpuRuntime ){
		if ( (pEndCondition->getMaxCpuRuntime()) == dMaxCpuRuntime ){
		
			cout<<"The maximal cpu -time is correctly "<< dMaxCpuRuntime <<". "<<endl;
		}else{
			cerr<<"Error: The maximal cpu -time is "<< (pEndCondition->getMaxCpuRuntime()) <<
				", but should be "<< dMaxCpuRuntime <<"."<<endl;
			iReturn++;
		}
	}else{
		if ( (pEndCondition->getMaxCpuRuntime()) < 0.0 ){
		
			cout<<"The maximal cpu -time is correctly lower 0 ("<< dMaxCpuRuntime <<"). "<<endl;
		}else{
			cerr<<"Error: The maximal cpu -time is not lower 0 ("<<
				(pEndCondition->getMaxCpuRuntime()) <<
				"), but should be ("<< dMaxCpuRuntime <<")."<<endl;
			iReturn++;
		}
	}
	//check the maximal runntime
	if ( 0.0 <= dMaxRuntime ){
		if ( (pEndCondition->getMaxRuntime()) == dMaxRuntime ){
		
			cout<<"The maximal runtime is correctly "<< dMaxRuntime <<". "<<endl;
		}else{
			cerr<<"Error: The maximal runtime is "<< (pEndCondition->getMaxRuntime()) <<
				", but should be "<< dMaxRuntime <<"."<<endl;
			iReturn++;
		}
	}else{
		if ( (pEndCondition->getMaxRuntime()) < 0.0 ){
		
			cout<<"The maximal runtime is correctly lower 0 ("<< dMaxRuntime <<"). "<<endl;
		}else{
			cerr<<"Error: The maximal runtime is not lower 0 ("<< (pEndCondition->getMaxRuntime()) <<
				"), but should be ("<< dMaxRuntime <<")."<<endl;
			iReturn++;
		}
	}
	//check the maximal date
	if ( (pEndCondition->getMaxDate()) == tmMaxDate ){
	
		cout<<"The maximal date is correctly "<< tmMaxDate <<". "<<endl;
	}else{
		cerr<<"Error: The maximal date is "<< (pEndCondition->getMaxDate()) <<
			", but should be "<< tmMaxDate <<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This function tests parameter methods of the cEndConditionCheck class.
 *
 * methods tested:
 * 	- cEndConditionCheck();
 * 	- cObjectFitness * getMaxFitness() const;
 * 	- bool setMaxFitness( cObjectFitness * fitness=NULL );
 * 	- unsigned long getMaxOperationCalls() const;
 * 	- bool setMaxOperationCalls( unsigned long lMaxCalls=0 );
 * 	- double getMaxCpuRuntime() const;
 * 	- double setMaxCpuRuntime( double dMaxCpuTime=-1.0 );
 * 	- double getMaxRuntime() const;
 * 	- bool setMaxRuntime( double dMaxTime=-1.0 );
 * 	- time_t getMaxDate() const;
 * 	- bool setMaxDate( time_t tMaxDate=0 );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testParameter( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods to set and get the endcondition parameters"<<endl;
	
	cout<<"cEndConditionCheck endCondition;"<<endl;
	cEndConditionCheck endCondition;
	
	cObjectFitness * pMaxFitness = NULL;
	unsigned long ulMaxOperationCalls = 0;
	double dMaxCpuRuntime = -1.0;
	double dMaxRuntime    = -1.0;
	time_t tmMaxDate      = 0;
	
	iReturn += checkParameter( & endCondition, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	cout<<"cFibObjectFitnessBasic fitness( 1.0, 0, 0, 1.0, 1.0, 1.0, NULL );"<<endl;
	cFibObjectFitnessBasic fitness( 1.0, 0, 0, 1.0, 1.0, 1.0, NULL );
	
	//check the setMaxFitness()
	cout<<"endCondition.setMaxFitness( &fitness );"<<endl;
	bool bMaxFitnessSet = endCondition.setMaxFitness( &fitness );
	pMaxFitness = &fitness;
	if ( bMaxFitnessSet ){
	
		cout<<"The maximal fitness could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The maximal fitness couldn't be set."<<endl;
		iReturn++;
	}
	iReturn += checkParameter( & endCondition, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	cout<<"endCondition.setMaxFitness( NULL );"<<endl;
	bMaxFitnessSet = endCondition.setMaxFitness( NULL );
	pMaxFitness = NULL;
	if ( bMaxFitnessSet ){
	
		cout<<"The maximal fitness could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The maximal fitness couldn't be set."<<endl;
		iReturn++;
	}
	iReturn += checkParameter( & endCondition, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	//check setMaxOperationCalls()
	cout<<"endCondition.setMaxOperationCalls( 13 );"<<endl;
	bool bParameterSet = endCondition.setMaxOperationCalls( 13 );
	ulMaxOperationCalls = 13;
	if ( bParameterSet ){
	
		cout<<"The maximal operations calls could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The maximal operations calls couldn't be set."<<endl;
		iReturn++;
	}
	iReturn += checkParameter( & endCondition, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	cout<<"endCondition.setMaxOperationCalls( 0 );"<<endl;
	bParameterSet = endCondition.setMaxOperationCalls( 0 );
	ulMaxOperationCalls = 0;
	if ( bParameterSet ){
	
		cout<<"The maximal operations calls could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The maximal operations calls couldn't be set."<<endl;
		iReturn++;
	}
	iReturn += checkParameter( & endCondition, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	cout<<"endCondition.setMaxCpuRuntime( 1.2 );"<<endl;
	bParameterSet = endCondition.setMaxCpuRuntime( 1.2 );
	dMaxCpuRuntime = 1.2;
	if ( bParameterSet ){
	
		cout<<"The maximal cpu -time could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The maximal cpu -time couldn't be set."<<endl;
		iReturn++;
	}
	iReturn += checkParameter( & endCondition, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	cout<<"endCondition.setMaxCpuRuntime( -0.5 );"<<endl;
	bParameterSet = endCondition.setMaxCpuRuntime( -0.5 );
	dMaxCpuRuntime = -0.5;
	if ( bParameterSet ){
	
		cout<<"The maximal cpu -time could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The maximal cpu -time couldn't be set."<<endl;
		iReturn++;
	}
	iReturn += checkParameter( & endCondition, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	cout<<"endCondition.setMaxRuntime( 12.54 );"<<endl;
	bParameterSet = endCondition.setMaxRuntime( 12.54  );
	dMaxRuntime = 12.54;
	if ( bParameterSet ){
	
		cout<<"The maximal runtime could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The maximal runtime couldn't be set."<<endl;
		iReturn++;
	}
	iReturn += checkParameter( & endCondition, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	cout<<"endCondition.setMaxRuntime( -2.75 );"<<endl;
	bParameterSet = endCondition.setMaxRuntime( -2.75  );
	dMaxRuntime = -2.75;
	if ( bParameterSet ){
	
		cout<<"The maximal runtime could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The maximal runtime couldn't be set."<<endl;
		iReturn++;
	}
	iReturn += checkParameter( & endCondition, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	cout<<"endCondition.setMaxDate( 2451 );"<<endl;
	bParameterSet = endCondition.setMaxDate( 2451  );
	tmMaxDate = 2451;
	if ( bParameterSet ){
	
		cout<<"The enddate could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The tmMaxDate couldn't be set."<<endl;
		iReturn++;
	}
	iReturn += checkParameter( & endCondition, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	cout<<"endCondition.setMaxDate( 0 );"<<endl;
	bParameterSet = endCondition.setMaxDate( 0  );
	tmMaxDate = 0;
	if ( bParameterSet ){
	
		cout<<"The enddate could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The tmMaxDate couldn't be set."<<endl;
		iReturn++;
	}
	iReturn += checkParameter( & endCondition, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );


	//check the setMaxFitness()
	cout<<"endCondition.setMaxFitness( &fitness );"<<endl;
	bParameterSet = endCondition.setMaxFitness( &fitness );
	pMaxFitness = &fitness;
	if ( bParameterSet ){
	
		cout<<"The maximal fitness could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The maximal fitness couldn't be set."<<endl;
		iReturn++;
	}
	iReturn += checkParameter( & endCondition, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	//check setMaxOperationCalls()
	cout<<"endCondition.setMaxOperationCalls( 574 );"<<endl;
	bParameterSet = endCondition.setMaxOperationCalls( 574 );
	ulMaxOperationCalls = 574;
	if ( bParameterSet ){
	
		cout<<"The maximal operations calls could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The maximal operations calls couldn't be set."<<endl;
		iReturn++;
	}
	iReturn += checkParameter( & endCondition, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	cout<<"endCondition.setMaxCpuRuntime( 654.123 );"<<endl;
	bParameterSet = endCondition.setMaxCpuRuntime( 654.123 );
	dMaxCpuRuntime = 654.123;
	if ( bParameterSet ){
	
		cout<<"The maximal cpu -time could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The maximal cpu -time couldn't be set."<<endl;
		iReturn++;
	}
	iReturn += checkParameter( & endCondition, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	cout<<"endCondition.setMaxRuntime( 123.456 );"<<endl;
	bParameterSet = endCondition.setMaxRuntime( 123.456 );
	dMaxRuntime = 123.456;
	if ( bParameterSet ){
	
		cout<<"The maximal runtime could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The maximal runtime couldn't be set."<<endl;
		iReturn++;
	}
	iReturn += checkParameter( & endCondition, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	cout<<"endCondition.setMaxDate( 1975 );"<<endl;
	bParameterSet = endCondition.setMaxDate( 1975  );
	tmMaxDate = 1975;
	if ( bParameterSet ){
	
		cout<<"The enddate could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The tmMaxDate couldn't be set."<<endl;
		iReturn++;
	}
	iReturn += checkParameter( & endCondition, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	cout<<"endCondition.setMaxRuntime( 652.159 );"<<endl;
	bParameterSet = endCondition.setMaxRuntime( 652.159 );
	dMaxRuntime = 652.159;
	if ( bParameterSet ){
	
		cout<<"The maximal runtime could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The maximal runtime couldn't be set."<<endl;
		iReturn++;
	}
	iReturn += checkParameter( & endCondition, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	cout<<"endCondition.setMaxOperationCalls( 84395 );"<<endl;
	bParameterSet = endCondition.setMaxOperationCalls( 84395 );
	ulMaxOperationCalls = 84395;
	if ( bParameterSet ){
	
		cout<<"The maximal operations calls could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The maximal operations calls couldn't be set."<<endl;
		iReturn++;
	}
	iReturn += checkParameter( & endCondition, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	return iReturn;
}



/**
 * This function staurts the enviroment with the given parameters.
 *
 * @param pEndConditionCheck a pointer to the cEndConditionCheck
 * 	object to test
 * @return the number of erros occured in the test
 */
int startEnviroment( cEndConditionCheck * pEndConditionCheck ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	//destroy the enviroment if it exists
	cEnviroment * pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment != NULL ){
	
		delete pEnviroment;
	}

	//set the parameter of the enviroment
	cVectorPosition vecPosition( 2 );
	vecPosition.setValue( 1, 1 );
	cPoint point1( &vecPosition );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cRoot rootInit( &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cRoot rootInit( NULL, NULL, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	
	cout<<"cInitFibEnviroment initEnviroment( rootInit ); "<<endl;
	cInitFibEnviroment initEnviroment( rootInit );

	vecPosition.setValue( 1, 10 );
	cPoint point2( &vecPosition );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cRoot rootOrg( &point2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cRoot rootOrg( NULL, NULL, &point2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	rootOrg.setNumberOfInputVariables( 1 );

	cout<<"cFibObjectFitnessBasicAlgorithm fibObjectAlgorithmBasic( rootOrg, 1, 1.0, 1.0 );"<<endl;
	cFibObjectFitnessBasicAlgorithm fibObjectAlgorithmBasic( rootOrg, 1, 1.0, 1.0 );
	
	//set the parameter of the enviroment
	cout<<"bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic, pEndConditionCheck );"<<endl;
	const bool bParameterSet = cEnviroment::setParameter(
		&initEnviroment, &fibObjectAlgorithmBasic, pEndConditionCheck );

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
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl<<flush;
		iReturn++;
		return iReturn;
	}
	//start the enviroment
	cout<<"pEnviroment->start(); "<<endl<<flush;
	pEnviroment->start();
	
	return iReturn;
}



/**
 * This function tests parameter of the given enviroment, if it stoped
 * correctly because of the endcondition.
 *
 * @param pMaxFitness the maximal fitness the enviroment should have
 * @param ulMaxOperationCalls the maximal number of operation calls for
 * 	the enviroment to stop
 * @param dMaxCpuRuntime the maximal cpu -time the enviroment should run
 * @param dMaxRuntime the maximal runtime the enviroment should run
 * @param tmMaxDate the maximal date/ time till which the enviroment should run
 * @return the number of erros occured in the test
 */
int checkIfEnviromentEndsCorrectly( cObjectFitness * pMaxFitness, unsigned long ulMaxOperationCalls,
		double dMaxCpuRuntime, double dMaxRuntime, time_t tmMaxDate ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cEnviroment * pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment == NULL ){
	
		cerr<<"Error: No enviroment exists to check."<<endl;
		iReturn++;
		return iReturn;
	}
	//check the maximum fitness
	if ( pMaxFitness != NULL ){
		cout<<"pIndividualinfo = pEnviroment->getBestIndividualInfo( "<< 1 <<", living ); "<<endl;
		const cIndividualInfo * pIndividualInfo = pEnviroment->getBestIndividualInfo( 1, 1 );
		if ( pIndividualInfo != NULL ){
			
			if ( (*pMaxFitness) < (*(pIndividualInfo->getFitness())) ){
				
				cout<<"The best individual in the enviroment is better than the maximum fitness. "<<endl;
			}else{
				cerr<<"Error: The best individual in the enviroment is not better than the maximum fitness."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: Couldn't get the individual information for the best individual."<<endl;
			iReturn++;
		}
	}
	//check the maximum number of called operations
	if ( ulMaxOperationCalls != 0 ){
		if ( ulMaxOperationCalls < pEnviroment->getNumberOfCalledOperations() ){
		
			cout<<"The number of called operations is correctly greater than "<<
				ulMaxOperationCalls <<" ( "<< pEnviroment->getNumberOfCalledOperations() <<" ) . "<<endl;
		}else{
			cerr<<"Error: The number of called operations is not greater than "<<
				ulMaxOperationCalls <<" ( "<< pEnviroment->getNumberOfCalledOperations() <<" ) . "<<endl;
			iReturn++;
		}
	}
	//check the maximum cpu -time
	if ( 0.0 < dMaxCpuRuntime ){
		if ( dMaxCpuRuntime < pEnviroment->getCpuRunTime() ){
		
			cout<<"The cpu -runtime is correctly greater than "<<
				dMaxCpuRuntime <<" ( "<< pEnviroment->getCpuRunTime() <<" ) . "<<endl;
		}else{
			cerr<<"Error: The cpu -runtime is not greater than "<< dMaxCpuRuntime <<
				" ( "<< pEnviroment->getCpuRunTime() <<" ) . "<<endl;
			iReturn++;
		}
	}
	//check the maximum runtime
	if ( 0.0 < dMaxRuntime ){
		double dEnviromentRuntime = (time(0) - pEnviroment->getFirstStartTime());
		if ( dMaxRuntime < dEnviromentRuntime ){
		
			cout<<"The runtime is correctly greater than "<<
				dMaxRuntime <<" ( "<< dEnviromentRuntime <<" ) . "<<endl;
		}else{
			cerr<<"Error: The runtime is not greater than "<< dMaxCpuRuntime <<
				" ( "<< dEnviromentRuntime <<" ) . "<<endl;
			iReturn++;
		}
	}
	//check the maximum runtime
	if ( tmMaxDate != 0 ){
		time_t tActualTime = time(0);
		if ( tmMaxDate < tActualTime ){
		
			cout<<"The maximum date /time is correctly greater than "<<
				tmMaxDate <<" ( "<< tActualTime <<" ) . "<<endl;
		}else{
			cerr<<"Error: The maximum date /time is not greater than "<<
				tmMaxDate <<" ( "<< tActualTime <<" ) . "<<endl;
			iReturn++;
		}
	}

	return iReturn;
}



/**
 * This function tests cEndConditionCheck class.
 *
 * methods tested:
 * 	- cEndConditionCheck();
 * 	- ~cEndConditionCheck();
 * 	- bool endConditionCheck();
 * 	- cObjectFitness * getMaxFitness() const;
 * 	- bool setMaxFitness( cObjectFitness * fitness=NULL );
 * 	- unsigned long getMaxOperationCalls() const;
 * 	- bool setMaxOperationCalls( unsigned long lMaxCalls=0 );
 * 	- double getMaxCpuRuntime() const;
 * 	- double setMaxCpuRuntime( double dMaxCpuTime=-1.0 );
 * 	- double getMaxRuntime() const;
 * 	- bool setMaxRuntime( double dMaxTime=-1.0 );
 * 	- time_t getMaxDate() const;
 * 	- bool setMaxDate( time_t tMaxDate=0 );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testEndConditionCheck( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the endcondition with maximal operation calls"<<endl;
	
	cout<<"cEndConditionCheck endConditionMaxOperationCalls;"<<endl;
	cEndConditionCheck endConditionMaxOperationCalls;
	cout<<"endConditionMaxOperationCalls.setMaxOperationCalls( 5 );"<<endl;
	endConditionMaxOperationCalls.setMaxOperationCalls( 5 );
	
	cObjectFitness * pMaxFitness = NULL;
	unsigned long ulMaxOperationCalls = 5;
	double dMaxCpuRuntime = -1.0;
	double dMaxRuntime    = -1.0;
	time_t tmMaxDate      = 0;
	
	iReturn += checkParameter( & endConditionMaxOperationCalls,
		pMaxFitness, ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	//test endConditionCheck() is false
	if ( ! endConditionMaxOperationCalls.endConditionCheck() ){
	
		cout<<"The endcondition is correctly false. "<<endl;
	}else{
		cerr<<"Error: The endcondition is true."<<endl;
		iReturn++;
	}
	
	iReturn += startEnviroment( & endConditionMaxOperationCalls );
	//wait till it's done / the endcondition holds
	
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	cEnviroment * pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment == NULL ){
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
		return iReturn;
	}
	fibMilliSleep( 10 );
	while ( pEnviroment->isRunning() ){
		//delay if enougth enviroments are running
		fibMilliSleep( 10 );
	}
	//check enviroment values
	iReturn += checkIfEnviromentEndsCorrectly( pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	//check endcondition values
	iReturn += checkParameter( & endConditionMaxOperationCalls,
		pMaxFitness, ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	//test endConditionCheck() is true
	if ( endConditionMaxOperationCalls.endConditionCheck() ){
	
		cout<<"The endcondition is correctly true. "<<endl;
	}else{
		cerr<<"Error: The endcondition is false."<<endl;
		iReturn++;
	}
	delete pEnviroment;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the endcondition with maximal cpu -time"<<endl;
	
	cout<<"cEndConditionCheck endConditionMaxCpuTime;"<<endl;
	cEndConditionCheck endConditionMaxCpuTime;
	cout<<"endConditionMaxCpuTime.setMaxOperationCalls( 2.0 );"<<endl;
	endConditionMaxCpuTime.setMaxCpuRuntime( 2.0 );
	
	pMaxFitness = NULL;
	ulMaxOperationCalls = 0;
	dMaxCpuRuntime = 2.0;
	dMaxRuntime    = -1.0;
	tmMaxDate      = 0;
	
	iReturn += checkParameter( & endConditionMaxCpuTime,
		pMaxFitness, ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	//test endConditionCheck() is false
	if ( ! endConditionMaxCpuTime.endConditionCheck() ){
	
		cout<<"The endcondition is correctly false. "<<endl;
	}else{
		cerr<<"Error: The endcondition is true."<<endl;
		iReturn++;
	}
	
	iReturn += startEnviroment( & endConditionMaxCpuTime );
	//wait till it's done / the endcondition holds
	
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment == NULL ){
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
		return iReturn;
	}
	fibMilliSleep( 10 );
	while ( pEnviroment->isRunning() ){
		//delay if enougth enviroments are running
		fibMilliSleep( 10 );
	}
	//check enviroment values
	iReturn += checkIfEnviromentEndsCorrectly( pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	//check endcondition values
	iReturn += checkParameter( & endConditionMaxCpuTime,
		pMaxFitness, ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	//test endConditionCheck() is true
	if ( endConditionMaxCpuTime.endConditionCheck() ){
	
		cout<<"The endcondition is correctly true. "<<endl;
	}else{
		cerr<<"Error: The endcondition is false."<<endl;
		iReturn++;
	}
	delete pEnviroment;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the endcondition with maximal runtime"<<endl;
	
	cout<<"cEndConditionCheck endConditionMaxRunTime;"<<endl;
	cEndConditionCheck endConditionMaxRunTime;
	cout<<"endConditionMaxRunTime.setMaxRuntime( 2.0 );"<<endl;
	endConditionMaxRunTime.setMaxRuntime( 2.0 );
	
	pMaxFitness = NULL;
	ulMaxOperationCalls = 0;
	dMaxCpuRuntime = -1.0;
	dMaxRuntime    = 2.0;
	tmMaxDate      = 0;
	
	iReturn += checkParameter( & endConditionMaxRunTime,
		pMaxFitness, ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	//test endConditionCheck() is false
	if ( ! endConditionMaxRunTime.endConditionCheck() ){
	
		cout<<"The endcondition is correctly false. "<<endl;
	}else{
		cerr<<"Error: The endcondition is true."<<endl;
		iReturn++;
	}
	
	iReturn += startEnviroment( & endConditionMaxRunTime );
	//wait till it's done / the endcondition holds
	
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment == NULL ){
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
		return iReturn;
	}
	fibMilliSleep( 10 );
	while ( pEnviroment->isRunning() ){
		//delay if enougth enviroments are running
		fibMilliSleep( 10 );
	}
	//check enviroment values
	iReturn += checkIfEnviromentEndsCorrectly( pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	//check endcondition values
	iReturn += checkParameter( & endConditionMaxRunTime,
		pMaxFitness, ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	//test endConditionCheck() is true
	if ( endConditionMaxRunTime.endConditionCheck() ){
	
		cout<<"The endcondition is correctly true. "<<endl;
	}else{
		cerr<<"Error: The endcondition is false."<<endl;
		iReturn++;
	}
	delete pEnviroment;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the endcondition with maximal end date"<<endl;
	
	cout<<"cEndConditionCheck endConditionMaxDate;"<<endl;
	cEndConditionCheck endConditionMaxDate;
	pMaxFitness = NULL;
	ulMaxOperationCalls = 0;
	dMaxCpuRuntime = -1.0;
	dMaxRuntime    = -1.0;
	tmMaxDate      = time( NULL ) + 2;
	
	cout<<"endConditionMaxDate.setMaxDate( tmMaxDate );"<<endl;
	endConditionMaxDate.setMaxDate( tmMaxDate );
	
	iReturn += checkParameter( & endConditionMaxDate,
		pMaxFitness, ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	//test endConditionCheck() is false
	if ( ! endConditionMaxDate.endConditionCheck() ){
	
		cout<<"The endcondition is correctly false. "<<endl;
	}else{
		cerr<<"Error: The endcondition is true."<<endl;
		iReturn++;
	}
	
	iReturn += startEnviroment( & endConditionMaxDate );
	//wait till it's done / the endcondition holds
	
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment == NULL ){
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
		return iReturn;
	}
	fibMilliSleep( 10 );
	while ( pEnviroment->isRunning() ){
		//delay if enougth enviroments are running
		fibMilliSleep( 10 );
	}
	//check enviroment values
	iReturn += checkIfEnviromentEndsCorrectly( pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	//check endcondition values
	iReturn += checkParameter( & endConditionMaxDate,
		pMaxFitness, ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	//test endConditionCheck() is true
	if ( endConditionMaxDate.endConditionCheck() ){
	
		cout<<"The endcondition is correctly true. "<<endl;
	}else{
		cerr<<"Error: The endcondition is false."<<endl;
		iReturn++;
	}
	unsigned long ulAlgorithmIdentifier = pEnviroment->getAlgorithmIdentifier();
	delete pEnviroment;
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the endcondition with maximal fitness"<<endl;
	
	cVectorPosition vecPosition( 2 );
	vecPosition.setValue( 1, 10 );
	cPoint point2( &vecPosition );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cRoot rootOrg( &point2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cRoot rootOrg( NULL, NULL, &point2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	rootOrg.setNumberOfInputVariables( 1 );

	cout<<"cFibObjectFitnessBasicAlgorithm fibObjectAlgorithmBasic( &rootOrg, 1, 1.0, 1.0 );"<<endl;
	cFibObjectFitnessBasicAlgorithm fibObjectAlgorithmBasic( &rootOrg, 1, 1.0, 1.0 );
	
	cout<<"cEndConditionCheck endConditionMaxFitness;"<<endl;
	cEndConditionCheck endConditionMaxFitness;
	
	pMaxFitness = fibObjectAlgorithmBasic.evalueFitness( &rootOrg );

	const list<cIndividualIdentifier> liParents;
	cOperationIdentifier operationId( ulAlgorithmIdentifier );
	cIndividualInfo orgIndividualInfo( ulAlgorithmIdentifier,
		liParents, * pMaxFitness, "no_operation", "original individual",
		operationId, time_t( NULL ), 1.0 , pMaxFitness );
	cFibIndividual orgIndividual( rootOrg.clone(), orgIndividualInfo );

	//make the max fitnes worst
	((cFibObjectFitnessBasic*)pMaxFitness)->changeDifferenceToOriginal( 3 );
	cout<<"endConditionMaxFitness.setMaxFitness( pMaxFitness );"<<endl;
	endConditionMaxFitness.setMaxFitness( pMaxFitness );
	
	ulMaxOperationCalls = 0;
	dMaxCpuRuntime = -1.0;
	dMaxRuntime    = -1.0;
	tmMaxDate      = 0;
	
	
	iReturn += checkParameter( & endConditionMaxFitness,
		pMaxFitness, ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	//test endConditionCheck() is false
	if ( ! endConditionMaxFitness.endConditionCheck() ){
	
		cout<<"The endcondition is correctly false. "<<endl;
	}else{
		cerr<<"Error: The endcondition is true."<<endl;
		iReturn++;
	}
	
	iReturn += startEnviroment( & endConditionMaxFitness );
	//wait till it's done / the endcondition holds
	
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment == NULL ){
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
		return iReturn;
	}
	
	cout<<"pEnviroment->insertIndividual( &orgIndividual="<<&orgIndividual<<" ); "<<endl<<flush;
	pEnviroment->insertIndividual( &orgIndividual );
	
	fibMilliSleep( 10 );
	while ( pEnviroment->isRunning() ){
		//delay if enougth enviroments are running
		fibMilliSleep( 10 );
	}
	//check enviroment values
	iReturn += checkIfEnviromentEndsCorrectly( pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	//check endcondition values
	iReturn += checkParameter( & endConditionMaxFitness,
		pMaxFitness, ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	//test endConditionCheck() is true
	if ( endConditionMaxFitness.endConditionCheck() ){
	
		cout<<"The endcondition is correctly true. "<<endl;
	}else{
		cerr<<"Error: The endcondition is false."<<endl;
		iReturn++;
	}
	delete pMaxFitness;
	delete pEnviroment;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the endcondition with the interrup SIGABRT"<<endl;
	
	cout<<"cEndConditionCheck endConditionInterruptSigabr;"<<endl;
	cEndConditionCheck endConditionInterruptSigabr;
	pMaxFitness = NULL;
	ulMaxOperationCalls = 0;
	dMaxCpuRuntime = -1.0;
	dMaxRuntime    = -1.0;
	tmMaxDate      = 0;
	
	iReturn += checkParameter( & endConditionInterruptSigabr,
		pMaxFitness, ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	//test endConditionCheck() is false
	if ( ! endConditionInterruptSigabr.endConditionCheck() ){
	
		cout<<"The endcondition is correctly false. "<<endl;
	}else{
		cerr<<"Error: The endcondition is true."<<endl;
		iReturn++;
	}
	
	iReturn += startEnviroment( & endConditionInterruptSigabr );
	//wait till it's done / the endcondition holds
	
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment == NULL ){
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
		return iReturn;
	}
	//kill the enviroment
#ifdef WINDOWS
	cout<<"raise( SIGTERM ); "<<endl;
	raise( SIGTERM );
#else //WINDOWS
	cout<<"kill( getpid(), SIGTERM ); "<<endl;
	kill( getpid(), SIGTERM );
#endif //WINDOWS

	fibMilliSleep( 10 );
	while ( pEnviroment->isRunning() ){
		//delay if enougth enviroments are running
		fibMilliSleep( 10 );
	}
	//check enviroment values
	iReturn += checkIfEnviromentEndsCorrectly( pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	//check endcondition values
	iReturn += checkParameter( & endConditionInterruptSigabr,
		pMaxFitness, ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	//test endConditionCheck() is true
	if ( endConditionInterruptSigabr.endConditionCheck() ){
	
		cout<<"The endcondition is correctly true. "<<endl;
	}else{
		cerr<<"Error: The endcondition is false."<<endl;
		iReturn++;
	}
	delete pEnviroment;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the endcondition with the interrup SIGINT"<<endl;
	
	cout<<"cEndConditionCheck endConditionInterruptSigint;"<<endl;
	cEndConditionCheck endConditionInterruptSigint;
	pMaxFitness = NULL;
	ulMaxOperationCalls = 0;
	dMaxCpuRuntime = -1.0;
	dMaxRuntime    = -1.0;
	tmMaxDate      = 0;
	
	iReturn += checkParameter( & endConditionInterruptSigint,
		pMaxFitness, ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	//test endConditionCheck() is false
	if ( ! endConditionInterruptSigint.endConditionCheck() ){
	
		cout<<"The endcondition is correctly false. "<<endl;
	}else{
		cerr<<"Error: The endcondition is true."<<endl;
		iReturn++;
	}
	
	iReturn += startEnviroment( & endConditionInterruptSigint );
	//wait till it's done / the endcondition holds
	
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment == NULL ){
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
		return iReturn;
	}
	//kill the enviroment
#ifdef WINDOWS
	cout<<"raise( SIGTERM ); "<<endl;
	raise( SIGTERM );
#else //WINDOWS
	cout<<"kill( getpid(), SIGTERM ); "<<endl;
	kill( getpid(), SIGTERM );
#endif //WINDOWS

	fibMilliSleep( 10 );
	while ( pEnviroment->isRunning() ){
		//delay if enougth enviroments are running
		fibMilliSleep( 10 );
	}
	//check enviroment values
	iReturn += checkIfEnviromentEndsCorrectly( pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	//check endcondition values
	iReturn += checkParameter( & endConditionInterruptSigint,
		pMaxFitness, ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	//test endConditionCheck() is true
	if ( endConditionInterruptSigint.endConditionCheck() ){
	
		cout<<"The endcondition is correctly true. "<<endl;
	}else{
		cerr<<"Error: The endcondition is false."<<endl;
		iReturn++;
	}
	delete pEnviroment;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the endcondition with the interrup SIGTERM"<<endl;
	
	cout<<"cEndConditionCheck endConditionInterruptSigterm;"<<endl;
	cEndConditionCheck endConditionInterruptSigterm;
	pMaxFitness = NULL;
	ulMaxOperationCalls = 0;
	dMaxCpuRuntime = -1.0;
	dMaxRuntime    = -1.0;
	tmMaxDate      = 0;
	
	iReturn += checkParameter( & endConditionInterruptSigterm,
		pMaxFitness, ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	//test endConditionCheck() is false
	if ( ! endConditionInterruptSigterm.endConditionCheck() ){
	
		cout<<"The endcondition is correctly false. "<<endl;
	}else{
		cerr<<"Error: The endcondition is true."<<endl;
		iReturn++;
	}
	
	iReturn += startEnviroment( & endConditionInterruptSigterm );
	//wait till it's done / the endcondition holds
	
	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment == NULL ){
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
		return iReturn;
	}
	//kill the enviroment
#ifdef WINDOWS
	cout<<"raise( SIGTERM ); "<<endl;
	raise( SIGTERM );
#else //WINDOWS
	cout<<"kill( getpid(), SIGTERM ); "<<endl;
	kill( getpid(), SIGTERM );
#endif //WINDOWS

	fibMilliSleep( 10 );
	while ( pEnviroment->isRunning() ){
		//delay if enougth enviroments are running
		fibMilliSleep( 10 );
	}
	//check enviroment values
	iReturn += checkIfEnviromentEndsCorrectly( pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	//check endcondition values
	iReturn += checkParameter( & endConditionInterruptSigterm,
		pMaxFitness, ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	//test endConditionCheck() is true
	if ( endConditionInterruptSigterm.endConditionCheck() ){
	
		cout<<"The endcondition is correctly true. "<<endl;
	}else{
		cerr<<"Error: The endcondition is false."<<endl;
		iReturn++;
	}
	delete pEnviroment;
	

	return iReturn;
}



/**
 * This function tests cEndConditionCheck class.
 *
 * methods tested:
 * 	- cEndConditionCheck( const cEndConditionCheck & endConditionCheck );
 * 	- EndConditionCheck * clone() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCopy( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the copyconstructor and the clone() method"<<endl;
	
	cout<<"cEndConditionCheck endCondition;"<<endl;
	cEndConditionCheck endCondition;
	
	cout<<"cFibObjectFitnessBasic fitness( 1.0, 0, 0, 1.0, 1.0, 1.0, NULL );"<<endl;
	cFibObjectFitnessBasic fitness( 1.0, 0, 0, 1.0, 1.0, 1.0, NULL );
	//check the setMaxFitness()
	cout<<"endCondition.setMaxFitness( &fitness );"<<endl;
	endCondition.setMaxFitness( &fitness );
	cout<<"endCondition.setMaxOperationCalls( 13 );"<<endl;
	endCondition.setMaxOperationCalls( 13 );
	cout<<"endCondition.setMaxCpuRuntime( 1.2 );"<<endl;
	endCondition.setMaxCpuRuntime( 1.2 );
	cout<<"endCondition.setMaxRuntime( 12.54 );"<<endl;
	endCondition.setMaxRuntime( 12.54  );
	cout<<"endCondition.setMaxDate( 2451 );"<<endl;
	endCondition.setMaxDate( 2451  );

	cObjectFitness * pMaxFitness = &fitness;
	unsigned long ulMaxOperationCalls = 13;
	double dMaxCpuRuntime = 1.2;
	double dMaxRuntime    = 12.54;
	time_t tmMaxDate      = 2451;

	iReturn += checkParameter( & endCondition, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	cout<<"cEndConditionCheck endConditionClone( endCondition );"<<endl;
	cEndConditionCheck endConditionClone( endCondition );

	iReturn += checkParameter( & endConditionClone, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	cout<<"pEndConditionClone = endCondition.clone();"<<endl;
	cEndConditionCheck * pEndConditionClone = endCondition.clone();

	iReturn += checkParameter( & endConditionClone, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	delete pEndConditionClone;


	cout<<"cEndConditionCheck endCondition1;"<<endl;
	cEndConditionCheck endCondition1;
	
	cout<<"cFibObjectFitnessBasic fitness1( 2.0, 3, 4, 1.0, 1.0, 1.0, NULL );"<<endl;
	cFibObjectFitnessBasic fitness1( 2.0, 3, 4, 1.0, 1.0, 1.0, NULL );
	//check the setMaxFitness()
	cout<<"endCondition1.setMaxFitness( &fitness1 );"<<endl;
	endCondition1.setMaxFitness( &fitness1 );
	cout<<"endCondition1.setMaxOperationCalls( 35 );"<<endl;
	endCondition1.setMaxOperationCalls( 35 );
	cout<<"endCondition1.setMaxCpuRuntime( 84.26 );"<<endl;
	endCondition1.setMaxCpuRuntime( 84.26 );
	cout<<"endCondition1.setMaxRuntime( 2154.265 );"<<endl;
	endCondition1.setMaxRuntime( 2154.265  );
	tmMaxDate     = time( NULL ) + 3600;
	cout<<"endCondition1.setMaxDate( "<< tmMaxDate <<" );"<<endl;
	endCondition1.setMaxDate( tmMaxDate  );

	pMaxFitness = &fitness1;
	ulMaxOperationCalls = 35;
	dMaxCpuRuntime = 84.26;
	dMaxRuntime    = 2154.265;

	iReturn += checkParameter( & endCondition1, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	cout<<"cEndConditionCheck endCondition1Clone( endCondition1 );"<<endl;
	cEndConditionCheck endCondition1Clone( endCondition1 );

	iReturn += checkParameter( & endCondition1Clone, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );

	cout<<"pEndConditionClone = endCondition1.clone();"<<endl;
	pEndConditionClone = endCondition1.clone();

	iReturn += checkParameter( & endCondition1Clone, pMaxFitness,
		ulMaxOperationCalls, dMaxCpuRuntime, dMaxRuntime, tmMaxDate );
	
	delete pEndConditionClone;


	return iReturn;
}








