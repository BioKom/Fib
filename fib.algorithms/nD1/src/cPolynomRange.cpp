/**
 * @file cPolynomRange
 * file name: cPolynomRange.cpp
 * @author Betti Oesterholz
 * @date 07.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies functions for a one dimensional polynom functions.
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
 * This header specifies functions for a one dimensional polynom functions.
 *
 */
/*
History:
07.06.2010  Oesterholz  created
*/


#ifndef ___N_D_1_C_POLYNOM_RANGE_CPP__
#define ___N_D_1_C_POLYNOM_RANGE_CPP__

#include "cPolynomRange.h"

#include "nLinearInequation.h"
#include "cRangeFactor.h"
#include "cLinearConstrainFix.h"
#include "cInequation.h"

#include <iostream>



//#define PRINT_INFOS

#ifdef PRINT_INFOS
	#define PRINT_INFOS_FIND_POLYNOM_RAND
#endif


/**
 * The save boundery for error.
 * Errors will just be counted if ther are greater than this save boundery.
 */
#define SAVE_BOUNDERY 0.0000000001


using namespace fib::algorithms::nD1;
using namespace fib::algorithms::nLinearInequation;


/**
 * Standartconstructor
 */
template <class tX, class tY> fib::algorithms::nD1::cPolynomRange<tX, tY>::
		cPolynomRange():vecFactors(){
	//nothing to do
}


/**
 * This function prints the given polynom to the given stream.
 *
 * @param vecFactors the factors of the polynom to print
 * @param outputStream the stream wher to print the polynom to
 */
template <class tX, class tY> void fib::algorithms::nD1::cPolynomRange<tX, tY>::
	print( ostream & outputStream ) const{
	
	const unsigned int uiFactors = vecFactors.size();
	bool bPrintAdd = false;
	outputStream<<"fp( x ) = ";
	for ( unsigned int uiActualFactor = 0;
			uiActualFactor < uiFactors; uiActualFactor++ ){
		
		if ( ( vecFactors[ uiActualFactor ].min == 0 ) &&
				( vecFactors[ uiActualFactor ].max == 0 ) &&
				( ! vecFactors[ uiActualFactor ].isInf() ) ){
			continue;//skip
		}
		
		if ( bPrintAdd ){
			outputStream<<" + ";
		}
		outputStream<< "[";
		if ( vecFactors[ uiActualFactor ].bMinIsInf ){
			outputStream<< "-inf";
		}else{
			outputStream<< vecFactors[ uiActualFactor ].min;
		}
		outputStream<< " ... ";
		if ( vecFactors[ uiActualFactor ].bMaxIsInf ){
			outputStream<< "inf";
		}else{
			outputStream<< vecFactors[ uiActualFactor ].max;
		}
		
		outputStream<< "] * x^"<< uiActualFactor;
		
		bPrintAdd = true;
	}
	outputStream<<endl;
}


/**
 * This methods creats the linear inequiations ( @see cLinearConstrainFix )
 * for the given datapoints.
 * The i'th linear inequiations will have the form:
 * 	vecData[i].minY * yu_i <=
 * 	x_0 + vecData.x * x_1 + vecData.x^2 * x_2 + ... + 
 * 	vecData[uiMaxPolynomOrder - 1] * x_{uiMaxPolynomOrder - 1}
 * 	<= vecData[i].maxY * yu_i
 *
 * @param vecData the with the datapoints, for which to evalue the
 * 	linear equiations should be evalued
 * @param uiMaxPolynomOrder the maximal order of the polynom to generate
 * 	the factor ranges for
 * @return a vector with the linear equiations for the datapoints
 */
template <class tX, class tY> vector< cLinearConstrainFix<tY> >
	fib::algorithms::nD1::cPolynomRange<tX, tY>::createLinearInequations(
		const vector< cDataPointRange< tX, tY> > & vecData,
		unsigned int uiMaxPolynomOrder ){
	
	DEBUG_OUT_L2(<<"cPolynomRange<tX, tY>::createLinearInequations( vecData, uiMaxPolynomOrder="<<uiMaxPolynomOrder<<" ) started"<<endl<<flush);
	
	vector< cLinearConstrainFix<tY> > vecOfInequations( vecData.size(),
		cLinearConstrainFix<tY>( uiMaxPolynomOrder, vecData.size() ) );
	for( unsigned long iActualDataPoint = 0;
			iActualDataPoint < vecOfInequations.size(); iActualDataPoint++ ){
		
		//set the values for the x/ a_i factors
		const tX dX = vecData[ iActualDataPoint ].x;
		tX dFactor = 1.0;
		for ( unsigned long uiActualFactor = 0; uiActualFactor < uiMaxPolynomOrder;
				uiActualFactor++ ){
			
			vecOfInequations[ iActualDataPoint ].
				vecFactors[ uiActualFactor ] = dFactor;
			dFactor *= dX;
		}
		
		//set the lower and upper y bounds
		vecOfInequations[ iActualDataPoint ].vecBounderyFactors[ iActualDataPoint ] = 1.0;
	}
#ifdef PRINT_INFOS
	printInequations( vecOfInequations, cout );
#endif
	DEBUG_OUT_L2(<<"cPolynomRange<tX, tY>::createLinearInequations( vecData, uiMaxPolynomOrder="<<uiMaxPolynomOrder<<" ) done"<<endl<<flush);
	
	return vecOfInequations;
}


/**
 * This functions evalues the ranges for the possible factors for a
 * polynom which matches the given data vecData.
 * The returned ranges don't have to include the factors for polynom
 * which match the data, if ther isn't a possible polynome of the maximal
 * range given for the data.
 *
 * @see evalue()
 * @param vecData the data which the returend polynom should match
 * @param uiMaxPolynomOrder the maximal order of the polynom to generate
 * 	the factor ranges for
 * @return ranges in which the factors of a polynom should lay, if
 * 	possible (@see evalue())
 */
template <class tX, class tY> void fib::algorithms::nD1::
	cPolynomRange<tX, tY>::evalue(
		const vector< cDataPointRange< tX, tY> > & vecData,
		unsigned int uiMaxPolynomOrder ){
	
	DEBUG_OUT_L2(<<"cPolynomRange<tX, tY>::evalue( vecData, uiMaxPolynomOrder="<<uiMaxPolynomOrder<<" ) started"<<endl<<flush);
	
	vector< cLinearConstrainFix<tY> > vecOfInequationsOriginal =
		createLinearInequations( vecData, uiMaxPolynomOrder );
	
	vecFactors = solve( vecOfInequationsOriginal, vecData );
	
	DEBUG_OUT_L2(<<"cPolynomRange<tX, tY>::evalue( vecData, uiMaxPolynomOrder="<<uiMaxPolynomOrder<<" ) done"<<endl<<flush);
}


/**
 * @return the sum of the ranges of this function.
 */
template <class tX, class tY> tY fib::algorithms::nD1::
		cPolynomRange<tX, tY>::getRangeSizeSum() const{
	
	tY rangeSize = 0.0;
	const size_t iNumberOfFactors = vecFactors.size();
	for ( size_t iActualFactor = 0; iActualFactor < iNumberOfFactors;
			iActualFactor++ ){
		
		rangeSize += vecFactors[ iActualFactor ].diff();
	}
	return rangeSize;
}


/**
 * @return if the sum of the ranges of this function is 0
 */
template <class tX, class tY> bool fib::algorithms::nD1::
		cPolynomRange<tX, tY>::getRangeSizeSumIsNull() const{
	
	const size_t iNumberOfFactors = vecFactors.size();
	for ( size_t iActualFactor = 0; iActualFactor < iNumberOfFactors;
			iActualFactor++ ){
		
		if ( ! vecFactors[ iActualFactor ].diffIsNull() ){
			return false;
		}
	}
	return true;
}


#endif //___N_D_1_C_POLYNOM_RANGE_CPP__
















