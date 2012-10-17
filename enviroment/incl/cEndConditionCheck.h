/**
 * @file cEndConditionCheck
 * file name: cEndConditionCheck.h
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
 * 	- a maximal CPU -check time was reached
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


#ifndef ___C_END_CONDITION_CHECK_H__
#define ___C_END_CONDITION_CHECK_H__

#include "version.h"

#include "cObjectFitness.h"

#include <ctime>


namespace enviroment{


class cEndConditionCheck{
protected:
	
	/**
	 * The maximal fitness for individuals in the enviroment.
	 * If NULL the maximal fitness condition isn't checked/ is deaktivated.
	 */
	cObjectFitness * pMaxFitness;
	
	/**
	 * The maximum calls of operators/ operations executed of the enviroment.
	 * If 0 the maximal operators condition isn't checked/ is deaktivated.
	 */
	unsigned long lMaxOperationCalls;
	
	/**
	 * The maximum cpu -time (in system clocks) the enviroment can consume.
	 * If negativ (-1.0) the maximal cpu -time condition isn't checked/ is deaktivated.
	 */
	double dMaxCpuRuntime;
	
	/**
	 * The maximum runtime (in secounds) the enviroment can consume.
	 * If negativ (-1.0) the maximal runtime condition isn't checked/ is deaktivated.
	 */
	double dMaxRuntime;
	
	/**
	 * The (real-)time /date till which the enviroment can run.
	 * If 0 the maximal date condition isn't checked/ is deaktivated.
	 */
	time_t maxDate;
	
	
	/**
	 * This variable is true if an signal abort was received, else false.
	 */
	static bool bSignalAbortReceived;
	
	/**
	 * This variable is true if an signal interrupt was received, else false.
	 */
	static bool bSignalInterruptReceived;
	
	/**
	 * This variable is true if an signal terminat was received, else false.
	 */
	static bool bSignalTerminateReceived;

	
public:
	
	/**
	 * standardconstructor
	 */
	cEndConditionCheck();
	
	/**
	 * copyconstructor
	 */
	cEndConditionCheck( const cEndConditionCheck & endConditionCheck );

	/**
	 * Destructor of the class cEndConditionCheck.
	 */
	virtual ~cEndConditionCheck();

	/**
	 * @return the name of this class
	 */
	virtual string getClassName() const;
	
	
	/**
	 * @return true if the endcondition holds and the enviroment should be
	 * 	stoped, else false
	 */
	virtual bool endConditionCheck();
	
	/**
	 * @see pMaxFitness
	 * @return The maximal fitness for individuals in the enviroment.
	 * 	If NULL the maximal fitness condition isn't checked/ is deaktivated.
	 */
	cObjectFitness * getMaxFitness() const;
	
	/**
	 * This method sets the maximal fitness for individuals in the enviroment.
	 * If NULL is set (standardvalue) the maximal fitness condition isn't
	 * checked/ is deaktivated.
	 *
	 * @see pMaxFitness
	 * @param fitness the maximal fitness for individuals in the enviroment
	 * @return true if the fitness was set, else false
	 */
	bool setMaxFitness( cObjectFitness * fitness=NULL );
	
	/**
	 * @see lMaxOperationCalls
	 * @return The maximum calls of operators/ operations executed of the enviroment.
	 * 	If 0 the maximal operators condition isn't checked/ is deaktivated.
	 */
	unsigned long getMaxOperationCalls() const;
	
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
	bool setMaxOperationCalls( unsigned long lMaxCalls=0 );
	
	/**
	 * @see dMaxCpuRuntime
	 * @return The maximum cpu -time (in system clocks) the enviroment can
	 * 	consume. If negativ (-1.0) the maximal cpu -time condition isn't
	 * 	checked/ is deaktivated.
	 */
	double getMaxCpuRuntime() const;
	
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
	double setMaxCpuRuntime( double dMaxCpuTime=-1.0 );
	
	/**
	 * @see dMaxRuntime
	 * @return The maximum runtime (in secounds) the enviroment can consume.
	 * 	If negativ (-1.0) the maximal runtime condition isn't checked/ is
	 * 	deaktivated.
	 */
	double getMaxRuntime() const;
	
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
	bool setMaxRuntime( double dMaxTime=-1.0 );
	
	/**
	 * @see maxDate
	 * @return The (real-)time /date till which the enviroment can run.
	 * 	If 0 the maximal date condition isn't checked/ is deaktivated.
	 */
	time_t getMaxDate() const;
	
	/**
	 * This method sets the (real-)time /date till which the enviroment can run.
	 * If 0 (standardvalue) the maximal date condition isn't checked/ is deaktivated.
	 *
	 * @see maxDate
	 * @param tMaxDate the maximal date till which the enviroment can run
	 * 	of the enviroment
	 * @return true if the maximal date was set, else false
	 */
	bool setMaxDate( time_t tMaxDate=0 );

	/**
	 * This method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cEndConditionCheck * clone() const;

private:
	
	/**
	 * This method should catch the signal abort.
	 * @see bSignalAbortReceived
	 */
	static void catchSignalAbort( int parameter );

	/**
	 * This method should catch the signal interrupt.
	 * @see bSignalInterruptReceived
	 */
	static void catchSignalInterrupt( int parameter );

	/**
	 * This method should catch the signal terminate.
	 * @see bSignalTerminateReceived
	 */
	static void catchSignalTerminate( int parameter );


};//end class cEndConditionCheck


};//end namespace enviroment

#endif //___C_END_CONDITION_CHECK_H__







