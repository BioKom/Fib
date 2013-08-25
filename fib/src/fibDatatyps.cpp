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
*/

#include "fibDatatyps.h"

#include <cmath>


using namespace fib;


/**
 * This function evalues the digits needed to store a value as an
 * natural number.
 *
 * @param uiValue the value to evalue the digits for
 * @return the digits needed to store a value as an natural number
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
			
		if ( (uiValue & 0x01) != 0 ){
			//digit found
			uiDigits = iActualDigit;
		}
		if ( (uiValue & 0x02) != 0 ){
			//digit found
			uiDigits = iActualDigit + 1;
		}
		if ( (uiValue & 0x04) != 0 ){
			//digit found
			uiDigits = iActualDigit + 2;
		}
		if ( (uiValue & 0x08) != 0 ){
			//digit found
			uiDigits = iActualDigit + 3;
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
 * This function evalues the digits needed to store a value as an
 * natural number.
 *
 * @param ulValue the value to evalue the digits for
 * @return the digits needed to store a value as an natural number
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
			
		if ( (ulValue & 0x01) != 0 ){
			//digit found
			uiDigits = iActualDigit;
		}
		if ( (ulValue & 0x02) != 0 ){
			//digit found
			uiDigits = iActualDigit + 1;
		}
		if ( (ulValue & 0x04) != 0 ){
			//digit found
			uiDigits = iActualDigit + 2;
		}
		if ( (ulValue & 0x08) != 0 ){
			//digit found
			uiDigits = iActualDigit + 3;
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
 * This function evalues the digits needed to store a value as an
 * natural number.
 *
 * @param llValue the value to evalue the digits for
 * @return the digits needed to store a value as an natural number
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
			
		if ( (llValue & 0x01) != 0 ){
			//digit found
			uiDigits = iActualDigit;
		}
		if ( (llValue & 0x02) != 0 ){
			//digit found
			uiDigits = iActualDigit + 1;
		}
		if ( (llValue & 0x04) != 0 ){
			//digit found
			uiDigits = iActualDigit + 2;
		}
		if ( (llValue & 0x08) != 0 ){
			//digit found
			uiDigits = iActualDigit + 3;
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
				
			if ( (iValue & 0x01) != 0 ){
				//digit found
				uiDigits = iActualDigit;
			}
			if ( (iValue & 0x02) != 0 ){
				//digit found
				uiDigits = iActualDigit + 1;
			}
			if ( (iValue & 0x04) != 0 ){
				//digit found
				uiDigits = iActualDigit + 2;
			}
			if ( (iValue & 0x08) != 0 ){
				//digit found
				uiDigits = iActualDigit + 3;
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
				
			if ( (iValue & 0x01) == 0 ){
				//digit found
				uiDigits = iActualDigit;
			}
			if ( (iValue & 0x02) == 0 ){
				//digit found
				uiDigits = iActualDigit + 1;
			}
			if ( (iValue & 0x04) == 0 ){
				//digit found
				uiDigits = iActualDigit + 2;
			}
			if ( (iValue & 0x08) == 0 ){
				//digit found
				uiDigits = iActualDigit + 3;
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
				
			if ( (lValue & 0x01) != 0 ){
				//digit found
				uiDigits = iActualDigit;
			}
			if ( (lValue & 0x02) != 0 ){
				//digit found
				uiDigits = iActualDigit + 1;
			}
			if ( (lValue & 0x04) != 0 ){
				//digit found
				uiDigits = iActualDigit + 2;
			}
			if ( (lValue & 0x08) != 0 ){
				//digit found
				uiDigits = iActualDigit + 3;
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
				
			if ( (lValue & 0x01) == 0 ){
				//digit found
				uiDigits = iActualDigit;
			}
			if ( (lValue & 0x02) == 0 ){
				//digit found
				uiDigits = iActualDigit + 1;
			}
			if ( (lValue & 0x04) == 0 ){
				//digit found
				uiDigits = iActualDigit + 2;
			}
			if ( (lValue & 0x08) == 0 ){
				//digit found
				uiDigits = iActualDigit + 3;
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
				
			if ( (llValue & 0x01) != 0 ){
				//digit found
				uiDigits = iActualDigit;
			}
			if ( (llValue & 0x02) != 0 ){
				//digit found
				uiDigits = iActualDigit + 1;
			}
			if ( (llValue & 0x04) != 0 ){
				//digit found
				uiDigits = iActualDigit + 2;
			}
			if ( (llValue & 0x08) != 0 ){
				//digit found
				uiDigits = iActualDigit + 3;
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
				
			if ( (llValue & 0x01) == 0 ){
				//digit found
				uiDigits = iActualDigit;
			}
			if ( (llValue & 0x02) == 0 ){
				//digit found
				uiDigits = iActualDigit + 1;
			}
			if ( (llValue & 0x04) == 0 ){
				//digit found
				uiDigits = iActualDigit + 2;
			}
			if ( (llValue & 0x08) == 0 ){
				//digit found
				uiDigits = iActualDigit + 3;
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
	
	if ( dNumber == (double)(1.0) ){
		(*lMantissa) = 1;
		(*lExponent) = 0;
		
		if (iSizeMantissa != NULL){
			(*iSizeMantissa) = 2;
		}
		if (iSizeExponent != NULL){
			(*iSizeExponent) = 1;
		}
	}
	
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
	
	unsigned int uiDigitsMantissa = 0;
	unsigned int uiDigitsExponent = 0;
	
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
			uiDigitsMantissa = getDigits( llMantissa );
		}
		if ( iSizeExponent != NULL ){
			//evalue the digits in the exponent
			uiDigitsExponent = getDigits( iExponent );
		}
	
	}else{
		iExponent = 0;
	}
	//transfer the evauled numbers to the output valus
	if ( lMantissa != NULL ){
		(*lMantissa) = llMantissa;
	}
	if ( lMantissa != NULL ){
		(*lExponent) = iExponent;
	}
	if ( iSizeMantissa != NULL ){
		(*iSizeMantissa) = uiDigitsMantissa;
	}
	if ( iSizeExponent != NULL ){
		(*iSizeExponent) = uiDigitsExponent;
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
	//bring first mantissa bit to the bit 52
	unsigned int iExponent = lExponent + 1075; //1075 = (1023 + 52);
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









