/**
 * @file nBitStream
 * file name: nBitStram.cpp
 * @author Betti Oesterholz
 * @date 24.09.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements functions with which any number of bits can be
 * writen into a stream.
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
 * This file implements functions with which any number of bits can be
 * writen into a stream.
 *
 */
/*
History:
24.09.2009  Oesterholz  created
19.01.2011  Oesterholz  converting stream to binary stream under windows
16.02.2012  Oesterholz  Bugfix: clear bits from restbit not in true restbit
*/



#include "nBitStream.h"

using namespace nBitStream;


/**
 * This method stores ucBitsToStore Bits of the ulNumber into
 * the given stream.
 * It gives back the bits that, which are not yet stored into the stream.
 *
 * @param stream the stream where this ulNumber should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @param bWriteOptionalPart if true the optionalpart is written
 * @param ulNumber the unsigned number to store, bits to much will be
 * 	cuted
 * @param ucBitsToStore the bits the stored number should be long
 * @return true if the ulNumber is stored, else false
 */
bool nBitStream::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition,
		const unsigned long long & ulNumber, const unsigned char ucBitsToStore ){
	
	if ( sizeof(unsigned long long ) * 8 < ucBitsToStore ){
		//ulNumber has not engouth bits to store
		return false;
	}
	if (ucBitsToStore == 0){
		//no bits to store -> all bits to stored are stored
		return true;
	}
	
	return store( stream, cRestBits, uiRestBitPosition, (char*)&ulNumber, ucBitsToStore );
}


/**
 * This method stores ucBitsToStore Bits of the ulNumber into
 * the given stream.
 * It gives back the bits that, which are not yet stored into the stream.
 *
 * @param stream the stream where this ulNumber should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @param bWriteOptionalPart if true the optionalpart is written
 * @param ulNumber the unsigned number to store, bits to much will be
 * 	cuted
 * @param ucBitsToStore the bits the stored number should be long
 * @return true if the ulNumber is stored, else false
 */
bool nBitStream::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition,
		const unsigned long & ulNumber, const unsigned char ucBitsToStore ){
	
	if ( sizeof(unsigned long) * 8 < ucBitsToStore ){
		//ulNumber has not engouth bits to store
		return false;
	}
	if (ucBitsToStore == 0){
		//no bits to store -> all bits to stored are stored
		return true;
	}
	
	return store( stream, cRestBits, uiRestBitPosition, (char*)&ulNumber, ucBitsToStore );
}


/**
 * This method stores ucBitsToStore Bits of the ulNumber into
 * the given stream.
 * It gives back the bits that, which are not yet stored into the stream.
 *
 * @param stream the stream where this ulNumber should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @param bWriteOptionalPart if true the optionalpart is written
 * @param ulNumber the unsigned number to store, bits to much will be
 * 	cuted
 * @param ucBitsToStore the bits the stored number should be long
 * @return true if the ulNumber is stored, else false
 */
bool nBitStream::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition,
		const unsigned int & ulNumber, const unsigned char ucBitsToStore ){
	
	if ( sizeof(unsigned int) * 8 < ucBitsToStore ){
		//ulNumber has not engouth bits to store
		return false;
	}
	if (ucBitsToStore == 0){
		//no bits to store -> all bits to stored are stored
		return true;
	}
	
	return store( stream, cRestBits, uiRestBitPosition, (char*)&ulNumber, ucBitsToStore );
}


/**
 * This method stores ucBitsToStore Bits of the lNumber into
 * the given stream.
 * It gives back the bits that, which are not yet stored into the stream.
 *
 * @param stream the stream where this ulNumber should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @param bWriteOptionalPart if true the optionalpart is written
 * @param lNumber the signed number to store, bits to much will be
 * 	cuted
 * @param ucBitsToStore the bits the stored number should be long
 * @return true if the lNumber is stored, else false
 */
bool nBitStream::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition,
		const long long & lNumber, const unsigned char ucBitsToStore ){
	
	if ( sizeof(long long) * 8 < ucBitsToStore ){
		//ulNumber has not engouth bits to store
		return false;
	}
	if (ucBitsToStore == 0){
		//no bits to store -> all bits to stored are stored
		return true;
	}
	
	if ( 0 <= lNumber){
		//positiv number
		//set the ucBitsToStore to 0 for the positiv sign

		long long lNumberToStore = lNumber &
			(-1L >> ((sizeof(long long) * 8 + 1) - ucBitsToStore) );//for 64 Bit: (0x7FFFFFFFFFFFFFFFL >> (64 - ucBitsToStore))
		
		return store( stream, cRestBits, uiRestBitPosition, (char*)&lNumberToStore, ucBitsToStore );
	}//else negativ number
	//set the ucBitsToStore to 1 for the negativ sign
	long long lNumberToStore = lNumber |
		( ((long long)(0x01L)) << (ucBitsToStore - 1) );
	
	return store( stream, cRestBits, uiRestBitPosition, (char*)&lNumberToStore, ucBitsToStore );
}


/**
 * This method stores ucBitsToStore Bits of the lNumber into
 * the given stream.
 * It gives back the bits that, which are not yet stored into the stream.
 *
 * @param stream the stream where this ulNumber should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @param bWriteOptionalPart if true the optionalpart is written
 * @param lNumber the signed number to store, bits to much will be
 * 	cuted
 * @param ucBitsToStore the bits the stored number should be long
 * @return true if the lNumber is stored, else false
 */
bool nBitStream::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition,
		const long & lNumber, const unsigned char ucBitsToStore ){
	
	if ( sizeof(long) * 8 < ucBitsToStore ){
		//ulNumber has not engouth bits to store
		return false;
	}
	if (ucBitsToStore == 0){
		//no bits to store -> all bits to stored are stored
		return true;
	}
	
	if ( 0 <= lNumber){
		//positiv number
		//set the ucBitsToStore to 0 for the positiv sign

		long lNumberToStore = lNumber &
			(-1L >> ( (sizeof(long) * 8 + 1) - ucBitsToStore) );//for 64 Bit: (0x7FFFFFFFFFFFFFFFL >> (64 - ucBitsToStore))
		
		return store( stream, cRestBits, uiRestBitPosition, (char*)&lNumberToStore, ucBitsToStore );
	}//else negativ number
	//set the ucBitsToStore to 1 for the negativ sign
	long long lNumberToStore = lNumber |
		( 0x01L << (ucBitsToStore - 1) );
	
	return store( stream, cRestBits, uiRestBitPosition, (char*)&lNumberToStore, ucBitsToStore );
}


/**
 * This method stores ucBitsToStore Bits of the lNumber into
 * the given stream.
 * It gives back the bits that, which are not yet stored into the stream.
 *
 * @param stream the stream where this ulNumber should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @param bWriteOptionalPart if true the optionalpart is written
 * @param lNumber the signed number to store, bits to much will be
 * 	cuted
 * @param ucBitsToStore the bits the stored number should be long
 * @return true if the lNumber is stored, else false
 */
bool nBitStream::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition,
		const int & lNumber, const unsigned char ucBitsToStore ){
	
	if ( sizeof(int) * 8 < ucBitsToStore ){
		//ulNumber has not engouth bits to store
		return false;
	}
	if (ucBitsToStore == 0){
		//no bits to store -> all bits to stored are stored
		return true;
	}
	
	if ( 0 <= lNumber){
		//positiv number
		//set the ucBitsToStore to 0 for the positiv sign

		int lNumberToStore = lNumber &
			(-1L >> ( (sizeof(int) * 8 + 1) - ucBitsToStore) );//for 64 Bit: (0x7FFFFFFFFFFFFFFFL >> (64 - ucBitsToStore))
		
		return store( stream, cRestBits, uiRestBitPosition, (char*)&lNumberToStore, ucBitsToStore );
	}//else negativ number
	//set the ucBitsToStore to 1 for the negativ sign
	long long lNumberToStore = lNumber |
		( 0x01L << (ucBitsToStore - 1) );
	
	return store( stream, cRestBits, uiRestBitPosition, (char*)&lNumberToStore, ucBitsToStore );
}


/**
 * This method stores ucBitsToStore Bits of the charfield into
 * the given stream.
 * It gives back the bits that, which are not yet stored into the stream.
 *
 * @param stream the stream where this ulNumber should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @param bWriteOptionalPart if true the optionalpart is written
 * @param pcField the char field to store
 * @param uiBitsToStore the bits to store from the char field
 * @return true if the pcField is stored, else false
 */
bool nBitStream::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition,
		const char * pcField, const unsigned int uiBitsToStore ){
	
	if ( uiBitsToStore == 0 ){
		//nothing to store
		return false;
	}
	//remove ever bits not in restbit
	cRestBits = cRestBits & ( 0xFF >> ( 8 - uiRestBitPosition ));
	
	if ( uiRestBitPosition == 0 ){
		
		if ( (uiBitsToStore / 8) > 0 ){
			stream.write( pcField, uiBitsToStore / 8 );
		}
		
		uiRestBitPosition = uiBitsToStore % 8;
		if ( uiRestBitPosition != 0 ){
			cRestBits = pcField[ uiBitsToStore / 8 ];
			//remove ever bits not in restbit
			cRestBits = cRestBits & ( 0xFF >> ( 8 - uiRestBitPosition ) );
		}else{//no more bits to store restbits is 0
			cRestBits = 0x00;
		}
		
	}else{
		//the bigining is not a full byte
		unsigned int uiBytesToStore = (uiBitsToStore + 7) / 8;
		unsigned int uiRemainingBitsToStore = uiRestBitPosition + uiBitsToStore;
		
		for ( unsigned int uiActualByte = 0; uiActualByte < uiBytesToStore ;
				uiActualByte++ ){
			
			unsigned char cActualByte = pcField[ uiActualByte ];
			//the later cRestBits;= the part of the actual byte to store later
			unsigned char cRemainingBits = cActualByte;
			
			cRemainingBits = cRemainingBits >> ( 8 - uiRestBitPosition );
			
			cActualByte = cActualByte << uiRestBitPosition;
			cActualByte = cRestBits | cActualByte;
			
			if ( 8 <= uiRemainingBitsToStore ){
				stream.write( (char*)(&cActualByte), 1 );
				uiRemainingBitsToStore -= 8;
				cRestBits = cRemainingBits;
			}else{//no full byte to store
				cRestBits = cActualByte;
			}
			
		}
		uiRestBitPosition = uiRemainingBitsToStore % 8;
	}
	return true;
}



