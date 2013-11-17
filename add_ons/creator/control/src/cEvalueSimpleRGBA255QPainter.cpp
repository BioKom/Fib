
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
 * This file implements the class for evaluing Fib objects as a RGBA image
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
 * This file implements the class for evaluing Fib objects as a RGBA image
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


//TODO switches for test proposes
//#define DEBUG


#include "cEvalueSimpleRGBA255QPainter.h"

#include <QPainter>
#include <QBrush>
#include <QColor>


using namespace fib::nCreator;


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
cEvalueSimpleRGBA255QPainter::cEvalueSimpleRGBA255QPainter(
	QPainter * pInPainter, const qreal fInHeight,
	const doubleFib dInScalingFactorAlpha,
	const doubleFib dInScalingFactorRed,
	const doubleFib dInScalingFactorGreen,
	const doubleFib dInScalingFactorBlue,
		const qreal dInScalingFactorGrayscale ):
		pPainter( pInPainter ),
		dScalingFactorAlpha( dInScalingFactorAlpha ),
		dScalingFactorRed( dInScalingFactorRed ),
		dScalingFactorGreen( dInScalingFactorGreen ),
		dScalingFactorBlue( dInScalingFactorBlue ),
		dScalingFactorGrayscale( dInScalingFactorGrayscale ),
		bPointEvalued( false ), fHeight( fInHeight ), boundingRectangle(){
		
	DEBUG_OUT_L2(<<"cEvalueSimpleRGBA255QPainter("<<this<<")::cEvalueSimpleRGBA255QPainter( pInPainter="<<pInPainter<<", dInScalingFactorAlpha="<<dInScalingFactorAlpha<<", dInScalingFactorRed="<<dInScalingFactorRed<<", dInScalingFactorGreen="<<dInScalingFactorGreen<<", dInScalingFactorBlue="<<dInScalingFactorBlue<<", dInScalingFactorGrayscale="<<dInScalingFactorGrayscale<<", ) called"<<endl<<flush);
	//nothing to do
}

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
cEvalueSimpleRGBA255QPainter::cEvalueSimpleRGBA255QPainter(
	QPainter * pInPainter,
	const cEvalueSimpleRGBA255QPainter & evalueSimpleRGBA255 ):
		pPainter( pInPainter ),
		dScalingFactorAlpha( evalueSimpleRGBA255.dScalingFactorAlpha ),
		dScalingFactorRed( evalueSimpleRGBA255.dScalingFactorRed ),
		dScalingFactorGreen( evalueSimpleRGBA255.dScalingFactorGreen ),
		dScalingFactorBlue( evalueSimpleRGBA255.dScalingFactorBlue ),
		dScalingFactorGrayscale( evalueSimpleRGBA255.dScalingFactorGrayscale ),
		bPointEvalued( false ), fHeight( evalueSimpleRGBA255.fHeight ),
		boundingRectangle(){
	//nothing to do
	DEBUG_OUT_L2(<<"cEvalueSimpleRGBA255QPainter("<<this<<")::cEvalueSimpleRGBA255QPainter(  pPainter="<<pInPainter<<", evalueSimpleRGBA255( dScalingFactorAlpha="<<evalueSimpleRGBA255.dScalingFactorAlpha<<", dScalingFactorRed="<<evalueSimpleRGBA255.dScalingFactorRed<<", dScalingFactorGreen="<<evalueSimpleRGBA255.dScalingFactorGreen<<", dScalingFactorBlue="<<evalueSimpleRGBA255.dScalingFactorBlue<<", dScalingFactorGrayscale="<<evalueSimpleRGBA255.dScalingFactorGrayscale<<", ) called"<<endl<<flush);
}


/**
 * copy constructor
 *
 * @param evalueSimpleRGBA255 the evalueSimpleRGBA255 to copy
 */
cEvalueSimpleRGBA255QPainter::cEvalueSimpleRGBA255QPainter(
	cEvalueSimpleRGBA255QPainter & evalueSimpleRGBA255 ):
		pPainter( evalueSimpleRGBA255.pPainter ),
		dScalingFactorAlpha( evalueSimpleRGBA255.dScalingFactorAlpha ),
		dScalingFactorRed( evalueSimpleRGBA255.dScalingFactorRed ),
		dScalingFactorGreen( evalueSimpleRGBA255.dScalingFactorGreen ),
		dScalingFactorBlue( evalueSimpleRGBA255.dScalingFactorBlue ),
		dScalingFactorGrayscale( evalueSimpleRGBA255.dScalingFactorGrayscale ),
		bPointEvalued( evalueSimpleRGBA255.bPointEvalued ),
		fHeight( evalueSimpleRGBA255.fHeight ),
		boundingRectangle( evalueSimpleRGBA255.boundingRectangle ){
	//nothing to do
	DEBUG_OUT_L2(<<"cEvalueSimpleRGBA255QPainter("<<this<<")::cEvalueSimpleRGBA255QPainter(  evalueSimpleRGBA255( pPainter="<<evalueSimpleRGBA255.pPainter<<", dScalingFactorAlpha="<<evalueSimpleRGBA255.dScalingFactorAlpha<<", dScalingFactorRed="<<evalueSimpleRGBA255.dScalingFactorRed<<", dScalingFactorGreen="<<evalueSimpleRGBA255.dScalingFactorGreen<<", dScalingFactorBlue="<<evalueSimpleRGBA255.dScalingFactorBlue<<", dScalingFactorGrayscale="<<evalueSimpleRGBA255.dScalingFactorGrayscale<<", ) called"<<endl<<flush);
}


/**
 * destructor
 */
cEvalueSimpleRGBA255QPainter::~cEvalueSimpleRGBA255QPainter(){
	
	//nothing to do
}


/**
 * @return the name "cEvalueSimpleRGBA255QPainter" of this class
 */
std::string cEvalueSimpleRGBA255QPainter::getName() const{
	
	return std::string( "cEvalueSimpleRGBA255QPainter" );
}


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
bool cEvalueSimpleRGBA255QPainter::evaluePosition( const cVectorPosition & vPosition,
	const list<cVectorProperty> & vProperties ){
	
	//(re-)evalue the bounding box
	if ( vPosition.getNumberOfElements() != 0 ){
		//normal point
		const qreal fX = vPosition.getValue( 1 );
		const qreal fY = fHeight - vPosition.getValue( 2 );
		//(re-)evalue bounding box
		if ( bPointEvalued ){
			if ( ! boundingRectangle.contains( fX, fY ) ){
				//point not in bounding box -> enlarge bounding box if needed
				boundingRectangle.setLeft(
					qMin( boundingRectangle.left(), fX ) );
				boundingRectangle.setRight(
					qMax( boundingRectangle.right(), fX + 1 ) );
				boundingRectangle.setTop(
					qMin( boundingRectangle.top(), fY ) );
				boundingRectangle.setBottom(
					qMax( boundingRectangle.bottom(), fY + 1 ) );
			}//else point in bounding box -> do nothing
		}else{//first point to add to the bounding box -> bounding box = point
			boundingRectangle.setRect( fX, fY, 1, 1 );
			bPointEvalued = true;
		}
	}//end if evalue bounding box
	if ( pPainter == NULL ){
		//no painter -> done
		return true;
	}
	
	//the color of the point
	QColor color( 0, 0, 0, 0 );
	
	/*the last found alpha value for the point;
	 init with 1 because transparency standard value is 0*/
	qreal fLastAlpha = 1.0;
	
	bool bNoAlpha = true;//no transparency property set
	
	for ( list<cVectorProperty>::const_iterator
			itrProperty = vProperties.begin();
			itrProperty != vProperties.end(); itrProperty++ ){
		
		const unsignedIntFib uiPropertytype = itrProperty->getPropertyType();
		
		if ( uiPropertytype == cTypeProperty::COLOR_RGB ){
			//RGB color:
			//color_new = color_actual * alpha_last + color_matrix * alpha_matrix * ( 1 - alpha_last )
			if ( bNoAlpha ){
				//no transparency -> transparency = 0 -> alpha = 1
				color.setAlphaF( 1.0 );
				bNoAlpha = false;
			}
			const qreal fAlphaMatrix = color.alphaF();
			
			//red
			const qreal fRed = itrProperty->getValue( 1 ) *
				dScalingFactorRed * fLastAlpha +
				(color.redF() * fAlphaMatrix * ( 1.0 - fLastAlpha ) );
			color.setRedF(
				( fRed <= 0.0) ? 0.0 : ( ( 1.0 <= fRed )? 1.0 : fRed ) );
			//green
			const qreal fGreen = itrProperty->getValue( 2 ) *
				dScalingFactorGreen * fLastAlpha +
				(color.greenF() * fAlphaMatrix * ( 1.0 - fLastAlpha ) );
			color.setGreenF(
				( fGreen <= 0.0) ? 0.0 : ( ( 1.0 <= fGreen )? 1.0 : fGreen ) );
			//blue
			const qreal fBlue = itrProperty->getValue( 3 ) *
				dScalingFactorBlue * fLastAlpha +
				(color.blueF() * fAlphaMatrix * ( 1.0 - fLastAlpha ) );
			color.setBlueF(
				( fBlue <= 0.0) ? 0.0 : ( ( 1.0 <= fBlue )? 1.0 : fBlue ) );
			
		}else if ( uiPropertytype == cTypeProperty::TRANSPARENCY ){
			//transparency
			// alpha_new = alpha_matrix + alpha_new ( 1 - alpha_matrix )
			const qreal fTransparency =
				itrProperty->getValue( 1 ) * dScalingFactorAlpha;
			//alpha_new = 255 - transparency;
			fLastAlpha *= ( fTransparency <= 0 ) ? 1.0 :
				( 1.0 < fTransparency ) ? 0.0 : (1.0 - fTransparency);
			
			//alpha_matrix_new = 255.0 * fLastAlpha );
			color.setAlphaF( ( fLastAlpha <= 0.0) ?
				0.0 : ( ( 1.0 <= fLastAlpha )? 1.0 : fLastAlpha ) );
			
			bNoAlpha = false;//transparency value set
		}else if ( uiPropertytype == cTypeProperty::COLOR_GRAYSCALE ){
			//grayscale color:
			//color_new = color_actual * alpha_last + color_matrix * alpha_matrix * ( 1 - alpha_last )
			if ( bNoAlpha ){
				//no transparency -> transparency = 0 -> alpha = 1
				color.setAlpha( 255 );
				bNoAlpha = false;
			}
			const qreal fAlphaMatrix = color.alphaF();
			
			//set all tree color values to the same value (=grayscale)
			const qreal fColorGrayscale =
				itrProperty->getValue( 1 ) * dScalingFactorGrayscale * fLastAlpha;
			
			//red
			const qreal fRed = fColorGrayscale +
				( color.redF() * fAlphaMatrix * ( 1.0 - fLastAlpha ) );
			color.setRedF(
				( fRed <= 0.0) ? 0.0 : ( ( 1.0 <= fRed )? 1.0 : fRed ) );
			//green
			const qreal fGreen = fColorGrayscale +
				( color.greenF() * fAlphaMatrix * ( 1.0 - fLastAlpha ) );
			color.setGreenF(
				( fGreen <= 0.0) ? 0.0 : ( ( 1.0 <= fGreen )? 1.0 : fGreen ) );
			//blue
			const qreal fBlue = fColorGrayscale +
				( color.blueF() * fAlphaMatrix * ( 1.0 - fLastAlpha ) );
			color.setBlueF(
				( fBlue <= 0.0) ? 0.0 : ( ( 1.0 <= fBlue )? 1.0 : fBlue ) );
		}//else discard property
		
	}//end for all properties for the point
	
	drawPoint( vPosition, color );
	
	return true;
}


/**
 * This method draws the given point.
 *
 * @param vPosition the position of the point to draw
 * @param color the color of the point to draw
 */
void cEvalueSimpleRGBA255QPainter::drawPoint(
		const cVectorPosition & vPosition, const QColor & color ){
	
	if ( vPosition.getNumberOfElements() != 0 ){
		//normal point
		pPainter->setPen( color );
		
		const qreal fX = vPosition.getValue( 1 );
		const qreal fY = fHeight - vPosition.getValue( 2 );
		pPainter->drawPoint( QPointF( fX, fY ) );
		DEBUG_OUT_L4(<<"cEvalueSimpleRGBA255QPainter("<<this<<")::drawPoint() draw point ("<<fX<<", "<<fY<<") with color ("<<color.redF()<<", "<<color.greenF()<<", "<<color.blueF()<<",  "<<color.alphaF()<<")"<<endl<<flush);
		
	}else{//background point
		DEBUG_OUT_L4(<<"cEvalueSimpleRGBA255QPainter("<<this<<")::drawPoint() draw background with color ("<<color.redF()<<", "<<color.greenF()<<", "<<color.blueF()<<",  "<<color.alphaF()<<")"<<endl<<flush);
		pPainter->setBackground( QBrush( color ) );
	}
}


/**
 * @return scaling factor for the transparency values
 * 	@see dScalingFactorAlpha
 */
qreal cEvalueSimpleRGBA255QPainter::getScalingFactorAlpha() const{
	
	return dScalingFactorAlpha;
}


/**
 * @return scaling factor for the red values
 * 	@see dScalingFactorRed
 */
qreal cEvalueSimpleRGBA255QPainter::getScalingFactorRed() const{
	
	return dScalingFactorRed;
}


/**
 * @return scaling factor for the green values
 * 	@see dScalingFactorGreen
 */
qreal cEvalueSimpleRGBA255QPainter::getScalingFactorGreen() const{
	
	return dScalingFactorGreen;
}


/**
 * @return scaling factor for the blue values
 * 	@see dScalingFactorBlue
 */
qreal cEvalueSimpleRGBA255QPainter::getScalingFactorBlue() const{
	
	return dScalingFactorBlue;
}


/**
 * @return scaling factor for the grayscale values
 * 	@see dScalingFactorGrayscale
 */
qreal cEvalueSimpleRGBA255QPainter::getScalingFactorGrayscale() const{
	
	return dScalingFactorGrayscale;
}


/**
 * @return the height of the image so that it can be inverted
 * 	All vertical positions y will be ( fHeight - position.getValue( 2 ) )
 * 	@see fHeight
 */
qreal cEvalueSimpleRGBA255QPainter::getHeight() const{
	
	return fHeight;
}


/**
 * @param fInHeight the height of the image so that it can be inverted
 * 	All vertical positions y will be ( fHeight - position.getValue( 2 ) )
 * 	@see fHeight
 */
void cEvalueSimpleRGBA255QPainter::setHeight( const qreal & fInHeight ){
	
	fHeight = fInHeight;
}



