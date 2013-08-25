/**
 * @class cOptionalPart
 * file name: cOptionalPart.cpp
 * @author Betti Oesterholz
 * @date 30.06.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the optional part of an root element.
 *
 *
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
 * This class represents the optional part for an root element.
 * The optional part consists of an list of key value pairs.
 *
 */
/*
History:
29.06.2009  Oesterholz  created
10.07.2011  Oesterholz  changes for compressed storing
18.04.2012  Oesterholz  Bugfix: replace FirstChild()->ToElement() with
	FirstChildElement()
01.08.2013  Oesterholz  method operator=() added
*/

//TODO weg
//#define DEBUG


#include "version.h"

#include "cOptionalPart.h"
#include "cRoot.h"


#include "zlib.h"

#include <algorithm>


//buffer size for loading data
#define LOAD_BUFFER_SIZE 16384UL


using namespace fib;


/**
 * The constructor for the optional part.
 */
cOptionalPart::cOptionalPart():ulVersion( 1 ), uiCompressionType( 1 ),
		pCompressedData( NULL ), uiCompressedDataSize( 0 ),
		ulCompressedDataVersion( 0 ){
//nothing ro do
}

/**
 * The desstructor for the optional part.
 */
cOptionalPart::~cOptionalPart(){
	
	if ( pCompressedData ){
		free( pCompressedData );
	}
}


/**
 * This method clones this object.
 *
 * @return a clone of this object
 */
cOptionalPart *cOptionalPart::clone() const{

	cOptionalPart * optionalPartClone = new cOptionalPart();
	
	for ( unsignedLongFib actualEntry = 1; actualEntry <= getNumberOfEntries();
			actualEntry++ ){
		
		pair< string, string > entryToAdd = getEntry( actualEntry );
		optionalPartClone->addEntry( entryToAdd.first, entryToAdd.second,
			actualEntry );
	}
	//copy the compressed data
	if ( pCompressedData != NULL ){
		optionalPartClone->uiCompressedDataSize = uiCompressedDataSize;
		optionalPartClone->pCompressedData = ((char*)(malloc( uiCompressedDataSize + 1 )));
		memcpy( optionalPartClone->pCompressedData, pCompressedData,
			uiCompressedDataSize );
	}

	return optionalPartClone;
}




/**
 * @return returns the number of entries in the optional part
 */
unsignedLongFib cOptionalPart::getNumberOfEntries() const{
	
	return optionalInformation.size();
}


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
pair< string, string > cOptionalPart::getEntry(
		unsignedLongFib ulEntryNumber ) const{

	if ( ulEntryNumber < 1 ){
		return pair< string, string >("","");
	}

	//get the iterator for the position ulEntryNumber
	list< pair< string, string > >::const_iterator actualListElement=
		optionalInformation.begin();
	
	while ( (ulEntryNumber != 1) &&
			(actualListElement != optionalInformation.end()) ){
		ulEntryNumber--;
		actualListElement++;
	}
	//no such position ulEntryNumber -> can't return entry
	if ( actualListElement == optionalInformation.end() ){
		return pair< string, string >("","");
	}

	return (*actualListElement);
}


/**
 * This method returns all entries which have the given key szKey as
 * ther full key (if bFullBegin=true) or as the begining of ther key
 * (if bFullBegin=false) .
 *
 * @param szKey the key for which the entries are to return
 * @param bFullBegin if true (the standardvalue) the given key szKey
 * 	is the complete key to be found, else the key szKey is just the
 * 	beginning of the key to be found
 * @return a list with the key value pairs for the given key szKey;
 * 	the returned pairs are an (key, value)  -pairs
 */
list< pair<string,string> > cOptionalPart::getEntries( string szKey,
		bool bFullBegin ) const{

	list< pair< string, string > > foundedEntries;
	
	/*search for entries with the given name*/
	for ( list< pair<string,string> >::const_iterator
			actualListElement = optionalInformation.begin();
			actualListElement != optionalInformation.end(); actualListElement++ ){
		
		if ( bFullBegin ){
			//search for complete key
			if ( szKey == actualListElement->first ){
				//entry for the key founded
				foundedEntries.push_back( *actualListElement );
			}
		}else{
			if ( szKey.compare( 0, szKey.size(), actualListElement->first, 0, szKey.size() )==0 ){
				//entry for the key founded
				
				foundedEntries.push_back( *actualListElement );
			}
		}
	}
	return foundedEntries;
}


/**
 * This method returns all entries which have the given szKeyPart as an
 * part of ther key.
 *
 * @param szKeyPart the part of the keys for which the entries are to
 * 	be return
 * @return a list with the key value pairs with szKeyPart as part of
 * 	ther key; the returned pairs are an (key, value)  -pairs
 */
list< pair<string,string> > cOptionalPart::findKeyPart( string szKeyPart ) const{
	
	list< pair< string, string > > foundedEntries;
	
	/*search for entries with the given name*/
	for ( list< pair<string,string> >::const_iterator
			actualListElement = optionalInformation.begin();
			actualListElement != optionalInformation.end(); actualListElement++ ){
		
		if ( actualListElement->first.find( szKeyPart ) != string::npos ){
			//entry for the key founded
			foundedEntries.push_back( *actualListElement );
		}
	}

	return foundedEntries;
}


/**
 * This method ads the given key szKey and value szValue pair to the
 * optional part list.
 *
 * @param szKey the key of the entry to add
 * @param szValue the value of the entry to add
 * @param ulPosition the position on which in the optional part list
 * 	the new entry should be added (counting begins with 1);
 * 	the standardvalue is 0 to add the entry on the end of the list
 * @return the position wher the new entry was added to the optional
 * 	part list (counting begins with 1)
 */
unsignedLongFib cOptionalPart::addEntry( string szKey, string szValue, unsignedLongFib ulPosition ){
	
	ulVersion++;//this optional part changed
	
	if ( ulPosition < 1 ){
		//add the pair to the front of the optional part list
		optionalInformation.push_back( pair<string,string>( szKey, szValue ) );
		return (unsignedLongFib)( optionalInformation.size() );
	}

	//get the iterator for the position ulPosition
	list< pair<string,string> >::iterator actualListElement =
		optionalInformation.begin();
	
	unsignedLongFib ulEntryNumber = ulPosition;
	
	while ( (ulEntryNumber != 1) &&
			(actualListElement != optionalInformation.end()) ){
		ulEntryNumber--;
		actualListElement++;
	}
	//no such position ulEntryNumber -> add to the end of the entry list
	if ( actualListElement == optionalInformation.end() ){
		optionalInformation.push_back( pair<string,string>( szKey, szValue ) );
		return (unsignedLongFib)( optionalInformation.size() );
	}
	//insert on the founded position
	optionalInformation.insert( actualListElement,
		pair<string,string>( szKey, szValue ) );
	return ulPosition;

}


/**
 * This method deletes the ulEntryNumber'th entry of the optional part
 * list.
 *
 * @param ulEntryNumber the number of the entry in the optional list of
 * 	the entry to delete (counting begins with 1)
 * @return true if the entry was deleted, else false
 */
bool cOptionalPart::deleteEntry( unsignedLongFib ulEntryNumber ){

	if ( ulEntryNumber < 1 ){
		//no entry to delete
		return false;
	}

	//get the iterator for the position ulEntryNumber
	list< pair<string,string> >::iterator actualListElement=
		optionalInformation.begin();
	
	while ( (ulEntryNumber != 1) &&
			(actualListElement != optionalInformation.end()) ){
		ulEntryNumber--;
		actualListElement++;
	}
	if ( actualListElement == optionalInformation.end() ){
		//no such position ulEntryNumber -> can't delete entry
		return false;
	}
	//delete founded entry
	optionalInformation.erase( actualListElement );
	
	ulVersion++;//this optional part changed
	return true;

}


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
unsignedLongFib cOptionalPart::deleteEntries( string szKey, bool bFullBegin ){
	
	unsignedLongFib ulValuesDeleted = (unsignedLongFib)(0);
	
	/*search for entries with the given name*/
	for ( list< pair<string,string> >::iterator
			actualListElement = optionalInformation.begin();
			actualListElement != optionalInformation.end(); ){
		
		if (bFullBegin){
			//search for complete key
			if ( szKey == actualListElement->first ){
				//entry for the key founded
				actualListElement = optionalInformation.erase( actualListElement );
				ulValuesDeleted++;
			}else{
				actualListElement++;
			}
		}else{
			if ( szKey.compare( 0, szKey.size(), actualListElement->first, 0, szKey.size() ) == 0 ){
				//entry for the key founded
				
				actualListElement = optionalInformation.erase( actualListElement );
				ulValuesDeleted++;
			}else{
				actualListElement++;
			}
		}
	}
	ulVersion++;//this optional part changed
	return ulValuesDeleted;
}


/**
 * This method stores this optional part in the XML format into the
 * given stream.
 * example:
 * <optionalpart>
 * 	<pair key="copyright" value="GNU GPL 3"/>
 * 	<pair key="type" value="die Berliner Mauer"/>
 * </optionalpart>
 *
 * @param ostream the stream where this optional part should be stored to
 * @return true if this optional part is stored, else false
 */
bool cOptionalPart::storeXml( ostream & ostream ) const{
	
	ostream<<"<optionalpart>"<<endl;
	//write the entries
	for ( list< pair<string,string> >::const_iterator
			actualListElement = optionalInformation.begin();
			actualListElement != optionalInformation.end(); 
			actualListElement++ ){
		
		ostream<<"<pair key=\""<< actualListElement->first <<"\" value=\""<<
			actualListElement->second <<"\"/>"<<endl;
	}
	ostream<<"</optionalpart>"<<endl;
	return true;
}


/**
 * This method restores the optional part in the XML format from an
 * an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node wher the optional part is stored in
 * @return an integervalue with the errorvalue
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in TiXmlElement
 * 		- 1 loading warning, invalid data in TiXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in TiXmlElement, maybe the loaded
 * 			object is wrong
 */
intFib cOptionalPart::restoreXml( const TiXmlElement * pXmlElement ){
	
	//check the element type
	if ( pXmlElement == NULL ){
		//Error: noting to restore
		return -1;
	}
	string szElementType( pXmlElement->Value() );
	if ( szElementType != "optionalpart" ){
		//Error: wrong element type to restore
		return -2;
	}
	intFib iReturnValue = 0;
	
	optionalInformation.clear();

	//restore the elements of the optional part
	const TiXmlElement * pXmlElementPair = NULL;
	if ( pXmlElement->FirstChild() ){
		
		pXmlElementPair = pXmlElement->FirstChildElement();
	}

	for( ; pXmlElementPair; pXmlElementPair = pXmlElementPair->NextSiblingElement() ){
	
		string szElementName = pXmlElementPair->Value();
		
		if ( szElementName == "pair" ){
			const char * szXmlKey = pXmlElementPair->Attribute( "key" );
			const char * szXmlValue = pXmlElementPair->Attribute( "value" );
			
			if ( (szXmlKey == NULL) || (szXmlValue == NULL) ){
				//Warning: The optional part pair isn't correct
				iReturnValue = 2;
			}else{
				addEntry( string( szXmlKey ), string( szXmlValue ) );
			}
		
		}else{
			//Warning: Unknown element type.
			iReturnValue = 2;
			continue;
		}
	}

	return iReturnValue;
}


/**
 * This method evaluades the size of the optional part in bits in the
 * compressed file form.
 *
 * @see store()
 * @see restore()
 * @see setCompressionType()
 * @see uiCompressionType
 * @see actualizeCompressData()
 * @see cFibElement::getCompressedSize()
 * @return the size of the optional part in bits in the compressed form
 */
unsignedLongFib cOptionalPart::getCompressedSize() const{
	
	//actualize compressed data
	actualizeCompressData();
	
	return (uiCompressedDataSize * 8) + 16;
}


/**
 * This method stores this optional part in the compressed Fib format
 * (with the deflate -algorithmus) into the given stream.
 *
 * @see restore()
 * @see setCompressionType()
 * @see uiCompressionType
 * @see actualizeCompressData()
 * @see cFibElement::store()
 * @param stream the stream where this optional part should be stored to
 * @return true if the optional part are stored, else false
 */
bool cOptionalPart::store( ostream & stream ) const{
	
	//actualize compressed data
	if ( ! actualizeCompressData() ){
		return false;
	}
	//store the compression type
	stream.write( ((char*)(&uiCompressionType)), 2 );
	
	//store the compressed data
	stream.write( pCompressedData, uiCompressedDataSize );
	
	return true;
}


/**
 * This method restores the optional part from a bitstream, wher it is
 * stored in the compressed Fib format with the set compression type.
 *
 * @see store()
 * @see setCompressionType()
 * @see uiCompressionType
 * @see actualizeCompressData()
 * @see cFibElement::store()
 * @param iBitStream the stream where this optional part is stored to in,
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
intFib cOptionalPart::restore( cReadBits & iBitStream, const unsigned long ulBytsToRead ){
	
	DEBUG_OUT_L2(<<"cOptionalPart::restore( iBitStream"<<&iBitStream<<", ulBytsToRead="<<ulBytsToRead<<" ) started"<<endl<<flush);

	if ( ( ulBytsToRead != 0 ) && ( ulBytsToRead <= 3 ) ){
		//minimum is 3 byte for the compressed optional part
		DEBUG_OUT_EL2(<<"cOptionalPart::restore() end: minimum is 3 byte for the compressed optional part"<<endl<<flush);
		return -2;
	}
	
	//read compression type
	unsigned long uiCompressionTypeLoaded = 0;
	const unsigned int uiBitsReadCompressionType =
		iBitStream.readBits( uiCompressionTypeLoaded, 16 );
	if ( ( uiBitsReadCompressionType != 16 ) ||
			( ! iBitStream.getStream()->good() ) ){
		DEBUG_OUT_EL2(<<"cOptionalPart::restore() end Error: compression type not read"<<endl<<flush);
		return -2;
	}
	DEBUG_OUT_L2(<<"uiCompressionTypeLoaded="<<uiCompressionTypeLoaded<<endl<<flush);
		
	unsigned long ulBytsReaded = 2;
	
	if ( ( uiCompressionTypeLoaded != 0 ) &&
			( uiCompressionTypeLoaded != 1 ) ){
		//unknown compression type
		DEBUG_OUT_EL2(<<"cOptionalPart::restore() end Error: unknown compression type"<<endl<<flush);
		return -2;
	}
	
	/*The list with the readed data blocks.
	The pair elements are:
		first: a readed data block (beware you have to delete them)
		second: the number of byts the data block contains
	*/
	list< pair< char *, unsigned long > > liReadedData;
	unsigned long ulBytsUncompressed = ulBytsReaded;
	
	char * pUncompressedData = NULL;
	//restore compressed data
	DEBUG_OUT_L2(<<"restore compressed data (max buffer size="<<LOAD_BUFFER_SIZE<<")"<<endl<<flush);
	if ( uiCompressionTypeLoaded == 0 ){
		//restore unkompressed data
		DEBUG_OUT_L2(<<"restore unkompressed data"<<endl<<flush);
		char * pReadedDataBlock;
		do{
			const unsigned long uiSizeNextBlock =
				( ulBytsToRead == 0 ) ? LOAD_BUFFER_SIZE :
					min( ( ulBytsToRead - ulBytsReaded ), LOAD_BUFFER_SIZE );
			
			pReadedDataBlock = ((char*)(malloc( uiSizeNextBlock + 1 )));
			
			const unsigned int uiBitsReadOfBlock =
				iBitStream.readBits( pReadedDataBlock, uiSizeNextBlock * 8 );
			if ( ! iBitStream.getStream()->good() ){
				//delete data blocks from memory
				DEBUG_OUT_EL3(<<"delete data blocks from memory"<<endl<<flush);
				while( ! liReadedData.empty() ){
					free( liReadedData.back().first );
					liReadedData.pop_back();
				}
				DEBUG_OUT_EL2(<<"cOptionalPart::restore() end Error: block read"<<endl<<flush);
				return -2;
			}
			const unsigned long uiBytsInBlock = uiBitsReadOfBlock / 8;
		
			liReadedData.push_back(
				make_pair( pReadedDataBlock, uiBytsInBlock ) );
			ulBytsReaded += uiBytsInBlock;
		}while ( ( ! iBitStream.getStream()->eof() ) &&
			( ( ulBytsToRead == 0 ) || ( ulBytsReaded < ulBytsToRead ) ) );
		
		//concatenate restored data blocks
		if ( pCompressedData ){
			free( pCompressedData );
		}
		uiCompressedDataSize = ulBytsReaded - 2;
		pCompressedData = ((char*)(malloc( ulBytsReaded )));
		
		char * pActualPosition = pCompressedData;
		
		while( ! liReadedData.empty() ){
			
			const pair< char *, unsigned long > & paActualDataBlock =
				liReadedData.front();
			
			memcpy( pActualPosition, paActualDataBlock.first,
				paActualDataBlock.second );
			
			pActualPosition += paActualDataBlock.second;
			
			free( paActualDataBlock.first );
			liReadedData.pop_front();
		}
		//compressed data is uncompressed data
		pUncompressedData = pCompressedData;
		ulBytsUncompressed = ulBytsReaded;
		
		DEBUG_OUT_L2(<<"restore unkompressed data done"<<endl<<flush);
	}else{//( uiCompressionTypeLoaded == 1 )
		DEBUG_OUT_L2(<<"restore compressed date compression type 1"<<endl<<flush);
		/*The list with the readed data blocks.
		The pair elements are:
			first: a readed data block (beware you have to delete them)
			second: the number of byts the data block contains
		*/
		list< pair< char *, unsigned long > > liUncompressedData;
		
		//compressed with the zlib deflate algorithm
		int iRetInflate = 0;
		z_stream zStream;
		
		/* allocate inflate state */
		zStream.zalloc = Z_NULL;
		zStream.zfree  = Z_NULL;
		zStream.opaque = Z_NULL;
		zStream.avail_in = 0;
		zStream.next_in  = Z_NULL;
		const int iRetInflateInit = inflateInit( &zStream );
		if ( iRetInflateInit != Z_OK ){
			//zlib error
			DEBUG_OUT_EL2(<<"cOptionalPart::restore() end Error: zlib init"<<endl<<flush);
			return -2;
		}
		
		/* decompress until deflate stream ends or end of file */
		do {
			//yust read ulBytsToRead byts
			const unsigned long uiSizeNextBlock =
				( ulBytsToRead == 0 ) ? LOAD_BUFFER_SIZE :
					min( ( ulBytsToRead - ulBytsReaded ), LOAD_BUFFER_SIZE );
			DEBUG_OUT_L4(<<"   read next block of size "<<uiSizeNextBlock<<endl<<flush);
			
			if ( uiSizeNextBlock == 0 ){
				//all to read data readed
				DEBUG_OUT_L2(<<"all to read data readed"<<endl<<flush);
				iRetInflate = Z_STREAM_END;
				break;
			}
			DEBUG_OUT_L4(<<"   get memory for next block: malloc( "<<uiSizeNextBlock<<" + 1 )"<<endl<<flush);
			char * pInputBuffer = ((char*)(malloc( uiSizeNextBlock + 1 )));
			DEBUG_OUT_L4(<<"   read bits into block"<<endl<<flush);
			const unsigned int uiBitsReadOfBlock =
				iBitStream.readBits( pInputBuffer, uiSizeNextBlock * 8 );
			zStream.avail_in = uiBitsReadOfBlock / 8;
			DEBUG_OUT_L4(<<"   store block to readed data: liReadedData.push_back() (with readed bits="<<uiBitsReadOfBlock<<")"<<endl<<flush);
			liReadedData.push_back(
				make_pair( pInputBuffer, zStream.avail_in ) );
			ulBytsReaded += zStream.avail_in;
			if ( ! iBitStream.getStream()->good() ){
				(void)inflateEnd( &zStream );
				//delete data blocks from memory
				DEBUG_OUT_EL3(<<"delete data blocks from memory"<<endl<<flush);
				while( ! liReadedData.empty() ){
					free( liReadedData.back().first );
					liReadedData.pop_back();
				}
				while( ! liUncompressedData.empty() ){
					free( liUncompressedData.back().first );
					liUncompressedData.pop_back();
				}
				DEBUG_OUT_EL2(<<"cOptionalPart::restore() end Error: block deflate"<<endl<<flush);
				return -2;
			}
			if ( zStream.avail_in == 0 ){
				//no new data read
				DEBUG_OUT_L2(<<"no new data read"<<endl<<flush);
				break;
			}
			zStream.next_in = ((Bytef*)(pInputBuffer));
		
			/* decompress restored data:
				run inflate() on input until output buffer not full */
			DEBUG_OUT_L4(<<"   decompress restored data"<<endl<<flush);
			do {
				zStream.avail_out = LOAD_BUFFER_SIZE;
				char * pOutputBuffer = ((char*)(malloc( LOAD_BUFFER_SIZE + 1 )));
				zStream.next_out = ((Bytef*)(pOutputBuffer));
				iRetInflate = inflate( &zStream, Z_NO_FLUSH );
				assert( iRetInflate != Z_STREAM_ERROR );  /* state not clobbered */
				switch ( iRetInflate ) {
					case Z_NEED_DICT:
					case Z_DATA_ERROR:
					case Z_MEM_ERROR:
							(void)inflateEnd( &zStream );
							//delete data blocks from memory
							DEBUG_OUT_EL3(<<"delete data blocks from memory"<<endl<<flush);
							while( ! liReadedData.empty() ){
								free( liReadedData.back().first );
								liReadedData.pop_back();
							}
							while( ! liUncompressedData.empty() ){
								free( liUncompressedData.back().first );
								liUncompressedData.pop_back();
							}
							free( zStream.next_out );
							return -2;
				};
				//store restored data
				const unsigned long uiBytsInBlock =
					LOAD_BUFFER_SIZE - zStream.avail_out;
				
				liUncompressedData.push_back(
					make_pair( pOutputBuffer, uiBytsInBlock ) );
				ulBytsUncompressed += uiBytsInBlock;
				
				DEBUG_OUT_L4(<<"   decompress byts: "<<uiBytsInBlock<<" (all byts uncompressed: "<<ulBytsUncompressed<<")"<<endl<<flush);
				
			}while ( zStream.avail_out == 0 );
		
			/* done when inflate() says it's done */
		}while ( iRetInflate != Z_STREAM_END );
		
		/* clean up and return */
		DEBUG_OUT_EL2(<<"clean up and return"<<endl<<flush);
		(void)inflateEnd( &zStream );
		if ( iRetInflate != Z_STREAM_END ){
			//delete data blocks from memory
			DEBUG_OUT_EL3(<<"delete data blocks from memory"<<endl<<flush);
			while( ! liReadedData.empty() ){
				free( liReadedData.back().first );
				liReadedData.pop_back();
			}
			while( ! liUncompressedData.empty() ){
				free( liUncompressedData.back().first );
				liUncompressedData.pop_back();
			}
			DEBUG_OUT_EL2(<<"cOptionalPart::restore() end Error: inflate"<<endl<<flush);
			return -2;
		}
		
		//concatenate restored compressed data blocks
		if ( pCompressedData ){
			free( pCompressedData );
		}
		uiCompressedDataSize = ulBytsReaded - 2;
		DEBUG_OUT_EL2(<<"get memory for compressed data field of "<<ulBytsReaded<<" + 1 byts"<<endl<<flush);
		pCompressedData = ((char*)(malloc( ulBytsReaded + 1 )));
		
		char * pActualPosition = pCompressedData;
		
		DEBUG_OUT_EL2(<<"transfer readed data from readed buffers to compressed data block"<<endl<<flush);
		while( ! liReadedData.empty() ){
			
			const pair< char *, unsigned long > & paActualDataBlock =
				liReadedData.front();
			
			memcpy( pActualPosition, paActualDataBlock.first,
				paActualDataBlock.second );
			
			pActualPosition += paActualDataBlock.second;
			
			free( paActualDataBlock.first );
			liReadedData.pop_front();
		}
		
		/*build uncompressed data field
		-> concatenate restored compressed data blocks*/
		DEBUG_OUT_EL2(<<"get memory for uncompressed data field of "<<ulBytsUncompressed<<" + 1 byts"<<endl<<flush);
		pUncompressedData = ((char*)(malloc( ulBytsUncompressed + 1 )));
		
		pActualPosition = pUncompressedData;
		
		DEBUG_OUT_EL2(<<"free data blocks with compressed data from memory"<<endl<<flush);
		while( ! liUncompressedData.empty() ){
			
			const pair< char *, unsigned long > & paActualDataBlock =
				liUncompressedData.front();
			DEBUG_OUT_EL4(<<"copy "<<paActualDataBlock.second<<" block byts to uncompressed data"<<endl<<flush);
			
			memcpy( pActualPosition, paActualDataBlock.first,
				paActualDataBlock.second );
			
			pActualPosition += paActualDataBlock.second;
			
			free( paActualDataBlock.first );
			liUncompressedData.pop_front();
		}
		
	}
	DEBUG_OUT_L2(<<"reading and decompressing data done"<<endl<<flush);

	//read the number of entries
	char * pActualPosition = pUncompressedData;
	unsigned long long ulNumberOfEntries = 0;
	memcpy( ((char*)( & ulNumberOfEntries)), pActualPosition, 8 );
	DEBUG_OUT_L2(<<"entries readed: "<<ulNumberOfEntries<<endl<<flush);
	
	pActualPosition += 8;
	
	//read the coding style
	unsigned long uiCodingStyle = 0;
	memcpy( ((char*)( & uiCodingStyle)), pActualPosition, 2 );
	DEBUG_OUT_L2(<<"coding style: "<<uiCodingStyle<<endl<<flush);
	
	pActualPosition += 2;
	//check the coding style
	intFib iReturnValue = 0;
	if ( uiCodingStyle != 0 ){
		//TODO coding styls not implemented jet; only UTF-8 could work
		DEBUG_OUT_EL2(<<"cOptionalPart::restore() Warning: coding styls not implemented jet; only UTF-8 could work"<<endl<<flush);
		iReturnValue = 2;
	}
	//delete old key value elements
	DEBUG_OUT_L2(<<"delete old key value elements"<<endl<<flush);
	optionalInformation.clear();
	
	//find key value parts in restored data
	DEBUG_OUT_L2(<<"find key value parts in restored data"<<endl<<flush);
	//if bReadKey is true read a key else an value
	bool bReadKey = true;
	string szKey;
	string szValue;
	const char * pEndPosition = pUncompressedData + (ulBytsUncompressed - 2);
	for ( ; pActualPosition != pEndPosition; pActualPosition++ ){
		
		if ( (*pActualPosition) != 0x00 ){
			
			if ( bReadKey ){
				szKey.push_back( (*pActualPosition) );
			}else{
				szValue.push_back( (*pActualPosition) );
			}
		}else{//0 char readed -> null terminated strings -> read next entry
			if ( ! bReadKey ){
				//store readed key value pair
				DEBUG_OUT_L2(<<"add new entry (key=\""<<szKey<<"\", value=\""<<szValue<<"\")"<<endl<<flush);
				addEntry( szKey, szValue );
				//read next key value pair
				szKey.clear();
				szValue.clear();
				bReadKey = true;
			}else{
				//read value for the key
				bReadKey = false;
			}
		}
	}
	ulVersion++;
	ulCompressedDataVersion = ulVersion;
	uiCompressionType = uiCompressionTypeLoaded;
	
	if ( pUncompressedData != pCompressedData ){
		DEBUG_OUT_L2(<<"free buffer with uncompressed data"<<endl<<flush);
		free( pUncompressedData );
	}
	
	DEBUG_OUT_L2(<<"cOptionalPart::restore( iBitStream"<<&iBitStream<<", ulBytsToRead="<<ulBytsToRead<<" ) done returnvalue="<<iReturnValue<<endl<<flush);
	return iReturnValue;
}


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
bool cOptionalPart::setCompressionType( unsignedIntFib uiInCompressionType ){
	
	
	if ( ( uiInCompressionType != 0 ) && ( uiInCompressionType != 1 )){
		//no valid compression type
		return false;
	}
	if ( uiCompressionType == uiInCompressionType ){
		//compression type allready correct
		return true;
	}
	uiCompressionType = uiInCompressionType;
	ulVersion++;
	return true;
}


/**
 * This method checks if the given optional part is equal to this
 * optional part.
 * Two optional part are equal, if they have the same entries in the
 * same order.
 *
 * @param optionalPart the optional part to compare with this
 * @return true if the given optional part is equal to this
 * 	optional part, else false
 */
bool cOptionalPart::equal( const cOptionalPart & optionalPart ) const{
	
	return ((*this) == optionalPart);
}


/**
 * This method checks if the given optional part is equal to this
 * optional part.
 * Two optional part are equal, if they have the same entries in the
 * same order.
 *
 * @param optionalPart the optional part to compare with this
 * @return true if the given optional part is equal to this
 * 	optional part, else false
 */
bool cOptionalPart::operator==( const cOptionalPart &optionalPart ) const{
	
	return (optionalInformation == optionalPart.optionalInformation);
}


/**
 * This method assigns the values of the given optional part to this
 * optional part.
 * After calling this operator, this optional part will be equal to
 * the given optional part.
 *
 * @see equal()
 * @param optionalPart the optional part to copy
 */
cOptionalPart & cOptionalPart::operator=( const cOptionalPart & optionalPart ){
	
	optionalInformation = optionalPart.optionalInformation;
	ulVersion = optionalPart.ulVersion;
	uiCompressionType = optionalPart.uiCompressionType;
	
	if ( pCompressedData ){
		//delete old compressed data
		delete pCompressedData;
		pCompressedData = NULL;
	}
	
	//copy the compressed data
	uiCompressedDataSize = optionalPart.uiCompressedDataSize;
	if ( optionalPart.pCompressedData != NULL ){
		//copy the existing compressed optional data
		pCompressedData = ((char*)(malloc( uiCompressedDataSize + 1 )));
		memcpy( pCompressedData, optionalPart.pCompressedData,
			uiCompressedDataSize );
	}
	ulCompressedDataVersion = optionalPart.ulCompressedDataVersion;
	
	return *this;
}

//protected:

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
bool cOptionalPart::actualizeCompressData() const{
	
	if ( ulCompressedDataVersion == ulVersion ){
		//compressed data actual
		return true;
	}
	
	//evalue needed space for uncompressed data
	unsigned long ulBytsNeededUC = 10;//number of entries + coding style
	
	for ( list< pair<string,string> >::const_iterator
			itrEntry = optionalInformation.begin();
			itrEntry != optionalInformation.end(); itrEntry++ ){
		
		ulBytsNeededUC += itrEntry->first.size() + itrEntry->second.size() + 2;
	}
	char * pUncompressedData = ((char*)(malloc( ulBytsNeededUC + 2 )));
	
	//store the uncompressed data
	//store the number of entries
	char * pActualPosition = pUncompressedData;
	const unsigned long ulNumberOfEntries = optionalInformation.size();
	memcpy( pActualPosition, ((char*)( & ulNumberOfEntries)), 8 );
	pActualPosition += 8;
	
	//store the coding style
	//TODO add other coding styles
	const unsigned int uiCodingStyle = 0;
	memcpy( pActualPosition, ((char*)( & uiCodingStyle)), 2 );
	pActualPosition += 2;
	
	//store the entries
	for ( list< pair<string,string> >::const_iterator
			itrEntry = optionalInformation.begin();
			itrEntry != optionalInformation.end(); itrEntry++ ){
		
		const string & szKey = itrEntry->first;
		const size_t uiKeySize = szKey.size() + 1;
		
		memcpy( pActualPosition, szKey.c_str(), uiKeySize );
		pActualPosition += uiKeySize;
		
		const string & szValue = itrEntry->second;
		const size_t uiValueSize = szValue.size() + 1;
		
		memcpy( pActualPosition, szValue.c_str(), uiValueSize );
		pActualPosition += uiValueSize;
	}
	//generate compressed data
	if ( uiCompressionType == 0 ){
		
		//concatenate restored data blocks
		if ( pCompressedData ){
			free( pCompressedData );
		}
		
		uiCompressedDataSize = ulBytsNeededUC;
		pCompressedData = pUncompressedData;
		
	}else{// ( uiCompressionType == 1 )
		z_stream zlibStream;
		
		/* allocate inflate state */
		zlibStream.zalloc = Z_NULL;
		zlibStream.zfree = Z_NULL;
		zlibStream.opaque = Z_NULL;
		const int iInflateInitRet = deflateInit( &zlibStream, Z_BEST_COMPRESSION );
		if ( iInflateInitRet != Z_OK ){
			free( pUncompressedData );
			(void)deflateEnd( &zlibStream );
			return false;
		}
		zlibStream.avail_in = ulBytsNeededUC;
		zlibStream.next_in = ((Bytef*)(pUncompressedData));
		//the data is in great parts text
		zlibStream.data_type = Z_TEXT;
		
		/*The list with the compressed data blocks.
		The pair elements are:
			first: a compressed data block (beware you have to delete them)
			second: the number of byts the data block contains
		*/
		list< pair< char *, unsigned long > > liCompressedData;
		unsigned long ulCompressedByts = 0;
		
		int iDeflateReturn;
		/* run deflate() on input until output buffer not full, finish
			compression if all of source has been read in */
		do{
			zlibStream.avail_out = LOAD_BUFFER_SIZE;
			char * pOutputBuffer = ((char*)(malloc( LOAD_BUFFER_SIZE )));
			zlibStream.next_out = ((Bytef*)(pOutputBuffer));
			iDeflateReturn = deflate( &zlibStream, Z_FINISH );    /* no bad return value */
			if ( iDeflateReturn == Z_STREAM_ERROR ){
				/* state clobbered */
				free( pUncompressedData );
				while( ! liCompressedData.empty() ){
					free( liCompressedData.back().first );
					liCompressedData.pop_back();
				}
				(void)deflateEnd( &zlibStream );
				return false;
			}
			
			const unsigned long ulBytsOfBlock =
				LOAD_BUFFER_SIZE - zlibStream.avail_out;
			
			liCompressedData.push_back(
				make_pair( pOutputBuffer, ulBytsOfBlock ) );
			ulCompressedByts += ulBytsOfBlock;
			
		}while ( zlibStream.avail_out == 0 );
		
		/* clean up */
		free( pUncompressedData );
		if ( ( zlibStream.avail_in != 0 ) ||
				( iDeflateReturn != Z_STREAM_END ) ){
			/* state clobbered */
			(void)deflateEnd( &zlibStream );
			while( ! liCompressedData.empty() ){
				free( liCompressedData.back().first );
				liCompressedData.pop_back();
			}
			
			return false;
		}
		/* clean up */
		(void)deflateEnd( &zlibStream );
		
		//produce compressed data
		uiCompressedDataSize = ulCompressedByts;
		pCompressedData = ((char*)(malloc( ulCompressedByts + 2 )));
		
		char * pActualPosition = pCompressedData;
		
		while( ! liCompressedData.empty() ){
			
			const pair< char *, unsigned long > & paActualDataBlock =
				liCompressedData.front();
			
			memcpy( pActualPosition, paActualDataBlock.first,
				paActualDataBlock.second );
			
			pActualPosition += paActualDataBlock.second;
			
			free( paActualDataBlock.first );
			liCompressedData.pop_front();
		}
	}
	
	ulCompressedDataVersion = ulVersion;
	
	return true;
}


















