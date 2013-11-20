
//TODO check

/**
 * @file cFibObjectCategory
 * file name: cFibObjectCategory.cpp
 * @author Betti Oesterholz
 * @date 18.10.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a category for a Fib object.
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
 * This file implements a class for a category for a Fib object.
 *
 * possibel category types:
 *    - relative categories: same type (sameType), is contained (isContained), ...
 *      (the category is relativ to a (base) Fib object, e. g. the category
 *      of Fib object of the same type as a base Fib object)
 *    - absolute categories: all, typs like: objects, people, ...
 *
 * @see cFibObjectInfos
 * @see cFibObjectInfo
 * @see cDialogSelectFibObject
 */
/*
History:
18.10.2013  Oesterholz  created
*/



#include "cFibObjectCategory.h"


using namespace fib::nCreator;

/**
 * The standard constructor.
 *
 * @param szInName the name of the category to create
 * 	@see szName
 * @param bInIsAbsolute if true true if the category is absolute,
 * 	else false, if it is relativ to a other fib object
 * 	@see bIsAbsolute
 */
cFibObjectCategory::cFibObjectCategory( const QString & szInName,
		const bool bInIsAbsolute ):
		szName( szInName ), bIsAbsolute( bInIsAbsolute ){
	//nothing to do
}


/**
 * The copy constructor.
 *
 * @param fibObjectCategory the Fib object category to copy
 */
cFibObjectCategory::cFibObjectCategory( const cFibObjectCategory & fibObjectCategory ):
		szName( fibObjectCategory.szName ),
		bIsAbsolute( fibObjectCategory.bIsAbsolute ){
	//nothing to do
}


/**
 * @return the name of this class "cFibObjectCategory"
 */
std::string cFibObjectCategory::getName() const{
	
	return "cFibObjectCategory";
}


/**
 * @return the name of this category
 * 	@see szName
 */
QString cFibObjectCategory::getCategoryName() const{
	
	return szName;
}


/**
 * @return true true if the category is absolute, else false, if
 * 	it is relativ to a other fib object
 * 	@see bIsAbsolute
 */
bool cFibObjectCategory::isAbsolute() const{
	
	return bIsAbsolute;
}


/**
 * This method checks if the given category object is equal to this
 * category object.
 *
 * @param fibObjectCategory the category object to compare with this
 * @return true if the given category object is equal to this
 * 	category object, else false
 */
bool cFibObjectCategory::equal(
		const cFibObjectCategory & fibObjectCategory ) const{
	
	return ( (*this) == fibObjectCategory );
}


/**
 * This method checks if the given category object is equal to this
 * category object.
 *
 * @param fibObjectCategory the category object to compare with this
 * @return true if the given category object is equal to this
 * 	category object, else false
 */
bool cFibObjectCategory::operator==(
		const cFibObjectCategory & fibObjectCategory ) const{
	
	return ( ( szName == fibObjectCategory.szName ) &&
		( bIsAbsolute == fibObjectCategory.bIsAbsolute ) );
}








