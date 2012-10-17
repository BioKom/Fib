/**
 * @file nReduceFibObject
 * file name: nReduceFibObject.h
 * @author Betti Oesterholz
 * @date 14.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies functions for reducing fib -objects.
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
 * This header specifies functions for reducing fib -objects.
 * This is done be removing Fib -elements or / and fib -underobjects from
 * fib objects.
 */
/*
History:
14.06.2010  Oesterholz  created
11.09.2010  Oesterholz  FEATURE_REMOVE_TOPMOST_UNDEROBJECTS implemented
20.11.2010  Oesterholz  removeOverwrittenProperies() and namespace
	nRemoveOverwrittenUnderObjects with help classes added
05.12.2010  Oesterholz  FEATURE_STORE_EVALUED_UNDEROBJECT_NUMBERS added
*/


#include "fibDatatyps.h"
#include "cPoint.h"
#include "cProperty.h"
#include "iEvalueFibElement.h"
#include "cEvaluePositionList.h"
#include "cFibVector.h"
#include "cVectorPosition.h"
#include "cVectorProperty.h"
#include "cTypeDimension.h"

#include "cEvalueUnderObjects.h"
#include "cUnderobject.h"
#include "cPointData.h"


#ifndef ___N_REDUCE_FIB_OBJECT_CPP__
#define ___N_REDUCE_FIB_OBJECT_CPP__


#ifndef ___N_REDUCE_FIB_OBJECT_H__ //don't include non template impelemtations into the header

#include "nReduceFibObject.h"

#include <map>
#include <set>

using namespace fib::algorithms::nReduceFibObject;
using namespace fib::algorithms::nEvalueFibObject;
using namespace fib;


/*private (helper) namespace functions and classes for the
removeOverwrittenUnderObjects() function*/
namespace fib{
namespace algorithms{
namespace nReduceFibObject{
namespace nRemoveOverwrittenUnderObjects{


	/**
	 * @class cPositionUnderObjectsData
	 * This is a datastructur for storing the positions with ther properties
	 * and the number of underobjects in which they are contained.
	 */
	class cPositionUnderObjectsData{
	public:
		/**
		 * The position for the data.
		 */
		cVectorPosition position;
		
		/**
		 * The properties on the position.
		 */
		list< cVectorProperty > liProperties;
		
		/**
		 * A list with the underobjects which contain the position /point for
		 * the position.
		 * The number of the higher underobjects should stand at the front
		 * of the list.
		 *
		 * @see cFibElement::elementPointToObjectPoints()
		 */
		list<unsignedIntFib> liUnderObjects;
		
		
		/**
		 * @return if this position is needed(has properties) true, else false
		 */
		bool isNeeded() const{
			return ( ! liProperties.empty() );
		}
		
	};
	
	
	/**
	 * @class cEvalueUnderObjects
	 * This is a helpclass to evalue the positions with ther properties and
	 * the number of underobjects in which they are contained.
	 */
	class cEvalueUnderObjects: public iEvalueFibElement{
	public:
		
		
		/**
		 * The list for the evalued fib -object data.
		 *
		 * The first pairelement is the position and the second are the
		 * properties for the position.
		 */
		list< cPositionUnderObjectsData > liEvaluedPositionData;
		
#ifdef FEATURE_STORE_EVALUED_UNDEROBJECT_NUMBERS
		private:
		
		/**
		 * The map with the evalued underobjects for the points.
		 * For faster evaluation, so they will not needed to evalue
		 * them again while reevaluing a point.
		 */
		map< cFibElement*, list<unsignedIntFib> > mapLiUnderobjects;
		
		public:
#endif //FEATURE_STORE_EVALUED_UNDEROBJECT_NUMBERS
		
		
		/**
		 * The method with wich the evalued fib -elements with ther properties
		 * are inserted /evalued. Everytime a fib -element of the choosen type
		 * (to evalue) is reached in the evaluation, this method is called with
		 * the fib -element and the properties of the fib -element.
		 *
		 * @param pFibElement the fib -element to evalue
		 * @param vProperties a list with the properties of the fib -element
		 */
		bool evalueElement( cFibElement & fibElement,
				const list<cVectorProperty> & vProperties ){
			
			if ( fibElement.getType() != 'p' ){
				//can just evalue point elements
				return false;
			}
			DEBUG_OUT_L2(<<"evalueElement() called for element "<<flush<<fibElement.getNumberOfElement()<<"  "<<flush);
#ifdef DEBUG
			for ( cFibElement * pSuperiorElement = & fibElement;
					pSuperiorElement != NULL;
					pSuperiorElement = pSuperiorElement->getSuperiorFibElement() ){
				
				DEBUG_OUT_L2(<<pSuperiorElement->getType()<<"->");
			}
			DEBUG_OUT_L2(<<endl<<flush);
#endif
			/*for the given pointobject -insert it's position, properties and
			number of the underobjects, in which it is contained, to the list*/
			cVectorPosition * pVecPosition = ((cPoint*)&fibElement)->getPosition();
			if ( pVecPosition == NULL ){
				//point not evalued
				return true;
			}
			cPositionUnderObjectsData positionObject;
			
			positionObject.position = *pVecPosition;
			positionObject.liProperties = vProperties;

			DEBUG_OUT_L2(<<"evaluing the underobjects "<<endl<<flush);

#ifdef FEATURE_STORE_EVALUED_UNDEROBJECT_NUMBERS
			map<cFibElement*, list<unsignedIntFib> >::iterator itrPoint =
				mapLiUnderobjects.find( & fibElement );
			if ( itrPoint == mapLiUnderobjects.end() ){
				//point not found ->evalue it's underobjects
				positionObject.liUnderObjects = fibElement.getObjectPointsForElement(
					& fibElement, true );
				mapLiUnderobjects.insert(
					make_pair( & fibElement, positionObject.liUnderObjects ) );
			}else{
				//point found -> use the stored underobjects
				positionObject.liUnderObjects = itrPoint->second;
			}
			
#else //FEATURE_STORE_EVALUED_UNDEROBJECT_NUMBERS
			positionObject.liUnderObjects = fibElement.getObjectPointsForElement(
				& fibElement, true );
#endif //FEATURE_STORE_EVALUED_UNDEROBJECT_NUMBERS

			DEBUG_OUT_L2(<<"replace variables with ther values"<<endl<<flush);
			//replace variables with ther values
			{
				const unsignedIntFib uiNumberOfElements = positionObject.position.getNumberOfElements();
				for ( unsignedIntFib uiActualElement = 1;
						uiActualElement <= uiNumberOfElements; uiActualElement++ ){
					
					if ( positionObject.position.isVariable( uiActualElement ) ){
						positionObject.position.setValue( uiActualElement,
							positionObject.position.getValue( uiActualElement ) );
					}
				}
			}
			//replace variables with ther values in the properties
			for ( list<cVectorProperty>::iterator
						itrProperty = positionObject.liProperties.begin();
					itrProperty != positionObject.liProperties.end(); itrProperty++ ){
				
				const unsignedIntFib uiNumberOfElements = itrProperty->getNumberOfElements();
				for ( unsignedIntFib uiActualElement = 1;
						uiActualElement <= uiNumberOfElements; uiActualElement++ ){
					
					if ( itrProperty->isVariable( uiActualElement ) ){
						itrProperty->setValue( uiActualElement,
							itrProperty->getValue( uiActualElement ) );
					}
				}
			}
			liEvaluedPositionData.push_back( positionObject );
			DEBUG_OUT_L2(<<"evalueElement() done"<<endl<<flush);
			return true;
		}
		
	};//class cEvalueUnderObjects
	
	
	/**
	 * This function compares two cPositionUnderObjectsData objects
	 * by comparing ther positionsvectoren.
	 * A vector is lower if it has less elements than the other vector or
	 * it's i'th element is lower and all j'th elements with i > j are equal.
	 *
	 * @param positiondata1 the first cPositionUnderObjectsData to compare
	 * @param positiondata2 the second cPositionUnderObjectsData to compare
	 * @return true if the positionsvector of positiondata1 is lower than that
	 * 	of positiondata2, else false
	 */
	bool lowerPositionVector(
			const cPositionUnderObjectsData & positiondata1,
			const cPositionUnderObjectsData & positiondata2 ){
		
		return positiondata1.position < positiondata2.position;
	}
	
	
	/**
	 * This function eleminates the properties of the first given
	 * propertylists which are overwritten by properties of the
	 * secound given propertielist.
	 * If bouth propertielist are the same list, nothing is done.
	 *
	 * @param liProperties1 the propertielist
	 * @param liProperties2 the list with the properties to eleminate
	 */
	void eleminateProperties(
			list< cVectorProperty > & liProperties1,
			list< cVectorProperty > & liProperties2 ){
		
		if ( ( & liProperties1) == ( & liProperties2 ) ){
			return;
		}
		
		for ( list< cVectorProperty >::iterator itrPropertyLi2 =
				liProperties2.begin(); itrPropertyLi2 != liProperties2.end();
				itrPropertyLi2++ ){
		
			/*if this is a property that overwrite properties of the same type
			-> delete properties that this overwrites from the property list*/
#ifdef FEATURE_CHECK_OVERWRITTEN_WITH_IS_OVERWRITTEN_VECTOR
			if ( itrPropertyLi2->isOverwriting() ){
				for ( list<cVectorProperty>::iterator itrProperties = liProperties1.begin();
						itrProperties != liProperties1.end(); ){
					
					if ( itrPropertyLi2->isOverwritenVector( *itrProperties ) ){
						//the property is overwriten -> remove it
						liProperties1.erase( itrProperties );
						break;
					}else{
						//check the next propertyvector
						itrProperties++;
					}
				}
			}
#else //FEATURE_CHECK_OVERWRITTEN_WITH_IS_OVERWRITTEN_VECTOR
			cTypeProperty * typeOfProperty = (cTypeProperty*)(itrPropertyLi2->getElementType());
			list<cTypeProperty> liOverwritenTyps = typeOfProperty->getOverwritenTyps();
			delete typeOfProperty;
			bool bNotOverwritten = true;
			if ( ! liOverwritenTyps.empty() ){
				for ( list<cVectorProperty>::iterator itrProperties = liProperties1.begin();
						itrProperties != liProperties1.end(); ){
					
					typeOfProperty = (cTypeProperty*)(itrProperties->getElementType());
					
					for ( list<cTypeProperty>::iterator itrPropertyType = liOverwritenTyps.begin();
							itrPropertyType != liOverwritenTyps.end(); itrPropertyType++ ){
						
						if ( typeOfProperty->equalElementType( *itrPropertyType ) ){
							bNotOverwritten = false;
							break;
						}
					}
					delete typeOfProperty;
					if ( bNotOverwritten ){
						//check the next propertyvector
						itrProperties++;
					}else{//the property is overwriten -> remove it
						liProperties1.erase( itrProperties );
						break;
					}
				}
			}
#endif //FEATURE_CHECK_OVERWRITTEN_WITH_IS_OVERWRITTEN_VECTOR
		}
	}


};//end namespace nRemoveOverwrittenUnderObjects
};//end namespace nReduceFibObject
};//end namespace algorithms
};//end namespace fib


using namespace nRemoveOverwrittenUnderObjects;


/**
 * This function removes from the given fib -object all underobjects
 * which point properties are overwritten and so not necessary.
 *
 * @param fibElementToReduce a reference to the fib -object to reduce;
 * 	this fib -object will be changed
 * @return if the given fib -object was reduced true, else (the
 * 	fib -object wasn't changed) false
 */
bool fib::algorithms::nReduceFibObject::removeOverwrittenUnderObjects(
		cFibElement & fibElementToReduce ){
		
	DEBUG_OUT_L2(<<"removeOverwrittenUnderObjects() called"<<endl<<flush);

	//evalue the fib -object
	nRemoveOverwrittenUnderObjects::cEvalueUnderObjects evaluedData;
	
	const bool bObjectEvalued =
		fibElementToReduce.evalueObjectSimple( evaluedData );
	if ( ! bObjectEvalued ){
		return false;
	}
	//remove all properties which are overwritten from the evalued list
	DEBUG_OUT_L2(<<"sorting evalued data"<<endl<<flush);
	evaluedData.liEvaluedPositionData.sort( lowerPositionVector );
	
	DEBUG_OUT_L2(<<"eleminating overwritten properties"<<endl<<flush);
	for ( list< cPositionUnderObjectsData >::iterator itrPosition =
			evaluedData.liEvaluedPositionData.begin();
			itrPosition != evaluedData.liEvaluedPositionData.end();
			itrPosition++ ){
		
		//for every same position after the actual positionsvector
		list< cPositionUnderObjectsData >::iterator itrPosition2 = itrPosition;
		itrPosition2++;
		for ( ; ( itrPosition2 != evaluedData.liEvaluedPositionData.end() ) &&
				( itrPosition->position == itrPosition2->position ) ;
				itrPosition2++ ){
			
			eleminateProperties( itrPosition->liProperties,
				itrPosition2->liProperties );
		}
	}
	
#ifdef FEATURE_REMOVE_TOPMOST_UNDEROBJECTS
	//create the underobject tree
	nNeededUnderobjects::cUnderobject<cPositionUnderObjectsData> rootUnderobject( 1 );
	
	for ( list< cPositionUnderObjectsData >::iterator itrPosition =
			evaluedData.liEvaluedPositionData.begin();
			itrPosition != evaluedData.liEvaluedPositionData.end();
			itrPosition++ ){
		
		rootUnderobject.addPoint( *itrPosition );
	}
	//evalue removebel underobjects
	rootUnderobject.evalueOverwritten();
	list<unsignedIntFib> liRemovebelUnderobjects =
		rootUnderobject.getHighestOverwritten();
	
#else //FEATURE_REMOVE_TOPMOST_UNDEROBJECTS
	/*for every position evalued -> add all underobject to the set of possible underobjects
	-> and if the position has properties add all underobject to the set of not removebel underobjects
	 */
	DEBUG_OUT_L2(<<"evaluing possible and not removebel underobjects"<<endl<<flush);
	set<unsignedIntFib> setPossibleUnderobjects;
	set<unsignedIntFib> setNotRemovebelUnderobjects;
	
	for ( list< cPositionUnderObjectsData >::const_iterator itrPosition =
			evaluedData.liEvaluedPositionData.begin();
			itrPosition != evaluedData.liEvaluedPositionData.end();
			itrPosition++ ){
		
		setPossibleUnderobjects.insert( itrPosition->liUnderObjects.begin(),
			itrPosition->liUnderObjects.end() );
		
		if ( ! ( itrPosition->liProperties.empty() ) ){
			
			setNotRemovebelUnderobjects.insert( itrPosition->liUnderObjects.begin(),
				itrPosition->liUnderObjects.end() );
		}
	}
	
	/*create the set of removebel underobjects, by removing from the set of
	possible underobjects all not removebel underobjects*/
	DEBUG_OUT_L2(<<"evaluing underobjects to remove"<<endl<<flush);
	list<unsignedIntFib> liRemovebelUnderobjects(
		setPossibleUnderobjects.begin(), setPossibleUnderobjects.end() );
	
	for ( set<unsignedIntFib>::const_iterator
			itrPosition = setNotRemovebelUnderobjects.begin();
			itrPosition != setNotRemovebelUnderobjects.end(); itrPosition++ ){
	
		liRemovebelUnderobjects.remove( *itrPosition );
	}
#endif //FEATURE_REMOVE_TOPMOST_UNDEROBJECTS
	
	if ( liRemovebelUnderobjects.empty() ){
		DEBUG_OUT_L2(<<"no underobjects to remove"<<endl<<flush);
		return false;
	}
	DEBUG_OUT_L2(<<"ther are "<<liRemovebelUnderobjects.size()<<" underobjects to remove"<<endl<<flush);
	
	//remove the removebel underobjects (highest to the back)
	liRemovebelUnderobjects.sort();
	DEBUG_OUT_L2(<<"removing the underobjects: "<<flush);
	bool bUnderobjectRemoved = false;
	while ( ! liRemovebelUnderobjects.empty() ){
		
		DEBUG_OUT_L2(<<liRemovebelUnderobjects.back()<<" "<<flush);
		const bool bActualUnderobjectRemoved =
			fibElementToReduce.removeObject( liRemovebelUnderobjects.back(), true, true );
		
		DEBUG_OUT_L2(<<(bActualUnderobjectRemoved?"; ":" fail ; ")<<flush);
		
		bUnderobjectRemoved = bUnderobjectRemoved || bActualUnderobjectRemoved;
		
		liRemovebelUnderobjects.pop_back();
	}
	
	DEBUG_OUT_L2(<<endl<<"removeOverwrittenUnderObjects() done"<<endl<<flush);
	return bUnderobjectRemoved;
}




/**
 * This function removes from the given fib -object all underobjects
 * which point properties are overwritten or overwrite the background but
 * are equal to it, ther are not necessary. Than it removes all all
 * properties, which are not are not necessary
 *
 * @param fibObjectToReduce a reference to the fib -object to reduce;
 * 	this fib -object will be changed
 * @return if the given fib -object was reduced true, else (the
 * 	fib -object wasn't changed) false
 */
bool fib::algorithms::nReduceFibObject::removeOverwrittenProperties(
		cFibElement & fibObjectToReduce ){
	
	DEBUG_OUT_L2(<<"removeOverwrittenProperies() called"<<endl<<flush);

	//evalue the fib -object
	//evalue the dimensions of the original fib -object
	const cDomains validDomains = fibObjectToReduce.getValidDomains();
	const cDomainVectorBasis * pDomainDimension = (cDomainVectorBasis*)(
		validDomains.getDomainForElement( cTypeDimension() ));
	
	nNeededUnderobjects::cEvalueUnderObjects evaluedData( pDomainDimension );
	//search for all properties and points and create a data object for them
	evaluedData.findAllFibElementData( fibObjectToReduce );
	
	/*evalue fib-object:
	- stop at each property remember it and store it later to the position
	- if a point is reached store it to the object for the position on the
		last position, with all underobjects it is contained in and
		all its properties*/
	list<cVectorProperty> liVecProperties;
	list<char> liCFibElementTyps;
	liCFibElementTyps.push_back( 'p' );
	liCFibElementTyps.push_back( 'y' );
	
	const bool bObjectEvalued = fibObjectToReduce.evalueObject(
			evaluedData, 0, liVecProperties, liCFibElementTyps );
	if ( ! bObjectEvalued ){
		return false;
	}
	
	
	/*for all positions:
		- remove all overwritten properties
		- remove all properties, wich overwrites the background, but are also equal to it
	
	for this as long as ther are changes:
		- mark all point properties which are not needed, because ther are overwritten
		- if changes:
			- mark all properties which are not needed
		- mark all properties which are not needed, because of the background
		- if changes: mark all properties which are not needed
	mark all points which are not needed
	*/
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
	
	
	//remove points(on all positions) without properties(which are marked as not needed)
		//remove all underobjects with yust obsolete points
	//create the underobject tree
	nNeededUnderobjects::cUnderobject<cPointData> * pRootUnderobject =
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
				fibObjectToReduce.removeObject( liRemovebelUnderobjects.back(), true, true );
			
			DEBUG_OUT_L2(<<(bActualUnderobjectRemoved?"; ":" fail ; ")<<flush);
			
			bSomethingRemoved = bSomethingRemoved || bActualUnderobjectRemoved;
			
			liRemovebelUnderobjects.pop_back();
		}
	}

	/*remove all properties which aren't on any positions(which are marked as not needed);
	beware: check if an property was removed befor with an underobject;
	get all (remaining) properties in the fib-object and remove them, if they are not needed*/
	for ( cFibElement * pActualProperty = fibObjectToReduce.getNextFibElement( 'y' );
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
	
	DEBUG_OUT_L2(<<"removeOverwrittenProperies() done"<<endl<<flush);
	return bSomethingRemoved;
}



#endif //___N_REDUCE_FIB_OBJECT_H__

#endif //___N_REDUCE_FIB_OBJECT_CPP__





