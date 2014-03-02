/**
 * @file cFibObjectInfoHandler
 * file name: cFibObjectInfoHandler.h
 * @author Betti Oesterholz
 * @date 01.10.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for handling Fib object info objects for the
 * Fib creator application.
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
 * This file specifies a class for handling Fib object info objects for the
 * Fib creator application.
 * Fib object info objects contain the information about a Fib object.
 * This handler should work like a database for Fib objects, which can be
 * used by the Fib creator application. So the user can easily choose a
 * Fib object. The Fib object info objects contain the information and
 * dependency information for Fib objects, so that they can be displayed
 * in a way, that the user can choose from them a Fib object to use.
 *
 *
 * == Persistence ==
 *
 * Existing (including new created) Fib object info objects will be stored,
 * so that they can be retrieved later.
 *
 *
 * @pattern singelton
 * @pattern persistence
 * @see cFibObjectInfo
 * @see cFibObjectSource
 */
/*
History:
01.10.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_FIB_OBJECT_INFO_HANDLER_H__
#define ___FIB__NCREATOR__C_FIB_OBJECT_INFO_HANDLER_H__

#include "version.h"
#include "versionCreator.h"

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <utility>

#include <QObject>
#include <QMutex>
#include <QList>

#include "lFibObjectInfoChanged.h"


namespace fib{

namespace nCreator{

//forward declarations
class cFibObjectInfo;
class cFibObjectSource;
class cFibObjectCategory;

namespace nFibObjectInfoHandler{
	//forward declarations
	class cFibObjectInfoHandlerDeleter;
}


class cFibObjectInfoHandler: public lFibObjectInfoChanged {

///Zhe class to delete this singleton on destruction of the application.
friend class fib::nCreator::nFibObjectInfoHandler::cFibObjectInfoHandlerDeleter;

public:
	
	/**
	 * destructor
	 */
	virtual ~cFibObjectInfoHandler();
	
	/**
	 * @return an instance of the Fib info object handler
	 */
	static cFibObjectInfoHandler * getInstance();
	
	/**
	 * @return the name of this class "cFibObjectInfoHandler"
	 */
	std::string getName() const;
	
	
	/**
	 * @return the number of Fib object info objects in this handler
	 */
	unsigned int getNumberOfFibObjectInfos() const;

	/**
	 * This method returns the Fib object info object for the given identifier.
	 *
	 * @param ulIdentifier the identifer of the Fib object info object to return
	 * @return the Fib object info object for the given identifier or
	 * 	the null pointer NULL if non exists
	 */
	cFibObjectInfo * getFibObjectInfo( const unsigned long ulIdentifier );
	
	/**
	 * This method returns the Fib object info objects for the given
	 * identifiers. The order of the Fib object info objects will be that
	 * of the identifiers. Identifiers for which no Fib object info objects
	 * exists will be ignored.
	 *
	 * @param liIdentifier the list with the identifers of the Fib object
	 * 	info objects to return
	 * @return the Fib object info object for the given identifiers or
	 * 	the null pointer NULL if non exists
	 */
	std::list< cFibObjectInfo * > getFibObjectInfos(
		const std::list< unsigned long > & liIdentifier );
	
	/**
	 * This method will return the identifier for the Fib object info
	 * object for the given Fib object source object.
	 * If needed it will load Fib object and create info object for it.
	 *
	 * @param pFibObjectSource a pointer to the Fib object source object,
	 * 	for which the Fib object info object identifier should be returned
	 * @return the identifier for the Fib object info object for the given
	 * 	Fib object source object or 0 if non exists
	 */
	unsigned long getIdentifierForSource(
		const cFibObjectSource * pFibObjectSource );
	
	/**
	 * This method will add the given Fib object info object to the
	 * Fib object info objects of this handler.
	 * If the identifier of the Fib object info object is 0 , a free
	 * identifier will be choosen and set for the inserted Fib object info
	 * object.
	 * If the identifer of the Fib object info object is used allready,
	 * the given Fib object info object will overwrite the existing
	 * Fib object info object with the same identifier.
	 *
	 * @see mapFibObjectInfos
	 * @see setFibObjectInfos
	 * @see removeFibObjectInfo()
	 * @param fibObjectInfo the Fib object info object to add to this handler
	 * @return true if the Fib object info object was added, else false
	 */
	bool addFibObjectInfo( const cFibObjectInfo & fibObjectInfo );
	
	/**
	 * This method will remove the Fib object info object with the given
	 * identifier from this handler.
	 * Note: It will be also deleted from the memory.
	 *
	 * @see mapFibObjectInfos
	 * @see setFibObjectInfos
	 * @see addFibObjectInfo()
	 * @return true if a Fib object info object was removed else false
	 */
	bool removeFibObjectInfo( const unsigned long ulIdentifier );
	
	/**
	 * @return the next identifier not used by a Fib object info object
	 * 	@see ulFirstFreeIdentifier
	 */
	unsigned long getNextFreeIdentifier() const;
	
	
	/**
	 * This method returns a sorted list of Fib object info objects.
	 * All Fib object info objects are sorted in an order according to the
	 * times they where used. In which recently used times have a higher weight.
	 * The Fib object info objects with the higher sum of weights (for their
	 * used times) will be before the Fib object info objects with the lower
	 * sum of weights.
	 *
	 * @see cFibObjectInfo::getLastUsedTimes()
	 * @see getLastUsedTimesWeight()
	 * @see mapUsedTimeSortedFibObjectInfos
	 * @param ulLast the number of the last Fib object info object of all
	 * 	sorted Fib object info objects to return (counting starts with 1 )
	 * 	or 0 if all should be returned
	 * @param ulFirst the number of the first Fib object info object of all
	 * 	sorted Fib object info objects to return (counting starts with 1 );
	 * 	All Fib object info object from the ulFirst'th (including) to the
	 * 	ulLast'th  (including) will be returned
	 * @return a "last used time" sorted list of Fib object info objects
	 */
	std::list< cFibObjectInfo * > getSortedFibObjectInfos(
		const unsigned long ulLast = 0, const unsigned long ulFirst = 0 );
	
	/**
	 * This method returns a sorted list of identifiers of Fib object info objects.
	 * All Fib object info objects are sorted in an order according to the
	 * times they where used. In which recently used times have a higher weight.
	 * The Fib object info objects with the higher sum of weights (for their
	 * used times) will be before the Fib object info objects with the lower
	 * sum of weights.
	 *
	 * @see cFibObjectInfo::getLastUsedTimes()
	 * @see getLastUsedTimesWeight()
	 * @see mapUsedTimeSortedFibObjectInfos
	 * @param ulLast the number of the last Fib object info object of all
	 * 	sorted Fib object info objects to return (counting starts with 1 )
	 * 	or 0 if all should be returned
	 * @param ulFirst the number of the first Fib object info object of all
	 * 	sorted Fib object info objects to return (counting starts with 1 );
	 * 	All Fib object info object from the ulFirst'th (including) to the
	 * 	ulLast'th  (including) will be returned
	 * @return a "last used time" sorted list of identifiers of Fib object
	 * 	info objects
	 */
	std::list< unsigned long > getSortedFibObjectInfoIds(
		const unsigned long ulLast = 0, const unsigned long ulFirst = 0 );
	
	/**
	 * This method returns a sorted list of identifiers of Fib object info
	 * objects of a given cateory.
	 * All Fib object info objects are sorted in an order according to the
	 * times they where used. In which recently used times have a higher weight.
	 * The Fib object info objects with the higher sum of weights (for their
	 * used times) will be before the Fib object info objects with the lower
	 * sum of weights.
	 * All returned Fib object info objects will be in the given category.
	 *
	 * @see cFibObjectInfo::getLastUsedTimes()
	 * @see cFibObjectInfo::setInCategories
	 * @see getNumberOfSortedFibObjectInfoIdsForCategory()
	 * @see getLastUsedTimesWeight()
	 * @see mapUsedTimeSortedFibObjectInfos
	 * @see setPossibleCategories
	 * @see getPossibleCategories()
	 * @param szCategory the category all returned Fib object infos should be in
	 * @param ulLast the number of the last Fib object info object of all
	 * 	sorted Fib object info objects of the category to return
	 * 	(counting starts with 1 ) or 0 if all should be returned
	 * @param ulFirst the number of the first Fib object info object of all
	 * 	sorted Fib object info objects of the category to return
	 * 	(counting starts with 1 );
	 * 	All Fib object info object from the ulFirst'th (including) to the
	 * 	ulLast'th  (including) will be returned
	 * @return a "last used time" sorted list of identifiers of Fib object
	 * 	info objects
	 */
	std::list< unsigned long > getSortedFibObjectInfoIdsForCategory(
		const std::string & szCategory,
		const unsigned long ulLast = 0, const unsigned long ulFirst = 0 );
	
	/**
	 * This method returns number of a sorted Fib object info objects in the
	 * given cateory.
	 * All Fib object info objects are sorted in an order according to the
	 * times they where used. In which recently used times have a higher weight.
	 * The Fib object info objects with the higher sum of weights (for their
	 * used times) will be before the Fib object info objects with the lower
	 * sum of weights.
	 * All counted Fib object info objects will be in the given category.
	 *
	 * @see getSortedFibObjectInfoIdsForCategory()
	 * @see cFibObjectInfo::getLastUsedTimes()
	 * @see cFibObjectInfo::setInCategories
	 * @see getLastUsedTimesWeight()
	 * @see mapUsedTimeSortedFibObjectInfos
	 * @see setPossibleCategories
	 * @see getPossibleCategories()
	 * @param szCategory the category all counted Fib object infos should be in
	 * @return the number of Fib object infos in the "last used time" sorted
	 * 	list of Fib object info objects of the given category
	 */
	unsigned long getNumberOfSortedFibObjectInfoIdsForCategory(
		const std::string & szCategory );
	
	/**
	 * This method sorts the list of identifiers of Fib object info objects.
	 * All Fib object info objects are sorted in an order according to the
	 * times they where used. In which recently used times have a higher weight.
	 * The Fib object info objects with the higher sum of weights (for their
	 * used times) will be before the Fib object info objects with the lower
	 * sum of weights.
	 * Identifiers in the given list, for which no Fib object info handler in
	 * this handler exists, will be ignored.
	 *
	 * @see cFibObjectInfo::getLastUsedTimes()
	 * @see getLastUsedTimesWeight()
	 * @see mapUsedTimeSortedFibObjectInfos
	 * @param setFibObjectInfoIds the list of identifiers of Fib object info
	 * 	objects to sort
	 * @return a "last used time" sorted list of identifiers of Fib object
	 * 	info objects
	 */
	std::list< unsigned long > sortFibObjectInfoIds(
		const std::set< unsigned long > & setFibObjectInfoIds );
	
	/**
	 * This method sorts the list of Fib object info objects.
	 * All Fib object info objects are sorted in an order according to the
	 * times they where used. In which recently used times have a higher weight.
	 * The Fib object info objects with the higher sum of weights (for their
	 * used times) will be before the Fib object info objects with the lower
	 * sum of weights.
	 *
	 * @see cFibObjectInfo::getLastUsedTimes()
	 * @see getLastUsedTimesWeight()
	 * @see mapUsedTimeSortedFibObjectInfos
	 * @param setFibObjectInfos the set of of Fib object info objects to sort
	 * @return a "last used time" sorted list of of Fib object info objects
	 */
	std::list< cFibObjectInfo * > sortFibObjectInfo(
		const std::set< cFibObjectInfo * > & setFibObjectInfos ) const;
	
	/**
	 * This method sorts the list of Fib object info objects.
	 * All Fib object info objects are sorted in an order according to the
	 * times they where used. In which recently used times have a higher weight.
	 * The Fib object info objects with the higher sum of weights (for their
	 * used times) will be before the Fib object info objects with the lower
	 * sum of weights.
	 *
	 * @see cFibObjectInfo::getLastUsedTimes()
	 * @see getLastUsedTimesWeight()
	 * @see mapUsedTimeSortedFibObjectInfos
	 * @param liFibObjectInfos the list of of Fib object info objects to sort
	 * @return a "last used time" sorted list of of Fib object info objects
	 */
	std::list< cFibObjectInfo * > sortFibObjectInfo(
		const std::list< cFibObjectInfo * > & liFibObjectInfos ) const;
	
	/**
	 * This method updates the the sorted Fib object info objects.
	 * If the "last used time" data of a Fib object info object changes
	 * you can resort it with this method.
	 *
	 * @see mapUsedTimeSortedFibObjectInfos
	 * @see getLastUsedTimesWeight()
	 * @see getSortedFibObjectInfos()
	 * @see getSortedFibObjectInfoIds()
	 * @see sortFibObjectInfoIds()
	 * @see sortFibObjectInfo()
	 */
	void updateUsedTimeSortedFibObjectInfos();
	
	
	/**
	 * This method returns a set with the possible categories for the
	 * Fib object info objects of this handler.
	 * (e.g. isPointElement, isPerson)
	 *
	 * @see setPossibleCategories
	 * @see addPossibleCategories()
	 * @see mutexFibObjectInfoHandler
	 * @see cFibObjectInfo::setInCategories
	 * @return a set with the possible categories for the Fib object info
	 * 	objects of this handler
	 */
	std::set< std::string > getPossibleCategories() const;
	
	/**
	 * This method returns a set with the possible categories for the
	 * Fib object info objects of this handler.
	 * (e.g. isPointElement, isPerson)
	 * Note: The categories are returned as cFibObjectCategory objects.
	 *
	 * @see setPossibleCategories
	 * @see addPossibleCategories()
	 * @see mutexFibObjectInfoHandler
	 * @see cFibObjectInfo::setInCategories
	 * @return a set with the possible categories for the Fib object info
	 * 	objects of this handler
	 */
	QList< cFibObjectCategory > getPossibleFibObjectCategories() const;
	
	/**
	 * @return returns the category to get all Fib object info objects
	 */
	static std::string getCategoryForAll();
	
	/**
	 * Event method
	 * This method will be called every time a Fib Fib object info object
	 * (cFibObjectInfo), at which this object is registered, was changed.
	 *
	 * @see lFibObjectInfoChanged
	 * @param pFibObjectInfoChanged a pointer to the event, with the
	 * 	information about the changed Fib object info object
	 */
	virtual void fibObjectInfoChanged(
		const eFibObjectInfoChangedEvent * pFibObjectInfoChanged );
	
protected:
	
	/**
	 * constructor for the Fib info object handler
	 */
	cFibObjectInfoHandler();
	
	/**
	 * This method returns the sum of weights for the given last used times.
	 * All Fib object info object are sorted in an order according to the
	 * times they where used. In which recently used times have a higher weight.
	 * The Fib object info objects with the higher sum of weights (for their
	 * used times) will be before the Fib object info objects with the lower
	 * sum of weights.
	 * This method will evalue and return the sum of weights.
	 *
	 * @see cFibObjectInfo::getLastUsedTimes()
	 * @param vecLastUsedTimes the vector to the last used times information
	 * 	for a Fib object info object
	 * @return the sum of weights for the last used times
	 */
	static double getLastUsedTimesWeightSum(
		const std::vector< std::pair< time_t, unsigned long > > & vecLastUsedTimes );
	
	//TODO check
	
	/**
	 * This method will add the given Fib object info object to the
	 * "used time" sorted Fib object infos.
	 * Note: It will not use the mutexFibObjectInfoHandler, so lock it
	 * 	outside this method.
	 *
	 * @see mapUsedTimeSortedFibObjectInfos
	 * @see mutexUsedTimeSortedFibObjectInfos
	 * @param pFibObjectInfo the Fib object info object to add to the
	 * 	"used time" sorted Fib object infos Fib object infos
	 * @param bLock if true the mutexUsedTimeSortedFibObjectInfos will be
	 * 	used (locked and unlocked)
	 */
	void addToUsedTimeSortedFibObjectInfos( cFibObjectInfo * pFibObjectInfo,
		bool bLock=true );
	
	/**
	 * This method will remove the given Fib object info object from the
	 * "used time" sorted Fib object infos.
	 * Note: It will not use the mutexFibObjectInfoHandler, so lock it
	 * 	outside this method.
	 * 	But will use the mutexUsedTimeSortedFibObjectInfos.
	 *
	 * @see mapUsedTimeSortedFibObjectInfos
	 * @see mutexUsedTimeSortedFibObjectInfos
	 * @param pRemovedFibObjectInfo the Fib object info object to remove from the
	 * 	"used time" sorted Fib object infos
	 * @return true if a Fib object info object was removed, else false
	 */
	bool removeFromUsedTimeSortedFibObjectInfos(
		const cFibObjectInfo * pRemovedFibObjectInfo );
	
#ifdef FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
	
	/**
	 * This method evaluates the "used time" sorted lists/vectors of
	 * Fib object info objects for the categories.
	 * It will use the Fib object info (order) in mapUsedTimeSortedFibObjectInfos
	 * to evaluate the "used time" sorted Fib object info lists for
	 * mapCategoryUsedTimeSortedFibObjectInfos.
	 * Note: This method will not use mutex mutexUsedTimeSortedFibObjectInfos.
	 *
	 * @see mapCategoryUsedTimeSortedFibObjectInfos
	 * @see mapUsedTimeSortedFibObjectInfos
	 * @see bReevaluateMapCategoryUsedTimeSortedFibObjectInfos
	 * @see mutexUsedTimeSortedFibObjectInfos
	 */
	void evaluateMapCategoryUsedTimeSortedFibObjectInfos();
	
#endif //FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS

	//TODO check end
	
	
	/**
	 * This method adds a set with categories to the set of the possible
	 * categories for Fib object info objects of this handler.
	 * (e.g. isPointElement, isPerson)
	 * Note: This method will use no mutex.
	 *
	 * @see setPossibleCategories
	 * @see getPossibleCategories()
	 * @see cFibObjectInfo::setInCategories
	 * @param setInPossibleCategories a set with the possible categories, for
	 * 	the Fib object info objects of this handler, to add
	 */
	void addPossibleCategories(
		const std::set< std::string >  & setInPossibleCategories );
	
	
	/**
	 * This method returns the string for the path to the Fib object info
	 * objects of this database.
	 *
	 * @see loadListOfInfoObjects()
	 * @see loadFibInfoObject()
	 * @see storeFibInfoObject()
	 * @return the string for the path to the Fib object info objects
	 */
	char * getFibObjectInfoPath() const;
	
	/**
	 * This method loads a list of all existing Fib object info identifiers
	 * into the mapFibObjectInfos .
	 *
	 * @see getFibObjectInfoPath()
	 * @see mapFibObjectInfos
	 * @return true if a Fib object info object list could be loaded, else false
	 */
	bool loadListOfInfoObjects();
	
	/**
	 * This method checks if for the Fib object database the Fib object infos
	 * for this handler where created.
	 * (This method returns true if the file:
	 * 	szPathToFibObjectInfos"fibDbInfosCreated.flg" exists.)
	 *
	 * @see loadFibDatabase()
	 * @return true if the Fib object database identifers for this
	 * 	handler where created, else false
	 */
	bool checkFibDbIdsExist() const;
	
	/**
	 * This method creates for all Fib database objects new Fib object
	 * info objects (with their own unique Fib object info identifiers).
	 *
	 * @see checkFibDbIdsExist
	 * @return true if the Fib object infos for the Fib database objects
	 * 	could be created, else false
	 */
	bool loadFibDatabase();
	
	/**
	 * This method loads the Fib object info object for the given identifier
	 * and returns it.
	 *
	 * @see getFibObjectInfoPath()
	 * @see loadFibInfoObject()
	 * @see mapFibObjectInfos
	 * @see loadListOfInfoObjects()
	 * @param ulIdentifier the identifier of the Fib object info object to load
	 * @return a pointer to the Fib object info object or NULL if non exists
	 */
	cFibObjectInfo * loadFibInfoObject( const unsigned long ulIdentifier );

	/**
	 * This method stores the given Fib object info object to the disk into
	 * the Fib object info object folder.
	 *
	 * @see getFibObjectInfoPath()
	 * @see storeFibInfoObject()
	 * @see mapFibObjectInfos
	 * @see loadListOfInfoObjects()
	 * @param pFibObjectInfo Fib object info object to store
	 * @return true if the Fib object info object could be stored else false
	 */
	bool storeFibInfoObject( cFibObjectInfo * pFibObjectInfo );
	
	/**
	 * This function reads the integer number from the given string.
	 * Leading zeros '0' will be ignored.
	 *
	 * @param pSzNumber the number as a string
	 * @return the number of pSzNumber
	 */
	static unsigned long toUnsignedLong( const char * pSzNumber );

//members
	
	/**
	 * A pointer to the info object handler object.
	 */
	static cFibObjectInfoHandler * pFibObjectInfoHandler;
	
	/**
	 * A set with the in this handler existing / loaded Fib info objects.
	 */
	std::set< cFibObjectInfo * > setFibObjectInfos;
	
	/**
	 * The mapping for the Fib object info objects to their identifiers.
	 * 	key: the identifier of the Fib object info object
	 * 	value: the Fib object info object for the identifier or the
	 * 		null pointer NULL, if non was loaded
	 */
	std::map< unsigned long , cFibObjectInfo * > mapFibObjectInfos;
	
	/**
	 * The number of the first not used identifier.
	 * 0 is resevered and should not be used for a Fib object info object.
	 */
	unsigned long ulFirstFreeIdentifier;
	
	/**
	 * The path where the Fib object info are stored.
	 * @see mapFibObjectInfoFiles
	 */
	char * szPathToFibObjectInfos;
	
	/**
	 * A map with the file names for the Fib object info objects.
	 * 	key: the identifier of the Fib object info object
	 * 	value: the file name of the file (in the szPathToFibObjectInfos
	 * 		folder) for the Fib object info object for the key identifier
	 * @see szPathToFibObjectInfos
	 */
	std::map< unsigned long , std::string > mapFibObjectInfoFiles;
	
	/**
	 * The set with the possible categories for the Fib object info objects
	 * of this handler.
	 * (e.g. isPointElement, isPerson)
	 * @see cFibObjectInfo::setInCategories
	 * @see mutexFibObjectInfoHandler
	 * @see getPossibleCategories()
	 * @see addPossibleCategories()
	 */
	std::set< std::string > setPossibleCategories;
	
	/**
	 * Mutex to lock access to the Fib info object data of this class.
	 * Lock the mutex if you use one of the following containers:
	 * @see setFibObjectInfos
	 * @see mapFibObjectInfos
	 * @see mapFibObjectInfoFiles
	 * @see setPossibleCategories
	 */
	mutable QMutex mutexFibObjectInfoHandler;
	
	/**
	 * All Fib object info object are sorted in an order according to the
	 * times they where used. In which recently used times have a higher weight.
	 * The Fib object info objects with the higher sum of weights (for their
	 * used times) will be before the Fib object info objects with the lower
	 * sum of weights.
	 * This map stores the Fib object infos and their "used time" value.
	 * 	key: a value for the sum of of weights (for their used times)
	 * 		for the value Fib object info
	 * 	value: the Fib object info
	 *
	 * @see mutexUsedTimeSortedFibObjectInfos
	 * @see getLastUsedTimesWeightSum()
	 * @see cFibObjectInfo::getLastUsedTimes()
	 * @see getSortedFibObjectInfos()
	 * @see getSortedFibObjectInfoIds()
	 * @see sortFibObjectInfoIds()
	 */
	std::multimap< double , cFibObjectInfo * > mapUsedTimeSortedFibObjectInfos;
	
#ifdef FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
	
	/**
	 * All Fib object info object are sorted in an order according to the
	 * times they where used. In which recently used times have a higher weight.
	 * The Fib object info objects with the higher sum of weights (for their
	 * used times) will be before the Fib object info objects with the lower
	 * sum of weights.
	 * This map stores the sorted Fib object info objects:
	 * 	key: the category for the stored submaps of "used time" sorted
	 * 		Fib object infos
	 * 	value: The vector with the sorted Fib object infos for the key
	 * 		category. In the reverse order of mapUsedTimeSortedFibObjectInfos:
	 * 		highest weight at the front (=with lower indexes).
	 *
	 * @see mapUsedTimeSortedFibObjectInfos
	 * @see evaluateMapCategoryUsedTimeSortedFibObjectInfos()
	 * @see mutexUsedTimeSortedFibObjectInfos
	 * @see getLastUsedTimesWeightSum()
	 * @see cFibObjectInfo::getLastUsedTimes()
	 * @see getSortedFibObjectInfos()
	 * @see getSortedFibObjectInfoIds()
	 * @see sortFibObjectInfoIds()
	 */
	std::map< std::string, std::vector< cFibObjectInfo * > >
		mapCategoryUsedTimeSortedFibObjectInfos;
	
	/**
	 * If true the mapCategoryUsedTimeSortedFibObjectInfos should be
	 * reevaluated. To reevaluate mapUsedTimeSortedFibObjectInfos will be used.
	 *
	 * @see evaluateMapCategoryUsedTimeSortedFibObjectInfos()
	 * @see mapCategoryUsedTimeSortedFibObjectInfos
	 * @see mapUsedTimeSortedFibObjectInfos
	 */
	bool bReevaluateMapCategoryUsedTimeSortedFibObjectInfos;
	
#ifdef TODO_WEG
//TODO OR
//TODO good idea?
	/**
	 * All Fib object info object are sorted in an order according to the
	 * times they where used. In which recently used times have a higher weight.
	 * The Fib object info objects with the higher sum of weights (for their
	 * used times) will be before the Fib object info objects with the lower
	 * sum of weights.
	 * This map stores the (via multimaps) sorted Fib object info objects:
	 * 	key: the category for the stored submaps of "used time" sorted
	 * 		Fib object infos
	 * 	value: The submaps stores the Fib object infos and their
	 * 		"used time" value for the key category:
	 * 		key: a value for the sum of of weights (for their used times)
	 * 			for the value Fib object info
	 * 		value: the Fib object info
	 *
	 * @see mutexUsedTimeSortedFibObjectInfos
	 * @see getLastUsedTimesWeightSum()
	 * @see cFibObjectInfo::getLastUsedTimes()
	 * @see getSortedFibObjectInfos()
	 * @see getSortedFibObjectInfoIds()
	 * @see sortFibObjectInfoIds()
	 */
	std::map< std::string, std::multimap< double , cFibObjectInfo * > >
		mapUsedTimeSortedFibObjectInfos;
	
#endif //TODO_WEG
	
#endif //FEATURE_FIB_OBJECT_INFO_HANDLER_SORTET_SUBCATEGORIES_MAPS
	
	
	/**
	 * Mutex to lock access to the sorted Fib info object data of this class.
	 * Lock the mutex if you use one of the following containers:
	 * @see mapUsedTimeSortedFibObjectInfos
	 */
	mutable QMutex mutexUsedTimeSortedFibObjectInfos;
	
	
};//end class cFibObjectInfoHandler

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_OBJECT_INFO_HANDLER_H__





