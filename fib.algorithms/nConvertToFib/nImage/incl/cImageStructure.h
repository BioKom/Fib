/**
 * @file cImageStructure
 * file name: cImageStructure.h
 * @author Betti Oesterholz
 * @date 22.08.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class to store the data of a structure in an image.
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
 * This header specifies a class to store the data of a structure in an image.
 * If you want to convert an image to Fib structures, you have to search
 * the image for structures, which can be converted to Fib.
 * For this structures you can use this class
 */
/*
History:
22.08.2012  Oesterholz  created
*/


#ifndef ___C_IMAGE_STRUCTURE_H__
#define ___C_IMAGE_STRUCTURE_H__

#include "version.h"

#include "cVectorPosition.h"

#include <set>


using namespace std::set;


namespace fib{

namespace algorithms{

namespace nConvertToFib{

namespace nImage{


class cImageStructure{
protected:
	
	/**
	 * All points in the image structure.
	 */
	set<cVectorPosition> setStructurePoints;
	
	/**
	 * Points which are in the structure, but have neighbour points which
	 * are not in the structure.
	 * @see setStructureNeighbourPoints
	 * @see setStructurePoints
	 */
	set<cVectorPosition> setStructureBorderPoints;

	/**
	 * Points which are neighbours of points of the structure, but not in it.
	 * @see setStructureBorderPoints
	 * @see setStructurePoints
	 */
	set<cVectorPosition> setStructureNeighbourPoints;
	
	
	/**
	 * If the border points of the structure should be antialised.
	 */
	bool bIsAntialised;
	
public:
	
	/**
	 * standard constructor
	 */
	cImageStructure();
	
	/**
	 * copy constructor
	 *
	 * @param structureToCopy the image structure to copy
	 */
	cImageStructure( const cImageStructure & structureToCopy );
	
	
	/**
	 * destructor
	 */
	virtual ~cImageStructure();
	
	
	/**
	 * @return the set with the points of the structure
	 * 	@see setStructurePoints
	 */
	set<cVectorPosition> getStructurePoints() const;
	
	/**
	 * @return the set with the points of the structure
	 * 	@see setStructurePoints
	 */
	const set<cVectorPosition> & getStructurePoints() const;
	
	/**
	 * @return the set with the points which are in the structure, but have
	 * 	neighbour points which are not in the structure
	 * 	@see setStructureBorderPoints
	 */
	set<cVectorPosition> getStructureBorderPoints() const;
	
	/**
	 * @return the set with the points which are in the structure, but have
	 * 	neighbour points which are not in the structure
	 * 	@see setStructureBorderPoints
	 */
	const set<cVectorPosition> & getStructureBorderPoints() const;
	
	/**
	 * @return the set with the points which are neighbours of points of the
	 * 	structure, but not in it
	 * 	@see setStructureNeighbourPoints
	 */
	set<cVectorPosition> getStructureNeighbourPoints() const;
	
	/**
	 * @return the set with the points which are neighbours of points of the
	 * 	structure, but not in it
	 * 	@see setStructureNeighbourPoints
	 */
	const set<cVectorPosition> & getStructureNeighbourPoints() const;
	
	
	/**
	 * This method sets the points of the structure to the given points.
	 *
	 * @see setStructurePoints
	 * @param setInStructurePoints the set with the points of the structure
	 */
	void setStructurePoints( const set<cVectorPosition> & setInStructurePoints );
	
	/**
	 * This method sets the points which are in the structure, but have
	 * neighbour points which are not in the structure.
	 *
	 * @see setStructureBorderPoints
	 * @param setInStructureBorderPoints the set with the points which are
	 * 	in the structure, but have neighbour points which are not in the
	 * 	structure
	 */
	void setStructureBorderPoints( const set<cVectorPosition> & setInStructureBorderPoints );
	
	/**
	 * This method sets the points which are neighbours of points of the
	 * structure, but not in it.
	 *
	 * @see setStructureNeighbourPoints
	 * @param setInStructureBorderPoints the set with the points which are
	 * 	neighbours of points of the structure
	 */
	void setStructureNeighbourPoints( const set<cVectorPosition> & setInStructureNeighbourPoints );
	
	/**
	 * This method adds the given the given points to the structure.
	 *
	 * @see setStructurePoints
	 * @param setInStructurePoints the set with the points to add to the
	 * 	points of the structure
	 */
	void addStructurePoints( const set<cVectorPosition> & setInStructurePoints );
	
	/**
	 * This method adds the given points to the points which are in the
	 * structure, but have neighbour points which are not in the structure.
	 *
	 * @see setStructureBorderPoints
	 * @param setInStructureBorderPoints the set with the points which to
	 * 	add to the structure of points, which have neighbour points which
	 * 	are not in the structure
	 */
	void addStructureBorderPoints( const set<cVectorPosition> & setInStructureBorderPoints );
	
	/**
	 * This method adds the given points to the points which are neighbours
	 * of points of the structure, but not in it.
	 *
	 * @see setStructureNeighbourPoints
	 * @param setInStructureBorderPoints the set with the points to add as
	 * 	the neighbours of points of the structure
	 */
	void addStructureNeighbourPoints( const set<cVectorPosition> & setInStructureNeighbourPoints );
	
	/**
	 * This method adds the given the given point to the structure.
	 *
	 * @see setStructurePoints
	 * @param setInStructurePoints the point to add to the structure
	 */
	void addStructurePoints( const cVectorPosition & pointInStructurePoints );
	
	/**
	 * This method adds the given point to the points which are in the
	 * structure, but have neighbour points, which are not in the structure.
	 *
	 * @see setStructureBorderPoints
	 * @param setInStructureBorderPoints the point which to add to the
	 * 	structure of points which have neighbour points, which are not in
	 * 	the structure
	 */
	void addStructureBorderPoints( const cVectorPosition & pointInStructureBorderPoints );
	
	/**
	 * This method adds the given point to the points, which are neighbours
	 * of points of the structure, but not in it.
	 *
	 * @see setStructureNeighbourPoints
	 * @param setInStructureBorderPoints the points to add to the
	 * 	neighbours of points of the structure
	 */
	void addStructureNeighbourPoints( const cVectorPosition & pointInStructureNeighbourPoints );
	
	
	/**
	 * This method deletes the given points from the structure.
	 *
	 * @see setStructurePoints
	 * @param setInStructurePoints the set with the points to delete from the
	 * 	points of the structure
	 */
	void deleteStructurePoints( const set<cVectorPosition> & setInStructurePoints );
	
	/**
	 * This method deletes the given points from the points which are in the
	 * structure, but have neighbour points, which are not in the structure.
	 *
	 * @see setStructureBorderPoints
	 * @param setInStructureBorderPoints the set with the points which to
	 * 	delete from the structure of points which have neighbour points, which
	 * 	are not in the structure
	 */
	void deleteStructureBorderPoints( const set<cVectorPosition> & setInStructureBorderPoints );
	
	/**
	 * This method deletes the given points from the points which are neighbours
	 * of points of the structure, but not in it.
	 *
	 * @see setStructureNeighbourPoints
	 * @param setInStructureBorderPoints the set with the points to delete
	 * 	of the neighbours of points of the structure
	 */
	void deleteStructureNeighbourPoints( const set<cVectorPosition> & setInStructureNeighbourPoints );
	
	/**
	 * This method deletes the given the given point from the structure.
	 *
	 * @see setStructurePoints
	 * @param setInStructurePoints the point to delete from the structure
	 */
	void deleteStructurePoints( const cVectorPosition & pointInStructurePoints );
	
	/**
	 * This method deletes the given point from the points which are in the
	 * structure, but have neighbour points, which are not in the structure.
	 *
	 * @see setStructureBorderPoints
	 * @param setInStructureBorderPoints the point which to delete from the
	 * 	structure of points which have neighbour points, which are not in
	 * 	the structure
	 */
	void deleteStructureBorderPoints( const cVectorPosition & pointInStructureBorderPoints );
	
	/**
	 * This method deletes the given point from the points which are neighbours
	 * of points of the structure, but not in it.
	 *
	 * @see setStructureNeighbourPoints
	 * @param setInStructureBorderPoints the points to delete from the
	 * 	neighbours of points of the structure
	 */
	void deleteStructureNeighbourPoints( const cVectorPosition & pointInStructureNeighbourPoints );
	
	
	/**
	 * @see bIsAntialised
	 * @return if the structure border is antialised
	 */
	bool isAntialised() const;
	
	/**
	 * Set if the border as antialised.
	 *
	 * @see bIsAntialised
	 * @param bInIsAntialised if true the structure border will be set to
	 * 	antialised or if false, it will be to set to not antialised
	 */
	void setAntialised( const bool bInIsAntialised = true );
	
	
};//class cImageStructure


};//end namespace nImage
};//end namespace nConvertToFib
};//end namespace algorithms
};//end namespace fib


#endif //___C_IMAGE_STRUCTURE_H__