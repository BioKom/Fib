/**
 * @file saveAsBitmap
 * file name: saveAsBitmap.cpp
 * @author Betti Oesterholz
 * @date 03.08.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This programm evalues the size of the different fib -datatyps.
 *
 * Copyright (C) @c GPL3 2010 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
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
 * This programm evalues the size of the different fib -datatyps.
 *
 */
/*
History:
03.08.2010  Oesterholz  created
*/

#include "version.h"

#include "cPoint.h"
#include "cRoot.h"
#include "cList.h"
#include "cArea.h"
#include "cProperty.h"
#include "cFunction.h"
#include "cComment.h"

#include "cFunctionValue.h"
#include "cFunctionVariable.h"
#include "cFunctionAbs.h"
#include "cFunctionSin.h"
#include "cFunctionLog.h"
#include "cFunctionArcsin.h"
#include "cFunctionAdd.h"
#include "cFunctionSub.h"
#include "cFunctionMult.h"
#include "cFunctionDiv.h"
#include "cFunctionExp.h"
#include "cFunctionMin.h"
#include "cFunctionMax.h"
#include "cFibElement.h"

#include "cTypeProperty.h"
#include "cEvalueSimpleRGBA255.h"


#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"
#include "cTypeVariable.h"
#include "cTypeInVar.h"

#include "cFibVariable.h"
#include "cVectorProperty.h"
#include "cVectorPosition.h"

#include "cEvaluePositionList.h"
#include "cEvalueFibElementList.h"


#include "tinyxml.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <ostream>
#include <ctime>
#include <string>
#include <sstream>      // std::ostringstream

#include "tCompareBits.inc"

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif



using namespace fib;
using namespace std;


bool saveAsBitmap( const cEvalueSimpleRGBA255 * pImageData,
		ostream * stream );
std::basic_string<unsigned char> base64Encode(
		const unsigned char * pInputBuffer, const unsigned int uiBufferSize );


int main(int argc, char* argv[]){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	cout<<endl<<"This programm stores an cEvalueSimpleRGBA255 as an bitmap image"<<endl;
	cout<<      "==============================================================="<<endl;
	

	cEvalueSimpleRGBA255 imageData( 4, 6 );
	
	//TODO set image data
	cVectorPosition vecPosition( 2 );
	cVectorProperty vecProperty( cTypeProperty::COLOR_RGB );
	
	list<cVectorProperty> liProperties;
	liProperties.push_back( vecProperty );
	cVectorProperty & vecLiProperty = liProperties.back();
	
	
	vecPosition.setValue( 1, 0 );
	vecPosition.setValue( 2, 0 );
	vecLiProperty.setValue( 1, 255 );
	vecLiProperty.setValue( 2, 255 );
	vecLiProperty.setValue( 3, 255 );
	imageData.setPoint( vecPosition, liProperties );

	vecPosition.setValue( 1, 1 );
	vecPosition.setValue( 2, 0 );
	vecLiProperty.setValue( 1, 128 );
	vecLiProperty.setValue( 2, 128 );
	vecLiProperty.setValue( 3, 128 );
	imageData.setPoint( vecPosition, liProperties );

	vecPosition.setValue( 1, 0 );
	vecPosition.setValue( 2, 1 );
	vecLiProperty.setValue( 1, 64 );
	vecLiProperty.setValue( 2, 64 );
	vecLiProperty.setValue( 3, 64 );
	imageData.setPoint( vecPosition, liProperties );

	vecPosition.setValue( 1, 0 );
	vecPosition.setValue( 2, 2 );
	vecLiProperty.setValue( 1, 64 );
	vecLiProperty.setValue( 2, 0 );
	vecLiProperty.setValue( 3, 0 );
	imageData.setPoint( vecPosition, liProperties );

	vecPosition.setValue( 1, 0 );
	vecPosition.setValue( 2, 3 );
	vecLiProperty.setValue( 1, 128 );
	vecLiProperty.setValue( 2, 0 );
	vecLiProperty.setValue( 3, 0 );
	imageData.setPoint( vecPosition, liProperties );


	vecPosition.setValue( 1, 1 );
	vecPosition.setValue( 2, 1 );
	vecLiProperty.setValue( 1, 64 );
	vecLiProperty.setValue( 2, 128 );
	vecLiProperty.setValue( 3, 88 );
	imageData.setPoint( vecPosition, liProperties );
	
	vecPosition.setValue( 1, 3 );
	vecPosition.setValue( 2, 1 );
	vecLiProperty.setValue( 1, 0 );
	vecLiProperty.setValue( 2, 255 );
	vecLiProperty.setValue( 3, 0 );
	imageData.setPoint( vecPosition, liProperties );
	
	vecPosition.setValue( 1, 1 );
	vecPosition.setValue( 2, 4 );
	vecLiProperty.setValue( 1, 255 );
	vecLiProperty.setValue( 2, 0 );
	vecLiProperty.setValue( 3, 0 );
	imageData.setPoint( vecPosition, liProperties );
	
	vecPosition.setValue( 1, 2 );
	vecPosition.setValue( 2, 2 );
	vecLiProperty.setValue( 1, 255 );
	vecLiProperty.setValue( 2, 255 );
	vecLiProperty.setValue( 3, 0 );
	imageData.setPoint( vecPosition, liProperties );
	
	vecPosition.setValue( 1, 3 );
	vecPosition.setValue( 2, 5 );
	vecLiProperty.setValue( 1, 0 );
	vecLiProperty.setValue( 2, 0 );
	vecLiProperty.setValue( 3, 255 );
	imageData.setPoint( vecPosition, liProperties );
	
	
	{
		ofstream ostrForImageData( "test.bmp", ios_base::out | ios_base::binary );
		
		const bool bBitmapSaved = saveAsBitmap( &imageData, &ostrForImageData );
		if ( ! bBitmapSaved ){
			return 1;
		}
	}
	
	
	{
		//convert to base64 format
		std::ostringstream ostrForImageData;
		const bool bBitmapSaved2 = saveAsBitmap( &imageData, &ostrForImageData );
		if ( ! bBitmapSaved2 ){
			return 1;
		}
		
		const string strForImageData = ostrForImageData.str();
		std::basic_string<unsigned char> strBase64ForImageData =
			base64Encode( ((const unsigned char *)(strForImageData.c_str())),
				strForImageData.size() );
		
		ofstream ostrForImageDataBase64( "test.bmp.base64", ios_base::out | ios_base::binary );
		ostrForImageDataBase64<<strBase64ForImageData.c_str();
	}
	
	//convert to java compatible string (global char *)
	/*static char * szBase64ForImageData = NULL;
	if ( szBase64ForImageData != NULL ){
		delete szBase64ForImageData;
	}
	szBase64ForImageData = new char [ strBase64ForImageData.length() + 1 ];
	std::strcpy( szBase64ForImageData, ((const char *)strBase64ForImageData.c_str()) );
	*/





	cout<<"done"<<endl;
	
	return iReturn;
}




/**
 * writes the value of write with byte bytes to the stream stream
 * pre: the value write to write, how much usByte byte write should use and the stream to write to
 * post: the value of write with byte bytes in the stream stream
 */
void writeInteger( ostream * stream, unsigned short usByte, int iWrite ){
	for ( unsigned short i = 0; i < usByte ; i++ ){
		(*stream) << (unsigned char)( iWrite );
		iWrite = iWrite >> 8;
	}
}


/**
 * store this pictur Matrix to the bitmap pictur file with name file
 * pre: the name of the bitmap pictur file to store this PicturMatrix to
 */
bool saveAsBitmap( const cEvalueSimpleRGBA255 * pImageData,
		ostream * stream ){
	
	if ( pImageData == NULL ){
		//no data to save
		return false;
	}
	const unsigned int uiWidth = pImageData->uiMaxX;
	const unsigned int uiHight = pImageData->uiMaxY;
	
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
	const char * pCursor = (const char *)pImageData->pImageData;
	pCursor++;//ignore alpha value
	
	const char * pCursor2 = pCursor;
	const unsigned int uiBytsPerLine = uiHight * 4;
	
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
	}
	//weg: stream->write( ((const char *)pImageData->pImageData), uiNumberOfBytes );
	
	return true;
}


/**
	Below is a C++ version of Base64Encode. This code is released into public domain.
	Source: http://en.wikibooks.org/wiki/Algorithm_Implementation/Miscellaneous/Base64#C.2B.2B
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



