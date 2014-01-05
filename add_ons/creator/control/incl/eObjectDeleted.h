
//TODO check

/**
 * @file eObjectDeleted
 * file name: eObjectDeleted.h
 * @author Betti Oesterholz
 * @date 20.12.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies an event template for if a object was deleted.
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
 * This file specifies an event template for if a object was deleted.
 * It should be the parent class of events which signal that a object was
 * deleted.
 * @pattern event
 * @pattern template
 */
/*
History:
20.12.2013  Oesterholz  created
*/


#ifndef ___E_OBJECT_DELETED_H__
#define ___E_OBJECT_DELETED_H__


#include "version.h"

#include <string>


template< class tObject > class eObjectDeleted{
public:
	
	
	/**
	 * A parameter constructor of this class.
	 *
	 * @param pInObject a pointer to the object that was changed
	 * 	@see pObject
	 * @param bInFibVectorDeleted if true the object pInObject was
	 * 	deleted, else this event dosn't mark that it was deleted
	 * 	@see bDeleted
	 */
	explicit eObjectDeleted( const tObject * pInObject,
			const bool bInFibVectorDeleted = false ):
			pObject( pInObject ), bDeleted( bInFibVectorDeleted ){
		//nothing to do
	}
	
	
	/**
	 * @return the name of this class "eObjectDeleted"
	 */
	virtual std::string getName() const{
		
		return std::string( "eObjectDeleted" );
	}
	
	
	/**
	 * @return a pointer to the object that was changed
	 * 	@see pObject
	 */
	const tObject * getObject() const{
		
		return pObject;
	}
	
	
	/**
	 * @return a pointer to the object that was changed
	 * 	@see pObject
	 */
	tObject * getObject(){
		
		return pObject;
	}
	
	
	/**
	 * This method sets the object for this event.
	 *
	 * @param pInObject a pointer to the object that was changed
	 * 	@see pObject
	 */
	void setObject( const tObject * pInObject ){
		
		pObject = pInObject;
	}
	
	
	/**
	 * @return if true the object was deleted, else this
	 * 	event dosn't mark that it was deleted
	 * 	@see bDeleted
	 */
	bool isDeleted() const{
		
		return bDeleted;
	}
	
	
	/**
	 * This method sets if the object was deleted.
	 *
	 * @param bInObjectDeleted if true the object was deleted, else this
	 * 	event dosn't mark that it was deleted
	 * 	@see bDeleted
	 */
	void setDeleted( const bool bInObjectDeleted = true ){
		
		bDeleted = bInObjectDeleted;
	}
	
protected:
	
	/**
	 * A pointer to the object that was changed.
	 * @see getObject()
	 * @see setObject()
	 */
	const tObject * pObject;
	
	/**
	 * If true the object was deleted.
	 * @see setDeleted()
	 * @see isDeleted()
	 */
	bool bDeleted;
	
};//end class eObjectDeleted


#endif //___FIB__NCREATOR__E_OBJECT_DELETED_H__





