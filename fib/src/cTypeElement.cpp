/**
 * @class cTypeElement
 * file name: cTypeElement.cpp
 * @author Betti Oesterholz
 * @date 03.06.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents an abstract Fib vectorelementtype.
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
 * This file contains the basisclass of all Fib vectorelementtyps.
 * Fib vectorelementtyps are typs of the elements in an Fib vector (e.g.
 * for an area the type of the elements is area).
 *
 */
/*
History:
03.06.2009  Oesterholz  created
13.05.2010  Oesterholz  the ordering of bit for the compressed storing corrected
30.09.2010  Oesterholz  Bugfix: DomainReal replaced with DomainRational
21.07.2011  Oesterholz  for the Xml-format "underfunction" to "subfunction"
24.07.2011  Oesterholz  cTypeExtObject for restoring added
25.08.2011  Oesterholz  underarea to subarea
16.11.2011  Oesterholz  cTypeExtSubobject for restoring added
04.12.2011  Oesterholz  cTypeFibSet for restoring added
05.12.2011  Oesterholz  cTypeFibMatrix for restoring added
02.01.2012  Oesterholz  subarea to area
05.01.2012  Oesterholz  externObjekt to externObject
21.01.2012  Oesterholz  externObjekt to externObject
29.01.2011  Oesterholz  FEATURE_EXT_SUBOBJECT_INPUT_VECTOR implemented:
	the input values are now a vector of values
31.01.2012  Oesterholz  isInherited() method added
12.02.2012  Oesterholz  restoreXml*() without restoring domain possible
01.04.2012  Oesterholz  DEBUG_RESTORE_XML implemented
01.08.2013  Oesterholz  FEATURE_EXT_SUBOBJECT_INPUT_VECTOR as default (not case removed)
*/


#include "cTypeElement.h"
#include "cTypeDimension.h"
#include "cTypeProperty.h"
#include "cTypeArea.h"
#include "cTypeUnderFunction.h"
#include "cTypeInVar.h"
#include "cTypeVariable.h"
#include "cTypeComments.h"
#include "cTypeExtObject.h"
#include "cTypeExtObjectInput.h"
#include "cTypeExtSubobject.h"
#include "cTypeFibSet.h"
#include "cTypeFibMatrix.h"
#include "cDomainNaturalNumberBit.h"

using namespace fib;


/**
 * destructor
 */
cTypeElement::~cTypeElement(){
	//pure virtual destructor -> do nothing
}


/**
 * This method checks, if this element type is compatible with the
 * given domain. Just domains which are compadible can be used for the
 * elements of this type.
 *
 * @param domain the domain, which should be compatible
 * @return true if the given domain is compatible, else false
 */
bool cTypeElement::isCompatible( const cDomain &domain ) const{

	const string szDomainType = domain.getType();
	
	if ( (szDomainType.compare( 0, 19, "DomainNaturalNumber") == 0) ||
			(szDomainType.compare( 0, 13, "DomainInteger") == 0) ||
			(szDomainType.compare( 0, 14, "DomainRational") == 0) ){
		//if the domain is an (single) number domain it is compatible
		return true;
	}//else no compatible domain
	return false;
}


/**
 * This Method returns a pointer to a new instance of the standart
 * domain for elements of this type.
 * You have to delete the returned object after usage.
 *
 * @return the standart domain for elements of this type
 */
cDomain *cTypeElement::getStandardDomain( ) const{
	return new cDomainNaturalNumberBit(16);
}


/**
 * This Method checks if the elementtype of the given type is equal to
 * the elementtype of this type.
 * Two elementtype are not equal if ther are for different fib -elements.
 *
 * @param typeElement the typeelement to compare with this typeelement
 * @return true if the elementtype of the given type is equal to the
 * 	elementtype of this type, else false
 */
bool cTypeElement::equalElementType( const cTypeElement & typeElement ) const{
	return ((*this) == typeElement);
}


/**
 * This Method checks if the given type is equal to this type.
 *
 * @param typeElement the typeelement to compare with this typeelement
 * @return true if the given type is equal to this type, else false
 */
bool cTypeElement::equal( const cTypeElement &typeElement ) const{
	return ((*this) == typeElement);
}


/**
 * This Method checks if the given type is equal to this type.
 *
 * @param typeElement the typeelement to compare with this typeelement
 * @return true if the given type is equal to this type, else false
 */
bool cTypeElement::operator==( const cTypeElement &typeElement ) const{
	return (getType() == typeElement.getType());
}


/**
 * This method restores a type in the XML -format from a TinyXml element.
 *
 * @pattern Factory Method
 * @param pXmlNode a pointer to the TinyXml node wher the type is stored in
 * @param outStatus an integer value with the errorvalue
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 * @return the pointer to the restored type, if it could be restored
 * 	else it is a NULL pointer
 */
cTypeElement * cTypeElement::restoreXmlType(
		const TiXmlElement * pXmlElement, intFib & outStatus ){
	
	pair< cTypeElement * , cDomain * > paRestoredPair =
		restoreXmlTypeWithDomain( pXmlElement, outStatus, false );
	
	if ( paRestoredPair.second ){
		//Warning: domain restored -> delete restored domain
		delete paRestoredPair.second;
		if ( outStatus == 0 ){
			outStatus = 1;
		}
	}
	
	return paRestoredPair.first;
}


/**
 * This method restores a type with a domain in the XML -format from an
 * TinyXml element.
 *
 * @pattern Factory Method
 * @param pXmlNode a pointer to the TinyXml node wher the type is stored in
 * @param outStatus an integer value with the errorvalue
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 * @param bRestoreDomain if true a domain is to be asumed in the type
 * 	element and it will be restored, else no domain will be restores
 * @return a pair with the pointers to the restored type and domain,
 * 	if one couldn't be restored it's pointer is NULL
 */
pair< cTypeElement * , cDomain * > cTypeElement::restoreXmlTypeWithDomain(
		const TiXmlElement * pXmlElement, intFib & outStatus,
		const bool bRestoreDomain ){
	
	if ( pXmlElement == NULL ){
		//Error: nothing to load
		outStatus = -1;
		return make_pair( (cTypeElement*)NULL, (cDomain *)NULL );
	}
	cTypeElement * pTypeRestored = NULL;
	cDomain * pDomainRestore     = NULL;
	
	const string szElementType( pXmlElement->Value() );
	
#ifdef DEBUG_RESTORE_XML
	printf( "Restoring type \"%s\" (outStatus now %i)\n", szElementType.c_str(), outStatus );
#endif
	
	if ( szElementType == "dim" ){
		pTypeRestored = new cTypeDimension( 0 );
		pDomainRestore = pTypeRestored->restoreXmlWithDomain(
			pXmlElement, outStatus, bRestoreDomain );
		
	}else if ( szElementType == "inVar" ){
		pTypeRestored = new cTypeInVar( 0 );
		pDomainRestore = pTypeRestored->restoreXmlWithDomain( 
			pXmlElement, outStatus, bRestoreDomain );
		
	}else if ( ( szElementType == "subfunction" ) || ( szElementType == "underfunction" ) ){
		//"underfunction" is depricated
		pTypeRestored = new cTypeUnderFunction();
		pDomainRestore = pTypeRestored->restoreXmlWithDomain( pXmlElement, outStatus );
		
	}else if ( ( szElementType == "area" ) || ( szElementType == "underarea" ) ){
		//"underarea" is depricated
		pTypeRestored = new cTypeArea();
		pDomainRestore = pTypeRestored->restoreXmlWithDomain(
			pXmlElement, outStatus, bRestoreDomain );
		
	}else if ( szElementType == "property" ){
		pTypeRestored = new cTypeProperty( 0 );
		pDomainRestore = pTypeRestored->restoreXmlWithDomain(
			pXmlElement, outStatus, bRestoreDomain );
		
	}else if ( szElementType == "variable" ){
		pTypeRestored = new cTypeVariable();
		pDomainRestore = pTypeRestored->restoreXmlWithDomain(
			pXmlElement, outStatus, bRestoreDomain );
		
	}else if ( szElementType == "comments" ){
		pTypeRestored = new cTypeComments();
		pDomainRestore = pTypeRestored->restoreXmlWithDomain(
			pXmlElement, outStatus, bRestoreDomain );
		
	}else if ( szElementType == "externObject" ){
		pTypeRestored = new cTypeExtObject();
		pDomainRestore = pTypeRestored->restoreXmlWithDomain(
			pXmlElement, outStatus, bRestoreDomain );
		
	}else if ( szElementType == "externObjectInput" ){
		pTypeRestored = new cTypeExtObjectInput( 0 );
		pDomainRestore = pTypeRestored->restoreXmlWithDomain(
			pXmlElement, outStatus, bRestoreDomain );
		
	}else if ( szElementType == "externSubobject" ){
		pTypeRestored = new cTypeExtSubobject( 0 );
		pDomainRestore = pTypeRestored->restoreXmlWithDomain(
			pXmlElement, outStatus, bRestoreDomain );
		
	}else if ( szElementType == "setElement" ){
		pTypeRestored = new cTypeFibSet();
		pDomainRestore = pTypeRestored->restoreXmlWithDomain(
			pXmlElement, outStatus, bRestoreDomain );
		
	}else if ( szElementType == "matrixElement" ){
		pTypeRestored = new cTypeFibMatrix();
		pDomainRestore = pTypeRestored->restoreXmlWithDomain(
			pXmlElement, outStatus, bRestoreDomain );
		
	}else{//Error: no type to restore
	
		outStatus = 2;
	}//TODO more typs
	
	return make_pair( pTypeRestored, pDomainRestore );
}


/**
 * This method restores a type from a bitstream, wher it is stored in the
 * compressed fib -format.
 *
 * @pattern Factory Method
 * @see store
 * @param iBitStream the stream where the type is stored in, because the
 * 	stream is an cReadBits, any number of bits can be
 * 	readed from it
 * @param outStatus an integer value with the errorvalue
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 * @return a pointer to the restored type or NULL
 */
cTypeElement * cTypeElement::restore( cReadBits & iBitStream, intFib & outStatus ){
	
	DEBUG_OUT_L2(<<"restore( iBitStream, outStatus="<<outStatus<<" )"<<endl);

	if ( ! iBitStream.getStream()->good() ){
		//Error: nothing to load
		outStatus = -1;
		return NULL;
	}
	cTypeElement * pTypeRestored = NULL;
	
	//read the typename
	char cTypeName = 0x00;
	unsigned int uiBitsRead = iBitStream.readBits( &cTypeName, 8 );
	if ( ! iBitStream.getStream()->good() ){
		outStatus = -2;
		DEBUG_OUT_EL2(<<"Error: Stream not good"<<endl);
		return NULL;
	}
	if ( uiBitsRead != 8 ){
		outStatus = -2;
		DEBUG_OUT_EL2(<<"Error: Not 8 bit restored"<<endl);
		return NULL;
	}
	iBitStream.rollbackBits( 8 );
	
	/*till now no 64 bit typnames so ignore bit 1 and ignore 2 and 3
	because parameters are loaded in the type classes*/
	const unsigned char cTypeNamePure = cTypeName & 0xF8;

	DEBUG_OUT_L3(<<"cTypeNamePure= 0x"<<hex<<cTypeNamePure<<dec<<endl);

	if ( cTypeNamePure == 0x08 ){
		pTypeRestored = new cTypeDimension( 0 );
		outStatus = pTypeRestored->restore( iBitStream );
		
	}else if ( cTypeNamePure == 0x10 ){
		pTypeRestored = new cTypeUnderFunction();
		outStatus = pTypeRestored->restore( iBitStream );
	
	}else if ( cTypeNamePure == 0x18 ){
		pTypeRestored = new cTypeArea();
		outStatus = pTypeRestored->restore( iBitStream );
	
	}else if ( cTypeNamePure == 0x20 ){
		pTypeRestored = new cTypeProperty( 0 );
		outStatus = pTypeRestored->restore( iBitStream );
		
	}else if ( cTypeNamePure == 0x28 ){
		pTypeRestored = new cTypeInVar( 0 );
		outStatus = pTypeRestored->restore( iBitStream );
		
	}else if ( cTypeNamePure == 0x88 ){
		pTypeRestored = new cTypeVariable();
		outStatus = pTypeRestored->restore( iBitStream );
	
	}else if ( cTypeNamePure == 0x90 ){
		pTypeRestored = new cTypeComments();
		outStatus = pTypeRestored->restore( iBitStream );
	
	}else if ( cTypeNamePure == 0xC0 ){
		pTypeRestored = new cTypeExtObject();
		outStatus = pTypeRestored->restore( iBitStream );
	
	}else if ( cTypeNamePure == 0xC8 ){
		pTypeRestored = new cTypeExtSubobject( 0 );
		outStatus = pTypeRestored->restore( iBitStream );
		
	}else if ( cTypeNamePure == 0xD0 ){
		pTypeRestored = new cTypeFibSet();
		outStatus = pTypeRestored->restore( iBitStream );
	
	}else if ( cTypeNamePure == 0xD8 ){
		pTypeRestored = new cTypeFibMatrix();
		outStatus = pTypeRestored->restore( iBitStream );
		
	}else if ( cTypeNamePure == 0xE0 ){
		pTypeRestored = new cTypeExtObjectInput( 0 );
		outStatus = pTypeRestored->restore( iBitStream );
	
	}else{//Error: no type to restore
		outStatus = 2;
	}//TODO more typs

	return pTypeRestored;
}


/**
 * @return true if domains of this type are inerted else false
 */
bool cTypeElement::isInherited() const{
	///as default domains are inherited
	return true;
}



/**
 * @return true if the given domain is a domain for counters (it only
 * 	contains positiv numbers), else false
 */
bool cTypeElement::isCounterDomain( const cDomain * pDomain ){
	
	if ( pDomain == NULL ){
		//no domain given
		return false;
	}
	if ( ! pDomain->isScalar() ){
		//domain not a number
		return false;
	}
	const string szDomainType = pDomain->getType();
	if ( szDomainType.compare( 0, 19, "DomainNaturalNumber") != 0 ){
		//if the domain isn't a natural number domain it is not a counter domain
		if ( szDomainType.compare( 0, 13, "DomainInteger") == 0 ){
			cDomainIntegerBasis * pDomainInteger =
				(cDomainIntegerBasis*)pDomain;
			if ( pDomainInteger->getMinimumUnscaled() < 0 ){
				//if the domain isn't a natural number domain it is not a counter domain
				return false;
			}else{
				return true;
			}
		}else{//not a counter domain
			return false;
		}
	}//else domain is a natural number domain -> counter domain
	return true;
}







