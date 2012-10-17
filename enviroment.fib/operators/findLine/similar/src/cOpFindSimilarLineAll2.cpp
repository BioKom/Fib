/**
 * @file cOpFindSimilarLineAll2
 * file name: cOpFindSimilarLineAll2.cpp
 * @author Betti Oesterholz
 * @date 05.07.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This operator combines all neibourpoints in one dimension with
 * similar properties.
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
 * This operator combines all neibourpoints in one dimension with
 * similar properties.
 * The maximal acceptable difference will be the same for all points.
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
*/


#include "cOpFindSimilarLineAll2.h"

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
#include "cVectorProperty.h"
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


namespace enviroment{
namespace fib{
namespace nOpFindEvenLineAll{
	
	/**
	 * @class funLowerInActualDirection
	 * The functor for sorting the cEvaluePositionList list in an dimension.
	 */
	class funLowerInActualDirection{
	
	private:
		/**
		 * The dimension with the highest priority for sorting.
		 */
		unsignedIntFib uiDimension;
		
	public:
		/**
		 * constructor
		 *
		 * @param uiInDimension the dimension with the highest sorting
		 * 	priority
		 */
		funLowerInActualDirection( const unsignedIntFib uiInDimension ):
				uiDimension( uiInDimension ){
			//nothing to do
		}
		
		
		/**
		 * The lower operator for comparing two cEvaluePositionList list objects.
		 *
		 * @see cEvaluePositionList
		 * @param paPosition1 the first cEvaluePositionList list entry to
		 * 	compare with
		 * @param paPosition2 the second cEvaluePositionList list entry to
		 * 	compare with
		 */
		bool operator()(const pair< cVectorPosition, list< cVectorProperty > > & paPosition1,
				const pair< cVectorPosition, list< cVectorProperty > > & paPosition2 ){
			
			const cVectorPosition & position1 = paPosition1.first;
			const cVectorPosition & position2 = paPosition2.first;
			
			if ( position1.getNumberOfElements() < position2.getNumberOfElements() ){
				return true;
			}
			if ( position2.getNumberOfElements() < position1.getNumberOfElements() ){
				return false;
			}//else (position1.getNumberOfElements() == position2.getNumberOfElements())
			
			const unsignedIntFib uiCountOfVectorElements = position1.getNumberOfElements();
			for ( unsignedIntFib uiActualElement = 1;
					uiActualElement <= uiCountOfVectorElements; uiActualElement++ ){
				
				if ( uiDimension == uiActualElement ){
					continue;
				}
				if ( position1.getValue( uiActualElement ) < position2.getValue( uiActualElement ) ){
					return true;
				}
				if ( position2.getValue( uiActualElement ) < position1.getValue( uiActualElement ) ){
					return false;
				}
			}
			if ( position1.getValue( uiDimension ) < position2.getValue( uiDimension ) ){
				return true;
			}
			if ( position2.getValue( uiDimension ) < position1.getValue( uiDimension ) ){
				return false;
			}
			return false;
		}
		
	};
};//namespace nOpFindEvenLineAll
};//namespace fib
};//namespace enviroment


/**
 * The standardconstructor for the operation.
 * It will create the operation, but won't start it.
 *
 * @param operationId the identifer for the operation
 */
cOpFindSimilarLineAll2::cOpFindSimilarLineAll2( const cOperationIdentifier & operationId ):
		cOperationFib( operationId ){
	//nothing to do
}


/**
 * Destructor of the class cOpFindSimilarLineAll2.
 */
cOpFindSimilarLineAll2::~cOpFindSimilarLineAll2(){
	//nothing to do
}


/**
 * This method creats a new instance of this operator.
 * Beware: You have to delete the instance after usage.
 *
 * @param operationId the identifer for the operation
 * @return a pointer to a new instance of this operation
 */
cOpFindSimilarLineAll2 * cOpFindSimilarLineAll2::createInstance(
		const cOperationIdentifier & operationId ) const{
	
	return new cOpFindSimilarLineAll2( operationId );
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
bool cOpFindSimilarLineAll2::run(){
	
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
	cEvaluePositionList evaluedPositionsData;
	const bool bObjectEvalued = pFibObject->evalueObjectSimple( evaluedPositionsData );
	if ( ( ! bObjectEvalued ) ||
			(evaluedPositionsData.liEvaluedPositionData.size() < 3) ){
		delete pIndividual;
		setIsRunning( false );
		return true;
	}

	//evalue the scalingfactor for the choosen direction
	//evalue the dimensions of the original fib -object
	cDomains validDomains = pFibObject->getValidDomains();

	//evalue the (basic) area to check (the dimensions on which the original is defined)
	cDomain * pDomainDimension = validDomains.getDomainForElement( cTypeDimension() );
	
	doubleFib dScalingFactorInDirection = 1.0;
	
	bool bStandardDimensionDomain = false;
	if ( pDomainDimension == NULL ){
		pDomainDimension = cTypeDimension().getStandardDomain();
		bStandardDimensionDomain = true;
	}
	cDomainVectorBasis * pVecDomainDimension = (cDomainVectorBasis*)pDomainDimension;
	
	//choose direction
	const unsignedIntFib uiNumberOfDimensions = pVecDomainDimension->getNumberOfElements();
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
	
	DEBUG_OUT_L2(<<"uiNumberOfDimensions: "<<uiNumberOfDimensions<<"  uiDirectionDim: "<<uiDirectionDim<<endl<<flush);

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

	//store scaling factor in direction
	const string szDomainElementType = pDirectionDomain->getType();
	if ( ( szDomainElementType.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
				(szDomainElementType.compare( 0, 13, "DomainInteger" ) == 0) ){
		//cDomainIntegerBasis
		dScalingFactorInDirection = abs( ((cDomainIntegerBasis*)
			pDirectionDomain)->getScalingFactor() );
	}
	if ( bStandardDimensionDomain ){
		delete pDomainDimension;
	}
	DEBUG_OUT_L2(<<"scaling factor in direction: "<<dScalingFactorInDirection<<endl<<flush);

	nOpFindEvenLineAll::funLowerInActualDirection lowerInActualDirection( uiDirectionDim );
	//sort evalued points and ther properties
	evaluedPositionsData.liEvaluedPositionData.sort( lowerInActualDirection );
	
	//choose random point
	size_t iChoosenPoint = rand() % evaluedPositionsData.
		liEvaluedPositionData.size();
	
	DEBUG_OUT_L2(<<"choosen point: "<<iChoosenPoint<<endl<<flush);

	list< pair< cVectorPosition, list< cVectorProperty > > >::iterator
		itrPoint = evaluedPositionsData.liEvaluedPositionData.begin();
	for ( ; ( itrPoint != evaluedPositionsData.liEvaluedPositionData.end() ) &&
			( 0 < iChoosenPoint );
			itrPoint++, iChoosenPoint-- ){
		//nothing to do
	}
	itrPoint->second.sort( cVectorProperty::lowerPropertyVector );
	const list< cVectorProperty > liActualProperties = itrPoint->second;
	//the maximal acceptebel difference for the properties
	const list< cVectorProperty > liPropertiesNull;
	doubleFib dMaxDifference = cEvaluePositionList::distanceOfProperties(
		liPropertiesNull, liActualProperties );
	
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
	
	while ( ! evaluedPositionsData.liEvaluedPositionData.empty() ){
		
		/*beginning from the startpoint select all neibours which have the same properties*/
		DEBUG_OUT_L2(<<"evaluing start- and enpoint of the equal property line"<<endl<<flush);
		const doubleFib dStartValue = evaluedPositionsData.
			liEvaluedPositionData.front().first.getValue( uiDirectionDim );
		doubleFib dEndValue = dStartValue;
		const cVectorPosition lastPosition = evaluedPositionsData.
			liEvaluedPositionData.front().first;
		DEBUG_OUT_L2(<<"   startpoint: "<<dStartValue<<endl<<flush);
		
		DEBUG_OUT_L2(<<"   evaluing how long the equal property line is"<<endl<<flush);
		
		evaluedPositionsData.liEvaluedPositionData.pop_front();//skip the startpoint
		while ( ! evaluedPositionsData.liEvaluedPositionData.empty() ){
		
			evaluedPositionsData.liEvaluedPositionData.front().second.sort(
				cVectorProperty::lowerPropertyVector );
			if ( dMaxDifference < cEvaluePositionList::distanceOfProperties(
					liActualProperties,
					evaluedPositionsData.liEvaluedPositionData.front().second ) ){
				
				break;
			}
			
			const doubleFib dNewEndValue = evaluedPositionsData.
				liEvaluedPositionData.front().first.getValue( uiDirectionDim );
			if ( (((doubleFib)1.1) * dScalingFactorInDirection) <
					abs( dEndValue - dNewEndValue ) ){
				break;
			}
			//both points have different properties
			dEndValue = dNewEndValue;
			evaluedPositionsData.liEvaluedPositionData.pop_front();
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
			cPoint * pNewPoint = new cPoint( & lastPosition );
			
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
			cPoint * pNewPoint = new cPoint( & lastPosition );
			
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
		for ( list< cVectorProperty >::const_iterator itrProperty = liActualProperties.begin();
				itrProperty != liActualProperties.end(); itrProperty++ ){
			
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
string cOpFindSimilarLineAll2::getName() const{
	return "cOpFindSimilarLineAll2";
}





