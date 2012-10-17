/**
 * @class cConditionTrue
 * file name: cConditionTrue.cpp
 * @author Betti Oesterholz
 * @date 02.05.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a true condition.
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
 * This class represents a true condition.
 * This condition is allways true.
 *
 */
/*
History:
02.05.2011  Oesterholz  created
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
*/


#include "cConditionTrue.h"



using namespace fib;


/**
 * The constructor of the true condition.
 *
 * @param pInSuperiorCondition the condition which contains the
 * 	new condition
 * @param pInDefiningFibElement the Fib-element which defines/ uses
 * 	the new condition
 */
cConditionTrue::cConditionTrue( cCondition * pInSuperiorCondition,
		cFibElement * pInDefiningFibElement ):
		cCondition( pInSuperiorCondition, pInDefiningFibElement ){
	//nothing to do
}


/**
 * The copy constructor of the condition.
 *
 * @param condition the condition which to copy
 * @param pInSuperiorCondition the condition which contains the
 * 	new condition
 * @param pInDefiningFibElement the Fib-element which defines/ uses
 * 	the new condition
 */
cConditionTrue::cConditionTrue( const cConditionTrue & condition,
		cCondition * pInSuperiorCondition,
		cFibElement *pInDefiningFibElement ):
		cCondition( condition, pInSuperiorCondition, pInDefiningFibElement ){
	//nothing to do
}


/**
 * The destructor of the condition.
 */
cConditionTrue::~cConditionTrue(){
	//nothing to do
}


/**
 * This method returns if this condition is valid, else false.
 * All subcondition and underfunctions must be valid.
 * No condition should contain itself or should be contained in one
 * of its condition (no cycles allowed).
 *
 * @return true if this condition is valid, else false
 */
bool cConditionTrue::isValid() const{

	return true;
}


/**
 * This method checks if the given variable is used in this condition.
 *
 * @see cFibVariable
 * @param variable the variable to check if it is used
 * @return true if the variable is used, else false
 */
bool cConditionTrue::isUsedVariable( const cFibVariable * variable ) const{

	//no variables used
	return false;
}


/**
 * This method returns all variables used in this condition.
 *
 * @see cFibVariable
 * @return all variables used in this condition
 */
set<cFibVariable*> cConditionTrue::getUsedVariables(){

	//no variables used
	return set<cFibVariable*>();
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
bool cConditionTrue::replaceVariable( cFibVariable * variableOld,
		cFibVariable * variableNew ){
	//nothing to replace
	if ( (variableOld == NULL) || (variableNew == NULL) ){
		return false;
	}
	return true;
}


/**
 * Returns the value true of the condition.
 *
 * @return true
 */
bool cConditionTrue::getValue() const{

	return true;
}


/**
 * @return the number of conditions, a condition of this type has
 */
unsignedIntFib cConditionTrue::getNumberOfConditions() const{
	//no subconditions
	return 0;
}


/**
 * @return the number of underfunctions, a condition of this type has
 */
unsignedIntFib cConditionTrue::getNumberOfUnderFunctions() const{
	//no underfunctions
	return 0;
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
unsignedLongFib cConditionTrue::getTimeNeed( unsignedLongFib lMaxTime ) const{

	return 1;
}

/**
 * This method evaluades the size of the Fib-object in bits in the
 * compressed file form.
 * The optionalpart field of point -elements will be ignored.
 *
 * @see store()
 * @return the size of the Fib-object in bits in the compressed form
 */
unsignedLongFib cConditionTrue::getCompressedSize() const{

	return 4;
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
bool cConditionTrue::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	DEBUG_OUT_L3(<<this<<"->cConditionTrue::store()"<<endl);
	
	//write the bits for the prefix 0F
	const char cTypeBit = 0x0F;
	return nBitStream::store( stream, cRestBits, uiRestBitPosition,
		&cTypeBit, 4 );
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
bool cConditionTrue::storeXml( ostream & stream ) const{
	
	DEBUG_OUT_L3(<<this<<"->cConditionTrue::storeXml()"<<endl);
	
	//store the unserfunction
	stream<<"<true/>"<<endl;

	return true;
}


/**
 * @return the type for the condition
 */
unsignedIntFib cConditionTrue::getType() const{

	return CONDITION_TRUE;
}


/**
 * @return the name for the condition
 */
string cConditionTrue::getConditionName() const{

	return "true";
}


#ifdef FEATURE_EQUAL_FIB_OBJECT

/**
 * This Method checks if the given variable is equal to this variable.
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
 * @return true if the given variable is equal to this variable, else false
 */
bool cConditionTrue::equalInternal( const cCondition & condition,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{
	
	if ( (& condition) == NULL ){
		return false;
	}
	return getType() == condition.getType();
}

#else //FEATURE_EQUAL_FIB_OBJECT

/**
 * This Method checks if the given condition is equal to this condition.
 *
 * @param condition the condition to compare with this condition
 * @return true if the given condition is equal to this condition, else false
 */
bool cConditionTrue::equal( const cCondition & condition ) const{
	
	if ( (& condition) == NULL ){
		return false;
	}
	return getType() == condition.getType();
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
cConditionTrue * cConditionTrue::clone(
		cCondition * pInSuperiorCondition,
		cFibElement *pInDefiningFibElement ) const{
	
	return new cConditionTrue( *this, pInSuperiorCondition,
		pInDefiningFibElement );
}











