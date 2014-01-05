
//TODO check

/**
 * @file cFibScalar
 * file name: cFibScalar.h
 * @author Betti Oesterholz
 * @date 21.11.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies the basis class for a scalar in a Fib object.
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
 * This file specifies the basis class for a scalar in a Fib object.
 * For every scalar value or scalar in a Fib element a child of this
 * class can be used.
 * It helps the Fib creator applictaion to handle scalars in Fib objects.
 * (e. g. notify for value changes)
 *
 *
 * @see cFibElement
 * @see cDomainSingle
 */
/*
History:
21.11.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_FIB_SCALAR_H__
#define ___FIB__NCREATOR__C_FIB_SCALAR_H__


#include "version.h"

#include <string>
#include <set>

#include <QObject>
#include <QList>
#include <QString>

#include "cDomainSingle.h"

#include "iGetWidget.h"
#include "lScalarChanged.h"
#include "eFibScalarChangedEvent.h"
#include "lScalarValueChanged.h"


//TODO? use new change listener mechanism


namespace fib{

namespace nCreator{

class cFibScalar: public QObject, public iGetWidget{
		Q_OBJECT
public:
	
	/**
	 * The parameter constructor for a scalar.
	 *
	 * @param dInValue the value for the scalar
	 * @param strInScalarName the name of the scalar
	 * 	@see strScalarName
	 * @param pInScalarDomain a pointer to the domain for the scalar
	 * 	Beware: This object will delete the given object on destruction.
	 */
	cFibScalar( const doubleFib dInValue = 0, const QString strInScalarName="",
		cDomainSingle * pInScalarDomain = NULL );
	
	/**
	 * The copy constructor for a scalar.
	 *
	 * @param fibScalar a reference to the scalar, which to copy
	 */
	cFibScalar( const cFibScalar & fibScalar);
	
	/**
	 * destructor
	 */
	virtual ~cFibScalar();
	
	
	/**
	 * This method clones this object.
	 *
	 * @return a pointer to the clone of this object
	 */
	virtual cFibScalar * clone() const;
	
	/**
	 * @return the name of this class "cFibScalar"
	 */
	virtual std::string getName() const;
	
	/**
	 * @see setValue()
	 * @see dValue
	 * @return the value for the scalar
	 */
	doubleFib getValue() const;
	
	/**
	 * This method sets the value for the scalar.
	 * If a value is outside the domain pScalarDomain are given, it will
	 * be rounded to the next value inside the domain.
	 *
	 * @see dValue
	 * @see getValue()
	 * @see cDomainSingle::round()
	 * @param dInValue the value to set for the scalar
	 */
	void setValue( const doubleFib & dInValue );
	
	/**
	 * @return the name of the scalar
	 * 	@see strScalarName
	 */
	QString getScalarName() const;
	
	/**
	 * This method sets the name of the scalar to the given name.
	 *
	 * @see strScalarName
	 * @param strName the name of the scalar should have
	 */
	void setScalarName( const QString & strName );
	
	/**
	 * This method returns a pointer to the domain for the scalar.
	 *
	 * @see pScalarDomain
	 * @see setDomain()
	 * @return a pointer to the domain for the scalar, or the null
	 * 	pointer NULL if non exists
	 */
	const cDomainSingle * getDomain() const;
	
	/**
	 * This method sets domain for the scalar.
	 * Note: This method will reset the delta value dDeltaValue and
	 * 	delete the old domain if existing.
	 *
	 * @see pScalarDomain
	 * @see setDomain()
	 * @see dDeltaValue
	 * @param pInScalarDomain a pointer to the domain for the scalar,
	 * 	or the null pointer NULL if non should exists
	 * 	Beware: This object will delete the given object on destruction.
	 */
	void setDomain( cDomainSingle * pInScalarDomain = NULL );
	
	/**
	 * @return the delta value by which the scalar value is increased or
	 * 	decreased
	 * @see dDeltaValue
	 * @see increaseValue()
	 * @see decreaseValue()
	 */
	doubleFib getDelta() const;
	
	/**
	 * This method sets the delta value by which the scalar value is
	 * increased or decreased.
	 *
	 * @see dDeltaValue
	 * @see increaseValue()
	 * @see decreaseValue()
	 * @param dInDeltaValue the new delta value to use
	 */
	void setDelta( const doubleFib & dInDeltaValue );
	
	/**
	 * @see increaseValue()
	 * @see dValue
	 * @see dDeltaValue
	 * @see canDecreaseValue()
	 * @return true if the value of the scalar can be increased else false
	 */
	bool canIncreaseValue();
	
	/**
	 * @see increaseValue()
	 * @see dValue
	 * @see dDeltaValue
	 * @see canDecreaseValue()
	 * @return true if the value of the scalar can be decreased else false
	 */
	bool canDecreaseValue();
	
	/**
	 * This method returns possible values for the scalar.
	 * It will return maximal ulMaxCount values, but can return less.
	 * Also it will try to space the values evenly across the domain for
	 * the scalar.
	 *
	 * @see pScalarDomain
	 * @see dDeltaValue
	 * @see decreaseValue()
	 * @see increaseValue()
	 * @return a list with maximal ulMaxCount values to which the scalar can
	 * 	be set
	 */
	QList< doubleFib > getPossibleValues( const unsigned long ulMaxCount = 1024 ) const;
	
	
	/**
	 * With this function you can register a listeners for changes in this
	 * scalar.
	 *
	 * @see unregisterScalarChangeListener()
	 * @see setScalarChangeListener
	 * @see sendScalarChange()
	 * @param pScalarListener a pointer to the listener for changes
	 * @return true if the listener was registered, else false
	 */
	bool registerScalarChangeListener( lScalarChanged * pScalarListener );
	
	/**
	 * With this function you can unregister a listeners for changes in this
	 * scalar.
	 *
	 * @see registerScalarChangeListener()
	 * @see setScalarChangeListener
	 * @see sendScalarChange()
	 * @param pScalarListener a pointer to the listener for changes
	 * @return true if the listener was registered, else false
	 */
	bool unregisterScalarChangeListener( lScalarChanged * pScalarListener );

	/**
	 * With this function you can register a listeners for changes of this
	 * scalar value.
	 *
	 * @see unregisterScalarValueChangeListener()
	 * @see setScalarValueChangeListener
	 * @see sendScalarValueChange()
	 * @param pScalarValueListener a pointer to the listener for changes
	 * @return true if the listener was registered, else false
	 */
	bool registerScalarValueChangeListener(
		lScalarValueChanged * pScalarValueListener );
	
	/**
	 * With this function you can unregister a listeners for changes of this
	 * scalar value.
	 *
	 * @see registerScalarValueChangeListener()
	 * @see setScalarValueChangeListener
	 * @see sendScalarValueChange()
	 * @param pScalarValueListener a pointer to the listener for changes
	 * @return true if the listener was registered, else false
	 */
	bool unregisterScalarValueChangeListener(
		lScalarValueChanged * pScalarValueListener );

	/**
	 * This method will create a widget, which displays this object.
	 * ATTENTION: You have to care that the returned widget is deleted.
	 *
	 * @param pParent a pointer the parent of this new Fib scalar widget
	 * @return a pointer to the created widget, or NULL if non could be created
	 */
	virtual QWidget * getWidget( QWidget * pParent = NULL );
	
signals:
	
	/**
	 * This signal is triggert if the scalar value chages.
	 *
	 * @see dValue
	 * @param dNewValue the new scalar value
	 */
	void scalarValueChanged( doubleFib dNewValue );
	
	/**
	 * This signal is triggert if the canIncreaseValue() status changes.
	 *
	 * @see bCanIncreaseValue
	 * @see canIncreaseValue()
	 * @param bIncreaseValuePossible true if incresing the value of the
	 * 	scalar is possible, else false
	 */
	void increaseValuePossible( bool bIncreaseValuePossible );
	
	/**
	 * This signal is triggert if the canDecreaseValue() status changes.
	 *
	 * @see bCanDecreaseValue
	 * @see canDecreaseValue()
	 * @param bDecreaseValuePossible true if decresing the value of the
	 * 	scalar is possible, else false
	 */
	void decreaseValuePossible( bool bDecreaseValuePossible );
	
	
public slots:
	
	
	/**
	 * This method will increase the value of the scalar (if possible).
	 * ( dValue = pScalarDomain->round( dValue + dDeltaValue )
	 * @see pScalarDomain
	 * @see dDeltaValue
	 * @see decreaseValue()
	 */
	bool increaseValue();
	
	/**
	 * This method will decrease the value of the scalar (if possible).
	 * ( dValue = pScalarDomain->round( dValue - dDeltaValue )
	 * @see pScalarDomain
	 * @see dDeltaValue
	 * @see increaseValue()
	 */
	bool decreaseValue();
	
	
protected:
	
	/**
	 * This method sents a scalar changed event to all scalar change
	 * listeners of this object.
	 *
	 * @see setScalarChangeListener
	 * @see registerScalarChangeListener()
	 * @see unregisterScalarChangeListener()
	 * @param pFibScalarChangedEvent the change event to send
	 */
	void sendScalarChange(
		const eFibScalarChangedEvent * pFibScalarChangedEvent );

	/**
	 * This method sents a scalar value changed event to all scalar value
	 * change listeners of this object.
	 *
	 * @see setScalarValueChangeListener
	 * @see registerScalarValueChangeListener()
	 * @see unregisterScalarValueChangeListener()
	 */
	void sendScalarValueChange();

//members:
	
	/**
	 * The value for the scalar.
	 */
	doubleFib dValue;
	
	/**
	 * The name of the scalar.
	 */
	QString strScalarName;
	
	/**
	 * The domain with the possible values vor a scalar.
	 * The value dValue to be set should be in this domain. Only values in
	 * this domain can be set.
	 * If it is the null pointer NULL all values can be set.
	 *
	 * @see dValue
	 * @see setValue()
	 * @see increaseValue()
	 * @see decreaseValue()
	 */
	cDomainSingle * pScalarDomain;
	
	/**
	 * The delta value to increase or decrease the value of the scalar.
	 *
	 * @see dValue
	 * @see increaseValue()
	 * @see decreaseValue()
	 */
	doubleFib dDeltaValue;
	
	/**
	 * If true the value of the scalar can be increased.
	 */
	bool bCanIncreaseValue;
	
	/**
	 * If true the value of the scalar can be decreased.
	 */
	bool bCanDecreaseValue;
	
	/**
	 * The set with the listeners for scalars changes.
	 * @see registerScalarChangeListener()
	 * @see unregisterScalarChangeListener()
	 * @see sendScalarChange()
	 */
	std::set< lScalarChanged * > setScalarChangeListener;
	
	/**
	 * The set with the listeners for scalars value changes.
	 * @see registerScalarValueChangeListener()
	 * @see unregisterScalarValueChangeListener()
	 * @see sendScalarValueChange()
	 */
	std::set< lScalarValueChanged * > setScalarValueChangeListener;
	
	
};//end class cFibScalar

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_SCALAR_H__





