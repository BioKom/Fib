/**
 * @class cFibDatabase
 * file name: cFibDatabase.h
 * @author Betti Oesterholz
 * @date 25.11.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents Fib database.
 * Copyright (C) @c LGPL3 2011 Betti Oesterholz
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
 * This class represents Fib database. It gives you access to the Fib
 * database objects.
 * It will load the Fib database objects from a Fib database folder, if
 * they are needed.
 *
 */
/*
History:
25.11.2011  Oesterholz  created
*/

#ifndef ___C_FIB_DATABASE_H__
#define ___C_FIB_DATABASE_H__


#include "version.h"

#include "fibDatatyps.h"

#include "cRoot.h"
#include "cFolder.h"

#include <string>
#include <list>
#include <map>


namespace fib{

class cFibDatabaseDeleter;

class cFibDatabase{

friend class cFibDatabaseDeleter;

private:
	
	/**
	 * The instance for the Fib database
	 */
	static cFibDatabase * pFibDbInstance;
	
	/**
	 * The path to the actual loaded database.
	 */
	static std::string szDatabasePath;
	
	/**
	 * A map with the loaded Fib database objects.
	 * map entries:
	 * 	key: the identifer of the database object
	 * 	value: the loaded database object for the identifier 
	 */
	static std::map< longFib, cRoot * > mapLoadedDatabaseObjects;
	
	/**
	 * The set with the identifiers for all database objects.
	 * map entries:
	 * 	key: the identifer of the database object
	 * 	value: the name of the file for the object in the database folder
	 */
	static std::map< longFib, std::string > mapDatabaseIdentifiers;
	
	/**
	 * The list with the identifiers for all database objects.
	 * This data structure is yust for the faster evaluation of:
	 * 	@see cRoot::getAllDatabaseObjectIdentifiers()
	 */
	static std::list< longFib > liDatabaseIdentifiers;
	
	/**
	 * constructor
	 */
	cFibDatabase();
	
protected:
	
	/**
	 * This class is for deleting the database when the programm ends.
	 */
	static cFibDatabaseDeleter fibDatabaseDeleter;

public:
	
	
	/**
	 * destructor
	 */
	virtual ~cFibDatabase();
	
	/**
	 * @return a instance of the database object
	 */
	static cFibDatabase * getInstance();
	
	/**
	 * This method returns the identifiers of all database objects, in the
	 * actual database.
	 *
	 * @return the identifiers of all database objects
	 */
	std::list< longFib > getAllDatabaseObjectIdentifiers() const;

	/**
	 * This method returns the database Fib object for the identifer, if it
	 * exists.
	 * 
	 * @see loadFibObject()
	 * @see mapLoadedDatabaseObjects
	 * @see setDatabaseIdentifiers
	 * @param lIdentifer the identifer of the Fib object to return
	 * @return the Fib object for the identifer lIdentifer or NULL if non
	 * 	such exists
	 */
	cRoot * getFibObject( const longFib lIdentifer );
	
	/**
	 * This method loads the Fib object for the identifier.
	 * If you load Fib objects some time befor you want it
	 * (call getFibObject() for them) this could speed up the process. 
	 * This method won't load Fib objects that are allready loaded.
	 * 
	 * @see getFibObject()
	 * @see reloadDatabase()
	 * @see mapLoadedDatabaseObjects
	 * @see setDatabaseIdentifiers
	 * @param lIdentifer the identifer of the Fib object to load
	 */
	void loadFibObject( const longFib lIdentifer );
	
	/**
	 * This method frees the Fib object for the identifier.
	 * You could free some memory in this way.
	 * 
	 * @see getFibObject()
	 * @see loadFibObject()
	 * @see reloadDatabase()
	 * @see mapLoadedDatabaseObjects
	 * @see setDatabaseIdentifiers
	 * @param lIdentifer the identifer of the Fib object to load
	 */
	void freeFibObject( const longFib lIdentifer );
	
	/**
	 * @return A map with the loaded Fib database objects.
	 * 	map entries:
	 * 		key: the identifer of the database object
	 * 		value: the loaded database object for the identifier
	 * 	@see mapLoadedDatabaseObjects
	 */
	std::map< longFib, cRoot * > getLoadedDatabaseObjects();
	
	
	/**
	 * @see szDatabasePath
	 * @return a string to the actual set database path, the string is empty
	 * 	if no database path is set
	 */
	static std::string getDatabasePath();
	
	/**
	 * This function sets the Fib database path to the given path if possible.
	 *
	 * @see szDatabasePath
	 * @param szInDatabasePath the path to the folder with the Fib database
	 * 	objects
	 * @return true if the given Fib database path exists and was set, else
	 * 	false and the database path is not changed
	 */
	static bool setDatabasePath( const char * szInDatabasePath );
	
	/**
	 * This function sets the Fib database path to the given path if posible.
	 *
	 * @see szDatabasePath
	 * @param szInDatabasePath the path to the folder with the Fib database
	 * 	objects
	 * @return true if the given Fib database path exists and was set, else
	 * 	false and the database path is not changed
	 */
	static bool setDatabasePath( const std::string szInDatabasePath );
	
	/**
	 * This function search standard Fib database paths to find a valid Fib
	 * database and sets the first found Fib database path if one was found.
	 * 
	 * @see szDatabasePath
	 * @see szStandardDatabaseFolder
	 * @return true if a Fib database (path) was found and was set, else
	 * 	false and the database path is not changed
	 */
	static bool searchForDatabasePath();
	
	/**
	 * This method reloads all Fib database objects identifiers from the set
	 * database path.
	* No database objects will be loaded after the reload.
	 * 
	 * @see szDatabasePath
	 * @see mapLoadedDatabaseObjects
	 * @return true if the database objects identifiers could be reloded
	 * 	(the database path exists), else false
	 */
	bool reloadDatabase();
	
private:
	
	/**
	 * This method loads the database folder data.
	 * (Attention: No mutex variables are used in this method.)
	 * 
	 * @see liDatabaseIdentifiers
	 * @see mapDatabaseIdentifiers
	 * @param folder the database folder from which to load the data
	 * @return true if the data was loaded, else false
	 */
	static bool loadListContainedDbObjects( cFolder & folder );
	
	
#ifdef FEATURE_FIB_DB_USE_TREADS
	
	/**
	 * This method is for running in a seperate tread.
	 * It will loade the Fib object for the given identifier.
	 *
	 * @see run()
	 * @see start()
	 * @see stop()
	 * @param inputArg a longFib number for the Fib database object to load
	 */
	static void * treadloadFibObject( void * inputArg );
	
#endif //FEATURE_FIB_DB_USE_TREADS

	
};//end class cFibDatabase 
}//end namespace fib

#endif //___C_FIB_DATABASE_H__






