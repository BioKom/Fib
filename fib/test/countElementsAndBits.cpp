/**
 * @file countElementsAndBits
 * file name: countElementsAndBits.cpp
 * @author Betti Oesterholz
 * @date 18.02.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This programm evalues the element and bits of a Fib-object.
 *
 * Copyright (C) @c GPL3 2010 Betti Oesterholz
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
 * This programm evalues the element and bits of a Fib-object.
 * It outputs data for every subroot.
 *
 * call: countElementsAndBits FILE
 *
 * parameters:
 * 	FILE
 * 		The file, wher to load the Fib-object from.
 *
 *
 * Fib-elements counted:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
  * 	- cExtSubobject
  * 	- cFibSet
  * 	- cFibMatrix
*/
/*
History:
18.02.2011  Oesterholz  created
28.03.2011  Oesterholz  restoring from binary stream
29.03.2011  Oesterholz  outputing dimension domain values
27.05.2011  Oesterholz  cIf added
25.08.2011  Oesterholz  underarea to subarea
05.10.2011  Oesterholz  cExtObject added and seperate sub roots counts
	(because of differnt domains)
16.11.2011  Oesterholz  cExtSubobject added
03.01.2012  Oesterholz  cArea now uses domain for subarea count
19.01.2012  Oesterholz  cFibSet and cFibMatrix added
23.01.2012  Oesterholz  input values changed to input vector
04.02.2011  Oesterholz  FEATURE_EXT_SUBOBJECT_INPUT_VECTOR implemented:
	the input values are now a vector of values
*/

#include "version.h"

#include "cPoint.h"
#include "cRoot.h"
#include "cList.h"
#include "cArea.h"
#include "cProperty.h"
#include "cFunction.h"
#include "cIf.h"
#include "cComment.h"
#include "cExtObject.h"
#include "cExtSubobject.h"
#include "cFibSet.h"
#include "cFibMatrix.h"

#include "cFunctionValue.h"
#include "cFunctionVariable.h"
#include "cFunctionAbs.h"
#include "cFunctionSin.h"
#include "cFunctionLog.h"
#include "cFunctionArcsin.h"
#include "cFunctionAdd.h"
#include "cFunctionSub.h"
#include "cFunctionMult.h"
#include "cFunctionDiv.h"
#include "cFunctionExp.h"
#include "cFunctionMin.h"
#include "cFunctionMax.h"

#include "cCondition.h"


#include "cDomainNaturalNumberBit.h"
#include "cDomainNaturalNumber.h"
#include "cDomainVector.h"
#include "cTypeVariable.h"
#include "cTypeSubarea.h"
#include "cTypeInVar.h"
#include "cTypeDimension.h"
#include "cTypeExtObject.h"
#include "cTypeExtSubobject.h"

#include "cFibVariable.h"
#include "cVectorProperty.h"
#include "cVectorPosition.h"

#include "cEvaluePositionList.h"
#include "cEvalueFibElementList.h"


#include "tinyxml.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <ostream>
#include <ctime>



using namespace fib;
using namespace std;

//if the valid domains of all root elements should be printed
bool bPrintValidDomains = true;


int main(int argc, char* argv[]){

	
	cout<<endl<<"This programm evalues the element and bits of a Fib-object."<<endl;
	cout<<      "==========================================================="<<endl;
	
	char * pFileFibObject = NULL;
	
	if ( argc < 2 ){
		//no input file -> exit
		cout<<"No inputfile with the Fib-object given."<<endl;
		cout<<endl;
		cout<<" call: countElementsAndBits FILE"<<endl;
		cout<<endl;
		cout<<" parameters:"<<endl;
		cout<<" 	FILE"<<endl;
		cout<<" 		The file, wher to load the Fib-object from."<<endl;
		return 1;
	}
	pFileFibObject = argv[1];
	

	//load the multimediadata
	cFibElement * pRestoredFibObject = NULL;
	intFib outStatus = 0;
	
	if ( strcmp( & (pFileFibObject[
			strlen( pFileFibObject ) - 4 ]), ".xml") == 0 ){
		//restore to file in xml -format
		ifstream inFile( pFileFibObject );
		pRestoredFibObject = cFibElement::restoreXml( inFile , &outStatus );
		
		if ( outStatus == 0 ){
			cout<<"Restoring Fib object in the Xml-format from the file \""<<
				pFileFibObject <<"\" successfull. "<<endl;
		}else{
			cerr<<"Restoring Fib object in the Xml-format from the file \""<<
				pFileFibObject <<"\" not successfull. (return status="<< outStatus <<")"<<endl;
			return 1;
		}
	}else{//restore to file in compressedformat
		ifstream inFile( pFileFibObject, ios_base::in | ios_base::binary );
		pRestoredFibObject = cFibElement::restore( inFile , &outStatus );
		
		if ( outStatus == 0 ){
			cout<<"Restoring Fib object in the compressed format from the file \""<<
				pFileFibObject <<"\" successfull. "<<endl;
		}else{
			cerr<<"Restoring Fib object in the compressed format from the file \""<<
				pFileFibObject <<"\" not successfull. (return status="<< outStatus <<")"<<endl;
			return 1;
		}
	}
	if ( pRestoredFibObject == NULL ){
		cerr<<"Restoring Fib object from the file \""<<
			pFileFibObject <<"\" not successfull. (return status="<< outStatus <<")"<<endl;
		return 2;
	}
	
	
	//count elements
	const unsignedLongFib uiNumberOfAllElements = pRestoredFibObject->getNumberOfElements();
	const unsignedLongFib uiBitsFibObject = pRestoredFibObject->getCompressedSize();
	
	//count the elements
	unsignedLongFib uiNumberOfRoots = 0;
//	unsignedLongFib uiBitsForRoots = 0;//TODO bits for root elements??
	
	unsignedLongFib uiNumberOfPoints = 0;
	unsignedLongFib uiBitsForPoints = 0;
	
	unsignedLongFib uiNumberOfPositionVectors = 0;
	unsignedLongFib uiBitsForPositionVector = 0;
	
	unsignedLongFib uiNumberOfProperties = 0;
	unsignedLongFib uiBitsForProperties = 0;
	
	unsignedLongFib uiNumberOfPropertyVectors = 0;
	unsignedLongFib uiBitsForPropertyVector = 0;
	
	unsignedLongFib uiNumberOfAreas = 0;
	unsignedLongFib uiBitsForAreas = 0;
	
	unsignedLongFib uiNumberOfFunctions = 0;
	unsignedLongFib uiBitsForFunctions  = 0;
	
	unsignedLongFib uiNumberOfSubfunctions = 0;
	unsignedLongFib uiBitsForSubfunctions = 0;
	
	unsignedLongFib uiNumberOfLists = 0;
	unsignedLongFib uiBitsForLists  = 0;
	
	unsignedLongFib uiNumberOfIfs = 0;
	unsignedLongFib uiBitsForIfs  = 0;
	
	unsignedLongFib uiNumberOfConditions = 0;
	unsignedLongFib uiBitsForConditions = 0;
	
	unsignedLongFib uiNumberOfExtObjects = 0;
	unsignedLongFib uiBitsForExtObjects = 0;
	
	unsignedLongFib uiNumberOfExtSubobjects = 0;
	unsignedLongFib uiBitsForExtSubobjects = 0;
	
	unsignedLongFib uiNumberOfFibSets = 0;
	unsignedLongFib uiBitsForFibSets = 0;
	
	unsignedLongFib uiNumberOfFibMatrixs = 0;
	unsignedLongFib uiBitsForFibMatrixs = 0;
	
	unsignedLongFib uiNumberOfComments = 0;
	//TODO bits for comment elements??
	
	for ( cFibElement * pActualFibElement = pRestoredFibObject;
			pActualFibElement != NULL;
			pActualFibElement = pActualFibElement->getNextFibElement() ){
	
		//for all root elements
		
		//evalue the bits to store a property
		cProperty * pPropertyElement = ((cProperty*)(
			pActualFibElement->getNextFibElement( 'y' )) );
		
		const unsignedLongFib ulBitsForPropertyElements = (pPropertyElement == NULL)? 0:
			(pPropertyElement->getCompressedSize() -
			pPropertyElement->getNextFibElement()->getCompressedSize() -
			pPropertyElement->getProperty()->getCompressedSize());
		
		//evalue bits for variablea
		//get the domain for the variables in this vector
		cTypeVariable typeVariable;
		/*get the value domain for variables*/
		cDomains validDomains = pActualFibElement->getValidValueDomains();
		//return the variable domain
		cDomainSingle * pVariableDomain = (cDomainSingle*)
			validDomains.getDomainForElement( typeVariable );
		const bool bStandardVariableDomainUsed = (pVariableDomain == NULL);
		if ( bStandardVariableDomainUsed ){
			//use the standard domain
			pVariableDomain = (cDomainSingle*)typeVariable.getStandardDomain();
		}
#ifndef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
		//TODO: comment in if needed for variables
		const unsignedLongFib ulBitsForVariables =
			pVariableDomain->getCompressedSizeForValue();
		if ( bStandardVariableDomainUsed ){
			delete pVariableDomain;
		}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
		
		//output multimediaobject dimensions
		cTypeDimension typeDimension;
		cDomain * pDomainDimension = validDomains.getDomainForElement( typeDimension );
		
		if ( pDomainDimension == NULL ){
			cerr<<"Error: No dimension domain."<<endl;;
		}else{
			cDomainVectorBasis * pVecDomainDimension = (cDomainVectorBasis*)pDomainDimension;
			
			const unsigned long ulNumberOfDimensions =
				pVecDomainDimension->getNumberOfElements();
			
			unsigned long long ulPossiblePoints = 1;
			
			for ( unsigned long ulActualDimension = 1; ulActualDimension <= ulNumberOfDimensions;
					ulActualDimension++ ){
				cDomainSingle * pDirectionDomain = ((cDomainSingle*)(
					pVecDomainDimension->getElementDomain( ulActualDimension )));
				
				const doubleFib dDirectionMinimum = pDirectionDomain->getMinimum();
				const doubleFib dDirectionMaximum = pDirectionDomain->getMaximum();
				doubleFib dDirectionScaling = 1.0;
				string szDomainElementType = pDirectionDomain->getType();
				if ( ( szDomainElementType.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
							(szDomainElementType.compare( 0, 13, "DomainInteger" ) == 0) ){
					//cDomainIntegerBasis
					dDirectionScaling = ((cDomainIntegerBasis*)pDirectionDomain)->getScalingFactor();
				}
				
				const unsigned long ulWidth = (unsigned long)(
					(dDirectionMaximum - dDirectionMinimum) / dDirectionScaling);
				if ( pActualFibElement == pRestoredFibObject ){
					//print for master root
					//get mapping
					const string szDimensionMappingName =
						typeDimension.getDimensionMappingName(
							pRestoredFibObject->getDimensionMapping( ulActualDimension ) );
					
					cout<<"Dimension "<<ulActualDimension<<" in direction "<<szDimensionMappingName<<
						" has number of values "<<ulWidth<<
						" (min value "<<dDirectionMinimum<<" max value "<<dDirectionMaximum<<
						" and scaling factor "<<dDirectionScaling<<")"<<endl;
				}
				ulPossiblePoints *= ulWidth;
			}
			if ( pActualFibElement == pRestoredFibObject ){
				//print for master root
				cout<<"possible points in whool multimediaobject: "<<ulPossiblePoints<<endl<<endl;
			}
		}
		//return the cExtObject domain
		cTypeExtObject typeExtObject;
		cDomainVectorBasis * pExtObjDomain = (cDomainVectorBasis*)
			validDomains.getDomainForElement( typeExtObject );
		const bool bStandardExtObjDomainUsed = (pExtObjDomain == NULL);
		if ( bStandardExtObjDomainUsed ){
			//use the standard domain
			pExtObjDomain = (cDomainVectorBasis*)typeExtObject.getStandardDomain();
		}
		
		//evalue bits for identifier, count of input variables and count of subobjects of cExtObject
		const unsignedLongFib uiExtObjectIdCountSubObjInVarBits =
			( 3 <= pExtObjDomain->getNumberOfElements() )?
			(	(((cDomainSingle*)(pExtObjDomain->getElementDomain( 1 )))->getCompressedSizeForValue()) +
				(((cDomainSingle*)(pExtObjDomain->getElementDomain( 2 )))->getCompressedSizeForValue()) +
				(((cDomainSingle*)(pExtObjDomain->getElementDomain( 3 )))->getCompressedSizeForValue())
			):0;
		//evalue bits for counts of output variables of cExtObject
		const unsignedLongFib ulBitsForOutVarCount = (pExtObjDomain->getElementDomain( 4 ) != NULL )?
			(((cDomainSingle*)(pExtObjDomain->getElementDomain( 4 )))->getCompressedSizeForValue()):0;
		if ( bStandardExtObjDomainUsed ){
			delete pExtObjDomain;
		}
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
		//get the domain for the external subobject number
		cDomainNaturalNumber * pDomainNumberOfSubobjects;
		if ( pActualFibElement->getType() == 'r' ){
			//actual Fib element is an root element
			pDomainNumberOfSubobjects = new cDomainNaturalNumber(
				((cRoot*)(pActualFibElement))->getNumberOfExternSubobjects() );
		}else{
			pDomainNumberOfSubobjects = new cDomainNaturalNumber(
				(pActualFibElement->getSuperiorRootElement())->
					getNumberOfExternSubobjects() );
		}
		//evalue bits for counts of output variables of cExtSubobject
		const unsignedLongFib ulBitsForExtSubobjCounts =
			pDomainNumberOfSubobjects->getCompressedSizeForValue();
		delete pDomainNumberOfSubobjects;
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
		//return the cExtSubobject domain
		cTypeExtSubobject typeExtSubobject;
		cDomainIntegerBasis * pExtSubobjDomain = (cDomainIntegerBasis*)
			validDomains.getDomainForElement( typeExtSubobject );
		const bool bStandardExtSubobjDomainUsed = (pExtSubobjDomain == NULL);
		if ( bStandardExtSubobjDomainUsed ){
			//use the standard domain
			pExtSubobjDomain = (cDomainIntegerBasis*)typeExtSubobject.getStandardDomain();
		}
		//get the domain for the external subobject number
		cDomainNaturalNumber * pDomainNumberOfSubobjects;
		if ( pActualFibElement->getType() == 'r' ){
			//actual Fib element is an root element
			pDomainNumberOfSubobjects = new cDomainNaturalNumber(
				((cRoot*)(pActualFibElement))->getNumberOfExternSubobjects() );
		}else{
			pDomainNumberOfSubobjects = new cDomainNaturalNumber(
				(pActualFibElement->getSuperiorRootElement())->
					getNumberOfExternSubobjects() );
		}
		//evalue bits for counts of output variables of cExtSubobject
		const unsignedLongFib ulBitsForExtSubobjCounts =
			(pExtSubobjDomain->getCompressedSizeForValue()) +
			pDomainNumberOfSubobjects->getCompressedSizeForValue();
		if ( bStandardExtSubobjDomainUsed ){
			delete pExtSubobjDomain;
		}
		delete pDomainNumberOfSubobjects;
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
		
		for ( ; pActualFibElement != NULL;
				pActualFibElement = pActualFibElement->getNextFibElement() ){
			
			const char cTypeOfActualElement = pActualFibElement->getType();
			
			if ( cTypeOfActualElement == 'r' ){
				//root-element
				uiNumberOfRoots++;
				break;//stop at every root element
			}//else
			switch ( cTypeOfActualElement ){
				case 'p':{//point element
					uiNumberOfPoints++;
					
					const cVectorPosition * pVecPosition =
						((cPoint*)(pActualFibElement))->getPosition();
					
					if ( pVecPosition == NULL ){
						//no position vector
						uiBitsForPoints += 5;
					}else if ( pVecPosition->getNumberOfElements() == 0 ){
						//background position
						uiBitsForPoints += 5;
					}else{//normal position
						uiNumberOfPositionVectors++;
						const unsignedLongFib ulVectorBits =
							pVecPosition->getCompressedSize();
						uiBitsForPositionVector += ulVectorBits;
						uiBitsForPoints += 4 + ulVectorBits;
					}
				}break;
				case 'y':{//property element
					uiNumberOfProperties++ ;
					uiBitsForProperties += ulBitsForPropertyElements;
					
					const cVectorProperty * pVecProperty =
						((cProperty*)(pActualFibElement))->getProperty();
					uiNumberOfPropertyVectors++;
					const unsignedLongFib ulVectorBits =
						pVecProperty->getCompressedSize();
					uiBitsForPropertyVector += ulVectorBits;
					uiBitsForProperties += ulVectorBits;
				}break;
				case 'a':{//area element
					uiNumberOfAreas++;
					//TODO? getCompressedSize() (area - its subobject) to slow?
					uiBitsForAreas += pActualFibElement->getCompressedSize();
					if ( pActualFibElement->hasUnderAllObjects() ){
						
						uiBitsForAreas -= pActualFibElement->getNextFibElement()->
							getCompressedSize();
					}
				}break;
				case 'f':{//function element
					uiNumberOfFunctions++ ;
					uiBitsForFunctions += 4;
					
					const cUnderFunction * pSubfunction =
						((cFunction*)(pActualFibElement))->getUnderFunction();
					uiNumberOfSubfunctions++;
					const unsignedLongFib ulActualSubfunctionBits =
						pSubfunction->getCompressedSize();
					uiBitsForSubfunctions += ulActualSubfunctionBits;
					uiBitsForFunctions += ulActualSubfunctionBits;
				}break;
				case 'c':{//comment element
					uiNumberOfComments++;
				}break;
				case 'l':{//list element
					uiNumberOfLists++;
					uiBitsForLists += 4;
					const unsignedIntFib uiNumberOfSubObjects =
						((cList*)(pActualFibElement))->getNumberOfUnderobjects();
					if ( uiNumberOfSubObjects == 1 ){
						//add nothing
					}else if ( uiNumberOfSubObjects < 256 ){
						//4 bit counter
						uiBitsForLists += 8;
					}else{
						//64 bit counter
						uiBitsForLists += 64;
					}
				}break;
				case 'i':{//if-element
					uiNumberOfIfs++;
					uiBitsForIfs += 4;
					const cCondition * pCondition =
						((cIf*)(pActualFibElement))->getCondition();
					uiNumberOfConditions++;
					const unsignedLongFib ulActualConditionBits =
						pCondition->getCompressedSize();
					uiBitsForConditions += ulActualConditionBits;
					uiBitsForIfs += ulActualConditionBits;
				}break;
				case 'o':{//external object element
					uiNumberOfExtObjects++;
					cExtObject * pActualExtObject = ((cExtObject*)(pActualFibElement));
					//add bits for identifier, count of subobjects and count of input variables
					uiBitsForExtObjects += 4 + uiExtObjectIdCountSubObjInVarBits;
					//add bits for input values
					uiBitsForExtObjects +=
						pActualExtObject->getInputVector()->getCompressedSize();
					//add bits for counts of output variables
					uiBitsForExtObjects += ulBitsForOutVarCount *
						pActualExtObject->getNumberOfSubobjects();
					
				}break;
				case 's':{//external subobject element
					uiNumberOfExtSubobjects++;
					cExtSubobject * pActualExtSubobject = ((cExtSubobject*)(pActualFibElement));
					//add bits for identifier, count of subobjects and count of input variables
					uiBitsForExtSubobjects += 4 + ulBitsForExtSubobjCounts;
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
					//add bits for output values
					uiBitsForExtObjects +=
						pActualExtSubobject->getOutputVector()->getCompressedSize();
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
					//add bits for input variables
					uiBitsForExtSubobjects += ulBitsForVariables *
						pActualExtSubobject->getNumberOfOutputVariables();
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
				}break;
				case 'v':{//set-element
					uiNumberOfFibSets++;
					//TODO? getCompressedSize() (set-element - its subobject) to slow?
					uiBitsForFibSets += pActualFibElement->getCompressedSize();
					if ( pActualFibElement->hasUnderAllObjects() ){
						
						uiBitsForFibSets -= pActualFibElement->getNextFibElement()->
							getCompressedSize();
					}
				}break;
				case 'm':{//matrix element
					uiNumberOfFibMatrixs++;
					//TODO? getCompressedSize() (matrix element - its subobject) to slow?
					uiBitsForFibMatrixs += pActualFibElement->getCompressedSize();
					if ( pActualFibElement->hasUnderAllObjects() ){
						
						uiBitsForFibMatrixs -= pActualFibElement->getNextFibElement()->
							getCompressedSize();
					}
				}break;
				
	//TODO more elements
			}
			
		}
		
		if ( bPrintValidDomains ){
			//print the domains
			cout<<endl<<"valid domains for "<<uiNumberOfRoots<<"'st root:"<<endl;
			validDomains.storeXml( cout );
			cout<<endl<<endl;
		}
		if ( pActualFibElement == NULL ){
			break;
		}
	}//end for all roots
	
	const unsignedIntFib BITS_PER_KILOBYTE = 8 * 1024;
	
	cout.width(20);
	cout<<right;
	
	cout<<"Element          ;Number of elements  ; Bit sum for elements; Byte sum for elements; Kilo byte sum for elements"<<endl;
	cout<<"all              ;";
	cout.width(20);
	cout<<uiNumberOfAllElements<<"; ";
	cout.width(20);
	cout<<uiBitsFibObject<<"; ";
	cout.width(20);
	cout<<(uiBitsFibObject / 8);
	cout.width(20);
	cout<<(uiBitsFibObject / BITS_PER_KILOBYTE)<<endl;
	
	cout<<"roots            ;";
	cout.width(20);
	cout<<uiNumberOfRoots<<"; ";
	cout.width(20);
	cout<<"???"<<"; ";
	cout.width(20);
	cout<<"???";
	cout.width(20);
	cout<<"???"<<endl;
	
	cout<<"point elements   ;";
	cout.width(20);
	cout<<uiNumberOfPoints<<"; ";
	cout.width(20);
	cout<<uiBitsForPoints<<"; ";
	cout.width(20);
	cout<<(uiBitsForPoints / 8);
	cout.width(20);
	cout<<(uiBitsForPoints / BITS_PER_KILOBYTE)<<endl;
	
	cout<<"position vectors ;";
	cout.width(20);
	cout<<uiNumberOfPositionVectors<<"; ";
	cout.width(20);
	cout<<uiBitsForPositionVector<<"; ";
	cout.width(20);
	cout<<(uiBitsForPositionVector / 8);
	cout.width(20);
	cout<<(uiBitsForPositionVector / BITS_PER_KILOBYTE)<<endl;
	
	cout<<"properties       ;";
	cout.width(20);
	cout<<uiNumberOfProperties<<"; ";
	cout.width(20);
	cout<<uiBitsForProperties<<"; ";
	cout.width(20);
	cout<<(uiBitsForProperties / 8);
	cout.width(20);
	cout<<(uiBitsForProperties / BITS_PER_KILOBYTE)<<endl;
	
	cout<<"property vectors ;";
	cout.width(20);
	cout<<uiNumberOfPropertyVectors<<"; ";
	cout.width(20);
	cout<<uiBitsForPropertyVector<<"; ";
	cout.width(20);
	cout<<(uiBitsForPropertyVector / 8);
	cout.width(20);
	cout<<(uiBitsForPropertyVector / BITS_PER_KILOBYTE)<<endl;
	
	cout<<"area elements    ;";
	cout.width(20);
	cout<<uiNumberOfAreas<<"; ";
	cout.width(20);
	cout<<uiBitsForAreas<<"; ";
	cout.width(20);
	cout<<(uiBitsForAreas / 8);
	cout.width(20);
	cout<<(uiBitsForAreas / BITS_PER_KILOBYTE)<<endl;
	
	cout<<"functions        ;";
	cout.width(20);
	cout<<uiNumberOfFunctions<<"; ";
	cout.width(20);
	cout<<uiBitsForFunctions<<"; ";
	cout.width(20);
	cout<<(uiBitsForFunctions / 8);
	cout.width(20);
	cout<<(uiBitsForFunctions / BITS_PER_KILOBYTE)<<endl;
	
	cout<<"under functions  ;";
	cout.width(20);
	cout<<uiNumberOfSubfunctions<<"; ";
	cout.width(20);
	cout<<uiBitsForSubfunctions<<"; ";
	cout.width(20);
	cout<<(uiBitsForSubfunctions / 8);
	cout.width(20);
	cout<<(uiBitsForSubfunctions / BITS_PER_KILOBYTE)<<endl;
	
	cout<<"list elements    ;";
	cout.width(20);
	cout<<uiNumberOfLists<<"; ";
	cout.width(20);
	cout<<uiBitsForLists<<"; ";
	cout.width(20);
	cout<<(uiBitsForLists / 8);
	cout.width(20);
	cout<<(uiBitsForLists / BITS_PER_KILOBYTE)<<endl;

	cout<<"if-elements      ;";
	cout.width(20);
	cout<<uiNumberOfIfs<<"; ";
	cout.width(20);
	cout<<uiBitsForIfs<<"; ";
	cout.width(20);
	cout<<(uiBitsForIfs / 8);
	cout.width(20);
	cout<<(uiBitsForIfs / BITS_PER_KILOBYTE)<<endl;
	
	cout<<"conditions       ;";
	cout.width(20);
	cout<<uiNumberOfConditions<<"; ";
	cout.width(20);
	cout<<uiBitsForConditions<<"; ";
	cout.width(20);
	cout<<(uiBitsForConditions / 8);
	cout.width(20);
	cout<<(uiBitsForConditions / BITS_PER_KILOBYTE)<<endl;
	
	cout<<"external objects ;";
	cout.width(20);
	cout<<uiNumberOfExtObjects<<"; ";
	cout.width(20);
	cout<<uiBitsForExtObjects<<"; ";
	cout.width(20);
	cout<<(uiBitsForExtObjects / 8);
	cout.width(20);
	cout<<(uiBitsForExtObjects / BITS_PER_KILOBYTE)<<endl;
	
	cout<<"external subobj. ;";
	cout.width(20);
	cout<<uiNumberOfExtSubobjects<<"; ";
	cout.width(20);
	cout<<uiBitsForExtSubobjects<<"; ";
	cout.width(20);
	cout<<(uiBitsForExtSubobjects / 8);
	cout.width(20);
	cout<<(uiBitsForExtSubobjects / BITS_PER_KILOBYTE)<<endl;
	
	cout<<"set-elements     ;";
	cout.width(20);
	cout<<uiNumberOfFibSets<<"; ";
	cout.width(20);
	cout<<uiBitsForFibSets<<"; ";
	cout.width(20);
	cout<<(uiBitsForFibSets / 8);
	cout.width(20);
	cout<<(uiBitsForFibSets / BITS_PER_KILOBYTE)<<endl;
	
	cout<<"matrix elements  ;";
	cout.width(20);
	cout<<uiNumberOfFibMatrixs<<"; ";
	cout.width(20);
	cout<<uiBitsForFibMatrixs<<"; ";
	cout.width(20);
	cout<<(uiBitsForFibMatrixs / 8);
	cout.width(20);
	cout<<(uiBitsForFibMatrixs / BITS_PER_KILOBYTE)<<endl;
	
	cout<<"comments elements;";
	cout.width(20);
	cout<<uiNumberOfComments<<"; ";
	cout.width(20);
	cout<<"???"<<"; ";
	cout.width(20);
	cout<<"???";
	cout.width(20);
	cout<<"???"<<endl;
	
	cout<<endl<<"The bits and byts for the elements are given without contained Fib-objects, but with contained vectors."<<endl;
	
	
	pRestoredFibObject->deleteObject();

	return 0;
}








