/**
 * @class cEvalueUnderObjects
 * file name: cEvalueUnderObjects.cpp
 * @author Betti Oesterholz
 * @date 08.12.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This is a helpclass to evalue the positions with ther properties and
 * the number of underobjects in which they are contained.
 *
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
 * This is a helpclass to evalue the positions with ther properties and
 * the number of underobjects in which they are contained.
 *
 */
/*
History:
08.12.2010  Oesterholz  created
*/

//TODO weg
//#define DEBUG



#include "cEvalueUnderObjects.h"

using namespace fib::algorithms::nEvalueFibObject::nNeededUnderobjects;


/**
 * standardconstructor
 *
 * @param pInVecDomainDimension The dimension domain for the positions.
 * 	No position outside this domain will be added.
 * 	If NULL no check will be executed. (@see pVecDomainDimension)
 */
cEvalueUnderObjects::cEvalueUnderObjects(
		const cDomainVectorBasis * pInVecDomainDimension ){
	
	if ( pInVecDomainDimension ){
		pVecDomainDimension = pInVecDomainDimension->clone();
	}else{
		pVecDomainDimension = NULL;
	}
	liCFibElementTyps.push_back( 'p' );
	liCFibElementTyps.push_back( 'y' );
}


/**
 * desconstructor
 */
cEvalueUnderObjects::~cEvalueUnderObjects(){
	
	if ( pVecDomainDimension ){
		delete pVecDomainDimension;
	}
}


/**
 * The method with wich the evalued fib -elements with ther properties
 * are inserted /evalued. Everytime a fib -element of the choosen type
 * (to evalue) is reached in the evaluation, this method is called with
 * the fib -element and the properties of the fib -element.
 *
 * @param pFibElement the fib -element to evalue
 * @param vProperties a list with the properties of the fib -element
 */
bool cEvalueUnderObjects::evalueElement( cFibElement & fibElement,
		const list<cVectorProperty> & vProperties ){
	
	DEBUG_OUT_L2(<<"evalueElement() called for element "<<flush<<fibElement.getNumberOfElement()<<" (type="<<fibElement.getType()<<")  "<<flush);
	
	/*evalue fib-object:
	- stop at each property remember it and store it later to the position
	- if a point is reached store it to the object for the position on the
		last position, with all underobjects it is contained in and
		all it's properties*/
	
	if ( fibElement.getType() == 'y' ){
		//propertyelement evalued
		DEBUG_OUT_L2(<<"propertyelement evalued ("<<fibElement.getNumberOfElement()<<")"<<endl<<flush);
		
		pair< cProperty *, cVectorProperty > paProperty(
			((cProperty*)&fibElement), cVectorProperty( 0, (cFibElement*)NULL ) );
		
		cVectorProperty * pVecProperty = (paProperty.first)->getProperty();
		if ( pVecProperty == NULL ){
			//no property evalued
			return true;
		}
		//replace variables with ther values in the properties
		cVectorProperty vecProperty( * pVecProperty );
		
		const unsignedIntFib uiNumberOfElements = vecProperty.getNumberOfElements();
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= uiNumberOfElements; uiActualElement++ ){
			
			if ( vecProperty.isVariable( uiActualElement ) ){
				vecProperty.setValue( uiActualElement,
					vecProperty.getValue( uiActualElement ) );
			}
		}
		paProperty.second = vecProperty;
		liActualProperties.push_back( paProperty );
		
		//continue evalueation of the fib object
		cFibElement * pSubObject = fibElement.getNextFibElement();
		if ( pSubObject == NULL ){
			//Error: Propety (fib-branch) without subobject
			DEBUG_OUT_L2(<<"Error: Propety (fib-branch) without subobject"<<endl<<flush);
			return false;
		}
		list<cVectorProperty> liVecProperties;
		DEBUG_OUT_L2(<<"evaluating subobject"<<endl<<flush);
		const bool bEvalued = pSubObject->evalueObject( *this, 0,
			liVecProperties, liCFibElementTyps );
		
		//remove added property
		liActualProperties.pop_back();
		DEBUG_OUT_L2(<<"evalueElement() done, evaluating subobject"<<endl<<flush);
		return bEvalued;
		
	}else if ( fibElement.getType() == 'p' ){
		//pointelement evalued
		DEBUG_OUT_L2(<<"pointelement evalued"<<endl<<flush);

		/*for the given pointobject -insert it's position, properties and
		number of the underobjects, in which it is contained, to the list*/
		cVectorPosition * pVecPosition = ((cPoint*)&fibElement)->getPosition();
		if ( pVecPosition == NULL ){
			//point not evalued -> discarde actual properties
			return true;
		}
		
		DEBUG_OUT_L2(<<"replace position variables with ther values"<<endl<<flush);
		cVectorPosition vecPosition( * pVecPosition );
		//replace variables with ther values
		{
			const unsignedIntFib uiNumberOfElements = vecPosition.getNumberOfElements();
			for ( unsignedIntFib uiActualElement = 1;
					uiActualElement <= uiNumberOfElements; uiActualElement++ ){
				
				if ( vecPosition.isVariable( uiActualElement ) ){
					vecPosition.setValue( uiActualElement,
						vecPosition.getValue( uiActualElement ) );
				}
			}
		}
		//check if position is inside dimension bounderies
		if ( pVecDomainDimension ){
			//check if inside bounderies
			if ( ( vecPosition.getNumberOfElements() != 0 ) &&
				( ! ( pVecDomainDimension->isElement( vecPosition ) ) ) ){
				//position outside bounderies -> don't insert it
				return true;
			}
		}
		
	//add points and ther properties to the position data
		//find or add the position in the evalued position data (mapEvaluedPositionData)
		cPositionData & positionData = mapEvaluedPositionData[ vecPosition ];
		
		//insert position point data
		positionData.liData.push_back( cPositionPointData() );
		cPositionPointData & positionPointData = positionData.liData.back();
		
		cPointData & pointData = mapPointData[ ((cPoint*)&fibElement) ];
		positionPointData.pPoint = &pointData;
		pointData.liPositionData.push_back( &positionData );
		
		//insert property data
		for ( list< pair< cProperty *, cVectorProperty > >::iterator
				itrProperty = liActualProperties.begin();
				itrProperty != liActualProperties.end(); itrProperty++ ){
			
			cPropertyData & propertyData = mapPropertyData[ itrProperty->first ];
			positionPointData.liProperties.push_back(
				cPositionPropertieData(
					&propertyData, itrProperty->second ) );
			propertyData.liPositionData.push_back( &positionData );
		}
		
	}else{
		//can just evalue point elements
		DEBUG_OUT_L2(<<"evalueElement() done; can just evalue point elements"<<endl<<flush);
		return false;
	}
	DEBUG_OUT_L2(<<"evalueElement() done"<<endl<<flush);
	return true;
}


/**
 * This method finds all the property- and pointelements in the given
 * fib -object and adds them to the datasets.
 *
 * @see mapPropertyData
 * @see mapPointData
 * @param pFibObject the fib -object, wher to find the fib -element data
 */
void cEvalueUnderObjects::findAllFibElementData( cFibElement & pFibObject ){
	
	//first add the data to list and convert them later to sets (to speed the process)
	for ( cFibElement * pActualElement = & pFibObject; pActualElement != NULL;
			pActualElement = pActualElement->getNextFibElement() ){
		
		if ( pActualElement->getType() == 'p' ){
			//add pointelement
			DEBUG_OUT_L2(<<"evaluing the underobjects "<<endl<<flush);
			mapPointData[ (cPoint*)(pActualElement) ].liUnderObjects =
				pActualElement->getObjectPointsForElement( pActualElement, true );
			
		}else if ( pActualElement->getType() == 'y' ){
			//add propertyelement
			mapPropertyData.insert( make_pair(
				(cProperty*)(pActualElement), cPropertyData() ) );
			
		}
	}
}


/**
 * This function creates the underobject tree for the evalued points.
 * Beware: You have to care that the created underobject tree will
 * 	be deleted.
 *
 * @return a pointer to the created underobject tree
 */
cUnderobject<cPointData> * cEvalueUnderObjects::createUnderobjectTree(){
	
	cUnderobject<cPointData> * pRootUnderobject = new cUnderobject<cPointData>( 1 );
	
	for ( map< cPoint*, cPointData >::iterator
			itrPosition = mapPointData.begin();
			itrPosition != mapPointData.end(); itrPosition++ ){
		
		pRootUnderobject->addPoint( itrPosition->second );
	}
	return pRootUnderobject;
}


/**
 * This method marks all the property- and pointelements wich aren't
 * needed.
 *
 * This are:
 * 	- all overwritten properties
 * 	- all properties, wich overwrites the background, but are also equal to it
 * 	- all points which have no properties, which are not overwritten
 *
 * @see mapPropertyData
 * @see mapPointData
 * @see mapEvaluedPositionData
 * @return true if some fib -elements wher marked, else false
 */
bool cEvalueUnderObjects::markOverwrittenFibElements(){
	
	//evalue the background properties
	list< cVectorProperty > liBackgroundProperties;
	
	map< cVectorPosition, cPositionData >::iterator
			itrBackground = mapEvaluedPositionData.find( cVectorPosition( 0 ) );
	if ( itrBackground != mapEvaluedPositionData.end() ){
		//background found
		liBackgroundProperties = itrBackground->second.getAllProperties();
	}
	
	/*for all positions:
		- mark all overwritten properties
		- mark all properties, wich overwrites the background, but are also equal to it
	
	for this as long as ther are changes:
		- mark all point properties which are not needed, because ther are overwritten
		- if changes:
			- mark all properties which are not needed
		- mark all properties which are not needed, because of the background
		- if changes: mark all properties which are not needed
	*/
	bool bSomeMarked = false;
	bool bChanges1 = true;
	bool bChanges2 = true;
	//if changes -> mark all properties which are needed/used
	for ( map< cProperty*, cPropertyData >::iterator
			itrProperty = mapPropertyData.begin();
			itrProperty != mapPropertyData.end(); itrProperty++ ){
		
		const bool bOldNeeded = itrProperty->second.bPropertyNeeded;
		const bool bNewNeeded = itrProperty->second.isNeeded();
		if ( bOldNeeded != bNewNeeded ){
			bSomeMarked = true;
		}
	}
	while ( bChanges1 || bChanges2 ){
		bChanges1 = false;
		//mark all point properties which are not needed, because ther are overwritten
		for ( map< cVectorPosition, cPositionData >::iterator
				itrPosition = mapEvaluedPositionData.begin();
				itrPosition != mapEvaluedPositionData.end(); itrPosition++ ){
			
			bChanges1 |= itrPosition->second.markNotNeeded();
		}
		if ( bChanges1 ){
			//if changes -> mark all properties which are not needed
			bChanges1 = false;
			for ( map< cProperty*, cPropertyData >::iterator
					itrProperty = mapPropertyData.begin();
					itrProperty != mapPropertyData.end(); itrProperty++ ){
				
				const bool bOldNeeded = itrProperty->second.bPropertyNeeded;
				const bool bNewNeeded = itrProperty->second.isNeeded();
				if ( bOldNeeded != bNewNeeded ){
					bChanges1 = true;
					bSomeMarked = true;
				}
			}
		}
		bChanges2 = false;
		//mark all properties which are not needed, because of the background
		for ( map< cVectorPosition, cPositionData >::iterator
				itrPosition = mapEvaluedPositionData.begin();
				itrPosition != mapEvaluedPositionData.end(); itrPosition++ ){
			
			if ( itrPosition->first.getNumberOfElements() == 0 ){
				continue;//skip the background
			}
			
			bChanges2 |= itrPosition->second.markNotNeededWithBackground(
				liBackgroundProperties );
		}
		if ( bChanges2 ){
			//if changes -> mark all properties which are not needed
			bChanges2 = false;
			for ( map< cProperty*, cPropertyData >::iterator
					itrProperty = mapPropertyData.begin();
					itrProperty != mapPropertyData.end(); itrProperty++ ){
				
				const bool bOldNeeded = itrProperty->second.bPropertyNeeded;
				const bool bNewNeeded = itrProperty->second.isNeeded();
				if ( bOldNeeded != bNewNeeded ){
					bChanges2 = true;
					bSomeMarked = true;
				}
			}
		}
	}
	//mark all points which are not needed
	for ( map< cPoint*, cPointData >::iterator itrPoint = mapPointData.begin();
			itrPoint != mapPointData.end(); itrPoint++ ){
		//mark point elements not needed anymore
		
		const bool bOldNeeded = itrPoint->second.bPointNeeded;
		const bool bNewNeeded = itrPoint->second.evalueIfNeeded();
		if ( bOldNeeded != bNewNeeded ){
			bSomeMarked = true;
		}
	}
	return bSomeMarked;
}


/**
 * This method marks all the property- and pointelements wich aren't
 * needed if the given properties are the background properties.
 * This are all properties, wich overwrites the given background
 * 	properties, but are also equal to it.
 * Beware: Call @see markOverwrittenFibElements() befor calling this method.
 *
 * @see mapPropertyData
 * @see mapPointData
 * @see mapEvaluedPositionData
 * @param liBackgroundProperties the background properties
 * @return true if some fib -elements wher marked, else false
 */
bool cEvalueUnderObjects::markOverwrittenByBgFibElements(
		const list<cVectorProperty> &  liBackgroundProperties){
	
	bool bSomeMarked = false;
	bool bChanges = true;
	while ( bChanges ){
		bChanges = false;
		//mark all properties which are not needed, because of the background
		for ( map< cVectorPosition, cPositionData >::iterator
				itrPosition = mapEvaluedPositionData.begin();
				itrPosition != mapEvaluedPositionData.end(); itrPosition++ ){
			
			if ( itrPosition->first.getNumberOfElements() == 0 ){
				continue;//skip the background
			}
			
			bChanges |= itrPosition->second.markNotNeededWithBackground(
				liBackgroundProperties );
		}
		if ( bChanges ){
			//if changes -> mark all properties which are not needed
			bChanges = false;
			for ( map< cProperty*, cPropertyData >::iterator
					itrProperty = mapPropertyData.begin();
					itrProperty != mapPropertyData.end(); itrProperty++ ){
				
				const bool bOldNeeded = itrProperty->second.bPropertyNeeded;
				const bool bNewNeeded = itrProperty->second.isNeeded();
				if ( bOldNeeded != bNewNeeded ){
					bChanges = true;
					bSomeMarked = true;
				}
			}
		}
	}//while ( bChanges )
	//mark all points which are not needed
	for ( map< cPoint*, cPointData >::iterator itrPoint = mapPointData.begin();
			itrPoint != mapPointData.end(); itrPoint++ ){
		//mark point elements not needed anymore
		
		const bool bOldNeeded = itrPoint->second.bPointNeeded;
		const bool bNewNeeded = itrPoint->second.evalueIfNeeded();
		if ( bOldNeeded != bNewNeeded ){
			bSomeMarked = true;
		}
	}
	return bSomeMarked;
}

/*TODO bool markOverwrittenByBgFibElements(
		const list<cVectorProperty> &  liBackgroundProperties, doubleFib dDistance );
*/
	
//background methods

/**
 * This method evalues wich propertys can remove how many
 * propertyelements(of the evalued data) as a background property.
 * You should call the @see markOverwrittenFibElements() methods befor
 * jusing this method.
 *
 * @return a list with the pairs:
 * 	- first: a property vector(without variables)
 * 	- second: how many fib property elements can be removed, if this
 * 	property is used as an background property
 */
list< pair< cVectorProperty, unsigned long> > cEvalueUnderObjects::
		countPropertyElementsOverwritebelByBg() const{
	
	
	DEBUG_OUT_L2(<<"cEvalueUnderObjects::countPropertyElementsOverwritebelByBg() started "<<endl<<flush);
#ifdef DEBUG
	cout<<endl<<"marked data:"<<endl;
	print( cout );
	cout<<endl;
#endif //DEBUG

	map< cVectorProperty, unsigned long > mapBgProperties;
	cTypeProperty * typeOfCheckedProperty = NULL;
	
	//for every property element
	for ( map< cProperty*, cPropertyData >::const_iterator
			itrProperty = mapPropertyData.begin();
			itrProperty != mapPropertyData.end(); itrProperty++ ){
		
		if ( itrProperty->first->getProperty() == NULL ){
			//no property to check
			continue;
		}
		//the property element to check
		const cPropertyData * pCheckedProperty = &(itrProperty->second);
		if ( typeOfCheckedProperty ){
			delete typeOfCheckedProperty;
			typeOfCheckedProperty = NULL;
		}
		typeOfCheckedProperty = (cTypeProperty*)(
			itrProperty->first->getProperty()->getElementType());
		//count the checked property as removebel with a background property
		bool bCountProperty = true;
		/*the property vector, with the values of the property,
		if NULL the property wasn't used,
		if it changes the property can't be replaced by the background*/
		const cVectorProperty * pVectorProperty = NULL;
		//for every position the property is used at
		for( list< cPositionData *>::const_iterator
				itrPosition = itrProperty->second.liPositionData.begin();
				itrPosition != itrProperty->second.liPositionData.end();
				itrPosition++ ){
			
			/*if true an overwriting property was found befor*/
			bool bOverwritingPropertyBefor = false;
			//for every time it is used
			for ( list< cPositionPointData >::const_iterator
					itrPositionPoint = (*itrPosition)->liData.begin();
					itrPositionPoint != (*itrPosition)->liData.end();
					itrPositionPoint++ ){
				for ( list< cPositionPropertieData >::const_iterator
						itrPropertyPosition = itrPositionPoint->liProperties.begin();
						itrPropertyPosition != itrPositionPoint->liProperties.end();
						itrPropertyPosition++ ){
					
					DEBUG_OUT_L2(<<"Element 1 of checked Property: "<<itrProperty->first->getProperty()->getValue( 1 )<<"  actual Property: "<<itrPropertyPosition->vecProperty.getValue( 1 )<<endl<<flush);
					
					if ( itrPropertyPosition->pProperty != pCheckedProperty ){
						/*if it isn't the checked property->
						check if it is used and overwrites the checked property;
						if yes, the checked property can't be overwritten by a
						background property*/
						if ( ( ! bOverwritingPropertyBefor ) &&
								(itrPropertyPosition->pProperty->bPropertyNeeded) ){
							
							const cVectorProperty * pActualProperty =
								&(itrPropertyPosition->vecProperty);
							
							cTypeProperty * typeOfProperty = (cTypeProperty*)(
								pActualProperty->getElementType());
							const list<cTypeProperty> liOverwritenTyps =
								typeOfProperty->getOverwritenTyps();
							
							for ( list<cTypeProperty>::const_iterator itrPropertyType = liOverwritenTyps.begin();
									itrPropertyType != liOverwritenTyps.end(); itrPropertyType++ ){
								
								if ( typeOfCheckedProperty->equalElementType( *itrPropertyType ) ){
									//don't cont it-> breake
									DEBUG_OUT_L2(<<"   bOverwritingPropertyBefor"<<endl<<flush);
									bOverwritingPropertyBefor = true;
									break;
								}
							}
							delete typeOfProperty;
						}//else skip it, it dosn't matter
						continue;
					}//else itrPropertyPosition is the checked property
					if ( ! itrPropertyPosition->bPropertyNeeded ){
						//if the property(value) is not needed on this point -> skip it
						DEBUG_OUT_L2(<<"   actual position property not needed"<<endl<<flush);
						continue;
					}//else the property is needed /is used
					if ( bOverwritingPropertyBefor ){
						/*ther is a property evalued befor on this position,
						that is needed and overwrites the to check property
						-> the background can't remove this property*/
						DEBUG_OUT_L2(<<"   checked property not needed because bOverwritingPropertyBefor"<<endl<<flush);
						bCountProperty = false;
						break;
					}
					if ( pVectorProperty == NULL ){
						//remember the property(value), to check if it dosn't change
						pVectorProperty = &(itrPropertyPosition->vecProperty);
					}else{
						//if the propertyvector changed
						if ( (*pVectorProperty) != itrPropertyPosition->vecProperty ){
							//don't cont it (one background property can't replace it) -> breake
							DEBUG_OUT_L2(<<"   checked property not needed because vector changed"<<endl<<flush);
							bCountProperty = false;
							break;
						}
					}
				}
				if ( ! bCountProperty ){
					//don't cont it -> check next property -> breake
					break;
				}
			}//end for every time it is used in the position property
			if ( ! bCountProperty ){
				//don't cont it -> check next property -> breake
				break;
			}
		}//end for every position the property is used at
		DEBUG_OUT_L2(<<"bCountProperty="<<(bCountProperty?"true":"false")<<" pVectorProperty="<<pVectorProperty<<endl<<flush);
		
		//if the property should be counted and was used -> count it
		if ( bCountProperty && (pVectorProperty != NULL) ){
		
			map< cVectorProperty, unsigned long >::iterator itrBgProperty =
				mapBgProperties.find( *pVectorProperty );
			
			if ( itrBgProperty == mapBgProperties.end() ){
				//new property -> add it with count 1
				mapBgProperties.insert( make_pair( *pVectorProperty, 1 ) );
			}else{//add 1 to count
				itrBgProperty->second++;
			}
		}
	}
	if ( typeOfCheckedProperty ){
		delete typeOfCheckedProperty;
		typeOfCheckedProperty = NULL;
	}
	//transfer counted properties into a list
	list< pair< cVectorProperty, unsigned long> > liBgProperties(
		mapBgProperties.begin(), mapBgProperties.end() );
	
	DEBUG_OUT_L2(<<"cEvalueUnderObjects::countPropertyElementsOverwritebelByBg() done "<<endl<<flush);
	return liBgProperties;
}




#ifdef DEBUG
/**
 * Prints the evalued data.
 *
 * @param stream the strem wher to print the data to
 */
void cEvalueUnderObjects::print( ostream & stream ) const{
	
	for ( map< cVectorPosition, cPositionData >::const_iterator
			itrPosition = mapEvaluedPositionData.begin();
			itrPosition != mapEvaluedPositionData.end(); itrPosition++ ){
	
		stream<<"Position (";
		{
			const unsignedIntFib uiNumberOfElements = itrPosition->first.getNumberOfElements();
			for ( unsignedIntFib uiActualElement = 1;
					uiActualElement <= uiNumberOfElements; uiActualElement++ ){
				
				cout<<itrPosition->first.getValue( uiActualElement )<<";";
			}
		}
		stream<<"): ";
		
		for ( list< cPositionPointData >::const_iterator
				itrData = itrPosition->second.liData.begin();
				itrData != itrPosition->second.liData.end();
				itrData++ ){
			
			stream<<"position point "<<itrData->pPoint<<" "<<(itrData->bPointNeeded?"needed":"not needed")<<": ";
			for ( list< cPositionPropertieData >::const_iterator
					itrProperty = itrData->liProperties.begin();
					itrProperty != itrData->liProperties.end();
					itrProperty++ ){
				
				stream<<"pppy "<<itrProperty->pProperty<<" (";
				{
					const unsignedIntFib uiNumberOfElements =
						itrProperty->vecProperty.getNumberOfElements();
					for ( unsignedIntFib uiActualElement = 1;
							uiActualElement <= uiNumberOfElements; uiActualElement++ ){
						
						cout<<itrProperty->vecProperty.getValue( uiActualElement )<<";";
					}
				}
				stream<<") "<<(itrProperty->bPropertyNeeded?"needed":"not needed")<<", ";
			}
			stream<<"; ";
		}
	
		stream<<endl;
	}
/*if needed print
	map< cProperty*, cPropertyData > mapPropertyData;
	map< cPoint*, cPointData > mapPointData;
*/
	
}
#endif //DEBUG





