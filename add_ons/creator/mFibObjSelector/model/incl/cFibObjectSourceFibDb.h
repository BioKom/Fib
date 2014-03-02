/**
 * @file cFibObjectSourceFibDb
 * file name: cFibObjectSourceFibDb.h
 * @author Betti Oesterholz
 * @date 18.09.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for information for loading a Fib object
 * from the Fib database.
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
 * from the Fib database.
 *
 * ## File format ##
 *
 * A Fib information object for loading a Fib object will be stored in
 * the XML format.
 * The name of the root element is "fib_object_source". It has two
 * attributes "type" and "identifier".
 * The "type" attribute is always "Fib database". The attribute
 * "identifier" gives the identifier of the Fib database object.
 * @see lFibDbIdentifier
 *
 * example:
      <fib_object_source type="Fib database" identifier="-20">
 *
 *
 * @see cFibObjectSource
 * @see cFibElement
 * @see cFibDatabase
 * @see cFibObjectInfo
 * @see cFibNode
 */
/*
History:
18.09.2013  Oesterholz  created
02.03.2014  Oesterholz  categories for Fib object source added: getCategories()
*/


#ifndef ___FIB__NCREATOR__C_FIB_OBJECT_SOURCE_FIB_DB_H__
#define ___FIB__NCREATOR__C_FIB_OBJECT_SOURCE_FIB_DB_H__


#include "version.h"

#include "fibDatatyps.h"

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


class cFibObjectSourceFibDb: public cFibObjectSource{
protected:
	
	/**
	 * The Fib database identifer for the to load Fib database object.
	 */
	longFib lFibDbIdentifier;
	
public:
	
	/**
	 * The standard constructor for a Fib database object source object.
	 *
	 * @param lInFibDbIdentifier the identifier for the to load Fib database
	 * 	object
	 * 	@see lFibDbIdentifier
	 */
	explicit cFibObjectSourceFibDb( const longFib & lInFibDbIdentifier );
	
	/**
	 * The copy constructor for a Fib database object source object.
	 *
	 * @param fibObjectSourceFibDb the Fib database object source object to copy
	 */
	cFibObjectSourceFibDb( const cFibObjectSourceFibDb & fibObjectSourceFibDb );
	
	/**
	 * This constructor will restore the Fib database object source object
	 * from the given input stream.
	 *
	 * @see store()
	 * @param stream the input stream from which to read the Fib database
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
	explicit cFibObjectSourceFibDb( std::istream & stream, int * iOutStatus = NULL );
	
	/**
	 * This constructor will restore the Fib database object source object
	 * from the given TinyXml node.
	 *
	 * @see store()
	 * @param pXmlNode a pointer to the TinyXml node where the Fib database
	 * 	object source object is stored in
	 * @param iOutStatus if not NULL an integer value with the error value
	 * 	possible error values are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlNode
	 * 		- -2 loading error, invalid data in pXmlNode
	 * 		- 1 loading warning, invalid data in pXmlNode, error could
	 * 			be corrected
	 * 		- 2 loading warning, invalid data in pXmlNode, maybe the
	 * 			loaded object is wrong
	 */
	explicit cFibObjectSourceFibDb( const TiXmlNode * pXmlNode,
		int * iOutStatus = NULL );
	
	/**
	 * destructor
	 */
	virtual ~cFibObjectSourceFibDb();
	
	
	/**
	 * @return the name of this class "cFibObjectSourceFibDb"
	 */
	virtual std::string getName() const;
	
	/**
	 * @return the identifier for the to load Fib database object
	 * 	@see lFibDbIdentifier
	 */
	longFib getFibDbIdentifier() const;
	
	/**
	 * This method creates a copy of this object and returns it.
	 *
	 * @return a pointer to a copy of this object
	 */
	virtual cFibObjectSourceFibDb * clone() const;
	
	/**
	 * This method loads the Fib object from the source and returns a
	 * pointer to it.
	 * If no Fib object can be loaded NULL will be returned.
	 * Beware: You have to care that the loaded Fib object will be deleted.
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
		std::set< std::string > * pOutSetChangebelBy = NULL ) const;
	
	/**
	 * This method will store the given Fib object to the location this
	 * object specifies.
	 *
	 * @see loadFibObject()
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
	 * This method will store this Fib database object source object to
	 * the given stream.
	 *
	 * @see restoreFibObjectSource()
	 * @param stream the output stream to which to store this object
	 * @return true if this Fib database object source object could be
	 * 	stored, else false
	 */
	virtual bool store( std::ostream & stream ) const;

	/**
	 * This method will restore the Fib database object source object from
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
	 * This method will restore the Fib database object source object from
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
	 * This method will restore the Fib database object source object from
	 * the given input stream and return a pointer to it.
	 * Beware: You have to care that the returned Fib database object source
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
	 * @return a pointer to the restored Fib database object source object
	 * 	or NULL if non could be restored
	 */
	static cFibObjectSourceFibDb * restore( std::istream & stream,
			int * iOutStatus = NULL );
	
	/**
	 * This method will restore the Fib database object source object from
	 * the given TinyXml node and return a pointer to it.
	 * Beware: You have to care that the returned Fib database object source
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
	 * @return a pointer to the restored Fib database object source object or NULL if
	 * 	non could be restored
	 */
	static cFibObjectSourceFibDb * restore( const TiXmlNode * pXmlNode,
		int * iOutStatus = NULL );
	
	
	/**
	 * This method checks if the given Fib database object source object is
	 * equal to this Fib database object source object.
	 *
	 * @param fibObjectSource the Fib database object source object to
	 * 	compare with this
	 * @return true if the given Fib database object source object is equal
	 * 	to this Fib database object source object, else false
	 */
	virtual bool equal( const cFibObjectSource & fibObjectSource ) const;

	/**
	 * This method checks if the given Fib database object source object is
	 * equal to this Fib database object source object.
	 *
	 * @param fibObjectSource the Fib database object source object to
	 * 	compare with this
	 * @return true if the given Fib database object source object is equal
	 * 	to this Fib database object source object, else false
	 */
	virtual bool operator==( const cFibObjectSource & fibObjectSource ) const;

	
};//end class cFibObjectSourceFibDb

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_OBJECT_SOURCE_FIB_DB_H__





