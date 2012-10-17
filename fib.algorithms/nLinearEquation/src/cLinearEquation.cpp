/**
 * @file cLinearEquation
 * file name: cLinearEquation.h
 * @author Betti Oesterholz
 * @date 11.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements a class for a equiation.
 * Copyright (C) @c GPL3 2010 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (GPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This header specifies a class for a equiation.
 * The equiation has the form:
 * constant = vecFactors[0] * x_0 + ... + vecFactors[n] * x_n
 *
 * The elements are:
 * 	- constant: a constant for the equiation
 * 	- vecFactors[i]: the factors for the equiation
 * 	- x_i: variables for the equiation, theas are not given explicite
 *
 */
/*
History:
11.06.2010  Oesterholz  created
18.01.2011  Oesterholz  FEATURE_LINEAR_EQUIATION_PRECISION_FOR_NULL added
20.01.2011  Oesterholz  Methods isNull(), isSolvebel() and
	getNumberOfFactorsNotNull() added;
	the equiation is initialisized with 0 factors
*/


#include "cLinearEquation.h"

#include "fibDatatyps.h"

#ifndef ___C_LINEAR_EQUATION_CPP__
#define ___C_LINEAR_EQUATION_CPP__


using namespace fib;
using namespace fib::algorithms::nLinearEquation;


/**
 * standardconstructor
 *
 * @param uiInNumberOfFactors the number of factors in the to create
 * 	equiation (they will be initialisized with 1)
 * @param inConstant the constant for the equiation (@see constant)
 */
template <class tFactors> cLinearEquation<tFactors>::cLinearEquation(
		unsigned long uiInNumberOfFactors, tFactors inConstant ):
		constant( inConstant ), vecFactors( uiInNumberOfFactors, 0.0 ){
	//nothing to do
}


/**
 * This operator adds the given linear equiation to this equiation.
 * For this all correspondending factors and the constant will be added.
 *
 * @see operator+=()
 * @param linInequiation the inequiation to add to this inequiation
 * @return a reference to this inequiation
 */
template <class tFactors> cLinearEquation<tFactors> &
		cLinearEquation<tFactors>::operator+( const  cLinearEquation<tFactors> & equiation ){
	
#ifdef FEATURE_LINEAR_EQUIATION_PRECISION_FOR_NULL
	const unsigned int uiMinNumberOfFactors =
		min( vecFactors.size(), equiation.vecFactors.size() );
	
	addToFirst( constant, equiation.constant );
	for ( unsigned int uiActualFactor = 0;
			uiActualFactor < uiMinNumberOfFactors; uiActualFactor++ ){
		
		addToFirst( vecFactors[ uiActualFactor ], equiation.vecFactors[ uiActualFactor ] );
	}
#else //FEATURE_LINEAR_EQUIATION_PRECISION_FOR_NULL
	const unsigned int uiMinNumberOfFactors =
		min( vecFactors.size(), equiation.vecFactors.size() );
	
	constant += equiation.constant;
	
	for ( unsigned int uiActualFactor = 0;
			uiActualFactor < uiMinNumberOfFactors; uiActualFactor++ ){
		
		vecFactors[ uiActualFactor ] += equiation.vecFactors[ uiActualFactor ];
	}
#endif //FEATURE_LINEAR_EQUIATION_PRECISION_FOR_NULL
	
	return *this;
}


/**
 * This operator adds the given linear equiation to this equiation.
 * For this all correspondending factors and the constant will be added.
 *
 * @see operator+()
 * @param linInequiation the inequiation to add to this inequiation
 */
template <class tFactors> void cLinearEquation<tFactors>::
		operator+=( const  cLinearEquation<tFactors> & equiation ){
	
	operator+( equiation );
}


/**
 * This method multiplies the inequiation with the given factor.
 *
 * @param value the value, with which to multiply this inequiation
 * @return a reference to this inequiation
 */
template <class tFactors> cLinearEquation<tFactors> &
		cLinearEquation<tFactors>::mult( tFactors value ){
	
	constant *= value;
	
	const unsigned int uiNumberOfFactors = vecFactors.size();
	
	for ( unsigned int uiActualFactor = 0;
			uiActualFactor < uiNumberOfFactors; uiActualFactor++ ){
		
		vecFactors[ uiActualFactor ] *= value;
	}
	
	return *this;
}


/**
 * @return true if all factors and the constant are 0, else false
 */
template <class tFactors> bool cLinearEquation<tFactors>::isNull() const{
	
	if ( ! isEqualNull( constant ) ){
		return false;
	}
	const unsigned int uiNumberOfFactors = vecFactors.size();
	
	for ( unsigned int uiActualFactor = 0;
			uiActualFactor < uiNumberOfFactors; uiActualFactor++ ){
		
		if ( ! isEqualNull( vecFactors[ uiActualFactor ] ) ){
			return false;
		}
	}
	return true;
}


/**
 * @return true if the equiation is solvebel, else false (all factors
 * 	are 0, but the constant is not 0)
 */
template <class tFactors> bool cLinearEquation<tFactors>::isSolvebel() const{
	
	if ( isEqualNull( constant ) ){
		//if the constant is null the equiation is solvebel
		return true;
	}//else constsnt not null
	const unsigned int uiNumberOfFactors = vecFactors.size();
	
	for ( unsigned int uiActualFactor = 0;
			uiActualFactor < uiNumberOfFactors; uiActualFactor++ ){
		
		if ( ! isEqualNull( vecFactors[ uiActualFactor ] ) ){
			//constsnt not 0 and an factor not 0 -> equiation solvebel
			return true;
		}
	}//constant not 0 but all factors 0 -> equiation not solvebel
	return false;
}


/**
 * @return the number of factors which are not 0
 */
template <class tFactors> unsigned long cLinearEquation<tFactors>::
		getNumberOfFactorsNotNull() const{
	
	unsigned long ulFactorsNotNull = 0;
	const unsigned int uiNumberOfFactors = vecFactors.size();
	
	for ( unsigned int uiActualFactor = 0;
			uiActualFactor < uiNumberOfFactors; uiActualFactor++ ){
		
		if ( ! isEqualNull( vecFactors[ uiActualFactor ] ) ){
			
			ulFactorsNotNull++;
		}
	}
	return ulFactorsNotNull;
}


/**
 * This method print the inequiation in a readebel form to the given
 * output stream outputSream.
 *
 * @param outputStream the stream wher to print this inequiation to
 */
template <class tFactors> void cLinearEquation<tFactors>::print(
		ostream & outputStream ){
	
	const unsigned int uiNumberOfFactors = vecFactors.size();
	
	outputStream<< constant <<" = ";
	
	//print the factors
	bool bPrintPlus = false;
	for ( unsigned int uiActualFactor = 0;
			uiActualFactor < uiNumberOfFactors; uiActualFactor++ ){
		
		if ( vecFactors[ uiActualFactor ] == 0.0 ){
			continue;//skip
		}
		if ( bPrintPlus ){
			outputStream<<" + ";
		}
		outputStream<< vecFactors[ uiActualFactor ] <<"*x_"<< uiActualFactor;

		bPrintPlus = true;
	}
	if ( ! bPrintPlus ){
		//no factor printed -> print 0
		outputStream<< "0";
	}
	outputStream<<endl;
}


#endif //___C_LINEAR_EQUATION_CPP__


