/**
 * @file cImageStructure
 * file name: cImageStructure.cpp
 * @author Betti Oesterholz
 * @date 22.08.2012
 * @mail webmaster@BioKom.info
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
 * GNU Lesser General Public License for more details.
 *
 * This file implements a class to store the data of a structure in an image.
 * If you want to convert an image to Fib structures, you have to search
 * the image for structures, which can be converted to Fib.
 * For this structures you can use this class
 */
/*
History:
22.08.2012  Oesterholz  created
*/


#include "cImageStructure.h"



using namespace std::set;

using namespace fib;

using namespace fib::algorithms::nConvertToFib::nImage;


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
		setStructurePoints( structureToCopy.setStructurePoints ),
		setStructureBorderPoints( structureToCopy.setStructureBorderPoints ),
		setStructureNeighbourPoints( structureToCopy.setStructureNeighbourPoints ),
		bIsAntialised( structureToCopy.bIsAntialised ){
	//noting to do
}


/**
 * destructor
 */
cImageStructure::~cImageStructure(){
	//noting to do
}



/**
 * @return the set with the points of the structure
 * 	@see setStructurePoints
 */
set<cVectorPosition> cImageStructure::getStructurePoints() const{
	
	return setStructurePoints;
}


/**
 * @return the set with the points of the structure
 * 	@see setStructurePoints
 */
const set<cVectorPosition> & cImageStructure::getStructurePoints() const{
	
	return setStructurePoints;
}


/**
 * @return the set with the points which are in the structure, but have
 * 	neighbour points which are not in the structure
 * 	@see setStructureBorderPoints
 */
set<cVectorPosition> cImageStructure::getStructureBorderPoints() const{
	
	return setStructureBorderPoints;
}


/**
 * @return the set with the points which are in the structure, but have
 * 	neighbour points which are not in the structure
 * 	@see setStructureBorderPoints
 */
const set<cVectorPosition> & cImageStructure::getStructureBorderPoints() const{
	
	return setStructureBorderPoints;
}


/**
 * @return the set with the points which are neighbours of points of the
 * 	structure, but not in it
 * 	@see setStructureNeighbourPoints
 */
set<cVectorPosition> cImageStructure::getStructureNeighbourPoints() const{
	
	return setStructureNeighbourPoints;
}


/**
 * @return the set with the points which are neighbours of points of the
 * 	structure, but not in it
 * 	@see setStructureNeighbourPoints
 */
const set<cVectorPosition> & cImageStructure::getStructureNeighbourPoints() const{
	
	return setStructureNeighbourPoints;
}



/**
 * This method sets the points of the structure to the given points.
 *
 * @see setStructurePoints
 * @param setInStructurePoints the set with the points of the structure
 */
void cImageStructure::setStructurePoints(
		const set<cVectorPosition> & setInStructurePoints ){
	
	setStructurePoints = setInStructurePoints;
}


/**
 * This method sets the points which are in the structure, but have
 * neighbour points which are not in the structure.
 *
 * @see setStructureBorderPoints
 * @param setInStructureBorderPoints the set with the points which are
 * 	in the structure, but have neighbour points which are not in the
 * 	structure
 */
void cImageStructure::setStructureBorderPoints(
		const set<cVectorPosition> & setInStructureBorderPoints ){
	
	setStructureBorderPoints = setInStructureBorderPoints;
}


/**
 * This method sets the points which are neighbours of points of the
 * structure, but not in it.
 *
 * @see setStructureNeighbourPoints
 * @param setInStructureBorderPoints the set with the points which are
 * 	neighbours of points of the structure
 */
void cImageStructure::setStructureNeighbourPoints(
		const set<cVectorPosition> & setInStructureNeighbourPoints ){
	
	setStructureNeighbourPoints = setInStructureNeighbourPoints;
}


/**
 * This method adds the given the given points to the structure.
 *
 * @see setStructurePoints
 * @param setInStructurePoints the set with the points to add to the
 * 	points of the structure
 */
void cImageStructure::addStructurePoints(
		const set<cVectorPosition> & setInStructurePoints ){
	
	setStructurePoints.insert(
		setInStructurePoints.begin(), setInStructurePoints.end() );
}


/**
 * This method adds the given points to the points which are in the
 * structure, but have neighbour points which are not in the structure.
 *
 * @see setStructureBorderPoints
 * @param setInStructureBorderPoints the set with the points which to
 * 	add to the structure of points, which have neighbour points which
 * 	are not in the structure
 */
void cImageStructure::addStructureBorderPoints(
		const set<cVectorPosition> & setInStructureBorderPoints ){
	
	setStructureBorderPoints.insert( setInStructureBorderPoints.begin(),
		setInStructureBorderPoints.end() );
}


/**
 * This method adds the given points to the points which are neighbours
 * of points of the structure, but not in it.
 *
 * @see setStructureNeighbourPoints
 * @param setInStructureBorderPoints the set with the points to add as
 * 	the neighbours of points of the structure
 */
void cImageStructure::addStructureNeighbourPoints(
		const set<cVectorPosition> & setInStructureNeighbourPoints ){
	
	setStructureNeighbourPoints.insert( setInStructureNeighbourPoints.begin(),
		setInStructureNeighbourPoints.end() );
}


/**
 * This method adds the given the given point to the structure.
 *
 * @see setStructurePoints
 * @param setInStructurePoints the point to add to the structure
 */
void cImageStructure::addStructurePoints(
		const cVectorPosition & pointInStructurePoints ){
	
	setStructurePoints.insert( pointInStructurePoints );
}


/**
 * This method adds the given point to the points which are in the
 * structure, but have neighbour points, which are not in the structure.
 *
 * @see setStructureBorderPoints
 * @param setInStructureBorderPoints the point which to add to the
 * 	structure of points which have neighbour points, which are not in
 * 	the structure
 */
void cImageStructure::addStructureBorderPoints(
		const cVectorPosition & pointInStructureBorderPoints ){
	
	setStructureBorderPoints.insert( pointInStructureBorderPoints );
}


/**
 * This method adds the given point to the points, which are neighbours
 * of points of the structure, but not in it.
 *
 * @see setStructureNeighbourPoints
 * @param setInStructureBorderPoints the points to add to the
 * 	neighbours of points of the structure
 */
void cImageStructure::addStructureNeighbourPoints(
		const cVectorPosition & pointInStructureNeighbourPoints ){
	
	setStructureNeighbourPoints.insert( pointInStructureNeighbourPoints );
}



/**
 * This method deletes the given points from the structure.
 *
 * @see setStructurePoints
 * @param setInStructurePoints the set with the points to delete from the
 * 	points of the structure
 */
void cImageStructure::deleteStructurePoints(
		const set<cVectorPosition> & setInStructurePoints ){
	
	for ( set<cVectorPosition>::const_iterator itrPoint = setInStructurePoints.begin();
			itrPoint != setInStructurePoints.end(); itrPoint++ ){
		setStructurePoints.erase( *itrPoint );
	}
}


/**
 * This method deletes the given points from the points which are in the
 * structure, but have neighbour points, which are not in the structure.
 *
 * @see setStructureBorderPoints
 * @param setInStructureBorderPoints the set with the points which to
 * 	delete from the structure of points which have neighbour points, which
 * 	are not in the structure
 */
void cImageStructure::deleteStructureBorderPoints(
		const set<cVectorPosition> & setInStructureBorderPoints ){
	
	for ( set<cVectorPosition>::const_iterator itrPoint = setInStructureBorderPoints.begin();
			itrPoint != setInStructureBorderPoints.end(); itrPoint++ ){
		setStructureBorderPoints.erase( *itrPoint );
	}
}


/**
 * This method deletes the given points from the points which are neighbours
 * of points of the structure, but not in it.
 *
 * @see setStructureNeighbourPoints
 * @param setInStructureBorderPoints the set with the points to delete
 * 	of the neighbours of points of the structure
 */
void cImageStructure::deleteStructureNeighbourPoints(
		const set<cVectorPosition> & setInStructureNeighbourPoints ){
	
	for ( set<cVectorPosition>::const_iterator itrPoint = setInStructureNeighbourPoints.begin();
			itrPoint != setInStructureNeighbourPoints.end(); itrPoint++ ){
		setStructureNeighbourPoints.erase( *itrPoint );
	}
}


/**
 * This method deletes the given the given point from the structure.
 *
 * @see setStructurePoints
 * @param setInStructurePoints the point to delete from the structure
 */
void cImageStructure::deleteStructurePoints(
		const cVectorPosition & pointInStructurePoints ){
	
	setStructurePoints.erase( pointInStructurePoints );
}


/**
 * This method deletes the given point from the points which are in the
 * structure, but have neighbour points, which are not in the structure.
 *
 * @see setStructureBorderPoints
 * @param setInStructureBorderPoints the point which to delete from the
 * 	structure of points which have neighbour points, which are not in
 * 	the structure
 */
void cImageStructure::deleteStructureBorderPoints(
		const cVectorPosition & pointInStructureBorderPoints ){
	
	setStructureBorderPoints.erase( pointInStructureBorderPoints );
}


/**
 * This method deletes the given point from the points which are neighbours
 * of points of the structure, but not in it.
 *
 * @see setStructureNeighbourPoints
 * @param setInStructureBorderPoints the points to delete from the
 * 	neighbours of points of the structure
 */
void cImageStructure::deleteStructureNeighbourPoints(
		const cVectorPosition & pointInStructureNeighbourPoints ){
	
	setStructureNeighbourPoints.erase( pointInStructureNeighbourPoints );
}



/**
 * @see bIsAntialised
 * @return if the structure border is antialised
 */
bool cImageStructure::isAntialised() const{
	
	return bIsAntialised;
}


/**
 * Set if the border as antialised.
 *
 * @see bIsAntialised
 * @param bInIsAntialised if true the structure border will be set to
 * 	antialised or if false, it will be to set to not antialised
 */
void cImageStructure::setAntialised( const bool bInIsAntialised = true ){
	
	bIsAntialised = bInIsAntialised;
}





