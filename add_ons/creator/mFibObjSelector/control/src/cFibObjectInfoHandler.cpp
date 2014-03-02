/**
 * @file cFibObjectInfoHandler
 * file name: cFibObjectInfoHandler.cpp
 * @author Betti Oesterholz
 * @date 01.10.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for handling Fib object info objects for
 * the Fib creator application.
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
 * This file implements a class for handling Fib object info objects for
 * the Fib creator application.
 * Fib object info objects contain the information about a Fib object.
 * This handler should work like a database for Fib objects, which can be
 * used by the Fib creator application. So the user can easily choose a
 * Fib object. The Fib object info objects contain the information and
 * dependency information for Fib objects, so that they can be displayed
 * in a way that the user can choose from them a Fib object to use.
 *
 *
 * == Persistence ==
 *
 * Existing (including new created) Fib object info objects will be stored,
 * so that they can be retrieved later.
 *
 *
 * @pattern singelton
 * @see cFibObjectInfo
 * @see cFibObjectSource
 */
/*
History:
01.10.2013  Oesterholz  created
*/


//switches for test proposes
//#define DEBUG


#include "cFibObjectInfoHandler.h"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <list>
#include <stack>

#include <QSettings>
#include <QString>
#include <QDir>
#include <QFile>
#include <QIODevice>

#include "cFibDatabase.h"

#include "cFibObjectInfo.h"
#include "cFibObjectSource.h"
#include "cFibObjectSourceFibDb.h"
#include "cFibObjectCategory.h"

using namespace std;
using namespace fib::nCreator;



/**
 * A pointer to the info object handler object.
 */
cFibObjectInfoHandler * cFibObjectInfoHandler::pFibObjectInfoHandler = NULL;




namespace fib{
namespace nCreator{
namespace nFibObjectInfoHandler{

	/**
	 * This class is for deleting the Fib info object handler when the
	 * program ends.
	 * @see cFibObjectInfoHandlerDeleter
	 */
	class cFibObjectInfoHandlerDeleter{
	public:
		
		/**
		 * destructor which deletes the info object handler if not allready deleted
		 */
		~cFibObjectInfoHandlerDeleter() {
			
			DEBUG_OUT_L2(<<"cFibObjectInfoHandlerDeleter("<<this<<")::~cFibObjectInfoHandlerDeleter() called"<<endl<<flush);
	
			if ( cFibObjectInfoHandler::pFibObjectInfoHandler != NULL ) {
				//delete Fib info object handler
				delete cFibObjectInfoHandler::pFibObjectInfoHandler;
				cFibObjectInfoHandler::pFibObjectInfoHandler = NULL;
			}
		}
		
	};//end class cFibObjectInfoHandlerDeleter
	
	/**
	 * Object to delete the Fib info object handler, when the program ends.
	 */
	cFibObjectInfoHandlerDeleter fibNodeHandlerDeleter;
	
};//end namespace nFibObjectInfoHandler
};//end namespace nCreator
};//end namespace fib




/**
 * The constructor for the Fib info object handler.
 */
cFibObjectInfoHandler::cFibObjectInfoHandler():
		ulFirstFreeIdentifier( 1 ), szPathToFibObjectInfos( NULL )
#ifdef FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
		, bReevaluateMapCategoryUsedTimeSortedFibObjectInfos( true )
#endif //FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
		{
	
	DEBUG_OUT_L2(<<"cFibObjectInfoHandler("<<this<<")::cFibObjectInfoHandler() called"<<endl<<flush);
			
	if ( pFibObjectInfoHandler != NULL ) {
		//delete main window handler
		delete pFibObjectInfoHandler;
		pFibObjectInfoHandler = NULL;
	}
	pFibObjectInfoHandler = this;
	
	szPathToFibObjectInfos = getFibObjectInfoPath();
	loadListOfInfoObjects();
	
	if ( ! checkFibDbIdsExist() ) {
		loadFibDatabase();
	}
}


/**
 * destructor
 */
cFibObjectInfoHandler::~cFibObjectInfoHandler() {
	
	DEBUG_OUT_L2(<<"cFibObjectInfoHandler("<<this<<")::~cFibObjectInfoHandler() called"<<endl<<flush);
	
	mutexFibObjectInfoHandler.lock();
	for ( set< cFibObjectInfo * >::iterator
			itrFibObjectInfo = setFibObjectInfos.begin();
			itrFibObjectInfo != setFibObjectInfos.end(); ++itrFibObjectInfo ) {
		
		(*itrFibObjectInfo)->unregisterFibObjectInfoChangeListener( this );
		delete (*itrFibObjectInfo);
	}
	setFibObjectInfos.clear();
	mapFibObjectInfos.clear();
	
	if ( szPathToFibObjectInfos ) {
		delete szPathToFibObjectInfos;
	}
	
	pFibObjectInfoHandler = NULL;
	
	mutexFibObjectInfoHandler.unlock();
}


/**
 * @return an instance of the Fib info object handler
 */
cFibObjectInfoHandler * cFibObjectInfoHandler::getInstance() {
	
	if ( pFibObjectInfoHandler == NULL ) {
		//create a new instance
		pFibObjectInfoHandler = new cFibObjectInfoHandler();
	}//else return existing instance
	return pFibObjectInfoHandler;
}


/**
 * @return the name of this class "cFibObjectInfoHandler"
 */
std::string cFibObjectInfoHandler::getName() const {
	
	return string("cFibObjectInfoHandler");
}


/**
 * @return the number of Fib object info objects in this handler
 */
unsigned int cFibObjectInfoHandler::getNumberOfFibObjectInfos() const {
	
	mutexFibObjectInfoHandler.lock();
	const unsigned int uiNumberOfFibObjectInfos = setFibObjectInfos.size();
	mutexFibObjectInfoHandler.unlock();
	return uiNumberOfFibObjectInfos;
}


/**
 * This method returns the Fib object info object for the given identifier.
 *
 * @param ulIdentifier the identifer of the Fib object info object to return
 * @return the Fib object info object for the given identifier or
 * 	the null pointer NULL if non exists
 */
cFibObjectInfo * cFibObjectInfoHandler::getFibObjectInfo(
		const unsigned long ulIdentifier ) {
	
	DEBUG_OUT_L2(<<"cFibObjectInfoHandler("<<this<<")::getFibObjectInfo( ulIdentifier="<<ulIdentifier<<") called"<<endl<<flush);
	
	mutexFibObjectInfoHandler.lock();
	
	std::map< unsigned long , cFibObjectInfo * >::iterator
		itrFibObjectInfo = mapFibObjectInfos.find( ulIdentifier );
	
	if ( itrFibObjectInfo == mapFibObjectInfos.end() ) {
		//no such Fib object info object
		mutexFibObjectInfoHandler.unlock();
		DEBUG_OUT_L2(<<"cFibObjectInfoHandler("<<this<<")::getFibObjectInfo( ulIdentifier="<<ulIdentifier<<") done: no such Fib object info object"<<endl<<flush);
		return NULL;
	}//Fib object info object for identifer exists
	cFibObjectInfo * pFibObjectInfo = itrFibObjectInfo->second;
	if ( pFibObjectInfo != NULL ) {
		//Fib object info object allready loaded -> return pointer to it
		mutexFibObjectInfoHandler.unlock();
		DEBUG_OUT_L2(<<"cFibObjectInfoHandler("<<this<<")::getFibObjectInfo( ulIdentifier="<<ulIdentifier<<") done returning existing "<<pFibObjectInfo<<endl<<flush);
		return pFibObjectInfo;
	}//else Fib object info object not loaded
	
	pFibObjectInfo = loadFibInfoObject( ulIdentifier );
	if ( pFibObjectInfo ) {
		//insert loaded Fib object info
		setFibObjectInfos.insert( pFibObjectInfo );
		pFibObjectInfo->registerFibObjectInfoChangeListener( this );
		itrFibObjectInfo->second = pFibObjectInfo;
		//add to sorted Fib object info objects
		addToUsedTimeSortedFibObjectInfos( pFibObjectInfo );
		//add possible categories of new Fib object (info)
		addPossibleCategories( pFibObjectInfo->getCategories() );
	}
	mutexFibObjectInfoHandler.unlock();
	
	DEBUG_OUT_L2(<<"cFibObjectInfoHandler("<<this<<")::getFibObjectInfo( ulIdentifier="<<ulIdentifier<<") done returning loaded "<<pFibObjectInfo<<endl<<flush);
	return pFibObjectInfo;
}


/**
 * This method returns the Fib object info objects for the given
 * identifiers. The order of the Fib object info objects will be that
 * of the identifiers. Identifiers for which no Fib object info objects
 * exists will be ignored.
 *
 * @param lIdentifier the list with the identifers of the Fib object
 * 	info objects to return
 * @return the Fib object info object for the given identifiers or
 * 	the null pointer NULL if non exists
 */
list< cFibObjectInfo * > cFibObjectInfoHandler::getFibObjectInfos(
		const list< unsigned long > & lIdentifier ) {
	
	list< cFibObjectInfo * > liFibObjectInfosToReturn;
	for ( list< unsigned long >::const_iterator
			itrIdentifier = lIdentifier.begin();
			itrIdentifier != lIdentifier.end(); ++itrIdentifier ) {
		
		cFibObjectInfo * pActualFibObjectInfo =
			getFibObjectInfo( *itrIdentifier );
		
		if ( pActualFibObjectInfo ) {
			//add loaded Fib object info object to the return list
			liFibObjectInfosToReturn.push_back( pActualFibObjectInfo );
		}//else no Fib object info object loaded -> non exists -> ignore identifier
	}
	return liFibObjectInfosToReturn;
}


/**
 * This method will return the identifier for the Fib object info
 * object for the given Fib object source object.
 * If needed it will load Fib object and create info object for it.
 *
 * @param pFibObjectSource a pointer to the Fib object source object,
 * 	for which the Fib object info object identifier should be returned
 * @return the identifier for the Fib object info object for the given
 * 	Fib object source object or 0 if non exists
 */
unsigned long cFibObjectInfoHandler::getIdentifierForSource(
		const cFibObjectSource * pFibObjectSource ) {
	
	if ( pFibObjectSource == NULL ) {
		//no source object given -> Fib object info object for it exists
		return 0;
	}
	mutexFibObjectInfoHandler.lock();
	//check all loaded Fib object info objects
	cFibObjectSource * pActualFibObjectSource = NULL;
	for ( set< cFibObjectInfo * >::const_iterator
			itrFibObjectInfo = setFibObjectInfos.begin();
			itrFibObjectInfo != setFibObjectInfos.end(); ++itrFibObjectInfo ) {
		
		pActualFibObjectSource = (*itrFibObjectInfo)->getFibObjectSource();
		if ( ( pActualFibObjectSource != NULL ) &&
				pActualFibObjectSource->equal( *pFibObjectSource ) ) {
			/*Fib object info object for the source object found
			 *-> return its identifier*/
			const unsigned long ulFoundIdentifier =
				(*itrFibObjectInfo)->getIdentifier();
			mutexFibObjectInfoHandler.unlock();
			return ulFoundIdentifier;
		}//else source objects not equal
	}//else no loaded Fib object info object for the source object found
	
	//check (and load) not loaded Fib object info objects
	cFibObjectInfo * pFibObjectInfo = NULL;
	for ( map< unsigned long , cFibObjectInfo * >::iterator
			itrFibObjectInfo = mapFibObjectInfos.begin();
			itrFibObjectInfo != mapFibObjectInfos.end(); ++itrFibObjectInfo ) {
		
		if ( itrFibObjectInfo->second != NULL ) {
			//Fib object info object for identifier loaded -> it was checked
			continue;
		}//else
		pFibObjectInfo = loadFibInfoObject( itrFibObjectInfo->first );
		if ( pFibObjectInfo ) {
			//insert loaded Fib object info
			setFibObjectInfos.insert( pFibObjectInfo );
			pFibObjectInfo->registerFibObjectInfoChangeListener( this );
			itrFibObjectInfo->second = pFibObjectInfo;
			//add possible categories of new Fib object (info)
			addPossibleCategories( pFibObjectInfo->getCategories() );
			
			pFibObjectSource = pFibObjectInfo->getFibObjectSource();
			if ( ( pFibObjectSource != NULL ) &&
					pFibObjectSource->equal( *pFibObjectSource ) ) {
				/*Fib object info object for the source object found
				 *-> return its identifier*/
				const unsigned long ulFoundIdentifier =
					pFibObjectInfo->getIdentifier();
				mutexFibObjectInfoHandler.unlock();
				return ulFoundIdentifier;
			}//else source objects not equal
		}//else no Fib object info object could be loaded -> check next identifier
	}//else no Fib object info object for the source object found
	mutexFibObjectInfoHandler.unlock();
	return 0;
}


/**
 * This method will add the given Fib object info object to the
 * Fib object info objects of this handler.
 * If the identifier of the Fib object info object is 0 , a free
 * identifier will be choosen and set for the inserted Fib object info
 * object.
 * If the identifer of the Fib object info object is used allready,
 * the given Fib object info object will overwrite the existing
 * Fib object info object with the same identifier.
 *
 * @see mapFibObjectInfos
 * @see setFibObjectInfos
 * @see removeFibObjectInfo()
 * @param fibObjectInfo the Fib object info object to add to this handler
 * @return true if the Fib object info object was added, else false
 */
bool cFibObjectInfoHandler::addFibObjectInfo( const cFibObjectInfo & fibObjectInfo ) {
	
	cFibObjectInfo * pFibObjectInfoToInsert;
	unsigned long ulIdentifier = fibObjectInfo.getIdentifier();
	if ( ulIdentifier != 0 ) {
		//clone the Fib object info object
		pFibObjectInfoToInsert = fibObjectInfo.clone();
	}else{// ulIdentifier == 0 -> set first free identifier
		pFibObjectInfoToInsert = fibObjectInfo.clone( ulFirstFreeIdentifier );
		ulIdentifier = ulFirstFreeIdentifier;
	}
	mutexFibObjectInfoHandler.lock();
	
	map< unsigned long , cFibObjectInfo * >::iterator
		itrExistingFibObjectInfo = mapFibObjectInfos.find( ulIdentifier );
	
	if ( itrExistingFibObjectInfo == mapFibObjectInfos.end() ) {
		//Fib object info object dos not exists -> insert it
		mapFibObjectInfos.insert( pair< unsigned long , cFibObjectInfo * >(
			ulIdentifier, pFibObjectInfoToInsert ) );
	}else{//identifier for Fib object info object exists -> remove old and add new
		cFibObjectInfo * pExistingFibObjectInfo =
			itrExistingFibObjectInfo->second;
		if ( pExistingFibObjectInfo != NULL ) {
			//delete old Fib object info object
			setFibObjectInfos.erase( pExistingFibObjectInfo );
			pExistingFibObjectInfo->unregisterFibObjectInfoChangeListener( this );
			delete pExistingFibObjectInfo;
		}
		itrExistingFibObjectInfo->second = pFibObjectInfoToInsert;
	}
	setFibObjectInfos.insert( pFibObjectInfoToInsert );
	pFibObjectInfoToInsert->registerFibObjectInfoChangeListener( this );
	//add possible categories of new Fib object (info)
	addPossibleCategories( pFibObjectInfoToInsert->getCategories() );
	
	if ( ulIdentifier == ulFirstFreeIdentifier ) {
		//search for next free identifier
		ulFirstFreeIdentifier = 1;
		for ( map< unsigned long , cFibObjectInfo * >::const_iterator
				itrFibObjectInfo = mapFibObjectInfos.begin();
				itrFibObjectInfo != mapFibObjectInfos.end();
				++itrFibObjectInfo, ++ulFirstFreeIdentifier ) {
			
			if ( itrFibObjectInfo->first != ulFirstFreeIdentifier ) {
				//ulFirstFreeIdentifier not used -> first not used found
				break;
			}
		}
	}//end if search for next free identifier
	//add to sorted Fib object info objects
	addToUsedTimeSortedFibObjectInfos( pFibObjectInfoToInsert );
	
	mutexFibObjectInfoHandler.unlock();
	
	//write Fib object info object to disk
	storeFibInfoObject( pFibObjectInfoToInsert );
	
	return true;
}


//TODO check


/**
 * This method will remove the Fib object info object with the given
 * identifier from this handler.
 * Note: It will be also deleted from the memory.
 *
 * @see mapFibObjectInfos
 * @see setFibObjectInfos
 * @see addFibObjectInfo()
 * @return true if a Fib object info object was removed else false
 */
bool cFibObjectInfoHandler::removeFibObjectInfo( const unsigned long ulIdentifier ) {
	
	mutexFibObjectInfoHandler.lock();
	
	std::map< unsigned long , cFibObjectInfo * >::iterator
		itrFibObjectInfo = mapFibObjectInfos.find( ulIdentifier );
	
	if ( itrFibObjectInfo == mapFibObjectInfos.end() ) {
		//no such Fib object info object -> nothing to remove
		mutexFibObjectInfoHandler.unlock();
		return false;
	}//Fib object info object for identifer exists
	
	if ( itrFibObjectInfo->first < ulFirstFreeIdentifier ) {
		/*the identifer of the to remove Fib object info object is before the
		 first free identifier*/
		ulFirstFreeIdentifier = itrFibObjectInfo->first;
	}
	cFibObjectInfo * pRemovedFibObjectInfo = itrFibObjectInfo->second;
	
	if ( pRemovedFibObjectInfo != NULL ) {
		//delete removed Fib object info from hard drive, if its source is not valid
		cFibObjectSource * pFibObjectSource =
			pRemovedFibObjectInfo->getFibObjectSource();
		if ( ( pFibObjectSource == NULL ) ||
				( ! pFibObjectSource->checkSource() ) ) {
			//original Fib object dosn't exists anymore
			QDir dirFibObjectInfos = QDir( QString( szPathToFibObjectInfos ) );
			
			std::map< unsigned long , string >::const_iterator
				itrFileName = mapFibObjectInfoFiles.find(
					pRemovedFibObjectInfo->getIdentifier() );
			if ( itrFileName != mapFibObjectInfoFiles.end() ) {
				//delete file
				dirFibObjectInfos.remove( QString( itrFileName->second.c_str() ) );
			}
		}
		//Fib object info object was loaded -> delete it
		setFibObjectInfos.erase( pRemovedFibObjectInfo );
		pRemovedFibObjectInfo->unregisterFibObjectInfoChangeListener( this );
		delete pRemovedFibObjectInfo;
	}
	mapFibObjectInfos.erase( itrFibObjectInfo );
	//remove from sorted Fib object info objects
	removeFromUsedTimeSortedFibObjectInfos( pRemovedFibObjectInfo );
	
	mutexFibObjectInfoHandler.unlock();
	
	return true;
}


/**
 * @return the next identifier not used by a Fib object info object
 * 	@see ulFirstFreeIdentifier
 */
unsigned long cFibObjectInfoHandler::getNextFreeIdentifier() const {
	
	return ulFirstFreeIdentifier;
}


/**
 * This method returns the string for the path to the Fib object info
 * objects of this database.
 *
 * @see loadListOfInfoObjects()
 * @see loadFibInfoObject()
 * @see storeFibInfoObject()
 * @return the string for the path to the Fib object info objects
 */
char * cFibObjectInfoHandler::getFibObjectInfoPath() const {
	
	/* Fib object info folder:
	 * - store it in settings (settings object QSettings)
	 * -- linux ~/.fibCreator/fibObjectInfo/
	 * -- windows: subfolder of application path + /fibObjectInfo/
	 */
	QSettings settings("Fib development", "Fib creator");
	QString szPathFibObjectInfo =
		settings.value("objectInfoHandler/pathFibObjectInfo",
#ifdef WINDOWS
			QString( QDir::homePath() + "/fibCreator/fibObjectInfo/" )
#else //WINDOWS
			//linux
			QString( QDir::homePath() + "/.fibCreator/fibObjectInfo/" )
#endif //WINDOWS
		).toString();
	
	//if not existing create path
	QDir().mkpath( szPathFibObjectInfo );
	
	//copy path into char *
	char * pPathFibObjectInfo = new char[ szPathFibObjectInfo.size() + 1 ] ;
	
	strcpy( pPathFibObjectInfo, szPathFibObjectInfo.toStdString().c_str() );
	
	return pPathFibObjectInfo;
}


/**
 * This method loads a list of all existing Fib object info identifiers
 * into the mapFibObjectInfos .
 *
 * @see getFibObjectInfoPath()
 * @see mapFibObjectInfos
 * @return true if a Fib object info object list could be loaded, else false
 */
bool cFibObjectInfoHandler::loadListOfInfoObjects() {
	
	QDir dirFibObjectInfos = QDir( QString( szPathToFibObjectInfos ) );
	
	if ( ! dirFibObjectInfos.exists() ) {
		//no such directory
		if ( ! QDir().mkpath( szPathToFibObjectInfos ) ) {
			//can't create directory
			return false;
		}//can create directory -> directory exists
		dirFibObjectInfos = QDir( QString( szPathToFibObjectInfos ) );
	}
	//get the names of the Fib object infos files
	QStringList filtersFibObjectInfoFiles;
	filtersFibObjectInfoFiles << "id*.xml"  << "id*.FIB" << "id*.XML"<<
		"ID*.fib" << "ID*.xml"  << "ID*.FIB" << "ID*.XML";
	
	const QStringList liFibObjectInfoFiles = dirFibObjectInfos.entryList(
		filtersFibObjectInfoFiles, (QDir::Files | QDir::Readable) , QDir::Name );
	
	mutexFibObjectInfoHandler.lock();
	//delete the old Fib object info entries
	for ( set< cFibObjectInfo * >::iterator
			itrFibObjectInfo = setFibObjectInfos.begin();
			itrFibObjectInfo != setFibObjectInfos.end(); ++itrFibObjectInfo ) {
		
		(*itrFibObjectInfo)->unregisterFibObjectInfoChangeListener( this );
		delete (*itrFibObjectInfo);
	}
	setFibObjectInfos.clear();
	mapFibObjectInfos.clear();
	setPossibleCategories.clear();
	
	DEBUG_OUT_L2(<<"cFibObjectInfoHandler("<<this<<")::loadListOfInfoObjects() extract the new entries form the Fib object info in there directory ("<<szPathToFibObjectInfos<<"):"<<endl<<flush);
	//extract the new entries form the Fib object info in there directory
	QStringList::const_iterator constIterator;
	const QString szOStringPath( szPathToFibObjectInfos );
	for ( QStringList::const_iterator
			itrFibObjectInfoFile = liFibObjectInfoFiles.constBegin();
			itrFibObjectInfoFile != liFibObjectInfoFiles.constEnd();
			++itrFibObjectInfoFile ) {
		DEBUG_OUT_L2(<<"   loading info: \""<<itrFibObjectInfoFile->toStdString()<<"\" (\""<<( szOStringPath + (*itrFibObjectInfoFile) ).toStdString()<<"\" number: "<<itrFibObjectInfoFile->mid( 2 ).toStdString()<<")"<<endl<<flush);
		//read the identifer (behind the "id part")
		const unsigned long ulIdentifier = toUnsignedLong(
			itrFibObjectInfoFile->mid( 2 ).toStdString().c_str() );
		//load the Fib object info object
		ifstream streamIn( ( szOStringPath + (*itrFibObjectInfoFile) ).
			toStdString().c_str() );
	
		int iOutStatus = 0;
		cFibObjectInfo * pLoadedFibInfoObject =
			cFibObjectInfo::restore( streamIn, &iOutStatus );
		
		if ( ( iOutStatus < 0 ) || ( pLoadedFibInfoObject == NULL ) ) {
			//Error while loading -> invalid file -> check next file
			if ( pLoadedFibInfoObject ) {
				delete pLoadedFibInfoObject;
			}
			continue;
		}//else Fib object infor object could be loaded -> add it to members
		//insert loaded Fib object info object
		setFibObjectInfos.insert( pLoadedFibInfoObject );
		pLoadedFibInfoObject->registerFibObjectInfoChangeListener( this );
		mapFibObjectInfos.insert( pair<unsigned long , cFibObjectInfo *>(
			ulIdentifier, pLoadedFibInfoObject ) );
		//add possible categories of new Fib object (info)
		addPossibleCategories( pLoadedFibInfoObject->getCategories() );
		//add to sorted Fib object info objects
		addToUsedTimeSortedFibObjectInfos( pLoadedFibInfoObject );
		
		mapFibObjectInfoFiles.insert( pair< unsigned long , string >(
			ulIdentifier, itrFibObjectInfoFile->toStdString() ) );
		
	}//end for all files in the folder
	//find the first free identifier
	
	ulFirstFreeIdentifier = 1;
	for ( map< unsigned long , cFibObjectInfo * >::const_iterator
			itrFibObjectInfo = mapFibObjectInfos.begin();
			itrFibObjectInfo != mapFibObjectInfos.end();
			++itrFibObjectInfo, ++ulFirstFreeIdentifier ) {
		
		if ( itrFibObjectInfo->first != ulFirstFreeIdentifier ) {
			//ulFirstFreeIdentifier not used -> first not used found
			break;
		}
	}
	
	mutexFibObjectInfoHandler.unlock();
	
	return true;
}



/**
 * This method checks if for the Fib object database the Fib object infos
 * for this handler where created.
 * (This method returns true if the file:
 * 	szPathToFibObjectInfos"fibDbInfosCreated.flg" exists.)
 *
 * @see loadFibDatabase()
 * @return true if the Fib object database identifers for this
 * 	handler where created, else false
 */
bool cFibObjectInfoHandler::checkFibDbIdsExist() const {
	
	QString szFibDatabaseFlagFileName( szPathToFibObjectInfos );
	szFibDatabaseFlagFileName.append( "fibDbInfosCreated.flg" );
	
	const QFile fibDatabaseFlagFile( szFibDatabaseFlagFileName );
	return fibDatabaseFlagFile.exists();
}


/**
 * This method creates for all Fib database objects new Fib object
 * info objects (with their own Fib object info identifiers).
 *
 * @see checkFibDbIdsExist
 * @return true if the Fib object infos for the Fib database objects
 * 	could be created, else false
 */
bool cFibObjectInfoHandler::loadFibDatabase() {
	
	DEBUG_OUT_L2(<<"cFibObjectInfoHandler("<<this<<")::loadFibDatabase() started"<<endl<<flush);
	
	cFibDatabase * pFibDatabase = cFibDatabase::getInstance();
	if ( pFibDatabase == NULL ) {
		//no Fib database to load
		return false;
	}
	const list< longFib > liAllFibDbIdentifiers =
		pFibDatabase->getAllDatabaseObjectIdentifiers();
	if ( liAllFibDbIdentifiers.empty() ) {
		//no Fib database objects to load -> all created
		return true;
	}
	

//TODO check fast

	mutexFibObjectInfoHandler.lock();
	mutexUsedTimeSortedFibObjectInfos.lock();
	stack< cFibObjectInfo* > stackFibObjectInfosToStore;
	cFibObjectInfo * pFibDbObjectInfo;
	for ( list< longFib >::const_iterator
			itrDbIdentifier = liAllFibDbIdentifiers.begin();
			itrDbIdentifier != liAllFibDbIdentifiers.end();
			++itrDbIdentifier ) {
		//create Fib object info for Fib database object
		const cFibObjectSourceFibDb fibDbSource( *itrDbIdentifier );
		pFibDbObjectInfo = new cFibObjectInfo(
			ulFirstFreeIdentifier, &fibDbSource, false );
		
		//insert Fib object info object
		pair< map< unsigned long , cFibObjectInfo * >::iterator, bool>
			paInsertPosition =
				mapFibObjectInfos.insert( pair< unsigned long , cFibObjectInfo * >(
					ulFirstFreeIdentifier, pFibDbObjectInfo ) );
		if ( ! paInsertPosition.second ) {
			/*Fib object info object for database object could not be inserted
			 -> skip it*/
			delete pFibDbObjectInfo;
			continue;
		}
		
		setFibObjectInfos.insert( pFibDbObjectInfo );
		//add possible categories of new Fib object (info)
		addPossibleCategories( pFibDbObjectInfo->getCategories() );
		
		//evalue next free identifier
		map< unsigned long , cFibObjectInfo * >::const_iterator
			itrFibObjectInfo = paInsertPosition.first;
		++itrFibObjectInfo;
		++ulFirstFreeIdentifier;
		for ( ; itrFibObjectInfo != mapFibObjectInfos.end();
				++itrFibObjectInfo, ++ulFirstFreeIdentifier ) {
			
			if ( itrFibObjectInfo->first != ulFirstFreeIdentifier ) {
				//ulFirstFreeIdentifier not used -> first not used found
				break;
			}
		}
		//add to sorted Fib object info objects
		addToUsedTimeSortedFibObjectInfos( pFibDbObjectInfo, false );
		
		//store Fib object infos to store to disk (evade mutexFibObjectInfoHandler lock)
		stackFibObjectInfosToStore.push( pFibDbObjectInfo );
	}//end for all Fib database object identifiers
	mutexUsedTimeSortedFibObjectInfos.unlock();
	mutexFibObjectInfoHandler.unlock();
	//write all Fib object info object to disk
	bool bAllFibObjectsStored = true;
	unsigned long ulStoredDbFibObjects = 0;
	while ( ! stackFibObjectInfosToStore.empty() ) {
		pFibDbObjectInfo = stackFibObjectInfosToStore.top();
		stackFibObjectInfosToStore.pop();
		//extract info for Fib object info
		pFibDbObjectInfo->loadFibObjectFromSource();
		pFibDbObjectInfo->extractInfoFromLoadedFibObject();
		//write Fib object info object to disk
		if ( storeFibInfoObject( pFibDbObjectInfo ) ) {
			//Fib object info for Fib database object stored
			ulStoredDbFibObjects++;
		} else {
			bAllFibObjectsStored = false;
		}
		pFibDbObjectInfo->registerFibObjectInfoChangeListener( this );
	}
	if ( 0 < ulStoredDbFibObjects ) {
		//some Fib database objects stored -> set Fib database infos created flag
		QString szFibDatabaseFlagFileName( szPathToFibObjectInfos );
		szFibDatabaseFlagFileName.append( "fibDbInfosCreated.flg" );
		
		QFile fibDatabaseFlagFile( szFibDatabaseFlagFileName );
		
		fibDatabaseFlagFile.open( QIODevice::WriteOnly );
		QString szFlagText;
		szFlagText.setNum( ulStoredDbFibObjects );
		szFlagText.append(" Fib object info objects for Fib database objects created");
		fibDatabaseFlagFile.write( szFlagText.toStdString().c_str(), szFlagText.size() );
		fibDatabaseFlagFile.close();
	}
	
	return bAllFibObjectsStored;
}

//TODO check fast end




/**
 * This method loads the Fib object info object for the given identifier.
 * It stores the result into mapFibObjectInfos .
 *
 * @see getFibObjectInfoPath()
 * @see loadFibInfoObject()
 * @see mapFibObjectInfos
 * @see loadListOfInfoObjects()
 * @param ulIdentifier the identifier of the Fib object info object to load
 * @return true if the Fib object info object could be loaded, else false
 */
cFibObjectInfo * cFibObjectInfoHandler::loadFibInfoObject(
		const unsigned long ulIdentifier ) {
	
	mutexFibObjectInfoHandler.lock();
	
	if ( szPathToFibObjectInfos == NULL ) {
		//no path where the Fib object info are stored
		mutexFibObjectInfoHandler.unlock();
		return NULL;
	}
	
	std::map< unsigned long , string >::const_iterator
		itrFibInfoObjectFile = mapFibObjectInfoFiles.find( ulIdentifier );
	if ( itrFibInfoObjectFile == mapFibObjectInfoFiles.end() ) {
		//no file for the Fib object info object for the given identifier
		mutexFibObjectInfoHandler.unlock();
		return NULL;
	}//else load Fib object info object
	
	const string strFilePath(
		szPathToFibObjectInfos + (itrFibInfoObjectFile->second) );
	
	mutexFibObjectInfoHandler.unlock();
	
	ifstream streamIn( strFilePath.c_str() );
	
	int iOutStatus = 0;
	cFibObjectInfo * pLoadedFibInfoObject =
		cFibObjectInfo::restore( streamIn, &iOutStatus );
	
	if ( ( iOutStatus < 0 ) || ( pLoadedFibInfoObject == NULL ) ) {
		//Error while loading
		if ( pLoadedFibInfoObject ) {
			delete pLoadedFibInfoObject;
		}
		return NULL;
	}
	
	return pLoadedFibInfoObject;
}


/**
 * This method stores the given Fib object info object to the disk into
 * the Fib object info object folder.
 *
 * @see getFibObjectInfoPath()
 * @see storeFibInfoObject()
 * @see mapFibObjectInfos
 * @see loadListOfInfoObjects()
 * @param pFibObjectInfo Fib object info object to store
 * @return true if the Fib object info object could be stored else false
 */
bool cFibObjectInfoHandler::storeFibInfoObject( cFibObjectInfo * pFibObjectInfo ) {
	
	if ( pFibObjectInfo == NULL ) {
		//nothing to store
		return false;
	}
	
	mutexFibObjectInfoHandler.lock();
	if ( szPathToFibObjectInfos == NULL ) {
		//no path where the Fib object info are stored
		mutexFibObjectInfoHandler.unlock();
		return false;
	}
	
	string strFilePath;
	std::map< unsigned long , string >::const_iterator
		itrFibInfoObjectFile = mapFibObjectInfoFiles.find(
			pFibObjectInfo->getIdentifier() );
	if ( itrFibInfoObjectFile == mapFibObjectInfoFiles.end() ) {
		/*no file for the Fib object info object for the given identifier
		-> create one*/
		char szFileNameBuffer[ 32 ];
		const unsigned long ulIdentifier = pFibObjectInfo->getIdentifier();
		sprintf( szFileNameBuffer, "id%09lu.xml", ulIdentifier );
		
		mapFibObjectInfoFiles.insert( pair< unsigned long , string >(
			ulIdentifier, (string(szFileNameBuffer)) ) );
		strFilePath = ((string)(szPathToFibObjectInfos)) + szFileNameBuffer;
	}else{//use existing path
		strFilePath = szPathToFibObjectInfos + (itrFibInfoObjectFile->second);
	}
	//load Fib object info object
	mutexFibObjectInfoHandler.unlock();
	
	ofstream streamOut( strFilePath.c_str() );
	
	return pFibObjectInfo->store( streamOut );
}

//TODO check

/**
 * This method returns a sorted list of Fib object info objects.
 * All Fib object info objects are sorted in an order according to the
 * times they where used. In which recently used times have a higher weight.
 * The Fib object info objects with the higher sum of weights (for their
 * used times) will be before the Fib object info objects with the lower
 * sum of weights.
 *
 * @see cFibObjectInfo::getLastUsedTimes()
 * @see getLastUsedTimesWeight()
 * @see mapUsedTimeSortedFibObjectInfos
 * @param ulLast the number of the last Fib object info object of all
 * 	sorted Fib object info objects to return (counting starts with 1 )
 * 	or 0 if all should be returned
 * @param ulFirst the number of the first Fib object info object of all
 * 	sorted Fib object info objects to return (counting starts with 1 );
 * 	All Fib object info object from the ulFirst'th (including) to the
 * 	ulLast'th  (including) will be returned
 * @return a "last used time" sorted list of Fib object info objects
 */
list< cFibObjectInfo * > cFibObjectInfoHandler::getSortedFibObjectInfos(
	const unsigned long ulLast, const unsigned long ulFirst ) {
	
	DEBUG_OUT_L2(<<"cFibObjectInfoHandler("<<this<<")::getSortedFibObjectInfos( ulLast="<<ulLast<<", ulFirst="<<ulFirst<<") started"<<endl<<flush);
	
	list< cFibObjectInfo * > liSortedFibObjectInfos;
#ifdef FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
	mutexUsedTimeSortedFibObjectInfos.lock();
	if ( bReevaluateMapCategoryUsedTimeSortedFibObjectInfos ) {
		evaluateMapCategoryUsedTimeSortedFibObjectInfos();
	}
	//get for category sorted Fib object info vector
	std::vector< cFibObjectInfo * > & vecFibObjectInfoForCategory =
		mapCategoryUsedTimeSortedFibObjectInfos[ getCategoryForAll() ];
	//get Fib object infos of category from ulFirst till ulLast
	const unsigned int uiFirstIndex = ( 0 < ulFirst ) ? ( ulFirst - 1 ) : 0;
	const unsigned int uiLastIndex =
		( ( vecFibObjectInfoForCategory.size() <= ulLast ) || ( ulLast == 0 ) ) ?
			( vecFibObjectInfoForCategory.size() - 1 ) : ( ulLast - 1 );
	for ( unsigned int uiIndex = uiFirstIndex; uiIndex <= uiLastIndex; ++uiIndex ) {
		
		liSortedFibObjectInfos.push_back(
			vecFibObjectInfoForCategory[ uiIndex ] );
	}
#else //FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
	unsigned long ulActualPosition = 1;
	//go to the first Fib object info to return
	mutexUsedTimeSortedFibObjectInfos.lock();
	std::multimap< double , cFibObjectInfo * >::iterator itrFibObjectInfo;
	for ( itrFibObjectInfo = mapUsedTimeSortedFibObjectInfos.begin();
			( ulActualPosition < ulFirst ) &&
			( itrFibObjectInfo != mapUsedTimeSortedFibObjectInfos.end() );
			++itrFibObjectInfo, ++ulActualPosition ) {
		//nothing to do
	}
	if ( 0 < ulLast ) {
		//return Fib object infos till ulLast (including)
		for ( ; ( ulActualPosition <= ulLast ) &&
				( itrFibObjectInfo != mapUsedTimeSortedFibObjectInfos.end() );
				++itrFibObjectInfo, ++ulActualPosition ) {
			//add to return list
			liSortedFibObjectInfos.push_back( itrFibObjectInfo->second );
		}
	}else{//return all Fib object infors
		for ( ; itrFibObjectInfo != mapUsedTimeSortedFibObjectInfos.end();
				++itrFibObjectInfo ) {
			//add to return list
			liSortedFibObjectInfos.push_back( itrFibObjectInfo->second );
		}
	}
#endif //FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
	mutexUsedTimeSortedFibObjectInfos.unlock();
	DEBUG_OUT_L2(<<"cFibObjectInfoHandler("<<this<<")::getSortedFibObjectInfos( ulLast="<<ulLast<<", ulFirst="<<ulFirst<<") done returning "<<liSortedFibObjectInfos.size()<<" Fib object infos"<<endl<<flush);
	return liSortedFibObjectInfos;
}


/**
 * This method returns a sorted list of identifiers of Fib object info objects.
 * All Fib object info objects are sorted in an order according to the
 * times they where used. In which recently used times have a higher weight.
 * The Fib object info objects with the higher sum of weights (for their
 * used times) will be before the Fib object info objects with the lower
 * sum of weights.
 *
 * @see cFibObjectInfo::getLastUsedTimes()
 * @see getLastUsedTimesWeight()
 * @see mapUsedTimeSortedFibObjectInfos
 * @param ulLast the number of the last Fib object info object of all
 * 	sorted Fib object info objects to return (counting starts with 1 )
 * 	or 0 if all should be returned
 * @param ulFirst the number of the first Fib object info object of all
 * 	sorted Fib object info objects to return (counting starts with 1 );
 * 	All Fib object info object from the ulFirst'th (including) to the
 * 	ulLast'th  (including) will be returned
 * @return a "last used time" sorted list of identifiers of Fib object
 * 	info objects
 */
list< unsigned long > cFibObjectInfoHandler::getSortedFibObjectInfoIds(
		const unsigned long ulLast, const unsigned long ulFirst ) {
	
	DEBUG_OUT_L2(<<"cFibObjectInfoHandler("<<this<<")::getSortedFibObjectInfoIds( ulLast="<<ulLast<<", ulFirst="<<ulFirst<<") started"<<endl<<flush);
	
#ifdef FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
	return getSortedFibObjectInfoIdsForCategory(
		getCategoryForAll(), ulLast, ulFirst );
#else //FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
	unsigned long ulActualPosition = 1;
	list< unsigned long > liSortedFibObjectInfos;
	//go to the first Fib object info to return
	mutexUsedTimeSortedFibObjectInfos.lock();
	std::multimap< double , cFibObjectInfo * >::iterator itrFibObjectInfo;
	for ( itrFibObjectInfo = mapUsedTimeSortedFibObjectInfos.begin();
			( ulActualPosition < ulFirst ) &&
			( itrFibObjectInfo != mapUsedTimeSortedFibObjectInfos.end() );
			++itrFibObjectInfo, ++ulActualPosition ) {
		//nothing to do
	}
	if ( 0 < ulLast ) {
		//return Fib object infos till ulLast (including)
		for ( ; ( ulActualPosition <= ulLast ) &&
				( itrFibObjectInfo != mapUsedTimeSortedFibObjectInfos.end() );
				++itrFibObjectInfo, ++ulActualPosition ) {
			//add to return list
			if ( itrFibObjectInfo->second ) {
				liSortedFibObjectInfos.push_back(
					itrFibObjectInfo->second->getIdentifier() );
			}
		}
	}else{//return all Fib object infors
		for ( ; itrFibObjectInfo != mapUsedTimeSortedFibObjectInfos.end();
				++itrFibObjectInfo ) {
			//add to return list
			if ( itrFibObjectInfo->second ) {
				liSortedFibObjectInfos.push_back(
					itrFibObjectInfo->second->getIdentifier() );
			}
		}
	}//end if till end
	mutexUsedTimeSortedFibObjectInfos.unlock();
	DEBUG_OUT_L2(<<"cFibObjectInfoHandler("<<this<<")::getSortedFibObjectInfoIds( ulLast="<<ulLast<<", ulFirst="<<ulFirst<<") done returning "<<liSortedFibObjectInfos.size()<<" Fib object infos"<<endl<<flush);
	return liSortedFibObjectInfos;
#endif //FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
}


/**
 * This method returns a sorted list of identifiers of Fib object info
 * objects of a given cateory.
 * All Fib object info objects are sorted in an order according to the
 * times they where used. In which recently used times have a higher weight.
 * The Fib object info objects with the higher sum of weights (for their
 * used times) will be before the Fib object info objects with the lower
 * sum of weights.
 * All returned Fib object info objects will be in the given category.
 *
 * @see cFibObjectInfo::getLastUsedTimes()
 * @see cFibObjectInfo::setInCategories
 * @see getLastUsedTimesWeight()
 * @see mapUsedTimeSortedFibObjectInfos
 * @see setPossibleCategories
 * @see getPossibleCategories()
 * @param szCategory the category all returned Fib object infos should be in
 * @param ulLast the number of the last Fib object info object of all
 * 	sorted Fib object info objects of the category to return
 * 	(counting starts with 1 ) or 0 if all should be returned
 * @param ulFirst the number of the first Fib object info object of all
 * 	sorted Fib object info objects of the category to return
 * 	(counting starts with 1 );
 * 	All Fib object info object from the ulFirst'th (including) to the
 * 	ulLast'th  (including) will be returned
 * @return a "last used time" sorted list of identifiers of Fib object
 * 	info objects
 */
list< unsigned long > cFibObjectInfoHandler::getSortedFibObjectInfoIdsForCategory(
		const std::string & szCategory,
		const unsigned long ulLast, const unsigned long ulFirst ) {
	
	DEBUG_OUT_L2(<<"cFibObjectInfoHandler("<<this<<")::getSortedFibObjectInfoIdsForCategory( szCategory=\""<<szCategory<<"\", ulLast="<<ulLast<<", ulFirst="<<ulFirst<<") started"<<endl<<flush);
	
//TODO check
	list< unsigned long > liSortedFibObjectInfos;
#ifdef FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
	mutexUsedTimeSortedFibObjectInfos.lock();
	if ( bReevaluateMapCategoryUsedTimeSortedFibObjectInfos ) {
		evaluateMapCategoryUsedTimeSortedFibObjectInfos();
	}
	//get for category sorted Fib object info vector
	std::vector< cFibObjectInfo * > & vecFibObjectInfoForCategory =
		mapCategoryUsedTimeSortedFibObjectInfos[ szCategory ];
	//get Fib object infos of category from ulFirst till ulLast
	const unsigned int uiFirstIndex = ( 0 < ulFirst ) ? ( ulFirst - 1 ) : 0;
	const unsigned int uiLastIndex =
		( ( vecFibObjectInfoForCategory.size() <= ulLast ) || ( ulLast == 0 ) ) ?
			( vecFibObjectInfoForCategory.size() - 1 ) : ( ulLast - 1 );
	for ( unsigned int uiIndex = uiFirstIndex; uiIndex <= uiLastIndex; ++uiIndex ) {
		
		liSortedFibObjectInfos.push_back(
			vecFibObjectInfoForCategory[ uiIndex ]->getIdentifier() );
	}
	
#else //FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
	if ( szCategory == getCategoryForAll() ) {
		//category for return all Fib object infos
		return getSortedFibObjectInfoIds( ulLast, ulFirst );
	}//else don't return all
	unsigned long ulActualPosition = 0;
	//go to the first Fib object info to return
	std::multimap< double , cFibObjectInfo * >::iterator itrFibObjectInfo;
	mutexUsedTimeSortedFibObjectInfos.lock();
	for ( itrFibObjectInfo = mapUsedTimeSortedFibObjectInfos.begin();
			( ulActualPosition < ulFirst ) &&
			( itrFibObjectInfo != mapUsedTimeSortedFibObjectInfos.end() );
			++itrFibObjectInfo ) {
		
		const std::set< std::string > setFibObjectInfoCategories =
			itrFibObjectInfo->second->getCategories();
		if ( setFibObjectInfoCategories.find( szCategory ) !=
				setFibObjectInfoCategories.end() ) {
			//Fib object info object for category found
			++ulActualPosition;
		}//else Fib object info object not for category -> skip it
	}
	if ( 0 < ulLast ) {
		//return Fib object infos till ulLast (including)
		for ( ; ( ulActualPosition <= ulLast ) &&
				( itrFibObjectInfo != mapUsedTimeSortedFibObjectInfos.end() );
				++itrFibObjectInfo ) {
			
			const std::set< std::string > setFibObjectInfoCategories =
				itrFibObjectInfo->second->getCategories();
			if ( setFibObjectInfoCategories.find( szCategory ) !=
					setFibObjectInfoCategories.end() ) {
				//Fib object info object for category found
				++ulActualPosition;
				//add to return list
				if ( itrFibObjectInfo->second ) {
					liSortedFibObjectInfos.push_back(
						itrFibObjectInfo->second->getIdentifier() );
				}
			}//else Fib object info object not for category -> skip it
		}
	}else{//return all Fib object infors
		for ( ; itrFibObjectInfo != mapUsedTimeSortedFibObjectInfos.end();
				++itrFibObjectInfo ) {
			const std::set< std::string > setFibObjectInfoCategories =
				itrFibObjectInfo->second->getCategories();
			if ( setFibObjectInfoCategories.find( szCategory ) !=
					setFibObjectInfoCategories.end() ) {
				/*Fib object info object for category found
				  -> add to return list*/
				if ( itrFibObjectInfo->second ) {
					liSortedFibObjectInfos.push_back(
						itrFibObjectInfo->second->getIdentifier() );
				}
			}//else Fib object info object not for category -> skip it
		}
	}//end if till end
#endif //FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
	mutexUsedTimeSortedFibObjectInfos.unlock();
	
	DEBUG_OUT_L2(<<"cFibObjectInfoHandler("<<this<<")::getSortedFibObjectInfoIdsForCategory( szCategory=\""<<szCategory<<"\", ulLast="<<ulLast<<", ulFirst="<<ulFirst<<") done returning "<<liSortedFibObjectInfos.size()<<" Fib object infos"<<endl<<flush);
	return liSortedFibObjectInfos;
}


/**
 * This method returns number of a sorted Fib object info objects in the
 * given cateory.
 * All Fib object info objects are sorted in an order according to the
 * times they where used. In which recently used times have a higher weight.
 * The Fib object info objects with the higher sum of weights (for their
 * used times) will be before the Fib object info objects with the lower
 * sum of weights.
 * All counted Fib object info objects will be in the given category.
 *
 * @see getSortedFibObjectInfoIdsForCategory()
 * @see cFibObjectInfo::getLastUsedTimes()
 * @see cFibObjectInfo::setInCategories
 * @see getLastUsedTimesWeight()
 * @see mapUsedTimeSortedFibObjectInfos
 * @see setPossibleCategories
 * @see getPossibleCategories()
 * @param szCategory the category all counted Fib object infos should be in
 * @return the number of Fib object infos in the "last used time" sorted
 * 	list of Fib object info objects of the given category
 */
unsigned long cFibObjectInfoHandler::getNumberOfSortedFibObjectInfoIdsForCategory(
		const std::string & szCategory ){
	
#ifdef FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
	mutexUsedTimeSortedFibObjectInfos.lock();
	if ( bReevaluateMapCategoryUsedTimeSortedFibObjectInfos ) {
		evaluateMapCategoryUsedTimeSortedFibObjectInfos();
	}
	const unsigned long ulFibElementsForCategory =
		mapCategoryUsedTimeSortedFibObjectInfos[ szCategory ].size();
	mutexUsedTimeSortedFibObjectInfos.unlock();
	DEBUG_OUT_L2(<<"cFibObjectInfoHandler("<<this<<")::getNumberOfSortedFibObjectInfoIdsForCategory( szCategory=\""<<szCategory<<"\" ) done returning "<<ulFibElementsForCategory<<endl<<flush);
	return ulFibElementsForCategory;
#else //FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
	return getSortedFibObjectInfoIdsForCategory( szCategory ).size();
#endif //FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
}
//TODO check end

/**
 * This method sorts the list of identifiers of Fib object info objects.
 * All Fib object info objects are sorted in an order according to the
 * times they where used. In which recently used times have a higher weight.
 * The Fib object info objects with the higher sum of weights (for their
 * used times) will be before the Fib object info objects with the lower
 * sum of weights.
 * Identifiers in the given list, for which no Fib object info handler in
 * this handler exists, will be ignored.
 *
 * @see cFibObjectInfo::getLastUsedTimes()
 * @see getLastUsedTimesWeight()
 * @see mapUsedTimeSortedFibObjectInfos
 * @param setFibObjectInfoIds the list of identifiers of Fib object info
 * 	objects to sort
 * @return a "last used time" sorted list of identifiers of Fib object
 * 	info objects
 */
list< unsigned long > cFibObjectInfoHandler::sortFibObjectInfoIds(
		const set< unsigned long > & setFibObjectInfoIds ) {
	
	const list< unsigned long > liIdentifier(
		setFibObjectInfoIds.begin(), setFibObjectInfoIds.end() );
	
	list< cFibObjectInfo * > liFibObjectInfos = sortFibObjectInfo(
		getFibObjectInfos( liIdentifier ) );
	
	//get the identifiers for the Fib object info objects
	list< unsigned long > liSortedFibObjectInfoIds;
	for ( list< cFibObjectInfo * >::iterator
			itrFibObjectInfo = liFibObjectInfos.begin();
			itrFibObjectInfo != liFibObjectInfos.end(); ++itrFibObjectInfo ) {
		
		liSortedFibObjectInfoIds.push_back(
			(*itrFibObjectInfo)->getIdentifier() );
	}
	
	return liSortedFibObjectInfoIds;
}


/**
 * This method sorts the list of Fib object info objects.
 * All Fib object info objects are sorted in an order according to the
 * times they where used. In which recently used times have a higher weight.
 * The Fib object info objects with the higher sum of weights (for their
 * used times) will be before the Fib object info objects with the lower
 * sum of weights.
 *
 * @see cFibObjectInfo::getLastUsedTimes()
 * @see getLastUsedTimesWeight()
 * @see mapUsedTimeSortedFibObjectInfos
 * @param setFibObjectInfos the set of of Fib object info objects to sort
 * @return a "last used time" sorted list of of Fib object info objects
 */
list< cFibObjectInfo * > cFibObjectInfoHandler::sortFibObjectInfo(
		const set< cFibObjectInfo * > & setFibObjectInfos ) const {
	//sort the Fib object infos with the help of a multimap
	multimap< double , cFibObjectInfo * > mapTmpUsedTimeSortedFibObjectInfos;
	for ( set< cFibObjectInfo * >::const_iterator
			itrFibObjectInfo = setFibObjectInfos.begin();
			itrFibObjectInfo != setFibObjectInfos.end(); ++itrFibObjectInfo ) {
		
		mapTmpUsedTimeSortedFibObjectInfos.insert( pair< double , cFibObjectInfo * >(
			getLastUsedTimesWeightSum( (*itrFibObjectInfo)->getLastUsedTimes() ),
			(*itrFibObjectInfo) ) );
	
		DEBUG_OUT_L2(<<"cFibObjectInfoHandler("<<this<<")::sortFibObjectInfo() add to sorted \""<<(*itrFibObjectInfo)->getFibObjectName()<<"\" with weight "<<getLastUsedTimesWeightSum( (*itrFibObjectInfo)->getLastUsedTimes() )<<endl<<flush);
	}
	//transfer the Fib object infos from the multimap into a list
	list< cFibObjectInfo * > liSortedFibObjectInfos;
	for ( multimap< double , cFibObjectInfo * > ::iterator
			itrFibObjectInfo = mapTmpUsedTimeSortedFibObjectInfos.begin();
			itrFibObjectInfo != mapTmpUsedTimeSortedFibObjectInfos.end();
			++itrFibObjectInfo ) {
		
		liSortedFibObjectInfos.push_front( itrFibObjectInfo->second );
	}
	
	return liSortedFibObjectInfos;
}


/**
 * This method sorts the list of Fib object info objects.
 * All Fib object info objects are sorted in an order according to the
 * times they where used. In which recently used times have a higher weight.
 * The Fib object info objects with the higher sum of weights (for their
 * used times) will be before the Fib object info objects with the lower
 * sum of weights.
 *
 * @see cFibObjectInfo::getLastUsedTimes()
 * @see getLastUsedTimesWeight()
 * @see mapUsedTimeSortedFibObjectInfos
 * @param liFibObjectInfos the list of of Fib object info objects to sort
 * @return a "last used time" sorted list of of Fib object info objects
 */
list< cFibObjectInfo * > cFibObjectInfoHandler::sortFibObjectInfo(
		const list< cFibObjectInfo * > & liFibObjectInfos ) const {
	//sort the Fib object infos with the help of a multimap
	multimap< double , cFibObjectInfo * > mapTmpUsedTimeSortedFibObjectInfos;
	for ( list< cFibObjectInfo * >::const_iterator
			itrFibObjectInfo = liFibObjectInfos.begin();
			itrFibObjectInfo != liFibObjectInfos.end(); ++itrFibObjectInfo ) {
		
		mapTmpUsedTimeSortedFibObjectInfos.insert( pair< double , cFibObjectInfo * >(
			getLastUsedTimesWeightSum( (*itrFibObjectInfo)->getLastUsedTimes() ),
			(*itrFibObjectInfo) ) );
	
		DEBUG_OUT_L2(<<"cFibObjectInfoHandler("<<this<<")::sortFibObjectInfo() add to sorted \""<<(*itrFibObjectInfo)->getFibObjectName()<<"\" with weight "<<getLastUsedTimesWeightSum( (*itrFibObjectInfo)->getLastUsedTimes() )<<endl<<flush);
	}
	//transfer the Fib object infos from the multimap into a list
	list< cFibObjectInfo * > liSortedFibObjectInfos;
	for ( multimap< double , cFibObjectInfo * > ::iterator
			itrFibObjectInfo = mapTmpUsedTimeSortedFibObjectInfos.begin();
			itrFibObjectInfo != mapTmpUsedTimeSortedFibObjectInfos.end();
			++itrFibObjectInfo ) {
		
		liSortedFibObjectInfos.push_front( itrFibObjectInfo->second );
	}
	
	return liSortedFibObjectInfos;
}


/**
 * This method updates the the sorted Fib object info objects.
 * If the "last used time" data of a Fib object info object changes
 * you can resort it with this method.
 *
 * @see mapUsedTimeSortedFibObjectInfos
 * @see getLastUsedTimesWeight()
 * @see getSortedFibObjectInfos()
 * @see getSortedFibObjectInfoIds()
 * @see sortFibObjectInfoIds()
 * @see sortFibObjectInfo()
 */
void cFibObjectInfoHandler::updateUsedTimeSortedFibObjectInfos() {
	
	mutexUsedTimeSortedFibObjectInfos.lock();
	//clear old mapUsedTimeSortedFibObjectInfos data
	mapUsedTimeSortedFibObjectInfos.clear();
#ifdef FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
	bReevaluateMapCategoryUsedTimeSortedFibObjectInfos = true;
#endif //FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
	
	mutexFibObjectInfoHandler.lock();
	//create mapUsedTimeSortedFibObjectInfos data
	for ( set< cFibObjectInfo * >::iterator
			itrFibObjectInfo = setFibObjectInfos.begin();
			itrFibObjectInfo != setFibObjectInfos.end(); ++itrFibObjectInfo ) {
		
		addToUsedTimeSortedFibObjectInfos( *itrFibObjectInfo, false );
	}//end for all Fib object info objects
	mutexFibObjectInfoHandler.unlock();
	mutexUsedTimeSortedFibObjectInfos.unlock();
}


/**
 * This method returns a set with the possible categories for the
 * Fib object info objects of this handler.
 * (e.g. isPointElement, isPerson)
 *
 * @see setPossibleCategories
 * @see addPossibleCategories()
 * @see mutexFibObjectInfoHandler
 * @see cFibObjectInfo::setInCategories
 * @return a set with the possible categories for the Fib object info
 * 	objects of this handler
 */
std::set< std::string > cFibObjectInfoHandler::getPossibleCategories() const {
	
	mutexFibObjectInfoHandler.lock();
	std::set< std::string > setRetPossibleCategories =
		setPossibleCategories;
	mutexFibObjectInfoHandler.unlock();
	
	setRetPossibleCategories.insert( getCategoryForAll() );//all is always a category
	return setRetPossibleCategories;
}


/**
 * This method returns a set with the possible categories for the
 * Fib object info objects of this handler.
 * (e.g. isPointElement, isPerson)
 * Note: The categories are returned as cFibObjectCategory objects.
 *
 * @see setPossibleCategories
 * @see addPossibleCategories()
 * @see mutexFibObjectInfoHandler
 * @see cFibObjectInfo::setInCategories
 * @return a set with the possible categories for the Fib object info
 * 	objects of this handler
 */
QList< cFibObjectCategory > cFibObjectInfoHandler::getPossibleFibObjectCategories() const {
	
	mutexFibObjectInfoHandler.lock();
	QList< cFibObjectCategory > liFibObjectCategories;
	/*Convert all categories of setPossibleCategories to cFibObjectCategory .
	 *Note: All categories of setPossibleCategories are absolute categories.*/
	for ( set< std::string >::const_iterator
			itrCategory = setPossibleCategories.begin();
			itrCategory != setPossibleCategories.end(); ++itrCategory ) {
		
		liFibObjectCategories.push_back(
			cFibObjectCategory( QString( itrCategory->c_str() ), true ) );
	}
	mutexFibObjectInfoHandler.unlock();
	//all is always a category
	liFibObjectCategories.push_front(
		cFibObjectCategory( QString( getCategoryForAll().c_str() ), true ) );
	return liFibObjectCategories;
}



/**
 * @return returns the category to get all Fib object info objects
 */
std::string cFibObjectInfoHandler::getCategoryForAll() {
	
	return (QObject::tr( "all" )).toStdString();
}


/**
 * Event method
 * This method will be called every time a Fib Fib object info object
 * (cFibObjectInfo), at which this object is registered, was changed.
 *
 * @see lFibObjectInfoChanged
 * @param pFibObjectInfoChanged a pointer to the event, with the information
 * 	about the changed Fib node
 */
void cFibObjectInfoHandler::fibObjectInfoChanged(
		const eFibObjectInfoChangedEvent * pFibObjectInfoChanged ) {
	
	if ( ( pFibObjectInfoChanged == NULL ) ||
			( pFibObjectInfoChanged->getFibObjectInfo() == NULL ) ) {
		//nothing changed
		return;
	}//else
	
	if ( pFibObjectInfoChanged->isDeleted() ) {
		//Fib object info was deleted -> remove itfrom members
		const cFibObjectInfo * pDeletedFibObjectInfo =
			pFibObjectInfoChanged->getFibObjectInfo();
		
		mutexFibObjectInfoHandler.lock();
		setFibObjectInfos.erase( const_cast<cFibObjectInfo *>(
			pDeletedFibObjectInfo ) );
		//remove from mapFibObjectInfos
		for ( map< unsigned long , cFibObjectInfo * >::iterator
				itrFibObjectInfo = mapFibObjectInfos.begin();
				itrFibObjectInfo != mapFibObjectInfos.end(); ++itrFibObjectInfo ) {
			
			if ( itrFibObjectInfo->second == pDeletedFibObjectInfo ) {
				//Fib object info found -> erase i
				mapFibObjectInfos.erase( itrFibObjectInfo );
				break;
			}
		}
		mutexFibObjectInfoHandler.unlock();
		//remove from map of sorted Fib object infos
		removeFromUsedTimeSortedFibObjectInfos( pDeletedFibObjectInfo );
		return;
	}//else
	cFibObjectInfo * pChangedFibObjectInfo = const_cast<cFibObjectInfo *>(
		pFibObjectInfoChanged->getFibObjectInfo() );
	
	mutexFibObjectInfoHandler.lock();
	addPossibleCategories( pChangedFibObjectInfo->getCategories() );
	mutexFibObjectInfoHandler.unlock();
	//update map of sorted Fib object infos
	removeFromUsedTimeSortedFibObjectInfos( pChangedFibObjectInfo );
	addToUsedTimeSortedFibObjectInfos( pChangedFibObjectInfo );
	
	//store changed Fib object infos
	storeFibInfoObject( pChangedFibObjectInfo );
}


/**
 * This method adds a set with categories to the set of the possible
 * categories for Fib object info objects of this handler.
 * (e.g. isPointElement, isPerson)
 * Note: This method will use no mutex.
 *
 * @see setPossibleCategories
 * @see getPossibleCategories()
 * @see cFibObjectInfo::setInCategories
 * @param setInPossibleCategories a set with the possible categories, for
 * 	the Fib object info objects of this handler, to add
 */
void cFibObjectInfoHandler::addPossibleCategories(
		const std::set< std::string >  & setInPossibleCategories ) {
	
	setPossibleCategories.insert( setInPossibleCategories.begin(),
		setInPossibleCategories.end() );
}



/**
 * This method returns the sum of weights for the given last used times.
 * All Fib object info object are sorted in an order according to the
 * times they where used. In which recently used times have a higher weight.
 * The Fib object info objects with the higher sum of weights (for their
 * used times) will be before the Fib object info objects with the lower
 * sum of weights.
 * This method will evalue and return the sum of weights.
 *
 * @see cFibObjectInfo::getLastUsedTimes()
 * @param vecLastUsedTimes the vector to the last used times information
 * 	for a Fib object info object
 * @return the sum of weights for the last used times
 */
double cFibObjectInfoHandler::getLastUsedTimesWeightSum(
		const vector< pair< time_t, unsigned long > > & vecLastUsedTimes ) {
	
	const time_t tmActual = time( NULL );
	double dWeightSum = 0;
	for ( vector< pair< time_t, unsigned long > >::const_iterator
			itrActualTimestamp = vecLastUsedTimes.begin();
			itrActualTimestamp != vecLastUsedTimes.end();
			itrActualTimestamp++ ) {
		
		if ( itrActualTimestamp->first == tmActual ) {
			/*time differnce is null -> below formular would be 1.0 / 0
			 *-> evalue ( 1.0 / ( exp( dMonth ) * dMonth )) for about 1 second*/
			dWeightSum += 80000000.0 * itrActualTimestamp->second;
			continue;
		}//else
		const double dMonth = ((double)( tmActual - itrActualTimestamp->first )) /
			2592000.0;//about seconds per mounth
		
		dWeightSum += ( 1.0 / ( exp( dMonth ) * dMonth )) *
			itrActualTimestamp->second;//number of uses
	}//end for all timestamps
	return dWeightSum;
}

//TODO check fast

/**
 * This method will add the given Fib object info object to the
 * "used time" sorted Fib object infos.
 * Note: It will not use the mutexFibObjectInfoHandler, so lock it
 * 	outside this method.
 * 	But will use the mutexUsedTimeSortedFibObjectInfos.
 *
 * @see mapUsedTimeSortedFibObjectInfos
 * @see mutexUsedTimeSortedFibObjectInfos
 * @param pFibObjectInfo the Fib object info object to add to the
 * 	"used time" sorted Fib object infos Fib object infos
 * @param bLock if true the mutexUsedTimeSortedFibObjectInfos will be
 * 	used (locked and unlocked)
 */
void cFibObjectInfoHandler::addToUsedTimeSortedFibObjectInfos(
		cFibObjectInfo * pFibObjectInfo, bool bLock ) {
	
	if ( bLock ) {
		mutexUsedTimeSortedFibObjectInfos.lock();
	}
	const double dLastUsedTimesWeightSum = getLastUsedTimesWeightSum(
		pFibObjectInfo->getLastUsedTimes() );
		
	mapUsedTimeSortedFibObjectInfos.insert( pair< double , cFibObjectInfo * >(
		dLastUsedTimesWeightSum, pFibObjectInfo ) );
#ifdef FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
	bReevaluateMapCategoryUsedTimeSortedFibObjectInfos = true;
#endif //FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
	
	DEBUG_OUT_L2(<<"cFibObjectInfoHandler("<<this<<")::addToUsedTimeSortedFibObjectInfos() add to sorted \""<<pFibObjectInfo->getFibObjectName()<<"\" with weight "<<dLastUsedTimesWeightSum<<endl<<flush);
	if ( bLock ) {
		mutexUsedTimeSortedFibObjectInfos.unlock();
	}
}


/**
 * This method will remove the given Fib object info object from the
 * "used time" sorted Fib object infos.
 * Note: It will not use the mutexFibObjectInfoHandler, so lock it
 * 	outside this method.
 * 	But will use the mutexUsedTimeSortedFibObjectInfos.
 *
 * @see mapUsedTimeSortedFibObjectInfos
 * @see mutexUsedTimeSortedFibObjectInfos
 * @param pRemovedFibObjectInfo the Fib object info object to remove from the
 * 	"used time" sorted Fib object infos
 */
bool cFibObjectInfoHandler::removeFromUsedTimeSortedFibObjectInfos(
		const cFibObjectInfo * pRemovedFibObjectInfo ) {
	
	mutexUsedTimeSortedFibObjectInfos.lock();
	
	const double dLastUsedTimesWeightSum = getLastUsedTimesWeightSum(
		pRemovedFibObjectInfo->getLastUsedTimes() );
	pair< multimap< double , cFibObjectInfo * >::iterator,
		multimap< double , cFibObjectInfo * >::iterator > paFound =
		mapUsedTimeSortedFibObjectInfos.equal_range( dLastUsedTimesWeightSum );
	bool bSortedFibObjectInfoFound = false;
	
	for ( multimap< double , cFibObjectInfo * >::iterator
			itrSortedFibObjectInfo = paFound.first;
			itrSortedFibObjectInfo != paFound.second; ++itrSortedFibObjectInfo ) {
		
		if ( itrSortedFibObjectInfo->second == pRemovedFibObjectInfo ) {
			//Fib object info in sorted map found -> erase it
			mapUsedTimeSortedFibObjectInfos.erase( itrSortedFibObjectInfo );
			bSortedFibObjectInfoFound = true;
			break;
		}
	}
	
	if ( ! bSortedFibObjectInfoFound ) {
		//search in the whole sorted map
		for ( multimap< double , cFibObjectInfo * >::iterator
				itrSortedFibObjectInfo = mapUsedTimeSortedFibObjectInfos.begin();
				itrSortedFibObjectInfo != mapUsedTimeSortedFibObjectInfos.end();
				++itrSortedFibObjectInfo ) {
			
			if ( itrSortedFibObjectInfo->second == pRemovedFibObjectInfo ) {
				//Fib object info in sorted map found -> erase it
				mapUsedTimeSortedFibObjectInfos.erase( itrSortedFibObjectInfo );
				bSortedFibObjectInfoFound = true;
				break;
			}
		}
	}
#ifdef FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
	bReevaluateMapCategoryUsedTimeSortedFibObjectInfos = true;
#endif //FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
	mutexUsedTimeSortedFibObjectInfos.unlock();
	return bSortedFibObjectInfoFound;
}


#ifdef FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS

/**
 * This method evaluates the "used time" sorted lists/vectors of
 * Fib object info objects for the categories.
 * It will use the Fib object info (order) in mapUsedTimeSortedFibObjectInfos
 * to evaluate the "used time" sorted Fib object info lists for
 * mapCategoryUsedTimeSortedFibObjectInfos.
 * Note: This method will not use mutex mutexUsedTimeSortedFibObjectInfos.
 *
 * @see mapCategoryUsedTimeSortedFibObjectInfos
 * @see mapUsedTimeSortedFibObjectInfos
 * @see bReevaluateMapCategoryUsedTimeSortedFibObjectInfos
 * @see mutexUsedTimeSortedFibObjectInfos
 */
void cFibObjectInfoHandler::evaluateMapCategoryUsedTimeSortedFibObjectInfos() {
	//clear old values
	mapCategoryUsedTimeSortedFibObjectInfos.clear();
	/*put the Fib object infos in there order into thiere category vectors
	in mapCategoryUsedTimeSortedFibObjectInfos*/
	cFibObjectInfo * pActualFibObjectInfo;
	std::set< std::string >::const_iterator itrCategory;
	
	std::vector< cFibObjectInfo * > & vecFibObjectInfoForCategoryAll =
		mapCategoryUsedTimeSortedFibObjectInfos[ getCategoryForAll() ];
	for ( std::multimap< double , cFibObjectInfo * >::reverse_iterator
			itrFibObjectInfo = mapUsedTimeSortedFibObjectInfos.rbegin();
			itrFibObjectInfo != mapUsedTimeSortedFibObjectInfos.rend();
			++itrFibObjectInfo ) {
		
		pActualFibObjectInfo = itrFibObjectInfo->second;
		const std::set< std::string > setFibObjectInfoCategories =
			pActualFibObjectInfo->getCategories();
		//add the Fib object info into category for all
		vecFibObjectInfoForCategoryAll.push_back( pActualFibObjectInfo );
		//add the Fib object info into every category it is in
		for ( itrCategory = setFibObjectInfoCategories.begin();
				itrCategory != setFibObjectInfoCategories.end();
				++itrCategory ) {
			
			mapCategoryUsedTimeSortedFibObjectInfos[ *itrCategory ].push_back(
				pActualFibObjectInfo );
		}
	}
	//mapCategoryUsedTimeSortedFibObjectInfos reevalued
	bReevaluateMapCategoryUsedTimeSortedFibObjectInfos = false;
}

#endif //FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS


//TODO check fast end

/**
 * This function reads the integer number from the given string.
 * Leading zeros '0' will be ignored.
 *
 * @param pSzNumber the number as a string
 * @return the number of pSzNumber
 */
unsigned long cFibObjectInfoHandler::toUnsignedLong( const char * pSzNumber ) {
	
	unsigned long ulNumber = 0;
	while ( true ) {
		const char cActualChar = (*pSzNumber);
		if ( ( cActualChar < '0' ) || ( '9' < cActualChar ) ) {
			//not a number
			break;
		}
		//read next decimal char
		ulNumber *= 10;
		ulNumber += ((unsigned int)(cActualChar - '0'));
		//check next character
		pSzNumber++;
	}
	return ulNumber;
}








