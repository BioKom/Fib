/**
 * @class cArea
 * file name: cArea.cpp
 * @author Betti Oesterholz
 * @date 14.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the Fib area element.
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
 * This class represents the area element of the Fib -multimedialanguage.
 * An area element contains a list with subareas which build the area.
 * It defines a variable which runs over the values of the areas.
 * The variable takes all integervalues in the subareas of the area.
 *
 */
/*
History:
14.02.2010  Oesterholz  created
18.04.2010  Oesterholz  evalueObject() methods changed: not a function but
	an object is given to evalue the data
05.08.2011  Oesterholz  FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES implemented
07.08.2011  Oesterholz  isDefinedVariable() and getDefinedVariables() with
	pCallingFibElement
25.08.2011  Oesterholz  underarea to subarea
17.10.2011  Oesterholz  FEATURE_OUTPUT_ELEMENT_NUMBER_XML implemented
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
10.11.2011  Oesterholz  Bugfix: every subobject evalueObject() call needs
	its own property vector list
02.01.2012  Oesterholz  cTypeSubarea to cTypeArea
06.01.2012  Oesterholz  DEBUG_RESTORE_XML: debugging information added for
	restore from Xml
*/


#include "cArea.h"

#include "cTypeArea.h"
#include "cTypeVariable.h"
#include "cDomainNaturalNumberBit.h"

#include <algorithm>


using namespace fib;

#ifdef FEATURE_SIMPLE_CONSTRUCTOR

/**
 * parameterconstructor
 *
 * @param inVectorArea the areavector this area should have
 * @param pInUnderobject the Fib Element which is the underobejct of
 * 	this Fib element (it also stands next in the order of Fib elements)
 * @param pInSuperiorElement the Fib Element in which this
 * 	area -element is an underobject
 */
cArea::cArea( const cVectorArea & inVectorArea,
		cFibElement * pInUnderobject,
		cFibElement * pInSuperiorElement ):
		cFibLimb( pInUnderobject, pInSuperiorElement ),
		variableDefined( this ){
	
	if ( pInSuperiorElement ){
		pInSuperiorElement->insertObjectInElement( this );
	}else{
		updateAllValues();
	}
	liSubAreas.push_back( inVectorArea );
	if ( pInSuperiorElement ){
		liSubAreas.back().setDefiningFibElement( this );
	}else{
		liSubAreas.back().setDefiningFibElement( this, false );
	}
	
}

#else //FEATURE_SIMPLE_CONSTRUCTOR

/**
 * parameterconstructor
 *
 * @param inVectorArea the areavector this area should have
 * @param pInSuperiorElement the Fib Element in which this
 * 	area -element is an underobject
 * @param pInPreviousFibElement the Fib Element which stands in th order
 * 	of Fib -elements befor this Fib -element
 * @param pInUnderobject the Fib Element which is the underobejct of
 * 	this Fib element (it also stands next in the order of Fib elements)
 */
cArea::cArea( const cVectorArea & inVectorArea,
		cFibElement * pInSuperiorElement,
		cFibElement * pInPreviousFibElement,
		cFibElement * pInUnderobject ):
		cFibLimb( pInSuperiorElement, pInPreviousFibElement, pInUnderobject ),
		variableDefined( this ){
	
	liSubAreas.push_back( inVectorArea );
	
	if ( pInSuperiorElement ){
		liSubAreas.back().setDefiningFibElement( this );
	}else{
		liSubAreas.back().setDefiningFibElement( this, false );
	}
	
	updateAllValues();
}

#endif //FEATURE_SIMPLE_CONSTRUCTOR


/**
 * copyconstructor
 * This copyconstructor constructs a copy of the given area element.
 * It dosn't copy other area -elements than the given, even if ther are
 * in the area -element.
 *
 * @param areaElement the area -element to copy
 */
cArea::cArea( const cArea &areaElement ):
		cFibLimb( areaElement ),
		liSubAreas( areaElement.liSubAreas ), variableDefined( this ){
	
	for ( list<cVectorArea>::iterator itrSubArea = liSubAreas.begin();
			 itrSubArea != liSubAreas.end(); itrSubArea++ ){
		itrSubArea->setDefiningFibElement( this, false );
	}
}


/**
 * The constructor for restoring a area element from an TinyXml element.
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
cArea::cArea( const TiXmlElement * pXmlElement, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables ): variableDefined( this ){
	
	if ( pXmlElement == NULL ){
		//noting to restore
		outStatus = -1;
		return;
	}
#ifdef DEBUG_RESTORE_XML
	printf( "cArea::restoreXml() started\n" );
#endif //DEBUG_RESTORE_XML
	string szElementType( pXmlElement->Value() );
	if ( szElementType != "area" ){
		//wrong element type to restore
#ifdef DEBUG_RESTORE_XML
		printf( "cArea::restoreXml() done: wrong element type to restore\n" );
#endif //DEBUG_RESTORE_XML
		outStatus = -2;
		return;
	}

	//read the variable number
	const char * szDefinedVariableNumber = pXmlElement->Attribute( "define_variable" );
	
	if ( szDefinedVariableNumber == NULL ){
#ifdef DEBUG_RESTORE_XML
		printf( "cArea::restoreXml(): no defined variable\n" );
#endif //DEBUG_RESTORE_XML
		outStatus = 2;
	}else{
		variableDefined.setIntegerValue( atol( szDefinedVariableNumber ) );
	}
	liDefinedVariables.push_front( &variableDefined );
	
	bool bVectorAreaRestored = false;
	for ( const TiXmlNode * pChild = pXmlElement->FirstChild();
			pChild != NULL; pChild = pChild->NextSibling() ) {
		
		int iType = pChild->Type();
		
		switch ( iType ){
			case TiXmlNode::ELEMENT:{
				/*check if this is a valid Fib element xml -element, create
				the apropirate Fib element and call its restoreXml() method*/
				const TiXmlElement * pXmlElement = pChild->ToElement();
				if ( pXmlElement == NULL ){
					outStatus = 2;
					continue;
				}
				string szElementType( pXmlElement->Value() );
				
				if ( szElementType == "vector" ){
					//check the attribute of the vector
					const char * szVectorXmlType = pXmlElement->Attribute( "type" );
					
					if ( szVectorXmlType == NULL ){
						outStatus = 2;
#ifdef DEBUG_RESTORE_XML
						printf( "cArea::restoreXml(): subarea could not be restored\n" );
#endif //DEBUG_RESTORE_XML
						continue;
					}else if ( ( string( "subarea" ) != szVectorXmlType ) &&
							string( "underarea" ) != szVectorXmlType ){//"underarea" is depricated
						outStatus = 2;
#ifdef DEBUG_RESTORE_XML
						printf( "cArea::restoreXml(): no subarea element, but %s\n", szVectorXmlType );
#endif //DEBUG_RESTORE_XML
						continue;
					}
					//restore the areavector
					liSubAreas.push_back( cVectorArea( pXmlElement, outStatus,
						liDefinedVariables ) );
					liSubAreas.back().setDefiningFibElement( this, false );
					bVectorAreaRestored = true;
					if ( outStatus < 0 ){
						return;
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
#ifdef DEBUG_RESTORE_XML
						printf( "cArea::restoreXml(): to many subobjects -> no correct area element\n" );
#endif //DEBUG_RESTORE_XML
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
				//invalid area element
				if ( outStatus ){
					outStatus = 2;
				}
				continue;
		}
	}
	if ( ! bVectorAreaRestored ){
		outStatus = 2;
		liSubAreas.push_back( cVectorArea( this ) );
	}
	if ( pUnderObject == NULL ){
		outStatus = -2;
#ifdef DEBUG_RESTORE_XML
		printf( "cArea::restoreXml(): no subobject -> no correct area element\n" );
#endif //DEBUG_RESTORE_XML
		return;
	}
}


/**
 * This constructor restores a area element from the stream where it is
 * stored in the compressed Fib format.
 * This constructor is for internal use only.
 *
 * @param iBitStream the stream wher the area element is stored to in,
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
 * @param pNextRoot the next higher root -element for the to restore
 * 	Fib elements, or the last restored root -element
 */
cArea::cArea( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains,
		cRoot * pNextRoot ):
		variableDefined( this ){
	
	if ( ! iBitStream.getStream()->good() ){
		outStatus = -1;
		return;
	}
	//get the domain for the variables in this vector
	cTypeVariable typeVariable;
	//return the variable domain
	cDomainIntegerBasis * pDomainVariable = (cDomainIntegerBasis*)
		validDomains.getDomainForElement( typeVariable );
	const bool bStandardDomainVariable = ( pDomainVariable == NULL );
	if ( bStandardDomainVariable ){
		//use the standrad domain
		pDomainVariable = (cDomainIntegerBasis*)typeVariable.getStandardDomain();
	}
	//set value for the defined variables
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

	//restore the vectors for the subarea
	cTypeArea typeSubarea;
	cDomain * pDomainAreaBasis = validDomains.getDomainForElement( typeSubarea );
	const bool bStandardDomainArea = ( pDomainAreaBasis == NULL );
	if ( bStandardDomainArea ){
		pDomainAreaBasis = typeSubarea.getStandardDomain();
	}
	if ( ! pDomainAreaBasis->isVector() ){
		//error in domain not a vector domain -> can't load area object
		if ( bStandardDomainArea ){
			delete pDomainAreaBasis;
		}
		outStatus = -2;
		return;
	}
	cDomainVectorBasis * pDomainArea = (cDomainVectorBasis*)pDomainAreaBasis;
	if ( pDomainArea->getNumberOfElements() < 2 ){
		/*error in domain (domain for number of subareas / vectors and / or
		 subareas/ vectors missing) -> can't load area object*/
		if ( bStandardDomainArea ){
			delete pDomainAreaBasis;
		}
		outStatus = -2;
		return;
	}
	const cDomainIntegerBasis * pDomainNumberOfSubareas = ((cDomainIntegerBasis*)(
		pDomainArea->getElementDomain( 1 ) ));
	if ( pDomainNumberOfSubareas == NULL ){
		/*error in domain (domain for number of subareas / vectors missing)
		-> can't load matrix object*/
		if ( bStandardDomainArea ){
			delete pDomainAreaBasis;
		}
		outStatus = -2;
		return;
	}
	//evalue count of subareas
	unsignedLongFib ulNumberOfSubareas = pDomainNumberOfSubareas->
		restoreIntegerValue( iBitStream, outStatus );
	if ( outStatus < 0 ){
		return;
	}
	const cDomain * pDomainSubareas = pDomainArea->getElementDomain( 2 );
	if ( pDomainSubareas == NULL  ){
		/*error in domain (domain subareas / vectors missing)
		-> can't load matrix object*/
		if ( bStandardDomainArea ){
			delete pDomainAreaBasis;
		}
		outStatus = -2;
		return;
	}
	cDomainVectorBasis * pVecDomainSubareas =
		(cDomainVectorBasis*)pDomainSubareas;
	if ( pVecDomainSubareas->getNumberOfElements() < 2 ){
		/*error in domain (domain subareas / vectors wrong)
		-> can't load matrix object*/
		if ( bStandardDomainArea ){
			delete pDomainAreaBasis;
		}
		outStatus = -2;
		return;
	}
	
	for ( unsignedLongFib uiActualSubarea = 1;
			uiActualSubarea <= ulNumberOfSubareas; uiActualSubarea++ ){
		
		liSubAreas.push_back( cVectorArea( iBitStream, outStatus,
			liDefinedVariables, pVecDomainSubareas, pDomainVariable ) );
		
		liSubAreas.back().setDefiningFibElement( this, false );
		if ( outStatus < 0 ){
			break;
		}
	}
	if ( bStandardDomainArea ){
		delete pDomainArea;
	}
	if ( bStandardDomainVariable ){
		delete pDomainVariable;
	}
	if ( outStatus < 0 ){
		return;
	}

	//restore the underobject
	pUnderObject = cFibElement::restoreInternal( iBitStream, outStatus,
		liDefinedVariables, validDomains, pNextRoot );
#ifdef FEATURE_FAST_UPDATE
	if ( pUnderObject ){
		pUnderObject->pSuperiorElement = this;
	}
#endif //FEATURE_FAST_UPDATE
}



/**
 * @see getTypeName
 * @return a character for the typ of the Fib -element
 * Types are:
 *		- u: element of unknown typ
 *		- p: point
 * 	- l: list-element
 *		- y: property
 *		- c: comment
 *		- a: area
 *		- f: function
 *		- i: if-condition
 *		- o: extern object element
 *		- s: extern subobject element
 *		- v: set-element
 *		- m: matrix element
 *		- r: root-element
 */
char cArea::getType() const{
	return 'a';
}


/**
 * This method evaluades the Fib object.
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
bool cArea::evalueObject( iEvaluePosition & evaluePosition,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties ) const{
	
	if ( pUnderObject == NULL ){
		//nothing to evalue
		return false;
	}
	//evalue the underobject for all values in the subareas
	for ( list<cVectorArea>::const_iterator itrSubArea = liSubAreas.begin();
			 itrSubArea != liSubAreas.end(); itrSubArea++ ){
#ifdef FEATURE_DIRECT_UNDERAREAVALUES
		const longFib lLowerBound = itrSubArea->getLowerBound();
		const longFib lUpperBound = itrSubArea->getUpperBound();
		
#ifdef DEBUG_EVALUE
		const long liLowerBound = lLowerBound;
		const long liUpperBound = lUpperBound;
		printf( "cArea::evalueObject() going from %li to %li\n", liLowerBound, liUpperBound );
#endif //DEBUG_EVALUE

		if ( lLowerBound < lUpperBound ){
			//go in increasing order
			for ( longFib lActualValue = lLowerBound; lActualValue <= lUpperBound;
					lActualValue++ ){
				//properties for the subobject
				list<cVectorProperty> liVecSubProperties = liVecProperties;
				
				const_cast<cArea*>(this)->variableDefined.setIntegerValue( lActualValue );
				const bool bUnderObjectEvalued = pUnderObject->evalueObject(
					evaluePosition, objectPoint, liVecSubProperties );
				if ( ! bUnderObjectEvalued ){
					//stop evaluing
					return false;
				}
			}
		}else{//go in decreasing order
			for ( longFib lActualValue = lLowerBound; lActualValue >= lUpperBound;
					lActualValue-- ){
				//properties for the subobject
				list<cVectorProperty> liVecSubProperties = liVecProperties;
				
				const_cast<cArea*>(this)->variableDefined.setIntegerValue( lActualValue );
				const bool bUnderObjectEvalued = pUnderObject->evalueObject(
					evaluePosition, objectPoint, liVecSubProperties );
				if ( ! bUnderObjectEvalued ){
					//stop evaluing
					return false;
				}
			}
		}
#else
		const list<longFib> liVariableValues = itrSubArea->getAreaValues();
		
#ifdef DEBUG_EVALUE
		printf( "cArea::evalueObject() setting values: " );
		for ( list<longFib>::const_iterator itrValue = liVariableValues.begin();
				itrValue != liVariableValues.end(); itrValue++ ){
			
			const long lActualValue = (*itrValue);
			printf( "%li, ", lActualValue );
		}
		printf( "\n");
#endif //DEBUG_EVALUE
		
		for ( list<longFib>::const_iterator itrValue = liVariableValues.begin();
				itrValue != liVariableValues.end(); itrValue++ ){
			//properties for the subobject
			list<cVectorProperty> liVecSubProperties = liVecProperties;
			
			const_cast<cArea*>(this)->variableDefined.setIntegerValue( *itrValue );
			const bool bUnderObjectEvalued = pUnderObject->evalueObject(
				evaluePosition, objectPoint, liVecSubProperties );
			if ( ! bUnderObjectEvalued ){
				//stop evaluing
				return false;
			}
		}
#endif
	}
	return true;
}


/**
 * This method evaluades the Fib object.
 * Evertime a Fib elements, with a type of the given type chars in
 * liCFibElementTyps, is reached while evaluation, it is given
 * back with the properties which it has.
 * Ever pointelement is given back. The type chars for pointelements
 * don't need to be in the list liCFibElementTyps.
 *
 * @param evalueFibElement a reference to the object with the
 * 	evalueElement() method to evalue /store the Fib elements and ther
 * 	properties; everytime a Fib element (with one of the type given
 * 	in liCFibElementTyps) is reached in the evaluation, the method
 * 	evalueElement() of this objects is called with the Fib element
 * 	and the properties of the Fib element; @see iEvalueFibElement
 * @param objectPoint the object point in the order of true partobjects
 * 	to evalue
 * @param liVecProperties a list with the property vectors which should
 * 	be global for the evalued object
 * @param liCFibElementTyps a list with the type chars (@see getType)
 * 	of the Fib elements to return
 * @return if the evalueation was successfull true, else false
 */
bool cArea::evalueObject( iEvalueFibElement & evalueFibElement,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties,
		const list<char> & liCFibElementTyps ){
	
	//check if this Fib element should be given back with evalueElement()
	for ( list<char>::const_iterator itrCType = liCFibElementTyps.begin();
			itrCType != liCFibElementTyps.end(); itrCType++ ){
		
		if ( *itrCType == getType() ){
			//call evalueElement() with this element
			return evalueFibElement.evalueElement( *this, liVecProperties );
		}
	}//else if this element shouldn't be returned -> evalue the main -Fib object

	if ( pUnderObject == NULL ){
		//nothing to evalue
		return false;
	}
	//evalue the underobject for all values in the subareas
	for ( list<cVectorArea>::const_iterator itrSubArea = liSubAreas.begin();
			 itrSubArea != liSubAreas.end(); itrSubArea++ ){
		
#ifdef FEATURE_DIRECT_UNDERAREAVALUES
		longFib lLowerBound = itrSubArea->getLowerBound();
		longFib lUpperBound = itrSubArea->getUpperBound();
		
#ifdef DEBUG_EVALUE
		const long liLowerBound = lLowerBound;
		const long liUpperBound = lUpperBound;
		printf( "cArea::evalueObject() going from %li to %li\n", liLowerBound, liUpperBound );
#endif //DEBUG_EVALUE
		
		if ( lLowerBound < lUpperBound ){
			//go in increasing order
			for ( longFib lActualValue = lLowerBound; lActualValue <= lUpperBound;
					lActualValue++ ){
				//properties for the subobject
				list<cVectorProperty> liVecSubProperties = liVecProperties;
				
				const_cast<cArea*>(this)->variableDefined.setIntegerValue( lActualValue );
				const bool bUnderObjectEvalued = pUnderObject->evalueObject(
					evalueFibElement, objectPoint, liVecSubProperties, liCFibElementTyps );
				if ( ! bUnderObjectEvalued ){
					//stop evaluing
					return false;
				}
			}
		}else{//go in decreasing order
			for ( longFib lActualValue = lLowerBound; lActualValue >= lUpperBound;
					lActualValue-- ){
				//properties for the subobject
				list<cVectorProperty> liVecSubProperties = liVecProperties;
				
				const_cast<cArea*>(this)->variableDefined.setIntegerValue( lActualValue );
				const bool bUnderObjectEvalued = pUnderObject->evalueObject(
					evalueFibElement, objectPoint, liVecSubProperties, liCFibElementTyps );
				if ( ! bUnderObjectEvalued ){
					//stop evaluing
					return false;
				}
			}
		}
#else
		const list<longFib> liVariableValues = itrSubArea->getAreaValues();
		
#ifdef DEBUG_EVALUE
		printf( "cArea::evalueObject() setting values: " );
		for ( list<longFib>::const_iterator itrValue = liVariableValues.begin();
				itrValue != liVariableValues.end(); itrValue++ ){
			
			const long lActualValue = (*itrValue);
			printf( "%li, ", lActualValue );
		}
		printf( "\n");
#endif //DEBUG_EVALUE
		
		for ( list<longFib>::const_iterator itrValue = liVariableValues.begin();
				itrValue != liVariableValues.end(); itrValue++ ){
			//properties for the subobject
			list<cVectorProperty> liVecSubProperties = liVecProperties;
			
			const_cast<cArea*>(this)->variableDefined.setIntegerValue( *itrValue );
			const bool bUnderObjectEvalued = pUnderObject->evalueObject(
				evalueFibElement, objectPoint, liVecSubProperties, liCFibElementTyps );
			if ( ! bUnderObjectEvalued ){
				//stop evaluing
				return false;
			}
		}
#endif
	}
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
 * @param lMaxTime the maximum time for the evaluation, the returned
 * 	exceed this value; the value 0 stands for infinity, so the 
 * 	evaluation won't be stoped
 * @return a value for the time needed to evalue the object
 */
unsignedLongFib cArea::getTimeNeed( unsignedLongFib lMaxTime ) const{
	
	if ( lMaxTime == 1 ){
		return lMaxTime;
	}

	unsignedLongFib ulTimeNeeded = 1;
	if ( pUnderObject == NULL ){
		return ulTimeNeeded;
	}

	//evalue the underobject for all values in the subareas
	for ( list<cVectorArea>::const_iterator itrSubArea = liSubAreas.begin();
			 itrSubArea != liSubAreas.end(); itrSubArea++ ){
		
#ifdef FEATURE_DIRECT_UNDERAREAVALUES
		longFib lLowerBound = itrSubArea->getLowerBound();
		longFib lUpperBound = itrSubArea->getUpperBound();
		
		if ( lLowerBound < lUpperBound ){
			//go in increasing order
			for ( longFib lActualValue = lLowerBound; lActualValue <= lUpperBound;
					lActualValue++ ){
				
				const_cast<cArea*>(this)->variableDefined.setIntegerValue( lActualValue );
				if ( lMaxTime == 0 ){
					ulTimeNeeded += pUnderObject->getTimeNeed( 0 );
				}else{
					ulTimeNeeded += pUnderObject->getTimeNeed( lMaxTime - ulTimeNeeded );
					if ( lMaxTime <= ulTimeNeeded ){
						return lMaxTime;
					}
				}
			}
		}else{//go in decreasing order
			for ( longFib lActualValue = lLowerBound; lActualValue >= lUpperBound;
					lActualValue-- ){
				
				const_cast<cArea*>(this)->variableDefined.setIntegerValue( lActualValue );
				if ( lMaxTime == 0 ){
					ulTimeNeeded += pUnderObject->getTimeNeed( 0 );
				}else{
					ulTimeNeeded += pUnderObject->getTimeNeed( lMaxTime - ulTimeNeeded );
					if ( lMaxTime <= ulTimeNeeded ){
						return lMaxTime;
					}
				}
			}
		}
#else
		const list<longFib> liVariableValues = itrSubArea->getAreaValues();
		
		for ( list<longFib>::const_iterator itrValue = liVariableValues.begin();
				itrValue != liVariableValues.end(); itrValue++ ){
			
			const_cast<cArea*>(this)->variableDefined.setIntegerValue( *itrValue );
			if ( lMaxTime == 0 ){
				ulTimeNeeded += pUnderObject->getTimeNeed( 0 );
			}else{
				ulTimeNeeded += pUnderObject->getTimeNeed( lMaxTime - ulTimeNeeded );
				if ( lMaxTime <= ulTimeNeeded ){
					return lMaxTime;
				}
			}
		}
#endif
	}
	return ulTimeNeeded;
}


/**
 * This method evaluades the size of the Fib object in bits in the
 * compressed file form.
 * The optionalpart field of area -elements will be ignored.
 *
 * @see store()
 * @return the size of the Fib object in bits in the compressed form
 */
unsignedLongFib cArea::getCompressedSize() const{
	
	unsignedLongFib ulCompressedSize = 4;//bits for the initiator
	const cDomains validDomains = getValidValueDomains();
	
	cTypeArea typeSubarea;
	cDomain * pDomainAreaBasis = validDomains.getDomainForElement( typeSubarea );
	const bool bStandardDomainArea = ( pDomainAreaBasis == NULL );
	if ( bStandardDomainArea ){
		pDomainAreaBasis = typeSubarea.getStandardDomain();
	}
	if ( ! pDomainAreaBasis->isVector() ){
		//error in domain not a vector domain -> can't store area object
		if ( bStandardDomainArea ){
			delete pDomainAreaBasis;
		}
		return 0;
	}
	cDomainVectorBasis * pDomainArea = (cDomainVectorBasis*)pDomainAreaBasis;
	if ( pDomainArea->getNumberOfElements() < 2 ){
		/*error in domain (domain for number of subareas / vectors and / or
		 subareas/ vectors missing) -> can't store area object*/
		if ( bStandardDomainArea ){
			delete pDomainAreaBasis;
		}
		return 0;
	}
	const cDomainIntegerBasis * pDomainNumberOfSubareas = ((cDomainIntegerBasis*)(
		pDomainArea->getElementDomain( 1 ) ));
	//add size of subarea count
	if ( pDomainNumberOfSubareas != NULL ){
		//add bits for defined variables count
		ulCompressedSize += pDomainNumberOfSubareas->getCompressedSizeForValue();
	}
	
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

	//add bits for the subareas
	if ( ! liSubAreas.empty() ){
		//evalue domains for the subareas /vectors
		const cDomain * pDomainSubareas = pDomainArea->getElementDomain( 2 );
		if ( pDomainSubareas == NULL  ){
			/*error in domain (domain subareas / vectors missing)
			-> can't store matrix object*/
			if ( bStandardDomainArea ){
				delete pDomainAreaBasis;
			}
			return 0;
		}
		cDomainVectorBasis * pVecDomainSubareas =
			(cDomainVectorBasis*)pDomainSubareas;
		if ( pVecDomainSubareas->getNumberOfElements() < 2 ){
			/*error in domain (domain subareas / vectors wrong)
			-> can't store matrix object*/
			if ( bStandardDomainArea ){
				delete pDomainAreaBasis;
			}
			return 0;
		}
		//get the domain for the variables in this vector
		cDomainSingle * pVariableDomain =
			liSubAreas.front().getVariableDomain();
		if ( pVariableDomain == NULL ){
			//Error: no variable domain
			return 0;
		}
		//add compressed size for the Vectorelements
		for ( list<cVectorArea>::const_iterator itrSubArea = liSubAreas.begin();
				itrSubArea != liSubAreas.end(); itrSubArea++ ){
			
			ulCompressedSize += itrSubArea->getCompressedSize(
				*pVecDomainSubareas, *pVariableDomain );
		}
		//delete variable domain
		delete pVariableDomain;
	}
	if ( bStandardDomainArea ){
		delete pDomainAreaBasis;
	}
	//add compressed size for the subobject
	if ( pUnderObject != NULL ){
		ulCompressedSize += pUnderObject->getCompressedSize();
	}
	return ulCompressedSize;
}


/**
 * This method checks if the given variable is used in the given
 * direction from this Fib -element.
 *
 * @see cFibVariable
 * @see isDefinedVariable()
 * @param variable the variable to check if it is used
 * @param direction the direction from this Fib -element, in which the
 * 	variable should be used; standardvalue is ED_POSITION so yust
 * 	this Fib -element will be checked
 * @return true if the variable is used, else false
 */
bool cArea::isUsedVariable( const cFibVariable *variable ,
		edDirection direction ) const{
	
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		//check subareas
		for ( list<cVectorArea>::const_iterator itrSubArea = liSubAreas.begin();
				itrSubArea != liSubAreas.end(); itrSubArea++ ){
		
			const bool bVariableUsed = itrSubArea->isUsedVariable( variable );
			if ( bVariableUsed ){
				return true;
			}
		}
	}
	return cFibLimb::isUsedVariable( variable, direction );
}


/**
 * This method returns all variables used in the given direction from
 * this Fib -element.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @see isDefinedVariable()
 * @param direction the direction from this Fib -element, in which the
 * 	variable should be used; standardvalue is ED_POSITION so yust
 * 	this Fib -element will be checked
 * @return the set with all variables used in the given direction from
 * 	this Fib -element
 */
set<cFibVariable*> cArea::getUsedVariables( edDirection direction ){
	
	set<cFibVariable*> setUsedVariables;
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		//check subareas
		for ( list<cVectorArea>::iterator itrSubArea = liSubAreas.begin();
				itrSubArea != liSubAreas.end(); itrSubArea++ ){
			
			set<cFibVariable*> setUsedVarSubarea =
				itrSubArea->getUsedVariables();
			
			setUsedVariables.insert( setUsedVarSubarea.begin(),
				setUsedVarSubarea.end() );
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
bool cArea::isDefinedVariableInternal( const cFibVariable *variable,
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
list<cFibVariable*> cArea::getDefinedVariablesInternal(
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
		
		//insert the defined variables this area element defines
		liDefinedVariables.push_front( &variableDefined );
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
bool cArea::replaceVariable( cFibVariable *variableOld,
		cFibVariable *variableNew ){
	
	if ( (variableOld == NULL) || (variableNew == NULL) ){
		//can't replace
		return false;
	}
	for ( list<cVectorArea>::iterator itrSubArea = liSubAreas.begin();
			itrSubArea != liSubAreas.end(); itrSubArea++ ){
		
		//replace variable in areavector
		if ( ! itrSubArea->replaceVariable( variableOld, variableNew ) ){
			return false;
		}
	}
	return cFibLimb::replaceVariable( variableOld, variableNew );
}


/**
 * This method copies the Fib -element on the specified position.
 * Variables which are not defined in the Fib -element but used
 * don't change ther reference.
 *
 * @see getType()
 * @param cType the type of the Fib -element to copy
 * @param elementPoint the number of the Fib -element, in the order of
 * 	Fib -elements of the given type cType, to copy
 * @return the copy of the Fib -element
 */
cFibElement * cArea::copyElement( const char cType, const unsignedIntFib
		elementPoint, bool bAbsolute ) const{
	
	if ( elementPoint == 0 ){
		//copy this element
		return new cArea( *this );
	}//else get the Fib element and copy it
	
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
bool cArea::equalInternal( const cFibElement & fibObject,
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
bool cArea::equalElementInternal( const cFibElement & fibElement,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{

	if ( getType() != fibElement.getType() ){
		return false;
	}
	//compare subareas
	cArea * pAreaElement = (cArea*)(&fibElement);
	if ( getNumberOfSubareas() != pAreaElement->getNumberOfSubareas() ){
		return false;
	}
	list<cVectorArea>::const_iterator itrSubAreaOther =
		pAreaElement->liSubAreas.begin();
	for ( list<cVectorArea>::const_iterator itrSubArea = liSubAreas.begin();
			itrSubArea != liSubAreas.end(); itrSubArea++, itrSubAreaOther++ ){
		
		if ( ! itrSubArea->equalInternal( *itrSubAreaOther,
				mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
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
bool cArea::equalValuesSetInternal( const cFibVariable * variableOwn,
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
	const bool bEqualElement = equalElementInternal(
		fibElement, mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects );
	if ( bEqualElement ){
		
		mapEqualDefinedVariables.insert( make_pair( this, &fibElement ) );
		return true;
	}
	return false;
}


#else //FEATURE_EQUAL_FIB_OBJECT


/**
 * This method checks if the given Fib object is equal to this Fib
 * -object.
 * Variables can be others, but must be defined and used in equivalent
 * Fib -elements.
 *
 * @param fibObject the Fib object to which this Fib object should be
 * 	equal
 * @return true if this Fib object is equal to the given Fib object,
 * 	else false
 */
bool cArea::equal( const cFibElement & fibObject ) const{

	if ( ! cFibLimb::equal( fibObject ) ){
		return false;
	}
	return equalElement( fibObject );
}


/**
 * This method checks if the given Fib element is equal to this fib
 * -element.
 * The underobjects arn't compared, not even ther count is compared.
 * Used variables can be others.
 *
 * @param fibElement the Fib element to which this Fib element should be
 * 	equal
 * @return true if this Fib element is equal to the given Fib object,
 * 	else false
 */
bool cArea::equalElement( const cFibElement & fibElement ) const{

	if ( getType() != fibElement.getType() ){
		return false;
	}
	cArea * pAreaElement = (cArea*)(&fibElement);
	if ( getNumberOfSubareas() != pAreaElement->getNumberOfSubareas() ){
		return false;
	}
	if ( liSubAreas != pAreaElement->liSubAreas ){
		return false;
	}
	return true;
}

#endif //FEATURE_EQUAL_FIB_OBJECT



/**
 * This method stores this Fib object in the XML -format into the
 * given stream.
 *
 * @param stream the stream where this Fib object should be stored to
 * @return true if this Fib object is stored, else false
 */
bool cArea::storeXml( ostream &stream ) const{

	bool bReturnValue = true;
#ifdef FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	stream<<"<area elementNr=\""<<getNumberOfElement()<<"\" "<<
		"define_variable=\""<< variableDefined.getIntegerValue() <<"\">"<<endl;
#else //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	stream<<"<area define_variable=\""<< variableDefined.getIntegerValue() <<"\">"<<endl;
#endif //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	for ( list<cVectorArea>::const_iterator itrSubArea = liSubAreas.begin();
			itrSubArea != liSubAreas.end(); itrSubArea++ ){
		
		//store subareas
		if ( ! itrSubArea->storeXml( stream ) ){
			return false;
		}
	}
	if ( pUnderObject ){
		bReturnValue &= pUnderObject->storeXml( stream );
	}
	stream<<"</area>"<<endl;
	return bReturnValue;
}


/*
 * Area -element methods
 */


/**
 * @return the number of subareas this area element consists of
 */
unsignedIntFib cArea::getNumberOfSubareas() const{
	return liSubAreas.size();
}


/**
 * This method returns a pointer to the iSubarea'th subarea of this
 * area element.
 *
 * @param iSubarea the number of the subarea to return (counting begins with 1)
 * @return a pointer to the iSubarea'th subarea, or NULL if non such exists
 */
cVectorArea * cArea::getSubarea( unsignedIntFib iSubarea ){
	
	if ( iSubarea < 1){
		//no such subarea
		return NULL;
	}
	list<cVectorArea>::iterator itrSubArea = liSubAreas.begin();
	while ( 1 < iSubarea ){
		if ( itrSubArea == liSubAreas.end() ){
			//no such subarea
			return NULL;
		}
		itrSubArea++;
		iSubarea--;
	}
	if ( itrSubArea == liSubAreas.end() ){
		//no such subarea
		return NULL;
	}
	return &(*itrSubArea);
}


/**
 * This method adds the given subarea to the existing subareas.
 *
 * @param underArea a reference to the to add subarea
 * @param uiPosition the position wher the underArea should be added
 * 	(counting begins with 1); if 0 the underArea will be added to the
 * 	end of the subarea list
 * @return true if the underArea was added, else false
 */
bool cArea::addSubarea( const cVectorArea &underArea, unsignedIntFib uiPosition ){
	
	if ( (uiPosition == 0) || (liSubAreas.size() <= uiPosition) ){
		//add th the end of the subarealist
		liSubAreas.push_back( underArea );
		liSubAreas.back().setDefiningFibElement( this );
		return true;
	}//else find the position wher to insert
	list<cVectorArea>::iterator itrSubArea = liSubAreas.begin();
	while ( 1 < uiPosition ){
		itrSubArea++;
		uiPosition--;
	}
	itrSubArea = liSubAreas.insert( itrSubArea, underArea );
	itrSubArea->setDefiningFibElement( this );
	return true;
}


/**
 * This method deletes the uiSubareaPosition'th subarea from the
 * existing subareas.
 *
 * @param uiSubareaPosition the position wher the underArea should be
 * 	deleted (counting begins with 1)
 * @return true if the subarea was deleted, else false
 */
bool cArea::deleteSubarea( unsignedIntFib uiSubareaPosition ){
	
	if ( (uiSubareaPosition < 1) || (liSubAreas.size() < 2) ){
		//can't delete
		return false;
	}
	
	list<cVectorArea>::iterator itrSubArea = liSubAreas.begin();
	while ( 1 < uiSubareaPosition ){
		if ( itrSubArea == liSubAreas.end() ){
			//no such subarea
			return false;
		}
		itrSubArea++;
		uiSubareaPosition--;
	}
	if ( itrSubArea == liSubAreas.end() ){
		//no such subarea
		return false;
	}
	liSubAreas.erase( itrSubArea );
	return true;
}


/**
 * This method sorts the subareas.
 *
 * when sorted the subarealist will fullfill the following constrains:
 * 	- if the a suarea as two values as it's bounderies, the first
 * 	  value will be lower than the second
 * 	- every subareas which have overlaped will be combined to one new
 * 	  subarea
 * 	- the subarealist will be sorted in increasing order; subarea
 * 	  with lower bounderies will be on the front of the subarealist
 * While sorting bounderies which are given by variables will be ignored.
 *
 * @return true if the subareas are sorted, else false
 */
bool cArea::sort(){
	
	/*if the a suarea as two values as it's bounderies, the first
	value will be lower than the second*/
	for ( list<cVectorArea>::iterator itrSubArea = liSubAreas.begin();
			itrSubArea != liSubAreas.end(); itrSubArea++ ){
		
		if ( itrSubArea->isVariable( 1 ) || itrSubArea->isVariable( 2 ) ){
			//skip check
			continue;
		}
		if ( itrSubArea->getValue( 2 ) < itrSubArea->getValue( 1 ) ){
			//switch the values
			const doubleFib dTmp = itrSubArea->getValue( 2 );
			itrSubArea->setValue( 2, itrSubArea->getValue( 1 ) );
			itrSubArea->setValue( 1, dTmp );
		}
	}
	/*every subareas which have overlaped will be combined to one new subarea
	and the subarealist will be sorted in increasing order; subarea
	with lower bounderies will be on the front of the subarealist*/
	//use bubblesort
	bool bHasChaged = true;
	while ( bHasChaged && ( 1 < liSubAreas.size() ) ){
		bHasChaged = false;
		list<cVectorArea>::iterator itrSubAreaOld = liSubAreas.begin();
		list<cVectorArea>::iterator itrSubAreaActual = itrSubAreaOld;
		itrSubAreaActual++;
		
		for ( ;itrSubAreaActual != liSubAreas.end(); itrSubAreaActual++ ){
			if ( itrSubAreaActual->isVariable( 1 ) ){
				continue;
			}
			if ( ( ! itrSubAreaOld->isVariable( 1 ) ) && ( ! itrSubAreaOld->isVariable( 2 ) ) &&
					( ! itrSubAreaActual->isVariable( 1 ) ) && ( ! itrSubAreaActual->isVariable( 2 ) ) ){
				//combine vectors if they overlap
				if ( (itrSubAreaActual->getValue( 1 ) <= ( itrSubAreaOld->getValue( 2 ) + 1 ) )  &&
						(itrSubAreaOld->getValue( 1 ) <= itrSubAreaActual->getValue( 2 )) ){
					//the areas are connected -> combine them
					if ( itrSubAreaOld->getValue( 2 ) < itrSubAreaActual->getValue( 2 ) ){
						itrSubAreaOld->setValue( 2, itrSubAreaActual->getValue( 2 ) );
					}//else the new subarea is a part of the old
					
					itrSubAreaActual = liSubAreas.erase( itrSubAreaActual );
					bHasChaged = true;
					itrSubAreaOld = itrSubAreaActual;
					if ( itrSubAreaActual == liSubAreas.end() ){
						break;
					}
					continue;
				}
			}
			if ( ( ! itrSubAreaOld->isVariable( 2 ) ) && ( ! itrSubAreaActual->isVariable( 1 ) ) ){
				
				if ( itrSubAreaActual->getValue( 1 ) < itrSubAreaOld->getValue( 2 ) ){
					//swap the vectors
					cVectorArea vecAreaTmp( *itrSubAreaOld );
					itrSubAreaActual = liSubAreas.erase( itrSubAreaOld );
					itrSubAreaActual++;
					itrSubAreaActual = liSubAreas.insert( itrSubAreaActual, vecAreaTmp );
					itrSubAreaActual->setDefiningFibElement( this );
					itrSubAreaOld = itrSubAreaActual;
					bHasChaged = true;
				}
			}
			if ( ! itrSubAreaActual->isVariable( 2 ) ){
				itrSubAreaOld = itrSubAreaActual;
			}
		}
	}
	
	return true;
}


/**
 * @return a pointer to the variable this area element defines
 */
cFibVariable * cArea::getDefinedVariable(){
	return &variableDefined;
}


/**
 * This method stores this Fib object in the compressed Fib -format
 * into the given stream.
 * It is needed becouse the stream can yust store byts but the size of
 * Fib elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the Fib elements.
 * Beware: You need to call storeBit() of the root -elements with the
 * domain for the area or the area will not be readebel.
 *
 * @see store
 * @param stream the stream where this Fib object should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if this Fib object is stored, else false
 */
bool cArea::storeBit( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{

	if ( pUnderObject == NULL ){
		return false;
	}
	
	char cInitiation = 0x08;
	const bool bInitiationStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, &cInitiation, 4 );
	if ( ! bInitiationStored ){
		return false;
	}
	
	const cDomains validDomains = getValidValueDomains();
	//store the vectors for the subarea
	cTypeArea typeSubarea;
	cDomain * pDomainAreaBasis = validDomains.getDomainForElement( typeSubarea );
	const bool bStandardDomainArea = ( pDomainAreaBasis == NULL );
	if ( bStandardDomainArea ){
		pDomainAreaBasis = typeSubarea.getStandardDomain();
	}
	if ( ! pDomainAreaBasis->isVector() ){
		//error in domain not a vector domain -> can't store area object
		if ( bStandardDomainArea ){
			delete pDomainAreaBasis;
		}
		return false;
	}
	cDomainVectorBasis * pDomainArea = (cDomainVectorBasis*)pDomainAreaBasis;
	if ( pDomainArea->getNumberOfElements() < 2 ){
		/*error in domain (domain for number of subareas / vectors and / or
		 subareas/ vectors missing) -> can't store area object*/
		if ( bStandardDomainArea ){
			delete pDomainAreaBasis;
		}
		return false;
	}
	const cDomainIntegerBasis * pDomainNumberOfSubareas = ((cDomainIntegerBasis*)(
		pDomainArea->getElementDomain( 1 ) ));
	if ( pDomainNumberOfSubareas == NULL ){
		//no domain for the subarea count
		if ( bStandardDomainArea ){
			delete pDomainAreaBasis;
		}
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
	if ( ! bVariableStored ){
		return false;
	}
	if ( bStandardDomainUsed ){
		delete variableDomain;
	}
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	
	//store number of subareas
	const unsignedIntFib uiNumberOfSubareas = liSubAreas.size();
	const bool bNumberOfSubareasStored = pDomainNumberOfSubareas->storeUnscaledValue(
		uiNumberOfSubareas, stream, cRestBits, uiRestBitPosition );
	if ( ! bNumberOfSubareasStored ){
		//error: number of defined variables not stored
		if ( bStandardDomainArea ){
			delete pDomainAreaBasis;
		}
		return false;
	}
	//evalue domains for the vectors
	if ( ! liSubAreas.empty() ){
		
		const cDomain * pDomainSubareas = pDomainArea->getElementDomain( 2 );
		if ( pDomainSubareas == NULL  ){
			/*error in domain (domain subareas / vectors missing)
			-> can't store matrix object*/
			if ( bStandardDomainArea ){
				delete pDomainAreaBasis;
			}
			return false;
		}
		cDomainVectorBasis * pVecDomainSubareas =
			(cDomainVectorBasis*)pDomainSubareas;
		if ( pVecDomainSubareas->getNumberOfElements() < 2 ){
			/*error in domain (domain subareas / vectors wrong)
			-> can't store matrix object*/
			if ( bStandardDomainArea ){
				delete pDomainAreaBasis;
			}
			return false;
		}
		//get the domain for the variables in this vector
		cDomainSingle * pVariableDomain =
			liSubAreas.front().getVariableDomain();
		if ( pVariableDomain == NULL ){
			//Error: no variable domain
			return false;
		}
		//store the subareas
		for ( list<cVectorArea>::const_iterator itrSubArea = liSubAreas.begin();
				itrSubArea != liSubAreas.end(); itrSubArea++ ){
			
			const bool bVectorStored = itrSubArea->store( stream, cRestBits,
				uiRestBitPosition, *pVecDomainSubareas, *pVariableDomain );
			if ( ! bVectorStored ){
				return false;
			}
		}
		//delete variable domain
		delete pVariableDomain;
	}
	if ( bStandardDomainArea ){
		delete pDomainAreaBasis;
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
unsignedIntFib cArea::enumerateVariablesForStoring(
		unsignedIntFib uiLastVariableNumber ){
	
	uiLastVariableNumber++;
	variableDefined.setIntegerValue( uiLastVariableNumber );
	
	return cFibLimb::enumerateVariablesForStoring( uiLastVariableNumber );
}


/**
 * This method copies the connected object with the given number in the
 * order of connected objects.
 * For this every Fib -element, beginning from this Fib -element, that
 * is part of the connected object will be copied.
 * Variables which are not defined in the connected object but used
 * don't change ther reference.
 * It is an helpmethod for the copy method. It dosn't update the
 * structural information of the created Fib object.
 *
 * @param iObjectPoint the number of the connected object to copy;
 * 	the standartvalue is 0 for coping the complet actual object
 * @return the copy of the connected object or NULL if non such exists
 */
cFibElement *cArea::copyInternal( const unsignedIntFib iObjectPoint ) const{

	cArea * pArea = NULL;

	if ( pUnderObject ){
		pArea = new cArea( *this );
		//copy the underobject
		cFibElement * pCopyUnderobject = pUnderObject->copyInternal( iObjectPoint );
		if ( pCopyUnderobject == NULL ){
			//no such objectpoint
			delete pArea;
			return NULL;
		}
		pCopyUnderobject->replaceVariable(
			const_cast<cFibVariable*>(&variableDefined), &(pArea->variableDefined));
		pArea->pUnderObject = pCopyUnderobject;
#ifdef FEATURE_FAST_UPDATE
		if ( pArea->pUnderObject ){
			pArea->pUnderObject->pSuperiorElement = pArea;
		}
#endif //FEATURE_FAST_UPDATE
	}else{//no underobject
		if ( iObjectPoint == 0 ){
			//just copy if this is the correct objectpoint
			pArea = new cArea( *this );
		}
	}
	return pArea;
}












