/**
 * @class cUnderobject
 * file name: cUnderobject.h
 * @author Betti Oesterholz
 * @date 08.12.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class contains the information to create the underobject
 * structur of a fib -object.
 *
 * Copyright (C) @c LGPL3 2010 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This class contains the information to create the underobject
 * structur of a fib -object.
 * @param tPoint class with the point data of the underobjects,
 * 	it needs to have an isNeeded() method, if every of its points and
 * 	underobjects aren't needed the underobjects isn't needed
 *
 */
/*
History:
08.12.2010  Oesterholz  created
*/


#ifndef ___N_NEEDED_UNDEROBJECTS_C_UNDEROBJECT_H__
#define ___N_NEEDED_UNDEROBJECTS_C_UNDEROBJECT_H__


#include "version.h"
#include "fibDatatyps.h"

#include <set>
#include <list>
#include <map>


using namespace std;


namespace fib{
namespace algorithms{
namespace nEvalueFibObject{
namespace nNeededUnderobjects{


template <class tPoint>
class cUnderobject{
public:

	/**
	 * The number of this underobject.
	 */
	unsignedIntFib uiUnderobjectNumber;
	
	/**
	 * A map with the underobjects which are directly below this
	 * underobject.
	 * The map key is the underobject number. (@see uiUnderobjectNumber)
	 */
	map< unsignedIntFib, cUnderobject * > mapSubUnderobjects;
	
	/**
	 * A set with the @see cPositionUnderObjectsData objects, which are
	 * directly below this underobject.
	 */
	set< tPoint * > setSubPoints;
	
	/**
	 * If true this underobject is overwritten, else not.
	 */
	bool bOverwritten;
	
	
	/**
	 * The constructor for the underobject.
	 */
	cUnderobject( unsignedIntFib uiInUnderobjectNumber = 0 );
	
	/**
	 * destructor
	 * The destructor will remove and delete all underobjects
	 */
	~cUnderobject();
	
	/**
	 * This method adds the given pointdata to this underobjecttree.
	 * If the point is part of underobject not jet in the underobjecttree,
	 * the needed underobjects and ther structur will be created.
	 *
	 * @param pointData the pointdata to add to the
	 * 	underobjecttree;
	 * 	Beware: the liUnderObjects will be emptied.
	 * @return true if the adding was successfull, else false
	 */
	bool addPoint( tPoint & pointData );	
	/**
	 * This method will set the @see bOverwritten flag for all
	 * underobjects in this tree, which are overwritten.
	 * Attention: tPoint.isNeeded() is used in ths method.
	 * (For cEvalueUnderObjects you have to call
	 * cEvalueUnderObjects::markOverwrittenFibElements() for the data
	 * first befor you call this method.)
	 *
	 * @return true if this underobject is overwritten, else false
	 */
	bool evalueOverwritten();
	
	/**
	 * This method will return all underobjects of this underobject tree,
	 * which are overwritten but are not contained in an overwritten
	 * underobject.
	 * Attention: You have to call @see evalueOverwritten() first befor
	 * 	you call this method.
	 *
	 * @return the list with all overwritten underobjects to remove.
	 */
	list<unsignedIntFib> getHighestOverwritten();

};//end class cUnderobject



};//end namespace nNeededUnderobjects
};//end namespace nEvalueFibObject
};//end namespace algorithms
};//end namespace fib


//include template implementation
#include "../src/cUnderobject.cpp"


#endif //___N_NEEDED_UNDEROBJECTS_C_UNDEROBJECT_H__
