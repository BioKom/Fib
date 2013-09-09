
//TODO check

/**
 * @class funJavaScriptFileHandling
 * file name: funJavaScriptFileHandling.cpp
 * @author Betti Oesterholz
 * @date 15.05.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements some functions to access the file system via
 * javascript.
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
 * This file implements some functions to access the file system via
 * javascript.
 *
 */
/*
History:
15.05.2013  Oesterholz  created
*/



#include "funJavaScriptFileHandling.h"

#include <string>      // std::ostringstream
#include <sstream>      // std::ostringstream

extern "C" {

extern char * jsFunOpenFileStream( const char * zsPath );
extern int jsFunCheckIfFolderExists( const char * zsFolder );
extern int jsFunCheckIfFileExists( const char * zsPath );


};//end extern "C"


/**
 * This function opens the stream for the given path.
 *
 * @param zsPath the path of the file to open
 * @return the open stream
 */
istream * jsOpenFileStream( const char * zsPath ){
	
	const char * pLoadedData = jsFunOpenFileStream( zsPath );
	if ( pLoadedData == NULL ){
		//no data loaded
		return NULL;
	}
	
	return new std::istringstream( string( pLoadedData ) );
}


/**
 * This function checks if the given path is a existing folder.
 *
 * @param zsPath the path to check
 * @return true if the path is a existing folder, else false
 */
bool jsCheckIfFolderExists( const char * zsFolder ){
	
	return ( jsFunCheckIfFolderExists( zsFolder ) == 0 );
}


/**
 * This function checks if the given path is a existing file.
 *
 * @param zsPath the path to check
 * @return true if the path is a existing file, else false
 */
bool jsCheckIfFileExists( const char * zsPath ){
	
	return ( jsFunCheckIfFileExists( zsPath ) == 0 );
}







