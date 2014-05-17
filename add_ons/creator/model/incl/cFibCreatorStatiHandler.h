
//TODO check

/**
 * @file cFibCreatorStatiHandler
 * file name: cFibCreatorStatiHandler.h
 * @author Betti Oesterholz
 * @date 12.03.2014
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class to store the Fib creator application stati.
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
 * This file specifies a class to store the Fib creator application stati.
 * @pattern singleton
 */
/*
History:
12.03.2014  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_FIB_CREATOR_STATI_HANDLER_H__
#define ___FIB__NCREATOR__C_FIB_CREATOR_STATI_HANDLER_H__


#include "version.h"
#include "versionCreator.h"

#include <QObject>
#include <QMutex>

#include <string>


namespace fib{

namespace nCreator{


namespace nFibCreatorStatiHandler{
	//cyclic dependencies
	class cFibCreatorStatiHandlerDeleter;
}


class cFibCreatorStatiHandler: public QObject{
	Q_OBJECT

friend class nFibCreatorStatiHandler::cFibCreatorStatiHandlerDeleter;

public:
	
	/**
	 * This type (enum) is for mouse mode type.
	 * It influences what how the mouse works.
	 */
	enum typeMouseMode{
		POINTING = 0,///mouse is for pointing
		DRAWING  = 1///mouse is for drawing
	};
	
	
	/**
	 * destructor
	 */
	virtual ~cFibCreatorStatiHandler();
	
	/**
	 * @return a instance of the Fib creator stati handler
	 */
	static cFibCreatorStatiHandler * getInstance();
	
	
	/**
	 * @return the name of this class "cFibCreatorStatiHandler"
	 */
	virtual std::string getName() const;
	
	/**
	 * @returns the actual mouse mode
	 * @see actualMouseMode
	 * @see typeMouseMode
	 */
	static typeMouseMode getActualMouseMode();
	
	/**
	 * This method sets the actual mouse mode.
	 *
	 * @see actualMouseMode
	 * @see typeMouseMode
	 * @param inActualMouseMode the mouse mode to set
	 */
	static void setActualMouseModeStatic( const typeMouseMode inActualMouseMode );
	
public slots:
	
	/**
	 * This method sets the actual mouse mode.
	 *
	 * @see actualMouseMode
	 * @see typeMouseMode
	 * @param inActualMouseMode the mouse mode to set
	 */
	void setActualMouseMode( const typeMouseMode inActualMouseMode );
	
	/**
	 * This method sets the actual mouse mode to pointing.
	 *
	 * @see actualMouseMode
	 * @see typeMouseMode::POINTING
	 */
	void setMouseModeToPointing();
	
	/**
	 * This method sets the actual mouse mode to drawing.
	 *
	 * @see actualMouseMode
	 * @see typeMouseMode::DRAWING
	 */
	void setMouseModeToDrawing();
	
protected:
	
	
	/**
	 * standard constructor for the stati handler
	 */
	cFibCreatorStatiHandler();
	
///members:
	
	/**
	 * A pointer to the stati handler object.
	 */
	static cFibCreatorStatiHandler * pFibCreatorStatiHandler;
	
	/**
	 * The actual mouse mode.
	 * @see typeMouseMode
	 */
	static typeMouseMode actualMouseMode;
	

};//end class cFibCreatorStatiHandler

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_CREATOR_STATI_HANDLER_H__





