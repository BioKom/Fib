
//TODO check

/**
 * @file cFibInputVariable
 * file name: cFibInputVariable.h
 * @author Betti Oesterholz
 * @date 16.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a input variable of a Fib object.
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
 * This file specifies a class for a input variable of a Fib object.
 * In some Fib objects not all used variables are defined in it.
 * Every Fib variable, which is used in a Fib object, but not defined in it
 * is a input variable for the Fib object. The input variables need to be
 * given  and set for a Fib object.
 * @pattern Decorator
 *
 *
 * @see cFibInputVariables
 * @see fib::cFibVariable
 * @see cFibElement
 */
/*
History:
16.08.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_FIB_INPUT_VARIABLE_H__
#define ___FIB__NCREATOR__C_FIB_INPUT_VARIABLE_H__


#include "version.h"

#include <string>

#include <QObject>
#include <QList>
#include <QString>

#include "cFibScalar.h"
#include "cFibVariable.h"
#include "cFibVariableCreator.h"


namespace fib{

namespace nCreator{

//cyclic dependencies
class cFibInputVariableHandler;

class cFibInputVariable: public cFibVariableCreator,
	public virtual cFibScalar {
	
friend class cFibVariableHandler;

public:
	
	/**
	 * @return the name of this class "cFibInputVariable"
	 */
	virtual std::string getName() const;
	
	/**
	 * This method assigns the value of the input variable to the Fib
	 * variable. ( pFibVariable->setValue( dValue ) )
	 * Call this function before evaluing the Fib object for the input variable.
	 *
	 * @see fib::cFibVariable::setValue()
	 * @see getValue()
	 * @see setValue()
	 * @return true if the value could be assigned, else false
	 */
	bool assignValue();
	
	/**
	 * @return the name of the input variable
	 * 	@see strVariableName
	 */
	virtual QString getVariableName() const;
	
	/**
	 * This method sets the name of the input to the given name.
	 *
	 * @see strVariableName
	 * @param strName the name of the input variable should have
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
	 * parameter constructor for a input variable
	 *
	 * @param pInInputVariable a pointer to the Fib variable for the input variable
	 * 	@see fib::cFibVariable
	 * @param dInValue the value for the input variable
	 * 	@see assignValue()
	 * @param strInVariableName the name of the input variable
	 * 	@see strVariableName
	 * @param pInVariableDomain a pointer to the domain for the input variable
	 * 	Beware: This object will delete the given object on destruction.
	 */
	cFibInputVariable( fib::cFibVariable * pInInputVariable,
		const doubleFib dInValue = 0, const QString strInVariableName="",
		cDomainSingle * pInVariableDomain = NULL );
	
	/**
	 * copy parameter constructor for a input variable
	 * It will copy the values of a given input variable except the pointer
	 * to the Fib input variable itself, which will be given seperatly.
	 * If you copy or clone a Fib object, you can use this constructor to
	 * copy its input variables.
	 *
	 * @param fibInputVariable a reference to the input variable, which
	 * 	values to copy (the pointer to the input variable won't be copied)
	 * @param pInInputVariable a pointer to the Fib variable for the input variable
	 * 	@see fib::cFibVariable
	 */
	cFibInputVariable( const cFibInputVariable & fibInputVariable,
		fib::cFibVariable * pInInputVariable );
	
	/**
	 * copy constructor for a input variable
	 *
	 * @param fibInputVariable a reference to the input variable, which to copy
	 */
	cFibInputVariable( const cFibInputVariable & fibInputVariable);
	
	/**
	 * destructor
	 */
	virtual ~cFibInputVariable();
	
	/**
	 * This method clones this object.
	 *
	 * @return a pointer to the clone of this object
	 */
	virtual cFibInputVariable * clone() const;
	
};//end class cFibInputVariable

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_INPUT_VARIABLE_H__





