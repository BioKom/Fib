
//TODO check

/**
 * @file cFindImageAreaLinearColorSimple
 * file name: cFindImageAreaLinearColorSimple.cpp
 * @author Betti Oesterholz
 * @date 28.03.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements specifies a class for searching for a structure with
 * linear color gradient in an image.
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
 * linear color gradient color in an image.
 * For this a method findImageStructure() is defined.
 * If you want to convert an image to Fib structures, you have to search
 * the image for structures, which can be converted to Fib.
 * For this you can use this class.
 * @see findImageStructure()
 *
 * @pattern Strategy
 * @see cImageAreaLinearColor
 * @see cConvertImageToFib
 * @see iFindImageStructure
 * @see iConvertImageStructureToFib
 */
/*
History:
29.03.2013  Oesterholz  created
*/

//debugging switch
//#define DEBUG

#include "version.h"

#include "cFindImageAreaLinearColorSimple.h"

#include "cVectorProperty.h"

#include <list>
#include <set>
#include <algorithm>


using namespace std;
using namespace fib::algorithms::nConvertToFib::nImage::nSearchForStructure;
using namespace fib::algorithms::nConvertToFib::nImage::nStructureData;

#define FEATURE_FIND_POINTS_FOR_IMAGE_STRUCTURE_WITH_ORIGINAL_START_POINT
#define FEATURE_EVALUE_BASE_FOR_INDEX__ERROR_DISTANCE 2

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
 * @param dMaxErrorPerPropertyElement the maximal error for a property
 * 	element value for a point of the area;
 * 	This value is just for evaluing the base and slope parameters for the
 * 	image structure (for linear properties) to create.
 * 	@see maxErrorPerPropertyElement
 */
cFindImageAreaLinearColorSimple::cFindImageAreaLinearColorSimple(
		unsigned int uiPropertyType, const double dMaxErrorPerPoint,
		const bool bInCanBeAntialised,
		const double dMaxErrorPerPropertyElement ):
		propertyTypeNumber( uiPropertyType ),
		maxErrorPerPoint( dMaxErrorPerPoint ),
		bCanBeAntialised( bInCanBeAntialised ),
		maxErrorPerPropertyElement( dMaxErrorPerPropertyElement ){
	
	DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::cFindImageAreaLinearColorSimple( uiPropertyType="<<uiPropertyType<<", dMaxErrorPerPoint="<<dMaxErrorPerPoint<<"="<<maxErrorPerPoint<<", bInCanBeAntialised="<<(bInCanBeAntialised ? "true" : "false")<<", dMaxErrorPerPropertyElement="<<dMaxErrorPerPropertyElement<<" ) started"<<endl<<flush);
	zeroErrorValue = 0.0000000001;
}



/**
 * This method is for searching in an image for an area with the linear color.
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
cImageAreaLinearColor * cFindImageAreaLinearColorSimple::findImageStructure(
		const pair< long, long> paStartPoint,
		cConvertImageToFib * pConvertImageToFib ) const{
	
	/* Steps:
	 * 	- take as start point a neighbour of the start point paStartPoint
	 * 		which has (if possible) no overlapped neighbours (so the start
	 * 		point can be antialised, without make the evaluation of the
	 * 		parameters (slope base) difficult)
	 * 	- find good parameters for the area (base + slope)
	 * 	- find slope parameters:
	 * 		- evalue derivate (in both directions)
	 * 		- (min distance for property elements needed)
	 * 		- from start point: evalue not overlapped neighbours with
	 * 			 +-(min distance) to mean slope for property element
	 * 		- use mean slope for property element and direction as their slope
	 * 	- find base property parameters:
	 * 		- for every point in intersection of all slope areas:
	 * 			point property - (x * slopeX) - (y * slopeY)
	 * 	- find area of points with element error lower equal maxErrorPerPropertyElement
	 * - evalue if antialised
	 * - add start point paStartPoint to area border (if needed)
	 */
	
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
		//no image data
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
	}
	
	
	/* Take as start point a not found point as near as possible to the
	 * original start point paStartPoint, which is not on a border.
	 * Points not on a border have a low derivate value, which is also
	 * similar to a lot of there neighbours. */
	pair< unsigned int, unsigned int> vecStartPoint =
		findGoodAreaStartPoint( paStartPoint, maxErrorPerPropertyElement,
			pConvertImageToFib );
	
	//find slope parameters
	const vector< unsigned int > vecPropertyIndexDim3 =
		pImageData->getDimension3IndexesForPropertyType(
			propertyTypeNumber, vecStartPoint.first, vecStartPoint.second );
		
	//for the base vector value
	cVectorProperty vecBase( pImageData->getProperty( vecStartPoint, propertyTypeNumber ) );
	//for the first (x) direction
	cVectorProperty vecSlopeX( vecBase );
	//for the second (y) direction
	cVectorProperty vecSlopeY( vecBase );
	unsigned int uiActualElement = 1;
	for ( vector< unsigned int >::const_iterator
			itrActualIndex = vecPropertyIndexDim3.begin();
			itrActualIndex != vecPropertyIndexDim3.end();
			itrActualIndex++, uiActualElement++ ){
		
		const doubleFib dSlopeX = evalueSlopeXForIndex(
			*itrActualIndex, vecStartPoint, maxErrorPerPropertyElement,
			pConvertImageToFib );
		vecSlopeX.setValue( uiActualElement, dSlopeX );
		const doubleFib dSlopeY = evalueSlopeYForIndex(
			*itrActualIndex, vecStartPoint, maxErrorPerPropertyElement,
			pConvertImageToFib );
		vecSlopeY.setValue( uiActualElement, dSlopeY );
		
		//find base property parameter
		vecBase.setValue( uiActualElement, evalueBaseForIndex(
			*itrActualIndex, vecStartPoint, dSlopeX, dSlopeY,
			maxErrorPerPropertyElement, pConvertImageToFib ) );
	}
	
	//create image structure to use, with the color of the area/start point
	cImageAreaLinearColor * pFoundImageStructure = new cImageAreaLinearColor(
		vecBase, vecSlopeX, vecSlopeY );
	
	//add start point vecStartPoint to area border (if needed)
#ifdef FEATURE_FIND_POINTS_FOR_IMAGE_STRUCTURE_WITH_ORIGINAL_START_POINT
	pFoundImageStructure->addStructurePoint( paStartPoint );
#endif //FEATURE_FIND_POINTS_FOR_IMAGE_STRUCTURE_WITH_ORIGINAL_START_POINT
	pFoundImageStructure->addStructurePoint( vecStartPoint );
	
	//find area of points with element error lower equal maxErrorPerPropertyElement
	findPointsForImageStructure(
		pFoundImageStructure, maxErrorPerPoint, pConvertImageToFib );
	
	//evalue if antialised
	bool bIsAntialised = false;
	
	if ( bCanBeAntialised ){
		/* if antialising is possible
		*-> check if border neighbours are antialised border
		*-> if yes add them as new border and make area antitalised*/
		if ( checkIfBorderIsAntialised( pFoundImageStructure, pImageSearchData ) ){
			//structure is antialised
			bIsAntialised = true;
		}
	}
	if ( ! bIsAntialised ){
		//unregister the neighbour points as found
		const set< pair< unsigned int, unsigned int> >
			setStructureNeighboursPoints =
				pFoundImageStructure->getStructureNeighbourPointsPair();
		pImageSearchData->registerFound( setStructureNeighboursPoints, false );
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
#ifndef FEATURE_FIND_POINTS_FOR_IMAGE_STRUCTURE_WITH_ORIGINAL_START_POINT
	//add start point paStartPoint to the created image structure (if needed)
	pImageSearchData->registerFound( paStartPoint );
	if ( pImageSearchData->hasNotFoundNotOverlappedNeighbours( paStartPoint ) ){
		/* start point is border point
		-> add start point paStartPoint to the created image structure border (if needed)*/
		pFoundImageStructure->addStructureBorderPoint( paStartPoint );
		if ( ! bIsAntialised ){
			/* not antialised
			-> add start point paStartPoint to the created image structure (if needed)*/
			pFoundImageStructure->addStructurePoint( paStartPoint );
		}
		
	}else{//start point is not a border point
		//add start point paStartPoint to the created image structure (if needed)
		pFoundImageStructure->addStructurePoint( paStartPoint );
	}
	/* remove all neighbour points of paStartPoint from the border
	 * points of the structure which have no not found not overlapped neighbours*/
	const set< pair< unsigned int, unsigned int> > setStartPointNeighbours =
		pImageSearchData->getFoundNeighbours( paStartPoint );
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrNeighbour = setStartPointNeighbours.begin();
			itrNeighbour != setStartPointNeighbours.end(); itrNeighbour++ ){
		
		if ( ! pImageSearchData->hasNotFoundNotOverlappedNeighbours( *itrNeighbour ) ){
			/*the point has no not found and not not overlapped neighbours
			 -> it is not a border points of the structure*/
			pFoundImageStructure->deleteStructureBorderPoint( *itrNeighbour  );
			if ( bIsAntialised ){
				//add point to structure points
				pFoundImageStructure->addStructurePoint( *itrNeighbour );
			}
		}
	}//end for all neighbour points of paStartPoint which are in the structure (==found)
	//adding neighbour points of the start point
	pFoundImageStructure->deleteStructureNeighbourPoint( paStartPoint  );
	const set< pair< unsigned int, unsigned int> > setStartPointNeighboursNotF =
		pImageSearchData->getNotFoundNotOverlappedNeighbours( paStartPoint );
	pFoundImageStructure->addStructureNeighbourPoints( setStartPointNeighboursNotF );
#endif //FEATURE_FIND_POINTS_FOR_IMAGE_STRUCTURE_WITH_ORIGINAL_START_POINT
	return pFoundImageStructure;
}


/**
 * @return the name of this class
 */
string cFindImageAreaLinearColorSimple::getName() const{
	
	return "cFindImageAreaLinearColorSimple";
}



/**
 * This method takes as start point a neighbour of the start point paStartPoint
 * which has (if possible) no overlapped neighbours (so the start
 * point can be antialised, without make the evaluation of the
 * parameters (slope base) difficult).
 *
 * @param paStartPoint the original start point
 * @param dMaxErrorPerValue the maximal error for a value of the matrix
 * @param pConvertImageToFib a pointer to the object for converting an
 * 	image to a Fib object (it should implement methods to get the
 * 	image search data);
 * 	The image data (getImageData()) of the search data
 * 	(pConvertImageToFib->getImageSearchData()) should have a
 * 	propertyTypeNumber'th property for each point.
 * @return a new start point which is neighbour of the start point
 * 	paStartPoint and  which has (if possible) no overlapped neighbours
 */
pair< unsigned int, unsigned int> cFindImageAreaLinearColorSimple::findGoodAreaStartPoint(
		const pair< unsigned int, unsigned int> & paStartPoint,
		const double dMaxErrorPerValue,
		cConvertImageToFib * pConvertImageToFib ) const{
	
	DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::findGoodAreaStartPoint( paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), dMaxErrorPerValue="<<dMaxErrorPerValue<<", pConvertImageToFib ) started"<<endl<<flush);
	if ( pConvertImageToFib == NULL ){
		//no convert object
		DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::findGoodAreaStartPoint( paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), dMaxErrorPerValue="<<dMaxErrorPerValue<<", pConvertImageToFib ) done: no convert object"<<endl<<flush);
		return paStartPoint;
	}
	//get image search structure
	cImageSearchData * pImageSearchData =
		pConvertImageToFib->getImageSearchData();
	if ( pImageSearchData == NULL ){
		//no search data
		DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::findGoodAreaStartPoint( paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), dMaxErrorPerValue="<<dMaxErrorPerValue<<", pConvertImageToFib ) done: no search data"<<endl<<flush);
		return paStartPoint;
	}
	const iImageData * pImageData = pImageSearchData->getImageData();
	if ( pImageData == NULL ){
		//no image data
		DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::findGoodAreaStartPoint( paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), dMaxErrorPerValue="<<dMaxErrorPerValue<<", pConvertImageToFib ) done: /no image data"<<endl<<flush);
		return paStartPoint;
	}
	/* Take as start point a not found point as near as possible to the
	 * original start point paStartPoint, which is not on a border.
	 * Points not on a border have a low derivate value, which is also
	 * similar to a lot of there neighbours. */
	
	//evalue derivations
	const vector< unsigned int > vecPropertyIndexDim3 =
		pImageData->getDimension3IndexesForPropertyType(
			propertyTypeNumber, paStartPoint.first, paStartPoint.second );
	//get all possible derivate matrixes
	const iMatrix3D * pDerivateMatrix0 = pConvertImageToFib->getDerivation( 0 );
	const iMatrix3D * pDerivateMatrix1 = pConvertImageToFib->getDerivation( 1 );
	list< const iMatrix3D * > liDerivateMatrix;
	if ( pDerivateMatrix0 ){
		liDerivateMatrix.push_back( pDerivateMatrix0 );
	}
	if ( pDerivateMatrix1 ){
		liDerivateMatrix.push_back( pDerivateMatrix1 );
	}
	const double dMaxErrorPerPoint = dMaxErrorPerValue *
		((double)liDerivateMatrix.size()) * ((double)vecPropertyIndexDim3.size());
	/* evalue all not found or overlapped neighbours till miximal distance
	 * of  4 from start point*/
	set< pair< unsigned int, unsigned int> > setActualDistance;
	setActualDistance.insert( paStartPoint );
	pImageSearchData->clearFound();
	pImageSearchData->registerFound( paStartPoint );
	
	pair< unsigned int, unsigned int> paActualBestPoint = paStartPoint;
	double dSumAbsSlopesDifferenceBestPoint = 0.0;
	{
		set< pair< unsigned int, unsigned int> > setNeighbourPoints =
			pImageSearchData->getNeighbours( paActualBestPoint );
		
		for ( list< const iMatrix3D * >::const_iterator
				itrActualDerivate = liDerivateMatrix.begin();
				itrActualDerivate != liDerivateMatrix.end(); itrActualDerivate++ ){
			for ( vector< unsigned int >::const_iterator
					itrActualIndex = vecPropertyIndexDim3.begin();
					itrActualIndex != vecPropertyIndexDim3.end(); itrActualIndex++ ){
				
				const double dActualSlope = (*itrActualDerivate)->getValue(
					paActualBestPoint.first, paActualBestPoint.second, *itrActualIndex );
				
				for ( set< pair< unsigned int, unsigned int> >::const_iterator
						itrNeighbour = setNeighbourPoints.begin();
						itrNeighbour != setNeighbourPoints.end(); itrNeighbour++ ){
				
					//get the slope value for the point, add it to slope sum (for average)
					const double dSlopeNeighbour = (*itrActualDerivate)->getValue(
						itrNeighbour->first, itrNeighbour->second, *itrActualIndex );
					
					dSumAbsSlopesDifferenceBestPoint += abs( dSlopeNeighbour - dActualSlope );
				}//end for all point neighbours
			}//end for all property indexes
		}//end for all derivations
		dSumAbsSlopesDifferenceBestPoint /= ((double)setNeighbourPoints.size());
		
		DEBUG_OUT_L2(<<"   paActualBestPoint=("<<paActualBestPoint.first<<", "<<paActualBestPoint.second<<") with dSumAbsSlopesDifferenceBestPoint="<<dSumAbsSlopesDifferenceBestPoint<<endl<<flush);
	}
	
	for ( unsigned int uiActualDistance = 1; ( uiActualDistance < 5 ) &&
			( ! setActualDistance.empty() ) ; uiActualDistance++ ){
		
		//evalue points of next distance
		set< pair< unsigned int, unsigned int> > setNextDistance;
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrActualPoint = setActualDistance.begin();
				itrActualPoint != setActualDistance.end(); itrActualPoint++ ){
			//evalue the neighbour points of the choosen point
			const set< pair< unsigned int, unsigned int> > setPointsToCheck =
				pImageSearchData->getNotFoundNotOverlappedNeighbours(
					*itrActualPoint );
			if ( setPointsToCheck.empty() ){
				//no neighbours to check -> check next border point
				continue;
			}
			pImageSearchData->registerFound( setPointsToCheck );
			setNextDistance.insert(
				setPointsToCheck.begin(), setPointsToCheck.end() );
		}
		setActualDistance = setNextDistance;
		
		DEBUG_OUT_L2(<<"  searching for distance "<<uiActualDistance<<", with "<<setActualDistance.size()<<" points in distance"<<endl<<flush);
		/*best point is the point with the minimal sum of slope difference to
		*its neighbour points*/
		bool bBetterPointForDistanceFound = false;
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrPoint = setActualDistance.begin();
				itrPoint != setActualDistance.end(); itrPoint++ ){
			
			//evalue sum of slope difference of point to its neighbour points
			const set< pair< unsigned int, unsigned int> > setNeighbourPoints =
				pImageSearchData->getNeighbours( *itrPoint );
			
			const unsigned int uiNumberOfNeighbourPoints = setNeighbourPoints.size();
			if ( uiNumberOfNeighbourPoints <= 2 ){
				//not enougth neighbours -> skip point
				DEBUG_OUT_L2(<<"      point ("<<itrPoint->first<<", "<<itrPoint->second<<") has not enougth neighbours ("<<setNeighbourPoints.size()<<")"<<endl<<flush);
				continue;
			}
			double dSumAbsSlopesDifference = 0;
			
			if ( uiNumberOfNeighbourPoints == 2 ){
				
				for ( list< const iMatrix3D * >::const_iterator
						itrActualDerivate = liDerivateMatrix.begin();
						itrActualDerivate != liDerivateMatrix.end(); itrActualDerivate++ ){
					for ( vector< unsigned int >::const_iterator
							itrActualIndex = vecPropertyIndexDim3.begin();
							itrActualIndex != vecPropertyIndexDim3.end(); itrActualIndex++ ){
						
						const double dActualSlope = (*itrActualDerivate)->getValue(
							itrPoint->first, itrPoint->second, *itrActualIndex );
						
						unsigned int uiNeighbour = 0;
						for ( set< pair< unsigned int, unsigned int> >::const_iterator
								itrNeighbour = setNeighbourPoints.begin();
								itrNeighbour != setNeighbourPoints.end();
								itrNeighbour++, uiNeighbour++ ){
						
							//get the slope value for the point, add it to slope sum (for average)
							const double dSlopeNeighbour = (*itrActualDerivate)->getValue(
								itrNeighbour->first, itrNeighbour->second, *itrActualIndex );
							
							dSumAbsSlopesDifference +=
								abs( dSlopeNeighbour - dActualSlope );
						}//end for all point neighbours
						
					}//end for all property indexes
				}//end for all derivations
				dSumAbsSlopesDifference /= 2.0;
				DEBUG_OUT_L2(<<"      point ("<<itrPoint->first<<", "<<itrPoint->second<<") with two neighbours has absolute distance value="<<dSumAbsSlopesDifference<<endl<<flush);
			}else{// tree or more neighbour points
				//vector with the slope differences for the neighbour points
				vector< double > vecSumAbsSlopesDifferenceForNeighbours(
					uiNumberOfNeighbourPoints, 0.0 );
				
				for ( list< const iMatrix3D * >::const_iterator
						itrActualDerivate = liDerivateMatrix.begin();
						itrActualDerivate != liDerivateMatrix.end(); itrActualDerivate++ ){
					for ( vector< unsigned int >::const_iterator
							itrActualIndex = vecPropertyIndexDim3.begin();
							itrActualIndex != vecPropertyIndexDim3.end(); itrActualIndex++ ){
						
						const double dActualSlope = (*itrActualDerivate)->getValue(
							itrPoint->first, itrPoint->second, *itrActualIndex );
						
						unsigned int uiNeighbour = 0;
						for ( set< pair< unsigned int, unsigned int> >::const_iterator
								itrNeighbour = setNeighbourPoints.begin();
								itrNeighbour != setNeighbourPoints.end();
								itrNeighbour++, uiNeighbour++ ){
						
							//get the slope value for the point, add it to slope sum (for average)
							const double dSlopeNeighbour = (*itrActualDerivate)->getValue(
								itrNeighbour->first, itrNeighbour->second, *itrActualIndex );
							
							vecSumAbsSlopesDifferenceForNeighbours[ uiNeighbour ] +=
								abs( dSlopeNeighbour - dActualSlope );
						}//end for all point neighbours
						
					}//end for all property indexes
				}//end for all derivations
				//sort vector
				sort( vecSumAbsSlopesDifferenceForNeighbours.begin(),
					vecSumAbsSlopesDifferenceForNeighbours.end() );
				
				dSumAbsSlopesDifference = vecSumAbsSlopesDifferenceForNeighbours[ 0 ];
				dSumAbsSlopesDifference += vecSumAbsSlopesDifferenceForNeighbours[ 1 ];
				
				dSumAbsSlopesDifference /=  2.0;
				DEBUG_OUT_L2(<<"      point ("<<itrPoint->first<<", "<<itrPoint->second<<") has absolute distance value="<<dSumAbsSlopesDifference<<endl<<flush);
			}
			
			if ( ( ( uiActualDistance < 3 ) &&
						( dSumAbsSlopesDifference < dSumAbsSlopesDifferenceBestPoint ) ) ||
					( ( dSumAbsSlopesDifference + dMaxErrorPerPoint ) <
						dSumAbsSlopesDifferenceBestPoint ) ){
				//the actual point has a better sum absolute slope difference
				paActualBestPoint = (*itrPoint);
				dSumAbsSlopesDifferenceBestPoint = dSumAbsSlopesDifference;
				bBetterPointForDistanceFound = true;
				DEBUG_OUT_L2(<<"   better start point found paActualBestPoint=("<<paActualBestPoint.first<<", "<<paActualBestPoint.second<<") with dSumAbsSlopesDifferenceBestPoint="<<dSumAbsSlopesDifferenceBestPoint<<endl<<flush);
				if ( dSumAbsSlopesDifferenceBestPoint <= zeroErrorValue ){
					//error can't get smaaler -> break
					break;
				}
			}
		}//end for all points of actual distance
		
		
		if ( ( 2 < uiActualDistance ) && ( ! bBetterPointForDistanceFound ) ){
			//no better point for distance found -> break search
			break;
		}//else
		if ( dSumAbsSlopesDifferenceBestPoint <= zeroErrorValue ){
			//error can't get smaaler -> break
			break;
		}/* else if better point (with error lower maxErrorPerPropertyElement
		 * to last lower distance point) was found
		 * -> take next bigger distance*/
	}
	
	DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::findGoodAreaStartPoint( paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), dMaxErrorPerValue="<<dMaxErrorPerValue<<", pConvertImageToFib ) done new start point ("<<paActualBestPoint.first<<", "<<paActualBestPoint.second<<")"<<endl<<flush);
	return paActualBestPoint;
}

#ifdef TODO_WEG

/**
 * This method takes as start point a neighbour of the start point paStartPoint
 * which has (if possible) no overlapped neighbours (so the start
 * point can be antialised, without make the evaluation of the
 * parameters (slope base) difficult).
 *
 * @param paStartPoint the original start point
 * @param pImageSearchData the image search data wher the overlapped
 * 	points are marked
 * @return a new start point which is neighbour of the start point
 * 	paStartPoint and  which has (if possible) no overlapped neighbours
 */
pair< unsigned int, unsigned int> cFindImageAreaLinearColorSimple::findGoodAreaStartPoint(
		const pair< unsigned int, unsigned int> & paStartPoint,
		const cImageSearchData * pImageSearchData ) const{
	/* take as start point a neighbour of the start point paStartPoint
	 * which has (if possible) no overlapped neighbours (so the start
	 * point can be antialised, without make the evaluation of the
	 * parameters (slope base) difficult)*/
	
	DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::findGoodAreaStartPoint( paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), pImageSearchData ) started"<<endl<<flush);
	pair< unsigned int, unsigned int> paNewStartPoint( paStartPoint );
	
	if ( pImageSearchData == NULL ){
		DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::findGoodAreaStartPoint( paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), pImageSearchData=NULL ) done new start is old start point"<<endl<<flush);
		return paNewStartPoint;
	}
	set< pair< unsigned int, unsigned int> > setNotOverlappedNeighbours =
		pImageSearchData->getNotOverlappedNeighbours( paStartPoint );
	
	//get neighbours points which wher overlapped
	set< pair< unsigned int, unsigned int> > setOverlappedNeighbours =
		pImageSearchData->getOverlappedNeighbours( paStartPoint );
	
	
	if ( ( setNotOverlappedNeighbours.empty() ) ||
			( setOverlappedNeighbours.empty() ) ){
		/*evalue neighbours of distance 1 and try to evalue the overlapped
		 * and not for them*/
		const set< pair< unsigned int, unsigned int> > setNeighboursDist1 =
			pImageSearchData->getNeighbours( paStartPoint );
		if ( setNotOverlappedNeighbours.empty() ){
			//evalue not overlapped neighbours of distance 1
			for ( set< pair< unsigned int, unsigned int> >::const_iterator
					itrNeighbour = setNeighboursDist1.begin();
					itrNeighbour != setNeighboursDist1.end(); itrNeighbour++ ){
				
				const set< pair< unsigned int, unsigned int> > setNotOverlappedNeighboursDist1 =
					pImageSearchData->getNotOverlappedNeighbours( *itrNeighbour );
				
				setNotOverlappedNeighbours.insert(
					setNotOverlappedNeighboursDist1.begin(),
					setNotOverlappedNeighboursDist1.end() );
			}
		}//end if no not overlapped neighbours
		if ( setOverlappedNeighbours.empty() ){
			//evalue overlapped neighbours of distance 1
			for ( set< pair< unsigned int, unsigned int> >::const_iterator
					itrNeighbour = setNeighboursDist1.begin();
					itrNeighbour != setNeighboursDist1.end(); itrNeighbour++ ){
				
				const set< pair< unsigned int, unsigned int> > setOverlappedNeighboursDist1 =
					pImageSearchData->getOverlappedNeighbours( *itrNeighbour );
				
				setOverlappedNeighbours.insert(
					setOverlappedNeighboursDist1.begin(),
					setOverlappedNeighboursDist1.end() );
			}
		}//end if no overlapped neighbours
		
		if ( ( setNotOverlappedNeighbours.empty() ) ||
				( setOverlappedNeighbours.empty() ) ){
			//no neighbour points till distance 1 -> can't choose new start point
			DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::findGoodAreaStartPoint( paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), pImageSearchData ) done no neighbour points: new start is old start point"<<endl<<flush);
			return paNewStartPoint;
		}
	}
	//get neighbours (till distance 3) points which wher overlapped
	set< pair< unsigned int, unsigned int> > setOverlappedNeighboursDist2;
	for ( set< pair< unsigned int, unsigned int> >::iterator
			itrNeighbour = setOverlappedNeighbours.begin();
			itrNeighbour != setOverlappedNeighbours.end(); itrNeighbour++ ){
		
		const set< pair< unsigned int, unsigned int> > setOverlappedNeighboursNeig =
			pImageSearchData->getOverlappedNeighbours( *itrNeighbour );
		setOverlappedNeighboursDist2.insert( setOverlappedNeighboursNeig.begin(),
			setOverlappedNeighboursNeig.end() );
	}
	for ( set< pair< unsigned int, unsigned int> >::iterator
			itrNeighbour = setOverlappedNeighboursDist2.begin();
			itrNeighbour != setOverlappedNeighboursDist2.end(); itrNeighbour++ ){
		
		const set< pair< unsigned int, unsigned int> > setOverlappedNeighboursNeig =
			pImageSearchData->getOverlappedNeighbours( *itrNeighbour );
		setOverlappedNeighbours.insert( setOverlappedNeighboursNeig.begin(),
			setOverlappedNeighboursNeig.end() );
	}
	setOverlappedNeighbours.insert( setOverlappedNeighboursDist2.begin(),
		setOverlappedNeighboursDist2.end() );
	
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
	
	set< pair< unsigned int, unsigned int> > setNotOverlappedNeighboursMinusBorder =
		setNotOverlappedNeighbours;
	//remove the border line betwean overlappted and not overlappted points/areas
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrActualPoint = setNeigbousOfOverlappedNeighbours.begin();
			itrActualPoint != setNeigbousOfOverlappedNeighbours.end();
			itrActualPoint++ ){
		
		setNotOverlappedNeighboursMinusBorder.erase( *itrActualPoint );
	}
	if ( setNotOverlappedNeighboursMinusBorder.empty() ){
		//find not overlapped neighbours of not overlapped neighbours and try again
		
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrNeighbour = setNotOverlappedNeighbours.begin();
				itrNeighbour != setNotOverlappedNeighbours.end(); itrNeighbour++ ){
			
			set< pair< unsigned int, unsigned int> > setNeighbours =
				pImageSearchData->getNotOverlappedNeighbours( *itrNeighbour );
			
			setNotOverlappedNeighboursMinusBorder.insert(
				setNeighbours.begin(), setNeighbours.end() );
		}
		//remove the border line betwean overlappted and not overlappted points/areas
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrActualPoint = setNeigbousOfOverlappedNeighbours.begin();
				itrActualPoint != setNeigbousOfOverlappedNeighbours.end();
				itrActualPoint++ ){
			
			setNotOverlappedNeighboursMinusBorder.erase( *itrActualPoint );
		}
		
		if ( setNotOverlappedNeighboursMinusBorder.empty() ){
			//no neighbour points -> not antialised
			DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::findGoodAreaStartPoint( paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), pImageSearchData ) done no neighbour points without border: new start is old start point"<<endl<<flush);
			return paNewStartPoint;
		}//else
	}//else
	//choose first point of generated set as new start point
	paNewStartPoint = *(setNotOverlappedNeighboursMinusBorder.begin());
	
	DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::findGoodAreaStartPoint( paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), pImageSearchData ) done new start point: ("<<paNewStartPoint.first<<", "<<paNewStartPoint.second<<")"<<endl<<flush);
	return paNewStartPoint;
}
#endif //TODO_WEG


/**
 * This method evalues a good slope value in the first (x) dimension /
 * direction, for the area which includs the start point paStartPoint,
 * is not overlapped and has in dimension 3 the given index uiIndexDim3.
 *
 * @param uiIndexDim3 the index in dimension 3 for the values for which the
 * 	slope should be evalued
 * @param paStartPoint the start point for the area
 * @param dMaxErrorPerValue the maximal error for a value of the matrix
 * @param pConvertImageToFib a pointer to the object for converting an
 * 	image to a Fib object (it should implement methods to get the
 * 	image search data);
 * 	The image data (getImageData()) of the search data
 * 	(pConvertImageToFib->getImageSearchData()) should have a
 * 	propertyTypeNumber'th property for each point.
 * @return a good slope parameter
 */
doubleFib cFindImageAreaLinearColorSimple::evalueSlopeXForIndex( const unsigned int uiIndexDim3,
		const pair< unsigned int, unsigned int> & paStartPoint,
		const double dMaxErrorPerValue,
		cConvertImageToFib * pConvertImageToFib ) const{
	/* - evalue derivate in x direction
	 * 	- from start point: evalue not overlapped neighbours with
	 * 	- use mean slope for property element and direction as their slope
	 */
	DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::evalueSlopeXForIndex( uiIndexDim3="<<uiIndexDim3<<", paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), pConvertImageToFib ) started"<<endl<<flush);
	if ( pConvertImageToFib == NULL ){
		//no convert object
		return 0.0;
	}
	//get image search structure
	cImageSearchData * pImageSearchData =
		pConvertImageToFib->getImageSearchData();
	if ( pImageSearchData == NULL ){
		//no search data
		return 0.0;
	}
	
	const iMatrix3D * pDerivateMatrix = pConvertImageToFib->getDerivation( 0 );
	
	//2 possible slope start points paStartPoint and (paStartPoint.first - 1, paStartPoint.second )
	pair< unsigned int, unsigned int> paStartPointNeig1 = paStartPoint;
	paStartPointNeig1.first--;
	pair< unsigned int, unsigned int> paStartPointNeig2 = paStartPoint;
	paStartPointNeig2.first++;
	
	if ( ( ! pImageSearchData->isOverlapped( paStartPointNeig2 ) ) ||
			( pImageSearchData->isOverlapped( paStartPointNeig1 ) )){
		//use the start point paStartPoint as the start point for the slope search
		
		return searchForGoodSlope( uiIndexDim3, paStartPoint,
			dMaxErrorPerValue, pDerivateMatrix, pImageSearchData );
	}//elst use paStartPointNeig1 as the start point for the slope search
	
	return searchForGoodSlope( uiIndexDim3, paStartPointNeig1,
		dMaxErrorPerValue, pDerivateMatrix, pImageSearchData );
}



/**
 * This method evalues a good slope value in the second (y) dimension /
 * direction, for the area which includs the start point paStartPoint,
 * is not overlapped and has in dimension 3 the given index uiIndexDim3.
 *
 * @param uiIndexDim3 the index in dimension 3 for the values for which the
 * 	slope should be evalued
 * @param paStartPoint the start point for the area
 * @param dMaxErrorPerValue the maximal error for a value of the matrix
 * @param pConvertImageToFib a pointer to the object for converting an
 * 	image to a Fib object (it should implement methods to get the
 * 	image search data);
 * 	The image data (getImageData()) of the search data
 * 	(pConvertImageToFib->getImageSearchData()) should have a
 * 	propertyTypeNumber'th property for each point.
 * @return a good slope parameter
 */
doubleFib cFindImageAreaLinearColorSimple::evalueSlopeYForIndex( const unsigned int uiIndexDim3,
		const pair< unsigned int, unsigned int> & paStartPoint,
		const double dMaxErrorPerValue,
		cConvertImageToFib * pConvertImageToFib ) const{
	/* - evalue derivate in y direction
	 * 	- from start point: evalue not overlapped neighbours with
	 * 	- use mean slope for property element and direction as their slope
	 */
	DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::evalueSlopeYForIndex( uiIndexDim3="<<uiIndexDim3<<", paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), pConvertImageToFib ) started"<<endl<<flush);
	if ( pConvertImageToFib == NULL ){
		//no convert object
		return 0.0;
	}
	//get image search structure
	cImageSearchData * pImageSearchData =
		pConvertImageToFib->getImageSearchData();
	if ( pImageSearchData == NULL ){
		//no search data
		return 0.0;
	}
	
	const iMatrix3D * pDerivateMatrix = pConvertImageToFib->getDerivation( 1 );
	
	//2 possible slope start points paStartPoint and (paStartPoint.first, paStartPoint.second - 1 )
	pair< unsigned int, unsigned int> paStartPointNeig1 = paStartPoint;
	paStartPointNeig1.second--;
	pair< unsigned int, unsigned int> paStartPointNeig2 = paStartPoint;
	paStartPointNeig2.second++;
	
	if ( ( ! pImageSearchData->isOverlapped( paStartPointNeig2 ) ) ||
			( pImageSearchData->isOverlapped( paStartPointNeig1 ) )){
		//use the start point paStartPoint as the start point for the slope search
		
		return searchForGoodSlope( uiIndexDim3, paStartPoint,
			dMaxErrorPerValue, pDerivateMatrix, pImageSearchData );
	}//elst use paStartPointNeig1 as the start point for the slope search
	
	return searchForGoodSlope( uiIndexDim3, paStartPointNeig1,
		dMaxErrorPerValue, pDerivateMatrix, pImageSearchData );
}


/**
 * This method evalues a good slope value in the given first derivation
 * matrix, for the area which includs the start point paStartPoint,
 * is not overlapped and has in dimension 3 the given index uiIndexDim3.
 *
 * @param uiIndexDim3 the index in dimension 3 for the values for which the
 * 	slope should be evalued
 * @param paStartPoint the start point for the area
 * @param dMaxErrorPerValue the maximal error for a value of the matrix
 * @param pDerivateMatrix the derivation matrix in which the slope
 * 	parameter should be evalued
 * @param pImageSearchData the image search data with the overlapped points
 * 	marked; all points in the slope area will be marked as found
 * @return a good slope parameter
 */
doubleFib cFindImageAreaLinearColorSimple::searchForGoodSlope(
		const unsigned int uiIndexDim3,
		const pair< unsigned int, unsigned int> & paStartPoint,
		const double dMaxErrorPerValue,
		const iMatrix3D * pDerivateMatrix,
		cImageSearchData * pImageSearchData ) const{
	
	DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::searchForGoodSlope( uiIndexDim3="<<uiIndexDim3<<", paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), dMaxErrorPerValue="<<dMaxErrorPerValue<<", pDerivateMatrix="<<pDerivateMatrix<<", pImageSearchData ) started"<<endl<<flush);
	if ( ( pDerivateMatrix == NULL ) || ( pImageSearchData == NULL ) ){
		//Error: can't evalue slope parameter
		return 0.0;
	}
	
	/* - from start point: evalue not overlapped neighbours with
	 * 	+-(min_distance or max_dist) to mean slope for property element
	 * 	(what if maxErrorPerPropertyElement != 0 ?
	 * 		max_dist = min_distance +
	 * 			maxErrorPerPropertyElement / distance( point, paStartPoint ) )
	 * - use mean slope for property element and direction as their slope
	 */
	const doubleFib dMinDistance = pDerivateMatrix->getMinDifference(
		paStartPoint.first, paStartPoint.second, uiIndexDim3 );
	const doubleFib dMinDistanceDouble = dMinDistance * 2.0;
	//mean slope
	doubleFib dMeanSlope = pDerivateMatrix->getValue( paStartPoint.first,
		paStartPoint.second, uiIndexDim3 );
	doubleFib dSlopeSum = dMeanSlope;
	doubleFib dNumberOfAreaPoints = 1.0;
	
	doubleFib dSlopeSumBigValues = 0;
	doubleFib dNumberOfAreaPointsBigValues = 0.0;
	
	map< doubleFib, list< pair< unsigned int, unsigned int> > >
		mapBorderPoints;
	mapBorderPoints[ 0.0 ].push_back( paStartPoint );
	pImageSearchData->clearFound();
	pImageSearchData->registerFound( paStartPoint );
	
	map< doubleFib, list< pair< unsigned int, unsigned int> > >::iterator
		itrActualPoints;
	while ( ! mapBorderPoints.empty() ){
		//choose point
		itrActualPoints = mapBorderPoints.begin();
		
		list< pair< unsigned int, unsigned int> > &
			liActualPoints = itrActualPoints->second;
		
		const pair< unsigned int, unsigned int> paActualPoint =
			liActualPoints.front();
		liActualPoints.pop_front();
		
		if ( liActualPoints.empty() ){
			//no more points for this average distance value -> delete entry
			mapBorderPoints.erase( itrActualPoints );
		}
		//evalue the neighbour points of the choosen point
		const set< pair< unsigned int, unsigned int> > setPointsToCheck =
			pImageSearchData->getNotFoundNotOverlappedNeighbours(
				paActualPoint );
		DEBUG_OUT_L4(<<"The point ("<<paActualPoint.first<<", "<<paActualPoint.second<<") has "<<setPointsToCheck.size()<<" not found and not overlapped neighbours"<<endl<<flush);
		if ( setPointsToCheck.empty() ){
			//no neighbours to check -> check next border point
			continue;
		}
		pImageSearchData->registerFound( setPointsToCheck );
		
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrNeighbour = setPointsToCheck.begin();
				itrNeighbour != setPointsToCheck.end(); itrNeighbour++ ){
			//get the slope value for the point, add it to slope sum (for average)
			const double dActualSlope = pDerivateMatrix->getValue(
				itrNeighbour->first, itrNeighbour->second, uiIndexDim3 );
			
			const double dDiffToMean = abs( dActualSlope - dMeanSlope );
			DEBUG_OUT_L4(<<"Checking point ("<<itrNeighbour->first<<", "<<itrNeighbour->second<<") with slope "<<dActualSlope<<" and difference to mean="<<dDiffToMean<<" (mean is "<< dMeanSlope<<")"<<flush);
			if ( dMinDistance < dDiffToMean ){
				/* make finer grained check
				 * max_dist = min_distance +
				 *    maxErrorPerPropertyElement / distance( point, paStartPoint ) )
				 */
				const double dActualMaxDistance = dMinDistance +
					( dMaxErrorPerValue * 3.0 ) / (
						abs( paStartPoint.first - itrNeighbour->first ) +
						abs( paStartPoint.second - itrNeighbour->second ) );
				if ( dActualMaxDistance < dDiffToMean ){
					//slope to big -> skip point
					DEBUG_OUT_L4(<<"-> difference to mean great"<<endl<<flush);
					continue;
				}
			}
			if ( dMinDistanceDouble < dDiffToMean ){
				DEBUG_OUT_L4(<<"-> OK (but big) -> adding "<<dNumberOfAreaPoints<<"'th point to border"<<endl<<flush);
				dSlopeSumBigValues += dActualSlope;
				dNumberOfAreaPointsBigValues += 1.0;
				
				mapBorderPoints[ dDiffToMean ].push_back( *itrNeighbour );
			}else{// ( dDiffToMean <= dMinDistance ) difference to mean is OK -> add point to area
				DEBUG_OUT_L4(<<"-> OK -> adding "<<dNumberOfAreaPoints<<"'th point to border"<<endl<<flush);
			
				dSlopeSum += dActualSlope;
				dNumberOfAreaPoints += 1.0;
				dMeanSlope = dSlopeSum / dNumberOfAreaPoints;
				/*all slope values with less than dMinDistance to mean slope
				 should have the same propability to be choosen as the next point*/
				mapBorderPoints[ 0.0 ].push_back( *itrNeighbour );
			}
			
			if ( ((doubleFib)uiPointsToUseToEvalueParameters) < dNumberOfAreaPoints ){
				DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::searchForGoodSlope( uiIndexDim3="<<uiIndexDim3<<", paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), dMaxErrorPerValue="<<dMaxErrorPerValue<<", pDerivateMatrix="<<pDerivateMatrix<<", pImageSearchData ) done (used points "<<dNumberOfAreaPoints<<") evalued mean: "<<dMeanSlope<<endl<<flush);
				//return mean dMeanSlope
				return dMeanSlope;
			}
		}
	}
	
	DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::searchForGoodSlope( uiIndexDim3="<<uiIndexDim3<<", paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), dMaxErrorPerValue="<<dMaxErrorPerValue<<", pDerivateMatrix="<<pDerivateMatrix<<", pImageSearchData ) done evalued mean: "<<dMeanSlope<<endl<<flush);
	//return mean dMeanSlope
	if ( ( dNumberOfAreaPoints < 32.0 ) &&
			( dNumberOfAreaPoints < ( dNumberOfAreaPointsBigValues / 2.0 ) ) ){
		//points with bigger error needed
		return ( dSlopeSum + dSlopeSumBigValues) /
			( dNumberOfAreaPoints + dNumberOfAreaPointsBigValues );
	}//else use just slope values with smaal errors values
	return dMeanSlope;
}


/**
 * This method evalues a good base value for the area which includs the
 * start point paStartPoint, is not overlapped and has in dimension 3 the
 * given index uiIndexDim3.
 *
 * @param uiIndexDim3 the index in dimension 3 for the values for which the
 * 	base should be evalued
 * @param paStartPoint the start point for the area
 * @param dSlopeX the slope in the first (x) direction
 * @param dSlopeY the slope in the second (y) direction
 * @param dMaxErrorPerValue the maximal error for a value of the matrix
 * @param pConvertImageToFib a pointer to the object for converting an
 * 	image to a Fib object (it should implement methods to get the
 * 	image search data);
 * 	The image data (getImageData()) of the search data
 * 	(pConvertImageToFib->getImageSearchData()) should have a
 * 	propertyTypeNumber'th property for each point.
 * @return a good slope parameter
 */
doubleFib cFindImageAreaLinearColorSimple::evalueBaseForIndex(
		const unsigned int uiIndexDim3,
		const pair< unsigned int, unsigned int> & paStartPoint,
		const doubleFib dSlopeX, const doubleFib dSlopeY,
		const double dMaxErrorPerValue,
		cConvertImageToFib * pConvertImageToFib ) const{
	
	DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::evalueBaseForIndex( uiIndexDim3="<<uiIndexDim3<<", paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), dSlopeX="<<dSlopeX<<", dSlopeY="<<dSlopeY<<", dMaxErrorPerValue="<<dMaxErrorPerValue<<", pConvertImageToFib ) started"<<endl<<flush);
	if ( pConvertImageToFib == NULL ){
		//no convert object
		return 0.0;
	}
	//get image search structure
	cImageSearchData * pImageSearchData =
		pConvertImageToFib->getImageSearchData();
	if ( pImageSearchData == NULL ){
		//no search data
		return 0.0;
	}
	const iImageData * pImageData = pImageSearchData->getImageData();
	if ( pImageData == NULL ){
		//no image data
		return 0.0;
	}
	pImageSearchData->clearFound();
	
	list< pair< unsigned int, unsigned int> > liBorderPoints;
	liBorderPoints.push_back( paStartPoint );
	pImageSearchData->registerFound( paStartPoint );
	/* the base from a point can be evalued with:
	 * 	base = point property - (x * slopeX) - (y * slopeY)
	 * every point in the area didn't should exclue the start point
	 * -> the difference betwaen the base of the start point and the actual
	 * point should be lower equal the maximal error dMaxErrorPerValue */
	const doubleFib dMinDistance = pImageData->getMinDifference(
		paStartPoint.first, paStartPoint.second, uiIndexDim3 );
	
	const doubleFib dBaseStartPoint = pImageData->getValue(
		paStartPoint.first, paStartPoint.second, uiIndexDim3 ) -
			(dSlopeX * ((doubleFib)(paStartPoint.first)) ) -
			(dSlopeY * ((doubleFib)(paStartPoint.second)) );
	
#if FEATURE_EVALUE_BASE_FOR_INDEX__ERROR_DISTANCE == 2
	doubleFib dSumBase  = dBaseStartPoint;
	unsigned int uiNumberOfAreaPoints = 1;
	
	const double dMaxErrorPerValuePossible =
			dMinDistance + dMaxErrorPerValue * 2.0;
	
	while ( ! liBorderPoints.empty() ){
		//choose point
		const pair< unsigned int, unsigned int>
			paActualPoint = liBorderPoints.front();
		liBorderPoints.pop_front();
		
		//evalue the neighbour points of the choosen point
		const set< pair< unsigned int, unsigned int> > setPointsToCheck =
			pImageSearchData->getNotFoundNotOverlappedNeighbours(
				paActualPoint );
		DEBUG_OUT_L4(<<"The point ("<<paActualPoint.first<<", "<<paActualPoint.second<<") has "<<setPointsToCheck.size()<<" not found and not overlapped neighbours"<<endl<<flush);
		if ( setPointsToCheck.empty() ){
			//no neighbours to check -> check next border point
			continue;
		}
		pImageSearchData->registerFound( setPointsToCheck );
		
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrNeighbour = setPointsToCheck.begin();
				itrNeighbour != setPointsToCheck.end(); itrNeighbour++ ){
			//get the slope value for the point, add it to slope sum (for average)
			const doubleFib dBaseActualPoint = pImageData->getValue(
				itrNeighbour->first, itrNeighbour->second, uiIndexDim3 ) -
					(dSlopeX * ((doubleFib)(itrNeighbour->first)) ) -
					(dSlopeY * ((doubleFib)(itrNeighbour->second)) );
			
			DEBUG_OUT_L4(<<"Checking point ("<<itrNeighbour->first<<", "<<itrNeighbour->second<<") with base="<<dBaseActualPoint<<" (mean base is "<<(dSumBase / ((doubleFib)uiNumberOfAreaPoints))<<")"<<flush);
			if ( dMaxErrorPerValuePossible < abs( dBaseStartPoint - dBaseActualPoint ) ){
				//difference to start point base to big -> skip point
				DEBUG_OUT_L4(<<"-> difference to start point base to big"<<endl<<flush);
				continue;
			}//else difference to mean is OK -> add point to area
			DEBUG_OUT_L4(<<"-> OK -> adding "<<uiNumberOfAreaPoints<<"'th point to border"<<endl<<flush);
			
			dSumBase += dBaseActualPoint;
			uiNumberOfAreaPoints++;
			liBorderPoints.push_back( *itrNeighbour );
			
			if ( uiPointsToUseToEvalueParameters < uiNumberOfAreaPoints ){
				//stop evaluation
				liBorderPoints.clear();
				break;
			}
		}
	}
	const double dMeanBase = ( dSumBase / ((doubleFib)uiNumberOfAreaPoints) );
	const double dMaxDistanceToStartPoint = dMinDistance / 2.0 + dMaxErrorPerValue;
	if ( ( dBaseStartPoint + dMaxDistanceToStartPoint ) < dMeanBase ){
		//the base mean should also include the start point
		DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::evalueBaseForIndex( uiIndexDim3="<<uiIndexDim3<<", paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), dSlopeX="<<dSlopeX<<", dSlopeY="<<dSlopeY<<", dMaxErrorPerValue="<<dMaxErrorPerValue<<", pConvertImageToFib ) done (used points "<<uiNumberOfAreaPoints<<") evalued mean base "<<dMeanBase<<" to great returning as mean base: "<<(dBaseStartPoint + dMaxDistanceToStartPoint - zeroErrorValue)<<endl<<flush);
		
		return dBaseStartPoint + dMaxDistanceToStartPoint - zeroErrorValue;
	}//else
	if ( dMeanBase < ( dBaseStartPoint - dMaxDistanceToStartPoint ) ){
		//the base mean should also include the start point
		DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::evalueBaseForIndex( uiIndexDim3="<<uiIndexDim3<<", paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), dSlopeX="<<dSlopeX<<", dSlopeY="<<dSlopeY<<", dMaxErrorPerValue="<<dMaxErrorPerValue<<", pConvertImageToFib ) done (used points "<<uiNumberOfAreaPoints<<") evalued mean base "<<dMeanBase<<" to low returning as mean base: "<<(dBaseStartPoint - dMaxDistanceToStartPoint + zeroErrorValue)<<endl<<flush);
		
		return dBaseStartPoint - dMaxDistanceToStartPoint + zeroErrorValue;
	}//else
	
	DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::evalueBaseForIndex( uiIndexDim3="<<uiIndexDim3<<", paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), dSlopeX="<<dSlopeX<<", dSlopeY="<<dSlopeY<<", dMaxErrorPerValue="<<dMaxErrorPerValue<<", pConvertImageToFib ) done (used points "<<uiNumberOfAreaPoints<<") evalued mean base: "<<dMeanBase<<endl<<flush);
	//return mean mean base
	return dMeanBase;
	
#elif FEATURE_EVALUE_BASE_FOR_INDEX__ERROR_DISTANCE == 1
	doubleFib dSumBase  = dBaseStartPoint;
	unsigned int uiNumberOfAreaPoints = 1;
	
	const double dMaxErrorPerValuePossible =
		( dMaxErrorPerValue < ( dMinDistance / 2.0 ) ) ?
			( dMinDistance / 2.0 ) : dMaxErrorPerValue;
	
	while ( ! liBorderPoints.empty() ){
		//choose point
		const pair< unsigned int, unsigned int>
			paActualPoint = liBorderPoints.front();
		liBorderPoints.pop_front();
		
		//evalue the neighbour points of the choosen point
		const set< pair< unsigned int, unsigned int> > setPointsToCheck =
			pImageSearchData->getNotFoundNotOverlappedNeighbours(
				paActualPoint );
		DEBUG_OUT_L4(<<"The point ("<<paActualPoint.first<<", "<<paActualPoint.second<<") has "<<setPointsToCheck.size()<<" not found and not overlapped neighbours"<<endl<<flush);
		if ( setPointsToCheck.empty() ){
			//no neighbours to check -> check next border point
			continue;
		}
		pImageSearchData->registerFound( setPointsToCheck );
		
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrNeighbour = setPointsToCheck.begin();
				itrNeighbour != setPointsToCheck.end(); itrNeighbour++ ){
			//get the slope value for the point, add it to slope sum (for average)
			const doubleFib dBaseActualPoint = pImageData->getValue(
				itrNeighbour->first, itrNeighbour->second, uiIndexDim3 ) -
					(dSlopeX * ((doubleFib)(itrNeighbour->first)) ) -
					(dSlopeY * ((doubleFib)(itrNeighbour->second)) );
			
			DEBUG_OUT_L4(<<"Checking point ("<<itrNeighbour->first<<", "<<itrNeighbour->second<<") with base="<<dBaseActualPoint<<" (mean base is "<<(dSumBase / ((doubleFib)uiNumberOfAreaPoints))<<")"<<flush);
			if ( dMaxErrorPerValuePossible < abs( dBaseStartPoint - dBaseActualPoint ) ){
				//difference to start point base to big -> skip point
				DEBUG_OUT_L4(<<"-> difference to start point base to big"<<endl<<flush);
				continue;
			}//else difference to mean is OK -> add point to area
			DEBUG_OUT_L4(<<"-> OK -> adding "<<uiNumberOfAreaPoints<<"'th point to border"<<endl<<flush);
			
			dSumBase += dBaseActualPoint;
			uiNumberOfAreaPoints++;
			liBorderPoints.push_back( *itrNeighbour );
			
			if ( uiPointsToUseToEvalueParameters < uiNumberOfAreaPoints ){
				DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::evalueBaseForIndex( uiIndexDim3="<<uiIndexDim3<<", paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), dSlopeX="<<dSlopeX<<", dSlopeY="<<dSlopeY<<", dMaxErrorPerValue="<<dMaxErrorPerValue<<", pConvertImageToFib ) done  (used points "<<uiNumberOfAreaPoints<<") evalued mean base: "<<(dSumBase / ((doubleFib)uiNumberOfAreaPoints))<<endl<<flush);
				//return mean dMeanBase
				return ( dSumBase / ((doubleFib)uiNumberOfAreaPoints) );
			}
		}
	}
	
	DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::evalueBaseForIndex( uiIndexDim3="<<uiIndexDim3<<", paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), dSlopeX="<<dSlopeX<<", dSlopeY="<<dSlopeY<<", dMaxErrorPerValue="<<dMaxErrorPerValue<<", pConvertImageToFib ) done evalued mean base: "<<(dSumBase / ((doubleFib)uiNumberOfAreaPoints))<<endl<<flush);
	//return mean mean base
	return ( dSumBase / ((doubleFib)uiNumberOfAreaPoints) );
	
#else //FEATURE_EVALUE_BASE_FOR_INDEX__ERROR_DISTANCE
	//base mean
	doubleFib dMeanBase = dBaseStartPoint;
	doubleFib dSumBase  = dBaseStartPoint;
	doubleFib dNumberOfAreaPoints = 1.0;
	
	const double dMaxErrorPerValuePossible =
		( dMaxErrorPerValue < ( dMinDistance / 2.0 ) ) ?
			( dMinDistance / 2.0 ) : dMaxErrorPerValue;
	
	while ( ! liBorderPoints.empty() ){
		//choose point
		const pair< unsigned int, unsigned int>
			paActualPoint = liBorderPoints.front();
		liBorderPoints.pop_front();
		
		//evalue the neighbour points of the choosen point
		const set< pair< unsigned int, unsigned int> > setPointsToCheck =
			pImageSearchData->getNotFoundNotOverlappedNeighbours(
				paActualPoint );
		DEBUG_OUT_L4(<<"The point ("<<paActualPoint.first<<", "<<paActualPoint.second<<") has "<<setPointsToCheck.size()<<" not found and not overlapped neighbours"<<endl<<flush);
		if ( setPointsToCheck.empty() ){
			//no neighbours to check -> check next border point
			continue;
		}
		pImageSearchData->registerFound( setPointsToCheck );
		
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrNeighbour = setPointsToCheck.begin();
				itrNeighbour != setPointsToCheck.end(); itrNeighbour++ ){
			//get the slope value for the point, add it to slope sum (for average)
			const doubleFib dBaseActualPoint = pImageData->getValue(
				itrNeighbour->first, itrNeighbour->second, uiIndexDim3 ) -
					(dSlopeX * ((doubleFib)(itrNeighbour->first)) ) -
					(dSlopeY * ((doubleFib)(itrNeighbour->second)) );
	
			DEBUG_OUT_L4(<<"Checking point ("<<itrNeighbour->first<<", "<<itrNeighbour->second<<") with base="<<dBaseActualPoint<<" (mean base is "<<dMeanBase<<")"<<flush);
			if ( dMaxErrorPerValuePossible < abs( dMeanBase - dBaseActualPoint ) ){
				//difference to mean base to big -> skip point
				DEBUG_OUT_L4(<<"-> difference to mean base to big"<<endl<<flush);
				continue;
			}
			if ( dMaxErrorPerValuePossible < abs( dBaseStartPoint - dBaseActualPoint ) ){
				//difference to start point base to big -> skip point
				DEBUG_OUT_L4(<<"-> difference to start point base to big"<<endl<<flush);
				continue;
			}//else difference to mean is OK -> add point to area
			DEBUG_OUT_L4(<<"-> OK -> adding "<<dNumberOfAreaPoints<<"'th point to border"<<endl<<flush);
			
			dSumBase += dBaseActualPoint;
			dNumberOfAreaPoints += 1.0;
			dMeanBase = dSumBase / dNumberOfAreaPoints;
			liBorderPoints.push_back( *itrNeighbour );
			
			uiNumberPointsUsed++;
			if ( uiPointsToUseToEvalueParameters < uiNumberPointsUsed ){
				DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::evalueBaseForIndex( uiIndexDim3="<<uiIndexDim3<<", paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), dSlopeX="<<dSlopeX<<", dSlopeY="<<dSlopeY<<", dMaxErrorPerValue="<<dMaxErrorPerValue<<", pConvertImageToFib ) done  (used points "<<uiNumberPointsUsed<<") evalued mean base: "<<dMeanBase<<endl<<flush);
				//return mean dMeanBase
				return dMeanBase;
			}
		}
	}
	
	DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::evalueBaseForIndex( uiIndexDim3="<<uiIndexDim3<<", paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), dSlopeX="<<dSlopeX<<", dSlopeY="<<dSlopeY<<", dMaxErrorPerValue="<<dMaxErrorPerValue<<", pConvertImageToFib ) done evalued mean base: "<<dMeanBase<<endl<<flush);
	//return mean dMeanBase
	return dMeanBase;
#endif //FEATURE_EVALUE_BASE_FOR_INDEX__ERROR_DISTANCE
}


/**
 * This method searches for all points which can be included into the given
 * image structure pInOutImageStructure and includes them into it.
 *
 * @param pInOutImageStructure the image structure for which the points
 * 	should be found and in which the points will be included;
 * 	It should already contain at last one point, at which to start the
 * 	search (if it contains more than one point they should be in one
 * 	connected (via neighbours) area).
 * 	The structure and structure neighbour points will be added, you have
 * 	to add the structure border points to it.
 * @param dMaxErrorPerPoint the maximal error for a property of a point
 * @param pConvertImageToFib a pointer to the object for converting an
 * 	image to a Fib object (it should implement methods to get the
 * 	image search data);
 * 	The image data (getImageData()) of the search data
 * 	(pConvertImageToFib->getImageSearchData()) should have a
 * 	propertyTypeNumber'th property for each point.
 * @return the pointer to the image structure object, wher the points wher
 * 	added ( pInOutImageStructure ), or NULL if no points could be added
 */
cImageAreaLinearColor * cFindImageAreaLinearColorSimple::findPointsForImageStructure(
		cImageAreaLinearColor * pInOutImageStructure,
		doubleFib dMaxErrorPerPoint,
		cConvertImageToFib * pConvertImageToFib ) const{
	
	DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::findPointsForImageStructure( pInOutImageStructure, dMaxErrorPerPoint="<<dMaxErrorPerPoint<<", pConvertImageToFib ) started"<<endl<<flush);
	
	if ( ( pConvertImageToFib == NULL ) || ( pInOutImageStructure == NULL ) ){
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
		//no image data
		return NULL;
	}
	const set< pair< unsigned int, unsigned int> > setStructurePoints =
		pInOutImageStructure->getStructurePointsPair();
	if ( setStructurePoints.empty() ){
		//no start point
		return NULL;
	}
	pImageSearchData->clearFound();
	
	//the border points of the actual search area to check
	list< pair< unsigned int, unsigned int> > liBorderPoints;
	
	
#ifdef FEATURE_FIND_POINTS_FOR_IMAGE_STRUCTURE_WITH_ORIGINAL_START_POINT
	liBorderPoints.insert( liBorderPoints.begin(),
		setStructurePoints.begin(), setStructurePoints.end() );
	pImageSearchData->registerFound( setStructurePoints );
#else //FEATURE_FIND_POINTS_FOR_IMAGE_STRUCTURE_WITH_ORIGINAL_START_POINT
	liBorderPoints.push_back( *(setStructurePoints.begin()) );
	pImageSearchData->registerFound( paStartPoint );
#endif //FEATURE_FIND_POINTS_FOR_IMAGE_STRUCTURE_WITH_ORIGINAL_START_POINT
	
	//evalue if a element minimum distance half error should be used
	bool bUseElementError = false;
	const vector< unsigned int > vecPropertyIndexDim3 =
		pImageData->getDimension3IndexesForPropertyType(
			propertyTypeNumber, 0, 0 );
	for ( vector< unsigned int >::const_iterator
			itrActualIndex = vecPropertyIndexDim3.begin();
			itrActualIndex != vecPropertyIndexDim3.end(); itrActualIndex++ ){
	
		const doubleFib dMinDistanceHalf = pImageData->getMinDifference(
			0, 0, (*itrActualIndex) ) / 2.0;
		if ( dMaxErrorPerPoint / vecPropertyIndexDim3.size() < dMinDistanceHalf ){
			//use corrected error value 
			bUseElementError = true;
		}
	}
	if ( ! bUseElementError ){
		//use given error value
		while ( ! liBorderPoints.empty() ){
			//choose good border point to enlarge area for
			const pair< unsigned int, unsigned int> & vecActualPoint =
				liBorderPoints.front();
			pInOutImageStructure->addStructurePoint( vecActualPoint );
			
			//get neighbour points of choosen border point
			const set< pair< unsigned int, unsigned int> > setPointsToCheck =
				pImageSearchData->getNotFoundNotOverlappedNeighbours(
					vecActualPoint );
			DEBUG_OUT_L2(<<"   checking neighbours of point ("<<vecActualPoint.first<<", "<<vecActualPoint.second<<") it has "<<setPointsToCheck.size()<<" neighbours to check"<<endl<<flush);
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
				//get actual property
				const cVectorProperty vecNeighbourProperty =
					pImageData->getProperty( *itrNeighbour, propertyTypeNumber );
				//get actual structure property
				const cVectorProperty vecNeighbourPropertyStructure =
					pInOutImageStructure->getProperty(
						*itrNeighbour, propertyTypeNumber, true );
				//check the points error (on the area color)
				const doubleFib dErrorOfNeighbour =
					vecNeighbourPropertyStructure.distanceToProperty( vecNeighbourProperty );
					
				DEBUG_OUT_L2(<<"   checking point ("<<itrNeighbour->first<<", "<<itrNeighbour->second<<") with error "<<dErrorOfNeighbour<<", which is "<<((dMaxErrorPerPoint < dErrorOfNeighbour)?"not OK":"OK")<<endl<<flush);
				if ( dMaxErrorPerPoint < dErrorOfNeighbour ){
					//error for point to great -> skip it
					//neighbour point is area neighbour point
					pInOutImageStructure->addStructureNeighbourPoint( *itrNeighbour );
					continue;
				}//else error smaal enougth -> register as border point
				
				//add the point to border points
				liBorderPoints.push_back( *itrNeighbour );
			}//end for all neighbour points
			//remove choosen border point from search/check border
			liBorderPoints.pop_front();
		}//end while border points to check
	}else{//use error of property element components
		vector< doubleFib > vecPropertyElementErrorHalf;
		for ( vector< unsigned int >::const_iterator
				itrActualIndex = vecPropertyIndexDim3.begin();
				itrActualIndex != vecPropertyIndexDim3.end(); itrActualIndex++ ){
			
			vecPropertyElementErrorHalf.push_back( pImageData->getMinDifference(
				0, 0, (*itrActualIndex) ) / 2.0 );
		}
		bool bHalfErrorOk = true;
		
		while ( ! liBorderPoints.empty() ){
			//choose good border point to enlarge area for
			const pair< unsigned int, unsigned int> & vecActualPoint =
				liBorderPoints.front();
			pInOutImageStructure->addStructurePoint( vecActualPoint );
			
			//get neighbour points of choosen border point
			const set< pair< unsigned int, unsigned int> > setPointsToCheck =
				pImageSearchData->getNotFoundNotOverlappedNeighbours(
					vecActualPoint );
			DEBUG_OUT_L2(<<"   checking neighbours of point ("<<vecActualPoint.first<<", "<<vecActualPoint.second<<") it has "<<setPointsToCheck.size()<<" neighbours to check"<<endl<<flush);
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
				//get actual property
				const cVectorProperty vecNeighbourProperty =
					pImageData->getProperty( *itrNeighbour, propertyTypeNumber );
				//get actual structure property
				const cVectorProperty vecNeighbourPropertyStructure =
					pInOutImageStructure->getProperty(
						*itrNeighbour, propertyTypeNumber, true );
				//check the points error (on the area color)
				const doubleFib dErrorOfNeighbour =
					vecNeighbourPropertyStructure.distanceToProperty( vecNeighbourProperty );
					
				DEBUG_OUT_L2(<<"   checking point ("<<itrNeighbour->first<<", "<<itrNeighbour->second<<") with error "<<dErrorOfNeighbour<<", which is "<<((dMaxErrorPerPoint < dErrorOfNeighbour)?"not OK":"OK")<<endl<<flush);
				if ( dMaxErrorPerPoint < dErrorOfNeighbour ){
					//check property element error
					bHalfErrorOk = true;
					unsigned int uiActualPropertyIndex = 1;
					for ( vector< doubleFib >::const_iterator
							itrActualError = vecPropertyElementErrorHalf.begin();
							itrActualError != vecPropertyElementErrorHalf.end();
							uiActualPropertyIndex++, itrActualError++ ){
						
						const doubleFib dErrorValue = abs(
							vecNeighbourPropertyStructure.getValue( uiActualPropertyIndex ) -
							vecNeighbourProperty.getValue( uiActualPropertyIndex ) );
						
						if ( (*itrActualError) < dErrorValue ){
							bHalfErrorOk = false;
							break;
						}
					}//end for all property elements
					DEBUG_OUT_L2(<<"      its element error is "<<(bHalfErrorOk?"OK":"not OK")<<endl<<flush);
					
					if ( ! bHalfErrorOk ){
						//error for point to great -> skip it
						//neighbour point is area neighbour point
						pInOutImageStructure->addStructureNeighbourPoint( *itrNeighbour );
						continue;
					}
				}//else error smaal enougth -> register as border point
				
				//add the point to border points
				liBorderPoints.push_back( *itrNeighbour );
			}//end for all neighbour points
			//remove choosen border point from search/check border
			liBorderPoints.pop_front();
		}//end while border points to check
	}
	DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::findPointsForImageStructure( pInOutImageStructure, dMaxErrorPerPoint="<<dMaxErrorPerPoint<<", pConvertImageToFib ) done"<<endl<<flush);
	return pInOutImageStructure;
}


/**
 * This function checks if the border neighbours of the given structure
 * are antialised.
 *
 * @param pInOutImageStructure the structure which neighbours to check
 * 	 and in which the points will be included, if antialised
 * @param pImageSearchData the image search data for the structure,
 * 	all points in the structure pInOutImageStructure and there neighbour
 * 	points have to be marked as found in pImageSearchData
 * @return true if the structure border neighbours are antialised else false
 */
bool cFindImageAreaLinearColorSimple::checkIfBorderIsAntialised(
		cImageAreaLinearColor * pInOutImageStructure,
		const cImageSearchData * pImageSearchData ) const{
	
	/* if 9 times more points are antialised than not antialised (overlapped
	 * neighbours and neighbours with no not found neighbours don't count)
	 * - a points is antialised if its color elements values are betwean
	 * the neighbour in the area (border) and a point outside the area and
	 * the area neighbours (which is not overlapped)*/
	if ( ( pInOutImageStructure == NULL ) || ( pImageSearchData == NULL ) ){
		//can't evalue antialising -> return not antialised
		return false;
	}
	const iImageData * pImageData = pImageSearchData->getImageData();
	if ( pImageData == NULL ){
		//can't evalue antialising -> return not antialised
		return false;
	}
	DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::checkIfBorderIsAntialised( pInOutImageStructure, pImageSearchData )"<<endl<<flush);
	
	const cVectorProperty vecAreaColor =
		pInOutImageStructure->getColorBasisOfArea();
	const unsigned int uiElementsOfProperties = vecAreaColor.getNumberOfElements();
	
	set< pair< unsigned int, unsigned int> > setStructureNeighboursNeighboursPoints;
	//for all neighbour points
	const set< pair< unsigned int, unsigned int> > setStructureNeighboursPoints =
		pInOutImageStructure->getStructureNeighbourPointsPair();
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
		const cVectorProperty vecNeighbourPropertyStructure =
			pInOutImageStructure->getProperty(
				*itrNeighbour, propertyTypeNumber, true );
		const cVectorProperty vecNeighbourProperty = pImageData->getProperty(
			*itrNeighbour, propertyTypeNumber );
		const cVectorProperty vecNeighbourNeighbProperty = pImageData->getProperty(
			(*(setPointsNeighboursNei.begin())), propertyTypeNumber );
		
		for ( unsigned int uiActualElement = 1;
				uiActualElement <= uiElementsOfProperties; uiActualElement++ ){
			
			const doubleFib dActualValue = vecNeighbourProperty.getValue( uiActualElement );
			
			if ( ( vecNeighbourPropertyStructure.getValue( uiActualElement ) < dActualValue ) ==
					( vecNeighbourNeighbProperty.getValue( uiActualElement ) < dActualValue ) ){
				if ( ( vecNeighbourPropertyStructure.getValue( uiActualElement ) != dActualValue ) &&
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
				DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::checkIfBorderIsAntialised() done to much points not antialised (ulNotAANeighboursNeededForNotAA="<<ulNotAANeighboursNeededForNotAA<<" + 2 ?<? ulNotAntialisedNeighbours="<<ulNotAntialisedNeighbours<<"  ulAntialisedNeighbours="<<ulAntialisedNeighbours<<"): return false"<<endl<<flush);
				return false;
			}
		}
		setStructureNeighboursNeighboursPoints.insert(
			setPointsNeighboursNei.begin(), setPointsNeighboursNei.end() );
	}//end for all neighbour points
	// 9 times more points antialised than not antialised
	const unsigned long ulAANeighboursNeedeForAA =
		ulNotAntialisedNeighbours * 9;
	DEBUG_OUT_L2(<<"ulAANeighboursNeedeForAA="<<ulAANeighboursNeedeForAA<<" ?<=? ulAntialisedNeighbours="<<ulAntialisedNeighbours<<"  ulNotAntialisedNeighbours="<<ulNotAntialisedNeighbours<<" ?<=? ulNotAANeighboursNeededForNotAA="<<ulNotAANeighboursNeededForNotAA<<" + 2"<<endl<<flush);
	if ( ( ulAANeighboursNeedeForAA <= ulAntialisedNeighbours ) &&
			( ulNotAntialisedNeighbours <= ( ulNotAANeighboursNeededForNotAA + 2 ) ) ){
		//area is antialised
		//add new structure points to structure
		pInOutImageStructure->setStructureBorderPoints(
			pInOutImageStructure->getStructureNeighbourPointsConst() );
		//now the border points are correct
		pInOutImageStructure->setStructureNeighbourPoints(
			setStructureNeighboursNeighboursPoints );
		pInOutImageStructure->setAntialised( true );
		DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::checkIfBorderIsAntialised() done return true"<<endl<<flush);
		return true;
	}//else
	DEBUG_OUT_L2(<<"cFindImageAreaLinearColorSimple("<<this<<")::checkIfBorderIsAntialised() done return false"<<endl<<flush);
	return false;
}






