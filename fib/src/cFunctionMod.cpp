/**
 * @class cFunctionMod
 * file name: cFunctionMod.cpp
 * @author Betti Oesterholz
 * @date 09.11.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a Fib function for the symmetric modulo operator.
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
 * This class represents a Fib function for the symmetric modulo operator.
 * This function works on two subfunctions. The symmetric modulo operator
 * returns the remainder of the integer division.
 * ( mod(x, y) = x - y * int (x / y), where int refers to the truncation of
 * the decimal digits)
 *
 */
/*
History:
09.11.2012  Oesterholz  created
*/


#include "cFunctionMod.h"

#include <math.h>


using namespace fib;


/**
 * The constructor of the subfunction.
 *
 * @param firstUnderfunction the first subfunction for the function
 * 	@see pFirstUnderfunction
 * @param secondUnderfunction the second subfunction for the function
 * 	@see pSecondUnderfunction
 * @param pInSuperiorFunction the subfunction which contains the
 * 	new subfunction
 * @param pInDefiningFibElement the fib -element which defines/ uses
 * 	the new subfunction
 */
cFunctionMod::cFunctionMod( const cUnderFunction & firstUnderfunction,
		const cUnderFunction & secondUnderfunction,
		cUnderFunction * pInSuperiorFunction,
		cFibElement * pInDefiningFibElement ):
		cFunctionTwoValue( firstUnderfunction, secondUnderfunction,
			pInSuperiorFunction, pInDefiningFibElement ){
	//nothing to do
}


/**
 * The copy constructor of the subfunction.
 * This constructor will also copy the subfunctions of the given
 * function.
 *
 * @param subfunction the subfunction which to copy
 * @param pInSuperiorFunction the subfunction which contains the
 * 	new subfunction
 * @param pInDefiningFibElement the fib -element which defines/ uses
 * 	the new subfunction
 */
cFunctionMod::cFunctionMod( const cFunctionMod & subfunction,
		cUnderFunction * pInSuperiorFunction,
		cFibElement *pInDefiningFibElement ):
		cFunctionTwoValue( subfunction, pInSuperiorFunction, pInDefiningFibElement ){
	//nothing to do
}


/**
 * The constructor for restoring a value subfunction from an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node the subfunction is stored in
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
 * @param pInSuperiorFunction the subfunction which contains the
 * 	new subfunction
 * @param pInDefiningFibElement the fib -element which defines/ uses
 * 	the new subfunction
 */
cFunctionMod::cFunctionMod( const TiXmlElement * pXmlElement, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		cUnderFunction * pInSuperiorFunction,
		cFibElement * pInDefiningFibElement ):
		cFunctionTwoValue( pXmlElement, outStatus, liDefinedVariables,
			pInSuperiorFunction, pInDefiningFibElement  ){
		
	if ( pXmlElement == NULL ){
		//noting to restore
		outStatus = -1;
		return;
	}
	//check the subfunction type
	string szElementType( pXmlElement->Value() );
	if ( szElementType != getUnderFunctionName() ){
		//wrong element type to restore
		outStatus = -2;
		return;
	}

}


/**
 * This constructor restores a value subfunction from the stream
 * where it is stored in the compressed fib -format.
 * Beware: The bits for the functiontype should be allready readed, this
 * 	constructor reads yust the two subfunctions.
 *
 * @param iBitStream the stream where this subfunction is stored to in,
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
 * @param pInDomainValue the domain for value subfunction
 * @param pInDomainVariable the domain for variables
 * @param pInSuperiorFunction the subfunction which contains the
 * 	new subfunction
 * @param pInDefiningFibElement the fib -element which defines/ uses
 * 	the new subfunction
 */
cFunctionMod::cFunctionMod( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomainSingle * pInDomainValue, const cDomainSingle * pInDomainVariable,
		cUnderFunction * pInSuperiorFunction,
		cFibElement * pInDefiningFibElement ):
		cFunctionTwoValue( iBitStream, outStatus, liDefinedVariables,
			pInDomainValue, pInDomainVariable, pInSuperiorFunction,
			pInDefiningFibElement  ){
	//nothing to do
}


/**
 * Returns the value of the subfunction or 0 if non such exists.
 *
 * @return the value of the subfunction or 0 if non
 * 	such exists
 */
doubleFib cFunctionMod::getValue() const{
	
	//get the values of the two subfunctions
	doubleFib dValue1 = 0.0;
	doubleFib dValue2 = 0.0;
	
	if ( pFirstUnderfunction ){
		dValue1 = pFirstUnderfunction->getValue();
	}else{//no first subfunction -> get the nullvalue of the domain for the value
		cDomainSingle * pDomain = getDomain();
		bool bStandardDomain = false;
		if ( pDomain == NULL ){
			pDomain = getStandardDomain();
			bStandardDomain = true;
		}
		dValue1 = pDomain->getNull();
		
		if ( bStandardDomain ){
			delete pDomain;
		}
	}
	if ( pSecondUnderfunction ){
		dValue2 = pSecondUnderfunction->getValue();
	}else{//no second subfunction -> get the nullvalue of the domain for the value
		cDomainSingle * pDomain = getDomain();
		bool bStandardDomain = false;
		if ( pDomain == NULL ){
			pDomain = getStandardDomain();
			bStandardDomain = true;
		}
		dValue2 = pDomain->getNull();
		
		if ( bStandardDomain ){
			delete pDomain;
		}
	}
	if ( ( dValue1 == 0.0 ) || ( dValue2 == 0.0 ) ){
		return 0.0;
	}
	return fmod( dValue1, dValue2 );
}


/**
 * This method evaluades the size of the Fib object in bits in the
 * compressed file form.
 * The optional part field of point elements will be ignored.
 *
 * @see store()
 * @return the size of the Fib object in bits in the compressed form
 */
unsignedLongFib cFunctionMod::getCompressedSize() const{

	//mod-function has 5 additional bits to normal cFunctionTwoValue
	
	return 5 + cFunctionTwoValue::getCompressedSize();
}


/**
 * This method stores this Fib object in the compressed Fib -format
 * into the given stream.
 * It is needed becouse the stream can yust store byts but the size of
 * fib -elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the fib -elements.
 *
 * @see store
 * @param stream the stream where this Fib object should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if this Fib object is stored, else false
 */
bool cFunctionMod::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	if ( ( pFirstUnderfunction == NULL ) || ( pSecondUnderfunction == NULL ) ){
		//a subfunction is missing -> can't store
		return false;
	}
	//store the identifier for the function mod
	const char szInitiation[] = { 0x5F, 0x00 };//0001 0 111 11 = 00 0101 1111 = 0x00 0x5F
	const bool bInitiationStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, szInitiation, 10 );
	if ( ! bInitiationStored ){
		return false;
	}
	//store the first subfunction
	const bool bFirstUnderfunctionStored =
		pFirstUnderfunction->store( stream, cRestBits, uiRestBitPosition );
	
	if ( ! bFirstUnderfunctionStored ){
		return false;
	}
	//store the second subfunction
	return pSecondUnderfunction->store( stream, cRestBits, uiRestBitPosition );
}


/**
 * @return the type for the subfunction
 */
unsignedIntFib cFunctionMod::getType() const{

	return FUNCTION_MOD;
}


/**
 * @return the name for the subfunction
 */
string cFunctionMod::getUnderFunctionName() const{

	return "mod";
}


/**
 * This method duplicates this whole subfunction.
 * Underfunctions of this subfunction are also cloned.
 *
 * @param pSuperiorUnderFunction the subfunction which contains
 * @param pInDefiningFibElement the Fib -element which defines/ uses
 * @return the cloned/ duplicated subfunction
 */
cFunctionMod * cFunctionMod::clone(
		cUnderFunction * pInSuperiorUnderFunction,
		cFibElement *pInDefiningFibElement ) const{
	
	return new cFunctionMod( * this, pInSuperiorUnderFunction,
		pInDefiningFibElement );
}







