/**
 * @class cFunctionIf
 * file name: cFunctionIf.h
 * @author Betti Oesterholz
 * @date 03.06.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a Fib if-function.
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
 * This class represents a Fib if-function.
 * It gives back the value of the first underfunction if the condition is
 * true, else the value of the second underfunction.
 * ( if( condition, underfunction1, underfunction2) )
 *
 */
/*
History:
03.06.2011  Oesterholz  created
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
*/

#ifndef ___C_FUNCTION_IF_H__
#define ___C_FUNCTION_IF_H__


#include "cFunctionTwoValue.h"
#include "cCondition.h"

#include "cmath"


namespace fib{


class cFunctionIf: public cFunctionTwoValue{
	
	/**
	 * A pointer to the condition of the if-function.
	 */
	cCondition * pCondition;
	
public:

	/**
	 * The constructor of the underfunction.
	 *
	 * @param condition the condition for the function
	 * 	@see pCondition
	 * @param firstUnderfunction the first underfunction for the function
	 * 	@see pFirstUnderfunction
	 * @param secondUnderfunction the second underfunction for the function
	 * 	@see pSecondUnderfunction
	 * @param pInSuperiorFunction the underfunction which contains the
	 * 	new underfunction
	 * @param pInDefiningFibElement the fib -element which defines/ uses
	 * 	the new underfunction
	 */
	cFunctionIf( const cCondition & condition,
		const cUnderFunction & firstUnderfunction,
		const cUnderFunction & secondUnderfunction,
		cUnderFunction * pInSuperiorFunction = NULL,
		cFibElement * pInDefiningFibElement = NULL );

	/**
	 * The constructor of the underfunction.
	 *
	 * @param pInCondition a pointer to the condition for the function
	 * 	Beware: It (pInCondition) won't be copied.
	 * 	@see pCondition
	 * @param pInFirstUnderfunction a pointer to the first underfunction
	 *		for the function
	 * 	Beware: It (pInFirstUnderfunction) won't be copied.
	 * 	@see pFirstUnderfunction
	 * @param pInSecondUnderfunction a pointer to the second underfunction
	 * 	for the function
	 * 	Beware: It (pInSecondUnderfunction) won't be copied.
	 * 	@see pSecondUnderfunction
	 * @param pInSuperiorFunction the underfunction which contains the
	 * 	new underfunction
	 * @param pInDefiningFibElement the fib -element which defines/ uses
	 * 	the new underfunction
	 */
	cFunctionIf( cCondition * pInCondition,
		cUnderFunction * pInFirstUnderfunction,
		cUnderFunction * pInSecondUnderfunction,
		cUnderFunction * pInSuperiorFunction = NULL,
		cFibElement * pInDefiningFibElement = NULL );

	/**
	 * The copy constructor of the underfunction.
	 * This constructor will also copy the underfunctions of the given
	 * function.
	 *
	 * @param underfunction the underfunction which to copy
	 * @param pInSuperiorFunction the underfunction which contains the
	 * 	new underfunction
	 * @param pInDefiningFibElement the fib -element which defines/ uses
	 * 	the new underfunction
	 */
	cFunctionIf( const cFunctionIf & underfunction,
		cUnderFunction * pInSuperiorFunction = NULL,
		cFibElement *pInDefiningFibElement = NULL );

	/**
	 * The constructor for restoring a value underfunction from an TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node the underfunction is stored in
	 * @param outStatus An reference to an integervalue where the errorvalue
	 * 	can be stored to.
	 * 	possible errorvalues are:
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
	cFunctionIf( const TiXmlElement * pXmlElement, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		cUnderFunction * pInSuperiorFunction = NULL,
		cFibElement * pInDefiningFibElement = NULL );

	/**
	 * This constructor restores a value underfunction from the stream
	 * where it is stored in the compressed fib -format.
	 * Beware: The bits for the functiontype should be allready readed, this
	 * 	constructor reads yust the two underfunctions.
	 *
	 * @param iBitStream the stream where this underfunction is stored to in,
	 * 	because this stream is an cReadBits, any number of bits can be
	 * 	readed from it
	 * @param outStatus An reference to an integervalue where the errorvalue
	 * 	can be stored to. If the pointer is NULL no errorvalue will be
	 * 	given back.
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid stream
	 * 		- -2 loading error, invalid data in stream
	 * 		- 1 loading warning, invalid data in stream, error could be corrected
	 * 		- 2 loading warning, invalid data in stream, maybe the loaded
	 * 			object is wrong
	 * @param liDefinedVariables a list with the defined variables for the
	 * 	to restore fib -element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 * @param pInDomainValue the domain for value underfunction
	 * @param pInDomainVariable the domain for variables
	 * @param pInSuperiorFunction the underfunction which contains the
	 * 	new underfunction
	 * @param pInDefiningFibElement the fib -element which defines/ uses
	 * 	the new underfunction
	 */
	cFunctionIf( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomainSingle * pInDomainValue, const cDomainSingle * pInDomainVariable,
		cUnderFunction * pInSuperiorFunction = NULL,
		cFibElement * pInDefiningFibElement = NULL );


	/**
	 * The destructor of the underfunction.
	 */
	virtual ~cFunctionIf();


	/**
	 * This method returns if this underfunction is valid, else false.
	 * All values in the underfunction and it's underfunctions must be
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
	 * @param pVariable the variable to check if it is used
	 * @return true if the variable is used, else false
	 */
	virtual bool isUsedVariable( const cFibVariable * pVariable ) const;
	
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
	 * @param pVariableOld the variable to replace
	 * @param pVariableNew the variable with which the variable variableOld
	 * 	is to replace
	 * @return true if the variable variableOld is replaced with variableNew,
	 * 	else false
	 */
	virtual bool replaceVariable( cFibVariable * pVariableOld,
		cFibVariable * pVariableNew );
	
	/**
	 * Sets the Fib -element which defines/ uses this underfunction.
	 * If the given pointer is the nullpointer (standardvalue), no
	 * Fib -element defines this underfunction.
	 *
	 * @param definingFibElement a pointer to the Fib -element which
	 * 	defines/ uses this underfunction
	 * @param bCheckDomains getthe domains of the defining element and
	 * 	check the underfunctionelements with it
	 */
	virtual void setDefiningFibElement( cFibElement *fibElement=NULL,
		bool bCheckDomains=true );
	
	/**
	 * This method evaluades a value for the time needed to evalue the
	 * underfunction.
	 * This value should not exceed lMaxTime, if the value for the time
	 * is greater than lMaxTime the evaluation will be stopt and lMaxTime
	 * returned. If lMaxTime is 0 (for infinity) the evaluation won't be
	 * stoped, this is the standard case.
	 *
	 * @see cFibElement::evalueObject()
	 * @param lMaxTime the maximum time for the evaluation, the returned
	 * 	exceed this value; the value 0 stands for infinity, so the
	 * 	evaluation won't be stoped
	 * @return a value for the time needed to evalue this underfunction
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
	 * Returns the value of the underfunction or 0 if non such exists.
	 *
	 * @return the value of the underfunction or 0 if non
	 * 	such exists
	 */
	virtual doubleFib getValue() const;

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
	 * @return the type for the underfunction
	 */
	virtual unsignedIntFib getType() const;
	
	/**
	 * @return the name for the underfunction
	 */
	virtual string getUnderFunctionName() const;

	/**
	 * This method duplicates this whole underfunction.
	 * Underfunctions of this underfunction are also cloned.
	 *
	 * @param pSuperiorUnderFunction the underfunction which contains
	 * @param pInDefiningFibElement the Fib -element which defines/ uses
	 * @return the cloned/ duplicated underfunction
	 */
	virtual cFunctionIf * clone(
		cUnderFunction * pInSuperiorUnderFunction = NULL,
		cFibElement *pInDefiningFibElement = NULL) const;
	
	/**
	 * This method stores this underfunction in the XML -format into the
	 * given stream.
	 * Variables should have ther number as ther value.
	 *
	 * @param stream the stream where this underfunctionshould be
	 * 	stored to
	 * @return true if this underfunction is stored, else false
	 */
	virtual bool storeXml( ostream &stream ) const;

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
	 * @return This method returns a pointer to the condition of this
	 * 	function. @see pCondition
	 */
	cCondition * getCondition();
	
	/**
	 * @return This method returns a pointer to the condition of this
	 * 	function. @see pCondition
	 */
	const cCondition * getCondition() const;
	
	/**
	 * This methods sets the condition of this function.
	 *
	 * @see pCondition
	 * @param inCondition the condition, which should be set as the
	 * 	condition of this function; the condition will be
	 * 	copied and the copy will be inserted
	 * @param bDeleteOld if true the old condition will be deleted from
	 * 	memory, else the old condition should be deleted elsewhere
	 * @return true if inCondition condition was set, else false
	 */
	bool setCondition( const cCondition & inCondition,
		bool bDeleteOld=true );

	/**
	 * This methods sets the condition of this function.
	 *
	 * @see pCondition
	 * @param pInCondition a pointer to the condition, which should be set
	 * 	as the condition of this function; the condition will be
	 * 	copied and the copy will be inserted
	 * 	Beware: It (pInCondition) won't be copied.
	 * @param bDeleteOld if true the old condition will be deleted from
	 * 	memory, else the old condition should be deleted elsewhere
	 * @return true if pInSubCondition condition was set, else false
	 */
	bool setCondition( cCondition * pInCondition,
		bool bDeleteOld=true );


protected:

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
	 * @return true if the given variable is equal to this variable, else false
	 */
	virtual bool equalInternal( const cUnderFunction & underfunction,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const;

#endif //FEATURE_EQUAL_FIB_OBJECT

};//end class cFunctionIf


}//end namespace fib

#endif
