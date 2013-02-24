/**
 * @class cEvalueSimpleRGBA255
 * file name: cEvalueSimpleRGBA255.h
 * @author Betti Oesterholz
 * @date 18.03.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the class for evaluing Fib objects as a matrix of
 * a RGBA image.
 * Copyright (C) @c LGPL3 2012 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This file contains the class for evaluing Fib objects as a matrix of
 * a RGBA image. @see pImageData
 * Just colors and transparency is evalued. The data is stored into an
 * array. The array is two dimensional and goes in the first dimension
 * from 0 to uiMaxX and in the second from 0 to uiMaxY. Every entry of the
 * array consists of tree values with 8 bit each (values from 0 to 255).
 * This class should keep the evaluing of a normal image (e.g. Bitmap image)
 * as simple as possible.
 */
/*
History:
18.03.2012  Oesterholz  created
10.04.2012  Oesterholz  methods of interface iImageData added
19.02.2013  Oesterholz  clone method and copy constructor added
*/

#ifndef ___C_EVALUE_SIMPLE_RGBA_255__
#define ___C_EVALUE_SIMPLE_RGBA_255__

#include "version.h"

#include "iEvaluePosition.h"
#include "iImageData.h"

#include "cVectorPosition.h"
#include "cVectorProperty.h"


#include <list>



using std::list;

namespace fib{

class cEvalueSimpleRGBA255: public iEvaluePosition, public iImageData{
public:
	
	/**
	 * The maximum value for the first (x) dimension.
	 * (The number of point rows.)
	 */
	const unsigned int uiMaxX;
	
	/**
	 * The maximum value for the second (y) dimension.
	 * (The number of point lines.)
	 */
	const unsigned int uiMaxY;
	
	/**
	 * The matrix with the ARGB image data.
	 * The dimension entries are:
	 * 	- first dimension (x)
	 * 	- second dimension (y)
	 * 	- value: alpha (transparency), red, green, blue
	 * 	wher 0 is the minimum (e.g. no green) and 255 the maximum (e.g.
	 * 	full red), the color values are non-premultiplied;
	 * 	for the alpha value @see http://en.wikipedia.org/wiki/Alpha_compositing
	 * 	(0 = total transparent, 255 = total opaque)
	 *
	 * The pointer will point to an one dimensional array. You have to evalue
	 * the single entries by hand (with: *(pImageData + (x * uiMaxY + y) * 4) )
	 */
	unsigned char * pImageData;
	
	/**
	 * The ARGB value for the background color.
	 * value: alpha (transparency), red, green, blue
	 * 	wher 0 is the minimum (e.g. no green) and 255 the maximum (e.g.
	 * 	full red), the color values are non-premultiplied;
	 * 	for the alpha value @see http://en.wikipedia.org/wiki/Alpha_compositing
	 * 	(0 = total transparent, 255 = total opaque)
	 */
	unsigned char pBackgroundColor[ 4 ];
	
	/**
	 * If true a background color was set.
	 */
	bool bBackgroundColorExists;
	
	/**
	 * standard constructor
	 *
	 * @param uiInMaxX the maximum value for the first (x) dimension @see uiMaxX
	 * @param uiInMaxY the maximum value for the second (y) dimension @see uiMaxY
	 */
	cEvalueSimpleRGBA255( const unsigned int uiInMaxX, const unsigned int uiInMaxY );

	/**
	 * copy constructor
	 *
	 * @param evalueSimpleRGBA255 the evalueSimpleRGBA255 to copy
	 */
	cEvalueSimpleRGBA255( const cEvalueSimpleRGBA255 & evalueSimpleRGBA255 );

	/**
	 * desstructor
	 */
	~cEvalueSimpleRGBA255();

	/**
	 * This method clones this object.
	 */
	virtual cEvalueSimpleRGBA255 * clone();
	
	/**
	 * The method with wich the evalued points with ther properties are
	 * inserted. Everytime a point (to evalue) is reached in the
	 * evaluation, this method is called with the position and the
	 * properties of the point and stores the data into @see pImageData
	 * This method will just evalue two dimensional points and properties
	 * for RGB and transparency.
	 * Points first dimension can have values from 0 ( including ) to the
	 * maximum value for the first (x) dimension.
	 * 	( 0 =< vPosition.getValue( 1 ) < uiMaxX ) @see uiMaxX
	 * Points second dimension ( vPosition.getValue( 2 ) ) can have values
	 * from 0 ( including ) to the maximum value for the second (y) dimension.
	 * 	( 0 =< vPosition.getValue( 2 ) < uiMaxY ) @see uiMaxY
	 * Background points (with 0 elements) are also possible.
	 * All other points will be discarded.
	 * Property (color RGB or transparency) element values should have a
	 * values from 0 to 255 (both including), else they will be rounded
	 * into the area.
	 *
	 * @see pImageData
	 * @param vPosition the position of the point, which is evalued
	 * @param vProperties a list of the properties of the point
	 */
	virtual bool evaluePosition( const cVectorPosition & vPosition,
		const list<cVectorProperty> & vProperties );

	/**
	 * This method clears the data from the list with the evalued position data
	 * liEvaluedPositionData.
	 * After the function call the liEvaluedPositionData list will be empty.
	 *
	 * @see liEvaluedPositionData
	 */
	virtual void clear();
	
	/**
	 * Adds the background color pBackgroundColor to the image data matrix
	 * pImageData, if existing.
	 *
	 * @see pBackgroundColor
	 * @see pImageData
	 * @return true if the background color was added the image data matrix,
	 * 	else false
	 */
	bool colorWithBackgroundColor();
	
	
//methods of interface iImageData:
	
	/**
	 * This method returns the domains for the color and transparency properties.
	 *
	 * @return the domains for the color and transparency properties
	 */
	virtual cDomains getPropertyDomains() const;

	/**
	 * This method returns the domains for the positions (dimension domain).
	 *
	 * @return the domains for the positions (dimension domain)
	 */
	virtual cDomains getPositionDomain() const;
	
	/**
	 * With this method the properties for a points are set.
	 *
	 * @param vPosition the position of the point to set
	 * @param vProperties a list of the properties of the point
	 * @return true if the properties for the point cold be set, else false
	 */
	virtual bool setPoint(  const cVectorPosition & vPosition,
		const list<cVectorProperty> & vProperties );
	
	/**
	 * With this method the properties for given points are returned.
	 *
	 * @param vPosition the position of the point, for which the properties
	 * 	should be returned
	 * @return a list of the properties of the point
	 */
	virtual list<cVectorProperty> getPointProperties(
		const cVectorPosition & vPosition ) const;

	
};//class cEvalueSimpleRGBA255

};

#endif


