/**
 * @file cOp2DFibFindSimilarAreaNOrg
 * file name: cOp2DFibFindSimilarAreaNOrg.h
 * @author Betti Oesterholz
 * @date 16.09.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This Operator evalues the areas with the same properties and combines
 * n to an complex fib -underobject.
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
 * Evalues the areas with the same properties in the original fib -object
 * and combines n random to an complex fib -underobject.
 * This is done with the help of area- and functionelements.
 * In an last step it removes from the created fib -object all underobjects
 * which point properties are overwritten and so not necessary.
 * The number n is random choosen betwean 1 and log( Datapoints ) .
 * Smaler numbers will be prevered.
 *
 * @see cOperationFib
 * @see cOperation
 * @see cEnviroment
 */
/*
History:
16.09.2010  Oesterholz  created
01.12.2011  Oesterholz  changes for: cDomainVector has as elements now
	cDomain and not cDomainSingle 
*/


#include "cOp2DFibFindSimilarAreaNOrg.h"

#include "cEnviroment.h"
#include "cObjectFitnessAlgorithm.h"
#include "cFibObjectFitnessAlgorithm.h"

#include "cFibIndividual.h"

#include "fibDatatyps.h"
#include "cFibElement.h"
#include "cPoint.h"
#include "cProperty.h"
#include "cList.h"
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

#include "cMatrix2D.h"
#include "nReduceFibObject.h"
#include "../nD1/incl/cDataPoint.h"
#include "nD2.h"

#include <list>
#include <ctime>
#include <cmath>

using namespace std;
using namespace fib::algorithms::nReduceFibObject;
using namespace fib::algorithms;
using namespace enviroment;
using namespace enviroment::fib;




/**
 * The standardconstructor for the operation.
 * It will create the operation, but won't start it.
 *
 * @param operationId the identifer for the operation
 */
cOp2DFibFindSimilarAreaNOrg::cOp2DFibFindSimilarAreaNOrg( const cOperationIdentifier & operationId ):
		cOperationFib( operationId ){
	//nothing to do
}


/**
 * Destructor of the class cOp2DFibFindSimilarAreaNOrg.
 */
cOp2DFibFindSimilarAreaNOrg::~cOp2DFibFindSimilarAreaNOrg(){
	//nothing to do
}


/**
 * This method creats a new instance of this operator.
 * Beware: You have to delete the instance after usage.
 *
 * @param operationId the identifer for the operation
 * @return a pointer to a new instance of this operation
 */
cOp2DFibFindSimilarAreaNOrg * cOp2DFibFindSimilarAreaNOrg::createInstance(
		const cOperationIdentifier & operationId ) const{
	
	return new cOp2DFibFindSimilarAreaNOrg( operationId );
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
bool cOp2DFibFindSimilarAreaNOrg::run(){
	
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

	//get the original individual
	const cObjectFitnessAlgorithm * pFitnessAlgorithm =
		pEnviroment->getFitnessAlgorithm();
	
	if ( pFitnessAlgorithm == NULL ){
		//can't run
		setIsRunning( false );
		return false;
	}
	if ( pFitnessAlgorithm->getClassName().compare( 0, 17, "cFibObjectFitness" ) != 0 ){
		//can't run -> not an fib -enviroment
		setIsRunning( false );
		return false;
	}
	const cFibIndividual * pOriginalIndividual = ((cFibObjectFitnessAlgorithm*)(
		pFitnessAlgorithm))->getOriginalIndividual();
	
	if ( pOriginalIndividual == NULL ){
		//can't run -> not original individual
		setIsRunning( false );
		return false;
	}
	const cFibElement * pOriginalFibObject = pOriginalIndividual->getFibObject();
	if ( pOriginalFibObject == NULL ){
		
		setIsRunning( false );
		return true;
	}
	DEBUG_OUT_L2(<<"uiNumberOfDimensions: "<< pOriginalFibObject->getNumberOfDimensions() <<endl<<flush);
	if ( pOriginalFibObject->getNumberOfDimensions() != 2 ){
		//if the fib -object is not 2 dimensional -> return
		setIsRunning( false );
		return true;
	}

	DEBUG_OUT_L2(<<"get the evalued original fib -object"<<endl<<flush);
	
	const cEvaluePositionList * pOrginalPositionsData = ((cFibObjectFitnessAlgorithm*)(
		pFitnessAlgorithm))->getOriginalPositionList();
	
	if ( pOrginalPositionsData == NULL ){
		setIsRunning( false );
		return true;
	}
	const unsignedLongFib ulNumberOfPoints = pOrginalPositionsData->liEvaluedPositionData.size();
	if ( ulNumberOfPoints < 3 ){
		//no points to combine
		setIsRunning( false );
		return true;
	}

	//evalue the values for the dimensions
	cDomains validDomains = pOriginalFibObject->getValidDomains();
	cDomain * pDomainDimension = validDomains.getDomainForElement( cTypeDimension() );
	
	doubleFib dDim1ScalingFactor = 1.0;
	doubleFib dDim2ScalingFactor = 1.0;
	unsignedLongFib ulDim1Min = 1;
	unsignedLongFib ulDim2Min = 1;
	unsignedLongFib ulDim1Max = 1;
	unsignedLongFib ulDim2Max = 1;
	
	bool bStandardDimensionDomain = false;
	if ( pDomainDimension == NULL ){
		pDomainDimension = cTypeDimension().getStandardDomain();
		bStandardDimensionDomain = true;
	}
	cDomainVectorBasis * pVecDomainDimension = (cDomainVectorBasis*)pDomainDimension;
	

	cDomain * pDirectionDomainElement =
		pVecDomainDimension->getElementDomain( 1 );
	
	if ( ( pDirectionDomainElement == NULL ) && ( ! pDirectionDomainElement->isScalar() ) ){
		//error
		if ( bStandardDimensionDomain ){
			delete pDomainDimension;
		}
		setIsRunning( false );
		return true;
	}
	cDomainSingle * pDirectionDomain = ((cDomainSingle*)(pDirectionDomainElement));
	//store scaling factor in direction
	const string szDomainElementType1 = pDirectionDomain->getType();
	if ( ( szDomainElementType1.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
				(szDomainElementType1.compare( 0, 13, "DomainInteger" ) == 0) ){
		//cDomainIntegerBasis
		cDomainIntegerBasis * pDomInteger = (cDomainIntegerBasis*)pDirectionDomain;
		dDim1ScalingFactor = abs( pDomInteger->getScalingFactor() );
		ulDim1Min = pDomInteger->getMinimumUnscaled();
		ulDim1Max = pDomInteger->getMaximumUnscaled();
	}else{
		//can't work with not int domain
		if ( bStandardDimensionDomain ){
			delete pDomainDimension;
		}
		setIsRunning( false );
		return true;
	}
	DEBUG_OUT_L2(<<"direction 1: min: "<<ulDim1Min<<" max: "<<ulDim1Max<<" scaling factor: "<<dDim1ScalingFactor<<endl<<flush);
	
	pDirectionDomainElement = pVecDomainDimension->getElementDomain( 2 );
	
	if ( ( pDirectionDomainElement == NULL ) && ( ! pDirectionDomainElement->isScalar() ) ){
		//error
		if ( bStandardDimensionDomain ){
			delete pDomainDimension;
		}
		setIsRunning( false );
		return true;
	}
	pDirectionDomain = ((cDomainSingle*)(pDirectionDomainElement));

	//store scaling factor in direction
	const string szDomainElementType2 = pDirectionDomain->getType();
	if ( ( szDomainElementType2.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
				(szDomainElementType2.compare( 0, 13, "DomainInteger" ) == 0) ){
		//cDomainIntegerBasis
		cDomainIntegerBasis * pDomInteger = (cDomainIntegerBasis*)pDirectionDomain;
		dDim2ScalingFactor = abs( pDomInteger->getScalingFactor() );
		ulDim2Min = pDomInteger->getMinimumUnscaled();
		ulDim2Max = pDomInteger->getMaximumUnscaled();
	}else{
		//can't work with not int domain
		if ( bStandardDimensionDomain ){
			delete pDomainDimension;
		}
		setIsRunning( false );
		return true;
	}
	if ( bStandardDimensionDomain ){
		delete pDomainDimension;
	}
	DEBUG_OUT_L2(<<"direction 2: min: "<<ulDim2Min<<" max: "<<ulDim2Max<<" scaling factor: "<<dDim2ScalingFactor<<endl<<flush);
	
	unsignedLongFib ulAreasToCreate = 1;
	
	if ( rand() % 4 != 0 ){
		ulAreasToCreate = rand() % ((unsignedLongFib)(log( ulNumberOfPoints ))) + 1;
		
	}//else minimum 25 % propadility to create just one area
	DEBUG_OUT_L2(<<"areas to creat :"<<ulAreasToCreate<<endl<<flush);
	
	//create a map for faster search of the positions 
	typedef pair< nD1::cDataPoint< longFib, longFib>, const list< cVectorProperty > * >
				typePairPointProperties;
	typedef map< nD1::cDataPoint< longFib, longFib>, const list< cVectorProperty > * >
				typeMapPointProperties;
	
	//a map with the point and ther properties
	typeMapPointProperties mapPointProperties;
	
	for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
			itrPoint = pOrginalPositionsData->liEvaluedPositionData.begin();
			itrPoint != pOrginalPositionsData->liEvaluedPositionData.end(); itrPoint++ ){
		
		mapPointProperties.insert( typePairPointProperties( nD1::cDataPoint< longFib, longFib >(
			roundToLongFib( itrPoint->first.getValue( 1 ) * dDim1ScalingFactor),
			roundToLongFib( itrPoint->first.getValue( 2 ) * dDim2ScalingFactor) ),
			&(itrPoint->second) ) );
	}
	
	//choose random point
	size_t iChoosenPoint = rand() % ulNumberOfPoints;
	
	DEBUG_OUT_L2(<<"choosen point for maximal acceptebel difference: "<<iChoosenPoint<<endl<<flush);

	list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
		itrPoint = pOrginalPositionsData->liEvaluedPositionData.begin();
	for ( ; ( itrPoint != pOrginalPositionsData->liEvaluedPositionData.end() ) &&
			( 0 < iChoosenPoint );
			itrPoint++, iChoosenPoint-- ){
		//nothing to do
	}
	if ( itrPoint == pOrginalPositionsData->liEvaluedPositionData.end() ){
		DEBUG_OUT_EL2(<<"Error: Non existing point choosen"<<endl<<flush);
		setIsRunning( false );
		return true;
	}
	list< cVectorProperty > liActualProperties = itrPoint->second;
	liActualProperties.sort( cVectorProperty::lowerPropertyVector );
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
	DEBUG_OUT_L2(<<"number of areas to create: "<<ulAreasToCreate<<endl<<flush);
	//for the number of areas to create
	bool bAreaCreated = false;
	for ( unsignedLongFib ulActualArea = 1; ulActualArea <= ulAreasToCreate;
			ulActualArea++ ){
		//choose random point for the first area point
		
		if ( mapPointProperties.size() < 5 ){
			DEBUG_OUT_L2(<<"Warning: Not enough points to create a area ( "<<mapPointProperties.size()<<" )"<<endl<<flush);
			continue;
		}
		unsignedLongFib ulChoosenPoint = rand() % mapPointProperties.size();
		DEBUG_OUT_L2(<<"choose random point from this areas ( "<<ulActualArea<<" ) :"<<ulChoosenPoint<<endl<<flush);
		
		typeMapPointProperties::iterator itrPoint = mapPointProperties.begin();
		for ( ; ( itrPoint != mapPointProperties.end() ) &&
				( 0 < ulChoosenPoint );
				itrPoint++, ulChoosenPoint-- ){
			//nothing to do
		}
		if ( itrPoint == mapPointProperties.end() ){
			DEBUG_OUT_EL2(<<"Error: Non existing point choosen"<<endl<<flush);
			continue;
		}
		const list< cVectorProperty > liChoosenProperties = *(itrPoint->second);
		
		DEBUG_OUT_L2(<<"the choose point is ("<< itrPoint->first.x <<", "<< itrPoint->first.y <<")"<<endl<<flush);
		const nD1::cDataPoint< longFib, longFib > paOriginalPoint( itrPoint->first );
		
		DEBUG_OUT_L2(<<"find all points which are directly or indirectly neibourpoints of the choosen point"<<endl<<flush);
		/*find all points which are directly or indirectly neibourpoints of the
		choosen point*/
		typedef set< nD1::cDataPoint< longFib, longFib > >
					typeSetPoints;
		//a set with the neibourpoints to check the neibours of
		typeSetPoints setPointsToCheck;
		setPointsToCheck.insert( paOriginalPoint );
		//a set with the neibourpoints which neibours are checked
		typeSetPoints setCheckedPoints;
		
		const typeMapPointProperties::const_iterator itrOriginalPoint =
			mapPointProperties.find( paOriginalPoint );
	
		if ( itrOriginalPoint == mapPointProperties.end() ){
			//error: no original point found
			DEBUG_OUT_EL2(<<"Original point not in evalued map"<<endl<<flush);
			continue;
		}
		const list< cVectorProperty > paOriginalPointProperties =
			*(itrOriginalPoint->second);
		
		while ( ! setPointsToCheck.empty() ){
			
			typeSetPoints::iterator itrPointToCheck = setPointsToCheck.begin();
			
			const unsignedLongFib ulActualPosDim1 = itrPointToCheck->x;
			const unsignedLongFib ulActualPosDim2 = itrPointToCheck->y;
			setCheckedPoints.insert( * itrPointToCheck );
			setPointsToCheck.erase( itrPointToCheck );
			
			//check the 4 neibours of the point
			//compare the properties of the points with the properties of the original point
			for ( unsigned int uiNeibour = 0; uiNeibour < 4; uiNeibour++ ){
				
				nD1::cDataPoint< longFib, longFib > actualPosition;
				switch ( uiNeibour ){
					case 0:
						if ( ulActualPosDim1 <= ulDim1Min ){
							continue;//no neibour in direction
						}
						actualPosition.x = ulActualPosDim1 - 1;
						actualPosition.y = ulActualPosDim2;
					break;
					case 1:
						if ( ulDim1Max <= ulActualPosDim1 ){
							continue;//no neibour in direction
						}
						actualPosition.x = ulActualPosDim1 + 1;
						actualPosition.y = ulActualPosDim2;
					break;
					case 2:
						if ( ulActualPosDim2 <= ulDim2Min ){
							continue;//no neibour in direction
						}
						actualPosition.x = ulActualPosDim1;
						actualPosition.y = ulActualPosDim2 - 1;
					break;
					case 3:
						if ( ulDim2Max <= ulActualPosDim2 ){
							continue;//no neibour in direction
						}
						actualPosition.x = ulActualPosDim1;
						actualPosition.y = ulActualPosDim2 + 1;
					break;
					default:
						continue;//unknown neibour -> switch it
				}
				//check if point was checked befor
				if ( ( setCheckedPoints.find( actualPosition ) == setCheckedPoints.end() ) &&
						( setPointsToCheck.find( actualPosition ) == setPointsToCheck.end() ) ){
					/*point not checked befor and not allready notified to check
					-> check if it has the correct properties*/
					
					//todo find the point properties
					const typeMapPointProperties::const_iterator itrActualPoint =
						mapPointProperties.find( actualPosition );
					
					if ( itrActualPoint == mapPointProperties.end() ){
						//no such point -> check next point
						continue;
					}
					//compare the properties of the points with the properties of the original point
					if ( cEvaluePositionList::distanceOfProperties(
							*(itrActualPoint->second), liChoosenProperties ) <=
								dMaxDifference ){
						setPointsToCheck.insert( actualPosition );
						//erase point, do not include it in other areas
						mapPointProperties.erase( actualPosition );
					}
				}
			}
		}
		
		DEBUG_OUT_L2(<<"number of points which are neibourpoints of the choosen point: "<<setCheckedPoints.size()<<endl<<flush);
		if ( setCheckedPoints.size() < 5 ){
			continue;
		}
		/*create the area underobjects: build the area -point -underobjects for
		the selected points with same properties*/
	
		cFibVariable * pVariableX = new cFibVariable( NULL );
		cFibVariable * pVariableY = new cFibVariable( NULL );
		cVectorPosition vecPosition( 2 );
		vecPosition.setVariable( 1, pVariableX );
		vecPosition.setVariable( 2, pVariableY );
		
		cPoint * pNewPoint = new cPoint( & vecPosition );
		
		DEBUG_OUT_L2(<<"createAreasForPoints()"<<endl<<flush);
		cFibElement * pAreaFibObject = createAreasForPoints< longFib >(
			setCheckedPoints, pNewPoint, pVariableX, pVariableY );
		
		if ( pAreaFibObject == NULL ){
			DEBUG_OUT_EL2(<<"Error: createAreasForPoints() returned NULL"<<endl<<flush);
			cFibElement::deleteObject( pNewPoint );
			delete pVariableX;
			delete pVariableY;
			continue;
		}
		delete pVariableX;
		delete pVariableY;
		DEBUG_OUT_L2(<<"creating fib -object to insert"<<endl<<flush);
		
		if ( dDim1ScalingFactor != 1.0 ){
			DEBUG_OUT_L2(<<"adding dimension 1 scaling factor transformations"<<endl<<flush);
			
			cFunctionValue funValScalingFactor( dDim1ScalingFactor );
			//for every pointelement
			for ( cPoint * pPoint = ((cPoint*)pAreaFibObject->getNextFibElement( 'p' ) );
					pPoint != NULL; pPoint = ((cPoint*)pPoint->getNextFibElement( 'p' ) ) ){
				
				//evalue the varaible for dimension 1 of the point element and scale it
				if ( pPoint->getPosition() == NULL ){
					DEBUG_OUT_L2(<<"Error: point ("<<pPoint->getNumberOfElement()<<") with no positionsvector"<<endl<<flush);
					continue;
				}
				cFibVariable * pVariable = pPoint->getPosition()->getVariable( 1 );
				if ( pVariable != NULL ){
					//scale the variable
					cFibElement * pSuperior = pPoint->getSuperiorFibElement();
					cFunctionMult underFunction( funValScalingFactor,
						cFunctionVariable( pVariable ) );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
					cFunction * pFunction = new cFunction(
						((cUnderFunction&)underFunction), pPoint );
#else //FEATURE_SIMPLE_CONSTRUCTOR
					cFunction * pFunction = new cFunction(
						((cUnderFunction&)underFunction), NULL, NULL, pPoint );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
					pPoint->replaceVariable( pVariable, pFunction->getDefinedVariable() );
					//insert the function on the position of the point
					pSuperior->insertElement( pFunction );
				}else{
					//scale value
					pPoint->getPosition()->setValue( 1,
						pPoint->getPosition()->getValue( 1 ) * dDim1ScalingFactor );
				}
			}
		}
		if ( dDim2ScalingFactor != 1.0 ){
			DEBUG_OUT_L2(<<"adding dimension 2 scaling factor transformations"<<endl<<flush);
	
			cFunctionValue funValScalingFactor( dDim2ScalingFactor );
			//for every pointelement
			for ( cPoint * pPoint = ((cPoint*)pAreaFibObject->getNextFibElement( 'p' ) );
					pPoint != NULL; pPoint = ((cPoint*)pPoint->getNextFibElement( 'p' ) ) ){
				
				//evalue the varaible for dimension 1 of the point element and scale it
				if ( pPoint->getPosition() == NULL ){
					DEBUG_OUT_L2(<<"Error: point ("<<pPoint->getNumberOfElement()<<") with no positionsvector"<<endl<<flush);
					continue;
				}
				cFibVariable * pVariable = pPoint->getPosition()->getVariable( 2 );
				if ( pVariable != NULL ){
					//scale the variable
					cFibElement * pSuperior = pPoint->getSuperiorFibElement();
					cFunctionMult underFunction( funValScalingFactor,
						cFunctionVariable( pVariable ) );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
					cFunction * pFunction = new cFunction(
						((cUnderFunction&)underFunction), pPoint );
#else //FEATURE_SIMPLE_CONSTRUCTOR
					cFunction * pFunction = new cFunction(
						((cUnderFunction&)underFunction), NULL, NULL, pPoint );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
					pPoint->replaceVariable( pVariable, pFunction->getDefinedVariable() );
					//insert the function on the position of the point
					pSuperior->insertElement( pFunction );
				}else{
					//scale value
					pPoint->getPosition()->setValue( 2,
						pPoint->getPosition()->getValue( 2 ) * dDim1ScalingFactor );
				}
			}
		}
		
		DEBUG_OUT_L2(<<"adding correct properties to the created area fib -object"<<endl<<flush);
		
		//add the properties
		for ( list< cVectorProperty >::const_iterator
				itrProperty = liChoosenProperties.begin();
				itrProperty != liChoosenProperties.end(); itrProperty++ ){
			
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
			pAreaFibObject = new cProperty( *itrProperty, pAreaFibObject );
#else //FEATURE_SIMPLE_CONSTRUCTOR
			pAreaFibObject = new cProperty( *itrProperty, NULL, NULL, pAreaFibObject );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
		}
		
		//insert the created area -point -underobject as the last underobject
		DEBUG_OUT_L2(<<"inserting underobject"<<endl<<flush);
		
		bool bObjectInserted = false;
		cList * pNextList = ((cList*)( pFibObject->getNextFibElement( 'l' )) );
		if ( pNextList ){
			//add line to the end of the founded listelement
			bObjectInserted = pNextList->addUnderobject( pAreaFibObject,
				pNextList->getNumberOfUnderobjects() + 1 );
			
		}else{//create listelement as main -fib -object
			bObjectInserted = pFibObject->insertObjectInElement(
				pAreaFibObject, 'r', 0, false, true );
		}
		if ( ! bObjectInserted ){
			pAreaFibObject->deleteObject();
			delete pIndividual;

			setIsRunning( false );
			
			DEBUG_OUT_L1(<<getName()<<"::run() done generated object could not be inserted"<<endl<<flush);
			return false;
		}
		bAreaCreated = true;
	}
	if ( ! bAreaCreated ){
		DEBUG_OUT_L2(<<"no areas created"<<endl<<flush);
		delete pIndividual;
		setIsRunning( false );
		return true;
	}

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
string cOp2DFibFindSimilarAreaNOrg::getName() const{
	return "cOp2DFibFindSimilarAreaNOrg";
}


/**
 * This function compares two property elemente pairs.
 * It is used for ordering property elemente pairs.
 *
 * @param paPropertyElement1 the first property elemente pair to compare
 * @param paPropertyElement2 the second property elemente pair to compare
 * @return true if the propertietype of the first pair is lower or,
 * 	if the propertietyps are equal, if the second element number of the
 * 	first pair is lower
 */
bool cOp2DFibFindSimilarAreaNOrg::lowerPropertyElement(
		const pair< cTypeProperty, unsignedIntFib > & paPropertyElement1,
		const pair< cTypeProperty, unsignedIntFib > & paPropertyElement2 ){

	return ( paPropertyElement1.first < paPropertyElement2.first ) ||
		( ( paPropertyElement1.first == paPropertyElement2.first ) &&
		( paPropertyElement1.second < paPropertyElement2.second ) );
}


/**
 * @param dValue the value for which to check, if it is 0
 * @return true if the given value is 0, else false
 */
bool cOp2DFibFindSimilarAreaNOrg::isNull( const double & dValue ){
	
	return (dValue == 0);
}



