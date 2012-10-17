/**
 * file name: version.h
 * @author Betti Oesterholz
 * @date 22.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains switches for the converter.
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
 * This file contains the versionsinformation for the converter of the Fib
 * -Multimedialanguage implementation.
 * This includes descriptions of declarations for versioned
 * programming switches.
 *
 */
/*
History:
19.04.2009  Oesterholz  created
12.09.2009  Oesterholz  FEATURE_BALANCED_LOAD added
28.03.2011  Oesterholz  FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP added
06.07.2011  Oesterholz  FEATURE_CONVERT_TO_FIB_AREA_GENERATOR added
*/

//debugging information; define DEBUG to activate them
//#define DEBUG
#include "debugOut.inc"


/**************************************
* Version Information
**************************************/

//Versionsinformation for the converter of the fib-multimedialanguage
#define FIB_CONVERTER_VERSION          0
#define FIB_CONVERTER_VERSION_NAME     V0.0.0



/**************************************
* versioned programming switches
**************************************/


/**
 * With this feature the the loaded fib-object will be balanced
 * The value of the definition, is the number of underobjects in the
 * balanced listtree.
 *
 * created: 12.09.2010  Betti Oesterholz
 * Status:  implemened and tested
 *//*
History:
*/
#define FEATURE_BALANCED_LOAD 8


/**
 * With this feature the loaded fib-object will be converted to
 * an image with the given number of bits per color value (red, green and
 * blue).
 *
 * created: 17.11.2010  Betti Oesterholz
 * Status: implemened and tested
 *//*
History:
*/
#define FEATURE_FROM_FIB_BITS_PER_RGB_COLOR_VALUE 8


/**
 * With this feature the method with which a set of points is converted
 * into an area can be choose.
 *
 * Used method:
 * 	- not defined:
 *			use @see nD2::createSplineItrFastBorderAreasForPoints()
 * 	- defined:
 *			use @see nD2::createNSplineBorderAreasForPoints()
 *
 * created: 06.07.2011  Betti Oesterholz
 * Status: implemened and tested
 *//*
History:
*/
#define FEATURE_CONVERT_TO_FIB_AREA_GENERATOR


/**
 * With this feature when converting pictures to fib with convertReduced()
 * the small areas will be processed first and added to the end for
 * evaluing the fib-object. They will overlap bigger areas, so
 * processing time and storing memmory can be saved.
 *
 * The value of the define will determine the size of the classes for the
 * areas. In each class ther will be areas from (e^value)^class to
 * (e^value)^(class + 1) - 1 number of points. The class -1 contains all
 * single points. The class i is overlapted by all classes lower i.
 *
 * @see nConvertToFib::convertReduced()
 * created: 28.03.2011  Betti Oesterholz
 * Status:  implemened and tested
 *//*
History:
*/
/*( 0.4 is about log(1.5)) -> number of points of areas in class c is:
	1.5^c till 1.5^(class+1)-1  */
#define FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP 0.4



/**
 * This feature uses an own wraper object for the FreeImage image
 * functionality. (For systems wher the wraper dosn't work, like windows.)
 * @see fipImage
 * @see FreeImagePlus.h
 *
 * created: 18.05.2011  Betti Oesterholz
 * Status:  implemened and tested (18.05.2011)
 *//*
History:
*/
#define FEATURE_OWN_FREE_IMAGE_WARPER

#ifndef FEATURE_OWN_FREE_IMAGE_WARPER
#ifdef WINDOWS
	//use this feature under widows because ther is no wraper for it
	#define FEATURE_OWN_FREE_IMAGE_WARPER
#endif //WINDOWS
#endif //FEATURE_OWN_FREE_IMAGE_WARPER







