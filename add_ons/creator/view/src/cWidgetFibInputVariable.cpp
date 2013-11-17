
//TODO check

/**
 * @file cWidgetFibInputVariable
 * file name: cWidgetFibInputVariable.cpp
 * @author Betti Oesterholz
 * @date 27.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a widget for a Fib input variable.
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
 * This file implements a class for a widget for a Fib input variable.
 * It will display one input variable. This input variable is represented
 * by a name and a value.
 *
 * @see cFibInputVariable
 * @see cFibVariable
 */
/*
History:
27.08.2013  Oesterholz  created
*/


#include "cWidgetFibInputVariable.h"

#include <QDoubleValidator>


//TODO switches for test proposes
#define DEBUG



using namespace fib::nCreator;



/**
 * standard constructor for a Fib object node
 *
 * @param pInFibInputVariable a pointer to the input variable to display
 * @param pParent a pointer the parent of this new Fib object dialog window
 */
cWidgetFibInputVariable::cWidgetFibInputVariable(
		cFibInputVariable * pInFibInputVariable, QWidget * pParent ):
		QWidget( pParent ), pFibInputVariable( pInFibInputVariable ),
		pLabelVariable( NULL ), pLineEditValue( NULL ),
		pButtonDecrease( NULL ), pButtonIncrease( NULL ),
		pLayoutMain( NULL ), pLayoutValue( NULL ){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariable("<<this<<")::cWidgetFibInputVariable( pInFibInputVariable="<<pInFibInputVariable<<", pParent="<<pParent<<") called"<<endl<<flush);
	if ( pFibInputVariable == NULL ){
		//no input variable -> no widget
		return;
	}
	//register this object as a listener for changes of the input variable
	pFibInputVariable->registerInputVariableChangeListener( this );
	//TODO
	//except any double
	QDoubleValidator * pValidatorValue = new QDoubleValidator( this );
		//TODO?? use variable domain vor the validator
	
	//create variable name label
	pLabelVariable = new QLabel( pFibInputVariable->getVariableName(), this );
	pLabelVariable->setAlignment( Qt::AlignHCenter );
	
	pLineEditValue = new QLineEdit( this );
	pLabelVariable->setBuddy( pLineEditValue );
	
	QString strVariableValue;
	strVariableValue.setNum( pFibInputVariable->getValue(), 'g', 6 );
	
	pLineEditValue->setText( strVariableValue );
	pLineEditValue->setAlignment( Qt::AlignHCenter );
	pLineEditValue->setValidator( pValidatorValue );
	
	connect( pLineEditValue, SIGNAL( textChanged( const QString ) ),
		this, SLOT( setVariableValue( const QString ) ) );
	
	//create decrease button
	pButtonDecrease = new QPushButton( tr("<"), this );
	pButtonDecrease->setDefault( true );
	pButtonDecrease->setAutoRepeat( true );
	connect( pButtonDecrease, SIGNAL( pressed() ),
		pFibInputVariable, SLOT( decreaseValue() ) );
	connect( pFibInputVariable, SIGNAL( decreaseValuePossible( bool ) ),
		pButtonDecrease, SLOT( setEnabled( bool ) ) );
	
	//create increase button
	pButtonIncrease = new QPushButton( tr(">"), this );
	pButtonIncrease->setDefault( true );
	pButtonIncrease->setAutoRepeat( true );
	connect( pButtonIncrease, SIGNAL( pressed() ),
		pFibInputVariable, SLOT( increaseValue() ) );
	connect( pFibInputVariable, SIGNAL( increaseValuePossible( bool ) ),
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
cWidgetFibInputVariable::~cWidgetFibInputVariable(){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariable("<<this<<")::~cWidgetFibInputVariable() called"<<endl<<flush);
	if ( pFibInputVariable ){
		//unregister this object as a listener for changes of the input variable
		pFibInputVariable->unregisterInputVariableChangeListener( this );
	}
}


/**
 * @return the pointer to the input variable for the widget
 */
cFibInputVariable * cWidgetFibInputVariable::getFibInputVariable(){
	
	return pFibInputVariable;
}


/**
 * @return the pointer to the input variable for the widget
 */
const cFibInputVariable * cWidgetFibInputVariable::getFibInputVariable() const{
	
	return pFibInputVariable;
}


/**
 * Event method
 * It will be called every time a input variable (cFibInputVariable),
 * at which this object is registered,was changed.
 *
 * @param pFibInputVariableEvent a pointer to the event with the
 * 	information of the change of the Fib input variable
 */
void cWidgetFibInputVariable::fibInputVariableChangedEvent(
		const eFibInputVariableChangedEvent * pFibInputVariableEvent ){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariable("<<this<<")::fibInputVariableChangedEvent( pFibInputVariableEvent="<<pFibInputVariableEvent<<" ) called"<<endl<<flush);
	if ( pFibInputVariableEvent == NULL ){
		//no event given
		return;
	}
	if ( pFibInputVariableEvent->bInputVariableDeleted ){
		//remove deleted input variable
		if ( pFibInputVariable ){
			//unregister this object as a listener for changes of the input variable
			pFibInputVariable->unregisterInputVariableChangeListener( this );
			pFibInputVariable = NULL;
		}
	}
	
	if ( pFibInputVariable &&
			( pFibInputVariable == pFibInputVariableEvent->pInputVariableChanged ) ){
		//set the new values
		pLabelVariable->setText( pFibInputVariable->getVariableName() );
		
		QString strVariableValue;
		strVariableValue.setNum( pFibInputVariable->getValue(), 'g', 6 );
		pLineEditValue->setText( strVariableValue );
	}
}


/**
 * @return the name of this class "cWidgetFibInputVariable"
 */
std::string cWidgetFibInputVariable::getName() const{
	
	return std::string( "cWidgetFibInputVariable" );
}


/**
 * @return a hint for a good size of this window
 */
QSize cWidgetFibInputVariable::sizeHint() const{
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariable("<<this<<")::sizeHint() called (pFibInputVariable="<<pFibInputVariable<<")"<<endl<<flush);
	
	if ( pFibInputVariable ){
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
 * This method sets the value of the Fi input variable to the given value.
 *
 * @see pFibInputVariable
 * @param strNewValue the string which contains the to set value for
 * 	the variable
 * @return true if the readed value could be set, else false
 */
bool cWidgetFibInputVariable::setVariableValue( const QString & strNewValue ){
	
	if ( pFibInputVariable == NULL ){
		//no input variable where to set the values
		return false;
	}
	bool bReadedValueOk = true;
	const double dReadedValue = strNewValue.toDouble( &bReadedValueOk );
	
	if ( ! bReadedValueOk ){
		//value could not be read
		return false;
	}//else readed value OK
	pFibInputVariable->setValue( dReadedValue );
	return true;
}









