/**
 * @class cFibDatabase
 * file name: cFibDatabase.cpp
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
25.02.2012  Oesterholz  if while restoring the Fib object a warning ocured
	don't abord
09.05.2013  Oesterholz  added debugging info: DEBUG_RESTORE_XML and
14.05.2013  Oesterholz  changes so that the database class can be replaced
*/

//switches for test proposes
//#define DEBUG


#include "cFibDatabase.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#ifdef FEATURE_FIB_DB_USE_TREADS
	#include <pthread.h>
	
	static pthread_mutex_t mutexFibDatabaseLoad = PTHREAD_MUTEX_INITIALIZER;
#endif //FEATURE_FIB_DB_USE_TREADS


using namespace fib;
using namespace std;

//static variables
/**
* The instance for the Fib database
*/
cFibDatabase * cFibDatabase::pFibDbInstance = NULL;

/**
* The path to the actual loaded database.
*/
string cFibDatabase::szDatabasePath = "";

/**
 * True if the database path is Ok else false.
 * @see szDatabasePath
 * If true the @see mapDatabaseIdentifiers
 * and @see liDatabaseIdentifiers
 * should be loaded correctly from the given path.
 */
bool cFibDatabase::bDatabasePathOk = false;


/**
 * A map with the loaded Fib database objects.
 * map entries:
 * 	key: the identifier of the database object
 * 	value: the loaded database object for the identifier 
 */
std::map< longFib, cRoot * > cFibDatabase::mapLoadedDatabaseObjects;

/**
 * The set with the identifiers for all database objects.
 * map entries:
 * 	key: the identifier of the database object
 * 	value: the name of the file for the object in the database folder
 */
std::map< longFib, std::string > cFibDatabase::mapDatabaseIdentifiers;

/**
 * The list with the identifiers for all database objects.
 * This data structure is yust for the faster evaluation of:
 * 	@see cRoot::getAllDatabaseObjectIdentifiers()
 */
std::list< longFib > cFibDatabase::liDatabaseIdentifiers;


namespace fib{

	/**
	 * This class is for deleting the database when the programm ends.
	 */
	class cFibDatabaseDeleter{
	public:
		
		/**
		 * destructor which deletes the Fib database if not allready deleted
		 */
		~cFibDatabaseDeleter(){
			
			if ( cFibDatabase::pFibDbInstance != NULL ){
				//get new database instance
				delete cFibDatabase::pFibDbInstance;
				cFibDatabase::pFibDbInstance = NULL;
			}
		}
		
	};//end class cFibDatabaseDeleter

};//end namespace fib

cFibDatabaseDeleter cFibDatabase::fibDatabaseDeleter;



/**
 * constructor
 */
cFibDatabase::cFibDatabase(){
	
	pFibDbInstance = this;
}


/**
 * destructor
 */
cFibDatabase::~cFibDatabase(){
	
	if ( pFibDbInstance != NULL ){
		//delete loaded Fib objects
		for ( map< longFib, cRoot * >::iterator
				itrDbObject = mapLoadedDatabaseObjects.begin();
				itrDbObject != mapLoadedDatabaseObjects.end(); itrDbObject++ ){
			
			if ( itrDbObject->second ){
				itrDbObject->second->deleteObject();
			}
		}
		mapLoadedDatabaseObjects.clear();
		
		pFibDbInstance = NULL;
	}
}


/**
 * @return a instance of the database object
 */
cFibDatabase * cFibDatabase::getInstance(){
	
	if ( pFibDbInstance == NULL ){
		//create a new instance
#ifdef DEBUG_RESTORE_XML
		printf("cFibDatabase::getInstance(): create a new instance\n" );
#endif//DEBUG_RESTORE_XML
		pFibDbInstance = new cFibDatabase();
	}//else return existing instance
#ifdef DEBUG_RESTORE_XML
	printf("cFibDatabase::getInstance(): return existing instance\n" );
#endif//DEBUG_RESTORE_XML
	return pFibDbInstance;
}


/**
 * This method returns the identifiers of all database objects, in the
 * actual database.
 *
 * @return the identifiers of all database objects
 */
list< longFib > cFibDatabase::getAllDatabaseObjectIdentifiers() const{
	
	const string szOkDatabasePath = const_cast<cFibDatabase*>(this)->getDatabase();
	if ( szOkDatabasePath == "" ){
		DEBUG_OUT_EL2(<<"Error: No valid database path could be found -> can't load the database identifiers"<<endl);
		return list< longFib >();
	}
	
	return liDatabaseIdentifiers;
}


/**
 * This method returns the database Fib object for the identifier, if it
 * exists.
 *
 * @see loadFibObject()
 * @see mapLoadedDatabaseObjects
 * @see setDatabaseIdentifiers
 * @param lIdentifier the identifier of the Fib object to return
 * @return the Fib object for the identifier lIdentifier or NULL if non
 * 	such exists
 */
cRoot * cFibDatabase::getFibObject( const longFib lIdentifier ){
	
	//check database path
	const string szOkDatabasePath = getDatabase();
	if ( szOkDatabasePath == "" ){
		DEBUG_OUT_EL2(<<"Error: No valid database path could be found -> can't load the database object with identifier "<<lIdentifier<<endl);
		return NULL;
	}
	
	//check if the object is allready loaded
#ifdef FEATURE_FIB_DB_USE_TREADS
	pthread_mutex_lock( & mutexFibDatabaseLoad );
#endif //FEATURE_FIB_DB_USE_TREADS
	map< longFib, cRoot * >::iterator
		itrLoadedObject = mapLoadedDatabaseObjects.find( lIdentifier );
	if ( itrLoadedObject != mapLoadedDatabaseObjects.end() ){
		//the object is allready loaded -> return it
		return itrLoadedObject->second;
	}//else check if the database object for the identifier exists
	
	map< longFib, string >::iterator
		itrDatabaseObject = mapDatabaseIdentifiers.find( lIdentifier );
	if ( itrDatabaseObject == mapDatabaseIdentifiers.end() ){
		//no such database object exists -> return NULL
		DEBUG_OUT_EL2(<<"Error: No such database object exists. -> return NULL"<<endl);
		return NULL;
	}//else load the database object
#ifdef FEATURE_FIB_DB_USE_TREADS
	pthread_mutex_unlock( & mutexFibDatabaseLoad );
#endif //FEATURE_FIB_DB_USE_TREADS
	
	cRoot * pRestoredFibObject = loadFibObject( itrDatabaseObject->second );
	if ( pRestoredFibObject == NULL ){
		return NULL;
	}

#ifdef FEATURE_FIB_DB_USE_TREADS
	//use mutex for storing loaded
	pthread_mutex_lock( & mutexFibDatabaseLoad );
	mapLoadedDatabaseObjects.insert( make_pair( lIdentifier, pRestoredFibObject ) );
	pthread_mutex_unlock( & mutexFibDatabaseLoad );
#else //FEATURE_FIB_DB_USE_TREADS
	mapLoadedDatabaseObjects.insert( make_pair( lIdentifier, pRestoredFibObject ) );
#endif //FEATURE_FIB_DB_USE_TREADS
	
	return pRestoredFibObject;
}


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
 * @param lIdentifier the identifier of the Fib object to load
 */
void cFibDatabase::loadFibObject( const longFib lIdentifier ){
	
	//check database path
	const string szOkDatabasePath = getDatabase();
	if ( szOkDatabasePath == "" ){
		DEBUG_OUT_EL2(<<"Error: No valid database path could be found -> can't load the database object with identifier "<<lIdentifier<<endl);
		return;
	}
	
	//check if the object is allready loaded
#ifdef FEATURE_FIB_DB_USE_TREADS
	pthread_mutex_lock( & mutexFibDatabaseLoad );
#endif //FEATURE_FIB_DB_USE_TREADS
	
	if ( mapLoadedDatabaseObjects.find( lIdentifier ) !=
			mapLoadedDatabaseObjects.end() ){
		//the object is allready loaded -> nothing to do
		return;
	}//else check if the database object for the identifier exists
	map< longFib, string >::const_iterator
		itrDatabaseObject = mapDatabaseIdentifiers.find( lIdentifier );
	if ( itrDatabaseObject == mapDatabaseIdentifiers.end() ){
		//no such database object exists -> nothing to do
		return;
	}//else load the database object
#ifdef FEATURE_FIB_DB_USE_TREADS
	pthread_mutex_unlock( & mutexFibDatabaseLoad );
	
	//load in own tread
	pthread_t * pThreadLoad = new pthread_t();
	const int iReturn = pthread_create( pThreadLoad, NULL,
		&(cFibDatabase::treadloadFibObject), ((void*)(&lIdentifier)) );
	
	if ( iReturn != 0 ){
		DEBUG_OUT_EL2(<<"Error: cFibDatabase::treadloadFibObject() returned error"<<endl<<flush);
		return;
	}
	pthread_detach( *pThreadLoad );
#else //FEATURE_FIB_DB_USE_TREADS
	
	cRoot * pRestoredFibObject = loadFibObject( itrDatabaseObject->second );
	if ( pRestoredFibObject == NULL ){
		return;
	}
	
	mapLoadedDatabaseObjects.insert( make_pair( lIdentifier, pRestoredFibObject ) );
#endif //FEATURE_FIB_DB_USE_TREADS
}


/**
 * This method frees the Fib object for the identifier.
 * You could free some memory in this way.
 *
 * @see getFibObject()
 * @see loadFibObject()
 * @see reloadDatabase()
 * @see mapLoadedDatabaseObjects
 * @see setDatabaseIdentifiers
 * @param lIdentifier the identifier of the Fib object to freed
 */
void cFibDatabase::freeFibObject( const longFib lIdentifier ){
	
	//check if the object is allready loaded
#ifdef FEATURE_FIB_DB_USE_TREADS
	pthread_mutex_lock( & mutexFibDatabaseLoad );
#endif //FEATURE_FIB_DB_USE_TREADS
	std::map< longFib, cRoot * >::iterator itrLoadedObject =
		mapLoadedDatabaseObjects.find( lIdentifier );
	if ( itrLoadedObject == mapLoadedDatabaseObjects.end() ){
		//the object is not loaded -> nothing to do
		return;
	}//else free object
	cRoot * pFibObjectToFree = itrLoadedObject->second;
	mapLoadedDatabaseObjects.erase( itrLoadedObject );

#ifdef FEATURE_FIB_DB_USE_TREADS
	pthread_mutex_unlock( & mutexFibDatabaseLoad );
#endif //FEATURE_FIB_DB_USE_TREADS
	if ( pFibObjectToFree ){
		pFibObjectToFree->deleteObject();
	}
}


/**
 * @return A map with the loaded Fib database objects.
 * 	map entries:
 * 		key: the identifier of the database object
 * 		value: the loaded database object for the identifier
 * 	@see mapLoadedDatabaseObjects
 */
std::map< longFib, cRoot * > cFibDatabase::getLoadedDatabaseObjects(){
	
	return mapLoadedDatabaseObjects;
}


/**
 * @see szDatabasePath
 * @return a string to the actual set database path, the string is empty
 * 	if no database path is set
 */
string cFibDatabase::getDatabasePath(){
	
	return szDatabasePath;
}


/**
 * This function sets the Fib database path to the given path if possible.
 *
 * @see szDatabasePath
 * @param szInDatabasePath the path to the folder with the Fib database
 * 	objects
 * @return true if the given Fib database path exists and was set, else
 * 	false and the database path is not changed
 */
bool cFibDatabase::setDatabasePath( const char * szInDatabasePath ){
	
	return getInstance()->setDatabasePath( string( szInDatabasePath ) );
}


/**
 * This function sets the Fib database path to the given path if posible.
 *
 * @see szDatabasePath
 * @param szInDatabasePath the path to the folder with the Fib database
 * 	objects
 * @return true if the given Fib database path exists and was set, else
 * 	false and the database path is not changed
 */
bool cFibDatabase::setDatabasePath( const string szInDatabasePath ){
	
	if ( szInDatabasePath == "" ){
		//no database path to set
#ifdef DEBUG_RESTORE_XML
		printf("cFibDatabase::setDatabasePath(): no database path to set\n" );
#endif//DEBUG_RESTORE_XML
		return false;
	}
	if ( bDatabasePathOk && ( szInDatabasePath == szDatabasePath ) ){
		//database path set already
#ifdef DEBUG_RESTORE_XML
		printf("cFibDatabase::setDatabasePath(): database path set already\n" );
#endif//DEBUG_RESTORE_XML
		return true;
	}
	//check if the path if valid
	cFolder folder( szInDatabasePath.c_str() );
	
	if ( ! folder.good() ){
		//the path is not valid
#ifdef DEBUG_RESTORE_XML
		printf("cFibDatabase::setDatabasePath(): the path is not valid\n" );
#endif//DEBUG_RESTORE_XML
		return false;
	}//else if the path if valid
	//set database path
#ifdef DEBUG_RESTORE_XML
	printf("cFibDatabase::setDatabasePath(): set database path\n" );
#endif//DEBUG_RESTORE_XML
#ifdef FEATURE_FIB_DB_USE_TREADS
	pthread_mutex_lock( & mutexFibDatabaseLoad );
#endif //FEATURE_FIB_DB_USE_TREADS

	szDatabasePath  = szInDatabasePath;
	bDatabasePathOk = true;
	
#ifdef DEBUG_RESTORE_XML
	printf("cFibDatabase::setDatabasePath(): load list with contained database objects\n" );
#endif//DEBUG_RESTORE_XML
	//load list with contained database objects
	const bool bListContainedDbObjectsLoaded =
		loadListContainedDbObjects( folder );
	
#ifdef FEATURE_FIB_DB_USE_TREADS
	pthread_mutex_unlock( & mutexFibDatabaseLoad );
#endif //FEATURE_FIB_DB_USE_TREADS
#ifdef DEBUG_RESTORE_XML
	printf("cFibDatabase::setDatabasePath() done\n" );
#endif//DEBUG_RESTORE_XML
	return bListContainedDbObjectsLoaded;
}


/**
 * This function search for the standard Fib database paths, to find a
 * valid Fib database, and set the first found Fib database path, if one was
 * found.
 *
 * @see szDatabasePath
 * @return true if a Fib database (path) was found and was set, else
 * 	false and the database path is not changed
 */
bool cFibDatabase::searchForDatabasePath(){
	
#ifdef DEBUG_RESTORE_XML
	printf("cFibDatabase::searchForDatabasePath() started\n" );
#endif//DEBUG_RESTORE_XML
	//list with the standard database folders
	list< string > liSzStandardDatabaseFolders;
	liSzStandardDatabaseFolders.push_back( "fibDatabase/" );
	liSzStandardDatabaseFolders.push_back( "fibDb/" );
	liSzStandardDatabaseFolders.push_back( "fibDB/" );
	liSzStandardDatabaseFolders.push_back( "fib/fibDatabase/" );
	liSzStandardDatabaseFolders.push_back( "fib/fibDb/" );
	liSzStandardDatabaseFolders.push_back( "fib/fibDB/" );

	//the path to the found Fib database directory; if empty non was found
	string szFoundDatabasePath;
	//the path to the actual base directory
	string szActualBasePath( "./" );
	
	unsigned int uiActualSearchDepth = 0;
	//search for path
	while ( szFoundDatabasePath.empty() ){
		//check if base folder exists
#ifdef DEBUG_RESTORE_XML
		printf("cFibDatabase::searchForDatabasePath() check path: %s\n", szActualBasePath.c_str() );
#endif//DEBUG_RESTORE_XML
		cFolder baseFolder( szActualBasePath );
		
		if ( ! baseFolder.good() ){
			//the path is not valid -> no standard database folder could be found
#ifdef DEBUG_RESTORE_XML
			printf("   the path %s is not valid -> no standar database folder could be found\n", szActualBasePath.c_str() );
#endif//DEBUG_RESTORE_XML
			return false;
		}//else if the base path if valid
		
		//search in subpath for standard database folders
#ifdef DEBUG_RESTORE_XML
		printf("   search in subpath for standard database folders\n" );
#endif//DEBUG_RESTORE_XML
		for ( list< string >::iterator
				itrActualStandardDbFolder = liSzStandardDatabaseFolders.begin();
				itrActualStandardDbFolder != liSzStandardDatabaseFolders.end();
				itrActualStandardDbFolder++ ){
			
			string szActualPath( szActualBasePath );
#ifdef DEBUG_RESTORE_XML
			printf("      actual subpath for standard database folders: %s\n",
				szActualPath.c_str() );
#endif//DEBUG_RESTORE_XML
			if ( itrActualStandardDbFolder->at( 0 ) == '/' ){
				//absolute path
#ifdef DEBUG_RESTORE_XML
				printf("         absolute path\n" );
#endif//DEBUG_RESTORE_XML
				if ( szActualBasePath.compare( "./" ) == 0 ){
					//just check the path ons, without the base folder part
					szActualPath = *itrActualStandardDbFolder;
				}else{//don't check path again
					continue;
				}
			}else{//relativ path -> add actual standard subfolder part
#ifdef DEBUG_RESTORE_XML
				printf("         relativ path -> add actual standard subfolder part\n" );
#endif//DEBUG_RESTORE_XML
				szActualPath.append( "/" );
				szActualPath.append( *itrActualStandardDbFolder );
			}
			//check if database folder exists
#ifdef DEBUG_RESTORE_XML
			printf("   check if database folder %s exists\n", szActualPath.c_str() );
#endif//DEBUG_RESTORE_XML
			cFolder databaseFolder( szActualPath );
			
			if ( databaseFolder.good() ){
				//valid Fib database path found
#ifdef DEBUG_RESTORE_XML
				printf("      valid Fib database path %s found\n", szActualPath.c_str() );
#endif//DEBUG_RESTORE_XML
				szFoundDatabasePath = szActualPath;
				break;
			}//else if the database path is not valid -> check next path
#ifdef DEBUG_RESTORE_XML
			printf("   the database %s path is not valid -> check next path\n", szActualPath.c_str() );
#endif//DEBUG_RESTORE_XML
		}//end for all possible database subpaths
		//check superior folder
		uiActualSearchDepth++;
		if ( MAX_DATABASE_PATH_SEARCH_DEPTH < uiActualSearchDepth ){
#ifdef DEBUG_RESTORE_XML
			printf("the maximal database search depth %i was reached\n",
				MAX_DATABASE_PATH_SEARCH_DEPTH );
#endif//DEBUG_RESTORE_XML
			break;
		}
		if ( szActualBasePath.compare( "./" ) == 0 ){
			//replace "." with ".."
			szActualBasePath = string( "../" );
		}else{//go up one directory
			szActualBasePath.append( "../" );
		}
	}//end while no database path was found
	if ( szFoundDatabasePath.empty() ){
		//no standard Fib database directory found
#ifdef DEBUG_RESTORE_XML
		printf("cFibDatabase::searchForDatabasePath(): no standard Fib database directory found\n" );
#endif//DEBUG_RESTORE_XML
		return false;
	}//else standard Fib database directory found -> set it
#ifdef DEBUG_RESTORE_XML
	printf("cFibDatabase::searchForDatabasePath(): standard Fib database directory found\n" );
#endif//DEBUG_RESTORE_XML
	return setDatabasePath( szFoundDatabasePath );
}


/**
 * This method reloads all Fib database objects identifiers from the set
 * database path.
 * No database objects will be loaded after the reload.
 *
 * @see szDatabasePath
 * @see mapLoadedDatabaseObjects
 * @return true if the database objects identifiers could be reloded (the
 * 	database path exists), else false
 */
bool cFibDatabase::reloadDatabase(){
	
	//check database path
	const string szOkDatabasePath = getDatabase();
	if ( szOkDatabasePath == "" ){
		DEBUG_OUT_EL2(<<"Error: No valid database path could be found -> can't reload the database"<<endl);
		return false;
	}
	
#ifdef FEATURE_FIB_DB_USE_TREADS
	pthread_mutex_lock( & mutexFibDatabaseLoad );
#endif //FEATURE_FIB_DB_USE_TREADS
	if ( szOkDatabasePath.empty() ){
		//no database to reloade
#ifdef FEATURE_FIB_DB_USE_TREADS
		pthread_mutex_unlock( & mutexFibDatabaseLoad );
#endif //FEATURE_FIB_DB_USE_TREADS
		return false;
	}
	//check if the path if valid
	cFolder folder( szOkDatabasePath.c_str() );
	
	if ( ! folder.good() ){
		//the path is not valid
#ifdef FEATURE_FIB_DB_USE_TREADS
		pthread_mutex_unlock( & mutexFibDatabaseLoad );
#endif //FEATURE_FIB_DB_USE_TREADS
		return false;
	}//else if the path if valid
	//reload database paths object identifiers
	
	//load list with contained database objects
	const bool bListContainedDbObjectsLoaded =
		loadListContainedDbObjects( folder );
	
#ifdef FEATURE_FIB_DB_USE_TREADS
	pthread_mutex_unlock( & mutexFibDatabaseLoad );
#endif //FEATURE_FIB_DB_USE_TREADS
	return bListContainedDbObjectsLoaded;
}


/**
 * This method loads the database folder data.
 *
 * @see liDatabaseIdentifiers
 * @see mapDatabaseIdentifiers
 * @param folder the database folder from which to load the data
 * @return true if the data was loaded, else false
 */
bool cFibDatabase::loadListContainedDbObjects( cFolder & folder ){
	
	if ( ! folder.good() ){
		//the path is not valid
		return false;
	}//else if the path if valid
	
	//delete old loaded Fib objects
	for ( map< longFib, cRoot * >::iterator
			itrDbObject = mapLoadedDatabaseObjects.begin();
			itrDbObject != mapLoadedDatabaseObjects.end(); itrDbObject++ ){
		
		if ( itrDbObject->second ){
			itrDbObject->second->deleteObject();
		}
	}
	mapLoadedDatabaseObjects.clear();
	
	liDatabaseIdentifiers.clear();
	mapDatabaseIdentifiers.clear();
	
	//check all files in the database folder if they are Fib database objects
	const list< string > liDbFolderFiles = folder.getFiles();
	for ( list< string >::const_iterator itrDbFile = liDbFolderFiles.begin();
			itrDbFile != liDbFolderFiles.end(); itrDbFile++ ){
		
		const string & szFileName = (*itrDbFile);
		DEBUG_OUT_L3(<<"Checking database file: "<<szFileName<<endl);
		
		if ( szFileName.compare( 0, 2, "id" ) != 0 ){
			//database file donsn't start with id
			DEBUG_OUT_EL2(<<"Warning: Database file "<<szFileName<<" has wrong syntax (idIDENTIFIER.fib or idIDENTIFIER.xml), \"id\" is missing."<<endl);
			continue;
		}
		if ( ( szFileName.compare( szFileName.length() - 4, 4, ".fib" ) != 0 ) &&
				( szFileName.compare( szFileName.length() - 4, 4, ".xml" ) != 0 ) ){
			//database file donsn't start with id
			DEBUG_OUT_EL2(<<"Warning: Database file "<<szFileName<<" has wrong syntax (idIDENTIFIER.fib or idIDENTIFIER.xml), no correct ending."<<endl);
			continue;
		}//else evalue identifier

		//else evalue identifier
		
		const long lIdentifier = atol( &((szFileName.c_str())[2]) );
		
		/*this should not happen and if it happens, you can also insert the
		 * last found file; so to save the time this check would need, it deactivated
		if ( mapDatabaseIdentifiers.find( lIdentifier ) !=
				mapDatabaseIdentifiers.end() ){
			DEBUG_OUT_EL2(<<"Error: Database file "<<szFileName<<" has identifier that was used befor."<<endl);
			continue;
		}//else insert database identifier
		*/
		
		DEBUG_OUT_L3(<<"Inserting database file "<<szFileName<<" for identifier "<<lIdentifier<<endl);
		liDatabaseIdentifiers.push_back( lIdentifier );
		mapDatabaseIdentifiers.insert( make_pair( lIdentifier, szFileName ) );
	}
	liDatabaseIdentifiers.sort();
	
	return true;
}


/**
 * This method returns a valid database path if possible.
 * If the database is ok @see bDatabasePathOk
 * this will be the actual set database, else it will be searched for a
 * Fib database.
 * If a Fib database was found, the members dependent on the database
 * will be updated:
 * 	@see mapLoadedDatabaseObjects
 * 	@see mapDatabaseIdentifiers
 * 	@see liDatabaseIdentifiers
 *
 * @return a valid database path if possible
 */
string cFibDatabase::getDatabase(){
	
	if ( bDatabasePathOk ){
		//the actual set database path is OK
		return szDatabasePath;
	}//else bDatabasePathOk is not OK
	if ( szDatabasePath != "" ){
		//try the existing database path again
		if ( setDatabasePath( szDatabasePath ) ){
			//the database path was sucessfully set
			return szDatabasePath;
		}
	}//else search for the database path
	
	if ( searchForDatabasePath() ){
		//a valid database path found
		return szDatabasePath;
	}
	return "";
}


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
cRoot * cFibDatabase::loadFibObject( const string & szFileName ){
	
	//check database path
	const string szOkDatabasePath = getDatabase();
	if ( szOkDatabasePath == "" ){
		DEBUG_OUT_EL2(<<"Error: No valid database path could be found -> can't load the database object with file name "<<szFileName<<endl);
		return NULL;
	}
	
	string szPathToDbObject( szOkDatabasePath.c_str() );
	szPathToDbObject.append( szFileName );
	
	cRoot * pRestoredFibObject = NULL;
	if ( szFileName.compare( szFileName.length() - 4, 4, ".xml" ) == 0 ){
		//restore to file in xml -format
		ifstream inFile( szPathToDbObject.c_str() );
		intFib outStatus = 0;
		
		pRestoredFibObject = ((cRoot*)(cFibElement::restoreXml( inFile , &outStatus )));
		
		if ( outStatus != 0 ){
			DEBUG_OUT_EL2(<<"Error: Restoring Fib object in the Xml-Fib-format from the database file "<<szPathToDbObject<<" not successfull. (return status="<< outStatus <<")"<<endl);
			if ( outStatus < 0 ){
				bDatabasePathOk = false;
				return NULL;
			}
		}
	}else{//restore to file in compressedformat
		ifstream inFile( szPathToDbObject.c_str(), ios_base::in | ios_base::binary );
		
		intFib outStatus = 0;
		pRestoredFibObject = ((cRoot*)(cFibElement::restore( inFile , &outStatus )));
		
		if ( outStatus != 0 ){
			DEBUG_OUT_EL2(<<"Error: Restoring Fib object in the compressed Fib-format from the database file "<<szPathToDbObject<<" not successfull. (return status="<< outStatus <<")"<<endl);
			if ( outStatus < 0 ){
				bDatabasePathOk = false;
				return NULL;
			}
		}
	}
	if ( pRestoredFibObject == NULL ){
		DEBUG_OUT_EL2(<<"Error: Restoring Fib object from the database file "<<szPathToDbObject<<" not successfull. (return object NULL)"<<endl);
		return NULL;
	}
	return pRestoredFibObject;
}



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
void * cFibDatabase::treadloadFibObject( void * inputArg ){
	
	longFib & lIdentifier = *((longFib*)(inputArg));
	
	const string szOkDatabasePath = getDatabase();
	if ( szOkDatabasePath == "" ){
		DEBUG_OUT_EL2(<<"Error: No valid database path could be found -> can't load the database object with identifier "<<lIdentifier<<endl);
		return NULL;
	}
	
	pthread_mutex_lock( & mutexFibDatabaseLoad );
	map< longFib, string >::iterator
		itrDatabaseObject = mapDatabaseIdentifiers.find( lIdentifier );
	if ( itrDatabaseObject == mapDatabaseIdentifiers.end() ){
		//no such database object exists -> nothing to do
		return NULL;
	}//else load the database object
	
	pthread_mutex_unlock( & mutexFibDatabaseLoad );
	
	cRoot * pRestoredFibObject = loadFibObject( itrDatabaseObject->second );
	if ( pRestoredFibObject == NULL ){
		return NULL;
	}
	
	//use mutex for storing loaded
	pthread_mutex_lock( & mutexFibDatabaseLoad );
	mapLoadedDatabaseObjects.insert( make_pair( lIdentifier, pRestoredFibObject ) );
	pthread_mutex_unlock( & mutexFibDatabaseLoad );
	
	return ((void*)(pRestoredFibObject));
}

#endif //FEATURE_FIB_DB_USE_TREADS




