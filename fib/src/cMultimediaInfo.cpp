/**
 * @class cMultimediaInfo
 * file name: cMultimediaInfo.cpp
 * @author Betti Oesterholz
 * @date 24.06.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the multimedia information of an root element.
 *
 *
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
 * This class represents the multimedia information for an root element.
 * This includes the version numbers of Fib and the Fib database.
 *
 */
/*
History:
24.06.2009  Oesterholz  created
21.12.2012  Oesterholz  virtual destructor added
01.08.2013  Oesterholz  method assignValues() added
*/

#include "cMultimediaInfo.h"
#include "cRoot.h"


using namespace fib;


/**
 * The constructor for the multimedia information.
 * The defaultmapping for the dimension i is the mapping value i.
 *
 * @param root the root element this multimedia information stands in/for
 */
cMultimediaInfo::cMultimediaInfo( cRoot * root ) :
		ulFibVersion( FIB_VERSION ), ulFibDbVersion( FIB_DB_VERSION ),
		masterRoot( root ){
//nothing to do
}

/**
 * The destructor for the multimedia information.
 */
cMultimediaInfo::~cMultimediaInfo(){
	//nothing to do
}



/**
 * This method clones this object.
 *
 * @return a clone of this object
 */
cMultimediaInfo *cMultimediaInfo::clone() const{

	cMultimediaInfo *pMultimediaInformationClone =
		new cMultimediaInfo( masterRoot );

	pMultimediaInformationClone->setFibVersion( getFibVersion() );
	pMultimediaInformationClone->setDatabaseVersion( getDatabaseVersion() );

	return pMultimediaInformationClone;
}


/**
 * @return the version of the Fib multimedia language needed for the
 * 	Fib multimedia object
 */
unsignedLongFib cMultimediaInfo::getFibVersion() const{

	return ulFibVersion;
}


/**
 * @param ulFibVersion the version of the Fib multimedia language to set
 */
void cMultimediaInfo::setFibVersion( unsignedLongFib ulFibVersion ){
	this->ulFibVersion=ulFibVersion;
}


/**
 * @return the version of the Fib database needed for the
 * 	Fib multimedia object
 */
unsignedLongFib cMultimediaInfo::getDatabaseVersion() const{
	return ulFibDbVersion;
}


/**
 * @param ulFibVersion the version of the Fib database to set
 */
void cMultimediaInfo::setDatabaseVersion( unsignedLongFib ulFibDbVersion ){

	this->ulFibDbVersion=ulFibDbVersion;
}


/**
 * This method evalues and sets the Fib multimedia language and
 * Fib database version numbers, which are needed for the Fib -object.
 *
 * @return true if the version numbers where evalued and set
 */
bool cMultimediaInfo::evalueMinVersionsNumbers(){

	ulFibVersion=FIB_VERSION;
	ulFibDbVersion=FIB_DB_VERSION;

	return true;
}

/**
 * This method checks if the given multimedia information is equal to this
 * multimedia information.
 *
 * @param multimediaInfo the multimedia information which should be equal
 * 	to this multimedia information
 * @return true if the given multimedia information is equal to this
 * 	multimedia information, else false
 */
bool cMultimediaInfo::equal( const cMultimediaInfo & multimediaInfo ) const{
	return ((*this)==multimediaInfo);
}


/**
 * This method checks if the given multimedia information is equal to this
 * multimedia information.
 *
 * @param multimediaInfo the multimedia information which should be equal
 * 	to this multimedia information
 * @return true if the given multimedia information is equal to this
 * 	multimedia information, else false
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
 * This method asigns / copies the values from the given multimedia
 * information to rmation. This means, it will copy
 * everything of the rmation multimediaInfo except pointers to Fib
 * elements (e. g. the master root element), these will remain the same.
 *
 * @see equal()
 * @param multimediaInfo the multimedia information, from which to
 * 	assign / copy the values
 * @return true if the values could be copied from the given multimedia
 * 	information multimediaInfo, else false
 */
bool cMultimediaInfo::assignValues( const cMultimediaInfo & multimediaInfo ){
	
	ulFibVersion   = multimediaInfo.ulFibVersion;
	ulFibDbVersion = multimediaInfo.ulFibDbVersion;
	return true;
}


/**
 * This method stores this multimedia information in the XML -format into the
 * given stream.
 * example: <multimedia_info fib_version="1" db_version="0"/>
 *
 * @param ostream the stream where thismultimedia information should be stored to
 * @return true if this multimedia information is stored, else false
 */
bool cMultimediaInfo::storeXml( ostream & ostream ) const{
	
	ostream<<"<multimedia_info fib_version=\""<< getFibVersion() <<"\" ";
	ostream<<"db_version=\""<< getDatabaseVersion() <<"\"/>"<<endl;
	
	return true;
}


/**
 * This method restores this multimedia information in the XML -format from an
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
		//Warning: The multimedia information has no fib -versionsnumber.
		iReturnValue = 2;
	}else{
		setFibVersion( iLoadedFibVersion );
	}
	
	int iLoadedDbVersion = 0;
	const char * szXmlDbVersion = pXmlElement->Attribute( "db_version", &iLoadedDbVersion );
	
	if ( szXmlDbVersion == NULL ){
		//Warning: The multimedia information has no fib -databaseversionsnumber.
		iReturnValue = 2;
	}else{
		setDatabaseVersion( iLoadedDbVersion );
	}
	return iReturnValue;
}
























