/**
 * @class cFunction
 * file name: cFunction.cpp
 * @author Betti Oesterholz
 * @date 23.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the fib -functionelement.
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
 * This class represents the functionelement of the Fib -multimedialanguage.
 * An functionelement contains a subfunction which realizes the function.
 * It defines a variable which is set to the value of the subfunction.
 *
 */
/*
History:
23.04.2010  Oesterholz  created
28.02.2011  Oesterholz  if the constructors are given an NULL reference to
	the underfunction, the underfunction is set to the value 0 underfunction,
	so the function always has an underfunction
06.05.2011  Oesterholz  isValidFibElement() checks the underfunction
21.07.2011  Oesterholz  for the Xml-format "underfunction" to "subfunction"
05.08.2011  Oesterholz  FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES implemented
07.08.2011  Oesterholz  isDefinedVariable() and getDefinedVariables() with
	pCallingFibElement
17.10.2011  Oesterholz  FEATURE_OUTPUT_ELEMENT_NUMBER_XML implemented
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
*/


#include "cFunction.h"

#include "cFibElement.h"
#include "cTypeVariable.h"
#include "cDomainIntegerBasis.h"
#include "cFunctionValue.h"

using namespace fib;



#ifdef FEATURE_SIMPLE_CONSTRUCTOR

/**
 * parameterconstructor
 *
 * @param inUnderFunction the subfunction this function should have
 * @param pInUnderobject the fib-element, which is the underobject of
 * 	this fib-element (it also stands next in the order of fib-elements)
 * @param pInSuperiorElement the fib-element in which this
 * 	function element is an underobject
 */
cFunction::cFunction( const cUnderFunction & inUnderFunction,
		cFibElement * pInUnderobject, cFibElement * pInSuperiorElement ):
		cFibLimb( pInUnderobject, pInSuperiorElement ),
		pUnderFunction( NULL ), variableDefined( this ){
	
	if ( (& inUnderFunction) != NULL ){
		setUnderFunction( inUnderFunction );
	}else{
		setUnderFunction( cFunctionValue( 0.0 ) );
	}
	if ( pInSuperiorElement ){
		pInSuperiorElement->insertObjectInElement( this );
	}else{
		updateAllValues();
	}
}

#else //FEATURE_SIMPLE_CONSTRUCTOR

/**
 * parameterconstructor
 *
 * @param inUnderFunction the subfunction this function should have
 * @param pInSuperiorElement the fib-element in which this
 * 	function -element is an underobject
 * @param pInPreviousFibElement the fib-element which stands in the order
 * 	of fib-elements befor this fib-element
 * @param pInUnderobject the fib-element which is the underobject of
 * 	this fib-element (it also stands next in the order of fib-elements)
 */
cFunction::cFunction( const cUnderFunction & inUnderFunction,
		cFibElement * pInSuperiorElement, cFibElement * pInPreviousFibElement,
		cFibElement * pInUnderobject ):
		cFibLimb( pInSuperiorElement, pInPreviousFibElement, pInUnderobject ),
		pUnderFunction( NULL ), variableDefined( this ){
	
	if ( (& inUnderFunction) != NULL ){
		setUnderFunction( inUnderFunction );
	}else{
		setUnderFunction( cFunctionValue( 0.0 ) );
	}
	updateAllValues();
}

#endif //FEATURE_SIMPLE_CONSTRUCTOR


/**
 * copyconstructor
 * This copyconstructor constructs a copy of the given function element.
 * It dosn't copy other if-elements than the given, even if ther are
 * in the function element.
 *
 * @param functionElement the function -element to copy
 */
cFunction::cFunction( const cFunction & functionElement ):
		cFibLimb( functionElement ),
		pUnderFunction( NULL ), variableDefined( this ){
	
	if ( functionElement.pUnderFunction != NULL ){
		setUnderFunction( *(functionElement.pUnderFunction) );
	}else{
		setUnderFunction( cFunctionValue( 0.0 ) );
	}
}


/**
 * The constructor for restoring a functionobject from an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node wher the fib -object is stored in
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
 * 	to restore fib-element, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 */
cFunction::cFunction( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables ):
		pUnderFunction( NULL ), variableDefined( this ){
	
	if ( pXmlElement == NULL ){
		//noting to restore
		outStatus = -1;
		return;
	}
	string szElementType( pXmlElement->Value() );
	if ( szElementType != "function" ){
		//wrong element type to restore
		outStatus = -2;
		return;
	}
	//read the variable number
	const char * szDefinedVariableNumber = pXmlElement->Attribute( "define_variable" );
	
	if ( szDefinedVariableNumber == NULL ){
		outStatus = 2;
	}else{
		variableDefined.setIntegerValue( atol( szDefinedVariableNumber ) );
	}
	liDefinedVariables.push_front( &variableDefined );
	
	for ( const TiXmlNode * pChild = pXmlElement->FirstChild();
			pChild != NULL; pChild = pChild->NextSibling() ) {
		
		int iType = pChild->Type();
		
		switch ( iType ){
			case TiXmlNode::ELEMENT:{
				/*check if this is a valid fib-element xml -element, create
				the apropirate fib-element and call its restoreXml() method*/
				const TiXmlElement * pXmlElement = pChild->ToElement();
				if ( pXmlElement == NULL ){
					outStatus = 2;
					continue;
				}
				string szElementType( pXmlElement->Value() );

				if ( ( szElementType == "subfunction" ) || ( szElementType == "underfunction" )  ){
					//"underfunction" is depricated
					//restore the subfunction
					pXmlElement = pXmlElement->FirstChildElement();
					if ( (pUnderFunction == NULL) && (pXmlElement != NULL) ){
						
						pUnderFunction = cUnderFunction::restoreXml(
							pXmlElement, outStatus, liDefinedVariables, NULL, this );
						if ( outStatus < 0 ){
							//an error occured
							return;
						}
					}else{//to many underobjects -> no correct area element
						outStatus = 2;
						continue;
					}
				}else{//restore the underobject
					if ( pUnderObject == NULL ){
						pUnderObject = cFibElement::restoreXml(
							pChild, outStatus, liDefinedVariables );
#ifdef FEATURE_FAST_UPDATE
						if ( pUnderObject ){
							pUnderObject->pSuperiorElement = this;
						}
#endif //FEATURE_FAST_UPDATE
						if ( outStatus < 0 ){
							//an error occured
							return;
						}
					}else{//to many underobjects -> no correct area element
						outStatus = 2;
						continue;
					}
				}
			}break;
			
			case TiXmlNode::DECLARATION:
			case TiXmlNode::COMMENT:{
				//ignore
				continue;
			}break;
			case TiXmlNode::DOCUMENT:
			case TiXmlNode::TEXT:
			case TiXmlNode::UNKNOWN:
			default:
				//invalid areaelement
				if ( outStatus ){
					outStatus = 2;
				}
				continue;
		}
	}
	if ( pUnderFunction == NULL ){
		//no subfunction loaded
		outStatus = 2;
		setUnderFunction( cFunctionValue( 0.0 ) );
		return;
	}
	if ( pUnderObject == NULL ){
		outStatus = -2;
		return;
	}
}


/**
 * This constructor restores a functionobject from the stream where it is
 * stored in the compressed fib -format.
 * This method is for internal use only.
 *
 * @param iBitStream the stream wher the functionobject is stored to in,
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
 * 	to restore fib-element, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 * @param validDomains the domains valid for restoring the fib-elements
 * @param pNextRoot the next higher root -element for the to restore
 * 	fib-elements, or the last restored root -element
 */
cFunction::cFunction( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains,
		cRoot * pNextRoot ): pUnderFunction( NULL ), variableDefined( this ){
	
	DEBUG_OUT_L2(<<"constructor cFunction() reading bit"<<endl);
	
	if ( ! iBitStream.getStream()->good() ){
		DEBUG_OUT_EL2(<<"stream not good"<<endl);
		outStatus = -1;
		return;
	}
	//get the domain for the variables in this vector
	cTypeVariable typeVariable;
	//return the variable domain
	cDomainIntegerBasis * pDomainVariable = (cDomainIntegerBasis*)
		validDomains.getDomainForElement( typeVariable );
	bool bStandardDomainVariable = false;
	if ( pDomainVariable == NULL ){
		//use the standrad domain
		pDomainVariable = (cDomainIntegerBasis*)typeVariable.getStandardDomain();
		bStandardDomainVariable = true;
	}
	//set the defined variable value
#ifdef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	variableDefined.setIntegerValue( liDefinedVariables.size() + 1 );
#else //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	//restore the variablevalue
	longFib lValue = pDomainVariable->restoreIntegerValue( iBitStream, outStatus );
	if ( outStatus < 0 ){
		return;
	}
	variableDefined.setIntegerValue( lValue );
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES

	liDefinedVariables.push_front( &variableDefined );

	//restore the vectors for the subfunction
	cTypeUnderFunction typeUnderFunction;
	cDomainSingle * pDomainFunction = (cDomainSingle*)
		validDomains.getDomainForElement( typeUnderFunction );
	bool bStandardDomainFunction = false;
	if ( pDomainFunction == NULL ){
		pDomainFunction = (cDomainSingle*)
			typeUnderFunction.getStandardDomain();
		bStandardDomainFunction = true;
	}
	
	//restore the subfunction
	pUnderFunction = cUnderFunction::restore( iBitStream, outStatus,
		liDefinedVariables, pDomainFunction, pDomainVariable, NULL, this );
	
	if ( bStandardDomainFunction ){
		delete pDomainFunction;
	}
	if ( bStandardDomainVariable ){
		delete pDomainVariable;
	}
	if ( outStatus < 0 ){
		DEBUG_OUT_EL2(<<"Error: While loading subfunction"<<endl);
		return;
	}

	//restore the underobject
	DEBUG_OUT_L2(<<"restoring underobject"<<endl);
	
	pUnderObject = cFibElement::restoreInternal( iBitStream, outStatus,
		liDefinedVariables, validDomains, pNextRoot );
	
#ifdef FEATURE_FAST_UPDATE
	if ( pUnderObject ){
		pUnderObject->pSuperiorElement = this;
	}
#endif //FEATURE_FAST_UPDATE
	DEBUG_OUT_L2(<<"constructor cFunction() reading bit done"<<endl);
}


/**
 * desstructor
 */
cFunction::~cFunction(){
	
	if ( pUnderFunction != NULL ){
		delete pUnderFunction;
	}
}


/**
 * This method checks, if this Fib-element is an valid Fib-element.
 *
 * @return true if this Fib-element is an valid Fib-element, else false
 */
bool cFunction::isValidFibElement() const{
	
	if ( pUnderFunction == NULL ){
		//no subfunction
		return false;
	}
	if ( ! pUnderFunction->isValid() ){
		//subfunction isn't valid -> function element not valid
		return false;
	}
	//everything if-specific is ok
	return cFibLimb::isValidFibElement();
}


/**
 * @see getTypeName
 * @return a character for the typ of the Fib-element
 * Types are:
 * 	- u: element of unknown typ
 * 	- p: point
 * 	- l: list-element
 * 	- y: property
 * 	- c: comment
 * 	- a: area
 * 	- f: function
 * 	- i: if-condition
 * 	- o: extern object element
 * 	- s: extern subobject element
 * 	- v: set-element
 * 	- m: matrix element
 * 	- r: root-element
 */
char cFunction::getType() const{

	return 'f';
}


/**
 * This method evaluades the fib -object.
 *
 * @param evaluePosition a reference to the object with the
 * 	evaluePosition() method to evalue /store the positions and ther
 * 	properties; everytime a point (to evalue) is reached in the
 * 	evaluation, this method is called with the position and the
 * 	properties of the point; @see iEvaluePosition
 * @param objectPoint the object point in the order of true partobjects
 * 	to evalue
 * @param liVecProperties a list with the property vectors which should
 * 	be global for the evalued object
 * @return if the evalueation was successfull true, else false
 */
bool cFunction::evalueObject( iEvaluePosition & evaluePosition,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties ) const{
	
	if ( pUnderObject == NULL ){
		//nothing to evalue
		return false;
	}
	if ( pUnderFunction == NULL ){
		//no subfunction -> can't evalue function
		return false;
	}
	//evalue the underobject for the subfunction value
	const_cast<cFunction*>(this)->variableDefined.setValue(
		pUnderFunction->getValue() );
	return pUnderObject->evalueObject( evaluePosition, objectPoint, liVecProperties );
}


/**
 * This method evaluades the fib -object.
 * Evertime a fib-elements, with a type of the given type chars in
 * liCFibElementTyps, is reached while evaluation, it is given
 * back with the properties which it has.
 * Ever pointelement is given back. The type chars for pointelements
 * don't need to be in the list liCFibElementTyps.
 *
 * @param evalueFibElement a reference to the object with the
 * 	evalueElement() method to evalue /store the fib-elements and ther
 * 	properties; everytime a fib-element (with one of the type given
 * 	in liCFibElementTyps) is reached in the evaluation, the method
 * 	evalueElement() of this objects is called with the fib-element
 * 	and the properties of the fib-element; @see iEvalueFibElement
 * @param objectPoint the object point in the order of true partobjects
 * 	to evalue
 * @param liVecProperties a list with the property vectors which should
 * 	be global for the evalued object
 * @param liCFibElementTyps a list with the type chars (@see getType)
 * 	of the fib-elements to return
 * @return if the evalueation was successfull true, else false
 */
bool cFunction::evalueObject( iEvalueFibElement & evalueFibElement,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties,
		const list<char> & liCFibElementTyps ){
	
	//check if this fib-element should be given back with evalueElement()
	for ( list<char>::const_iterator itrCType = liCFibElementTyps.begin();
			itrCType != liCFibElementTyps.end(); itrCType++ ){
		
		if ( *itrCType == getType() ){
			//call evalueElement() with this element
			return evalueFibElement.evalueElement( *this, liVecProperties );
		}
	}//else if this element shouldn't be returned -> evalue the main -fib -object

	if ( pUnderObject == NULL ){
		//nothing to evalue
		return false;
	}
	if ( pUnderFunction == NULL ){
		//no subfunction -> can't evalue function
		return false;
	}
	//evalue the underobject for the subfunction value
	const_cast<cFunction*>(this)->variableDefined.setValue(
		pUnderFunction->getValue() );
	return pUnderObject->evalueObject( evalueFibElement, objectPoint,
		liVecProperties, liCFibElementTyps );
}


/**
 * This method evaluades a value for the time needed to evalue the
 * object.
 * This value should not exceed lMaxTime, if the value for the time
 * is greater than lMaxTime the evaluation will be stopt and lMaxTime
 * returned. If lMaxTime is 0 (for infinity) the evaluation won't be
 * stoped, this is the standard case.
 *
 * @see evalueObject()
 * @param lMaxTime the maximum time for the evaluation, the returned
 * 	exceed this value; the value 0 stands for infinity, so the 
 * 	evaluation won't be stoped
 * @return a value for the time needed to evalue the object
 */
unsignedLongFib cFunction::getTimeNeed( unsignedLongFib lMaxTime ) const{
	
	if ( lMaxTime == 1 ){
		return lMaxTime;
	}

	unsignedLongFib ulTimeNeeded = 0;

	const_cast<cFunction*>(this)->variableDefined.setValue(
		pUnderFunction->getValue() );
	
	//evalue the underobject for the function
	if ( pUnderFunction ){
		if ( lMaxTime == 0 ){
			ulTimeNeeded += pUnderFunction->getTimeNeed( 0 );
		}else{
			ulTimeNeeded += pUnderFunction->getTimeNeed( lMaxTime - ulTimeNeeded );
			if ( lMaxTime <= ulTimeNeeded ){
				return lMaxTime;
			}
		}
	}//else no subfunction
	
	//evalue the underobject for the function
	if ( pUnderObject ){
		if ( lMaxTime == 0 ){
			ulTimeNeeded += pUnderObject->getTimeNeed( 0 );
		}else{
			ulTimeNeeded += pUnderObject->getTimeNeed( lMaxTime - ulTimeNeeded );
			if ( lMaxTime <= ulTimeNeeded ){
				return lMaxTime;
			}
		}
	}//no underobject
	return ulTimeNeeded;
}


/**
 * This method evaluades the size of the fib-object in bits in the
 * compressed file form.
 * The optionalpart field of function -elements will be ignored.
 *
 * @see store()
 * @return the size of the fib-object in bits in the compressed form
 */
unsignedLongFib cFunction::getCompressedSize() const{
	
	unsignedLongFib ulCompressedSize = 4;

#ifndef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	//evalue the bits needed for the variable
	//get the domain for the variables in this vector
	cTypeVariable typeVariable;
	/*get the value domain for variables*/
	cDomains validDomains = getValidValueDomains();
	//return the variable domain
	cDomainSingle * variableDomain = (cDomainSingle*)
		validDomains.getDomainForElement( typeVariable );
	bool bStandardDomainUsed = false;
	if ( variableDomain == NULL ){
		//use the standrad domain
		variableDomain = (cDomainSingle*)typeVariable.getStandardDomain();
		bStandardDomainUsed = true;
	}
	ulCompressedSize += variableDomain->getCompressedSizeForValue();
	if ( bStandardDomainUsed ){
		delete variableDomain;
	}
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES

	//add compressed size for the subfunction
	if ( pUnderFunction ){
		ulCompressedSize += pUnderFunction->getCompressedSize();
	}
	//add compressed size for the underobject
	if ( pUnderObject != NULL ){
		ulCompressedSize += pUnderObject->getCompressedSize();
	}
	return ulCompressedSize;
}


/**
 * This method checks if the given variable is used in the given
 * direction from this fib-element.
 *
 * @see cFibVariable
 * @see isDefinedVariable()
 * @param variable the variable to check if it is used
 * @param direction the direction from this fib-element, in which the
 * 	variable should be used; standardvalue is ED_POSITION so yust
 * 	this fib-element will be checked
 * @return true if the variable is used, else false
 */
bool cFunction::isUsedVariable( const cFibVariable *variable ,
		edDirection direction ) const{
	
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		//check subfunction
		if ( pUnderFunction ){
		
			const bool bVariableUsed = pUnderFunction->isUsedVariable( variable );
			if ( bVariableUsed ){
				return true;
			}
		}
	}
	return cFibLimb::isUsedVariable( variable, direction );
}


/**
 * This method returns all variables used in the given direction from
 * this fib-element.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @see isDefinedVariable()
 * @param direction the direction from this fib-element, in which the
 * 	variable should be used; standardvalue is ED_POSITION so yust
 * 	this fib-element will be checked
 * @return the set with all variables used in the given direction from
 * 	this fib-element
 */
set<cFibVariable*> cFunction::getUsedVariables( edDirection direction ){
	
	set<cFibVariable*> setUsedVariables;
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		//check subfunction
		if ( pUnderFunction ){
			
			set<cFibVariable*> setUsedVarUnderfunction =
				pUnderFunction->getUsedVariables();
			
			setUsedVariables.insert( setUsedVarUnderfunction.begin(),
				setUsedVarUnderfunction.end() );
		}
	}
	
	set<cFibVariable*> setUsedVariableleaf = cFibLimb::getUsedVariables( direction );
	setUsedVariables.insert( setUsedVariableleaf.begin(),
		setUsedVariableleaf.end() );

	return setUsedVariables;
}


/**
 * This method checks if the given variable is defined in the given
 * direction from this Fib-element.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @param variable the variable to check if it is defined
 * @param direction the direction from this Fib-element, in which the
 * 	variable should be defined; standardvalue is ED_POSITION so yust
 * 	this Fib-element will be checked
 * @param pCallingFibElement the Fib-Element which called this method
 * @return true if the variable is used, else false
 */
bool cFunction::isDefinedVariableInternal( const cFibVariable *variable,
		edDirection direction,
		const cFibElement * pCallingFibElement ) const{
	
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		//check the defiened variable
		if ( variable == &variableDefined ){
			return true;
		}//variable not defined here
	}
	return cFibLimb::isDefinedVariableInternal(
		variable,  direction, pCallingFibElement );
}


/**
 * This method returns all variables defined in the given direction from
 * this Fib-element.
 * This is for intern use to get the correct data from
 * getDefinedVariables() without pCallingFibElement.
 *
 * @see cFibVariable
 * @see getUsedVariables()
 * @see isDefinedVariable()
 * @param direction the direction from this Fib-element, in which the
 * 	variable should be used; standardvalue is ED_POSITION so yust
 * 	this Fib-element will be checked
 * @param pCallingFibElement the Fib-Element which called this method
 * @return the set with all variables used in the given direction from
 * 	this Fib-element
 */
list<cFibVariable*> cFunction::getDefinedVariablesInternal(
		edDirection direction,
		const cFibElement * pCallingFibElement ){

	list<cFibVariable*> liDefinedVariables;
	
	if ( (direction == ED_ALL) || ( direction == ED_BELOW ) ||
			(direction == ED_BELOW_EQUAL) ){
		//check in underobject
		liDefinedVariables = cFibLimb::getDefinedVariablesInternal(
			ED_BELOW, pCallingFibElement );
		
		if ( direction == ED_BELOW ){
			return liDefinedVariables;
		}
	}
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		//insert the defined variables this areaelement defines
		liDefinedVariables.push_front( &variableDefined );
	}
	if ( (direction == ED_ALL) || ( direction == ED_HIGHER ) ||
			(direction == ED_HIGHER_EQUAL) ){
		//elements to check in the direction
		list<cFibVariable*> liDefinedVariablesOfSuperObject =
				cFibLimb::getDefinedVariablesInternal( ED_HIGHER, pCallingFibElement );
			
		liDefinedVariables.insert( liDefinedVariables.begin(),
			liDefinedVariablesOfSuperObject.begin(),
			liDefinedVariablesOfSuperObject.end() );
	}
	return liDefinedVariables;
}


/**
 * This method replace the variable variableOld with the variable
 * variableNew in the object.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @see isDefinedVariable()
 * @param variableOld the variable to replace
 * @param variableNew the variable with which the variable variableOld
 * 	is to replace
 * @return true if the variable variableOld is replaced with variableNew,
 * 	else false
 */
bool cFunction::replaceVariable( cFibVariable *variableOld,
		cFibVariable *variableNew ){
	
	if ( (variableOld == NULL) || (variableNew == NULL) ){
		//can't replace
		return false;
	}
	//replace in subfunction
	if ( pUnderFunction ){
		
		//replace variable in areavector
		if ( ! pUnderFunction->replaceVariable( variableOld, variableNew ) ){
			return false;
		}
	}
	return cFibLimb::replaceVariable( variableOld, variableNew );
}


/**
 * This method copies the fib-element on the specified position.
 * Variables which are not defined in the fib-element but used
 * don't change ther reference.
 *
 * @see getType()
 * @param cType the type of the fib-element to copy
 * @param elementPoint the number of the fib-element, in the order of
 * 	Fib -elements of the given type cType, to copy
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	fib -object
 * @return the copy of the fib-element
 */
cFibElement * cFunction::copyElement( const char cType, const unsignedIntFib
		elementPoint, bool bAbsolute ) const{
	
	if ( elementPoint == 0 ){
		//copy this element
		return new cFunction( *this );
	}//else get the fib-element and copy it
	
	const cFibElement * pFibElementToCopy = getConstFibElement(
		cType, elementPoint, bAbsolute );
	
	if ( pFibElementToCopy ){
		return ( pFibElementToCopy->copyElement( 'u', 0 ) );
	}//else
	return NULL;
}


#ifdef FEATURE_EQUAL_FIB_OBJECT

/**
 * This method checks if the given Fib-object is equal to this fib
 * -object.
 * Variables can be others, but must be defined and used in equivalent
 * Fib-elements.
 *
 * @param fibObject the Fib-object to which this Fib-object should be
 * 	equal
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
bool cFunction::equalInternal( const cFibElement & fibObject,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{

	if ( ! equalElementInternal( fibObject, mapEqualRootObjects,
			mapEqualDefinedVariables, bCheckExternalObjects ) ){
		return false;
	}
	//add this element to the equal defined variables
	mapEqualDefinedVariables.insert( make_pair( this, &fibObject ) );
	
	return cFibLimb::equalInternal( fibObject, mapEqualRootObjects,
		mapEqualDefinedVariables, bCheckExternalObjects );
}


/**
 * This method checks if the given Fib-element is equal to this fib
 * -element.
 * The subobjects arn't compared, not even ther count is compared.
 * Used variables can be others.
 *
 * @param fibElement the Fib-element to which this Fib-element should be
 * 	equal
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
 * @return true if this Fib-element is equal to the given Fib-object,
 * 	else false
 */
bool cFunction::equalElementInternal( const cFibElement & fibElement,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{

	if ( getType() != fibElement.getType() ){
		return false;
	}
	cFunction * pFunctionElement = (cFunction*)(&fibElement);
	
	if ( pUnderFunction ){
		if ( pFunctionElement->pUnderFunction == NULL ){
			return false;
		}
		if ( ! pUnderFunction->equalInternal( * (pFunctionElement->pUnderFunction),
				mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
			return false;
		}
	}else{// pUnderFunction == NULL
		if ( pFunctionElement->pUnderFunction != NULL ){
			return false;
		}
	}
	return true;
}


/**
 * This method checks if the given Fib-element sets the variable to
 * the same values as this Fib-element.
 *
 * @param variableOwn a pointer to a defined variable in this Fib-element,
 * 	it is compared to the equivalent variable fibElement in the given
 * 	Fib-element fibElement
 * @param fibElement the Fib-element to which this Fib-element should be
 * 	compared
 * @param variable a pointer to a defined variable in the other 
 * 	Fib-element fibElement
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
 * @return true if this Fib-element sets the variable to the same
 * 	values as this Fib-element
 */
bool cFunction::equalValuesSetInternal( const cFibVariable * variableOwn,
		const cFibElement & fibElement,
		const cFibVariable * variable,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{

	const map< const cFibElement *, const cFibElement * >::const_iterator
		itrEqualDefinedVariable = mapEqualDefinedVariables.find( this );
	
	if ( ( itrEqualDefinedVariable != mapEqualDefinedVariables.end() ) &&
			( itrEqualDefinedVariable->second == &fibElement ) ){
		//Fib-elements compared befor
		return true;
	}//else compare Fib elements
	const bool bEqualElement = equalElementInternal( fibElement,
		mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects );
	if ( bEqualElement ){
		
		mapEqualDefinedVariables.insert( make_pair( this, &fibElement ) );
		return true;
	}
	return false;
}

#else //FEATURE_EQUAL_FIB_OBJECT

/**
 * This method checks if the given fib-object is equal to this Fib
 * -object.
 * Variables can be others, but must be defined and used in equivalent
 * fib-elements.
 *
 * @param fibObject the fib-object to which this fib-object should be
 * 	equal
 * @return true if this fib-object is equal to the given fib-object,
 * 	else false
 */
bool cFunction::equal( const cFibElement & fibObject ) const{

	if ( ! cFibLimb::equal( fibObject ) ){
		return false;
	}
	return equalElement( fibObject );
}


/**
 * This method checks if the given fib-element is equal to this fib
 * -element.
 * The underobjects arn't compared, not even ther count is compared.
 * Used variables can be others.
 *
 * @param fibElement the fib-element to which this fib-element should be
 * 	equal
 * @return true if this fib-element is equal to the given fib -object,
 * 	else false
 */
bool cFunction::equalElement( const cFibElement & fibElement ) const{

	if ( getType() != fibElement.getType() ){
		return false;
	}
	cFunction * pFunctionElement = (cFunction*)(&fibElement);
	
	if ( pUnderFunction ){
		if ( pFunctionElement->pUnderFunction == NULL ){
			return false;
		}
		if ( ! pUnderFunction->equal( * (pFunctionElement->pUnderFunction) ) ){
			return false;
		}
	}else{// pUnderFunction == NULL
		if ( pFunctionElement->pUnderFunction != NULL ){
			return false;
		}
	}
	return true;
}

#endif //FEATURE_EQUAL_FIB_OBJECT


/**
 * This method stores this fib-object in the XML -format into the
 * given stream.
 *
 * @param stream the stream where this fib-object should be stored to
 * @return true if this fib-object is stored, else false
 */
bool cFunction::storeXml( ostream & stream ) const{

	bool bReturnValue = true;
	
#ifdef FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	stream<<"<function elementNr=\""<<getNumberOfElement()<<"\" "<<
		"define_variable=\""<< variableDefined.getIntegerValue() <<"\">"<<endl;
#else //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	stream<<"<function define_variable=\""<< variableDefined.getIntegerValue() <<"\">"<<endl;
#endif //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	if ( pUnderFunction ){
		stream<<"<subfunction>"<<endl;
		//store subareas
		if ( ! pUnderFunction->storeXml( stream ) ){
			return false;
		}
		stream<<"</subfunction>"<<endl;
	}
	if ( pUnderObject ){
		bReturnValue &= pUnderObject->storeXml( stream );
	}
	stream<<"</function>"<<endl;
	return bReturnValue;
}



/*
 * functionelement methods
 */
	
/**
 * @return the subfunction this functionelement realizes
 */
cUnderFunction * cFunction::getUnderFunction() const{

	return pUnderFunction;
}


/**
 * This method sets the given subfunction as the subfunction of
 * this function.
 * (The given subfunction is copied befor it is set.)
 *
 * @param underFunction a reference to the to set subfunction
 * @return true if the underFunction was set, else false
 */
bool cFunction::setUnderFunction( const cUnderFunction & underFunction ){

	if ( ( & underFunction ) != NULL ){
		
		if ( pUnderFunction != NULL ){
			delete pUnderFunction;
		}
		pUnderFunction = underFunction.clone( NULL, this );
		return true;
	}//else
	return false;
}


/**
 * @return a pointer to the variable this functionelement defines
 */
cFibVariable * cFunction::getDefinedVariable(){
	return &variableDefined;
}



/**
 * This method stores this fib-object in the compressed Fib -format
 * into the given stream.
 * It is needed becouse the stream can yust store byts but the size of
 * fib-elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the fib-elements.
 * Beware: You need to call storeBit() of the root -elements with the
 * domain for the function or the function will not be readebel.
 *
 * @see store
 * @param stream the stream where this fib-object should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if this fib-object is stored, else false
 */
bool cFunction::storeBit( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{

	if ( pUnderObject == NULL ){
		return false;
	}
	const char cInitiation = 0x0B;

	const bool bInitiationStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, &cInitiation, 4 );
	if ( ! bInitiationStored ){
		return false;
	}

#ifndef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	//store the variable
	//get the domain for the variables in this vector
	cTypeVariable typeVariable;
	/*get the value domain for variables*/
	cDomains validDomains = getValidValueDomains();
	//return the variable domain
	cDomainSingle * variableDomain = (cDomainSingle*)
		validDomains.getDomainForElement( typeVariable );
	bool bStandardDomainUsed = false;
	if ( variableDomain == NULL ){
		//use the standrad domain
		variableDomain = (cDomainSingle*)typeVariable.getStandardDomain();
		bStandardDomainUsed = true;
	}
	const bool bVariableStored = variableDomain->storeValue(
		variableDefined.getValue(), stream, cRestBits, uiRestBitPosition );
	if ( bStandardDomainUsed ){
		delete variableDomain;
	}
	if ( ! bVariableStored ){
		return false;
	}
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	//store the subfunction
	if ( pUnderFunction ){
		
		const bool bUnderFunctionStored = pUnderFunction->store(
			stream, cRestBits, uiRestBitPosition );
		if ( ! bUnderFunctionStored ){
			return false;
		}
	}
	return pUnderObject->storeBit( stream, cRestBits, uiRestBitPosition );
}


/**
 * This method sets the each variable, which is defined over an leaf,
 * to an uniqe integer number greater than the given number
 * uiLastVariableNumber. While storing this number can be stored to
 * identify the variable.
 *
 * @param uiLastVariableNumber the number which was last use, this
 * 	means also is the greatest used, in this limb.
 * @return the number which was last use, this
 * 	means also is the greatest used, in this limb
 * 	from the method
 */
unsignedIntFib cFunction::enumerateVariablesForStoring(
		unsignedIntFib uiLastVariableNumber ){
	
	uiLastVariableNumber++;
	variableDefined.setIntegerValue( uiLastVariableNumber );
	
	return cFibLimb::enumerateVariablesForStoring( uiLastVariableNumber );
}


/**
 * This method copies the connected object with the given number in the
 * order of connected objects.
 * For this every fib-element, beginning from this fib-element, that
 * is part of the connected object will be copied.
 * Variables which are not defined in the connected object but used
 * don't change ther reference.
 * It is an helpmethod for the copy method. It dosn't update the
 * structural information of the created fib -object.
 *
 * @param iObjectPoint the number of the connected object to copy;
 * 	the standartvalue is 0 for coping the complet actual object
 * @return the copy of the connected object or NULL if non such exists
 */
cFibElement * cFunction::copyInternal( const unsignedIntFib iObjectPoint ) const{

	cFunction * pFunction = NULL;

	if ( pUnderObject ){
		pFunction = new cFunction( *this );
		//copy the underobject
		cFibElement * pCopyUnderobject = pUnderObject->copyInternal( iObjectPoint );
		if ( pCopyUnderobject == NULL ){
			//no such objectpoint
			delete pFunction;
			return NULL;
		}
		pCopyUnderobject->replaceVariable(
			const_cast<cFibVariable*>(&variableDefined), &(pFunction->variableDefined));
		pFunction->pUnderObject = pCopyUnderobject;
#ifdef FEATURE_FAST_UPDATE
		if ( pFunction->pUnderObject ){
			pFunction->pUnderObject->pSuperiorElement = pFunction;
		}
#endif //FEATURE_FAST_UPDATE
	}else{//no underobject
		if ( iObjectPoint == 0 ){
			//just copy if this is the correct objectpoint
			pFunction = new cFunction( *this );
		}
	}
	return pFunction;
}







