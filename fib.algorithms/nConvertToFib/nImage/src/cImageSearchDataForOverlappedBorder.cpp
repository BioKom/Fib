/**
 * @file cImageSearchDataForOverlappedBorder
 * file name: cImageSearchDataForOverlappedBorder.cpp
 * @author Betti Oesterholz
 * @date 29.04.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header implements a class to store the data for a search on image
 * data and data for the border of the overlapped area.
 *
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
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This header implements a class to store the data for a search on image
 * data and data for the border of the overlapped area.
 * If you want to convert an image to Fib structures, you have to search
 * the image for structures, which can be converted to Fib.
 * To mark for which points structures where found and which points you can
 * set to any overwritten property because the points are overwritten, you
 * can use this class.
 *
 * This class will also help to get border points of the overlapped area
 * @see getBorderPoint()
 * and to mark points of a Fib object as overlapped. @see evaluePosition()
 *
 * All positions vectors (cVectorPosition) elements should be positiv
 * integers from 0 to ulBorderX or ulBorderY respectively.
 *
 */
/*
History:
29.04.2013  Oesterholz  created
*/


#include "cImageSearchDataForOverlappedBorder.h"

#include "cVectorPosition.h"
#include "cVectorProperty.h"

#include <queue>
#include <list>
#include <utility>


using namespace fib::algorithms::nConvertToFib::nImage;



/**
 * parameter constructor
 *
 * @param ulInWidth the width of the image to search @see ulBorderX
 * @param ulInHeight the height of the image to search @see ulBorderY
 * @param dInTransparencyThreshold just points with a lower or equal transparency
 * 	value will be marked as overlapped when evalued by @see evaluePosition()
 * 	@see dTransparencyThreshold
 */
cImageSearchDataForOverlappedBorder::cImageSearchDataForOverlappedBorder(
		const unsigned long ulInWidth, const unsigned long ulInHeight,
		const double dInTransparencyThreshold ):
			cImageSearchData( ulInWidth, ulInHeight ),
			dTransparencyThreshold( dInTransparencyThreshold ){
	//nothing to do
}


/**
 * parameter constructor
 *
 * @param pInImageData pointer to the image data, of the image to convert
 * 	@see pImageData
 * @param dInTransparencyThreshold just points with a lower or equal transparency
 * 	value will be marked as overlapped when evalued by @see evaluePosition()
 * 	@see dTransparencyThreshold
 */
cImageSearchDataForOverlappedBorder::cImageSearchDataForOverlappedBorder(
		const iImageData * pInImageData,
		const double dInTransparencyThreshold ):
			cImageSearchData( pInImageData ),
			dTransparencyThreshold( dInTransparencyThreshold ){
	//nothing to do
}


/**
 * copy constructor
 *
 * @param pInImageData pointer to the image search data to copy
 */
cImageSearchDataForOverlappedBorder::cImageSearchDataForOverlappedBorder(
			const cImageSearchDataForOverlappedBorder & imageSearchData ):
			cImageSearchData( imageSearchData ),
			dTransparencyThreshold( imageSearchData.dTransparencyThreshold ){
	//nothing to do
}


/**
 * destructor
 */
cImageSearchDataForOverlappedBorder::~cImageSearchDataForOverlappedBorder(){
	//nothing to do
}


/**
 * This method clones this object.
 *
 * @return a pointer to the clone of this object
 */
cImageSearchDataForOverlappedBorder * cImageSearchDataForOverlappedBorder::clone() const{
	
	return new cImageSearchDataForOverlappedBorder( *this );
}


/**
 * @return the transparency threshold value
 * 	@see dTransparencyThreshold
 */
double cImageSearchDataForOverlappedBorder::getTransparencyThreshold() const{
	
	return dTransparencyThreshold;
}


/**
 * @return true and a point near the overlapped points but not overlapped
 * 	itself, or false
 * 		first: if a border point exists
 * 		second: if first is true the point near the overlapped points but
 * 			not overlapped
 */
pair< bool, pair< unsigned int, unsigned int> >
		cImageSearchDataForOverlappedBorder::getBorderPoint(){
	
	//try to get a border points from the possible border point queue
	while ( ! qePossibleOverlappedBorderPoints.empty() ){
		const pair< unsigned int, unsigned int> paPointToCheck =
			qePossibleOverlappedBorderPoints.front();
		qePossibleOverlappedBorderPoints.pop();
		if ( ( ! isOverlapped( paPointToCheck ) ) && isIn( paPointToCheck ) ){
			//border point found
			return make_pair( true, paPointToCheck );
		}
	}//else search the image search data for the next not overlapped point
	
	unsigned long ulBytsInOverlapped = ( ulBorderX * ulBorderY ) / 8 + 1;
	
	const unsigned char * pActualByte = pImageDataOverlapped;
	for ( unsigned long ulActualByte = 0; ulActualByte < ulBytsInOverlapped;
			ulActualByte++, pActualByte++ ){
		
		if ( (*pActualByte) != 0xFF ){
			//one of the (given) points in byte is not overlapped
			//evalue the position of the first bit in the byte
			unsigned long ulActualBit = ulActualByte * 8;
			
			char cMaskBit = 0x01;
			for ( unsigned int uiByteBit = 0; uiByteBit < 8;
					uiByteBit++, ulActualBit++, cMaskBit = (cMaskBit << 1) ){
				if ( ( cMaskBit & (*pActualByte) ) == 0x00 ){
					//bit for not overlapped (bit is 0) found
					break;
				}
			}//for all bits in byte
			
			const unsigned int uiY = ulActualBit / ulBorderX;
			if ( ulBorderY <= uiY ){
				//no such point
				return make_pair( false, pair< unsigned int, unsigned int>( 0, 0 ) );
			}//else return point
			const unsigned int uiX = ulActualBit % ulBorderX;
			
			return make_pair( true, pair< unsigned int, unsigned int>( uiX, uiY ) );
		}//end if one of the points in byte is not overlapped
	}//end for the overlapped bit mask
	return make_pair( false, pair< unsigned int, unsigned int>( 0, 0 ) );
}


/**
 * This method will mark every point with a transparency value lower or
 * equal the transparency threshold (or no transparency) as overlapped.
 * @see dTransparencyThreshold
 *
 * @param vPosition the position of the point, which is evalued
 * @param vProperties a list of the properties of the point
 * @return true if the the point cold be evalued, else false
 */
bool cImageSearchDataForOverlappedBorder::evaluePosition(
		const cVectorPosition & vPosition,
		const list<cVectorProperty> & vProperties ){
	
	if ( vPosition.getNumberOfElements() != 2 ){
		//can't evalue a point with not two position elements
		return false;
	}
	
	//default transparency (=0) is OK (because it is lower equal the threshold)
	bool bTransparencyOk = true;
	/* search for the transparency property and check if it is lower equal
	 * the threshold (the last found transparency value counts)*/
	for ( list<cVectorProperty>::const_iterator
				itrProperty = vProperties.begin();
			itrProperty != vProperties.end(); itrProperty++ ){
		
		if ( itrProperty->getPropertyType() == cTypeProperty::TRANSPARENCY ){
			//transparency
			if ( dTransparencyThreshold < itrProperty->getValue( 1 ) ){
				//transparency value to great
				bTransparencyOk = false;
			}else{//if ( itrProperty->getValue( 1 ) <= dTransparencyThreshold )
				//transparency value is Ok
				bTransparencyOk = true;
			}
		}//else not a transparency property -> check next property
	}//end for all properties for the point
	
	if ( bTransparencyOk ){
		//set point as overlapped
		registerOverlapped( vPosition );
		
		//remember (not overlapped) neigbours as possible overlapped border
		const pair< unsigned int, unsigned int> paPosition(
			roundToLongFib( vPosition.getValue( 1 ) ),
			roundToLongFib( vPosition.getValue( 2 ) ) );
		const set< pair< unsigned int, unsigned int> > setNeighbours =
			getNotOverlappedNeighbours( paPosition );
		
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
					itrNeighbour = setNeighbours.begin();
				itrNeighbour != setNeighbours.end(); itrNeighbour++ ){
			//check if outside bounderies
			if ( isIn( *itrNeighbour ) ){
				qePossibleOverlappedBorderPoints.push( *itrNeighbour );
			}
		}
	}else{//don't set point as overlapped
		//check if outside bounderies
		if ( isIn( vPosition ) ){
			qePossibleOverlappedBorderPoints.push(
				pair< unsigned int, unsigned int>(
					roundToLongFib( vPosition.getValue( 1 ) ),
					roundToLongFib( vPosition.getValue( 2 ) ) ) );
		}
	}//end if transparency OK
	return true;
}



