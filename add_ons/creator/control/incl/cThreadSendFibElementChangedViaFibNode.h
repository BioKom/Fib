
//TODO check

/**
 * @file cThreadSendFibElementChangedViaFibNode
 * file name: cThreadSendFibElementChangedViaFibNode.h
 * @author Betti Oesterholz
 * @date 08.02.2014
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This is a worker class for a thread.
 * It will send, that a Fib element changed to the Fib node of the Fib element.
 *
 *
 * Copyright (C) @c GPL3 2014 Betti Oesterholz
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
 * This is a worker class for a thread.
 * It will send, that a Fib element changed to the Fib node of the Fib element.
 *
 * @pattern worker
 * @see eFibNodeChangedEvent
 * @see fib::cFibElement
 * @see cFibNode
 * @see cFibNodeHandler
 * @see QThread
 */
/*
History:
08.02.2014  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_THREAD_SEND_FIB_ELEMENT_CHANGED_VIA_FIB_NODE_H__
#define ___FIB__NCREATOR__C_THREAD_SEND_FIB_ELEMENT_CHANGED_VIA_FIB_NODE_H__


#include "version.h"

#include <QObject>
#include <QThread>

#include "cFibElement.h"


namespace fib{

namespace nCreator{


class cThreadSendFibElementChangedViaFibNode : public QThread {
		Q_OBJECT

public:
	/**
	 * The standard constructor for a worker.
	 *
	 * @param pInChangedFibElement a pointer to the changed Fib element
	 * 	@see pChangedFibElement
	 */
	cThreadSendFibElementChangedViaFibNode( fib::cFibElement * pInChangedFibElement );
	
	/**
	 * destructor
	 */
	~cThreadSendFibElementChangedViaFibNode();
	
	/**
	 * This method will send that a Fib element changed to the Fib node of
	 * the Fib element.
	 */
	void run();

private:
	/**
	 * A pointer to the changed Fib element.
	 */
	fib::cFibElement * pChangedFibElement;
	
};//end class cThreadSendFibElementChangedViaFibNode

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_THREAD_SEND_FIB_ELEMENT_CHANGED_VIA_FIB_NODE_H__





