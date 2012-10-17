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
*/

#include "fibDatatyps.h"

using namespace fib;


/**
 * This function evalues the digits needed to store a value as an
 * natural number.
 *
 * @param llValue the value to evalue the digits for
 * @return the digits needed to store a value as an natural number
 */
unsigned int fib::getDigits( unsigned long long llValue ){

	unsigned int uiDigits = 0;
	
	if ( llValue == 0 ){
		//no digits needed to store value
		return 0;
	}
	
	for ( unsigned int iActualDigit = 1; iActualDigit <= 64;
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
 * Decompses a doubleFib number into it's mantissa and exponent part.
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
void fib::decomposeDoubleFib( const doubleFib dNumber,
	longFib * lMantissa, longFib * lExponent,
	intFib * iSizeMantissa , intFib * iSizeExponent ){
	
	if ( dNumber == (doubleFib)(1.0) ){
		(*lMantissa) = 1;
		(*lExponent) = 0;
		
		if (iSizeMantissa != NULL){
			(*iSizeMantissa) = 2;
		}
		if (iSizeExponent != NULL){
			(*iSizeExponent) = 1;
		}
	}
	
	//get the sign; it's the bit 63
	unsigned char* c = (unsigned char*)&dNumber;
	int sign = 0x80 & c[7];
	
	//get the exponent; its the bit 52 till 62
	int iExponent = 0x7F & c[7];
	iExponent = iExponent << 8;
	iExponent += 0xF0 & c[6];
	iExponent = iExponent >> 4;
		
	//get the matissa; its the bit 0 till 51
	long long llMantissa;
	if ( iExponent != 0 ){
		iExponent += -1023 - 52;
		llMantissa = 0x10 | (0x0F & c[6]);
	}else{
		iExponent = -1022 - 52;
		llMantissa = (0x0F & c[6]);
	}
	llMantissa = llMantissa << 8;
	llMantissa += c[5];
	llMantissa = llMantissa << 8;
	llMantissa += c[4];
	llMantissa = llMantissa << 8;
	llMantissa += c[3];
	llMantissa = llMantissa << 8;
	llMantissa += c[2];
	llMantissa = llMantissa << 8;
	llMantissa += c[1];
	llMantissa = llMantissa << 8;
	llMantissa += c[0];
	
	unsigned int uiDigitsMantissa = 0;
	unsigned int uiDigitsExponent = 0;
	
	if ( llMantissa != 0 ){
		while ( (llMantissa & 0x01) == 0x00 ) {
			llMantissa = llMantissa >> 1;
			iExponent++;
		}
		
		if ( iSizeMantissa != NULL ){
			//evalue the digits in the mantissa
			uiDigitsMantissa = getDigits( llMantissa );
			
			//add digit for sign
			uiDigitsMantissa++;
		}
		
		if ( iSizeExponent != NULL ){
			//evalue the digits in the exponent
			//to evalue the digits a positiv number is needed
			unsigned int uiExponent;
			if ( iExponent >= 0 ){
				uiExponent = iExponent;
			}else{//negativ exponent
				uiExponent = -1.0 * iExponent;
			}
			
			uiDigitsExponent = getDigits( uiExponent );
			
			//add digit for sign
			uiDigitsExponent++;
		}
	
	}else{
		iExponent=0;
	}
	
	//add mantissa sign
	if ( sign != 0 ){
		//the mantissa is negativ
		llMantissa *= -1.0;
	}//the mantissa is positiv
	
	
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

	return (0.0 <= dValue)? dValue : dValue * ((float)(-1.0));
}

/**
 * @param dValue the value, for which to evalue the positiv value
 * @return the positive value for the given number dValue
 */
double fib::absF( const double & dValue ){

	return (0.0 <= dValue)? dValue : dValue * ((double)(-1.0));
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









