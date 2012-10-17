/**
 * @class cUnderobject
 * file name: cUnderobject.cpp
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


#include "cUnderobject.h"

#ifndef ___N_NEEDED_UNDEROBJECTS_C_UNDEROBJECT_CPP__
#define ___N_NEEDED_UNDEROBJECTS_C_UNDEROBJECT_CPP__


using namespace fib::algorithms::nEvalueFibObject::nNeededUnderobjects;


/**
 * The constructor for the underobject.
 */
template <class tPoint> cUnderobject<tPoint>::cUnderobject(
	unsignedIntFib uiInUnderobjectNumber ):
		uiUnderobjectNumber( uiInUnderobjectNumber ),
		bOverwritten( false ){
}


/**
 * destructor
 * The destructor will remove and delete all underobjects
 */
template <class tPoint> cUnderobject<tPoint>::~cUnderobject(){
	
	//remove all underobjects
	typedef cUnderobject<tPoint> * typePUnderobject;
	typedef typename map< unsignedIntFib, typePUnderobject >::iterator
		typeItrUnderobject;
	for ( typeItrUnderobject itrUnderobject = mapSubUnderobjects.begin();
			itrUnderobject != mapSubUnderobjects.end(); itrUnderobject++ ){
		delete itrUnderobject->second;
	}
	mapSubUnderobjects.clear();
}
	
	
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
template <class tPoint> bool cUnderobject<tPoint>::
		addPoint( tPoint & pointData ){
	
	if ( pointData.liUnderObjects.empty() ){
		setSubPoints.insert( &pointData );
		return true;
	}
	
	unsignedIntFib uiNextUnderobject =
		pointData.liUnderObjects.front();
	pointData.liUnderObjects.pop_front();
	
	if ( uiNextUnderobject == uiUnderobjectNumber ){
		//take next underobject
		if ( pointData.liUnderObjects.empty() ){
			setSubPoints.insert( &pointData );
			return true;
		}
		uiNextUnderobject = pointData.liUnderObjects.front();
		pointData.liUnderObjects.pop_front();
	}
	typedef cUnderobject<tPoint> * typePUnderobject;
	typedef typename map< unsignedIntFib, typePUnderobject >::iterator
		typeItrUnderobject;
	typeItrUnderobject itrUnderobject = mapSubUnderobjects.find( uiNextUnderobject );
	
	if ( itrUnderobject == mapSubUnderobjects.end() ){
		//underobject not found -> create and add a new underobject baranch
		cUnderobject<tPoint> * pNewUnderobject =
			new cUnderobject<tPoint>( uiNextUnderobject );
		mapSubUnderobjects.insert( pair< unsignedIntFib, cUnderobject<tPoint> * >(
			uiNextUnderobject, pNewUnderobject ) );
		
		return pNewUnderobject->addPoint( pointData );
	}//else underobject found -> go into the found underobject baranch
	return itrUnderobject->second->addPoint( pointData );
}


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
template <class tPoint> bool cUnderobject<tPoint>::evalueOverwritten(){
	
	bOverwritten = true;
	//for every underobject
	typedef cUnderobject<tPoint> * typePUnderobject;
	typedef typename map< unsignedIntFib, typePUnderobject >::iterator
		typeItrUnderobject;
	for ( typeItrUnderobject itrUnderobject = mapSubUnderobjects.begin();
			itrUnderobject != mapSubUnderobjects.end(); itrUnderobject++ ){
		//evalue if the underobject is overwritten
		itrUnderobject->second->evalueOverwritten();
		
		if ( ! (itrUnderobject->second->bOverwritten) ){
			/*an underobject is overwritten -> it is needed
			-> don't remove this underobject*/
			bOverwritten = false;
		}
	}
	if ( ! bOverwritten ){
		return false;//=bOverwritten
	}
	typedef typename set< tPoint * >::const_iterator typeConstItrPoint;
	for ( typeConstItrPoint itrPosition = setSubPoints.begin();
			itrPosition != setSubPoints.end(); itrPosition++ ){
		//evalue if position is needed
		
		if ( (*itrPosition)->isNeeded() ){
			//this point is needed -> don't remove it
			bOverwritten = false;
			return false;//=bOverwritten
		}
	}
	return bOverwritten;//=true
}


/**
 * This method will return all underobjects of this underobject tree,
 * which are overwritten but are not contained in an overwritten
 * underobject.
 * Attention: You have to call @see evalueOverwritten() first befor
 * 	you call this method.
 *
 * @return the list with all overwritten underobjects to remove.
 */
template <class tPoint> list<unsignedIntFib> cUnderobject<tPoint>::
		getHighestOverwritten(){
	
	list<unsignedIntFib> liOverwrittenUnderobjects;
	if ( bOverwritten ){
		liOverwrittenUnderobjects.push_back( uiUnderobjectNumber );
		return liOverwrittenUnderobjects;
	}else{
		typedef cUnderobject<tPoint> * typePUnderobject;
		typedef typename map< unsignedIntFib, typePUnderobject >::const_iterator
			typeConstItrUnderobject;
		for ( typeConstItrUnderobject itrUnderobject = mapSubUnderobjects.begin();
				itrUnderobject != mapSubUnderobjects.end(); itrUnderobject++ ){
			//evalue if the underobject is overwritten
			list< unsignedIntFib > liOverwrittenUnderobjectsTmp =
				itrUnderobject->second->getHighestOverwritten();
			
			liOverwrittenUnderobjects.insert( liOverwrittenUnderobjects.end(),
				liOverwrittenUnderobjectsTmp.begin(),
				liOverwrittenUnderobjectsTmp.end() );
		}
	}
	return liOverwrittenUnderobjects;
}

#endif //___N_NEEDED_UNDEROBJECTS_C_UNDEROBJECT_CPP__




