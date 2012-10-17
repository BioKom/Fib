/**
 * @class cConditionTwoValue
 * file name: cConditionTwoValue.cpp
 * @author Betti Oesterholz
 * @date 13.05.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a abstract condition with two subconditions.
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
 * This class represents a abstract condition with two subconditions.
 *
 */
/*
History:
13.05.2011  Oesterholz  created
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
*/


#include "cConditionTwoValue.h"



using namespace fib;


/**
 * The constructor of the two value condition.
 *
 * @param pInFirstSubCondition a pointer to the first condition, this condition
 * 	contains; Beware: It (pSubCondition) won't be copied.
 * 	@see pFirstSubCondition
 * @param pInSecondSubCondition a pointer to the second condition, this
 * 	condition contains; Beware: It (pSubCondition) won't be copied.
 * 	@see pSecondSubCondition
 * @param pInSuperiorCondition the condition which contains the
 * 	new condition
 * @param pInDefiningFibElement the Fib-element which defines/ uses
 * 	the new condition
 */
cConditionTwoValue::cConditionTwoValue( cCondition * pInFirstSubCondition,
		cCondition * pInSecondSubCondition,
		cCondition * pInSuperiorCondition,
		cFibElement * pInDefiningFibElement ):
		cCondition( pInSuperiorCondition, pInDefiningFibElement ),
		pFirstSubCondition( pInFirstSubCondition ),
		pSecondSubCondition( pInSecondSubCondition ){
	
	if ( pFirstSubCondition ){
		pFirstSubCondition->pSuperiorCondition = this;
		pFirstSubCondition->setDefiningFibElement( pDefiningFibElement );
	}
	if ( pSecondSubCondition ){
		pSecondSubCondition->pSuperiorCondition = this;
		pSecondSubCondition->setDefiningFibElement( pDefiningFibElement );
	}
}

/**
 * The constructor of the two value condition.
 *
 * @param inFirstSubCondition the first condition, this condition contains
 * 	@see pFirstSubCondition
 * @param inSecondSubCondition the second condition, this condition contains
 * 	@see pSecondSubCondition
 * @param pInSuperiorCondition the condition which contains the
 * 	new condition
 * @param pInDefiningFibElement the Fib-element which defines/ uses
 * 	the new condition
 */
cConditionTwoValue::cConditionTwoValue( const cCondition & inFirstSubCondition,
		const cCondition & inSecondSubCondition,
		cCondition * pInSuperiorCondition,
		cFibElement * pInDefiningFibElement ):
		cCondition( pInSuperiorCondition, pInDefiningFibElement ),
		pFirstSubCondition( NULL ), pSecondSubCondition( NULL ){
	
	setFirstSubCondition( inFirstSubCondition );
	setSecondSubCondition( inSecondSubCondition );
}


/**
 * The copy constructor of the condition.
 * This constructor will also copy the subconditions of the given
 * condition.
 *
 * @param condition the condition which to copy
 * @param pInSuperiorCondition the condition which contains the
 * 	new condition
 * @param pInDefiningFibElement the Fib-element which defines/ uses
 * 	the new condition
 */
cConditionTwoValue::cConditionTwoValue( const cConditionTwoValue & condition,
		cCondition * pInSuperiorCondition,
		cFibElement *pInDefiningFibElement ):
		cCondition( condition, pInSuperiorCondition, pInDefiningFibElement ),
		pFirstSubCondition( NULL ), pSecondSubCondition( NULL ){
	
	setFirstSubCondition( *(condition.getFirstSubCondition()) );
	setSecondSubCondition( *(condition.getSecondSubCondition()) );
}


/**
 * The destructor of the condition.
 */
cConditionTwoValue::~cConditionTwoValue(){
	
	if ( pFirstSubCondition ){
		delete pFirstSubCondition;
	}
	if ( pSecondSubCondition ){
		delete pSecondSubCondition;
	}
}


/**
 * This method returns if this condition is valid, else false.
 * All subcondition and underfunctions must be valid.
 * No condition should contain itself or should be contained in one
 * of its condition (no cycles allowed).
 *
 * @return true if this condition is valid, else false
 */
bool cConditionTwoValue::isValid() const{
	
	if ( pFirstSubCondition != NULL ){
		if ( ! pFirstSubCondition->isValid() ){
			//subconditions not valid -> condition not valid
			return false;
		}
	}else{
		//subconditions missing -> condition not valid
		return false;
	}
	if ( pSecondSubCondition != NULL ){
		if ( ! pSecondSubCondition->isValid() ){
			//subconditions not valid -> condition not valid
			return false;
		}
	}else{
		//subconditions missing -> condition not valid
		return false;
	}
	//all is Ok
	return true;
}


/**
 * This method checks if the given variable is used in this condition.
 *
 * @see cFibVariable
 * @param variable the variable to check if it is used
 * @return true if the variable is used, else false
 */
bool cConditionTwoValue::isUsedVariable( const cFibVariable * variable ) const{
	
	if ( pFirstSubCondition != NULL ){
		//no subconditions -> condition don't use variable
		if ( pFirstSubCondition->isUsedVariable( variable ) ){
			return true;
		}
	}
	if ( pSecondSubCondition != NULL ){
		//no subconditions -> condition don't use variable
		if ( pSecondSubCondition->isUsedVariable( variable ) ){
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
set<cFibVariable*> cConditionTwoValue::getUsedVariables(){
	
	set< cFibVariable * > setUsedVariables;
	if ( pFirstSubCondition != NULL ){
		//get used variables of first subcondition
		setUsedVariables = pFirstSubCondition->getUsedVariables();
		
	}
	if ( pSecondSubCondition != NULL ){
		//get used variables of second subcondition
		const set< cFibVariable * > setUsedVariablesInSecond =
			pSecondSubCondition->getUsedVariables();
		
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
bool cConditionTwoValue::replaceVariable( cFibVariable * variableOld,
		cFibVariable * variableNew ){
	
	if ( (variableOld == NULL) || (variableNew == NULL) ){
		return false;
	}
	bool bVariableReplaced = true;
	if ( pFirstSubCondition != NULL ){
		//replace variable in first subcondition
		bVariableReplaced = pFirstSubCondition->replaceVariable(
			variableOld, variableNew );
		
	}
	if ( pSecondSubCondition != NULL ){
		//replace variable in second subcondition
		bVariableReplaced &= pSecondSubCondition->replaceVariable(
			variableOld, variableNew );
	}
	
	return bVariableReplaced;
}



/**
 * @return the number of conditions, a condition of this type has
 */
unsignedIntFib cConditionTwoValue::getNumberOfConditions() const{
	//no subconditions
	return 2;
}


/**
 * @return the number of underfunctions, a condition of this type has
 */
unsignedIntFib cConditionTwoValue::getNumberOfUnderFunctions() const{
	//no underfunctions
	return 0;
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
void cConditionTwoValue::setDefiningFibElement(
		cFibElement * pDefiningFibElement, bool bCheckDomains ){
	
	//set the defining fib -elements in both underfunctions
	if ( pFirstSubCondition ){
		pFirstSubCondition->setDefiningFibElement( pDefiningFibElement, bCheckDomains );
	}
	if ( pSecondSubCondition ){
		pSecondSubCondition->setDefiningFibElement( pDefiningFibElement, bCheckDomains );
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
unsignedLongFib cConditionTwoValue::getTimeNeed( unsignedLongFib lMaxTime ) const{
	
	if ( lMaxTime == 0 ){
		
		unsignedLongFib ulTimeNeed = 1;
		if ( pFirstSubCondition != NULL ){
			//get time need for the first subcondition
			ulTimeNeed += pFirstSubCondition->getTimeNeed( lMaxTime );
		}
		if ( pSecondSubCondition != NULL ){
			//get time need for the second subcondition
			ulTimeNeed += pSecondSubCondition->getTimeNeed( lMaxTime );
		}
		return ulTimeNeed;
	}//else
	if ( lMaxTime == 1 ){
		//max time reached
		return 1;
	}
	unsignedLongFib ulTimeNeed = 1;
	
	if ( pFirstSubCondition != NULL ){
		//get time need for the first subcondition
		ulTimeNeed += pFirstSubCondition->getTimeNeed( lMaxTime );
		if ( lMaxTime <= ulTimeNeed ){
			//max time reached
			return lMaxTime;
		}
	}
	if ( pSecondSubCondition != NULL ){
		//get time need for the second subcondition
		ulTimeNeed += pSecondSubCondition->getTimeNeed( lMaxTime );
		
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
unsignedLongFib cConditionTwoValue::getCompressedSize() const{

	unsignedLongFib ulCompressedSize = 4;
	
	if ( pFirstSubCondition != NULL ){
		//get the compression size for the first subcondition
		ulCompressedSize += pFirstSubCondition->getCompressedSize();
	}
	if ( pSecondSubCondition != NULL ){
		//get the compression size for the second subcondition
		ulCompressedSize += pSecondSubCondition->getCompressedSize();
		
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
bool cConditionTwoValue::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	DEBUG_OUT_L3(<<this<<"->cConditionTwoValue::store()"<<endl);
	
	if ( ( pFirstSubCondition == NULL ) || ( pSecondSubCondition == NULL ) ){
		//a subconditions is missing -> can't store
		return false;
	}
	
	//write the bits for the prefix 0x01
	const char cTypeBit = getTypeBit();
	const bool bPrefixStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
		&cTypeBit, 4 );
	if ( ! bPrefixStored ){
		return false;
	}
	//store the subcondition
	const bool bFirstSubConditionStored =
		pFirstSubCondition->store( stream, cRestBits, uiRestBitPosition );
	if ( ! bFirstSubConditionStored ){
		return false;
	}
	return pSecondSubCondition->store( stream, cRestBits, uiRestBitPosition );
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
bool cConditionTwoValue::storeXml( ostream & stream ) const{
	
	DEBUG_OUT_L3(<<this<<"->cConditionTwoValue::storeXml()"<<endl);
	
	bool bStoreSucessful = true;
	//store the unserfunction
	stream<<"<"<<getConditionName()<<">"<<endl;
	
	if ( pFirstSubCondition != NULL ){
		//store the first subcondition
		bStoreSucessful = pFirstSubCondition->storeXml( stream );
	}else{//ther no first subcondition
		bStoreSucessful = false;
	}
	if ( pSecondSubCondition != NULL ){
		//store the second subcondition
		bStoreSucessful &= pSecondSubCondition->storeXml( stream );
	}else{//ther no second subcondition
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
bool cConditionTwoValue::equalInternal( const cCondition & condition,
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
	cConditionTwoValue * pConditionTwoValue = ((cConditionTwoValue*)(& condition));
	if ( pFirstSubCondition == NULL ){
		if ( pConditionTwoValue->pFirstSubCondition != NULL ){
			return false;
		}//else ( pFirstSubCondition == pConditionTwoValue->pFirstSubCondition == NULL )
	}else{// ( pFirstSubCondition != NULL )
		if ( pConditionTwoValue->pFirstSubCondition == NULL ){
			return false;
		}//else
		if ( ! pFirstSubCondition->equalInternal( *(pConditionTwoValue->pFirstSubCondition),
				mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
			return false;
		}
	}
	
	//check if the second subcondition is equal
	if ( pSecondSubCondition == NULL ){
		if ( pConditionTwoValue->pSecondSubCondition != NULL ){
			return false;
		}//else ( pSecondSubCondition == pConditionTwoValue->pSecondSubCondition == NULL )
		return true;
	}//else ( pSecondSubCondition != NULL )
	if ( pConditionTwoValue->pSecondSubCondition == NULL ){
		return false;
	}//else
	return pSecondSubCondition->equalInternal( *(pConditionTwoValue->pSecondSubCondition),
		mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects );
}

#else //FEATURE_EQUAL_FIB_OBJECT

/**
 * This Method checks if the given condition is equal to this condition.
 *
 * @param condition the condition to compare with this condition
 * @return true if the given condition is equal to this condition, else false
 */
bool cConditionTwoValue::equal( const cCondition & condition ) const{
	
	if ( (& condition) == NULL ){
		//no other condition
		return false;
	}
	if ( getType() != condition.getType() ){
		return false;
	}
	//check if the first subcondition is equal
	cConditionTwoValue * pConditionTwoValue = ((cConditionTwoValue*)(& condition));
	if ( pFirstSubCondition == NULL ){
		if ( pConditionTwoValue->pFirstSubCondition != NULL ){
			return false;
		}//else ( pFirstSubCondition == pConditionTwoValue->pFirstSubCondition == NULL )
	}else{
		if ( ! pFirstSubCondition->equal( *(pConditionTwoValue->pFirstSubCondition) ) ){
			return false;
		}
	}
	
	//check if the second subcondition is equal
	if ( pSecondSubCondition == NULL ){
		if ( pConditionTwoValue->pSecondSubCondition != NULL ){
			return false;
		}//else ( pSecondSubCondition == pConditionTwoValue->pSecondSubCondition == NULL )
		return true;
	}
	return pSecondSubCondition->equal( *(pConditionTwoValue->pSecondSubCondition) );
	
}

#endif //FEATURE_EQUAL_FIB_OBJECT


/**
 * @see pFirstSubCondition
 * @see setFirstSubCondition()
 * @return a pointer to the first condition this condition contains (@see pSubCondition)
 */
cCondition * cConditionTwoValue::getFirstSubCondition(){

	return pFirstSubCondition;
}


/**
 * @see pFirstSubCondition
 * @see setFirstSubCondition()
 * @return a pointer to the first condition this condition contains (@see pSubCondition)
 */
const cCondition * cConditionTwoValue::getFirstSubCondition() const{

	return pFirstSubCondition;
}


/**
 * This method sets the contained first condition (@see pFirstSubCondition) to the
 * given condition pInSubCondition.
 * Beware: It (pInSubCondition) won't be copied.
 *
 * @see pFirstSubCondition
 * @see getFirstSubCondition()
 * @param pInSubCondition a pointer to the subcondition to set
 * @param bDeleteOld if true, delete the old subcondition from the memory
 * @return true if pInSubCondition condition was set, else false
 */
bool cConditionTwoValue::setFirstSubCondition( cCondition * pInSubCondition,
		bool bDeleteOld ){
	
	if ( pInSubCondition == NULL ){
		return false;
	}
	if ( pFirstSubCondition != NULL ){
		if ( bDeleteOld ){
			delete pFirstSubCondition;
		}else{//cut connections
			if ( pFirstSubCondition->pSuperiorCondition == this ){
				pFirstSubCondition->pSuperiorCondition = NULL;
			}
		}
	}
	pFirstSubCondition = pInSubCondition;
	pFirstSubCondition->pSuperiorCondition = this;
	pFirstSubCondition->setDefiningFibElement( getDefiningFibElement() );
	
	return true;
}


/**
 * This method sets the contained first condition (@see pFirstSubCondition) to the
 * given condition pInSubCondition.
 * Beware: It (pInSubCondition) won't be copied.
 *
 * @see pFirstSubCondition
 * @see getFirstSubCondition()
 * @param pInSubCondition a pointer to the subcondition to set
 * @param bDeleteOld if true, delete the old subcondition from the memory
 * @return true if pInSubCondition condition was set, else false
 */
bool cConditionTwoValue::setFirstSubCondition( const cCondition & inSubCondition,
		bool bDeleteOld ){
	
	if ( (&inSubCondition) == NULL ){
		return false;
	}
	if ( pFirstSubCondition != NULL ){
		if ( bDeleteOld ){
			delete pFirstSubCondition;
		}else{//cut connections
			if ( pFirstSubCondition->pSuperiorCondition == this ){
				pFirstSubCondition->pSuperiorCondition = NULL;
			}
		}
	}
	pFirstSubCondition = inSubCondition.clone( this, getDefiningFibElement() );
	
	return true;
}



/**
 * @see pSecondSubCondition
 * @see setSecondSubCondition()
 * @return a pointer to the second condition this condition contains (@see pSubCondition)
 */
cCondition * cConditionTwoValue::getSecondSubCondition(){

	return pSecondSubCondition;
}


/**
 * @see pSecondSubCondition
 * @see setSecondSubCondition()
 * @return a pointer to the second condition this condition contains (@see pSubCondition)
 */
const cCondition * cConditionTwoValue::getSecondSubCondition() const{

	return pSecondSubCondition;
}


/**
 * This method sets the contained second condition (@see pSecondSubCondition) to the
 * given condition pInSubCondition.
 * Beware: It (pInSubCondition) won't be copied.
 *
 * @see pSecondSubCondition
 * @see getSecondSubCondition()
 * @param pInSubCondition a pointer to the subcondition to set
 * @param bDeleteOld if true, delete the old subcondition from the memory
 * @return true if pInSubCondition condition was set, else false
 */
bool cConditionTwoValue::setSecondSubCondition( cCondition * pInSubCondition,
		bool bDeleteOld ){
	
	if ( pInSubCondition == NULL ){
		return false;
	}
	if ( pSecondSubCondition != NULL ){
		if ( bDeleteOld ){
			delete pSecondSubCondition;
		}else{//cut connections
			if ( pSecondSubCondition->pSuperiorCondition == this ){
				pSecondSubCondition->pSuperiorCondition = NULL;
			}
		}
	}
	pSecondSubCondition = pInSubCondition;
	pSecondSubCondition->pSuperiorCondition = this;
	pSecondSubCondition->setDefiningFibElement( getDefiningFibElement() );
	
	return true;
}


/**
 * This method sets the contained second condition (@see pSecondSubCondition) to the
 * given condition pInSubCondition.
 * Beware: It (pInSubCondition) won't be copied.
 *
 * @see pSecondSubCondition
 * @see getSecondSubCondition()
 * @param pInSubCondition a pointer to the subcondition to set
 * @param bDeleteOld if true, delete the old subcondition from the memory
 * @return true if pInSubCondition condition was set, else false
 */
bool cConditionTwoValue::setSecondSubCondition( const cCondition & inSubCondition,
		bool bDeleteOld ){
	
	if ( (&inSubCondition) == NULL ){
		return false;
	}
	if ( pSecondSubCondition != NULL ){
		if ( bDeleteOld ){
			delete pSecondSubCondition;
		}else{//cut connections
			if ( pSecondSubCondition->pSuperiorCondition == this ){
				pSecondSubCondition->pSuperiorCondition = NULL;
			}
		}
	}
	pSecondSubCondition = inSubCondition.clone( this, getDefiningFibElement() );
	
	return true;
}















