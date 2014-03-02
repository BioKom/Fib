/**
 * @file cFibObjectSourcePath
 * file name: cFibObjectSourcePath.h
 * @author Betti Oesterholz
 * @date 29.09.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for information for loading a Fib object
 * from a given path.
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
 * This file specifies a class for information for loading a Fib object
 * from a given path.
 *
 * ## File format ##
 *
 * A Fib information object for loading a Fib object will be stored in
 * the XML format.
 * The name of the root element is "fib_object_source". It has two
 * attributes "type" and "path".
 * The "type" attribute is always "path". The attribute
 * "path" gives the path to the Fib object.
 * @see szPath
 *
 * example:
       <fib_object_source type="path" path="/home/biokom/fib_objects">
 *
 *
 * @see cFibObjectSource
 * @see cFibElement
 * @see cFibObjectInfo
 * @see cFibNode
 */
/*
History:
29.09.2013  Oesterholz  created
02.03.2014  Oesterholz  categories for Fib object source added: getCategories()
*/


#ifndef ___FIB__NCREATOR__C_FIB_OBJECT_SOURCE_PATH_H__
#define ___FIB__NCREATOR__C_FIB_OBJECT_SOURCE_PATH_H__


#include "version.h"

#include "cFibObjectSource.h"

#include <ostream>
#include <istream>
#include <set>
#include <string>

#include "tinyxml.h"


namespace fib{
//forward declarations
class cFibElement;

namespace nCreator{


class cFibObjectSourcePath: public cFibObjectSource{
protected:
	
	/**
	 * The path to the to load Fib object.
	 * @see getPath()
	 * @see loadFibObject()
	 * @see storeFibObject()
	 */
	std::string szPath;
	
public:
	
	/**
	 * The standard constructor for a path Fib object source object.
	 *
	 * @param szInPath the path to the to load Fib object
	 * 	@see szPath
	 */
	explicit cFibObjectSourcePath( const std::string & szInPath );
	
	/**
	 * The copy constructor for a path Fib object source object.
	 *
	 * @param fibObjectSourcePath the path Fib object source object to copy
	 */
	cFibObjectSourcePath( const cFibObjectSourcePath & fibObjectSourcePath );
	
	/**
	 * This constructor will restore the path Fib object source object from
	 * the given input stream.
	 *
	 * @see store()
	 * @param stream the input stream from which to read the path Fib
	 * 	object source object
	 * @param iOutStatus if not NULL an integer value with the error value
	 * 	possible error values are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid stream
	 * 		- -2 loading error, invalid data in stream
	 * 		- 1 loading warning, invalid data in stream, error could be corrected
	 * 		- 2 loading warning, invalid data in stream, maybe the loaded
	 * 			object is wrong
	 */
	explicit cFibObjectSourcePath( std::istream & stream, int * iOutStatus = NULL );
	
	/**
	 * This constructor will restore the path Fib object source object from
	 * the given TinyXml node.
	 *
	 * @see store()
	 * @param pXmlNode a pointer to the TinyXml node where the path Fib
	 * 	object source object is stored in
	 * @param iOutStatus if not NULL an integer value with the error value
	 * 	possible error values are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlNode
	 * 		- -2 loading error, invalid data in pXmlNode
	 * 		- 1 loading warning, invalid data in pXmlNode, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlNode, maybe the loaded
	 * 			object is wrong
	 */
	explicit cFibObjectSourcePath( const TiXmlNode * pXmlNode,
		int * iOutStatus = NULL );
	
	/**
	 * destructor
	 */
	virtual ~cFibObjectSourcePath();
	
	
	/**
	 * @return the name of this class "cFibObjectSourcePath"
	 */
	virtual std::string getName() const;
	
	/**
	 * @return the path to the to load Fib object
	 * 	@see szPath
	 */
	std::string getPath() const;
	
	/**
	 * This method creates a copy of this object and returns it.
	 *
	 * @return a pointer to a copy of this object
	 */
	virtual cFibObjectSourcePath * clone() const;
	
	/**
	 * This method loads the Fib object from the source and returns a
	 * pointer to it.
	 * If no Fib object can be loaded NULL will be returned.
	 * Beware: You have to care that the loaded Fib object will be deleted.
	 *
	 * @see storeFibObject()
	 * @see szPath
	 * @see getPath()
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
		std::set< std::string > * pOutSetChangebelBy = NULL ) const;
	
	/**
	 * This method will store the given Fib object to the location this
	 * object specifies.
	 *
	 * @see loadFibObject()
	 * @see szPath
	 * @see getPath()
	 * @param pFibObject a pointer to the Fib object to store
	 * @return true if the given Fib object could be stored, else false
	 */
	virtual bool storeFibObject( const cFibElement * pFibObject ) const;
	
	/**
	 * This method checks if the Fib object source exists.
	 *
	 * @return true if the source for the Fib object exists, else false
	 */
	virtual bool checkSource() const;
	
	/**
	 * @return the set with the categories this Fib object source is in
	 * 	(e.g. "Fib database", "file")
	 */
	virtual std::set< std::string > getCategories() const;
	
	
	/**
	 * This method will store this path Fib object source object to
	 * the given stream.
	 *
	 * @see restoreFibObjectSource()
	 * @param stream the output stream to which to store this object
	 * @return true if this path Fib object source object could be
	 * 	stored, else false
	 */
	virtual bool store( std::ostream & stream ) const;

	/**
	 * This method will restore the path Fib object source object from
	 * the given stream.
	 *
	 * @see storeFibObjectSource()
	 * @param stream the input stream from which to read the Fib object source
	 * @return an integer value with the error value
	 * 	possible error values are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid stream
	 * 		- -2 loading error, invalid data in stream
	 * 		- 1 loading warning, invalid data in stream, error could be corrected
	 * 		- 2 loading warning, invalid data in stream, maybe the loaded
	 * 			object is wrong
	 */
	virtual int restoreFibObjectSource( std::istream & stream );
	
	/**
	 * This method will restore the path Fib object source object from
	 * the given TinyXml node.
	 *
	 * @see storeFibObjectSource()
	 * @param pXmlNode a pointer to the TinyXml node where the Fib object
	 * 	source object is stored in
	 * @return an integer value with the error value
	 * 	possible error values are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlNode
	 * 		- -2 loading error, invalid data in pXmlNode
	 * 		- 1 loading warning, invalid data in pXmlNode, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlNode, maybe the loaded
	 * 			object is wrong
	 */
	virtual int restoreFibObjectSource( const TiXmlNode * pXmlNode );
	
	/**
	 * This method will restore the path Fib object source object from
	 * the given input stream and return a pointer to it.
	 * Beware: You have to care that the returned path Fib object source
	 * 	object is deleted.
	 *
	 * @see storeFibObjectSource()
	 * @param stream the input stream from which to read the Fib object source
	 * @param iOutStatus if not NULL an integer value with the error value
	 * 	possible error values are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid stream
	 * 		- -2 loading error, invalid data in stream
	 * 		- 1 loading warning, invalid data in stream, error could be corrected
	 * 		- 2 loading warning, invalid data in stream, maybe the loaded
	 * 			object is wrong
	 * @return a pointer to the restored path Fib object source object or
	 * 	NULL if non could be restored
	 */
	static cFibObjectSourcePath * restore( std::istream & stream,
			int * iOutStatus = NULL );
	
	/**
	 * This method will restore the path Fib object source object from
	 * the given TinyXml node and return a pointer to it.
	 * Beware: You have to care that the returned path Fib object source
	 * 	object is deleted.
	 *
	 * @see storeFibObjectSource()
	 * @param pXmlNode a pointer to the TinyXml node where the Fib object
	 * 	source object is stored in
	 * @param iOutStatus if not NULL an integer value with the error value
	 * 	possible error values are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlNode
	 * 		- -2 loading error, invalid data in pXmlNode
	 * 		- 1 loading warning, invalid data in pXmlNode, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlNode, maybe the loaded
	 * 			object is wrong
	 * @return a pointer to the restored path Fib object source object or
	 * 	NULL if non could be restored
	 */
	static cFibObjectSourcePath * restore( const TiXmlNode * pXmlNode,
		int * iOutStatus = NULL );
	
	
	/**
	 * This method checks if the given Fib object source object is equal to
	 * this path Fib object source object.
	 *
	 * @param fibObjectSource the Fib object source object to compare with this
	 * @return true if the given Fib object source object is equal
	 * 	to this path Fib object source object, else false
	 */
	virtual bool equal( const cFibObjectSource & fibObjectSource ) const;
	
	/**
	 * This method checks if the given Fib object source object is equal to
	 * this path Fib object source object.
	 *
	 * @param fibObjectSource the Fib object source object to
	 * 	compare with this
	 * @return true if the given Fib object source object is equal
	 * 	to this path Fib object source object, else false
	 */
	virtual bool operator==( const cFibObjectSource & fibObjectSource ) const;

	
};//end class cFibObjectSourcePath

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_OBJECT_SOURCE_PATH_H__





