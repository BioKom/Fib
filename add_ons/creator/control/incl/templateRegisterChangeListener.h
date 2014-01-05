
//TODO check

/**
 * @file templateRegisterChangeListener
 * file name: templateRegisterChangeListener.h
 * @author Betti Oesterholz
 * @date 20.12.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a template for handling listeners for object changes.
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
 * This file specifies a template for handling listeners for object changes.
 * @pattern listener
 * @pattern template
 */
/*
History:
20.12.2013  Oesterholz  created
*/


#ifndef ___TEMPLATE_REGISTER_CHANGE_LISTENER_H__
#define ___TEMPLATE_REGISTER_CHANGE_LISTENER_H__


#include "version.h"

#include <string>
#include <set>

#include <QMutex>


template< class tListener, class tEvent > class templateRegisterChangeListener{

typedef std::set< tListener * > tListenerSet;
typedef typename tListenerSet::iterator tListenerSetIterator;

public:
	
	/**
	 * @return the name of this class "cFibVector"
	 */
	virtual std::string getName() const{
		
		return std::string( "templateRegisterChangeListener" );
	}
	
	
	/**
	 * With this function you can register a listeners for changes in this
	 * object.
	 *
	 * @see unregisterChangeListener()
	 * @see setChangeListener
	 * @see sendChangeEvent()
	 * @param pListener a pointer to the listener for changes
	 * @return true if the listener was registered, else false
	 */
	bool registerChangeListener( tListener * pListener ) {
		
		DEBUG_OUT_L2(<<"templateRegisterChangeListener("<<this<<")::registerChangeListener( pListener="<<pListener<<") called"<<endl<<flush);
		if ( pListener == NULL ){
			//nothing to register
			return false;
		}
		mutexChangeListener.lock();
		const pair< tListenerSetIterator, bool > paListenerInserted =
			setChangeListener.insert( pListener );
		mutexChangeListener.unlock();
		return paListenerInserted.second;
	}


	/**
	 * With this function you can unregister a listeners for changes in this
	 * object.
	 *
	 * @see registerChangeListener()
	 * @see setChangeListener
	 * @see sendChangeEvent()
	 * @param pListener a pointer to the listener for changes
	 * @return true if the listener was registered, else false
	 */
	bool unregisterChangeListener( tListener * pListener ) {
		
		DEBUG_OUT_L2(<<"templateRegisterChangeListener("<<this<<")::unregisterChangeListener( pListener="<<pListener<<") called"<<endl<<flush);
		mutexChangeListener.lock();
		const bool bUnregistered = ( 0 < setChangeListener.erase( pListener ) );
		mutexChangeListener.unlock();
		return bUnregistered;
	}


	/**
	 * This method sents a object changed event to all object change
	 * listeners of this object.
	 *
	 * @see setChangeListener
	 * @see registerChangeListener()
	 * @see unregisterChangeListener()
	 * @param pChangedEvent the change event to send
	 */
	void sendChangeEvent( const tEvent * pChangedEvent ) {
		
		mutexChangeListener.lock();
		for ( tListenerSetIterator
				itrListenerVectorChanged = setChangeListener.begin();
				itrListenerVectorChanged != setChangeListener.end();
				itrListenerVectorChanged++ ){
			
			(*itrListenerVectorChanged)->changedEvent( pChangedEvent );
		}
		mutexChangeListener.unlock();
	}
	
protected:
	
	/**
	 * The set with the listeners for object changes.
	 * @see registerChangeListener()
	 * @see unregisterChangeListener()
	 * @see sendChangeEvent()
	 * @see mutexChangeListener
	 */
	tListenerSet setChangeListener;
	
	
	/**
	 * Mutex to lock access to the listeners for object changes.
	 * Lock the mutex if you use one of the following containers:
	 * 	@see setChangeListener
	 */
	QMutex mutexChangeListener;
	
};//end class templateRegisterChangeListener


#endif //___FIB__NCREATOR__E_OBJECT_DELETED_H__





