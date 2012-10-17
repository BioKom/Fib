/**
 * @file cLinearConstrainFix
 * file name: cLinearConstrainFix.cpp
 * @author Betti Oesterholz
 * @date 08.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for a linear constrain.
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
 * This header specifies a class for a linear constrain.
 * The number of factors are fixed in this inequiations.
 * This constrain has the implicite form:
 * 	vecBounderyFactors[0] * yu_0 + ... + vecBounderyFactors[uiNumberOfDataPoints-1] * yu_{uiNumberOfDataPoints-1}
 * 	(bGreaterEqual ? <= : =>)
 * 	constant + vecFactors[0] * x_0 + ... + vecFactors[uiNumberOfFactors-1] * x_[uiNumberOfFactors-1}
 * 	(bGreaterEqual ? <= : =>)
 * 	vecBounderyFactors[0] * yo_0 + ... + vecBounderyFactors[uiNumberOfDataPoints-1] * yo_{uiNumberOfDataPoints-1}
 *
 * Wher:
 * 	- yu_i: are the lower bounderies for the y variables
 * 	- yo_i: are the upper bounderies for the y variables
 * 	- vecBounderyFactors[i]: is the factor for the lower and upper y factors
 * 	- bGreaterEqual: is a boolean, if the inequiation sign is greater equal "<="
 * 		( if bGreaterEqual == true ) or lower equal ">=" ( if bGreaterEqual == false )
 * 	- constant: is a constant factor for the linear inequiation
 * 	- vecFactors[k]: are the factors for the x variables
 *
 * The x and the y variables are not given. (In the common case they
 * should be evalued with the help of this constrain.)
 *
 * The y bounderies are for example implemented in @see cDataPointRange.
 * This linear constrain can represent a formular for the y values with
 * linear dependent factors. (like (yu <= f(x) <= yo ) with
 * (f(x)= a_0 * g_0(x) + ... + a_n * g_n(x)) and g_i(x) formulars that
 * only depend on x)
 *
 * This class is for easily handling this formulars.
 *
 */
/*
History:
08.06.2010  Oesterholz  created
*/


#include "cLinearConstrainFix.h"

#include <cmath>

#ifndef ___C_LINEAR_CONSTRAIN_FIX_CPP__
#define ___C_LINEAR_CONSTRAIN_FIX_CPP__


using namespace fib::algorithms::nLinearInequation;




/**
 * standardconstructor for a linear inequiation
 *
 * @param uiInNumberOfFactors The number of factors @see vecFactors in the
 * 	linear formular. @see ulNumberOfFactors
 * @param uiInNumberOfConstrainFactors The number of constrain/ bounderie
 * 	factors @see vecBounderyFactors that constrain the linear formular.
 * 	@see ulNumberOfConstrainFactors
 */
template <class tFactors> cLinearConstrainFix<tFactors>::
	cLinearConstrainFix( unsigned int uiInNumberOfFactors,
		unsigned int uiInNumberOfConstrainFactors ):
		ulNumberOfFactors( uiInNumberOfFactors ),
		ulNumberOfConstrainFactors( uiInNumberOfConstrainFactors ),
		bGreaterEqual( true ),
		vecFactors( vector< tFactors >( uiInNumberOfFactors, 1.0 ) ),
		constant( 0.0 ),
		vecBounderyFactors( vector< tFactors >( ulNumberOfConstrainFactors, 0.0 ) ){
	//nothing to do
}


/**
 * This operator adds the given linear inequiation to this inequiation.
 * If the inequiation sign (@see bGreaterEqual) is equal in both, all
 * correspondending factors and the constant will be added, else they
 * will be subtracted.
 *
 * @see operator+=()
 * @param linInequiation the inequiation to add to this inequiation
 * @return a reference to this inequiation
 */
template <class tFactors> cLinearConstrainFix<tFactors> &
		cLinearConstrainFix<tFactors>::operator+(
		const cLinearConstrainFix<tFactors> & linInequiation ){
	
	const unsigned long ulMinNumberOfFactors =
		min( ulNumberOfFactors, linInequiation.ulNumberOfFactors );
	const unsigned long ulMinNumberOfConstrainFactors =
		min( ulNumberOfConstrainFactors, linInequiation.ulNumberOfConstrainFactors );
	
	if ( bGreaterEqual == linInequiation.bGreaterEqual ){
	
		constant += linInequiation.constant;
		for ( unsigned long uiActualFactor = 0;
				uiActualFactor < ulMinNumberOfFactors; uiActualFactor++ ){
			
			vecFactors[ uiActualFactor ] += linInequiation.vecFactors[ uiActualFactor ];
		}
		for ( unsigned long uiActualFactor = 0;
				uiActualFactor < ulMinNumberOfConstrainFactors; uiActualFactor++ ){
			
			vecBounderyFactors[ uiActualFactor ] += linInequiation.vecBounderyFactors[ uiActualFactor ];
		}
	}else{//swich signs
		constant -= linInequiation.constant;
		for ( unsigned long uiActualFactor = 0;
				uiActualFactor < ulMinNumberOfFactors; uiActualFactor++ ){
			
			vecFactors[ uiActualFactor ] -= linInequiation.vecFactors[ uiActualFactor ];
		}
		for ( unsigned long uiActualFactor = 0;
				uiActualFactor < ulMinNumberOfConstrainFactors; uiActualFactor++ ){
			
			vecBounderyFactors[ uiActualFactor ] -= linInequiation.vecBounderyFactors[ uiActualFactor ];
		}
	}
	
	return *this;
}


/**
 * This operator adds the given linear inequiation to this inequiation.
 * If the inequiation sign (@see bGreaterEqual) is equal in both, all
 * correspondending factors and the constant will be added, else they
 * will be subtracted.
 *
 * @see operator+()
 * @param linInequiation the inequiation to add to this inequiation
 */
template <class tFactors> void cLinearConstrainFix<tFactors>::operator+=(
		const cLinearConstrainFix<tFactors> & linInequiation ){
	
	operator+( linInequiation );
}


/**
 * This method multiplies the inequiation with the given factor.
 * If the factor is negativ the inequiation sign (@see bGreaterEqual)
 * will be switcht ( bGreaterEqual = ! bGreaterEqual ).
 *
 * @param value the value, with which to multiply this inequiation
 * @return a reference to this inequiation
 */
template <class tFactors> cLinearConstrainFix<tFactors> &
		cLinearConstrainFix<tFactors>::mult( tFactors value ){
	
	if ( value < 0.0 ){
		//switch comparisson operator / sign
		bGreaterEqual = ! bGreaterEqual;
		value = abs( value );
	}
	constant *= value;
	
	for ( unsigned long uiActualFactor = 0;
			uiActualFactor < ulNumberOfFactors; uiActualFactor++ ){
		
		vecFactors[ uiActualFactor ] *= value;
	}
	for ( unsigned long uiActualFactor = 0;
			uiActualFactor < ulNumberOfConstrainFactors; uiActualFactor++ ){
		
		vecBounderyFactors[ uiActualFactor ] *= value;
	}
	
	return *this;
}


/**
 * This method print the inequiation in a readebel form to the given
 * output stream outputStream.
 *
 * @param outputStream the stream wher to print this inequiation to
 */
template <class tFactors> void cLinearConstrainFix<tFactors>::print(
		ostream & outputStream ){
	
	bool bPrintPlus = false;
	//print lower bound factors
	for ( unsigned long uiActualFactor = 0;
			uiActualFactor < ulNumberOfConstrainFactors; uiActualFactor++ ){
		
		if ( vecBounderyFactors[ uiActualFactor ] == 0.0 ){
			continue;//skip
		}
		if ( bPrintPlus ){
			outputStream<<" + ";
		}
		outputStream<< vecBounderyFactors[ uiActualFactor ] <<"*yu_"<< uiActualFactor;
		bPrintPlus = true;
	}
	if ( ! bPrintPlus ){
		//no factor printed -> print 0
		outputStream<< "0";
	}
	
	if ( bGreaterEqual ){
		outputStream<<" <= ";
	}else{
		outputStream<<" >= ";
	}
	
	//print the linear formular factors
	bPrintPlus = false;
	for ( unsigned long uiActualFactor = 0;
			uiActualFactor < ulNumberOfFactors; uiActualFactor++ ){
		
		if ( vecFactors[ uiActualFactor ] == 0.0 ){
			continue;//skip
		}
		if ( bPrintPlus ){
			outputStream<<" + ";
		}
		outputStream<< vecFactors[ uiActualFactor ] <<"*x_"<< uiActualFactor;

		bPrintPlus = true;
	}
	if ( constant != 0.0 ){
		outputStream<<" + "<<constant;
	}
	
	if ( bGreaterEqual ){
		outputStream<<" <= ";
	}else{
		outputStream<<" >= ";
	}
	//print upper bound factors
	bPrintPlus = false;
	for ( unsigned long uiActualFactor = 0;
			uiActualFactor < ulNumberOfConstrainFactors; uiActualFactor++ ){
		
		if ( vecBounderyFactors[ uiActualFactor ] == 0.0 ){
			continue;//skip
		}
		if ( bPrintPlus ){
			outputStream<<" + ";
		}
		outputStream<< vecBounderyFactors[ uiActualFactor ] <<"*yo_"<< uiActualFactor;
		bPrintPlus = true;
	}
	if ( ! bPrintPlus ){
		//no factor printed -> print 0
		outputStream<< "0";
	}
	
	outputStream<<endl;
}

#endif //___C_LINEAR_CONSTRAIN_FIX_CPP__


