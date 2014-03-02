
//TODO check

/**
 * @file iFibGraphicsItemFactory
 * file name: iFibGraphicsItemFactory.h
 * @author Betti Oesterholz
 * @date 21.01.2014
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a interface for a factory, which generates a
 * graphics item form a Fib object.
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
 * This file specifies a interface for a factory, which generates a
 * graphics item form a Fib object.
 * It should be the implemented by all such factories.
 * To generate a Fib graphics item from a Fib objects this factory analysis
 * the Fib object.
 * The returned Fib graphics item correspondents to a Fib object.
 *
 * @pattern factory
 * @pattern functor
 * @pattern interface
 * @see QFibGraphicsItem
 * @see QGraphicsScene
 * @see cFibGraphicsScene
 * @see QGraphicsItem
 */
/*
History:
21.01.2014  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__I_FIB_GRAPHICS_ITEM_FACTORY_H__
#define ___FIB__NCREATOR__I_FIB_GRAPHICS_ITEM_FACTORY_H__


#include "version.h"

#include "cFibElement.h"

#include <string>

#include "cFibGraphicsItem.h"


namespace fib{

namespace nCreator{

//forward declarations
class cFibGraphicsItem;

class iFibGraphicsItemFactory{

public:
	
	/**
	 * destructor
	 */
	virtual ~iFibGraphicsItemFactory() {};
	
	
	/**
	 * @return the name of this class "iFibGraphicsItemFactory"
	 */
	virtual std::string getName() const = 0;
	
	
	/**
	 * This operator uses this factory to generate a Fib graphics item for
	 * a Fib object.
	 * Beware: You have to care, that the returned Fib graphics item is deleted.
	 *
	 * @param pFibObject a pointer to the Fib object, for which a Fib
	 * 	graphics item should be generated
	 * @return a pointer to the generated Fib graphics item, which represents
	 * 	the given Fib object, or NULL, if non could be generated
	 */
	virtual cFibGraphicsItem * operator()( cFibElement * pFibObject ) const = 0;
	
};//end class iFibGraphicsItemFactory

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__I_FIB_GRAPHICS_ITEM_FACTORY_H__





