
//TODO check

/**
 * @file cFibGraphicsItemImageFactory
 * file name: cFibGraphicsItemImageFactory.h
 * @author Betti Oesterholz
 * @date 21.01.2014
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a factory, which generates a image
 * Fib graphics item form a Fib object.
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
 * This file specifies a class for a factory, which generates a image
 * Fib graphics item form a Fib object.
 * To generate a image Fib graphics item from a Fib objects this factory
 * analysis the Fib object.
 * The returned Fib graphics item correspondents to a Fib object and is a
 * image graphics item.
 *
 * @pattern factory
 * @pattern functor
 * @see QFibGraphicsItem
 * @see QGraphicsScene
 * @see cFibGraphicsScene
 * @see QGraphicsItem
 */
/*
History:
21.01.2014  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_FIB_GRAPHICS_ITEM_IMAGE_FACTORY_H__
#define ___FIB__NCREATOR__C_FIB_GRAPHICS_ITEM_IMAGE_FACTORY_H__


#include "version.h"

#include "cFibElement.h"

#include <string>

#include "iFibGraphicsItemFactory.h"
#include "cFibGraphicsScene.h"
#include "cFibGraphicsItem.h"


namespace fib{

namespace nCreator{

class cFibGraphicsItemImageFactory: public iFibGraphicsItemFactory{

public:
	
	/**
	 * The constructor of the factory.
	 *
	 * @param ulInFibNodeVersion the version of the Fib object for the node,
	 * 	which is converted / displayed.
	 * 	@see ulFibNodeVersion
	 * @param pInFibGraphicsScene a pointer to the graphic scene, for which
	 * 	the generated graphic items are
	 * 	@see pFibGraphicsScene
	 */
	cFibGraphicsItemImageFactory( const unsigned long ulInFibNodeVersion,
		cFibGraphicsScene * pInFibGraphicsScene );
	
	/**
	 * destructor
	 */
	virtual ~cFibGraphicsItemImageFactory();
	
	
	/**
	 * @return the name of this class "cFibGraphicsItemImageFactory"
	 */
	virtual std::string getName() const;
	
	
	/**
	 * This operator uses this factory to generate a Fib graphics item for
	 * a Fib object.
	 * Beware: You have to care, that the returned Fib graphics item is deleted.
	 *
	 * @param pFibObject a pointer to the Fib object, for which a Fib
	 * 	graphics item should be generated
	 * @return a pointer to the generated image Fib graphics item, which
	 * 	represents the given Fib object, or NULL, if non could be generated
	 */
	virtual cFibGraphicsItem * operator()( cFibElement * pFibObject ) const;
	
protected:
	
	/**
	 * The version of the Fib object for the node, which is converted / displayed.
	 * Every time the Fib object is changed the version number is counted up.
	 * If this number is not equal to the Fib node version number the shown
	 * Fib object needs to be updated.
	 * @see cFibNode::ulVersion
	 * @see cFibNode::fibObjectChanged()
	 */
	unsigned long ulFibNodeVersion;
	
	/**
	 * Aa pointer to the graphic scene, for which the generated graphic
	 * items are.
	 */
	cFibGraphicsScene * pFibGraphicsScene;

};//end class cFibGraphicsItemImageFactory

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_GRAPHICS_ITEM_IMAGE_FACTORY_H__





