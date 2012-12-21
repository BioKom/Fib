/**
 * @class cMultimediaInfo
 * file name: cMultimediaInfo.h
 * @author Betti Oesterholz
 * @date 21.06.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the multimediainfo of an root -element.
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
 * This class represents the multimediainfo for an root -element.
 * This includes the versionsnumbers of Fib and the Fib -Database.
 *
 */
/*
History:
21.06.2009  Oesterholz  created
21.12.2012  Oesterholz  virtual destructor added
*/

#ifndef ___C_MULTIMEDIA_INFO_H__
#define ___C_MULTIMEDIA_INFO_H__


#include "version.h"

#include "fibDatatyps.h"

#include "tinyxml.h"

#include <string>
#include <ostream>

using std::string;
using std::ostream;


namespace fib{

class cRoot;//cyclic dependencies

class cMultimediaInfo{

friend class cRoot;

protected:


	/**
	 * The version of the Fib -multimedialanguage needed for the
	 * Fib -multimediaobject.
	 * The value 0 means the version of the Fib -multimedialanguage is
	 * irrelevant.
	 */
	unsignedLongFib ulFibVersion;

	/**
	 * The version of the Fib -database needed for the Fib -multimediaobject.
	 * The value 0 means the version of the Fib -database is irrelevant.
	 */
	unsignedLongFib ulFibDbVersion;

	/**
	 * the pointer to the root object which uses this cMultimediaInfo
	 */
	cRoot * masterRoot;



#ifdef TEST
public: //make the following constructor public for the test
#endif

	/**
	 * The constructor for the multimediainfo.
	 * The defaultmapping for the dimension i is the mappingvalue i.
	 *
	 * @param root the root -element this multimediainfo stands in/for
	 */
	cMultimediaInfo( cRoot * root);

	/**
	 * The destructor for the multimediainfo.
	 */
	virtual ~cMultimediaInfo();

	/**
	 * This Method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cMultimediaInfo *clone() const;


public:

	/**
	 * @return the version of the Fib -multimedialanguage needed for the
	 * 	Fib -multimediaobject
	 */
	unsignedLongFib getFibVersion() const;


	/**
	 * @param ulFibVersion the version of the Fib -multimedialanguage to set
	 */
	void setFibVersion( unsignedLongFib ulFibVersion );


	/**
	 * @return the version of the Fib -database needed for the
	 * 	Fib -multimediaobject
	 */
	unsignedLongFib getDatabaseVersion() const;


	/**
	 * @param ulFibVersion the version of the Fib -database to set
	 */
	void setDatabaseVersion( unsignedLongFib ulFibDbVersion );


	/**
	 * This method evalues and sets the Fib -multimedialanguage and
	 * Fib -database versionnumbers, which are needed for the Fib -object.
	 *
	 * @return true if the versionsnumbers where evalued and set
	 */
	bool evalueMinVersionsNumbers();
	
	/**
	 * This Method checks if the given multimedianfo is equal to this
	 * multimedianfo.
	 *
	 * @param multimediaInfo the multimedianfo which should be equal to this
	 * 	multimedianfo
	 * @return true if the given multimedianfo is equal to this
	 * 	multimedianfo, else false
	 */
	virtual bool equal( const cMultimediaInfo &multimediaInfo ) const;

	/**
	 * This Method checks if the given multimedianfo is equal to this
	 * multimedianfo.
	 *
	 * @param multimediaInfo the multimedianfo which should be equal to this
	 * 	multimedianfo
	 * @return true if the given multimedianfo is equal to this
	 * 	multimedianfo, else false
	 */
	virtual bool operator==( const cMultimediaInfo & multimediaInfo) const;

	/**
	 * This method stores this multimediainfo in the XML -format into the
	 * given stream.
	 * example: <multimedia_info fib_version="1" db_version="0"/>
	 *
	 * @param ostream the stream where this multimediainfo should be stored to
	 * @return true if this multimediainfo is stored, else false
	 */
	virtual bool storeXml( ostream & ostream ) const;


	/**
	 * This method restores this multimediainfo in the XML -format from an
	 * an TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node the multimediainfo is stored in
	 * @return an integervalue with the errorvalue
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 */
	virtual intFib restoreXml( const TiXmlElement * pXmlElement );

};//end class cMultimediaInfo


}//end namespace fib

#endif //___C_MULTIMEDIA_INFO_H__
