/**
 * @class cFunctionOneValue
 * file name: cFunctionOneValue.cpp
 * @author Betti Oesterholz
 * @date 08.05.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the basisclass for all one value underfunction.
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
 * This class represents the basisclass for all one value underfunction.
 * From this class all classes are derived, which represent functions,
 * which work on one input values.
 *
 */
/*
History:
08.05.2010  Oesterholz  created
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
18.04.2012  Oesterholz  Bugfix: replace FirstChild()->ToElement() with
	FirstChildElement()
*/


#include "cFunctionOneValue.h"


using namespace fib;



/**
 * The constructor of the underfunction.
 *
 * @param pUnderfunction a pointer to the underfunction for the function
 * 	(a clone of the underfunction will be taken as the underfunction of
 * 	this function; this is a pointer, so that this constructor didn't
 * 	gets confused with the copy constructor) @see pUnderfunction
 * @param pInSuperiorFunction the underfunction which contains the
 * 	new underfunction
 * @param pInDefiningFibElement the fib -element which defines/ uses
 * 	the new underfunction
 */
cFunctionOneValue::cFunctionOneValue( const cUnderFunction * const pUnderfunction,
		cUnderFunction * pInSuperiorFunction,
		cFibElement * pInDefiningFibElement ):
		cUnderFunction( pInSuperiorFunction, pInDefiningFibElement ),
		pUnderfunction( NULL ){
	
	setUnderFunction( *pUnderfunction );
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
cFunctionOneValue::cFunctionOneValue( const cFunctionOneValue & underfunction,
		cUnderFunction * pInSuperiorFunction, cFibElement *pInDefiningFibElement ):
		cUnderFunction( underfunction, pInSuperiorFunction, pInDefiningFibElement ),
		pUnderfunction( NULL ){
	
	setUnderFunction( *(underfunction.pUnderfunction) );
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
cFunctionOneValue::cFunctionOneValue( const TiXmlElement * pXmlElement, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		cUnderFunction * pInSuperiorFunction, cFibElement * pInDefiningFibElement ):
		cUnderFunction( pInSuperiorFunction, pInDefiningFibElement ),
		pUnderfunction( NULL ){
	
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
	
	//restore the one underfunctions
	pUnderfunction = cUnderFunction::restoreXml( pXmlElementUf, outStatus,
		liDefinedVariables, this, pInDefiningFibElement );
	
}


/**
 * This constructor restores a value underfunction from the stream
 * where it is stored in the compressed fib -format.
 * Beware: The bits for the functiontype should be allready readed, this
 * 	constructor reads yust the one underfunctions.
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
cFunctionOneValue::cFunctionOneValue( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomainSingle * pInDomainValue, const cDomainSingle * pInDomainVariable,
		cUnderFunction * pInSuperiorFunction, cFibElement * pInDefiningFibElement ):
		cUnderFunction( pInSuperiorFunction, pInDefiningFibElement ),
		pUnderfunction( NULL ){
	
	DEBUG_OUT_L3(<<this<<"->cFunctionOneValue() restore bit"<<endl);
	
	//check the stream type
	if ( ! iBitStream.getStream()->good() ){
		outStatus = -1;
		return;
	}
	
	//restore the one underfunctions
	pUnderfunction = cUnderFunction::restore( iBitStream, outStatus,
		liDefinedVariables, pInDomainValue, pInDomainVariable,
		this, pInDefiningFibElement );
}


/**
 * The destructor of the underfunction.
 */
cFunctionOneValue::~cFunctionOneValue(){
	
	if ( pUnderfunction ){
		delete pUnderfunction;
	}
}


/**
 * @return This method returns a pointer to the underfunction of
 * 	this function. @see pUnderfunction
 */
cUnderFunction * cFunctionOneValue::getUnderFunction(){
	
	return pUnderfunction;
}


/**
 * This methods sets the underfunction of this function.
 *
 * @see pUnderfunction
 * @param underFunction the underfunction, which should be set as the
 * 	underfunction of this function; the underfunction will be
 * 	copied and the copy will be inserted
 * @param bDeleteOld if true the old underfunction will be deleted from
 * 	memory, else the old underfunction should be deleted elswher
 */
void cFunctionOneValue::setUnderFunction(
		const cUnderFunction & underFunction, bool bDeleteOld ){
	
	if ( &underFunction == NULL ){
		//Error: no underfunction to set given
		return;
	}
	if ( pUnderfunction != NULL ){
		if ( bDeleteOld ){
			delete pUnderfunction;
		}else{//cut connections
			if ( pUnderfunction->pSuperiorUnderFunction == this ){
				pUnderfunction->pSuperiorUnderFunction = NULL;
			}
		}
	}
	pUnderfunction = underFunction.clone( this, getDefiningFibElement() );
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
bool cFunctionOneValue::isValid() const{
	
	if ( pUnderfunction == NULL ){
		return false;
	}
	return pUnderfunction->isValid();
}


/**
 * This method checks if the given variable is used in this underfunction.
 *
 * @see cFibVariable
 * @param variable the variable to check if it is used
 * @return true if the variable is used, else false
 */
bool cFunctionOneValue::isUsedVariable( const cFibVariable * variable ) const{
	
	//check variables in underfunctions
	if ( pUnderfunction ){
		if ( pUnderfunction->isUsedVariable( variable ) ){
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
set<cFibVariable*> cFunctionOneValue::getUsedVariables(){
	
	//get variables from underfunctions
	if ( pUnderfunction ){
		return pUnderfunction->getUsedVariables();
	}
	return set<cFibVariable*>();
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
bool cFunctionOneValue::replaceVariable( cFibVariable *variableOld,
		cFibVariable *variableNew ){
	
	if ( (variableOld == NULL) || (variableNew == NULL) ){
		return false;
	}
	//replace variables in underfunctions
	bool bReplaceVariables = true;
	if ( pUnderfunction ){
		bReplaceVariables =
			pUnderfunction->replaceVariable( variableOld, variableNew );
	}
	return bReplaceVariables;
}


/**
 * @return the number of underfunctions, a underfunction of this type has
 */
unsignedIntFib cFunctionOneValue::getNumberOfUnderFunctions() const{

	return 1;
}


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
void cFunctionOneValue::setDefiningFibElement( cFibElement * fibElement,
		bool bCheckDomains ){
	
	//set the defining fib -elements in underfunctions
	if ( pUnderfunction ){
		pUnderfunction->setDefiningFibElement( fibElement, bCheckDomains );
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
unsignedLongFib cFunctionOneValue::getTimeNeed( unsignedLongFib lMaxTime ) const{
	
	if ( lMaxTime == 1 ){
		//the time is needed for the underfunction
		return 1;
	}
	unsignedLongFib ulTimeNeed = 1;
	
	//get the time need from in underfunctions
	if ( pUnderfunction ){
		
		if ( lMaxTime == 0 ){
			//no evalue time bouderie
			ulTimeNeed += pUnderfunction->getTimeNeed( 0 );
		}else{//lMaxTime is an evalue time bouderie
			ulTimeNeed += pUnderfunction->getTimeNeed( lMaxTime - 1 );
			
			if ( (lMaxTime != 0) && (lMaxTime <= ulTimeNeed) ){
				return lMaxTime;
			}
		}
	}
	return ulTimeNeed;
}


/**
 * This method evaluades the size of the Fib -object in bits in the
 * compressed file form.
 * The optionalpart field of point -elements will be ignored.
 *
 * @see store()
 * @return the size of the Fib -object in bits in the compressed form
 */
unsignedLongFib cFunctionOneValue::getCompressedSize() const{

	unsignedLongFib ulCompressedSize = 4;
	
	//evaluing and add the compressed size for underfunctions
	if ( pUnderfunction ){
		ulCompressedSize += pUnderfunction->getCompressedSize();
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
bool cFunctionOneValue::storeXml( ostream &stream ) const{

	const string szUnderFunctionName = getUnderFunctionName();
	stream<<"<"<< szUnderFunctionName <<">"<<endl;
	
	bool bUnderFunctionStoredCorrect = true;
	
	//store underfunctions in the xml -format
	if ( pUnderfunction ){
		bUnderFunctionStoredCorrect =
			pUnderfunction->storeXml( stream );
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
bool cFunctionOneValue::equalInternal( const cUnderFunction & underfunction,
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
	cFunctionOneValue * pFunctionOneValue = (cFunctionOneValue *)( & underfunction);
	
	//compare the underfunction
	if ( pUnderfunction != NULL ){
		if ( pFunctionOneValue->pUnderfunction == NULL ){
			return false;
		}
		if ( ! pUnderfunction->equalInternal( *(pFunctionOneValue->pUnderfunction),
				mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
			return false;
		}
	}else{//pUnderfunction == NULL 
		
		if ( pFunctionOneValue->pUnderfunction != NULL ){
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
bool cFunctionOneValue::equal( const cUnderFunction & underfunction ) const{
	
	if ( & underfunction == NULL ){
		return false;
	}
	if ( getType() != underfunction.getType() ){
		//underfunctions don't have the same type
		return false;
	}
	cFunctionOneValue * pFunctionOneValue = (cFunctionOneValue *)( & underfunction);
	
	//compare the underfunction
	if ( pUnderfunction != NULL ){
		if ( pFunctionOneValue->pUnderfunction == NULL ){
			return false;
		}
		if ( ! pUnderfunction->equal( *(pFunctionOneValue->pUnderfunction) ) ){
			return false;
		}
	}else{//pUnderfunction == NULL 
		
		if ( pFunctionOneValue->pUnderfunction != NULL ){
			return false;
		}
	}

	return true;
}

#endif //FEATURE_EQUAL_FIB_OBJECT





