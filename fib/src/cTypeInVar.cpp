/**
 * @class cTypeInVar
 * file name: cTypeInVar.h
 * @author Betti Oesterholz
 * @date 07.10.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents an abstract Fib -inputvariabletype.
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
 * This file contains the basisclass of all Fib -inputvariabletype.
 * Fib -vectorelementtyps are typs of the elements in an Fib -vector (e.g.
 * for an underarea vector the type of the elements is underarea).
 *
 */
/*
History:
07.10.2009  Oesterholz  created
13.05.2010  Oesterholz  the ordering of bits for the compressed storing corrected
31.01.2012  Oesterholz  isInherited() method added
12.02.2012  Oesterholz  restoreXml*() without restoring domain possible
18.04.2012  Oesterholz  Bugfix: replace FirstChild()->ToElement() with
	FirstChildElement()
*/


#include "cTypeInVar.h"

#include "cDomainNaturalNumberBit.h"

#include "nBitStream.h"

using namespace fib;


/**
 * Standardconstructor for the input variablen type.
 *
 * @param iNumberOIfInputVariable the number of the input variable
 * 	for which this type stands
 */
cTypeInVar::cTypeInVar( unsignedIntFib uiNumberOfInputVariable ):
		uiNumberOfInputVariable( uiNumberOfInputVariable ){
	//nothing to do
}


/**
 * This Function returns for the type of the element an number.
 * The values, which are returned, mean:
 * 	- 1: cTypeDimension
 * 	- 2: cTypeUnderArea
 * 	- 3: cTypeUnderFunction
 * 	- 5: cTypeInVar
 * 	- 6: cTypeProperty
 * 	- 10: cTypeVariable
 * 	- 11: cTypeComments
 * 	- 12: cTypeExtObject
 * 	- 13: cTypeExtSubobject
 * 	- 14: cTypeFibSet
 * 	- 15: cTypeFibMatrix
 * 	- 16: cTypeExtObjectInput
 *
 * @return for the type of the element an number
 */
unsignedIntFib cTypeInVar::getType() const{
	return 5;
}


/**
 * This Method checks if the given type is equal to this type.
 *
 * @return true if the given type is equal to this type, else false
 */
bool cTypeInVar::operator==( const cTypeElement & typeElement ) const{
	return (getType() == typeElement.getType()) &&
		(getNumberOfInputVariable() ==
			((cTypeInVar*)(&typeElement))->getNumberOfInputVariable());
}


/**
 * This Method clones this object.
 *
 * @return a clone of this object
 */
cTypeInVar * cTypeInVar::clone() const{
	return new cTypeInVar( getNumberOfInputVariable() );
}

/**
 * This method evaluades the size of the typeelement in bits in the
 * compressed file form.
 *
 * @see store()
 * @return the size of the typeelement in bits in the compressed form
 */
unsignedLongFib cTypeInVar::getCompressedSize() const{
	
	if ( getNumberOfInputVariable() < 256 ){
		//short input variable number -> 8 bit parameter is enought
		return 8 + 8;
	}//else
	return 8 + 64;
}

/**
 * This method stores this type in the XML -format into the
 * given stream.
 *
 * @param ostream the stream where domains should be stored to
 * @param domain the domain which should be stored to this type;
 * 	if a Nullpointer NULL (the standardvalue) is given, no domain
 * 	will be stored to this type
 * @return true if this type are stored, else false
 */
bool cTypeInVar::storeXml( ostream & ostream,
		const cDomain * domain ) const{
	
	ostream<<"<inVar number=\""<< getNumberOfInputVariable();
	
	//if given write the domain to the stream
	if ( domain != NULL ){
		
		ostream<<"\">"<<endl;

		bool bDomainStored = domain->storeXml( ostream );
		if ( ! bDomainStored ){
			return false;
		}
		ostream<<"</inVar>"<<endl;
	}else{
		ostream<<"\"/>"<<endl;
	}

	return true;
}


/**
 * This method restores a type with a domain in the XML -format from an
 * TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node wher the type is stored in
 * @param outStatus an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 * @param bRestoreDomain if true a domain is to be asumed in the type
 * 	element and it will be restored, else no domain will be restores
 * @return a pointer to the restored domain, or NULL if it couldn't be restored
 */
cDomain * cTypeInVar::restoreXmlWithDomain( const TiXmlElement * pXmlElement,
		intFib & outStatus, const bool bRestoreDomain ){
	
	//check the element type
	if ( pXmlElement == NULL ){
		//Error: noting to restore
		outStatus = -1;
		return NULL;
	}
	string szElementType( pXmlElement->Value() );
	if ( szElementType != "inVar" ){
		//Error: wrong element type to restore
		outStatus = -2;
		return NULL;
	}
	
	int iNumberOfInputVariable = 0;
	const char * szXmlNumberOfInputVariable = pXmlElement->Attribute(
		"number", &iNumberOfInputVariable );
	if ( szXmlNumberOfInputVariable == NULL ){
		//Warning: count of dimensions missing
		outStatus = 2;
	}
	uiNumberOfInputVariable = iNumberOfInputVariable;
	
	if ( bRestoreDomain ){
		//restore the domain
		const TiXmlElement * pXmlElementType = NULL;
		if ( pXmlElement->FirstChild() ){
			
			pXmlElementType = pXmlElement->FirstChildElement();
		}
		const TiXmlElement * pXmlElementDomain = NULL;
		for( ; pXmlElementType != NULL;
				pXmlElementType = pXmlElementType->NextSiblingElement() ){
			
			if ( pXmlElementDomain == NULL ){
				pXmlElementDomain = pXmlElementType;
			}else{//Warning: more than one domain to restore
				outStatus = 2;
				break;
			}
		}
		//restore the domain
		cDomain * pRestoredDomain = NULL;
		if ( pXmlElementDomain ){
			int iDomainRestoreReturn = 0;
			pRestoredDomain = cDomain::restoreXml( pXmlElementDomain, iDomainRestoreReturn );
			
			if ( iDomainRestoreReturn != 0 ){
				outStatus = iDomainRestoreReturn;
			}
		}else{
			outStatus = 2;
		}
		return pRestoredDomain;
	}//end if restore domain + else no domain to return
	return NULL;
}


/**
 * This method stores this typeelement in the compressed fib -format
 * into the given stream.
 * It is needed because the stream can yust store byts but the size of
 * fib -elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the fib -elements.
 *
 * @see cFibElement::store
 * @param stream the stream where this typeelement should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if the typeelement is stored, else false
 */
bool cTypeInVar::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	if ( uiRestBitPosition >= 8){
		//error in input
		return false;
	}

	char cInVarName = 0x28; //the name "inVar"
	if ( uiNumberOfInputVariable < 256 ){
		//short input variable number -> 8 bit parameter is enought
		cInVarName = cInVarName | 0x02;
		unsigned char cParameter = getNumberOfInputVariable();
		
		bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			&cInVarName, 8 );
		if ( ! bNameStored ){
			return false;
		}
		bool bParameterStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			(unsigned long)(cParameter), 8 );
		if ( ! bParameterStored ){
			return false;
		}

	}else{
		//long input variable number -> 64 bit parameter
		cInVarName = cInVarName | 0x04;
		unsigned long long ulParameter = getNumberOfInputVariable();
		
		bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			&cInVarName, 8 );
		if ( ! bNameStored ){
			return false;
		}
		bool bParameterStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
			ulParameter, 64 );
		if ( ! bParameterStored ){
			return false;
		}
	}
	return true;
}


/**
 * This method restores a type from a bitstream, wher it is
 * stored in the compressed fib -format.
 *
 * @see store
 * @param iBitStream the stream where the type is stored in,
 * 	because the stream is an cReadBits, any number of bits can be
 * 	readed from it
 * @return an integervalue with the errorvalue
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 */
intFib cTypeInVar::restore( cReadBits & iBitStream ){
	
	if ( ! iBitStream.getStream()->good() ){
		//Error: nothing to load
		return -1;
	}

	//read the typename
	char cTypeName = 0x00;
	unsigned int uiBitsRead = iBitStream.readBits( &cTypeName, 8 );
	if ( ! iBitStream.getStream()->good() ){
		return -2;
	}
	if ( uiBitsRead != 8 ){
		return -2;
	}
	if ( (cTypeName & 0xF8) != 0x28 ){
		//warning: wrong type
		return -2;
	}
	if ( (cTypeName & 0x06) == 0x02 ){
		//short input variable number -> 8 bit parameter is enought
		unsignedIntFib uiNumberInVar = 0x00;
		uiBitsRead = iBitStream.readBits( uiNumberInVar, 8 );
		if ( ! iBitStream.getStream()->good() ){
			return -2;
		}
		if ( uiBitsRead != 8 ){
			return -2;
		}
		uiNumberOfInputVariable = uiNumberInVar;
	
	}else if ( (cTypeName & 0x06) == 0x04 ){
		//long input variable number -> 64 bit parameter
		unsignedLongFib ulNumberInVar = 0;
		uiBitsRead = iBitStream.readBits( ulNumberInVar, 64 );
		if ( ! iBitStream.getStream()->good() ){
			return -2;
		}
		if ( uiBitsRead != 64 ){
			return -2;
		}
		uiNumberOfInputVariable = ulNumberInVar;
	}else{//warning: wrong parameter
		uiNumberOfInputVariable = 0;
		return -2;
	}
	return 0;
}


/**
 * @return true if domains of this type are inerted else false
 */
bool cTypeInVar::isInherited() const{
	///domains for input variables are not inerhited
	return false;
}



/**
 * @return the number of the input variable for which this type stands
 */
unsignedIntFib cTypeInVar::getNumberOfInputVariable() const{
	return uiNumberOfInputVariable;
}


