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
 * GNU Lesser General Public License for more details.
 *
 * This file implements a class to store the data for a search on image data.
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


#include "cImageSearchData.h"

#include "cDomains.h"
#include "cDomain.h"
#include "cDomainIntegerBasis.h"

#include <string>


using namespace std;

using namespace fib::algorithms::nConvertToFib::nImage;
using namespace fib;


/**
 * parameter constructor
 *
 * @param ulInWidth the width of the image to search @see ulWidth
 * @param ulInHeight the height of the image to search @see ulHeight
 */
cImageSearchData::cImageSearchData( const unsigned long ulInWidth,
		const unsigned long ulInHeight ): pImageData( NULL ),
		ulWidth( ulInWidth ), ulHeight( ulInHeight ){
	
	//init arrays
	const unsigned long ulBytsNeeded = ulWidth * ulHeight / 8 + 1;
	
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
		ulWidth = 0;
		ulHeight = 0;
		return;
	}
	//evalue width and height
	const cDomains domsPosition = pImageData->getPositionDomain();
	
	const cDomain * pDomPosition = cDomains::getDomain( 1 );
	if ( ( pDomPosition == NULL ) || ( ! pDomPosition->isVector() ) ||
			( ((const cDomainVectorBasis*)(pDomPosition))->getNumberOfElements() != 2 ) ){
		//Error: no image data given
		pImageDataFound = NULL;
		pImageDataOverlapped = NULL;
		ulWidth = 0;
		ulHeight = 0;
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
		ulWidth = 0;
		ulHeight = 0;
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
		ulWidth = 0;
		ulHeight = 0;
		return;
	}
	
	const cDomainIntegerBasis  * pDomPositionIntDim1 =
		(cDomainIntegerBasis*)pDomPositionDim1;
	const cDomainIntegerBasis  * pDomPositionIntDim2 =
		(cDomainIntegerBasis*)pDomPositionDim2;
	
	ulWidth = (unsigned long)(
		((const cDomainIntegerBasis*)pDomPositionDim1)->getMaximumUnscaled() -
			((const cDomainIntegerBasis*)pDomPositionDim1)->getMinimumUnscaled()) + 1;
	ulHeight = (unsigned long)(
		((const cDomainIntegerBasis*)pDomPositionDim2)->getMaximumUnscaled() -
			((const cDomainIntegerBasis*)pDomPositionDim2)->getMinimumUnscaled()) + 1;
	
	//init arrays
	const unsigned long ulBytsNeeded = ulWidth * ulHeight / 8 + 1;
	
	pImageDataFound = (unsigned char*)malloc( ulBytsNeeded );
	memset( pImageDataFound, 0x0, ulBytsNeeded );
	pImageDataOverlapped = (unsigned char*)malloc( ulBytsNeeded );
	memset( pImageDataOverlapped, 0x0, ulBytsNeeded );
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
 * @return the width of the image to search
 * @see ulWidth
 */
unsigned long cImageSearchData::getWidth() const{
	
	return ulWidth;
}


/**
 * @return the height of the image to search
 * @see ulHeight
 */
unsigned long cImageSearchData::getHeight() const{
	
	return ulHeight;
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
 * @see pImageDataFound
 * @param position the position of the point, for which to check, if it
 * 	was found
 * @return true if the point on the position was found, else false
 */
bool cImageSearchData::isFound( const cVectorPosition& position ) const{
	
	const long lX = position.getValue( 1 );
	const long lY = position.getValue( 2 );
	
	if ( ( lX < 0 ) || ( ulWidth <= lX ) ||
			( lY < 0 ) || ( ulHeight <= lY ) ){
		//point not existing -> point not found
		return false;
	}
	
	const unsigned long ulPosition = lY * ulHeight + lX;
	
	return ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
		( 0x01 << ulPosition % 8 ) ) != 0x0 );
}


/**
 * @see pImageDataOverlapped
 * @param position the position of the point, for which to check, if it
 * 	is overlapped
 * @return true if the point on the position is overlapped, else false
 */
bool cImageSearchData::isOverlapped( const cVectorPosition& position ) const{
	
	const long lX = position.getValue( 1 );
	const long lY = position.getValue( 2 );
	
	if ( ( lX < 0 ) || ( ulWidth <= lX ) ||
			( lY < 0 ) || ( ulHeight <= lY ) ){
		//point not existing -> point not overlapped
		return false;
	}
	
	const unsigned long ulPosition = lY * ulHeight + lX;
	
	return ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
		( 0x01 << ulPosition % 8 ) ) != 0x0 );
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
	for ( unsigned long lY = 0; lY < ulHeight; lY++, ulPosition++ ){
		
		for ( unsigned long lX = 0; lX < ulWidth; lX++, ulPosition++ ){
			
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ulPosition % 8 ) ) != 0x0 ){
				
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
	for ( unsigned long lY = 0; lY < ulHeight; lY++, ulPosition++ ){
		
		for ( unsigned long lX = 0; lX < ulWidth; lX++, ulPosition++ ){
			
			if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
					( 0x01 << ulPosition % 8 ) ) == 0x0 ){
				
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
	for ( unsigned long lY = 0; lY < ulHeight; lY++, ulPosition++ ){
		
		for ( unsigned long lX = 0; lX < ulWidth; lX++, ulPosition++ ){
			
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ulPosition % 8 ) ) != 0x0 ){
				
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
	for ( unsigned long lY = 0; lY < ulHeight; lY++, ulPosition++ ){
		
		for ( unsigned long lX = 0; lX < ulWidth; lX++, ulPosition++ ){
			
			if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
					( 0x01 << ulPosition % 8 ) ) == 0x0 ){
				
				vectorPosition.setValue( 1, lX );
				vectorPosition.setValue( 2, lY );
				setNotOverlappedPositionsVector.insert( vectorPosition );
			}
		}
	}
	return setNotOverlappedPositionsVector;
}


/**
 * @see registerFound()
 * @see getFoundNeighbours()
 * @param position the position of the point, for which to return the
 * 	neighbour points
 * @return a set of the neighbour points of the given point
 */
set<cVectorPosition> cImageSearchData::getNeighbours( const cVectorPosition& position ) const{
	
	const long lX = position.getValue( 1 );
	const long lY = position.getValue( 2 );
	
	set<cVectorPosition> setNeighboursPositionsVector;
	cVectorPosition vectorPosition( 2 );
	//evalue the four neighbours
	if ( 0 < lX ){
		vectorPosition.setValue( 1, lX - 1 );
		vectorPosition.setValue( 2, lY );
		setNeighboursPositionsVector.insert( vectorPosition );
	}
	if ( 0 < lY ){
		vectorPosition.setValue( 1, lX  );
		vectorPosition.setValue( 2, lY - 1 );
		setNeighboursPositionsVector.insert( vectorPosition );
	}
	if ( ( lX + 1 ) < ulWidth ){
		vectorPosition.setValue( 1, lX + 1 );
		vectorPosition.setValue( 2, lY );
		setNeighboursPositionsVector.insert( vectorPosition );
	}
	if ( ( lY + 1 ) < ulHeight ){
		vectorPosition.setValue( 1, lX  );
		vectorPosition.setValue( 2, lY + 1 );
		setNeighboursPositionsVector.insert( vectorPosition );
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
	
	const long lX = position.getValue( 1 );
	const long lY = position.getValue( 2 );
	
	set<cVectorPosition> setNeighboursPositionsVector;
	cVectorPosition vectorPosition( 2 );
	
	//evalue the four neighbours
	if ( 0 < lX ){
		//check if the point was found
		const unsigned long ulPosition = lY * ulHeight + lX - 1;
		if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
				( 0x01 << ulPosition % 8 ) ) != 0x0 ){
			vectorPosition.setValue( 1, lX - 1 );
			vectorPosition.setValue( 2, lY );
			setNeighboursPositionsVector.insert( vectorPosition );
		}
	}
	if ( 0 < lY ){
		//check if the point was found
		const unsigned long ulPosition = ( lY - 1 ) * ulHeight + lX;
		if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
				( 0x01 << ulPosition % 8 ) ) != 0x0 ){
			vectorPosition.setValue( 1, lX  );
			vectorPosition.setValue( 2, lY - 1 );
			setNeighboursPositionsVector.insert( vectorPosition );
		}
	}
	if ( ( lX + 1 ) < ulWidth ){
		//check if the point was found
		const unsigned long ulPosition = lY * ulHeight + lX + 1;
		if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
				( 0x01 << ulPosition % 8 ) ) != 0x0 ){
			vectorPosition.setValue( 1, lX + 1 );
			vectorPosition.setValue( 2, lY );
			setNeighboursPositionsVector.insert( vectorPosition );
		}
	}
	if ( ( lY + 1 ) < ulHeight ){
		//check if the point was found
		const unsigned long ulPosition = ( lY + 1 ) * ulHeight + lX;
		if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
				( 0x01 << ulPosition % 8 ) ) != 0x0 ){
			vectorPosition.setValue( 1, lX );
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
 * 	not found neighbour points
 * @return a set of the not found neighbour points of the given point
 * @see pImageDataFound
 */
set<cVectorPosition> cImageSearchData::getNotFoundNeighbours(
		const cVectorPosition& position ) const{
	
	const long lX = position.getValue( 1 );
	const long lY = position.getValue( 2 );
	
	set<cVectorPosition> setNeighboursPositionsVector;
	cVectorPosition vectorPosition( 2 );
	
	//evalue the four neighbours
	if ( 0 < lX ){
		//check if the point was not found
		const unsigned long ulPosition = lY * ulHeight + lX - 1;
		if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
				( 0x01 << ulPosition % 8 ) ) == 0x0 ){
			vectorPosition.setValue( 1, lX - 1 );
			vectorPosition.setValue( 2, lY );
			setNeighboursPositionsVector.insert( vectorPosition );
		}
	}
	if ( 0 < lY ){
		//check if the point was not found
		const unsigned long ulPosition = ( lY - 1 ) * ulHeight + lX;
		if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
				( 0x01 << ulPosition % 8 ) ) == 0x0 ){
			vectorPosition.setValue( 1, lX  );
			vectorPosition.setValue( 2, lY - 1 );
			setNeighboursPositionsVector.insert( vectorPosition );
		}
	}
	if ( ( lX + 1 ) < ulWidth ){
		//check if the point was not found
		const unsigned long ulPosition = lY * ulHeight + lX + 1;
		if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
				( 0x01 << ulPosition % 8 ) ) == 0x0 ){
			vectorPosition.setValue( 1, lX + 1 );
			vectorPosition.setValue( 2, lY );
			setNeighboursPositionsVector.insert( vectorPosition );
		}
	}
	if ( ( lY + 1 ) < ulHeight ){
		//check if the point was not found
		const unsigned long ulPosition = ( lY + 1 ) * ulHeight + lX;
		if ( ( *((pImageDataFound + ( ulPosition / 8 ) ) ) &
				( 0x01 << ulPosition % 8 ) ) == 0x0 ){
			vectorPosition.setValue( 1, lX );
			vectorPosition.setValue( 2, lY + 1 );
			setNeighboursPositionsVector.insert( vectorPosition );
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
	
	const long lX = position.getValue( 1 );
	const long lY = position.getValue( 2 );
	
	set<cVectorPosition> setNeighboursPositionsVector;
	cVectorPosition vectorPosition( 2 );
	
	//evalue the four neighbours
	if ( 0 < lX ){
		//check if the point was overlapped
		const unsigned long ulPosition = lY * ulHeight + lX - 1;
		if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
				( 0x01 << ulPosition % 8 ) ) != 0x0 ){
			vectorPosition.setValue( 1, lX - 1 );
			vectorPosition.setValue( 2, lY );
			setNeighboursPositionsVector.insert( vectorPosition );
		}
	}
	if ( 0 < lY ){
		//check if the point was overlapped
		const unsigned long ulPosition = ( lY - 1 ) * ulHeight + lX;
		if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
				( 0x01 << ulPosition % 8 ) ) != 0x0 ){
			vectorPosition.setValue( 1, lX  );
			vectorPosition.setValue( 2, lY - 1 );
			setNeighboursPositionsVector.insert( vectorPosition );
		}
	}
	if ( ( lX + 1 ) < ulWidth ){
		//check if the point was overlapped
		const unsigned long ulPosition = lY * ulHeight + lX + 1;
		if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
				( 0x01 << ulPosition % 8 ) ) != 0x0 ){
			vectorPosition.setValue( 1, lX + 1 );
			vectorPosition.setValue( 2, lY );
			setNeighboursPositionsVector.insert( vectorPosition );
		}
	}
	if ( ( lY + 1 ) < ulHeight ){
		//check if the point was overlapped
		const unsigned long ulPosition = ( lY + 1 ) * ulHeight + lX;
		if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
				( 0x01 << ulPosition % 8 ) ) != 0x0 ){
			vectorPosition.setValue( 1, lX );
			vectorPosition.setValue( 2, lY + 1 );
			setNeighboursPositionsVector.insert( vectorPosition );
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
	
	const long lX = position.getValue( 1 );
	const long lY = position.getValue( 2 );
	
	set<cVectorPosition> setNeighboursPositionsVector;
	cVectorPosition vectorPosition( 2 );
	
	//evalue the four neighbours
	if ( 0 < lX ){
		//check if the point was not overlapped
		const unsigned long ulPosition = lY * ulHeight + lX - 1;
		if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
				( 0x01 << ulPosition % 8 ) ) == 0x0 ){
			vectorPosition.setValue( 1, lX - 1 );
			vectorPosition.setValue( 2, lY );
			setNeighboursPositionsVector.insert( vectorPosition );
		}
	}
	if ( 0 < lY ){
		//check if the point was not overlapped
		const unsigned long ulPosition = ( lY - 1 ) * ulHeight + lX;
		if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
				( 0x01 << ulPosition % 8 ) ) == 0x0 ){
			vectorPosition.setValue( 1, lX  );
			vectorPosition.setValue( 2, lY - 1 );
			setNeighboursPositionsVector.insert( vectorPosition );
		}
	}
	if ( ( lX + 1 ) < ulWidth ){
		//check if the point was not overlapped
		const unsigned long ulPosition = lY * ulHeight + lX + 1;
		if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
				( 0x01 << ulPosition % 8 ) ) == 0x0 ){
			vectorPosition.setValue( 1, lX + 1 );
			vectorPosition.setValue( 2, lY );
			setNeighboursPositionsVector.insert( vectorPosition );
		}
	}
	if ( ( lY + 1 ) < ulHeight ){
		//check if the point was not overlapped
		const unsigned long ulPosition = ( lY + 1 ) * ulHeight + lX;
		if ( ( *((pImageDataOverlapped + ( ulPosition / 8 ) ) ) &
				( 0x01 << ulPosition % 8 ) ) == 0x0 ){
			vectorPosition.setValue( 1, lX );
			vectorPosition.setValue( 2, lY + 1 );
			setNeighboursPositionsVector.insert( vectorPosition );
		}
	}
	
	return setNeighboursPositionsVector;
}

//TODO check

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
	
	const long lX = foundPoint.getValue( 1 );
	const long lY = foundPoint.getValue( 2 );
	
	if ( ( lX < 0 ) || ( ulWidth <= lX ) ||
			( lY < 0 ) || ( ulHeight <= lY ) ){
		//point not existing -> points not found
		return false;
	}
	
	const unsigned long ulPosition = lY * ulHeight + lX;
	
	unsigned char * pByte = (pImageDataFound + ( ulPosition / 8 ) );
	
	if ( bFound ){
		pByte |= ( 0x01 << ulPosition % 8 );
	}else{
		pByte &= ~( 0x01 << ulPosition % 8 );
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
 * @return true if the points wher (/not) registered as found,
 * 	else false and no data changed
 */
bool cImageSearchData::registerFound(
		const set<cVectorPosition> & setFoundPoints, const bool bFound ){
	
	for ( set<cVectorPosition>::iterator itrFoundPoint = setFoundPoints.begin();
			itrFoundPoint != setFoundPoints.end(); itrFoundPoint++ ){
		
		const long lX = itrFoundPoint->getValue( 1 );
		const long lY = itrFoundPoint->getValue( 2 );
		
		if ( ( lX < 0 ) || ( ulWidth <= lX ) ||
				( lY < 0 ) || ( ulHeight <= lY ) ){
			//point not existing -> points not found
			return false;
		}
	}
	for ( set<cVectorPosition>::iterator itrFoundPoint = setFoundPoints.begin();
			itrFoundPoint != setFoundPoints.end(); itrFoundPoint++ ){
		
		const long lX = itrFoundPoint->getValue( 1 );
		const long lY = itrFoundPoint->getValue( 2 );
		
		const unsigned long ulPosition = lY * ulHeight + lX;
		
		unsigned char * pByte = (pImageDataFound + ( ulPosition / 8 ) );
		
		if ( bFound ){
			pByte |= ( 0x01 << ulPosition % 8 );
		}else{
			pByte &= ~( 0x01 << ulPosition % 8 );
		}
	}
	return true;
}


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
bool cImageSearchData::registerFound(
		const cImageStructure * imageStrFoundPoints, const bool bFound ){
	
	//TODO implement
	
	return registerFound( setFoundPoints, bFound );
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
	
	const long lX = overlappedPoint.getValue( 1 );
	const long lY = overlappedPoint.getValue( 2 );
	
	if ( ( lX < 0 ) || ( ulWidth <= lX ) ||
			( lY < 0 ) || ( ulHeight <= lY ) ){
		//point not existing -> points not overlapped
		return false;
	}
	
	const unsigned long ulPosition = lY * ulHeight + lX;
	
	unsigned char * pByte = (pImageDataOverlapped + ( ulPosition / 8 ) );
	
	if ( bOverlapped ){
		pByte |= ( 0x01 << ulPosition % 8 );
	}else{
		pByte &= ~( 0x01 << ulPosition % 8 );
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
 * @return true if the points wher (/not) registered as overlapped,
 * 	else false and no data changed
 */
bool cImageSearchData::registerOverlapped(
		const set<cVectorPosition> & setOverlappedPoints, const bool bOverlapped ){
	
	for ( set<cVectorPosition>::iterator itrOverlappedPoint = setOverlappedPoints.begin();
			itrOverlappedPoint != setOverlappedPoints.end(); itrOverlappedPoint++ ){
		
		const long lX = itrOverlappedPoint->getValue( 1 );
		const long lY = itrOverlappedPoint->getValue( 2 );
		
		if ( ( lX < 0 ) || ( ulWidth <= lX ) ||
				( lY < 0 ) || ( ulHeight <= lY ) ){
			//point not existing -> points not overlapped
			return false;
		}
	}
	for ( set<cVectorPosition>::iterator itrOverlappedPoint = setOverlappedPoints.begin();
			itrOverlappedPoint != setOverlappedPoints.end(); itrOverlappedPoint++ ){
		
		const long lX = itrOverlappedPoint->getValue( 1 );
		const long lY = itrOverlappedPoint->getValue( 2 );
		
		const unsigned long ulPosition = lY * ulHeight + lX;
		
		unsigned char * pByte = (pImageDataOverlapped + ( ulPosition / 8 ) );
		
		if ( bOverlapped ){
			pByte |= ( 0x01 << ulPosition % 8 );
		}else{
			pByte &= ~( 0x01 << ulPosition % 8 );
		}
	}
	return true;
}


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
bool cImageSearchData::registerOverlapped(
		const cImageStructure * imageStrOverlappedPoints, const bool bOverlapped ){
	
	//TODO implement
	return registerOverlapped( setOverlappedPoints, bOverlapped );
}


/**
 * Converts all found points to overlapped points.
 * If you start a new layer, wich is below the layers of the found points,
 * call this method.
 */
void cImageSearchData::foundToOverlapped(){
	
	const unsigned long ulBytsInArrays = ulWidth * ulHeight / 8 + 1;
	
	unsigned char * pTmpImageDataOverlapped = pImageDataOverlapped;
	unsigned char * pTmpImageDataFound = pImageDataFound;
	
	for ( unsigned long ulActualByte = 0; ulActualByte < ulBytsInArrays;
			ulActualByte++, pTmpImageDataOverlapped++, pTmpImageDataFound++ ){
		
		pTmpImageDataOverlapped |= pTmpImageDataFound;
	}
}


