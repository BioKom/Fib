/**
 * @file cImageSearchData
 * file name: cImageSearchData.cpp
 * @author Betti Oesterholz
 * @date 14.08.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements a class to store the data for a search on image data.
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
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This file implements a class to store the data for a search on image data.
 * If you want to convert an image to Fib structures, you have to search
 * the image for structures, which can be converted to Fib.
 * To mark for which points structures wher found and which points you can
 * set to any overwritten property because the points are overwritten, you
 * can use this class.
 *
 * All positions vectors (cVectorPosition) elements should be positiv
 * integers from 0 to ulBorderX or ulBorderY respectively.
 *
 */
/*
History:
14.08.2012  Oesterholz  created
*/

//switches for debugging proposes
//#define DEBUG


#include "cImageSearchData.h"

#include "cImageStructure.h"

#include "cDomains.h"
#include "cDomain.h"
#include "cDomainIntegerBasis.h"

#include <string>


using namespace std;

using namespace fib::algorithms::nConvertToFib::nImage::nStructureData;
using namespace fib;


/**
 * parameter constructor
 *
 * @param ulInWidth the width of the image to search @see ulBorderX
 * @param ulInHeight the height of the image to search @see ulBorderY
 */
cImageSearchData::cImageSearchData( const unsigned long ulInWidth,
		const unsigned long ulInHeight ): pImageData( NULL ),
		ulBorderX( ulInWidth ), ulBorderY( ulInHeight ){
	
	//init arrays
	const unsigned long ulBytsNeeded = ( ulBorderX * ulBorderY ) / 8 + 1;
	
	pImageDataFound = (unsigned char*)malloc( ulBytsNeeded );
	memset( pImageDataFound, 0x0, ulBytsNeeded );
	pImageDataOverlapped = (unsigned char*)malloc( ulBytsNeeded );
	memset( pImageDataOverlapped, 0x0, ulBytsNeeded );
}


/**
 * parameter constructor
 *
 * @param pInImageData pointer to the image data, of the image to convert
 * 	@see pImageData
 */
cImageSearchData::cImageSearchData( const iImageData * pInImageData ):
		pImageData( pInImageData ){
	
	if ( pInImageData == NULL ){
		//Error: no image data given
		pImageDataFound = NULL;
		pImageDataOverlapped = NULL;
		ulBorderX = 0;
		ulBorderY = 0;
		return;
	}
	//evalue width and height
	const cDomains domsPosition = pImageData->getPositionDomain();
	
	const cDomain * pDomPosition = domsPosition.getDomain( 1 );
	if ( ( pDomPosition == NULL ) || ( ! pDomPosition->isVector() ) ||
			( ((const cDomainVectorBasis*)(pDomPosition))->getNumberOfElements() != 2 ) ){
		//Error: no image data given
		pImageDataFound = NULL;
		pImageDataOverlapped = NULL;
		ulBorderX = 0;
		ulBorderY = 0;
		return;
	}
	const cDomainVectorBasis * pVecDomPosition =
		(const cDomainVectorBasis*)(pDomPosition);
	
	const cDomain * pDomPositionDim1 = pVecDomPosition->getElementDomain( 1 );
	const cDomain * pDomPositionDim2 = pVecDomPosition->getElementDomain( 2 );

	if ( ( pDomPositionDim1 == NULL ) || ( ! pDomPositionDim1->isScalar() ) ||
			( pDomPositionDim2 == NULL ) || ( ! pDomPositionDim2->isScalar() ) ){
		//Error: no image data given
		pImageDataFound = NULL;
		pImageDataOverlapped = NULL;
		ulBorderX = 0;
		ulBorderY = 0;
		return;
	}
	
	const string szDomainTypePositionDim1 = pDomPositionDim1->getType();
	const string szDomainTypePositionDim2 = pDomPositionDim2->getType();
	
	if ( ( ( szDomainTypePositionDim1.compare( 0, 19, "DomainNaturalNumber") != 0 ) &&
			( szDomainTypePositionDim1.compare( 0, 13, "DomainInteger") != 0 ) ) ||
			( ( szDomainTypePositionDim2.compare( 0, 19, "DomainNaturalNumber") != 0 ) &&
			( szDomainTypePositionDim2.compare( 0, 13, "DomainInteger") != 0 )) ){
		//Error: no image data given
		pImageDataFound = NULL;
		pImageDataOverlapped = NULL;
		ulBorderX = 0;
		ulBorderY = 0;
		return;
	}
	
	ulBorderX = (unsigned long)(
		((const cDomainIntegerBasis*)pDomPositionDim1)->getMaximumUnscaled() -
			((const cDomainIntegerBasis*)pDomPositionDim1)->getMinimumUnscaled()) + 1;
	ulBorderY = (unsigned long)(
		((const cDomainIntegerBasis*)pDomPositionDim2)->getMaximumUnscaled() -
			((const cDomainIntegerBasis*)pDomPositionDim2)->getMinimumUnscaled()) + 1;
	
	//init arrays
	const unsigned long ulBytsNeeded = ( ulBorderX * ulBorderY ) / 8 + 1;
	
	pImageDataFound = (unsigned char*)malloc( ulBytsNeeded );
	memset( pImageDataFound, 0x0, ulBytsNeeded );
	pImageDataOverlapped = (unsigned char*)malloc( ulBytsNeeded );
	memset( pImageDataOverlapped, 0x0, ulBytsNeeded );
}


/**
 * copy constructor
 *
 * @param pInImageData pointer to the image search data to copy
 */
cImageSearchData::cImageSearchData( const cImageSearchData & imageSearchData ):
		pImageData( imageSearchData.pImageData ),
		ulBorderX( imageSearchData.ulBorderX ),
		ulBorderY( imageSearchData.ulBorderY ){
	
	//init arrays
	const unsigned long ulBytsNeeded = ( ulBorderX * ulBorderY ) / 8 + 1;
	
	pImageDataFound = (unsigned char*)malloc( ulBytsNeeded );
	memcpy( pImageDataFound, imageSearchData.pImageDataFound, ulBytsNeeded );
	
	pImageDataOverlapped = (unsigned char*)malloc( ulBytsNeeded );
	memcpy( pImageDataOverlapped, imageSearchData.pImageDataOverlapped, ulBytsNeeded );
}


/**
 * destructor
 */
cImageSearchData::~cImageSearchData(){
	
	if ( pImageDataFound != NULL ){
		free( pImageDataFound );
	}
	if ( pImageDataOverlapped != NULL ){
		free( pImageDataOverlapped );
	}
}


/**
 * This method clones this object.
 *
 * @return a pointer to the clone of this object
 */
cImageSearchData * cImageSearchData::clone() const{
	
	return new cImageSearchData( *this );
}


/**
 * Assigns the data of the given search structure to this class.
 *
 * @param imageSearchData the image search data which data to copy to this
 * @return *this object
 */
cImageSearchData & cImageSearchData::operator=(
		const cImageSearchData & imageSearchData ){
	
	
	if ( pImageDataFound != NULL ){
		free( pImageDataFound );
	}
	if ( pImageDataOverlapped != NULL ){
		free( pImageDataOverlapped );
	}
	pImageData = imageSearchData.pImageData;
	ulBorderX  = imageSearchData.ulBorderX;
	ulBorderY  = imageSearchData.ulBorderY;
	
	//init arrays
	const unsigned long ulBytsNeeded = ( ulBorderX * ulBorderY ) / 8 + 1;
	
	pImageDataFound = (unsigned char*)malloc( ulBytsNeeded );
	memcpy( pImageDataFound, imageSearchData.pImageDataFound, ulBytsNeeded );
	
	pImageDataOverlapped = (unsigned char*)malloc( ulBytsNeeded );
	memcpy( pImageDataOverlapped, imageSearchData.pImageDataOverlapped, ulBytsNeeded );
	
	return (*this);
}


/**
 * @return the width of the image to search
 * @see ulBorderX
 */
unsigned long cImageSearchData::getWidth() const{
	
	return ulBorderX;
}


/**
 * @return the height of the image to search
 * @see ulBorderY
 */
unsigned long cImageSearchData::getHeight() const{
	
	return ulBorderY;
}


/**
 * @return a pointer to the image data, of the image for the search, or
 * 	NULL if non such exists
 * @see pImageData
 */
const iImageData * cImageSearchData::getImageData() const{
	
	return pImageData;
}


/**
 * This method checks if the given position is in the image search data.
 *
 * @param position the position to check
 * @return true if the position is in the search data, else false
 */
bool cImageSearchData::isIn( const cVectorPosition & position ) const{
	
	const long lX = roundToLongFib( position.getValue( 1 ) );
	const long lY = roundToLongFib( position.getValue( 2 ) );
	
	if (  ( lX < 0 ) || ( ((long)ulBorderX) <= lX ) ||
			( lY < 0 ) || ( ((long)ulBorderY) <= lY ) ){
		//point not existing
		return false;
	}
	return true;
}


/**
 * This method checks if the given position is in the image search data.
 *
 * @param position the position to check
 * @return true if the position is in the search data, else false
 */
bool cImageSearchData::isIn( const pair< unsigned int, unsigned int> & position ) const{
	
	if (  ( ulBorderX <= position.first ) ||
			( ulBorderY <= position.second ) ){
		//point not existing
		return false;
	}
	return true;
}


/**
 * @see pImageDataFound
 * @param position the position of the point, for which to check, if it
 * 	was found
 * @return true if the point on the position was found, else false
 */
bool cImageSearchData::isFound( const cVectorPosition& position ) const{
	
	const long lX = roundToLongFib( position.getValue( 1 ) );
	const long lY = roundToLongFib( position.getValue( 2 ) );
	
	if ( ( lX < 0 ) || ( ((long)ulBorderX) <= lX ) ||
			( lY < 0 ) || ( ((long)ulBorderY) <= lY ) ){
		//point not existing -> point not found
		return false;
	}
	
	const unsigned long ulPosition = lY * ulBorderX + lX;
	
	return ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
		( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 );
}


/**
 * @see pImageDataOverlapped
 * @param lX the x / first dimension position of the point, for which to
 * 	check, if it was found
 * @param lY the y / second dimension position of the point, for which to
 * 	check, if it was found
 * @return true if the point on the position was found, else false
 */
bool cImageSearchData::isFound( const unsigned long lX,
		const unsigned long lY ) const{
	
	if ( ( ulBorderX <= lX ) || ( ulBorderY <= lY ) ){
		//point not existing -> point not overlapped
		return false;
	}
	
	const unsigned long ulPosition = lY * ulBorderX + lX;
	
	return ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
		( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 );
}


/**
 * @see pImageDataOverlapped
 * @param position the position of the point, for which to check, if it
 * 	is overlapped
 * @return true if the point on the position is overlapped, else false
 */
bool cImageSearchData::isOverlapped( const cVectorPosition& position ) const{
	
	const long lX = roundToLongFib( position.getValue( 1 ) );
	const long lY = roundToLongFib( position.getValue( 2 ) );
	
	if ( ( lX < 0 ) || ( ((long)ulBorderX) <= lX ) ||
			( lY < 0 ) || ( ((long)ulBorderY) <= lY ) ){
		//point not existing -> point not overlapped
		return false;
	}
	
	const unsigned long ulPosition = lY * ulBorderX + lX;
	
	return ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
		( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 );
}


/**
 * @see pImageDataOverlapped
 * @param lX the x / first dimension position of the point, for which to
 * 	check, if it is overlapped
 * @param lY the y / second dimension position of the point, for which to
 * 	check, if it is overlapped
 * @return true if the point on the position is overlapped, else false
 */
bool cImageSearchData::isOverlapped( const unsigned long lX,
		const unsigned long lY ) const{
	
	if ( ( ulBorderX <= lX ) || ( ulBorderY <= lY ) ){
		//point not existing -> point not overlapped
		return false;
	}
	
	const unsigned long ulPosition = lY * ulBorderX + lX;
	
	return ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
		( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 );
}


/**
 * @see pImageDataOverlapped
 * @param position the position of the point, for which to check, if it
 * 	is found or overlapped
 * @return true if the point on the position is found or overlapped, else false
 */
bool cImageSearchData::isFoundOrOverlapped( const cVectorPosition& position ) const{
	
	const long lX = roundToLongFib( position.getValue( 1 ) );
	const long lY = roundToLongFib( position.getValue( 2 ) );
	
	if ( ( lX < 0 ) || ( ((long)ulBorderX) <= lX ) ||
			( lY < 0 ) || ( ((long)ulBorderY) <= lY ) ){
		//point not existing -> point not found
		return false;
	}
	
	const unsigned long ulPosition  = lY * ulBorderX + lX;
	const unsigned int uiByteOffset = ulPosition / 8;
	const unsigned char ucBitMask   = 0x01 << (ulPosition % 8);
	
	return ( ( *((pImageDataFound + uiByteOffset ) ) & ucBitMask ) != 0x0 ) ||
		( ( *((pImageDataOverlapped + uiByteOffset ) ) & ucBitMask ) != 0x0 );
}


/**
 * @see pImageDataFound
 * @see pImageDataOverlapped
 * @param lX the x / first dimension position of the point, for which to
 * 	check, if it is found or overlapped
 * @param lY the y / second dimension position of the point, for which to
 * 	check, if it is found or overlapped
 * @return true if the point on the position is found or overlapped, else false
 */
bool cImageSearchData::isFoundOrOverlapped(
		const unsigned long lX, const unsigned long lY ) const{
	
	if ( ( ulBorderX <= lX ) || ( ulBorderY <= lY ) ){
		//point not existing -> point not overlapped
		return false;
	}
	
	const unsigned long ulPosition  = lY * ulBorderX + lX;
	const unsigned int uiByteOffset = ulPosition / 8;
	const unsigned char ucBitMask   = 0x01 << (ulPosition % 8);
	
	return ( ( *((pImageDataFound + uiByteOffset ) ) & ucBitMask ) != 0x0 ) ||
		( ( *((pImageDataOverlapped + uiByteOffset ) ) & ucBitMask ) != 0x0 );
}


/**
 * @see pImageDataOverlapped
 * @param position the position of the point, for which to check, if it
 * 	is found or overlapped
 * @return true if the point on the position is found or overlapped, else false
 */
bool cImageSearchData::isFoundOrOverlapped(
		const pair< unsigned int, unsigned int> & position ) const{
	
	const unsigned int & uiX = position.first;
	const unsigned int & uiY = position.second;
	
	if ( ( ulBorderX <= uiX ) || ( ulBorderY <= uiY ) ){
		//point not existing -> point not overlapped
		return false;
	}
	
	const unsigned long ulPosition  = uiY * ulBorderX + uiX;
	const unsigned int uiByteOffset = ulPosition / 8;
	const unsigned char ucBitMask   = 0x01 << (ulPosition % 8);
	
	return ( ( *((pImageDataFound + uiByteOffset ) ) & ucBitMask ) != 0x0 ) ||
		( ( *((pImageDataOverlapped + uiByteOffset ) ) & ucBitMask ) != 0x0 );
}


/**
 * @see isFound()
 * @see registerFound()
 * @return a set of all found points in the image
 * @see pImageDataFound
 */
set<cVectorPosition> cImageSearchData::getFoundPoints() const{
	
	unsigned long ulPosition = 0;
	cVectorPosition vectorPosition( 2 );
	set<cVectorPosition> setFoundPositionsVector;
	//check all found array positions
	for ( unsigned long lY = 0; lY < ulBorderY; lY++ ){
		
		for ( unsigned long lX = 0; lX < ulBorderX; lX++, ulPosition++ ){
			
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 ){
				//point was found -> add it to found points
				vectorPosition.setValue( 1, lX );
				vectorPosition.setValue( 2, lY );
				setFoundPositionsVector.insert( vectorPosition );
			}
		}
	}
	return setFoundPositionsVector;
}


/**
 * @see isFound()
 * @see registerFound()
 * @return a set of all not found points in the image
 * @see pImageDataFound
 */
set<cVectorPosition> cImageSearchData::getNotFoundPoints() const{
	
	unsigned long ulPosition = 0;
	cVectorPosition vectorPosition( 2 );
	set<cVectorPosition> setNotFoundPositionsVector;
	//check all found array positions
	for ( unsigned long lY = 0; lY < ulBorderY; lY++ ){
		
		for ( unsigned long lX = 0; lX < ulBorderX; lX++, ulPosition++ ){
			
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ){
				//point was not found -> add it to not found points
				vectorPosition.setValue( 1, lX );
				vectorPosition.setValue( 2, lY );
				setNotFoundPositionsVector.insert( vectorPosition );
			}
		}
	}
	return setNotFoundPositionsVector;
}


/**
 * @see isOverlapped()
 * @see registerOverlapped()
 * @return a set of all overlapped points in the image
 * @see pImageDataOverlapped
 */
set<cVectorPosition> cImageSearchData::getOverlappedPoints() const{
	
	unsigned long ulPosition = 0;
	cVectorPosition vectorPosition( 2 );
	set<cVectorPosition> setOverlappedPositionsVector;
	//check all found array positions
	for ( unsigned long lY = 0; lY < ulBorderY; lY++ ){
		
		for ( unsigned long lX = 0; lX < ulBorderX; lX++, ulPosition++ ){
			
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 ){
				//point was overlapped -> add it to overlapped points
				vectorPosition.setValue( 1, lX );
				vectorPosition.setValue( 2, lY );
				setOverlappedPositionsVector.insert( vectorPosition );
			}
		}
	}
	return setOverlappedPositionsVector;
}


/**
 * @see isOverlapped()
 * @see registerOverlapped()
 * @return a set of all not overlapped points in the image
 * @see pImageDataOverlapped
 */
set<cVectorPosition> cImageSearchData::getNotOverlappedPoints() const{
	
	unsigned long ulPosition = 0;
	cVectorPosition vectorPosition( 2 );
	set<cVectorPosition> setNotOverlappedPositionsVector;
	//check all found array positions
	for ( unsigned long lY = 0; lY < ulBorderY; lY++ ){
		
		for ( unsigned long lX = 0; lX < ulBorderX; lX++, ulPosition++ ){
			
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ){
				//point was not overlapped -> add it to not overlapped points
				vectorPosition.setValue( 1, lX );
				vectorPosition.setValue( 2, lY );
				setNotOverlappedPositionsVector.insert( vectorPosition );
			}
		}
	}
	return setNotOverlappedPositionsVector;
}


/**
 * @see getFoundNeighbours()
 * @see getOverlappedNeighbours()
 * @param position the position of the point, for which to return the
 * 	neighbour points
 * @return a set of the neighbour points of the given point
 */
set<cVectorPosition> cImageSearchData::getNeighbours( const cVectorPosition& position ) const{
	
	const long lX = roundToLongFib( position.getValue( 1 ) );
	const long lY = roundToLongFib( position.getValue( 2 ) );
	
	set<cVectorPosition> setNeighboursPositionsVector;
	cVectorPosition vectorPosition( 2 );
	//evalue the four neighbours
	if ( ( 0 <= lY ) && ( lY < ((long)ulBorderY) ) ){
		//inside y area
		if ( ( 0 < lX ) && ( lX <= ((long)ulBorderX) ) ){
			vectorPosition.setValue( 1, lX - 1 );
			vectorPosition.setValue( 2, lY );
			setNeighboursPositionsVector.insert( vectorPosition );
		}
		if ( ( 0 <= lX ) && ( ( lX + 1 ) < ((long)ulBorderX) ) ){
			vectorPosition.setValue( 1, lX + 1 );
			vectorPosition.setValue( 2, lY );
			setNeighboursPositionsVector.insert( vectorPosition );
		}
	}
	if ( ( 0 <= lX ) && ( lX < ((long)ulBorderX) ) ){
		//inside x area
		if ( ( 0 < lY ) && ( lY <= ((long)ulBorderY) ) ){
			vectorPosition.setValue( 1, lX  );
			vectorPosition.setValue( 2, lY - 1 );
			setNeighboursPositionsVector.insert( vectorPosition );
		}
		if ( ( 0 <= lY ) && ( ( lY + 1 ) < ((long)ulBorderY) ) ){
			vectorPosition.setValue( 1, lX  );
			vectorPosition.setValue( 2, lY + 1 );
			setNeighboursPositionsVector.insert( vectorPosition );
		}
	}
	
	return setNeighboursPositionsVector;
}


/**
 * @see isFound()
 * @see registerFound()
 * @param position the position of the point, for which to return the
 * 	found neighbour points
 * @return a set of the found neighbour points of the given point
 * @see pImageDataFound
 */
set<cVectorPosition> cImageSearchData::getFoundNeighbours(
		const cVectorPosition& position ) const{
	
	const long lX = roundToLongFib( position.getValue( 1 ) );
	const long lY = roundToLongFib( position.getValue( 2 ) );
	
	set<cVectorPosition> setNeighboursPositionsVector;
	
	cVectorPosition vectorPosition( 2 );
	
	//evalue the four neighbours
	if ( ( 0 <= lY ) && ( lY < ((long)ulBorderY) ) ){
		//inside y area
		if ( ( 0 < lX ) && ( lX <= ((long)ulBorderX) ) ){
			//check if the point was found
			const unsigned long ulPosition = lY * ulBorderX + lX - 1;
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 ){
				vectorPosition.setValue( 1, lX - 1 );
				vectorPosition.setValue( 2, lY );
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
		if ( ( 0 <= lX ) && ( ( lX + 1 ) < ((long)ulBorderX) ) ){
			//check if the point was found
			const unsigned long ulPosition = lY * ulBorderX + lX + 1;
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 ){
				vectorPosition.setValue( 1, lX + 1 );
				vectorPosition.setValue( 2, lY );
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
	}
	if ( ( 0 <= lX ) && ( lX < ((long)ulBorderX) ) ){
		//inside x area
		if ( ( 0 < lY ) && ( lY <= ((long)ulBorderY) ) ){
			//check if the point was found
			const unsigned long ulPosition = ( lY - 1 ) * ulBorderX + lX;
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 ){
				vectorPosition.setValue( 1, lX  );
				vectorPosition.setValue( 2, lY - 1 );
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
		if ( ( 0 <= lY ) && ( ( lY + 1 ) < ((long)ulBorderY) ) ){
			//check if the point was found
			const unsigned long ulPosition = ( lY + 1 ) * ulBorderX + lX;
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 ){
				vectorPosition.setValue( 1, lX );
				vectorPosition.setValue( 2, lY + 1 );
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
	}
	
	return setNeighboursPositionsVector;
}


/**
 * @see isFound()
 * @see registerFound()
 * @param position the position of the point, for which to return the
 * 	not found neighbour points
 * @return a set of the not found neighbour points of the given point
 * @see pImageDataFound
 */
set<cVectorPosition> cImageSearchData::getNotFoundNeighbours(
		const cVectorPosition& position ) const{
	
	const long lX = roundToLongFib( position.getValue( 1 ) );
	const long lY = roundToLongFib( position.getValue( 2 ) );
	
	set<cVectorPosition> setNeighboursPositionsVector;
	cVectorPosition vectorPosition( 2 );
	
	//evalue the four neighbours
	if ( ( 0 <= lY ) && ( lY < ((long)ulBorderY) ) ){
		//inside y area
		if ( ( 0 < lX ) && ( lX <= ((long)ulBorderX) ) ){
			//check if the point was not found
			const unsigned long ulPosition = lY * ulBorderX + lX - 1;
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ){
				vectorPosition.setValue( 1, lX - 1 );
				vectorPosition.setValue( 2, lY );
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
		if ( ( 0 <= lX ) && ( ( lX + 1 ) < ((long)ulBorderX) ) ){
			//check if the point was not found
			const unsigned long ulPosition = lY * ulBorderX + lX + 1;
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ){
				vectorPosition.setValue( 1, lX + 1 );
				vectorPosition.setValue( 2, lY );
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
	}
	if ( ( 0 <= lX ) && ( lX < ((long)ulBorderX) ) ){
		//inside x area
		if ( ( 0 < lY ) && ( lY <= ((long)ulBorderY) ) ){
			//check if the point was not found
			const unsigned long ulPosition = ( lY - 1 ) * ulBorderX + lX;
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ){
				vectorPosition.setValue( 1, lX  );
				vectorPosition.setValue( 2, lY - 1 );
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
		if  ( ( 0 <= lY ) && ( ( lY + 1 ) < ((long)ulBorderY) ) ){
			//check if the point was not found
			const unsigned long ulPosition = ( lY + 1 ) * ulBorderX + lX;
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ){
				vectorPosition.setValue( 1, lX );
				vectorPosition.setValue( 2, lY + 1 );
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
	}
	return setNeighboursPositionsVector;
}


/**
 * @see isOverlapped()
 * @see registerOverlapped()
 * @param position the position of the point, for which to return the
 * 	overlapped neighbour points
 * @return a set of the overlapped neighbour points of the given point
 * @see pImageDataOverlapped
 */
set<cVectorPosition> cImageSearchData::getOverlappedNeighbours(
		const cVectorPosition& position ) const{
	
	const long lX = roundToLongFib( position.getValue( 1 ) );
	const long lY = roundToLongFib( position.getValue( 2 ) );
	
	set<cVectorPosition> setNeighboursPositionsVector;
	cVectorPosition vectorPosition( 2 );
	
	//evalue the four neighbours
	if ( ( 0 <= lY ) && ( lY < ((long)ulBorderY) ) ){
		//inside y area
		if ( ( 0 < lX ) && ( lX <= ((long)ulBorderX) ) ){
			//check if the point was overlapped
			const unsigned long ulPosition = lY * ulBorderX + lX - 1;
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 ){
				vectorPosition.setValue( 1, lX - 1 );
				vectorPosition.setValue( 2, lY );
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
		if ( ( 0 <= lX ) && ( ( lX + 1 ) < ((long)ulBorderX) ) ){
			//check if the point was overlapped
			const unsigned long ulPosition = lY * ulBorderX + lX + 1;
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 ){
				vectorPosition.setValue( 1, lX + 1 );
				vectorPosition.setValue( 2, lY );
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
	}
	if ( ( 0 <= lX ) && ( lX < ((long)ulBorderX) ) ){
		//inside x area
		if ( ( 0 < lY ) && ( lY <= ((long)ulBorderY) ) ){
			//check if the point was overlapped
			const unsigned long ulPosition = ( lY - 1 ) * ulBorderX + lX;
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 ){
				vectorPosition.setValue( 1, lX  );
				vectorPosition.setValue( 2, lY - 1 );
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
		if ( ( 0 <= lY ) && ( ( lY + 1 ) < ((long)ulBorderY) ) ){
			//check if the point was overlapped
			const unsigned long ulPosition = ( lY + 1 ) * ulBorderX + lX;
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 ){
				vectorPosition.setValue( 1, lX );
				vectorPosition.setValue( 2, lY + 1 );
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
	}
	return setNeighboursPositionsVector;
}


/**
 * @see isOverlapped()
 * @see registerOverlapped()
 * @param position the position of the point, for which to return the
 * 	not overlapped neighbour points
 * @return a set of the not overlapped neighbour points of the given point
 * @see pImageDataOverlapped
 */
set<cVectorPosition> cImageSearchData::getNotOverlappedNeighbours(
		const cVectorPosition& position ) const{
	
	const long lX = roundToLongFib( position.getValue( 1 ) );
	const long lY = roundToLongFib( position.getValue( 2 ) );
	
	set<cVectorPosition> setNeighboursPositionsVector;
	cVectorPosition vectorPosition( 2 );
	
	//evalue the four neighbours
	if ( ( 0 <= lY ) && ( lY < ((long)ulBorderY) ) ){
		//inside y area
		if ( ( 0 < lX ) && ( lX <= ((long)ulBorderX) ) ){
			//check if the point was not overlapped
			const unsigned long ulPosition = lY * ulBorderX + lX - 1;
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ){
				vectorPosition.setValue( 1, lX - 1 );
				vectorPosition.setValue( 2, lY );
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
		if ( ( 0 <= lX ) && ( ( lX + 1 ) < ((long)ulBorderX) ) ){
			//check if the point was not overlapped
			const unsigned long ulPosition = lY * ulBorderX + lX + 1;
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ){
				vectorPosition.setValue( 1, lX + 1 );
				vectorPosition.setValue( 2, lY );
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
	}
	if ( ( 0 <= lX ) && ( lX < ((long)ulBorderX) ) ){
		//inside x area
		if ( ( 0 < lY ) && ( lY <= ((long)ulBorderY) ) ){
			//check if the point was not overlapped
			const unsigned long ulPosition = ( lY - 1 ) * ulBorderX + lX;
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ){
				vectorPosition.setValue( 1, lX );
				vectorPosition.setValue( 2, lY - 1 );
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
		if ( ( 0 <= lY ) && ( ( lY + 1 ) < ((long)ulBorderY) ) ){
			//check if the point was not overlapped
			const unsigned long ulPosition = ( lY + 1 ) * ulBorderX + lX;
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ){
				vectorPosition.setValue( 1, lX );
				vectorPosition.setValue( 2, lY + 1 );
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
	}
	
	return setNeighboursPositionsVector;
}


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
set<cVectorPosition> cImageSearchData::getNotFoundNotOverlappedNeighbours(
		const cVectorPosition& position ) const{
	
	const long lX = roundToLongFib( position.getValue( 1 ) );
	const long lY = roundToLongFib( position.getValue( 2 ) );
	
	set<cVectorPosition> setNeighboursPositionsVector;
	cVectorPosition vectorPosition( 2 );
	
	//evalue the four neighbours
	if ( ( 0 <= lY ) && ( lY < ((long)ulBorderY) ) ){
		//inside y area
		if ( ( 0 < lX ) && ( lX <= ((long)ulBorderX) ) ){
			//check if the point was not overlapped
			const unsigned long ulPosition = lY * ulBorderX + lX - 1;
			if ( ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) &&
					( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
						( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) ){
				vectorPosition.setValue( 1, lX - 1 );
				vectorPosition.setValue( 2, lY );
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
		if ( ( 0 <= lX ) && ( ( lX + 1 ) < ((long)ulBorderX) ) ){
			//check if the point was not overlapped
			const unsigned long ulPosition = lY * ulBorderX + lX + 1;
			if ( ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) &&
					( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
						( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) ){
				vectorPosition.setValue( 1, lX + 1 );
				vectorPosition.setValue( 2, lY );
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
	}
	if ( ( 0 <= lX ) && ( lX < ((long)ulBorderX) ) ){
		//inside x area
		if ( ( 0 < lY ) && ( lY <= ((long)ulBorderY) ) ){
			//check if the point was not overlapped
			const unsigned long ulPosition = ( lY - 1 ) * ulBorderX + lX;
			if ( ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) &&
					( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
						( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) ){
				vectorPosition.setValue( 1, lX );
				vectorPosition.setValue( 2, lY - 1 );
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
		if ( ( 0 <= lY ) && ( ( lY + 1 ) < ((long)ulBorderY) ) ){
			//check if the point was not overlapped
			const unsigned long ulPosition = ( lY + 1 ) * ulBorderX + lX;
			if ( ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) &&
					( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
						( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) ){
				vectorPosition.setValue( 1, lX );
				vectorPosition.setValue( 2, lY + 1 );
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
	}
	return setNeighboursPositionsVector;
}


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
bool cImageSearchData::hasNotFoundNotOverlappedNeighbours(
		const cVectorPosition& position ) const{
	
	const long lX = roundToLongFib( position.getValue( 1 ) );
	const long lY = roundToLongFib( position.getValue( 2 ) );
	
	//evalue the four neighbours
	if ( ( 0 <= lY ) && ( lY < ((long)ulBorderY) ) ){
		//inside y area
		if ( ( 0 < lX ) && ( lX <= ((long)ulBorderX) ) ){
			//check if the point was not overlapped
			const unsigned long ulPosition = lY * ulBorderX + lX - 1;
			if ( ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) &&
					( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
						( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) ){
				return true;
			}
		}
		if ( ( 0 <= lX ) && ( ( lX + 1 ) < ((long)ulBorderX) ) ){
			//check if the point was not overlapped
			const unsigned long ulPosition = lY * ulBorderX + lX + 1;
			if ( ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) &&
					( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
						( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) ){
				return true;
			}
		}
	}
	if ( ( 0 <= lX ) && ( lX < ((long)ulBorderX) ) ){
		//inside x area
		if ( ( 0 < lY ) && ( lY <= ((long)ulBorderY) ) ){
			//check if the point was not overlapped
			const unsigned long ulPosition = ( lY - 1 ) * ulBorderX + lX;
			if ( ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) &&
					( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
						( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) ){
				return true;
			}
		}
		if ( ( 0 <= lY ) && ( ( lY + 1 ) < ((long)ulBorderY) ) ){
			//check if the point was not overlapped
			const unsigned long ulPosition = ( lY + 1 ) * ulBorderX + lX;
			if ( ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) &&
					( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
						( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) ){
				return true;
			}
		}
	}
	return false;
}


/**
 * This method registers the given point as found or not found point.
 *
 * @see pImageDataFound
 * @see isFound()
 * @see getFoundNeighbours()
 * @param foundPoint the point to register (/set) as (/not) found point
 * @param bFound if true the point will be registered as found, else
 * 	the point will be registered as not found
 * @return true if the point wher (/not) registered as found,
 * 	else false and no data changed
 */
bool cImageSearchData::registerFound(
		const cVectorPosition & foundPoint, const bool bFound ){
	
	const long lX = roundToLongFib( foundPoint.getValue( 1 ) );
	const long lY = roundToLongFib( foundPoint.getValue( 2 ) );
	
	DEBUG_OUT_L2(<<"cImageSearchData("<<this<<")::registerFound( foundPoint=("<<lX<<", "<<lY<<"), bFound="<<(bFound?"true":"false")<<" ) started"<<endl<<flush);
	
	if ( ( lX < 0 ) || ( ((long)ulBorderX) <= lX ) ||
			( lY < 0 ) || ( ((long)ulBorderY) <= lY ) ){
		//point not existing -> points not found
		return false;
	}
	
	const unsigned long ulPosition = lY * ulBorderX + lX;
	
	unsigned char * pByte = ( pImageDataFound + ( ulPosition / 8 ) );
	
	if ( bFound ){
		//register point as found
		(*pByte) |= ( 0x01 << (ulPosition % 8) );
	}else{//register point as not found
		(*pByte) &= ~( 0x01 << (ulPosition % 8) );
	}
	return true;
}


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
unsigned long cImageSearchData::registerFound(
		const set<cVectorPosition> & setFoundPoints, const bool bFound ){
	
	unsigned long ulRegisteredPoints = 0;
	DEBUG_OUT_L2(<<"cImageSearchData("<<this<<")::registerFound( #setFoundPoints=("<<setFoundPoints.size()<<"), bFound="<<(bFound?"true":"false")<<" ) started points:"<<flush);
	
	for ( set<cVectorPosition>::iterator itrFoundPoint = setFoundPoints.begin();
			itrFoundPoint != setFoundPoints.end(); itrFoundPoint++ ){
		
		const long lX = roundToLongFib( itrFoundPoint->getValue( 1 ) );
		const long lY = roundToLongFib( itrFoundPoint->getValue( 2 ) );
		
		DEBUG_OUT_L2(<<" ("<<lX<<", "<<lY<<");"<<flush);
	
		if ( ( 0 <= lX ) && ( lX < ((long)ulBorderX) ) &&
				( 0 <= lY ) && ( lY < ((long)ulBorderY) ) ){
			
			const unsigned long ulPosition = lY * ulBorderX + lX;
			
			unsigned char * pByte = ( pImageDataFound + ( ulPosition / 8 ) );
			
			if ( bFound ){
				//register point as found
				(*pByte) |= ( 0x01 << ( ulPosition % 8 ) );
			}else{//register point as not found
				(*pByte) &= ~( 0x01 << ( ulPosition % 8 ) );
			}
			ulRegisteredPoints++;
		}
	}
	DEBUG_OUT_L2(<<endl<<flush);
	return ulRegisteredPoints;
}


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
unsigned long cImageSearchData::registerFound(
		const cImageStructure * pImageStrFoundPoints, const bool bFound ){
	
	return registerFound( pImageStrFoundPoints->getStructurePointsConst(), bFound );
}


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
 * @return true if the point wher (/not) registered as overlapped,
 * 	else false and no data changed
 */
bool cImageSearchData::registerOverlapped(
		const cVectorPosition & overlappedPoint, const bool bOverlapped ){
	
	const long lX = roundToLongFib( overlappedPoint.getValue( 1 ) );
	const long lY = roundToLongFib( overlappedPoint.getValue( 2 ) );
	
	if ( ( lX < 0 ) || ( ((long)ulBorderX) <= lX ) ||
			( lY < 0 ) || ( ((long)ulBorderY) <= lY ) ){
		//point not existing -> points not overlapped
		return false;
	}
	
	const unsigned long ulPosition = lY * ulBorderX + lX;
	
	unsigned char * pByte = ( pImageDataOverlapped + ( ulPosition / 8 ) );
	
	if ( bOverlapped ){
		//register point as overlapped
		(*pByte) |= ( 0x01 << ( ulPosition % 8 ) );
	}else{//register point as not overlapped
		(*pByte) &= ~( 0x01 << ( ulPosition % 8 ) );
	}
	return true;
}


/**
 * This method registers the given points as overlapped or not overlapped
 * points.
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
unsigned long cImageSearchData::registerOverlapped(
		const set<cVectorPosition> & setOverlappedPoints, const bool bOverlapped ){
	
	DEBUG_OUT_L4(<<"cImageSearchData("<<this<<")::registerOverlapped( setOverlappedPoints, bOverlapped="<<(bOverlapped?"true":"false")<<" ) started"<<endl<<flush);
	
	unsigned long ulRegisteredPoints = 0;
	
	for ( set<cVectorPosition>::iterator itrOverlappedPoint = setOverlappedPoints.begin();
			itrOverlappedPoint != setOverlappedPoints.end(); itrOverlappedPoint++ ){
		
		const long lX = roundToLongFib( itrOverlappedPoint->getValue( 1 ) );
		const long lY = roundToLongFib( itrOverlappedPoint->getValue( 2 ) );
		
		if ( ( 0 <= lX ) && ( lX < ((long)ulBorderX) ) &&
				( 0 <= lY ) && ( lY < ((long)ulBorderY) ) ){
			
			const unsigned long ulPosition = lY * ulBorderX + lX;
			
			unsigned char * pByte = ( pImageDataOverlapped + ( ulPosition / 8 ) );
			
			DEBUG_OUT_L4(<<"register point ("<<lX<<", "<<lY<<") on position "<<ulPosition<< " for the "<<(ulPosition / 8)<<" byte (image ulBorderX="<<ulBorderX<<" ulBorderY="<<ulBorderY<<")"<<endl<<flush);
			
			if ( bOverlapped ){
				//register point as overlapped
				(*pByte) |= ( 0x01 << ( ulPosition % 8 ) );
			}else{//register point as not overlapped
				(*pByte) &= ~( 0x01 << ( ulPosition % 8 ) );
			}
			ulRegisteredPoints++;
		}
	}
	return ulRegisteredPoints;
}


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
unsigned long cImageSearchData::registerOverlapped(
		const cImageStructure * pImageStrOverlappedPoints, const bool bOverlapped ){
	
	return registerOverlapped( pImageStrOverlappedPoints->getStructurePointsConst(),
		bOverlapped );
}


/**
 * Converts all found points to overlapped points.
 * The points marked as found won't change.
 * If you start a new layer, wich is below the layers of the found points,
 * call this method.
 */
void cImageSearchData::foundToOverlapped(){
	
	DEBUG_OUT_L2(<<"cImageSearchData("<<this<<")::foundToOverlapped() started"<<endl<<flush);
	const unsigned long ulBytsInArrays = ( ulBorderX * ulBorderY ) / 8 + 1;
	
	unsigned char * pTmpImageDataOverlapped = pImageDataOverlapped;
	unsigned char * pTmpImageDataFound = pImageDataFound;
	
	for ( unsigned long ulActualByte = 0; ulActualByte < ulBytsInArrays;
			ulActualByte++, pTmpImageDataOverlapped++, pTmpImageDataFound++ ){
		
		(*pTmpImageDataOverlapped) |= (*pTmpImageDataFound);
	}
}


/**
 * Set all points to not found.
 */
void cImageSearchData::clearFound(){
	
	DEBUG_OUT_L2(<<"cImageSearchData("<<this<<")::clearFound() started"<<endl<<flush);
	const unsigned long ulBytsNeeded = ( ulBorderX * ulBorderY ) / 8 + 1;
	memset( pImageDataFound, 0x0, ulBytsNeeded );
}


/**
 * Set all points to not overlapped.
 */
void cImageSearchData::clearOverlapped(){
	
	DEBUG_OUT_L2(<<"cImageSearchData("<<this<<")::clearOverlapped() started"<<endl<<flush);
	const unsigned long ulBytsNeeded = ( ulBorderX * ulBorderY ) / 8 + 1;
	memset( pImageDataOverlapped, 0x0, ulBytsNeeded );
}



//methods for points given as unsigned int pairs:

/**
 * @see pImageDataFound
 * @param position the position of the point, for which to check, if it
 * 	was found
 * @return true if the point on the position was found, else false
 */
bool cImageSearchData::isFound(
		const pair< unsigned int, unsigned int> & position ) const{
	
	const unsigned long ulX = position.first;
	const unsigned long ulY = position.second;
	
	if ( ( ulBorderX <= ulX ) || ( ulBorderY <= ulY ) ){
		//point not existing -> point not found
		return false;
	}
	const unsigned long ulPosition = ulY * ulBorderX + ulX;
	
	return ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
		( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 );
}


/**
 * @see pImageDataOverlapped
 * @param position the position of the point, for which to check, if it
 * 	is overlapped
 * @return true if the point on the position is overlapped, else false
 */
bool cImageSearchData::isOverlapped(
		const pair< unsigned int, unsigned int> & position ) const{
	
	const unsigned long ulX = position.first;
	const unsigned long ulY = position.second;
	
	if ( ( ulBorderX <= ulX ) || ( ulBorderY <= ulY ) ){
		//point not existing -> point not overlapped
		return false;
	}
	
	const unsigned long ulPosition = ulY * ulBorderX + ulX;
	
	return ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
		( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 );
}


/**
 * @see isFound()
 * @see registerFound()
 * @return a set of all found points in the image
 * @see pImageDataFound
 */
set< pair< unsigned int, unsigned int> > cImageSearchData::getFoundPointsAsPair() const{
	
	unsigned long ulPosition = 0;
	pair< unsigned int, unsigned int> vectorPosition;
	set< pair< unsigned int, unsigned int> > setFoundPositionsVector;
	//check all found array positions
	for ( unsigned long ulY = 0; ulY < ulBorderY; ulY++ ){
		
		for ( unsigned long ulX = 0; ulX < ulBorderX; ulX++, ulPosition++ ){
			
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 ){
				//point was found -> add it to found points
				vectorPosition.first  = ulX;
				vectorPosition.second = ulY;
				setFoundPositionsVector.insert( vectorPosition );
			}
		}
	}
	return setFoundPositionsVector;
}


/**
 * @see isFound()
 * @see registerFound()
 * @return a set of all not found points in the image
 * @see pImageDataFound
 */
set< pair< unsigned int, unsigned int> > cImageSearchData::getNotFoundPointsAsPair() const{
	
	unsigned long ulPosition = 0;
	pair< unsigned int, unsigned int> vectorPosition;
	set< pair< unsigned int, unsigned int> > setNotFoundPositionsVector;
	//check all found array positions
	for ( unsigned long ulY = 0; ulY < ulBorderY; ulY++ ){
		
		for ( unsigned long ulX = 0; ulX < ulBorderX; ulX++, ulPosition++ ){
			
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ){
				//point was not found -> add it to not found points
				vectorPosition.first  = ulX;
				vectorPosition.second = ulY;
				setNotFoundPositionsVector.insert( vectorPosition );
			}
		}
	}
	return setNotFoundPositionsVector;
}


/**
 * @see isOverlapped()
 * @see registerOverlapped()
 * @return a set of all overlapped points in the image
 * @see pImageDataOverlapped
 */
set< pair< unsigned int, unsigned int> > cImageSearchData::getOverlappedPointsAsPair() const{
	
	unsigned long ulPosition = 0;
	pair< unsigned int, unsigned int> vectorPosition;
	set< pair< unsigned int, unsigned int> > setOverlappedPositionsVector;
	//check all found array positions
	for ( unsigned long ulY = 0; ulY < ulBorderY; ulY++ ){
		
		for ( unsigned long ulX = 0; ulX < ulBorderX; ulX++, ulPosition++ ){
			
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 ){
				//point was overlapped -> add it to overlapped points
				vectorPosition.first  = ulX;
				vectorPosition.second = ulY;
				setOverlappedPositionsVector.insert( vectorPosition );
			}
		}
	}
	return setOverlappedPositionsVector;
}


/**
 * @see isOverlapped()
 * @see registerOverlapped()
 * @return a set of all not overlapped points in the image
 * @see pImageDataOverlapped
 */
set< pair< unsigned int, unsigned int> > cImageSearchData::getNotOverlappedPointsAsPair() const{
	
	unsigned long ulPosition = 0;
	pair< unsigned int, unsigned int> vectorPosition;
	set< pair< unsigned int, unsigned int> > setNotOverlappedPositionsVector;
	//check all found array positions
	for ( unsigned long ulY = 0; ulY < ulBorderY; ulY++ ){
		
		for ( unsigned long ulX = 0; ulX < ulBorderX; ulX++, ulPosition++ ){
			
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ){
				//point was not overlapped -> add it to not overlapped points
				vectorPosition.first  = ulX;
				vectorPosition.second = ulY;
				setNotOverlappedPositionsVector.insert( vectorPosition );
			}
		}
	}
	return setNotOverlappedPositionsVector;
}


/**
 * @see getFoundNeighbours()
 * @see getOverlappedNeighbours()
 * @param position the position of the point, for which to return the
 * 	neighbour points
 * @return a set of the neighbour points of the given point
 */
set< pair< unsigned int, unsigned int> > cImageSearchData::getNeighbours(
		const pair< unsigned int, unsigned int> & position ) const{
	
	const unsigned long ulX = position.first;
	const unsigned long ulY = position.second;
	
	set< pair< unsigned int, unsigned int> > setNeighboursPositionsVector;
	pair< unsigned int, unsigned int> vectorPosition;
	//evalue the four neighbours
	if ( ulY < ulBorderY ){
		//inside y area
		if ( ( 0 < ulX ) && ( ulX <= ulBorderX ) ){
			vectorPosition.first  = ulX - 1;
			vectorPosition.second = ulY;
			setNeighboursPositionsVector.insert( vectorPosition );
		}
		if ( ( ulX + 1 ) < ulBorderX ){
			vectorPosition.first   = ulX + 1;
			vectorPosition.second  = ulY;
			setNeighboursPositionsVector.insert( vectorPosition );
		}
	}
	if ( ulX < ulBorderX ){
		//inside x area
		if ( ( 0 < ulY ) && ( ulY <= ulBorderY ) ){
			vectorPosition.first   = ulX;
			vectorPosition.second  = ulY - 1;
			setNeighboursPositionsVector.insert( vectorPosition );
		}
		if ( ( ulY + 1 ) < ulBorderY ){
			vectorPosition.first   = ulX;
			vectorPosition.second  = ulY + 1;
			setNeighboursPositionsVector.insert( vectorPosition );
		}
	}
	return setNeighboursPositionsVector;
}


/**
 * @see isFound()
 * @see registerFound()
 * @param position the position of the point, for which to return the
 * 	found neighbour points
 * @return a set of the found neighbour points of the given point
 * @see pImageDataFound
 */
set< pair< unsigned int, unsigned int> > cImageSearchData::getFoundNeighbours(
		const pair< unsigned int, unsigned int>  & position ) const{
	
	const unsigned long ulX = position.first;
	const unsigned long ulY = position.second;
	
	set< pair< unsigned int, unsigned int> > setNeighboursPositionsVector;
	pair< unsigned int, unsigned int> vectorPosition;
	
	//evalue the four neighbours
	if ( ulY < ulBorderY ){
		//inside y area
		if ( ( 0 < ulX ) && ( ulX <= ulBorderX ) ){
			//check if the point was found
			const unsigned long ulPosition = ulY * ulBorderX + ulX - 1;
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 ){
				vectorPosition.first  = ulX - 1;
				vectorPosition.second = ulY;
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
		if ( ( ulX + 1 ) < ulBorderX ){
			//check if the point was found
			const unsigned long ulPosition = ulY * ulBorderX + ulX + 1;
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 ){
				vectorPosition.first  = ulX + 1;
				vectorPosition.second = ulY;
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
	}
	if ( ulX < ulBorderX ){
		//inside x area
		if ( ( 0 < ulY ) && ( ulY <= ulBorderY ) ){
			//check if the point was found
			const unsigned long ulPosition = ( ulY - 1 ) * ulBorderX + ulX;
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 ){
				vectorPosition.first  = ulX;
				vectorPosition.second = ulY - 1;
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
		if ( ( ulY + 1 ) < ulBorderY ){
			//check if the point was found
			const unsigned long ulPosition = ( ulY + 1 ) * ulBorderX + ulX;
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 ){
				vectorPosition.first  = ulX;
				vectorPosition.second = ulY + 1;
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
	}
	return setNeighboursPositionsVector;
}


/**
 * @see isFound()
 * @see registerFound()
 * @param position the position of the point, for which to return the
 * 	not found neighbour points
 * @return a set of the not found neighbour points of the given point
 * @see pImageDataFound
 */
set< pair< unsigned int, unsigned int> > cImageSearchData::getNotFoundNeighbours(
		const pair< unsigned int, unsigned int> & position ) const{
	
	const unsigned long ulX = position.first;
	const unsigned long ulY = position.second;
	
	set< pair< unsigned int, unsigned int> > setNeighboursPositionsVector;
	pair< unsigned int, unsigned int> vectorPosition;
	
	//evalue the four neighbours
	if ( ulY < ulBorderY ){
		//inside y area
		if ( ( 0 < ulX ) && ( ulX <= ulBorderX ) ){
			//check if the point was not found
			const unsigned long ulPosition = ulY * ulBorderX + ulX - 1;
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ){
				vectorPosition.first  = ulX - 1;
				vectorPosition.second = ulY;
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
		if ( ( ulX + 1 ) < ulBorderX ){
			//check if the point was not found
			const unsigned long ulPosition = ulY * ulBorderX + ulX + 1;
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ){
				vectorPosition.first  = ulX + 1;
				vectorPosition.second = ulY;
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
	}
	if ( ulX < ulBorderX ){
		//inside x area
		if ( ( 0 < ulY ) && ( ulY <= ulBorderY ) ){
			//check if the point was not found
			const unsigned long ulPosition = ( ulY - 1 ) * ulBorderX + ulX;
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ){
				vectorPosition.first  = ulX;
				vectorPosition.second = ulY - 1;
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
		if  ( ( ulY + 1 ) < ulBorderY ){
			//check if the point was not found
			const unsigned long ulPosition = ( ulY + 1 ) * ulBorderX + ulX;
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ){
				vectorPosition.first  = ulX;
				vectorPosition.second = ulY + 1;
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
	}
	return setNeighboursPositionsVector;
}


/**
 * @see isOverlapped()
 * @see registerOverlapped()
 * @param position the position of the point, for which to return the
 * 	overlapped neighbour points
 * @return a set of the overlapped neighbour points of the given point
 * @see pImageDataOverlapped
 */
set< pair< unsigned int, unsigned int> > cImageSearchData::getOverlappedNeighbours(
		const pair< unsigned int, unsigned int> & position ) const{
	
	const unsigned long ulX = position.first;
	const unsigned long ulY = position.second;
	
	set< pair< unsigned int, unsigned int> > setNeighboursPositionsVector;
	pair< unsigned int, unsigned int> vectorPosition;
	
	//evalue the four neighbours
	if ( ulY < ulBorderY ){
		//inside y area
		if ( ( 0 < ulX ) && ( ulX <= ulBorderX ) ){
			//check if the point was overlapped
			const unsigned long ulPosition = ulY * ulBorderX + ulX - 1;
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 ){
				vectorPosition.first  = ulX - 1;
				vectorPosition.second = ulY;
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
		if ( ( ulX + 1 ) < ulBorderX ){
			//check if the point was overlapped
			const unsigned long ulPosition = ulY * ulBorderX + ulX + 1;
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 ){
				vectorPosition.first  = ulX + 1;
				vectorPosition.second = ulY;
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
	}
	if ( ulX < ulBorderX ){
		//inside x area
		if ( ( 0 < ulY ) && ( ulY <= ulBorderY ) ){
			//check if the point was overlapped
			const unsigned long ulPosition = ( ulY - 1 ) * ulBorderX + ulX;
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 ){
				vectorPosition.first  = ulX;
				vectorPosition.second = ulY - 1;
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
		if ( ( ulY + 1 ) < ulBorderY ){
			//check if the point was overlapped
			const unsigned long ulPosition = ( ulY + 1 ) * ulBorderX + ulX;
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) != 0x0 ){
				vectorPosition.first  = ulX;
				vectorPosition.second = ulY + 1;
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
	}
	return setNeighboursPositionsVector;
}


/**
 * @see isOverlapped()
 * @see registerOverlapped()
 * @param position the position of the point, for which to return the
 * 	not overlapped neighbour points
 * @return a set of the not overlapped neighbour points of the given point
 * @see pImageDataOverlapped
 */
set< pair< unsigned int, unsigned int> > cImageSearchData::getNotOverlappedNeighbours(
		const pair< unsigned int, unsigned int> & position ) const{
	
	const unsigned long ulX = position.first;
	const unsigned long ulY = position.second;
	
	set< pair< unsigned int, unsigned int> > setNeighboursPositionsVector;
	pair< unsigned int, unsigned int> vectorPosition;
	
	//evalue the four neighbours
	if ( ulY < ulBorderY ){
		//inside y area
		if ( ( 0 < ulX ) && ( ulX <= ulBorderX ) ){
			//check if the point was not overlapped
			const unsigned long ulPosition = ulY * ulBorderX + ulX - 1;
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ){
				vectorPosition.first  = ulX - 1;
				vectorPosition.second = ulY;
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
		if ( ( ulX + 1 ) < ulBorderX ){
			//check if the point was not overlapped
			const unsigned long ulPosition = ulY * ulBorderX + ulX + 1;
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ){
				vectorPosition.first  = ulX + 1;
				vectorPosition.second = ulY;
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
	}
	if ( ulX < ulBorderX ){
		//inside x area
		if ( ( 0 < ulY ) && ( ulY <= ulBorderY ) ){
			//check if the point was not overlapped
			const unsigned long ulPosition = ( ulY - 1 ) * ulBorderX + ulX;
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ){
				vectorPosition.first  = ulX;
				vectorPosition.second = ulY - 1;
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
		if ( ( ulY + 1 ) < ulBorderY ){
			//check if the point was not overlapped
			const unsigned long ulPosition = ( ulY + 1 ) * ulBorderX + ulX;
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ){
				vectorPosition.first  = ulX;
				vectorPosition.second = ulY + 1;
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
	}
	return setNeighboursPositionsVector;
}


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
set< pair< unsigned int, unsigned int> > cImageSearchData::
		getNotFoundNotOverlappedNeighbours(
			const pair< unsigned int, unsigned int> & position ) const{
	
	const unsigned long ulX = position.first;
	const unsigned long ulY = position.second;
	
	set<pair< unsigned int, unsigned int> > setNeighboursPositionsVector;
	pair< unsigned int, unsigned int> vectorPosition;
	
	//evalue the four neighbours
	if ( ulY < ulBorderY ){
		//inside y area
		if ( ( 0 < ulX ) && ( ulX <= ulBorderX ) ){
			//check if the point was not overlapped
			const unsigned long ulPosition = ulY * ulBorderX + ulX - 1;
			if ( ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) &&
					( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
						( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) ){
				vectorPosition.first  = ulX - 1;
				vectorPosition.second = ulY;
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
		if ( ( ulX + 1 ) < ulBorderX ){
			//check if the point was not overlapped
			const unsigned long ulPosition = ulY * ulBorderX + ulX + 1;
			if ( ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) &&
					( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
						( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) ){
				vectorPosition.first  = ulX + 1;
				vectorPosition.second = ulY;
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
	}
	if ( ulX < ulBorderX ){
		//inside x area
		if ( ( 0 < ulY ) && ( ulY <= ulBorderY ) ){
			//check if the point was not overlapped
			const unsigned long ulPosition = ( ulY - 1 ) * ulBorderX + ulX;
			if ( ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) &&
					( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
						( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) ){
				vectorPosition.first  = ulX;
				vectorPosition.second = ulY - 1;
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
		if ( ( ulY + 1 ) < ulBorderY ){
			//check if the point was not overlapped
			const unsigned long ulPosition = ( ulY + 1 ) * ulBorderX + ulX;
			if ( ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) &&
					( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
						( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) ){
				vectorPosition.first  = ulX;
				vectorPosition.second = ulY + 1;
				setNeighboursPositionsVector.insert( vectorPosition );
			}
		}
	}
	return setNeighboursPositionsVector;
}


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
bool cImageSearchData::hasNotFoundNotOverlappedNeighbours(
		const pair< unsigned int, unsigned int> & position ) const{
	
	const unsigned long ulX = position.first;
	const unsigned long ulY = position.second;
	
	//evalue the four neighbours
	if ( ulY < ulBorderY ){
		//inside y area
		if ( ( 0 < ulX ) && ( ulX <= ulBorderX ) ){
			//check if the point was not overlapped
			const unsigned long ulPosition = ulY * ulBorderX + ulX - 1;
			if ( ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) &&
					( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
						( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) ){
				return true;
			}
		}
		if ( ( ulX + 1 ) < ulBorderX ){
			//check if the point was not overlapped
			const unsigned long ulPosition = ulY * ulBorderX + ulX + 1;
			if ( ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) &&
					( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
						( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) ){
				return true;
			}
		}
	}
	if ( ulX < ulBorderX ){
		//inside x area
		if ( ( 0 < ulY ) && ( ulY <= ulBorderY ) ){
			//check if the point was not overlapped
			const unsigned long ulPosition = ( ulY - 1 ) * ulBorderX + ulX;
			if ( ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) &&
					( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
						( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) ){
				return true;
			}
		}
		if ( ( ulY + 1 ) < ulBorderY ){
			//check if the point was not overlapped
			const unsigned long ulPosition = ( ulY + 1 ) * ulBorderX + ulX;
			if ( ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) &&
					( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
						( 0x01 << ( ulPosition % 8 ) ) ) == 0x0 ) ){
				return true;
			}
		}
	}
	return false;
}


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
bool cImageSearchData::registerFound(
		const pair< unsigned int, unsigned int> & foundPoint,
		const bool bFound ){
	
	const unsigned long ulX = foundPoint.first;
	const unsigned long ulY = foundPoint.second;
	
	DEBUG_OUT_L2(<<"cImageSearchData("<<this<<")::registerFound( foundPointPair=("<<ulX<<", "<<ulY<<"), bFound="<<(bFound?"true":"false")<<" ) started"<<endl<<flush);
	
	if ( ( ulBorderX <= ulX ) || ( ulBorderY <= ulY ) ){
		//point not existing -> points not found
		return false;
	}
	
	const unsigned long ulPosition = ulY * ulBorderX + ulX;
	
	unsigned char * pByte = ( pImageDataFound + ( ulPosition / 8 ) );
	
	if ( bFound ){
		//register point as found
		(*pByte) |= ( 0x01 << (ulPosition % 8) );
	}else{//register point as not found
		(*pByte) &= ~( 0x01 << (ulPosition % 8) );
	}
	return true;
}


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
unsigned long cImageSearchData::registerFound(
		const set< pair< unsigned int, unsigned int> > & setFoundPoints,
		const bool bFound ){
	
	unsigned long ulRegisteredPoints = 0;
	DEBUG_OUT_L2(<<"cImageSearchData("<<this<<")::registerFound( #setFoundPointsPair=("<<setFoundPoints.size()<<"), bFound="<<(bFound?"true":"false")<<" ) started points:"<<flush);
	
	for ( set< pair< unsigned int, unsigned int> >::iterator
			itrFoundPoint = setFoundPoints.begin();
			itrFoundPoint != setFoundPoints.end(); itrFoundPoint++ ){
		
		const unsigned long ulX = itrFoundPoint->first;
		const unsigned long ulY = itrFoundPoint->second;
	
		DEBUG_OUT_L2(<<" ("<<ulX<<", "<<ulY<<");"<<flush);
		
		if ( ( ulX < ulBorderX ) && ( ulY < ulBorderY ) ){
			
			const unsigned long ulPosition = ulY * ulBorderX + ulX;
			
			unsigned char * pByte = ( pImageDataFound + ( ulPosition / 8 ) );
			
			if ( bFound ){
				//register point as found
				(*pByte) |= ( 0x01 << ( ulPosition % 8 ) );
			}else{//register point as not found
				(*pByte) &= ~( 0x01 << ( ulPosition % 8 ) );
			}
			ulRegisteredPoints++;
		}
	}
	DEBUG_OUT_L2(<<endl<<flush);
	return ulRegisteredPoints;
}


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
bool cImageSearchData::registerOverlapped(
		const pair< unsigned int, unsigned int> & overlappedPoint,
		const bool bOverlapped ){
	
	const unsigned long ulX = overlappedPoint.first;
	const unsigned long ulY = overlappedPoint.second;
	
	if ( ( ulBorderX <= ulX ) || ( ulBorderY <= ulY ) ){
		//point not existing -> points not overlapped
		return false;
	}
	
	const unsigned long ulPosition = ulY * ulBorderX + ulX;
	
	unsigned char * pByte = ( pImageDataOverlapped + ( ulPosition / 8 ) );
	
	if ( bOverlapped ){
		//register point as overlapped
		(*pByte) |= ( 0x01 << ( ulPosition % 8 ) );
	}else{//register point as not overlapped
		(*pByte) &= ~( 0x01 << ( ulPosition % 8 ) );
	}
	return true;
}


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
unsigned long cImageSearchData::registerOverlapped(
		const set< pair< unsigned int, unsigned int> > & setOverlappedPoints,
		const bool bOverlapped ){
	
	DEBUG_OUT_L4(<<"cImageSearchData("<<this<<")::registerOverlapped( setOverlappedPoints, bOverlapped="<<(bOverlapped?"true":"false")<<" ) started"<<endl<<flush);
	
	unsigned long ulRegisteredPoints = 0;
	
	for ( set<pair< unsigned int, unsigned int> >::iterator
			itrOverlappedPoint = setOverlappedPoints.begin();
			itrOverlappedPoint != setOverlappedPoints.end(); itrOverlappedPoint++ ){
		
		const unsigned long ulX = itrOverlappedPoint->first;
		const unsigned long ulY = itrOverlappedPoint->second;
		
		if ( ( ulX < ulBorderX ) && ( ulY < ulBorderY ) ){
			
			const unsigned long ulPosition = ulY * ulBorderX + ulX;
			
			unsigned char * pByte = ( pImageDataOverlapped + ( ulPosition / 8 ) );
			
			DEBUG_OUT_L4(<<"register point ("<<ulX<<", "<<ulY<<") on position "<<ulPosition<< " for the "<<(ulPosition / 8)<<" byte (image ulBorderX="<<ulBorderX<<" ulBorderY="<<ulBorderY<<")"<<endl<<flush);
			
			if ( bOverlapped ){
				//register point as overlapped
				(*pByte) |= ( 0x01 << ( ulPosition % 8 ) );
			}else{//register point as not overlapped
				(*pByte) &= ~( 0x01 << ( ulPosition % 8 ) );
			}
			ulRegisteredPoints++;
		}
	}
	return ulRegisteredPoints;
}







