/**
 * @class cMultimediaInfo
 * file name: cMultimediaInfo.cpp
 * @author Betti Oesterholz
 * @date 24.06.2009
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
24.06.2009  Oesterholz  created
21.12.2012  Oesterholz  virtual destructor added
*/

#include "cMultimediaInfo.h"
#include "cRoot.h"


using namespace fib;


/**
 * The constructor for the multimediainfo.
 * The defaultmapping for the dimension i is the mappingvalue i.
 *
 * @param root the root -element this multimediainfo stands in/for
 */
cMultimediaInfo::cMultimediaInfo( cRoot * root) :
		ulFibVersion( FIB_VERSION ), ulFibDbVersion( FIB_DB_VERSION ),
		masterRoot( root ){
//nothing to do
}

/**
 * The destructor for the multimediainfo.
 */
cMultimediaInfo::~cMultimediaInfo(){
	//nothing to do
}



/**
 * This Method clones this object.
 *
 * @return a clone of this object
 */
cMultimediaInfo *cMultimediaInfo::clone() const{

	cMultimediaInfo *multimediainfoClone=new cMultimediaInfo( masterRoot );


	multimediainfoClone->setFibVersion( getFibVersion() );
	multimediainfoClone->setDatabaseVersion( getDatabaseVersion() );

	return multimediainfoClone;
}


/**
 * @return the version of the Fib -multimedialanguage needed for the
 * 	Fib -multimediaobject
 */
unsignedLongFib cMultimediaInfo::getFibVersion() const{

	return ulFibVersion;
}


/**
 * @param ulFibVersion the version of the Fib -multimedialanguage to set
 */
void cMultimediaInfo::setFibVersion( unsignedLongFib ulFibVersion ){
	this->ulFibVersion=ulFibVersion;
}


/**
 * @return the version of the Fib -database needed for the
 * 	Fib -multimediaobject
 */
unsignedLongFib cMultimediaInfo::getDatabaseVersion() const{
	return ulFibDbVersion;
}


/**
 * @param ulFibVersion the version of the Fib -database to set
 */
void cMultimediaInfo::setDatabaseVersion( unsignedLongFib ulFibDbVersion ){

	this->ulFibDbVersion=ulFibDbVersion;
}


/**
 * This method evalues and sets the Fib -multimedialanguage and
 * Fib -database versionnumbers, which are needed for the Fib -object.
 *
 * @return true if the versionsnumbers where evalued and set
 */
bool cMultimediaInfo::evalueMinVersionsNumbers(){

	ulFibVersion=FIB_VERSION;
	ulFibDbVersion=FIB_DB_VERSION;

	return true;
}

/**
 * This Method checks if the given multimedianfo is equal to this
 * multimedianfo.
 *
 * @param multimediaInfo the multimedianfo which should be equal to this
 * 	multimedianfo
 * @return true if the given multimedianfo is equal to this
 * 	multimedianfo, else false
 */
bool cMultimediaInfo::equal( const cMultimediaInfo & multimediaInfo ) const{
	return ((*this)==multimediaInfo);
}


/**
 * This Method checks if the given multimedianfo is equal to this
 * multimedianfo.
 *
 * @param multimediaInfo the multimedianfo which should be equal to this
 * 	multimedianfo
 * @return true if the given multimedianfo is equal to this
 * 	multimedianfo, else false
 */
bool cMultimediaInfo::operator==( const cMultimediaInfo & multimediaInfo) const{
	
	if ( getFibVersion() != multimediaInfo.getFibVersion() ){
		return false;
	}
	if ( getDatabaseVersion() != multimediaInfo.getDatabaseVersion() ){
		return false;
	}
	return true;
}


/**
 * This method stores this multimediainfo in the XML -format into the
 * given stream.
 * example: <multimedia_info fib_version="1" db_version="0"/>
 *
 * @param ostream the stream where thismultimediainfo should be stored to
 * @return true if this multimediainfo is stored, else false
 */
bool cMultimediaInfo::storeXml( ostream & ostream ) const{
	
	ostream<<"<multimedia_info fib_version=\""<< getFibVersion() <<"\" ";
	ostream<<"db_version=\""<< getDatabaseVersion() <<"\"/>"<<endl;
	
	return true;
}


/**
 * This method restores this multimediainfo in the XML -format from an
 * an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node the fib -object is stored in
 * @return an integervalue with the errorvalue
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in TiXmlElement
 * 		- 1 loading warning, invalid data in TiXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in TiXmlElement, maybe the loaded
 * 			object is wrong
 */
intFib cMultimediaInfo::restoreXml( const TiXmlElement * pXmlElement ){
	
	//check the vector type
	if ( pXmlElement == NULL ){
		//Error: noting to restore
		return -1;
	}
	string szElementType( pXmlElement->Value() );
	if ( szElementType != "multimedia_info" ){
		//Error: wrong element type to restore
		return -2;
	}
	intFib iReturnValue = 0;
	
	int iLoadedFibVersion = 0;
	const char * szXmlFibVersion = pXmlElement->Attribute( "fib_version", &iLoadedFibVersion );
	
	if ( szXmlFibVersion == NULL ){
		//Warning: The multimediainfo has no fib -versionsnumber.
		iReturnValue = 2;
	}else{
		setFibVersion( iLoadedFibVersion );
	}
	
	int iLoadedDbVersion = 0;
	const char * szXmlDbVersion = pXmlElement->Attribute( "db_version", &iLoadedDbVersion );
	
	if ( szXmlDbVersion == NULL ){
		//Warning: The multimediainfo has no fib -databaseversionsnumber.
		iReturnValue = 2;
	}else{
		setDatabaseVersion( iLoadedDbVersion );
	}
	return iReturnValue;
}
























