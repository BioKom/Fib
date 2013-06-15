/**
 * @class cFibDatabaseJavaScript
 * file name: cFibDatabaseJavaScript.h
 * @author Betti Oesterholz
 * @date 10.05.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents Fib database.
 *
 *
 * Copyright (C) @c LGPL3 2013 Betti Oesterholz
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
 * This class represents Fib database for the javascript enviroment.
 * It gives you access to the Fib database objects.
 * It will load the Fib database objects from a Fib database folder, if
 * they are needed.
 *
 */
/*
History:
10.05.2013  Oesterholz  created
*/

#ifndef ___FIB__C_FIB_DATABASE_JAVA_SCRIPT_H__
#define ___FIB__C_FIB_DATABASE_JAVA_SCRIPT_H__


#include "version.h"

#include "fibDatatyps.h"

#include "cRoot.h"
#include "cFibDatabase.h"

#include <string>
#include <list>
#include <map>
#include <istream>

//TODO change to 32
#ifndef MAX_DATABASE_JAVASCRIPT_PATH_SEARCH_DEPTH
	#define MAX_DATABASE_JAVASCRIPT_PATH_SEARCH_DEPTH 4
#endif //MAX_DATABASE_JAVASCRIPT_PATH_SEARCH_DEPTH


namespace fib{


class cFibDatabaseJavaScript: public cFibDatabase{
private:
	
	/**
	 * constructor
	 */
	cFibDatabaseJavaScript();
	
public:
	
	/**
	 * destructor
	 */
	virtual ~cFibDatabaseJavaScript();
	
	/**
	 * @return a instance of the database object
	 */
	static cFibDatabase * getInstance();
	
	/**
	 * This function sets the Fib database path to the given path if posible.
	 *
	 * @see szDatabasePath
	 * @param szInDatabasePath the path to the folder with the Fib database
	 * 	objects
	 * @return true if the given Fib database path exists and was set, else
	 * 	false and the database path is not changed
	 */
	virtual bool setDatabasePath( const std::string szInDatabasePath );
	
	/**
	 * This function search standard Fib database paths to find a valid Fib
	 * database and sets the first found Fib database path if one was found.
	 *
	 * @see szDatabasePath
	 * @see szStandardDatabaseFolder
	 * @return true if a Fib database (path) was found and was set, else
	 * 	false and the database path is not changed
	 */
	virtual bool searchForDatabasePath();
	
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
	virtual bool reloadDatabase();
	
protected:
	
	/**
	 * This method loads the Fib object for the given file name.
	 * This function won't handle mutex variables.
	 *
	 * @see loadFibObject()
	 * @see getFibObject()
	 * @see treadloadFibObject()
	 *
	 * @see reloadDatabase()
	 * @see mapLoadedDatabaseObjects
	 * @see setDatabaseIdentifiers
	 * @param lIdentifer the identifer of the Fib object to load
	 */
	virtual cRoot * loadFibObject( const string & szFileName );

	/**
	 * This method loads the database folder data.
	 * (Attention: No mutex variables are used in this method.)
	 *
	 * @see liDatabaseIdentifiers
	 * @see mapDatabaseIdentifiers
	 * @param folder dummy for compatibility to cFibDatabase
	 * @return true if the data was loaded, else false
	 */
	virtual bool loadListContainedDbObjects( const string & folder );
	
	/**
	 * This function opens the stream for the given path.
	 *
	 * @param zsPath the path of the file to open
	 * @return the open stream
	 */
	static istream * openFileStream( const char * zsPath );
	
	/**
	 * This function checks if the given path is a database path.
	 * (It is a database path if it exists and contains a id-000000.xml or
	 * id-000000.fib file. )
	 *
	 * @param zsPath the path to check
	 * @return true if the path is a database path, else false
	 */
	static bool checkIfDatabasePath( const string & zsPath );
	
	/**
	 * This function checks if the given path is a existing folder.
	 *
	 * @param zsPath the path to check
	 * @return true if the path is a existing folder, else false
	 */
	static bool checkIfFolderExists( const string & zsPath );
	
	/**
	 * This function returns a list with the Fib database files.
	 *
	 * @return a list with the Fib database files
	 */
	static list< string > getDatabaseFiles();
	
	
};//end class cFibDatabaseJavaScript 
}//end namespace fib

#endif //___FIB__C_FIB_DATABASE_JAVA_SCRIPT_H__






