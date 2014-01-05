
//TODO check

/**
 * @file nFibObjectTools
 * file name: nFibObjectTools.cpp
 * @author Betti Oesterholz
 * @date 19.07.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a namespace with basic functions or tools for Fib objects.
 *
 *
 * Copyright (C) @c GPL3 2013 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (GPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
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
 * This file implements a namespace with basic functions or tools for Fib objects.
 *
 */
/*
History:
19.07.2013  Oesterholz  created
*/



#include "nFibObjectTools.h"

#include "cRoot.h"
#include "fib/incl/cFibVariable.h"


using namespace fib::nCreator;
using namespace fib;


/**
 * This function will evalue the input variables for the given
 * Fib object.
 * It will evalue all variables used in the Fib object, but not defined
 * in it. Also input variables are input variables of the root element
 * pFibObject, if pFibObject is a root element.
 *
 * @param pFibObject the pointer to the Fib object, for which to evalue
 * 	the input variables
 * @param bTillRoot if true searches for input variables in the Fib
 * 	object for pFibObject till the root Fib element (Fib element
 * 	with no superior), else the input variables for pFibObject will
 * 	be returned
 * @return a list with the (pointers to) the input variables of the
 * 	given Fib object;
 * 	First it will contain the input variables of the root element
 * 	pFibObject, if pFibObject is a root element.
 */
list< cFibVariable * > nFibObjectTools::evalueInputVariables(
		cFibElement * pFibObject, const bool bTillRoot ){
	
	if ( pFibObject == NULL ){
		//no Fib object -> no input variables
		return list< cFibVariable * >();
	}
	/*steps:
	 - if top most Fib element is root element -> add its input variables to the front
	 - evalue the used and defined varibles in the Fib object for the Fib node
	 - evalue all used variables not defined in the Fib object
	 */
	list< cFibVariable * > liInputVariables;
	//add (real) input variables of the next superior root to the front
	if ( pFibObject->getType() == 'r' ){
		//if top most Fib element is root element -> add its input variables to the front
		//pFibObject is a root element -> get its input variables
		liInputVariables = ((cRoot*)pFibObject)->getInputVariables();
	}else{//add the input variables of the next root element as input variables
		cRoot * pNextRoorElement = pFibObject->getSuperiorRootElement();
		if ( pNextRoorElement ){
			liInputVariables = pNextRoorElement->getInputVariables();
		}
	}
	//evalue the used and defined varibles in the Fib object for the Fib node
	set< cFibVariable* > setUsedVariables =
		pFibObject->getUsedVariables( bTillRoot ? ED_ALL : ED_BELOW_EQUAL );
	
//#define FEATURE_NEW_EVALUE_INPUT_VARIABLES
#ifdef FEATURE_NEW_EVALUE_INPUT_VARIABLES
	/*Note: dosn't work if the using Fib element is not in the same
	 * 	Fib object as the defining Fib object*/
	/* - get the smaales and greates Fib element number of the Fib object
	 * - evalue for every used variable if its defining Fib element has a
	 * 	Fib element number in the range of the given Fib object*/
	//Fib element number of the first Fib element in the Fib object
	const unsignedIntFib uiSmaalestFibElementNr =
		pFibObject->getNumberOfElement();
	//Fib element number of the last next Fib element in the Fib object
	const unsignedIntFib uiBiggestFibElementNr =
		uiSmaalestFibElementNr + pFibObject->getNumberOfElements() - 1;
	
	for ( set< cFibVariable* >::const_iterator
			itrUsedVariable = setUsedVariables.begin();
			itrUsedVariable != setUsedVariables.end(); itrUsedVariable++ ){
		//get defining Fib element of the used variable
		const cFibElement * pDefiningFibElement =
			(*itrUsedVariable)->getDefiningElement();
		//check Fib element number of the defining Fib element
		if ( pDefiningFibElement != NULL ){
			const unsignedIntFib uiDefiningFibElementNr =
				pDefiningFibElement->getNumberOfElement();
			
			if ( ( uiDefiningFibElementNr < uiSmaalestFibElementNr ) ||
					( uiBiggestFibElementNr < uiDefiningFibElementNr ) ){
				/*defining Fib element not in Fib object
				 *-> add variable as a input variable*/
				liInputVariables.push_back( *itrUsedVariable );
			}
		}
	}//end for all used variables

#else //FEATURE_NEW_EVALUE_INPUT_VARIABLES
	const list< cFibVariable* > liDefinedVariables =
		pFibObject->getDefinedVariables( bTillRoot ? ED_ALL : ED_BELOW_EQUAL );
	//evalue all used variables not defined in the Fib object
	for ( list< cFibVariable* >::const_iterator
			itrDefinedVariable = liDefinedVariables.begin();
			itrDefinedVariable != liDefinedVariables.end(); itrDefinedVariable++ ){
		
		setUsedVariables.erase( *itrDefinedVariable );
	}//end for all defined variables remove them from used variables
	/*setUsedVariables contains all used variables not defined in the Fib object
	 -> insert them as input variables to the end of the existing input variable list*/
	liInputVariables.insert( liInputVariables.end(),
		setUsedVariables.begin(), setUsedVariables.end() );
#endif //FEATURE_NEW_EVALUE_INPUT_VARIABLES
	
	
	
	return liInputVariables;
}










