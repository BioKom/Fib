/**
 * @class cConditionNot
 * file name: cConditionNot.cpp
 * @author Betti Oesterholz
 * @date 09.05.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a not condition.
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
 * This class represents a not condition.
 * This condition is allways the opposite of the contained condition.
 *
 */
/*
History:
09.05.2011  Oesterholz  created
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
*/


#include "cConditionNot.h"



using namespace fib;


/**
 * The constructor of the not condition.
 *
 * @param pInSubCondition a pointer to the condition, this condition
 * 	contains; Beware: it won't be copied.
 * @param pInSuperiorCondition the condition which contains the
 * 	new condition
 * @param pInDefiningFibElement the Fib-element which defines/ uses
 * 	the new condition
 */
cConditionNot::cConditionNot(  cCondition * pInSubCondition,
		cCondition * pInSuperiorCondition,
		cFibElement * pInDefiningFibElement ):
		cCondition( pInSuperiorCondition, pInDefiningFibElement ),
		pSubCondition( pInSubCondition ){
	
	if ( pSubCondition ){
		pSubCondition->pSuperiorCondition = this;
		pSubCondition->setDefiningFibElement( pDefiningFibElement );
	}
}

/**
 * The constructor of the not condition.
 *
 * @param inSubCondition a pointer to the condition, this condition
 * 	contains; Beware: it won't be copied.
 * @param pInSuperiorCondition the condition which contains the
 * 	new condition
 * @param pInDefiningFibElement the Fib-element which defines/ uses
 * 	the new condition
 */
cConditionNot::cConditionNot( const cCondition & inSubCondition,
		cCondition * pInSuperiorCondition,
		cFibElement * pInDefiningFibElement ):
		cCondition( pInSuperiorCondition, pInDefiningFibElement ),
		pSubCondition( NULL ){
	
	setSubCondition( inSubCondition );
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
cConditionNot::cConditionNot( const cConditionNot & condition,
		cCondition * pInSuperiorCondition,
		cFibElement *pInDefiningFibElement ):
		cCondition( condition, pInSuperiorCondition, pInDefiningFibElement ),
		pSubCondition( NULL ){
	
	setSubCondition( *(condition.getSubCondition()) );
}


/**
 * The destructor of the condition.
 */
cConditionNot::~cConditionNot(){
	
	if ( pSubCondition ){
		delete pSubCondition;
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
bool cConditionNot::isValid() const{
	
	if ( pSubCondition == NULL ){
		//no subconditions -> condition not valid
		return false;
	}
	return pSubCondition->isValid();
}


/**
 * This method checks if the given variable is used in this condition.
 *
 * @see cFibVariable
 * @param variable the variable to check if it is used
 * @return true if the variable is used, else false
 */
bool cConditionNot::isUsedVariable( const cFibVariable * variable ) const{

	if ( pSubCondition == NULL ){
		//no subconditions -> condition don't use variable
		return false;
	}
	return pSubCondition->isUsedVariable( variable );
}


/**
 * This method returns all variables used in this condition.
 *
 * @see cFibVariable
 * @return all variables used in this condition
 */
set<cFibVariable*> cConditionNot::getUsedVariables(){

	if ( pSubCondition == NULL ){
		//no subconditions -> condition don't use variables
		return set<cFibVariable*>();
	}
	return pSubCondition->getUsedVariables();
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
bool cConditionNot::replaceVariable( cFibVariable * variableOld,
		cFibVariable * variableNew ){
	
	if ( (variableOld == NULL) || (variableNew == NULL) ){
		return false;
	}
	if ( pSubCondition == NULL ){
		//no subconditions -> nothing to replace
		return true;
	}
	return pSubCondition->replaceVariable( variableOld, variableNew );
}


/**
 * Returns the value true of the condition.
 *
 * @return true
 */
bool cConditionNot::getValue() const{

	if ( pSubCondition == NULL ){
		//no subconditions
		return false;
	}
	return ( ! ( pSubCondition->getValue() ) );
}


/**
 * @return the number of conditions, a condition of this type has
 */
unsignedIntFib cConditionNot::getNumberOfConditions() const{
	//no subconditions
	return 1;
}


/**
 * @return the number of underfunctions, a condition of this type has
 */
unsignedIntFib cConditionNot::getNumberOfUnderFunctions() const{
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
void cConditionNot::setDefiningFibElement(
		cFibElement * pDefiningFibElement, bool bCheckDomains ){
	
	//set the defining fib -elements in both underfunctions
	if ( pSubCondition ){
		pSubCondition->setDefiningFibElement( pDefiningFibElement, bCheckDomains );
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
unsignedLongFib cConditionNot::getTimeNeed( unsignedLongFib lMaxTime ) const{

	if ( pSubCondition == NULL ){
		//no subconditions
		return 1;
	}
	if ( lMaxTime == 1 ){
		//max time reached
		return 1;
	}
	return 1 + pSubCondition->getTimeNeed( lMaxTime );
}

/**
 * This method evaluades the size of the Fib-object in bits in the
 * compressed file form.
 * The optionalpart field of point -elements will be ignored.
 *
 * @see store()
 * @return the size of the Fib-object in bits in the compressed form
 */
unsignedLongFib cConditionNot::getCompressedSize() const{

	if ( pSubCondition == NULL ){
		//no subconditions
		return 4;
	}
	return 4 + pSubCondition->getCompressedSize();
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
bool cConditionNot::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	DEBUG_OUT_L3(<<this<<"->cConditionNot::store()"<<endl);
	
	if ( pSubCondition == NULL ){
		//a subconditions is missing -> can't store
		return false;
	}
	
	//write the bits for the prefix 0x01
	const char cTypeBit = 0x01;
	const bool bPrefixStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
		&cTypeBit, 4 );
	if ( ! bPrefixStored ){
		return false;
	}
	//store the subcondition
	return pSubCondition->store( stream, cRestBits, uiRestBitPosition );
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
bool cConditionNot::storeXml( ostream & stream ) const{
	
	DEBUG_OUT_L3(<<this<<"->cConditionNot::storeXml()"<<endl);
	
	//store the unserfunction
	stream<<"<not>"<<endl;
	if ( pSubCondition == NULL ){
		//no subcondition
		stream<<"</not>";
		return false;
	}//else ther is an subcondition
	pSubCondition->storeXml( stream );
	stream<<"</not>"<<endl;
	return true;
}


/**
 * @return the type for the condition
 */
unsignedIntFib cConditionNot::getType() const{

	return CONDITION_NOT;
}


/**
 * @return the name for the condition
 */
string cConditionNot::getConditionName() const{

	return "not";
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
bool cConditionNot::equalInternal( const cCondition & condition,
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
	//check if the subcondition is equal
	cConditionNot * pConditionNot = ((cConditionNot*)(& condition));
	if ( pSubCondition == NULL ){
		if ( pConditionNot->pSubCondition != NULL ){
			return false;
		}//else ( pSubCondition == pConditionNot->pSubCondition == NULL )
		return true;
	}
	return pSubCondition->equalInternal( *(pConditionNot->pSubCondition),
				mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects );
}

#else //FEATURE_EQUAL_FIB_OBJECT

/**
 * This Method checks if the given condition is equal to this condition.
 *
 * @param condition the condition to compare with this condition
 * @return true if the given condition is equal to this condition, else false
 */
bool cConditionNot::equal( const cCondition & condition ) const{
	
	if ( (& condition) == NULL ){
		//no other condition
		return false;
	}
	if ( getType() != condition.getType() ){
		return false;
	}
	//check if the subcondition is equal
	cConditionNot * pConditionNot = ((cConditionNot*)(& condition));
	if ( pSubCondition == NULL ){
		if ( pConditionNot->pSubCondition != NULL ){
			return false;
		}//else ( pSubCondition == pConditionNot->pSubCondition == NULL )
		return true;
	}
	return pSubCondition->equal( *(pConditionNot->pSubCondition) );
}

#endif //FEATURE_EQUAL_FIB_OBJECT


/**
 * This method duplicates this whole condition.
 * subcondition of this condition are also cloned.
 *
 * @param pSuperiorCondition the condition which contains the cloned
 * 	condition
 * @param pInDefiningFibElement the Fib-element which defines/ uses
 * 	the cloned condition
 * @return the cloned/ duplicated condition
 */
cConditionNot * cConditionNot::clone(
		cCondition * pInSuperiorCondition,
		cFibElement *pInDefiningFibElement ) const{
	
	return new cConditionNot( *this, pInSuperiorCondition,
		pInDefiningFibElement );
}


/**
 * @see pSubCondition
 * @see setSubCondition()
 * @return a pointer to the condition this condition contains (@see pSubCondition)
 */
cCondition * cConditionNot::getSubCondition(){

	return pSubCondition;
}


/**
 * @see pSubCondition
 * @see setSubCondition()
 * @return a pointer to the condition this condition contains (@see pSubCondition)
 */
const cCondition * cConditionNot::getSubCondition() const{

	return pSubCondition;
}


/**
 * This method sets the contained condition (@see pSubCondition) to the
 * given condition pInSubCondition.
 * Beware: It (pInSubCondition) won't be copied.
 *
 * @see pSubCondition
 * @see getSubCondition()
 * @param pInSubCondition a pointer to the subcondition to set
 * @param bDeleteOld if true, delete the old subcondition from the memory
 * @return true if pInSubCondition condition was set, else false
 */
bool cConditionNot::setSubCondition( cCondition * pInSubCondition,
		bool bDeleteOld ){
	
	if ( pInSubCondition == NULL ){
		return false;
	}
	if ( pSubCondition != NULL ){
		if ( bDeleteOld ){
			delete pSubCondition;
		}else{//cut connections
			if ( pSubCondition->pSuperiorCondition == this ){
				pSubCondition->pSuperiorCondition = NULL;
			}
		}
	}
	pSubCondition = pInSubCondition;
	pSubCondition->pSuperiorCondition = this;
	pSubCondition->setDefiningFibElement( getDefiningFibElement() );
	
	return true;
}


/**
 * This method sets the contained condition (@see pSubCondition) to the
 * given condition pInSubCondition.
 *
 * @see pSubCondition
 * @see getSubCondition()
 * @param pInSubCondition the subcondition to set
 * @param bDeleteOld if true, delete the old subcondition from the memory
 * @return true if pInSubCondition condition was set, else false
 */
bool cConditionNot::setSubCondition( const cCondition & inSubCondition,
		bool bDeleteOld ){
	
	if ( (&inSubCondition) == NULL ){
		return false;
	}
	if ( pSubCondition != NULL ){
		if ( bDeleteOld ){
			delete pSubCondition;
		}else{//cut connections
			if ( pSubCondition->pSuperiorCondition == this ){
				pSubCondition->pSuperiorCondition = NULL;
			}
		}
	}
	pSubCondition = inSubCondition.clone( this, getDefiningFibElement() );
	
	return true;
}









