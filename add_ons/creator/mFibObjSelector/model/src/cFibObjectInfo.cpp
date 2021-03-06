
//TODO check

/**
 * @file cFibObjectInfo
 * file name: cFibObjectInfo.cpp
 * @author Betti Oesterholz
 * @date 13.09.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a information about a Fib object.
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
 * This file implements a class for a information about a Fib object.
 *
 * ## File format ##
 *
 * A Fib information object will be stored as in the XML format.
 * The name of the root element is "fib_object_info". It has the attributes
 * "identifier", "name", "countFibElements", "countInVariables" and
 * "countExtSubobjects".
 * - The "identifier" attribute stores the identifiers of this Fib object.
 *   @see ulIdentifier
 * - The optional "name" attribute contains the Fib object name.
 *   @see szNameOfFibObject
 * - The optional "countFibElements" attribute contains the number of
 *   Fib elements in the Fib object for this Fib object info object.
 *   @see ulNumberOfFibElements
 *   @see cFibElement::getNumberOfElements()
 * - The optional "countInVariables" attribute contains the number of
 *   input variables for the Fib object for this Fib object info object.
 *   @see ulNumberOfInputVariables
 *   @see cRoot::getNumberOfInputVariables()
 * - The optional "countExtSubobjects" attribute contains the number of
 *   external subobjects for the Fib object for this Fib object info object.
 *   @see ulNumberOfExtSubobjects
 *   @see cRoot::getNumberOfExternSubobjects()
 *
 * For the other class members it contains subelements (all are optional):
 * - The subelement with the name "description" contains the description
 *    text for the Fib object.
 * - The Fib object source object, which stores the data where the Fib object
 *    for this info is stored, is stored with its own store method (
 *    @see pFibObjectSource and @see cFibObjectSource::store() ).
 * - The subelement with the name "connected_to" contains the information
 *    about connected Fib objects ( @see mapConnectedTo ).
 *    It has for every connection type (map mapConnectedTo key) a
 *    subelement with the the name "connection", which has the attribute
 *    "name" for the type of the connection (map mapConnectedTo key).
 *    The "connection" element contains for every connected Fib object an
 *    element with name "identifier", wich contains the identifier (number)
 *    of a Fib element which is connected to the stored Fib object via
 *    the connection type.
 * - The subelement with the name "last_used" contains the data when the
 *    Fib object was last used. ( @see vecLastUsed )
 *    It contains a list with the timestamp / intervall data.
 *    Its subelements have the name "used_till" which each contains the
 *    attributes "timestamp" and "count_uses". The "timestamp" is the
 *    time stamp and and "count_uses" is the number of how often the
 *    Fib object was used betwean the time stamp and the next earlier time
 *    stamp. The "timestamp" generally represents the number of seconds
 *    since 00:00 hours, Jan 1, 1970 UTC (i.e., the current unix timestamp).
 *    @see std::time()
 * - The element "changeable_by" contains for every user which can change
 *    the Fib object (@see changeableBy) a "user" element.
 *    The "user" element as the attribute "name" which contains the name of
 *    a user which can change the Fib object.
 * - The optional element "preview" contains the information for the
 *    preview image for the Fib object. It should contain a Fib object info
 *    XML element, like specified here.
 *    @see pPreviewFibObject
 * - The optional element "in_var_types" contains a list for known input
 *    variable types. For each input variable, for which the type is known,
 *    it contains a "input_variable" element with the attributes "number"
 *    and "type". The attribute "number" contains the number of the input
 *    variable (counting starts with 1) and the attribute "type" contains
 *    the type of the input variable.
 *    @see typeOfInputVariables
 *    @see mapInVarTypes
 *
 * example:
    <?xml version="1.0" encoding="UTF-8"?>
    <fib_object_info identifier="17" name="example" countFibElements="1234"
          countInVariables="3" countExtSubobjects="0">
       <description>This example demonstrates the Fib object info file
          format.
       </description>
       <fib_object_source ...>
          ...
       </fib_object_source>
       <connected_to>
           <connection name="isContained">
              <identifier>6</identifier>
              <identifier>7</identifier>
           </connection>
           <connection name="sameType">
              <identifier>16</identifier>
           </connection>
       </connected_to>
       <last_used>
          <used_till timestamp="1379267017" count_uses="1"/>
          <used_till timestamp="1379266234" count_uses="2"/>
          <used_till timestamp="1379262148" count_uses="2"/>
          <used_till timestamp="1378598632" count_uses="4"/>
          ...
       </last_used>
       <changeable_by>
          <user name="all">
       </changeable_by>
       <preview>
          <fib_object_info ... >
             ...
          </fib_object_info>
       </preview>
       <in_var_types>
          <input_variable number="2" type="position dimension 1"/>
          <input_variable number="3" type="position dimension 2"/>
          <input_variable number="7" type="size radius"/>
          ...
       </in_var_types>
    </fib_object_info>
 *
 *
 * @see cFibElement
 * @see cFibNode
 * @see cFibObjectSource
 */
/*
History:
13.09.2013  Oesterholz  created
02.03.2014  Oesterholz  categories for Fib object source added
05.04.2014  Oesterholz  input variables types added
*/



#include "cFibObjectInfo.h"

#ifdef FEATURE_FIB_OBJECT_INFO_IN_VAR_TYPE_FROM_TEXT_REGEX
#include <regex>
#endif //FEATURE_FIB_OBJECT_INFO_IN_VAR_TYPE_FROM_TEXT_REGEX

#include "cFibElement.h"
#include "cRoot.h"
#include "cOptionalPart.h"

#include "cFibObjectSource.h"
#include "cFibObjectSourceFibDb.h"
#include "eFibObjectInfoChangedEvent.h"
#include "nFibObjectTools.h"
#include "cFibObjectInfoHandler.h"

//debugging switches
#define DEBUG
//#define DEBUG_RESTORE_XML


using namespace std;
using namespace fib::nCreator;


/**
 * The mutex to check for cyclic dependencies for the preview Fib object
 * info.
 * @see setPreviewFibObjectInfo()
 */
QMutex cFibObjectInfo::mutexCheckCyclicPreviewFibObjectInf;


/**
 * constructor for a Fib object info object
 *
 * @param ulInIdentifier the identifer of this Fib object info object
 * @param pInFibObjectSource a pointer to the source object for the
 * 	Fib object for this Fib object info object;
 * 	This class will try to read all needed data from the source Fib object.
 * 	@see pFibObjectSource
 * @param bExtractInfo if true the information for the Fib object info
 * 	will be extracted from the Fib object
 * 	@see extractInfoFromLoadedFibObject()
 */
cFibObjectInfo::cFibObjectInfo( const unsigned long ulInIdentifier,
		const cFibObjectSource * pInFibObjectSource, const bool bExtractInfo ):
		ulIdentifier( ulInIdentifier ),
		szNameOfFibObject(""), pFibObjectSource( NULL ), pLoadedFibObject( NULL ),
		pPreviewFibObject( NULL ), ulNumberOfInputVariables( 0 ),
		ulNumberOfExtSubobjects( 0 ), ulNumberOfFibElements( 0 ) {
		
	DEBUG_OUT_L2(<<"cFibObjectInfo("<<this<<")::cFibObjectInfo( ulInIdentifier="<<ulInIdentifier<<", pInFibObjectSource="<<pInFibObjectSource<<" ) called"<<endl<<flush);
	if ( pInFibObjectSource ) {
		//clone the given Fib object source
		pFibObjectSource = pInFibObjectSource->clone();
	}
	
	if ( bExtractInfo ) {
		loadFibObjectFromSource();
		extractInfoFromLoadedFibObject();
	}
}


/**
 * This method will restore the Fib object info object from the given
 * input stream.
 *
 * @see store()
 * @param stream the input stream from which to read the Fib object info
 * @param iOutStatus if not NULL an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid stream
 * 		- -2 loading error, invalid data in stream
 * 		- 1 loading warning, invalid data in stream, error could be corrected
 * 		- 2 loading warning, invalid data in stream, maybe the loaded
 * 			object is wrong
 */
cFibObjectInfo::cFibObjectInfo( istream & stream, int * iOutStatus ):
		ulIdentifier( 0 ), szNameOfFibObject(""),
		pFibObjectSource( NULL ), pLoadedFibObject( NULL ),
		pPreviewFibObject( NULL ), ulNumberOfInputVariables( 0 ),
		ulNumberOfExtSubobjects( 0 ), ulNumberOfFibElements( 0 ) {
	
	DEBUG_OUT_L2(<<"cFibObjectInfo("<<this<<")::cFibObjectInfo( stream, iOutStatus="<<iOutStatus<<" ) called"<<endl<<flush);
	if ( iOutStatus != NULL ) {
		(*iOutStatus) = restoreFibObjectInfo( stream );
	}else{//don't use iOutStatus
		restoreFibObjectInfo( stream );
	}
}


/**
 * This method will restore the Fib object info object from the given
 * TinyXml node.
 *
 * @see store()
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
 */
cFibObjectInfo::cFibObjectInfo( const TiXmlNode * pXmlNode,
		int * iOutStatus ): ulIdentifier( 0 ), szNameOfFibObject(""),
		pFibObjectSource( NULL ), pLoadedFibObject( NULL ),
		pPreviewFibObject( NULL ), ulNumberOfInputVariables( 0 ),
		ulNumberOfExtSubobjects( 0 ), ulNumberOfFibElements( 0 ) {
	
	DEBUG_OUT_L2(<<"cFibObjectInfo("<<this<<")::cFibObjectInfo( pXmlNode, iOutStatus="<<iOutStatus<<" ) called"<<endl<<flush);
	if ( iOutStatus != NULL ) {
		(*iOutStatus) = restoreFibObjectInfo( pXmlNode );
	}else{//don't use iOutStatus
		restoreFibObjectInfo( pXmlNode );
	}
}


/**
 * parameter constructor for a Fib object info object
 *
 * @param ulInIdentifier the identifer of this Fib object info object
 * 	@see ulIdentifier
 * @param szInNameOfFibObject the name of this Fib object info object
 * 	@see szNameOfFibObject
 * @param szInDescription the description of this Fib object info object
 * 	@see szDescription
 * @param pInFibObjectSource a pointer to the source object for the
 * 	Fib object for this Fib object info object;
 * 	Note: The Fib object won't be loaded from the source object and
 * 		so no data from it will be used for this object.
 * 	@see pFibObjectSource
 * @param setChangeableBy A list with the names of fur users, which can
 * 	change this Fib object. (e. g. "non", "all", "biokom")
 * 	@see changeableBy
 */
cFibObjectInfo::cFibObjectInfo( const unsigned long ulInIdentifier,
	const string szInNameOfFibObject, const string szInDescription,
	const cFibObjectSource * pInFibObjectSource,
	const set< string > setChangeableBy ):
		ulIdentifier( ulInIdentifier ), szNameOfFibObject( szInNameOfFibObject ),
		szDescription( szInDescription ),
		pFibObjectSource( NULL ), pLoadedFibObject( NULL ),
		changeableBy( setChangeableBy ),
		pPreviewFibObject( NULL ), ulNumberOfInputVariables( 0 ),
		ulNumberOfExtSubobjects( 0 ), ulNumberOfFibElements( 0 ) {
	
	DEBUG_OUT_L2(<<"cFibObjectInfo("<<this<<")::cFibObjectInfo( ulInIdentifier="<<ulInIdentifier<<", szInNameOfFibObject="<<szInNameOfFibObject<<", szInDescription="<<szInDescription<<", pInFibObjectSource="<<pInFibObjectSource<<", setChangeableBy ) called"<<endl<<flush);
	if ( pInFibObjectSource ) {
		//clone the given Fib object source
		pFibObjectSource = pInFibObjectSource->clone();
	}
}


/**
 * copy constructor for a Fib object info object
 *
 * @param fibObjectInfo the Fib object info object to copy
 */
cFibObjectInfo::cFibObjectInfo( const cFibObjectInfo & fibObjectInfo ):
		ulIdentifier( fibObjectInfo.ulIdentifier ),
		szNameOfFibObject( fibObjectInfo.szNameOfFibObject ),
		szDescription( fibObjectInfo.szDescription ),
		pFibObjectSource( NULL ), pLoadedFibObject( NULL ),
		mapConnectedTo( fibObjectInfo.mapConnectedTo ),
		vecLastUsed( fibObjectInfo.vecLastUsed ),
		changeableBy( fibObjectInfo.changeableBy ),
		pPreviewFibObject( fibObjectInfo.pPreviewFibObject ),
		ulNumberOfInputVariables( fibObjectInfo.ulNumberOfInputVariables ),
		ulNumberOfExtSubobjects( fibObjectInfo.ulNumberOfExtSubobjects ),
		ulNumberOfFibElements( fibObjectInfo.ulNumberOfFibElements ) {
	
	DEBUG_OUT_L2(<<"cFibObjectInfo("<<this<<")::cFibObjectInfo( fibObjectInfo ) called"<<endl<<flush);
	if ( fibObjectInfo.pFibObjectSource ) {
		pFibObjectSource = fibObjectInfo.pFibObjectSource->clone();
	}
}


/**
 * copy constructor for a Fib object info object
 * With this copy constructor the identifier can be changed for the copy.
 *
 * @param ulInIdentifier the identifer of this Fib object info object
 * 	@see ulIdentifier
 * @param fibObjectInfo the Fib object info object to copy
 */
cFibObjectInfo::cFibObjectInfo( const unsigned long ulInIdentifier,
		const cFibObjectInfo & fibObjectInfo ):
		ulIdentifier( ulInIdentifier ),
		szNameOfFibObject( fibObjectInfo.szNameOfFibObject ),
		szDescription( fibObjectInfo.szDescription ),
		pFibObjectSource( NULL ), pLoadedFibObject( NULL ),
		mapConnectedTo( fibObjectInfo.mapConnectedTo ),
		vecLastUsed( fibObjectInfo.vecLastUsed ),
		changeableBy( fibObjectInfo.changeableBy ),
		pPreviewFibObject( fibObjectInfo.pPreviewFibObject ),
		ulNumberOfInputVariables( fibObjectInfo.ulNumberOfInputVariables ),
		ulNumberOfExtSubobjects( fibObjectInfo.ulNumberOfExtSubobjects ),
		ulNumberOfFibElements( fibObjectInfo.ulNumberOfFibElements ) {
	
	DEBUG_OUT_L2(<<"cFibObjectInfo("<<this<<")::cFibObjectInfo( ulInIdentifier="<<ulInIdentifier<<", fibObjectInfo ) called"<<endl<<flush);
	if ( fibObjectInfo.pFibObjectSource ) {
		pFibObjectSource = fibObjectInfo.pFibObjectSource->clone();
	}
}


/**
 * destructor
 */
cFibObjectInfo::~cFibObjectInfo() {
	
	DEBUG_OUT_L2(<<"cFibObjectInfo("<<this<<")::~cFibObjectInfo() called"<<endl<<flush);
	mutexFibObjectInfoData.lock();
	if ( pFibObjectSource ) {
		delete pFibObjectSource;
	}
	if ( pLoadedFibObject ) {
		pLoadedFibObject->deleteObject();
	}
	mutexFibObjectInfoData.unlock();
	//send event that this Fib object info object has changed
	const eFibObjectInfoChangedEvent fibObjectInfoChangedEvent( this, true );
	sendFibObjectInfoChange( &fibObjectInfoChangedEvent );
}


/**
 * This method creates a copy of this object and returns it.
 *
 * @return a pointer to a copy of this object
 */
cFibObjectInfo * cFibObjectInfo::clone() const {
	
	DEBUG_OUT_L2(<<"cFibObjectInfo("<<this<<")::clone() called"<<endl<<flush);
	mutexFibObjectInfoData.lock();
	cFibObjectInfo * pFibObjectInfoClone = new cFibObjectInfo( *this );
	mutexFibObjectInfoData.unlock();
	DEBUG_OUT_L2(<<"cFibObjectInfo("<<this<<")::clone() done: "<<pFibObjectInfoClone<<endl<<flush);
	return pFibObjectInfoClone;
}


/**
 * This method creates a copy of this object and returns it.
 * With this clone method the identifier can be changed for the copy.
 *
 * @param ulInIdentifier the identifer of the copy Fib object info object
 * 	@see ulIdentifier
 * @return a pointer to a copy of this object
 */
cFibObjectInfo * cFibObjectInfo::clone( const unsigned long ulInIdentifier ) const {
	
	mutexFibObjectInfoData.lock();
	cFibObjectInfo * pFibObjectInfoClone =
		new cFibObjectInfo( ulInIdentifier, *this );
	mutexFibObjectInfoData.unlock();
	return pFibObjectInfoClone;
}


/**
 * @return the name of this class "cFibObjectInfo"
 */
string cFibObjectInfo::getName() const {
	
	return string( "cFibObjectInfo" );
}


/**
 * @see setIdentifier()
 * @return the identifiers of this Fib object
 * 	@see ulIdentifier
 */
unsigned long cFibObjectInfo::getIdentifier() const {
	
	mutexIdentifier.lock();
	const unsigned long ulIdentifierToReturn = ulIdentifier;
	mutexIdentifier.unlock();
	
	return ulIdentifierToReturn;
}


/**
 * This method sets the identifier for this object.
 *
 * @see ulIdentifier
 * @see getIdentifier()
 * @param ulNewIdentifier the identifiers of this Fib object
 */
void cFibObjectInfo::setIdentifier( const unsigned long ulNewIdentifier ) {
	
	mutexIdentifier.lock();
	ulIdentifier = ulNewIdentifier;
	mutexIdentifier.unlock();
	//send event that this Fib object info object has changed
	sendFibObjectInfoChange();
}


/**
 * @see setFibObjectName()
 * @return the name of the Fib object
 * 	@see szNameOfFibObject
 */
string cFibObjectInfo::getFibObjectName() const {
	
	mutexFibObjectInfoData.lock();
	const string szRetNameOfFibObject = szNameOfFibObject;
	mutexFibObjectInfoData.unlock();
	return szRetNameOfFibObject;
}


/**
 * This method set the name of the Fib object to the given name.
 *
 * @see szNameOfFibObject
 * @see getFibObjectName()
 * @param szFibObjectName the name of the Fib object to set
 */
void cFibObjectInfo::setFibObjectName( const string & szFibObjectName ) {
	
	mutexFibObjectInfoData.lock();
	szNameOfFibObject = szFibObjectName;
	mutexFibObjectInfoData.unlock();
	//send event that this Fib object info object has changed
	sendFibObjectInfoChange();
}


/**
 * @see setDescription()
 * @return the description of the Fib object
 * 	@see szDescription
 */
string cFibObjectInfo::getDescription() const {
	
	mutexFibObjectInfoData.lock();
	const string szRetDescription = szDescription;
	mutexFibObjectInfoData.unlock();
	return szRetDescription;
}


/**
 * This method set the description of the Fib object to the given description.
 *
 * @see szDescription
 * @see getDescription()
 * @param szFibObjectDescription the description of the Fib object to set
 */
void cFibObjectInfo::setDescription( const string & szFibObjectDescription ) {
	
	mutexFibObjectInfoData.lock();
	szDescription = szFibObjectDescription;
	mutexFibObjectInfoData.unlock();
	//send event that this Fib object info object has changed
	sendFibObjectInfoChange();
}


/**
 * @see setFibObjectSource()
 * @return a pointer to the Fib object source object
 * 	@see pFibObjectSource
 */
cFibObjectSource * cFibObjectInfo::getFibObjectSource() {
	
	mutexFibObjectSource.lock();
	cFibObjectSource * pRetFibObjectSource = pFibObjectSource;
	mutexFibObjectSource.unlock();
	return pRetFibObjectSource;
}


/**
 * @see setFibObjectSource()
 * @return a const pointer to the Fib object source object
 * 	@see pFibObjectSource
 */
const cFibObjectSource * cFibObjectInfo::getFibObjectSource() const {
	
	mutexFibObjectSource.lock();
	const cFibObjectSource * pRetFibObjectSource = pFibObjectSource;
	mutexFibObjectSource.unlock();
	return pRetFibObjectSource;
}


/**
 * This method sets the Fib object source object to a copy of the given
 * Fib object source object.
 * Note: This method will clone the given pInFibObjectSource object.
 *
 * @see pFibObjectSource
 * @see getFibObjectSource()
 * @return a pointer to the Fib object source object to set
 */
bool cFibObjectInfo::setFibObjectSource( const cFibObjectSource * pInFibObjectSource ) {
	
	mutexFibObjectSource.lock();
	if ( pFibObjectSource ) {
		//delete old Fib object source object
		delete pFibObjectSource;
		pFibObjectSource = NULL;
	}
	if ( pInFibObjectSource ) {
		pFibObjectSource = pInFibObjectSource->clone();
	}
	mutexFibObjectSource.unlock();
	deleteLoadedFibObject();
	//send event that this Fib object info object has changed
	sendFibObjectInfoChange();
	
	return true;
}


/**
 * This method loads the Fib object from the source and returns a
 * pointer to it. If a Fib object is already loaded it will be
 * returned (without reloading it). If you like to relode the Fib object
 * first delete the loaded Fib object with deleteLoadedFibObject() .
 * If no Fib object can be loaded NULL will be returned.
 * Note: This object will care that the returned Fib object will be
 * 	deleted. (On destruction of this object.)
 *
 * @see pLoadedFibObject
 * @see deleteLoadedFibObject()
 * @see pFibObjectSource
 * @see getFibObjectSource()
 * @see setFibObjectSource()
 * @param iOutStatus if not NULL an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlNode
 * 		- -2 loading error, invalid data in pXmlNode
 * 		- 1 loading warning, invalid data in pXmlNode, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlNode, maybe the loaded
 * 			object is wrong
 * @return a pointer to the loaded Fib object, or NULL if non could be loaded
 */
cFibElement * cFibObjectInfo::loadFibObjectFromSource( int * iOutStatus ) {
	
	//the Fib object for this Fib object info is used now
	setFibObjectUsed();
	
	mutexFibObjectInfoData.lock();
	if ( pLoadedFibObject ) {
		//the source object loaded allready -> return pointer to it
		cFibElement * pRetLoadedFibObject = pLoadedFibObject;
		mutexFibObjectInfoData.unlock();
		return pRetLoadedFibObject;
	}//else
	mutexFibObjectSource.lock();
	if ( pFibObjectSource ) {
		//load the Fib object from its source
		int iLoadStatus = 0;
		set< string > setChangebelBy;
		
		pLoadedFibObject = pFibObjectSource->loadFibObject(
			&iLoadStatus, &setChangebelBy );
		mutexFibObjectSource.unlock();
		
		if ( iOutStatus ) {
			(*iOutStatus) = iLoadStatus;
		}
		changeableBy = setChangebelBy;
		
		mutexFibObjectInfoData.unlock();
		return pLoadedFibObject;
	}//else can't load the Fib object
	mutexFibObjectSource.unlock();
	mutexFibObjectInfoData.unlock();
	return NULL;
}

/**
 * This method will delete the loaded Fib object, if it exists.
 *
 * @see pLoadedFibObject
 * @see loadFibObjectFromSource()
 * @see pFibObjectSource
 * @see getFibObjectSource()
 * @see setFibObjectSource()
 * @return ture if the loaded Fib object was deleted, else false (no
 * 	Fib object loaded)
 */
bool cFibObjectInfo::deleteLoadedFibObject() {
	
	mutexFibObjectInfoData.lock();
	if ( pLoadedFibObject ) {
		//loaded Fib object exists -> delete it
		pLoadedFibObject->deleteObject();
		pLoadedFibObject = NULL;
		mutexFibObjectInfoData.unlock();
		return true;
	}//else no loaded Fib object to delete
	mutexFibObjectInfoData.unlock();
	return false;
}


/**
 * This method will extract all possible information for the Fib object
 * info.
 * It will adapt members of this object to the extracted information.
 *
 * @param true if information could be extracted, else false
 */
bool cFibObjectInfo::extractInfoFromLoadedFibObject() {
	
	DEBUG_OUT_L2(<<"cFibObjectInfo("<<this<<")::extractInfoFromLoadedFibObject() called"<<endl<<flush);
	mutexFibObjectInfoData.lock();
	if ( pLoadedFibObject == NULL ) {
		//nothing to evaluate the information from
		mutexFibObjectInfoData.unlock();
		return false;
	}
	//evalue the number of Fib elements
	ulNumberOfFibElements = pLoadedFibObject->getNumberOfElements();
	DEBUG_OUT_L2(<<"cFibObjectInfo("<<this<<")::extractInfoFromLoadedFibObject() number of elements "<<ulNumberOfFibElements<<endl<<flush);
	
	if ( pLoadedFibObject->getType() == 'r' ) {
		
		cRoot * pLoadedRootElement = ((cRoot*)(pLoadedFibObject));
		//evalue the number of input variables
		ulNumberOfInputVariables = pLoadedRootElement->getNumberOfInputVariables();
		//evalue the number of external subobjects
		ulNumberOfExtSubobjects  = pLoadedRootElement->getNumberOfExternSubobjects();
		//get the optional part for the top most root element
		cOptionalPart * pOptionalPart =
			pLoadedRootElement->getOptionalPart();
		if ( pOptionalPart != NULL ) {
			const list< pair<string,string> > liAllEntries =
				pOptionalPart->getEntries();
			
			for ( list< pair<string,string> >::const_iterator
					itrEntry = liAllEntries.begin();
					itrEntry != liAllEntries.end(); itrEntry++ ) {
				
				const string szKey = itrEntry->first;
				if ( szKey.size() < 2 ) {
					//not a entry to extract -> skip it
					continue;
				}
				const char * pSzKey = szKey.c_str();
				switch ( pSzKey[ 0 ] ) {
					case 'n':{
						//extract the Fib object name from the optional part "name" entry?
						if ( szKey == "name" ) {
							//read the name of the Fib object
							szNameOfFibObject = itrEntry->second;
							DEBUG_OUT_L2(<<"cFibObjectInfo("<<this<<")::extractInfoFromLoadedFibObject() name readed: "<<szNameOfFibObject<<endl<<flush);
						}
					}break;
					case 'd':{
						//extract the Fib object description from the optional part "description" entry?
						if ( szKey == "description" ) {
							//read the description of the Fib object
							szDescription = itrEntry->second;
							DEBUG_OUT_L2(<<"cFibObjectInfo("<<this<<")::extractInfoFromLoadedFibObject() description readed: "<<szDescription<<endl<<flush);
						}
					}break;
					case 'i':{
						if ( pSzKey[ 1 ] == 's' ) {
							/*the key begins with "is" (e.g. "isPointElement")
							 *-> add to categories*/
							setInCategories.insert( szKey );
							DEBUG_OUT_L2(<<"cFibObjectInfo("<<this<<")::extractInfoFromLoadedFibObject() categories readed: "<<szKey<<endl<<flush);
						}
						if ( szKey.compare( 0, 5, "inVar" ) == 0 ) {
							/*extract input variable types:
							 * - inVar1::name
							 * -inVar1::description
							 */
							const unsigned int uiInVar = atol( &(pSzKey[ 5 ]) );
							if ( uiInVar == 0 ) {
								//not a valid input variable -> skip
								continue;
							}
							if ( ( szKey.find( "description", 8 ) == string::npos ) &&
									( szKey.find( "name", 8 ) == string::npos ) ) {
								//the comment is not a "description" or "name" -> skip
								continue;
							}
							const typeOfInputVariables inVarType =
								getInVarTypeFromText( itrEntry->second );
							if ( inVarType == UNKNOWN ) {
								//not a valid input variable type -> skip
								continue;
							}
							mapInVarTypes[ inVarType ] = uiInVar;
						}
					}break;
					case 'D':{
						if ( szKey.compare( 0, 10, "DbObject::" ) == 0 ) {
							/*extract information about the connections to other Fib objects:
							 * (Note: map external identifiers to identifiers of this
							 * database (try to find equal cFibObjectSource))
								- DbObject::isPointElement
								- DbObject::isPointSubObject
								- DbObject::isAntialiased
								- DbObject::isNotAntialiased
								- DbObject::XXX
							*/
							//read Fib database identifier
							const longFib ulFibDbIdentifier = atol(
								itrEntry->second.c_str() );
							DEBUG_OUT_L2(<<"cFibObjectInfo("<<this<<")::extractInfoFromLoadedFibObject() read connected to for: \""<<szKey<<"\" with db identifer: "<<ulFibDbIdentifier<<"("<<itrEntry->second<<")"<<endl<<flush);
							if ( ulFibDbIdentifier != 0 ) {
								//get Fib info object handler identifier for Fib database identifer
								cFibObjectSourceFibDb fibDatabaseSource( ulFibDbIdentifier );
								
								const unsigned long ulFibInfoHandlerId =
									cFibObjectInfoHandler::getInstance()->
										getIdentifierForSource( &fibDatabaseSource );
								DEBUG_OUT_L3(<<"   Fib object info handler identifier "<<ulFibInfoHandlerId<<endl<<flush);
								if ( 0 < ulFibInfoHandlerId ) {
									//Fib info object for Fib database identifier exists
									mapConnectedTo[ szKey ].insert( ulFibInfoHandlerId );
								}
							}
						}
					}break;
					case 'c':{
						if ( szKey.compare( 0, 13, "connectedTo::" ) == 0 ) {
							/*extract information about the connections to other Fib objects:
							 * (Beware: how to map external identifiers to identifiers of this
							 * database (try to find equal cFibObjectSource))
								- connectedTo::KEY (TODO docu)
							*/
							//read Fib database identifier
							const longFib ulFibDbIdentifier = atol(
								itrEntry->second.c_str() );
							DEBUG_OUT_L2(<<"cFibObjectInfo("<<this<<")::extractInfoFromLoadedFibObject() read connected to for: \""<<szKey<<"\" with db identifer: "<<ulFibDbIdentifier<<"("<<itrEntry->second<<")"<<endl<<flush);
							if ( ulFibDbIdentifier != 0 ) {
								//get Fib info object handler identifier for Fib database identifer
								cFibObjectSourceFibDb fibDatabaseSource( ulFibDbIdentifier );
								
								const unsigned long ulFibInfoHandlerId =
									cFibObjectInfoHandler::getInstance()->
										getIdentifierForSource( &fibDatabaseSource );
								DEBUG_OUT_L3(<<"   Fib object info handler identifier "<<ulFibInfoHandlerId<<endl<<flush);
								if ( 0 < ulFibInfoHandlerId ) {
									//Fib info object for Fib database identifier exists
									mapConnectedTo[ szKey ].insert( ulFibInfoHandlerId );
								}
							}
						}
					}break;
				};//end switch for key of type
				
			}//end for all entries
			fillInMissingTypesOfInputVariables( mapInVarTypes );
		}//else nothing to evaluate the information from
	}else{//not a root element loaded
		//evalue the number of input variables
		ulNumberOfInputVariables = nFibObjectTools::evalueInputVariables(
			pLoadedFibObject ).size();
		//no external subobjects, because without root non can be given
		ulNumberOfExtSubobjects = 0;
	}//end if loaded Fib object is root element
	
	//TODO cFibObjectInfo * pPreviewFibObject
	
	
	/*try to extract the information by which users it can be changed.
	 (If from Fib database: "non".)*/
	
	
	
	mutexFibObjectInfoData.unlock();
	//send event that this Fib object info object has changed
	sendFibObjectInfoChange();

	return true;
}



/**
 * @see setInCategories
 * @see setCategories()
 * @see addCategory()
 * @see removeCategory()
 * @return the set with the categories this Fib object is in
 * 	@see setInCategories
 */
std::set< std::string > cFibObjectInfo::getCategories() const {
	
	mutexFibObjectInfoData.lock();
	mutexFibObjectSource.lock();
	std::set< std::string > setInCategoriesRet = setInCategories;
	if ( pFibObjectSource ) {
		//add the categories for the Fib object source
		 const std::set< std::string > setSourceCategories =
			 pFibObjectSource->getCategories();
		setInCategoriesRet.insert(
			setSourceCategories.begin(), setSourceCategories.end() );
	}
	mutexFibObjectSource.unlock();
	mutexFibObjectInfoData.unlock();
	return setInCategoriesRet;
}


/**
 * This method sets the categories this Fib object is in to the given set.
 *
 * @see setInCategories
 * @see getCategories()
 * @see addCategory()
 * @see removeCategory()
 * @param setInputCategories the set with the categories this Fib object is in
 */
void cFibObjectInfo::setCategories( const std::set< std::string > & setInputCategories ) {
	
	mutexFibObjectInfoData.lock();
	setInCategories = setInputCategories;
	mutexFibObjectInfoData.unlock();
	sendFibObjectInfoChange();
}


/**
 * This method adds the given category to the categories this Fib object
 * is in.
 *
 * @see setInCategories
 * @see getCategories()
 * @see setCategories()
 * @see removeCategory()
 * @param strCategory the category to add to the set with the categories
 * 	this Fib object is in
 */
void cFibObjectInfo::addCategory( const std::string & strCategory ) {
	
	mutexFibObjectInfoData.lock();
	setInCategories.insert( strCategory );
	mutexFibObjectInfoData.unlock();
	sendFibObjectInfoChange();
}


/**
 * This method removes the given category from the categories this
 * Fib object is in.
 *
 * @see setInCategories
 * @see getCategories()
 * @see setCategories()
 * @see addCategory()
 * @param strCategory the category to removes from the set with the
 * 	categories this Fib object is in
 * @return true if the category could be removed, else false
 */
bool cFibObjectInfo::removeCategory( const std::string & strCategory ) {
	
	mutexFibObjectInfoData.lock();
	const bool bCouldBeRemoved = ( 0 < setInCategories.erase( strCategory ) );
	mutexFibObjectInfoData.unlock();
	sendFibObjectInfoChange();
	return bCouldBeRemoved;
}



/**
 * @return The map with connected Fib objects.
 * 	key: the connected key, of which type the connection is (e. g.
 * 		isContained, similar, sameType)
 * 	value: the identifiers of connected Fib objects
 * 		@see ulIdentifier
 * 	@see mapConnectedTo
 */
map< string, set< unsigned long > > cFibObjectInfo::getConnectedToMap() const {
	
	mutexFibObjectInfoData.lock();
	const map< string, set< unsigned long > > mapRetConnectedTo = mapConnectedTo;
	mutexFibObjectInfoData.unlock();
	return mapConnectedTo;
}


/**
 * This method returns a set of identifiers of Fib objects, which are
 * connected to this Fib object via the given key szKey.
 *
 * @see mapConnectedTo
 * @param szKey the key of the kind of connetions which should be returned
 * @return a set with identifiers of Fib objects which are connected
 * 	to this Fib object via the given key
 */
set< unsigned long > cFibObjectInfo::getConnectedFor( const string & szKey ) const {
	
	mutexFibObjectInfoData.lock();
	map< string, set< unsigned long > >::const_iterator
		itrConnectionEntry = mapConnectedTo.find( szKey );
	if ( itrConnectionEntry == mapConnectedTo.end() ) {
		//no entry exists for the given key
		mutexFibObjectInfoData.unlock();
		return set< unsigned long >();
	}//else return found entry
	const set< unsigned long > setConnections = itrConnectionEntry->second;
	mutexFibObjectInfoData.unlock();
	return setConnections;
}


/**
 * This method adds the given identifier of a Fib object to the via
 * the given key szKey to this Fib object connected Fib objects.
 *
 * @see mapConnectedTo
 * @param szKey the key of the kind of connetions, to which the
 * 	identifier should be added
 * @param ulConnectedId the identifier of the Fib object, which is
 * 	connected to this Fib object via the given key
 */
void cFibObjectInfo::addConnectionTo( const string & szKey,
		const unsigned long ulConnectedId ) {
	
	mutexFibObjectInfoData.lock();
	mapConnectedTo[ szKey ].insert( ulConnectedId );
	mutexFibObjectInfoData.unlock();
	//send event that this Fib object info object has changed
	sendFibObjectInfoChange();
}


/**
 * This method adds the given identifiers of Fib objects to the via
 * the given key szKey to this Fib object connected Fib objects.
 *
 * @see mapConnectedTo
 * @param szKey the key of the kind of connetions, to which the
 * 	identifiers should be added
 * @param setNotConnectedIds a set with the identifier of the Fib objects,
 * 	which are connected to this Fib object via the given key
 */
void cFibObjectInfo::addConnectionTo( const string & szKey,
		const set< unsigned long > & setNotConnectedIds ) {
	
	mutexFibObjectInfoData.lock();
	set< unsigned long > & setListForKey = mapConnectedTo[ szKey ];
	setListForKey.insert( setNotConnectedIds.begin(), setNotConnectedIds.end() );
	mutexFibObjectInfoData.unlock();
	//send event that this Fib object info object has changed
	sendFibObjectInfoChange();
}


/**
 * This method removes the given identifier of a Fib object from the via
 * the given key szKey to this Fib object connected Fib objects.
 *
 * @see mapConnectedTo
 * @param szKey the key of the kind of connetions, from which the
 * 	identifier should be removed
 * @param ulConnectedId the identifier of the Fib object, which is no
 * 	more connected to this Fib object via the given key
 * 	(which to remove)
 */
bool cFibObjectInfo::removeConnectionTo( const string & szKey,
		const unsigned long ulConnectedId ) {
	
	mutexFibObjectInfoData.lock();
	map< string, set< unsigned long > >::iterator
		itrConnectionEntry = mapConnectedTo.find( szKey );
	if ( itrConnectionEntry == mapConnectedTo.end() ) {
		//no entry exists for the given key -> nothing to erase
		mutexFibObjectInfoData.unlock();
		return false;
	}//else erase identifer from entry
	
	set< unsigned long > & setIdentifiers = itrConnectionEntry->second;
	const bool bIdentifierRemoved = ( 0 < setIdentifiers.erase( ulConnectedId ) );
	if ( setIdentifiers.empty() ) {
		//no connections remaining -> remove connection type
		mapConnectedTo.erase( itrConnectionEntry );
	}
	mutexFibObjectInfoData.unlock();
	//send event that this Fib object info object has changed
	sendFibObjectInfoChange();
	
	return bIdentifierRemoved;
}


/**
 * This method removes the given identifiers of Fib objects from the via
 * the given key szKey to this Fib object connected Fib objects.
 *
 * @see mapConnectedTo
 * @param szKey the key of the kind of connetions, from which the
 * 	identifiers should be removed
 * @param setNotConnectedIds a set with the identifiers of the Fib objects,
 * 	which are no more connected to this Fib object via the given key
 * 	(which to remove)
 */
unsigned int cFibObjectInfo::removeConnectionTo( const string & szKey,
		const set< unsigned long > & setNotConnectedIds ) {
	
	mutexFibObjectInfoData.lock();
	map< string, set< unsigned long > >::iterator
		itrConnectionEntry = mapConnectedTo.find( szKey );
	if ( itrConnectionEntry == mapConnectedTo.end() ) {
		//no entry exists for the given key -> nothing to erase
		mutexFibObjectInfoData.unlock();
		return false;
	}//else erase identifers from entry
	unsigned int uiNumberErasedIds = 0;
	set< unsigned long > & setIdentifiers = itrConnectionEntry->second;
	for ( set< unsigned long >::iterator itrActualId = setNotConnectedIds.begin();
			itrActualId != setNotConnectedIds.end(); itrActualId++ ) {
		//erase actual identifier
		uiNumberErasedIds += setIdentifiers.erase( *itrActualId );
	}
	if ( setIdentifiers.empty() ) {
		//no connections remaining -> remove connection type
		mapConnectedTo.erase( itrConnectionEntry );
	}
	mutexFibObjectInfoData.unlock();
	//send event that this Fib object info object has changed
	sendFibObjectInfoChange();
	
	return uiNumberErasedIds;
}


/**
 * This method returns a vector with information when the Fib object was
 * last used.
 * Every vector entry contains a time stamp and a number of how often
 * the Fib object was used betwean the time stamp and the next earlier
 * time stamp. The first entry has the lowest time stamp. Also the
 * first entry stores the last time the Fib object was used.
 *
 * @see vecLastUsed
 * @return a vector with information when the Fib object was last used
 */
vector< pair< time_t, unsigned long > > cFibObjectInfo::getLastUsedTimes() const {
	
	mutexFibObjectInfoData.lock();
	const vector< pair< time_t, unsigned long > > vecRetLastUsed = vecLastUsed;
	mutexFibObjectInfoData.unlock();
	return vecRetLastUsed;
}


/**
 * This method notices when the Fib object was used.
 * When you use the Fib object call this method.
 *
 * @see vecLastUsed
 * @param timestamp the timestamp when the Fib object was last used;
 * 	if 0 (default) the timestamp will be set to the actual time
 */
void cFibObjectInfo::setFibObjectUsed( time_t timestamp ) {
	
	mutexFibObjectInfoData.lock();
	//if timestamp is 0 use actual time, else use timestamp
	pair< time_t, unsigned long > paActualTimestamp(
		( ( timestamp == 0 ) ? time( NULL ) : timestamp ), 1 );
	unsigned long ulActualMaxNumber = 1;
	
	for ( vector< pair< time_t, unsigned long > >::iterator
			itrTimestamp = vecLastUsed.begin(); ;
			itrTimestamp++, ulActualMaxNumber *= 2 ) {
		
		if ( itrTimestamp == vecLastUsed.end() ) {
			if ( vecLastUsed.size() < 9 ) {
				//less than 9 entries -> can add new entry
				vecLastUsed.push_back( paActualTimestamp );
			}else{//add actual time stamp to last entry
				itrTimestamp--;
				if ( paActualTimestamp.first < itrTimestamp->first ) {
					/*time for last timestamp entry after actual time stamp
					 -> set time of actual timestamp entry*/
					itrTimestamp->first = paActualTimestamp.first;
				}
				itrTimestamp->second += paActualTimestamp.second;
			}
			//done
			break;
		}//else not last entry reached
		if ( paActualTimestamp.first < itrTimestamp->first ) {
			/*time for actual entry after time for actual time stamp
			 -> check next time stamp*/
			continue;
		}/*else time for actual entry befor time for actual time stamp
		-> put actual time stamp to actual entry*/
		const unsigned long ulCountSum =
			itrTimestamp->second + paActualTimestamp.second;
		if ( ulCountSum <= ulActualMaxNumber ) {
			//maximum number would not be reached -> simple add cound and done
			itrTimestamp->second = ulCountSum;
			break;
		}/*else maximum number would be reached
		-> push actual entry up*/
		const pair< time_t, unsigned long > paOldTimestamp =
			(*itrTimestamp);
		(*itrTimestamp) = paActualTimestamp;
		paActualTimestamp = paOldTimestamp;
		
	}//end for all entries in the last used vector
	mutexFibObjectInfoData.unlock();
	
	//send event that this Fib object info object has changed
	sendFibObjectInfoChange();
}


/**
 * @return a list with the names of fur users, which can change this
 * 	Fib object (e. g. "non", "all", "biokom")
 * 	@see changeableBy
 */
set< string > cFibObjectInfo::getChangeableBy() const {
	
	mutexFibObjectInfoData.lock();
	const set< string > retChangeableBy = changeableBy;
	mutexFibObjectInfoData.unlock();
	return changeableBy;
}


/**
 * @return true if the given user can change the Fib object for this
 * 	Fib object info
 * 	@see changeableBy
 */
bool cFibObjectInfo::canChange( const string & szUser ) const {
	//check if szUser or ""all" is in changeableBy
	mutexFibObjectInfoData.lock();
	const bool bCanChange =
		( ( changeableBy.find( szUser ) != changeableBy.end() ) ||
		( changeableBy.find( "all" ) != changeableBy.end() ) );
	mutexFibObjectInfoData.unlock();
	return bCanChange;
}


/**
 * This method will add the given user to the can change list.
 * Added users can change the Fib object for this Fib object info.
 *
 * @see changeableBy
 * @param szUser the user which can change the Fib object for this
 * 	Fib object info
 */
void cFibObjectInfo::addUserWhichCanChange( const string & szUser ) {
	
	mutexFibObjectInfoData.lock();
	changeableBy.insert( szUser );
	mutexFibObjectInfoData.unlock();
	//send event that this Fib object info object has changed
	sendFibObjectInfoChange();
}


/**
 * This method will remove the given user from the can change list.
 * Removed users can not change the Fib object for this Fib object info.
 *
 * @see changeableBy
 * @param szUser the user which can not change the Fib object for this
 * 	Fib object info
 * @return true if the user was removed (he could change the Fib object
 * 	befor), else false
 */
bool cFibObjectInfo::removeUserWhichCanChange( const string & szUser ) {
	
	mutexFibObjectInfoData.lock();
	const bool bUserRemoved = ( 0 < changeableBy.erase( szUser ) );
	mutexFibObjectInfoData.unlock();
	//send event that this Fib object info object has changed
	sendFibObjectInfoChange();
	return bUserRemoved;
}



/**
 * This method set the number of Fib elements value for this Fib object
 * info object.
 *
 * @see ulNumberOfFibElements
 * @see getNumberOfFibElements()
 * @param ulInNumberOfFibElements the number of Fib elements value
 * 	to set
 */
void cFibObjectInfo::setNumberOfFibElements(
		const unsigned long ulInNumberOfFibElements ) {
	
	mutexFibObjectInfoData.lock();
	ulNumberOfFibElements = ulInNumberOfFibElements;
	mutexFibObjectInfoData.unlock();
	//send event that this Fib object info object has changed
	sendFibObjectInfoChange();
}


/**
 * @see setNumberOfFibElements()
 * @return the number of Fib elements value
 * 	@see ulNumberOfFibElements
 */
unsigned long cFibObjectInfo::getNumberOfFibElements() const {
	
	mutexFibObjectInfoData.lock();
	const unsigned long ulRetNumberOfFibElements = ulNumberOfFibElements;
	mutexFibObjectInfoData.unlock();
	return ulRetNumberOfFibElements;
}


/**
 * This method set the number of input variables value for this Fib
 * object info object.
 *
 * @see ulNumberOfInputVariables
 * @see getNumberOfInputVariables()
 * @param ulInNumberOfInputVariables the number of input variables value
 * 	to set
 */
void cFibObjectInfo::setNumberOfInputVariables(
		const unsigned long ulInNumberOfInputVariables ) {
	
	mutexFibObjectInfoData.lock();
	ulNumberOfInputVariables = ulInNumberOfInputVariables;
	mutexFibObjectInfoData.unlock();
	//send event that this Fib object info object has changed
	sendFibObjectInfoChange();
}


/**
 * @see setNumberOfInputVariables()
 * @return the number of input variables value
 * 	@see ulNumberOfInputVariables
 */
unsigned long cFibObjectInfo::getNumberOfInputVariables() const {
	
	mutexFibObjectInfoData.lock();
	const unsigned long ulRetNumberOfInputVariables = ulNumberOfInputVariables;
	mutexFibObjectInfoData.unlock();
	return ulRetNumberOfInputVariables;
}


/**
 * This method set the number of external subobjects value for this Fib
 * object info object.
 *
 * @see ulNumberOfExtSubobjects
 * @see getNumberOfExtSubobjects()
 * @param ulInNumberOfExtSubobjects the number of external subobjects
 * 	value to set
 */
void cFibObjectInfo::setNumberOfExtSubobjects(
		const unsigned long ulInNumberOfExtSubobjects ) {
	
	mutexFibObjectInfoData.lock();
	ulNumberOfExtSubobjects = ulInNumberOfExtSubobjects;
	mutexFibObjectInfoData.unlock();
	//send event that this Fib object info object has changed
	sendFibObjectInfoChange();
}


/**
 * @see setNumberOfExtSubobjects()
 * @return the number of external subobjects value
 * 	@see ulNumberOfExtSubobjects
 */
unsigned long cFibObjectInfo::getNumberOfExtSubobjects() const {
	
	mutexFibObjectInfoData.lock();
	const unsigned long ulRetNumberOfExtSubobjects = ulNumberOfExtSubobjects;
	mutexFibObjectInfoData.unlock();
	return ulRetNumberOfExtSubobjects;
}


/**
 * This method set the Fib object info object for the preview Fib object
 * for this Fib object info object.
 *
 * @see pPreviewFibObject
 * @see getPreviewFibObjectInfo()
 * @param pInPreviewFibObject a pointer to the the Fib object info
 * 	object for the preview Fib object for this Fib object info object
 * @return true if the preview Fib object could be set, else false
 */
bool cFibObjectInfo::setPreviewFibObjectInfo( cFibObjectInfo * pInPreviewFibObject ) {
	
	mutexCheckCyclicPreviewFibObjectInf.lock();
	//check that there are no cyclic dependencies
	for ( cFibObjectInfo * pSubPreviewFibObject = pInPreviewFibObject;
			pSubPreviewFibObject != NULL;
			pSubPreviewFibObject = pSubPreviewFibObject->getPreviewFibObjectInfo() ) {
	
		if ( pSubPreviewFibObject == this ) {
			mutexCheckCyclicPreviewFibObjectInf.unlock();
			return false;
		}
	}
	
	mutexFibObjectInfoData.lock();
	pPreviewFibObject = pInPreviewFibObject;
	mutexFibObjectInfoData.unlock();
	mutexCheckCyclicPreviewFibObjectInf.unlock();
	//send event that this Fib object info object has changed
	sendFibObjectInfoChange();
	return true;
}


/**
 * @see setPreviewFibObjectInfo()
 * @return a pointer to the the Fib object info object for the preview
 * 	Fib object for this Fib object info object
 * 	@see pPreviewFibObject
 */
const cFibObjectInfo * cFibObjectInfo::getPreviewFibObjectInfo() const {
	
	mutexFibObjectInfoData.lock();
	const cFibObjectInfo * pRetPreviewFibObject = pPreviewFibObject;
	mutexFibObjectInfoData.unlock();
	return pRetPreviewFibObject;
}


/**
 * @see setPreviewFibObjectInfo()
 * @return a pointer to the the Fib object info object for the preview
 * 	Fib object for this Fib object info object
 * 	@see pPreviewFibObject
 */
cFibObjectInfo * cFibObjectInfo::getPreviewFibObjectInfo() {
	
	mutexFibObjectInfoData.lock();
	cFibObjectInfo * pRetPreviewFibObject = pPreviewFibObject;
	mutexFibObjectInfoData.unlock();
	return pRetPreviewFibObject;
}


/**
 * This method returns the type of the uiNumberOfInVar'th input variable
 * (counting starts with 1), of the Fib object of this Fib object info object.
 *
 * @see mapInVarTypes
 * @see getInVarForType()
 * @see typeOfInputVariables
 * @param uiNumberOfInVar the number of the input variable, of which to
 * 	return the type (counting starts with 1)
 * @return the type of the uiNumberOfInVar'th input variable or UNKNOWN,
 * 	if no type exists
 */
cFibObjectInfo::typeOfInputVariables cFibObjectInfo::getTypeInVar(
		const unsigned int uiNumberOfInVar ) const {
	
	mutexFibObjectInfoData.lock();
	typeOfInputVariables inVarType = UNKNOWN;
	for ( map< typeOfInputVariables , unsigned int >::const_iterator
			itrFoundInVar = mapInVarTypes.begin();
			itrFoundInVar != mapInVarTypes.end(); ++itrFoundInVar ) {
		if ( itrFoundInVar->second == uiNumberOfInVar ) {
			//input variable found
			inVarType = itrFoundInVar->first;
		}
	}
	mutexFibObjectInfoData.unlock();
	return inVarType;
}


/**
 * This method returns the number of the input variable (counting starts
 * with 1), of the Fib object of this Fib object info object, which is
 * of the given type.
 *
 * @see mapInVarTypes
 * @see getTypeInVar()
 * @see typeOfInputVariables
 * @param typeOfInVar the type of the input variable, of which to
 * 	return the number (counting starts with 1)
 * @return the number of the input variable, which is of the given type
 * 	or 0 if non could be found
 */
unsigned int cFibObjectInfo::getInVarForType(
		const typeOfInputVariables typeOfInVar ) const {
	
	mutexFibObjectInfoData.lock();
	map< typeOfInputVariables , unsigned int >::const_iterator
		itrFoundType = mapInVarTypes.find( typeOfInVar );
	const unsigned int uiNumberOfInputVariable =
		( itrFoundType == mapInVarTypes.end() ) ? 0 : itrFoundType->second;
	mutexFibObjectInfoData.unlock();
	return uiNumberOfInputVariable;
}


/**
 * This method adds the type for the uiNumberOfInVar'th input variable
 * (counting starts with 1), of the Fib object of this Fib object info object.
 * If a input variable with the same type exists allready, it will be
 * replaced.
 *
 * @see mapInVarTypes
 * @see getTypeInVar()
 * @see getInVarForType()
 * @see typeOfInputVariables
 * @param uiNumberOfInVar the number of the input variable, to which to
 * 	add the type (counting starts with 1)
 * @param typeOfInVar the type of the uiNumberOfInVar'th input variable
 */
void cFibObjectInfo::addTypeInVar( const unsigned int uiNumberOfInVar,
		const typeOfInputVariables typeOfInVar ) {
	
	if ( typeOfInVar == UNKNOWN ) {
		//not a valid input variable type -> skip
		return;
	}
	mutexFibObjectInfoData.lock();
	mapInVarTypes[ typeOfInVar ] = uiNumberOfInVar;
	mutexFibObjectInfoData.unlock();
}


/**
 * This method removes the type for a input variable, of the Fib object
 * of this Fib object info object.
 * No input variable with the given type will exists, after you called
 * this method.
 *
 * @see mapInVarTypes
 * @see addTypeInVar()
 * @see getTypeInVar()
 * @see getInVarForType()
 * @see typeOfInputVariables
 * @param typeOfInVar the type of the input variable to remove
 */
void cFibObjectInfo::removeTypeInVar( const typeOfInputVariables typeOfInVar ) {
	
	mutexFibObjectInfoData.lock();
	mapInVarTypes.erase( typeOfInVar );
	mutexFibObjectInfoData.unlock();
}


/**
 * This method returns if the given input variable type is for input
 * variables, which determines the size of a Fib object.
 *
 * @see mapInVarTypes
 * @see typeOfInputVariables
 * @see getSizeInVarTypes()
 * @return true if the given input variable type is for input
 * 	variables, which determines the size of a Fib object
 */
bool cFibObjectInfo::isSizeInVarTypes( const typeOfInputVariables typeOfInVar ) {
	
	return ( typeOfInVar == SIZE ) ||
		( typeOfInVar == SIZE_DIM_1 ) ||
		( typeOfInVar == SIZE_DIM_2 ) ||
		( typeOfInVar == SIZE_RADIUS ) ||
		( typeOfInVar == SIZE_RADIUS_DIM_1 ) ||
		( typeOfInVar == SIZE_RADIUS_DIM_2 );
}


/**
 * This method returns all size typs for input variables of this object.
 *
 * @see mapInVarTypes
 * @see typeOfInputVariables
 * @see addTypeInVar()
 * @see removeTypeInVar()
 * @see getTypeInVar()
 * @see getInVarForType()
 * @return all size typs for input variables of this object
 */
set< cFibObjectInfo::typeOfInputVariables > cFibObjectInfo::getSizeInVarTyps() const {
	
	set< typeOfInputVariables > setSizeInVarTyps;
	for ( map< typeOfInputVariables , unsigned int >::const_iterator
			itrInVarTyp = mapInVarTypes.begin();
			itrInVarTyp != mapInVarTypes.end(); ++itrInVarTyp ) {
		
		if ( isSizeInVarTypes( itrInVarTyp->first ) ) {
			//input variable type is for size -> add it
			setSizeInVarTyps.insert( itrInVarTyp->first );
		}
	}
	return setSizeInVarTyps;
}


/**
 * This method returns all input variables which determine the size of this
 * Fib object.
 *
 * @see mapInVarTypes
 * @see typeOfInputVariables
 * @see getSizeInVarTyps()
 * @see addTypeInVar()
 * @see removeTypeInVar()
 * @see getTypeInVar()
 * @see getInVarForType()
 * @return all size typs for input variables of this object
 */
set< unsigned int > cFibObjectInfo::getSizeInVar() const {
	
	set< unsigned int > setSizeInVar;
	for ( map< typeOfInputVariables , unsigned int >::const_iterator
			itrInVarTyp = mapInVarTypes.begin();
			itrInVarTyp != mapInVarTypes.end(); ++itrInVarTyp ) {
		
		if ( isSizeInVarTypes( itrInVarTyp->first ) ) {
			//input variable type is for size -> add it
			setSizeInVar.insert( itrInVarTyp->second );
		}
	}
	return setSizeInVar;
}


/**
 * This function will analyse the given text and try to evalue an
 * input variable type for it.
 * For example the text:
 * 	"position of the start point in dimension 2 (y_s)"
 * would be interpreted as the POS_DIM_2 input variable type.
 *
 * There exists a test exectebel, where the regular expressions are tested
 * and where new regular expressions can be tested first:
 * @see ../test/tInVarTypeFromTextRegex.cpp
 *
 * @see typeOfInputVariables
 * @see mapInVarTypes
 * @see getTypeInVar()
 * @see getInVarForType()
 * @see addTypeInVar()
 * @param szText a text which shold describe/contain a input variable type
 * @return the found input variable type for the given text or
 * 	UNKNOWN if non could be found
 */
cFibObjectInfo::typeOfInputVariables cFibObjectInfo::getInVarTypeFromText(
		const string & szText ) {
	
#ifdef FEATURE_FIB_OBJECT_INFO_IN_VAR_TYPE_FROM_TEXT_REGEX
	/*a list with the patterns for the input variable types
		 first: the pattern
		 second: the input variable type for the pattern*/
	list< pair< regex, typeOfInputVariables > > liPatternsForInVarTypes;
	
	//search for key words:
	const string patPosition = "(((((position)|(location))|((locale)|(locality)))|(((place)|(site))|((spot)|(point))))|(pixle))";
	const string patDimension = "(((dimension)|(dim))|(direction))";
	const string parOne = "(((1)|(one))|((1\\.)|(first)))";
	const string parTwo = "(((2)|(two))|((2\\.)|(second)))";
	const string parThree = "(((3)|(three))|((3\\.)|(third)))";
	const string parFour = "(((4)|(four))|((4\\.)|(fourth)))";
	
	const string patStart = "(((1\\.)|(start))|((first)|"+ parOne +"))";
	
	const string patDim1 = "(((" + patDimension + " +" + parOne + ")|(" +
		parOne + " +" + patDimension + "))|(x))";
	const string patDim2 = "(((" + patDimension + " +" + parTwo + ")|(" +
		parTwo + " +" + patDimension + "))|(y))";
	
	const string patWidth = "((((width)|(breadth))|((compass)|(diameter)))|(((measure)|(span))|((thickness)|(wideness))))";
	
	const string patLine = "(((((line)|(lines))|((border)|(borderline)))|(((boundary)|(bound))|((edge)|( fringe))))|(((rank)|(rim))|(verge)))";
	
	const string patStartPosition = "((" + patStart + " +" + patPosition + ")|(" +
		patPosition + " +" + patStart +"))";
	
	const string patEndPosition = "(((((end)|(ending))|(last)) +" + patPosition + ")|(" +
		patPosition + " +(((end)|(ending))|(last))))";
	
	
	//e.g. "position start point dimension 1 (x_1)"
	liPatternsForInVarTypes.push_back( pair< regex, typeOfInputVariables >(
		regex( ".*" + patPosition + " .*" + patStartPosition +" .*" + patDim1 +".*",
			regex_constants::icase | regex_constants::ECMAScript ) , POS_DIM_1 ) );
	liPatternsForInVarTypes.push_back( pair< regex, typeOfInputVariables >(
		regex( ".*" + patPosition + " .*" + patStartPosition +" .*" + patDim2 +".*",
			regex_constants::icase | regex_constants::ECMAScript ) , POS_DIM_2 ) );
	liPatternsForInVarTypes.push_back( pair< regex, typeOfInputVariables >(
		regex( ".*" + patPosition + " .*" + patEndPosition +" .*" + patDim1 +".*",
			regex_constants::icase | regex_constants::ECMAScript ) , POS_END_DIM_1 ) );
	liPatternsForInVarTypes.push_back( pair< regex, typeOfInputVariables >(
		regex( ".*" + patPosition + " .*" + patEndPosition +" .*" + patDim2 +".*",
			regex_constants::icase | regex_constants::ECMAScript ) , POS_END_DIM_2 ) );
	liPatternsForInVarTypes.push_back( pair< regex, typeOfInputVariables >(
		regex( ".*((" + patWidth + " .*" + patLine +")|("
		+ patLine + " .*" + patWidth +")).*",
			regex_constants::icase | regex_constants::ECMAScript ) , LINE_WIDTH ) );
	liPatternsForInVarTypes.push_back( pair< regex, typeOfInputVariables >(
		regex( ".*" + patPosition + " .*((" + parThree + " +" + patPosition + ")|(" +
		patPosition + " +" + parThree +")) .*" + patDim1 +".*",
			regex_constants::icase | regex_constants::ECMAScript ) , POS_POINT_3_DIM_1 ) );
	liPatternsForInVarTypes.push_back( pair< regex, typeOfInputVariables >(
		regex( ".*" + patPosition + " .*((" + parThree + " +" + patPosition + ")|(" +
		patPosition + " +" + parThree +")) .*" + patDim2 +".*",
			regex_constants::icase | regex_constants::ECMAScript ) , POS_POINT_3_DIM_2 ) );
	liPatternsForInVarTypes.push_back( pair< regex, typeOfInputVariables >(
		regex( ".*" + patPosition + " .*((" + parFour + " +" + patPosition + ")|(" +
		patPosition + " +" + parFour +")) .*" + patDim1 +".*",
			regex_constants::icase | regex_constants::ECMAScript ) , POS_POINT_4_DIM_1 ) );
	liPatternsForInVarTypes.push_back( pair< regex, typeOfInputVariables >(
		regex( ".*" + patPosition + " .*((" + parFour + " +" + patPosition + ")|(" +
		patPosition + " +" + parFour +")) .*" + patDim2 +".*",
			regex_constants::icase | regex_constants::ECMAScript ) , POS_POINT_4_DIM_2 ) );
	
	const string patRadius = "((radius)|(diameter))";
	liPatternsForInVarTypes.push_back( pair< regex, typeOfInputVariables >(
		regex( ".*((" + patRadius + ".* " + patDim1 +")|(" +
		patDim1 + ".* " + patRadius +")).*",
			regex_constants::icase | regex_constants::ECMAScript ) , SIZE_RADIUS_DIM_1 ) );
	liPatternsForInVarTypes.push_back( pair< regex, typeOfInputVariables >(
		regex( ".*((" + patRadius + ".* " + patDim2 +")|(" +
		patDim2 + ".* " + patRadius +")).*",
			regex_constants::icase | regex_constants::ECMAScript ) , SIZE_RADIUS_DIM_2 ) );
	//check specific pattern before general pattern
	liPatternsForInVarTypes.push_back( pair< regex, typeOfInputVariables >(
		regex( ".*" + patRadius + ".*",
			regex_constants::icase | regex_constants::ECMAScript ) , SIZE_RADIUS ) );
	
	liPatternsForInVarTypes.push_back( pair< regex, typeOfInputVariables >(
		regex( ".*((angle)|(chevron)).*",
			regex_constants::icase | regex_constants::ECMAScript ) , ANGLE ) );
	
	const string patSize = "((((size)|(distance))|((extent)|(bigness)))|(((length)|(span))|((stretch)|(width))))";
	liPatternsForInVarTypes.push_back( pair< regex, typeOfInputVariables >(
		regex( ".*((" + patSize + ".* " + patDim1 +")|(" + patDim1 + ".* " + patSize +")).*",
			regex_constants::icase | regex_constants::ECMAScript ) , SIZE_DIM_1 ) );
	liPatternsForInVarTypes.push_back( pair< regex, typeOfInputVariables >(
		regex( ".*((" + patSize + ".* " + patDim2 +")|(" + patDim2 + ".* " + patSize +")).*",
			regex_constants::icase | regex_constants::ECMAScript ) , SIZE_DIM_2 ) );
	//check specific pattern before general pattern
	liPatternsForInVarTypes.push_back( pair< regex, typeOfInputVariables >(
		regex( ".*" + patSize + ".*",
			regex_constants::icase | regex_constants::ECMAScript ) , SIZE ) );
	
	liPatternsForInVarTypes.push_back( pair< regex, typeOfInputVariables >(
		regex( ".*" + patPosition + " .*" + patPosition +"s .*" + patDim1 +".*",
			regex_constants::icase | regex_constants::ECMAScript ) , POS_POINT_ALL_DIM_1 ) );
	liPatternsForInVarTypes.push_back( pair< regex, typeOfInputVariables >(
		regex( ".*" + patPosition + " .*" + patPosition +"s .*" + patDim2 +".*",
			regex_constants::icase | regex_constants::ECMAScript ) , POS_POINT_ALL_DIM_2 ) );
	
	const string parMiddle = "(((middle)|(center))|((mid)|(midpoint)))";
	liPatternsForInVarTypes.push_back( pair< regex, typeOfInputVariables >(
		regex( ".*" + parMiddle + " .*" + patDim1 +".*",
			regex_constants::icase | regex_constants::ECMAScript ) , POS_POINT_MIDDLE_DIM_1 ) );
	liPatternsForInVarTypes.push_back( pair< regex, typeOfInputVariables >(
		regex( ".*" + parMiddle + " .*" + patDim2 +".*",
			regex_constants::icase | regex_constants::ECMAScript ) , POS_POINT_MIDDLE_DIM_2 ) );
	
	
	
	for ( typename list< pair< regex, typeOfInputVariables > >::const_iterator
			itrPattern = liPatternsForInVarTypes.begin();
			itrPattern != liPatternsForInVarTypes.end(); ++itrPattern ) {
		
		if ( regex_match( szText, itrPattern->first ) ){
			/*the pattern matches the string
			 *-> return the input variable type for the pattern*/
			return itrPattern->second;
		}//else check next pattern
	}//end for all pattern
	
	
	
	/*TODO
	 -?how to implement? if no size is given but POS_DIM_n and POS_END_DIM_n -> size POS_END_DIM_n - POS_DIM_n
	 */
	
	
#endif //FEATURE_FIB_OBJECT_INFO_IN_VAR_TYPE_FROM_TEXT_REGEX
	return UNKNOWN;
}


//TODO

/**
 * This function will add missing Fib input variables types to the given
 * map of input variable types
 * For exampe the POS_END_DIM_1 input variable type, will be set to the
 * last not used POS_POINT_p_DIM_1 (if existing) .
 *
 * @see getInVarTypeFromText()
 * @see typeOfInputVariables
 * @see mapInVarTypes
 * @see getTypeInVar()
 * @see getInVarForType()
 * @see addTypeInVar()
 * @param inOutMapInVarTypes the map with the input variable types, for
 * 	which to add missing types that can be infered from the existing
 * 	input variable types
 */
void cFibObjectInfo::fillInMissingTypesOfInputVariables(
		map< typeOfInputVariables , unsigned int > & inOutMapInVarTypes ) {
	
	/*function fillInMissingTypesOfInputVariables
		* the first free inVar POS_* type will be set to the middle point
		 inVar (of same dimension)
		* for POS_END_DIM_n inVars set last not used POS_POINT_p_DIM_n (if existing)
		* set last used POS_POINT_p_DIM_n (if existing) to POS_END_DIM_n
		* remember inVar for position of all points in one dimension and
		 add later all free other sides for dimension as type for inVar
		 ( inVar v for dim 1: other inVars for POS_DIM_2, POS_POINT_2_DIM_1,
		 POS_POINT_3_DIM_1, POS_POINT_3_DIM_2 and POS_END_DIM_2
		 -> add type for inVar v: POS_DIM_1 and POS_END_DIM_1)
	 */
	const static int uiNumberOfPosNTypes = 4;
	const static typeOfInputVariables arOfPosNTypesDim1[ uiNumberOfPosNTypes ] =
		{ POS_DIM_1, POS_POINT_2_DIM_1, POS_POINT_3_DIM_1, POS_POINT_4_DIM_1 };
	const static typeOfInputVariables arOfPosNTypesDim2[ uiNumberOfPosNTypes ] =
		{ POS_DIM_2, POS_POINT_2_DIM_2, POS_POINT_3_DIM_2, POS_POINT_4_DIM_2 };
	
	//the first free inVar POS_* type will be set to the middle point inVar (of same dimension)
	if ( inOutMapInVarTypes.find( POS_POINT_MIDDLE_DIM_1 ) != inOutMapInVarTypes.end() ) {
		//a middle point for dimension 1 exists
		for ( int index = 0; index < uiNumberOfPosNTypes; ++index ) {
			if ( inOutMapInVarTypes.find( arOfPosNTypesDim1[ index ] ) == inOutMapInVarTypes.end() ) {
				//no input variable for the input variable POS_*_DIM_1 type
				//arOfPosNTypesDim1[ index ] exists -> set type for middle point inVar
				inOutMapInVarTypes[ arOfPosNTypesDim1[ index ] ] =
					inOutMapInVarTypes[ POS_POINT_MIDDLE_DIM_1 ];
				break;  //done
			}
		}
	}  //end if POS_POINT_MIDDLE_DIM_1
	if ( inOutMapInVarTypes.find( POS_POINT_MIDDLE_DIM_2 ) != inOutMapInVarTypes.end() ) {
		//a middle point for dimension 2 exists
		for ( int index = 0; index < uiNumberOfPosNTypes; ++index ) {
			if ( inOutMapInVarTypes.find( arOfPosNTypesDim2[ index ] ) == inOutMapInVarTypes.end() ) {
				//no input variable for the input variable POS_*_DIM_2 type
				//arOfPosNTypesDim1[ index ] exists -> set type for middle point inVar
				inOutMapInVarTypes[ arOfPosNTypesDim2[ index ] ] =
					inOutMapInVarTypes[ POS_POINT_MIDDLE_DIM_2 ];
				break;  //done
			}
		}
	}  //end if POS_POINT_MIDDLE_DIM_2
	
	//connect end point and last point (POS_POINT_p_DIM_d with p is max)
	if ( inOutMapInVarTypes.find( POS_END_DIM_1 ) != inOutMapInVarTypes.end() ) {
		//end point for dimension 1 exists
		//for POS_END_DIM_1 inVars set last not used POS_POINT_p_DIM_1 (if existing)
		
		//set last used POS_POINT_p_DIM_n (if existing) to POS_END_DIM_n
		for ( int index = uiNumberOfPosNTypes - 1; 0 <= index ; --index ) {
			if ( inOutMapInVarTypes.find( arOfPosNTypesDim1[ index ] ) != inOutMapInVarTypes.end() ) {
				//input variable for the input variable POS_*_DIM_1 type
				//arOfPosNTypesDim1[ index ] exists -> try to get next point
				if ( ( 0 < index ) &&  //not first point
						( index < uiNumberOfPosNTypes  ) && //not last existing position type
						( inOutMapInVarTypes[ POS_END_DIM_1 ] !=
							inOutMapInVarTypes[ arOfPosNTypesDim1[ index ] ] ) ) {
					//not the same input variable for both position types
					++index;  //get next point position type
					inOutMapInVarTypes[ arOfPosNTypesDim1[ index ] ] =
						inOutMapInVarTypes[ POS_END_DIM_1 ];
				}
				break;  //done
			}
		}
	} else { //no end point for dimension 1 exists
		//set last used POS_POINT_p_DIM_1 (if existing) to POS_END_DIM_1
		for ( int index = uiNumberOfPosNTypes - 1; 0 <= index ; --index ) {
			if ( inOutMapInVarTypes.find( arOfPosNTypesDim1[ index ] ) != inOutMapInVarTypes.end() ) {
				//input variable for the input variable POS_*_DIM_1 type
				//arOfPosNTypesDim1[ index ] exists -> set type for end point inVar
				inOutMapInVarTypes[ POS_END_DIM_1 ] =
					inOutMapInVarTypes[ arOfPosNTypesDim1[ index ] ];
				break;  //done
			}
		}
	}  //end if POS_END_DIM_1
	
	if ( inOutMapInVarTypes.find( POS_END_DIM_2 ) != inOutMapInVarTypes.end() ) {
		//end point for dimension 2 exists
		//for POS_END_DIM_n inVars set last not used POS_POINT_p_DIM_2 (if existing)
		
		//set last used POS_POINT_p_DIM_2 (if existing) to POS_END_DIM_2
		for ( int index = uiNumberOfPosNTypes - 1; 0 <= index ; --index ) {
			if ( inOutMapInVarTypes.find( arOfPosNTypesDim2[ index ] ) != inOutMapInVarTypes.end() ) {
				//input variable for the input variable POS_*_DIM_2 type
				//arOfPosNTypesDim2[ index ] exists -> try to get next point
				if ( ( 0 < index ) &&  //not first point
						( index < uiNumberOfPosNTypes  ) && //not last existing position type
						( inOutMapInVarTypes[ POS_END_DIM_2 ] !=
							inOutMapInVarTypes[ arOfPosNTypesDim2[ index ] ] ) ) {
					//not the same input variable for both position types
					++index;  //get next point position type
					inOutMapInVarTypes[ arOfPosNTypesDim2[ index ] ] =
						inOutMapInVarTypes[ POS_END_DIM_2 ];
				}
				break;  //done
			}
		}
	} else {  //no end point for dimension 2 exists
		//set last used POS_POINT_p_DIM_2 (if existing) to POS_END_DIM_2
		for ( int index = uiNumberOfPosNTypes - 1; 0 <= index ; --index ) {
			if ( inOutMapInVarTypes.find( arOfPosNTypesDim2[ index ] ) != inOutMapInVarTypes.end() ) {
				//input variable for the input variable POS_*_DIM_2 type
				//arOfPosNTypesDim2[ index ] exists -> set type for end point inVar
				inOutMapInVarTypes[ POS_END_DIM_2 ] =
					inOutMapInVarTypes[ arOfPosNTypesDim2[ index ] ];
				break;  //done
			}
		}
	}  //end if POS_END_DIM_1
	
	
	/* set inVar for position of all points in one dimension to
	 all free other sides for dimension as type for inVar
	 (e.g. inVar v for dim 1: other inVars for POS_DIM_2, POS_POINT_2_DIM_1,
	 POS_POINT_3_DIM_1, POS_POINT_3_DIM_2 and POS_END_DIM_2
	 -> add type for inVar v: POS_DIM_1 and POS_END_DIM_1) */
	if ( inOutMapInVarTypes.find( POS_POINT_ALL_DIM_1 ) != inOutMapInVarTypes.end() ) {
		//the POS_POINT_ALL_DIM_1 inVar type exists
		for ( int index = 0; index < uiNumberOfPosNTypes; ++index ) {
			if ( ( inOutMapInVarTypes.find( arOfPosNTypesDim1[ index ] ) ==
						inOutMapInVarTypes.end() ) &&
					( inOutMapInVarTypes.find( arOfPosNTypesDim2[ index ] ) !=
						inOutMapInVarTypes.end() ) ) {
				//no input variable for the input variable POS_n_DIM_1 type
				//but one for the POS_n_DIM_2 type exists
				//-> set type for POS_n_DIM_1 point inVar to
				// POS_POINT_ALL_DIM_1 inVar
				inOutMapInVarTypes[ arOfPosNTypesDim1[ index ] ] =
					inOutMapInVarTypes[ POS_POINT_ALL_DIM_1 ];
			}
		}
	}
	if ( inOutMapInVarTypes.find( POS_POINT_ALL_DIM_2 ) != inOutMapInVarTypes.end() ) {
		//the POS_POINT_ALL_DIM_2 inVar type exists
		for ( int index = 0; index < uiNumberOfPosNTypes; ++index ) {
			if ( ( inOutMapInVarTypes.find( arOfPosNTypesDim2[ index ] ) ==
						inOutMapInVarTypes.end() ) &&
					( inOutMapInVarTypes.find( arOfPosNTypesDim1[ index ] ) !=
						inOutMapInVarTypes.end() ) ) {
				//no input variable for the input variable POS_n_DIM_2 type
				//but one for the POS_n_DIM_1 type exists
				//-> set type for POS_n_DIM_2 point inVar to
				// POS_POINT_ALL_DIM_2 inVar
				inOutMapInVarTypes[ arOfPosNTypesDim2[ index ] ] =
					inOutMapInVarTypes[ POS_POINT_ALL_DIM_2 ];
			}
		}
	}
	
}



/**
 * This function returns the name for the given input variable type.
 *
 * @see getInVarTypeForName()
 * @see typeOfInputVariables
 * @see mapInVarTypes
 * @see getTypeInVar()
 * @see getInVarForType()
 * @param typeOfInVar the type of the input variable, for which to
 * 	return the name
 * @return the name for the given input variable type
 */
string cFibObjectInfo::getNameForInVarType( const typeOfInputVariables typeOfInVar ) {
	
	switch ( typeOfInVar ) {
		case UNKNOWN : return "type unknown";
			//the position in the first dimension
		case POS_DIM_1 : return "position dimension 1";
			//the position in the first dimension
		case POS_DIM_2 : return "position dimension 2";
			//the position in the second dimension
		case SIZE      : return "size";  //the size of the Fib object
		case SIZE_DIM_1 : return "size dimension 1";
			//the size of the Fib object in the first dimension
		case SIZE_DIM_2 : return "size dimension 2";
			//the size of the Fib object in the second dimension
		case SIZE_RADIUS : return "radius";//the radius of the Fib object
		case SIZE_RADIUS_DIM_1 : return "radius dimension 1";
			//the radius of the Fib object in the first dimension
		case SIZE_RADIUS_DIM_2 : return "radius dimension 2";
			//the radius of the Fib object in the second dimension
		case LINE_WIDTH : return "line width";
			//width of the line, with which the object was drawn
		
		case ANGLE : return "angle";//the angle of the Fib object
		case POS_END_DIM_1 : return "end position dimension 1";
			//the end position in the first dimension
		case POS_END_DIM_2 : return "end position dimension 2";
			//the end position in the second dimension
		
		case POS_POINT_2_DIM_1 : return "2. point dimension 1";
			//the position of the second point in the first dimension
		case POS_POINT_2_DIM_2 : return "2. point dimension 2";
			//the position of the second point in the second dimension
		
		case POS_POINT_3_DIM_1 : return "3. point dimension 1";
			//the position of the third point in the first dimension
		case POS_POINT_3_DIM_2 : return "3. point dimension 2";
			//the position of the third point in the second dimension
		
		case POS_POINT_4_DIM_1 : return "4. point dimension 1";
			//the position of the 4. point in the first dimension
		case POS_POINT_4_DIM_2 : return "4. point dimension 2";
			//the position of the 4. point in the second dimension
		
		case POS_POINT_ALL_DIM_1 : return "all points dimension 1";
			//the position of the all points in the first dimension
		case POS_POINT_ALL_DIM_2 : return "all points dimension 2";
			//the position of the all points in the second dimension
		case POS_POINT_MIDDLE_DIM_1 : return "middle point dimension 1";
			//the position of the middle point in the first dimension
		case POS_POINT_MIDDLE_DIM_2 : return "middle point dimension 2";
			//the position of the middle point in the second dimension
		
		
	};//else UNKNOWN
	//int to string
	const int iTypeOfInVar = ((int)(typeOfInVar));
	char szNumberBuffer[ 16 ];
	sprintf( szNumberBuffer, "%d", iTypeOfInVar);
	return string( szNumberBuffer );
}


/**
 * This function returns the input variable type for the given input
 * variable type name.
 *
 * @see getNameForInVarType()
 * @see typeOfInputVariables
 * @see mapInVarTypes
 * @see getTypeInVar()
 * @see getInVarForType()
 * @param typeOfInVar the type of the input variable, for which to
 * 	return the name
 * @return the input variable type for the given input variable type
 * 	name (or UNKNOWN if non exists)
 */
cFibObjectInfo::typeOfInputVariables cFibObjectInfo::getInVarTypeForName(
		const string szNameInVar ) {
	
	if ( szNameInVar == "position dimension 1" ) {
		return POS_DIM_1;  //the position in the first dimension
	} else if ( szNameInVar == "position dimension 2" ) {
		return POS_DIM_2;  //the position in the second dimension
	} else if ( szNameInVar == "size" ) {
		return SIZE;  //the size of the Fib object
	} else if ( szNameInVar == "size dimension 1" ) {
		return SIZE_DIM_1;  //the size of the Fib object in the first dimension
	} else if ( szNameInVar == "size dimension 2" ) {
		return SIZE_DIM_2;  //the size of the Fib object in the second dimension
	} else if ( szNameInVar == "radius" ) {
		return SIZE_RADIUS;  //the radius of the Fib object
	} else if ( szNameInVar == "radius dimension 1" ) {
		return SIZE_RADIUS_DIM_1;  //the radius of the Fib object in the first dimension
	} else if ( szNameInVar == "radius dimension 2" ) {
		return SIZE_RADIUS_DIM_2;  //the radius of the Fib object in the second dimension
	} else if ( szNameInVar == "line width" ) {
		return LINE_WIDTH;  //width of the line, with which the object was drawn
	
	} else  if ( szNameInVar == "angle" ) {
		return ANGLE;  //the angle of the Fib object
	} else if ( szNameInVar == "end position dimension 1" ) {
		return POS_END_DIM_1;  //the end position in the first dimension
	} else if ( szNameInVar == "end position dimension 2" ) {
		return POS_END_DIM_2;  //the end position in the second dimension
		
	} else if ( szNameInVar == "2. point dimension 1" ) {
		return POS_POINT_2_DIM_1;  //the position of the second point in the first dimension
	} else if ( szNameInVar == "2. point dimension 2" ) {
		return POS_POINT_2_DIM_2;  //the position of the second point in the second dimension
		
	} else if ( szNameInVar == "3. point dimension 1" ) {
		return POS_POINT_3_DIM_1;  //the position of the third point in the first dimension
	} else if ( szNameInVar == "3. point dimension 2" ) {
		return POS_POINT_3_DIM_2;  //the position of the third point in the second dimension
		
	} else if ( szNameInVar == "4. point dimension 1" ) {
		return POS_POINT_4_DIM_1;  //the position of the 4. point in the first dimension
	} else if ( szNameInVar == "4. point dimension 2" ) {
		return POS_POINT_4_DIM_2;  //the position of the 4. point in the second dimension
		
	} else if ( szNameInVar == "all points dimension 1" ) {
		return POS_POINT_ALL_DIM_1;  //the position of the all points in the first dimension
	} else if ( szNameInVar == "all points dimension 2" ) {
		return POS_POINT_ALL_DIM_2;  //the position of the all points in the second dimension
	} else if ( szNameInVar == "middle point dimension 1" ) {
		return POS_POINT_MIDDLE_DIM_1;  //the position of the middle point in the first dimension
	} else if ( szNameInVar == "middle point dimension 2" ) {
		return POS_POINT_MIDDLE_DIM_2;  //the position of the middle point in the second dimension
		
		
	} else if ( szNameInVar ==  "type unknown" ) {
		return UNKNOWN;  //type unknown
	}
	//string to int (if no string for the input variable could be provieded)
	return typeOfInputVariables( atoi( szNameInVar.c_str() ) );
}


/**
 * This method will store this Fib object info object from the given
 * stream.
 *
 * @see restoreFibObjectInfo()
 * @param stream the output stream to which to store the Fib object info
 * @return true if this Fib object info object could be stored, else false
 */
bool cFibObjectInfo::store( ostream & stream ) {
	//store header
	mutexFibObjectInfoData.lock();
	
	if ( ( &stream == NULL ) || ( ! stream.good() ) ) {
		//no good stream -> return false
		return false;
	}
	
	stream<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<endl;
	stream<<"<fib_object_info identifier=\""<<getIdentifier()<<
		"\" name=\""<<szNameOfFibObject<<
		"\" countFibElements=\""<<ulNumberOfFibElements<<
		"\" countInVariables=\""<<ulNumberOfInputVariables<<
		"\" countExtSubobjects=\""<<ulNumberOfExtSubobjects<<"\">"<<endl;
	
	if ( ! szDescription.empty() ) {
		//store description
		stream<<"<description>"<<szDescription<<"</description>"<<endl;
	}
	bool bStoreOk = true;
	mutexFibObjectSource.lock();
	if ( pFibObjectSource != NULL ) {
		//store the Fib object source object
		bStoreOk &= pFibObjectSource->store( stream );
	}
	mutexFibObjectSource.unlock();
	stream<<"<categories>"<<endl;
	for ( set< string >::const_iterator itrCategory = setInCategories.begin();
			itrCategory != setInCategories.end(); ++itrCategory ) {
		
		stream<<"<category name=\""<<(*itrCategory)<<"\"/>"<<endl;
	}
	stream<<"</categories>"<<endl;
	if ( ! mapConnectedTo.empty() ) {
		stream<<"<connected_to>"<<endl;
		//store the existing connections
		for ( map< string, set< unsigned long > >::const_iterator
				itrConnection = mapConnectedTo.begin();
				itrConnection != mapConnectedTo.end(); ++itrConnection ) {
			
			stream<<"	<connection name=\""<<itrConnection->first<<"\">"<<endl;
			//store the identifiers
			const set< unsigned long > & setConnectionIds =
				itrConnection->second;
			for ( set< unsigned long >::const_iterator
					itrIdentifier = setConnectionIds.begin();
					itrIdentifier != setConnectionIds.end(); ++itrIdentifier ) {
				
				stream<<"		<identifier>"<<(*itrIdentifier)<<"</identifier>"<<endl;
			}
			stream<<"	</connection>"<<endl;
		}
		
		stream<<"</connected_to>"<<endl;
	}
	//store last uses
	stream<<"<last_used>"<<endl;
	for ( vector< pair< time_t, unsigned long > >::const_iterator
			itrTimestamp = vecLastUsed.begin();
			itrTimestamp != vecLastUsed.end(); ++itrTimestamp ) {
		
		stream<<"<used_till timestamp=\""<<itrTimestamp->first<<
			"\" count_uses=\""<<itrTimestamp->second<<"\"/>"<<endl;
	}
	stream<<"</last_used>"<<endl;
	//store users who can change the Fib object
	stream<<"<changeable_by>"<<endl;
	for ( set< string >::const_iterator itrUser = changeableBy.begin();
			itrUser != changeableBy.end(); itrUser++ ) {
		
		stream<<"<user name=\""<<(*itrUser)<<"\"/>"<<endl;
	}
	stream<<"</changeable_by>"<<endl;
	
	if ( pPreviewFibObject != NULL ) {
		//store the information for the preview picture
		//TODO? use handler
		stream<<"<preview>"<<endl;
		pPreviewFibObject->store( stream );
		
		stream<<"</preview>"<<endl;
	}
	
	if ( ! mapInVarTypes.empty() ) {
		stream<<"<in_var_types>"<<endl;
		//store the input variable types
		for ( map< typeOfInputVariables , unsigned int >::const_iterator
				itrInVarTyp = mapInVarTypes.begin();
				itrInVarTyp != mapInVarTypes.end(); ++itrInVarTyp ) {
			
			stream<<"	<input_variable number=\""<<itrInVarTyp->second<<"\" "<<
				"type=\""<<getNameForInVarType( itrInVarTyp->first )<<"\"/>"<<endl;
		}
		
		stream<<"</in_var_types>"<<endl;
	}
	stream<<"</fib_object_info>"<<endl;
	mutexFibObjectInfoData.unlock();
	
	return bStoreOk;
}


/**
 * This method will restore the Fib object info object from the given
 * stream.
 * Note: members That are not restored won't change.
 *
 * @see store()
 * @param stream the input stream from which to read the Fib object info
 * @return an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid stream
 * 		- -2 loading error, invalid data in stream
 * 		- 1 loading warning, invalid data in stream, error could be corrected
 * 		- 2 loading warning, invalid data in stream, maybe the loaded
 * 			object is wrong
 */
int cFibObjectInfo::restoreFibObjectInfo( istream & stream ) {
	
	TiXmlDocument xmlDocFibObject;
	
	stream >> xmlDocFibObject;
	
	if ( xmlDocFibObject.Error() ) {
		//error while loading to stream
		return -1;
	}
	
	return restoreFibObjectInfo( &xmlDocFibObject );
}


/**
 * This method will restore the Fib object info object from the given
 * TinyXml node.
 * Note: members That are not restored won't change.
 *
 * @see store()
 * @param pXmlNode a pointer to the TinyXml node where the Fib object
 * 	info object is stored in
 * @return an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlNode
 * 		- -2 loading error, invalid data in pXmlNode
 * 		- 1 loading warning, invalid data in pXmlNode, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlNode, maybe the loaded
 * 			object is wrong
 */
int cFibObjectInfo::restoreFibObjectInfo( const TiXmlNode * pXmlNode ) {

#ifdef DEBUG_RESTORE_XML
	//print debugging output
	printf("restoring cFibObjectInfo\n" );
#endif//DEBUG_RESTORE_XML
	if ( pXmlNode == NULL ) {
		//nothing to restore
#ifdef DEBUG_RESTORE_XML
		//print debugging output
		printf("nothing to restore\n" );
#endif//DEBUG_RESTORE_XML
		return -1;
	}
	
	mutexFibObjectInfoData.lock();
	const int iRestoreStatus = restoreFibObjectInfoInternal( pXmlNode );
	mutexFibObjectInfoData.unlock();
	//send event that this Fib object info object has changed
	sendFibObjectInfoChange();
	
	return iRestoreStatus;
}


/**
 * This method will restore the Fib object info object from the given
 * TinyXml node.It is a helpmethod of restoreFibObjectInfo() and
 * uses no mutex .
 * Note: Members that are not restored won't change.
 *
 * @see restoreFibObjectInfo()
 * @param pXmlNode a pointer to the TinyXml node where the Fib object
 * 	info object is stored in
 * @return an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 */
int cFibObjectInfo::restoreFibObjectInfoInternal( const TiXmlNode * pXmlNode ) {

#ifdef DEBUG_RESTORE_XML
	//print debugging output
	printf("restoring cFibObjectInfo\n" );
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
	
	if ( pPreviewFibObject ) {
		//delete old preview Fib object
		//TODO don't delete
		delete pPreviewFibObject;
		pPreviewFibObject = NULL;
	}
	//as long no Fib element was read and no error occured
	while ( ( pXmlNode != NULL ) && ( 0 <= iRestoreStatus ) ) {
		//get type of XML element
		const int iType = pXmlNode->Type();
		switch ( iType ) {
			case TiXmlNode::ELEMENT:{
				/*check if this is a valid Fib element XML element, create
				the apropirate Fib element and call its restoreXml() method*/
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
				printf( "Restoring root subelement \"%s\" (iRestoreStatus now %i)\n",
					szElementType.c_str(), iRestoreStatus );
#endif
				
				if ( szElementType == "fib_object_info" ) {
					/*if exists get "identifier", "name", "countFibElements", "countInVariables" and "countExtSubobjects" attributes*/
					//if exists get "identifier" attribute
					const char * szXmlIdentifier =
						pXmlElement->Attribute( "identifier" );
					if ( szXmlIdentifier ) {
						//"identifier" attribute exists
						mutexIdentifier.lock();
						ulIdentifier = atol( szXmlIdentifier );
						mutexIdentifier.unlock();
#ifdef DEBUG_RESTORE_XML
						//print debugging output
						printf("   identifier %lu\n", ulIdentifier );
#endif//DEBUG_RESTORE_XML
					}
					//if exists get "name" attribute
					const char * szXmlName =
						pXmlElement->Attribute( "name" );
					if ( szXmlName ) {
						//"name" attribute exists
						szNameOfFibObject = string( szXmlName );
					}
					//if exists get "countFibElements" attribute
					const char * szXmlNumberOfFibElements =
						pXmlElement->Attribute( "countFibElements" );
					if ( szXmlNumberOfFibElements ) {
						//"countFibElements" attribute exists
						ulNumberOfFibElements = atol( szXmlNumberOfFibElements );
					}
					//if exists get "countInVariables" attribute
					const char * szXmlNumberOfInputVariables =
						pXmlElement->Attribute( "countInVariables" );
					if ( szXmlNumberOfInputVariables ) {
						//"countInVariables" attribute exists
						ulNumberOfInputVariables = atol( szXmlNumberOfInputVariables );
					}
					//if exists get "countExtSubobjects" attribute
					const char * szXmlNumberOfExtSubobjects =
						pXmlElement->Attribute( "countExtSubobjects" );
					if ( szXmlNumberOfExtSubobjects ) {
						//"countExtSubobjects" attribute exists
						ulNumberOfExtSubobjects = atol( szXmlNumberOfExtSubobjects );
					}
					//restore the subelements
#ifdef DEBUG_RESTORE_XML
					//print debugging output
					printf("   restore the subelements\n" );
#endif//DEBUG_RESTORE_XML
					const int iSubStatusRestore = restoreFibObjectInfoInternal(
						pXmlElement->FirstChild() );
					
					if ( iSubStatusRestore < 0 ) {
						//Error: while restoring
						return iSubStatusRestore;
					}//else
					if ( ( 0 < iSubStatusRestore ) && ( iRestoreStatus == 0 ) ) {
						//Warning: while restoring -> remember first warning
						iRestoreStatus = iSubStatusRestore;
					}//else everything OK
				}else if ( szElementType == "description" ) {
					//read description element
					const char * pcXmlDescriptionText = pXmlElement->GetText();
					if ( pcXmlDescriptionText ) {
						//description text extists
						szDescription = string( pcXmlDescriptionText );
					}else{//no description text extists
						szDescription = string( "" );
					}
				}else if ( szElementType == "fib_object_source" ) {
					//restore (correct) Fib object source object
#ifdef DEBUG_RESTORE_XML
					//print debugging output
					printf("restore (correct) Fib object source object\n" );
#endif//DEBUG_RESTORE_XML
					int iOutStatusFibObjectSource = 0;
					cFibObjectSource * pRestoredFibObjectSource =
						cFibObjectSource::restore( pXmlElement, &iOutStatusFibObjectSource );
					
					if ( iOutStatusFibObjectSource < 0 ) {
						//Error: while restoring
						if ( pRestoredFibObjectSource ) {
							//delete created Fib object source object
							delete pRestoredFibObjectSource;
						}
						return iOutStatusFibObjectSource;
					}//else
					if ( ( 0 < iOutStatusFibObjectSource ) && ( iRestoreStatus == 0 ) ) {
						//Warning: while restoring -> remember first warning
						iRestoreStatus = iOutStatusFibObjectSource;
					}//else everything OK
					/*set the new Fib object source, like in:
					 @see setFibObjectSource( pRestoredFibObjectSource ); */
					mutexFibObjectSource.lock();
					if ( pFibObjectSource ) {
						//delete old Fib object source object
						delete pFibObjectSource;
						pFibObjectSource = NULL;
					}
					if ( pLoadedFibObject ) {
						//the source object changes -> so delete the loaded Fib object
						pLoadedFibObject->deleteObject();
						pLoadedFibObject = NULL;
					}
					pFibObjectSource = pRestoredFibObjectSource;
					mutexFibObjectSource.unlock();
					
				}else if ( szElementType == "categories" ) {
					/*read the "changeable_by" subelements; example:
			       <categories>
			          <category name="all">
			          ...
			       </categories>
					 */
#ifdef DEBUG_RESTORE_XML
					//print debugging output
					printf("read the categories element\n" );
#endif//DEBUG_RESTORE_XML
					for( const TiXmlElement *
							pActualUserElement = pXmlElement->FirstChildElement();
							pActualUserElement != NULL;
							pActualUserElement =
								pActualUserElement->NextSiblingElement() ) {
						//check the type of the sibling element
						const string szActualUsedSubElementType(
							pActualUserElement->Value() );
						if ( szActualUsedSubElementType == "category" ) {
							//if exists get "name" attribute
							const char * szXmlName =
								pActualUserElement->Attribute( "name" );
							if ( szXmlName != NULL ) {
								//"name" attribute exists -> add it
								setInCategories.insert( string( szXmlName ) );
								
							}//else OK, because "name" attribute is optional
						}else if ( iRestoreStatus == 0 ) {
							//Warning: unknown "category" subelement
							iRestoreStatus = 1;
						}
					}//end for all subelements of "category"
				}else if ( szElementType == "connected_to" ) {
					//restore connection data from Xml element
#ifdef DEBUG_RESTORE_XML
					//print debugging output
					printf("restore connected to Xml element\n" );
#endif//DEBUG_RESTORE_XML
					const int iStatusRestoreConnectedTo =
						restoreConnectedTo( pXmlElement );
					if ( iStatusRestoreConnectedTo < 0 ) {
						//Error: while restoring
						return iStatusRestoreConnectedTo;
					}//else
					if ( ( 0 < iStatusRestoreConnectedTo ) && ( iRestoreStatus == 0 ) ) {
						//Warning: while restoring -> remember first warning
						iRestoreStatus = iStatusRestoreConnectedTo;
					}//else everything OK
				}else if ( szElementType == "last_used" ) {
					//restore "last used" data
					//clear the old data
					vecLastUsed.clear();
					/*read the "used_till" subelements; example;
					<last_used>
					   <used_till timestamp="1379267017" count_uses="1"/>
					   <used_till timestamp="1379266234" count_uses="2"/>
					   <used_till timestamp="1379262148" count_uses="2"/>
					   <used_till timestamp="1378598632" count_uses="4"/>
					   ...
					</last_used>
					 */
#ifdef DEBUG_RESTORE_XML
					//print debugging output
					printf("restore connected to Xml element\n" );
#endif//DEBUG_RESTORE_XML
					for( const TiXmlElement *
							pActualUsedSubElement = pXmlElement->FirstChildElement();
							pActualUsedSubElement != NULL;
							pActualUsedSubElement =
								pActualUsedSubElement->NextSiblingElement() ) {
						//check the type of the sibling element
						const string szActualUsedSubElementType(
							pActualUsedSubElement->Value() );
						if ( szActualUsedSubElementType == "used_till" ) {
							
							//if exists get "timestamp" attribute
							const char * szXmlTimestamp =
								pActualUsedSubElement->Attribute( "timestamp" );
							//if exists get "count_uses" attribute
							const char * szXmlCountUses =
								pActualUsedSubElement->Attribute( "count_uses" );
							if ( ( szXmlTimestamp != NULL ) && ( szXmlCountUses != NULL ) ) {
								//"timestamp" and "count_uses" attribute exists
								const time_t timestamp = atol( szXmlTimestamp );
								const unsigned long ulCount = atol( szXmlCountUses );
								//push new entry with data to end of vecLastUsed
								vecLastUsed.push_back( pair< time_t, unsigned long >(
									timestamp, ulCount ) );
							}else if ( iRestoreStatus == 0 ) {
								/*Warning: "timestamp" or "count_uses" attribute missing
								 -> can't restore entry*/
								iRestoreStatus = 2;
							}
							
							
						}else if ( iRestoreStatus == 0 ) {
							//Warning: unknown "last_used" subelement
							iRestoreStatus = 1;
						}
					}//end for all subelements of "last_used"
				}else if ( szElementType == "changeable_by" ) {
					/*read the "changeable_by" subelements; example:
					<changeable_by>
					   <user name="all">
					   ...
					</changeable_by>
					 */
#ifdef DEBUG_RESTORE_XML
					//print debugging output
					printf("read the changeable_by element\n" );
#endif//DEBUG_RESTORE_XML
					for( const TiXmlElement *
							pActualUserElement = pXmlElement->FirstChildElement();
							pActualUserElement != NULL;
							pActualUserElement =
								pActualUserElement->NextSiblingElement() ) {
						//check the type of the sibling element
						const string szActualUsedSubElementType(
							pActualUserElement->Value() );
						if ( szActualUsedSubElementType == "user" ) {
							//if exists get "name" attribute
							const char * szXmlName =
								pActualUserElement->Attribute( "name" );
							if ( szXmlName != NULL ) {
								//"name" attribute exists -> add it
								changeableBy.insert( string( szXmlName ) );
								
							}//else OK, because "name" attribute is optional
						}else if ( iRestoreStatus == 0 ) {
							//Warning: unknown "changeable_by" subelement
							iRestoreStatus = 1;
						}
					}//end for all subelements of "changeable_by"
				}else if ( szElementType == "preview" ) {
					//read the "preview" subelement
#ifdef DEBUG_RESTORE_XML
					//print debugging output
					printf("read the preview subelement\n" );
#endif//DEBUG_RESTORE_XML
					for( const TiXmlElement *
							pActualUserElement = pXmlElement->FirstChildElement();
							pActualUserElement != NULL;
							pActualUserElement =
								pActualUserElement->NextSiblingElement() ) {
						
						int iOutStatusPreviewFibObject = 0;
						//TODO? use handler
						cFibObjectInfo * pLoadedPreviewFibObject =
							cFibObjectInfo::restore(
								pActualUserElement, &iOutStatusPreviewFibObject );
						
						if ( iOutStatusPreviewFibObject < 0 ) {
							//Error: while restoring
							if ( pLoadedPreviewFibObject ) {
								//delete created Fib object source object
								delete pLoadedPreviewFibObject;
							}
							return iOutStatusPreviewFibObject;
						}//else
						if ( ( 0 < iOutStatusPreviewFibObject ) && ( iRestoreStatus == 0 ) ) {
							//Warning: while restoring -> remember first warning
							iRestoreStatus = iOutStatusPreviewFibObject;
						}//else everything OK
						if ( pLoadedPreviewFibObject ) {
							//preview Fib object loaded -> don't load more of this XML element
							mutexCheckCyclicPreviewFibObjectInf.lock();
							//check that there are no cyclic dependencies
							bool bCyclicDependency = false;
							for ( cFibObjectInfo *
									pSubPreviewFibObject = pLoadedPreviewFibObject;
									pSubPreviewFibObject != NULL;
									pSubPreviewFibObject =
										pSubPreviewFibObject->getPreviewFibObjectInfo() ) {
							
								if ( pSubPreviewFibObject == this ) {
									bCyclicDependency = true;
									break;
								}
							}
							if ( ! bCyclicDependency ) {
								//set preview Fib object info
								if ( pPreviewFibObject ) {
									//Warning: preview object exists allready -> delete old
									delete pPreviewFibObject;
									iRestoreStatus = 2;
								}
								pPreviewFibObject = pLoadedPreviewFibObject;
								mutexCheckCyclicPreviewFibObjectInf.unlock();
								break;
							}else{//cyclic dependency -> don't set preview
								delete pLoadedPreviewFibObject;
								mutexCheckCyclicPreviewFibObjectInf.unlock();
							}
						}
					}//end for all "preview" subelements
				}else if ( szElementType == "in_var_types" ) {
					//restore "in_var_types" data
					//clear the old data
					mapInVarTypes.clear();
					/*read the "in_var_types" subelements; example;
			       <in_var_types>
			          <input_variable number="2" type="position dimension 1"/>
			          <input_variable number="3" type="position dimension 2"/>
			          <input_variable number="7" type="size radius"/>
			          ...
			       </in_var_types>
					 */
#ifdef DEBUG_RESTORE_XML
					//print debugging output
					printf("restore input variable types from Xml element\n" );
#endif//DEBUG_RESTORE_XML
					for( const TiXmlElement *
							pActualInVarSubElement = pXmlElement->FirstChildElement();
							pActualInVarSubElement != NULL;
							pActualInVarSubElement =
								pActualInVarSubElement->NextSiblingElement() ) {
						//check the type of the sibling element
						const string szActualInVarSubElementType(
							pActualInVarSubElement->Value() );
						if ( szActualInVarSubElementType == "input_variable" ) {
							
							//if exists get "number" attribute
							const char * szXmlInVarNumber =
								pActualInVarSubElement->Attribute( "number" );
							//if exists get "type" attribute
							const char * szXmlInVarType =
								pActualInVarSubElement->Attribute( "type" );
							if ( ( szXmlInVarNumber != NULL ) && ( szXmlInVarType != NULL ) ) {
								//"number" and "type" attribute exists
								const unsigned int uiInVarNumber =
									atol( szXmlInVarNumber );
								const typeOfInputVariables inVarType =
									getInVarTypeForName( string( szXmlInVarType ) );
								//push new entry with data to end of mapInVarTypes
								mapInVarTypes.insert( pair< typeOfInputVariables , unsigned int >(
									inVarType, uiInVarNumber ) );
							}else if ( iRestoreStatus == 0 ) {
								/*Warning: "number" or "type" attribute missing
								 -> can't restore entry*/
								iRestoreStatus = 2;
							}
							
							
						}else if ( iRestoreStatus == 0 ) {
							//Warning: unknown "last_used" subelement
							iRestoreStatus = 1;
						}
					}//end for all subelements of "in_var_types"
					
				}else{//unknown element type
					if ( iRestoreStatus == 0 ) {
						//Warning: unknown element type
						iRestoreStatus = 1;
					}
				}
				
			}break;
			case TiXmlNode::DOCUMENT:{
				//try to load the Fib object info object data from a child XML element
#ifdef DEBUG_RESTORE_XML
				//print debugging output
				printf("try to load the Fib object info object data from a child XML element\n" );
#endif//DEBUG_RESTORE_XML
				for ( const TiXmlNode * pChild = pXmlNode->FirstChild();
						pChild != NULL; pChild = pChild->NextSibling() ) {
					
					return restoreFibObjectInfoInternal( pChild );
				}
				//nothing to load
#ifdef DEBUG_RESTORE_XML
				//print debugging output
				printf( "Error: nothing to load\n" );
#endif//DEBUG_RESTORE_XML
				return -2;
			}break;
			case TiXmlNode::DECLARATION:
			case TiXmlNode::COMMENT:{
				//ignore
			}break;
			case TiXmlNode::TEXT:
			case TiXmlNode::UNKNOWN:
			default:
				//ignore; Warning: invalid Fib object
				iRestoreStatus = 2;
		}//end switch XML element type
		//if no Fib element was read check next XML eleemnt
		pXmlNode = pXmlNode->NextSibling();
	}//end as long no Fib element was read and no error occured
	
	return iRestoreStatus;
}


/**
 * This method will restore the Fib object info object from the given
 * input stream and return a pointer to it.
 * Beware: You have to care that the returned Fib object info object is
 * 	deleted.
 *
 * @see store()
 * @param stream the input stream from which to read the Fib object info
 * @param iOutStatus if not NULL an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlNode
 * 		- -2 loading error, invalid data in pXmlNode
 * 		- 1 loading warning, invalid data in pXmlNode, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlNode, maybe the loaded
 * 			object is wrong
 * @return a pointer to the restored Fib object info object or NULL if
 * 	non could be restored
 */
cFibObjectInfo * cFibObjectInfo::restore( istream & stream,
		int * iOutStatus ) {
	
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
 * This method will restore the Fib object info object from the given
 * TinyXml node and return a pointer to it.
 * Beware: You have to care that the returned Fib object info object is
 * 	deleted.
 *
 * @see store()
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
 * @return a pointer to the restored Fib object info object or NULL if
 * 	non could be restored
 */
cFibObjectInfo * cFibObjectInfo::restore(
		const TiXmlNode * pXmlNode, int * iOutStatus ) {
	
	int iInternalOutStatus = 0;
	cFibObjectInfo * pRestoreFibObjectInfo =
		new cFibObjectInfo( pXmlNode, &iInternalOutStatus );
	
	if ( iOutStatus != NULL ) {
		//transfer the output status
		(*iOutStatus) = iInternalOutStatus;
	}
	
	if ( iInternalOutStatus < 0 ) {
		//error while restoring -> return NULL
		delete pRestoreFibObjectInfo;
		return NULL;
	}
	
	return pRestoreFibObjectInfo;
}



/**
 * This method will restore the connected to part of the Fib object info
 * object from the given TinyXml node.
 *
 * @see mapConnectedTo
 * @see store()
 * @param pXmlElement a pointer to the TinyXml element where the
 * 	connected to part of the Fib object info object is stored in
 * @return an integer value with the error value
 * 	possible error values are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in pXmlElement
 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
 * 			object is wrong
 */
int cFibObjectInfo::restoreConnectedTo( const TiXmlElement * pXmlElement ) {
	
	/*read the connected_to element;
	example:
		<connected_to>
			  <connection name="isContained">
				  <identifier>6</identifier>
				  <identifier>7</identifier>
			  </connection>
			  <connection name="sameType">
				  <identifier>16</identifier>
			  </connection>
		 </connected_to>
	*/
	int iRestoreStatus = 0;
	const string szElementType( pXmlElement->Value() );
	if ( szElementType == "connected_to" ) {
		//clear the old data
		mapConnectedTo.clear();
		//read the "connection" subelements
		for( const TiXmlElement *
				pActualConnectionElement = pXmlElement->FirstChildElement();
				pActualConnectionElement != NULL;
				pActualConnectionElement =
					pActualConnectionElement->NextSiblingElement() ) {
			//check the type of the sibling element
			const string szActualConnectionElementType(
				pActualConnectionElement->Value() );
			if ( szActualConnectionElementType == "connection" ) {
				//a connection element found
				const char * szXmlName =
					pActualConnectionElement->Attribute( "name" );
				if ( szXmlName == NULL ) {
					//no name attribue -> can't create a connected to entry
					if ( iRestoreStatus == 0 ) {
						//Warning: unknown "connected_to" subelement
						iRestoreStatus = 2;
					}
					continue;
				}
				//read the "identifier" subelements
				set< unsigned long > setConnectionIdentifiers;
				for( const TiXmlElement * pActualIdentifierElement =
							pActualConnectionElement->FirstChildElement();
						pActualIdentifierElement != NULL;
						pActualIdentifierElement =
							pActualIdentifierElement->NextSiblingElement() ) {
					//check the type of the sibling element
					const string szActualIdentifierElementType(
						pActualIdentifierElement->Value() );
					if ( szActualIdentifierElementType == "identifier" ) {
						//a identifer element found
						const char * pcXmlIdentifier =
							pActualIdentifierElement->GetText();
						if ( pcXmlIdentifier ) {
							//set the read identifer
							setConnectionIdentifiers.insert( atol( pcXmlIdentifier ) );
						}else if ( iRestoreStatus == 0 ) {
							//Warning: no "identifier" given
							iRestoreStatus = 1;
						}
						
					}else if ( iRestoreStatus == 0 ) {
						//Warning: unknown "connection" subelement
						iRestoreStatus = 1;
					}
				}//end for all subelements of "connection"
				
				mapConnectedTo[ (string(szXmlName)) ].insert(
					setConnectionIdentifiers.begin(), setConnectionIdentifiers.end() );
				
			}else if ( iRestoreStatus == 0 ) {
				//Warning: unknown "connected_to" subelement
				iRestoreStatus = 1;
			}
		}//end for all subelements of "connected_to"
	}else{//wrong element
		if ( iRestoreStatus == 0 ) {
			//Warning: unknown element type
			return 1;
		}
	}//end if correct element type "connected_to"
	return iRestoreStatus;
}


/**
 * With this function you can register a listeners for changes for this
 * object.
 *
 * @see unregisterFibObjectInfoChangeListener()
 * @see setListenersFibNodeChanged
 * @see sendFibObjectInfoChange()
 * @param pFibObjectInfoListener a pointer to the listener for changes
 * @return true if the listener was registered, else false
 */
bool cFibObjectInfo::registerFibObjectInfoChangeListener(
		lFibObjectInfoChanged * pFibObjectInfoListener ) {
	
	if ( pFibObjectInfoListener == NULL ) {
		return false;
	}
	mutexFibObjectInfoData.lock();
	const pair< set< lFibObjectInfoChanged * >::iterator, bool > paListenerInserted =
		setListenersFibNodeChanged.insert( pFibObjectInfoListener );
	mutexFibObjectInfoData.unlock();
	return paListenerInserted.second;
}


/**
 * With this function you can unregister a listeners for changes in this
 * object.
 *
 * @see registerFibObjectInfoChangeListener()
 * @see setListenersFibNodeChanged
 * @see sendFibObjectInfoChange()
 * @param pFibObjectInfoListener a pointer to the listener for changes
 * @return true if the listener was registered, else false
 */
bool cFibObjectInfo::unregisterFibObjectInfoChangeListener(
		lFibObjectInfoChanged * pFibObjectInfoListener ) {
	
	mutexFibObjectInfoData.lock();
	const bool bListenerRemoved = ( 0 < setListenersFibNodeChanged.erase(
		pFibObjectInfoListener ) );
	mutexFibObjectInfoData.unlock();
	return bListenerRemoved;
}


/**
 * Event method
 * It will be called every time a Fib Fib object info object
 * (cFibObjectInfo), at which this object is registered, was changed.
 *
 * @param pFibObjectInfoChanged a pointer to the event, with the information
 * 	about the changed Fib node
 */
void cFibObjectInfo::fibObjectInfoChanged(
	const eFibObjectInfoChangedEvent * pFibObjectInfoChanged ) {
	
	if ( ( pFibObjectInfoChanged == NULL ) ||
			( pFibObjectInfoChanged->getFibObjectInfo() == NULL ) ) {
		//nothing changed
		return;
	}
	
	mutexFibObjectInfoData.lock();
	if ( ( pFibObjectInfoChanged->getFibObjectInfo() == pPreviewFibObject ) &&
			pFibObjectInfoChanged->isDeleted() ) {
		//if the preview Fib object info object was deleted -> cut connection to it
		pPreviewFibObject = NULL;
	}
	mutexFibObjectInfoData.unlock();
}


/**
 * This method sents a Fib object info object changed event to all change
 * Fib object info object listeners of this object.
 * The event will just say that this Fib object info object has canged.
 *
 * @see setListenersFibNodeChanged
 */
void cFibObjectInfo::sendFibObjectInfoChange() {
	
	const eFibObjectInfoChangedEvent fibObjectInfoChangedEvent( this );
	sendFibObjectInfoChange( &fibObjectInfoChangedEvent );
}


/**
 * This method sents a Fib object info object changed event to all change
 * Fib object info object listeners of this object.
 *
 * @see setListenersFibNodeChanged
 * @param pFibNodeChangedEvent the change event to send
 */
void cFibObjectInfo::sendFibObjectInfoChange(
		const eFibObjectInfoChangedEvent * pFibObjectInfoChanged ) {
	
	mutexFibObjectInfoData.lock();
	set< lFibObjectInfoChanged * > setListenersFibNodeChangedCopy(
		setListenersFibNodeChanged );
	mutexFibObjectInfoData.unlock();
	
	for ( set< lFibObjectInfoChanged * >::iterator
			itrChangeListener = setListenersFibNodeChangedCopy.begin();
			itrChangeListener != setListenersFibNodeChangedCopy.end();
			itrChangeListener++ ) {
		
		(*itrChangeListener)->fibObjectInfoChanged( pFibObjectInfoChanged );
	}
}




