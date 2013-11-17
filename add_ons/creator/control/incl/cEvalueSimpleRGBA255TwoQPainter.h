
//TODO check


/**
 * @class cEvalueSimpleRGBA255TwoQPainter
 * file name: cEvalueSimpleRGBA255TwoQPainter.h
 * @author Betti Oesterholz
 * @date 12.09.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies the class for evaluing Fib objects as a RGBA image
 * and drawing it with two QPainter.
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
 * and drawing it with two QPainters.
 * Just colors and transparency is evalued. The data is drawn directly with
 * the two QPainters. Every drawn color consists of tree values with 8 bit each
 * (values from 0 to 255).
 * You have to set the QPainter pens ( setPen() ) to the correct values
 * (e. g. width) vor drawing points.
 * @see QPainter::setPen()
 */
/*
History:
12.09.2013  Oesterholz  created
*/


#ifndef ___FIB__C_EVALUE_SIMPLE_RGBA_255_TWO_QPAINTER__
#define ___FIB__C_EVALUE_SIMPLE_RGBA_255_TWO_QPAINTER__

#include "version.h"

#include "cEvalueSimpleRGBA255QPainter.h"

#include "cVectorPosition.h"
#include "cVectorProperty.h"


#include <string>

#include <QPainter>



namespace fib{

namespace nCreator{

class cEvalueSimpleRGBA255TwoQPainter: public cEvalueSimpleRGBA255QPainter{
protected:
	
	/**
	 * The second painter with which the image should be drawn.
	 */
	QPainter * pSecondPainter;
	
	/**
	 * The offset for the first / x direction / dimension for the second painter.
	 * The point ( 0, 0 ) will be the offset point. So form every point
	 * evaluated offset will be subtracted.
	 * pPainter->drawPoint( QPointF( (vPosition.getValue( 1 ) - fOffsetX),
	 * 		(vPosition.getValue( 2 ) - fOffsetY) );
	 * @see fOffsetY
	 */
	qreal fOffsetX;
	
	/**
	 * The offset for the second / y direction / dimension for the second painter.
	 * The point ( 0, 0 ) will be the offset point. So form every point
	 * evaluated offset will be subtracted.
	 * pPainter->drawPoint( QPointF( (vPosition.getValue( 1 ) - fOffsetX),
	 * 		(vPosition.getValue( 2 ) - fOffsetY) );
	 * @see fOffsetX
	 */
	qreal fOffsetY;

public:
	
	
	/**
	 * standard constructor
	 *
	 * @param pInFirstPainter the painter with which the image should be drawn
	 * 	@see pPainter
	 * @param pInSecondPainter the second painter with which the image should be drawn
	 * 	@see pSecondPainter
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
	cEvalueSimpleRGBA255TwoQPainter(
		QPainter * pInFirstPainter, QPainter * pInSecondPainter,
		const qreal fInHeight = 0.0,
		const qreal dInScalingFactorAlpha = 1.0,
		const qreal dInScalingFactorRed = 1.0,
		const qreal dInScalingFactorGreen = 1.0,
		const qreal dInScalingFactorBlue = 1.0,
		const qreal dInScalingFactorGrayscale = 1.0 );

	/**
	 * template constructor
	 *
	 * @param pInFirstPainter the first painter with which the image should be drawn
	 * 	@see pPainter
	 * @param pInSecondPainter the second painter with which the image should be drawn
	 * 	@see pSecondPainter
	 * @param evalueSimpleRGBA255 the evalueSimpleRGBA255 from which to copy
	 * 	the scaling factors
	 * 	@see dScalingFactorAlpha
	 * 	@see dScalingFactorRed
	 * 	@see dScalingFactorGreen
	 * 	@see dScalingFactorBlue
	 */
	cEvalueSimpleRGBA255TwoQPainter(
		QPainter * pInFirstPainter, QPainter * pInSecondPainter,
		const cEvalueSimpleRGBA255QPainter & evalueSimpleRGBA255 );

	/**
	 * copy constructor
	 *
	 * @param evalueSimpleRGBA255 the evalueSimpleRGBA255 to copy
	 */
	cEvalueSimpleRGBA255TwoQPainter(
		cEvalueSimpleRGBA255TwoQPainter & evalueSimpleRGBA255 );

	/**
	 * destructor
	 */
	virtual ~cEvalueSimpleRGBA255TwoQPainter();

	/**
	 * @return the name "cEvalueSimpleRGBA255TwoQPainter" of this class
	 */
	virtual std::string getName() const;
	
	/**
	 * This method draws the given point.
	 *
	 * @param vPosition the position of the point to draw
	 * @param color the color of the point to draw
	 */
	virtual void drawPoint( const cVectorPosition & vPosition,
		const QColor & color );
	
	
	/**
	 * This method sets the offset for the second painter.
	 * The point ( 0, 0 ) will be the offset point. So form every point
	 * evaluated offset will be subtracted.
	 * pPainter->drawPoint( QPointF( (vPosition.getValue( 1 ) - fOffsetX),
	 * 		(vPosition.getValue( 2 ) - fOffsetY) );
	 *
	 * @see fOffsetX
	 * @see fOffsetY
	 * @see pSecondPainter
	 * @param fInOffsetX The offset for the first / x direction / dimension
	 * @param fInOffsetX The offset for the second / y direction / dimension
	 */
	void setOffsetSecondPainter( const qreal & fInOffsetX, const qreal & fInOffsetY );
	
};//class cEvalueSimpleRGBA255TwoQPainter

};//end namespace nCreator
};//end namespace fib

#endif


