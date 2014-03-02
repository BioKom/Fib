
//TODO check

/**
 * @file cFibVectorCreator
 * file name: cFibVectorCreator.h
 * @author Betti Oesterholz
 * @date 22.11.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a Fib vector.
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
 * This file specifies a class for a Fib vector.
 * If you have a Fib element, vectors of it can be represented with this
 * class for the Fib creator modul.
 * A Fib vector contains a number of elements.
 * This class adds events and listeners to the Fib vector (fib::cFibVector).
 * @pattern Decorator
 *
 * @see cFibVector
 * @see cFibScalar
 * @see cFibVectorCreator
 */
/*
History:
22.11.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_FIB_VECTOR_H__
#define ___FIB__NCREATOR__C_FIB_VECTOR_H__


#include "version.h"

#include <string>
#include <set>

#include <QObject>
#include <QList>
#include <QMutex>

#include "cFibVariableCreator.h"
#include "lScalarChanged.h"
#include "lScalarValueChanged.h"
#include "eFibScalarChangedEvent.h"
#include "lFibNodeChanged.h"
#include "eFibNodeChangedEvent.h"
#include "iGetWidget.h"


namespace fib{

//forward declarations
class cFibElement;
class cFibVector;

namespace nCreator{
	
//forward declarations
class cFibScalar;
class cFibVectorHandler;
class lFibVectorChanged;

class eFibVectorChangedEvent;


class cFibVectorCreator: public QObject, public lScalarChanged,
		public lScalarValueChanged, public lFibVariableCreatorChanged,
		public lFibNodeChanged, public iGetWidget {
		Q_OBJECT

friend class cFibVectorHandler;

public:
	
	/**
	 * destructor
	 */
	virtual ~cFibVectorCreator();
	
	
	/**
	 * @return the name of this class "cFibVectorCreator"
	 */
	virtual std::string getName() const;
	
	/**
	 * @return the name of this vector
	 * 	@see strVectorName
	 */
	virtual QString getVectorName() const;
	
	/**
	 * This method sets the name of this vector to the given name.
	 *
	 * @see strVectorName
	 * @param strName the name the vector should have
	 */
	void setVectorName( const QString & strName );
	
	/**
	 * @return the number of element in the vector
	 * 	@see liElements
	 */
	virtual unsigned int getNumberOfElements() const;
	
	/**
	 * This method returns the uiNumberOfElement'th element of this vector.
	 *
	 * @see liElements
	 * @see getNumberOfElements()
	 * @param uiNumberOfElement the number of the element to return
	 * 	(counting starts with 1)
	 * @return a pointer to the uiNumberOfElement'th element, or
	 * 	NULL if non exists
	 */
	virtual iGetWidget * getElement(
		const unsigned int uiNumberOfElement );
	
	/**
	 * This method returns the uiNumberOfElement'th element of this vector.
	 *
	 * @see liElements
	 * @see getNumberOfElements()
	 * @param uiNumberOfElement the number of the element to return
	 * 	(counting starts with 1)
	 * @return a const pointer to the uiNumberOfElement'th element,
	 * 	or NULL if non exists
	 */
	virtual const iGetWidget * getElement(
		const unsigned int uiNumberOfElement ) const;
	
	/**
	 * @see liElements
	 * @see getNumberOfElements()
	 * @see getElement()
	 * @return a list with the pointers to the element of this vector
	 */
	virtual QList< iGetWidget * > getElements();
	
	/**
	 * @see liElements
	 * @see getNumberOfElements()
	 * @see getElement()
	 * @return a const list with the pointers to the element of this vector
	 */
	virtual const QList< iGetWidget * > getElements() const;
	
	/**
	 * This method adds the given element to this vector.
	 * This method will also adapt the Fib vector pFibVector.
	 * Note: If the Fib vector can't be adapted, this method will fail.
	 *
	 * @see liElements
	 * @see getNumberOfElements()
	 * @see removeElement()
	 * @see replaceElement()
	 * @param pElement a pointer to the element to add
	 * 	(Beware: The element won't be cloned, so do not delete it.)
	 * @param uiPosition the position where to add the element,
	 * 	if 0 or greater the number of elements in this vector it will be
	 * 	added to the end of the vector
	 * 	(counting starts with 1)
	 * @return true if the element was added, else false
	 */
	virtual bool addElement( iGetWidget * pElement,
		const unsigned int uiPosition = 0 );
	
	/**
	 * This method removes the uiPosition'th element from this vector.
	 * This method will also adapt the Fib vector pFibVector.
	 * Note: If the Fib vector can't be adapted, this method will fail.
	 *
	 * @see liElements
	 * @see getNumberOfElements()
	 * @see addElement()
	 * @see replaceElement()
	 * @param uiPosition the position where to remove the element from
	 * 	(counting starts with 1)
	 * @return true if the element was removed, else false
	 */
	virtual bool removeElement( const unsigned int uiPosition );
	
	/**
	 * This method removes the given element from this vector.
	 * This method will also adapt the Fib vector pFibVector.
	 * Note: If the Fib vector can't be adapted, this method will fail.
	 *
	 * @see liElements
	 * @see getNumberOfElements()
	 * @see addElement()
	 * @see replaceElement()
	 * @param pElement the element to remove
	 * @return true if the element was removed, else false
	 */
	virtual bool removeElement( iGetWidget * pElement );
	
	/**
	 * This method replaces a element in this vector.
	 * It will replace the uiPosition'th element in the vector with the given
	 * element pElement (if possible).
	 * This method will also adapt the Fib vector pFibVector.
	 * Note: If the Fib vector can't be adapted, this method will fail.
	 *
	 * @see liElements
	 * @see getNumberOfElements()
	 * @see removeElement()
	 * @see addElement()
	 * @param uiPosition the position where to replace the element
	 * 	(counting starts with 1)
	 * @param pElement a pointer to the element to add, which will replace the
	 * 	old element on the uiPosition'th position
	 * @return true if the element was replace, else false
	 */
	virtual bool replaceElement( const unsigned int uiPosition,
		iGetWidget * pElement );
	
	/**
	 * This method replaces elements in this vector.
	 * It will replace the pElementToReplace elements in the vector with the
	 * given element pElement (if possible).
	 * This method will also adapt the Fib vector pFibVector.
	 * Note: If the Fib vector can't be adapted, this method will fail.
	 *
	 * @see liElements
	 * @see getNumberOfElements()
	 * @see removeElement()
	 * @see addElement()
	 * @param pElementToReplace a pointer to the element to replace
	 * 	(Beware: The element won't be cloned, so do not delete it.)
	 * @param pElement a pointer to the element to add, which will replace the
	 * 	old element pElementToReplace
	 * @return true if the elements where replace, else false
	 */
	virtual bool replaceElement( iGetWidget * pElementToReplace,
		iGetWidget * pNewElement );
	
	/**
	 * This method replaces a element in this vector.
	 * It will replace the uiPosition'th element in the vector with a scalar
	 * value element with value dValue.
	 * This method will also adapt the Fib vector pFibVector.
	 * Note: If the Fib vector can't be adapted, this method will fail.
	 *
	 * @see liElements
	 * @see getNumberOfElements()
	 * @see removeElement()
	 * @see addElement()
	 * @param uiPosition the position where to replace the element
	 * 	(counting starts with 1)
	 * @param dValue the value for the scalar element, which will replace the
	 * 	old element on the uiPosition'th position
	 * @return true if the element was replace, else false
	 */
	virtual bool replaceElement( const unsigned int uiPosition,
		const doubleFib dValue );
	
	/**
	 * This method sets the vector to the given list of elements.
	 * All old element of this vector are removed and the given elements added.
	 * This method will also adapt the Fib vector pFibVector.
	 * Note: If the Fib vector can't be adapted, this method will fail.
	 *
	 * @see liElements
	 * @see getNumberOfElements()
	 * @see replaceElement()
	 * @see removeElement()
	 * @see addElement()
	 * @param liInElements a list of the element this object should contain
	 * @return true if the elements could be set, else false
	 */
	virtual bool setElements( QList< iGetWidget * > & liInElements );
	
	/**
	 * @see setFibElement()
	 * @return a pointer to the Fib element, which the vector of this
	 * 	object represents or NULL if non was given
	 * 	@see pFibElement
	 */
	virtual cFibElement * getFibElement();
	
	/**
	 * @see setFibElement()
	 * @return a const pointer to the Fib element, which the vector of this
	 * 	object represents or NULL if non was given
	 * 	@see pFibElement
	 */
	virtual const cFibElement * getFibElement() const;
	
	/**
	 * This method sets the Fib element, which the vector of this object
	 * represents.
	 *
	 * @see pFibElement
	 * @see getFibElement()
	 * @param pInFibElement a pointer to the Fib element, which the vector
	 * 	of this object represents or NULL if non should be stored
	 */
	virtual void setFibElement( cFibElement * pInFibElement );
	
	
	/**
	 * @see setFibVector()
	 * @return a pointer to the Fib vector, which this vector
	 * 	of this object represents or NULL if non was given
	 * 	@see pFibVector
	 */
	virtual fib::cFibVector * getFibVector();
	
	/**
	 * @see setFibVector()
	 * @return a const pointer to the Fib vector, which this vector
	 * 	of this object represents or NULL if non was given
	 * 	@see pFibVector
	 */
	virtual const fib::cFibVector * getFibVector() const;
	
	/**
	 * This method sets the Fib vector, which the vector of this object
	 * represents.
	 *
	 * @see pFibVector
	 * @see getFibElement()
	 * @param pInFibVector a pointer to the Fib vector, which this vector (of
	 * 	this object) represents or NULL if non should be stored
	 */
	virtual void setFibVector( fib::cFibVector * pInFibVector );
	
	
	/**
	 * This method assigns the value of the vector elements to the
	 * Fib elements. ( pScalar->assignValues() )
	 * Call this function before evaluing the Fib element for the vector.
	 *
	 * @see cFibScalar::assignValues()
	 * @see cFibScalar::getValue()
	 * @see cFibScalar::setValue()
	 */
	virtual void assignValues();
	
	
	/**
	 * Event method
	 * It will be called every time a scalar (cFibScalar),  at which this
	 * object is registered, was changed.
	 *
	 * @param pFibScalarEvent a pointer to the event with the information of
	 * 	the change of the Fib scalar
	 */
	virtual void fibScalarChangedEvent(
		const eFibScalarChangedEvent * pFibScalarEvent );
	
	/**
	 * Event method
	 * It will be called every time a scalar value (cFibScalar), at which
	 * this object is registered, was changed.
	 *
	 * @see cFibScalar::dValue
	 * @param pFibScalar a pointer to the changed Fib scalar
	 */
	virtual void fibScalarValueChangedEvent(
		const cFibScalar * pFibScalar );
	
	/**
	 * Event method
	 * It will be called every time a input variable (cFibInputVariable),
	 * at which this object is registered,was changed.
	 *
	 * @param pFibVariableChangedEvent a pointer to the event with the
	 * 	information of the change of the Fib input variable
	 */
	virtual void changedEvent(
		const eFibVariableCreatorChangedEvent * pFibVariableChangedEvent );
	
	/**
	 * Event method
	 * It will be called every time a Fib node (cFibNode), at which
	 * this object is registered, was changed.
	 *
	 * @param pFibNodeChangedEvent a pointer to the event, with the information
	 * 	about the changed Fib node
	 */
	virtual void fibNodeChangedEvent(
		const eFibNodeChangedEvent * pFibNodeChangedEvent );
	
	
	/**
	 * With this function you can register a listeners for changes in this
	 * Fib vector.
	 *
	 * @see unregisterFibVectorChangeListener()
	 * @see setFibVectorChangeListener
	 * @see sendFibVectorChange()
	 * @param pFibVectorListener a pointer to the listener for changes
	 * @return true if the listener was registered, else false
	 */
	bool registerFibVectorChangeListener( lFibVectorChanged * pFibVectorListener );
	
	/**
	 * With this function you can unregister a listeners for changes in this
	 * Fib vector.
	 *
	 * @see registerFibVectorChangeListener()
	 * @see setFibVectorChangeListener
	 * @see sendFibVectorChange()
	 * @param pFibVectorListener a pointer to the listener for changes
	 * @return true if the listener was registered, else false
	 */
	bool unregisterFibVectorChangeListener( lFibVectorChanged * pFibVectorListener );
	
	
	/**
	 * This method will create a widget, which displays this object.
	 * ATTENTION: You have to care that the returned widget is deleted.
	 *
	 * @param pParent a pointer the parent of this new Fib element widget
	 * @return a pointer to the created widget, or NULL if non could be created
	 */
	virtual QWidget * getWidget( QWidget * pParent = NULL );
	
	/**
	 * This method returns the name for the uiPosition'th vector element.
	 *
	 * @param uiPosition the position where of the element for which to return
	 * 	the name (counting starts with 1)
	 * @return the name for the uiPosition'th vector element
	 */
	virtual QString getVectorElementName( const unsigned int uiPosition ) const;
	
protected:
	
	/**
	 * The standard constructor for a vector.
	 * It constructs a vector with no element. (So you can add them later.)
	 */
	cFibVectorCreator();

	/**
	 * A parameter constructor for a vector.
	 *
	 * @param pInFibVector a pointer to the Fib vector of this vector,
	 * 	The elements for this vector will be read from this vector.
	 * 	The Fib element for this vector will be the defining Fib element
	 * 	of the given vector.
	 * 	@see pFibVector
	 */
	explicit cFibVectorCreator( fib::cFibVector * pInFibVector );
	
	/**
	 * A parameter constructor for a vector.
	 *
	 * @param liInElements list with element for this object
	 * 	@see liElements
	 * @param szVectorName the name of the vector
	 * @param pInFibVector a pointer to the Fib vector of this vector
	 * 	(Note: It should contain the same elements in the same order as liInElements .)
	 * 	@see pFibVector
	 * @param pInFibElement the Fib element for which this vector is or NULL
	 * 	(The Fib element which contains the vector)
	 * 	@see pFibElement
	 */
	explicit cFibVectorCreator( QList< iGetWidget * > & liInElements,
		const QString szVectorName = "",
		fib::cFibVector * pInFibVector = NULL,
		cFibElement * pInFibElement = NULL );
	
	/**
	 * This method sents a Fib vector changed event to all Fib vector change
	 * listeners of this object.
	 *
	 * @see setFibVectorChangeListener
	 * @see registerFibVectorChangeListener()
	 * @see unregisterFibVectorChangeListener()
	 * @param pFibVectorChangedEvent the change event to send
	 */
	void sendFibVectorChange(
		const eFibVectorChangedEvent * pFibVectorChangedEvent );
	
	
	/**
	 * This method register this object at the given element.
	 * Note: It dosn't use a mutex.
	 *
	 * @param pElement a pointer to the object where to register this object
	 */
	void registerForElement( iGetWidget * pElement );
	
	/**
	 * This method removes the given element from this vector.
	 * Note: It dosn't use a mutex or send signals.
	 *
	 * @param pElement a pointer to the object to remove from this object
	 */
	void removeElementFromVector( iGetWidget * pElement );
	
	/**
	 * This method send a node changed event for the Fib node for the
	 * Fib object which contains this vector.
	 */
	bool sendNodeChangedEvent() const;
	
//members:
	
	/**
	 * The name of the vector.
	 */
	QString strVectorName;
	
	/**
	 * The list with the vector elements.
	 * @see mutexFibVector
	 * @see getNumberOfElements()
	 * @see getElements()
	 * @see setElements()
	 * @see getElement()
	 * @see addElement()
	 * @see removeElement()
	 * @see replaceElement()
	 */
	QList< iGetWidget * > liElements;
	
	/**
	 * Mutex to lock access to the vector.
	 * Lock the mutex if you use one of the following containers:
	 * 	@see liElements
	 * 	@see strVectorName
	 */
	mutable QMutex mutexFibVector;
	
	
	/**
	 * The Fib element for which this vector is or NULL.
	 * @see getFibElement()
	 * @see setFibElement()
	 */
	cFibElement * pFibElement;
	
	/**
	 * The Fib vector for which this vector is or NULL.
	 * @see getFibVector()
	 * @see setFibVector()
	 */
	fib::cFibVector * pFibVector;
	
	/**
	 * The top most node for the Fib object for the vector.
	 * The widget needs to know it, so it can react to domain changes.
	 * @see mutexFibVector
	 */
	cFibNode * pMasterNode;
	
	/**
	 * The set with the listeners for Fib vectors changes.
	 * @see registerFibVectorChangeListener()
	 * @see unregisterFibVectorChangeListener()
	 * @see sendFibVectorChange()
	 * @see mutexFibVectorChangeListener
	 */
	std::set< lFibVectorChanged * > setFibVectorChangeListener;
	
	/**
	 * Mutex to lock access to the listeners for Fib vector changes.
	 * Lock the mutex if you use one of the following containers:
	 * 	@see setFibVectorChangeListener
	 */
	mutable QMutex mutexFibVectorChangeListener;
	
};//end class cFibVectorCreator

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_VECTOR_H__





