/**
 * file name: versionCreator.h
 * @author Betti Oesterholz
 * @date 02.03.2014
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains switches for the different Fib creator versions.
 * Copyright (C) @c GPL3 2014 Betti Oesterholz
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
 * This file contains the versions information for the Fib
 * creator system implementation.
 * This includes descriptions of declarations for versioned
 * programming switches.
 *
 */
/*
History:
02.03.2014  Oesterholz  created
*/


//debugging information; define DEBUG to activate them
//#define DEBUG
#include "debugOut.inc"


/**************************************
* version information for the Fib creator application
**************************************/

#define FIB_CREATOR_VERSION          1
#define FIB_CREATOR_VERSION_NAME     V1.0.0


/*****************************************
* versioned programming debugging switches
******************************************/

/**
 * This switch prints debugging information, which prints the Fib object.
 */
//#define DEBUG_FIB_OBJECT



/**************************************
* versioned programming switches
**************************************/


/**
 * The delay time in seconds betwean when it should be tried to delete not
 * needed nodes.
 * @see cFibNodeHandler::tmNextDeleteNodesAction
 * @see cFibNodeHandler::deleteNodesWithoutListeners()
 */
#define TM_DELAY_BETWEAN_DELETE_NODES_ACTION 10


/**
 * With this feature the "used time" sorted Fib object info lists will be
 * stored for every subcategory.
 *
 * @see cFibObjectInfoHandler::mapUsedTimeSortedFibObjectInfos
 * created: 28.02.2014 Betti Oesterholz
 * status:  implemented and tested (02.03.2014)
 * depricated: not FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
 *//*
History:
*/
#define FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS



/**
 * With this feature the Fib node handler @see cFibNodeHandler
 * will use a more adaptive aproche, to integrate Fib objects into an
 * existing Fib node.
 *
 * @see nFibNodeHandler::integrateFibObjectIntoNode()
 * created: 03.02.2014 Betti Oesterholz
 * status:  running and tested (02.03.2014)
 * (deprecated: not FEATURE_INTEGRATE_FIB_OBJECT_INTO_NODE)
 *//*
History:
*/
#define FEATURE_INTEGRATE_FIB_OBJECT_INTO_NODE









