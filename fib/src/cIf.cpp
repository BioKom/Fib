/**
 * @class cIf
 * file name: cIf.cpp
 * @author Betti Oesterholz
 * @date 20.04.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the fib if-element.
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
 * This class represents the fib if-element.
 * An if-element contains an condition and two subobjects, for the true
 * case and the false case of the condition.
 * If the condition is true the subobject for the true case will be
 * evalued, else the subobject for the false case.
 *
 */
/*
History:
20.04.2011  Oesterholz  created
21.08.2011  Oesterholz  syncUnderobjects() renamed to syncSubobjects()
05.10.2011  Oesterholz  Bugfix for restoring: every subobject has it's own
	defined variables
17.10.2011  Oesterholz  FEATURE_OUTPUT_ELEMENT_NUMBER_XML implemented
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
01.08.2013  Oesterholz  method assignValues() added
*/


#include "cIf.h"

#include "cFibElement.h"
#include "cTypeVariable.h"
#include "cTypeUnderFunction.h"
#include "cDomainIntegerBasis.h"
#include "cConditionFalse.h"

using namespace fib;



/**
 * parameterconstructor
 *
 * @param inCondition the condition this if-element should have
 * @param pInUnderobjectTrueCase the fib-element, which is the underobject of
 * 	this fib-element for the true case;
 * 	(it also stands next in the order of fib-elements)
 * @param pInUnderobjectFalseCase the fib-element, which is the
 * 	underobject of this fib-element for the false case
 * @param pInSuperiorElement the fib-element, in which this
 * 	if-element is an underobject
 */
cIf::cIf( const cCondition & inCondition,
		cFibElement * pInUnderobjectTrueCase,
		cFibElement * pInUnderobjectFalseCase,
		cFibElement * pInSuperiorElement ):
		cFibBranch( list<cFibElement*>(), pInSuperiorElement ),
		pCondition( NULL ),
		pFibObjectTrue( pInUnderobjectTrueCase ),
		pFibObjectFalse( pInUnderobjectFalseCase ){
	
	fibObjectCounts.vecNumberOfFibElements[
		cFibObjectCounts::IF ]++;
	fibObjectCounts.vecNumberOfFibElements[
		cFibObjectCounts::ALL ]++;
	
	if ( (& inCondition) != NULL ){
		setCondition( inCondition );
	}else{
		setCondition( cConditionFalse() );
	}
	if ( pInUnderobjectTrueCase ){
		fibUnderObjects.push_back( pInUnderobjectTrueCase );
		
		if ( pInUnderobjectTrueCase->pSuperiorElement != NULL ){
			pInUnderobjectTrueCase->pSuperiorElement->cutConnectionsTo(
				pInUnderobjectTrueCase );
		}
		pInUnderobjectTrueCase->pSuperiorElement = this;
	}
	if ( pInUnderobjectFalseCase ){
		fibUnderObjects.push_back( pInUnderobjectFalseCase );
		
		if ( pInUnderobjectFalseCase->pSuperiorElement != NULL ){
			pInUnderobjectFalseCase->pSuperiorElement->cutConnectionsTo(
				pInUnderobjectFalseCase );
		}
		pInUnderobjectFalseCase->pSuperiorElement = this;
	}
	updateAllCounters();
	if ( pInSuperiorElement ){
		pInSuperiorElement->insertObjectInElement( this );
	}
}


/**
 * copyconstructor
 * This copyconstructor constructs a copy of the given if-element.
 * It dosn't copy other if-elements than the given, even if ther are
 * in the if-element.
 *
 * @param ifElement the if-element to copy
 */
cIf::cIf( const cIf & ifElement ):
		cFibBranch( ifElement ), pCondition( NULL ),
		pFibObjectTrue( NULL ), pFibObjectFalse( NULL ){
	
	if ( ifElement.pCondition != NULL ){
		setCondition( *(ifElement.pCondition) );
	}else{
		setCondition( cConditionFalse() );
	}
	updateAllCounters();
}


/**
 * The constructor for restoring a if-elementobject from an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node wher the fib -object is stored in
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
 * 	to restore fib-element, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 */
cIf::cIf( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables ):
		pCondition( NULL ),
		pFibObjectTrue( NULL ), pFibObjectFalse( NULL ){
	
	if ( pXmlElement == NULL ){
		//noting to restore
		outStatus = -1;
		return;
	}
	string szElementType( pXmlElement->Value() );
	if ( szElementType != "if" ){
		//wrong element type to restore
		outStatus = -2;
		return;
	}
	
	for ( const TiXmlNode * pChild = pXmlElement->FirstChild();
			pChild != NULL; pChild = pChild->NextSibling() ) {
		
		int iType = pChild->Type();
		
		switch ( iType ){
			case TiXmlNode::ELEMENT:{
				/*check if this is a valid fib-element xml -element, create
				the apropirate fib-element and call its restoreXml() method*/
				const TiXmlElement * pXmlElement = pChild->ToElement();
				if ( pXmlElement == NULL ){
					outStatus = 2;
					continue;
				}
				string szElementType( pXmlElement->Value() );

				if ( szElementType == "condition" ){
					//restore the condition
					pXmlElement = pXmlElement->FirstChildElement();
					if ( (pCondition == NULL) && (pXmlElement != NULL) ){
						
						pCondition = cCondition::restoreXml(
							pXmlElement, outStatus, liDefinedVariables, NULL, this );
						if ( outStatus < 0 ){
							//an error occured
							return;
						}
					}else{//to many underobjects -> no correct area element
						outStatus = 2;
						continue;
					}
				}else{//restore the subobjects
					if ( pFibObjectTrue == NULL ){
						//every subobject has it's own variables
						list<cFibVariable*> liDefinedVariablesCopy( liDefinedVariables );
						
						pFibObjectTrue = cFibElement::restoreXml(
							pChild, outStatus, liDefinedVariablesCopy );
#ifdef FEATURE_FAST_UPDATE
						if ( pFibObjectTrue ){
							pFibObjectTrue->pSuperiorElement = this;
						}
#endif //FEATURE_FAST_UPDATE
						if ( outStatus < 0 ){
							//an error occured
							return;
						}
						fibUnderObjects.push_front( pFibObjectTrue );
					}else if ( pFibObjectFalse == NULL ){
						pFibObjectFalse = cFibElement::restoreXml(
							pChild, outStatus, liDefinedVariables );
#ifdef FEATURE_FAST_UPDATE
						if ( pFibObjectFalse ){
							pFibObjectFalse->pSuperiorElement = this;
						}
#endif //FEATURE_FAST_UPDATE
						if ( outStatus < 0 ){
							//an error occured
							return;
						}
						fibUnderObjects.push_back( pFibObjectFalse );
					}else{//to many underobjects -> no correct area element
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
				//invalid areaelement
				if ( outStatus ){
					outStatus = 2;
				}
				continue;
		}
	}
	if ( pCondition == NULL ){
		//no condition loaded
		outStatus = 2;
		setCondition( cConditionFalse() );
		return;
	}
	if ( ( pFibObjectTrue == NULL ) || ( pFibObjectFalse == NULL ) ){
		outStatus = -2;
		return;
	}
	updateAllCounters();
}


/**
 * This constructor restores a if-elementobject from the stream where it is
 * stored in the compressed fib -format.
 * This method is for internal use only.
 *
 * @param iBitStream the stream wher the if-elementobject is stored to in,
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
 * @param pNextRoot the next higher root -element for the to restore
 * 	fib-elements, or the last restored root -element
 */
cIf::cIf( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains,
		cRoot * pNextRoot ): pCondition( NULL ),
		pFibObjectTrue( NULL ), pFibObjectFalse( NULL ){
	
	DEBUG_OUT_L2(<<"constructor cIf() reading bit"<<endl);
	
	if ( ! iBitStream.getStream()->good() ){
		DEBUG_OUT_EL2(<<"stream not good"<<endl);
		outStatus = -1;
		return;
	}

	//set the defined variable value
	//restore the variablevalue
	//get the domain for the variables in this vector
	cTypeVariable typeVariable;
	//return the variable domain
	cDomainIntegerBasis * pDomainVariable = (cDomainIntegerBasis*)
		validDomains.getDomainForElement( typeVariable );
	bool bStandardDomainVariable = false;
	if ( pDomainVariable == NULL ){
		//use the standrad domain
		pDomainVariable = (cDomainIntegerBasis*)typeVariable.getStandardDomain();
		bStandardDomainVariable = true;
	}
	//restore the vectors for the underfunction
	cTypeUnderFunction typeUnderFunction;
	cDomainSingle * pDomainFunction = (cDomainSingle*)
		validDomains.getDomainForElement( typeUnderFunction );
	bool bStandardDomainFunction = false;
	if ( pDomainFunction == NULL ){
		pDomainFunction = (cDomainSingle*)
			typeUnderFunction.getStandardDomain();
		bStandardDomainFunction = true;
	}
	
	//restore the condition
	pCondition = cCondition::restore( iBitStream, outStatus,
		liDefinedVariables, pDomainFunction, pDomainVariable, NULL, this );
	
	if ( bStandardDomainVariable ){
		delete pDomainVariable;
	}
	if ( bStandardDomainFunction ){
		delete pDomainFunction;
	}
	if ( outStatus < 0 ){
		DEBUG_OUT_EL2(<<"Error: While loading condition"<<endl);
		return;
	}

	//restore the underobject
	DEBUG_OUT_L2(<<"restoring true case underobject"<<endl);
	
	//every subobject has it's own variables
	list<cFibVariable*> liDefinedVariablesCopy( liDefinedVariables );
	
	pFibObjectTrue = cFibElement::restoreInternal( iBitStream, outStatus,
		liDefinedVariablesCopy, validDomains, pNextRoot );
	
	fibUnderObjects.push_front( pFibObjectTrue );
#ifdef FEATURE_FAST_UPDATE
	if ( pFibObjectTrue ){
		pFibObjectTrue->pSuperiorElement = this;
	}
#endif //FEATURE_FAST_UPDATE
	//restore the underobject
	DEBUG_OUT_L2(<<"restoring false case underobject"<<endl);
	
	pFibObjectFalse = cFibElement::restoreInternal( iBitStream, outStatus,
		liDefinedVariables, validDomains, pNextRoot );
	
	fibUnderObjects.push_back( pFibObjectFalse );
#ifdef FEATURE_FAST_UPDATE
	if ( pFibObjectFalse ){
		pFibObjectFalse->pSuperiorElement = this;
	}
#endif //FEATURE_FAST_UPDATE
	
	updateAllCounters();
	DEBUG_OUT_L2(<<"constructor cIf() reading bit done"<<endl);
}


/**
 * desstructor
 */
cIf::~cIf(){
	
	if ( pCondition != NULL ){
		delete pCondition;
	}
}


/**
 * This method checks, if this Fib-element is an valid Fib-element.
 *
 * @return true if this Fib-element is an valid Fib-element, else false
 */
bool cIf::isValidFibElement() const{
	
	if ( fibUnderObjects.size() != 2 ){
		//no two underobjects
		return false;
	}
	if ( ( pFibObjectTrue == NULL ) || ( pFibObjectFalse == NULL ) ){
		//true or false case missing
		return false;
	}
	//check condition
	if ( pCondition == NULL ){
		//no condition
		return false;
	}
	if ( ! pCondition->isValid() ){
		//condition isn't valid -> if element not valid
		return false;
	}
	//everything if-specific is ok
	return cFibBranch::isValidFibElement();
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
char cIf::getType() const{

	return 'i';
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
bool cIf::evalueObject( iEvaluePosition & evaluePosition,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties ) const{
	
	if ( objectPoint == 0 ){
		if ( pCondition == NULL ){
			//no condition -> can't evalue if-element
			return false;
		}
		//evalue the underobject for the condition value
		if ( pCondition->getValue() ){
		
			if ( pFibObjectTrue == NULL ){
				//nothing to evalue
				return false;
			}
			return pFibObjectTrue->evalueObject( evaluePosition, objectPoint, liVecProperties );
		}//else false case
		if ( pFibObjectFalse == NULL ){
			//nothing to evalue
			return false;
		}
		return pFibObjectFalse->evalueObject( evaluePosition, objectPoint, liVecProperties );
	}else{//evalue on underobject
		//find the underobject to evalue
		unsignedIntFib uiRemainingObjectPoints = objectPoint;
		for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
			
			if ( (*actualUnderObject) != NULL ){
				
				unsignedIntFib uiActualObjectPoints =
					(*actualUnderObject)->getNumberOfObjectPoints() + 1;
				
				if ( uiRemainingObjectPoints <= uiActualObjectPoints ){
					//underobject to copy found
					return (*actualUnderObject)->evalueObject( evaluePosition,
						uiRemainingObjectPoints - 1, liVecProperties );
				}else{
					uiRemainingObjectPoints -= uiActualObjectPoints;
				}
			}
		}
		//no fib -object to evalue
		return false;
	}
	return true;
}


/**
 * This method evaluades the fib -object.
 * Evertime a fib-elements, with a type of the given type chars in
 * liCFibElementTyps, is reached while evaluation, it is given
 * back with the properties which it has.
 * Ever pointelement is given back. The type chars for pointelements
 * don't need to be in the list liCFibElementTyps.
 *
 * @param evalueFibElement a reference to the object with the
 * 	evalueElement() method to evalue /store the fib-elements and ther
 * 	properties; everytime a fib-element (with one of the type given
 * 	in liCFibElementTyps) is reached in the evaluation, the method
 * 	evalueElement() of this objects is called with the fib-element
 * 	and the properties of the fib-element; @see iEvalueFibElement
 * @param objectPoint the object point in the order of true partobjects
 * 	to evalue
 * @param liVecProperties a list with the property vectors which should
 * 	be global for the evalued object
 * @param liCFibElementTyps a list with the type chars (@see getType)
 * 	of the fib-elements to return
 * @return if the evalueation was successfull true, else false
 */
bool cIf::evalueObject( iEvalueFibElement & evalueFibElement,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties,
		const list<char> & liCFibElementTyps ){
	
	//check if this fib-element should be given back with evalueElement()
	for ( list<char>::const_iterator itrCType = liCFibElementTyps.begin();
			itrCType != liCFibElementTyps.end(); itrCType++ ){
		
		if ( *itrCType == getType() ){
			//call evalueElement() with this element
			return evalueFibElement.evalueElement( *this, liVecProperties );
		}
	}//else if this element shouldn't be returned -> evalue the main -fib -object

	if ( objectPoint == 0 ){
		if ( pCondition == NULL ){
			//no condition -> can't evalue if-element
			return false;
		}
		//evalue the underobject for the condition
		if ( pCondition->getValue() ){
			
			if ( pFibObjectTrue == NULL ){
				//nothing to evalue
				return false;
			}
			return pFibObjectTrue->evalueObject( evalueFibElement, objectPoint,
				liVecProperties, liCFibElementTyps );
		}//else false case
		if ( pFibObjectFalse == NULL ){
			//nothing to evalue
			return false;
		}
		return pFibObjectFalse->evalueObject( evalueFibElement, objectPoint,
			liVecProperties, liCFibElementTyps );
	}else{//evalue on underobject
		//find the underobject to evalue
		unsignedIntFib uiRemainingObjectPoints = objectPoint;
		for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
			
			if ( (*actualUnderObject) != NULL ){
				
				unsignedIntFib uiActualObjectPoints =
					(*actualUnderObject)->getNumberOfObjectPoints() + 1;
				
				if ( uiRemainingObjectPoints <= uiActualObjectPoints ){
					//underobject to copy found
					return (*actualUnderObject)->evalueObject( evalueFibElement,
						uiRemainingObjectPoints - 1, liVecProperties,
						liCFibElementTyps );
				}else{
					uiRemainingObjectPoints -= uiActualObjectPoints;
				}
			}
		}
		//no fib -object to evalue
		return false;
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
unsignedLongFib cIf::getTimeNeed( unsignedLongFib lMaxTime ) const{
	
	if ( lMaxTime == 1 ){
		return lMaxTime;
	}

	unsignedLongFib ulTimeNeeded = 0;

	//evalue the underobject for the if-element
	if ( pCondition ){
		if ( lMaxTime == 0 ){
			ulTimeNeeded += pCondition->getTimeNeed( 0 );
		}else{
			ulTimeNeeded += pCondition->getTimeNeed( lMaxTime - ulTimeNeeded );
			if ( lMaxTime <= ulTimeNeeded ){
				return lMaxTime;
			}
		}
	}//else no condition
	
	//evalue the underobject for the if-element
	const bool bConditionValue = pCondition->getValue();
	if ( bConditionValue ){
		if ( pFibObjectTrue == NULL ){
			//nothing to evalue
			return ulTimeNeeded;
		}
	}else{
		if ( pFibObjectFalse == NULL ){
			//nothing to evalue
			return ulTimeNeeded;
		}
	}
	if ( lMaxTime == 0 ){
		if ( bConditionValue ){
			ulTimeNeeded += pFibObjectTrue->getTimeNeed( 0 );
		}else{//false case
			ulTimeNeeded += pFibObjectFalse->getTimeNeed( 0 );
		}
	}else{
		if ( bConditionValue ){
			ulTimeNeeded += pFibObjectTrue->getTimeNeed(
				lMaxTime - ulTimeNeeded );
		}else{// false case
			ulTimeNeeded += pFibObjectFalse->getTimeNeed(
				lMaxTime - ulTimeNeeded );
		}
		if ( lMaxTime <= ulTimeNeeded ){
			return lMaxTime;
		}
	}
	return ulTimeNeeded;
}


/**
 * This method evaluades the size of the Fib-object in bits in the
 * compressed file form.
 * The optionalpart field of if-elements will be ignored.
 *
 * @see store()
 * @return the size of the Fib-object in bits in the compressed form
 */
unsignedLongFib cIf::getCompressedSize() const{
	
	unsignedLongFib ulCompressedSize = 4;

	//add compressed size for the condition
	if ( pCondition ){
		ulCompressedSize += pCondition->getCompressedSize();
	}
	//add compressed size for the underobject
	if ( pFibObjectTrue != NULL ){
		ulCompressedSize += pFibObjectTrue->getCompressedSize();
	}
	if ( pFibObjectFalse != NULL ){
		ulCompressedSize += pFibObjectFalse->getCompressedSize();
	}
	return ulCompressedSize;
}


/**
 * This method checks if the given variable is used in the given
 * direction from this fib-element.
 *
 * @see cFibVariable
 * @see isDefinedVariable()
 * @param variable the variable to check if it is used
 * @param direction the direction from this fib-element, in which the
 * 	variable should be used; standardvalue is ED_POSITION so yust
 * 	this fib-element will be checked
 * @return true if the variable is used, else false
 */
bool cIf::isUsedVariable( const cFibVariable *variable ,
		edDirection direction ) const{
	
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		//check condition
		if ( pCondition ){
		
			const bool bVariableUsed = pCondition->isUsedVariable( variable );
			if ( bVariableUsed ){
				return true;
			}
		}
	}
	return cFibBranch::isUsedVariable( variable, direction );
}


/**
 * This method returns all variables used in the given direction from
 * this fib-element.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @see isDefinedVariable()
 * @param direction the direction from this fib-element, in which the
 * 	variable should be used; standardvalue is ED_POSITION so yust
 * 	this fib-element will be checked
 * @return the set with all variables used in the given direction from
 * 	this fib-element
 */
set<cFibVariable*> cIf::getUsedVariables( edDirection direction ){
	
	set<cFibVariable*> setUsedVariables;
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		//check condition
		if ( pCondition ){
			
			set<cFibVariable*> setUsedVariableCondition =
				pCondition->getUsedVariables();
			
			setUsedVariables.insert( setUsedVariableCondition.begin(),
				setUsedVariableCondition.end() );
		}
	}
	
	set<cFibVariable*> setUsedVariableRest = cFibBranch::getUsedVariables( direction );
	setUsedVariables.insert( setUsedVariableRest.begin(),
		setUsedVariableRest.end() );

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
bool cIf::replaceVariable( cFibVariable *variableOld,
		cFibVariable *variableNew ){
	
	if ( (variableOld == NULL) || (variableNew == NULL) ){
		//can't replace
		return false;
	}
	//replace in condition
	if ( pCondition ){
		
		//replace variable in areavector
		if ( ! pCondition->replaceVariable( variableOld, variableNew ) ){
			return false;
		}
	}
	return cFibBranch::replaceVariable( variableOld, variableNew );
}


/**
 * This method copies the fib-element on the specified position.
 * Variables which are not defined in the fib-element but used
 * don't change ther reference.
 *
 * @see getType()
 * @param cType the type of the fib-element to copy
 * @param elementPoint the number of the fib-element, in the order of
 * 	Fib-elements of the given type cType, to copy
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	fib -object
 * @return the copy of the fib-element
 */
cFibElement * cIf::copyElement( const char cType, const unsignedIntFib
		elementPoint, bool bAbsolute ) const{
	
	if ( elementPoint == 0 ){
		//copy this element
		return new cIf( *this );
	}//else get the fib-element and copy it
	
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
bool cIf::assignValues( const cFibElement & fibElement ){
	
	if ( fibElement.getType() != getType() ){
		//both Fib elements not of the same type -> can't assign values
		return false;
	}
	if ( equalElement( fibElement, false ) ){
		//elements already equal -> don't need to assign anything
		return true;
	}
	const cIf * pOtherIf = ((const cIf*)(&fibElement));
	const cCondition * pOtherCondition =
		pOtherIf->pCondition;
	if ( pOtherCondition == NULL ){
		//set the condition of this if element to the null pointer NULL
		if ( pCondition ){
			//delete old condition
			delete pCondition;
			pCondition = NULL;
		}
		return true;
	}
	
	//try to match used variables
	const set< cFibVariable* > setUsedVariables = (const_cast< cCondition * >(
		pOtherCondition))->getUsedVariables();
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
	//copy condition of other if
	if ( pCondition ){
		//delete old condition
		delete pCondition;
	}
	pCondition = pOtherCondition->clone( NULL, this );
	
	if ( ! liVariablesToReplace.empty() ){
		//replace variables to replace
		for ( list< pair< cFibVariable * ,cFibVariable * > >::iterator
				itrActualVariable = liVariablesToReplace.begin();
				itrActualVariable != liVariablesToReplace.end(); itrActualVariable++ ){
			
			//replace variable in condition
			if ( ! pCondition->replaceVariable(
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
bool cIf::equalInternal( const cFibElement & fibObject,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{

	if ( getType() != fibObject.getType() ){
		//not the same element type
		return false;
	}
	const cIf * pIf = ((cIf*)(&fibObject));
	
	if ( ! equalElementInternal( fibObject,
			mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
		return false;
	}
	
	if ( fibUnderObjects.size() != pIf->fibUnderObjects.size() ){
		//not the same number of underobjects
		return false;
	}
	if ( (pFibObjectTrue == NULL) || (pIf->pFibObjectTrue == NULL)){
		if ( pFibObjectTrue != pIf->pFibObjectTrue ){
			//one but not both underobjects are NULL
			return false;
		}
	}else{
		if ( ! pFibObjectTrue->equalInternal( *(pIf->pFibObjectTrue),
				mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
			//both underobjects are not equal
			return false;
		}
	}
	if ( (pFibObjectFalse == NULL) || (pIf->pFibObjectFalse == NULL)){
		if ( pFibObjectFalse != pIf->pFibObjectFalse ){
			//one but not both underobjects are NULL
			return false;
		}
	}else{
		if ( ! pFibObjectFalse->equalInternal( *(pIf->pFibObjectFalse),
				mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
			//both underobjects are not equal
			return false;
		}
	}
	return true;
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
bool cIf::equalElementInternal( const cFibElement & fibElement,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{

	if ( getType() != fibElement.getType() ){
		return false;
	}
	cIf * pIfElement = (cIf*)(&fibElement);
	
	if ( pCondition ){
		if ( pIfElement->pCondition == NULL ){
			return false;
		}
		if ( ! pCondition->equalInternal( * (pIfElement->pCondition),
				mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
			return false;
		}
	}else{// pCondition == NULL
		if ( pIfElement->pCondition != NULL ){
			return false;
		}
	}
	return true;
}

#else //FEATURE_EQUAL_FIB_OBJECT

/**
 * This method checks if the given Fib-object is equal to this Fib
 * -object.
 * Variables can be others, but must be defined and used in equivalent
 * fib-elements.
 *
 * @param fibObject the Fib-object to which this Fib-object should be
 * 	equal
 * @return true if this Fib-object is equal to the given Fib-object,
 * 	else false
 */
bool cIf::equal( const cFibElement & fibObject ) const{

	if ( getType() != fibObject.getType() ){
		//not the same element type
		return false;
	}
	const cIf * pIf = ((cIf*)(&fibObject));
	if ( fibUnderObjects.size() != pIf->fibUnderObjects.size() ){
		//not the same number of underobjects
		return false;
	}
	if ( (pFibObjectTrue == NULL) || (pIf->pFibObjectTrue == NULL)){
		if ( pFibObjectTrue != pIf->pFibObjectTrue ){
			//one but not both underobjects are NULL
			return false;
		}
	}else{
		if ( ! pFibObjectTrue->equal( *(pIf->pFibObjectTrue) ) ){
			//both underobjects are not equal
			return false;
		}
	}
	if ( (pFibObjectFalse == NULL) || (pIf->pFibObjectFalse == NULL)){
		if ( pFibObjectFalse != pIf->pFibObjectFalse ){
			//one but not both underobjects are NULL
			return false;
		}
	}else{
		if ( ! pFibObjectFalse->equal( *(pIf->pFibObjectFalse) ) ){
			//both underobjects are not equal
			return false;
		}
	}
	return equalElement( fibObject );
}


/**
 * This method checks if the given fib-element is equal to this fib
 * -element.
 * The underobjects arn't compared, not even ther count is compared.
 * Used variables can be others.
 *
 * @param fibElement the fib-element to which this fib-element should be
 * 	equal
 * @return true if this fib-element is equal to the given fib -object,
 * 	else false
 */
bool cIf::equalElement( const cFibElement & fibElement ) const{

	if ( getType() != fibElement.getType() ){
		return false;
	}
	cIf * pIfElement = (cIf*)(&fibElement);
	
	if ( pCondition ){
		if ( pIfElement->pCondition == NULL ){
			return false;
		}
		if ( ! pCondition->equal( * (pIfElement->pCondition) ) ){
			return false;
		}
	}else{// pCondition == NULL
		if ( pIfElement->pCondition != NULL ){
			return false;
		}
	}
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
bool cIf::storeXml( ostream & stream ) const{

	bool bReturnValue = true;
	
#ifdef FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	stream<<"<if elementNr=\""<<getNumberOfElement()<<"\">"<<endl;
#else //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	stream<<"<if>"<<endl;
#endif //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	if ( pCondition ){
		stream<<"<condition>"<<endl;
		//store subareas
		if ( ! pCondition->storeXml( stream ) ){
			return false;
		}
		stream<<"</condition>"<<endl;
	}
	if ( pFibObjectTrue ){
		bReturnValue &= pFibObjectTrue->storeXml( stream );
	}
	if ( pFibObjectFalse ){
		bReturnValue &= pFibObjectFalse->storeXml( stream );
	}
	stream<<"</if>"<<endl;
	return bReturnValue;
}



/**
 * This method inserts the given Fib-element pFibElement on the
 * specified position. The replaced Fib-element will be the underobject
 * of the inserted Fib-element pFibElement.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see getType()
 * @param cType the type of the Fib-element insted of which the given
 * 	Fib-element pFibElement should be inserted
 * @param elementPoint the number of the Fib-element, in the order of
 * 	Fib-elements of the given type cType, in which position the given
 * 	Fib-element pFibElement should be inserted; if 0 the given
 * 	pFibElement will be inserted under this Fib-element
 * @param pFibElement the Fib-element to insert
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib-object
 * @param bCheckVariables if true (standardvalue) it will be checked if
 * 	the variables the Fib-element defines are needed, else the 
 * 	Fib-element will be removed even if its variables are needed elsewher
 * @return true if the Fib-element pFibElement was inserted, else false
 */
bool cIf::insertElement( cFibElement *pFibElement, const char cType,
		const unsignedIntFib elementPoint, bool bAbsolute, bool bCheckVariables ){
	
	if ( pFibElement == NULL ){
		//nothing to insert
		return false;
	}
	if ( (pFibElement->getType() == 'r') ||
			(pFibElement->getType() == 'l') ||
			(pFibElement->getType() == 'i') ){
		//can't insert root, list or if-elements
		return false;
	}
	if ( pFibElement->getNumberOfElements() != 1 ){
		//more then one Fib-element to insert
		return false;
	}
#ifdef FEATURE_FAST_UPDATE
	if ( ! cFibObjectCounts::isValidType( cType ) ){
		return false;
	}
#endif //FEATURE_FAST_UPDATE
	
	if ( elementPoint == 0 ){
		//replace the (first) underobject of this Fib-element
		if ( ( fibUnderObjects.empty() ) ||
				( fibUnderObjects.front() == NULL ) ){
			//check if the variables used in the to insert Fib-element are defined higer
			if ( bCheckVariables && ( ! variablesAreDefined( pFibElement->
					getUsedVariables( ED_POSITION ) , ED_HIGHER_EQUAL ) ) ){
				return false;
			}
#ifdef FEATURE_FAST_UPDATE
			cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( pFibElement );;
#endif //FEATURE_FAST_UPDATE
			if ( fibUnderObjects.empty() ){
				fibUnderObjects.push_front( pFibElement );
#ifdef FEATURE_FAST_UPDATE
				fibObjectCountsDelta.uiNumberOfObjectpoints++;
#endif //FEATURE_FAST_UPDATE
			}else{//( fibUnderObjects.front() == NULL )
				fibUnderObjects.front() = pFibElement;
			}
			pFibObjectTrue = pFibElement;
#ifdef FEATURE_FAST_UPDATE
			if ( pFibElement->pSuperiorElement != NULL ){
				pFibElement->pSuperiorElement->cutConnectionsTo(
					pFibElement );
			}
			pFibElement->pSuperiorElement = this;
			//update counters
			updateAllCounters( fibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
			updateAllValues();
#endif //FEATURE_FAST_UPDATE
			return true;
		}
		return insertElement( pFibElement, 'u', 2, false, bCheckVariables );
	}
	if ( bAbsolute ){
		return getMasterRoot()->insertElement( pFibElement, cType, elementPoint,
			false, bCheckVariables );
	}//else elementPoint is an relative value
//#define FEATURE_FIB_ELEMENT_LAST_INSERT
#ifdef FEATURE_FIB_ELEMENT_LAST_INSERT
//This FEATURE didn't work correct and is logical not sound
	
	cFibElement * pFibElementToReplace = getFibElement( cType, elementPoint );
	if ( pFibElementToReplace == NULL ){
		if ( ( ! pFibElement->isLeaf() ) && ( pFibElement->getType() != 'o' )  ){
			//no Fib-element to replace
			return false;
		}
		//try to insert in the last last Fib element
		cFibElement * pLastFibElement = getFibElement( getNumberOfElements() );
		if ( pLastFibElement == this ){
			if ( 2 <= fibUnderObjects.size() ){
				//can't insert more underobjects
				return false;
			}
			//check if the variables used in the to insert Fib-element are defined higer
			if ( bCheckVariables &&( ! variablesAreDefined( pFibElement->
					getUsedVariables( ED_POSITION ) , ED_HIGHER_EQUAL ) ) ){
				return false;
			}
			//insert the leafelement into this branchelement
			fibUnderObjects.push_back( pFibElement );
			pFibObjectTrue  = fibUnderObjects.front();
			pFibObjectFalse = fibUnderObjects.back();
			
#ifdef FEATURE_FAST_UPDATE
			if ( pFibElement->pSuperiorElement != NULL ){
				pFibElement->pSuperiorElement->cutConnectionsTo(
					pFibElement );
			}
			pFibElement->pSuperiorElement = this;
			//update counters
			cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( pFibElement );
			fibObjectCountsDelta.uiNumberOfObjectpoints++;
			updateAllCounters( fibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
			updateAllValues();
#endif //FEATURE_FAST_UPDATE
			return true;
		}
		return pLastFibElement->insertElement( pFibElement, 'u', 0, false, bCheckVariables );
	}
	
	if ( (pFibElementToReplace != NULL) &&
			( pFibElementToReplace->getType() == 'r') ){
		//no Fib-element to replace
		return false;
	}
#else //FEATURE_FIB_ELEMENT_LAST_INSERT
	cFibElement * pFibElementToReplace = getFibElement( cType, elementPoint );
	if ( ( (pFibElementToReplace == NULL) && ( ! pFibElement->isLeaf() ) &&
				( pFibElement->getType() != 'o' ) ) ||
			( (pFibElementToReplace != NULL) &&
				( pFibElementToReplace->getType() == 'r') ) ){
		//no Fib-element to replace
		return false;
	}
#endif //FEATURE_FIB_ELEMENT_LAST_INSERT

	/*check ( if (cType=='u') ) if the pFibElement should replace a
	underobject of this object*/
	if ( cType == 'u' ){
		if ( elementPoint == 2 ){
			//insert the pFibElement in this if-element
			if ( pFibElement->isLeaf() ){
				if ( 2 <= fibUnderObjects.size() ){
					//can't insert more underobjects
					return false;
				}
				//check if the variables used in the to insert Fib-element are defined higer
				if ( bCheckVariables &&( ! variablesAreDefined( pFibElement->
						getUsedVariables( ED_POSITION ) , ED_HIGHER_EQUAL ) ) ){
					return false;
				}
				//insert the leafelement into this branchelement
				fibUnderObjects.push_back( pFibElement );
				pFibObjectTrue  = fibUnderObjects.front();
				pFibObjectFalse = fibUnderObjects.back();
				
#ifdef FEATURE_FAST_UPDATE
				if ( pFibElement->pSuperiorElement != NULL ){
					pFibElement->pSuperiorElement->cutConnectionsTo(
						pFibElement );
				}
				pFibElement->pSuperiorElement = this;
				//update counters
				cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( pFibElement );
				fibObjectCountsDelta.uiNumberOfObjectpoints++;
				updateAllCounters( fibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
				updateAllValues();
#endif //FEATURE_FAST_UPDATE
				return true;
			}
		}
		for ( list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
			
			if ( (*actualUnderObject) != NULL ){
#ifdef FEATURE_FAST_UPDATE
				if ( (*actualUnderObject) == pFibElementToReplace ){
#else //FEATURE_FAST_UPDATE
				if ( ((*actualUnderObject)->getNumberOfElement()) ==
						pFibElementToReplace->getNumberOfElement() ){
#endif //FEATURE_FAST_UPDATE
					//replace the actualUnderObject with the given pFibElement
					
					//check if the variables used in the to insert Fib-element are defined higer
					if ( bCheckVariables &&( ! variablesAreDefined(
							pFibElement->getUsedVariables( ED_POSITION ), ED_HIGHER_EQUAL ) ) ){
						return false;
					}
#ifdef FEATURE_FAST_UPDATE
					if ( pFibElement->isLeaf() ){

						if ( 2 <= fibUnderObjects.size() ){
							//can't insert more underobjects
							return false;
						}
						if ( pFibObjectTrue == NULL ){
							fibUnderObjects.push_front( pFibElement );
							pFibObjectTrue = pFibElement;
						}else if ( pFibObjectFalse == NULL ){
							fibUnderObjects.push_back( pFibElement );
							pFibObjectFalse = pFibElement;
						}else{//can't insert more underobjects
							return false;
						}
						
						if ( pFibElement->pSuperiorElement != NULL ){
							pFibElement->pSuperiorElement->cutConnectionsTo(
								pFibElement );
						}
						pFibElement->pSuperiorElement = this;
						//update counters
						cFibObjectCounts fibObjectCountsDelta;
						fibObjectCountsDelta.vecNumberOfFibElements[
							cFibObjectCounts::elementTypeToIndex( pFibElement->getType() ) ]++;
						fibObjectCountsDelta.vecNumberOfFibElements[ cFibObjectCounts::ALL ]++;
						fibObjectCountsDelta.uiNumberOfObjectpoints++;
						updateAllCounters( fibObjectCountsDelta );
						//done and pFibElement inserted
						return true;
					}//else not a leaf
					//set the underobject of the pFibElement
					(*actualUnderObject)->pSuperiorElement = NULL;
					const bool bUnderObjectReplaced =
						pFibElement->insertObjectInElement( (*actualUnderObject) );
					if ( ! bUnderObjectReplaced ){
						//can't replace the underobject
						return false;
					}
					cFibObjectCounts fibObjectCountsDelta;
					fibObjectCountsDelta -= evalueCountersForObject( (*actualUnderObject) );
					//set the new underobject of this element
					(*actualUnderObject) = pFibElement;
					pFibObjectTrue  = fibUnderObjects.front();
					pFibObjectFalse = fibUnderObjects.back();
					if ( pFibElement->pSuperiorElement != NULL ){
						pFibElement->pSuperiorElement->cutConnectionsTo(
							pFibElement );
					}
					pFibElement->pSuperiorElement = this;
					//update counters
					fibObjectCountsDelta += evalueCountersForObject( (*actualUnderObject) );
					
					updateAllCounters( fibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
					if ( pFibElement->isLeaf() ){
						fibUnderObjects.insert( actualUnderObject, pFibElement );
						updateAllValues();
						//done and pFibElement inserted
						return true;
					}
					//set the underobject of the pFibElement
					const bool bUnderObjectReplaced =
						pFibElement->insertObjectInElement( (*actualUnderObject) );
					if ( ! bUnderObjectReplaced ){
						//can't replace the underobject
						return false;
					}
					//set the new underobject of this element
					(*actualUnderObject) = pFibElement;
					updateAllValues();
#endif //FEATURE_FAST_UPDATE
					//done and pFibElement inserted
					return true;
				}
			}//end if (actualUnderObject!=NULL )
		}//end for
	}
	
	/*get the pSuperiorElement of the to replacing object and call
	insertElement of theas*/
	if ( (pFibElementToReplace != NULL) &&
			( pFibElementToReplace->pSuperiorElement != NULL ) ){
			
		return pFibElementToReplace->pSuperiorElement->insertElement(
			pFibElement, 'u', (pFibElementToReplace->getNumberOfElement()) + 1 -
			(pFibElementToReplace->pSuperiorElement->getNumberOfElement() ),
			false, bCheckVariables );
		
	}//else the to replace Fib-element dosn't exists or is the topmost
	return false;
}


/**
 * This method inserts the given Fib-object fibObject on the
 * specified position. On the specified position a listelement will
 * be inserted, with the old Fib-object and the given Fib-object
 * fibObject as its underobjects.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see overwriteObjectWithObject()
 * @see getType()
 * @param cType the type of the Fib-element, on which position the 
 * 	given Fib-object fibObject should be inserted
 * @param elementPoint the number of the Fib-element, in the order of
 * 	Fib-elements of the given type cType, on which position the given
 * 	Fib-object fibObject should be inserted
 * @param fibObject the Fib-object to insert
 * @param first if true, the inserted object will be the first
 * 	underobject of the new listelement
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib-object
 * @return true if the Fib-object fibObject was inserted, else false
 */
bool cIf::insertObjectInElement( cFibElement *fibObject, const char cType,
		const unsignedIntFib elementPoint, bool first, bool bAbsolute ){
	
	if ( fibObject == NULL ){
		//nothing to insert
		return false;
	}
	if ( fibObject->getType() == 'r' ){
		//can't insert a root -element
		return false;
	}
#ifdef FEATURE_FAST_UPDATE
	if ( ! cFibObjectCounts::isValidType( cType ) ){
		return false;
	}
#endif //FEATURE_FAST_UPDATE

	if ( elementPoint == 0 ){
		//insert for the (first) underobject of this Fib-element

		if ( fibUnderObjects.empty() ){
			//insert in this branchelement
			fibUnderObjects.push_front( fibObject );
			pFibObjectTrue = fibObject;
#ifdef FEATURE_FAST_UPDATE
			if ( fibObject->pSuperiorElement != NULL ){
				fibObject->pSuperiorElement->cutConnectionsTo(
					fibObject );
			}
			fibObject->pSuperiorElement = this;
			
			cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( fibObject );
			fibObjectCountsDelta.uiNumberOfObjectpoints++;
			updateAllCounters( fibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
			updateAllValues();
#endif //FEATURE_FAST_UPDATE
			//done with inserting
			return true;
		}else{
			//check if the underobject to overwrite is NULL
			list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
			
			if ( ! first ){
				actualUnderObject++;
			}
			if ( (*actualUnderObject) == NULL ){
				//overwrite the actualUnderObject NULL object
				
				//set the values of the fibObject
#ifdef FEATURE_FAST_UPDATE
				if ( fibObject->pSuperiorElement != NULL ){
					fibObject->pSuperiorElement->cutConnectionsTo(
						fibObject );
				}
				fibObject->pSuperiorElement = this;
				(*actualUnderObject) = fibObject;
				pFibObjectTrue  = fibUnderObjects.front();
				pFibObjectFalse = fibUnderObjects.back();
				
				cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( fibObject );
				fibObjectCountsDelta.uiNumberOfObjectpoints++;
				updateAllCounters( fibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
				fibObject->pSuperiorElement = this;
				(*actualUnderObject) = fibObject;
				
				updateAllValues();
#endif //FEATURE_FAST_UPDATE
				//done with inserting
				return true;
			}
		}
		return insertObjectInElement( fibObject, 'u', 2, first );
	}
	
	if ( bAbsolute ){
		return getMasterRoot()->insertObjectInElement( fibObject, cType, elementPoint, first );
	}//else elementPoint is an relative value

	/*check ( if (cType=='u') ) if the fibObject should inserted as an
	neibour of an underobject of this object*/
	cFibElement * pFibElementPosition = getFibElement( cType, elementPoint );
	if ( (pFibElementPosition == NULL) || (pFibElementPosition->getType() == 'r')){
		//no position to insert
		return false;
	}
	if ( cType == 'u' ){
		if ( pFibElementPosition->pSuperiorElement == this ){
			if ( fibUnderObjects.size() < 2 ){
				//can add an underobject
				
				if ( fibUnderObjects.front() != NULL ){
					if ( fibUnderObjects.front() == pFibElementPosition ){
						//insert the given fibObject
						
						//set the values of the fibObject
						if ( fibObject->pSuperiorElement != NULL ){
							fibObject->pSuperiorElement->cutConnectionsTo(
								fibObject );
						}
						fibObject->pSuperiorElement = this;
						
						if ( first ){
							//insert fibObject instead of the actualUnderObject
							fibUnderObjects.push_front( fibObject );
						}else{
							//insert fibObject after the actualUnderObject
							fibUnderObjects.push_back( fibObject );
						}
						pFibObjectTrue  = fibUnderObjects.front();
						pFibObjectFalse = fibUnderObjects.back();
	
						cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( fibObject );
						fibObjectCountsDelta.uiNumberOfObjectpoints++;
						updateAllCounters( fibObjectCountsDelta );
						//done and fibElement inserted
						return true;
					}else{//Error
						return false;
					}
				}else{//if (actualUnderObject == NULL )
					fibUnderObjects.front() = fibObject;
					
					pFibObjectTrue  = fibUnderObjects.front();
					pFibObjectFalse = fibUnderObjects.back();

					cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( fibObject );
					fibObjectCountsDelta.uiNumberOfObjectpoints++;
					updateAllCounters( fibObjectCountsDelta );
					//done and fibElement inserted
					return true;
				}
			}else{// ( 2 <= fibUnderObjects.size() )
				//cant insert in this if-element
				return false;
			}
		}//end insert in this if-element
	}
	/*get the pSuperiorElement of the to insering objectposition and call
	insertElement of theas*/
	if ( pFibElementPosition->pSuperiorElement != NULL ){
			
			return pFibElementPosition->pSuperiorElement->insertObjectInElement(
				fibObject, 'u',
				(pFibElementPosition->getNumberOfElement()) + 1 -
				(pFibElementPosition->pSuperiorElement->getNumberOfElement() ),
				first );
			
	}//else the to insert position dosn't exists or is the topmost
	return false;
}



/**
 * This method overwrites the Fib -object on specified position with
 * the given Fib -object fibObject. The Fib -object on specified
 * position will be replaced with the given Fib -object fibObject.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see insertObjectInElement()
 * @see getType()
 * @param cType the type of the Fib -element, on which position the 
 * 	given Fib -object fibObject should be inserted
 * @param elementPoint the number of the Fib -element, in the order of
 * 	Fib -elements of the given type cType, on which position the given
 * 	Fib -object fibObject should be inserted
 * @param fibObject the Fib -object to insert
 * @param bDeleteOld if true, delete the old Fib -object from the memory
 * @param bAbsolute if the elementPoint is an absolute value for the wool
 * 	Fib-object
 * @return true if the old Fib -object was overwritten and the given 
 * 	Fib -object fibObject was inserted, else false
 */
bool cIf::overwriteObjectWithObject( cFibElement *fibObject,
		const char cType, const unsignedIntFib elementPoint,
		bool bDeleteOld, bool bAbsolute ){

	if ( fibObject == NULL ){
		//nothing to insert
		return false;
	}
	if ( fibObject->getType() == 'r' ){
		//can't insert a root -element
		return false;
	}
	if ( ! cFibObjectCounts::isValidType( cType ) ){
		return false;
	}

	if ( elementPoint == 0 ){
		//insert for the (first) underobject of this Fib-element
		
		//check if the underobject to overwrite is NULL
		if ( fibUnderObjects.front() == NULL ){
			//overwrite the actualUnderObject NULL object
			
			//set the values of the fibObject
			if ( fibObject->pSuperiorElement != NULL ){
				fibObject->pSuperiorElement->cutConnectionsTo(
					fibObject );
			}
			fibObject->pSuperiorElement = this;
		
			fibUnderObjects.front() = fibObject;
			pFibObjectTrue = fibObject;
			
			cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( fibObject );
			fibObjectCountsDelta.uiNumberOfObjectpoints++;
			updateAllCounters( fibObjectCountsDelta );
			//done with inserting
			return true;
		}
		return overwriteObjectWithObject( fibObject, 'u', 2, bDeleteOld );
	}
	if ( bAbsolute ){
		return getMasterRoot()->overwriteObjectWithObject( fibObject, cType,
			elementPoint, bDeleteOld );
	}//else elementPoint is an relative value

	/*check ( if (cType=='u') ) if the fibObject should inserted as an
	neibour of an underobject of this object*/
	cFibElement * pFibElementPosition = getFibElement( cType, elementPoint );
	if ( (pFibElementPosition == NULL) || (pFibElementPosition->getType() == 'r') ){
		//no Fib-object to overwrite
		return false;
	}
	if ( cType == 'u' ){
		for ( list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
			
			if ( (*actualUnderObject) == pFibElementPosition ){
				//insert the given fibObject
				
				//set the values of the fibObject
				if ( fibObject->pSuperiorElement != NULL ){
					fibObject->pSuperiorElement->cutConnectionsTo(
						fibObject );
				}
				fibObject->pSuperiorElement = this;
				//insert fibObject instead of the actualUnderObject
				if ( (*actualUnderObject) == pFibObjectTrue ){
					//replace true case
					pFibObjectTrue  = fibObject;
				}else{//(*actualUnderObject) == pFibObjectFalse
					//replace false case
					pFibObjectFalse = fibObject;
				}
				(*actualUnderObject) = fibObject;
				
				//update the Fib-objectcounters
				cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( fibObject );
				const cFibObjectCounts fibObjectCountsOld =
					evalueCountersForObject( pFibElementPosition );
				fibObjectCountsDelta -= fibObjectCountsOld;
				updateAllCounters( fibObjectCountsDelta );
				
				//remove old underobject
				if ( pFibElementPosition->pSuperiorElement == this ){
					pFibElementPosition->pSuperiorElement = NULL;
					if ( bDeleteOld ){
						pFibElementPosition->deleteObject();
					}//else don't delete
				}
				//done and fibElement inserted
				return true;
			}
		}//end for
	}
	
	/*get the pSuperiorElement of the to insering objectposition and call
	insertElement of theas*/
	if ( pFibElementPosition->pSuperiorElement != NULL ){
			
			return pFibElementPosition->pSuperiorElement->overwriteObjectWithObject(
				fibObject, 'u', (pFibElementPosition->getNumberOfElement()) + 1 -
				(pFibElementPosition->pSuperiorElement->getNumberOfElement() ),
				bDeleteOld );
			
	}//else the to insert position dosn't exists or is the topmost
	return false;
}


/**
 * This method checks, if all Fib-elements of this Fib-object
 * have the underobjects they need to be correct.
 *
 * @return true if all Fib-elements of this Fib-object have the
 * 	underobjects they need to be correct, else false
 */
bool cIf::hasUnderAllObjects() const{

	//check all underobjects
	if ( ( fibUnderObjects.size() != 2 )
			|| ( pFibObjectTrue == NULL )
			|| ( pFibObjectFalse == NULL ) ){
		//the true or the false case is missing
		return false;
	}
	return cFibBranch::hasUnderAllObjects();
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
cFibElement * cIf::cutElement( const char cType, const unsignedIntFib
		elementPoint, bool bAbsolute, bool bCheckVariables ){

#ifdef FEATURE_FAST_UPDATE
	if ( ! cFibObjectCounts::isValidType( cType ) ){
		return NULL;
	}
#endif //FEATURE_FAST_UPDATE
	cFibElement * pFibElementToRemove = getFibElement( cType, elementPoint, bAbsolute );
	
	if ( (pFibElementToRemove == NULL) ||
			(pFibElementToRemove->pSuperiorElement == NULL)  ){
		return NULL;
	}
	if ( ! pFibElementToRemove->isRemovableElement( 'u', 0, false, bCheckVariables ) ){
		//can't remove the fib element
		return NULL;
	}//the element can be removed
	
	//check if the first element of an underobject should be removed
	for ( list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
		
		if ( (*actualUnderObject) != NULL ){
			//no underobject
			if ( (*actualUnderObject) == pFibElementToRemove ){
				cFibObjectCounts fibObjectCountsDelta;
				//Fib-element to remove found
				
				if ( pFibElementToRemove->getNumberOfElements() == 1 ){/*pFibElementToRemove has no underobjects
					->can't remove <- the fib-object/if-element will become invalit*/
					return NULL;
				}
				//pFibElementToRemove has underobjects to replace it
				(*actualUnderObject) = pFibElementToRemove->getNextFibElement();
			
				pFibObjectTrue  = fibUnderObjects.front();
				pFibObjectFalse = fibUnderObjects.back();
				
				if ( pFibElementToRemove->getNextFibElement() != NULL ){
					pFibElementToRemove->getNextFibElement()->pSuperiorElement = this;
				}
				if ( pFibElementToRemove->isBranch() ){
					/*a branch element with one subobject removed
					-> subtract one object point*/
					fibObjectCountsDelta.uiNumberOfObjectpoints--;
				}
#ifdef FEATURE_FAST_UPDATE
				fibObjectCountsDelta.vecNumberOfFibElements[
					cFibObjectCounts::elementTypeToIndex( pFibElementToRemove->getType() ) ]--;
				fibObjectCountsDelta.vecNumberOfFibElements[ cFibObjectCounts::ALL ]--;
				updateAllCounters( fibObjectCountsDelta );
				
				//clear values of cuted Fib-element
				pFibElementToRemove->cutConnectionsTo( this );
				pFibElementToRemove->cutConnectionsTo(
					pFibElementToRemove->getNextFibElement() );
#else //FEATURE_FAST_UPDATE
				updateAllValues();
				
				//clear values of cuted Fib-element
				pFibElementToRemove->cutConnections( ED_ALL );
#endif //FEATURE_FAST_UPDATE
				
				return pFibElementToRemove;
			}
		}
	}

	return pFibElementToRemove->pSuperiorElement->cutElement(  'u',
		pFibElementToRemove->getNumberOfElement() + 1 -
		pFibElementToRemove->pSuperiorElement->getNumberOfElement(),
		false, bCheckVariables );
}


/*
 * if-element methods
 */


/**
 * @return the condition of this if-element
 */
cCondition * cIf::getCondition() const{

	return pCondition;
}


/**
 * This method sets the given condition as the condition of
 * this if-element.
 * (The given condition is copied befor it is set.)
 *
 * @param condition a reference to the to set condition
 * @return true if the condition was set, else false
 */
bool cIf::setCondition( const cCondition & condition ){

	if ( ( & condition ) != NULL ){
		
		if ( pCondition != NULL ){
			delete pCondition;
		}
		pCondition = condition.clone( NULL, this );
		return true;
	}//else
	return false;
}


/**
 * @return the true case of this if-element or NULL, if non exist
 */
cFibElement * cIf::getTrueCase(){

	return pFibObjectTrue;
}

/**
 * This method sets the given Fib-object as the true case for this
 * this if-element.
 *
 * @param fibObjectTrue the new true case Fib-object to set
 * @param bDeleteOld if true, delete the old Fib-object from the memory
 * @return true if the true case was set else false
 */
bool cIf::setTrueCase( cFibElement * fibObjectTrue, bool bDeleteOld ){

	if ( fibObjectTrue != NULL ){
		
		if ( ( pFibObjectTrue == fibUnderObjects.front() ) ||
				( 1 < fibUnderObjects.size() ) ){
			//remove true case from the underobjects
			fibUnderObjects.pop_front();
		}
		cFibObjectCounts fibObjectCountsDelta;
		if ( pFibObjectTrue != NULL ){
			//cut connection to this element
			if ( pFibObjectTrue->pSuperiorElement == this ){
				pFibObjectTrue->pSuperiorElement = NULL;
			}
			fibObjectCountsDelta -= evalueCountersForObject( pFibObjectTrue );
			if ( bDeleteOld ){
				pFibObjectTrue->deleteObject();
			}
		}else{//new underobject
			fibObjectCountsDelta.uiNumberOfObjectpoints++;
		}
		pFibObjectTrue = fibObjectTrue;
		fibUnderObjects.push_front( fibObjectTrue );
		//update counters
		if ( pFibObjectTrue->pSuperiorElement != NULL ){
			pFibObjectTrue->pSuperiorElement->cutConnectionsTo( pFibObjectTrue );
		}
		pFibObjectTrue->pSuperiorElement = this;
		fibObjectCountsDelta += evalueCountersForObject( pFibObjectTrue );
		updateAllCounters( fibObjectCountsDelta );
	
		return true;
	}//else
	return false;
}


/**
 * @return the false case of this if-element or NULL, if non exist
 */
cFibElement * cIf::getFalseCase(){

	return pFibObjectFalse;
}


/**
 * This method sets the given Fib-object as the false case for this
 * this if-element.
 *
 * @param fibObjectFalse the new false case Fib-object to set
 * @param bDeleteOld if true, delete the old Fib-object from the memory
 * @return true if the false case was set else false
 */
bool cIf::setFalseCase( cFibElement * fibObjectFalse, bool bDeleteOld ){

	if ( fibObjectFalse != NULL ){
		
		if ( ( pFibObjectFalse == fibUnderObjects.back() ) ||
				( 1 < fibUnderObjects.size() ) ){
			//remove true case from the underobjects
			fibUnderObjects.pop_back();
		}
		cFibObjectCounts fibObjectCountsDelta;
		if ( pFibObjectFalse != NULL ){
			//cut connection to this element
			if ( pFibObjectFalse->pSuperiorElement == this ){
				pFibObjectFalse->pSuperiorElement = NULL;
			}
			fibObjectCountsDelta -= evalueCountersForObject( pFibObjectFalse );
			if ( bDeleteOld ){
				pFibObjectFalse->deleteObject();
			}
		}else{//new underobject
			fibObjectCountsDelta.uiNumberOfObjectpoints++;
		}
		pFibObjectFalse = fibObjectFalse;
		fibUnderObjects.push_back( fibObjectFalse );
		//update counters
		if ( pFibObjectFalse->pSuperiorElement != NULL ){
			pFibObjectFalse->pSuperiorElement->cutConnectionsTo( pFibObjectFalse );
		}
		pFibObjectFalse->pSuperiorElement = this;
		fibObjectCountsDelta += evalueCountersForObject( pFibObjectFalse );
		updateAllCounters( fibObjectCountsDelta );
		
		return true;
	}//else
	return false;
}


/**
 * This method stores this Fib-object in the compressed Fib-format
 * into the given stream.
 * It is needed becouse the stream can yust store byts but the size of
 * fib-elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the fib-elements.
 * Beware: You need to call storeBit() of the root -elements with the
 * domain for the if-element or the if-element will not be readebel.
 *
 * @see store
 * @param stream the stream where this Fib-object should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if this Fib-object is stored, else false
 */
bool cIf::storeBit( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{

	if ( ( pFibObjectTrue == NULL ) || ( pFibObjectFalse == NULL ) ){
		return false;
	}
	char cInitiation = 0x0C;

	const bool bInitiationStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, &cInitiation, 4 );
	if ( ! bInitiationStored ){
		return false;
	}

	//store the condition
	if ( pCondition ){
		
		const bool bCoditionStored = pCondition->store(
			stream, cRestBits, uiRestBitPosition );
		if ( ! bCoditionStored ){
			return false;
		}
	}
	const bool bTrueCaseStored = pFibObjectTrue->storeBit(
		stream, cRestBits, uiRestBitPosition );
	if ( ! bTrueCaseStored ){
		return false;
	}
	return pFibObjectFalse->storeBit( stream, cRestBits, uiRestBitPosition );
}


/**
 * This method copies the connected object with the given number in the
 * order of connected objects.
 * For this every Fib-element, beginning from this Fib-element, that
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
cFibElement * cIf::copyInternal( const unsignedIntFib iObjectPoint ) const{

	if ( iObjectPoint == 0 ){
		//copy the whool object
		cIf * pIf = new cIf( *this );
		
		//copy every underobject and insert it in the new listelement
		for ( list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
			
			if ( (*actualUnderObject) != NULL ){
				
				cFibElement * pFibElement = (*actualUnderObject)->copyInternal();
#ifdef FEATURE_FAST_UPDATE
				if ( pFibElement ){
					pIf->fibUnderObjects.push_back( pFibElement );
					pFibElement->pSuperiorElement = pIf;
				}else{//ERROR while copying
					pIf->deleteObject();
					return NULL;
				}
#else //FEATURE_FAST_UPDATE
				if ( pFibElement ){
					pIf->fibUnderObjects.push_back( pFibElement );
				}else{//ERROR while copying
					pIf->updateAllValues();
					deleteObject( pList );
					return NULL;
				}
#endif //FEATURE_FAST_UPDATE
			}else{
				pIf->fibUnderObjects.push_back( NULL );
			}
		}
		//set true and false case if existing
		const unsigned char uiNumberOfUnderObjects = pIf->fibUnderObjects.size();
		if ( 1 <= uiNumberOfUnderObjects ){
			if ( uiNumberOfUnderObjects == 1 ){
				if ( pFibObjectTrue == fibUnderObjects.front() ){
					
					pIf->pFibObjectTrue  = pIf->fibUnderObjects.front();
				}else{//( pFibObjectFalse == fibUnderObjects.front() == fibUnderObjects.back() )
					pIf->pFibObjectFalse = pIf->fibUnderObjects.back();
				}
			}else{
				pIf->pFibObjectTrue  = pIf->fibUnderObjects.front();
				pIf->pFibObjectFalse = pIf->fibUnderObjects.back();
			}
		}
#ifdef FEATURE_FAST_UPDATE
		pIf->updateAllCounters();
#endif //FEATURE_FAST_UPDATE
		return pIf;
	}//else just copy one underobject and discard this listelement

	//find the underobject to copy
	unsignedIntFib uiRemainingObjectPoints = iObjectPoint;
	for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
		
		if ( (*actualUnderObject) != NULL ){
			
			unsignedIntFib uiActualObjectPoints =
				(*actualUnderObject)->getNumberOfObjectPoints() + 1;
			
			if ( uiRemainingObjectPoints <= uiActualObjectPoints ){
				//underobject to copy found
				return (*actualUnderObject)->copyInternal( uiRemainingObjectPoints - 1 );
			}else{
				uiRemainingObjectPoints -= uiActualObjectPoints;
			}
		}
	}
	//no underobject to copy found
	return NULL;
}


/**
 * This method syncronises the underobjects of this cIf-class with
 * the underobjectslist fibUnderObjects of the cFibBranch class.
 */
void cIf::syncSubobjects(){
	
	if ( 2 <= fibUnderObjects.size() ){
		
		pFibObjectTrue  = fibUnderObjects.front();
		pFibObjectFalse = fibUnderObjects.back();
		return;
	}//else
	if ( fibUnderObjects.empty() ){
		
		pFibObjectTrue  = NULL;
		pFibObjectFalse = NULL;
		return;
	}//else if ( fibUnderObjects.size() == 1 )
	
	pFibObjectTrue = fibUnderObjects.front();
}







