/**
 * @class cDomainVectorBasis
 * file name: cDomainVectorBasis.cpp
 * @author Betti Oesterholz
 * @date 14.01.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a vector domains.
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
 * This file contains the basis class of all vector Fib domains.
 * It's not possible to create instances from this class.
 *
 */
/*
History:
14.01.2011  Oesterholz  created
*/

//TODO weg
//#define DEBUG


#include "cDomainVectorBasis.h"

#include "cFibVector.h"
#include "cDomainVector.h"
#include "cDomainVectorOpenEnd.h"


using namespace fib;



/**
 * @return true if the object represents a scalar domain, else false
 */
bool cDomainVectorBasis::isScalar() const{
	return false;
}


/**
 * @return true if the object represents a vector domain, else false
 */
bool cDomainVectorBasis::isVector() const{
	return true;
}


/**
 * This function creates creates a good domain wich contains all the
 * vectors of the given list liVectors .
 * A domain is better than an other domain, if it takes less storage bits
 * to store the numbers and the domain.
 * Beware: You have to care that the returned domain is deleted. (if
 * 	one was returned)
 *
 * @param liVectors the list with the vectors, for which a domain is to create
 * @return a new domain which contains all the given vectors liVectors
 */
cDomainVectorBasis * cDomainVectorBasis::createGoodDomain(
		const list< cFibVector * > & liVectors ){
	
	DEBUG_OUT_L2(<<"cDomainVectorBasis::createGoodDomain(): create domain for "<<liVectors.size()<<" vectors"<<endl<<flush);
	
	if ( liVectors.empty() ){
		//domain contains no vectors
		DEBUG_OUT_L2(<<"cDomainVectorBasis::createGoodDomain() done -> domain contains no vectors"<<endl<<flush);
		vector<cDomainSingle*> vecNoElementDomains;
		return new cDomainVector( vecNoElementDomains );
	}
	//check if vectors have all same number of elements
	//+ evalue minimum number of elements
	unsigned int uiMinimumNumberOfElements =
		liVectors.front()->getNumberOfElements();
	bool bSameNumberOfElements = true;
	for ( list< cFibVector * >::const_iterator
			itrVector = liVectors.begin();
			itrVector != liVectors.end(); itrVector++ ){
		
		const unsigned int uiNumberOfSetElements =
			(*itrVector)->getNumberOfElements();
		if ( uiNumberOfSetElements != uiMinimumNumberOfElements ){
			//at least some of the sets have a different number of elements
			bSameNumberOfElements = false;
			if ( uiNumberOfSetElements < uiMinimumNumberOfElements ){
				uiMinimumNumberOfElements = uiNumberOfSetElements;
			}
		}
	}
	if ( uiMinimumNumberOfElements == 0 ){
		if ( bSameNumberOfElements ){
			//all vectors have 0 vector elements
			DEBUG_OUT_L2(<<"cDomainVectorBasis::createGoodDomain() done -> all vectors have 0 vector elements"<<endl<<flush);
			vector<cDomainSingle*> vecNoElementDomains;
			return new cDomainVector( vecNoElementDomains );
		}//else ther are more than 0 elements in some vectors
		uiMinimumNumberOfElements = 1;
	}
	//evalue values of the subelements of the vectors
	DEBUG_OUT_L2(<<"cDomainVectorBasis::createGoodDomain() evalue values of the subelements of the vectors; uiMinimumNumberOfElements="<<uiMinimumNumberOfElements<<" and "<<(bSameNumberOfElements?"same":"different")<<" number of elements"<<endl<<flush);
	vector< list< doubleFib > > vecElements( uiMinimumNumberOfElements );
	const unsigned int uiMaximumNumberOfVectorElement =
		uiMinimumNumberOfElements - 1;
	for ( list< cFibVector * >::const_iterator
			itrVector = liVectors.begin();
			itrVector != liVectors.end(); itrVector++ ){
		
		const unsigned int uiNumberOfActualElements =
			(*itrVector)->getNumberOfElements();
		for ( unsigned int uiActualElement = 1;
				uiActualElement <= uiNumberOfActualElements; uiActualElement++ ){
		
			if ( ! (*itrVector)->isVariable( uiActualElement ) ){
				if ( uiActualElement <= uiMaximumNumberOfVectorElement ){
					
					vecElements[ uiActualElement - 1 ].push_back(
						(*itrVector)->getValue( uiActualElement ) );
				}else{//( uiMinimumNumberOfElements < uiActualElement )
					//last subdomain is for all numbers from uiMinimumNumberOfElements
					vecElements[ uiMaximumNumberOfVectorElement ].
						push_back( (*itrVector)->getValue( uiActualElement ) );
				}
			}//else vector element is a variable -> don't add it 
		}
	}
	//create sub domain
	DEBUG_OUT_L2(<<"cDomainVectorBasis::createGoodDomain() create subdomain"<<endl<<flush);
	vector<cDomainSingle*> vecFibSetVectorDomains(
			uiMinimumNumberOfElements );
	for ( unsigned int uiNumberOfElement = 0; 
			uiNumberOfElement < uiMinimumNumberOfElements;
			uiNumberOfElement++ ){
		
		vecFibSetVectorDomains[ uiNumberOfElement ] = cDomainSingle::
			createGoodDomain( vecElements[ uiNumberOfElement ] );
	}
	cDomainVectorBasis * pVectorDomain = NULL;
	if ( bSameNumberOfElements ){
		//create vector domain with number of elements uiMinimumNumberOfElements
		DEBUG_OUT_L2(<<"cDomainVectorBasis::createGoodDomain() create vector domain with "<<uiMinimumNumberOfElements<<" number of elements"<<endl<<flush);
		pVectorDomain = new cDomainVector( vecFibSetVectorDomains );
	}else{//create vector domain open end with number of elements uiMinimumNumberOfElements
		DEBUG_OUT_L2(<<"cDomainVectorBasis::createGoodDomain() create vector domain open end with "<<uiMinimumNumberOfElements<<" number of elements"<<endl<<flush);
		pVectorDomain = new cDomainVectorOpenEnd( vecFibSetVectorDomains );
	}
	//delete created subdomains
	DEBUG_OUT_L2(<<"cDomainVectorBasis::createGoodDomain() delete created subdomains"<<endl<<flush);
	for ( unsigned int uiNumberOfElement = 0; 
			uiNumberOfElement < uiMinimumNumberOfElements;
			uiNumberOfElement++ ){
		
		delete vecFibSetVectorDomains[ uiNumberOfElement ];
	}
	
	DEBUG_OUT_L2(<<"cDomainVectorBasis::createGoodDomain() done -> domain created"<<endl<<flush);
	return pVectorDomain;
}









