/**
 * @file cFindImageAreaSameColorSimple
 * file name: cFindImageAreaSameColorSimple.cpp
 * @author Betti Oesterholz
 * @date 18.02.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements a class for searching for a structure with
 * constant color in an image.
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
 * This file implements a class for searching for a structure with
 * constant color in an image.
 * For this a method findImageStructure() is defined.
 * If you want to convert an image to Fib structures, you have to search
 * the image for structures, which can be converted to Fib.
 * For this you can use this class.
 * @see findImageStructure()
 *
 * @pattern Strategy
 * @see cImageAreaSameColor
 * @see cConvertImageToFib
 * @see iFindImageStructure
 * @see iConvertImageStructureToFib
 */
/*
History:
18.02.2013  Oesterholz  created
*/

//switches for debugging proposes
//#define DEBUG

#include "version.h"

#include "cFindImageAreaSameColorSimple.h"

#include "cVectorProperty.h"

#include <list>
#include <set>


using namespace std;
using namespace fib::algorithms::nConvertToFib::nImage::nSearchForStructure;
using namespace fib::algorithms::nConvertToFib::nImage::nStructureData;


/**
 * Constructor
 *
 * @param uiPropertyType the type number of the property to use;
 * 	(e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
 * @param dMaxErrorPerPoint the maximal error for a point of the area
 * 	@see maxErrorPerPoint
 * @param bInCanBeAntialised if true the found image structure can be
 * 	antialised, else the image structure should not antialised
 * 	@see bCanBeAntialised
 * @param uiInNumberOfMaxCenterColorAdaptions The number of maximal
 * 	retrys to find a better color for the area.
 * 	Note if maxErrorPerPoint is 0 this property is irrelevant.
 * 	@see uiNumberOfMaxCenterColorAdaptions
 */
cFindImageAreaSameColorSimple::cFindImageAreaSameColorSimple(
		unsigned int uiPropertyType, const double dMaxErrorPerPoint,
		const bool bInCanBeAntialised,
		const unsigned int uiInNumberOfMaxCenterColorAdaptions ):
		propertyTypeNumber( uiPropertyType ),
		maxErrorPerPoint( dMaxErrorPerPoint ),
		bCanBeAntialised( bInCanBeAntialised ),
		uiNumberOfMaxCenterColorAdaptions( uiInNumberOfMaxCenterColorAdaptions ){
	
	DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::cFindImageAreaSameColorSimple( uiPropertyType="<<uiPropertyType<<", dMaxErrorPerPoint="<<dMaxErrorPerPoint<<", bInCanBeAntialised="<<(bInCanBeAntialised?"true":"false")<<", uiInNumberOfMaxCenterColorAdaptions="<<uiInNumberOfMaxCenterColorAdaptions<<" )"<<endl<<flush);
	
	zeroErrorValue = 0.0000000001;
	
	//nothing to do
}


/**
 * This method is for searching in an image for an area with the same color.
 * If the returned structure is antialised, the border points of the
 * structure, will not be in the structure points of the structure.
 * @see cImageStructure::bIsAntialised
 * @see cImageStructure::structureBorderPoints
 * @see cImageStructure::structurePoints
 * Also the neighbour points of the generated structure will just contain
 * points not overlapped in the search structure.
 * @see cImageStructure::structureNeighbourPoints
 * @see cImageSearchData::pImageDataOverlapped
 * In the search structure (pConvertImageToFib->getImageSearchData())
 * no points should be set as found befor the method start, this method
 * will set all structure points as found.
 *
 * @param paStartPoint the point where to start the search;
 * 	it will be included in the generated image structure
 * @param pConvertImageToFib a pointer to the object for converting an
 * 	image to a Fib object (it should implement methods to get the
 * 	image search data);
 * 	The image data (getImageData()) of the search data
 * 	(pConvertImageToFib->getImageSearchData()) should have a
 * 	propertyTypeNumber'th property for each point.
 * @return the found image structure, or the null pointer NULL if non
 * 	could be found
 * 	Beware: You have to delete the returned image structure after usage.
 */
cImageAreaSameColor * cFindImageAreaSameColorSimple::findImageStructure(
		const pair< long, long> paStartPoint,
		cConvertImageToFib * pConvertImageToFib ) const{
	
	DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::findImageStructure( paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), pConvertImageToFib="<<pConvertImageToFib<<" ) started"<<endl<<flush);
	
	if ( pConvertImageToFib == NULL ){
		//no convert object
		DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::findImageStructure() done: no convert object"<<endl<<flush);
		return NULL;
	}
	//get image search structure
	cImageSearchData * pImageSearchData =
		pConvertImageToFib->getImageSearchData();
	if ( pImageSearchData == NULL ){
		//no search data
		DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::findImageStructure() done: no search data"<<endl<<flush);
		return NULL;
	}
	const iImageData * pImageData = pImageSearchData->getImageData();
	if ( pImageData == NULL ){
		//no image data
		DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::findImageStructure() done: no image data"<<endl<<flush);
		return NULL;
	}
	
	
	{//evalue value for zero error
		zeroErrorValue = 0.0000000001;
		const vector< unsigned int > vecIndexDim3 =
			pImageData->getDimension3IndexesForPropertyType( propertyTypeNumber );
		for ( vector< unsigned int >::const_iterator
				itrActualIndex = vecIndexDim3.begin();
				itrActualIndex != vecIndexDim3.end(); itrActualIndex++ ){
			
			zeroErrorValue *= pImageData->getMinDifference(
				0, 0, (*itrActualIndex) );
		}
		DEBUG_OUT_L3(<<"cFindImageAreaSameColorSimple("<<this<<") the zero value is "<<zeroErrorValue<<endl<<flush);
	}
	pair< unsigned int, unsigned int> vecStartPoint( paStartPoint );
	
	bool bIsAntialised = false;
	if ( bCanBeAntialised ){
		// check if an other point should be used, becaus area is antialised
		DEBUG_OUT_L2(<<"check if an other point should be used, becaus area is antialised"<<endl<<flush);
		pair< unsigned int, unsigned int> * pVecNewStartPoint =
			checkIfStartPointIsAntialised( vecStartPoint, maxErrorPerPoint, pConvertImageToFib );
		
		if ( pVecNewStartPoint ){
			//area should be antialised
			DEBUG_OUT_L2(<<"Area should be antialised new start point: ("<<pVecNewStartPoint->first<<", "<<pVecNewStartPoint->second<<")"<<endl<<flush);
			vecStartPoint = (*pVecNewStartPoint);
			delete pVecNewStartPoint;
			bIsAntialised = true;
		}
	}//end check if the area should be antialised
	
	//create image structure to use, with the color of the area/start point
	cImageAreaSameColor * pFoundImageStructure = new cImageAreaSameColor(
		pImageData->getProperty( vecStartPoint, propertyTypeNumber ) );
	
	bool bNeighboursInSearchStructure = true;
	if ( maxErrorPerPoint != 0.0 ){
		//error is possible -> maybe try to find better area color
		pair< unsigned int, unsigned int> vecActualPointCenterProperty(
			vecStartPoint );
		bool bSearchForBetterArea = true;
		
		for ( unsigned int iteration = 0; bSearchForBetterArea &&
				( iteration < uiNumberOfMaxCenterColorAdaptions ) ; iteration++ ){
			//evalue best area with same color
			set< pair< unsigned int, unsigned int> > setOutStructurePoints;
			set< pair< unsigned int, unsigned int> > setOutStructureNeighboursPoints;
			
			pair< unsigned int, unsigned int> * pVecNewActualCenterProperty =
				cFindImageAreaSameColorSimple::convertToAreaAndSearchForBetterColor(
					vecStartPoint, vecActualPointCenterProperty, maxErrorPerPoint,
					pConvertImageToFib,
					setOutStructurePoints, setOutStructureNeighboursPoints );
			bSearchForBetterArea = false;
			
			if ( pFoundImageStructure->getStructurePointsConst().size() <
					setOutStructurePoints.size() ){
				//new evalued structure is bigger
				pFoundImageStructure->setStructurePoints( setOutStructurePoints );
				pFoundImageStructure->setStructureNeighbourPoints(
					setOutStructureNeighboursPoints );
				pFoundImageStructure->setColorOfArea( pImageData->getProperty(
					vecActualPointCenterProperty, propertyTypeNumber ) );
				
				//set new area color
				if ( pVecNewActualCenterProperty == NULL ){
					//no better color found -> stop searching
					break;
				}
				if ( maxErrorPerPoint < pImageData->getDifference(
						vecStartPoint, *pVecNewActualCenterProperty,
						propertyTypeNumber ) ){
					//the start point should be allways included in the area
					delete pVecNewActualCenterProperty;
					break;
				}
				//change center color for which to try to find an area
				vecActualPointCenterProperty = (*pVecNewActualCenterProperty);
				delete pVecNewActualCenterProperty;
				bSearchForBetterArea = true;
				//next iteration
			}else{//new area not bigger -> don't evalue more areas
				//use old search structure
				pImageSearchData->clearFound();
				pImageSearchData->registerFound(
					pFoundImageStructure->getStructurePointsConst() );
				bNeighboursInSearchStructure = false;
				
				if ( pVecNewActualCenterProperty ){
					delete pVecNewActualCenterProperty;
				}
				break;
			}
		}//end while search for area
		if ( bSearchForBetterArea ){
			//search for area (version without get next color)
			set< pair< unsigned int, unsigned int> > setOutStructurePoints;
			set< pair< unsigned int, unsigned int> > setOutStructureNeighboursPoints;
			
			cFindImageAreaSameColorSimple::convertToArea(
				vecStartPoint, vecActualPointCenterProperty, maxErrorPerPoint,
				pConvertImageToFib,
				setOutStructurePoints, setOutStructureNeighboursPoints );
			
			if ( pFoundImageStructure->getStructurePointsConst().size() <
					setOutStructurePoints.size() ){
				//new evalued structure is bigger
				pFoundImageStructure->setStructurePoints( setOutStructurePoints );
				pFoundImageStructure->setStructureNeighbourPoints(
					setOutStructureNeighboursPoints );
				pFoundImageStructure->setColorOfArea( pImageData->getProperty(
					vecActualPointCenterProperty, propertyTypeNumber ) );
			}else{//new area not bigger
				//use old search structure
				pImageSearchData->clearFound();
				pImageSearchData->registerFound(
					pFoundImageStructure->getStructurePointsConst() );
				bNeighboursInSearchStructure = false;
			}
		}
	}else{//maxErrorPerPoint == 0 -> no max error needed, perfect match with start point
		set< pair< unsigned int, unsigned int> > setOutStructurePoints;
		set< pair< unsigned int, unsigned int> > setOutStructureNeighboursPoints;
		
		cFindImageAreaSameColorSimple::convertToArea(
			vecStartPoint, pConvertImageToFib,
			setOutStructurePoints, setOutStructureNeighboursPoints );
		
		pFoundImageStructure->setStructurePoints( setOutStructurePoints );
		pFoundImageStructure->setStructureNeighbourPoints(
			setOutStructureNeighboursPoints );
	}
	
	if ( bCanBeAntialised ){
		/* if antialising is possible
		*-> check if border neighbours are antialised border
		*-> if yes add them as new border and make area antitalised*/
		if (! bNeighboursInSearchStructure ){
			//neighbours needed in search structure -> add them
			pImageSearchData->registerFound(
				pFoundImageStructure->getStructureNeighbourPointsConst() );
			bNeighboursInSearchStructure = true;
		}
		set< pair< unsigned int, unsigned int> > setStructureNeighboursNeighboursPoints;
		
		if ( ! bIsAntialised ){
			if ( checkIfBorderIsAntialised( pFoundImageStructure,
					pImageSearchData,
					setStructureNeighboursNeighboursPoints ) ){
				//structure is antialised
				DEBUG_OUT_L2(<<"structure is antialised"<<endl<<flush);
				bIsAntialised = true;
			}
		}else{/*start point was allready antialised
			-> generate structure neighbours neighbours
			setStructureNeighboursNeighboursPoints*/
			const set< pair< unsigned int, unsigned int> >
				setStructureNeighboursPoints =
					pFoundImageStructure->getStructureNeighbourPointsPair();
			for ( set< pair< unsigned int, unsigned int> >::const_iterator
					itrNeighbour = setStructureNeighboursPoints.begin();
					itrNeighbour != setStructureNeighboursPoints.end();
					itrNeighbour++ ){
				/* find not found border neighbours ( setBorderNeigbours )
				* neighbours which are not neighbours*/
				const set< pair< unsigned int, unsigned int> >
					setPointsNeighbourNeighbours =
						pImageSearchData->getNotFoundNotOverlappedNeighbours(
							*itrNeighbour );
				setStructureNeighboursNeighboursPoints.insert(
					setPointsNeighbourNeighbours.begin(),
					setPointsNeighbourNeighbours.end() );
			}
		}
		if ( bIsAntialised ){
			//add the actual border neighbour points as new border points to structure
			pFoundImageStructure->setStructureBorderPoints(
				pFoundImageStructure->getStructureNeighbourPointsConst() );
			//now the border points are correct
			pFoundImageStructure->setStructureNeighbourPoints(
				setStructureNeighboursNeighboursPoints );
			pFoundImageStructure->setAntialised( true );
		}
	}
	if ( ! bIsAntialised ){
		//unregister the neighbour points as found
		const set< pair< unsigned int, unsigned int> >
			setStructureNeighboursPoints =
				pFoundImageStructure->getStructureNeighbourPointsPair();
		if ( bNeighboursInSearchStructure ){
			pImageSearchData->registerFound( setStructureNeighboursPoints, false );
		}
		/*the neighbour points are correct, but the border points needs to be evalued
		-> evalue border points
		pre: all structure points are marked as found but no structure
			neighbour point or other point is marked as found*/
		
		set< pair< unsigned int, unsigned int> > setStructureBorderPoints;
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrNeighbour = setStructureNeighboursPoints.begin();
				itrNeighbour != setStructureNeighboursPoints.end();
				itrNeighbour++ ){
			/* find found points of neighbours, which are in the structure
			 * (because they are found) and so structure border points */
			const set< pair< unsigned int, unsigned int> >
				setPointsFoundNeighbourNeighbours =
					pImageSearchData->getFoundNeighbours( *itrNeighbour );
			setStructureBorderPoints.insert(
				setPointsFoundNeighbourNeighbours.begin(),
				setPointsFoundNeighbourNeighbours.end() );
		}
		pFoundImageStructure->setStructureBorderPoints(
			setStructureBorderPoints );
	}
	
	DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::findImageStructure() done: found image structure "<<pFoundImageStructure<<endl<<flush);
	return pFoundImageStructure;
}


/**
 * @return the name of this class
 */
string cFindImageAreaSameColorSimple::getName() const{
	
	return "cFindImageAreaSameColorSimple";
}


/**
 * This method is for searching in an image for an area with the same color.
 * The neighbour points of the generated structure will just contain
 * points not overlapped in the search structure.
 * @see cImageStructure::structureNeighbourPoints
 * @see cImageSearchData::pImageDataOverlapped
 * In the search structure (pConvertImageToFib->getImageSearchData()) this
 * method will set all structure points and there neighbour points as found.
 *
 * @param vecStartPoint the point where to start the search;
 * 	it will be included in the generated image structure setOutStructurePoints
 * @param vecCenterPropertyPoint point with the the property the area
 * 	should have; it is the center property to which the distance for
 * 	dMaxErrorPerPoint will be evalued
 * @param dMaxErrorPerPoint the maximal error for a point of the area
 * @param pConvertImageToFib a pointer to the object for converting an
 * 	image to a Fib object (it should implement methods to get the
 * 	image search data);
 * 	The image data (getImageData()) of the search data
 * 	(pConvertImageToFib->getImageSearchData()) should have a
 * 	propertyTypeNumber'th property for each point.
 * @param setOutStructurePoints a reference to a set to output the
 * 	structure points to
 * @param setOutStructureNeighboursPoints a reference to a set to output
 * 	the structure neighbour points to
 * @return a pointer to a point, for which property it could be usefull to
 * 	generate a new area
 * 	Beware: You have to delete the returned point after usage.
 */
pair< unsigned int, unsigned int> * cFindImageAreaSameColorSimple::
		convertToAreaAndSearchForBetterColor(
		const pair< unsigned int, unsigned int> & vecStartPoint,
		const pair< unsigned int, unsigned int> & vecCenterPropertyPoint,
		const double dMaxErrorPerPoint,
		cConvertImageToFib * pConvertImageToFib,
		set< pair< unsigned int, unsigned int> > & setOutStructurePoints,
		set< pair< unsigned int, unsigned int> > & setOutStructureNeighboursPoints ) const{
	
	if ( pConvertImageToFib == NULL ){
		//no convert object
		return NULL;
	}
	if ( dMaxErrorPerPoint == 0.0 ){
		//no maximal error per point -> use other method for this case
		convertToArea( vecStartPoint, pConvertImageToFib,
			setOutStructurePoints, setOutStructureNeighboursPoints );
		//no better property possible
		return NULL;
	}
	DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::convertToAreaAndSearchForBetterColor( vecStartPoint=("<<vecStartPoint.first<<", "<<vecStartPoint.second<<"), vecCenterPropertyPoint=("<<vecCenterPropertyPoint.first<<", "<<vecCenterPropertyPoint.second<<"), dMaxErrorPerPoint="<<dMaxErrorPerPoint<<", pConvertImageToFib="<<pConvertImageToFib<<", setOutStructurePoints, setOutStructureNeighboursPoints ) started"<<endl<<flush);
	
	//get image search structure
	cImageSearchData * pImageSearchData =
		pConvertImageToFib->getImageSearchData();
	if ( pImageSearchData == NULL ){
		//no search data
		return NULL;
	}
	
	const iImageData * pImageData = pImageSearchData->getImageData();
	if ( pImageData == NULL ){
		//no image data
		return NULL;
	}
	pImageSearchData->clearFound();
	
	const cVectorProperty vecAreaColor = pImageData->getProperty(
		vecCenterPropertyPoint, propertyTypeNumber );
	
	//the border points of the actual search area to check
	list< pair< unsigned int, unsigned int> > liBorderPoints;
	liBorderPoints.push_back( vecStartPoint );
	pImageSearchData->registerFound( vecStartPoint );
	
	//the points in the structure (inclusive border) sorted to ther properties
	map< cVectorProperty, set< pair< unsigned int, unsigned int> > > mapStructurePointsForProperties;
	unsigned long ulMaxPointsWithSameColor = 0;
	
	const cVectorProperty * pColorMaxPointsWithSameColor = NULL;
	
	while ( ! liBorderPoints.empty() ){
		//choose good border point to enlarge area for
		const pair< unsigned int, unsigned int> & vecActualPoint =
			liBorderPoints.front();
		setOutStructurePoints.insert( vecActualPoint );
		
		//get neighbour points of choosen border point
		const set< pair< unsigned int, unsigned int> > setPointsToCheck =
			pImageSearchData->getNotFoundNotOverlappedNeighbours(
				vecActualPoint );
		if ( setPointsToCheck.empty() ){
			//no neighbours to check -> check next border point
			liBorderPoints.pop_front();
			continue;
		}
		//check every point once
		pImageSearchData->registerFound( setPointsToCheck );
		
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrNeighbour = setPointsToCheck.begin();
				itrNeighbour != setPointsToCheck.end(); itrNeighbour++ ){
			/*check the neighbour points if their error is smaal enougth and add
			 *them to the structure if */
			//get actual property
			const cVectorProperty vecNeighbourProperty =
				pImageData->getProperty( *itrNeighbour, propertyTypeNumber );
			//check the points error (on the area color)
			const doubleFib dErrorOfNeighbour =
				vecAreaColor.distanceToProperty( vecNeighbourProperty );
			if ( dMaxErrorPerPoint < dErrorOfNeighbour ){
				//error for point to great -> skip it
				//neighbour point is area neighbour point
				setOutStructureNeighboursPoints.insert( *itrNeighbour );
				continue;
			}//else error smaal enougth -> register as border point
			//add the point to border points
			liBorderPoints.push_back( *itrNeighbour );
			
			
			//add point to mapStructurePointsForProperties
			set< pair< unsigned int, unsigned int> > & setPointsForNeighbourProperty =
				mapStructurePointsForProperties[ vecNeighbourProperty ];
			
			setPointsForNeighbourProperty.insert( *itrNeighbour );
			
			if ( ulMaxPointsWithSameColor < setPointsForNeighbourProperty.size() ){
				//update number max point with same color
				ulMaxPointsWithSameColor = setPointsForNeighbourProperty.size();
				
				map< cVectorProperty, set< pair< unsigned int, unsigned int> > >::iterator
					itrPointsForPropertie =
						mapStructurePointsForProperties.find( vecNeighbourProperty );
					
				pColorMaxPointsWithSameColor = &(itrPointsForPropertie->first);
			}
		}//end for all neighbour points
		//remove choosen border point from search/check border
		liBorderPoints.pop_front();
	}//end while border points to check
	if ( pColorMaxPointsWithSameColor == NULL ){
		//no better maximal points given
		return NULL;
	}
	const doubleFib dMaxPointsDistance = vecAreaColor.distanceToProperty(
		*pColorMaxPointsWithSameColor );
	if ( dMaxPointsDistance < ( dMaxErrorPerPoint / 1000000.0 ) ){
		/*maximal points with error are very close to center property
		-> don't try new property*/
		DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::convertToAreaAndSearchForBetterColor() done: maximal points with error are very close to center property -> don't try new property"<<endl<<flush);
		return NULL;
	}
	const double dPointsWithCenterColor =
		mapStructurePointsForProperties[ vecAreaColor ].size();
	
	if ( ( (2.3 - ( dMaxPointsDistance / dMaxErrorPerPoint ) ) *
			dPointsWithCenterColor ) < ((double)(ulMaxPointsWithSameColor)) ){
		//you can try the property of max points with same property as next area property
		DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::convertToAreaAndSearchForBetterColor() done: new center point=("<<(mapStructurePointsForProperties[
			*pColorMaxPointsWithSameColor ].begin() )->first<<", "<<(mapStructurePointsForProperties[
			*pColorMaxPointsWithSameColor ].begin() )->second<<" )"<<endl<<flush);
		return new pair< unsigned int, unsigned int>( *(mapStructurePointsForProperties[
			*pColorMaxPointsWithSameColor ].begin() ) );
	}
	DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::convertToAreaAndSearchForBetterColor() done: don't try new property"<<endl<<flush);
	//don't try new property
	return NULL;
}


/**
 * This method is for searching in an image for an area with the same color.
 * The neighbour points of the generated structure will just contain
 * points not overlapped in the search structure.
 * @see cImageStructure::structureNeighbourPoints
 * @see cImageSearchData::pImageDataOverlapped
 * In the search structure (pConvertImageToFib->getImageSearchData()) this
 * method will set all structure points and there neighbour points as found.
 *
 * @param vecStartPoint the point where to start the search;
 * 	it will be included in the generated image structure setOutStructurePoints
 * @param vecCenterPropertyPoint point with the the property the area
 * 	should have; it is the center property to which the distance for
 * 	dMaxErrorPerPoint will be evalued
 * @param dMaxErrorPerPoint the maximal error for a point of the area
 * @param pConvertImageToFib a pointer to the object for converting an
 * 	image to a Fib object (it should implement methods to get the
 * 	image search data);
 * 	The image data (getImageData()) of the search data
 * 	(pConvertImageToFib->getImageSearchData()) should have a
 * 	propertyTypeNumber'th property for each point.
 * @param setOutStructurePoints a reference to a set to output the
 * 	structure points to
 * @param setOutStructureNeighboursPoints a reference to a set to output
 * 	the structure neighbour points to
 */
void cFindImageAreaSameColorSimple::convertToArea(
		const pair< unsigned int, unsigned int> & vecStartPoint,
		const pair< unsigned int, unsigned int> & vecCenterPropertyPoint,
		const double dMaxErrorPerPoint,
		cConvertImageToFib * pConvertImageToFib,
		set< pair< unsigned int, unsigned int> > & setOutStructurePoints,
		set< pair< unsigned int, unsigned int> > & setOutStructureNeighboursPoints ) const{
	
	if ( pConvertImageToFib == NULL ){
		//no convert object
		return;
	}
	if ( dMaxErrorPerPoint == 0.0 ){
		//no maximal error per point -> use other method for this case
		convertToArea( vecStartPoint, pConvertImageToFib,
			setOutStructurePoints, setOutStructureNeighboursPoints );
		return;
	}
	DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::convertToArea( vecStartPoint=("<<vecStartPoint.first<<", "<<vecStartPoint.second<<"), vecCenterPropertyPoint=("<<vecCenterPropertyPoint.first<<", "<<vecCenterPropertyPoint.second<<"), dMaxErrorPerPoint="<<dMaxErrorPerPoint<<", pConvertImageToFib="<<pConvertImageToFib<<", setOutStructurePoints, setOutStructureNeighboursPoints ) started"<<endl<<flush);
	
	//get image search structure
	cImageSearchData * pImageSearchData =
		pConvertImageToFib->getImageSearchData();
	if ( pImageSearchData == NULL ){
		//no search data
		return;
	}
	
	const iImageData * pImageData = pImageSearchData->getImageData();
	if ( pImageData == NULL ){
		//no image data
		return;
	}
	pImageSearchData->clearFound();
	
	//the border points of the actual search area to check
	list< pair< unsigned int, unsigned int> > liBorderPoints;
	liBorderPoints.push_back( vecStartPoint );
	pImageSearchData->registerFound( vecStartPoint );
	
	while ( ! liBorderPoints.empty() ){
		//choose good border point to enlarge area for
		const pair< unsigned int, unsigned int> & vecActualPoint =
			liBorderPoints.front();
		setOutStructurePoints.insert( vecActualPoint );
		
		//get neighbour points of choosen border point
		const set< pair< unsigned int, unsigned int> > setPointsToCheck =
			pImageSearchData->getNotFoundNotOverlappedNeighbours(
				vecActualPoint );
		if ( setPointsToCheck.empty() ){
			//no neighbours to check -> check next border point
			liBorderPoints.pop_front();
			continue;
		}
		//check every point once
		pImageSearchData->registerFound( setPointsToCheck );
		
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrNeighbour = setPointsToCheck.begin();
				itrNeighbour != setPointsToCheck.end(); itrNeighbour++ ){
			/*check the neighbour points if their error is smaal enougth and
			 *add them to the structure if */
			//check the points error (on the area color)
			const doubleFib dErrorOfNeighbour =
				pImageData->getDifference( vecCenterPropertyPoint, *itrNeighbour,
					propertyTypeNumber );
			if ( dMaxErrorPerPoint < dErrorOfNeighbour ){
				//error for point to great -> skip it
				//neighbour point is area neighbour point
				setOutStructureNeighboursPoints.insert( *itrNeighbour );
				continue;
			}//else error smaal enougth -> register as border point
			//add point to border points
			liBorderPoints.push_back( (*itrNeighbour) );
		}//end for all neighbour points
		//remove choosen border point from search/check border
		liBorderPoints.pop_front();
	}//end while border points to check
	
	DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::convertToArea() done"<<endl<<flush);
}


/**
 * This method is for searching in an image for an area with the same color.
 * The neighbour points of the generated structure will just contain
 * points not overlapped in the search structure.
 * @see cImageStructure::structureNeighbourPoints
 * @see cImageSearchData::pImageDataOverlapped
 * In the search structure (pConvertImageToFib->getImageSearchData()) this
 * method will set all structure points and there neighbour points as found.
 * (Note every maxErrorPerPoint will be ignored, properties have to
 * match perfect.)
 *
 * @param vecStartPoint the point where to start the search;
 * 	it will be included in the generated image structure
 * @param pConvertImageToFib a pointer to the object for converting an
 * 	image to a Fib object (it should implement methods to get the
 * 	image search data);
 * 	The image data (getImageData()) of the search data
 * 	(pConvertImageToFib->getImageSearchData()) should have a
 * 	propertyTypeNumber'th property for each point.
 * @param setOutStructurePoints a reference to a set to output the
 * 	structure points to
 * @param setOutStructureNeighboursPoints a reference to a set to output
 * 	the structure neighbour points to
 */
void cFindImageAreaSameColorSimple::convertToArea(
		const pair< unsigned int, unsigned int> & vecStartPoint,
		cConvertImageToFib * pConvertImageToFib,
		set< pair< unsigned int, unsigned int> > & setOutStructurePoints,
		set< pair< unsigned int, unsigned int> > & setOutStructureNeighboursPoints ) const{
	
	DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::convertToArea( vecStartPoint=("<<vecStartPoint.first<<", "<<vecStartPoint.second<<"), pConvertImageToFib="<<pConvertImageToFib<<", setOutStructurePoints, setOutStructureNeighboursPoints ) started"<<endl<<flush);
	
	if ( pConvertImageToFib == NULL ){
		//no convert object
		return;
	}
	//get image search structure
	cImageSearchData * pImageSearchData =
		pConvertImageToFib->getImageSearchData();
	if ( pImageSearchData == NULL ){
		//no search data
		return;
	}
	const iImageData * pImageData = pImageSearchData->getImageData();
	if ( pImageData == NULL ){
		//no image data
		return;
	}
	pImageSearchData->clearFound();
	
	//the border points of the actual search area to check
	list< pair< unsigned int, unsigned int> > liCorrectBorder;
	liCorrectBorder.push_back( vecStartPoint );
	pImageSearchData->registerFound( vecStartPoint );
	
	while ( ! liCorrectBorder.empty() ){
		//choose good border point to enlarge area for
		const pair< unsigned int, unsigned int> & vecActualPoint =
			liCorrectBorder.front();
		setOutStructurePoints.insert( vecActualPoint );
		
		//get neighbour points of choosen border point
		const set< pair< unsigned int, unsigned int> > setPointsToCheck =
			pImageSearchData->getNotFoundNotOverlappedNeighbours(
				vecActualPoint );
		if ( setPointsToCheck.empty() ){
			//no neighbours to check -> check next border point
			liCorrectBorder.pop_front();
			continue;
		}
		//check every point once
		pImageSearchData->registerFound( setPointsToCheck );
		
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrNeighbour = setPointsToCheck.begin();
				itrNeighbour != setPointsToCheck.end(); itrNeighbour++ ){
			/* check the neighbour points if their error is smaal enougth and
			 * add them to the structure if */
			//check the points error (on the area color)
			const doubleFib dErrorOfNeighbour =
				pImageData->getDifference( vecStartPoint, *itrNeighbour,
					propertyTypeNumber );
			if ( zeroErrorValue < dErrorOfNeighbour ){
				//error for point to great -> skip it
				//neighbour point is area neighbour point
				setOutStructureNeighboursPoints.insert( *itrNeighbour );
				continue;
			}//else the points has no error -> register as border point
			liCorrectBorder.push_back( *itrNeighbour );
		}//end for all neighbour points
		//remove choosen border point from search/check border
		liCorrectBorder.pop_front();
	}//end while border points to check
	
	DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::convertToArea() done"<<endl<<flush);
}




/**
 * This method checks if the area should be antialised and returns a
 * new starting point not in the antialised border of the area.
 *
 * @param vecStartPoint the point where to start the search
 * @param dMaxErrorPerPoint the maximal error for a point of the area
 * @param pConvertImageToFib a pointer to the object for converting an
 * 	image to a Fib object (it should implement methods to get the
 * 	image search data);
 * 	The image data (getImageData()) of the search data
 * 	(pConvertImageToFib->getImageSearchData()) should have a
 * 	propertyTypeNumber'th property for each point.
 * @return the point wich should be used as the start point because the
 * 	area is antialised, or NULL if the start point is not antialised
 * 	Beware: You have to delete the returned point after usage.
 */
pair< unsigned int, unsigned int> * cFindImageAreaSameColorSimple::
	checkIfStartPointIsAntialised(
		const pair< unsigned int, unsigned int> & vecStartPoint,
		const double dMaxErrorPerPoint,
		cConvertImageToFib * pConvertImageToFib ) const{
	
	if ( pConvertImageToFib == NULL ){
		//no convert object
		return NULL;
	}
	//get image search structure
	cImageSearchData * pImageSearchData =
		pConvertImageToFib->getImageSearchData();
	if ( pImageSearchData == NULL ){
		//no search data
		return NULL;
	}
	const iImageData * pImageData = pImageSearchData->getImageData();
	if ( pImageData == NULL ){
		//no image data -> not antialised
		return NULL;
	}
	DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::checkIfStartPointIsAntialised( vecStartPoint=("<<vecStartPoint.first<<", "<<vecStartPoint.second<<"), dMaxErrorPerPoint="<<dMaxErrorPerPoint<<", pConvertImageToFib ) started"<<endl<<flush);

	/* if antialised if possible and start point is antialised point
	 * - set area to antialised
	 * - choose new start point (and start property) from not overlapped
	 * 	neighbours with no overlapped neighbours of start point
	 */
	//get the not overlapped neighbours
	set< pair< unsigned int, unsigned int> > setNotOverlappedNeighbours =
		pImageSearchData->getNotOverlappedNeighbours( vecStartPoint );
	
	//get neighbours (till distance 3) points which wher overlapped
	const set< pair< unsigned int, unsigned int> > setOverlappedNeighboursDist1 =
		pImageSearchData->getOverlappedNeighbours( vecStartPoint );
	
	set< pair< unsigned int, unsigned int> > setOverlappedNeighboursDist2;
	for ( set< pair< unsigned int, unsigned int> >::iterator
			itrNeighbour = setOverlappedNeighboursDist1.begin();
			itrNeighbour != setOverlappedNeighboursDist1.end(); itrNeighbour++ ){
		
		const set< pair< unsigned int, unsigned int> > setOverlappedNeighboursNeig =
			pImageSearchData->getOverlappedNeighbours( *itrNeighbour );
		setOverlappedNeighboursDist2.insert( setOverlappedNeighboursNeig.begin(),
			setOverlappedNeighboursNeig.end() );
	}
	set< pair< unsigned int, unsigned int> > setOverlappedNeighbours;
	for ( set< pair< unsigned int, unsigned int> >::iterator
			itrNeighbour = setOverlappedNeighboursDist2.begin();
			itrNeighbour != setOverlappedNeighboursDist2.end(); itrNeighbour++ ){
		
		const set< pair< unsigned int, unsigned int> > setOverlappedNeighboursNeig =
			pImageSearchData->getOverlappedNeighbours( *itrNeighbour );
		setOverlappedNeighbours.insert( setOverlappedNeighboursNeig.begin(),
			setOverlappedNeighboursNeig.end() );
	}
	setOverlappedNeighbours.insert( setOverlappedNeighboursDist1.begin(),
		setOverlappedNeighboursDist1.end() );
	setOverlappedNeighbours.insert( setOverlappedNeighboursDist2.begin(),
		setOverlappedNeighboursDist2.end() );
	
	
	if ( ( setNotOverlappedNeighbours.empty() ) ||
			( setOverlappedNeighbours.empty() ) ){
		//no neighbour points -> not antialised
		DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::checkIfStartPointIsAntialised( vecStartPoint=("<<vecStartPoint.first<<", "<<vecStartPoint.second<<"), dMaxErrorPerPoint="<<dMaxErrorPerPoint<<", pConvertImageToFib ) done: no neighbour points (#neighbours not overlapped="<<setNotOverlappedNeighbours.size()<<"  overlapped="<<setOverlappedNeighbours.size()<<") -> not antialised"<<endl<<flush);
		return NULL;
	}
	/* remove from the not overlapped neighbours all points, which are
	 * neighbours to overlapped points
	 * (= border line betwean overlappted and not overlappted points/areas) */
	set< pair< unsigned int, unsigned int> > setNeigbousOfOverlappedNeighbours;
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrActualPoint = setOverlappedNeighbours.begin();
			itrActualPoint != setOverlappedNeighbours.end();
			itrActualPoint++ ){
		
		set< pair< unsigned int, unsigned int> > setNeighbours =
			pImageSearchData->getNotOverlappedNeighbours( *itrActualPoint );
		
		setNeigbousOfOverlappedNeighbours.insert(
			setNeighbours.begin(), setNeighbours.end() );
	}
	//remove the border line betwean overlappted and not overlappted points/areas
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrActualPoint = setNeigbousOfOverlappedNeighbours.begin();
			itrActualPoint != setNeigbousOfOverlappedNeighbours.end();
			itrActualPoint++ ){
		
		setNotOverlappedNeighbours.erase( *itrActualPoint );
	}
	if ( setNotOverlappedNeighbours.empty() ){
		//no neighbour points -> not antialised
		DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::checkIfStartPointIsAntialised( vecStartPoint=("<<vecStartPoint.first<<", "<<vecStartPoint.second<<"), dMaxErrorPerPoint="<<dMaxErrorPerPoint<<", pConvertImageToFib ) done: no neighbour points (after border line removal) (#neighbours not overlapped="<<setNotOverlappedNeighbours.size()<<") -> not antialised"<<endl<<flush);
		return NULL;
	}//else
	
	/* check if all not overlapped neighbour (without line betwean
	 * overlappted and not overlappted points/areas) have a distance greater
	 * than the maximum distance from the starting point*/
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrNeighbour = setNotOverlappedNeighbours.begin();
			itrNeighbour != setNotOverlappedNeighbours.end(); itrNeighbour++ ){
		//check the points error (on the start point color)
		const doubleFib dErrorOfNeighbour =
			pImageData->getDifference( vecStartPoint, *itrNeighbour,
				propertyTypeNumber );
		if ( dErrorOfNeighbour <= dMaxErrorPerPoint ){
			//error for point lower as maximum error -> start point not antialised
			return NULL;
		}//else error gigger than maximal error -> check next point
	}//end for all not overlapped neighbour points
	
	//change area to antialised
	DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::checkIfStartPointIsAntialised( vecStartPoint=("<<vecStartPoint.first<<", "<<vecStartPoint.second<<"), dMaxErrorPerPoint="<<dMaxErrorPerPoint<<", pConvertImageToFib ) done antialised new start point: ("<<(setNotOverlappedNeighbours.begin())->first<<", "<<(setNotOverlappedNeighbours.begin())->second<<")"<<endl<<flush);
	return new pair< unsigned int, unsigned int>( *(setNotOverlappedNeighbours.begin()) );
}


#ifdef TODO_WEG

/**
 * This method checks if the area should be antialised and returns a
 * new starting point not in the antialised border of the area.
 *
 * @param vecStartPoint the point where to start the search
 * @param pConvertImageToFib a pointer to the object for converting an
 * 	image to a Fib object (it should implement methods to get the
 * 	image search data);
 * 	The image data (getImageData()) of the search data
 * 	(pConvertImageToFib->getImageSearchData()) should have a
 * 	propertyTypeNumber'th property for each point.
 * @return the point wich should be used as the start point because the
 * 	area is antialised, or NULL if the start point is not antialised
 * 	Beware: You have to delete the returned point after usage.
 */
pair< unsigned int, unsigned int> * cFindImageAreaSameColorSimple::
	checkIfStartPointIsAntialised(
		const pair< unsigned int, unsigned int> & vecStartPoint,
		cConvertImageToFib * pConvertImageToFib ) const{
	
	if ( pConvertImageToFib == NULL ){
		//no convert object
		return NULL;
	}
	//get image search structure
	cImageSearchData * pImageSearchData =
		pConvertImageToFib->getImageSearchData();
	if ( pImageSearchData == NULL ){
		//no search data
		return NULL;
	}
	const iImageData * pImageData = pImageSearchData->getImageData();
	if ( pImageData == NULL ){
		//no image data -> not antialised
		return NULL;
	}
	DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::checkIfStartPointIsAntialised( vecStartPoint=("<<vecStartPoint.first<<", "<<vecStartPoint.second<<"), pConvertImageToFib ) started"<<endl<<flush);

	/* if antialised if possible and start point is antialised point
	 * - set area to antialised
	 * - choose new start point (and start property) from not overlapped
	 * 	neighbours with no overlapped neighbours of start point
	 */
	//get the not overlapped neighbours
	set< pair< unsigned int, unsigned int> > setNotOverlappedNeighbours =
		pImageSearchData->getNotOverlappedNeighbours( vecStartPoint );
	
	//get neighbours points which wher overlapped
	const set< pair< unsigned int, unsigned int> > setOverlappedNeighbours =
		pImageSearchData->getOverlappedNeighbours( vecStartPoint );
	
	
	if ( ( setNotOverlappedNeighbours.empty() ) ||
			( setOverlappedNeighbours.empty() ) ){
		//no neighbour points -> not antialised
		DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::checkIfStartPointIsAntialised( vecStartPoint=("<<vecStartPoint.first<<", "<<vecStartPoint.second<<"), pConvertImageToFib ) done: no neighbour points (#neighbours not overlapped="<<setNotOverlappedNeighbours.size()<<"  overlapped="<<setOverlappedNeighbours.size()<<") -> not antialised"<<endl<<flush);
		return NULL;
	}
	/* remove from the not overlapped neighbours all points, which are
	 * neighbours to overlapped points*/
	set< pair< unsigned int, unsigned int> > setNeigbousOfOverlappedNeighbours;
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrActualPoint = setOverlappedNeighbours.begin();
			itrActualPoint != setOverlappedNeighbours.end();
			itrActualPoint++ ){
		
		set< pair< unsigned int, unsigned int> > setNeighbours = pImageSearchData->
			getNotOverlappedNeighbours( *itrActualPoint );
		
		setNeigbousOfOverlappedNeighbours.insert(
			setNeighbours.begin(), setNeighbours.end() );
	}
	//remove the border line betwean overlappted and not overlappted points/areas
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrActualPoint = setNeigbousOfOverlappedNeighbours.begin();
			itrActualPoint != setNeigbousOfOverlappedNeighbours.end();
			itrActualPoint++ ){
		
		setNotOverlappedNeighbours.erase( *itrActualPoint );
	}
	if ( setNotOverlappedNeighbours.empty() ){
		//no neighbour points -> not antialised
		DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::checkIfStartPointIsAntialised( vecStartPoint=("<<vecStartPoint.first<<", "<<vecStartPoint.second<<"), pConvertImageToFib ) done: no neighbour points (after border line removal) (#neighbours not overlapped="<<setNotOverlappedNeighbours.size()<<") -> not antialised"<<endl<<flush);
		return NULL;
	}//else
	
	/* check if the elements of the start points property are betwean the
	 * correspondending elements of its not overlapped and its
	 * overlapped neighbour points*/
	
	//get properties for points
	set<cVectorProperty> setPropertiesOfNotOverlapped;
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrActualPoint = setNotOverlappedNeighbours.begin();
			itrActualPoint != setNotOverlappedNeighbours.end();
			itrActualPoint++ ){
		
		setPropertiesOfNotOverlapped.insert( pImageData->getProperty(
			*itrActualPoint, propertyTypeNumber ) );
	}
	set<cVectorProperty> setPropertiesOfOverlapped;
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrActualPoint = setOverlappedNeighbours.begin();
			itrActualPoint != setOverlappedNeighbours.end();
			itrActualPoint++ ){
	
		setPropertiesOfOverlapped.insert( pImageData->getProperty(
			*itrActualPoint, propertyTypeNumber ) );
	}
	
	if ( setPropertiesOfOverlapped.empty() ||
			setPropertiesOfNotOverlapped.empty() ){
		//no properties to check
		DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::checkIfStartPointIsAntialised( vecStartPoint=("<<vecStartPoint.first<<", "<<vecStartPoint.second<<"), pConvertImageToFib ) done: no properties to check -> not antialised"<<endl<<flush);
		return NULL;
	}
	//the color of the area
	const cVectorProperty vecAreaColor = pImageData->getProperty(
		vecStartPoint, propertyTypeNumber );
	const unsigned int uiElementsOfProperties =
		vecAreaColor.getNumberOfElements();
	
	//TODO error one value equal rest lower
	for ( unsigned int uiActualElement = 1;
			uiActualElement <= uiElementsOfProperties; uiActualElement++ ){
		
		const double dActualValue = vecAreaColor.getValue( uiActualElement );
		
		const bool bOverlappedLower = ( setPropertiesOfOverlapped.begin()->
			getValue( uiActualElement ) < dActualValue );
		
		set<cVectorProperty>::const_iterator
			itrOverlapped = setPropertiesOfOverlapped.begin();
		itrOverlapped++;
		
		//check found points
		if ( bOverlappedLower ){
			for ( ; itrOverlapped != setPropertiesOfOverlapped.end(); itrOverlapped++ ){
				
				if ( dActualValue < itrOverlapped->getValue( uiActualElement ) ){
					//not all overlapped points lower
					DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::checkIfStartPointIsAntialised( vecStartPoint=("<<vecStartPoint.first<<", "<<vecStartPoint.second<<"), pConvertImageToFib ) done: not all overlapped points lower -> not antialised"<<endl<<flush);
					return NULL;
				}
			}
			for ( set<cVectorProperty>::const_iterator
					itrNotOverlapped = setPropertiesOfNotOverlapped.begin();
					itrNotOverlapped != setPropertiesOfNotOverlapped.end();
					itrNotOverlapped++ ){
				if ( itrNotOverlapped->getValue( uiActualElement ) < dActualValue ){
					//not all not overlapped points bigger
					DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::checkIfStartPointIsAntialised( vecStartPoint=("<<vecStartPoint.first<<", "<<vecStartPoint.second<<"), pConvertImageToFib ) done: not all not overlapped points bigger -> not antialised"<<endl<<flush);
					return NULL;
				}
			}
		}else{//if ( ! bOverlappedLower )
			for ( ; itrOverlapped != setPropertiesOfOverlapped.end(); itrOverlapped++ ){
				if ( itrOverlapped->getValue( uiActualElement ) < dActualValue ){
					//not all overlapped points bigger
					DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::checkIfStartPointIsAntialised( vecStartPoint=("<<vecStartPoint.first<<", "<<vecStartPoint.second<<"), pConvertImageToFib ) done: not all not overlapped points bigger -> not antialised"<<endl<<flush);
					return NULL;
				}
			}
			for ( set<cVectorProperty>::const_iterator
					itrNotOverlapped = setPropertiesOfNotOverlapped.begin();
					itrNotOverlapped != setPropertiesOfNotOverlapped.end();
					itrNotOverlapped++ ){
				if ( dActualValue < itrNotOverlapped->getValue( uiActualElement ) ){
					//not all not overlapped points lower
					DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::checkIfStartPointIsAntialised( vecStartPoint=("<<vecStartPoint.first<<", "<<vecStartPoint.second<<"), pConvertImageToFib ) done: not all overlapped points lower -> not antialised"<<endl<<flush);
					return NULL;
				}
			}
		}
	}//end for all property elements
	
	//change area to antialised
	DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::checkIfStartPointIsAntialised( vecStartPoint=("<<vecStartPoint.first<<", "<<vecStartPoint.second<<"), pConvertImageToFib ) done antialised new start point: ("<<(setNotOverlappedNeighbours.begin())->first<<", "<<(setNotOverlappedNeighbours.begin())->second<<")"<<endl<<flush);
	return new pair< unsigned int, unsigned int>( *(setNotOverlappedNeighbours.begin()) );
}
#endif //TODO_WEG


/**
 * This function checks if the border neighbours of the given structure
 * are antialised.
 *
 * @param pStructureToCheck the structure which neighbours to check
 * @param pImageSearchData the image search data for the structure,
 * 	all points in the structure pStructureToCheck and there neighbour
 * 	points have to be marked as found in pImageSearchData
 * @param setOutStructureNeighboursNeighboursPoints a set to output
 * 	the structure neighbours neighbours of points not in the structure
 * 	or its neighbours
 * @return true if the structure border neighbours are antialised else false
 */
bool cFindImageAreaSameColorSimple::checkIfBorderIsAntialised(
		const cImageAreaSameColor * pStructureToCheck,
		const cImageSearchData * pImageSearchData,
		set< pair< unsigned int, unsigned int> > &
			setOutStructureNeighboursNeighboursPoints ) const{
	
	/* if 9 times more points are antialised than not antialised (overlapped
	 * neighbours and neighbours with no not found neighbours don't count)
	 * - a points is antialised if its color elements values are betwean
	 * the neighbour in the area (border) and a point outside the area and
	 * the area neighbours (which is not overlapped)*/
	if ( ( pStructureToCheck == NULL ) || ( pImageSearchData == NULL ) ){
		//can't evalue antialising -> return not antialised
		return false;
	}
	const iImageData * pImageData = pImageSearchData->getImageData();
	if ( pImageData == NULL ){
		//can't evalue antialising -> return not antialised
		return false;
	}
	DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::checkIfBorderIsAntialised( pStructureToCheck, pImageSearchData, setOutStructureNeighboursNeighboursPoints )"<<endl<<flush);
	
	const cVectorProperty vecAreaColor =
		pStructureToCheck->getColorOfArea();
	const unsigned int uiElementsOfProperties =
		vecAreaColor.getNumberOfElements();
	
	//speed up area property vector element retrieval
	vector< double > vecAreaColorValuesTmp;
	//counting for Fib vectors starts at 1 -> add value 0 to ignore later
	vecAreaColorValuesTmp.push_back( 0 );
	for ( unsigned int uiActualElement = 1;
			uiActualElement <= uiElementsOfProperties; uiActualElement++ ){
		
		vecAreaColorValuesTmp.push_back(
			vecAreaColor.getValue( uiActualElement ) );
	}
	//optimization: const is easier to optimize by compiler
	const vector< double > vecAreaColorValues( vecAreaColorValuesTmp );
	
	//for all neighbour points
	const set< pair< unsigned int, unsigned int> > setStructureNeighboursPoints =
		pStructureToCheck->getStructureNeighbourPointsPair();
	//if (1/10) of the neighbour points are not antialised -> area not antialised
	const unsigned long ulNotAANeighboursNeededForNotAA =
		setStructureNeighboursPoints.size() / 10;
	unsigned long ulAntialisedNeighbours = 0;
	unsigned long ulNotAntialisedNeighbours = 0;
	
	DEBUG_OUT_L2(<<"   neighbour points "<<setStructureNeighboursPoints.size()<<"  ulNotAANeighboursNeededForNotAA="<<ulNotAANeighboursNeededForNotAA<<endl<<flush);
	
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrNeighbour = setStructureNeighboursPoints.begin();
			itrNeighbour != setStructureNeighboursPoints.end();
			itrNeighbour++ ){
		/* find not found or overlapped border neighbours neighbours
		 * which are not border neighbours (or found)*/
		const set< pair< unsigned int, unsigned int> > setPointsNeighboursNei =
			pImageSearchData->getNotFoundNotOverlappedNeighbours(
				*itrNeighbour );
		
		if ( setPointsNeighboursNei.empty() ){
			//nothing to check (skip all overlapped points)
			continue;
		}
		/*check if the neighbour point property is betwean area color
			and neighbour neighbours property*/
		bool bPointIsAntialised = true;
		//evalue the properties for the points
		const cVectorProperty vecNeighbourProperty = pImageData->getProperty(
			*itrNeighbour, propertyTypeNumber );
		const cVectorProperty vecNeighbourNeighbProperty = pImageData->getProperty(
			(*(setPointsNeighboursNei.begin())), propertyTypeNumber );
		
		for ( unsigned int uiActualElement = 1;
				uiActualElement <= uiElementsOfProperties; uiActualElement++ ){
			
			const doubleFib dActualValue = vecNeighbourProperty.getValue( uiActualElement );
			
			if ( ( vecAreaColorValues[ uiActualElement ] < dActualValue ) ==
					( vecNeighbourNeighbProperty.getValue( uiActualElement ) < dActualValue ) ){
				if ( ( vecAreaColorValues[ uiActualElement ] != dActualValue ) &&
						( vecNeighbourNeighbProperty.getValue( uiActualElement ) != dActualValue ) ){
					/*points both lower or bigger (equal to area property not
					possible (than neighbour would be in area)) than neighbour
					-> point not antialised*/
					bPointIsAntialised = false;
					break;
				}
			}//else
		}//end for all property elements
		if ( bPointIsAntialised ){
			//point is antialised
			ulAntialisedNeighbours++;
		}else{//point is not antialised
			ulNotAntialisedNeighbours++;
			if ( ( ulNotAANeighboursNeededForNotAA + 2 ) < ulNotAntialisedNeighbours ){
				/*to much points not antialised -> stop evaluation
				 -> area is not antialised*/
				DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::checkIfBorderIsAntialised() done to much points not antialised (ulNotAANeighboursNeededForNotAA="<<ulNotAANeighboursNeededForNotAA<<" + 2 ?<? ulNotAntialisedNeighbours="<<ulNotAntialisedNeighbours<<"  ulAntialisedNeighbours="<<ulAntialisedNeighbours<<"): return false"<<endl<<flush);
				return false;
			}
		}
		setOutStructureNeighboursNeighboursPoints.insert(
			setPointsNeighboursNei.begin(), setPointsNeighboursNei.end() );
	}//end for all neighbour points
	// 9 times more points antialised than not antialised
	const unsigned long ulAANeighboursNeedeForAA =
		ulNotAntialisedNeighbours * 9;
	DEBUG_OUT_L2(<<"ulAANeighboursNeedeForAA="<<ulAANeighboursNeedeForAA<<" ?<=? ulAntialisedNeighbours="<<ulAntialisedNeighbours<<"  ulNotAntialisedNeighbours="<<ulNotAntialisedNeighbours<<" ?<=? ulNotAANeighboursNeededForNotAA="<<ulNotAANeighboursNeededForNotAA<<" + 2"<<endl<<flush);
	if ( ( ulAANeighboursNeedeForAA <= ulAntialisedNeighbours ) &&
			( ulNotAntialisedNeighbours <= ( ulNotAANeighboursNeededForNotAA + 2 ) ) ){
		//area is antialised
		DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::checkIfBorderIsAntialised() done return true"<<endl<<flush);
		return true;
	}//else
	DEBUG_OUT_L2(<<"cFindImageAreaSameColorSimple("<<this<<")::checkIfBorderIsAntialised() done return false"<<endl<<flush);
	return false;
}


























