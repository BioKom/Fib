/**
 * @class cFunctionVariable
 * file name: cFunctionVariable.cpp
 * @author Betti Oesterholz
 * @date 23.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a variable underfunction.
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
 * This class represents a variable underfunction.
 * Variable underfunction store a fixted /constant variable.
 *
 */
/*
History:
23.04.2010  Oesterholz  created
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
*/

#include "cFunctionVariable.h"

#include "cFibElement.h"
#include "cTypeVariable.h"
#include "cDomainIntegerBasis.h"


using namespace fib;


/**
 * The constructor of the underfunction.
 *
 * @param dInVariable the variable of this underfunction
 * @param pInSuperiorFunction the underfunction which contains the
 * 	new underfunction
 * @param pInDefiningFibElement the fib -element which defines/ uses
 * 	the new underfunction
 */
cFunctionVariable::cFunctionVariable( cFibVariable * pInVariable,
		cUnderFunction * pInSuperiorFunction,
		cFibElement * pInDefiningFibElement ):
		cUnderFunction( pInSuperiorFunction, pInDefiningFibElement ),
		pVariable( NULL ){
	
	setVariable( pInVariable );
}


/**
 * The copy constructor of the underfunction.
 *
 * @param underfunction the underfunction which to copy
 * @param pInSuperiorFunction the underfunction which contains the
 * 	new underfunction
 * @param pInDefiningFibElement the fib -element which defines/ uses
 * 	the new underfunction
 */
cFunctionVariable::cFunctionVariable( const cFunctionVariable & underfunction,
		cUnderFunction * pInSuperiorFunction,
		cFibElement *pInDefiningFibElement ):
		cUnderFunction( underfunction, pInSuperiorFunction, pInDefiningFibElement ),
		pVariable( NULL ){
	
	setVariable( underfunction.pVariable );
}


/**
 * The constructor for restoring a variable underfunction from an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node the underfunction is stored in
 * @param outStatus An reference to an integervariable where the errorvariable
 * 	can be stored to.
 * 	possible errorvariables are:
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
cFunctionVariable::cFunctionVariable( const TiXmlElement * pXmlElement, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		cUnderFunction * pInSuperiorFunction, cFibElement *pInDefiningFibElement ):
		cUnderFunction( pInSuperiorFunction, pInDefiningFibElement ),
		pVariable( NULL ){
	
	DEBUG_OUT_L3(<<this<<"->cFunctionVariable() rostore xml"<<endl);

	//check the vector type
	if ( pXmlElement == NULL ){
		//noting to restore
		outStatus = -1;
		return;
	}
	string szElementType( pXmlElement->Value() );
	if ( szElementType != "variable" ){
		//wrong element type to restore
		outStatus = -2;
		return;
	}
	//read the variable
	const char * pcValue = pXmlElement->GetText();
	long lValue;
	const int iReadValues = sscanf( pcValue, "%ld", & lValue );
	if ( iReadValues != 1){
		//Warning: The element text is not a number.
		outStatus = 2;
		return;
	}
	//search for the apropirate variable in the given variable list
	cFibVariable * pCorrectVariable = NULL;
	
	for ( list<cFibVariable*>::iterator itrVariable = liDefinedVariables.begin();
			itrVariable != liDefinedVariables.end(); itrVariable++ ){
		
		if ( (*itrVariable)->getIntegerValue() == lValue ){
			//correct variable to insert as the vectorelement found
			pCorrectVariable = *itrVariable;
			break;
		}
	}
	if ( pCorrectVariable == NULL ){
		//Warning: No such variable
		outStatus = 2;
		return;
	}
	setVariable( pCorrectVariable );
}


/**
 * This constructor restores a variable underfunction from the stream
 * where it is stored in the compressed fib -format.
 * Beware: The bits for the functiontype should be allready readed, this
 * 	constructor reads yust the two underfunctions.
 *
 * @param iBitStream the stream where this underfunction is stored to in,
 * 	because this stream is an cReadBits, any number of bits can be
 * 	readed from it
 * @param outStatus An reference to an integervariable where the errorvariable
 * 	can be stored to. If the pointer is NULL no errorvariable will be
 * 	given back.
 * 	possible errorvariables are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid stream
 * 		- -2 loading error, invalid data in stream
 * 		- 1 loading warning, invalid data in stream, error could be corrected
 * 		- 2 loading warning, invalid data in stream, maybe the loaded
 * 			object is wrong
 * @param liDefinedVariables a list with the defined variables for the
 * 	to restore fib -element, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 * @param pInVariableDomain the domain for variable underfunctions
 * @param pInSuperiorFunction the underfunction which contains the
 * 	new underfunction
 * @param pInDefiningFibElement the fib -element which defines/ uses
 * 	the new underfunction
 */
cFunctionVariable::cFunctionVariable( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomainSingle * pInVariableDomain,
		cUnderFunction * pInSuperiorFunction, cFibElement * pInDefiningFibElement ):
		cUnderFunction( pInSuperiorFunction, pInDefiningFibElement ),
		pVariable( NULL ){
	
	DEBUG_OUT_L3(<<this<<"->cFunctionVariable() restore bit"<<endl);

	//check the stream type
	if ( ! iBitStream.getStream()->good() ){
		outStatus = -1;
		DEBUG_OUT_EL3(<<"Error: stream not good"<<endl);
		return;
	}
	if ( pInVariableDomain == NULL ){
		outStatus = -2;
		DEBUG_OUT_EL3(<<"Error: no valid variable domain"<<endl);
		return;
	}
	
	if ( pInVariableDomain == NULL ){
		outStatus = -2;
		return;
	}
	
	cTypeVariable typeVariable;
	if ( ! typeVariable.isCompatible( *pInVariableDomain ) ){
		/*if the variable domain is not compatible to variable type
		-> can't restore the vector*/
		outStatus = -2;
		return;
	}
	cDomainIntegerBasis * pDomainVariable = (cDomainIntegerBasis*)pInVariableDomain;

	//restore the variable of the variableunderfunction
	longFib lValue = pDomainVariable->restoreIntegerValue( iBitStream, outStatus );
	if ( outStatus < 0 ){
		DEBUG_OUT_EL3(<<"Error: Couldn't restore the variable number"<<endl);
		return;
	}
	
	//search for the apropirate variable in the given variable list
	cFibVariable * pCorrectVariable = NULL;
	
	for ( list<cFibVariable*>::iterator itrVariable = liDefinedVariables.begin();
			itrVariable != liDefinedVariables.end(); itrVariable++ ){
		
		if ( (*itrVariable)->getIntegerValue() == lValue ){
			//correct variable to insert as the vectorelement found
			pCorrectVariable = *itrVariable;
			break;
		}
	}
	if ( pCorrectVariable == NULL ){
		//Warning: No such variable
		outStatus = 2;
		DEBUG_OUT_EL3(<<"Error: Couldn't find the correct variable with the number "<<lValue<<" (ther are "<< liDefinedVariables.size() <<" defined variables) ."<<endl);
		return;
	}
	setVariable( pCorrectVariable );
	
	DEBUG_OUT_L3(<<this<<"->cFunctionVariable() restore bit done"<<endl);
}


/**
 * The destructor of the underfunction.
 */
cFunctionVariable::~cFunctionVariable(){
	// unregister variable
	if ( pVariable ){
		pVariable->unregisterUsingElement( this );
	}
}


/**
 * This method returns if this underfunction is valid, else false.
 * All variables in the underfunction and it's underfunctions must be
 * inside the underfunction domain. All variables must be defined over
 * this underfunction.
 * No underfunction should contain itselfor should be contained in one
 * of its underfunctions (no cycles allowed).
 *
 * @return true if this underfunction is valid, else false
 */
bool cFunctionVariable::isValid() const{
	
	if ( pDefiningFibElement != NULL ){
		
		return pDefiningFibElement->isDefinedVariable( pVariable, ED_HIGHER );
	}
	return false;
}


/**
 * This method checks if the given variable is used in this underfunction.
 *
 * @see cFibVariable
 * @param variable the variable to check if it is used
 * @return true if the variable is used, else false
 */
bool cFunctionVariable::isUsedVariable( const cFibVariable * variable ) const{
	
	if ( ( pVariable == variable ) && ( pVariable != NULL ) ){
		return true;
	}
	return false;
}


/**
 * This method returns all variables used in this underfunction.
 *
 * @see cFibVariable
 * @return all variables used in this underfunction
 */
set<cFibVariable*> cFunctionVariable::getUsedVariables(){
	
	set<cFibVariable*> setUsedVariables;
	if ( pVariable ){
		setUsedVariables.insert( pVariable );
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
bool cFunctionVariable::replaceVariable( cFibVariable *variableOld,
		cFibVariable *variableNew ){
	
	if ( (variableOld == NULL) || (variableNew == NULL) ){
		return false;
	}
	if ( variableOld == pVariable ){
		return setVariable( variableNew );
	}
	return true;
}

/**
 * Returns the variable of the underfunction or 0 if non such exists.
 *
 * @return the variable of the underfunction or 0 if non
 * 	such exists
 */
cFibVariable * cFunctionVariable::getVariable(){
	
	return pVariable;
}


/**
 * This method Sets the variable of the underfunction.
 *
 * @param pInVariable a pointer to the variable for the underfunction
 * @return true if the variable was set to pInVariable else false
 */
bool cFunctionVariable::setVariable( cFibVariable * pInVariable ){

	DEBUG_OUT_L3(<<this<<"->cFunctionVariable::setVariable( "<<pInVariable<<" )"<<endl);
	
	if ( pInVariable == NULL ){
		return false;
	}
	if ( pVariable != NULL ){
		//unregister this underfunction in the old variable
		pVariable->unregisterUsingElement( this );
	}
	pVariable = pInVariable;
	//register the this variable user at the variable
	pVariable->registerUsingElement( this );

	return true;

}

/**
 * Returns the value of the underfunction or 0 if non such exists.
 *
 * @return the value of the underfunction or 0 if non
 * 	such exists
 */
doubleFib cFunctionVariable::getValue() const{

	if ( pVariable == NULL ){
		return 0.0;
	}
	return pVariable->getValue();
}


/**
 * @return the number of underfunctions, a underfunction of this type has
 */
unsignedIntFib cFunctionVariable::getNumberOfUnderFunctions() const{

	return 0;
}



/**
 * This method evaluades a variable for the time needed to evariable the
 * underfunction.
 * This variable should not exceed lMaxTime, if the variable for the time
 * is greater than lMaxTime the evaluation will be stopt and lMaxTime
 * returned. If lMaxTime is 0 (for infinity) the evaluation won't be
 * stoped, this is the standard case.
 *
 * @see cFibElement::evariableObject()
 * @param lMaxTime the maximum time for the evaluation, the returned
 * 	exceed this variable; the variable 0 stands for infinity, so the
 * 	evaluation won't be stoped
 * @return a variable for the time needed to evariable this underfunction
 */
unsignedLongFib cFunctionVariable::getTimeNeed( unsignedLongFib lMaxTime ) const{

	return 1;
}


/**
 * This method evaluades the size of the Fib -object in bits in the
 * compressed file form.
 * The optionalpart field of point -elements will be ignored.
 *
 * @see store()
 * @return the size of the Fib -object in bits in the compressed form
 */
unsignedLongFib cFunctionVariable::getCompressedSize() const{
	
	DEBUG_OUT_L3(<<this<<"->cFunctionVariable::getCompressedSize()"<<endl);
	
	unsignedLongFib ulCompressedSize = 2;//prefix
	
	//get the domain for the variables in this underfunction
	cDomainIntegerBasis * pDomainVariable = NULL;
	cTypeVariable typeVariable;
	if ( pDefiningFibElement ){
		cDomains validValueDomains = pDefiningFibElement->getValidValueDomains();
		
		//return the variable domain
		pDomainVariable = (cDomainIntegerBasis*)
			validValueDomains.getDomainForElement( typeVariable );
	}
	bool bStandardDomainVariable = false;
	if ( pDomainVariable == NULL ){
		//use the standrad domain
		pDomainVariable = (cDomainIntegerBasis*)typeVariable.getStandardDomain();
		bStandardDomainVariable = true;
	}

	//add the compressed size for the variable
	ulCompressedSize += pDomainVariable->getCompressedSizeForValue();

	if ( bStandardDomainVariable ){
		delete pDomainVariable;
	}

	return ulCompressedSize;
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
bool cFunctionVariable::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	DEBUG_OUT_L3(<<this<<"->cFunctionVariable::store()"<<endl);
	if ( pVariable == NULL ){
		return false;
	}
	
	//get the domain for the variables in this underfunction
	cDomainIntegerBasis * pDomainVariable = NULL;
	cTypeVariable typeVariable;
	if ( pDefiningFibElement ){
		cDomains validValueDomains = pDefiningFibElement->getValidValueDomains();
		
		//return the variable domain
		pDomainVariable = (cDomainIntegerBasis*)
			validValueDomains.getDomainForElement( typeVariable );
	}
	bool bStandardDomainVariable = false;
	if ( pDomainVariable == NULL ){
		//use the standrad domain
		pDomainVariable = (cDomainIntegerBasis*)typeVariable.getStandardDomain();
		bStandardDomainVariable = true;
	}

	//write the bits for the prefix 01
	char cTypeBit = 0x01;
	bool bReturnVariable = nBitStream::store( stream, cRestBits, uiRestBitPosition,
		&cTypeBit, 2 );
	//write the bits for the variable
	bReturnVariable &= pDomainVariable->storeValue( pVariable->getIntegerValue(),
		stream, cRestBits, uiRestBitPosition );
	
	if ( bStandardDomainVariable ){
		delete pDomainVariable;
	}
	return bReturnVariable;
}


/**
 * This method stores this underfunction in the XML -format into the
 * given stream.
 * Variables should have ther number as ther variable.
 *
 * @param stream the stream where this underfunctionshould be
 * 	stored to
 * @return true if this underfunction is stored, else false
 */
bool cFunctionVariable::storeXml( ostream & stream ) const{
	
	DEBUG_OUT_L3(<<this<<"->cFunctionVariable::storeXml()"<<endl);
	
	if ( pVariable == NULL ){
		return false;
	}
	//store the unserfunction
	stream<<"<variable>"<< pVariable->getIntegerValue() <<"</variable>"<<endl;

	return true;
}


/**
 * @return the type for the underfunction
 */
unsignedIntFib cFunctionVariable::getType() const{

	return FUNCTION_VARIABLE;
}

/**
 * @return the name for the underfunction
 */
string cFunctionVariable::getUnderFunctionName() const{
	
	return "variable";
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
bool cFunctionVariable::equalInternal( const cUnderFunction & underfunction,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{
	
	if ( & underfunction == NULL ){
		return false;
	}
	if ( getType() != underfunction.getType() ){
		return false;
	}
	cFunctionVariable * pFunctionVariable = (cFunctionVariable*)(& underfunction);
	if ( (pVariable == NULL) || (pFunctionVariable->pVariable == NULL) ){
		
		if ( pVariable != pFunctionVariable->pVariable ){
			//not both variables NULL
			return false;
		}//else
		return true;
	}
	return pVariable->equalInternal( *(pFunctionVariable->pVariable),
			mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects );
}

#else //FEATURE_EQUAL_FIB_OBJECT

/**
 * This Method checks if the given underfunction is equal to this underfunction.
 *
 * @param underfunction the underfunction to compare with this underfunction
 * @return true if the given underfunction is equal to this underfunction, else false
 */
bool cFunctionVariable::equal( const cUnderFunction & underfunction ) const{
	
	if ( & underfunction == NULL ){
		return false;
	}
	if ( getType() != underfunction.getType() ){
		return false;
	}
	cFunctionVariable * pFunctionVariable = (cFunctionVariable*)(& underfunction);
	if ( (pVariable == NULL) || (pFunctionVariable->pVariable == NULL) ){
		
		if ( pVariable != pFunctionVariable->pVariable ){
			//not both variables NULL
			return false;
		}//else
		return true;
	}
	return ( (*pVariable) == (*(pFunctionVariable->pVariable)) );
}

#endif //FEATURE_EQUAL_FIB_OBJECT

/**
 * This method duplicates this whole underfunction.
 * Underfunctions of this underfunction are also cloned.
 *
 * @param pSuperiorUnderFunction the underfunction which contains
 * @param pInDefiningFibElement the Fib -element which defines/ uses
 * @return the cloned/ duplicated underfunction
 */
cUnderFunction * cFunctionVariable::clone(
		cUnderFunction * pInSuperiorUnderFunction,
		cFibElement *pInDefiningFibElement) const{
	
	return new cFunctionVariable( *this, pInSuperiorUnderFunction,
		pInDefiningFibElement );
}


/**
 * @return the fib -element which uses the variables of this element
 */
cFibElement * cFunctionVariable::getVariableUsingFibElement() const{
	
	return pDefiningFibElement;
}


/**
 * This method deletes all occurenc of the given variable from this
 * element. So the variable is not used anymore of this element.
 * Beware: This element has to be unregisterd (call
 * unregisterUsingElement() ) at the pVariable seperatly. Do this directly
 * befor or after calling this method.
 *
 * @param pInVariable the variable which is to delete from this element
 * @return true if the variable dosn't occure anymore in this element,
 * 	else false
 */
bool cFunctionVariable::deleteVariable( cFibVariable * pInVariable ){
	
	if ( (pInVariable == NULL) || (pVariable == NULL) ){
		return true;
	}
	if ( pVariable == pInVariable ){
		//delete the variable of this underfunction
		pVariable = NULL;
	}
	return true;
}






