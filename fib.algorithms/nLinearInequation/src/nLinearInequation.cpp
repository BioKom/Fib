/**
 * @file nLinearInequation
 * file name: nLinearInequation.h
 * @author Betti Oesterholz
 * @date 09.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements functions for linear inequation.
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
 * This implements functions for linear inequation.
 */
/*
History:
09.06.2010  Oesterholz  created
*/


#include "nLinearInequation.h"
#include "../nD1/incl/cDataPointRange.h"

#ifndef ___N_LINEAR_INEQUATION_CPP__
#define ___N_LINEAR_INEQUATION_CPP__

#include <iostream>
#include <stdlib.h>
#include <time.h>

//#define PRINT_INFOS

#ifdef PRINT_INFOS
	#define PRINT_INFOS_HILLCLIMBING
#endif


using namespace fib::algorithms::nLinearInequation;


/**
 * This functions converts the given vector of inequation into a diagonal
 * form. In this form ther exsists only one factor in the liniar formular
 * (@see cLinearConstrainFix::vecFactors) in every inequation. For the
 * first n inequation this factor is the n'th factor. For the remaining
 * inequation, this factor is the last factor. (n is the number of
 * factors @see cLinearConstrainFix::ulNumberOfFactors)
 * The convertion is done by multiplying inequation with a number
 * (@see cLinearConstrainFix::mult()) or adding two inequation of the
 * vector of inequations (@see cLinearConstrainFix::operator+()).
 *
 * @param vecOfInequations a reference to the vector of inequation, which
 * 	to convert into the triangle form (this is changed)
 * @return a pointer to the converted vector of inequations
 */
template <class tFactors>
vector< cLinearConstrainFix<tFactors> > & fib::algorithms::nLinearInequation::
	crateDiagonalForm(
		vector< cLinearConstrainFix<tFactors> > & vecOfInequations ){
	
	if ( vecOfInequations.empty() ){
		//nothing to do
		return vecOfInequations;
	}
	const unsigned long ulNumberOfFactors = min(
		vecOfInequations[ 0 ].ulNumberOfFactors,
		(unsigned long)(vecOfInequations.size()) );

	cLinearConstrainFix<tFactors> polyTmp;
	
	for ( unsigned long uiActualFactor = 0; uiActualFactor < ulNumberOfFactors; ){
		//uiActualFactor = actual polynom to change
		
		for ( unsigned long uiActualFactor2 = 0; uiActualFactor2 < uiActualFactor;
				uiActualFactor2++ ){
			//uiActualFactor2 = actual factor in actual polynom to change
			polyTmp = vecOfInequations[ uiActualFactor2 ];
			
			const tFactors dFactor1 = polyTmp.vecFactors[ uiActualFactor2 ];
			const tFactors dFactor2 = vecOfInequations[ uiActualFactor ].vecFactors[ uiActualFactor2 ];
			if ( dFactor2 == 0 ){
				//factor is allready 0 -> skip it
				continue;
			}
			if ( dFactor1 == 0 ){
				//can't reduce this factor -> skip it
				continue;
			}
			const tFactors dMultiplyTmpWith = -1 * dFactor2 / dFactor1;
			polyTmp.mult( dMultiplyTmpWith );
			
			vecOfInequations[ uiActualFactor ] += polyTmp;
			
			//factor should now be 0, but to make sure (because of rounding errors)
			vecOfInequations[ uiActualFactor ].vecFactors[ uiActualFactor2 ] = 0.0;
		}
		if ( vecOfInequations[ uiActualFactor ].vecFactors[ uiActualFactor ] != 0.0 ){
			//go to the next factor
			uiActualFactor++;
		}else{
			/*if the actual factor in the actual polynom is null, replace the
			actual polynom with one after it and try again (because the
			factor is needed for the later equations)*/
			const unsigned long uiLastActualFactor = uiActualFactor;
			while ( vecOfInequations[ uiLastActualFactor ].vecFactors[ uiActualFactor ] == 0.0 ){
	
				unsigned long uiActualPolynom = vecOfInequations.size() - 1;
				for ( ; uiLastActualFactor < uiActualPolynom; uiActualPolynom-- ){
					
					if ( vecOfInequations[ uiActualPolynom ].vecFactors[ uiActualFactor ] != 0.0 ){
						//switch polynoms
						polyTmp = vecOfInequations[ uiLastActualFactor ];
						vecOfInequations[ uiLastActualFactor ] = vecOfInequations[ uiActualPolynom ];
						vecOfInequations[ uiActualPolynom ] = polyTmp;
						break;
					}
				}
				if ( uiLastActualFactor == uiActualPolynom ){
					/*can't switch with a polynom which has this factor
					-> no polynom has this factor -> everything is ok*/
					uiActualFactor++;
					
					if ( ulNumberOfFactors <= uiActualFactor ){
						//no more factors to check
						break;
					}
				}
			}//end while
		}
	}
	/*now the first ulNumberOfFactors inequations of vecOfInequations are in triangle form*/
#ifdef PRINT_INFOS
	cout<<endl<<"Polynom in triangle form with more than one x each:"<<endl;
	printInequations( vecOfInequations, cout );
#endif
	//eliminate all factores in the first ulNumberOfFactors inequations except the one
	for ( unsigned long uiActualPolynom = 0; uiActualPolynom < ulNumberOfFactors - 1;
			uiActualPolynom++ ){
		//uiActualPolynom = actual polynom to change
		
		for ( unsigned long uiActualFactor = uiActualPolynom + 1; uiActualFactor < ulNumberOfFactors;
				uiActualFactor++ ){
			//uiActualFactor = actual factor in actual polynom to change
			polyTmp = vecOfInequations[ uiActualFactor ];
			
			const tFactors dFactor1 = polyTmp.vecFactors[ uiActualFactor ];
			const tFactors dFactor2 = vecOfInequations[ uiActualPolynom ].vecFactors[ uiActualFactor ];
			if ( dFactor2 == 0 ){
				//factor is allready 0 -> skip it
				continue;
			}
			if ( dFactor1 == 0 ){
				//can't reduce this factor -> skip it
				continue;
			}
			const tFactors dMultiplyTmpWith = -1 * dFactor2 / dFactor1;
			polyTmp.mult( dMultiplyTmpWith );
			
			vecOfInequations[ uiActualPolynom ] += polyTmp;
			
			//factor should now be 0, but to make sure (because of rounding errors)
			vecOfInequations[ uiActualPolynom ].vecFactors[ uiActualFactor ] = 0.0;
		}
	}
	/*now the first ulNumberOfFactors inequations of vecOfInequations are
	in triangle form and have maximal one x -factor*/
	//eleminate all factors except one (the last) in the remaining inequations
	
	for( unsigned long uiActualPolynom = ulNumberOfFactors;
			uiActualPolynom < vecOfInequations.size(); uiActualPolynom++){
	
		for ( unsigned long uiActualFactor = 0; uiActualFactor < (ulNumberOfFactors - 1);
				uiActualFactor++ ){
			//uiActualFactor = actual factor in actual polynom to change
			polyTmp = vecOfInequations[ uiActualFactor ];
			
			const tFactors dFactor1 = polyTmp.vecFactors[ uiActualFactor ];
			const tFactors dFactor2 = vecOfInequations[ uiActualPolynom ].vecFactors[ uiActualFactor ];
			if ( dFactor2 == 0 ){
				//factor is allready 0 -> skip it
				continue;
			}
			if ( dFactor1 == 0 ){
				//can't reduce this factor -> skip it
				continue;
			}
			const tFactors dMultiplyTmpWith = -1 * dFactor2 / dFactor1;
			polyTmp.mult( dMultiplyTmpWith );
			
			vecOfInequations[ uiActualPolynom ] += polyTmp;
			
			//factor should now be 0, but to make sure (because of rounding errors)
			vecOfInequations[ uiActualPolynom ].vecFactors[ uiActualFactor ] = 0.0;
		}
	}
	//every x -factor to 1.0
	for( unsigned long uiActualPolynom = 0;
			uiActualPolynom < vecOfInequations.size(); uiActualPolynom++){
	
		for ( unsigned long uiActualFactor = 0; uiActualFactor < ulNumberOfFactors;
				uiActualFactor++ ){

			const tFactors dFactor = vecOfInequations[ uiActualPolynom ].vecFactors[ uiActualFactor ];
			if ( dFactor == 0 ){
				//factor is allready 0 -> skip it
				continue;
			}
			vecOfInequations[ uiActualPolynom ].mult( 1.0 / dFactor );
		}
	}
	return vecOfInequations;
}



/**
 * This function nulls all factors in the liniar formular
 * (@see cLinearConstrainFix::vecFactors) which x values are constant.
 * (Constant x values have a range size of 0, respectivly ther bounderies
 * are equal.)
 * The ranges for the x values are given (vecXRanges), wher the i'th
 * factor range correspondents to the i'th factor in the liniar formular.
 * The factors are nulled, by multiplying the factor in the liniar
 * formular with it's x value (the value the range for the x -factor contains).
 *
 * @param vecInputInequations a reference to the vector with the
 * 	inequations, which x -factors should be nulled
 * @param vecXRanges a vector with the ranges of the x -factors
 * @param setOpenAFactors a refernce to the set of x -factors, which can be
 * 	nulled; from this set the nulled factors will be removed;
 * 	the set contains the numbers of the x -factors (counting begins with 0)
 * @return a reference to the vector with the inequations, which x
 * 	factors wher nulled
 */
template <class tFactors> vector< cLinearConstrainFix<tFactors> > &
	fib::algorithms::nLinearInequation::nullConstantXFactors(
		vector< cLinearConstrainFix<tFactors> > & vecInputInequations,
		const vector< cRangeFactor<tFactors> > & vecXRanges,
		set<unsigned long> & setOpenAFactors ){
	
	//eleminate all constant x_i factors
	for ( set<unsigned long>::iterator itrFactor = setOpenAFactors.begin();
			itrFactor != setOpenAFactors.end(); ){
		
		const unsigned long uiActualFactor = *itrFactor ;

		if ( ( ! (vecXRanges[ uiActualFactor ].isInf()) ) &&
				( vecXRanges[ uiActualFactor ].diffIsNull() ) ){
			
			for( unsigned long iActualDataPoint = 0;
					iActualDataPoint < vecInputInequations.size(); iActualDataPoint++ ){
				//eleminate the factor in the inequation
				vecInputInequations[ iActualDataPoint ].constant +=
					vecInputInequations[ iActualDataPoint ].vecFactors[ uiActualFactor ] *
					vecXRanges[ uiActualFactor ].min;
				vecInputInequations[ iActualDataPoint ].vecFactors[ uiActualFactor ] = 0.0;
			}
			setOpenAFactors.erase( itrFactor );
			itrFactor = setOpenAFactors.begin();
		}else{
			itrFactor++;
		}
	}
	return vecInputInequations;
}


/**
 * This function nulls all constrain/ bounderie factors in the inequations
 * (@see cLinearConstrainFix::vecBounderyFactors) which y values are constant.
 * (Constant y values have a range size of 0, respectivly ther bounderies
 * are equal.)
 * The ranges for the y values are given (vecYRanges), wher the i'th
 * factor range correspondents to the i'th constrain/ bounderie factor in
 * the inequation.
 * The factors are nulled, by multiplying the bounderie factor in the
 * inequation with it's y value (the value the range of the y -factor contains).
 *
 * @param vecInputInequations a reference to the vector with the
 * 	inequations, of which the y -factors should be nulled
 * @param vecYRanges a vector with the ranges of the y -factors
 * @return a reference to the vector with the inequations, which y
 * 	-factors wher nulled
 */
template <class tFactors> vector< cLinearConstrainFix<tFactors> > &
	fib::algorithms::nLinearInequation::nullConstantYFactors(
		vector< cLinearConstrainFix<tFactors> > & vecInputInequations,
		const vector< cRangeFactor<tFactors> > & vecYRanges ){
	
	//eleminate all constant y -factors
	for ( unsigned long uiActualFactor = 0;
			uiActualFactor < vecYRanges.size(); uiActualFactor++ ){
		
		if ( ( ! (vecYRanges[ uiActualFactor ].isInf()) ) &&
				( vecYRanges[ uiActualFactor ].diffIsNull() ) ){
			
			for( unsigned long iActualDataPoint = 0;
					iActualDataPoint < vecInputInequations.size(); iActualDataPoint++ ){
				//eleminate the factor in the inequation
				vecInputInequations[ iActualDataPoint ].constant -=
					vecInputInequations[ iActualDataPoint ].vecBounderyFactors[ uiActualFactor ] *
					vecYRanges[ uiActualFactor ].min;
				vecInputInequations[ iActualDataPoint ].vecBounderyFactors[ uiActualFactor ] = 0.0;
			}
		}
	}
	return vecInputInequations;
}


/**
 * This function elemitats all nullfactors from the given vector of
 * inequations. Every -factor, that is 0 in all inequations, will be
 * removed from all inequations. Later factors will decrase ther position.
 * It is possible to set one factor as the last factor in the inequations.
 *
 * @param vecInputInequations the vector of the inequation, wher to
 * 	remove the nullfactors
 * @param vecFactorXMappings the new x -factor (factors in the liniar
 * 	formular) mappings, for the inequations;
 * 	on position i in this vector stands the position, the i'th x -factor
 * 	in the returned inequations, has in the given inequations
 * 	vecInputInequations (returned[k].vecFactors[ i ] ==
 * 	vecInputInequations[k].vecFactors[ vecFactorXMappings[i] ])
 * @param vecFactorYMappings  the new y -factor (bounderie factor)
 * 	mappings, for the inequations;
 * 	on position i in this vector stands the position, the i'th y -factor
 * 	in the returned inequations, has in the given inequations
 * 	vecInputInequations (returned[k].vecBounderyFactors[ i ] ==
 * 	vecInputInequations[k].vecBounderyFactors[ vecFactorYMappings[i] ])
 * @param uiLastFactor the x -factor (@see cLinearConstrainFix::vecFactors
 * 	counting begins with 0) which should be last in the returned inequations
 * @return a vector with the inequations wher the nullfactors are removed
 */
template <class tFactors> vector< cLinearConstrainFix<tFactors> >
	fib::algorithms::nLinearInequation::reduceNullFactors(
		const vector< cLinearConstrainFix<tFactors> > & vecInputInequations,
		vector< long > & vecFactorXMappings, vector< long > & vecFactorYMappings,
		unsigned long uiLastFactor = 0 ){
	
	//reduce the 0 factors in the set of inequation
	if ( vecInputInequations.empty() ){
		//nothing to reduce
		return vector< cLinearConstrainFix<tFactors> >();
	}
	//check which factors are 0 factors
	const unsigned long ulNumberOfXFactors = vecInputInequations[ 0 ].vecFactors.size();
	
	vector<bool> vecAIsNullFactor( ulNumberOfXFactors, true );
	unsigned long uiNumberofNotNullAFactors = 0;
	
	for ( unsigned long uiActualFactor = 0; uiActualFactor < ulNumberOfXFactors;
			uiActualFactor++ ){

		for( unsigned long uiActualPolynom = 0;
				uiActualPolynom < vecInputInequations.size(); uiActualPolynom++){
			
			if ( vecInputInequations[ uiActualPolynom ].vecFactors[ uiActualFactor ] != 0.0 ){
				
				vecAIsNullFactor[ uiActualFactor ] = false;
				uiNumberofNotNullAFactors++;
				break;
			}
		}
	}
	vector<bool> vecYIsNullFactor( vecInputInequations.size(), true );
	unsigned long uiNumberofNotNullYFactors = 0;
	
	for ( unsigned long uiActualFactor = 0; uiActualFactor < vecInputInequations.size();
			uiActualFactor++ ){
		for( unsigned long uiActualPolynom = 0;
				uiActualPolynom < vecInputInequations.size(); uiActualPolynom++){
			
			if ( vecInputInequations[ uiActualPolynom ].vecBounderyFactors[ uiActualFactor ] != 0.0 ){
				
				vecYIsNullFactor[ uiActualFactor ] = false;
				uiNumberofNotNullYFactors++;
				break;
			}
		}
	}
	//eleminate all null factors
	
	vector< cLinearConstrainFix<tFactors> > vecActualReducedInequations(
		vecInputInequations.size(), cLinearConstrainFix<tFactors>(
			uiNumberofNotNullAFactors, uiNumberofNotNullYFactors ) );
	
	vecFactorXMappings = vector< long >( uiNumberofNotNullAFactors, -1 );
	//reduce the 0 factors in the set of inequation
	if ( uiNumberofNotNullAFactors <= uiLastFactor ){
		uiLastFactor = 0;
	}
	
	//transfer constant factors
	for( unsigned long uiActualPolynom = 0;
			uiActualPolynom < vecInputInequations.size(); uiActualPolynom++){
		vecActualReducedInequations[ uiActualPolynom ].constant =
			vecInputInequations[ uiActualPolynom ].constant;
	}

	//transfer x -factors
	unsigned long uiActualFactor = 0;
	for ( unsigned long uiActualFactorOrg = 0; uiActualFactorOrg < ulNumberOfXFactors;
			uiActualFactorOrg++ ){
		
		if ( ! vecAIsNullFactor[ uiActualFactorOrg ] ){
			//this factor is not a null factor -> insert it in the reduced polynoms
			for( unsigned long uiActualPolynom = 0;
					uiActualPolynom < vecInputInequations.size(); uiActualPolynom++){
				
				if ( uiLastFactor == uiActualFactor ){
					//this parameter will be last in the triangle form
					vecActualReducedInequations[ uiActualPolynom ].vecFactors[ uiNumberofNotNullAFactors - 1 ] =
						vecInputInequations[ uiActualPolynom ].vecFactors[ uiActualFactorOrg ];
					
					vecFactorXMappings[ uiNumberofNotNullAFactors - 1 ] = uiActualFactorOrg;
				}else if ( uiActualFactor < uiLastFactor ){
					vecActualReducedInequations[ uiActualPolynom ].vecFactors[ uiActualFactor ] =
						vecInputInequations[ uiActualPolynom ].vecFactors[ uiActualFactorOrg ];
					
					vecFactorXMappings[ uiActualFactor ] = uiActualFactorOrg;
				}else{//( uiLastFactor < uiActualFactor )
					vecActualReducedInequations[ uiActualPolynom ].vecFactors[ uiActualFactor - 1 ] =
						vecInputInequations[ uiActualPolynom ].vecFactors[ uiActualFactorOrg ];
					
					vecFactorXMappings[ uiActualFactor - 1 ] = uiActualFactorOrg;
				}
			}
			uiActualFactor++;
		}
		if ( uiActualFactor == uiNumberofNotNullAFactors ){
			//all factors done
			break;
		}
	}
	vecFactorYMappings = vector< long >( uiNumberofNotNullYFactors, -1 );
	//transfer y -factors
	uiActualFactor = 0;
	unsigned long uiNullPolynoms = 0;
	for ( unsigned long uiActualFactorOrg = 0; uiActualFactorOrg < vecInputInequations.size();
			uiActualFactorOrg++ ){
		
		if ( ! vecYIsNullFactor[ uiActualFactorOrg ] ){
			//this factor is not a null factor -> insert it in the reduced polynoms
			for( unsigned long uiActualPolynom = 0;
					uiActualPolynom < vecInputInequations.size(); uiActualPolynom++){
				
				vecActualReducedInequations[ uiActualPolynom - uiNullPolynoms ].vecBounderyFactors[ uiActualFactor ] =
					vecInputInequations[ uiActualPolynom ].vecBounderyFactors[ uiActualFactorOrg ];
			}
			vecFactorYMappings[ uiActualFactor ] = uiActualFactorOrg;
			uiActualFactor++;
		}
		if ( uiActualFactor == uiNumberofNotNullYFactors ){
			//all factors done
			break;
		}
	}

	//eleminate inequations with just 0 as factors
	for( unsigned long uiActualPolynom = 0;
			uiActualPolynom < vecActualReducedInequations.size(); ){
		
		bool bAllFactorsNull = true;
		for ( uiActualFactor = 0; uiActualFactor <
				vecActualReducedInequations[ uiActualPolynom ].vecFactors.size();
				uiActualFactor++ ){
			
			if ( vecActualReducedInequations[ uiActualPolynom ].vecFactors[
					uiActualFactor ] != 0.0 ){
				bAllFactorsNull = false;
				break;
			}
		}
		if ( bAllFactorsNull ){
			for ( uiActualFactor = 0; uiActualFactor <
					vecActualReducedInequations[ uiActualPolynom ].vecBounderyFactors.size();
					uiActualFactor++ ){
				
				if ( vecActualReducedInequations[ uiActualPolynom ].vecBounderyFactors[
						uiActualFactor ] != 0.0 ){
					bAllFactorsNull = false;
					break;
				}
			}
		}
		if ( bAllFactorsNull ){
			vecActualReducedInequations[ uiActualPolynom ] =
				vecActualReducedInequations[ vecActualReducedInequations.size() - 1 ];
			
			vecActualReducedInequations.pop_back();
		}else{
			uiActualPolynom++;
		}
	}
	return vecActualReducedInequations;
}


/**
 * This function converts the given @see cLinearConstrainFix inequations
 * to an equivallent set of @see cInequation inequations.
 * For every cLinearConstrainFix two cInequation will be crated.
 * All factors, which are 0, will be eleminated
 *
 * vecBounderyFactors[0] * yu_0 + ... + vecBounderyFactors[uiNumberOfDataPoints-1] * yu_{uiNumberOfDataPoints-1}
 * (bGreaterEqual ? <= : =>)
 * constant + vecFactors[0] * x_0 + ... + vecFactors[ulNumberOfFactors-1] * x_[ulNumberOfFactors-1}
 * (bGreaterEqual ? <= : =>)
 * vecBounderyFactors[0] * yo_0 + ... + vecBounderyFactors[uiNumberOfDataPoints-1] * yo_{uiNumberOfDataPoints-1}
 * =>
 * -1 * constant <= vecFactors[0] * z_0 + ... + vecFactors[n] * z_n
 * constant <= -1 * vecFactors[0] * z_0 - ... - vecFactors[n] * z_n
 *
 * Wher:
 * 	- vecFactors[i] is the i'th factor not 0 of the cLinearConstrainFix
 * 		( vecBounderyFactors[0] or vecFactors[0] )
 * 	- constant is the constant of the formular
 *
 * The identifiers (@see cInequation::vecIdentifiers) of the cInequation
 * will be set to a positiv i (0 <= i), if the correspondending original
 * factor, was the i'th factor for the inequation (x -factor,
 * original.vecFactors[ i ] or vecOfInequations.vecFactors[ a ] with
 * i = vecFactorXMappings[ a ] ).
 * The identifiers will be set to a negativ i ( i < 0), if the
 * correspondending original factor, was the (-1 * i - 1)'th bounderie
 * factor (y -factor, original.vecBounderyFactors[ (-1 * i - 1) ] or
 * vecOfInequations.vecBounderyFactors[ a ] with (-1 * i - 1) = vecFactorYMappings[ a ] ).
 *
 * @param vecOfInequations a vector with the (not original) inequations
 * 	to convert
 * @param vecFactorXMappings the mappings for the x -factors in
 * 	vecOfInequations to the original x -factors
 * @param vecFactorYMappings the mappings for the y -factors in
 * 	vecOfInequations to the original y -factors
 * @return a vector with the cInequation, which is equivallent to the
 * 	given vecOfInequations
 */
template <class tFactors> vector< cInequation<tFactors> >
	fib::algorithms::nLinearInequation::fixInequationsToInequations(
		const vector< cLinearConstrainFix<tFactors> > & vecOfFixInequations,
		const vector< long > & vecFactorXMappings,
		const vector< long > & vecFactorYMappings ){
	
	vector< cInequation<tFactors> > vecOfInequations;
	for( unsigned long uiActualPolynom = 0;
			uiActualPolynom < vecOfFixInequations.size(); uiActualPolynom++){
		
		cInequation<tFactors> lowerPolyConstrain;
		cInequation<tFactors> upperPolyConstrain;
		
		lowerPolyConstrain.constant = -1.0 * vecOfFixInequations[ uiActualPolynom ].constant;
		upperPolyConstrain.constant = vecOfFixInequations[ uiActualPolynom ].constant;
		
		//transfer the x -factors
		for ( unsigned long uiActualFactor = 0; uiActualFactor <
				vecOfFixInequations[ uiActualPolynom ].vecFactors.size();
				uiActualFactor++ ){
			
			if ( vecOfFixInequations[ uiActualPolynom ].vecFactors[ uiActualFactor ] != 0.0 ){
				
				lowerPolyConstrain.vecFactors.push_back(
					vecOfFixInequations[ uiActualPolynom ].vecFactors[ uiActualFactor ] );
				lowerPolyConstrain.vecIdentifiers.push_back( vecFactorXMappings[ uiActualFactor ] );
				
				upperPolyConstrain.vecFactors.push_back( -1.0 *
					vecOfFixInequations[ uiActualPolynom ].vecFactors[ uiActualFactor ] );
				upperPolyConstrain.vecIdentifiers.push_back( vecFactorXMappings[ uiActualFactor ] );
			}//else skip factor
		}
		//transfer the y -factors
		for ( unsigned long uiActualFactor = 0; uiActualFactor <
				vecOfFixInequations[ uiActualPolynom ].vecBounderyFactors.size();
				uiActualFactor++ ){
			
			if ( vecOfFixInequations[ uiActualPolynom ].vecBounderyFactors[ uiActualFactor ] != 0.0 ){
				
				lowerPolyConstrain.vecFactors.push_back( -1.0 *
					vecOfFixInequations[ uiActualPolynom ].vecBounderyFactors[ uiActualFactor ] );
				lowerPolyConstrain.vecIdentifiers.push_back(
					(long)(vecFactorYMappings[ uiActualFactor ] + 1) * -1 );
				
				upperPolyConstrain.vecFactors.push_back(
					vecOfFixInequations[ uiActualPolynom ].vecBounderyFactors[ uiActualFactor ] );
				upperPolyConstrain.vecIdentifiers.push_back(
					(long)(vecFactorYMappings[ uiActualFactor ] + 1) * -1 );
			}//else skip factor
		}
		
		if ( vecOfFixInequations[ uiActualPolynom ].bGreaterEqual ){
			vecOfInequations.push_back( lowerPolyConstrain );
			vecOfInequations.push_back( upperPolyConstrain );
#ifdef PRINT_INFOS
			lowerPolyConstrain.print( cout );
			upperPolyConstrain.print( cout );
#endif
		}else{
			vecOfInequations.push_back( upperPolyConstrain );
			vecOfInequations.push_back( lowerPolyConstrain );
#ifdef PRINT_INFOS
			upperPolyConstrain.print( cout );
			lowerPolyConstrain.print( cout );
#endif
		}
	}
	return vecOfInequations;
}


/**
 * This function reduce the ranges for the given factors with the help of
 * the given formulars.
 * The reduced ranges of the factors are subsets of the given ranges.
 * The reduction is done by checking all inequations as long as ranges change.
 * For the check of one inequation, all it's elements except one are
 * maximized by setting the factors to one of ther bounderies.
 * For the not set element it is checked, wich minimum value it can have,
 * If it's range is to big for this value, the range will be adapted to
 * the minimal range, wich is consistent with the this value element.
 *
 * example inequation:
 * 	constant <= vecFactors[0] * z_0 + ... + vecFactors[n] * z_n
 *
 * 	(vecFactors[0] * z_0) is an element
 *
 * In ever inequation no more than one factor with a infinity boundery
 * should exists.
 *
 * The factor for an element is identified by the element identifier
 * (@see cInequation::vecIdentifiers).
 * If the identifiers (@see cInequation::vecIdentifiers) of the factor
 * is a positiv i (0 <= i) number, the correspondending original
 * factor, is the i'th factor for the inequation (x -factor,
 * vecXRanges[ i ] or vecOfInequations.vecFactors[ a ] with
 * i = vecFactorXMappings[ a ] ).
 * If the identifiers is a negativ i ( i < 0) number, the correspondending
 * original factor, is the (-1 * i - 1)'th bounderie
 * factor (y -factor, vecYRanges[ (-1 * i - 1) ] or
 * vecOfInequations.vecBounderyFactors[ a ] with (-1 * i - 1) = vecFactorYMappings[ a ] ).
 *
 * @see fixInequationsToInequations()
 * @param vecOfInequations the inequations, with which to reduce the
 * 	given ranges of the factors
 * @param vecXRanges the x -factors ranges to reduce
 * @param vecYRanges the y -factors ranges to reduce
 * @return true if a boudery was chaged, else false
 */
template <class tFactors> bool fib::algorithms::nLinearInequation::
	reduceBounderies( const vector< cInequation<tFactors> > & vecOfInequations,
		vector< cRangeFactor<tFactors> > & vecXRanges,
		vector< cRangeFactor<tFactors> > & vecYRanges ){

	//reduce the bounderies
	bool bBounderyChanged = false;
	unsigned long ulBounderChangedPolynomsBack = 0;;
	unsigned long uiActualInequation = 0;
	while( ulBounderChangedPolynomsBack <= vecOfInequations.size() ){
		//for every inequation
		
		uiActualInequation++;
		ulBounderChangedPolynomsBack++;
		if ( vecOfInequations.size() <= uiActualInequation ){
			//go back to the first inequation
			uiActualInequation = 0;
		}
		
		//try to reduce the bounderies for the factors
		//for every element i
		const unsigned long uiNumberOfElements =
			vecOfInequations[ uiActualInequation ].vecFactors.size();
		
		for ( unsigned long uiElement = 0; uiElement < uiNumberOfElements;
				uiElement++ ){
			//set other element bounderies to values to maximise the element i
			tFactors dMaxSumOthers = 0;
			bool bOtherRangeIsInf = false;
			for ( unsigned long uiElementOther = 0;
					uiElementOther < uiNumberOfElements; uiElementOther++ ){
				if ( uiElementOther == uiElement ){
					continue;//skip element
				}
				//get the correct range
				cRangeFactor<tFactors> rangeForFactor;
				const long lRangeType = vecOfInequations[
					uiActualInequation ].vecIdentifiers[ uiElementOther ];
				if ( 0 <= lRangeType ){
					//get the x range
					rangeForFactor = vecXRanges[ lRangeType ];
				}else{//get the y range
					rangeForFactor = vecYRanges[ (-1 * lRangeType) - 1 ];
				}
				if ( rangeForFactor.isInf() ){
					bOtherRangeIsInf = true;
					break;
				}
				tFactors dMaximizingBounderie = 0.0;
				if ( 0.0 <= vecOfInequations[ uiActualInequation ].
						vecFactors[ uiElementOther ] ){
					//the upper boundery is the maximising bounderie
					dMaximizingBounderie = rangeForFactor.max;
				}else{
					//the lower boundery is the maximising bounderie
					dMaximizingBounderie = rangeForFactor.min;
				}
				dMaxSumOthers += dMaximizingBounderie *
					vecOfInequations[ uiActualInequation ].
						vecFactors[ uiElementOther ];
			}
			if ( bOtherRangeIsInf ){
				//skip this element
				continue;
			}
			//evalue lower bound of choosen element i and set it, if it is inside the element bounderies
			const tFactors dElementFactor = vecOfInequations[
				uiActualInequation ].vecFactors[ uiElement ];
			tFactors dGreaterAs =
				( vecOfInequations[ uiActualInequation ].constant -
				dMaxSumOthers ) / dElementFactor;
			
			const long lRangeType = vecOfInequations[
				uiActualInequation ].vecIdentifiers[ uiElement ];
			cRangeFactor<tFactors> * pRangeForFactor = NULL;
			if ( 0 <= lRangeType ){
				//change the x range
				pRangeForFactor = &( vecXRanges[ lRangeType ] );
				
			}else{//change the y range
				pRangeForFactor = &( vecYRanges[ (-1 * lRangeType) - 1 ] );
			}
			
			if ( 0.0 <= dElementFactor ){
				//change lower boudery
				if ( ( ! pRangeForFactor->bMaxIsInf ) &&
						( ((tFactors)pRangeForFactor->max) < dGreaterAs ) ){
					//set to maximum
					dGreaterAs = pRangeForFactor->max;
				}
				if ( (pRangeForFactor->bMinIsInf) ||
						( ((tFactors)pRangeForFactor->min) < dGreaterAs ) ){
					
					pRangeForFactor->setMin( dGreaterAs );
					ulBounderChangedPolynomsBack = 0;
					bBounderyChanged = true;
				}
			}else{//change upper boudery
				if ( ( ! pRangeForFactor->bMinIsInf ) &&
						( dGreaterAs < pRangeForFactor->min ) ){
					//set to maximum
					dGreaterAs = pRangeForFactor->min;
				}
				if ( (pRangeForFactor->bMaxIsInf) ||
						(dGreaterAs < pRangeForFactor->max) ){
					
					pRangeForFactor->setMax( dGreaterAs );
					ulBounderChangedPolynomsBack = 0;
					bBounderyChanged = true;
				}
			}
#ifdef PRINT_INFOS
			cout<<"new boundery for "<<lRangeType<<" ("<<((0 <= lRangeType)?"x_":"y_")<<
				((0 <= lRangeType)?lRangeType:((-1 * lRangeType) - 1))<<"): "<<
				"min: "<<((pRangeForFactor->bMinIsInf)?"inf":"not inf")<<" value="<<pRangeForFactor->min<<
				"  max: "<<((pRangeForFactor->bMaxIsInf)?"inf":"not inf")<<" value="<<pRangeForFactor->max<<
				"  ( "<<((0.0 <= dElementFactor)?"min cahnged":"max changed")<<
				" actual inequation: "<< uiActualInequation <<
				" dMaxSumOthers: "<<dMaxSumOthers<<" dGreaterAs: "<<dGreaterAs<<
				" dElementFactor: "<<dElementFactor<<")"<<endl;
#endif
		}//for uiElement
	}
	return bBounderyChanged;
}


/**
 * This function implements a hillclimbing algorithm for finding good
 * values for the x -factors.
 * This function will try to minimize the error of the
 * @see evalueErrorForFactors() function for the factors.
 * It will choose random values for the factors which are in the
 * correspondending range given with vecXRanges. Than it will check near
 * points (factor values), to the best found point, if they are better.
 * Beware: In the vecOfInequations just the i'the y -factor is 1, every
 * 	other y -factor should have the value 0 .(@see evalueErrorForFactors)
 * 	This is a implicite assumption, the y -factors won't be checked.
 *
 * @see evalueErrorForFactors
 * @param vecOfInequations the inequations, for which to find the
 * 	factor values
 * @param inVecXRanges the x -factors ranges, in which to find the factor
 * 	values
 * @param vecYRanges the y -factors ranges
 * @param ulMaxIteration the maximal number of iterations / neibourpoints
 * 	to check
 * @return a pair:
 * 	- the first element is the actual point/ values for the x -factors in
 * 		the x ranges with the lowest found error
 * 	- the second element is the error of this point
 */
template <class tFactors> pair< vector<tFactors>, tFactors>
	fib::algorithms::nLinearInequation::hillClimbingInRanges(
		const vector< cLinearConstrainFix<tFactors> > & vecOfInequations,
		const vector< cRangeFactor<tFactors> > & inVecXRanges,
		const vector< cRangeFactor<tFactors> > & vecYRanges,
		unsigned long ulMaxIteration ){
	
	srand( time( NULL ) );
	vector< cRangeFactor<tFactors> > vecXRanges = inVecXRanges;
	
	//find correct values with a hill climbing algorithm
	const unsigned long ulNumberOfFactors = vecXRanges.size();
	vector<tFactors> vecActualPoint;
	//init the actual point
	bool bOneRangeIsNotNull = false;
	for ( unsigned long uiFactor = 0; uiFactor < ulNumberOfFactors; uiFactor++ ){
		
		if ( (vecXRanges[ uiFactor ].isInf()) ||
				( ( vecXRanges[ uiFactor ].min <= 0.0 ) &&
					( 0.0 <= vecXRanges[ uiFactor ].max ) ) ){
			
			vecActualPoint.push_back( 0.0 );
		}else{//set point to the area middlepoint
			vecActualPoint.push_back( (vecXRanges[ uiFactor ].min +
				vecXRanges[ uiFactor ].max) / 2.0 );
		}
		if ( ( ! bOneRangeIsNotNull ) &&
				( ! vecXRanges[ uiFactor ].diffIsNull() ) ){
			bOneRangeIsNotNull = true;
		}
	}
	tFactors dActualError = evalueErrorForFactors( vecActualPoint,
		vecOfInequations, vecYRanges );
	
	if ( ! bOneRangeIsNotNull ){
		//no other point to check
		return make_pair( vecActualPoint , dActualError );
	}
	
	/*old points with error 0 ( pair( point, error)) */
	vector< tFactors> vecOldGoodPoint;
	tFactors dOldGoodPointError = -1.0;
	
	/*The factor for which it is tryed, if it can be set to 0 and the
	error can than be reduced to 0;
	if -1 no factor is set to 0*/
	long uiActualNullFactor = -1;
	cRangeFactor<tFactors> rangeOldOfNullFactor;
	unsigned long ulIterationsForNullFactor = 0;
	for ( unsigned long uiIteration = 1; uiIteration <= ulMaxIteration; uiIteration++ ){
		
		//choos random neibourpoint to evalue
		vector<tFactors> vecTestPoint = vecActualPoint;
		if ( (rand() % 32) != 0 ){
			//try neibourpoint
			for ( unsigned long uiActualFactor = 0;
					uiActualFactor < ulNumberOfFactors; uiActualFactor++ ){
				
				if ( vecXRanges[ uiActualFactor ].diffIsNull() ){
					//skip factor
					continue;
				}
				//change values random
				tFactors dChangeFactor = 0.0;
				switch ( rand() % 16 ){
				case 0://set to bounderie
					dChangeFactor = 1.0;
				break;
				case 1:
				case 2://no change
					continue;
				break;
				default:
					dChangeFactor = 1.0 / ((tFactors)(
						((rand() % uiIteration) + 1) * ((rand() % 256) + 1)) );
				}
				if ( rand() % 2 == 0 ){
					//direction upper bouderie
					vecTestPoint[ uiActualFactor ] = vecActualPoint[ uiActualFactor ] +
						(vecXRanges[ uiActualFactor ].max -
						vecActualPoint[ uiActualFactor ]) * dChangeFactor;
				}else{
					//direction lower bouderie
					vecTestPoint[ uiActualFactor ] = vecActualPoint[ uiActualFactor ] +
						(vecXRanges[ uiActualFactor ].min -
						vecActualPoint[ uiActualFactor ]) * dChangeFactor;
				}
			}
		}else{//try random new point
			for ( unsigned long uiActualFactor = 0;
					uiActualFactor < ulNumberOfFactors; uiActualFactor++ ){
				
				if ( vecXRanges[ uiActualFactor ].diffIsNull() ){
					//skip factor
					continue;
				}
				//direction upper bouderie
				vecTestPoint[ uiActualFactor ] = vecXRanges[ uiActualFactor ].min +
					(vecXRanges[ uiActualFactor ].max - vecXRanges[ uiActualFactor ].min) *
					((tFactors)(rand() % (256 * 256))) / ((tFactors)(256 * 256));
				
			}
		}
		//evalue error on neibourpoint
		const tFactors dTestPointError = evalueErrorForFactors( vecTestPoint,
			vecOfInequations, vecYRanges );
		
		//if better set it as new actual point
		if ( dTestPointError < dActualError ){
			
			dActualError = dTestPointError;
			vecActualPoint = vecTestPoint;
#ifdef PRINT_INFOS_HILLCLIMBING
			//print actual point and it's error
			cout<<"new point error: "<< dActualError <<"  and factors: ";
			for ( unsigned long uiFactor = 0; uiFactor < ulNumberOfFactors; uiFactor++ ){
				
				cout<<"a_"<< uiFactor <<"=";
				cout<< vecActualPoint[ uiFactor ]<<",";
				cout<<"; ";
			}
			cout<<"( iteration="<< uiIteration <<" )"<<endl;
#endif
		}
		//null factor part
		if ( 0 < uiActualNullFactor ){
			if ( ulIterationsForNullFactor == 0 ){
				//if better point in vecOldGoodPoint choose it
				if ( ( 0.0 < dOldGoodPointError ) && ( dOldGoodPointError < dActualError ) ){
					vecActualPoint = vecOldGoodPoint;
					dActualError = dOldGoodPointError;
				}
				vecXRanges[ uiActualNullFactor ] = rangeOldOfNullFactor;
				uiActualNullFactor = -1;
			}else{
				ulIterationsForNullFactor--;
			}
		}
		//if error is 0 try to constrain the point
		if ( dActualError == 0.0 ){
			//try to set a factors to 0, which hasn't allready the area 0
			vector< unsigned long > vecPossibleNullFactors;
			for ( unsigned long uiActualFactor = 0;
					uiActualFactor < ulNumberOfFactors; uiActualFactor++ ){
				
				if ( vecXRanges[ uiActualFactor ].diffIsNull() ){
					//skip factor
					continue;
				}
				//direction upper bouderie
				if ( (vecXRanges[ uiActualFactor ].min <= 0.0) &&
						( 0.0 <= vecXRanges[ uiActualFactor ].max ) ){
					//area with null inside -> add this as a possible null factor
					vecPossibleNullFactors.push_back( uiActualFactor );
				}
			}
			if ( ! vecPossibleNullFactors.empty() ){
				//nullfactors possible -> choose one
				uiActualNullFactor = vecPossibleNullFactors[
					rand() % vecPossibleNullFactors.size() ];
				
				//a nullfactor was choosen
				rangeOldOfNullFactor = vecXRanges[ uiActualNullFactor ];
				vecXRanges[ uiActualNullFactor ].setMin( 0.0 );
				vecXRanges[ uiActualNullFactor ].setMax( 0.0 );
		
				vecOldGoodPoint = vecActualPoint;
				dOldGoodPointError = dActualError;
				
				vecActualPoint[ uiActualNullFactor ] = 0.0;
				dActualError = evalueErrorForFactors( vecActualPoint,
					vecOfInequations, vecYRanges );
				
				ulIterationsForNullFactor = 256 + ulMaxIteration / (vecActualPoint.size() + 16);
			}else{
				break;
			}
		}//choos nullfactor
		
	}//for iteration
	//if better point in vecOldGoodPoint choose it
	if ( ( 0.0 < dOldGoodPointError ) && ( dOldGoodPointError < dActualError ) ){
		vecActualPoint = vecOldGoodPoint;
		dActualError = dOldGoodPointError;
	}

	return make_pair( vecActualPoint , dActualError );
}


/**
 * This function will evalue the error for the given x -factors
 * vecActualPoint.
 * For this the factors are inserted into the given inequations
 * and it is checkt, if the evalued value is outside the given
 * y -factor bounderies, if so the difference will be added to the error.
 * Beware: In the vecOfInequations just the i'the y -factor is 1, every
 * 	other y -factor should have the value 0 .
 * 	This is a implicite assumption, the y -factors won't be checked.
 *
 * @param vecActualPoint the x -factors values, for which to evalue the error
 * @param vecOfInequations the inequations for which to evalue the error
 * 	for the vecActualPoint
 * @param vecYRanges the y -factors ranges
 * @return the error of the vecActualPoint
 */
template <class tFactors> tFactors fib::algorithms::nLinearInequation::
	evalueErrorForFactors( const vector<tFactors> & vecActualPoint,
		const vector< cLinearConstrainFix<tFactors> > & vecOfInequations,
		const vector< cRangeFactor<tFactors> > & vecYRanges ){

	tFactors dError = 0;
	
	for( unsigned long uiActualPolynom = 0;
			uiActualPolynom < vecOfInequations.size(); uiActualPolynom++){
		
		//evalue the polynomvalue
		tFactors dPolyValue = 0.0;
		for ( unsigned long uiActualFactor = 0;
				uiActualFactor < vecActualPoint.size(); uiActualFactor++ ){
			
			dPolyValue += vecActualPoint[ uiActualFactor ] *
				vecOfInequations[ uiActualPolynom ].vecFactors[ uiActualFactor ];
		}
		
		//evalue the error of the polynomvalue to the correspondending y area
		if ( dPolyValue < vecYRanges[ uiActualPolynom ].min ){
			
			dError += vecYRanges[ uiActualPolynom ].min - dPolyValue;
		}else if ( ((tFactors)vecYRanges[ uiActualPolynom ].max) < dPolyValue ){
			
			dError += dPolyValue - vecYRanges[ uiActualPolynom ].max;
		}//else no error
	}
	
	return dError;
}


/**
 * This function prints the given inequations.
 * It simply calls @see cPolyConstrainFix::print() for all given
 * inequations.
 *
 * @param vecOfInequations a vector with the inequations to output
 * @param outputStream a stream, wher to print the inequations to
 */
template <class tFactors> void fib::algorithms::nLinearInequation::
	printInequations( vector< cLinearConstrainFix<tFactors> > vecOfInequations,
		ostream & outputStream ){
	
	for ( unsigned int uiActualInequation = 0;
			uiActualInequation < vecOfInequations.size(); uiActualInequation++ ){

		vecOfInequations[ uiActualInequation ].print( outputStream );
	}
}


/**
 * This function solves the given vector of inequiations.
 *
 * @param vecOfInequationsInput the vector of linear inequiations to solve
 * @param vecData the data for the linear inequiations
 * @return a vector with the range factors, in which contain the factors
 * 	which solve the given linear inequiations
 */
/*
Polynom Approximation fuer n in N:

gegeben:
- Punkte: P_1( x_1, (yu_1,yo_1 )), …, P_p( x_p, y_p \in (yu_p,yo_p ))
- Grad des Polynoms n, mit n < p

gesucht:
- das Polynom f(x) = \sum_{i=0}^{n} (a_i( x )^i); bzw. Die Faktoren: a_i mit i=0, …, n

Lösung:

Lösung:
setze untere Grenze a_n auf  -inf und die obere auf +inf

1. Eingabe der ungleichungen (vecOfInequationsInput):
yu_1 <=  a_0 + a_1( x_1 ) + ... + a_n( x_1 )^n <= yo_1
yu_2 <=  a_0 + a_1( x_2 ) + ... + a_n( x_2 )^n <= yo_2
...
yu_p <=  a_0 + a_1( x_p ) + ... + a_n( x_p )^n <= yo_p


2. in Dreiecksform bringen:
( <=>? → Verglich wird entsprechend gedreht wenn durch negative x_i geteilt wird)
- mit a_k ist das a_i mit groessten i, dessen untere und ober Grenze nicht gleich ist 
- as_{n} ist der Konstante Faktor, der sich aus den a_i mit jeweils gleicher untere und ober Grenze und dem x Wert der Ungleichung ergibt

yu_1		 <=  a_0 + a_1( x_1 ) + ... + a_n( x_1 )^n <= yo_1
(yu_2 - yu_1)/x_2 	<=>?    a_1 + ... + 2* a_n( x_2 )^(n-1) <=>? (yo_2 – yo_1)/x_2
yu_3/x_3 - yu_2/x_2 + yu_1*(1/x_2 – 1/x_3)	<=>?    a_2 + ... + 3 * a_n( x_3 )^(n-2)  <=>? yo_3/x_3 - yo_2/x_2 + yo_1*(1/x_2 - 1/x_3)
...
yu_n / x_n^n + g_n( yu_1, … yu_{n-1}, x_1, …, x_{n-1}) 	<=>?  k*(k-1)/2 * a_k + as_{k} <=>? yo_n / x_n^n - g_n( yo_1, … yo_{n-1}, x_1, …, x_{n-1}) 
yu_{n+1} / x_{n+1}^n + g_{n+1}( yu_1, … yu_{n}, x_1, …, x_n, x_{n+1})  <=>?   k*(k-1)/2 * a_{k} + as_{k+1} <=>? yo_{n+1} / x_{n+1}^n + g_{n+1}( yo_1, … yo_{n}, x_1, …, x_n, x_{n+1})
...
yu_p / x_p^n + g_p( yu_1, … yu_{n}, x_1, …, x_n, x_p)  	<=>?   k*(k-1)/2 *  a_k  + as_{p}	<=>? yo_p / x_p^n + g_p( yo_1, … yo_{n}, x_1, …, x_n, x_p)


2.b in jeder Ungleichung ein a_i
- b_i Faktor fuer die a_i

g_0( yu_1, … yu_{n}, x_1, …, x_n, x_p)	<=>?  b_0 * a_0 + as_{0} <=>? g_0( yu_1, … yu_{n}, x_1, …, x_n, x_p)
g_1( yu_1, … yu_{n}, x_1, …, x_n, x_p) 	<=>?  b_1 * a_1 + as_{1} <=>? g_1( yu_1, … yu_{n}, x_1, …, x_n, x_p)
g_2( yu_1, … yu_{n}, x_1, …, x_n, x_p)	<=>?  b_2 * a_2 + as_{2} <=>? g_2( yu_1, … yu_{n}, x_1, …, x_n, x_p)
...
yu_n / x_n^n + g_n( yu_1, … yu_{n-1}, x_1, …, x_{n-1}) 	<=>?  k*(k-1)/2 * a_k + as_{k} <=>? yo_n / x_n^n - g_n( yo_1, … yo_{n-1}, x_1, …, x_{n-1}) 
yu_{n+1} / x_{n+1}^n + g_{n+1}( yu_1, … yu_{n}, x_1, …, x_n, x_{n+1})  <=>?   k*(k-1)/2 * a_{k} + as_{k+1} <=>? yo_{n+1} / x_{n+1}^n + g_{n+1}( yo_1, … yo_{n}, x_1, …, x_n, x_{n+1})
...
yu_p / x_p^n + g_p( yu_1, … yu_{n}, x_1, …, x_n, x_p)  	<=>?   k*(k-1)/2 *  a_k  + as_{p}	<=>? yo_p / x_p^n + g_p( yo_1, … yo_{n}, x_1, …, x_n, x_p)


3. Lösungsschema umformen (zu 0 <= p) :

- as'_{n} ist der Konstante Faktor, der sich aus den a_i und y mit jeweils gleicher untere und ober Grenze und dem x Wert der Ungleichung ergibt



4. Faktoren Eingrenzen:

	4. Fuer jede Ungleichung mit maximal einen Faktor mit einer Grenze im Unendlichen:
		1. Passe Faktoren an; für jeden Faktor f = a_i (mit i = 1, … n ) und y*; (enthaelt die Ungleichung einen inf Faktor kann nur dieser gewaehlt werden):
				1. setze anderen nicht f  Faktoren so (auf jeweils ihre Ober- oder Untergrenze), dass sie Formel maximieren; bestimme dann f neu
	5. wenn sich in 4. Aenderungen ergeben haben zurück zu 4.
	6. beginne dann mit diesem Wert Schritt 1. „Lösungschema  aufbauen“ erneut solange für ein a_i sich zuletzt Aenderungen ergeben haben oder es noch nicht eingegrenzt wurde
	7. Wenn alle a_i mit Grenzen belegt und keine Änderungen, wähle jeweils einen Wert (den Mittelwert) fuer a_i aus seinen Bereich aus; beginne mit a_i mit kleinsten i dessen Grenzen noch nicht gleich sind und gehe dann jeweils wieder zum Schritt 4
*/
template <class tX, class tY> vector< cRangeFactor<tY> >
	fib::algorithms::nLinearInequation::solve(
		const vector< cLinearConstrainFix<tY> > & vecOfInequationsInput,
		const vector< fib::algorithms::nD1::cDataPointRange< tX, tY> > & vecData ){
	
	if ( vecOfInequationsInput.empty() ){
		return vector< cRangeFactor<tY> >();
	}
	
	const unsigned long ulNumberOfXFactors = vecOfInequationsInput[0].ulNumberOfFactors;
	
	vector< cRangeFactor<tY> > vecXRanges( ulNumberOfXFactors );
	vector< cRangeFactor<tY> > vecYRanges;
	for( size_t iActualDataPoint = 0;
			iActualDataPoint < vecData.size(); iActualDataPoint++ ){
		
		vecYRanges.push_back( cRangeFactor<tY>(
			vecData[ iActualDataPoint ].minY, vecData[ iActualDataPoint ].maxY ) );
	}

	//find the factors
	set<unsigned long> setOpenXFactors;
	for ( unsigned long uiActualFactor = 0; uiActualFactor < ulNumberOfXFactors;
			uiActualFactor++ ){
		
		setOpenXFactors.insert( uiActualFactor );
	}
	unsigned long uiLastFactor = 0;
	unsigned long uiFactorsToNotChangTillSetAToValue = setOpenXFactors.size();
	while ( ! setOpenXFactors.empty() ){
		
		vector< cLinearConstrainFix<tY> > vecActualInequations = vecOfInequationsInput;
		
		setOpenXFactors.clear();
		for ( unsigned long uiActualFactor = 0; uiActualFactor < ulNumberOfXFactors;
				uiActualFactor++ ){
			
			setOpenXFactors.insert( uiActualFactor );
		}
		
		nullConstantXFactors( vecActualInequations, vecXRanges, setOpenXFactors );
		nullConstantYFactors( vecActualInequations, vecYRanges );
		
#ifdef PRINT_INFOS
		cout<<endl<<"Constants eleminated:"<<endl;
		printInequations( vecActualInequations, cout );
#endif
		//vecFactorAMappings[ i in vecActualReducedInequations[ uiActualPolynom ].vecFactors[ i ] ] = i of a_i
		vector< long > vecFactorAMappings;
		vector< long > vecFactorYMappings;
		
		vector< cLinearConstrainFix<tY> > vecActualReducedInequations =
			reduceNullFactors( vecActualInequations, vecFactorAMappings,
				vecFactorYMappings, uiLastFactor );
		
		if ( vecActualReducedInequations.empty() ){
			break;
		}
		//reduce the 0 factors in the set of inequation
		if ( vecActualReducedInequations[ 0 ].vecFactors.size() <= uiLastFactor ){
			uiLastFactor = 0;
		}
		uiFactorsToNotChangTillSetAToValue--;
		
		if ( setOpenXFactors.empty() ){
			break;
		}
#ifdef PRINT_INFOS
		cout<<endl<<"Polynom 0 factors eleminated form:"<<endl;
		printInequations( vecActualReducedInequations, cout );
#endif
		//create the triangle form
		vector< cLinearConstrainFix<tY> > vecOfInequationsTriangle =
			crateDiagonalForm( vecActualReducedInequations );
#ifdef PRINT_INFOS
		cout<<endl<<"Polynom in triangle form:"<<endl;
		printInequations( vecOfInequationsTriangle, cout );

		//create from the set of inequations inequations of the form: const <= x
		cout<<endl<<"create from the set of inequations inequations of the form: const <= x :"<<endl;
#endif
		vector< cInequation<tY> > vecPolynomRangeConstrains =
			fixInequationsToInequations( vecOfInequationsTriangle,
				vecFactorAMappings, vecFactorYMappings );
		
		const bool bBounderyChanged = reduceBounderies( vecPolynomRangeConstrains, vecXRanges, vecYRanges );
		
		if ( bBounderyChanged ){
			uiFactorsToNotChangTillSetAToValue = setOpenXFactors.size();
		}
		
		if ( setOpenXFactors.empty() ){
			break;
		}
		if (  uiFactorsToNotChangTillSetAToValue == 0 ){
			//choos value for an a_i with the smales boundery size or lowest number i
			vecFactorAMappings = vector< long >( ulNumberOfXFactors );
			for ( unsigned long uiActualFactor = 0; uiActualFactor < ulNumberOfXFactors;
					uiActualFactor++ ){
				vecFactorAMappings[ uiActualFactor ] = uiActualFactor;
			}
			vecFactorYMappings = vector< long >( vecOfInequationsInput.size() );
			for ( unsigned long uiActualFactor = 0;
					uiActualFactor < vecOfInequationsInput.size(); uiActualFactor++ ){
				vecFactorYMappings[ uiActualFactor ] = uiActualFactor;
			}
			
			vector< cInequation<tY> > vecPolynomRangeConstrainsOrg =
				fixInequationsToInequations( vecOfInequationsInput, vecFactorAMappings, vecFactorYMappings );
		
			const bool bBounderyChangedOrg = reduceBounderies( vecPolynomRangeConstrainsOrg, vecXRanges, vecYRanges );
			if ( ! bBounderyChangedOrg ){
				break;
			}else{
				uiFactorsToNotChangTillSetAToValue = setOpenXFactors.size();
			}
		}
#ifdef PRINT_INFOS
		cout<<"Ranges: ";
		for ( unsigned long uiFactor = 0; uiFactor < vecXRanges.size(); uiFactor++ ){
			
			cout<<"a_"<< uiFactor <<"={";
			if ( vecXRanges[ uiFactor ].bMinIsInf ){
				cout<<"inf";
			}else{
				cout<< vecXRanges[ uiFactor ].min;
			}
			cout<<",";
			if ( vecXRanges[ uiFactor ].bMaxIsInf ){
				cout<<"inf";
			}else{
				cout<< vecXRanges[ uiFactor ].max;
			}
			cout<<"}; ";
		}
		cout<<endl;
#endif
		uiLastFactor++;
	}
	
	return vecXRanges;
}

#endif //___N_LINEAR_INEQUATION_CPP__




