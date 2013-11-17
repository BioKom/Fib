/**
 * @file cFolder
 * file name: cFolder.h
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
07.10.2013  Oesterholz  method create() added
*/



#ifndef ___C_FOLDER_H__
#define ___C_FOLDER_H__



#include <string>
#include <list>

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>


using namespace std;



class cFolder{
protected:
	
	/**
	 * The path of the folder this class represents.
	 */
	string szFolderName;
	
	/**
	 * If the folder, this class represents, is accessible.
	 */
	bool bGood;
	
	/**
	 * The list of the entries of the folder, with ther information.
	 */
	list< pair<string, struct stat> > liEntryInfo;
	
	/**
	 * The list of subfolders in the folder.
	 */
	list<string> liSubFolders;
	
	/**
	 * The list of (regular) files in the folder.
	 */
	list<string> liFiles;


public:
	
	/**
	 * constructor
	 *
	 * @param szFolderName the path of the folder this object should represent
	 */
	cFolder( const char * szFolderName );

	/**
	 * constructor
	 *
	 * @param szFolderName the path of the folder this object should represent
	 */
	cFolder( const string & szFolderName );

	/**
	 * Updates the data of the folder.
	 * This means the folder information is reread.
	 *
	 * @return true if the folder, this class represents, is accessible, else false
	 */
	bool update();
	
	/**
	 * @return true if the folder, this class represents, is accessible, else false
	 */
	bool good() const;
	
	/**
	 * Returns the entry information for the entry with the given number.
	 *
	 * @param uiEntryNumber the number of the entry, for which the information
	 * 	is to be returned
	 * @return the information to the uiEntryNumber'th entry in the folder
	 */
	struct stat getInfo( unsigned int uiEntryNumber ) const;
	
	/**
	 * Returns the entry information for the entry with the given name.
	 *
	 * @param szEntryName the name of the entry, for which the information
	 * 	is to be returned
	 * @return the information to the entry with the given name szEntryName
	 */
	struct stat getInfo( const string & szEntryName ) const;
	
	/**
	 * This method returns the size (in byts) of the folderentry with the
	 * given name szEntryName.
	 *
	 * @param szEntryName the name of the entry, for which the size
	 * 	is to be returned
	 * @return the size in byts of the entry with given name szEntryName,
	 * 	or 0 if the entry didn't exists or has no size
	 */
	unsigned long getSize( const string & szEntryName ) const;
	
	/**
	 * This method returns the user id of the folderentry with the
	 * given name szEntryName.
	 *
	 * @param szEntryName the name of the entry, for which the user id
	 * 	is to be returned
	 * @return the user id of the entry with given name szEntryName,
	 * 	or 0 if the entry didn't exists or has no size
	 */
	unsigned int getUserId( const string & szEntryName ) const;
	
	/**
	 * This method returns the group id of the folderentry with the
	 * given name szEntryName.
	 *
	 * @param szEntryName the name of the entry, for which the group id
	 * 	is to be returned
	 * @return the group id of the entry with given name szEntryName,
	 * 	or 0 if the entry didn't exists or has no size
	 */
	unsigned int getGroupId( const string & szEntryName ) const;
	
	/**
	 * This method returns the time the folderentry with the given name
	 * szEntryName was last accessed.
	 *
	 * @param szEntryName the name of the entry, for which the last access
	 * 	time is to be returned
	 * @return the time of the last access of the entry with given name
	 * 	szEntryName, or 0 if the entry didn't exists
	 */
	time_t getLastAccessTime( const string & szEntryName ) const;
	
	/**
	 * This method returns the time the folderentry with the given name
	 * szEntryName was last changed.
	 *
	 * @param szEntryName the name of the entry, for which the last changed
	 * 	time is to be returned
	 * @return the time of the last changed of the entry with given name
	 * 	szEntryName, or 0 if the entry didn't exists
	 */
	time_t getLastChangeTime( const string & szEntryName ) const;
	
	/**
	 * This method returns the time status of the folderentry with the given
	 * name szEntryName was last changed.
	 *
	 * @param szEntryName the name of the entry, for which the last status
	 * 	changed time is to be returned
	 * @return the time of the last status changed of the entry with given name
	 * 	szEntryName, or 0 if the entry didn't exists
	 */
	time_t getLastStatusChangeTime( const string & szEntryName ) const;
	
	/**
	 * @return a list with the names of all entries in the folder
	 */
	list<string> getAllEntries() const;
	
	
	/**
	 * @return a list with the names of all subfolders in the folder
	 */
	list<string> getSubFolders() const;
	
	
	/**
	 * @return a list with the names of all (regular) files in the folder
	 */
	list<string> getFiles() const;
	
	/**
	 * This method creates the folder if it didn't exists.
	 *
	 * @return true if the folder, this class represents, is accessible, else false
	 * 	@see update()
	 */
	bool create();
	
private:
	
	/**
	 * This function checks if a file for the given path exists and can be
	 * opened.
	 *
	 * @param szPath a string for the path to be checked
	 * @return true if the path exists, else false
	 */
	static bool checkPath( char * szPath );
	
};//end class cFolder

#endif //___C_FOLDER_H__








