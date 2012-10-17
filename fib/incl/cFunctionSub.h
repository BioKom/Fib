/**
 * @class cFunctionSub
 * file name: cFunctionSub.h
 * @author Betti Oesterholz
 * @date 03.05.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a Fib -function for subtraction.
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
 * This class represents a Fib -function for subtraction.
 * This function works on two underfunctions which values are subtracted.
 * (underfunction1 - underfunction2)
 *
 */
/*
History:
03.05.2010  Oesterholz  created
*/

#ifndef ___C_FUNCTION_SUB_H__
#define ___C_FUNCTION_SUB_H__


#include "cFunctionTwoValue.h"


namespace fib{


class cFunctionSub: public cFunctionTwoValue{

public:

	/**
	 * The constructor of the underfunction.
	 *
	 * @param firstUnderfunction the first underfunction for the function
	 * 	@see pFirstUnderfunction
	 * @param secondUnderfunction the second underfunction for the function
	 * 	@see pSecondUnderfunction
	 * @param pInSuperiorFunction the underfunction which contains the
	 * 	new underfunction
	 * @param pInDefiningFibElement the fib -element which defines/ uses
	 * 	the new underfunction
	 */
	cFunctionSub( const cUnderFunction & firstUnderfunction,
		const cUnderFunction & secondUnderfunction,
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
	cFunctionSub( const cFunctionSub & underfunction,
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
	cFunctionSub( const TiXmlElement * pXmlElement, intFib & outStatus,
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
	cFunctionSub( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomainSingle * pInDomainValue, const cDomainSingle * pInDomainVariable,
		cUnderFunction * pInSuperiorFunction = NULL,
		cFibElement * pInDefiningFibElement = NULL );


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
	virtual cFunctionSub * clone(
		cUnderFunction * pInSuperiorUnderFunction = NULL,
		cFibElement *pInDefiningFibElement = NULL) const;



};//end class cFunctionSub


}//end namespace fib

#endif
