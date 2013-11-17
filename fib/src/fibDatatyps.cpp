/**
 * @file fibDatatyps
 * file name: fibDatatyps.cpp
 * @author Betti Oesterholz
 * @date 24.09.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains some functions for the fib datatyps.
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
 * This file contains some functions for the fib datatyps.
 *
 */
/*
History:
24.09.2009  Oesterholz  created
16.01.2011  Oesterholz  functions isEqualNull() added
11.05.2013  Oesterholz  function composeDoubleFib() added
31.08.2013  Oesterholz  function readDouble() and readDoubleFromFunction() added
*/

#include "fibDatatyps.h"

#include <cmath>
#include <list>


using namespace fib;
using namespace std;


/**
 * This function evalues the digits needed to store a value as a
 * natural number.
 *
 * @param uiValue the value to evalue the digits for
 * @return the digits needed to store a value as a natural number
 */
unsigned int fib::getDigits( unsigned int uiValue ){

	if ( uiValue == 0 ){
		//no digits needed to store value
		return 0;
	}
	
	unsigned int uiDigits = 0;
	
	static const unsigned int BITS_OF_UNSIGNED_INT = sizeof( unsigned int ) * 8;
	for ( unsigned int iActualDigit = 1; iActualDigit <= BITS_OF_UNSIGNED_INT;
			iActualDigit += 4 ){
			
		if ( (uiValue & 0x08) != 0 ){
			//digit found
			uiDigits = iActualDigit + 3;
		}else if ( (uiValue & 0x04) != 0 ){
			//digit found
			uiDigits = iActualDigit + 2;
		}else if ( (uiValue & 0x02) != 0 ){
			//digit found
			uiDigits = iActualDigit + 1;
		}else if ( (uiValue & 0x01) != 0 ){
			//digit found
			uiDigits = iActualDigit;
		}
		uiValue = uiValue >> 4;
		
		if ( uiValue == 0 ){
			//no more digits
			break;
		}
	}
	return uiDigits;
}


/**
 * This function evalues the digits needed to store a value as a
 * natural number.
 *
 * @param ulValue the value to evalue the digits for
 * @return the digits needed to store a value as a natural number
 */
unsigned int fib::getDigits( unsigned long ulValue ){

	if ( ulValue == 0 ){
		//no digits needed to store value
		return 0;
	}
	
	unsigned int uiDigits = 0;
	
	static const unsigned int BITS_OF_UNSIGNED_LONG =
		sizeof( unsigned long ) * 8;
	for ( unsigned int iActualDigit = 1; iActualDigit <= BITS_OF_UNSIGNED_LONG;
			iActualDigit += 4 ){
			
		if ( (ulValue & 0x08) != 0 ){
			//digit found
			uiDigits = iActualDigit + 3;
		}else if ( (ulValue & 0x04) != 0 ){
			//digit found
			uiDigits = iActualDigit + 2;
		}else if ( (ulValue & 0x02) != 0 ){
			//digit found
			uiDigits = iActualDigit + 1;
		}else if ( (ulValue & 0x01) != 0 ){
			//digit found
			uiDigits = iActualDigit;
		}
		ulValue = ulValue >> 4;
		
		if ( ulValue == 0 ){
			//no more digits
			break;
		}
	}
	return uiDigits;
}


/**
 * This function evalues the digits needed to store a value as a
 * natural number.
 *
 * @param llValue the value to evalue the digits for
 * @return the digits needed to store a value as a natural number
 */
unsigned int fib::getDigits( unsigned long long llValue ){

	if ( llValue == 0 ){
		//no digits needed to store value
		return 0;
	}
	
	unsigned int uiDigits = 0;
	
	static const unsigned int BITS_OF_UNSIGNED_LONG_LONG =
		sizeof( unsigned long long ) * 8;
	for ( unsigned int iActualDigit = 1; iActualDigit <= BITS_OF_UNSIGNED_LONG_LONG;
			iActualDigit += 4 ){
			
		if ( (llValue & 0x08) != 0 ){
			//digit found
			uiDigits = iActualDigit + 3;
		}else if ( (llValue & 0x04) != 0 ){
			//digit found
			uiDigits = iActualDigit + 2;
		}else if ( (llValue & 0x02) != 0 ){
			//digit found
			uiDigits = iActualDigit + 1;
		}else if ( (llValue & 0x01) != 0 ){
			//digit found
			uiDigits = iActualDigit;
		}
		
		llValue = llValue >> 4;
		
		if ( llValue == 0 ){
			//no more digits
			break;
		}
	}
	return uiDigits;
}


/**
 * This function evalues the digits needed to store a value as an
 * integer number (including 1 bit for the sign).
 *
 * @param iValue the value to evalue the digits for
 * @return the digits needed to store a value as an integer number
 */
unsigned int fib::getDigits( int iValue ){

	if ( iValue == 0 ){
		//no digits needed to store value
		return 0;
	}
	unsigned int uiDigits = 0;
	
	static const unsigned int BITS_OF_INT = sizeof( int ) * 8;
	if ( 0 <= iValue ){
		//number is positiv -> search for last 1 bit
		for ( unsigned int iActualDigit = 1; iActualDigit <= BITS_OF_INT;
				iActualDigit += 4 ){
				
			if ( (iValue & 0x08) != 0 ){
				//digit found
				uiDigits = iActualDigit + 3;
			}else if ( (iValue & 0x04) != 0 ){
				//digit found
				uiDigits = iActualDigit + 2;
			}else if ( (iValue & 0x02) != 0 ){
				//digit found
				uiDigits = iActualDigit + 1;
			}else if ( (iValue & 0x01) != 0 ){
				//digit found
				uiDigits = iActualDigit;
			}
			
			iValue = iValue >> 4;
			
			if ( iValue == 0 ){
				//no more digits
				break;
			}
		}
	}else{//number is negativ -> search for last 0 bit
		for ( unsigned int iActualDigit = 1; iActualDigit <= BITS_OF_INT;
				iActualDigit += 4 ){
				
			if ( (iValue & 0x08) == 0 ){
				//digit found
				uiDigits = iActualDigit + 3;
			}else if ( (iValue & 0x04) == 0 ){
				//digit found
				uiDigits = iActualDigit + 2;
			}else if ( (iValue & 0x02) == 0 ){
				//digit found
				uiDigits = iActualDigit + 1;
			}else if ( (iValue & 0x01) == 0 ){
				//digit found
				uiDigits = iActualDigit;
			}
			
			iValue = iValue >> 4;
			
			if ( iValue == -1 ){
				//no more digits
				break;
			}
		}
	}
	//add digit for sign
	return uiDigits + 1;
}


/**
 * This function evalues the digits needed to store a value as an
 * integer number (including 1 bit for the sign).
 *
 * @param lValue the value to evalue the digits for
 * @return the digits needed to store a value as an integer number
 */
unsigned int fib::getDigits( long lValue ){

	if ( lValue == 0 ){
		//no digits needed to store value
		return 0;
	}
	unsigned int uiDigits = 0;
	
	static const unsigned int BITS_OF_LONG = sizeof( long ) * 8;
	if ( 0 <= lValue ){
		//number is positiv -> search for last 1 bit
		for ( unsigned int iActualDigit = 1; iActualDigit <= BITS_OF_LONG;
				iActualDigit += 4 ){
				
			if ( (lValue & 0x08) != 0 ){
				//digit found
				uiDigits = iActualDigit + 3;
			}else if ( (lValue & 0x04) != 0 ){
				//digit found
				uiDigits = iActualDigit + 2;
			}else if ( (lValue & 0x02) != 0 ){
				//digit found
				uiDigits = iActualDigit + 1;
			}else if ( (lValue & 0x01) != 0 ){
				//digit found
				uiDigits = iActualDigit;
			}
			
			lValue = lValue >> 4;
			
			if ( lValue == 0 ){
				//no more digits
				break;
			}
		}
	}else{//number is negativ -> search for last 0 bit
		for ( unsigned int iActualDigit = 1; iActualDigit <= BITS_OF_LONG;
				iActualDigit += 4 ){
				
			if ( (lValue & 0x08) == 0 ){
				//digit found
				uiDigits = iActualDigit + 3;
			}else if ( (lValue & 0x04) == 0 ){
				//digit found
				uiDigits = iActualDigit + 2;
			}else if ( (lValue & 0x02) == 0 ){
				//digit found
				uiDigits = iActualDigit + 1;
			}else if ( (lValue & 0x01) == 0 ){
				//digit found
				uiDigits = iActualDigit;
			}
			
			lValue = lValue >> 4;
			
			if ( lValue == -1 ){
				//no more digits
				break;
			}
		}
	}
	//add digit for sign
	return uiDigits + 1;
}


/**
 * This function evalues the digits needed to store a value as an
 * integer number (including 1 bit for the sign).
 *
 * @param llValue the value to evalue the digits for
 * @return the digits needed to store a value as an integer number
 */
unsigned int fib::getDigits( long long llValue ){

	if ( llValue == 0 ){
		//no digits needed to store value
		return 0;
	}
	unsigned int uiDigits = 0;
	
	static const unsigned int BITS_OF_LONG_LONG = sizeof( long long ) * 8;
	if ( 0 <= llValue ){
		//number is positiv -> search for last 1 bit
		for ( unsigned int iActualDigit = 1; iActualDigit <= BITS_OF_LONG_LONG;
				iActualDigit += 4 ){
				
			if ( (llValue & 0x08) != 0 ){
				//digit found
				uiDigits = iActualDigit + 3;
			}else if ( (llValue & 0x04) != 0 ){
				//digit found
				uiDigits = iActualDigit + 2;
			}else if ( (llValue & 0x02) != 0 ){
				//digit found
				uiDigits = iActualDigit + 1;
			}else if ( (llValue & 0x01) != 0 ){
				//digit found
				uiDigits = iActualDigit;
			}
			
			llValue = llValue >> 4;
			
			if ( llValue == 0 ){
				//no more digits
				break;
			}
		}
	}else{//number is negativ -> search for last 0 bit
		for ( unsigned int iActualDigit = 1; iActualDigit <= BITS_OF_LONG_LONG;
				iActualDigit += 4 ){
				
			if ( (llValue & 0x08) == 0 ){
				//digit found
				uiDigits = iActualDigit + 3;
			}else if ( (llValue & 0x04) == 0 ){
				//digit found
				uiDigits = iActualDigit + 2;
			}else if ( (llValue & 0x02) == 0 ){
				//digit found
				uiDigits = iActualDigit + 1;
			}else if ( (llValue & 0x01) == 0 ){
				//digit found
				uiDigits = iActualDigit;
			}
			
			llValue = llValue >> 4;
			
			if ( llValue == -1 ){
				//no more digits
				break;
			}
		}
	}
	//add digit for sign
	return uiDigits + 1;
}


/**
 * Decompses a double number into it's mantissa and exponent part.
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
void fib::decomposeDoubleFib( const double dNumber,
	longFib * lMantissa, longFib * lExponent,
	intFib * iSizeMantissa , intFib * iSizeExponent ){
	
	if ( ( lMantissa == NULL ) || ( lExponent == NULL ) ){
		//can't store result
		return;
	}
	if ( dNumber == (double)(1.0) ){
		// 1.0 is special (fast) case
		(*lMantissa) = 1;
		(*lExponent) = 0;
		
		if (iSizeMantissa != NULL){
			(*iSizeMantissa) = 2;
		}
		if (iSizeExponent != NULL){
			(*iSizeExponent) = 1;
		}
		return;
	}//else
	
	const long long llNumber = *((const long long*)&dNumber);
	
	//get the sign; (it's the bit 63)
	const bool bSign = ( llNumber < 0);
	//get the exponent; its the bit 52 till 62
	int iExponent = (int) ( 0x7FFL & (llNumber >> 52) );
	//get the matissa; its the bit 0 till 51
	long long llMantissa = 0xFFFFFFFFFFFFFL & llNumber;
	
	if ( iExponent == 0 ){
		/* Subnormal numbers; exponent is effectively one higher,
		but there's no extra normalisation bit in the mantissa*/
		iExponent++;
	}else{/* Normal numbers; leave exponent as it is but add extra
		bit to the front of the mantissa*/
		llMantissa = llMantissa | (1L << 52);
	}
	/* Bias the exponent. It's actually biased by 1023, but we're
	treating the mantissa as m.0 rather than 0.m, so we need
	to subtract another 52 from it.*/
	iExponent -= 1075;
	
	if ( llMantissa != 0 ){
		//add mantissa sign
		while ( (llMantissa & 0x01) == 0x00 ){
			llMantissa = llMantissa >> 1;
			iExponent++;
		}
		if ( bSign ){
			//the mantissa is negativ
			llMantissa = 0 - llMantissa;
		}
		
		if ( iSizeMantissa != NULL ){
			//evalue the digits in the mantissa
			(*iSizeMantissa) = getDigits( llMantissa );
		}
		if ( iSizeExponent != NULL ){
			//evalue the digits in the exponent
			(*iSizeExponent) = getDigits( iExponent );
		}
	
	}else{
		iExponent = 0;
		
		if ( iSizeMantissa != NULL ){
			//set digits in the mantissa
			(*iSizeMantissa) = 0;
		}
		if ( iSizeExponent != NULL ){
			//set digits in the exponent
			(*iSizeExponent) = 0;
		}
	}
	//transfer the evauled numbers to the output valus
	if ( lMantissa != NULL ){
		(*lMantissa) = llMantissa;
	}
	if ( lMantissa != NULL ){
		(*lExponent) = iExponent;
	}
}


/**
 * Composes a doubleFib number into it's mantissa and exponent part.
 * It's the invers of: @see decomposeDoubleFib()
 * Basicly it evalues: lMantissa * 2^lExponent
 *
 * @param lMantissa the mantissa of the number
 * @param lExponent the exponent of the number
 * @return lMantissa * 2^lExponent
 */
doubleFib fib::composeDoubleFib(
		const longFib & lMantissa, const longFib & lExponent ){
	
	if ( lMantissa == 0 ){
		return 0.0;
	}
	double dReturnValue = 0.0;
	long long & llNumber = *((long long*)&dReturnValue);
	
	if ( lMantissa < 0 ){
		//set the sign to negativ; it's the bit 63
		llNumber = 0x8000000000000000L;
	}
	//set the mantissa
	long long llMantissa = (( 0 <= lMantissa) ? lMantissa : ( 0 - lMantissa ) );
	/* Bias the exponent. It's actually biased by 1023, but we're
	treating the mantissa as m.0 rather than 0.m, so we need
	to subtract another 52 from it.*/
	unsigned int iExponent = lExponent + 1075; //1075 = (1023 + 52);
	//bring first mantissa bit to the bit 52
	while ( ( llMantissa & 0x10000000000000L ) == 0x0L ){
		llMantissa = llMantissa << 1;
		iExponent--;
	}
	llNumber |= 0xFFFFFFFFFFFFFL & llMantissa;

	//set the exponent; its the bit 52 till 62
	if ( iExponent != 0 ){
		llNumber |= ( 0x7FFL & iExponent ) << 52;
	}//else exponent in double are bits with value 0
	
	return dReturnValue;
}


/**
 * This function rounds the given number of bits ulNumberOfBits up
 * to a full number of byte;
 *
 * @param ulNumberOfBits the number of bits to round
 * @return the, to full byte rounded up, number of bits
 */
unsigned long fib::roundUpToFullByte( unsigned long ulNumberOfBits ){
	
	unsigned int uiMissingBits = 8 - (ulNumberOfBits % 8);
	if ( uiMissingBits != 8 ){
		return ulNumberOfBits + uiMissingBits;
	}//else no bits missing
	return ulNumberOfBits;
}


/**
 * This function evalues the greatest common divisor of the two given
 * numbers.
 *
 * @param dValue1 the first number
 * @param dValue2 the second number
 * @return the greatest common divisor of the two given numbers dValue1
 * 	and dValue2
 */
doubleFib fib::gcd( doubleFib dValue1, doubleFib dValue2 ){
	
	//make the numbers positive
	if ( dValue1 < 0.0 ){
		dValue1 *= ((doubleFib)-1.0);
	}
	if ( dValue2 < 0.0 ){
		dValue2 *= ((doubleFib)-1.0);
	}
	
	//this is the Euclidean algorithm
	if ( dValue1 == 0.0 ){
		return dValue2;
	}
	while ( dValue2 != 0.0 ){
		if ( dValue1 <= dValue2 ){
			//bring the value of dValue1 near the value dValue2
			doubleFib dTmpValue1 = dValue1;
			if ( dValue1 != 0.0 ){
				while ( true ){
					const doubleFib dTmpValue1Double = dTmpValue1 * 2.0;
					if ( dValue2 < dTmpValue1Double ){
						break;
					}
					dTmpValue1 = dTmpValue1Double;
				}//dTmpValue1 <= dValue2
			}
			dValue2 = dValue2 - dTmpValue1;
		}else{
			//bring the value of dValue2 near the value dValue1
			doubleFib dTmpValue2 = dValue2;
			while ( true ){
				const doubleFib dTmpValue2Double = dTmpValue2 * 2.0;
				if ( dValue1 <= dTmpValue2Double ){
					break;
				}
				dTmpValue2 = dTmpValue2Double;
			}//dTmpValue2 <= dValue1
			dValue1 = dValue1 - dTmpValue2;
		}
	}
	return dValue1;
}


/**
 * @param dValue the value, for which to evalue the positiv value
 * @return the positive value for the given number dValue
 */
float fib::absF( const float & dValue ){

	return (0.0 <= dValue)? dValue : ( ((float)(0.0)) - dValue );
}

/**
 * @param dValue the value, for which to evalue the positiv value
 * @return the positive value for the given number dValue
 */
double fib::absF( const double & dValue ){

	return (0.0 <= dValue)? dValue : ( ((double)(0.0)) - dValue );
}


/**
 * This function evalues the power function of integer values.
 * Returns base raised to the power exponent.
 *
 * @param lBase the base for the power function
 * @param lExponent the exponent for the power function
 * @return the value lBase^lExponent
 */
double fib::powInt( const longFib lBase, const longFib lExponent ){
	
	if ( ( lBase == 2 ) && ( 0 <= lExponent ) ){
		return ((longFib)(1)) << lExponent;
	}
	
	return roundToLongFib( std::pow( (double(lBase)), (double(lExponent)) ) );
}


/**
 * This functions checks if the given double number is equal 0.
 * Really small differences will be ignored.
 *
 * @param dValue the number to check
 * @return true if the given number is equal 0, else false
 */
bool fib::isEqualNull( const double & dValue ){
	
	return ( -1e-300 <= dValue ) && ( dValue <= 1e-300 );
}


/**
 * This functions checks if the given double number is equal 0.
 * Really small differences will be ignored.
 *
 * @param dValue the number to check
 * @return true if the given number is equal 0, else false
 */
bool fib::isEqualNull( const float & dValue ){
	
	return ( -1e-35 <= dValue ) && ( dValue <= 1e-35 );
}


/**
 * This functions compares two double numbers.
 * Really small differences will be ignored.
 *
 * @param dValue1 the first number to compare
 * @param dValue2 the second number to compare
 * @return true if the first number is equal to the second, else false
 */
bool fib::compareDouble( const double & dValue1, const double & dValue2 ){
	
//	DEBUG_OUT_L4(<<"compareDouble( "<<dValue1<<", "<<dValue2<<") started "<<endl<<flush);
	if ( isEqualNull( dValue1 ) ){
		//both 0 ?
		return ( isEqualNull( dValue2 ) );
	}
	const double dDiff = absF( REALLY_SMALL_DOUBLE_DIFFERENCE * dValue1 );
//	DEBUG_OUT_L4(<<"dDiff= "<<dDiff<<"   evaluing: "<<(dValue1 - dDiff)<<" < "<<dValue2<<" < "<<(dValue1 + dDiff)<<endl<<flush);

	return ( dValue1 - dDiff <= dValue2 ) && ( dValue2 <= dValue1 + dDiff );
}


/**
 * This functions compares two float numbers.
 * Really small differences will be ignored.
 *
 * @param dValue1 the first number to compare
 * @param dValue2 the second number to compare
 * @return true if the first number is equal to the second, else false
 */
bool fib::compareDouble( const float & dValue1, const float & dValue2 ){
	
//	DEBUG_OUT_L4(<<"compareDouble( "<<dValue1<<", "<<dValue2<<") started "<<endl<<flush);
	if ( isEqualNull( dValue1 ) ){
		//both 0 ?
		return ( isEqualNull( dValue2 ) );
	}
	const float dDiff = absF( REALLY_SMALL_FLOAT_DIFFERENCE * dValue1 );
//	DEBUG_OUT_L4(<<"dDiff= "<<dDiff<<"   evaluing: "<<(dValue1 - dDiff)<<" <= "<<dValue2<<" <= "<<(dValue1 + dDiff)<<endl<<flush);
	
	return ( dValue1 - dDiff <= dValue2 ) && ( dValue2 <= dValue1 + dDiff );
}


/**
 * This functions reads a double number from the given string.
 * Reading will be independent of the local. (The default format is english.)
 * Leading spaces will be ignored.
 * The decimal point can be the english '.' or german ','.
 * If the number contains one '.' and some ',', the '.' will be seen as
 * the decimal point, ',' before it will be ignored and the number will
 * end at the first ',' after the '.'.
 * If the number contains one ',' and more than one '.', the ',' will
 * be seen as the decimal point, '.' before or after it will be ignored.
 * Examples:
 * 	- "123" = 123
 * 	- "-1234" = -1234
 * 	- "+1234" = 1234
 * 	- "12.34" = 12.34
 * 	- "12,34" = 12.34
 * 	- "12,345.678,9" = 12345.678
 * 	- "12.345,678.9" = 12345.6789
 *
 * @see readDoubleReturnEnd()
 * @see readDoubleFromFunction()
 * @param strDouble the string where to read the double from
 * @return the readed double number
 */
doubleFib fib::readDouble( const char * strDouble ){
	
	return fib::readDoubleReturnEnd( strDouble ).first;
}


/**
 * This functions reads a double number from the given string.
 * Reading will be independent of the local. (The default format is english.)
 * Leading spaces will be ignored.
 * The decimal point can be the english '.' or german ','.
 * If the number contains one '.' and some ',', the '.' will be seen as
 * the decimal point, ',' before it will be ignored and the number will
 * end at the first ',' after the '.'.
 * If the number contains one ',' and more than one '.', the ',' will
 * be seen as the decimal point, '.' before or after it will be ignored.
 * Examples:
 * 	- "123" = 123
 * 	- "-1234" = -1234
 * 	- "+1234" = 1234
 * 	- "12.34" = 12.34
 * 	- "12,34" = 12.34
 * 	- "12,345.678,9" = 12345.678
 * 	- "12.345,678.9" = 12345.6789
 * 	- "12,345.678.97,8" = 12345.678
 *
 * @see readDouble()
 * @see readDoubleFromFunction()
 * @param strDouble the string where to read the double from
 * @return a pair of:
 * 	first: the readed double number
 * 	second: a pointer to the end position of the readed number
 * 		(it points to the first character not in the number)
 */
pair< doubleFib, const char * >
	fib::readDoubleReturnEnd( const char * strDouble ){
	
	if ( strDouble == NULL ){
		//no number to read
		return pair< doubleFib, const char * >( 0.0, strDouble );
	}
	//evalue number of '.' and ',' (0, 1 or more than 1)
	unsigned char uiNumberOfPoints = 0;
	unsigned char uiNumberOfComma  = 0;
	const char * pActualPosition = strDouble;
	for ( ;(*pActualPosition) != 0x0; pActualPosition++ ){
		
		const char cActualChar = (*pActualPosition);
		if ( cActualChar == '.' ){
			uiNumberOfPoints++;
			
			if ( ( 1 < uiNumberOfPoints ) && ( 1 < uiNumberOfComma ) ){
				//not more information needed
				break;
			}
		}else if ( cActualChar == ',' ){
			uiNumberOfComma++;
			if ( 1 < uiNumberOfComma ){
				//not more information needed
				break;
			}
		}else if ( ( ( cActualChar < '0' ) || ( '9' < cActualChar ) ) &&
				( cActualChar != '+' ) && ( cActualChar != '-' ) &&
				( cActualChar != ' ' ) && ( cActualChar != '	' )){
			//end of number
			break;
		}//character not important
		
	}//end while string end not reached
	//if one ',' found and zero or more than one '.' ->  use ',' as decimal point
	const char cDecimalPoint =
		//if one ',' found and (zero or more than one '.') ->  use ',' as decimal point
		( ( uiNumberOfComma == 1 ) && ( uiNumberOfPoints != 1 ) ) ? ',' :
		//else use '.' as decimal point
		'.';
	const char cNotDecimalPoint = ( cDecimalPoint == '.' ) ? ',' : '.';
	pActualPosition = strDouble;
	//read till first number
	bool bNegativeSign = false;
	
	for ( ;(*pActualPosition) != 0x0; pActualPosition++ ){
		
		const char cActualChar = (*pActualPosition);
		if ( cActualChar == '-' ){
			//number is negativ
			bNegativeSign = true;
			//next character should be number
			pActualPosition++;
			break;
		}//else
		if ( ( ( '0' <= cActualChar ) && ( cActualChar <= '9' ) ) ||
				( cActualChar == '.' ) || ( cActualChar == ',' ) ){
			//number found
			break;
		}//else
		if ( ( cActualChar != '+' ) && ( cActualChar != ' ' ) &&
				( cActualChar != '	' ) ){
			//not a valid number -> return 0
			return pair< doubleFib, const char * >( 0.0, strDouble );
		}
	}
	doubleFib dReadedValue = 0.0;
	//read part before the decimal point
	while ( true ){
		const char cActualChar = (*pActualPosition);
		if ( ( '0' <= cActualChar ) && ( cActualChar <= '9' ) ){
			//read next decimal char
			dReadedValue *= 10;
			dReadedValue += ((doubleFib)(cActualChar - '0'));
		}else if ( cActualChar != cNotDecimalPoint ){
			//not a number or not "not decimal point" (ignore "not decimal point" char)
			break;
		}
		//check next character
		pActualPosition++;
	}
	if ( (*pActualPosition) == cDecimalPoint ){
		//read part after the decimal point
		pActualPosition++;
		
		unsigned long ulNumberAfterPoint = 0;
		unsigned int  uiDigitsAfterPoint = 0;
		
		while ( true ){
			const char cActualChar = (*pActualPosition);
			if ( ( '0' <= cActualChar ) && ( cActualChar <= '9' ) ){
				//read next decimal char
				ulNumberAfterPoint *= 10;
				ulNumberAfterPoint += ((doubleFib)(cActualChar - '0'));
				uiDigitsAfterPoint++;
			}else if ( cActualChar == cDecimalPoint ){
				//not a number and a decimal point or
				break;
			}else if ( cActualChar != '.' ){
				/*not a decimal point and not a '.' (if the decimal point is
				',' following '.' will be ignored)*/
				break;
			}
			//check next character
			pActualPosition++;
		}
		dReadedValue += ((doubleFib)(ulNumberAfterPoint)) /
			pow( 10.0, uiDigitsAfterPoint );
	}
	//try to read the part till the next e (scientific notation)
	for ( ;(*pActualPosition) != 0x0; pActualPosition++ ){
		
		const char cActualChar = (*pActualPosition);
		if ( ( cActualChar == 'e' ) || ( cActualChar == 'E' ) ||
				( ( cActualChar != ' ' ) && ( cActualChar != '	' ) ) ){
			//number found or not spaces
			break;
		}
	}//end for skip blanks
	//check for scientific notation (eX = 10^X)
	if ( ( (*pActualPosition) == 'e' ) || ( (*pActualPosition) == 'E' ) ){
		//read scientific notation (eX = 10^X ; X is an integer)
		//skip e
		pActualPosition++;
		//read the sign of the exponent
		bool bNegativSignExponent = false;
		for ( ;(*pActualPosition) != 0x0; pActualPosition++ ){
			
			const char cActualChar = (*pActualPosition);
			if ( cActualChar == '-' ){
				//number is negativ
				bNegativSignExponent = true;
				//next character should be number
				pActualPosition++;
				break;
			}//else
			if ( ( '0' <= cActualChar ) && ( cActualChar <= '9' ) ){
				//read decimal char
				break;
			}//else
			if ( ( cActualChar != '+' ) && ( cActualChar != ' ' ) &&
					( cActualChar != '	' ) ){
				//not a valid exponent number
				break;
			}
		}
		int iExponent = 0;
		while ( true ){
			const char cActualChar = (*pActualPosition);
			if ( ( cActualChar < '0' ) || ( '9' < cActualChar ) ){
				//not a number
				break;
			}
			//read next decimal char
			iExponent *= 10;
			iExponent += ((unsigned int)(cActualChar - '0'));
			//check next character
			pActualPosition++;
		}
		if ( bNegativSignExponent ){
			//negate readed exponent
			iExponent = 0 - iExponent;
		}
		dReadedValue *= pow( 10.0, (doubleFib)iExponent );
	}
	
	if ( bNegativeSign ){
		//negate readed value
		dReadedValue = 0 - dReadedValue;
	}
	
	return pair< doubleFib, const char * >( dReadedValue, pActualPosition );
}




/**
 * Help classes for @see readDoubleFromFunction()
 */
namespace fib{
namespace nFibDatatypes_ArithmeticOperator{
	
	/**
	 * The parent class for all operators.
	 */
	class cOperator{
	public:
		
		/**
		 * The number of open brackets for this operator.
		 * (Opened brackets before the operator, but not closed.)
		 */
		unsigned int uiOpenBarckets;
		
		/**
		 * standard constructor
		 *
		 * @param uiInOpenBarckets the number of open brackets for this operator
		 * 	@see uiOpenBarckets
		 */
		cOperator( const unsigned int uiInOpenBarckets ):
				uiOpenBarckets( uiInOpenBarckets ){
			//nothing to do
		}
		
		
		/**
		 * destructor
		 */
		virtual ~cOperator(){
			//nothing to do
		}
		
		/**
		 * @return the evalued value for this operator
		 */
		virtual doubleFib getValue() const = 0;
		
		/**
		 * @return the type for this operator
		 */
		virtual char getType() const = 0;
		
		/**
		 * @see hasMissingSubOperators()
		 * @return the number of suboperators for this operator
		 */
		virtual unsigned int getNumberSubOperators() const = 0;
		
		/**
		 * @see getNumberSubOperators()
		 * @return true if sub operators of this operator or a contained
		 * 	operator are missing, else false
		 */
		virtual bool hasMissingSubOperators() const = 0;
		
		/**
		 * This method sets the most left operator of this or the left
		 * contained operator.
		 *
		 * @see setMostRightOperator()
		 * @param pOperator a pointer to the operator to set
		 * @return true if the operator could be set, else false
		 */
		virtual bool setMostLeftOperator( cOperator * pOperator ) = 0;
		
		/**
		 * This method sets the most right operator of this or the right
		 * contained operator.
		 *
		 * @see setMostLeftOperator()
		 * @param pOperator a pointer to the operator to set
		 * @return true if the operator could be set, else false
		 */
		virtual bool setMostRightOperator( cOperator * pOperator ) = 0;
		
		
		/**
		 * @see hasPrecedence()
		 * @return the precedence value for this operation (operations with
		 * 	higher precedence should be evalued first)
		 */
		unsigned int getPrecedenceValue() const{
			
			switch ( getType() ){
				
				case 'a'://add
				case 's'://subtract
					return 50;
				case 'm'://multiply
				case 'o'://modulo
				case 'd'://divide
					return 100;
				case 'S'://sinus
				case 'C'://cosinus
				case 'T'://tangens
					return 130;
				case 'l'://log
				case 'L'://ln
				case 'r'://square root
				case 'e'://exponent
					return 150;
				case 'i'://increment
				case 'c'://decrement
					return 170;
				case 'p'://positiv (abs)
					return 180;
				case 'n'://negativ
					return 190;
				case 'v'://value
					return 200;
			}//else unknown operator
			return 0;
		}
		
		
		/**
		 * This methods evalues if this operator has precedence over the
		 * given operator.
		 *
		 * @see getPrecedenceValue()
		 * @param pOperator a pointer to the operator for which the
		 * 	precedence to this operator should be evalued
		 * 	(Beware: Should never be NULL.)
		 * @return true if this operator has precedence over the given
		 * 	operator, else false
		 */
		bool hasPrecedence( const cOperator * pOperator ) const{
			
			if ( pOperator->uiOpenBarckets != uiOpenBarckets ){
				//different bracked depth
				if ( pOperator->uiOpenBarckets < uiOpenBarckets ){
					/*this operator is in bracket (higher than the other)
					 -> it has precedence over the other*/
					return true;
				}//else ( uiOpenBarckets < pOperator->uiOpenBarckets ){
				/*the other operator is in bracket (higher than this)
				 -> it has precedence over this*/
				return false;
			}//else open brackets are equal
			//use the precedence values of the operators
			return ( pOperator->getPrecedenceValue() <= getPrecedenceValue() );
		}
		
		
		
	};//end class cOperator
	
	
	/**
	 * Class for unary operators.
	 */
	class cUnaryOperator: public cOperator{
	public:
		
		/**
		 * A pointer to the operator contained in this operator.
		 */
		cOperator * pSubOperator;
		
		/**
		 * The type of this operator.
		 * possible types are:
		 * 	- 'p': positiv (abs)
		 * 	- 'n': negativ
		 * 	- 'l': log
		 * 	- 'L': ln
		 * 	- 'r': square root
		 * 	- 'i': increment
		 * 	- 'c': decrement
		 * 	- 'S'://sinus
		 * 	- 'C'://cosinus
		 * 	- 'T'://tangens
		 */
		char cType;
		
		
		
		/**
		 * standard constructor
		 *
		 * @param cInType the type of the operator @see cType
		 * @param uiInOpenBarckets the number of open brackets for this operator
		 * 	@see uiOpenBarckets
		 */
		cUnaryOperator( const char cInType, const unsigned int uiInOpenBarckets  ):
				cOperator( uiInOpenBarckets ), pSubOperator( NULL ), cType( cInType ){
			//nothing to do
		}
		
		
		/**
		 * destructor
		 */
		virtual ~cUnaryOperator(){
			
			if ( pSubOperator ){
				//delete sub operator
				delete pSubOperator;
			}
		}
		
		/**
		 * @return the evalued value for this operator
		 */
		virtual doubleFib getValue() const{
			
			if ( pSubOperator == NULL ){
				//can't evalue a value -> return 0
				return ((doubleFib)0.0);
			}
			const doubleFib dSubValue = pSubOperator->getValue();
			
			switch ( cType ){
				case 'p'://positiv (abs)
					return abs( dSubValue );
				case 'n'://negativ
					return ((doubleFib)0.0) - dSubValue;
				case 'l'://log
					return ( 0 < dSubValue ) ? log10( dSubValue ) : ((doubleFib)0.0);
				case 'L'://ln
					return ( 0 < dSubValue ) ? log( dSubValue ) : ((doubleFib)0.0);
				case 'r'://square root
					return ( 0 < dSubValue ) ? sqrt( dSubValue ) : ((doubleFib)0.0);
				case 'i'://increment
					return dSubValue + ((doubleFib)1.0);
				case 'c'://decrement
					return dSubValue - ((doubleFib)1.0);
				case 'S'://sinus
					return sin( dSubValue );
				case 'C'://cosinus
					return cos( dSubValue );
				case 'T'://tangens
					return tan( dSubValue );
			}//else unknown operator
			return ((doubleFib)0.0);
		}
		
		
		/**
		 * @return the type for this operator
		 */
		virtual char getType() const{
			return cType;
		}
		
		
		/**
		 * @return the number of suboperators for this operator 1
		 */
		virtual unsigned int getNumberSubOperators() const{
			return 1;
		}
		
		
		/**
		 * @see getNumberSubOperators()
		 * @return true if sub operators of this operator or a contained
		 * 	operators are missing, else false
		 */
		virtual bool hasMissingSubOperators() const{
			
			if ( pSubOperator ){
				return pSubOperator->hasMissingSubOperators();
			}//else suboperator missing
			return true;
		}
		
		
		/**
		 * This method sets the most left operator of this or the left
		 * contained operators.
		 * (This operator type (unary) as no left operator. So this method
		 * will retun always false.)
		 *
		 * @see setMostRightOperator()
		 * @param pOperator a pointer to the operator to set
		 * @return false because the operator could not be set
		 */
		virtual bool setMostLeftOperator( cOperator * pOperator ){
			//one ary operators have no left sub operator
			return false;
		}
		
		
		/**
		 * This method sets the most right operator of this or the right
		 * contained operators.
		 *
		 * @see setMostLeftOperator()
		 * @param pOperator a pointer to the operator to set
		 * @return true if the operator could be set, else false
		 */
		virtual bool setMostRightOperator( cOperator * pOperator ){
			
			if ( pSubOperator ){
				return pSubOperator->setMostRightOperator( pOperator );
			}//else suboperator missing -> set to given operator
			pSubOperator = pOperator;
			return true;
		}
		
	};//end class cUnaryOperator
	
	
	/**
	 * Class for binary operators.
	 */
	class cBinaryOperator: public cOperator{
	public:
		
		/**
		 * A pointer to the first operator contained in this operator.
		 */
		cOperator * pFirstSubOperator;
		
		
		/**
		 * A pointer to the  second operator contained in this operator.
		 */
		cOperator * pSecondSubOperator;
		
		/**
		 * The type of this operator.
		 * possible types are:
		 * 	- 'a': add
		 * 	- 's': subtract
		 * 	- 'm': multiply
		 * 	- 'd': divide
		 * 	- 'e': exponent
		 * 	- 'o': modulo
		 */
		char cType;
		
		
		
		/**
		 * standard constructor
		 *
		 * @param cInType the type of the operator @see cType
		 * @param uiInOpenBarckets the number of open brackets for this operator
		 * 	@see uiOpenBarckets
		 */
		cBinaryOperator( const char cInType, const unsigned int uiInOpenBarckets  ):
				cOperator( uiInOpenBarckets ), pFirstSubOperator( NULL ),
				pSecondSubOperator( NULL ), cType( cInType ){
			//nothing to do
		}
		
		
		/**
		 * destructor
		 */
		virtual ~cBinaryOperator(){
			
			if ( pFirstSubOperator ){
				//delete first sub operator
				delete pFirstSubOperator;
			}
			if ( pSecondSubOperator ){
				//delete second sub operator
				delete pSecondSubOperator;
			}
		}
		
		
		/**
		 * @return the evalued value for this operator
		 */
		virtual doubleFib getValue() const{
			
			if ( ( pFirstSubOperator == NULL ) || ( pSecondSubOperator == NULL ) ){
				//can't evalue a value -> return 0
				return ((doubleFib)0.0);
			}
			const doubleFib dFirstValue  = pFirstSubOperator->getValue();
			const doubleFib dSecondValue = pSecondSubOperator->getValue();
			
			switch ( cType ){
				case 'a'://add
					return dFirstValue + dSecondValue;
				case 's'://subtract
					return dFirstValue - dSecondValue;
				case 'm'://multiply
					return dFirstValue * dSecondValue;
				case 'd'://divide
					return ( isEqualNull( dSecondValue ) ?
						((doubleFib)0.0) : ( dFirstValue / dSecondValue ) );
				case 'e'://exponent
					return pow( dFirstValue, dSecondValue);
				case 'o'://modulo
					return fmod( dFirstValue, dSecondValue );
			}//else unknown operator
			return ((doubleFib)0.0);
		}
		
		
		/**
		 * @return the type for this operator
		 */
		virtual char getType() const{
			return cType;
		}
		
		
		/**
		 * @return the number of suboperators for this operator 2
		 */
		virtual unsigned int getNumberSubOperators() const{
			
			return 2;
		}
		
		
		/**
		 * @see getNumberSubOperators()
		 * @return true if sub operators of this operator or a contained
		 * 	operator are missing, else false
		 */
		virtual bool hasMissingSubOperators() const{
			//check first suboperator
			if ( pFirstSubOperator == NULL ){
				//first suboperator missing
				return true;
			}else{//first suboperator not missing
				if ( pFirstSubOperator->hasMissingSubOperators() ){
					//suboperator missing in operator contained in the first suboperator
					return true;
				}
			}
			//check second suboperator
			if ( pSecondSubOperator == NULL ){
				//second suboperator missing
				return true;
			}else{//second suboperator not missing
				if ( pSecondSubOperator->hasMissingSubOperators() ){
					//suboperator missing in operator contained in the second suboperator
					return true;
				}
			}//else no suboperator missing
			return false;
		}
		
		
		/**
		 * This method sets the most left operator of this or the left
		 * contained operator.
		 *
		 * @see setMostRightOperator()
		 * @param pOperator a pointer to the operator to set
		 * @return true if the operator could be set, else false
		 */
		virtual bool setMostLeftOperator( cOperator * pOperator ){
			
			if ( pFirstSubOperator == NULL ){
				//first suboperator missing -> set it to the given operator
				pFirstSubOperator = pOperator;
				return true;
			}else{/*first suboperator not missing
				-> try to set most left operator in first suboperator*/
				return pFirstSubOperator->setMostLeftOperator( pOperator );
			}//else can't set most left suboperator
			return false;
		}
		
		
		/**
		 * This method sets the most right operator of this or the right
		 * contained operator.
		 *
		 * @see setMostLeftOperator()
		 * @param pOperator a pointer to the operator to set
		 * @return true if the operator could be set, else false
		 */
		virtual bool setMostRightOperator( cOperator * pOperator ){
			
			if ( pSecondSubOperator == NULL ){
				//second suboperator missing -> set it to the given operator
				pSecondSubOperator = pOperator;
				return true;
			}else{/*second suboperator not missing
				-> try to set most left operator in second suboperator*/
				return pSecondSubOperator->setMostRightOperator( pOperator );
			}//else can't set most left suboperator
			return false;
		}
		
	};//end class cBinaryOperator
	
	
	
	/**
	 * This class represents a operator which is a value.
	 */
	class cValueOperator: public cOperator{
	public:
		
		/**
		 * The value for this value operator.
		 */
		doubleFib dValue;
		
		/**
		 * standard constructor
		 *
		 * @param uiInOpenBarckets the number of open brackets for this operator
		 * 	@see uiOpenBarckets
		 * @param dInValue the value for this value operator
		 */
		cValueOperator( const unsigned int uiInOpenBarckets,
				const doubleFib dInValue = 0.0 ):
				cOperator( uiInOpenBarckets ), dValue( dInValue ){
			//nothing to do
		}
		
		
		/**
		 * destructor
		 */
		virtual ~cValueOperator(){
			//nothing to do
		}
		
		
		/**
		 * @return the value for this operator dValue
		 * 	@see dValue
		 */
		virtual doubleFib getValue() const{
			
			return dValue;
		}
		
		
		/**
		 * @return the type for this operator 'v'
		 */
		virtual char getType() const{
			return 'v';
		}
		
		
		/**
		 * @return the number of suboperators for this operator 0
		 */
		virtual unsigned int getNumberSubOperators() const{
			
			return 0;
		}
		
		
		
		/**
		 * @see getNumberSubOperators()
		 * @return true because no sub operators of this operator or a contained
		 * 	operator are missing (it has no suboperators which could be missing)
		 */
		virtual bool hasMissingSubOperators() const{
			//value operator has no suboperators -> non can be missing
			return false;
		}
		
		
		/**
		 * This method sets the most left operator of this or the left
		 * contained operator.
		 *
		 * @see setMostRightOperator()
		 * @param pOperator a pointer to the operator to set
		 * @return false because no sub operator can be set for this class
		 * 	(it has no suboperators)
		 */
		virtual bool setMostLeftOperator( cOperator * pOperator ){
			//value operator has no suboperators -> non can be set
			return false;
		}
		
		
		/**
		 * This method sets the most right operator of this or the right
		 * contained operator.
		 *
		 * @see setMostLeftOperator()
		 * @param pOperator a pointer to the operator to set
		 * @return false because no sub operator can be set for this class
		 * 	(it has no suboperators)
		 */
		virtual bool setMostRightOperator( cOperator * pOperator ){
			//value operator has no suboperators -> non can be set
			return false;
		}
		
	};//end class cValueOperator


};//end namespace fib
};//end namespace nFibDatatypes_ArithmeticOperator




using namespace fib::nFibDatatypes_ArithmeticOperator;

/**
 * This functions reads a double number from the given string.
 * The number can represented by a simple formular.
 * Allowed operators (spaces will be ignored):
 * 	- values as numbers @see readDouble()
 * 	- addition: X + Y
 * 	- subtraction: X - Y
 * 	- multiply: X * Y
 * 	- division: X / Y
 * 	- modulo: X % Y
 * 	- increment: ++X
 * 	- decrement: --X
 * 	- positiv / absolut value: +X
 * 	- positiv / absolut value: abs X
 * 	- logarithm to base 10: log X
 * 	- natural logarithm: ln X
 * 	- square root: sqrt X
 * 	- exponent: X^Y
 * 	- exponent: pow( X, Y )
 * 	- sinus: sin X
 * 	- cosinus: cos X
 * 	- tangens: tan X
 * 	- constant PI: PI
 * 	- constant e: e
 *
 * @see readDouble()
 * @param strDouble the string where to read the double from (null terminated)
 * @param pPairOutEvalueStatus if not NULL a pair for the status of the
 * 	formula evaluation
 * 		first: true if the formular could be evalued, else false;
 * 			If false the returned value will not include the whole formular.
 * 		second: a pointer to the end position of the readed formular
 * 			(it points to the first character not in the formular)
 * 			If first is false it points to the first character which
 * 			could not be interpreted as a operator or number, but not
 * 			all the string before is necessarily be used to evalue the
 * 			return value.
 * @return the readed double number
 */
doubleFib fib::readDoubleFromFunction( const char * strDouble,
		pair< bool, const char * > * pPairOutEvalueStatus  ){
	
	if ( strDouble == NULL ){
		//Error: nothing to read
		if ( pPairOutEvalueStatus ){
			//evalue status
			pPairOutEvalueStatus->first  = false;
			//the formular could be evalued till the actual position
			pPairOutEvalueStatus->second = strDouble;
		}
		return 0.0;
	}
	if ( pPairOutEvalueStatus ){
		pPairOutEvalueStatus->first = true;
	}
	
	unsigned int uiOpenBarckets = 0;
	//the list of operators in the order they where readed
	list< cOperator * > liOpenOperators;
	
	const char * pActualPosition = strDouble;
	//read all function operators and values
	bool bGoOn = true;
	while ( bGoOn ){
		//skip blanks
		for ( ;(*pActualPosition) != 0x0; pActualPosition++ ){
			
			if ( ( (*pActualPosition) != ' ' ) && ( (*pActualPosition) != '	' ) ){
				//not a blank -> break
				break;
			}
		}//end for skip blanks
		if ( (*pActualPosition) == 0x0  ){
			//end of string
			break;
		}
		
		const char cActualChar = (*pActualPosition);
		//check if next is opening bracket
		if ( cActualChar == '(' ){
			//next is opening bracket
			uiOpenBarckets++;
			pActualPosition++;
			
		}else if ( cActualChar == ')' ){
			//if next is closing bracket
			if ( 0 < uiOpenBarckets ){
				uiOpenBarckets--;
			}else if ( pPairOutEvalueStatus ){
				//no opening bracket for closing bracket
				pPairOutEvalueStatus->first = false;
			}
			pActualPosition++;
		}else if ( ( '0' <= cActualChar ) && ( cActualChar <= '9' ) ){
			//next comes a number -> read it
			const pair< doubleFib, const char * > paReadedNumber =
				readDoubleReturnEnd( pActualPosition );
			
			liOpenOperators.push_back( new cValueOperator( uiOpenBarckets,
				paReadedNumber.first ) );
			pActualPosition = paReadedNumber.second;
		}else if ( ( ( cActualChar == '.' ) || ( cActualChar == ',' ) ) &&
				( ( '0' <= (*(pActualPosition + 1)) ) &&
					( (*(pActualPosition + 1)) <= '9' ) ) ){
			//next comes a number (starting with a point) -> read it
			const pair< doubleFib, const char * > paReadedNumber =
				readDoubleReturnEnd( pActualPosition );
			
			liOpenOperators.push_back( new cValueOperator( uiOpenBarckets,
				paReadedNumber.first ) );
			pActualPosition = paReadedNumber.second;
		}else{//try to read other operator
			pActualPosition++;
			if ( (*pActualPosition) == 0x0  ){
				/*create operators which can be represented as a single char at
				 *the formular end*/
				if ( cActualChar == 'e' ){
					//constant "e"
					liOpenOperators.push_back(
						new cValueOperator( uiOpenBarckets, 2.718281828459045235360 ) );
				}
				break;
			}
			switch ( cActualChar ){
				case '+':{
					if ( liOpenOperators.empty() ||
							( liOpenOperators.back()->getNumberSubOperators() != 0 ) ){
						if ( (*pActualPosition) == '+' ){
							//two '+' follow each other ("++") -> increment operator
							liOpenOperators.push_back(
								new cUnaryOperator( 'i', uiOpenBarckets ) );
							pActualPosition++;
						}else{//the '+' is an unary positiv
							liOpenOperators.push_back(
								new cUnaryOperator( 'p', uiOpenBarckets ) );
						}
					}else{
						//the '+' is a binary addition
						liOpenOperators.push_back(
							new cBinaryOperator( 'a', uiOpenBarckets ) );
					}
				}break;
				case 'a':{//absolut value "abs"
					if ( (*pActualPosition) == 'b' ){
						
						pActualPosition++;
						if ( (*pActualPosition) == 's' ){
							liOpenOperators.push_back(
								new cUnaryOperator( 'p', uiOpenBarckets ) );
							pActualPosition++;
							break;
						}//else
					}//else unknown operator
					if ( pPairOutEvalueStatus ){
						pPairOutEvalueStatus->first = false;
					}
					bGoOn = false;
				}break;
				case '-':{
					if ( liOpenOperators.empty() ||
							( liOpenOperators.back()->getNumberSubOperators() != 0 ) ){
						
						if ( (*pActualPosition) == '-' ){
							//two '-' follow each other ("--") -> decrement operator
							liOpenOperators.push_back(
								new cUnaryOperator( 'c', uiOpenBarckets ) );
							pActualPosition++;
						}else{//the '-' is an unary negativ
							liOpenOperators.push_back(
								new cUnaryOperator( 'n', uiOpenBarckets ) );
						}
					}else{//the '-' is a binary subtraction
						liOpenOperators.push_back(
							new cBinaryOperator( 's', uiOpenBarckets ) );
					}
				}break;
				case 'l':{//check log or ln
					if ( (*pActualPosition) == 'n' ){
						//ln operator
						liOpenOperators.push_back(
							new cUnaryOperator( 'L', uiOpenBarckets ) );
						pActualPosition++;
						break;
					}else if ( (*pActualPosition) == 'o' ){
						pActualPosition++;
						
						if ( (*pActualPosition) == 'g' ){
							//log operator
							liOpenOperators.push_back(
								new cUnaryOperator( 'l', uiOpenBarckets ) );
							pActualPosition++;
							break;
						}//else
					}//else
					//unknown operator
					if ( pPairOutEvalueStatus ){
						pPairOutEvalueStatus->first = false;
					}
					bGoOn = false;
				}break;
				case 's':{//check if square root "sqrt" or sinus "sin"
					if ( (*pActualPosition) == 'q' ){
						
						pActualPosition++;
						if ( (*pActualPosition) == 'r' ){
							
							pActualPosition++;
							if ( (*pActualPosition) == 't' ){
								//next operator is square root "sqrt"
								liOpenOperators.push_back(
									new cUnaryOperator( 'r', uiOpenBarckets ) );
								pActualPosition++;
								break;
							}//else
						}//else unknown operator
					}else if ( (*pActualPosition) == 'i' ){
						
						pActualPosition++;
						if ( (*pActualPosition) == 'n' ){
							//next operator is sinus "sin"
							liOpenOperators.push_back(
								new cUnaryOperator( 'S', uiOpenBarckets ) );
							pActualPosition++;
							break;
						}//else
					}//else unknown operator
					if ( pPairOutEvalueStatus ){
						pPairOutEvalueStatus->first = false;
					}
					bGoOn = false;
				}break;
				case '*':{//multiply
					liOpenOperators.push_back( new cBinaryOperator( 'm', uiOpenBarckets ) );
				}break;
				case '/':{//divide
					liOpenOperators.push_back( new cBinaryOperator( 'd', uiOpenBarckets ) );
				}break;
				case '^':{//exponent
					liOpenOperators.push_back( new cBinaryOperator( 'e', uiOpenBarckets ) );
				}break;
				case 'p':{//exponent with "pow"
					if ( (*pActualPosition) == 'o' ){
						
						pActualPosition++;
						if ( (*pActualPosition) == 'w' ){
							//operator is exponent with "pow"
							liOpenOperators.push_back(
								new cBinaryOperator( 'e', uiOpenBarckets ) );
							pActualPosition++;
							break;
						}//else
					}//else unknown operator
					if ( pPairOutEvalueStatus ){
						pPairOutEvalueStatus->first = false;
					}
					bGoOn = false;
				}break;
				case 'P':{//constant "PI"
					if ( (*pActualPosition) == 'I' ){
						//operator is constant "PI"
						liOpenOperators.push_back(
							new cValueOperator( uiOpenBarckets, 3.141592653589793238462 ) );
						pActualPosition++;
						break;
					}//else unknown operator
					if ( pPairOutEvalueStatus ){
						pPairOutEvalueStatus->first = false;
					}
					bGoOn = false;
				}break;
				case 'e':{//constant "e"
					liOpenOperators.push_back(
						new cValueOperator( uiOpenBarckets, 2.718281828459045235360 ) );
				}break;
				case 'c':{//cosinus with "cos"
					if ( (*pActualPosition) == 'o' ){
						
						pActualPosition++;
						if ( (*pActualPosition) == 's' ){
							//operator is cosinus with "cos"
							liOpenOperators.push_back(
								new cUnaryOperator( 'C', uiOpenBarckets ) );
							pActualPosition++;
							break;
						}//else
					}//else unknown operator
					if ( pPairOutEvalueStatus ){
						pPairOutEvalueStatus->first = false;
					}
					bGoOn = false;
				}break;
				case 't':{//tangens with "tan"
					if ( (*pActualPosition) == 'a' ){
						
						pActualPosition++;
						if ( (*pActualPosition) == 'n' ){
							//operator is tangens with "tan"
							liOpenOperators.push_back(
								new cUnaryOperator( 'T', uiOpenBarckets ) );
							pActualPosition++;
							break;
						}//else
					}//else unknown operator
					if ( pPairOutEvalueStatus ){
						pPairOutEvalueStatus->first = false;
					}
					bGoOn = false;
				}break;
				case '%':{//modulo
					liOpenOperators.push_back(
						new cBinaryOperator( 'o', uiOpenBarckets ) );
				}break;
				default://unknown operator
					if ( pPairOutEvalueStatus ){
						pPairOutEvalueStatus->first = false;
					}
					bGoOn = false;
			};//end switch operators
		}
	}//end while go on
	
	if ( liOpenOperators.empty() ){
		//nothing on the list -> no function
		if ( pPairOutEvalueStatus ){
			pPairOutEvalueStatus->first  = false;
			pPairOutEvalueStatus->second = strDouble;
		}
		return 0.0;
	}
	
	//try to reduce listeded operators (evalue from the list begin)
	list< cOperator * >::iterator itrActualOperator = liOpenOperators.begin();
	list< cOperator * >::iterator itrPreviousOperator;
	list< cOperator * >::iterator itrNextOperator;
	
	while ( 1 < liOpenOperators.size() ){
		/*algorithm:
			- go to the next value operator (=operator with no missing sub
			operators in itself or a suboperator )
			possible valid cases:
			v=value operator (no suboperators open)
			V=selected value operator (no suboperators open)
			r=both sub operators open
			r=most right sub operator open
			l=most left sub operator open
			(note: before the first printed character no value operator exists;
				-> first character can't be a 'l' (most left sub operator open))
				...rV -> ...v
				...bV -> ...l
				Vb... -> r...
				...bVv... -> ...rv...
				...bV)l... -> ...rl...
				...b(Vl... -> ...bv...
				...bV)r... -> ...rr...
				...rV)b... -> ...vb...
				...r(Vb... -> ...rr...
		*/
		if ( (*itrActualOperator)->hasMissingSubOperators() ){
			//actual operator not a value operator -> check next operator
			itrActualOperator++;
			if ( itrActualOperator == liOpenOperators.end() ){
				/*list end was reached with no value operator found
				 -> chancel evaluation*/
				if ( pPairOutEvalueStatus ){
					pPairOutEvalueStatus->first = false;
				}
				break;
			}//else
			continue;
		}//else actual operator is a value operator
		itrNextOperator = itrActualOperator;
		itrNextOperator++;
		if ( itrNextOperator == liOpenOperators.end() ){
			/*no next operator -> add value to right side of previous operator
			valid cases:
				...rV -> ...v
				...bV -> ...l
			*/
			/*the list as minimum two elements and itrActualOperator is the last
			 -> there exists a previous operator*/
			itrPreviousOperator = itrActualOperator;
			itrPreviousOperator--;
			if ( (*itrPreviousOperator)->setMostRightOperator( *itrActualOperator ) ){
				//most right operator could be set -> erase inserted operator (itrActualOperator)
				liOpenOperators.erase( itrActualOperator );
				//check previous operator again
				itrActualOperator = itrPreviousOperator;
				continue;
			}else{//could not insert operator -> no valid formular
				if ( pPairOutEvalueStatus ){
					pPairOutEvalueStatus->first = false;
				}
				break;
			}
		}//else there is a next operator
		if ( itrActualOperator == liOpenOperators.begin() ){
			//valid case: Vb... -> r...
			if ( (*itrNextOperator)->setMostLeftOperator( *itrActualOperator ) ){
				//most left operator could be set -> erase inserted operator
				liOpenOperators.erase( itrActualOperator );
				//check next operator
				itrActualOperator = itrNextOperator;
				continue;
			}else{//could not insert -> no valid formular
				if ( pPairOutEvalueStatus ){
					pPairOutEvalueStatus->first = false;
				}
				break;
			}
		}//else actual operator has operator befor and after it
		itrPreviousOperator = itrActualOperator;
		itrPreviousOperator--;
		if ( ! (*itrNextOperator)->hasMissingSubOperators() ){
			/*valid cases:
				...bVv... -> ...rv...
				...rVv... -> ...vv...
			 */
			if ( (*itrPreviousOperator)->setMostLeftOperator( *itrActualOperator ) ){
				//erase inserted operator
				liOpenOperators.erase( itrActualOperator );
				//check previous operator
				itrActualOperator = itrPreviousOperator;
				continue;
			}else{//could not insert -> no valid formular
				//still try to reduce formular as much as possible (to get good result value)
				if ( (*itrPreviousOperator)->setMostRightOperator( *itrActualOperator ) ){
					//erase inserted operator
					liOpenOperators.erase( itrActualOperator );
					//check previous operator
					itrActualOperator = itrPreviousOperator;
					continue;
				}else{//could not insert -> no valid formular
					if ( pPairOutEvalueStatus ){
						pPairOutEvalueStatus->first = false;
					}
					break;
				}
			}
		}//else check which operator as precedence (previous or next operator)
		if ( (*itrPreviousOperator)->hasPrecedence( *itrNextOperator ) ){
			/*left operator as precedence, valid cases:
				...bV)l... -> ...rl...
				...bV)r... -> ...rr...
				...rV)b... -> ...vb...
			*/
			//try to insert as left operator ( ...bV)*... )
			if ( (*itrPreviousOperator)->setMostLeftOperator( *itrActualOperator ) ){
				//erase inserted operator
				liOpenOperators.erase( itrActualOperator );
				//check next operator
				itrActualOperator = itrPreviousOperator;
				continue;
			}else{//try to insert as right operator ( ...rV)b... -> ...vb... )
				if ( (*itrPreviousOperator)->setMostRightOperator( *itrActualOperator ) ){
					//erase inserted operator
					liOpenOperators.erase( itrActualOperator );
					//check next operator
					itrActualOperator = itrPreviousOperator;
					continue;
				}else{//could not insert -> no valid formular
					if ( pPairOutEvalueStatus ){
						pPairOutEvalueStatus->first = false;
					}
					break;
				}
			}
		}else{/*right operator as precedence, valid cases:
				...b(Vl... -> ...bv...
				...r(Vb... -> ...rr...
			*/
			if ( (*itrNextOperator)->setMostLeftOperator( *itrActualOperator ) ){
				//erase inserted operator
				liOpenOperators.erase( itrActualOperator );
				//check next operator
				itrActualOperator = itrNextOperator;
				continue;
			}else{//could not insert -> no valid formular
				if ( pPairOutEvalueStatus ){
					pPairOutEvalueStatus->first = false;
				}
				break;
			}
		}
	}//end while reduce operands
	
	//evalue value of the function (value of first operator in the list)
	const doubleFib dEvaluedValue = liOpenOperators.front()->getValue();
	
	if ( pPairOutEvalueStatus ){
		//evalue status
		pPairOutEvalueStatus->first &= ( liOpenOperators.size() == 1 );
		
		//the formular could be evalued till the actual position
		pPairOutEvalueStatus->second = pActualPosition;
	}
	
	//delete all the operators on the operator list
	for ( itrActualOperator = liOpenOperators.begin();
			itrActualOperator != liOpenOperators.end(); itrActualOperator++ ){
		//delete actual entry
		delete (*itrActualOperator);
	}
	return dEvaluedValue;
}


/**
 * This method stores the given double number in XML -format into the
 * given stream.
 * The output is in a form that can be readed by readDoubleFromFunction().
 * Also (if possible) no precision will be lost.
 *
 * @see readDoubleFromFunction()
 * @param stream the stream where the number should be stored to
 * @param dValueToStore the double Fib number to store
 */
void fib::storeXmlDoubleFib( std::ostream & stream,
		const doubleFib & dValueToStore ){
	
	if ( ( -1000000 < dValueToStore ) && ( dValueToStore < 1000000 ) &&
			( (((doubleFib)((longFib)( dValueToStore * 100.0 ))) / 100.0) == dValueToStore ) ){
		//number with no more than 6 digits before and 2 digits after the point
		stream.precision( 9 );
		stream<< dValueToStore;
	}else{//split into mantissa and exponent (base 2) and store them
		longFib lMantissa;
		longFib lExponent;
		
		decomposeDoubleFib( dValueToStore, & lMantissa, & lExponent );
		
		stream<< lMantissa <<" * 2^("<< lExponent <<")";
	}
}












