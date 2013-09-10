
//TODO check

/**
 * @file cQPainterDuplicate
 * file name: cQPainterDuplicate.h
 * @author Betti Oesterholz
 * @date 17.07.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a QPainter which duplicates some
 * QPainter method calls.
 *
 *
 * Copyright (C) @c GPL3 2013 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (GPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This file specifies a class for a QPainter which duplicates some
 * QPainter method calls.
 * See below what method calls will be duplicated.
 * If you want to paint on two QPainters with the given methods below,
 * you can use this class. One painter will be implemented by this class
 * the other will be a member of this class.
 * If you call methods to get values, just the values of the original will
 * be returned. If you want values of the other painter use
 * getOtherPainter() to get it.
 * (Mainly the draw methods will be duplicated.)
 *
 * @see QPainter
 */
/*
History:
17.07.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_Q_PAINTER_DUPLICATE_H__
#define ___FIB__NCREATOR__C_Q_PAINTER_DUPLICATE_H__


#include "version.h"


#include <string>

#include <QPainter>
#include <QPaintDevice>



namespace fib{

namespace nCreator{


class cQPainterDuplicate: public QPainter{
protected:
	
	/**
	 * A pointer to the other painter device, for which calls to this
	 * painter should be duplicated.
	 */
	QPainter * pInPainterOther;
	
public:

	/**
	 * parameter constructor for a graphics item for a Fib object
	 *
	 * @param pDevice a pointer to the paint device to paint on
	 * @see QPaintDevice
	 * @param pInPainterOther a pointer to the other painter device, for
	 * which calls to this painter should be duplicated;
	 * If NULL is given, all calls will be called to this painter twice.
	 * @see pInPainterOther
	 */
	cQPainterDuplicate( QPaintDevice * pDevice, QPainter * pInPainterOther );
	
	/**
	 * destructor
	 */
	virtual ~cQPainterDuplicate();
	
	
	
	/**
	 * @return the name of this class "cQPainterDuplicate"
	 */
	virtual std::string getName() const;
	
	/**
	 * @return a pointer to the other painter device, for  which calls to
	 * 	this painter should be duplicated;
	 */
	QPainter * getOtherPainter();
	
	/**
	 * @return a pointer to the other painter device, for  which calls to
	 * 	this painter should be duplicated;
	 */
	const QPainter * getOtherPainter() const;
	
/**
 * Methods which will be duplicated.
 */
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawArc()
	 */
	virtual void drawArc(const QRectF & rectangle, int startAngle, int spanAngle);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawArc()
	 */
	virtual void drawArc(const QRect & rectangle, int startAngle, int spanAngle);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawArc()
	 */
	virtual void drawArc(int x, int y, int width, int height, int startAngle, int spanAngle);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawChord()
	 */
	virtual void drawChord(const QRectF & rectangle, int startAngle, int spanAngle);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawChord()
	 */
	virtual void drawChord(const QRect & rectangle, int startAngle, int spanAngle);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawChord()
	 */
	virtual void drawChord(int x, int y, int width, int height, int startAngle, int spanAngle);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawConvexPolygon()
	 */
	virtual void drawConvexPolygon(const QPointF * points, int pointCount);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawConvexPolygon()
	 */
	virtual void drawConvexPolygon(const QPoint * points, int pointCount);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawConvexPolygon()
	 */
	virtual void drawConvexPolygon(const QPolygonF & polygon);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawConvexPolygon()
	 */
	virtual void drawConvexPolygon(const QPolygon & polygon);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawEllipse()
	 */
	virtual void drawEllipse(const QRectF & rectangle);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawEllipse()
	 */
	virtual void drawEllipse(const QRect & rectangle);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawEllipse()
	 */
	virtual void drawEllipse(int x, int y, int width, int height);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawEllipse()
	 */
	virtual void drawEllipse(const QPointF & center, qreal rx, qreal ry);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawEllipse()
	 */
	virtual void drawEllipse(const QPoint & center, int rx, int ry);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawGlyphRun()
	 */
	virtual void drawGlyphRun(const QPointF & position, const QGlyphRun & glyphs);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawImage()
	 */
	virtual void drawImage(const QRectF & target, const QImage & image, const QRectF & source, Qt::ImageConversionFlags flags = Qt::AutoColor);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawImage()
	 */
	virtual void drawImage(const QRect & target, const QImage & image, const QRect & source, Qt::ImageConversionFlags flags = Qt::AutoColor);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawImage()
	 */
	virtual void drawImage(const QPointF & point, const QImage & image);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawImage()
	 */
	virtual void drawImage(const QPoint & point, const QImage & image);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawImage()
	 */
	virtual void drawImage(const QPointF & point, const QImage & image, const QRectF & source, Qt::ImageConversionFlags flags = Qt::AutoColor);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawImage()
	 */
	virtual void drawImage(const QPoint & point, const QImage & image, const QRect & source, Qt::ImageConversionFlags flags = Qt::AutoColor);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawImage()
	 */
	virtual void drawImage(const QRectF & rectangle, const QImage & image);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawImage()
	 */
	virtual void drawImage(const QRect & rectangle, const QImage & image);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawImage()
	 */
	virtual void drawImage(int x, int y, const QImage & image, int sx = 0, int sy = 0, int sw = -1, int sh = -1, Qt::ImageConversionFlags flags = Qt::AutoColor);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawLine()
	 */
	virtual void drawLine(const QLineF & line);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawLine()
	 */
	virtual void drawLine(const QLine & line);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawLine()
	 */
	virtual void drawLine(const QPoint & p1, const QPoint & p2);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawLine()
	 */
	virtual void drawLine(const QPointF & p1, const QPointF & p2);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawLine()
	 */
	virtual void drawLine(int x1, int y1, int x2, int y2);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawLines()
	 */
	virtual void drawLines(const QLineF * lines, int lineCount);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawLines()
	 */
	virtual void drawLines(const QLine * lines, int lineCount);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawLines()
	 */
	virtual void drawLines(const QPointF * pointPairs, int lineCount);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawLines()
	 */
	virtual void drawLines(const QPoint * pointPairs, int lineCount);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawLines()
	 */
	virtual void drawLines(const QVector<QPointF> & pointPairs);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawLines()
	 */
	virtual void drawLines(const QVector<QPoint> & pointPairs);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawLines()
	 */
	virtual void drawLines(const QVector<QLineF> & lines);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawLines()
	 */
	virtual void drawLines(const QVector<QLine> & lines);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPath()
	 */
	virtual void drawPath(const QPainterPath & path);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPicture()
	 */
	virtual void drawPicture(const QPointF & point, const QPicture & picture);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPicture()
	 */
	virtual void drawPicture(const QPoint & point, const QPicture & picture);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPicture()
	 */
	virtual void drawPicture(int x, int y, const QPicture & picture);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPie()
	 */
	virtual void drawPie(const QRectF & rectangle, int startAngle, int spanAngle);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPie()
	 */
	virtual void drawPie(const QRect & rectangle, int startAngle, int spanAngle);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPie()
	 */
	virtual void drawPie(int x, int y, int width, int height, int startAngle, int spanAngle);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPixmap()
	 */
	virtual void drawPixmap(const QRectF & target, const QPixmap & pixmap, const QRectF & source);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPixmap()
	 */
	virtual void drawPixmap(const QRect & target, const QPixmap & pixmap, const QRect & source);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPixmap()
	 */
	virtual void drawPixmap(const QPointF & point, const QPixmap & pixmap, const QRectF & source);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPixmap()
	 */
	virtual void drawPixmap(const QPoint & point, const QPixmap & pixmap, const QRect & source);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPixmap()
	 */
	virtual void drawPixmap(const QPointF & point, const QPixmap & pixmap);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPixmap()
	 */
	virtual void drawPixmap(const QPoint & point, const QPixmap & pixmap);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPixmap()
	 */
	virtual void drawPixmap(int x, int y, const QPixmap & pixmap);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPixmap()
	 */
	virtual void drawPixmap(const QRect & rectangle, const QPixmap & pixmap);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPixmap()
	 */
	virtual void drawPixmap(int x, int y, int width, int height, const QPixmap & pixmap);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPixmap()
	 */
	virtual void drawPixmap(int x, int y, int w, int h, const QPixmap & pixmap, int sx, int sy, int sw, int sh);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPixmap()
	 */
	virtual void drawPixmap(int x, int y, const QPixmap & pixmap, int sx, int sy, int sw, int sh);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPixmapFragments()
	 */
	virtual void drawPixmapFragments(const PixmapFragment * fragments, int fragmentCount, const QPixmap & pixmap, PixmapFragmentHints hints = 0);
	
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPoint()
	 */
	virtual void drawPoint(const QPointF & position);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPoint()
	 */
	virtual void drawPoint(const QPoint & position);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPoint()
	 */
	virtual void drawPoint(int x, int y);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPoints()
	 */
	virtual void drawPoints(const QPointF * points, int pointCount);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPoints()
	 */
	virtual void drawPoints(const QPoint * points, int pointCount);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPoints()
	 */
	virtual void drawPoints(const QPolygonF & points);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPoints()
	 */
	virtual void drawPoints(const QPolygon & points);
	
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPolygon()
	 */
	virtual void drawPolygon(const QPointF * points, int pointCount, Qt::FillRule fillRule = Qt::OddEvenFill);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPolygon()
	 */
	virtual void drawPolygon(const QPoint * points, int pointCount, Qt::FillRule fillRule = Qt::OddEvenFill);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPolygon()
	 */
	virtual void drawPolygon(const QPolygonF & points, Qt::FillRule fillRule = Qt::OddEvenFill);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPolygon()
	 */
	virtual void drawPolygon(const QPolygon & points, Qt::FillRule fillRule = Qt::OddEvenFill);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPolyline()
	 */
	virtual void drawPolyline(const QPointF * points, int pointCount);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPolyline()
	 */
	virtual void drawPolyline(const QPoint * points, int pointCount);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPolyline()
	 */
	virtual void drawPolyline(const QPolygonF & points);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawPolyline()
	 */
	virtual void drawPolyline(const QPolygon & points);
	
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawRect()
	 */
	virtual void drawRect(const QRectF & rectangle);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawRect()
	 */
	virtual void drawRect(const QRect & rectangle);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawRect()
	 */
	virtual void drawRect(int x, int y, int width, int height);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawRects()
	 */
	virtual void drawRects(const QRectF * rectangles, int rectCount);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawRects()
	 */
	virtual void drawRects(const QRect * rectangles, int rectCount);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawRects()
	 */
	virtual void drawRects(const QVector<QRectF> & rectangles);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawRects()
	 */
	virtual void drawRects(const QVector<QRect> & rectangles);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawRoundedRect()
	 */
	virtual void drawRoundedRect(const QRectF & rect, qreal xRadius, qreal yRadius, Qt::SizeMode mode = Qt::AbsoluteSize);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawRoundedRect()
	 */
	virtual void drawRoundedRect(const QRect & rect, qreal xRadius, qreal yRadius, Qt::SizeMode mode = Qt::AbsoluteSize);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawRoundedRect()
	 */
	virtual void drawRoundedRect(int x, int y, int w, int h, qreal xRadius, qreal yRadius, Qt::SizeMode mode = Qt::AbsoluteSize);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawStaticText()
	 */
	virtual void drawStaticText(const QPointF & topLeftPosition, const QStaticText & staticText);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawStaticText()
	 */
	virtual void drawStaticText(const QPoint & topLeftPosition, const QStaticText & staticText);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawStaticText()
	 */
	virtual void drawStaticText(int left, int top, const QStaticText & staticText);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawText()
	 */
	virtual void drawText(const QPointF & position, const QString & text);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawText()
	 */
	virtual void drawText(const QPoint & position, const QString & text);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawText()
	 */
	virtual void drawText(const QRectF & rectangle, int flags, const QString & text, QRectF * boundingRect = 0);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawText()
	 */
	virtual void drawText(const QRect & rectangle, int flags, const QString & text, QRect * boundingRect = 0);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawText()
	 */
	virtual void drawText(int x, int y, const QString & text);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawText()
	 */
	virtual void drawText(int x, int y, int width, int height, int flags, const QString & text, QRect * boundingRect = 0);
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawTiledPixmap()
	 */
	virtual void drawText(const QRectF & rectangle, const QString & text, const QTextOption & option = QTextOption());
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawTiledPixmap()
	 */
	virtual void drawTiledPixmap(const QRectF & rectangle, const QPixmap & pixmap, const QPointF & position = QPointF());
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawTiledPixmap()
	 */
	virtual void drawTiledPixmap(const QRect & rectangle, const QPixmap & pixmap, const QPoint & position = QPoint());
	
	/**
	 * This method duplicates:
	 * @see QPainter::drawTiledPixmap()
	 */
	virtual void drawTiledPixmap(int x, int y, int width, int height, const QPixmap & pixmap, int sx = 0, int sy = 0);
	
	/**
	 * This method duplicates:
	 * @see QPainter::endNativePainting()
	 */
	virtual void endNativePainting();
	
	/**
	 * This method duplicates:
	 * @see QPainter::eraseRect()
	 */
	virtual void eraseRect(const QRectF & rectangle);
	
	/**
	 * This method duplicates:
	 * @see QPainter::eraseRect()
	 */
	virtual void eraseRect(const QRect & rectangle);
	
	/**
	 * This method duplicates:
	 * @see QPainter::eraseRect()
	 */
	virtual void eraseRect(int x, int y, int width, int height);
	
	/**
	 * This method duplicates:
	 * @see QPainter::fillPath()
	 */
	virtual void fillPath(const QPainterPath & path, const QBrush & brush);
	
	/**
	 * This method duplicates:
	 * @see QPainter::fillRect()
	 */
	virtual void fillRect(const QRectF & rectangle, const QBrush & brush);
	
	/**
	 * This method duplicates:
	 * @see QPainter::fillRect()
	 */
	virtual void fillRect(int x, int y, int width, int height, Qt::BrushStyle style);
	
	/**
	 * This method duplicates:
	 * @see QPainter::fillRect()
	 */
	virtual void fillRect(const QRect & rectangle, Qt::BrushStyle style);
	
	/**
	 * This method duplicates:
	 * @see QPainter::fillRect()
	 */
	virtual void fillRect(const QRectF & rectangle, Qt::BrushStyle style);
	
	/**
	 * This method duplicates:
	 * @see QPainter::fillRect()
	 */
	virtual void fillRect(const QRect & rectangle, const QBrush & brush);
	
	/**
	 * This method duplicates:
	 * @see QPainter::fillRect()
	 */
	virtual void fillRect(const QRect & rectangle, const QColor & color);
	
	/**
	 * This method duplicates:
	 * @see QPainter::fillRect()
	 */
	virtual void fillRect(const QRectF & rectangle, const QColor & color);
	
	/**
	 * This method duplicates:
	 * @see QPainter::fillRect()
	 */
	virtual void fillRect(int x, int y, int width, int height, const QBrush & brush);
	
	/**
	 * This method duplicates:
	 * @see QPainter::fillRect()
	 */
	virtual void fillRect(int x, int y, int width, int height, const QColor & color);
	
	/**
	 * This method duplicates:
	 * @see QPainter::fillRect()
	 */
	virtual void fillRect(int x, int y, int width, int height, Qt::GlobalColor color);
	
	/**
	 * This method duplicates:
	 * @see QPainter::fillRect()
	 */
	virtual void fillRect(const QRect & rectangle, Qt::GlobalColor color);
	
	/**
	 * This method duplicates:
	 * @see QPainter::fillRect()
	 */
	virtual void fillRect(const QRectF & rectangle, Qt::GlobalColor color);
	
	/**
	 * This method duplicates:
	 * @see QPainter::resetTransform()
	 */
	virtual void resetTransform();
	
	/**
	 * This method duplicates:
	 * @see QPainter::restore()
	 */
	virtual void restore();
	
	/**
	 * This method duplicates:
	 * @see QPainter::rotate()
	 */
	virtual void rotate(qreal angle);
	
	/**
	 * This method duplicates:
	 * @see QPainter::save()
	 */
	virtual void save();
	
	/**
	 * This method duplicates:
	 * @see QPainter::scale()
	 */
	virtual void scale(qreal sx, qreal sy);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setBackground()
	 */
	virtual void setBackground(const QBrush & brush);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setBackgroundMode()
	 */
	virtual void setBackgroundMode(Qt::BGMode mode);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setBrush()
	 */
	virtual void setBrush(const QBrush & brush);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setBrush()
	 */
	virtual void setBrush(Qt::BrushStyle style);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setBrushOrigin()
	 */
	virtual void setBrushOrigin(const QPointF & position);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setBrushOrigin()
	 */
	virtual void setBrushOrigin(const QPoint & position);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setBrushOrigin()
	 */
	virtual void setBrushOrigin(int x, int y);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setClipPath()
	 */
	virtual void setClipPath(const QPainterPath & path, Qt::ClipOperation operation = Qt::ReplaceClip);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setClipRect()
	 */
	virtual void setClipRect(const QRectF & rectangle, Qt::ClipOperation operation = Qt::ReplaceClip);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setClipRect()
	 */
	virtual void setClipRect(int x, int y, int width, int height, Qt::ClipOperation operation = Qt::ReplaceClip);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setClipRect()
	 */
	virtual void setClipRect(const QRect & rectangle, Qt::ClipOperation operation = Qt::ReplaceClip);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setClipRegion()
	 */
	virtual void setClipRegion(const QRegion & region, Qt::ClipOperation operation = Qt::ReplaceClip);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setClipping()
	 */
	virtual void setClipping(bool enable);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setCompositionMode()
	 */
	virtual void setCompositionMode(CompositionMode mode);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setFont()
	 */
	virtual void setFont(const QFont & font);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setLayoutDirection()
	 */
	virtual void setLayoutDirection(Qt::LayoutDirection direction);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setOpacity()
	 */
	virtual void setOpacity(qreal opacity);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setPen()
	 */
	virtual void setPen(const QPen & pen);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setPen()
	 */
	virtual void setPen(const QColor & color);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setPen()
	 */
	virtual void setPen(Qt::PenStyle style);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setRenderHint()
	 */
	virtual void setRenderHint(RenderHint hint, bool on = true);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setRenderHints()
	 */
	virtual void setRenderHints(RenderHints hints, bool on = true);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setTransform()
	 */
	virtual void setTransform(const QTransform & transform, bool combine = false);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setViewTransformEnabled()
	 */
	virtual void setViewTransformEnabled(bool enable);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setViewport()
	 */
	virtual void setViewport(const QRect & rectangle);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setViewport()
	 */
	virtual void setViewport(int x, int y, int width, int height);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setWindow()
	 */
	virtual void setWindow(const QRect & rectangle);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setWindow()
	 */
	virtual void setWindow(int x, int y, int width, int height);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setWorldMatrixEnabled()
	 */
	virtual void setWorldMatrixEnabled(bool enable);
	
	/**
	 * This method duplicates:
	 * @see QPainter::setWorldTransform()
	 */
	virtual void setWorldTransform(const QTransform & matrix, bool combine = false);
	
	/**
	 * This method duplicates:
	 * @see QPainter::shear()
	 */
	virtual void shear(qreal sh, qreal sv);
	
	/**
	 * This method duplicates:
	 * @see QPainter::strokePath()
	 */
	virtual void strokePath(const QPainterPath & path, const QPen & pen);
	
	/**
	 * This method duplicates:
	 * @see QPainter::testRenderHint()
	 */
	virtual bool testRenderHint(RenderHint hint) const;
	
	/**
	 * This method duplicates:
	 * @see QPainter::translate()
	 */
	virtual void translate(const QPointF & offset);
	
	/**
	 * This method duplicates:
	 * @see QPainter::translate()
	 */
	virtual void translate(const QPoint & offset);
	
	/**
	 * This method duplicates:
	 * @see QPainter::translate()
	 */
	virtual void translate(qreal dx, qreal dy);
	
	
};//end class cQPainterDuplicate

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_Q_PAINTER_DUPLICATE_H__





