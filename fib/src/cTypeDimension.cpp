/**
 * @class cTypeDimension
 * file name: cTypeDimension.cpp
 * @author Betti Oesterholz
 * @date 03.06.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents Fib -dimensionselementtyps.
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
 * This file contains the basisclass of all Fib -dimensionselementtyps.
 * Fib -dimensionselementtyps are typs of the elements in an Fib 
 * -positionsvector.
 *
 */
/*
History:
03.06.2009  Oesterholz  created
13.05.2010  Oesterholz  the ordering of bit for the compressed storing corrected
12.02.2012  Oesterholz  restoreXml*() without restoring domain possible
27.02.2012  Oesterholz  DIRECTION_ANYWHERE added
18.04.2012  Oesterholz  Bugfix: replace FirstChild()->ToElement() with
	FirstChildElement()
*/



#include "cTypeDimension.h"

#include "cDomainVector.h"
#include "cDomainSingle.h"
#include "cDomainNaturalNumberBit.h"


using namespace fib;


/**
 * The constructor for dimension typs.
 *
 * @param iNumberOfDimensions the number of dimensions this type
 *		represents
 */
cTypeDimension::cTypeDimension( unsignedIntFib iNumberOfDimensions ):
		dimensionMapping( iNumberOfDimensions ){

	for ( unsignedIntFib actualDimension = 0;
			actualDimension<iNumberOfDimensions; actualDimension++ ){
		//init dimensionmappings with defaultvalues
		dimensionMapping[actualDimension] = actualDimension+1;
	}

}


/**
 * The constructor for dimension typs.
 *
 * @param dimensionMapping the mappings for the dimensions
 */
cTypeDimension::cTypeDimension( vector<unsignedIntFib> dimensionMapping  ):
		dimensionMapping( dimensionMapping ){
	
	//search for duplicate values
	if ( 0 < this->dimensionMapping.size() ){
		for ( unsignedIntFib actualDimension = 0;
				actualDimension < (this->dimensionMapping.size() - 1);
				actualDimension++ ){
			
			if ( this->dimensionMapping[actualDimension] == 0 ){
				continue;//mapping 0 is OK
			}
	
			for ( unsignedIntFib checkDimension=actualDimension+1;
					checkDimension<this->dimensionMapping.size();
					checkDimension++ ){
				
				if ( this->dimensionMapping[checkDimension] == 0 ){
					continue;//mapping 0 is OK
				}
				if ( this->dimensionMapping[checkDimension] ==
						this->dimensionMapping[actualDimension] ){
					//duplicate mapping-> change duplicate to 0
					this->dimensionMapping[checkDimension] = 0;
				}
			}
		}
	}

}


/**
 * The copyconstructor for dimension typs.
 *
 * @param typeDimension the type dimension to copy
 */
cTypeDimension::cTypeDimension( const cTypeDimension &typeDimension ):
	dimensionMapping( typeDimension.dimensionMapping ){
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
unsignedIntFib cTypeDimension::getType() const{
	return 1;
}


/**
 * This Method returns a pointer to a new instance of the standart
 * domain for elements of this dimension type.
 * The returned standarddomain is adapted to the number of dimensions of this
 * object. If you want the global standarddomain, please construct a
 * cTypeDimension object with the constructor without parameters. ( The
 * standard constructor.)
 * You have to delete the returned object after usage.
 *
 * @return the standart domain for elements of this type
 */
cDomain *cTypeDimension::getStandardDomain() const{
	
	//construct the vectordomain for the type
	cDomainVector *vectorDomain;
	vector<cDomainSingle*> vecDomains( dimensionMapping.size() );
	for ( unsignedIntFib actualDimension = 0;
			actualDimension < dimensionMapping.size(); actualDimension++ ){
			
		vecDomains[ actualDimension ] = new cDomainNaturalNumberBit( 16 );
	}
	vectorDomain = new cDomainVector( vecDomains );
	
	for ( unsignedIntFib actualDimension = 0;
			actualDimension < dimensionMapping.size(); actualDimension++ ){
			
		delete vecDomains[ actualDimension ];
	}
	return vectorDomain;
}


/**
 * This method checks, if this element type is compatible with the
 * given domain. Just domains which are compadible can be used for the
 * elements of this type.
 *
 * @param domain the domain, which should be compatible
 * @return true if the given domain is compatible, else false
 */
bool cTypeDimension::isCompatible( const cDomain &domain ) const{

	string szDomainType = domain.getType();
	
	if ( szDomainType.compare( 0, 12, "DomainVector" ) == 0 ){
		/*if the domain is an vector domain 
		-> check the number of vectorelements vor the properties with 
		standard domains*/
		
		const unsignedIntFib uiNumberOfDomainVectorElements =
			((cDomainVectorBasis*)(&domain))->getNumberOfElements();

		if ( uiNumberOfDomainVectorElements == getNumberOfDimensions() ){
			return true;
		}
	}
	return false;
}


/**
 * @return the number of dimensions of the Fib -object
 */
unsignedIntFib cTypeDimension::getNumberOfDimensions() const{

	return (unsignedIntFib)( dimensionMapping.size() );
}


/**
 * This method returns in which direction the iDimensionNumber dimension
 * is mapped.
 *
 * @param iDimensionNumber the number of the dimension for which the
 * 	mapping is to be returned
 * @return the direction in which the iDimensionNumber dimension is
 * 	mapped
 */
unsignedIntFib cTypeDimension::getDimensionMapping(
		unsignedIntFib iDimensionNumber ) const{
	
	if ( ( iDimensionNumber<1 ) ||
			( getNumberOfDimensions()<iDimensionNumber ) ){
		//no existing dimension so the mapping is 0 for "none"
		return 0;
	}

	return dimensionMapping[iDimensionNumber-1];
}


/**
 * This method sets in which direction the iDimensionNumber dimension
 * is mapped.
 *
 * @param iDimensionNumber the number of the dimension for which the
 * 	mapping is to be set
 * @param iMapping the mapping to set for the dimension
 * @return true if the mapping for the iDimensionNumber dimension is
 * 	set to the given value iMapping, else false
 */
bool cTypeDimension::setDimensionMapping( unsignedIntFib iDimensionNumber,
		unsignedIntFib iMapping ){
	
	if ( ( iDimensionNumber<1 ) || 
			( getNumberOfDimensions()<iDimensionNumber ) ){
		//no existing dimension, so not setable
		return false;
	}
	//check if the to set mapping dosen't exists for an other dimension
	for ( unsignedIntFib actualDimension=1; 
			actualDimension<=dimensionMapping.size(); actualDimension++ ){
			
		if ( actualDimension==iDimensionNumber ){
			if ( dimensionMapping[actualDimension-1]==iMapping ){
				//the dimension to set has the correct value
				return true;
			}//else
			//skip to change dimension
			continue;
		}
		
		if ( dimensionMapping[actualDimension-1]==0 ){
			//skip dimension with mapping 0 for none
			continue;
		}
		
		if ( dimensionMapping[actualDimension-1]==iMapping ){
			// the to set mapping is used for an other dimension
			return false;
		}
		
	}

	dimensionMapping[iDimensionNumber-1]=iMapping;
	
	return true;
}


/**
 * This method returns a name for the dimensionmapping with the given
 * number.
 *
 * @see getNumberForDimensionMappingName()
 * @param iMapping the mapping for which a string/name is to be returned
 * @return a string for the mapping with the number iMapping if known,
 * 	else an empty string
 */
string cTypeDimension::getDimensionMappingName( unsignedIntFib iMapping ) const{

	
	switch ( iMapping ){
		case DIRECTION_NONE    : return "none";
		case DIRECTION_HORIZONTAL: return "horizontal";
		case DIRECTION_VERTICAL: return "vertical";
		case DIRECTION_DEPTH   : return "depth";
		case DIRECTION_TIME    : return "time";
		case DIRECTION_ANYWHERE: return "anywhere";
		
		default:{
			unsigned int uiMapping = iMapping;
			char szDirectionBuffer[ 32 ];
			sprintf( szDirectionBuffer, "%u", uiMapping );
			return string( szDirectionBuffer );
		}
	};

	return "";
}


/**
 * This method returns the number for the given name of the dimensionmapping.
 *
 * @see getDimensionMappingName()
 * @param szMappingName the mappingname for which the number is to be returned
 * @return the number for the szMappingName or 0 if non such exists
 */
unsignedIntFib cTypeDimension::getNumberForDimensionMappingName( string szMappingName ) const{

	if ( szMappingName == "none" ){
		return DIRECTION_NONE;
	}else if ( szMappingName == "horizontal" ){
		return DIRECTION_HORIZONTAL;
	}else if ( szMappingName == "vertical" ){
		return DIRECTION_VERTICAL;
	}else if ( szMappingName == "depth" ){
		return DIRECTION_DEPTH;
	}else if ( szMappingName == "time" ){
		return DIRECTION_TIME;
	}else if ( szMappingName == "anywhere" ){
		return DIRECTION_ANYWHERE;
	}
//TODO for more typs

	long lValue = 0;
	const int iReadValues = sscanf ( szMappingName.c_str() , "%ld", & lValue );
	if ( iReadValues != 1){
		return 0;
	}
	return (unsignedIntFib)lValue;
}


/**
 * @return a vectro with the SI unit for the dimensions this type represents;
 * 	possible values are:
 * 		- "": for 0 none
 * 		- "m": for 1 horizontal, 2 vertical or 3 depth direction
 * 		- "s": for 4 time
 */
vector<string> cTypeDimension::getUnit() const{
	
	vector<string> vecDimensionUnits;
	
	for ( unsignedIntFib actualDimension=0; 
			actualDimension<dimensionMapping.size(); actualDimension++ ){
			
		switch ( dimensionMapping[ actualDimension ] ){
			case DIRECTION_HORIZONTAL:
			case DIRECTION_VERTICAL:
			case DIRECTION_DEPTH:
				vecDimensionUnits.push_back( "m" );
			break;
			case DIRECTION_TIME:
				vecDimensionUnits.push_back( "s" );
			break;
			default:
				vecDimensionUnits.push_back( "" );
		};
	}

	return vecDimensionUnits;
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
bool cTypeDimension::equalElementType( const cTypeElement & typeElement ) const{
	//all dimension types are vor the same typeelement
	return ( getType() == typeElement.getType() );
}

/**
 * This Method checks if the given type is equal to this type.
 *
 * @return true if the given type is equal to this type, else false
 */
bool cTypeDimension::operator==( const cTypeElement &typeElement ) const{
	 
	if ( getType() == typeElement.getType() ){
		//is the dimension type for the same dimension
		return (dimensionMapping ==
			((cTypeDimension*)&typeElement)->dimensionMapping);
	
	}//else

	 return false;
}

/**
 * This Method clones this object.
 *
 * @return a clone of this object
 */
cTypeDimension * cTypeDimension::clone() const{
	return new cTypeDimension( *this );
}


/**
 * This method evaluades the size of the typeelement in bits in the
 * compressed file form.
 *
 * @see store()
 * @return the size of the typeelement in bits in the compressed form
 */
unsignedLongFib cTypeDimension::getCompressedSize() const{
	
	unsignedLongFib ulCompressedSize = 8 + 16 + 16;
	
	//evalue the bits needed to store an dimension values
	unsigned int uiDigitsPerDimension = 0;
	
	for ( unsignedIntFib actualDimension = 0;
			actualDimension < dimensionMapping.size(); actualDimension++ ){
			
		uiDigitsPerDimension = max( uiDigitsPerDimension ,
			getDigits( dimensionMapping[ actualDimension ] ) );
	}
	
	ulCompressedSize += uiDigitsPerDimension * dimensionMapping.size();
	
	ulCompressedSize = roundUpToFullByte( ulCompressedSize );
	
	return ulCompressedSize;
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
bool cTypeDimension::storeXml( ostream & ostream,
		const cDomain * domain ) const{
	
	ostream<<"<dim count=\""<< getNumberOfDimensions() <<"\">"<<endl;
	
	//write the dimension mappings to the stream
	for ( unsignedIntFib uiActualDimension = 1;
			uiActualDimension <= getNumberOfDimensions(); uiActualDimension++ ){
		
		ostream<<"<dimension number=\""<< uiActualDimension <<"\" ";
		ostream<<"direction=\""<< getDimensionMappingName(
			getDimensionMapping( uiActualDimension ) ) <<"\"/>"<<endl;
	}
	//if given write the domain to the stream
	if ( domain != NULL ){

		bool bDomainStored = domain->storeXml( ostream );
		if ( ! bDomainStored ){
			return false;
		}
	}
	
	ostream<<"</dim>"<<endl;
	
	return true;
}


/**
 * This method restores a type with a domain in the XML -format from an
 * TinyXml element.
 *
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
 * @return a pointer to the restored domain, or NULL if it couldn't be restored
 */
cDomain * cTypeDimension::restoreXmlWithDomain( const TiXmlElement * pXmlElement,
		intFib & outStatus, const bool bRestoreDomain ){
	
	//check the element type
	if ( pXmlElement == NULL ){
		//Error: noting to restore
		outStatus = -1;
		return NULL;
	}
	string szElementType( pXmlElement->Value() );
	if ( szElementType != "dim" ){
		//Error: wrong element type to restore
		outStatus = -2;
		return NULL;
	}
	dimensionMapping.clear();
	
	int iCountOfDimensions = 0;
	const char * szXmlCountValue = pXmlElement->Attribute( "count", & iCountOfDimensions );
	if ( ( szXmlCountValue == NULL ) && bRestoreDomain ){
		//Warning: count of dimensions missing
		outStatus = 2;
	}
	//restore dimensionmapping
	const TiXmlElement * pXmlElementMapping = NULL;
	if ( pXmlElement->FirstChild() ){
		
		pXmlElementMapping = pXmlElement->FirstChildElement();
	}
	const TiXmlElement * pXmlElementDomain = NULL;
	int iActualDimension = 1;
	for( iActualDimension = 1; pXmlElementMapping != NULL;
			pXmlElementMapping = pXmlElementMapping->NextSiblingElement() ){
		
		string szElementType( pXmlElementMapping->Value() );

		if ( szElementType == "dimension" ){
			int iNumberOfDimension = 0;
			const char * szXmlDimNumber = pXmlElementMapping->Attribute( "number", & iNumberOfDimension );
			const char * szXmlDimDirection = pXmlElementMapping->Attribute( "direction" );
			
			if ( (szXmlDimNumber == NULL) || (iNumberOfDimension != iActualDimension) ){
				//Warning: no correct dimension Number
				outStatus = 2;
			}
			if ( szXmlDimDirection == NULL ){
				//Warning: no correct direction
				outStatus = 2;
			}else{
				dimensionMapping.push_back( getNumberForDimensionMappingName(
					string( szXmlDimDirection ) ) );
				iActualDimension++;
			}
		}else{
			if ( pXmlElementDomain == NULL ){
				pXmlElementDomain = pXmlElementMapping;
			}else{//Warning: more than one domain to restore
				outStatus = 2;
			}
		}
	}
	if ( iActualDimension <= iCountOfDimensions ){
		//Warning: dimensions missing
		outStatus = 2;
	}
	if ( bRestoreDomain ){
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
bool cTypeDimension::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	if ( uiRestBitPosition >= 8){
		//error in input
		return false;
	}

	char cDimensionName = 0x0E; //the name "dim" + variable parameter length

	//evalue the bits needed to store an dimension values
	unsigned int uiDigitsPerDimension = 0;
	
	for ( unsignedIntFib actualDimension = 0;
			actualDimension < dimensionMapping.size(); actualDimension++ ){
			
		uiDigitsPerDimension = max( uiDigitsPerDimension ,
			getDigits( dimensionMapping[ actualDimension ] ) );
	}
	
	unsigned long ulParameterSizeBits = 16 + uiDigitsPerDimension *
		dimensionMapping.size();
	
	ulParameterSizeBits = roundUpToFullByte( ulParameterSizeBits );
	
	/*reevalue the digits per dimension to get a upper bound of bits for it
	(e.g. if ther are 2 dimensions with 2 Bit each, 2 digits per dimensions
	would be wrong, because 8 bit (1 byte) for the dimensions is minimum
	but thats 4 Bits per dimension for 2 dimensions)*/
	if ( dimensionMapping.size() != 0 ){
		uiDigitsPerDimension = ( ulParameterSizeBits - 16 ) / dimensionMapping.size();
	}

	unsigned long ulParameterSize = ulParameterSizeBits / 8;//parametersize in byte	
	
	//write the name
	bool bNameStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
		&cDimensionName, 8 );
	if ( ! bNameStored ){
		return false;
	}

	//write the 16 bit parameterfild size in Byte
	bool bParameterLengthStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, ulParameterSize, 16 );
	if ( ! bParameterLengthStored ){
		return false;
	}

	//write the count of dimensions
	unsigned long ulCountOfDimensions = dimensionMapping.size();
	bool bDimensionCountStored = nBitStream::store( stream, cRestBits,
		uiRestBitPosition, ulCountOfDimensions, 16 );
	if ( ! bDimensionCountStored ){
		return false;
	}

	//write the numbers for the dimensions
	for ( unsignedIntFib uiActualDimension = 1;
			uiActualDimension <= getNumberOfDimensions(); uiActualDimension++ ){
		
		unsigned long ulActualDimensionMapping =
			getDimensionMapping( uiActualDimension );
		bool bDimensionMappingStored = nBitStream::store( stream, cRestBits,
			uiRestBitPosition, ulActualDimensionMapping, uiDigitsPerDimension );
		if ( ! bDimensionMappingStored ){
			return false;
		}
	}
	//fill the parameterbits up with 0 to an full byte
	unsigned long ulFillBits = ulParameterSizeBits -
		( 16 + uiDigitsPerDimension * dimensionMapping.size() );
	if ( ulFillBits > 0 ){
		char cFiller = 0x00;
		bool bFillerStored = nBitStream::store( stream, cRestBits,
			uiRestBitPosition, &cFiller, ulFillBits );
		if ( ! bFillerStored ){
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
intFib cTypeDimension::restore( cReadBits & iBitStream ){
	
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
	//the name "dim" + variable parameter length
	if ( (cTypeName & 0xFF) != 0x0E ){
		//warning: wrong type
		return -2;
	}
	
	//read the parameterlist size
	unsignedLongFib ulParameterlistSize = 0;
	uiBitsRead = iBitStream.readBits( ulParameterlistSize, 16 );
	if ( ! iBitStream.getStream()->good() ){
		return -2;
	}
	if ( uiBitsRead != 16 ){
		return -2;
	}
	//parametersize in bit
	ulParameterlistSize *= 8;
	if ( ulParameterlistSize < 16 ){
		//Warning: no dimensionmappings
		return 2;
	}
	
	//read count of dimensions
	unsignedLongFib ulCountOfDimensions = 0;
	uiBitsRead = iBitStream.readBits( ulCountOfDimensions, 16 );
	if ( ! iBitStream.getStream()->good() ){
		return -2;
	}
	if ( uiBitsRead != 16 ){
		return -2;
	}
	
	const unsigned int uiBitsPerDimension =
		(ulParameterlistSize - 16) / ulCountOfDimensions;
	
	dimensionMapping.clear();
	
	for ( unsignedIntFib uiActualDimension = 1;
			uiActualDimension <= ulCountOfDimensions; uiActualDimension++ ){
		
		unsignedLongFib ulDimensionMapping = 0;
		uiBitsRead = iBitStream.readBits( ulDimensionMapping, uiBitsPerDimension );
		if ( ! iBitStream.getStream()->good() ){
			return -2;
		}
		if ( uiBitsRead != uiBitsPerDimension ){
			return -2;
		}

		dimensionMapping.push_back( ulDimensionMapping );
	}
	//read the remaining filler bits
	unsignedLongFib ulNumberOfFillerBits = ulParameterlistSize - ( 16 +
		((ulParameterlistSize - 16) / ulCountOfDimensions) * ulCountOfDimensions);
	char cBuffer[ ulNumberOfFillerBits / 8 + 2 ];
	
	uiBitsRead = iBitStream.readBits( cBuffer, ulNumberOfFillerBits );
	if ( ! iBitStream.getStream()->good() ){
		return -2;
	}
	if ( uiBitsRead != ulNumberOfFillerBits ){
		return -2;
	}
	
	return 0;
}














