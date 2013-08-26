/**
 * @class cDomainSingle
 * file name: cDomainSingle.h
 * @author Betti Oesterholz
 * @date 13.05.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a scalar domains.
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
 * This file contains the basisclass of all scalar Fib -domains.
 * It's not possible to create instances from this class.
 *
 */
/*
History:
19.09.2010  Oesterholz  created with the createGoodDomain() function
*/


#include "cDomainSingle.h"

#include "fibDatatyps.h"

#include "cDomainInteger.h"
#include "cDomainRational.h"
#include "cDomainNaturalNumberBit.h"


using namespace fib;


/**
 * This function creates creates a good domain wich contains all the
 * numbers of the given list liValues.
 * A domain is better than an other domain, if it takes less storage bits
 * to store the numbers and the domain.
 * Beware: You have to care that the returned domain is deleted. (if
 * 	one was returned)
 *
 * @param liValues the list with the values, for which a domain is to create
 * @return a new domain which contains all the given values liValues
 */
cDomainSingle * cDomainSingle::createGoodDomain( list< doubleFib > & liValues ){
	
	if ( liValues.empty() ){
		return new cDomainNaturalNumberBit( 0 );
	}
	
	bool bUseIntegerDomain = true;
	
	/*evalue:
	- the minimum, maximum value
	- the scaling factor
	- evalue maximum bits for the mantissa bM and exponent bE for rational numbers*/
	//evalue the values for an integer domain
	liValues.sort();
	const doubleFib dMinimum = liValues.front();
	const doubleFib dMaximum = liValues.back();
	
	/*the scaling factor is the greates common divisor gcd of the
	difference betwean the numbers and 0*/
	doubleFib dScalingFactor = 0.0;

	unsigned int iuBitPerInteger = 0;
	doubleFib dLastDifferentNumber = 0.0;
	for ( list< doubleFib >::const_iterator itrValue = liValues.begin();
			itrValue != liValues.end(); itrValue++ ){
		
		if ( dScalingFactor == 0.0 ){
			if ( dLastDifferentNumber != (*itrValue) ){
				dScalingFactor = (*itrValue) - dLastDifferentNumber;
				dLastDifferentNumber = (*itrValue);
			}//else value not changed
		}else{
			if ( dLastDifferentNumber != (*itrValue) ){
				dScalingFactor = gcd( dScalingFactor,
					(*itrValue) - dLastDifferentNumber );
				dLastDifferentNumber = (*itrValue);
			}//else value not changed
		}
		if ( dScalingFactor != 0.0 ){
			// (maximum - minimum) / dScalingFactor + 1 = numbers of values in integer domain = #I
			const unsigned long long ulNumbersInDomain =
				(unsigned long long)( ( dMaximum - dMinimum ) / dScalingFactor) + 1;
			if ( (((doubleFib)ulNumbersInDomain - 1)) * dScalingFactor <
					( dMaximum - dMinimum )  ){
				//domain can't be represented by an integer domain
				bUseIntegerDomain = false;
				break;
			}
			// log_2( #I ) = bits for integer domain number = bI
			iuBitPerInteger = getDigits( ulNumbersInDomain );
		}
	}
	//evalue the values for an rational domain
	longFib lTmpMantissa;
	longFib lTmpExponent;
	intFib iTmpSizeMantissa;
	intFib iTmpSizeExponent;
	
	intFib iSizeMantissa = 0;
	intFib iSizeExponent = 0;
	longFib lMinMantissa;
	longFib lMinExponent;
	decomposeDoubleFib( dMinimum , & lMinMantissa, & lMinExponent,
		& iTmpSizeMantissa , & iTmpSizeExponent );
	
	longFib lMaxMantissa = lMinMantissa;
	longFib lMaxExponent = lMinExponent;
	
	unsigned int iuBitPerRational = 0;
	for ( list< doubleFib >::const_iterator itrValue = liValues.begin();
			itrValue != liValues.end(); itrValue++ ){
		
		decomposeDoubleFib( *itrValue , & lTmpMantissa, & lTmpExponent,
			& iTmpSizeMantissa , & iTmpSizeExponent );
		
		if ( lTmpMantissa < lMinMantissa ){
			lMinMantissa = lTmpMantissa;
		}
		if ( lMaxMantissa < lTmpMantissa ){
			lMaxMantissa = lTmpMantissa;
		}
		if ( lTmpExponent < lMinExponent ){
			lMinExponent = lTmpExponent;
		}
		if ( lMaxExponent < lTmpExponent ){
			lMaxExponent = lTmpExponent;
		}
		if ( iSizeMantissa < iTmpSizeMantissa ){
			iSizeMantissa = iTmpSizeMantissa;
		}
		if ( iSizeExponent < iTmpSizeExponent ){
			iSizeExponent = iTmpSizeExponent;
		}
		iuBitPerRational = iSizeMantissa + iSizeExponent;
		if ( bUseIntegerDomain && ( iuBitPerInteger < iuBitPerRational ) ){
			//create integer domain
			break;
		}
	}
	//TODO include value domains
	
	if ( bUseIntegerDomain && ( iuBitPerInteger < iuBitPerRational ) ){
		//create integer domain
		if ( dScalingFactor < 0.0 ){
			dScalingFactor *= -1.0;
		}
		return new cDomainInteger( roundToLongFib( dMinimum / dScalingFactor ),
			roundToLongFib( dMaximum / dScalingFactor), dScalingFactor );
	}//else{ create rational domain
	cDomainInteger domainMantissa( lMinMantissa, lMaxMantissa );
	cDomainInteger domainExponent( lMinExponent, lMaxExponent );
#ifdef DEBUG
	cout<<"creating rational domain:"<<endl;
	cout<<"cDomainRational( cDomainInteger domainMantissa( lMinMantissa="<<
		lMinMantissa<<", lMaxMantissa="<<lMaxMantissa<<" ), "<<
		" cDomainInteger domainExponent( lMinExponent="<<lMinExponent<<
		", lMaxExponent="<<lMaxExponent<<" );"<<endl;
	cout<<"iSizeMantissa="<<iSizeMantissa<<" and iSizeExponent="<<iSizeExponent<<endl;

#endif //DEBUG


	return new cDomainRational( domainMantissa, domainExponent );
}










