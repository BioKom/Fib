/**
 * @file cThreadDeleteNodesWithoutListener
 * file name: cThreadDeleteNodesWithoutListener.h
 * @author Betti Oesterholz
 * @date 30.06.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a smaal tread class for deleting nodes without
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
 * This file specifies a smaal tread class for deleting nodes without
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
30.06.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__N_FIB_NODE_HANDLER__C_THREAD_DELETE_NODES_WITHOUT_LISTENERS_H__
#define ___FIB__NCREATOR__N_FIB_NODE_HANDLER__C_THREAD_DELETE_NODES_WITHOUT_LISTENERS_H__


#include "version.h"

#include <QThread>

#include "cFibNodeHandler.h"



using namespace std;


namespace fib{

namespace nCreator{

namespace nFibNodeHandler{


class cThreadDeleteNodesWithoutListener : public QThread{
		Q_OBJECT
	
friend class cFibNodeHandler;

public:
	
	/**
	 * constructor
	 *
	 * @param pParent parent of this class
	 */
	cThreadDeleteNodesWithoutListener( QObject * pParent = NULL );
	
	/**
	 * Call @see cFibNodeHandler::deleteNodesWithoutListeners()
	 */
	void run();
	
};//end class cThreadDeleteNodesWithoutListener


};//end namespace nFibNodeHandler
};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__N_FIB_NODE_HANDLER__C_THREAD_DELETE_NODES_WITHOUT_LISTENERS_H__





