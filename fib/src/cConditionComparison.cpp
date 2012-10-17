/**
 * @class cConditionComparison
 * file name: cConditionComparison.cpp
 * @author Betti Oesterholz
 * @date 15.05.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a abstract condition for comparing numbers.
 * Copyright (C) @c LGPL3 2011 Betti Oesterholz
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
 * This class represents a abstract condition with two subfunctions, which
 * values will be compared with this condition.
 *
 */
/*
History:
15.05.2011  Oesterholz  created
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
*/


#include "cConditionComparison.h"



using namespace fib;


/**
 * The constructor of the two value condition.
 *
 * @param pInFirstSubFunction a pointer to the first function, this condition
 * 	contains; Beware: It (pSubFunction) won't be copied.
 * 	@see pFirstSubFunction
 * @param pInSecondSubFunction a pointer to the second function, this
 * 	condition contains; Beware: It (pSubFunction) won't be copied.
 * 	@see pSecondSubFunction
 * @param pInSuperiorCondition the condition which contains the
 * 	new condition
 * @param pInDefiningFibElement the Fib-element which defines/ uses
 * 	the new condition
 */
cConditionComparison::cConditionComparison( cUnderFunction * pInFirstSubFunction,
		cUnderFunction * pInSecondSubFunction,
		cCondition * pInSuperiorCondition,
		cFibElement * pInDefiningFibElement ):
		cCondition( pInSuperiorCondition, pInDefiningFibElement ),
		pFirstSubFunction( pInFirstSubFunction ),
		pSecondSubFunction( pInSecondSubFunction ){
	
	if ( pFirstSubFunction ){
		pFirstSubFunction->pSuperiorUnderFunction = NULL;
		pFirstSubFunction->setDefiningFibElement( pDefiningFibElement );
	}
	if ( pSecondSubFunction ){
		pSecondSubFunction->pSuperiorUnderFunction = NULL;
		pSecondSubFunction->setDefiningFibElement( pDefiningFibElement );
	}
}

/**
 * The constructor of the two value condition.
 *
 * @param inFirstSubFunction the first function, this condition contains
 * 	@see pFirstSubFunction
 * @param inSecondSubFunction the second function, this condition contains
 * 	@see pSecondSubFunction
 * @param pInSuperiorCondition the condition which contains the
 * 	new condition
 * @param pInDefiningFibElement the Fib-element which defines/ uses
 * 	the new condition
 */
cConditionComparison::cConditionComparison( const cUnderFunction & inFirstSubFunction,
		const cUnderFunction & inSecondSubFunction,
		cCondition * pInSuperiorCondition,
		cFibElement * pInDefiningFibElement ):
		cCondition( pInSuperiorCondition, pInDefiningFibElement ),
		pFirstSubFunction( NULL ), pSecondSubFunction( NULL ){
	
	setFirstSubFunction( inFirstSubFunction );
	setSecondSubFunction( inSecondSubFunction );
}


/**
 * The copy constructor of the condition.
 * This constructor will also copy the subfunctions of the given
 * condition.
 *
 * @param condition the condition which to copy
 * @param pInSuperiorCondition the condition which contains the
 * 	new condition
 * @param pInDefiningFibElement the Fib-element which defines/ uses
 * 	the new condition
 */
cConditionComparison::cConditionComparison( const cConditionComparison & condition,
		cCondition * pInSuperiorCondition,
		cFibElement *pInDefiningFibElement ):
		cCondition( condition, pInSuperiorCondition, pInDefiningFibElement ),
		pFirstSubFunction( NULL ), pSecondSubFunction( NULL ){
	
	setFirstSubFunction( *(condition.getFirstSubFunction()) );
	setSecondSubFunction( *(condition.getSecondSubFunction()) );
}


/**
 * The destructor of the condition.
 */
cConditionComparison::~cConditionComparison(){
	
	if ( pFirstSubFunction ){
		delete pFirstSubFunction;
	}
	if ( pSecondSubFunction ){
		delete pSecondSubFunction;
	}
}


/**
 * This method returns if this condition is valid, else false.
 * All subfunction and underfunctions must be valid.
 * No condition should contain itself or should be contained in one
 * of its condition (no cycles allowed).
 *
 * @return true if this condition is valid, else false
 */
bool cConditionComparison::isValid() const{
	
	if ( ( pFirstSubFunction != NULL ) && ( pSecondSubFunction != NULL ) ){
		if ( pFirstSubFunction->isValid() && pSecondSubFunction->isValid() ){
			//both subfunctions are valid -> condition is valid
			return true;
		}
	}
	//subfunctions missing or not valid -> condition not valid
	return false;
}


/**
 * This method checks if the given variable is used in this condition.
 *
 * @see cFibVariable
 * @param variable the variable to check if it is used
 * @return true if the variable is used, else false
 */
bool cConditionComparison::isUsedVariable( const cFibVariable * variable ) const{
	
	if ( pFirstSubFunction != NULL ){
		//no subfunctions -> condition don't use variable
		if ( pFirstSubFunction->isUsedVariable( variable ) ){
			return true;
		}
	}
	if ( pSecondSubFunction != NULL ){
		//no subfunctions -> condition don't use variable
		if ( pSecondSubFunction->isUsedVariable( variable ) ){
			return true;
		}
	}
	return false;
}


/**
 * This method returns all variables used in this condition.
 *
 * @see cFibVariable
 * @return all variables used in this condition
 */
set<cFibVariable*> cConditionComparison::getUsedVariables(){
	
	set< cFibVariable * > setUsedVariables;
	if ( pFirstSubFunction != NULL ){
		//get used variables of first subfunction
		setUsedVariables = pFirstSubFunction->getUsedVariables();
		
	}
	if ( pSecondSubFunction != NULL ){
		//get used variables of second subfunction
		const set< cFibVariable * > setUsedVariablesInSecond =
			pSecondSubFunction->getUsedVariables();
		
		setUsedVariables.insert( setUsedVariablesInSecond.begin(),
			setUsedVariablesInSecond.end() );
	}
	return setUsedVariables;
}


/**
 * This method replace the variable variableOld with the variable
 * variableNew in the condition.
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
bool cConditionComparison::replaceVariable( cFibVariable * variableOld,
		cFibVariable * variableNew ){
	
	if ( (variableOld == NULL) || (variableNew == NULL) ){
		return false;
	}
	bool bVariableReplaced = true;
	if ( pFirstSubFunction != NULL ){
		//replace variable in first subfunction
		bVariableReplaced = pFirstSubFunction->replaceVariable(
			variableOld, variableNew );
		
	}
	if ( pSecondSubFunction != NULL ){
		//replace variable in second subfunction
		bVariableReplaced &= pSecondSubFunction->replaceVariable(
			variableOld, variableNew );
	}
	
	return bVariableReplaced;
}



/**
 * @return the number of conditions, a condition of this type has
 */
unsignedIntFib cConditionComparison::getNumberOfConditions() const{
	//no subfunctions
	return 0;
}


/**
 * @return the number of underfunctions, a condition of this type has
 */
unsignedIntFib cConditionComparison::getNumberOfUnderFunctions() const{
	//no underfunctions
	return 2;
}


/**
 * Sets the Fib-element which defines/ uses this condition.
 * If the given pointer is the nullpointer (standardvalue), no
 * Fib-element defines this condition.
 *
 * @param pDefiningFibElement a pointer to the Fib-element which
 * 	defines/ uses this condition
 * @param bCheckDomains get the domains of the defining element and
 * 	check the underfunctionelements with it
 */
void cConditionComparison::setDefiningFibElement(
		cFibElement * pDefiningFibElement, bool bCheckDomains ){
	
	//set the defining fib -elements in both underfunctions
	if ( pFirstSubFunction ){
		pFirstSubFunction->setDefiningFibElement( pDefiningFibElement, bCheckDomains );
	}
	if ( pSecondSubFunction ){
		pSecondSubFunction->setDefiningFibElement( pDefiningFibElement, bCheckDomains );
	}
	cCondition::setDefiningFibElement( pDefiningFibElement, bCheckDomains );
}


/**
 * This method evaluades a value for the time needed to evalue the
 * condition.
 * This value should not exceed lMaxTime, if the value for the time
 * is greater than lMaxTime the evaluation will be stopt and lMaxTime
 * returned. If lMaxTime is 0 (for infinity) the evaluation won't be
 * stoped, this is the standard case.
 *
 * @see cFibElement::evalueObject()
 * @param lMaxTime the maximum time for the evaluation, the returned
 * 	exceed this value; the value 0 stands for infinity, so the
 * 	evaluation won't be stoped
 * @return a value for the time needed to evalue this condition
 */
unsignedLongFib cConditionComparison::getTimeNeed( unsignedLongFib lMaxTime ) const{
	
	if ( lMaxTime == 0 ){
		
		unsignedLongFib ulTimeNeed = 1;
		if ( pFirstSubFunction != NULL ){
			//get time need for the first subfunction
			ulTimeNeed += pFirstSubFunction->getTimeNeed( lMaxTime );
		}
		if ( pSecondSubFunction != NULL ){
			//get time need for the second subfunction
			ulTimeNeed += pSecondSubFunction->getTimeNeed( lMaxTime );
		}
		return ulTimeNeed;
	}//else
	if ( lMaxTime == 1 ){
		//max time reached
		return 1;
	}
	unsignedLongFib ulTimeNeed = 1;
	
	if ( pFirstSubFunction != NULL ){
		//get time need for the first subfunction
		ulTimeNeed += pFirstSubFunction->getTimeNeed( lMaxTime );
		if ( lMaxTime <= ulTimeNeed ){
			//max time reached
			return lMaxTime;
		}
	}
	if ( pSecondSubFunction != NULL ){
		//get time need for the second subfunction
		ulTimeNeed += pSecondSubFunction->getTimeNeed( lMaxTime );
		
		if ( lMaxTime <= ulTimeNeed ){
			//max time reached
			return lMaxTime;
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
unsignedLongFib cConditionComparison::getCompressedSize() const{

	unsignedLongFib ulCompressedSize = 4;
	
	if ( pFirstSubFunction != NULL ){
		//get the compression size for the first subfunction
		ulCompressedSize += pFirstSubFunction->getCompressedSize();
	}
	if ( pSecondSubFunction != NULL ){
		//get the compression size for the second subfunction
		ulCompressedSize += pSecondSubFunction->getCompressedSize();
		
	}
	return ulCompressedSize;
}


/**
 * This method stores this Fib-object in the compressed Fib-format
 * into the given stream.
 * It is needed becouse the stream can yust store byts but the size of
 * Fib-elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the Fib-elements.
 *
 * @see store
 * @param stream the stream where this Fib-object should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if this Fib-object is stored, else false
 */
bool cConditionComparison::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	DEBUG_OUT_L3(<<this<<"->cConditionComparison::store()"<<endl);
	
	if ( ( pFirstSubFunction == NULL ) || ( pSecondSubFunction == NULL ) ){
		//a subfunctions is missing -> can't store
		return false;
	}
	
	//write the bits for the prefix 0x01
	const char cTypeBit = getTypeBit();
	const bool bPrefixStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
		&cTypeBit, 4 );
	if ( ! bPrefixStored ){
		return false;
	}
	//store the subfunction
	const bool bFirstSubFunctionStored =
		pFirstSubFunction->store( stream, cRestBits, uiRestBitPosition );
	if ( ! bFirstSubFunctionStored ){
		return false;
	}
	return pSecondSubFunction->store( stream, cRestBits, uiRestBitPosition );
}


/**
 * This method stores this condition in the XML-format into the
 * given stream.
 * Variables should have ther number as ther value.
 *
 * @param stream the stream where this conditionshould be
 * 	stored to
 * @return true if this condition is stored, else false
 */
bool cConditionComparison::storeXml( ostream & stream ) const{
	
	DEBUG_OUT_L3(<<this<<"->cConditionComparison::storeXml()"<<endl);
	
	bool bStoreSucessful = true;
	//store the unserfunction
	stream<<"<"<<getConditionName()<<">"<<endl;
	
	if ( pFirstSubFunction != NULL ){
		//store the first subfunction
		bStoreSucessful = pFirstSubFunction->storeXml( stream );
	}else{//ther no first subfunction
		bStoreSucessful = false;
	}
	if ( pSecondSubFunction != NULL ){
		//store the second subfunction
		bStoreSucessful &= pSecondSubFunction->storeXml( stream );
	}else{//ther no second subfunction
		bStoreSucessful = false;
	}
	stream<<"</"<<getConditionName()<<">"<<endl;
	return bStoreSucessful;
}


#ifdef FEATURE_EQUAL_FIB_OBJECT

/**
 * This method checks if the given Fib-object is equal to this fib
 * -object.
 * Variables can be others, but must be defined and used in equivalent
 * Fib-elements.
 *
 * @param condition the condition to which this condition should be equal
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
bool cConditionComparison::equalInternal( const cCondition & condition,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{
	
	if ( (& condition) == NULL ){
		//no other condition
		return false;
	}
	if ( getType() != condition.getType() ){
		return false;
	}
	//check if the first subfunction is equal
	cConditionComparison * pConditionTwoValue = ((cConditionComparison*)(& condition));
	if ( pFirstSubFunction == NULL ){
		if ( pConditionTwoValue->pFirstSubFunction != NULL ){
			return false;
		}//else ( pFirstSubFunction == pConditionTwoValue->pFirstSubFunction == NULL )
	}else{// ( pFirstSubFunction != NULL )
		if ( pConditionTwoValue->pFirstSubFunction == NULL ){
			return false;
		}//else
		if ( ! pFirstSubFunction->equalInternal( *(pConditionTwoValue->pFirstSubFunction),
				mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
			return false;
		}
	}
	
	//check if the second subfunction is equal
	if ( pSecondSubFunction == NULL ){
		if ( pConditionTwoValue->pSecondSubFunction != NULL ){
			return false;
		}//else ( pSecondSubFunction == pConditionTwoValue->pSecondSubFunction == NULL )
		return true;
	}//else ( pSecondSubFunction != NULL )
	if ( pConditionTwoValue->pSecondSubFunction == NULL ){
		return false;
	}//else
	return pSecondSubFunction->equalInternal( *(pConditionTwoValue->pSecondSubFunction),
		mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects );
}

#else //FEATURE_EQUAL_FIB_OBJECT

/**
 * This Method checks if the given condition is equal to this condition.
 *
 * @param condition the condition to compare with this condition
 * @return true if the given condition is equal to this condition, else false
 */
bool cConditionComparison::equal( const cCondition & condition ) const{
	
	if ( (& condition) == NULL ){
		//no other condition
		return false;
	}
	if ( getType() != condition.getType() ){
		return false;
	}
	//check if the first subfunction is equal
	cConditionComparison * pConditionTwoValue = ((cConditionComparison*)(& condition));
	if ( pFirstSubFunction == NULL ){
		if ( pConditionTwoValue->pFirstSubFunction != NULL ){
			return false;
		}//else ( pFirstSubFunction == pConditionTwoValue->pFirstSubFunction == NULL )
	}else{// ( pFirstSubFunction != NULL )
		if ( pConditionTwoValue->pFirstSubFunction == NULL ){
			return false;
		}//else
		if ( ! pFirstSubFunction->equal( *(pConditionTwoValue->pFirstSubFunction) ) ){
			return false;
		}
	}
	
	//check if the second subfunction is equal
	if ( pSecondSubFunction == NULL ){
		if ( pConditionTwoValue->pSecondSubFunction != NULL ){
			return false;
		}//else ( pSecondSubFunction == pConditionTwoValue->pSecondSubFunction == NULL )
		return true;
	}//else ( pSecondSubFunction != NULL )
	if ( pConditionTwoValue->pSecondSubFunction == NULL ){
		return false;
	}//else
	return pSecondSubFunction->equal( *(pConditionTwoValue->pSecondSubFunction) );
}

#endif //FEATURE_EQUAL_FIB_OBJECT



/**
 * @see pFirstSubFunction
 * @see setFirstSubFunction()
 * @return a pointer to the first function this condition contains (@see pSubFunction)
 */
cUnderFunction * cConditionComparison::getFirstSubFunction(){

	return pFirstSubFunction;
}


/**
 * @see pFirstSubFunction
 * @see setFirstSubFunction()
 * @return a pointer to the first function this condition contains (@see pSubFunction)
 */
const cUnderFunction * cConditionComparison::getFirstSubFunction() const{

	return pFirstSubFunction;
}


/**
 * This method sets the contained first function (@see pFirstSubFunction) to the
 * given condition pInSubFunction.
 * Beware: It (pInSubFunction) won't be copied.
 *
 * @see pFirstSubFunction
 * @see getFirstSubFunction()
 * @param pInSubFunction a pointer to the subfunction to set
 * @param bDeleteOld if true, delete the old subfunction from the memory
 * @return true if pInSubFunction function was set, else false
 */
bool cConditionComparison::setFirstSubFunction( cUnderFunction * pInSubFunction,
		bool bDeleteOld ){
	
	if ( pInSubFunction == NULL ){
		return false;
	}
	if ( pFirstSubFunction != NULL ){
		if ( bDeleteOld ){
			delete pFirstSubFunction;
		}
	}
	pFirstSubFunction = pInSubFunction;
	pFirstSubFunction->pSuperiorUnderFunction = NULL;
	pFirstSubFunction->setDefiningFibElement( getDefiningFibElement() );
	
	return true;
}


/**
 * This method sets the contained first function (@see pFirstSubFunction) to the
 * given condition pInSubFunction.
 * Beware: It (pInSubFunction) won't be copied.
 *
 * @see pFirstSubFunction
 * @see getFirstSubFunction()
 * @param pInSubFunction a pointer to the subfunction to set
 * @param bDeleteOld if true, delete the old subfunction from the memory
 * @return true if pInSubFunction function was set, else false
 */
bool cConditionComparison::setFirstSubFunction( const cUnderFunction & inSubFunction,
		bool bDeleteOld ){
	
	if ( (&inSubFunction) == NULL ){
		return false;
	}
	if ( pFirstSubFunction != NULL ){
		if ( bDeleteOld ){
			delete pFirstSubFunction;
		}
	}
	pFirstSubFunction = inSubFunction.clone( NULL, getDefiningFibElement() );
	
	return true;
}



/**
 * @see pSecondSubFunction
 * @see setSecondSubFunction()
 * @return a pointer to the second function this condition contains (@see pSubFunction)
 */
cUnderFunction * cConditionComparison::getSecondSubFunction(){

	return pSecondSubFunction;
}


/**
 * @see pSecondSubFunction
 * @see setSecondSubFunction()
 * @return a pointer to the second function this condition contains (@see pSubFunction)
 */
const cUnderFunction * cConditionComparison::getSecondSubFunction() const{

	return pSecondSubFunction;
}


/**
 * This method sets the contained second function (@see pSecondSubFunction) to the
 * given condition pInSubFunction.
 * Beware: It (pInSubFunction) won't be copied.
 *
 * @see pSecondSubFunction
 * @see getSecondSubFunction()
 * @param pInSubFunction a pointer to the subfunction to set
 * @param bDeleteOld if true, delete the old subfunction from the memory
 * @return true if pInSubFunction function was set, else false
 */
bool cConditionComparison::setSecondSubFunction( cUnderFunction * pInSubFunction,
		bool bDeleteOld ){
	
	if ( pInSubFunction == NULL ){
		return false;
	}
	if ( pSecondSubFunction != NULL ){
		if ( bDeleteOld ){
			delete pSecondSubFunction;
		}
	}
	pSecondSubFunction = pInSubFunction;
	pSecondSubFunction->pSuperiorUnderFunction = NULL;
	pSecondSubFunction->setDefiningFibElement( getDefiningFibElement() );
	
	return true;
}


/**
 * This method sets the contained second function (@see pSecondSubFunction) to the
 * given condition pInSubFunction.
 * Beware: It (pInSubFunction) won't be copied.
 *
 * @see pSecondSubFunction
 * @see getSecondSubFunction()
 * @param pInSubFunction a pointer to the subfunction to set
 * @param bDeleteOld if true, delete the old subfunction from the memory
 * @return true if pInSubFunction function was set, else false
 */
bool cConditionComparison::setSecondSubFunction( const cUnderFunction & inSubFunction,
		bool bDeleteOld ){
	
	if ( (&inSubFunction) == NULL ){
		return false;
	}
	if ( pSecondSubFunction != NULL ){
		if ( bDeleteOld ){
			delete pSecondSubFunction;
		}
	}
	pSecondSubFunction = inSubFunction.clone( NULL, getDefiningFibElement() );
	
	return true;
}















