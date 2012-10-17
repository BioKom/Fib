/**
 * @file cEndConditionCheck
 * file name: cEndConditionCheck.cpp
 * @author Betti Oesterholz
 * @date 15.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for checking the end condition of the
 * enviroment.
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
 * This header specifies a class for checking the end condition of the
 * enviroment.
 * This includes, if set, checking if:
 * 	- if a system signal to end the process was received (for Linux: HUP=1, QUIT=3, TERM=15)
 * 	- a maximal number of opertions wher performed
 * 	- a maximal fitness was reached
 * 	- a maximal CPU -time was reached
 * 	- a realtime runtime was reached
 * 	- a specific date was reached
 *
 * If one of the checks is positiv the endconditions holds and the
 * enviroment should be ended.
 *
 * @see cEnviroment
 */
/*
History:
15.03.2010  Oesterholz  created
*/


#include "cEndConditionCheck.h"

#include "cEnviroment.h"

#include <csignal>

using namespace enviroment;



bool cEndConditionCheck::bSignalAbortReceived = false;
bool cEndConditionCheck::bSignalInterruptReceived = false;
bool cEndConditionCheck::bSignalTerminateReceived = false;



/**
 * standardconstructor
 */
cEndConditionCheck::cEndConditionCheck():pMaxFitness( NULL ),
		lMaxOperationCalls( 0 ), dMaxCpuRuntime( -1.0 ) , dMaxRuntime( -1.0 ),
		maxDate( 0 ){
	
	bSignalAbortReceived = false;
	bSignalInterruptReceived = false;
	bSignalTerminateReceived = false;
	
	signal( SIGABRT, catchSignalAbort );
	signal( SIGINT, catchSignalInterrupt );
	signal( SIGTERM, catchSignalTerminate );
}


/**
 * Destructor of the class cEndConditionCheck.
 */
cEndConditionCheck::~cEndConditionCheck(){
	//nothing to do
	if ( pMaxFitness ){
		delete pMaxFitness;
	}
}


/**
 * copyconstructor
 */
cEndConditionCheck::cEndConditionCheck( const cEndConditionCheck & endConditionCheck ):
		lMaxOperationCalls( endConditionCheck.lMaxOperationCalls ),
		dMaxCpuRuntime( endConditionCheck.dMaxCpuRuntime ),
		dMaxRuntime( endConditionCheck.dMaxRuntime ),
		maxDate( endConditionCheck.maxDate ){
	
	if ( endConditionCheck.pMaxFitness ){
		pMaxFitness = endConditionCheck.pMaxFitness->clone();
	}else{
		pMaxFitness = NULL;
	}
}


/**
 * @return the name of this class
 */
string cEndConditionCheck::getClassName() const{
	return "cEndConditionCheck";
}


/**
 * @return true if the endcondition holds and the enviroment should be
 * 	stoped, else false
 */
bool cEndConditionCheck::endConditionCheck(){
	
	//check if a system signal to end the process was received
	if ( bSignalAbortReceived || bSignalInterruptReceived ||
			bSignalTerminateReceived ){
		return true;
	}
	
	//check if a maximal number of opertions wher performed
	cEnviroment * pEnviroment = cEnviroment::getInstance();
	
	if ( pEnviroment == NULL ){
		//can't check
		return false;
	}
	if ( (lMaxOperationCalls != 0) &&
			(lMaxOperationCalls < pEnviroment->getNumberOfCalledOperations()) ){
		//the maximal opertions endcondition holds
		return true;
	}

	//check if a maximal fitness was reached
	const cIndividualInfo * pBestIndividualInfo = pEnviroment->getBestIndividualInfo();
	
	if ( pBestIndividualInfo && pMaxFitness ){
		if ( *pMaxFitness < *(pBestIndividualInfo->getFitness()) ){
			//the maximal fitness endcondition holds
			return true;
		}
	}
	//check if a maximal CPU -time was reached
	if ( ( 0.0 < dMaxCpuRuntime ) &&
			( dMaxCpuRuntime < pEnviroment->getCpuRunTime() ) ){
		//the maximal CPU -time endcondition holds
		return true;
	}
	//check if a realtime runtime was reached
	if ( ( 0.0 < dMaxRuntime ) && ( pEnviroment->getFirstStartTime() != 0 ) &&
			( dMaxRuntime < (time(0) - pEnviroment->getFirstStartTime() ) ) ){
		//the maximal realtime runtime endcondition holds
		return true;
	}
	//check if a specific date was reached
	if ( ( maxDate != 0 ) && ( maxDate < time(0) ) ){
		//the maximal date endcondition holds
		return true;
	}
	return false;
}


/**
 * @see pMaxFitness
 * @return The maximal fitness for individuals in the enviroment.
 * 	If NULL the maximal fitness condition isn't checked/ is deaktivated.
 */
cObjectFitness * cEndConditionCheck::getMaxFitness() const{

	return pMaxFitness;
}


/**
 * This method sets the maximal fitness for individuals in the enviroment.
 * If NULL is set (standardvalue) the maximal fitness condition isn't
 * checked/ is deaktivated.
 *
 * @see pMaxFitness
 * @param fitness the maximal fitness for individuals in the enviroment
 * @return true if the fitness was set, else false
 */
bool cEndConditionCheck::setMaxFitness( cObjectFitness * fitness ){
	
	if ( pMaxFitness ){
		delete pMaxFitness;
	}
	if ( fitness ){
		pMaxFitness = fitness->clone();
	}else{
		pMaxFitness = NULL;
	}
	return true;
}


/**
 * @see lMaxOperationCalls
 * @return The maximum calls of operators/ operations executed of the enviroment.
 * 	If 0 the maximal operators condition isn't checked/ is deaktivated.
 */
unsigned long cEndConditionCheck::getMaxOperationCalls() const{
	return lMaxOperationCalls;
}


/**
 * This method sets the maximum calls of operators/ operations
 * executed of the enviroment.
 * If 0 is set (standardvalue) the operators fitness condition isn't
 * checked/ is deaktivated.
 *
 * @see lMaxOperationCalls
 * @param lMaxCalls the maximal calls of operators/ operations executed
 * 	of the enviroment
 * @return true if the maximal calls was set, else false
 */
bool cEndConditionCheck::setMaxOperationCalls( unsigned long lMaxCalls ){
	
	lMaxOperationCalls = lMaxCalls;
	return true;
}


/**
 * @see dMaxCpuRuntime
 * @return The maximum cpu -time (in system clocks) the enviroment can
 * 	consume. If negativ (-1.0) the maximal cpu -time condition isn't
 * 	checked/ is deaktivated.
 */
double cEndConditionCheck::getMaxCpuRuntime() const{
	return dMaxCpuRuntime;
}


/**
 * This method sets the maximum cpu -time (in system clocks) the
 * enviroment can consume.
 * If negativ (standardvalue = -1.0) the maximal cpu -time condition
 * isn't checked/ is deaktivated.
 *
 * @see dMaxCpuRuntime
 * @param dMaxCpuTime the maximal cpu -time the enviroment can consume
 * 	of the enviroment
 * @return true if the maximal cpu -time was set, else false
 */
double cEndConditionCheck::setMaxCpuRuntime( double dMaxCpuTime ){
	
	dMaxCpuRuntime = dMaxCpuTime;
	return true;
}


/**
 * @see dMaxRuntime
 * @return The maximum runtime (in secounds) the enviroment can consume.
 * 	If negativ (-1.0) the maximal runtime condition isn't checked/ is
 * 	deaktivated.
 */
double cEndConditionCheck::getMaxRuntime() const{
	return dMaxRuntime;
}


/**
 * This method sets the maximum runtime (in secounds) the enviroment
 * can consume.
 * If negativ (standardvalue = -1.0) the maximal runtime condition
 * isn't checked/ is deaktivated.
 *
 * @see dMaxRuntime
 * @param dMaxTime the maximal runtime the enviroment can consume
 * 	of the enviroment
 * @return true if the maximal runtime was set, else false
 */
bool cEndConditionCheck::setMaxRuntime( double dMaxTime ){
	
	dMaxRuntime = dMaxTime;
	return true;
}


/**
 * @see maxDate
 * @return The (real-)time /date till which the enviroment can run.
 * 	If 0 the maximal date condition isn't checked/ is deaktivated.
 */
time_t cEndConditionCheck::getMaxDate() const{
	return maxDate;
}


/**
 * This method sets the (real-)time /date till which the enviroment can run.
 * If 0 (standardvalue) the maximal date condition isn't checked/ is deaktivated.
 *
 * @see maxDate
 * @param tMaxDate the maximal date till which the enviroment can run
 * 	of the enviroment
 * @return true if the maximal date was set, else false
 */
bool cEndConditionCheck::setMaxDate( time_t tMaxDate ){
	
	maxDate = tMaxDate;
	return true;
}


/**
 * This method clones this object.
 *
 * @return a clone of this object
 */
cEndConditionCheck * cEndConditionCheck::clone() const{

	return new cEndConditionCheck( *this );
}


/**
 * This method should catch the signal abort.
 * @see bSignalAbortReceived
 */
void cEndConditionCheck::catchSignalAbort( int parameter ){
	bSignalAbortReceived = true;
}


/**
 * This method should catch the signal interrupt.
 * @see bSignalInterruptReceived
 */
void cEndConditionCheck::catchSignalInterrupt( int parameter ){
	bSignalInterruptReceived = true;
}


/**
 * This method should catch the signal terminate.
 * @see bSignalTerminateReceived
 */
void cEndConditionCheck::catchSignalTerminate( int parameter ){
	bSignalTerminateReceived = true;
}






