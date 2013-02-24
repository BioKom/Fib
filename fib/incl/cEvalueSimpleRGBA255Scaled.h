/**
 * @class cEvalueSimpleRGBA255Scaled
 * file name: cEvalueSimpleRGBA255Scaled.h
 * @author Betti Oesterholz
 * @date 23.02.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the class for evaluing Fib objects as a matrix of
 * a RGBA image.
 *
 * Copyright (C) @c LGPL3 2013 Betti Oesterholz
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
 * The input property vector values will be scaled with given scaling factors.
 */
/*
History:
23.02.2013  Oesterholz  created
*/

#ifndef ___C_EVALUE_SIMPLE_RGBA_255_SCALED__
#define ___C_EVALUE_SIMPLE_RGBA_255_SCALED__

#include "version.h"

#include "cEvalueSimpleRGBA255.h"
#include "iImageData.h"

#include "cVectorPosition.h"
#include "cVectorProperty.h"


#include <list>



using std::list;

namespace fib{

class cEvalueSimpleRGBA255Scaled: public virtual cEvalueSimpleRGBA255{
public:
	
	
	/**
	 * The scaling factor for the transparency values.
	 * The scaling factor should be a value, so that all evalued transparency
	 * values multiplied by the scaling factor are betwean (including) 0 and 255.
	 */
	const doubleFib dScalingFactorAlpha;
	
	/**
	 * The scaling factor for the color red.
	 * The scaling factor should be a value, so that all evalued color red
	 * values multiplied by the scaling factor are betwean (including) 0 and 255.
	 */
	const doubleFib dScalingFactorRed;
	
	/**
	 * The scaling factor for the color green.
	 * The scaling factor should be a value, so that all evalued color green
	 * values multiplied by the scaling factor are betwean (including) 0 and 255.
	 */
	const doubleFib dScalingFactorGreen;
	
	/**
	 * The scaling factor for the color blue.
	 * The scaling factor should be a value, so that all evalued color blue
	 * values multiplied by the scaling factor are betwean (including) 0 and 255.
	 */
	const doubleFib dScalingFactorBlue;
	
	
	/**
	 * standard constructor
	 * The given scaling factors should be a values, so that all evalued
	 * property values multiplied by the scaling factor are betwean
	 * (including) 0 and 255.
	 *
	 * @param uiInMaxX the maximum value for the first (x) dimension @see uiMaxX
	 * @param uiInMaxY the maximum value for the second (y) dimension @see uiMaxY
	 * @param dInScalingFactorAlpha the scaling factor for the color alpha
	 * 	@see dScalingFactorAlpha
	 * @param dInScalingFactorRed the scaling factor for the color red
	 * 	@see dScalingFactorRed
	 * @param dInScalingFactorGreen the scaling factor for the color green
	 * 	@see dScalingFactorGreen
	 * @param dInScalingFactorBlue the scaling factor for the color blue
	 * 	@see dScalingFactorBlue
	 */
	cEvalueSimpleRGBA255Scaled( const unsigned int uiInMaxX,
			const unsigned int uiInMaxY,
			const doubleFib dInScalingFactorAlpha = 1.0,
			const doubleFib dInScalingFactorRed = 1.0,
			const doubleFib dInScalingFactorGreen = 1.0,
			const doubleFib dInScalingFactorBlue = 1.0 );

	/**
	 * desstructor
	 */
	virtual ~cEvalueSimpleRGBA255Scaled();

//methods of interface iImageData:
	
	/**
	 * This method returns the domains for the color and transparency properties.
	 *
	 * @return the domains for the color and transparency properties
	 */
	virtual cDomains getPropertyDomains() const;

	/**
	 * With this method the properties for a point are set.
	 *
	 * @param vPosition the position of the point to set
	 * @param vProperties a list of the properties of the point
	 * @return true if the properties for the point cold be set, else false
	 */
	virtual bool setPoint(  const cVectorPosition & vPosition,
		const list<cVectorProperty> & vProperties );
	
	/**
	 * With this method the properties for given point are returned.
	 *
	 * @param vPosition the position of the point, for which the properties
	 * 	should be returned
	 * @return a list of the properties of the point
	 */
	virtual list<cVectorProperty> getPointProperties(
		const cVectorPosition & vPosition ) const;

	
};//class cEvalueSimpleRGBA255Scaled

};

#endif


