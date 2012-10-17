/**
 * @class cFibSet
 * file name: cFibSet.cpp
 * @author Betti Oesterholz
 * @date 10.12.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the Fib set-element.
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
 * This class represents the set-element of the Fib -multimedialanguage.
 * An set-element contains a list with vectors to which element values the
 * variables it defines are set.
 *
 */
/*
History:
10.12.2011  Oesterholz  created
*/


#include "cFibSet.h"

#include "cTypeFibSet.h"
#include "cTypeVariable.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainNaturalNumber.h"

#include <algorithm>


using namespace fib;



/**
 * parameterconstructor
 *
 * @param iuNumberOfVariables the number of defined variables or
 * 	elements in the vectors this set-element should have
 * 	(minimum is 1)
 * @param pInSubobject the Fib element which is the subobject of
 * 	this Fib element (it also stands next in the order of Fib elements)
 * @param pInSuperiorElement the Fib element in which this
 * 	set-element is an subobject
 */
cFibSet::cFibSet( const unsignedIntFib iuNumberOfVariables,
		cFibElement * pInSubobject,
		cFibElement * pInSuperiorElement ):
		cFibLimb( pInSubobject, pInSuperiorElement ),
		uiDomainNr( 0 ){
	
	for ( unsignedIntFib uiNumberOfVariable = 0;
			uiNumberOfVariable < iuNumberOfVariables; uiNumberOfVariable++ ){
		
		vecVariablesDefined.push_back( new cFibVariable( this ) );
	}
	if ( vecVariablesDefined.empty() ){
		//define at least one variable
		vecVariablesDefined.push_back( new cFibVariable( this ) );
	}
	
	if ( pInSuperiorElement ){
		pInSuperiorElement->insertObjectInElement( this );
	}else{
		updateAllValues();
	}
}


/**
 * copyconstructor
 * This copyconstructor constructs a copy of the given set-element.
 * It dosn't copy other Fib elements than the given, even if ther are
 * in the set-element.
 *
 * @param setElement the set-element to copy
 */
cFibSet::cFibSet( const cFibSet &setElement ):
		cFibLimb( setElement ),
		liFibSets( setElement.liFibSets ), uiDomainNr( setElement.uiDomainNr ){
	
	const unsignedIntFib iuNumberOfVariables =
		setElement.vecVariablesDefined.size();
	for ( unsignedIntFib uiNumberOfVariable = 0;
			uiNumberOfVariable < iuNumberOfVariables; uiNumberOfVariable++ ){
		
		vecVariablesDefined.push_back( new cFibVariable( this ) );
	}

	for ( list<cVectorFibSet>::iterator itrFibSet = liFibSets.begin();
			 itrFibSet != liFibSets.end(); itrFibSet++ ){
		
		itrFibSet->setDefiningFibElement( this, false );
	}
}


/**
 * The constructor for restoring a set-element from an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node the Fib object is stored in
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
 * 	to restore Fib element, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 */
cFibSet::cFibSet( const TiXmlElement * pXmlElement, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables ): uiDomainNr( 0 ){
	
	if ( pXmlElement == NULL ){
		//noting to restore
		outStatus = -1;
		return;
	}
	const string szElementType( pXmlElement->Value() );
	if ( szElementType != "set" ){
		//wrong element type to restore
		outStatus = -2;
		return;
	}
	
	//read the domain number
	const char * szDomainNumber = pXmlElement->Attribute( "domainNr" );
	if ( szDomainNumber != NULL ){
		//the optional attribute domainNr exists
		uiDomainNr = atol( szDomainNumber );
	}
	
	bool bVectorFibSetRestored = false;
	bool bDefinedVariablesRestored = false;
	for ( const TiXmlNode * pChild = pXmlElement->FirstChild();
			pChild != NULL; pChild = pChild->NextSibling() ) {
		
		const int iType = pChild->Type();
		
		switch ( iType ){
			case TiXmlNode::ELEMENT:{
				/*check if this is a valid Fib element xml -element, create
				the apropirate Fib element and call its restoreXml() method*/
				const TiXmlElement * pXmlElement = pChild->ToElement();
				if ( pXmlElement == NULL ){
					outStatus = 2;
					continue;
				}
				const string szElementType( pXmlElement->Value() );
				
				if ( szElementType == "defined_variables" ){
					//read the defined variables
					const TiXmlElement * pXmlDefVariable = NULL;
					if ( pXmlElement->FirstChild( "variable" ) ){
						
						pXmlDefVariable = pXmlElement->FirstChild( "variable" )->ToElement();
					}
					const unsigned long lBiggestDefinedVarValue = liDefinedVariables.size();
					for( int iActualDefVariable = 1; pXmlDefVariable != NULL;
							pXmlDefVariable = pXmlDefVariable->NextSiblingElement( "variable" ),
							iActualDefVariable++ ){

						int iNumberOfDefVariable = 0;
						const char * szXmlObjectNumber = pXmlDefVariable->Attribute( "number", & iNumberOfDefVariable );
						if ( szXmlObjectNumber != NULL ){
							//defined variable number given
							if ( iActualDefVariable != iNumberOfDefVariable ){
								//Warning: no correct defined variable number
								outStatus = 2;
							}
						}
						
						const char * pcValue = pXmlDefVariable->GetText();
						unsigned long lDefVariableValue = 0;
						if ( pcValue ){
							const int iReadValues = sscanf( pcValue, "%lu", & lDefVariableValue );
							if ( iReadValues != 1){
								//Warning: The element text is not a number.
								outStatus = 2;
								continue;
							}
						}
						
						if ( ( pcValue == NULL ) ||
								( lDefVariableValue < lBiggestDefinedVarValue + iActualDefVariable ) ){
							/*Warning: no correct variable identifier / number*/
							outStatus = 2;
							lDefVariableValue = lBiggestDefinedVarValue + iActualDefVariable;
						}
						vecVariablesDefined.push_back( new cFibVariable( this ) );
						vecVariablesDefined.back()->setIntegerValue( lDefVariableValue );
						liDefinedVariables.push_front( vecVariablesDefined.back() );
						bDefinedVariablesRestored = true;
					}//end for all defined variables
				}else if ( szElementType == "values" ){
					//read vectors with values to set
					
					const TiXmlElement * pXmlVector = NULL;
					if ( pXmlElement->FirstChild( "vector" ) ){
						
						pXmlVector = pXmlElement->FirstChild( "vector" )->ToElement();
					}
					for( ; pXmlVector != NULL;
							pXmlVector = pXmlVector->NextSiblingElement( "vector" ) ){
					
						//check the attribute of the vector
						const char * szVectorXmlType = pXmlVector->Attribute( "type" );
						
						if ( szVectorXmlType == NULL ){
							outStatus = 2;
							continue;
						}else if ( string( "set" ).compare( szVectorXmlType ) != 0 ){
							outStatus = 2;
							continue;
						}
						//restore the vector
						liFibSets.push_back( cVectorFibSet( pXmlVector, outStatus,
							liDefinedVariables ) );
						liFibSets.back().setDefiningFibElement( this, false );
						bVectorFibSetRestored = true;
						if ( outStatus < 0 ){
							return;
						}
					}//end for all vectors
					
				}else{//restore the subobject
					if ( pUnderObject == NULL ){
						pUnderObject = cFibElement::restoreXml(
							pChild, outStatus, liDefinedVariables );
						if ( pUnderObject ){
							pUnderObject->pSuperiorElement = this;
						}
						if ( outStatus < 0 ){
							//an error occured
							return;
						}
					}else{//to many subobjects -> no correct set-element
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
				//invalid set-element
				if ( outStatus ){
					outStatus = 2;
				}
				continue;
		}
	}//end switch restore set-element elements
	
	if ( ! bDefinedVariablesRestored ){
		//Warning: No defined variables restored
		outStatus = 2;
		vecVariablesDefined.push_back( new cFibVariable( this ) );
	}
	if ( ! bVectorFibSetRestored ){
		//Warning: No vectors with values to set restored
		outStatus = 2;
		liFibSets.push_back( cVectorFibSet( vecVariablesDefined.size(), this ) );
	}
	if ( pUnderObject == NULL ){
		//Error: No subobject restored
		outStatus = -2;
		return;
	}
}


/**
 * This constructor restores a set-element from the stream where it is
 * stored in the compressed Fib format.
 * This constructor is for internal use only.
 *
 * @param iBitStream the stream wher the set-element is stored to in,
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
 * 	to restore Fib element, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 * @param validDomains the domains valid for restoring the Fib elements
 * @param pNextRoot the next higher root-element for the to restore
 * 	Fib elements, or the last restored root-element
 */
cFibSet::cFibSet( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains,
		cRoot * pNextRoot ):
		uiDomainNr( 0 ){
	
	if ( ! iBitStream.getStream()->good() ){
		outStatus = -1;
		return;
	}
	//read bit if a domain number is given
	unsigned char bReadedBit = 0;
	const unsigned int uiBitsRead = iBitStream.readBits( (char*)(&bReadedBit), 1 );
	if ( uiBitsRead != 1 ){
		//warning: not just one bit read
		outStatus = 2;
		bReadedBit = 0;
	}
	if ( bReadedBit != 0 ){
		//read domain number
		//find greatest domain number in the value domains
		unsignedIntFib uiMaxNumberOfSetDomain = 0;
		const unsignedIntFib uiNumberOfDomains = validDomains.getNumberOfDomains();
		for ( unsignedIntFib uiActualDomain = 1; uiActualDomain <= uiNumberOfDomains;
				uiActualDomain++ ){
			
			const cTypeElement * pTypeElement = validDomains.getType( uiActualDomain );
			if ( ( pTypeElement != NULL ) && ( pTypeElement->getType() == 14 ) ){
				//the type is a cTypeFibSet type
				const unsignedIntFib uiNumberOfSetDomain =
					((cTypeFibSet*)(pTypeElement))->getNumberOfDomain();
				if ( uiMaxNumberOfSetDomain < uiNumberOfSetDomain ){
					uiMaxNumberOfSetDomain = uiNumberOfSetDomain;
				}
			}
		}//end for search all domains for maximal set-element domain
		//read domain number
		cDomainNaturalNumber domainForSetDomainNumber( uiMaxNumberOfSetDomain );
		
		uiDomainNr = domainForSetDomainNumber.restoreIntegerValue( iBitStream, outStatus );
		if ( outStatus < 0 ){
			//Warining: domain number not readed correctly
			outStatus = 2;
			uiDomainNr = 0;
		}
	}
	//get the set-element domain
	cDomain * pDomainFibSetBase = NULL;
	for ( intFib uiActualDomain = uiDomainNr; 0 <= uiActualDomain;
			uiActualDomain-- ){
		
		const cTypeFibSet typeFibSet( uiActualDomain );
		pDomainFibSetBase = validDomains.getDomainForElement( typeFibSet );
			
		if ( pDomainFibSetBase != NULL ){
			break;
		}
	}
	const bool bStandardDomainFibSet = ( pDomainFibSetBase == NULL );
	if ( bStandardDomainFibSet ){
		const cTypeFibSet typeFibSet;
		pDomainFibSetBase = typeFibSet.getStandardDomain();
	}
	if ( ! pDomainFibSetBase->isVector() ){
		//error in domain not a vector domain -> can't load set-object
		if ( bStandardDomainFibSet ){
			delete pDomainFibSetBase;
		}
		outStatus = -2;
		return;
	}
	const cDomainVectorBasis * pDomainFibSet = (cDomainVectorBasis*)pDomainFibSetBase;
	if ( pDomainFibSet->getNumberOfElements() < 3 ){
		/*error in domain (domain for number of defined variables and / or
		number of vectors and / or vectors missing) -> can't load set-object*/
		if ( bStandardDomainFibSet ){
			delete pDomainFibSet;
		}
		outStatus = -2;
		return;
	}
	const cDomainIntegerBasis * pDomainDefVariablesCount = ((cDomainIntegerBasis*)(
		pDomainFibSet->getElementDomain( 1 ) ));
	if ( pDomainDefVariablesCount == NULL ){
		/*error in domain (domain for number of defined variables missing)
		-> can't load set-object*/
		if ( bStandardDomainFibSet ){
			delete pDomainFibSet;
		}
		outStatus = -2;
		return;
	}
	//restore the number of defined variables
	const unsignedIntFib uiNumberDefVariables =
		pDomainDefVariablesCount->restoreIntegerValue( iBitStream, outStatus );
	if ( outStatus < 0 ){
		if ( bStandardDomainFibSet ){
			delete pDomainFibSet;
		}
		return;
	}
	
	//restore number of vectors with the to set values
	const cDomainIntegerBasis * pDomainVectorsCount = ((cDomainIntegerBasis*)(
		pDomainFibSet->getElementDomain( 2 ) ));
	if ( pDomainVectorsCount == NULL ){
		/*error in domain (domain for number of vectors with the to set values missing)
		-> can't load set-object*/
		if ( bStandardDomainFibSet ){
			delete pDomainFibSet;
		}
		outStatus = -2;
		return;
	}
	//restore number of vectors with the to set values
	const unsignedLongFib uiNumberOfVectors =
		pDomainVectorsCount->restoreIntegerValue( iBitStream, outStatus );
	if ( outStatus < 0 ){
		if ( bStandardDomainFibSet ){
			delete pDomainFibSet;
		}
		return;
	}
	
	//get domain for the vectors with the to set values
	const cDomain * pDomainFibSetVectorDom = pDomainFibSet->getElementDomain( 3 );
	if ( ( pDomainFibSetVectorDom == NULL ) || ( ! pDomainFibSetVectorDom->isVector() ) ){
		/*error in domain (domain for the vectors with the to set values
		 * missing or not a vector domain) -> can't load set-object*/
		if ( bStandardDomainFibSet ){
			delete pDomainFibSet;
		}
		outStatus = -2;
		return;
	}
	const cDomainVectorBasis * pDomainFibSetVector = ((cDomainVectorBasis*)(
		pDomainFibSetVectorDom ));
	
	//get the domain for the variables in this vector
	const cTypeVariable typeVariable;
	//return the variable domain
	const cDomainIntegerBasis * pDomainVariable = (cDomainIntegerBasis*)
		validDomains.getDomainForElement( typeVariable );
	const bool bStandardDomainVariable = ( pDomainVariable == NULL );
	if ( bStandardDomainVariable ){
		//use the standard domain
		pDomainVariable = (cDomainIntegerBasis*)typeVariable.getStandardDomain();
	}
	//restore the vectors with the to set values
	for ( unsignedLongFib uiActualVector = 1;
			uiActualVector <= uiNumberOfVectors; uiActualVector++ ){
		
		liFibSets.push_back( cVectorFibSet( iBitStream, outStatus,
			liDefinedVariables, pDomainFibSetVector, pDomainVariable,
			uiNumberDefVariables ) );
		
		liFibSets.back().setDefiningFibElement( this, false );
		if ( outStatus < 0 ){
			break;
		}
	}//end for restore the vectors with the to set values
	if ( bStandardDomainFibSet ){
		delete pDomainFibSet;
	}
	if ( bStandardDomainVariable ){
		delete pDomainVariable;
	}
	//create defined variables for the subobject
	const unsignedIntFib uiCountDefVariablesBefor = liDefinedVariables.size();
	for ( unsignedIntFib uiNumberOfVariable = 1;
			uiNumberOfVariable <= uiNumberDefVariables; uiNumberOfVariable++ ){
		
		vecVariablesDefined.push_back( new cFibVariable( this ) );
		vecVariablesDefined.back()->setIntegerValue(
			uiCountDefVariablesBefor + uiNumberOfVariable );
		liDefinedVariables.push_front( vecVariablesDefined.back() );
	}
	if ( outStatus < 0 ){
		//an error occured -> don't restore subobject
		return;
	}

	//restore the subobject
	pUnderObject = cFibElement::restoreInternal( iBitStream, outStatus,
		liDefinedVariables, validDomains, pNextRoot );
	if ( pUnderObject ){
		pUnderObject->pSuperiorElement = this;
	}
}


/**
 * destructor
 */
cFibSet::~cFibSet(){
	
	for ( vector< cFibVariable * >::iterator
			itrDefVariable = vecVariablesDefined.begin();
			itrDefVariable != vecVariablesDefined.end(); itrDefVariable++ ){
		
		delete (*itrDefVariable);
	}
	//automatic: vecVariablesDefined.clear()
}


/**
 * @see getTypeName
 * @return a character for the typ of the Fib element
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
char cFibSet::getType() const{
	return 'v';
}


/**
 * This method checks, if this Fib-element is an valid Fib-element.
 *
 * @return true if this Fib-element is an valid Fib-element, else false
 */
bool cFibSet::isValidFibElement() const{
	
	if ( vecVariablesDefined.empty() ){
		//no defined variables -> set-element not valid
		return false;
	}
	if ( liFibSets.empty() ){
		//no vectors with values to set -> set-element not valid
		return false;
	}
	//check contained vectors
	const unsignedIntFib uiNumberDefVar = vecVariablesDefined.size();
	for ( list< cVectorFibSet >::const_iterator itrActualVector = liFibSets.begin();
			 itrActualVector != liFibSets.end(); itrActualVector++ ){
	
		if ( itrActualVector->getNumberOfElements() != uiNumberDefVar ){
			//vector has wrong number of elements
			return false;
		}
	}
	//everything is ok
	return true;
}


/**
 * This method evaluades the Fib object.
 *
 * @param evaluePosition a reference to the object with the
 * 	evaluePosition() method to evalue /store the positions and ther
 * 	properties; everytime a point (to evalue) is reached in the
 * 	evaluation, this method is called with the position and the
 * 	properties of the point; @see iEvaluePosition
 * @param objectPoint the object point in the order of true part objects
 * 	to evalue
 * @param liVecProperties a list with the property vectors which should
 * 	be global for the evalued object
 * @return if the evaluation was successfull true, else false
 */
bool cFibSet::evalueObject( iEvaluePosition & evaluePosition,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties ) const{
	
	if ( pUnderObject == NULL ){
		//nothing to evalue
		return false;
	}
	//for every vector with to set values
	const unsigned int uiNumberOfDefVariables = vecVariablesDefined.size();
	for ( list< cVectorFibSet >::const_iterator itrActualVector = liFibSets.begin();
			 itrActualVector != liFibSets.end(); itrActualVector++ ){
		//set the defined variables to the values of the vector
		vector< cFibVariable* >::iterator itrActualDefVariable =
			const_cast<cFibSet*>(this)->vecVariablesDefined.begin();
		for ( unsigned int uiActualDefVariable = 1;
				uiActualDefVariable <= uiNumberOfDefVariables;
				uiActualDefVariable++, itrActualDefVariable++ ){
			
			(*itrActualDefVariable)->setValue(
				itrActualVector->getValue( uiActualDefVariable ) );
		}
		//call subobject with the defined variables set to the actual to set values
		list<cVectorProperty> liVecSubProperties = liVecProperties;
		
		const bool bUnderObjectEvalued = pUnderObject->evalueObject(
			evaluePosition, objectPoint, liVecSubProperties );
		if ( ! bUnderObjectEvalued ){
			//stop evaluing
			return false;
		}
	}//end for all vectors with to set values
	return true;
}


/**
 * This method evaluades the Fib object.
 * Evertime a Fib elements, with a type of the given type chars in
 * liCFibElementTyps, is reached while evaluation, it is given
 * back with the properties which it has.
 * Ever point element is given back. The type chars for point elements
 * don't need to be in the list liCFibElementTyps.
 *
 * @param evalueFibElement a reference to the object with the
 * 	evalueElement() method to evalue /store the Fib elements and ther
 * 	properties; everytime a Fib element (with one of the type given
 * 	in liCFibElementTyps) is reached in the evaluation, the method
 * 	evalueElement() of this objects is called with the Fib element
 * 	and the properties of the Fib element; @see iEvalueFibElement
 * @param objectPoint the object point in the order of true part objects
 * 	to evalue
 * @param liVecProperties a list with the property vectors which should
 * 	be global for the evalued object
 * @param liCFibElementTyps a list with the type chars (@see getType() )
 * 	of the Fib elements to return
 * @return if the evaluation was successfull true, else false
 */
bool cFibSet::evalueObject( iEvalueFibElement & evalueFibElement,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties,
		const list<char> & liCFibElementTyps ){
	
	//check if this Fib element should be given back with evalueElement()
	const char cThisType = getType();
	for ( list<char>::const_iterator itrCType = liCFibElementTyps.begin();
			itrCType != liCFibElementTyps.end(); itrCType++ ){
		
		if ( (*itrCType) == cThisType ){
			//call evalueElement() with this element
			return evalueFibElement.evalueElement( *this, liVecProperties );
		}
	}//else if this element shouldn't be returned -> evalue the subobject

	if ( pUnderObject == NULL ){
		//nothing to evalue
		return false;
	}
	//for every vector with to set values
	const unsigned int uiNumberOfDefVariables = vecVariablesDefined.size();
	for ( list< cVectorFibSet >::const_iterator itrActualVector = liFibSets.begin();
			 itrActualVector != liFibSets.end(); itrActualVector++ ){
		//set the defined variables to the values of the vector
		vector< cFibVariable* >::iterator itrActualDefVariable =
			const_cast<cFibSet*>(this)->vecVariablesDefined.begin();
		for ( unsigned int uiActualDefVariable = 1;
				uiActualDefVariable <= uiNumberOfDefVariables;
				uiActualDefVariable++, itrActualDefVariable++ ){
			
			(*itrActualDefVariable)->setValue(
				itrActualVector->getValue( uiActualDefVariable ) );
		}
		//call subobject with the defined variables set to the actual to set values
		list<cVectorProperty> liVecSubProperties = liVecProperties;
		
		const bool bUnderObjectEvalued = pUnderObject->evalueObject(
			evalueFibElement, objectPoint, liVecSubProperties, liCFibElementTyps );
		if ( ! bUnderObjectEvalued ){
			//stop evaluing
			return false;
		}
	}//end for all vectors with to set values
	return true;
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
 * @param lMaxTime the maximum time for the evaluation, the returned value
 * 	will not be greater than this value; the value 0 stands for infinity,
 * 	so the evaluation won't be stoped
 * @return a value for the time needed to evalue the object
 */
unsignedLongFib cFibSet::getTimeNeed( unsignedLongFib lMaxTime ) const{
	
	unsignedLongFib ulTimeNeeded = vecVariablesDefined.size() * liFibSets.size();
	if ( ( lMaxTime != 0 ) && ( lMaxTime <= ulTimeNeeded ) ){
		return lMaxTime;
	}
	if ( pUnderObject == NULL ){
		return ulTimeNeeded;
	}

	//for every vector with to set values
	const unsigned int uiNumberOfDefVariables = vecVariablesDefined.size();
	for ( list< cVectorFibSet >::const_iterator itrActualVector = liFibSets.begin();
			 itrActualVector != liFibSets.end(); itrActualVector++ ){
		//set the defined variables to the values of the vector
		vector< cFibVariable* >::iterator itrActualDefVariable =
			const_cast<cFibSet*>(this)->vecVariablesDefined.begin();
		for ( unsigned int uiActualDefVariable = 1;
				uiActualDefVariable <= uiNumberOfDefVariables;
				uiActualDefVariable++, itrActualDefVariable++ ){
			
			(*itrActualDefVariable)->setValue(
				itrActualVector->getValue( uiActualDefVariable ) );
		}
		//call subobject with the defined variables set to the actual to set values
		if ( lMaxTime == 0 ){
			ulTimeNeeded += pUnderObject->getTimeNeed( 0 );
		}else{
			ulTimeNeeded += pUnderObject->getTimeNeed( lMaxTime - ulTimeNeeded );
			if ( lMaxTime <= ulTimeNeeded ){
				return lMaxTime;
			}
		}
	}//end for all vectors with to set values
	return ulTimeNeeded;
}


/**
 * This method evaluades the size of the Fib object in bits in the
 * compressed file form.
 *
 * @see store()
 * @return the size of the Fib object in bits in the compressed form
 */
unsignedLongFib cFibSet::getCompressedSize() const{
	
	//add bits for introduction plus domain number bit
	unsignedLongFib ulCompressedSize = 16 + 1;
	//get the value domain
	const cDomains validDomains = getValidValueDomains();
	if ( uiDomainNr != 0 ){
		//if needed add bits for the domain number
		//find greatest domain number in the value domains
		unsignedIntFib uiMaxNumberOfSetDomain = 0;
		const unsignedIntFib uiNumberOfDomains = validDomains.getNumberOfDomains();
		for ( unsignedIntFib uiActualDomain = 1; uiActualDomain <= uiNumberOfDomains;
				uiActualDomain++ ){
			
			const cTypeElement * pTypeElement = validDomains.getType( uiActualDomain );
			if ( ( pTypeElement != NULL ) && ( pTypeElement->getType() == 14 ) ){
				//the type is a cTypeFibSet type
				const unsignedIntFib uiNumberOfSetDomain =
					((cTypeFibSet*)(pTypeElement))->getNumberOfDomain();
				if ( uiMaxNumberOfSetDomain < uiNumberOfSetDomain ){
					uiMaxNumberOfSetDomain = uiNumberOfSetDomain;
				}
			}
		}//end for search all domains for maximal set-element domain
		//read domain number
		const cDomainNaturalNumber domainForSetDomainNumber( uiMaxNumberOfSetDomain );
		
		ulCompressedSize += domainForSetDomainNumber.getCompressedSizeForValue();
	}
	//get the set-element domain
	cDomain * pDomainFibSetBase = NULL;
	for ( intFib uiActualDomain = uiDomainNr; 0 <= uiActualDomain;
			uiActualDomain-- ){
		
		const cTypeFibSet typeFibSet( uiActualDomain );
		pDomainFibSetBase = validDomains.getDomainForElement( typeFibSet );
			
		if ( pDomainFibSetBase != NULL ){
			break;
		}
	}
	const bool bStandardDomainFibSet = ( pDomainFibSetBase == NULL );
	if ( bStandardDomainFibSet ){
		const cTypeFibSet typeFibSet;
		pDomainFibSetBase = typeFibSet.getStandardDomain();
	}
	if ( ! pDomainFibSetBase->isVector() ){
		//Error: not a vector domain
		if ( bStandardDomainFibSet ){
			delete pDomainFibSetBase;
		}
		return ulCompressedSize;
	}
	const cDomainVectorBasis * pDomainFibSet =
		(const cDomainVectorBasis*)pDomainFibSetBase;
	
	const cDomainIntegerBasis * pDomainDefVariablesCount = ((const cDomainIntegerBasis*)(
		pDomainFibSet->getElementDomain( 1 ) ));
	if ( pDomainDefVariablesCount != NULL ){
		//add bits for defined variables count
		ulCompressedSize += pDomainDefVariablesCount->getCompressedSizeForValue();
	}
	
	//add compressed size for number of vectors with the to set values
	const cDomainIntegerBasis * pDomainVectorsCount = ((const cDomainIntegerBasis*)(
		pDomainFibSet->getElementDomain( 2 ) ));
	if ( pDomainVectorsCount != NULL ){
		//add bits for vector with the values to set count
		ulCompressedSize += pDomainVectorsCount->getCompressedSizeForValue();
	}
	
	//get domain for the vectors with the to set values
	const cDomain * pDomainFibSetVectorDom = pDomainFibSet->getElementDomain( 3 );
	if ( ( pDomainFibSetVectorDom != NULL ) && ( pDomainFibSetVectorDom->isVector() ) ){
		
		const cDomainVectorBasis * pDomainFibSetVector = ((const cDomainVectorBasis*)(
			pDomainFibSetVectorDom ));
		
		//get the domain for the variables in this vector
		const cTypeVariable typeVariable;
		//return the variable domain
		const cDomainIntegerBasis * pDomainVariable = (const cDomainIntegerBasis*)
			validDomains.getDomainForElement( typeVariable );
		const bool bStandardDomainVariable = ( pDomainVariable == NULL );
		if ( bStandardDomainVariable ){
			//use the standard domain
			pDomainVariable = (cDomainIntegerBasis*)typeVariable.getStandardDomain();
		}
		
		//add compressed size for the vector elements
		for ( list<cVectorFibSet>::const_iterator itrFibSet = liFibSets.begin();
				itrFibSet != liFibSets.end(); itrFibSet++ ){
			//call method with given domains for variables and values
			ulCompressedSize += itrFibSet->getCompressedSize(
				*pDomainFibSetVector, *pDomainVariable );
		}
		if ( bStandardDomainVariable ){
			//delete standard domain
			delete pDomainVariable;
		}
	}
	if ( bStandardDomainFibSet ){
		delete pDomainFibSetBase;
	}
	//add compressed size for the subobject
	if ( pUnderObject != NULL ){
		ulCompressedSize += pUnderObject->getCompressedSize();
	}
	return ulCompressedSize;
}


/**
 * This method checks if the given variable is used in the given
 * direction from this Fib element.
 *
 * @see cFibVariable
 * @see isDefinedVariable()
 * @param pVariable the variable to check if it is used
 * @param direction the direction from this Fib element, in which the
 * 	variable should be used; standardvalue is ED_POSITION so yust
 * 	this Fib element will be checked
 * @return true if the variable is used, else false
 */
bool cFibSet::isUsedVariable( const cFibVariable * pVariable,
		edDirection direction ) const{
	
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		//check to set vectors
		for ( list<cVectorFibSet>::const_iterator itrFibSet = liFibSets.begin();
				itrFibSet != liFibSets.end(); itrFibSet++ ){
		
			const bool bVariableUsed = itrFibSet->isUsedVariable( pVariable );
			if ( bVariableUsed ){
				return true;
			}
		}
	}
	return cFibLimb::isUsedVariable( pVariable, direction );
}


/**
 * This method returns all variables used in the given direction from
 * this Fib element.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @see isDefinedVariable()
 * @param direction the direction from this Fib element, in which the
 * 	variable should be used; standardvalue is ED_POSITION so yust
 * 	this Fib element will be checked
 * @return the set with all variables used in the given direction from
 * 	this Fib element
 */
set<cFibVariable*> cFibSet::getUsedVariables( edDirection direction ){
	
	set<cFibVariable*> setUsedVariables(
		cFibLimb::getUsedVariables( direction ) );
	//add the used variables in the vectors of this set-element
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		//check to set vectors
		for ( list<cVectorFibSet>::iterator itrFibSet = liFibSets.begin();
				itrFibSet != liFibSets.end(); itrFibSet++ ){
			
			set<cFibVariable*> setUsedVarVector = itrFibSet->getUsedVariables();
			
			setUsedVariables.insert( setUsedVarVector.begin(),
				setUsedVarVector.end() );
		}
	}
	return setUsedVariables;
}


/**
 * This method checks if the given variable is defined in the given
 * direction from this Fib element.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @param pVariable the variable to check if it is defined
 * @param direction the direction from this Fib element, in which the
 * 	variable should be defined; standardvalue is ED_POSITION so yust
 * 	this Fib element will be checked
 * @param pCallingFibElement the Fib-Element which called this method
 * @return true if the variable is used, else false
 */
bool cFibSet::isDefinedVariableInternal( const cFibVariable * pVariable,
		edDirection direction,
		const cFibElement * pCallingFibElement ) const{
	
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		//check the defiened variable
		for ( vector<cFibVariable*>::const_iterator
				itrDefVariable = vecVariablesDefined.begin();
				itrDefVariable != vecVariablesDefined.end(); itrDefVariable++ ){
			
			if ( pVariable == (*itrDefVariable) ){
				return true;
			}
		}//variable not defined here
	}
	return cFibLimb::isDefinedVariableInternal(
		pVariable, direction, pCallingFibElement );
}


/**
 * This method returns all variables defined in the given direction from
 * this Fib element.
 * This is for intern use to get the correct data from
 * getDefinedVariables() without pCallingFibElement.
 *
 * @see cFibVariable
 * @see getUsedVariables()
 * @see isDefinedVariable()
 * @param direction the direction from this Fib element, in which the
 * 	variable should be used; standardvalue is ED_POSITION so yust
 * 	this Fib element will be checked
 * @param pCallingFibElement the Fib-Element which called this method
 * @return the set with all variables used in the given direction from
 * 	this Fib element
 */
list<cFibVariable*> cFibSet::getDefinedVariablesInternal(
		edDirection direction,
		const cFibElement * pCallingFibElement ){

	list<cFibVariable*> liDefinedVariables;
	
	if ( (direction == ED_ALL) || ( direction == ED_BELOW ) ||
			(direction == ED_BELOW_EQUAL) ){
		//check in subobject
		liDefinedVariables = cFibLimb::getDefinedVariablesInternal(
			ED_BELOW, pCallingFibElement );
		
		if ( direction == ED_BELOW ){
			return liDefinedVariables;
		}
	}
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		//insert the defined variables this set-element defines
		liDefinedVariables.insert( liDefinedVariables.begin(),
			vecVariablesDefined.begin(), vecVariablesDefined.end() );
	}
	if ( (direction == ED_ALL) || ( direction == ED_HIGHER ) ||
			(direction == ED_HIGHER_EQUAL) ){
		//elements to check in the direction
		list<cFibVariable*> liDefinedVariablesOfSuperObject =
				cFibLimb::getDefinedVariablesInternal(
					ED_HIGHER, pCallingFibElement );
			
		liDefinedVariables.insert( liDefinedVariables.begin(),
			liDefinedVariablesOfSuperObject.begin(),
			liDefinedVariablesOfSuperObject.end() );
	}
	return liDefinedVariables;
}


/**
 * This method replace the variable pVariableOld with the variable
 * pVariableNew in the object.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @see isDefinedVariable()
 * @param pVariableOld the variable to replace
 * @param pVariableNew the variable with which the variable pVariableOld
 * 	is to be replace
 * @return true if the variable pVariableOld is replaced with pVariableNew,
 * 	else false
 */
bool cFibSet::replaceVariable( cFibVariable * pVariableOld,
		cFibVariable * pVariableNew ){
	
	if ( (pVariableOld == NULL) || (pVariableNew == NULL) ){
		//can't replace
		return false;
	}
	for ( list<cVectorFibSet>::iterator itrFibSet = liFibSets.begin();
			itrFibSet != liFibSets.end(); itrFibSet++ ){
		
		//replace variable in vector
		if ( ! itrFibSet->replaceVariable( pVariableOld, pVariableNew ) ){
			return false;
		}
	}
	return cFibLimb::replaceVariable( pVariableOld, pVariableNew );
}


/**
 * This method copies the Fib element on the specified position.
 * Variables which are not defined in the Fib element but used
 * don't change ther reference.
 *
 * @see getType()
 * @param cType the type of the Fib element to copy
 * @param elementPoint the number of the Fib element, in the order of
 * 	Fib elements of the given type cType, to copy
 * @return the copy of the Fib element
 */
cFibElement * cFibSet::copyElement( const char cType, const unsignedIntFib
		elementPoint, bool bAbsolute ) const{
	
	if ( elementPoint == 0 ){
		//copy this element
		return new cFibSet( *this );
	}//else get the Fib element and copy it
	
	const cFibElement * pFibElementToCopy = getConstFibElement(
		cType, elementPoint, bAbsolute );
	
	if ( pFibElementToCopy ){
		return ( pFibElementToCopy->copyElement( 'u', 0 ) );
	}//else
	return NULL;
}


/**
 * This method checks if the given Fib object is equal to this Fib
 * object.
 * Variables can be others, but must be defined and used in equivalent
 * Fib elements.
 *
 * @param fibObject the Fib object to which this Fib object should be
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
 * @return true if this Fib object is equal to the given Fib object,
 * 	else false
 */
bool cFibSet::equalInternal( const cFibElement & fibObject,
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
 * This method checks if the given Fib element is equal to this Fib
 * element.
 * The subobjects are not compared, not even ther count is compared.
 * Used variables can be others.
 *
 * @param fibElement the Fib element to which this Fib element should be
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
 * @return true if this Fib element is equal to the given Fib element,
 * 	else false
 */
bool cFibSet::equalElementInternal( const cFibElement & fibElement,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{

	if ( getType() != fibElement.getType() ){
		return false;
	}
	const cFibSet * pFibSetElement = (const cFibSet*)(&fibElement);
	if ( vecVariablesDefined.size() != pFibSetElement->vecVariablesDefined.size() ){
		return false;
	}
	if ( getDomainNr() != pFibSetElement->getDomainNr() ){
		//domain number not equal -> Fib elements not equal
		return false;
	}
	//compare to set vectors
	if ( liFibSets.size() != pFibSetElement->liFibSets.size() ){
		//number of vectors not equal -> Fib elements not equal
		return false;
	}
	//compare vectors with values to set
	list<cVectorFibSet>::const_iterator itrFibSetOther =
		pFibSetElement->liFibSets.begin();
	for ( list<cVectorFibSet>::const_iterator itrFibSet = liFibSets.begin();
			itrFibSet != liFibSets.end(); itrFibSet++, itrFibSetOther++ ){
		
		if ( ! itrFibSet->equalInternal( *itrFibSetOther,
				mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
			return false;
		}
	}
	return true;
}


/**
 * This method checks if the given Fib element sets the variable to
 * the same values as this Fib element.
 *
 * @param pVariableOwn a pointer to a defined variable in this Fib element,
 * 	it is compared to the equivalent variable pVariable in the given
 * 	Fib element fibElement
 * @param fibElement the Fib element, to which this Fib element should be
 * 	compared
 * @param pVariable a pointer to a defined variable in the other
 * 	Fib element fibElement
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
 * @return true if this Fib element sets the variable to the same
 * 	values as this Fib element
 */
bool cFibSet::equalValuesSetInternal( const cFibVariable * pVariableOwn,
		const cFibElement & fibElement,
		const cFibVariable * pVariable,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{
	
	if ( fibElement.getType() != getType() ){
		//not equal element type -> not equal values set
		return false;
	}
	const cFibSet * pFibSetElement = (const cFibSet*)(&fibElement);
	//check if the variables are defined on the same position
	vector<cFibVariable*>::const_iterator itrDefVarOther =
		pFibSetElement->vecVariablesDefined.begin();
	bool bDefVariablesOnSamePosition = false;
	for ( vector<cFibVariable*>::const_iterator itrDefVar = vecVariablesDefined.begin();
			( itrDefVar != vecVariablesDefined.end() ) &&
			( itrDefVarOther != pFibSetElement->vecVariablesDefined.end() );
			itrDefVar++, itrDefVarOther++ ){
		
		if ( ( (*itrDefVar) == pVariableOwn ) || ( (*itrDefVarOther) == pVariable ) ){
			//defined variable found in a Fib element
			if ( ( (*itrDefVar) == pVariableOwn ) && ( (*itrDefVarOther) == pVariable ) ){
				//the defined variables are on the same position
				bDefVariablesOnSamePosition = true;
				break;
			}else{/*the defined variables are not on the same position
				-> not equal values set*/
				return false;
			}
		}
	}//end for check if the variables are defined on the same position
	if ( ! bDefVariablesOnSamePosition ){
		/*the defined variables are not on the same position
		 -> not equal values set*/
		return false;
	}
	
	const map< const cFibElement *, const cFibElement * >::const_iterator
		itrEqualDefinedVariable = mapEqualDefinedVariables.find( this );
	if ( ( itrEqualDefinedVariable != mapEqualDefinedVariables.end() ) &&
			( itrEqualDefinedVariable->second == &fibElement ) ){
		//Fib elements compared befor as equal
		return true;
	}//else compare Fib elements
	const bool bEqualElement = equalElementInternal(
		fibElement, mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects );
	if ( bEqualElement ){
		mapEqualDefinedVariables.insert( make_pair( this, &fibElement ) );
		return true;
	}
	return false;
}


/**
 * This method stores this Fib object in the XML -format into the
 * given stream.
 *
 * @param stream the stream where this Fib object should be stored to
 * @return true if this Fib object is stored, else false
 */
bool cFibSet::storeXml( ostream &stream ) const{

	bool bReturnValue = true;
#ifdef FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	stream<<"<set elementNr=\""<<getNumberOfElement()<<"\"";
#else //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	stream<<"<set";
#endif //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	if ( uiDomainNr == 0 ){
		stream<<">"<<endl;
	}else{
		stream<<" domainNr=\""<< uiDomainNr <<"\">"<<endl;
	}
	
	stream<<"<defined_variables>"<<endl;
	for ( vector<cFibVariable*>::const_iterator
			itrDefVariable = vecVariablesDefined.begin();
			itrDefVariable != vecVariablesDefined.end(); itrDefVariable++ ){
		
		stream<<"<variable>"<<(*itrDefVariable)->getIntegerValue()<<"</variable>"<<endl;
	}
	stream<<"</defined_variables>"<<endl;
	
	stream<<"<values>"<<endl;
	for ( list<cVectorFibSet>::const_iterator itrFibSet = liFibSets.begin();
			itrFibSet != liFibSets.end(); itrFibSet++ ){
		
		//store to set vectors
		if ( ! itrFibSet->storeXml( stream ) ){
			return false;
		}
	}
	stream<<"</values>"<<endl;
	if ( pUnderObject ){
		bReturnValue &= pUnderObject->storeXml( stream );
	}
	stream<<"</set>"<<endl;
	return bReturnValue;
}


/*
 * cFibSet-element methods
 */



/**
 * @return the number of variables this set-element defines
 */
unsignedIntFib cFibSet::getNumberOfVariables() const{
	
	return vecVariablesDefined.size();
}


/**
 * This method returns a pointer to the uiPosition'th from this
 * set-element defined variable.
 *
 * @param uiPosition the number of the from this set-element defined
 * 	variable to return (counting begins with 1)
 * @return a pointer to the uiPosition'th from this set-element defined
 * 	variable, or NULL if non such exists
 */
cFibVariable * cFibSet::getDefinedVariable( const unsignedLongFib uiPosition ){
	
	if ( ( uiPosition < 1 ) || ( vecVariablesDefined.size() < uiPosition ) ){
		//no such defined variables
		return NULL;
	}
	return vecVariablesDefined[ uiPosition - 1 ];
}



/**
 * @see uiDomainNr
 * @return the number of the set-element domain for this set-element
 */
unsignedIntFib cFibSet::getDomainNr() const{
	
	return uiDomainNr;
}


/**
 * This method sets the number of the set-element domain for this
 * set-element.
 * 
 * @see uiDomainNr
 * @param uiInDomainNumber the number of the set-element domain for this set-element
 */
void cFibSet::setDomainNr( const unsignedLongFib uiInDomainNumber ){
	
	uiDomainNr = uiInDomainNumber;
}


/**
 * @see liFibSets
 * @return the number of vectors or sets of values this set-element contains
 */
unsignedLongFib cFibSet::getNumberOfVectors() const{
	
	return liFibSets.size();
}


/**
 * @return a vector with all vectors / sets of values of this set-element
 * @see liFibSets
 */
const vector< cVectorFibSet > cFibSet::getVectors(){
	
	return vector< cVectorFibSet >( liFibSets.begin(), liFibSets.end() );
}


/**
 * This method sets all vectors / sets of values of this set-element to
 * the given vectors.
 * 
 * @see liFibSets
 * @param vecSets a vector with all vectors / sets of values this
 * 	set-element should contain
 * @return true if the vectors wher set, else false and the vectors of
 * 	this set-element unchanged
 */
bool cFibSet::setVectors( const vector< cVectorFibSet > & vecSets ){
	
	//check vectors
	const unsignedIntFib uiNumberOfDefVariables =
		vecVariablesDefined.size();
	for ( vector<cVectorFibSet>::const_iterator itrFibSet = vecSets.begin();
			 itrFibSet != vecSets.end(); itrFibSet++ ){
		
		if ( itrFibSet->getNumberOfElements() != uiNumberOfDefVariables ){
			//not correct number of vector elements -> can't change to set vectors
			return false;
		}
	}//end for check vectors
	//set vectors
	liFibSets.clear();
	liFibSets.insert( liFibSets.begin(), vecSets.begin(), vecSets.end() );
	
	for ( list<cVectorFibSet>::iterator itrFibSet = liFibSets.begin();
			 itrFibSet != liFibSets.end(); itrFibSet++ ){
		
		itrFibSet->setDefiningFibElement( this, false );
	}
	return true;
}


/**
 * This method returns a pointer to the uiPosition'th vector of this
 * set-element.
 *
 * @see liFibSets
 * @param uiPosition the number of the vector to return (counting begins
 * 	with 1)
 * @return a pointer to the uiPosition'th vector, or NULL if non such exists
 */
cVectorFibSet * cFibSet::getVector( const unsignedLongFib uiPosition ){
	
	list<cVectorFibSet>::iterator itrFibSetToReturn =
		getListElement( liFibSets, uiPosition );
	if ( itrFibSetToReturn == liFibSets.end() ){
		return NULL;
	}
	return &(*itrFibSetToReturn);
}


/**
 * This method sets the uiPosition'th vector of this set-element to the
 * given vector.
 *
 * @see liFibSets
 * @param vecSet the vector to set
 * @param uiPosition the position wher the to set vector should stand
 * 	in this set-element (counting begins with 1)
 * @return true if the vector wher set, else false and the vectors of
 * 	this set-element unchanged
 */
bool cFibSet::setVector( const cVectorFibSet & vecSet,
		const unsignedLongFib uiPosition ){
	
	if ( vecSet.getNumberOfElements() != vecVariablesDefined.size() ){
		//the to set vector has not the correct number of elements
		return false;
	}
	list<cVectorFibSet>::iterator itrFibSetToChange =
		getListElement( liFibSets, uiPosition );
	if ( itrFibSetToChange == liFibSets.end() ){
		return false;
	}
	(*itrFibSetToChange) = vecSet;
	itrFibSetToChange->setDefiningFibElement( this, false );
	return true;
}


/**
 * This method adds the given vector to the existing vectors.
 *
 * @see liFibSets
 * @param vecSet a reference to the to add vector
 * @param uiPosition the position wher the vecSet should be added
 * 	(counting begins with 1); if 0 the vecSet or greater than the number
 * 	of vectors the vector will be added to the end of the vector list
 * @return true if the vecSet was added, else false
 */
bool cFibSet::addVector( const cVectorFibSet & vecSet,
		const unsignedLongFib uiPosition ){
	
	if ( vecSet.getNumberOfElements() != vecVariablesDefined.size() ){
		//the to set vector has not the correct number of elements
		return false;
	}
	if ( ( uiPosition < 1 ) || ( liFibSets.size() < uiPosition ) ){
		liFibSets.push_back( vecSet );
		liFibSets.back().setDefiningFibElement( this, false );
		return true;
	}
	list<cVectorFibSet>::iterator itrFibSetToChange =
		getListElement( liFibSets, uiPosition );
	if ( itrFibSetToChange == liFibSets.end() ){
		return false;
	}
	itrFibSetToChange = liFibSets.insert( itrFibSetToChange, vecSet );
	itrFibSetToChange->setDefiningFibElement( this, false );
	return true;
}


/**
 * This method deletes the uiPosition'th vector from the existing vectors.
 *
 * @param uiPosition the position, wher the vector should be deleted from
 * 	(counting begins with 1)
 * @return true if the vector was deleted, else false
 */
bool cFibSet::deleteVector( const unsignedLongFib uiPosition ){
	
	list<cVectorFibSet>::iterator itrFibSetToChange =
		getListElement( liFibSets, uiPosition );
	if ( itrFibSetToChange == liFibSets.end() ){
		return false;
	}
	liFibSets.erase( itrFibSetToChange );
	return true;
}


/**
 * This method stores this Fib object in the compressed Fib -format
 * into the given stream.
 * It is needed becouse the stream can yust store byts but the size of
 * Fib elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the Fib elements.
 *
 * @see store
 * @param stream the stream where this Fib object should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if this Fib object is stored, else false
 */
bool cFibSet::storeBit( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{

	if ( pUnderObject == NULL ){
		return false;
	}
	
	const char szInitiation[] = { 0x1F, 0x00 };//0000 0000; 0001 1111
	const bool bInitiationStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, szInitiation, 16 );
	if ( ! bInitiationStored ){
		return false;
	}
	//get the needed domains
	cDomains validDomains = getValidValueDomains();
	//write information for the domain number
	if ( uiDomainNr == 0 ){
		const char cDomainNrBit = 0x00;
		const bool bDomainNrBitStored = nBitStream::store( stream, cRestBits,
			uiRestBitPosition, cDomainNrBit, 1 );
		if ( ! bDomainNrBitStored ){
			return false;
		}
	}else{
		//store bit for domain number
		const char cDomainNrBit = 0x01;
		const bool bDomainNrBitStored = nBitStream::store( stream, cRestBits,
			uiRestBitPosition, cDomainNrBit, 1 );
		if ( ! bDomainNrBitStored ){
			return false;
		}
		//read domain number
		//find greatest domain number in the value domains
		unsignedIntFib uiMaxNumberOfSetDomain = 0;
		const unsignedIntFib uiNumberOfDomains = validDomains.getNumberOfDomains();
		for ( unsignedIntFib uiActualDomain = 1; uiActualDomain <= uiNumberOfDomains;
				uiActualDomain++ ){
			
			const cTypeElement * pTypeElement = validDomains.getType( uiActualDomain );
			if ( ( pTypeElement != NULL ) && ( pTypeElement->getType() == 14 ) ){
				//the type is a cTypeFibSet type
				const unsignedIntFib uiNumberOfSetDomain =
					((cTypeFibSet*)(pTypeElement))->getNumberOfDomain();
				if ( uiMaxNumberOfSetDomain < uiNumberOfSetDomain ){
					uiMaxNumberOfSetDomain = uiNumberOfSetDomain;
				}
			}
		}//end for search all domains for maximal set-element domain
		//read domain number
		cDomainNaturalNumber domainForSetDomainNumber( uiMaxNumberOfSetDomain );
		
		const bool bDomainNumberStored = domainForSetDomainNumber.storeUnscaledValue(
			uiDomainNr, stream, cRestBits, uiRestBitPosition );
		if ( ! bDomainNumberStored ){
			//error: domain number not stored
			return false;
		}
	}
	
	//get the set-element domain
	cDomain * pDomainFibSetBase = NULL;
	for ( intFib uiActualDomain = uiDomainNr; 0 <= uiActualDomain;
			uiActualDomain-- ){
		
		const cTypeFibSet typeFibSet( uiActualDomain );
		pDomainFibSetBase = validDomains.getDomainForElement( typeFibSet );
		
		if ( pDomainFibSetBase != NULL ){
			break;
		}
	}
	const bool bStandardDomainFibSet = ( pDomainFibSetBase == NULL );
	if ( bStandardDomainFibSet ){
		const cTypeFibSet typeFibSet;
		pDomainFibSetBase = typeFibSet.getStandardDomain();
	}
	if ( ! pDomainFibSetBase->isVector() ){
		//error: not a vector domain -> can't store set-object
		if ( bStandardDomainFibSet ){
			delete pDomainFibSetBase;
		}
		return false;
	}
	cDomainVectorBasis * pDomainFibSet = (cDomainVectorBasis*)pDomainFibSetBase;
	
	if ( pDomainFibSet->getNumberOfElements() < 3 ){
		/*error in domain (domain for number of defined variables and / or
		number of vectors and / or vectors missing) -> can't load set-object*/
		if ( bStandardDomainFibSet ){
			delete pDomainFibSet;
		}
		return false;
	}
	cDomainIntegerBasis * pDomainDefVariablesCount = ((cDomainIntegerBasis*)(
		pDomainFibSet->getElementDomain( 1 ) ));
	if ( pDomainDefVariablesCount == NULL ){
		/*error: in domain (domain for number of defined variables missing)
		-> can't store set-object*/
		if ( bStandardDomainFibSet ){
			delete pDomainFibSet;
		}
		return false;
	}
	//store the number of defined variables
	const unsignedIntFib uiNumberDefVariables = vecVariablesDefined.size();
	const bool bNumberDefVariablesStored = pDomainDefVariablesCount->storeUnscaledValue(
		uiNumberDefVariables, stream, cRestBits, uiRestBitPosition );
	if ( ! bNumberDefVariablesStored ){
		//error: number of defined variables not stored
		if ( bStandardDomainFibSet ){
			delete pDomainFibSet;
		}
		return false;
	}
	//restore number of vectors with the to set values
	cDomainIntegerBasis * pDomainVectorsCount = ((cDomainIntegerBasis*)(
		pDomainFibSet->getElementDomain( 2 ) ));
	if ( pDomainVectorsCount == NULL ){
		/*error in domain (domain for number of vectors with the to set values missing)
		-> can't store set-object*/
		if ( bStandardDomainFibSet ){
			delete pDomainFibSet;
		}
		return false;
	}
	//store number of vectors with the to set values
	const unsignedLongFib ulNumberOfVectors = liFibSets.size();
	const bool bNumberOfVectorsStored = pDomainVectorsCount->storeUnscaledValue(
		ulNumberOfVectors, stream, cRestBits, uiRestBitPosition );
	if ( ! bNumberOfVectorsStored ){
		//error: number of defined variables not stored
		if ( bStandardDomainFibSet ){
			delete pDomainFibSet;
		}
		return false;
	}
	
	//get domain for the vectors with the to set values
	cDomain * pDomainFibSetVectorDom = pDomainFibSet->getElementDomain( 3 );
	if ( ( pDomainFibSetVectorDom == NULL ) || ( ! pDomainFibSetVectorDom->isVector() ) ){
		/*error in domain (domain for the vectors with the to set values
		 * missing or not a vector domain) -> can't load set-object*/
		if ( bStandardDomainFibSet ){
			delete pDomainFibSet;
		}
		return false;
	}
	cDomainVectorBasis * pDomainFibSetVector = ((cDomainVectorBasis*)(
		pDomainFibSetVectorDom ));
	
	//get the domain for the variables in this vector
	cTypeVariable typeVariable;
	//return the variable domain
	cDomainIntegerBasis * pDomainVariable = (cDomainIntegerBasis*)
		validDomains.getDomainForElement( typeVariable );
	const bool bStandardDomainVariable = ( pDomainVariable == NULL );
	if ( bStandardDomainVariable ){
		//use the standard domain
		pDomainVariable = (cDomainIntegerBasis*)typeVariable.getStandardDomain();
	}
	
	for ( list<cVectorFibSet>::const_iterator itrFibSet = liFibSets.begin();
			itrFibSet != liFibSets.end(); itrFibSet++ ){
		
		const bool bVectorStored = itrFibSet->store( stream, cRestBits,
			uiRestBitPosition, *pDomainFibSetVector, *pDomainVariable );
		if ( ! bVectorStored ){
			if ( bStandardDomainFibSet ){
				delete pDomainFibSet;
			}
			if ( bStandardDomainVariable ){
				delete pDomainVariable;
			}
			return false;
		}
	}//end for store vectors with values to set
	
	if ( bStandardDomainFibSet ){
		delete pDomainFibSet;
	}
	if ( bStandardDomainVariable ){
		delete pDomainVariable;
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
unsignedIntFib cFibSet::enumerateVariablesForStoring(
		unsignedIntFib uiLastVariableNumber ){
	
	for ( vector<cFibVariable*>::iterator
			itrDefVariable = vecVariablesDefined.begin();
			itrDefVariable != vecVariablesDefined.end(); itrDefVariable++ ){
		
		uiLastVariableNumber++;
		(*itrDefVariable)->setIntegerValue( uiLastVariableNumber );
	}
	
	return cFibLimb::enumerateVariablesForStoring( uiLastVariableNumber );
}


/**
 * This method copies the connected object with the given number in the
 * order of connected objects.
 * For this every Fib element, beginning from this Fib element, that
 * is part of the connected object will be copied.
 * Variables which are not defined in the connected object but used
 * don't change ther reference.
 * It is an help method for the copy method. It dosn't update the
 * structural information of the created Fib object.
 *
 * @param iObjectPoint the number of the connected object to copy;
 * 	the standart value is 0 for coping the complet actual object
 * @return the copy of the connected object or NULL if non such exists
 */
cFibElement *cFibSet::copyInternal( const unsignedIntFib iObjectPoint ) const{

	cFibSet * pFibSet = NULL;

	if ( pUnderObject ){
		pFibSet = new cFibSet( *this );
		//copy the subobject
		cFibElement * pCopyUnderobject = pUnderObject->copyInternal( iObjectPoint );
		if ( pCopyUnderobject == NULL ){
			//no such objectpoint
			delete pFibSet;
			return NULL;
		}
		vector<cFibVariable*>::iterator itrDefVarOther =
			pFibSet->vecVariablesDefined.begin();
		for ( vector<cFibVariable*>::const_iterator
				itrDefVar = vecVariablesDefined.begin();
				itrDefVar != vecVariablesDefined.end();
				itrDefVar++, itrDefVarOther++ ){
			
			pCopyUnderobject->replaceVariable(
				const_cast<cFibVariable*>(*itrDefVar), (*itrDefVarOther) );
		}//end for check if the variables are defined on the same position
		
		pFibSet->pUnderObject = pCopyUnderobject;
		if ( pFibSet->pUnderObject ){
			pFibSet->pUnderObject->pSuperiorElement = pFibSet;
		}
	}else{//no subobject
		if ( iObjectPoint == 0 ){
			//just copy if this is the correct objectpoint
			pFibSet = new cFibSet( *this );
		}
	}
	return pFibSet;
}












