
//TODO check

/**
 * @file cFibGraphicsScene
 * file name: cFibGraphicsScene.h
 * @author Betti Oesterholz
 * @date 15.07.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for the graphics view of a Fib object.
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
 * This file specifies a class for the graphics view of a Fib object.
 * It will display the Fib object as an graphic scene / image.
 * For that it will analyse a Fib objects, create and add Fib graphic items
 * cFibGraphicsItem for its parts, so that in the end all Fib graphic
 * items together will look like the image the Fib object represents.
 * The cFibGraphicsItem can provide means to interact with them and via
 * them with the Fib object.
 *
 * @see cFibObjectMainWindow
 * @see QGraphicsScene
 * @see cFibGraphicsItem
 * @see QGraphicsItem
 * @see QGraphicsView
 * @pattern Factory Method
 * @see iFibGraphicsItemFactory
 * @see cFibGraphicsItemImageFactory
 */
/*
History:
15.07.2013  Oesterholz  created
25.01.2013  Oesterholz  the graphical items will be updated, if possible,
	with the information of the Fib node change event
13.04.2014  Oesterholz  mousePressEvent() insert selected Fib object
*/


#ifndef ___FIB__NCREATOR__C_FIB_GRAPHICS_SCENE_H__
#define ___FIB__NCREATOR__C_FIB_GRAPHICS_SCENE_H__


#include "version.h"

#include "fibDatatyps.h"

#include "lFibNodeChanged.h"

#include <set>
#include <string>

#include <QGraphicsScene>
#include <QList>
#include <QMutex>


namespace fib{

//forward declarations
class cFibElement;
class cFibVariable;
class cDomain;

namespace nCreator{

//forward declarations
class cFibObjectMainWindow;
class cFibNode;
class cFibNodeHandler;
class cFibGraphicsItem;
class cWidgetFibInputVariables;
class cEvalueSimpleRGBA255QPainter;

class cFibGraphicsScene: public QGraphicsScene, public lFibNodeChanged{
		Q_OBJECT
public:

	/**
	 * parameter constructor for a graphics view of a Fib object
	 *
	 * @param pInFibNode a pointer to the Fib node object for the widget to construct
	 * 	@see pFibNode
	 * @param pParent a pointer to parent of this widget
	 */
	explicit cFibGraphicsScene( cFibNode * pInFibNode, QWidget * pParent = NULL );
	
	/**
	 * parameter constructor for a graphics view of a Fib object
	 *
	 * @param pInFibNode a pointer to the Fib node object for the widget to construct
	 * 	@see pFibNode
	 * @param pInMainWindow a pointer to the main window for this widget
	 * 	@see pMainWindow
	 */
	cFibGraphicsScene( cFibNode * pInFibNode, cFibObjectMainWindow * pInMainWindow );
	
	/**
	 * A parameter constructor for a graphics view of a Fib object
	 *
	 * @param pInFibObject a pointer to the Fib object for the widget to
	 * 	construct, the node for it will be used as the Fib node for this
	 * 	Fib graphic scene; use this constructor if you need a listener for
	 * 	node changes (this object will be added as a listener)
	 * 	@see pFibNode
	 * 	@see cFibNodeHandler::getNodeForFibObject()
	 * @param pParent a pointer to parent of this widget
	 */
	explicit cFibGraphicsScene( cFibElement * pInFibObject, QWidget * pParent = NULL );
	
	/**
	 * destructor
	 */
	virtual ~cFibGraphicsScene();
	
	
	// TODO? build interface iShowFibNode with the next 3 or 4 or 5 methods
	
	/**
	 * @return a pointer to the Fib node object this widget shows / represents
	 * 	@see pFibNode
	 */
	cFibNode * getFibNode();
	
	/**
	 * @return a const pointer to the Fib node object this widget shows / represents
	 * 	@see pFibNode
	 */
	const cFibNode * getFibNode() const;
	
	/**
	 * This method will set the given Fib (node) object in this widget.
	 * Beware: If the Fib (node) object was set (returned true) the Fib node
	 * 	handler will handel the given Fib object (e. g. It will delete the
	 * 	Fib object, so don't delete it yourself).
	 * @see cFibNodeHandler
	 *
	 * @param pNewFibObject a pointer to the Fib object to set for this widget
	 * @return true if the given Fib object was set, else false
	 */
	virtual bool setFibObjectNode( cFibNode * pNewFibObjectNode );
	
	/**
	 * Event method
	 * It will be called every time a Fib node (cFibNode), at which
	 * this object is registered, was changed.
	 *
	 * @param pFibNode a pointer to the changed Fib node
	 */
	virtual void fibNodeChangedEvent(
		const eFibNodeChangedEvent * pFibNodeChanged );
	
	
	/*TODO? input variables into own class (?so they can be used by all views?)
	 + input variables view: cInputVariablesView*/

	/**
	 * This method will return the number of input variables for the Fib
	 * object for the Fib node.
	 *
	 * @see pFibNode
	 * @see pWidgetInputVariables
	 * @see evalueInputVariables()
	 * @see getInputVariablesWidget()
	 * @return the number of input variables for the Fib object for the Fib node
	 */
	unsigned int getNumberOfInputVariables() const;
	
	/**
	 * This method sets the input variable widgets.
	 *
	 * @see pFibNode
	 * @see pWidgetInputVariables
	 * @see evalueInputVariables()
	 * @see getNumberOfInputVariables()
	 * @param pNewWidgetFibInputVariables a pointer to the widget with the
	 * 	input variables to set
	 * 	Beware: This object will handle the given widget object (e.g. it will delete it).
	 */
	void setInputVariablesWidget( cWidgetFibInputVariables * pNewWidgetFibInputVariables );
	
	/**
	 * @see pFibNode
	 * @see pWidgetInputVariables
	 * @see evalueInputVariables()
	 * @see getNumberOfInputVariables()
	 * @return a pointer to the widget with the input variables
	 */
	cWidgetFibInputVariables * getInputVariablesWidget();
	
	/**
	 * @see pFibNode
	 * @see pWidgetInputVariables
	 * @see evalueInputVariables()
	 * @see getNumberOfInputVariables()
	 * @return a pointer to the widget with the input variables
	 */
	const cWidgetFibInputVariables * getInputVariablesWidget() const;
	
	/**
	 * This method will return a pointer cEvalueSimpleRGBA255QPainter
	 * template for this graphic scene.
	 * If existing, this painter will contain the enviroment / domain
	 * information to paint a Fib object into this graphic scene.
	 * The object can be used with the template constructor of the
	 * cEvalueSimpleRGBA255QPainter to construct a cEvalueSimpleRGBA255QPainter
	 * object which has the correct enviroment parameters set and uses
	 * the actual painter (QPainter) object.
	 * If you use this cEvalueSimpleRGBA255QPainter template, you have still
	 * to adapt the QPainter for painting (e.g. you have to set the QPainter
	 * pen ( setPen() ) to the correct values (e. g. width) vor drawing points.)
	 *
	 * @see pEvalueSimpleRGBA255QPainter
	 * @see cEvalueSimpleRGBA255QPainter( QPainter * pInPainter, const cEvalueSimpleRGBA255QPainter & evalueSimpleRGBA255 );
	 * @see QPainter
	 * @see pFibRootNode
	 * @return return a pointer cEvalueSimpleRGBA255QPainter
	 * 	template for this graphic scene, or NULL if non exists
	 */
	const cEvalueSimpleRGBA255QPainter * getEvalueSimpleRGBA255QPainter() const;
	
	/**
	 * This method will set the pen of the given to match the pixle / point
	 * dimensions of the Fib object of displayed Fib object.
	 *
	 * @see dPointWidth
	 * @see dPointHeight
	 * @see updateForDimensionChange()
	 * @see pFibNode
	 * @return true if the pen was set, else false
	 */
	bool setPenForPointSize( QPainter * pPainter ) const;
	
	/**
	 * This method returns the size of a point.
	 *
	 * @see dPointWidth
	 * @see dPointHeight
	 * @see setPenForPointSize()
	 * @see updateForDimensionChange()
	 * @see pFibNode
	 * @return the size of a point
	 */
	QSizeF getPointSize() const;
	
	/**
	 * @return the name of this class "cFibGraphicsScene"
	 */
	virtual std::string getName() const;
	
	
public slots:
	
	/**
	 * This method evalue the input variables for the Fib object for the
	 * Fib node.
	 * It will evalue all variables used in the Fib object, but not defined
	 * in it.
	 * New input variables will be set to the default value 0 .
	 *
	 * @see signalEvalueInputVariable()
	 * @see pFibNode
	 * @see pWidgetInputVariables
	 * @see getNumberOfInputVariables()
	 * @see getInputVariablesWidget()
	 * @return true if the input variables for the Fib object for the node
	 * 	could be set, else false (and no input variables set)
	 */
	bool evalueInputVariables();
	
	/**
	 * This slot will notify the Fib node that it was changed, if the scene
	 * for the Fib object was changed.
	 * This method should be called if the Fib object scene of this widget
	 * changes. It will then try to create the Fib object of this scene.
	 * If it was successfull, it will adapt / replace the Fib node
	 * Fib object with the Fib object of this scene and notify the node that
	 * it was changed.
	 * @see fibNodeChangedEvent()
	 */
	void notifyNodeForChange();
	
	/**
	 * This slot will notify the Fib node that it was changed, if the scene
	 * for the Fib object was changed.
	 * This method should be called if the Fib object scene of this widget
	 * changes. It will then try to create the Fib object of this scene.
	 * If it was successfull, it will adapt / replace the Fib node
	 * Fib object with the Fib object of this scene and notify the node that
	 * it was changed.
	 * @see fibNodeChangedEvent()
	 *
	 * @param fibNodeChangedEvent the information for the change event
	 */
	void notifyNodeForChange( const eFibNodeChangedEvent & fibNodeChangedEvent );
	
signals:
	
	/**
	 * Send this signal if the input variables should be (re-)evalued.
	 * @see evalueInputVariables()
	 */
	void signalEvalueInputVariable();
	
	/**
	 * Call this signal if the the Fib object of the Fib node of this object
	 * should be converted to graphical items and they should be shown.
	 * @see evalueGraphicsItemsFromFibNode()
	 */
	void signalEvalueGraphicsItemsFromFibNode();
	
protected slots:

	
	/**
	 * This method will evalue the grapical items for the Fib object of this
	 * scene and include them in this grapical scene.
	 * At the end this graphical scene will display the Fib object.
	 *
	 * @see QList <QGraphicsItem *> QGraphicsScene::items()
	 * @see iFibGraphicsItemFactory
	 * @see signalEvalueGraphicsItemsFromFibNode()
	 * @see cFibGraphicsItemImageFactory
	 * @see cFibGraphicsItem
	 * @return true if the Fib object was displayed, else false
	 */
	bool evalueGraphicsItemsFromFibNode();
	
protected:
	
	/**
	 * @return a hint for a good size of this widget
	 */
	virtual QSize sizeHint() const;
	
	/**
	 * This method sets the input variables to there values, so that the
	 * Fib object can be evalued.
	 * @see pWidgetInputVariables
	 */
	void setInputVariables();
	
	/**
	 * This method will update evalue Fib object with painter object
	 * pEvalueSimpleRGBA255QPainter.
	 *
	 * @see pEvalueSimpleRGBA255QPainter
	 * @see pFibNode
	 * @see dPointWidth
	 * @see dPointHeight
	 * @return true if the evalue Fib object with painter object
	 * 	pEvalueSimpleRGBA255QPainter was changed, else false
	 */
	bool updateEvalueFibObjectForPainter();
	
	/**
	 * This method will change the values of this graphics view according the
	 * dimension domain of the displayed Fib object.
	 * This method will update the point size for a point of the displayed
	 * Fib object. If you call setPenForPointSize() the pen will be set to the
	 * evalued point size.
	 * It will also update the image borders.
	 *
	 * @see dPointWidth
	 * @see dPointHeight
	 * @see dDirection1Minimum
	 * @see dDirection1Maximum
	 * @see dDirection2Minimum
	 * @see dDirection2Maximum
	 * @see setPenForPointSize()
	 * @return true if the dimensions for the Fib object could be evaluated,
	 * 	else false
	 */
	bool updateForDimensionChange();
	
	/**
	 * The event handler for mouse press events.
	 *
	 * @see QGraphicsScene::mousePressEvent
	 * @param pMouseEvent the mouse press event
	 */
	virtual void mousePressEvent( QGraphicsSceneMouseEvent * pMouseEvent );
	
//members:
	
	/**
	 * A pointer to the Fib node object for this widget.
	 */
	cFibNode * pFibNode;
	
	/**
	 * The version of the Fib object for the node, which is displayed.
	 * Every time the Fib object is changed the version number is counted up.
	 * If this number is not equal to the Fib node version number the shown
	 * Fib object needs to be updated.
	 * @see cFibNode::ulVersion
	 * @see cFibNode::fibObjectChanged()
	 */
	unsigned long ulFibNodeVersionDisplayed;
	
	
	/**
	 * A pointer the the widget for the input variables, or NULL if non
	 * exists.
	 * @see evalueInputVariables()
	 * @see getInputVariablesWidget()
	 */
	cWidgetFibInputVariables * pWidgetFibInputVariables;
	
#ifdef TODO_WEG
	/**
	 * A list with the input variables of the Fib object for the Fib node.
	 * 	first: a pointer to the input variable
	 * 	second: a value for the input variable
	 * Input variables of a Fib object are variables, which are used in the
	 * Fib object, but not defined in it. So these variables need to be
	 * set to a value in order to evalue the Fib object.
	 *
	 * @see pFibNode
	 */
	list< pair< cFibVariable *, doubleFib > > pWidgetInputVariables;
#endif //TODO_WEG
	
	
	/**
	 * A pointer to the main window for this widget, or NULL if non exists.
	 */
	cFibObjectMainWindow * pMainWindow;
	
	/**
	 * The list with the Fib grapical items of the Fib object, which is
	 * displayed.
	 * @see mutexFibParts
	 */
	QList< cFibGraphicsItem * > liFibParts;
	
	/**
	 * This mutex is to control access to Fib graphical item, which display
	 * the Fib object.
	 * Lock this mutex befor using or changing Fib graphical item and
	 * unlock it afterwards.
	 * Lock when using:
	 * 	- @see liFibParts
	 *
	 * @see QGraphicsScene::items()
	 */
	mutable QMutex mutexFibParts;
	
	
	
	/**
	 * A pointer cEvalueSimpleRGBA255QPainter template for this graphic scene.
	 * If existing, this painter will contain the enviroment / domain
	 * information to paint a Fib object into this graphic scene.
	 * This object can be used with the template constructor of the
	 * cEvalueSimpleRGBA255QPainter to construct a cEvalueSimpleRGBA255QPainter
	 * object which has the correct enviroment parameters set and uses
	 * the actual painter (QPainter) object.
	 * If you use this cEvalueSimpleRGBA255QPainter template, you have still
	 * to adapt the QPainter for painting (e.g. you have to set the QPainter
	 * pen ( setPen() ) to the correct values (e. g. width) vor drawing points.)
	 * @see cEvalueSimpleRGBA255QPainter( QPainter * pInPainter, const cEvalueSimpleRGBA255QPainter & evalueSimpleRGBA255 );
	 * @see QPainter
	 * @see pFibRootNode
	 */
	cEvalueSimpleRGBA255QPainter * pEvalueSimpleRGBA255QPainter;
	
	
	/**
	 * The node for the root (top most) Fib root object of the Fib node object
	 * for this widget.
	 * It should contain the domains for this graphic scene, so the graphic
	 * scene can be tailord to the Fib object domains.
	 * @see pFibNode
	 * @see pEvalueSimpleRGBA255QPainter
	 */
	cFibNode * pFibRootNode;
	
	/**
	 * The width of a point of the Fib object.
	 * @see pFibNode
	 */
	qreal dPointWidth;
	
	/**
	 * The height of a point of the Fib object.
	 * @see pFibNode
	 */
	qreal dPointHeight;
	
	/**
	 * The minimum value for the direction 1 (x).
	 */
	qreal dDirection1Minimum;
	
	/**
	 * The maximum value for the direction 1 (x).
	 */
	qreal dDirection1Maximum;
	
	/**
	 * The minimum value for the direction 2 (x).
	 */
	qreal dDirection2Minimum;
	
	/**
	 * The maximum value for the direction 2 (x).
	 */
	qreal dDirection2Maximum;
	
};//end class cFibGraphicsScene

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_GRAPHICS_SCENE_H__





