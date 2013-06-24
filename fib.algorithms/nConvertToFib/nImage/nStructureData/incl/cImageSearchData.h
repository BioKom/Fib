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
 * GNU General Public License for more details.
 *
 * This header specifies a class to store the data for a search on image data.
 * If you want to convert an image to Fib structures, you have to search
 * the image for structures, which can be converted to Fib.
 * To mark for which points structures wher found and which points you can
 * set to any overwritten property because the points are overwritten, you
 * can use this class.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * All positions vectors (cVectorPosition) elements should be positiv
 * integers from 0 to ulBorderX or ulBorderY respectively.
 *
 */
/*
History:
14.08.2012  Oesterholz  created
*/


#ifndef ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__C_IMAGE_SEARCH_DATA_H__
#define ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__C_IMAGE_SEARCH_DATA_H__

#include "version.h"

#include "iImageData.h"
#include "cVectorPosition.h"

#include <set>


using namespace std;


namespace fib{

namespace algorithms{

namespace nConvertToFib{

namespace nImage{

namespace nStructureData{

//cyclic dependencies
class cImageStructure;


class cImageSearchData{
protected:
	
	/**
	 * A pointer to the image data, of the image for the search.
	 */
	const iImageData * pImageData;
	
	/**
	 * The width of the image to search.
	 */
	unsigned long ulBorderX;
	
	/**
	 * The height of the image to search.
	 */
	unsigned long ulBorderY;
	
	/**
	 * The matrix with the data, which points of the image wher found (converted).
	 * The values are 1 bit: 0 for not found and 1 for found
	 *
	 * The pointer will point to an one dimensional array. You have to evalue
	 * the single entries by hand (with:
	 * 	*((pImageData + ((y * ulBorderX + x) / 8)) ) & ( 0x01 << (y * ulBorderX + x) % 8 ) )
	 * 		( x in dim 1 or ulBorderX, y in dim 2 or ulBorderY )
	 */
	unsigned char * pImageDataFound;
	
	/**
	 * The matrix with the data, which points of the image wher overlapped
	 * by found structures.
	 * The values are 1 bit: 0 for not overlapped and 1 for overlapped
	 *
	 * The pointer will point to an one dimensional array. You have to evalue
	 * the single entries by hand (with:
	 * 	*((pImageDataOverlapped + ((y * ulBorderX + x) / 8)) ) & ( 0x01 << (y * ulBorderX + x) % 8 ) )
	 * 		( x in dim 1 or ulBorderX, y in dim 2 or ulBorderY )
	 */
	unsigned char * pImageDataOverlapped;
	
	
public:
	
	/**
	 * parameter constructor
	 *
	 * @param ulInWidth the width of the image to search @see ulBorderX
	 * @param ulInHeight the height of the image to search @see ulBorderY
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
	 * copy constructor
	 *
	 * @param pInImageData pointer to the image search data to copy
	 */
	cImageSearchData( const cImageSearchData & imageSearchData );
	
	
	/**
	 * destructor
	 */
	~cImageSearchData();
	
	
	/**
	 * This method clones this object.
	 *
	 * @return a pointer to the clone of this object
	 */
	cImageSearchData * clone() const;
	
	/**
	 * Assigns the data of the given search structure to this class.
	 *
	 * @param imageSearchData the image search data which data to copy to this
	 * @return *this object
	 */
	cImageSearchData & operator=( const cImageSearchData & imageSearchData );
	
	/**
	 * @return the width of the image to search
	 * @see ulBorderX
	 */
	unsigned long getWidth() const;
	
	/**
	 * @return the height of the image to search
	 * @see ulBorderY
	 */
	unsigned long getHeight() const;
	
	/**
	 * This method checks if the given position is in the image search data.
	 *
	 * @param position the position to check
	 * @return true if the position is in the search data, else false
	 */
	bool isIn( const cVectorPosition & position ) const;
	
	/**
	 * This method checks if the given position is in the image search data.
	 *
	 * @param position the position to check
	 * @return true if the position is in the search data, else false
	 */
	bool isIn( const  pair< unsigned int, unsigned int> & position ) const;
	
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
	 * @see pImageDataFound
	 * @param lX the x / first dimension position of the point, for which to
	 * 	check, if it was found
	 * @param lY the y / second dimension position of the point, for which to
	 * 	check, if it was found
	 * @return true if the point on the position was found, else false
	 */
	bool isFound( const unsigned long lX, const unsigned long lY ) const;
	
	/**
	 * @see pImageDataOverlapped
	 * @param position the position of the point, for which to check, if it
	 * 	is overlapped
	 * @return true if the point on the position is overlapped, else false
	 */
	bool isOverlapped( const cVectorPosition& position ) const;
	
	/**
	 * @see pImageDataOverlapped
	 * @param lX the x / first dimension position of the point, for which to
	 * 	check, if it is overlapped
	  * @param lY the y / second dimension position of the point, for which to
	* 	check, if it is overlapped
	 * @return true if the point on the position is overlapped, else false
	 */
	bool isOverlapped( const unsigned long lX, const unsigned long lY ) const;
	
	/**
	 * @see pImageDataFound
	 * @see pImageDataOverlapped
	 * @param position the position of the point, for which to check, if it
	 * 	is found or overlapped
	 * @return true if the point on the position is found or overlapped, else false
	 */
	bool isFoundOrOverlapped( const cVectorPosition& position ) const;
	
	/**
	 * @see pImageDataFound
	 * @see pImageDataOverlapped
	 * @param lX the x / first dimension position of the point, for which to
	 * 	check, if it is found or overlapped
	 * @param lY the y / second dimension position of the point, for which to
	 * 	check, if it is found or overlapped
	 * @return true if the point on the position is found or overlapped, else false
	 */
	bool isFoundOrOverlapped( const unsigned long lX, const unsigned long lY ) const;
	
	/**
	 * @see pImageDataFound
	 * @see pImageDataOverlapped
	 * @param position the position of the point, for which to check, if it
	 * 	is found or overlapped
	 * @return true if the point on the position is found or overlapped, else false
	 */
	bool isFoundOrOverlapped( const pair< unsigned int, unsigned int> & position ) const;
	
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
	 * @see getFoundNeighbours()
	 * @see getOverlappedNeighbours()
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
	 * @see isFound()
	 * @see registerFound()
	 * @see isOverlapped()
	 * @see registerOverlapped()
	 * @param position the position of the point, for which to return the
	 * 	not found and not overlapped neighbour points
	 * @return a set of the not found and not overlapped neighbour points of
	 * 	the given point
	 * @see pImageDataFound
	 */
	set<cVectorPosition> getNotFoundNotOverlappedNeighbours(
		const cVectorPosition& position ) const;
	
	/**
	 * @see isFound()
	 * @see registerFound()
	 * @see isOverlapped()
	 * @see registerOverlapped()
	 * @param position the position of the point, for which to return if it
	 * 	has not found and not overlapped neighbour points
	 * @return true if the given point has not found and not overlapped
	 * 	neighbour points
	 * @see pImageDataFound
	 */
	bool hasNotFoundNotOverlappedNeighbours(
		const cVectorPosition& position ) const;
	
	
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
	 * @return the number of points, which wher (/not) registered as found
	 */
	unsigned long registerFound( const set<cVectorPosition> & setFoundPoints,
		const bool bFound=true );
	
	/**
	 * This method registers the points of the given image structure as
	 * found or not found points.
	 *
	 * @see pImageDataFound
	 * @see isFound()
	 * @see getFoundNeighbours()
	 * @see cImageStructure
	 * @param pImageStrFoundPoints the cImageStructure with the points to
	 * 	register (/set) as (/not) found points
	 * @param bFound if true the points will be registered as found, else
	 * 	the points will be registered as not found
	 * @return the number of points, which wher (/not) registered as found
	 */
	unsigned long registerFound( const cImageStructure * pImageStrFoundPoints,
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
	 * @return the number of points, which wher (/not) registered as overlapped
	 */
	unsigned long registerOverlapped( const set<cVectorPosition> & setOverlappedPoints,
		const bool bOverlapped=true );
	
	/**
	 * This method registers the points of the given image structure as
	 * overlapped or not overlapped points.
	 *
	 * @see pImageDataOverlapped
	 * @see isOverlapped()
	 * @see getOverlappedNeighbours()
	 * @see cImageStructure
	 * @param pImageStrOverlappedPoints the cImageStructure with the points to
	 * 	register (/set) as (/not) overlapped points
	 * @param bOverlapped if true the points will be registered as overlapped,
	 * 	else the points will be registered as not overlapped
	 * @return the number of points, which wher (/not) registered as overlapped
	 */
	unsigned long registerOverlapped( const cImageStructure * pImageStrOverlappedPoints,
		const bool bOverlapped=true );
	
	
	/**
	 * Converts all found points to overlapped points.
	 * The points marked as found won't change.
	 * If you start a new layer, wich is below the layers of the found points,
	 * call this method.
	 */
	void foundToOverlapped();
	
	/**
	 * Set all points to not found.
	 */
	void clearFound();
	
	/**
	 * Set all points to not overlapped.
	 */
	void clearOverlapped();
	
	
//methods for points given as unsigned int pairs:
	
	/**
	 * @see pImageDataFound
	 * @param position the position of the point, for which to check, if it
	 * 	was found
	 * @return true if the point on the position was found, else false
	 */
	bool isFound( const pair< unsigned int, unsigned int> & position ) const;
	
	/**
	 * @see pImageDataOverlapped
	 * @param position the position of the point, for which to check, if it
	 * 	is overlapped
	 * @return true if the point on the position is overlapped, else false
	 */
	bool isOverlapped( const pair< unsigned int, unsigned int> & position ) const;
	
	/**
	 * @see isFound()
	 * @see registerFound()
	 * @return a set of all found points in the image
	 * @see pImageDataFound
	 */
	set< pair< unsigned int, unsigned int> > getFoundPointsAsPair() const;
	
	/**
	 * @see isFound()
	 * @see registerFound()
	 * @return a set of all not found points in the image
	 * @see pImageDataFound
	 */
	set< pair< unsigned int, unsigned int> > getNotFoundPointsAsPair() const;
	
	/**
	 * @see isOverlapped()
	 * @see registerOverlapped()
	 * @return a set of all overlapped points in the image
	 * @see pImageDataOverlapped
	 */
	set< pair< unsigned int, unsigned int> > getOverlappedPointsAsPair() const;
	
	/**
	 * @see isOverlapped()
	 * @see registerOverlapped()
	 * @return a set of all not overlapped points in the image
	 * @see pImageDataOverlapped
	 */
	set< pair< unsigned int, unsigned int> > getNotOverlappedPointsAsPair() const;
	
	
	/**
	 * @see getFoundNeighbours()
	 * @see getOverlappedNeighbours()
	 * @param position the position of the point, for which to return the
	 * 	neighbour points
	 * @return a set of the neighbour points of the given point
	 */
	set< pair< unsigned int, unsigned int> > getNeighbours(
		const pair< unsigned int, unsigned int> & position ) const;
	
	/**
	 * @see isFound()
	 * @see registerFound()
	 * @param position the position of the point, for which to return the
	 * 	found neighbour points
	 * @return a set of the found neighbour points of the given point
	 * @see pImageDataFound
	 */
	set< pair< unsigned int, unsigned int> > getFoundNeighbours(
		const pair< unsigned int, unsigned int>  & position ) const;
	
	/**
	 * @see isFound()
	 * @see registerFound()
	 * @param position the position of the point, for which to return the
	 * 	not found neighbour points
	 * @return a set of the not found neighbour points of the given point
	 * @see pImageDataFound
	 */
	set< pair< unsigned int, unsigned int> > getNotFoundNeighbours(
		const pair< unsigned int, unsigned int> & position ) const;
	
	/**
	 * @see isOverlapped()
	 * @see registerOverlapped()
	 * @param position the position of the point, for which to return the
	 * 	overlapped neighbour points
	 * @return a set of the overlapped neighbour points of the given point
	 * @see pImageDataOverlapped
	 */
	set< pair< unsigned int, unsigned int> > getOverlappedNeighbours(
		const pair< unsigned int, unsigned int> & position ) const;
	
	/**
	 * @see isOverlapped()
	 * @see registerOverlapped()
	 * @param position the position of the point, for which to return the
	 * 	not overlapped neighbour points
	 * @return a set of the not overlapped neighbour points of the given point
	 * @see pImageDataOverlapped
	 */
	set< pair< unsigned int, unsigned int> > getNotOverlappedNeighbours(
		const pair< unsigned int, unsigned int> & position ) const;
	
	/**
	 * @see isFound()
	 * @see registerFound()
	 * @see isOverlapped()
	 * @see registerOverlapped()
	 * @param position the position of the point, for which to return the
	 * 	not found and not overlapped neighbour points
	 * @return a set of the not found and not overlapped neighbour points of
	 * 	the given point
	 * @see pImageDataFound
	 */
	set< pair< unsigned int, unsigned int> > getNotFoundNotOverlappedNeighbours(
		const pair< unsigned int, unsigned int> & position ) const;
	
	/**
	 * @see isFound()
	 * @see registerFound()
	 * @see isOverlapped()
	 * @see registerOverlapped()
	 * @param position the position of the point, for which to return if it
	 * 	has not found and not overlapped neighbour points
	 * @return true if the given point has not found and not overlapped
	 * 	neighbour points
	 * @see pImageDataFound
	 */
	bool hasNotFoundNotOverlappedNeighbours(
		const pair< unsigned int, unsigned int> & position ) const;
	
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
	bool registerFound( const pair< unsigned int, unsigned int> & foundPoint,
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
	 * @return the number of points, which wher (/not) registered as found
	 */
	unsigned long registerFound(
		const set< pair< unsigned int, unsigned int> > & setFoundPoints,
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
	bool registerOverlapped( const pair< unsigned int, unsigned int> & overlappedPoint,
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
	 * @return the number of points, which wher (/not) registered as overlapped
	 */
	unsigned long registerOverlapped(
		const set< pair< unsigned int, unsigned int> > & setOverlappedPoints,
		const bool bOverlapped=true );
	
	
};//class cImageSearchData


};//end namespace nStructureData
};//end namespace nImage
};//end namespace nConvertToFib
};//end namespace algorithms
};//end namespace fib


#endif //___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__C_IMAGE_SEARCH_DATA_H__
