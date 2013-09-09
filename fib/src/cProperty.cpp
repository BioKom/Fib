/**
 * @class cProperty
 * file name: cProperty.h
 * @author Betti Oesterholz
 * @date 26.11.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the property -Fib -element.
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
 * This class represents the propertyelement of the Fib -multimedialanguage.
 * It represents a property for a fib -object.
 *
 */
/*
History:
08.12.2009  Oesterholz  created
18.04.2010  Oesterholz  evalueObject() methods changed: not a function but
	an object is given to evalue the data
17.12.2010  Oesterholz  FEATURE_CHECK_OVERWRITTEN_WITH_IS_OVERWRITTEN_VECTOR added
08.03.2011  Oesterholz  method for const getProperty() added
17.10.2011  Oesterholz  FEATURE_OUTPUT_ELEMENT_NUMBER_XML implemented
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
10.11.2011  Oesterholz  FEATURE_EVALUE_ALL_PROPERTIES_IN_C_PROPERTY implemented
30.07.2013  Oesterholz  method assignValues() added
*/


#include "cProperty.h"

#include "cTypeProperty.h"
#include "cTypeVariable.h"


using namespace fib;


#ifdef FEATURE_SIMPLE_CONSTRUCTOR

/**
 * parameterconstructor
 *
 * @param inVectorProperty the propertyvector this property should have
 * @param pInUnderobject the fib -Element which is the underobejct of
 * 	this fib -element (it also stands next in the order of fib -elements)
 * @param pInSuperiorElement the fib -Element in which this
 * 	property -element is an underobject
 */
cProperty::cProperty( const cVectorProperty & inVectorProperty,
		cFibElement * pInUnderobject, cFibElement * pInSuperiorElement ):
		cFibLimb( pInUnderobject, pInSuperiorElement ),
		vectorProperty( inVectorProperty ){
	
	if ( pInSuperiorElement != NULL ){
		pInSuperiorElement->insertObjectInElement( this );
	}else{
		updateAllValues();
	}
	if ( pInSuperiorElement ){
		vectorProperty.setDefiningFibElement( this );
	}else{
		vectorProperty.setDefiningFibElement( this, false );
	}
}

#else //FEATURE_SIMPLE_CONSTRUCTOR

/**
 * parameterconstructor
 *
 * @param inVectorProperty the propertyvector this property should have
 * @param pInSuperiorElement the fib -Element in which this
 * 	property -element is an underobject
 * @param pInPreviousFibElement the fib -Element which stands in th order
 * 	of Fib -elements befor this Fib -element
 * @param pInUnderobject the fib -Element which is the underobejct of
 * 	this fib -element (it also stands next in the order of fib -elements)
 */
cProperty::cProperty( const cVectorProperty & inVectorProperty,
		cFibElement * pInSuperiorElement,
		cFibElement * pInPreviousFibElement,
		cFibElement * pInUnderobject ):
		cFibLimb( pInSuperiorElement, pInPreviousFibElement, pInUnderobject ),
		vectorProperty( inVectorProperty ){
	
	if ( pInSuperiorElement ){
		vectorProperty.setDefiningFibElement( this );
	}else{
		vectorProperty.setDefiningFibElement( this, false );
	}
	
	updateAllValues();
}

#endif //FEATURE_SIMPLE_CONSTRUCTOR



/**
 * copyconstructor
 * This copyconstructor constructs a copy of the given property -Element.
 * It dosn't copy other property -elements than the given, even if ther are
 * in the property -element.
 *
 * @param propertyElement the property -element to copy
 */
cProperty::cProperty( const cProperty &propertyElement ):
		cFibLimb( propertyElement ),
		vectorProperty( propertyElement.vectorProperty ){
	
	vectorProperty.setDefiningFibElement( this, false );
}


/**
 * The constructor for restoring a propertyelement from an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node the fib -object is stored in
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
 * 	to restore fib -element, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 */
cProperty::cProperty( const TiXmlElement * pXmlElement, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables ): vectorProperty( 0 ){
	
	if ( pXmlElement == NULL ){
		//noting to restore
		outStatus = -1;
		return;
	}
	string szElementType( pXmlElement->Value() );
	if ( szElementType != "property" ){
		//wrong element type to restore
		outStatus = -2;
		return;
	}
	bool bVectorPropertyRestored = false;
	for ( const TiXmlNode * pChild = pXmlElement->FirstChild();
			pChild != NULL; pChild = pChild->NextSibling() ) {
		
		int iType = pChild->Type();
		
		switch ( iType ){
			case TiXmlNode::ELEMENT:{
				/*check if this is a valid fib -element xml -element, create
				the apropirate fib -element and call its restoreXml() method*/
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
						continue;
					}else if ( strncmp( "property.", szVectorXmlType, 9 ) != 0 ){
						outStatus = 2;
						continue;
					}
					//restore the propertyvector
					if ( ! bVectorPropertyRestored ){
						vectorProperty = cVectorProperty( pXmlElement, outStatus, liDefinedVariables );
						if ( outStatus < 0 ){
							return;
						}
						bVectorPropertyRestored = true;
						vectorProperty.setDefiningFibElement( this, false );
					}else{//to many propertyvector -> invalid data in stream
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
					}else{//to many underobjects -> no correct property element
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
				//invalid propertyelement
				if ( outStatus ){
					outStatus = 2;
				}
				continue;
		}
	}
	if ( ! bVectorPropertyRestored ){
		outStatus = -2;
		return;
	}
	if ( pUnderObject == NULL ){
		outStatus = -2;
		return;
	}
}


/**
 * This constructor restores a propertyelement from the stream where it is
 * stored in the compressed fib -format.
 * This constructor is for internal use only.
 *
 * @param iBitStream the stream wher the propertyelement is stored to in,
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
 * 	to restore fib -element, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 * @param validDomains the domains valid for restoring the fib -elements
 * @param pNextRoot the next higher root -element for the to restore
 * 	fib -elements, or the last restored root -element
 */
cProperty::cProperty( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains,
		cRoot * pNextRoot ): vectorProperty( 0 ){
	
	if ( ! iBitStream.getStream()->good() ){
		outStatus = -1;
		return;
	}
	if ( pNextRoot == NULL ){
		outStatus = -2;
		return;
	}
	//restore the vector of the property
	//restore the propertytype
	cTypeProperty typeProperty = pNextRoot->restorePropertyType(
		iBitStream, outStatus );
	if ( outStatus < 0 ){
		//restoring propertytype failed
		return;
	}
	cDomain * pDomainProperty = validDomains.getDomainForElement( typeProperty );
	bool bStandardDomainProperty = false;
	if ( pDomainProperty == NULL ){
		pDomainProperty = typeProperty.getStandardDomain();
		bStandardDomainProperty = true;
	}
	
	cTypeVariable typeVariable;
	cDomain * pDomainVariable = validDomains.getDomainForElement( typeVariable );
	bool bStandardDomainVariable = false;
	if ( pDomainVariable == NULL ){
		pDomainVariable = typeVariable.getStandardDomain();
		bStandardDomainVariable = true;
	}
	
	vectorProperty = cVectorProperty( iBitStream, outStatus,
		liDefinedVariables, pDomainProperty, pDomainVariable,
		typeProperty.getNumberOfProperty() );
	
	if ( bStandardDomainProperty ){
		delete pDomainProperty;
	}
	if ( bStandardDomainVariable ){
		delete pDomainVariable;
	}
	vectorProperty.setDefiningFibElement( this, false );
	
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
char cProperty::getType() const{
	return 'y';
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
bool cProperty::evalueObject( iEvaluePosition & evaluePosition,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties ) const{
	
	if ( pUnderObject == NULL ){
		//nothing to evalue
		return false;
	}
#ifdef FEATURE_EVALUE_ALL_PROPERTIES_IN_C_PROPERTY
	if ( vectorProperty.isEvalued() ){
		//add the property of this propertyelement to the propertylist
		liVecProperties.push_back( vectorProperty );
	}
#else //deprecated not FEATURE_EVALUE_ALL_PROPERTIES_IN_C_PROPERTY

#ifdef FEATURE_CHECK_OVERWRITTEN_WITH_IS_OVERWRITTEN_VECTOR
	if ( vectorProperty.isEvalued() ){
		/*if this is a property that overwrite properties of the same type
		-> delete properties that this overwrites from the property list*/
		if ( vectorProperty.isOverwriting() ){
			for ( list<cVectorProperty>::iterator itrProperties = liVecProperties.begin();
					itrProperties != liVecProperties.end(); ){
				
				if ( vectorProperty.isOverwritenVector( *itrProperties ) ){
					//erase overwritten property
					itrProperties = liVecProperties.erase( itrProperties );
				}else{
					//check the next propertyvector
					itrProperties++;
				}
			}
		}
		//add the property of this propertyelement to the propertylist
		liVecProperties.push_back( vectorProperty );
	}
#else //FEATURE_CHECK_OVERWRITTEN_WITH_IS_OVERWRITTEN_VECTOR
	cTypeProperty * typeOfProperty = (cTypeProperty*)(vectorProperty.getElementType());
	if ( typeOfProperty->isEvalued() ){
		/*if this is a property that overwrite properties of the same type
		-> delete properties that this overwrites from the property list*/
		list<cTypeProperty> liOverwritenTyps = typeOfProperty->getOverwritenTyps();
		delete typeOfProperty;
		if ( ! liOverwritenTyps.empty() ){
			for ( list<cVectorProperty>::iterator itrProperties = liVecProperties.begin();
					itrProperties != liVecProperties.end(); ){
				
				bool bNotDeleted = true;
				typeOfProperty = (cTypeProperty*)(itrProperties->getElementType());
				
				for ( list<cTypeProperty>::iterator itrPropertyType = liOverwritenTyps.begin();
						itrPropertyType != liOverwritenTyps.end(); itrPropertyType++ ){
					
					if ( typeOfProperty->equalElementType( *itrPropertyType ) ){
						itrProperties = liVecProperties.erase( itrProperties );
						bNotDeleted = false;
						break;
					}
				}
				delete typeOfProperty;
				if ( bNotDeleted ){
					//check the next propertyvector
					itrProperties++;
				}
			}
		}
		//add the property of this propertyelement to the propertylist
		liVecProperties.push_back( vectorProperty );
	}else{//don't add this property to the liVecProperties
		delete typeOfProperty;
	}
#endif //FEATURE_CHECK_OVERWRITTEN_WITH_IS_OVERWRITTEN_VECTOR
#endif //FEATURE_EVALUE_ALL_PROPERTIES_IN_C_PROPERTY
	return pUnderObject->evalueObject( evaluePosition, objectPoint, liVecProperties );
}


/**
 * This method evaluades the fib -object.
 * Evertime a fib -elements, with a type of the given type chars in
 * liCFibElementTyps, is reached while evaluation, it is given
 * back with the properties which it has.
 * Ever pointelement is given back. The type chars for pointelements
 * don't need to be in the list liCFibElementTyps.
 *
 * @param evalueFibElement a reference to the object with the
 * 	evalueElement() method to evalue /store the fib -elements and ther
 * 	properties; everytime a fib -element (with one of the type given
 * 	in liCFibElementTyps) is reached in the evaluation, the method
 * 	evalueElement() of this objects is called with the fib -element
 * 	and the properties of the fib -element; @see iEvalueFibElement
 * @param objectPoint the object point in the order of true partobjects
 * 	to evalue
 * @param liVecProperties a list with the property vectors which should
 * 	be global for the evalued object
 * @param liCFibElementTyps a list with the type chars (@see getType)
 * 	of the fib -elements to return
 * @return if the evalueation was successfull true, else false
 */
bool cProperty::evalueObject( iEvalueFibElement & evalueFibElement,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties,
		const list<char> & liCFibElementTyps ){
	
	//check if this fib -element should be given back with evalueElement()
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
#ifdef FEATURE_EVALUE_ALL_PROPERTIES_IN_C_PROPERTY
	if ( vectorProperty.isEvalued() ){
		//add the property of this propertyelement to the propertylist
		liVecProperties.push_back( vectorProperty );
	}
#else //deprecated not FEATURE_EVALUE_ALL_PROPERTIES_IN_C_PROPERTY

#ifdef FEATURE_CHECK_OVERWRITTEN_WITH_IS_OVERWRITTEN_VECTOR
	if ( vectorProperty.isEvalued() ){
		/*if this is a property that overwrite properties of the same type
		-> delete properties that this overwrites from the property list*/
		if ( vectorProperty.isOverwriting() ){
			for ( list<cVectorProperty>::iterator itrProperties = liVecProperties.begin();
					itrProperties != liVecProperties.end(); ){
				if ( vectorProperty.isOverwritenVector( *itrProperties ) ){
					//erase overwritten property
					itrProperties = liVecProperties.erase( itrProperties );
				}else{
					//check the next propertyvector
					itrProperties++;
				}
			}
		}
		//add the property of this propertyelement to the propertylist
		liVecProperties.push_back( vectorProperty );
	}
#else //FEATURE_CHECK_OVERWRITTEN_WITH_IS_OVERWRITTEN_VECTOR
	cTypeProperty * typeOfProperty = (cTypeProperty*)(vectorProperty.getElementType());
	if ( typeOfProperty->isEvalued() ){
		/*if this is a property that overwrite properties of the same type
		-> delete properties that this overwrites from the property list*/
		list<cTypeProperty> liOverwritenTyps = typeOfProperty->getOverwritenTyps();
		delete typeOfProperty;
		if ( ! liOverwritenTyps.empty() ){
			for ( list<cVectorProperty>::iterator itrProperties = liVecProperties.begin();
					itrProperties != liVecProperties.end(); ){
				bool bNotDeleted = true;
				typeOfProperty = (cTypeProperty*)(itrProperties->getElementType());
				
				for ( list<cTypeProperty>::iterator itrPropertyType = liOverwritenTyps.begin();
						itrPropertyType != liOverwritenTyps.end(); itrPropertyType++ ){
					
					if ( typeOfProperty->equalElementType( *itrPropertyType ) ){
						itrProperties = liVecProperties.erase( itrProperties );
						bNotDeleted = false;
						break;
					}
				}
				delete typeOfProperty;
				if ( bNotDeleted ){
					//check the next propertyvector
					itrProperties++;
				}
			}
		}
		//add the property of this propertyelement to the propertylist
		liVecProperties.push_back( vectorProperty );
	}else{//don't add this property to the liVecProperties
		delete typeOfProperty;
	}
#endif //FEATURE_CHECK_OVERWRITTEN_WITH_IS_OVERWRITTEN_VECTOR
#endif //FEATURE_EVALUE_ALL_PROPERTIES_IN_C_PROPERTY
	
	//evalue main -fib -object
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
unsignedLongFib cProperty::getTimeNeed( unsignedLongFib lMaxTime ) const{
	
	unsignedLongFib ulTimeNeeded = 1 + vectorProperty.getNumberOfElements();

	if ( (lMaxTime == 0 ) || (ulTimeNeeded < lMaxTime) ){
		if ( pUnderObject != NULL ){
			if (lMaxTime == 0 ){
				ulTimeNeeded += pUnderObject->getTimeNeed( 0 );
			}else{
				ulTimeNeeded += pUnderObject->getTimeNeed( lMaxTime - ulTimeNeeded );
			}
		}
		//nothing to evalue
		return ulTimeNeeded;
	}//else
	return lMaxTime;

}


/**
 * This method evaluades the size of the Fib -object in bits in the
 * compressed file form.
 * The optionalpart field of property -elements will be ignored.
 *
 * @see store()
 * @return the size of the Fib -object in bits in the compressed form
 */
unsignedLongFib cProperty::getCompressedSize() const{
	
	unsignedLongFib ulCompressedSize = 4;
	//add the compressed size for the propertytype
#ifdef FEATURE_FAST_UPDATE
	//find the next root -element
	const cFibElement * pNextRootElement = this;
	while ( (pNextRootElement != NULL) && (pNextRootElement->getType() != 'r') ){
		pNextRootElement = pNextRootElement->pSuperiorElement;
	}
	if ( pNextRootElement ){
		ulCompressedSize += ((cRoot*)pNextRootElement)->getBitsForStoredPropertyType();
	}
#else //FEATURE_FAST_UPDATE
	if ( pNextRootElement ){
		ulCompressedSize += pNextRootElement->getBitsForStoredPropertyType();
	}
#endif //FEATURE_FAST_UPDATE
	//add compressed size for the Vectorelements
	ulCompressedSize += vectorProperty.getCompressedSize();
		
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
bool cProperty::isUsedVariable( const cFibVariable *variable ,
		edDirection direction ) const{
	
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		const bool bVariableUsed = vectorProperty.isUsedVariable( variable );
		if ( bVariableUsed ){
			return true;
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
set<cFibVariable*> cProperty::getUsedVariables( edDirection direction ){
	
	set<cFibVariable*> setUsedVariables;
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		setUsedVariables = vectorProperty.getUsedVariables();
	}
	
	set<cFibVariable*> setUsedVariableleaf = cFibLimb::getUsedVariables( direction );
	setUsedVariables.insert( setUsedVariableleaf.begin(),
		setUsedVariableleaf.end() );

	return setUsedVariables;
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
bool cProperty::replaceVariable( cFibVariable *variableOld,
		cFibVariable *variableNew ){
	
	if ( (variableOld == NULL) || (variableNew == NULL) ){
		//can't replace
		return false;
	}
	//replace variable in propertyvector
	if ( ! vectorProperty.replaceVariable( variableOld, variableNew ) ){
		return false;
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
cFibElement *cProperty::copyElement( const char cType, const unsignedIntFib
		elementPoint, bool bAbsolute ) const{
	
	if ( elementPoint == 0 ){
		//copy this element
		return new cProperty( *this );
	}//else get the fib element and copy it
	
	const cFibElement * pFibElementToCopy = getConstFibElement(
		cType, elementPoint, bAbsolute );
	
	if ( pFibElementToCopy ){
		return ( pFibElementToCopy->copyElement( 'u', 0 ) );
	}//else
	return NULL;
}


/**
 * This method assigns / copies the values from the given Fib element
 * fibElement to this Fib element. This means, it will copy everything
 * of the Fib element fibElement except pointers to other Fib elements
 * (e. g. for subobjects), these will remain the same.
 * For that both Fib elements have to be of the same type.
 * Note: The variables used in this Fib element should be equal some
 * 	variables defined above.
 * 	@see cFibVariable::equal( const cFibVariable &variable, false )
 *
 * @see getType()
 * @param fibElement the Fib element, from which to assign / copy the values
 * @return true if the values could be copied from the given Fib element
 * 	fibElement, else false
 */
bool cProperty::assignValues( const cFibElement & fibElement ){
	
	if ( fibElement.getType() != getType() ){
		//both Fib elements not of the same type -> can't assign values
		return false;
	}
	if ( equalElement( fibElement, false ) ){
		//elements already equal -> don't need to assign anything
		return true;
	}
	const cProperty * pOtherProperty = ((const cProperty*)(&fibElement));
	const cVectorProperty * pOtherVectorProperty =
		&(pOtherProperty->vectorProperty);
	
	//try to match used variables
	const set< cFibVariable* > setUsedVariables = (const_cast< cVectorProperty * >(
		pOtherVectorProperty))->getUsedVariables();
	/* The list with the variables to replace:
	 * 	first: the original used variable to replace
	 * 	second: the new variable to replace the original variable
	 */
	list< pair< cFibVariable * ,cFibVariable * > > liVariablesToReplace;
	
	if ( ! getVariablesToReplace( setUsedVariables, liVariablesToReplace ) ){
		//not all variables can be replaced with for this Fib element defined variables
		return false;
	}
	//copy property vector of other property
	//assign the values
	vectorProperty = *pOtherVectorProperty;
	vectorProperty.setDefiningFibElement( this, false );
	
	if ( ! liVariablesToReplace.empty() ){
		//replace variables to replace
		for ( list< pair< cFibVariable * ,cFibVariable * > >::iterator
				itrActualVariable = liVariablesToReplace.begin();
				itrActualVariable != liVariablesToReplace.end(); itrActualVariable++ ){
			
			//replace variable in areavector
			if ( ! vectorProperty.replaceVariable(
					itrActualVariable->first, itrActualVariable->second ) ){
				//Error: should not happen
				return false;
			}
		}//end for all variables to replace
	}//end if variables to replace
	
	return true;
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
bool cProperty::equalInternal( const cFibElement & fibObject,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{

	if ( ! equalElementInternal( fibObject, mapEqualRootObjects,
			mapEqualDefinedVariables, bCheckExternalObjects ) ){
		return false;
	}
	
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
bool cProperty::equalElementInternal( const cFibElement & fibElement,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{

	if ( getType() != fibElement.getType() ){
		return false;
	}
	cProperty *pPropertyElement = (cProperty*)(&fibElement);
	
	//compare the propertyvectors
	if ( ! (vectorProperty.equalInternal( pPropertyElement->vectorProperty,
			mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ) ){
		return false;
	}
	return true;
}


#else //FEATURE_EQUAL_FIB_OBJECT

/**
 * This method checks if the given Fib -object is equal to this Fib
 * -object.
 * Variables can be others, but must be defined and used in equivalent
 * Fib -elements.
 *
 * @param fibObject the Fib -object to which this Fib -object should be
 * 	equal
 * @return true if this Fib -object is equal to the given Fib -object,
 * 	else false
 */
bool cProperty::equal( const cFibElement & fibObject ) const{

	if ( ! cFibLimb::equal( fibObject ) ){
		return false;
	}
	
	return equalElement( fibObject );
}


/**
 * This method checks if the given fib -element is equal to this fib
 * -element.
 * The underobjects arn't compared, not even ther count is compared.
 * Used variables can be others.
 *
 * @param fibElement the fib -element to which this fib -element should be
 * 	equal
 * @return true if this fib -element is equal to the given fib -object,
 * 	else false
 */
bool cProperty::equalElement( const cFibElement & fibElement ) const{

	if ( getType() != fibElement.getType() ){
		return false;
	}
	cProperty *pPropertyElement = (cProperty*)(&fibElement);
	
	//compare the propertyvectors
	if ( ! (vectorProperty == pPropertyElement->vectorProperty) ){
		return false;
	}
	return true;
}

#endif //FEATURE_EQUAL_FIB_OBJECT

/**
 * This method stores this Fib -object in the XML -format into the
 * given stream.
 *
 * @param stream the stream where this Fib -object should be stored to
 * @return true if this Fib -object is stored, else false
 */
bool cProperty::storeXml( ostream &stream ) const{

	bool bReturnValue = true;
	
#ifdef FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	stream<<"<property elementNr=\""<<getNumberOfElement()<<"\" >"<<endl;
#else //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	stream<<"<property>"<<endl;
#endif //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	bReturnValue &= vectorProperty.storeXml( stream );
	if ( pUnderObject ){
		bReturnValue &= pUnderObject->storeXml( stream );
	}
	stream<<"</property>"<<endl;
	return bReturnValue;
}


/*
 * Property -element methods
 */


/**
 * @return a pointer to the propertyvector of this propertyelement
 */
cVectorProperty * cProperty::getProperty(){
	return & vectorProperty;
}


/**
 * @return a pointer to the propertyvector of this propertyelement
 */
const cVectorProperty * cProperty::getProperty() const{
	return & vectorProperty;
}


/**
 * This method stores this Fib -object in the compressed Fib -format
 * into the given stream.
 * It is needed becouse the stream can yust store byts but the size of
 * fib -elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the fib -elements.
 * Beware: You need to call storeBit() of the root -elements with the
 * domain for the property or the property will not be readebel.
 *
 * @see store
 * @param stream the stream where this Fib -object should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if this Fib -object is stored, else false
 */
bool cProperty::storeBit( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{

#ifdef FEATURE_FAST_UPDATE
	if ( pUnderObject == NULL ){
		return false;
	}
	//find the next root -element
	const cFibElement * pNextRootFibElement = this;
	while ( (pNextRootFibElement != NULL) && (pNextRootFibElement->getType() != 'r') ){
		pNextRootFibElement = pNextRootFibElement->pSuperiorElement;
	}
	if ( pNextRootFibElement == NULL ){
		return false;
	}
	const cRoot * pNextRootElement = (const cRoot *)pNextRootFibElement;
#else //FEATURE_FAST_UPDATE
	if ( (pNextRootElement == NULL) || (pUnderObject == NULL) ){
		return false;
	}
#endif //FEATURE_FAST_UPDATE
	
	const char cInitiation = 0x03;
	const bool bInitiationStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, &cInitiation, 4 );
	if ( ! bInitiationStored ){
		return false;
	}
	//store the propertyvectortype
	cTypeProperty * pPropertyType = (cTypeProperty*)(vectorProperty.getElementType());
	const bool bPropertyTypeStored = pNextRootElement->storePropertyType(
		stream,  cRestBits, uiRestBitPosition, *pPropertyType );
	delete pPropertyType;
	if ( ! bPropertyTypeStored ){
		return false;
	}
	//store the propertyvector
	const bool bVectorStored = vectorProperty.store( stream, cRestBits, uiRestBitPosition );
	if ( ! bVectorStored ){
		return false;
	}
	return pUnderObject->storeBit( stream, cRestBits, uiRestBitPosition );
}


/**
 * This method copies the connected object with the given number in the
 * order of connected objects.
 * For this every Fib -element, beginning from this Fib -element, that
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
cFibElement *cProperty::copyInternal( const unsignedIntFib iObjectPoint ) const{

	cProperty * pProperty = NULL;

	if ( pUnderObject ){
		pProperty = new cProperty( *this );
		//copy the underobject
		cFibElement * pCopyUnderobject = pUnderObject->copyInternal( iObjectPoint );
		if ( pCopyUnderobject == NULL ){
			//no such objectpoint
			delete pProperty;
			return NULL;
		}
		pProperty->pUnderObject = pCopyUnderobject;
#ifdef FEATURE_FAST_UPDATE
		if ( pProperty->pUnderObject ){
			pProperty->pUnderObject->pSuperiorElement = pProperty;
		}
#endif //FEATURE_FAST_UPDATE
	}else{//no underobject
		if ( iObjectPoint == 0 ){
			//just copy if this is the correct objectpoint
			pProperty = new cProperty( *this );
		}
	}
	return pProperty;
}












