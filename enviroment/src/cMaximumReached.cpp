/**
 * @file cMaximumReached
 * file name: cMaximumReached.cpp
 * @author Betti Oesterholz
 * @date 18.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for checking if enougth individuals are
 * in the enviroment.
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
 * This header specifies a class for checking if enougth individuals are
 * in the enviroment. If the test is true, no more individuals should be
 * added to the enviroment, befor deleting some old individuals from it.
 * The test of this class (but not necessarily it's children) is true if:
 * 	- ther are more than 65 536 individuals in the enviroment
 * 	- ther are more then 16 (=MIN_INDIVIDUALS) individuals in the
 * 		envirmonet and less than 10 % of the main memory free
 *
 * @see cEnviroment
 */
/*
History:
18.03.2010  Oesterholz  created
06.06.2010  Oesterholz  method getClassName() added
15.03.2012  Oesterholz  changes for windows compatibility
*/


#include "cMaximumReached.h"

#include "cEnviroment.h"

#ifdef WINDOWS
	#include <windows.h>
#else //WINDOWS
	#include <sys/sysinfo.h>
#endif //WINDOWS

/*the minimum number of individuals;
if less individuals exists, the memory wont be checked*/
#define MIN_INDIVIDUALS 16


using namespace std;

using namespace enviroment;


/**
 * Destructor of the class cMaximumReached.
 */
cMaximumReached::~cMaximumReached(){
	//nothing to do
}


/**
 * @return true if no more individuals should be added to the
 * 	enviroment, else false
 */
bool cMaximumReached::maximumReached() const{

	cEnviroment * pEnviroment = cEnviroment::getInstance();
	
	if ( pEnviroment == NULL ){
		//nothing to check
		return NULL;
	}
	//check if ther are more than 65 536 individuals in the enviroment
	const unsigned long ulCountIndividuals =
		pEnviroment->getNumberOfIndividuals( 1 );
	if ( 65536 < ulCountIndividuals ){
		return true;
	}
	if ( MIN_INDIVIDUALS < ulCountIndividuals ){

#ifdef WINDOWS


#ifdef MEMORYSTATUSEX
		//for newer systems
		MEMORYSTATUSEX statex;
		statex.dwLength = sizeof( statex );
		GlobalMemoryStatusEx( &statex );
#else //MEMORYSTATUSEX
		//for older systems
		MEMORYSTATUS statex;
		statex.dwLength = sizeof( statex );
		GlobalMemoryStatus( &statex );
#endif //MEMORYSTATUSEX
		
		if ( 90 <= statex.dwMemoryLoad ){
			return true;
		}
#else//WINDOWS

		//check if 10 % of the main memory is free
		struct sysinfo sysInfo;
		const int iReturn = sysinfo( &sysInfo );
		if ( (iReturn == 0) &&
				((double)(sysInfo.freeram) / (double)(sysInfo.totalram) < 0.1 )){
			return true;
		}
#endif//WINDOWS
	}
	return false;
}


/**
 * This method clones this object.
 *
 * @return a clone of this object
 */
cMaximumReached * cMaximumReached::clone() const{

	return new cMaximumReached( *this );
}


/**
 * @return the name of this class
 */
std::string cMaximumReached::getClassName() const{
	return "cMaximumReached";
}





