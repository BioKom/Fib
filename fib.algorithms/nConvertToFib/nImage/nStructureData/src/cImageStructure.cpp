/**
 * @file cImageStructure
 * file name: cImageStructure.cpp
 * @author Betti Oesterholz
 * @date 22.08.2012
 * @mail Oesterholz@Fib-development.org
 *
 * System: C++
 *
 * This file implements a class to store the data of a structure in an image.
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
 * This file implements a class to store the data of a structure in an image.
 * If you want to convert an image to Fib structures, you have to search
 * the image for structures, which can be converted to Fib.
 * For this structures you can use this class.
 */
/*
History:
22.08.2012  Oesterholz  created
*/


#include "cImageStructure.h"

#include "cImageAreaSameColor.h"
#include "cImageAreaLinearColor.h"
#include "cTypeProperty.h"
#include "cVectorProperty.h"

#include <cstring>



using namespace fib::algorithms::nConvertToFib::nImage::nStructureData;
using namespace fib;


/**
 * standard constructor
 */
cImageStructure::cImageStructure():bIsAntialised( false ){
	//noting to do
}


/**
 * copy constructor
 *
 * @param structureToCopy the image structure to copy
 */
cImageStructure::cImageStructure( const cImageStructure & structureToCopy ):
		structurePoints( structureToCopy.structurePoints ),
		structureBorderPoints( structureToCopy.structureBorderPoints ),
		structureNeighbourPoints( structureToCopy.structureNeighbourPoints ),
		bIsAntialised( structureToCopy.bIsAntialised ){
	//noting to do
}


/**
 * The constructor for restoring a image structure from an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node the image structure is stored in
 * @param outStatus a reference to an integer value where the error value
 * 	can be stored to.
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 */
cImageStructure::cImageStructure( const TiXmlElement * pXmlElement,
		intFib & outStatus ){
	
	outStatus = cImageStructure::restoreXml( pXmlElement );
}


/**
 * destructor
 */
cImageStructure::~cImageStructure(){
	//noting to do
}


/**
 * This method clones this object.
 *
 * @return a clone of this object
 */
cImageStructure * cImageStructure::clone() const{
	//copy this object
	return new cImageStructure( *this );
}



/**
 * @return the name of the image structure (class name without the leading 'c')
 */
string cImageStructure::getName() const{
	
	return "ImageStructure";
}


/**
 * @return the set with the points of the structure
 * 	@see structurePoints
 */
set<cVectorPosition> cImageStructure::getStructurePoints() const{
	
	return structurePoints;
}


/**
 * @return the set with the points of the structure
 * 	@see structurePoints
 */
const set<cVectorPosition> & cImageStructure::getStructurePointsConst() const{
	
	return structurePoints;
}


/**
 * @return the set with the points which are in the structure, but have
 * 	neighbour points which are not in the structure
 * 	@see structureBorderPoints
 */
set<cVectorPosition> cImageStructure::getStructureBorderPoints() const{
	
	return structureBorderPoints;
}


/**
 * @return the set with the points which are in the structure, but have
 * 	neighbour points which are not in the structure
 * 	@see structureBorderPoints
 */
const set<cVectorPosition> & cImageStructure::getStructureBorderPointsConst() const{
	
	return structureBorderPoints;
}


/**
 * @return the set with the points which are neighbours of points of the
 * 	structure, but not in it
 * 	@see structureNeighbourPoints
 */
set<cVectorPosition> cImageStructure::getStructureNeighbourPoints() const{
	
	return structureNeighbourPoints;
}


/**
 * @return the set with the points which are neighbours of points of the
 * 	structure, but not in it
 * 	@see structureNeighbourPoints
 */
const set<cVectorPosition> & cImageStructure::getStructureNeighbourPointsConst() const{
	
	return structureNeighbourPoints;
}



/**
 * This method sets the points of the structure to the given points.
 *
 * @see structurePoints
 * @param setInStructurePoints the set with the points of the structure
 */
void cImageStructure::setStructurePoints(
		const set<cVectorPosition> & setInStructurePoints ){
	
	structurePoints = setInStructurePoints;
}


/**
 * This method sets the points which are in the structure, but have
 * neighbour points which are not in the structure.
 *
 * @see structureBorderPoints
 * @param setInStructureBorderPoints the set with the points which are
 * 	in the structure, but have neighbour points which are not in the
 * 	structure
 */
void cImageStructure::setStructureBorderPoints(
		const set<cVectorPosition> & setInStructureBorderPoints ){
	
	structureBorderPoints = setInStructureBorderPoints;
}


/**
 * This method sets the points which are neighbours of points of the
 * structure, but not in it.
 *
 * @see structureNeighbourPoints
 * @param setInStructureNeighbourPoints the set with the points which are
 * 	neighbours of points of the structure
 */
void cImageStructure::setStructureNeighbourPoints(
		const set<cVectorPosition> & setInStructureNeighbourPoints ){
	
	structureNeighbourPoints = setInStructureNeighbourPoints;
}


/**
 * This method adds the given points to the structure.
 *
 * @see structurePoints
 * @param setInStructurePoints the set with the points to add to the
 * 	points of the structure
 */
void cImageStructure::addStructurePoints(
		const set<cVectorPosition> & setInStructurePoints ){
	
	structurePoints.insert(
		setInStructurePoints.begin(), setInStructurePoints.end() );
}


/**
 * This method adds the given points to the points which are in the
 * structure, but have neighbour points which are not in the structure.
 *
 * @see structureBorderPoints
 * @param setInStructureBorderPoints the set with the points which to
 * 	add to the structure of points, which have neighbour points which
 * 	are not in the structure
 */
void cImageStructure::addStructureBorderPoints(
		const set<cVectorPosition> & setInStructureBorderPoints ){
	
	structureBorderPoints.insert( setInStructureBorderPoints.begin(),
		setInStructureBorderPoints.end() );
}


/**
 * This method adds the given points to the points which are neighbours
 * of points of the structure, but not in it.
 *
 * @see structureNeighbourPoints
 * @param setInStructureNeighbourPoints the set with the points to add as
 * 	the neighbours of points of the structure
 */
void cImageStructure::addStructureNeighbourPoints(
		const set<cVectorPosition> & setInStructureNeighbourPoints ){
	
	structureNeighbourPoints.insert( setInStructureNeighbourPoints.begin(),
		setInStructureNeighbourPoints.end() );
}



/**
 * This method generates the structure neighbour points.
 * This means all points neighbour to the border points of the structure
 * but not in it will be added to the structure neighbour points.
 * All old neighbour points will be discarded before the search.
 *
 * @see structureNeighbourPoints
 * @see structureBorderPoints
 * @param pImageSearchData the image search data in which the neighbour
 * 	point must lay and which determines what are neighbour points;
 * 	if no image search structure is given the four neighbours with
 * 	distance one in one direction to a border point will be
 * 	considered its neighbour
 * @param bAddOverlapped if overlappted points should be added as
 * 	neighbour point
 */
void cImageStructure::generateStructureNeighbourPoint(
		const cImageSearchData * pImageSearchData,
		const bool bAddOverlapped ){
	//discard old neighbour points
	structureNeighbourPoints.clear();
	
	if ( pImageSearchData ){
		
		for ( set<cVectorPosition>::const_iterator
				itrBorderPoint = structureBorderPoints.begin();
				itrBorderPoint != structureBorderPoints.end(); itrBorderPoint++ ){
			
			const set<cVectorPosition> setNeighbours = bAddOverlapped ?
				pImageSearchData->getNeighbours( *itrBorderPoint ):
				pImageSearchData->getNotOverlappedNeighbours( *itrBorderPoint );
			
			for ( set<cVectorPosition>::const_iterator
					itrNeighbour = setNeighbours.begin();
					itrNeighbour != setNeighbours.end(); itrNeighbour++ ){
				
				const cVectorPosition & vecPoint = (*itrNeighbour);
				
				set<cVectorPosition>::const_iterator itrFoundPoint =
					structureBorderPoints.find( vecPoint );
				if ( itrFoundPoint == structureBorderPoints.end() ){
					//point not found in structure border
					itrFoundPoint = structurePoints.find( vecPoint );
					if ( itrFoundPoint == structurePoints.end() ){
						//point not found in structure -> a neighbour point -> add to neighbour point
						structureNeighbourPoints.insert( vecPoint );
					}
				}
			}//end for all neighbours
			
		}//end for all border point
	}else{
		cVectorPosition vecPoint( 2 );
		for ( set<cVectorPosition>::const_iterator
				itrBorderPoint = structureBorderPoints.begin();
				itrBorderPoint != structureBorderPoints.end(); itrBorderPoint++ ){
			
			vecPoint = (*itrBorderPoint);
			vecPoint.setValue( 1, vecPoint.getValue( 1 ) + 1.0 );
			
			set<cVectorPosition>::const_iterator itrFoundPoint =
				structureBorderPoints.find( vecPoint );
			if ( itrFoundPoint == structureBorderPoints.end() ){
				//point not found in structure border
				itrFoundPoint = structurePoints.find( vecPoint );
				if ( itrFoundPoint == structurePoints.end() ){
					//point not found in structure -> a neighbour point -> add to neighbour point
					structureNeighbourPoints.insert( vecPoint );
				}
			}
			
			vecPoint.setValue( 1, vecPoint.getValue( 1 ) - 2.0 );
			
			itrFoundPoint = structureBorderPoints.find( vecPoint );
			if ( itrFoundPoint == structureBorderPoints.end() ){
				//point not found in structure border
				itrFoundPoint = structurePoints.find( vecPoint );
				if ( itrFoundPoint == structurePoints.end() ){
					//point not found in structure -> a neighbour point -> add to neighbour point
					structureNeighbourPoints.insert( vecPoint );
				}
			}
			
			vecPoint = (*itrBorderPoint);
			vecPoint.setValue( 2, vecPoint.getValue( 2 ) + 1.0 );
			
			itrFoundPoint = structureBorderPoints.find( vecPoint );
			if ( itrFoundPoint == structureBorderPoints.end() ){
				//point not found in structure border
				itrFoundPoint = structurePoints.find( vecPoint );
				if ( itrFoundPoint == structurePoints.end() ){
					//point not found in structure -> a neighbour point -> add to neighbour point
					structureNeighbourPoints.insert( vecPoint );
				}
			}
			
			vecPoint.setValue( 2, vecPoint.getValue( 2 ) - 2.0 );
			
			itrFoundPoint = structureBorderPoints.find( vecPoint );
			if ( itrFoundPoint == structureBorderPoints.end() ){
				//point not found in structure border
				itrFoundPoint = structurePoints.find( vecPoint );
				if ( itrFoundPoint == structurePoints.end() ){
					//point not found in structure -> a neighbour point -> add to neighbour point
					structureNeighbourPoints.insert( vecPoint );
				}
			}
			
		}//end for all border point
	}
	
}



/**
 * This method adds the given point to the structure.
 *
 * @see structurePoints
 * @param pointInImageStructure the point to add to the structure
 */
void cImageStructure::addStructurePoint(
		const cVectorPosition & pointInImageStructure ){
	
	structurePoints.insert( pointInImageStructure );
}


/**
 * This method adds the given point to the points which are in the
 * structure, but have neighbour points, which are not in the structure.
 *
 * @see structureBorderPoints
 * @param pointInImageStructureBorder the point which to add to the
 * 	structure of points which have neighbour points, which are not in
 * 	the structure
 */
void cImageStructure::addStructureBorderPoint(
		const cVectorPosition & pointInImageStructureBorder ){
	
	structureBorderPoints.insert( pointInImageStructureBorder );
}


/**
 * This method adds the given point to the points, which are neighbours
 * of points of the structure, but not in it.
 *
 * @see structureNeighbourPoints
 * @param pointInImageStructureNeighbour the points to add to the
 * 	neighbours of points of the structure
 */
void cImageStructure::addStructureNeighbourPoint(
		const cVectorPosition & pointInImageStructureNeighbour ){
	
	structureNeighbourPoints.insert( pointInImageStructureNeighbour );
}



/**
 * This method deletes the given points from the structure.
 *
 * @see structurePoints
 * @param setInStructurePoints the set with the points to delete from the
 * 	points of the structure
 */
void cImageStructure::deleteStructurePoints(
		const set<cVectorPosition> & setInStructurePoints ){
	
	for ( set<cVectorPosition>::const_iterator itrPoint = setInStructurePoints.begin();
			itrPoint != setInStructurePoints.end(); itrPoint++ ){
		structurePoints.erase( *itrPoint );
	}
}


/**
 * This method deletes the given points from the points which are in the
 * structure, but have neighbour points, which are not in the structure.
 *
 * @see structureBorderPoints
 * @param setInStructureBorderPoints the set with the points which to
 * 	delete from the structure of points which have neighbour points, which
 * 	are not in the structure
 */
void cImageStructure::deleteStructureBorderPoints(
		const set<cVectorPosition> & setInStructureBorderPoints ){
	
	for ( set<cVectorPosition>::const_iterator itrPoint = setInStructureBorderPoints.begin();
			itrPoint != setInStructureBorderPoints.end(); itrPoint++ ){
		structureBorderPoints.erase( *itrPoint );
	}
}


/**
 * This method deletes the given points from the points which are neighbours
 * of points of the structure, but not in it.
 *
 * @see structureNeighbourPoints
 * @param setInStructureNeighbourPoints the set with the points to delete
 * 	of the neighbours of points of the structure
 */
void cImageStructure::deleteStructureNeighbourPoints(
		const set<cVectorPosition> & setInStructureNeighbourPoints ){
	
	for ( set<cVectorPosition>::const_iterator itrPoint = setInStructureNeighbourPoints.begin();
			itrPoint != setInStructureNeighbourPoints.end(); itrPoint++ ){
		structureNeighbourPoints.erase( *itrPoint );
	}
}


/**
 * This method deletes the given point from the structure.
 *
 * @see structurePoints
 * @param pointInImageStructure the point to delete from the structure
 */
void cImageStructure::deleteStructurePoint(
		const cVectorPosition & pointInImageStructure ){
	
	structurePoints.erase( pointInImageStructure );
}


/**
 * This method deletes the given point from the points which are in the
 * structure, but have neighbour points, which are not in the structure.
 *
 * @see structureBorderPoints
 * @param pointInImageStructureBorder the point which to delete from the
 * 	structure of points which have neighbour points, which are not in
 * 	the structure
 */
void cImageStructure::deleteStructureBorderPoint(
		const cVectorPosition & pointInImageStructureBorder ){
	
	structureBorderPoints.erase( pointInImageStructureBorder );
}


/**
 * This method deletes the given point from the points which are neighbours
 * of points of the structure, but not in it.
 *
 * @see structureNeighbourPoints
 * @param pointInImageStructureNeighbour the points to delete from the
 * 	neighbours of points of the structure
 */
void cImageStructure::deleteStructureNeighbourPoint(
		const cVectorPosition & pointInImageStructureNeighbour ){
	
	structureNeighbourPoints.erase( pointInImageStructureNeighbour );
}


//methods for points given as unsigned int pairs:

/**
 * @return the set with the points of the structure
 * 	@see structurePoints
 */
set< pair< unsigned int, unsigned int> > cImageStructure::getStructurePointsPair() const{
	
	return convertToVectorPair( structurePoints );
}


/**
 * @return the set with the points which are in the structure, but have
 * 	neighbour points which are not in the structure
 * 	@see structureBorderPoints
 */
set< pair< unsigned int, unsigned int> > cImageStructure::getStructureBorderPointsPair() const{
	
	return convertToVectorPair( structureBorderPoints );
}


/**
 * @return the set with the points which are neighbours of points of the
 * 	structure, but not in it
 * 	@see structureNeighbourPoints
 */
set< pair< unsigned int, unsigned int> > cImageStructure::getStructureNeighbourPointsPair() const{
	
	return convertToVectorPair( structureNeighbourPoints );
}


/**
 * This method sets the points of the structure to the given points.
 *
 * @see structurePoints
 * @param setInStructurePoints the set with the points of the structure
 */
void cImageStructure::setStructurePoints(
		const set< pair< unsigned int, unsigned int> > & setInStructurePoints ){
	
	structurePoints = convertToVectorPosition( setInStructurePoints );
}


/**
 * This method sets the points which are in the structure, but have
 * neighbour points which are not in the structure.
 *
 * @see structureBorderPoints
 * @param setInStructureBorderPoints the set with the points which are
 * 	in the structure, but have neighbour points which are not in the
 * 	structure
 */
void cImageStructure::setStructureBorderPoints(
		const set< pair< unsigned int, unsigned int> > & setInStructureBorderPoints ){
	
	structureBorderPoints = convertToVectorPosition( setInStructureBorderPoints );
}


/**
 * This method sets the points which are neighbours of points of the
 * structure, but not in it.
 *
 * @see structureNeighbourPoints
 * @param setInStructureNeighbourPoints the set with the points which are
 * 	neighbours of points of the structure
 */
void cImageStructure::setStructureNeighbourPoints(
		const set< pair< unsigned int, unsigned int> > & setInStructureNeighbourPoints ){
	
	structureNeighbourPoints = convertToVectorPosition( setInStructureNeighbourPoints );
}


/**
 * This method adds the given points to the structure.
 *
 * @see structurePoints
 * @param setInStructurePoints the set with the points to add to the
 * 	points of the structure
 */
void cImageStructure::addStructurePoints(
		const set< pair< unsigned int, unsigned int> > & setInStructurePoints ){
	
	addStructurePoints( convertToVectorPosition( setInStructurePoints ) );
}


/**
 * This method adds the given points to the points which are in the
 * structure, but have neighbour points which are not in the structure.
 *
 * @see structureBorderPoints
 * @param setInStructureBorderPoints the set with the points which to
 * 	add to the structure of points, which have neighbour points which
 * 	are not in the structure
 */
void cImageStructure::addStructureBorderPoints(
		const set< pair< unsigned int, unsigned int> > & setInStructureBorderPoints ){
	
	addStructureBorderPoints( convertToVectorPosition( setInStructureBorderPoints ) );
}


/**
 * This method adds the given points to the points which are neighbours
 * of points of the structure, but not in it.
 *
 * @see structureNeighbourPoints
 * @param setInStructureNeighbourPoints the set with the points to add as
 * 	the neighbours of points of the structure
 */
void cImageStructure::addStructureNeighbourPoints(
		const set< pair< unsigned int, unsigned int> > & setInStructureNeighbourPoints ){
	
	addStructureNeighbourPoints( convertToVectorPosition(
		setInStructureNeighbourPoints ) );
}


/**
 * This method adds the given point to the structure.
 *
 * @see structurePoints
 * @param pointInImageStructure the point to add to the structure
 */
void cImageStructure::addStructurePoint(
		const pair< unsigned int, unsigned int> & pointInImageStructure ){
	
	structurePoints.insert( convertToVectorPosition( pointInImageStructure ) );
}


/**
 * This method adds the given point to the points which are in the
 * structure, but have neighbour points, which are not in the structure.
 *
 * @see structureBorderPoints
 * @param pointInImageStructureBorder the point which to add to the
 * 	structure of points which have neighbour points, which are not in
 * 	the structure
 */
void cImageStructure::addStructureBorderPoint(
		const pair< unsigned int, unsigned int> & pointInImageStructureBorder ){
	
	structureBorderPoints.insert( convertToVectorPosition(
		pointInImageStructureBorder ) );
}


/**
 * This method adds the given point to the points, which are neighbours
 * of points of the structure, but not in it.
 *
 * @see structureNeighbourPoints
 * @param pointInImageStructureNeighbour the points to add to the
 * 	neighbours of points of the structure
 */
void cImageStructure::addStructureNeighbourPoint(
		const pair< unsigned int, unsigned int> & pointInImageStructureNeighbour ){
	
	structureNeighbourPoints.insert( convertToVectorPosition(
		pointInImageStructureNeighbour ) );
}


/**
 * This method deletes the given points from the structure.
 *
 * @see structurePoints
 * @param setInStructurePoints the set with the points to delete from the
 * 	points of the structure
 */
void cImageStructure::deleteStructurePoints(
		const set< pair< unsigned int, unsigned int> > & setInStructurePoints ){
	
	deleteStructurePoints( convertToVectorPosition( setInStructurePoints ) );
}


/**
 * This method deletes the given points from the points which are in the
 * structure, but have neighbour points, which are not in the structure.
 *
 * @see structureBorderPoints
 * @param setInStructureBorderPoints the set with the points which to
 * 	delete from the structure of points which have neighbour points, which
 * 	are not in the structure
 */
void cImageStructure::deleteStructureBorderPoints(
		const set< pair< unsigned int, unsigned int> > & setInStructureBorderPoints ){
	
	deleteStructureBorderPoints( convertToVectorPosition(
		setInStructureBorderPoints ) );
}


/**
 * This method deletes the given points from the points which are neighbours
 * of points of the structure, but not in it.
 *
 * @see structureNeighbourPoints
 * @param setInStructureNeighbourPoints the set with the points to delete
 * 	of the neighbours of points of the structure
 */
void cImageStructure::deleteStructureNeighbourPoints(
		const set< pair< unsigned int, unsigned int> > & setInStructureNeighbourPoints ){
	
	deleteStructureNeighbourPoints( convertToVectorPosition(
		setInStructureNeighbourPoints ) );
}


/**
 * This method deletes the given point from the structure.
 *
 * @see structurePoints
 * @param pointInImageStructure the point to delete from the structure
 */
void cImageStructure::deleteStructurePoint(
		const pair< unsigned int, unsigned int> & pointInImageStructure ){
	
	structurePoints.erase( convertToVectorPosition( pointInImageStructure ) );
}


/**
 * This method deletes the given point from the points which are in the
 * structure, but have neighbour points, which are not in the structure.
 *
 * @see structureBorderPoints
 * @param pointInImageStructureBorder the point which to delete from the
 * 	structure of points which have neighbour points, which are not in
 * 	the structure
 */
void cImageStructure::deleteStructureBorderPoint(
		const pair< unsigned int, unsigned int> & pointInImageStructureBorder ){
	
	structureBorderPoints.erase( convertToVectorPosition(
		pointInImageStructureBorder ) );
}


/**
 * This method deletes the given point from the points which are neighbours
 * of points of the structure, but not in it.
 *
 * @see structureNeighbourPoints
 * @param pointInImageStructureNeighbour the points to delete from the
 * 	neighbours of points of the structure
 */
void cImageStructure::deleteStructureNeighbourPoint(
		const pair< unsigned int, unsigned int> & pointInImageStructureNeighbour ){
	
	structureNeighbourPoints.erase( convertToVectorPosition(
		pointInImageStructureNeighbour ) );
}


/**
 * @see bIsAntialised
 * @return if the structure border is antialised
 */
bool cImageStructure::isAntialised() const{
	
	return bIsAntialised;
}


/**
 * This method returns if the given point is a structure point.
 *
 * @see structurePoints
 * @param pointInImageStructure the point for which to check if it is
 * 	a structure point
 * @return true if the given point is a structure point, else false
 */
bool cImageStructure::isStructurePoint( const cVectorPosition & pointInImageStructure ) const{
	
	const set<cVectorPosition>::const_iterator
		itrFoundPoint = structurePoints.find( pointInImageStructure );
	return ( itrFoundPoint != structurePoints.end() );
}


/**
 * This method returns if the given point is a structure border point.
 *
 * @see structureBorderPoints
 * @param pointInImageStructureBorder the point for which to check if
 * 	it is a structure border point
 * @return true if the given point is a structure border point, else false
 */
bool cImageStructure::isStructureBorderPoint(
		const cVectorPosition & pointInImageStructureBorder ) const{
	
	const set<cVectorPosition>::const_iterator
		itrFoundPoint = structureBorderPoints.find( pointInImageStructureBorder );
	return ( itrFoundPoint != structureBorderPoints.end() );
}


/**
 * This method returns if the given point is a structure neighbour point.
 *
 * @see structureNeighbourPoints
 * @param pointInImageStructureNeighbour the point for which to check
 * 	if it is a structure neighbour point
 * @return true if the given point is a structure neighbour point, else false
 */
bool cImageStructure::isStructureNeighbourPoint(
		const cVectorPosition & pointInImageStructureNeighbour ) const{
	
	const set<cVectorPosition>::const_iterator
		itrFoundPoint = structureNeighbourPoints.find( pointInImageStructureNeighbour );
	return ( itrFoundPoint != structureNeighbourPoints.end() );
}


/**
 * This method returns if the given point is a structure point.
 *
 * @see structurePoints
 * @param pointInImageStructure the point for which to check if it is
 * 	a structure point
 * @return true if the given point is a structure point, else false
 */
bool cImageStructure::isStructurePoint(
		const pair< unsigned int, unsigned int> & pointInImageStructure ) const{
	
	const set<cVectorPosition>::const_iterator
		itrFoundPoint = structurePoints.find( convertToVectorPosition(
			pointInImageStructure ) );
	return ( itrFoundPoint != structurePoints.end() );
}


/**
 * This method returns if the given point is a structure border point.
 *
 * @see structureBorderPoints
 * @param pointInImageStructureBorder the point for which to check if
 * 	it is a structure border point
 * @return true if the given point is a structure border point, else false
 */
bool cImageStructure::isStructureBorderPoint(
		const pair< unsigned int, unsigned int> & pointInImageStructureBorder ) const{
	
	const set<cVectorPosition>::const_iterator
		itrFoundPoint = structureBorderPoints.find( convertToVectorPosition(
			pointInImageStructureBorder ) );
	return ( itrFoundPoint != structureBorderPoints.end() );
}


/**
 * This method returns if the given point is a structure neighbour point.
 *
 * @see structureNeighbourPoints
 * @param pointInImageStructureNeighbour the point for which to check
 * 	if it is a structure neighbour point
 * @return true if the given point is a structure neighbour point, else false
 */
bool cImageStructure::isStructureNeighbourPoint(
		const pair< unsigned int, unsigned int> & pointInImageStructureNeighbour ) const{
	
	const set<cVectorPosition>::const_iterator
		itrFoundPoint = structureNeighbourPoints.find( convertToVectorPosition(
			pointInImageStructureNeighbour ) );
	return ( itrFoundPoint != structureNeighbourPoints.end() );
}


/**
 * @return true if the property types don't depend on the position of the
 * 	point, else false;
 * 	If true you can for example ignore the position parameters of:
 * 		@see getPropertyType()
 * 		@see getPropertyNumberForType()
 */
bool cImageStructure::isPropertyTypeIndependentOfPosition() const{
	
	return true;
}


/**
 * This method returns the number of properties for the image structure
 * point.
 *
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return value 0), else
 * 	it works as if the given point was included in this image structure
 * @param vecPoint the point for which to return the number of
 * 	properties
 * @return the number of property vectors for the given position
 */
unsigned int cImageStructure::getNumberOfProperties( const bool bEvenIfOutside,
		const cVectorPosition vecPoint ) const{
	
	return 0;
}


/**
 * This method returns the number of properties for the image structure
 * point.
 *
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return value 0), else
 * 	it works as if the given point was included in this image structure
 * @param point the point for which to return the number of
 * 	properties
 * @return the number of property vectors for the given position
 */
unsigned int cImageStructure::getNumberOfProperties( const bool bEvenIfOutside,
		const pair< unsigned int, unsigned int> point ) const{
	
	return 0;
}


/**
 * This method returns the number of the uiPropertyNumber'th property
 * type for the image structure point.
 * @see cTypeProperty
 * @see getPropertyNumberForType()
 *
 * @param uiPropertyNumber the number of the property to return the type of;
 * 	counting starts with 1; @see getNumberOfProperties()
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return value 0), else
 * 	it works as if the given point was included in this image structure
 * @param vecPoint the point for which to return the number of
 * 	the type of the property
 * @return the number of the type of the uiPropertyNumber'th property
 * 	on the given position, or 0 (cTypeProperty::NONE) if non exists
 * 	@see cTypeProperty
 */
unsigned int cImageStructure::getPropertyType( const unsigned int uiPropertyNumber,
		const bool bEvenIfOutside, const cVectorPosition vecPoint ) const{
	
	return cTypeProperty::NONE;
}


/**
 * This method returns the number of the uiPropertyNumber'th property
 * type for the image structure point.
 * @see cTypeProperty
 * @see getPropertyNumberForType()
 *
 * @param uiPropertyNumber the number of the property to return the type of;
 * 	counting starts with 1; @see getNumberOfProperties()
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return value 0), else
 * 	it works as if the given point was included in this image structure
 * @param point the point for which to return the number of
 * 	the type of the property
 * @return the number of the type of the uiPropertyNumber'th property
 * 	on the given position, or 0 (cTypeProperty::NONE) if non exists
 * 	@see cTypeProperty
 */
unsigned int cImageStructure::getPropertyType( const unsigned int uiPropertyNumber,
		const bool bEvenIfOutside, const pair< unsigned int, unsigned int> point ) const{
	
	return cTypeProperty::NONE;
}


/**
 * This method returns the property number for the given property type
 * for the image position.
 * @see cTypeProperty
 * @see getPropertyType()
 * @see getNumberOfProperties()
 *
 * @param uiPropertyType the type number of the property to return the
 * 	number of (e. g. cTypeProperty::COLOR_RGB )
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return value 0), else
 * 	it works as if the given point was included in this image structure
 * @param vecPoint the point for which to return the number of
 * 	the property of the given type
 * @return the number for the given property type for the image position,
 * 	or 0 if no such property extists
 * 	@see cTypeProperty
 */
unsigned int cImageStructure::getPropertyNumberForType( const unsigned int uiPropertyType,
		const bool bEvenIfOutside, const cVectorPosition vecPoint ) const{
	
	return 0;
}


/**
 * This method returns the property number for the given property type
 * for the image position.
 * @see cTypeProperty
 * @see getPropertyType()
 * @see getNumberOfProperties()
 *
 * @param uiPropertyType the type number of the property to return the
 * 	number of (e. g. cTypeProperty::COLOR_RGB )
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return value 0), else
 * 	it works as if the given point was included in this image structure
 * @param point the point for which to return the number of
 * 	the property of the given type
 * @return the number for the given property type for the image position,
 * 	or 0 if no such property extists
 * 	@see cTypeProperty
 */
unsigned int cImageStructure::getPropertyNumberForType( const unsigned int uiPropertyType,
		const bool bEvenIfOutside, const pair< unsigned int, unsigned int> point ) const{
	
	return 0;
}


/**
 * With this method the properties for given point are returned.
 * Antialising will be ignored. @see bIsAntialised
 *
 * @param vecPoint the point, for which the properties should be returned
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return empty list), else
 * 	it works as if the given point was included in this image structure
 * @return a list of the properties of the point
 */
list<cVectorProperty> cImageStructure::getPointProperties(
		const cVectorPosition & vecPoint, const bool bEvenIfOutside ) const{
	
	return list<cVectorProperty>();
}


/**
 * With this method the properties for given point are returned.
 * Antialising will be ignored. @see bIsAntialised
 *
 * @param point the point, for which the properties should be
 * 	returned
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return empty list), else
 * 	it works as if the given point was included in this image structure
 * @return a list of the properties of the point
 */
list<cVectorProperty> cImageStructure::getPointProperties(
		const pair< unsigned int, unsigned int> & point,
		const bool bEvenIfOutside ) const{
	
	return list<cVectorProperty>();
}


/**
 * This method returns the property of the given type for the given image
 * structure point.
 * Antialising will be ignored. @see bIsAntialised
 *
 * @param vecPoint the point of which to return the property vector
 * @param uiPropertyType the type number of the property to return
 * 	(e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return cTypeProperty::NONE),
 * 	 else it works as if the given point was included in this image structure
 * @return the property for the given type uiPropertyType for the given
 * 	point or the property of type cTypeProperty::NONE if non exists
 */
cVectorProperty cImageStructure::getProperty( const cVectorPosition & vecPoint,
		const unsigned int uiPropertyType, const bool bEvenIfOutside ) const{
	
	return cVectorProperty( cTypeProperty::NONE );
}


/**
 * This method returns the property of the given type for the given image
 * structure point.
 * Antialising will be ignored. @see bIsAntialised
 *
 * @param point the point of which to return the property vector
 * @param uiPropertyType the type number of the property to return
 * 	(e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return cTypeProperty::NONE),
 * 	 else it works as if the given point was included in this image structure
 * @return the property for the given type uiPropertyType for the given
 * 	point or the property of type cTypeProperty::NONE if non exists
 */
cVectorProperty cImageStructure::getProperty(
		const pair< unsigned int, unsigned int> & point,
		const unsigned int uiPropertyType, const bool bEvenIfOutside ) const{
	
	return cVectorProperty( cTypeProperty::NONE );
}


/**
 * This method returns the uiPropertyNumber'th property for the given image
 * structure point.
 * Antialising will be ignored. @see bIsAntialised
 *
 * @param vecPoint the point of which to return the property vector
 * @param uiPropertyNumber the number of the property to return;
 * 	counting starts with 1; @see getNumberOfProperties()
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return cTypeProperty::NONE),
 * 	 else it works as if the given point was included in this image structure
 * @return the uiPropertyNumber'th property from the given position or the
 * 	property of type cTypeProperty::NONE if non exists
 */
cVectorProperty cImageStructure::getPropertyForNumber( const cVectorPosition & vecPoint,
		const unsigned int uiPropertyNumber, const bool bEvenIfOutside ) const{
	
	return cVectorProperty( cTypeProperty::NONE );
}


/**
 * This method returns the uiPropertyNumber'th property for the given image
 * structure point.
 * Antialising will be ignored. @see bIsAntialised
 *
 * @param point the point of which to return the property vector
 * @param uiPropertyNumber the number of the property to return;
 * 	counting starts with 1; @see getNumberOfProperties()
 * @param bEvenIfOutside if false points outside this image structure
 * 	( getStructurePoints() ) will be ignored (return cTypeProperty::NONE),
 * 	 else it works as if the given point was included in this image structure
 * @return the uiPropertyNumber'th property from the given position or the
 * 	property of type cTypeProperty::NONE if non exists
 */
cVectorProperty cImageStructure::getPropertyForNumber(
		const pair< unsigned int, unsigned int> & point,
		const unsigned int uiPropertyNumber, const bool bEvenIfOutside ) const{
	
	return cVectorProperty( cTypeProperty::NONE );
}


/**
 * This method evaluades this image structure.
 * (Antialising will be ignored. @see bIsAntialised
 * It uses the getPointProperties() method of this class.)
 * @see getPointProperties()
 *
 * @pattern strategy
 * @param evaluePosition a reference to the object with the
 * 	evaluePosition() method to evalue /store the positions and ther
 * 	properties; for every point in the structure, this method is
 * 	called with the position and the properties of the point;
 * 	@see iEvaluePosition
 * @return if the evaluation was successfull true, else false
 */
bool cImageStructure::evalue( iEvaluePosition & evaluePosition ) const{
	
	for ( set<cVectorPosition>::const_iterator
			itrPoint = structurePoints.begin();
			itrPoint != structurePoints.end(); itrPoint++ ){
		
		evaluePosition.evaluePosition( *itrPoint,
			getPointProperties( *itrPoint ) );
	}
	return true;
}



/**
 * Set if the border as antialised.
 *
 * @see bIsAntialised
 * @param bInIsAntialised if true the structure border will be set to
 * 	antialised or if false, it will be to set to not antialised
 */
void cImageStructure::setAntialised( const bool bInIsAntialised ){
	
	bIsAntialised = bInIsAntialised;
}


/**
 * This method checks if the given image structure is equal to this
 * image structure.
 *
 * @param imageStructure the image structure which should be equal to
 * 	this image structure
 * @return true if the given image structure is equal to this image
 * 	structure, else false
 */
bool cImageStructure::equal( const cImageStructure &imageStructure ) const{
	
	//check if the classes are of the same type
	if ( getName() != imageStructure.getName() ){
		//classes are not of the same type -> not equal
		return false;
	}
	//compare members of this class
	
	//compare antialising
	if ( bIsAntialised != imageStructure.bIsAntialised ){
		//not equal
		return false;
	}
	//compare structure points
	if ( structurePoints != imageStructure.structurePoints ){
		//not equal
		return false;
	}
	//compare structure border points
	if ( structureBorderPoints != imageStructure.structureBorderPoints ){
		//not equal
		return false;
	}
	
	//compare structure neighbour points
	if ( structureNeighbourPoints != imageStructure.structureNeighbourPoints ){
		//not equal
		return false;
	}
	//all members equal -> objects equal
	return true;
}


/**
 * This method checks if the given image structure is equal to this
 * image structure.
 *
 * @param imageStructure the image structure which should be equal to
 * 	this image structure
 * @return true if the given image structure is equal to this image
 * 	structure, else false
 */
bool cImageStructure::operator==( const cImageStructure &imageStructure ) const{
	
	return this->equal( imageStructure );
}


/**
 * This method stores this image structure in the XML format into the
 * given stream.
 *
 * @param ostream the stream where image structure should be stored to
 * @return true if this image structure was stored, else false
 */
bool cImageStructure::storeXml( ostream & ostream ) const{
	
	ostream<<"<imageStructure ";
	//store antialising
	if ( bIsAntialised ){
		ostream<<"isAntialised=\"yes\" >"<<endl;
	}else{
		ostream<<"isAntialised=\"no\" >"<<endl;
	}
	
	//store structure points
	ostream<<"<structurePoints>"<<endl;
	for ( set<cVectorPosition>::const_iterator itrPoint = structurePoints.begin();
			itrPoint != structurePoints.end(); itrPoint++ ){
		
		itrPoint->storeXml( ostream );
	}
	ostream<<"</structurePoints>"<<endl;
	
	//store structure border points
	ostream<<"<structureBorderPoints>"<<endl;
	for ( set<cVectorPosition>::const_iterator itrPoint = structureBorderPoints.begin();
			itrPoint != structureBorderPoints.end(); itrPoint++ ){
		
		itrPoint->storeXml( ostream );
	}
	ostream<<"</structureBorderPoints>"<<endl;
	
	//store structure neighbours points
	ostream<<"<structureNeighbourPoints>"<<endl;
	for ( set<cVectorPosition>::const_iterator itrPoint = structureNeighbourPoints.begin();
			itrPoint != structureNeighbourPoints.end(); itrPoint++ ){
		
		itrPoint->storeXml( ostream );
	}
	ostream<<"</structureNeighbourPoints>"<<endl;
	
	ostream<<"</imageStructure>"<<endl;
	return true;
}


/**
 * This method restores image structure from the stream where it is
 * stored in the XML format.
 *
 * @pattern Factory Method
 * @param stream the stream where the  image structure is stored in
 * @param pOutStatus a pointer to an integer value where the error value
 * 	can be stored to. If the pointer is NULL no error value will be
 * 	given back.
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid stream
 * 		- -2 loading error, invalid data in stream
 * 		- 1 loading warning, invalid data in stream, error could be corrected
 * 		- 2 loading warning, invalid data in stream, maybe the loaded
 * 			object is wrong
 * @return the readed  image structure or the null pointer NULL, if
 * 	reading was not possible
 */
cImageStructure * cImageStructure::restoreXml( istream &stream,
		intFib * pOutStatus ){
	
	
	TiXmlDocument xmlDocFibObject;

	stream >> xmlDocFibObject;
	
	if ( xmlDocFibObject.Error() ){
		//Error: invalid stream
		if ( pOutStatus ){
			(*pOutStatus) = -1;
		}
		return NULL;
	}
	
	if ( pOutStatus ){
		return cImageStructure::restoreXmlNode( &xmlDocFibObject, *pOutStatus );
	}
	intFib outStatus;
	return cImageStructure::restoreXmlNode( &xmlDocFibObject, outStatus );
}


/**
 * This method restores a image structure in the XML format from a
 * TinyXml node element.
 *
 * @pattern Factory method
 * @param pXmlNode a pointer to the TinyXml node wher the image
 * 	structure is stored in
 * @param outStatus an integer value with the error value;
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlNode
 * 		- -2 loading error, invalid data in pXmlNode
 * 		- 1 loading warning, invalid data in pXmlNode, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlNode, maybe the loaded
 * 			object is wrong
 * @return the pointers to the restored image structure, if non could be
 * 	restored the returned pointer is NULL
 */
cImageStructure * cImageStructure::restoreXmlNode(
		const TiXmlNode * pXmlNode, intFib & outStatus ){
	
	if ( pXmlNode == NULL ){
		//Error: nothing to load
		outStatus = -1;
		return NULL;
	}
	
	const TiXmlElement * pXmlElement = NULL;

	/* try to find basis XML element
	-> as long as no XML element was read and no error occured*/
	while ( ( pXmlElement == NULL ) && ( pXmlNode != NULL ) &&
			( 0 <= outStatus ) ){
		//get type of XML element
		const int iType = pXmlNode->Type();
		
		switch ( iType ){
			case TiXmlNode::ELEMENT:{
				//check if this is a valid XML element
				pXmlElement = pXmlNode->ToElement();
				if ( pXmlElement == NULL ){
					//Error: nothing to load
					outStatus = -1;
					return NULL;
				}//else pXmlElement != NULL -> next steps
			}break;
			case TiXmlNode::DOCUMENT:{
				//check the child elements
				const TiXmlNode * pChild = pXmlNode->FirstChild();
				
				cImageStructure * pRestoredImageStructure =
					restoreXmlNode( pChild, outStatus );
				if ( pRestoredImageStructure != NULL ){
					return pRestoredImageStructure;
				}
				if ( outStatus < 0 ){
					//an error occured
					return NULL;
				}
			}break;
			case TiXmlNode::DECLARATION:
			case TiXmlNode::COMMENT:{
				//ignore
			}break;
			case TiXmlNode::TEXT:
			case TiXmlNode::UNKNOWN:
			default:
				//ignore; Warning: invalid element
				outStatus = 2;
		}//end switch XML element type
		//if no element was read check next XML element
		pXmlNode = pXmlNode->NextSibling();
	}//end as long as no XML element was read and no error occured
	if ( pXmlElement == NULL ){
		//Error: nothing to load
		outStatus = -1;
		return NULL;
	}//else pXmlElement != NULL -> next steps
	
	cImageStructure * pImageStructureRestore = NULL;
	
	const string szElementType( pXmlElement->Value() );
	
	intFib iReturnValue = 0;
	if ( szElementType == "imageStructure" ){
		pImageStructureRestore = new cImageStructure( pXmlElement, iReturnValue );
		
	}else if ( szElementType == "imageAreaSameColor" ){
		pImageStructureRestore = new cImageAreaSameColor( pXmlElement, iReturnValue );
		
	}else if ( szElementType == "imageAreaLinearColor" ){
		pImageStructureRestore = new cImageAreaLinearColor( pXmlElement, iReturnValue );
		
	}else{//Warning: no image structur to restore
		outStatus = 2;
	}//TODO more image structur classes
	
	if ( iReturnValue < 0 ){
		outStatus = iReturnValue;
	}else if ( ( outStatus < iReturnValue ) && ( 0 <= outStatus ) ){
		outStatus = iReturnValue;
	}
	return pImageStructureRestore;
}


/**
 * This method restores a image structure from the stream, where it is
 * stored in the XML format.
 *
 * @param stream the stream where the image structure is stored in
 * @return an integer value with the error value;
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 */
intFib cImageStructure::restoreXml( istream & stream ){
	
	TiXmlDocument xmlDocFibObject;
	
	stream >> xmlDocFibObject;
	
	if ( xmlDocFibObject.Error() ){
		//Error: nothing to load
		return -1;
	}
	
	const TiXmlNode * pXmlNode = &xmlDocFibObject;
	const TiXmlElement * pXmlElement = NULL;
	
	intFib outStatus = 0;
	/* try to find basis XML element
	-> as long as no XML element was read and no error occured*/
	list< const TiXmlNode* > liDocumentNodes;
	
	while ( ( pXmlElement == NULL ) && ( pXmlNode != NULL ) ){
		//get type of XML element
		const int iType = pXmlNode->Type();
		
		switch ( iType ){
			case TiXmlNode::ELEMENT:{
				//check if this is a valid XML element
				pXmlElement = pXmlNode->ToElement();
				if ( pXmlElement == NULL ){
					//Error: nothing to load
					return -1;
				}//else pXmlElement != NULL -> next steps
			}break;
			case TiXmlNode::DOCUMENT:{
				//check the child elements
				const TiXmlNode * pXmlChildNode = pXmlNode->FirstChild();
				
				if ( pXmlChildNode != NULL ){
					//store child node for later evaluation
					liDocumentNodes.push_back( pXmlChildNode );
				}
			}break;
			case TiXmlNode::DECLARATION:
			case TiXmlNode::COMMENT:{
				//ignore
			}break;
			case TiXmlNode::TEXT:
			case TiXmlNode::UNKNOWN:
			default:
				//ignore; Warning: invalid element
				outStatus = 2;
		}//end switch XML element type
		//if no element was read check next XML element
		pXmlNode = pXmlNode->NextSibling();
		if ( pXmlNode == NULL ){
			//all nodes checked, check found document nodes
			pXmlNode = liDocumentNodes.back();
			liDocumentNodes.pop_back();
		}
		
	}//end as long as no XML element was read and no error occured
	if ( pXmlElement == NULL ){
		//Error: nothing to load
		return -1;
	}//else pXmlElement != NULL -> next steps
	
	
	
	//restore data
	const intFib iReturn = restoreXml( pXmlElement );
	if ( iReturn < 0 ){
		//error
		return iReturn;
	}
	if ( iReturn < outStatus ){
		return outStatus;
	}
	return iReturn;
}


/**
 * This method restores a image structure in the XML format from a
 * TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node wher the image
 * 	structure is stored in
 * @return an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 */
intFib cImageStructure::restoreXml( const TiXmlElement * pXmlElement ){
	
	if ( pXmlElement == NULL ){
		//noting to restore
		return -1;
	}
	const string szElementType( pXmlElement->Value() );
	if ( szElementType != "imageStructure" ){
		//wrong element type to restore
		return -2;
	}
	
	intFib iReturn = 0;
	
	//read the if antialised
	bIsAntialised = false;//default not antialised
	const char * szIsAntialised = pXmlElement->Attribute( "isAntialised" );
	if ( szIsAntialised != NULL ){
		//the optional attribute isAntialised exists
		
		if (  ( szIsAntialised[ 0 ] == 'y' ) ||
				( szIsAntialised[ 0 ] == 'Y' ) ||
				( szIsAntialised[ 0 ] == 't' ) ||
				( szIsAntialised[ 0 ] == 'T' ) ||
				( szIsAntialised[ 0 ] == 'j' ) ||
				( szIsAntialised[ 0 ] == 'J' ) ){
			//structure is antialised
			bIsAntialised = true;
		}
	}
	//no variables defined
	list<cFibVariable*> liDefinedVariables;
	
	for ( const TiXmlNode * pChild = pXmlElement->FirstChild();
			pChild != NULL; pChild = pChild->NextSibling() ) {
		
		const int iType = pChild->Type();
		
		switch ( iType ){
			case TiXmlNode::ELEMENT:{
				//load the member point lists
				const TiXmlElement * pXmlElement = pChild->ToElement();
				if ( pXmlElement == NULL ){
					if ( iReturn == 0 ){
						iReturn = 1;
					}
					continue;
				}
				const string szElementType( pXmlElement->Value() );
				
				bool bRestoreStructurePoints = false;
				bool bRestoreStructureBorderPoints    = false;
				bool bRestoreStructureNeighbourPoints = false;
				
				if ( szElementType == "structurePoints" ){
					//restore structure points
					bRestoreStructurePoints = true;
					
				}else if ( szElementType == "structureBorderPoints" ){
					//restore structure border points
					bRestoreStructureBorderPoints = true;
					
				}else if ( szElementType == "structureNeighbourPoints" ){
					//restore border neighbour points
					bRestoreStructureNeighbourPoints = true;
				}else{//unknown element
					if ( iReturn == 0 ){
						iReturn = 1;
					}
					continue;
				}
				//read vectors with structure points
				const TiXmlElement * pXmlVector = NULL;
				if ( pXmlElement->FirstChildElement( "vector" ) ){
					
					pXmlVector = pXmlElement->FirstChildElement( "vector" );
				}
				for( ; pXmlVector != NULL;
						pXmlVector = pXmlVector->NextSiblingElement( "vector" ) ){
				
					//check the attribute of the vector
					const char * szVectorXmlType = pXmlVector->Attribute( "type" );
					
					if ( szVectorXmlType == NULL ){
						if ( iReturn == 0 ){
							iReturn = 2;
						}
						continue;
					}else if ( string( "position" ).compare( szVectorXmlType ) != 0 ){
						if ( iReturn == 0 ){
							iReturn = 2;
						}
						continue;
					}
					//error value to return
					intFib outStatus = 0;
					//restore the vector
					if ( bRestoreStructurePoints ){
						//restore structure points
						structurePoints.insert( cVectorPosition(
							pXmlVector, outStatus, liDefinedVariables ) );
						
					}else if ( bRestoreStructureBorderPoints ){
						//restore structure border points
						structureBorderPoints.insert( cVectorPosition(
							pXmlVector, outStatus, liDefinedVariables ) );
						
					}else if ( bRestoreStructureNeighbourPoints ){
						//restore border neighbour points
						structureNeighbourPoints.insert( cVectorPosition(
							pXmlVector, outStatus, liDefinedVariables ) );
					}//else not possible
					if ( outStatus < 0 ){
						return outStatus;
					}
					if ( ( iReturn < outStatus ) && ( 0 <= iReturn ) ){
						iReturn = outStatus;
					}
				}//end for all vectors
				
			}break;
			
			case TiXmlNode::DECLARATION:
			case TiXmlNode::COMMENT:{
				//ignore
				continue;
			}break;
			case TiXmlNode::DOCUMENT:
			case TiXmlNode::TEXT:
			case TiXmlNode::UNKNOWN:
			default:
				//invalid image structur
				if ( iReturn != 0  ){
					iReturn = 1;
				}
				continue;
		}
	}//end switch restore image structure members
	
	return iReturn;
}



//methods of iConvertImageStructureToFib

/**
 * This method is for converting the data of this object to a Fib object.
 *
 * @return a Fib object which represents the data of this object
 * 	Beware: You have to delete the returned Fib object after usage.
 * 		Also the given root element will contain no domains, you have to
 * 		create them if needed (eg. with cRoot::generateNeededDomains() ).
 */
cRoot * cImageStructure::convertToFib() const{
	
	//use empty search data (for "perfect match")
	cImageSearchData imageSearchData( 0, 0 );
	return convertToFib( &imageSearchData );
}


/**
 * This method is for converting the data of this object to a Fib object.
 * The area is converted with the iConvertAreaToExtObjects class,
 * which is set by the cUseConvertAreaToExtObjectsStrategy class methods.
 * For antialising it uses the cConvertFibDatabaseObject::convertToAntialised()
 * method.
 * @see iConvertAreaToExtObjects
 * @see cConvertFibDatabaseObject::convertToAntialised()
 * @see iConvertAreaToExtObjects
 * @see cUseConvertAreaToExtObjectsStrategy
 *
 * @param pImageSearchData a pointer to the image search data of found
 * 	image parts, which will overwrite area parts
 * 	(the area can be bigger, because some parts of it won't be seen)
 * @param maxValue the maximum possible value in all evalued parameters
 * 	of the evalued Fib elements will allways have lower absolute values
 * 	or the values (parameters) of the Fib elements are coordinate values
 * 	of points;
 * 	if 0 (standard value) is given, the maximum possible value will
 * 	be evalued from the given data (absolute maximum in given data * 256)
 * @param maxErrorPerValue the maximal error for the border points to
 * 	find on one border point; every point in the area of the generated
 * 	Fib object will have a distance lower or equal maxErrorPerValue
 * 	to a point in this structure or an overlappted point of pImageSearchData
 * @return a Fib object which represents the data of this object
 * 	Beware: You have to delete the returned Fib object after usage.
 * 		Also the given root element will contain no domains, you have to
 * 		create them if needed (eg. with cRoot::generateNeededDomains() ).
 */
cRoot * cImageStructure::convertToFib(
		const cImageSearchData * pImageSearchData,
		const double maxValue, const unsigned long ulMaxErrorPerPoint ) const{
	
	const double maxErrorPerValue = ulMaxErrorPerPoint;
	
	//convert this object into a external object area
	const list< cExtObject * > liConvertedTiles =
		getStrategy()->convertToExtObjects( structurePoints, pImageSearchData,
			bIsAntialised, maxValue, maxErrorPerValue );
	
	if ( liConvertedTiles.empty() ){
		//can not create an Fib object
		return NULL;
	}
	//sort external objects acording their identifiers
	map< longFib, list< cExtObject * > > mapExtObjectClasses;
	
	for ( list< cExtObject * >::const_iterator itrExtObject = liConvertedTiles.begin();
			itrExtObject != liConvertedTiles.end(); itrExtObject++ ){
		
		mapExtObjectClasses[ (*itrExtObject)->getIdentifier() ].push_back(
			*itrExtObject );
	}
	
	/*if more than one external object for one identifier exists
	 -> convert the external object list into a set element with an external
	 object subobject*/
	list< cFibElement * > liConvertedObjects;
	
	for ( map< longFib, list< cExtObject * > >::iterator
			itrActualExtObjectClass = mapExtObjectClasses.begin();
			itrActualExtObjectClass != mapExtObjectClasses.end();
			itrActualExtObjectClass++ ){
		
		list< cExtObject * > & liConvertedExtObjects =
			itrActualExtObjectClass->second;
		
		if ( 1 < liConvertedExtObjects.size() ){
			//combine the external objects into one set element
			cExtObject * pActualExternalObject =
				liConvertedExtObjects.front();
			
			const unsigned int uiNumberInVar =
				pActualExternalObject->getNumberOfInputValues();
			
			cFibSet * pSetElement = new cFibSet( uiNumberInVar, pActualExternalObject );
			liConvertedObjects.push_back( pSetElement );
			
			/* set the input variables of the external object to the defined
			 * variables of the set element*/
			cVectorExtObject * pVecInputVector = pActualExternalObject->getInputVector();
			cVectorFibSet vecSet( uiNumberInVar );
			for ( unsigned int uiActualVariable = 1; uiActualVariable <= uiNumberInVar;
					uiActualVariable++ ){
				
				vecSet.setValue( uiActualVariable,
					pVecInputVector->getValue( uiActualVariable ) );
				
				pVecInputVector->setVariable( uiActualVariable,
					pSetElement->getDefinedVariable( uiActualVariable ) );
			}
			//remove original external object
			pSetElement->addVector( vecSet );
			liConvertedExtObjects.pop_front();
			
			//add for every original external object element a vector to the set element
			while ( ! liConvertedExtObjects.empty() ){
				pActualExternalObject = liConvertedExtObjects.back();
				
				const cVectorExtObject * pVecActualExtObject =
					pActualExternalObject->getInputVector();
				//copy the values from the external object to set vector to add
				for ( unsigned int uiActualVariable = 1;
						uiActualVariable <= uiNumberInVar; uiActualVariable++ ){
					
					vecSet.setValue( uiActualVariable,
						pVecActualExtObject->getValue( uiActualVariable ) );
				}
				pSetElement->addVector( vecSet );
				
				//remove original external object
				pActualExternalObject->deleteObject();
				liConvertedExtObjects.pop_back();
			}
		}else{//one object in liConvertedExtObjects
			liConvertedObjects.push_back( liConvertedExtObjects.front() );
		}//end if convert liConvertedExtObjects
	}//end for convert external object class
	//all to use Fib objects are in liConvertedObjects
	
	cFibElement * pConvertedObject = NULL;

	//if needed put all objects into a list element
	pConvertedObject = liConvertedObjects.front();
	if ( 1 < liConvertedObjects.size() ){
		pConvertedObject = new cList( liConvertedObjects );
	}
	
	//put the created object into an root element
	cRoot * pCreatedRootObject = new cRoot( pConvertedObject );
	
	return pCreatedRootObject;
}



/**
 * This function converts the given point into a cVectorPosition point.
 *
 * @param paPoint the point to convert
 * @return a cVectorPosition object which represents the point
 */
cVectorPosition cImageStructure::convertToVectorPosition(
		const pair< unsigned int, unsigned int> & paPoint ){
	
	cVectorPosition vecPosition( 2 );
	vecPosition.setValue( 1, paPoint.first );
	vecPosition.setValue( 2, paPoint.second );
	return vecPosition;
}


/**
 * This function converts the given points into cVectorPosition points.
 *
 * @param setPaPoint the set with the points to convert
 * @return a set with the cVectorPosition objects, which represents the
 * 	points in setPaPoint
 */
set< cVectorPosition > cImageStructure::convertToVectorPosition(
		const set< pair< unsigned int, unsigned int> > & setPaPoint ){
	
	set< cVectorPosition > setVecPostions;
	cVectorPosition vecPosition( 2 );
	
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrPoint = setPaPoint.begin();
			itrPoint != setPaPoint.end(); itrPoint++ ){
		
		vecPosition.setValue( 1, itrPoint->first );
		vecPosition.setValue( 2, itrPoint->second );
		setVecPostions.insert( vecPosition );
	}
	return setVecPostions;
}


/**
 * This function converts the given point into a pair point.
 *
 * @param vecPoint the point to convert
 * @return a unsigned int pair which represents the point
 */
pair< unsigned int, unsigned int> cImageStructure::convertToVectorPair(
		const cVectorPosition & vecPoint ){
	
	const longFib lX = roundToLongFib( vecPoint.getValue( 1 ) );
	const longFib lY = roundToLongFib( vecPoint.getValue( 2 ) );
	
	return pair< unsigned int, unsigned int>(
		((0 < lX) ? lX : 0), ((0 < lY) ? lY : 0) );
}


/**
 * This function converts the given points into pair points.
 *
 * @param setVecPoint the set with the points to convert
 * @return a set with the unsigned int pairs, which represents the
 * 	points in setVecPoint
 */
set< pair< unsigned int, unsigned int> > cImageStructure::convertToVectorPair(
		const set< cVectorPosition > & setVecPoint ){
	
	set< pair< unsigned int, unsigned int> > setPaPostions;
	
	for ( set< cVectorPosition >::const_iterator
			itrPoint = setVecPoint.begin();
			itrPoint != setVecPoint.end(); itrPoint++ ){
		
		const longFib lX = roundToLongFib( itrPoint->getValue( 1 ) );
		const longFib lY = roundToLongFib( itrPoint->getValue( 2 ) );
		setPaPostions.insert( pair< unsigned int, unsigned int>(
			((0 < lX) ? lX : 0), ((0 < lY) ? lY : 0) ) );
	}
	return setPaPostions;
}



