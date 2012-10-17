/**
 * @class cCondition
 * file name: cCondition.cpp
 * @author Betti Oesterholz
 * @date 29.04.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a basic Fib-condition.
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
 * This file contains the basisclass of all Fib-condition. It's not
 * possible to create instances from this class.
 * Conditions are used in Fib-elements, especialy if-elements, to
 * represent logical conditions such like "not" or the "and" condition.
 *
 */
/*
History:
29.04.2011  Oesterholz  created
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
18.04.2012  Oesterholz  Bugfix: replace FirstChild()->ToElement() with
	FirstChildElement()
*/


#include "cCondition.h"
#include "cFibElement.h"
#include "cTypeVariable.h"


#include "cConditionTrue.h"
#include "cConditionFalse.h"
#include "cConditionNot.h"
#include "cConditionOr.h"
#include "cConditionAnd.h"
#include "cConditionXor.h"
#include "cConditionEqualInteger.h"
#include "cConditionLower.h"
#include "cConditionGreater.h"
#include "cUnderFunction.h"


using namespace fib;


/**
 * The constructor of the condition.
 *
 * @param pInSuperiorCondition the condition which contains
 * @param pInDefiningFibElement the Fib-element which defines/ uses
 * 	the new condition
 */
cCondition::cCondition( cCondition * pInSuperiorCondition,
		cFibElement * pInDefiningFibElement ):
		pSuperiorCondition( pInSuperiorCondition ),
		pDefiningFibElement( pInDefiningFibElement ){
	//nothing to do
}


/**
 * The copy constructor of the condition.
 *
 * @param condition the condition which to copy
 * @param pInSuperiorCondition the condition which contains
 * @param pInDefiningFibElement the Fib-element which defines/ uses
 */
cCondition::cCondition( const cCondition & condition,
		cCondition * pInSuperiorCondition,
		cFibElement *pInDefiningFibElement ):
		pSuperiorCondition( NULL ),
		pDefiningFibElement( condition.pDefiningFibElement ){
	
	if ( pInSuperiorCondition ){
		//if an superior condition is given take this
		pSuperiorCondition = pInSuperiorCondition;
	}
	if ( pInDefiningFibElement ){
		//if an defining Fib-element is given take this
		pDefiningFibElement = pInDefiningFibElement;
	}
}


/**
 * The destructor of the condition.
 */
cCondition::~cCondition(){

	//nothing to do
}


/**
 * @return the Fib-element which defines/ uses this condition or
 * 	a Nullpointer NULL if non such Fib-element exists
 */
cFibElement * cCondition::getDefiningFibElement( ) const{

	DEBUG_OUT_L3(<<this<<"->cCondition::getDefiningFibElement()="<<pDefiningFibElement<<endl);
	
	return pDefiningFibElement;
}


/**
 * @return the superior condition to this or NULL, if non such
 * 	exists (the superior condition is the condition, which
 * 	contains this condition)
 */
cCondition * cCondition::getSuperiorCondition() const{

	return pSuperiorCondition;
}


/**
 * Sets the Fib-element which defines/ uses this condition.
 * If the given pointer is the nullpointer (standardvalue), no
 * Fib-element defines this condition.
 *
 * @param definingFibElement a pointer to the Fib-element which
 * 	defines/ uses this condition
 * @param bCheckDomains getthe domains of the defining element and
 * 	check the conditionelements with it
 */
void cCondition::setDefiningFibElement( cFibElement *fibElement,
		bool bCheckDomains ){

	DEBUG_OUT_L3(<<this<<"->cCondition::setDefiningFibElement( "<< fibElement <<", "<<bCheckDomains<<" )"<<endl);
	
	pDefiningFibElement = fibElement;
}


/**
 * This method restores a condition in the XML -format from an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node wher the condition is stored in
 * @param outStatus an integervalue with the errorvalue
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 * @param liDefinedVariables a list with the defined variables for the
 * 	to restore Fib-element, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 * @param pInSuperiorCondition the condition which contains the
 * 	to restore condition
 * @param pInDefiningFibElement the Fib-element which defines/ uses
 * 	the to restore condition
 * @return the pointers to the restored condition, if non could be restored
 * 	the returned pointer is NULL
 */
cCondition * cCondition::restoreXml( const TiXmlElement * pXmlElement,
		intFib & outStatus, list<cFibVariable*> & liDefinedVariables,
		cCondition * pInSuperiorCondition,
		cFibElement *pInDefiningFibElement ){

	if ( pXmlElement == NULL ){
		//Error: nothing to load
		outStatus = -1;
		return NULL;
	}
	cCondition * pConditionRestored = NULL;
	
	string szElementType( pXmlElement->Value() );
	
	intFib iReturnValue = 0;
	if ( szElementType == "false" ){
		pConditionRestored = new cConditionFalse( pInSuperiorCondition, pInDefiningFibElement );
		
	}else if ( szElementType == "true" ){
		pConditionRestored = new cConditionTrue( pInSuperiorCondition, pInDefiningFibElement );
		
	}else if ( szElementType == "not" ){
		pConditionRestored = new cConditionNot( NULL, pInSuperiorCondition, pInDefiningFibElement );
		
		//restore the subconditions of the condition
		const TiXmlElement * pXmlElementSubCon = NULL;
		if ( pXmlElement->FirstChild() == NULL ){
			//Error: no subcondition
			outStatus = -1;
			return pConditionRestored;
		}
		pXmlElementSubCon = pXmlElement->FirstChildElement();
		
		cCondition * pSubConditionRestored =
			restoreXml( pXmlElementSubCon, outStatus, liDefinedVariables,
				pConditionRestored, pInDefiningFibElement );
		
		((cConditionNot*)pConditionRestored)->setSubCondition(
			pSubConditionRestored );
		
	}else if ( ( szElementType == "or" ) || ( szElementType == "and" ) ||
			( szElementType == "xor" ) ){
		
		if ( szElementType == "or" ){
			pConditionRestored = new cConditionOr( NULL, NULL, pInSuperiorCondition, pInDefiningFibElement );
		}else if ( szElementType == "and" ){
			pConditionRestored = new cConditionAnd( NULL, NULL, pInSuperiorCondition, pInDefiningFibElement );
		}else if ( szElementType == "xor" ){
			pConditionRestored = new cConditionXor( NULL, NULL, pInSuperiorCondition, pInDefiningFibElement );
		}
		//restore the subconditions of the condition
		const TiXmlElement * pXmlElementSubCon = NULL;
		if ( pXmlElement->FirstChild() == NULL ){
			//Error: no subcondition
			outStatus = -1;
			return pConditionRestored;
		}
		pXmlElementSubCon = pXmlElement->FirstChildElement();
		
		cCondition * pSubConditionRestored =
			restoreXml( pXmlElementSubCon, outStatus, liDefinedVariables,
				pConditionRestored, pInDefiningFibElement );
		
		((cConditionTwoValue*)pConditionRestored)->setFirstSubCondition(
			pSubConditionRestored );
		
		if ( outStatus < 0 ){
			return pConditionRestored;
		}
		pXmlElementSubCon = pXmlElementSubCon->NextSiblingElement();
		if ( pXmlElementSubCon == NULL ){
			//Error: no second underfunctions
			outStatus = -1;
			return pConditionRestored;
		}
		
		pSubConditionRestored =
			restoreXml( pXmlElementSubCon, outStatus, liDefinedVariables,
				pConditionRestored, pInDefiningFibElement );
		
		((cConditionTwoValue*)pConditionRestored)->setSecondSubCondition(
			pSubConditionRestored );
		
	}else if ( ( szElementType == "eqInt" ) || ( szElementType == "lo" ) ||
			( szElementType == "gr" ) ){//load comparison condition
		
		if ( szElementType == "eqInt" ){
			pConditionRestored = new cConditionEqualInteger( NULL, NULL, pInSuperiorCondition, pInDefiningFibElement );
		}else if ( szElementType == "lo" ){
			pConditionRestored = new cConditionLower( NULL, NULL, pInSuperiorCondition, pInDefiningFibElement );
		}else if ( szElementType == "gr" ){
			pConditionRestored = new cConditionGreater( NULL, NULL, pInSuperiorCondition, pInDefiningFibElement );
		}
		//restore the subconditions of the condition
		const TiXmlElement * pXmlElementSubFun = NULL;
		if ( pXmlElement->FirstChild() == NULL ){
			//Error: no subcondition
			outStatus = -1;
			return pConditionRestored;
		}
		pXmlElementSubFun = pXmlElement->FirstChildElement();
		
		cUnderFunction * pSubFunctionRestored =
			cUnderFunction::restoreXml( pXmlElementSubFun, outStatus, liDefinedVariables,
				NULL, pInDefiningFibElement );
		
		((cConditionComparison*)pConditionRestored)->setFirstSubFunction(
			pSubFunctionRestored );
		
		if ( outStatus < 0 ){
			return pConditionRestored;
		}
		pXmlElementSubFun = pXmlElementSubFun->NextSiblingElement();
		if ( pXmlElementSubFun == NULL ){
			//Error: no second underfunctions
			outStatus = -1;
			return pConditionRestored;
		}
		
		pSubFunctionRestored =
			cUnderFunction::restoreXml( pXmlElementSubFun, outStatus, liDefinedVariables,
				NULL, pInDefiningFibElement );
		
		((cConditionComparison*)pConditionRestored)->setSecondSubFunction(
			pSubFunctionRestored );
	
	}else{//Warning: no conditions to restore
		iReturnValue = 2;
	}//TODO more conditions
	
	if ( iReturnValue < 0 ){
		outStatus = iReturnValue;
	}else if ( (iReturnValue != 0) && (outStatus == 0) ){
		outStatus = iReturnValue;
	}
	return pConditionRestored;
}


/**
 * This method restores a condition from a bitstream, wher it is
 * stored in the compressed Fib-format.
 *
 * @see store
 * @param iBitStream the stream where the condition is stored in,
 * 	because the stream is an cReadBits, any number of bits can be
 * 	readed from it
 * @param outStatus an integervalue with the errorvalue
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 * @param liDefinedVariables a list with the defined variables for the
 * 	to restore Fib-element, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 * @param pInDomainValue the domain for value conditions
 * @param pInDomainVariable the domain for variables
 * @param pInSuperiorCondition the condition which contains the
 * 	to restore condition
 * @param pInDefiningFibElement the Fib-element which defines/ uses
 * 	the to restore condition
 * @return a pointer to the restored condition or NULL
 */
cCondition * cCondition::restore( cReadBits & iBitStream,
		intFib & outStatus, list<cFibVariable*> & liDefinedVariables,
		const cDomainSingle * pInDomainValue, const cDomainSingle * pInDomainVariable,
		cCondition * pInSuperiorCondition,
		cFibElement *pInDefiningFibElement ){

	DEBUG_OUT_L2(<<"cCondition::restore()"<<endl);
	
	if ( ! iBitStream.getStream()->good() ){
		//Error: nothing to load
		outStatus = -1;
		return NULL;
	}
	cCondition * pConditionRestored = NULL;
	
	//read the domainname
	char cConditionName = 0x00;
	unsigned int uiBitsRead = iBitStream.readBits( &cConditionName, 4 );
	if ( ! iBitStream.getStream()->good() ){
		outStatus = -2;
		return NULL;
	}
	if ( uiBitsRead != 4 ){
		outStatus = -2;
		DEBUG_OUT_EL2(<<"Error: "<<uiBitsRead<<" bits read, but should be 4"<<endl);
		return NULL;
	}
	/*clear bits not needed for the condition*/
	char cConditionNamePure = cConditionName & 0x0F;

	intFib iReturnValue = 0;
	if ( cConditionNamePure == 0x00 ){// load condition false
		DEBUG_OUT_L2(<<"cCondition::restoring cConditionFalse"<<endl);
		pConditionRestored = new cConditionFalse( pInSuperiorCondition, pInDefiningFibElement );
		
	}else if ( cConditionNamePure == 0x0F ){// load condition true
		DEBUG_OUT_L2(<<"cCondition::restoring cConditionTrue"<<endl);
		pConditionRestored = new cConditionTrue( pInSuperiorCondition, pInDefiningFibElement );
	
	}else if ( cConditionNamePure == 0x01 ){// load condition not
		pConditionRestored = new cConditionNot( NULL, pInSuperiorCondition, pInDefiningFibElement );
		
		cCondition * pSubConditionRestored =
			restore( iBitStream, outStatus, liDefinedVariables, pInDomainValue,
				pInDomainVariable, pConditionRestored, pInDefiningFibElement );
		
		((cConditionNot*)pConditionRestored)->setSubCondition(
			pSubConditionRestored );
		
		
	}else if ( ( cConditionNamePure == 0x02  ) || ( cConditionNamePure == 0x03  ) ||
			( cConditionNamePure == 0x04  ) ){//load two subcondition condition
		
		if ( cConditionNamePure == 0x02 ){
			// load condition or
			pConditionRestored = new cConditionOr( NULL, NULL, pInSuperiorCondition, pInDefiningFibElement );
		}else if ( cConditionNamePure == 0x03 ){
			// load condition or
			pConditionRestored = new cConditionAnd( NULL, NULL, pInSuperiorCondition, pInDefiningFibElement );
		}else if ( cConditionNamePure == 0x04 ){
			// load condition or
			pConditionRestored = new cConditionXor( NULL, NULL, pInSuperiorCondition, pInDefiningFibElement );
		}
		
		cCondition * pSubConditionRestored =
			restore( iBitStream, outStatus, liDefinedVariables, pInDomainValue,
				pInDomainVariable, pConditionRestored, pInDefiningFibElement );
		
		((cConditionTwoValue*)pConditionRestored)->setFirstSubCondition(
			pSubConditionRestored );
		
		if ( outStatus < 0 ){
			return pConditionRestored;
		}
		pSubConditionRestored =
			restore( iBitStream, outStatus, liDefinedVariables, pInDomainValue,
				pInDomainVariable, pConditionRestored, pInDefiningFibElement );
		
		((cConditionTwoValue*)pConditionRestored)->setSecondSubCondition(
			pSubConditionRestored );
		
	}else if ( ( cConditionNamePure == 0x08  ) || ( cConditionNamePure == 0x09  ) ||
			( cConditionNamePure == 0x0A  ) ){//load comparison condition
		
		if ( cConditionNamePure == 0x08 ){
			// load condition or
			pConditionRestored = new cConditionEqualInteger( NULL, NULL, pInSuperiorCondition, pInDefiningFibElement );
		}else if ( cConditionNamePure == 0x09 ){
			// load condition or
			pConditionRestored = new cConditionLower( NULL, NULL, pInSuperiorCondition, pInDefiningFibElement );
		}else if ( cConditionNamePure == 0x0A ){
			// load condition or
			pConditionRestored = new cConditionGreater( NULL, NULL, pInSuperiorCondition, pInDefiningFibElement );
		}
		
		cUnderFunction * pSubFunctionRestored =
			cUnderFunction::restore( iBitStream, outStatus, liDefinedVariables, pInDomainValue,
				pInDomainVariable, NULL, pInDefiningFibElement );
		
		((cConditionComparison*)pConditionRestored)->setFirstSubFunction(
			pSubFunctionRestored );
		
		if ( outStatus < 0 ){
			return pConditionRestored;
		}
		pSubFunctionRestored =
			cUnderFunction::restore( iBitStream, outStatus, liDefinedVariables, pInDomainValue,
				pInDomainVariable, NULL, pInDefiningFibElement );
		
		((cConditionComparison*)pConditionRestored)->setSecondSubFunction(
			pSubFunctionRestored );
	
	}else{//Warning: no condition to restore
		iReturnValue = 2;
	}//TODO more conditions

	if ( iReturnValue < 0 ){
		outStatus = iReturnValue;
	}else if ( (iReturnValue != 0) && (outStatus == 0) ){
		outStatus = iReturnValue;
	}
	
	DEBUG_OUT_L2(<<"cCondition::restore() done (outStatus="<<outStatus<<")"<<endl);
	
	return pConditionRestored;
}



/**
 * This Method checks if the given condition is equal to this condition.
 *
 * @param condition the condition to compare with this condition
 * @return true if the given condition is equal to this condition, else false
 */
bool cCondition::operator==( const cCondition &condition ) const{

	return this->equal( condition );
}


/**
 * This Method checks if the given condition is not equal to this condition.
 *
 * @param condition the condition to compare with this condition
 * @return true if the given condition is not equal to this condition, else false
 */
bool cCondition::operator!=( const cCondition &condition ) const{

	return ! ( this->equal( condition ) );
}

#ifdef FEATURE_EQUAL_FIB_OBJECT

/**
 * This method checks if the given condition is equal to this condition.
 *
 * @param condition the condition to compare with this condition
 * @param bCheckExternalObjects if true the external objects of
 * 	cExtObject will be compared
 * @return true if the given condition is equal to this condition, else false
 */
bool cCondition::equal( const cCondition &condition,
		const bool bCheckExternalObjects ) const{
	
	map< const cRoot *, const cRoot * > mapEqualRootObjects;
	map< const cFibElement *, const cFibElement * > mapEqualDefinedVariables;
	
	return equalInternal( condition,
		mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects );
}

#endif //FEATURE_EQUAL_FIB_OBJECT









