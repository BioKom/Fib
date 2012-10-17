/**
 * @class cFunctionTwoValue
 * file name: cFunctionTwoValue.cpp
 * @author Betti Oesterholz
 * @date 30.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the basisclass for all two value underfunctions.
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
 * This class represents the basisclass for all two value underfunctions.
 * From this class all classes are derived, which represent functions,
 * which work on two input values.
 *
 */
/*
History:
30.04.2010  Oesterholz  created
03.07.2010  Oesterholz  const get*UnderFunction() added
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
18.04.2012  Oesterholz  Bugfix: replace FirstChild()->ToElement() with
	FirstChildElement()
*/


#include "cFunctionTwoValue.h"


using namespace fib;



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
cFunctionTwoValue::cFunctionTwoValue( const cUnderFunction & firstUnderfunction,
		const cUnderFunction & secondUnderfunction,
		cUnderFunction * pInSuperiorFunction,
		cFibElement * pInDefiningFibElement ):
		cUnderFunction( pInSuperiorFunction, pInDefiningFibElement ),
		pFirstUnderfunction( NULL ), pSecondUnderfunction( NULL ){
	
	setFirstUnderFunction( firstUnderfunction );
	setSecondUnderFunction( secondUnderfunction );
}


/**
 * The constructor of the underfunction.
 *
 * @param pInFirstUnderfunction a pointer to the first underfunction
 * 	for the function
 * 	Beware: It won't be copied for inserting.
 * 	@see pFirstUnderfunction
 * @param pInSecondUnderfunction a pointer to the second underfunction
 * 	for the function
 * 	Beware: It won't be copied for inserting.
 * 	@see pSecondUnderfunction
 * @param pInSuperiorFunction the underfunction which contains the
 * 	new underfunction
 * @param pInDefiningFibElement the fib -element which defines/ uses
 * 	the new underfunction
 */
cFunctionTwoValue::cFunctionTwoValue( cUnderFunction * pInFirstUnderfunction,
		cUnderFunction * pInSecondUnderfunction,
		cUnderFunction * pInSuperiorFunction,
		cFibElement * pInDefiningFibElement ):
		cUnderFunction( pInSuperiorFunction, pInDefiningFibElement ),
		pFirstUnderfunction( pInFirstUnderfunction ),
		pSecondUnderfunction( pInSecondUnderfunction ){
	
	if ( pFirstUnderfunction != NULL ){
		pFirstUnderfunction->pSuperiorUnderFunction = this;
		pFirstUnderfunction->setDefiningFibElement( pInDefiningFibElement, false );
	}
	if ( pSecondUnderfunction != NULL ){
		pSecondUnderfunction->pSuperiorUnderFunction = this;
		pSecondUnderfunction->setDefiningFibElement( pInDefiningFibElement, false );
	}
}



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
cFunctionTwoValue::cFunctionTwoValue( const cFunctionTwoValue & underfunction,
		cUnderFunction * pInSuperiorFunction, cFibElement *pInDefiningFibElement ):
		cUnderFunction( underfunction, pInSuperiorFunction, pInDefiningFibElement ),
		pFirstUnderfunction( NULL ), pSecondUnderfunction( NULL ){
	
	setFirstUnderFunction( *(underfunction.pFirstUnderfunction) );
	setSecondUnderFunction( *(underfunction.pSecondUnderfunction) );
}


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
cFunctionTwoValue::cFunctionTwoValue( const TiXmlElement * pXmlElement, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		cUnderFunction * pInSuperiorFunction, cFibElement * pInDefiningFibElement ):
		cUnderFunction( pInSuperiorFunction, pInDefiningFibElement ),
		pFirstUnderfunction( NULL ), pSecondUnderfunction( NULL ){
	
	if ( pXmlElement == NULL ){
		//noting to restore
		outStatus = -1;
		return;
	}
	
	//restore the underfunctions of the function
	const TiXmlElement * pXmlElementUf = NULL;
	if ( pXmlElement->FirstChild() == NULL ){
		//Error: no underfunctions
		outStatus = -1;
		return;
	}
	pXmlElementUf = pXmlElement->FirstChildElement();
	
	//restore the two underfunctions
	pFirstUnderfunction = cUnderFunction::restoreXml( pXmlElementUf, outStatus,
		liDefinedVariables, this, pInDefiningFibElement );
	
	if ( outStatus < 0 ){
		return;
	}
	pXmlElementUf = pXmlElementUf->NextSiblingElement();
	if ( pXmlElementUf == NULL ){
		//Error: no second underfunctions
		outStatus = -1;
		return;
	}
	
	pSecondUnderfunction = cUnderFunction::restoreXml( pXmlElementUf, outStatus,
		liDefinedVariables, this, pInDefiningFibElement );
}


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
cFunctionTwoValue::cFunctionTwoValue( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomainSingle * pInDomainValue, const cDomainSingle * pInDomainVariable,
		cUnderFunction * pInSuperiorFunction, cFibElement * pInDefiningFibElement ):
		cUnderFunction( pInSuperiorFunction, pInDefiningFibElement ),
		pFirstUnderfunction( NULL ), pSecondUnderfunction( NULL ){
	
	DEBUG_OUT_L3(<<this<<"->cFunctionTwoValue() restore bit"<<endl);
	
	//check the stream type
	if ( ! iBitStream.getStream()->good() ){
		outStatus = -1;
		return;
	}
	
	//restore the two underfunctions
	pFirstUnderfunction = cUnderFunction::restore( iBitStream, outStatus,
		liDefinedVariables, pInDomainValue, pInDomainVariable,
		this, pInDefiningFibElement );
	
	if ( outStatus < 0 ){
		return;
	}
	pSecondUnderfunction = cUnderFunction::restore( iBitStream, outStatus,
		liDefinedVariables, pInDomainValue, pInDomainVariable,
		this, pInDefiningFibElement );
}


/**
 * The destructor of the underfunction.
 */
cFunctionTwoValue::~cFunctionTwoValue(){
	
	if ( pFirstUnderfunction ){
		delete pFirstUnderfunction;
	}
	if ( pSecondUnderfunction ){
		delete pSecondUnderfunction;
	}
}


/**
 * @return This method returns a pointer to the first underfunction of
 * 	this function. @see pFirstUnderfunction
 */
cUnderFunction * cFunctionTwoValue::getFirstUnderFunction(){
	
	return pFirstUnderfunction;
}


/**
 * @return This method returns a pointer to the first underfunction of
 * 	this function. @see pFirstUnderfunction
 */
const cUnderFunction * cFunctionTwoValue::getFirstUnderFunction() const{
	
	return pFirstUnderfunction;
}


/**
 * This methods sets the first underfunction of this function.
 *
 * @see pFirstUnderfunction
 * @param underFunction the underfunction, which should be set as the
 * 	first underfunction of this function; the underfunction will be
 * 	copied and the copy will be inserted
 * @param bDeleteOld if true the old underfunction will be deleted from
 * 	memory, else the old underfunction should be deleted elswher
 */
void cFunctionTwoValue::setFirstUnderFunction(
		const cUnderFunction & underFunction, bool bDeleteOld ){
	
	if ( &underFunction == NULL ){
		//Error: no underfunction to set given
		return;
	}
	if ( pFirstUnderfunction != NULL ){
		if ( bDeleteOld ){
			delete pFirstUnderfunction;
		}else{//cut connections
			if ( pFirstUnderfunction->pSuperiorUnderFunction == this ){
				pFirstUnderfunction->pSuperiorUnderFunction = NULL;
			}
		}
	}
	pFirstUnderfunction = underFunction.clone( this, getDefiningFibElement() );
}


/**
 * @return This method returns a pointer to the second underfunction of
 * 	this function. @see pSecondUnderfunction
 */
cUnderFunction * cFunctionTwoValue::getSecondUnderFunction(){
	
	return pSecondUnderfunction;
}


/**
 * @return This method returns a pointer to the second underfunction of
 * 	this function. @see pSecondUnderfunction
 */
const cUnderFunction * cFunctionTwoValue::getSecondUnderFunction() const{
	
	return pSecondUnderfunction;
}


/**
 * This methods sets the second underfunction of this function.
 *
 * @see pSecondUnderfunction
 * @param underFunction the underfunction, which should be set as the
 * 	second underfunction of this function; the underfunction will be
 * 	copied and the copy will be inserted
 * @param bDeleteOld if true the old underfunction will be deleted from
 * 	memory, else the old underfunction should be deleted elswher
 */
void cFunctionTwoValue::setSecondUnderFunction(
		const cUnderFunction & underFunction,
		bool bDeleteOld ){
	
	if ( &underFunction == NULL ){
		//Error: no underfunction to set given
		return;
	}
	if ( pSecondUnderfunction != NULL ){
		if ( bDeleteOld ){
			delete pSecondUnderfunction;
		}else{//cut connections
			if ( pSecondUnderfunction->pSuperiorUnderFunction == this ){
				pSecondUnderfunction->pSuperiorUnderFunction = NULL;
			}
		}
	}
	pSecondUnderfunction = underFunction.clone( this, getDefiningFibElement() );
}


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
bool cFunctionTwoValue::isValid() const{
	
	if ( (pFirstUnderfunction == NULL) || (pSecondUnderfunction == NULL) ){
		return false;
	}
	if ( ! pFirstUnderfunction->isValid() ){
		return false;
	}
	return pSecondUnderfunction->isValid();
}


/**
 * This method checks if the given variable is used in this underfunction.
 *
 * @see cFibVariable
 * @param variable the variable to check if it is used
 * @return true if the variable is used, else false
 */
bool cFunctionTwoValue::isUsedVariable( const cFibVariable * variable ) const{
	
	//check variables in both underfunctions
	if ( pFirstUnderfunction ){
		if ( pFirstUnderfunction->isUsedVariable( variable ) ){
			return true;
		}
	}
	if ( pSecondUnderfunction ){
		if ( pSecondUnderfunction->isUsedVariable( variable ) ){
			return true;
		}
	}
	return false;
}


/**
 * This method returns all variables used in this underfunction.
 *
 * @see cFibVariable
 * @return all variables used in this underfunction
 */
set<cFibVariable*> cFunctionTwoValue::getUsedVariables(){
	
	//get variables from both underfunctions
	set<cFibVariable*> setUsedVariables;
	if ( pFirstUnderfunction ){
		setUsedVariables = pFirstUnderfunction->getUsedVariables();
	}
	if ( pSecondUnderfunction ){
		set<cFibVariable*> setUsedVariablesInSecond =
			pSecondUnderfunction->getUsedVariables();
		
		setUsedVariables.insert( setUsedVariablesInSecond.begin(),
			setUsedVariablesInSecond.end() );
	}
	return setUsedVariables;
}


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
bool cFunctionTwoValue::replaceVariable( cFibVariable *variableOld,
		cFibVariable *variableNew ){
	
	if ( (variableOld == NULL) || (variableNew == NULL) ){
		return false;
	}
	//replace variables in both underfunctions
	bool bReplaceVariables = true;
	if ( pFirstUnderfunction ){
		bReplaceVariables =
			pFirstUnderfunction->replaceVariable( variableOld, variableNew );
		if ( ! bReplaceVariables ){
			return false;
		}
	}
	if ( pSecondUnderfunction ){
		bReplaceVariables =
			pSecondUnderfunction->replaceVariable( variableOld, variableNew );
	}
	return bReplaceVariables;
}


/**
 * @return the number of underfunctions, a underfunction of this type has
 */
unsignedIntFib cFunctionTwoValue::getNumberOfUnderFunctions() const{

	return 2;
}


/**
 * Sets the Fib-element which defines/ uses this underfunction.
 * If the given pointer is the nullpointer (standardvalue), no
 * Fib-element defines this underfunction.
 *
 * @param definingFibElement a pointer to the Fib-element which
 * 	defines/ uses this underfunction
 * @param bCheckDomains get the domains of the defining element and
 * 	check the underfunctionelements with it
 */
void cFunctionTwoValue::setDefiningFibElement( cFibElement * fibElement,
		bool bCheckDomains ){
	
	//set the defining fib -elements in both underfunctions
	if ( pFirstUnderfunction ){
		pFirstUnderfunction->setDefiningFibElement( fibElement, bCheckDomains );
	}
	if ( pSecondUnderfunction ){
		pSecondUnderfunction->setDefiningFibElement( fibElement, bCheckDomains );
	}
	cUnderFunction::setDefiningFibElement( fibElement, bCheckDomains );
}


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
unsignedLongFib cFunctionTwoValue::getTimeNeed( unsignedLongFib lMaxTime ) const{
	
	if ( lMaxTime == 1 ){
		//the time is needed for the underfunction
		return 1;
	}
	unsignedLongFib ulTimeNeed = 1;
	
	//get the time need from in both underfunctions
	if ( pFirstUnderfunction ){
		
		if ( lMaxTime == 0 ){
			//no evalue time bouderie
			ulTimeNeed += pFirstUnderfunction->getTimeNeed( 0 );
		}else{//lMaxTime is an evalue time bouderie
			ulTimeNeed += pFirstUnderfunction->getTimeNeed( lMaxTime - 1 );
			
			if ( (lMaxTime != 0) && (lMaxTime <= ulTimeNeed) ){
				return lMaxTime;
			}
		}
	}
	if ( pSecondUnderfunction ){
		if ( lMaxTime == 0 ){
			//no evalue time bouderie
			ulTimeNeed += pSecondUnderfunction->getTimeNeed( 0 );
		}else{//lMaxTime is an evalue time bouderie
			ulTimeNeed += pSecondUnderfunction->getTimeNeed( lMaxTime - ulTimeNeed );
			
			if ( (lMaxTime != 0) && (lMaxTime <= ulTimeNeed) ){
				return lMaxTime;
			}
		}
	}
	return ulTimeNeed;
}


/**
 * This method evaluades the size of the Fib-object in bits in the
 * compressed file form.
 * The optionalpart field of point -elements will be ignored.
 *
 * @see store()
 * @return the size of the Fib-object in bits in the compressed form
 */
unsignedLongFib cFunctionTwoValue::getCompressedSize() const{

	unsignedLongFib ulCompressedSize = 5;
	
	//evaluing and add the compressed size for both underfunctions
	if ( pFirstUnderfunction ){
		ulCompressedSize += pFirstUnderfunction->getCompressedSize();
	}
	if ( pSecondUnderfunction ){
		ulCompressedSize += pSecondUnderfunction->getCompressedSize();
	}

	
	return ulCompressedSize;
}


/**
 * This method stores this underfunction in the XML -format into the
 * given stream.
 * Variables should have ther number as ther value.
 *
 * @param stream the stream where this underfunctionshould be
 * 	stored to
 * @return true if this underfunction is stored, else false
 */
bool cFunctionTwoValue::storeXml( ostream &stream ) const{

	const string szUnderFunctionName = getUnderFunctionName();
	stream<<"<"<< szUnderFunctionName <<">"<<endl;
	
	bool bUnderFunctionStoredCorrect = true;
	
	//store both underfunctions in the xml -format
	if ( pFirstUnderfunction ){
		bUnderFunctionStoredCorrect =
			pFirstUnderfunction->storeXml( stream );
	}else{
		bUnderFunctionStoredCorrect = false;
	}
	if ( pSecondUnderfunction ){
		bUnderFunctionStoredCorrect &=
			pSecondUnderfunction->storeXml( stream );
	}else{
		bUnderFunctionStoredCorrect = false;
	}

	stream<<"</"<< szUnderFunctionName <<">"<<endl;

	return bUnderFunctionStoredCorrect;
}



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
bool cFunctionTwoValue::equalInternal( const cUnderFunction & underfunction,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{
	
	if ( & underfunction == NULL ){
		return false;
	}
	if ( getType() != underfunction.getType() ){
		//underfunctions don't have the same type
		return false;
	}
	const cFunctionTwoValue * pFunctionTwoValue = (const cFunctionTwoValue *)( & underfunction);
	
	//compare the first underfunction
	if ( pFirstUnderfunction != NULL ){
		if ( pFunctionTwoValue->pFirstUnderfunction == NULL ){
			return false;
		}
		if ( ! pFirstUnderfunction->equalInternal( *(pFunctionTwoValue->pFirstUnderfunction),
				mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
			return false;
		}
	}else{//pFirstUnderfunction == NULL
		
		if ( pFunctionTwoValue->pFirstUnderfunction != NULL ){
			return false;
		}
	}
		
	//compare the second underfunction
	if ( pSecondUnderfunction != NULL ){
		if ( pFunctionTwoValue->pSecondUnderfunction == NULL ){
			return false;
		}
		if ( ! pSecondUnderfunction->equalInternal( *(pFunctionTwoValue->pSecondUnderfunction),
				mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
			return false;
		}
	}else{//pSecondUnderfunction == NULL
		
		if ( pFunctionTwoValue->pSecondUnderfunction != NULL ){
			return false;
		}
	}

	return true;
}

#else //FEATURE_EQUAL_FIB_OBJECT

/**
 * This Method checks if the given underfunction is equal to this underfunction.
 *
 * @param underfunction the underfunction to compare with this underfunction
 * @return true if the given underfunction is equal to this underfunction, else false
 */
bool cFunctionTwoValue::equal( const cUnderFunction & underfunction ) const{
	
	if ( & underfunction == NULL ){
		return false;
	}
	if ( getType() != underfunction.getType() ){
		//underfunctions don't have the same type
		return false;
	}
	const cFunctionTwoValue * pFunctionTwoValue = (const cFunctionTwoValue *)( & underfunction);
	
	//compare the first underfunction
	if ( pFirstUnderfunction != NULL ){
		if ( pFunctionTwoValue->pFirstUnderfunction == NULL ){
			return false;
		}
		if ( ! pFirstUnderfunction->equal( *(pFunctionTwoValue->pFirstUnderfunction) ) ){
			return false;
		}
	}else{//pFirstUnderfunction == NULL
		
		if ( pFunctionTwoValue->pFirstUnderfunction != NULL ){
			return false;
		}
	}
		
	//compare the second underfunction
	if ( pSecondUnderfunction != NULL ){
		if ( pFunctionTwoValue->pSecondUnderfunction == NULL ){
			return false;
		}
		if ( ! pSecondUnderfunction->equal( *(pFunctionTwoValue->pSecondUnderfunction) ) ){
			return false;
		}
	}else{//pSecondUnderfunction == NULL
		
		if ( pFunctionTwoValue->pSecondUnderfunction != NULL ){
			return false;
		}
	}

	return true;
}

#endif //FEATURE_EQUAL_FIB_OBJECT




