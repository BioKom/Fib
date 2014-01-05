
//TODO check

/**
 * @file cFibVariableCreator
 * file name: cFibVariableCreator.cpp
 * @author Betti Oesterholz
 * @date 19.12.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a variable of a Fib object.
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
 * This file implements a class for a variable of a Fib object.
 * @pattern Decorator
 *
 * @see fib::cFibVariable
 * @see cFibElement
 */
/*
History:
19.12.2013  Oesterholz  created
*/



//TODO switches for test proposes
#define DEBUG


#include "cFibVariableCreator.h"


#include <QLabel>

#include "cDomainIntegerBasis.h"
#include "cDomainRationalBasis.h"



using namespace fib::nCreator;
using namespace fib;


/**
 * parameter constructor for a variable
 *
 * @param pInVariable a pointer to the Fib variable for the variable
 * 	@see cFibVariable
 * @param strInVariableName the name of the variable
 * 	@see strVariableName
 */
cFibVariableCreator::cFibVariableCreator( fib::cFibVariable * pInVariable,
		const QString strInVariableName ):
		pFibVariable( pInVariable ), strVariableName( strInVariableName ){
	
	DEBUG_OUT_L2(<<"cFibVariable("<<this<<")::cFibVariable( pInVariable="<<pInVariable<<", strInVariableName="<<strInVariableName.toStdString()<<") called"<<endl<<flush);
}


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
cFibVariableCreator::cFibVariableCreator( const cFibVariableCreator & fibVariable,
		fib::cFibVariable * pInVariable ):
		pFibVariable( pInVariable ),
		strVariableName( fibVariable.strVariableName ){
	//nothing to do
	DEBUG_OUT_L2(<<"cFibVariable("<<this<<")::cFibVariable( fibVariable, pInVariable="<<pInVariable<<") called"<<endl<<flush);
}


/**
 * copy constructor for a variable
 *
 * @param fibVariable a reference to the variable, which to copy
 */
cFibVariableCreator::cFibVariableCreator( const cFibVariableCreator & fibVariable ):
		pFibVariable( fibVariable.pFibVariable ),
		strVariableName( fibVariable.strVariableName ){
	//nothing to do
	DEBUG_OUT_L2(<<"cFibVariable("<<this<<")::cFibVariable( fibVariable ) called"<<endl<<flush);
}


/**
 * destructor
 */
cFibVariableCreator::~cFibVariableCreator(){
	
	DEBUG_OUT_L2(<<"cFibVariable("<<this<<")::~cFibVariable() called"<<endl<<flush);
}



/**
 * This method clones this object.
 *
 * @return a pointer to the clone of this object
 */
cFibVariableCreator * cFibVariableCreator::clone() const{
	
	return new cFibVariableCreator( *this );
}


/**
 * @return the name of this class "cFibVariable"
 */
std::string cFibVariableCreator::getName() const{
	
	return string( "cFibVariable" );
}


/**
 * @see pFibVariable
 * @see setFibVariable()
 * @return a pointer to the Fib variable for the variable
 */
const fib::cFibVariable * cFibVariableCreator::getFibVariable() const{
	
	return pFibVariable;
}


/**
 * @see pFibVariable
 * @see setFibVariable()
 * @return a pointer to the Fib variable for the variable
 */
fib::cFibVariable * cFibVariableCreator::getFibVariable(){
	
	return pFibVariable;
}


/**
 * This methods sets the pointer to the Fib variable of this input
 * variable to the given Fib variable pointer.
 *
 * @see pFibVariable
 * @see getFibVariable()
 * @param pInVariable a pointer to the Fib variable to set for this
 * 	variable
 */
void cFibVariableCreator::setFibVariable( fib::cFibVariable * pInVariable ){
	
	if ( pFibVariable == pInVariable ){
		//nothing changed
		return;
	}
	pFibVariable = pInVariable;
	
	//send variable change event
	/*TODO
	const eFibScalarChangedEvent fibScalarChangedEvent(
		this );
	sendScalarChange( &fibScalarChangedEvent );
	*/
}


/**
 * @return the name of the variable
 * 	@see strVariableName
 */
QString cFibVariableCreator::getVariableName() const{
	
	return strVariableName;
}


/**
 * This method sets the name of the input to the given name.
 *
 * @see strVariableName
 * @param strName the name of the variable should have
 */
void cFibVariableCreator::setVariableName( const QString & strName ){
	
	strVariableName = strName;
	//send variable change event
	/*TODO
	const eFibScalarChangedEvent fibScalarChangedEvent(
		this );
	sendScalarChange( &fibScalarChangedEvent );
	*/
}


/**
 * This method will create a widget, which displays this object.
 * ATTENTION: You have to care that the returned widget is deleted.
 *
 * @param pParent a pointer the parent of this new Fib scalar widget
 * @return a pointer to the created widget, or NULL if non could be created
 */
QWidget * cFibVariableCreator::getWidget( QWidget * pParent ){
	//return label with variable name
	return new QLabel( getVariableName(), pParent );
}




