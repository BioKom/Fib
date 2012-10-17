/**
 * @file cFibObjectFitnessAlgorithm
 * file name: cFibObjectFitnessAlgorithm.cpp
 * @author Betti Oesterholz
 * @date 26.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies the abstract basisclass of fib -enviroment algorithm
 * creating fib -fitness objects.
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
 * @see cObjectFitness
 * This header specifies the abstract basisclass of fib -enviroment algorithm
 * for creating fib -fitness objects.
 * The better (higher) the fitness the better the fib -object, the more likly
 * it should live and children should be created from it.
 *
 */
/*
History:
26.02.2010  Oesterholz  created
12.09.2010  Oesterholz  getOriginalPositionList() method implemented
*/

#include "cFibObjectFitnessAlgorithm.h"

#include "cFibIndividual.h"
#include "cFibObjectFitness.h"

#include "cPoint.h"
#include "cTypeProperty.h"
#include "cTypeDimension.h"
#include "cDomainNaturalNumber.h"
#include "cDomainIntegerBasis.h"
#include "cDomainVector.h"
#include "cDomainVectorBasis.h"
#include "cEvaluePositionListLimit.h"


#include <ctime>

#ifdef FEATURE_ALGORITHM_WITH_BALANCED_FIB_OBJECT

	#include "nBalanceLists.h"

	using namespace fib::algorithms::nTidyFibObjects::nBalanceLists;

#endif //FEATURE_ALGORITHM_WITH_BALANCED_FIB_OBJECT

using namespace std;
using namespace enviroment::fib;


/**
 * constructor
 */
cFibObjectFitnessAlgorithm::cFibObjectFitnessAlgorithm():
		cObjectFitnessAlgorithm(), pOriginalRoots( NULL ),
		bOriginalIsFibObject( false ), pEvaluedPositionsDataOriginal( NULL ),
		bOriginalEvalued( false ),
		uiNumberOfDimensions( 0 ), pdDirectionMinimum( NULL ),
		pdDirectionMaximum( NULL ), pdDirectionScaling( NULL ),
		pdDirectionSize( NULL ),
		bStandardDimensionDomain( false ), pVecDomainDimension( NULL ),
		ulNumberOfPoints( 1 ){
	//nothing to do
}


/**
 * constructor
 *
 * @param pInOriginalIndividual the individual with which the fitness
 * 	should be evalued;
 * 	Beware: this object won't be copied, so don't delete it as long
 * 	as this object exists
 */
cFibObjectFitnessAlgorithm::cFibObjectFitnessAlgorithm(
		cFibIndividual * pInOriginalIndividual ):
		cObjectFitnessAlgorithm( pInOriginalIndividual ),
		pOriginalRoots( NULL ), bOriginalIsFibObject( false ),
		pEvaluedPositionsDataOriginal( NULL ), bOriginalEvalued( false ),
		uiNumberOfDimensions( 0 ), pdDirectionMinimum( NULL ),
		pdDirectionMaximum( NULL ), pdDirectionScaling( NULL ),
		pdDirectionSize( NULL ),
		bStandardDimensionDomain( false ), pVecDomainDimension( NULL ),
		ulNumberOfPoints( 1 ){
	
	if ( pOriginalIndividual ){
		//evalue the root -elements of the individual
		pOriginalRoots = createRootTree(
			(cFibElement*)(pOriginalIndividual->getObject()) );
#ifdef FEATURE_ALGORITHM_WITH_BALANCED_FIB_OBJECT
		balanceFibTreeLists( (cFibElement*)(pOriginalIndividual->getObject()),
			FEATURE_ALGORITHM_WITH_BALANCED_FIB_OBJECT );
#endif //FEATURE_ALGORITHM_WITH_BALANCED_FIB_OBJECT
		//evalue the dimensions of the original fib -object
		evalueOriginalDimensions();
		pEvaluedPositionsDataOriginal = new cEvaluePositionListLimit( ulNumberOfPoints * 2,
			pVecDomainDimension, false, 0, ulNumberOfPoints * 64 );
		
		const bool bObjectEvalued = ((cFibIndividual*)pOriginalIndividual)->
			getFibObject()->evalueObjectSimple( *pEvaluedPositionsDataOriginal );
		if ( bObjectEvalued ){
			pEvaluedPositionsDataOriginal->sortPositionsData();
			bOriginalEvalued = true;
		}else{
			DEBUG_OUT_EL1( <<"Error: The original fib -object couldn't be evalued."<<endl );
			bOriginalEvalued = false;
			if ( pEvaluedPositionsDataOriginal ){
				delete pEvaluedPositionsDataOriginal;
				pEvaluedPositionsDataOriginal = NULL;
			}
		}
	}else{
		pOriginalRoots = NULL;
		bOriginalEvalued = false;
	}
}


/**
 * constructor
 *
 * @param pInOriginalFibObject the fib -object with which the fitness
 * 	should be evalued;
 * 	Beware: this object won't be copied, so don't delete it as long
 * 	as this object exists
 */
cFibObjectFitnessAlgorithm::cFibObjectFitnessAlgorithm(
		cFibElement * pInOriginalFibObject ):
		pEvaluedPositionsDataOriginal( NULL ), bOriginalEvalued( false ),
		uiNumberOfDimensions( 0 ), pdDirectionMinimum( NULL ),
		pdDirectionMaximum( NULL ), pdDirectionScaling( NULL ),
		pdDirectionSize( NULL ),
		bStandardDimensionDomain( false ), pVecDomainDimension( NULL ),
		ulNumberOfPoints( 1 ){
	
	if ( pInOriginalFibObject ){
		//cIndividualInfo parameter
		const cFibObjectFitness fitnessDummy( 0.0 );
		const list<cIndividualIdentifier> liParents;
		
		pOriginalIndividual = new cFibIndividual( pInOriginalFibObject,
			cIndividualInfo( 0, liParents, fitnessDummy,
			"originalInvividual", "", cOperationIdentifier( 0 ),
			time_t( NULL ), 0.0, NULL ), false );
		bOriginalIsFibObject = true;
		
		//evalue the root -elements of the individual
		pOriginalRoots = createRootTree( pInOriginalFibObject);
#ifdef FEATURE_ALGORITHM_WITH_BALANCED_FIB_OBJECT
		balanceFibTreeLists( (cFibElement*)(pOriginalIndividual->getObject()),
			FEATURE_ALGORITHM_WITH_BALANCED_FIB_OBJECT );
#endif //FEATURE_ALGORITHM_WITH_BALANCED_FIB_OBJECT
		//evalue the dimensions of the original fib -object
		evalueOriginalDimensions();
		pEvaluedPositionsDataOriginal = new cEvaluePositionListLimit( ulNumberOfPoints * 2,
			pVecDomainDimension, false, 0, ulNumberOfPoints * 64 );
		
		const bool bObjectEvalued = pInOriginalFibObject->
			evalueObjectSimple( *pEvaluedPositionsDataOriginal );
		if ( bObjectEvalued ){
			pEvaluedPositionsDataOriginal->sortPositionsData();
			bOriginalEvalued = true;
		}else{
			DEBUG_OUT_EL1( <<"Error: The original fib -object couldn't be evalued."<<endl );
			bOriginalEvalued = false;
			if ( pEvaluedPositionsDataOriginal ){
				delete pEvaluedPositionsDataOriginal;
				pEvaluedPositionsDataOriginal = NULL;
			}
		}
	}else{
		pOriginalIndividual = NULL;
		bOriginalIsFibObject = false;
		pOriginalRoots = NULL;
	}
}


/**
 * copyconstructor
 *
 * @param objectFitnessAlgorithm the cFibObjectFitnessAlgorithm object to copy
 */
cFibObjectFitnessAlgorithm::cFibObjectFitnessAlgorithm(
		const cFibObjectFitnessAlgorithm & objectFitnessAlgorithm ):
		cObjectFitnessAlgorithm( objectFitnessAlgorithm ),
		bOriginalIsFibObject( objectFitnessAlgorithm.bOriginalIsFibObject ),
		pEvaluedPositionsDataOriginal( NULL ),
		bOriginalEvalued( false ),
		uiNumberOfDimensions( 0 ), pdDirectionMinimum( NULL ),
		pdDirectionMaximum( NULL ), pdDirectionScaling( NULL ),
		pdDirectionSize( NULL ),
		bStandardDimensionDomain( false ), pVecDomainDimension( NULL ),
		ulNumberOfPoints( 1 ){
	
	if ( bOriginalIsFibObject ){
		//cIndividualInfo parameter
		const cFibObjectFitness fitnessDummy( 0.0 );
		const list<cIndividualIdentifier> liParents;
		
		pOriginalIndividual = new cFibIndividual(
			const_cast<cFibElement*>(
			const_cast<cFibObjectFitnessAlgorithm*>(
				& objectFitnessAlgorithm )->getOriginalFibObject() ),
			cIndividualInfo( 0, liParents, fitnessDummy,
			"originalInvividual", "", cOperationIdentifier( 0 ),
			time_t( NULL ), 0.0, NULL ), false );
	}

	if ( pOriginalIndividual ){
		//evalue the root -elements of the individual
		pOriginalRoots = createRootTree(
			(cFibElement*)(pOriginalIndividual->getObject()) );
#ifdef FEATURE_ALGORITHM_WITH_BALANCED_FIB_OBJECT
		balanceFibTreeLists( (cFibElement*)(pOriginalIndividual->getObject()),
			FEATURE_ALGORITHM_WITH_BALANCED_FIB_OBJECT );
#endif //FEATURE_ALGORITHM_WITH_BALANCED_FIB_OBJECT
		//evalue the dimensions of the original fib -object
		evalueOriginalDimensions();
		pEvaluedPositionsDataOriginal = new cEvaluePositionListLimit( ulNumberOfPoints * 2,
			pVecDomainDimension, false, 0, ulNumberOfPoints * 64 );
		
		const bool bObjectEvalued = ((cFibIndividual*)pOriginalIndividual)->
			getFibObject()->evalueObjectSimple( *pEvaluedPositionsDataOriginal );
		if ( bObjectEvalued ){
			pEvaluedPositionsDataOriginal->sortPositionsData();
			bOriginalEvalued = true;
		}else{
			DEBUG_OUT_EL1( <<"Error: The original fib -object couldn't be evalued."<<endl );
			bOriginalEvalued = false;
			if ( pEvaluedPositionsDataOriginal ){
				delete pEvaluedPositionsDataOriginal;
				pEvaluedPositionsDataOriginal = NULL;
			}
		}
	}else{
		pOriginalRoots = NULL;
	}
}


/**
 * destructor
 */
cFibObjectFitnessAlgorithm::~cFibObjectFitnessAlgorithm(){
	
	if ( pEvaluedPositionsDataOriginal ){
		delete pEvaluedPositionsDataOriginal;
	}
	if ( pOriginalRoots ){
		cFibElement::deleteObject( pOriginalRoots );
	}
	if ( bOriginalIsFibObject && ( pOriginalIndividual != NULL ) ){
		delete pOriginalIndividual;
	}
	
	if ( pdDirectionMinimum != NULL ){
		delete[] pdDirectionMinimum;
	}
	if ( pdDirectionMaximum != NULL ){
		delete[] pdDirectionMaximum;
	}
	if ( pdDirectionScaling != NULL ){
		delete[] pdDirectionScaling;
	}
	if ( pdDirectionSize != NULL ){
		delete[] pdDirectionSize;
	}
	if ( bStandardDimensionDomain && ( pVecDomainDimension != NULL ) ){
		delete pVecDomainDimension;
	}
}


/**
 * @return the name of this class
 */
string cFibObjectFitnessAlgorithm::getClassName() const{

	return "cFibObjectFitnessAlgorithm";
}



/**
 * This method sets the originalindividual.
 * The originalindividual is the individual with which the fitness
 * should be evalued.
 *
 * @see getOriginalIndividual()
 * @see pOriginalIndividual
 * @param pInOriginalIndividual a point to the fib -originalindividual to set
 * 	Beware: this object won't be copied, so don't delete it as long
 * 	as this object exists
 * @return true if the originalindividual is set to pInOriginalIndividual,
 * 	else false
 */
bool cFibObjectFitnessAlgorithm::setOriginalIndividual(
		cIndividual * pInOriginalIndividual ){
	
	if ( (pInOriginalIndividual != NULL) &&
			(pInOriginalIndividual->getClassName() != "cFibIndividual") ){
		return false;
	}
	
	return setOriginalIndividual( (cFibIndividual*)pInOriginalIndividual );
}


/**
 * This method sets the originalindividual.
 * The originalindividual is the individual with which the fitness
 * should be evalued.
 *
 * @see getOriginalIndividual()
 * @see pOriginalIndividual
 * @param pInOriginalIndividual a point to the fib -originalindividual to set
 * 	Beware: this object won't be copied, so don't delete it as long
 * 	as this object exists
 * @return true if the originalindividual is set to pInOriginalIndividual,
 * 	else false
 */
bool cFibObjectFitnessAlgorithm::setOriginalIndividual(
		cFibIndividual * pInOriginalIndividual ){
	
	bOriginalEvalued = false;
	if ( pEvaluedPositionsDataOriginal ){
		delete pEvaluedPositionsDataOriginal;
		pEvaluedPositionsDataOriginal = NULL;
	}
	if ( bOriginalIsFibObject && ( pOriginalIndividual != NULL ) ){
		delete pOriginalIndividual;
	}
	pOriginalIndividual  = pInOriginalIndividual;
	bOriginalIsFibObject = false;
	
	if ( pOriginalRoots ){
		cFibElement::deleteObject( pOriginalRoots );
		pOriginalRoots = NULL;
	}
	bool bRetunValue = true;
	if ( pOriginalIndividual ){
		//evalue the root -elements of the individual
		pOriginalRoots = createRootTree(
			(cFibElement*)(pOriginalIndividual->getObject()) );
#ifdef FEATURE_ALGORITHM_WITH_BALANCED_FIB_OBJECT
		balanceFibTreeLists( (cFibElement*)(pOriginalIndividual->getObject()),
			FEATURE_ALGORITHM_WITH_BALANCED_FIB_OBJECT );
#endif //FEATURE_ALGORITHM_WITH_BALANCED_FIB_OBJECT
		//evalue the dimensions of the original fib -object
		bRetunValue = evalueOriginalDimensions();
		pEvaluedPositionsDataOriginal = new cEvaluePositionListLimit( ulNumberOfPoints * 2,
			pVecDomainDimension, false, 0, ulNumberOfPoints * 64 );
		
		const bool bObjectEvalued = ((cFibIndividual*)pOriginalIndividual)->
			getFibObject()->evalueObjectSimple( *pEvaluedPositionsDataOriginal );
		if ( bObjectEvalued ){
			pEvaluedPositionsDataOriginal->sortPositionsData();
			bOriginalEvalued = true;
		}else{
			DEBUG_OUT_EL1( <<"Error: The original fib -object couldn't be evalued."<<endl );
			if ( pEvaluedPositionsDataOriginal ){
				delete pEvaluedPositionsDataOriginal;
				pEvaluedPositionsDataOriginal = NULL;
			}
			bRetunValue = false;
		}
	}
	return bRetunValue;
}


/**
 * This method sets the originalindividual.
 * The originalindividual is the individual with which the fitness
 * should be evalued.
 *
 * @see getOriginalIndividual()
 * @see pOriginalIndividual
 * @param pInOriginalFibObject the fib -object with which the fitness
 * 	should be evalued;
 * 	Beware: this object won't be copied, so don't delete it as long
 * 	as this object exists
 * @return true if the originalindividual is set to pInOriginalFibObject,
 * 	else false
 */
bool cFibObjectFitnessAlgorithm::setOriginalFibObject(
		cFibElement  * pInOriginalFibObject ){
	
	bOriginalEvalued = false;
	if ( pEvaluedPositionsDataOriginal ){
		delete pEvaluedPositionsDataOriginal;
		pEvaluedPositionsDataOriginal = NULL;
	}
	if ( bOriginalIsFibObject && ( pOriginalIndividual != NULL ) ){
		delete pOriginalIndividual;
	}
	if ( pOriginalRoots ){
		cFibElement::deleteObject( pOriginalRoots );
		pOriginalRoots = NULL;
	}
	bool bReturnValue = true;
	if ( pInOriginalFibObject != NULL ){
		//cIndividualInfo parameter
		cFibObjectFitness fitnessDummy( 0.0 );
		
		pOriginalIndividual = new cFibIndividual( pInOriginalFibObject,
			cIndividualInfo( 0, list<cIndividualIdentifier>(), fitnessDummy,
			"originalInvividual", "", cOperationIdentifier( 0 ),
			time_t( NULL ), 0.0, NULL ), false );
		bOriginalIsFibObject = true;
		
		//evalue the root -elements of the individual
		pOriginalRoots = createRootTree( pInOriginalFibObject );
#ifdef FEATURE_ALGORITHM_WITH_BALANCED_FIB_OBJECT
		balanceFibTreeLists( (cFibElement*)(pOriginalIndividual->getObject()),
			FEATURE_ALGORITHM_WITH_BALANCED_FIB_OBJECT );
#endif //FEATURE_ALGORITHM_WITH_BALANCED_FIB_OBJECT
		//evalue the dimensions of the original fib -object
		bReturnValue = evalueOriginalDimensions();
		pEvaluedPositionsDataOriginal = new cEvaluePositionListLimit( ulNumberOfPoints * 2,
			pVecDomainDimension, false, 0, ulNumberOfPoints * 64 );
		
		const bool bObjectEvalued = pInOriginalFibObject->
			evalueObjectSimple( *pEvaluedPositionsDataOriginal );
		if ( bObjectEvalued ){
			pEvaluedPositionsDataOriginal->sortPositionsData();
			bOriginalEvalued = true;
		}else{
			DEBUG_OUT_EL1( <<"Error: The original fib -object couldn't be evalued."<<endl );
			if ( pEvaluedPositionsDataOriginal ){
				delete pEvaluedPositionsDataOriginal;
				pEvaluedPositionsDataOriginal = NULL;
			}
			bReturnValue = false;
		}
	}else{
		pOriginalIndividual  = NULL;
		bOriginalIsFibObject = false;
	}
	return bReturnValue;
}


/**
 * @see setOriginalIndividual()
 * @see getOriginalIndividual()
 * @return a pointer to the originalindividual
 * 	The originalindividual is the individual with which the
 * 	fitness is evalued.
 */
cFibIndividual * cFibObjectFitnessAlgorithm::getOriginalIndividual(){

	return (cFibIndividual*)pOriginalIndividual;
}


/**
 * @see setOriginalFibObject()
 * @see getOriginalIndividual()
 * @return a pointer to the originalindividual
 * 	The originalindividual is the individual with which the
 * 	fitness is evalued.
 */
const cFibElement * cFibObjectFitnessAlgorithm::getOriginalFibObject(){

	if ( pOriginalIndividual == NULL ){
		return NULL;
	}//else
	return ((cFibIndividual*)pOriginalIndividual)->getFibObject();
}


/**
 * @see setOriginalIndividual()
 * @see getOriginalIndividual()
 * @see pOriginalIndividual
 * @return a pointer to the originalindividual root -elements;
 * 	The originalindividual is the individual with which the
 * 	fitness is evalued. This methods will yust return ther
 * 	root -elements, with the main -fib -objects set to NULL.
 */
const cRoot * cFibObjectFitnessAlgorithm::getOriginalIndividualRoot(){

	return pOriginalRoots;
}


/**
 * This function extracts the root -element tree from the fib -object.
 * The root -elements will have the same structur as in the given
 * fib -object, but empty points for ther main fib objects.
 * Beware: delete the returnd fib object after usage.
 *
 * @param pFibObject the fib -object wher to extract the root -elements
 * @return a fib -object with just root -elements of the given
 * 	fib -object pFibObject
 */
cRoot * cFibObjectFitnessAlgorithm::createRootTree( const cFibElement * pFibObject ){
	
	if ( (pFibObject == NULL) || (pFibObject->getType() != 'r') ){
		return NULL;
	}
	cRoot * pOriginalRoot = (cRoot*)pFibObject;
	cRoot * pMasterRoot = new cRoot( *pOriginalRoot );
	pMasterRoot->insertElement( new cPoint() );
	
	//copy sub -roots
	for ( unsigned int uiActualSubRoot = 1;
			uiActualSubRoot <= pOriginalRoot->getNumberOfSubRootObjects();
			uiActualSubRoot++ ){
		
		pair<longFib, cRoot*> paSubRoot = pOriginalRoot->getSubRootObject( uiActualSubRoot );
		
		if ( paSubRoot.second == NULL ){
			//no sub -root -object
			continue;
		}
		
		pMasterRoot->addSubRootObject( paSubRoot.first,
			createRootTree( paSubRoot.second ), uiActualSubRoot );
	}
	
	return pMasterRoot;
}


/**
 * @return the evalued positionslist of the original fib -object or NULL,
 * 	if no exists
 */
const cEvaluePositionList * cFibObjectFitnessAlgorithm::getOriginalPositionList() const{

	return pEvaluedPositionsDataOriginal;
}



/**
 * This method evalues the dimensions variables for the original fib -object.
 *
 * evalued class members are:
 * @see uiNumberOfDimensions;
 * @see pdDirectionMinimum;
 * @see pdDirectionMaximum;
 * @see pdDirectionScaling;
 * @see pdDirectionSize;
 * @see bStandardDimensionDomain
 * @see pVecDomainDimension
 *
 * @return true if the evaluation was successfull, else false
 */
bool cFibObjectFitnessAlgorithm::evalueOriginalDimensions() const{

	DEBUG_OUT_L2(<<"cFibObjectFitnessBasicAlgorithm::evalueOriginalDimensions() called"<<endl);
	
	if ( pdDirectionMinimum != NULL ){
		delete[] pdDirectionMinimum;
	}
	if ( pdDirectionMaximum != NULL ){
		delete[] pdDirectionMaximum;
	}
	if ( pdDirectionScaling != NULL ){
		delete[] pdDirectionScaling;
	}
	if ( pdDirectionSize != NULL ){
		delete[] pdDirectionSize;
	}
	if ( bStandardDimensionDomain && ( pVecDomainDimension != NULL )  ){
		delete pVecDomainDimension;
	}
	
	//evalue the dimensions of the original fib -object
	cDomains validDomains = const_cast<cFibObjectFitnessAlgorithm*>(
		this)->getOriginalFibObject()->getValidDomains();

	//evalue the (basic) area to check (the dimensions on which the original is defined)
	cDomain * pDomainDimension = validDomains.getDomainForElement( cTypeDimension() );
	
	bStandardDimensionDomain = false;
	if ( pDomainDimension == NULL ){
		pDomainDimension = cTypeDimension().getStandardDomain();
		bStandardDimensionDomain = true;
	}
	pVecDomainDimension = (cDomainVectorBasis*)pDomainDimension;
	
	uiNumberOfDimensions = pVecDomainDimension->getNumberOfElements();
	
	pdDirectionMinimum = new doubleFib[ uiNumberOfDimensions ];
	pdDirectionMaximum = new doubleFib[ uiNumberOfDimensions ];
	pdDirectionScaling = new doubleFib[ uiNumberOfDimensions ];
	pdDirectionSize    = new doubleFib[ uiNumberOfDimensions ];
	
	ulNumberOfPoints   = 1;
	
	for ( unsigned int uiActualDimension = 1;
			uiActualDimension <= uiNumberOfDimensions; uiActualDimension++ ){
		
		cDomain * pDirectionDomainElement = 
			pVecDomainDimension->getElementDomain( uiActualDimension );
		if ( ! pDirectionDomainElement->isScalar() ){
			//no scalar domain
			continue;
		}
		cDomainSingle * pDirectionDomain = ((cDomainSingle*)(pDirectionDomainElement));
		
		if ( pDirectionDomain == NULL ){
			pdDirectionMinimum[ uiActualDimension - 1 ] = 0;
			pdDirectionMaximum[ uiActualDimension - 1 ] = 0;
			pdDirectionScaling[ uiActualDimension - 1 ] = 1.0;
			pdDirectionSize[ uiActualDimension - 1 ]    = 1;
			continue;
		}
		
		pdDirectionMinimum[ uiActualDimension - 1 ] = pDirectionDomain->getMinimum();
		pdDirectionMaximum[ uiActualDimension - 1 ] = pDirectionDomain->getMaximum();
		
		string szDomainElementType = pDirectionDomain->getType();
		if ( ( szDomainElementType.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
					(szDomainElementType.compare( 0, 13, "DomainInteger" ) == 0) ){
			//cDomainIntegerBasis
			pdDirectionScaling[ uiActualDimension - 1 ] = ((cDomainIntegerBasis*)
				pDirectionDomain)->getScalingFactor();
			pdDirectionSize[ uiActualDimension - 1 ]    = 1 +
				(pDirectionDomain->getMaximum() - pDirectionDomain->getMinimum() ) /
				((cDomainIntegerBasis*)pDirectionDomain)->getScalingFactor();
		}else{
			pdDirectionScaling[ uiActualDimension - 1 ] = 1.0;
			pdDirectionSize[ uiActualDimension - 1 ]    = 1 +
				( pDirectionDomain->getMaximum() - pDirectionDomain->getMinimum() );
		}
		
		
		ulNumberOfPoints *= pdDirectionSize[ uiActualDimension - 1 ];

		DEBUG_OUT_L4(<<"Dimension "<<uiActualDimension<<" size="<< pdDirectionSize[ uiActualDimension - 1 ] <<" ."<<endl);
	}
	
	DEBUG_OUT_L2(<<"cFibObjectFitnessBasicAlgorithm::evalueOriginalDimensions() done"<<endl);
	
	return true;
}




