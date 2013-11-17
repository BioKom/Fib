
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
 * This file implements the class for evaluing Fib objects as a RGBA image
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
 * This file implements the class for evaluing Fib objects as a RGBA image
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


//TODO switches for test proposes
//#define DEBUG


#include "cEvalueSimpleRGBA255TwoQPainter.h"

#include <QPainter>
#include <QBrush>
#include <QColor>


using namespace fib::nCreator;


/**
 * standard constructor
 *
 * @param pInFirstPainter the painter with which the image should be drawn
 * 	@see pPainter
 * @param pInSecondPainter the second painter with which the image should be drawn
 * 	@see pSecondPainter
 * @param fInHeight the height of the image so that it can be inverted
 * 	@see fHeight
 * @param dInScalingFactorRed the scaling factor for the color red
 * 	@see dScalingFactorRed
 * @param dInScalingFactorGreen the scaling factor for the color green
 * 	@see dScalingFactorGreen
 * @param dInScalingFactorBlue the scaling factor for the color blue
 * 	@see dScalingFactorBlue
 * @param dInScalingFactorGrayscale the scaling factor for the color blue
 * 	@see dScalingFactorGrayscale
 */
cEvalueSimpleRGBA255TwoQPainter::cEvalueSimpleRGBA255TwoQPainter(
		QPainter * pInFirstPainter, QPainter * pInSecondPainter,
		 const qreal fInHeight,
		const doubleFib dInScalingFactorAlpha,
		const doubleFib dInScalingFactorRed,
		const doubleFib dInScalingFactorGreen,
		const doubleFib dInScalingFactorBlue,
		const qreal dInScalingFactorGrayscale ):
		cEvalueSimpleRGBA255QPainter( pInFirstPainter, fInHeight,
			dInScalingFactorAlpha, dInScalingFactorRed,
			dInScalingFactorGreen, dInScalingFactorBlue,
			dInScalingFactorGrayscale ),
		pSecondPainter( pInSecondPainter ), fOffsetX( 0.0 ), fOffsetY( 0.0 ){
		
	DEBUG_OUT_L2(<<"cEvalueSimpleRGBA255TwoQPainter("<<this<<")::cEvalueSimpleRGBA255TwoQPainter( pInFirstPainter="<<pInFirstPainter<<", pInSecondPainter="<<pInSecondPainter<<", dInScalingFactorAlpha="<<dInScalingFactorAlpha<<", dInScalingFactorRed="<<dInScalingFactorRed<<", dInScalingFactorGreen="<<dInScalingFactorGreen<<", dInScalingFactorBlue="<<dInScalingFactorBlue<<", dInScalingFactorGrayscale="<<dInScalingFactorGrayscale<<", ) called"<<endl<<flush);
	//nothing to do
}

/**
 * template constructor
 *
 * @param pInFirstPainter the painter with which the image should be drawn
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
cEvalueSimpleRGBA255TwoQPainter::cEvalueSimpleRGBA255TwoQPainter(
		QPainter * pInFirstPainter, QPainter * pInSecondPainter,
		const cEvalueSimpleRGBA255QPainter & evalueSimpleRGBA255 ):
		cEvalueSimpleRGBA255QPainter( pInFirstPainter, evalueSimpleRGBA255 ),
		pSecondPainter( pInSecondPainter ), fOffsetX( 0.0 ), fOffsetY( 0.0 ){
	//nothing to do
	DEBUG_OUT_L2(<<"cEvalueSimpleRGBA255TwoQPainter("<<this<<")::cEvalueSimpleRGBA255TwoQPainter(  pInFirstPainter="<<pInFirstPainter<<", pInSecondPainter="<<pInSecondPainter<<", evalueSimpleRGBA255() ) called"<<endl<<flush);
}


/**
 * copy constructor
 *
 * @param evalueSimpleRGBA255 the evalueSimpleRGBA255 to copy
 */
cEvalueSimpleRGBA255TwoQPainter::cEvalueSimpleRGBA255TwoQPainter(
	cEvalueSimpleRGBA255TwoQPainter & evalueSimpleRGBA255 ):
		cEvalueSimpleRGBA255QPainter( evalueSimpleRGBA255 ),
		pSecondPainter( evalueSimpleRGBA255.pSecondPainter ),
		fOffsetX( 0.0 ), fOffsetY( 0.0 ){
	//nothing to do
	DEBUG_OUT_L2(<<"cEvalueSimpleRGBA255TwoQPainter("<<this<<")::cEvalueSimpleRGBA255TwoQPainter( evalueSimpleRGBA255() ) called"<<endl<<flush);
}


/**
 * destructor
 */
cEvalueSimpleRGBA255TwoQPainter::~cEvalueSimpleRGBA255TwoQPainter(){
	
	//nothing to do
}


/**
 * @return the name "cEvalueSimpleRGBA255TwoQPainter" of this class
 */
std::string cEvalueSimpleRGBA255TwoQPainter::getName() const{
	
	return std::string( "cEvalueSimpleRGBA255TwoQPainter" );
}


/**
 * This method draws the given point.
 *
 * @param vPosition the position of the point to draw
 * @param color the color of the point to draw
 */
void cEvalueSimpleRGBA255TwoQPainter::drawPoint(
		const cVectorPosition & vPosition, const QColor & color ){
	
	if ( vPosition.getNumberOfElements() != 0 ){
		//normal point
		pPainter->setPen( color );
		pSecondPainter->setPen( color );
		
		const qreal fX = vPosition.getValue( 1 );
		const qreal fY = fHeight - vPosition.getValue( 2 );
		
		pPainter->drawPoint( QPointF( fX, fY ) );
		pSecondPainter->drawPoint( QPointF( fX - fOffsetX, fY - fOffsetY ) );
		
		DEBUG_OUT_L4(<<"cEvalueSimpleRGBA255TwoQPainter("<<this<<")::drawPoint() draw point ("<<fX<<", "<<fY<<") with color ("<<color.redF()<<", "<<color.greenF()<<", "<<color.blueF()<<",  "<<color.alphaF()<<")"<<endl<<flush);
		
	}else{//background point
		DEBUG_OUT_L4(<<"cEvalueSimpleRGBA255TwoQPainter("<<this<<")::drawPoint() draw background with color ("<<color.redF()<<", "<<color.greenF()<<", "<<color.blueF()<<",  "<<color.alphaF()<<")"<<endl<<flush);
		pPainter->setBackground( QBrush( color ) );
		pSecondPainter->setBackground( QBrush( color ) );
	}
}


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
void cEvalueSimpleRGBA255TwoQPainter::setOffsetSecondPainter(
		const qreal & fInOffsetX, const qreal & fInOffsetY ){
	DEBUG_OUT_L2(<<"cEvalueSimpleRGBA255TwoQPainter("<<this<<")::setOffsetSecondPainter( fInOffsetX="<<fInOffsetX<<", fInOffsetY="<<fInOffsetY<<" ) called"<<endl<<flush);
	fOffsetX = fInOffsetX;
	fOffsetY = fInOffsetY;
}



