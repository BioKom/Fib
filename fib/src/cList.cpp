/**
 * @class cList
 * file name: cList.cpp
 * @author Betti Oesterholz
 * @date 16.12.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the list -Fib -element.
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
 * This class represents the list element of the Fib -multimedialanguage.
 * It represents a list of fib -objects.
 *
 */
/*
History:
16.12.2009  Oesterholz  created
18.04.2010  Oesterholz  evalueObject() methods changed: not a function but
	an object is given to evalue the data
05.09.2010  Oesterholz  replaceAllUnderobjects() added
26.01.2011  Oesterholz  some bugfixes in deleteUnderobjects() and
	replaceAllUnderobjects() (pointer errors)
20.08.2011  Oesterholz  store in compressed format NULL if no subobject exists
17.10.2011  Oesterholz  FEATURE_OUTPUT_ELEMENT_NUMBER_XML implemented
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
*/


#include "cList.h"
#include "cDomainNaturalNumberBit.h"


#ifdef FEATURE_SIMPLE_CONSTRUCTOR

#ifdef FEATURE_FAST_UPDATE
/**
 * parameterconstructor
 *
 * @param pFibObject1 the fib -Element which is the first underobject of
 * 	this list-lement (it also stands next in the order of fib -elements)
 * @param pFibObject2 the fib -Element which is the secound underobject of
 * 	this list element
 * @param pInSuperiorElement the fib -Element in which this
 * 	list -element is an underobject
 */
cList::cList( cFibElement * pFibObject1, cFibElement * pFibObject2,
		cFibElement * pInSuperiorElement ):
		cFibBranch( list<cFibElement*>(), pInSuperiorElement ){
	
	if ( pFibObject1 ){
		fibUnderObjects.push_back( pFibObject1 );
		if ( pFibObject1->pSuperiorElement != NULL ){
			pFibObject1->pSuperiorElement->cutConnectionsTo(
				pFibObject1 );
		}
		pFibObject1->pSuperiorElement = this;
	}
	if ( pFibObject2 ){
		fibUnderObjects.push_back( pFibObject2 );
		if ( pFibObject2->pSuperiorElement != NULL ){
			pFibObject2->pSuperiorElement->cutConnectionsTo(
				pFibObject2 );
		}
		pFibObject2->pSuperiorElement = this;
	}
	updateAllCounters();
	
	if ( pInSuperiorElement ){
		pInSuperiorElement->insertObjectInElement( this );
	}
}

#else //FEATURE_FAST_UPDATE

/**
 * parameterconstructor
 *
 * @param pFibObject1 the fib -Element which is the first underobject of
 * 	this list-lement (it also stands next in the order of fib -elements)
 * @param pFibObject2 the fib -Element which is the secound underobject of
 * 	this list element
 * @param pInSuperiorElement the fib -Element in which this
 * 	list -element is an underobject
 */
cList::cList( cFibElement * pFibObject1, cFibElement * pFibObject2,
		cFibElement * pInSuperiorElement ):
		cFibBranch( list<cFibElement*>(), pInSuperiorElement ){
	
	if ( pFibObject1 ){
		fibUnderObjects.push_back( pFibObject1 );
	}
	if ( pFibObject2 ){
		fibUnderObjects.push_back( pFibObject2 );
	}
	
	if ( pInSuperiorElement ){
		pInSuperiorElement->insertObjectInElement( this );
	}else{
		updateAllValues();
	}
}

#endif//FEATURE_FAST_UPDATE


/**
 * parameterconstructor
 *
 * @param liInUnderObjects the list with the underobjects for the list element
 * @param pInSuperiorElement the fib -Element in which this
 * 	list -element is an underobject
 */
cList::cList( list< cFibElement * > liInUnderObjects, cFibElement * pInSuperiorElement ):
		cFibBranch( liInUnderObjects, pInSuperiorElement ){
	
#ifdef FEATURE_FAST_UPDATE
	updateAllCounters();
	if ( pInSuperiorElement ){
		pInSuperiorElement->insertElement( this );
	}
#else //FEATURE_FAST_UPDATE
	if ( pInSuperiorElement ){
		pInSuperiorElement->insertElement( this );
	}else{
		updateAllValues();
	}
#endif//FEATURE_FAST_UPDATE
}

#else //FEATURE_SIMPLE_CONSTRUCTOR

/**
 * parameterconstructor
 *
 * @param pFibObject1 the fib -Element which is the first underobject of
 * 	this list-lement (it also stands next in the order of fib -elements)
 * @param pFibObject2 the fib -Element which is the secound underobject of
 * 	this list element
 * @param pInSuperiorElement the fib -Element in which this
 * 	list -element is an underobject
 * @param pInPreviousFibElement the fib -Element which stands in th order
 * 	of Fib -elements befor this Fib -element
 */
cList::cList( cFibElement * pFibObject1, cFibElement * pFibObject2,
		cFibElement * pInSuperiorElement,
		cFibElement * pInPreviousFibElement ):
		cFibBranch( pInSuperiorElement, pInPreviousFibElement,
		pFibObject1 ){
	
	if ( pFibObject1 ){
		fibUnderObjects.push_back( pFibObject1 );
	}
	if ( pFibObject2 ){
		fibUnderObjects.push_back( pFibObject2 );
	}
	updateAllValues();
}

#endif //EATURE_SIMPLE_CONSTRUCTOR


/**
 * copyconstructor
 * This copyconstructor constructs a copy of the given list -Element.
 * It dosn't copy other list -elements than the given, even if ther are
 * in the list -element.
 *
 * @param listElement the list -element to copy
 */
cList::cList( const cList &listElement ):
		cFibBranch( listElement ){
	
#ifdef FEATURE_FAST_UPDATE
	updateAllCounters();
#endif //FEATURE_FAST_UPDATE
}




/**
 * The constructor for restoring a list element from an TinyXml element.
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
cList::cList( const TiXmlElement * pXmlElement, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables ){
	
	if ( pXmlElement == NULL ){
		//noting to restore
		outStatus = -1;
		return;
	}
	string szElementType( pXmlElement->Value() );
	if ( szElementType != "list" ){
		//wrong element type to restore
		outStatus = -2;
		return;
	}
	for ( const TiXmlNode * pChild = pXmlElement->FirstChild();
			pChild != NULL; pChild = pChild->NextSibling() ) {
		
		int iType = pChild->Type();
		
		switch ( iType ){
			case TiXmlNode::ELEMENT:{
				/*restore the underobjects of the list element*/
				
				//every underobject has it's own variables
				list<cFibVariable*> liDefinedVariablesCopy( liDefinedVariables );
				
				cFibElement * pUnderObject = cFibElement::restoreXml(
					pChild, outStatus, liDefinedVariablesCopy );
				if ( pUnderObject != NULL){
					//add the loaded underobject to the list element
					fibUnderObjects.push_back( pUnderObject );
#ifdef FEATURE_FAST_UPDATE
					if ( pUnderObject->pSuperiorElement != NULL ){
						pUnderObject->pSuperiorElement->cutConnectionsTo( pUnderObject );
					}
					pUnderObject->pSuperiorElement = this;
#endif //FEATURE_FAST_UPDATE
				}
				if ( outStatus < 0 ){
					//an error occured
					return;
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
			default:{
				//invalid pointobject
				if ( outStatus ){
					outStatus = 2;
				}
			}
		}
	}
	if ( fibUnderObjects.size() < 2 ){
		//not enougth underobjects
		outStatus = 2;
	}
#ifdef FEATURE_FAST_UPDATE
	updateAllCounters();
#endif //FEATURE_FAST_UPDATE
}


/**
 * This constructor restores a list element from the stream where it is
 * stored in the compressed fib -format.
 * This constructor is for internal use only.
 *
 * @param iBitStream the stream wher the list element is stored to in,
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
 * @param uiBitsForUnderObjectCount the number of bits of the count of
 * 	the underobjects for the list element
 */
cList::cList( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains,
		cRoot * pNextRoot, unsignedIntFib uiBitsForUnderObjectCount ){
	
	if ( ! iBitStream.getStream()->good() ){
		outStatus = -1;
		return;
	}
	if ( pNextRoot == NULL ){
		outStatus = -2;
		return;
	}
	unsignedLongFib ulNumberOfUnderobjects = 2;
	if ( uiBitsForUnderObjectCount != 0 ){
		//restore the count of underobjects
		cDomainNaturalNumberBit domainNaturalNumberBit( uiBitsForUnderObjectCount );
		
		ulNumberOfUnderobjects = domainNaturalNumberBit.restoreIntegerValue(
			iBitStream, outStatus );
		if ( outStatus < 0 ){
			return;
		}
	}//else two underobjects
	
	//restore the underobjects of the list element
	for ( unsignedLongFib ulActualUnderobject = 1;
			ulActualUnderobject <= ulNumberOfUnderobjects; ulActualUnderobject++ ){
		
		list<cFibVariable*> liDefinedVariablesCopy( liDefinedVariables );
		cFibElement * pUnderObject = cFibElement::restoreInternal(
			iBitStream, outStatus, liDefinedVariablesCopy, validDomains, pNextRoot );
		
		if ( pUnderObject != NULL){
			//add the loaded underobject to the list element
			fibUnderObjects.push_back( pUnderObject );
#ifdef FEATURE_FAST_UPDATE
			if ( pUnderObject->pSuperiorElement != NULL ){
				pUnderObject->pSuperiorElement->cutConnectionsTo( pUnderObject );
			}
			pUnderObject->pSuperiorElement = this;
#endif //FEATURE_FAST_UPDATE
		}
		if ( outStatus < 0 ){
			//an error occured
			return;
		}
	}
#ifdef FEATURE_FAST_UPDATE
	updateAllCounters();
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
char cList::getType() const{
	return 'l';
}


/**
 * This method checks, if this fib -element is an valid fib -element.
 *
 * @return true if this fib -element is an valid fib -element, else false
 */
bool cList::isValidFibElement() const{
	if ( ! cFibBranch::isValidFibElement() ){
		return false;
	}
	if ( getNumberOfUnderobjects() < 2 ){
		//list elements needs to have a minimum of two underobjects
		return false;
	}
	return true;
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
bool cList::evalueObject( iEvaluePosition & evaluePosition,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties ) const{
		
	if ( objectPoint == 0 ){
		//evalue all underobjects with the given properties
		for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
			
			if ( (*actualUnderObject) != NULL ){
				list<cVectorProperty> liVecPropertiesUnderObject( liVecProperties );
				const bool bUnderobjectEvalued =
					(*actualUnderObject)->evalueObject( evaluePosition, objectPoint,
						liVecPropertiesUnderObject );
				if ( ! bUnderobjectEvalued ){
					return false;
				}
			}
		}
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
bool cList::evalueObject( iEvalueFibElement & evalueFibElement,
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
	
	if ( objectPoint == 0 ){
		//evalue all underobjects with the given properties
		for (list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
			
			if ( (*actualUnderObject) != NULL ){
				list<cVectorProperty> liVecPropertiesUnderObject( liVecProperties );
				const bool bUnderobjectEvalued =
					(*actualUnderObject)->evalueObject( evalueFibElement, objectPoint,
						liVecPropertiesUnderObject, liCFibElementTyps );
				if ( ! bUnderobjectEvalued ){
					return false;
				}
			}
		}
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
unsignedLongFib cList::getTimeNeed( unsignedLongFib lMaxTime ) const{
	
	unsignedLongFib ulTimeNeeded = 1;
	if ( lMaxTime != 0 ){
		if ( 1 < lMaxTime ){
			lMaxTime--;
		}else{//max time reached
			return lMaxTime;
		}
	}

	//evalue all underobjects with the given properties
	for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
		
		if ( (*actualUnderObject) != NULL ){
			
			const unsignedLongFib ulActualTimeNeeded =
				(*actualUnderObject)->getTimeNeed( lMaxTime );
			if ( lMaxTime != 0 ){
				if ( ulActualTimeNeeded < lMaxTime ){
					lMaxTime -= ulActualTimeNeeded;
				}else{//max time reached
					return lMaxTime + ulTimeNeeded;
				}
			}
			ulTimeNeeded += ulActualTimeNeeded;
		}
	}
	return ulTimeNeeded;
}


/**
 * This method checks, if all Fib -elements of this Fib -object
 * have the underobjects they need to be correct.
 *
 * @return true if all Fib -elements of this Fib -object have the
 * 	underobjects they need to be correct, else false
 */
bool cList::hasUnderAllObjects() const{
	
	if ( fibUnderObjects.size() < 2 ){
		//list elements needs to have a minimum of two underobjects
		return false;
	}
	if ( ! cFibBranch::hasUnderAllObjects() ){
		return false;
	}
	return true;
}


/**
 * This method evaluades the size of the Fib -object in bits in the
 * compressed file form.
 * The optionalpart field of list -elements will be ignored.
 *
 * @see store()
 * @return the size of the Fib -object in bits in the compressed form
 */
unsignedLongFib cList::getCompressedSize() const{
	
	unsignedLongFib ulCompressedSize = 4;

	//add bits for number of underobjects field
	const unsigned long long ulNumberOfUnderobjects = getNumberOfUnderobjects();
	if ( ulNumberOfUnderobjects == 2 ){
		//no number of underobjects field
	}else if ( ulNumberOfUnderobjects < 256 ){
		ulCompressedSize += 8;
	}else{
		ulCompressedSize += 64;
	}

	//evalue all underobjects with the given properties
	for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
		
		if ( (*actualUnderObject) != NULL ){
			
			ulCompressedSize += (*actualUnderObject)->getCompressedSize();
		}
	}
	return ulCompressedSize;
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
cFibElement * cList::copyElement( const char cType, const unsignedIntFib
		elementPoint, bool bAbsolute ) const{
	
	if ( elementPoint == 0 ){
		//copy this element
		return new cList( *this );
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
bool cList::equalElementInternal( const cFibElement & fibElement,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{
	
	if ( getType() != fibElement.getType() ){
		return false;
	}
	return true;
}

#else //FEATURE_EQUAL_FIB_OBJECT

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
bool cList::equalElement( const cFibElement & fibElement ) const{
	
	if ( getType() != fibElement.getType() ){
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
bool cList::storeXml( ostream &stream ) const{
	
	bool bReturnValue = true;
	
#ifdef FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	stream<<"<list elementNr=\""<<getNumberOfElement()<<"\" >"<<endl;
#else //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	stream<<"<list>"<<endl;
#endif //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	//store all underobjects
	for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
		
		if ( (*actualUnderObject) != NULL ){
			
			bReturnValue &= (*actualUnderObject)->storeXml( stream );
		}
	}
	stream<<"</list>"<<endl;
	return bReturnValue;
}



/*
 * List -element methods
 */


/**
 * @return the number of underobjects of this list element
 */
unsignedIntFib cList::getNumberOfUnderobjects() const{
	return fibUnderObjects.size();
}


/**
 * This method return the iNumberOfUnderObject'th underobject of this
 * list element.
 *
 * @param iNumberOfUnderObject the number of the underobject to return
 * @return iNumberOfUnderObject'th underobject of this list element or
 * 	NULL, if non such exists
 */
cFibElement * cList::getUnderobject( unsignedIntFib iNumberOfUnderObject ){

	//find the position from wher underobject should be given back
	for ( list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
			(actualUnderObject != fibUnderObjects.end()) && (iNumberOfUnderObject >= 1);
			actualUnderObject++, iNumberOfUnderObject-- ){
		
		if ( iNumberOfUnderObject == 1 ){
			return (*actualUnderObject);
		}
	}
	return NULL;
}


/**
 * This method returns a number of underobjects from this list element,
 * beginning from a first underobject.
 *
 * @see getUnderobject()
 * @param iNumberOfFirstUnderobject the number of the first underobject
 * 	to return
 * @param iNumberOfToReturnUnderobjects the number /count of underobjects
 * 	to return; if 0 or greater equal the count of underobjects from
 * 	first underobject, all underobjects to the listend  will be returned
 * @return a list with the underobjects to return
 */
list< cFibElement * > cList::getUnderobjects(
		unsignedIntFib iNumberOfFirstUnderobject,
		unsignedIntFib iNumberOfToReturnUnderobjects ){
	
	if ( (iNumberOfFirstUnderobject <= 1) && (
			(iNumberOfToReturnUnderobjects == 0) ||
			(fibUnderObjects.size() <= iNumberOfToReturnUnderobjects) ) ){
		//return all underobjects
		return fibUnderObjects;
	}
	//find the position from wher underobject should be given back
	list<cFibElement*>::iterator firstUnderObject;
	for ( firstUnderObject = fibUnderObjects.begin();
			(firstUnderObject != fibUnderObjects.end()) && (iNumberOfFirstUnderobject >= 1);
			firstUnderObject++, iNumberOfFirstUnderobject-- ){
		
		if ( iNumberOfFirstUnderobject == 1 ){
			break;
		}
	}
	if ( firstUnderObject != fibUnderObjects.end() ){
		//no underobjects to return
		return list< cFibElement * >();
	}
	list<cFibElement*>::iterator lastUnderObject;
	if ( iNumberOfToReturnUnderobjects != 0 ){
	
		for ( lastUnderObject = firstUnderObject;
				(lastUnderObject != fibUnderObjects.end()) && (iNumberOfToReturnUnderobjects >= 1);
				lastUnderObject++, iNumberOfToReturnUnderobjects-- ){
			
			if ( iNumberOfToReturnUnderobjects == 1 ){
				break;
			}
		}
		if ( lastUnderObject != fibUnderObjects.end() ){
			//include the last fib element
			lastUnderObject++;
		}
	}else{//return all underobjects to the listend
		lastUnderObject = fibUnderObjects.end();
	}
	//return all underobjects betwean the first and last underobject
	return list< cFibElement * >( firstUnderObject, lastUnderObject );
}


/**
 * This method adds the underobject pUnderObject on the given position
 * iPosition to this list element.
 *
 * @param pUnderObject a pointer to the underobject to add to the list element
 * @param iPosition the position on which to add the underobject, if
 * 	this number is greater than the number of underobjects in the
 * 	list element, the underobject will be added to the end of th list element
 * @return true if the underobject was added, else false
 */
bool cList::addUnderobject( cFibElement * pUnderObject, unsignedIntFib iPosition ){
	
	if ( pUnderObject == NULL ){
		//nothing to insert
		return false;
	}
	if ( iPosition <= fibUnderObjects.size() ){
		list<cFibElement*>::iterator actualUnderObject;
		//find the position wher to insert the new element	
		for ( actualUnderObject = fibUnderObjects.begin();
				(actualUnderObject != fibUnderObjects.end()) && (1 < iPosition);
				actualUnderObject++, iPosition-- ){
		}
		fibUnderObjects.insert( actualUnderObject, pUnderObject );
	}else{//add to end of underobject list
		fibUnderObjects.push_back( pUnderObject );
	}
#ifdef FEATURE_FAST_UPDATE
	if ( pUnderObject->pSuperiorElement != NULL ){
		pUnderObject->pSuperiorElement->cutConnectionsTo( pUnderObject );
	}
	pUnderObject->pSuperiorElement = this;
	cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( pUnderObject );
	fibObjectCountsDelta.uiNumberOfObjectpoints++;
	updateAllCounters( fibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
	updateAllValues();
#endif //FEATURE_FAST_UPDATE
	return true;
}


/**
 * This method adds the underobject pUnderobject on the given position
 * iPosition to this list element.
 *
 * @param liUnderobjects the list with the pointers to the underobjects
 * 	to add to the list element
 * @param iPosition the position on which to add the underobjects, if
 * 	this number is greater than the number of underobjects in the
 * 	list element, the underobjects will be added to the end of the list element
 * @return the number of underobjects added
 */
unsignedIntFib cList::addUnderobjects( list<cFibElement*> liUnderobjects,
		unsignedIntFib iPosition ){
	
#ifdef FEATURE_FAST_UPDATE
	cFibObjectCounts fibObjectCountsDelta;
#endif //FEATURE_FAST_UPDATE
	//remove all nullpointers from the to add list
	list<cFibElement*>::iterator actualUnderObject;
	for ( actualUnderObject = liUnderobjects.begin();
			(actualUnderObject != liUnderobjects.end());
			actualUnderObject++ ){
		
		if ( (*actualUnderObject) == NULL ){
			liUnderobjects.erase( actualUnderObject );
		}
#ifdef FEATURE_FAST_UPDATE
		else{//an valid underobject
			if ( (*actualUnderObject)->pSuperiorElement != NULL ){
				(*actualUnderObject)->pSuperiorElement->cutConnectionsTo( (*actualUnderObject) );
			}
			(*actualUnderObject)->pSuperiorElement = this;
			fibObjectCountsDelta += evalueCountersForObject( *actualUnderObject );
			fibObjectCountsDelta.uiNumberOfObjectpoints++;
		}
#endif //FEATURE_FAST_UPDATE
	}
	//find the position wher to insert the new underobjects
	for ( actualUnderObject = fibUnderObjects.begin();
			(actualUnderObject != fibUnderObjects.end()) && (1 < iPosition);
			actualUnderObject++, iPosition-- ){
	}
	fibUnderObjects.insert( actualUnderObject, liUnderobjects.begin(),
		liUnderobjects.end() );
	
#ifdef FEATURE_FAST_UPDATE
	updateAllCounters( fibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
	updateAllValues();
#endif //FEATURE_FAST_UPDATE
	
	return liUnderobjects.size();
}


/**
 * This method deleted the underobject pUnderObject on the given
 * position iPositionUnderObject from this list element.
 *
 * @param iPositionUnderObject the position from which to delete the
 * 	underobject
 * @param bDeleteOld if true, delete the old Fib -object from the memory
 * @return true if the underobject was deleted, else false
 */
bool cList::deleteUnderobject( unsignedIntFib iPositionUnderObject,
		bool bDeleteOld ){
	
	if ( (iPositionUnderObject == 0) ||
			(fibUnderObjects.size() < iPositionUnderObject) ||
			(fibUnderObjects.size() <= 2) ){
		//nothing to delete
		return false;
	}
	list<cFibElement*>::iterator actualUnderObject;
	//find the position wher to delete the underobject
	for ( actualUnderObject = fibUnderObjects.begin();
			(actualUnderObject != fibUnderObjects.end()) && (iPositionUnderObject > 1);
			actualUnderObject++, iPositionUnderObject-- ){
	}
	if ( iPositionUnderObject == 1 ){
		//underobject to delete found
		cFibElement * pRootObjectToDelete = (*actualUnderObject);
		fibUnderObjects.erase( actualUnderObject );
		//cut connection to this element
		if ( pRootObjectToDelete->pSuperiorElement == this ){
			pRootObjectToDelete->pSuperiorElement = NULL;
		}
		
#ifdef FEATURE_FAST_UPDATE
		cFibObjectCounts fibObjectCountsDelta;
		fibObjectCountsDelta -= evalueCountersForObject( pRootObjectToDelete );
		fibObjectCountsDelta.uiNumberOfObjectpoints--;
		updateAllCounters( fibObjectCountsDelta );
			
		if ( bDeleteOld && (pRootObjectToDelete != NULL) ){
			pRootObjectToDelete->deleteObject();
		}
#else //FEATURE_FAST_UPDATE
		if ( bDeleteOld && ((*actualUnderObject) != NULL) ){
			pRootObjectToDelete->pPreviousFibElement = NULL;
			if ( pRootObjectToDelete->pSuperiorElement == this ){
				pRootObjectToDelete->pSuperiorElement = NULL;
			}
			
			cFibElement * pLastFibElementInOld =
				pRootObjectToDelete->getFibElement(
					pRootObjectToDelete->getNumberOfElements() - 1 );
			
			if ( pLastFibElementInOld ){
				pLastFibElementInOld->pNextFibElement = NULL;
			}
			deleteObject( pRootObjectToDelete );
		}
		updateAllValues();
#endif //FEATURE_FAST_UPDATE
		return true;
	}//else
	return false;
}


#ifdef FEATURE_FAST_UPDATE

/**
 * This method deletes a number of underobjects from this list element,
 * beginning from a first underobject.
 *
 * @see getUnderobject()
 * @param iNumberOfFirstUnderobject the number of the first underobject
 * 	to delete
 * @param iNumberOfToDeleteUnderobjects the number /count of underobjects
 * 	to delete; if 0 or greater equal the count of underobjects from
 * 	first underobject, all underobjects to the listend  will be deleted
 * @param bDeleteOld if true, delete the old fib -underobjects from the memory
 * @return true if the underobject wher deleted, else false
 */
bool cList::deleteUnderobjects(
		unsignedIntFib iNumberOfFirstUnderobject,
		unsignedIntFib iNumberOfToDeleteUnderobjects, bool bDeleteOld ){
	
	if ( fibUnderObjects.size() < iNumberOfFirstUnderobject ){
		//no such underobjects to delete
		return false;
	}
	if ( (iNumberOfFirstUnderobject <= 2) &&
			(iNumberOfToDeleteUnderobjects == 0) ){
		//two underobjects must remain in list
		return false;
	}
	
	//find the position from wher underobject should be given back
	list<cFibElement*>::iterator itrFirstUnderObject;
	for ( itrFirstUnderObject = fibUnderObjects.begin();
			(itrFirstUnderObject != fibUnderObjects.end()) && (iNumberOfFirstUnderobject > 1);
			itrFirstUnderObject++, iNumberOfFirstUnderobject-- ){
	}
	if ( itrFirstUnderObject == fibUnderObjects.end() ){
		//no underobjects to delete
		return false;
	}
	list<cFibElement*>::iterator itrLastUnderObject;
	if ( iNumberOfToDeleteUnderobjects != 0 ){
	
		unsignedIntFib uiUnderobjectsToDelete = 1;
		for ( itrLastUnderObject = itrFirstUnderObject;
				(itrLastUnderObject != fibUnderObjects.end()) && (iNumberOfToDeleteUnderobjects > 1);
				itrLastUnderObject++, iNumberOfToDeleteUnderobjects--, uiUnderobjectsToDelete++ ){
		}
		if ( itrLastUnderObject != fibUnderObjects.end() ){
			//include the last fib element
			itrLastUnderObject++;
		}else{//uncount last underobject
			uiUnderobjectsToDelete--;
		}
		if ( fibUnderObjects.size() - 1 <= uiUnderobjectsToDelete ){
			//two underobjects must remain in list
			return false;
		}
	}else{//return all underobjects to the listend
		itrLastUnderObject = fibUnderObjects.end();
	}
	//update counters and delete underobjects
	cFibObjectCounts fibObjectCountsDelta;
	for ( list<cFibElement*>::iterator itrActualUnderObject = itrFirstUnderObject;
			itrActualUnderObject != itrLastUnderObject; ){
		
		cFibElement * pUnderobjectToDelete = *itrActualUnderObject;
		itrActualUnderObject = fibUnderObjects.erase( itrActualUnderObject );
		
		fibObjectCountsDelta -= evalueCountersForObject( pUnderobjectToDelete );
		fibObjectCountsDelta.uiNumberOfObjectpoints--;
		
		if ( pUnderobjectToDelete != NULL ){
			
			if ( pUnderobjectToDelete->pSuperiorElement == this ){
				pUnderobjectToDelete->pSuperiorElement = NULL;
			}
			if ( bDeleteOld ){
				pUnderobjectToDelete->deleteObject();
			}
		}
	}
	//delete all underobjects betwean the first and last underobject
//TODO weg (done by cutConnectionsTo() )	fibUnderObjects.erase( itrFirstUnderObject, itrLastUnderObject );
	
	updateAllCounters( fibObjectCountsDelta );
	return true;
}


/**
 * This method replaces all underobjects of this list element with the
 * given underobjects liUnderobjects.
 *
 * @param liUnderobject the list with the pointers to the underobjects,
 * 	with which to replace the existing underobjects of the list element
 * @param bDeleteOld if true, delete the old fib -underobjects from the memory
 * @return true if the replacing was successfull, else false
 */
bool cList::replaceAllUnderobjects( list<cFibElement*> liUnderobjects,
		bool bDeleteOld ){
	
	//remove all nullpointers from the to add list
	for ( list<cFibElement*>::iterator actualUnderObject = liUnderobjects.begin();
			(actualUnderObject != liUnderobjects.end()); actualUnderObject++ ){
		
		if ( (*actualUnderObject) == NULL ){
			liUnderobjects.erase( actualUnderObject );
		}
	}
	if ( liUnderobjects.size() < 2 ){
		return false;
	}
	
	//delete all underobjects betwean the first and last underobject
	while ( ! fibUnderObjects.empty() ){
		
		cFibElement * pUnderobjectToDelete =
			fibUnderObjects.back();
		fibUnderObjects.pop_back();
		
		if ( pUnderobjectToDelete != NULL ){
			
			if ( pUnderobjectToDelete->pSuperiorElement == this ){
				pUnderobjectToDelete->pSuperiorElement = NULL;
			}
			if ( bDeleteOld ){
				pUnderobjectToDelete->deleteObject();
			}
		}
	}
	//add superior connection to this to the given underobjects
	for ( list<cFibElement*>::iterator actualUnderObject = liUnderobjects.begin();
			(actualUnderObject != liUnderobjects.end()); actualUnderObject++ ){
		
		if ( (*actualUnderObject)->pSuperiorElement != NULL ){
			(*actualUnderObject)->pSuperiorElement->cutConnectionsTo(
				(*actualUnderObject) );
		}
		(*actualUnderObject)->pSuperiorElement = this;
	}

	fibUnderObjects = liUnderobjects;
	
	updateAllCounters();

	return true;
}

#endif //FEATURE_FAST_UPDATE


/**
 * This method stores this Fib -object in the compressed Fib -format
 * into the given stream.
 * It is needed becouse the stream can yust store byts but the size of
 * fib -elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the fib -elements.
 * Beware: You need to call storeBit() of the root -elements with the
 * domain for the list or the list will not be readebel.
 *
 * @see store
 * @param stream the stream where this Fib -object should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if this Fib -object is stored, else false
 */
bool cList::storeBit( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	char cInitiation;
	unsigned char usBitsForNumberOfUnderobjects;
	const unsigned long long ulNumberOfUnderobjects = getNumberOfUnderobjects();
	if ( ulNumberOfUnderobjects < 2 ){
		//no valid listobject to store
		return false;
	}
	if ( ulNumberOfUnderobjects == 2 ){
		cInitiation = 0x04;
		usBitsForNumberOfUnderobjects = 0;
	}else if ( ulNumberOfUnderobjects < 256 ){
		cInitiation = 0x05;
		usBitsForNumberOfUnderobjects = 8;
	}else{
		cInitiation = 0x06;
		usBitsForNumberOfUnderobjects = 64;
	}
	
	const bool bInitiationStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, &cInitiation, 4 );
	if ( ! bInitiationStored ){
		return false;
	}
	
	const bool bNumberOfUnderObjectsStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, ulNumberOfUnderobjects, usBitsForNumberOfUnderobjects );
	if ( ! bNumberOfUnderObjectsStored ){
		return false;
	}
	bool bReturnValue = true;
	for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
		
		if ( (*actualUnderObject) != NULL ){
			
			const bool bUnderObjectStored = (*actualUnderObject)->storeBit(
				stream, cRestBits, uiRestBitPosition );
			if ( ! bUnderObjectStored ){
				return false;
			}
		}else{//not correct list element
			//error no subobject -> store NULL
			const char cNull = 0x00;
		
			const bool bNullStored = nBitStream::store( stream, cRestBits,
				uiRestBitPosition, &cNull, 4 );
			if ( ! bNullStored ){
				return false;
			}
			bReturnValue = false;
		}
	}
	return bReturnValue;
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
cFibElement * cList::copyInternal( const unsignedIntFib iObjectPoint ) const{

	if ( iObjectPoint == 0 ){
		//copy the whool object
		cList * pList = new cList( *this );
		
		//copy every underobject and insert it in the new list element
		for ( list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
			
			if ( (*actualUnderObject) != NULL ){
				
				cFibElement * pFibElement = (*actualUnderObject)->copyInternal();
#ifdef FEATURE_FAST_UPDATE
				if ( pFibElement ){
					pList->fibUnderObjects.push_back( pFibElement );
					pFibElement->pSuperiorElement = pList;
				}else{//ERROR while copying
					pList->deleteObject();
					return NULL;
				}
#else //FEATURE_FAST_UPDATE
				if ( pFibElement ){
					pList->fibUnderObjects.push_back( pFibElement );
				}else{//ERROR while copying
					pList->updateAllValues();
					deleteObject( pList );
					return NULL;
				}
#endif //FEATURE_FAST_UPDATE
			}else{
				pList->fibUnderObjects.push_back( NULL );
			}
		}
#ifdef FEATURE_FAST_UPDATE
		pList->updateAllCounters();
#endif //FEATURE_FAST_UPDATE
		return pList;
	}//else just copy one underobject and discard this list element

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




