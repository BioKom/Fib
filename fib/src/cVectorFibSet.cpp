/**
 * @class cVectorFibSet
 * file name: cVectorFibSet.cpp
 * @author Betti Oesterholz
 * @date 06.12.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a set-element vector.
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
 * This class represents a set-element vector of the
 * Fib multimedia language.
 * It is a vector for set-elements.
 *
 */
/*
History:
06.12.2011  Oesterholz  created
*/


#include "cVectorFibSet.h"
#include "cFibElement.h"
#include "cFibSet.h"
#include "cTypeFibSet.h"
#include "cDomains.h"


using namespace fib;



/**
 * The constructor of the set-element vector.
 *
 * @param iNumberOfElements the number of elements the vector should have
 * @param pDefiningElement the Fib element which
 * 	defines/ uses the set-element vector
 */
cVectorFibSet::cVectorFibSet( unsignedIntFib iNumberOfElements,
		cFibElement * pDefiningSetElement ):
		cFibVector( iNumberOfElements, pDefiningSetElement ){
	//noting to do
}


/**
 * The constructor of the set-element vector.
 *
 * @param definingSetElement the Fib set-element which
 * 	defines/ uses the set-element vector
 */
cVectorFibSet::cVectorFibSet( cFibSet & definingSetElement ):
		cFibVector( definingSetElement.getNumberOfVariables(), &definingSetElement ){
	
	//nothing to do
}




/**
 * The copy constructor of the vector.
 *
 * @param vector the vector from which to copy the data
 * @param pDefiningFibElement the Fib -element which defines/ uses
 * 	the new vector
 */
cVectorFibSet::cVectorFibSet( const cVectorFibSet & vector,
		cFibElement *pDefiningFibElement ):
		cFibVector( vector, pDefiningFibElement ){
	DEBUG_OUT_L3(<<this<<"->cVectorFibSet("<<&vector<<", "<<definingFibElement<<") copy constructor"<<endl);
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
cVectorFibSet::cVectorFibSet( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables ):
		cFibVector( pXmlElement, outStatus, liDefinedVariables ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorFibSet() constructor restore xml"<<endl);
	
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
	}else if ( strcmp( "set", szVectorXmlType ) != 0 ){
		outStatus = 2;
		return;
	}
}

/**
 * This constructor restores a set-element vector from the stream where it is
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
cVectorFibSet::cVectorFibSet( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomain * pInVectorDomain, const cDomain * pInDomainVariable,
		const unsignedIntFib uiInNumberOfElements ):
		cFibVector( iBitStream, outStatus, liDefinedVariables,
			pInVectorDomain, pInDomainVariable, uiInNumberOfElements ){
	//nothing to do
	DEBUG_OUT_L3(<<this<<"->cVectorFibSet() constructor restore bit"<<endl);
}


/**
 * This method creates an instance of this vector type.
 *
 * @param iNumberOfVectorElements number of elements in the vector
 * @param definingPropertyElement the Fib set-element which
 * 	defines/ uses the set-element
 */
cVectorFibSet * cVectorFibSet::createInstance(
		unsignedIntFib iNumberOfVectorElements,
		cFibElement *pDefiningElement ) const{

	DEBUG_OUT_L3(<<this<<"->cVectorFibSet::createInstance("<<iNumberOfVectorElements<<", "<<pDefiningElement<<")"<<endl);
	
	return new cVectorFibSet( iNumberOfVectorElements, pDefiningElement );
}


/**
 * Returns the type of the vector.
 * You have to delete the returned object after usage.
 *
 * @return the type of the vector
 */
cTypeElement * cVectorFibSet::getElementType() const{
	
	DEBUG_OUT_L3(<<this<<"->cVectorFibSet::getElementType()"<<endl);
	
	/*the type is dimension type*/
	if ( pDefiningFibElement != NULL ){
		//try to evalue type with the help of the defining Fib element
		if ( pDefiningFibElement->getType() != 'v' ){
			/*not a set-element defines this vector
			-> return the standard type /  use 0'th domain*/
			return new cTypeFibSet( 0 );
		}
		const intFib uiDomainNumber =
			((cFibSet*)pDefiningFibElement)->getDomainNr();
		return new cTypeFibSet( uiDomainNumber );
	}//else no type found -> return the standard type /  use 0'th domain

	return new cTypeFibSet( 0 );
}


/**
 * Returns a reference to the domain of the vector or
 * the nullpointer NULL if no domain is defined for the vector.
 * If the nullpointer NULL is returned the standarddomain is valid for the
 * vector.
 *
 * @return a reference to the definitionarea of the vector
 */
cDomainVectorBasis * cVectorFibSet::getDomain() const{

	DEBUG_OUT_L3(<<this<<"->cVectorFibSet::getDomain()"<<endl);
	
	if ( pDefiningFibElement == NULL ){
		//can't get enviroment/ no enviroment -> return standard domain
		return NULL;
	}
	
	/*get the domain for the type of the vector*/
	cDomains validDomains = pDefiningFibElement->getValidDomains();

	if ( pDefiningFibElement->getType() == 'v' ){
		//defining Fib element is an set element
		
		const intFib uiDomainNumber =
			((cFibSet*)pDefiningFibElement)->getDomainNr();
		//find the next domain for the domain number
		cDomainVectorBasis * pDomainSetElement = NULL;
		for ( intFib uiActualDomain = uiDomainNumber; 0 <= uiActualDomain;
				uiActualDomain-- ){
			
			const cTypeFibSet typeFibSet( uiActualDomain );
			pDomainSetElement = (cDomainVectorBasis*)
				validDomains.getDomainForElement( typeFibSet );
				
			if ( pDomainSetElement != NULL ){
				break;
			}
		}
		if ( pDomainSetElement == NULL ){
			//use the standard domain
			return NULL;
		}
		cDomain * pDomainVector = pDomainSetElement->getElementDomain( 3 );
		if ( ! pDomainVector->isVector() ){
			return NULL;
		}
		
		return ((cDomainVectorBasis*)pDomainVector);
	}//else not a set element as defining element
	
	cTypeElement * pTypeElement = getElementType();
	cDomain * pDomain = validDomains.getDomainForElement( *pTypeElement );
	delete pTypeElement;

	if ( ( pDomain == NULL ) || ( ! pDomain->isVector() ) ){
		//error in domain: not a domain or not a vector domain)
		return NULL;
	}
	cDomainVectorBasis * pDomainFibSet = (cDomainVectorBasis*)pDomain;
	
	cDomain * pDomainFibSetVector = pDomainFibSet->getElementDomain( 3 );
	if ( ( pDomainFibSetVector == NULL ) || ( ! pDomainFibSetVector->isVector() ) ){
		/*error in domain (domain for the vectors with the to set values
		* missing or not a vector domain)*/
		return NULL;
	}
	return (cDomainVectorBasis*)pDomainFibSetVector;
}


/**
 * Returns a reference to the standard domain of the vector.
 * You have to delete the returned object after usage.
 *
 * @return a reference to the standard domain of the vector
 */
cDomainVectorBasis * cVectorFibSet::getStandardDomain() const{

	DEBUG_OUT_L3(<<this<<"->cVectorFibSet::getStandardDomain()"<<endl);
	
	const cTypeElement * typeElement = getElementType();
	cDomain * pDomainStandardFibSet = typeElement->getStandardDomain();
	delete typeElement;
	
	if ( ( pDomainStandardFibSet == NULL ) || ( ! pDomainStandardFibSet->isVector() ) ){
		//error in domain: not a domain or not a vector domain)
		delete pDomainStandardFibSet;
		return NULL;
	}
	cDomainVectorBasis * pDomVecStandardFibSet =
		(cDomainVectorBasis*)pDomainStandardFibSet;
	
	cDomain * pDomainStandardFibSetVector = pDomVecStandardFibSet->getElementDomain( 3 );
	if ( pDomainStandardFibSetVector == NULL ){
		/*error in domain (domain for the vectors with the to set values
		* missing)*/
		return NULL;
	}
	if ( ! pDomainStandardFibSetVector->isVector() ){
		/*error in domain (domain for the vectors with the to set values
		* not a vector domain)*/
		delete pDomainStandardFibSet;
		return NULL;
	}
	pDomainStandardFibSetVector = pDomainStandardFibSetVector->clone();

	delete pDomainStandardFibSet;
	
	return (cDomainVectorBasis*)pDomainStandardFibSetVector;
}


/**
 * Returns a reference to the valuedomain of the vector or
 * the nullpointer NULL if no valuedomain is defined for the vector.
 * If the nullpointer NULL is returned the standarddomain is valid for the
 * vector.
 *
 * @return a reference to the definitionarea of the vector
 */
cDomainVectorBasis * cVectorFibSet::getValueDomain() const{

	DEBUG_OUT_L3(<<this<<"->cVectorFibSet::getValueDomain()"<<endl);
	
	if ( pDefiningFibElement == NULL ){
		//can't get enviroment/ no enviroment -> return standard domain
		return NULL;
	}
	
	//get the domain for the type of the vector
	cDomains validValueDomains = pDefiningFibElement->getValidValueDomains();
	
	if ( pDefiningFibElement->getType() == 'v' ){
		//defining Fib element is an set element
		
		const intFib uiDomainNumber =
			((cFibSet*)pDefiningFibElement)->getDomainNr();
		//find the next domain for the domain number
		cDomainVectorBasis * pDomainSetElement = NULL;
		for ( intFib uiActualDomain = uiDomainNumber; 0 <= uiActualDomain;
				uiActualDomain-- ){
			
			const cTypeFibSet typeFibSet( uiActualDomain );
			pDomainSetElement = (cDomainVectorBasis*)
				validValueDomains.getDomainForElement( typeFibSet );
				
			if ( pDomainSetElement != NULL ){
				break;
			}
		}
		if ( pDomainSetElement == NULL ){
			//use the standard domain
			return NULL;
		}
		cDomain * pDomainVector = pDomainSetElement->getElementDomain( 3 );
		if ( ! pDomainVector->isVector() ){
			return NULL;
		}
		
		return ((cDomainVectorBasis*)pDomainVector);
	}//else not a set element as defining element
	
	cTypeElement * typeElement = getElementType();
	cDomain * pDomain = validValueDomains.getDomainForElement( *typeElement );
	delete typeElement;

	if ( ( pDomain == NULL ) || ( ! pDomain->isVector() ) ){
		//error in domain: not a domain or not a vector domain)
		return NULL;
	}
	cDomainVectorBasis * pDomainFibSet = (cDomainVectorBasis*)pDomain;
	
	cDomain * pDomainFibSetVector = pDomainFibSet->getElementDomain( 3 );
	if ( ( pDomainFibSetVector == NULL ) || ( ! pDomainFibSetVector->isVector() ) ){
		/*error in domain (domain for the vectors with the to set values
		* missing or not a vector domain)*/
		return NULL;
	}
	return (cDomainVectorBasis*)pDomainFibSetVector;
}


/**
 * @return the name for the type of the vector
 */
string cVectorFibSet::getVectorType() const{
	
	DEBUG_OUT_L3(<<this<<"->cVectorFibSet::getVectorType()"<<endl);
	
	return "set";
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
void cVectorFibSet::setDefiningFibElement( cFibElement * pFibElement,
		bool bCheckDomains ){

	DEBUG_OUT_L3(<<this<<"->cVectorFibSet::setDefiningFibElement( "<< pFibElement <<", "<<bCheckDomains<<" )"<<endl);
	
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
			//set the correct number of vectorelements
			unsigned int uiNumberOfVectorElements;
			if ( pDefiningFibElement->getType() == 'v' ){
				/*defining element is a set element
				 -> the number of vector elements is equal to the number of
				 defined variables of the set element*/
				uiNumberOfVectorElements =
					((cFibSet*)(pDefiningFibElement))->getNumberOfVariables();
			}else{/*the number of vector elements is equal to the number of
				 vector domain elements*/
				uiNumberOfVectorElements = domain->getNumberOfElements();
			}
			
			//unregister this vector from all variables
			const unsigned int uiNumberOfElements = liVectorVariable.size();
			for ( unsigned int uiActualElement = 0;
					uiActualElement < uiNumberOfElements; uiActualElement++ ){
				
				if ( ( liVectorType[ uiActualElement ] == VARIABLE ) &&
						(liVectorVariable[ uiActualElement ] != NULL) ){
					liVectorVariable[ uiActualElement ]->unregisterUsingElement( this );
				}
			}
			liVectorType = vector<eVectorType>( uiNumberOfVectorElements, VALUE );
			liVectorValues = vector<doubleFib>( uiNumberOfVectorElements, 0 );
			liVectorVariable = vector<cFibVariable*>( uiNumberOfVectorElements, NULL );
			
			//set the correct vectorelementvalues
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







