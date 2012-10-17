/**
 * @class cVectorPosition
 * file name: cVectorPosition.cpp
 * @author Betti Oesterholz
 * @date 11.05.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a positions -fib -vector.
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
 * This file contains the class of all Fib -positionvectors.
 * Thes positionvectors are used in Fib pointelements, for the position of
 * the point.
 *
 */
/*
History:
11.05.2009  Oesterholz  created
*/


#include "cVectorPosition.h"

#include "cTypeDimension.h"
#include "cDomains.h"
#include "cFibElement.h"


using std::vector;

using namespace fib;


/**
 * The constructor of the positionvector.
 *
 * @param definingPointElement the Fib -pointelement which defines/ uses
 * 	the positionsvector
 */
cVectorPosition::cVectorPosition( cFibElement & definingPointElement ):
		cFibVector( definingPointElement.getNumberOfDimensions(),
			&definingPointElement ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorPosition("<<&definingPointElement<<") constructor"<<endl);
	//nothing to do
}


/**
 * The constructor of the positionvector.
 *
 * @param iNumberOfDimensions number of elements in the vector or the dimensions
 * @param pDefiningPointElement the Fib -pointelement which defines/ uses
 * 	the positionsvector
 */
cVectorPosition::cVectorPosition( unsignedIntFib iNumberOfDimensions,
		 cFibElement * pDefiningPointElement ):
	cFibVector( iNumberOfDimensions, pDefiningPointElement ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorPosition("<<iNumberOfDimensions<<", "<<pDefiningPointElement<<") constructor"<<endl);
}

/**
 * The copy constructor of the vector.
 *
 * @param vector the vector from which to copy the data
 * @param definingFibElement the Fib -element which defines/ uses
 * 	the new vector
 */
cVectorPosition::cVectorPosition( const cVectorPosition & vector,
		cFibElement *definingFibElement ):
		cFibVector( vector, definingFibElement ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorPosition("<<&vector<<", "<<definingFibElement<<") copyconstructor"<<endl);
	DEBUG_OUT_L3(<<"calling : "<<getNumberOfElements()<<"  ");
	
	if ( definingFibElement ){
		//use the domain of the new defining element
		setDefiningFibElement( definingFibElement );
	}//else copy the other vector exactly
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
cVectorPosition::cVectorPosition( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables ):
		cFibVector( pXmlElement, outStatus, liDefinedVariables ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorPosition() constructor restore xml"<<endl);
	
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
	const string szVectortypeNeeded( "position" );
	
	if ( szVectorXmlType == NULL ){
		outStatus = -2;
		return;
	}else if ( szVectortypeNeeded != szVectorXmlType ){
		outStatus = -2;
		return;
	}
}


/**
 * This constructor restores a positionsvector from the stream where it is
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
 */
cVectorPosition::cVectorPosition( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomain * pInVectorDomain, const cDomain * pInDomainVariable ):
		cFibVector( iBitStream, outStatus, liDefinedVariables,
			pInVectorDomain, pInDomainVariable ){
	//nothing to do
	DEBUG_OUT_L3(<<this<<"->cVectorPosition() constructor restore bit"<<endl);
}


/**
 * This method creates an instance of this vector type.
 *
 * @param iNumberOfDimensions number of elements in the vector
 * @param definingPointElement the Fib -pointelement which defines/ uses
 * 	the positionsvector
 */
cVectorPosition * cVectorPosition::createInstance(
		unsignedIntFib iNumberOfDimensions,
		cFibElement *definingPointElement ) const{
	
	DEBUG_OUT_L3(<<this<<"->cVectorPosition::createInstance("<<iNumberOfDimensions<<", "<<definingPointElement<<")"<<endl);
	
	return new cVectorPosition( iNumberOfDimensions, definingPointElement );
}


/**
 * Sets the Fib -element which defines/ uses this vector.
 * If the given pointer is the nullpointer (standardvalue), no
 * Fib -element defines this vector.
 *
 * @param definingFibElement a pointer to the Fib -element which
 * 	defines/ uses this vector
 * @param bCheckDomains getthe domains of the defining element and
 * 	check the vectorelements with it
 */
void cVectorPosition::setDefiningFibElement( cFibElement *fibElement,
		bool bCheckDomains ){

	DEBUG_OUT_L3(<<this<<"->cVectorPosition::setDefiningFibElement("<<fibElement<<", "<<bCheckDomains<<")"<<endl);
	
	if ( getNumberOfElements() != 0 ){
		return cFibVector::setDefiningFibElement( fibElement, bCheckDomains );
	}/*else don't change the vectorsize when the defining element changes
	and the vector has size 0*/
	pDefiningFibElement = fibElement;
}


/**
 * Returns the type of the vector.
 * You have to delete the returned object after usage.
 *
 * @return the type of the vector
 */
cTypeElement * cVectorPosition::getElementType() const{
	
	DEBUG_OUT_L3(<<this<<"->cVectorPosition::getElementType()"<<endl);
	
	/*the type is dimension type*/
	if ( pDefiningFibElement == NULL ){
		//can't get enviroment/ no enviroment -> return standard type
		return new cTypeDimension( getNumberOfElements() );
	}
	//try get the type from the valid domains
	cDomains validDomains = pDefiningFibElement->getValidDomains();
	cTypeDimension typeDimension;

	unsignedIntFib uiNumberOfDomains = validDomains.getNumberOfDomains();
	for ( unsignedIntFib uiActualDomain = 1;
			uiActualDomain <= uiNumberOfDomains; uiActualDomain++ ){
		if ( typeDimension.equalElementType(
				*(validDomains.getType( uiNumberOfDomains )) ) ){
			//correct type found -> return a copy of it
			return (validDomains.getType( uiNumberOfDomains ))->clone();
		}
	}

	//no type found -> return the standardtype
	return new cTypeDimension( getNumberOfElements() );
}


/**
 * @return the name for the type of the vector
 */
string cVectorPosition::getVectorType() const{

	DEBUG_OUT_L3(<<this<<"->cVectorPosition::getVectorType()"<<endl);
	
	return "position";
}



