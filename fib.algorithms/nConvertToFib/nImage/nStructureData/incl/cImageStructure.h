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


#ifndef ___C_IMAGE_STRUCTURE_H__
#define ___C_IMAGE_STRUCTURE_H__

#include "version.h"

#include "iConvertImageStructureToFib.h"
#include "cUseConvertAreaToExtObjectsStrategy.h"

#include "cVectorPosition.h"

#include "tinyxml.h"

#include "cFibSet.h"
#include "cList.h"
#include "cRoot.h"
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
	 * @param setInStructureBorderPoints the set with the points which are
	 * 	neighbours of points of the structure
	 */
	void setStructureNeighbourPoints( const set<cVectorPosition> & setInStructureNeighbourPoints );
	
	/**
	 * This method adds the given the given points to the structure.
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
	 * @param setInStructureBorderPoints the set with the points to add as
	 * 	the neighbours of points of the structure
	 */
	void addStructureNeighbourPoints( const set<cVectorPosition> & setInStructureNeighbourPoints );
	
	/**
	 * This method adds the given the given point to the structure.
	 *
	 * @see structurePoints
	 * @param setInStructurePoints the point to add to the structure
	 */
	void addStructurePoint( const cVectorPosition & pointInStructurePoint );
	
	/**
	 * This method adds the given point to the points which are in the
	 * structure, but have neighbour points, which are not in the structure.
	 *
	 * @see structureBorderPoints
	 * @param setInStructureBorderPoints the point which to add to the
	 * 	structure of points which have neighbour points, which are not in
	 * 	the structure
	 */
	void addStructureBorderPoint( const cVectorPosition & pointInStructureBorderPoint );
	
	/**
	 * This method adds the given point to the points, which are neighbours
	 * of points of the structure, but not in it.
	 *
	 * @see structureNeighbourPoints
	 * @param setInStructureBorderPoints the points to add to the
	 * 	neighbours of points of the structure
	 */
	void addStructureNeighbourPoint( const cVectorPosition & pointInStructureNeighbourPoint );
	
	
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
	 * @param setInStructureBorderPoints the set with the points to delete
	 * 	of the neighbours of points of the structure
	 */
	void deleteStructureNeighbourPoints( const set<cVectorPosition> & setInStructureNeighbourPoints );
	
	/**
	 * This method deletes the given the given point from the structure.
	 *
	 * @see structurePoints
	 * @param setInStructurePoints the point to delete from the structure
	 */
	void deleteStructurePoint( const cVectorPosition & pointInStructurePoint );
	
	/**
	 * This method deletes the given point from the points which are in the
	 * structure, but have neighbour points, which are not in the structure.
	 *
	 * @see structureBorderPoints
	 * @param setInStructureBorderPoints the point which to delete from the
	 * 	structure of points which have neighbour points, which are not in
	 * 	the structure
	 */
	void deleteStructureBorderPoint( const cVectorPosition & pointInStructureBorderPoint );
	
	/**
	 * This method deletes the given point from the points which are neighbours
	 * of points of the structure, but not in it.
	 *
	 * @see structureNeighbourPoints
	 * @param setInStructureBorderPoints the points to delete from the
	 * 	neighbours of points of the structure
	 */
	void deleteStructureNeighbourPoint( const cVectorPosition & pointInStructureNeighbourPoint );
	
	
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
	 * @param maxErrorPerValue the maximal error for the border points to
	 * 	find on one border point; every point in the area of the generated
	 * 	Fib object will have a distance lower or equal maxErrorPerValue
	 * 	to a point in this structure or an overlappted point of pImageSearchData
	 * @return a Fib object which represents the data of this object
	 * 	Beware: You have to delete the returned Fib object after usage.
	 * 		Also the given root element will contain no domains, you have to
	 * 		create them if needed (eg. with cRoot::generateNeededDomains() ).
	 */
	virtual cRoot * convertToFib( const cImageSearchData * pImageSearchData,
		const double maxValue = 65536.0, const unsigned long ulMaxErrorPerPoint = 0.0 ) const;
	
};//class cImageStructure

};//end namespace nStructureData
};//end namespace nImage
};//end namespace nConvertToFib
};//end namespace algorithms
};//end namespace fib


#endif //___C_IMAGE_STRUCTURE_H__