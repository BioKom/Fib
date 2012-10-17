/**
 * @file cFolder
 * file name: cFolder.cpp
 * @author Betti Oesterholz
 * @date 07.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a folder.
 *
 * Copyright (C) @c GPL3 2010 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
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
 * This class represents a folder.
 * You can get the information about a folder and it's entries with it.
 *
 */
/*
History:
07.02.2010  Oesterholz  created
*/




#include "cFolder.h"

#include <cstring>
#include <cstdio>

/**
 * constructor
 *
 * @param szInFolderName the path of the folder this object should represent
 */
cFolder::cFolder( const char * szInFolderName ):
		szFolderName( szInFolderName ){
	
	update();
}


/**
 * constructor
 *
 * @param szInFolderName the path of the folder this object should represent
 */
cFolder::cFolder( const string & szInFolderName ):
		szFolderName( szInFolderName ){
	
	update();
}


/**
 * Updates the data of the folder.
 * This means the folder information is reread.
 */
bool cFolder::update(){
	
	//clear old data
	liEntryInfo.clear();
	liSubFolders.clear();
	liFiles.clear();
	bGood = true;
	
	//read the folderentries
	DIR * pFolder = opendir( szFolderName.c_str() );
	
	if ( pFolder == NULL ){
		bGood = false;
		return false;
	}
	struct dirent * pDirentry;
	list<string> liEntries;
	
	while ( (pDirentry = readdir( pFolder ) ) != NULL) {
		liEntries.push_back( string( pDirentry->d_name ) );
	}
	closedir( pFolder );
	
	//read the information of the folderentries
	for ( list<string>::iterator itrEntry = liEntries.begin();
			itrEntry != liEntries.end(); itrEntry++ ){
		
		struct stat fileStatus;
		char szFilePath[ 1024 ];
		
		sprintf( szFilePath, "%s/%s", szFolderName.c_str(), itrEntry->c_str() );
		
		if ( stat( szFilePath, &fileStatus ) == 0 ){
			
			liEntryInfo.push_back( make_pair( *itrEntry, fileStatus ) );
			
			int iFileType = fileStatus.st_mode & S_IFMT;
			switch ( iFileType ) {
				case S_IFREG:
					liFiles.push_back( *itrEntry );
				break;
				case S_IFDIR:
					liSubFolders.push_back( *itrEntry );
				break;
			}
		}//else Error
	}
	
	return bGood;
}

/**
 * @return true if the folder, this class represents, is accessible, else false
 */
bool cFolder::good() const{

	return bGood;
}


/**
 * Returns the entryinformation for the entry with the given number.
 *
 * @param uiEntryNumber the number of the entry, for which the information
 * 	is to be returned
 * @return the information to the uiEntryNumber'th entry in the folder
 */
struct stat cFolder::getInfo( unsigned int uiEntryNumber ) const{
	
	list< pair<string, struct stat> >::const_iterator
		itrEntry = liEntryInfo.begin();
	for ( ; itrEntry != liEntryInfo.end() ; itrEntry++, uiEntryNumber-- ){
		if ( uiEntryNumber <= 1 ){
			break;
		}
	}
	if ( itrEntry != liEntryInfo.end() ){
		//no such entry found
		struct stat dummyStatus;
		
		memset( & dummyStatus, 0x00, sizeof( struct stat ) );
		return dummyStatus;
	}
	return itrEntry->second;
}

/**
 * Returns the entryinformation for the entry with the given name.
 *
 * @param szEntryName the name of the entry, for which the information
 * 	is to be returned
 * @return the information to the entry with the given name szEntryName
 */
struct stat cFolder::getInfo( const string & szEntryName ) const{
	
	list< pair<string, struct stat> >::const_iterator
		itrEntry = liEntryInfo.begin();
	for ( ; itrEntry != liEntryInfo.end() ; itrEntry++ ){
		if ( itrEntry->first == szEntryName ){
			break;
		}
	}
	if ( itrEntry != liEntryInfo.end() ){
		//no such entry found
		struct stat dummyStatus;
		
		memset( & dummyStatus, 0x00, sizeof( struct stat ) );
		return dummyStatus;
	}
	return itrEntry->second;
}

/**
 * This method returns the size (in byts) of the folderentry with the
 * given name szEntryName.
 *
 * @param szEntryName the name of the entry, for which the size
 * 	is to be returned
 * @return the size in byts of the entry with given name szEntryName,
 * 	or 0 if the entry didn't exists or has no size
 */
unsigned long cFolder::getSize( const string & szEntryName ) const{
	
	return getInfo( szEntryName ).st_size;
}

/**
 * This method returns the user id of the folderentry with the
 * given name szEntryName.
 *
 * @param szEntryName the name of the entry, for which the user id
 * 	is to be returned
 * @return the user id of the entry with given name szEntryName,
 * 	or 0 if the entry didn't exists or has no size
 */
unsigned int cFolder::getUserId( const string & szEntryName ) const{
	
	return getInfo( szEntryName ).st_uid;
}

/**
 * This method returns the group id of the folderentry with the
 * given name szEntryName.
 *
 * @param szEntryName the name of the entry, for which the group id
 * 	is to be returned
 * @return the group id of the entry with given name szEntryName,
 * 	or 0 if the entry didn't exists or has no size
 */
unsigned int cFolder::getGroupId( const string & szEntryName ) const{
	
	return getInfo( szEntryName ).st_gid;
}

/**
 * This method returns the time the folderentry with the given name
 * szEntryName was last accessed.
 *
 * @param szEntryName the name of the entry, for which the last access
 * 	time is to be returned
 * @return the time of the last access of the entry with given name
 * 	szEntryName, or 0 if the entry didn't exists
 */
time_t cFolder::getLastAccessTime( const string & szEntryName ) const{
	
	return getInfo( szEntryName ).st_atime;
}

/**
 * This method returns the time the folderentry with the given name
 * szEntryName was last changed.
 *
 * @param szEntryName the name of the entry, for which the last changed
 * 	time is to be returned
 * @return the time of the last changed of the entry with given name
 * 	szEntryName, or 0 if the entry didn't exists
 */
time_t cFolder::getLastChangeTime( const string & szEntryName ) const{
	
	return getInfo( szEntryName ).st_mtime;
}

/**
 * This method returns the time status of the folderentry with the given
 * name szEntryName was last changed.
 *
 * @param szEntryName the name of the entry, for which the last status
 * 	changed time is to be returned
 * @return the time of the last status changed of the entry with given name
 * 	szEntryName, or 0 if the entry didn't exists
 */
time_t cFolder::getLastStatusChangeTime( const string & szEntryName ) const{
	
	return getInfo( szEntryName ).st_ctime;
}

/**
 * @return a list with the names of all entries in the folder
 */
list<string> cFolder::getAllEntries() const{
	
	list<string> liAllEntries;
	for ( list< pair<string, struct stat> >::const_iterator
			itrEntry = liEntryInfo.begin();
			itrEntry != liEntryInfo.end() ; itrEntry++ ){
		
		liAllEntries.push_back( itrEntry->first );
	}

	return liAllEntries;
}


/**
 * @return a list with the names of all subfolders in the folder
 */
list<string> cFolder::getSubFolders() const{
	
	return liSubFolders;
}


/**
 * @return a list with the names of all (regular) files in the folder
 */
list<string> cFolder::getFiles() const{
	
	return liFiles;
}










