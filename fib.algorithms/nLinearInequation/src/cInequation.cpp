/**
 * @file cInequation
 * file name: cInequation.h
 * @author Betti Oesterholz
 * @date 09.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements a class for a inequation.
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
 * This header specifies a class for a inequation.
 * The inequation has the form:
 * constant <= vecFactors[0] * x_0 + ... + vecFactors[n] * x_n
 *
 * The elements are:
 * 	- constant: a constant for the inequation
 * 	- vecFactors[i]: the factors for the inequation
 * 	- x_i: variables for the inequation, theas are not given explicite
 *
 * You can give the factors identifiers to relate them to other formulars.
 */
/*
History:
09.06.2010  Oesterholz  created
26.01.2011  Oesterholz  method evalue() added
03.04.2011  Oesterholz  method evalueValue() added
04.04.2011  Oesterholz  method FEATURE_INEQUIATION_EVALUE_FAST added
*/


#ifndef ___C_INEQUATION_CPP__
#define ___C_INEQUATION_CPP__

#include "cInequation.h"

#include "fibDatatyps.h"


using namespace fib::algorithms::nLinearInequation;


/**
 * standardconstructor
 */
template <class tFactors> cInequation<tFactors>::cInequation():
		constant( 0.0 ){
}


/**
 * This method print the inequation in a readebel form to the given
 * output stream outputSream.
 *
 * @param outputSream the stream wher to print this inequation to
 */
template <class tFactors> void cInequation<tFactors>::
		print( ostream & outputStream ) const{
	
	outputStream<<constant;
	
	outputStream<<" <= ";
	
	bool bPrintPlus = false;
	for ( unsigned long uiActualFactor = 0;
			uiActualFactor < vecFactors.size(); uiActualFactor++ ){
		
		if ( vecFactors[ uiActualFactor ] == 0.0 ){
			continue;//skip
		}
		if ( bPrintPlus ){
			outputStream<<" + ";
		}
		if ( uiActualFactor < vecIdentifiers.size() ){
			outputStream<< vecFactors[ uiActualFactor ] <<"*f_"<< vecIdentifiers[ uiActualFactor ];
		}else{
			outputStream<< vecFactors[ uiActualFactor ] <<"*f_"<< uiActualFactor;
		}
		bPrintPlus = true;
	}
	if ( ! bPrintPlus ){
		//no factor printed -> print 0
		outputStream<< "0";
	}
	
	outputStream<<endl;
}


/**
 * This method evalues the inequiation for the given values.
 * constant <= vecFactors[0] * vecValues[0] + ... + vecFactors[n] * vecValues[n]
 *
 * @return true if the inequation is true for the values, else false
 */
template <class tFactors> bool cInequation<tFactors>::evalue(
		const vector< tFactors > & vecValues ) const{

#ifdef FEATURE_INEQUIATION_EVALUE_FAST
	//evalue: vecFactors[0] * vecValues[0] + ... + vecFactors[n] * vecValues[n]
	tFactors evaluedValue = ((tFactors)(0));
	const size_t uiNumberOfFactors = min( vecFactors.size(),
		vecValues.size() );
	for ( unsigned long uiActualFactor = 0;
			uiActualFactor < uiNumberOfFactors; uiActualFactor++ ){
		
		evaluedValue += vecFactors[ uiActualFactor ] * vecValues[ uiActualFactor ];
	}
	//compare evalues value with the constant
	//return ( constant <= evaluedValue ); with lower precision
	return constant <= evaluedValue;

#else //FEATURE_INEQUIATION_EVALUE_FAST
	//evalue: vecFactors[0] * vecValues[0] + ... + vecFactors[n] * vecValues[n]
	tFactors evaluedValue = ((tFactors)(0));
	const size_t uiNumberOfFactors = min( vecFactors.size(),
		vecValues.size() );
	for ( unsigned long uiActualFactor = 0;
			uiActualFactor < uiNumberOfFactors; uiActualFactor++ ){
		
		fib::addToFirst( evaluedValue,
			vecFactors[ uiActualFactor ] * vecValues[ uiActualFactor ] );
	}
	//compare evalues value with the constant
	//return ( constant <= evaluedValue ); with lower precision
#define FEATURE_INEQUIATION_EVALUE_USE_COMPARE_DOUBLE
#ifdef FEATURE_INEQUIATION_EVALUE_USE_COMPARE_DOUBLE
	return ( compareDouble( constant, evaluedValue ) ||
		( constant <= evaluedValue ) );
#else //FEATURE_INEQUIATION_EVALUE_USE_COMPARE_DOUBLE
	const tFactors diffValue = evaluedValue - constant;
	return ( isEqualNull( diffValue ) || ( 0 <= diffValue ) );
#endif //FEATURE_INEQUIATION_EVALUE_USE_COMPARE_DOUBLE
#endif //FEATURE_INEQUIATION_EVALUE_FAST
}


/**
 * This method evalues the inequiation for the given values.
 * constant <= vecFactors[0] * vecValues[0] + ... + vecFactors[n] * vecValues[n]
 *
 * @return vecFactors[0] * vecValues[0] + ... + vecFactors[n] * vecValues[n] - constant;
 * 	if the value is negativ the inequation is not fulfilled, else it is
 * 	fulfilled
 */
template <class tFactors> tFactors cInequation<tFactors>::evalueValue(
		const vector< tFactors > & vecValues ) const{
	
#ifdef FEATURE_INEQUIATION_EVALUE_FAST
	//evalue: vecFactors[0] * vecValues[0] + ... + vecFactors[n] * vecValues[n]
	tFactors evaluedValue = ((tFactors)(0));
	const size_t uiNumberOfFactors = min( vecFactors.size(),
		vecValues.size() );
	for ( unsigned long uiActualFactor = 0;
			uiActualFactor < uiNumberOfFactors; uiActualFactor++ ){
		
		evaluedValue += vecFactors[ uiActualFactor ] * vecValues[ uiActualFactor ];
	}
	//return difference
	return ( evaluedValue - constant );
	
#else //FEATURE_INEQUIATION_EVALUE_FAST

	//evalue: vecFactors[0] * vecValues[0] + ... + vecFactors[n] * vecValues[n]
	tFactors evaluedValue = ((tFactors)(0));
	const size_t uiNumberOfFactors = min( vecFactors.size(),
		vecValues.size() );
	for ( unsigned long uiActualFactor = 0;
			uiActualFactor < uiNumberOfFactors; uiActualFactor++ ){
		
		fib::addToFirst( evaluedValue,
			vecFactors[ uiActualFactor ] * vecValues[ uiActualFactor ] );
	}
	//return difference
	return fib::sub( evaluedValue, constant );
#endif //FEATURE_INEQUIATION_EVALUE_FAST
}


/**
 * @return true if the given inequiation is the same as this inequiation,
 * 	else false;
 * 	two inequiations are the same, if all factors and the constant of
 * 	one inequiation multiplyed ba a fixed constant are the same to
 * 	the other inequiation
 */
template <class tFactors> bool cInequation<tFactors>::sameInequiation(
		const cInequation< tFactors > & inequiation  ) const{
	
	//if the inequiation differs yust in the sign and an multiplicator
	tFactors tMultiplicator = ((tFactors)(0));
	if ( constant == ((tFactors)(0)) ){
		if ( inequiation.constant != ((tFactors)(0)) ){
			return false;
		}//else both are 0
	}else{
		if ( inequiation.constant == ((tFactors)(0)) ){
			return false;
		}else{
			tMultiplicator = constant / inequiation.constant;
			if ( tMultiplicator < 0 ){
				//the sign switched
				return false;
			}
		}
	}
	
	const size_t uiFactorsInOld = vecFactors.size();
	const size_t uiFactorsInNew = inequiation.vecFactors.size();
	const size_t uiMinFactors = min( uiFactorsInOld, uiFactorsInNew );
	for ( unsigned int uiActualFactor = 0; uiActualFactor < uiMinFactors;
			uiActualFactor++ ){
		
		if ( vecFactors[ uiActualFactor ] == ((tFactors)(0)) ){
			if ( inequiation.vecFactors[ uiActualFactor ] != ((tFactors)(0)) ){
				return false;
			}//else both are 0
		}else{
			if ( inequiation.vecFactors[ uiActualFactor ] == ((tFactors)(0)) ){
				return false;
			}else{//else both are not 0
				const tFactors tMultiplicatorActual =
					vecFactors[ uiActualFactor ] /
						inequiation.vecFactors[ uiActualFactor ];
					
				if ( tMultiplicator != ((tFactors)(0)) ){
					if ( tMultiplicatorActual != tMultiplicator ){
						return false;
					}
				}else{//tMultiplicator == ((tFactors)(0))
					tMultiplicator = tMultiplicatorActual;
				}
			}
		}
	}//end for all factors
	if ( tMultiplicator < 0 ){
		//the sign switched
		return false;
	}
	//all not checked factors should be 0
	for ( unsigned int uiActualFactor = uiMinFactors; uiActualFactor < uiFactorsInOld;
			uiActualFactor++ ){
		//all remaining factors should be 0
		if ( vecFactors[ uiActualFactor ] != ((tFactors)(0)) ){
			return false;
		}
	}
	for ( unsigned int uiActualFactor = uiMinFactors; uiActualFactor < uiFactorsInNew;
			uiActualFactor++ ){
		//all remaining factors should be 0
		if ( inequiation.vecFactors[ uiActualFactor ] != ((tFactors)(0)) ){
			return false;
		}
	}

	return true;
}


/**
 * @return true if the given inequiation is the same as this inequiation
 * 	except that the constant (or operator) sign is switched, else false;
 * 	two inequiations are the same, if all factors and the constant of
 * 	one inequiation multiplyed ba a fixed constant are the same to
 * 	the other inequiation
 */
template <class tFactors> bool cInequation<tFactors>::antiInequiation(
		const cInequation< tFactors > & inequiation  ) const{
	
	//if the inequiation differs yust in the sign and an multiplicator
	tFactors tMultiplicator = ((tFactors)(0));
	if ( constant == ((tFactors)(0)) ){
		if ( inequiation.constant != ((tFactors)(0)) ){
			return false;
		}//else both are 0
	}else{
		if ( inequiation.constant == ((tFactors)(0)) ){
			return false;
		}else{
			tMultiplicator = constant / inequiation.constant;
			if ( 0 < tMultiplicator ){
				//the sign dosn't switched
				return false;
			}
		}
	}
	
	const size_t uiFactorsInOld = vecFactors.size();
	const size_t uiFactorsInNew = inequiation.vecFactors.size();
	const size_t uiMinFactors = min( uiFactorsInOld, uiFactorsInNew );
	for ( unsigned int uiActualFactor = 0; uiActualFactor < uiMinFactors;
			uiActualFactor++ ){
		
		if ( vecFactors[ uiActualFactor ] == ((tFactors)(0)) ){
			if ( inequiation.vecFactors[ uiActualFactor ] != ((tFactors)(0)) ){
				return false;
			}//else both are 0
		}else{
			if ( inequiation.vecFactors[ uiActualFactor ] == ((tFactors)(0)) ){
				return false;
			}else{//else both are not 0
				const tFactors tMultiplicatorActual =
					vecFactors[ uiActualFactor ] /
						inequiation.vecFactors[ uiActualFactor ];
					
				if ( tMultiplicator != ((tFactors)(0)) ){
					if ( tMultiplicatorActual != tMultiplicator ){
						return false;
					}
				}else{//tMultiplicator == ((tFactors)(0))
					tMultiplicator = tMultiplicatorActual;
				}
			}
		}
	}//end for all factors
	if ( 0 < tMultiplicator ){
		//the sign dosn't switched
		return false;
	}
	//all not checked factors should be 0
	for ( unsigned int uiActualFactor = uiMinFactors; uiActualFactor < uiFactorsInOld;
			uiActualFactor++ ){
		//all remaining factors should be 0
		if ( vecFactors[ uiActualFactor ] != ((tFactors)(0)) ){
			return false;
		}
	}
	for ( unsigned int uiActualFactor = uiMinFactors; uiActualFactor < uiFactorsInNew;
			uiActualFactor++ ){
		//all remaining factors should be 0
		if ( inequiation.vecFactors[ uiActualFactor ] != ((tFactors)(0)) ){
			return false;
		}
	}

	return true;
}


/**
 * @return true if the inequation is fulfilled for all values, else false
 * 	(false -> some values not fulfilled it)
 */
template <class tFactors> bool cInequation<tFactors>::isTrue() const{
	
	const size_t uiNumberOfFactors = vecFactors.size();
	for ( unsigned long uiActualFactor = 0;
			uiActualFactor < uiNumberOfFactors; uiActualFactor++ ){
		
		if ( ! isEqualNull( vecFactors[ uiActualFactor ] ) ){
			return false;
		}
	}
	//all factors are 0
	//return ( constant <= 0 ); with lower precision
	return ( isEqualNull( constant ) || ( constant <= 0 ) );
}


/**
 * @return true if the inequation is not fulfilled for all values
 * 	(false -> some values fulfilled it)
 */
template <class tFactors> bool cInequation<tFactors>::isFalse() const{
	
	const size_t uiNumberOfFactors = vecFactors.size();
	for ( unsigned long uiActualFactor = 0;
			uiActualFactor < uiNumberOfFactors; uiActualFactor++ ){
		
		if ( ! isEqualNull( vecFactors[ uiActualFactor ] ) ){
			return false;
		}
	}
	//all factors are 0
	return ( 0 < constant );
}




#endif //___C_INEQUATION_CPP__




