/**
 * @class cVectorFibMatrix
 * file name: cVectorFibMatrix.cpp
 * @author Betti Oesterholz
 * @date 06.12.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a matrix element vector.
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
 * This class represents a matrix element vector of the
 * Fib multimedia language.
 * It is a vector for matrix elements.
 *
 */
/*
History:
06.12.2011  Oesterholz  created
17.02.2013  Oesterholz FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE implemented
16.03.2013  Oesterholz  clone() method added
*/


#include "cVectorFibMatrix.h"
#include "cFibElement.h"
#include "cFibMatrix.h"
#include "cTypeFibMatrix.h"
#include "cDomains.h"


using namespace fib;



/**
 * The constructor of the matrix element vector.
 *
 * @param iNumberOfElements the number of elements the vector should have
 * @param pDefiningElement the Fib element which
 * 	defines/ uses the matrix element vector
 */
cVectorFibMatrix::cVectorFibMatrix( unsignedIntFib iNumberOfElements,
		cFibElement * pDefiningMatrixElement ):
		cFibVector( iNumberOfElements, pDefiningMatrixElement ){
	//noting to do
}


/**
 * The constructor of the matrix element vector.
 *
 * @param definingMatrixElement the Fib matrix element which
 * 	defines/ uses the matrix element vector
 */
cVectorFibMatrix::cVectorFibMatrix( cFibMatrix & definingMatrixElement ):
		cFibVector( definingMatrixElement.getNumberOfVectorElements(),
			&definingMatrixElement ){
	
	//nothing to do
}



/**
 * The copy constructor of the vector.
 *
 * @param vector the vector from which to copy the data
 * @param pDefiningFibElement the Fib -element which defines/ uses
 * 	the new vector
 */
cVectorFibMatrix::cVectorFibMatrix( const cVectorFibMatrix & vector,
		cFibElement *pDefiningFibElement ):
		cFibVector( vector, pDefiningFibElement ){
	DEBUG_OUT_L3(<<this<<"->cVectorFibMatrix("<<&vector<<", "<<definingFibElement<<") copy constructor"<<endl);
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
cVectorFibMatrix::cVectorFibMatrix( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables ):
		cFibVector( pXmlElement, outStatus, liDefinedVariables ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorFibMatrix() constructor restore xml"<<endl);
	
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
	}else if ( strcmp( "matrix", szVectorXmlType ) != 0 ){
		outStatus = 2;
		return;
	}
}

/**
 * This constructor restores a matrix element vector from the stream where it is
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
cVectorFibMatrix::cVectorFibMatrix( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomain * pInVectorDomain, const cDomain * pInDomainVariable,
		const unsignedIntFib uiInNumberOfElements ):
		cFibVector( iBitStream, outStatus, liDefinedVariables,
			pInVectorDomain, pInDomainVariable, uiInNumberOfElements ){
	//nothing to do
	DEBUG_OUT_L3(<<this<<"->cVectorFibMatrix() constructor restore bit"<<endl);
}


/**
 * This method clones this object.
 *
 * @return a pointer to the clone of this object
 */
cVectorFibMatrix * cVectorFibMatrix::clone() const{
	
	return new cVectorFibMatrix( *this );
}


/**
 * This method creates an instance of this vector type.
 *
 * @param iNumberOfVectorElements number of elements in the vector
 * @param definingPropertyElement the Fib matrix element which
 * 	defines/ uses the matrix element
 */
cVectorFibMatrix * cVectorFibMatrix::createInstance(
		unsignedIntFib iNumberOfVectorElements,
		cFibElement *pDefiningElement ) const{

	DEBUG_OUT_L3(<<this<<"->cVectorFibMatrix::createInstance("<<iNumberOfVectorElements<<", "<<pDefiningElement<<")"<<endl);
	
	return new cVectorFibMatrix( iNumberOfVectorElements, pDefiningElement );
}


/**
 * Returns the type of the vector.
 * You have to delete the returned object after usage.
 *
 * @return the type of the vector
 */
cTypeElement * cVectorFibMatrix::getElementType() const{
	
	DEBUG_OUT_L3(<<this<<"->cVectorFibMatrix::getElementType()"<<endl);
	
	/*the type is dimension type*/
	if ( pDefiningFibElement != NULL ){
		//try to evalue type with the help of the defining Fib element
		if ( pDefiningFibElement->getType() != 'm' ){
			/*not a matrix element defines this vector
			-> return the standard type /  use 0'th domain*/
			return new cTypeFibMatrix( 0 );
		}
		const intFib uiDomainNumber =
			((cFibMatrix*)pDefiningFibElement)->getDomainNr();
		return new cTypeFibMatrix( uiDomainNumber );
	}//else no type found -> return the standard type /  use 0'th domain

	return new cTypeFibMatrix( 0 );
}


/**
 * Returns a reference to the domain of the vector or
 * the nullpointer NULL if no domain is defined for the vector.
 * If the nullpointer NULL is returned the standarddomain is valid for the
 * vector.
 *
 * @return a reference to the definitionarea of the vector
 */
cDomainVectorBasis * cVectorFibMatrix::getDomain() const{

	DEBUG_OUT_L3(<<this<<"->cVectorFibMatrix::getDomain()"<<endl);
	
	if ( pDefiningFibElement == NULL ){
		//can't get enviroment/ no enviroment -> return standard domain
		return NULL;
	}
	
	/*get the domain for the type of the vector*/
	cDomains validDomains = pDefiningFibElement->getValidDomains();
	
	if ( pDefiningFibElement->getType() == 'm' ){
		//defining Fib element is an matrix element
		
		const intFib uiDomainNumber =
			((cFibMatrix*)pDefiningFibElement)->getDomainNr();
		//find the next domain for the domain number
		cDomainVectorBasis * pDomainMatrixElement = NULL;
		for ( intFib uiActualDomain = uiDomainNumber; 0 <= uiActualDomain;
				uiActualDomain-- ){
			
			const cTypeFibMatrix typeFibMatrix( uiActualDomain );
			pDomainMatrixElement = (cDomainVectorBasis*)
				validDomains.getDomainForElement( typeFibMatrix );
				
			if ( pDomainMatrixElement != NULL ){
				break;
			}
		}
		if ( pDomainMatrixElement == NULL ){
			//use the standard domain
			return NULL;
		}
		cDomain * pDomainVector = pDomainMatrixElement->getElementDomain( 4 );
		if ( ! pDomainVector->isVector() ){
			return NULL;
		}
		
		return ((cDomainVectorBasis*)pDomainVector);
	}//else not a matrix element as defining element
	
	cTypeElement * typeElement = getElementType();
	cDomain * pDomain = validDomains.getDomainForElement( *typeElement );
	delete typeElement;
	
	if ( ( pDomain == NULL ) || ( ! pDomain->isVector() ) ){
		//error in domain: not a domain or not a vector domain)
		return NULL;
	}
	cDomainVectorBasis * pDomainFibMatrix = (cDomainVectorBasis*)pDomain;
	
	cDomain * pDomainFibMatrixVector = pDomainFibMatrix->getElementDomain( 4 );
	if ( ( pDomainFibMatrixVector == NULL ) || ( ! pDomainFibMatrixVector->isVector() ) ){
		/*error in domain (domain for the vectors with the to set values
		* missing or not a vector domain)*/
		return NULL;
	}
	return (cDomainVectorBasis*)pDomainFibMatrixVector;
}


/**
 * Returns a reference to the standard domain of the vector.
 * You have to delete the returned object after usage.
 *
 * @return a reference to the standard domain of the vector
 */
cDomainVectorBasis * cVectorFibMatrix::getStandardDomain() const{

	DEBUG_OUT_L3(<<this<<"->cVectorFibMatrix::getStandardDomain()"<<endl);
	
	const cTypeElement * typeElement = getElementType();
	cDomain * pDomainStandardFibMatrix = typeElement->getStandardDomain();
	delete typeElement;
	
	if ( ( pDomainStandardFibMatrix == NULL ) || ( ! pDomainStandardFibMatrix->isVector() ) ){
		//error in domain: not a domain or not a vector domain)
		delete pDomainStandardFibMatrix;
		return NULL;
	}
	cDomainVectorBasis * pDomVecStandardFibMatrix =
		(cDomainVectorBasis*)pDomainStandardFibMatrix;
	
	cDomain * pDomainStandardFibMatrixVector = pDomVecStandardFibMatrix->getElementDomain( 4 );
	if ( pDomainStandardFibMatrixVector == NULL ){
		/*error in domain (domain for the vectors with the to matrix values
		* missing)*/
		return NULL;
	}
	if ( ! pDomainStandardFibMatrixVector->isVector() ){
		/*error in domain (domain for the vectors with the to matrix values
		* not a vector domain)*/
		delete pDomainStandardFibMatrix;
		return NULL;
	}
	pDomainStandardFibMatrixVector = pDomainStandardFibMatrixVector->clone();

	delete pDomainStandardFibMatrix;
	
	return (cDomainVectorBasis*)pDomainStandardFibMatrixVector;
}


/**
 * Returns a reference to the valuedomain of the vector or
 * the nullpointer NULL if no valuedomain is defined for the vector.
 * If the nullpointer NULL is returned the standarddomain is valid for the
 * vector.
 *
 * @return a reference to the definitionarea of the vector
 */
cDomainVectorBasis * cVectorFibMatrix::getValueDomain() const{
	
	DEBUG_OUT_L3(<<this<<"->cVectorFibMatrix::getValueDomain()"<<endl);
	
	if ( pDefiningFibElement == NULL ){
		//can't get enviroment/ no enviroment -> return standard domain
		return NULL;
	}
	
	//get the domain for the type of the vector
	cDomains validValueDomains = pDefiningFibElement->getValidValueDomains();
	
	if ( pDefiningFibElement->getType() == 'm' ){
		//defining Fib element is an matrix element
		
		const intFib uiDomainNumber =
			((cFibMatrix*)pDefiningFibElement)->getDomainNr();
		//find the next domain for the domain number
		cDomainVectorBasis * pDomainMatrixElement = NULL;
		for ( intFib uiActualDomain = uiDomainNumber; 0 <= uiActualDomain;
				uiActualDomain-- ){
			
			const cTypeFibMatrix typeFibMatrix( uiActualDomain );
			pDomainMatrixElement = (cDomainVectorBasis*)
				validValueDomains.getDomainForElement( typeFibMatrix );
				
			if ( pDomainMatrixElement != NULL ){
				break;
			}
		}
		if ( pDomainMatrixElement == NULL ){
			//use the standard domain
			return NULL;
		}
		cDomain * pDomainVector = pDomainMatrixElement->getElementDomain( 4 );
		if ( ! pDomainVector->isVector() ){
			return NULL;
		}
		
		return ((cDomainVectorBasis*)pDomainVector);
	}//else not a matrix element as defining element
	
	cTypeElement * typeElement = getElementType();
	cDomain * pDomain = validValueDomains.getDomainForElement( *typeElement );
	delete typeElement;

	if ( ( pDomain == NULL ) || ( ! pDomain->isVector() ) ){
		//error in domain: not a domain or not a vector domain)
		return NULL;
	}
	cDomainVectorBasis * pDomainFibMatrix = (cDomainVectorBasis*)pDomain;
	
	cDomain * pDomainFibMatrixVector = pDomainFibMatrix->getElementDomain( 4 );
	if ( ( pDomainFibMatrixVector == NULL ) || ( ! pDomainFibMatrixVector->isVector() ) ){
		/*error in domain (domain for the vectors with the to matrix values
		* missing or not a vector domain)*/
		return NULL;
	}
	return (cDomainVectorBasis*)pDomainFibMatrixVector;
}


/**
 * @return the name for the type of the vector
 */
string cVectorFibMatrix::getVectorType() const{
	
	DEBUG_OUT_L3(<<this<<"->cVectorFibMatrix::getVectorType()"<<endl);
	
	return "matrix";
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
void cVectorFibMatrix::setDefiningFibElement( cFibElement * pFibElement,
		bool bCheckDomains ){

	DEBUG_OUT_L3(<<this<<"->cVectorFibMatrix::setDefiningFibElement( "<< pFibElement <<", "<<bCheckDomains<<" )"<<endl);
	
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
			if ( pDefiningFibElement->getType() == 'm' ){
				/*defining element is a matrix element
				 -> the number of vector elements is equal to the number of
				 vector elements of the matrix element*/
				uiNumberOfVectorElements =
					((cFibMatrix*)(pDefiningFibElement))->getNumberOfVectorElements();
			}else{/*the number of vector elements is equal to the number of
				 vector domain elements*/
				uiNumberOfVectorElements = domain->getNumberOfElements();
			}
			
			//unregister this vector from all variables
#ifndef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
			const unsigned int uiNumberOfElements = liVectorVariable.size();
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
			for ( unsigned int uiActualElement = 0;
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





