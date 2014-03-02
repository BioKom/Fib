/**
 * @file cFibObjectSource
 * file name: cFibObjectSource.h
 * @author Betti Oesterholz
 * @date 16.09.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for information for loading a Fib object.
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
 * This file specifies a class for information for loading a Fib object.
 * It is a base class for all classes for information to restore a Fib object.
 *
 * @see cFibElement
 * @see cFibObjectInfo
 * @see cFibNode
 */
/*
History:
16.09.2013  Oesterholz  created
02.03.2014  Oesterholz  categories for Fib object source added: getCategories()
*/


#ifndef ___FIB__NCREATOR__C_FIB_OBJECT_SOURCE_H__
#define ___FIB__NCREATOR__C_FIB_OBJECT_SOURCE_H__


#include "version.h"

#include <ostream>
#include <istream>
#include <set>
#include <string>

#include "tinyxml.h"



namespace fib{

//forward declarations
class cFibElement;

namespace nCreator{


class cFibObjectSource{
public:
	
	/**
	 * The standard constructor for a Fib object source object.
	 */
	cFibObjectSource();
	
	/**
	 * destructor
	 */
	virtual ~cFibObjectSource();
	
	
	/**
	 * @return the name of this class "cFibObjectSource"
	 */
	virtual std::string getName() const;
	
	/**
	 * This method creates a copy of this object and returns it.
	 *
	 * @return a pointer to a copy of this object
	 */
	virtual cFibObjectSource * clone() const = 0;
	
	/**
	 * This method loads the Fib object from the source and returns a
	 * pointer to it. If a Fib object is already loaded it will be
	 * returned (without reloading it). If you like to relode the Fib object
	 * first delete the loaded Fib object with deleteLoadedFibObject() .
	 * If no Fib object can be loaded NULL will be returned.
	 * Note: This object will care that the returned Fib object will be
	 * 	deleted. (On destruction of this object.)
	 *
	 * @param iOutStatus if not NULL an integer value with the error value
	 * 	possible error values are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid source
	 * 		- -2 loading error, invalid data
	 * 		- 1 loading warning, invalid data, error could be corrected
	 * 		- 2 loading warning, invalid data, maybe the loaded
	 * 			object is wrong
	 * @param pOutSetChangebelBy if not NULL a set to output the users who
	 * 	can change change the loaded Fib object
	 * @return a pointer to the loaded Fib object, or NULL if non could be
	 * 	loaded
	 */
	virtual cFibElement * loadFibObject( int * iOutStatus = NULL,
		std::set< std::string > * pOutSetChangebelBy = NULL ) const = 0;
	
	/**
	 * This method will store the given Fib object to location this object
	 * specifies.
	 *
	 * @see loadFibObject()
	 * @param pFibObject a pointer to the Fib object to store
	 * @return true if the given Fib object could be stored, else false
	 */
	virtual bool storeFibObject( const cFibElement * pFibObject ) const = 0;
	
	/**
	 * This method checks if the Fib object source exists.
	 *
	 * @return true if the source for the Fib object exists, else false
	 */
	virtual bool checkSource() const = 0;
	
	/**
	 * @return the set with the categories this Fib object source is in
	 * 	(e.g. "Fib database", "file")
	 */
	virtual std::set< std::string > getCategories() const;
	
	/**
	 * This method will store this Fib object source object to the given
	 * stream.
	 *
	 * @see restoreFibObjectSource()
	 * @param stream the output stream to which to store this object
	 * @return true if this Fib object source object could be stored, else false
	 */
	virtual bool store( std::ostream & stream ) const = 0;

	/**
	 * This method will restore the Fib object source object from the given
	 * stream.
	 *
	 * @see storeFibObjectSource()
	 * @param stream the input stream from which to read the Fib object source object
	 * @return an integer value with the error value,
	 * 	possible error values are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid stream
	 * 		- -2 loading error, invalid data in stream
	 * 		- 1 loading warning, invalid data in stream, error could be corrected
	 * 		- 2 loading warning, invalid data in stream, maybe the loaded
	 * 			object is wrong
	 */
	virtual int restoreFibObjectSource( std::istream & stream ) = 0;
	
	/**
	 * This method will restore the Fib object source object from the given
	 * TinyXml node.
	 *
	 * @see storeFibObjectSource()
	 * @param pXmlNode a pointer to the TinyXml node where the Fib object
	 * 	info object is stored in
	 * @return an integer value with the error value,
	 * 	possible error values are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlNode
	 * 		- -2 loading error, invalid data in pXmlNode
	 * 		- 1 loading warning, invalid data in pXmlNode, error could
	 * 			be corrected
	 * 		- 2 loading warning, invalid data in pXmlNode, maybe the loaded
	 * 			object is wrong
	 */
	virtual int restoreFibObjectSource( const TiXmlNode * pXmlNode ) = 0;
	
	/**
	 * This method will restore the Fib object source object from the given
	 * input stream and return a pointer to it.
	 * Beware: You have to care that the returned Fib object source object is
	 * 	deleted.
	 *
	 * @see storeFibObjectSource()
	 * @param stream the input stream from which to read the Fib object info
	 * @param iOutStatus if not NULL an integer value with the error value,
	 * 	possible error values are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid stream
	 * 		- -2 loading error, invalid data in stream
	 * 		- 1 loading warning, invalid data in stream, error could
	 * 			be corrected
	 * 		- 2 loading warning, invalid data in stream, maybe the
	 * 			loaded object is wrong
	 * @return a pointer to the restored Fib object source object or NULL if
	 * 	non could be restored
	 */
	static cFibObjectSource * restore( std::istream & stream,
			int * iOutStatus = NULL );
	
	/**
	 * This method will restore the Fib object source object from the given
	 * TinyXml node and return a pointer to it.
	 * Beware: You have to care that the returned Fib object source object
	 * 	is deleted.
	 *
	 * @see storeFibObjectSource()
	 * @param pXmlNode a pointer to the TinyXml node where the Fib object
	 * 	info object is stored in
	 * @param iOutStatus if not NULL an integer value with the error value,
	 * 	possible error values are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlNode
	 * 		- -2 loading error, invalid data in pXmlNode
	 * 		- 1 loading warning, invalid data in pXmlNode, error could
	 * 			be corrected
	 * 		- 2 loading warning, invalid data in pXmlNode, maybe the
	 * 			loaded object is wrong
	 * @return a pointer to the restored Fib object source object or NULL, if
	 * 	non could be restored
	 */
	static cFibObjectSource * restore( const TiXmlNode * pXmlNode,
		int * iOutStatus = NULL );
	
	
	/**
	 * This method checks if the given Fib object source object is equal to
	 * this Fib object source object.
	 *
	 * @param fibObjectSource the Fib object source object to compare with this
	 * @return true if the given Fib object source object is equal to this
	 * 	Fib object source object, else false
	 */
	virtual bool equal( const cFibObjectSource & fibObjectSource ) const = 0;

	/**
	 * This method checks if the given Fib object source object is equal to
	 * this Fib object source object.
	 *
	 * @param fibObjectSource the Fib object source object to compare with this
	 * @return true if the given Fib object source object is equal to this
	 * 	Fib object source object, else false
	 */
	virtual bool operator==( const cFibObjectSource & fibObjectSource ) const = 0;

	
};//end class cFibObjectSource

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_OBJECT_SOURCE_H__





