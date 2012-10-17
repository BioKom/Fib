/**
 * @class cEvaluePositionList
 * file name: cEvaluePositionList.cpp
 * @author Betti Oesterholz
 * @date 18.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the class for evaluing fib -objects and storing
 * the evalued data into a list.
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
 * This file contains the class for evaluing fib -objects and storing
 * the evalued data into a list (@see liEvaluedPositionData).
 * When the fib -object is evalued this method is called every time a
 * pointelement is reached. The parameter for the method are the
 * positionsvector of the point and properties of the point.
 */
/*
History:
18.04.2010  Oesterholz  created
05.07.2010  Oesterholz  distanceOfProperties() moved from
	cFibObjectFitnessBasicAlgorithm to hear
19.10.2010  Oesterholz  toFibObject() added
*/

#include "cEvaluePositionList.h"

#include "cPoint.h"
#include "cProperty.h"

using namespace fib;


/**
 * standrdconstructor
 */
cEvaluePositionList::cEvaluePositionList()
#ifdef TEST
	:ulCountOfEvalueMethodCalled( 0 ), lNumberOfTrueEvalueCalls( -1 )
#endif
	{
	//nothing to do
}


/**
 * The method with wich the evalued points with ther properties are
 * inserted. Everytime a point (to evalue) is reached in the
 * evaluation, this method is called with the position and the
 * properties of the point and stores the copies of this data
 * to the end of the list @see liEvaluedPositionData .
 *
 * @see liEvaluedPositionData
 * @param vPosition the position of the point, which is evalued
 * @param vProperties a list of the properties of the point
 */
bool cEvaluePositionList::evaluePosition( const cVectorPosition & vPosition,
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

	//replace variables with ther values
	pair< cVectorPosition, list< cVectorProperty > > paEvaluedData;
	paEvaluedData.first  = vPosition;
	paEvaluedData.second = vProperties;
	
	//replace variables with ther values
	{
		const unsignedIntFib uiNumberOfElements = paEvaluedData.first.getNumberOfElements();
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= uiNumberOfElements; uiActualElement++ ){
			
			if ( paEvaluedData.first.isVariable( uiActualElement ) ){
				paEvaluedData.first.setValue( uiActualElement,
					paEvaluedData.first.getValue( uiActualElement ) );
			}
		}
	}
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
	liEvaluedPositionData.push_back( paEvaluedData );

	return true;
}

/**
 * This method clears the data from the list with the evalued position data
 * liEvaluedPositionData. 
 * After the function call the liEvaluedPositionData list will be empty.
 *
 * @see liEvaluedPositionData
 */
void cEvaluePositionList::clear(){
	liEvaluedPositionData.clear();
}


/**
 * This function sorts the list liEvaluedPositionData of
 * positions with ther values.
 * It also sorts the property sublists.
 * A vector is lower if it has less elements than the other vector or
 * it's i'th element is lower und all j'th elements with i > j are
 * equal.
 * The positions with ther properties are sorted in the order as the
 * positionsvectors.
 * Propertyvectors with lower propertypvalues are sorted befor
 * propertyvectors with higer propertypvalues, independent of ther
 * elements.
 * Also equal/duplicate positions will be removed, ther properties will be
 * merged. Properties of a later positions in the given list will
 * overwrite properties earlier in the list, if neccessary.
 * Positions without porperties will be removed.
 *
 * @see liEvaluedPositionData
 * @param bDeleteEmptyPoints if true points without properties will be
 * 	deleted, else (if false) points without properties won't be deleted
 */
void cEvaluePositionList::sortPositionsData( bool bDeleteEmptyPoints ){

	return sortPositionsData( & liEvaluedPositionData, bDeleteEmptyPoints );
}



/**
 * This function sorts the given list of positions with ther values.
 * It also sorts the property sublists.
 * A vector is lower if it has less elements than the other vector or
 * it's i'th element is lower und all j'th elements with i > j are
 * equal.
 * The positions with ther properties are sorted in the order as the
 * positionsvectors.
 * Propertyvectors with lower propertypvalues are sorted befor
 * propertyvectors with higer propertypvalues, independent of ther
 * elements.
 * Also equal/duplicate positions will be removed, ther properties will be
 * merged. Properties of a later positions in the given list will
 * overwrite properties earlier in the list, if neccessary.
 * Positions without porperties will be removed.
 *
 * @param liEvaluedPositionData a pointer to the positionsdata to sort
 * @param bDeleteEmptyPoints if true points without properties will be
 * 	deleted, else (if false) points without properties won't be deleted
 */
void cEvaluePositionList::sortPositionsData( list< pair< cVectorPosition,
		list< cVectorProperty > > > * liEvaluedPositionData,
		bool bDeleteEmptyPoints ){
	
	if ( liEvaluedPositionData->empty() ){
		//nothing to do
		return;
	}
	liEvaluedPositionData->sort( lowerPositionPair );
	
	//eleminate duplicate positions
	list< pair< cVectorPosition, list< cVectorProperty > > >::iterator
		itrPosition = liEvaluedPositionData->begin();
	
	list< pair< cVectorPosition, list< cVectorProperty > > >::iterator
		itrPositionOld = itrPosition;
	itrPosition++;
	while ( itrPosition != liEvaluedPositionData->end() ){
		
		if ( itrPositionOld->first == itrPosition->first ){
			
			itrPositionOld->second = mergeProperties(
				itrPosition->second, itrPositionOld->second );
			
			itrPosition = liEvaluedPositionData->erase( itrPosition );
		}else{
			itrPositionOld = itrPosition;
			itrPosition++;
		}
	}
	//sort the property sublists
	if ( bDeleteEmptyPoints ){
		for ( itrPosition = liEvaluedPositionData->begin();
				itrPosition != liEvaluedPositionData->end(); ){
			
			if ( ! itrPosition->second.empty() ){
				itrPosition->second.sort( cVectorProperty::lowerPropertyVector );
				itrPosition++;
			}else{//no properties for the position -> remove it
				itrPosition = liEvaluedPositionData->erase( itrPosition );
			}
		}
	}else{
		for ( itrPosition = liEvaluedPositionData->begin();
				itrPosition != liEvaluedPositionData->end(); itrPosition++ ){
			
			if ( ! itrPosition->second.empty() ){
				itrPosition->second.sort( cVectorProperty::lowerPropertyVector );
			}
		}
	}
}


/**
 * This function compares two positions with ther properties.
 * For that just the positionsvectors are compared.
 * A (position)vector is lower if it has less elements than the other
 * vector or it's i'th element is lower and all j'th elements with i > j
 * are equal.
 *
 * @param paPosition1 the first pair of position with it's properties to compare
 * @param paPosition2 the second pair of position with it's properties to compare
 * @return true if the positionsvector of paPosition1 is lower than that
 * 	of paPosition2, else false
 */
bool cEvaluePositionList::lowerPositionPair(
		const pair< cVectorPosition, list< cVectorProperty > > & paPosition1,
		const pair< cVectorPosition, list< cVectorProperty > > & paPosition2 ){
	
	return cFibVector::lowerVector( paPosition1.first, paPosition2.first );
}


/**
 * This function mergs the two given propertylists.
 * All Properties of the second list liProperties2 that,
 * aren't overwritten by properties in the first propertylist,
 * liProperties1 are added to it.
 *
 * @param liProperties1 the propertielist to add to
 * @param liProperties2 the list with the properties to be added
 * @return a lis with the properties from the list liProperties1 and
 * 	the properties from the list liProperties2 which arn't overwirtten
 * 	by properties from list liProperties1
 */
list< cVectorProperty > cEvaluePositionList::mergeProperties(
		const list< cVectorProperty > & liProperties1,
		const list< cVectorProperty > & liProperties2 ){
	
	list< cVectorProperty > liVecProperties = liProperties1;
	
	for ( list< cVectorProperty >::const_iterator itrPropertyLi2 =
			liProperties2.begin(); itrPropertyLi2 != liProperties2.end();
			itrPropertyLi2++ ){
		
		bool bNotOverwritten = true;
#ifdef FEATURE_CHECK_OVERWRITTEN_WITH_IS_OVERWRITTEN_VECTOR
		if ( itrPropertyLi2->isOverwriting() ){
			for ( list<cVectorProperty>::const_iterator itrProperties = liProperties1.begin();
					itrProperties != liProperties1.end(); itrProperties++ ){
				if ( itrProperties->isOverwritenVector( *itrPropertyLi2 ) ){
					//the property is overwriten -> don't add it
					bNotOverwritten = false;
					break;
				}//else check the next propertyvector
			}
		}
#else //FEATURE_CHECK_OVERWRITTEN_WITH_IS_OVERWRITTEN_VECTOR
		cTypeProperty * typeOfProperty = (cTypeProperty*)(itrPropertyLi2->getElementType());
		/*if this is a property that overwrite properties of the same type
		-> delete properties that this overwrites from the property list*/
		list<cTypeProperty> liOverwritenTyps = typeOfProperty->getOverwritenTyps();
		delete typeOfProperty;
		
		if ( ! liOverwritenTyps.empty() ){
			for ( list<cVectorProperty>::const_iterator itrProperties = liProperties1.begin();
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
				}else{//the property is overwriten -> don't add it
					break;
				}
			}
		}
#endif //FEATURE_CHECK_OVERWRITTEN_WITH_IS_OVERWRITTEN_VECTOR
		if ( bNotOverwritten ){
			//add the property of this propertyelement to the propertylist
			liVecProperties.push_back( *itrPropertyLi2 );
		}
	}
	return liVecProperties;
}


/**
 * This function evalues the difference betwean the two propertielists.
 * Both propertylist have to be sorted in the order of lowerPropertyVector().
 *
 * @see cVectorProperty::lowerPropertyVector()
 * @see cVectorProperty::distanceOfProperty()
 * @see cVectorProperty::distanceOfPropertyToNull()
 * @param liPropertiesOriginal the positions with ther properties of the
 * 	original fib -object
 * @param liPropertiesGiven the positions with ther properties of the
 * 	given fib -object, for which the distance to the original fib -object
 * 	(liPropertiesOriginal) should be evalued
 * @return the sum of the distance of the properties of the points
 * 	(for missing properties, ther value to the nullvector will be added)
 */
doubleFib cEvaluePositionList::distanceOfProperties(
		const list< cVectorProperty > & liPropertiesOriginal,
		const list< cVectorProperty > & liPropertiesGiven ){
	
	double dDistance = 0;
	//compare the properties of the original and the given fib -object
	//beware of more propertyvectores of the same type

	list< cVectorProperty >::const_iterator itrPropertyOriginal =
		liPropertiesOriginal.begin();
	list< cVectorProperty >::const_iterator itrPropertyGiven =
		liPropertiesGiven.begin();
	
	while ( (itrPropertyOriginal != liPropertiesOriginal.end()) ||
			(itrPropertyGiven != liPropertiesGiven.end()) ){
		//for every property given
		
		if ( itrPropertyGiven == liPropertiesGiven.end() ){
			/*if equivallent property is not in the given fib -object
			-> compare original propertys properties against given nullvector*/
			dDistance += cVectorProperty::distanceOfPropertyToNull( *itrPropertyOriginal );
			
			itrPropertyOriginal++;
		}else if ( itrPropertyOriginal == liPropertiesOriginal.end() ){
			//for properties in the given fib -object but not in the original fib -object
			/*add differnce to original nullvector properties, if existing,
			or the nullvector*/
			dDistance += cVectorProperty::distanceOfPropertyToNull( *itrPropertyGiven );
			
			itrPropertyGiven++;
		}else if ( itrPropertyOriginal->getPropertyType() <
				itrPropertyGiven->getPropertyType() ){
			/*if equivallent property is not in the given fib -object
			-> compare original propertys properties against given nullvector*/
			//if no equivallent nullvector properties add to nullvector
			dDistance += cVectorProperty::distanceOfPropertyToNull( *itrPropertyOriginal );
			
			itrPropertyOriginal++;
		}else if ( itrPropertyGiven->getPropertyType() <
				itrPropertyOriginal->getPropertyType() ){
			dDistance += cVectorProperty::distanceOfPropertyToNull( *itrPropertyGiven );
			
			itrPropertyGiven++;
		}else{//both are equal ( itrPropertyOriginal->getPropertyType() == itrPropertyGiven->getPropertyType() )
			//if equivallent property is in the given fib -object
			dDistance += cVectorProperty::distanceOfProperty( *itrPropertyOriginal, *itrPropertyGiven );

			itrPropertyGiven++;
			itrPropertyOriginal++;
		}
	}

	return dDistance;
}


/**
 * @param vecPosition the position for the to create point
 * @param liProperties the properties of the create point
 * @return a fib -object with a point on the given position, wich is
 * 	an underobject of propertyelements, with the given properties
 */
cFibElement * cEvaluePositionList::toFibObject( const cVectorPosition & vecPosition,
		const list< cVectorProperty > & liProperties ){
	
	cFibElement * pFibObject = new cPoint( & vecPosition );
	//add the properties
	for ( list< cVectorProperty >::const_iterator
			itrProperty = liProperties.begin();
			itrProperty != liProperties.end(); itrProperty++ ){
		
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
		pFibObject = new cProperty( *itrProperty, pFibObject );
#else //FEATURE_SIMPLE_CONSTRUCTOR
		pFibObject = new cProperty( *itrProperty, NULL, NULL, pFibObject );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	}
	
	return pFibObject;
}



#ifdef TEST
/**
 * This function prints the given list of positions with ther values.
 * It also prints the property sublists.
 *
 * @param liEvaluedPositionData a reference to the positionsdata to print
 * @param strOutput the stream wher to print the data to
 */
void cEvaluePositionList::printPositionsData(
		const list< pair< cVectorPosition, list< cVectorProperty > > > & liEvaluedPositionData,
		ostream & strOutput ){
	
	for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
			itrActualPosition = liEvaluedPositionData.begin();
			itrActualPosition != liEvaluedPositionData.end(); itrActualPosition++ ){
		{
			strOutput<<"( ";
			const unsignedIntFib uiNumberOfElements = itrActualPosition->first.getNumberOfElements();
			for ( unsignedIntFib uiActualElement = 1;
					uiActualElement <= uiNumberOfElements; uiActualElement++ ){
				
				strOutput << itrActualPosition->first.getValue( uiActualElement )<<"; ";
			}
			strOutput<<")-> ";
		}
		
		for ( list<cVectorProperty>::const_iterator
					itrProperty = itrActualPosition->second.begin();
				itrProperty != itrActualPosition->second.end(); itrProperty++ ){
			
			strOutput<<itrProperty->getVectorType()<<"( ";
			const unsignedIntFib uiNumberOfElements = itrProperty->getNumberOfElements();
			for ( unsignedIntFib uiActualElement = 1;
					uiActualElement <= uiNumberOfElements; uiActualElement++ ){
				
				strOutput << itrProperty->getValue( uiActualElement )<<"; ";
			}
			strOutput<<"); ";
		}
		
		strOutput<<endl;
	}
}
#endif



