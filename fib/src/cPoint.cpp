/**
 * @class cPoint
 * file name: cPoint.cpp
 * @author Betti Oesterholz
 * @date 26.11.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the point -Fib -element.
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
 * This class represents the pointelement of the Fib -multimedialanguage.
 * It represents the position on which the properties, from higer in this
 * fib -limb, should be.
 * If the positionsvector of the point is empty. the properties are for
 * the background. If ther is no positionsvector the properties are discarded.
 *
 */
/*
History:
26.11.2009  Oesterholz  created
18.04.2010  Oesterholz  evalueObject() methods changed: not a function but
	an object is given to evalue the data
08.03.2011  Oesterholz  method for const getPosition() added
17.10.2011  Oesterholz  FEATURE_OUTPUT_ELEMENT_NUMBER_XML implemented
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
30.07.2013  Oesterholz  method assignValues() added
*/



#include "cPoint.h"

#include "cTypeDimension.h"
#include "cTypeVariable.h"



using namespace fib;


#ifdef FEATURE_SIMPLE_CONSTRUCTOR

/**
 * parameterconstructor
 *
 * @param pInVectorPosition a pointer to the positionsvector for the
 * 	point ore NULL if the point shouldn'd have a positionsvector
 * @param pInSuperiorPointElement the fib -Element in which this
 * 	point -element is an underobject
 */
cPoint::cPoint( const cVectorPosition * pInVectorPosition,
		cFibElement * pInSuperiorElement ):
		cFibLeaf( pInSuperiorElement ),
		pVectorPosition( NULL ){
	
	if ( pInSuperiorElement ){
		pInSuperiorElement->insertObjectInElement( this );
	}
	if ( pInVectorPosition == NULL ){
		pVectorPosition = NULL;
	}else{
		pVectorPosition = new cVectorPosition( *pInVectorPosition );
		if ( pInSuperiorElement ){
			pVectorPosition->setDefiningFibElement( this );
		}else{
			pVectorPosition->setDefiningFibElement( this, false );
		}
	}
	if ( pInSuperiorElement == NULL ){
		updateAllValues();
	}
}

#else //FEATURE_SIMPLE_CONSTRUCTOR

/**
 * parameterconstructor
 *
 * @param pInVectorPosition a pointer to the positionsvector for the
 * 	point ore NULL if the point shouldn'd have a positionsvector
 * @param pInSuperiorPointElement the fib -Element in which this
 * 	point -element is an underobject
 * @param pInPreviousFibElement the fib -Element which stands in th order
 * 	of Fib -elements befor this Fib -element
 * @param pInNextFibElement the fib -Element which stands in th order
 * 	of Fib -elements after this Fib -element
 */
cPoint::cPoint( const cVectorPosition * pInVectorPosition,
		cFibElement * pInSuperiorElement,
		cFibElement * pInPreviousFibElement,
		cFibElement * pInNextFibElement ):
		cFibLeaf( pInSuperiorElement, pInPreviousFibElement, pInNextFibElement ),
		pVectorPosition( NULL ){
	
	if ( pInVectorPosition == NULL ){
		pVectorPosition = NULL;
	}else{
		pVectorPosition = new cVectorPosition( *pInVectorPosition );
		if ( pInSuperiorElement ){
			pVectorPosition->setDefiningFibElement( this );
		}else{
			pVectorPosition->setDefiningFibElement( this, false );
		}
	}
}

#endif //FEATURE_SIMPLE_CONSTRUCTOR


/**
 * copyconstructor
 * This copyconstructor constructs a copy of the given point -Element.
 * It dosn't copy other point -elements than the given, even if ther are
 * in the point -element.
 *
 * @param pointElement the point -element to copy
 */
cPoint::cPoint( const cPoint &pointElement ):
		cFibLeaf( pointElement ),
		pVectorPosition( NULL ){
	
	if ( pointElement.pVectorPosition == NULL ){
		pVectorPosition = NULL;
	}else{
		pVectorPosition = new cVectorPosition( *pointElement.pVectorPosition );
		pVectorPosition->setDefiningFibElement( this, false );
	}
}


/**
 * The constructor for restoring a pointelement from an TinyXml element.
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
cPoint::cPoint( const TiXmlElement * pXmlElement, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables ): pVectorPosition( NULL ){
	
	if ( pXmlElement == NULL ){
		//noting to restore
		outStatus = -1;
		return;
	}
	string szElementType( pXmlElement->Value() );
	if ( szElementType != "point" ){
		//wrong element type to restore
		outStatus = -2;
		return;
	}
	//restore the positionsvector if existing
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
					const string szVectortypeNeeded( "position" );
					
					if ( szVectorXmlType == NULL ){
						outStatus = 2;
						continue;
					}else if ( szVectortypeNeeded != szVectorXmlType ){
						outStatus = 2;
						continue;
					}
					//restore the positionsvector
					if ( pVectorPosition == NULL ){
						pVectorPosition = new cVectorPosition( pXmlElement, outStatus, liDefinedVariables );
						if ( outStatus < 0 ){
							return;
						}
					}else{//to many positionsvectors -> invalid data in stream
						outStatus = 2;
						continue;
					}
				}else{//no correct subelement for a positionselement
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
				//invalid pointobject
				if ( outStatus ){
					outStatus = 2;
				}
				continue;
		}
	}
	if ( pVectorPosition != NULL ){
		pVectorPosition->setDefiningFibElement( this, false );
	}
}


/**
 * This constructor restores a pointelement from the stream where it is
 * stored in the compressed fib -format.
 * This constructor is for internal use only.
 *
 * @param iBitStream the stream wher the pointelement is stored to in,
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
 */
cPoint::cPoint( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains ):
		pVectorPosition( NULL ){
	
	if ( ! iBitStream.getStream()->good() ){
		outStatus = -1;
		return;
	}
	//restore the vector of the point
	cTypeDimension typeDimension;
	cDomain * pDomainPosition = validDomains.getDomainForElement( typeDimension );
	const bool bStandardDomainPosition = (pDomainPosition == NULL);
	if ( bStandardDomainPosition ){
		pDomainPosition = typeDimension.getStandardDomain();
	}
	cTypeVariable typeVariable;
	cDomain * pDomainVariable = validDomains.getDomainForElement( typeVariable );
	const bool bStandardDomainVariable = (pDomainVariable == NULL);
	if ( bStandardDomainVariable ){
		pDomainVariable = typeVariable.getStandardDomain();
	}
	
	pVectorPosition = new cVectorPosition( iBitStream, outStatus,
		liDefinedVariables, pDomainPosition, pDomainVariable );
	
	if ( bStandardDomainPosition ){
		delete pDomainPosition;
	}
	if ( bStandardDomainVariable ){
		delete pDomainVariable;
	}
	
	if ( pVectorPosition != NULL ){
		pVectorPosition->setDefiningFibElement( this, false );
	}
}


/**
 * desstructor
 */
cPoint::~cPoint(){
	
	if ( pVectorPosition != NULL ){
		delete pVectorPosition;
	}
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
char cPoint::getType() const{
	return 'p';
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
bool cPoint::evalueObject( iEvaluePosition & evaluePosition,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties ) const{
	
	if ( objectPoint != 0 ){
		//no such objectpoint
		return false;
	}
	
	if ( pVectorPosition ){
		return evaluePosition.evaluePosition( *pVectorPosition, liVecProperties );
	}//else don't evalue this point
	return true;
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
bool cPoint::evalueObject( iEvalueFibElement & evalueFibElement,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties,
		const list<char> & liCFibElementTyps ){
	
	if ( objectPoint != 0 ){
		//no such objectpoint
		return false;
	}
	
	if ( pVectorPosition ){
		return evalueFibElement.evalueElement( *this, liVecProperties );
	}//else don't evalue this point
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
unsignedLongFib cPoint::getTimeNeed( unsignedLongFib lMaxTime ) const{
	
	unsignedLongFib ulTimeNeeded = 0;
	if ( pVectorPosition ){
		ulTimeNeeded = 1 + pVectorPosition->getNumberOfElements();
	}else{// don't evalue this point
		ulTimeNeeded = 1;
	}
	if ( (lMaxTime == 0 ) || (ulTimeNeeded < lMaxTime) ){
		return ulTimeNeeded;
	}//else
	return lMaxTime;

}

/**
 * This method evaluades the size of the Fib -object in bits in the
 * compressed file form.
 * The optionalpart field of point -elements will be ignored.
 *
 * @see store()
 * @return the size of the Fib -object in bits in the compressed form
 */
unsignedLongFib cPoint::getCompressedSize() const{
	
	if ( (pVectorPosition == NULL) || (pVectorPosition->getNumberOfElements() == 0) ){
		return 5;
	}
	
	unsignedLongFib ulCompressedSize = 4;
	//add compressed size for the Vectorelements
	ulCompressedSize += pVectorPosition->getCompressedSize();
	
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
bool cPoint::isUsedVariable( const cFibVariable *variable ,
		edDirection direction ) const{
	
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		if ( pVectorPosition ){
			
			const bool bVariableUsed =
				pVectorPosition->isUsedVariable( variable );
			if ( bVariableUsed ){
				return true;
			}
		}
	}
	if ( (direction == ED_POSITION) ||  (direction == ED_BELOW_EQUAL)
			|| (direction == ED_BELOW) ){
		//all possible variables searched
		return false;
	}
	return cFibLeaf::isUsedVariable( variable, ED_HIGHER );
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
set<cFibVariable*> cPoint::getUsedVariables( edDirection direction ){
	
	set<cFibVariable*> setUsedVariables;
	if ( (direction == ED_POSITION) || (direction == ED_ALL) ||
			(direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
		
		if ( pVectorPosition ){
			
			setUsedVariables = pVectorPosition->getUsedVariables();
		}
	}
	if ( (direction == ED_POSITION) ||  (direction == ED_BELOW_EQUAL)
			|| (direction == ED_BELOW) ){
		//all possible variables found
		return setUsedVariables;
	}
	set<cFibVariable*> setUsedVariableleaf = cFibLeaf::getUsedVariables( ED_HIGHER );
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
bool cPoint::replaceVariable( cFibVariable *variableOld,
		cFibVariable *variableNew ){
	
	if ( (variableOld == NULL) || (variableNew == NULL) ){
		//can't replace
		return false;
	}
	if ( pVectorPosition ){
		
		return pVectorPosition->replaceVariable( variableOld, variableNew );
	}//else nothing to replace

	return true;
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
cFibElement * cPoint::copyElement( const char cType, const unsignedIntFib
		elementPoint, bool bAbsolute ) const{
	
	if ( elementPoint == 0 ){
		//copy this Fib element
		return new cPoint( *this );
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
bool cPoint::assignValues( const cFibElement & fibElement ){
	
	if ( fibElement.getType() != getType() ){
		//both Fib elements not of the same type -> can't assign values
		return false;
	}
	if ( equalElement( fibElement, false ) ){
		//elements already equal -> don't need to assign anything
		return true;
	}
	const cPoint * pOtherPoint = ((const cPoint*)(&fibElement));
	const cVectorPosition * pOtherVectorPosition =
		pOtherPoint->pVectorPosition;
	if ( pOtherVectorPosition == NULL ){
		//set the positions vector of this point to NULL
		if ( pVectorPosition ){
			//delete old position vector
			delete pVectorPosition;
			pVectorPosition = NULL;
		}
		return true;
	}
	
	//try to match used variables
	const set< cFibVariable* > setUsedVariables = (const_cast< cVectorPosition * >(
		pOtherVectorPosition))->getUsedVariables();
	/* The list with the variables to replace:
	 * 	first: the original used variable to replace
	 * 	second: the new variable to replace the original variable
	 */
	list< pair< cFibVariable * ,cFibVariable * > > liVariablesToReplace;
	
	if ( ! getVariablesToReplace( setUsedVariables, liVariablesToReplace ) ){
		//not all variables can be replaced with for this Fib element defined variables
		return false;
	}
	//copy position vector of other point
	//assign the values
	if ( pVectorPosition ){
		delete pVectorPosition;
	}
	pVectorPosition = new cVectorPosition( *pOtherVectorPosition, this );
	
	if ( ! liVariablesToReplace.empty() ){
		//replace variables to replace
		for ( list< pair< cFibVariable * ,cFibVariable * > >::iterator
				itrActualVariable = liVariablesToReplace.begin();
				itrActualVariable != liVariablesToReplace.end(); itrActualVariable++ ){
			
			//replace variable in areavector
			if ( ! pVectorPosition->replaceVariable(
					itrActualVariable->first, itrActualVariable->second ) ){
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
bool cPoint::equalInternal( const cFibElement & fibObject,
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
bool cPoint::equalElementInternal( const cFibElement & fibElement,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{

	if ( getType() != fibElement.getType() ){
		return false;
	}
	cPoint * pPoint = (cPoint*)( &fibElement );
	
	if ( (pVectorPosition == NULL) || (pPoint->pVectorPosition == NULL) ){
		if ( pVectorPosition != pPoint->pVectorPosition ){
			//both vectorpointers aren't NULL
			return false;
		}//else both vectorpointers are NULL
		return true;
	}//else
	if ( pVectorPosition->equalInternal( *(pPoint->pVectorPosition),
			mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects ) ){
		//equal vectors -> equal points
		return true;
	}//else
	return false;
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
bool cPoint::equal( const cFibElement & fibObject ) const{
	
	if ( ! cFibLeaf::equal( fibObject ) ){
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
bool cPoint::equalElement( const cFibElement & fibElement ) const{

	if ( getType() != fibElement.getType() ){
		return false;
	}
	cPoint * pPoint = (cPoint*)( &fibElement );
	
	if ( (pVectorPosition == NULL) || (pPoint->pVectorPosition == NULL) ){
		if ( pVectorPosition != pPoint->pVectorPosition ){
			//both vectorpointers aren't NULL
			return false;
		}//else both vectorpointers are NULL
		return true;
	}//else
	if ( ! ( *pVectorPosition == *(pPoint->pVectorPosition) ) ){
		return false;
	}//else
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
bool cPoint::storeXml( ostream &stream ) const{

	bool bReturnValue = true;
	
	if ( pVectorPosition != NULL ){
		if ( 0 < pVectorPosition->getNumberOfElements() ){
#ifdef FEATURE_OUTPUT_ELEMENT_NUMBER_XML
			stream<<"<point elementNr=\""<<getNumberOfElement()<<"\" >"<<endl;
#else //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
			stream<<"<point>"<<endl;
#endif //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
			bReturnValue &= pVectorPosition->storeXml( stream );
			stream<<"</point>"<<endl;
		}else{//background point (pVectorPosition->getNumberOfElements() == 0)
			stream<<"<background/>"<<endl;
		}
	}else{//empty poin
#ifdef FEATURE_OUTPUT_ELEMENT_NUMBER_XML
		stream<<"<point elementNr=\""<<getNumberOfElement()<<"\" />"<<endl;
#else //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
		stream<<"<point/>"<<endl;
#endif //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	}
	return bReturnValue;
}


/**
 * @return a pointer to the positionsvector of this pointelement or
 * 	NULL if the point has no positionsvector
 */
cVectorPosition * cPoint::getPosition(){
	return pVectorPosition;
}


/**
 * @return a pointer to the positionsvector of this pointelement or
 * 	NULL if the point has no positionsvector
 */
const cVectorPosition * cPoint::getPosition() const{
	return pVectorPosition;
}

/**
 * This sets the positionsvector of this point.
 * The given positionsvector is copied befor inserting it in this point.
 * If the positionsvector of the point is empty. the properties are for
 * the background.
 * If ther is no positionsvector the properties are discarded at this point.
 *
 * @param vecPositon the positionsvector this point should have
 */
void cPoint::setPosition( const cVectorPosition *vecPositon ){
	
	if ( pVectorPosition != NULL ){
		delete pVectorPosition;
	}
	if ( vecPositon == NULL ){
		pVectorPosition = NULL;
		return;
	}
	pVectorPosition = new cVectorPosition( *vecPositon, this );
}



/**
 * This method stores this Fib -object in the compressed Fib -format
 * into the given stream.
 * It is needed becouse the stream can yust store byts but the size of
 * fib -elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the fib -elements.
 *
 * @see store
 * @param stream the stream where this Fib -object should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if this Fib -object is stored, else false
 */
bool cPoint::storeBit( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{

	if ( pVectorPosition == NULL ){
		//point with not positionsvector
		const char cInitiation = 0x12;
		return nBitStream::store( stream, cRestBits, uiRestBitPosition,
				&cInitiation, 5 );
	}else if ( pVectorPosition->getNumberOfElements() == 0 ){
		//point with empty positionsvector
		const char cInitiation = 0x02;
		return nBitStream::store( stream, cRestBits, uiRestBitPosition,
				&cInitiation, 5 );
	}//else normal point
	const char cInitiation = 0x01;
	const bool bInitiationStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, &cInitiation, 4 );
	if ( ! bInitiationStored ){
		return false;
	}
	return pVectorPosition->store( stream, cRestBits, uiRestBitPosition );
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
cFibElement * cPoint::copyInternal( const unsignedIntFib iObjectPoint ) const{
	if ( iObjectPoint == 0 ){
		return new cPoint( *this );
	}//else no objectpoint to copy
	return NULL;
}



















