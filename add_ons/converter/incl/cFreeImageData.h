/**
 * @class cFreeImageData
 * file name: cFreeImageData.h
 * @author Betti Oesterholz
 * @date 14.04.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains a warper class for FreeImage image data with the
 * iImageData interface.
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
 * This file contains a warper class for FreeImage image data with the
 * iImageData interface.
 * (TODO: Just implemented for RGB images. No palettized image implemented.)
 */
/*
History:
14.04.2012  Oesterholz  created
*/

#ifndef ___C_FREE_IMAGE_DATA__
#define ___C_FREE_IMAGE_DATA__

#include "version.h"

#include "iImageData.h"

#include "cVectorPosition.h"
#include "cVectorProperty.h"

#include "fipImage.h"


#include <list>



using std::list;

namespace fib{

class cFreeImageData: public iImageData{
public:

	
	/**
	 * The object, for which this class is the wraper.
	 */
	fipImage * pFipImageDataObject;
	
	
	/**
	 * standard constructor
	 *
	 * @param fipImageDataObject The object, for which this class is the wraper.
	 */
	cFreeImageData( fipImage & fipImageDataObject );

	/**
	 * destructor
	 */
	virtual ~cFreeImageData();

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
	 * Beware: No scaling is done. The position coordinate values are taken
	 * as index values (counting starts at 0) for the image matrix. Color and
	 * transparency values should be numbers from 0 to 255 (inclusive).
	 *
	 * @param vPosition the position of the point to set
	 * @param vProperties a list of the properties of the point
	 * @return true if the properties for the point cold be set, else false
	 */
	virtual bool setPoint( const cVectorPosition & vPosition,
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

	/**
	 * This method clears the data from the list with the evalued position data
	 * liEvaluedPositionData.
	 * After the function call the liEvaluedPositionData list will be empty.
	 *
	 * @see liEvaluedPositionData
	 */
	virtual void clear();
	

};//class cFreeImageData

};

#endif //___C_FREE_IMAGE_DATA__


