
//TODO check

/**
 * @file cFibInputVariableHandler
 * file name: cFibInputVariableHandler.h
 * @author Betti Oesterholz
 * @date 24.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for handling Fib input variables for the
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
 * This file specifies a class for handling Fib input variables for the
 * Fib creator application.
 * If you have a Fib object, the input variables of it are root object
 * input variables or variables used in the Fib object but not defined in it.
 * With this class you can handle these.
 *
 * @pattern singelton
 * @see cFibInputVariable
 * @see cFibInputVariables
 */
/*
History:
24.08.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_FIB_INPUT_VARIABLE_HANDLER_H__
#define ___FIB__NCREATOR__C_FIB_INPUT_VARIABLE_HANDLER_H__

#include "version.h"

#include "cFibInputVariable.h"
#include "cFibNode.h"

#include <map>
#include <set>
#include <string>

#include <QObject>
#include <QMutex>

#include "cFibVariable.h"



using namespace std;


namespace fib{

namespace nCreator{


class cFibInputVariableHandler: public lFibNodeChanged,
		public lInputVariableChanged{

protected:
	
	/**
	 * A pointer to the input variable handler object.
	 */
	static cFibInputVariableHandler * pFibInputVariableHandler;
	
	/**
	 * A set with the existing Fib input variables.
	 */
	set< cFibInputVariable * > setFibInputVariables;
	
	/**
	 * The map for the existing Fib input variables.
	 * 	key: the Fib variable for the value Fib input variable
	 * 	value: the Fib input variables for the key Fib objects
	 */
	map< cFibVariable * , cFibInputVariable * > mapFibInputVariables;
	
	/**
	 * The map for the existing Fib nodes.
	 * 	key: the Fib object node for the value Fib input variables,
	 * 		the Fib object of the Fib node contains the defining Fib
	 * 		element of the Fib variable of the Fib input variable,
	 * 		also the Fib object is a master root (highest) Fib object
	 * 	value: a list with the Fib input variables for the Fib object node
	 */
	map< cFibNode * , set< cFibInputVariable * > > mapInputVariablesForNodes;
	
	/**
	 * A map with counters for variables, so they can get a unique name.
	 * 	key: the type character for the Fib element type ('u' is for unknown)
	 * 		@see cFibElement::getType()
	 * 	value: the next free number for a variable name
	 */
	map< char, unsigned int > mapVariableCounters;
	
	
	/**
	 * Mutex to lock access to the Fib object and Fib input variable data of this class.
	 * Lock the mutex if you use one of the following containers:
	 * @see setFibInputVariables
	 * @see mapFibInputVariables
	 * @see mapInputVariablesForNodes
	 */
	QMutex mutexFibInputVariableHandler;
	
	
	/**
	 * constructor for the Fib input variable handler
	 */
	cFibInputVariableHandler();
	
public:
	
	/**
	 * destructor
	 */
	virtual ~cFibInputVariableHandler();
	
	/**
	 * @return a instance of the Fib input variable handler
	 */
	static cFibInputVariableHandler * getInstance();
	
	/**
	 * @return the name of this class "cFibInputVariableHandler"
	 */
	std::string getName() const;
	
	/**
	 * This method returns the Fib input variable for the given Fib variable.
	 * If no Fib input variable exists till now one is created.
	 * Beware: Input variables which defining Fib element is deleted will
	 * 	be also deleted.
	 *
	 * @see mapFibInputVariables
	 * @param pFibVariable the Fib variable for the Fib input variable to return
	 * @param pListenerInputVariableChanged a listener for the changes in
	 * 	the input variable or NULL
	 * @return the Fib input variable for the given Fib variable, or NULL if
	 * 	non could be evalued
	 */
	cFibInputVariable * getFibInputVariableForFibVariable(
		cFibVariable * pFibVariable,
		lInputVariableChanged * pListenerInputVariableChanged = NULL );
	
	/**
	 * This method checks if the given pointer points to a in this handler
	 * existing Fib input variable.
	 *
	 * @param pFibInputVariable a pointer to the Fib input variable to check
	 * @return true if the given Fib input variable points to an existing
	 * 	Fib input variable in this handler, else false
	 */
	bool isValidInputVariable( cFibInputVariable * pFibInputVariable );
	
	
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
	 * It will be called every time a input variable value (cFibInputVariable),
	 * at which this object is registered,was changed.
	 *
	 * @see cFibInputVariable::dValue
	 * @param pFibInputVariable a pointer to the changed Fib input variable
	 */
	virtual void fibInputVariableChangedEvent(
		const eFibInputVariableChangedEvent * pFibInputVariableEvent );

};//end class cFibInputVariableHandler

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_INPUT_VARIABLE_HANDLER_H__





