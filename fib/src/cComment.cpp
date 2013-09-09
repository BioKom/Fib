/**
 * @class cComment
 * file name: cComment.cpp
 * @author Betti Oesterholz
 * @date 26.07.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the fib-commentelement.
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
 * This class represents the commentelement of the fib-multimedialanguage.
 * An commentelement contains a key- value- pair. Both key and value are
 * strings. The key is the key /identifier for the comment type. (e.g. an
 * key could be "autor" to indicate, that this value is the name of the
 * author of the underobject.)
 * The value is the commentvalue for the key and underobject.
 *
 */
/*
History:
26.07.2010  Oesterholz  created
17.10.2011  Oesterholz  FEATURE_OUTPUT_ELEMENT_NUMBER_XML implemented
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
02.12.2011  Oesterholz  XML format: the "value" can also loaded as a
	XML element
03.06.2013  Oesterholz  SWITCH_JUST_STORE_AND_EVALUE implemented
30.07.2013  Oesterholz  method assignValues() added
*/


#include "cComment.h"

#include "cTypeComments.h"
#include "cDomainNaturalNumberBit.h"

#include <algorithm>


using namespace fib;


#ifdef FEATURE_SIMPLE_CONSTRUCTOR

/**
 * parameterconstructor
 *
 * @param szInKey the key for the comment ( @see szKey )
 * @param szInValue the value for the comment ( @see szValue )
 * @param pInUnderobject the fib-element which is the underobject of
 * 	this fib-element (it also stands next in the order of fib-elements)
 * @param pInSuperiorElement the fib-element in which this
 * 	commentelement is an underobject
 */
cComment::cComment( const string & szInKey, const string & szInValue,
		cFibElement * pInUnderobject, cFibElement * pInSuperiorElement ):
		cFibLimb( pInUnderobject, pInSuperiorElement ),
		szKey( szInKey ), szValue( szInValue ), ulCommentNumber( 0 ){
	
	if ( pInSuperiorElement ){
		pInSuperiorElement->insertObjectInElement( this );
	}else{
		updateAllValues();
	}
}

#else //FEATURE_SIMPLE_CONSTRUCTOR

/**
 * parameterconstructor
 *
 * @param szInKey the key for the comment ( @see szKey )
 * @param szInValue the value for the comment ( @see szValue )
 * @param pInSuperiorElement the fib-element in which this
 * 	commentelement is an underobject
 * @param pInPreviousFibElement the fib-element, which stands in the order
 * 	of fib-elements befor this fib-element
 * @param pInUnderobject the fib-element which is the underobject of
 * 	this fib-element (it also stands next in the order of fib-elements)
 */
cComment::cComment( const string & szInKey, const string & szInValue,
		cFibElement * pInSuperiorElement, cFibElement * pInPreviousFibElement,
		cFibElement * pInUnderobject ):
		cFibLimb( pInSuperiorElement, pInPreviousFibElement, pInUnderobject ),
		szKey( szInKey ), szValue( szInValue ), ulCommentNumber( 0 ){
	
	updateAllValues();
}
#endif //FEATURE_SIMPLE_CONSTRUCTOR


/**
 * copyconstructor
 * This copyconstructor constructs a copy of the given commentelement.
 * It dosn't copy other commentelements than the given, even if ther are
 * in the commentelement.
 *
 * @param commentElement the commentelement to copy
 */
cComment::cComment( const cComment &commentElement ):
		cFibLimb( commentElement ),
		szKey( commentElement.szKey ), szValue( commentElement.szValue ),
		ulCommentNumber( 0 ){
	
}


/**
 * The constructor for restoring a commentelement from an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node the fib-object is stored in
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
cComment::cComment( const TiXmlElement * pXmlElement, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables ):
		szKey( "" ), szValue( "" ){
	
	if ( pXmlElement == NULL ){
		//noting to restore
		outStatus = -1;
		return;
	}
	string szElementType( pXmlElement->Value() );
	if ( szElementType != "comment" ){
		//wrong element type to restore
		outStatus = -2;
		return;
	}
	//read the variable number
	const char * szXmlKey = pXmlElement->Attribute( "key" );
	
	if ( szXmlKey == NULL ){
		outStatus = 2;
	}else{
		szKey = szXmlKey;
	}
	bool bValueRestored = false;
	const char * szXmlValue = pXmlElement->Attribute( "value" );
	if ( szXmlValue != NULL ){
		szValue = szXmlValue;
		bValueRestored = true;
	}
	
	for ( const TiXmlNode * pChild = pXmlElement->FirstChild();
			pChild != NULL; pChild = pChild->NextSibling() ) {
		
		int iType = pChild->Type();
		
		switch ( iType ){
			case TiXmlNode::ELEMENT:{
				/*check if this is a valid fib-element xml -element, create
				the apropirate fib-element and call its restoreXml() method*/
				//restore the underobject
				if ( ! bValueRestored ){
					const TiXmlElement * pXmlElement = pChild->ToElement();
					const string szElementName = pXmlElement->Value();
					if ( szElementName == "value" ){
						
						const char * szXmlValue = pXmlElement->GetText();
						szValue = "";
						if ( szXmlValue != NULL ){
							szValue = szXmlValue;
						}
						bValueRestored = true;
						
						continue;//check next element
					}
				}
				
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
				}else{//to many underobjects -> no correct comment element
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
				//invalid commentelement
				if ( outStatus ){
					outStatus = 2;
				}
				continue;
		}
	}
	if ( ! bValueRestored ){
		outStatus = 2;
	}
	if ( pUnderObject == NULL ){
		outStatus = -2;
		return;
	}
}


/**
 * This constructor restores a commentelement from the stream where it is
 * stored in the compressed fib-format.
 * This constructor is for internal use only.
 *
 * @param iBitStream the stream wher the commentelement is stored to in,
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
cComment::cComment( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains,
		cRoot * pNextRoot ):
		szKey( "" ), szValue( "" ){
	
	if ( ! iBitStream.getStream()->good() ){
		outStatus = -1;
		return;
	}
	if ( pNextRoot == NULL ){
		outStatus = -1;
		return;
	}
	//restore the comment number
	
	//restore the comment number
	//get the domain for the comment numbers in this vector
	cTypeComments typeComments;
	//return the comment numbers domain
	cDomainIntegerBasis * pDomainComment = (cDomainIntegerBasis*)
		validDomains.getDomainForElement( typeComments );
	bool bStandardDomainComments = false;
	if ( pDomainComment == NULL ){
		//use the standrad domain
		pDomainComment = (cDomainIntegerBasis*)typeComments.getStandardDomain();
		bStandardDomainComments = true;
	}
	ulCommentNumber = pDomainComment->restoreIntegerValue( iBitStream, outStatus );
	if ( outStatus < 0 ){
		if ( bStandardDomainComments ){
			delete pDomainComment;
		}
		return;
	}
	//the value pair of the comments get extract in the next root element

	if ( bStandardDomainComments ){
		delete pDomainComment;
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
 * @return a character for the typ of the fib-element
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
char cComment::getType() const{
	return 'c';
}


/**
 * This method evaluades the fib-object.
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
bool cComment::evalueObject( iEvaluePosition & evaluePosition,
		const unsignedIntFib objectPoint,
		list<cVectorProperty> & liVecProperties ) const{
	
	if ( pUnderObject == NULL ){
		//nothing to evalue
		return false;
	}
	//evalue the underobject
	return pUnderObject->evalueObject( evaluePosition, objectPoint, liVecProperties );
}


/**
 * This method evaluades the fib-object.
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
bool cComment::evalueObject( iEvalueFibElement & evalueFibElement,
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
	}//else if this element shouldn't be returned -> evalue the main -fib-object

	if ( pUnderObject == NULL ){
		//nothing to evalue
		return false;
	}
	//evalue the underobject
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
unsignedLongFib cComment::getTimeNeed( unsignedLongFib lMaxTime ) const{
	
	if ( lMaxTime == 1 ){
		return 1;
	}
	if ( pUnderObject == NULL ){
		return 1;
	}

	//evalue the underobject
	return pUnderObject->getTimeNeed( lMaxTime - 1 ) + 1;
}


/**
 * This method evaluades the size of the fib-object in bits in the
 * compressed file form.
 * The optionalpart field of commentelements will be ignored.
 *
 * @see store()
 * @return the size of the fib-object in bits in the compressed form
 */
unsignedLongFib cComment::getCompressedSize() const{
	
	unsignedLongFib ulCompressedSize = 4;
	
	//evalue the bits needed for the comment number
	//get the domain for the comments in this vector
	cTypeComments typeComments;
	//get the value domain for variables
	cDomains validDomains = getValidValueDomains();
	//return the variable domain
	cDomainSingle * commentsDomain = (cDomainSingle*)
		validDomains.getDomainForElement( typeComments );
	bool bStandardDomainUsed = false;
	if ( commentsDomain == NULL ){
		//use the standrad domain
		commentsDomain = (cDomainSingle*)typeComments.getStandardDomain();
		bStandardDomainUsed = true;
	}
	ulCompressedSize += commentsDomain->getCompressedSizeForValue();
	if ( bStandardDomainUsed ){
		delete commentsDomain;
	}

	//add compressed size for the underobject
	if ( pUnderObject != NULL ){
		ulCompressedSize += pUnderObject->getCompressedSize();
	}
	return ulCompressedSize;
}


/**
 * This method copies the fib-element on the specified position.
 * Variables which are not defined in the fib-element but used
 * don't change ther reference.
 *
 * @see getType()
 * @param cType the type of the fib-element to copy
 * @param elementPoint the number of the fib-element, in the order of
 * 	fib-elements of the given type cType, to copy
 * @return the copy of the fib-element
 */
cFibElement *cComment::copyElement( const char cType, const unsignedIntFib
		elementPoint, bool bAbsolute ) const{
	
	if ( elementPoint == 0 ){
		//copy this element
		return new cComment( *this );
	}//else get the fib-element and copy it
	
	const cFibElement * pFibElementToCopy = getConstFibElement(
		cType, elementPoint, bAbsolute );
	
	if ( pFibElementToCopy ){
		return ( pFibElementToCopy->copyElement( 'u', 0 ) );
	}//else
	return NULL;
}

#ifndef SWITCH_JUST_STORE_AND_EVALUE

/**
 * This method assigns / copies the values from the given Fib element
 * fibElement to this Fib element. This means, it will copy everything
 * of the Fib element fibElement except pointers to other Fib elements
 * (e. g. for subobjects), these will remain the same.
 * For that both Fib elements have to be of the same type.
 *
 * @see getType()
 * @param fibElement the Fib element, from which to assign / copy the values
 * @return true if the values could be copied from the given Fib element
 * 	fibElement, else false
 */
bool cComment::assignValues( const cFibElement & fibElement ){
	
	if ( fibElement.getType() != getType() ){
		//both Fib elements not of the same type -> can't assign values
		return false;
	}
	//copy key and value
	cComment * pOtherComment = ((cComment*)(&fibElement));
	
	szKey   = pOtherComment->szKey;
	szValue = pOtherComment->szValue;
	
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
bool cComment::equalInternal( const cFibElement & fibObject,
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
bool cComment::equalElementInternal( const cFibElement & fibElement,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{

	if ( getType() != fibElement.getType() ){
		return false;
	}
	cComment * pCommentElement = (cComment*)(&fibElement);
	if ( getKey() != pCommentElement->getKey() ){
		return false;
	}
	if ( getValue() != pCommentElement->getValue() ){
		return false;
	}
	return true;
}

#else //FEATURE_EQUAL_FIB_OBJECT

/**
 * This method checks if the given fib-object is equal to this Fib
 * -object.
 * Variables can be others, but must be defined and used in equivalent
 * fib-elements.
 *
 * @param fibObject the fib-object to which this fib-object should be
 * 	equal
 * @return true if this fib-object is equal to the given fib-object,
 * 	else false
 */
bool cComment::equal( const cFibElement & fibObject ) const{

	if ( ! cFibLimb::equal( fibObject ) ){
		return false;
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
 * @return true if this fib-element is equal to the given fib-object,
 * 	else false
 */
bool cComment::equalElement( const cFibElement & fibElement ) const{

	if ( getType() != fibElement.getType() ){
		return false;
	}
	cComment * pCommentElement = (cComment*)(&fibElement);
	if ( getKey() != pCommentElement->getKey() ){
		return false;
	}
	if ( getValue() != pCommentElement->getValue() ){
		return false;
	}
	return true;
}

#endif //FEATURE_EQUAL_FIB_OBJECT

#endif //SWITCH_JUST_STORE_AND_EVALUE

/**
 * This method stores this fib-object in the XML -format into the
 * given stream.
 *
 * @param stream the stream where this fib-object should be stored to
 * @return true if this fib-object is stored, else false
 */
bool cComment::storeXml( ostream &stream ) const{

	bool bReturnValue = true;
//TODO strings zu XML -kompatible strings konvertieren
	const string szValue = getValue();
	if ( ( szValue.length() < 20 ) &&
			( szValue.find_first_of( "\n" ) == string::npos ) ){
		//value staring has less then 20 characters and contains no newline
#ifdef FEATURE_OUTPUT_ELEMENT_NUMBER_XML
		stream<<"<comment elementNr=\""<<getNumberOfElement()<<"\" "<<
			"key=\""<< getKey() <<"\" value=\""<< szValue <<"\">"<<endl;
#else //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
		stream<<"<comment key=\""<< getKey() <<"\" value=\""<< szValue <<"\">"<<endl;
#endif //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
	}else{
#ifdef FEATURE_OUTPUT_ELEMENT_NUMBER_XML
		stream<<"<comment elementNr=\""<<getNumberOfElement()<<"\" "<<
			"key=\""<< getKey() <<"\">"<<endl;
#else //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
		stream<<"<comment key=\""<< getKey() <<"\">"<<endl;
#endif //FEATURE_OUTPUT_ELEMENT_NUMBER_XML
		stream<<"<value>"<<szValue<<"</value>"<<endl;
	}
	if ( pUnderObject ){
		bReturnValue &= pUnderObject->storeXml( stream );
	}
	stream<<"</comment>"<<endl;
	return bReturnValue;
}


/*
 * commentelement methods
 */


/**
 * @return the key of the comment ( @see szKey )
 */
string cComment::getKey() const{
	
	return szKey;
}


/**
 * @param szInKey the key for the comment ( @see szKey )
 */
void cComment::setKey( const string & szInKey ){
	
	szKey = szInKey;
}


/**
 * @return the value of the comment ( @see szValue )
 */
string cComment::getValue() const{
	
	return szValue;
}

/**
 * @param szInValue the value for the comment ( @see szValue )
 */
void cComment::setValue( const string & szInValue ){
	
	szValue = szInValue;
}



/**
 * This method stores this fib-object in the compressed fib-format
 * into the given stream.
 * It is needed becouse the stream can yust store byts but the size of
 * fib-elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the fib-elements.
 * Beware: You need to call storeBit() of the root -elements with the
 * domain for the comment or the comment will not be readebel.
 *
 * @see store
 * @param stream the stream where this fib-object should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if this fib-object is stored, else false
 */
bool cComment::storeBit( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{

	if ( pUnderObject == NULL ){
		return false;
	}
	char cInitiation = 0x07;
	const bool bInitiationStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, &cInitiation, 4 );
	if ( ! bInitiationStored ){
		return false;
	}
	//store the comment counter
	//get the domain for the comment counter
	cTypeComments typeComments;
	//get the value domain for the comment counter
	cDomains validDomains = getValidValueDomains();
	//return the comment counter domain
	cDomainSingle * commentsDomain = (cDomainSingle*)
		validDomains.getDomainForElement( typeComments );
	bool bStandardDomainUsed = false;
	if ( commentsDomain == NULL ){
		//use the standrad domain
		commentsDomain = (cDomainSingle*)typeComments.getStandardDomain();
		bStandardDomainUsed = true;
	}
	const bool bVariableStored = commentsDomain->storeValue(
		ulCommentNumber, stream, cRestBits, uiRestBitPosition );
	if ( ! bVariableStored ){
		return false;
	}
	if ( bStandardDomainUsed ){
		delete commentsDomain;
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
unsignedIntFib cComment::enumerateVariablesForStoring(
		unsignedIntFib uiLastVariableNumber ){

	return cFibLimb::enumerateVariablesForStoring( uiLastVariableNumber );
}


/**
 * This method copies the connected object with the given number in the
 * order of connected objects.
 * For this every fib-element, beginning from this fib-element, that
 * is part of the connected object will be copied.
 * Variables which are not defined in the connected object but used
 * don't change ther reference.
 * It is an helpmethod for the copy method. It dosn't update the
 * structural information of the created fib-object.
 *
 * @param iObjectPoint the number of the connected object to copy;
 * 	the standartvalue is 0 for coping the complet actual object
 * @return the copy of the connected object or NULL if non such exists
 */
cFibElement *cComment::copyInternal( const unsignedIntFib iObjectPoint ) const{

	cComment * pComment = NULL;

	if ( pUnderObject ){
		pComment = new cComment( *this );
		//copy the underobject
		cFibElement * pCopyUnderobject = pUnderObject->copyInternal( iObjectPoint );
		if ( pCopyUnderobject == NULL ){
			//no such objectpoint
			delete pComment;
			return NULL;
		}
		pComment->pUnderObject = pCopyUnderobject;
#ifdef FEATURE_FAST_UPDATE
		if ( pComment->pUnderObject ){
			pComment->pUnderObject->pSuperiorElement = pComment;
		}
#endif //FEATURE_FAST_UPDATE
	}else{//no underobject
		if ( iObjectPoint == 0 ){
			//just copy if this is the correct objectpoint
			pComment = new cComment( *this );
		}
	}
	return pComment;
}












