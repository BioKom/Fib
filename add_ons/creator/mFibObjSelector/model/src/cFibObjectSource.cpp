/**
 * @file cFibObjectSource
 * file name: cFibObjectSource.cpp
 * @author Betti Oesterholz
 * @date 24.09.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for information for loading a Fib object.
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
 * This file implements a class for information for loading a Fib object.
 * It is a base class for all classes for information to restore a Fib object.
 *
 * @see cFibElement
 * @see cFibObjectInfo
 * @see cFibNode
 */
/*
History:
24.09.2013  Oesterholz  created
02.03.2014  Oesterholz  categories for Fib object source added: getCategories()
*/



#include "cFibObjectSource.h"

#include "cFibObjectSourceFibDb.h"
#include "cFibObjectSourcePath.h"

#include "cFibElement.h"


using namespace std;


using namespace fib::nCreator;
using namespace fib;


/**
 * standard constructor for a Fib object source object
 */
cFibObjectSource::cFibObjectSource() {
	//nothing to do
}


/**
 * destructor
 */
cFibObjectSource::~cFibObjectSource() {
	//nothing to do
}


/**
 * @return the name of this class "cFibObjectSource"
 */
string cFibObjectSource::getName() const {
	
	return "cFibObjectSource";
}


/**
 * @return the set with the categories this Fib object source is in
 * 	(e.g. "Fib database", "file")
 */
std::set< std::string > cFibObjectSource::getCategories() const {
	//default: no categories
	return std::set< std::string >();
}


/**
 * This method will restore the Fib object source object from the given
 * input stream and return a pointer to it.
 * Beware: You have to care that the returned Fib object source object is
 * 	deleted.
 *
 * @see storeFibObjectSource()
 * @param stream the input stream from which to read the Fib object info
 * @param iOutStatus if not NULL an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid stream
 * 		- -2 loading error, invalid data in stream
 * 		- 1 loading warning, invalid data in stream, error could be corrected
 * 		- 2 loading warning, invalid data in stream, maybe the loaded
 * 			object is wrong
 * @return a pointer to the restored Fib object source object or NULL if
 * 	non could be restored
 */
cFibObjectSource * cFibObjectSource::restore(
		istream & stream, int * iOutStatus ) {
	
	TiXmlDocument xmlDocFibObject;
	
	stream >> xmlDocFibObject;
	
	if ( xmlDocFibObject.Error() ) {
		//error while loading to stream
		if ( iOutStatus ) {
			(*iOutStatus) = -1;
		}
		return NULL;
	}
	
	return cFibObjectSource::restore( &xmlDocFibObject, iOutStatus );
}


/**
 * This method will restore the Fib object source object from the given
 * TinyXml node and return a pointer to it.
 * Beware: You have to care that the returned Fib object source object is
 * 	deleted.
 *
 * @see storeFibObjectSource()
 * @param pXmlNode a pointer to the TinyXml node where the Fib object
 * 	info object is stored in
 * @param iOutStatus if not NULL an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlNode
 * 		- -2 loading error, invalid data in pXmlNode
 * 		- 1 loading warning, invalid data in pXmlNode, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlNode, maybe the loaded
 * 			object is wrong
 * @return a pointer to the restored Fib object source object or NULL, if
 * 	non could be restored
 */
cFibObjectSource * cFibObjectSource::restore(
		const TiXmlNode * pXmlNode, int * iOutStatus ) {
	
#ifdef DEBUG_RESTORE_XML
	//print debugging output
	printf("restoring cFibObjectSource\n" );
#endif//DEBUG_RESTORE_XML
	if ( pXmlNode == NULL ) {
		//nothing to restore
#ifdef DEBUG_RESTORE_XML
		//print debugging output
		printf("nothing to restore\n" );
#endif//DEBUG_RESTORE_XML
		if ( iOutStatus != NULL ) {
			//set the output status
			(*iOutStatus) = -1;
		}
		return NULL;
	}
	
	//as long no Fib object source object was read and no error occured
	while ( ( pXmlNode != NULL ) && ( 0 <= (*iOutStatus) ) ) {
		//get type of XML element
		const int iType = pXmlNode->Type();
		switch ( iType ) {
			case TiXmlNode::ELEMENT:{
				/*check if this is a valid Fib object source object XML element,
				create the apropirate Fib object source and call its restoreXml() method*/
				const TiXmlElement * pXmlElement = pXmlNode->ToElement();
				if ( pXmlElement == NULL ) {
					//Warning: nothing to load
#ifdef DEBUG_RESTORE_XML
					//print debugging output
					printf("not valid xml sub element\n" );
#endif//DEBUG_RESTORE_XML
					if ( iOutStatus != NULL ) {
						//set the output status
						(*iOutStatus) = -1;
					}
					return NULL;
				}
				const string szElementType( pXmlElement->Value() );
				
#ifdef DEBUG_RESTORE_XML
				printf( "Restoring root subelement \"%s\" (iOutStatus now %i)\n",
					szElementType.c_str(), iOutStatus );
#endif
				//<fib_object_source type="..." ...>
				if ( szElementType == "fib_object_source" ) {
					//if exists get "type" attribute
					const char * szXmlName =
						pXmlElement->Attribute( "type" );
					if ( szXmlName == NULL ) {
						//Error: unknown element type (don't know what to restore)
						if ( iOutStatus != NULL ) {
							//set the output status
							(*iOutStatus) = -2;
						}
						return NULL;
					}else if ( strncmp( "Fib database", szXmlName, 12 ) == 0 ) {
						//restore a Fib database source object
						return new cFibObjectSourceFibDb( pXmlElement, iOutStatus );
						
					}else if ( strncmp( "path", szXmlName, 4 ) == 0 ) {
						//restore a Fib database source object
						return new cFibObjectSourcePath( pXmlElement, iOutStatus );
						
					}else{//Error: unknown element type (don't know what to restore)
						if ( iOutStatus != NULL ) {
							//set the output status
							(*iOutStatus) = -2;
						}
						return NULL;
					}
					
				}else{//Error: unknown element type
					if ( iOutStatus != NULL ) {
						//set the output status
						(*iOutStatus) = -2;
					}
					return NULL;
				}
				
			}break;
			case TiXmlNode::DOCUMENT:{
				//restore Fib object source object from subelements
				for ( const TiXmlNode * pChild = pXmlNode->FirstChild();
						pChild != NULL; pChild = pChild->NextSibling() ) {
					
					int iOutStatusLoc = 0;
					cFibObjectSource * pRestoredFibObjectSource =
						restore( pChild, &iOutStatusLoc );
					if ( ( iOutStatus != NULL ) && ( iOutStatusLoc != 0 ) ) {
						//transver output status
						if ( (*iOutStatus) == 0 ) {
							
							(*iOutStatus) = iOutStatusLoc;
							
						}else if ( ( 0 < (*iOutStatus) ) && ( iOutStatusLoc < 0 ) ) {
							
							(*iOutStatus) = iOutStatusLoc;
						}//else do not transver output status
					}//end if transver output status
					
					if ( ( pRestoredFibObjectSource != NULL ) ||
							( iOutStatusLoc < 0 ) ) {
						return pRestoredFibObjectSource;
					}//else no Fib object source object loaded -> try next XML element
				}//else nothing to load
#ifdef DEBUG_RESTORE_XML
				//print debugging output
				printf( "Error: nothing to load\n" );
#endif//DEBUG_RESTORE_XML
				if ( iOutStatus != NULL ) {
					//set the output status
					(*iOutStatus) = -2;
				}
				return NULL;
			}break;
			case TiXmlNode::DECLARATION:
			case TiXmlNode::COMMENT:{
				//ignore
			}break;
			case TiXmlNode::TEXT:
			case TiXmlNode::UNKNOWN:
			default:
				//ignore; Warning: invalid Fib object
				if ( ( iOutStatus != NULL ) && ( (*iOutStatus) == 0 ) ) {
					(*iOutStatus) = 2;
				}
		}//end switch XML element type
		//if no Fib element was read check next XML eleemnt
		pXmlNode = pXmlNode->NextSibling();
	}//end as long no Fib element was read and no error occured
	
	if ( iOutStatus != NULL ) {
		//set the output status
		(*iOutStatus) = -2;
	}
	return NULL;
}








