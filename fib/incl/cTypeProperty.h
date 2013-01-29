/**
 * @class cTypeProperty
 * file name: cTypeProperty.h
 * @author Betti Oesterholz
 * @date 18.07.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents Fib -propertytyps.
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
 * This file contains the basisclass of all Fib -propertytyps.
 * Fib -propertytyps are typs of the elements in an Fib 
 * -propertyvector.
 *
 */
/*
History:
18.07.2009  Oesterholz  created
10.12.2009  Oesterholz  getOverwritenTyps() and isEvalued() added
05.07.2010  Oesterholz  lowerTypeProperty() moved her from cEvaluePositionList
	and operator<() added
17.12.2010  Oesterholz  isOverwritenTyp() method added
18.12.2010  Oesterholz  isOverwriting() and static isEvalued() methods added
12.02.2012  Oesterholz  restoreXml*() without restoring domain possible
28.01.2013  Oesterholz  colorSW changed to colorGrascale
*/

#ifndef ___C_TYPE_PROPERTY_H__
#define ___C_TYPE_PROPERTY_H__


#include "version.h"
#include "fibDatatyps.h"
#include "cTypeElement.h"
#include "cDomain.h"

#include <vector>
#include <list>

using std::vector;

namespace fib{


class cTypeProperty: public cTypeElement{
private:

	/**
	 * the number of the dimension this type represents;
	 * 	possible values are:
	 * 		TODO
	 */
	unsignedIntFib uiPropertyType;
	
	/**
	 * The number of dimension this property type is for.
	 * Some properties like soundPolarized change ther domains for different
	 * number of dimensions. So they need to be known, when the information
	 * about the domain of thes properties are given.
	 */
	unsignedIntFib uiNumberOfDimensions;
	
public:

	/**
	 * constants for the property type
	 */
	static const unsignedIntFib NONE = 0;
	
	static const unsignedIntFib COLOR_RGB = 1;
	static const unsignedIntFib COLOR_GRAYSCALE = 2;
	static const unsignedIntFib LAYER     = 100;
	static const unsignedIntFib TRANSPARENCY    = 200;
	static const unsignedIntFib SOUND     = 300;
	static const unsignedIntFib SOUND_POLARIZED = 301;
	static const unsignedIntFib SOUND_AMPLITUDE = 305;
	static const unsignedIntFib SOUND_BARRIER   = 310;
	static const unsignedIntFib SOUND_REFLECTED = 311;
	static const unsignedIntFib SOUND_DAMPING   = 312;
	static const unsignedIntFib KELVIN    = 400;
	static const unsignedIntFib ELECTRO_MAGNETIC= 410;

	static const unsignedIntFib CHECKSUM  = 600;

	/**
	 * The constructor for dimension typs.
	 *
	 * @param iPropertyType the number of the property this type
	 *		represents;
	 * 	possible values are:
	 * 		TODO
	 * @param iPropertyType the number of dimension this property type is for;
	 * 	you don't have to give them if the number of dimensions is 
	 * 	irrelevant for the property type
	 */
	cTypeProperty( unsignedIntFib uiPropertyType,
		unsignedIntFib uiNumberOfDimensions=2 );

	/**
	 * The copyconstructor for property typs.
	 *
	 * @param typeProperty the type property to copy
	 */
	cTypeProperty( const cTypeProperty &typeProperty );

	/**
	 * The constructor for property typs.
	 * This constructor constructs a propertytype, which is of the same type
	 * as the given propertytype typeProperty, but which is adapted to the
	 * given domain if possible. For that the number of dimension is
	 * set to a value that is compatible to the vectordomain if possible.
	 * (If not possible number of dimension is set to the value as in
	 * typeProperty.)
	 *
	 * @param typeProperty the type property to copy
	 * @param domain the domain to which the propertytype is to be adapted
	 */
	cTypeProperty( const cTypeProperty &typeProperty,
			const cDomain & domain );


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
	 * This Method returns a pointer to a new instance of the standart
	 * domain for elements of this type.
	 * You have to delete the returned object after usage.
	 *
	 * @return the standart domain for elements of this type
	 */
	virtual cDomain *getStandardDomain() const;
	
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
	 * @return the type of property this type represents
	 */
	virtual unsignedIntFib getNumberOfProperty() const;

	/**
	 * @see getNumberForPropertyName()
	 * @return the name of property this type represents
	 */
	virtual string getNameOfProperty() const;

	/**
	 * @see getNameOfProperty()
	 * @param szPropertyName a name for a property
	 * @return the number the name szPropertyName represents
	 */
	static unsignedIntFib getNumberForPropertyName( const string szPropertyName );

	/**
	 * @return The SI unit for the dimension this type represents;
	 * 	possible values are:
	 * 		- "": for none
	 * 		- "m": for meter
	 * 		- "s": for secound
	 *			TODO
	 */
	virtual vector<string> getUnit() const;

	/**
	 * @return The typs of the properties the properties of this type overwrites
	 */
	virtual list<cTypeProperty> getOverwritenTyps() const;

	/**
	 * This method checks if the given type is overwritten by this type.
	 *
	 * @param typeToCheck the type to check, if it is overwritten
	 * @return true if typeToCheck is overwritten by this type, else false
	 */
	bool isOverwritenTyp( const cTypeProperty & typeToCheck ) const;
	
	/**
	 * This method checks if the given type is overwritten by this type.
	 *
	 * @see uiPropertyType
	 * @param uiTypeToCheck the number of the type to check, if it is overwritten
	 * @return true if uiTypeToCheck is overwritten by this type, else false
	 */
	bool isOverwritenTyp( const unsignedIntFib & uiTypeToCheck ) const;

	/**
	 * @return if this type overwrites typs true, else false
	 */
	bool isOverwriting() const;

	/**
	 * This function checks if the given type overwrites some typs.
	 *
	 * @param uiTypeToCheck the number of the type to check, if it overwrittes
	 * 	other typs
	 * @return if the given type overwrites typs true, else false
	 */
	static bool isOverwriting( const unsignedIntFib & uiTypeToCheck );

	/**
	 * @return this method returnes true, if the property of this type is
	 * 	for evaluating a fib -object, else false is returned 
	 */
	virtual bool isEvalued() const;

	/**
	 * This function checks if the given type is evalued.
	 *
	 * @param uiTypeToCheck the number of the type to check, if it is evalued
	 * @return this method returnes true, if the property of the given type is
	 * 	for evaluating a fib -object, else false is returned
	 */
	static bool isEvalued( const unsignedIntFib & uiTypeToCheck );
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
	virtual cTypeProperty *clone() const;

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

	/**
	 * This function compares this property type with the given property type.
	 * Propertytype is lower, if it's number is lower than the number of the 
	 * other Propertytype.
	 *
	 * @param typeProperty a pointer to the second propertytype to compare
	 * @return true if this propertytype is lower than that the given
	 * 	of typeProperty, else false
	 */
	virtual bool operator<( const cTypeProperty & typeProperty ) const;

	/**
	 * This function compares two cTypeProperty.
	 * Propertytype is lower, if it's number is lower than the number of the 
	 * other Propertytype.
	 *
	 * @param pTypeProperty1 a pointer to the first propertytype to compare
	 * @param pTypeProperty2 a pointer to the second propertytype to compare
	 * @return true if the propertytype pTypeProperty1 is lower than that
	 * 	of pTypeProperty2, else false
	 */
	static bool lowerTypeProperty( const cTypeProperty & pTypeProperty1,
		const cTypeProperty & pTypeProperty2 );
	
	/**
	 * This function compares two cTypeProperty.
	 * Propertytype is lower, if it's number is lower than the number of the 
	 * other Propertytype.
	 *
	 * @param pTypeProperty1 a pointer to the first propertytype to compare
	 * @param pTypeProperty2 a pointer to the second propertytype to compare
	 * @return true if the propertytype pTypeProperty1 is lower than that
	 * 	of pTypeProperty2, else false
	 */
	static bool lowerTypeProperty( const cTypeProperty * pTypeProperty1,
		const cTypeProperty * pTypeProperty2 );


};//end class cTypeProperty


}//end namespace fib

#endif //___C_TYPE_PROPERTY_H__
