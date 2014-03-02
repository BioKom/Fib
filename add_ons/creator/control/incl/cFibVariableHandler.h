
//TODO check

/**
 * @file cFibVariableHandler
 * file name: cFibVariableHandler.h
 * @author Betti Oesterholz
 * @date 24.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for handling Fib variables for the
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
 * This file specifies a class for handling Fib variables for the
 * Fib creator application.
 *
 * @pattern singelton
 * @see cFibVariableCreator
 */
/*
History:
24.08.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_FIB_VARIABLE_HANDLER_H__
#define ___FIB__NCREATOR__C_FIB_VARIABLE_HANDLER_H__

#include "version.h"

#include <map>
#include <set>
#include <string>

#include <QObject>
#include <QMutex>

#include "cFibVariable.h"

#include "lFibNodeChanged.h"
#include "cFibVariableCreator.h"



namespace fib{

namespace nCreator{

//forward declarations
class cFibNode;


class cFibVariableHandler: public lFibNodeChanged,
		public lFibVariableCreatorChanged{
public:
	
	/**
	 * destructor
	 */
	virtual ~cFibVariableHandler();
	
	/**
	 * @return a instance of the Fib input variable handler
	 */
	static cFibVariableHandler * getInstance();
	
	/**
	 * @return the name of this class "cFibVariableHandler"
	 */
	std::string getName() const;
	
	/**
	 * This method returns the Fib input variable for the given Fib variable.
	 * If no Fib input variable exists till now one is created.
	 * Beware: Input variables which defining Fib element is deleted will
	 * 	be also deleted.
	 *
	 * @see mapFibVariables
	 * @param pFibVariable the Fib variable for the Fib input variable to return
	 * @param pListenerVariableChanged a listener for the changes in
	 * 	the input variable or NULL
	 * @return the Fib input variable for the given Fib variable, or NULL if
	 * 	non could be evalued
	 */
	cFibVariableCreator * getFibVariableCreatorForFibVariable(
		fib::cFibVariable * pFibVariable,
		lFibVariableCreatorChanged * pListenerVariableChanged = NULL );
	
	/**
	 * This method checks if the given pointer points to an in this handler
	 * existing Fib input variable.
	 *
	 * @param pFibInputVariable a pointer to the Fib input variable to check
	 * @return true if the given Fib input variable points to an existing
	 * 	Fib input variable in this handler, else false
	 */
	bool isValidInputVariable( cFibVariableCreator * pFibInputVariable );
	
	
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
	
	/**
	 * Event method
	 * It will be called every time a scalar value (cFibScalar),
	 * at which this object is registered, was changed.
	 *
	 * @see cFibScalar
	 * @param pFibVariableChangedEvent a pointer to the Fib scalar change event
	 */
	virtual void changedEvent(
		const eFibVariableCreatorChangedEvent * pFibVariableChangedEvent );


protected:
	
	/**
	 * constructor for the Fib input variable handler
	 */
	cFibVariableHandler();
	
	/**
	 * This method will remove the given variable from this handler.
	 * Note: Tis method won't use any mutex.
	 *
	 * @see setFibVariables
	 * @see mapFibVariables
	 * @see mapVariablesForNodes
	 * @see mapDefiningFibElements
	 * @see mutexFibVariableHandler
	 * @param pVariable a pointer to the variable to delete from this handler
	 */
	void removeVariableFromHandler( cFibVariableCreator * pVariable );
	
//members
	
	/**
	 * A pointer to the input variable handler object.
	 */
	static cFibVariableHandler * pFibVariableHandler;
	
	/**
	 * A set with the existing Fib variables.
	 */
	std::set< cFibVariableCreator * > setFibVariables;
	
	/**
	 * The map for the existing Fib variables.
	 * 	key: the Fib variable for the value Fib input variable
	 * 	value: the Fib variables for the key Fib variable
	 */
	std::map< fib::cFibVariable * , cFibVariableCreator * > mapFibVariables;
	
	/**
	 * The map for the existing Fib nodes.
	 * 	key: the Fib object node for the value Fib variables,
	 * 		the Fib object of the Fib node contains the defining Fib
	 * 		element of the Fib variable of the Fib input variable,
	 * 		also the Fib object is a master root (highest) Fib object
	 * 	value: a list with the Fib variables for the Fib object node
	 */
	std::map< cFibNode * , std::set< cFibVariableCreator * > > mapVariablesForNodes;
	
	/**
	 * The map for the defining Fib elements of the Fib variables.
	 * 	key: the Fib variable which the value Fib element defines
	 * 	value: the Fib element which defines the key Fib variable
	 */
	std::map< cFibVariableCreator * , cFibElement * > mapDefiningFibElements;
	
	/**
	 * A map with counters for variables, so they can get a unique name.
	 * 	key: the type character for the Fib element type ('u' is for unknown)
	 * 		@see cFibElement::getType()
	 * 	value: the next free number for a variable name
	 */
	std::map< char, unsigned int > mapVariableCounters;
	
	
	/**
	 * Mutex to lock access to the Fib object and Fib input variable data of this class.
	 * Lock the mutex if you use one of the following containers:
	 * @see setFibVariables
	 * @see mapFibVariables
	 * @see mapVariablesForNodes
	 * @see mapVariableCounters
	 */
	QMutex mutexFibVariableHandler;
	
	
};//end class cFibVariableHandler

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_VARIABLE_HANDLER_H__





