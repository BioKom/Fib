
//TODO check

/**
 * @file cWidgetFibScalar
 * file name: cWidgetFibScalar.cpp
 * @author Betti Oesterholz
 * @date 27.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a widget for a Fib scalar.
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
 * This file implements a class for a widget for a Fib scalar.
 * It will display one scalar. This scalar is represented
 * by a name and a value.
 *
 * @see cFibScalar
 * @see cFibVariable
 */
/*
History:
27.08.2013  Oesterholz  created
*/


#include "cWidgetFibScalar.h"

#include <QDoubleValidator>


//TODO switches for test proposes
#define DEBUG



using namespace fib::nCreator;



/**
 * The standard constructor for a Fib scalar widget.
 *
 * @param pInFibScalar a pointer to the scalar to display
 * @param pParent a pointer the parent of this new Fib scalar widget
 */
cWidgetFibScalar::cWidgetFibScalar(
		cFibScalar * pInFibScalar, QWidget * pParent ):
		QWidget( pParent ), pFibScalar( pInFibScalar ),
		pLabelVariable( NULL ), pLineEditValue( NULL ),
		pButtonDecrease( NULL ), pButtonIncrease( NULL ),
		pLayoutMain( NULL ), pLayoutValue( NULL ){
	
	DEBUG_OUT_L2(<<"cWidgetFibScalar("<<this<<")::cWidgetFibScalar( pInFibScalar="<<pInFibScalar<<", pParent="<<pParent<<") called"<<endl<<flush);
	if ( pFibScalar == NULL ){
		//no scalar -> no widget
		return;
	}
	//register this object as a listener for changes of the scalar
	pFibScalar->registerScalarChangeListener( this );
	//TODO
	//except any double
	QDoubleValidator * pValidatorValue = new QDoubleValidator( this );
		//TODO?? use scalar domain vor the validator
	
	//create scalar name label
	pLabelVariable = new QLabel( pFibScalar->getScalarName(), this );
	pLabelVariable->setAlignment( Qt::AlignHCenter );
	
	pLineEditValue = new QLineEdit( this );
	pLabelVariable->setBuddy( pLineEditValue );
	
	QString strVariableValue;
	strVariableValue.setNum( pFibScalar->getValue(), 'g', 6 );
	
	pLineEditValue->setText( strVariableValue );
	pLineEditValue->setAlignment( Qt::AlignHCenter );
	pLineEditValue->setValidator( pValidatorValue );
	
	connect( pLineEditValue, SIGNAL( textChanged( const QString ) ),
		this, SLOT( setScalarValue( const QString ) ) );
	
	//create decrease button
	pButtonDecrease = new QPushButton( tr("<"), this );
	pButtonDecrease->setDefault( true );
	pButtonDecrease->setAutoRepeat( true );
	connect( pButtonDecrease, SIGNAL( pressed() ),
		pFibScalar, SLOT( decreaseValue() ) );
	connect( pFibScalar, SIGNAL( decreaseValuePossible( bool ) ),
		pButtonDecrease, SLOT( setEnabled( bool ) ) );
	
	//create increase button
	pButtonIncrease = new QPushButton( tr(">"), this );
	pButtonIncrease->setDefault( true );
	pButtonIncrease->setAutoRepeat( true );
	connect( pButtonIncrease, SIGNAL( pressed() ),
		pFibScalar, SLOT( increaseValue() ) );
	connect( pFibScalar, SIGNAL( increaseValuePossible( bool ) ),
		pButtonIncrease, SLOT( setEnabled( bool ) ) );
	
	
//create the layout
	//create value
	pLayoutValue = new QHBoxLayout();
	pLayoutValue->addWidget( pButtonDecrease );
	pLayoutValue->addWidget( pLineEditValue );
	pLayoutValue->addWidget( pButtonIncrease );
	//create main layout
	pLayoutMain = new QVBoxLayout();
	pLayoutMain->addWidget( pLabelVariable );
	pLayoutMain->addLayout( pLayoutValue );
	
	setLayout( pLayoutMain );
}


/**
 * destructor
 */
cWidgetFibScalar::~cWidgetFibScalar(){
	
	DEBUG_OUT_L2(<<"cWidgetFibScalar("<<this<<")::~cWidgetFibScalar() called"<<endl<<flush);
	if ( pFibScalar ){
		//unregister this object as a listener for changes of the scalar
		pFibScalar->unregisterScalarChangeListener( this );
	}
}


/**
 * @return the pointer to the scalar for the widget
 */
cFibScalar * cWidgetFibScalar::getFibScalar(){
	
	return pFibScalar;
}


/**
 * @return the pointer to the scalar for the widget
 */
const cFibScalar * cWidgetFibScalar::getFibScalar() const{
	
	return pFibScalar;
}


/**
 * Event method
 * It will be called every time a scalar (cFibScalar), at which this
 * object is registered, was changed.
 *
 * @param pFibScalarEvent a pointer to the event with the information of
 * 	the change of the Fib scalar
 */
void cWidgetFibScalar::fibScalarChangedEvent(
	const eFibScalarChangedEvent * pFibScalarEvent ){
	
	DEBUG_OUT_L2(<<"cWidgetFibScalar("<<this<<")::fibScalarChangedEvent( pFibScalarEvent="<<pFibScalarEvent<<" ) called"<<endl<<flush);
	if ( pFibScalarEvent == NULL ){
		//no event given
		return;
	}
	if ( pFibScalarEvent->bScalarDeleted ){
		//remove deleted scalar
		if ( pFibScalar ){
			//unregister this object as a listener for changes of the scalar
			pFibScalar->unregisterScalarChangeListener( this );
			pFibScalar = NULL;
		}
	}
	
	if ( pFibScalar &&
			( pFibScalar == pFibScalarEvent->pScalarChanged ) ){
		//set the new values
		pLabelVariable->setText( pFibScalar->getScalarName() );
		
		QString strVariableValue;
		strVariableValue.setNum( pFibScalar->getValue(), 'g', 6 );
		pLineEditValue->setText( strVariableValue );
	}
}


/**
 * @return the name of this class "cWidgetFibScalar"
 */
std::string cWidgetFibScalar::getName() const{
	
	return std::string( "cWidgetFibScalar" );
}


/**
 * @return a hint for a good size of this window
 */
QSize cWidgetFibScalar::sizeHint() const{
	
	DEBUG_OUT_L2(<<"cWidgetFibScalar("<<this<<")::sizeHint() called (pFibScalar="<<pFibScalar<<")"<<endl<<flush);
	
	if ( pFibScalar ){
		//evalue size hint with the help of the sub elements
		const QSize sizeLineEditValue = pLineEditValue->sizeHint();
		
		return QSize( pButtonDecrease->sizeHint().width() * 4,
			pLabelVariable->sizeHint().height() + sizeLineEditValue.height() );
		/*return QSize( pButtonDecrease->sizeHint().width() +
			sizeLineEditValue.width() + pButtonIncrease->sizeHint().width(),
			pLabelVariable->sizeHint().height() + sizeLineEditValue.height() );*/
	}//else use default values
	return QSize( 64, 20 );
}



/**
 * This method sets the value of the Fib scalar to the given value.
 *
 * @see pFibScalar
 * @param strNewValue the string which contains the to set value for
 * 	the scalar
 * @return true if the readed value could be set, else false
 */
bool cWidgetFibScalar::setScalarValue( const QString & strNewValue ){
	
	DEBUG_OUT_L2(<<"cWidgetFibScalar("<<this<<")::setScalarValue( strNewValue="<<strNewValue.toStdString()<<") called"<<endl<<flush);
	if ( pFibScalar == NULL ){
		//no scalar where to set the values
		return false;
	}
	bool bReadedValueOk = true;
	const double dReadedValue = strNewValue.toDouble( &bReadedValueOk );
	
	if ( ! bReadedValueOk ){
		//value could not be read
		return false;
	}//else readed value OK
	pFibScalar->setValue( dReadedValue );
	return true;
}









