/**
 * file name: version.h
 * @author Betti Oesterholz
 * @date 19.04.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains switches for the different Fib-versions.
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
 * This file contains the versionsinformation for the Fib 
 * -Multimedialanguage implementation.
 * This includes descriptions of declarations for versioned
 * programming switches.
 *
 */
/*
History:
19.04.2009  Oesterholz  created
06.06.2011  Oesterholz  FEATURE_STORE_VECTOR_ELEMENT_NUMBER added
05.08.2011  Oesterholz  FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES added
04.09.2011  Oesterholz  FEATURE_GENERATE_NEEDED_DOMAINS added
17.10.2011  Oesterholz  FEATURE_OUTPUT_ELEMENT_NUMBER_XML,
	FEATURE_NEW_ROOT_GET_DEFINED_VARIBLES and FEATURE_EQUAL_FIB_OBJECT added
10.11.2011  Oesterholz  FEATURE_EVALUE_ALL_PROPERTIES_IN_C_PROPERTY added
26.11.2011  Oesterholz  FEATURE_FIB_DB_USE_TREADS added
29.01.2012  Oesterholz  FEATURE_EXT_SUBOBJECT_INPUT_VECTOR added
09.03.2012  Oesterholz  new version numbers for Fib and Fib database
22.10.2012  Oesterholz  DEBUG_EVALUE added
16.01.2013  Oesterholz  FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS added
17.02.2013  Oesterholz  FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE added
*/


//debugging information; define DEBUG to activate them
//#define DEBUG
#include "debugOut.inc"


/**************************************
* Version Information
**************************************/

//versions information for the Fib multimedia language
#define FIB_VERSION          6
#define FIB_VERSION_NAME     V1.2.3

//versions information for the Fib database
#define FIB_DB_VERSION      5
#define FIB_DB_VERSION_NAME V1.1.3


/*****************************************
* versioned programming debugging switches
******************************************/

/**
 * This switch prints debugging information when restoring from the
 * compressed XML format.
 *
 * @see cFibElement::restoreXmlInternal()
 * @see cUnderFunction::restoreXml()
 */
//#define DEBUG_RESTORE_XML

/**
 * With this switch on the evalueObject() functionality can be debugged.
 *
 * @see evalueObject()
 */
//#define DEBUG_EVALUE

/**
 * With this feature the element number will be written as a XML attribute
 * "elementNr", when the Fib-elements are stored in the XML format.
 * This feature is for testing, in normaly it should be deactivated.
 *
 * created: 17.10.2011 Betti Oesterholz
 * status:  running and tested(17.10.2011)
 *//*
History:
*/
//#define FEATURE_OUTPUT_ELEMENT_NUMBER_XML


/**
 * With this feature the number of the vector elements are written, when
 * storing in the Fib-XML-format.
 * @see cFibVector::storeXml()
 *
 * created: 06.06.2011  Betti Oesterholz
 * status:  running and tested(06.06.2011)
 *//*
History:
*/
//#define FEATURE_STORE_VECTOR_ELEMENT_NUMBER



/**************************************
* versioned programming switches
**************************************/


/**
 * The maximal number of numbers in an underarea the method
 * cVectorArea::getAreaValues() returns.
 * If defined no underare will contain more then MAX_UNDERAREA_SIZE
 * numbers.
 *
 * created: 12.05.2010  Betti Oesterholz
 * status:  not working for limit values
 * @see cVectorArea::getAreaValues()
 */
//#define MAX_UNDERAREA_SIZE 10000000


/**
 * With this feature the class cArea iterates directly over the values of
 * it's subareas without using the method @see cVectorArea::getAreaValues().
 * @see cArea
 *
 * created: 12.05.2010  Betti Oesterholz
 * status:  tested
 *//*
History:
*/
#define FEATURE_DIRECT_UNDERAREAVALUES


/**
 * With this feature the constructors of the Fib-elements won't ask for
 * the next and previos Fib-elements.
 *
 * created: 05.08.2010  Betti Oesterholz
 * status:  running and tested(10.2010)
 * (deprecated: not FEATURE_SIMPLE_CONSTRUCTOR)
 *//*
History:
*/
#define FEATURE_SIMPLE_CONSTRUCTOR


/**
 * With this feature the registerNewFibObject() method will be removed.
 * @see registerNewFibObject()
 *
 * created: 19.08.2010  Betti Oesterholz
 * status:  running and tested(10.2010)
 * (deprecated: not FEATURE_NO_REGISTER_NEW_FIB_)
 * needed features:
 * 	- FEATURE_SIMPLE_CONSTRUCTOR
 *//*
History:
*/
#define FEATURE_NO_REGISTER_NEW_FIB_

#ifdef FEATURE_NO_REGISTER_NEW_FIB_
	#define FEATURE_SIMPLE_CONSTRUCTOR
#endif //FEATURE_NO_REGISTER_NEW_FIB_

/**
 * With this feature the Fib-object values will be updated if the values
 * are needed and not when the Fib-object is changed.
 * @see updateValues()
 *
 * created: 02.08.2010  Betti Oesterholz
 * status:  running and tested(10.2010)
 * (deprecated: not FEATURE_FAST_UPDATE)
 * needed features:
 * 	- FEATURE_SIMPLE_CONSTRUCTOR
 * 	- FEATURE_NO_REGISTER_NEW_FIB_
 *//*
History:
*/
#define FEATURE_FAST_UPDATE

#ifdef FEATURE_FAST_UPDATE
	#define FEATURE_SIMPLE_CONSTRUCTOR
	#define FEATURE_NO_REGISTER_NEW_FIB_
#endif //FEATURE_FAST_UPDATE


/**
 * When checking if an property is overwritten the
 * cVectorProperty::isOverwritenVector() method of the property vector is
 * used.
 *
 * created: 17.12.2010  Betti Oesterholz
 * status:  running and tested(18.12.2010)
 * (deprecated: not FEATURE_CHECK_OVERWRITTEN_WITH_IS_OVERWRITTEN_VECTOR)
 *//*
History:
*/
#define FEATURE_CHECK_OVERWRITTEN_WITH_IS_OVERWRITTEN_VECTOR


/**
 * When compressed storing a Fib-element its defined variables aren't
 * stored, because ther number is implicite.
 *
 * created: 05.08.2011 Betti Oesterholz
 * status:  running and tested(05.08.2011)
 * (deprecated: not FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES)
 *//*
History:
*/
#define FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES


/**
 * New handling of generting needed domains
 * ( @see cRoot::generateNeededDomains() ).
 * - Domains for the sub-roots will be generated also.
 * - If the existing valid domain is OK new new domain will be created.
 *
 * created: 04.09.2011 Betti Oesterholz
 * status:  running and tested(04.09.2011)
 * (deprecated: not FEATURE_GENERATE_NEEDED_DOMAINS)
 *//*
History:
*/
#define FEATURE_GENERATE_NEEDED_DOMAINS


/**
 * New implementation of the Fib element equal methods.
 *
 * @see cFibElement::equal()
 * @see cFibElement::equalElement()
 * @see cFibElement::equalValuesSet()
 *
 * created: 19.10.2011 Betti Oesterholz
 * status:  running and tested(26.10.2011)
 * (deprecated: not FEATURE_EQUAL_FIB_OBJECT)
 *//*
History:
*/
#define FEATURE_EQUAL_FIB_OBJECT


/**
 * The root Element has new getDefinedVariables() method / handling:
 * 	all defined variables in the subroots will be considered
 *
 * @see cRoot::getDefinedVariables()
 * @see cRoot::getDefinedVariablesInternal()
 *
 * created: 01.11.2011 Betti Oesterholz
 * status:  running and tested(01.11.2011)
 * (deprecated: not FEATURE_NEW_ROOT_GET_DEFINED_VARIBLES)
 *//*
History:
*/
#define FEATURE_NEW_ROOT_GET_DEFINED_VARIBLES


/**
 * When evalue the properties @see cProperty will not check and delete
 * overwriting properties. This behavior is needed because, because the
 * propertie dependencies can be complex (e. g. the debendencie of color
 * and transparency properties )
 *
 * @see cProperty::evalueObject()
 *
 * This feature will make the feature FEATURE_CHECK_OVERWRITTEN_WITH_IS_OVERWRITTEN_VECTOR
 * obsolete.
 *
 * created: 10.11.2011 Betti Oesterholz
 * status:  running and tested(10.11.2011)
 * (deprecated: not FEATURE_EVALUE_ALL_PROPERTIES_IN_C_PROPERTY
 * 	and FEATURE_CHECK_OVERWRITTEN_WITH_IS_OVERWRITTEN_VECTOR)
 *//*
History:
*/
#define FEATURE_EVALUE_ALL_PROPERTIES_IN_C_PROPERTY



/**
 * With this feature the external subobject element @see cExtSubobject
 * will use a vector for its input values.
 * (@see cFibDatabase::loadFibObject() ).
 *
 * @see cExtSubobject
 * @see cVectorExtSubobject
 * @see cTypeExtSubobject
 * created: 29.01.2012 Betti Oesterholz
 * status:  running and tested(29.01.2012)
 * (deprecated: not FEATURE_EXT_SUBOBJECT_INPUT_VECTOR)
 *//*
History:
*/
#define FEATURE_EXT_SUBOBJECT_INPUT_VECTOR


/**
 * With this feature the Fib vector @see cFibVector
 * will just store (compressed) as much elements as the domains permits.
 * (@see cFibVector::store() ).
 *
 * @see cFibVector
 * created: 04.02.2012 Betti Oesterholz
 * status:  running and tested(04.02.2012)
 * (deprecated: not FEATURE_FIB_VECTOR_STORE_JUST_DOMAIN)
 *//*
History:
*/
#define FEATURE_FIB_VECTOR_STORE_JUST_DOMAIN


/**
 * With this feature the Fib database @see cFibDatabase will be build for
 * treads. Loading will be done in a seperate tread.
 * @see cFibDatabase::loadFibObject()
 *
 * @see cFibDatabase
 * created: 17.10.2011 Betti Oesterholz
 * status:  implemented (17.10.2011)
 *//*
History:
*///TODO
//#define FEATURE_FIB_DB_USE_TREADS


/**
 * With this feature the Fib element class @see cFibElement
 * will check the Fib database for external objects if no root element
 * is aviable.
 *
 * @see cFibElement::getAccessibleRootObject
 * created: 16.01.2013 Betti Oesterholz
 * status:  running and tested(16.01.2013)
 * (deprecated: not FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS)
 *//*
History:
*/
#define FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS


/**
 * With this feature the Fib vector class @see cFibVector
 * will use a variable to get the size of the underlying vectors.
 *
 * @see cFibVector::getNumberOfElements
 * created: 17.02.2013 Betti Oesterholz
 * status:  running and tested(17.02.2013)
 * (deprecated: not FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE)
 *//*
History:
*/
#define FEATURE_FIB_VECTOR_GET_SIZE_WITH_VARIABLE





