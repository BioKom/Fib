/**
 * @file fipImage
 * file name: fipImage.h
 * @author Betti Oesterholz
 * @date 14.05.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file specifies class to wrap the FreeImage functionality for
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
 * This file specifies class to wrap the FreeImage functionality for
 * the Fib-system.
 *
 */
/*
History:
14.05.2011  Oesterholz  created
22.03.2012  Oesterholz  setTransparent() implemented
14.04.2012  Oesterholz  isTransparent() and unload() implemented
*/

#include "FreeImage.h"


#ifndef ___C_FIP_IMAGE_H__
#define ___C_FIP_IMAGE_H__


/**
 * @class fipImage
 * Warper class for FreeImage image data
 */
class fipImage{
private:
	
	/**
	 * This flag is true if the FreeImage system was initialised, else false.
	 */
	static bool bFreeImageInitialised;
	
	/**
	 * The counter for the number of instances of this class.
	 * If no instance exists anymore the FreeImage system will be
	 * deinitialised.
	 */
	static unsigned long ulImageInstances;
	
	/**
	 * The pointer to the data of the image.
	 */
	FIBITMAP * pImageData;

public:

	/**
	 * standard constructor of an fipImage object
	 */
	fipImage();
	
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
	fipImage( FREE_IMAGE_TYPE type, const unsigned long ulWidth, const unsigned long ulHeight, const unsigned int uiBitsPerPixel );
	
	/**
	 * copy constructor
	 *
	 * @param inFipImage the fip image to copy
	 */
	fipImage( const fipImage & inFipImage );
	
	/**
	 * destructor
	 */
	~fipImage();
	
	
	/**
	 * @return the width of the image (in points)
	 */
	unsigned long getWidth() const;
	
	/**
	 * @return the height of the image (in points)
	 */
	unsigned long getHeight() const;
	
	/**
	 * @return the number of bits per pixel for the color
	 */
	unsigned int getBitsPerPixel() const;
	
	/**
	 * @return true if the picture is in grayscale else false
	 */
	bool isGrayscale() const;
	
	/**
	 * @return the color type of the picture
	 */
	FREE_IMAGE_COLOR_TYPE getColorType() const;
	
	/**
	 * @return the number of entries in the color palette
	 */
	unsigned long getPaletteSize() const;
	
	/**
	 * @return the array of the color palette (every entry is an color)
	 */
	RGBQUAD * getPalette() const;
	
	/**
	 * @return if the picture has an background color, else false
	 */
	bool hasFileBkColor() const;
	
	/**
	 * This method returns the background color value of the picture.
	 *
	 * @param colorValue a pointer to the color value field wher to store
	 * 	the background color value
	 * @return true if the background color was evalued, else false
	 */
	bool getFileBkColor( RGBQUAD * colorValue ) const;
	
	/**
	 * This method sets the background color value of the picture.
	 *
	 * @param colorValue the color value to set
	 * @return true if the background color was set, else false
	 */
	bool setFileBkColor( RGBQUAD * colorValue );
	
	/**
	 * This method returns the color on the given position.
	 *
	 * @param ulX the horizontal (x) position, from which to get the color
	 * @param ulY the vertical (y) position, from which to get the color
	 * @param colorValue a pointer to the color value field wher to store
	 * 	the color value
	 * @return true if pixel color was evalued, else false
	 */
	bool getPixelColor( const unsigned long ulX, const unsigned long ulY, RGBQUAD * colorValue ) const;
	
	/**
	 * This method sets the color on the given position.
	 *
	 * @param ulX the horizontal (x) position, on which to set the color
	 * @param ulY the vertical (y) position, on which to set the color
	 * @param colorValue a pointer to the color value field to set
	 * @return true if pixel color was set, else false
	 */
	bool setPixelColor( const unsigned long ulX, const unsigned long ulY, RGBQUAD * colorValue );
	
	/**
	 * This method returns the color index value on the given position.
	 *
	 * @param ulX the horizontal (x) position, from which to get the color index
	 * @param ulY the vertical (y) position, from which to get the color index
	 * @param colorValue a pointer to the color index value field wher to
	 * 	store the color index value
	 * @return true if pixel color index was evalued, else false
	 */
	bool getPixelIndex( const unsigned long ulX, const unsigned long ulY, BYTE * colorIndexValue ) const;
	
	/**
	 * This method sets the color index value on the given position.
	 *
	 * @param ulX the horizontal (x) position, on which to set the color index
	 * @param ulY the vertical (y) position, on which to set the color index
	 * @param colorValue a pointer to the color index value field to set
	 * @return true if pixel color index was set, else false
	 */
	bool setPixelIndex( const unsigned long ulX, const unsigned long ulY, BYTE * colorIndexValue );
	
	/**
	 * This method converts the image to grayscale.
	 *
	 * @return true if the image was converted to grayscale, else false
	 */
	bool convertToGrayscale();
	
	/**
	 * @return true if transparency is enabled, else false
	 */
	bool isTransparent();
	
	/**
	 * This method sets if transparency should be enabled for the image.
	 *
	 * @param bEnabled if transparency should be enabled
	 */
	void setTransparent( bool bEnabled );
	
	/**
	 * This method loads the image from an given file.
	 * The image type will determined by the file ending and its
	 * contained data.
	 *
	 * @param szFile the path of the image file to load
	 * @return true if the image data was loaded, else false
	 */
	bool load( const char * szFile );
	
	/**
	 * Deletes previously loaded image data.
	 */
	void unload();
	
	/**
	 * This method saves the image to an given file.
	 * The image type will determined by the file ending.
	 *
	 * @param szFile the path of the image file to save
	 * @return true if the image data was saved, else false
	 */
	bool save( const char * szFile ) const;

	
};//end class fipImage



#endif //___C_FIP_IMAGE_H__


