/**
 * @class iImageData
 * file name: iImageData.h
 * @author Betti Oesterholz
 * @date 10.04.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the interface for image data classes.
 * Copyright (C) @c LGPL3 2010 Betti Oesterholz
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
 * This file contains the interface for image data classes.
 * Image data classes are for storing image data.
 */
/*
History:
10.04.2012  Oesterholz  created
*/

#ifndef ___I_IMAGE_DATA__
#define ___I_IMAGE_DATA__

#include "version.h"

#include "cVectorPosition.h"
#include "cVectorProperty.h"
#include "cDomains.h"


#include <list>


using std::list;

namespace fib{

class iImageData{
public:
	
	/**
	 * destructor
	 */
	virtual ~iImageData(){};

	/**
	 * This method returns the domains for the color and transparency properties.
	 *
	 * @return the domains for the color and transparency properties
	 */
	virtual cDomains getPropertyDomains() const = 0;

	/**
	 * This method returns the domains for the positions (dimension domain).
	 *
	 * @return the domains for the positions (dimension domain)
	 */
	virtual cDomains getPositionDomain() const = 0;
	
	/**
	 * With this method the properties for a points are set.
	 *
	 * @param vPosition the position of the point to set
	 * @param vProperties a list of the properties of the point
	 * @return true if the properties for the point cold be set, else false
	 */
	virtual bool setPoint(  const cVectorPosition & vPosition,
		const list<cVectorProperty> & vProperties ) = 0;
	
	/**
	 * With this method the properties for given points are returned.
	 *
	 * @param vPosition the position of the point, for which the properties
	 * 	should be returned
	 * @return a list of the properties of the point
	 */
	virtual list<cVectorProperty> getPointProperties(
		const cVectorPosition & vPosition ) const = 0;
	
	/**
	 * This method clears the data for the image.
	 */
	virtual void clear() = 0;
	
};//class iImageData

};

#endif


