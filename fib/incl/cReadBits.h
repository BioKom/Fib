/**
 * @class cReadBits
 * file name: cReadBits.h
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

#ifndef ___C_READ_BITS_H__
#define ___C_READ_BITS_H__


#include <cstring>
#include <istream>


using namespace std;

namespace fib{


class cReadBits{
protected:
	/**
	 * This is a pointer to the buffer wher the readed byts of the stream
	 * will be bufferd.
	 * The byts bufferd are readed round. If the end of the buffer is
	 * reached, the beginning is the next byte.
	 */
	char * szByteBuffer;
	
	/**
	 * The number of byts to buffer.
	 */
	unsigned int uiBitsToBuffer;
	
	/**
	 * The bitposition in the buffer of the bit to read next from the buffer.
	 */
	unsigned int uiBitPositionBuffer;

	/**
	 * The bitposition of the bit which will be stored next to the buffer.
	 */
	unsigned int uiBitReadedInBuffer;

	/**
	 * The the number of bits readed from the stream.
	 */
	unsigned long ulBitReadedCount;

	/**
	 * A pointer to the input stream to buffer.
	 */
	istream * pIstream;
	
public:
	
	/**
	 * Standardconstructor
	 * Beware: Don't use istreamIn elsewher, while using it with theas class.
	 * This class should only use istreamIn.
	 *
	 * @param istreamIn the stream to read the bits from
	 * @param uiBytsToBuffer the number of byts to buffer from the stream
	 */
	cReadBits( istream & istreamIn, unsigned int uiBytsToBuffer = 256 );

	/**
	 * destructor
	 */
	~cReadBits();

	/**
	 * This method reads a number of bits from the stream.
	 *
	 * @param pBuffer the character array wher to writes the readed bits to,
	 * 	the first bit will begin at the pointer pBuffer
	 * @param uiBitsToRead the number of bits to read
	 * @return the number of bits readed
	 */
	unsigned int readBits( char * pBuffer, unsigned int uiBitsToRead );

	/**
	 * This method reads a number of bits from the stream into a integer
	 * variable.
	 *
	 * @param iBuffer a reference to the variable, wher to read the number to
	 * @param uiBitsToRead the number of bits to read
	 * @return the number of bits readed
	 */
	unsigned int readBits( int & iBuffer, unsigned int uiBitsToRead );
	
	/**
	 * This method reads a number of bits from the stream into a integer
	 * variable.
	 *
	 * @param lBuffer a reference to the variable, wher to read the number to
	 * @param uiBitsToRead the number of bits to read
	 * @return the number of bits readed
	 */
	unsigned int readBits( long & lBuffer, unsigned int uiBitsToRead );

	/**
	 * This method reads a number of bits from the stream into a integer
	 * variable.
	 *
	 * @param lBuffer a reference to the variable, wher to read the number to
	 * @param uiBitsToRead the number of bits to read
	 * @return the number of bits readed
	 */
	unsigned int readBits( long long & lBuffer, unsigned int uiBitsToRead );

	/**
	 * This method reads a number of bits from the stream into a integer
	 * variable.
	 *
	 * @param uiBuffer a reference to the variable, wher to read the number to
	 * @param uiBitsToRead the number of bits to read
	 * @return the number of bits readed
	 */
	unsigned int readBits( unsigned int & uiBuffer, unsigned int uiBitsToRead );

	/**
	 * This method reads a number of bits from the stream into a integer
	 * variable.
	 *
	 * @param uiBuffer a reference to the variable, wher to read the number to
	 * @param uiBitsToRead the number of bits to read
	 * @return the number of bits readed
	 */
	unsigned int readBits( unsigned long & ulBuffer, unsigned int uiBitsToRead );

	/**
	 * This method reads a number of bits from the stream into a integer
	 * variable.
	 *
	 * @param uiBuffer a reference to the variable, wher to read the number to
	 * @param uiBitsToRead the number of bits to read
	 * @return the number of bits readed
	 */
	unsigned int readBits( unsigned long long & ulBuffer, unsigned int uiBitsToRead );
	
	/**
	 * This method reads to the beginning of the next full byte, if it isn't
	 * allready readed to a full byte.
	 * After the method call the readpoint stands on the beginning of a byte,
	 * which is after or at the read position befor the call.
	 *
	 * @return the number of bits readed
	 */
	unsigned int readTillNextFullByte();

	/**
	 * This function will rollbach uiBitsToRollback bits of the stream so
	 * they will be read again.
	 *
	 * @param uiBitsToRollback the number of bits to rollback
	 * @return the number of bits rollbacked
	 */
	unsigned int rollbackBits( unsigned int uiBitsToRollback );

	/**
	 * @return a pointer to the bufferd input stream
	 * Beware: The readposition will be after the byte of last readed bit,
	 * without the rollbacks.
	 */
	istream * getStream();
	
	/**
	 * @return the number of bits readed from the stream or respectively
	 * 	the bitposition in the stream (rollbacks inclusive)
	 */
	unsigned long getBitReadedCount() const;


};//end class cReadBits


}//end namespace fib

#endif //___C_READ_BITS_H__
