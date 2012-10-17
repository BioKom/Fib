/**
 * @file debugOut.inc
 * file name: debugOut.inc
 * @author Betti Oesterholz
 * @date 04.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This includefile contains the definitions vor debugoutput.
 *
 * Copyright (C) @c GPL3 2009 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
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
 * This includefile contains the definitions vor debugoutput.
 *
 */
/*
History:
01.11.2009  Oesterholz  created
*/

#ifndef ___DEBUG_OUT_H__
#define ___DEBUG_OUT_H__

#ifdef DEBUG


#include <iostream>

using namespace std;

//higher level (L) less serios output

//debugoutputs
#define DEBUG_OUT_L1( X ) cout X
#define DEBUG_OUT_L2( X ) cout X
#define DEBUG_OUT_L3( X ) cout X
#define DEBUG_OUT_L4( X ) cout X

//error outputs
#define DEBUG_OUT_EL1( X ) cerr X
#define DEBUG_OUT_EL2( X ) cerr X
#define DEBUG_OUT_EL3( X ) cerr X
#define DEBUG_OUT_EL4( X ) cerr X


#else //DEBUG
//dummy: comment out the debugging code

//debugoutputs
#define DEBUG_OUT_L1( X )
#define DEBUG_OUT_L2( X )
#define DEBUG_OUT_L3( X )
#define DEBUG_OUT_L4( X )

//error outputs
#define DEBUG_OUT_EL1( X )
#define DEBUG_OUT_EL2( X )
#define DEBUG_OUT_EL3( X )
#define DEBUG_OUT_EL4( X )


#endif //DEBUG




#endif



 
