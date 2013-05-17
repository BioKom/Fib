/**
 * @class cVectorProperty
 * file name: cVectorProperty.cpp
 * @author Betti Oesterholz
 * @date 17.07.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a property vector.
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
 * This class represents a property vector of the Fib -multimedialanguage.
 * It is a vector for properties.
 *
 */
/*
History:
21.06.2009  Oesterholz  created
05.07.2010  Oesterholz  lowerPropertyVector() moved her from cEvaluePositionList
	and operator<() added;
	distanceOfProperty() and distanceOfPropertyOfNull() moved from
	cFibObjectFitnessBasicAlgorithm to hear and distanceToProperty() and
	distanceOfPropertyToNull() added
17.12.2010  Oesterholz  isOverwritenVector() method added
18.12.2010  Oesterholz  isOverwriting() and isEvalued() methods added
17.02.2013  Oesterholz FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE implemented
16.03.2013  Oesterholz  clone() method added
*/

#include "cVectorProperty.h"

#include "cFibElement.h"


using std::vector;

using namespace fib;


//TODO change cFibElement to cProperty

/**
 * The constructor of the propertyvector.
 *
 * @param uiInPropertyType a number for the type of the property,
 * 	this should be a type with a correct standard domain
 * @param pDefiningPropertyElement the Fib -propertyelement which
 * 	defines/ uses the propertyvector
 */
cVectorProperty::cVectorProperty( unsignedIntFib uiInPropertyType,
		cFibElement *pDefiningPropertyElement ):
		uiPropertyType( uiInPropertyType ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorProperty( uiInPropertyType="<<uiInPropertyType<<", "<<pDefiningPropertyElement<<") constructor"<<endl);
	
	pDefiningFibElement = pDefiningPropertyElement;

	//try to get the domain for this property type
	cDomainVectorBasis * propertyDomain = getDomain();
	
	unsignedIntFib iNumberOfVectorElements = 0;
	if ( propertyDomain ){
		iNumberOfVectorElements = propertyDomain->getNumberOfElements();
	}else{
		//if no properdomain exists -> get the standarddomain for the propertytype
		
		//somtimes the number of dimensions is important for the property
		unsignedIntFib uiNumberOfDimensions = 0;
	
		if ( pDefiningPropertyElement == NULL ){
			//can't get enviroment/ no enviroment -> return standard domain
			uiNumberOfDimensions = 2;
		}else{
			uiNumberOfDimensions = pDefiningPropertyElement->getNumberOfDimensions();
		}
	
		//select the correct number of vector elements for the property type
		cTypeProperty propertyType( uiPropertyType, uiNumberOfDimensions );
		
		propertyDomain = (cDomainVectorBasis*)propertyType.getStandardDomain();
		iNumberOfVectorElements = propertyDomain->getNumberOfElements();
		delete propertyDomain;
	}
	
	//init the vector elements
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	uiNumberOfElements = iNumberOfVectorElements;
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
	liVectorType.resize( iNumberOfVectorElements, VALUE );
	liVectorValues.resize( iNumberOfVectorElements, 0 );
	liVectorVariable.resize( iNumberOfVectorElements, NULL );
}


/**
 * The copy constructor of the vector.
 *
 * @param vector the vector from which to copy the data
 * @param definingFibElement the Fib -element which defines/ uses
 * 	the new vector
 */
cVectorProperty::cVectorProperty( const cVectorProperty & vector,
		cFibElement * definingFibElement ):
		cFibVector( vector, definingFibElement ),
		uiPropertyType( vector.uiPropertyType ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorProperty("<<&vector<<", "<<definingFibElement<<") copyconstructor"<<endl);
	DEBUG_OUT_L3(<<"calling : "<<getNumberOfElements()<<"  "<<endl);

	if ( definingFibElement ){
		//use the domain of the new defining element
		setDefiningFibElement( definingFibElement );
	}//else copy the other vector exactly
	DEBUG_OUT_L3(<<"const end calling2 : "<<getNumberOfElements()<<"  "<<endl);
}


/**
 * The constructor of the propertyvector.
 *
 * @param uiInPropertyType a number for the type of the property
 * @param iNumberOfElements number of elements in the vector
 * @param pDefiningPropertyElement the Fib -propertyelement which
 * 	defines/ uses the propertyvector
 */
cVectorProperty::cVectorProperty( unsignedIntFib uiInPropertyType,
		unsignedIntFib iNumberOfElements ,
		cFibElement *pDefiningPropertyElement ):
		cFibVector( iNumberOfElements, pDefiningPropertyElement ),
		uiPropertyType( uiInPropertyType ){
//nothing to do
	DEBUG_OUT_L3(<<this<<"->cVectorProperty("<<uiInPropertyType<<", "<<iNumberOfElements<<", "<<pDefiningPropertyElement<<") constructor"<<endl);
	
}


/**
 * The constructor of the propertyvector.
 *
 * @param typeProperty the type this propertyvector should have
 */
cVectorProperty::cVectorProperty( const cTypeProperty & typeProperty ):
		cFibVector( 0, NULL ),
		uiPropertyType( typeProperty.getNumberOfProperty() ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorProperty("<<&typeProperty<<") typeconstructor"<<endl);
	
	cDomainVectorBasis * pDomain =
		(cDomainVectorBasis*)(typeProperty.getStandardDomain());
	if ( pDomain != NULL ){
		//set the correct number of vectorelements
		unsigned int uiNumberOfVectorElements = pDomain->getNumberOfElements();
		
#ifdef FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		uiNumberOfElements = uiNumberOfVectorElements ,
#endif //FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE
		liVectorType = vector<eVectorType>( uiNumberOfVectorElements, VALUE );
		liVectorValues = vector<doubleFib>( uiNumberOfVectorElements, 0 );
		liVectorVariable = vector<cFibVariable*>( uiNumberOfVectorElements, NULL );
		
		delete pDomain;
	}
}


/**
 * The constructor for restoring a vector from an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node the vector is stored in
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
 * 	to restore vector, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 */
cVectorProperty::cVectorProperty( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables ):
		cFibVector( pXmlElement, outStatus, liDefinedVariables ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorProperty() constructor restore xml"<<endl);
	
	//check the vector type
	if ( pXmlElement == NULL ){
		//noting to restore
		outStatus = -1;
		return;
	}
	if ( outStatus < 0 ){
		//an error occured while restoring the vector
		return;
	}
	//check the attribute of the vector
	const char * szVectorXmlType = pXmlElement->Attribute( "type" );
	
	if ( szVectorXmlType == NULL ){
		outStatus = 2;
		return;
	}else if ( strncmp( "property.", szVectorXmlType, 9 ) != 0 ){
		outStatus = 2;
		return;
	}
	if ( strlen( szVectorXmlType ) < 10 ){
		//not enought characters to store "property." + type
		outStatus = 2;
		return;
	}
	//evalue the property type
	string szPropertyName( &(szVectorXmlType[ 9 ]) );
	
	uiPropertyType = cTypeProperty::getNumberForPropertyName( szPropertyName );
}


/**
 * This constructor restores a propertyvector from the stream where it is
 * stored in the compressed fib -format.
 *
 * @param iBitStream the stream where this vector is stored to in,
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
 * 	to restore vector, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 * @param pInVectorDomain the domain for this vector
 * @param pInDomainVariable the domain for variables
 * @param uiInPropertyType a number for the type of the property
 */
cVectorProperty::cVectorProperty( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomain * pInVectorDomain, const cDomain * pInDomainVariable,
		unsignedIntFib uiInPropertyType ):
		cFibVector( iBitStream, outStatus, liDefinedVariables,
			pInVectorDomain, pInDomainVariable ), uiPropertyType( uiInPropertyType ){
	//nothing to do
	DEBUG_OUT_L3(<<this<<"->cVectorProperty() constructor restore bit"<<endl);
}


/**
 * This method clones this object.
 *
 * @return a pointer to the clone of this object
 */
cVectorProperty * cVectorProperty::clone() const{
	
	return new cVectorProperty( *this );
}


/**
 * This method creates an instance of this vector type.
 *
 * @param iNumberOfElements number of elements in the vector
 * @param definingPropertyElement the Fib -propertyelement which
 * 	defines/ uses the propertyvector
 */
cVectorProperty * cVectorProperty::createInstance(
		unsignedIntFib iNumberOfElements,
		cFibElement *definingPropertyElement ) const{

	DEBUG_OUT_L3(<<this<<"->cVectorProperty::createInstance("<<iNumberOfElements<<", "<< definingPropertyElement<<")"<<endl);
	
	return new cVectorProperty( uiPropertyType, iNumberOfElements,
		definingPropertyElement );
}


/**
 * Returns the type of the vector.
 * You have to delete the returned object after usage.
 *
 * @return the type of the property
 */
cTypeElement * cVectorProperty::getElementType() const{
	/*the type is diemnsion*/
	DEBUG_OUT_L3(<<this<<"->cVectorProperty::getElementType()");
	DEBUG_OUT_L4(<<" (#typs="<<liVectorType.size()<<" #variables="<<liVectorVariable.size()<<" #values="<<liVectorValues.size()<<")"<<endl);

	return new cTypeProperty( uiPropertyType );
}


/**
 * This method returns a number for the type of the property.
 *
 * @return a number for the type of the property
 */
unsignedIntFib cVectorProperty::getPropertyType() const{
	
	DEBUG_OUT_L3(<<this<<"->cVectorProperty::getPropertyType()"<<endl);
	
	return uiPropertyType;
}


/**
 * This method checks if the given vector is overwritten by this vector.
 *
 * @param vectorToCheck the vector to check, if it is overwritten
 * @return true if vectorToCheck is overwritten by this vector, else false
 */
bool cVectorProperty::isOverwritenVector( const cVectorProperty & vectorToCheck ) const{
	
	
	const cTypeProperty typeOfThisProperty( uiPropertyType );
	return typeOfThisProperty.isOverwritenTyp( vectorToCheck.getPropertyType() );
}


/**
 * This function checks if the this property vector overwrites property vectors.
 *
 * @return if the given vector overwrites vector true, else false
 */
bool cVectorProperty::isOverwriting() const{
	
	return cTypeProperty::isOverwriting( uiPropertyType );
}


/**
 * @return this method returnes true, if the property of this vector is
 * 	for evaluating a fib -object, else false is returned
 */
bool cVectorProperty::isEvalued() const{

	return cTypeProperty::isEvalued( uiPropertyType );
}


/**
 * @return the name for the type of the vector
 */
string cVectorProperty::getVectorType() const{
	
	DEBUG_OUT_L3(<<this<<"->cVectorProperty::getVectorType()"<<endl);
	
	cTypeProperty propertyType( uiPropertyType );
	
	return "property." + propertyType.getNameOfProperty();
}


/**
 * This Method makes this vectorelements equal to the correspondending
 * vectorelements of the given vector.
 * The type of the vector won't be changed.
 * The type of the propertie will be adapted.
 *
 * @param vector the vector to copy
 */
cVectorProperty & cVectorProperty::operator=( const cFibVector &vector ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorProperty::operator=( "<<&vector<<" ) (vector.getVectorType()="<< vector.getVectorType() <<")"<<endl);
	
	this->cFibVector::operator=( vector );
	
	if ( (vector.getVectorType().compare( 0, 8,"property" )) == 0 ){
		//this is a property vector
		DEBUG_OUT_L3(<<"setting propertytype to "<< ((cVectorProperty&)(vector)).getPropertyType() <<endl);
		uiPropertyType = ((cVectorProperty&)(vector)).getPropertyType();
	}
	
	return *this;
}


/**
 * This function compares this propertyvector with the given propertyvector.
 * Propertyvectors is lower if it's propertypvalues is lower than the
 * propertyvectors of the other vector or its propertypvalues is equal, but
 * if it has less elements than the other vector or it's i'th element is
 * lower and all j'th elements with i > j are equal.
 *
 * @see cFibVector::lowerVector()
 * @see lowerPropertyVector()
 * @param vector the property to compare this with
 * @return true if this propertyvectors is lower than the
 * 	propertyvectors vector, else false
 */
bool cVectorProperty::operator<( const cVectorProperty & vector ) const{

	return lowerPropertyVector( *this, vector );
}


/**
 * This function compares two propertyvectors.
 * Propertyvectors is lower if it's propertypvalues is lower than the
 * propertyvectors of the other vector or its propertypvalues is equal, but
 * if it has less elements than the other vector or it's i'th element is
 * lower and all j'th elements with i > j are equal.
 *
 * @see cFibVector::lowerVector()
 * @param vector1 the first property to compare
 * @param vector2 the second property to compare
 * @return true if the propertyvectors vector1 is lower than that
 * 	of vector2, else false
 */
bool cVectorProperty::lowerPropertyVector( const cVectorProperty & vector1,
		const cVectorProperty & vector2 ){
	
	if ( vector1.getPropertyType() < vector2.getPropertyType() ){
		return true;
	}
	if ( vector2.getPropertyType() < vector1.getPropertyType() ){
		return false;
	}/*else (vector1.getPropertyType() == vector2.getPropertyType())
	-> same typs -> compair the vectors*/
	return cFibVector::lowerVector( vector1, vector2 );
}


/**
 * This function evalues the distance of this property to the given
 * property of the same type.
 * This distance is the sum of the differnece of the property
 * vectorelements
 *
 *	@param property the first propertyvector
 * @return the sum of differneces betwean the vectorelements in this
 * 	property and the given property
 */
doubleFib cVectorProperty::distanceToProperty(
		const cVectorProperty & property ) const{

	return distanceOfProperty( *this, property );
}


/**
 * This function evalues the distance of two properties of the same type.
 * This distance is the sum of the differnece of the property
 * vectorelements
 *
 *	@param property1 the first propertyvector
 *	@param property2 the second propertyvector
 * @return the sum of differneces betwean the vectorelements in property1
 * 	and property2
 */
doubleFib cVectorProperty::distanceOfProperty( const cVectorProperty & property1,
		const cVectorProperty & property2 ){
	
	doubleFib dDistance = 0;
	const unsignedIntFib uiNumberOfElements = property1.getNumberOfElements();
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= uiNumberOfElements; uiActualElement++ ){
		
		//add absolutevalue of the difference
		if ( property2.getValue( uiActualElement ) < property1.getValue( uiActualElement ) ){
			dDistance += property1.getValue( uiActualElement ) -
				property2.getValue( uiActualElement );
		}else{
			dDistance += property2.getValue( uiActualElement ) -
				property1.getValue( uiActualElement );
		}
	}
	return dDistance;
}


/**
 * This function evalues the distance of the this property to a
 * property of the same type, wher all vectorelements are 0.
 * This distance is the sum of the differnece of the property
 * vectorelements
 *
 *	@param property the propertyvector
 * @return the sum of differneces betwean the vectorelements in property
 * 	and the nullvector of the same type with all vectorelements 0
 */
doubleFib cVectorProperty::distanceOfPropertyToNull() const{

	return distanceOfPropertyToNull( *this );
}


/**
 * This function evalues the distance of the given property to a
 * property of the same type, wher all vectorelements are 0.
 * This distance is the sum of the differnece of the property
 * vectorelements
 *
 *	@param property the propertyvector
 * @return the sum of differneces betwean the vectorelements in property
 * 	and the nullvector of the same type with all vectorelements 0
 */
doubleFib cVectorProperty::distanceOfPropertyToNull(
		const cVectorProperty & property ){
	
	doubleFib dDistance = 0;
	const unsignedIntFib uiNumberOfElements = property.getNumberOfElements();
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= uiNumberOfElements; uiActualElement++ ){
		
		//add absolutevalue of the difference
		if ( 0.0 < property.getValue( uiActualElement ) ){
			dDistance += property.getValue( uiActualElement );
		}else{
			dDistance -= property.getValue( uiActualElement );
		}
	}
	return dDistance;
}


