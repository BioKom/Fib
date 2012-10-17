/**
 * @file cOpAddBackgroundWichReduceMuchProperties
 * file name: cOpAddBackgroundWichReduceMuchProperties.cpp
 * @author Betti Oesterholz
 * @date 17.12.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This Operator adds a background which reduce much properties.
 *
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
 * This Operator searches for properties values in an random choosen
 * fib object, wich are used by a lot property elements.
 * It will chose the properties wich are most often used as the new
 * background for the fib element and remove the with the new background
 * not needed properties.
 *
 * @see cOperationFib
 * @see cOperation
 * @see cEnviroment
 * @see nEvalueFibObject::nNeededUnderobjects
 * @see nEvalueFibObject::nNeededUnderobjects::cEvalueUnderObjects
 */
/*
History:
17.12.2010  Oesterholz  created
*/


#include "cOpAddBackgroundWichReduceMuchProperties.h"

#include "cEnviroment.h"
#include "cObjectFitnessAlgorithm.h"
#include "cFibObjectFitnessAlgorithm.h"

#include "cFibIndividual.h"

#include "fibDatatyps.h"
#include "cFibElement.h"
#include "cRoot.h"
#include "cPoint.h"
#include "cProperty.h"
#include "cList.h"
#include "cVectorPosition.h"
#include "cVectorProperty.h"
#include "cTypeDimension.h"
#include "cDomains.h"
#include "cDomainVectorBasis.h"


#include "cEvalueUnderObjects.h"


#include <list>
#include <ctime>
#include <cmath>
#include <iostream>

using namespace std;
using namespace fib::algorithms::nEvalueFibObject::nNeededUnderobjects;
using namespace enviroment;
using namespace enviroment::fib;




/**
 * The standardconstructor for the operation.
 * It will create the operation, but won't start it.
 *
 * @param operationId the identifer for the operation
 */
cOpAddBackgroundWichReduceMuchProperties::cOpAddBackgroundWichReduceMuchProperties( const cOperationIdentifier & operationId ):
		cOperationFib( operationId ){
	//nothing to do
}


/**
 * Destructor of the class cOpAddBackgroundWichReduceMuchProperties.
 */
cOpAddBackgroundWichReduceMuchProperties::~cOpAddBackgroundWichReduceMuchProperties(){
	//nothing to do
}


/**
 * This method creats a new instance of this operator.
 * Beware: You have to delete the instance after usage.
 *
 * @param operationId the identifer for the operation
 * @return a pointer to a new instance of this operation
 */
cOpAddBackgroundWichReduceMuchProperties * cOpAddBackgroundWichReduceMuchProperties::createInstance(
		const cOperationIdentifier & operationId ) const{
	
	return new cOpAddBackgroundWichReduceMuchProperties( operationId );
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
bool cOpAddBackgroundWichReduceMuchProperties::run(){
	
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
	//evalue the dimensions of the original fib -object
	const cDomains validDomains = pFibObject->getValidDomains();
	const cDomainVectorBasis * pDomainDimension = (cDomainVectorBasis*)(
		validDomains.getDomainForElement( cTypeDimension() ));
	
	cEvalueUnderObjects evaluedData( pDomainDimension );
	//search for all properties and points and create a data object for them
	evaluedData.findAllFibElementData( *pFibObject );
	
	/*evalue fib-object:
	- stop at each property remember it and store it later to the position
	- if a point is reached store it to the object for the position on the
		last position, with all underobjects it is contained in and
		all its properties*/
	list<cVectorProperty> liVecProperties;
	list<char> liCFibElementTyps;
	liCFibElementTyps.push_back( 'p' );
	liCFibElementTyps.push_back( 'y' );
	
	const bool bObjectEvalued = pFibObject->evalueObject(
			evaluedData, 0, liVecProperties, liCFibElementTyps );
	if ( ! bObjectEvalued ){
		delete pIndividual;
		setIsRunning( false );
		return false;
	}
	
	/*marke not needed points and properties*/
#ifdef DEBUG
	cout<<endl<<"evalued data:"<<endl;
	evaluedData.print( cout );
	cout<<endl<<"evaluedData.markOverwrittenFibElements();"<<endl<<flush;
#endif //DEBUG
	evaluedData.markOverwrittenFibElements();
#ifdef DEBUG
	cout<<endl<<"marked data:"<<endl;
	evaluedData.print( cout );
	cout<<endl;
#endif //DEBUG
	//evalue how often the properties are needed
	DEBUG_OUT_L2(<<">>> bUnderobjectRemoved = countPropertyElementsOverwritebelByBg();<<< " <<endl<<flush);
	list< pair< cVectorProperty, unsigned long> > liCountedProperties =
		evaluedData.countPropertyElementsOverwritebelByBg();
	
	if ( liCountedProperties.empty() ){
		//no properties to replace with the background
		delete pIndividual;
		setIsRunning( false );
		return true;
	}
	//find the most needed properties
	list< pair< cVectorProperty, unsigned long> > liMostNeededProperties;
	//add one property
	liMostNeededProperties.push_back( liCountedProperties.front() );
	liCountedProperties.pop_front();
	
	for ( list< pair< cVectorProperty, unsigned long> >::iterator
			itrPropertyCheck = liCountedProperties.begin();
			itrPropertyCheck != liCountedProperties.end(); itrPropertyCheck++ ){
		
		//check if the property is needed mor often as a property it overwrites
		
		//an property that overwrits the actual property exists in the background properties
		bool bOverwritingPropertyExists = false;
		for ( list< pair< cVectorProperty, unsigned long> >::iterator
				itrPropertyBg = liMostNeededProperties.begin();
				itrPropertyBg != liMostNeededProperties.end(); itrPropertyBg++ ){
			
			if ( itrPropertyBg->first.isOverwritenVector( itrPropertyCheck->first ) ){
				//if the property is overwritten compare how often they are needed
				bOverwritingPropertyExists = true;
				if ( itrPropertyBg->second < itrPropertyCheck->second ){
					/*the checked property is nedded more often than the actual
					background property -> replace the background property with
					the checked proeprty*/
					itrPropertyBg = liMostNeededProperties.erase( itrPropertyBg );
					liMostNeededProperties.push_front( *itrPropertyCheck );
				}
				//stop at the first overwriting property
				break;
			}
		}
		if ( ! bOverwritingPropertyExists ){
			/*no overwriting background property exists
			->add the checked property to the background proeprties*/
			liMostNeededProperties.push_front( *itrPropertyCheck );
		}
	}
	
	
	/*create background object for the most needed properties
	and insert its data into the evalued data*/
	cVectorPosition positionBackground( 0 );
	cFibElement * pBackgroundFibObject = new cPoint( &positionBackground );
	
	cPositionData & positionBgData = evaluedData.mapEvaluedPositionData[
		positionBackground ];
		
	//insert position point data
	positionBgData.liData.push_back( cPositionPointData() );
	cPositionPointData & positionPointData = positionBgData.liData.back();
		
	cPointData & pointData = evaluedData.mapPointData[
		((cPoint*)pBackgroundFibObject) ];
	positionPointData.pPoint = &pointData;
	pointData.liPositionData.push_back( &positionBgData );
		
	//insert property data
	for ( list< pair< cVectorProperty, unsigned long> >::iterator
			itrPropertyBg = liCountedProperties.begin();
			itrPropertyBg != liCountedProperties.end(); itrPropertyBg++ ){
		
		pBackgroundFibObject = new cProperty( itrPropertyBg->first,
			pBackgroundFibObject );
		
		cPropertyData & propertyData = evaluedData.mapPropertyData[
			(cProperty*)pBackgroundFibObject ];
		positionPointData.liProperties.push_back(
			cPositionPropertieData(
				&propertyData, itrPropertyBg->first ) );
		propertyData.liPositionData.push_back( &positionBgData );
	}
	
#ifdef DEBUG
	cout<<endl<<"evalued data:"<<endl;
	evaluedData.print( cout );
	cout<<endl<<"evaluedData.markOverwrittenFibElements();"<<endl<<flush;
#endif //DEBUG
	evaluedData.markOverwrittenFibElements();
#ifdef DEBUG
	cout<<endl<<"marked data:"<<endl;
	evaluedData.print( cout );
	cout<<endl;
#endif //DEBUG

	//remove points (on all positions) without properties (which are marked as not needed)
		//remove all underobjects with yust obsolete points
	//create the underobject tree
	cUnderobject<cPointData> * pRootUnderobject =
		evaluedData.createUnderobjectTree();
	
	//evalue removebel underobjects
	pRootUnderobject->evalueOverwritten();
	list<unsignedIntFib> liRemovebelUnderobjects =
		pRootUnderobject->getHighestOverwritten();
	delete pRootUnderobject;
	
	bool bSomethingRemoved = false;
	if ( ! liRemovebelUnderobjects.empty() ){

		DEBUG_OUT_L2(<<"ther are "<<liRemovebelUnderobjects.size()<<" underobjects to remove"<<endl<<flush);
		
		//remove the removebel underobjects (highest to the back)
		liRemovebelUnderobjects.sort();
		DEBUG_OUT_L2(<<"removing the underobjects: "<<flush);
		while ( ! liRemovebelUnderobjects.empty() ){
			
			DEBUG_OUT_L2(<<liRemovebelUnderobjects.back()<<" "<<flush);
			const bool bActualUnderobjectRemoved =
				pFibObject->removeObject( liRemovebelUnderobjects.back(), true, true );
			
			DEBUG_OUT_L2(<<(bActualUnderobjectRemoved?"; ":" fail ; ")<<flush);
			
			bSomethingRemoved = bSomethingRemoved || bActualUnderobjectRemoved;
			
			liRemovebelUnderobjects.pop_back();
		}
	}

	/*remove all properties which aren't on any positions(which are marked as not needed);
	beware: check if an property was removed befor with an underobject;
	get all (remaining) properties in the fib-object and remove them, if they are not needed*/
	for ( cFibElement * pActualProperty = pFibObject->getNextFibElement( 'y' );
			pActualProperty != NULL; ){
		
		if ( ! (evaluedData.mapPropertyData[ ((cProperty*)pActualProperty)
				].bPropertyNeeded) ){
			//the property is not needed -> delete it
			cFibElement * pNextProperty = pActualProperty->getNextFibElement( 'y' );
			pActualProperty->removeElement();
			pActualProperty = pNextProperty;
			bSomethingRemoved = true;
		}else{
			pActualProperty = pActualProperty->getNextFibElement( 'y' );
		}
	}
	
	//insert the created background object
	DEBUG_OUT_L2(<<"inserting background object"<<endl<<flush);
	
	bool bObjectInserted = false;
	cList * pNextList = ((cList*)( pFibObject->getNextFibElement( 'l' )) );
	if ( pNextList ){
		//add line to the end of the founded listelement
		bObjectInserted = pNextList->addUnderobject( pBackgroundFibObject, 1 );
		
	}else{//create listelement as main -fib -object
		bObjectInserted = pFibObject->insertObjectInElement(
			pBackgroundFibObject, 'r', 0, true, true );
	}
	if ( ! bObjectInserted ){
		pBackgroundFibObject->deleteObject();
		delete pIndividual;

		setIsRunning( false );
		
		DEBUG_OUT_L1(<<getName()<<"::run() done generated object could not be inserted"<<endl<<flush);
		return false;
	}

	
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
string cOpAddBackgroundWichReduceMuchProperties::getName() const{
	return "cOpAddBackgroundWichReduceMuchProperties";
}





