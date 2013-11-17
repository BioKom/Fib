
//TODO check


/**
 * @class cEvalueSimpleRGBA255QPainter
 * file name: cEvalueSimpleRGBA255QPainter.h
 * @author Betti Oesterholz
 * @date 21.07.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies the class for evaluing Fib objects as a RGBA image
 * and drawing it with a QPainter.
 *
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
 * This file specifies the class for evaluing Fib objects as a RGBA image
 * and drawing it with a QPainter.
 * Just colors and transparency is evalued. The data is drawn directly with
 * the QPainter. Every drawn color consists of tree values with 8 bit each
 * (values from 0 to 255).
 * You have to set the QPainter pen ( setPen() ) to the correct values
 * (e. g. width) vor drawing points.
 * @see QPainter::setPen()
 */
/*
History:
21.07.2013  Oesterholz  created
*/


/*TODO set outside
 * 
	QPainter::setBackgroundMode( Qt::OpaqueMode )
*/


#ifndef ___FIB__C_EVALUE_SIMPLE_RGBA_255_QPAINTER__
#define ___FIB__C_EVALUE_SIMPLE_RGBA_255_QPAINTER__

#include "version.h"

#include "iEvaluePosition.h"

#include "cVectorPosition.h"
#include "cVectorProperty.h"


#include <string>

#include <QPainter>



namespace fib{

namespace nCreator{

class cEvalueSimpleRGBA255QPainter: public virtual iEvaluePosition{
protected:
	
	/**
	 * The painter with which the image should be drawn.
	 */
	QPainter * pPainter;
	
	/**
	 * The scaling factor for the transparency values.
	 * The scaling factor should be a value, so that all evalued transparency
	 * values multiplied by the scaling factor are betwean (including) 0 and 1 .
	 */
	const qreal dScalingFactorAlpha;
	
	/**
	 * The scaling factor for the color red.
	 * The scaling factor should be a value, so that all evalued color red
	 * values multiplied by the scaling factor are betwean (including) 0 and 1 .
	 */
	const qreal dScalingFactorRed;
	
	/**
	 * The scaling factor for the color green.
	 * The scaling factor should be a value, so that all evalued color green
	 * values multiplied by the scaling factor are betwean (including) 0 and 1 .
	 */
	const qreal dScalingFactorGreen;
	
	/**
	 * The scaling factor for the color blue.
	 * The scaling factor should be a value, so that all evalued color blue
	 * values multiplied by the scaling factor are betwean (including) 0 and 1 .
	 */
	const qreal dScalingFactorBlue;
	
	/**
	 * The scaling factor for the grayscale color.
	 * The scaling factor should be a value, so that all evalued grayscale
	 * color values multiplied by the scaling factor are betwean (including)
	 * 0 and 1 .
	 */
	const qreal dScalingFactorGrayscale;
	
	/**
	 * If true a point was evalued, else no point was evalued by this object.
	 * needed to evalue the boundingRectangle.
	 * @see boundingRectangle
	 */
	bool bPointEvalued;
	
	/**
	 * The height of the image so that it can be inverted.
	 * All vertical positions y will be ( fHeight - position.getValue( 2 ) ) .
	 */
	qreal fHeight;
	
public:
	
	/**
	 * The bounding rectangle of the evalued points.
	 * @see bPointEvalued
	 */
	QRectF boundingRectangle;
	
	
	/**
	 * standard constructor
	 *
	 * @param pInPainter the painter with which the image should be drawn
	 * 	@see pPainter
	 * @param fInHeight the height of the image so that it can be inverted
	 * 	@see fHeight
	 * @param dInScalingFactorAlpha the scaling factor for the color alpha
	 * 	@see dScalingFactorAlpha
	 * @param dInScalingFactorRed the scaling factor for the color red
	 * 	@see dScalingFactorRed
	 * @param dInScalingFactorGreen the scaling factor for the color green
	 * 	@see dScalingFactorGreen
	 * @param dInScalingFactorBlue the scaling factor for the color blue
	 * 	@see dScalingFactorBlue
	 * @param dInScalingFactorGrayscale the scaling factor for the color blue
	 * 	@see dScalingFactorGrayscale
	 */
	cEvalueSimpleRGBA255QPainter(
		QPainter * pInPainter, const qreal fInHeight = 0.0,
		const qreal dInScalingFactorAlpha = 1.0,
		const qreal dInScalingFactorRed = 1.0,
		const qreal dInScalingFactorGreen = 1.0,
		const qreal dInScalingFactorBlue = 1.0,
		const qreal dInScalingFactorGrayscale = 1.0 );

	/**
	 * template constructor
	 *
	 * @param pInPainter the painter with which the image should be drawn
	 * 	@see pPainter
	 * @param evalueSimpleRGBA255 the evalueSimpleRGBA255 from which to copy
	 * 	the scaling factors
	 * 	@see dScalingFactorAlpha
	 * 	@see dScalingFactorRed
	 * 	@see dScalingFactorGreen
	 * 	@see dScalingFactorBlue
	 */
	cEvalueSimpleRGBA255QPainter(
		QPainter * pInPainter,
		const cEvalueSimpleRGBA255QPainter & evalueSimpleRGBA255 );

	/**
	 * copy constructor
	 *
	 * @param evalueSimpleRGBA255 the evalueSimpleRGBA255 to copy
	 */
	cEvalueSimpleRGBA255QPainter(
		cEvalueSimpleRGBA255QPainter & evalueSimpleRGBA255 );

	/**
	 * destructor
	 */
	virtual ~cEvalueSimpleRGBA255QPainter();

	/**
	 * @return the name "cEvalueSimpleRGBA255QPainter" of this class
	 */
	virtual std::string getName() const;
	
	/**
	 * The method with wich the evalued points with ther properties are
	 * inserted. Everytime a point (to evalue) is reached in the
	 * evaluation, this method is called with the position and the
	 * properties of the point and stores the data into @see pImageData
	 * This method will just evalue two dimensional points and properties
	 * for RGB and transparency.
	 * Points first dimension can have values from 0 ( including ) to the
	 * maximum value for the first (x) dimension.
	 * 	( 0 =< vPosition.getValue( 1 ) < uiBorderIndexX ) @see uiBorderIndexX
	 * Points second dimension ( vPosition.getValue( 2 ) ) can have values
	 * from 0 ( including ) to the maximum value for the second (y) dimension.
	 * 	( 0 =< vPosition.getValue( 2 ) < uiBorderIndexY ) @see uiBorderIndexY
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
	 * This method draws the given point.
	 *
	 * @param vPosition the position of the point to draw
	 * @param color the color of the point to draw
	 */
	virtual void drawPoint( const cVectorPosition & vPosition,
		const QColor & color );
	
	/**
	 * @return scaling factor for the transparency values
	 * 	@see dScalingFactorAlpha
	 */
	qreal getScalingFactorAlpha() const;
	
	/**
	 * @return scaling factor for the red values
	 * 	@see dScalingFactorRed
	 */
	qreal getScalingFactorRed() const;
	
	/**
	 * @return scaling factor for the green values
	 * 	@see dScalingFactorGreen
	 */
	qreal getScalingFactorGreen() const;
	
	/**
	 * @return scaling factor for the blue values
	 * 	@see dScalingFactorBlue
	 */
	qreal getScalingFactorBlue() const;
	
	/**
	 * @return scaling factor for the grayscale values
	 * 	@see dScalingFactorGrayscale
	 */
	qreal getScalingFactorGrayscale() const;
	
	
	/**
	 * @return the height of the image so that it can be inverted
	 * 	All vertical positions y will be ( fHeight - position.getValue( 2 ) )
	 * 	@see fHeight
	 */
	qreal getHeight() const;

	/**
	 * @param fInHeight the height of the image so that it can be inverted
	 * 	All vertical positions y will be ( fHeight - position.getValue( 2 ) )
	 * 	@see fHeight
	 */
	void setHeight( const qreal & fInHeight );
	
};//class cEvalueSimpleRGBA255QPainter

};//end namespace nCreator
};//end namespace fib

#endif


