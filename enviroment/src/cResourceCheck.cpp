/**
 * @file cResourceCheck
 * file name: cResourceCheck.cpp
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
 * 	- ther are more then 16 individuals in the envirmonet and less than
 * 		10 % of the main memory free
 *
 * @see cEnviroment
 */
/*
History:
18.03.2010  Oesterholz  created
06.06.2010  Oesterholz  method getClassName() added
*/


#include "cResourceCheck.h"

#include "cEnviroment.h"


using namespace std;

using namespace enviroment;


/**
 * constructor
 *
 * @param uiInMaxOperationsToRun the maximal number of operations which
 * 	should run in the enviroment
 */
cResourceCheck::cResourceCheck( unsigned int uiInMaxOperationsToRun ):
		uiMaxOperationsToRun( uiInMaxOperationsToRun ) {
	//nothing to do
}


/**
 * Destructor of the class cResourceCheck.
 */
cResourceCheck::~cResourceCheck(){
	//nothing to do
}


/**
 * @return true if enougth resources exists to start more operations
 * 	(ther are under 32 operations running), else false
 */
bool cResourceCheck::enoughResources() const{

	cEnviroment * pEnviroment = cEnviroment::getInstance();
	
	if ( pEnviroment == NULL ){
		//nothing to check
		return NULL;
	}
	//check if ther are more than 65 536 individuals in the enviroment
	const unsigned int ulCountRunningOperations =
		pEnviroment->getNumberOfRunningOperations();
	if ( ulCountRunningOperations <= uiMaxOperationsToRun ){
		return true;
	}

	return false;
}


/**
 * This method clones this object.
 *
 * @return a clone of this object
 */
cResourceCheck * cResourceCheck::clone() const{

	return new cResourceCheck( *this );
}


/**
 * @return the name of this class
 */
string cResourceCheck::getClassName() const{
	return "cResourceCheck";
}






