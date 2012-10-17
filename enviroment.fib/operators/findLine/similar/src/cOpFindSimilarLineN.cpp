/**
 * @file cOpFindSimilarLineN
 * file name: cOpFindSimilarLineN.cpp
 * @author Betti Oesterholz
 * @date 05.07.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This operator chooses n random points and combines it with all
 * neibourpoints in an random choosen direction with similar properties.
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
 * This operator chooses s random points and combines it with all
 * neibourpoints in an random choosen direction with similar properties,
 * with the help of an areaelement and if needed an functionelement.
 * (The number n is randomly choosen.)
 * In an last step it removes from the created fib -object all underobjects
 * which point properties are overwritten and so not necessary.
 *
 *
 * @see cOperationFib
 * @see cOperation
 * @see cEnviroment
 */
/*
History:
05.07.2010  Oesterholz  created
01.12.2011  Oesterholz  changes for: cDomainVector has as elements now
	cDomain and not cDomainSingle 
*/


#include "cOpFindSimilarLineN.h"

#include "cEnviroment.h"

#include "cFibIndividual.h"

#include "fibDatatyps.h"
#include "cFibElement.h"
#include "cPoint.h"
#include "cProperty.h"
#include "cList.h"
#include "cArea.h"
#include "cFunction.h"
#include "cFunctionValue.h"
#include "cFunctionVariable.h"
#include "cFunctionTwoValue.h"
#include "cFunctionAdd.h"
#include "cFunctionMult.h"
#include "cEvaluePositionList.h"
#include "cTypeDimension.h"
#include "cDomains.h"
#include "cDomain.h"
#include "cDomainVectorBasis.h"
#include "cDomainIntegerBasis.h"
#include "cDomainSingle.h"

#include "nReduceFibObject.h"

#include <list>
#include <ctime>
#include <cmath>

using namespace std;
using namespace fib::algorithms::nReduceFibObject;
using namespace enviroment;
using namespace enviroment::fib;


/**
 * The standardconstructor for the operation.
 * It will create the operation, but won't start it.
 *
 * @param operationId the identifer for the operation
 */
cOpFindSimilarLineN::cOpFindSimilarLineN( const cOperationIdentifier & operationId ):
		cOperationFib( operationId ){
	//nothing to do
}


/**
 * Destructor of the class cOpFindSimilarLineN.
 */
cOpFindSimilarLineN::~cOpFindSimilarLineN(){
	//nothing to do
}


/**
 * This method creats a new instance of this operator.
 * Beware: You have to delete the instance after usage.
 *
 * @param operationId the identifer for the operation
 * @return a pointer to a new instance of this operation
 */
cOpFindSimilarLineN * cOpFindSimilarLineN::createInstance(
		const cOperationIdentifier & operationId ) const{
	
	return new cOpFindSimilarLineN( operationId );
}


/**
 * This method runs the operation.
 * It will wait till the operation is ended befor returning.
 * Beware: If overwriten call setIsRunning( false ), when the operation
 * is done.
 *
 * @see start()
 * @see stop()
 * @see setIsRunning()
 * @return true if the operation was started
 */
bool cOpFindSimilarLineN::run(){
	
	DEBUG_OUT_L1(<<getName()<<"::run()"<<endl<<flush);
	
	if ( isRunning() || bStop ){
		//the operation runs allready
		return false;
	}
	
	cEnviroment * pEnviroment = cEnviroment::getInstance();
	
	if ( pEnviroment == NULL ){
		//no enviroment for the operation
		return false;
	}
	//check if the individualtype is correct
	if ( pEnviroment->OPERATION_DOMAIN != OPERATION_DOMAIN ){
		//wrong enviromenttype for the operation
		return false;
	}
	setIsRunning( true );
	
	DEBUG_OUT_L1(<<getName()<<"::run()"<<endl<<flush);

	//choose random fib -individual
	cFibIndividual * pIndividual = ((cFibIndividual*)(pEnviroment->getIndividual()));
	if ( pIndividual == NULL ){
		setIsRunning( false );
		return true;
	}
	
	cFibElement * pFibObject = pIndividual->getFibObject();
	if ( pFibObject == NULL ){
		
		delete pIndividual;
		setIsRunning( false );
		return true;
	}
	//evalue the fib -object
	cEvaluePositionList evaluedPositionsDataOriginal;
	const bool bObjectEvalued = pFibObject->evalueObjectSimple( evaluedPositionsDataOriginal );
	if ( ( ! bObjectEvalued ) ||
			evaluedPositionsDataOriginal.liEvaluedPositionData.empty() ){
		delete pIndividual;
		setIsRunning( false );
		return true;
	}
	evaluedPositionsDataOriginal.sortPositionsData();
	const unsigned long ulEvaluedPoints = evaluedPositionsDataOriginal.liEvaluedPositionData.size();
	if ( ulEvaluedPoints < 3 ){
		//no points to combine
		delete pIndividual;
		setIsRunning( false );
		return true;
	}

	//evalue the scalingfactor for the choosen direction
	//evalue the dimensions of the original fib -object
	cDomains validDomains = pFibObject->getValidDomains();

	//evalue the (basic) area to check (the dimensions on which the original is defined)
	cDomain * pDomainDimension = validDomains.getDomainForElement( cTypeDimension() );
	
	unsignedLongFib ulNumberOfLines = 1;
	doubleFib dScalingFactorInDirection = 1.0;
	
	bool bStandardDimensionDomain = false;
	if ( pDomainDimension == NULL ){
		pDomainDimension = cTypeDimension().getStandardDomain();
		bStandardDimensionDomain = true;
	}
	cDomainVectorBasis * pVecDomainDimension = (cDomainVectorBasis*)pDomainDimension;
	
	//choose direction
	const unsignedIntFib uiNumberOfDimensions = pVecDomainDimension->getNumberOfElements();
	const bool bDirectionHigher = ((rand() % 2) == 0);
	if ( uiNumberOfDimensions == 0 ){
		//error
		if ( bStandardDimensionDomain ){
			delete pDomainDimension;
		}
		delete pIndividual;
		setIsRunning( false );
		return true;
	}
	const unsignedIntFib uiDirectionDim = (rand() % uiNumberOfDimensions) + 1;
	
	DEBUG_OUT_L2(<<"uiNumberOfDimensions: "<<uiNumberOfDimensions<<"  uiDirectionDim: "<<uiDirectionDim<<"  bDirectionHigher:"<<bDirectionHigher<<endl<<flush);

	for ( unsignedIntFib uiActualDimension = 1;
			uiActualDimension <= uiNumberOfDimensions; uiActualDimension++ ){
		
		cDomain * pDirectionDomainElement =
			pVecDomainDimension->getElementDomain( uiDirectionDim );
		
		if ( ( pDirectionDomainElement == NULL ) && ( ! pDirectionDomainElement->isScalar() ) ){
			//error
			if ( bStandardDimensionDomain ){
				delete pDomainDimension;
			}
			delete pIndividual;
			setIsRunning( false );
			return true;
		}
		cDomainSingle * pDirectionDomain = ((cDomainSingle*)(pDirectionDomainElement));
		if( uiActualDimension == uiDirectionDim ){
			//store scaling factor in direction
			const string szDomainElementType = pDirectionDomain->getType();
			if ( ( szDomainElementType.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
						(szDomainElementType.compare( 0, 13, "DomainInteger" ) == 0) ){
				//cDomainIntegerBasis
				dScalingFactorInDirection = abs( ((cDomainIntegerBasis*)
					pDirectionDomain)->getScalingFactor() );
			}
			DEBUG_OUT_L2(<<"scaling factor in direction: "<<dScalingFactorInDirection<<endl<<flush);
		}else{//evalue the possible lines
			string szDomainElementType = pDirectionDomain->getType();
			if ( ( szDomainElementType.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
						(szDomainElementType.compare( 0, 13, "DomainInteger" ) == 0) ){
				//cDomainIntegerBasis
				ulNumberOfLines *= 1 +
					(pDirectionDomain->getMaximum() - pDirectionDomain->getMinimum() ) /
					((cDomainIntegerBasis*)pDirectionDomain)->getScalingFactor();
			}else{
				ulNumberOfLines *= 1 +
					( pDirectionDomain->getMaximum() - pDirectionDomain->getMinimum() );
			}
		}
	}
	if ( bStandardDimensionDomain ){
		delete pDomainDimension;
	}

	//choose the lines to evalue
	const unsignedLongFib ulLinesToEvalue = (rand() % ulNumberOfLines) + 2;
	DEBUG_OUT_L2(<<"lines to evalue: "<<ulLinesToEvalue<<"( possible lines: "<<ulNumberOfLines<<" )"<<endl<<flush);
	
	for ( unsignedLongFib ulActualLine = 0; ulActualLine <= ulLinesToEvalue;
			ulActualLine++ ){
		//choose random startpoint
		size_t iChoosenPoint = rand() % ulEvaluedPoints;
		
		DEBUG_OUT_L2(<<"choosen point: "<<iChoosenPoint<<endl<<flush);
	
		list< pair< cVectorPosition, list< cVectorProperty > > >::iterator
			itrPoint = evaluedPositionsDataOriginal.liEvaluedPositionData.begin();
		for ( ; ( itrPoint != evaluedPositionsDataOriginal.liEvaluedPositionData.end() ) &&
				( 0 < iChoosenPoint );
				itrPoint++, iChoosenPoint-- ){
			//nothing to do
		}
		const cVectorPosition choosenPosition( itrPoint->first );
		const list< cVectorProperty > liChoosenProperties = itrPoint->second;
		
		if ( choosenPosition.getNumberOfElements() == 0 ){
			//backgroundpoint choosen
			DEBUG_OUT_L2(<<"backgroundpoint choosen: skipping it"<<endl<<flush);
			continue;
		}
	
		cEvaluePositionList evaluedPositionsData;
		
		/*find all needed points (all points on the same line in the
		choosen direction)*/
		for ( itrPoint = evaluedPositionsDataOriginal.liEvaluedPositionData.begin();
				itrPoint != evaluedPositionsDataOriginal.liEvaluedPositionData.end();
				itrPoint++ ){
			
			if ( itrPoint->first.getNumberOfElements() == 0 ){
				//backgroundpoint is not in line -> skip it
				continue;
			}
			for ( unsignedIntFib uiActualDimension = 1;
					uiActualDimension <= uiNumberOfDimensions; uiActualDimension++ ){
				
				if ( uiActualDimension == uiDirectionDim ){
					
					if ( bDirectionHigher ){
						if ( itrPoint->first.getValue( uiActualDimension ) <
								choosenPosition.getValue( uiActualDimension ) ){
							//point itrPoint in direction lower from choosenPosition
							break;
						}
					}else{//direction lower
						if ( choosenPosition.getValue( uiActualDimension ) <
								itrPoint->first.getValue( uiActualDimension ) ){
							//point itrPoint in direction higher from choosenPosition
							break;
						}
					}
				}else{// ( uiActualDimension != uiDirectionDim )
				
					if ( choosenPosition.getValue( uiActualDimension ) !=
							itrPoint->first.getValue( uiActualDimension ) ){
						//point not in line
						break;
					}
				}
				if ( uiNumberOfDimensions <= uiActualDimension ){
					//point in line -> don't erase this point -> check the next point
					evaluedPositionsData.liEvaluedPositionData.push_back( *itrPoint );
				}
			}
		}
		DEBUG_OUT_L2(<<"Remaining points in line: "<<evaluedPositionsData.liEvaluedPositionData.size() <<endl<<flush);

		if ( evaluedPositionsData.liEvaluedPositionData.size() < 3 ){
			//not enought points
			DEBUG_OUT_L2(<<"not enougth points in line ("<< evaluedPositionsData.liEvaluedPositionData.size()<<" points )"<<endl<<flush);
			continue;
		}
		//sort evalued points and ther properties
		evaluedPositionsData.sortPositionsData();
		if ( ! bDirectionHigher ){
			//change directionitrPoint
			evaluedPositionsData.liEvaluedPositionData.reverse();
		}
		/*now the choosen point is the first in the list and it neibours follow
		in ther order*/
		
		
		/*beginning from the startpoint select all neibours which have the same properties*/
		DEBUG_OUT_L2(<<"evaluing start- and enpoint of the equal property line"<<endl<<flush);
		const doubleFib dStartValue = choosenPosition.getValue( uiDirectionDim );
		doubleFib dEndValue = dStartValue;
		DEBUG_OUT_L2(<<"   startpoint: "<<dStartValue<<endl<<flush);
		
		itrPoint = evaluedPositionsData.liEvaluedPositionData.begin();
		itrPoint++;//skip the startpoint
		
		//the maximal acceptebel difference for the properties
		const list< cVectorProperty > liPropertiesNull;
		doubleFib dMaxDifference = cEvaluePositionList::distanceOfProperties(
			liPropertiesNull, liChoosenProperties );
		
		if ( (rand() % 8) != 0 ){
			dMaxDifference /= 256.0;
		}else{
			if ( (rand() % 8) != 0 ){
				dMaxDifference /= 16.0;
			}//else don't change dMaxDifference
		}
		dMaxDifference = dMaxDifference * ( ((doubleFib)(rand() % 1000)) / 1000.0 );
		if ( dMaxDifference == 0.0 ){
			dMaxDifference = 1.0;
		}
		DEBUG_OUT_L2(<<"maximal acceptebel difference in the properties: "<<dMaxDifference<<endl<<flush);
		
		DEBUG_OUT_L2(<<"   evaluing how long the equal property line is"<<endl<<flush);
		for ( ; itrPoint != evaluedPositionsData.liEvaluedPositionData.end(); itrPoint++ ){
			
//			DEBUG_OUT_L2(<<"   comparing properties "<<endl<<flush);
			if ( dMaxDifference < cEvaluePositionList::distanceOfProperties(
					itrPoint->second, liChoosenProperties ) ){
//				DEBUG_OUT_L2(<<"   properties not equal"<<endl<<flush);
				break;
			}else{
//				DEBUG_OUT_L2(<<"   properties equal"<<endl<<flush);
				const doubleFib dNewEndValue =
					itrPoint->first.getValue( uiDirectionDim );
//				DEBUG_OUT_L2(<<"   checking new endvalue: "<<dNewEndValue<<endl<<flush);
				if ( (((doubleFib)1.1) * dScalingFactorInDirection) <
						abs( dEndValue - dNewEndValue ) ){
					break;
				}
				//both points have different properties
//				DEBUG_OUT_L2(<<"   new endvalue ok: "<<dNewEndValue<<endl<<flush);
				dEndValue = dNewEndValue;
			}
		}
		DEBUG_OUT_L2(<<"dStartValue: "<<dStartValue<<" dEndValue: "<<dEndValue<<endl<<flush);
		
		//if less than two points are selected -> stop evaluation
		if ( ( (abs( dStartValue ) - ((doubleFib)2.5) * dScalingFactorInDirection)) < abs( dEndValue ) &&
				( abs( dEndValue ) < (abs( dStartValue ) + ((doubleFib)2.5) * dScalingFactorInDirection) ) ){
			continue;
		}
		DEBUG_OUT_L2(<<"creating underobject"<<endl<<flush);
		
		/*build an area -point -underobject for the selected points with same properties*/
		cFibElement * pLineFibObject = NULL;
		if ( dScalingFactorInDirection == 1.0 ){
			//don't need rescaling -> yust add area for the line
			cPoint * pNewPoint = new cPoint( & choosenPosition );
			
			cVectorArea vectorArea( roundToLongFib( dStartValue ),
				roundToLongFib( dEndValue ) );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
			cArea * pArea = new cArea( vectorArea, pNewPoint );
#else //FEATURE_SIMPLE_CONSTRUCTOR
			cArea * pArea = new cArea( vectorArea, NULL, NULL, pNewPoint );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
			pNewPoint->getPosition()->setVariable( uiDirectionDim, pArea->getDefinedVariable() );
			pLineFibObject = pArea;
		}else{//scale the value with a function element
			cPoint * pNewPoint = new cPoint( &choosenPosition );
			
			cFunctionMult underFunction( cFunctionValue( dScalingFactorInDirection ),
				cFunctionValue( 1.0 ) );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
			cFunction * pFunction = new cFunction( underFunction, pNewPoint );
#else //FEATURE_SIMPLE_CONSTRUCTOR
			cFunction * pFunction = new cFunction( underFunction, NULL, NULL, pNewPoint );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
			
			cVectorArea vectorArea( roundToLongFib( dStartValue / dScalingFactorInDirection ),
				roundToLongFib( dEndValue / dScalingFactorInDirection ) );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
			cArea * pArea = new cArea( vectorArea, pFunction );
#else //FEATURE_SIMPLE_CONSTRUCTOR
			cArea * pArea = new cArea( vectorArea, NULL, NULL, pFunction );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
			
			pNewPoint->getPosition()->setVariable( uiDirectionDim, pFunction->getDefinedVariable() );
			((cFunctionTwoValue*)( pFunction->getUnderFunction() ))->setSecondUnderFunction(
				cFunctionVariable( pArea->getDefinedVariable() ) );
			
			pLineFibObject = pArea;
		}
		DEBUG_OUT_L2(<<"   adding properties for underobject"<<endl<<flush);
		
		//add the properties
		for ( list< cVectorProperty >::const_iterator itrProperty = liChoosenProperties.begin();
				itrProperty != liChoosenProperties.end(); itrProperty++ ){
			
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
			pLineFibObject = new cProperty( *itrProperty, pLineFibObject );
#else //FEATURE_SIMPLE_CONSTRUCTOR
			pLineFibObject = new cProperty( *itrProperty, NULL, NULL, pLineFibObject );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
		}
		
		//insert the created area -point -underobject as the last underobject
		DEBUG_OUT_L2(<<"inserting underobject"<<endl<<flush);
		
		bool bObjectInserted = false;
		cList * pNextList = ((cList*)( pFibObject->getNextFibElement( 'l' ) ) );
		if ( pNextList ){
			//add line to the end of the founded listelement
			bObjectInserted = pNextList->addUnderobject( pLineFibObject,
				pNextList->getNumberOfUnderobjects() + 1 );
			
		}else{//create listelement as main -fib -object
			bObjectInserted = pFibObject->insertObjectInElement(
				pLineFibObject, 'r', 0, false, true );
		}
		if ( ! bObjectInserted ){
			pLineFibObject->deleteObject();
			delete pIndividual;

			setIsRunning( false );
			
			DEBUG_OUT_L1(<<getName()<<"::run() done generated object could not be inserted"<<endl<<flush);
			return false;
		}
		
	}//end for (ulActualLine)

	//remove from the individual overwritten underobjects
	DEBUG_OUT_L2(<<"removeOverwrittenUnderObjects()"<<endl<<flush);
	removeOverwrittenUnderObjects( *pFibObject );
	
	//if the fib -objects was changed -> insert changed individual into the enviroment
	DEBUG_OUT_L2(<<"inserting indiviual into enviroment"<<endl<<flush);
	list<cIndividualIdentifier> liParents;
	liParents.push_back( pIndividual->getInfo()->getIdentifier() );
	
	const bool bIndividualInserted = insertFibObjectIntoEnviroment(
		pFibObject, liParents );
	
	delete pIndividual;
	setIsRunning( false );
	
	DEBUG_OUT_L1(<<getName()<<"::run() done bIndividualInserted="<<(bIndividualInserted?"true":"false")<<endl<<flush);
	return bIndividualInserted;
}


/**
 * @return the (class-)name of the operation
 */
string cOpFindSimilarLineN::getName() const{
	return "cOpFindSimilarLineN";
}





