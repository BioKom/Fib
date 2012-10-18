/**
 * @file cImageSearchData
 * file name: cImageSearchData.h
 * @author Betti Oesterholz
 * @date 14.08.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class to store the data for a search on image data.
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
 * This header specifies a class to store the data for a search on image data.
 * If you want to convert an image to Fib structures, you have to search
 * the image for structures, which can be converted to Fib.
 * To mark for which points structures wher found and which points you can
 * set to any overwritten property because the points are overwritten, you
 * can use this class.
 *
 * All positions vectors (cVectorPosition) elements should be positiv
 * integers from 0 to ulWidth or ulHeight respectively.
 *
 */
/*
History:
14.08.2012  Oesterholz  created
*/


#ifndef ___C_IMAGE_SEARCH_DATA_H__
#define ___C_IMAGE_SEARCH_DATA_H__

#include "version.h"

#include "iImageData.h"
#include "cImageStructure.h"
#include "cVectorPosition.h"

#include <set>


using namespace std::set;


namespace fib{

namespace algorithms{

namespace nConvertToFib{

namespace nImage{


class cImageSearchData{
protected:
	
	/**
	 * A pointer to the image data, of the image for the search.
	 */
	const iImageData * pImageData;
	
	/**
	 * The width of the image to search.
	 */
	unsigned long ulWidth;
	
	/**
	 * The height of the image to search.
	 */
	unsigned long ulHeight;
	
	/**
	 * The matrix with the data, which points of the image wher found (converted).
	 * The values are 1 bit: 0 for not found and 1 for found
	 *
	 * The pointer will point to an one dimensional array. You have to evalue
	 * the single entries by hand (with:
	 * 	*((pImageData + ((y * ulWidth + x) / 8)) ) & ( 0x01 << (y * ulWidth + x) % 8 ) )
	 * 		( x in dim 1 or ulWidth, y in dim 2 or ulHeight )
	 */
	unsigned char * pImageDataFound;
	
	/**
	 * The matrix with the data, which points of the image wher overlapped
	 * by found structures.
	 * The values are 1 bit: 0 for not overlapped and 1 for overlapped
	 *
	 * The pointer will point to an one dimensional array. You have to evalue
	 * the single entries by hand (with:
	 * 	*((pImageDataOverlapped + ((y * ulWidth + x) / 8)) ) & ( 0x01 << (y * ulWidth + x) % 8 ) )
	 * 		( x in dim 1 or ulWidth, y in dim 2 or ulHeight )
	 */
	unsigned char * pImageDataOverlapped;
	
	

public:
	

	/**
	 * parameter constructor
	 *
	 * @param ulInWidth the width of the image to search @see ulWidth
	 * @param ulInHeight the height of the image to search @see ulHeight
	 */
	cImageSearchData( const unsigned long ulInWidth, const unsigned long ulInHeight );

	/**
	 * parameter constructor
	 *
	 * @param pInImageData pointer to the image data, of the image to convert
	 * 	@see pImageData
	 */
	cImageSearchData( const iImageData * pInImageData );
	
	
	/**
	 * destructor
	 */
	~cImageSearchData();
	
	
	/**
	 * @return the width of the image to search
	 * @see ulWidth
	 */
	unsigned long getWidth() const;
	
	/**
	 * @return the height of the image to search
	 * @see ulHeight
	 */
	unsigned long getHeight() const;
	
	/**
	 * @return a pointer to the image data, of the image for the search
	 * @see pImageData
	 */
	const iImageData * getImageData() const;
	
	
	/**
	 * @see pImageDataFound
	 * @param position the position of the point, for which to check, if it
	 * 	was found
	 * @return true if the point on the position was found, else false
	 */
	bool isFound( const cVectorPosition& position ) const;
	
	/**
	 * @see pImageDataOverlapped
	 * @param position the position of the point, for which to check, if it
	 * 	is overlapped
	 * @return true if the point on the position is overlapped, else false
	 */
	bool isOverlapped( const cVectorPosition& position ) const;
	
	
	/**
	 * @see isFound()
	 * @see registerFound()
	 * @return a set of all found points in the image
	 * @see pImageDataFound
	 */
	set<cVectorPosition> getFoundPoints() const;
	
	/**
	 * @see isFound()
	 * @see registerFound()
	 * @return a set of all not found points in the image
	 * @see pImageDataFound
	 */
	set<cVectorPosition> getNotFoundPoints() const;
	
	/**
	 * @see isOverlapped()
	 * @see registerOverlapped()
	 * @return a set of all overlapped points in the image
	 * @see pImageDataOverlapped
	 */
	set<cVectorPosition> getOverlappedPoints() const;
	
	/**
	 * @see isOverlapped()
	 * @see registerOverlapped()
	 * @return a set of all not overlapped points in the image
	 * @see pImageDataOverlapped
	 */
	set<cVectorPosition> getNotOverlappedPoints() const;
	
	
	/**
	 * @see registerFound()
	 * @see getFoundNeighbours()
	 * @param position the position of the point, for which to return the
	 * 	neighbour points
	 * @return a set of the neighbour points of the given point
	 */
	set<cVectorPosition> getNeighbours( const cVectorPosition& position ) const;
	
	/**
	 * @see isFound()
	 * @see registerFound()
	 * @param position the position of the point, for which to return the
	 * 	found neighbour points
	 * @return a set of the found neighbour points of the given point
	 * @see pImageDataFound
	 */
	set<cVectorPosition> getFoundNeighbours( const cVectorPosition& position ) const;
	
	/**
	 * @see isFound()
	 * @see registerFound()
	 * @param position the position of the point, for which to return the
	 * 	not found neighbour points
	 * @return a set of the not found neighbour points of the given point
	 * @see pImageDataFound
	 */
	set<cVectorPosition> getNotFoundNeighbours( const cVectorPosition& position ) const;
	
	/**
	 * @see isOverlapped()
	 * @see registerOverlapped()
	 * @param position the position of the point, for which to return the
	 * 	overlapped neighbour points
	 * @return a set of the overlapped neighbour points of the given point
	 * @see pImageDataOverlapped
	 */
	set<cVectorPosition> getOverlappedNeighbours( const cVectorPosition& position ) const;
	
	/**
	 * @see isOverlapped()
	 * @see registerOverlapped()
	 * @param position the position of the point, for which to return the
	 * 	not overlapped neighbour points
	 * @return a set of the not overlapped neighbour points of the given point
	 * @see pImageDataOverlapped
	 */
	set<cVectorPosition> getNotOverlappedNeighbours( const cVectorPosition& position ) const;
	
	
	/**
	 * This method registers the given point as found or not found point.
	 *
	 * @see pImageDataFound
	 * @see isFound()
	 * @see getFoundNeighbours()
	 * @param foundPoint the point to register (/set) as (/not) found point
	 * @param bFound if true the point will be registered as found, else
	 * 	the point will be registered as not found
	 * @return true if the point wher (/not) registered as found, else false
	 */
	bool registerFound( const cVectorPosition & foundPoint,
		const bool bFound=true );

	/**
	 * This method registers the given points as found or not found points.
	 *
	 * @see pImageDataFound
	 * @see isFound()
	 * @see getFoundNeighbours()
	 * @param setFoundPoints a set with the points to register (/set) as
	 * 	(/not) found points
	 * @param bFound if true the points will be registered as found, else
	 * 	the points will be registered as not found
	 * @return true if the points wher (/not) registered as found,
	 * 	else false and no data changed
	 */
	bool registerFound( const set<cVectorPosition> & setFoundPoints,
		const bool bFound=true );
	
	/**
	 * This method registers the points of the given image structure as
	 * found or not found points.
	 *
	 * @see pImageDataFound
	 * @see isFound()
	 * @see getFoundNeighbours()
	 * @see cImageStructure
	 * @param imageStrFoundPoints the cImageStructure with the points to
	 * 	register (/set) as (/not) found points
	 * @param bFound if true the points will be registered as found, else
	 * 	the points will be registered as not found
	 * @return true if the points wher (/not) registered as found,
	 * 	else false and no data changed
	 */
	bool registerFound( const cImageStructure * imageStrFoundPoints,
		const bool bFound=true );
	
	/**
	 * This method registers the given point as overlapped or not overlapped
	 * point.
	 *
	 * @see pImageDataOverlapped
	 * @see isOverlapped()
	 * @see getOverlappedNeighbours()
	 * @param overlappedPoint the point to register (/set) as (/not) overlapped point
	 * @param bOverlapped if true the point will be registered as overlapped,
	 * 	else the point will be registered as not overlapped
	 * @return true if the point wher (/not) registered as overlapped, else false
	 */
	bool registerOverlapped( const cVectorPosition & overlappedPoint,
		const bool bOverlapped=true );

	/**
	 * This method registers the given points as overlapped or not overlapped points.
	 *
	 * @see pImageDataOverlapped
	 * @see isOverlapped()
	 * @see getOverlappedNeighbours()
	 * @param setOverlappedPoints a set with the points to register (/set) as
	 * 	(/not) overlapped points
	 * @param bOverlapped if true the points will be registered as overlapped,
	 * 	else the points will be registered as not overlapped
	 * @return true if the points wher (/not) registered as overlapped,
	 * 	else false and no data changed
	 */
	bool registerOverlapped( const set<cVectorPosition> & setOverlappedPoints,
		const bool bOverlapped=true );
	
	/**
	 * This method registers the points of the given image structure as
	 * overlapped or not overlapped points.
	 *
	 * @see pImageDataOverlapped
	 * @see isOverlapped()
	 * @see getOverlappedNeighbours()
	 * @see cImageStructure
	 * @param imageStrOverlappedPoints the cImageStructure with the points to
	 * 	register (/set) as (/not) overlapped points
	 * @param bOverlapped if true the points will be registered as overlapped,
	 * 	else the points will be registered as not overlapped
	 * @return true if the points wher (/not) registered as overlapped,
	 * 	else false and no data changed
	 */
	bool registerOverlapped( const cImageStructure * imageStrOverlappedPoints,
		const bool bOverlapped=true );
	
	
	/**
	 * Converts all found points to overlapped points.
	 * If you start a new layer, wich is below the layers of the found points,
	 * call this method.
	 */
	void foundToOverlapped();
	
	
};//class cImageSearchData


};//end namespace nImage
};//end namespace nConvertToFib
};//end namespace algorithms
};//end namespace fib


#endif //___C_IMAGE_SEARCH_DATA_H__
