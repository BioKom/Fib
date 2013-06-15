
//TODO check

/**
 * @class cFibDatabaseJavaScript
 * file name: cFibDatabaseJavaScript.cpp
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

//switches for test proposes
//#define DEBUG

#ifdef DEBUG_RESTORE_XML
	#define DEBUG
#endif//DEBUG_RESTORE_XML


#include "cFibDatabaseJavaScript.h"

#include "funJavaScriptFileHandling.h"
#include "fibDatabaseFiles.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>



using namespace fib;
using namespace std;

//down't work (javascript for browsers, isn't good with file handling)
//#define FIB_DATABASE_CHECK_PATH

/**
 * constructor
 */
cFibDatabaseJavaScript::cFibDatabaseJavaScript(){
	//nothing to do
}


/**
 * destructor
 */
cFibDatabaseJavaScript::~cFibDatabaseJavaScript(){
	//nothing to do
}


/**
 * @return a instance of the database object
 */
cFibDatabase * cFibDatabaseJavaScript::getInstance(){
	
	if ( pFibDbInstance == NULL ){
		//create a new instance
#ifdef DEBUG_RESTORE_XML
		printf("cFibDatabaseJavaScript::getInstance(): create a new instance\n" );
#endif//DEBUG_RESTORE_XML
		pFibDbInstance = new cFibDatabaseJavaScript();
	}//else return existing instance
#ifdef DEBUG_RESTORE_XML
	printf("cFibDatabaseJavaScript::getInstance(): return existing instance\n" );
#endif//DEBUG_RESTORE_XML
	return pFibDbInstance;
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
bool cFibDatabaseJavaScript::setDatabasePath( const string szInDatabasePath ){
	
#ifdef DEBUG_RESTORE_XML
	printf("cFibDatabaseJavaScript::setDatabasePath( szInDatabasePath=%s )\n", szInDatabasePath.c_str() );
#endif//DEBUG_RESTORE_XML
	if ( szInDatabasePath == "" ){
		//no database path to set
#ifdef DEBUG_RESTORE_XML
		printf("cFibDatabaseJavaScript::setDatabasePath(): no database path to set\n" );
#endif//DEBUG_RESTORE_XML
		return false;
	}
	if ( bDatabasePathOk && ( szInDatabasePath == szDatabasePath ) ){
		//database path set already
#ifdef DEBUG_RESTORE_XML
		printf("cFibDatabaseJavaScript::setDatabasePath(): database path set already\n" );
#endif//DEBUG_RESTORE_XML
		return true;
	}
	//check if the path if valid
	if ( ! checkIfDatabasePath( szInDatabasePath ) ){
		//the path is not valid
#ifdef DEBUG_RESTORE_XML
		printf("cFibDatabaseJavaScript::setDatabasePath(): the path is not valid\n" );
#endif//DEBUG_RESTORE_XML
		return false;
	}//else if the path if valid
	//set database path
#ifdef DEBUG_RESTORE_XML
	printf("cFibDatabaseJavaScript::setDatabasePath(): set database path\n" );
#endif//DEBUG_RESTORE_XML
#ifdef FEATURE_FIB_DB_USE_TREADS
	pthread_mutex_lock( & mutexFibDatabaseLoad );
#endif //FEATURE_FIB_DB_USE_TREADS

	szDatabasePath  = szInDatabasePath;
	bDatabasePathOk = true;
	
#ifdef DEBUG_RESTORE_XML
	printf("cFibDatabaseJavaScript::setDatabasePath(): load list with contained database objects\n" );
#endif//DEBUG_RESTORE_XML
	//load list with contained database objects
	const bool bListContainedDbObjectsLoaded =
		loadListContainedDbObjects( szInDatabasePath );
	
#ifdef FEATURE_FIB_DB_USE_TREADS
	pthread_mutex_unlock( & mutexFibDatabaseLoad );
#endif //FEATURE_FIB_DB_USE_TREADS
#ifdef DEBUG_RESTORE_XML
	printf("cFibDatabaseJavaScript::setDatabasePath() done\n" );
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
bool cFibDatabaseJavaScript::searchForDatabasePath(){
	
#ifdef DEBUG_RESTORE_XML
	printf("cFibDatabaseJavaScript::searchForDatabasePath() started\n" );
#endif//DEBUG_RESTORE_XML
	//list with the standard database folders
	list< string > liSzStandardDatabaseFolders;
	liSzStandardDatabaseFolders.push_back( "fibDatabase/" );
	/* TODO needs to long:
	liSzStandardDatabaseFolders.push_back( "." );
	liSzStandardDatabaseFolders.push_back( "fibDb/" );
	liSzStandardDatabaseFolders.push_back( "fibDB/" );
	liSzStandardDatabaseFolders.push_back( "fib/fibDatabase/" );
	liSzStandardDatabaseFolders.push_back( "fib/fibDb/" );
	liSzStandardDatabaseFolders.push_back( "fib/fibDB/" );*/

	//the path to the found Fib database directory; if empty non was found
	string szFoundDatabasePath;
	//the path to the actual base directory
	string szActualBasePath( "./" );
	
	unsigned int uiActualSearchDepth = 0;
	//search for path
	while ( szFoundDatabasePath.empty() ){
		//check if base folder exists
#ifdef DEBUG_RESTORE_XML
		printf("cFibDatabaseJavaScript::searchForDatabasePath() check path: %s\n", szActualBasePath.c_str() );
#endif//DEBUG_RESTORE_XML
		
#ifdef FIB_DATABASE_CHECK_PATH
		if ( ! checkIfFolderExists( szActualBasePath ) ){
			//the path is not valid -> no standard database folder could be found
#ifdef DEBUG_RESTORE_XML
			printf("   the path %s is not valid -> no standar database folder could be found\n", szActualBasePath.c_str() );
#endif//DEBUG_RESTORE_XML
			return false;
		}//else if the base path if valid
#endif //FIB_DATABASE_CHECK_PATH

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
					//just check the path ones, without the base folder part
					szActualPath = *itrActualStandardDbFolder;
				}else{//don't check path again
					continue;
				}
			}else{//relativ path -> add actual standard subfolder part
#ifdef DEBUG_RESTORE_XML
				printf("         relativ path -> add actual standard subfolder part\n" );
#endif//DEBUG_RESTORE_XML
				//szActualPath.append( "/" );
				szActualPath.append( *itrActualStandardDbFolder );
			}
			//check if database folder exists
#ifdef DEBUG_RESTORE_XML
			printf("   check if database folder %s exists\n", szActualPath.c_str() );
#endif//DEBUG_RESTORE_XML
			
			if ( checkIfDatabasePath( szActualPath ) ){
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
		if ( MAX_DATABASE_JAVASCRIPT_PATH_SEARCH_DEPTH < uiActualSearchDepth ){
#ifdef DEBUG_RESTORE_XML
			printf("the maximal database search depth %i was reached\n",
				MAX_DATABASE_JAVASCRIPT_PATH_SEARCH_DEPTH );
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
		if ( checkIfDatabasePath( "http://www.fib-development.org/fibDatabase/" ) ){
			//valid Fib database path found
#ifdef DEBUG_RESTORE_XML
			printf("      valid Fib database path \"http://www.fib-development.org/fibDatabase/\" found\n" );
#endif//DEBUG_RESTORE_XML
			szFoundDatabasePath = "http://www.fib-development.org/fibDatabase/";
		}//else if the database path is not valid
	}
	
	if ( szFoundDatabasePath.empty() ){
		//no standard Fib database directory found
#ifdef DEBUG_RESTORE_XML
		printf("cFibDatabaseJavaScript::searchForDatabasePath(): no standard Fib database directory found\n" );
#endif//DEBUG_RESTORE_XML
		return false;
	}//else standard Fib database directory found -> set it
#ifdef DEBUG_RESTORE_XML
	printf("cFibDatabaseJavaScript::searchForDatabasePath(): standard Fib database directory %s found\n", szFoundDatabasePath.c_str() );
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
bool cFibDatabaseJavaScript::reloadDatabase(){
	
#ifdef DEBUG_RESTORE_XML
	printf("cFibDatabaseJavaScript::reloadDatabase()\n" );
#endif//DEBUG_RESTORE_XML
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
	if ( ! checkIfDatabasePath( szOkDatabasePath ) ){
		//the path is not valid
#ifdef DEBUG_RESTORE_XML
		printf("cFibDatabaseJavaScript::setDatabasePath(): the path is not valid\n" );
#endif//DEBUG_RESTORE_XML
		return false;
	}//else if the path if valid

	//reload database paths object identifiers
	
	//load list with contained database objects
	const bool bListContainedDbObjectsLoaded =
		loadListContainedDbObjects( szOkDatabasePath );
	
#ifdef FEATURE_FIB_DB_USE_TREADS
	pthread_mutex_unlock( & mutexFibDatabaseLoad );
#endif //FEATURE_FIB_DB_USE_TREADS
	return bListContainedDbObjectsLoaded;
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
cRoot * cFibDatabaseJavaScript::loadFibObject( const string & szFileName ){
	
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
		istream * pInFile = openFileStream( szPathToDbObject.c_str() );
		if ( pInFile == NULL ){
			//no such database object exists -> return NULL
			DEBUG_OUT_EL2(<<"Error: No such file \""<<szPathToDbObject<<"\" for database object exists. -> return NULL"<<endl);
			return NULL;
		}
		intFib outStatus = 0;
		
		pRestoredFibObject = ((cRoot*)(cFibElement::restoreXml( *pInFile , &outStatus )));
		delete pInFile;
		
		if ( outStatus != 0 ){
			DEBUG_OUT_EL2(<<"Error: Restoring Fib object in the Xml-Fib-format from the database file "<<szPathToDbObject<<" not successfull. (return status="<< outStatus <<")"<<endl);
			if ( outStatus < 0 ){
				if ( pRestoredFibObject ){
					delete pRestoredFibObject;
				}
				return NULL;
			}
		}
	}else{//restore to file in compressedformat
		istream * pInFile = openFileStream( szPathToDbObject.c_str() );
		if ( pInFile == NULL ){
			//no such database object exists -> return NULL
			DEBUG_OUT_EL2(<<"Error: No such file \""<<szPathToDbObject<<"\" for database object exists. -> return NULL"<<endl);
			return NULL;
		}
		
		intFib outStatus = 0;
		pRestoredFibObject = ((cRoot*)(cFibElement::restore( *pInFile , &outStatus )));
		delete pInFile;
		
		if ( outStatus != 0 ){
			DEBUG_OUT_EL2(<<"Error: Restoring Fib object in the compressed Fib-format from the database file "<<szPathToDbObject<<" not successfull. (return status="<< outStatus <<")"<<endl);
			if ( outStatus < 0 ){
				if ( pRestoredFibObject ){
					delete pRestoredFibObject;
				}
				return NULL;
			}
		}
	}
	if ( pRestoredFibObject == NULL ){
		DEBUG_OUT_EL2(<<"Error: Restoring Fib object in the compressed Fib-format from the database file "<<szPathToDbObject<<" not successfull. (return object NULL)"<<endl);
		return NULL;
	}
	return pRestoredFibObject;
}


/**
 * This method loads the database folder data.
 *
 * @see liDatabaseIdentifiers
 * @see mapDatabaseIdentifiers
 * @param folder dummy for compatibility to cFibDatabase
 * @return true if the data was loaded, else false
 */
bool cFibDatabaseJavaScript::loadListContainedDbObjects( const string & folder ){
	
	DEBUG_OUT_L2(<<" cFibDatabaseJavaScript::loadListContainedDbObjects()"<<endl);
	
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
	
	//check all files in the database if they are Fib database objects
	const list< string > liDbFolderFiles = getDatabaseFiles();
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
 * This function opens the stream for the given path.
 *
 * @param zsPath the path of the file to open
 * @return the open stream
 */
istream * cFibDatabaseJavaScript::openFileStream( const char * zsPath ){
	
	//delegate to javascript function
	return jsOpenFileStream( zsPath );
}


/**
 * This function checks if the given path is a database path.
 * (It is a database path if it exists and contains a id-000000.xml or
 * id-000000.fib file. )
 *
 * @param zsPath the path to check
 * @return true if the path is a database path, else false
 */
bool cFibDatabaseJavaScript::checkIfDatabasePath( const string & zsPath ){

#ifdef FIB_DATABASE_CHECK_PATH
	if ( ! checkIfFolderExists( zsPath ) ){
		return false;
	}
#endif //FIB_DATABASE_CHECK_PATH
	//check if a id-000000.xml or id-000000.fib file in path exists
	DEBUG_OUT_L4(<<"FibDatabaseJavaScript::checkIfDatabasePath( zsPath="<<zsPath<<" ): check if a id-000000.xml or id-000000.fib file in path exists"<<endl);
	if ( jsCheckIfFileExists( (zsPath + "id-000000.xml").c_str() ) ||
			jsCheckIfFileExists( (zsPath + "id-000000.fib").c_str() ) ){
		//the file id-000000.xml or id-000000.fib in path exists -> database path
		return true;
	}
	return false;
}

#ifdef FIB_DATABASE_CHECK_PATH
/**
 * This function checks if the given path is a existing folder.
 *
 * @param zsPath the path to check
 * @return true if the path is a existing folder, else false
 */
bool cFibDatabaseJavaScript::checkIfFolderExists( const string & zsPath ){
	//TODO dosn't work
	
	//delegate to javascript function
	return jsCheckIfFolderExists( zsPath.c_str() );
}
#endif //FIB_DATABASE_CHECK_PATH

/**
 * This function returns a list with the Fib database files.
 *
 * @return a list with the Fib database files
 */
list< string > cFibDatabaseJavaScript::getDatabaseFiles(){
	
	DEBUG_OUT_L4(<<"FibDatabaseJavaScript::getDatabaseFiles()"<<endl);
	//evalue file list with a script in make
	list< string > liFilesOfFibDatabase( arSzFilesOfFibDatabase,
		arSzFilesOfFibDatabase + uiNumberArSzFilesOfFibDatabase );
	
	//to simpleyfy the script the list ends with "", wich will now be removed
	if ( liFilesOfFibDatabase.back() == "" ){
		liFilesOfFibDatabase.pop_back();
	}
	
	return liFilesOfFibDatabase;
}







