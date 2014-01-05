
//TODO check

/**
 * @file cFibVectorHandler
 * file name: cFibVectorHandler.h
 * @author Betti Oesterholz
 * @date 28.11.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for handling Fib vectors for the
 * Fib creator application.
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
 * This file specifies a class for handling Fib vectors for the
 * Fib creator application.
 *
 * @pattern singelton
 * @see cFibVectorCreator
 * @see fib::cFibVector
 */
/*
History:
28.11.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_FIB_VECTOR_HANDLER_H__
#define ___FIB__NCREATOR__C_FIB_VECTOR_HANDLER_H__

#include "version.h"

#include <map>
#include <set>
#include <string>

#include <QObject>
#include <QMutex>

#include "lFibNodeChanged.h"
#include "lFibVectorChanged.h"


namespace fib{

//forward declarations
class cFibVector;

namespace nCreator{

//forward declarations
class cFibNode;
class cFibVectorCreator;


class cFibVectorHandler: public lFibNodeChanged{

friend class cFibVectorCreator;

public:
	
	/**
	 * The destructor of this class.
	 */
	virtual ~cFibVectorHandler();
	
	/**
	 * @return a instance of the Fib vector handler
	 */
	static cFibVectorHandler * getInstance();
	
	/**
	 * @return the name of this class "cFibVectorHandler"
	 */
	std::string getName() const;
	
	/**
	 * This method returns the Fib creator vector for the given Fib vector.
	 * If no Fib creator vector exists till now one is created.
	 * Beware: Input scalars which defining Fib element is deleted will
	 * 	be also deleted.
	 *
	 * @see mapFibVectors
	 * @param pFibVector the Fib vector for the Fib creator vector to return
	 * @param pListenerVectorChanged a listener for the changes in
	 * 	the vector or NULL
	 * @return the Fib creator vector for the given Fib vector, or NULL if
	 * 	non could be evalued
	 */
	cFibVectorCreator * getFibVectorForFibVector(
		fib::cFibVector * pFibVector,
		lFibVectorChanged * pListenerVectorChanged = NULL );
	
	/**
	 * This method checks if the given pointer points to an in this handler
	 * existing Fib creator vector.
	 *
	 * @param pFibVector a pointer to the Fib creator vector to check
	 * @return true if the given Fib creator vector points to an existing
	 * 	Fib creator vector in this handler, else false
	 */
	bool isValidVector( cFibVectorCreator * pFibVector );
	
	
	/**
	 * Event method
	 * It will be called every time a Fib node (cFibNode), at which
	 * this object is registered, was changed.
	 *
	 * @param pFibNodeChanged a pointer to the event, with the information
	 * 	about the changed Fib node
	 */
	virtual void fibNodeChangedEvent(
		const eFibNodeChangedEvent * pFibNodeChanged );
	

protected:
	
	/**
	 * The constructor for the Fib vector handler.
	 */
	cFibVectorHandler();
	
	/**
	 * This method removes the given vector from this handler.
	 * cFibVectorCreator should call this method on destruction.
	 * After the call to this method no pointer to the Fib vector pFibVector
	 * will exists in this handler.
	 *
	 * @see cFibVectorCreator::~cFibVectorCreator()
	 * @param pFibVector a pointer to the vector to remove
	 * @return true if the vector was removed, else false (the vector didn't
	 * 	exists in this handler)
	 */
	bool removeVector( cFibVectorCreator * pFibVector );
	
//members
	
	/**
	 * A pointer to the vector handler object.
	 */
	static cFibVectorHandler * pFibVectorHandler;
	
	/**
	 * A set with the existing Fib creator vectors.
	 */
	std::set< cFibVectorCreator * > setFibVectors;
	
	/**
	 * The map for the existing Fib creator vectors.
	 * 	key: the Fib vector for the value Fib creator vector
	 * 	value: the Fib creator vector for the key Fib vector
	 */
	std::map< fib::cFibVector * , cFibVectorCreator * > mapFibVectors;
	
	/**
	 * The map for the existing Fib nodes.
	 * 	key: the Fib object node for the value Fib creator vectors,
	 * 		the Fib object of the Fib node contains the defining Fib
	 * 		element of the Fib vectors, also the Fib object is a master
	 * 		root (highest) Fib object
	 * 	value: a list with the Fib creator vectors for the Fib object node
	 */
	std::map< cFibNode * , std::set< cFibVectorCreator * > > mapVectorsForNodes;
	
	/**
	 * A map with counters for scalars, so they can get a unique name.
	 * 	key: the type character for the Fib element type ('u' is for unknown)
	 * 		@see cFibElement::getType()
	 * 	value: the next free number for a scalar name
	 */
	std::map< char, unsigned int > mapVectorCounters;
	
	
	/**
	 * Mutex to lock access to the Fib object and Fib vector data of this class.
	 * Lock the mutex if you use one of the following containers:
	 * @see setFibVectors
	 * @see mapFibVectors
	 * @see mapVectorsForNodes
	 * @see mapVectorCounters
	 */
	QMutex mutexFibVectorHandler;
	
	
};//end class cFibVectorHandler

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_VECTOR_HANDLER_H__





