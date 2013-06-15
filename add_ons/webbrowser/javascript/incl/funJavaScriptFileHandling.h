
//TODO check

/**
 * @class funJavaScriptFileHandling
 * file name: funJavaScriptFileHandling.h
 * @author Betti Oesterholz
 * @date 15.05.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This interface declares some functions to access the file system via
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
 * This interface declares some functions to access the file system via
 * javascript.
 *
 */
/*
History:
15.05.2013  Oesterholz  created
*/

#ifndef ___FUN_JAVASCRIPT_FILE_HANDLING_H__
#define ___FUN_JAVASCRIPT_FILE_HANDLING_H__


#include "version.h"

#include <istream>

using namespace std;

	
	/**
	 * This function opens the stream for the given path.
	 *
	 * @param zsPath the path of the file to open
	 * @return the open stream
	 */
	extern istream * jsOpenFileStream( const char * zsPath );


	/**
	 * This function checks if the given path is a existing folder.
	 *
	 * @param zsPath the path to check
	 * @return true if the path is a existing folder, else false
	 */
	extern bool jsCheckIfFolderExists( const char * zsFolder );

	/**
	 * This function checks if the given path is a existing file.
	 *
	 * @param zsPath the path to check
	 * @return true if the path is a existing file, else false
	 */
	extern bool jsCheckIfFileExists( const char * zsPath );

#endif //___FUN_JAVASCRIPT_FILE_HANDLING_H__






