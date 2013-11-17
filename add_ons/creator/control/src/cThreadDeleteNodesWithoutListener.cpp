/**
 * @file cThreadDeleteNodesWithoutListener
 * file name: cThreadDeleteNodesWithoutListener.cpp
 * @author Betti Oesterholz
 * @date 14.06.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a smaal tread class for deleting nodes without
 * listeners in the node handler.
 *
 *
 * Copyright (C) @c GPL3 2013 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (GPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
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
 * This file implements a smaal tread class for deleting nodes without
 * listeners in the node handler. It is a helper class for the
 * @see cFibNodeHandler
 * This class implements a thread for calling the
 * @see cFibNodeHandler::deleteNodesWithoutListeners()
 * method of the Fib node handler.
 *
 * @pattern worker
 */
/*
History:
14.06.2013  Oesterholz  created
*/


#include "cThreadDeleteNodesWithoutListener.h"


using namespace fib::nCreator::nFibNodeHandler;


/**
 * constructor
 *
 * @param pParent parent of this class
 */
cThreadDeleteNodesWithoutListener::cThreadDeleteNodesWithoutListener(
		QObject * pParent ):QThread( pParent ){
	//nothing to do
}


/**
 * Call @see cFibNodeHandler::deleteNodesWithoutListeners()
 */
void cThreadDeleteNodesWithoutListener::run(){
	//run the deleteNodesWithoutListeners() method of the Fib node handler
	cFibNodeHandler::getInstance()->deleteNodesWithoutListeners();
}






