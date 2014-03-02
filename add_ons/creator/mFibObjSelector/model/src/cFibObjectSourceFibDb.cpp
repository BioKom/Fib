/**
 * @file cFibObjectSourceFibDb
 * file name: cFibObjectSourceFibDb.cpp
 * @author Betti Oesterholz
 * @date 23.09.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for information for loading a Fib object
 * from the Fib database.
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
 * This file implements a class for information for loading a Fib object
 * from the Fib database.
 *
 * ## File format ##
 *
 * A Fib information object for loading a Fib object will be stored in
 * the XML format.
 * The name of the root element is "fib_object_source". It has two
 * attributes "type" and "identifier".
 * The "type" attribute is always "Fib database". The attribute
 * "identifier" gives the identifier of the Fib database object.
 * @see lFibDbIdentifier
 *
 * example:
       <fib_object_source type="Fib database" identifier="-20">
 *
 *
 * @see cFibObjectSource
 * @see cFibElement
 * @see cFibDatabase
 * @see cFibObjectInfo
 * @see cFibNode
 */
/*
History:
23.09.2013  Oesterholz  created
02.03.2014  Oesterholz  categories for Fib object source added: getCategories()
*/


#include "cFibObjectSourceFibDb.h"

#include <cstring>
#include <algorithm>

#include <QObject>

#include "cFibElement.h"
#include "cFibDatabase.h"


//debugging switches
//#define DEBUG_RESTORE_XML


using namespace std;
using namespace fib::nCreator;


/**
 * The standard constructor for a Fib database object source object.
 *
 * @param lInFibDbIdentifier the identifier for the to load Fib database
 * 	object
 * 	@see lFibDbIdentifier
 */
cFibObjectSourceFibDb::cFibObjectSourceFibDb(
		const longFib & lInFibDbIdentifier ):lFibDbIdentifier( lInFibDbIdentifier ){
	//nothing to do
}


/**
 * The copy constructor for a Fib database object source object.
 *
 * @param fibObjectSourceFibDb the Fib database object source object to copy
 */
cFibObjectSourceFibDb::cFibObjectSourceFibDb(
		const cFibObjectSourceFibDb & fibObjectSourceFibDb ):
		lFibDbIdentifier( fibObjectSourceFibDb.lFibDbIdentifier ){
	//nothing to do
}


/**
 * This constructor will restore the Fib database object source object from
 * the given input stream.
 *
 * @see store()
 * @param stream the input stream from which to read the Fib database
 * 	object source object
 * @param iOutStatus if not NULL an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid stream
 * 		- -2 loading error, invalid data in stream
 * 		- 1 loading warning, invalid data in stream, error could be corrected
 * 		- 2 loading warning, invalid data in stream, maybe the loaded
 * 			object is wrong
 */
cFibObjectSourceFibDb::cFibObjectSourceFibDb(
		istream & stream, int * iOutStatus ):lFibDbIdentifier( 0 ){
	
	if ( iOutStatus != NULL ){
		//evalue / use output status
		(*iOutStatus) = restoreFibObjectSource( stream );
	}else{//don't use iOutStatus
		restoreFibObjectSource( stream );
	}
}


/**
 * This constructor will restore the Fib database object source object from
 * the given TinyXml node.
 *
 * @see store()
 * @param pXmlNode a pointer to the TinyXml node where the Fib database
 * 	object source object is stored in
 * @param iOutStatus if not NULL an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlNode
 * 		- -2 loading error, invalid data in pXmlNode
 * 		- 1 loading warning, invalid data in pXmlNode, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlNode, maybe the loaded
 * 			object is wrong
 */
cFibObjectSourceFibDb::cFibObjectSourceFibDb( const TiXmlNode * pXmlNode,
		int * iOutStatus ):lFibDbIdentifier( 0 ){
	
	if ( iOutStatus != NULL ){
		//evalue / use output status
		(*iOutStatus) = restoreFibObjectSource( pXmlNode );
	}else{//don't use iOutStatus
		restoreFibObjectSource( pXmlNode );
	}
}


/**
 * destructor
 */
cFibObjectSourceFibDb::~cFibObjectSourceFibDb(){
	//nothing to do
}



/**
 * @return the name of this class "cFibObjectSourceFibDb"
 */
string cFibObjectSourceFibDb::getName() const{
	
	return string( "cFibObjectSourceFibDb" );
}

/**
 * @return the identifier for the to load Fib database object
 * 	@see lFibDbIdentifier
 */
longFib cFibObjectSourceFibDb::getFibDbIdentifier() const{
	
	return lFibDbIdentifier;
}


/**
 * This method creates a copy of this object and returns it.
 *
 * @return a pointer to a copy of this object
 */
cFibObjectSourceFibDb * cFibObjectSourceFibDb::clone() const{
	
	return new cFibObjectSourceFibDb( *this );
}


/**
 * This method loads the Fib object from the source and returns a
 * pointer to it.
 * If no Fib object can be loaded NULL will be returned.
 * Beware: You have to care that the loaded Fib object will be deleted.
 *
 * @param iOutStatus if not NULL an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid source
 * 		- -2 loading error, invalid data
 * 		- 1 loading warning, invalid data, error could be corrected
 * 		- 2 loading warning, invalid data, maybe the loaded
 * 			object is wrong
 * @param pOutSetChangebelBy if not NULL a set to output the users who
 * 	can change change the loaded Fib object
 * @return a pointer to the loaded Fib object, or NULL if non could be
 * 	loaded
 */
cFibElement * cFibObjectSourceFibDb::loadFibObject( int * iOutStatus,
		set< string > * pOutSetChangebelBy ) const{
	
	if ( pOutSetChangebelBy ){
		//Fib database object can be changed by no one
		pOutSetChangebelBy->clear();
	}
	//get the Fib object from the Fib database
	cFibElement * pDbObject = fib::cFibDatabase::getInstance()->
		getFibObject( lFibDbIdentifier );
	
	if ( ( pDbObject == NULL ) && ( iOutStatus != NULL ) ){
		//Error: no database object loaded -> invalid source
		(*iOutStatus) = -1;
	}
	if ( pDbObject == NULL ){
		//no Fib object for identifier in Fib database
		return NULL;
	}//else
	return pDbObject->clone();
}


/**
 * This method will store the given Fib object to the location this object
 * specifies.
 *
 * @see loadFibObject()
 * @param pFibObject a pointer to the Fib object to store
 * @return true if the given Fib object could be stored, else false
 */
bool cFibObjectSourceFibDb::storeFibObject( const cFibElement * /*pFibObject*/ ) const{
	//can't store a Fib database object (Fib database should not change)
	return false;
}


/**
 * This method checks if the Fib object source exists.
 *
 * @return true if the source for the Fib object exists, else false
 */
bool cFibObjectSourceFibDb::checkSource() const{
	
	fib::cFibDatabase * pFibDatabase = fib::cFibDatabase::getInstance();
	if ( pFibDatabase == NULL ){
		//no Fib database -> no Fib object source
		return false;
	}//else
	const std::list< longFib > liAllDbIdentifiers =
		pFibDatabase->getAllDatabaseObjectIdentifiers();
	
	if ( find( liAllDbIdentifiers.begin(), liAllDbIdentifiers.end(),
					lFibDbIdentifier ) == liAllDbIdentifiers.end() ){
		//no such identifier in database
		return false;
	}//else Fib database object exists
	return true;
}


/**
 * @return the set with the categories this Fib object source is in
 * 	(e.g. "Fib database", "file")
 */
std::set< std::string > cFibObjectSourceFibDb::getCategories() const {
	
	set< string > setCategories;
	setCategories.insert( QObject::tr("Fib database").toStdString() );
	return setCategories;
}


/**
 * This method will store this Fib database object source object to
 * the given stream.
 *
 * @see restoreFibObjectSource()
 * @param stream the output stream to which to store this object
 * @return true if this Fib database object source object could be
 * 	stored, else false
 */
bool cFibObjectSourceFibDb::store( ostream & stream ) const{
	
	if ( ( &stream == NULL ) || ( ! stream.good() ) ){
		//no good stream -> return false
		return false;
	}
	stream<<"<fib_object_source type=\"Fib database\" "<<
		 "identifier=\""<<lFibDbIdentifier<<"\" />"<<endl;
	return true;
}


/**
 * This method will restore the Fib database object source object from
 * the given stream.
 *
 * @see storeFibObjectSource()
 * @param stream the input stream from which to read the Fib object source
 * @return an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid stream
 * 		- -2 loading error, invalid data in stream
 * 		- 1 loading warning, invalid data in stream, error could be corrected
 * 		- 2 loading warning, invalid data in stream, maybe the loaded
 * 			object is wrong
 */
int cFibObjectSourceFibDb::restoreFibObjectSource( istream & stream ){
	
	TiXmlDocument xmlDocFibObject;

	stream >> xmlDocFibObject;
	
	if ( xmlDocFibObject.Error() ){
		//error while loading to stream
		return -1;
	}
	
	return restoreFibObjectSource( &xmlDocFibObject );
}


/**
 * This method will restore the Fib database object source object from
 * the given TinyXml node.
 *
 * @see storeFibObjectSource()
 * @param pXmlNode a pointer to the TinyXml node where the Fib object
 * 	source object is stored in
 * @return an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlNode
 * 		- -2 loading error, invalid data in pXmlNode
 * 		- 1 loading warning, invalid data in pXmlNode, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlNode, maybe the loaded
 * 			object is wrong
 */
int cFibObjectSourceFibDb::restoreFibObjectSource( const TiXmlNode * pXmlNode ){
	
#ifdef DEBUG_RESTORE_XML
	//print debugging output
	printf("restoring cFibObjectSourceFibDb\n" );
#endif//DEBUG_RESTORE_XML
	if ( pXmlNode == NULL ){
		//nothing to restore
#ifdef DEBUG_RESTORE_XML
		//print debugging output
		printf("nothing to restore\n" );
#endif//DEBUG_RESTORE_XML
		return -1;
	}
	int iRestoreStatus = 0;
	
	//as long no Fib element was read and no error occured
	while ( ( pXmlNode != NULL ) && ( 0 <= iRestoreStatus ) ){
		//get type of XML element
		const int iType = pXmlNode->Type();
		switch ( iType ){
			case TiXmlNode::ELEMENT:{
				/*check if this is a valid Fib element XML element, create
				the apropirate Fib element and call its restoreXml() method*/
				const TiXmlElement * pXmlElement = pXmlNode->ToElement();
				if ( pXmlElement == NULL ){
					//Warning: nothing to load
#ifdef DEBUG_RESTORE_XML
					//print debugging output
					printf("not valid xml sub element\n" );
#endif//DEBUG_RESTORE_XML
					return -1;
				}
				const string szElementType( pXmlElement->Value() );
				
#ifdef DEBUG_RESTORE_XML
				printf( "Restoring subelement \"%s\" (iRestoreStatus now %i)\n",
					szElementType.c_str(), iRestoreStatus );
#endif
				//<fib_object_source type="Fib database" identifier="-20">
				if ( szElementType == "fib_object_source" ){
					//if exists get "type" and "identifier" attributes
					//if exists get "type" attribute
					const char * szXmlName =
						pXmlElement->Attribute( "type" );
					if ( szXmlName == NULL ){
						if ( iRestoreStatus == 0 ){
							//Warning: unknown element type
							iRestoreStatus = 1;
						}
					}else if ( strncmp( "Fib database", szXmlName, 12 ) != 0 ){
						//type not "Fib database"
						if ( iRestoreStatus == 0 ){
							//Warning: unknown element type
							iRestoreStatus = 1;
						}
					}
					//if exists get "identifier" attribute
					const char * szXmlIdentifier =
						pXmlElement->Attribute( "identifier" );
					if ( szXmlIdentifier ){
						//"identifier" attribute exists
						lFibDbIdentifier = atol( szXmlIdentifier );
					}else{//no identifier ->invalid data in pXmlElement
						return -2;
					}
					//all read whats needed
					return iRestoreStatus;
				}else{//unknown element type
					if ( iRestoreStatus == 0 ){
						//Warning: unknown element type
						iRestoreStatus = 1;
					}
				}
				
			}break;
			case TiXmlNode::DOCUMENT:{
				return restoreFibObjectSource( pXmlNode->FirstChild() );
			}break;
			case TiXmlNode::DECLARATION:
			case TiXmlNode::COMMENT:{
				//ignore
			}break;
			case TiXmlNode::TEXT:
			case TiXmlNode::UNKNOWN:
			default:
				//ignore; Warning: invalid object
				iRestoreStatus = 2;
		}//end switch XML element type
		//if no  object was read check next XML eleemnt
		pXmlNode = pXmlNode->NextSibling();
	}//end as long no object was read and no error occured
	
	return iRestoreStatus;
}


/**
 * This method will restore the Fib database object source object from
 * the given input stream and return a pointer to it.
 * Beware: You have to care that the returned Fib database object source
 * 	object is deleted.
 *
 * @see storeFibObjectSource()
 * @param stream the input stream from which to read the Fib object source
 * @param iOutStatus if not NULL an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid stream
 * 		- -2 loading error, invalid data in stream
 * 		- 1 loading warning, invalid data in stream, error could be corrected
 * 		- 2 loading warning, invalid data in stream, maybe the loaded
 * 			object is wrong
 * @return a pointer to the restored Fib database object source object
 * 	or NULL if non could be restored
 */
cFibObjectSourceFibDb * cFibObjectSourceFibDb::restore(
		istream & stream, int * iOutStatus ){
	
	TiXmlDocument xmlDocFibObject;

	stream >> xmlDocFibObject;
	
	if ( xmlDocFibObject.Error() ){
		//error while loading to stream
		if ( iOutStatus ){
			(*iOutStatus) = -1;
		}
		return NULL;
	}
	
	return restore( &xmlDocFibObject, iOutStatus );
}


/**
 * This method will restore the Fib database object source object from
 * the given TinyXml node and return a pointer to it.
 * Beware: You have to care that the returned Fib database object source
 * 	object is deleted.
 *
 * @see storeFibObjectSource()
 * @param pXmlNode a pointer to the TinyXml node where the Fib object
 * 	source object is stored in
 * @param iOutStatus if not NULL an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlNode
 * 		- -2 loading error, invalid data in pXmlNode
 * 		- 1 loading warning, invalid data in pXmlNode, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlNode, maybe the loaded
 * 			object is wrong
 * @return a pointer to the restored Fib database object source object or NULL if
 * 	non could be restored
 */
cFibObjectSourceFibDb * cFibObjectSourceFibDb::restore(
		const TiXmlNode * pXmlNode, int * iOutStatus ){
	
	int iInternalOutStatus = 0;
	
	cFibObjectSourceFibDb * pRestoreFibObjectSource =
		new cFibObjectSourceFibDb( pXmlNode, &iInternalOutStatus );
	
	if ( iOutStatus != NULL ){
		//transfer the output status
		(*iOutStatus) = iInternalOutStatus;
	}
	
	if ( iInternalOutStatus < 0 ){
		//error while restoring -> return NULL
		delete pRestoreFibObjectSource;
		return NULL;
	}
	
	return pRestoreFibObjectSource;
}


/**
 * This method checks if the given Fib database object source object is
 * equal to this Fib database object source object.
 *
 * @param fibObjectSource the Fib database object source object to compare with this
 * @return true if the given Fib database object source object is equal
 * 	to this Fib database object source object, else false
 */
bool cFibObjectSourceFibDb::equal( const cFibObjectSource & fibObjectSource ) const{
	
	return ( (*this) == fibObjectSource );
}


/**
 * This method checks if the given Fib database object source object is
 * equal to this Fib database object source object.
 *
 * @param fibObjectSource the Fib database object source object to
 * 	compare with this
 * @return true if the given Fib database object source object is equal
 * 	to this Fib database object source object, else false
 */
bool cFibObjectSourceFibDb::operator==(
		const cFibObjectSource & fibObjectSource ) const{
	
	if ( getName() != fibObjectSource.getName() ){
		//not Fib object source object not of same type
		return false;
	}
	
	return ( lFibDbIdentifier ==
		((cFibObjectSourceFibDb & )fibObjectSource).lFibDbIdentifier );
}












