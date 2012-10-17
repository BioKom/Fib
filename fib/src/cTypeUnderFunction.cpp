/**
 * @class cTypeUnderFunction
 * file name: cTypeUnderFunction.h
 * @author Betti Oesterholz
 * @date 22.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents an abstract Fib-subfunctions.
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
 * This class represents an abstract Fib-subfunctions.
 * Fib-subfunctions are the elements to evalue to a function.
 *
 * @see cUnderFunction
 */
/*
History:
22.04.2010  Oesterholz  created
13.05.2010  Oesterholz  the ordering of bits for the compressed storing corrected
21.07.2011  Oesterholz  for the Xml-format "underfunction" to "subfunction"
12.02.2012  Oesterholz  restoreXml*() without restoring domain possible
18.04.2012  Oesterholz  Bugfix: replace FirstChild()->ToElement() with
	FirstChildElement()
*/


#include "cTypeUnderFunction.h"

#include "cDomainNaturalNumberBit.h"

#include "nBitStream.h"

using namespace fib;



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
unsignedIntFib cTypeUnderFunction::getType() const{
	return 3;
}


/**
 * This Method clones this object.
 *
 * @return a clone of this object
 */
cTypeUnderFunction * cTypeUnderFunction::clone() const{
	return new cTypeUnderFunction();
}

/**
 * This method evaluades the size of the typeelement in bits in the
 * compressed file form.
 *
 * @see store()
 * @return the size of the typeelement in bits in the compressed form
 */
unsignedLongFib cTypeUnderFunction::getCompressedSize() const{

	return 8;
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
bool cTypeUnderFunction::storeXml( ostream & ostream,
		const cDomain * domain ) const{
	
	ostream<<"<subfunction";
	
	//if given write the domain to the stream
	if ( domain != NULL ){
		
		ostream<<">"<<endl;

		bool bDomainStored = domain->storeXml( ostream );
		if ( ! bDomainStored ){
			return false;
		}
		ostream<<"</subfunction>"<<endl;
	}else{
		ostream<<"/>"<<endl;
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
cDomain * cTypeUnderFunction::restoreXmlWithDomain( const TiXmlElement * pXmlElement,
		intFib & outStatus, const bool bRestoreDomain ){
	
	//check the element type
	if ( pXmlElement == NULL ){
		//Error: noting to restore
		outStatus = -1;
		return NULL;
	}
	string szElementType( pXmlElement->Value() );
	if ( ( szElementType != "subfunction" ) && ( szElementType != "underfunction" ) ){
		//underfunction is depricated
		//Error: wrong element type to restore
		outStatus = -2;
		return NULL;
	}
	
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
	}//end if restore domain

	return NULL;
}


/**
 * This method stores this typeelement in the compressed Fib-format
 * into the given stream.
 * It is needed because the stream can yust store byts but the size of
 * Fib-elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the Fib-elements.
 *
 * @see cFibElement::store
 * @param stream the stream where this typeelement should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if the typeelement is stored, else false
 */
bool cTypeUnderFunction::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	if ( uiRestBitPosition >= 8){
		//error in input
		return false;
	}
	char cInVarName = 0x10; //the name "subfunction"
	
	bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
		&cInVarName, 8 );
	if ( ! bNameStored ){
		return false;
	}

	return true;
}


/**
 * This method restores a type from a bitstream, wher it is
 * stored in the compressed Fib-format.
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
intFib cTypeUnderFunction::restore( cReadBits & iBitStream ){
	
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
	if ( cTypeName != 0x10 ){
		//warning: wrong type
		return -2;
	}
	return 0;
}




