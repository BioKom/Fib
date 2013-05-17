/**
 * @file cImageAreaSameColor
 * file name: cImageAreaSameColor.cpp
 * @author Betti Oesterholz
 * @date 23.10.2012
 * @mail Oesterholz@Fib-development.org
 *
 * System: C++
 *
 * This file implements a class to store the data of a same colored area in
 * an image.
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
 * This file implements a class to store the data of a same colored area in
 * an image.
 * If you want to convert an image to Fib structures, you have to search
 * the image for structures, which can be converted to Fib.
 * If you have a area with one color, you can use this class to represent it.
 */
/*
History:
23.10.2012  Oesterholz  created
*/

#include "cImageAreaSameColor.h"

#include "cFibSet.h"
#include "cPoint.h"
#include "cList.h"
#include "cRoot.h"
#include "cProperty.h"


//switches for debugging proposes
//#define DEBUG


using namespace fib::algorithms::nConvertToFib::nImage::nStructureData;
using namespace fib;


/**
 * standard constructor
 *
 * @param vecInColor the color the area has
 */
cImageAreaSameColor::cImageAreaSameColor( const cVectorProperty & vecInColor ):
		vecColor( vecInColor ){
	//nothing to do
}


/**
 * copy constructor
 *
 * @param structureToCopy the image structure to copy
 */
cImageAreaSameColor::cImageAreaSameColor( const cImageAreaSameColor & structureToCopy ):
		cImageStructure( structureToCopy ), vecColor( structureToCopy.vecColor ){
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
cImageAreaSameColor::cImageAreaSameColor( const TiXmlElement * pXmlElement,
		intFib & outStatus ):vecColor( 0 ){
	
	outStatus = cImageAreaSameColor::restoreXml( pXmlElement );
}


/**
 * destructor
 */
cImageAreaSameColor::~cImageAreaSameColor(){
	//nothing to do
}


/**
 * @return the name of the image structure (class name without the leading 'c')
 */
string cImageAreaSameColor::getName() const{
	
	return "ImageAreaSameColor";
}


/**
 * @see vecColor
 * @see setColorOfArea()
 * @return the color the area has
 */
cVectorProperty cImageAreaSameColor::getColorOfArea() const{
	
	return vecColor;
}


/**
 * @see vecColor
 * @see setColorOfArea()
 * @return the color the area has
 */
const cVectorProperty & cImageAreaSameColor::getColorOfAreaConst() const{
	
	return vecColor;
}


/**
 * This method sets the color the area has to the given color.
 *
 * @see vecColor
 * @see getColorOfArea()
 * @param vecInColor the color the area should have
 */
void cImageAreaSameColor::setColorOfArea( const cVectorProperty & vecInColor ){
	
	vecColor = vecInColor;
}


/**
 * This method clones this object.
 *
 * @return a clone of this object
 */
cImageAreaSameColor * cImageAreaSameColor::clone() const{
	
	return new cImageAreaSameColor( *this );
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
unsigned int cImageAreaSameColor::getNumberOfProperties( const bool bEvenIfOutside,
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
unsigned int cImageAreaSameColor::getNumberOfProperties( const bool bEvenIfOutside,
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
unsigned int cImageAreaSameColor::getPropertyType( const unsigned int uiPropertyNumber,
		const bool bEvenIfOutside, const cVectorPosition vecPoint ) const{
	
	if ( ( uiPropertyNumber == 1 ) &&
			( bEvenIfOutside || isStructurePoint( vecPoint ) ) ){
		//return the property type
		return vecColor.getPropertyType();
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
unsigned int cImageAreaSameColor::getPropertyType( const unsigned int uiPropertyNumber,
		const bool bEvenIfOutside, const pair< unsigned int, unsigned int> point ) const{
	
	if ( ( uiPropertyNumber == 1 ) &&
			( bEvenIfOutside || isStructurePoint( point ) ) ){
		return vecColor.getPropertyType();
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
unsigned int cImageAreaSameColor::getPropertyNumberForType( const unsigned int uiPropertyType,
		const bool bEvenIfOutside, const cVectorPosition vecPoint ) const{
	
	if ( bEvenIfOutside || isStructurePoint( vecPoint ) ){
		return ( vecColor.getPropertyType() == uiPropertyType )? 1 : 0;
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
unsigned int cImageAreaSameColor::getPropertyNumberForType( const unsigned int uiPropertyType,
		const bool bEvenIfOutside, const pair< unsigned int, unsigned int> point ) const{
	
	if ( bEvenIfOutside || isStructurePoint( point ) ){
		return ( vecColor.getPropertyType() == uiPropertyType )? 1 : 0;
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
list<cVectorProperty> cImageAreaSameColor::getPointProperties(
		const cVectorPosition & vecPoint, const bool bEvenIfOutside ) const{
	
	if ( bEvenIfOutside || isStructurePoint( vecPoint ) ){
		return list<cVectorProperty>( 1, vecColor );
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
list<cVectorProperty> cImageAreaSameColor::getPointProperties(
		const pair< unsigned int, unsigned int> & point,
		const bool bEvenIfOutside ) const{
	
	if ( bEvenIfOutside || isStructurePoint( point ) ){
		return list<cVectorProperty>( 1, vecColor );
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
cVectorProperty cImageAreaSameColor::getProperty( const cVectorPosition & vecPoint,
		const unsigned int uiPropertyType, const bool bEvenIfOutside ) const{
	
	if ( bEvenIfOutside || isStructurePoint( vecPoint ) ){
		if ( vecColor.getPropertyType() == uiPropertyType ){
			return vecColor;
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
cVectorProperty cImageAreaSameColor::getProperty(
		const pair< unsigned int, unsigned int> & point,
		const unsigned int uiPropertyType, const bool bEvenIfOutside ) const{
	
	if ( bEvenIfOutside || isStructurePoint( point ) ){
		if ( vecColor.getPropertyType() == uiPropertyType ){
			return vecColor;
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
cVectorProperty cImageAreaSameColor::getPropertyForNumber(
		const cVectorPosition & vecPoint,
		const unsigned int uiPropertyNumber, const bool bEvenIfOutside ) const{
	
	if ( bEvenIfOutside || isStructurePoint( vecPoint ) ){
		if ( uiPropertyNumber == 1 ){
			return vecColor;
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
cVectorProperty cImageAreaSameColor::getPropertyForNumber(
		const pair< unsigned int, unsigned int> & point,
		const unsigned int uiPropertyNumber, const bool bEvenIfOutside ) const{
	
	if ( bEvenIfOutside || isStructurePoint( point ) ){
		if ( uiPropertyNumber == 1 ){
			return vecColor;
		}
	}//else
	return cVectorProperty( cTypeProperty::NONE );
}



/**
 * This method checks if the given image structure is equal to this image
 * structure.
 *
 * @param imageStructure the image structure, which should be equal to this
 * 	image structure
 * @return true if the given image structure is equal to this image
 * 	structure, else false
 */
bool cImageAreaSameColor::equal( const cImageStructure &imageStructure ) const{
	
	//check if the image structure and class type is correct
	if ( ! cImageStructure::equal( imageStructure ) ){
		//the image structure or class type is not equal -> not equal
		return false;
	}
	const cImageAreaSameColor * pImageAreaSameColor =
		((cImageAreaSameColor*)(& imageStructure));

	if ( vecColor.equal( pImageAreaSameColor->getColorOfAreaConst() ) ){
		//color vector not equal -> structure not equal
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
bool cImageAreaSameColor::storeXml( ostream & ostream ) const{
	
	ostream<<"<imageAreaSameColor>"<<endl;
	
	if ( ! vecColor.storeXml( ostream ) ){
		//error while storing
		return false;
	}
	if ( ! cImageStructure::storeXml( ostream ) ){
		return false;
	}
	
	ostream<<"</imageAreaSameColor>"<<endl;
	
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
intFib cImageAreaSameColor::restoreXml( const TiXmlElement * pXmlElement ){
	
	intFib iReturn = 0;
	
	if ( pXmlElement == NULL ){
		//nothing to restore
		return -1;
	}
	const string szElementType( pXmlElement->Value() );
	if ( szElementType != "imageAreaSameColor" ){
		//wrong element type to restore
		return -2;
	}
	
	//no variables defined
	list<cFibVariable*> liDefinedVariables;
	
	bool bColorVectorRestored = false;
	bool bImageStructureDataRestored = false;
	
	for ( const TiXmlNode * pChild = pXmlElement->FirstChild();
			pChild != NULL; pChild = pChild->NextSibling() ) {
		
		const int iType = pChild->Type();
		
		switch ( iType ){
			case TiXmlNode::ELEMENT:{
				//load the members
				const TiXmlElement * pXmlElement = pChild->ToElement();
				if ( pXmlElement == NULL ){
					if ( iReturn == 0 ){
						iReturn = 1;
					}
					continue;
				}
				const string szElementType( pXmlElement->Value() );
				
				if ( szElementType == "vector" ){
					//element for color vector
					if ( ! bColorVectorRestored ){
						//restore the color vector
						//check the attribute of the vector
						const char * szVectorXmlType = pXmlElement->Attribute( "type" );
						
						if ( szVectorXmlType == NULL ){
							if ( iReturn == 0 ){
								iReturn = 1;
							}
							continue;
						}else if ( strncmp( "property.", szVectorXmlType, 9 ) != 0 ){
							if ( iReturn == 0 ){
								iReturn = 1;
							}
							continue;
						}
						//error value to return
						intFib outStatus = 0;
						//restore the vector
						vecColor = cVectorProperty( pXmlElement, outStatus,
							liDefinedVariables );
						if ( outStatus < 0 ){
							return outStatus;
						}
						bColorVectorRestored = true;
						if ( ( iReturn < outStatus ) && ( 0 <= iReturn ) ){
							iReturn = outStatus;
						}
					}else{//two (color) vectors to restore
						if ( iReturn == 0 ){
							iReturn = 1;
						}
					}
				}else if ( szElementType == "imageStructure" ){
					//image structure data element
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
		}
	}//end switch restore image structure members
	
	if ( ! bColorVectorRestored ){
		//warning: no color vector restored
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
 * 	Fib object will have a distance lower or equal maxErrorPerValue
 * 	to a point in this structure or an overlappted point of pImageSearchData
 * @return a Fib object which represents the data of this object
 * 	Beware: You have to delete the returned Fib object after usage.
 * 		Also the given root element will contain no domains, you have to
 * 		create them if needed (eg. with cRoot::generateNeededDomains() ).
 */
cRoot * cImageAreaSameColor::convertToFib(
		const cImageSearchData * pImageSearchData,
		const double maxValue, const unsigned long ulMaxErrorPerPoint ) const{
	
#ifdef DEBUG
	cout<<" cImageAreaSameColor::convertToFib( pImageSearchData, maxValue="<<
		maxValue<<", ulMaxErrorPerPoint="<<ulMaxErrorPerPoint<<" ) started"<<endl;
	cout<<"This object:"<<endl;
	storeXml( cout );
#endif //DEBUG
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
	
	if ( bIsAntialised ){
		//change identifiers according antialising bIsAntialised
		
		//if no antialised version exists -> use not antialised version
		
		//convert all external objects to antialised objects
		for ( list< cFibElement * >::iterator
				itrActualObject = liConvertedObjects.begin();
				itrActualObject != liConvertedObjects.end();
				itrActualObject++ ){
			
			cExtObject * pActualExternalObject =
				((cExtObject*)((*itrActualObject)->getFibElement( 'o', 1 )));
			
			if ( pActualExternalObject == NULL ){
				//no external object -> can't convert to antialised
				continue;
			}
			
#ifdef DEBUG
			cout<<"converting external object:"<<endl;
			(*itrActualObject)->storeXml( cout );
			cout<<endl;
#endif //DEBUG
			
			//object is antialised
			//set color for object directly below the created point element
			cFibElement * pExtSubObject = pActualExternalObject->getSubobject( 1 );
			if ( pExtSubObject == NULL ){
				/*Error: no first subobject in external object
					-> set color for entire object to basis color (can't do something else) */
				(*itrActualObject) = new cProperty( vecColor, (*itrActualObject) );
				continue;
			}//else
			
			list<cFibElement*> liPointsInExtSubObject = pExtSubObject->
				getAllFibElements( 'u', 1, 'p', ED_BELOW_EQUAL, 2, false );
			if ( liPointsInExtSubObject.empty() ){
				/*Error: no points in first subobject of external object
					-> set color for entire object to basis color (can't do something else) */
				(*itrActualObject) = new cProperty( vecColor, (*itrActualObject) );
				continue;
			}//else
			bool bPropertyAdded = false;
			
			for ( list<cFibElement*>::iterator
					itrExtObject = liPointsInExtSubObject.begin();
					itrExtObject != liPointsInExtSubObject.end(); itrExtObject++ ){
				
				cPoint * pPoint = ((cPoint*)(*itrExtObject));
				if ( pPoint == NULL ){
					//Error: no point element -> set color for entire object
					continue;
				}
				//get the property element above the point
				cFibElement * pSuperiorFibElement =
					pPoint->getSuperiorFibElement();
				if ( pSuperiorFibElement == NULL ){
					//Error: no transparency property element-> set color for entire object
					continue;
				}
				
				cProperty * pColorProperty = new cProperty( vecColor, pPoint );
				
				//overwrite pPoint with the created Fib object (which includes to old pPoint)
				if ( pSuperiorFibElement->getType() == 'o' ){
					/*point object directly below external object
					-> add new object as first subobject of external object*/
					((cExtObject*)(pSuperiorFibElement))->setSubobject(
						1, pColorProperty, false );
				}else{//superior object of point is other object (the transparency property)
					pSuperiorFibElement->overwriteObjectWithObject(
						pColorProperty, 'u', 2, false );
				}
				bPropertyAdded = true;
			}//end for all points in first external subobject
			if ( ! bPropertyAdded ){
				/*Error: no property element added
					-> set color for entire object to basis color (can't do something else) */
				(*itrActualObject) = new cProperty( vecColor, (*itrActualObject) );
			}
			
		}
		//if needed put all objects into a list element
		pConvertedObject = liConvertedObjects.front();
		if ( 1 < liConvertedObjects.size() ){
			pConvertedObject = new cList( liConvertedObjects );
		}
	}else{//not antialised
		//if needed put all objects into a list element
		pConvertedObject = liConvertedObjects.front();
		if ( 1 < liConvertedObjects.size() ){
			pConvertedObject = new cList( liConvertedObjects );
		}
		//set the color property for the created object
		pConvertedObject = new cProperty( vecColor, pConvertedObject );
	}
	
	//put the created object into an root element
	cRoot * pCreatedRootObject = new cRoot( pConvertedObject );
	
#ifdef DEBUG
	cout<<endl<<"created Fib object:"<<endl;
	pCreatedRootObject->storeXml( cout );
	cout<<endl;
#endif //DEBUG
	return pCreatedRootObject;
}






