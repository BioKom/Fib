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
18.04.2012  Oesterholz  Bugfix: replace FirstChild()->ToElement() with
	FirstChildElement()
*/


#include "cFunctionIf.h"


using namespace fib;


/**
 * The constructor of the underfunction.
 *
 * @param firstUnderfunction the first underfunction for the function
 * 	@see pFirstUnderfunction
 * @param condition the condition for the function
 * 	@see pCondition
 * @param secondUnderfunction the second underfunction for the function
 * 	@see pSecondUnderfunction
 * @param pInSuperiorFunction the underfunction which contains the
 * 	new underfunction
 * @param pInDefiningFibElement the fib -element which defines/ uses
 * 	the new underfunction
 */
cFunctionIf::cFunctionIf( const cCondition & condition,
		const cUnderFunction & firstUnderfunction,
		const cUnderFunction & secondUnderfunction,
		cUnderFunction * pInSuperiorFunction,
		cFibElement * pInDefiningFibElement ):
		cFunctionTwoValue( firstUnderfunction, secondUnderfunction,
			pInSuperiorFunction, pInDefiningFibElement ),
		pCondition( NULL ){
	
	setCondition( condition );
}


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
cFunctionIf::cFunctionIf( cCondition * pInCondition,
		cUnderFunction * pInFirstUnderfunction,
		cUnderFunction * pInSecondUnderfunction,
		cUnderFunction * pInSuperiorFunction,
		cFibElement * pInDefiningFibElement ):
		cFunctionTwoValue( pInFirstUnderfunction, pInSecondUnderfunction,
			pInSuperiorFunction, pInDefiningFibElement ),
		pCondition( NULL ){
	
	setCondition( pInCondition );
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
cFunctionIf::cFunctionIf( const cFunctionIf & underfunction,
		cUnderFunction * pInSuperiorFunction,
		cFibElement *pInDefiningFibElement ):
		cFunctionTwoValue( underfunction, pInSuperiorFunction, pInDefiningFibElement ),
		pCondition( NULL ){
	
	setCondition( *(underfunction.getCondition()) );
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
cFunctionIf::cFunctionIf( const TiXmlElement * pXmlElement, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		cUnderFunction * pInSuperiorFunction,
		cFibElement * pInDefiningFibElement ):
		cFunctionTwoValue( NULL, NULL, pInSuperiorFunction, pInDefiningFibElement ),
		pCondition( NULL ){
	
	if ( pXmlElement == NULL ){
		//noting to restore
		outStatus = -1;
		return;
	}
	//check the underfunction type
	string szElementType( pXmlElement->Value() );
	if ( szElementType != getUnderFunctionName() ){
		//wrong element type to restore
		outStatus = -2;
		return;
	}
	
	//restore the condition of the function
	const TiXmlElement * pXmlElementUf = NULL;
	if ( pXmlElement->FirstChild() == NULL ){
		//Error: no underfunctions
		outStatus = -1;
		return;
	}
	pXmlElementUf = pXmlElement->FirstChildElement();
	
	pCondition = cCondition::restoreXml( pXmlElementUf, outStatus,
		liDefinedVariables, NULL, pInDefiningFibElement );
	
	if ( outStatus < 0 ){
		return;
	}
	pXmlElementUf = pXmlElementUf->NextSiblingElement();
	if ( pXmlElementUf == NULL ){
		//Error: no first underfunction
		outStatus = -1;
		return;
	}
	//restore the two underfunctions
	pFirstUnderfunction = cUnderFunction::restoreXml( pXmlElementUf, outStatus,
		liDefinedVariables, this, pInDefiningFibElement );
	
	if ( outStatus < 0 ){
		return;
	}
	pXmlElementUf = pXmlElementUf->NextSiblingElement();
	if ( pXmlElementUf == NULL ){
		//Error: no second underfunction
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
cFunctionIf::cFunctionIf( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomainSingle * pInDomainValue, const cDomainSingle * pInDomainVariable,
		cUnderFunction * pInSuperiorFunction, cFibElement * pInDefiningFibElement ):
		cFunctionTwoValue( NULL, NULL, pInSuperiorFunction, pInDefiningFibElement ),
		pCondition( NULL ){
		
	DEBUG_OUT_L3(<<this<<"->cFunctionIf() restore bit"<<endl);
	
	//check the stream type
	if ( ! iBitStream.getStream()->good() ){
		outStatus = -1;
		return;
	}
	
	//restore the condition
	pCondition = cCondition::restore( iBitStream, outStatus,
		liDefinedVariables, pInDomainValue, pInDomainVariable,
		NULL, pInDefiningFibElement );
	
	if ( outStatus < 0 ){
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
cFunctionIf::~cFunctionIf(){
	
	if ( pCondition ){
		delete pCondition;
	}
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
bool cFunctionIf::isValid() const{
	
	if ( pCondition == NULL ){
		//no condition -> not valid
		return false;
	}
	if ( ! pCondition->isValid() ){
		//condition not valid -> not valid
		return false;
	}
	
	return cFunctionTwoValue::isValid();
}


/**
 * This method checks if the given variable is used in this underfunction.
 *
 * @see cFibVariable
 * @param pVariable the variable to check if it is used
 * @return true if the variable is used, else false
 */
bool cFunctionIf::isUsedVariable( const cFibVariable * pVariable ) const{
	
	if ( pCondition ){
		if ( pCondition->isUsedVariable( pVariable ) ){
			return true;
		}
	}
	
	return cFunctionTwoValue::isUsedVariable( pVariable );
}


/**
 * This method returns all variables used in this underfunction.
 *
 * @see cFibVariable
 * @return all variables used in this underfunction
 */
set< cFibVariable* > cFunctionIf::getUsedVariables(){
	
	
	//get variables from both underfunctions
	set<cFibVariable*> setUsedVariables =
		cFunctionTwoValue::getUsedVariables();
	
	if ( pCondition ){
		set<cFibVariable*> setUsedVariablesInCondition =
			pCondition->getUsedVariables();
		
		setUsedVariables.insert( setUsedVariablesInCondition.begin(),
			setUsedVariablesInCondition.end() );
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
 * @param pVariableOld the variable to replace
 * @param pVariableNew the variable with which the variable variableOld
 * 	is to replace
 * @return true if the variable variableOld is replaced with variableNew,
 * 	else false
 */
bool cFunctionIf::replaceVariable( cFibVariable * pVariableOld,
		cFibVariable * pVariableNew ){
	
	if ( (pVariableOld == NULL) || (pVariableNew == NULL) ){
		return false;
	}
	//replace variables in condition
	if ( pCondition ){
		const bool bReplaceVariables =
			pCondition->replaceVariable( pVariableOld, pVariableNew );
		if ( ! bReplaceVariables ){
			return false;
		}
	}

	return cFunctionTwoValue::replaceVariable( pVariableOld, pVariableNew );;
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
void cFunctionIf::setDefiningFibElement( cFibElement * fibElement,
		bool bCheckDomains ){
	
	//set the defining fib -elements in both underfunctions
	if ( pCondition ){
		pCondition->setDefiningFibElement( fibElement, bCheckDomains );
	}
	cFunctionTwoValue::setDefiningFibElement( fibElement, bCheckDomains );
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
unsignedLongFib cFunctionIf::getTimeNeed( unsignedLongFib lMaxTime ) const{
	
	if ( lMaxTime == 1 ){
		//the time is needed for the underfunction
		return 1;
	}
	unsignedLongFib ulTimeNeed = 0;
	
	//get the time need from in both underfunctions
	if ( pCondition ){
		
		if ( lMaxTime == 0 ){
			//no evalue time bouderie
			ulTimeNeed += pCondition->getTimeNeed( 0 );
		}else{//lMaxTime is an evalue time bouderie
			ulTimeNeed += pCondition->getTimeNeed( lMaxTime - 1 );
			
			if ( (lMaxTime != 0) && (lMaxTime <= (ulTimeNeed + 1)) ){
				return lMaxTime;
			}
		}
	}
	if ( lMaxTime == 0 ){
		//no evalue time bouderie
		ulTimeNeed += cFunctionTwoValue::getTimeNeed( 0 );
	}else{//lMaxTime is an evalue time bouderie
		ulTimeNeed += cFunctionTwoValue::getTimeNeed( lMaxTime - ulTimeNeed );
		
		if ( (lMaxTime != 0) && (lMaxTime <= ulTimeNeed) ){
			return lMaxTime;
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
unsignedLongFib cFunctionIf::getCompressedSize() const{

	//if-function has 5 additional bits to normal cFunctionTwoValue
	unsignedLongFib ulCompressedSize = 5;
	
	//evaluing and add the compressed size for the condition
	if ( pCondition ){
		ulCompressedSize += pCondition->getCompressedSize();
	}

	
	return ulCompressedSize + cFunctionTwoValue::getCompressedSize();
}



/**
 * Returns the value of the underfunction or 0 if non such exists.
 *
 * @return the value of the underfunction or 0 if non
 * 	such exists
 */
doubleFib cFunctionIf::getValue() const{
	
	//evalue condition value; if no condition -> condition is false
	const bool bCondition = ( pCondition != NULL ) ?
		pCondition->getValue() : false;
	
	//get the values of the two underfunctions
	if ( bCondition ){
		//evalue first subfunction
		if ( pFirstUnderfunction ){
			return pFirstUnderfunction->getValue();
		}else{//no first underfunction -> get the nullvalue of the domain for the value
			cDomainSingle * pDomain = getDomain();
			bool bStandardDomain = false;
			if ( pDomain == NULL ){
				pDomain = getStandardDomain();
				bStandardDomain = true;
			}
			const doubleFib dValue1 = pDomain->getNull();
			
			if ( bStandardDomain ){
				delete pDomain;
			}
			return dValue1;
		}
	}//else evalue second subfunction
	if ( pSecondUnderfunction ){
		return pSecondUnderfunction->getValue();
	}//else no second underfunction -> get the nullvalue of the domain for the value
	cDomainSingle * pDomain = getDomain();
	bool bStandardDomain = false;
	if ( pDomain == NULL ){
		pDomain = getStandardDomain();
		bStandardDomain = true;
	}
	const doubleFib dValue2 = pDomain->getNull();
	
	if ( bStandardDomain ){
		delete pDomain;
	}
	return dValue2;
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
bool cFunctionIf::storeXml( ostream &stream ) const{

	const string szUnderFunctionName = getUnderFunctionName();
	stream<<"<"<< szUnderFunctionName <<">"<<endl;
	
	bool bSubElementsStoredCorrect = true;
	
	//store the condition
	if ( pCondition ){
		bSubElementsStoredCorrect =
			pCondition->storeXml( stream );
	}else{
		bSubElementsStoredCorrect = false;
	}
	//store both underfunctions in the xml -format
	if ( pFirstUnderfunction ){
		bSubElementsStoredCorrect =
			pFirstUnderfunction->storeXml( stream );
	}else{
		bSubElementsStoredCorrect = false;
	}
	if ( pSecondUnderfunction ){
		bSubElementsStoredCorrect &=
			pSecondUnderfunction->storeXml( stream );
	}else{
		bSubElementsStoredCorrect = false;
	}

	stream<<"</"<< szUnderFunctionName <<">"<<endl;

	return bSubElementsStoredCorrect;
}

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
bool cFunctionIf::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	if ( ( pCondition == NULL ) || ( pFirstUnderfunction == NULL ) ||
			( pSecondUnderfunction == NULL ) ){
		//condition or a underfunction is missing -> can't store
		return false;
	}
	//store the identifier for the function if
	const char szInitiation[] = { 0x1F, 0x00 };// 0000 0 111 11 = 00 0001 1111 = 0x00 0x1F
	const bool bInitiationStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, szInitiation, 10 );
	if ( ! bInitiationStored ){
		return false;
	}
	//store the first underfunction
	const bool bConditionStored =
		pCondition->store( stream, cRestBits, uiRestBitPosition );
	
	if ( ! bConditionStored ){
		return false;
	}
	//store the first underfunction
	const bool bFirstUnderfunctionStored =
		pFirstUnderfunction->store( stream, cRestBits, uiRestBitPosition );
	
	if ( ! bFirstUnderfunctionStored ){
		return false;
	}
	//store the second underfunction
	return pSecondUnderfunction->store( stream, cRestBits, uiRestBitPosition );
}


/**
 * @return the type for the underfunction
 */
unsignedIntFib cFunctionIf::getType() const{

	return FUNCTION_IF;
}


/**
 * @return the name for the underfunction
 */
string cFunctionIf::getUnderFunctionName() const{

	return "if";
}


/**
 * This method duplicates this whole underfunction.
 * Underfunctions of this underfunction are also cloned.
 *
 * @param pSuperiorUnderFunction the underfunction which contains
 * @param pInDefiningFibElement the Fib -element which defines/ uses
 * @return the cloned/ duplicated underfunction
 */
cFunctionIf * cFunctionIf::clone(
		cUnderFunction * pInSuperiorUnderFunction,
		cFibElement *pInDefiningFibElement ) const{
	
	return new cFunctionIf( * this, pInSuperiorUnderFunction,
		pInDefiningFibElement );
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
 * @return true if the given variable is equal to this variable, else false
 */
bool cFunctionIf::equalInternal( const cUnderFunction & underfunction,
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
	const cFunctionIf * pFunctionTwoValue = (const cFunctionIf *)( & underfunction);
	
	//compare the condition
	if ( pCondition != NULL ){
		if ( pFunctionTwoValue->pCondition == NULL ){
			return false;
		}
		if ( ! pCondition->equalInternal( *(pFunctionTwoValue->pCondition),
				mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
			return false;
		}
	}else{//pFirstUnderfunction == NULL
		
		if ( pFunctionTwoValue->pCondition != NULL ){
			return false;
		}
	}
	
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
bool cFunctionIf::equal( const cUnderFunction & underfunction ) const{

	if ( & underfunction == NULL ){
		return false;
	}
	if ( getType() != underfunction.getType() ){
		//underfunctions don't have the same type
		return false;
	}
	const cFunctionIf * pFunctionTwoValue = (const cFunctionIf *)( & underfunction);
	
	//compare the condition
	if ( pCondition != NULL ){
		if ( pFunctionTwoValue->pCondition == NULL ){
			return false;
		}
		if ( ! pCondition->equal( *(pFunctionTwoValue->pCondition) ) ){
			return false;
		}
	}else{//pFirstUnderfunction == NULL
		
		if ( pFunctionTwoValue->pCondition != NULL ){
			return false;
		}
	}
	
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

/**
 * @return This method returns a pointer to the condition of this
 * 	function. @see pCondition
 */
cCondition * cFunctionIf::getCondition(){
	
	return pCondition;
}


/**
 * @return This method returns a pointer to the condition of this
 * 	function. @see pCondition
 */
const cCondition * cFunctionIf::getCondition() const{
	
	return pCondition;
}


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
bool cFunctionIf::setCondition( const cCondition & inCondition,
		bool bDeleteOld ){

	if ( ( & inCondition ) != NULL ){
		
		if ( bDeleteOld && ( pCondition != NULL ) ){
			delete pCondition;
		}
		pCondition = inCondition.clone( NULL, getDefiningFibElement() );
		return true;
	}//else
	return false;
}


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
 * @return true if pInCondition condition was set, else false
 */
bool cFunctionIf::setCondition( cCondition * pInCondition,
		bool bDeleteOld ){

	if ( pInCondition != NULL ){
		
		if ( bDeleteOld && ( pCondition != NULL ) ){
			delete pCondition;
		}
		pCondition = pInCondition;
		pCondition->setDefiningFibElement( getDefiningFibElement() );
		return true;
	}//else
	return false;
}













