/**
 * @class cOptionalPart
 * file name: cOptionalPart.h
 * @author Betti Oesterholz
 * @date 29.06.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the optionalpart of an root -element.
 * Copyright (C) @c LGPL3 2009 Betti Oesterholz
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
 * This class represents the optionalpart for an root -element.
 * The optionalpart consists of an list of key -value -pairs.
 *
 */
/*
History:
29.06.2009  Oesterholz  created
10.07.2011  Oesterholz  changes for compressed storing
23.09.2012  Oesterholz  Warning removed: virtual destructor added
*/

#ifndef ___C_OPTIONAL_PART_H__
#define ___C_OPTIONAL_PART_H__


#include "version.h"

#include "fibDatatyps.h"
#include "cReadBits.h"

#include "tinyxml.h"

#include <string>
#include <list>
#include <utility> //for pair
#include <ostream>


using std::string;
using std::list;
using std::pair;
using std::ostream;


namespace fib{

class cRoot;//cyclic dependencie

class cOptionalPart{

friend class cRoot;

protected:


	/**
	 * the list with the key -value -pairs of optional information
	 */
	list< pair<string,string> > optionalInformation;

	
	/**
	 * This number will be increased with each update.
	 * With it, it can be checked if this optional part is changed.
	 */
	unsigned long ulVersion;
	
	/**
	 * The type of the compression.
	 * Possible typs are:
	 * 	0: no compression
	 * 	1: The data is compressed in the zlib format. This is a Warper
	 * 		(documented in RFC 1950) for a deflate stream (lossless data
	 * 		compression, documented in RFC 1951).
	 */
	unsignedIntFib uiCompressionType;
	
//the folowing datatyps are just for intern use
	/**
	 * The compressed data of this optional part version
	 * @see ulCompressedDataVersion.
	 * If ulCompressedDataVersion and @see ulVersion are equal the
	 * compressed data is actual and can be used.
	 */
	mutable char * pCompressedData;
	
	/**
	 * The size in byts of the compressed data @see pCompressedData of
	 * this optional part.
	 */
	mutable size_t uiCompressedDataSize;
	
	/**
	 * The version number of the compressed data @see pCompressedData of
	 * this optional part.
	 * If ulCompressedDataVersion and @see ulVersion are equal the
	 * compressed data is actual and can be used.
	 */
	mutable unsigned long ulCompressedDataVersion;
	

#ifdef TEST
public: //make the following constructor public for the test
#endif

	/**
	 * The constructor for the optionalpart.
	 */
	cOptionalPart();

	/**
	 * The destructor for the optionalpart.
	 */
	virtual ~cOptionalPart();

	
	/**
	 * This Method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cOptionalPart *clone() const;


public:


	/**
	 * @return returns the number of entries in the optional part
	 */
	unsignedLongFib getNumberOfEntries() const;


	/**
	 * This method returns the ulEntryNumber'th entry of the optional part 
	 * list.
	 * If ther is no ulEntryNumber'th entry a pair with two empty strings is
	 * returend;
	 *
	 * @param ulEntryNumber the number of the entry in the optional list of
	 * 	the entry to return (counting begins with 1)
	 * @return the ulEntryNumber'th entry of the optional part list or a pair
	 * 	with to empty strings if an ulEntryNumber'th entry dosn't exists;
	 * 	the returned pair is an (key, value)  -pair
	 */
	pair< string, string > getEntry( unsignedLongFib ulEntryNumber ) const;


	/**
	 * This method returns all entries which have the given key szKey as
	 * ther full key (if bFullBegin=true) or as the begining of ther key
	 * (if bFullBegin=false) .
	 *
	 * @param szKey the key for which the entries are to return
	 * @param bFullBegin if true (the standardvalue) the given key szKey
	 * 	is the complete key to be found, else the key szKey is just the
	 * 	beginning of the key to be found
	 * @return a list with the key -value -pairs for the given key szKey;
	 * 	the returned pairs are an (key, value)  -pairs
	 */
	list< pair<string,string> > getEntries( string szKey,
		bool bFullBegin=true ) const;


	/**
	 * This method returns all entries which have the given szKeyPart as an
	 * part of ther key.
	 *
	 * @param szKeyPart the part of the keys for which the entries are to
	 * 	be return
	 * @return a list with the key -value -pairs with szKeyPart as part of
	 * 	ther key; the returned pairs are an (key, value)  -pairs
	 */
	list< pair<string,string> > findKeyPart( string szKeyPart ) const;


	/**
	 * This method ads the given key szKey and value szValue pair to the
	 * optionalpart list.
	 *
	 * @param szKey the key of the entry to add
	 * @param szValue the value of the entry to add
	 * @param ulPosition the position on which in the optional part list
	 * 	the new entry should be added (counting begins with 1);
	 * 	the standardvalue is 0 to add the entry on the end of the list
	 * @return the position wher the new entry was added to the optional
	 * 	part list (counting begins with 1)
	 */
	unsignedLongFib addEntry( string szKey, string szValue,
		unsignedLongFib ulPosition=0 );


	/**
	 * This method deletes the ulEntryNumber'th entry of the optional part
	 * list.
	 *
	 * @param ulEntryNumber the number of the entry in the optional list of
	 * 	the entry to delete (counting begins with 1)
	 * @return true if the entry was deleted, else false
	 */
	bool deleteEntry( unsignedLongFib ulEntryNumber );


	/**
	 * This method deletes all entries which have the given key szKey as
	 * ther full key (if bFullBegin=true) or as the begining of ther key
	 * (if bFullBegin=false) .
	 *
	 * @param szKey the key for which the entries are to delete
	 * @param bFullBegin if true (the standardvalue) the given key szKey
	 * 	is the complete key to be found, else the key szKey is just the
	 * 	beginning of the key to be found
	 * @return the number of deleted entries
	 */
	unsignedLongFib deleteEntries( string szKey,
		bool bFullBegin=true );

	
	/**
	 * This method stores this optionalpart in the XML -format into the
	 * given stream.
	 * example:
	 * <optionalpart>
	 * 	<pair key="copyright" value="GNU GPL 3"/>
	 * 	<pair key="type" value="die Berliner Mauer"/>
	 * </optionalpart>
	 *
	 * @param ostream the stream where this optionalpart should be stored to
	 * @return true if this optionalpart is stored, else false
	 */
	virtual bool storeXml( ostream & ostream ) const;
	
	/**
	 * This method restores this optionalpart in the XML-format from an
	 * an TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node wher the optionalpart is stored in
	 * @return an integervalue with the errorvalue
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 */
	virtual intFib restoreXml( const TiXmlElement * pXmlElement );

	/**
	 * This method evaluades the size of the optionalpart in bits in the
	 * compressed file form.
	 *
	 * @see store()
	 * @see restore()
	 * @see setCompressionType()
	 * @see uiCompressionType
	 * @see actualizeCompressData()
	 * @see cFibElement::getCompressedSize()
	 * @return the size of the optionalpart in bits in the compressed form
	 */
	virtual unsignedLongFib getCompressedSize() const;

	/**
	 * This method stores this optionalpart in the compressed fib-format
	 * (with the deflate -algorithmus) into the given stream.
	 *
	 * @see restore()
	 * @see setCompressionType()
	 * @see uiCompressionType
	 * @see actualizeCompressData()
	 * @see cFibElement::store()
	 * @param stream the stream where this optionalpart should be stored to
	 * @return true if the optionalpart are stored, else false
	 */
	virtual bool store( ostream & stream ) const;

	/**
	 * This method restores the optionalpart from a bitstream, wher it is
	 * stored in the compressed fib-format with the set compression type.
	 *
	 * @see store()
	 * @see setCompressionType()
	 * @see uiCompressionType
	 * @see actualizeCompressData()
	 * @see cFibElement::store()
	 * @param iBitStream the stream where this optionalpart is stored to in,
	 * 	because this stream is an cReadBits, any number of bits can be
	 * 	readed from it
	 * @param ulBytsToRead the nuber of byts the optional part is long,
	 * 	if 0 (defaultvalue) it will be read till the end of the stream is reached
	 * @return the errorvalue
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid stream
	 * 		- -2 loading error, invalid data in stream
	 * 		- 1 loading warning, invalid data in stream, error could be corrected
	 * 		- 2 loading warning, invalid data in stream, maybe the loaded
	 * 			object is wrong
	 */
	virtual intFib restore( cReadBits & iBitStream, const unsigned long ulBytsToRead = 0 );
	
	/**
	 * This method sets the compression type of the optional part for
	 * compressed storing.
	 * Possible typs are:
	 * 	0: no compression
	 * 	1: The data is compressed in the zlib format. This is a Warper
	 * 		(documented in RFC 1950) for a deflate stream (lossless data
	 * 		compression, documented in RFC 1951).
	 *
	 * @see uiCompressionType
	 * @see store()
	 * @see restore()
	 * @see getCompressedSize()
	 * @see actualizeCompressData()
	 * @param uiInCompressionType the compression type to set,
	 * 	standard value is 1 fo zlib compression
	 * @return true if the compression type could be set
	 */
	virtual bool setCompressionType( unsignedIntFib uiInCompressionType = 1 );

	/**
	 * This Method checks if the given optionalpart is equal to this
	 * optionalpart.
	 * Two optionalpart are equal, if they have the same entries in the
	 * same order.
	 *
	 * @param optionalPart the optionalpart to compare with this
	 * @return true if the given optionalpart is equal to this
	 * 	optionalpart, else false
	 */
	virtual bool equal( const cOptionalPart &optionalPart ) const;

	/**
	 * This Method checks if the given optionalpart is equal to this
	 * optionalpart.
	 * Two optionalpart are equal, if they have the same entries in the
	 * same order.
	 *
	 * @param optionalPart the optionalpart to compare with this
	 * @return true if the given optionalpart is equal to this
	 * 	optionalpart, else false
	 */
	virtual bool operator==( const cOptionalPart &optionalPart ) const;



protected:

	/**
	 * This method actualize the compressed data of this optional part.
	 * After it was performed successful @see ulCompressedDataVersion and
	 * @see ulVersion will be equal and pCompressedData will contain the
	 * data of this optional part.
	 *
	 * @see store()
	 * @see restore()
	 * @see getCompressedSize()
	 * @see uiCompressionType
	 * @see setCompressionType()
	 * @return true if pCompressedData contains the actual data of this
	 * 	optional part, else false
	 */
	virtual bool actualizeCompressData() const;


};//end class cOptionalPart


}//end namespace fib

#endif //___C_OPTIONAL_PART_H__
