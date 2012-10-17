/**
 * @file cHyperplaneBody
 * file name: cHyperplaneBody.cpp
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
 *
 * This file implements a class body with hyperplanes as its borders.
 * This body is defined by inequiations, all points wich fulfill the
 * inequiations are part of the body.
 *
 * Beware of the curse of dimensions! The complexity of the body will
 * grow exponential with the number of dimensions. For example, just the
 * number of border points of a newly created body will be 2^uiDimensions .
 *
 * @see cHyperplane
 * @see cInequation
 */
/*
History:
28.01.2011  Oesterholz  created
27.02.2011  Oesterholz  method getNumberOfBorderPoints() added
03.04.2011  Oesterholz  reimplemented with optimized algorithm
*/

#ifndef ___C_HYPERPLANE_BODY_CPP__
#define ___C_HYPERPLANE_BODY_CPP__


#include "version.h"


#include "cHyperplaneBody.h"

#include <vector>
#include <ostream>
#include <map>
#include <cmath>
#include <algorithm>


//for debugging comment in
//#define DEBUG_GET_POINT_IN_BODY


#ifdef DEBUG_GET_POINT_IN_BODY
	#ifndef DEBUG_NEEDED
		#define DEBUG_NEEDED
	#endif
#endif //DEBUG_GET_POINT_IN_BODY


#ifdef DEBUG_NEEDED

	#include <iostream>

	namespace fib{
	namespace algorithms{
	namespace nDn{
	namespace nHyperplaneBody{
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



namespace fib{
namespace algorithms{
namespace nDn{
namespace nHyperplaneBody{
	
	/**
	 * @return true if the first element of the first pair is lower than
	 * 	first element of the second pair, else false
	 */
	template< class tFirstElement, class tSecondElement >
	bool lowestFirstElement( const pair< tFirstElement, tSecondElement > & paFirst,
			const pair< tFirstElement, tSecondElement > & paSecond ){
		
		return ( paFirst.first < paSecond.first );
	}

};};};};//end fib::algorithms::nDn::nHyperplaneBody


using namespace fib::algorithms::nDn;



/**
 * standardconstructor
 *
 * @param uiDimensions the dimensions of the space for the hyperbody;
 * 	all added inequiations should have this much factors
 * 	@see uiDimensions
 */
template< class tFactors > cHyperplaneBody<tFactors>::cHyperplaneBody(
		unsigned int uiInDimensions ):
		uiDimensions( uiInDimensions ){
	//nothing to do
}


/**
 * standard destructor
 */
template< class tFactors > cHyperplaneBody<tFactors>::~cHyperplaneBody(){
	
	//nothing to do
}


/**
 * The inequiations of the given list of inequiations are added with
 * @see addInequiation() till this method returns false or all
 * inequiations are added.
 * @see addInequiation()
 * @see cInequation
 *
 * @return the number of inequiations added to this body, befor a
 *		inequiation (vecInequiation[ return - 1 ]) would remove this body
 */
template< class tFactors > unsigned long cHyperplaneBody<tFactors>::
		addInequiations( const vector< cInequation< tFactors > > & vecInequiations ){
	
	unsigned long uiAddedHyperplanes = 0;
	
	for ( typename vector< cInequation< tFactors > >::const_iterator
			itrInequiation = vecInequiations.begin();
			itrInequiation != vecInequiations.end(); itrInequiation++ ){
		
		if ( addInequiation( *itrInequiation ) ){
			//inequiation could be added
			uiAddedHyperplanes++;
		}else{//inequiation could not be added
			break;
		}
	}
	return uiAddedHyperplanes;
}


/**
 * @return the number of the dimensions for the hyperplane body
 */
template< class tFactors > unsigned int cHyperplaneBody<tFactors>::
		getDimensions() const{
	
	return uiDimensions;
}



/**
 * This method evalues a point in the body.
 * This point will have:
 * 	- as much as possible of its last elements set to 0
 *
 * @param uiMinBitsToStoreMantissa the minimal number of bits to store
 * 	the mantissa of a vector element, when the element is in the
 * 	form: mantissa * 2^exponent ;
 * 	the method will try to reduce the bits, to store a element of the
 * 	returned vector, to this value;
 * 	if uiMinBitsToStoreMantissa is 0 the center points will be returned
 * 	directly and no bits will be reduced
 * @return a point in the body
 */
template< class tFactors > vector< tFactors > cHyperplaneBody<tFactors>::
		getPointInBody( const unsigned int uiMinBitsToStoreMantissa ) const{


#ifdef DEBUG_GET_POINT_IN_BODY
	cout<<endl<<"cHyperplaneBody<tFactors>::getPointInBody( uiMinBitsToStoreMantissa="<<uiMinBitsToStoreMantissa<<" ) started"<<endl;
#endif
	if ( getNumberOfBorderPoints() == 0 ){
		return vector< tFactors >();
	}
	vector< tFactors > vecPointInBody( uiDimensions, ((tFactors)(0)) );
	if ( isPart( vecPointInBody ) ){
		return vecPointInBody;
	}
#ifdef DEBUG_GET_POINT_IN_BODY
	cout<<"copying this hyperbody"<<endl<<flush;
#endif
	//create temporary body, which is a copy of this body
	cHyperplaneBody< tFactors > * pBodyTmp = this->clone();
	if ( pBodyTmp == NULL ){
		return vector< tFactors >();
	}
	/*try to add as much as possible 0 axis inequiations as possible:
		0 <= x_i and  0 <= -x_i*/
	
#ifdef DEBUG_GET_POINT_IN_BODY
	cout<<"try to reduce dimensions"<<endl<<flush;
#endif
	cInequation< tFactors > inequiation;
	inequiation.vecFactors = vector< tFactors >( uiDimensions, ((tFactors)(0)) );
	for ( long lActualDimension = (uiDimensions - 1); 0 <= lActualDimension;
			lActualDimension-- ){
		
#ifdef DEBUG_GET_POINT_IN_BODY
		cout<<"   try to reduce dimension "<<lActualDimension<<endl<<flush;
#endif
		inequiation.vecFactors[ lActualDimension ] = ((tFactors)(1));
		pBodyTmp->addInequiation( inequiation );
		
		inequiation.vecFactors[ lActualDimension ] = ((tFactors)(-1));
		pBodyTmp->addInequiation( inequiation );
		
		inequiation.vecFactors[ lActualDimension ] = ((tFactors)(0));
	}
	//evalue center point of border points
#ifdef DEBUG_GET_POINT_IN_BODY
	cout<<"hyperbody with reduced dimensions:"<<endl;
	pBodyTmp->print( cout );
#endif

	
#define FEATURE_IS_PART_USES_SMALL_BORDER_POINTS 2

	const vector< vector< tFactors > > vecBorderPoints =
		pBodyTmp->getBorderPoints();
	
#if FEATURE_IS_PART_USES_SMALL_BORDER_POINTS == 2
	//remove points with big numbers so that
	
	//choos the border points with the lowes absolut element sum
	typedef set< pair< double, vector< tFactors > >, bool(*)(
		const pair< double, vector< tFactors > > &,
		const pair< double, vector< tFactors > > & ) >
			typeSetBorderPoints;
	typeSetBorderPoints setBordersPoints( nHyperplaneBody::lowestFirstElement<
		double, vector< tFactors > > );
	
	for ( typename vector< vector< tFactors > >::const_iterator
			itrBorderPoint = vecBorderPoints.begin();
			itrBorderPoint != vecBorderPoints.end(); itrBorderPoint++ ){
		
		double dElementSum = 0;
		vector< tFactors > vecBourderPoint( (*itrBorderPoint) );
		//evalue absolut element sum of the border point
		for ( unsigned int uiActualDimension = 0;
				uiActualDimension < uiDimensions; uiActualDimension++ ){
			
			dElementSum += absF( vecBourderPoint[ uiActualDimension ] );
		}
		
#ifdef DEBUG_GET_POINT_IN_BODY
		cout<<"border point (with element sum="<<dElementSum<<"):";
		nHyperplaneBody::nDebug::printVector( cout, vecBourderPoint );
#endif
		setBordersPoints.insert( make_pair( dElementSum, vecBourderPoint ) );
	}
	//take the ulMinBorderPoints border points with the lowest element sum
	const double dBiggestElementSum = setBordersPoints.begin()->first * 16.0;
	unsigned long ulBorderPointsAdded = 0;
	for ( typename typeSetBorderPoints::iterator
			itrBorderPoint = setBordersPoints.begin();
			itrBorderPoint != setBordersPoints.end(); itrBorderPoint++ ){
		
/*TODO better?
		if ( ( dBiggestElementSum < itrBorderPoint->first ) &&
				( uiDimensions < ulBorderPointsAdded ) ){
*/
		if ( dBiggestElementSum < itrBorderPoint->first ){
			/*the following border points have an to big absulut element sum
			and ther wher also an border point for each dimension added
			-> don't use them to evalue the point in the body*/
			break;
		}//else use the border point to evalue a point in the body
#ifdef DEBUG_GET_POINT_IN_BODY
		cout<<"adding vector (with element sum="<<itrBorderPoint->first<<"):";
		nHyperplaneBody::nDebug::printVector( cout, itrBorderPoint->second );
#endif
		addToFirst( vecPointInBody, itrBorderPoint->second );
		ulBorderPointsAdded++;
	}
#ifdef DEBUG_GET_POINT_IN_BODY
	cout<<"sum vector (for "<<ulBorderPointsAdded<<" border points):";
	nHyperplaneBody::nDebug::printVector( cout, vecPointInBody );
#endif
	multToFirst( vecPointInBody, ((tFactors)(1)) / ((tFactors)( ulBorderPointsAdded )) );
#ifdef DEBUG_GET_POINT_IN_BODY
	cout<<"result vector :";
	nHyperplaneBody::nDebug::printVector( cout, vecPointInBody );
#endif
	
	
#elif FEATURE_IS_PART_USES_SMALL_BORDER_POINTS == 1
	
	//remove points with big numbers so that uiDimension + 3 border poins remain
	const unsigned long ulMinBorderPoints = uiDimensions + 3;
	
	if ( ulMinBorderPoints < pBodyTmp->getNumberOfBorderPoints() ){
		//choos the ulMinBorderPoints'th border points with the lowes absolut element sum
		typedef set< pair< double, vector< tFactors > >, bool(*)(
			const pair< double, vector< tFactors > > &,
			const pair< double, vector< tFactors > > & ) >
				typeSetBorderPoints;
		typeSetBorderPoints setBordersPoints( lowestFirstElement< double, vector< tFactors > > );
		
		for ( typename vector< vector< tFactors > * >::const_iterator
				itrBorderPoint = vecBorderPoints.begin();
				itrBorderPoint != vecBorderPoints.end(); itrBorderPoint++ ){
			
			double dElementSum = 0;
			vector< tFactors > vecBourderPoint( (*itrBorderPoint) );
			//evalue absolut element sum of the border point
			for ( unsigned int uiActualDimension = 0;
					uiActualDimension < uiDimensions; uiActualDimension++ ){
				
				dElementSum += absF( vecBourderPoint[ uiActualDimension ] );
			}
			
			setBordersPoints.insert( make_pair( dElementSum, vecBourderPoint ) );
		}
		//take the ulMinBorderPoints border points with the lowest element sum
		unsigned long ulActualBorderPoint = 0;
		for ( typename typeSetBorderPoints::iterator
				itrBorderPoint = setBordersPoints.begin();
				( itrBorderPoint != setBordersPoints.end() ) &&
				( ulActualBorderPoint < ulMinBorderPoints );
				itrBorderPoint++, ulActualBorderPoint++ ){
			
			addToFirst( vecPointInBody, itrBorderPoint->second );
		}
		multToFirst( vecPointInBody, ((tFactors)(1)) / ((tFactors)( ulActualBorderPoint )) );
	}else{//yust take the border points
		for ( typename vector< vector< tFactors > * >::const_iterator
				itrBorderPoint = vecBorderPoints.begin();
				itrBorderPoint != vecBorderPoints.end(); itrBorderPoint++ ){
			
			addToFirst( vecPointInBody, (*itrBorderPoint) );
		}
		multToFirst( vecPointInBody, ((tFactors)(1)) / ((tFactors)( pBodyTmp->getNumberOfBorderPoints() )) );
	}
#else//FEATURE_IS_PART_USES_SMALL_BORDER_POINTS
	for ( typename vector< vector< tFactors > * >::const_iterator
				itrBorderPoint = vecBorderPoints.begin();
				itrBorderPoint != vecBorderPoints.end(); itrBorderPoint++  ){
		
		addToFirst( vecPointInBody, (*itrBorderPoint) );
	}
	multToFirst( vecPointInBody, ((tFactors)(1)) / ((tFactors)(( pBodyTmp->getNumberOfBorderPoints() ))) );
#endif//FEATURE_IS_PART_USES_SMALL_BORDER_POINTS
	
	if ( uiMinBitsToStoreMantissa == 0 ){
		//don't reduce bits
		delete pBodyTmp;
		return vecPointInBody;
	}

	//tvectors for the data of vecPointInBody
	vector< long long > vecMantissas( uiDimensions, 0 );
	vector< unsigned int > vecBitsNeededForMantissa( uiDimensions, 0 );
	vector< int > vecExponent( uiDimensions, 0 );
	
	unsigned int uiMaxBitsNeededForMantissa = 0;
	//evalue uiBitsNeededToStoreSolutionMantissa
	longFib lMantissa;
	longFib lExponent;
	intFib iSizeMantissa;
	intFib iSizeExponent;
	for ( unsigned int uiActualElement = 0; uiActualElement < uiDimensions;
			uiActualElement++ ){
		
		decomposeDoubleFib( vecPointInBody[ uiActualElement ],
			&lMantissa, &lExponent, &iSizeMantissa, &iSizeExponent );
		
		vecMantissas[ uiActualElement ] = lMantissa;
		vecBitsNeededForMantissa[ uiActualElement ] = iSizeMantissa;
		vecExponent[ uiActualElement ] = lExponent;
		
		uiMaxBitsNeededForMantissa = max(
			((unsigned int)(iSizeMantissa)),
			uiMaxBitsNeededForMantissa );
	}
	
	bool bMantissaReduced = true;
	while ( bMantissaReduced &&
			( uiMinBitsToStoreMantissa < uiMaxBitsNeededForMantissa ) ){
		//as long as a mantissa was reduced in the run
		bMantissaReduced = false;
		
		for ( int uiDirection = -1; (uiDirection <= 1) &&
				( uiMinBitsToStoreMantissa < uiMaxBitsNeededForMantissa );
				uiDirection += 2 ){
			//for the two direction in which the mantissa can be changed
			for ( unsigned int uiActualElement = 0; (uiActualElement < uiDimensions) &&
					( uiMinBitsToStoreMantissa < uiMaxBitsNeededForMantissa );
					uiActualElement++ ){
				//for every vector element
				if ( uiMaxBitsNeededForMantissa ==
						vecBitsNeededForMantissa[ uiActualElement ] ){
					/*if the mantissa has the maximum number of bits
					-> try to reduce bits of mantissa*/
					//store old values
					const tFactors dOldValue = vecPointInBody[uiActualElement ];
					//create value for element with reduced number of bits for the mantissa
					vecPointInBody[uiActualElement ] =
						( vecMantissas[ uiActualElement ] + uiDirection ) *
							pow( 2.0, vecExponent[ uiActualElement ] );
					
#ifdef DEBUG_GET_POINT_IN_BODY
					cout<<"checking new point ("<<uiActualElement<<
						"'th element canged in direction "<<uiDirection<<
						", wher "<<vecBitsNeededForMantissa[ uiActualElement ]<<
						" bits are needed to store it)"<<endl;
					nHyperplaneBody::nDebug::printVector( cout, vecPointInBody );
#endif //DEBUG_GET_POINT_IN_BODY
					const bool bNewVectorIsElement = pBodyTmp->isPart( vecPointInBody );
					if ( bNewVectorIsElement ){
						//new vector is part of body -> update values
						vecMantissas[ uiActualElement ] += uiDirection;
						//remove last 0 in mantissa
						vecMantissas[ uiActualElement ] =
							vecMantissas[ uiActualElement ] >> 1;
						vecExponent[ uiActualElement ]++;
						vecBitsNeededForMantissa[ uiActualElement ]--;
						
						uiMaxBitsNeededForMantissa = 0;
						for ( unsigned int uiActualElement1 = 0;
								uiActualElement1 < uiDimensions; uiActualElement1++ ){
							
							uiMaxBitsNeededForMantissa = max(
								vecBitsNeededForMantissa[ uiActualElement1 ],
								uiMaxBitsNeededForMantissa );
						}
						bMantissaReduced = true;
#ifdef DEBUG_GET_POINT_IN_BODY
						cout<<"   point in body -> go to it"<<endl;
#endif //DEBUG_GET_POINT_IN_BODY
					}else{//new vector is not part of body -> restore old value
#ifdef DEBUG_GET_POINT_IN_BODY
						cout<<"   point not in body -> discard it"<<endl;
#endif //DEBUG_GET_POINT_IN_BODY
						vecPointInBody[uiActualElement ] = dOldValue;
					}
				}
			}
		}
	}
	delete pBodyTmp;
	
	return vecPointInBody;
}







#endif //___C_HYPERPLANE_BODY_CPP__



