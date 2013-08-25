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
*/

//TODO switches for test proposes
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
	
	//load database
	bool bDatabaseLoaded = false;
	if ( ! szDatabasePath.empty() ){
		//if a database path was set -> try to load it
		bDatabaseLoaded = setDatabasePath( szDatabasePath );
	}
	if ( ! bDatabaseLoaded ){
		//no valid Fib database directory check standard Fib database directories
		searchForDatabasePath();
	}
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
		pFibDbInstance = new cFibDatabase();
	}//else return existing instance
	return pFibDbInstance;
}


/**
 * This method returns the identifiers of all database objects, in the
 * actual database.
 *
 * @return the identifiers of all database objects
 */
list< longFib > cFibDatabase::getAllDatabaseObjectIdentifiers() const{
	
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
	const string & szFileName = itrDatabaseObject->second;
	string szPathToDbObject( szDatabasePath.c_str() );
	szPathToDbObject.append( szFileName );
#ifdef FEATURE_FIB_DB_USE_TREADS
	pthread_mutex_unlock( & mutexFibDatabaseLoad );
#endif //FEATURE_FIB_DB_USE_TREADS
	cRoot * pRestoredFibObject = NULL;
	if ( szFileName.compare( szFileName.length() - 4, 4, ".xml" ) == 0 ){
		//restore to file in xml -format
		ifstream inFile( szPathToDbObject.c_str() );
		intFib outStatus = 0;
		
		pRestoredFibObject = ((cRoot*)(cFibElement::restoreXml( inFile , &outStatus )));
		
		if ( outStatus != 0 ){
			DEBUG_OUT_EL2(<<"Error: Restoring Fib object in the Xml-Fib-format from the database file "<<itrDatabaseObject->second <<" not successfull. (return status="<< outStatus <<")"<<endl);
			if ( outStatus < 0 ){
				return NULL;
			}
		}
	}else{//restore to file in compressedformat
		ifstream inFile( szPathToDbObject.c_str(), ios_base::in | ios_base::binary );
		
		intFib outStatus = 0;
		pRestoredFibObject = ((cRoot*)(cFibElement::restore( inFile , &outStatus )));
		
		if ( outStatus != 0 ){
			DEBUG_OUT_EL2(<<"Error: Restoring Fib object in the compressed Fib-format from the database file "<<itrDatabaseObject->second <<" not successfull. (return status="<< outStatus <<")"<<endl);
			if ( outStatus < 0 ){
				return NULL;
			}
		}
	}
	if ( pRestoredFibObject == NULL ){
		DEBUG_OUT_EL2(<<"Error: Restoring Fib object in the compressed Fib-format from the database file "<<itrDatabaseObject->second <<" not successfull. (return object NULL)"<<endl);
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
#endif //FEATURE_FIB_DB_USE_TREADS
	
#ifdef FEATURE_FIB_DB_USE_TREADS
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
	const string & szFileName = itrDatabaseObject->second;
	string szPathToDbObject( szDatabasePath.c_str() );
	szPathToDbObject.append( szFileName );
	
	cRoot * pRestoredFibObject = NULL;
	if ( szFileName.compare( szFileName.length() - 4, 4, ".xml" ) == 0 ){
		//restore to file in xml -format
		ifstream inFile( szPathToDbObject.c_str() );
		intFib outStatus = 0;
		
		pRestoredFibObject = ((cRoot*)(cFibElement::restoreXml( inFile , &outStatus )));
		
		if ( outStatus != 0 ){
			DEBUG_OUT_EL2(<<"Error: Restoring Fib object in the Xml-Fib-format from the database file "<<itrDatabaseObject->second <<" not successfull. (return status="<< outStatus <<")"<<endl);
			if ( outStatus < 0 ){
				return;
			}
		}
	}else{//restore to file in compressedformat
		ifstream inFile( szPathToDbObject.c_str(), ios_base::in | ios_base::binary );
		
		intFib outStatus = 0;
		pRestoredFibObject = ((cRoot*)(cFibElement::restore( inFile , &outStatus )));
		
		if ( outStatus != 0 ){
			DEBUG_OUT_EL2(<<"Error: Restoring Fib object in the compressed Fib-format from the database file "<<itrDatabaseObject->second <<" not successfull. (return status="<< outStatus <<")"<<endl);
			if ( outStatus < 0 ){
				return;
			}
		}
	}
	if ( pRestoredFibObject == NULL ){
		DEBUG_OUT_EL2(<<"Error: Restoring Fib object in the compressed Fib-format from the database file "<<itrDatabaseObject->second <<" not successfull. (return object NULL)"<<endl);
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
	
	return setDatabasePath( string( szInDatabasePath ) );
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
		return false;
	}
	if ( szInDatabasePath == szDatabasePath ){
		//database path set already
		return true;
	}
	//check if the path if valid
	cFolder folder( szInDatabasePath.c_str() );
	
	if ( ! folder.good() ){
		//the path is not valid
		return false;
	}//else if the path if valid
	//set database path
#ifdef FEATURE_FIB_DB_USE_TREADS
	pthread_mutex_lock( & mutexFibDatabaseLoad );
#endif //FEATURE_FIB_DB_USE_TREADS

	szDatabasePath = szInDatabasePath;
	
	//load list with contained database objects
	const bool bListContainedDbObjectsLoaded =
		loadListContainedDbObjects( folder );
	
#ifdef FEATURE_FIB_DB_USE_TREADS
	pthread_mutex_unlock( & mutexFibDatabaseLoad );
#endif //FEATURE_FIB_DB_USE_TREADS
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

	//search for path
	while ( szFoundDatabasePath.empty() ){
		//check if base folder exists
		cFolder baseFolder( szActualBasePath );
		
		if ( ! baseFolder.good() ){
			//the path is not valid -> no standar database folder could be found
			return false;
		}//else if the base path if valid
		
		//search in subpath for standard database folders
		for ( list< string >::iterator
				itrActualStandardDbFolder = liSzStandardDatabaseFolders.begin();
				itrActualStandardDbFolder != liSzStandardDatabaseFolders.end();
				itrActualStandardDbFolder++ ){
			
			string szActualPath( szActualBasePath );
			if ( itrActualStandardDbFolder->at( 0 ) == '/' ){
				//absolute path
				if ( szActualBasePath.compare( "./" ) == 0 ){
					//just check the path ons, without the base folder part
					szActualPath = *itrActualStandardDbFolder;
				}else{//don't check path again
					continue;
				}
			}else{//relativ path -> add actual standard subfolder part
				szActualPath.append( "/" );
				szActualPath.append( *itrActualStandardDbFolder );
			}
			//check if database folder exists
			cFolder databaseFolder( szActualPath );
			
			if ( databaseFolder.good() ){
				//valid Fib database path found
				szFoundDatabasePath = szActualPath;
				break;
			}//else if the database path is not valid -> check next path
		}//end for all possible database subpaths
		//check superior folder
		if ( szActualBasePath.compare( "./" ) == 0 ){
			//replace "." with ".."
			szActualBasePath = string( "../" );
		}else{//go up one directory
			szActualBasePath.append( "../" );
		}
	}//end while no database path was found
	if ( szFoundDatabasePath.empty() ){
		//no standard Fib database directory found
		return false;
	}//else standard Fib database directory found -> set it
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
	
#ifdef FEATURE_FIB_DB_USE_TREADS
	pthread_mutex_lock( & mutexFibDatabaseLoad );
#endif //FEATURE_FIB_DB_USE_TREADS
	if ( szDatabasePath.empty() ){
		//no database to reloade
		return false;
	}
	//check if the path if valid
	cFolder folder( szDatabasePath.c_str() );
	
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
	
	pthread_mutex_lock( & mutexFibDatabaseLoad );
	map< longFib, string >::iterator
		itrDatabaseObject = mapDatabaseIdentifiers.find( lIdentifier );
	if ( itrDatabaseObject == mapDatabaseIdentifiers.end() ){
		//no such database object exists -> nothing to do
		return NULL;
	}//else load the database object
	
	const string & szFileName = itrDatabaseObject->second;
	string szPathToDbObject( szDatabasePath.c_str() );
	szPathToDbObject.append( szFileName );
	
	pthread_mutex_unlock( & mutexFibDatabaseLoad );
	
	cRoot * pRestoredFibObject = NULL;
	if ( szFileName.compare( szFileName.length() - 4, 4, ".xml" ) == 0 ){
		//restore to file in xml -format
		ifstream inFile( szPathToDbObject.c_str() );
		intFib outStatus = 0;
		
		pRestoredFibObject = ((cRoot*)(cFibElement::restoreXml( inFile , &outStatus )));
		
		if ( outStatus != 0 ){
			DEBUG_OUT_EL2(<<"Error: Restoring Fib object in the Xml-Fib-format from the database file "<<itrDatabaseObject->second <<" not successfull. (return status="<< outStatus <<")"<<endl);
			if ( outStatus < 0 ){
				return NULL;
			}
		}
	}else{//restore to file in compressedformat
		ifstream inFile( szPathToDbObject.c_str(), ios_base::in | ios_base::binary );
		
		intFib outStatus = 0;
		pRestoredFibObject = ((cRoot*)(cFibElement::restore( inFile , &outStatus )));
		
		if ( outStatus != 0 ){
			DEBUG_OUT_EL2(<<"Error: Restoring Fib object in the compressed Fib-format from the database file "<<itrDatabaseObject->second <<" not successfull. (return status="<< outStatus <<")"<<endl);
			if ( outStatus < 0 ){
				return NULL;
			}
		}
	}
	if ( pRestoredFibObject == NULL ){
		DEBUG_OUT_EL2(<<"Error: Restoring Fib object in the compressed Fib-format from the database file "<<itrDatabaseObject->second <<" not successfull. (return object NULL)"<<endl);
		return NULL;
	}

	//use mutex for storing loaded
	pthread_mutex_lock( & mutexFibDatabaseLoad );
	mapLoadedDatabaseObjects.insert( make_pair( lIdentifier, pRestoredFibObject ) );
	pthread_mutex_unlock( & mutexFibDatabaseLoad );
	
	return ((void*)(pRestoredFibObject));
}

#endif //FEATURE_FIB_DB_USE_TREADS




