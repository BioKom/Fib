/**
 * @class cEvalueFibElementList
 * file name: cEvalueFibElementList.cpp
 * @author Betti Oesterholz
 * @date 18.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains a class for evaluing fib -objects and storing the
 * evalued data into a list.
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
 * This file contains a class for evaluing fib -objects and storing the
 * evalued data into a list.
 * When the fib -object is evalued this method is called every time a
 * fib -element of the choosen type is reached. The parameter for the
 * method are the fib -element, which was reached, and properties of the
 * fib -element.
 */
/*
History:
18.04.2010  Oesterholz  created
*/

#include "version.h"

#include "cEvalueFibElementList.h"

#include "cFibElement.h"

using namespace fib;


/**
 * standrdconstructor
 *
 * @param bInCopyFibElements if true the fib -elements parameter for
 * 	evalueElement() will be copied, else false
 */
cEvalueFibElementList::cEvalueFibElementList( bool bInCopyFibElements ):
		bCopyFibElements( bInCopyFibElements )
#ifdef TEST
		, ulCountOfEvalueMethodCalled( 0 ), lNumberOfTrueEvalueCalls( -1 )
#endif
	{
	//nothing to do
}


/**
 * destructor
 */
cEvalueFibElementList::~cEvalueFibElementList(){
	
	clear();
}

/**
 * The method with wich the evalued fib -elements with ther properties
 * are inserted /evalued. Everytime a fib -element of the choosen type
 * (to evalue) is reached in the evaluation, this method is called with
 * the fib -element and the properties of the fib -element.
 *
 * @param pFibElement the fib -element to evalue
 * @param vProperties a list with the properties of the fib -element
 */
bool cEvalueFibElementList::evalueElement( cFibElement & pFibElement,
		const list<cVectorProperty> & vProperties ){

#ifdef TEST
	ulCountOfEvalueMethodCalled++;
	if ( lNumberOfTrueEvalueCalls != -1 ){
		if ( lNumberOfTrueEvalueCalls == 0 ){
			return false;
		}
		lNumberOfTrueEvalueCalls--;
	}
#endif

	pair< cFibElement*, list< cVectorProperty > > paEvaluedData;
	if ( bCopyFibElements ){
		paEvaluedData.first = pFibElement.copy();
	}else{
		paEvaluedData.first = & pFibElement;
	}
	paEvaluedData.second = vProperties;
	
	//replace variables with ther values in the properties
	for ( list<cVectorProperty>::iterator
				itrProperty = paEvaluedData.second.begin();
			itrProperty != paEvaluedData.second.end(); itrProperty++ ){
		
		const unsignedIntFib uiNumberOfElements = itrProperty->getNumberOfElements();
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= uiNumberOfElements; uiActualElement++ ){
			
			if ( itrProperty->isVariable( uiActualElement ) ){
				itrProperty->setValue( uiActualElement,
					itrProperty->getValue( uiActualElement ) );
			}
		}
	}
	liEvaluedElementData.push_back( paEvaluedData );
	
	return true;
}


/**
 * This method clears the data from the list with the evalued element data
 * liEvaluedElementData. It deletes all fib -objects the list contain, if
 * they are copies.
 * After the function call the liEvaluedElementData list will be empty.
 *
 * @see liEvaluedElementData
 */
void cEvalueFibElementList::clear(){
	
	if ( bCopyFibElements ){
		for ( list< pair< cFibElement*, list< cVectorProperty > > >::iterator
				itrEvaluedData = liEvaluedElementData.begin();
				itrEvaluedData != liEvaluedElementData.end(); itrEvaluedData++ ){
			
			if ( itrEvaluedData->first != NULL ){
				cFibElement::deleteObject( itrEvaluedData->first );
			}
		}
	}//else not copied fib -elements -> clear list

	liEvaluedElementData.clear();
}






