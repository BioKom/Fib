/**
 * file name: version.h
 * @author Betti Oesterholz
 * @date 28.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains switches for the fib -enviroment.
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
 * This file contains the versionsinformation for the fib -enviroment
 * implementation.
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

//Versionsinformation for the fib -enviroment
#define FIB_ENVIROMENT_VERSION          0
#define FIB_ENVIROMENT_VERSION_NAME     V0.0.0



/**************************************
* versioned programming switches
**************************************/

/**
 * This feature sets a maximum for the evaluation time for the fitness
 * with cFibObjectFitnessBasicAlgorithm.
 *
 * created: 28.02.2010  Betti Oesterholz
 * Status:  tested
 *//*
History:
*/
#define FATURE_MAX_FITNESS_EVALUATION_TIME


/**
 * With this feature the original fib -object of the
 * cFibObjectFitnessAlgorithm will be balanced.
 * The value of the feature are the number of max underobjects per
 * listelement.
 *
 * @see cFibObjectFitnessAlgorithm
 * @see nBalanceLists::balanceFibTreeLists()
 * created: 28.08.2010  Betti Oesterholz
 * Status:  tested
 *//*
History:
*/
//#define FEATURE_ALGORITHM_WITH_BALANCED_FIB_OBJECT 8


/**
 * With this feature the the runEnviroment program will save also the best
 * actual individual, with it's lists reduced with eliminateListTrees()
 * (no listtrees).
 *
 * @see runEnviroment
 * @see nBalanceLists::eliminateListTrees()
 * created: 03.10.2010  Betti Oesterholz
 * Status:  tested
 *//*
History:
*/
//#define FEATURE_RUN_ENVIROMENT_SAVE_BEST_REDUCED_LIST










