/**
 * @class cExtObject
 * file name: cExtObject.h
 * @author Betti Oesterholz
 * @date 27.07.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the external object element.
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
 * This class represents the external objects element of the Fib-multimedialanguage.
 * It is for calling an external object.
 *
 */
/*
History:
27.07.2011  Oesterholz  created
23.01.2012  Oesterholz  input values changed to input vector
18.04.2012  Oesterholz  Bugfix: replace FirstChild()->ToElement() with
	FirstChildElement()
19.08.2012  Oesterholz  Bugfix?: equal* check if same pointers
30.12.2012  Oesterholz  debugging evalue will print number of input variables
*/


//TODO debugging switches
//#define DEBUG
//#define DEBUG_EVALUE


#include "cExtObject.h"

#include "cTypeExtObject.h"
#include "cTypeExtObjectInput.h"
#include "cTypeVariable.h"
#include "cDomainSingle.h"
#include "cDomainIntegerBasis.h"
#include "cDomainVectorBasis.h"

#include <algorithm>


using namespace fib;


/**
 * parameterconstructor
 *
 * @param lInIdentifier The identifier of the external Fib-object this
 * 	external element stands for. @see lIdentifier
 * @param vecInInputValues the vector with the input values of this
 * 	external element @see vecInputValues
 * @param pInSuperiorElement the Fib-element in which this
 * 	Fib-element is an subobject
 */
cExtObject::cExtObject( const longFib lInIdentifier,
		const cVectorExtObject & vecInInputValues,
		cFibElement * pInSuperiorElement ):
		cFibBranch( list<cFibElement*>(), NULL ),
		lIdentifier( lInIdentifier ),
		vecInputValues( vecInInputValues, this ){
	
	fibObjectCounts.vecNumberOfFibElements[
		cFibObjectCounts::EXT_OBJECT ]++;
	fibObjectCounts.vecNumberOfFibElements[
		cFibObjectCounts::ALL ]++;

	if ( pInSuperiorElement ){
		pInSuperiorElement->insertObjectInElement( this );
	}
}


/**
 * parameterconstructor
 *
 * @param uiNumberOfInputValues the number of input values of this
 * 	external element @see vecInputValues
 * @param pInSuperiorElement the Fib-element in which this
 * 	Fib-element is an subobject
 */
cExtObject::cExtObject( const longFib lInIdentifier,
		const unsignedIntFib uiNumberOfInputValues,
		cFibElement * pInSuperiorElement ):
	cFibBranch( list<cFibElement*>(), NULL ),
		lIdentifier( lInIdentifier ),
		vecInputValues( uiNumberOfInputValues, this ){
	
	fibObjectCounts.vecNumberOfFibElements[
		cFibObjectCounts::EXT_OBJECT ]++;
	fibObjectCounts.vecNumberOfFibElements[
		cFibObjectCounts::ALL ]++;

	if ( pInSuperiorElement ){
		pInSuperiorElement->insertObjectInElement( this );
	}
}


/**
 * copyconstructor
 * This copyconstructor constructs a copy of the given external object element.
 * It dosn't copy other Fib-elements than the given, even if ther are
 * in the external object element.
 *
 * @param extObjElement the external object element to copy
 */
cExtObject::cExtObject( const cExtObject & extObjElement ):
		cFibBranch( extObjElement ),
		lIdentifier( extObjElement.lIdentifier ),
		vecInputValues( extObjElement.vecInputValues, this ){
	
	/*don't copy vecSubobjects because subobjects aren't copied, just the
	extObjElement element*/
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	for ( list< pair< cFibElement * , list< cFibVariable * > > >::const_iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	for ( vector< pair< cFibElement * , vector< cFibVariable * > > >::const_iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
			itrActualSubObject = extObjElement.vecSubobjects.begin();
			itrActualSubObject != extObjElement.vecSubobjects.end();
			itrActualSubObject++ ){

		//copy output variables
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
		list< cFibVariable * > vecNewOutputVariables;
		const list< cFibVariable * > & vecOutputVariables =
			itrActualSubObject->second;
		
		for ( list< cFibVariable * >::const_iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
		vector< cFibVariable * > vecNewOutputVariables;
		const vector< cFibVariable * > & vecOutputVariables =
			itrActualSubObject->second;
		
		for ( vector< cFibVariable * >::const_iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
				itrOutputVariable = vecOutputVariables.begin();
				itrOutputVariable != vecOutputVariables.end();
				itrOutputVariable++ ){
			
			vecNewOutputVariables.push_back( new cFibVariable( this ) );
		}
		
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
		vecSubobjects.push_back(
			make_pair( ((cFibElement *)(NULL)), vecNewOutputVariables ) );
#else //FEATURE_C_EXT_OBJECT_USE_LIST
		vecSubobjects.push_back(
			pair< cFibElement * , vector< cFibVariable * > >(
				NULL, vecNewOutputVariables ) );
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
		fibUnderObjects.push_back( NULL );
		
		fibObjectCounts.uiNumberOfObjectpoints++;
	}
	
	fibObjectCounts.vecNumberOfFibElements[
		cFibObjectCounts::EXT_OBJECT ]++;
	fibObjectCounts.vecNumberOfFibElements[
		cFibObjectCounts::ALL ]++;
}


/**
 * The constructor for restoring a extern object element from an TinyXml element.
 *
 * @param pXmlElement a pointer to the TinyXml node the Fib-object is stored in
 * @param outStatus An reference to an integervalue where the error value
 * 	can be stored to.
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 * @param liDefinedVariables a list with the defined variables for the
 * 	to restore Fib-element, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 */
cExtObject::cExtObject( const TiXmlElement * pXmlElement, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables ): lIdentifier( 0 ),
		vecInputValues( 0, this ){
	
	if ( pXmlElement == NULL ){
		//noting to restore
		outStatus = -1;
		return;
	}
	string szElementType( pXmlElement->Value() );
	if ( szElementType != "obj" ){
		//wrong element type to restore
		outStatus = -2;
		return;
	}
	
	//read the identifier number
	const char * szIdentifierNumber = pXmlElement->Attribute( "identifier" );
	
	if ( szIdentifierNumber == NULL ){
		outStatus = 2;
	}else{
		lIdentifier = atol( szIdentifierNumber );
	}
	//restore input values just once
	bool bInputValuesRestored = false;
	
	for ( const TiXmlNode * pChild = pXmlElement->FirstChild();
			pChild != NULL; pChild = pChild->NextSibling() ) {
		
		int iType = pChild->Type();
		
		switch ( iType ){
			case TiXmlNode::ELEMENT:{
				/*check if this is a valid Fib-element xml-element, create
				the apropirate Fib-element and call its restoreXml() method*/
				const TiXmlElement * pXmlElement = pChild->ToElement();
				if ( pXmlElement == NULL ){
					outStatus = 2;
					continue;
				}
				const string szElementType( pXmlElement->Value() );
				
				if ( szElementType == "vector" ){
					//element for the input values
					if ( ! bInputValuesRestored ){
						//restore the input values
						//check the attribute of the vector
						const char * szVectorXmlType = pXmlElement->Attribute( "type" );
						
						if ( szVectorXmlType == NULL ){
							outStatus = 2;
							continue;
						}else if ( string( "externObjectInput" ).compare( szVectorXmlType ) != 0 ){
							outStatus = 2;
							continue;
						}
						//restore the vector
						vecInputValues = cVectorExtObject( pXmlElement, outStatus,
							liDefinedVariables );
						vecInputValues.setDefiningFibElement( this, false );
						bInputValuesRestored = true;
						if ( outStatus < 0 ){
							return;
						}
					}
				}else if ( szElementType == "subobject" ){
					//restore the subobjects
					
					//every subobject has it's own variables
					list< cFibVariable* > liDefinedVariablesCopy( liDefinedVariables );
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
					list< cFibVariable* > vecOutputVariables;
#else //FEATURE_C_EXT_OBJECT_USE_LIST
					vector< cFibVariable* > vecOutputVariables;
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
					
					const TiXmlElement * pXmlElementObject = NULL;
					if ( pXmlElement->FirstChild() ){
						
						pXmlElementObject = pXmlElement->FirstChildElement();
					}
					const string szElementObjectType( pXmlElementObject->Value() );
					if ( szElementObjectType == "output_variables" ){
						//read output variables
						const TiXmlElement * pXmlOutVariable = NULL;
						if ( pXmlElementObject->FirstChild( "variable" ) ){
							
							pXmlOutVariable = pXmlElementObject->FirstChild( "variable" )->ToElement();
						}
						const unsigned long lBiggestDefinedVarValue = liDefinedVariables.size();
						for( int iActualOutVariable = 1; pXmlOutVariable != NULL;
								pXmlOutVariable = pXmlOutVariable->NextSiblingElement( "variable" ),
								iActualOutVariable++ ){
	
							int iNumberOfOutVariable = 0;
							const char * szXmlObjectNumber = pXmlOutVariable->Attribute( "number", & iNumberOfOutVariable );
							if ( szXmlObjectNumber != NULL ){
								//output variable number given
								if ( iActualOutVariable != iNumberOfOutVariable ){
									//Warning: no correct output variable number
									outStatus = 2;
								}
							}
							
							const char * pcValue = pXmlOutVariable->GetText();
							unsigned long lOutVariableValue = 0;
							if ( pcValue ){
								const int iReadValues = sscanf( pcValue, "%lu", & lOutVariableValue );
								if ( iReadValues != 1){
									//Warning: The element text is not a number.
									outStatus = 2;
									continue;
								}
							}
							
							if ( ( pcValue == NULL ) ||
									( lOutVariableValue < lBiggestDefinedVarValue + iActualOutVariable ) ){
								/*Warning: no correct variable identifier / number
								-> take the liDefinedVariablesCopy size as a counter*/
								outStatus = 2;
								lOutVariableValue = lBiggestDefinedVarValue + iActualOutVariable;
							}
							cFibVariable * pOutVariable = new cFibVariable( this );
							pOutVariable->setIntegerValue( lOutVariableValue );
							
							liDefinedVariablesCopy.push_front( pOutVariable );
							vecOutputVariables.push_back( pOutVariable );
						}
						//set the pointer to the subobject
						pXmlElementObject = pXmlElementObject->NextSiblingElement();
						
					}//else element is subobject
					cFibElement * pSubobject = NULL;
					if ( pXmlElementObject ){
						//restore subobject
						pSubobject = cFibElement::restoreXml(
							pXmlElementObject, outStatus, liDefinedVariablesCopy );
					}
					//add the loaded subobject to the extern object
					fibUnderObjects.push_back( pSubobject );
					vecSubobjects.push_back( make_pair(
						pSubobject, vecOutputVariables ) );
					if ( pSubobject != NULL){
						pSubobject->pSuperiorElement = this;
					}else{//Warning: NULL subobject loaded
						outStatus = 2;
					}
					if ( outStatus < 0 ){
						//an error occured
						return;
					}
					
				}else{//unknown xml-element
					outStatus = 2;
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
				//invalid erxternal object object
				outStatus = 2;
		}
		if ( outStatus < 0 ){
			//an error occured
			return;
		}
	}
	
	updateAllCounters();
}


/**
 * This method restores a external object object from the stream where it is
 * stored in the compressed Fib-format.
 * This method is for internal use only.
 *
 * @param iBitStream the stream where this external object object is stored to in,
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
 * @param pNextRoot the next higher root-element for the to restore
 * 	fib-elements, or the last restored root-element
 */
cExtObject::cExtObject( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains,
		cRoot * pNextRoot ): lIdentifier( 0 ), vecInputValues( 0, this ){

	DEBUG_OUT_L2(<<"Running compressed restore extern object constructor"<<endl);
	
	if ( ! iBitStream.getStream()->good() ){
		outStatus = -1;
		return;
	}
	if ( pNextRoot == NULL ){
		outStatus = -2;
		return;
	}
	//get the domain for the extern object element
	cTypeExtObject typeExtObject;
	//return the extern object element domain
	cDomainVectorBasis * pDomainExtObject = (cDomainVectorBasis*)
		validDomains.getDomainForElement( typeExtObject );
	const bool bStandardDomainExtObject = ( pDomainExtObject == NULL );
	if ( bStandardDomainExtObject ){
		//use the standrad domain
		pDomainExtObject = (cDomainVectorBasis*)typeExtObject.getStandardDomain();
	}
	if ( pDomainExtObject->getNumberOfElements() < 3 ){
		/*error in domain (domain for identifier and / or input values
		missing and / or number of subobjects) -> can't load external object*/
		if ( bStandardDomainExtObject ){
			delete pDomainExtObject;
		}
		outStatus = -2;
		return;
	}
	//get the domain for the variables
	cTypeVariable typeVariable;
	//return the variable domain
	cDomainIntegerBasis * pDomainVariable = (cDomainIntegerBasis*)
		validDomains.getDomainForElement( typeVariable );
	const bool bStandardDomainVariable = ( pDomainVariable == NULL );
	if ( bStandardDomainVariable ){
		//use the standrad domain
		pDomainVariable = (cDomainIntegerBasis*)typeVariable.getStandardDomain();
	}
	
	//read the identifier number
	cDomainIntegerBasis * pDomainIdentifier = ((cDomainIntegerBasis*)(
		pDomainExtObject->getElementDomain( 1 ) ));
	
	//restore the identifier number
	lIdentifier = pDomainIdentifier->restoreIntegerValue( iBitStream, outStatus );
	if ( outStatus < 0 ){
		if ( bStandardDomainExtObject ){
			delete pDomainExtObject;
		}
		if ( bStandardDomainVariable ){
			delete pDomainVariable;
		}
		return;
	}
	
	//restore input values
	//restore the count of input values
	cDomainIntegerBasis * pDomainCountInVar = ((cDomainIntegerBasis*)(
		pDomainExtObject->getElementDomain( 2 ) ));
	
	const unsignedIntFib uiNumberOfInputValues =
		pDomainCountInVar->restoreIntegerValue( iBitStream, outStatus );
	if ( outStatus < 0 ){
		if ( bStandardDomainExtObject ){
			delete pDomainExtObject;
		}
		if ( bStandardDomainVariable ){
			delete pDomainVariable;
		}
		return;
	}
	//get domain for the input values
	cTypeExtObjectInput typeExtObjectInput( lIdentifier );
	//return the variable domain
	cDomain * pDomainInputValuesBase =
		validDomains.getDomainForElement( typeExtObjectInput );
	const bool bStandardInputValues = ( pDomainInputValuesBase == NULL );
	if ( bStandardInputValues ){
		//use the standrad domain
		pDomainInputValuesBase = typeVariable.getStandardDomain();
	}
	if ( ! pDomainInputValuesBase->isVector() ){
		//Error: input values domain is not a vector domain
		if ( bStandardDomainExtObject ){
			delete pDomainExtObject;
		}
		if ( bStandardInputValues ){
			delete pDomainInputValuesBase;
		}
		if ( bStandardDomainVariable ){
			delete pDomainVariable;
		}
		outStatus = -2;
		return;
	}
	if ( 0 < uiNumberOfInputValues ){
		//some input values exists -> load them
		cDomainVectorBasis * pDomainInputValues =
			(cDomainVectorBasis*)pDomainInputValuesBase;
		//restore the input values
		vecInputValues = cVectorExtObject( iBitStream, outStatus,
			liDefinedVariables, pDomainInputValues, pDomainVariable,
			uiNumberOfInputValues );
		
		vecInputValues.setDefiningFibElement( this, false );
		if ( outStatus < 0 ){
			if ( bStandardDomainExtObject ){
				delete pDomainExtObject;
			}
			if ( bStandardInputValues ){
				delete pDomainInputValuesBase;
			}
			if ( bStandardDomainVariable ){
				delete pDomainVariable;
			}
			outStatus = -2;
			return;
		}
	}

	//restore the subobjects of the external object element
	//restore the count of subobjects of the external object element
	cDomainIntegerBasis * pDomainCountSubObj = ((cDomainIntegerBasis*)(
		pDomainExtObject->getElementDomain( 3 ) ));
	
	const unsignedLongFib ulNumberOfSubObjects =
		pDomainCountSubObj->restoreIntegerValue( iBitStream, outStatus );
	if ( outStatus < 0 ){
		if ( bStandardDomainExtObject ){
			delete pDomainExtObject;
		}
		if ( bStandardInputValues ){
			delete pDomainInputValuesBase;
		}
		if ( bStandardDomainVariable ){
			delete pDomainVariable;
		}
		return;
	}
	if ( ( 0 < ulNumberOfSubObjects ) &&
			( pDomainExtObject->getNumberOfElements() < 4 ) ){
		/*error in domain (domain for the output variable count missing)
		-> can't load external object*/
		if ( bStandardDomainExtObject ){
			delete pDomainExtObject;
		}
		if ( bStandardInputValues ){
			delete pDomainInputValuesBase;
		}
		if ( bStandardDomainVariable ){
			delete pDomainVariable;
		}
		outStatus = -2;
		return;
	}
	
	cDomainIntegerBasis * pDomainCountOutVar = ((cDomainIntegerBasis*)(
		pDomainExtObject->getElementDomain( 4 ) ));
	
	const unsignedLongFib ulNumberOfFirstOutVar =
		(liDefinedVariables.size() + 1);
	//restore ulNumberOfSubObjects subobjects of the external object element
	for ( unsignedLongFib ulActualUnderobject = 1;
			ulActualUnderobject <= ulNumberOfSubObjects; ulActualUnderobject++ ){
		
		//restore the output variables
		const unsignedLongFib ulNumberOfOutVar =
			pDomainCountOutVar->restoreIntegerValue( iBitStream, outStatus );
		if ( outStatus < 0 ){
			if ( bStandardDomainExtObject ){
				delete pDomainExtObject;
			}
			if ( bStandardInputValues ){
				delete pDomainInputValuesBase;
			}
			if ( bStandardDomainVariable ){
				delete pDomainVariable;
			}
			return;
		}
		list< cFibVariable* > liDefinedVariablesCopy( liDefinedVariables );
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
		list< cFibVariable* > vecOutputVariables;
#else //FEATURE_C_EXT_OBJECT_USE_LIST
		vector< cFibVariable* > vecOutputVariables;
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
		
		for ( unsignedLongFib ulActualOutVar = 0; ulActualOutVar < ulNumberOfOutVar;
				ulActualOutVar++ ){
			
			cFibVariable * pOutVariable = new cFibVariable( this );
			pOutVariable->setIntegerValue( ulNumberOfFirstOutVar + ulActualOutVar );
			
			liDefinedVariablesCopy.push_front( pOutVariable );
			vecOutputVariables.push_back( pOutVariable );
		}
		
		//restore the subobject
		cFibElement * pSubobject = cFibElement::restoreInternal(
			iBitStream, outStatus, liDefinedVariablesCopy, validDomains, pNextRoot );
		
		//add the loaded subobject to the extern object
		fibUnderObjects.push_back( pSubobject );
		vecSubobjects.push_back( make_pair(
			pSubobject, vecOutputVariables ) );
		
		if ( pSubobject != NULL){
			pSubobject->pSuperiorElement = this;
		}else{//Warning: NULL subobject loaded
			outStatus = 2;
		}
		
		if ( outStatus < 0 ){
			//an error occured
			if ( bStandardDomainExtObject ){
				delete pDomainExtObject;
			}
			if ( bStandardInputValues ){
				delete pDomainInputValuesBase;
			}
			if ( bStandardDomainVariable ){
				delete pDomainVariable;
			}
			return;
		}
	}
	if ( bStandardDomainExtObject ){
		delete pDomainExtObject;
	}
	if ( bStandardInputValues ){
		delete pDomainInputValuesBase;
	}
	if ( bStandardDomainVariable ){
		delete pDomainVariable;
	}
	updateAllCounters();
	
	DEBUG_OUT_L1(<<"End restoring extern object"<<endl);
}


/**
 * destructor
 */
cExtObject::~cExtObject(){
	
	DEBUG_OUT_L2(<<"cExtObject(="<<this<<")::~cExtObject() started (number of input values "<<flush<<vecInputValues.size()<<")"<<endl<<flush);

	DEBUG_OUT_L3(<<"   cExtObject(="<<this<<")::~cExtObject() empty subobjects"<<endl<<flush);
	//delete the output variables
	while ( ! vecSubobjects.empty() ){
		
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
		list< cFibVariable * > & vecOutputVariables =
			vecSubobjects.back().second;
		for ( list< cFibVariable* >::iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
		vector< cFibVariable * > & vecOutputVariables =
			vecSubobjects.back().second;
		for ( vector< cFibVariable* >::iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
				itrVariable = vecOutputVariables.begin();
				itrVariable != vecOutputVariables.end(); itrVariable++ ){
			
			if ( (*itrVariable) != NULL ){
				delete (*itrVariable);
			}
		}
		vecSubobjects.pop_back();
	}
	DEBUG_OUT_L2(<<"cExtObject(="<<this<<")::~cExtObject() done"<<endl<<flush);
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
char cExtObject::getType() const{
	return 'o';
}


/**
 * This method checks, if this Fib-element is an valid Fib-element.
 *
 * @return true if this Fib-element is an valid Fib-element, else false
 */
bool cExtObject::isValidFibElement() const{
	
	if ( vecSubobjects.size() != fibUnderObjects.size() ){
		return false;
	}
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	list< pair< cFibElement * , list< cFibVariable * > > >::const_iterator
		itrSubObject = vecSubobjects.begin();
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	vector< pair< cFibElement * , vector< cFibVariable * > > >::const_iterator
		itrSubObject = vecSubobjects.begin();
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
	
	for ( list< cFibElement* >::const_iterator itrUnderObject = fibUnderObjects.begin();
			itrUnderObject != fibUnderObjects.end(); itrUnderObject++, itrSubObject++ ){
		
		if ( (*itrUnderObject) == NULL ){
			//incorrect subobject
			return false;
		}
		if ( (*itrUnderObject) != itrSubObject->first ){
			//wrong subobject
			return false;
		}
	}
	
	return true;
}


/**
 * This method checks if the given variable is used in the given
 * direction from this Fib-element.
 *
 * @see cFibVariable
 * @see isDefinedVariable()
 * @param pVariable a pointer to the variable to check if it is used
 * @param direction the direction from this Fib-element, in which the
 * 	variable should be used; standardvalue is ED_POSITION so yust
 * 	this Fib-element will be checked
 * @return true if the variable is used, else false
 */
bool cExtObject::isUsedVariable( const cFibVariable * pVariable,
		edDirection direction ) const{
	
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		//check input values
		if ( vecInputValues.isUsedVariable( pVariable ) ){
			//the variable is used in the input values vector
			return true;
		}
	}
	return cFibBranch::isUsedVariable( pVariable, direction );
}


/**
 * This method returns all variables used in the given direction from
 * this Fib-element.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @see isDefinedVariable()
 * @param direction the direction from this Fib-element, in which the
 * 	variable should be used; standardvalue is ED_POSITION so yust
 * 	this Fib-element will be checked
 * @return the set with all variables used in the given direction from
 * 	this Fib-element
 */
set< cFibVariable* > cExtObject::getUsedVariables( edDirection direction ){
	
	set< cFibVariable* > setUsedVariables;
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		//insert input values variables
		set<cFibVariable*> setUsedVariableThis = vecInputValues.getUsedVariables();
		
		setUsedVariables.insert( setUsedVariableThis.begin(),
			setUsedVariableThis.end() );
	}
	//erase NULL pointers
	setUsedVariables.erase( ((cFibVariable*)(NULL)) );
	
	set< cFibVariable* > setUsedVariableBranch =
		cFibBranch::getUsedVariables( direction );
	setUsedVariables.insert( setUsedVariableBranch.begin(),
		setUsedVariableBranch.end() );

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
 * @param pVariableNew the variable with which the variable pVariableOld
 * 	is to be replace
 * @return true if the variable pVariableOld is replaced with pVariableNew,
 * 	else false
 */
bool cExtObject::replaceVariable( cFibVariable * pVariableOld,
		cFibVariable * pVariableNew ){
	
	if ( (pVariableOld == NULL) || (pVariableNew == NULL) ){
		//can't replace
		return false;
	}
	//check input values vector
	vecInputValues.replaceVariable( pVariableOld, pVariableNew );
	
	return cFibBranch::replaceVariable( pVariableOld, pVariableNew );
}


/**
 * This method checks if the given variable is defined in the given
 * direction from this Fib-element.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @param pVariable the pVariable to check if it is defined
 * @param direction the direction from this Fib-element, in which the
 * 	pVariable should be defined; standardvalue is ED_POSITION so yust
 * 	this Fib-element will be checked
 * @param pCallingFibElement the Fib-Element which called this method
 * @return true if the pVariable is used, else false
 */
bool cExtObject::isDefinedVariableInternal(
		const cFibVariable * pVariable, edDirection direction,
		const cFibElement * pCallingFibElement ) const{
	
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		const bool bSearchAllOutVar = ( direction == ED_POSITION ) ||
			( direction == ED_BELOW_EQUAL ) || ( pCallingFibElement == NULL );
		
		//check the output pVariables this extern object element defines
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
		for ( list< pair< cFibElement * , list< cFibVariable * > > >::const_iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
		for ( vector< pair< cFibElement * , vector< cFibVariable * > > >::const_iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
				itrSubObject = vecSubobjects.begin();
				itrSubObject != vecSubobjects.end(); itrSubObject++ ){
			
			//beware subobject: output pVariables not all defined above of a subobject
			if ( bSearchAllOutVar || ( pCallingFibElement == (itrSubObject->first) ) ){
				//test output variables of subobject
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
				const list< cFibVariable * > & vecOutputVariables = itrSubObject->second;
				for ( list< cFibVariable * >::const_iterator itrOutputVariable = vecOutputVariables.begin();
#else //FEATURE_C_EXT_OBJECT_USE_LIST
				const vector< cFibVariable * > & vecOutputVariables = itrSubObject->second;
				for ( vector< cFibVariable * >::const_iterator itrOutputVariable = vecOutputVariables.begin();
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
						itrOutputVariable != vecOutputVariables.end(); itrOutputVariable++ ){
					
					if ( pVariable == (*itrOutputVariable) ){
						return true;
					}
				}
			}
		}//pVariable not defined here
	}
	
	return cFibBranch::isDefinedVariableInternal( pVariable, direction );
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
list< cFibVariable* > cExtObject::getDefinedVariablesInternal(
		edDirection direction,
		const cFibElement * pCallingFibElement ){
	
	list< cFibVariable* > liDefinedVariables;
	
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		const bool bSearchAllOutVar = ( direction == ED_POSITION ) ||
			( direction == ED_BELOW_EQUAL ) || ( pCallingFibElement == NULL );
		
		//get variables defined on this position
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
		for ( list< pair< cFibElement * , list< cFibVariable * > > >::iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
		for ( vector< pair< cFibElement * , vector< cFibVariable * > > >::iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
				itrSubObject = vecSubobjects.begin();
				itrSubObject != vecSubobjects.end(); itrSubObject++ ){
			
			//beware subobject: output variables not all defined above of a subobject
			if ( bSearchAllOutVar || ( pCallingFibElement == (itrSubObject->first) ) ){
				//insert the output variables this extern object element defines
				liDefinedVariables.insert( liDefinedVariables.end(),
					itrSubObject->second.begin(), itrSubObject->second.end() );
			}
		}
	}
	if ( (direction == ED_ALL) || ( direction == ED_BELOW ) ||
			(direction == ED_BELOW_EQUAL) ){
		//get defined variables below
		list< cFibVariable* > liVariablesDefinedBelow =
			cFibBranch::getDefinedVariablesInternal( ED_BELOW, pCallingFibElement );
		liDefinedVariables.insert( liDefinedVariables.end(),
			liVariablesDefinedBelow.begin(), liVariablesDefinedBelow.end() );
		
	}
	if ( ( direction == ED_ALL ) || ( direction == ED_HIGHER ) ||
			( direction == ED_HIGHER_EQUAL ) ){
		//get defined variables higher
		list< cFibVariable* > liVariablesDefinedHigher =
			cFibBranch::getDefinedVariablesInternal( ED_HIGHER, pCallingFibElement );
		liDefinedVariables.insert( liDefinedVariables.begin(),
			liVariablesDefinedHigher.begin(), liVariablesDefinedHigher.end() );
	}
	
	return liDefinedVariables;
}


/**
 * This method evaluades the Fib-object.
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
bool cExtObject::evalueObject( iEvaluePosition & evaluePosition,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties ) const{
	
	if ( objectPoint == 0 ){
#ifdef DEBUG_EVALUE
		const long lTmpIdentifier = lIdentifier;
		const unsigned int uiInputValues = vecInputValues.getNumberOfElements();
		printf( "cExtObject::evalueObject() with identifier %li and %u input values:", lTmpIdentifier, uiInputValues );
		
		for ( unsigned int uiActualInputValue = 1;
				uiActualInputValue <= uiInputValues; uiActualInputValue++ ){
			
			const double dValue = vecInputValues.getValue( uiActualInputValue );
			
			printf( " %lf;", dValue );
		}
		printf( "\n" );
#endif //DEBUG_EVALUE
		//get root element for identifier
		cExtObject * pThisObject = const_cast< cExtObject* >(this);
		
		cRoot * pExternalRootObject = pThisObject->
			getAccessibleRootObject( lIdentifier );
		
		if ( pExternalRootObject == NULL ){
#ifdef DEBUG_EVALUE
			printf( "cExtObject::evalueObject() with identifier %li external root object is NULL \n ", lTmpIdentifier);
#endif //DEBUG_EVALUE
			return false;
		}
		//set this cExtObject element as calling
		pExternalRootObject->setCallingFibElement( pThisObject );
		
		//evalue root-element
		const bool bExternObjectEvalued =
			pExternalRootObject->evalueObject( evaluePosition, objectPoint, liVecProperties );
		
		pExternalRootObject->unsetCallingFibElement();
		
#ifdef DEBUG_EVALUE
		const char * szEvalued = ( bExternObjectEvalued?"evalued":"not evalued");
		printf( "cExtObject::evalueObject() with identifier %li %s \n ", lTmpIdentifier, szEvalued );
#endif //DEBUG_EVALUE
		return bExternObjectEvalued;
	}//else evalue one subobject
	//TODO? did this make sense?
	
	//find the subobject to evalue
	unsignedIntFib uiRemainingObjectPoints = objectPoint;
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	for ( list< pair< cFibElement * , list< cFibVariable * > > >::const_iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	for ( vector< pair< cFibElement * , vector< cFibVariable * > > >::const_iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
			itrSubObject = vecSubobjects.begin();
			itrSubObject != vecSubobjects.end(); itrSubObject++ ){
		
		if ( (itrSubObject->first) != NULL ){
			
			const unsignedIntFib uiActualObjectPoints =
				itrSubObject->first->getNumberOfObjectPoints() + 1;
			
			if ( uiRemainingObjectPoints <= uiActualObjectPoints ){
				//subobject to evalue found
				//set its input values to 0
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
				const list< cFibVariable * > & vecOutputVariables =
					itrSubObject->second;
				for ( list< cFibVariable * >::const_iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
				const vector< cFibVariable * > & vecOutputVariables =
					itrSubObject->second;
				for ( vector< cFibVariable * >::const_iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
						itrOutputVariable = vecOutputVariables.begin();
						itrOutputVariable != vecOutputVariables.end(); itrOutputVariable++ ){
					
					(const_cast< cFibVariable * >(*itrOutputVariable))->setIntegerValue( 0 );
				}
				//evalue subobject
				return (itrSubObject->first)->evalueObject( evaluePosition,
					uiRemainingObjectPoints - 1, liVecProperties );
			}else{
				uiRemainingObjectPoints -= uiActualObjectPoints;
			}
		}
	}
	//no Fib-object to evalue
	return false;
}


/**
 * This method evaluades the Fib-object.
 * Evertime a Fib-elements, with a type of the given type chars in
 * liCFibElementTyps, is reached while evaluation, it is given
 * back with the properties which it has.
 * Ever pointelement is given back. The type chars for pointelements
 * don't need to be in the list liCFibElementTyps.
 *
 * @param evalueFibElement a reference to the object with the
 * 	evalueElement() method to evalue /store the Fib-elements and ther
 * 	properties; everytime a Fib-element (with one of the type given
 * 	in liCFibElementTyps) is reached in the evaluation, the method
 * 	evalueElement() of this objects is called with the Fib-element
 * 	and the properties of the Fib-element; @see iEvalueFibElement
 * @param objectPoint the object point in the order of true partobjects
 * 	to evalue
 * @param liVecProperties a list with the property vectors which should
 * 	be global for the evalued object
 * @param liCFibElementTyps a list with the type chars (@see getType() )
 * 	of the Fib-elements to return
 * @return if the evalueation was successfull true, else false
 */
bool cExtObject::evalueObject( iEvalueFibElement & evalueFibElement,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties,
		const list<char> & liCFibElementTyps ){
	
	//check if this Fib-element should be given back with evalueElement()
	for ( list<char>::const_iterator itrCType = liCFibElementTyps.begin();
			itrCType != liCFibElementTyps.end(); itrCType++ ){
		
		if ( (*itrCType) == getType() ){
			//call evalueElement() with this element
			return evalueFibElement.evalueElement( *this, liVecProperties );
		}
	}//else if this element shouldn't be returned

	if ( objectPoint == 0 ){
		//get root element for identifier
		cExtObject * pThisObject = const_cast< cExtObject* >(this);
		
		cRoot * pExternalRootObject = pThisObject->
			getAccessibleRootObject( lIdentifier );
		
		if ( pExternalRootObject == NULL ){
			return false;
		}
		//set this cExtObject element as calling
		pExternalRootObject->setCallingFibElement( pThisObject );
		
		//evalue root-element
		const bool bExternObjectEvalued =
			pExternalRootObject->evalueObject( evalueFibElement, objectPoint,
				liVecProperties, liCFibElementTyps );
		
		pExternalRootObject->unsetCallingFibElement();
		
		return bExternObjectEvalued;
	}//else evalue one subobject
	//TODO? did this make sense?
	
	//find the subobject to evalue
	unsignedIntFib uiRemainingObjectPoints = objectPoint;
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	for ( list< pair< cFibElement * , list< cFibVariable * > > >::const_iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	for ( vector< pair< cFibElement * , vector< cFibVariable * > > >::const_iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
			itrSubObject = vecSubobjects.begin();
			itrSubObject != vecSubobjects.end(); itrSubObject++ ){
		
		if ( (itrSubObject->first) != NULL ){
			
			const unsignedIntFib uiActualObjectPoints =
				itrSubObject->first->getNumberOfObjectPoints() + 1;
			
			if ( uiRemainingObjectPoints <= uiActualObjectPoints ){
				//subobject to evalue found
				//set its input values to 0
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
				const list< cFibVariable * > & vecOutputVariables =
					itrSubObject->second;
				for ( list< cFibVariable * >::const_iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
				const vector< cFibVariable * > & vecOutputVariables =
					itrSubObject->second;
				for ( vector< cFibVariable * >::const_iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
						itrOutputVariable = vecOutputVariables.begin();
						itrOutputVariable != vecOutputVariables.end(); itrOutputVariable++ ){
					
					(const_cast< cFibVariable * >(*itrOutputVariable))->setIntegerValue( 0 );
				}
				//evalue subobject
				return (itrSubObject->first)->evalueObject( evalueFibElement,
					uiRemainingObjectPoints - 1, liVecProperties, liCFibElementTyps );
			}else{
				uiRemainingObjectPoints -= uiActualObjectPoints;
			}
		}
	}
	//no Fib-object to evalue
	return false;
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
unsignedLongFib cExtObject::getTimeNeed( unsignedLongFib lMaxTime ) const{
	
	if ( (1 <= lMaxTime) && (lMaxTime <= 5) ){
		//max time is up with evaluing this extern object element
		return lMaxTime;
	}
	//evalue time for external object
	cExtObject * pThisObject = const_cast< cExtObject* >(this);
	
	//get root element for identifier
	cRoot * pExternalRootObject =
		pThisObject->getAccessibleRootObject( lIdentifier );
	
	if ( pExternalRootObject == NULL ){
		//no external object -> nothing to call
		return 5;
	}
	//set this cExtObject element as calling
	pExternalRootObject->setCallingFibElement( pThisObject );
	
	//decrease max time about the evalue time of this extern object element
	if ( lMaxTime != 0 ){
		lMaxTime -= 5;
	}
	//evalue root-element
	const unsignedLongFib lNeededTime =
		pExternalRootObject->getTimeNeed( lMaxTime );
	
	pExternalRootObject->unsetCallingFibElement();
	
	return lNeededTime + 5;
}


/**
 * This method evaluades the size of the Fib-object in bits in the
 * compressed file form.
 *
 * The optionalpart field of extern object elements will not be ignored.
 *
 * @see storeBit()
 * @return the size of the Fib-object in bits in the compressed form
 */
unsignedLongFib cExtObject::getCompressedSize() const{
	
	cDomains validDomains = getValidValueDomains();
	//get the domain for the extern object element
	cTypeExtObject typeExtObject;
	//return the extern object element domain
	cDomainVectorBasis * pDomainExtObject = (cDomainVectorBasis*)
		validDomains.getDomainForElement( typeExtObject );
	const bool bStandardDomainExtObject = (pDomainExtObject == NULL);
	if ( bStandardDomainExtObject ){
		//use the standrad domain
		pDomainExtObject = (cDomainVectorBasis*)typeExtObject.getStandardDomain();
	}
	//get the domain for the variables
	cTypeVariable typeVariable;
	//return the variable domain
	cDomainIntegerBasis * pDomainVariable = (cDomainIntegerBasis*)
		validDomains.getDomainForElement( typeVariable );
	const bool bStandardDomainVariable = (pDomainVariable == NULL);
	if ( bStandardDomainVariable ){
		//use the standrad domain
		pDomainVariable = (cDomainIntegerBasis*)typeVariable.getStandardDomain();
	}
	
	//add compressed size for identifier
	unsignedLongFib ulCompressedSize = 4;
	
	if ( 1 <= pDomainExtObject->getNumberOfElements() ){
		
		ulCompressedSize += ((cDomainSingle*)(pDomainExtObject->getElementDomain( 1 )))->
			getCompressedSizeForValue();
	}
	//add compressed size for input values (number + number * variable size)
	if ( 2 <= pDomainExtObject->getNumberOfElements() ){
		
		ulCompressedSize += ((cDomainSingle*)(pDomainExtObject->getElementDomain( 2 )))->
			getCompressedSizeForValue();

		ulCompressedSize += vecInputValues.getCompressedSize();
	}
	//add compressed size for number of subobjects
	if ( 3 <= pDomainExtObject->getNumberOfElements() ){
		
		ulCompressedSize += ((cDomainSingle*)(pDomainExtObject->getElementDomain( 3 )))->
			getCompressedSizeForValue();
	}
	
	//add compressed size for subobjects
	//add compressed size for output variable counter
	if ( 4 <= pDomainExtObject->getNumberOfElements() ){
		
		ulCompressedSize += vecSubobjects.size() *
			((cDomainSingle*)(pDomainExtObject->getElementDomain( 4 )))->getCompressedSizeForValue();
	}
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	for ( list< pair< cFibElement * , list< cFibVariable * > > >::const_iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	for ( vector< pair< cFibElement * , vector< cFibVariable * > > >::const_iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
			itrSubObject = vecSubobjects.begin();
			itrSubObject != vecSubobjects.end(); itrSubObject++ ){
		
		//add compressed size for subobject
		ulCompressedSize += itrSubObject->first->getCompressedSize();
	}//end for add compressed size for subobjects
	if ( bStandardDomainExtObject ){
		delete pDomainExtObject;
	}
	if ( bStandardDomainVariable ){
		delete pDomainVariable;
	}
	return ulCompressedSize;
}


/**
 * @return true if this Fib-element is movebel else false
 */
bool cExtObject::isMovable() const{
	//extern object element isn't moveble
	return false;
}


/**
 * This method copies the Fib-element on the specified position.
 * Variables which are not defined in the Fib-element but used
 * don't change ther reference.
 *
 * @see getType()
 * @param cType the type of the Fib-element to copy
 * @param elementPoint the number of the Fib-element, in the order of
 * 	Fib-elements of the given type cType, to copy
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib-object
 * @return the copy of the Fib-element
 */
cFibElement * cExtObject::copyElement( const char cType,
		const unsignedIntFib elementPoint, bool bAbsolute ) const{
	
	if ( elementPoint == 0 ){
		//copy this element
		return new cExtObject( *this );
	}//else get the fib element and copy it
	
	const cFibElement * pFibElementToCopy = getConstFibElement(
		cType, elementPoint, bAbsolute );
	
	if ( pFibElementToCopy ){
		return ( pFibElementToCopy->copyElement( 'u', 0 ) );
	}//else
	return NULL;
}


#ifdef FEATURE_EQUAL_FIB_OBJECT

/**
 * This method checks if the given Fib-object is equal to this Fib
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
bool cExtObject::equalInternal( const cFibElement & fibObject,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{

	if ( getType() != fibObject.getType() ){
		return false;
	}
	if ( ! equalElementInternal( fibObject, mapEqualRootObjects,
			mapEqualDefinedVariables, bCheckExternalObjects ) ){
		return false;
	}
	if ( bCheckExternalObjects ){
		//check same external object
		const cRoot * pExternalRootObject = const_cast< cExtObject * >(this)->
			getAccessibleRootObject( lIdentifier );
		
		const cRoot * pOtherExternalRootObject =
			((cExtObject*)(&fibObject))->getAccessibleRootObject( lIdentifier );
		
		if ( pExternalRootObject != pOtherExternalRootObject ){
			//not equal pointers
			
			if ( ( pExternalRootObject == NULL ) || ( pOtherExternalRootObject == NULL ) ){
				//one external object is NULL
				if ( ( pExternalRootObject != NULL ) || ( pOtherExternalRootObject != NULL ) ){
					//one not Null -> not the same external subobjects
					return false;
				}//else both external objects are NULL -> external objects are equal
			}else{//both external object exists
				const map< const cRoot *, const cRoot * >::const_iterator itrExternalObjects =
					mapEqualRootObjects.find( pExternalRootObject );
				
				if ( ( itrExternalObjects == mapEqualRootObjects.end() ) ||
						( itrExternalObjects->second != pOtherExternalRootObject )  ){
					//don't know if external objects are equal -> compare them
					if ( ! pExternalRootObject->equalInternal( * pOtherExternalRootObject,
							mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
						
						return false;
					}//external objects are equal
				}//external objects are equal}
			}
		}//else same pointers -> same subobject
		//if this point is reached -> external objects are equal
		mapEqualRootObjects.insert( make_pair(
			pExternalRootObject, pOtherExternalRootObject ) );
	}//end if check same external object
	mapEqualDefinedVariables.insert( make_pair( this, &fibObject ) );
	
	return cFibBranch::equalInternal( fibObject, mapEqualRootObjects,
		mapEqualDefinedVariables, bCheckExternalObjects );
}


/**
 * This method checks if the given Fib-element is equal to this Fib
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
bool cExtObject::equalElementInternal( const cFibElement & fibElement,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{

	if ( getType() != fibElement.getType() ){
		return false;
	}
	const cExtObject * pExtObjectElement = (const cExtObject*)(&fibElement);

	//compare identifiers
	if ( lIdentifier != pExtObjectElement->lIdentifier ){
		return false;
	}
	//compare input values vectors
	if ( ! vecInputValues.equalInternal( pExtObjectElement->vecInputValues,
			mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
		return false;
	}
	//compare number of subobjects
	if ( vecSubobjects.size() != pExtObjectElement->vecSubobjects.size() ){
		return false;
	}
	//compare output variables
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	list< pair< cFibElement * , list< cFibVariable * > > >::const_iterator
		itrSubObjectOther = pExtObjectElement->vecSubobjects.begin();
	for ( list< pair< cFibElement * , list< cFibVariable * > > >::const_iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	vector< pair< cFibElement * , vector< cFibVariable * > > >::const_iterator
		itrSubObjectOther = pExtObjectElement->vecSubobjects.begin();
	for ( vector< pair< cFibElement * , vector< cFibVariable * > > >::const_iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
			itrSubObject = vecSubobjects.begin();
			itrSubObject != vecSubobjects.end();
			itrSubObject++, itrSubObjectOther++ ){
		
		//compare output variables count
		if ( itrSubObject->second.size() != itrSubObjectOther->second.size() ){
			return false;
		}
	}//end for compare output variables
	
	return true;
}


/**
 * This method checks if the given Fib-element sets the variable to
 * the same values as this Fib-element.
 *
 * @param pVariableOwn a pointer to a defined variable in this Fib-element,
 * 	it is compared to the equivalent variable pVariable in the given
 * 	Fib-element fibElement
 * @param fibElement the Fib-element to which this Fib-element should be
 * 	compared
 * @param pVariable a pointer to a defined variable in the other
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
 * 	values as the Fib-element fibElement
 */
bool cExtObject::equalValuesSetInternal( const cFibVariable * pVariableOwn,
		const cFibElement & fibElement,
		const cFibVariable * pVariable,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{
	
	if ( pVariableOwn == pVariable ){
		//same defined variable -> same values set
		return true;
	}
	if ( getType() != fibElement.getType() ){
		//not the same element type
		return false;
	}
	
	//get subobjects which uses the variable
	cExtObject * pOtherExtObject = const_cast< cExtObject* >(
		((cExtObject*)(&fibElement)) );
	
	/*same external object + same variable position + same values set for
	input values (this means)-> same values set*/
	
	//check same variable position
	bool bVariableFound = false;
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	list< pair< cFibElement * , list< cFibVariable * > > >::const_iterator
		itrSubObject = vecSubobjects.begin();
	list< pair< cFibElement * , list< cFibVariable * > > >::const_iterator
		itrSubObjectOther = pOtherExtObject->vecSubobjects.begin();
	for ( ; ( itrSubObject != vecSubobjects.end() ) &&
				( itrSubObjectOther != pOtherExtObject->vecSubobjects.end() );
			itrSubObject++, itrSubObjectOther++ ){
		
		//check output variables
		const list< cFibVariable * > & vecOutputVariables = itrSubObject->second;
		const list< cFibVariable * > & vecOutputVariablesOther = itrSubObjectOther->second;
		
		list< cFibVariable * >::const_iterator itrOutputVariableOther =
			vecOutputVariablesOther.begin();
		for ( list< cFibVariable * >::const_iterator itrOutputVariable = vecOutputVariables.begin();
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	vector< pair< cFibElement * , vector< cFibVariable * > > >::const_iterator
		itrSubObject = vecSubobjects.begin();
	vector< pair< cFibElement * , vector< cFibVariable * > > >::const_iterator
		itrSubObjectOther = pOtherExtObject->vecSubobjects.begin();
	for ( ; ( itrSubObject != vecSubobjects.end() ) &&
				( itrSubObjectOther != pOtherExtObject->vecSubobjects.end() );
			itrSubObject++, itrSubObjectOther++ ){
		
		//check output variables
		const vector< cFibVariable * > & vecOutputVariables = itrSubObject->second;
		const vector< cFibVariable * > & vecOutputVariablesOther = itrSubObjectOther->second;
		
		vector< cFibVariable * >::const_iterator itrOutputVariableOther =
			vecOutputVariablesOther.begin();
		for ( vector< cFibVariable * >::const_iterator itrOutputVariable = vecOutputVariables.begin();
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
				( itrOutputVariable != vecOutputVariables.end() ) &&
					( itrOutputVariableOther != vecOutputVariablesOther.end() );
				itrOutputVariable++, itrOutputVariableOther++ ){
			
			if ( ( pVariableOwn == (*itrOutputVariable) ) ||
					( pVariable == (*itrOutputVariableOther) ) ){
				
				if ( ( pVariableOwn == (*itrOutputVariable) ) &&
						( pVariable == (*itrOutputVariableOther) ) ){
					//variables have same position in both external subobject elements
					bVariableFound = true;
					break;
				}else{//variables don't have same position in both external subobject elements
					return false;
				}
			}
		}
		if ( bVariableFound ){
			break;
		}
	}
	if ( ! bVariableFound ){
		//variable not found in one subobject -> not same position
		return false;
	}//the variable is defined in bouth elements on the same position
	const map< const cFibElement *, const cFibElement * >::const_iterator
		itrEqualDefinedVariable = mapEqualDefinedVariables.find( this );
	
	if ( ( itrEqualDefinedVariable != mapEqualDefinedVariables.end() ) &&
			( itrEqualDefinedVariable->second == &fibElement ) ){
		//Fib-elements compared befor
		return true;
	}//else compare Fib elements
	
	if ( bCheckExternalObjects ){
		//check same external object
		const cRoot * pExternalRootObject = const_cast< cExtObject * >(this)->
			getAccessibleRootObject( lIdentifier );
		
		const cRoot * pOtherExternalRootObject =
			pOtherExtObject->getAccessibleRootObject( lIdentifier );
		
		if ( pExternalRootObject != pOtherExternalRootObject ){
			//not equal pointers
			if ( ( pExternalRootObject == NULL ) || ( pOtherExternalRootObject == NULL ) ){
				//one external object is NULL
				if ( ( pExternalRootObject != NULL ) || ( pOtherExternalRootObject != NULL ) ){
					//one not NULL -> not the same external subobjects
					return false;
				}//else both external objects are NULL -> external objects are equal
				
			}else{//both external object exists
				const map< const cRoot *, const cRoot * >::const_iterator itrExternalObjects =
					mapEqualRootObjects.find( pExternalRootObject );
				
				if ( ( itrExternalObjects == mapEqualRootObjects.end() ) ||
						( itrExternalObjects->second != pOtherExternalRootObject )  ){
					//don't know if external objects are equal -> compare them
					if ( ! pExternalRootObject->equalInternal( * pOtherExternalRootObject,
							mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
						
						return false;
					}//external objects are equal
				}//else{ external objects are equal}
			}
		}//else same pointers -> external objects are equal
		//if this point is reached -> external objects are equal
		mapEqualRootObjects.insert( make_pair(
			pExternalRootObject, pOtherExternalRootObject ) );
	}else{//don't check external objects just compare identifiers
		if ( lIdentifier != pOtherExtObject->lIdentifier ){
			return false;
		}
	}
	
	/*subobjects are equal: variables are equal set, if input
	values are equal set*/
	if ( ! vecInputValues.equalInternal( pOtherExtObject->vecInputValues,
			mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
		
		return false;
	}
	
	
	
/*TODO weg? chanell variables trought external objects

	//set this cExtObject element as calling
	pExternalRootObject->setCallingFibElement( this );
	pOtherExternalRootObject->setCallingFibElement( this );
	
	//TODO equal value set
	bool bEqualvalueSet = true;
	//get external subobjects of both which uses the variable
	
	//get correspondending input values pairs
	
	//check for each variable pair if equal value set
	
	pExternalRootObject->unsetCallingFibElement();
	pOtherExternalRootObject->unsetCallingFibElement();
*/
	
	mapEqualDefinedVariables.insert( make_pair( this, &fibElement ) );
	
	//the input pVariables on the same position are set to the same values
	return true;
}


#else //FEATURE_EQUAL_FIB_OBJECT

/**
 * This method checks if the given Fib-object is equal to this Fib
 * -object.
 * Variables can be others, but must be defined and used in equivalent
 * Fib-elements.
 *
 * @param fibObject the Fib-object to which this Fib-object should be
 * 	equal
 * @return true if this Fib-object is equal to the given Fib-object,
 * 	else false
 */
bool cExtObject::equal( const cFibElement & fibObject ) const{

	if ( getType() != fibObject.getType() ){
		return false;
	}
	if ( ! equalElement( fibObject ) ){
		return false;
	}
	//check same external object
	const cRoot * pExternalRootObject = const_cast< cExtObject * >(this)->
		getAccessibleRootObject( lIdentifier );
	
	const cRoot * pOtherExternalRootObject =
		((cExtObject*)(&fibObject))->getAccessibleRootObject( lIdentifier );
	
	if ( ( pExternalRootObject == NULL ) || ( pOtherExternalRootObject == NULL ) ){
		//one external object is NULL
		if ( ( pExternalRootObject != NULL ) || ( pOtherExternalRootObject != NULL ) ){
			//one not Null -> not the same external subobjects
			return false;
		}
	}else{//both external object exists
		if ( ! pExternalRootObject->equal( * pOtherExternalRootObject ) ){
			
			return false;
		}
	}
	return cFibBranch::equal( fibObject );
}


/**
 * This method checks if the given Fib-element is equal to this Fib
 * -element.
 * The subobjects arn't compared, not even ther count is compared.
 * Used variables can be others.
 *
 * @param fibElement the Fib-element to which this Fib-element should be
 * 	equal
 * @return true if this Fib-element is equal to the given Fib-object,
 * 	else false
 */
bool cExtObject::equalElement( const cFibElement & fibElement ) const{

	if ( getType() != fibElement.getType() ){
		return false;
	}
	const cExtObject * pExtObjectElement = (const cExtObject*)(&fibElement);

	//compare identifiers
	if ( lIdentifier != pExtObjectElement->lIdentifier ){
		return false;
	}
	
	//compare input values vectors
	if ( vecInputValues != pExtObjectElement->vecInputValues ){
		return false;
	}
	//compare number of subobjects
	if ( vecSubobjects.size() != pExtObjectElement->vecSubobjects.size() ){
		return false;
	}
	//compare output variables
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	list< pair< cFibElement * , list< cFibVariable * > > >::const_iterator
		itrSubObjectOther = pExtObjectElement->vecSubobjects.begin();
	for ( list< pair< cFibElement * , list< cFibVariable * > > >::const_iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	vector< pair< cFibElement * , vector< cFibVariable * > > >::const_iterator
		itrSubObjectOther = pExtObjectElement->vecSubobjects.begin();
	for ( vector< pair< cFibElement * , vector< cFibVariable * > > >::const_iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
			itrSubObject = vecSubobjects.begin();
			itrSubObject != vecSubobjects.end();
			itrSubObject++, itrSubObjectOther++ ){
		
		//compare output variables count
		if ( itrSubObject->second.size() != itrSubObjectOther->second.size() ){
			return false;
		}
	}//end for compare output variables
	
	return true;
}


/**
 * This method checks if the given Fib-element sets the variable to
 * the same values as this Fib-element.
 *
 * @param pVariableOwn a pointer to a defined variable in this Fib-element,
 * 	it is compared to the equivalent variable pVariable in the given
 * 	Fib-element fibElement
 * @param fibElement the Fib-element to which this Fib-element should be
 * 	compared
 * @param pVariable a pointer to a defined variable in the other
 * 	Fib-element fibElement
 * @return true if this Fib-element sets the variable to the same
 * 	values as the Fib-element fibElement
 */
bool cExtObject::equalValuesSet( const cFibVariable * pVariableOwn,
		const cFibElement & fibElement,
		const cFibVariable * pVariable ) const{
	
	if ( getType() != fibElement.getType() ){
		//not the same element type
		return false;
	}
	
	//get subobjects which uses the variable
	cExtObject * pOtherExtObject = const_cast< cExtObject* >(
		((cExtObject*)(&fibElement)) );
	
	/*same external object + same variable position + same values set for
	input values (this means)-> same values set*/
	
	//check same variable position
	bool bVariableFound = false;
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	list< pair< cFibElement * , list< cFibVariable * > > >::const_iterator
		itrSubObject = vecSubobjects.begin();
	list< pair< cFibElement * , list< cFibVariable * > > >::const_iterator
		itrSubObjectOther = pOtherExtObject->vecSubobjects.begin();
	for ( ; ( itrSubObject != vecSubobjects.end() ) &&
				( itrSubObjectOther != pOtherExtObject->vecSubobjects.end() );
			itrSubObject++, itrSubObjectOther++ ){
		
		//check output variables
		const list< cFibVariable * > & vecOutputVariables = itrSubObject->second;
		const list< cFibVariable * > & vecOutputVariablesOther = itrSubObjectOther->second;
		
		list< cFibVariable * >::const_iterator itrOutputVariableOther =
			vecOutputVariablesOther.begin();
		for ( list< cFibVariable * >::const_iterator itrOutputVariable = vecOutputVariables.begin();
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	vector< pair< cFibElement * , vector< cFibVariable * > > >::const_iterator
		itrSubObject = vecSubobjects.begin();
	vector< pair< cFibElement * , vector< cFibVariable * > > >::const_iterator
		itrSubObjectOther = pOtherExtObject->vecSubobjects.begin();
	for ( ; ( itrSubObject != vecSubobjects.end() ) &&
				( itrSubObjectOther != pOtherExtObject->vecSubobjects.end() );
			itrSubObject++, itrSubObjectOther++ ){
		
		//check output variables
		const vector< cFibVariable * > & vecOutputVariables = itrSubObject->second;
		const vector< cFibVariable * > & vecOutputVariablesOther = itrSubObjectOther->second;
		
		vector< cFibVariable * >::const_iterator itrOutputVariableOther =
			vecOutputVariablesOther.begin();
		for ( vector< cFibVariable * >::const_iterator itrOutputVariable = vecOutputVariables.begin();
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
				( itrOutputVariable != vecOutputVariables.end() ) &&
					( itrOutputVariableOther != vecOutputVariablesOther.end() );
				itrOutputVariable++, itrOutputVariableOther++ ){
			
			if ( ( pVariableOwn == (*itrOutputVariable) ) ||
					( pVariable == (*itrOutputVariableOther) ) ){
				
				if ( ( pVariableOwn == (*itrOutputVariable) ) &&
						( pVariable == (*itrOutputVariableOther) ) ){
					//variables have same position in both external subobject elements
					bVariableFound = true;
					break;
				}else{//variables don't have same position in both external subobject elements
					return false;
				}
			}
		}
		if ( bVariableFound ){
			break;
		}
	}
	if ( ! bVariableFound ){
		//variable not found in one subobject -> not same position
		return false;
	}
	
	//check same external object
	const cRoot * pExternalRootObject = const_cast< cExtObject * >(this)->
		getAccessibleRootObject( lIdentifier );
	
	const cRoot * pOtherExternalRootObject =
		pOtherExtObject->getAccessibleRootObject( lIdentifier );
	
	if ( ( pExternalRootObject == NULL ) || ( pOtherExternalRootObject == NULL ) ){
		if ( ( pExternalRootObject == NULL ) && ( pOtherExternalRootObject == NULL ) ){
			//no external subobjects used -> variables are set equal to 0
			return true;
		}//else not the same external subobjects
		return false;
	}
	
	if ( ! pExternalRootObject->equal( * pOtherExternalRootObject ) ){
		
		return false;
	}/*else if subobjects are equal: variables are equal set, if input
	variables are equal set*/
	if ( vecInputValues = pOtherExtObject->vecInputValues ){
		
		return false;
	}
	
	
	
/*TODO weg? chanell variables trought external objects

	//set this cExtObject element as calling
	pExternalRootObject->setCallingFibElement( this );
	pOtherExternalRootObject->setCallingFibElement( this );
	
	//TODO equal value set
	bool bEqualvalueSet = true;
	//get external subobjects of both which uses the variable
	
	//get correspondending input values pairs
	
	//check for each variable pair if equal value set
	
	pExternalRootObject->unsetCallingFibElement();
	pOtherExternalRootObject->unsetCallingFibElement();
*/
	
	
	//the input pVariables on the same position are set to the same values
	return true;
}

#endif //FEATURE_EQUAL_FIB_OBJECT


/**
 * This method stores this Fib-object in the XML-format into the
 * given stream.
 *
 * @param stream the stream where this Fib-object should be stored to
 * @return true if this Fib-object is stored, else false
 */
bool cExtObject::storeXml( ostream & stream ) const{

	bool bReturnValue = true;
	
#ifdef FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	stream<<"<obj elementNr=\""<<getNumberOfElement()<<"\" "<<
		"identifier=\""<<lIdentifier<<"\">"<<endl;
#else //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	stream<<"<obj identifier=\""<<lIdentifier<<"\">"<<endl;
#endif //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	//write input values vector
	vecInputValues.storeXml( stream );
	
	//write the subobjects
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	for ( list< pair< cFibElement * , list< cFibVariable * > > >::const_iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	for ( vector< pair< cFibElement * , vector< cFibVariable * > > >::const_iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
			itrSubObject = vecSubobjects.begin();
			itrSubObject != vecSubobjects.end(); itrSubObject++ ){
		
		if ( itrSubObject->first == NULL ){
			//error: no subobject to write
			bReturnValue = false;
			continue;
		}
		
		stream<<"<subobject>"<<endl;
		//write output variables
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
		const list< cFibVariable * > & vecOutputVariables = itrSubObject->second;
#else //FEATURE_C_EXT_OBJECT_USE_LIST
		const vector< cFibVariable * > & vecOutputVariables = itrSubObject->second;
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
		if ( vecOutputVariables.empty() ){
			//no input values
			stream<<"<output_variables/>"<<endl;
		}else{//write input variable elements
			stream<<"<output_variables>"<<endl;
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
			for ( list< cFibVariable * >::const_iterator itrOutputVariable = vecOutputVariables.begin();
#else //FEATURE_C_EXT_OBJECT_USE_LIST
			for ( vector< cFibVariable * >::const_iterator itrOutputVariable = vecOutputVariables.begin();
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
					itrOutputVariable != vecOutputVariables.end(); itrOutputVariable++ ){
				
				if ( *itrOutputVariable ){
					stream<<"<variable>"<<(*itrOutputVariable)->getValue()<<
						"</variable>"<<endl;
				}else{//error: no output variable to write
					bReturnValue = false;
				}
			}
			stream<<"</output_variables>"<<endl;
		}
		if ( itrSubObject->first ){
			bReturnValue &= itrSubObject->first->storeXml( stream );
		}
		stream<<"</subobject>"<<endl;
	}

	stream<<"</obj>"<<endl;

	return bReturnValue;
}


/**
 * This method inserts the given Fib-element fibElement on the
 * specified position. The replaced Fib-element will be the subobject
 * of the inserted Fib-element fibElement.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see getType()
 * @param cType the type of the Fib-element insted of which the given
 * 	Fib-element fibElement should be inserted
 * @param elementPoint the number of the Fib-element, in the order of
 * 	Fib-elements of the given type cType, in which position the given
 * 	Fib-element fibElement should be inserted; if 0 the given
 * 	fibElement will be inserted under this Fib-element
 * @param fibElement the Fib-element to insert
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib-object
 * @param bCheckVariables if true (standardvalue) it will be checked if
 * 	the variables the Fib-element defines are needed, else the 
 * 	Fib-element will be removed even if its variables are needed elsewher
 * @return true if the Fib-element fibElement was inserted, else false
 */
bool cExtObject::insertElement( cFibElement *fibElement, const char cType,
		const unsignedIntFib elementPoint, bool bAbsolute,
		bool bCheckVariables ){
		
	DEBUG_OUT_L2(<<"cExtObject::insertElement( fibElement="<<fibElement<<", elementPoint="<<elementPoint<<", bAbsolute="<<bAbsolute<<", bCheckVariables="<<bCheckVariables<<" ) started"<<endl<<flush);
	
	const bool bObjectChanged = cFibBranch::insertElement(
		fibElement, cType, elementPoint, bAbsolute, bCheckVariables );
	
	if ( bObjectChanged ){
		DEBUG_OUT_L4(<<"cExtObject::insertElement( fibElement="<<fibElement<<", elementPoint="<<elementPoint<<", bAbsolute="<<bAbsolute<<", bCheckVariables="<<bCheckVariables<<" ) -> syncSubobjects()"<<endl<<flush);
		syncSubobjects();
	}
	DEBUG_OUT_L2(<<"cExtObject::insertElement( fibElement="<<fibElement<<", elementPoint="<<elementPoint<<", bAbsolute="<<bAbsolute<<", bCheckVariables="<<bCheckVariables<<" ) done with result "<<(bObjectChanged?"true":"false")<<""<<endl<<flush);
	return bObjectChanged;
}


/**
 * This method inserts the given Fib-object pFibObject on the
 * specified position. In limb elements on the specified position a
 * list element will be inserted, with the old Fib-object and the
 * given Fib-object pFibObject as its subobjects.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see overwriteObjectWithObject()
 * @see getType()
 * @param cType the type of the Fib-element, on which position the
 * 	given Fib-object pFibObject should be inserted
 * @param elementPoint the number of the Fib-element, in the order of
 * 	Fib-elements of the given type cType, on which position the given
 * 	Fib-object pFibObject should be inserted
 * @param pFibObject the Fib-object to insert
 * @param first if true, the inserted object will be the first
 * 	subobject of the new list element
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib-object
 * @return true if the Fib-object pFibObject was inserted, else false
 */
bool cExtObject::insertObjectInElement( cFibElement * pFibObject, const char cType,
		const unsignedIntFib elementPoint, bool first,
		bool bAbsolute ){
	
	DEBUG_OUT_L2(<<"cExtObject::insertObjectInElement( pFibObject="<<pFibObject<<", cType="<<cType<<", elementPoint="<<elementPoint<<", first="<<first<<", bAbsolute="<<bAbsolute<<" ) started"<<endl<<flush);
	
	if ( pFibObject == NULL ){
		//nothing to insert
		return false;
	}
	if ( pFibObject->getType() == 'r' ){
		//can't insert a root-element
		return false;
	}
	if ( ! cFibObjectCounts::isValidType( cType ) ){
		return false;
	}

	if ( elementPoint == 0 ){
		//insert for the (first) subobject of this Fib-element
		DEBUG_OUT_L2(<<"   insert for the (first) subobject of this Fib-element; number of underobjects "<<fibUnderObjects.size()<<endl<<flush);

		if ( fibUnderObjects.empty() ){
			//insert in this branchelement
			fibUnderObjects.push_back( pFibObject );
			if ( pFibObject->pSuperiorElement != NULL ){
				pFibObject->pSuperiorElement->cutConnectionsTo(
					pFibObject );
			}
			pFibObject->pSuperiorElement = this;
			
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
			vecSubobjects.push_back( pair< cFibElement * , list< cFibVariable * > >(
				pFibObject, list< cFibVariable * >() ) );
#else //FEATURE_C_EXT_OBJECT_USE_LIST
			vecSubobjects.push_back( pair< cFibElement * , vector< cFibVariable * > >(
				pFibObject, vector< cFibVariable * >() ) );
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
			
			cFibObjectCounts pFibObjectCountsDelta = evalueCountersForObject( pFibObject );
			pFibObjectCountsDelta.uiNumberOfObjectpoints++;
			updateAllCounters( pFibObjectCountsDelta );
			//done with inserting
			return true;
		}else{
			//check if the subobject to overwrite is NULL
			DEBUG_OUT_L2(<<"   check if the subobject to overwrite is NULL"<<endl<<flush);
			list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
			list< pair< cFibElement * , list< cFibVariable * > > >::iterator
				itrActualSubObject = vecSubobjects.begin();
#else //FEATURE_C_EXT_OBJECT_USE_LIST
			vector< pair< cFibElement * , vector< cFibVariable * > > >::iterator
				itrActualSubObject = vecSubobjects.begin();
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
			
			if ( ( ! first ) && ( 1 < fibUnderObjects.size() ) ){
				actualUnderObject++;
				itrActualSubObject++;
			}
			if ( (*actualUnderObject) == NULL ){
				//overwrite the actualUnderObject NULL object
				
				//set the values of the pFibObject
				if ( pFibObject->pSuperiorElement != NULL ){
					pFibObject->pSuperiorElement->cutConnectionsTo(
						pFibObject );
				}
				pFibObject->pSuperiorElement = this;
				(*actualUnderObject) = pFibObject;
				
				if ( itrActualSubObject->first == NULL ){
					itrActualSubObject->first = pFibObject;
				}else{//Error: should not happen, because in both lists are the same subobjects
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
					vecSubobjects.insert( itrActualSubObject,
						pair< cFibElement * , list< cFibVariable * > >(
							pFibObject, list< cFibVariable * >() ) );
#else //FEATURE_C_EXT_OBJECT_USE_LIST
					vecSubobjects.insert( itrActualSubObject,
						pair< cFibElement * , vector< cFibVariable * > >(
							pFibObject, vector< cFibVariable * >() ) );
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
				}
				
				updateAllCounters( evalueCountersForObject( pFibObject ) );
				//done with inserting
				return true;
			}
		}
		return insertObjectInElement( pFibObject, 'u', 2, first );
	}
	
	if ( bAbsolute ){
		return getMasterRoot()->insertObjectInElement(
			pFibObject, cType, elementPoint, first );
	}//else elementPoint is an relative value

	/*check ( if (cType=='u') ) if the pFibObject should inserted as an
	neibour of an subobject of this object*/
	cFibElement *pFibElementPosition = getFibElement( cType, elementPoint );
	if ( (pFibElementPosition == NULL) || (pFibElementPosition->getType() == 'r') ){
		//no position to insert
		return false;
	}
	if ( cType == 'u' ){
		
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
		list< pair< cFibElement * , list< cFibVariable * > > >::iterator
			itrActualSubObject = vecSubobjects.begin();
#else //FEATURE_C_EXT_OBJECT_USE_LIST
		vector< pair< cFibElement * , vector< cFibVariable * > > >::iterator
			itrActualSubObject = vecSubobjects.begin();
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
		for ( list< cFibElement* >::iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end();
				actualUnderObject++, itrActualSubObject++ ){
			
			if ( (*actualUnderObject) == pFibElementPosition ){
				//insert the given pFibObject
				
				//set the values of the pFibObject
				if ( pFibObject->pSuperiorElement != NULL ){
					pFibObject->pSuperiorElement->cutConnectionsTo(
						pFibObject );
				}
				pFibObject->pSuperiorElement = this;
				
				if ( ! first ){
					//insert pFibObject after the actualUnderObject
					actualUnderObject++;
					itrActualSubObject++;
				}//else insert pFibObject instead of the actualUnderObject
				fibUnderObjects.insert( actualUnderObject, pFibObject );
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
				vecSubobjects.insert( itrActualSubObject,
					pair< cFibElement * , list< cFibVariable * > >(
						pFibObject, list< cFibVariable * >() ) );
#else //FEATURE_C_EXT_OBJECT_USE_LIST
				vecSubobjects.insert( itrActualSubObject,
					pair< cFibElement * , vector< cFibVariable * > >(
						pFibObject, vector< cFibVariable * >() ) );
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
						
				cFibObjectCounts pFibObjectCountsDelta = evalueCountersForObject( pFibObject );
				pFibObjectCountsDelta.uiNumberOfObjectpoints++;
				updateAllCounters( pFibObjectCountsDelta );
				//done and fibElement inserted
				return true;
			}//end if (actualUnderObject == pFibElementPosition )
		}//end for
	}
	/*get the pSuperiorElement of the to insering objectposition and call
	insertElement of theas*/
	if ( pFibElementPosition->pSuperiorElement != NULL ){
			
			return pFibElementPosition->pSuperiorElement->insertObjectInElement(
				pFibObject, 'u',
				(pFibElementPosition->getNumberOfElement()) + 1 -
				(pFibElementPosition->pSuperiorElement->getNumberOfElement() ),
				first );
			
	}//else the to insert position dosn't exists or is the topmost
	return false;
}


/**
 * This method overwrites the Fib-object on specified position with
 * the given Fib-object pFibObject. The Fib-object on specified
 * position will be replaced with the given Fib-object pFibObject.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see insertObjectInElement()
 * @see getType()
 * @param cType the type of the Fib-element, on which position the 
 * 	given Fib-object pFibObject should be inserted
 * @param elementPoint the number of the Fib-element, in the order of
 * 	Fib-elements of the given type cType, on which position the given
 * 	Fib-object pFibObject should be inserted
 * @param pFibObject the Fib-object to insert
 * @param bDeleteOld if true, delete the old Fib-object from the memory
 * @param bAbsolute if the elementPoint is an absolute value for the wool
 * 	Fib-object
 * @return true if the old Fib-object was overwritten and the given 
 * 	Fib-object pFibObject was inserted, else false
 */
bool cExtObject::overwriteObjectWithObject( cFibElement * pFibObject, const char cType,
		const unsignedIntFib elementPoint, bool bDeleteOld,
		bool bAbsolute ){
	
	DEBUG_OUT_L2(<<"cExtObject::overwriteObjectWithObject( pFibObject="<<pFibObject<<", cType="<<cType<<", elementPoint="<<elementPoint<<", bDeleteOld="<<(bDeleteOld?"true":"false")<<", bAbsolute="<<bAbsolute<<" ) started"<<endl<<flush);
	
	if ( pFibObject == NULL ){
		//nothing to insert
		return false;
	}
	if ( pFibObject->getType() == 'r' ){
		//can't insert a root-element
		return false;
	}
	if ( ! cFibObjectCounts::isValidType( cType ) ){
		return false;
	}

	if ( elementPoint == 0 ){
		if ( fibUnderObjects.empty() ){
			//nothing to overwrite
			return false;
		}
		//insert for the (first) underobject of this Fib-element
		
		//check if the underobject to overwrite is NULL
		if ( fibUnderObjects.front() == NULL ){
			//overwrite the actualUnderObject NULL object
			
			//set the values of the pFibObject
			if ( pFibObject->pSuperiorElement != NULL ){
				pFibObject->pSuperiorElement->cutConnectionsTo(
					pFibObject );
			}
			pFibObject->pSuperiorElement = this;
		
			fibUnderObjects.front() = pFibObject;
			vecSubobjects.front().first = pFibObject;

			cFibObjectCounts pFibObjectCountsDelta = evalueCountersForObject( pFibObject );
			pFibObjectCountsDelta.uiNumberOfObjectpoints++;
			updateAllCounters( pFibObjectCountsDelta );
			//done with inserting
			return true;
		}
		return overwriteObjectWithObject( pFibObject, 'u', 2, bDeleteOld );
	}
	if ( bAbsolute ){
		return getMasterRoot()->overwriteObjectWithObject( pFibObject, cType,
			elementPoint, bDeleteOld );
	}//else elementPoint is an relative value

	/*check ( if (cType=='u') ) if the pFibObject should inserted as an
	neibour of an underobject of this object*/
	cFibElement * pFibElementPosition = getFibElement( cType, elementPoint );
	if ( (pFibElementPosition == NULL) || (pFibElementPosition->getType() == 'r') ){
		//no Fib-object to overwrite
		return false;
	}
	if ( cType == 'u' ){
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
		list< pair< cFibElement * , list< cFibVariable * > > >::iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
		vector< pair< cFibElement * , vector< cFibVariable * > > >::iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
			itrActualSubbject = vecSubobjects.begin();
		for ( list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++, itrActualSubbject++ ){
			if ( (*actualUnderObject) == pFibElementPosition ){
				//insert the given pFibObject
				
				//set the values of the pFibObject
				if ( pFibObject->pSuperiorElement != NULL ){
					pFibObject->pSuperiorElement->cutConnectionsTo(
						pFibObject );
				}
				pFibObject->pSuperiorElement = this;
				//insert pFibObject instead of the actualUnderObject
				(*actualUnderObject) = pFibObject;
				itrActualSubbject->first = pFibObject;
				
				//update the Fib-objectcounters
				cFibObjectCounts pFibObjectCountsDelta = evalueCountersForObject( pFibObject );
				const cFibObjectCounts pFibObjectCountsOld =
					evalueCountersForObject( pFibElementPosition );
				pFibObjectCountsDelta -= pFibObjectCountsOld;
				updateAllCounters( pFibObjectCountsDelta );
				
				//remove old underobject
				if ( pFibElementPosition->pSuperiorElement == this ){
					pFibElementPosition->pSuperiorElement = NULL;
					if ( bDeleteOld ){
						DEBUG_OUT_L3(<<"cExtObject::overwriteObjectWithObject() deleting pFibElementPosition"<<endl<<flush);
						pFibElementPosition->deleteObject();
					}//else don't delete
				}
				//done and pFibObject inserted
				DEBUG_OUT_L3(<<"cExtObject::overwriteObjectWithObject() done pFibObject inserted"<<endl<<flush);
				return true;
			}
		}//end for
	}
	
	/*get the pSuperiorElement of the to insering objectposition and call
	insertElement of theas*/
	if ( pFibElementPosition->pSuperiorElement != NULL ){
			
			DEBUG_OUT_L2(<<"cExtObject::overwriteObjectWithObject() done calling overwriteObjectWithObject() on pFibElementPosition->pSuperiorElement"<<endl<<flush);
			return pFibElementPosition->pSuperiorElement->overwriteObjectWithObject(
				pFibObject, 'u', (pFibElementPosition->getNumberOfElement()) + 1 -
				(pFibElementPosition->pSuperiorElement->getNumberOfElement() ),
				bDeleteOld );
			
	}//else the to insert position dosn't exists or is the topmost
	return false;
}



/**
 * This method cuts the Fib-element on the specified position.
 * This works like removeElement(), except that the removed element is 
 * returned.
 *
 * @see isDeletableElement()
 * @see removeElement()
 * @see getType()
 * @param cType the type of the Fib-element to cut
 * @param elementPoint the number of the Fib-element, in the order of
 * 	Fib-elements of the given type cType, to cut
 * @param bAbsolute if the elementPoint is an absolute value for the wool
 * 	Fib-object
 * @param bCheckVariables if true (standardvalue) it will be checked if
 * 	the variables the Fib-element defines are needed, else the 
 * 	Fib-element will be removed even if its variables are needed elsewher
 * @return the pointer to the cuted Fib-element or NULL, if the Fib
 * 	-element couldn't cut
 */
cFibElement * cExtObject::cutElement( const char cType, const unsignedIntFib
		elementPoint, bool bAbsolute, bool bCheckVariables ){
	
	DEBUG_OUT_L2(<<"cExtObject::cutElement( cType="<<cType<<", elementPoint="<<elementPoint<<", bAbsolute="<<bAbsolute<<", bCheckVariables="<<(bCheckVariables?"true":"false")<<" ) started"<<endl<<flush);
	
	cFibElement * pCutedElement =
		cFibBranch::cutElement( cType, elementPoint, bAbsolute, bCheckVariables );
	
	if ( pCutedElement ){
		DEBUG_OUT_L4(<<"cExtObject::cutElement( cType="<<cType<<", elementPoint="<<elementPoint<<", bAbsolute="<<bAbsolute<<", bCheckVariables="<<(bCheckVariables?"true":"false")<<" ) syncSubobjects()"<<endl<<flush);
		syncSubobjects();
	}
	DEBUG_OUT_L2(<<"cExtObject::cutElement( cType="<<cType<<", elementPoint="<<elementPoint<<", bAbsolute="<<bAbsolute<<", bCheckVariables="<<(bCheckVariables?"true":"false")<<" ) done with result "<<pCutedElement<<" )"<<endl<<flush);
	return pCutedElement;
}


/**
 * This method moves a Fib-limb -element (cFibLimb) on the specified
 * position over iHowfar Fib-elements.
 * Moving is stoped if an invalid Fib-object would result (e.g. no Fib
 * -element can be moved over an Fib-elements that defines a variable
 * the moved Fib-element uses).
 * Moving an Fib-element into an list element will result in an
 * list element with the moved element in everyone of it's subobjects.
 *
 * @see isDeletableElement()
 * @see removeElement()
 * @see getType()
 * @param cType the type of the Fib-element to move
 * @param elementPoint the number of the Fib-element, in the order of
 * 	Fib-elements of the given type cType, to move
 * @param iHowfar the number of Fib-elements over which the to move
 * 	Fib-element should be moved; if this value is positiv the Fib
 * 	-element will be moved over Fib-elements it contains else over
 * 	Fib-elements it is contained in
 * @param bAbsolute if the elementPoint is an absolute value for the wool
 * 	Fib-object
 * @return the number of Fib-Elements over which the to move Fib
 * 	-element was moved; if this value is positiv the Fib-element
 * 	was moved over Fib-elements it contains else over Fib-elements
 * 	it is contained in
 */
intFib cExtObject::moveLimbElement( const char cType, const
		unsignedIntFib elementPoint, const intFib iHowfar, bool bAbsolute ){
	
	DEBUG_OUT_L2(<<"cExtObject::moveLimbElement( cType="<<cType<<", elementPoint="<<elementPoint<<", iHowfar="<<iHowfar<<", bAbsolute="<<(bAbsolute?"true":"false")<<" ) started"<<endl<<flush);
	
	const intFib iElementsMoved = cFibBranch::moveLimbElement( cType, elementPoint,
		iHowfar, bAbsolute );
	
	if ( iElementsMoved ){
		DEBUG_OUT_L4(<<"cExtObject::moveLimbElement( cType="<<cType<<", elementPoint="<<elementPoint<<", iHowfar="<<iHowfar<<", bAbsolute="<<(bAbsolute?"true":"false")<<" ) syncSubobjects()"<<endl<<flush);
		syncSubobjects();
	}
	DEBUG_OUT_L2(<<"cExtObject::moveLimbElement( cType="<<cType<<", elementPoint="<<elementPoint<<", iHowfar="<<iHowfar<<", bAbsolute="<<(bAbsolute?"true":"false")<<" ) done with result "<<iElementsMoved<<endl<<flush);
	return iElementsMoved;
}


/**
 * @return The identifier of the external Fib-object this external
 * 	element stands for. @see lIdentifier
 */
longFib cExtObject::getIdentifier() const{
	
	return lIdentifier;
}


/**
 * This method sets identifier of the external Fib-object this external
 * element stands for.
 * @see lIdentifier
 *
 * @param lInIdentifier The to set identifier of the external Fib-object
 * 	this external element stands for.
 */
void cExtObject::setIdentifier( const longFib lInIdentifier ){
	
	lIdentifier = lInIdentifier;
}


/**
 * @see vecInputValues
 * @see getNumberOfInputValues()
 * @see setNumberOfInputValues()
 * @return the vector with the input values of this external object element
 * 	@see vecInputValues
 */
cVectorExtObject * cExtObject::getInputVector(){
	
	return &vecInputValues;
}


/**
 * @see vecInputValues
 * @see getNumberOfInputValues()
 * @see setNumberOfInputValues()
 * @return the vector with the input values of this external object element
 * 	@see vecInputValues
 */
const cVectorExtObject * cExtObject::getInputVector() const{
	
	return &vecInputValues;
}


/**
 * @see vecInputValues
 * @see setNumberOfInputValues()
 * @see getInputVector()
 * @return the number of input values of this external element element
 * 	@see vecInputValues 
 */
unsignedIntFib cExtObject::getNumberOfInputValues() const{
	
	return vecInputValues.getNumberOfElements();
}


/**
 * This method sets the number of input values, this external object
 * element has, to the given number.
 *
 * @see vecInputValues
 * @see getNumberOfInputValues()
 * @see getInputVector()
 * @param uiNumberOfInputValues the number of input values this external
 * 	object element should have
 */
void cExtObject::setNumberOfInputValues(
		const unsignedIntFib uiNumberOfInputValues ){
	
	vecInputValues.resize( uiNumberOfInputValues );
}



/**
 * @see vecSubobjects
 * @see setNumberOfSubobject()
 * @see getSubobject()
 * @see setSubobject()
 * @see addSubobject()
 * @see deleteSubobject()
 * @return the count of subobjects in this external object element
 */
unsignedIntFib cExtObject::getNumberOfSubobjects() const{
	
	return (unsignedIntFib)( vecSubobjects.size() );
}


/**
 * This method sets the number of subobjects, this external object
 * element have, to the given number. It will create or delete
 * subobjects as necessary, wher created subobjects are NULL with 0
 * output variables.
 * The delete process will beginn on the end of the subobject list
 * and stop if enough subobject are deleted.
 *
 * @see vecSubobjects
 * @see getNumberOfSubobjects()
 * @see getSubobject()
 * @see setSubobject()
 * @see addSubobject()
 * @see deleteSubobject()
 * @param uiNumberOfSubobjects the number of subobjects this external
 * 	object element should have
 * @param bDeleteOld if true, delete the old subobject from the memory
 */
void cExtObject::setNumberOfSubobjects(
		const unsignedIntFib uiNumberOfSubobjects, bool bDeleteOld ){
	
	DEBUG_OUT_L2(<<"cExtObject::setNumberOfSubobjects( uiNumberOfSubobjects="<<uiNumberOfSubobjects<<", bDeleteOld="<<(bDeleteOld?"true":"false")<<" ) started"<<endl<<flush);
	cFibObjectCounts fibObjectCountsDelta;
	
	if ( vecSubobjects.size() < uiNumberOfSubobjects ){
		//add missing subobjects
		const unsignedIntFib uiSubobjectsToAdd =
			uiNumberOfSubobjects - vecSubobjects.size();
		DEBUG_OUT_L3(<<"   add missing subobjects vecSubobjects.size()="<<vecSubobjects.size()<<" < "<<uiNumberOfSubobjects<<"=uiNumberOfSubobjects  ("<<uiSubobjectsToAdd<<" subobjects to add)"<<endl<<flush);
		for ( unsignedIntFib uiActualNewSubobject = 0;
				uiActualNewSubobject < uiSubobjectsToAdd; uiActualNewSubobject++ ){
			
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
			vecSubobjects.push_back( pair< cFibElement * , list< cFibVariable * > >(
				NULL, list< cFibVariable * >() ) );
#else //FEATURE_C_EXT_OBJECT_USE_LIST
			vecSubobjects.push_back( pair< cFibElement * , vector< cFibVariable * > >(
				NULL, vector< cFibVariable * >() ) );
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
				
			fibUnderObjects.push_back( NULL );
		}
		fibObjectCountsDelta.uiNumberOfObjectpoints += uiSubobjectsToAdd;

	}else if ( uiNumberOfSubobjects < vecSubobjects.size() ){
		//delete to many subobjects
		const unsignedIntFib uiSubobjectsToDelete =
			vecSubobjects.size() - uiNumberOfSubobjects;
		DEBUG_OUT_L3(<<"   delete to many subobjects uiNumberOfSubobjects="<<uiNumberOfSubobjects<<" < "<<vecSubobjects.size()<<"vecSubobjects.size() ("<<uiSubobjectsToDelete<<" subobjects to delete)"<<endl<<flush);
		fibObjectCountsDelta.uiNumberOfObjectpoints -= uiSubobjectsToDelete;
		for ( unsignedIntFib uiActualDeletedSubobject = 0;
				uiActualDeletedSubobject < uiSubobjectsToDelete; uiActualDeletedSubobject++ ){
			
			cFibElement * pOldSubObject = vecSubobjects.back().first;
			
			if ( pOldSubObject != NULL ){
				
				pOldSubObject->pSuperiorElement = NULL;
				fibObjectCountsDelta -= evalueCountersForObject( pOldSubObject );
				
				if ( bDeleteOld ){
					//delete subobject
					pOldSubObject->deleteObject();
				}
			}
			//delete old output variables
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
			list< cFibVariable * > & vecOutputVariables =
				vecSubobjects.back().second;
			for ( list< cFibVariable* >::iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
			vector< cFibVariable * > & vecOutputVariables =
				vecSubobjects.back().second;
			for ( vector< cFibVariable* >::iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
					itrVariable = vecOutputVariables.begin();
					itrVariable != vecOutputVariables.end(); itrVariable++ ){
				
				if ( (*itrVariable) != NULL ){
					delete (*itrVariable);
				}
			}
			vecSubobjects.pop_back();
			fibUnderObjects.pop_back();
		}
	}
	
	//update counters
	updateAllCounters( fibObjectCountsDelta );
}


/**
 * @see vecSubobjects
 * @see setSubobject()
 * @see getNumberOfSubobjects()
 * @see setNumberOfSubobject()
 * @see addSubobject()
 * @see deleteSubobject()
 * @param uiNumberSubobject the number of the subobject to
 * 	return, @see vecSubobjects
 * @return a pointer to the uiNumberSubobject'th subobject of
 * 	this external object element or NULL if non such exists
 */
cFibElement * cExtObject::getSubobject( const unsignedIntFib uiNumberSubobject ){
	
	DEBUG_OUT_L2(<<"cExtObject::getSubobject( uiNumberSubobject="<<uiNumberSubobject<<" ) started"<<endl<<flush);
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	list< pair< cFibElement * , list< cFibVariable * > > >::iterator
		itrSubobj = fib::getListElement( vecSubobjects, uiNumberSubobject );
	
	if ( itrSubobj == vecSubobjects.end() ){
		return NULL;
	}
	return itrSubobj->first;
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	if ( ( uiNumberSubobject < 1 ) ||
			( vecSubobjects.size() < uiNumberSubobject )){
		//no such subobject
		return NULL;
	}
	return vecSubobjects[ uiNumberSubobject - 1 ].first;
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
}


/**
 * This method sets the iNumberSubobject'th subobject of this
 * external object element to the given subobject.
 * It will create new subobjects if ther are less than uiNumberSubobject
 * subobjects (@see setNumberOfSubobject() ).
 * The output variables for the iNumberSubobject'th subobject won't change.
 *
 * @see vecSubobjects
 * @see getSubobject()
 * @see getNumberOfSubobjects()
 * @see setNumberOfSubobject()
 * @see addSubobject()
 * @see deleteSubobject()
 * @param uiNumberSubobject the number of the subobject to set
 * 	(counting from 1)
 * @param pFibObject the pointer to the uiNumberVariable'th subobject
 * 	this external object should have
 * @param bDeleteOld if true, delete the old subobject from the memory
 * @return true if the subobject was set to the given subobject,
 * 	else false
 */
bool cExtObject::setSubobject( const unsignedIntFib uiNumberSubobject,
		cFibElement * pFibObject, bool bDeleteOld ){
	
	if ( pFibObject == NULL ){
		//no subobject to set
		return false;
	}
	if ( uiNumberSubobject < 1 ){
		//no such subobject
		return false;
	}
	if ( vecSubobjects.size() < uiNumberSubobject ){
		//increase number of subobjects
		setNumberOfSubobjects( uiNumberSubobject );
	}
	//update counters
	if ( pFibObject->pSuperiorElement != NULL ){
		pFibObject->pSuperiorElement->cutConnectionsTo(
			pFibObject );
	}
	pFibObject->pSuperiorElement = this;
	
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	list< pair< cFibElement * , list< cFibVariable * > > >::iterator
		itrSubobj = fib::getListElement( vecSubobjects, uiNumberSubobject );
	
	if ( itrSubobj == vecSubobjects.end() ){
		return false;
	}
	cFibElement * pOldSubObject = itrSubobj->first;
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	cFibElement * pOldSubObject = vecSubobjects[ uiNumberSubobject - 1 ].first;
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
	cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( pFibObject );
	
	if ( pOldSubObject != NULL ){
		
		pOldSubObject->pSuperiorElement = NULL;
		fibObjectCountsDelta -= evalueCountersForObject( pOldSubObject );
		
		if ( bDeleteOld && ( pOldSubObject != pFibObject ) ){
			//delete subobject
			pOldSubObject->deleteObject();
		}
	}
	updateAllCounters( fibObjectCountsDelta );
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	itrSubobj->first = pFibObject;
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	vecSubobjects[ uiNumberSubobject - 1 ].first = pFibObject;
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
	
	//insert the subobject on the correct position in the subobject list
	list< cFibElement * >::iterator itrActualUnderObject =
		fib::getListElement( fibUnderObjects, uiNumberSubobject );
	if ( itrActualUnderObject != fibUnderObjects.end() ){
		
		(*itrActualUnderObject) = pFibObject;
	}else{//Error: subobject lists not syncron
		fibUnderObjects.push_back( pFibObject );
	}
	
	return true;
}


/**
 * This method returns the number of output variables of the
 * uiNumberOfSubobject extern subobject in this external object element, or
 * 0 if the subobject dosn't exists.
 *
 * @see vecSubobjects
 * @see setNumberOfOutputVariables()
 * @see getOutputVariables()
 * @see getOutputVariable()
 * @param uiNumberOfSubobject the number of the subobject for which
 * 	the number of output variables is to be returned
 * @return the count of output variables of the uiNumberOfSubobject
 * 	extern subobject in this external object element, or 0 if the
 * 	subobject dosn't exists
 */
unsignedIntFib cExtObject::getNumberOfOutputVariables(
		const unsignedIntFib uiNumberOfSubobject ) const{
	
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	list< pair< cFibElement * , list< cFibVariable * > > >::const_iterator
		itrSubobj = fib::getListElement( vecSubobjects, uiNumberOfSubobject );
	
	if ( itrSubobj == vecSubobjects.end() ){
		return (unsignedIntFib)(0);
	}
	return itrSubobj->second.size();
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	if ( ( uiNumberOfSubobject < 1 ) ||
			( vecSubobjects.size() < uiNumberOfSubobject ) ){
		//no such subobject
		return (unsignedIntFib)(0);
	}
	//return number of output variables of the subobject
	return vecSubobjects[ uiNumberOfSubobject - 1 ].second.size();
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
}


/**
 * This method sets the number of output variables of the
 * uiNumberOfSubobject'th extern subobject in this external object
 * element to the given value uiNumberOfVariables.
 *
 * @see vecSubobjects
 * @see getNumberOfOutputVariables()
 * @see getOutputVariables()
 * @see getOutputVariable()
 * @param uiNumberOfSubobject the number of the subobject for which
 * 	the number of output variables is to be set
 * @param uiNumberOfVariables the number of output variables the
 * 	uiNumberOfSubobject'th subobject of this external object
 * 	element should have
 * @return the new number of output variables the
 * 	uiNumberOfSubobject'th subobject of this external object
 * 	element have
 */
unsignedIntFib cExtObject::setNumberOfOutputVariables(
		const unsignedIntFib uiNumberOfSubobject,
		const unsignedIntFib uiNumberOfVariables ){
	
	//find the correct extern object
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	list< pair< cFibElement * , list< cFibVariable * > > >::iterator
		itrSubobj = fib::getListElement( vecSubobjects, uiNumberOfSubobject );
	
	if ( itrSubobj == vecSubobjects.end() ){
		return (unsignedIntFib)(0);
	}
	list< cFibVariable * > & vecOutputVariables =
		itrSubobj->second;
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	if ( ( uiNumberOfSubobject < 1 ) ||
			( vecSubobjects.size() < uiNumberOfSubobject ) ){
		//no such extern object
		return (unsignedIntFib)(0);
	}
	vector< cFibVariable * > & vecOutputVariables =
		vecSubobjects[ uiNumberOfSubobject - 1 ].second;
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
	
	//change number of output variables
	if ( vecOutputVariables.size() < uiNumberOfVariables ){
		/*the number of output variables is to low
		-> create new output variables till ther count is
		uiNumberOfInputValues*/
		const unsignedIntFib uiOutVarsToAdd =
			uiNumberOfVariables - vecOutputVariables.size();
		for ( unsignedIntFib uiActualNewOutVar = 0;
				uiActualNewOutVar < uiOutVarsToAdd; uiActualNewOutVar++ ){
			
			vecOutputVariables.push_back( new cFibVariable( this ) );
		}
	}else if ( uiNumberOfVariables < vecOutputVariables.size() ){
		/* the number of output variables is to high
		-> delete output variables from the end of the output variables vector
		till ther count is uiNumberOfInputValues or an output variable
		can't deleted*/
		const unsignedIntFib uiOutVarsToDelete =
			vecOutputVariables.size() - uiNumberOfVariables;
		for ( unsignedIntFib uiActualDeletedOutVar = 0;
				uiActualDeletedOutVar < uiOutVarsToDelete; uiActualDeletedOutVar++ ){
			
			if ( vecOutputVariables.back()->getNumberOfUsingElements() == 0 ){
				//variable not used -> delete it
				delete (vecOutputVariables.back());
				vecOutputVariables.pop_back();
			}else{//variable is used -> can't delete it
				return vecOutputVariables.size();
			}
		}
	}//else the number of output variables is correct
	
	return vecOutputVariables.size();
}


/**
 * This method returns a vector with the pointers to the output
 * variables of the uiNumberOfSubobject'th subobject.
 *
 * @see vecSubobjects
 * @see getOutputVariable()
 * @see getNumberOfOutputVariables()
 * @see setNumberOfOutputVariables()
 * @param uiNumberOfSubobject the number of the subobject for which
 * 	the output variables should be returned
 * @return a vector with the pointers to the output variables of the
 * 	uiNumberOfSubobject'th subobject, or an empty list if non exists
 */
vector< cFibVariable* > cExtObject::getOutputVariables(
		const unsignedIntFib uiNumberOfSubobject ){
	
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	list< pair< cFibElement * , list< cFibVariable * > > >::iterator
		itrSubobj = fib::getListElement( vecSubobjects, uiNumberOfSubobject );
	
	if ( itrSubobj == vecSubobjects.end() ){
		return vector< cFibVariable* >();
	}
	return vector< cFibVariable* >(
		itrSubobj->second.begin(), itrSubobj->second.end() );
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	if ( ( uiNumberOfSubobject < 1 ) ||
			( vecSubobjects.size() < uiNumberOfSubobject ) ){
		//no such subobject
		return vector< cFibVariable* >();
	}
	//return number of output variables of the subobject
	return vecSubobjects[ uiNumberOfSubobject - 1 ].second;
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
}


/**
 * This method returns a pointer to the uiNumberOfInputVariable'th
 * output variable of the uiNumberOfSubobject'th subobject of
 * this external object element.
 *
 * @see vecSubobjects
 * @see getOutputVariables()
 * @see getNumberOfOutputVariables()
 * @see setNumberOfOutputVariables()
 * @param uiNumberOfSubobject the number of the subobject for which
 * 	the output variable should be returned
 * @param uiNumberOfOutputVariable the number of the output variable of
 * 	the uiNumberOfSubobject'th subobject to return
 * @return a pointer to the uiNumberOfInputVariable'th output variable of
 * 	the uiNumberOfSubobject'th subobject of this external object element,
 * 	or NULL if non exists
 */
cFibVariable * cExtObject::getOutputVariable( const unsignedIntFib uiNumberOfSubobject,
		const unsignedIntFib uiNumberOfOutputVariable ){
	
	//return output variables of the subobject
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	list< pair< cFibElement * , list< cFibVariable * > > >::iterator
		itrSubobj = fib::getListElement( vecSubobjects, uiNumberOfSubobject );
	
	if ( itrSubobj == vecSubobjects.end() ){
		return NULL;
	}
	list< cFibVariable * >::iterator itrOutVar =
		fib::getListElement( itrSubobj->second, uiNumberOfOutputVariable );
	
	if ( itrOutVar == itrSubobj->second.end() ){
		return NULL;
	}
	return (*itrOutVar);
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	if ( ( uiNumberOfSubobject < 1 ) ||
			( vecSubobjects.size() < uiNumberOfSubobject ) ){
		//no such subobject
		return NULL;
	}
	vector< cFibVariable * > & vecOutputVariables =
		vecSubobjects[ uiNumberOfSubobject - 1 ].second;
	
	if ( ( uiNumberOfOutputVariable < 1 ) ||
			( vecOutputVariables.size() < uiNumberOfOutputVariable ) ){
		//no such output variable
		return NULL;
	}
	return vecOutputVariables[ uiNumberOfOutputVariable - 1 ];
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
}


/**
 * This method adds the given subobject to the subobjects of this extern
 * object element.
 * This will fail if:
 * 	- ther is no subobject (pSubobject==NULL)
 *
 * @see vecSubobjects
 * @see getSubobject()
 * @see setSubobject()
 * @see deleteSubobject()
 * @see getNumberOfSubobjects()
 * @see setNumberOfSubobject()
 * @see getOutputVariables()
 * @see getNumberOfOutputVariables()
 * @see setNumberOfOutputVariables()
 * @param pSubobject a pointer to the subobject to add; the object
 * 	will not be copied, so don't delete it
 * @param uiPosition the position on which the subobject is to insert in
 * 	this extern object element subobject vector (counting begins with 1),
 * 	if 0 or greater the number of subobjects the subobject will be
 * 	inserted to the end of the subobject list
 * @param uiNumberOfOutVar the number of output variables of the subobject
 * 	to add should have
 * @return true if the subobject pSubobject was inserted, else false
 */
bool cExtObject::addSubobject( cFibElement * pSubobject,
		unsignedIntFib uiPosition, const unsignedIntFib uiNumberOfOutVar ){

	if ( pSubobject == NULL ){
		//nothing to insert
		return false;
	}
	//generate the output variables for the subobject to add
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	list< cFibVariable * > vecOutputVariables;
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	vector< cFibVariable * > vecOutputVariables;
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
	for ( unsignedIntFib uiActualOutVar = 0;
			uiActualOutVar < uiNumberOfOutVar; uiActualOutVar++ ){
		
		vecOutputVariables.push_back( new cFibVariable( this) );
	}
	//add the subobject
	if ( pSubobject->pSuperiorElement != NULL ){
		pSubobject->pSuperiorElement->cutConnectionsTo(
			pSubobject );
	}
	if ( ( uiPosition == 0 ) || ( vecSubobjects.size() < uiPosition ) ){
		//add the subobject to the end of the subobject vector
		vecSubobjects.push_back( make_pair( pSubobject, vecOutputVariables ) );
		fibUnderObjects.push_back( pSubobject );
		
	}else if ( uiPosition == 1 ){
		//add the subobject to the front of the subobject vector
		vecSubobjects.insert( vecSubobjects.begin(),
			make_pair( pSubobject, vecOutputVariables ) );
		
		/*add the subobject to the subobject at the first position*/
		fibUnderObjects.push_front( pSubobject );
	}else{
		//insert the subobject on the correct position
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
		list< pair< cFibElement * , list< cFibVariable * > > >::iterator
			itrActualSubobject;
#else //FEATURE_C_EXT_OBJECT_USE_LIST
		vector< pair< cFibElement * , vector< cFibVariable * > > >::iterator
			itrActualSubobject;
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
		list< cFibElement * >::iterator itrActualUnderObject =
			fibUnderObjects.begin();
		for ( itrActualSubobject = vecSubobjects.begin();
				( itrActualSubobject != vecSubobjects.end() ) &&
				( itrActualUnderObject != fibUnderObjects.end() ) &&
				( uiPosition != 1 );
				itrActualSubobject++, itrActualUnderObject++ , uiPosition-- ){
			//nothing to do
		}
		vecSubobjects.insert( itrActualSubobject,
			make_pair( pSubobject, vecOutputVariables ) );
		fibUnderObjects.insert( itrActualUnderObject, pSubobject );
	}
	//update the values
	pSubobject->pSuperiorElement = this;
	
	cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( pSubobject );
	fibObjectCountsDelta.uiNumberOfObjectpoints++;
	updateAllCounters( fibObjectCountsDelta );
	return true;
}


/**
 * This method deletes the uiSubobjectNumber'th subobject in this extern
 * object element.
 *
 * @see vecSubobjects
 * @see getSubobject()
 * @see setSubobject()
 * @see addSubobject()
 * @see getNumberOfSubobjects()
 * @see setNumberOfSubobject()
 * @see getOutputVariables()
 * @see getNumberOfOutputVariables()
 * @see setNumberOfOutputVariables()
 * @param uiSubobjectNumber the number of the subobject in the subobject
 * 	vector to delete
 * @param bDeleteOld if true the subobject will be removed from the memory,
 * 	else yust the reference will be removed from this extern object
 * 	element;default is true
 * @return true if the uiSubobjectNumber'th subobject was deleted, else false
 */
bool cExtObject::deleteSubobject( unsignedIntFib uiSubobjectNumber,
		bool bDeleteOld ){
	
	if ( ( uiSubobjectNumber < 1 ) ||
			( vecSubobjects.size() < uiSubobjectNumber ) ){
		//no such subobject
		return false;
	}
	//find the correct subobject
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	list< pair< cFibElement * , list< cFibVariable * > > >::iterator
		itrActualSubobject;
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	vector< pair< cFibElement * , vector< cFibVariable * > > >::iterator
		itrActualSubobject;
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
	list< cFibElement* >::iterator itrActualUnderObject = fibUnderObjects.begin();
	for ( itrActualSubobject = vecSubobjects.begin();
			itrActualUnderObject != fibUnderObjects.end() &&
			itrActualSubobject != vecSubobjects.end() &&
			uiSubobjectNumber != 1;
			itrActualSubobject++, itrActualUnderObject++ , uiSubobjectNumber-- ){
		//nothing to do
	}
	if ( itrActualSubobject != vecSubobjects.end() ){
		//delete the subobject
		if ( itrActualUnderObject != fibUnderObjects.end() ){
			fibUnderObjects.erase( itrActualUnderObject );
		}
		cFibElement * pSubobjectToDelete = itrActualSubobject->first;
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
		list< cFibVariable * > & vecOutputVariables = itrActualSubobject->second;
		//delete output variables
		for ( list< cFibVariable* >::iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
		vector< cFibVariable * > & vecOutputVariables = itrActualSubobject->second;
		//delete output variables
		for ( vector< cFibVariable* >::iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
				itrVariable = vecOutputVariables.begin();
				itrVariable != vecOutputVariables.end(); itrVariable++ ){
			
			if ( (*itrVariable) != NULL ){
				delete (*itrVariable);
			}
		}
		vecSubobjects.erase( itrActualSubobject );
		
		//update branch counts
		cFibObjectCounts fibObjectCountsDelta;
		
		if ( pSubobjectToDelete != NULL ){
			fibObjectCountsDelta -= evalueCountersForObject( pSubobjectToDelete );
			fibObjectCountsDelta.uiNumberOfObjectpoints--;
			updateAllCounters( fibObjectCountsDelta );
			
			if ( pSubobjectToDelete->pSuperiorElement == this ){
				pSubobjectToDelete->pSuperiorElement = NULL;
				if ( bDeleteOld ){
					pSubobjectToDelete->deleteObject();
				}//else don't delete
			}
		}else{//( pSubobjectToDelete == NULL )
			fibObjectCountsDelta.uiNumberOfObjectpoints--;
			updateAllCounters( fibObjectCountsDelta );
		}
		return true;
	}//else ( uiSubobjectNumber != 1 )
	return false;
}


/**
 * This method stores this Fib-object in the compressed Fib-format
 * into the given stream.
 * It is needed because the stream can yust store byts but the size of
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
bool cExtObject::storeBit( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{

	//the value returned by the method
	bool bReturnValue = true;

	const char cInitiation = 0x0D;

	const bool bInitiationStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, &cInitiation, 4 );
	if ( ! bInitiationStored ){
		return false;
	}
	//get the domain for the variables
	cTypeVariable typeVariable;
	/*get the value domain for variables*/
	cDomains validDomains = getValidValueDomains();
	//return the variable domain
	cDomainIntegerBasis * pVariableDomain = (cDomainIntegerBasis*)
		validDomains.getDomainForElement( typeVariable );
	const bool bStandardVariableDomainUsed = (pVariableDomain == NULL);
	if ( bStandardVariableDomainUsed ){
		//use the standrad domain
		pVariableDomain = (cDomainIntegerBasis*)typeVariable.getStandardDomain();
	}
	//get the domain for the external object element
	cTypeExtObject typeExtObject;
	//return the external object element domain
	cDomainVectorBasis * pDomainExtObject = (cDomainVectorBasis*)
		validDomains.getDomainForElement( typeExtObject );
	const bool bStandardExtObjDomainUsed = (pDomainExtObject == NULL);
	if ( bStandardExtObjDomainUsed ){
		//use the standrad domain
		pDomainExtObject = (cDomainVectorBasis*)typeExtObject.getStandardDomain();
	}
	
	//store the identifier of the external object element
	if ( pDomainExtObject->getNumberOfElements() < 3 ){
		/*error in domain (domain for identifier and / or input values
		missing and / or number of subobjects) -> can't load external object*/
		if ( bStandardVariableDomainUsed ){
			delete pVariableDomain;
		}
		if ( bStandardExtObjDomainUsed ){
			delete pDomainExtObject;
		}
		return false;
	}
	cDomainIntegerBasis * pDomainIdentifier = ((cDomainIntegerBasis*)(
		pDomainExtObject->getElementDomain( 1 )));
	//store the identifier number
	const bool bIdentifierStored = pDomainIdentifier->storeUnscaledValue(
		lIdentifier, stream, cRestBits, uiRestBitPosition );
	if ( ! bIdentifierStored ){
		//error identifier not stored
		if ( bStandardVariableDomainUsed ){
			delete pVariableDomain;
		}
		if ( bStandardExtObjDomainUsed ){
			delete pDomainExtObject;
		}
		return false;
	}
	//store input values
	//store the count of input values
	cDomainIntegerBasis * pDomainCountInVar = ((cDomainIntegerBasis*)(
		pDomainExtObject->getElementDomain( 2 )));
	
	const unsignedIntFib uiNumberOfInputValues =
		vecInputValues.getNumberOfElements();
	
	const bool bCountInVarStored = pDomainCountInVar->storeUnscaledValue(
		uiNumberOfInputValues, stream, cRestBits, uiRestBitPosition );
	if ( ! bCountInVarStored ){
		//error input variable count not stored
		if ( bStandardVariableDomainUsed ){
			delete pVariableDomain;
		}
		if ( bStandardExtObjDomainUsed ){
			delete pDomainExtObject;
		}
		return false;
	}
	//store the input values vector
	const bool bInputValuesStored = vecInputValues.store(
			stream, cRestBits, uiRestBitPosition );
	
	if ( ! bInputValuesStored ){
		//error input value not stored
		if ( bStandardVariableDomainUsed ){
			delete pVariableDomain;
		}
		if ( bStandardExtObjDomainUsed ){
			delete pDomainExtObject;
		}
		return false;
	}
	//store the subobjects of the external object element
	//store the count of subobjects of the external object element
	cDomainIntegerBasis * pDomainCountSubObj = ((cDomainIntegerBasis*)(
		pDomainExtObject->getElementDomain( 3 )));
	
	const unsignedLongFib ulNumberOfSubObjects = vecSubobjects.size();
	
	const bool bCountSubObjStored = pDomainCountSubObj->storeUnscaledValue(
		ulNumberOfSubObjects, stream, cRestBits, uiRestBitPosition );
	if ( ! bCountSubObjStored ){
		//error subobject count not stored
		if ( bStandardVariableDomainUsed ){
			delete pVariableDomain;
		}
		if ( bStandardExtObjDomainUsed ){
			delete pDomainExtObject;
		}
		return false;
	}
	if ( ( 0 < ulNumberOfSubObjects ) &&
			( pDomainExtObject->getNumberOfElements() < 4 ) ){
		/*error in domain (domain for the output variable count missing)
		-> can't store external object subobjects*/
		if ( bStandardVariableDomainUsed ){
			delete pVariableDomain;
		}
		if ( bStandardExtObjDomainUsed ){
			delete pDomainExtObject;
		}
		return false;
	}
	
	cDomainIntegerBasis * pDomainCountOutVar = ((cDomainIntegerBasis*)(
		pDomainExtObject->getElementDomain( 4 )));
	
	//store ulNumberOfSubObjects subobjects of the external object element
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	for ( list< pair< cFibElement * , list< cFibVariable * > > >::const_iterator
			itrActualSubobject = vecSubobjects.begin();
			itrActualSubobject != vecSubobjects.end();
			itrActualSubobject++ ){
		//store the output variable count
		const unsignedLongFib ulNumberOfOutVariables =
			itrActualSubobject->second.size();
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	for ( unsignedLongFib ulActualUnderobject = 0;
			ulActualUnderobject < ulNumberOfSubObjects; ulActualUnderobject++ ){
		//store the output variable count
		const unsignedLongFib ulNumberOfOutVariables =
			vecSubobjects[ ulActualUnderobject ].second.size();
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
		
		const bool bCountOutVarStored = pDomainCountOutVar->storeUnscaledValue(
			ulNumberOfOutVariables, stream, cRestBits, uiRestBitPosition );
		if ( ! bCountOutVarStored ){
			//error output variable count not stored
			if ( bStandardVariableDomainUsed ){
				delete pVariableDomain;
			}
			if ( bStandardExtObjDomainUsed ){
				delete pDomainExtObject;
			}
			return false;
		}
		//store the subobject
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
		const cFibElement * pSubObjectToStore =
			 itrActualSubobject->first;
#else //FEATURE_C_EXT_OBJECT_USE_LIST
		const cFibElement * pSubObjectToStore =
			 vecSubobjects[ ulActualUnderobject ].first;
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
		
		if ( pSubObjectToStore == NULL ){
			//error no subobject -> store NULL
			const char cNull = 0x00;
		
			const bool bNullStored = nBitStream::store( stream, cRestBits,
				uiRestBitPosition, &cNull, 4 );
			if ( ! bNullStored ){
				if ( bStandardVariableDomainUsed ){
					delete pVariableDomain;
				}
				if ( bStandardExtObjDomainUsed ){
					delete pDomainExtObject;
				}
				return false;
			}
			bReturnValue = false;
			continue;//next subobject
		}//else (pSubObjectToStore != NULL)
		const bool bSubObjectStored = pSubObjectToStore->storeBit(
			stream, cRestBits, uiRestBitPosition );
		if ( ! bSubObjectStored ){
			//error output variable count not stored
			if ( bStandardVariableDomainUsed ){
				delete pVariableDomain;
			}
			if ( bStandardExtObjDomainUsed ){
				delete pDomainExtObject;
			}
			return false;
		}
	}

	if ( bStandardVariableDomainUsed ){
		delete pVariableDomain;
	}
	if ( bStandardExtObjDomainUsed ){
		delete pDomainExtObject;
	}
	return bReturnValue;
}


/**
 * This method sets each variable, which is defined over an leaf,
 * to an uniqe integer number greater than the given number
 * uiLastVariableNumber. While storing this number can be used to
 * identify the variable.
 *
 * @param uiLastVariableNumber the number which was last used, this
 * 	means also is the greatest used, in this object.
 * @return the number which was last use, this
 * 	means also is the greatest used, in this object
 * 	from the method
 */
unsignedIntFib cExtObject::enumerateVariablesForStoring(
		unsignedIntFib uiLastVariableNumber ){
	
	unsignedIntFib uiBiggestVariableNumber = uiLastVariableNumber;
	//enumerate variables of all subobjects
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	for ( list< pair< cFibElement * , list< cFibVariable * > > >::iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	for ( vector< pair< cFibElement * , vector< cFibVariable * > > >::iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
			itrSubObject = vecSubobjects.begin();
			itrSubObject != vecSubobjects.end(); itrSubObject++ ){
		
		unsignedIntFib uiLastSubobjVariableNumber = uiLastVariableNumber;
		
		//enumerate output variables
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
		list< cFibVariable * > & vecOutputVariables = itrSubObject->second;
		for ( list< cFibVariable * >::iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
		vector< cFibVariable * > & vecOutputVariables = itrSubObject->second;
		for ( vector< cFibVariable * >::iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
				itrOutputVariable = vecOutputVariables.begin();
				itrOutputVariable != vecOutputVariables.end(); itrOutputVariable++ ){
			
			if ( *itrOutputVariable ){
				uiLastSubobjVariableNumber++;
				(*itrOutputVariable)->setIntegerValue( uiLastSubobjVariableNumber );
			}
		}
		//enumerate variables in subobject
		if ( itrSubObject->first ){
			uiLastSubobjVariableNumber = itrSubObject->first->
				enumerateVariablesForStoring( uiLastSubobjVariableNumber );
		}
		if ( uiBiggestVariableNumber < uiLastSubobjVariableNumber ){
			uiBiggestVariableNumber = uiLastSubobjVariableNumber;
		}
	}
	return uiBiggestVariableNumber;
}


/**
 * This method cuts the connections of this Fib-element to the
 * given Fib-element.
 *
 * @param pFibElement the Fib-element to which to cut the connection
 */
void cExtObject::cutConnectionsTo( const cFibElement * pFibElement ){
	
	if ( pFibElement == NULL ){
		//no connections to cut
		return;
	}
	cFibElement::cutConnectionsTo( pFibElement );
	//check the subobjects
	bool bSubobjectsChanged = false;
	list<cFibElement*>::iterator itrActualUnderObject = fibUnderObjects.begin();
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	for ( list< pair< cFibElement * , list< cFibVariable * > > >::iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	for ( vector< pair< cFibElement * , vector< cFibVariable * > > >::iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
			itrActualSubobject = vecSubobjects.begin();
			itrActualUnderObject != fibUnderObjects.end();
			itrActualUnderObject++, itrActualSubobject++ ){
		
		if ( (*itrActualUnderObject) == pFibElement ){
			/*cut connection to the actual subobject;
			it is (itrActualUnderObject != fibUnderObjects.end())*/
			(*itrActualUnderObject) = NULL;
			itrActualSubobject->first = NULL;
			bSubobjectsChanged = true;
		}
	}
	if ( bSubobjectsChanged ){
		//cut connection to the found subobject
		updateAllCounters();
	}
}


/**
 * This method syncronises the subobjects of this cExtObject class with
 * the subobject list fibUnderObjects of the cFibBranch class.
 */
void cExtObject::syncSubobjects(){
	
	DEBUG_OUT_L2(<<"cExtObject::syncSubobjects() started (number underobjects="<<flush<<fibUnderObjects.size()<<", number subobjects="<<vecSubobjects.size()<<")"<<endl<<flush);
	if ( fibUnderObjects.empty() ){
		//no subobjects
		while( ! vecSubobjects.empty() ){
			
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
			list< cFibVariable * > & vecOutputVariables =
				vecSubobjects.back().second;
			for ( list< cFibVariable* >::iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
			vector< cFibVariable * > & vecOutputVariables =
				vecSubobjects.back().second;
			for ( vector< cFibVariable* >::iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
					itrVariable = vecOutputVariables.begin();
					itrVariable != vecOutputVariables.end(); itrVariable++ ){
				
				if ( (*itrVariable) != NULL ){
					delete (*itrVariable);
				}
			}
			vecSubobjects.pop_back();
		}
		DEBUG_OUT_L2(<<"cExtObject::syncSubobjects() done no subobjects"<<endl<<flush);
		return;
	}
	
	//syncronize the subobjects
	list< cFibElement* >::const_iterator itrActualUnderobject = fibUnderObjects.begin();
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
	list< pair< cFibElement * , list< cFibVariable * > > >::iterator
		itrActualSubobject = vecSubobjects.begin();
#else //FEATURE_C_EXT_OBJECT_USE_LIST
	vector< pair< cFibElement * , vector< cFibVariable * > > >::iterator
		itrActualSubobject = vecSubobjects.begin();
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
	while ( itrActualUnderobject != fibUnderObjects.end() ){
		
		if ( itrActualSubobject == vecSubobjects.end() ){
			//insert a new subobject with 0 output variables
			DEBUG_OUT_L3(<<"   insert a new subobject "<<(*itrActualUnderobject)<<" with 0 output variables"<<endl<<flush);
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
			vecSubobjects.push_back( make_pair(
				( * itrActualUnderobject ), list< cFibVariable * >() ) );
#else //FEATURE_C_EXT_OBJECT_USE_LIST
			vecSubobjects.push_back( make_pair(
				( * itrActualUnderobject ), vector< cFibVariable * >() ) );
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
			//insert the next subobject at the end of the subobject vector
			itrActualSubobject = vecSubobjects.end();
			itrActualUnderobject++;
		}else{//compare subobject and underobject
			DEBUG_OUT_L2(<<"   subobject="<<(itrActualSubobject->first)<<" ?==? underobject="<<(*itrActualUnderobject)<<endl<<flush);
			if ( (*itrActualUnderobject) == itrActualSubobject->first ){
				//subobjects equal -> check next pair
				itrActualSubobject++;
				itrActualUnderobject++;
			}else{//subobjects not equal
				//check if one subobject was removed
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
				list< pair< cFibElement * , list< cFibVariable * > > >::const_iterator
					itrNextSubobject = itrActualSubobject;
#else //FEATURE_C_EXT_OBJECT_USE_LIST
				vector< pair< cFibElement * , vector< cFibVariable * > > >::const_iterator
					itrNextSubobject = itrActualSubobject;
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
				itrNextSubobject++;
				DEBUG_OUT_L3(<<"   check if one subobject was removed (next subobject="<<(itrNextSubobject->first)<<")"<<endl<<flush);
				if ( itrNextSubobject->first == (*itrActualUnderobject) ){
					//one subobject was removed -> remove actual subobject
					DEBUG_OUT_L3(<<"      one subobject was removed -> remove actual subobject"<<endl<<flush);
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
					list< cFibVariable * > & vecActualOutpuVariables =
						itrActualSubobject->second;
#else //FEATURE_C_EXT_OBJECT_USE_LIST
					vector< cFibVariable * > & vecActualOutpuVariables =
						itrActualSubobject->second;
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
					
					while( ! vecActualOutpuVariables.empty() ){
						
						delete (vecActualOutpuVariables.back());
						vecActualOutpuVariables.pop_back();
					}
					itrActualSubobject = vecSubobjects.erase( itrActualSubobject );
				}else{//check if one subobject was inserted
					list< cFibElement* >::const_iterator itrNextUnderobject =
						itrActualUnderobject;
					itrNextUnderobject++;
					DEBUG_OUT_L3(<<"   check if one subobject was inserted (next underobject="<<(*itrNextUnderobject)<<")"<<endl<<flush);
					if ( itrActualSubobject->first == (*itrNextUnderobject) ){
						/*one subobject was inserted -> insert subobject into
						subobject vector with 0 output variables*/
						DEBUG_OUT_L3(<<"      one subobject was inserted -> insert subobject "<<(*itrNextUnderobject)<<" into subobject vector with 0 output variables"<<endl<<flush);
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
						itrActualSubobject = vecSubobjects.insert( itrActualSubobject, make_pair(
							( * itrActualUnderobject ), list< cFibVariable * >() ) );
#else //FEATURE_C_EXT_OBJECT_USE_LIST
						itrActualSubobject = vecSubobjects.insert( itrActualSubobject, make_pair(
							( * itrActualUnderobject ), vector< cFibVariable * >() ) );
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
					}else{//overwrite subobject
						DEBUG_OUT_L3(<<"      overwrite subobject: subobject = underobject(="<<(*itrActualUnderobject)<<")"<<endl<<flush);
						itrActualSubobject->first = ( * itrActualUnderobject );
					}
					itrActualSubobject++;
					itrActualUnderobject++;
				}
			}
		}
	}//end for all subobjects
	//remove subobjects that are to many
	while ( itrActualSubobject != vecSubobjects.end() ){
		
		DEBUG_OUT_L2(<<"   delete missing subobject="<<(itrActualSubobject->first)<<endl<<flush);
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
		list< cFibVariable * > & vecActualOutpuVariables =
			itrActualSubobject->second;
#else //FEATURE_C_EXT_OBJECT_USE_LIST
		vector< cFibVariable * > & vecActualOutpuVariables =
			itrActualSubobject->second;
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
		
		while( ! vecActualOutpuVariables.empty() ){
			
			delete (vecActualOutpuVariables.back());
			vecActualOutpuVariables.pop_back();
		}
		itrActualSubobject = vecSubobjects.erase( itrActualSubobject );
	}
	DEBUG_OUT_L2(<<"cExtObject::syncSubobjects() done"<<endl<<flush);
}


/**
 * This method copies the connected object with the given number in the
 * order of connected objects.
 * For this every Fib-element, beginning from this Fib-element, that
 * is part of the connected object will be copied.
 * Variables which are not defined in the connected object but used
 * don't change ther reference.
 * It is an help method for the copy method. It dosn't update the
 * structural information of the created Fib-object.
 *
 * @see copy()
 * @param iObjectPoint the number of the connected object to copy;
 * 	the standartvalue is 0 for coping the complet actual object
 * @return the copy of the connected object or NULL if non such exists
 */
cExtObject * cExtObject::copyInternal( const unsignedIntFib uiObjectPoint ) const{
	
	//copy this element
	cExtObject * pFibObjectCopy = new cExtObject( lIdentifier, vecInputValues );
	
	//copy and insert the subobjects which are part of the uiObjectPoint subobject
	if ( uiObjectPoint == 0 ){
		//copy all subobjects
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
		for ( list< pair< cFibElement * , list< cFibVariable * > > >::const_iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
		for ( vector< pair< cFibElement * , vector< cFibVariable * > > >::const_iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
				itrActualSubObject = vecSubobjects.begin();
				itrActualSubObject != vecSubobjects.end();
				itrActualSubObject++ ){

			cFibElement * pSubobject = NULL;
			if ( itrActualSubObject->first != NULL ){
				//copy subobject
				pSubobject = itrActualSubObject->first->copyInternal();
			}// else itrActualSubObject->first == NULL
			
			//copy output variables
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
			list< cFibVariable * > vecNewOutputVariables;
#else //FEATURE_C_EXT_OBJECT_USE_LIST
			vector< cFibVariable * > vecNewOutputVariables;
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
			/*map to map old output variables to new
				first element: old output variables pointer
				second elmenent: new correspondending output variables pointer
			*/
			list< pair< cFibVariable *, cFibVariable * > > liMapOutputVariables;
			
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
			const list< cFibVariable * > & vecOutputVariables =
				itrActualSubObject->second;
			for ( list< cFibVariable * >::const_iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
			const vector< cFibVariable * > & vecOutputVariables =
				itrActualSubObject->second;
			for ( vector< cFibVariable * >::const_iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
					itrOutputVariable = vecOutputVariables.begin();
					itrOutputVariable != vecOutputVariables.end();
					itrOutputVariable++ ){
				
				cFibVariable * pNewOutputVariable =
					new cFibVariable( pFibObjectCopy );
				vecNewOutputVariables.push_back( pNewOutputVariable );
				liMapOutputVariables.push_back( make_pair(
					const_cast< cFibVariable * >(*itrOutputVariable), pNewOutputVariable ) );
			}
			
			if ( pSubobject != NULL ){
				//subobject could be copied
				pFibObjectCopy->vecSubobjects.push_back( make_pair(
					pSubobject, vecNewOutputVariables ) );
				pFibObjectCopy->fibUnderObjects.push_back( pSubobject );
				pSubobject->pSuperiorElement = pFibObjectCopy;
				
				//replace output variables
				for ( list< pair< cFibVariable *, cFibVariable * > >::iterator
						itrOutputVariable = liMapOutputVariables.begin();
						itrOutputVariable != liMapOutputVariables.end();
						itrOutputVariable++ ){
					
					pSubobject->replaceVariable( itrOutputVariable->first,
						itrOutputVariable->second );
				}
				
			}else{/*subobject is NULL*/
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
				pFibObjectCopy->vecSubobjects.push_back(
					pair< cFibElement * , list< cFibVariable * > >(
						NULL, vecNewOutputVariables ) );
#else //FEATURE_C_EXT_OBJECT_USE_LIST
				pFibObjectCopy->vecSubobjects.push_back(
					pair< cFibElement * , vector< cFibVariable * > >(
						NULL, vecNewOutputVariables ) );
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
				pFibObjectCopy->fibUnderObjects.push_back( NULL );
			}
			
		}
	}else{
		//copy one subobject
		unsignedIntFib uiRemainingObjectpoints = uiObjectPoint;
		unsignedIntFib uiActualObjectpoints = 0;
		bool bSubobjectFound = false;
		
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
		for ( list< pair< cFibElement * , list< cFibVariable * > > >::const_iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
		for ( vector< pair< cFibElement * , vector< cFibVariable * > > >::const_iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
				itrActualSubobject = vecSubobjects.begin();
				itrActualSubobject != vecSubobjects.end();
				itrActualSubobject++ ){
			
			if ( itrActualSubobject->first != NULL ){
				
				uiActualObjectpoints = itrActualSubobject->first->
					getNumberOfObjectPoints() + 1;
				
				if ( uiRemainingObjectpoints <= uiActualObjectpoints ){
					//subobject to copy found
					cFibElement * pSubobject = itrActualSubobject->first->
						copyInternal( uiRemainingObjectpoints - 1 );
					
					if ( pSubobject == NULL ){
						//subobject couldn't be copied -> give back NULL
						pFibObjectCopy->deleteObject();
						return NULL;
					}//else subobject could be copied
					pFibObjectCopy->fibUnderObjects.push_back( pSubobject );
					pSubobject->pSuperiorElement = pFibObjectCopy;
					
					//copy output variables
					
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
					list< cFibVariable * > vecNewOutputVariables;
					const list< cFibVariable * > & vecOutputVariables =
						itrActualSubobject->second;
					for ( list< cFibVariable * >::const_iterator
#else //FEATURE_C_EXT_OBJECT_USE_LIST
					vector< cFibVariable * > vecNewOutputVariables;
					const vector< cFibVariable * > & vecOutputVariables =
						itrActualSubobject->second;
					for ( vector< cFibVariable * >::const_iterator
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
							itrOutputVariable = vecOutputVariables.begin();
							itrOutputVariable != vecOutputVariables.end();
							itrOutputVariable++ ){
						
						cFibVariable * pNewOutputVariable =
							new cFibVariable( pFibObjectCopy );
						vecNewOutputVariables.push_back( pNewOutputVariable );
						pSubobject->replaceVariable( const_cast< cFibVariable * >(
							*itrOutputVariable), pNewOutputVariable );
					}
					pFibObjectCopy->vecSubobjects.push_back( make_pair(
						pSubobject, vecNewOutputVariables ) );
					bSubobjectFound = true;
					
					break;//done
				}else{//objectpoint not found yet
					//insert empty place holder for missing subobject
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
					pFibObjectCopy->vecSubobjects.push_back( pair< cFibElement * , list< cFibVariable * > >(
						NULL, list< cFibVariable * >() ) );
#else //FEATURE_C_EXT_OBJECT_USE_LIST
					pFibObjectCopy->vecSubobjects.push_back( pair< cFibElement * , vector< cFibVariable * > >(
						NULL, vector< cFibVariable * >() ) );
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
				}
				uiRemainingObjectpoints -= uiActualObjectpoints;
			}else{//( itrActualSubobject->first == NULL )
				if ( 1 < uiRemainingObjectpoints ){
					uiRemainingObjectpoints--;
					//insert empty place holder for missing subobject
#ifdef FEATURE_C_EXT_OBJECT_USE_LIST
					pFibObjectCopy->vecSubobjects.push_back( pair< cFibElement * , list< cFibVariable * > >(
						NULL, list< cFibVariable * >() ) );
#else //FEATURE_C_EXT_OBJECT_USE_LIST
					pFibObjectCopy->vecSubobjects.push_back( pair< cFibElement * , vector< cFibVariable * > >(
						NULL, vector< cFibVariable * >() ) );
#endif //FEATURE_C_EXT_OBJECT_USE_LIST
				}else{//copy NULL subobject
					//-> subobject couldn't be copied -> give back NULL
					pFibObjectCopy->deleteObject();
					return NULL;
				}
			}
		}
		if ( ! bSubobjectFound ){
			/*no subobject to copy found
			-> the objectpoint uiObjectPoint dosn't exists
			-> give back NULL*/
			pFibObjectCopy->deleteObject();
			return NULL;
		}
	}
	
	pFibObjectCopy->updateAllCounters();
	
	return pFibObjectCopy;
}









