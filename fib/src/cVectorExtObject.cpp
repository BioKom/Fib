/**
 * @class cVectorExtObject
 * file name: cVectorExtObject.cpp
 * @author Betti Oesterholz
 * @date 22.01.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a external object element vector.
 * Copyright (C) @c LGPL3 2012 Betti Oesterholz
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
 * This class represents a external object element vector of the
 * Fib multimedia language.
 * It is a vector for external object element input variables.
 *
 */
/*
History:
22.01.2012  Oesterholz  created
17.02.2013  Oesterholz FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE implemented
*/


#include "cVectorExtObject.h"
#include "cFibElement.h"
#include "cExtObject.h"
#include "cTypeExtObjectInput.h"
#include "cDomains.h"


using namespace fib;


/**
 * The constructor of the external object element vector.
 *
 * @param iNumberOfElements the number of elements the vector should have
 * @param pDefiningElement the Fib element which
 * 	defines/ uses the external object element vector
 */
cVectorExtObject::cVectorExtObject( unsignedIntFib iNumberOfElements,
		cFibElement * pDefiningExtObject ):
		cFibVector( iNumberOfElements, pDefiningExtObject ){
	//noting to do
}


/**
 * The constructor of the external object element vector.
 *
 * @param definingExtObject the Fib external object element which
 * 	defines/ uses the external object element vector
 */
cVectorExtObject::cVectorExtObject( cExtObject & definingExtObject ){
	
	pDefiningFibElement = & definingExtObject;

	/* the number of vector elements is equal to the number of vector
	elements of the external object element*/
	//TODO use the domain
	unsignedIntFib uiNumberOfVectorElements = 0;
	cDomainVectorBasis * pVectorDomain = getDomain();
	if ( pVectorDomain ){
		uiNumberOfVectorElements = pVectorDomain->getNumberOfElements();
	}
	
	//init the vector elements
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	uiNumberOfElements = uiNumberOfVectorElements;
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	liVectorType.resize( uiNumberOfVectorElements, VALUE );
	liVectorValues.resize( uiNumberOfVectorElements, 0 );
	liVectorVariable.resize( uiNumberOfVectorElements, NULL );
	//nothing to do
}



/**
 * The copy constructor of the vector.
 *
 * @param vector the vector from which to copy the data
 * @param pDefiningFibElement the Fib -element which defines/ uses
 * 	the new vector
 */
cVectorExtObject::cVectorExtObject( const cVectorExtObject & vector,
		cFibElement *pDefiningFibElement ):
		cFibVector( vector, pDefiningFibElement ){
	DEBUG_OUT_L3(<<this<<"->cVectorExtObject("<<&vector<<", "<<definingFibElement<<") copy constructor"<<endl);
}


/**
 * The constructor for restoring a vector from an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node the vector is stored in
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
 * 	to restore vector, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 */
cVectorExtObject::cVectorExtObject( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables ):
		cFibVector( pXmlElement, outStatus, liDefinedVariables ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorExtObject() constructor restore xml"<<endl);
	
	//check the vector type
	if ( pXmlElement == NULL ){
		//noting to restore
		outStatus = -1;
		return;
	}
	if ( outStatus < 0 ){
		//an error occured while restoring the vector
		return;
	}
	//check the attribute of the vector
	const char * szVectorXmlType = pXmlElement->Attribute( "type" );
	
	if ( szVectorXmlType == NULL ){
		outStatus = 2;
		return;
	}else if ( strcmp( "externObjectInput", szVectorXmlType ) != 0 ){
		outStatus = 2;
		return;
	}
}

/**
 * This constructor restores a external object element vector from the stream where it is
 * stored in the compressed Fib format.
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
cVectorExtObject::cVectorExtObject( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomain * pInVectorDomain, const cDomain * pInDomainVariable,
		const unsignedIntFib uiInNumberOfElements ):
		cFibVector( iBitStream, outStatus, liDefinedVariables,
			pInVectorDomain, pInDomainVariable, uiInNumberOfElements ){
	//nothing to do
	DEBUG_OUT_L3(<<this<<"->cVectorExtObject() constructor restore bit"<<endl);
}


/**
 * This method creates an instance of this vector type.
 *
 * @param iNumberOfVectorElements number of elements in the vector
 * @param definingPropertyElement the Fib external object element which
 * 	defines/ uses the external object element
 */
cVectorExtObject * cVectorExtObject::createInstance(
		unsignedIntFib iNumberOfVectorElements,
		cFibElement *pDefiningElement ) const{

	DEBUG_OUT_L3(<<this<<"->cVectorExtObject::createInstance("<<iNumberOfVectorElements<<", "<<pDefiningElement<<")"<<endl);
	
	return new cVectorExtObject( iNumberOfVectorElements, pDefiningElement );
}


/**
 * Returns the type of the vector.
 * You have to delete the returned object after usage.
 *
 * @return the type of the vector
 */
cTypeElement * cVectorExtObject::getElementType() const{
	
	DEBUG_OUT_L3(<<this<<"->cVectorExtObject::getElementType()"<<endl);
	
	/*the type is dimension type*/
	if ( pDefiningFibElement != NULL ){
		//try to evalue type with the help of the defining Fib element
		if ( pDefiningFibElement->getType() != 'o' ){
			/*not a external object element defines this vector
			-> return the standard type /  use 0'th domain*/
			return new cTypeExtObjectInput( 0 );
		}
		const longFib lIdentifier =
			((cExtObject*)pDefiningFibElement)->getIdentifier();
		return new cTypeExtObjectInput( lIdentifier );
	}//else no type found -> return the standard type /  use 0'th domain

	return new cTypeExtObjectInput( 0 );
}


/**
 * Returns a reference to the domain of the vector or
 * the nullpointer NULL if no domain is defined for the vector.
 * If the nullpointer NULL is returned the standarddomain is valid for the
 * vector.
 *
 * @return a reference to the definitionarea of the vector
 */
cDomainVectorBasis * cVectorExtObject::getDomain() const{

	DEBUG_OUT_L3(<<this<<"->cVectorExtObject::getDomain()"<<endl);
	
	if ( pDefiningFibElement == NULL ){
		//can't get enviroment/ no enviroment -> return standard domain
		return NULL;
	}
	
	/*get the domain for the type of the vector*/
	cDomains validDomains = pDefiningFibElement->getValidDomains();
	
	cTypeElement * pTypeElement = getElementType();
	if ( pTypeElement == NULL ){
		//error in domain: not a domain or not a vector domain)
		return NULL;
	}
	cDomain * pDomain = validDomains.getDomainForElement( *pTypeElement );
	delete pTypeElement;
	
	if ( ( pDomain == NULL ) || ( ! pDomain->isVector() ) ){
		//error in domain: not a domain or not a vector domain)
		return NULL;
	}
	
	return (cDomainVectorBasis*)pDomain;
}


/**
 * Returns a reference to the standard domain of the vector.
 * You have to delete the returned object after usage.
 *
 * @return a reference to the standard domain of the vector
 */
cDomainVectorBasis * cVectorExtObject::getStandardDomain() const{

	DEBUG_OUT_L3(<<this<<"->cVectorExtObject::getStandardDomain()"<<endl);
	
	const cTypeElement * pTypeElement = getElementType();
	if ( pTypeElement == NULL ){
		//error in domain: not a domain or not a vector domain)
		return NULL;
	}
	cDomain * pDomainStandardExtObject = pTypeElement->getStandardDomain();
	delete pTypeElement;
	
	if ( pDomainStandardExtObject == NULL ){
		//error in domain: not a domain
		return NULL;
	}
	if ( ! pDomainStandardExtObject->isVector() ){
		//error in domain: not a vector domain
		delete pDomainStandardExtObject;
		return NULL;
	}
	return (cDomainVectorBasis*)pDomainStandardExtObject;
}


/**
 * Returns a reference to the valuedomain of the vector or
 * the nullpointer NULL if no valuedomain is defined for the vector.
 * If the nullpointer NULL is returned the standarddomain is valid for the
 * vector.
 *
 * @return a reference to the definitionarea of the vector
 */
cDomainVectorBasis * cVectorExtObject::getValueDomain() const{
	
	DEBUG_OUT_L3(<<this<<"->cVectorExtObject::getValueDomain()"<<endl);
	
	if ( pDefiningFibElement == NULL ){
		//can't get enviroment/ no enviroment -> return standard domain
		return NULL;
	}
	
	//get the domain for the type of the vector
	cDomains validValueDomains = pDefiningFibElement->getValidValueDomains();
	
	cTypeElement * pTypeElement = getElementType();
	if ( pTypeElement == NULL ){
		//error in domain: not a domain or not a vector domain)
		return NULL;
	}
	cDomain * pDomain = validValueDomains.getDomainForElement( *pTypeElement );
	delete pTypeElement;

	if ( ( pDomain == NULL ) || ( ! pDomain->isVector() ) ){
		//error in domain: not a domain or not a vector domain)
		return NULL;
	}
	return (cDomainVectorBasis*)pDomain;
}


/**
 * @return the name for the type of the vector
 */
string cVectorExtObject::getVectorType() const{
	
	DEBUG_OUT_L3(<<this<<"->cVectorExtObject::getVectorType()"<<endl);
	
	return "externObjectInput";
}


/**
 * Sets the Fib-element which defines/ uses this vector.
 * If the given pointer is the nullpointer (standardvalue), no
 * Fib-element defines this vector.
 *
 * @param pFibElement a pointer to the Fib-element which
 * 	defines/ uses this vector
 * @param bCheckDomains getthe domains of the defining element and
 * 	check the vectorelements with it
 */
void cVectorExtObject::setDefiningFibElement( cFibElement * pFibElement,
		bool bCheckDomains ){

	DEBUG_OUT_L3(<<this<<"->cVectorExtObject::setDefiningFibElement( "<< pFibElement <<", "<<bCheckDomains<<" )"<<endl);
	
	pDefiningFibElement = pFibElement;
	if ( bCheckDomains && pDefiningFibElement ){
		/*if ther is a new defining element, try to use the pDomain of the
		defining element for the vector*/
		cDomainVectorBasis * pDomain = getDomain();
		if ( pDomain != NULL ){
			
			cFibVector * roundedVector = pDomain->round( *this );
			
			if ( roundedVector == NULL ){
				return;//no elements to copy
			}
			//set the correct number of vector elements
			/*the number of vector elements is equal to the number of
			 vector pDomain elements*/
			unsigned int uiNumberOfVectorElements = pDomain->getNumberOfElements();;
			if ( ( pDefiningFibElement->getType() == 'o' ) &&
					pDomain->getType().compare( "DomainVectorOpenEnd" ) == 0 ){
				//open end vector domain -> vector can be bigger as domain number of elements
				const unsigned int uiNumberOfExtObjectVectorElements = 
					((cExtObject*)(pDefiningFibElement))->getNumberOfInputValues();;
				//take the bigger of the two numbers
				uiNumberOfVectorElements =
					( uiNumberOfExtObjectVectorElements < uiNumberOfVectorElements )?
					uiNumberOfVectorElements : uiNumberOfExtObjectVectorElements;
			}
			
			//unregister this vector from all to much variables
#ifndef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
			const unsigned int uiNumberOfElements = liVectorVariable.size();
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
			for ( unsigned int uiActualElement = uiNumberOfVectorElements;
					uiActualElement < uiNumberOfElements; uiActualElement++ ){
				
				if ( ( liVectorType[ uiActualElement ] == VARIABLE ) &&
						(liVectorVariable[ uiActualElement ] != NULL) ){
					liVectorVariable[ uiActualElement ]->unregisterUsingElement( this );
				}
			}
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
			uiNumberOfElements = uiNumberOfVectorElements;
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
			liVectorType = vector<eVectorType>( uiNumberOfVectorElements, VALUE );
			liVectorValues = vector<doubleFib>( uiNumberOfVectorElements, 0 );
			liVectorVariable = vector<cFibVariable*>( uiNumberOfVectorElements, NULL );
			
			//set the correct vector element values
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
 * This method changes the number of Elements of this vector to the given
 * number.
 *
 * @param uiNumberOfVectorElements the number of elements this vector
 * 	should have
 */
void cVectorExtObject::resize( unsigned int uiNumberOfVectorElements ){

	//unregister this vector from all variables that will be lost
#ifndef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	const unsigned int uiNumberOfElements = liVectorVariable.size();
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	for ( unsigned int uiActualElement = uiNumberOfVectorElements;
			uiActualElement < uiNumberOfElements; uiActualElement++ ){
		
		if ( ( liVectorType[ uiActualElement ] == VARIABLE ) &&
				(liVectorVariable[ uiActualElement ] != NULL) ){
			liVectorVariable[ uiActualElement ]->unregisterUsingElement( this );
		}
	}
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	uiNumberOfElements = uiNumberOfVectorElements;
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	liVectorType.resize( uiNumberOfVectorElements, VALUE );
	liVectorValues.resize( uiNumberOfVectorElements, 0 );
	liVectorVariable.resize( uiNumberOfVectorElements, NULL );
}




