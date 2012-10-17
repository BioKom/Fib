/**
 * @file cOp2DFibFindEvenAreaOrg
 * file name: cOp2DFibFindEvenAreaOrg.h
 * @author Betti Oesterholz
 * @date 16.09.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This Operator Evalues the areas with the same properties and combines
 * one to an complex fib -underobject.
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
 * and combines a random one to an complex fib -underobject.
 * This is done with the help of area- and functionelements.
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
16.09.2010  Oesterholz  created
01.12.2011  Oesterholz  changes for: cDomainVector has as elements now
	cDomain and not cDomainSingle 
*/



#include "cOp2DFibFindEvenAreaOrg.h"

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
cOp2DFibFindEvenAreaOrg::cOp2DFibFindEvenAreaOrg( const cOperationIdentifier & operationId ):
		cOperationFib( operationId ){
	//nothing to do
}


/**
 * Destructor of the class cOp2DFibFindEvenAreaOrg.
 */
cOp2DFibFindEvenAreaOrg::~cOp2DFibFindEvenAreaOrg(){
	//nothing to do
}


/**
 * This method creats a new instance of this operator.
 * Beware: You have to delete the instance after usage.
 *
 * @param operationId the identifer for the operation
 * @return a pointer to a new instance of this operation
 */
cOp2DFibFindEvenAreaOrg * cOp2DFibFindEvenAreaOrg::createInstance(
		const cOperationIdentifier & operationId ) const{
	
	return new cOp2DFibFindEvenAreaOrg( operationId );
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
bool cOp2DFibFindEvenAreaOrg::run(){
	
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
	const unsignedLongFib ulEvaluedPoints = pOrginalPositionsData->liEvaluedPositionData.size();
	if ( ulEvaluedPoints < 3 ){
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
	DEBUG_OUT_L2(<<"direction 2: min: "<<ulDim2Min<<" max: "<<ulDim2Max<<" scaling factor: "<<dDim2ScalingFactor<<endl<<flush);

	const unsignedLongFib ulSizeDim1 = (ulDim1Max - ulDim1Min + 1);
	const unsignedLongFib ulSizeDim2 = (ulDim2Max - ulDim2Min + 1);

	if ( bStandardDimensionDomain ){
		delete pDomainDimension;
	}
	
	DEBUG_OUT_L2(<<"create the 2 D matrixes for ever existing property vector element"<<endl<<flush);
	//create the 2 D matrixes for ever existing property vector element
	typedef pair< pair< cTypeProperty, unsignedIntFib >, cMatrix2D<doubleFib> >
		typePairMatrix;
	typedef map< pair< cTypeProperty, unsignedIntFib >, cMatrix2D<doubleFib>,
		bool(*)( const pair< cTypeProperty, unsignedIntFib >& ,
		const pair< cTypeProperty, unsignedIntFib >& ) > typeMapMatrix;

	typeMapMatrix mapPropertyValues( lowerPropertyElement );
	
	//for every position
	for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
			itrPoint = pOrginalPositionsData->liEvaluedPositionData.begin();
			itrPoint != pOrginalPositionsData->liEvaluedPositionData.end(); itrPoint++ ){
		
		//for every property
		for ( list< cVectorProperty >::const_iterator itrProperty = itrPoint->second.begin();
				itrProperty != itrPoint->second.end(); itrProperty++ ){
			
			const unsignedIntFib uiNumberOfElements = itrProperty->getNumberOfElements();
			const cTypeProperty * pPropertyType = ((cTypeProperty*)
				(itrProperty->getElementType()));
			if ( pPropertyType == NULL ){
				//error
				continue;
			}
			
			//for every property element
			for ( unsignedIntFib uiActualElement = 1;
					uiActualElement <= uiNumberOfElements; uiActualElement++ ){
				
				const pair< cTypeProperty, unsignedIntFib > paPropertyElement(
					*pPropertyType, uiActualElement );
				
				typeMapMatrix::iterator itrMapEntry = mapPropertyValues.find( paPropertyElement );
				
				if ( itrMapEntry == mapPropertyValues.end() ){
					
					const pair< typeMapMatrix::iterator, bool > paInsertPair =
						mapPropertyValues.insert( typePairMatrix( paPropertyElement,
							cMatrix2D<doubleFib>( ulSizeDim1, ulSizeDim2 ) ) );
					
					itrMapEntry = paInsertPair.first;
				}
				//set for the propertyelement the matrix element
				itrMapEntry->second.set(
					roundToLongFib( itrPoint->first.getValue( 1 ) * dDim1ScalingFactor ) - ulDim1Min,
					roundToLongFib( itrPoint->first.getValue( 2 ) * dDim2ScalingFactor ) - ulDim2Min,
					itrProperty->getValue( uiActualElement ) );
			}
			delete pPropertyType;
		}
	}
	DEBUG_OUT_L2(<<"evalue even areas with the aid of the first derivates"<<endl<<flush);
	// for calculations: true is not 0 and false is 0
	cMatrix2D<bool> matrixEvenPoints( ulSizeDim1 - 1, ulSizeDim2 - 1, true );
	
	for ( typeMapMatrix::iterator itrMatrix = mapPropertyValues.begin();
			itrMatrix != mapPropertyValues.end(); itrMatrix++ ){
		
		//create the derivats of the matrix in both directions indipendently
		cMatrix2D<doubleFib> matrixDerivateDim1 = itrMatrix->second;
		matrixDerivateDim1.derivateDirection1();
		cMatrix2D<doubleFib> matrixDerivateDim2 = itrMatrix->second;
		matrixDerivateDim2.derivateDirection2();
		
		//find even areas in bouth directions
		cMatrix2D<bool> matrixEvenDim1 = matrixDerivateDim1.evalueCondition( isNull );
		cMatrix2D<bool> matrixEvenDim2 = matrixDerivateDim2.evalueCondition( isNull );
		
		/*combine the directions
		== evalue areas which are even in both directions*/
		matrixEvenDim1.resize( ulSizeDim1 - 1, ulSizeDim2 - 1  );
		matrixEvenPoints *= matrixEvenDim1;// * does the same as and
		matrixEvenDim2.resize( ulSizeDim1 - 1, ulSizeDim2 - 1 );
		matrixEvenPoints *= matrixEvenDim2;// * does the same as and
		
//#define DEBUG_OUTPUT_MATRIX
#ifdef DEBUG_OUTPUT_MATRIX
		cout<<"itrMatrix->second:"<<endl;
		itrMatrix->second.print( cout );
		cout<<"matrixDerivateDim1:"<<endl;
		matrixDerivateDim1.print( cout );
		cout<<"matrixDerivateDim2:"<<endl;
		matrixDerivateDim2.print( cout );
		cout<<endl<<"matrixEvenDim1:"<<endl;
		matrixEvenDim1.print( cout );
		cout<<"matrixEvenDim2:"<<endl;
		matrixEvenDim2.print( cout );
#endif
	}
#ifdef DEBUG_OUTPUT_MATRIX
		cout<<endl<<"matrixEvenPoints:"<<endl;
		matrixEvenPoints.print( cout );
#endif
	const unsignedLongFib ulEvenPoints = ( (ulSizeDim1 - 1) * (ulSizeDim2 - 1) ) -
		matrixEvenPoints.countNull();//all points minus all false points
	
	DEBUG_OUT_L2(<<"evalued even points: "<<ulEvenPoints<<endl<<flush);
	//choos a random point from the even areas
	if ( ulEvenPoints < 5 ){
		DEBUG_OUT_L2(<<"no even points to choose from"<<endl<<flush);
		//no even points to choose from
		setIsRunning( false );
		return true;
	}
	unsignedLongFib ulChoosenPoint = rand() % ulEvenPoints;
	DEBUG_OUT_L2(<<"choose random point from this areas :"<<ulChoosenPoint<<endl<<flush);
	
	unsignedLongFib ulPosDim1 = 0;
	unsignedLongFib ulPosDim2 = 0;
	for ( ulPosDim1 = 0; (ulPosDim1 < ulSizeDim1 - 1) &&
			(ulChoosenPoint != 0); ulPosDim1++ ){
		for ( ulPosDim2 = 0; (ulPosDim2 < ulSizeDim2 - 1) &&
				(ulChoosenPoint != 0); ulPosDim2++ ){
		
			if ( matrixEvenPoints.get( ulPosDim1, ulPosDim2 ) ){
				ulChoosenPoint--;
			}
		}
	}
	//choos a random point from the even areas
	if ( (ulSizeDim1 - 1 <= ulPosDim1) || (ulSizeDim2 - 1 <= ulPosDim2) ){
		DEBUG_OUT_EL2(<<"Error: the choosen point out of boundery"<<endl<<flush);
		//the choosen point out of boundery
		setIsRunning( false );
		return true;
	}
	DEBUG_OUT_L2(<<"the choose point is ("<<ulPosDim1 - ulDim1Min<<", "<<ulPosDim2 - ulDim2Min<<")"<<endl<<flush);
	const nD1::cDataPoint< longFib, longFib > paOriginalPoint(
		ulPosDim1 + ulDim1Min, ulPosDim2 + ulDim2Min );
	
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
	const typeMapPointProperties::const_iterator itrOriginalPoint =
		mapPointProperties.find( paOriginalPoint );

	if ( itrOriginalPoint == mapPointProperties.end() ){
		//error: no original point found
		DEBUG_OUT_EL2(<<"Original point not in evalued map"<<endl<<flush);
		setIsRunning( false );
		return true;
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
					actualPosition.x  = ulActualPosDim1 - 1;
					actualPosition.y = ulActualPosDim2;
				break;
				case 1:
					if ( ulDim1Max <= ulActualPosDim1 ){
						continue;//no neibour in direction
					}
					actualPosition.x  = ulActualPosDim1 + 1;
					actualPosition.y = ulActualPosDim2;
				break;
				case 2:
					if ( ulActualPosDim2 <= ulDim2Min ){
						continue;//no neibour in direction
					}
					actualPosition.x  = ulActualPosDim1;
					actualPosition.y = ulActualPosDim2 - 1;
				break;
				case 3:
					if ( ulDim2Max <= ulActualPosDim2 ){
						continue;//no neibour in direction
					}
					actualPosition.x  = ulActualPosDim1;
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
				const typeMapPointProperties::iterator itrActualPoint =
					mapPointProperties.find( actualPosition );
				
				if ( itrActualPoint == mapPointProperties.end() ){
					//no such point -> check next point
					continue;
				}
				//compare the properties of the points with the properties of the original point
				if ( paOriginalPointProperties == (*(itrActualPoint->second)) ){
					setPointsToCheck.insert( actualPosition );
				}
				//actual point isn't needed anymore
				mapPointProperties.erase( itrActualPoint );
			}
		}
	}
	
	DEBUG_OUT_L2(<<"number of points which are neibourpoints of the choosen point: "<<mapPointProperties.size()<<endl<<flush);
	if ( setCheckedPoints.size() < 3 ){
		setIsRunning( false );
		return true;
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
		setIsRunning( false );
		return true;
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
			itrProperty = paOriginalPointProperties.begin();
			itrProperty != paOriginalPointProperties.end(); itrProperty++ ){
		
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
		pAreaFibObject = new cProperty( *itrProperty, pAreaFibObject );
#else //FEATURE_SIMPLE_CONSTRUCTOR
		pAreaFibObject = new cProperty( *itrProperty, NULL, NULL, pAreaFibObject );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	}
	
	//insert the created area -point -underobject as the last underobject
	DEBUG_OUT_L2(<<"inserting underobject"<<endl<<flush);
	
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
string cOp2DFibFindEvenAreaOrg::getName() const{
	return "cOp2DFibFindEvenAreaOrg";
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
bool cOp2DFibFindEvenAreaOrg::lowerPropertyElement(
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
bool cOp2DFibFindEvenAreaOrg::isNull( const double & dValue ){
	
	return (dValue == 0);
}



