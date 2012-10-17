/**
 * @file nBits
 * file name: nBits.cpp
 * @author Betti Oesterholz
 * @date 14.03.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header implements functions to analyse the fib-objects to get bit counts.
 * Copyright (C) @c GPL3 2011 Betti Oesterholz
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
 * This header implements functions to analyse the fib-objects to get bit
 * counts.
 */
/*
History:
14.03.2011  Oesterholz  created
23.05.2011  Oesterholz  cIf and conditions added
*/



#include "version.h"

#include "nBits.h"

#include "fibDatatyps.h"

#include "cFunction.h"
#include "cUnderFunction.h"
#include "cFunctionOneValue.h"
#include "cFunctionTwoValue.h"
#include "cFunctionIf.h"

#include "cIf.h"
#include "cCondition.h"
#include "cConditionNot.h"
#include "cConditionTwoValue.h"
#include "cConditionComparison.h"


#include <vector>
#include <set>
#include <list>
#include <ostream>



using namespace std;
using namespace fib;
using namespace fib::algorithms::nAnalyse::nFibObject;



/**
 * This function returns the minimal number of bits needed to store the
 * mantissa values, of all underfunction values in the given fib-object.
 *
 * @param pFibObject the fib object to analyse
 * @return  a pair with:
 * 	-first: the minimal number of bits needed to store the mantissa values
 * 	-second: the number of values in functions
 */
pair< unsigned int, unsigned long > nBits::evalueMaxFunctionValuesMantissaBits(
		const cFibElement * pFibObject ){
	
	if ( pFibObject == NULL ){
		//no bits needed
		return pair< unsigned int, unsigned long >( 0, 0 );
	}
	unsigned int uiMinBitsForMantissas = 0;
	unsigned long ulNumberOfValues = 0;
	//for every fib -element in the fib -object
	
	unsigned long ulFibElementsToCheck = pFibObject->getNumberOfElements();
	for ( const cFibElement * pActualFibElement = pFibObject;
			(pActualFibElement != NULL) && ( ulFibElementsToCheck != 0 );
			pActualFibElement = pActualFibElement->getNextFibElement(),
			ulFibElementsToCheck-- ){

		if ( ( pActualFibElement->getType() == 'f' ) ||
				( pActualFibElement->getType() == 'i' ) ){
			/*if the fib -element is an functionelement
			-> search for all values*/
			
			//the list with the underfunctions, wich whern't searched
			list<const cUnderFunction *> liOpenUnderFunctions;
			list<const cCondition *> liOpenSubConditions;
			if ( pActualFibElement->getType() == 'f' ){
			
				const cUnderFunction * pUnderFunction =
					((cFunction*)pActualFibElement)->getUnderFunction();
				liOpenUnderFunctions.push_back( pUnderFunction );
			}else{// pActualFibElement->getType() == 'i' )
				const cCondition * pCondition =
					((cIf*)pActualFibElement)->getCondition();
				liOpenSubConditions.push_back( pCondition );
			}
			
			while ( ( ! liOpenUnderFunctions.empty() ) ||
					( ! liOpenSubConditions.empty() ) ){
				
				while ( ! liOpenUnderFunctions.empty() ){
					//search every underfunction
					const cUnderFunction * pUnderFunction =
						liOpenUnderFunctions.front();
					liOpenUnderFunctions.pop_front();
					
					if ( pUnderFunction->getNumberOfUnderFunctions() == 0 ){
						//this is a variable or value underfunction
						if ( pUnderFunction->getType() == cUnderFunction::FUNCTION_VALUE ){
							//evalue the minimal number of bits for the mantissa
							const doubleFib dValue = pUnderFunction->getValue();
							longFib lMantissa = 0;
							longFib lExponent = 0;
							intFib iSizeMantissa = 0;
							intFib iSizeExponent = 0;
							
							decomposeDoubleFib( dValue, &lMantissa, &lExponent,
								&iSizeMantissa, &iSizeExponent );
							
							if ( uiMinBitsForMantissas < ((unsigned int)(iSizeMantissa)) ){
								uiMinBitsForMantissas = iSizeMantissa;
							}
							ulNumberOfValues++;
						}//else ignore variable underfunctions
						
					}else if ( pUnderFunction->getNumberOfUnderFunctions() == 1 ){
						/*this is a one value underfunction
						-> add the one underfunctions into the to search through underfunctions*/
						liOpenUnderFunctions.push_back(
							((cFunctionOneValue*)pUnderFunction)->getUnderFunction() );
						
					}else if ( pUnderFunction->getNumberOfUnderFunctions() == 2 ){
						/*this is a two value underfunction
						-> add the two underfunctions into the to search through underfunctions*/
					
						liOpenUnderFunctions.push_back(
							((cFunctionTwoValue*)pUnderFunction)->getFirstUnderFunction() );
						liOpenUnderFunctions.push_back(
							((cFunctionTwoValue*)pUnderFunction)->getSecondUnderFunction() );
						
						//check special cases
						if ( pUnderFunction->getType() == cUnderFunction::FUNCTION_IF ){
							//if subfunction add condition
							liOpenSubConditions.push_back(
								((cFunctionIf*)pUnderFunction)->getCondition() );
						}
					}
				}//end while open underfunctions exists
				while ( ! liOpenSubConditions.empty() ){
					//search every subcondition
					const cCondition * pSubCondition =
						liOpenSubConditions.front();
					liOpenSubConditions.pop_front();
					
					if ( pSubCondition->getNumberOfConditions() == 1 ){
						/*this is a one value subcondition
						-> add the one subcondition into the to search through subconditions*/
						liOpenSubConditions.push_back(
							((cConditionNot*)pSubCondition)->getSubCondition() );
						
					}else if ( pSubCondition->getNumberOfConditions() == 2 ){
						/*this is a two value subcondition
						-> add the two subconditions into the to search through subconditions*/
						liOpenSubConditions.push_back(
							((cConditionTwoValue*)pSubCondition)->getFirstSubCondition() );
						liOpenSubConditions.push_back(
							((cConditionTwoValue*)pSubCondition)->getSecondSubCondition() );
						
					}else if ( pSubCondition->getNumberOfUnderFunctions() == 2 ){
						/*this is a comparison condition with two underfunctions
						-> add the two underfunctions into the to search through underfunctions*/
					
						liOpenUnderFunctions.push_back(
							((cConditionComparison*)pSubCondition)->getFirstSubFunction() );
						liOpenUnderFunctions.push_back(
							((cConditionComparison*)pSubCondition)->getSecondSubFunction() );
					}
				}//end while open subconditions exists
				
			}//end while open subelements exists
		}//end if function or if-element
	}//end for all fib-elements

	return make_pair( uiMinBitsForMantissas, ulNumberOfValues );
}















