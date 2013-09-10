/**
 * @class cFunctionValue
 * file name: cFunctionValue.cpp
 * @author Betti Oesterholz
 * @date 23.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a value underfunction.
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
 * This class represents a value underfunction.
 * Value underfunction store a fixted /constant value.
 *
 */
/*
History:
23.04.2010  Oesterholz  created
30.09.2010  Oesterholz  xml storing and restoring full rational number
30.04.2011  Oesterholz  scanf long for 64 bit and windows
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
30.08.2013  Oesterholz  debugging information added (restore XML)
03.09.2013  Oesterholz  using readDoubleFromFunction() and storeXmlDoubleFib()
	for storing and restoring Fib double numbers in XML
*/


#include "cFunctionValue.h"

#include <cmath>


using namespace fib;


/**
 * The constructor of the underfunction.
 *
 * @param dInValue the value of this underfunction
 * @param pInSuperiorFunction the underfunction which contains the
 * 	new underfunction
 * @param pInDefiningFibElement the fib -element which defines/ uses
 * 	the new underfunction
 */
cFunctionValue::cFunctionValue( doubleFib dInValue,
		cUnderFunction * pInSuperiorFunction,
		cFibElement * pInDefiningFibElement ):
		cUnderFunction( pInSuperiorFunction, pInDefiningFibElement ),
		dValue( dInValue ){
	//nothing to do
}


/**
 * The copy constructor of the underfunction.
 *
 * @param underfunction the underfunction which to copy
 * @param pInSuperiorFunction the underfunction which contains the
 * 	new underfunction
 * @param pInDefiningFibElement the fib -element which defines/ uses
 * 	the new underfunction
 */
cFunctionValue::cFunctionValue( const cFunctionValue & underfunction,
		cUnderFunction * pInSuperiorFunction,
		cFibElement *pInDefiningFibElement ):
		cUnderFunction( underfunction, pInSuperiorFunction, pInDefiningFibElement ),
		dValue( underfunction.dValue ){
	//nothing to do
}


/**
 * The constructor for restoring a value underfunction from an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node the underfunction is stored in
 * @param outStatus An reference to an integervalue where the errorvalue
 * 	can be stored to.
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 * @param pInSuperiorFunction the underfunction which contains the
 * 	new underfunction
 * @param pInDefiningFibElement the fib -element which defines/ uses
 * 	the new underfunction
 */
cFunctionValue::cFunctionValue( const TiXmlElement * pXmlElement, intFib & outStatus,
		cUnderFunction * pInSuperiorFunction,
		cFibElement *pInDefiningFibElement ):
		cUnderFunction( pInSuperiorFunction, pInDefiningFibElement ),
		dValue( 0.0 ){
	
#ifdef DEBUG_RESTORE_XML
	printf( "   cFunctionValue::cFunctionValue() restore xml started\n" );
#endif //DEBUG_RESTORE_XML
	
	//check the vector type
	if ( pXmlElement == NULL ){
		//noting to restore
		outStatus = -1;
		return;
	}
	string szElementType( pXmlElement->Value() );
	if ( szElementType != "value" ){
		//wrong element type to restore
		outStatus = -2;
		return;
	}
	//read the value
	const char * pcValue = pXmlElement->GetText();
	//converting value to double
	std::pair< bool, const char * > pairOutEvalueStatus;
	dValue = readDoubleFromFunction( pcValue, &pairOutEvalueStatus );
	
	if ( ! pairOutEvalueStatus.second ){
		//Warning: Error while reading the number
		outStatus = 2;
	}
#ifdef DEBUG_RESTORE_XML
	const double dRestoredValue = dValue;
	printf( "   cFunctionValue::cFunctionValue() restored value: %lf (%s)\n", dRestoredValue, pcValue );
#endif //DEBUG_RESTORE_XML
}


/**
 * This constructor restores a value underfunction from the stream
 * where it is stored in the compressed fib -format.
 * Beware: The bits for the functiontype should be allready readed, this
 * 	constructor reads yust the two underfunctions.
 *
 * @param iBitStream the stream where this underfunction is stored to in,
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
 * @param pInValueDomain the domain for value underfunctions
 * @param pInSuperiorFunction the underfunction which contains the
 * 	new underfunction
 * @param pInDefiningFibElement the fib -element which defines/ uses
 * 	the new underfunction
 */
cFunctionValue::cFunctionValue( cReadBits & iBitStream, intFib & outStatus,
		const cDomainSingle * pInValueDomain,
		cUnderFunction * pInSuperiorFunction, cFibElement * pInDefiningFibElement ):
		cUnderFunction( pInSuperiorFunction, pInDefiningFibElement ),
		dValue( 0.0 ){
	
	DEBUG_OUT_L3(<<this<<"->cFunctionValue() restore bit"<<endl);
	
	//check the stream type
	if ( ! iBitStream.getStream()->good() ){
		outStatus = -1;
		DEBUG_OUT_EL3(<<"Error: stream not good"<<endl);
		return;
	}
	if ( pInValueDomain == NULL ){
		outStatus = -2;
		DEBUG_OUT_EL3(<<"Error: no valid value domain"<<endl);
		return;
	}
	//restore the value of the valueunderfunction
	dValue = pInValueDomain->restoreValue( iBitStream, outStatus );
	if ( outStatus < 0 ){
		DEBUG_OUT_EL3(<<"Error: couldn't load value"<<endl);
		return;
	}
	
	DEBUG_OUT_L3(<<this<<"->cFunctionValue() restore bit done"<<endl);
}


/**
 * The destructor of the underfunction.
 */
cFunctionValue::~cFunctionValue(){
	//nothing to do
}


/**
 * This method returns if this underfunction is valid, else false.
 * All values in the underfunction and it's underfunctions must be
 * inside the underfunction domain. All variables must be defined over
 * this underfunction.
 * No underfunction should contain itselfor should be contained in one
 * of its underfunctions (no cycles allowed).
 *
 * @return true if this underfunction is valid, else false
 */
bool cFunctionValue::isValid() const{
	
	cDomainSingle * domain = getDomain();
	if ( domain != NULL ){
		
		return domain->isElement( dValue );
	}
	return false;
}


/**
 * This method checks if the given variable is used in this underfunction.
 *
 * @see cFibVariable
 * @param variable the variable to check if it is used
 * @return true if the variable is used, else false
 */
bool cFunctionValue::isUsedVariable( const cFibVariable * variable ) const{
	
	return false;
}


/**
 * This method returns all variables used in this underfunction.
 *
 * @see cFibVariable
 * @return all variables used in this underfunction
 */
set<cFibVariable*> cFunctionValue::getUsedVariables(){
	
	return set<cFibVariable*>();
}


/**
 * This method replace the variable variableOld with the variable
 * variableNew in the underfunction.
 *
 * @see cFibVariable
 * @see isVariable()
 * @see isUsedVariable()
 * @param variableOld the variable to replace
 * @param variableNew the variable with which the variable variableOld
 * 	is to replace
 * @return true if the variable variableOld is replaced with variableNew,
 * 	else false
 */
bool cFunctionValue::replaceVariable( cFibVariable *variableOld,
		cFibVariable *variableNew ){
	
	if ( (variableOld == NULL) || (variableNew == NULL) ){
		return false;
	}
	return true;
}

/**
 * Returns the value of the underfunction or 0 if non such exists.
 *
 * @return the value of the underfunction or 0 if non
 * 	such exists
 */
doubleFib cFunctionValue::getValue() const{
	
	return dValue;
}


/**
 * @return the number of underfunctions, a underfunction of this type has
 */
unsignedIntFib cFunctionValue::getNumberOfUnderFunctions() const{

	return 0;
}


/**
 * Sets the Fib -element which defines/ uses this underfunction.
 * If the given pointer is the nullpointer (standardvalue), no
 * Fib -element defines this underfunction.
 *
 * @param definingFibElement a pointer to the Fib -element which
 * 	defines/ uses this underfunction
 * @param bCheckDomains getthe domains of the defining element and
 * 	check the underfunctionelements with it
 */
void cFunctionValue::setDefiningFibElement( cFibElement *fibElement,
		bool bCheckDomains ){

	DEBUG_OUT_L3(<<this<<"->cFunctionValue::setDefiningFibElement( "<< fibElement <<", "<<bCheckDomains<<" )"<<endl);
	
	cUnderFunction::setDefiningFibElement( fibElement, bCheckDomains );
	if ( bCheckDomains && pDefiningFibElement ){
		/*if ther is a new defining element, try to use the domain of the
		defining element for the vector*/
		cDomainSingle * domain = getDomain();
		if ( domain != NULL ){
			
			dValue = domain->round( dValue );
		}
	}
}


/**
 * This method evaluades a value for the time needed to evalue the
 * underfunction.
 * This value should not exceed lMaxTime, if the value for the time
 * is greater than lMaxTime the evaluation will be stopt and lMaxTime
 * returned. If lMaxTime is 0 (for infinity) the evaluation won't be
 * stoped, this is the standard case.
 *
 * @see cFibElement::evalueObject()
 * @param lMaxTime the maximum time for the evaluation, the returned
 * 	exceed this value; the value 0 stands for infinity, so the
 * 	evaluation won't be stoped
 * @return a value for the time needed to evalue this underfunction
 */
unsignedLongFib cFunctionValue::getTimeNeed( unsignedLongFib lMaxTime ) const{

	return 1;
}


/**
 * This method evaluades the size of the Fib -object in bits in the
 * compressed file form.
 * The optionalpart field of point -elements will be ignored.
 *
 * @see store()
 * @return the size of the Fib -object in bits in the compressed form
 */
unsignedLongFib cFunctionValue::getCompressedSize() const{
	
	DEBUG_OUT_L3(<<this<<"->cFunctionValue::getCompressedSize()"<<endl);
	
	unsignedLongFib ulCompressedSize = 2;//prefix
	
	//get the domain for the values in this vector
	cDomainSingle * pValueDomain = getValueDomain();
	
	bool bStandardValueDomain = false;
	if ( pValueDomain == NULL ){
		bStandardValueDomain = true;
		pValueDomain = getStandardDomain();
	}
	//add the compressed size for the value
	ulCompressedSize += pValueDomain->getCompressedSizeForValue();

	if ( bStandardValueDomain ){
		delete pValueDomain;
	}

	return ulCompressedSize;
}


/**
 * This method stores this Fib -object in the compressed Fib -format
 * into the given stream.
 * It is needed becouse the stream can yust store byts but the size of
 * fib -elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the fib -elements.
 *
 * @see store
 * @param stream the stream where this Fib -object should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if this Fib -object is stored, else false
 */
bool cFunctionValue::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	DEBUG_OUT_L3(<<this<<"->cFunctionValue::store()"<<endl);
	
	//get the domain for the values in this vector
	cDomainSingle * pValueDomain = getValueDomain();
	
	bool bStandardValueDomain = false;
	if ( pValueDomain == NULL ){
		bStandardValueDomain = true;
		pValueDomain = getStandardDomain();
	}

	//write the bits for the prefix 00
	const char cTypeBit = 0x00;
	bool bReturnValue = nBitStream::store( stream, cRestBits, uiRestBitPosition,
		&cTypeBit, 2 );
	//write the bits for the value
	bReturnValue &= pValueDomain->storeValue( getValue(), stream, cRestBits,
		uiRestBitPosition );
	
	if ( bStandardValueDomain ){
		delete pValueDomain;
	}
	return bReturnValue;
}


/**
 * This method stores this underfunction in the XML -format into the
 * given stream.
 * Variables should have ther number as ther value.
 *
 * @param stream the stream where this underfunction should be
 * 	stored to
 * @return true if this underfunction is stored, else false
 */
bool cFunctionValue::storeXml( ostream & stream ) const{
	
	DEBUG_OUT_L3(<<this<<"->cFunctionValue::storeXml()"<<endl);
	
	//store the unserfunction
	stream<<"<value>";
	storeXmlDoubleFib( stream, getValue() );
	stream<<"</value>"<<endl;

	return true;
}


/**
 * @return the type for the underfunction
 */
unsignedIntFib cFunctionValue::getType() const{

	return FUNCTION_VALUE;
}

/**
 * @return the name for the underfunction
 */
string cFunctionValue::getUnderFunctionName() const{
	
	return "value";
}


#ifdef FEATURE_EQUAL_FIB_OBJECT

/**
 * This method checks if the given underfunction is equal to this underfunction.
 * Variables can be others, but must be defined and used in equivalent
 * Fib-elements.
 *
 * @param underfunction the underfunction to compare with this underfunction
 * @param mapEqualRootObjects the root objects of this object that wher
 * 	already checked as equal
 * 	map entries:
 * 		key: the root-element of this Fib object that was checked
 * 		value: the to the key correspondending root-element of the
 * 			fibObject that was checked and which is equal to the key
 * 		root-element
 * 	(it is empty if bCheckExternalObjects == false)
 * @param mapEqualDefinedVariables the Fib elements that defines
 * 	variables and are equal;
 * 	map entries:
 * 		key: the Fib element of this Fib object that was checked
 * 		value: the to the key correspondending Fib element of the
 * 			fibObject that was checked and which sets its defined
 * 			variables to the same values as the key Fib element
 * @param bCheckExternalObjects if true the external objects of
 * 	cExtObject will be compared
 * @return true if this Fib-object is equal to the given Fib-object,
 * 	else false
 */
bool cFunctionValue::equalInternal( const cUnderFunction & underfunction,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{
	
	if ( & underfunction == NULL ){
		return false;
	}
	if ( getType() != underfunction.getType() ){
		return false;
	}
	return ( getValue() == underfunction.getValue() );
}

#else //FEATURE_EQUAL_FIB_OBJECT

/**
 * This Method checks if the given underfunction is equal to this underfunction.
 *
 * @param underfunction the underfunction to compare with this underfunction
 * @return true if the given underfunction is equal to this underfunction, else false
 */
bool cFunctionValue::equal( const cUnderFunction & underfunction ) const{
	
	if ( & underfunction == NULL ){
		return false;
	}
	if ( getType() != underfunction.getType() ){
		return false;
	}
	return ( getValue() == underfunction.getValue() );
}

#endif //FEATURE_EQUAL_FIB_OBJECT

/**
 * This method duplicates this whole underfunction.
 * Underfunctions of this underfunction are also cloned.
 *
 * @param pSuperiorUnderFunction the underfunction which contains
 * @param pInDefiningFibElement the Fib -element which defines/ uses
 * @return the cloned/ duplicated underfunction
 */
cUnderFunction * cFunctionValue::clone(
		cUnderFunction * pInSuperiorUnderFunction,
		cFibElement *pInDefiningFibElement) const{
	
	return new cFunctionValue( *this, pInSuperiorUnderFunction,
		pInDefiningFibElement );
}




