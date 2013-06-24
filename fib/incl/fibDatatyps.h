/**
 * @file fibDatatyps
 * file name: fibDatatyps.h
 * @author Betti Oesterholz
 * @date 17.04.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies the primitiv datatyps for fib.
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
 * This file contains the basic datatyps for fib.
 * The main reason for Fib specific datatyps is: that the Fib datatyps
 * can be changed easily with this file.
 *
 * The basic datatyps for Fib are defined as the basic datatyps of C++.
 *
 */
/*
History:
17.04.2009  Oesterholz  created
16.01.2011  Oesterholz  functions isEqualNull(), compareDouble() and
	compareVectorDouble() added
22.01.2011  Oesterholz  functions add(), sub(), addToFirst() and
	subFromFirst() added
13.10.2011  Oesterholz  functions getListElement() added
13.10.2011  Oesterholz  min() function replaced
11.05.2013  Oesterholz  function composeDoubleFib() added
*/


#ifndef ___FIB_DATATYPS_H__
#define ___FIB_DATATYPS_H__


#include "version.h"

#include <cstdlib>
#include <vector>
#include <list>


//#define REALLY_SMALL_DOUBLE_DIFFERENCE 0.000000000001
#define REALLY_SMALL_DOUBLE_DIFFERENCE 0.0000000000001
#define REALLY_SMALL_FLOAT_DIFFERENCE 0.000001



#define intFib          int
#define longFib         long long
#define doubleFib       double
#define unsignedIntFib  unsigned int
#define unsignedLongFib unsigned long long

namespace fib{

	/**
	 * This function rounds an double value to an longFib value.
	 *
	 * @param value the value to round
	 * @return the rounded value
	 */
	template <class Type> longFib roundToLongFib( const Type &value ){

		if( 0 <= value){
			return (longFib) (value + 0.5);
		}else{
			return (longFib) (value - 0.5);
		}
	}
	
	/**
	 * This function evalues the maximum of two values.
	 *
	 * @param value1 the first value
	 * @param value2 the second value
	 * @return the maximum of the first and the second value
	 */
	template <class Type> Type max( const Type &value1, const Type &value2 ){

		if( value1 < value2 ){
			return value2;
		}else{
			return value1;
		}
	}

	/**
	 * This returns the ulElementNumber'th element from an given list.
	 *
	 * @param liList the list from wher to return the list iterator
	 * @param ulElementNumber the number of the list element to return
	 * @return an iterator to the ulElementNumber'th list element
	 */
	template <class Type> typename std::list< Type >::iterator getListElement(
			std::list< Type > & liList, unsigned long ulElementNumber ){

		if ( ( ulElementNumber < 1 ) || ( liList.size() < ulElementNumber ) ){
			return liList.end();
		}
		typename std::list< Type >::iterator itrList = liList.begin();
		for ( ; 1 < ulElementNumber; ulElementNumber--, itrList++ ){
			//nothing to do
		}
		return itrList;
	}


	/**
	 * This returns the ulElementNumber'th element from an given list.
	 *
	 * @param liList the list from wher to return the list iterator
	 * @param ulElementNumber the number of the list element to return
	 * @return an iterator to the ulElementNumber'th list element
	 */
	template <class Type> typename std::list< Type >::const_iterator getListElement(
			const std::list< Type > & liList, unsigned long ulElementNumber ){

		if ( ( ulElementNumber < 1 ) || ( liList.size() < ulElementNumber ) ){
			return liList.end();
		}
		typename std::list< Type >::const_iterator itrList = liList.begin();
		for ( ; 1 < ulElementNumber; ulElementNumber--, itrList++ ){
			//nothing to do
		}
		return itrList;
	}


	/**
	 * This function evalues the digits needed to store a value as a
	 * natural number.
	 *
	 * @param uiValue the value to evalue the digits for
	 * @return the digits needed to store a value as a natural number
	 */
	unsigned int getDigits( unsigned int uiValue );

	/**
	 * This function evalues the digits needed to store a value as a
	 * natural number.
	 *
	 * @param ulValue the value to evalue the digits for
	 * @return the digits needed to store a value as a natural number
	 */
	unsigned int getDigits( unsigned long ulValue );
	
	/**
	 * This function evalues the digits needed to store a value as a
	 * natural number.
	 *
	 * @param llValue the value to evalue the digits for
	 * @return the digits needed to store a value as a natural number
	 */
	unsigned int getDigits( unsigned long long llValue );

	/**
	 * This function evalues the digits needed to store a value as an
	 * integer number (including 1 bit for the sign).
	 *
	 * @param iValue the value to evalue the digits for
	 * @return the digits needed to store a value as an integer number
	 */
	unsigned int getDigits( int iValue );

	/**
	 * This function evalues the digits needed to store a value as an
	 * integer number (including 1 bit for the sign).
	 *
	 * @param llValue the value to evalue the digits for
	 * @return the digits needed to store a value as an integer number
	 */
	unsigned int getDigits( long llValue );
	
	/**
	 * This function evalues the digits needed to store a value as an
	 * integer number (including 1 bit for the sign).
	 *
	 * @param llValue the value to evalue the digits for
	 * @return the digits needed to store a value as an integer number
	 */
	unsigned int getDigits( long long llValue );


	/**
	 * Decomposes a double number into it's mantissa and exponent part.
	 *
	 * @param dNumber the number to decompose
	 * @param lMantissa a pointer to the longFib field wher the mantissa
	 * 	should be stored
	 * @param lExponent a pointer to the longFib field wher the exponent
	 * 	should be stored
	 * @param iSizeMantissa a pointer to the intFib field wher the size of
	 * 	the mantissa in bits should be stored or NULL if it shouldn't be
	 * 	stored
	 * @param iSizeExponent a pointer to the intFib field wher the size of
	 * 	the exponent in bits should be stored or NULL if it shouldn't be
	 * 	stored
	 */
	void decomposeDoubleFib( const double dNumber,
		longFib * lMantissa, longFib * lExponent,
		intFib * iSizeMantissa = NULL, intFib * iSizeExponent = NULL );
	
	/**
	 * Composes a double number into it's mantissa and exponent part.
	 * It's the invers of: @see decomposeDoubleFib()
	 * Basicly it evalues: lMantissa * 2^lExponent
	 *
	 * @param lMantissa the mantissa of the number
	 * @param lExponent the exponent of the number
	 * @return lMantissa * 2^lExponent
	 */
	double composeDoubleFib(
		const longFib & lMantissa, const longFib & lExponent );
	
	/**
	 * This function rounds the given number of bits ulNumberOfBits up
	 * to a full number of byte;
	 *
	 * @param ulNumberOfBits the number of bits to round
	 * @return the, to full byte rounded up, number of bits
	 */
	unsigned long roundUpToFullByte( unsigned long ulNumberOfBits );
	
	/**
	 * This function evalues the greatest common divisor of the two given
	 * numbers.
	 *
	 * @param dValue1 the first number
	 * @param dValue2 the second number
	 * @return the greatest common divisor of the two given numbers dValue1
	 * 	and dValue2
	 */
	doubleFib gcd( doubleFib dValue1, doubleFib dValue2 );

	/**
	 * @param dValue the value, for which to evalue the positiv value
	 * @return the positive value for the given number dValue
	 */
	float absF( const float & dValue );
	
	/**
	 * @param dValue the value, for which to evalue the positiv value
	 * @return the positive value for the given number dValue
	 */
	double absF( const double & dValue );
	
	/**
	 * This functions checks if the given double number is equal 0.
	 * Really small differences will be ignored.
	 *
	 * @param dValue the number to check
	 * @return true if the given number is equal 0, else false
	 */
	bool isEqualNull( const double & dValue );

	/**
	 * This functions checks if the given float number is equal 0.
	 * Really small differences will be ignored.
	 *
	 * @param dValue the number to check
	 * @return true if the given number is equal 0, else false
	 */
	bool isEqualNull( const float & dValue );

	/**
	 * This functions compares two double numbers.
	 * Really small differences will be ignored.
	 *
	 * @param dValue1 the first number to compare
	 * @param dValue2 the second number to compare
	 * @return true if the first number is equal to the second, else false
	 */
	bool compareDouble( const double & dValue1, const double & dValue2 );
	
	/**
	 * This functions compares two float numbers.
	 * Really small differences will be ignored.
	 *
	 * @param dValue1 the first number to compare
	 * @param dValue2 the second number to compare
	 * @return true if the first number is equal to the second, else false
	 */
	bool compareDouble( const float & dValue1, const float & dValue2 );
	
	
	/**
	 * This functions compares two vectors with double numbers.
	 * Really small differences betwean the vector element numbers will be ignored.
	 *
	 * @param vector1 the first vector to compare
	 * @param vector2 the second vector to compare
	 * @return true if the first vector is equal to the second, else false
	 */
	template<class tDouble>
	bool compareVectorDouble( const std::vector< tDouble > & vector1,
			const std::vector< tDouble > & vector2 ){
		
		if ( vector1.size() != vector2.size() ){
			//not the same number of elements -> vectors not equal
			return false;
		}
		const size_t uiNumberOfElements = vector1.size();
		
		for ( size_t uiActualElement = 0; uiActualElement < uiNumberOfElements;
				uiActualElement++ ){
			
			if ( ! fib::compareDouble( vector1[ uiActualElement ], vector2[ uiActualElement ] ) ){
				//actual vector element not equal -> vectors not equal
				return false;
			}
		}//else all vector elements equal
		return true;
	}
	
	
	/**
	 * This functions adds two floating point numbers.
	 * Really small differences will be ignored, this means:
	 * If one number is allmost equal to the negativ of the other the result is 0.
	 *
	 * @param dValue1 the first number to add
	 * @param dValue2 the second number to add
	 * @return the sum of the two given values
	 */
	template<class tDouble>
	tDouble add( const tDouble & dValue1, const tDouble & dValue2 ){
	
		if ( compareDouble( dValue1, ((tDouble)(-1)) * dValue2 ) ){
			//the sum is 0
			return ((tDouble)(0));
		}//else
		return dValue1 + dValue2;
	}
	
	
	/**
	 * This functions subtracts two floating point numbers.
	 * Really small differences will be ignored, this means:
	 * If one number is allmost equal to the other the result is 0.
	 *
	 * @param dValue1 the minuend of the subtraction
	 * @param dValue2 the subtrahend of the subtraction
	 * @return the difference of the two given values
	 */
	template<class tDouble>
	tDouble sub( const tDouble & dValue1, const tDouble & dValue2 ){
	
		if ( compareDouble( dValue1, dValue2 ) ){
			//the sum is 0
			return ((tDouble)(0));
		}//else
		return dValue1 - dValue2;
	}
	
	
	/**
	 * This functions adds two floating point numbers.
	 * Really small differences will be ignored, this means:
	 * If one number is allmost equal to the negativ of the other the result is 0.
	 *
	 * @param dValue1 the first number to add, the sum will also be stored
	 * 	in this variable
	 * @param dValue2 the second number to add
	 * @return the sum of the two given values
	 */
	template<class tDouble>
	tDouble addToFirst( tDouble & dValue1, const tDouble & dValue2 ){
	
		if ( compareDouble( dValue1, ((tDouble)(-1)) * dValue2 ) ){
			//the sum is 0
			dValue1 = ((tDouble)(0));
			return ((tDouble)(0));
		}//else
		dValue1 += dValue2;
		return dValue1;
	}
	
	
	/**
	 * This functions subtracts two floating point numbers.
	 * Really small differences will be ignored, this means:
	 * If one number is allmost equal to the other the result is 0.
	 *
	 * @param dValue1 the minuend of the subtraction, the difference will
	 * 	also be stored in this variable
	 * @param dValue2 the subtrahend of the subtraction
	 * @return the difference of the two given values
	 */
	template<class tDouble>
	tDouble subFromFirst( tDouble & dValue1, const tDouble & dValue2 ){
	
		if ( compareDouble( dValue1, dValue2 ) ){
			//the sum is 0
			dValue1 = ((tDouble)(0));
			return ((tDouble)(0));
		}//else
		dValue1 -= dValue2;
		return dValue1;
	}


	/**
	 * This functions adds two floating point number vectors.
	 * Really small differences will be ignored, this means:
	 * If one number is allmost equal to the negativ of the other the result is 0.
	 *
	 * @param vecValue1 the first vector to add, the sum will also be stored
	 * 	in this variable
	 * @param vecValue2 the second vector to add
	 * @return the sum of the two given vectors
	 */
	template<class tDouble>
	std::vector< tDouble > addToFirst( std::vector< tDouble > & vecValue1,
		const std::vector< tDouble > & vecValue2 ){
	
		/*const size_t uiNumberOfElements = min(
			vecValue1.size(), vecValue2.size() );*/
		const size_t uiVecValue1Size = vecValue1.size();
		const size_t uiVecValue2Size = vecValue2.size();
		const size_t uiNumberOfElements = ( uiVecValue1Size < uiVecValue2Size )?
			uiVecValue1Size : uiVecValue2Size ;
		
		for ( size_t uiActualElement = 0; uiActualElement < uiNumberOfElements;
				uiActualElement++ ){
			
			addToFirst( vecValue1[ uiActualElement ], vecValue2[ uiActualElement ] );
		}
		return vecValue1;
	}

	/**
	 * This functions multiplys a floating point number vector with a number.
	 *
	 * @param vecValue the vector to multiply with the number, the product
	 * 	will also be stored in this variable
	 * @param dValue the value to multiply the vector with
	 * @return the product of the given vector and the value
	 */
	template<class tDouble>
	std::vector< tDouble > multToFirst( std::vector< tDouble > & vecValue,
		const tDouble & dValue ){
	
		const size_t uiNumberOfElements = vecValue.size();
		
		for ( size_t uiActualElement = 0; uiActualElement < uiNumberOfElements;
				uiActualElement++ ){
			
			vecValue[ uiActualElement ] *= dValue;
		}
		return vecValue;
	}


}//end namespace fib


#endif //___FIB_DATATYPS_H__









