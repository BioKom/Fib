
//TODO check

/**
 * @file tFibDatatyps
 * file name: tFibDatatyps.cpp
 * @author Betti Oesterholz
 * @date 11.05.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for testing the fibDatatyps functions.
 *
 * Copyright (C) @c GPL3 2013 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This test is for testing the fibDatatyps functions.
 *
 *
 * call: tFibDatatyps [MAX_ITERATION]
 *
 * parameters:
 * 	MAX_ITERATION
 * 		The number of iterators for the random tests (test with given
 * 		parameters for convertToTiles()).
 * 		Just works with the DIR_TESTDATA parameter given.
 *
 *
 * Methods tested:
 * 	- longFib roundToLongFib( const Type &value )
 * 	-(TODO) Type max( const Type &value1, const Type &value2 )
 * 	-(TODO) std::list< Type >::iterator getListElement( std::list< Type > & liList, unsigned long ulElementNumber )
 * 	-(TODO) std::list< Type >::const_iterator getListElement( const std::list< Type > & liList, unsigned long ulElementNumber )
 * 	- int getDigits( unsigned int llValue )
 * 	- int getDigits( unsigned long llValue )
 * 	- int getDigits( int llValue )
 * 	- int getDigits( long llValue )
 * 	- int getDigits( long long llValue )
 * 	- void decomposeDoubleFib( const double dNumber, longFib * lMantissa, longFib * lExponent, intFib * iSizeMantissa = NULL, intFib * iSizeExponent = NULL )
 * 	- double composeDoubleFib( const longFib & lMantissa, const longFib & lExponent )
 * 	-(TODO) unsigned long roundUpToFullByte( unsigned long ulNumberOfBits );
 * 	-(TODO) doubleFib gcd( doubleFib dValue1, doubleFib dValue2 );
 * 	-(TODO) float absF( const float & dValue );
 * 	-(TODO) double absF( const double & dValue );
 * 	-(TODO) bool isEqualNull( const double & dValue );
 * 	-(TODO) bool isEqualNull( const float & dValue );
 * 	-(TODO) bool compareDouble( const double & dValue1, const double & dValue2 );
 * 	-(TODO) bool compareDouble( const float & dValue1, const float & dValue2 );
 * 	-(TODO) bool compareVectorDouble( const std::vector< tDouble > & vector1, const std::vector< tDouble > & vector2 )
 * 	-(TODO) tDouble add( const tDouble & dValue1, const tDouble & dValue2 )
 * 	-(TODO) tDouble sub( const tDouble & dValue1, const tDouble & dValue2 )
 * 	-(TODO) tDouble addToFirst( tDouble & dValue1, const tDouble & dValue2 )
 * 	-(TODO) tDouble subFromFirst( tDouble & dValue1, const tDouble & dValue2 )
 * 	-(TODO) std::vector< tDouble > addToFirst( std::vector< tDouble > & vecValue1, const std::vector< tDouble > & vecValue2 )
 * 	-(TODO) std::vector< tDouble > multToFirst( std::vector< tDouble > & vecValue, const tDouble & dValue )
 *
 */
/*
History:
11.05.2013  Oesterholz  created
*/


#include "version.h"
#include "fibDatatyps.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <list>
#include <vector>
#include <algorithm>
#include <cmath>


using namespace fib;
using namespace std;


unsigned long MAX_ITERATION = 1024;



int testRoundToLongFibFunction( unsigned long &ulTestphase );
int testGetDigitsFunction( unsigned long &ulTestphase );
int testComposeDoubleFibFunctions( unsigned long &ulTestphase );


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test
	int iReturn = 0;//return value of the test; the number of occured Errors
	
	srand( time(NULL) );
	
	cout<<endl<<"Running Test for the fibDatatyps functions"<<endl;
	cout<<      "=========================================="<<endl;
	cout<<      "=========================================="<<endl;
	
	if ( 1 < argc ){
		//two parameters given; read parameter iterators
		MAX_ITERATION = atol( argv[1] );
		if ( MAX_ITERATION < 1 ){
			MAX_ITERATION = 1;
		}
	}
	cout<<endl<<"Number of maximal iterators is "<<MAX_ITERATION<<endl;
	
	
	//test the fibDatatyps functions
	
	//TODO more test
	
	iReturn += testRoundToLongFibFunction( ulTestphase );
	iReturn += testGetDigitsFunction( ulTestphase );
	iReturn += testComposeDoubleFibFunctions( ulTestphase );
	
	
	
	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	
	return iReturn;
}



/**
 * @param dValue the value to check
 * @return true if the value is not a number, else false
 */
inline bool own_isnan( doubleFib dValue ){
    return dValue != dValue;
}


/**
 * @param dValue the value to check
 * @return true if the value is infinity, else false
 */
inline bool own_isinf( doubleFib dValue ){
    return ( ( dValue == INFINITY ) || ( dValue == -INFINITY ) );
}


/**
 * This function compares two values with a given savety boundery.
 *
 * @param dValue1 the first value to compare
 * @param dValue2 the second value to compare
 * @param dPrecision the precision of the comparrisson
 * @return true if the values are very simular
 */
bool isEqual( const doubleFib dValue1, const doubleFib dValue2,
		const doubleFib dPrecision = 0.000001 ){

	if ( own_isnan( dValue1 ) || own_isnan( dValue2 ) ){
		if ( own_isnan( dValue1 ) && own_isnan( dValue2 ) ){
			return true;
		}
		return false;
	}
	if ( own_isinf( dValue1 ) || own_isinf( dValue2 ) ){
		if ( own_isinf( dValue1 ) && own_isinf( dValue2 ) ){
			return true;
		}
		return false;
	}
	
	const doubleFib dSaveBoundery1 = abs( dValue1 * dPrecision );
	const doubleFib dSaveBoundery2 = abs( dValue2 * dPrecision );
	const doubleFib dSaveBoundery  = min( dSaveBoundery1, dSaveBoundery2 );
	
	if ( ( dValue1 - dSaveBoundery <= dValue2 ) &&
			( dValue2 <= dValue1 + dSaveBoundery ) ){
		return true;
	}
	return false;
}

/**
 * @return a random double number
 */
double generateRandomDouble(){
	
	return ( ( ((double)(rand())) * ((double)(rand())) + ((double)(rand())) -
			((double)(rand())) * ((double)(rand())) ) ) /
		((double)(rand()));
}


/**
 * This function writes the bits of the double to the given stream.
 *
 * @param stream the stream wher to write to
 * @param dValue the double to write the bits of
 */
void writeBitsDouble( ostream & stream, const double dValue ){
	
	unsigned long long llValue = *((unsigned long long*)(&dValue ));
	
	for ( unsigned int uiBit = 0; uiBit < 64; uiBit++ ){
		if ( ( uiBit == 52 ) || ( uiBit == 63 ) ){
			//print a space betwaen the double Fib parts
			stream<<" ";
		}
		stream<<(( (llValue & 0x01) == 0x01 ) ? "1" : "0");
		llValue = llValue >> 1;
	}
}


/**
 * This function writes the bits of the double to the given stream.
 *
 * @param stream the stream wher to write to
 * @param dValue the double to write the bits of
 */
void writeBitsLongLong( ostream & stream, const long long llValue,
		const unsigned int uiBitsToWrite = 64 ){
	
	unsigned long long ullValue = *((unsigned long long*)(&llValue ));
	
	for ( unsigned int uiBit = 0; uiBit < uiBitsToWrite; uiBit++ ){
		
		stream<<(( (ullValue & 0x01) == 0x01 ) ? "1" : "0");
		ullValue = ullValue >> 1;
	}
}





/**
 * This function tests the roundToLongFib() function.
 *
 * Methods tested:
 * 	- longFib roundToLongFib( const Type &value )
 *
 * @param ulTestphase a reference to the number for the test phase
 * @return the number of errors occured in the test
 */
int testRoundToLongFibFunction( unsigned long &ulTestphase ){
	
	int iReturn = 0;//return value of the test; the number of occured errors
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing roundToLongFib() function"<<endl;
	
	for ( unsigned int uiActualIteration = 0;
			uiActualIteration < MAX_ITERATION; uiActualIteration++ ){
		cout<<endl;
		//generate random correct number
		const longFib lCorrectNumber = ( rand() * rand() ) -
			( rand() * rand() ) + rand();
		
		const double dNumberToRound = ((double)lCorrectNumber) +
			((double)( ( rand() % 9998 ) - 4999 )) / 10000.0;
		
		const longFib lRoundedNumber = roundToLongFib( dNumberToRound );
		cout<<"roundToLongFib( dNumberToRound="<<dNumberToRound<<
			" )="<<lRoundedNumber<<endl;
		
		if ( lRoundedNumber != lCorrectNumber ){
			cerr<<"Error: The returned number "<<lRoundedNumber<<
				" is not equal the correct number "<<lCorrectNumber<<" ."<<endl;
			iReturn++;
		}
	}//end iterate random test

	
	return iReturn;
}



/**
 * This function tests the getDigits() function.
 *
 * Methods tested:
 * 	- int getDigits( unsigned int llValue )
 * 	- int getDigits( unsigned long llValue )
 * 	- int getDigits( int llValue )
 * 	- int getDigits( long llValue )
 * 	- int getDigits( long long llValue )
 *
 * @param ulTestphase a reference to the number for the test phase
 * @return the number of errors occured in the test
 */
int testGetDigitsFunction( unsigned long &ulTestphase ){
	
	int iReturn = 0;//return value of the test; the number of occured errors
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing getDigits() function"<<endl;
	
	for ( unsigned int uiActualIteration = 0;
			uiActualIteration < MAX_ITERATION; uiActualIteration++ ){
		cout<<endl;
		//generate last bit position
		const int uiLastSetBit = rand() % (sizeof(unsigned int));
		
		unsigned long uiNumberToTest = 0;
		if ( 0 < uiLastSetBit ){
			uiNumberToTest = 1;
			for ( int iActualBit = 1; iActualBit < uiLastSetBit; iActualBit++ ){
				uiNumberToTest = uiNumberToTest << 1;
				uiNumberToTest |= ( rand() % 2 ) ? 0x0L : 0x1L;
			}
		}
		const int iDigitsEvalued = getDigits( uiNumberToTest );
		cout<<"getDigits( uiNumberToTest=";
		writeBitsLongLong( cout, uiNumberToTest );
		cout<<" )="<<iDigitsEvalued<<endl;
		
		if ( iDigitsEvalued != uiLastSetBit ){
			cerr<<"Error: The returned digits "<<iDigitsEvalued<<
				" is not equal the last set bit "<<uiLastSetBit<<" ."<<endl;
			iReturn++;
		}
		
	}//end iterate random test
	for ( unsigned int uiActualIteration = 0;
			uiActualIteration < MAX_ITERATION; uiActualIteration++ ){
		cout<<endl;
		//generate last bit position
		const int uiLastSetBit = rand() % (sizeof(unsigned long));
		
		unsigned long ulNumberToTest = 0;
		if ( 0 < uiLastSetBit ){
			ulNumberToTest = 1;
			for ( int iActualBit = 1; iActualBit < uiLastSetBit; iActualBit++ ){
				ulNumberToTest = ulNumberToTest << 1;
				ulNumberToTest |= ( rand() % 2 ) ? 0x0L : 0x1L;
			}
		}
		const int iDigitsEvalued = getDigits( ulNumberToTest );
		cout<<"getDigits( ulNumberToTest=";
		writeBitsLongLong( cout, ulNumberToTest );
		cout<<" )="<<iDigitsEvalued<<endl;
		
		if ( iDigitsEvalued != uiLastSetBit ){
			cerr<<"Error: The returned digits "<<iDigitsEvalued<<
				" is not equal the last set bit "<<uiLastSetBit<<" ."<<endl;
			iReturn++;
		}
		
	}//end iterate random test
	for ( unsigned int uiActualIteration = 0;
			uiActualIteration < MAX_ITERATION; uiActualIteration++ ){
		cout<<endl;
		//generate last bit position
		const int uiLastSetBit = rand() % (sizeof(unsigned long long));
		
		unsigned long long ullNumberToTest = 0;
		if ( 0 < uiLastSetBit ){
			ullNumberToTest = 1;
			for ( int iActualBit = 1; iActualBit < uiLastSetBit; iActualBit++ ){
				ullNumberToTest = ullNumberToTest << 1;
				ullNumberToTest |= ( rand() % 2 ) ? 0x0L : 0x1L;
			}
		}
		const int iDigitsEvalued = getDigits( ullNumberToTest );
		cout<<"getDigits( ullNumberToTest=";
		writeBitsLongLong( cout, ullNumberToTest );
		cout<<" )="<<iDigitsEvalued<<endl;
		
		if ( iDigitsEvalued != uiLastSetBit ){
			cerr<<"Error: The returned digits "<<iDigitsEvalued<<
				" is not equal the last set bit "<<uiLastSetBit<<" ."<<endl;
			iReturn++;
		}
		
	}//end iterate random test
	
	for ( unsigned int uiActualIteration = 0;
			uiActualIteration < MAX_ITERATION; uiActualIteration++ ){
		cout<<endl;
		//generate last bit position
		const int uiLastSetBit = rand() % (sizeof(int) - 1);
		
		int iNumberToTest = 0;
		if ( 0 < uiLastSetBit ){
			iNumberToTest = 1;
			for ( int iActualBit = 1; iActualBit < uiLastSetBit; iActualBit++ ){
				iNumberToTest = iNumberToTest << 1;
				iNumberToTest |= ( rand() % 2 ) ? 0x0L : 0x1L;
			}
		}
		if ( ( rand() % 2 ) == 0 ){
			iNumberToTest = ~iNumberToTest;
		}
		const int iDigitsEvalued = getDigits( iNumberToTest );
		cout<<"getDigits( iNumberToTest=";
		writeBitsLongLong( cout, iNumberToTest );
		cout<<" )="<<iDigitsEvalued<<endl;
		
		if ( iNumberToTest != 0 ){
			if ( iDigitsEvalued != ( uiLastSetBit + 1 ) ){
				cerr<<"Error: The returned digits "<<iDigitsEvalued<<
					" is not equal the last set bit "<<uiLastSetBit<<" + 1 ."<<endl;
				iReturn++;
			}
		}else{
			if ( iDigitsEvalued != 0 ){
				cerr<<"Error: The returned digits "<<iDigitsEvalued<<
					" should be 0, because no bit was set."<<endl;
				iReturn++;
			}
		}
	}//end iterate random test
	for ( unsigned int uiActualIteration = 0;
			uiActualIteration < MAX_ITERATION; uiActualIteration++ ){
		cout<<endl;
		//generate last bit position
		const int uiLastSetBit = rand() % (sizeof(long) - 1);
		
		long lNumberToTest = 0;
		if ( 0 < uiLastSetBit ){
			lNumberToTest = 1;
			for ( int iActualBit = 1; iActualBit < uiLastSetBit; iActualBit++ ){
				lNumberToTest = lNumberToTest << 1;
				lNumberToTest |= ( rand() % 2 ) ? 0x0L : 0x1L;
			}
		}
		if ( ( rand() % 2 ) == 0 ){
			lNumberToTest = ~lNumberToTest;
		}
		const int iDigitsEvalued = getDigits( lNumberToTest );
		cout<<"getDigits( lNumberToTest=";
		writeBitsLongLong( cout, lNumberToTest );
		cout<<" )="<<iDigitsEvalued<<endl;
		
		if ( lNumberToTest != 0 ){
			if ( iDigitsEvalued != ( uiLastSetBit + 1 ) ){
				cerr<<"Error: The returned digits "<<iDigitsEvalued<<
					" is not equal the last set bit "<<uiLastSetBit<<" + 1 ."<<endl;
				iReturn++;
			}
		}else{
			if ( iDigitsEvalued != 0 ){
				cerr<<"Error: The returned digits "<<iDigitsEvalued<<
					" should be 0, because no bit was set."<<endl;
				iReturn++;
			}
		}
	}//end iterate random test
	for ( unsigned int uiActualIteration = 0;
			uiActualIteration < MAX_ITERATION; uiActualIteration++ ){
		cout<<endl;
		//generate last bit position
		const int uiLastSetBit = rand() % (sizeof(long long) - 1);
		
		long long llNumberToTest = 0;
		if ( 0 < uiLastSetBit ){
			llNumberToTest = 1;
			for ( int iActualBit = 1; iActualBit < uiLastSetBit; iActualBit++ ){
				llNumberToTest = llNumberToTest << 1;
				llNumberToTest |= ( rand() % 2 ) ? 0x0L : 0x1L;
			}
		}
		if ( ( rand() % 2 ) == 0 ){
			llNumberToTest = ~llNumberToTest;
		}
		const int iDigitsEvalued = getDigits( llNumberToTest );
		cout<<"getDigits( llNumberToTest=";
		writeBitsLongLong( cout, llNumberToTest );
		cout<<" )="<<iDigitsEvalued<<endl;
		
		if ( llNumberToTest != 0 ){
			if ( iDigitsEvalued != ( uiLastSetBit + 1 ) ){
				cerr<<"Error: The returned digits "<<iDigitsEvalued<<
					" is not equal the last set bit "<<uiLastSetBit<<" + 1 ."<<endl;
				iReturn++;
			}
		}else{
			if ( iDigitsEvalued != 0 ){
				cerr<<"Error: The returned digits "<<iDigitsEvalued<<
					" should be 0, because no bit was set."<<endl;
				iReturn++;
			}
		}
	}//end iterate random test
	
	
	return iReturn;
}



/**
 * This function tests the decomposeDoubleFib() and composeDoubleFib() functions.
 *
 * Methods tested:
 * 	- void decomposeDoubleFib( const double dNumber, longFib * lMantissa, longFib * lExponent, intFib * iSizeMantissa = NULL, intFib * iSizeExponent = NULL )
 * 	- double composeDoubleFib( const longFib & lMantissa, const longFib & lExponent )
 *
 * @param ulTestphase a reference to the number for the test phase
 * @return the number of errors occured in the test
 */
int testComposeDoubleFibFunctions( unsigned long &ulTestphase ){
	
	int iReturn = 0;//return value of the test; the number of occured errors
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing decomposeDoubleFib() and composeDoubleFib() a double number"<<endl;
	
	for ( unsigned int uiActualIteration = 0;
			uiActualIteration < MAX_ITERATION; uiActualIteration++ ){
		cout<<endl;
		//generate random double number
		const double dNumberToTest = generateRandomDouble();
		longFib lMantissa;
		longFib lExponent;
		intFib iSizeMantissa;
		intFib iSizeExponent;
		decomposeDoubleFib( dNumberToTest, &lMantissa, &lExponent,
			&iSizeMantissa, &iSizeExponent );
		cout<<"decomposeDoubleFib( dNumberToTest="<<dNumberToTest<<
			", &lMantissa="<<lMantissa<<", &lExponent="<<lExponent<<
			", &iSizeMantissa="<<iSizeMantissa<<", &iSizeExponent="<<iSizeExponent<<" )"<<endl;
		
		/*
		cerr<<      "   Bits      dNumberToTest: ";
		writeBitsDouble( cerr, dNumberToTest );
		cerr<<endl<<"   Bits      lMantissa    : ";
		writeBitsLongLong( cerr, lMantissa, 54 ); cout<<endl;
		*/
		
		//check values
		const double dEvaluedValue = ((long double)lMantissa) *
			pow( ((long double)2.0), lExponent );
		if ( ! isEqual( dNumberToTest, dEvaluedValue ) ){
			cerr<<"Error: The returned values evalue to a wrong value "<<dEvaluedValue<<
				" (lMantissa * pow( 2.0, lExponent )), but it should be "<<dNumberToTest<<" ."<<endl;
			iReturn++;
		}
		
		if ( iSizeMantissa != ((intFib)getDigits( lMantissa )) ){
			cerr<<"Error: The returned mantissa size "<<iSizeMantissa<<
				" is wrong, should be "<<(getDigits( lMantissa ) )<<"."<<endl;
			cerr<<"Bits lMantissa: ";
			writeBitsLongLong( cerr, lMantissa, 54 ); cout<<endl;
			iReturn++;
		}
		if ( iSizeExponent != ((intFib)getDigits( lExponent )) ){
			cerr<<"Error: The returned exponent size "<<iSizeExponent<<
				" is wrong, should be "<<(getDigits( lExponent ) )<<"."<<endl;
			cerr<<"Bits lExponent: ";
			writeBitsLongLong( cerr, lExponent, 11 ); cout<<endl;
			iReturn++;
		}
		/*TODO weg
		if ( 0 <= lMantissa ){*/
			if ( ( lMantissa & 0x01 ) == 0x00 ){
				cerr<<"Error: The returned mantissa "<<lMantissa<<
					" has not 1 as the first bit."<<endl;
				cerr<<      "   Bits      lMantissa    : ";
				writeBitsLongLong( cerr, lMantissa, 54 );
				cerr<<endl<<"   Bits      dNumberToTest: ";
				writeBitsDouble( cerr, dNumberToTest );
				cerr<<endl;
				iReturn++;
			}
		/*TODO weg
		}else{// ( lMantissa < 0 )
			if ( ( lMantissa & 0x01 ) == 0x00 ){
				cerr<<"Error: The returned mantissa "<<lMantissa<<
					" has not 0 as the first bit."<<endl;
				cerr<<      "   Bits      lMantissa    : ";
				writeBitsLongLong( cerr, lMantissa, 54 );
				cerr<<endl<<"   Bits      dNumberToTest: ";
				writeBitsDouble( cerr, dNumberToTest );
				cerr<<endl;
				iReturn++;
			}
		}*/
		
		const double dComposedValue = composeDoubleFib( lMantissa, lExponent );
		cout<<"composeDoubleFib( lMantissa="<<lMantissa<<", lExponent="<<lExponent<<" )="<<dComposedValue<<endl;
		
		if ( dComposedValue != dNumberToTest ){
			cerr<<"Error: composeDoubleFib() returns (dComposedValue="<<dComposedValue<<
				") a different number to the "<<
				"number given to decomposeDoubleFib() (dNumberToTest="<<dNumberToTest<<")."<<endl;
			cerr<<      "   Bits      dNumberToTest: ";
			writeBitsDouble( cerr, dNumberToTest );
			cerr<<endl<<"   Bits composeDoubleFib(): ";
			writeBitsDouble( cerr, dComposedValue );
			cerr<<endl<<"   Bits      lMantissa    : ";
			writeBitsLongLong( cerr, lMantissa, 54 );
			cerr<<endl<<"   Bits      lExponent    : ";
			writeBitsLongLong( cerr, lExponent, 11 );
			cerr<<endl;
			iReturn++;
		}
		
		longFib lMantissa2;
		longFib lExponent2;
		decomposeDoubleFib( dComposedValue, &lMantissa2, &lExponent2 );
		cout<<"decomposeDoubleFib( dComposedValue="<<dComposedValue<<
			", &lMantissa2="<<lMantissa2<<", &lExponent2="<<lExponent2<<" )"<<endl;
		if ( lMantissa != lMantissa2 ){
			cerr<<"Error: The returned mantissa "<<lMantissa2<<
				" changed to the first call "<<lMantissa<<" ."<<endl;
			cerr<<"Bits lMantissa2: ";
			writeBitsLongLong( cerr, lMantissa2, 54 ); cout<<endl;
			iReturn++;
		}
		if ( lExponent != lExponent2 ){
			cerr<<"Error: The returned exponent "<<lExponent2<<
				" changed to the first call "<<lExponent<<" ."<<endl;
			iReturn++;
		}
		
		longFib lMantissa3;
		longFib lExponent3;
		intFib iSizeMantissa3;
		decomposeDoubleFib( dComposedValue, &lMantissa3, &lExponent3, &iSizeMantissa3 );
		cout<<"decomposeDoubleFib( dComposedValue="<<dComposedValue<<
			", &lMantissa3="<<lMantissa3<<", &lExponent3="<<lExponent3<<
			", &iSizeMantissa3="<<iSizeMantissa3<<" )"<<endl;
		if ( lMantissa != lMantissa3 ){
			cerr<<"Error: The returned mantissa "<<lMantissa3<<
				" changed to the first call "<<lMantissa<<" ."<<endl;
			iReturn++;
		}
		if ( lExponent != lExponent3 ){
			cerr<<"Error: The returned exponent "<<lExponent3<<
				" changed to the first call "<<lExponent<<" ."<<endl;
			iReturn++;
		}
		if ( iSizeMantissa != iSizeMantissa3 ){
			cerr<<"Error: The returned mantissa size "<<iSizeMantissa3<<
				" changed to the first call "<<iSizeMantissa<<" ."<<endl;
			iReturn++;
		}
		
	}//end iterate random test
	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing composeDoubleFib() and decomposeDoubleFib() a double number"<<endl;
	for ( unsigned int uiActualIteration = 0;
			uiActualIteration < MAX_ITERATION; uiActualIteration++ ){
		cout<<endl;
		//generate random mantissa and exponent number
		const long lMantissa = ( ((long)( rand() % 32767 )) * ((long)( rand() % 32767 )) ) +
			((long)( rand() % 32767 )) -
			( ((long)( rand() % 32767 )) * ((long)( rand() % 32767 )) );
		const long lExponent = (lMantissa == 0) ? 1 : ( rand() % 1800 ) - 900;
		
		const double dComposedValue = composeDoubleFib( lMantissa, lExponent );
		cout<<"composeDoubleFib( lMantissa="<<lMantissa<<", lExponent="<<lExponent<<" )="<<dComposedValue<<endl;
		
		/*TODO precision of pow not hight enougt?*/
		const double dEvaluedValue = ((long double)lMantissa) *
			pow( ((long double)2.0), lExponent );
		if ( ! isEqual( dComposedValue, dEvaluedValue ) ){
			cerr<<"Error: The given values evalue to the value "<<dEvaluedValue<<
				" (lMantissa * pow( 2.0, lExponent )), but "<<dComposedValue<<" was returned."<<endl;
			iReturn++;
		}
		
		
		longFib lMantissa2;
		longFib lExponent2;
		intFib iSizeMantissa2;
		intFib iSizeExponent2;
		decomposeDoubleFib( dComposedValue, &lMantissa2, &lExponent2,
			&iSizeMantissa2, &iSizeExponent2 );
		cout<<"decomposeDoubleFib( dComposedValue="<<dComposedValue<<
			", &lMantissa2="<<lMantissa2<<", &lExponent2="<<lExponent2<<
			", &iSizeMantissa2="<<iSizeMantissa2<<", &iSizeExponent2="<<iSizeExponent2<<" )"<<endl;
		
		//check values
		if ( lExponent2 == lExponent ){
			
			if ( lMantissa2 != lMantissa ){
				cerr<<"Error: Evalued values not equal (exponent equal but not mantissa)."<<endl;
				iReturn++;
			}
		}else if ( lExponent2 < lExponent ){
			const longFib lExponentDifferenceFactor = ( lExponent - lExponent2 );
			if ( ( lMantissa2 >> lExponentDifferenceFactor ) != lMantissa ){
				cerr<<"Error: Evalued values not OK. ( lMantissa(="<<lMantissa<<
					") != lMantissa2(="<<lMantissa2<<
					") / 2^"<<( lExponentDifferenceFactor )<<" )"<<endl;
				iReturn++;
			}
		}else if ( lExponent < lExponent2 ){
			const longFib lExponentDifferenceFactor = ( lExponent2 - lExponent );
			if ( lMantissa2 != ( lMantissa >> lExponentDifferenceFactor ) ){
				cerr<<"Error: Evalued values not OK. ( lMantissa(="<<lMantissa<<
					") / 2^"<<lExponentDifferenceFactor<<
					" != lMantissa2(="<<lMantissa2<<")) )"<<endl;
				iReturn++;
			}
		}
		
		/*TODO precision of pow not hight enougt?*/
		const double dEvaluedValue2 = ((long double)lMantissa2) *
			pow( ((long double)2.0), lExponent2 );
		if ( ! isEqual( dComposedValue, dEvaluedValue2 ) ){
			cerr<<"Error: The returned values evalue to a wrong value "<<dEvaluedValue2<<
				" (lMantissa * pow( 2.0, lExponent )), but it should be "<<dComposedValue<<" ."<<endl;
			iReturn++;
		}
		
		if ( iSizeMantissa2 != ((intFib)getDigits( lMantissa2 )) ){
			cerr<<"Error: The returned mantissa size "<<iSizeMantissa2<<
				" is wrong, should be "<<getDigits( lMantissa2 )<<"."<<endl;
			cerr<<"Bits lMantissa2: ";
			writeBitsLongLong( cerr, lMantissa2 ); cout<<endl;
			iReturn++;
		}
		if ( iSizeExponent2 != ((intFib)getDigits( lExponent2 )) ){
			cerr<<"Error: The returned exponent size "<<iSizeExponent2<<
				" is wrong, should be "<<getDigits( lExponent2 )<<"."<<endl;
			cerr<<"Bits lExponent2: ";
			writeBitsLongLong( cerr, lExponent2 ); cout<<endl;
			iReturn++;
		}
		
		/*TODO weg
		if ( 0 <= lMantissa2 ){*/
			if ( ( lMantissa2 & 0x01 ) == 0x00 ){
				cerr<<"Error: The returned mantissa "<<lMantissa2<<
					" has not 1 as the first bit."<<endl;
				cerr<<      "   Bits      lMantissa2    : ";
				writeBitsLongLong( cerr, lMantissa2, 54 );
				cerr<<endl<<"   Bits      dComposedValue: ";
				writeBitsDouble( cerr, dComposedValue );
				cerr<<endl;
				iReturn++;
			}
		/*TODO weg
		}else{// ( lMantissa2 < 0 )
			if ( ( lMantissa2 & 0x01 ) == 0x01 ){
				cerr<<"Error: The returned mantissa "<<lMantissa2<<
					" has not 0 as the first bit."<<endl;
				cerr<<      "   Bits      lMantissa2   : ";
				writeBitsLongLong( cerr, lMantissa2, 54 );
				cerr<<endl<<"   Bits      dComposedValue: ";
				writeBitsDouble( cerr, dComposedValue );
				cerr<<endl;
				iReturn++;
			}
		}*/
		
	}//end iterate random test
	
	return iReturn;
}














