/**
 * @class cExtSubobject
 * file name: cExtSubobject.cpp
 * @author Betti Oesterholz
 * @date 06.11.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the external subobject element.
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
 * This class represents the external subobject element.
 * External subobject elements are for calling subobjects that are given a
 * external object element (@see cExtObject).
 *
 */
/*
History:
06.11.2011  Oesterholz  created
29.01.2011  Oesterholz  FEATURE_EXT_SUBOBJECT_INPUT_VECTOR implemented:
	the input values are now a vector of values
22.11.2012  Oesterholz  Bugfix: a root element can be called more than one
	time by external objects
29.12.2012  Oesterholz  debugging evalue will print number of input variables
31.07.2013  Oesterholz  method assignValues() added;
	FEATURE_EXT_SUBOBJECT_INPUT_VECTOR as default (not case removed)
*/

//TODO debugging switches
//#define DEBUG
//#define DEBUG_EVALUE


#include "cExtSubobject.h"

#include "cExtObject.h"
#include "cTypeExtSubobject.h"
#include "cTypeVariable.h"
#include "cDomainIntegerBasis.h"
#include "cDomainNaturalNumber.h"



using namespace fib;



/**
 * parameterconstructor
 *
 * @param uiInNumberOfSubobject the number of the subobject to call
 * @param vecInOutputValues the vector with the output variables 
 * 	of the subobject to call
 * @param pInSuperiorElement the Fib element in which this
 * 	external object element is an subobject
 */
cExtSubobject::cExtSubobject( unsignedIntFib uiInNumberOfSubobject,
		cVectorExtSubobject vecInOutputValues,
		cFibElement * pInSuperiorElement ):
		cFibLeaf( pInSuperiorElement ),
		uiNumberOfSubobject( uiInNumberOfSubobject ),
		vecOutputValues( vecInOutputValues, this ){
	
	if ( pInSuperiorElement ){
		pInSuperiorElement->insertObjectInElement( this );
	}
}


/**
 * parameterconstructor
 *
 * @param uiInNumberOfSubobject the number of the subobject to call
 * @param uiNumberOfOutputVariables the number of output variables 
 * 	of the subobject to call
 * @param pInSuperiorElement the Fib element in which this
 * 	external object element is an subobject
 */
cExtSubobject::cExtSubobject( unsignedIntFib uiInNumberOfSubobject,
		unsignedIntFib uiNumberOfOutputVariables,
		cFibElement * pInSuperiorElement ):
		cFibLeaf( pInSuperiorElement ),
		uiNumberOfSubobject( uiInNumberOfSubobject ),
		vecOutputValues( uiNumberOfOutputVariables, this ){
	
	if ( pInSuperiorElement ){
		pInSuperiorElement->insertObjectInElement( this );
	}
}


/**
 * copyconstructor
 * This copyconstructor constructs a copy of the given external object element.
 * It dosn't copy other Fib elements than the given.
 *
 * @param extObjectElement the external object element to copy
 */
cExtSubobject::cExtSubobject( const cExtSubobject & extObjectElement ):
		cFibLeaf( extObjectElement ),
		uiNumberOfSubobject( extObjectElement.uiNumberOfSubobject ),
		vecOutputValues( extObjectElement.vecOutputValues, this ){
	//nothing to do
}


/**
 * The constructor for restoring a external object element from an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node the Fib object is stored in
 * @param outStatus An reference to an integervalue where the errorvalue
 * 	can be stored to.
 * 	possible error values are:
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
cExtSubobject::cExtSubobject( const TiXmlElement * pXmlElement, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables ): uiNumberOfSubobject( 0 ),
		vecOutputValues( 0 ){
	
	if ( pXmlElement == NULL ){
		//noting to restore
		outStatus = -1;
		return;
	}
	string szElementType( pXmlElement->Value() );
	if ( szElementType != "subobject" ){
		//wrong element type to restore
		outStatus = -2;
		return;
	}
	//read attribute number for the subobject number
	const char * szNumberOfSubobject = pXmlElement->Attribute( "number" );
	
	if ( szNumberOfSubobject == NULL ){
		outStatus = 2;
	}else{
		uiNumberOfSubobject = atol( szNumberOfSubobject );
	}
	//restore output variables just once
	bool bOutputValuesRestored = false;
	
	//restore the output variables if existing
	for ( const TiXmlNode * pChild = pXmlElement->FirstChild();
			pChild != NULL; pChild = pChild->NextSibling() ) {
		
		int iType = pChild->Type();
		
		switch ( iType ){
			case TiXmlNode::ELEMENT:{
				/*check if this is a valid Fib element xml-element*/
				const TiXmlElement * pXmlElement = pChild->ToElement();
				if ( pXmlElement == NULL ){
					outStatus = 2;
					continue;
				}
				const string szElementType( pXmlElement->Value() );
				
				if ( szElementType == "vector" ){
					//element for the output values
					if ( ! bOutputValuesRestored ){
						//restore the output values
						//check the attribute of the vector
						const char * szVectorXmlType = pXmlElement->Attribute( "type" );
						
						if ( szVectorXmlType == NULL ){
							outStatus = 2;
							continue;
						}else if ( string( "externSubobject" ).compare( szVectorXmlType ) != 0 ){
							outStatus = 2;
							continue;
						}
						//restore the vector
						vecOutputValues = cVectorExtSubobject( pXmlElement, outStatus,
							liDefinedVariables );
						vecOutputValues.setDefiningFibElement( this, false );
						bOutputValuesRestored = true;
						if ( outStatus < 0 ){
							return;
						}
					}
				}else{//no correct subelement for a external subobject element
					outStatus = 2;
					continue;
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
				//invalid external object object
				if ( outStatus ){
					outStatus = 2;
				}
				continue;
		}//end switch XML subelement
	}//end for all XML subelements
	if ( ( ! bOutputValuesRestored ) && ( 0 <= outStatus ) ){
		//warning no output values restored
		outStatus = 2;
	}
}


/**
 * This constructor restores a external object element from the stream where it is
 * stored in the compressed Fib format.
 * This constructor is for internal use only.
 *
 * @param iBitStream the stream wher the external object element is stored in,
 * 	because this stream is an cReadBits, any number of bits can be
 * 	readed from it
 * @param outStatus An reference to an integervalue, where the errorvalue
 * 	can be stored to. If the pointer is NULL no errorvalue will be
 * 	given back.
 * 	possible error values are:
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
cExtSubobject::cExtSubobject( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains,
		cRoot * pNextRoot ): uiNumberOfSubobject( 0 ), vecOutputValues( 0 ){
	
	DEBUG_OUT_L2(<<"Running compressed restore extern subobject constructor"<<endl);
	
	if ( ! iBitStream.getStream()->good() ){
		outStatus = -1;
		return;
	}
	if ( pNextRoot == NULL ){
		DEBUG_OUT_EL2(<<"Error: compressed restore fails no next root element"<<endl);
		outStatus = -2;
		return;
	}
	
	//read the subobject number
	cDomainNaturalNumber domainNumberOfSubobjects(
		pNextRoot->getNumberOfExternSubobjects() );
	
	//restore the subobject number
	uiNumberOfSubobject = domainNumberOfSubobjects.restoreIntegerValue(
		iBitStream, outStatus );
	if ( outStatus < 0 ){
		return;
	}
	DEBUG_OUT_L2(<<"restored external subobject number: "<<uiNumberOfSubobject<<endl);
	
	//get the domain for the variables
	cTypeVariable typeVariable;
	//return the variable domain
	cDomainIntegerBasis * pDomainVariable = (cDomainIntegerBasis*)
		validDomains.getDomainForElement( typeVariable );
	const bool bStandardDomainVariable = ( pDomainVariable == NULL );
	if ( bStandardDomainVariable ){
		//use the standard domain
		pDomainVariable = (cDomainIntegerBasis*)typeVariable.getStandardDomain();
	}
	//restore output values
	cTypeExtSubobject typeExtSubobject( uiNumberOfSubobject );
	
	//return the extern subobject element domain for the number of output variables
	cDomain * pDomainExtSubobject =
		validDomains.getDomainForElement( typeExtSubobject );
	const bool bStandardDomainExtSubobject = ( pDomainExtSubobject == NULL );
	if ( bStandardDomainExtSubobject ){
		//use the standard domain
		pDomainExtSubobject = typeExtSubobject.getStandardDomain();
	}
	if ( ! pDomainExtSubobject->isVector() ){
		//Error: output values domain is not a vector domain
		if ( bStandardDomainExtSubobject ){
			delete pDomainExtSubobject;
		}
		if ( bStandardDomainVariable ){
			delete pDomainVariable;
		}
		DEBUG_OUT_EL2(<<"Error: external subobject domain is no vector"<<endl);
		outStatus = -2;
		return;
	}
	cDomainVectorBasis * pDomainOutputValues =
		(cDomainVectorBasis*)pDomainExtSubobject;
	//restore the output values
	vecOutputValues = cVectorExtSubobject( iBitStream, outStatus,
		liDefinedVariables, pDomainOutputValues, pDomainVariable );
	
	vecOutputValues.setDefiningFibElement( this, false );
	if ( outStatus < 0 ){
		if ( bStandardDomainExtSubobject ){
			delete pDomainExtSubobject;
		}
		if ( bStandardDomainVariable ){
			delete pDomainVariable;
		}
		DEBUG_OUT_EL2(<<"Error: while restoring vector"<<endl);
		outStatus = -2;
		return;
	}
	
	if ( bStandardDomainExtSubobject ){
		delete pDomainExtSubobject;
	}
	if ( bStandardDomainVariable ){
		delete pDomainVariable;
	}
	
	DEBUG_OUT_L1(<<"End restoring extern subobject"<<endl);
}


/**
 * destructor
 */
cExtSubobject::~cExtSubobject(){
	//nothing to do
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
char cExtSubobject::getType() const{
	
	return 's';
}


/**
 * This method checks, if this Fib element is an valid Fib element.
 *
 * @return true if this Fib element is an valid Fib element, else false
 */
bool cExtSubobject::isValidFibElement() const{
	
/*TODO weg? just check Fib element
	const cRoot * pSuperiorRoot = getSuperiorRootElement();
	if ( pSuperiorRoot == NULL ){
		//external subobjects need a superior root element
		return false;
	}
	if ( ( uiNumberOfSubobject < 1 ) ||
			(pSuperiorRoot->getNumberOfExternSubobjects() < uiNumberOfSubobject ) ){
		//subobject number to hight / not existing
		return false;
	}
	
	//test output variables
	for ( vector< cFibVariable * >::const_iterator itrOutputVariable = vecOutputValues.begin();
			itrOutputVariable != vecOutputValues.end(); itrOutputVariable++ ){
		
		if ( (*itrOutputVariable) == NULL ){
			//incorrect output variable
			return false;
		}else{//the output variable exists
			if ( ! isDefinedVariable( (*itrOutputVariable), ED_HIGHER ) ){
				//the output variable is not defined higher
				return false;
			}
		}
	}
*/
	return cFibLeaf::isValidFibElement();
}


/**
 * This method evaluades the Fib object.
 *
 * @param evaluePosition a reference to the object with the
 * 	evaluePosition() method to evalue /store the positions and ther
 * 	properties; everytime a external object (to evalue) is reached in the
 * 	evaluation, this method is called with the position and the
 * 	properties of the point ; @see iEvaluePosition
 * @param objectPoint the object point in the order of true partobjects
 * 	to evalue
 * @param liVecProperties a list with the property vectors which should
 * 	be global for the evalued object
 * @return if the evalueation was successfull true, else false
 */
bool cExtSubobject::evalueObject( iEvaluePosition & evaluePosition,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties ) const{
	
	if ( objectPoint != 0 ){
		//no such object point
		return false;
	}
#ifdef DEBUG_EVALUE
	const int iOutNumberOfSubobject = uiNumberOfSubobject;
	printf( "cExtSubobject::evalueObject() with number %i\n", iOutNumberOfSubobject );
#endif
	//get the subobject to evalue
	cRoot * pSuperiorRoot = const_cast< cExtSubobject* >(this)->
		getSuperiorRootElement();
	
	if ( pSuperiorRoot == NULL ){
		//no calling external object -> no subobject to evalue
		return false;
	}
	cExtObject * pCallingExtObject = pSuperiorRoot->getCallingExtObject();
	
	if ( pCallingExtObject == NULL ){
		//no calling external object -> no subobject to evalue
		return false;
	}
#ifdef DEBUG_EVALUE
	const long lTmpIdentifier = pCallingExtObject->getIdentifier();
	printf( "cExtSubobject::evalueObject() for external subobject with identifier %li", lTmpIdentifier );
#endif //DEBUG_EVALUE
	
	//get subobject to evalue
	cFibElement * pSubobjectToEvalue =
		pCallingExtObject->getSubobject( uiNumberOfSubobject );
	if ( pSubobjectToEvalue == NULL ){
		//no subobject to evalue in the calling external object
		return false;
	}
	//set the input variables
	vector< cFibVariable* > vecInputVariables =
		pCallingExtObject->getOutputVariables( uiNumberOfSubobject );
	
	vector< cFibVariable* >::iterator itrInVar = vecInputVariables.begin();
#ifdef DEBUG_EVALUE
	const int uiNumberInputValues = vecInputVariables.size();
	printf( " and %u input values:", uiNumberInputValues );
#endif //DEBUG_EVALUE
	
	for ( unsignedIntFib uiActualElement = 1;
			itrInVar != vecInputVariables.end();
			uiActualElement++, itrInVar++ ){
		
		if ( *itrInVar ){
			(*itrInVar)->setValue( vecOutputValues.getValue( uiActualElement ) );
#ifdef DEBUG_EVALUE
			const double dActualvalue = vecOutputValues.getValue( uiActualElement );
			printf( " %lf;", dActualvalue );
#endif//DEBUG_EVALUE
		}//else no input variable to set
	}
#ifdef DEBUG_EVALUE
	printf( "\n" );
#endif//DEBUG_EVALUE
	//evalue the subobject
	return pSubobjectToEvalue->evalueObject( evaluePosition, 0, liVecProperties );
}


/**
 * This method evaluades the Fib object.
 * Evertime a Fib elements, with a type of the given type chars in
 * liCFibElementTyps, is reached while evaluation, it is given
 * back with the properties which it has.
 * Every point element is given back. The type chars for point elements
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
bool cExtSubobject::evalueObject( iEvalueFibElement & evalueFibElement,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties,
		const list<char> & liCFibElementTyps ){
	
	//check if this Fib element should be given back with evalueElement()
	for ( list<char>::const_iterator itrCType = liCFibElementTyps.begin();
			itrCType != liCFibElementTyps.end(); itrCType++ ){
		
		if ( (*itrCType) == getType() ){
			//call evalueElement() with this element
			return evalueFibElement.evalueElement( *this, liVecProperties );
		}
	}//else if this element shouldn't be returned
	
	if ( objectPoint != 0 ){
		//no such object point
		return false;
	}
	//get the subobject to evalue
	cRoot * pSuperiorRoot = const_cast< cExtSubobject* >(this)->
		getSuperiorRootElement();
	
	if ( pSuperiorRoot == NULL ){
		//no calling external object -> no subobject to evalue
		return false;
	}
	cExtObject * pCallingExtObject = pSuperiorRoot->getCallingExtObject();
	
	if ( pCallingExtObject == NULL ){
		//no calling external object -> no subobject to evalue
		return false;
	}
	//get subobject to evalue
	cFibElement * pSubobjectToEvalue =
		pCallingExtObject->getSubobject( uiNumberOfSubobject );
	if ( pSubobjectToEvalue == NULL ){
		//no subobject to evalue in the calling external object
		return false;
	}
	//set the input variables
	vector< cFibVariable* > vecInputVariables =
		pCallingExtObject->getOutputVariables( uiNumberOfSubobject );
	
	vector< cFibVariable* >::iterator itrInVar = vecInputVariables.begin();
	
	for ( unsignedIntFib uiActualElement = 1;
			itrInVar != vecInputVariables.end();
			uiActualElement++, itrInVar++ ){
		
		if ( *itrInVar ){
			(*itrInVar)->setValue( vecOutputValues.getValue( uiActualElement ) );
		}//else no input variable to set
	}
	
	//evalue the subobject
	return pSubobjectToEvalue->evalueObject( evalueFibElement, 0,
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
unsignedLongFib cExtSubobject::getTimeNeed( unsignedLongFib lMaxTime ) const{
	
	if ( (1 <= lMaxTime) && (lMaxTime <= 2) ){
		//max time is up with evaluing this extern object element
		return lMaxTime;
	}
	//evalue time for the external subobject
	
	//get the subobject to evalue
	cRoot * pSuperiorRoot = const_cast< cExtSubobject* >(this)->
		getSuperiorRootElement();
	
	if ( pSuperiorRoot == NULL ){
		//no calling external object -> no subobject to evalue
		return 2;
	}
	cExtObject * pCallingExtObject = pSuperiorRoot->getCallingExtObject();
	
	if ( pCallingExtObject == NULL ){
		//no calling external object -> no subobject to evalue
		return 2;
	}
	//get subobject to evalue
	cFibElement * pSubobjectToEvalue =
		pCallingExtObject->getSubobject( uiNumberOfSubobject );
	if ( pSubobjectToEvalue == NULL ){
		//no subobject to evalue in the calling external object
		return 2;
	}
	//set the input variables
	vector< cFibVariable* > vecInputVariables =
		pCallingExtObject->getOutputVariables( uiNumberOfSubobject );
	
	vector< cFibVariable* >::iterator itrInVar = vecInputVariables.begin();
	
	for ( unsignedIntFib uiActualElement = 1;
			itrInVar != vecInputVariables.end();
			uiActualElement++, itrInVar++ ){
		
		if ( *itrInVar ){
			(*itrInVar)->setValue( vecOutputValues.getValue( uiActualElement ) );
		}//else no input variable to set
	}
	
	if ( lMaxTime != 0 ){
		lMaxTime -= 2;
	}
	//evalue the subobject
	return pSubobjectToEvalue->getTimeNeed( lMaxTime ) + 2;
}


/**
 * This method evaluades the size of the Fib object in bits in the
 * compressed file form.
 *
 * @see store()
 * @return the size of the Fib object in bits in the compressed form
 */
unsignedLongFib cExtSubobject::getCompressedSize() const{
	
	unsignedLongFib ulCompressedSize = 4;
	//add bits for the subobject number
	const cRoot * pSuperiorRoot = getSuperiorRootElement();
	if ( pSuperiorRoot ){
		//add bits for the number of the subobject
		cDomainNaturalNumber domainNumberOfSubobjects(
			pSuperiorRoot->getNumberOfExternSubobjects() );
		ulCompressedSize += domainNumberOfSubobjects.getCompressedSizeForValue();
	}
	
	cDomains validDomains = getValidValueDomains();
	//add bits for the output values
	ulCompressedSize += vecOutputValues.getCompressedSize();
	
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
bool cExtSubobject::isUsedVariable( const cFibVariable * pVariable ,
		edDirection direction ) const{
	
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		//check this Fib element
		
		if ( vecOutputValues.isUsedVariable( pVariable ) ){
			return true;
		}
	}
	if ( (direction == ED_ALL) ||
			(direction == ED_HIGHER) || (direction == ED_HIGHER_EQUAL) ){
		//search for the variable in direction higher
		return cFibLeaf::isUsedVariable( pVariable, ED_HIGHER );
	}//else all possible direction searched and variables not found
	return false;
}


/**
 * This method returns all used variables in the given direction from
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
set<cFibVariable*> cExtSubobject::getUsedVariables( edDirection direction ){
	
	set< cFibVariable* > setUsedVariables;
	if ( (direction == ED_ALL) ||
			(direction == ED_HIGHER) || (direction == ED_HIGHER_EQUAL) ){
		//search for the variable in direction higher
		setUsedVariables = cFibLeaf::getUsedVariables( ED_HIGHER );
	}
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		//search this Fib element -> insert output variables
		set<cFibVariable*> vecOutputVariables =
			vecOutputValues.getUsedVariables();
		
		setUsedVariables.insert( vecOutputVariables.begin(),
			vecOutputVariables.end() );
	}//all possible direction searched

	return setUsedVariables;
}


/**
 * This method replace the variable pVariableOld with the variable
 * pVariableNew in the object.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @see isDefinedVariable()
 * @param pVariableOld the variable to replace
 * @param pVariableNew the variable with which the variable pVariableNew
 * 	is to replace
 * @return true if the variable pVariableNew is replaced with pVariableNew,
 * 	else false
 */
bool cExtSubobject::replaceVariable( cFibVariable * pVariableOld,
		cFibVariable * pVariableNew ){
	
	if ( ( pVariableOld == NULL ) || ( pVariableNew == NULL ) ){
		//can't replace
		return false;
	}
	//check output variables
	//check output values
	return vecOutputValues.replaceVariable( pVariableOld, pVariableNew );
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
cFibElement * cExtSubobject::copyElement( const char cType, const unsignedIntFib
		elementPoint, bool bAbsolute ) const{
	
	if ( elementPoint == 0 ){
		//copy this Fib element
		return new cExtSubobject( *this );
	}//else other element point to copy
	
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
bool cExtSubobject::assignValues( const cFibElement & fibElement ){
	
	if ( fibElement.getType() != getType() ){
		//both Fib elements not of the same type -> can't assign values
		return false;
	}
	if ( equalElement( fibElement, false ) ){
		//elements already equal -> don't need to assign anything
		return true;
	}
	const cExtSubobject * pOtherExtSubobject = ((const cExtSubobject*)(&fibElement));
	const cVectorExtSubobject * pOtherOutputValues =
		&(pOtherExtSubobject->vecOutputValues);
	
	//try to match used variables
	const set< cFibVariable* > setUsedVariables = (const_cast< cVectorExtSubobject * >(
		pOtherOutputValues))->getUsedVariables();
	/* The list with the variables to replace:
	 * 	first: the original used variable to replace
	 * 	second: the new variable to replace the original variable
	 */
	list< pair< cFibVariable * ,cFibVariable * > > liVariablesToReplace;
	
	if ( ! getVariablesToReplace( setUsedVariables, liVariablesToReplace ) ){
		//not all variables can be replaced with for this Fib element defined variables
		return false;
	}
	//assign the values
	uiNumberOfSubobject = pOtherExtSubobject->uiNumberOfSubobject;
	//copy external subobject vector of other external subobject
	vecOutputValues = *pOtherOutputValues;
	vecOutputValues.setDefiningFibElement( this, false );
	
	if ( ! liVariablesToReplace.empty() ){
		//replace variables to replace
		for ( list< pair< cFibVariable * ,cFibVariable * > >::iterator
				itrActualVariable = liVariablesToReplace.begin();
				itrActualVariable != liVariablesToReplace.end(); itrActualVariable++ ){
			
			//replace variable in areavector
			if ( ! vecOutputValues.replaceVariable(
					itrActualVariable->first, itrActualVariable->second ) ){
				//Error: should not happen
				return false;
			}
		}//end for all variables to replace
	}//end if variables to replace
	
	return true;
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
 * 	@see cExtObject will be compared
 * @return true if this Fib object is equal to the given Fib object,
 * 	else false
 */
bool cExtSubobject::equalInternal( const cFibElement & fibObject,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{
	
	if ( ! equalElementInternal( fibObject,
			mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
		return false;
	}
	return cFibLeaf::equalInternal( fibObject,
		mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects );
}


/**
 * This method checks if the given Fib element is equal to this Fib
 * element.
 * The subobjects arn't compared, not even ther count is compared.
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
 * @return true if this Fib element is equal to the given Fib object,
 * 	else false
 */
bool cExtSubobject::equalElementInternal( const cFibElement & fibElement,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{

	if ( getType() != fibElement.getType() ){
		return false;
	}
	cExtSubobject * pExtSubobject = (cExtSubobject*)( &fibElement );
	//compare number of subobject
	if ( uiNumberOfSubobject != pExtSubobject->uiNumberOfSubobject ){
		//not the same subobject number
		return false;
	}//else
	//compare output values vector
	if ( ! vecOutputValues.equalInternal( pExtSubobject->vecOutputValues,
			mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
		return false;
	}
	
	return true;
}

/**
 * This method stores this Fib object in the XML format into the
 * given stream.
 *
 * @param stream the stream where this Fib object should be stored to
 * @return true if this Fib object is stored, else false
 */
bool cExtSubobject::storeXml( ostream &stream ) const{

	bool bReturnValue = true;
	
#ifdef FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	stream<<"<subobject elementNr=\""<<getNumberOfElement()<<"\" number=\""<<
		uiNumberOfSubobject<<"\">"<<endl;
#else //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	stream<<"<subobject number=\""<<uiNumberOfSubobject<<"\">"<<endl;
#endif //FEATURE_OUTPUT_ELEMENT_NUMBER_XML

	//store output value vector
	vecOutputValues.storeXml( stream );
	
	stream<<"</subobject>"<<endl;
	return bReturnValue;
}



/**
 * @return the number of the subobject to call @see uiNumberOfSubobject
 */
unsignedIntFib cExtSubobject::getNumberSubobject() const{

	return uiNumberOfSubobject;
}


/**
 * This method sets the number of the subobject to call
 * (@see uiNumberOfSubobject).
 *
 * @param iInSubobjectNumber the number of the subobject to set
 * @return if the subobject number was set true, else false
 */
bool cExtSubobject::setNumberSubobject(
		const unsignedIntFib iInSubobjectNumber ){
	
	uiNumberOfSubobject = iInSubobjectNumber;
	return true;
}


/**
 * @return the vector with the output values of this external subobject element
 * @see vecOutputValues
 */
cVectorExtSubobject * cExtSubobject::getOutputVector(){
	
	return &vecOutputValues;
}


/**
 * @return the vector with the output values of this external subobject element
 * @see vecOutputValues
 */
const cVectorExtSubobject * cExtSubobject::getOutputVector() const{
	
	return &vecOutputValues;
}



/**
 * This method stores this Fib object in the compressed Fib format
 * into the given stream.
 * It is needed because the stream can yust store byts but the size of
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
bool cExtSubobject::storeBit( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{

	const cRoot * pSuperiorRoot = getSuperiorRootElement();
	if ( pSuperiorRoot == NULL ){
		//no superior root-element can't store subobject
		return false;
	}
	//the value returned by the method
	const char cInitiation = 0x0E;

	const bool bInitiationStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, &cInitiation, 4 );
	if ( ! bInitiationStored ){
		return false;
	}
	//store the number of the subobject
	cDomainNaturalNumber domainNumberOfSubobjects(
		pSuperiorRoot->getNumberOfExternSubobjects() );
		
	const bool bNumberSubobjectStored = domainNumberOfSubobjects.storeUnscaledValue(
		uiNumberOfSubobject, stream, cRestBits, uiRestBitPosition );
	if ( ! bNumberSubobjectStored ){
		//error: number of subobject not stored
		return false;
	}
	
	return vecOutputValues.store( stream, cRestBits, uiRestBitPosition );
}


/**
 * This method copies the connected object with the given number in the
 * order of connected objects.
 * For this every Fib element, beginning from this Fib element, that
 * is part of the connected object, will be copied.
 * Variables which are not defined in the connected object but used
 * don't change ther reference.
 * It is an help method for the copy method. It dosn't update the
 * structural information of the created Fib object.
 *
 * @see copy()
 * @param iObjectPoint the number of the connected object to copy;
 * 	the standart value is 0 for coping the complet actual object
 * @return the copy of the connected object or NULL if non such exists
 */
cFibElement * cExtSubobject::copyInternal( const unsignedIntFib iObjectPoint ) const{
	
	if ( iObjectPoint == 0 ){
		return new cExtSubobject( *this );
	}//else no object point to copy
	return NULL;
}















