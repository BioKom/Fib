/**
 * file name: version.h
 * @author Betti Oesterholz
 * @date 26.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains switches for the enviroment.
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
 * This file contains the versionsinformation for the enviroment implementation.
 * This includes descriptions of declarations for versioned
 * programming switches.
 *
 */
/*
History:
26.04.2009  Oesterholz  created
*/


/**************************************
* Version Information
**************************************/

//Versionsinformation for the enviroment
#define ENVIROMENT_VERSION          0
#define ENVIROMENT_VERSION_NAME     V0.0.0



/**************************************
* versioned programming switches
**************************************/



/**
 * With this feature the getIndividual() method of the enviroment cEnviroment
 * will return with a probability of 1/256 the original individual.
 * @see cEnviroment::getIndividual()
 *
 * created: 05.07.2010  Betti Oesterholz
 * Status:  tested
 *//*
History:
*/
#define FEATURE_GET_INDIVIDUAL_WITH_ORIGINAL


/**
 * With this feature the deleteNotRunningOperations() method of the
 * enviroment cEnviroment will check every secound all operations on the
 * running list, if they still run. If an operation is found wich dosn't
 * run anymore, it's status will be changed to not running.
 * @see cEnviroment::deleteNotRunningOperations()
 *
 * created: 05.07.2010  Betti Oesterholz
 * Status:  tested
 *//*
History:
*/
#define FEATURE_CHECK_RUNNIG_OP_FOR_DELETE







