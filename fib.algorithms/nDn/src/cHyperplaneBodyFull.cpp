/**
 * @file cHyperplaneBodyFull
 * file name: cHyperplaneBodyFull.cpp
 * @author Betti Oesterholz
 * @date 28.01.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements a class for a body with hyperplanes as its borders.
 * @pattern strategy
 *
 * Copyright (C) @c GPL3 2010 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (GPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * This file implements a class body with hyperplanes as its borders.
 * This body is defined by inequiations, all points wich fulfill the
 * inequiations are part of the body.
 * For the body all its hyperplane borders are stored and evalued.
 *
 * Beware of the curse of dimensions! The complexity of the body will
 * grow exponential with the number of dimensions. For example, just the
 * number of border points of a newly created body will be 2^uiDimensions .
 *
 * @see cHyperplaneBodyFull
 * @see cHyperplane
 * @see cInequation
 */
/*
History:
28.01.2011  Oesterholz  created
27.02.2011  Oesterholz  method getNumberOfBorderPoints() added
*/

#ifndef ___C_HYPERPLANE_BODY_FULL_CPP__
#define ___C_HYPERPLANE_BODY_FULL_CPP__


#include "version.h"


#include "cHyperplaneBodyFull.h"

#include <vector>
#include <ostream>
#include <map>
#include <cmath>




//for debugging comment in
//#define DEBUG_ADD_INEQUIATION
//#define DEBUG_COPY_CONSTRUCTOR


#ifdef DEBUG_ADD_INEQUIATION
	#define DEBUG_NEEDED
#endif //DEBUG_ADD_INEQUIATION

#ifdef DEBUG_COPY_CONSTRUCTOR
	#ifndef DEBUG_NEEDED
		#define DEBUG_NEEDED
	#endif
#endif //DEBUG_COPY_CONSTRUCTOR


#ifdef DEBUG_NEEDED

	#include <iostream>

	namespace fib{
	namespace algorithms{
	namespace nDn{
	namespace nHyperplaneBodyFull{
	namespace nDebug{
		/**
		 * This function prints the given vector to the given output stream.
		 *
		 * @param outputStream the output stream to print the vector to
		 * @param vector the vector to print
		 */
		template< class tElements > void printVector( ostream & outputStream,
				const vector< tElements > & vector ){
			
			outputStream<<"( ";
			for ( unsigned int uiDimension = 0; uiDimension < vector.size();
					uiDimension++ ){
				
				outputStream<< vector[ uiDimension ] <<", ";
			}
			outputStream<<")^T"<<endl;
		}
	};};};};};//fib::algorithms::nDn::nHyperplaneBodyFull::nDebug

#endif //DEBUG_ADD_INEQUIATION

using namespace std;

using namespace fib::algorithms::nDn;


/**
 * Namespace for helperclasses for the cHyperplaneBodyFull class.
 */
using namespace nHyperplaneBodyFull;


/**
 * methods for the @class cHyperplaneData
 * The data for a hyperplane.
 */

/**
 * standard constructor
 */
template< class tFactors > cHyperplaneData< tFactors >::cHyperplaneData():
		bUpdateContainedPoints( true ), pInequiation( NULL ){
	//nothing to do
}

/**
 * parameter constructor
 *
 * @param inInequiation the inequiation from which to create the hyperplane
 * @param uiDimensions the number of dimensions of the space for the hyperplane
 */
template< class tFactors > cHyperplaneData< tFactors >::cHyperplaneData(
		cInequationData< tFactors > & inInequiation, unsigned int uiDimensions ):
		bUpdateContainedPoints( true ),
		hyperplane( inInequiation.inequiation, uiDimensions ),
		pInequiation( &inInequiation ){
	//nothing to do
}


/**
 * destructor
 */
template< class tFactors > cHyperplaneData< tFactors >::~cHyperplaneData(){
	
#ifdef DEBUG_ADD_INEQUIATION
	cout<<"deleting hyperplane: "<<this<<endl;
	hyperplane.print( cout );
#endif //DEBUG_ADD_INEQUIATION
	//remove connections
	for ( typeItrSetPHyperplanes
			itrContainingHyperplane = setContainingHyperplanes.begin();
			itrContainingHyperplane != setContainingHyperplanes.end();
			itrContainingHyperplane++ ){
		
		(*itrContainingHyperplane)->setContainedHyperplanes.erase( this );
#ifdef DEBUG_ADD_INEQUIATION
		cout<<"disconnecting containing "<<(*itrContainingHyperplane)<<" from "<<this<<endl;
#endif //DEBUG_ADD_INEQUIATION
	}
	for ( typeItrSetPHyperplanes
			itrContainedHyperplane = setContainedHyperplanes.begin();
			itrContainedHyperplane != setContainedHyperplanes.end();
			itrContainedHyperplane++ ){
		
		(*itrContainedHyperplane)->setContainingHyperplanes.erase( this );
#ifdef DEBUG_ADD_INEQUIATION
		cout<<"disconnecting contained "<<(*itrContainedHyperplane)<<" from "<<this<<endl;
#endif //DEBUG_ADD_INEQUIATION
	}
	for ( typeItrSetPHyperplanes
			itrContainedPoint = setContainedPoints.begin();
			itrContainedPoint != setContainedPoints.end();
			itrContainedPoint++ ){
		
		(*itrContainedPoint)->setContainingBorders.erase( this );
#ifdef DEBUG_ADD_INEQUIATION
		cout<<"disconnecting contained border point "<<(*itrContainedPoint)<<" from "<<this<<endl;
#endif //DEBUG_ADD_INEQUIATION
	}
	for ( typeItrSetPHyperplanes
			itrContainingBorder = setContainingBorders.begin();
			itrContainingBorder != setContainingBorders.end();
			itrContainingBorder++ ){
			
		(*itrContainingBorder)->setContainedPoints.erase( this );
#ifdef DEBUG_ADD_INEQUIATION
		cout<<"disconnecting containing border "<<(*itrContainingBorder)<<" from "<<this<<endl;
#endif //DEBUG_ADD_INEQUIATION
	}
	if ( ( pInequiation != NULL ) && ( pInequiation->pHyperplane == this ) ){
		pInequiation->pHyperplane = NULL;
	}
}


/**
 * This method adds the given hyperplane (pointer) as a contained
 * hyperplane. It will also add the pointer to this hyperplane as
 * the containing hyperplane in the given hyperplane
 * pContainedHyperplane.
 * @see setContainedHyperplanes and @see setContainingHyperplanes
 *
 * @param pContainedHyperplane a pointer to the hyperplane to add as
 * 	the contained hyperplane
 */
template< class tFactors > void cHyperplaneData< tFactors >::
		addContainedHyperplane( cHyperplaneData< tFactors > * pContainedHyperplane ){
	
	if ( pContainedHyperplane == NULL ){
		//nothing to add
		return;
	}
#ifdef DEBUG_ADD_INEQUIATION
	cout<<"making connection from "<<this<<" containing "<<pContainedHyperplane<<endl;
	cout<<"this is:"<<endl;
	hyperplane.print( cout );
	cout<<"the contained is:"<<endl;
	pContainedHyperplane->hyperplane.print( cout );
	cout<<endl;
#endif //DEBUG_ADD_INEQUIATION
	setContainedHyperplanes.insert( pContainedHyperplane );
	pContainedHyperplane->setContainingHyperplanes.insert( this );
	
	bUpdateContainedPoints = true;
}


/**
 * @return if the given hyperplane is part of this hyperplane true,
 * 	else false; @see setContainedHyperplanes
 */
template< class tFactors > bool cHyperplaneData< tFactors >::
		isPart( const cHyperplaneData< tFactors > * pHyperplane ){
	
#ifdef DEBUG_ADD_INEQUIATION
	cout<<"cHyperplaneData< tFactors >("<<this<<")::isPart( pHyperplane="<<pHyperplane<<" ) started"<<endl;
#endif //DEBUG_ADD_INEQUIATION
	/*evalue all contained hyperplanes till the dimensionality of
	pHyperplane is reached (contained hyperplanes have a increased with one
	dimensionality)*/
	const unsigned int uiDimensionalityHyperplane =
		pHyperplane->hyperplane.getNumberOfDirections();
	
	if ( (uiDimensionalityHyperplane == 0) && setContainingHyperplanes.empty() &&
			( ! bUpdateContainedPoints ) ){
		//this is a border hyperplane and its contained points a searched for
		
#ifdef DEBUG_ADD_INEQUIATION
		cout<<"searching in setContainedPoints ( size="<<
			setContainedPoints.size()<<" ) is "<<( ( ( setContainedPoints.find(
			const_cast< cHyperplaneData< tFactors > * >( pHyperplane) ) !=
			setContainedPoints.end() ) )?"true":"false")<<endl;
#endif //DEBUG_ADD_INEQUIATION
		//TODO why i need const_cast??
		return ( setContainedPoints.find( const_cast< cHyperplaneData< tFactors > * >(
			pHyperplane ) ) != setContainedPoints.end() );
	}
	const unsigned int uiDimensionalityThis =
		hyperplane.getNumberOfDirections();
	
	if ( uiDimensionalityThis < uiDimensionalityHyperplane ){
		/*a hyperplane with higher dimensionality as this, can never be a
		part of this hyperplane*/
#ifdef DEBUG_ADD_INEQUIATION
		cout<<"uiDimensionalityThis < uiDimensionalityHyperplane"<<endl;
#endif //DEBUG_ADD_INEQUIATION
		return false;
	}
	
	if ( uiDimensionalityThis == uiDimensionalityHyperplane ){
		/*the hyperplane and this hyperplane have the same dimensionality
		-> the given hyperplane is only part of this if it is this*/
#ifdef DEBUG_ADD_INEQUIATION
		cout<<"uiDimensionalityThis == uiDimensionalityHyperplane"<<endl;
#endif //DEBUG_ADD_INEQUIATION
		if ( this == pHyperplane ){
#ifdef DEBUG_ADD_INEQUIATION
			cout<<"this == pHyperplane"<<endl;
#endif //DEBUG_ADD_INEQUIATION
			return true;
		}//else
		return false;
	}
	
#ifdef DEBUG_ADD_INEQUIATION
	cout<<"evaluing the hyperplanes, uiDimensionalityThis="<<
		uiDimensionalityThis<<"  uiDimensionalityHyperplane="<<uiDimensionalityHyperplane<<endl;
#endif //DEBUG_ADD_INEQUIATION
	typeSetPHyperplanes setActualContained =
		setContainedHyperplanes;
	
	typeSetPHyperplanes setNextContained;
	
	for ( unsigned int uiActualDimensionality = uiDimensionalityThis - 1;
			uiDimensionalityHyperplane < uiActualDimensionality;
			uiActualDimensionality--  ){
		
		for ( typeItrSetPHyperplanes
				itrContainedHyperplane = setActualContained.begin();
				itrContainedHyperplane != setActualContained.end();
				itrContainedHyperplane++ ){
			
			setNextContained.insert(
				(*itrContainedHyperplane)->setContainedHyperplanes.begin(),
				(*itrContainedHyperplane)->setContainedHyperplanes.end() );
		}
		setActualContained = setNextContained;
		setNextContained.clear();
	}
	
	if ( ( uiDimensionalityHyperplane == 0 ) && setContainingHyperplanes.empty() ){
#ifdef DEBUG_ADD_INEQUIATION
		cout<<"storing evalued hyperplanes as border points"<<endl;
#endif //DEBUG_ADD_INEQUIATION
		/*the evalued setActualContained are all point hyperplanes contained
		in this border hyperplane*/
		setContainedPoints = setActualContained;
		bUpdateContainedPoints = false;
		
		//register this border hyperplane at the points
		for ( typeItrSetPHyperplanes
				itrContainedHyperplane = setContainedPoints.begin();
				itrContainedHyperplane != setContainedPoints.end();
				itrContainedHyperplane++ ){
			
			(*itrContainedHyperplane)->setContainingBorders.insert( this );
		}
	}
#ifdef DEBUG_ADD_INEQUIATION
	cout<<"evalued setActualContained "<<setActualContained.size()<<endl;
#endif //DEBUG_ADD_INEQUIATION
	//TODO why i need const_cast??
	return ( setActualContained.find( const_cast< cHyperplaneData< tFactors > * >(
		pHyperplane ) ) != setActualContained.end() );
}


//end cHyperplaneData


/**
 * methods for the @class cInequationData
 * The data for a inequiation.
 */

/**
 * standardconstructor
 */
template< class tFactors > cInequationData< tFactors >::cInequationData():
		pHyperplane( NULL ){
	//nothing to do
}


/**
 * parameterconstructor
 *
 * @param inInequiation the inequiation for the inequiation data
 * @param pInHyperplane the pointer to the hyperplane for the inequiation
 */
template< class tFactors > cInequationData< tFactors >::cInequationData(
		const cInequation< tFactors > & inInequiation,
		cHyperplaneData< tFactors > * pInHyperplane ):
		inequiation( inInequiation ), pHyperplane( pInHyperplane ){
	//nothing to do
}


/**
 * destructor
 */
template< class tFactors > cInequationData< tFactors >::~cInequationData(){
	//remove connections
	if ( ( pHyperplane != NULL ) && ( pHyperplane->pInequiation == this ) ){
		pHyperplane->pInequiation = NULL;
	}
}

//end cInequationData


/**
 * methods for the @class cHyperplaneBodyFull
 */


/**
 * standardconstructor
 *
 * @param uiInDimensions the dimensions of the space for the hyperbody;
 * 	all added inequiations should have this much factors
 * 	@see uiDimensions
 * @param maxValue the maximum possible value in all directions
 * 	the evalued hyperbody will allways inside a hypercubus of all
 * 	vectors = (x_0,..., x_uiDimensions)^T, with
 * 	-1 * maxValue <= x_i <= maxValue for 0 <= i <= uiDimensions
 */
template< class tFactors > cHyperplaneBodyFull<tFactors>::cHyperplaneBodyFull(
		unsigned int uiInDimensions, const tFactors maxValue ):
			cHyperplaneBody<tFactors>( uiInDimensions ),
			vecBorders( uiInDimensions, list< cHyperplaneData< tFactors > * >() ){
	
	if ( this->uiDimensions == 0 ){
		//nothing to create
		return;
	}
	if ( maxValue == ((tFactors)(0)) ){
		//nothing to create
		return;
	}
	/*for 0 <= i <= uiDimensions create inequiations with ther hyperplanes:
		maxValue <= x_i
		maxValue <= -1 * x_i
		(all factors not shown are 0)*/
	const tFactors negMaxValue = ((tFactors)(-1)) * maxValue;
	
	for ( unsigned int uiActualDimension = 0; uiActualDimension < this->uiDimensions;
			uiActualDimension++ ){
		
		cHyperplaneData< tFactors > * pHyperplaneData1 =
			new cHyperplaneData< tFactors >();
		
		cInequationData< tFactors > * pInequiationData1 =
			new cInequationData< tFactors >();
		pInequiationData1->inequiation.constant = negMaxValue;
		pInequiationData1->inequiation.vecFactors =
			vector< tFactors >( this->uiDimensions , ((tFactors)(0)) );
		//create: maxValue <= x_i
		pInequiationData1->inequiation.vecFactors[ uiActualDimension ] =
			((tFactors)(1));
		
		pHyperplaneData1->hyperplane = cHyperplane< tFactors >(
			pInequiationData1->inequiation, this->uiDimensions );
		
		pInequiationData1->pHyperplane = pHyperplaneData1;
		pHyperplaneData1->pInequiation = pInequiationData1;
		
		liInequiations.push_back( pInequiationData1 );
		vecBorders[ this->uiDimensions - 1 ].push_back( pHyperplaneData1 );
		
		//create: maxValue <= -1 * x_i
		cHyperplaneData< tFactors > * pHyperplaneData2 =
			new cHyperplaneData< tFactors >();
		cInequationData< tFactors > * pInequiationData2 =
			new cInequationData< tFactors >();
		pInequiationData2->inequiation.constant = negMaxValue;
		pInequiationData2->inequiation.vecFactors =
			vector< tFactors >( this->uiDimensions , ((tFactors)(0)) );
		pInequiationData2->inequiation.vecFactors[ uiActualDimension ] =
			((tFactors)(-1));
		
		pHyperplaneData2->hyperplane = cHyperplane< tFactors >(
			pInequiationData2->inequiation, this->uiDimensions );
		
		pInequiationData2->pHyperplane = pHyperplaneData2;
		pHyperplaneData2->pInequiation = pInequiationData2;
		
		liInequiations.push_back( pInequiationData2 );
		vecBorders[ this->uiDimensions - 1 ].push_back( pHyperplaneData2 );
	}
	
	if ( this->uiDimensions == 1 ){
		//can't intersect border points
		return;
	}
	/*for dimensionality this->uiDimensions - 2 create the intersections of all
	hyperplanes of dimensionality this->uiDimensions - 1*/
	list< cHyperplaneData< tFactors > * > liNewHyperplanes;
	for ( typename list< cHyperplaneData< tFactors > * >::iterator
			itrFirstHyperplane = vecBorders[ this->uiDimensions - 1 ].begin();
			itrFirstHyperplane != vecBorders[ this->uiDimensions - 1 ].end();
			itrFirstHyperplane++ ){
		
		typename list< cHyperplaneData< tFactors > * >::iterator
			itrSecondHyperplane = itrFirstHyperplane;
		itrSecondHyperplane++;
		
		for ( ; itrSecondHyperplane != vecBorders[ this->uiDimensions - 1 ].end();
				itrSecondHyperplane++ ){
			
			cHyperplane< tFactors > * pIntersection =
				(*itrFirstHyperplane)->hyperplane.evalueIntersection(
					(*itrSecondHyperplane)->hyperplane );
			
			if ( pIntersection == NULL ){
				//no intersection -> nothing to add
				continue;
			}
			cHyperplaneData< tFactors > * pIntersectionHyperplane =
				new cHyperplaneData< tFactors >();
			
			pIntersectionHyperplane->hyperplane = *pIntersection;
			delete pIntersection;
			
			(*itrFirstHyperplane)->addContainedHyperplane( pIntersectionHyperplane );
			(*itrSecondHyperplane)->addContainedHyperplane( pIntersectionHyperplane );
			
			liNewHyperplanes.push_back( pIntersectionHyperplane );
			
			vecBorders[ this->uiDimensions - 2 ].push_back( pIntersectionHyperplane );
		}
	}

	/*for dimensionality = this->uiDimensions - 3, ..., 0 create the intersections
	of all hyperplanes of dimensionality dimensionality - 1;
	yust create intersections of hyperplanes of dimensionality which are
	contained one one hyperplane of dimensionality + 1*/
	for ( unsigned int uiDimensionality = (this->uiDimensions - 2);
			1 <= uiDimensionality; uiDimensionality-- ){
		
		liNewHyperplanes = addIntersectionsFor( liNewHyperplanes, uiDimensionality );
	}//end for uiDimensionality
}


/**
 * copy constructor
 *
 * @param hyperplaneBody the body to copy
 */
template< class tFactors > cHyperplaneBodyFull<tFactors>::cHyperplaneBodyFull(
		const cHyperplaneBodyFull< tFactors > & hyperplaneBody ):
		cHyperplaneBody<tFactors>( hyperplaneBody.uiDimensions ),
		vecBorders( hyperplaneBody.uiDimensions, list< cHyperplaneData< tFactors > * >() ){
	
#ifdef DEBUG_COPY_CONSTRUCTOR
	cout<<"cHyperplaneBodyFull<tFactors>::cHyperplaneBodyFull( hyperplaneBody ) started copying:"<<endl<<flush;
	hyperplaneBody.print( cout );
#endif //DEBUG_COPY_CONSTRUCTOR
	//data to relink the pointers
	map< cHyperplaneData< tFactors > *, cHyperplaneData< tFactors > * >
		mapHyperplaneMapping;
	map< cInequationData< tFactors > *, cInequationData< tFactors > * >
		mapInequiationMapping;
	
	mapHyperplaneMapping.insert( pair< cHyperplaneData< tFactors > *,
		cHyperplaneData< tFactors > * >( NULL, NULL ) );
	mapInequiationMapping.insert( pair< cInequationData< tFactors > *,
		cInequationData< tFactors > * >( NULL, NULL ) );
	
	for ( unsigned int uiDimension = 0; uiDimension < this->uiDimensions;
			uiDimension++ ){

#ifdef DEBUG_COPY_CONSTRUCTOR
		cout<<"copying hyperplanes with dimensionality "<<uiDimension<<endl<<flush;
#endif //DEBUG_COPY_CONSTRUCTOR
		for ( typename list< cHyperplaneData< tFactors > * >::const_iterator
				itrHyperplanes = hyperplaneBody.vecBorders[ uiDimension  ].begin();
				itrHyperplanes != hyperplaneBody.vecBorders[ uiDimension  ].end();
				itrHyperplanes++ ){
			
			cHyperplaneData< tFactors >  * pHyperplaneCopy =
				new cHyperplaneData< tFactors >();
			pHyperplaneCopy->hyperplane = (*itrHyperplanes)->hyperplane;
			
			mapHyperplaneMapping.insert( pair< cHyperplaneData< tFactors > *,
				cHyperplaneData< tFactors > * >( *itrHyperplanes, pHyperplaneCopy ) );
			
			vecBorders[ uiDimension ].push_back( pHyperplaneCopy );
		}
	}
	
#ifdef DEBUG_COPY_CONSTRUCTOR
	cout<<"copying inequiations "<<endl<<flush;
#endif //DEBUG_COPY_CONSTRUCTOR
	for ( typename list< cInequationData< tFactors > * >::const_iterator
			itrInequiation = hyperplaneBody.liInequiations.begin();
			itrInequiation != hyperplaneBody.liInequiations.end();
			itrInequiation++ ){
		
		cInequationData< tFactors > * pInequiationCopy =
			new cInequationData< tFactors >( **itrInequiation );
		mapInequiationMapping.insert( pair< cInequationData< tFactors > *,
			cInequationData< tFactors > * >( *itrInequiation, pInequiationCopy ) );
		
		pInequiationCopy->pHyperplane = mapHyperplaneMapping[
			(*itrInequiation)->pHyperplane ];
		liInequiations.push_back( pInequiationCopy );
	}
	mapHyperplaneMapping.erase( NULL );
	
#ifdef DEBUG_COPY_CONSTRUCTOR
	cout<<"relink the hyperplane pointers "<<endl<<flush;
#endif //DEBUG_COPY_CONSTRUCTOR
	//relink the hyperplane pointers
	for ( typename map< cHyperplaneData< tFactors > *, cHyperplaneData< tFactors > * >::iterator
			itrHyperplane = mapHyperplaneMapping.begin();
			itrHyperplane != mapHyperplaneMapping.end(); itrHyperplane++ ){
		
		const cHyperplaneData< tFactors > * pFirstHyperplane = itrHyperplane->first;
		cHyperplaneData< tFactors > * pSecondHyperplane = itrHyperplane->second;

		for ( typename cHyperplaneData< tFactors >::typeSetPHyperplanes::const_iterator
				itrContainingHyperplane = pFirstHyperplane->setContainingHyperplanes.begin();
				itrContainingHyperplane != pFirstHyperplane->setContainingHyperplanes.end();
				itrContainingHyperplane++ ){
			
			pSecondHyperplane->setContainingHyperplanes.insert(
				mapHyperplaneMapping[ *itrContainingHyperplane ] );
		}
		for ( typename cHyperplaneData< tFactors >::typeSetPHyperplanes::const_iterator
				itrContainedHyperplane = pFirstHyperplane->setContainedHyperplanes.begin();
				itrContainedHyperplane != pFirstHyperplane->setContainedHyperplanes.end();
				itrContainedHyperplane++ ){
			
			pSecondHyperplane->setContainedHyperplanes.insert(
				mapHyperplaneMapping[ *itrContainedHyperplane ] );
		}
		pSecondHyperplane->pInequiation =
			mapInequiationMapping[ pFirstHyperplane->pInequiation ];
	}
#ifdef DEBUG_COPY_CONSTRUCTOR
	cout<<"cHyperplaneBodyFull<tFactors>::cHyperplaneBodyFull( hyperplaneBody ) done; this:"<<endl<<flush;
	print( cout );
#endif //DEBUG_COPY_CONSTRUCTOR
}


/**
 * standard destructor
 */
template< class tFactors > cHyperplaneBodyFull<tFactors>::~cHyperplaneBodyFull(){
	
	//delete hyperplanes
	for ( typename vector< list< cHyperplaneData< tFactors > * > >::iterator
			itrDimHyperplanes = vecBorders.begin();
			itrDimHyperplanes != vecBorders.end(); itrDimHyperplanes++ ){
		
		while ( ! itrDimHyperplanes->empty() ){
			
			delete itrDimHyperplanes->back();
			itrDimHyperplanes->pop_back();
		}
	}
	//delete inequiations
	while ( ! liInequiations.empty() ){
		delete liInequiations.back();
		liInequiations.pop_back();
	}
}


/**
 * With this method the hyperplane body can be restricted by the given
 * inequiation, if the inequiation dosn't remove the body.
 * If ther are points in this hyperplane body exists wich fulfill the
 * inequiation, an hyperplane for the inequiation is created and added
 * to this hyperplane body.
 * 
 * @see addInequiations()
 * @see cInequation
 * @see cInequation::cHyperplane( const cInequation & inequation )
 *
 * @return if true this body was restricted by the given inequiation,
 * 	else the inequiation would remove this body
 */
template< class tFactors > bool cHyperplaneBodyFull<tFactors>::addInequiation(
		const cInequation< tFactors > & inequiation ){
	
#ifdef DEBUG_ADD_INEQUIATION
	cout<<"cHyperplaneBodyFull<tFactors>::addInequiation( inequiation ) started"<<endl;
	cout<<"inequiation:";
	inequiation.print( cout );
	cout<<endl;
#endif //DEBUG_ADD_INEQUIATION

	if ( this->uiDimensions == 0 ){
		//nothing to create
		return false;
	}
	if ( inequiation.isTrue() ){
		//the inequiation cuts nothing from the body
		return true;
	}
	if ( inequiation.isFalse() ){
		//the inequiation removes the body
		return false;
	}
	/*check if non, some or all border points of the body ( vecBorders[ 0 ] )
	fullfill the given inequiation*/
	bool bSomeFulfill = false;;
	bool bSomeNotFulfill = false;;
	
#ifdef DEBUG_ADD_INEQUIATION
	cout<<"checking border points"<<endl;
#endif //DEBUG_ADD_INEQUIATION
	list< cHyperplaneData< tFactors > * > & liBorderOfDimensionality0 =
		vecBorders[ 0 ];
	for  ( typename list< cHyperplaneData< tFactors > * >::iterator
			itrBorderPoint = liBorderOfDimensionality0.begin();
			itrBorderPoint != liBorderOfDimensionality0.end(); itrBorderPoint++ ){
		
		if ( inequiation.evalue( (*itrBorderPoint)->hyperplane.getBase() ) ){
			//this border point fulfill the ineqiation
			bSomeFulfill = true;
			if ( bSomeNotFulfill ){
				//bSomeFulfill == bSomeNotFulfill == true -> done
				break;
			}
		}else{//this border point dosn't fulfill the ineqiation
			bSomeNotFulfill = true;
			if ( bSomeFulfill ){
				//bSomeFulfill == bSomeNotFulfill == true -> done
				break;
			}
		}
	}
	
	if ( ! bSomeFulfill ){
		/*if non border points fulfill the inequiation
		-> the inequiation will remove the body
		-> return false*/
		
#ifdef DEBUG_ADD_INEQUIATION
		cout<<"if non border points fulfill the inequiation "<<endl;
#endif //DEBUG_ADD_INEQUIATION
		return false;
	}//else
	
	if ( ! bSomeNotFulfill ){
		/*if all border points fulfill the inequiation
		-> the inequiation won't change the body
		-> return true*/
		
#ifdef DEBUG_ADD_INEQUIATION
		cout<<"if all border points fulfill the inequiation "<<endl;
#endif //DEBUG_ADD_INEQUIATION
		return true;
	}/*else if some border points of the body ( vecBorders[ 0 ] ) fullfill the
	given inequiation some not -> the inequiation change the body*/
	
	list< cHyperplaneData< tFactors > * > & liBorderOfDimensionalityMax =
		vecBorders[ this->uiDimensions - 1 ];
	/*create the hyperplane H for the inequiation and
	add the hyperplane h to the body*/
	liInequiations.push_back( new cInequationData< tFactors >( inequiation ) );
	
	liBorderOfDimensionalityMax.push_back(
		new cHyperplaneData< tFactors >( *(liInequiations.back()), this->uiDimensions ) );
	cHyperplaneData< tFactors > & hyperplaneInequiation =
		*(liBorderOfDimensionalityMax.back());
		
	liInequiations.back()->pHyperplane = & hyperplaneInequiation;
	
	list< cHyperplaneData< tFactors > * > liNewHyperplanes;
	if ( this->uiDimensions != 1 ){
	
		/*evalue all intersection hyperplanes Hi of the hyperplane H and all
		hyperplanes of dimensionality this->uiDimensions - 1 ( vecBorders[ vecBorders.size() ] )*/
		//iterator to the inserted inequiation hyperplane
		typename list< cHyperplaneData< tFactors > * >::const_iterator
			itrInequiationHyperplane = liBorderOfDimensionalityMax.end();
		itrInequiationHyperplane--;
		
		for ( typename list< cHyperplaneData< tFactors > * >::iterator
				itrHyperplane = liBorderOfDimensionalityMax.begin();
				itrHyperplane != itrInequiationHyperplane; itrHyperplane++ ){
			
			cHyperplane< tFactors > * pIntersection =
				hyperplaneInequiation.hyperplane.evalueIntersection(
					(*itrHyperplane)->hyperplane );
			
			if ( pIntersection == NULL ){
				//no intersection -> nothing to add
				continue;
			}
			if ( pIntersection->getNumberOfDirections() == (this->uiDimensions - 1) ){
				/*if intersection hyperplanes Hi of dimensionality this->uiDimensions - 1 exists
				-> hyperplane h is equal to an other hyperplane
				-> the inequiations are different and ther normal vectors are opposed
					(the new inequiation removes some border points from the body
					that the equal hyperplane dos not (see liPointNotFulfillInequiation) )
						-> remove Hi from the to check intersections and continue (
						the body will be restriced later, when the border points are removed)
				*/
				delete pIntersection;
				continue;
			}
			
			/*check if the Hyperplane, which created the intersection, contains
			allready an equal hyperplane
				- if yes: discard actual intersection and add the hyperplane H
					to its containing hyperplanes
				- if no: add the hyperplane to the body and to check hyperplanes,
					add the contained and containig hyperplanes*/
			bool bEqualHyperlaneExsists = false;
			for ( typename cHyperplaneData< tFactors >::typeItrSetPHyperplanes
					itrContainedHyperplane = (*itrHyperplane)->setContainedHyperplanes.begin();
					itrContainedHyperplane != (*itrHyperplane)->setContainedHyperplanes.end();
					itrContainedHyperplane++ ){
				
				if ( pIntersection->equal( (*itrContainedHyperplane)->hyperplane ) ){
					/*discard actual intersection and add the hyperplane H
					to its containing hyperplanes*/
					bEqualHyperlaneExsists = true;
					
					hyperplaneInequiation.addContainedHyperplane( *itrContainedHyperplane );
				}
			}//end for itrContainedHyperplane
			if ( bEqualHyperlaneExsists ){
				/*discard actual intersection and add the hyperplane H
				to its containing hyperplanes*/
				delete pIntersection;
				continue;
			}
			for ( typename cHyperplaneData< tFactors >::typeItrSetPHyperplanes
					itrContainedHyperplane = hyperplaneInequiation.setContainedHyperplanes.begin();
					itrContainedHyperplane != hyperplaneInequiation.setContainedHyperplanes.end();
					itrContainedHyperplane++ ){
				
				if ( pIntersection->equal( (*itrContainedHyperplane)->hyperplane ) ){
					/*discard actual intersection and add the hyperplane H
					to its containing hyperplanes*/
					bEqualHyperlaneExsists = true;
					
					(*itrHyperplane)->addContainedHyperplane( *itrContainedHyperplane );
				}
			}//end for itrContainedHyperplane
			if ( bEqualHyperlaneExsists ){
				/*discard actual intersection and add the hyperplane H
				to its containing hyperplanes*/
				delete pIntersection;
				continue;
			}/*else add the hyperplane to the body and to check hyperplanes,
			add the contained and containig hyperplanes*/
	
			cHyperplaneData< tFactors > * pIntersectionHyperplane =
				new cHyperplaneData< tFactors >();
			
			pIntersectionHyperplane->hyperplane = *pIntersection;
			delete pIntersection;
			
			(*itrHyperplane)->addContainedHyperplane( pIntersectionHyperplane );
			hyperplaneInequiation.addContainedHyperplane( pIntersectionHyperplane );
			
			liNewHyperplanes.push_back( pIntersectionHyperplane );
			vecBorders[ this->uiDimensions - 2 ].push_back( pIntersectionHyperplane );
		}
		/*for dimensionality = this->uiDimensions - 3, ..., 0 create the intersections
		of all hyperplanes of dimensionality dimensionality - 1;
		yust create intersections of hyperplanes of dimensionality which are
		contained one one hyperplane of dimensionality + 1*/
		for ( unsigned int uiDimensionality = (this->uiDimensions - 2);
				1 <= uiDimensionality; uiDimensionality-- ){
			
			liNewHyperplanes = addIntersectionsFor( liNewHyperplanes, uiDimensionality );
		}//end for uiDimensionality
	}/*end if ( this->uiDimensions != 1 )
	else if ( this->uiDimensions == 1 )
	-> the intersection represents allready a border point
	-> it has no intersections*/


#ifdef DEBUG_ADD_INEQUIATION
	cout<<"befor removing: "<<endl;
	print( cout );
#endif //DEBUG_ADD_INEQUIATION
	/*for all points on the hyperplane h (they are contained in
	liNewHyperplanes), check if they are in the body:
		for every new point to check/new hyperplane, check if it fulfills all inequiations*/
	//iterator to the inserted inequiation
	typename list< cInequationData< tFactors > * >::iterator
		itrAddedInequiation = liInequiations.end();
	itrAddedInequiation--;
	
#ifdef DEBUG_ADD_INEQUIATION
	cout<<"removing not needed new"<<endl<<flush;
#endif //DEBUG_ADD_INEQUIATION
	while ( ! liNewHyperplanes.empty() ){
		
		bool bBorderPointOutside = false;
		const cHyperplaneData< tFactors > * pActualHyperplane =
			liNewHyperplanes.back();
		const vector< tFactors > vecBorderPoint =
			pActualHyperplane->hyperplane.getBase();

#ifdef DEBUG_ADD_INEQUIATION
		cout<<"checking to remove: "<<flush;
		nHyperplaneBodyFull::nDebug::printVector( cout, vecBorderPoint );
#endif //DEBUG_ADD_INEQUIATION
		for ( typename list< cInequationData< tFactors > * >::iterator
				itrInequiation = liInequiations.begin();
				itrInequiation != itrAddedInequiation; itrInequiation++ ){
			
			if ( ! ( (*itrInequiation)->inequiation.evalue( vecBorderPoint ) ) ){
				//border point is not in the body -> delete it?
#ifdef DEBUG_ADD_INEQUIATION
				cout<<"outside bounderies: ";
				nHyperplaneBodyFull::nDebug::printVector( cout, vecBorderPoint );
				cout<<"  inequiation: ";
				(*itrInequiation)->inequiation.print( cout );
#endif //DEBUG_ADD_INEQUIATION
				if ( ! (*itrInequiation)->pHyperplane->isPart( pActualHyperplane ) ){
					//the point dosn't lay on the hyperplane for the inequiation -> delete it
#ifdef DEBUG_ADD_INEQUIATION
					cout<<"mark to removing: ";
					nHyperplaneBodyFull::nDebug::printVector( cout, vecBorderPoint );
#endif //DEBUG_ADD_INEQUIATION
					bBorderPointOutside = true;
					break;
				}
			}
		}
		if ( bBorderPointOutside ){
			//remove the border point
			for  ( typename list< cHyperplaneData< tFactors > * >::reverse_iterator
					itrBorderPoint = liBorderOfDimensionality0.rbegin();
					itrBorderPoint != liBorderOfDimensionality0.rend();
					itrBorderPoint++ ){
				
				if ( (*itrBorderPoint) == pActualHyperplane ){
					
					typename list< cHyperplaneData< tFactors > * >::iterator
						itrBorderPointOrg = itrBorderPoint.base();
					itrBorderPointOrg--;
#ifdef DEBUG_ADD_INEQUIATION
					cout<<"removing1: ";
					nHyperplaneBodyFull::nDebug::printVector( cout, (*itrBorderPoint)->hyperplane.getBase() );
#endif //DEBUG_ADD_INEQUIATION
					delete * itrBorderPointOrg;
					liBorderOfDimensionality0.erase( itrBorderPointOrg );
					break;
				}
			}
		}
		liNewHyperplanes.pop_back();
	}
	
	//remove all border points vecBorders[ 0 ], which dosn't fulfill the inequiation
	for  ( typename list< cHyperplaneData< tFactors > * >::iterator
			itrBorderPoint = liBorderOfDimensionality0.begin();
			itrBorderPoint != liBorderOfDimensionality0.end(); ){
		
		if ( ! inequiation.evalue( (*itrBorderPoint)->hyperplane.getBase() ) ){
			//this border point dosn't fulfill the ineqiation -> erase it
#ifdef DEBUG_ADD_INEQUIATION
			cout<<"outside bounderies2: ";
			nHyperplaneBodyFull::nDebug::printVector( cout, (*itrBorderPoint)->hyperplane.getBase() );
#endif //DEBUG_ADD_INEQUIATION
			if ( ! hyperplaneInequiation.isPart( *itrBorderPoint ) ){
				//the point dosn't lay on the hyperplane for the inequiation -> delete it
#ifdef DEBUG_ADD_INEQUIATION
				cout<<"removing2: ";
				nHyperplaneBodyFull::nDebug::printVector( cout, (*itrBorderPoint)->hyperplane.getBase() );
#endif //DEBUG_ADD_INEQUIATION
				delete * itrBorderPoint;
				itrBorderPoint = liBorderOfDimensionality0.erase( itrBorderPoint );
			}else{//don't cut points which lay on the hyperplane to the inequiation
				itrBorderPoint++;
			}
		}else{
			itrBorderPoint++;
		}
	}
	
#ifdef DEBUG_ADD_INEQUIATION
	cout<<"after removing points: "<<endl;
	print( cout );
#endif //DEBUG_ADD_INEQUIATION
	/*remove all border hyperplanes of dimensionality greater 0 (all except
	points), which dosn't dosn't contain other border hyperplanes*/
//TODO
//#define REMOVE_NOT_BORDER_PLANES
#ifdef REMOVE_NOT_BORDER_PLANES

#ifdef TODO_REMOVE_NOT_BORDER_PLANES
	/*the vecBorders index of the hyperplanes with the maximum
	dimensionality (the top most hyperplanes)*/
	const unsigned int uiTopMostHyperplaneLayer = this->uiDimensions - 1;
	//for dimensionality 1 to dimensions - 2
	for ( unsigned int uiDimensionality = 1;
			uiDimensionality < uiTopMostHyperplaneLayer; uiDimensionality++ ){
		
		list< cHyperplaneData< tFactors > * > & liBorderOfActualDimensionality =
			vecBorders[ uiDimensionality ];
		
		for  ( typename list< cHyperplaneData< tFactors > * >::iterator
				itrBorderHyperplane = liBorderOfActualDimensionality.begin();
				itrBorderHyperplane != liBorderOfActualDimensionality.end(); ){
			
			/*remove all hyperplanes wich have less than ther dimensionality + 1
			sub hyperplanes, because they don't restrict the hyper body;
			if the border hyperplane isn't a hyperplane with top most
			dimensionality and it is not contained in at last two hyperplanes,
			it can't be an intersection hyperplane so remove it */
//TODO switch			if ( ( (*itrBorderHyperplane)->setContainedHyperplanes.size() <= uiDimensionality ) ||
//					( (*itrBorderHyperplane)->setContainingHyperplanes.size() < 2 ) ){
			if ( ( (*itrBorderHyperplane)->setContainedHyperplanes.empty() ) ){
				
#ifdef DEBUG_ADD_INEQUIATION
				cout<<"removing hyperplane (containing "<<(*itrBorderHyperplane)->setContainedHyperplanes.size()<<
					" hyperplanes, is contained in "<<(*itrBorderHyperplane)->setContainingHyperplanes.size()<<")"<<endl;
				(*itrBorderHyperplane)->hyperplane.print( cout );
#endif //DEBUG_ADD_INEQUIATION
				delete *itrBorderHyperplane;
				itrBorderHyperplane = liBorderOfActualDimensionality.erase(
					itrBorderHyperplane );
				
			}else{
				itrBorderHyperplane++;
			}
		}
	}
	{//removing hyperplanes of maximum dimensionality
		list< cHyperplaneData< tFactors > * > & liBorderOfActualDimensionality =
			vecBorders[ uiTopMostHyperplaneLayer ];
	
		for  ( typename list< cHyperplaneData< tFactors > * >::iterator
				itrBorderHyperplane = liBorderOfActualDimensionality.begin();
				itrBorderHyperplane != liBorderOfActualDimensionality.end(); ){
			
			/*remove all hyperplanes wich have less than ther dimensionality + 1
			sub hyperplanes, because they don't restrict the hyper body*/
//TODO switch			if ( (*itrBorderHyperplane)->setContainedHyperplanes.size() <= uiTopMostHyperplaneLayer ){
			if ( (*itrBorderHyperplane)->setContainedHyperplanes.empty() ){
				
				const cInequationData< tFactors > * pInequiationToErase =
					(*itrBorderHyperplane)->pInequiation;
				if ( pInequiationToErase != NULL ){
					//erase the inequiation for the hyperplane
					for  ( typename list< cInequationData< tFactors > * >::iterator
							itrInequiation = liInequiations.begin();
							itrInequiation != liInequiations.end();
							itrInequiation++ ){
						
						if ( (*itrInequiation) == pInequiationToErase ){
							//inequiation for hyperplane found -> erase it
#ifdef DEBUG_ADD_INEQUIATION
							cout<<"removing inequiation"<<endl;
							(*itrInequiation)->inequiation.print( cout );
#endif //DEBUG_ADD_INEQUIATION
							delete *itrInequiation;
							liInequiations.erase( itrInequiation );
							break;
						}
					}
				}//end if hyperplane has inequiation
#ifdef DEBUG_ADD_INEQUIATION
				cout<<"removing hyperplane (containing "<<(*itrBorderHyperplane)->setContainedHyperplanes.size()<<" hyperplanes)"<<endl;
				(*itrBorderHyperplane)->hyperplane.print( cout );
#endif //DEBUG_ADD_INEQUIATION
				delete *itrBorderHyperplane;
				itrBorderHyperplane = liBorderOfActualDimensionality.erase(
					itrBorderHyperplane );
				
			}else{
				itrBorderHyperplane++;
			}
		}//end for itrBorderHyperplane
	}
#endif //TODO_REMOVE_NOT_BORDER_PLANES

	
	/*the vecBorders index of the hyperplanes with the maximum
	dimensionality (the top most hyperplanes)*/
	const unsigned int uiTopMostHyperplaneLayer = this->uiDimensions - 1;
	//for dimensionality 1 to dimensions - 2
	for ( unsigned int uiDimensionality = 1;
			uiDimensionality <= uiTopMostHyperplaneLayer; uiDimensionality++ ){
	
	if ( uiDimensionality != uiTopMostHyperplaneLayer ){
		
		list< cHyperplaneData< tFactors > * > & liBorderOfActualDimensionality =
			vecBorders[ uiDimensionality ];
		
		for  ( typename list< cHyperplaneData< tFactors > * >::iterator
				itrBorderHyperplane = liBorderOfActualDimensionality.begin();
				itrBorderHyperplane != liBorderOfActualDimensionality.end(); ){
			
			if ( (*itrBorderHyperplane)->setContainedHyperplanes.empty() ){
				
#ifdef DEBUG_ADD_INEQUIATION
				cout<<"removing hyperplane ( containing "<<(*itrBorderHyperplane)->setContainedHyperplanes.size()<<
					" hyperplanes, is contained in "<<(*itrBorderHyperplane)->setContainingHyperplanes.size()<<
					" and has dimensionality "<<uiDimensionality<<")"<<endl;
				(*itrBorderHyperplane)->hyperplane.print( cout );
#endif //DEBUG_ADD_INEQUIATION
				delete *itrBorderHyperplane;
				itrBorderHyperplane = liBorderOfActualDimensionality.erase(
					itrBorderHyperplane );
			}else{
				itrBorderHyperplane++;
			}
		}
	}else//TODO: why do I need this if ???
	{//removing hyperplanes of maximum dimensionality
		
		for  ( typename list< cHyperplaneData< tFactors > * >::iterator
				itrMaxBorderHyperplane = liBorderOfDimensionalityMax.begin();
				itrMaxBorderHyperplane != liBorderOfDimensionalityMax.end(); ){
			
//TODO switch			if ( (*itrMaxBorderHyperplane)->setContainedHyperplanes.size() < 2 ){
			if ( (*itrMaxBorderHyperplane)->setContainedHyperplanes.empty() ){
				
				const cInequationData< tFactors > * pInequiationToErase =
					(*itrMaxBorderHyperplane)->pInequiation;
				if ( pInequiationToErase != NULL ){
					//erase the inequiation for the hyperplane
					for  ( typename list< cInequationData< tFactors > * >::iterator
							itrInequiation = liInequiations.begin();
							itrInequiation != liInequiations.end();
							itrInequiation++ ){
						
						if ( (*itrInequiation) == pInequiationToErase ){
							//inequiation for hyperplane found -> erase it
#ifdef DEBUG_ADD_INEQUIATION
							cout<<"removing inequiation"<<endl;
							(*itrInequiation)->inequiation.print( cout );
#endif //DEBUG_ADD_INEQUIATION
							delete *itrInequiation;
							liInequiations.erase( itrInequiation );
							break;
						}
					}
				}//end if hyperplane has inequiation
#ifdef DEBUG_ADD_INEQUIATION
				cout<<"removing hyperplane (containing "<<(*itrMaxBorderHyperplane)->setContainedHyperplanes.size()<<" hyperplanes)"<<endl;
				(*itrMaxBorderHyperplane)->hyperplane.print( cout );
#endif //DEBUG_ADD_INEQUIATION
				delete *itrMaxBorderHyperplane;
				itrMaxBorderHyperplane = liBorderOfDimensionalityMax.erase(
					itrMaxBorderHyperplane );
			}else{
				itrMaxBorderHyperplane++;
			}
		}
	}
}


#else //REMOVE_NOT_BORDER_PLANES
	
	//for dimensionality 1 to dimensions - 1
	for ( unsigned int uiDimensionality = 1;
			uiDimensionality < this->uiDimensions; uiDimensionality++ ){
		
		list< cHyperplaneData< tFactors > * > & liBorderOfActualDimensionality =
			vecBorders[ uiDimensionality ];
		
		for  ( typename list< cHyperplaneData< tFactors > * >::iterator
				itrBorderHyperplane = liBorderOfActualDimensionality.begin();
				itrBorderHyperplane != liBorderOfActualDimensionality.end(); ){
			
			if ( (*itrBorderHyperplane)->setContainedHyperplanes.empty() ){
				
				const cInequationData< tFactors > * pInequiationToErase =
					(*itrBorderHyperplane)->pInequiation;
				if ( pInequiationToErase != NULL ){
					//erase the inequiation for the hyperplane
					for  ( typename list< cInequationData< tFactors > * >::iterator
							itrInequiation = liInequiations.begin();
							itrInequiation != liInequiations.end();
							itrInequiation++ ){
						
						if ( (*itrInequiation) == pInequiationToErase ){
							//inequiation for hyperplane found -> erase it
#ifdef DEBUG_ADD_INEQUIATION
							cout<<"removing inequiation"<<endl;
							(*itrInequiation)->inequiation.print( cout );
#endif //DEBUG_ADD_INEQUIATION
							delete *itrInequiation;
							liInequiations.erase( itrInequiation );
							break;
						}
					}
				}//end if hyperplane has inequiation
#ifdef DEBUG_ADD_INEQUIATION
				cout<<"removing hyperplane"<<endl;
				(*itrBorderHyperplane)->hyperplane.print( cout );
#endif //DEBUG_ADD_INEQUIATION
				delete *itrBorderHyperplane;
				itrBorderHyperplane = liBorderOfActualDimensionality.erase(
					itrBorderHyperplane );
			}else{
				itrBorderHyperplane++;
			}
		}
	}
#endif //REMOVE_NOT_BORDER_PLANES

#ifdef DEBUG_ADD_INEQUIATION
	cout<<endl<<"after removing hyperplanes: "<<endl;
	print( cout );
#endif //DEBUG_ADD_INEQUIATION
	
	return true;
}


/**
 * @return a vector with the borderpoints of the body
 */
template< class tFactors > unsigned long
		cHyperplaneBodyFull<tFactors>::getNumberOfBorderPoints() const{
	

	return ( vecBorders.empty() ? 0 :( vecBorders[ 0 ].size() ) );
}


/**
 * @return a vector with the borderpoints of the body
 */
template< class tFactors > vector< vector< tFactors > >
		cHyperplaneBodyFull<tFactors>::getBorderPoints() const{
	
	if ( vecBorders.empty() ){
		return vector< vector< tFactors > >();
	}
	vector< vector< tFactors > > vecBorderPoints( vecBorders[ 0 ].size() );
	
	size_t uiActualPoint = 0;
	for ( typename list< cHyperplaneData< tFactors > * >::const_iterator
			itrBorderPoint = vecBorders[ 0 ].begin();
			itrBorderPoint != vecBorders[ 0 ].end();
			itrBorderPoint++, uiActualPoint++ ){
		
		vecBorderPoints[ uiActualPoint ] = (*itrBorderPoint)->hyperplane.getBase();
	}
	return vecBorderPoints;
}


/**
 * This method checks if the given point is part of the hyperbody.
 * If the point is on one of the borders of the hyperbody or inside it,
 * it is part of the hyperbody.
 *
 * @param vecPoint the point to check
 * @return true if the point vecPoint is part of the hyperbody, else false
 */
template< class tFactors > bool cHyperplaneBodyFull<tFactors>::isPart(
		const vector< tFactors > & vecPoint ) const{
		
	//check if the point fullfill all inequiations of this hyperplane
	for ( typename list< cInequationData< tFactors > * >::const_iterator
			itrInequiation = liInequiations.begin();
			itrInequiation != liInequiations.end(); itrInequiation++ ){
		
		if ( ! (*itrInequiation)->inequiation.evalue( vecPoint ) ){
			//point dosn't fulfill the inequiation -> point not in body
			return false;
		}
	}//else point fulfill all inequiations -> point in body
	return true;
}


/**
 * This method print the hyperplane in a readebel form to the given
 * output stream outputSream.
 *
 * @param outputSream the stream wher to print this inequation to
 */
template< class tFactors > void cHyperplaneBodyFull<tFactors>::print(
		ostream & outputStream ) const{
	
	//print all inequiations for this body
	outputStream<<endl<<"Inequiations:"<<endl;
	for ( typename list< cInequationData< tFactors > * >::const_iterator
			itrInequiation = liInequiations.begin();
			itrInequiation != liInequiations.end(); itrInequiation++ ){
		
		(*itrInequiation)->inequiation.print( outputStream );
#ifdef DEBUG_NEEDED
			outputStream<<"   "<<(*itrInequiation)<<" for hyperplane "<<(*itrInequiation)->pHyperplane<<endl;
#endif//DEBUG_NEEDED
	}
	
	//print all hyperplanes with increasing dimensionality
	outputStream<<endl<<"Hyperplanes:"<<endl;
	const size_t uiNumberOfDimensions = vecBorders.size();
	
	for ( size_t uiActualDimensionality = 0;
			uiActualDimensionality < uiNumberOfDimensions;
			uiActualDimensionality++ ){
		
		outputStream<<endl<<"Hyperplanes of dimensionality "<<
			uiActualDimensionality<<" :"<<endl;
	
		for ( typename list< cHyperplaneData< tFactors > * >::const_iterator
				itrHyperplane = vecBorders[ uiActualDimensionality ].begin();
				itrHyperplane != vecBorders[ uiActualDimensionality ].end();
				itrHyperplane++ ){
			
			(*itrHyperplane)->hyperplane.print( outputStream );
			
#ifdef DEBUG_NEEDED
			outputStream<<(*itrHyperplane)<<" for inequiation "<<(*itrHyperplane)->pInequiation<<" containing: ";
			
			for ( typename cHyperplaneData< tFactors >::typeItrSetPHyperplanes
					itrContainedHyperplane = (*itrHyperplane)->setContainedHyperplanes.begin();
					itrContainedHyperplane != (*itrHyperplane)->setContainedHyperplanes.end();
					itrContainedHyperplane++ ){
				
				outputStream<<(*itrContainedHyperplane)<<", ";
			}
			outputStream<<endl<<"   contained in: ";
			for ( typename cHyperplaneData< tFactors >::typeItrSetPHyperplanes
					itrContainingHyperplane = (*itrHyperplane)->setContainingHyperplanes.begin();
					itrContainingHyperplane != (*itrHyperplane)->setContainingHyperplanes.end();
					itrContainingHyperplane++ ){
				
				outputStream<<(*itrContainingHyperplane)<<", ";
			}
			outputStream<<endl<<"   "<<(((*itrHyperplane)->bUpdateContainedPoints)?"not actual":"actual")<<" containing points: ";
			for ( typename cHyperplaneData< tFactors >::typeItrSetPHyperplanes
					itrContainedPoint = (*itrHyperplane)->setContainedPoints.begin();
					itrContainedPoint != (*itrHyperplane)->setContainedPoints.end();
					itrContainedPoint++ ){
					
				outputStream<<(*itrContainedPoint)<<", ";
			}
			outputStream<<" is contained in borders: ";
			for ( typename cHyperplaneData< tFactors >::typeItrSetPHyperplanes
					itrContainingBorder = (*itrHyperplane)->setContainingBorders.begin();
					itrContainingBorder != (*itrHyperplane)->setContainingBorders.end();
					itrContainingBorder++ ){
					
				outputStream<<(*itrContainingBorder)<<", ";
			}
		
#endif //DEBUG_NEEDED
			
			outputStream<<endl;
		}
	}
}


/**
 * This method duplicates this whole hyperplane body.
 *
 * @return the cloned/ duplicates hyperplane body
 */
template< class tFactors > cHyperplaneBodyFull<tFactors> *
		cHyperplaneBodyFull<tFactors>::clone() const{
	
	return new cHyperplaneBodyFull< tFactors >( *this );
}


/**
 * This method evalues and inserts the intersections for the given
 * hyperplanes liHyperplanes into this body.
 * The hyperplanes of liHyperplanes should be allready in this body.
 * The hyperplanes of liHyperplanes should also have the same
 * dimensionality (number of directions) uiDimensionality.
 * The containing hyperplanes of the hyperplanes in liHyperplanes, should
 * be allready evalued.
 *
 * @param liHyperplanes the list with the hyperplanes, for which to evalue
 * 	the intersections with this body
 * @param uiDimensionality the dimensionality (number of directions) of
 * 	the hyperplanes in liHyperplanes;
 * 	because the containing hyperplanes of the liHyperplanes should be
 * 	allready evalued, it should be uiDimensionality <= iDimensions - 2
 * @return a list with the pointers of the new created intersection hyperplanes
 */
template< class tFactors > list< cHyperplaneData< tFactors > * >
		cHyperplaneBodyFull<tFactors>::addIntersectionsFor(
		list< cHyperplaneData< tFactors > * > & liHyperplanes,
		const unsigned int uiDimensionality ){
	
	DEBUG_OUT_L2(<<"cHyperplaneBodyFull<tFactors>::addIntersectionsFor( #liHyperplanes="<<liHyperplanes.size()<<", uiDimensionality="<<uiDimensionality<<" ) started"<<endl<<flush);
	
	if ( uiDimensionality == 0 ){
		//can't intersec points -> return no intersections
		return list< cHyperplaneData< tFactors > * >();
	}
	
	/*generate hyperplane pairs for which to create the intersections;
	every combination should be uniqe ( because of that pair.first < pair.second ) )*/
	set< pair< cHyperplaneData< tFactors > *, cHyperplaneData< tFactors > * > >
		setToCreateintersections;
	
	for ( typename list< cHyperplaneData< tFactors > * >::iterator
			itrFirstHyperplane = liHyperplanes.begin();
			itrFirstHyperplane != liHyperplanes.end(); itrFirstHyperplane++ ){
		
		for ( typename cHyperplaneData< tFactors >::typeItrSetPHyperplanes
				itrContainingHyperplane = (*itrFirstHyperplane)->setContainingHyperplanes.begin();
				itrContainingHyperplane != (*itrFirstHyperplane)->setContainingHyperplanes.end();
				itrContainingHyperplane++ ){
			
			for ( typename cHyperplaneData< tFactors >::typeItrSetPHyperplanes
					itrSecondHyperplane = (*itrContainingHyperplane)->setContainedHyperplanes.begin();
					itrSecondHyperplane != (*itrContainingHyperplane)->setContainedHyperplanes.end();
					itrSecondHyperplane++ ){
				
				if ( (*itrFirstHyperplane) != (*itrSecondHyperplane) ){
				
					if ( (*itrFirstHyperplane) < (*itrSecondHyperplane) ){
						
						setToCreateintersections.insert(
							pair< cHyperplaneData< tFactors > *, cHyperplaneData< tFactors > * >(
								(*itrFirstHyperplane), (*itrSecondHyperplane) ) );
					}else{//(*itrSecondHyperplane) < (*itrFirstHyperplane)
						setToCreateintersections.insert(
							pair< cHyperplaneData< tFactors > *, cHyperplaneData< tFactors > * >(
								(*itrSecondHyperplane), (*itrFirstHyperplane) ) );
					}
				}//else skip
			}//end for itrSecondHyperplane
		}//end for itrContainingHyperplane
	}//end for itrFirstHyperplane
	//generate and add intersections of the hyperplanes
	list< cHyperplaneData< tFactors > * > liNewHyperplanes;
	
	for ( typename set< pair< cHyperplaneData< tFactors > *, cHyperplaneData< tFactors > * > >::iterator
			itrHyperplanePair = setToCreateintersections.begin();
			itrHyperplanePair != setToCreateintersections.end();
			itrHyperplanePair++ ){
		
		cHyperplaneData< tFactors > * pFirstHyperplane = itrHyperplanePair->first;
		cHyperplaneData< tFactors > * pSecondHyperplane = itrHyperplanePair->second;
		
		cHyperplane< tFactors > * pIntersection =
			pFirstHyperplane->hyperplane.evalueIntersection(
				pSecondHyperplane->hyperplane );
		
		if ( pIntersection == NULL ){
			//no intersection -> nothing to add
			continue;
		}
		if ( pIntersection->getNumberOfDirections() != (uiDimensionality - 1) ){
			/*the intersection as the same dimensionality as the intersect hyperplanes
			-> it is equal to them ->don't add it
			OR
			tihe intersection has less than uiDimensionality - 1 directions
			-> it is not an border for the intersecting hyperplanes*/
#ifdef DEBUG_ADD_INEQUIATION
			cout<<"the intersection has the wrong dimensionality "<<
				pIntersection->getNumberOfDirections()<<", but should have "<<
				(uiDimensionality - 1)<<endl;
			cout<<"intersection:"<<endl;
			pIntersection->print( cout );
#endif //DEBUG_ADD_INEQUIATION
			delete pIntersection;
			continue;
		}
		/*check if intersection allready exists:
			for all in itrFirstHyperplane and itrSecondHyperplane
			contained hyperplanes, check if ther are equal to the
			intersection*/
		bool bEqualHyperlaneExsists = false;
		for ( typename cHyperplaneData< tFactors >::typeItrSetPHyperplanes
				itrContainedHyperplane = pFirstHyperplane->setContainedHyperplanes.begin();
				itrContainedHyperplane != pFirstHyperplane->setContainedHyperplanes.end();
				itrContainedHyperplane++ ){
			
			if ( pIntersection->equal( (*itrContainedHyperplane)->hyperplane ) ){
				/*if an equal intersection exists, add, if needed, the
				containing hyperplanes itrSecondHyperplane*/
#ifdef DEBUG_ADD_INEQUIATION
				cout<<"equal intersection allready exists in first ("<<pFirstHyperplane<<") hyperplane"<<endl;
				cout<<"intersection:"<<endl;
				pIntersection->print( cout );
#endif //DEBUG_ADD_INEQUIATION
				bEqualHyperlaneExsists = true;
				pSecondHyperplane->addContainedHyperplane( *itrContainedHyperplane );
			}
		}//end for itrContainedHyperplane
		if ( bEqualHyperlaneExsists ){
			//the intersection hyperplane exists allready -> don't add it again
			delete pIntersection;
			continue;
		}
		for ( typename cHyperplaneData< tFactors >::typeItrSetPHyperplanes
				itrContainedHyperplane = pSecondHyperplane->setContainedHyperplanes.begin();
				itrContainedHyperplane != pSecondHyperplane->setContainedHyperplanes.end();
				itrContainedHyperplane++ ){
			
			if ( pIntersection->equal( (*itrContainedHyperplane)->hyperplane ) ){
				/*if an equal intersection exists, add, if needed, the
				containing hyperplanes itrFirstHyperplane*/
#ifdef DEBUG_ADD_INEQUIATION
				cout<<"equal intersection allready exists in second ("<<pSecondHyperplane<<") hyperplane"<<endl;
				cout<<"intersection:"<<endl;
				pIntersection->print( cout );
#endif //DEBUG_ADD_INEQUIATION
				bEqualHyperlaneExsists = true;
				pFirstHyperplane->addContainedHyperplane( *itrContainedHyperplane );
			}
		}//end for itrContainedHyperplane
		if ( bEqualHyperlaneExsists ){
			//the intersection hyperplane exists allready -> don't add it again
			delete pIntersection;
			continue;
		}
		
#ifdef DEBUG_ADD_INEQUIATION
		cout<<"adding new intersection"<<endl;
#endif //DEBUG_ADD_INEQUIATION
		cHyperplaneData< tFactors > * pIntersectionHyperspace =
			new cHyperplaneData< tFactors >();
		
		pIntersectionHyperspace->hyperplane = *pIntersection;
		delete pIntersection;
		
		pFirstHyperplane->addContainedHyperplane( pIntersectionHyperspace );
		pSecondHyperplane->addContainedHyperplane( pIntersectionHyperspace );
		
		liNewHyperplanes.push_back( pIntersectionHyperspace );
		vecBorders[ uiDimensionality - 1 ].push_back( pIntersectionHyperspace );
	}//end for itrHyperplanePair

	DEBUG_OUT_L2(<<"cHyperplaneBodyFull<tFactors>::addIntersectionsFor( liHyperplanes, uiDimensionality ) done "<<liNewHyperplanes.size()<<" created borders"<<endl<<flush);
	return liNewHyperplanes;
}





#endif //___C_HYPERPLANE_BODY_FULL_CPP__



