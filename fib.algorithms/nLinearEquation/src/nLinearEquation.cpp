/**
 * @file nLinearEquation
 * file name: nLinearEquation.h
 * @author Betti Oesterholz
 * @date 11.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements functions for linear equation.
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
 * This implements functions for linear equation.
 */
/*
History:
11.06.2010  Oesterholz  created
*/


#include "nLinearEquation.h"

#include "fibDatatyps.h"

#ifndef ___N_LINEAR_EQUATION_CPP__
#define ___N_LINEAR_EQUATION_CPP__

//debugging switches
//#define PRINT_INFOS
//more debugging information
//#define PRINT_INFOS_2


#ifdef PRINT_INFOS_2
#define PRINT_INFOS
#endif
#ifdef PRINT_INFOS
	#include <iostream>
	using namespace std;
#endif

using namespace fib::algorithms::nLinearEquation;


/**
 * This functions converts the given vector of equation into a diagonal
 * form. In this form ther exsists only one factor in the liniar formular
 * (@see cLinearEquation::vecFactors) in every equation. For the
 * first n equation this factor is the n'th factor. For the remaining
 * equation, this factor is the last factor. (n is the number of
 * factors @see cLinearEquation::vecFactors.size())
 * The convertion is done by multiplying equation with a number
 * (@see cLinearEquation::mult()) or adding two equation of the
 * vector of equations (@see cLinearEquation::operator+()).
 *
 * @param vecOfEquations a reference to the vector of equation, which
 * 	to convert into the diagonal form (this is changed)
 * @return a pointer to the converted vector of equations
 */
template <class tFactors> vector< cLinearEquation<tFactors> > &
	fib::algorithms::nLinearEquation::crateDiagonalForm(
		vector< cLinearEquation<tFactors> > & vecOfEquations ){
		
	if ( vecOfEquations.empty() ){
		//nothing to do
		return vecOfEquations;
	}
#ifdef PRINT_INFOS
	cout<<endl<<"Input equiations (#equiations="<<vecOfEquations.size()<<" #factors="<<vecOfEquations[ 0 ].vecFactors.size()<<"):"<<endl;
	printEquations( vecOfEquations, cout );
#endif
	const unsigned long ulNumberOfEquiations = vecOfEquations.size();
	const unsigned long ulNumberOfEquiationFactors =
		vecOfEquations[ 0 ].vecFactors.size();
	//the number of factors which should be one in the triangle form
	const unsigned long uiNumberOfFactors = min(
		ulNumberOfEquiationFactors, ulNumberOfEquiations );

	cLinearEquation<tFactors> equiationTmp;
	
	/*this vector stores for every factor, which should be later 1 in the
	triangle form the index of the equiation for it;
	so the i'th factor should be one in the vecTriangleFactorIndex[ i ]'th equiation;
	if -1 no equiation eqsists for this factor*/
	vector<long> vecTriangleFactorIndex( ulNumberOfEquiationFactors, -1 );
	
#ifdef PRINT_INFOS_2
	cout<<"Eleminating the first factors of the equiation"<<endl<<flush;
#endif
	unsigned long uiNextTriangleFactor = 0;
	unsigned long uiFirstNotTriangleEquiation = 0;
	
	while ( (uiFirstNotTriangleEquiation < uiNumberOfFactors)
			&& ( uiNextTriangleFactor < ulNumberOfEquiationFactors ) ){
		//uiFirstNotTriangleEquiation = actual equiation to change
#ifdef PRINT_INFOS_2
		cout<<"Actual equiation: "<<uiFirstNotTriangleEquiation<<"  trying to create the triangle factor: "<<uiNextTriangleFactor<<endl<<flush;
#endif
		for ( unsigned long uiActualFactor2 = 0;
				uiActualFactor2 <= uiNextTriangleFactor; uiActualFactor2++ ){
			
			const long lFactorEquiation = vecTriangleFactorIndex[ uiActualFactor2 ];
			if ( lFactorEquiation == -1 ){
				//no equiation to reduce this factor -> skip it
				continue;
			}
#ifdef PRINT_INFOS_2
			cout<<"Try reducing "<<uiFirstNotTriangleEquiation<<"'th factor of "<<uiActualFactor2<<"'th equiation to 0, with the help of the "<<lFactorEquiation<<" equiation "<<endl<<flush;
#endif
			//uiActualFactor2 = actual factor in actual equiation to change
			const tFactors dFactor2 = vecOfEquations[ uiFirstNotTriangleEquiation ].vecFactors[ uiActualFactor2 ];
			if ( dFactor2 == (tFactors)(0.0) ){
				//factor is allready 0 -> skip it
#ifdef PRINT_INFOS_2
				cout<<"Factor is allready 0 -> skip it "<<endl<<flush;
#endif
				continue;
			}
			const tFactors dFactor1 = vecOfEquations[ lFactorEquiation  ].vecFactors[ uiActualFactor2 ];
			if ( dFactor1 == (tFactors)(0.0) ){
				//can't reduce this factor -> skip it
				continue;
			}
			const tFactors dMultiplyTmpWith = ((tFactors)(-1.0)) * dFactor2 / dFactor1;

			equiationTmp = vecOfEquations[ lFactorEquiation ];
			equiationTmp.mult( dMultiplyTmpWith );
			vecOfEquations[ uiFirstNotTriangleEquiation ] += equiationTmp;

			//factor should now be 0, but to make sure (because of rounding errors)
			vecOfEquations[ uiFirstNotTriangleEquiation ].vecFactors[ uiActualFactor2 ] = (tFactors)(0.0);
		}
		
		if ( vecOfEquations[ uiFirstNotTriangleEquiation ].vecFactors[ uiNextTriangleFactor ] != (tFactors)(0.0) ){
			/*evalue the factor for this equiation which should be later 1 in
			the triangle form <- this is the first factor in the equiation not 0*/
#ifdef PRINT_INFOS_2
			cout<<"checking next equiation and triangle factor."<<endl<<flush;
#endif
			//this equiation should have uiNextTriangleFactor as the 1 factor in the triangle form
			vecTriangleFactorIndex[ uiNextTriangleFactor ] = uiFirstNotTriangleEquiation;
			uiNextTriangleFactor++;
			
			//go to the next factor
			uiFirstNotTriangleEquiation++;
		}else{
			/*if the actual factor in the actual equiation is null, try to
			replace the actual equiation with one after it and try again
			(because the factor is needed for the later equiations)*/
#ifdef PRINT_INFOS_2
			cout<<"the actual "<<uiNextTriangleFactor<<"'th factor in the actual "<<
				uiFirstNotTriangleEquiation<<"'th equiation is null; try switchen equiation with a later"<<endl<<flush;
			cout<<"equiations"<<endl<<flush;
			printEquations( vecOfEquations, cout );
#endif
			const unsigned long uiLastActualEquiation = uiFirstNotTriangleEquiation;
			while ( vecOfEquations[ uiLastActualEquiation ].vecFactors[ uiNextTriangleFactor ] == (tFactors)(0.0) ){
	
				unsigned long uiActualEquiation = ulNumberOfEquiations - 1;
				bool bEquiationsSwitched = false;
				for ( ; ( uiLastActualEquiation < uiActualEquiation ) &&
						( ! bEquiationsSwitched ) ; uiActualEquiation-- ){
					//for every equiation after the actual equiation
					for ( unsigned int uiActualFactor1 = 0;
							( uiActualFactor1 <= uiNextTriangleFactor ) &&
							( ! bEquiationsSwitched ) ; uiActualFactor1++ ){
						//for every factor till the uiNextTriangleFactor'th factor (inclusive it)
						if ( vecOfEquations[ uiActualEquiation ].vecFactors[ uiActualFactor1 ] != (tFactors)(0.0) ){
							/*equiation with a factor till the
							uiNextTriangleFactor'th factor (inclusive it) not 0 found
							-> switch equiations and try to reduce the factors
							till the uiNextTriangleFactor'th factor*/
#ifdef PRINT_INFOS_2
							cout<<"switchen equiations "<<uiLastActualEquiation<<" and "<<uiActualEquiation<<endl<<flush;
#endif
							equiationTmp = vecOfEquations[ uiLastActualEquiation ];
							vecOfEquations[ uiLastActualEquiation ] = vecOfEquations[ uiActualEquiation ];
							vecOfEquations[ uiActualEquiation ] = equiationTmp;
							bEquiationsSwitched = true;
							break;
						}
					}
				}
				if ( bEquiationsSwitched ){
					//reduce factors of the found/switched equiation
					break;
				}else{
					/*can't switch with a equiation which has the uiNextTriangleFactor factor
					-> no equiation has this factor -> everything is ok -> take next factor*/
#ifdef PRINT_INFOS_2
					cout<<"can't switch with a equiation which has the "<<uiNextTriangleFactor<<" factor"<<endl<<flush;
#endif
					uiNextTriangleFactor++;
					
					if ( ulNumberOfEquiationFactors <= uiNextTriangleFactor ){
						//no more factors to check
						break;
					}
				}
			}//end while
		}
	}
	/*now the first uiNumberOfFactors inequations of vecOfEquations are in triangle form*/
#ifdef PRINT_INFOS
	cout<<endl<<"Polynom in triangle form with more than one a_i each:"<<endl<<flush;
	printEquations( vecOfEquations, cout );
#endif
	//every triangle a_i factor to 1.0
	for ( unsigned long uiActualFactor = 0; uiActualFactor < ulNumberOfEquiationFactors;
			uiActualFactor++ ){
		//change the next factor not 0 to 1
		const long lFactorEquiation = vecTriangleFactorIndex[ uiActualFactor ];
		if ( lFactorEquiation == -1 ){
			//no equiation to change this factor to 1 -> skip it
			continue;
		}
		const tFactors dFactor = vecOfEquations[ lFactorEquiation ].vecFactors[ uiActualFactor ];
		
		if ( dFactor == (tFactors)(1.0) ){
			//factor is allready 1 -> skip it
			continue;
		}
		if ( dFactor == (tFactors)(0.0) ){
			//factor is allready 0 (should not happen) -> skip it
			continue;
		}//else change actual factor to 1
		vecOfEquations[ lFactorEquiation ].mult( ((tFactors)(1.0)) / dFactor );
		//factor should now be 1, but to make sure (because of rounding errors)
		vecOfEquations[ lFactorEquiation ].vecFactors[ uiActualFactor ] = (tFactors)(1.0);
	}
	//new the factor a_i for the triangle form is 1
	
	if ( 1 <= uiNumberOfFactors ){
		//eliminate all factores in the first uiNumberOfFactors inequations except the one
		for ( unsigned long uiActualEquiation = 0; uiActualEquiation < uiNumberOfFactors - 1;
				uiActualEquiation++ ){
			//uiActualEquiation = actual equiation to change
			for ( unsigned long uiActualFactor = uiActualEquiation + 1; uiActualFactor < ulNumberOfEquiationFactors;
					uiActualFactor++ ){
				
				if ( vecTriangleFactorIndex[ uiActualFactor ] == -1 ){
					//no equiation to reduce this factor -> skip it
					continue;
				}
				const unsigned int uiEquiationToReduceFactor =
					vecTriangleFactorIndex[ uiActualFactor ];
				if ( uiEquiationToReduceFactor == uiActualEquiation ){
					//don't change the factor for this equiation -> skip it
					continue;
				}
				//uiActualFactor = actual factor in actual equiation to change
				const tFactors dFactor2 = vecOfEquations[ uiActualEquiation ].vecFactors[ uiActualFactor ];
				if ( dFactor2 == (tFactors)(0.0) ){
					//factor is allready 0 -> skip it
					continue;
				}
				const tFactors dMultiplyTmpWith = ((tFactors)(-1.0)) * dFactor2;
				equiationTmp = vecOfEquations[ uiEquiationToReduceFactor ];
				equiationTmp.mult( dMultiplyTmpWith );
				
				vecOfEquations[ uiActualEquiation ] += equiationTmp;
				
				//factor should now be 0, but to make sure (because of rounding errors)
				vecOfEquations[ uiActualEquiation ].vecFactors[ uiActualFactor ] = (tFactors)(0.0);
			}
		}
	}
	/*now the first uiNumberOfFactors inequations of vecOfEquations are
	in triangle form and have maximal one a_i (i < uiNumberOfFactors) factor, wich is 1*/
	
	//eleminate all factors in the remaining inequations
	for( unsigned long uiActualEquiation = uiFirstNotTriangleEquiation;
			uiActualEquiation < ulNumberOfEquiations; uiActualEquiation++ ){
	
		for ( unsigned long uiActualFactor = 0; uiActualFactor < ulNumberOfEquiationFactors;
				uiActualFactor++ ){
			
			const long lFactorEquiation = vecTriangleFactorIndex[ uiActualFactor ];
			if ( lFactorEquiation == -1 ){
				//no equiation to reduce this factor -> skip it
				continue;
			}
			const tFactors dFactor2 = vecOfEquations[ uiActualEquiation ].vecFactors[ uiActualFactor ];
			if ( dFactor2 == (tFactors)(0.0) ){
				//factor is allready 0 -> skip it
				continue;
			}
			//uiActualFactor = actual factor in actual equiation to change
			const tFactors dMultiplyTmpWith = ((tFactors)(-1.0)) * dFactor2;
			equiationTmp = vecOfEquations[ lFactorEquiation ];
			equiationTmp.mult( dMultiplyTmpWith );
			
			vecOfEquations[ uiActualEquiation ] += equiationTmp;
			
			//factor should now be 0, but to make sure (because of rounding errors)
			vecOfEquations[ uiActualEquiation ].vecFactors[ uiActualFactor ] =
				(tFactors)(0.0);
		}
	}

#ifdef PRINT_INFOS
	cout<<endl<<"Polynom in triangle form with one a_i = 1 each (if possible):"<<endl<<flush;
	printEquations( vecOfEquations, cout );
#endif

	return vecOfEquations;
}


/**
 * This function prints the given inequiations.
 * It simply calls @see cPolyConstrainFix::print() for all given
 * inequiations.
 *
 * @param vecOfInequations a vector with the inequiations to output
 * @param outputStream a stream, wher to print the inequiations to
 */
template <class tFactors> void fib::algorithms::nLinearEquation::
	printEquations( vector< cLinearEquation<tFactors> > vecOfInequations,
		ostream & outputStream ){
	
	for ( unsigned int uiActualInequation = 0;
			uiActualInequation < vecOfInequations.size(); uiActualInequation++ ){

		vecOfInequations[ uiActualInequation ].print( outputStream );
	}
}

#endif //___N_LINEAR_EQUATION_CPP__





