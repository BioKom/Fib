/**
 * @class cDomainRationalBasis
 * file name: cDomainRationalBasis.h
 * @author Betti Oesterholz
 * @date 12.05.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a domain for rational numbers.
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
 * This file contains the basisclass of all rational Fib -domains.
 * It's not possible to create instances from this class.
 * Rational numbers are composed of two numbers the mantissa and the exponent.
 * The number is: mantissa * 2^exponent
 *
 */
/*
History:
12.05.2010  Oesterholz  created
*/


#include "cDomainRationalBasis.h"


using namespace fib;


/**
 * The constructor for scalar/ number domains.
 *
 * @param dfMantissa the domain for the mantisse of the rational domain
 * @param dfExponent the domain for the exponent of the rational domain
 */
cDomainRationalBasis::cDomainRationalBasis( const cDomainIntegerBasis &dfMantissa,
		const cDomainIntegerBasis &dfExponent ){

	pDomainMantissa = dfMantissa.clone();
	pDomainExponent = dfExponent.clone();
}


/**
 * The copyconstructor for rational number domains.
 *
 * @param domainRational the domain to copy
 */
cDomainRationalBasis::cDomainRationalBasis( const cDomainRationalBasis &domainRational ):
		pDomainMantissa( NULL ), pDomainExponent( NULL ){

	if ( domainRational.pDomainMantissa ){
		pDomainMantissa = domainRational.pDomainMantissa->clone();
	}
	if ( domainRational.pDomainExponent ){
		pDomainExponent = domainRational.pDomainExponent->clone();
	}
}


/**
 * The desstructor for rational number domains.
 */
cDomainRationalBasis::~cDomainRationalBasis(){

	if ( pDomainMantissa ){
		delete pDomainMantissa;
	}
	if ( pDomainExponent ){
		delete pDomainExponent;
	}
}


/**
 * This Method checks if the given domain is equal to this domain.
 *
 * @param domain the domain to compare with
 * @return true if the given domain is equal to this domain, else false
 */
bool cDomainRationalBasis::operator==( const cDomain &domain ) const{
	
	if ( ! cDomain::operator==( domain ) ){
		return false;
	}
	cDomainRationalBasis * pRationalDomain = (cDomainRationalBasis *) &domain;
	//compare the mantissa domain
	if ( pDomainMantissa != NULL ){
		if ( pRationalDomain->pDomainMantissa == NULL ){
			return false;
		}
		if ( ! ( pDomainMantissa->equal( *(pRationalDomain->pDomainMantissa) ) ) ){
			return false;
		}
	}else{//pDomainMantissa == NULL
		if ( pRationalDomain->pDomainMantissa != NULL ){
			return false;
		}
	}
	//compare the exponent domain
	if ( pDomainExponent != NULL ){
		if ( pRationalDomain->pDomainExponent == NULL ){
			return false;
		}
		if ( ! ( pDomainExponent->equal( *(pRationalDomain->pDomainExponent) ) ) ){
			return false;
		}
	}else{//pDomainExponent == NULL
		if ( pRationalDomain->pDomainExponent != NULL ){
			return false;
		}
	}
	return true;
}




