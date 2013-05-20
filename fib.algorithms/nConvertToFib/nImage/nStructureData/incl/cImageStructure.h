/**
 * @file cImageStructure
 * file name: cImageStructure.h
 * @author Betti Oesterholz
 * @date 22.08.2012
 * @mail Oesterholz@Fib-development.org
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
 * GNU General Public License for more details.
 *
 * This header specifies a class to store the data of a structure in an image.
 * If you want to convert an image to Fib structures, you have to search
 * the image for structures, which can be converted to Fib.
 * For this structures you can use this class.
 */
/*
History:
22.08.2012  Oesterholz  created
*/


#ifndef ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__C_IMAGE_STRUCTURE_H__
#define ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__C_IMAGE_STRUCTURE_H__

#include "version.h"

#include "iConvertImageStructureToFib.h"
#include "cUseConvertAreaToExtObjectsStrategy.h"

#include "cVectorPosition.h"

#include "tinyxml.h"

#include "cFibSet.h"
#include "cList.h"
#include "cRoot.h"
#include "iEvaluePosition.h"
#include "cConvertFibDatabaseObject.h"

#include <set>
#include <string>


using namespace std;


namespace fib{

namespace algorithms{

namespace nConvertToFib{

namespace nImage{

namespace nStructureData{


class cImageStructure:
	public iConvertImageStructureToFib,
	public nConvertToFib::cUseConvertAreaToExtObjectsStrategy{
protected:
	
	/**
	 * All points in the image structure.
	 */
	set<cVectorPosition> structurePoints;
	
	/**
	 * Points which are in the structure, but have neighbour points which
	 * are not in the structure.
	 * @see structureNeighbourPoints
	 * @see structurePoints
	 */
	set<cVectorPosition> structureBorderPoints;

	/**
	 * Points which are neighbours of points of the structure, but not in it.
	 * @see structureBorderPoints
	 * @see structurePoints
	 */
	set<cVectorPosition> structureNeighbourPoints;
	
	
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
	cImageStructure( const TiXmlElement * pXmlElement, intFib & outStatus );
	
	
	/**
	 * destructor
	 */
	virtual ~cImageStructure();
	
	/**
	 * This method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cImageStructure *clone() const;
	
	
	/**
	 * @return the name of the image structure (class name without the leading 'c')
	 */
	virtual string getName() const;
	
	/**
	 * @return the set with the points of the structure
	 * 	@see structurePoints
	 */
	set<cVectorPosition> getStructurePoints() const;
	
	/**
	 * @return the set with the points of the structure
	 * 	@see structurePoints
	 */
	const set<cVectorPosition> & getStructurePointsConst() const;
	
	/**
	 * @return the set with the points which are in the structure, but have
	 * 	neighbour points which are not in the structure
	 * 	@see structureBorderPoints
	 */
	set<cVectorPosition> getStructureBorderPoints() const;
	
	/**
	 * @return the set with the points which are in the structure, but have
	 * 	neighbour points which are not in the structure
	 * 	@see structureBorderPoints
	 */
	const set<cVectorPosition> & getStructureBorderPointsConst() const;
	
	/**
	 * @return the set with the points which are neighbours of points of the
	 * 	structure, but not in it
	 * 	@see structureNeighbourPoints
	 */
	set<cVectorPosition> getStructureNeighbourPoints() const;
	
	/**
	 * @return the set with the points which are neighbours of points of the
	 * 	structure, but not in it
	 * 	@see structureNeighbourPoints
	 */
	const set<cVectorPosition> & getStructureNeighbourPointsConst() const;
	
	
	/**
	 * This method sets the points of the structure to the given points.
	 *
	 * @see structurePoints
	 * @param setInStructurePoints the set with the points of the structure
	 */
	void setStructurePoints( const set<cVectorPosition> & setInStructurePoints );
	
	/**
	 * This method sets the points which are in the structure, but have
	 * neighbour points which are not in the structure.
	 *
	 * @see structureBorderPoints
	 * @param setInStructureBorderPoints the set with the points which are
	 * 	in the structure, but have neighbour points which are not in the
	 * 	structure
	 */
	void setStructureBorderPoints( const set<cVectorPosition> & setInStructureBorderPoints );
	
	/**
	 * This method sets the points which are neighbours of points of the
	 * structure, but not in it.
	 *
	 * @see structureNeighbourPoints
	 * @param setInStructureNeighbourPoints the set with the points which are
	 * 	neighbours of points of the structure
	 */
	void setStructureNeighbourPoints( const set<cVectorPosition> & setInStructureNeighbourPoints );
	
	/**
	 * This method adds the given points to the structure.
	 *
	 * @see structurePoints
	 * @param setInStructurePoints the set with the points to add to the
	 * 	points of the structure
	 */
	void addStructurePoints( const set<cVectorPosition> & setInStructurePoints );
	
	/**
	 * This method adds the given points to the points which are in the
	 * structure, but have neighbour points which are not in the structure.
	 *
	 * @see structureBorderPoints
	 * @param setInStructureBorderPoints the set with the points which to
	 * 	add to the structure of points, which have neighbour points which
	 * 	are not in the structure
	 */
	void addStructureBorderPoints( const set<cVectorPosition> & setInStructureBorderPoints );
	
	/**
	 * This method adds the given points to the points which are neighbours
	 * of points of the structure, but not in it.
	 *
	 * @see structureNeighbourPoints
	 * @param setInStructureNeighbourPoints the set with the points to add as
	 * 	the neighbours of points of the structure
	 */
	void addStructureNeighbourPoints( const set<cVectorPosition> & setInStructureNeighbourPoints );
	
	/**
	 * This method adds the given point to the structure.
	 *
	 * @see structurePoints
	 * @param pointInImageStructure the point to add to the structure
	 */
	void addStructurePoint( const cVectorPosition & pointInImageStructure );
	
	/**
	 * This method adds the given point to the points which are in the
	 * structure, but have neighbour points, which are not in the structure.
	 *
	 * @see structureBorderPoints
	 * @param pointInImageStructureBorder the point which to add to the
	 * 	structure of points which have neighbour points, which are not in
	 * 	the structure
	 */
	void addStructureBorderPoint( const cVectorPosition & pointInImageStructureBorder );
	
	/**
	 * This method adds the given point to the points, which are neighbours
	 * of points of the structure, but not in it.
	 *
	 * @see structureNeighbourPoints
	 * @param pointInImageStructureNeighbour the points to add to the
	 * 	neighbours of points of the structure
	 */
	void addStructureNeighbourPoint( const cVectorPosition & pointInImageStructureNeighbour );
	
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
	void generateStructureNeighbourPoint(
		const cImageSearchData * pImageSearchData = NULL,
		const bool bAddOverlapped = true );
	
	
	/**
	 * This method deletes the given points from the structure.
	 *
	 * @see structurePoints
	 * @param setInStructurePoints the set with the points to delete from the
	 * 	points of the structure
	 */
	void deleteStructurePoints( const set<cVectorPosition> & setInStructurePoints );
	
	/**
	 * This method deletes the given points from the points which are in the
	 * structure, but have neighbour points, which are not in the structure.
	 *
	 * @see structureBorderPoints
	 * @param setInStructureBorderPoints the set with the points which to
	 * 	delete from the structure of points which have neighbour points, which
	 * 	are not in the structure
	 */
	void deleteStructureBorderPoints( const set<cVectorPosition> & setInStructureBorderPoints );
	
	/**
	 * This method deletes the given points from the points which are neighbours
	 * of points of the structure, but not in it.
	 *
	 * @see structureNeighbourPoints
	 * @param setInStructureNeighbourPoints the set with the points to delete
	 * 	of the neighbours of points of the structure
	 */
	void deleteStructureNeighbourPoints( const set<cVectorPosition> & setInStructureNeighbourPoints );
	
	/**
	 * This method deletes the given point from the structure.
	 *
	 * @see structurePoints
	 * @param pointInImageStructure the point to delete from the structure
	 */
	void deleteStructurePoint( const cVectorPosition & pointInImageStructure );
	
	/**
	 * This method deletes the given point from the points which are in the
	 * structure, but have neighbour points, which are not in the structure.
	 *
	 * @see structureBorderPoints
	 * @param pointInImageStructureBorder the point which to delete from the
	 * 	structure of points which have neighbour points, which are not in
	 * 	the structure
	 */
	void deleteStructureBorderPoint( const cVectorPosition & pointInImageStructureBorder );
	
	/**
	 * This method deletes the given point from the points which are neighbours
	 * of points of the structure, but not in it.
	 *
	 * @see structureNeighbourPoints
	 * @param pointInImageStructureNeighbour the points to delete from the
	 * 	neighbours of points of the structure
	 */
	void deleteStructureNeighbourPoint( const cVectorPosition & pointInImageStructureNeighbour );
	
	
//methods for points given as unsigned int pairs:
	
	/**
	 * @return the set with the points of the structure
	 * 	@see structurePoints
	 */
	set< pair< unsigned int, unsigned int> > getStructurePointsPair() const;
	
	/**
	 * @return the set with the points which are in the structure, but have
	 * 	neighbour points which are not in the structure
	 * 	@see structureBorderPoints
	 */
	set< pair< unsigned int, unsigned int> > getStructureBorderPointsPair() const;
	
	/**
	 * @return the set with the points which are neighbours of points of the
	 * 	structure, but not in it
	 * 	@see structureNeighbourPoints
	 */
	set< pair< unsigned int, unsigned int> > getStructureNeighbourPointsPair() const;
	
	
	/**
	 * This method sets the points of the structure to the given points.
	 *
	 * @see structurePoints
	 * @param setInStructurePoints the set with the points of the structure
	 */
	void setStructurePoints(
		const set< pair< unsigned int, unsigned int> > & setInStructurePoints );
	
	/**
	 * This method sets the points which are in the structure, but have
	 * neighbour points which are not in the structure.
	 *
	 * @see structureBorderPoints
	 * @param setInStructureBorderPoints the set with the points which are
	 * 	in the structure, but have neighbour points which are not in the
	 * 	structure
	 */
	void setStructureBorderPoints( const set< pair< unsigned int, unsigned int> > &
		setInStructureBorderPoints );
	
	/**
	 * This method sets the points which are neighbours of points of the
	 * structure, but not in it.
	 *
	 * @see structureNeighbourPoints
	 * @param setInStructureNeighbourPoints the set with the points which are
	 * 	neighbours of points of the structure
	 */
	void setStructureNeighbourPoints( const set< pair< unsigned int, unsigned int> > &
		setInStructureNeighbourPoints );
	
	/**
	 * This method adds the given points to the structure.
	 *
	 * @see structurePoints
	 * @param setInStructurePoints the set with the points to add to the
	 * 	points of the structure
	 */
	void addStructurePoints( const set< pair< unsigned int, unsigned int> > &
		setInStructurePoints );
	
	/**
	 * This method adds the given points to the points which are in the
	 * structure, but have neighbour points which are not in the structure.
	 *
	 * @see structureBorderPoints
	 * @param setInStructureBorderPoints the set with the points which to
	 * 	add to the structure of points, which have neighbour points which
	 * 	are not in the structure
	 */
	void addStructureBorderPoints( const set< pair< unsigned int, unsigned int> > &
		setInStructureBorderPoints );
	
	/**
	 * This method adds the given points to the points which are neighbours
	 * of points of the structure, but not in it.
	 *
	 * @see structureNeighbourPoints
	 * @param setInStructureNeighbourPoints the set with the points to add as
	 * 	the neighbours of points of the structure
	 */
	void addStructureNeighbourPoints( const set< pair< unsigned int, unsigned int> > &
		setInStructureNeighbourPoints );
	
	/**
	 * This method adds the given point to the structure.
	 *
	 * @see structurePoints
	 * @param pointInImageStructure the point to add to the structure
	 */
	void addStructurePoint( const pair< unsigned int, unsigned int> &
		pointInImageStructure );
	
	/**
	 * This method adds the given point to the points which are in the
	 * structure, but have neighbour points, which are not in the structure.
	 *
	 * @see structureBorderPoints
	 * @param pointInImageStructureBorder the point which to add to the
	 * 	structure of points which have neighbour points, which are not in
	 * 	the structure
	 */
	void addStructureBorderPoint( const pair< unsigned int, unsigned int> &
		pointInImageStructureBorder );
	
	/**
	 * This method adds the given point to the points, which are neighbours
	 * of points of the structure, but not in it.
	 *
	 * @see structureNeighbourPoints
	 * @param pointInImageStructureNeighbour the points to add to the
	 * 	neighbours of points of the structure
	 */
	void addStructureNeighbourPoint( const pair< unsigned int, unsigned int> &
		pointInImageStructureNeighbour );

	/**
	 * This method deletes the given points from the structure.
	 *
	 * @see structurePoints
	 * @param setInStructurePoints the set with the points to delete from the
	 * 	points of the structure
	 */
	void deleteStructurePoints( const set< pair< unsigned int, unsigned int> > &
		setInStructurePoints );
	
	/**
	 * This method deletes the given points from the points which are in the
	 * structure, but have neighbour points, which are not in the structure.
	 *
	 * @see structureBorderPoints
	 * @param setInStructureBorderPoints the set with the points which to
	 * 	delete from the structure of points which have neighbour points, which
	 * 	are not in the structure
	 */
	void deleteStructureBorderPoints( const set< pair< unsigned int, unsigned int> > &
		setInStructureBorderPoints );
	
	/**
	 * This method deletes the given points from the points which are neighbours
	 * of points of the structure, but not in it.
	 *
	 * @see structureNeighbourPoints
	 * @param setInStructureNeighbourPoints the set with the points to delete
	 * 	of the neighbours of points of the structure
	 */
	void deleteStructureNeighbourPoints( const set< pair< unsigned int, unsigned int> > &
		setInStructureNeighbourPoints );
	
	/**
	 * This method deletes the given point from the structure.
	 *
	 * @see structurePoints
	 * @param pointInImageStructure the point to delete from the structure
	 */
	void deleteStructurePoint( const pair< unsigned int, unsigned int> &
		pointInImageStructure );
	
	/**
	 * This method deletes the given point from the points which are in the
	 * structure, but have neighbour points, which are not in the structure.
	 *
	 * @see structureBorderPoints
	 * @param pointInImageStructureBorder the point which to delete from the
	 * 	structure of points which have neighbour points, which are not in
	 * 	the structure
	 */
	void deleteStructureBorderPoint( const pair< unsigned int, unsigned int> &
		pointInImageStructureBorder );
	
	/**
	 * This method deletes the given point from the points which are neighbours
	 * of points of the structure, but not in it.
	 *
	 * @see structureNeighbourPoints
	 * @param pointInImageStructureNeighbour the points to delete from the
	 * 	neighbours of points of the structure
	 */
	void deleteStructureNeighbourPoint( const pair< unsigned int, unsigned int> &
		pointInImageStructureNeighbour );
	
	
	
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
	
	
	/**
	 * This method returns if the given point is a structure point.
	 *
	 * @see structurePoints
	 * @param pointInImageStructure the point for which to check if it is
	 * 	a structure point
	 * @return true if the given point is a structure point, else false
	 */
	bool isStructurePoint( const cVectorPosition & pointInImageStructure ) const;
	
	/**
	 * This method returns if the given point is a structure border point.
	 *
	 * @see structureBorderPoints
	 * @param pointInImageStructureBorder the point for which to check if
	 * 	it is a structure border point
	 * @return true if the given point is a structure border point, else false
	 */
	bool isStructureBorderPoint( const cVectorPosition & pointInImageStructureBorder ) const;
	
	/**
	 * This method returns if the given point is a structure neighbour point.
	 *
	 * @see structureNeighbourPoints
	 * @param pointInImageStructureNeighbour the point for which to check
	 * 	if it is a structure neighbour point
	 * @return true if the given point is a structure neighbour point, else false
	 */
	bool isStructureNeighbourPoint( const cVectorPosition & pointInImageStructureNeighbour ) const;
	
	/**
	 * This method returns if the given point is a structure point.
	 *
	 * @see structurePoints
	 * @param pointInImageStructure the point for which to check if it is
	 * 	a structure point
	 * @return true if the given point is a structure point, else false
	 */
	bool isStructurePoint(
		const pair< unsigned int, unsigned int> & pointInImageStructure ) const;
	
	/**
	 * This method returns if the given point is a structure border point.
	 *
	 * @see structureBorderPoints
	 * @param pointInImageStructureBorder the point for which to check if
	 * 	it is a structure border point
	 * @return true if the given point is a structure border point, else false
	 */
	bool isStructureBorderPoint(
		const pair< unsigned int, unsigned int> & pointInImageStructureBorder ) const;
	
	/**
	 * This method returns if the given point is a structure neighbour point.
	 *
	 * @see structureNeighbourPoints
	 * @param pointInImageStructureNeighbour the point for which to check
	 * 	if it is a structure neighbour point
	 * @return true if the given point is a structure neighbour point, else false
	 */
	bool isStructureNeighbourPoint(
		const pair< unsigned int, unsigned int> & pointInImageStructureNeighbour ) const;
	
	
	/**
	 * @return true if the property types don't depend on the position of the
	 * 	point, else false;
	 * 	If true you can for example ignore the position parameters of:
	 * 		@see getPropertyType()
	 * 		@see getPropertyNumberForType()
	 */
	virtual bool isPropertyTypeIndependentOfPosition() const;
	
	/**
	 * This method returns the number of properties for the given image
	 * structure point.
	 *
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( isStructurePoint() ) will be ignored (return value 0), else
	 * 	it works as if the given point was included in this image structure
	 * @param vecPoint the point for which to return the number of properties
	 * @return the number of property vectors for the given point
	 */
	virtual unsigned int getNumberOfProperties( const bool bEvenIfOutside = false,
		const cVectorPosition vecPoint = cVectorPosition( 2 ) ) const;
	
	/**
	 * This method returns the number of properties for the given image
	 * structure point.
	 *
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( isStructurePoint() ) will be ignored (return value 0), else
	 * 	it works as if the given point was included in this image structure
	 * @param point the point for which to return the number of
	 * 	properties
	 * @return the number of property vectors for the given point
	 */
	virtual unsigned int getNumberOfProperties( const bool bEvenIfOutside = false,
		const pair< unsigned int, unsigned int> point =
			pair< unsigned int, unsigned int>(0, 0) ) const;
	
	/**
	 * This method returns the number of the uiPropertyNumber'th property
	 * type for the image structure point.
	 * @see cTypeProperty
	 * @see getPropertyNumberForType()
	 *
	 * @param uiPropertyNumber the number of the property to return the type of;
	 * 	counting starts with 1; @see getNumberOfProperties()
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( isStructurePoint() ) will be ignored (return value 0), else
	 * 	it works as if the given point was included in this image structure
	 * @param vecPoint the point for which to return the number of
	 * 	the type of the property
	 * @return the number of the type of the uiPropertyNumber'th property
	 * 	on the given point, or 0 (cTypeProperty::NONE) if non exists
	 * 	@see cTypeProperty
	 */
	virtual unsigned int getPropertyType( const unsigned int uiPropertyNumber,
		const bool bEvenIfOutside = false,
		const cVectorPosition vecPoint = cVectorPosition( 2 ) ) const;
	
	/**
	 * This method returns the number of the uiPropertyNumber'th property
	 * type for the image structure point.
	 * @see cTypeProperty
	 * @see getPropertyNumberForType()
	 *
	 * @param uiPropertyNumber the number of the property to return the type of;
	 * 	counting starts with 1; @see getNumberOfProperties()
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( isStructurePoint() ) will be ignored (return value 0), else
	 * 	it works as if the given point was included in this image structure
	 * @param point the point for which to return the number of
	 * 	the type of the property
	 * @return the number of the type of the uiPropertyNumber'th property
	 * 	on the given point, or 0 (cTypeProperty::NONE) if non exists
	 * 	@see cTypeProperty
	 */
	virtual unsigned int getPropertyType( const unsigned int uiPropertyNumber,
		const bool bEvenIfOutside = false,
		const pair< unsigned int, unsigned int> point =
			pair< unsigned int, unsigned int>(0, 0) ) const;
	
	/**
	 * This method returns the property number for the given property type
	 * for the image point.
	 * @see cTypeProperty
	 * @see getPropertyType()
	 * @see getNumberOfProperties()
	 *
	 * @param uiPropertyType the type number of the property to return the
	 * 	number of (e. g. cTypeProperty::COLOR_RGB )
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( isStructurePoint() ) will be ignored (return value 0), else
	 * 	it works as if the given point was included in this image structure
	 * @param vecPoint the point for which to return the number of
	 * 	the property of the given type
	 * @return the number for the given property type for the image point,
	 * 	or 0 if no such property extists
	 * 	@see cTypeProperty
	 */
	virtual unsigned int getPropertyNumberForType( const unsigned int uiPropertyType,
		const bool bEvenIfOutside = false,
		const cVectorPosition vecPoint = cVectorPosition( 2 ) ) const;
	
	/**
	 * This method returns the property number for the given property type
	 * for the image point.
	 * @see cTypeProperty
	 * @see getPropertyType()
	 * @see getNumberOfProperties()
	 *
	 * @param uiPropertyType the type number of the property to return the
	 * 	number of (e. g. cTypeProperty::COLOR_RGB )
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( isStructurePoint() ) will be ignored (return value 0), else
	 * 	it works as if the given point was included in this image structure
	 * @param point the point for which to return the number of
	 * 	the property of the given type
	 * @return the number for the given property type for the image point,
	 * 	or 0 if no such property extists
	 * 	@see cTypeProperty
	 */
	virtual unsigned int getPropertyNumberForType( const unsigned int uiPropertyType,
		const bool bEvenIfOutside = false,
		const pair< unsigned int, unsigned int> point =
			pair< unsigned int, unsigned int>(0, 0) ) const;
	
	/**
	 * With this method the properties for given point are returned.
	 * Antialising will be ignored. @see bIsAntialised
	 *
	 * @param vecPoint the point, for which the properties should be returned
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( isStructurePoint() ) will be ignored (return empty list), else
	 * 	it works as if the given point was included in this image structure
	 * @return a list of the properties of the point
	 */
	virtual list<cVectorProperty> getPointProperties(
		const cVectorPosition & vecPoint,
		const bool bEvenIfOutside = false ) const;
	
	/**
	 * With this method the properties for given point are returned.
	 * Antialising will be ignored. @see bIsAntialised
	 *
	 * @param point the point, for which the properties should be
	 * 	returned
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( isStructurePoint() ) will be ignored (return empty list), else
	 * 	it works as if the given point was included in this image structure
	 * @return a list of the properties of the point
	 */
	virtual list<cVectorProperty> getPointProperties(
		const pair< unsigned int, unsigned int> & point,
		const bool bEvenIfOutside = false ) const;
	
	/**
	 * This method returns the property of the given type for the given image
	 * structure point.
	 * Antialising will be ignored. @see bIsAntialised
	 *
	 * @param vecPoint the point of which to return the property vector
	 * @param uiPropertyType the type number of the property to return
	 * 	(e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( isStructurePoint() ) will be ignored (return cTypeProperty::NONE),
	 * 	 else it works as if the given point was included in this image structure
	 * @return the property for the given type uiPropertyType for the given
	 * 	point or the property of type cTypeProperty::NONE if non exists
	 */
	virtual cVectorProperty getProperty( const cVectorPosition & vecPoint,
		const unsigned int uiPropertyType = 0, const bool bEvenIfOutside = false ) const;
	
	/**
	 * This method returns the property of the given type for the given image
	 * structure point.
	 * Antialising will be ignored. @see bIsAntialised
	 *
	 * @param point the point of which to return the property vector
	 * @param uiPropertyType the type number of the property to return
	 * 	(e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( isStructurePoint() ) will be ignored (return cTypeProperty::NONE),
	 * 	 else it works as if the given point was included in this image structure
	 * @return the property for the given type uiPropertyType for the given
	 * 	point or the property of type cTypeProperty::NONE if non exists
	 */
	virtual cVectorProperty getProperty(
		const pair< unsigned int, unsigned int> & point,
		const unsigned int uiPropertyType = 0, const bool bEvenIfOutside = false ) const;
	
	/**
	 * This method returns the uiPropertyNumber'th property for the given
	 * image structure point.
	 * Antialising will be ignored. @see bIsAntialised
	 *
	 * @param vecPoint the point of which to return the property vector
	 * @param uiPropertyNumber the number of the property to return;
	 * 	counting starts with 1; @see getNumberOfProperties()
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( isStructurePoint() ) will be ignored (return cTypeProperty::NONE),
	 * 	 else it works as if the given point was included in this image structure
	 * @return the uiPropertyNumber'th property from the given point or the
	 * 	property of type cTypeProperty::NONE if non exists
	 */
	virtual cVectorProperty getPropertyForNumber( const cVectorPosition & vecPoint,
		const unsigned int uiPropertyNumber = 0, const bool bEvenIfOutside = false ) const;
	
	/**
	 * This method returns the uiPropertyNumber'th property for the given image
	 * structure point.
	 * Antialising will be ignored. @see bIsAntialised
	 *
	 * @param point the point of which to return the property vector
	 * @param uiPropertyNumber the number of the property to return;
	 * 	counting starts with 1; @see getNumberOfProperties()
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( isStructurePoint() ) will be ignored (return cTypeProperty::NONE),
	 * 	 else it works as if the given point was included in this image structure
	 * @return the uiPropertyNumber'th property from the given point or the
	 * 	property of type cTypeProperty::NONE if non exists
	 */
	virtual cVectorProperty getPropertyForNumber(
		const pair< unsigned int, unsigned int> & point,
		const unsigned int uiPropertyNumber = 0, const bool bEvenIfOutside = false ) const;
	
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
	 * 	called with the point/position and the properties of the point;
	 * 	@see iEvaluePosition
	 * @return if the evaluation was successfull true, else false
	 */
	bool evalue( iEvaluePosition & evaluePosition ) const;
	
	
	/**
	 * This method checks if the given image structure is equal to this
	 * image structure.
	 *
	 * @param imageStructure the image structure, which should be equal to
	 * 	this image structure
	 * @return true if the given image structure is equal to this image
	 * 	structure, else false
	 */
	virtual bool equal( const cImageStructure &imageStructure ) const;

	/**
	 * This method checks if the given image structure is equal to this
	 * image structure.
	 *
	 * @param imageStructure the image structure, which should be equal to
	 * 	this image structure
	 * @return true if the given image structure is equal to this image
	 * 	structure, else false
	 */
	virtual bool operator==( const cImageStructure &imageStructure ) const;
	
	/**
	 * This method stores this image structure in the XML format into the
	 * given stream.
	 *
	 * @param ostream the stream where image structure should be stored to
	 * @return true if this image structure was stored, else false
	 */
	virtual bool storeXml( ostream & ostream ) const;
	
	/**
	 * This method restores image structure from the stream, where it is
	 * stored in the XML format.
	 *
	 * @pattern factory method
	 * @param stream the stream where the image structure is stored in
	 * @param pOutStatus A pointer to an integer value, where the error value
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
	static cImageStructure *restoreXml( istream &stream, intFib * pOutStatus=NULL );
	
	/**
	 * This method restores a image structure in the XML format from a
	 * TinyXml node element.
	 *
	 * @pattern Factory method
	 * @param pXmlNode a pointer to the TinyXml node, wher the image
	 * 	structure is stored in
	 * @param outStatus an intege rvalue with the error value
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
	static cImageStructure * restoreXmlNode( const TiXmlNode * pXmlNode,
		intFib & outStatus );

	/**
	 * This method restores a image structure from the stream, where it is
	 * stored in the XML format.
	 *
	 * @param stream the stream where the image structure is stored in
	 * @return an integer value with the error value
	 * 	possible error values are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 */
	virtual intFib restoreXml( istream &stream );
	
	/**
	 * This method restores a image structure in the XML format from a
	 * TinyXml element.
	 *
	 * @param pXmlElement a pointer to the TinyXml node wher the image
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
	virtual intFib restoreXml( const TiXmlElement * pXmlElement );
	
	
	//methods of iConvertImageStructureToFib
	
	/**
	 * This method is for converting the data of this object to a Fib object.
	 *
	 * @return a Fib-object which represents the data of this object
	 * 	Beware: You have to delete the returned Fib object after usage.
	 */
	virtual cRoot * convertToFib() const;
	
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
	 * @param ulMaxErrorPerPoint the maximal error for the border points to
	 * 	find on one border point; every point in the area of the generated
	 * 	Fib object will have a distance lower or equal ulMaxErrorPerPoint
	 * 	to a point in this structure or an overlappted point of pImageSearchData
	 * @return a Fib object which represents the data of this object
	 * 	Beware: You have to delete the returned Fib object after usage.
	 * 		Also the given root element will contain no domains, you have to
	 * 		create them if needed (eg. with cRoot::generateNeededDomains() ).
	 */
	virtual cRoot * convertToFib( const cImageSearchData * pImageSearchData,
		const double maxValue = 65536.0, const unsigned long ulMaxErrorPerPoint = 0.0 ) const;

protected:
	
	/**
	 * This function converts the given point into a cVectorPosition point.
	 *
	 * @param paPoint the point to convert
	 * @return a cVectorPosition object which represents the point
	 */
	static cVectorPosition convertToVectorPosition(
		const pair< unsigned int, unsigned int> & paPoint );
	
	/**
	 * This function converts the given points into cVectorPosition points.
	 *
	 * @param setPaPoint the set with the points to convert
	 * @return a set with the cVectorPosition objects, which represents the
	 * 	points in setPaPoint
	 */
	static set< cVectorPosition > convertToVectorPosition(
		const set< pair< unsigned int, unsigned int> > & setPaPoint );

	
	/**
	 * This function converts the given point into a pair point.
	 *
	 * @param vecPoint the point to convert
	 * @return a unsigned int pair which represents the point
	 */
	static pair< unsigned int, unsigned int> convertToVectorPair(
		const cVectorPosition & vecPoint );
	
	/**
	 * This function converts the given points into pair points.
	 *
	 * @param setVecPoint the set with the points to convert
	 * @return a set with the unsigned int pairs, which represents the
	 * 	points in setVecPoint
	 */
	static set< pair< unsigned int, unsigned int> > convertToVectorPair(
		const set< cVectorPosition > & setVecPoint );

};//class cImageStructure

};//end namespace nStructureData
};//end namespace nImage
};//end namespace nConvertToFib
};//end namespace algorithms
};//end namespace fib


#endif //___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__C_IMAGE_STRUCTURE_H__