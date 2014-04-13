
//TODO check

/**
 * @file cFibObjectInfo
 * file name: cFibObjectInfo.h
 * @author Betti Oesterholz
 * @date 13.09.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a information about a Fib object.
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
 * This file specifies a class for a information about a Fib object.
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
 * - The element "categories" contains for every category the Fib object
 *    for this Fib object info is in an (@see setInCategories) a "category" element.
 *    The "category" element has the attribute "name" which contains the
 *    name of the category for the Fib object for this Fib object info.
 *    @see setInCategories
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
 *    The "user" element has the attribute "name" which contains the name of
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
       <categories>
          <category name="all">
          ...
       </categories>
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
05.04.2014  Oesterholz  input variables types added
*/


#ifndef ___FIB__NCREATOR__C_FIB_OBJECT_INFO_H__
#define ___FIB__NCREATOR__C_FIB_OBJECT_INFO_H__


#include "version.h"
#include "versionCreator.h"

#include <string>
#include <map>
#include <set>
#include <vector>
#include <ostream>
#include <istream>

#include <QMutex>

#include "tinyxml.h"

#include "lFibObjectInfoChanged.h"


using std::string;
using std::map;
using std::set;
using std::vector;
using std::ostream;
using std::istream;
using std::pair;


namespace fib{
//forward declarations
class cFibElement;

namespace nCreator{

//forward declarations
class cFibObjectSource;


class cFibObjectInfo: public lFibObjectInfoChanged{
public:
	
	/**
	 * This type (enum) is for the types of the input variables.
	 * Note: Adapt when changing this type:
	 * 	- @see getNameForInVarType()
	 * 	- @see getInVarTypeForName()
	 * 	- @see isSizeInVarTypes()
	 * 	- @see getSizeInVarTyps()
	 *
	 * @see getTypeInVar()
	 * @see getInVarForType()
	 * @see addTypeInVar()
	 * @see removeTypeInVar()
	 * @see getNameForInVarType()
	 * @see getInVarTypeForName()
	 * @see isSizeInVarTypes()
	 * @see getSizeInVarTyps()
	 */
	enum typeOfInputVariables{
		UNKNOWN   = 0,  //type unknown
		POS_DIM_1 = 1,  //the position in the first dimension
		POS_DIM_2 = 2,  //the position in the second dimension
		SIZE      = 10, //the size of the Fib object
		SIZE_DIM_1 = 11,//the size of the Fib object in the first dimension
		SIZE_DIM_2 = 12,//the size of the Fib object in the second dimension
		SIZE_RADIUS= 20,//the radius of the Fib object
		SIZE_RADIUS_DIM_1 = 21,//the radius of the Fib object in the first dimension
		SIZE_RADIUS_DIM_2 = 22,//the radius of the Fib object in the second dimension
		ANGLE = 100//the angle of the Fib object
		/*TODO
		 POS_POINT_2_DIM_1 = 200
		 POS_POINT_2_DIM_2 = 201
		 POS_POINT_3_DIM_1 = 300
		 POS_POINT_3_DIM_2 = 301
		 POS_POINT_4_DIM_1 = 400
		 POS_POINT_4_DIM_2 = 401
		 */
		
	};//end typeOfInputVariables

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
	cFibObjectInfo( const unsigned long ulInIdentifier,
		const cFibObjectSource * pInFibObjectSource,
		const bool bExtractInfo = true );
	
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
	explicit cFibObjectInfo( istream & stream, int * iOutStatus=NULL );
	
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
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 */
	explicit cFibObjectInfo( const TiXmlNode * pXmlNode,
		int * iOutStatus=NULL );
	
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
	explicit cFibObjectInfo( const unsigned long ulInIdentifier,
		const std::string szInNameOfFibObject = "",
		const std::string szInDescription = "",
		const cFibObjectSource * pInFibObjectSource = NULL,
		const std::set< std::string > setChangeableBy = set< string >() );
	
	/**
	 * copy constructor for a Fib object info object
	 *
	 * @param fibObjectInfo the Fib object info object to copy
	 */
	cFibObjectInfo( const cFibObjectInfo & fibObjectInfo );
	
	/**
	 * copy constructor for a Fib object info object
	 * With this copy constructor the identifier can be changed for the copy.
	 *
	 * @param ulInIdentifier the identifer of this Fib object info object
	 * 	@see ulIdentifier
	 * @param fibObjectInfo the Fib object info object to copy
	 */
	cFibObjectInfo( const unsigned long ulInIdentifier,
		const cFibObjectInfo & fibObjectInfo );
	
	/**
	 * destructor
	 */
	virtual ~cFibObjectInfo();
	
	
	/**
	 * This method creates a copy of this object and returns it.
	 *
	 * @return a pointer to a copy of this object
	 */
	cFibObjectInfo * clone() const;
	
	/**
	 * This method creates a copy of this object and returns it.
	 * With this clone method the identifier can be changed for the copy.
	 *
	 * @param ulInIdentifier the identifer of the copy Fib object info object
	 * 	@see ulIdentifier
	 * @return a pointer to a copy of this object
	 */
	cFibObjectInfo * clone( const unsigned long ulInIdentifier ) const;
	
	
	/**
	 * @return the name of this class "cFibObjectInfo"
	 */
	std::string getName() const;
	
	/**
	 * @see setIdentifier()
	 * @return the identifiers of this Fib object
	 * 	@see ulIdentifier
	 */
	unsigned long getIdentifier() const;
	
	/**
	 * This method sets the identifier for this object.
	 *
	 * @see ulIdentifier
	 * @see getIdentifier()
	 * @param ulNewIdentifier the identifiers of this Fib object
	 */
	void setIdentifier( const unsigned long ulNewIdentifier );
	
	/**
	 * @see setFibObjectName()
	 * @return the name of the Fib object
	 * 	@see szNameOfFibObject
	 */
	std::string getFibObjectName() const;
	
	/**
	 * This method set the name of the Fib object to the given name.
	 *
	 * @see szNameOfFibObject
	 * @see getFibObjectName()
	 * @param szFibObjectName the name of the Fib object to set
	 */
	void setFibObjectName( const std::string & szFibObjectName );
	
	/**
	 * @see setDescription()
	 * @return the description of the Fib object
	 * 	@see szDescription
	 */
	std::string getDescription() const;
	
	/**
	 * This method set the description of the Fib object to the given description.
	 *
	 * @see szDescription
	 * @see getDescription()
	 * @param szFibObjectDescription the description of the Fib object to set
	 */
	void setDescription( const std::string & szFibObjectDescription );
	
	/**
	 * @see setFibObjectSource()
	 * @return a pointer to the Fib object source object
	 * 	@see pFibObjectSource
	 */
	cFibObjectSource * getFibObjectSource();
	
	/**
	 * @see setFibObjectSource()
	 * @return a const pointer to the Fib object source object
	 * 	@see pFibObjectSource
	 */
	const cFibObjectSource * getFibObjectSource() const;
	
	/**
	 * This method sets the Fib object source object to a copy of the given
	 * Fib object source object.
	 * Note: This method will clone the given pInFibObjectSource object.
	 *
	 * @see pFibObjectSource
	 * @see getFibObjectSource()
	 * @return a pointer to the Fib object source object to set
	 */
	bool setFibObjectSource( const cFibObjectSource * pInFibObjectSource );
	
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
	 * @return a pointer to the loaded Fib object
	 */
	cFibElement * loadFibObjectFromSource( int * iOutStatus = NULL );
	
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
	bool deleteLoadedFibObject();
	
	/**
	 * This method will extract all possible information for the Fib object
	 * info.
	 * It will adapt members of this object to the extracted information.
	 *
	 * @param true if information could be extracted, else false
	 */
	bool extractInfoFromLoadedFibObject();
	
	
	/**
	 * @see setInCategories
	 * @see setCategories()
	 * @see addCategory()
	 * @see removeCategory()
	 * @return the set with the categories this Fib object is in
	 * 	@see setInCategories
	 */
	std::set< std::string > getCategories() const;
	
	/**
	 * This method sets the categories this Fib object is in to the given set.
	 *
	 * @see setInCategories
	 * @see getCategories()
	 * @see addCategory()
	 * @see removeCategory()
	 * @param setInputCategories the set with the categories this Fib object is in
	 */
	void setCategories( const std::set< std::string > & setInputCategories );
	
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
	void addCategory( const std::string & strCategory );
	
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
	bool removeCategory( const std::string & strCategory );
	
	
	/**
	 * @return The map with connected Fib objects.
	 * 	key: the connected key, of which type the connection is (e. g.
	 * 		isContained, similar, sameType)
	 * 	value: the identifiers of connected Fib objects
	 * 		@see ulIdentifier
	 * 	@see mapConnectedTo
	 */
	std::map< string, std::set< unsigned long > > getConnectedToMap() const;
	
	/**
	 * This method returns a set of identifiers of Fib objects, which are
	 * connected to this Fib object via the given key szKey.
	 *
	 * @see mapConnectedTo
	 * @param szKey the key of the kind of connetions which should be returned
	 * @return a set with identifiers of Fib objects which are connected
	 * 	to this Fib object via the given key
	 */
	std::set< unsigned long > getConnectedFor( const string & szKey ) const;
	
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
	void addConnectionTo( const string & szKey,
		const unsigned long ulConnectedId );
	
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
	void addConnectionTo( const string & szKey,
		const std::set< unsigned long > & setNotConnectedIds );
	
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
	bool removeConnectionTo( const string & szKey,
		const unsigned long ulConnectedId );
	
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
	unsigned int removeConnectionTo( const string & szKey,
		const std::set< unsigned long > & setNotConnectedIds );
	
	
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
	std::vector< std::pair< time_t, unsigned long > > getLastUsedTimes() const;
	
	/**
	 * This method notices when the Fib object was used.
	 * When you use the Fib object call this method.
	 *
	 * @see vecLastUsed
	 * @param timestamp the timestamp when the Fib object was last used;
	 * 	if 0 (default) the timestamp will be set to the actual time
	 */
	void setFibObjectUsed( time_t timestamp = 0 );
	
	/**
	 * @return a list with the names of fur users, which can change this
	 * 	Fib object (e. g. "non", "all", "biokom")
	 * 	@see changeableBy
	 */
	std::set< std::string > getChangeableBy() const;
	
	/**
	 * @return true if the given user can change the Fib object for this
	 * 	Fib object info
	 * 	@see changeableBy
	 */
	bool canChange( const std::string & szUser ) const;
	
	/**
	 * This method will add the given user to the can change list.
	 * Added users can change the Fib object for this Fib object info.
	 *
	 * @see changeableBy
	 * @param szUser the user which can change the Fib object for this
	 * 	Fib object info
	 */
	void addUserWhichCanChange( const std::string & szUser );
	
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
	bool removeUserWhichCanChange( const std::string & szUser );
	
	
	/**
	 * This method set the number of Fib elements value for this Fib object
	 * info object.
	 *
	 * @see ulNumberOfFibElements
	 * @see getNumberOfFibElements()
	 * @param ulInNumberOfFibElements the number of Fib elements value
	 * 	to set
	 */
	void setNumberOfFibElements( const unsigned long ulInNumberOfFibElements );
	
	/**
	 * @see setNumberOfFibElements()
	 * @return the number of Fib elements value
	 * 	@see ulNumberOfFibElements
	 */
	unsigned long getNumberOfFibElements() const;

	/**
	 * This method set the number of input variables value for this Fib
	 * object info object.
	 *
	 * @see ulNumberOfInputVariables
	 * @see getNumberOfInputVariables()
	 * @param ulInNumberOfInputVariables the number of input variables value
	 * 	to set
	 */
	void setNumberOfInputVariables( const unsigned long ulInNumberOfInputVariables );
	
	/**
	 * @see setNumberOfInputVariables()
	 * @return the number of input variables value
	 * 	@see ulNumberOfInputVariables
	 */
	unsigned long getNumberOfInputVariables() const;

	/**
	 * This method set the number of external subobjects value for this Fib
	 * object info object.
	 *
	 * @see ulNumberOfExtSubobjects
	 * @see getNumberOfExtSubobjects()
	 * @param ulInNumberOfExtSubobjects the number of external subobjects
	 * 	value to set
	 */
	void setNumberOfExtSubobjects( const unsigned long ulInNumberOfExtSubobjects );
	
	/**
	 * @see setNumberOfExtSubobjects()
	 * @return the number of external subobjects value
	 * 	@see ulNumberOfExtSubobjects
	 */
	unsigned long getNumberOfExtSubobjects() const;
	
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
	bool setPreviewFibObjectInfo( cFibObjectInfo * pInPreviewFibObject );
	
	/**
	 * @see setPreviewFibObjectInfo()
	 * @return a pointer to the the Fib object info object for the preview
	 * 	Fib object for this Fib object info object
	 * 	@see pPreviewFibObject
	 */
	const cFibObjectInfo * getPreviewFibObjectInfo() const;
	
	/**
	 * @see setPreviewFibObjectInfo()
	 * @return a pointer to the the Fib object info object for the preview
	 * 	Fib object for this Fib object info object
	 * 	@see pPreviewFibObject
	 */
	cFibObjectInfo * getPreviewFibObjectInfo();
	
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
	typeOfInputVariables getTypeInVar( const unsigned int uiNumberOfInVar ) const;
	
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
	unsigned int getInVarForType( const typeOfInputVariables typeOfInVar ) const;
	
	/**
	 * This method adds the type for the uiNumberOfInVar'th input variable
	 * (counting starts with 1), of the Fib object of this Fib object info
	 * object.
	 * If a input variable with the same type exists allready, it will be
	 * replaced.
	 *
	 * @see mapInVarTypes
	 * @see removeTypeInVar()
	 * @see getTypeInVar()
	 * @see getInVarForType()
	 * @see typeOfInputVariables
	 * @param uiNumberOfInVar the number of the input variable, to which to
	 * 	add the type (counting starts with 1)
	 * @param typeOfInVar the type of the uiNumberOfInVar'th input variable
	 */
	void addTypeInVar( const unsigned int uiNumberOfInVar,
		const typeOfInputVariables typeOfInVar );

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
	void removeTypeInVar( const typeOfInputVariables typeOfInVar );

	/**
	 * This method returns if the given input variable type is for input
	 * variables, which determines the size of a Fib object.
	 *
	 * @see mapInVarTypes
	 * @see typeOfInputVariables
	 * @see getSizeInVarTyps()
	 * @return true if the given input variable type is for input
	 * 	variables, which determines the size of a Fib object
	 */
	static bool isSizeInVarTypes( const typeOfInputVariables typeOfInVar );

	/**
	 * This method returns all size typs for input variables of this object.
	 *
	 * @see mapInVarTypes
	 * @see typeOfInputVariables
	 * @see isSizeInVarTypes()
	 * @see addTypeInVar()
	 * @see removeTypeInVar()
	 * @see getTypeInVar()
	 * @see getInVarForType()
	 * @return all size typs for input variables of this object
	 */
	set< typeOfInputVariables > getSizeInVarTyps() const;
	
	/**
	 * This method returns all input variables which determine the size of
	 * this Fib object.
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
	set< unsigned int > getSizeInVar() const;


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
	static string getNameForInVarType( const typeOfInputVariables typeOfInVar );
	
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
	static typeOfInputVariables getInVarTypeForName( const string szNameInVar );
	
	/**
	 * This method will store this Fib object info object from the given
	 * stream.
	 *
	 * @see restoreFibObjectInfo()
	 * @param stream the output stream to which to store the Fib object info
	 * @return true if this Fib object info object could be stored, else false
	 */
	bool store( ostream & stream );

	/**
	 * This method will restore the Fib object info object from the given
	 * stream.
	 * Note: Members that are not restored won't change.
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
	int restoreFibObjectInfo( istream & stream );
	
	/**
	 * This method will restore the Fib object info object from the given
	 * TinyXml node.
	 * Note: Members that are not restored won't change.
	 *
	 * @see store()
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
	int restoreFibObjectInfo( const TiXmlNode * pXmlNode );
	
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
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 * @return a pointer to the restored Fib object info object or NULL if
	 * 	non could be restored
	 */
	static cFibObjectInfo * restore( istream & stream, int * iOutStatus=NULL );
	
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
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 * @return a pointer to the restored Fib object info object or NULL if
	 * 	non could be restored
	 */
	static cFibObjectInfo * restore( const TiXmlNode * pXmlNode,
		int * iOutStatus=NULL );
	
	
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
	bool registerFibObjectInfoChangeListener(
		lFibObjectInfoChanged * pFibObjectInfoListener );
	
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
	bool unregisterFibObjectInfoChangeListener(
		lFibObjectInfoChanged * pFibObjectInfoListener );
	
	/**
	 * Event method
	 * It will be called every time a Fib Fib object info object
	 * (cFibObjectInfo), at which this object is registered, was changed.
	 *
	 * @param pFibObjectInfoChanged a pointer to the event, with the information
	 * 	about the changed Fib node
	 */
	virtual void fibObjectInfoChanged(
		const eFibObjectInfoChangedEvent * pFibObjectInfoChanged );
	
	
protected:
	
	/**
	 * This method sents a Fib object info object changed event to all change
	 * Fib object info object listeners of this object.
	 * The event will just say that this Fib object info object has canged.
	 *
	 * @see setListenersFibNodeChanged
	 */
	void sendFibObjectInfoChange();

	/**
	 * This method sents a Fib object info object changed event to all change
	 * Fib object info object listeners of this object.
	 *
	 * @see setListenersFibNodeChanged
	 * @param pFibNodeChangedEvent the change event to send
	 */
	void sendFibObjectInfoChange(
		const eFibObjectInfoChangedEvent * pFibObjectInfoChanged );
	
	
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
	int restoreConnectedTo( const TiXmlElement * pXmlElement );
	
	
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
	int restoreFibObjectInfoInternal( const TiXmlNode * pXmlNode );
	
	/**
	 * This function will analyse the given text and try to evalue an
	 * input variable type for it.
	 * For example the text:
	 * 	"position of the start point in dimension 2 (y_s)"
	 * would be interpreted as the POS_DIM_2 input variable type.
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
	static typeOfInputVariables getInVarTypeFromText( const string & szText );
	
	/**
	 * The identifiers of this Fib object.
	 */
	unsigned long ulIdentifier;
	
	/**
	 * The mutex to lock access to this Fib object info object identifer.
	 * Lock the mutex if you use one of the following containers:
	 * @see ulIdentifier
	 */
	mutable QMutex mutexIdentifier;
	
	/**
	 * The name of this Fib object.
	 */
	std::string szNameOfFibObject;
	
	/**
	 * The description for the Fib object.
	 */
	std::string szDescription;
	
	/**
	 * A pointer to the object, which stores the data where the Fib
	 * object for this info is stored.
	 */
	cFibObjectSource * pFibObjectSource;
	
	/**
	 * The mutex to lock access to this Fib object info object source.
	 * Lock the mutex if you use one of the following containers:
	 * @see pFibObjectSource
	 */
	mutable QMutex mutexFibObjectSource;
	
	/**
	 * A pointer ot the loaded Fib object for this Fib object info or NULL
	 * if non was loaded.
	 */
	cFibElement * pLoadedFibObject;
	
	
	/**
	 * The set with the categories this Fib object is in.
	 * (e.g. isPointElement, isPerson)
	 * @see getCategories()
	 * @see setCategories()
	 * @see addCategory()
	 * @see removeCategory()
	 */
	std::set< std::string > setInCategories;

	/**
	 * The map with connected Fib objects.
	 * 	key: the connected key, of which type the connection is (e. g.
	 * 		isContained, similar, sameType)
	 * 	value: the identifiers of connected Fib objects
	 * 		@see ulIdentifier
	 */
	std::map< std::string, std::set< unsigned long > > mapConnectedTo;
	
	/*TODO
	A map with the data, when the connection to a Fib object was last used.
	map< unsigned long, vector< pair< time_t, unsigned long > >
		mapConnectionUsed;
	*/
	
	/**
	 * The vector whith the data when these Fib object was last used.
	 * Every vector entry contains a time stamp and a number of how often
	 * the Fib object was used betwean the time stamp and the next earlier
	 * time stamp. The first entry has the lowest time stamp. Also the
	 * first entry stores the last time the Fib object was used.
	 * The max number of how often used for ever entry is maximal 2^index (
	 * except the last vector used entry which is infinite).
	 * If the entry was used the new used time is set to the first entry.
	 * The old first entry is put to the second entry.
	 * When putting entry e_i to entry e_(i+1) the count of e_i is added to
	 * e_(i+1) if the resultung e_(i+1) will not become greater than its max
	 * number. Else, e_(i+1) will become greater than its max count number,
	 * the old e_(i+1) is put to the e_(i+2) entry and the entry e_i is
	 * set (timestamp and count) to the position e_(i+1).
	 * (This is valid for all entries except the last. If an entry is put to
	 * the last entry its count is added.)
	 *
	 * The vector contains 9 entries.
	 */
	std::vector< std::pair< time_t, unsigned long > > vecLastUsed;
	
	
	/**
	 * A list with the names of fur users, which can change this Fib object.
	 * (e. g. "all", "biokom")
	 */
	std::set< std::string > changeableBy;
	
	/**
	 * If not NULL the pointer to the cFibObjectInfo for the preview of
	 * this Fib object info.
	 * If NULL no preview exists.
	 * Note: If existing the cFibObjectInfoHandler will handle this object.
	 * @see cFibObjectInfoHandler
	 *
	 * TODO implement: extract, (extern) generate
	 */
	cFibObjectInfo * pPreviewFibObject;
	
	/**
	 * The number of input variables for the Fib object for this Fib object
	 * info object.
	 * @see cRoot::getNumberOfInputVariables()
	 */
	unsigned long ulNumberOfInputVariables;
	
	/**
	 * The number of external subobjects for the Fib object for this
	 * Fib object info object.
	 * @see cRoot::getNumberOfExternSubobjects()
	 */
	unsigned long ulNumberOfExtSubobjects;
	
	/**
	 * The number of Fib elements for the Fib object for this Fib object
	 * info object.
	 * @see cFibElement::getNumberOfElements()
	 */
	unsigned long ulNumberOfFibElements;
	
	//TODO
	/**
	 * The known types of the input variables.
	 * 	key: the type of the input variable
	 * 	value: the input variable, which has the type
	 * There can only be one input variable of every type (except type UNKNOWN).
	 * Every input variable not in this map has the type UNKNOWN .
	 * Note: The more frequent use case should be: searching for the input
	 * 	variable of a given type.
	 * @see typeOfInputVariables
	 * @see getTypeInVar()
	 * @see getInVarForType()
	 * @see addTypeInVar()
	 * @see removeTypeInVar()
	 * @see getInVarTypeForName()
	 * @see getNameForInVarType()
	 * TODO extract
	 */
	map< typeOfInputVariables , unsigned int > mapInVarTypes;
	
	
	/**
	 * The set with the listeners for changes in this Fib object info
	 * object changes.
	 * @see registerFibObjectInfoChangeListener()
	 * @see unregisterFibObjectInfoChangeListener()
	 * @see sendFibObjectInfoChange()
	 */
	std::set< lFibObjectInfoChanged * > setListenersFibNodeChanged;
	
	
	
	/**
	 * The mutex to lock access to this Fib object info object data.
	 * Lock the mutex if you use one of the following containers:
	 * @see szNameOfFibObject
	 * @see szDescription
	 * @see pLoadedFibObject
	 * @see setInCategories
	 * @see mapConnectedTo
	 * @see vecLastUsed
	 * @see changeableBy
	 * @see pPreviewFibObject
	 * @see ulNumberOfInputVariables
	 * @see ulNumberOfExtSubobjects
	 * @see ulNumberOfFibElements
	 * @see setListenersFibNodeChanged
	 * @see mapInVarTypes
	 */
	mutable QMutex mutexFibObjectInfoData;
	
	/**
	 * The mutex to check for cyclic dependencies for the preview Fib object
	 * info.
	 * @see setPreviewFibObjectInfo()
	 */
	static QMutex mutexCheckCyclicPreviewFibObjectInf;
	
};//end class cFibObjectInfo

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_OBJECT_INFO_H__





