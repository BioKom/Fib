
//TODO check

/**
 * @file cFibGraphicsItemImageFactory
 * file name: cFibGraphicsItemImageFactory.cpp
 * @author Betti Oesterholz
 * @date 21.01.2014
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a factory, which generates a image
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
 * This file implements a class for a factory, which generates a image
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
 * @see cFibGraphicsItemImageFactory
 * @see QGraphicsItem
 */
/*
History:
21.01.2014  Oesterholz  created
*/


#include "cFibGraphicsItemImageFactory.h"


#include "cFibGraphicsItemFibList.h"
#include "cFibGraphicsItemFibObject.h"
#include "cFibGraphicsItemFibExtObject.h"


using namespace fib::nCreator;

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
cFibGraphicsItemImageFactory::cFibGraphicsItemImageFactory(
		const unsigned long ulInFibNodeVersion,
		cFibGraphicsScene * pInFibGraphicsScene ):
		ulFibNodeVersion( ulInFibNodeVersion ),
		pFibGraphicsScene( pInFibGraphicsScene) {
	//nothing to do
}

/**
 * destructor
 */
cFibGraphicsItemImageFactory::~cFibGraphicsItemImageFactory() {
	//nothing to do
}


/**
 * @return the name of this class "cFibGraphicsItemImageFactory"
 */
std::string cFibGraphicsItemImageFactory::getName() const {
	
	return std::string( "cFibGraphicsItemImageFactory" );
}


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
cFibGraphicsItem * cFibGraphicsItemImageFactory::operator()(
		cFibElement * pFibObject ) const {
	//TODO
	
	
	DEBUG_OUT_L2(<<"cFibGraphicsItemImageFactory("<<this<<")::operator()( pFibObject="<<pFibObject<<") called"<<endl<<flush);
	if ( pFibObject == NULL ){
		//nothing to convert
		DEBUG_OUT_L2(<<"cFibGraphicsItemImageFactory("<<this<<")::operator()( pFibObject="<<pFibObject<<") done no Fib object"<<endl<<flush);
		return NULL;
	}
	/* use recursion
	 * - for actual Fib element:
	 * 	- if Fib element is limb element -> check next Fib element (getNextFibElement())
	 * 	- if Fib element is list element -> create cFibGraphicsItemFibList
	 * 		element for it and add the cFibGraphicsItem for every subobject
	 * 		of it, the cFibGraphicsItem are creating by calling the method
	 * 		recursively
	 * 	- if Fib element is root element -> check main Fib object of it
	 * 		(=next Fib element: getNextFibElement())
	 * 	- else -> create cFibGraphicsItemFibObject for it
	 * 
	 */
	if ( pFibObject->isLimb() ){
		//if Fib element is limb element -> use next Fib element to convert
		DEBUG_OUT_L2(<<"cFibGraphicsItemImageFactory("<<this<<")::operator()( pFibObject="<<pFibObject<<") Fib element is limb element"<<endl<<flush);
		return operator()( pFibObject->getNextFibElement() );
	}//else
	const char cType = pFibObject->getType();
	
	switch ( cType ){
		case 'l':{/* if Fib element is list element
			-> create cFibGraphicsItemFibList element for it and add the
				cFibGraphicsItem for every subobject of it, the
				cFibGraphicsItem are creating by calling the method recursively*/
			DEBUG_OUT_L2(<<"cFibGraphicsItemImageFactory("<<this<<")::operator()( pFibObject="<<pFibObject<<") Fib element is list element"<<endl<<flush);
			QList< cFibGraphicsItem * > liSubitems;
			list< cFibElement * > liSubobjects = pFibObject->getSubobjects();
			for ( list< cFibElement * >::iterator
					itrActualSubobject = liSubobjects.begin();
					itrActualSubobject != liSubobjects.end(); itrActualSubobject++ ){
				
				cFibGraphicsItem * pConvertedItem = operator()(
					*itrActualSubobject );
				
				if ( pConvertedItem ){
					liSubitems.push_back( pConvertedItem );
				}
			}
			return new cFibGraphicsItemFibList( pFibObject, ulFibNodeVersion,
				pFibGraphicsScene, liSubitems );
		}break;
		case 'r':{//if Fib element is root element -> convert the main Fib object of it
			DEBUG_OUT_L2(<<"cFibGraphicsItemImageFactory("<<this<<")::operator()( pFibObject="<<pFibObject<<") Fib element is root element"<<endl<<flush);
			return operator()( pFibObject->getNextFibElement() );
		}break;
		case 'o':{/*if Fib element is external object element
			-> create a cFibGraphicsItemFibExtObject for it*/
			DEBUG_OUT_L2(<<"cFibGraphicsItemImageFactory("<<this<<")::operator()( pFibObject="<<pFibObject<<") Fib element is external object element convert to cFibGraphicsItemFibExtObject"<<endl<<flush);
			
			return new cFibGraphicsItemFibExtObject( pFibObject,
				ulFibNodeVersion, pFibGraphicsScene );
		}break;
		default://else -> create cFibGraphicsItemFibObject for it
			DEBUG_OUT_L2(<<"cFibGraphicsItemImageFactory("<<this<<")::operator()( pFibObject="<<pFibObject<<") else convert to cFibGraphicsItemFibObject"<<endl<<flush);
			//evalue the object point for the Fib element
			const unsignedIntFib uiObjectPoint =
				pFibObject->getNumberOfObjectPoint();
				
			cFibElement * pTopMostFibElement = pFibObject->getMasterRoot();
			//evalue the defining Fib element for the object point
			const unsignedIntFib uiDefiningFibElementPoint =
				pTopMostFibElement->objectPointToElementPoint( uiObjectPoint, true );
			
			cFibElement * pDefiningFibElement =
				pTopMostFibElement->getFibElement( uiDefiningFibElementPoint );
			
			return new cFibGraphicsItemFibObject( pDefiningFibElement,
				ulFibNodeVersion, pFibGraphicsScene );
	}//end switch Fib element type
	//Error: should not happen
	DEBUG_OUT_EL2(<<"cFibGraphicsItemImageFactory("<<this<<")::operator()( pFibObject="<<pFibObject<<") done no known Fib element"<<endl<<flush);
	return NULL;
}











