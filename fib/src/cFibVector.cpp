/**
 * @class cFibVector
 * file name: cFibVector.cpp
 * @author Betti Oesterholz
 * @date 10.05.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a basic Fib-vector.
 * Copyright (C) @c LGPL3 2009 Betti Oesterholz
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
 * This file contains the basisclass of all Fib-vectors.  It's not
 * possible to create instances from this class.
 * Thes vectors are used in Fib-elements. A vector contains a fixed
 * number of elements. Every element is an value or an Fib-Variable.
 *
 */
/*
History:
10.05.2009  Oesterholz  created
05.07.2010  Oesterholz  lowerVector() moved her from cEvaluePositionList
	and operator<() added
30.09.2010  Oesterholz  xml storing and restoring full rational number
20.02.2011  Oesterholz  sscanf() reads long long "%lld" instead of long
29.04.2011  Oesterholz  sscanf() "%lld" for windows to "%I64d"
06.06.2011  Oesterholz  the number atribute is optional in the XML-format
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
03.12.2011  Oesterholz  changes for cDomainVectorOpenEnd (store + restore
	of more elements than in the domain)
11.12.2011  Oesterholz  getCompressedSize() and store() method with
	parameters for domains added
18.04.2012  Oesterholz  Bugfix: replace FirstChild()->ToElement() with
	FirstChildElement()
18.04.2012  Oesterholz  speed up for lowerVector() with retrieving size once
17.02.2013  Oesterholz  FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE implemented
17.02.2013  Oesterholz  Bugfix: XML restore: check if pcValue is NULL
22.08.2013  Oesterholz  pow() replaced by composeDoubleFib()
26.08.2013  Oesterholz  Bugfix: storeXml() precision was to low, numbers
	got cut of, so that the restore result was not equal
03.09.2013  Oesterholz  using readDoubleFromFunction() and storeXmlDoubleFib()
	for storing and restoring Fib double numbers in XML
01.10.2013  Oesterholz  some minor changes (comments, formating, help variable)
*/

//comment in for debugging
//#define DEBUG

#include "cFibVector.h"
#include "cDomain.h"
#include "cDomains.h"
#include "cDomainSingle.h"
#include "cDomainVectorBasis.h"
#include "cDomainNaturalNumberBit.h"
#include "cTypeVariable.h"
#include "cFibElement.h"
#include "nBitStream.h"

#include <cmath>

using namespace fib;
using namespace nBitStream;



/**
 * The constructor of the vector.
 *
 * @param iNumberOfVectorElements number of elements in the vector
 * @param definingFibElement the Fib-element which defines/ uses
 * 	the vector
 */
cFibVector::cFibVector( unsignedIntFib iNumberOfVectorElements,
		cFibElement *definingFibElement ):
		liVectorType( iNumberOfVectorElements, VALUE ),
		liVectorValues( iNumberOfVectorElements, 0.0 ),
		liVectorVariable( iNumberOfVectorElements, NULL ),
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		uiNumberOfElements( iNumberOfVectorElements ),
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		pDefiningFibElement( definingFibElement ){
	DEBUG_OUT_L3(<<this<<"->cFibVector( iNumberOfVectorElements="<< iNumberOfVectorElements <<", "<<definingFibElement <<") parameter constructor"<<endl);
}

/**
 * The copy constructor of the vector.
 *
 * @param vector the vector from which to copy the data
 * @param definingFibElement the Fib-element which defines/ uses
 * 	the new vector
 */
cFibVector::cFibVector( const cFibVector & vector,
	cFibElement *definingFibElement ):
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		liVectorType( vector.uiNumberOfElements, VALUE ),
		liVectorValues( vector.uiNumberOfElements, 0.0 ),
		liVectorVariable( vector.uiNumberOfElements, NULL ),
		uiNumberOfElements( vector.uiNumberOfElements )
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		liVectorType( vector.getNumberOfElements(), VALUE ),
		liVectorValues( vector.getNumberOfElements(), 0.0 ),
		liVectorVariable( vector.getNumberOfElements(), NULL )
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		{
	
	DEBUG_OUT_L3(<<this<<"->cFibVector("<< &vector<<", "<<definingFibElement <<") copyconstructor"<<endl);
	
	if ( definingFibElement ){
		//use the given defining element
		pDefiningFibElement = definingFibElement;
	}else{
		//use the defining element of vector to copy
		pDefiningFibElement = vector.pDefiningFibElement;
	}
	
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 1;
			uiActualElement <= uiNumberOfElements; uiActualElement++ ){
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 1;
			(uiActualElement <= vector.getNumberOfElements()); uiActualElement++ ){
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		
		if ( vector.isVariable( uiActualElement ) ){
			setVariable( uiActualElement,
				(const_cast<cFibVector*>(&vector))->getVariable( uiActualElement ) );
		}else{//is value
			setValue( uiActualElement, vector.getValue( uiActualElement ) );
		}
	}
}


/**
 * The constructor for restoring a vector from an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node the vector is stored in
 * @param outStatus An reference to an integervalue where the errorvalue
 * 	can be stored to.
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElementVector
 * 		- -2 loading error, invalid data in pXmlElementVector
 * 		- 1 loading warning, invalid data in pXmlElementVector, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElementVector, maybe the loaded
 * 			object is wrong
 * @param liDefinedVariables a list with the defined variables for the
 * 	to restore vector, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 */
cFibVector::cFibVector( const TiXmlElement * pXmlElementVector, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables ):
		liVectorType( 0, VALUE ), liVectorValues( 0, 0.0 ),
		liVectorVariable( 0, (cFibVariable*)NULL ),
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		uiNumberOfElements( 0 ),
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		pDefiningFibElement( (cFibElement*)NULL ){
	
	DEBUG_OUT_L3(<<this<<"->cFibVector() rostore xml"<<endl);
	
	//check the vector type
	if ( pXmlElementVector == NULL ){
		//noting to restore
		outStatus = -1;
		return;
	}
	string szElementType( pXmlElementVector->Value() );
	if ( szElementType != "vector" ){
		//wrong element type to restore
		outStatus = -2;
		return;
	}

	//restore the elements of the vector
	const TiXmlElement * pXmlElement = NULL;
	if ( pXmlElementVector->FirstChild() ){
		
		pXmlElement = pXmlElementVector->FirstChildElement();
	}
	int iNumberOfElementLoaded = 0;
	for( int iNumberOfElement = 1; pXmlElement;
			pXmlElement = pXmlElement->NextSiblingElement(),
			iNumberOfElement++ ){
	
		const string szElementName = pXmlElement->Value();
		
		if ( pXmlElement->Attribute( "number", & iNumberOfElementLoaded ) ){
			//could read an optional number attribute
			if ( iNumberOfElementLoaded < 1 ){
				//Warning: Ther couldn't be a 0'th vector element.
				outStatus = 2;
				continue;
			}
			iNumberOfElement = iNumberOfElementLoaded;
		}
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		if ( uiNumberOfElements < (unsigned int)iNumberOfElement ){
			//resize the vector so it has a place for the new element
			liVectorType.resize( iNumberOfElement, VALUE );
			liVectorValues.resize( iNumberOfElement, 0.0 );
			liVectorVariable.resize( iNumberOfElement, NULL );
			uiNumberOfElements = iNumberOfElement;
		}
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		if ( liVectorType.size() < (unsigned int)iNumberOfElement ){
			//resize the vector so it has a place for the new element
			liVectorType.resize( iNumberOfElement, VALUE );
			liVectorValues.resize( iNumberOfElement, 0.0 );
			liVectorVariable.resize( iNumberOfElement, NULL );
		}
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		
		if ( szElementName == "value" ){
			const char * pcValue = pXmlElement->GetText();
			
			if ( pcValue == NULL ){
				DEBUG_OUT_EL2(<<"Warning: No value given"<<endl);
				outStatus = 2;
				continue;
			}
			//converting value to double
			std::pair< bool, const char * > pairOutEvalueStatus;
			setValue( iNumberOfElement,
				readDoubleFromFunction( pcValue, &pairOutEvalueStatus ) );
			if ( ! pairOutEvalueStatus.second ){
				//Warning: Error while reading the number
				outStatus = 2;
			}
		
		}else if ( szElementName == "variable" ){
		
			const char * pcValue = pXmlElement->GetText();
			
			if ( pcValue == NULL ){
				DEBUG_OUT_EL2(<<"Warning: No variable value given"<<endl);
				outStatus = 2;
				continue;
			}
			long lValue;
			const int iReadValues = sscanf( pcValue, "%ld", & lValue );
			if ( iReadValues != 1){
				//Warning: The element text is not a number.
				outStatus = 2;
				continue;
			}
			//search for the apropirate variable in the given variable list
			cFibVariable * pCorrectVariable = NULL;
			
			for ( list<cFibVariable*>::iterator itrVariable = liDefinedVariables.begin();
					itrVariable != liDefinedVariables.end(); itrVariable++ ){
				
				if ( (*itrVariable)->getIntegerValue() == lValue ){
					//correct variable to insert as the vector element found
					pCorrectVariable = *itrVariable;
					break;
				}
			}
			if ( pCorrectVariable == NULL ){
				//Warning: No such variable
				DEBUG_OUT_EL2(<<"Warning: No such variable"<<endl);
				outStatus = 2;
				continue;
			}
			setVariable( iNumberOfElement, pCorrectVariable );
			
		}else{
			//Warning: Unknown element type.
			outStatus = 2;
			continue;
		}
	}
}


/**
 * This constructor restores a poisitionsvector from the stream where it is
 * stored in the compressed Fib-format.
 *
 * @param iBitStream the stream where this vector is stored to in,
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
 * 	to restore vector, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 * @param pInVectorDomain the domain for this vector
 * @param pInDomainVariable the domain for variables
 * @param uiInNumberOfElements the number of elements to restore,
 * 	if not given or 0, it will be evalued by the number of elements of
 * 	the given domain pInVectorDomain
 */
cFibVector::cFibVector( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomain * pInVectorDomain, const cDomain * pInDomainVariable,
		const unsignedIntFib uiInNumberOfElements ){
	
	DEBUG_OUT_L3(<<this<<"->cFibVector() restore bit"<<endl);
	
	//check the stream type
	if ( ! iBitStream.getStream()->good() ){
		outStatus = -1;
		return;
	}
	if ( pInVectorDomain == NULL ){
		outStatus = -2;
		return;
	}
	string szDomainType = pInVectorDomain->getType();
	
	if ( szDomainType.compare( 0, 12, "DomainVector" ) != 0 ){
		/*if the domain is not an vector domain
		-> can't restore the vector*/
		outStatus = -2;
		return;
	}
	cDomainVectorBasis * pVectorDomain = (cDomainVectorBasis*)pInVectorDomain;
	
	if ( pInDomainVariable == NULL ){
		outStatus = -2;
		return;
	}
	
	cTypeVariable typeVariable;
	if ( ! typeVariable.isCompatible( *pInDomainVariable) ){
		/*if the variable domain is not compatible to variable type
		-> can't restore the vector*/
		outStatus = -2;
		return;
	}
	cDomainIntegerBasis * pDomainVariable = (cDomainIntegerBasis*)pInDomainVariable;

#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	uiNumberOfElements = (uiInNumberOfElements == 0)?
		pVectorDomain->getNumberOfElements() : uiInNumberOfElements;
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	const unsignedIntFib uiNumberOfElements = (uiInNumberOfElements == 0)?
		pVectorDomain->getNumberOfElements() : uiInNumberOfElements;
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	
	//resize the vector so it has a place for the new element
	liVectorType.resize( uiNumberOfElements, VALUE );
	liVectorValues.resize( uiNumberOfElements, 0.0 );
	liVectorVariable.resize( uiNumberOfElements, NULL );

	for( unsignedIntFib uiActualElement = 1;
			uiActualElement <= uiNumberOfElements; uiActualElement++ ){
		
		char cIsVariable = 0x00;
		unsigned int uiBitsRead = iBitStream.readBits( &cIsVariable, 1 );
		
		if ( uiBitsRead != 1 ){
			outStatus = -2;
			return;
		}
		if ( cIsVariable == 0x00 ){
			//the to restore element is an singlevalue
			const cDomain * pElementDomain =
				pVectorDomain->getElementDomain( uiActualElement );
			if ( pElementDomain == NULL ){
				outStatus = -2;
				return;
			}
			if ( ! pElementDomain->isScalar() ){
				//TODO change if vectors can contain not just scalars
				outStatus = -2;
				return;
			}
			doubleFib dValue = ((cDomainSingle*)pElementDomain)->
				restoreValue( iBitStream, outStatus );
			if ( outStatus < 0 ){
				return;
			}
			setValue( uiActualElement, dValue );
		
		}else{//the element is an variable
			longFib lValue = pDomainVariable->restoreIntegerValue( iBitStream, outStatus );
			if ( outStatus < 0 ){
				return;
			}
			
			//search for the apropirate variable in the given variable list
			cFibVariable * pCorrectVariable = NULL;
			
			for ( list<cFibVariable*>::iterator itrVariable = liDefinedVariables.begin();
					itrVariable != liDefinedVariables.end(); itrVariable++ ){
				
				if ( (*itrVariable)->getIntegerValue() == lValue ){
					//correct variable to insert as the vector element found
					pCorrectVariable = *itrVariable;
					break;
				}
			}
			if ( pCorrectVariable == NULL ){
				//Warning: No such variable
				outStatus = 2;
				continue;
			}
			setVariable( uiActualElement, pCorrectVariable );
		}
	}
}



/**
 * The destructor of the vector.
 */
cFibVector::~cFibVector(){
	//unregister the defining element on the variables
	DEBUG_OUT_L3(<<this<<"->~cFibVector()"<<endl);

#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 0;
			uiActualElement < uiNumberOfElements; uiActualElement++ ){
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 0;
			uiActualElement < getNumberOfElements(); uiActualElement++ ){
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		
		if ( ( liVectorType[ uiActualElement ] == VARIABLE ) &&
				( liVectorVariable[ uiActualElement ] != NULL ) ){
			//register the defining element at the variables
			DEBUG_OUT_L3(<<"liVectorVariable[ "<< uiActualElement <<" ]->unregisterUsingElement( "<<this<<" );"<<endl<<flush);
			
			liVectorVariable[ uiActualElement ]->
				unregisterUsingElement( this );
		}
	}
}


/**
 * Returns the number of elements the vector contains.
 *
 * @return the number of elements the vector contains
 */
unsignedIntFib cFibVector::getNumberOfElements() const{
	
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	DEBUG_OUT_L3(<<this<<"->cFibVector::getNumberOfElements()="<<uiNumberOfElements<<" (#typs="<<liVectorType.size()<<" #variable="<<liVectorVariable.size()<<" #value="<<liVectorValues.size()<<")"<<endl);
	return uiNumberOfElements;
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	DEBUG_OUT_L3(<<this<<"->cFibVector::getNumberOfElements()="<<liVectorType.size()<<" (#variable="<<liVectorVariable.size()<<" #value="<<liVectorValues.size()<<")"<<endl);
	return (unsignedIntFib)( liVectorType.size() );
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
}



/**
 * Returns if the iNumberElement'te vector element is an variable.
 *
 * @param iNumberElement the number of the element, for which is to
 * 	check if it is an variable
 * @return true if the iNumberElement'te vector element is an variable,
 * 	else false
 */
bool cFibVector::isVariable( unsignedIntFib iNumberElement ) const{

	DEBUG_OUT_L3(<<this<<"->cFibVector::isVariable("<<iNumberElement<<")"<<endl);
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	if ( ( iNumberElement < 1 ) || ( uiNumberOfElements < iNumberElement ) ){
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	if ( (iNumberElement < 1) || (getNumberOfElements() < iNumberElement) ){
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		//non such element
		return false;
	}

	if ( liVectorType[ iNumberElement - 1 ] == VARIABLE ){
		return true;
	}//else
	return false;
}

/**
 * This method checks if the given variable is used in this vector.
 *
 * @see cFibVariable
 * @param variable the variable to check if it is used
 * @return true if the variable is used, else false
 */
bool cFibVector::isUsedVariable( const cFibVariable * pVariable ) const{

	DEBUG_OUT_L3(<<this<<"->cFibVector::isUsedVariable("<<pVariable<<")"<<endl);
	if ( pVariable == NULL ){
		//no variable -> can't be used
		return false;
	}
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 0;
			uiActualElement < uiNumberOfElements; uiActualElement++ ){
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 0;
			uiActualElement < getNumberOfElements(); uiActualElement++ ){
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		
		if ( ( liVectorType[ uiActualElement ] == VARIABLE ) &&
				( liVectorVariable[ uiActualElement ] != NULL ) &&
				( liVectorVariable[ uiActualElement ] == pVariable ) ){
			return true;
		}
	}
	return false;
}

/**
 * This method returns all variables used in this vector.
 *
 * @see cFibVariable
 * @return all variables used in this vector
 */
set<cFibVariable*> cFibVector::getUsedVariables(){

	DEBUG_OUT_L3(<<this<<"->cFibVector::getUsedVariables()"<<endl);
	
	set<cFibVariable*> setUsedVariables;
	
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 0;
			uiActualElement < uiNumberOfElements; uiActualElement++ ){
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 0;
			uiActualElement < getNumberOfElements(); uiActualElement++ ){
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		
		if ( ( liVectorType[ uiActualElement ] == VARIABLE ) &&
				( liVectorVariable[ uiActualElement ] != NULL ) ){
			//insert the found variable
			setUsedVariables.insert( liVectorVariable[ uiActualElement ] );
		}
	}
	return setUsedVariables;
}



/**
 * This method replace the variable variableOld with the variable
 * variableNew in the vector.
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
bool cFibVector::replaceVariable( cFibVariable *variableOld,
		cFibVariable *variableNew ){
	
	DEBUG_OUT_L3(<<this<<"->cFibVector::replaceVariable("<<variableOld<<", "<<variableNew<<")"<<endl);
	
	if ( (variableOld == NULL) || (variableNew == NULL) ){
		//nothing to replace
		return false;
	}
	bool bVariableSet = true;
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 1;
			uiActualElement <= uiNumberOfElements; uiActualElement++ ){
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 1;
			uiActualElement <= getNumberOfElements(); uiActualElement++ ){
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		
		if ( ( isVariable( uiActualElement ) ) &&
				( getVariable( uiActualElement ) == variableOld ) ){
			
			bVariableSet &= setVariable( uiActualElement, variableNew );
		}
	}
	return bVariableSet;
}



/**
 * Returns the value of the iNumberElement'te vector element or
 * Nullvalue if non such exists.
 *
 * @param iNumberElement the number of the element, which value is to
 * 	return
 * @return the value of the iNumberElement'te vector element or 0 if non
 * 	such exists
 */
doubleFib cFibVector::getValue( unsignedIntFib iNumberElement ) const{
	
	DEBUG_OUT_L3(<<this<<"->cFibVector::getValue("<<iNumberElement<<")"<<endl);
	
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	if ( ( iNumberElement < 1 ) || ( uiNumberOfElements < iNumberElement ) ){
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	if ( (iNumberElement < 1) || (getNumberOfElements() < iNumberElement) ){
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		//non such element
		return (doubleFib)( 0.0 );
	}

	if ( liVectorType[ iNumberElement - 1 ] == VALUE ){

		return liVectorValues[ iNumberElement - 1 ];

	} else if ( liVectorType[ iNumberElement - 1 ] == VARIABLE ){
	
		return liVectorVariable[ iNumberElement - 1 ]->getValue();
	}
	//return the nullvalue of the domain for the element
	cDomain * pDomainForElement = getDomain( iNumberElement );
	if ( pDomainForElement ){
		return (doubleFib)( ((cDomainSingle*)(pDomainForElement))->getNull() );
	}//else return nullvalue of the standard domain for the element
	doubleFib dReturnValue = (doubleFib)(0.0);
	cDomain * pStandardDomain = getStandardDomain();

	if ( pStandardDomain == NULL ){
		//no vector standarddomain defined
		return dReturnValue;
	}
	string szDomainType = pStandardDomain->getType();
	if ( szDomainType.compare( 0, 12, "DomainVector" ) == 0 ){
		//no vector domain
		cDomainVectorBasis * pStandardVectorDomain = (cDomainVectorBasis*)pStandardDomain;
		
		if ( iNumberElement <= pStandardVectorDomain->getNumberOfElements() ){
			pDomainForElement = pStandardVectorDomain->getElementDomain( iNumberElement );
			if ( pDomainForElement ){
				dReturnValue = (doubleFib)( ((cDomainSingle*)(pDomainForElement))->getNull() );
			}
		}
	}
	delete pStandardDomain;
	//return 0
	return dReturnValue;
}


/**
 * Sets the value of the iNumberElement'te vector element.
 *
 * @param iNumberElement the number of the element, which value is to
 * 	set
 * @param dValue the value to set
 * @return true if the iNumberElement'te vector element is set to the
 * 	given value dValue, else false
 */
bool cFibVector::setValue( unsignedIntFib iNumberElement, doubleFib dValue ){

	DEBUG_OUT_L3(<<this<<"->cFibVector::setValue( "<< iNumberElement <<", "<<dValue<<" )"<<endl);
	
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	if ( ( iNumberElement < 1 ) || ( uiNumberOfElements < iNumberElement ) ){
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	if ( (iNumberElement < 1) || (getNumberOfElements() < iNumberElement) ){
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		//non such element
		return false;
	}
	//if the vector element is an variable unregister the defining -element
	if ( ( liVectorType[ iNumberElement - 1 ] == VARIABLE ) &&
			( liVectorVariable[ iNumberElement - 1 ] != NULL ) ){
		//register the defining element at the variables
		
		/*if the variable isn't used in an other element, unregister this
		vector at the variable*/
		bool bVariableIsUsedElseWhere = false;
		unsigned int uiNumberOfElements = liVectorVariable.size();
		cFibVariable * pDeletedVariable =
			liVectorVariable[ iNumberElement - 1 ];
		for ( unsigned int uiActualElement = 0;
				uiActualElement < uiNumberOfElements; uiActualElement++ ){
			
			if ( uiActualElement == iNumberElement - 1 ){
				continue;//don't check the variable to change
			}
			if ( ( liVectorType[ uiActualElement ] == VARIABLE ) &&
					( liVectorVariable[ uiActualElement ] != NULL ) &&
					( liVectorVariable[ uiActualElement ] == pDeletedVariable ) ){
				DEBUG_OUT_L4(<<"bVariableIsUsedElseWhere = true; (uiActualElement="<<uiActualElement<<")"<<endl);
				
				bVariableIsUsedElseWhere = true;
				break;
			}
		}
		if ( ! bVariableIsUsedElseWhere ){
			/*Fib variable no more used in this vector
			-> unregister this vector as a variable listener*/
			pDeletedVariable->unregisterUsingElement( this );
		}
	}//end if variable was removed
	
	liVectorType[ iNumberElement - 1 ]     = VALUE;
	liVectorValues[ iNumberElement - 1 ]   = dValue;
	liVectorVariable[ iNumberElement - 1 ] = NULL;
	
	return true;
}


/**
 * Returns the variable of the iNumberElement'te vector element or the
 * Nullpointer NULL, if the iNumberElement'te vector element isn't an
 * variable.
 *
 * @param iNumberElement the number of the element, which variable is
 * 	to return
 * @return the variable of the iNumberElement'te vector element or the
 * 	Nullpointer NULL, if the iNumberElement'te vector element isn't an
 * 	variable.
 */
cFibVariable * cFibVector::getVariable( unsignedIntFib iNumberElement ){

	DEBUG_OUT_L3(<<this<<"->cFibVector::getVariable("<<iNumberElement<<")"<<endl);
	
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	if ( ( iNumberElement < 1 ) || ( uiNumberOfElements < iNumberElement ) ){
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	if ( (iNumberElement < 1) || (getNumberOfElements() < iNumberElement) ){
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		//non such element
		return NULL;
	}
	
	if ( liVectorType[ iNumberElement - 1 ] == VARIABLE ){
	
		return liVectorVariable[ iNumberElement - 1 ];
	}
	return NULL;
}


/**
 * Sets the variable of the iNumberElement'te vector element.
 *
 * @param iNumberElement the number of the element, where the variable is
 * 	to set
 * @param pVariable the variable to set
 * @return true if the iNumberElement'te vector element is set to the
 * 	given variable pVariable, else false
 */
bool cFibVector::setVariable( unsignedIntFib iNumberElement,
		cFibVariable *pVariable ){

	DEBUG_OUT_L3(<<this<<"->cFibVector::setVariable( "<< iNumberElement <<", "<<pVariable<<" )"<<endl);
	
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	if ( ( iNumberElement < 1 ) || ( uiNumberOfElements < iNumberElement ) ){
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	if ( (iNumberElement < 1) || (getNumberOfElements() < iNumberElement) ){
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		//non such element
		return false;
	}
	if ( pVariable == NULL ){
		return false;
	}
	//if the vector element is an variable unregister the defining -element
	if ( ( liVectorType[ iNumberElement - 1 ] == VARIABLE ) &&
			( liVectorVariable[ iNumberElement - 1 ] != NULL ) ){
		//register the defining element at the variables
		
		/*if the variable isn't used in an other element, unregister this
		vector at the variable*/
		bool bVariableIsUsedElseWhere = false;
		unsigned int uiNumberOfElements = liVectorVariable.size();
		cFibVariable * pDeletedVariable =
			liVectorVariable[ iNumberElement - 1 ];
		for ( unsigned int uiActualElement = 0;
				uiActualElement < uiNumberOfElements; uiActualElement++ ){
			
			if ( uiActualElement == iNumberElement - 1 ){
				continue;//don't check the variable to change
			}
			if ( ( liVectorType[ uiActualElement ] == VARIABLE ) &&
					( liVectorVariable[ uiActualElement ] != NULL ) &&
					( liVectorVariable[ uiActualElement ] == pDeletedVariable ) ){
				DEBUG_OUT_L4(<<"bVariableIsUsedElseWhere = true; (uiActualElement="<<uiActualElement<<")"<<endl);
				
				bVariableIsUsedElseWhere = true;
				break;
			}
		}
		if ( ! bVariableIsUsedElseWhere ){
			/*Fib variable no more used in this vector
			-> unregister this vector as a variable listener*/
			pDeletedVariable->unregisterUsingElement( this );
		}
	}//end if variable was removed

	liVectorType[ iNumberElement - 1 ] = VARIABLE;
	liVectorVariable[ iNumberElement - 1 ] = pVariable;

	//register the defining element at the variable
	pVariable->registerUsingElement( this );

	return true;
}


/**
 * Returns a reference to the domain of the vector or
 * the nullpointer NULL if no domain is defined for the vector.
 * If the nullpointer NULL is returned the standarddomain is valid for the
 * vector.
 *
 * @return a reference to the definitionarea of the vector
 */
cDomainVectorBasis * cFibVector::getDomain() const{

	DEBUG_OUT_L3(<<this<<"->cFibVector::getDomain()"<<endl);
	
	if ( pDefiningFibElement == NULL ){
		//can't get enviroment/ no enviroment -> return standard domain
		return NULL;
	}
	
	/*get the domain for the type of the vector*/

	cDomains validDomains = pDefiningFibElement->getValidDomains();
	
	cTypeElement * typeElement = getElementType();
	cDomain * pDomain = validDomains.getDomainForElement( *typeElement );
	delete typeElement;
	
	if ( pDomain ){
		return (cDomainVectorBasis*)pDomain;
	}//else no domain in root -elements -> return NULL
	return NULL;
}


/**
 * Returns a reference to the valuedomain of the vector or
 * the nullpointer NULL if no valuedomain is defined for the vector.
 * If the nullpointer NULL is returned the standarddomain is valid for the
 * vector.
 *
 * @return a reference to the definitionarea of the vector
 */
cDomainVectorBasis * cFibVector::getValueDomain() const{

	DEBUG_OUT_L3(<<this<<"->cFibVector::getValueDomain()"<<endl);
	
	if ( pDefiningFibElement == NULL ){
		//can't get enviroment/ no enviroment -> return standard domain
		return NULL;
	}
	
	/*get the domain for the type of the vector*/

	cDomains validValueDomains = pDefiningFibElement->getValidValueDomains();
	
	cTypeElement * typeElement = getElementType();
	cDomain * pDomain = validValueDomains.getDomainForElement( *typeElement );
	delete typeElement;

	if ( pDomain ){
		return (cDomainVectorBasis*)pDomain;
	}//else no domain in root -elements -> return NULL
	return NULL;
}


/**
 * Returns a reference to the domain the iNumberElement'te
 * vector element or the nullpointer NULL if non exists.
 *
 * @param iNumberElement the number of the element, which
 * 	definitionarea is to return
 * @return a reference to the definitionarea of the iNumberElement'te
 * 	vector element
 */
cDomain * cFibVector::getDomain( unsignedIntFib iNumberElement ) const{

	DEBUG_OUT_L3(<<this<<"->cFibVector::getDomain("<<iNumberElement<<")"<<endl);
	
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	if ( ( iNumberElement < 1 ) || ( uiNumberOfElements < iNumberElement ) ){
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	if ( (iNumberElement < 1) || (getNumberOfElements() < iNumberElement) ){
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		//not enough elements in the vector
		return NULL;
	}
	
	if ( pDefiningFibElement == NULL ){
		//can't get enviroment/ no enviroment
		return NULL;
	}
	
	cDomainVectorBasis * domain = getDomain();

	if ( domain == NULL ){
		//no such element
		return NULL;
	}
	if ( domain->getNumberOfElements() < iNumberElement ){
		//no such element
		return NULL;
	}
	
	return domain->getElementDomain( iNumberElement );
}


/**
 * Returns a reference to the standard domain of the vector.
 * You have to delete the returned object after usage.
 *
 * @return a reference to the standard domain of the vector
 */
cDomainVectorBasis * cFibVector::getStandardDomain() const{

	DEBUG_OUT_L3(<<this<<"->cFibVector::getStandardDomain()"<<endl);
	
	cTypeElement * typeElement = getElementType();
	cDomain * domainStandard = typeElement->getStandardDomain();
	delete typeElement;
	return (cDomainVectorBasis*)domainStandard;
}


/**
 * Returns a reference to the domain for variables of the vector.
 * You have to delete the returned object after usage.
 *
 * @return a reference to the domain for variables of the vector
 */
cDomainSingle * cFibVector::getVariableDomain() const{
	
	DEBUG_OUT_L3(<<this<<"->cFibVector::getVariableDomain()"<<endl);
	
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
 * @return the Fib-element which defines/ uses this vector or
 * 	a Nullpointer NULL if non such Fib-element exists
 */
cFibElement * cFibVector::getDefiningFibElement() const{

	DEBUG_OUT_L3(<<this<<"->cFibVector::getDefiningFibElement()="<<pDefiningFibElement<<endl);
	
	return pDefiningFibElement;
}


/**
 * Sets the Fib-element which defines/ uses this vector.
 * If the given pointer is the nullpointer (standardvalue), no
 * Fib-element defines this vector.
 *
 * @param pFibElement a pointer to the Fib-element which
 * 	defines/ uses this vector
 * @param bCheckDomains getthe domains of the defining element and
 * 	check the vector elements with it
 */
void cFibVector::setDefiningFibElement( cFibElement * pFibElement,
		bool bCheckDomains ){

	DEBUG_OUT_L3(<<this<<"->cFibVector::setDefiningFibElement( "<< pFibElement <<", "<<bCheckDomains<<" )"<<endl);
	
	pDefiningFibElement = pFibElement;
	if ( bCheckDomains && pDefiningFibElement ){
		/*if ther is a new defining element, try to use the domain of the
		defining element for the vector*/
		cDomainVectorBasis * domain = getDomain();
		if ( domain != NULL ){
			
			cFibVector * roundedVector = domain->round( *this );
			
			if ( roundedVector == NULL ){
				return;//no elements to copy
			}
			//set the correct number of vector elements
			const unsigned int uiNumberOfVectorElements =
				domain->getNumberOfElements();
			
			//unregister this vector from all variables
#ifndef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
			const unsigned int uiNumberOfElements = liVectorVariable.size();
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
			for ( unsigned int uiActualElement = 0;
					uiActualElement < uiNumberOfElements; uiActualElement++ ){
				
				if ( ( liVectorType[ uiActualElement ] == VARIABLE ) &&
						( liVectorVariable[ uiActualElement ] != NULL ) ){
					//unregister this element as variable user
					liVectorVariable[ uiActualElement ]->unregisterUsingElement( this );
				}
			}
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
			uiNumberOfElements = uiNumberOfVectorElements;
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
			liVectorType = vector<eVectorType>( uiNumberOfVectorElements, VALUE );
			liVectorValues = vector<doubleFib>( uiNumberOfVectorElements, 0 );
			liVectorVariable = vector<cFibVariable*>( uiNumberOfVectorElements, NULL );
			
			//set the correct vector elementvalues
			for ( unsigned int uiActualElement = 1;
					uiActualElement <= uiNumberOfVectorElements; uiActualElement++ ){
				
				if ( roundedVector->isVariable( uiActualElement ) ){
					setVariable( uiActualElement,
						roundedVector->getVariable( uiActualElement ) );
				}else{//is value
					setValue( uiActualElement, roundedVector->getValue( uiActualElement ) );
				}
			}
			delete roundedVector;
		}
	}
}


/**
 * This method evaluades the size of the Fib-object in bits in the
 * compressed file form.
 *
 * @see store()
 * @return the size of the Fib-object in bits in the compressed form
 */
unsignedLongFib cFibVector::getCompressedSize() const{
	
	DEBUG_OUT_L3(<<this<<"->cFibVector::getCompressedSize()"<<endl);
	
	//get the domain for the values in this vector
	cDomain * pValueDomain = getValueDomain();
	
	const bool bStandardValueDomain = ( pValueDomain == NULL );
	if ( bStandardValueDomain ){
		pValueDomain = getStandardDomain();
	}
	cDomainVectorBasis * pValueVectorDomain = (cDomainVectorBasis*)pValueDomain;

	//get the domain for the variables in this vector
	cDomainSingle * pVariableDomain = getVariableDomain();
	if ( pVariableDomain == NULL ){
		//Error: no variable domain
		return 0;
	}
	const unsignedLongFib ulCompressedSize =
		getCompressedSize( *pValueVectorDomain, *pVariableDomain );
	
	if ( bStandardValueDomain ){
		delete pValueDomain;
	}
	delete pVariableDomain;
	
	return ulCompressedSize;
}


/**
 * This method evaluades the size of the Fib-object in bits in the
 * compressed file form.
 *
 * @see store()
 * @param valueVectorDomain the domain for this vector
 * @param variableDomain the domain for variables
 * @return the size of the Fib-object in bits in the compressed form
 */
unsignedLongFib cFibVector::getCompressedSize(
		const cDomainVectorBasis & valueVectorDomain,
		const cDomainSingle & variableDomain ) const{
	
	//add the bits for the elements
	const unsigned int uiNumberOfElements = liVectorVariable.size();
	//add bits vor the variable/value bit of each element
#ifdef FEATURE_FIB_VECTOR_STORE_JUST_DOMAIN
	unsignedLongFib ulCompressedSize = 0;
	
	for ( unsigned int uiActualElement = 0;
			uiActualElement < uiNumberOfElements; uiActualElement++ ){
		
		const cDomain * pElementDomain =
			valueVectorDomain.getElementDomain( uiActualElement + 1 );
		if ( pElementDomain != NULL ){
			ulCompressedSize++;
			if ( liVectorType[ uiActualElement ] == VARIABLE ){
				
				ulCompressedSize += variableDomain.getCompressedSizeForValue();
			}else{//get bits for storing a value
				
				if ( pElementDomain->isScalar() ){
					
					ulCompressedSize += ((cDomainSingle*)(pElementDomain))->
						getCompressedSizeForValue();
				}//else TODO if the vector can contain other elements as scalars
			}
		}//no such domain element -> don't store anything
	}
#else //FEATURE_FIB_VECTOR_STORE_JUST_DOMAIN
	unsignedLongFib ulCompressedSize = uiNumberOfElements;
	
	for ( unsigned int uiActualElement = 0;
			uiActualElement < uiNumberOfElements; uiActualElement++ ){
		
		if ( liVectorType[ uiActualElement ] == VARIABLE ){
			
			ulCompressedSize += variableDomain.getCompressedSizeForValue();
		}else{//get bits for storing a value
			
			const cDomain * pElementDomain =
				valueVectorDomain.getElementDomain( uiActualElement + 1 );
			if ( pElementDomain != NULL ){
				if ( pElementDomain->isScalar() ){
					
					ulCompressedSize += ((cDomainSingle*)(pElementDomain))->
						getCompressedSizeForValue();
				}//else TODO if the vector can contain other elements as scalars
			}else{//add 16 bits the standardomain naturalNumberB( 16 )
				ulCompressedSize += 16;
			}
		}
	}
#endif //FEATURE_FIB_VECTOR_STORE_JUST_DOMAIN
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
bool cFibVector::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	DEBUG_OUT_L3(<<this<<"->cFibVector::store()"<<endl);
	
	//get the domain for the values in this vector
	cDomain * pValueDomain = getValueDomain();
	
	const bool bStandardValueDomain = ( pValueDomain == NULL );
	if ( bStandardValueDomain ){
		pValueDomain = getStandardDomain();
	}
	cDomainVectorBasis * pValueVectorDomain = (cDomainVectorBasis*)pValueDomain;

	//get the domain for the variables in this vector
	cDomainSingle * pVariableDomain = getVariableDomain();
	
	const bool bReturnValue = store( stream, cRestBits,
		uiRestBitPosition, *pValueVectorDomain, *pVariableDomain );
	if ( bStandardValueDomain ){
		delete pValueDomain;
	}
	delete pVariableDomain;
	
	return bReturnValue;
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
 * @param valueVectorDomain the domain for this vector
 * @param variableDomain the domain for variables
 * @return true if this Fib-object is stored, else false
 */
bool cFibVector::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition,
		const cDomainVectorBasis & valueVectorDomain,
		const cDomainSingle & variableDomain ) const{
	
	bool bReturnValue = true;
	//write the bits for the elements
#ifndef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	const unsigned int uiNumberOfElements = getNumberOfElements();
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	
#ifdef FEATURE_FIB_VECTOR_STORE_JUST_DOMAIN
	for ( unsigned int uiActualElement = 1;
			uiActualElement <= uiNumberOfElements; uiActualElement++ ){
		
		const cDomain * pElementDomain =
			valueVectorDomain.getElementDomain( uiActualElement );
		if ( pElementDomain != NULL ){
			if ( isVariable( uiActualElement ) ){
				//store variable
				const char cTypeBit = 0x01;
				bool bVariableStored = nBitStream::store( stream, cRestBits,
					uiRestBitPosition, &cTypeBit, 1 );
				bVariableStored &= variableDomain.storeValue(
					getValue( uiActualElement ), stream, cRestBits, uiRestBitPosition );
				if ( ! bVariableStored ){
					bReturnValue = false;
					break;
				}
			}else{//store value
				const char cTypeBit = 0x00;
				bool bValueStored = nBitStream::store( stream, cRestBits,
					uiRestBitPosition, &cTypeBit, 1 );
				if ( pElementDomain->isScalar() ){
					//store with scalar domain
					bValueStored &= ((cDomainSingle*)(pElementDomain))->storeValue(
						getValue( uiActualElement ), stream, cRestBits, uiRestBitPosition );
				}else{//TODO if the vector can contain other elements as scalars
					bReturnValue = false;
					break;
				}
				if ( ! bValueStored ){
					bReturnValue = false;
					break;
				}
			}
		}//no such domain element -> don't store anything
	}
#else //FEATURE_FIB_VECTOR_STORE_JUST_DOMAIN
	for ( unsigned int uiActualElement = 1;
			uiActualElement <= uiNumberOfElements; uiActualElement++ ){
		
		if ( isVariable( uiActualElement ) ){
			//store variable
			const char cTypeBit = 0x01;
			bool bVariableStored = nBitStream::store( stream, cRestBits,
				uiRestBitPosition, &cTypeBit, 1 );
			bVariableStored &= variableDomain.storeValue(
				getValue( uiActualElement ), stream, cRestBits, uiRestBitPosition );
			if ( ! bVariableStored ){
				bReturnValue = false;
				break;
			}
		}else{//store value
			const char cTypeBit = 0x00;
			bool bValueStored = nBitStream::store( stream, cRestBits,
				uiRestBitPosition, &cTypeBit, 1 );
			const cDomain * pElementDomain =
				valueVectorDomain.getElementDomain( uiActualElement );
			if ( pElementDomain != NULL ){
				if ( pElementDomain->isScalar() ){
					//store with scalar domain
					bValueStored &= ((cDomainSingle*)(pElementDomain))->storeValue(
						getValue( uiActualElement ), stream, cRestBits, uiRestBitPosition );
				}else{//TODO if the vector can contain other elements as scalars
					bReturnValue = false;
					break;
				}
			}else{//write with a 16 bits the standardomain naturalNumberB( 16 )
				cDomainNaturalNumberBit domainNaturalNumberB16( 16 );
				bValueStored &= domainNaturalNumberB16.storeValue(
					getValue( uiActualElement ), stream, cRestBits, uiRestBitPosition );
			}
			if ( ! bValueStored ){
				bReturnValue = false;
				break;
			}
		}
	}
#endif //FEATURE_FIB_VECTOR_STORE_JUST_DOMAIN
	return bReturnValue;
}


/**
 * This method stores this vector in the XML -format into the
 * given stream.
 * Variables should have ther number as ther value.
 *
 * @param stream the stream where this vectorshould be stored to
 * @return true if this vector is stored, else false
 */
bool cFibVector::storeXml( ostream &stream ) const{
	
	DEBUG_OUT_L3(<<this<<"->cFibVector::storeXml()"<<endl);
	
	stream<<"<vector type=\""<< getVectorType() <<"\">"<<endl;
	//store the vector elements
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 0;
			uiActualElement < uiNumberOfElements; uiActualElement++ ){
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 0;
			uiActualElement < getNumberOfElements(); uiActualElement++ ){
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE

#ifdef FEATURE_STORE_VECTOR_ELEMENT_NUMBER
		if ( liVectorType[uiActualElement] == VALUE ){
			//store a value
			stream<<"<value number=\""<< uiActualElement + 1 <<"\">";
			storeXmlDoubleFib( stream, liVectorValues[uiActualElement] );
			stream<<"</value>"<<endl;
			
		}else if ( liVectorType[uiActualElement] == VARIABLE ){
			//store a variable
			if ( liVectorVariable[uiActualElement]->isIntegerValue() ){
				stream<<"<variable number=\""<< uiActualElement + 1 <<"\">"<<
					liVectorVariable[uiActualElement]->getIntegerValue()
					<<"</variable>"<<endl;
			}else{//real value
				stream<<"<variable number=\""<< uiActualElement + 1 <<"\">"<<
					liVectorVariable[uiActualElement]->getValue()
					<<"</variable>"<<endl;
			}
		}else{//undefined
			stream<<"<undefined number=\""<< uiActualElement + 1 <<"\"/>"<<endl;
		}
#else //FEATURE_STORE_VECTOR_ELEMENT_NUMBER
		if ( liVectorType[uiActualElement] == VALUE ){
			//store a value
			stream<<"<value>";
			const doubleFib dValue = liVectorValues[uiActualElement];
			if ( ( -1000000 < dValue ) && ( dValue < 1000000 ) &&
					(((doubleFib)((longFib)( dValue * 100.0 ))) / 100.0) == dValue ){
				//number with no more than 6 digits befor and 2 digits after the point
				stream.precision( 9 );
				stream<< dValue <<"</value>"<<endl;
			}else{
				longFib lMantissa;
				longFib lExponent;
				
				decomposeDoubleFib( dValue, & lMantissa, & lExponent );
				
				stream<< lMantissa <<" * 2^("<< lExponent <<")</value>"<<endl;
			}
	
		}else if ( liVectorType[uiActualElement] == VARIABLE ){
			//store a variable
			if ( liVectorVariable[uiActualElement]->isIntegerValue() ){
				stream<<"<variable>"<<
					liVectorVariable[uiActualElement]->getIntegerValue()
					<<"</variable>"<<endl;
			}else{//real value
				stream<<"<variable>"<<
					liVectorVariable[uiActualElement]->getValue()
					<<"</variable>"<<endl;
			}
		}else{//undefined
			stream<<"<undefined/>"<<endl;
		}
#endif //FEATURE_STORE_VECTOR_ELEMENT_NUMBER
	}
	stream<<"</vector>"<<endl;

	return true;
}


#ifdef FEATURE_EQUAL_FIB_OBJECT

/**
 * This method checks if the given vector is equal to this vector.
 *
 * @param vector the vector to compare with this vector
 * @param bCheckExternalObjects if true the external objects of
 * 	cExtObject will be compared
 * @return true if the given vector is equal to this vector, else false
 */
bool cFibVector::equal( const cFibVector &vector,
		const bool bCheckExternalObjects ) const{
	
	map< const cRoot *, const cRoot * > mapEqualRootObjects;
	map< const cFibElement *, const cFibElement * > mapEqualDefinedVariables;
	
	return equalInternal( vector,
		mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects );
}


/**
 * This method checks if the given vector is equal to this vector.
 *
 * @param vector the vector to compare with this vector
 * @return true if the given vector is equal to this vector, else false
 */
bool cFibVector::operator==( const cFibVector &vector ) const{
	
	map< const cRoot *, const cRoot * > mapEqualRootObjects;
	map< const cFibElement *, const cFibElement * > mapEqualDefinedVariables;
	
	return equalInternal( vector,
		mapEqualRootObjects, mapEqualDefinedVariables, true );
}


/**
 * This method checks if the given vector is not equal to this vector.
 *
 * @param vector the vector to compare with this vector
 * @return true if the given vector is not equal to this vector, else false
 */
bool cFibVector::operator!=( const cFibVector &vector ) const{
	
	map< const cRoot *, const cRoot * > mapEqualRootObjects;
	map< const cFibElement *, const cFibElement * > mapEqualDefinedVariables;
	
	return ! equalInternal( vector,
		mapEqualRootObjects, mapEqualDefinedVariables, true );
}


/**
 * This method checks if the given variable is equal to this variable.
 *
 * @param vector the vector to compare with this vector
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
bool cFibVector::equalInternal( const cFibVector &vector,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{
	
	DEBUG_OUT_L3(<<this<<"->cFibVector::equalInternal("<<&vector<<", setEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects )"<<endl);
	
	if ( getVectorType() != vector.getVectorType() ){
		//the vector typs are not equal
		return false;
	}
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	if ( uiNumberOfElements != vector.uiNumberOfElements ){
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	if ( getNumberOfElements() != vector.getNumberOfElements() ){
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		//non such element
		return false;
	}
	
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 0;
			uiActualElement < uiNumberOfElements; uiActualElement++ ){
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 0;
			uiActualElement < getNumberOfElements(); uiActualElement++ ){
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		
		if ( liVectorType[ uiActualElement ] != vector.liVectorType[ uiActualElement ] ){
			return false;
		}
		if ( liVectorType[ uiActualElement ] == VALUE ){
			//compare the values
			if ( liVectorValues[ uiActualElement ] !=
					vector.liVectorValues[ uiActualElement ] ){
				return false;
			}
		}else if ( liVectorType[ uiActualElement ] == VARIABLE ){
			//compare the variables
			if ( ! ( liVectorVariable[ uiActualElement ]->equalInternal(
					*(vector.liVectorVariable[ uiActualElement ]),
					mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ) ){
				return false;
			}
		}
	}
	return true;
}

#else //FEATURE_EQUAL_FIB_OBJECT

/**
 * This method checks if the given vector is equal to this vector.
 *
 * @param vector the vector to compare with this vector
 * @return true if the given vector is equal to this vector, else false
 */
bool cFibVector::equal( const cFibVector &vector ) const{
	
	DEBUG_OUT_L3(<<this<<"->cFibVector::equal("<<&vector<<")"<<endl);
	
	return ((*this) == vector);
}


/**
 * This method checks if the given vector is equal to this vector.
 *
 * @param vector the vector to compare with this vector
 * @return true if the given vector is equal to this vector, else false
 */
bool cFibVector::operator==( const cFibVector &vector ) const{
	
	DEBUG_OUT_L3(<<this<<"->cFibVector::operator==("<<&vector<<")"<<endl);
	
	if ( getVectorType() != vector.getVectorType() ){
		//the vectortyps are not equal
		return false;
	}
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	if ( uiNumberOfElements != vector.uiNumberOfElements ){
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	if ( getNumberOfElements() != vector.getNumberOfElements() ){
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		//non such element
		return false;
	}
	
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 0;
			uiActualElement < uiNumberOfElements; uiActualElement++ ){
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 0;
			uiActualElement < getNumberOfElements(); uiActualElement++ ){
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		
		if ( liVectorType[uiActualElement] != vector.liVectorType[uiActualElement] ){
			return false;
		}
		if ( liVectorType[uiActualElement] == VALUE ){
			//compare the values
			if ( liVectorValues[uiActualElement] !=
					vector.liVectorValues[uiActualElement] ){
				return false;
			}
		}else if ( liVectorType[uiActualElement] == VARIABLE ){
			//compare the variables
			if ( !( *(liVectorVariable[uiActualElement]) ==
					*(vector.liVectorVariable[uiActualElement]) ) ){
				return false;
			}
		}
	}
	return true;
}


/**
 * This method checks if the given vector is not equal to this vector.
 *
 * @param vector the vector to compare with this vector
 * @return true if the given vector is not equal to this vector, else false
 */
bool cFibVector::operator!=( const cFibVector &vector ) const{
	
	DEBUG_OUT_L3(<<this<<"->cFibVector::operator!=("<<&vector<<")"<<endl);
	
	return ! ((*this) == vector);
}

#endif //FEATURE_EQUAL_FIB_OBJECT


/**
 * This method makes this vector elements equal to the correspondending
 * vector elements of the given vector.
 * The type of the vector won't be changed.
 *
 * @param vector the vector to copy
 */
cFibVector & cFibVector::operator=( const cFibVector &inVector ){
	DEBUG_OUT_L3(<<this<<"->cFibVector::operator=( "<<&inVector<<" )"<<endl);
	
	//unregister this element as variable listener at all variables
#ifndef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	unsigned int uiNumberOfElements = getNumberOfElements();
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 0;
			uiActualElement < uiNumberOfElements; uiActualElement++ ){
		
		if ( ( liVectorType[ uiActualElement ] == VARIABLE ) &&
				(liVectorVariable[ uiActualElement ] != NULL) ){
			liVectorVariable[ uiActualElement ]->unregisterUsingElement( this );
		}
	}
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	uiNumberOfElements = inVector.getNumberOfElements();
	liVectorType     = vector<eVectorType>( uiNumberOfElements, VALUE );
	liVectorValues   = vector<doubleFib>( uiNumberOfElements, 0 );
	liVectorVariable = vector<cFibVariable*>( uiNumberOfElements, NULL );
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	liVectorType     = vector<eVectorType>( inVector.getNumberOfElements(), VALUE );
	liVectorValues   = vector<doubleFib>( inVector.getNumberOfElements(), 0 );
	liVectorVariable = vector<cFibVariable*>( inVector.getNumberOfElements(), NULL );
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 1;
			uiActualElement <= uiNumberOfElements; uiActualElement++ ){
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 1;
			uiActualElement <= getNumberOfElements(); uiActualElement++ ){
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		
		if ( inVector.isVariable( uiActualElement ) ){
			setVariable( uiActualElement,
				(const_cast<cFibVector*>(&inVector))->getVariable( uiActualElement ) );
		}else{
			setValue( uiActualElement, inVector.getValue( uiActualElement ) );
		}
	}
	return (*this);
}


/**
 * This function compares on lower this vector with the given Fib-vectors.
 * A this vector is lower, if it has less elements than the other vector or
 * it's i'th element is lower and all j'th elements with i > j are equal.
 *
 * @param vector the vector to compare
 * @return true if this vector is lower than that of vector, else false
 */
bool cFibVector::operator<( const cFibVector & vector ) const{

	return lowerVector( *this, vector);
}


/**
 * This function compares two Fib-vectors.
 * A vector is lower, if it has less elements than the other vector or
 * it's i'th element is lower and all j'th elements with i > j are equal.
 *
 * @param vector1 the first vector to compare
 * @param vector2 the second vector to compare
 * @return true if the vector1 is lower than that of vector2, else false
 */
bool cFibVector::lowerVector( const cFibVector & vector1,
	const cFibVector & vector2 ){
	
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	const unsignedIntFib & uiCountOfVectorElements  = vector1.uiNumberOfElements;
	const unsignedIntFib & uiCountOfVector2Elements = vector2.uiNumberOfElements;
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	const unsignedIntFib uiCountOfVectorElements  = vector1.getNumberOfElements();
	const unsignedIntFib uiCountOfVector2Elements = vector2.getNumberOfElements();
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	if ( uiCountOfVectorElements != uiCountOfVector2Elements ){
		
		if ( uiCountOfVectorElements < uiCountOfVector2Elements ){
			return true;
		}//else if ( uiCountOfVector2Elements < uiCountOfVectorElements ){
		return false;
		
	}//else (vector1.getNumberOfElements() == vector2.getNumberOfElements())
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= uiCountOfVectorElements; uiActualElement++ ){
		
		if ( vector1.getValue( uiActualElement ) < vector2.getValue( uiActualElement ) ){
			return true;
		}
		if ( vector2.getValue( uiActualElement ) < vector1.getValue( uiActualElement ) ){
			return false;
		}
	}
	
	return false;
}


/**
 * @return the Fib-element which uses the variables of this element
 */
cFibElement * cFibVector::getVariableUsingFibElement() const{
	DEBUG_OUT_L3(<<this<<"->cFibVector::getVariableUsingFibElement()"<<endl);
	return getDefiningFibElement();
}


/**
 * This method deletes all occurenc of the given variable from this
 * element. So the variable is not used anymore of this element.
 * Beware: This element has to be unregisterd (call
 * unregisterUsingElement() ) at the pVariable seperatly. Do this directly
 * befor or after calling this method.
 *
 * @param pVariable the variable which is to delete from this element
 * @return true if the variable dosn't occure anymore in this element,
 * 	else false
 */
bool cFibVector::deleteVariable( cFibVariable * pVariable ){

	DEBUG_OUT_L3(<<this<<"->cFibVector::deleteVariable( "<< pVariable<<" )"<<endl);
	
	if ( pVariable == NULL ){
		//no variable to delete
		return false;
	}
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 0;
			uiActualElement < uiNumberOfElements; uiActualElement++ ){
#else //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = 0;
			uiActualElement < getNumberOfElements(); uiActualElement++ ){
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		
		if ( ( liVectorType[ uiActualElement ] == VARIABLE ) &&
				( liVectorVariable[ uiActualElement ] != NULL ) &&
				( liVectorVariable[ uiActualElement ] == pVariable ) ){
			//replace the variable with undefined
			
			liVectorType[ uiActualElement ] = VALUE;
			if ( pVariable->isSet() ){
				liVectorValues[ uiActualElement ] = pVariable->getValue();
			}else{
				liVectorValues[ uiActualElement ] = 0;
			}
			liVectorVariable[ uiActualElement ] = NULL;
		}
	}

	return true;
}





