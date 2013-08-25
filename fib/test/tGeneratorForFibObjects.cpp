/**
 * @file tGeneratorForFibObjects
 * file name: tGeneratorForFibObjects.cpp
 * @author Betti Oesterholz
 * @date 20.12.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains functions to generate random Fib objects.
 *
 * Copyright (C) @c GPL3 2009 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
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
 * This file contains functions to generate random Fib objects.
 * The generated Fib objects can be used in tests.
 * If an error occures while generating an fib object it will be returned.
 *
 *
 * Fib -elements used:
 * 	- cRoot
 * 	- cPoint
 * 	- cProperty
 * 	- cList
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 *
 * Underfunctions used:
 * 	- cFunctionValue
 * 	- cFunctionVariable
 * 	- cFunctionAbs
 * 	- cFunctionSin
 * 	- cFunctionLog
 * 	- cFunctionRound
 * 	- cFunctionArcsin
 * 	- cFunctionAdd
 * 	- cFunctionSub
 * 	- cFunctionMult
 * 	- cFunctionDiv
 * 	- cFunctionExp
 * 	- cFunctionMin
 * 	- cFunctionMax
 * 	- cFunctionIf
 *
 * Subconditions used:
 * 	- cConditionTrue
 * 	- cConditionFalse
 * 	- cConditionNot
 * 	- cConditionOr
 * 	- cConditionAnd
 * 	- cConditionXor
 * 	- cConditionEqualInteger
 * 	- cConditionLower
 * 	- cConditionGreater
 *
 */
/*
History:
20.12.2009  Oesterholz  created
24.04.2010  Oesterholz  cFunction and cFunctionValue included
01.08.2010  Oesterholz  cComment included
30.09.2010  Oesterholz  cFEATURE_USE_GENERATE_NEEDED_DOMAINS implemented
31.10.2010  Oesterholz  generateFibObject() with dimension vector for ther sizes
21.05.2011  Oesterholz  cIf and conditions included
20.06.2011  Oesterholz  cFunctionIf included
23.06.2011  Oesterholz  cFunctionRound included
23.06.2011  Oesterholz  some random (sub-)root-elements domains and
	optional parts will be set
25.08.2011  Oesterholz  underarea to subarea
04.09.2010  Oesterholz  FEATURE_GENERATE_NEEDED_DOMAINS implemented
27.09.2010  Oesterholz  cExtObject inserted
14.11.2011  Oesterholz  cExtSubobject inserted
15.01.2012  Oesterholz  cFibSet and cFibMatrix added
23.01.2012  Oesterholz  input values changed to input vector
29.01.2012  Oesterholz  FEATURE_EXT_SUBOBJECT_INPUT_VECTOR implemented:
	the input values are now a vector of values
04.03.2012  Oesterholz  FEATURE_GENERATED_LIST_OBJECT implemented: speed up
01.08.2013  Oesterholz  FEATURE_EXT_SUBOBJECT_INPUT_VECTOR as default (not case removed)
18.08.2013  Oesterholz  generation of dSmalestUnit improved
	( see evalueSmalestUnit() )
*/

//TODO weg
//#define DEBUG


/**
 * This feature uses the cRoot::generateNeededDomains() method to generate
 * the domains for the function- and area elements.
 * Function also using rational values.
 *
 * created: 30.09.2010  Betti Oesterholz
 * @see cRoot::generateNeededDomains()
 */
#define FEATURE_USE_GENERATE_NEEDED_DOMAINS


#include "version.h"

#include "cList.h"
#include "cPoint.h"
#include "cProperty.h"
#include "cArea.h"
#include "cFunction.h"
#include "cIf.h"
#include "cComment.h"
#include "cExtObject.h"
#include "cExtSubobject.h"
#include "cFibSet.h"
#include "cFibMatrix.h"
#include "cRoot.h"


#include "cFunctionValue.h"
#include "cFunctionVariable.h"
#include "cFunctionAbs.h"
#include "cFunctionSin.h"
#include "cFunctionLog.h"
#include "cFunctionArcsin.h"
#include "cFunctionRound.h"
#include "cFunctionAdd.h"
#include "cFunctionSub.h"
#include "cFunctionMult.h"
#include "cFunctionDiv.h"
#include "cFunctionExp.h"
#include "cFunctionMin.h"
#include "cFunctionMax.h"
#include "cFunctionIf.h"


#include "cConditionTrue.h"
#include "cConditionFalse.h"
#include "cConditionNot.h"
#include "cConditionOr.h"
#include "cConditionAnd.h"
#include "cConditionXor.h"
#include "cConditionEqualInteger.h"
#include "cConditionLower.h"
#include "cConditionGreater.h"

#include "cVectorExtSubobject.h"

#include "cDomainNaturalNumber.h"
#include "cDomainVector.h"
#include "cTypeDimension.h"
#include "cTypeProperty.h"
#include "cTypeSubarea.h"
#include "cTypeUnderFunction.h"
#include "cTypeFibMatrix.h"
#include "cTypeFibSet.h"



#include <algorithm>
#include <cmath>
#include <ctime>


using namespace fib;
using namespace std;


cCondition * generateCondition( unsigned int uiSize,
		double dMaxValueElementNumber = 1023.0, double dMinValueElementNumber = -1023.0,
		double dSmalestUnit = 0.1 );
cCondition * replaceConditionValuesWithVariables( cCondition * pCondition,
		list<cFibVariable*> liVariables, double dFractionsOfUsedVariables );

/**
 * A vector with strings, to choose random from.
 */
vector< string > vecRandStrings;

/**
 * This function will fill the vector @see vecRandStrings with strings,
 * to choose random from.
 */
void initVecRandStrings(){
	
	vecRandStrings.push_back("");
	vecRandStrings.push_back("key");
	vecRandStrings.push_back("value");
	vecRandStrings.push_back("name");
	vecRandStrings.push_back("test");
	vecRandStrings.push_back("test1");
	vecRandStrings.push_back("test2");
	vecRandStrings.push_back("test3");
	vecRandStrings.push_back("tes");
	vecRandStrings.push_back("abc");
	vecRandStrings.push_back("oesterholz");
	vecRandStrings.push_back("say's");
	vecRandStrings.push_back("hello");
	vecRandStrings.push_back("new");
	vecRandStrings.push_back("ok");
	vecRandStrings.push_back("dies ist ein laengerer Text zur Erklaerung");
}

/**
 * With this feature the generated Fib object list can be used faster.
 * @see cFibVector::storeXml()
 *
 * Depricated: not FEATURE_GENERATED_LIST_OBJECT
 * created: 04.03.2012  Betti Oesterholz
 * status:  running and tested(04.03.2012)
 */
#define FEATURE_GENERATED_LIST_OBJECT

#ifdef FEATURE_GENERATED_LIST_OBJECT

class cGeneratedList{
protected:
	
	/**
	 * The maximum difference betwean choosen Fib objects of the generated list.
	 * @see liFibObjects
	 */
	#define UL_MAX_NEXT_CHOOSEN 256
	
	/**
	 * The actual choosen Fib object of the list.
	 * Is a pointer to an element in @see liFibObjects
	 * if existing.
	 */
	list< pair< cFibElement*, unsigned long> >::iterator itrActualChoosen;
	
	
public:

	/**
	 * the Fib objects generated
	 *
	 * BEWARE: Better don't change it directly.
	 *
	 * element pair entries:
	 * - first element of the pair is a generated Fib object,
	 * - second element of the pair is the number of points the Fib object will evalue to
	 */
	list< pair< cFibElement*, unsigned long> > liFibObjects;
	
	/**
	 * The number of elements in the list @see liFibObjects
	 * BEWARE: Don't change it.
	 */
	unsigned long ulNumberOfFibObjects;
	
	
	/**
	 * constructor
	 */
	cGeneratedList():ulNumberOfFibObjects( 0 ){
		
		itrActualChoosen = liFibObjects.begin();
	}
	
	
	/**
	* This function choose a random Fib element from the given
	* Fib element list. Every Fib element has the same probability to get
	* choosen.
	* The choosen element will be removed from the list @see liFibObjects
	* ATTENTION: The random number generator should to be initialisized with srand()
	*
	* @return the choosen Fib element from liFibElements or a pair with
	*  ( NULL, 0 ) , if the given liFibElements is empty
	*/
	pair< cFibElement*, unsigned long> choosFibElement(){
		
		if ( liFibObjects.empty() ){
			//no list entry to choose
			return pair< cFibElement*, unsigned long>( NULL, 0 );
		}
		const unsigned int uiMaxNextChoosen =
			( ulNumberOfFibObjects < UL_MAX_NEXT_CHOOSEN ) ?
				ulNumberOfFibObjects : UL_MAX_NEXT_CHOOSEN;
		unsigned int uiRandom = rand() % uiMaxNextChoosen;
		
		const list< pair< cFibElement*, unsigned long> >::const_iterator
			itrEndGeneratedFibObjects = liFibObjects.end();
		
		for ( ;uiRandom != 0; uiRandom-- ){
			if ( itrActualChoosen != itrEndGeneratedFibObjects ){
				//choose next element
				itrActualChoosen++;
			}else{//last element reached -> go back to first element in list
				itrActualChoosen = liFibObjects.begin();
			}
		}
		if ( itrActualChoosen == itrEndGeneratedFibObjects ){
			itrActualChoosen = liFibObjects.begin();
		}
		pair< cFibElement*, unsigned long> paChoosen = (*itrActualChoosen);
		itrActualChoosen = liFibObjects.erase( itrActualChoosen );
		ulNumberOfFibObjects--;
		
		return paChoosen;
	}
	
	
	/**
	 * This method adds the given element to the list of generated Fib objects
	 * @see liFibObjects
	 *
	 * @param paElementToInsert the element to add
	 */
	void addElement( const pair< cFibElement*, unsigned long> & paElementToInsert ){
		
		ulNumberOfFibObjects++;
		liFibObjects.insert( itrActualChoosen, paElementToInsert );
	}
	
	
	/**
	 * This method adds the given element to the list of generated Fib objects
	 * @see liFibObjects
	 * on a random position.
	 *
	 * @param paElementToInsert the element to add
	 */
	void addElementRand( const pair< cFibElement*, unsigned long> & paElementToInsert ){
		
		if ( liFibObjects.empty() ){
			liFibObjects.push_back( paElementToInsert );
			ulNumberOfFibObjects++;
			return;
		}
		const unsigned int uiMaxNextChoosen =
			( ulNumberOfFibObjects < UL_MAX_NEXT_CHOOSEN )?
				ulNumberOfFibObjects : UL_MAX_NEXT_CHOOSEN;
		unsigned int uiRandom = rand() % uiMaxNextChoosen;
		
		const list< pair< cFibElement*, unsigned long> >::const_iterator
			itrEndGeneratedFibObjects = liFibObjects.end();
		
		for ( ;uiRandom != 0; uiRandom-- ){
			if ( itrActualChoosen != itrEndGeneratedFibObjects ){
				//choose next element
				itrActualChoosen++;
			}else{//last element reached -> go back to first element in list
				itrActualChoosen = liFibObjects.begin();
			}
		}
		ulNumberOfFibObjects++;
		liFibObjects.insert( itrActualChoosen, paElementToInsert );
	}
	
};//end class cGeneratedList

#else //FEATURE_GENERATED_LIST_OBJECT

/**
 * This function choose a random Fib element from the given
 * Fib elementlist. Every Fib element has the same probability to get
 * choosen.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * @param liFibElements the Fib elementlist wher to choos from
 * @return the iterator to a random choosen Fib element from liFibElements
 * 	or liFibElements.end(), if the given liFibElements is empty
 */
list< pair< cFibElement*, unsigned long> >::iterator choosFibElement(
		list< pair< cFibElement*, unsigned long> > & liFibElements ){
	
	if ( liFibElements.empty() ){
		return liFibElements.end();
	}
	unsigned int uiRandom = rand() % liFibElements.size();
	list< pair< cFibElement*, unsigned long> >::iterator itrActualFibElement =
		liFibElements.begin();
	for ( ;uiRandom != 0; uiRandom-- ){
		itrActualFibElement++;
	}
	return itrActualFibElement;
}

#endif //FEATURE_GENERATED_LIST_OBJECT


/**
 * This function evalues a value for the smallest unit of a vector element.
 *
 * @param uiMaxVectorElementNumber the maximum number for a vector element
 * @return a value for the smallest unit of a vector element
 */
doubleFib evalueSmalestUnit( unsigned long uiMaxVectorElementNumber ){
	/* 1 / 2^( log( uiMaxVectorElementNumber ) / 2 )
	 -> about half the bits befor the point*/
	return 1.0 / ((doubleFib) (((long long)0x01) <<
		((unsigned int)log( uiMaxVectorElementNumber)) / 2 ));
}


/**
 * This function generates a subfunction with around uiSize
 * contained subfunctions.
 * The propability of each subfunction type, except the 0 ary, will be
 * equal. All leaf subfunctions will be cFunctionValue, no
 * cFunctionVariable will be inserted.
 * Beware: You have to delete the returned subfunction.
 *
 * used subfunctions:
 * 	- cFunctionValue
 * 	- cFunctionAbs
 * 	- cFunctionSin
 * 	- cFunctionLog
 * 	- cFunctionArcsin
 * 	- cFunctionRound
 * 	- cFunctionAdd
 * 	- cFunctionSub
 * 	- cFunctionMult
 * 	- cFunctionDiv
 * 	- cFunctionExp
 * 	- cFunctionMin
 * 	- cFunctionMax
 * 	- cFunctionIf
 *
 * To generate /include variable subfunctions use
 * @see replaceUnderFunctionValuesWithVariables().
 *
 * @param uiSize a roughly number of subfunctions in the generated
 * 	subfunction
 * @param dMaxValueElementNumber the maximal number for a value,
 * 	the number in value subfunctions will vary from
 * 	dMinValueElementNumber till dMaxVectorElementNumber
 * @param dMinValueElementNumber the minimal number for a value,
 * 	the number in value subfunctions will vary from
 * 	dMinValueElementNumber till dMaxVectorElementNumber
 * @param dSmalestUnit the smallest unit for value subfunction
 * @return the generated subfunction or NULL, if no subfunction
 * 	could be generated
 */
cUnderFunction * generateUnderFunction( unsigned int uiSize,
		double dMaxValueElementNumber = 1023.0, double dMinValueElementNumber = -1023.0,
		double dSmalestUnit = 0.1 ){
	
	DEBUG_OUT_L2(<<"generateUnderFunction( uiSize="<<uiSize<<", dMaxValueElementNumber="<<dMaxValueElementNumber<<", dMinValueElementNumber="<<dMinValueElementNumber<<", dSmalestUnit="<<dSmalestUnit<<" ) started"<<endl<<flush);
	
	if ( (dMaxValueElementNumber - dSmalestUnit) <= dMinValueElementNumber ){
		dMinValueElementNumber = dMaxValueElementNumber - dSmalestUnit;
	}
	//the generated subfunction
	cUnderFunction * pUnderFunction = new cFunctionValue( (rand() %
		((long)((dMaxValueElementNumber - dMinValueElementNumber) / dSmalestUnit) )) *
		dSmalestUnit + dMinValueElementNumber );

	unsigned int uiUnderfunctionsGenerated = 1;
	while ( uiUnderfunctionsGenerated < uiSize ){
		//generate subfunctions
		//choose random subfunctiontype to generate
		const unsigned int uiUfType = rand() % 13;
		
		cUnderFunction * pUnderFunction1 = pUnderFunction;
		switch ( uiUfType ){
			case 0:{//cFunctionAbs
				pUnderFunction = new cFunctionAbs( pUnderFunction1 );
			}break;
			case 1:{//cFunctionSin
				pUnderFunction = new cFunctionSin( pUnderFunction1 );
			}break;
			case 2:{//cFunctionLog
				pUnderFunction = new cFunctionLog( pUnderFunction1 );
			}break;
			case 3:{//cFunctionArcsin
				pUnderFunction = new cFunctionArcsin( pUnderFunction1 );
			}break;
			case 4:{//cFunctionRound
				pUnderFunction = new cFunctionRound( pUnderFunction1 );
			}break;
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:{//two array subfunctions
				const unsigned int uiRemainingUfToGenerate =
					uiSize - uiUnderfunctionsGenerated;
				unsigned int uiToGenerateUf2 = std::min(
					rand() % uiRemainingUfToGenerate + 1,
					rand() % (uiUnderfunctionsGenerated * 2) + 1 );
				
				if ( uiSize < (uiUnderfunctionsGenerated + uiToGenerateUf2) ){
					uiToGenerateUf2 = uiSize - uiUnderfunctionsGenerated;
				}
				if ( uiToGenerateUf2 <= 0 ){
					uiToGenerateUf2 = 1;
				}
				cUnderFunction * pUnderFunction2 = generateUnderFunction(
					uiToGenerateUf2, dMaxValueElementNumber,
					dMinValueElementNumber, dSmalestUnit );
				
				if ( pUnderFunction2 == NULL ){
					//Error: no subfunction generated
					continue;
				}
				
				if ( rand() % 2 == 0 ){//switch subfunctions
					cUnderFunction * pUnderFunctionTmp = pUnderFunction2;
					pUnderFunction2 = pUnderFunction1;
					pUnderFunction1 = pUnderFunctionTmp;
					
				}
				switch ( uiUfType ){
					case 5:{//cFunctionAdd
						pUnderFunction = new cFunctionAdd( *pUnderFunction1, *pUnderFunction2 );
					}break;
					case 6:{//cFunctionSub
						pUnderFunction = new cFunctionSub( *pUnderFunction1, *pUnderFunction2 );
					}break;
					case 7:{//cFunctionMult
						pUnderFunction = new cFunctionMult( *pUnderFunction1, *pUnderFunction2 );
					}break;
					case 8:{//cFunctionDiv
						pUnderFunction = new cFunctionDiv( *pUnderFunction1, *pUnderFunction2 );
					}break;
					case 9:{//cFunctionExp
						pUnderFunction = new cFunctionExp( *pUnderFunction1, *pUnderFunction2 );
					}break;
					case 10:{//cFunctionMin
						pUnderFunction = new cFunctionMin( *pUnderFunction1, *pUnderFunction2 );
					}break;
					case 11:{//cFunctionMax
						pUnderFunction = new cFunctionMax( *pUnderFunction1, *pUnderFunction2 );
					}break;
					default://Error: unknown subfunction type
						delete pUnderFunction2;
						continue;
				}
				uiUnderfunctionsGenerated += uiToGenerateUf2;
				delete pUnderFunction2;
			}break;
			case 12:{//generate cFunctionIf
				unsigned int uiRemainingUfToGenerate =
					uiSize - uiUnderfunctionsGenerated;
					
				unsigned int uiToGenerateCondition = std::min(
					rand() % (uiRemainingUfToGenerate / 2 + 1) + 1,
					rand() % (uiUnderfunctionsGenerated * 2) + 1 );
				
				if ( uiSize < (uiUnderfunctionsGenerated + uiToGenerateCondition) ){
					uiToGenerateCondition = uiSize - uiUnderfunctionsGenerated;
				}
				if ( uiToGenerateCondition <= 0 ){
					uiToGenerateCondition = 1;
				}
				cCondition * pCondition = generateCondition(
					uiToGenerateCondition, dMaxValueElementNumber,
					dMinValueElementNumber, dSmalestUnit );
				
				if ( pCondition == NULL ){
					//Error: no condition generated
					continue;
				}
				uiRemainingUfToGenerate -= uiToGenerateCondition;
				if ( uiRemainingUfToGenerate == 0 ){
					uiRemainingUfToGenerate = 1;
				}
				
				unsigned int uiToGenerateUf2 = std::min(
					rand() % uiRemainingUfToGenerate + 1,
					rand() % (uiUnderfunctionsGenerated * 2) + 1 );
				
				if ( uiSize < (uiUnderfunctionsGenerated + uiToGenerateUf2) ){
					uiToGenerateUf2 = uiSize - uiUnderfunctionsGenerated;
				}
				if ( uiToGenerateUf2 <= 0 ){
					uiToGenerateUf2 = 1;
				}
				cUnderFunction * pUnderFunction2 = generateUnderFunction(
					uiToGenerateUf2, dMaxValueElementNumber,
					dMinValueElementNumber, dSmalestUnit );
				
				if ( pUnderFunction2 == NULL ){
					//Error: no subfunction generated
					delete pCondition;
					continue;
				}
				
				if ( rand() % 2 == 0 ){//switch subfunctions
					cUnderFunction * pUnderFunctionTmp = pUnderFunction2;
					pUnderFunction2 = pUnderFunction1;
					pUnderFunction1 = pUnderFunctionTmp;
					
				}
				pUnderFunction = new cFunctionIf( pCondition, pUnderFunction1, pUnderFunction2 );
				uiUnderfunctionsGenerated += uiToGenerateCondition + uiToGenerateUf2;
				pUnderFunction1 = 0;
			}break;
			default:
				continue;
		};
		if ( pUnderFunction1 ){
			delete pUnderFunction1;
		}
		uiUnderfunctionsGenerated++;

	}//while generate subfunctions
	DEBUG_OUT_L2(<<"generateUnderFunction() done"<<endl<<flush);

	return pUnderFunction;
}



/**
 * This function randomly replaces value subfunctions with variable
 * subfunctions in an function.
 * Beware: You have the delete the created subfunction after usage.
 *
 * @see cUnderFunction
 * @see cFunctionValue
 * @see cFunctionVariable
 * @param pUnderFunction a pointer to the subfunction, wher to replace
 * 	the values
 * @param liVariables a list with the variables, which can be used to
 * 	replace the values
 * @param dFractionsOfUsedVariables the fraction of elements of
 * 	vectors, which should be variables
 * @return a pointer to the subfunction wher the values are replaced or
 * 	NULL if non such could be creaded
 */
cUnderFunction * replaceUnderFunctionValuesWithVariables( cUnderFunction * pUnderFunction,
		list<cFibVariable*> liVariables, double dFractionsOfUsedVariables ){
	
	DEBUG_OUT_L2(<<"replaceUnderFunctionValuesWithVariables( pUnderFunction="<<pUnderFunction<<", liVariables, dFractionsOfUsedVariables="<<dFractionsOfUsedVariables<<" ) started"<<endl<<flush);
	if ( pUnderFunction == NULL ){
		DEBUG_OUT_L2(<<"replaceUnderFunctionValuesWithVariables() done pUnderFunction == NULL"<<endl<<flush);
		return NULL;
	}
	if ( liVariables.empty() ){
		DEBUG_OUT_L2(<<"replaceUnderFunctionValuesWithVariables() done liVariables.empty()"<<endl<<flush);
		return NULL;
	}
	if ( dFractionsOfUsedVariables == 0.0 ){
		//replaced enough
		DEBUG_OUT_L2(<<"replaceUnderFunctionValuesWithVariables() done dFractionsOfUsedVariables == 0.0"<<endl<<flush);
		return pUnderFunction->clone();
	}
	if ( pUnderFunction->getType() == cUnderFunction::FUNCTION_VALUE ){
		DEBUG_OUT_L2(<<"random replacing function value with function variable"<<endl<<flush);
		double dRandom = (double)(rand() % RAND_MAX) / (double)(RAND_MAX);
		if ( dRandom < dFractionsOfUsedVariables ){
			DEBUG_OUT_L2(<<"replacing function value with function variable"<<endl<<flush);
			//replace the value
			//choos random defined variables and insert it
			unsigned int uiChoosenVariable = rand() % liVariables.size();
			list<cFibVariable*>::iterator itrChoosenVariable = liVariables.begin();
			while ( uiChoosenVariable != 0){
				itrChoosenVariable++;
				uiChoosenVariable--;
			}
			cFibElement * pDefiningFibElement = pUnderFunction->getDefiningFibElement();
			cUnderFunction * pSuperiorUnderFunction =
				pUnderFunction->getSuperiorUnderFunction();

			return new cFunctionVariable( *itrChoosenVariable,
				pSuperiorUnderFunction, pDefiningFibElement );
		}//else don't replace the value
	}else if ( pUnderFunction->getType() == cUnderFunction::FUNCTION_VARIABLE ){
		DEBUG_OUT_L2(<<"allready function variable"<<endl<<flush);
		//nothing to do
	}else if ( pUnderFunction->getNumberOfUnderFunctions() == 1 ){
		DEBUG_OUT_L2(<<"subfunction with one value"<<endl<<flush);
		
		//replace values with variables in the subfunction
		cUnderFunction * pUnderFunction1 = ((cFunctionOneValue*)
			pUnderFunction)->getUnderFunction();
		pUnderFunction1 = replaceUnderFunctionValuesWithVariables(
			pUnderFunction1, liVariables, dFractionsOfUsedVariables );
		
		if ( pUnderFunction1 == NULL ){
			//error
			return NULL;
		}
		//create to return subfunction
		cFibElement * pDefiningFibElement = pUnderFunction->getDefiningFibElement();
		cUnderFunction * pSuperiorUnderFunction =
			pUnderFunction->getSuperiorUnderFunction();
		
		switch ( pUnderFunction->getType() ){
			case cUnderFunction::FUNCTION_ABS:
				pUnderFunction = new cFunctionAbs( pUnderFunction1,
					pSuperiorUnderFunction, pDefiningFibElement );
			break;
			case cUnderFunction::FUNCTION_SIN:
				pUnderFunction = new cFunctionSin( pUnderFunction1,
					pSuperiorUnderFunction, pDefiningFibElement );
			break;
			case cUnderFunction::FUNCTION_LOG:
				pUnderFunction = new cFunctionLog( pUnderFunction1,
					pSuperiorUnderFunction, pDefiningFibElement );
			break;
			case cUnderFunction::FUNCTION_ARCSIN:
				pUnderFunction = new cFunctionArcsin( pUnderFunction1,
					pSuperiorUnderFunction, pDefiningFibElement );
			break;
			case cUnderFunction::FUNCTION_ROUND:
				pUnderFunction = new cFunctionRound( pUnderFunction1,
					pSuperiorUnderFunction, pDefiningFibElement );
			break;
			default:
				//unknown 1'ary subfunction type
				pUnderFunction = NULL;
		};
		delete pUnderFunction1;
		return pUnderFunction;
	}else if ( pUnderFunction->getNumberOfUnderFunctions() == 2 ){
		DEBUG_OUT_L2(<<"subfunction with two value"<<endl<<flush);
		
		//replace values with variables in the first subfunction
		cUnderFunction * pUnderFunction1 = ((cFunctionTwoValue*)
			pUnderFunction)->getFirstUnderFunction();
		pUnderFunction1 = replaceUnderFunctionValuesWithVariables(
			pUnderFunction1, liVariables, dFractionsOfUsedVariables );
		
		if ( pUnderFunction1 == NULL ){
			//error
			return NULL;
		}
		//replace values with variables in the second subfunction
		cUnderFunction * pUnderFunction2 = ((cFunctionTwoValue*)
			pUnderFunction)->getSecondUnderFunction();
		pUnderFunction2 = replaceUnderFunctionValuesWithVariables(
			pUnderFunction2, liVariables, dFractionsOfUsedVariables );
		
		if ( pUnderFunction2 == NULL ){
			//error
			delete pUnderFunction1;
			return NULL;
		}
		//create to return subfunction
		cFibElement * pDefiningFibElement = pUnderFunction->getDefiningFibElement();
		cUnderFunction * pSuperiorUnderFunction =
			pUnderFunction->getSuperiorUnderFunction();
		
		switch ( pUnderFunction->getType() ){
			case cUnderFunction::FUNCTION_ADD:
				pUnderFunction = new cFunctionAdd( *pUnderFunction1, *pUnderFunction2,
					pSuperiorUnderFunction, pDefiningFibElement );
			break;
			case cUnderFunction::FUNCTION_SUB:
				pUnderFunction = new cFunctionSub( *pUnderFunction1, *pUnderFunction2,
					pSuperiorUnderFunction, pDefiningFibElement );
			break;
			case cUnderFunction::FUNCTION_MULT:
				pUnderFunction = new cFunctionMult( *pUnderFunction1, *pUnderFunction2,
					pSuperiorUnderFunction, pDefiningFibElement );
			break;
			case cUnderFunction::FUNCTION_DIV:
				pUnderFunction = new cFunctionDiv( *pUnderFunction1, *pUnderFunction2,
					pSuperiorUnderFunction, pDefiningFibElement );
			break;
			case cUnderFunction::FUNCTION_EXP:
				pUnderFunction = new cFunctionExp( *pUnderFunction1, *pUnderFunction2,
					pSuperiorUnderFunction, pDefiningFibElement );
			break;
			case cUnderFunction::FUNCTION_MIN:
				pUnderFunction = new cFunctionMin( *pUnderFunction1, *pUnderFunction2,
					pSuperiorUnderFunction, pDefiningFibElement );
			break;
			case cUnderFunction::FUNCTION_MAX:
				pUnderFunction = new cFunctionMax( *pUnderFunction1, *pUnderFunction2,
					pSuperiorUnderFunction, pDefiningFibElement );
			break;
			case cUnderFunction::FUNCTION_IF:{
				
				//replace values with variables in the condition
				cCondition * pCondition = ((cFunctionIf*)
					pUnderFunction)->getCondition();
				pCondition = replaceConditionValuesWithVariables(
					pCondition, liVariables, dFractionsOfUsedVariables );
				
				if ( pCondition == NULL ){
					//error
					delete pUnderFunction1;
					delete pUnderFunction2;
					return NULL;
				}
				
				pUnderFunction = new cFunctionIf( pCondition, pUnderFunction1, pUnderFunction2,
					pSuperiorUnderFunction, pDefiningFibElement );
				
				pUnderFunction1 = NULL;
				pUnderFunction2 = NULL;
			}break;
			default:
				//unknown 1'ary subfunction type
				pUnderFunction = NULL;
		};
		if ( pUnderFunction1 ){
			delete pUnderFunction1;
		}
		if ( pUnderFunction2 ){
			delete pUnderFunction2;
		}
		return pUnderFunction;
	}else{
		//unknown subfunction type
		DEBUG_OUT_L2(<<"unknown subfunction type"<<endl<<flush);
		return NULL;
	}//TODO more subfunction typs
	
	DEBUG_OUT_L2(<<"replaceUnderFunctionValuesWithVariables() done"<<endl<<flush);
	return pUnderFunction->clone();
}



/**
 * This function generates a condition with around uiSize
 * contained conditions plus subconditions.
 * The propability of each conditions and subcondition type, except the
 * 0 ary, will be equal.
 * For cConditionComparison subconditions will be generated with
 * @see generateSubCondition()
 * Beware: You have to delete the returned condition.
 *
 * used subconditions:
 * 	- cConditionTrue
 * 	- cConditionFalse
 * 	- cConditionOr
 * 	- cConditionAnd
 * 	- cConditionXor
 * 	- cConditionEqualInteger
 * 	- cConditionLower
 * 	- cConditionGreater
 *
 * To generate /include variable subconditions use
 * @see replaceConditionValuesWithVariables().
 *
 * @param uiSize a roughly number of conditions plus subconditions in
 * 	the generated subcondition
 * @param dMaxValueElementNumber the maximal number for a value,
 * 	the number in value subconditions will vary from
 * 	dMinValueElementNumber till dMaxVectorElementNumber
 * @param dMinValueElementNumber the minimal number for a value,
 * 	the number in value subconditions will vary from
 * 	dMinValueElementNumber till dMaxVectorElementNumber
 * @param dSmalestUnit the smallest unit for value subcondition
 * @return the generated condition or NULL, if no condition could be generated
 */
cCondition * generateCondition( unsigned int uiSize,
		double dMaxValueElementNumber, double dMinValueElementNumber,
		double dSmalestUnit ){
	
	DEBUG_OUT_L2(<<"generateCondition( uiSize="<<uiSize<<", dMaxValueElementNumber="<<dMaxValueElementNumber<<", dMinValueElementNumber="<<dMinValueElementNumber<<", dSmalestUnit="<<dSmalestUnit<<" ) started"<<endl<<flush);
	
	if( uiSize <= 1 ){
		if ( rand() % 2 ){
			return new cConditionTrue();
		}//else
		return new cConditionFalse();
	}//else generate condition with containing elements
	
	if ( (dMaxValueElementNumber - dSmalestUnit) <= dMinValueElementNumber ){
		dMinValueElementNumber = dMaxValueElementNumber - dSmalestUnit;
	}
	//generate subconditions
	//choose random subconditiontype to generate
	unsigned char uiChoosenCondition = rand() % 7;
	switch ( uiChoosenCondition ){
		case 0:{//cConditionNot
			cCondition * pSubCondition = generateCondition( uiSize - 1,
				dMaxValueElementNumber, dMinValueElementNumber, dSmalestUnit );
			return new cConditionNot( pSubCondition );
		}break;
		//cConditionTwoValue
		case 1:{//cConditionOr
		case 2://cConditionAnd
		case 3://cConditionXor
			//generate subconditions
			const unsigned int uiSubConditions1Size =
				rand() % (uiSize - 1);
			const unsigned int uiSubConditions2Size =
				(uiSize - 1) - uiSubConditions1Size;
			cCondition * pSubCondition1 = generateCondition( uiSubConditions1Size,
				dMaxValueElementNumber, dMinValueElementNumber, dSmalestUnit );
			cCondition * pSubCondition2 = generateCondition( uiSubConditions2Size,
				dMaxValueElementNumber, dMinValueElementNumber, dSmalestUnit );
			
			//create and return condition
			switch ( uiChoosenCondition ){
				case 1://cConditionOr
					return new cConditionOr( pSubCondition1, pSubCondition2 );
				case 2://cConditionAnd
					return new cConditionAnd( pSubCondition1, pSubCondition2 );
				case 3://cConditionXor
					return new cConditionXor( pSubCondition1, pSubCondition2 );
			};
		}break;
		//cConditionComparison
		case 4://cConditionEqualInteger
		case 5://cConditionLower
		case 6:{//cConditionGreater
			const unsigned int uiSubFunction1Size =
				rand() % (uiSize - 1);
			const unsigned int uiSubFunction2Size =
				(uiSize - 1) - uiSubFunction1Size;
			
			cUnderFunction * pUnderFunction1 = generateUnderFunction(
				uiSubFunction1Size, dMaxValueElementNumber,
				dMinValueElementNumber, dSmalestUnit );
			cUnderFunction * pUnderFunction2 = generateUnderFunction(
				uiSubFunction2Size, dMaxValueElementNumber,
				dMinValueElementNumber, dSmalestUnit );

			switch ( uiChoosenCondition ){
				case 4:{//cConditionEqualInteger
					return new cConditionEqualInteger( pUnderFunction1, pUnderFunction2 );
				}break;
				case 5:{//cConditionLower
					return new cConditionLower( pUnderFunction1, pUnderFunction2 );
				}break;
				case 6:{//cConditionGreater
					return new cConditionGreater( pUnderFunction1, pUnderFunction2 );
				}break;
			}
		}break;
	};

	DEBUG_OUT_L2(<<"generateSubCondition() done NULL"<<endl<<flush);

	return NULL;
}



/**
 * This function randomly replaces value subconditions with variable
 * subconditions in an function.
 * Beware: You have the delete the created condition after usage.
 *
 * @see cCondition
 * @see cConditionComparison
 * @see cCondition
 * @see cConditionValue
 * @see cConditionVariable
 * @param pSubCondition a pointer to the condition, wher to replace
 * 	the values
 * @param liVariables a list with the variables, which can be used to
 * 	replace the values
 * @param dFractionsOfUsedVariables the fraction of elements of
 * 	vectors, which should be variables
 * @return a pointer to the condition wher the values are replaced or
 * 	NULL, if non such could be creaded
 */
cCondition * replaceConditionValuesWithVariables( cCondition * pCondition,
		list<cFibVariable*> liVariables, double dFractionsOfUsedVariables ){
	
	DEBUG_OUT_L2(<<"replaceConditionValuesWithVariables( pCondition="<<pCondition<<", liVariables, dFractionsOfUsedVariables="<<dFractionsOfUsedVariables<<" ) started"<<endl<<flush);
	if ( pCondition == NULL ){
		DEBUG_OUT_L2(<<"replaceConditionValuesWithVariables() done pCondition == NULL"<<endl<<flush);
		return NULL;
	}
	if ( liVariables.empty() ){
		DEBUG_OUT_L2(<<"replaceUnderConditionValuesWithVariables() done liVariables.empty()"<<endl<<flush);
		return NULL;
	}
	if ( dFractionsOfUsedVariables == 0.0 ){
		//replaced enough
		DEBUG_OUT_L2(<<"replaceUnderConditionValuesWithVariables() done dFractionsOfUsedVariables == 0.0"<<endl<<flush);
		return pCondition->clone();
	}
	
	//create to return subcondition
	cFibElement * pDefiningFibElement = pCondition->getDefiningFibElement();
	cCondition * pSuperiorCondition =
		pCondition->getSuperiorCondition();
	
	switch ( pCondition->getType() ){
		case cCondition::CONDITION_FALSE:
			return new cConditionFalse( pSuperiorCondition, pDefiningFibElement );
		break;
		case cCondition::CONDITION_TRUE:
			return new cConditionTrue( pSuperiorCondition, pDefiningFibElement );
		break;
		case cCondition::CONDITION_NOT:{
			cCondition * pSubCondition = replaceConditionValuesWithVariables(
				((cConditionNot*)(pCondition))->getSubCondition(),
				liVariables, dFractionsOfUsedVariables );
			
			return new cConditionNot( pSubCondition,
				pSuperiorCondition, pDefiningFibElement );
		}break;
	//cConditionTwoValue
		case cCondition::CONDITION_OR:{
			cCondition * pSubCondition1 = replaceConditionValuesWithVariables(
				((cConditionTwoValue*)(pCondition))->getFirstSubCondition(),
				liVariables, dFractionsOfUsedVariables );
			cCondition * pSubCondition2 = replaceConditionValuesWithVariables(
				((cConditionTwoValue*)(pCondition))->getSecondSubCondition(),
				liVariables, dFractionsOfUsedVariables );
			
			return new cConditionOr( pSubCondition1, pSubCondition2,
				pSuperiorCondition, pDefiningFibElement );
		}break;
		case cCondition::CONDITION_AND:{
			cCondition * pSubCondition1 = replaceConditionValuesWithVariables(
				((cConditionTwoValue*)(pCondition))->getFirstSubCondition(),
				liVariables, dFractionsOfUsedVariables );
			cCondition * pSubCondition2 = replaceConditionValuesWithVariables(
				((cConditionTwoValue*)(pCondition))->getSecondSubCondition(),
				liVariables, dFractionsOfUsedVariables );
			
			return new cConditionAnd( pSubCondition1, pSubCondition2,
				pSuperiorCondition, pDefiningFibElement );
		}break;
		case cCondition::CONDITION_XOR:{
			cCondition * pSubCondition1 = replaceConditionValuesWithVariables(
				((cConditionTwoValue*)(pCondition))->getFirstSubCondition(),
				liVariables, dFractionsOfUsedVariables );
			cCondition * pSubCondition2 = replaceConditionValuesWithVariables(
				((cConditionTwoValue*)(pCondition))->getSecondSubCondition(),
				liVariables, dFractionsOfUsedVariables );
			
			return new cConditionXor( pSubCondition1, pSubCondition2,
				pSuperiorCondition, pDefiningFibElement );
		}break;
	//cConditionComparison
		case cCondition::CONDITION_EQUAL_INTEGER:{
			cUnderFunction * pSubFunction1 = replaceUnderFunctionValuesWithVariables(
				((cConditionComparison*)(pCondition))->getFirstSubFunction(),
				liVariables, dFractionsOfUsedVariables );
			cUnderFunction * pSubFunction2 = replaceUnderFunctionValuesWithVariables(
				((cConditionComparison*)(pCondition))->getSecondSubFunction(),
				liVariables, dFractionsOfUsedVariables );
			
			return new cConditionEqualInteger( pSubFunction1, pSubFunction2,
				pSuperiorCondition, pDefiningFibElement );
		}break;
		case cCondition::CONDITION_LOWER:{
			cUnderFunction * pSubFunction1 = replaceUnderFunctionValuesWithVariables(
				((cConditionComparison*)(pCondition))->getFirstSubFunction(),
				liVariables, dFractionsOfUsedVariables );
			cUnderFunction * pSubFunction2 = replaceUnderFunctionValuesWithVariables(
				((cConditionComparison*)(pCondition))->getSecondSubFunction(),
				liVariables, dFractionsOfUsedVariables );
			
			return new cConditionLower( pSubFunction1, pSubFunction2,
				pSuperiorCondition, pDefiningFibElement );
		}break;
		case cCondition::CONDITION_GREATER:{
			cUnderFunction * pSubFunction1 = replaceUnderFunctionValuesWithVariables(
				((cConditionComparison*)(pCondition))->getFirstSubFunction(),
				liVariables, dFractionsOfUsedVariables );
			cUnderFunction * pSubFunction2 = replaceUnderFunctionValuesWithVariables(
				((cConditionComparison*)(pCondition))->getSecondSubFunction(),
				liVariables, dFractionsOfUsedVariables );
			
			return new cConditionGreater( pSubFunction1, pSubFunction2,
				pSuperiorCondition, pDefiningFibElement );
		}break;
	};//TODO more condition typs
	
	DEBUG_OUT_L2(<<"unknown subcondition type"<<endl<<flush);
	return NULL;
}




/**
 * This function generates Fib objects with around uiSize
 * Fib elements (all together).
 * Beware: You have to delete the returned Fib objects.
 *
 * @param uiSize a roughly number of Fib elements in the generated Fib objects
 * @param ulMaximalEvaluedPoints a roughly number of points the Fib object
 * 	should evalue to; (this test didn't includes /checks variables, so it
 * 	basicly just works for dFractionsOfUsedVariables = 0.0)
 * @param liFractionOfFibElements the fractions of different
 * 	Fib elementtyps in the generated Fib Object;
 * 	first element of the pair is the char for the type of the
 * 	Fib element (@see getType()), second element is the number for the
 * 	fraction of the Fib element;
 * 	the fractions will be normalized, so that they sum to 1
 * @param liPossiblePropertyTyps the list with the possible propertytyps in the
 * 	generated Fib object
 * @param vecDimensions the vector with the size of the different dimensions
 * @param uiMaxVectorElementNumber the maximal number for a vectorelement,
 * 	the number in vectorelements will vary from 0 till
 * 	uiMaxVectorElementNumber
 * @return a list with the generated Fib objects
 */
list< pair< cFibElement*, unsigned long> > generateFibObjects(
		unsigned long uiFibObjectsToGenerate,
		unsigned long uiSize,
		unsigned long ulMaximalEvaluedPoints,
		list< pair< char, double > > liFractionOfFibElements,
		const list< cTypeProperty > & liPossiblePropertyTyps,
		const vector<unsigned long> & vecDimensions,
		unsigned long uiMaxVectorElementNumber = 1023 ){
	
	//evale values
	if ( uiSize == 0 ){
		//minimum size is 1
		DEBUG_OUT_L2(<<"generateFibObject() done uiSize = 0"<<endl<<flush);
		return list< pair< cFibElement*, unsigned long> >();
	}
	const unsigned int uiNumberOfDimensions = vecDimensions.size();
	if ( uiNumberOfDimensions == 0 ){
		//minimum size is 1
		DEBUG_OUT_L2(<<"generateFibObject() done uiNumberOfDimensions = 0"<<endl<<flush);
		return list< pair< cFibElement*, unsigned long> >();
	}
	if ( uiMaxVectorElementNumber == 0 ){
		//minimum size is 1
		DEBUG_OUT_L2(<<"generateFibObject() done uiMaxVectorElementNumber = 0"<<endl<<flush);
		return list< pair< cFibElement*, unsigned long> >();
	}
	
	static bool bRandomGeneratorStarted = false;
	if ( ! bRandomGeneratorStarted ){
		srand( time(NULL) );
		bRandomGeneratorStarted = true;
		initVecRandStrings();
	}
	
	double dFractionSum = 0.0;
	double dPointFraction = 0.0;
	double dExtObjectsFraction = 0.0;
	double dExtSubobjectsFraction = 0.0;
	double dListFraction = 0.0;
	for ( list< pair< char, double > >::iterator
			itrElementFractions = liFractionOfFibElements.begin();
			itrElementFractions != liFractionOfFibElements.end(); ){
		
		dFractionSum += itrElementFractions->second;
		if ( itrElementFractions->first == 'p' ){
			//fractions for the point elements will be handeld seperatly
			dPointFraction = itrElementFractions->second;
			itrElementFractions = liFractionOfFibElements.erase( itrElementFractions );
			continue;
		}else if ( itrElementFractions->first == 'o' ){
			//fractions for the external object elements will be handeld seperatly
			dExtObjectsFraction = itrElementFractions->second;
			itrElementFractions = liFractionOfFibElements.erase( itrElementFractions );
			continue;
		}else if ( itrElementFractions->first == 's' ){
			//fractions for the external subobject elements will be handeld seperatly
			dExtSubobjectsFraction = itrElementFractions->second;
			itrElementFractions = liFractionOfFibElements.erase( itrElementFractions );
			continue;
		}else if ( itrElementFractions->first == 'l' ){
			//fractions for the pointelements will be handeld seperatly
			dListFraction = itrElementFractions->second;
		}
		itrElementFractions++;
	}
	for ( list< pair< char, double > >::iterator itrElementFractions =
			liFractionOfFibElements.begin();
			itrElementFractions != liFractionOfFibElements.end();
			itrElementFractions++ ){
		
		itrElementFractions->second /= dFractionSum;
		DEBUG_OUT_L2(<<"fraction "<<itrElementFractions->first<<" = "<<itrElementFractions->second<<endl<<flush);
	}
	//evalue the values for the points
	if ( dPointFraction == 0.0 ){
		//no point fraction given -> set it to the average fraction
		dPointFraction = 1.0 / liFractionOfFibElements.size();
	}else{
		dPointFraction /= dFractionSum;
	}
	if ( 1.0 <= dPointFraction ){
		//no point fraction to great
		dPointFraction = 1.0 - (2.0 / (double)(uiSize) );
	}
	unsigned long uiPointsToGenerat = (unsigned int)(((double)uiSize) * dPointFraction);
	if ( uiPointsToGenerat < uiFibObjectsToGenerate ){
		uiPointsToGenerat = uiFibObjectsToGenerate;
	}
	const unsigned long uiExtObjectsToGenerat    = (unsigned int)(((double)uiSize) * dExtObjectsFraction);
	const unsigned long uiExtSubobjectsToGenerat = (unsigned int)(((double)uiSize) * dExtSubobjectsFraction);
	
	//get the average underobjects per listelement
	unsigned long uiListElementsToGenerate = uiSize * dListFraction;
	if ( uiListElementsToGenerate == 0 ){
		//no list fraction given -> set it to two lists
		uiListElementsToGenerate = 2;
	}
	/*every pointelement is an simple underobject
	-> the listelements needing enougth underobjects so that all
	listelements can contain all pointelements*/
	//the pointelements will be distributet identicaly over the uiFibObjectsToGenerate
	//the listelements will be distributet identicaly over the uiFibObjectsToGenerate
	unsigned long uiListElementsToGeneratePerRoot = uiListElementsToGenerate / uiFibObjectsToGenerate;
	if ( uiListElementsToGeneratePerRoot < 1 ){
		uiListElementsToGeneratePerRoot = 1;
	}
	//distribute the leaf elements per root-element betwean the listelements
	unsigned long uiAvarageUnderobjectsPerListelement = (uiPointsToGenerat +
		uiExtObjectsToGenerat + uiExtSubobjectsToGenerat) / uiFibObjectsToGenerate;
	if ( uiAvarageUnderobjectsPerListelement < 1 ){
		//one underobject per rootelement is minimum
		uiAvarageUnderobjectsPerListelement = 1;
	}
	uiAvarageUnderobjectsPerListelement--;
	uiAvarageUnderobjectsPerListelement /= uiListElementsToGeneratePerRoot;
	uiAvarageUnderobjectsPerListelement++;
	if ( uiAvarageUnderobjectsPerListelement < 2 ){
		//minimum is two underobjects in an listelement
		uiAvarageUnderobjectsPerListelement = 2;
	}

	//*generate Fib objects (for the main-objects in the root-elements)

	//generate the Fib objects
#ifdef FEATURE_GENERATED_LIST_OBJECT
	cGeneratedList liGeneratedFibObjects;
#else //FEATURE_GENERATED_LIST_OBJECT
	/*liGeneratedFibObjects: the Fib objects generated;
	- first element of the pair is a generated Fib object,
	- second element of the pair is the number of points the Fib object will evalue to*/
	list< pair< cFibElement*, unsigned long> > liGeneratedFibObjects;
#endif //FEATURE_GENERATED_LIST_OBJECT
	cVectorPosition vecPosition( uiNumberOfDimensions );
	uiMaxVectorElementNumber++;//change for (rand % uiMaxVectorElementNumber)
	for ( unsigned int uiActualPoint = 1; uiActualPoint <= uiPointsToGenerat;
			uiActualPoint++ ){
		//generate random Position
		for ( unsigned int uiActualDimensions = 1;
				uiActualDimensions <= uiNumberOfDimensions; uiActualDimensions++ ){
			
			vecPosition.setValue( uiActualDimensions,
				rand() % vecDimensions[ uiActualDimensions - 1 ] + 1 );
		}
#ifdef FEATURE_GENERATED_LIST_OBJECT
		liGeneratedFibObjects.addElement( make_pair( new cPoint( &vecPosition ), 1 ) );
#else //FEATURE_GENERATED_LIST_OBJECT
		liGeneratedFibObjects.push_back( make_pair( new cPoint( &vecPosition ), 1 ) );
#endif //FEATURE_GENERATED_LIST_OBJECT
	}
	uiMaxVectorElementNumber--;//change back because of (rand % uiMaxVectorElementNumber)
	if ( uiPointsToGenerat <= ulMaximalEvaluedPoints ){
		ulMaximalEvaluedPoints -= uiPointsToGenerat;
	}else{
		ulMaximalEvaluedPoints = 0;
	}
	//create cExtObject
	DEBUG_OUT_L2(<<"generating "<<uiExtObjectsToGenerat<<" external objects"<<endl<<flush);
	for ( unsigned int uiActualExtObject = 1; uiActualExtObject <= uiExtObjectsToGenerat;
			uiActualExtObject++ ){
		//insert empty cExtObject on random position
#ifdef FEATURE_GENERATED_LIST_OBJECT
		liGeneratedFibObjects.addElementRand( make_pair( new cExtObject( 0 ), 1 ) );
#else //FEATURE_GENERATED_LIST_OBJECT
		liGeneratedFibObjects.insert( choosFibElement( liGeneratedFibObjects ),
			make_pair( new cExtObject( 0 ), 1 ) );
#endif //FEATURE_GENERATED_LIST_OBJECT
	}
	//create cExtSubobject
	DEBUG_OUT_L2(<<"generating "<<uiExtSubobjectsToGenerat<<" external subobjects"<<endl<<flush);
	for ( unsigned int uiActualExtSubobject = 1; uiActualExtSubobject <= uiExtSubobjectsToGenerat;
			uiActualExtSubobject++ ){
		//insert empty cExtSubobject on random position
#ifdef FEATURE_GENERATED_LIST_OBJECT
		liGeneratedFibObjects.addElementRand( make_pair( new cExtSubobject( 0 ), 1 ) );
#else //FEATURE_GENERATED_LIST_OBJECT
		liGeneratedFibObjects.insert( choosFibElement( liGeneratedFibObjects ),
			make_pair( new cExtSubobject( 0 ), 1 ) );
#endif //FEATURE_GENERATED_LIST_OBJECT
	}
	
	DEBUG_OUT_L2(<<"uiAvarageUnderobjectsPerListelement: "<<uiAvarageUnderobjectsPerListelement<<endl<<flush);
	DEBUG_OUT_L2(<<"ulMaximalEvaluedPoints: "<<ulMaximalEvaluedPoints<<endl<<flush);
#ifdef FEATURE_GENERATED_LIST_OBJECT
	DEBUG_OUT_L2(<<"uiFibObjectsToGenerate: "<<uiFibObjectsToGenerate<<" now ther are "<<liGeneratedFibObjects.ulNumberOfFibObjects<<" Fib objects"<<endl<<flush);
#else //FEATURE_GENERATED_LIST_OBJECT
	DEBUG_OUT_L2(<<"uiFibObjectsToGenerate: "<<uiFibObjectsToGenerate<<" now ther are "<<liGeneratedFibObjects.size()<<" Fib objects"<<endl<<flush);
#endif //FEATURE_GENERATED_LIST_OBJECT

	//generate Fib elements
	//wheel selection
	list< pair< char, double > >::iterator itrSelectedElementtype =
		liFractionOfFibElements.begin();
	
	
	//max iterations to ensure no infinit loops happen
	unsigned long uiMaxIterations = uiSize * 2 +
		uiListElementsToGenerate * uiAvarageUnderobjectsPerListelement;
#ifdef FEATURE_GENERATED_LIST_OBJECT
	unsigned long uiGeneratedFibElements = liGeneratedFibObjects.ulNumberOfFibObjects;
#else //FEATURE_GENERATED_LIST_OBJECT
	unsigned long uiGeneratedFibElements = liGeneratedFibObjects.size();
#endif //FEATURE_GENERATED_LIST_OBJECT
	for ( unsigned long uiIterations = 0; uiIterations < uiMaxIterations;
			uiIterations++ ){
		
		
		//decide which fib element to generate
		double dRandom = (double)(rand() % RAND_MAX) / (double)(RAND_MAX);
		while ( itrSelectedElementtype->second < dRandom ){
			dRandom -= itrSelectedElementtype->second;
			itrSelectedElementtype++;
			if ( itrSelectedElementtype == liFractionOfFibElements.end() ){
				itrSelectedElementtype = liFractionOfFibElements.begin();
			}
		}
		char cSelectedType = itrSelectedElementtype->first;
		
		if ( cSelectedType == 'l' ){
			//generate a list element
#ifdef FEATURE_GENERATED_LIST_OBJECT
			if ( liGeneratedFibObjects.ulNumberOfFibObjects <= uiFibObjectsToGenerate ){
#else //FEATURE_GENERATED_LIST_OBJECT
			if ( liGeneratedFibObjects.size() <= uiFibObjectsToGenerate ){
#endif //FEATURE_GENERATED_LIST_OBJECT
				/*don't reduce number of Fib objects (don't concatenate
				Fib objects with list elements)*/
				continue;
			}//else generate new Fib element
		}else{//generate no list element
			if ( uiSize <= uiGeneratedFibElements ){
				//to much fib elements generated -> generate just list elements
				cSelectedType = 'l';
			}
		}
		//generate Fib element
		uiGeneratedFibElements++;
		
		switch ( cSelectedType ){
			case 'y':{//generate property element cProperty
				DEBUG_OUT_L2(<<"generating property "<<endl<<flush);
#ifdef FEATURE_GENERATED_LIST_OBJECT
				pair< cFibElement*, unsigned long>
					paUnderobject = liGeneratedFibObjects.choosFibElement();
#else //FEATURE_GENERATED_LIST_OBJECT
				list< pair< cFibElement*, unsigned long> >::iterator
					itrUnderobject = choosFibElement( liGeneratedFibObjects );
#endif //FEATURE_GENERATED_LIST_OBJECT
				//generate Propertyvector
				unsigned int uiRandom = rand() % liPossiblePropertyTyps.size();
				list< cTypeProperty >::const_iterator itrChoosenPropertyType = liPossiblePropertyTyps.begin();
				while ( uiRandom != 0 ){
					uiRandom--;
					itrChoosenPropertyType++;
				}
				cVectorProperty vecProperty( *itrChoosenPropertyType );
				for ( unsigned int uiActualElement = 1;
						uiActualElement <= vecProperty.getNumberOfElements(); uiActualElement++ ){
					
					vecProperty.setValue( uiActualElement, rand() % uiMaxVectorElementNumber );
				}
#ifdef FEATURE_GENERATED_LIST_OBJECT
				cProperty * pProperty = new cProperty( vecProperty, paUnderobject.first );
				const unsigned long ulEvaluedPoints = paUnderobject.second;
				liGeneratedFibObjects.addElement( make_pair( pProperty, ulEvaluedPoints) );
#else //FEATURE_GENERATED_LIST_OBJECT
				
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
				cProperty * pProperty = new cProperty( vecProperty, itrUnderobject->first );
#else //FEATURE_SIMPLE_CONSTRUCTOR
				cProperty * pProperty = new cProperty( vecProperty, NULL, NULL, itrUnderobject->first );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
				const unsigned long ulEvaluedPoints = itrUnderobject->second;
				liGeneratedFibObjects.erase( itrUnderobject );
				liGeneratedFibObjects.push_back( make_pair( pProperty, ulEvaluedPoints) );
#endif //FEATURE_GENERATED_LIST_OBJECT
				//erase old/used and insert new Fib object
			}break;
			case 'a':{//generate area element cArea
				DEBUG_OUT_L2(<<"generating area "<<endl<<flush);
#ifdef FEATURE_GENERATED_LIST_OBJECT
				pair< cFibElement*, unsigned long>
					paUnderobject = liGeneratedFibObjects.choosFibElement();
				unsigned long ulEvaluedPoints = paUnderobject.second;
#else //FEATURE_GENERATED_LIST_OBJECT
				list< pair< cFibElement*, unsigned long> >::iterator
					itrUnderobject = choosFibElement( liGeneratedFibObjects );
				unsigned long ulEvaluedPoints = itrUnderobject->second;
#endif //FEATURE_GENERATED_LIST_OBJECT
				//generate vectors for subareas
				unsigned int uiCountOfSubAreas = 1;
				if ( (rand() % 8) == 0 ){
					if ( (rand() % 256) == 0 ){
						uiCountOfSubAreas = (rand() % 1024 + 1);
					}else{
						uiCountOfSubAreas = (rand() % 16 + 1);
					}
				}else{
					uiCountOfSubAreas = (rand() % 2 + 1);
				}
				//the number of values in the subareas of the are
				unsigned long ulCountValues = 0;
				
				list<cVectorArea> liSubAreas;
				for ( unsigned int uiActualSubArea = 1;
						uiActualSubArea <= uiCountOfSubAreas; uiActualSubArea++ ){
					
					cVectorArea vecArea;
					const longFib lLowerBounderie =
						rand() % uiMaxVectorElementNumber -
						rand() % uiMaxVectorElementNumber;
					longFib lUpperBounderie = 0;
					if ( rand() % 32 != 0 ){
						//confined bouderie area
						lUpperBounderie = lLowerBounderie + (rand() % 32) - 16;
					}else{
						lUpperBounderie = lLowerBounderie +
							(rand() % (uiMaxVectorElementNumber / 32 + 32)) -
							(uiMaxVectorElementNumber / 64 + 16);
					}
					if ( uiMaxVectorElementNumber < ((unsigned long)lUpperBounderie) ){
						lUpperBounderie = uiMaxVectorElementNumber;
					}else if ( lUpperBounderie < (((long)uiMaxVectorElementNumber) * -1L) ){
						lUpperBounderie = ((long)uiMaxVectorElementNumber) * -1L;
					}
					//check the points evalued for the areaobject
					ulCountValues += abs( lLowerBounderie - lUpperBounderie ) + 1;
					if ( ulMaximalEvaluedPoints < (ulCountValues * ulEvaluedPoints) ){
						
						while ( (lLowerBounderie != lUpperBounderie) &&
								(ulMaximalEvaluedPoints < (ulCountValues - 1) * ulEvaluedPoints) ){
							
							if ( lLowerBounderie < lUpperBounderie ){
								lUpperBounderie--;
							}else{
								lUpperBounderie++;
							}
						}
						//this is the last added subarea
						uiCountOfSubAreas = uiActualSubArea;
					}
					//add the subarea for the area
					vecArea.setValue( 1, lLowerBounderie );
					vecArea.setValue( 2, lUpperBounderie );
					
					liSubAreas.push_back( vecArea );
				}
				if ( ulEvaluedPoints * (ulCountValues - 1) < ulMaximalEvaluedPoints ){
					ulMaximalEvaluedPoints -= ulEvaluedPoints * (ulCountValues - 1);
				}else{
					ulMaximalEvaluedPoints = 0;
				}
				ulEvaluedPoints *= ulCountValues;
				
#ifdef FEATURE_GENERATED_LIST_OBJECT
				cArea * pArea = new cArea( liSubAreas.front(), paUnderobject.first );
				//insert remaining subareas
				list<cVectorArea>::iterator itrSubArea = liSubAreas.begin();
				itrSubArea++;
				for ( ;itrSubArea != liSubAreas.end(); itrSubArea++ ){
					pArea->addSubarea( *itrSubArea );
				}
				//erase old/used and insert new Fib object
				liGeneratedFibObjects.addElement( make_pair( pArea, ulEvaluedPoints ) );
				
#else //FEATURE_GENERATED_LIST_OBJECT
				
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
				cArea * pArea = new cArea( liSubAreas.front(), itrUnderobject->first );
#else //FEATURE_SIMPLE_CONSTRUCTOR
				cArea * pArea = new cArea( liSubAreas.front(), NULL, NULL, itrUnderobject->first );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
				//insert remaining subareas
				list<cVectorArea>::iterator itrSubArea = liSubAreas.begin();
				itrSubArea++;
				for ( ;itrSubArea != liSubAreas.end(); itrSubArea++ ){
					pArea->addSubarea( *itrSubArea );
				}
				//erase old/used and insert new Fib object
				liGeneratedFibObjects.erase( itrUnderobject );
				liGeneratedFibObjects.push_back( make_pair( pArea, ulEvaluedPoints ) );
#endif //FEATURE_GENERATED_LIST_OBJECT
			}break;
			case 'f':{//generate function element cFunction
				DEBUG_OUT_L2(<<"generating function "<<endl<<flush);
#ifdef FEATURE_GENERATED_LIST_OBJECT
				pair< cFibElement*, unsigned long >
					paUnderobject = liGeneratedFibObjects.choosFibElement();
				unsigned long ulEvaluedPoints = paUnderobject.second;
#else //FEATURE_GENERATED_LIST_OBJECT
				list< pair< cFibElement*, unsigned long> >::iterator
					itrUnderobject = choosFibElement( liGeneratedFibObjects );
				unsigned long ulEvaluedPoints = itrUnderobject->second;
#endif //FEATURE_GENERATED_LIST_OBJECT
				//generate the subfunction for the function
#ifdef FEATURE_USE_GENERATE_NEEDED_DOMAINS
				//use rational numbers
				cUnderFunction * pUnderFunction = generateUnderFunction(
					log( uiSize ) + 1, uiMaxVectorElementNumber,
					((double)uiMaxVectorElementNumber) * -1,
					(1.0 / log( uiMaxVectorElementNumber) ) );
#else //FEATURE_USE_GENERATE_NEEDED_DOMAINS
				cUnderFunction * pUnderFunction = generateUnderFunction(
					log( uiSize ) + 1, uiMaxVectorElementNumber, 0.0 , 1.0 );
#endif //FEATURE_USE_GENERATE_NEEDED_DOMAINS
				if ( pUnderFunction == NULL ){
					//no subfunction could be creted
					continue;
				}
#ifdef FEATURE_GENERATED_LIST_OBJECT
				cFunction * pFunction = new cFunction( * pUnderFunction, paUnderobject.first );
				delete pUnderFunction;
				//erase old/used and insert new Fib object
				liGeneratedFibObjects.addElement( make_pair( pFunction, ulEvaluedPoints ) );
				
#else //FEATURE_GENERATED_LIST_OBJECT
				
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
				cFunction * pFunction = new cFunction( * pUnderFunction, itrUnderobject->first );
#else //FEATURE_SIMPLE_CONSTRUCTOR
				cFunction * pFunction = new cFunction( * pUnderFunction, NULL, NULL, itrUnderobject->first );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
				delete pUnderFunction;
				//erase old/used and insert new Fib object
				liGeneratedFibObjects.erase( itrUnderobject );
				liGeneratedFibObjects.push_back( make_pair( pFunction, ulEvaluedPoints ) );
#endif //FEATURE_GENERATED_LIST_OBJECT
			}break;
			case 'i':{//generate if-element cIf
#ifdef FEATURE_GENERATED_LIST_OBJECT
				if ( liGeneratedFibObjects.ulNumberOfFibObjects < 2 ){
					//not enough underobjects for if-element -> skip creating if-element
					continue;
				}
				DEBUG_OUT_L2(<<"generating if-element "<<endl<<flush);
				pair< cFibElement*, unsigned long>
					paUnderobject1 = liGeneratedFibObjects.choosFibElement();
				cFibElement * pFirstSubObject = paUnderobject1.first;
				unsigned long ulEvaluedPoints = paUnderobject1.second;
				
				pair< cFibElement*, unsigned long>
					paUnderobject2 = liGeneratedFibObjects.choosFibElement();
				cFibElement * pSecondSubObject = paUnderobject2.first;
				ulEvaluedPoints += paUnderobject2.second;
#else //FEATURE_GENERATED_LIST_OBJECT
				if ( liGeneratedFibObjects.size() < 2 ){
					//not enough underobjects for if-element -> skip creating if-element
					continue;
				}
				DEBUG_OUT_L2(<<"generating if-element "<<endl<<flush);
				list< pair< cFibElement*, unsigned long> >::iterator
					itrUnderobject1 = choosFibElement( liGeneratedFibObjects );
				cFibElement * pFirstSubObject = itrUnderobject1->first;
				unsigned long ulEvaluedPoints = itrUnderobject1->second;
				liGeneratedFibObjects.erase( itrUnderobject1 );
				
				list< pair< cFibElement*, unsigned long> >::iterator
					itrUnderobject2 = choosFibElement( liGeneratedFibObjects );
				cFibElement * pSecondSubObject = itrUnderobject2->first;
				ulEvaluedPoints += itrUnderobject2->second;
				liGeneratedFibObjects.erase( itrUnderobject2 );
#endif //FEATURE_GENERATED_LIST_OBJECT
				
				//generate the subfunction for the function
#ifdef FEATURE_USE_GENERATE_NEEDED_DOMAINS
				//use rational numbers
				cCondition * pCondition = generateCondition(
					log( uiSize ) + 1, uiMaxVectorElementNumber,
					((double)uiMaxVectorElementNumber) * -1,
					(1.0 / log( uiMaxVectorElementNumber) ) );
#else //FEATURE_USE_GENERATE_NEEDED_DOMAINS
				cCondition * pCondition = generateCondition(
					log( uiSize ) + 1, uiMaxVectorElementNumber, 0.0 , 1.0 );
#endif //FEATURE_USE_GENERATE_NEEDED_DOMAINS
				if ( pCondition == NULL ){
					//no subfunction could be creted
					DEBUG_OUT_EL2(<<"Error: Could not create an condition. "<<endl<<flush);
					continue;
				}
				cIf * pIf = new cIf( * pCondition, pFirstSubObject, pSecondSubObject );
				delete pCondition;
				//erase old/used and insert new Fib object
#ifdef FEATURE_GENERATED_LIST_OBJECT
				liGeneratedFibObjects.addElement( make_pair( pIf, ulEvaluedPoints ) );
#else //FEATURE_GENERATED_LIST_OBJECT
				liGeneratedFibObjects.push_back( make_pair( pIf, ulEvaluedPoints ) );
#endif //FEATURE_GENERATED_LIST_OBJECT
			}break;
			case 'c':{//generatea comment element cComment
				DEBUG_OUT_L2(<<"generating comment "<<endl<<flush);
				//choose the key and value for the comment
				const size_t iKey = rand() % vecRandStrings.size();
				const size_t iValue = rand() % vecRandStrings.size();
				
#ifdef FEATURE_GENERATED_LIST_OBJECT
				pair< cFibElement*, unsigned long>
					paUnderobject = liGeneratedFibObjects.choosFibElement();
				cComment * pComment = new cComment(
					vecRandStrings[ iKey ], vecRandStrings[ iValue ],
					paUnderobject.first );
				//erase old/used and insert new Fib object
				liGeneratedFibObjects.addElement( make_pair( pComment, paUnderobject.second ) );
#else //FEATURE_GENERATED_LIST_OBJECT
				list< pair< cFibElement*, unsigned long> >::iterator
					itrUnderobject = choosFibElement( liGeneratedFibObjects );
				unsigned long ulEvaluedPoints = itrUnderobject->second;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
				cComment * pComment = new cComment(
					vecRandStrings[ iKey ], vecRandStrings[ iValue ],
					itrUnderobject->first );
#else //FEATURE_SIMPLE_CONSTRUCTOR
				cComment * pComment = new cComment(
					vecRandStrings[ iKey ], vecRandStrings[ iValue ],
					NULL, NULL, itrUnderobject->first );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
				//erase old/used and insert new Fib object
				liGeneratedFibObjects.erase( itrUnderobject );
				liGeneratedFibObjects.push_back( make_pair( pComment, ulEvaluedPoints ) );
#endif //FEATURE_GENERATED_LIST_OBJECT
				
			}break;
			case 'l':{//generate list element cList
				/*if the remaining Fib elements for the root -element are less
				than half of dAvarageUnderobjectsPerListelement add all to the
				listelement*/
				DEBUG_OUT_L2(<<"generating list element "<<endl<<flush);
				unsigned int uiNumberOfUnderobjects =
					rand() % (uiAvarageUnderobjectsPerListelement * 2);
				
#ifdef FEATURE_GENERATED_LIST_OBJECT
				if ( liGeneratedFibObjects.ulNumberOfFibObjects <
						(uiFibObjectsToGenerate + uiNumberOfUnderobjects + 2) ){
					/*add all Fib objects not needed plus one (the list will
					be added as an Fib object) in an root -element to the list*/
					uiNumberOfUnderobjects = liGeneratedFibObjects.ulNumberOfFibObjects -
						uiFibObjectsToGenerate + 1;
				}
				if ( uiNumberOfUnderobjects < 2 ){
					//minimum is two underobjects in an listelement
					uiNumberOfUnderobjects = 2;
				}
				if ( liGeneratedFibObjects.ulNumberOfFibObjects < uiNumberOfUnderobjects ){
					//not enough underobjects for the list element -> skip creating one
					continue;
				}
				pair< cFibElement*, unsigned long>
					paFirstUnderobject = liGeneratedFibObjects.choosFibElement();
				
				cList * pList = new cList( paFirstUnderobject.first , NULL );
				uiNumberOfUnderobjects--;
				//add the remaining underobjects to the listelement
				unsigned long ulEvaluedPoints = paFirstUnderobject.second;
				for ( ; uiNumberOfUnderobjects != 0 ; uiNumberOfUnderobjects-- ){
					pair< cFibElement*, unsigned long>
						paUnderobject = liGeneratedFibObjects.choosFibElement();
					pList->addUnderobject( paUnderobject.first );
					ulEvaluedPoints += paUnderobject.second;
				}
				liGeneratedFibObjects.addElement( make_pair( pList, ulEvaluedPoints ) );
#else //FEATURE_GENERATED_LIST_OBJECT
				if ( liGeneratedFibObjects.size() <
						(uiFibObjectsToGenerate + uiNumberOfUnderobjects + 2) ){
					/*add all Fib objects not needed plus one (the list will
					be added as an Fib object) in an root -element to the list*/
					uiNumberOfUnderobjects = liGeneratedFibObjects.size() -
						uiFibObjectsToGenerate + 1;
				}
				if ( uiNumberOfUnderobjects < 2 ){
					//minimum is two underobjects in an listelement
					uiNumberOfUnderobjects = 2;
				}
				if ( liGeneratedFibObjects.size() < uiNumberOfUnderobjects ){
					//not enough underobjects for the list element -> skip creating one
					continue;
				}
				list<pair< cFibElement*, unsigned long> >::iterator
					itrFirstUnderobject = choosFibElement( liGeneratedFibObjects );
				
				cList * pList = new cList( itrFirstUnderobject->first , NULL );
				uiNumberOfUnderobjects--;
				liGeneratedFibObjects.erase( itrFirstUnderobject );
				//add the remaining underobjects to the listelement
				unsigned long ulEvaluedPoints = 0;
				for ( ; uiNumberOfUnderobjects != 0 ; uiNumberOfUnderobjects-- ){
					list<pair< cFibElement*, unsigned long> >::iterator
						itrUnderobject = choosFibElement( liGeneratedFibObjects );
					pList->addUnderobject( itrUnderobject->first );
					ulEvaluedPoints += itrUnderobject->second;
					liGeneratedFibObjects.erase( itrUnderobject );
				}
				liGeneratedFibObjects.push_back( make_pair( pList, ulEvaluedPoints ) );
#endif //FEATURE_GENERATED_LIST_OBJECT
			}break;
			case 'v':{//generate set-element cFibSet
				DEBUG_OUT_L2(<<"generating set-element "<<endl<<flush);
				
				//generate number of vectors
				unsigned int iuNumberOfVariables = 1;
				if ( (rand() % 8) == 0 ){
					if ( (rand() % 256) == 0 ){
						iuNumberOfVariables = (rand() % 64 + 1);
					}else{
						iuNumberOfVariables = (rand() % 16 + 1);
					}
				}else{
					iuNumberOfVariables = (rand() % 4 + 1);
				}
#ifdef FEATURE_GENERATED_LIST_OBJECT
				pair< cFibElement*, unsigned long>
					paUnderobject = liGeneratedFibObjects.choosFibElement();
				unsigned long ulEvaluedPoints = paUnderobject.second;
				cFibSet * pFibSet = new cFibSet( iuNumberOfVariables,
					paUnderobject.first );
#else //FEATURE_GENERATED_LIST_OBJECT
				list< pair< cFibElement*, unsigned long> >::iterator
					itrUnderobject = choosFibElement( liGeneratedFibObjects );
				unsigned long ulEvaluedPoints = itrUnderobject->second;
				cFibSet * pFibSet = new cFibSet( iuNumberOfVariables,
					itrUnderobject->first );
#endif //FEATURE_GENERATED_LIST_OBJECT
				
				//generate vectors for set vectors
				unsigned int uiNumberOfSetVectors = 1;
				if ( (rand() % 2) == 0 ){
					if ( (rand() % 256) == 0 ){
						uiNumberOfSetVectors = (rand() % 1024 + 1);
					}else{
						uiNumberOfSetVectors = (rand() % 64 + 1);
					}
				}else{
					uiNumberOfSetVectors = (rand() % 8 + 1);
				}
				if ( ulEvaluedPoints * (uiNumberOfSetVectors - 1) < ulMaximalEvaluedPoints ){
					ulMaximalEvaluedPoints -= ulEvaluedPoints * (uiNumberOfSetVectors - 1);
				}else{
					ulMaximalEvaluedPoints = 0;
				}
				ulEvaluedPoints *= uiNumberOfSetVectors;
				//erase old/used and insert new Fib object
#ifdef FEATURE_GENERATED_LIST_OBJECT
				liGeneratedFibObjects.addElement( make_pair( pFibSet, ulEvaluedPoints ) );
#else //FEATURE_GENERATED_LIST_OBJECT
				liGeneratedFibObjects.erase( itrUnderobject );
				liGeneratedFibObjects.push_back( make_pair( pFibSet, ulEvaluedPoints ) );
#endif //FEATURE_GENERATED_LIST_OBJECT
				
				if ( (rand() % 8) == 0 ){
					//set domain number
					const unsignedLongFib uiDomainNumber =
						rand() % (1 + rand() % 64) + 1;
					pFibSet->setDomainNr( uiDomainNumber );
				}
				const doubleFib dSmalestUnit =
					evalueSmalestUnit( uiMaxVectorElementNumber );
				const longFib lMaxVectorElementNumber = ((longFib)(
					((longFib)uiMaxVectorElementNumber) / dSmalestUnit )) %
						((longFib)RAND_MAX);
				for ( unsigned int uiActualSetVector = 1;
						uiActualSetVector <= uiNumberOfSetVectors; uiActualSetVector++ ){
					
					cVectorFibSet vecSet( *pFibSet );
					for ( unsigned int uiActualElement = 1;
							uiActualElement <= iuNumberOfVariables; uiActualElement++ ){
						
						const doubleFib dValue = (double)(
							rand() % lMaxVectorElementNumber - 
							rand() % lMaxVectorElementNumber ) * dSmalestUnit;
						//add the subarea for the area
						vecSet.setValue( uiActualElement, dValue );
					}
					pFibSet->addVector( vecSet );
				}
			}break;
			case 'm':{//generate matrix element cFibMatrix
				DEBUG_OUT_L2(<<"generating matrix element "<<endl<<flush);
				
				//generate number of dimensions
				unsigned int iuNumberOfDimensions = 1;
				if ( (rand() % 8) == 0 ){
					iuNumberOfDimensions = rand() % (rand() % 16 + 1) + 3;
				}else{
					iuNumberOfDimensions = (rand() % 4 + 1);
				}
				//generate number of vector elements
				unsigned int iuNumberOfVectorElements = 1;
				if ( (rand() % 8) == 0 ){
					if ( (rand() % 256) == 0 ){
						iuNumberOfVectorElements = (rand() % 64 + 1);
					}else{
						iuNumberOfVectorElements = (rand() % 8 + 1);
					}
				}else{
					iuNumberOfVectorElements = (rand() % 4 + 1);
				}
#ifdef FEATURE_GENERATED_LIST_OBJECT
				pair< cFibElement*, unsigned long>
					paUnderobject = liGeneratedFibObjects.choosFibElement();
				unsigned long ulEvaluedPoints = paUnderobject.second;
				cFibMatrix * pFibMatrix = new cFibMatrix( iuNumberOfDimensions,
					iuNumberOfVectorElements, paUnderobject.first );
#else //FEATURE_GENERATED_LIST_OBJECT
				list< pair< cFibElement*, unsigned long> >::iterator
					itrUnderobject = choosFibElement( liGeneratedFibObjects );
				unsigned long ulEvaluedPoints = itrUnderobject->second;
				cFibMatrix * pFibMatrix = new cFibMatrix( iuNumberOfDimensions,
					iuNumberOfVectorElements, itrUnderobject->first );
#endif //FEATURE_GENERATED_LIST_OBJECT
				
				//generate vectors for set vectors
				unsigned int uiNumberOfMatrixVectors = 0;
				if ( (rand() % 8) != 0 ){
					if ( (rand() % 2) == 0 ){
						if ( (rand() % 256) == 0 ){
							uiNumberOfMatrixVectors = (rand() % 1024 + 1);
						}else{
							uiNumberOfMatrixVectors = (rand() % 64 + 1);
						}
					}else{
						uiNumberOfMatrixVectors = (rand() % 16 + 1);
					}
				}//else generate no matrix vectors
				//set area values
				unsigned long uiAreaValues = 1;
				for ( unsigned int iuActualArea = 1;
						iuActualArea <= iuNumberOfDimensions; iuActualArea++ ){
					
					const longFib lLowerBounderie =
						rand() % uiMaxVectorElementNumber -
						rand() % uiMaxVectorElementNumber;
					longFib lUpperBounderie = 0;
					if ( rand() % (iuNumberOfDimensions * 16) != 0 ){
						//confined bouderie area
						lUpperBounderie = lLowerBounderie + (rand() % 32) - 16;
					}else if ( rand() % (iuNumberOfDimensions * 16) != 0 ){
						lUpperBounderie = lLowerBounderie +
							(rand() % (uiNumberOfMatrixVectors + 2)) -
							(rand() % (uiNumberOfMatrixVectors + 4));
					}else{
						lUpperBounderie = lLowerBounderie +
							(rand() % (uiMaxVectorElementNumber / 32 + 32)) -
							(uiMaxVectorElementNumber / 64 + 16);
					}
					if ( uiMaxVectorElementNumber < ((unsigned long)lUpperBounderie) ){
						lUpperBounderie = uiMaxVectorElementNumber;
					}else if ( lUpperBounderie < (((long)uiMaxVectorElementNumber) * -1L) ){
						lUpperBounderie = ((long)uiMaxVectorElementNumber) * -1L;
					}
					//check the points evalued for the matrix object
					unsigned int ulCountValues =
						abs( lLowerBounderie - lUpperBounderie ) + 1;
					
					if ( uiNumberOfMatrixVectors == 0 ){
						//the area values determines the number of evalue calls
						if ( ulMaximalEvaluedPoints < (ulCountValues *
								uiAreaValues * ulEvaluedPoints) ){
							
							while ( ( lLowerBounderie != lUpperBounderie ) &&
									( ulMaximalEvaluedPoints < ( ulCountValues *
										uiAreaValues * ulEvaluedPoints ) ) ){
								
								if ( lLowerBounderie < lUpperBounderie ){
									lUpperBounderie--;
								}else{
									lUpperBounderie++;
								}
								ulCountValues--;
							}
						}
					}
					uiAreaValues *= ulCountValues;
					//add the subarea for the area
					cVectorArea * pArea = pFibMatrix->getArea( iuActualArea );
					pArea->setValue( 1, lLowerBounderie );
					pArea->setValue( 2, lUpperBounderie );
				}
				//evalue evalue calls
				const unsigned long ulEvalueCalls =
					(uiNumberOfMatrixVectors == 0) ?
						uiAreaValues :
							( uiAreaValues < uiNumberOfMatrixVectors )?
								uiAreaValues : uiNumberOfMatrixVectors;
				if ( ulEvaluedPoints * (ulEvalueCalls - 1) < ulMaximalEvaluedPoints ){
					ulMaximalEvaluedPoints -= ulEvaluedPoints * (ulEvalueCalls - 1);
				}else{
					ulMaximalEvaluedPoints = 0;
				}
				ulEvaluedPoints *= ulEvalueCalls;
				
				//erase old/used and insert new Fib object
#ifdef FEATURE_GENERATED_LIST_OBJECT
				liGeneratedFibObjects.addElement( make_pair( pFibMatrix, ulEvaluedPoints ) );
#else //FEATURE_GENERATED_LIST_OBJECT
				liGeneratedFibObjects.erase( itrUnderobject );
				liGeneratedFibObjects.push_back( make_pair( pFibMatrix, ulEvaluedPoints ) );
#endif //FEATURE_GENERATED_LIST_OBJECT
				
				if ( (rand() % 8) == 0 ){
					//set domain number
					const unsignedLongFib uiDomainNumber =
						rand() % (1 + rand() % 64) + 1;
					pFibMatrix->setDomainNr( uiDomainNumber );
				}
				const doubleFib dSmalestUnit =
					evalueSmalestUnit( uiMaxVectorElementNumber );
				const longFib lMaxVectorElementNumber = ((longFib)(
					((longFib)uiMaxVectorElementNumber) / dSmalestUnit )) %
						((longFib)RAND_MAX);
				for ( unsigned int uiActualMatrixVector = 1;
						uiActualMatrixVector <= uiNumberOfMatrixVectors; uiActualMatrixVector++ ){
					
					cVectorFibMatrix vecMatrix( *pFibMatrix );
					for ( unsigned int uiActualElement = 1;
							uiActualElement <= iuNumberOfVectorElements; uiActualElement++ ){
						
						const doubleFib dValue = (double)(
							rand() % lMaxVectorElementNumber - 
							rand() % lMaxVectorElementNumber ) * dSmalestUnit;
						//add the subarea for the area
						vecMatrix.setValue( uiActualElement, dValue );
					}
					pFibMatrix->addVector( vecMatrix );
				}
			}break;
			
			
			
			
			default://try again
				continue;
		}
		DEBUG_OUT_L2(<<"generating element done "<<endl<<flush);
	}
	
#ifdef FEATURE_GENERATED_LIST_OBJECT
	return liGeneratedFibObjects.liFibObjects;
#else //FEATURE_GENERATED_LIST_OBJECT
	return liGeneratedFibObjects;
#endif //FEATURE_GENERATED_LIST_OBJECT
}//end generateFibObjects()



/**
 * 
 * @param pFibObject a pointer to the subobject in which the external
 * 	subobjects should be adapted
 * @param vecNumberOutVars a vector with the number of output values
 * 	for the external subobjects to change; the index i is for the
 * 	(i+1)'th subobject
 * @param dFractionsOfUsedVariables the fraction of elements of
 * 	vectors, which should be variables
 * @param uiMaxVectorElementNumber the maximal number for a vectorelement,
 * 	the number in vectorelements will vary from 0 till
 * @return a pointer to the Fib object (pInFibObject) with the changed
 * 	external subobjects
 */
cFibElement * adaptSubobjects( cFibElement * pFibObject,
		vector< unsignedIntFib > vecNumberOutVars,
		const double dFractionsOfUsedVariables = 0.5,
		unsigned long uiMaxVectorElementNumber = 1023 ){
	
	const unsignedIntFib uiMaxSubobjects = vecNumberOutVars.size();
	//create the set with subobject not used yet
	set< unsignedIntFib > setNotUsedSubobjectNumbers;
	for ( unsigned int uiActualSubobject = 1;
			uiActualSubobject <= uiMaxSubobjects; uiActualSubobject++ ){
		
		setNotUsedSubobjectNumbers.insert( uiActualSubobject );
	}

	//for all external subobject elements
	for ( cExtSubobject * pExtSubobjectElement =
			(cExtSubobject*)(pFibObject->getNextFibElement( 's' )); 
		pExtSubobjectElement != NULL;
		pExtSubobjectElement =
			(cExtSubobject*)(pExtSubobjectElement->getNextFibElement( 's' )) ){
		
		DEBUG_OUT_L2(<<"adapting external subobject element "<<pExtSubobjectElement<<" with number "<<flush<<pExtSubobjectElement->getNumberOfElement()<<endl<<flush);
		
		//choose subobject number to set
		longFib lSubobjectNumber = 0;
		if ( setNotUsedSubobjectNumbers.empty() || ( rand() % 8 == 0 ) ){
			//choose a random number as subobject number
			lSubobjectNumber = 1 + rand() % uiMaxSubobjects;
			
		}else{//use a not used subobject number
			lSubobjectNumber = rand() % setNotUsedSubobjectNumbers.size();
			set< unsignedIntFib >::iterator itrSubObjectNumber =
				setNotUsedSubobjectNumbers.begin();
			for ( ; 0 < lSubobjectNumber ; itrSubObjectNumber++, lSubobjectNumber-- ){
				//nothing to do
			}
			lSubobjectNumber = (*itrSubObjectNumber);
			setNotUsedSubobjectNumbers.erase( itrSubObjectNumber );
		}
		DEBUG_OUT_L2(<<"setting subobject number "<<lSubobjectNumber<<" for external subobject element "<<endl<<flush);
		
		pExtSubobjectElement->setNumberSubobject( lSubobjectNumber );
		
		//insert values for external object
		const unsignedIntFib uiOutputValuesToSet =
			vecNumberOutVars[ lSubobjectNumber - 1 ];
		
		if ( 0 < uiOutputValuesToSet ){
			//evalue possible/ defined variables for the element
			DEBUG_OUT_L2(<<"   set "<<uiOutputValuesToSet<<" output values for external subobject element "<<endl<<flush);
			list<cFibVariable*> liDefinedVariables =
				pExtSubobjectElement->getDefinedVariables( ED_HIGHER );
			
			cVectorExtSubobject * pVectorExtSubobject =
				pExtSubobjectElement->getOutputVector();
			
			pVectorExtSubobject->resize( uiOutputValuesToSet );
			
			const doubleFib dSmalestUnit =
				evalueSmalestUnit( uiMaxVectorElementNumber );
			const longFib lMaxVectorElementNumber = ((longFib)(
				((longFib)uiMaxVectorElementNumber) / dSmalestUnit )) %
					((longFib)RAND_MAX);
			for ( unsignedIntFib uiActualOutputValue = 1;
					uiActualOutputValue <= uiOutputValuesToSet; uiActualOutputValue++ ){
				
				const double dRandom = (double)(rand() % RAND_MAX) / (double)(RAND_MAX);
				if ( ( ! liDefinedVariables.empty() ) && 
						( dRandom < dFractionsOfUsedVariables ) ){
					//set actual input value to variables
					//choose variable to set
					unsigned int uiChoosenVariable = rand() % liDefinedVariables.size();
					list<cFibVariable*>::iterator itrChoosenVariable = liDefinedVariables.begin();
					while ( uiChoosenVariable != 0){
						itrChoosenVariable++;
						uiChoosenVariable--;
					}
					pVectorExtSubobject->setVariable( uiActualOutputValue, (*itrChoosenVariable) );
				}else{//set actual input value to value
					const doubleFib dValue = (double)(
						rand() % lMaxVectorElementNumber - 
						rand() % lMaxVectorElementNumber ) * dSmalestUnit;
					pVectorExtSubobject->setValue( uiActualOutputValue, dValue );
				}
			}
		}//else set no output values
	}//end for all external subobject elements
	
	return pFibObject;
}



/**
 * This function generates a Fib object with around uiSize
 * Fib elements.
 * Beware: You have to delete the returned Fib object.
 *
 * @param uiSize a roughly number of Fib elements in the generated Fib objects
 * @param ulMaximalEvaluedPoints a roughly number of points the Fib object
 * 	should evalue to; (this test didn't includes /checks variables, so it
 * 	basicly just works for dFractionsOfUsedVariables = 0.0;
 * 	it also dosn't include external subobjects)
 * @param liFractionOfFibElements the fractions of different
 * 	Fib elementtyps in the generated Fib Object;
 * 	first element of the pair is the char for the type of the
 * 	Fib element (@see getType()), second element is the number for the
 * 	fraction of the Fib element;
 * 	the fractions will be normalized, so that they sum to 1
 * @param liPossiblePropertyTyps the list with the possible propertytyps in the
 * 	generated Fib object
 * @param vecDimensions the vector with the size of the different dimensions
 * @param uiAverageSubRoots number of the average sub -root -objects per
 * 	root -element (sub -roots -elements without sub -roots -won't be counted)
 * @param uiAverageSubRootsDepth the average depth of sub -root -elements
 * @param uiNumberOfAverageInputVariables the number of average input
 * 	variables per root -element
 * @param dFractionsOfUsedVariables the fraction of elements of
 * 	vectors, which should be variables
 * @param uiMaxVectorElementNumber the maximal number for a vectorelement,
 * 	the number in vectorelements will vary from 0 till
 * 	uiMaxVectorElementNumber
 * @return the generated Fib object or NULL, if no Fib object could be generated
 */
cFibElement * generateFibObject( unsigned int uiSize, unsigned long ulMaximalEvaluedPoints,
		list< pair< char, double > > liFractionOfFibElements,
		const list< cTypeProperty > & liPossiblePropertyTyps,
		const vector<unsigned long> & vecDimensions,
		const unsigned int uiAverageSubRoots = 2, const unsigned int uiAverageSubRootsDepth = 1,
		const unsigned int uiNumberOfAverageInputVariables = 1,
		const double dFractionsOfUsedVariables = 0.5,
		unsigned long uiMaxVectorElementNumber = 1023 ){
	
	DEBUG_OUT_L2(<<"generateFibObject( unsigned int uiSize="<<uiSize<<",  ulMaximalEvaluedPoints="<<ulMaximalEvaluedPoints<<", liFractionOfFibElements,");
	DEBUG_OUT_L2(<<"liPossiblePropertyTyps, vecDimensions, uiAverageSubRoots="<<uiAverageSubRoots<<",");
	DEBUG_OUT_L2(<<"const unsigned int uiAverageSubRootsDepth="<<uiAverageSubRootsDepth<<", uiNumberOfAverageInputVariables="<<uiNumberOfAverageInputVariables<<", ");
	DEBUG_OUT_L2(<<"dFractionsOfUsedVariables="<<dFractionsOfUsedVariables<<", uiMaxVectorElementNumber="<<uiMaxVectorElementNumber<<" ) started"<<endl<<flush);
	
	static bool bRandomGeneratorStarted = false;
	if ( ! bRandomGeneratorStarted ){
		srand( time(NULL) );
		bRandomGeneratorStarted = true;
		initVecRandStrings();
	}
	
	//evale values
	if ( uiSize == 0 ){
		//minimum size is 1
		DEBUG_OUT_L2(<<"generateFibObject() done uiSize = 0"<<endl<<flush);
		return NULL;
	}
	const unsigned int uiNumberOfDimensions = vecDimensions.size();
	if ( uiNumberOfDimensions == 0 ){
		//minimum size is 1
		DEBUG_OUT_L2(<<"generateFibObject() done uiNumberOfDimensions = 0"<<endl<<flush);
		return NULL;
	}
	if ( uiMaxVectorElementNumber == 0 ){
		//minimum size is 1
		DEBUG_OUT_L2(<<"generateFibObject() done uiMaxVectorElementNumber = 0"<<endl<<flush);
		return NULL;
	}
	//get the number of root elements
	unsigned int uiRootElementsToGenerate = pow( uiAverageSubRoots, uiAverageSubRootsDepth );
	if ( uiSize < uiRootElementsToGenerate ){
		//to much root-elements to generate
		uiRootElementsToGenerate = uiSize;
	}
	
	
	//generate Fib subobjects
	list< pair< cFibElement*, unsigned long> > liGeneratedFibObjects =
		generateFibObjects( uiRootElementsToGenerate, uiSize,
			ulMaximalEvaluedPoints,
			liFractionOfFibElements, liPossiblePropertyTyps,
			vecDimensions, uiMaxVectorElementNumber );
	

	DEBUG_OUT_L2(<<"generating roots"<<endl<<flush);
	//generate root -elements
	list< cRoot* > liGeneratedRoots;
	//put every generated Fib object into an new root -element
	while ( ! liGeneratedFibObjects.empty() ){
		
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
		cRoot * pRoot = new cRoot( liGeneratedFibObjects.front().first );
#else //FEATURE_SIMPLE_CONSTRUCTOR
		cRoot * pRoot = new cRoot( NULL, NULL, liGeneratedFibObjects.front().first );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
		liGeneratedFibObjects.pop_front();
		liGeneratedRoots.push_back( pRoot );
		
		//set input variables of the root -element
		if ( uiNumberOfAverageInputVariables != 0 ){
			pRoot->setNumberOfInputVariables( rand() % (uiNumberOfAverageInputVariables * 2) );
		}

							//randomly generate optional part
		if ( rand() % 4 == 0 ){
			const unsigned int uiNumberOfEntries =
				( rand() % ( rand() % (rand() % 256 + 1 ) + 1 ));
			
			for ( unsigned int uiActualEntry = 0;
					uiActualEntry < uiNumberOfEntries; uiActualEntry++ ){
				
				const size_t iKey = rand() % vecRandStrings.size();
				const size_t iValue = rand() % vecRandStrings.size();
				
				pRoot->getOptionalPart()->addEntry(
					vecRandStrings[ iKey ], vecRandStrings[ iValue ] );
			}
		}
	}
	list< cRoot* > liAllGeneratedRoots = liGeneratedRoots;
	DEBUG_OUT_L2(<<"roots generated = "<<liGeneratedRoots.size()<<endl<<flush);
	
	//adapt external subobjects
	for ( list< cRoot* >::iterator itrFibObject = liGeneratedRoots.begin();
			itrFibObject != liGeneratedRoots.end(); itrFibObject++ ){
		
		cRoot * pActualFibObject = (*itrFibObject);
		//evalue the vector with the numbers of output values for the external subobjects
		const unsignedIntFib uiNumberOfExternalObjectElements =
			pActualFibObject->getNumberOfElements( 's' );
		if ( uiNumberOfExternalObjectElements == 0 ){
			//no external subobject elements -> skip object
			continue;
		}
		DEBUG_OUT_L3(<<"adapting external subobjects for new Fib object with "<<uiNumberOfExternalObjectElements<<" external subobject elements"<<endl<<flush);
		//create the vector with the number of output values
		unsignedIntFib uiMaxSubobjects = 1;
		if ( uiNumberOfExternalObjectElements < 16 ){
			uiMaxSubobjects = 1 + rand() %  ( 1 + rand() %
				( uiNumberOfExternalObjectElements + 1 ) );
		}else if ( uiNumberOfExternalObjectElements < 64 ){
			uiMaxSubobjects = 1 + rand() %  ( 1 + rand() %  ( 1 + rand() %
				( uiNumberOfExternalObjectElements + 4 ) ) );
		}else{//big number of external subobject elements
			uiMaxSubobjects = 1 + rand() %  ( 1 + rand() %  ( 1 + rand() % ( 1 + rand() %
				( uiNumberOfExternalObjectElements + 32 ) ) ) );
		}
		vector< unsignedIntFib > vecNumberOutVars( uiMaxSubobjects );
		//evalue number of output variables for the subobjects
		cFibElement * pActualMainFibObject =
			pActualFibObject->getNextFibElement();
		
		for ( unsigned int uiActualSubobject = 0;
				uiActualSubobject < uiMaxSubobjects; uiActualSubobject++ ){
			
			const unsignedIntFib uiNumberOfOutputVariables = rand() %
				( 4 + rand() % ( 1 + rand() % ( ((unsigned int)log(
					pActualMainFibObject->getNumberOfElements() )) + 8 ) ) );
			
			vecNumberOutVars[ uiActualSubobject ] = uiNumberOfOutputVariables;
			
			DEBUG_OUT_L3(<<"   subobject "<<(uiActualSubobject+1)<<" has "<<uiNumberOfOutputVariables<<" output variables"<<endl<<flush);
		}
		
		adaptSubobjects( pActualFibObject, vecNumberOutVars,
			dFractionsOfUsedVariables, uiMaxVectorElementNumber );
		
		//generate domains for the external subobjects
		pActualFibObject->generateExternSubobjectsDefinitions();
	}
	
	//add root -objects as sub -root -objects till one root -element remains
	cRoot * pMasterRoot = liGeneratedRoots.back();
	liGeneratedRoots.pop_back();
	unsigned int uiSubRootsForMasterRoot = 0;
	if ( 0 < uiAverageSubRoots ){
		uiSubRootsForMasterRoot = rand() % (uiAverageSubRoots * 2);
	}
	if ( uiSubRootsForMasterRoot < 1 ){
		uiSubRootsForMasterRoot = 1;
	}
	/*take a root from liGeneratedRoots put it into liGeneratedRootsWithSub,
	then put roots from liGeneratedRoots as sub -roots into it;
	if liGeneratedRoots is empty put the roots from liGeneratedRoots back
	into it and begin again till the remaining roots are for the master root*/
	DEBUG_OUT_L2(<<"inserting subroots"<<endl<<flush);
	list< cRoot* > liGeneratedRootsWithSub;
	unsigned int uiActualSubRoot = 1;
	while ( uiSubRootsForMasterRoot <=
			(liGeneratedRoots.size() + liGeneratedRootsWithSub.size()) ){
		
		liGeneratedRootsWithSub.push_back( liGeneratedRoots.front() );
		liGeneratedRoots.pop_front();
		unsigned int uiSubRootsToAdd  = 0;
		if ( 0 < uiAverageSubRoots ){
			uiSubRootsToAdd = rand() % (uiAverageSubRoots * 2);
		}

		if ( liGeneratedRoots.size() < (int)((double)(uiSubRootsToAdd) * 1.5) ){
			uiSubRootsToAdd = liGeneratedRoots.size();
		}
		if ( (liGeneratedRoots.size() + liGeneratedRootsWithSub.size()) <
				(uiSubRootsForMasterRoot + uiSubRootsToAdd) ){
			uiSubRootsToAdd = (liGeneratedRoots.size() +
				liGeneratedRootsWithSub.size()) - uiSubRootsForMasterRoot;
			
			if ( liGeneratedRoots.size() < uiSubRootsToAdd ){
				uiSubRootsToAdd = liGeneratedRoots.size();
			}
		}
		while ( uiSubRootsToAdd != 0 ){
			liGeneratedRootsWithSub.back()->addSubRootObject(
				uiActualSubRoot, liGeneratedRoots.back() );
			liGeneratedRoots.pop_back();
			uiActualSubRoot++;
			uiSubRootsToAdd--;
		}
		if ( liGeneratedRoots.empty() ){
			//generate next level
			liGeneratedRoots = liGeneratedRootsWithSub;
			liGeneratedRootsWithSub.clear();
		}
		if ( (liGeneratedRoots.size() + liGeneratedRootsWithSub.size()) <=
				(int)((double)(uiSubRootsForMasterRoot) * 1.5) ){
			//the remaining roots are for the master root
			while ( ! liGeneratedRootsWithSub.empty() ){
				liGeneratedRoots.push_front( liGeneratedRootsWithSub.front() );
				liGeneratedRootsWithSub.pop_front();
			}
			break;
		}
	}
	//add the remaining sub root objects to the master root
	while ( ! liGeneratedRoots.empty() ){
		pMasterRoot->addSubRootObject( uiActualSubRoot, liGeneratedRoots.back() );
		liGeneratedRoots.pop_back();
		uiActualSubRoot++;
	}
	
	
	//change and adapt the cExtObject
	cExtObject * pExtObjectElement = (cExtObject*)(pMasterRoot->getNextFibElement( 'o' ));
	while ( pExtObjectElement != NULL ){
		
		DEBUG_OUT_L2(<<"adapting external object element "<<pExtObjectElement<<" with number "<<flush<<pExtObjectElement->getNumberOfElement()<<endl<<flush);
		//choose root-element to call
		const list<longFib> liIdentifiers =
			pExtObjectElement->getAllAccessibleRootObjectIdentifiers();
		cRoot * pChoosenRoot = NULL;
		if ( ! liIdentifiers.empty() ){
			//identifiers to set -> set one
			longFib lIdentifierChoosen = 0;
			if ( rand() % 64 ){
				list<longFib>::const_iterator itrIdentifier = liIdentifiers.begin();
				for ( unsignedIntFib uiNextIdentifierChoosen = rand() % liIdentifiers.size();
						0 < uiNextIdentifierChoosen; uiNextIdentifierChoosen--, itrIdentifier++ ){
					//nothing to do
				}
				lIdentifierChoosen = (*itrIdentifier);
			}else{//take random identifier
				lIdentifierChoosen = ((longFib)(rand() % RAND_MAX)) - ((longFib)(RAND_MAX / 2));
			}
			DEBUG_OUT_L2(<<"setting identifier "<<lIdentifierChoosen<<" for external object element "<<endl<<flush);
			
			pExtObjectElement->setIdentifier( lIdentifierChoosen );
			
			pChoosenRoot = pExtObjectElement->getAccessibleRootObject( lIdentifierChoosen );
		}else{//take random identifier
			longFib lIdentifierChoosen = 0;
			if ( rand() % 2 ){
				lIdentifierChoosen = ((longFib)(rand() % RAND_MAX)) - ((longFib)(RAND_MAX / 2));
			}
			DEBUG_OUT_L2(<<"setting identifier "<<lIdentifierChoosen<<" for external object element "<<endl<<flush);
			
			pExtObjectElement->setIdentifier( lIdentifierChoosen );
		}
		//now vector to replace values with variables
		
		//insert variables for external object
		unsignedIntFib uiInputValuesToSet = 0;
		if ( pChoosenRoot ){
			uiInputValuesToSet = pChoosenRoot->getNumberOfInputVariables();
		}
		if ( (rand() % 32) == 0 ){
			//set wrong number of input values
			uiInputValuesToSet = rand() % ( rand() % (uiInputValuesToSet + 32) + 1 );
		}
		if ( 0 < uiInputValuesToSet ){
			//evalue possible/ defined variables for the element
			DEBUG_OUT_L2(<<"set "<<uiInputValuesToSet<<" input values for external object element "<<endl<<flush);
			list<cFibVariable*> liDefinedVariables =
				pExtObjectElement->getDefinedVariables( ED_HIGHER );
			
			pExtObjectElement->setNumberOfInputValues( uiInputValuesToSet );
			cVectorExtObject * pVectorExtObject =
				pExtObjectElement->getInputVector();
			
			const doubleFib dSmalestUnit =
				evalueSmalestUnit( uiMaxVectorElementNumber );
			const longFib lMaxVectorElementNumber = ((longFib)(
				((longFib)uiMaxVectorElementNumber) / dSmalestUnit )) %
					((longFib)RAND_MAX);
			for ( unsignedIntFib uiActualInputValue = 1;
					uiActualInputValue <= uiInputValuesToSet; uiActualInputValue++ ){
				
				const double dRandom = (double)(rand() % RAND_MAX) / (double)(RAND_MAX);
				if ( ( ! liDefinedVariables.empty() ) && 
						( dRandom < dFractionsOfUsedVariables ) ){
					//set actual input value to variables
					//choose variable to set
					unsigned int uiChoosenVariable = rand() % liDefinedVariables.size();
					list<cFibVariable*>::iterator itrChoosenVariable = liDefinedVariables.begin();
					while ( uiChoosenVariable != 0){
						itrChoosenVariable++;
						uiChoosenVariable--;
					}
					pVectorExtObject->setVariable( uiActualInputValue, (*itrChoosenVariable) );
				}else{//set actual input value to value
					const doubleFib dValue = (double)(
						rand() % lMaxVectorElementNumber - 
						rand() % lMaxVectorElementNumber ) * dSmalestUnit;
					pVectorExtObject->setValue( uiActualInputValue, dValue );
				}
			}
		}//else set no input values
		
		//insert subobjects for external object
		unsignedIntFib uiNumberOfNeededSubobjects = 0;
		if ( pChoosenRoot ){
			uiNumberOfNeededSubobjects = pChoosenRoot->getNumberOfExternSubobjects();
		}
		
		unsignedIntFib uiNumberOfToSetSubobjects = uiNumberOfNeededSubobjects;
		if ( rand() % 64 == 0 ){
			//set wrong number of subobjects
			uiNumberOfToSetSubobjects = rand() % ( rand() % (uiNumberOfNeededSubobjects + 32) + 1 );
		}
		
		DEBUG_OUT_L2(<<"try set "<<uiNumberOfToSetSubobjects<<" subobjects (needed "<<uiNumberOfNeededSubobjects<<") for the external object element "<<pExtObjectElement<<" with number "<<flush<<pExtObjectElement->getNumberOfElement()<<" for the root object "<<pChoosenRoot<<endl<<flush);
		if ( 0 < uiNumberOfToSetSubobjects ){
			//if subobjects should be generated -> generate them
			pExtObjectElement->setNumberOfSubobjects( uiNumberOfToSetSubobjects );
			DEBUG_OUT_L3(<<"   "<<uiNumberOfToSetSubobjects<<" subobjects set"<<endl<<flush);
			
			for ( unsignedIntFib uiActualSubobject = 1;
						uiActualSubobject <= uiNumberOfToSetSubobjects;
						uiActualSubobject++ ){
				//generate output variables
				unsignedIntFib uiOutputVariablesToSet = 0;
				if ( pChoosenRoot ){
					uiOutputVariablesToSet = pChoosenRoot->getNumberOfOutputVariables( uiActualSubobject );
					DEBUG_OUT_L3(<<"   external subobject should have "<<uiOutputVariablesToSet<<" output variables"<<endl<<flush);
				}
				if ( rand() % 64 == 0 ){
					//set wrong number of output variables
					uiOutputVariablesToSet = rand() % ( rand() % (uiOutputVariablesToSet + 32) + 1 );
				}
				DEBUG_OUT_L3(<<"   setting "<<uiOutputVariablesToSet<<" output variables for the "<<uiActualSubobject<<"'th subobject"<<endl<<flush);
				pExtObjectElement->setNumberOfOutputVariables(
					uiActualSubobject, uiOutputVariablesToSet );
				
				//generate subobject to set
				unsigned int uiSizeSubobject = log( uiSize );
				if ( uiSizeSubobject == 0 ){
					uiSizeSubobject = 1;
				}
				DEBUG_OUT_L3(<<"   generating for the external object element as the "<<uiActualSubobject<<"'th subobject ..."<<flush);
				list< pair< cFibElement*, unsigned long> > liExtSubobject =
					generateFibObjects( 1, uiSizeSubobject,
						ulMaximalEvaluedPoints,
						liFractionOfFibElements, liPossiblePropertyTyps,
						vecDimensions, uiMaxVectorElementNumber );
					
				DEBUG_OUT_L3(<<" "<<liExtSubobject.size()<<" subobject(s) -> done"<<endl<<flush);
				//insert generated subobject
				if ( ! liExtSubobject.empty() ){
					//adapt external subobjects
					cRoot * pSuperiorRoot = pExtObjectElement->getSuperiorRootElement();
					if ( pSuperiorRoot != NULL ){
						const unsignedIntFib uiNumberOfExternSubobjects =
							pSuperiorRoot->getNumberOfExternSubobjects();
						const bool bNewExtSubobjectsGenerated =
							(uiNumberOfExternSubobjects == 0);
						vector< unsignedIntFib > vecNumberOutVars( uiNumberOfExternSubobjects );
						for ( unsignedIntFib uiActualExtSubobject = 1;
								uiActualExtSubobject <= uiNumberOfExternSubobjects;
								uiActualExtSubobject++ ){
							
							vecNumberOutVars[ uiActualExtSubobject - 1 ] =
								pSuperiorRoot->getNumberOfOutputVariables( 
									uiActualExtSubobject );
						}
						if ( bNewExtSubobjectsGenerated ){
							//no external subobjects exists -> give minimum one
							vecNumberOutVars.push_back( 0 );
						}
						
						adaptSubobjects( liExtSubobject.front().first,
							vecNumberOutVars, dFractionsOfUsedVariables,
							  uiMaxVectorElementNumber );
						
						if ( bNewExtSubobjectsGenerated ){
							//generate new domains for the new external subobjects
							pSuperiorRoot->generateExternSubobjectsDefinitions();
						}
					}//end if adapt external subobjects
					
					DEBUG_OUT_L3(<<"   adding to the external object element the subobject "<<liExtSubobject.front().first<<" as the "<<uiActualSubobject<<"'th subobject"<<endl<<flush);
					
					pExtObjectElement->setSubobject(
						uiActualSubobject, liExtSubobject.front().first );
				}
			}
		}
		
		//evalue next function element
		pExtObjectElement = (cExtObject*)(pExtObjectElement->getNextFibElement( 'o' ));
	}
	
	DEBUG_OUT_L2(<<"generating domains"<<endl<<flush);
	//set domains of master root -object

	//set the dimension domain
	cTypeDimension typeDimension( uiNumberOfDimensions );
	vector<cDomainSingle*> vecDomainsDimension( uiNumberOfDimensions );
	
	for ( unsigned int uiActualDimensions = 0;
			uiActualDimensions < uiNumberOfDimensions; uiActualDimensions++ ){
		
		cDomainNaturalNumber * pDomainNaturalNumber =
			new cDomainNaturalNumber( vecDimensions[ uiActualDimensions ] );
		vecDomainsDimension[ uiActualDimensions ] = pDomainNaturalNumber;
	}
	cDomainVector vectorDomainDimension( vecDomainsDimension );
	
	for ( unsigned int uiActualDimensions = 0;
			uiActualDimensions < uiNumberOfDimensions; uiActualDimensions++ ){
		
		delete vecDomainsDimension[ uiActualDimensions ];
	}
	
	pMasterRoot->getDomains()->addDomain( typeDimension, vectorDomainDimension );
	
	for ( list< cRoot* >::iterator itrRoot = liAllGeneratedRoots.begin();
			itrRoot != liAllGeneratedRoots.end(); itrRoot++ ){
		//randomly add domains domains
		if ( rand() % 4 == 0 ){
			(*itrRoot)->getDomains()->addDomain( typeDimension, vectorDomainDimension );
		}
#ifndef FEATURE_GENERATE_NEEDED_DOMAINS
#ifdef FEATURE_USE_GENERATE_NEEDED_DOMAINS
		if ( rand() % 4 == 0 ){
			(*itrRoot)->generateNeededDomains();
		}
#endif //FEATURE_USE_GENERATE_NEEDED_DOMAINS
#endif //FEATURE_GENERATE_NEEDED_DOMAINS
	}
	
	cDomainNaturalNumber domainNaturalNumber( uiMaxVectorElementNumber );
	//set the property domains
	for ( list< cTypeProperty >::const_iterator itrPropertytype = liPossiblePropertyTyps.begin();
			itrPropertytype != liPossiblePropertyTyps.end(); itrPropertytype++ ){
		
		//get the number of vector elements for the domain
		cDomainVector * pStandardDomain = (cDomainVector*)(
			itrPropertytype->getStandardDomain());
		
		vector<cDomainSingle*> vecDomainsProperty(
			pStandardDomain->getNumberOfElements(), &domainNaturalNumber );

		cDomainVector vectorDomainProperty( vecDomainsProperty );

		pMasterRoot->getDomains()->addDomain( (*itrPropertytype),
			vectorDomainProperty );
		
		for ( list< cRoot* >::iterator itrRoot = liAllGeneratedRoots.begin();
				itrRoot != liAllGeneratedRoots.end(); itrRoot++ ){
			//randomly add domains domains
			if ( rand() % 4 == 0 ){
				(*itrRoot)->getDomains()->addDomain( (*itrPropertytype),
					vectorDomainProperty );
			}
		}
		delete pStandardDomain;
	}
#ifdef FEATURE_USE_GENERATE_NEEDED_DOMAINS
	//generate function- and area element domains
	pMasterRoot->generateNeededDomains();
#else //FEATURE_USE_GENERATE_NEEDED_DOMAINS
	//set domains for optional fib-elements
	for ( list< pair< char, double > >::iterator itrElementFractions =
			liFractionOfFibElements.begin();
			itrElementFractions != liFractionOfFibElements.end();
			itrElementFractions++ ){
		
		if ( (itrElementFractions->first == 'a') && (itrElementFractions->second != 0.0) ){
			//set area domain
			vector<cDomainSingle*> vecDomainsArea( 2, &domainNaturalNumber );
	
			cDomainVector vectorDomainArea( vecDomainsArea );
	
			pMasterRoot->getDomains()->addDomain( cTypeSubarea(), vectorDomainArea );
			
		}else if ( (itrElementFractions->first == 'f') && (itrElementFractions->second != 0.0) ){
			//set function domain
			pMasterRoot->getDomains()->addDomain( cTypeUnderFunction(), domainNaturalNumber );
		}

	}
#endif //FEATURE_USE_GENERATE_NEEDED_DOMAINS
	
	
	DEBUG_OUT_L2(<<"generating variables"<<endl<<flush);
	if ( (pMasterRoot->getNumberOfInputVariables() == 0) && (
			( 0 < uiNumberOfAverageInputVariables ) || ( 0.0 < dFractionsOfUsedVariables) ) ){
		//the master root needs one input variable
		pMasterRoot->setNumberOfInputVariables( 1 );
	}
	
	if ( 0.0 < dFractionsOfUsedVariables ){
		//** insert random variables
		
		//insert variables into pointelements
		cPoint * pPointElement = (cPoint*)(pMasterRoot->getNextFibElement( 'p' ));
		while ( pPointElement != NULL ){
			//evalue possible/ defined variables for the element
			list<cFibVariable*> liDefinedVariables =
				pPointElement->getDefinedVariables( ED_HIGHER );
			if ( liDefinedVariables.empty() ){
				//no variables defined for the pointelement -> skip it
				//evalue next pointelement
				pPointElement = (cPoint*)(pPointElement->getNextFibElement( 'p' ));
				continue;
			}
			//for every element in the positionsvector
			cVectorPosition * pVecPosition = pPointElement->getPosition();
			if ( pVecPosition ){
				for ( unsigned int uiActualElement = 1;
						uiActualElement <= pVecPosition->getNumberOfElements();
						uiActualElement++ ){
					
					double dRandom = (double)(rand() % RAND_MAX) / (double)(RAND_MAX);
					if ( dRandom < dFractionsOfUsedVariables ){
						//choos random defined variables and insert it
						unsigned int uiChoosenVariable = rand() % liDefinedVariables.size();
						list<cFibVariable*>::iterator itrChoosenVariable =
							liDefinedVariables.begin();
						while ( uiChoosenVariable != 0){
							itrChoosenVariable++;
							uiChoosenVariable--;
						}
						pVecPosition->setVariable( uiActualElement, (*itrChoosenVariable) );
					}
				}
			}
			//evalue next pointelement
			pPointElement = (cPoint*)(pPointElement->getNextFibElement( 'p' ));
		}
		
		//insert variables into propertyelements
		cProperty * pPropertyElement = (cProperty*)(pMasterRoot->getNextFibElement( 'y' ));
		while ( pPropertyElement != NULL ){
			//evalue possible/ defined variables for the element
			list<cFibVariable*> liDefinedVariables =
				pPropertyElement->getDefinedVariables( ED_HIGHER );
			if ( liDefinedVariables.empty() ){
				//no variables defined for the pointelement -> skip it
				//evalue next pointelement
				pPropertyElement = (cProperty*)(pPropertyElement->getNextFibElement( 'y' ));
				continue;
			}
			//for every element in the propertyvector
			cVectorProperty * pVecProperty = pPropertyElement->getProperty();
			if ( pVecProperty ){
				for ( unsigned int uiActualElement = 1;
						uiActualElement <= pVecProperty->getNumberOfElements();
						uiActualElement++ ){
					
					double dRandom = (double)(rand() % RAND_MAX) / (double)(RAND_MAX);
					if ( dRandom < dFractionsOfUsedVariables ){
						//choos random defined variables and insert it
						unsigned int uiChoosenVariable = rand() % liDefinedVariables.size();
						list<cFibVariable*>::iterator itrChoosenVariable =
							liDefinedVariables.begin();
						while ( uiChoosenVariable != 0){
							itrChoosenVariable++;
							uiChoosenVariable--;
						}
						pVecProperty->setVariable( uiActualElement, (*itrChoosenVariable) );
					}
				}
			}
			//evalue next pointelement
			pPropertyElement = (cProperty*)(pPropertyElement->getNextFibElement( 'y' ));
		}
		//insert variables into area elements
		cArea * pAreaElement = (cArea*)(pMasterRoot->getNextFibElement( 'a' ));
		while ( pAreaElement != NULL ){
			//evalue possible/ defined variables for the element
			list<cFibVariable*> liDefinedVariables =
				pAreaElement->getDefinedVariables( ED_HIGHER );
			if ( liDefinedVariables.empty() ){
				//no variables defined for the area element -> skip it
				//evalue next area element
				pAreaElement = (cArea*)(pAreaElement->getNextFibElement( 'a' ));
				continue;
			}
			//for every subarea
			const unsignedIntFib uiCountSubAreas = pAreaElement->getNumberOfSubareas();
			for ( unsignedIntFib uiActualSubArea = 1;
					uiActualSubArea <= uiCountSubAreas; uiActualSubArea++ ){
				//for every element in the areavector
				cVectorArea * pVecArea = pAreaElement->getSubarea( uiActualSubArea );
				if ( pVecArea ){
					for ( unsigned int uiActualElement = 1;
							uiActualElement <= pVecArea->getNumberOfElements();
							uiActualElement++ ){
						
						double dRandom = (double)(rand() % RAND_MAX) / (double)(RAND_MAX);
						if ( dRandom < dFractionsOfUsedVariables ){
							//choos random defined variables and insert it
							unsigned int uiChoosenVariable = rand() % liDefinedVariables.size();
							list<cFibVariable*>::iterator itrChoosenVariable =
								liDefinedVariables.begin();
							while ( uiChoosenVariable != 0){
								itrChoosenVariable++;
								uiChoosenVariable--;
							}
							pVecArea->setVariable( uiActualElement, (*itrChoosenVariable) );
						}
					}
				}
			}
			//evalue next areatelement
			pAreaElement = (cArea*)(pAreaElement->getNextFibElement( 'a' ));
		}
		//insert variable subfunction (replace some value subfunctions with variables)
		cFunction * pFunctionElement = (cFunction*)(pMasterRoot->getNextFibElement( 'f' ));
		while ( pFunctionElement != NULL ){
			//evalue possible/ defined variables for the element
			DEBUG_OUT_L2(<<"try replacing values with variables of function element "<<pFunctionElement<<" with number "<<flush<<pFunctionElement->getNumberOfElement()<<endl<<flush);
			list<cFibVariable*> liDefinedVariables =
				pFunctionElement->getDefinedVariables( ED_HIGHER );
			if ( liDefinedVariables.empty() ){
				//no variables defined for the function element -> skip it
				//evalue next function element
				pFunctionElement = (cFunction*)(pFunctionElement->getNextFibElement( 'f' ));
				continue;
			}
			//for the subfunction
			cUnderFunction * pUnderFunction = pFunctionElement->getUnderFunction();
			DEBUG_OUT_L2(<<"replacing values with variables of function element "<<pFunctionElement<<" with number "<<flush<<pFunctionElement->getNumberOfElement()<<" and subfunction "<<pUnderFunction<<endl<<flush);
			
			cUnderFunction * pChangedUnderFunction = replaceUnderFunctionValuesWithVariables( pUnderFunction,
				liDefinedVariables, dFractionsOfUsedVariables );
			
			if ( pChangedUnderFunction != NULL ){
				if ( (*pChangedUnderFunction) != (*pUnderFunction) ){
					//replace the subfunction of the function
					pFunctionElement->setUnderFunction( * pChangedUnderFunction );
				}
				delete pChangedUnderFunction;
			}
			//evalue next function element
			pFunctionElement = (cFunction*)(pFunctionElement->getNextFibElement( 'f' ));
		}
		//insert variable subfunctions in conditions (replace some value subfunctions with variables in the condition)
		cIf * pIfElement = (cIf*)(pMasterRoot->getNextFibElement( 'i' ));
		while ( pIfElement != NULL ){
			//evalue possible/ defined variables for the element
			DEBUG_OUT_L2(<<"try replacing values with variables of if-element "<<pIfElement<<" with number "<<flush<<pIfElement->getNumberOfElement()<<endl<<flush);
			list<cFibVariable*> liDefinedVariables =
				pIfElement->getDefinedVariables( ED_HIGHER );
			if ( liDefinedVariables.empty() ){
				//no variables defined for the function element -> skip it
				//evalue next function element
				pIfElement = (cIf*)(pIfElement->getNextFibElement( 'i' ));
				continue;
			}
			//for the subcondition
			cCondition * pCondition = pIfElement->getCondition();
			DEBUG_OUT_L2(<<"replacing values with variables of if-element "<<pIfElement<<" with number "<<flush<<pIfElement->getNumberOfElement()<<" and subcondition "<<pCondition<<endl<<flush);
			
			cCondition * pChangedCondition = replaceConditionValuesWithVariables( pCondition,
				liDefinedVariables, dFractionsOfUsedVariables );
			
			if ( pChangedCondition != NULL ){
				if ( (*pChangedCondition) != (*pCondition) ){
					//replace the subcondition of the function
					pIfElement->setCondition( * pChangedCondition );
				}
				delete pChangedCondition;
			}
			//evalue next function element
			pIfElement = (cIf*)(pIfElement->getNextFibElement( 'i' ));
		}
		//insert variable in set-elements
		cFibSet * pSetElement = (cFibSet*)(pMasterRoot->getNextFibElement( 'v' ));
		while ( pSetElement != NULL ){
			//evalue possible / defined variables for the element
			list<cFibVariable*> liDefinedVariables =
				pSetElement->getDefinedVariables( ED_HIGHER );
			if ( liDefinedVariables.empty() ){
				//no variables defined for the set-element -> skip it
				//evalue next set- element
				pSetElement = (cFibSet*)(pSetElement->getNextFibElement( 'v' ));
				continue;
			}
			//for every vector with to set values
			const unsignedIntFib uiNumberOfSetVectors = pSetElement->getNumberOfVectors();
			for ( unsignedIntFib uiActualVector = 1;
					uiActualVector <= uiNumberOfSetVectors; uiActualVector++ ){
				//for every element in the vector with values to set
				cVectorFibSet * pVecFibSet = pSetElement->getVector( uiActualVector );
				if ( pVecFibSet ){
					for ( unsigned int uiActualElement = 1;
							uiActualElement <= pVecFibSet->getNumberOfElements();
							uiActualElement++ ){
						
						double dRandom = (double)(rand() % RAND_MAX) / (double)(RAND_MAX);
						if ( dRandom < dFractionsOfUsedVariables ){
							//choos random defined variables and insert it
							unsigned int uiChoosenVariable = rand() % liDefinedVariables.size();
							list<cFibVariable*>::iterator itrChoosenVariable =
								liDefinedVariables.begin();
							while ( uiChoosenVariable != 0){
								itrChoosenVariable++;
								uiChoosenVariable--;
							}
							pVecFibSet->setVariable( uiActualElement, (*itrChoosenVariable) );
						}
					}
				}
			}//end for every element in the vector with values to set
			//evalue next set-element
			pSetElement = (cFibSet*)(pSetElement->getNextFibElement( 'v' ));
		}
		//insert variable in matrix elements
		cFibMatrix * pMatrixElement = (cFibMatrix*)(pMasterRoot->getNextFibElement( 'm' ));
		while ( pMatrixElement != NULL ){
			//evalue possible / defined variables for the element
			list<cFibVariable*> liDefinedVariables =
				pMatrixElement->getDefinedVariables( ED_HIGHER );
			if ( liDefinedVariables.empty() ){
				//no variables defined for the matrix element -> skip it
				//evalue next set- element
				pMatrixElement = (cFibMatrix*)(pMatrixElement->getNextFibElement( 'm' ));
				continue;
			}
			//for every area vectors
			const unsignedIntFib uiNumberOfAreas = pMatrixElement->getNumberOfDimensions();
			for ( unsignedIntFib uiActualVector = 1;
					uiActualVector <= uiNumberOfAreas; uiActualVector++ ){
				//for every element in the areavector
				cVectorArea * pVecFibMatrixArea =
					pMatrixElement->getArea( uiActualVector );
				if ( pVecFibMatrixArea ){
					for ( unsigned int uiActualElement = 1;
							uiActualElement <= pVecFibMatrixArea->getNumberOfElements();
							uiActualElement++ ){
						
						double dRandom = (double)(rand() % RAND_MAX) / (double)(RAND_MAX);
						if ( dRandom < dFractionsOfUsedVariables ){
							//choos random defined variables and insert it
							unsigned int uiChoosenVariable =
								rand() % liDefinedVariables.size();
							list<cFibVariable*>::iterator itrChoosenVariable =
								liDefinedVariables.begin();
							while ( uiChoosenVariable != 0){
								itrChoosenVariable++;
								uiChoosenVariable--;
							}
							pVecFibMatrixArea->setVariable( uiActualElement, (*itrChoosenVariable) );
						}
					}
				}
			}//end for every area vectors
			//for every vector with to set values
			const unsignedIntFib uiNumberOfMatrixVectors = pMatrixElement->getNumberOfVectors();
			for ( unsignedIntFib uiActualVector = 1;
					uiActualVector <= uiNumberOfMatrixVectors; uiActualVector++ ){
				//for every element in the areavector
				cVectorFibMatrix * pVecFibMatrixVector = pMatrixElement->getVector( uiActualVector );
				if ( pVecFibMatrixVector ){
					for ( unsigned int uiActualElement = 1;
							uiActualElement <= pVecFibMatrixVector->getNumberOfElements();
							uiActualElement++ ){
						
						double dRandom = (double)(rand() % RAND_MAX) / (double)(RAND_MAX);
						if ( dRandom < dFractionsOfUsedVariables ){
							//choos random defined variables and insert it
							unsigned int uiChoosenVariable = rand() % liDefinedVariables.size();
							list<cFibVariable*>::iterator itrChoosenVariable =
								liDefinedVariables.begin();
							while ( uiChoosenVariable != 0){
								itrChoosenVariable++;
								uiChoosenVariable--;
							}
							pVecFibMatrixVector->setVariable( uiActualElement, (*itrChoosenVariable) );
						}
					}
				}
			}//end for every vector with to set values
			//evalue next matrix element
			pMatrixElement = (cFibMatrix*)(pMatrixElement->getNextFibElement( 'm' ));
		}
		//TODO replace values with variables in more Fib elements
		
		
	}
	
	
	
	DEBUG_OUT_L2(<<"generateFibObject() done"<<endl<<flush);
	
	return pMasterRoot;
}


/**
 * This function generates a Fib object with around uiSize
 * Fib elements.
 * Beware: You have to delete the returned Fib object.
 *
 * @param uiSize a roughly number of Fib elements in the generated Fib objects
 * @param ulMaximalEvaluedPoints a roughly number of points the Fib object
 * 	should evalue to; (this test didn't includes /checks variables, so it
 * 	basicly just works for dFractionsOfUsedVariables = 0.0)
 * @param liFractionOfFibElements the fractions of different
 * 	Fib elementtyps in the generated Fib Object;
 * 	first element of the pair is the char for the type of the
 * 	Fib element (@see getType()), second element is the number for the
 * 	fraction of the Fib element;
 * 	the fractions will be normalized, so that they sum to 1
 * @param liPossiblePropertyTyps the list with the possible propertytyps in the
 * 	generated Fib object
 * @param uiNumberOfDimensions the number of dimensions the Fib object
 * 	should use
 * @param uiAverageSubRoots number of the average sub -root -objects per
 * 	root -element (sub -roots -elements without sub -roots -won't be counted)
 * @param uiAverageSubRootsDepth the average depth of sub -root -elements
 * @param uiNumberOfAverageInputVariables the number of average input
 * 	variables per root -element
 * @param dFractionsOfUsedVariables the fraction of elements of
 * 	vectors, which should be variables
 * @param uiMaxVectorElementNumber the maximal number for a vectorelement,
 * 	the number in vectorelements will vary from 0 till
 * 	uiMaxVectorElementNumber
 * @return the generated Fib object or NULL, if no Fib object could be generated
 */
cFibElement * generateFibObject( unsigned int uiSize, unsigned long ulMaximalEvaluedPoints,
		list< pair< char, double > > liFractionOfFibElements,
		const list< cTypeProperty > & liPossiblePropertyTyps,
		const unsigned int uiNumberOfDimensions = 2,
		const unsigned int uiAverageSubRoots = 2, const unsigned int uiAverageSubRootsDepth = 1,
		const unsigned int uiNumberOfAverageInputVariables = 1,
		const double dFractionsOfUsedVariables = 0.5,
		unsigned int uiMaxVectorElementNumber = 1023 ){
	
	vector<unsigned long> vecDimensions( uiNumberOfDimensions,
		uiMaxVectorElementNumber );
	
	return generateFibObject( uiSize, ulMaximalEvaluedPoints,
		liFractionOfFibElements, liPossiblePropertyTyps,
		vecDimensions, uiAverageSubRoots, uiAverageSubRootsDepth,
		uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
		uiMaxVectorElementNumber );
}


/**
 * This function generates a Fib object with around uiSize
 * Fib elements.
 * You have to delete the returned Fib object.
 *
 * @param uiSize a roughly number of Fib elements in the generated Fib objects
 * @param liFractionOfFibElements the fractions of different
 * 	Fib elementtyps in the generated Fib Object;
 * 	first element of the pair is the char for the type of the
 * 	Fib element (@see getType()), second element is the number for the
 * 	fraction of the Fib element;
 * 	the fractions will be normalized, so that they sum to 1
 * @param liPossiblePropertyTyps the list with the possible propertytyps in the
 * 	generated Fib object
 * @param uiNumberOfDimensions the number of dimensions the Fib object
 * 	should use
 * @param uiAverageSubRoots number of the average sub -root -objects per
 * 	root -element (sub -roots -elements without sub -roots -won't be counted)
 * @param uiAverageSubRootsDepth the average depth of sub -root -elements
 * @param uiNumberOfAverageInputVariables the number of average input
 * 	variables per root -element
 * @param dFractionsOfUsedVariables the fraction of elements of
 * 	vectors, which should be variables
 * @param uiMaxVectorElementNumber the maximal number for a vectorelement,
 * 	the number in vectorelements will vary from 0 till
 * 	uiMaxVectorElementNumber
 * @return the generated Fib object or NULL, if no Fib object could be generated
 */
cFibElement * generateFibObject( unsigned int uiSize,
		list< pair< char, double > > liFractionOfFibElements,
		const list< cTypeProperty > & liPossiblePropertyTyps,
		const unsigned int uiNumberOfDimensions = 2,
		const unsigned int uiAverageSubRoots = 2, const unsigned int uiAverageSubRootsDepth = 1,
		const unsigned int uiNumberOfAverageInputVariables = 1,
		const double dFractionsOfUsedVariables = 0.5,
		unsigned int uiMaxVectorElementNumber = 1023 ){

	return  generateFibObject( uiSize, uiSize * uiSize, liFractionOfFibElements,
		liPossiblePropertyTyps, uiNumberOfDimensions,
		uiAverageSubRoots, uiAverageSubRootsDepth,
		uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
		uiMaxVectorElementNumber);
}

/**
 * This function generates a Fib object with around uiSize
 * Fib elements.
 *
 * @param uiSize a roughly number of Fib elements in the generated Fib objects
 * @return the generated Fib object
 */
cFibElement * generateFibObject( unsigned int uiSize ){
	
	srand( time(NULL) );
	
	const unsigned int uiNumberOfDimensions = 2;
	const unsigned int uiNumberOfPropertyTyps = 2;
	
	const cTypeProperty pPossiblePropertytyps[] = {
		cTypeProperty( 1, uiNumberOfDimensions ),
		cTypeProperty( 2, uiNumberOfDimensions ),
		cTypeProperty( 100, uiNumberOfDimensions ),
		cTypeProperty( 200, uiNumberOfDimensions ),
		cTypeProperty( 300, uiNumberOfDimensions ),
		cTypeProperty( 301, uiNumberOfDimensions ),
		cTypeProperty( 305, uiNumberOfDimensions ),
		cTypeProperty( 310, uiNumberOfDimensions ),
		cTypeProperty( 311, uiNumberOfDimensions ),
		cTypeProperty( 312, uiNumberOfDimensions ),
		cTypeProperty( 400, uiNumberOfDimensions ),
		cTypeProperty( 410, uiNumberOfDimensions ),
		cTypeProperty( 600, uiNumberOfDimensions ),
		//no existing typs
		cTypeProperty( 46, uiNumberOfDimensions ),
		cTypeProperty( 0, uiNumberOfDimensions )
	};
	
	//generate possible propertytyps
	list< cTypeProperty > liPossiblePropertyTyps( pPossiblePropertytyps,
		pPossiblePropertytyps + sizeof( pPossiblePropertytyps ) / sizeof( cTypeProperty ) );
	while ( uiNumberOfPropertyTyps < liPossiblePropertyTyps.size() ){
		//choos random propertytyp and erase it
		unsigned int uiRandom = rand() % liPossiblePropertyTyps.size();
		list< cTypeProperty >::iterator itrChoosenProperty = liPossiblePropertyTyps.begin();
		while ( uiRandom != 0 ){
			uiRandom--;
			itrChoosenProperty++;
		}
		liPossiblePropertyTyps.erase( itrChoosenProperty );
	}

	list< pair< char, double > > liFractionOfFibElements;
	liFractionOfFibElements.push_back( make_pair( 'p', 1.0 ) );
	liFractionOfFibElements.push_back( make_pair( 'y', 1.0 ) );
	liFractionOfFibElements.push_back( make_pair( 'l', 0.5 ) );
	liFractionOfFibElements.push_back( make_pair( 'a', 0.5 ) );
	liFractionOfFibElements.push_back( make_pair( 'f', 0.5 ) );
	liFractionOfFibElements.push_back( make_pair( 'i', 0.2 ) );
	liFractionOfFibElements.push_back( make_pair( 'c', 0.1 ) );
	liFractionOfFibElements.push_back( make_pair( 'o', 0.1 ) );
	liFractionOfFibElements.push_back( make_pair( 's', 0.1 ) );
	liFractionOfFibElements.push_back( make_pair( 'v', 0.1 ) );
	liFractionOfFibElements.push_back( make_pair( 'm', 0.1 ) );
	
	return generateFibObject( uiSize, liFractionOfFibElements, liPossiblePropertyTyps );
}




























