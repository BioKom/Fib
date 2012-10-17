/**
 * @class cTypeDimension
 * file name: cTypeDimension.h
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
12.02.2012  Oesterholz  restoreXml*() without restoring domain possible
27.02.2012  Oesterholz  DIRECTION_ANYWHERE added
*/

#ifndef ___C_TYPE_DIMENSION_H__
#define ___C_TYPE_DIMENSION_H__


#include "version.h"
#include "fibDatatyps.h"
#include "cTypeElement.h"

#include "vector"

using std::vector;


namespace fib{


class cTypeDimension: public cTypeElement{
private:

	/**
	 * the vector with the mappings for the dimensions
	 */
	vector<unsignedIntFib> dimensionMapping;


public:

	/**
	 * constants for the directions/mappings of the dimension
	 */
	static const unsignedIntFib DIRECTION_NONE      = 0;
	static const unsignedIntFib DIRECTION_HORIZONTAL= 1;
	static const unsignedIntFib DIRECTION_VERTICAL  = 2;
	static const unsignedIntFib DIRECTION_DEPTH     = 3;
	static const unsignedIntFib DIRECTION_TIME      = 4;

	static const unsignedIntFib DIRECTION_ANYWHERE  = 16;

	
	/**
	 * The constructor for dimension typs.
	 *
	 * @param iNumberOfDimensions the Number of dimensions the
	 * 	positionvetordomain has
	 */
	cTypeDimension( unsignedIntFib iNumberOfDimensions=2  );
	
	/**
	 * The constructor for dimension typs.
	 * Duplicte mapping will be set to 0.
	 *
	 * @param dimensionMapping the mappings for the dimensions
	 */
	cTypeDimension( vector<unsignedIntFib> dimensionMapping  );

	/**
	 * The copyconstructor for dimension typs.
	 *
	 * @param typeDimension the type dimension to copy
	 */
	cTypeDimension( const cTypeDimension &typeDimension );


	/**
	 * This Function returns for the type of the element an number.
	 * The values, which are returned, mean:
	 * 	- 1:  cTypeDimension
	 * 	- 2:  cTypeUnderArea
	 * 	- 3:  cTypeUnderFunction
	 * 	- 5:  cTypeInVar
	 * 	- 6:  cTypeProperty
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
	virtual unsignedIntFib getType() const;

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
	virtual cDomain *getStandardDomain( ) const;

	/**
	 * This method checks, if this element type is compatible with the
	 * given domain. Just domains which are compadible can be used for the
	 * elements of this type.
	 *
	 * @param domain the domain, which should be compatible
	 * @return true if the given domain is compatible, else false
	 */
	virtual bool isCompatible( const cDomain &domain ) const;


	/**
	 * @return the number of dimensions of the Fib -object
	 */
	unsignedIntFib getNumberOfDimensions() const;


	/**
	 * This method returns in which direction the iDimensionNumber dimension
	 * is mapped.
	 *
	 * @param iDimensionNumber the number of the dimension for which the
	 * 	mapping is to be returned
	 * @return the direction in which the iDimensionNumber dimension is
	 * 	mapped
	 */
	unsignedIntFib getDimensionMapping( unsignedIntFib iDimensionNumber ) const;


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
	bool setDimensionMapping( unsignedIntFib iDimensionNumber,
		unsignedIntFib iMapping );

	/**
	 * This method returns a name for the dimensionmapping with the given
	 * number.
	 *
	 * @see getNumberForDimensionMappingName()
	 * @param iMapping the mapping for which a string/name is to be returned
	 * @return a string for the mapping with the number iMapping if known,
	 * 	else an empty string
	 */
	string getDimensionMappingName( unsignedIntFib iMapping ) const;

	/**
	 * This method returns the number for the given name of the dimensionmapping.
	 *
	 * @see getDimensionMappingName()
	 * @param szMappingName the mappingname for which the number is to be returned
	 * @return the number for the szMappingName or 0 if non such exists
	 */
	unsignedIntFib getNumberForDimensionMappingName( string szMappingName ) const;

	/**
	 * @return The SI unit for the dimension this type represents;
	 * 	possible values are:
	 * 		- "": for direction 0 none
	 * 		- "m": for direction 1 horizontal, 2 vertical or 3 depth direction
	 * 		- "s": for direction 4 time
	 */
	virtual vector<string> getUnit() const;

	/**
	 * This Method checks if the elementtype of the given type is equal to
	 * the elementtype of this type.
	 * Two elementtype are not equal if ther are for different fib -elements.
	 *
	 * @param typeElement the typeelement to compare with this typeelement
	 * @return true if the elementtype of the given type is equal to the
	 * 	elementtype of this type, else false
	 */
	virtual bool equalElementType( const cTypeElement & typeElement ) const;

	/**
	 * This Method checks if the given type is equal to this type.
	 *
	 * @return true if the given type is equal to this type, else false
	 */
	virtual bool operator==( const cTypeElement &typeElement ) const;

	/**
	 * This Method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cTypeDimension *clone() const;

	/**
	 * This method evaluades the size of the typeelement in bits in the
	 * compressed file form.
	 *
	 * @see store()
	 * @return the size of the typeelement in bits in the compressed form
	 */
	virtual unsignedLongFib getCompressedSize() const;

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
	virtual bool storeXml( ostream & ostream,
		const cDomain * domain = NULL ) const;

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
	virtual cDomain * restoreXmlWithDomain( const TiXmlElement * pXmlElement,
		intFib & outStatus, const bool bRestoreDomain = true );

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
	virtual bool store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const;

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
	virtual intFib restore( cReadBits & iBitStream );


};//end class cTypeDimension


}//end namespace fib

#endif //___C_TYPE_DIMENSION_H__
