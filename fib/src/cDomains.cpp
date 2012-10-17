/**
 * @class cDomains
 * file name: cDomains.cpp
 * @author Betti Oesterholz
 * @date 09.06.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a list of domains.
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
 * This class represents a list of domains for an root -element.
 * The domain list consists of a number of domains with a type for which
 * they apply. No two domains can be for the same type.
 *
 */
/*
History:
09.06.2009  Oesterholz  created
12.02.2012  Oesterholz  methods for changed cDomainReference
11.03.2012  Oesterholz  getDirectDomainForElement() added;
	Bugfix: equal and operator==() compare refered to domains
18.04.2012  Oesterholz  Bugfix: replace FirstChild()->ToElement() with
	FirstChildElement()
23.09.2012  Oesterholz  Warning removed: virtual destructor added
*/


#include "cDomains.h"
#include "cTypeProperty.h"
#include "cDomainVectorBasis.h"

#include "nBitStream.h"

using namespace fib;

/**
 * The constructor for the domain list.
 */
cDomains::cDomains():standardDomain( 16 ){
	//nothing to do
}

/**
 * The desstructor for the domain list.
 */
cDomains::~cDomains(){
	//nothing to do
}


/**
 * @return the number of domains in the domain list
 */
unsignedIntFib cDomains::getNumberOfDomains() const{
	return domainElements.size();
}


/**
 * This method returns the domain on the given position iDomainNumber
 * in the domain list.
 * If the domain on the position is a reference domain @see cDomainReference
 * the domain to which it is rfered to will be returned.
 *
 * @param iDomainNumber the positionsnumber on which the domain to
 * 	return stands in the domain list (the counting begins with 1)
 * @return a reference to the iDomainNumber'th domain (so you can adopt
 * 	the domain) of this domain list or the Nullpointer NULL if non
 * 	such exists;
 */
cDomain * cDomains::getDomain( unsignedIntFib iDomainNumber ) const{

	if ( iDomainNumber < 1 ){
		return NULL;
	}

	//get the iterator for the position iDomainNumber
	list<cDomainElement>::const_iterator actualListElement=
		domainElements.begin();
	
	while ( (iDomainNumber != 1) &&
			(actualListElement != domainElements.end()) ){
		iDomainNumber--;
		actualListElement++;
	}
	//no such position iDomainNumber -> can't return domain
	if ( actualListElement == domainElements.end() ){
		return NULL;
	}//else domain list entry found
	//check domain on position
	cDomain * pDomainOnPosition = actualListElement->getDomain();

	if ( pDomainOnPosition == NULL ){
		return NULL;
	}
	if ( pDomainOnPosition->isReference() ){
		return getDomainForReferenceDomain(
			(cDomainReference*)pDomainOnPosition,
			actualListElement->getElementType() );
	}
	return pDomainOnPosition;
}


/**
 * This method returns the type on the given position iTypeNumber
 * in the domain list.
 *
 * @param iTypeNumber the positionsnumber on which the type to
 * 	return stands in the domain list (the counting begins with 1)
 * @return a reference to the iTypeNumber'th type of this domain list or
 * 	the Nullpointer NULL if non such exists;
 */
cTypeElement * cDomains::getType( unsignedIntFib iTypeNumber ) const{

	if ( iTypeNumber < 1 ){
		return NULL;
	}

	//get the iterator for the position iDomainNumber
	list<cDomainElement>::const_iterator actualListElement=
		domainElements.begin();
	
	while ( (iTypeNumber != 1) &&
			(actualListElement != domainElements.end()) ){
		iTypeNumber--;
		actualListElement++;
	}
	//no such position iDomainNumber -> can't return domain
	if ( actualListElement == domainElements.end() ){
		return NULL;
	}

	return actualListElement->getElementType();
}


/**
 * This method returns the domain for the given type from the
 * domain list.
 * If the domain for the type is a reference domain @see cDomainReference
 * the domain to which it is rfered to will be returned.
 *
 * @param type the type for which the domain is to return
 * @return a reference to the domain (so you can adopt the domain) of
 * 	this domain list for elements of the given type or the Nullpointer
 * 	NULL if non such exists;
 */
cDomain * cDomains::getDomainForElement( const cTypeElement &type ) const{

	//find the domain for the type
	for ( list<cDomainElement>::const_iterator actualListElement =
			domainElements.begin(); actualListElement != domainElements.end();
			actualListElement++ ){
		
		if ( type.equalElementType( *(actualListElement->getElementType()) ) ){
			//domain for the type founded
			cDomain * pDomainOnPosition = actualListElement->getDomain();
			
			if ( ! pDomainOnPosition->isReference() ){
				//not a reference domain
				return pDomainOnPosition;
			}//else a reference domain
			return getDomainForReferenceDomain(
				(cDomainReference*)pDomainOnPosition,
				actualListElement->getElementType() );
		}//else check next domain list entry
	}
	//no domain for the type founded
	return NULL;
}


/**
 * This method returns the direct domain on the given position
 * iDomainNumber in the domain list, without evaluating it.
 * Since some domains (ie cDomainReference) are evalued by methods like
 * getDomain(), this method will return the domain directly without
 * evaluing it.
 *
 * @see getDomain()
 * @see getDomainForElement()
 * @param iDomainNumber the position on which the direct domain to
 * 	return stands in the domain list (the counting begins with 1)
 * @return a reference to the iDomainNumber'th direct domain (so you
 * 	can adopt the domain) of this domain list or the Nullpointer
 * 	NULL if non such exists;
 */
cDomain * cDomains::getDirectDomain(
		const unsignedIntFib iInDomainNumber ) const{
	
	if ( iInDomainNumber < 1 ){
		return NULL;
	}
	unsignedIntFib iDomainNumber = iInDomainNumber;
	//get the iterator for the position iDomainNumber
	list<cDomainElement>::const_iterator actualListElement=
		domainElements.begin();
	
	while ( (iDomainNumber != 1) &&
			(actualListElement != domainElements.end()) ){
		iDomainNumber--;
		actualListElement++;
	}
	//no such position iDomainNumber -> can't return domain
	if ( actualListElement == domainElements.end() ){
		return NULL;
	}
	//check the domain on the position
	cDomain * pDomainOnPosition = actualListElement->getDomain();
	
	return pDomainOnPosition;
}


/**
 * This method returns the direct domain for the given type
 * in the domain list, without evaluating it.
 * Since some domains (ie cDomainReference) are evalued by methods like
 * getDomainForElement(), this method will return the domain directly
 * without evaluing it.
 *
 * @see getDomain()
 * @see getDomainForElement()
 * @param type the type for which the domain is to return
 * @return a reference to the direct domain (so you can adopt the domain)
 * 	of the gifen type of this domain list or the Nullpointer
 * 	NULL if non such exists;
 */
cDomain * cDomains::getDirectDomainForElement( const cTypeElement &type ) const{

	//find the domain for the type
	for ( list<cDomainElement>::const_iterator actualListElement =
			domainElements.begin(); actualListElement != domainElements.end();
			actualListElement++ ){
		
		if ( type.equalElementType( *(actualListElement->getElementType()) ) ){
			//domain for the type founded
			cDomain * pDomainOnPosition = actualListElement->getDomain();
			
			return pDomainOnPosition;
		}//else check next domain list entry
	}
	//no domain for the type founded
	return NULL;
}


/**
 * This method returns the domain to which the given reference domain
 * refers to.
 * If no domain to which it is refered can be found the standard domain
 * for the pDomainReference type will be returned.
 *
 * @param pDomainReference reference domain for which the domain is to
 * 	be returned
 * @param pTypeElementForWhich a pointer to the type element for which the
 * 	domain should be
 * @return a pointer to the domain (so you can adopt the domain) for
 * 	the reference domain or the Nullpointer NULL if non such exists
 */
cDomain * cDomains::getDomainForReferenceDomain(
		cDomainReference * pDomainReference,
		cTypeElement * pTypeElementForWhich ) const{
	
	if ( pDomainReference == NULL ){
		//no reference domain
		if ( pTypeElementForWhich != NULL ){
			//no domain to which it is refered to
			//use standard domain of the type
			list<cDomainElement>::iterator itrActualStandardDomain;
			for ( itrActualStandardDomain = standardDomains.begin();
					itrActualStandardDomain != standardDomains.end();
					itrActualStandardDomain++ ){
				
				if ( pTypeElementForWhich->equalElementType(
						*(itrActualStandardDomain->getElementType() ) ) ){
					/*domain for the type founded
					-> the standard domain was created befor*/
					return itrActualStandardDomain->getDomain();
				}
			}//else no standard domain found -> create one
			standardDomains.push_back( cDomainElement( *pTypeElementForWhich, NULL ) );
			
			return standardDomains.back().getDomain();
		}//else don't know what to return
		return NULL;
	}
	
	//set with all found reference domains to check for cyclic dependencies
	set< cDomain*  > setDomainsFoundTillNow;
	
	cDomain * pDomainToWhichItIsRefered = pDomainReference;
	while ( pDomainToWhichItIsRefered->isReference() ){
		//search till the domain to which it is refered is found
		pDomainReference = (cDomainReference*)pDomainToWhichItIsRefered;
		setDomainsFoundTillNow.insert( pDomainReference );
		
		//evalue domain to which it is refered to
		const cTypeElement * pTypeElement =
			pDomainReference->getTypeElement();
		
		bool bUseStandardDomain = true;
		if ( pTypeElement != NULL ){
			//use type to which it is refered to
			//find the domain for the type
			for ( list<cDomainElement>::const_iterator
						actualListElement = domainElements.begin();
					actualListElement != domainElements.end();
					actualListElement++ ){
				
				if ( pTypeElement->equalElementType( *(actualListElement->getElementType()) ) ){
					//domain for the type founded
					cDomain * pDomainOnPosition = actualListElement->getDomain();
					
					if ( ! pDomainOnPosition->isReference() ){
						//not a reference domain -> domain to which it is refered to
						pDomainToWhichItIsRefered = pDomainOnPosition;
						bUseStandardDomain = false;
						break;
					}//else a reference domain
					//check cyclic dependencies over more than one step
					if ( setDomainsFoundTillNow.find( pDomainOnPosition ) !=
								setDomainsFoundTillNow.end() ){
						/*the reference domain was found befor
						-> use standard domain of the type*/
						bUseStandardDomain = true;
						break;
					}//else return choosen domain
					pDomainToWhichItIsRefered = pDomainOnPosition;
					bUseStandardDomain = false;
					break;
				}//else check next domain list entry
			}//end for find type
		}//else nothing refered to -> return standard domain
		
		if ( bUseStandardDomain ){
			if ( pTypeElementForWhich != NULL ){
				//no domain to which it is refered to
				//use standard domain of the type
				list<cDomainElement>::iterator itrActualStandardDomain;
				for ( itrActualStandardDomain = standardDomains.begin();
						itrActualStandardDomain != standardDomains.end();
						itrActualStandardDomain++ ){
					
					if ( pTypeElementForWhich->equalElementType(
							*(itrActualStandardDomain->getElementType() ) ) ){
						/*domain for the type founded
						-> the standard domain was created befor*/
						return itrActualStandardDomain->getDomain();
					}
				}//else no standard domain found -> create one
				standardDomains.push_back( cDomainElement( *pTypeElementForWhich, NULL ) );
				
				return standardDomains.back().getDomain();
			}//else use standard domain for the type to which it is refered
			list<cDomainElement>::iterator itrActualStandardDomain;
			for ( itrActualStandardDomain = standardDomains.begin();
					itrActualStandardDomain != standardDomains.end();
					itrActualStandardDomain++ ){
				
				if ( pTypeElement->equalElementType(
						*(itrActualStandardDomain->getElementType() ) ) ){
					/*domain for the type founded
					-> the standard domain was created befor*/
					return itrActualStandardDomain->getDomain();
				}
			}//else no standard domain found -> create one
			standardDomains.push_back( cDomainElement( *pTypeElement, NULL ) );
			
			return standardDomains.back().getDomain();
		}//else if use standard domain
		
		//check if to choose a subdomain
		const vector<unsignedIntFib> & vecNumberSubdomains =
			pDomainReference->getElement();
		if ( ( ! vecNumberSubdomains.empty() ) &&
				( pDomainToWhichItIsRefered->isVector() ) ){
			//choose subdomain
			cDomainVectorBasis * pActualChoosenDomain =
				(cDomainVectorBasis*)pDomainToWhichItIsRefered;
			
			cDomain * pNextChoosenDomain = NULL;
			cDomain * pDomainToReturn = pActualChoosenDomain;
			//for choose subdomain
			if ( pTypeElementForWhich != NULL ){
				//type element for which the domain is given -> check if compatible
				bool bCompatibleDomainFound = false;
				for ( vector<unsignedIntFib>::const_iterator
						itrActualSubdomain = vecNumberSubdomains.begin();
						itrActualSubdomain != vecNumberSubdomains.end(); itrActualSubdomain++ ){
					
					pNextChoosenDomain =
						pActualChoosenDomain->getElementDomain( *itrActualSubdomain );
					
					if ( pNextChoosenDomain == NULL ){
						//try the last element of the vector domain
						pNextChoosenDomain = pActualChoosenDomain->getElementDomain(
							pActualChoosenDomain->getNumberOfElements() );
						if ( pNextChoosenDomain == NULL ){
							//can't find correct domain
							break;
						}
					}
					
					if ( pTypeElementForWhich->isCompatible( *pNextChoosenDomain ) ){
						//domain is compatible -> use it
						pDomainToReturn = pNextChoosenDomain;
						bCompatibleDomainFound = true;
					}else if ( ! bCompatibleDomainFound ){
						//no compatible domain found jet -> take what is ther
						pDomainToReturn = pNextChoosenDomain;
					}
					if ( ! pNextChoosenDomain->isVector() ){
						//no vector domain can't choose from it
						break;
					}
					pActualChoosenDomain = (cDomainVectorBasis*)pNextChoosenDomain;
				}//end for choose subdomain
			}else{//no type element for which the domain is be given
				for ( vector<unsignedIntFib>::const_iterator
						itrActualSubdomain = vecNumberSubdomains.begin();
						itrActualSubdomain != vecNumberSubdomains.end(); itrActualSubdomain++ ){
					
					pNextChoosenDomain =
						pActualChoosenDomain->getElementDomain( *itrActualSubdomain );
					
					if ( pNextChoosenDomain == NULL ){
						//try the last element of the vector domain
						pNextChoosenDomain = pActualChoosenDomain->getElementDomain(
							pActualChoosenDomain->getNumberOfElements() );
						if ( pNextChoosenDomain == NULL ){
							//can't find correct domain
							break;
						}
					}
					
					pDomainToReturn = pNextChoosenDomain;
					
					if ( ! pNextChoosenDomain->isVector() ){
						//no vector domain can't choose from it
						break;
					}
					pActualChoosenDomain = (cDomainVectorBasis*)pNextChoosenDomain;
				}//end for choose subdomain
			}
			pDomainToWhichItIsRefered = pDomainToReturn;
		}//end if choose subdomain
	}//end while search for refered to domain
	return pDomainToWhichItIsRefered;
}



/**
 * This method adds a given domain for the given type to the domain list.
 * If an domain for the element allready exists, it is replaced.
 *
 * @param type the type for which the domain is to add
 * @param domain the domain for the given type
 * @return the number of the position on which the new domain stands in
 * 	the domain list or 0 if the domain wasn't inserted
 */
unsignedIntFib cDomains::addDomain( const cTypeElement &type, const cDomain &domain ){
	
	//find the domain for the type
	list<cDomainElement>::iterator actualListElement;
	unsignedIntFib actualDomainlistPosition = 1;
	
	for ( actualListElement = domainElements.begin(); 
			actualListElement != domainElements.end(); actualListElement++ ){
		
		if ( type.equalElementType( *(actualListElement->getElementType()) ) ){
			//domain for the type founded
			if ( type.equal( *(actualListElement->getElementType()) ) ){
				//the type hasn't changed
				actualListElement->setDomain( domain );
				return actualDomainlistPosition;
			}else{//the type has changed -> replace old entry
				domainElements.erase( actualListElement );
				break;//add new entry
			}
		}
		actualDomainlistPosition++;
	}

	/*no domain for the type founded
	-> add an new domainelement to the end of the domain list*/
	domainElements.push_back( cDomainElement( type, domain ) );
	return domainElements.size();
}


/**
 * This method adds a given domain for the given type to the domain list.
 * If an domain for the element allready exists, it is replaced.
 * This add method dosn't copy the domain, befor adding it.
 *
 * @param type the type for which the domain is to add
 * @param domain a pointer to the domain for the given type
 * @return the number of the position on which the new domain stands in
 * 	the domain list or 0 if the domain wasn't inserted
 */
unsignedIntFib cDomains::addDomain( const cTypeElement &type, cDomain * domain ){
	
	//find the domain for the type
	list<cDomainElement>::iterator actualListElement;
	unsignedIntFib actualDomainlistPosition = 1;
	
	for ( actualListElement = domainElements.begin(); 
			actualListElement != domainElements.end(); actualListElement++ ){
		
		if ( type.equalElementType( *(actualListElement->getElementType()) ) ){
			//domain for the type founded
			if ( type.equal( *(actualListElement->getElementType()) ) ){
				//the type hasn't changed
				actualListElement->setDomain( domain );
				return actualDomainlistPosition;
			}else{//the type has changed -> replace old entry
				domainElements.erase( actualListElement );
				break;//add new entry
			}
		}
		actualDomainlistPosition++;
	}

	/*no domain for the type founded
	-> add an new domainelement to the end of the domain list*/
	domainElements.push_back( cDomainElement( type, domain ) );
	return domainElements.size();
}



/**
 * This method sets the domain for the given type to the standarddomain
 * of the type. If no entry for the type exists, an entry is added.
 *
 * @param type the type for which the domain is to set to the
 * 	standarddomain
 * @return the number of the position on which the type stands in
 * 	the domain list
 */
unsignedIntFib cDomains::setStandardDomain( const cTypeElement &type ){

	cDomain *standardDomain = type.getStandardDomain();
	unsignedIntFib iPositionChanged = addDomain( type, *standardDomain );
	delete standardDomain;
	
	return iPositionChanged;
}



/**
 * This method deletes the domain on the given position iDomainNumber
 * in the domain list.
 *
 * @param iDomainNumber the positionsnumber on which the domain to
 * 	delete stands in the domain list (the counting begins with 1)
 * @return true if the domain on the position is deleted, else false
 */
bool cDomains::deleteDomain( unsignedIntFib iDomainNumber ){

	if ( iDomainNumber<1 ){
		return false;
	}

	//get the iterator for the position iDomainNumber
	list<cDomainElement>::iterator actualListElement=
		domainElements.begin();
	
	while ( (iDomainNumber != 1) &&
			(actualListElement != domainElements.end()) ){
		iDomainNumber--;
		actualListElement++;
	}
	//no such position iDomainNumber -> can't delete
	if ( actualListElement == domainElements.end() ){
		return false;
	}

	//delete founded element
	domainElements.erase( actualListElement );
	return true;
}


/**
 * This method deletes the domain for the given type from the
 * domain list.
 *
 * @param type the type for which the domain is to delete
 * @return true if the domain for the given type is deleted, else false
 */
bool cDomains::deleteDomain( const cTypeElement &type ){

	//find the domain for the type
	list<cDomainElement>::iterator actualListElement;
	
	for ( actualListElement = domainElements.begin(); 
			actualListElement != domainElements.end(); actualListElement++ ){
		
		if ( type.equalElementType( *(actualListElement->getElementType()) ) ){
			//domain for the type founded ->delete it
			
			domainElements.erase( actualListElement );
			return true;
		}
	}
	/*no domain for the type founded -> nothing to delete*/
	return false;
}


/**
 * This Method clones this object.
 *
 * @return a clone of this object
 */
cDomains *cDomains::clone() const{

	cDomains *domainsClone = new cDomains();
	
	domainsClone->domainElements = domainElements;

	return domainsClone;
}


/**
 * This method evaluades the size of the domains in bits in the
 * compressed file form.
 *
 * @see store()
 * @return the size of the domains in bits in the compressed form
 */
unsignedLongFib cDomains::getCompressedSize() const{

	unsignedLongFib ulCompressedSize = 64;//size of the domain list
	
	//add bits for domains
	for ( list<cDomainElement>::const_iterator actualDomain = domainElements.begin();
			actualDomain != domainElements.end(); actualDomain++ ){
		
		ulCompressedSize += actualDomain->getCompressedSize();
	}
	return ulCompressedSize;
}


/**
 * This method stores this domains in the XML -format into the
 * given stream.
 *
 * @param ostream the stream where domains should be stored to
 * @param szName the name the writen XML -element should have
 * @return true if this domains are stored, else false
 */
bool cDomains::storeXml( ostream & ostream, string szName ) const{

	//write starttag
	ostream<<"<"<<szName<<">"<<endl;
	
	//write the domains
	for ( list<cDomainElement>::const_iterator actualDomain = domainElements.begin();
			actualDomain != domainElements.end(); actualDomain++ ){
		
		bool bDomainStored = actualDomain->storeXml( ostream );
		if ( ! bDomainStored ){
			return false;
		}
	}
	//write closetag
	ostream<<"</"<<szName<<">"<<endl;
	
	return true;
}



/**
 * This method restores this multimediainfo in the XML -format from an
 * an TinyXml element.
 *
 * @param pXmlNode a pointer to the TinyXml node wher the domains are stored in
 * @return an integervalue with the errorvalue
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid pXmlElement
 * 		- -2 loading error, invalid data in TiXmlElement
 * 		- 1 loading warning, invalid data in TiXmlElement, error could be corrected
 * 		- 2 loading warning, invalid data in TiXmlElement, maybe the loaded
 * 			object is wrong
 */
intFib cDomains::restoreXml( const TiXmlElement * pXmlElement ){
	
	//check the vector type
	if ( pXmlElement == NULL ){
		//Error: noting to restore
		return -1;
	}
	intFib iReturnValue = 0;
	
	domainElements.clear();

	//restore the domains
	const TiXmlElement * pXmlElementDomain = NULL;
	if ( pXmlElement->FirstChild() ){
		
		pXmlElementDomain = pXmlElement->FirstChildElement();
	}

	for( ; pXmlElementDomain; pXmlElementDomain = pXmlElementDomain->NextSiblingElement() ){
	
		pair< cTypeElement * , cDomain * > paRestoredDomain =
			cTypeElement::restoreXmlTypeWithDomain( pXmlElementDomain, iReturnValue );
		
		if ( (paRestoredDomain.first != NULL) && (paRestoredDomain.second != NULL) ){
			addDomain( *(paRestoredDomain.first), *(paRestoredDomain.second) );
		}else{
			if ( 0 < iReturnValue){
				iReturnValue = 2;
			}
		}
		if ( paRestoredDomain.first ){
			delete paRestoredDomain.first;
		}
		if ( paRestoredDomain.second ){
			delete paRestoredDomain.second;
		}
		if ( iReturnValue < 0 ){
			return iReturnValue;
		}
	}
	return iReturnValue;
}


/**
 * This method stores this domains in the compressed Fib -format
 * into the given stream.
 * It is needed because the stream can yust store byts but the size of
 * fib -elements can be any number of bits. Because of that ther have to
 * be a possibility to exchange the missing bits betwean the fib -elements.
 *
 * @see cFibElement::store
 * @param stream the stream where this domains should be stored to
 * @param cRestBits the not yet writen bits which should be stored
 * @param uiRestBitPosition the number of bits in the cRestBits which
 * 	should be writen respectively containing valid information
 * @return true if the domains are stored, else false
 */
bool cDomains::store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const{
	
	if ( uiRestBitPosition >= 8){
		//error in input
		return false;
	}
	
	//write domains size
	unsigned long long ulNumberOfDomains = getNumberOfDomains();
	
	bool bNumberStored = nBitStream::store( stream, cRestBits, uiRestBitPosition,
		ulNumberOfDomains, 64 );
	if ( ! bNumberStored ){
		return false;
	}

	//write the domains
	for ( list<cDomainElement>::const_iterator actualDomain = domainElements.begin();
			actualDomain != domainElements.end(); actualDomain++ ){
		
		bool bDomainStored = actualDomain->store( stream, cRestBits,
			uiRestBitPosition );
		if ( ! bDomainStored ){
			return false;
		}
	}

	return true;
}


/**
 * This method restores the domains from a bitstream, wher it is
 * stored in the compressed fib -format.
 *
 * @see store
 * @see cFibElement::store
 * @param iBitStream the stream where this domains is stored in,
 * 	because this stream is an cReadBits, any number of bits can be
 * 	readed from it
 * @return the errorvalue
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid stream
 * 		- -2 loading error, invalid data in stream
 * 		- 1 loading warning, invalid data in stream, error could be corrected
 * 		- 2 loading warning, invalid data in stream, maybe the loaded
 * 			object is wrong
 */
intFib cDomains::restore( cReadBits & iBitStream ){
	
	if ( ! iBitStream.getStream()->good() ){
		return -1;
	}
	//read number of domains to restore
	unsignedLongFib ulCountDomains = 0;
	
	unsigned int uiBitsRead = iBitStream.readBits( ulCountDomains, 64 );
	if ( ! iBitStream.getStream()->good() ){
		DEBUG_OUT_EL2(<<"Error: stream not good"<<endl);
		return -2;
	}
	if ( uiBitsRead != 64 ){
		DEBUG_OUT_EL2(<<"Error: "<<uiBitsRead<<" bits restored but should be 64"<<endl);
		return -2;
	}
	intFib iReturnValue = 0;
	
	domainElements.clear();

	for ( unsignedLongFib ulActualDomain = 1;
			ulActualDomain <= ulCountDomains; ulActualDomain++ ){
		
		DEBUG_OUT_L2(<<"Restoring the "<<ulActualDomain<<"'th domain "<<endl);
		//restore the domain type
		cTypeElement * pRestoredType =
			cTypeElement::restore( iBitStream, iReturnValue );
		if ( iReturnValue < 0 ){
			if ( pRestoredType ){
				delete pRestoredType;
			}
			DEBUG_OUT_EL2(<<"Error: while restoring type "<<endl);
			return iReturnValue;
		}
		//restore the domain
		cDomain * pRestoredDomain =
			cDomain::restore( iBitStream, iReturnValue );
		if ( iReturnValue < 0 ){
			if ( pRestoredType ){
				delete pRestoredType;
			}
			if ( pRestoredDomain ){
				delete pRestoredDomain;
			}
			DEBUG_OUT_EL2(<<"Error: while restoring domain "<<endl);
			return iReturnValue;
		}
//#define DEBUG_PRINT_RESTORED_DATA
#ifdef DEBUG_PRINT_RESTORED_DATA
		if ( pRestoredType != NULL ){
			pRestoredType->storeXml( cout );
		}else{
			cerr<<"Error: the restored type is NULL"<<endl;
		}
		if ( pRestoredDomain != NULL ){
			pRestoredDomain->storeXml( cout );
		}else{
			cerr<<"Error: the restored domain is NULL"<<endl;
		}
		
#endif //DEBUG_PRINT_RESTORED
		if ( (pRestoredType != NULL) && (pRestoredDomain != NULL) ){
			
			if ( pRestoredType->getType() == 6 ){
				//a cTypeProperty restored -> adapt to the domain if possible
				cTypeProperty * pRestoredPropertyType = new cTypeProperty(
					*((cTypeProperty*)pRestoredType), *pRestoredDomain );
				delete pRestoredType;
				pRestoredType = pRestoredPropertyType;
			}
			
			addDomain( *(pRestoredType), *(pRestoredDomain) );
		}else{
			if ( 0 < iReturnValue){
				iReturnValue = 2;
			}
			DEBUG_OUT_EL2(<<"Error: restored type ("<<pRestoredType<<") or domain ("<<pRestoredDomain<<") is NULL "<<endl);
		}
		if ( pRestoredType ){
			delete pRestoredType;
		}
		if ( pRestoredDomain ){
			delete pRestoredDomain;
		}
	}
	return iReturnValue;
}


/**
 * This Method checks if the given domains is equal to this domains.
 *
 * @param domains the domains to compare with this
 * @return true if the given domains is equal to this
 * 	domains, else false
 */
bool cDomains::equal( const cDomains &domains ) const{
	
	return ( (*this) == domains );
}


/**
 * This Method checks if the given domains is equal to this domains.
 *
 * @param domains the domains to compare with this
 * @return true if the given domains is equal to this
 * 	domains, else false
 */
bool cDomains::operator==( const cDomains &domains ) const{
	//compare the counts of the domains
	if ( getNumberOfDomains() != domains.getNumberOfDomains() ){
		return false;
	}
	
	//compare the domains
	for ( list<cDomainElement>::const_iterator actualDomain = domainElements.begin();
			actualDomain != domainElements.end(); actualDomain++ ){
		//compare the domains to which the actual type refers to
		cDomain * pThisDomain = getDomainForElement(
			* (actualDomain->getElementType()) );
		cDomain * pOtherDomain = domains.getDomainForElement(
			* (actualDomain->getElementType()) );
		
		if ( ( pOtherDomain == NULL ) && ( pThisDomain == NULL ) ){
			//domains are equal -> check next domain
			continue;
		}
		if ( ( pOtherDomain == NULL ) || ( pThisDomain == NULL ) ){
			//domain for an element is missing
			return false;
		}
		if ( ! ( (*pOtherDomain) == (*pThisDomain) ) ){
			//domains for the type not equal
			return false;
		}
	}
	return true;
}


/**
 * This operator makes this domains equal to the given domains.
 *
 * @param domains the domains to which this should be equal
 * @return a refernce to this domain
 */
cDomains & cDomains::operator=( const cDomains &domains ){

	domainElements.clear();
	
	for ( list<cDomainElement>::const_iterator itrActualDomain =
			domains.domainElements.begin();
			itrActualDomain != domains.domainElements.end();
			itrActualDomain++ ){
		
		domainElements.push_back( cDomainElement( *itrActualDomain ) );
	}
	return *this;
}














