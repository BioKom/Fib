/**
 * @file cImageAreaLinearColor
 * file name: cImageAreaLinearColor.cpp
 * @author Betti Oesterholz
 * @date 27.11.2012
 * @mail Oesterholz@Fib-development.org
 *
 * System: C++
 *
 * This file implements a class to store the data of a area in an image,
 * which has a linear color gradient.
 *
 *
 * Copyright (C) @c GPL3 2012 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (GPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 *
 * This file implements a class to store the data of a area in an image,
 * which as a linear color gradient (in both directions).
 * If you want to convert an image to Fib structures, you have to search
 * the image for structures, which can be converted to Fib.
 * If you have an area with a linear color gradient, you can use this class
 * to represent it.
 * For this three color vectors are stored for the color basis
 * (vecColorBasis) at the point (0,0) and the slope in the two image
 * dimensions / directions x (vecColorXSlope) and y (vecColorYSlope).
 * The colors of the points can then be evalued with:
 * 	vecColorBasis + x * vecColorXSlope + y * vecColorYSlope
 * Where x and y are the coordinate components for the first (x) and second
 * (y) dimension.
 */
/*
History:
27.11.2012  Oesterholz  created
*/


//switches for debugging proposes
//#define DEBUG


#include "cImageAreaLinearColor.h"

#include "cConvertFibDatabaseObject.h"

#include "cExtObject.h"
#include "cFibSet.h"
#include "cVectorFibSet.h"
#include "cPoint.h"
#include "cProperty.h"
#include "cList.h"
#include "cFunction.h"
#include "cFunctionValue.h"
#include "cFunctionVariable.h"
#include "cFunctionAdd.h"
#include "cFunctionMult.h"


using namespace fib::algorithms::nConvertToFib::nImage::nStructureData;
using namespace fib;


/**
 * standard constructor
 *
 * @param vecInColorBasis the color at the point (0,0)
 * @param vecInColorXSlope the color slope for the x / first dimension
 * @param vecInColorYSlope the color slope for the y / second dimension
 */
cImageAreaLinearColor::cImageAreaLinearColor( const cVectorProperty & vecInColorBasis,
		const cVectorProperty & vecInColorXSlope,
		const cVectorProperty & vecInColorYSlope ):
		vecColorBasis( vecInColorBasis ),
		vecColorXSlope( vecInColorXSlope ), vecColorYSlope( vecInColorYSlope ){
	//nothing to do
}


/**
 * copy constructor
 *
 * @param structureToCopy the image structure to copy
 */
cImageAreaLinearColor::cImageAreaLinearColor(
		const cImageAreaLinearColor & structureToCopy ):
		cImageStructure( structureToCopy ),
		vecColorBasis( structureToCopy.vecColorBasis ),
		vecColorXSlope( structureToCopy.vecColorXSlope ),
		vecColorYSlope( structureToCopy.vecColorYSlope ){
	//nothing to do
}


/**
 * The constructor for restoring a image structure from an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node the image structure is stored in
 * @param outStatus a reference to an integer value where the error value
 * 	can be stored to.
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 */
cImageAreaLinearColor::cImageAreaLinearColor( const TiXmlElement * pXmlElement,
		intFib & outStatus ):
		vecColorBasis( 0 ), vecColorXSlope( 0 ), vecColorYSlope( 0 ){
	
	outStatus = cImageAreaLinearColor::restoreXml( pXmlElement );
}


/**
 * destructor
 */
cImageAreaLinearColor::~cImageAreaLinearColor(){
	//nothing to do
}


/**
 * @return the name of the image structure (class name without the leading 'c')
 */
string cImageAreaLinearColor::getName() const{
	
	return "ImageAreaLinearColor";
}


/**
 * @see vecColorBasis
 * @see setColorBasisOfArea()
 * @return the color at the point (0,0)
 */
cVectorProperty cImageAreaLinearColor::getColorBasisOfArea() const{
	
	return vecColorBasis;
}


/**
 * @see vecColorBasis
 * @see setColorBasisOfArea()
 * @return the color at the point (0,0)
 */
const cVectorProperty & cImageAreaLinearColor::getColorBasisOfAreaConst() const{
	
	return vecColorBasis;
}


/**
 * This method sets the color at the point (0,0) to the given color.
 *
 * @see vecColorBasis
 * @see getColorBasisOfArea()
 * @param vecInColor the color at the point (0,0) to set
 */
void cImageAreaLinearColor::setColorBasisOfArea( const cVectorProperty & vecInColor ){
	
	vecColorBasis = vecInColor;
}


/**
 * @see vecColorXSlope
 * @see setColorXSlopeOfArea()
 * @return the color slope for the x / first dimension
 */
cVectorProperty cImageAreaLinearColor::getColorXSlopeOfArea() const{
	
	return vecColorXSlope;
}


/**
 * @see vecColorXSlope
 * @see setColorXSlopeOfArea()
 * @return the color slope for the x / first dimension
 */
const cVectorProperty & cImageAreaLinearColor::getColorXSlopeOfAreaConst() const{
	
	return vecColorXSlope;
}


/**
 * This method sets the color slope for the x / first dimension for the
 * area to the given color.
 *
 * @see vecColorXSlope
 * @see getColorXSlopeOfArea()
 * @param vecInColor the color slope for the x / first dimension to set
 */
void cImageAreaLinearColor::setColorXSlopeOfArea(const cVectorProperty & vecInColor ){
	
	vecColorXSlope = vecInColor;
}


/**
 * @see vecColorYSlope
 * @see setColorYSlopeOfArea()
 * @return the color slope for the y / second dimension
 */
cVectorProperty cImageAreaLinearColor::getColorYSlopeOfArea() const{
	
	return vecColorYSlope;
}


/**
 * @see vecColorYSlope
 * @see setColorYSlopeOfArea()
 * @return the color slope for the y / second dimension
 */
const cVectorProperty & cImageAreaLinearColor::getColorYSlopeOfAreaConst() const{
	
	return vecColorYSlope;
}


/**
 * This method sets the color slope for the y / second dimension for the
 * area to the given color.
 *
 * @see vecColorYSlope
 * @see getColorYSlopeOfArea()
 * @param vecInColor the color slope for the y / second dimension to set
 */
void cImageAreaLinearColor::setColorYSlopeOfArea( const cVectorProperty & vecInColor ){
	
	vecColorYSlope = vecInColor;
}



/**
 * This method evalues and returns the color at the given point (x,y):
 * 	vecColorBasis + x * vecColorXSlope + y * vecColorYSlope
 *
 * @see vecColorBasis
 * @see getColorBasisOfArea()
 * @see setColorBasisOfArea()
 * @param x the x / first dimension coordinate of the point
 * @param y the y / second dimension coordinate of the point
 * @return the color at the given point (x,y)
 */
cVectorProperty cImageAreaLinearColor::getColorOfPoint(
		const double x, const double y  ) const{
	
	const unsignedIntFib uiNumberOfElements =
		vecColorBasis.getNumberOfElements();
	
	cVectorProperty vecResult( vecColorBasis.getPropertyType(), uiNumberOfElements );
	
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= uiNumberOfElements; uiActualElement++ ){
		
		vecResult.setValue( uiActualElement,
			vecColorBasis.getValue( uiActualElement ) +
			x * vecColorXSlope.getValue( uiActualElement ) +
			y * vecColorYSlope.getValue( uiActualElement ) );
	}
	
	return vecResult;
}



/**
 * This method clones this object.
 *
 * @return a clone of this object
 */
cImageAreaLinearColor * cImageAreaLinearColor::cImageAreaLinearColor::clone() const{
	
	return new cImageAreaLinearColor( *this );
}


/**
 * This method returns the number of properties for the image structure
 * point.
 *
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return value 0), else
 * 	it works as if the given point was included in this image structure
 * @param vecPoint the point for which to return the number of
 * 	properties
 * @return the number of property vectors for the given position
 */
unsigned int cImageAreaLinearColor::getNumberOfProperties( const bool bEvenIfOutside,
		const cVectorPosition vecPoint ) const{
	
	if ( bEvenIfOutside || isStructurePoint( vecPoint ) ){
		return 1;
	}//else
	return 0;
}


/**
 * This method returns the number of properties for the image structure
 * point.
 *
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return value 0), else
 * 	it works as if the given point was included in this image structure
 * @param point the point for which to return the number of
 * 	properties
 * @return the number of property vectors for the given position
 */
unsigned int cImageAreaLinearColor::getNumberOfProperties( const bool bEvenIfOutside,
		const pair< unsigned int, unsigned int> point ) const{
	
	if ( bEvenIfOutside || isStructurePoint( point ) ){
		return 1;
	}//else
	return 0;
}


/**
 * This method returns the number of the uiPropertyNumber'th property
 * type for the image structure point.
 * @see cTypeProperty
 * @see getPropertyNumberForType()
 *
 * @param uiPropertyNumber the number of the property to return the type of;
 * 	counting starts with 1; @see getNumberOfProperties()
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return value 0), else
 * 	it works as if the given point was included in this image structure
 * @param vecPoint the point for which to return the number of
 * 	the type of the property
 * @return the number of the type of the uiPropertyNumber'th property
 * 	on the given position, or 0 (cTypeProperty::NONE) if non exists
 * 	@see cTypeProperty
 */
unsigned int cImageAreaLinearColor::getPropertyType( const unsigned int uiPropertyNumber,
		const bool bEvenIfOutside, const cVectorPosition vecPoint ) const{
	
	if ( ( uiPropertyNumber == 1 ) &&
			( bEvenIfOutside || isStructurePoint( vecPoint ) ) ){
		return vecColorBasis.getPropertyType();
	}//else
	return cTypeProperty::NONE;
}


/**
 * This method returns the number of the uiPropertyNumber'th property
 * type for the image structure point.
 * @see cTypeProperty
 * @see getPropertyNumberForType()
 *
 * @param uiPropertyNumber the number of the property to return the type of;
 * 	counting starts with 1; @see getNumberOfProperties()
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return value 0), else
 * 	it works as if the given point was included in this image structure
 * @param point the point for which to return the number of
 * 	the type of the property
 * @return the number of the type of the uiPropertyNumber'th property
 * 	on the given position, or 0 (cTypeProperty::NONE) if non exists
 * 	@see cTypeProperty
 */
unsigned int cImageAreaLinearColor::getPropertyType( const unsigned int uiPropertyNumber,
		const bool bEvenIfOutside, const pair< unsigned int, unsigned int> point ) const{
	
	if ( ( uiPropertyNumber == 1 ) &&
			( bEvenIfOutside || isStructurePoint( point ) ) ){
		return vecColorBasis.getPropertyType();
	}//else
	return cTypeProperty::NONE;
}


/**
 * This method returns the property number for the given property type
 * for the image position.
 * @see cTypeProperty
 * @see getPropertyType()
 * @see getNumberOfProperties()
 *
 * @param uiPropertyType the type number of the property to return the
 * 	number of (e. g. cTypeProperty::COLOR_RGB )
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return value 0), else
 * 	it works as if the given point was included in this image structure
 * @param vecPoint the point for which to return the number of
 * 	the property of the given type
 * @return the number for the given property type for the image position,
 * 	or 0 if no such property extists
 * 	@see cTypeProperty
 */
unsigned int cImageAreaLinearColor::getPropertyNumberForType(
		const unsigned int uiPropertyType, const bool bEvenIfOutside,
		const cVectorPosition vecPoint ) const{
	
	if ( bEvenIfOutside || isStructurePoint( vecPoint ) ){
		return (( vecColorBasis.getPropertyType() == uiPropertyType )? 1 : 0);
	}//else
	return 0;
}


/**
 * This method returns the property number for the given property type
 * for the image position.
 * @see cTypeProperty
 * @see getPropertyType()
 * @see getNumberOfProperties()
 *
 * @param uiPropertyType the type number of the property to return the
 * 	number of (e. g. cTypeProperty::COLOR_RGB )
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return value 0), else
 * 	it works as if the given point was included in this image structure
 * @param point the point for which to return the number of
 * 	the property of the given type
 * @return the number for the given property type for the image position,
 * 	or 0 if no such property extists
 * 	@see cTypeProperty
 */
unsigned int cImageAreaLinearColor::getPropertyNumberForType( const unsigned int uiPropertyType,
		const bool bEvenIfOutside, const pair< unsigned int, unsigned int> point ) const{
	
	if ( bEvenIfOutside || isStructurePoint( point ) ){
		return ( vecColorBasis.getPropertyType() == uiPropertyType )? 1 : 0;
	}//else
	return 0;
}


/**
 * With this method the properties for given point are returned.
 * (Antialising will be ignored. @see bIsAntialised )
 *
 * @param vecPoint the point, for which the properties should be returned
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return empty list), else
 * 	it works as if the given point was included in this image structure
 * @return a list of the properties of the point
 */
list<cVectorProperty> cImageAreaLinearColor::getPointProperties(
		const cVectorPosition & vecPoint, const bool bEvenIfOutside ) const{
	
	if ( bEvenIfOutside || isStructurePoint( vecPoint ) ){
		return list<cVectorProperty>( 1,
			getPropertyForNumber( vecPoint, 1, true ) );
	}//else
	return list<cVectorProperty>();
}


/**
 * With this method the properties for given point are returned.
 * (Antialising will be ignored. @see bIsAntialised )
 *
 * @param point the point, for which the properties should be
 * 	returned
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return empty list), else
 * 	it works as if the given point was included in this image structure
 * @return a list of the properties of the point
 */
list<cVectorProperty> cImageAreaLinearColor::getPointProperties(
		const pair< unsigned int, unsigned int> & point,
		const bool bEvenIfOutside ) const{
	
	if ( bEvenIfOutside || isStructurePoint( point ) ){
		return list<cVectorProperty>( 1,
			getPropertyForNumber( convertToVectorPosition( point ), 1, true ) );
	}//else
	return list<cVectorProperty>();
}


/**
 * This method returns the property of the given type for the given image
 * structure point.
 * (Antialising will be ignored. @see bIsAntialised )
 *
 * @param vecPoint the point of which to return the property vector
 * @param uiPropertyType the type number of the property to return
 * 	(e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return cTypeProperty::NONE),
 * 	 else it works as if the given point was included in this image structure
 * @return the property for the given type uiPropertyType for the given
 * 	point or the property of type cTypeProperty::NONE if non exists
 */
cVectorProperty cImageAreaLinearColor::getProperty( const cVectorPosition & vecPoint,
		const unsigned int uiPropertyType, const bool bEvenIfOutside ) const{
	
	if ( bEvenIfOutside || isStructurePoint( vecPoint ) ){
		if ( vecColorBasis.getPropertyType() == uiPropertyType ){
			return getPropertyForNumber( vecPoint, 1, true );
		}
	}//else
	return cVectorProperty( cTypeProperty::NONE );
}


/**
 * This method returns the property of the given type for the given image
 * structure point.
 * (Antialising will be ignored. @see bIsAntialised )
 *
 * @param point the point of which to return the property vector
 * @param uiPropertyType the type number of the property to return
 * 	(e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return cTypeProperty::NONE),
 * 	 else it works as if the given point was included in this image structure
 * @return the property for the given type uiPropertyType for the given
 * 	point or the property of type cTypeProperty::NONE if non exists
 */
cVectorProperty cImageAreaLinearColor::getProperty(
		const pair< unsigned int, unsigned int> & point,
		const unsigned int uiPropertyType, const bool bEvenIfOutside ) const{
	
	if ( bEvenIfOutside || isStructurePoint( point ) ){
		if ( vecColorBasis.getPropertyType() == uiPropertyType ){
			return getPropertyForNumber( convertToVectorPosition( point ), 1, true );
		}
	}//else
	return cVectorProperty( cTypeProperty::NONE );
}


/**
 * This method returns the uiPropertyNumber'th property for the given image
 * structure point.
 * (Antialising will be ignored. @see bIsAntialised )
 *
 * @param vecPoint the point of which to return the property vector
 * @param uiPropertyNumber the number of the property to return;
 * 	counting starts with 1; @see getNumberOfProperties()
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return cTypeProperty::NONE),
 * 	 else it works as if the given point was included in this image structure
 * @return the uiPropertyNumber'th property from the given position or the
 * 	property of type cTypeProperty::NONE if non exists
 */
cVectorProperty cImageAreaLinearColor::getPropertyForNumber(
		const cVectorPosition & vecPoint,
		const unsigned int uiPropertyNumber, const bool bEvenIfOutside ) const{
	
	if ( bEvenIfOutside || isStructurePoint( vecPoint ) ){
		if ( uiPropertyNumber == 1 ){
			//evalue property
			cVectorProperty vecEvaluedProperty( vecColorBasis );
			const unsigned int uiNumberOfElements =
				vecColorBasis.getNumberOfElements();
			const doubleFib dValueX = vecPoint.getValue( 1 );
			const doubleFib dValueY = vecPoint.getValue( 2 );
			for ( unsigned int uiActualElement = 1;
					uiActualElement <= uiNumberOfElements; uiActualElement++ ){
				//for every property element
				vecEvaluedProperty.setValue( uiActualElement,
					vecColorBasis.getValue( uiActualElement ) +
					dValueX * vecColorXSlope.getValue( uiActualElement ) +
					dValueY * vecColorYSlope.getValue( uiActualElement ) );
			}
			return vecEvaluedProperty;
		}
	}//else
	return cVectorProperty( cTypeProperty::NONE );
}


/**
 * This method returns the uiPropertyNumber'th property for the given image
 * structure point.
 * (Antialising will be ignored. @see bIsAntialised )
 *
 * @param point the point of which to return the property vector
 * @param uiPropertyNumber the number of the property to return;
 * 	counting starts with 1; @see getNumberOfProperties()
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return cTypeProperty::NONE),
 * 	 else it works as if the given point was included in this image structure
 * @return the uiPropertyNumber'th property from the given position or the
 * 	property of type cTypeProperty::NONE if non exists
 */
cVectorProperty cImageAreaLinearColor::getPropertyForNumber(
		const pair< unsigned int, unsigned int> & point,
		const unsigned int uiPropertyNumber, const bool bEvenIfOutside ) const{
	
	if ( bEvenIfOutside || isStructurePoint( point ) ){
		if ( uiPropertyNumber == 1 ){
			return getPropertyForNumber( convertToVectorPosition( point ), 1, true );
		}
	}//else
	return cVectorProperty( cTypeProperty::NONE );
}


/**
 * This method checks if the given image structure is equal to this image structure.
 *
 * @param imageStructure the image structure which should be equal to this image structure
 * @return true if the given image structure is equal to this image structure, else false
 */
bool cImageAreaLinearColor::equal( const cImageStructure &imageStructure ) const{
	
	//check if the image structure and class type is correct
	if ( ! cImageStructure::equal( imageStructure ) ){
		//the image structure or class type is not equal -> not equal
		return false;
	}
	const cImageAreaLinearColor * pImageAreaLinearColor =
		((cImageAreaLinearColor*)(& imageStructure));
	
	if ( vecColorBasis.equal(
			pImageAreaLinearColor->getColorBasisOfAreaConst() ) ){
		//basis color vector not equal -> structure not equal
		return false;
	}
	if ( vecColorXSlope.equal(
			pImageAreaLinearColor->getColorXSlopeOfAreaConst() ) ){
		//x slope color vector not equal -> structure not equal
		return false;
	}
	if ( vecColorYSlope.equal(
			pImageAreaLinearColor->getColorYSlopeOfAreaConst() ) ){
		//y slope color vector not equal -> structure not equal
		return false;
	}
	//image structures equal
	return true;
}


/**
 * This method stores this image structure in the XML format into the
 * given stream.
 *
 * @param ostream the stream where image structure should be stored to
 * @return true if this image structure was stored, else false
 */
bool cImageAreaLinearColor::storeXml( ostream & ostream ) const{
	
	ostream<<"<imageAreaLinearColor>"<<endl;
	
	if ( ! vecColorBasis.storeXml( ostream ) ){
		//error while storing
		return false;
	}
	if ( ! vecColorXSlope.storeXml( ostream ) ){
		//error while storing
		return false;
	}
	if ( ! vecColorYSlope.storeXml( ostream ) ){
		//error while storing
		return false;
	}
	if ( ! cImageStructure::storeXml( ostream ) ){
		return false;
	}
	
	ostream<<"</imageAreaLinearColor>"<<endl;
	
	return true;
}



/**
 * This method restores a image structure in the XML format from a
 * TinyXml element.
 *
 * @param pXmlElement a pointer to the TinyXml node wher the image
 * 	structure is stored in
 * @return an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 */
intFib cImageAreaLinearColor::restoreXml( const TiXmlElement * pXmlElement ){
	
	intFib iReturn = 0;
	
	if ( pXmlElement == NULL ){
		//nothing to restore
		return -1;
	}
	const string szElementType( pXmlElement->Value() );
	if ( szElementType != "imageAreaLinearColor" ){
		//wrong element type to restore
		return -2;
	}
	
	//no variables defined
	list<cFibVariable*> liDefinedVariables;
	
	bool bBasisColorVectorRestored  = false;
	bool bColorXSlopeVectorRestored = false;
	bool bColorYSlopeVectorRestored = false;
	bool bImageStructureDataRestored= false;
	
	for ( const TiXmlNode * pChild = pXmlElement->FirstChild();
			pChild != NULL; pChild = pChild->NextSibling() ){
		
		const int iType = pChild->Type();
		
		switch ( iType ){
			case TiXmlNode::ELEMENT:{
				//load the members
				const TiXmlElement * pXmlElement = pChild->ToElement();
				if ( pXmlElement == NULL ){
					if ( iReturn == 0 ){
						iReturn = 2;
					}
					continue;
				}
				const string szElementType( pXmlElement->Value() );
				
				if ( szElementType == "vector" ){
					//element for color vector
					//check the attribute of the vector
					const char * szVectorXmlType = pXmlElement->Attribute( "type" );
					
					if ( szVectorXmlType == NULL ){
						if ( iReturn == 0 ){
							iReturn = 1;
						}
						continue;
					}//else
					if ( strncmp( "property.", szVectorXmlType, 9 ) != 0 ){
						if ( iReturn == 0 ){
							iReturn = 1;
						}
						continue;
					}
					//error value to return
					intFib outStatus = 0;
					if ( ! bBasisColorVectorRestored ){
						//restore the basis color vector
						//restore the vector
						vecColorBasis = cVectorProperty( pXmlElement, outStatus,
							liDefinedVariables );
						bBasisColorVectorRestored = true;
						if ( outStatus < 0 ){
							return outStatus;
						}
						if ( ( iReturn < outStatus ) && ( 0 <= iReturn ) ){
							iReturn = outStatus;
						}
					}else if ( ! bColorXSlopeVectorRestored ){
						//restore the x slope color vector
						//restore the vector
						vecColorXSlope = cVectorProperty( pXmlElement, outStatus,
							liDefinedVariables );
						bColorXSlopeVectorRestored = true;
						if ( outStatus < 0 ){
							return outStatus;
						}
						if ( ( iReturn < outStatus ) && ( 0 <= iReturn ) ){
							iReturn = outStatus;
						}
					}else if ( ! bColorYSlopeVectorRestored ){
						//restore the y slope color vector
						//restore the vector
						vecColorYSlope = cVectorProperty( pXmlElement, outStatus,
							liDefinedVariables );
						bColorYSlopeVectorRestored = true;
						if ( outStatus < 0 ){
							return outStatus;
						}
						if ( ( iReturn < outStatus ) && ( 0 <= iReturn ) ){
							iReturn = outStatus;
						}
					}else{//to much color vectors to restore
						if ( iReturn == 0 ){
							iReturn = 1;
						}
					}
				}else if ( szElementType == "imageStructure" ){
					//restore image structure data element
					if ( ! bImageStructureDataRestored ){
						//restore the image structure data
						const intFib outStatus = cImageStructure::restoreXml( pXmlElement );
						if ( outStatus < 0 ){
							return outStatus;
						}
						bImageStructureDataRestored = true;
						if ( ( iReturn < outStatus ) && ( 0 <= iReturn ) ){
							iReturn = outStatus;
						}
					}else{//two image structures to restore
						if ( iReturn == 0 ){
							iReturn = 1;
						}
					}
				}else{//unknown element to restore
					if ( iReturn == 0 ){
						iReturn = 1;
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
				//warning: invalid image structur
				if ( iReturn == 0 ){
					iReturn = 1;
				}
				continue;
		}//end switch restore image structure members
	}//end for restore image structure members
	
	if ( ! bBasisColorVectorRestored ){
		//warning: no basis color vector restored
		if ( ( 0 <= iReturn ) && ( iReturn < 2 ) ){
			iReturn = 2;
		}
	}
	if ( ! bColorXSlopeVectorRestored ){
		//warning: no x slope color vector restored
		if ( ( 0 <= iReturn ) && ( iReturn < 2 ) ){
			iReturn = 2;
		}
	}
	if ( ! bColorYSlopeVectorRestored ){
		//warning: no y slope color vector restored
		if ( ( 0 <= iReturn ) && ( iReturn < 2 ) ){
			iReturn = 2;
		}
	}
	if ( ! bImageStructureDataRestored ){
		//warning: no image structure data restored
		if ( ( 0 <= iReturn ) && ( iReturn < 2 ) ){
			iReturn = 2;
		}
	}
	return iReturn;
}


//methods of iConvertImageStructureToFib

/**
 * This method is for converting the data of this object to a Fib object.
 * The area is converted with the iConvertAreaToExtObjects class,
 * which is set by the cUseConvertAreaToExtObjectsStrategy class methods.
 * For antialising it uses the cConvertFibDatabaseObject::convertToAntialised()
 * method.
 * @see iConvertAreaToExtObjects
 * @see cConvertFibDatabaseObject::convertToAntialised()
 * @see iConvertAreaToExtObjects
 * @see cUseConvertAreaToExtObjectsStrategy
 *
 * @param pImageSearchData a pointer to the image search data of found
 * 	image parts, which will overwrite area parts
 * 	(the area can be bigger, because some parts of it won't be seen)
 * @param maxValue the maximum possible value in all evalued parameters
 * 	of the evalued Fib elements will allways have lower absolute values
 * 	or the values (parameters) of the Fib elements are coordinate values
 * 	of points;
 * 	if 0 (standard value) is given, the maximum possible value will
 * 	be evalued from the given data (absolute maximum in given data * 256)
 * @param maxErrorPerValue the maximal error for the border points to
 * 	find on one border point; every point in the area of the generated
 * 	Fib object will have a distance lower or equal maxErrorPerValue to
 * 	a point in this structure or an overlappted point of pImageSearchData
 * @return a Fib object which represents the data of this object
 * 	Beware: You have to delete the returned Fib object after usage.
 * 		Also the given root element will contain no domains, you have to
 * 		create them if needed (eg. with cRoot::generateNeededDomains() ).
 */
cRoot * cImageAreaLinearColor::convertToFib(
		const cImageSearchData * pImageSearchData,
		const double maxValue, const unsigned long ulMaxErrorPerPoint ) const{
	
	const double maxErrorPerValue = ulMaxErrorPerPoint;
	
	//convert this object into a external object area
	const list< cExtObject * > liConvertedTiles =
		getStrategy()->convertToExtObjects( structurePoints, pImageSearchData,
			bIsAntialised, maxValue, maxErrorPerValue );
	
	if ( liConvertedTiles.empty() ){
		//can not create an Fib object
		return NULL;
	}
	
	//sort external objects acording their identifiers
	map< longFib, list< cExtObject * > > mapExtObjectClasses;
	
	for ( list< cExtObject * >::const_iterator itrExtObject = liConvertedTiles.begin();
			itrExtObject != liConvertedTiles.end(); itrExtObject++ ){
		
		mapExtObjectClasses[ (*itrExtObject)->getIdentifier() ].push_back(
			*itrExtObject );
	}
	
	/*if more than one external object for one identifier exists
	 -> convert the external object list into a set element with an external
	 object subobject*/
	list< cFibElement * > liConvertedObjects;
	
	for ( map< longFib, list< cExtObject * > >::iterator
			itrActualExtObjectClass = mapExtObjectClasses.begin();
			itrActualExtObjectClass != mapExtObjectClasses.end();
			itrActualExtObjectClass++ ){
		
		list< cExtObject * > & liConvertedExtObjects =
			itrActualExtObjectClass->second;
		
		if ( 1 < liConvertedExtObjects.size() ){
			//combine the external objects into one set element
			cExtObject * pActualExternalObject =
				liConvertedExtObjects.front();
			
			const unsigned int uiNumberInVar =
				pActualExternalObject->getNumberOfInputValues();
			
			cFibSet * pSetElement = new cFibSet( uiNumberInVar, pActualExternalObject );
			liConvertedObjects.push_back( pSetElement );
			
			/* set the input variables of the external object to the defined
			 * variables of the set element*/
			cVectorExtObject * pVecInputVector = pActualExternalObject->getInputVector();
			cVectorFibSet vecSet( uiNumberInVar );
			for ( unsigned int uiActualVariable = 1; uiActualVariable <= uiNumberInVar;
					uiActualVariable++ ){
				
				vecSet.setValue( uiActualVariable,
					pVecInputVector->getValue( uiActualVariable ) );
				
				pVecInputVector->setVariable( uiActualVariable,
					pSetElement->getDefinedVariable( uiActualVariable ) );
			}
			//remove original external object
			pSetElement->addVector( vecSet );
			liConvertedExtObjects.pop_front();
			
			//add for every original external object element a vector to the set element
			while ( ! liConvertedExtObjects.empty() ){
				pActualExternalObject = liConvertedExtObjects.back();
				
				const cVectorExtObject * pVecActualExtObject =
					pActualExternalObject->getInputVector();
				//copy the values from the external object to set vector to add
				for ( unsigned int uiActualVariable = 1;
						uiActualVariable <= uiNumberInVar; uiActualVariable++ ){
					
					vecSet.setValue( uiActualVariable,
						pVecActualExtObject->getValue( uiActualVariable ) );
				}
				pSetElement->addVector( vecSet );
				
				//remove original external object
				pActualExternalObject->deleteObject();
				liConvertedExtObjects.pop_back();
			}
		}else{//one object in liConvertedExtObjects
			liConvertedObjects.push_back( liConvertedExtObjects.front() );
		}//end if convert liConvertedExtObjects
	}//end for convert external object class
	//all to use Fib objects are in liConvertedObjects
	
	cFibElement * pConvertedObject = NULL;
	
	//convert all external objects to objects with subobject
	fib::algorithms::nFibDatabase::cConvertFibDatabaseObject
		convertFibDatabaseObject;
	for ( list< cFibElement * >::iterator
			itrActualObject = liConvertedObjects.begin();
			itrActualObject != liConvertedObjects.end();
			itrActualObject++ ){
		
		cExtObject * pActualExternalObject =
			((cExtObject*)((*itrActualObject)->getFibElement( 'o', 1 )));
		
		if ( pActualExternalObject == NULL ){
			//no external object -> can't convert to version with subobject
			continue;
		}
		
#ifdef DEBUG
		cout<<"created area object:"<<endl;
		(*itrActualObject)->storeXml( cout );
		cout<<endl;
#endif //DEBUG
		//convert
		bool bObjectConverted = true;
		if ( ! bIsAntialised ){
			//change identifiers and external object for point subobject (isPointSubObject)
			bObjectConverted = convertFibDatabaseObject.convertToPointSubObject(
				pActualExternalObject );
#ifdef DEBUG
			cout<<"converted to point subobject:"<<endl;
			(*itrActualObject)->storeXml( cout );
			cout<<endl;
#endif //DEBUG
		}//else if antialised -> no change needed (antialised version with point subobject generated)
		
		if ( ! bObjectConverted ){
			//warning: object was not converted to point subobject
			//set color for entire object to basis color (can't do something else)
			(*itrActualObject) = new cProperty( vecColorBasis, (*itrActualObject) );
			continue;
		}//else object was converted to object with point subobject
		//set color for object directly below the created point element
		cFibElement * pExtSubObject = pActualExternalObject->getSubobject( 1 );
		if ( pExtSubObject == NULL ){
			/*Error: no first subobject in external object
				-> set color for entire object to basis color (can't do something else) */
			(*itrActualObject) = new cProperty( vecColorBasis, (*itrActualObject) );
			continue;
		}//else
		
		list<cFibElement*> liPointsInExtSubObject = pExtSubObject->
			getAllFibElements( 'u', 1, 'p', ED_BELOW_EQUAL, 2, false );
		if ( liPointsInExtSubObject.empty() ){
			/*Error: no points in first subobject of external object
				-> set color for entire object to basis color (can't do something else) */
			(*itrActualObject) = new cProperty( vecColorBasis, (*itrActualObject) );
			continue;
		}//else
		bool bPropertyAdded = false;
		
		for ( list<cFibElement*>::iterator
				itrExtObject = liPointsInExtSubObject.begin();
				itrExtObject != liPointsInExtSubObject.end(); itrExtObject++ ){
			
			cPoint * pPoint = ((cPoint*)(*itrExtObject));
			if ( pPoint == NULL ){
				/*Error: no point element
					-> set color for entire object to basis color (can't do something else) */
				continue;
			}//else
			//get the first external subobject
			//get the property element above the point
			cFibElement * pSuperiorFibElement = pPoint->getSuperiorFibElement();
			if ( pSuperiorFibElement == NULL ){
				/*Error: no Fib element
					-> set color for entire object to basis color (can't do something else) */
				continue;
			}//else
			//get position variables for functions
			cFibVariable * pVariableX = pPoint->getPosition()->getVariable( 1 );
			cFibVariable * pVariableY = pPoint->getPosition()->getVariable( 2 );
			
			if ( ( pVariableX == NULL ) || ( pVariableY == NULL ) ){
				/*Error: positions variables
					-> set color for entire object to basis color (can't do something else) */
				continue;
			}//else
			cProperty * pColorProperty = new cProperty( vecColorBasis, pPoint );
			//create functions for colors
			cFibElement * pColorObject = pColorProperty;
			cFunctionVariable funVariableX( pVariableX );
			cFunctionVariable funVariableY( pVariableY );
			
			const unsignedIntFib uiNumberOfColorElements =
				vecColorBasis.getNumberOfElements();
			for ( unsignedIntFib uiActualColorElement = 1;
					uiActualColorElement <= uiNumberOfColorElements;
					uiActualColorElement++ ){
				
				if ( ( vecColorXSlope.getValue( uiActualColorElement ) != 0.0 ) ||
						( vecColorYSlope.getValue( uiActualColorElement ) != 0.0 ) ){
					/*create function for color element:
						vecColorBasis[ uiActualColorElement ] +
						vecColorXSlope[ uiActualColorElement ] * x +
						vecColorYSlope[ uiActualColorElement ] * y */
					
					cFunctionValue funBasisValue(
						vecColorBasis.getValue( uiActualColorElement ) );
					
					cFunctionAdd * pFunAdd = NULL;
					
					if ( ( vecColorXSlope.getValue( uiActualColorElement ) != 0.0 ) &&
							( vecColorYSlope.getValue( uiActualColorElement ) != 0.0 ) ){
						//both slope factors not 0
						cFunctionValue funXSlopeValue(
							vecColorXSlope.getValue( uiActualColorElement ) );
						cFunctionValue funYSlopeValue(
							vecColorYSlope.getValue( uiActualColorElement ) );
						
						cFunctionMult funMultX( funXSlopeValue, funVariableX );
						cFunctionMult funMultY( funYSlopeValue, funVariableY );
						
						cFunctionAdd funSlopeAdd( funMultX, funMultY );
						pFunAdd = new cFunctionAdd( funBasisValue, funSlopeAdd );
						
					}else if ( vecColorXSlope.getValue( uiActualColorElement ) != 0.0 ){
						//just x slope factor not 0
						cFunctionValue funXSlopeValue(
							vecColorXSlope.getValue( uiActualColorElement ) );
						
						cFunctionMult funMultX( funXSlopeValue, funVariableX );
						
						pFunAdd = new cFunctionAdd( funBasisValue, funMultX );
					}else{//( vecColorYSlope.getValue( uiActualColorElement ) != 0.0 )
						//just y slope factor not 0
						cFunctionValue funYSlopeValue(
							vecColorYSlope.getValue( uiActualColorElement ) );
						
						cFunctionMult funMultY( funYSlopeValue, funVariableY );
						
						pFunAdd = new cFunctionAdd( funBasisValue, funMultY );
					}
					//create function element for color element
					cFunction * pNewFunctionElement =
						new cFunction( *pFunAdd, pColorObject );
					pColorObject = pNewFunctionElement;
					
					delete pFunAdd;
					
					//set color element in property to defined variable of function element
					pColorProperty->getProperty()->setVariable( uiActualColorElement,
						pNewFunctionElement->getDefinedVariable() );
					
#ifdef DEBUG
					cout<<"pColorObject:"<<endl;
					pColorObject->storeXml( cout );
					cout<<endl;
#endif //DEBUG
				}//else no need to create function -> color element is basis color
			}//end for create a function for color elements
			//overwrite pPoint with the created Fib object (which includes to old pPoint)
			if ( pSuperiorFibElement->getType() == 'o' ){
				/*point object directly below external object
				-> add new object as first subobject of external object*/
				((cExtObject*)(pSuperiorFibElement))->setSubobject(
					1, pColorObject, false );
			}else{//superior object of point is other object (the transparency property)
				pSuperiorFibElement->overwriteObjectWithObject(
					pColorProperty, 'u', 2, false );
			}
			bPropertyAdded = true;
		}//end for all points in first external subobject
		if ( ! bPropertyAdded ){
			/*Error: no property element added
				-> set color for entire object to basis color (can't do something else) */
			(*itrActualObject) = new cProperty( vecColorBasis, (*itrActualObject) );
		}
		
	}//end for convert all external objects to ther transparency version
	//if needed put all objects into a list element
	pConvertedObject = liConvertedObjects.front();
	if ( 1 < liConvertedObjects.size() ){
		/*more than one object in converted list
		 *-> join them to one object with a list element */
		pConvertedObject = new cList( liConvertedObjects );
	}
	
	//put the created object into an root element
	cRoot * pCreatedRootObject = new cRoot( pConvertedObject );
	
	return pCreatedRootObject;
}






