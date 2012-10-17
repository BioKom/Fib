/**
 * @class cFunctionVariable
 * file name: cFunctionVariable.h
 * @author Betti Oesterholz
 * @date 25.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a variable underfunction.
 * Copyright (C) @c LGPL3 2010 Betti Oesterholz
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
 * This class represents a variable underfunction.
 * Variable underfunction store a fixted /constant variable.
 *
 */
/*
History:
25.04.2010  Oesterholz  created
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
*/

#ifndef ___C_FUNCTION_VARIABLE_H__
#define ___C_FUNCTION_VARIABLE_H__


#include "version.h"
#include "fibDatatyps.h"
#include "cFibVariable.h"
#include "cReadBits.h"

#include "cUnderFunction.h"


using std::set;

namespace fib{


class cFunctionVariable: public cUnderFunction, iVariableUser{

protected:
	
	/**
	 * The variable of this underfunction.
	 */
	cFibVariable * pVariable;

public:


	/**
	 * The constructor of the underfunction.
	 *
	 * @param pInVariable a pointer to the variable of this underfunction
	 * @param pInSuperiorFunction the underfunction which contains the
	 * 	new underfunction
	 * @param pInDefiningFibElement the fib -element which defines/ uses
	 * 	the new underfunction
	 */
	cFunctionVariable( cFibVariable * pInVariable, cUnderFunction * pInSuperiorFunction = NULL,
		cFibElement * pInDefiningFibElement = NULL );

	/**
	 * The copy constructor of the underfunction.
	 *
	 * @param underfunction the underfunction which to copy
	 * @param pInSuperiorFunction the underfunction which contains the
	 * 	new underfunction
	 * @param pInDefiningFibElement the fib -element which defines/ uses
	 * 	the new underfunction
	 */
	cFunctionVariable( const cFunctionVariable & underfunction,
		cUnderFunction * pInSuperiorFunction = NULL,
		cFibElement *pInDefiningFibElement = NULL );

	/**
	 * The constructor for restoring a variable underfunction from an TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node the underfunction is stored in
	 * @param outStatus An reference to an integervariable where the errorvariable
	 * 	can be stored to.
	 * 	possible errorvariables are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 * @param liDefinedVariables a list with the defined variables for the
	 * 	to restore fib -element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 * @param pInSuperiorFunction the underfunction which contains the
	 * 	new underfunction
	 * @param pInDefiningFibElement the fib -element which defines/ uses
	 * 	the new underfunction
	 */
	cFunctionVariable( const TiXmlElement * pXmlElement, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		cUnderFunction * pInSuperiorFunction = NULL,
		cFibElement * pInDefiningFibElement = NULL );

	/**
	 * This constructor restores a variable underfunction from the stream
	 * where it is stored in the compressed fib -format.
	 * Beware: The bits for the functiontype should be allready readed, this
	 * 	constructor reads yust the two underfunctions.
	 *
	 * @param iBitStream the stream where this underfunction is stored to in,
	 * 	because this stream is an cReadBits, any number of bits can be
	 * 	readed from it
	 * @param outStatus An reference to an integervariable where the errorvariable
	 * 	can be stored to. If the pointer is NULL no errorvariable will be
	 * 	given back.
	 * 	possible errorvariables are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid stream
	 * 		- -2 loading error, invalid data in stream
	 * 		- 1 loading warning, invalid data in stream, error could be corrected
	 * 		- 2 loading warning, invalid data in stream, maybe the loaded
	 * 			object is wrong
	 * @param liDefinedVariables a list with the defined variables for the
	 * 	to restore fib -element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 * @param pInVariableDomain the domain for variable underfunctions
	 * @param pInSuperiorFunction the underfunction which contains the
	 * 	new underfunction
	 * @param pInDefiningFibElement the fib -element which defines/ uses
	 * 	the new underfunction
	 */
	cFunctionVariable( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomainSingle * pInVariableDomain,
		cUnderFunction * pInSuperiorFunction = NULL,
		cFibElement * pInDefiningFibElement = NULL );


	/**
	 * The destructor of the underfunction.
	 */
	virtual ~cFunctionVariable();

	/**
	 * This method returns if this underfunction is valid, else false.
	 * All variables in the underfunction and it's underfunctions must be
	 * inside the underfunction domain. All variables must be defined over
	 * this underfunction.
	 * No underfunction should contain itselfor should be contained in one
	 * of its underfunctions (no cycles allowed).
	 *
	 * @return true if this underfunction is valid, else false
	 */
	virtual bool isValid() const;

	/**
	 * This method checks if the given variable is used in this underfunction.
	 *
	 * @see cFibVariable
	 * @param variable the variable to check if it is used
	 * @return true if the variable is used, else false
	 */
	virtual bool isUsedVariable( const cFibVariable * variable ) const;
	
	/**
	 * This method returns all variables used in this underfunction.
	 *
	 * @see cFibVariable
	 * @return all variables used in this underfunction
	 */
	virtual set<cFibVariable*> getUsedVariables();

	/**
	 * This method replace the variable variableOld with the variable
	 * variableNew in the underfunction.
	 *
	 * @see cFibVariable
	 * @see isVariable()
	 * @see isUsedVariable()
	 * @param variableOld the variable to replace
	 * @param variableNew the variable with which the variable variableOld
	 * 	is to replace
	 * @return true if the variable variableOld is replaced with variableNew,
	 * 	else false
	 */
	virtual bool replaceVariable( cFibVariable *variableOld,
		cFibVariable *variableNew );

	/**
	 * Returns the variable of the underfunction or 0 if non such exists.
	 *
	 * @return a pointer to the variable of the underfunction or NULL, if
	 * 	non such exists
	 */
	virtual cFibVariable * getVariable();

	/**
	 * This method Sets the variable of the underfunction.
	 *
	 * @param pInVariable a pointer to the variable for the underfunction
	 * @return true if the variable was set to pInVariable else false
	 */
	virtual bool setVariable( cFibVariable * pInVariable );

	/**
	 * Returns the value of the underfunction or 0 if non such exists.
	 *
	 * @return the value of the underfunction or 0 if non
	 * 	such exists
	 */
	virtual doubleFib getValue() const;

	/**
	 * @return the number of underfunctions, a underfunction of this type has
	 */
	virtual unsignedIntFib getNumberOfUnderFunctions() const;
	
	/**
	 * This method evaluades a variable for the time needed to evariable the
	 * underfunction.
	 * This variable should not exceed lMaxTime, if the variable for the time
	 * is greater than lMaxTime the evaluation will be stopt and lMaxTime
	 * returned. If lMaxTime is 0 (for infinity) the evaluation won't be
	 * stoped, this is the standard case.
	 *
	 * @see cFibElement::evariableObject()
	 * @param lMaxTime the maximum time for the evaluation, the returned
	 * 	exceed this variable; the variable 0 stands for infinity, so the
	 * 	evaluation won't be stoped
	 * @return a variable for the time needed to evariable this underfunction
	 */
	virtual unsignedLongFib getTimeNeed( unsignedLongFib lMaxTime=0 ) const;
	
	/**
	 * This method evaluades the size of the Fib -object in bits in the
	 * compressed file form.
	 * The optionalpart field of point -elements will be ignored.
	 *
	 * @see store()
	 * @return the size of the Fib -object in bits in the compressed form
	 */
	virtual unsignedLongFib getCompressedSize() const;

	/**
	 * This method stores this Fib -object in the compressed Fib -format
	 * into the given stream.
	 * It is needed becouse the stream can yust store byts but the size of
	 * fib -elements can be any number of bits. Because of that ther have to
	 * be a possibility to exchange the missing bits betwean the fib -elements.
	 *
	 * @see store
	 * @param stream the stream where this Fib -object should be stored to
	 * @param cRestBits the not yet writen bits which should be stored
	 * @param uiRestBitPosition the number of bits in the cRestBits which
	 * 	should be writen respectively containing valid information
	 * @return true if this Fib -object is stored, else false
	 */
	virtual bool store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const;

	/**
	 * This method stores this underfunction in the XML -format into the
	 * given stream.
	 * Variables should have ther number as ther variable.
	 *
	 * @param stream the stream where this underfunctionshould be
	 * 	stored to
	 * @return true if this underfunction is stored, else false
	 */
	virtual bool storeXml( ostream &stream ) const;

	/**
	 * @return the type for the underfunction
	 */
	virtual unsignedIntFib getType() const;
	
	/**
	 * @return the name for the underfunction
	 */
	virtual string getUnderFunctionName() const;

#ifndef FEATURE_EQUAL_FIB_OBJECT
	/**
	 * This Method checks if the given underfunction is equal to this underfunction.
	 *
	 * @param underfunction the underfunction to compare with this underfunction
	 * @return true if the given underfunction is equal to this underfunction, else false
	 */
	virtual bool equal( const cUnderFunction & underfunction ) const;
#endif //FEATURE_EQUAL_FIB_OBJECT

	/**
	 * This method duplicates this whole underfunction.
	 * Underfunctions of this underfunction are also cloned.
	 *
	 * @param pSuperiorUnderFunction the underfunction which contains
	 * @param pInDefiningFibElement the Fib -element which defines/ uses
	 * @return the cloned/ duplicated underfunction
	 */
	virtual cUnderFunction * clone(
		cUnderFunction * pInSuperiorUnderFunction = NULL,
		cFibElement *pInDefiningFibElement = NULL) const;


protected:

	/**
	 * @return the fib -element which uses the variables of this element
	 */
	virtual cFibElement * getVariableUsingFibElement() const;
	
	/**
	 * This method deletes all occurenc of the given variable from this
	 * element. So the variable is not used anymore of this element.
	 * Beware: This element has to be unregisterd (call
	 * unregisterUsingElement() ) at the pVariable seperatly. Do this directly
	 * befor or after calling this method.
	 *
	 * @param pInVariable the variable which is to delete from this element
	 * @return true if the variable dosn't occure anymore in this element,
	 * 	else false
	 */
	virtual bool deleteVariable( cFibVariable * pInVariable );
	
#ifdef FEATURE_EQUAL_FIB_OBJECT
	/**
	 * This method checks if the given underfunction is equal to this underfunction.
	 * Variables can be others, but must be defined and used in equivalent
	 * Fib-elements.
	 *
	 * @param underfunction the underfunction to compare with this underfunction
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
	 * @return true if this Fib-object is equal to the given Fib-object,
	 * 	else false
	 */
	virtual bool equalInternal( const cUnderFunction & underfunction,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const;

#endif //FEATURE_EQUAL_FIB_OBJECT

};//end class cFunctionVariable


}//end namespace fib

#endif
