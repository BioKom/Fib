/**
 * @class cVectorArea
 * file name: cVectorArea.cpp
 * @author Betti Oesterholz
 * @date 11.05.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a uderarea -Fib-vector.
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
 * This file contains the class of all Fib-subareavectors.
 * Thes subareavectors are used in Fib-areaelements, for the subareaa of
 * the area. An subareavector contains two elements wich are integers.
 *
 */
/*
History:
11.05.2009  Oesterholz  created
23.02.2011  Oesterholz  Bugfix: getLowerBound() rounding new correctly
25.08.2011  Oesterholz  underarea to subarea
02.01.2012  Oesterholz  cTypeSubarea to cTypeArea;
   changes for cTypeArea and cFibMatrix
16.03.2013  Oesterholz  clone() method added
*/


#include "cVectorArea.h"

#include "cTypeArea.h"
#include "cTypeFibMatrix.h"
#include "cDomains.h"
#include "cFibElement.h"
#include "cFibMatrix.h"


using std::vector;

using namespace fib;


/**
 * The constructor of the subareavector.
 *
 * @param pInDefiningAreaElement the Fib-element which
 * 	defines/ uses the checksum -property -vector
 */
cVectorArea::cVectorArea( cFibElement * pInDefiningAreaElement ):
		cFibVector( 2, pInDefiningAreaElement ){
	//nothing to do
	DEBUG_OUT_L3(<<this<<"->cVectorArea("<<pInDefiningAreaElement<<") constructor"<<endl);
}


/**
 * The copy constructor of the vector.
 *
 * @param vector the vector from which to copy the data
 * @param pInDefiningAreaElement the Fib-element which defines/ uses
 * 	the new vector
 */
cVectorArea::cVectorArea( const cVectorArea & vector,
		cFibElement * pInDefiningAreaElement ):
		cFibVector( vector, pInDefiningAreaElement ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorArea("<<&vector<<","<<pInDefiningAreaElement<<") copyconstructor"<<endl);
	
	if ( pInDefiningAreaElement ){
		//use the domain of the new defining element
		setDefiningFibElement( pInDefiningAreaElement );
	}//else copy the other vector exactly
}


/**
 * parameterconstructor
 *
 * @param lLowerBound the lower bound value to set
 * @param lUpperBound the upper bound value to set
 * @param pInDefiningAreaElement the Fib-element which defines/ uses
 * 	the new vector
 */
cVectorArea::cVectorArea( longFib lLowerBound, longFib lUpperBound,
		cFibElement * pInDefiningAreaElement ):
		cFibVector( 2, pInDefiningAreaElement ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorArea("<<lLowerBound<<","<<lUpperBound<<", "<<pInDefiningAreaElement<<") constructor"<<endl);
	
	setLowerBoundValue( lLowerBound );
	setUpperBoundValue( lUpperBound );
	if ( pInDefiningAreaElement ){
		//use the domain of the new defining element
		setDefiningFibElement( pInDefiningAreaElement );
	}//else copy the other vector exactly
}


/**
 * parameterconstructor
 *
 * @param lLowerBound the lower bound value to set
 * @param pVariableUpperBound the upper bound variable to set
 * @param pInDefiningAreaElement the Fib-element which defines/ uses
 * 	the new vector
 */
cVectorArea::cVectorArea( longFib lLowerBound, cFibVariable *
		pVariableUpperBound, cFibElement * pInDefiningAreaElement ):
		cFibVector( 2, pInDefiningAreaElement ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorArea("<<lLowerBound<<","<<pVariableUpperBound<<", "<<pInDefiningAreaElement<<") constructor"<<endl);
	
	setLowerBoundValue( lLowerBound );
	setUpperBoundVariable( pVariableUpperBound );
	if ( pInDefiningAreaElement ){
		//use the domain of the new defining element
		setDefiningFibElement( pInDefiningAreaElement );
	}//else copy the other vector exactly
}


/**
 * parameterconstructor
 *
 * @param pVariableLowerBound the lower bound variable to set
 * @param lUpperBound the upper bound value to set
 * @param pInDefiningAreaElement the Fib-element which defines/ uses
 * 	the new vector
 */
cVectorArea::cVectorArea( cFibVariable * pVariableLowerBound,
		longFib lUpperBound, cFibElement * pInDefiningAreaElement ):
		cFibVector( 2, pInDefiningAreaElement ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorArea("<<pVariableLowerBound<<","<<lUpperBound<<", "<<pInDefiningAreaElement<<") constructor"<<endl);
	
	setLowerBoundVariable( pVariableLowerBound );
	setUpperBoundValue( lUpperBound );
	if ( pInDefiningAreaElement ){
		//use the domain of the new defining element
		setDefiningFibElement( pInDefiningAreaElement );
	}//else copy the other vector exactly
}


/**
 * parameterconstructor
 *
 * @param pVariableLowerBound the lower bound variable to set
 * @param pVariableUpperBound the upper bound variable to set
 * @param pInDefiningAreaElement the Fib-element which defines/ uses
 * 	the new vector
 */
cVectorArea::cVectorArea( cFibVariable * pVariableLowerBound,
		cFibVariable * pVariableUpperBound, cFibElement * pInDefiningAreaElement ):
		cFibVector( 2, pInDefiningAreaElement ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorArea("<<pVariableLowerBound<<","<<pVariableUpperBound<<", "<<pInDefiningAreaElement<<") constructor"<<endl);
	
	setLowerBoundVariable( pVariableLowerBound );
	setUpperBoundVariable( pVariableUpperBound );
	if ( pInDefiningAreaElement ){
		//use the domain of the new defining element
		setDefiningFibElement( pInDefiningAreaElement );
	}//else copy the other vector exactly
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
cVectorArea::cVectorArea( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables ):
		cFibVector( pXmlElement, outStatus, liDefinedVariables ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorArea() restore Xml"<<endl);
	
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
	}else if ( ( string( "subarea" ) != szVectorXmlType ) &&
			( string( "area" ) != szVectorXmlType ) && //for matrix element
			( string( "underarea" ) != szVectorXmlType ) ){//"underarea" is depricated
		outStatus = 2;
		return;
	}
}


/**
 * This constructor restores a subareasvector from the stream where it is
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
 */
cVectorArea::cVectorArea( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomain * pInVectorDomain, const cDomain * pInDomainVariable ):
		cFibVector( iBitStream, outStatus, liDefinedVariables,
			pInVectorDomain, pInDomainVariable ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorArea() restore bit"<<endl);
	
	//nothing to do
}


/**
 * This method clones this object.
 *
 * @return a pointer to the clone of this object
 */
cVectorArea * cVectorArea::clone() const{
	
	return new cVectorArea( *this );
}


/**
 * This method creates an instance of this vector type.
 *
 * @param iNumberOfElements number of elements in the vector (this will
 * 	be ignored for the subareavector)
 * @param pInDefiningAreaElement the Fib-areaelement which defines/ uses
 * 	the subareasvector
 */
cVectorArea * cVectorArea::createInstance(
		unsignedIntFib iNumberOfElements,
		cFibElement * pInDefiningAreaElement ) const{
	
	DEBUG_OUT_L3(<<this<<"->cVectorArea::createInstance("<<iNumberOfElements<<", "<< pInDefiningAreaElement <<")"<<endl);
	
	return new cVectorArea( pInDefiningAreaElement );
}


/**
 * Sets the Fib-element which defines/ uses this vector.
 * If the given pointer is the nullpointer (standardvalue), no
 * Fib-element defines this vector.
 *
 * @param definingAreaElement a pointer to the Fib-element which
 * 	defines/ uses this vector
 * @param bCheckDomains getthe domains of the defining element and
 * 	check the vectorelements with it
 */
void cVectorArea::setDefiningFibElement( cFibElement *fibElement,
		bool bCheckDomains ){

	DEBUG_OUT_L3(<<this<<"->cVectorArea::setDefiningFibElement("<<fibElement<<", "<< bCheckDomains <<")"<<endl);
	
	if ( getNumberOfElements() != 0 ){
		return cFibVector::setDefiningFibElement( fibElement, bCheckDomains );
	}/*else don't change the vectorsize when the defining element changes
	and the vector has size 0*/
	pDefiningFibElement = fibElement;
}


/**
 * Returns the type of the vector.
 * You have to delete the returned object after usage.
 *
 * @return the type of the vector
 */
cTypeElement * cVectorArea::getElementType() const{
	
	DEBUG_OUT_L3(<<this<<"->cVectorArea::getElementType()"<<endl);
	
	//the type depends on the defining Fib element
	if ( ( pDefiningFibElement != NULL ) &&
			( pDefiningFibElement->getType() == 'm' )  ){
		//the vector is used by a matrix element
		return new cTypeFibMatrix();
	}//else default is cTypeArea
	return new cTypeArea();
}



/**
 * Returns a reference to the domain of the vector or
 * the nullpointer NULL if no domain is defined for the vector.
 * If the nullpointer NULL is returned the standarddomain is valid for the
 * vector.
 *
 * @return a reference to the definitionarea of the vector
 */
cDomainVectorBasis * cVectorArea::getDomain() const{

	DEBUG_OUT_L3(<<this<<"->cVectorArea::getDomain()"<<endl);
	
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
		cDomain * pDomainVector = pDomainMatrixElement->getElementDomain( 3 );
		if ( ! pDomainVector->isVector() ){
			return NULL;
		}
		
		return ((cDomainVectorBasis*)pDomainVector);
	}//else not a matrix element as defining element -> it should be an area element
	
	cTypeElement * pTypeElement = getElementType();
	cDomain * pDomain = validDomains.getDomainForElement( *pTypeElement );
	delete pTypeElement;

	if ( ( pDomain == NULL ) || ( ! pDomain->isVector() ) ){
		//error in domain: not a domain or not a vector domain)
		return NULL;
	}
	cDomainVectorBasis * pDomainArea = (cDomainVectorBasis*)pDomain;
	
	cDomain * pDomainAreaVector = pDomainArea->getElementDomain( 2 );
	if ( ( pDomainAreaVector == NULL ) || ( ! pDomainAreaVector->isVector() ) ){
		/*error in domain (domain for the vectors with the to set values
		* missing or not a vector domain)*/
		return NULL;
	}
	return (cDomainVectorBasis*)pDomainAreaVector;
}


/**
 * Returns a reference to the standard domain of the vector.
 * You have to delete the returned object after usage.
 *
 * @return a reference to the standard domain of the vector
 */
cDomainVectorBasis * cVectorArea::getStandardDomain() const{

	DEBUG_OUT_L3(<<this<<"->cVectorArea::getStandardDomain()"<<endl);
	
	const cTypeElement * typeElement = getElementType();
	cDomain * pDomainStandardArea = typeElement->getStandardDomain();
	delete typeElement;
	
	if ( ( pDomainStandardArea == NULL ) || ( ! pDomainStandardArea->isVector() ) ){
		//error in domain: not a domain or not a vector domain)
		delete pDomainStandardArea;
		return NULL;
	}
	cDomainVectorBasis * pDomVecStandardArea =
		(cDomainVectorBasis*)pDomainStandardArea;
	
	cDomain * pDomainStandardAreaVector;
	if ( ( pDefiningFibElement != NULL ) &&
			( pDefiningFibElement->getType() == 'm' ) ){
		//the vector is used by a matrix element
		pDomainStandardAreaVector = pDomVecStandardArea->getElementDomain( 3 );
	}else{//default is area element
		pDomainStandardAreaVector = pDomVecStandardArea->getElementDomain( 2 );
	}
	if ( ( pDomainStandardAreaVector == NULL ) ||
			( ! pDomainStandardAreaVector->isVector() ) ){
		/*error in domain (domain for the vectors with the to set values
		* missing or not a vector domain)*/
		delete pDomainStandardArea;
		return NULL;
	}
	pDomainStandardAreaVector = pDomainStandardAreaVector->clone();

	delete pDomainStandardArea;
	
	return (cDomainVectorBasis*)pDomainStandardAreaVector;
}


/**
 * Returns a reference to the valuedomain of the vector or
 * the nullpointer NULL if no valuedomain is defined for the vector.
 * If the nullpointer NULL is returned the standarddomain is valid for the
 * vector.
 *
 * @return a reference to the definitionarea of the vector
 */
cDomainVectorBasis * cVectorArea::getValueDomain() const{

	DEBUG_OUT_L3(<<this<<"->cVectorArea::getValueDomain()"<<endl);
	
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
		cDomain * pDomainVector = pDomainMatrixElement->getElementDomain( 3 );
		if ( ! pDomainVector->isVector() ){
			return NULL;
		}
		
		return ((cDomainVectorBasis*)pDomainVector);
	}//else not a matrix element as defining element -> it should be an area element
	
	cTypeElement * typeElement = getElementType();
	cDomain * pDomain = validValueDomains.getDomainForElement( *typeElement );
	delete typeElement;

	if ( ( pDomain == NULL ) || ( ! pDomain->isVector() ) ){
		//error in domain: not a domain or not a vector domain)
		return NULL;
	}
	cDomainVectorBasis * pDomainFibSet = (cDomainVectorBasis*)pDomain;
	
	cDomain * pDomainFibSetVector = pDomainFibSet->getElementDomain( 2 );
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
string cVectorArea::getVectorType() const{
	DEBUG_OUT_L3(<<this<<"->cVectorArea::getVectorType()"<<endl);
	
	//the type depends on the defining Fib element
	if ( ( pDefiningFibElement != NULL ) &&
			( pDefiningFibElement->getType() == 'm' )  ){
		
		return "area";
	}//else default is cTypeArea
	return "subarea";
}



/**
 * @return the lower bound of the subarea
 */
longFib cVectorArea::getLowerBound() const{
	
	DEBUG_OUT_L3(<<this<<"->cVectorArea::getLowerBound()"<<endl);
	
	return roundToLongFib( getValue( 1 ) );
}

/**
 * @return the upper bound of the subarea
 */
longFib cVectorArea::getUpperBound() const{
	
	DEBUG_OUT_L3(<<this<<"->cVectorArea::getUpperBound()"<<endl);
	
	return roundToLongFib( getValue( 2 ) );
}


/**
 * @return all values which are in the subarea
 */
list<longFib> cVectorArea::getAreaValues() const{
	
	DEBUG_OUT_L3(<<this<<"->cVectorArea::getAreaValues()"<<endl);
	
	longFib lLowerBound = getLowerBound();
	longFib lUpperBound = getUpperBound();
	
	list<longFib> liAreaValues;
	
#ifdef MAX_UNDERAREA_SIZE
	if ( lLowerBound < lUpperBound ){
		if ( MAX_UNDERAREA_SIZE < (lUpperBound - lLowerBound) ){
			//to much elements in this subarea
			lUpperBound = lLowerBound + MAX_UNDERAREA_SIZE;
		}
		//go in increasing order
		for ( longFib lActualValue = lLowerBound; lActualValue <= lUpperBound;
				lActualValue++ ){
			
			liAreaValues.push_back( lActualValue );
		}
	}else{//go in decreasing order
		if ( MAX_UNDERAREA_SIZE < (lLowerBound - lUpperBound) ){
			//to much elements in this subarea
			lUpperBound = lLowerBound - MAX_UNDERAREA_SIZE;
		}
		for ( longFib lActualValue = lLowerBound; lActualValue >= lUpperBound;
				lActualValue-- ){
			
			liAreaValues.push_back( lActualValue );
		}
	}
#else
	if ( lLowerBound < lUpperBound ){
		//go in increasing order
		for ( longFib lActualValue = lLowerBound; lActualValue <= lUpperBound;
				lActualValue++ ){
			
			liAreaValues.push_back( lActualValue );
		}
	}else{//go in decreasing order
		for ( longFib lActualValue = lLowerBound; lActualValue >= lUpperBound;
				lActualValue-- ){
			
			liAreaValues.push_back( lActualValue );
		}
	}
#endif
	return liAreaValues;
}


/**
 * This method sets the lower bound of the subarea to the given value.
 *
 * @param lValue the lower bound to set
 * @return true if the lower bound is set to the given value lValue,
 * 	else false
 */
bool cVectorArea::setLowerBoundValue( longFib lValue ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorArea::setLowerBoundValue("<<lValue<<")"<<endl);
	
	return setValue( 1, (doubleFib)(lValue) );
}


/**
 * This method sets the upper bound of the subarea to the given value.
 *
 * @param lValue the upper bound to set
 * @return true if the upper bound is set to the given value lValue,
 * 	else false
 */
bool cVectorArea::setUpperBoundValue( longFib lValue ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorArea::setUpperBoundValue("<<lValue<<")"<<endl);
	
	return setValue( 2, (doubleFib)(lValue) );
}


/**
 * This method sets the lower bound of the subarea to the given variable.
 *
 * @param pVariable the lower bound variable to set
 * @return true if the lower bound is set to the given variable
 * 	pVariable, else false
 */
bool cVectorArea::setLowerBoundVariable( cFibVariable *pVariable ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorArea::setLowerBoundVariable("<<pVariable<<")"<<endl);
	
	return setVariable( 1, pVariable );
}


/**
 * This method sets the upper bound of the subarea to the given variable.
 *
 * @param pVariable the upper bound variable to set
 * @return true if the upper bound is set to the given variable
 * 	pVariable, else false
 */
bool cVectorArea::setUpperBoundVariable( cFibVariable *pVariable ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorArea::setUpperBoundVariable("<<pVariable<<")"<<endl);
	
	return setVariable( 2, pVariable );
}



/**
 * This Method makes this vectorelements equal to the correspondending
 * vectorelements of the given vector.
 * The type of the vector and the number of elements won't be changed.
 *
 * @param vector the vector to copy
 */
cVectorArea & cVectorArea::operator=( const cFibVector &vector ){
	DEBUG_OUT_L3(<<this<<"->cVectorArea::operator=( "<<&vector<<" )"<<endl);
	
	for ( unsigned int uiActualElement = 1; uiActualElement <= 2; uiActualElement++ ){
		
		if ( vector.isVariable( uiActualElement ) ){
			setVariable( uiActualElement,
				(const_cast<cFibVector*>(&vector))->getVariable( uiActualElement ) );
		}else{
			setValue( uiActualElement, vector.getValue( uiActualElement ) );
		}
	}
	return (*this);
}


















