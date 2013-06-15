
//TODO check

/**
 * @file jsInterface
 * file name: jsInterface.cpp
 * @author Betti Oesterholz
 * @date 10.04.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements a interface to interact with the Fib library for
 * Javascript.
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
 * This file implements a class to store the data for a search on image data.
 * If you want to convert an image to Fib structures, you have to search
 * the image for structures, which can be converted to Fib.
 * To mark for which points structures wher found and which points you can
 * set to any overwritten property because the points are overwritten, you
 * can use this class.
 *
 *
 * This file implements a interface to interact with the Fib library for
 * Javascript.
 *
 */
/*
History:
10.04.2012  Oesterholz  created
*/

//switches for debugging proposes
//#define DEBUG


#include "cFibElement.h"
#include "cPoint.h"
#include "cVectorPosition.h"
#include "cVectorProperty.h"
#include "cTypeProperty.h"
#include "cTypeDimension.h"
#include "cEvalueSimpleRGBA255.h"

#include "cFibDatabaseJavaScript.h"


#include <string>
#include <ostream>
#include <sstream>      // std::ostringstream
#include <fstream>
#include <vector>

using namespace std;
using namespace fib;

pair< long, long > getFibObjectDimensions( cFibElement * pFibObject );
bool saveAsBitmap( const cEvalueSimpleRGBA255 * pImageData,
		ostream * stream );
std::basic_string<unsigned char> base64Encode(
		const unsigned char * pInputBuffer, const unsigned int uiBufferSize );


extern "C" {

/*
 * give parameters ( [ ... ] ):
 * 	printP = Module.convertFibToImageData('printPoint', 'string', ['number'] )
 */

/**
 * @return a image data encoded with base64 for a default image
 */
char * getDefaultImage(){
	return ((char *)"iVBORw0KGgoAAAANSUhEUgAAAAUAAAAFCAYAAACNbyblAAAAHElEQVQI12P4//8/w38GIAXDIBKE0DHxgljNBAAO9TXL0Y4OHwAAAABJRU5ErkJggg==");
}


/**
 * This function converts the given Fib object into bmp image data encoded
 * with base64.
 *
 * @param szGivenData the Fib object given in the Fib Xml representation
 * @return the given Fib object into bmp image data encoded with base64
 */
char * convertFibToImageData( const char * szGivenData ){
	
	
	if ( szGivenData == NULL ){
		printf("convertFibToImageData(): no data given\n" );
		return getDefaultImage();
	}
	//comment out
	//printf("Data given: %s\n", szGivenData );
	
	//set the correct database class cFibDatabaseJavaScript
	cFibDatabaseJavaScript::getInstance();
	
	//load the given Fib object
	istringstream strXmlFibObject( ((string)( szGivenData )) );
	intFib outStatus = 0;
	
	cFibElement * pRestoredFibObject =
		cFibElement::restoreXml( strXmlFibObject , &outStatus );
	
	if ( outStatus < 0 ){
		const int iOutStatus = outStatus;
		
		printf("Restoring Fib object in the Xml format not successfull. (return status=%i)\n", iOutStatus);
		if ( pRestoredFibObject ){
			cFibElement::deleteObject( pRestoredFibObject );
		}
		return getDefaultImage();
	}
	if ( outStatus != 0 ){
		const int iOutStatus = outStatus;
		
		printf("Restoring Fib object in the Xml format returned warning. (return status=%i)\n", iOutStatus);
	}
	//pRestoredFibObject contains the restored Fib object
	//evalue Fib object size
	pair< long, long > paDimensions = getFibObjectDimensions( pRestoredFibObject );
	if ( ( paDimensions.first < 0 ) || ( paDimensions.second < 0 ) ){
		//no valid dimensions
		return getDefaultImage();
	}
	
	//evalue the Fib object into image
	printf("value the Fib object into image with width %li and hight %li\n",
		paDimensions.first, paDimensions.second );
	cEvalueSimpleRGBA255 imageData( paDimensions.first, paDimensions.second );
	
	pRestoredFibObject->evalueObjectSimple( imageData );
	
	//store the image data as a bitmap
	printf("store the image data as a bitmap\n");
	std::ostringstream ostrForImageData;
	const bool bBitmapSaved = saveAsBitmap( &imageData, &ostrForImageData );
	if ( ! bBitmapSaved ){
		return NULL;
	}
	
	//convert to base64 format
	printf("convert to base64 format\n");
	const string strForImageData = ostrForImageData.str();
	std::basic_string<unsigned char> strBase64ForImageData =
		base64Encode( ((const unsigned char *)(strForImageData.c_str())),
			strForImageData.size() );
	
	//convert to java compatible string (global char *)
	printf("convert to java compatible string (global char *)\n");
	static char * szBase64ForImageData = NULL;
	if ( szBase64ForImageData != NULL ){
		delete szBase64ForImageData;
	}
	szBase64ForImageData = new char [ strBase64ForImageData.length() + 1 ];
	std::strcpy( szBase64ForImageData, ((const char *)strBase64ForImageData.c_str()) );
	
	printf("convertFibToImageData() done result (a bitmap in base64, for the img element \"<img src=\"data:image/bmp;base64,...\">\" ):\n\"%s\"\n", szBase64ForImageData );
	return szBase64ForImageData;
}


/**
 * This function sets the Fib database path to the given path.
 *
 * @param szInDatabasePath the path to set
 * @return 0 (dummy)
 */
int setDatabasePath( const char * szInDatabasePath ){
	
	cFibDatabaseJavaScript::getInstance()->setDatabasePath( szInDatabasePath );
	
	return 0;
}

};//end extern "C"





/**
 * This function evalues the the size of the given Fib object for image data.
 *
 * @param pFibObject the Fib object for which to evalue dimensions
 * @return a pair with the size ( first=width and second=hight) of the image
 */
pair< long, long > getFibObjectDimensions( cFibElement * pFibObject ){
	
	if ( ( pFibObject == NULL ) || ( pFibObject->getType() != 'r' ) ){
		//no valid dimension
		return pair< long, long >( -1, -1 );
	}
	cRoot * pRootObject = ((cRoot *)pFibObject);
	
	/*evalue the size of the image and include a corresponding dimension
	domain in the root element*/
	if ( pRootObject->getNumberOfDimensions() != 2 ){
		printf("Error: No 2 dimensional Fib object.\n");
		return pair< long, long >( -1, -1 );
	}
	
	/*TODO implement for image matrix and evalue:
	const unsignedIntFib dimensionMapping1 = pRootObject->getDimensionMapping( 1 );
	const unsignedIntFib dimensionMapping2 = pRootObject->getDimensionMapping( 2 );
	bool bDimensionXY = true;
	if ( ( dimensionMapping1 == cTypeDimension::DIRECTION_HORIZONTAL ) &&
			( dimensionMapping2 == cTypeDimension::DIRECTION_VERTICAL ) ){
		bDimensionXY = true;
	}else if ( ( dimensionMapping1 == cTypeDimension::DIRECTION_VERTICAL ) &&
			( dimensionMapping2 == cTypeDimension::DIRECTION_HORIZONTAL ) ){
		bDimensionXY = false;
	}else{
		printf("Error: Wrong Dimension mappings.\n");
		return pair< long, long >( -1, -1 );
	}*/
	
	cDomain * pDomainDimension = pRootObject->
		getValidDomains().getDomainForElement( cTypeDimension() );
	
	if ( pDomainDimension == NULL ){
		printf("Error: No dimension domain.\n" );
		return pair< long, long >( -1, -1 );
	}
	cDomainVectorBasis * pVecDomainDimension = (cDomainVectorBasis*)pDomainDimension;
	
	if ( pVecDomainDimension->getNumberOfElements() != 2 ){
		printf("Error: No 2 dimensional dimension domain in Fib object.\n");
		return pair< long, long >( -1, -1 );
	}
	if ( ( ! pVecDomainDimension->getElementDomain( 1 )->isScalar() ) ||
			( ! pVecDomainDimension->getElementDomain( 2 )->isScalar() ) ){
		printf("Error: A dimension subdomain in the Fib object is not a scalar.\n");
		return pair< long, long >( -1, -1 );
	}
	cDomainSingle * pDirection1Domain = (cDomainSingle*)(
		pVecDomainDimension->getElementDomain( 1 ) );
	cDomainSingle * pDirection2Domain = (cDomainSingle*)(
		pVecDomainDimension->getElementDomain( 2 ) );
	
	const float dDirection1Minimum = pDirection1Domain->getMinimum();
	const float dDirection1Maximum = pDirection1Domain->getMaximum();
	float dDirection1Scaling = 1.0;
	string szDomainElementType = pDirection1Domain->getType();
	if ( ( szDomainElementType.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
				(szDomainElementType.compare( 0, 13, "DomainInteger" ) == 0) ){
		//cDomainIntegerBasis
		dDirection1Scaling = ((cDomainIntegerBasis*)pDirection1Domain)->getScalingFactor();
	}
	const float dDirection2Minimum = pDirection2Domain->getMinimum();
	const float dDirection2Maximum = pDirection2Domain->getMaximum();
	float dDirection2Scaling = 1.0;
	szDomainElementType = pDirection2Domain->getType();
	if ( ( szDomainElementType.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
				(szDomainElementType.compare( 0, 13, "DomainInteger" ) == 0) ){
		//cDomainIntegerBasis
		dDirection2Scaling = ((cDomainIntegerBasis*)pDirection2Domain)->getScalingFactor();
	}
	
	const unsigned long ulWidth = (unsigned long)(
		(dDirection1Maximum - dDirection1Minimum) / dDirection1Scaling) + 1;
	const unsigned long ulHeight = (unsigned long)(
		(dDirection2Maximum - dDirection2Minimum) / dDirection2Scaling) + 1;
	
	printf("image size width=%lu (= (%f- %f) / %f + 1)",
		ulWidth, dDirection1Maximum, dDirection1Minimum, dDirection1Scaling );
	printf(" height=%lu (= (%f- %f) / %f + 1)\n",
		ulHeight, dDirection2Maximum, dDirection2Minimum, dDirection2Scaling );
	
	/*TODO implement for image matrix and evalue:
	if ( bDimensionXY ){
		return pair< long, long >( ulWidth, ulHeight );
	}//else
	return pair< long, long >( ulHeight, ulWidth );
	*/
	return pair< long, long >( ulWidth, ulHeight );
}








/**
 * This function writes the value of iWrite with usByte bytes to the stream stream.
 *
 * @param stream the stream to iWrite to
 * @param usByte the number of byts to write
 * @param iWrite the value iWrite to write
 * @return the value of iWrite with byte bytes in the stream stream
 */
void writeInteger( ostream * stream, unsigned short usByte, int iWrite ){
	for ( unsigned short i = 0; i < usByte ; i++ ){
		(*stream) << (unsigned char)( iWrite );
		iWrite = iWrite >> 8;
	}
}


//TODO color with background color



/**
 * This function stores the image data in pImageData to a stream in the
 * bitmap pictur format.
 *
 * @param pImageData the image data to store as a bitmap image
 * @param stream the stream wher to write the image data to
 * @return true if the image was stored as a bitmap image
 */
bool saveAsBitmap( const cEvalueSimpleRGBA255 * pImageData,
		ostream * stream ){
	
	if ( pImageData == NULL ){
		//no data to save
		return false;
	}
	const unsigned int uiWidth = pImageData->getMaxIndex( 0 );
	const unsigned int uiHight = pImageData->getMaxIndex( 1 );
	
	//TODO implement other color depth
	const unsigned int uiBitPerPixle = 24;
	const unsigned int uiNumberOfBytes =
		(uiHight * uiWidth * uiBitPerPixle) / 8;
	
	(*stream)<<'B'<<'M';//identifier
	writeInteger( stream, 4, 54 + uiNumberOfBytes );//file size
	writeInteger( stream, 4, 0 );//reserved
	writeInteger( stream, 4, 54 );//offset from file begin till data; 54 when no color table
	writeInteger( stream, 4, 40 );//bitmap header size
	writeInteger( stream, 4, uiWidth );//horizontale width of bitmap pixels
	writeInteger( stream, 4, uiHight );//vertical width of bitmap pixels
	writeInteger( stream, 2, 1 );//number of planes in this bitmap should be 1
	writeInteger( stream, 2, uiBitPerPixle );//bits per pixel; 24 for no color table
	writeInteger( stream, 4, 0 );//compression specification, should be 0=none
	writeInteger( stream, 4, uiNumberOfBytes );//size of bitmap data
	writeInteger( stream, 4, 0 );//horizontal pixel per meter, unimportant
	writeInteger( stream, 4, 0 );//vertical pixel per meter, unimportant

	writeInteger( stream, 4, 0 );//number of colors
	writeInteger( stream, 4, 0 );//number of important colors, should be equal number of colors
	
	//write bitmap data
	const char * pCursor = (const char *)(pImageData->pImageData);
	pCursor++;//ignore alpha value
	
	//to fill every line till line is a multiple of 4 bytes some 0 bytes are needed
	const unsigned int uiToFillNullBytesOfLine =
		( 4 - ( ( uiWidth * uiBitPerPixle ) / 8 ) % 4 ) % 4;
	cout<<"width="<<uiWidth<<"   hight="<<uiHight<<endl;
	cout<<"Null bytes to fill="<<uiToFillNullBytesOfLine<<
		" (bytes per bitmap line "<<(( uiWidth * uiBitPerPixle ) / 8)<<")"<<endl;
	const char pcNull[ 4 ] = { 0x00, 0x00, 0x00, 0x00 };
	
	//( ( lX * (uiBorderIndexY==uiWidth)  + lY ) * 4 );

	const char * pCursor2 = pCursor;
	const unsigned int uiBytsPerLine = (uiHight + 1) * 4;
	for ( unsigned int uiY = 0; uiY < uiHight; uiY++ ){
		for ( unsigned int uiX = 0; uiX < uiWidth; uiX++ ){
			//write pixle data
			//stream->write( pCursor, 3 );
			stream->write( pCursor + 2, 1 );
			stream->write( pCursor + 1, 1 );
			stream->write( pCursor, 1 );
			
			pCursor += uiBytsPerLine;
			//weg: pCursor += 4;
		}
		pCursor2 += 4;
		pCursor = pCursor2;
		//fill till line is a multiple of 4 bytes
		stream->write( pcNull, uiToFillNullBytesOfLine );
	}
	//weg: stream->write( ((const char *)pImageData->pImageData), uiNumberOfBytes );
	
	return true;
}






/**
 * Below is a C++ version of Base64Encode. This code is released into public domain.
 * Source: http://en.wikibooks.org/wiki/Algorithm_Implementation/Miscellaneous/Base64#C.2B.2B
*/
// Prototype
// std::basic_string<TCHAR> base64Encode(std::vector<BYTE> inputBuffer);
// This line goes in header file

/* Define these if they aren't already in your environment */

#ifndef TEXT
	//#define TEXT(x) Lx    //Unicode
	#define TEXT(x) x     //Not unicode
#ifndef TEXT
#endif //TCHAR
	#define TCHAR wchar_t //Unicode
#endif //TCHAR
	/*
	#define TCHAR char    //Not unicode
	*/
#ifndef DWORD
	#define DWORD long
#endif //DWORD
#ifndef BYTE
	#define BYTE unsigned char
#endif //BYTE

//Lookup table for encoding
//If you want to use an alternate alphabet, change the characters here
const static TCHAR encodeLookup[] =
	//TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
	{'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/'};

const static TCHAR padCharacter = TEXT('=');


/**
 * This functions encodes the characters of the buffer with base64 .
 *
 * @param pInputBuffer the buffer to encode
 * @param uiBufferSize the number of characters in the buffer to encode
 * @return a string with the encoded data
 */
std::basic_string<unsigned char> base64Encode(
		const unsigned char * pInputBuffer, const unsigned int uiBufferSize ){
	
	std::basic_string<unsigned char> szEncodedString;
	szEncodedString.reserve( ((uiBufferSize / 3) + (uiBufferSize % 3 > 0)) * 4 );
	unsigned long lTemp = 0;
	const unsigned char * pCursor = pInputBuffer;
	for( size_t idx = 0; idx < uiBufferSize / 3; idx++ ){
		lTemp  = (*pCursor) << 16; //Convert to big endian
		pCursor++;
		lTemp += (*pCursor) << 8;
		pCursor++;
		lTemp += (*pCursor);
		pCursor++;
		szEncodedString.append( 1, encodeLookup[(lTemp & 0x00FC0000) >> 18] );
		szEncodedString.append( 1, encodeLookup[(lTemp & 0x0003F000) >> 12] );
		szEncodedString.append( 1, encodeLookup[(lTemp & 0x00000FC0) >> 6 ] );
		szEncodedString.append( 1, encodeLookup[(lTemp & 0x0000003F)      ] );
	}
	switch ( uiBufferSize % 3 ){
		case 1:
			lTemp  = (*pCursor) << 16; //Convert to big endian
			pCursor++;
			szEncodedString.append( 1, encodeLookup[(lTemp & 0x00FC0000) >> 18] );
			szEncodedString.append( 1, encodeLookup[(lTemp & 0x0003F000) >> 12] );
			szEncodedString.append( 2, padCharacter );
		break;
		case 2:
			lTemp  = (*pCursor) << 16; //Convert to big endian
			pCursor++;
			lTemp += (*pCursor) << 8;
			pCursor++;
			szEncodedString.append( 1, encodeLookup[(lTemp & 0x00FC0000) >> 18] );
			szEncodedString.append( 1, encodeLookup[(lTemp & 0x0003F000) >> 12] );
			szEncodedString.append( 1, encodeLookup[(lTemp & 0x00000FC0) >> 6 ] );
			szEncodedString.append( 1, padCharacter );
		break;
	}
	return szEncodedString;
}
















