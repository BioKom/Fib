/**
 * @file nBitStream
 * file name: nBitStram.h
 * @author Betti Oesterholz
 * @date 24.09.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies functions with which any number of bits can be
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
 * This header specifies functions with which any number of bits can be
 * writen into a stream.
 *
 */
/*
History:
24.09.2009  Oesterholz  created
*/

#ifndef ___N_BIT_STREAMS_H__
#define ___N_BIT_STREAMS_H__

#include <ostream>

using namespace std;

namespace nBitStream{

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
	bool store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition,
		const unsigned long long & ulNumber, const unsigned char ucBitsToStore );

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
	bool store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition,
		const unsigned long & ulNumber, const unsigned char ucBitsToStore );

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
	bool store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition,
		const unsigned int & ulNumber, const unsigned char ucBitsToStore );

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
	bool store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition,
		const long long & lNumber, const unsigned char ucBitsToStore );

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
	bool store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition,
		const long & lNumber, const unsigned char ucBitsToStore );

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
	bool store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition,
		const int & lNumber, const unsigned char ucBitsToStore );

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
	bool store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition,
		const char * pcField, const unsigned int uiBitsToStore );

	
}//end namespace nBitStream


#endif //___N_BIT_STREAMS_H__







