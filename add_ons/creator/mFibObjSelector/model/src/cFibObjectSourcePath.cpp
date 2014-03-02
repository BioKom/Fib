/**
 * @file cFibObjectSourcePath
 * file name: cFibObjectSourcePath.cpp
 * @author Betti Oesterholz
 * @date 29.09.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for information for loading a Fib object
 * from a given path.
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
 * from a given path.
 *
 * ## File format ##
 *
 * A Fib information object for loading a Fib object will be stored in
 * the XML format.
 * The name of the root element is "fib_object_source". It has two
 * attributes "type" and "path".
 * The "type" attribute is always "path". The attribute
 * "path" gives the path to the Fib object.
 * @see szPath
 *
 * example:
       <fib_object_source type="path" path="/home/biokom/fib_objects">
 *
 *
 * @see cFibObjectSource
 * @see cFibElement
 * @see cFibObjectInfo
 * @see cFibNode
 */
/*
History:
29.09.2013  Oesterholz  created
02.03.2014  Oesterholz  categories for Fib object source added: getCategories()
*/


//switches for debugging proposes
//#define DEBUG
//#define DEBUG_RESTORE_XML


#include "cFibObjectSourcePath.h"

#include <cstring>
#include <iostream>
#include <fstream>
#include <stdio.h>

#include <QObject>

#include "cFibElement.h"



using namespace std;
using namespace fib::nCreator;


/**
 * The standard constructor for a path Fib object source object.
 *
 * @param szInPath the path to the to load Fib object
 * 	@see szPath
 */
cFibObjectSourcePath::cFibObjectSourcePath( const std::string & szInPath ):
		szPath( szInPath ) {
	//nothing to do
}


/**
 * The copy constructor for a path Fib object source object.
 *
 * @param fibObjectSourcePath the path Fib object source object to copy
 */
cFibObjectSourcePath::cFibObjectSourcePath(
		const cFibObjectSourcePath & fibObjectSourcePath ):
		szPath( fibObjectSourcePath.szPath ) {
	//nothing to do
}


/**
 * This constructor will restore the path Fib object source object from
 * the given input stream.
 *
 * @see store()
 * @param stream the input stream from which to read the path Fib object
 * 	source object
 * @param iOutStatus if not NULL an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid stream
 * 		- -2 loading error, invalid data in stream
 * 		- 1 loading warning, invalid data in stream, error could be corrected
 * 		- 2 loading warning, invalid data in stream, maybe the loaded
 * 			object is wrong
 */
cFibObjectSourcePath::cFibObjectSourcePath( istream & stream,
		int * iOutStatus ):szPath( "" ) {
	
	if ( iOutStatus != NULL ) {
		(*iOutStatus) = restoreFibObjectSource( stream );
	}else{//don't use iOutStatus
		restoreFibObjectSource( stream );
	}
}


/**
 * This constructor will restore the path Fib object source object from
 * the given TinyXml node.
 *
 * @see store()
 * @param pXmlNode a pointer to the TinyXml node where the path Fib object
 * 	source object is stored in
 * @param iOutStatus if not NULL an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlNode
 * 		- -2 loading error, invalid data in pXmlNode
 * 		- 1 loading warning, invalid data in pXmlNode, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlNode, maybe the loaded
 * 			object is wrong
 */
cFibObjectSourcePath::cFibObjectSourcePath( const TiXmlNode * pXmlNode,
		int * iOutStatus ):szPath( "" ) {
	
	if ( iOutStatus != NULL ) {
		(*iOutStatus) = restoreFibObjectSource( pXmlNode );
	}else{//don't use iOutStatus
		restoreFibObjectSource( pXmlNode );
	}
}


/**
 * destructor
 */
cFibObjectSourcePath::~cFibObjectSourcePath() {
	//nothing to do
}



/**
 * @return the name of this class "cFibObjectSourcePath"
 */
string cFibObjectSourcePath::getName() const {
	
	return string( "cFibObjectSourcePath" );
}

/**
 * @return the path to the to load Fib object
 * 	@see szPath
 */
string cFibObjectSourcePath::getPath() const {
	
	return szPath;
}


/**
 * This method creates a copy of this object and returns it.
 *
 * @return a pointer to a copy of this object
 */
cFibObjectSourcePath * cFibObjectSourcePath::clone() const {
	
	return new cFibObjectSourcePath( *this );
}


/**
 * This method loads the Fib object from the source and returns a
 * pointer to it.
 * If no Fib object can be loaded NULL will be returned.
 * Beware: You have to care that the loaded Fib object will be deleted.
 *
 * @see storeFibObject()
 * @see szPath
 * @see getPath()
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
cFibElement * cFibObjectSourcePath::loadFibObject( int * iOutStatus,
		set< string > * pOutSetChangebelBy ) const {
	
	if ( pOutSetChangebelBy ) {
		pOutSetChangebelBy->clear();
	}
	if ( szPath.empty() ) {
		//no file name exists -> nothing to load
		return NULL;
	}
	
	cFibElement * pRestoredFibObject = NULL;
	int iOutStatusIntern;
	if ( szPath.compare( szPath.size() - 4, 4, ".xml" ) == 0 ) {
		//restore to file in xml -format
		ifstream inFile( szPath.c_str() );
		
		if ( ! inFile.good() ) {
			DEBUG_OUT_EL2(<<"Error: Can't open file."<<endl<<flush);
			if ( iOutStatus ) {
				//remember output status
				(*iOutStatus) = -1;
			}
			return NULL;
		}
		
		pRestoredFibObject = cFibElement::restoreXml( inFile , &iOutStatusIntern );
		
#ifdef DEBUG
		if ( iOutStatusIntern == 0 ) {
			cout<<"Restoring Fib object in the Xml format from the file \""<<
				szPath <<"\" successfull. "<<endl;
		}else if ( 0 < iOutStatusIntern ) {
			cerr<<"Warning: Restoring Fib object in the Xml format from the file \""<<
				szPath <<"\" not successfull. (return status="<< iOutStatusIntern <<")"<<endl;
		}else{//( iOutStatusIntern < 0 )
			cerr<<"Error: Restoring Fib object in the Xml format from the file \""<<
				szPath <<"\" not successfull. (return status="<< iOutStatusIntern <<")"<<endl;
		}
#endif //DEBUG
	}else{//restore to file in compressed format
		ifstream inFile( szPath.c_str(), ios_base::in | ios_base::binary );
		
		if ( ! inFile.good() ) {
			DEBUG_OUT_EL2(<<"Error: Can't open file."<<endl<<flush);
			if ( iOutStatus ) {
				//remember output status
				(*iOutStatus) = -1;
			}
			return NULL;
		}
		
		pRestoredFibObject = cFibElement::restore( inFile , &iOutStatusIntern );
		
#ifdef DEBUG
		if ( iOutStatusIntern == 0 ) {
			cout<<"Restoring Fib object in the compressed format from the file \""<<
				szPath <<"\" successfull. "<<endl;
		}else if ( 0 < iOutStatusIntern ) {
			cerr<<"Warning: Restoring Fib object in the compressed format from the file \""<<
				szPath <<"\" not successfull. (return status="<< iOutStatusIntern <<")"<<endl;
		}else{
			cerr<<"Error: Restoring Fib object in the compressed format from the file \""<<
				szPath <<"\" not successfull. (return status="<< iOutStatusIntern <<")"<<endl;
		}
#endif //DEBUG
	}
	if ( iOutStatus ) {
		//remember output status
		(*iOutStatus) = iOutStatusIntern;
	}
	if ( iOutStatusIntern < 0 ) {
		if ( pRestoredFibObject != NULL ) {
			//delete loaded Fib object
			pRestoredFibObject->deleteObject();
		}
		return NULL;
	}
	if ( pRestoredFibObject == NULL ) {
		cerr<<"Error: No Fib object restored."<<endl;
		return NULL;
	}
	if ( pOutSetChangebelBy ) {
		//TODO adapt for operating system users or/and with optional part entry
		pOutSetChangebelBy->insert("all");
	}
	return pRestoredFibObject;
}


/**
 * This method will store the given Fib object to the location this object
 * specifies.
 *
 * @see loadFibObject()
 * @see szPath
 * @see getPath()
 * @param pFibObject a pointer to the Fib object to store
 * @return true if the given Fib object could be stored, else false
 */
bool cFibObjectSourcePath::storeFibObject( const cFibElement * pFibObject ) const {
	
	if ( pFibObject == NULL ) {
		//no Fib object to store given
		return false;
	}
	if ( szPath.empty() ) {
		//no file name exists
		return false;
	}
	//store depending on file ending
	if ( szPath.compare( szPath.size() - 4, 4, ".xml" ) == 0 ) {
		//store to file in Xml format
		ofstream outFile( szPath.c_str() );
		
		DEBUG_OUT_L2(<<"Storing Fib object in the Xml format to the file "<< szPath <<" . "<<endl<<flush);
		
		const bool bStoreSuccesfull = pFibObject->storeXml( outFile );
		
		if ( ! bStoreSuccesfull ) {
			
			DEBUG_OUT_EL2(<<"Error: Storing the data of the converted Fib object "<<
				"in the Xml format to the file "<< szPath <<" failed."<<endl<<flush);
			return false;
		}
	}else{//store to file in compressed format
		DEBUG_OUT_L2(<<"Storing Fib object in the compressed format to the file "<< szPath <<" . "<<endl<<flush);
		
		ofstream outFile( szPath.c_str(), ios_base::out | ios_base::binary );
		
		const bool bStoreSuccesfull = pFibObject->store( outFile );
		
		if ( ! bStoreSuccesfull ) {
	
			DEBUG_OUT_EL2(<<"Error: Storing the data of the converted Fib object "<<
				"in the compressed Fib format to the file "<< szPath <<" failed."<<endl<<flush);
			return false;
		}
	}//Fib object stored
	return true;
}


/**
 * This method checks if the Fib object source exists.
 *
 * @return true if the source for the Fib object exists, else false
 */
bool cFibObjectSourcePath::checkSource() const {
	
	if ( szPath.empty() ) {
		//no file name exists -> nothing to load
		return false;
	}
	//try to open the Fib object file / path
	FILE * pFibObjectFile = fopen( szPath.c_str() , "r" );
	if ( pFibObjectFile == NULL ) {
		//no such file
		return false;
	}//else Fib object file exists
	fclose( pFibObjectFile );
	
	return true;
}


/**
 * @return the set with the categories this Fib object source is in
 * 	(e.g. "Fib database", "file")
 */
std::set< std::string > cFibObjectSourcePath::getCategories() const {
	
	set< string > setCategories;
	setCategories.insert( QObject::tr("file").toStdString() );
	return setCategories;
}

/**
 * This method will store this path Fib object source object to
 * the given stream.
 *
 * @see restoreFibObjectSource()
 * @param stream the output stream to which to store this object
 * @return true if this path Fib object source object could be
 * 	stored, else false
 */
bool cFibObjectSourcePath::store( ostream & stream ) const {
	
	if ( ( &stream == NULL ) || ( ! stream.good() ) ) {
		//no good stream -> return false
		return false;
	}
	stream<<"<fib_object_source type=\"path\" "<<
		 "path=\""<<szPath<<"\" />"<<endl;
	return true;
}


/**
 * This method will restore the path Fib object source object from
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
int cFibObjectSourcePath::restoreFibObjectSource( istream & stream ) {
	
	TiXmlDocument xmlDocFibObject;

	stream >> xmlDocFibObject;
	
	if ( xmlDocFibObject.Error() ) {
		//error while loading from stream
		return -1;
	}
	
	return restoreFibObjectSource( &xmlDocFibObject );
}


/**
 * This method will restore the path Fib object source object from
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
int cFibObjectSourcePath::restoreFibObjectSource( const TiXmlNode * pXmlNode ) {
	
#ifdef DEBUG_RESTORE_XML
	//print debugging output
	printf("restoring cFibObjectSourcePath\n" );
#endif//DEBUG_RESTORE_XML
	if ( pXmlNode == NULL ) {
		//nothing to restore
#ifdef DEBUG_RESTORE_XML
		//print debugging output
		printf("nothing to restore\n" );
#endif//DEBUG_RESTORE_XML
		return -1;
	}
	int iRestoreStatus = 0;
	
	//as long no Fib element was read and no error occured
	while ( ( pXmlNode != NULL ) && ( 0 <= iRestoreStatus ) ) {
		//get type of XML element
		const int iType = pXmlNode->Type();
		switch ( iType ) {
			case TiXmlNode::ELEMENT:{
				//read Fib object source path object from XML element
				const TiXmlElement * pXmlElement = pXmlNode->ToElement();
				if ( pXmlElement == NULL ) {
					//Warning: nothing to load
#ifdef DEBUG_RESTORE_XML
					//print debugging output
					printf("not valid xml sub element\n" );
#endif//DEBUG_RESTORE_XML
					return -1;
				}
				const string szElementType( pXmlElement->Value() );
				
#ifdef DEBUG_RESTORE_XML
				printf( "Restoring XML element \"%s\" (iRestoreStatus now %i)\n",
					szElementType.c_str(), iRestoreStatus );
#endif
				//<fib_object_source type="path" path="/home/biokom/fib_objects">
				if ( szElementType == "fib_object_source" ) {
					//if exists get "type" and "path" attributes
					//if exists get "type" attribute
					const char * szXmlName =
						pXmlElement->Attribute( "type" );
					if ( szXmlName == NULL ) {
						if ( iRestoreStatus == 0 ) {
							//Warning: unknown element type
							iRestoreStatus = 1;
						}
					}else if ( strncmp( "path", szXmlName, 4 ) != 0 ) {
						//type not "path"
						if ( iRestoreStatus == 0 ) {
							//Warning: unknown element type
							iRestoreStatus = 1;
						}
					}
					//if exists get "path" attribute
					const char * szXmlPath = pXmlElement->Attribute( "path" );
					if ( szXmlPath ) {
						//"path" attribute exists
						szPath = string( szXmlPath );
					}else{//no path -> invalid data in pXmlElement
						return -2;
					}
					//all read whats needed
					return iRestoreStatus;
				}else{//unknown element type
					if ( iRestoreStatus == 0 ) {
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
				//ignore; Warning: invalid  object
				iRestoreStatus = 2;
		}//end switch XML element type
		//if no object was read check next XML element
		pXmlNode = pXmlNode->NextSibling();
	}//end while as long no object was read and no error occured
	
	return iRestoreStatus;
}


/**
 * This method will restore the path Fib object source object from
 * the given input stream and return a pointer to it.
 * Beware: You have to care that the returned path Fib object source
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
 * @return a pointer to the restored path Fib object source object or NULL
 * 	if non could be restored
 */
cFibObjectSourcePath * cFibObjectSourcePath::restore(
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
	
	return restore( &xmlDocFibObject, iOutStatus );
}


/**
 * This method will restore the path Fib object source object from
 * the given TinyXml node and return a pointer to it.
 * Beware: You have to care that the returned path Fib object source
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
 * @return a pointer to the restored path Fib object source object or NULL
 * 	if non could be restored
 */
cFibObjectSourcePath * cFibObjectSourcePath::restore(
		const TiXmlNode * pXmlNode, int * iOutStatus ) {
	
	int iInternalOutStatus = 0;
	
	cFibObjectSourcePath * pRestoreFibObjectSource =
		new cFibObjectSourcePath( pXmlNode, &iInternalOutStatus );
	
	if ( iOutStatus != NULL ) {
		//transfer the output status
		(*iOutStatus) = iInternalOutStatus;
	}
	
	if ( iInternalOutStatus < 0 ) {
		//error while restoring -> return NULL
		delete pRestoreFibObjectSource;
		return NULL;
	}
	
	return pRestoreFibObjectSource;
}


/**
 * This method checks if the given Fib object source object is equal to
 * this path Fib object source object.
 *
 * @param fibObjectSource the Fib object source object to compare with this
 * @return true if the given Fib object source object is equal
 * 	to this path Fib object source object, else false
 */
bool cFibObjectSourcePath::equal( const cFibObjectSource & fibObjectSource ) const {
	
	return ( (*this) == fibObjectSource );
}


/**
 * This method checks if the given Fib object source object is equal to
 * this path Fib object source object.
 *
 * @param fibObjectSource the Fib object source object to
 * 	compare with this
 * @return true if the given Fib object source object is equal
 * 	to this path Fib object source object, else false
 */
bool cFibObjectSourcePath::operator==(
		const cFibObjectSource & fibObjectSource ) const {
	
	if ( getName() != fibObjectSource.getName() ) {
		//not Fib object source object not of same type
		return false;
	}
	
	return ( szPath ==
		(static_cast<const cFibObjectSourcePath & >(fibObjectSource)).szPath );
}












