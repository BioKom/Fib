
//TODO check

/**
 * @file cFibVariableCreator
 * file name: cFibVariableCreator.h
 * @author Betti Oesterholz
 * @date 19.12.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a variable of a Fib object.
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
 * This file specifies a class for a variable of a Fib object.
 * @pattern Decorator
 *
 * @see fib::cFibVariable
 * @see cFibElement
 */
/*
History:
19.12.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_FIB_VARIABLE_H__
#define ___FIB__NCREATOR__C_FIB_VARIABLE_H__


#include "version.h"

#include <string>

#include <QObject>
#include <QList>
#include <QString>

#include "cFibVariable.h"

#include "cFibScalar.h"
#include "eObjectDeleted.h"
#include "lObjectChanged.h"
#include "templateRegisterChangeListener.h"


namespace fib{

namespace nCreator{

//cyclic dependencies
//TODO change cFibInputVariableHandler to cFibVariableHandler
class cFibVariableHandler;

//for handler, listener and events for changes in cFibVariableCreator
class cFibVariableCreator;
typedef eObjectDeleted< cFibVariableCreator > eFibVariableCreatorChangedEvent;
typedef lObjectChanged< eFibVariableCreatorChangedEvent > lFibVariableCreatorChanged;


class cFibVariableCreator: public iGetWidget,
	public templateRegisterChangeListener<
		lFibVariableCreatorChanged, eFibVariableCreatorChangedEvent >{

friend class cFibVariableHandler;

public:
	
	/**
	 * @return the name of this class "cFibVariableCreator"
	 */
	virtual std::string getName() const;
	
	/**
	 * @see pFibVariable
	 * @see setFibVariable()
	 * @return a pointer to the Fib variable for the variable
	 */
	virtual const fib::cFibVariable * getFibVariable() const;
	
	/**
	 * @see pFibVariable
	 * @see setFibVariable()
	 * @return a pointer to the Fib variable for the variable
	 */
	virtual fib::cFibVariable * getFibVariable();
	
	/**
	 * This methods sets the pointer to the Fib variable of this input
	 * variable to the given Fib variable pointer.
	 *
	 * @see pFibVariable
	 * @see getFibVariable()
	 * @param pInVariable a pointer to the Fib variable to set for this
	 * 	variable
	 */
	virtual void setFibVariable( fib::cFibVariable * pInVariable );
	
	/**
	 * @return the name of the variable
	 * 	@see strVariableName
	 */
	virtual QString getVariableName() const;
	
	/**
	 * This method sets the name of the input to the given name.
	 *
	 * @see strVariableName
	 * @param strName the name of the variable should have
	 */
	virtual void setVariableName( const QString & strName );
	
	/**
	 * This method will create a widget, which displays this object.
	 * ATTENTION: You have to care that the returned widget is deleted.
	 *
	 * @param pParent a pointer the parent of this new Fib scalar widget
	 * @return a pointer to the created widget, or NULL if non could be created
	 */
	virtual QWidget * getWidget( QWidget * pParent = NULL );
	
protected:
	
	
	/**
	 * parameter constructor for a variable
	 *
	 * @param pInVariable a pointer to the Fib variable for the variable
	 * 	@see cFibVariable
	 * @param strInVariableName the name of the variable
	 * 	@see strVariableName
	 */
	cFibVariableCreator( fib::cFibVariable * pInVariable,
		const QString strInVariableName="" );
	
	/**
	 * copy parameter constructor for a variable
	 * It will copy the values of a given variable except the pointer
	 * to the Fib variable itself, which will be given seperatly.
	 * If you copy or clone a Fib object, you can use this constructor to
	 * copy its variables.
	 *
	 * @param fibVariable a reference to the variable, which
	 * 	values to copy (the pointer to the variable won't be copied)
	 * @param pInVariable a pointer to the Fib variable for the variable
	 * 	@see cFibVariable
	 */
	cFibVariableCreator( const cFibVariableCreator & fibVariable,
		fib::cFibVariable * pInVariable );
	
	/**
	 * copy constructor for a variable
	 *
	 * @param fibVariable a reference to the variable, which to copy
	 */
	cFibVariableCreator( const cFibVariableCreator & fibVariable);
	
	/**
	 * destructor
	 */
	virtual ~cFibVariableCreator();
	
	/**
	 * This method clones this object.
	 *
	 * @return a pointer to the clone of this object
	 */
	virtual cFibVariableCreator * clone() const;
	
///members:
	
	/**
	 * A pointer to the Fib Variable which is the variable for the
	 * Fib object.
	 */
	fib::cFibVariable * pFibVariable;
	
	/**
	 * The name of the vector.
	 */
	QString strVariableName;
	

};//end class cFibVariableCreator

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_VARIABLE_H__





