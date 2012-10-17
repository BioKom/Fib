/**
 * @class cReadBits
 * file name: cReadBits.cpp
 * @author Betti Oesterholz
 * @date 30.01.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * With this class it is possible to read a input stream bit for bit.
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
 * With this class it is possible to read a input stream bit for bit.
 * It implements methods to read a given number of bits from a input
 * stream and buffers a number of byts of the input stream.
 *
 */
/*
History:
30.01.2009  Oesterholz  created
*/


#include "cReadBits.h"

#include "fibDatatyps.h"

#include <cstring>
#include <algorithm>

using namespace fib;



/**
 * Standardconstructor
 * Beware: Don't use istreamIn elsewher, while using it with theas class.
 * This class should only use istreamIn.
 *
 * @param istreamIn the stream to read the bits from
 * @param uiInBytsToBuffer the number of byts to buffer from the stream
 */
cReadBits::cReadBits( istream & istreamIn, unsigned int uiInBytsToBuffer ):
		uiBitsToBuffer( uiInBytsToBuffer * 8 ), uiBitPositionBuffer(0),
		uiBitReadedInBuffer( 0 ), ulBitReadedCount( 0 ){

	szByteBuffer = new char[ uiInBytsToBuffer + 1 ];
	memset( szByteBuffer, 0x00, uiInBytsToBuffer + 1);
	
	pIstream = &istreamIn;
}


/**
 * destructor
 */
cReadBits::~cReadBits(){
	
	delete[] szByteBuffer;
}


/**
 * This method reads a number of bits from the stream.
 *
 * @param pBuffer the character array wher to writes the readed bits to,
 * 	the first bit will begin at the pointer pBuffer
 * @param uiBitsToRead the number of bits to read
 * @return the number of bits readed
 */
unsigned int cReadBits::readBits( char * pBuffer, unsigned int uiBitsToRead ){
	
	if ( (pIstream == NULL) || ( ! pIstream->good() ) ){
		//can't read
		return 0;
	}
	if ( pBuffer == NULL ){
		//nowher to read to
		return 0;
	}
	if ( uiBitsToRead == 0 ){
		//done
		return 0;
	}

	unsigned char pReadedBits[ uiBitsToRead / 8 + 2 ];
	memset( pReadedBits, 0x00, uiBitsToRead / 8 + 2 );
	const unsigned int uiShift = uiBitPositionBuffer % 8;
	
	/*copy bits from the szByteBuffer into the pReadedBits buffer till the
	uiBitReadedInBuffer is reached*/
	unsigned int uiBitsReaded = 0;
	unsigned int uiByteOfReadedBits = 0;
	if ( uiShift != 0 ){
		//just a part of the first byte needed
		
		uiBitsReaded = 8 - uiShift;
		pReadedBits[ uiByteOfReadedBits ] = szByteBuffer[ uiBitPositionBuffer / 8 ];
		
		if ( uiBitsToRead < uiBitsReaded ){
			//more bits readed then needed
			unsigned char cMask = 0xFF >> ( 8 - uiShift - uiBitsToRead );
			pReadedBits[ uiByteOfReadedBits ] =
				pReadedBits[ uiByteOfReadedBits ] & cMask;
			uiBitsReaded = uiBitsToRead;
		}
		uiByteOfReadedBits++;
		uiBitPositionBuffer += uiBitsReaded;
	}
	//now uiBitPositionBuffer stands on the beginning of a byte
	
	while ( uiBitsReaded < uiBitsToRead ){
		if ( uiBitsToBuffer <= uiBitPositionBuffer ){
			//go to the start of the buffer
			uiBitPositionBuffer -= uiBitsToBuffer;
			continue;
		}
		if ( uiBitPositionBuffer == uiBitReadedInBuffer ){
			//no more newer bits to read in buffer
			break;
		}
		if ( 8 <= uiBitsToRead - uiBitsReaded ){
			//copy one byte
			pReadedBits[ uiByteOfReadedBits ] =
				 szByteBuffer[ uiBitPositionBuffer / 8 ];
			uiByteOfReadedBits++;
			uiBitPositionBuffer += 8;
			uiBitsReaded += 8;
		}else{//don't read a wool byte -> copy a part of a byte
			pReadedBits[ uiByteOfReadedBits ] =
				 szByteBuffer[ uiBitPositionBuffer / 8 ];
			//more bits readed then needed
			unsigned char cMask = 0xFF >> ( (uiBitsReaded + 8) - uiBitsToRead );
			pReadedBits[ uiByteOfReadedBits ] =
				pReadedBits[ uiByteOfReadedBits ] & cMask;
			
			uiByteOfReadedBits++;
			
			uiBitPositionBuffer += uiBitsToRead - uiBitsReaded;
			uiBitsReaded = uiBitsToRead;
			break;//done reading
		}
	}
	if ( uiBitPositionBuffer == uiBitsToBuffer ){
		//go to the start of the buffer
		uiBitPositionBuffer = 0;
	}
	//if more bits should be given back than: uiBitReadedInBuffer == uiBitPositionBuffer
	
	//read some more byts from the stream
	while ( uiBitsReaded < uiBitsToRead ){
		if ( uiBitsToBuffer <= uiBitPositionBuffer ){
			//go to the start of the buffer
			uiBitReadedInBuffer = 0;
			uiBitPositionBuffer = 0;
			continue;
		}
		unsigned char cReaded = pIstream->get();
		//check stream
		if ( ! pIstream->good() ){
			//can't read anymore + last readed byte invalid
			break;
		}
		szByteBuffer[ uiBitReadedInBuffer / 8 ] = cReaded;
		uiBitReadedInBuffer += 8;
		
		if ( 8 <= uiBitsToRead - uiBitsReaded ){
			//copy one byte
			pReadedBits[ uiByteOfReadedBits ] = cReaded;
			uiByteOfReadedBits++;
			uiBitPositionBuffer += 8;
			uiBitsReaded += 8;
		}else{//don't read a wool byte -> copy a part of a byte
			//more bits readed then needed
			unsigned char cMask = 0xFF >> ( (uiBitsReaded + 8) - uiBitsToRead );
			cReaded = cReaded & cMask;
			
			pReadedBits[ uiByteOfReadedBits ] = cReaded;
			
			uiByteOfReadedBits++;
			
			uiBitPositionBuffer += uiBitsToRead - uiBitsReaded;
			uiBitsReaded = uiBitsToRead;
			break;//done reading
		}
	}
	if ( uiBitReadedInBuffer == uiBitsToBuffer ){
		//go to the start of the buffer
		uiBitReadedInBuffer = 0;
	}
	if ( uiBitPositionBuffer == uiBitsToBuffer ){
		//go to the start of the buffer
		uiBitPositionBuffer = 0;
	}

	//shift the first bit to the first position in the pReadedBits buffer
	if ( uiShift != 0 ){
		for ( unsigned int uiBytePosition = 0; uiBytePosition < uiByteOfReadedBits;
				uiBytePosition++ ){
			
			pReadedBits[ uiBytePosition ] =
				pReadedBits[ uiBytePosition ] >> uiShift;
			if ( (uiBytePosition + 1) < uiByteOfReadedBits ){
				//transfer the remaining of the next byte
				pReadedBits[ uiBytePosition ] =
					pReadedBits[ uiBytePosition ] |
					pReadedBits[ uiBytePosition + 1 ] << (8 - uiShift);
			}
		}
	}
	//transfer the readed bits to the ountput buffer pBuffer
	memset( pBuffer, 0x00, roundUpToFullByte( uiBitsToRead ) / 8 );
	memcpy( pBuffer, pReadedBits, roundUpToFullByte( uiBitsToRead ) / 8 );
	
	ulBitReadedCount += uiBitsReaded;
	
	return uiBitsReaded;
}


/**
 * This method reads a number of bits from the stream into a integer
 * variable.
 *
 * @param iBuffer a reference to the variable, wher to read the number to
 * @param uiBitsToRead the number of bits to read
 * @return the number of bits readed
 */
unsigned int cReadBits::readBits( int & iBuffer, unsigned int uiBitsToRead ){

	const unsigned int uiBitsReaded = readBits( (char *)(&iBuffer),
		min( uiBitsToRead, (unsigned int)( sizeof( int ) * 8) ) );
	
	if ( (uiBitsReaded != 0) && (uiBitsReaded != (sizeof( int ) * 8) ) ){
		/*if the readed number was negativ
		-> add leading 1 Bits befor the readed sign bit*/
		int iOneBit = 1;
		if ( ( iBuffer & (iOneBit << (uiBitsReaded - 1) ) ) != 0 ){
			
			iBuffer = iBuffer | (-1L << uiBitsReaded );
		}
	}
	return uiBitsReaded;
}


/**
 * This method reads a number of bits from the stream into a integer
 * variable.
 *
 * @param lBuffer a reference to the variable, wher to read the number to
 * @param uiBitsToRead the number of bits to read
 * @return the number of bits readed
 */
unsigned int cReadBits::readBits( long & lBuffer, unsigned int uiBitsToRead ){

	const unsigned int uiBitsReaded = readBits( (char *)(&lBuffer),
		min( uiBitsToRead, (unsigned int)(sizeof( long ) * 8)) );
	
	if ( (uiBitsReaded != 0) && (uiBitsReaded != (sizeof( long ) * 8) ) ){
		/*if the readed number was negativ
		-> add leading 1 Bits befor the readed sign bit*/
		long lOneBit = 1;
		if ( ( lBuffer & (lOneBit << (uiBitsReaded - 1) ) ) != 0 ){
			
			lBuffer = lBuffer | (-1L << uiBitsReaded );
		}
	}
	return uiBitsReaded;
}


/**
 * This method reads a number of bits from the stream into a integer
 * variable.
 *
 * @param lBuffer a reference to the variable, wher to read the number to
 * @param uiBitsToRead the number of bits to read
 * @return the number of bits readed
 */
unsigned int cReadBits::readBits( long long & lBuffer, unsigned int uiBitsToRead ){

	const unsigned int uiBitsReaded = readBits( (char *)(&lBuffer),
		min( uiBitsToRead, (unsigned int)(sizeof( long long ) * 8)) );
	
	if ( (uiBitsReaded != 0) && (uiBitsReaded != (sizeof( long long ) * 8) ) ){
		/*if the readed number was negativ
		-> add leading 1 Bits befor the readed sign bit*/
		long long lOneBit = 1;
		if ( ( lBuffer & (lOneBit << (uiBitsReaded - 1) ) ) != 0 ){
			
			lBuffer = lBuffer | ( ((long long)(-1L)) << uiBitsReaded );
		}
	}
	return uiBitsReaded;
}


/**
 * This method reads a number of bits from the stream into a integer
 * variable.
 *
 * @param uiBuffer a reference to the variable, wher to read the number to
 * @param uiBitsToRead the number of bits to read
 * @return the number of bits readed
 */
unsigned int cReadBits::readBits( unsigned int & uiBuffer, unsigned int uiBitsToRead ){

	const unsigned int uiBitsReaded = readBits( (char *)(&uiBuffer),
		min( uiBitsToRead, (unsigned int)(sizeof( unsigned int ) * 8)) );

	return uiBitsReaded;
}

/**
 * This method reads a number of bits from the stream into a integer
 * variable.
 *
 * @param uiBuffer a reference to the variable, wher to read the number to
 * @param uiBitsToRead the number of bits to read
 * @return the number of bits readed
 */
unsigned int cReadBits::readBits( unsigned long & ulBuffer, unsigned int uiBitsToRead ){

	const unsigned int uiBitsReaded = readBits( (char *)(&ulBuffer),
		min( uiBitsToRead, (unsigned int)(sizeof( unsigned long ) * 8)) );

	return uiBitsReaded;
}

/**
 * This method reads a number of bits from the stream into a integer
 * variable.
 *
 * @param uiBuffer a reference to the variable, wher to read the number to
 * @param uiBitsToRead the number of bits to read
 * @return the number of bits readed
 */
unsigned int cReadBits::readBits( unsigned long long & ulBuffer, unsigned int uiBitsToRead ){

	const unsigned int uiBitsReaded = readBits( (char *)(&ulBuffer),
		min( uiBitsToRead, (unsigned int)(sizeof( unsigned long long ) * 8)) );

	return uiBitsReaded;
}


/**
 * This method reads to the beginning of the next full byte, if it isn't
 * allready readed to a full byte.
 * After the method call the readpoint stands on the beginning of a byte,
 * which is after or at the read position befor the call.
 *
 * @return the number of bits readed
 */
unsigned int cReadBits::readTillNextFullByte(){

	if ( (uiBitPositionBuffer % 8) != 0 ){
		const unsigned short uiBitsToRead = 8 - (uiBitPositionBuffer % 8);
		uiBitPositionBuffer += uiBitsToRead;
		ulBitReadedCount += uiBitsToRead;
		return uiBitsToRead;
	}
	return 0;
}

/**
 * This function will rollbach uiBitsToRollback bits of the stream so
 * they will be read again.
 *
 * @param uiBitsToRollback the number of bits to rollback
 * @return the number of bits rollbacked
 */
unsigned int cReadBits::rollbackBits( unsigned int uiBitsToRollback ){
	
	unsigned int uiBitsRollbacked = 0;
	//never rollback over the uiByteReadedInBuffer position
	if ( uiBitReadedInBuffer < uiBitPositionBuffer ){
		if ( uiBitsToRollback < (uiBitPositionBuffer - uiBitReadedInBuffer) ){
			//rollback uiBitsToRollback bits
			uiBitPositionBuffer -= uiBitsToRollback;
			uiBitsRollbacked = uiBitsToRollback;
		}else{//not enoght bits to rollback, roolback to uiBitReadedInBuffer
			uiBitsRollbacked = (uiBitPositionBuffer - uiBitReadedInBuffer);
			uiBitPositionBuffer = uiBitReadedInBuffer;
		}
	}else{/*uiBitPositionBuffer < uiBitReadedInBuffer
		-> rollback over beginning of the buffer*/
		//ulBitPositionBufferVirtual = the virtual uiBitPositionBuffer after uiBitReadedInBuffer
		const unsigned long ulBitPositionBufferVirtual =
			uiBitsToBuffer + uiBitPositionBuffer;
		
		if ( uiBitsToRollback < (ulBitPositionBufferVirtual - uiBitReadedInBuffer) ){
			//rollback uiBitsToRollback bits
			if ( uiBitsToRollback <= uiBitPositionBuffer ){
				uiBitPositionBuffer -= uiBitsToRollback;
			}else{
				uiBitPositionBuffer = ulBitPositionBufferVirtual - uiBitsToRollback;
			}
			uiBitsRollbacked = uiBitsToRollback;
		}else{//not enoght bits to rollback, roolback to uiBitReadedInBuffer
			uiBitsRollbacked = (ulBitPositionBufferVirtual - uiBitReadedInBuffer);
			uiBitPositionBuffer = uiBitReadedInBuffer;
		}
	}
	
	ulBitReadedCount -= uiBitsRollbacked;
	return uiBitsRollbacked;
}


/**
 * @return a pointer to the bufferd input stream
 * Beware: The readposition will be after the byte of last readed bit,
 * without the rollbacks.
 */
istream * cReadBits::getStream(){

	return pIstream;
}


/**
 * @return the number of bits readed from the stream or respectively
 * 	the bitposition in the stream (rollbacks inclusive)
 */
unsigned long cReadBits::getBitReadedCount() const{
	
	return ulBitReadedCount;
}






