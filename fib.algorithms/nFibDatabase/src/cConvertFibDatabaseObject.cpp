/**
 * @file cConvertFibDatabaseObject
 * file name: cConvertFibDatabaseObject.cpp
 * @author Betti Oesterholz
 * @date 29.01.2013
 * @mail Oesterholz@Fib-development.org
 *
 * System: C++
 *
 * This file implements a class to convert Fib database objects.
 *
 * Copyright (C) @c GPL3 2012 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (GPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * This file implements a class to convert Fib database objects.
 * For this the given external object elements will be changed, so
 * they match the requirements.
 * @pattern Strategy
 */
/*
History:
29.01.2013  Oesterholz  created
*/


#include "cConvertFibDatabaseObject.h"


#include <list>

#include "cRoot.h"
#include "cProperty.h"
#include "cVectorProperty.h"
#include "cTypeProperty.h"
#include "cPoint.h"


using namespace fib::algorithms::nFibDatabase;
using namespace fib;
using namespace std;


/**
 * This function converts the given external object into the external
 * object with a point subobject if possible.
 * BEWARE: You have to add the color property directly below the created
 * 	point.
 * 	You have to care that the created (if converted) point element
 * 	is deleted.
 *
 * @param pExternalObject a pointer to the external object to convert
 * 	to it's version with a point subobject;
 * 	BEWARE: this object will be changed to its version with point subobject
 * @return a pointer to the version of the external object with a point
 * 	subobject, or NULL if non exists
 */
cExtObject * cConvertFibDatabaseObject::convertToPointSubObject(
		cExtObject * pExternalObject ){
	
	if ( pExternalObject == NULL ){
		//no external object -> can't convert to version with point subobject
		return NULL;
	}
	cFibDatabase * pFibDatabase = cFibDatabase::getInstance();
	
	//get the identifier for the identical but with point subobject object
	cRoot * pNotPointSubobjectObject =
		pFibDatabase->getFibObject( pExternalObject->getIdentifier() );
	if ( pNotPointSubobjectObject == NULL ){
		//no object for the identifer -> no version with point subobject can be evalued
		return NULL;
	}
	
	const cOptionalPart * pOptionalPart =
		pNotPointSubobjectObject->getOptionalPart();
	if ( pOptionalPart == NULL ){
		//no optional part -> no version with point subobject can be evalued
		return NULL;
	}
	const list< pair<string,string> > liEntryIsPointSubobject =
		pOptionalPart->getEntries( "isPointSubObject" );
	if ( ! liEntryIsPointSubobject.empty() ){
		//the given object was allready with point subobject
		return pExternalObject;
	}
	const list< pair<string,string> > liEntryPointSubobject =
		pOptionalPart->getEntries( "DbObject::isPointSubObject" );
	if ( liEntryPointSubobject.empty() ){
		//can't evalue a version with point subobject of the given external object
		return NULL;
	}
		//store the identifer of the point subobject version
	const longFib lPointSubobjectIdentifier =
		atol( liEntryPointSubobject.front().second.c_str() );
	
	if ( lPointSubobjectIdentifier == 0 ){
		//can't evalue a version with point subobject of the given external object
		return NULL;
	}
	//change external object identifier
	pExternalObject->setIdentifier( lPointSubobjectIdentifier );
	//create a point subobject if non exists
	const unsignedIntFib uiNumberSubobjects =
		pExternalObject->getNumberOfSubobjects();
	if ( uiNumberSubobjects == 0 ){
		//no subobject exists -> create point
		cVectorPosition vecPosition( 2 );
		cPoint * pPoint = new cPoint( &vecPosition );
		//create the subobject for the external object element
		pExternalObject->setNumberOfSubobjects( 1 );
		pExternalObject->setNumberOfOutputVariables( 1, 2 );
		
		//set the position of the point to the external object output variables
		pPoint->getPosition()->setVariable( 1,
			pExternalObject->getOutputVariable( 1, 1 ) );
		pPoint->getPosition()->setVariable( 2,
			pExternalObject->getOutputVariable( 1, 2 ) );
		
		//set the created point as the first subobject of the external object
		pExternalObject->setSubobject( 1, pPoint );
	}
	
	return pExternalObject;
}


/**
 * This function converts the given external object into an antialised
 * external object if possible.
 * BEWARE: You have to add the color property directly below the created
 * 	point or above the created transparency property.
 * 	You have to care that the created (if converted) point and property
 * 	element are deleted.
 *
 * @param pExternalObject a pointer to the external object to convert
 * 	to it's antialised version;
 * 	BEWARE: this object will be changed to its antialised version
 * @return a pointer to the antialised version of the external object,
 * 	or NULL if non exists
 */
cExtObject * cConvertFibDatabaseObject::convertToAntialised(
		cExtObject * pExternalObject ){
	
	if ( pExternalObject == NULL ){
		//no external object -> can't convert to antialised
		return NULL;
	}
	cFibDatabase * pFibDatabase = cFibDatabase::getInstance();
	
	//get the identifier for the identical but antialised object
	cRoot * pNotAntialisedObject =
		pFibDatabase->getFibObject( pExternalObject->getIdentifier() );
	if ( pNotAntialisedObject == NULL ){
		//no object for the identifer -> no antialised version can be evalued
		return NULL;
	}
	
	const cOptionalPart * pOptionalPart =
		pNotAntialisedObject->getOptionalPart();
	if ( pOptionalPart == NULL ){
		//no optional part -> no antialised version can be evalued
		return NULL;
	}
	const list< pair<string,string> > liEntryAntialialised =
		pOptionalPart->getEntries( "isAntialiased" );
	if ( ! liEntryAntialialised.empty() ){
		//the given object was allready antialised
		return pExternalObject;
	}
	/*the identifier for the antialised version of pExternalObject, or 0 if
	 *non such exists*/
	longFib lAnialisedIdentifier = 0;
	{
		const list< pair<string,string> > liEntryObjAntialialised =
			pOptionalPart->getEntries( "DbObject::isAntialiased" );
		if ( ! liEntryObjAntialialised.empty() ){
			//store the identifer of the antialised object
			lAnialisedIdentifier =
				atol( liEntryObjAntialialised.front().second.c_str() );
		}
	}
	if ( lAnialisedIdentifier == 0 ){
		/*try to evalue the antialised version with the help of the version
		 of this object, which uses a subobject for it's points*/
		const list< pair<string,string> > liEntryPointSubobject =
			pOptionalPart->getEntries( "DbObject::isPointSubObject" );
		if ( ! liEntryPointSubobject.empty() ){
			//store the identifer of the point subobject version
			const longFib lPointSubobjectIdentifier =
				atol( liEntryPointSubobject.front().second.c_str() );
			
			if ( lPointSubobjectIdentifier != 0 ){
				//ther is a version with a point subobject for this object
				cRoot * pPointSubobjectObject =
					pFibDatabase->getFibObject( lPointSubobjectIdentifier );
				
				if ( pPointSubobjectObject ){
					//get the point subobject version optional part
					const cOptionalPart * pOptionalPartPointSubobject =
						pPointSubobjectObject->getOptionalPart();
					
					if ( pOptionalPartPointSubobject != NULL ){
						//get the "DbObject::isAntialised" entry of the optional part
						const list< pair<string,string> > liEntryObjAntialialised =
							pOptionalPartPointSubobject->getEntries(
								"DbObject::isAntialiased" );
						if ( ! liEntryObjAntialialised.empty() ){
							//store the identifer of the antialised object
							lAnialisedIdentifier =
								atol( liEntryObjAntialialised.front().second.c_str() );
						}
					}//end if optional part for pPointSubobjectObject exists
				}//end if point subobject version object exists
			}//end if identifer of the point subobject version exists
		}//end if identifer entry of the point subobject version exists
	}
	if ( lAnialisedIdentifier == 0 ){
		//can't evalue a antialised version of the given external object
		return NULL;
	}
	//change external object identifier
	pExternalObject->setIdentifier( lAnialisedIdentifier );
	//create a point subobject if non exists
	const unsignedIntFib uiNumberSubobjects =
		pExternalObject->getNumberOfSubobjects();
	if ( uiNumberSubobjects == 0 ){
		//no subobject exists -> create point and set transparency property
		cVectorPosition vecPosition( 2 );
		cPoint * pPoint = new cPoint( &vecPosition );
		//create the subobject for the external object element
		pExternalObject->setNumberOfSubobjects( 1 );
		pExternalObject->setNumberOfOutputVariables( 1, 3 );
		
		//set the position of the point to the external object output variables
		pPoint->getPosition()->setVariable( 1,
			pExternalObject->getOutputVariable( 1, 1 ) );
		pPoint->getPosition()->setVariable( 2,
			pExternalObject->getOutputVariable( 1, 2 ) );
		//create the transparency property
		cVectorProperty vecTransparency( cTypeProperty::TRANSPARENCY );
		cProperty * pProperty = new cProperty( vecTransparency, pPoint );
		pProperty->getProperty()->setVariable( 1,
			pExternalObject->getOutputVariable( 1, 3 ) );
		
		//set the created property and point as the first subobject of the external object
		pExternalObject->setSubobject( 1, pProperty );
	}else{// if (  1 <= uiNumberSubobjects )
		const unsigned int uiNumberOutVar =
			pExternalObject->getNumberOfOutputVariables( 1 );
		if ( uiNumberOutVar < 3 ){
			//not enougth output variables -> add transparency variables
			pExternalObject->setNumberOfOutputVariables( 1, 3 );
			
			//create transparency property
			cFibElement * pSubObject = pExternalObject->getSubobject( 1 );
			cVectorProperty vecTransparency( cTypeProperty::TRANSPARENCY );
			cProperty * pProperty = new cProperty( vecTransparency, pSubObject );
			pProperty->getProperty()->setVariable( 1,
				pExternalObject->getOutputVariable( 1, 3 ) );
			pExternalObject->setSubobject( 1, pProperty, false );
		}//minimum 3 variables existed -> transparency variable exists
	}
	
	return pExternalObject;
}


