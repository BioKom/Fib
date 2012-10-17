/**
 * @class cFibVariable
 * file name: cFibVariable.h
 * @author Betti Oesterholz
 * @date 02.05.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a Fib -variable.
 * Copyright (C) @c LGPL3 2009 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This file contains the class for Fib -variables. Just Fib -elements
 * can create Fib -variables. A variable contains a value or is undefined.
 */
/*
History:
17.04.2009  Oesterholz  created
17.04.2009  Oesterholz  cExtObjects as friend class added
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
03.01.2012  Oesterholz  cVectorFibSet and cVectorFibMatrix as friends added
29.01.2012  Oesterholz  cVectorExtObject and cVectorExtSubobject as friends added
*/

#ifndef ___C_FIB_VARIABLE_H__
#define ___C_FIB_VARIABLE_H__

#include "version.h"
#include "fibDatatyps.h"
#include "iVariableUser.h"

#include <set>
#include <map>

using std::set;
using std::map;


namespace fib{

class cFibElement;//cyclic dependencie
class cRoot;//cyclic dependencie
class cArea;//cyclic dependencie
class cFunction;//cyclic dependencie
class cFibVector;//cyclic dependencie
class cFunctionVariable;//cyclic dependencie

class cFibVariable{

//TODO friend class cFunction

friend class cRoot;
friend class cArea;
friend class cFunction;
friend class cExtObject;
friend class cExtSubobject;
friend class cFibVector;
friend class cVectorFibSet;
friend class cVectorFibMatrix;
friend class cVectorExtObject;
friend class cVectorExtSubobject;
friend class cFunctionVariable;


#ifndef TEST
protected:
#else
public: //make the following constructor and methods public for the test
#endif
	/**
	 * the type fore the type of the variable
	 */
	enum eVariableType{
		UNDEFINED,
		REAL_VALUE,
		INTEGER_VALUE
	};
	/**
	 * the type of the variable
	 */
	eVariableType variableType;

	/**
	 * the value if the variable is of type real
	 */
	doubleFib doubleValue;

	/**
	 * the value if the variable is of type integer
	 */
	longFib integerValue;

	/**
	 * the refernce to the Fib -element that defines the variable
	 */
	cFibElement * pDefiningFibElement;

	/**
	 * the set with the refernces to the Fib -elements that uses the
	 * variable
	 */
	set<iVariableUser*> setUsingElements;



public:

	/**
	 * The constructor of the variable.
	 *
	 * @param definingFibElement the Fib -element that defines the variable
	 */
	cFibVariable( cFibElement *definingFibElement );

	/**
	 * The copyconstructor of the variable.
	 *
	 * @param variable the Fib -element that should be copied
	 * @param definingFibElement the Fib -element that defines the variable
	 */
	cFibVariable( const cFibVariable & variable,
		cFibElement *definingFibElement = NULL );

	/**
	 * The destructor of the variable.
	 */
	virtual ~cFibVariable();


	/**
	 * This method returns the value of the variable as an real value.
	 * It returns 0 if the variable is undefined.
	 *
	 * @return the value of the variable or 0 if the variable is undefined
	 */
	doubleFib getValue() const;

	/**
	 * This method returns the value of the variable as an integer value.
	 * It returns 0 if the variable is undefined. If the value of the
	 * variable is an real value, the value is rounded to an integervalue.
	 *
	 * @return the value of the variable or 0 if the variable is undefined
	 */
	longFib getIntegerValue() const;

	/**
	 * This method sets the value of the variable as an real value.
	 *
	 * @param dValue the value of the variable to set
	 */
	void setValue( const doubleFib dValue );

	/**
	 * This method sets the value of the variable as an integer value.
	 *
	 * @param lValue the value of the variable to set
	 */
	void setIntegerValue( const longFib lValue );

	/**
	 * This method returns a pointer to the Fib -element that defines the
	 * variable.
	 *
	 * @return a pointer to  the Fib -element that defines the variable
	 */
	cFibElement *getDefiningElement() const;

	/**
	 * This method returns the number of Fib -elements that uses the
	 * variable. These have to be registered befor.
	 *
	 * @return the number of Fib -elements that uses the variable
	 */
	unsignedIntFib getNumberOfUsingElements() const;

	/**
	 * This method returns a set of Fib -elements that uses the variable.
	 * These have to be registered befor.
	 *
	 * @return a set Fib -elements that uses the variable
	 */
	set<cFibElement*> getUsingElements() const;

	/**
	 * @return if the value of the variable was set true is returned, else false
	 */
	bool isSet() const;

	/**
	 * @return if the value is an integer value true, else false
	 */
	bool isIntegerValue() const;


#ifdef FEATURE_EQUAL_FIB_OBJECT
	
	/**
	 * This Method checks if the given variable is equal to this variable.
	 *
	 * @param variable the variable to compare with this variable
	 * @param bCheckExternalObjects if true the external objects of
	 * 	cExtObject will be compared
	 * @return true if the given variable is equal to this variable, else false
	 */
	virtual bool equal( const cFibVariable &variable,
		const bool bCheckExternalObjects=true ) const;

#else //FEATURE_EQUAL_FIB_OBJECT
	
	/**
	 * This Method checks if the given variable is equal to this variable.
	 *
	 * @param variable the variable to compare with this variable
	 * @return true if the given variable is equal to this variable, else false
	 */
	virtual bool equal( const cFibVariable &variable ) const;

#endif//FEATURE_EQUAL_FIB_OBJECT

	/**
	 * This Method checks if the given variable is equal to this variable.
	 *
	 * @param variable the variable to compare with this variable
	 * @return true if the given variable is equal to this variable, else false
	 */
	virtual bool operator==( const cFibVariable &variable ) const;

	/**
	 * This Method makes this variable equal to the given variable.
	 *
	 * @param variable the variable to copy
	 */
	virtual cFibVariable & operator=( const cFibVariable &variable );


#ifndef TEST
protected:
#else
public: //make the following constructor and methods public for the test
#endif
	/**
	 * This method registers an element that uses the variable.
	 *
	 * @param usingElement the element that uses the variable
	 */
	void registerUsingElement( iVariableUser * usingElement );

	/**
	 * This method unregisters an element that don't uses the variable
	 * anymore.
	 *
	 * @param usingElement the element that don't uses the variable
	 * 	anymore
	 */
	void unregisterUsingElement( iVariableUser * usingElement );


#ifdef FEATURE_EQUAL_FIB_OBJECT
	
	/**
	 * This Method checks if the given variable is equal to this variable.
	 *
	 * @param variable the variable to compare with this variable
	 * @param mapEqualRootObjects the root objects of this object that wher
	 * 	already checked as equal
	 * 	map entries:
	 * 		key: the root-element of this Fib object that was checked
	 * 		value: the to the key correspondending root-element of the
	 * 			fibObject that was checked and which is equal to the key
	 * 		root-element
	 * 	(it is empty if bCheckExternalObjects == false)
	 * @param mapEqualDefinedVariables the Fib elements that defines
	 * 	variables and are equal;
	 * 	map entries:
	 * 		key: the Fib element of this Fib object that was checked
	 * 		value: the to the key correspondending Fib element of the
	 * 			fibObject that was checked and which sets its defined
	 * 			variables to the same values as the key Fib element
	 * @param bCheckExternalObjects if true the external objects of
	 * 	cExtObject will be compared
	 * @return true if the given variable is equal to this variable, else false
	 */
	virtual bool equalInternal( const cFibVariable &variable,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const;

#endif //FEATURE_EQUAL_FIB_OBJECT

};//end class cFibVariable


}//end namespace fib

#endif

