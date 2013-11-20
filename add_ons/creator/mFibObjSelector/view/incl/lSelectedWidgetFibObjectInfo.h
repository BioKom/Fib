/**
 * @file lSelectedWidgetFibObjectInfo
 * file name: lSelectedWidgetFibObjectInfo.h
 * @author Betti Oesterholz
 * @date 19.10.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a listener interface for listening if a Fib object
 * info widget was selected.
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
 * This file specifies a listener interface for listening if a Fib object
 * info widget was selected.
 *
 * @see cWidgetFibObjectInfo
 * @see cWidgetFibObjectInfos
 * @see cDialogSelectFibObject
 */
/*
History:
19.10.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__L_SELECTED_WIDGET_FIB_OBJECT_INFO_H__
#define ___FIB__NCREATOR__L_SELECTED_WIDGET_FIB_OBJECT_INFO_H__


#include "version.h"

#include <string>


namespace fib{

namespace nCreator{


//forward declarations
class cWidgetFibObjectInfo;

class lSelectedWidgetFibObjectInfo{
public:
	
	/**
	 * Event method
	 * This method will be called if an Fib object info widget was
	 * selected.
	 *
	 * @param pWidgetFibObjectInfo a pointer to the Fib object info
	 * 	widget which was selected
	 */
	virtual void selectWidgetFibObjectInfo(
		const cWidgetFibObjectInfo * pWidgetFibObjectInfo ) = 0;
	
	/**
	 * @return the name of this class
	 */
	virtual std::string getName() const = 0;
	
};//end class selectWidgetFibObjectInfo

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__L_SELECTED_WIDGET_FIB_OBJECT_INFO_H__





