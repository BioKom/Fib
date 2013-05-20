
//TODO check

/**
 * @file cConvertImageToFibForOnePropertySimple
 * file name: cConvertImageToFibForOnePropertySimple.cpp
 * @author Betti Oesterholz
 * @date 17.02.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements a class for converting an image to a Fib object.
 *
 * Copyright (C) @c GPL3 2013 Betti Oesterholz
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
 *
 * This file implements a class for converting an image to a Fib object.
 * For this a method convertToFib() is implemented (in a simple way).
 * The convered Fib object is just for one property.
 * If antialising is allowed the transparency property will be used.
 * @see findImageStructure()
 *
 * @pattern Strategy
 * @see iFindImageStructure
 * @see cImageStructure
 */
/*
History:
17.02.2013  Oesterholz  created
*/

//debugging switches
//#define DEBUG
//#define DEBUG_OUTPUT_STRUCTURE_DATA


#include "cConvertImageToFibForOnePropertySimple.h"

#include "iImageData.h"
#include "cImageSearchData.h"
#include "cImageAreaSameColor.h"
#include "cImageAreaLinearColor.h"

#include "cFindImageAreaSameColorSimple.h"
#include "cFindImageAreaLinearColorSimple.h"

#include "cList.h"
#include "cPoint.h"
#include "cProperty.h"
#include "cExtObject.h"
#include "cVectorPosition.h"
#include "cVectorProperty.h"
#include "cDomains.h"
#include "cTypeProperty.h"
#include "cDomainIntegerBit.h"
#include "cDomainVector.h"


#if defined(DEBUG_OUTPUT_STRUCTURE_DATA) || defined(DEBUG)
	#include <iostream>
	#include <fstream>
	
	#ifndef DEBUG_OUTPUT_STRUCTURE_DATA_FILE
		#define DEBUG_OUTPUT_STRUCTURE_DATA_FILE "structureData.xml"
	#endif //DEBUG_OUTPUT_STRUCTURE_DATA_FILE
	
	#ifndef DEBUG_OUTPUT_BORDER_DATA_FILE
		#define DEBUG_OUTPUT_BORDER_DATA_FILE "borderData.xml"
	#endif //DEBUG_OUTPUT_BORDER_DATA_FILE
	#ifndef DEBUG_OUTPUT_STRUCTUR_BORDER_DATA_FILE
		#define DEBUG_OUTPUT_STRUCTUR_BORDER_DATA_FILE "structureBorderData.xml"
	#endif //DEBUG_OUTPUT_STRUCTUR_BORDER_DATA_FILE
	
	#ifndef DEBUG_OUTPUT_OVERLAPPED_POINTS_DATA_FILE
//		#define DEBUG_OUTPUT_OVERLAPPED_POINTS_DATA_FILE "structureOverlappedData.xml"
	#endif //DEBUG_OUTPUT_OVERLAPPED_POINTS_DATA_FILE
	
#endif //DEBUG_OUTPUT_STRUCTURE_DATA


using namespace fib::algorithms::nConvertToFib::nImage::nSearchForStructure;
using namespace fib::algorithms::nConvertToFib::nImage::nStructureData::nOperators;
using namespace fib::algorithms::nConvertToFib::nImage;
using namespace fib;

/**
 * constructor
 *
 * @param imageData the image data to convert;
 * 	The given image data object will be copied. @see pImageData
 * @param uiPropertyType the type number of the property to use;
 * 	(e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
 * @param dMaxErrorPerPoint the maximal error for a point of the area
 * @param dMaxErrorPerBorderPoint the maximal error for the border points to
 * 	find on one border point; every point in the part areas of the generated
 * 	Fib objects will have a distance lower or equal dMaxErrorPerBorderPoint
 * 	to a point in the correct area border
 * @param bInCanBeAntialised if true the found Fib object can use
 * 	antialising (transparency for border points of areas), else it can't
 * @param liInOperatoresForImageStructure A list with the operators for
 * 	the created image structures.
 * 	On every created image structure, which will be converted to a
 * 	Fib object, every operator (from begin to end of the list) will be
 * 	called. @see liOperatoresForImageStructure
 */
cConvertImageToFibForOnePropertySimple::cConvertImageToFibForOnePropertySimple(
		const iImageData & imageData,
		const unsigned int uiPropertyType, const double dMaxErrorPerPoint,
		const double dMaxErrorPerBorderPoint, const bool bInCanBeAntialised,
		const list< iImageStructureSearchOperator * > liInOperatoresForImageStructure ):
#ifdef FEATURE_SEARCH_BORDER_HANDLING
		cConvertImageToFib(),
#else //FEATURE_SEARCH_BORDER_HANDLING
		cConvertImageToFib( imageData ),
#endif //FEATURE_SEARCH_BORDER_HANDLING
		propertyTypeNumber( uiPropertyType ),
		maxErrorPerPoint( dMaxErrorPerPoint ),
		maxErrorPerBorderPoint( dMaxErrorPerBorderPoint ),
		bCanBeAntialised( bInCanBeAntialised ),
		liOperatoresForImageStructure( liInOperatoresForImageStructure )
		{
	//nothing to do
#ifdef FEATURE_SEARCH_BORDER_HANDLING
	pImageData = imageData.clone();
	isImageDataCopy  = true;
	pImageSearchDataForOverlappedBorder =
		new cImageSearchDataForOverlappedBorder( pImageData );
	pImageSearchData = pImageSearchDataForOverlappedBorder;
#endif //FEATURE_SEARCH_BORDER_HANDLING
}


/**
 * constructor
 *
 * @param pInImageData a pointer to the image data to convert;
 * 	Beware this object won't be copied, so keep it alive as long as
 * 	this object exists. @see pImageData
 * @param uiPropertyType the type number of the property to use;
 * 	(e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
 * @param dMaxErrorPerPoint the maximal error for a point of the area
 * @param dMaxErrorPerBorderPoint the maximal error for the border points to
 * 	find on one border point; every point in the part areas of the generated
 * 	Fib objects will have a distance lower or equal dMaxErrorPerBorderPoint
 * 	to a point in the correct area border
 * @param bInCanBeAntialised if true the found Fib object can use
 * 	antialising (transparency for border points of areas), else it can't
 * @param liInOperatoresForImageStructure A list with the operators for
 * 	the created image structures.
 * 	On every created image structure, which will be converted to a
 * 	Fib object, every operator (from begin to end of the list) will be
 * 	called. @see liOperatoresForImageStructure
 */
cConvertImageToFibForOnePropertySimple::cConvertImageToFibForOnePropertySimple(
		const iImageData * pInImageData,
		const unsigned int uiPropertyType, const double dMaxErrorPerPoint,
		const double dMaxErrorPerBorderPoint, const bool bInCanBeAntialised,
		const list< iImageStructureSearchOperator * > liInOperatoresForImageStructure ):
#ifdef FEATURE_SEARCH_BORDER_HANDLING
		cConvertImageToFib(),
#else //FEATURE_SEARCH_BORDER_HANDLING
		cConvertImageToFib( pInImageData ),
#endif //FEATURE_SEARCH_BORDER_HANDLING
		propertyTypeNumber( uiPropertyType ),
		maxErrorPerPoint( dMaxErrorPerPoint ),
		maxErrorPerBorderPoint( dMaxErrorPerBorderPoint ),
		bCanBeAntialised( bInCanBeAntialised ),
		liOperatoresForImageStructure( liInOperatoresForImageStructure )
#ifdef FEATURE_SEARCH_BORDER_HANDLING
		,pImageSearchDataForOverlappedBorder(
			new cImageSearchDataForOverlappedBorder( pInImageData ) )
#endif //FEATURE_SEARCH_BORDER_HANDLING
		{
	//nothing to do
#ifdef FEATURE_SEARCH_BORDER_HANDLING
	pImageData = pInImageData;
	isImageDataCopy  = false;
	pImageSearchData = pImageSearchDataForOverlappedBorder;
#endif //FEATURE_SEARCH_BORDER_HANDLING
}


/**
 * destructor
 */
cConvertImageToFibForOnePropertySimple::~cConvertImageToFibForOnePropertySimple(){
	//nothing to do
#ifdef FEATURE_SEARCH_BORDER_HANDLING
	if ( pImageSearchDataForOverlappedBorder ){
		delete pImageSearchDataForOverlappedBorder;
		pImageSearchDataForOverlappedBorder = NULL;
		pImageSearchData = NULL;
	}
#endif //FEATURE_SEARCH_BORDER_HANDLING
}


/**
 * This method is for converting the image data to a Fib object.
 *
 * @pattern Factory Method
 * @return a Fib object which represents the the image data of this object
 * 	or NULL if non could be generated
 * 	Beware: You have to delete the returned Fib object after usage.
 */
cRoot * cConvertImageToFibForOnePropertySimple::convertToFib(){
	
	if ( pImageData == NULL ){
		return NULL;
	}
	
#ifdef DEBUG_OUTPUT_STRUCTURE_DATA
	unsigned long ulOutputDebugIteration = 0;
	{
		ofstream ofFileStructurData( DEBUG_OUTPUT_STRUCTURE_DATA_FILE );
		ofFileStructurData.close();
		
#ifndef FEATURE_SEARCH_BORDER_HANDLING
		ofstream ofFileBorderData( DEBUG_OUTPUT_BORDER_DATA_FILE );
		ofFileBorderData.close();
#endif //FEATURE_SEARCH_BORDER_HANDLING
		
		ofstream ofFileStructurBorderData( DEBUG_OUTPUT_STRUCTUR_BORDER_DATA_FILE );
		ofFileStructurBorderData.close();
#ifdef DEBUG_OUTPUT_OVERLAPPED_POINTS_DATA_FILE
		ofstream ofFileStructurOverlappedAreaData( DEBUG_OUTPUT_OVERLAPPED_POINTS_DATA_FILE );
		ofFileStructurOverlappedAreaData.close();
#endif //DEBUG_OUTPUT_OVERLAPPED_POINTS_DATA_FILE
	}
#endif //DEBUG_OUTPUT_STRUCTURE_DATA
#ifndef FEATURE_SEARCH_BORDER_HANDLING
	//border for found area
	set< pair< unsigned int, unsigned int > > setFoundAreaBorder;
	//add as the start point the point (0, 0) (garanted to exists)
	setFoundAreaBorder.insert( pair< unsigned int, unsigned int >( 0, 0 ) );
#endif //FEATURE_SEARCH_BORDER_HANDLING
	
	cList * pMainList = new cList( NULL, NULL );
	cRoot * pFibObjectRoot = new cRoot( pMainList );
	//strategies for finding image structures
	cFindImageAreaSameColorSimple findImageAreaSameColorSimple(
			propertyTypeNumber, maxErrorPerPoint, bCanBeAntialised );
	
	const unsigned int uiNumberOfPropertyElements = (pImageData->
		getDimension3IndexesForPropertyType( propertyTypeNumber )).size();
	const double dMaxErrorPerPropertyElement =
		( uiNumberOfPropertyElements == 0 ) ? 0.0 :
			( maxErrorPerPoint / ((double)uiNumberOfPropertyElements) );
	
	cFindImageAreaLinearColorSimple findImageAreaLinearColorSimple(
			propertyTypeNumber, maxErrorPerPoint, bCanBeAntialised,
			dMaxErrorPerPropertyElement  );
	bool bAntialisingUsed = false;
	//while not whole image found (or while there are border points for found area)
#ifdef FEATURE_SEARCH_BORDER_HANDLING
	while ( true ){
		//choose good next start point from actual border
		pair< bool, pair< unsigned int, unsigned int> > paBorderPoint =
			pImageSearchDataForOverlappedBorder->getBorderPoint();
		
		if ( ! paBorderPoint.first ){
			//no not overlapped point (overlapped border point) found -> stop evaluation
			break;
		}
		
		pair< unsigned int, unsigned int > & paNextStartPoint =
			paBorderPoint.second;
#else //FEATURE_SEARCH_BORDER_HANDLING
	while ( ! setFoundAreaBorder.empty() ){
		//choose good next start point from actual border
		//point with minimum x and then minimum y
		pair< unsigned int, unsigned int > paNextStartPoint =
			*(setFoundAreaBorder.begin());
		setFoundAreaBorder.erase( setFoundAreaBorder.begin() );
#endif //FEATURE_SEARCH_BORDER_HANDLING
			
		//start converting area to image structure
		DEBUG_OUT_L2(<<"start converting area to image structure for start point ("<<paNextStartPoint.first<<", "<<paNextStartPoint.second<<")"<<endl<<flush);
		cImageStructure * pImageStructureToUse = NULL;
		//try to find constant color image
		DEBUG_OUT_L2(<<"try to find constant color image"<<endl<<flush);
		cImageAreaSameColor * pImageAreaSameColor =
			findImageAreaSameColorSimple.findImageStructure(
				paNextStartPoint, this );
		
		pImageStructureToUse = pImageAreaSameColor;
		cImageAreaLinearColor * pImageAreaLinearColor = NULL;
		if ( pImageData->isPropertyTypeIndependentOfPosition() ){
			/* the used strategies just works with position independet
			 * dimension 3 indexes for the property*/
			
			//TODO checkWidthLower() just if error is smaal enougth (== 0)
			if ( ( maxErrorPerPoint != 0 ) ||
					( checkWidthLower( pImageStructureToUse, 5 ) ) ){
				/*if width or hight of found area is lower 5
				(evalue minimum and maximum in each direction; if for both
				directions 5 <= maximum - minimum -> don't find linear color image
				structure )*/
				DEBUG_OUT_L2(<<"try to find linear color image structure"<<endl<<flush);
				//try to find linear color image structure
				pImageAreaLinearColor =
					findImageAreaLinearColorSimple.findImageStructure(
						paNextStartPoint, this );
				
				//if last found image structure not better -> set points of used image structure as found
				if ( pImageAreaLinearColor->getStructurePointsConst().size() <
						pImageStructureToUse->getStructurePointsConst().size() ){
					//better image structure found than last
					pImageStructureToUse = pImageAreaLinearColor;
					if ( pImageAreaSameColor ){
						//delete image structure for same clored area
						delete pImageAreaSameColor;
						pImageAreaSameColor = NULL;
					}
				}else{//else found image structure not better -> delete it
					if ( pImageAreaLinearColor ){
						//delete image structure for same clored area
						delete pImageAreaLinearColor;
						pImageAreaLinearColor = NULL;
					}
				}
				
			}
		}
		if ( ( pImageStructureToUse == NULL ) ||
				( pImageStructureToUse->getStructurePointsConst().empty() ) ){
			/*no image structure found or it contains no points
			 -> add border point with its property into Fib object*/
			DEBUG_OUT_L2(<<"Error: no image structure found or it contains no points: generate Fib point for start point ("<<paNextStartPoint.first<<", "<<paNextStartPoint.second<<")"<<endl<<flush);
			cFibElement * pPointObject =
				generateObjectForPoint( paNextStartPoint );
			
			if ( pPointObject ){
				if ( ! pMainList->addUnderobject( pPointObject, 1 ) ){
					//point object not set -> delete it
					pPointObject->deleteObject();
				}
			}
#ifdef DEBUG
			else{
				cerr<<"Error: could not generate point for start point (could not generate an image structure)"<<endl;
			}
#endif //DEBUG
			pImageSearchData->registerOverlapped( paNextStartPoint );
			continue;
		}
		//call the operators for the image structure to use
		if ( ! liOperatoresForImageStructure.empty() ){
			for ( list< iImageStructureSearchOperator * >::const_iterator
					itrOperator = liOperatoresForImageStructure.begin();
					itrOperator != liOperatoresForImageStructure.end();
					itrOperator++ ){
				
				(**itrOperator)( pImageStructureToUse, pImageSearchData );
			}
			//start point should remain image structure
			pImageStructureToUse->addStructurePoint( paNextStartPoint );
		}
#ifdef FEATURE_SEARCH_BORDER_HANDLING
		if ( pImageStructureToUse->isAntialised() ){
			bAntialisingUsed = true;
			DEBUG_OUT_L2(<<"add all its overlapped neighbours to the structure"<<endl<<flush);
			const set< pair< unsigned int, unsigned int> > setStructureBorderPoints =
				pImageStructureToUse->getStructureBorderPointsPair();
			//for all structure border points
			for ( set< pair< unsigned int, unsigned int> >::const_iterator
					itrBorderPoint = setStructureBorderPoints.begin();
					itrBorderPoint != setStructureBorderPoints.end();
					itrBorderPoint++ ){
				
				//add all its overlapped neighbours to the structure
				pImageStructureToUse->addStructurePoints(
					pImageSearchData->getOverlappedNeighbours( *itrBorderPoint ) );
			}//end for all structure neighbour points
			/*if image structure is antialised
			 *-> add border points to structure points*/
			pImageStructureToUse->addStructurePoints(
				pImageStructureToUse->getStructureBorderPointsConst() );
		}
#else //FEATURE_SEARCH_BORDER_HANDLING
		//evalue new border for found area
		if ( ! pImageStructureToUse->isAntialised() ){
			//if not antialised
			const set< pair< unsigned int, unsigned int> > setStructureNeighbours =
				pImageStructureToUse->getStructureNeighbourPointsPair();
			//for all structure neighbour points
			for ( set< pair< unsigned int, unsigned int> >::const_iterator
					itrNeighbourPoint = setStructureNeighbours.begin();
					itrNeighbourPoint != setStructureNeighbours.end();
					itrNeighbourPoint++ ){
				
				set< pair< unsigned int, unsigned int > >::iterator
					itrAreaBorderPoint = setFoundAreaBorder.find( *itrNeighbourPoint );
				if ( itrAreaBorderPoint != setFoundAreaBorder.end() ){
					/*if neighbour point in border for found area
					-> remove neighbour point from border for found area*/
					const bool bHasNotFoundNotOverlappedNeighbours =
						pImageSearchData->hasNotFoundNotOverlappedNeighbours(
							*itrNeighbourPoint );
					if ( ! bHasNotFoundNotOverlappedNeighbours ){
						setFoundAreaBorder.erase( itrAreaBorderPoint );
					}
				}else{/*if neighbour point not in border for found area
					-> add neighbour point to border for found area*/
					setFoundAreaBorder.insert( *itrNeighbourPoint );
				}
			}//end for all structure neighbour points
		}else{//if antialised
			bAntialisingUsed = true;
			const set< pair< unsigned int, unsigned int> > setStructureBorderPoints =
				pImageStructureToUse->getStructureBorderPointsPair();
			//for all structure border points
			for ( set< pair< unsigned int, unsigned int> >::const_iterator
					itrBorderPoint = setStructureBorderPoints.begin();
					itrBorderPoint != setStructureBorderPoints.end();
					itrBorderPoint++ ){
				
				set< pair< unsigned int, unsigned int > >::iterator
					itrAreaBorderPoint = setFoundAreaBorder.find( *itrBorderPoint );
				if ( itrAreaBorderPoint != setFoundAreaBorder.end() ){
					/*if border point in border for found area
					-> add all its overlapped neighbours to the structure
					+ if all its neighbour are found, overlapped or structure 
					border points:
						remove border point from border for found area
						+ mark it as found point in seach structure*/
					//add all its overlapped neighbours to the structure
					pImageStructureToUse->addStructurePoints(
						pImageSearchData->getOverlappedNeighbours( *itrBorderPoint ) );
					/*check if all its neighbour are found, overlapped or
					 * structure border points*/
					const set< pair< unsigned int, unsigned int > >
						setNotFoundNotOverlappedNeighbours =
							pImageSearchData->getNotFoundNotOverlappedNeighbours(
								*itrBorderPoint );
					bool bAllNotFoundNotOverlappedNeighboursInStructurBorder = true;
					for ( set< pair< unsigned int, unsigned int > >::const_iterator
							itrNeighbourPoint = setNotFoundNotOverlappedNeighbours.begin();
							itrNeighbourPoint != setNotFoundNotOverlappedNeighbours.end();
							itrNeighbourPoint++ ){
						const set< pair< unsigned int, unsigned int> >::const_iterator
							itrFoundPoint = setStructureBorderPoints.find( *itrNeighbourPoint );
						if ( itrFoundPoint == setStructureBorderPoints.end() ){
							//neighbour point not structure border point
							bAllNotFoundNotOverlappedNeighboursInStructurBorder = false;
							break;
						}
					}
					
					if ( bAllNotFoundNotOverlappedNeighboursInStructurBorder ){
						//remove border point from border for found area
						setFoundAreaBorder.erase( itrAreaBorderPoint );
						//mark it as found point in seach structure
						pImageSearchData->registerFound( *itrBorderPoint );
					}
					
				}else{/*if border point not in border for found area
					-> add border point to border for found area*/
					setFoundAreaBorder.insert( *itrBorderPoint );
				}
			}//end for all structure neighbour points
			/*if image structure is antialised
			 *-> add border points to structure points*/
			pImageStructureToUse->addStructurePoints(
				pImageStructureToUse->getStructureBorderPointsConst() );
		}
		{//remove points from border points for found area which are found or overlapped
			set< pair< unsigned int, unsigned int > >::iterator itrDeleteBorderPoint;
			set< pair< unsigned int, unsigned int > > setBorderNotFoundNotOverlappedNeighbours;
			for ( set< pair< unsigned int, unsigned int > >::iterator
					itrActualBorderPoint = setFoundAreaBorder.begin();
					itrActualBorderPoint != setFoundAreaBorder.end(); ){
				
				if ( pImageSearchData->isFoundOrOverlapped( *itrActualBorderPoint ) ){
					//add not found and not overlapped neighbours
					const set< pair< unsigned int, unsigned int > >
						setNotFoundNotOverlappedNeighbours =
							pImageSearchData->getNotFoundNotOverlappedNeighbours(
								*itrActualBorderPoint );
					setBorderNotFoundNotOverlappedNeighbours.insert(
						setNotFoundNotOverlappedNeighbours.begin(),
						setNotFoundNotOverlappedNeighbours.end() );
					
					//delete border point
					itrDeleteBorderPoint = itrActualBorderPoint;
					itrActualBorderPoint++;
					setFoundAreaBorder.erase( itrDeleteBorderPoint );
				}else{
					itrActualBorderPoint++;
				}
			}
			setFoundAreaBorder.insert( setBorderNotFoundNotOverlappedNeighbours.begin(),
				setBorderNotFoundNotOverlappedNeighbours.end() );
		}
#endif //FEATURE_SEARCH_BORDER_HANDLING
#ifdef DEBUG_OUTPUT_STRUCTURE_DATA
		{
			ulOutputDebugIteration++;
			
			ofstream ofFileStructurData( DEBUG_OUTPUT_STRUCTURE_DATA_FILE, ios_base::app );
			pImageStructureToUse->storeXml( ofFileStructurData );
			ofFileStructurData.close();
			//output border data
			
			cVectorProperty vecBorderColor( cTypeProperty::COLOR_RGB );
			vecBorderColor.setValue( 3, 255 );
			
			vecBorderColor.setValue( 2, ulOutputDebugIteration % 256 );
			vecBorderColor.setValue( 1, ( ulOutputDebugIteration / 256 ) % 256 );
#ifndef FEATURE_SEARCH_BORDER_HANDLING
			cImageAreaSameColor borderArea( vecBorderColor );
			borderArea.setStructurePoints( setFoundAreaBorder );
			
			ofstream ofFileBorderData( DEBUG_OUTPUT_BORDER_DATA_FILE, ios_base::app );
			borderArea.storeXml( ofFileBorderData );
			ofFileBorderData.close();
#endif //FEATURE_SEARCH_BORDER_HANDLING
			
			cImageAreaSameColor structureBorderArea( vecBorderColor );
			structureBorderArea.setStructurePoints(
				pImageStructureToUse->getStructureBorderPointsConst() );
			
			ofstream ofFileStructurBorderData( DEBUG_OUTPUT_STRUCTUR_BORDER_DATA_FILE, ios_base::app );
			structureBorderArea.storeXml( ofFileStructurBorderData );
			ofFileStructurBorderData.close();
			
#ifdef DEBUG_OUTPUT_OVERLAPPED_POINTS_DATA_FILE
			cImageAreaSameColor structureOverlappedArea( vecBorderColor );
			structureOverlappedArea.setStructurePoints(
				pImageSearchData->getOverlappedPoints() );
			
			ofstream ofFileStructurOverlappedAreaData( DEBUG_OUTPUT_OVERLAPPED_POINTS_DATA_FILE, ios_base::app );
			structureOverlappedArea.storeXml( ofFileStructurOverlappedAreaData );
			ofFileStructurOverlappedAreaData.close();
#endif //DEBUG_OUTPUT_OVERLAPPED_POINTS_DATA_FILE
			
		}
#endif //DEBUG_OUTPUT_STRUCTURE_DATA
		
		if ( pImageStructureToUse->getStructurePointsConst().size() < 4 ){
			/*if best image structure contains less than 4 points
			 -> use image structure with constant color and add their point
			 with their property (without converting)*/
			const set< pair< unsigned int, unsigned int> > setStructurePoints =
				pImageStructureToUse->getStructurePointsPair();
			
			for ( set< pair< unsigned int, unsigned int> >::const_iterator
					itrActualPoint = setStructurePoints.begin();
					itrActualPoint != setStructurePoints.end();
					itrActualPoint++ ){
				//for all structure points
				DEBUG_OUT_L3(<<"Structure has less than 4 points: generate Fib point for point ("<<itrActualPoint->first<<", "<<itrActualPoint->second<<")"<<endl<<flush);
				cFibElement * pPointObject =
					generateObjectForPoint( *itrActualPoint );
				
				if ( pPointObject ){
					if ( ! pMainList->addUnderobject( pPointObject, 1 ) ){
						//point object not set -> delete it
						pPointObject->deleteObject();
					}
				}
#ifdef DEBUG
				else{
					cerr<<"   Error: could not generate point"<<endl;
				}
#endif //DEBUG
				pImageSearchData->registerOverlapped( *itrActualPoint );
			}//for all structure points
			if ( pImageAreaSameColor ){
				//delete image structure for same clored area
				delete pImageAreaSameColor;
				pImageAreaSameColor = NULL;
			}
			if ( pImageAreaLinearColor ){
				//delete image structure for same clored area
				delete pImageAreaLinearColor;
				pImageAreaLinearColor = NULL;
			}
			continue;
		}//end if best image structure contains less than 4 point
		//convert found image structure to Fib object
		DEBUG_OUT_L2(<<"Convert found image structure to Fib object"<<endl<<flush);
		cRoot * pConvertedFibObjectToUse =
			pImageStructureToUse->convertToFib( pImageSearchData,
				65536.0, maxErrorPerBorderPoint );
		
		//delete created image structures
		DEBUG_OUT_L2(<<"delete created image structures"<<endl<<flush);
		if ( pImageAreaSameColor ){
			//delete image structure for same clored area
			delete pImageAreaSameColor;
			pImageAreaSameColor = NULL;
		}
		if ( pImageAreaLinearColor ){
			//delete image structure for same clored area
			delete pImageAreaLinearColor;
			pImageAreaLinearColor = NULL;
		}
		if ( pConvertedFibObjectToUse == NULL ){
			//error: no Fib object generated -> try next converted image structure
			DEBUG_OUT_EL2(<<"Error: no Fib object generated -> try next converted image structure: generate Fib point for start point ("<<paNextStartPoint.first<<", "<<paNextStartPoint.second<<")"<<endl<<flush);
			cFibElement * pPointObject =
				generateObjectForPoint( paNextStartPoint );
			
			if ( pPointObject ){
				if ( ! pMainList->addUnderobject( pPointObject, 1 ) ){
					//point object not set -> delete it
					pPointObject->deleteObject();
				}
			}
#ifdef DEBUG
			else{
				cerr<<"Error: could not generate point for start point (could not generate an image structure)"<<endl;
			}
#endif //DEBUG
			pImageSearchData->registerOverlapped( paNextStartPoint );
			continue;
		}
		
#ifdef FEATURE_SEARCH_BORDER_HANDLING
		//evalue overlapped and border with created Fib-object ( evalue() )
		pConvertedFibObjectToUse->evalueObjectSimple(
			*pImageSearchDataForOverlappedBorder );
		
		//make sure the start point is removed from points to find a image structure for
		pImageSearchData->registerOverlapped( paNextStartPoint );
		
#endif //FEATURE_SEARCH_BORDER_HANDLING
		//integrate created Fib object for area into Fib object
		DEBUG_OUT_L2(<<"integrate created Fib object for area into Fib object"<<endl<<flush);
		
		//check if sub roots exists
		const unsignedIntFib uiNumberOfSubRootsGenerated =
			pConvertedFibObjectToUse->getNumberOfSubRootObjects();
		if ( 0 < uiNumberOfSubRootsGenerated ){
			//add just subroots which don't exists till now (compare with equal)
			//evalue generated sub root objects
			list< pair<longFib, cRoot*> > liSubRootObjectsGenerated;
			
			for ( unsignedIntFib uiActualSubObject = 1;
					uiActualSubObject <= uiNumberOfSubRootsGenerated;
					uiActualSubObject++ ){
				
				liSubRootObjectsGenerated.push_back( pConvertedFibObjectToUse->
					getSubRootObject( uiActualSubObject ) );
			}
			//evalue existing sub root objects
			const unsignedIntFib uiNumberOfSubRoots =
				pFibObjectRoot->getNumberOfSubRootObjects();
			list< pair<longFib, cRoot*> > liSubRootObjects;
			longFib lMaxUsedIdentifer = 0;
			
			for ( unsignedIntFib uiActualSubObject = 1;
					uiActualSubObject <= uiNumberOfSubRoots;
					uiActualSubObject++ ){
				
				liSubRootObjects.push_back( pFibObjectRoot->
					getSubRootObject( uiActualSubObject ) );
				lMaxUsedIdentifer = max( lMaxUsedIdentifer,
					liSubRootObjects.back().first );
			}
			/*map the subroots identifiers:
			 * 	- For all generated subroots with changed identifiers:
			 * 		replace identifers in external object elements of generated object
			 * 	- For all generated subroots for which no subroot exists for
			 * 		same identifier: insert needed generated subroots for
			 * 		mapped identifiers into pFibObjectRoot
			 */
			//check if some subobjects allready exists
			map< longFib, longFib > mapIdentifierMapping;
			list< pair<longFib, cRoot*> > liSubRootObjectsToAdd;
			
			for ( list< pair<longFib, cRoot*> >::iterator
					itrActualSubObject = liSubRootObjectsGenerated.begin();
					itrActualSubObject != liSubRootObjectsGenerated.end(); ){
				//try to find an equal subroot in pFibObjectRoot
				if ( itrActualSubObject->second == NULL ){
					//no sub root object
					itrActualSubObject = liSubRootObjectsGenerated.erase(
							itrActualSubObject );
					continue;
				}
				//check subroot with same identifier
				const cRoot * pRootWithSameIdentifier = pFibObjectRoot->
					getSubRootObjectForIdentifier( itrActualSubObject->first );
				bool bOtherSubRootWithSameIdentifierExists = false;
				if ( pRootWithSameIdentifier ){
					if ( pRootWithSameIdentifier->equal( *(itrActualSubObject->second) ) ){
						/*both roots are equal
						 *-> don't need to change anything for inserted Fib object*/
						//equal sub root object exists -> delete generated sub root object
						itrActualSubObject->second->deleteObject();
						itrActualSubObject->second = NULL;
						itrActualSubObject = liSubRootObjectsGenerated.erase(
							itrActualSubObject );
						continue;//check next generated sob root object
					}
					bOtherSubRootWithSameIdentifierExists = true;
				}
				bool bEqualSubRootExists = false;
				//check all existing subroots
				for ( list< pair<longFib, cRoot*> >::const_iterator
						itrActualSubObjectExisting = liSubRootObjects.begin();
						itrActualSubObjectExisting != liSubRootObjects.end();
						itrActualSubObjectExisting++ ){
					
					if ( itrActualSubObject->second->equal(
							*(itrActualSubObjectExisting->second) ) ){
						//equal sub root object exists -> delete generated sub root object
						itrActualSubObject->second->deleteObject();
						itrActualSubObject->second = NULL;
						//both roots are equal -> store mapping
						mapIdentifierMapping.insert( pair< longFib, longFib >(
							itrActualSubObject->first, itrActualSubObjectExisting->first ) );
						itrActualSubObject->first = itrActualSubObjectExisting->first;
						bOtherSubRootWithSameIdentifierExists = false;
						bEqualSubRootExists = true;
						break;//check next generated sob root object
					}
				}//end for check all existing subroots
				if ( bOtherSubRootWithSameIdentifierExists ){
					/*a sub root object with the same identifier exists
					 -> map identifier to a new not used identifer*/
					lMaxUsedIdentifer++;
					mapIdentifierMapping.insert( pair< longFib, longFib >(
						itrActualSubObject->first, lMaxUsedIdentifer ) );
					itrActualSubObject->first = lMaxUsedIdentifer;
				}
				if ( ! bEqualSubRootExists ){
					/* - For all generated subroots for which no equal subroot exists:
					 * 	- insert needed generated subroots for mapped
					 * 		identifiers into existing sub roots pFibObjectRoot */
					liSubRootObjectsToAdd.push_back( *itrActualSubObject );
				}
				
				//check next sub root object
				itrActualSubObject++;
			}
			/*For all generated subroots with changed identifiers:
			 * 	-replace identifers in external object elements of generated object*/
			cExtObject * pActualExtObject = ((cExtObject*)
				pConvertedFibObjectToUse->getNextFibElement( 'o' ));
			for ( ; pActualExtObject != NULL;
					pActualExtObject = ((cExtObject*)
						pActualExtObject->getNextFibElement( 'o' )) ){
				
				const longFib lOldIdentifer = pActualExtObject->getIdentifier();
				
				map< longFib, longFib >::const_iterator itrIdentifierMapping =
					mapIdentifierMapping.find( lOldIdentifer );
				
				if ( itrIdentifierMapping != mapIdentifierMapping.end() ){
					//mapping found -> set new identifer
					pActualExtObject->setIdentifier( itrIdentifierMapping->second );
				}//else do nothing -> next external object
			}
			//move to add (/new) sub root objects
			for ( list< pair<longFib, cRoot*> >::const_iterator
					itrActualSubObject = liSubRootObjectsToAdd.begin();
					itrActualSubObject != liSubRootObjectsToAdd.end();
					itrActualSubObject++ ){
				//add all to add sub root objects
				pFibObjectRoot->addSubRootObject(
					itrActualSubObject->first, itrActualSubObject->second );
			}
		}//end if for sub root objects
		//add the main Fib object to the main list
		DEBUG_OUT_L2(<<"add the main Fib object to the main list"<<endl<<flush);
		cFibElement * pGeneratedObject =
			pConvertedFibObjectToUse->getNextFibElement();
		if ( ( pGeneratedObject == NULL ) ||
				( ! pMainList->addUnderobject( pGeneratedObject, 1 ) ) ){
			//could not add generated Fib object
			pConvertedFibObjectToUse->deleteObject();
			continue;
		}
		delete pConvertedFibObjectToUse;
#ifdef FEATURE_SEARCH_BORDER_HANDLING
		//clear as found marked points
		pImageSearchData->clearFound();
#else //FEATURE_SEARCH_BORDER_HANDLING
		//convert found points of structure to overlapped points
		pImageSearchData->foundToOverlapped();
#endif //FEATURE_SEARCH_BORDER_HANDLING
	}//end while not whole image found
#ifdef DEBUG
	cout<<"end while not whole image found"<<endl;
	cout<<"not overlapped points:";
	{
		const set< pair< unsigned int, unsigned int> > setNotOverlappedPoints =
			pImageSearchData->getNotOverlappedPointsAsPair();
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrPoint = setNotOverlappedPoints.begin();
				itrPoint != setNotOverlappedPoints.end(); itrPoint++ ){
			
			cout<<" ("<<itrPoint->first<<", "<<itrPoint->second<<");";
		}
		cout<<endl;
		
		cImageSearchDataForOverlappedBorder testImageSearchData( pImageData );
		pFibObjectRoot->evalueObjectSimple( testImageSearchData );
		cout<<"not overlapped points for created object:";
		const set< pair< unsigned int, unsigned int> > setNotOverlappedPointsObj =
			testImageSearchData.getNotOverlappedPointsAsPair();
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrPoint = setNotOverlappedPointsObj.begin();
				itrPoint != setNotOverlappedPointsObj.end(); itrPoint++ ){
			
			cout<<" ("<<itrPoint->first<<", "<<itrPoint->second<<");";
		}
		cout<<endl;
	}
	
#endif //DEBUG
	
	if ( pMainList->getNumberOfUnderobjects() < 2 ){
		
		if ( pMainList->getNumberOfUnderobjects() == 0 ){
			//nothing created
			pFibObjectRoot->deleteObject();
			return NULL;
		}//else ( pMainList.getNumberOfUnderobjects() == 1 )
		//set one existing list subobject as main Fib object
		pFibObjectRoot->setMainFibObject( pMainList->getUnderobject( 1 ) );
		delete pMainList;
	}
	//generate needed domains
	pFibObjectRoot->generateNeededDomains();
	//add domains to root object for the image data
	cDomains * pDomainsOfRootObject = pFibObjectRoot->getDomains();
	if ( pDomainsOfRootObject == NULL ){
		//Error: the root element has no domains
		return pFibObjectRoot;
	}
	//add the dimansion domains
	const cDomains domainsImageDimensions = pImageData->getPositionDomain();
	
	const unsignedIntFib uiNumberOfDomains =
		domainsImageDimensions.getNumberOfDomains();
	for ( unsignedIntFib uiActualDimDomain = 1;
			uiActualDimDomain <= uiNumberOfDomains; uiActualDimDomain++ ){
		
		const cDomain * pActualDomain =
			domainsImageDimensions.getDirectDomain( uiActualDimDomain );
		cTypeElement * pActualDimType =
			domainsImageDimensions.getType( uiActualDimDomain );
		
		pDomainsOfRootObject->addDomain( *pActualDimType, *pActualDomain );
	}
	
	//add property domains
	const cDomains domainsImageProperties = pImageData->getPropertyDomains();
	const cTypeProperty propertyType( propertyTypeNumber );
	
	const cDomain * pDomainForUsedProperty =
		domainsImageProperties.getDirectDomainForElement( propertyType );
	pDomainsOfRootObject->addDomain( propertyType, *pDomainForUsedProperty );
	
	if ( bAntialisingUsed ){
		//add domain for antialising
		vector< cDomainSingle * > vecDomainAA( 1 );
		vecDomainAA[ 0 ] = new cDomainNaturalNumberBit( 8, (1.0 / 255.0) );
		const cDomainVector domVecAntialising( vecDomainAA );
		delete vecDomainAA[ 0 ];
		
		const cTypeProperty propertyTypeAntialising( cTypeProperty::TRANSPARENCY );
		pDomainsOfRootObject->addDomain( propertyTypeAntialising, domVecAntialising );
	}
#ifdef DEBUG
	cout<<"cConvertImageToFibForOnePropertySimple::convertToFib() done"<<endl;
	cout<<"not overlapped points:";
	{
		const set< pair< unsigned int, unsigned int> > setNotOverlappedPoints =
			pImageSearchData->getNotOverlappedPointsAsPair();
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrPoint = setNotOverlappedPoints.begin();
				itrPoint != setNotOverlappedPoints.end(); itrPoint++ ){
			
			cout<<" ("<<itrPoint->first<<", "<<itrPoint->second<<");";
		}
		cout<<endl;
		
		cImageSearchDataForOverlappedBorder testImageSearchData( pImageData );
		pFibObjectRoot->evalueObjectSimple( testImageSearchData );
		cout<<"not overlapped points for created object:";
		const set< pair< unsigned int, unsigned int> > setNotOverlappedPointsObj =
			testImageSearchData.getNotOverlappedPointsAsPair();
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrPoint = setNotOverlappedPointsObj.begin();
				itrPoint != setNotOverlappedPointsObj.end(); itrPoint++ ){
			
			cout<<" ("<<itrPoint->first<<", "<<itrPoint->second<<");";
		}
		cout<<endl;
	}
	
#endif //DEBUG
	
	return pFibObjectRoot;
}


/**
 * @return the name of this class
 */
string cConvertImageToFibForOnePropertySimple::getName() const{
	
	return "cConvertImageToFibForOnePropertySimple";
}


/**
 * @return the type number of the property to use (e. g. cTypeProperty::COLOR_RGB )
 * @see propertyTypeNumber
 * @see iImageData::getNumberOfProperties()
 * @see iImageData::getProperty()
 */
unsigned int cConvertImageToFibForOnePropertySimple::getPropertyTypeNumber() const{
	
	return propertyTypeNumber;
}


/**
 * @return the maximal error for a point of the area
 * @see maxErrorPerPoint
 */
double cConvertImageToFibForOnePropertySimple::getMaxErrorPerPoint() const{
	
	return maxErrorPerPoint;
}


/**
 * @return the maximal error for the border points to find on one
 * 	border point; every point in the part areas of the generated
 * 	Fib objects will have a distance lower or equal maxErrorPerBorderPoint
 * 	to a point in the correct area border
 * @see maxErrorPerBorderPoint
 */
double cConvertImageToFibForOnePropertySimple::getMaxErrorPerBorderPoint() const{
	
	return maxErrorPerBorderPoint;
}


/**
 * @return true if the found image structure can be antialised, else the
 * 	image structure should not be antialised
 * @see bCanBeAntialised
 */
const bool cConvertImageToFibForOnePropertySimple::isCanBeAntialised() const{
	
	return bCanBeAntialised;
}

/**
 * @return A list with the operators for the created image structures.
 * 	On every created image structure, which will be converted to a
 * 	Fib object, every operator (from begin to end of the list) will be
 * 	called. @see liOperatoresForImageStructure
 */
const list< iImageStructureSearchOperator * > & cConvertImageToFibForOnePropertySimple::
		getOperatoresForImageStructure() const{
	
	return liOperatoresForImageStructure;
}


/**
 * This method generates for the given point a Fib object.
 *
 * @param paPoint the point for which to generate the Fib object
 * @return the Fib object for the given point or NULL if non could be
 * 	generated; The returned Fib object will consist of a point with the
 * 	given position and a property element for the property in the image
 * 	data for the point
 */
cFibElement * cConvertImageToFibForOnePropertySimple::generateObjectForPoint(
		const pair< unsigned int, unsigned int > & paPoint ) const{
	
	if ( pImageData == NULL ){
		//can't generate Fib object
		return NULL;
	}
	cVectorProperty vecProperty = pImageData->getProperty(
		paPoint, propertyTypeNumber );
	
	if ( vecProperty.getPropertyType() != propertyTypeNumber ){
		/*no property of given type for the point (returned property is type cTypeProperty::NONE)
		 *-> can't generate Fib object */
		return NULL;
	}
	//generate point element
	cVectorPosition vecPosition( 2 );
	vecPosition.setValue( 1, paPoint.first );
	vecPosition.setValue( 2, paPoint.second );
	cPoint * pPoint = new cPoint( &vecPosition );
	//generate property element
	cProperty * pProperty = new cProperty( vecProperty, pPoint );
	
	return pProperty;
}


/**
 * This function checks if the width of the given image structure is lower
 * the given value uiWidth in both directions.
 * (The width is the distance of the position elements in the two dimensions.)
 *
 * @param pImageStructureToUse the image structure of which to check the width
 * @param uiWidth the maximal width the image structure should have
 * @return true if given the image structure has a width lower uiWidth, else false
 */
bool cConvertImageToFibForOnePropertySimple::checkWidthLower(
		const cImageStructure * pImageStructureToUse, const unsigned int uiWidth ) const{
	
	const doubleFib dWidth = uiWidth;
	
	if ( pImageStructureToUse == NULL ){
		//no image structure -> width lower 0
		return true;
	}
	const set<cVectorPosition> & setStructurePoints =
		pImageStructureToUse->getStructurePointsConst();
	if ( setStructurePoints.empty() ){
		//no image structure points -> width lower 0
		return true;
	}
	
	/*evalue width first and last point in the image structure first
	 -> init with last point values*/
	doubleFib dMinDim1 = setStructurePoints.rbegin()->getValue( 1 );
	doubleFib dMaxDim1 = setStructurePoints.rbegin()->getValue( 1 );
	doubleFib dMinDim2 = setStructurePoints.rbegin()->getValue( 2 );
	doubleFib dMaxDim2 = setStructurePoints.rbegin()->getValue( 2 );
	
	for ( set<cVectorPosition>::const_iterator
			itrActualPoint = setStructurePoints.begin();
			itrActualPoint != setStructurePoints.end(); itrActualPoint++ ){
		
		dMinDim1 = min( dMinDim1, itrActualPoint->getValue( 1 ) );
		dMaxDim1 = max( dMaxDim1, itrActualPoint->getValue( 1 ) );
		dMinDim2 = min( dMinDim2, itrActualPoint->getValue( 2 ) );
		dMaxDim2 = max( dMaxDim2, itrActualPoint->getValue( 2 ) );
		
		if ( ( dWidth <= (dMaxDim1 - dMinDim1) ) &&
				( dWidth <= (dMaxDim2 - dMinDim2) ) ){
			//the width of the structure is bigger than uiWidth in both directions
			return false;
		}//else check next point
	}//end for all structure points
	//the width of the structure points is less than uiWidth in one direction
	return true;
}




