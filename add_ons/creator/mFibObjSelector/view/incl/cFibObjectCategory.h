
//TODO check

/**
 * @file cFibObjectCategory
 * file name: cFibObjectCategory.h
 * @author Betti Oesterholz
 * @date 18.10.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a category for a Fib object.
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
 * This file specifies a class for a category for a Fib object.
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


#ifndef ___FIB__NCREATOR__C_FIB_OBJECT_CATEGORY_H__
#define ___FIB__NCREATOR__C_FIB_OBJECT_CATEGORY_H__


#include "version.h"

#include <string>

#include <QObject>
#include <QString>


namespace fib{

namespace nCreator{

class cFibObjectCategory{
public:
	
	/**
	 * The standard constructor.
	 *
	 * @param szInName the name of the category to create
	 * 	@see szName
	 * @param bInIsAbsolute if true true if the category is absolute,
	 * 	else false, if it is relativ to a other fib object
	 * 	@see bIsAbsolute
	 */
	cFibObjectCategory( const QString & szInName, const bool bInIsAbsolute = false );
	
	/**
	 * The copy constructor.
	 *
	 * @param fibObjectCategory the Fib object category to copy
	 */
	cFibObjectCategory( const cFibObjectCategory & fibObjectCategory );
	
	/**
	 * @return the name of this class "cFibObjectCategory"
	 */
	std::string getName() const;
	
	/**
	 * @return the name of this category
	 * 	@see szName
	 */
	QString getCategoryName() const;
	
	/**
	 * @return true true if the category is absolute, else false, if
	 * 	it is relativ to a other fib object
	 * 	@see bIsAbsolute
	 */
	bool isAbsolute() const;
	
	/**
	 * This method checks if the given category object is equal to this
	 * category object.
	 *
	 * @param fibObjectCategory the category object to compare with this
	 * @return true if the given category object is equal to this
	 * 	category object, else false
	 */
	virtual bool equal( const cFibObjectCategory & fibObjectCategory ) const;

	/**
	 * This method checks if the given category object is equal to this
	 * category object.
	 *
	 * @param fibObjectCategory the category object to compare with this
	 * @return true if the given category object is equal to this
	 * 	category object, else false
	 */
	virtual bool operator==( const cFibObjectCategory & fibObjectCategory ) const;
	
protected:
	
	/**
	 * The name of the category.
	 */
	QString szName;
	
	/**
	 * If true true if the category is absolute, else false, if it is
	 * relativ to a other fib object.
	 */
	bool bIsAbsolute;
	
};//end class cFibObjectCategory


};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_OBJECT_CATEGORY_H__





