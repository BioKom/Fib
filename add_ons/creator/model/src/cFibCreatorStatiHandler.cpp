
//TODO check

/**
 * @file cFibCreatorStatiHandler
 * file name: cFibCreatorStatiHandler.cpp
 * @author Betti Oesterholz
 * @date 12.03.2014
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class to store the Fib creator application stati.
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
 * This file implements a class to store the Fib creator application stati.
 * @pattern singleton
 */
/*
History:
12.03.2014  Oesterholz  created
*/



#include "cFibCreatorStatiHandler.h"


using namespace fib::nCreator;



/**
 * A pointer to the stati handler object.
 */
cFibCreatorStatiHandler *
	cFibCreatorStatiHandler::pFibCreatorStatiHandler = NULL;

/**
 * The actual mouse mode.
 * @see typeMouseMode
 */
cFibCreatorStatiHandler::typeMouseMode
	cFibCreatorStatiHandler::actualMouseMode = POINTING;


namespace fib{
namespace nCreator{
namespace nFibCreatorStatiHandler{

	/**
	 * This class is for deleting the Fib stati handler when the programm ends.
	 * @see cFibNodeHandler
	 */
	class cFibCreatorStatiHandlerDeleter{
	public:
		
		/**
		 * destructor which deletes the Fib stati handler if not allready deleted
		 */
		~cFibCreatorStatiHandlerDeleter() {
			
			if ( cFibCreatorStatiHandler::pFibCreatorStatiHandler != NULL ) {
				//delete node handler
				delete cFibCreatorStatiHandler::pFibCreatorStatiHandler;
				cFibCreatorStatiHandler::pFibCreatorStatiHandler = NULL;
			}
		}
		
	};//end class cFibCreatorStatiHandlerDeleter
	
	/**
	 * Object to delete the Fib stati handler when the programm ends.
	 */
	cFibCreatorStatiHandlerDeleter fibStatiHandlerDeleter;
	
};//end namespace nFibCreatorStatiHandler
};//end namespace nCreator
};//end namespace fib





/**
 * standard constructor for the stati handler
 */
cFibCreatorStatiHandler::cFibCreatorStatiHandler() {
	
	pFibCreatorStatiHandler = this;
}


/**
 * destructor
 */
cFibCreatorStatiHandler::~cFibCreatorStatiHandler() {
	pFibCreatorStatiHandler = NULL;
}

/**
 * @return a instance of the Fib creator stati handler
 */
cFibCreatorStatiHandler * cFibCreatorStatiHandler::getInstance() {
	
	if ( pFibCreatorStatiHandler == NULL ) {
		//create a new instance
		pFibCreatorStatiHandler = new cFibCreatorStatiHandler();
	}//else return existing instance
	return pFibCreatorStatiHandler;
}


/**
 * @return the name of this class "cFibCreatorStatiHandler"
 */
std::string cFibCreatorStatiHandler::getName() const {
	
	return std::string( "cFibCreatorStatiHandler" );
}


/**
 * @returns the actual mouse mode
 * @see actualMouseMode
 * @see typeMouseMode
 */
cFibCreatorStatiHandler::typeMouseMode
		cFibCreatorStatiHandler::getActualMouseMode() {
	
	return actualMouseMode;
}


/**
 * This method sets the actual mouse mode.
 *
 * @see actualMouseMode
 * @see typeMouseMode
 * @param inActualMouseMode the mouse mode to set
 */
void cFibCreatorStatiHandler::setActualMouseModeStatic(
		const typeMouseMode inActualMouseMode ) {
	
	actualMouseMode = inActualMouseMode;
}


/**
 * This method sets the actual mouse mode.
 *
 * @see actualMouseMode
 * @see typeMouseMode
 * @param inActualMouseMode the mouse mode to set
 */
void cFibCreatorStatiHandler::setActualMouseMode(
		const typeMouseMode inActualMouseMode ) {
	
	actualMouseMode = inActualMouseMode;
}


/**
 * This method sets the actual mouse mode to pointing.
 *
 * @see actualMouseMode
 * @see typeMouseMode::POINTING
 */
void cFibCreatorStatiHandler::setMouseModeToPointing() {
	
	actualMouseMode = POINTING;
}


/**
 * This method sets the actual mouse mode to drawing.
 *
 * @see actualMouseMode
 * @see typeMouseMode::DRAWING
 */
void cFibCreatorStatiHandler::setMouseModeToDrawing() {
	
	actualMouseMode = DRAWING;
}





