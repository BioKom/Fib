/**
 * @class cVectorChecksum
 * file name: cVectorChecksum.cpp
 * @author Betti Oesterholz
 * @date 06.10.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a checksumm -property -vector.
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
 * This class represents a checksum -property -vector of the
 * Fib -multimedialanguage.
 * It is a vector for checksum -properties.
 *
 */
/*
History:
06.10.2009  Oesterholz  created
16.03.2013  Oesterholz  clone() method added
*/


#include "cVectorChecksum.h"


using namespace fib;


/**
 * The constructor of the checksum -property -vector.
 *
 * @param pDefiningElement the Fib -element which
 * 	defines/ uses the checksum -property -vector
 */
cVectorChecksum::cVectorChecksum( cFibElement * pDefiningElement ):
		cVectorProperty( (intFib)(600), pDefiningElement ){
	//noting to do
	DEBUG_OUT_L3(<<this<<"->cVectorChecksum("<<pDefiningElement<<") constructor"<<endl);
}

/**
 * The copy constructor of the vector.
 *
 * @param vector the vector from which to copy the data
 * @param definingFibElement the Fib -element which defines/ uses
 * 	the new vector
 */
cVectorChecksum::cVectorChecksum( const cVectorChecksum & vector,
		cFibElement *definingFibElement ):
		cVectorProperty( vector, definingFibElement ){
	DEBUG_OUT_L3(<<this<<"->cVectorChecksum("<<&vector<<", "<<definingFibElement<<") copyconstructor"<<endl);
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
cVectorChecksum::cVectorChecksum( const TiXmlElement * pXmlElement, intFib &outStatus,
		list<cFibVariable*> & liDefinedVariables ):
		cVectorProperty( pXmlElement, outStatus, liDefinedVariables ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorChecksum() constructor restore xml"<<endl);
	
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
	}else if ( strncmp( "property.checksum", szVectorXmlType, 17 ) != 0 ){
		outStatus = 2;
		return;
	}
}


/**
 * This method clones this object.
 *
 * @return a pointer to the clone of this object
 */
cVectorChecksum * cVectorChecksum::clone() const{
	
	return new cVectorChecksum( *this );
}


/**
 * This method creates an instance of this vector type.
 *
 * @param definingPropertyElement the Fib -propertyelement which
 * 	defines/ uses the propertyvector
 */
cVectorChecksum * cVectorChecksum::createInstance(
		cFibElement *pDefiningElement ) const{

	DEBUG_OUT_L3(<<this<<"->cVectorChecksum::createInstance("<<pDefiningElement<<")"<<endl);
	
	return new cVectorChecksum( pDefiningElement );
}



/**
 * Sets the variable of the iNumberElement'te vectorelement.
 *
 * @param iNumberElement the number of the element, where the variable is
 * 	to set
 * @param pVariable the variable to set
 * @return true if the iNumberElement'te vectorelement is set to the
 * 	given variable pVariable, else false
 */
bool cVectorChecksum::setVariable( unsignedIntFib iNumberElement,
		cFibVariable *pVariable ){
	
	DEBUG_OUT_L3(<<this<<"->cVectorChecksum::setVariable("<<iNumberElement<<","<<pVariable<<")"<<endl);
	
	//an checksum element can't be a variable
	return false;
}


/**
 * This Method makes this vectorelements equal to the correspondending
 * vectorelements of the given vector.
 * The type of the vector and the number of elements won't be changed.
 *
 * @param vector the vector to copy
 */
cVectorChecksum & cVectorChecksum::operator=( const cFibVector &vector ){
	DEBUG_OUT_L3(<<this<<"->cVectorChecksum::operator=( "<<&vector<<" )"<<endl);
	
	for ( unsigned int uiActualElement = 1;
			uiActualElement <= getNumberOfElements(); uiActualElement++ ){
		
		if ( vector.isVariable( uiActualElement ) ){
			setValue( uiActualElement,
				((const_cast<cFibVector*>(&vector))->getVariable( uiActualElement ))->getValue() );
		}else{
			setValue( uiActualElement, vector.getValue( uiActualElement ) );
		}
	}
	return (*this);
}
