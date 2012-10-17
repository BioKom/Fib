/**
 * @file fipImage
 * file name: fipImage.cpp
 * @author Betti Oesterholz
 * @date 17.05.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements an class to wrap the FreeImage functionality for
 * the Fib-system.
 * Copyright (C) @c GPL3 2010 Betti Oesterholz
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
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This file implements an class to wrap the FreeImage functionality for
 * the Fib-system.
 *
 */
/*
History:
17.05.2011  Oesterholz  created
22.03.2012  Oesterholz  setTransparent() implemented
14.04.2012  Oesterholz  isTransparent() and unload() implemented
*/

#include "fipImage.h"


#ifndef STATIC_VARIABLES_FIP_IMAGE
#define STATIC_VARIABLES_FIP_IMAGE

bool fipImage::bFreeImageInitialised = false;

unsigned long fipImage::ulImageInstances = 0;

#endif //STATIC_VARIABLES_FIP_IMAGE


/**
 * standard constructor of an fipImage object
 */
fipImage::fipImage(){
	
	if ( ! bFreeImageInitialised ){
		FreeImage_Initialise();
		bFreeImageInitialised = true;
	}
	ulImageInstances++;
	
	pImageData = NULL;
}


/**
 * parameter constructor of an fipImage object
 *
 * @param type the type of the image of the fipImage to create
 * @param ulWidth the width of the image (in points) of the fipImage
 * 	to create
 * @param ulHeight the height of the image (in points) of the fipImage
 * 	to create
 * @param uiBitsPerPixel the number of bits per pixel for the color of
 * 	the fipImage to create
 */
fipImage::fipImage( FREE_IMAGE_TYPE type, const unsigned long ulWidth,
		const unsigned long ulHeight, const unsigned int uiBitsPerPixel ){

	
	if ( ! bFreeImageInitialised ){
		FreeImage_Initialise();
		bFreeImageInitialised = true;
	}
	ulImageInstances++;
	
	pImageData = FreeImage_AllocateT( type, ulWidth, ulHeight, uiBitsPerPixel );

}


/**
 * copy constructor
 *
 * @param inFipImage the fip image to copy
 */
fipImage::fipImage( const fipImage & inFipImage ){

	
	if ( ! bFreeImageInitialised ){
		FreeImage_Initialise();
		bFreeImageInitialised = true;
	}
	ulImageInstances++;

	pImageData = FreeImage_Clone( inFipImage.pImageData );
}


/**
 * destructor
 */
fipImage::~fipImage(){
	
	if ( pImageData ){
		FreeImage_Unload( pImageData );
	}
	
	ulImageInstances--;
	if ( ( ulImageInstances == 0 ) && bFreeImageInitialised ){
		FreeImage_DeInitialise();
		bFreeImageInitialised = false;
	}
	
}



/**
 * @return the width of the image (in points)
 */
unsigned long fipImage::getWidth() const{

	return FreeImage_GetWidth( pImageData );
}


/**
 * @return the height of the image (in points)
 */
unsigned long fipImage::getHeight() const{

	return FreeImage_GetHeight( pImageData );
}

/**
 * @return the number of bits per pixel for the color
 */
unsigned int fipImage::getBitsPerPixel() const{
	
	return FreeImage_GetBPP( pImageData );
}


/**
 * @return the color type of the picture
 */
FREE_IMAGE_COLOR_TYPE fipImage::getColorType() const{

	return FreeImage_GetColorType( pImageData );
}


/**
 * @return the number of entries in the color palette
 */
unsigned long fipImage::getPaletteSize() const{

	return FreeImage_GetColorsUsed( pImageData );
}


/**
 * @return the array of the color palette (every entry is an color)
 */
RGBQUAD * fipImage::getPalette() const{

	return FreeImage_GetPalette( pImageData );
}


/**
 * @return if the picture has an background color, else false
 */
bool fipImage::hasFileBkColor() const{

	return FreeImage_HasBackgroundColor( pImageData );
}


/**
 * This method returns the background color value of the picture.
 *
 * @param colorValue a pointer to the color value field wher to store
 * 	the background color value
 * @return true if the background color was evalued, else false
 */
bool fipImage::getFileBkColor( RGBQUAD * colorValue ) const{

	return FreeImage_GetBackgroundColor( pImageData, colorValue );
}


/**
 * This method sets the background color value of the picture.
 *
 * @param colorValue the color value to set
 * @return true if the background color was set, else false
 */
bool fipImage::setFileBkColor( RGBQUAD * colorValue ){

	return FreeImage_SetBackgroundColor( pImageData, colorValue );
}


/**
 * This method returns the color on the given position.
 *
 * @param ulX the horizontal (x) position, from which to get the color
 * @param ulY the vertical (y) position, from which to get the color
 * @param colorValue a pointer to the color value field wher to store
 * 	the color value
 * @return true if pixel color was evalued, else false
 */
bool fipImage::getPixelColor( const unsigned long ulX, const unsigned long ulY, RGBQUAD * colorValue ) const{

/*	if ( colorValue == NULL ){
		return false;
	}
*/
	return FreeImage_GetPixelColor( pImageData, ulX, ulY, colorValue );
}

/**
 * This method sets the color on the given position.
 *
 * @param ulX the horizontal (x) position, on which to set the color
 * @param ulY the vertical (y) position, on which to set the color
 * @param colorValue a pointer to the color value field to set
 * @return true if pixel color was set, else false
 */
bool fipImage::setPixelColor( const unsigned long ulX, const unsigned long ulY,
		RGBQUAD * colorValue ){
	
	return FreeImage_SetPixelColor( pImageData, ulX, ulY, colorValue );
}


/**
 * This method returns the color index value on the given position.
 *
 * @param ulX the horizontal (x) position, from which to get the color index
 * @param ulY the vertical (y) position, from which to get the color index
 * @param colorValue a pointer to the color index value field wher to
 * 	store the color index value
 * @return true if pixel color index was evalued, else false
 */
bool fipImage::getPixelIndex( const unsigned long ulX, const unsigned long ulY,
		BYTE * colorIndexValue ) const{

/*	if ( ( colorIndexValue == NULL ) || ( pImageData == NULL ) ){
		return false;
	}
*/
	return FreeImage_GetPixelIndex( pImageData, ulX, ulY, colorIndexValue );
}


/**
 * This method sets the color index value on the given position.
 *
 * @param ulX the horizontal (x) position, on which to set the color index
 * @param ulY the vertical (y) position, on which to set the color index
 * @param colorValue a pointer to the color index value field to set
 * @return true if pixel color index was set, else false
 */
bool fipImage::setPixelIndex( const unsigned long ulX, const unsigned long ulY,
		BYTE * colorIndexValue ){

/*	if ( pImageData == NULL ){
		return false;
	}
*/
	return FreeImage_SetPixelIndex( pImageData, ulX, ulY, colorIndexValue );
}


/**
 * @return true if the picture is in grayscale else false
 */
bool fipImage::isGrayscale() const{

	return FreeImage_GetColorType( pImageData ) == FIC_MINISBLACK;
}


/**
 * This method converts the image to grayscale.
 *
 * @return true if the image was converted to grayscale, else false
 */
bool fipImage::convertToGrayscale(){

	pImageData = FreeImage_ConvertToGreyscale( pImageData );
	
	return isGrayscale();
}


/**
 * @return true if transparency is enabled, else false
 */
bool fipImage::isTransparent(){

	return FreeImage_IsTransparent( pImageData );
}


/**
 * This method sets if transparency should be enabled for the image.
 *
 * @param bEnabled if transparency should be enabled
 */
void fipImage::setTransparent( bool bEnabled ){

	FreeImage_SetTransparent( pImageData, bEnabled );
}


/**
 * This method loads the image from an given file.
 * The image type will determined by the file ending and its
 * contained data.
 *
 * @param the path of the image file to load
 * @return true if the image data was loaded, else false
 */
bool fipImage::load( const char * szFile ){

	FREE_IMAGE_FORMAT freeImageFormat = FreeImage_GetFileType( szFile );
	if ( freeImageFormat == FIF_UNKNOWN ){
		freeImageFormat = FreeImage_GetFIFFromFilename( szFile );
	}
	if ( freeImageFormat == FIF_UNKNOWN ){
		return false;
	}
	pImageData = FreeImage_Load( freeImageFormat, szFile);

	return ( pImageData != NULL );
}

/**
 * Deletes previously loaded image data.
 */
void fipImage::unload(){
	
	FreeImage_Unload( pImageData );
}


/**
 * This method saves the image to an given file.
 * The image type will determined by the file ending.
 *
 * @param szFile the path of the image file to save
 * @return true if the image data was saved, else false
 */
bool fipImage::save( const char * szFile ) const{

	FREE_IMAGE_FORMAT freeImageFormat = FreeImage_GetFIFFromFilename( szFile );
	if ( freeImageFormat == FIF_UNKNOWN ){
		return false;
	}
	
	return FreeImage_Save( freeImageFormat, pImageData, szFile);
}



















