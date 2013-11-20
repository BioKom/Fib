
//TODO check

/**
 * @file cWidgetFibObjectInfo
 * file name: cWidgetFibObjectInfo.h
 * @author Betti Oesterholz
 * @date 09.10.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for the information about a Fib object.
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
 * This file specifies a class for the information about a Fib object.
 *
 * It should look like:
 * +-------------------------------------------------+
 * | - name @see szNameOfFibObject                   |
 * | - preview or description @see szDescription     |
 * |      - switch by parameter or click on by mouse |
 * | - number of input variables ->pic-> number of - |
 * |      subobjects ;    number of Fib elements;    |
 * |      changebel (=green or red for not changebel)|
 * +-------------------------------------------------+
 *
 */
/*
History:
09.10.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_WIDGET_FIB_OBJECT_INFO_H__
#define ___FIB__NCREATOR__C_WIDGET_FIB_OBJECT_INFO_H__


#include "version.h"

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsView>


#include "cFibObjectInfo.h"


namespace fib{

namespace nCreator{

//forward declarations
class cFibGraphicsScene;
class lSelectedWidgetFibObjectInfo;

class cWidgetFibObjectInfo: public QFrame, public lFibObjectInfoChanged{
		Q_OBJECT
public:
	
	/**
	 * standard constructor for a Fib object info widget
	 *
	 * @param pInFibObjectInfo a pointer to the Fib object info object for this widget
	 * 	@see pFibObjectInfo
	 * @param pParent a pointer the parent of this new Fib object info widget
	 */
	cWidgetFibObjectInfo( cFibObjectInfo * pInFibObjectInfo,
		QWidget * pParent = NULL );
	
	/**
	 * destructor
	 */
	virtual ~cWidgetFibObjectInfo();
	
	/**
	 * This method returns a pointer to the Fib object info object of this
	 * widget.
	 * Note: Don't delete the returned Fib object info object.
	 *
	 * @see pFibObjectInfo
	 * @return a pointer to the Fib object info object of this widget
	 */
	const cFibObjectInfo * getFibObjectInfo() const;
	
	/**
	 * This method returns a pointer to the Fib object info object of this
	 * widget.
	 * Note: Don't delete the returned Fib object info object.
	 *
	 * @see pFibObjectInfo
	 * @return a pointer to the Fib object info object of this widget
	 */
	cFibObjectInfo * getFibObjectInfo();
	
	/**
	 * @return the name of this class "cWidgetFibObjectInfo"
	 */
	virtual std::string getName() const;
	
	/**
	 * This method sets if this Fib object info widget is selected or not.
	 *
	 * @param bSelected true if this widget is selected, else false
	 */
	void setSelected( bool bSelected = true );
	
	/**
	 * Event method
	 * It will be called every time a Fib Fib object info object
	 * (cFibObjectInfo), at which this object is registered, was changed.
	 *
	 * @param pFibObjectInfoChanged a pointer to the event, with the information
	 * 	about the changed Fib node
	 */
	virtual void fibObjectInfoChanged(
		const eFibObjectInfoChangedEvent * pFibObjectInfoChanged );
	
	/**
	 * With this function you can register a listeners for changes for the
	 * selected Fib object info widget.
	 *
	 * @see cWidgetFibObjectInfo::registerListenerSelectedFibObjectInfo()
	 * @see unregisterListenerSelectedFibObjectInfo()
	 * @see liListenersSelectedWidgetFibObjectInfo
	 * @see setSelectedFibObjectInfo()
	 * @see sendSelectedFibObjectInfoChange()
	 * @param pSelectedFibObjectInfo a pointer to the listener for changes
	 * @return true if the listener was registered, else false
	 */
	bool registerListenerSelectedFibObjectInfo(
		lSelectedWidgetFibObjectInfo * pSelectedFibObjectInfo );
	
	/**
	 * With this function you can unregister a listeners for changes for the
	 * selected Fib object info widget.
	 *
	 * @see registerListenerSelectedFibObjectInfo()
	 * @see liListenersSelectedWidgetFibObjectInfo
	 * @see setSelectedFibObjectInfo()
	 * @see sendSelectedFibObjectInfoChange()
	 * @param pSelectedFibObjectInfo a pointer to the listener for changes
	 * @return true if the listener was registered, else false
	 */
	bool unregisterListenerSelectedFibObjectInfo(
		lSelectedWidgetFibObjectInfo * pSelectedFibObjectInfo );
	
	
protected:
	
	/**
	 * This method send a event that the selected Fib object info widget
	 * has changed to all registered listeners for changes of the selected
	 * Fib object info widget.
	 *
	 * @see registerListenerSelectedFibObjectInfo()
	 * @see unregisterListenerSelectedFibObjectInfo()
	 * @see liListenersSelectedWidgetFibObjectInfo
	 * @see setSelectedFibObjectInfo()
	 */
	void sendSelectedFibObjectInfoChange();
	
	/**
	 * This method will (re-)create this Fib object info widget
	 * correspondending to the actual Fib object info object.
	 * @see pFibObjectInfo
	 */
	virtual void createFibObjectInfoWidget();
	
	/**
	 * @return a hint for a good size of this widget
	 */
	virtual QSize sizeHint() const;
	
	/**
	 * This method handles mouse events.
	 */
	virtual void mousePressEvent( QMouseEvent * );
	
protected:
	
	/**
	 * A pointer to the Fib object info object this widget represents.
	 * @see getFibObjectInfo()
	 * @see createFibObjectInfoWidget()
	 */
	cFibObjectInfo * pFibObjectInfo;
	
	/**
	 * The label for the name of the Fib object.
	 */
	QLabel * pLabelNameOfFibObject;
	
	
	/**
	 * This enumerate what is viewed in the center of this widget.
	 * @see pLayoutCenter
	 */
	enum edCenterViewMode{
		ED_PREVIEW,//view preview picture in the center
		ED_DESCRIPTION//view Fib object description in the center
	}centerViewMode;
	
	
	/**
	 * The label for the description of the Fib object.
	 * @see cRoot::getNumberOfInputVariables()
	 * (edCenterViewMode::ED_DESCRIPTION)
	 * @see edCenterViewMode
	 */
	QLabel * pLabelDescription;
	
	/**
	 * The preview image for the Fib object.
	 * (edCenterViewMode::ED_PREVIEW)
	 * @see edCenterViewMode
	 * @see pViewPreviewPicture
	 */
	cFibGraphicsScene * pScenePreviewPicture;
	
	/**
	 * The graphics view for the preview image scene where the preview
	 * Fib object is shown.
	 * @see pScenePreviewPicture
	 */
	QGraphicsView * pViewPreviewPicture;
	
	/**
	 * The label for the number of input variables of the Fib object.
	 * @see cRoot::getNumberOfInputVariables()
	 */
	QLabel * pLabelNumberOfInputVariables;
	
	/**
	 * The label for the number of Fib elements in the Fib object.
	 * @see cFibElement::getNumberOfElements()
	 */
	QLabel * pLabelNumberOfFibElements;
	
	/**
	 * The label for the number of input variables of the Fib object.
	 * @see cRoot::getNumberOfExternSubobjects()
	 */
	QLabel * pLabelNumberOfExtSubobjects;
	
	//TODO is changebel

	
	/**
	 * The variables to organize the layout of the widget.
	 */
	QHBoxLayout * pLayoutCenter;
	QHBoxLayout * pLayoutBottomLine;
	QVBoxLayout * pLayoutMain;
	
	/**
	 * The set with the listeners for changes of the selected Fib object
	 * info widget.
	 */
	set< lSelectedWidgetFibObjectInfo * > setListenersSelectedWidgetFibObjectInfo;
	
	/**
	 * Mutex to lock access to the listeners for changes of the selected
	 * Fib object info widget.
	 * Lock the mutex if you use one of the following containers:
	 * @see setInputVariableChangeListener
	 */
	mutable QMutex mutexListenersSelectedWidgetFibObjectInfo;
	
private:
	
};//end class cWidgetFibObjectInfo

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_WIDGET_FIB_OBJECT_INFO_H__





