
//TODO check

/**
 * @file cWidgetFibInputVariables
 * file name: cWidgetFibInputVariables.cpp
 * @author Betti Oesterholz
 * @date 23.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a list of variable widgets.
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
 * This file implements a class for a list of variable widgets.
 * If you have a Fib object, the input variables of it are root object
 * input variables or variables used in the Fib object but not defined in it.
 * With this class you can display these.
 *
 * @see cFibInputVariable
 * @see cFibVariable
 */
/*
History:
23.08.2013  Oesterholz  created
*/

//TODO switches for test proposes
#define DEBUG

#include "cWidgetFibInputVariables.h"

#include "nFibObjectTools.h"


using namespace fib::nCreator;
using namespace fib;




/**
 * standard constructor for a list of input variable widgets
 * It constructs a list of input variables with no input variables. (So
 * you can add them later.)
 */
cWidgetFibInputVariables::cWidgetFibInputVariables():cFibInputVariables(){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::cWidgetFibInputVariables() called"<<endl<<flush);
	pInputVariableLayout = new cFlowLayout( this );
	setLayout( pInputVariableLayout );
}


/**
 * parameter constructor for a list of input variable widgets
 *
 * @param liInInputVariables list with input variables for this object
 * 	@see inputVariables
 * @param pInFibObject the Fib object for which the input variables are or NULL
 * 	@see pFibObject
 */
cWidgetFibInputVariables::cWidgetFibInputVariables(
		QList< cFibInputVariable * > & liInInputVariables,
		cFibElement * pInFibObject ):
		cFibInputVariables( liInInputVariables, pInFibObject ){
			
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::cWidgetFibInputVariables( liInInputVariables, pInFibObject="<<pInFibObject<<") called"<<endl<<flush);
	//create input variable widgets
	mutexFibNodeHandler.lock();
	pInputVariableLayout = new cFlowLayout( this );
	for ( QList< cFibInputVariable * >::iterator
			itrActualInVar = inputVariables.begin();
			itrActualInVar != inputVariables.end(); itrActualInVar++ ){
		
		if ( mapInputVariables.constFind( *itrActualInVar ) ==
				mapInputVariables.constEnd() ){
			//the variable was not registered before
			mapInputVariables.insert( *itrActualInVar,
				new cWidgetFibInputVariable( *itrActualInVar, this ) );
		}
		pInputVariableLayout->addWidget( mapInputVariables[ *itrActualInVar ] );
	}
	setLayout( pInputVariableLayout );
	mutexFibNodeHandler.unlock();
}


/**
 * parameter constructor for a list of input variable widgets
 *
 * @param pInFibObject the Fib object for which the input variables are or NULL
 * 	@see pFibObject
 * @param bFindInputVariables if true it will evalue the input variables
 * 	for the given Fib object.
 * 	It will evalue all variables used in the Fib object, but not
 * 	defined in it. Also input variables are input variables of the
 * 	root element pFibObject, if pFibObject is a root element.
 * 	@see nFibObjectTools::evalueInputVariables()
 * 	Also the list will be updated for input variables changes.
 * 	If bFindInputVariables is false, this constructor constructs a
 * 	list of input variables with no input variables. (So you can add
 * 	them later.)
 * @param bTillRoot if true searches for input variables in the Fib
 * 	object for pFibObject till the root Fib element (Fib element
 * 	with no superior), else the input variables for pFibObject will
 * 	be returned
 */
cWidgetFibInputVariables::cWidgetFibInputVariables( cFibElement * pInFibObject,
		const bool bFindInputVariables, const bool bTillRoot ):
		cFibInputVariables( pInFibObject, bFindInputVariables, bTillRoot ){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::cWidgetFibInputVariables( pInFibObject="<<pInFibObject<<", bFindInputVariables="<<(bFindInputVariables?"true":"false")<<") called"<<endl<<flush);
	//create input variable widgets
	mutexFibNodeHandler.lock();
	pInputVariableLayout = new cFlowLayout( this );
	for ( QList< cFibInputVariable * >::iterator
			itrActualInVar = inputVariables.begin();
			itrActualInVar != inputVariables.end(); itrActualInVar++ ){
		
		if ( mapInputVariables.constFind( *itrActualInVar ) ==
				mapInputVariables.constEnd() ){
			//the variable was not registered before
			mapInputVariables.insert( *itrActualInVar,
				new cWidgetFibInputVariable( *itrActualInVar, this ) );
		}
		pInputVariableLayout->addWidget( mapInputVariables[ *itrActualInVar ] );
	}
	setLayout( pInputVariableLayout );
	mutexFibNodeHandler.unlock();
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::cWidgetFibInputVariables( pInFibObject="<<pInFibObject<<", bFindInputVariables="<<(bFindInputVariables?"true":"false")<<") done "<<inputVariables.size()<<" input variables created"<<endl<<flush);
}


/**
 * copy constructor for a list of input variable widgets
 *
 * @param fibInputVariables the input variables to copy
 */
cWidgetFibInputVariables::cWidgetFibInputVariables(
		cWidgetFibInputVariables & fibInputVariables ):
	QWidget( fibInputVariables.parentWidget() ),
	cFibInputVariables( fibInputVariables ){
		
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::cWidgetFibInputVariables( fibInputVariables ) called"<<endl<<flush);
	//create input variable widgets
	mutexFibNodeHandler.lock();
	pInputVariableLayout = new cFlowLayout( this );
	for ( QList< cFibInputVariable * >::iterator
			itrActualInVar = inputVariables.begin();
			itrActualInVar != inputVariables.end(); itrActualInVar++ ){
		
		if ( mapInputVariables.constFind( *itrActualInVar ) ==
				mapInputVariables.constEnd() ){
			//the variable was not registered before
			mapInputVariables.insert( *itrActualInVar,
				new cWidgetFibInputVariable( *itrActualInVar, this ) );
		}
		pInputVariableLayout->addWidget( mapInputVariables[ *itrActualInVar ] );
	}
	setLayout( pInputVariableLayout );
	mutexFibNodeHandler.unlock();
}


/**
 * destructor
 */
cWidgetFibInputVariables::~cWidgetFibInputVariables(){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::~cWidgetFibInputVariables() called"<<endl<<flush);
	//unregister this as input variable change listener at input variables
	mutexFibNodeHandler.lock();
	for ( QMap< cFibInputVariable *, cWidgetFibInputVariable * >::iterator
			itrActualInVar = mapInputVariables.begin();
			itrActualInVar != mapInputVariables.end(); itrActualInVar++ ){
		//delete input variable widget
		delete itrActualInVar.value();
	}
	mutexFibNodeHandler.unlock();
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::~cWidgetFibInputVariables() done"<<endl<<flush);
}


/**
 * @return the name of this class "cWidgetFibInputVariables"
 */
std::string cWidgetFibInputVariables::getName() const{
	
	return std::string( "cWidgetFibInputVariables" );
}


/**
 * This method adds the given input variable to this input variable list.
 *
 * @see inputVariables
 * @see getNumberOfInputVariables()
 * @see removeInputVariable()
 * @see replaceInputVariable()
 * @param pInputVariable a pointer to the input variable to add
 * @param uiPosition the position where to add the input variable,
 * 	if 0 or greater the number of input variables in this input
 * 	variable list it will be added to the end of the input variable list
 * 	(counting starts with 1)
 * @return true if the input variable was added, else false
 */
bool cWidgetFibInputVariables::addInputVariable( cFibInputVariable * pInputVariable,
		const unsigned int uiPosition ){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::addInputVariable( pInputVariable="<<pInputVariable<<") called"<<endl<<flush);
	if ( cFibInputVariables::addInputVariable( pInputVariable, uiPosition ) ){
	
		mutexFibNodeHandler.lock();
		if ( mapInputVariables.constFind( pInputVariable ) ==
				mapInputVariables.constEnd() ){
			//the variable was not registered before
			mapInputVariables.insert( pInputVariable,
				new cWidgetFibInputVariable( pInputVariable, this ) );
		}
		pInputVariableLayout->addWidget(
			mapInputVariables[ pInputVariable ], uiPosition );
		mutexFibNodeHandler.unlock();
		return true;
	}
	return false;
}


/**
 * This method removes the uiPosition'th input variable from this input
 * variable list.
 *
 * @see inputVariables
 * @see getNumberOfInputVariables()
 * @see addInputVariable()
 * @see replaceInputVariable()
 * @param uiPosition the position where to remove the input variable from
 * 	(counting starts with 1)
 * @return true if the input variable was removed, else false
 */
bool cWidgetFibInputVariables::removeInputVariable( const unsigned int uiPosition ){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::removeInputVariable( uiPosition="<<uiPosition<<") called"<<endl<<flush);
	cFibInputVariable * pInputVariable = inputVariables.at( uiPosition );
	if ( cFibInputVariables::removeInputVariable( uiPosition ) ){
		//Fib input variable was removed
		mutexFibNodeHandler.lock();
		if ( ! inputVariables.contains( pInputVariable ) ){
			//the input variable dosn't exist anymore -> remove the widget for it
			QMap< cFibInputVariable *, cWidgetFibInputVariable * >::iterator
				itrVariable = mapInputVariables.find( pInputVariable );
			
			delete (itrVariable.value());
			mapInputVariables.erase( itrVariable );
		}
		pInputVariableLayout->removeWidget( uiPosition, false );
		mutexFibNodeHandler.unlock();
		return true;
	}
	return false;
}


/**
 * This method removes the given input variable from this input
 * variable list.
 *
 * @see inputVariables
 * @see getNumberOfInputVariables()
 * @see addInputVariable()
 * @see replaceInputVariable()
 * @param pInputVariable the input variable to remove
 * @return true if the input variable was removed, else false
 */
bool cWidgetFibInputVariables::removeInputVariable(
		cFibInputVariable * pInputVariable ){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::removeInputVariable( pInputVariable="<<pInputVariable<<") called"<<endl<<flush);
	if ( cFibInputVariables::removeInputVariable( pInputVariable ) ){
		//Fib input variable was removed
		mutexFibNodeHandler.lock();
		//the input variable dosn't exist anymore -> remove the widget for it
		QMap< cFibInputVariable *, cWidgetFibInputVariable * >::iterator
			itrVariable = mapInputVariables.find( pInputVariable );
		
		delete (itrVariable.value());
		mapInputVariables.erase( itrVariable );
		//update the layout
		pInputVariableLayout->clear();
		for ( QList< cFibInputVariable * >::iterator
				itrActualInVar = inputVariables.begin();
				itrActualInVar != inputVariables.end(); itrActualInVar++ ){
			
			pInputVariableLayout->addWidget( mapInputVariables[ *itrActualInVar ] );
		}
		
		mutexFibNodeHandler.unlock();
		return true;
	}
	return false;
}


/**
 * This method replaces a input variable in this input variable list.
 * It will replace the uiPosition'th input variable in the input
 * variable list with the given input variable pInputVariable (if possible).
 *
 * @see inputVariables
 * @see getNumberOfInputVariables()
 * @see removeInputVariable()
 * @see addInputVariable()
 * @param pInputVariable a pointer to the input variable to add,
 * 	which will replace the old input variable on the uiPosition'th position
 * @param uiPosition the position where to replace the input variable,
 * 	(counting starts with 1)
 * @return true if the input variable was replace, else false
 */
bool cWidgetFibInputVariables::replaceInputVariable( cFibInputVariable * pInputVariable,
		const unsigned int uiPosition ){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::replaceInputVariable( pInputVariable="<<pInputVariable<<", uiPosition="<<uiPosition<<") called"<<endl<<flush);
	cFibInputVariable * pRemovedInputVariable = inputVariables.at( uiPosition );
	if ( cFibInputVariables::replaceInputVariable( pInputVariable, uiPosition ) ){
		//Fib input variable was removed
		mutexFibNodeHandler.lock();
		if ( ! inputVariables.contains( pRemovedInputVariable ) ){
			//the input variable dosn't exist anymore -> remove the widget for it
			QMap< cFibInputVariable *, cWidgetFibInputVariable * >::iterator
				itrVariable = mapInputVariables.find( pRemovedInputVariable );
			
			delete (itrVariable.value());
			mapInputVariables.erase( itrVariable );
		}
		if ( mapInputVariables.constFind( pInputVariable ) ==
				mapInputVariables.constEnd() ){
			//the variable was not registered before
			mapInputVariables.insert( pInputVariable,
				new cWidgetFibInputVariable( pInputVariable, this ) );
		}
		//update the layout
		pInputVariableLayout->removeWidget( uiPosition, false );
		pInputVariableLayout->addWidget(
			mapInputVariables[ pInputVariable ], uiPosition );
		
		mutexFibNodeHandler.unlock();
		return true;
	}
	return false;
}


/**
 * This method sets the list of input variables to the given list.
 * All old input variables of this list are removed and the given input
 * added.
 *
 * @see inputVariables
 * @see getNumberOfInputVariables()
 * @see replaceInputVariable()
 * @see removeInputVariable()
 * @see addInputVariable()
 * @param liInInputVariables a list of the input variables this object
 * 	should contain
 * @return true if the input variables could be set, else false
 */
bool cWidgetFibInputVariables::setInputVariables(
		QList< cFibInputVariable * > & liInInputVariables ){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::setInputVariables( liInInputVariables=#"<<liInInputVariables.size()<<") called"<<endl<<flush);
	if ( cFibInputVariables::setInputVariables( liInInputVariables ) ){
		mutexFibNodeHandler.lock();
		//delete old input variable widgets
		for ( QMap< cFibInputVariable *, cWidgetFibInputVariable * >::iterator
				itrActualInVar = mapInputVariables.begin();
				itrActualInVar != mapInputVariables.end(); itrActualInVar++ ){
			//delete input variable widget
			delete (itrActualInVar.value());
		}
		mapInputVariables.clear();
		//update the layout
		pInputVariableLayout->clear();
		//create widgets for new input variable
		for ( QList< cFibInputVariable * >::iterator
				itrActualInVar = inputVariables.begin();
				itrActualInVar != inputVariables.end(); itrActualInVar++ ){
			
			if ( mapInputVariables.constFind( *itrActualInVar ) ==
					mapInputVariables.constEnd() ){
				//the variable was not registered before
				mapInputVariables.insert( *itrActualInVar,
					new cWidgetFibInputVariable( *itrActualInVar, this ) );
			}
			//update the layout
			pInputVariableLayout->addWidget( mapInputVariables[ *itrActualInVar ] );
		}
		mutexFibNodeHandler.unlock();
		return true;
	}
	return false;
}


/**
 * Event method
 * It will be called every time a input variable (cFibInputVariable),
 * at which this object is registered,was changed.
 *
 * @param pFibInputVariableEvent a pointer to the event with the
 * 	information of the change of the Fib input variable
 */
void cWidgetFibInputVariables::fibInputVariableChangedEvent(
		const eFibInputVariableChangedEvent * pFibInputVariableEvent ){
	
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::fibInputVariableChangedEvent( pFibInputVariableEvent="<<pFibInputVariableEvent<<") called"<<endl<<flush);
	if ( pFibInputVariableEvent == NULL ){
		//no event given
		return;
	}
	if ( pFibInputVariableEvent->bInputVariableDeleted ){
		//remove deleted input variable
		DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::fibInputVariableChangedEvent( pFibInputVariableEvent="<<pFibInputVariableEvent<<") remove deleted input variable"<<endl<<flush);
		mutexFibNodeHandler.lock();
		cFibInputVariable * pInputVariable = const_cast<cFibInputVariable*>(
			pFibInputVariableEvent->pInputVariableChanged );
		inputVariables.removeAll( pInputVariable );
		
		//the input variable don't exist anymore -> remove the widget for it
		QMap< cFibInputVariable *, cWidgetFibInputVariable * >::iterator
			itrVariable = mapInputVariables.find( pInputVariable );
		delete (itrVariable.value());
		mapInputVariables.erase( itrVariable );
		//update the layout
		pInputVariableLayout->clear();
		for ( QList< cFibInputVariable * >::iterator
				itrActualInVar = inputVariables.begin();
				itrActualInVar != inputVariables.end(); itrActualInVar++ ){
			
			pInputVariableLayout->addWidget( mapInputVariables[ *itrActualInVar ] );
		}
		
		mutexFibNodeHandler.unlock();
	}
	cFibInputVariables::fibInputVariableChangedEvent( pFibInputVariableEvent );
	DEBUG_OUT_L2(<<"cWidgetFibInputVariables("<<this<<")::fibInputVariableChangedEvent( pFibInputVariableEvent="<<pFibInputVariableEvent<<") done"<<endl<<flush);
}





