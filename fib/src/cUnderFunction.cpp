/**
 * @class cUnderFunction
 * file name: cUnderFunction.cpp
 * @author Betti Oesterholz
 * @date 22.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a basic fib -subfunction.
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
 * This file contains the basisclass of all fib -subfunctions. It's not
 * possible to create instances from this class.
 * Underfunctions are used in fib -elements, especialy functions, to
 * represent mathematical functions such like addition or the maximum
 * function.
 *
 */
/*
History:
22.04.2010  Oesterholz  created
23.06.2011  Oesterholz  cFunctionIf and cFunctionRound included for restoring
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
01.04.2012  Oesterholz  DEBUG_RESTORE_XML implemented
*/


#include "cUnderFunction.h"
#include "cFibElement.h"
#include "cTypeVariable.h"

#include "cFunctionValue.h"
#include "cFunctionVariable.h"

#include "cFunctionAdd.h"
#include "cFunctionSub.h"
#include "cFunctionMult.h"
#include "cFunctionDiv.h"
#include "cFunctionExp.h"
#include "cFunctionMin.h"
#include "cFunctionMax.h"

#include "cFunctionAbs.h"
#include "cFunctionSin.h"
#include "cFunctionLog.h"
#include "cFunctionArcsin.h"
#include "cFunctionRound.h"
#include "cFunctionIf.h"


using namespace fib;


/**
 * The constructor of the subfunction.
 *
 * @param pInSuperiorUnderFunction the subfunction which contains
 * @param pInDefiningFibElement the Fib -element which defines/ uses
 * 	the new subfunction
 */
cUnderFunction::cUnderFunction( cUnderFunction * pInSuperiorUnderFunction,
		cFibElement * pInDefiningFibElement ):
		pSuperiorUnderFunction( pInSuperiorUnderFunction ),
		pDefiningFibElement( pInDefiningFibElement ){
	//nothing to do
}


/**
 * The copy constructor of the subfunction.
 *
 * @param subfunction the subfunction which to copy
 * @param pInSuperiorUnderFunction the subfunction which contains
 * @param pInDefiningFibElement the Fib -element which defines/ uses
 */
cUnderFunction::cUnderFunction( const cUnderFunction & subfunction,
		cUnderFunction * pInSuperiorUnderFunction,
		cFibElement *pInDefiningFibElement ):
		pSuperiorUnderFunction( NULL ),
		pDefiningFibElement( subfunction.pDefiningFibElement ){
	
	if ( pInSuperiorUnderFunction ){
		//if an superior subfunction is given take this
		pSuperiorUnderFunction = pInSuperiorUnderFunction;
	}
	if ( pInDefiningFibElement ){
		//if an defining fib -element is given take this
		pDefiningFibElement = pInDefiningFibElement;
	}
}


/**
 * The destructor of the subfunction.
 */
cUnderFunction::~cUnderFunction(){

	//nothing to do
}


/**
 * Returns the type of the subfunction.
 * You have to delete the returned object after usage.
 *
 * @return the type of the subfunction
 */
cTypeElement * cUnderFunction::getElementType() const{

	return new cTypeUnderFunction();
}


/**
 * Returns a reference to the domain of the subfunction or
 * the nullpointer NULL if no domain is defined for the subfunction.
 * If the nullpointer NULL is returned the standarddomain is valid for the
 * subfunction.
 *
 * @return a reference to the subfunctiondomain of the subfunction
 */
cDomainSingle * cUnderFunction::getDomain() const{

	DEBUG_OUT_L3(<<this<<"->cUnderFunction::getDomain()"<<endl);
	
	if ( pDefiningFibElement == NULL ){
		//can't get enviroment/ no enviroment -> return standard domain
		return NULL;
	}
	
	/*get the domain for the type of the vector*/
	cDomains validDomains = pDefiningFibElement->getValidDomains();
	
	cTypeElement * typeElement = getElementType();
	cDomain * domain = validDomains.getDomainForElement( *typeElement );
	delete typeElement;
	
	if ( domain ){
		return (cDomainSingle*)domain;
	}//else no domain in root -elements -> return NULL
	return NULL;
}


/**
 * Returns a reference to the value domain of the subfunction or
 * the nullpointer NULL if no value domain is defined for the subfunction.
 * If the nullpointer NULL is returned the standarddomain is valid for the
 * subfunction.
 *
 * @return a reference to the definitionarea of the subfunction
 */
cDomainSingle * cUnderFunction::getValueDomain() const{

	DEBUG_OUT_L3(<<this<<"->cUnderFunction::getValueDomain()"<<endl);
	
	if ( pDefiningFibElement == NULL ){
		//can't get enviroment/ no enviroment -> return standard domain
		return NULL;
	}
	
	/*get the domain for the type of the vector*/
	cDomains validValueDomains = pDefiningFibElement->getValidValueDomains();
	
	cTypeElement * typeElement = getElementType();
	cDomain * domain = validValueDomains.getDomainForElement( *typeElement );
	delete typeElement;

	if ( domain ){
		return (cDomainSingle*)domain;
	}//else no domain in root -elements -> return NULL
	return NULL;
}


/**
 * Returns a reference to the standard domain of the subfunction.
 * You have to delete the returned object after usage.
 *
 * @return a reference to the standard domain of the subfunction
 */
cDomainSingle * cUnderFunction::getStandardDomain() const{

	DEBUG_OUT_L3(<<this<<"->cUnderFunction::getStandardDomain()"<<endl);
	
	cTypeElement * typeElement = getElementType();
	cDomain * domainStandard = typeElement->getStandardDomain();
	delete typeElement;
	return (cDomainSingle*)domainStandard;
}


/**
 * Returns a reference to the domain for variables of the subfunction.
 * You have to delete the returned object after usage.
 *
 * @return a reference to the domain for variables of the subfunction
 */
cDomainSingle * cUnderFunction::getVariableDomain() const{
	
	DEBUG_OUT_L3(<<this<<"->cUnderFunction::getVariableDomain()"<<endl);
	
	cTypeVariable typeVariable;
	
	if ( pDefiningFibElement ){
		/*get the value domain for variables*/
		cDomains validDomains = pDefiningFibElement->getValidValueDomains();
	
		//return the positionvector domain
		cDomainSingle * variableDomain = (cDomainSingle*)
			validDomains.getDomainForElement( typeVariable );
	
		if ( variableDomain != NULL ){
			return variableDomain->clone();
		}//else
	}
	//return the standrad domain
	return (cDomainSingle*)typeVariable.getStandardDomain();
}


/**
 * @return the Fib -element which defines/ uses this subfunction or
 * 	a Nullpointer NULL if non such fib -element exists
 */
cFibElement * cUnderFunction::getDefiningFibElement( ) const{

	DEBUG_OUT_L3(<<this<<"->cUnderFunction::getDefiningFibElement()="<<pDefiningFibElement<<endl);
	
	return pDefiningFibElement;
}


/**
 * @return the superior subfunction to this or NULL, if non such
 * 	exists (the superior subfunction is the subfunction, which
 * 	contains this subfunction)
 */
cUnderFunction * cUnderFunction::getSuperiorUnderFunction() const{

	return pSuperiorUnderFunction;
}


/**
 * Sets the Fib -element which defines/ uses this subfunction.
 * If the given pointer is the nullpointer (standardvalue), no
 * Fib -element defines this subfunction.
 *
 * @param definingFibElement a pointer to the Fib -element which
 * 	defines/ uses this subfunction
 * @param bCheckDomains getthe domains of the defining element and
 * 	check the subfunctionelements with it
 */
void cUnderFunction::setDefiningFibElement( cFibElement *fibElement,
		bool bCheckDomains ){

	DEBUG_OUT_L3(<<this<<"->cUnderFunction::setDefiningFibElement( "<< fibElement <<", "<<bCheckDomains<<" )"<<endl);
	
	pDefiningFibElement = fibElement;
}


/**
 * This method restores a subfunction in the XML -format from an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node wher the subfunction is stored in
 * @param outStatus an integervalue with the errorvalue
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
 * 	to restore subfunction
 * @param pInDefiningFibElement the fib -element which defines/ uses
 * 	the to restore subfunction
 * @return the pointers to the restored subfunction, if non could be restored
 * 	the returned pointer is NULL
 */
cUnderFunction * cUnderFunction::restoreXml( const TiXmlElement * pXmlElement,
		intFib & outStatus, list<cFibVariable*> & liDefinedVariables,
		cUnderFunction * pInSuperiorFunction,
		cFibElement *pInDefiningFibElement ){

	if ( pXmlElement == NULL ){
		//Error: nothing to load
		outStatus = -1;
		return NULL;
	}
	cUnderFunction * pUnderFunctionRestored = NULL;
	
	const string szElementType( pXmlElement->Value() );
	
#ifdef DEBUG_RESTORE_XML
	printf( "Restoring subfunction \"%s\" (outStatus now %i)\n", szElementType.c_str(), outStatus );
#endif
	
	intFib iReturnValue = 0;
	if ( szElementType == "value" ){
		pUnderFunctionRestored = new cFunctionValue( pXmlElement, iReturnValue,
			pInSuperiorFunction, pInDefiningFibElement );
		
	}else if ( szElementType == "variable" ){
		pUnderFunctionRestored = new cFunctionVariable( pXmlElement, iReturnValue,
			liDefinedVariables, pInSuperiorFunction, pInDefiningFibElement );
		
	}else if ( szElementType == "log" ){
		pUnderFunctionRestored = new cFunctionLog( pXmlElement, iReturnValue,
			liDefinedVariables, pInSuperiorFunction, pInDefiningFibElement );
		
	}else if ( szElementType == "abs" ){
		pUnderFunctionRestored = new cFunctionAbs( pXmlElement, iReturnValue,
			liDefinedVariables, pInSuperiorFunction, pInDefiningFibElement );
		
	}else if ( szElementType == "sin" ){
		pUnderFunctionRestored = new cFunctionSin( pXmlElement, iReturnValue,
			liDefinedVariables, pInSuperiorFunction, pInDefiningFibElement );
		
	}else if ( szElementType == "round" ){
		pUnderFunctionRestored = new cFunctionRound( pXmlElement, iReturnValue,
			liDefinedVariables, pInSuperiorFunction, pInDefiningFibElement );
		
	}else if ( szElementType == "arcsin" ){
		pUnderFunctionRestored = new cFunctionArcsin( pXmlElement, iReturnValue,
			liDefinedVariables, pInSuperiorFunction, pInDefiningFibElement );
		
	}else if ( szElementType == "add" ){
		pUnderFunctionRestored = new cFunctionAdd( pXmlElement, iReturnValue,
			liDefinedVariables, pInSuperiorFunction, pInDefiningFibElement );
		
	}else if ( szElementType == "sub" ){
		pUnderFunctionRestored = new cFunctionSub( pXmlElement, iReturnValue,
			liDefinedVariables, pInSuperiorFunction, pInDefiningFibElement );
		
	}else if ( szElementType == "mult" ){
		pUnderFunctionRestored = new cFunctionMult( pXmlElement, iReturnValue,
			liDefinedVariables, pInSuperiorFunction, pInDefiningFibElement );
		
	}else if ( szElementType == "div" ){
		pUnderFunctionRestored = new cFunctionDiv( pXmlElement, iReturnValue,
			liDefinedVariables, pInSuperiorFunction, pInDefiningFibElement );
		
	}else if ( szElementType == "exp" ){
		pUnderFunctionRestored = new cFunctionExp( pXmlElement, iReturnValue,
			liDefinedVariables, pInSuperiorFunction, pInDefiningFibElement );
		
	}else if ( szElementType == "min" ){
		pUnderFunctionRestored = new cFunctionMin( pXmlElement, iReturnValue,
			liDefinedVariables, pInSuperiorFunction, pInDefiningFibElement );
		
	}else if ( szElementType == "max" ){
		pUnderFunctionRestored = new cFunctionMax( pXmlElement, iReturnValue,
			liDefinedVariables, pInSuperiorFunction, pInDefiningFibElement );
		
	}else if ( szElementType == "if" ){
		pUnderFunctionRestored = new cFunctionIf( pXmlElement, iReturnValue,
			liDefinedVariables, pInSuperiorFunction, pInDefiningFibElement );
	
	}else{//Warning: no subfunctions to restore
		iReturnValue = 2;
	}//TODO more subfunctions
	
	if ( iReturnValue < 0 ){
		outStatus = iReturnValue;
#ifdef DEBUG_RESTORE_XML
		printf( "Error while restoring subfunction; outStatus now %i\n", outStatus );
#endif
	}else if ( (iReturnValue != 0) && (outStatus == 0) ){
		outStatus = iReturnValue;
#ifdef DEBUG_RESTORE_XML
		printf( "Warining while restoring subfunction; outStatus now %i\n", outStatus );
#endif
	}
	return pUnderFunctionRestored;
}


/**
 * This method restores a subfunction from a bitstream, wher it is
 * stored in the compressed fib -format.
 *
 * @see store
 * @param iBitStream the stream where the subfunction is stored in,
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
 * 	to restore fib -element, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 * @param pInDomainValue the domain for value subfunctions
 * @param pInDomainVariable the domain for variables
 * @param pInSuperiorFunction the subfunction which contains the
 * 	to restore subfunction
 * @param pInDefiningFibElement the fib -element which defines/ uses
 * 	the to restore subfunction
 * @return a pointer to the restored subfunction or NULL
 */
cUnderFunction * cUnderFunction::restore( cReadBits & iBitStream,
		intFib & outStatus, list<cFibVariable*> & liDefinedVariables,
		const cDomainSingle * pInDomainValue, const cDomainSingle * pInDomainVariable,
		cUnderFunction * pInSuperiorFunction,
		cFibElement *pInDefiningFibElement ){

	DEBUG_OUT_L2(<<"cUnderFunction::restore()"<<endl);
	
	if ( ! iBitStream.getStream()->good() ){
		//Error: nothing to load
		outStatus = -1;
		return NULL;
	}
	cUnderFunction * pUnderFunctionRestored = NULL;
	
	//read the domainname
	char cFunctionName = 0x00;
	unsigned int uiBitsRead = iBitStream.readBits( &cFunctionName, 2 );
	if ( ! iBitStream.getStream()->good() ){
		outStatus = -2;
		return NULL;
	}
	if ( uiBitsRead != 2 ){
		outStatus = -2;
		DEBUG_OUT_EL2(<<"Error: "<<uiBitsRead<<" bits read, but should be 2"<<endl);
		return NULL;
	}
	/*clear bits not needed for the function ary type*/
	char cFunctionNamePure = cFunctionName & 0x03;

	intFib iReturnValue = 0;
	if ( cFunctionNamePure == 0x00 ){// 0'ary value subfunction
		DEBUG_OUT_L2(<<"cUnderFunction::restoring cFunctionValue"<<endl);
		pUnderFunctionRestored = new cFunctionValue( iBitStream, iReturnValue,
			pInDomainValue, pInSuperiorFunction, pInDefiningFibElement );
		
	}else if ( cFunctionNamePure == 0x01 ){// 0'ary variable subfunction
		DEBUG_OUT_L2(<<"cUnderFunction::restoring cFunctionVariable"<<endl);
		pUnderFunctionRestored = new cFunctionVariable( iBitStream, iReturnValue,
			liDefinedVariables, pInDomainVariable, pInSuperiorFunction, pInDefiningFibElement );
		
	}else if ( cFunctionNamePure == 0x02 ){// 1'ary subfunction
		DEBUG_OUT_L2(<<"cUnderFunction::restoring 1'ary subfunction"<<endl);
		//read the subfunctionname
		cFunctionName = 0x00;
		uiBitsRead = iBitStream.readBits( &cFunctionName, 2 );
		if ( ! iBitStream.getStream()->good() ){
			outStatus = -2;
			return NULL;
		}
		if ( uiBitsRead != 2 ){
			outStatus = -2;
			DEBUG_OUT_EL2(<<"Error: "<<uiBitsRead<<" bits read, but should be 2"<<endl);
			return NULL;
		}
		/*clear bits not needed for the function ary type*/
		cFunctionNamePure = cFunctionName & 0x03;
		
		if ( cFunctionNamePure == 0x00 ){//abs subfunction 000
			DEBUG_OUT_L2(<<"cUnderFunction::restoring cFunctionAbs"<<endl);
			pUnderFunctionRestored = new cFunctionAbs( iBitStream, iReturnValue,
				liDefinedVariables, pInDomainValue, pInDomainVariable,
				pInSuperiorFunction, pInDefiningFibElement );
		
		}else if ( cFunctionNamePure == 0x01 ){//sin subfunction 001
			DEBUG_OUT_L2(<<"cUnderFunction::restoring cFunctionSin"<<endl);
			pUnderFunctionRestored = new cFunctionSin( iBitStream, iReturnValue,
				liDefinedVariables, pInDomainValue, pInDomainVariable,
				pInSuperiorFunction, pInDefiningFibElement );
		
		}else if ( cFunctionNamePure == 0x02 ){//1'ary subfunction with 4 bit initalisizer
			//read the next two bit
			cFunctionName = 0x00;
			uiBitsRead = iBitStream.readBits( &cFunctionName, 2 );
			if ( ! iBitStream.getStream()->good() ){
				outStatus = -2;
				return NULL;
			}
			if ( uiBitsRead != 2 ){
				outStatus = -2;
				DEBUG_OUT_EL2(<<"Error: "<<uiBitsRead<<" bits read, but should be 2"<<endl);
				return NULL;
			}
			/*clear bits not needed for the function ary type*/
			cFunctionNamePure = cFunctionName & 0x03;
			if ( cFunctionNamePure == 0x00 ){//log subfunction 00
				DEBUG_OUT_L2(<<"cUnderFunction::restoring cFunctionLog"<<endl);
				pUnderFunctionRestored = new cFunctionLog( iBitStream, iReturnValue,
					liDefinedVariables, pInDomainValue, pInDomainVariable,
					pInSuperiorFunction, pInDefiningFibElement );
			
			}else if ( cFunctionNamePure == 0x01 ){//arcsin subfunction 01
				DEBUG_OUT_L2(<<"cUnderFunction::restoring cFunctionArcsin"<<endl);
				pUnderFunctionRestored = new cFunctionArcsin( iBitStream, iReturnValue,
					liDefinedVariables, pInDomainValue, pInDomainVariable,
					pInSuperiorFunction, pInDefiningFibElement );
		
			}else if ( cFunctionNamePure == 0x02 ){//round subfunction 10
				DEBUG_OUT_L2(<<"cUnderFunction::restoring cFunctionRound"<<endl);
				pUnderFunctionRestored = new cFunctionRound( iBitStream, iReturnValue,
					liDefinedVariables, pInDomainValue, pInDomainVariable,
					pInSuperiorFunction, pInDefiningFibElement );
			
			}else{//Warning: no subfunction to restore
				iReturnValue = 2;
			}//TODO more subfunctions
			
		}else{//Warning: no subfunction to restore
			iReturnValue = 2;
		}//TODO more subfunctions
				
	}else if ( cFunctionNamePure == 0x03 ){// 2'ary subfunction
		DEBUG_OUT_L2(<<"cUnderFunction::restoring 2'ary subfunction"<<endl);
		
		//read the subfunctionname
		cFunctionName = 0x00;
		uiBitsRead = iBitStream.readBits( &cFunctionName, 3 );
		if ( ! iBitStream.getStream()->good() ){
			outStatus = -2;
			return NULL;
		}
		if ( uiBitsRead != 3 ){
			outStatus = -2;
			DEBUG_OUT_EL2(<<"Error: "<<uiBitsRead<<" bits read, but should be 3"<<endl);
			return NULL;
		}
		/*clear bits not needed for the function ary type*/
		cFunctionNamePure = cFunctionName & 0x07;
		
		if ( cFunctionNamePure == 0x00 ){//add subfunction 000
			DEBUG_OUT_L2(<<"cUnderFunction::restoring cFunctionAdd"<<endl);
			pUnderFunctionRestored = new cFunctionAdd( iBitStream, iReturnValue,
				liDefinedVariables, pInDomainValue, pInDomainVariable,
				pInSuperiorFunction, pInDefiningFibElement );
		
		}else if ( cFunctionNamePure == 0x01 ){//sub subfunction 001
			DEBUG_OUT_L2(<<"cUnderFunction::restoring cFunctionSub"<<endl);
			pUnderFunctionRestored = new cFunctionSub( iBitStream, iReturnValue,
				liDefinedVariables, pInDomainValue, pInDomainVariable,
				pInSuperiorFunction, pInDefiningFibElement );
		
		}else if ( cFunctionNamePure == 0x02 ){//mult subfunction 010
			DEBUG_OUT_L2(<<"cUnderFunction::restoring cFunctionMult"<<endl);
			pUnderFunctionRestored = new cFunctionMult( iBitStream, iReturnValue,
				liDefinedVariables, pInDomainValue, pInDomainVariable,
				pInSuperiorFunction, pInDefiningFibElement );
		
		}else if ( cFunctionNamePure == 0x03 ){//div subfunction 011
			DEBUG_OUT_L2(<<"cUnderFunction::restoring cFunctionDiv"<<endl);
			pUnderFunctionRestored = new cFunctionDiv( iBitStream, iReturnValue,
				liDefinedVariables, pInDomainValue, pInDomainVariable,
				pInSuperiorFunction, pInDefiningFibElement );
		
		}else if ( cFunctionNamePure == 0x04 ){//exp subfunction 100
			DEBUG_OUT_L2(<<"cUnderFunction::restoring cFunctionExp"<<endl);
			pUnderFunctionRestored = new cFunctionExp( iBitStream, iReturnValue,
				liDefinedVariables, pInDomainValue, pInDomainVariable,
				pInSuperiorFunction, pInDefiningFibElement );
		
		}else if ( cFunctionNamePure == 0x05 ){//min subfunction 101
			DEBUG_OUT_L2(<<"cUnderFunction::restoring cFunctionMin"<<endl);
			pUnderFunctionRestored = new cFunctionMin( iBitStream, iReturnValue,
				liDefinedVariables, pInDomainValue, pInDomainVariable,
				pInSuperiorFunction, pInDefiningFibElement );
		
		}else if ( cFunctionNamePure == 0x06 ){//max subfunction 110
			DEBUG_OUT_L2(<<"cUnderFunction::restoring cFunctionMax"<<endl);
			pUnderFunctionRestored = new cFunctionMax( iBitStream, iReturnValue,
				liDefinedVariables, pInDomainValue, pInDomainVariable,
				pInSuperiorFunction, pInDefiningFibElement );
		
		}else if ( cFunctionNamePure == 0x07 ){//111 subfunctions with 10 bits as initiator
		
			//read the subfunctionname
			cFunctionName = 0x00;
			uiBitsRead = iBitStream.readBits( &cFunctionName, 5 );
			if ( ! iBitStream.getStream()->good() ){
				outStatus = -2;
				return NULL;
			}
			if ( uiBitsRead != 5 ){
				outStatus = -2;
				DEBUG_OUT_EL2(<<"Error: "<<uiBitsRead<<" bits read, but should be 5"<<endl);
				return NULL;
			}
			/*clear bits not needed for the function ary type*/
			cFunctionNamePure = cFunctionName & 0x1F;
			
			if ( cFunctionNamePure == 0x00 ){//if subfunction 000
				DEBUG_OUT_L2(<<"cUnderFunction::restoring cFunctionIf"<<endl);
				pUnderFunctionRestored = new cFunctionIf( iBitStream, iReturnValue,
					liDefinedVariables, pInDomainValue, pInDomainVariable,
					pInSuperiorFunction, pInDefiningFibElement );
				
		/*TODO delay:
			if ( cFunctionNamePure == 0x01 ){//delay subfunction 001
			 0000 1 111: Delay
		*/
			}//TODO more subfunctions
		
		}else{//Warning: no subfunction to restore
			iReturnValue = 2;
		}
		
	}else{//Warning: no subfunction to restore
		iReturnValue = 2;
	}//TODO more subfunctions

	if ( iReturnValue < 0 ){
		outStatus = iReturnValue;
	}else if ( (iReturnValue != 0) && (outStatus == 0) ){
		outStatus = iReturnValue;
	}
	
	DEBUG_OUT_L2(<<"cUnderFunction::restore() done (outStatus="<<outStatus<<")"<<endl);
	
	return pUnderFunctionRestored;
}



/**
 * This Method checks if the given subfunction is equal to this subfunction.
 *
 * @param subfunction the subfunction to compare with this subfunction
 * @return true if the given subfunction is equal to this subfunction, else false
 */
bool cUnderFunction::operator==( const cUnderFunction &subfunction ) const{

	return this->equal( subfunction );
}


/**
 * This Method checks if the given subfunction is not equal to this subfunction.
 *
 * @param subfunction the subfunction to compare with this subfunction
 * @return true if the given subfunction is not equal to this subfunction, else false
 */
bool cUnderFunction::operator!=( const cUnderFunction &subfunction ) const{

	return ! ( this->equal( subfunction ) );
}


/**
 * This method checks if the given subfunction is equal to this subfunction.
 *
 * @param subfunction the subfunction to compare with this subfunction
 * @param bCheckExternalObjects if true the external objects of
 * 	cExtObject will be compared
 * @return true if the given subfunction is equal to this subfunction, else false
 */
bool cUnderFunction::equal( const cUnderFunction &subfunction,
		const bool bCheckExternalObjects ) const{
	
	map< const cRoot *, const cRoot * > mapEqualRootObjects;
	map< const cFibElement *, const cFibElement * > mapEqualDefinedVariables;
	
	return equalInternal( subfunction,
		mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects );
}









