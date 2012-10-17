/**
 * @file cHyperplaneBodySimple
 * file name: cHyperplaneBodySimple.cpp
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
 * This implementation of the hyperplane body is simple with just points,
 * lines and hyperplanes of the maximal dimensionality. It is fast
 * but it dosn't work correct on big bodies.
 *
 * Beware of the curse of dimensions! The complexity of the body will
 * grow exponential with the number of dimensions. For example, just the
 * number of border points of a newly created body will be 2^uiDimensions .
 *
 * @see cHyperplaneBody
 * @see cHyperplane
 * @see cInequation
 */
/*
History:
28.01.2011  Oesterholz  created
27.02.2011  Oesterholz  method getNumberOfBorderPoints() added
03.04.2011  Oesterholz  reimplemented with optimized algorithm
10.03.2012  Oesterholz  Bugfix: setBorderPoints erase befor deleting the
	point (because point is needed in comparrison)
*/

#ifndef ___C_HYPERPLANE_BODY_SIMPLE_CPP__
#define ___C_HYPERPLANE_BODY_SIMPLE_CPP__


#include "version.h"


#include "cHyperplaneBodySimple.h"

#include <vector>
#include <ostream>
#include <map>
#include <cmath>
#include <algorithm>



//for debugging comment in
//#define DEBUG_ADD_INEQUIATION_SIMPLE
//#define DEBUG_COPY_CONSTRUCTOR_SIMPLE
//#define DEBUG_ADD_INEQUIATION_SIMPLE_2
//#define DEBUG_ADD_INEQUIATION_SIMPLE_COUNTS


#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
	#ifndef DEBUG_NEEDED_HYPERPLANE_BODY_SIMPLE
		#define DEBUG_NEEDED_HYPERPLANE_BODY_SIMPLE
	#endif
#endif //DEBUG_ADD_INEQUIATION_SIMPLE

#ifdef DEBUG_ADD_INEQUIATION_SIMPLE_2
	#ifndef DEBUG_NEEDED_HYPERPLANE_BODY_SIMPLE
		#define DEBUG_NEEDED_HYPERPLANE_BODY_SIMPLE
	#endif
#endif //DEBUG_ADD_INEQUIATION_SIMPLE_2

#ifdef DEBUG_COPY_CONSTRUCTOR_SIMPLE
	#ifndef DEBUG_NEEDED_HYPERPLANE_BODY_SIMPLE
		#define DEBUG_NEEDED_HYPERPLANE_BODY_SIMPLE
	#endif
#endif //DEBUG_COPY_CONSTRUCTOR_SIMPLE

#ifdef DEBUG_ADD_INEQUIATION_SIMPLE_COUNTS
	#ifndef DEBUG_NEEDED_HYPERPLANE_BODY_SIMPLE
		#define DEBUG_NEEDED_HYPERPLANE_BODY_SIMPLE
	#endif
#endif //DEBUG_ADD_INEQUIATION_SIMPLE_2


#ifdef DEBUG_NEEDED_HYPERPLANE_BODY_SIMPLE

	#include <iostream>

	namespace fib{
	namespace algorithms{
	namespace nDn{
	namespace nHyperplaneBodySimple{
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
	};};};};};//fib::algorithms::nDn::nHyperplaneBodySimple::nDebug

#endif //DEBUG_ADD_INEQUIATION_SIMPLE

using namespace std;

using namespace fib::algorithms::nDn;


/**
 * Namespace for border helper classes for the cHyperplaneBodySimple class.
 */
using namespace nHyperplaneBodySimple;

namespace fib{
namespace algorithms{
namespace nDn{
namespace nHyperplaneBodySimple{
/**
 * Namespace for the addInequiation method of the class cHyperplaneBodySimple.
 */
namespace nAddIequiation{
	
	/**
	 * @class cLineToCreate
	 * The class to store the data for an to create (border) line.
	 */
	template< class tFactors > class cLineToCreate{
	public:
		/**
		 * The set with the hyperplanes the to create line is contained in.
		 */
		set< nBorder::cHyperplaneData< tFactors > * > setHyperplanesContainedIn;
		
		/**
		 * The created border line.
		 */
		nBorder::cLine< tFactors > * pBorderLine;
		
		/**
		 * The old points the line connects.
		 * if it connects two old points which wher connected befor, it
		 * isn't needed.
		 */
		list< nBorder::cPoint< tFactors > * > liOldPoints;
		
		/**
		 * Standardconstructor
		 */
		cLineToCreate():pBorderLine( NULL ){
			//nothing to do
		}
		
	};//end class cLineToCreate
	
	/**
	 * @class cPointToCreate
	 * The class to store the data for an to create (border) point.
	 */
	template< class tFactors > class cPointToCreate{
	public:
		
		/**
		 * The set with the hyperplanes the to create point is contained in.
		 */
		set< nBorder::cHyperplaneData< tFactors > * > setHyperplanesContainedIn;
		
		/**
		 * The set with the lines this point is contained in.
		 */
		set< nAddIequiation::cLineToCreate< tFactors > * > setContainingLines;
		
		/**
		 * The lines the point is allready contained in.
		 */
		set< nBorder::cLine< tFactors > * > setContainingLinesOld;
		
		/**
		 * If exists a pointer to the old point, else NULL.
		 */
		nBorder::cPoint< tFactors > * pOldPoint;
		
		/**
		 * Standardconstructor
		 */
		cPointToCreate():pOldPoint( NULL ){
			//nothing to do
		}
		
	};//end class cPointToCreate
	
	
	
};//end namespace nAddIequiation
};};};};//end fib::algorithms::nDn::nHyperplaneBodySimple



/**
 * methods for the @class cHyperplaneData
 * The data for a border hyperplane.
 */

/**
 * standard constructor
 */
template< class tFactors > nBorder::cHyperplaneData< tFactors >::cHyperplaneData():
		pInequiation( NULL ), pInequiationTwo( NULL ){
	//nothing to do
}

/**
 * parameter constructor
 *
 * @param inInequiation the inequiation from which to create the hyperplane
 * @param uiDimensions the number of dimensions of the space for the hyperplane
 */
template< class tFactors > nBorder::cHyperplaneData< tFactors >::cHyperplaneData(
		nBorder::cInequationData< tFactors > & inInequiation, unsigned int uiDimensions ):
		hyperplane( inInequiation.inequiation, uiDimensions ),
		pInequiation( &inInequiation ), pInequiationTwo( NULL ){
	//nothing to do
}


/**
 * destructor
 */
template< class tFactors > nBorder::cHyperplaneData< tFactors >::~cHyperplaneData(){
	
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
	cout<<"deleting hyperplane: "<<this<<endl;
	hyperplane.print( cout );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
	//remove connections
	for ( typename set< nBorder::cLine< tFactors > * >::iterator
			itrContainedLine = setContainedLines.begin();
			itrContainedLine != setContainedLines.end();
			itrContainedLine++ ){
		
		(*itrContainedLine)->setContainingHyperplanes.erase( this );
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
		cout<<"disconnecting contained line "<<(*itrContainedLine)<<" from "<<this<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
	}
	if ( ( pInequiation != NULL ) && ( pInequiation->pHyperplane == this ) ){
		pInequiation->pHyperplane = NULL;
	}
	if ( ( pInequiationTwo != NULL ) && ( pInequiationTwo->pHyperplane == this ) ){
		pInequiationTwo->pHyperplane = NULL;
	}
}


/**
 * This method adds the given line (pointer) as a contained
 * line. It will also add the pointer to this hyperplane as
 * the containing hyperplane in the given line pContainedLine.
 * @see setContainedLines
 *
 * @param pContainedLine a pointer to the line to add as
 * 	the contained line
 */
template< class tFactors > void nBorder::cHyperplaneData< tFactors >::
		addContainedLine( nBorder::cLine< tFactors > * pContainedLine ){
	
	if ( pContainedLine == NULL ){
		//nothing to add
		return;
	}
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
	cout<<"making connection from "<<this<<" containing "<<pContainedLine<<endl;
	cout<<"this is:"<<endl;
	hyperplane.print( cout );
	cout<<"the contained is:"<<endl;
	pContainedLine->hyperplane.print( cout );
	cout<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
	setContainedLines.insert( pContainedLine );
	pContainedLine->setContainingHyperplanes.insert( this );
	
}

//end cHyperplaneData


/**
 * methods for the @class cLine
 * The data for a border line.
 */

/**
 * standard constructor
 */
template< class tFactors > nBorder::cLine< tFactors >::cLine(){
	//nothing to do
}


/**
 * parameter constructor
 *
 * @param point1 a reference to the first point which creats this line
 * @param point2 a reference to the second point which creats this line
 */
template< class tFactors > nBorder::cLine< tFactors >::cLine(
			nBorder::cPoint< tFactors > & point1,
			nBorder::cPoint< tFactors > & point2 ){
	//the direction of the line
	vector< vector< tFactors > > vecDirections( 1 );
	vecDirections[ 0 ] = point2.vecPointPosition;
	vector< tFactors > & vecDirection = vecDirections[ 0 ];
	
	const vector< tFactors > & vecPoint1Position = point1.vecPointPosition;
	const size_t uiNumberOfElements = vecPoint1Position.size();
	
	for ( size_t uiActualElement = 0; uiActualElement < uiNumberOfElements;
			uiActualElement++ ){
		
		vecDirection[ uiActualElement ] -= vecPoint1Position[ uiActualElement ];
	}
	
	hyperplane = cHyperplane< tFactors >( vecPoint1Position, vecDirections );
	
	addContainedPoint( & point1 );
	addContainedPoint( & point2 );
}


/**
 * destructor
 */
template< class tFactors > nBorder::cLine< tFactors >::~cLine(){
	
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
	cout<<"deleting line: "<<this<<endl;
	hyperplane.print( cout );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
	//remove connections
	for ( typename set< nBorder::cPoint< tFactors > * >::iterator
			itrContainedPoint = setContainedPoints.begin();
			itrContainedPoint != setContainedPoints.end();
			itrContainedPoint++ ){
		
		(*itrContainedPoint)->setContainingLines.erase( this );
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
		cout<<"disconnecting contained point "<<(*itrContainedPoint)<<" from line "<<this<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
	}
	for ( typename set< nBorder::cHyperplaneData< tFactors > * >::iterator
			itrContainingHyperplane = setContainingHyperplanes.begin();
			itrContainingHyperplane != setContainingHyperplanes.end();
			itrContainingHyperplane++ ){
		
		(*itrContainingHyperplane)->setContainedLines.erase( this );
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
		cout<<"disconnecting containing hyperplane "<<(*itrContainingHyperplane)<<" from line "<<this<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
	}
}


/**
 * This method adds the given point (pointer) as a contained
 * point. It will also add the pointer to this line as
 * the containing line in the given line pContainedPoint.
 * @see setContainedPoints
 *
 * @param pContainedPoint a pointer to the point to add as
 * 	the contained point
 */
template< class tFactors > void nBorder::cLine< tFactors >::addContainedPoint(
		nBorder::cPoint< tFactors > * pContainedPoint ){
	
	if ( pContainedPoint == NULL ){
		//nothing to add
		return;
	}
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
	cout<<"making connection from "<<this<<" containing "<<pContainedPoint<<endl;
	cout<<"this is:"<<endl;
	hyperplane.print( cout );
	cout<<"the contained is:"<<endl;
	nDebug::printVector( cout, pContainedPoint->vecPointPosition );
	cout<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
	setContainedPoints.insert( pContainedPoint );
	pContainedPoint->setContainingLines.insert( this );
}


//end cLine



/**
 * methods for the @class cPoint
 * The data for a border point.
 */


/**
 * parameter constructor
 *
 * @param inVecPointPosition a vector for the position of this point
 */
template< class tFactors > nBorder::cPoint< tFactors >::cPoint(
		const vector< tFactors > & inVecPointPosition ):
		vecPointPosition( inVecPointPosition ){
	//nothing to do
}


/**
 * destructor
 */
template< class tFactors > nBorder::cPoint< tFactors >::~cPoint(){
	
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
	cout<<"deleting point (containt in "<<setContainingLines.size()<<" lines): "<<this<<endl;
	nDebug::printVector( cout, vecPointPosition );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
	//remove connections
	for ( typename set< nBorder::cLine< tFactors > * >::iterator
			itrContainingLine = setContainingLines.begin();
			itrContainingLine != setContainingLines.end();
			itrContainingLine++ ){
		
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
		cout<<"disconnecting containing line "<<(*itrContainingLine)<<" from point "<<this<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
		(*itrContainingLine)->setContainedPoints.erase( this );
	}
}

//end cPoint


/**
 * methods for the @class cInequationData
 * The data for a inequiation.
 */

/**
 * standardconstructor
 */
template< class tFactors > nBorder::cInequationData< tFactors >::cInequationData():
		pHyperplane( NULL ){
	//nothing to do
}


/**
 * parameterconstructor
 *
 * @param inInequiation the inequiation for the inequiation data
 * @param pInHyperplane the pointer to the hyperplane for the inequiation
 */
template< class tFactors > nBorder::cInequationData< tFactors >::cInequationData(
		const cInequation< tFactors > & inInequiation,
		nBorder::cHyperplaneData< tFactors > * pInHyperplane ):
		inequiation( inInequiation ), pHyperplane( pInHyperplane ){
	//nothing to do
}


/**
 * destructor
 */
template< class tFactors > nBorder::cInequationData< tFactors >::~cInequationData(){
	//remove connections
	if ( ( pHyperplane != NULL ) && ( pHyperplane->pInequiation == this ) ){
		pHyperplane->pInequiation = NULL;
	}
}

//end cInequationData



/**
 * methods for the @class cHyperplaneBodySimple
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
template< class tFactors > cHyperplaneBodySimple<tFactors>::cHyperplaneBodySimple(
		unsigned int uiInDimensions, const tFactors maxValue ):
		cHyperplaneBody<tFactors>( uiInDimensions ){
	
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
	
	/*a vector with the two inequiations for each direction (=factor not null):
		first: is the border in the positiv area
		second: is the border in the negativ area*/
	vector< pair< nBorder::cHyperplaneData< tFactors > *,
		nBorder::cHyperplaneData< tFactors > * > > vecInequiationsForDirections;
	
	for ( unsigned int uiActualDimension = 0; uiActualDimension < this->uiDimensions;
			uiActualDimension++ ){
		
		nBorder::cHyperplaneData< tFactors > * pHyperplaneData1 =
			new nBorder::cHyperplaneData< tFactors >();
		
		nBorder::cInequationData< tFactors > * pInequiationData1 =
			new nBorder::cInequationData< tFactors >();
		pInequiationData1->inequiation.constant = negMaxValue;
		pInequiationData1->inequiation.vecFactors =
			vector< tFactors >( this->uiDimensions , ((tFactors)(0)) );
		//create: negMaxValue <= x_i
		pInequiationData1->inequiation.vecFactors[ uiActualDimension ] =
			((tFactors)(1));
		
		pHyperplaneData1->hyperplane = cHyperplane< tFactors >(
			pInequiationData1->inequiation, this->uiDimensions );
		
		pInequiationData1->pHyperplane = pHyperplaneData1;
		pHyperplaneData1->pInequiation = pInequiationData1;
		
		liInequiations.push_back( pInequiationData1 );
		setBorders.insert( pHyperplaneData1 );
		
		//create: negMaxValue <= -1 * x_i -> x_i <= maxValue
		nBorder::cHyperplaneData< tFactors > * pHyperplaneData2 =
			new nBorder::cHyperplaneData< tFactors >();
		nBorder::cInequationData< tFactors > * pInequiationData2 =
			new nBorder::cInequationData< tFactors >();
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
		setBorders.insert( pHyperplaneData2 );
		
		vecInequiationsForDirections.push_back( make_pair(
			pHyperplaneData2, pHyperplaneData1 ) );
	}
	
	/*The map to create the border points. The entries are:
		key: the signs of the position vector components of the point
		value: a set with the lines, which contain the border point*/
	map< vector< bool >, set< nBorder::cLine< tFactors > * > >
		mapBorderPoints;
	
	/*the vector with the lines for the directions:
		the index is the direction of the line;
		the map vor each index contains:
			key: the signs vor the base vector of the direction, wher the
				direction element is set to true
			value: the line
	*/
	vector< map< vector< bool >, nBorder::cLine< tFactors > * > >
		vecMapLines( this->uiDimensions );
	
	//create border lines and points (beware of uiDimensions<=2)
	if ( 2 < this->uiDimensions ){
		//if more than two dimensions
		//for every two inequiations
		unsigned int uiDirection1 = 0;
		vector< tFactors > vecBase( this->uiDimensions, ((tFactors)(0)) );
		vector< tFactors > vecDirection( this->uiDimensions, ((tFactors)(0)) );
		
		for ( typename vector< pair< nBorder::cHyperplaneData< tFactors > *, nBorder::cHyperplaneData< tFactors > * > >::iterator
				itrDirection1Inequiations = vecInequiationsForDirections.begin();
				itrDirection1Inequiations != vecInequiationsForDirections.end();
				itrDirection1Inequiations++, uiDirection1++ ){
			
			typename vector< pair< nBorder::cHyperplaneData< tFactors > *, nBorder::cHyperplaneData< tFactors > * > >::iterator
				itrDirection2Inequiations = itrDirection1Inequiations;
			unsigned int uiDirection2 = uiDirection1;
			itrDirection2Inequiations++;
			uiDirection2++;
			
			for ( ; itrDirection2Inequiations != vecInequiationsForDirections.end();
					itrDirection2Inequiations++, uiDirection2++ ){
				
				//for all directions which are diffent to the hyperplane normal vectors
				for ( unsigned int uiDirection = 0; uiDirection < this->uiDimensions;
						uiDirection++ ){
					if ( ( uiDirection == uiDirection1 ) || ( uiDirection == uiDirection2 ) ){
						continue;//skip directions
					}
					map< vector< bool >, nBorder::cLine< tFactors > * > &
						mapDirectionLines = vecMapLines[ uiDirection ];
					/*if different factors are not 0 (=for differnt directions)
					-> create line for the factors and connect it to the hyperplanes for
					the inequiations*/
					vecDirection[ uiDirection ] = ((tFactors)(1));
					//direction of the line (value irrelevant,-> set to 0)
					vecBase[ uiDirection ] = 0;
					//vector with the signs for the border point positions vectors
					vector< bool > vecBorderPointSigns( this->uiDimensions, false );
					bool bAddingDone = true;
					while ( bAddingDone ){
						//create the base vectors for the border lines
						for ( char bSignDirection1 = 0; bSignDirection1 <= 1; bSignDirection1++ ){
							vecBorderPointSigns[ uiDirection1 ] = (bSignDirection1 == 0);
							
							for ( char bSignDirection2 = 0; bSignDirection2 <= 1; bSignDirection2++ ){
								vecBorderPointSigns[ uiDirection2 ] = (bSignDirection2 == 0);
								
								for ( unsigned int uiDirectionBase = 0; uiDirectionBase < this->uiDimensions;
										uiDirectionBase++ ){
									//for all non direction base components will be set to values
									if ( uiDirectionBase != uiDirection ){
										/*direction not fixed by the inequiations or in lines direction
										-> take sign from vecBorderPointSigns*/
										if ( vecBorderPointSigns[ uiDirectionBase ] ){
											//positiv value
											vecBase[ uiDirectionBase ] = maxValue;
										}else{//negativ value
											vecBase[ uiDirectionBase ] = negMaxValue;
										}
									}
								}//end for uiDirectionBase
								
								vecBorderPointSigns[ uiDirection ] = true;
								//check if the border line allready exists
								nBorder::cLine< tFactors > * pBorderLine = NULL;
								typename map< vector< bool >, nBorder::cLine< tFactors > * >::iterator
									itrDirectionLine = mapDirectionLines.find( vecBorderPointSigns );
								
								if ( itrDirectionLine == mapDirectionLines.end() ){
									//no line exists jet -> create new line
									pBorderLine = new nBorder::cLine< tFactors >();
									pBorderLine->hyperplane.setBase( vecBase );
									pBorderLine->hyperplane.addDirection( vecDirection );
									setBorderLines.insert( pBorderLine );
									
									mapDirectionLines.insert( make_pair(
											vecBorderPointSigns, pBorderLine ) );
									//add border points
									//first (positiv) side of the line
									mapBorderPoints[ vecBorderPointSigns ].insert( pBorderLine );
									vecBorderPointSigns[ uiDirection ] = false;//other side of the line
									mapBorderPoints[ vecBorderPointSigns ].insert( pBorderLine );
								}else{//use existing line
									pBorderLine = itrDirectionLine->second;
								}
								//add line to containing hyperplanes
								if ( bSignDirection1 == 0 ){//add to positiv first direction hyperplane
									itrDirection1Inequiations->first->addContainedLine( pBorderLine );
								}else{//add to negativ first direction hyperplane
									itrDirection1Inequiations->second->addContainedLine( pBorderLine );
								}
								if ( bSignDirection2 == 0 ){//add to positiv direction second hyperplane
									itrDirection2Inequiations->first->addContainedLine( pBorderLine );
								}else{//add to negativ second direction hyperplane
									itrDirection2Inequiations->second->addContainedLine( pBorderLine );
								}
							}//end for bSignDirection2
						}//end for bSignDirection1
						
						/*basicly add 1 to vecBorderPointSigns with ignoring
						direction not fixed by the inequiations or in lines
						direction;
						You have to imagine vecBorderPointSigns without the
						direction not fixed by the inequiations or in lines
						direction as an integer number. With wher false is an
						0 Bit and true is 1 Bit. For every value this
						integer number should be set, so that every possible
						border line and point are created. So add one till
						vecBorderPointSigns reaches the maximum value and overflows.*/
						bAddingDone = false;
						for ( unsigned int uiActualDirection = 0;
								( uiActualDirection < this->uiDimensions ) && ( ! bAddingDone );
								uiActualDirection++ ){
							
							if ( ( uiActualDirection != uiDirection1 ) &&
									( uiActualDirection != uiDirection2 ) &&
									( uiActualDirection != uiDirection ) ){
								/*direction not fixed by the inequiations or in lines direction
								 -> add one*/
								if ( vecBorderPointSigns[ uiActualDirection ] ){
									//actual direction is positiv -> negate it and add overflow
									vecBorderPointSigns[ uiActualDirection ] = false;
								}else{//actual direction is negativ -> negate it and done (no overflow)
									vecBorderPointSigns[ uiActualDirection ] = true;
									bAddingDone = true;
								}
							}
						}//end add on to vecBorderPointSigns
					}//end while ( bAddingDone )
					vecDirection[ uiDirection ] = ((tFactors)(0));
				}//end for all directions
			}//end for itrDirection2Inequiations
		}//end for itrDirection1Inequiations
		
	}else{/*if uiDimensions<=2 the lines are the border hyperplanes and are
		connected to themself*/
		vector< bool > vecBorderPointSigns( this->uiDimensions, true );
		unsigned int uiDirection = 0;
		for ( typename vector< pair< nBorder::cHyperplaneData< tFactors > *, nBorder::cHyperplaneData< tFactors > * > >::iterator
				itrDirectionInequiations = vecInequiationsForDirections.begin();
				itrDirectionInequiations != vecInequiationsForDirections.end();
				itrDirectionInequiations++, uiDirection++ ){
			
			nBorder::cLine< tFactors > * pBorderLine1 =
				new nBorder::cLine< tFactors >();
			nBorder::cHyperplaneData< tFactors > * pHyperplaneData1 =
				itrDirectionInequiations->first;
			pBorderLine1->hyperplane = pHyperplaneData1->hyperplane;
			pHyperplaneData1->addContainedLine( pBorderLine1 );
			setBorderLines.insert( pBorderLine1 );
			
			nBorder::cLine< tFactors > * pBorderLine2 =
				new nBorder::cLine< tFactors >();
			nBorder::cHyperplaneData< tFactors > * pHyperplaneData2 =
				itrDirectionInequiations->second;
			pBorderLine2->hyperplane = pHyperplaneData2->hyperplane;
			pHyperplaneData2->addContainedLine( pBorderLine2 );
			setBorderLines.insert( pBorderLine2 );
			
			//create border point connections
			if ( this->uiDimensions == 2 ){
				unsigned int uiOtherDirection = ( uiDirection == 0 ) ? 1 : 0;
				
				vecBorderPointSigns[ uiDirection ] = true;
				vecBorderPointSigns[ uiOtherDirection ] = true;//first (positiv) side of the line
				mapBorderPoints[ vecBorderPointSigns ].insert( pBorderLine1 );
				vecBorderPointSigns[ uiOtherDirection ] = false;//other side of the line
				mapBorderPoints[ vecBorderPointSigns ].insert( pBorderLine1 );
				
				vecBorderPointSigns[ uiDirection ] = false;
				vecBorderPointSigns[ uiOtherDirection ] = true;//first (positiv) side of the line
				mapBorderPoints[ vecBorderPointSigns ].insert( pBorderLine2 );
				vecBorderPointSigns[ uiOtherDirection ] = false;//other side of the line
				mapBorderPoints[ vecBorderPointSigns ].insert( pBorderLine2 );
			
			}else{//uiDimensions == 1
				vecBorderPointSigns[ 0 ] = true;//first (positiv) side of the line
				mapBorderPoints[ vecBorderPointSigns ].insert( pBorderLine1 );
				vecBorderPointSigns[ 0 ] = false;//other side of the line
				mapBorderPoints[ vecBorderPointSigns ].insert( pBorderLine2 );
			}
		}
	}//end if more or less than two dimensions
	//create border points -> convert mapBorderPoints to border points
	vector< tFactors > vecBorderPointPosition( this->uiDimensions, ((tFactors)(0)) );
	for ( typename map< vector< bool >, set< nBorder::cLine< tFactors > * > >::iterator
			itrBorderPointSign = mapBorderPoints.begin();
			itrBorderPointSign != mapBorderPoints.end(); itrBorderPointSign++ ){
		//create border vector
		for ( unsigned int uiDirection = 0; uiDirection < this->uiDimensions;
				uiDirection++ ){
			
			const vector< bool > & vecBorderPointSigns =
				itrBorderPointSign->first;
			if ( vecBorderPointSigns[ uiDirection ] ){
				//positiv sign
				vecBorderPointPosition[ uiDirection ] = maxValue;
			}else{//negativ sign
				vecBorderPointPosition[ uiDirection ] = negMaxValue;
			}
		}
		nBorder::cPoint< tFactors > * pBorderPoint =
			new nBorder::cPoint< tFactors >( vecBorderPointPosition );
		setBorderPoints.insert( pBorderPoint );
		
		//connect created border point with the border lines ther are part of
		set< nBorder::cLine< tFactors > * > & setLinesForBorderPoint =
			itrBorderPointSign->second;
		
		for ( typename set< nBorder::cLine< tFactors > * >::iterator
				itrLine = setLinesForBorderPoint.begin();
				itrLine != setLinesForBorderPoint.end(); itrLine++ ){
			
			(*itrLine)->addContainedPoint( pBorderPoint );
		}
	}//end for create all border points
	
}


/**
 * copy constructor
 *
 * @param hyperplaneBody the body to copy
 */
template< class tFactors > cHyperplaneBodySimple<tFactors>::cHyperplaneBodySimple(
		const cHyperplaneBodySimple< tFactors > & hyperplaneBody ):
		cHyperplaneBody<tFactors>( hyperplaneBody.uiDimensions ){
	
#ifdef DEBUG_COPY_CONSTRUCTOR_SIMPLE
	cout<<"cHyperplaneBodySimple<tFactors>::cHyperplaneBodySimple( hyperplaneBody ) started copying:"<<endl<<flush;
	hyperplaneBody.print( cout );
#endif //DEBUG_COPY_CONSTRUCTOR_SIMPLE
	//data to relink the pointers
	map< nBorder::cHyperplaneData< tFactors > *, nBorder::cHyperplaneData< tFactors > * >
		mapHyperplaneMapping;
	map< nBorder::cInequationData< tFactors > *, nBorder::cInequationData< tFactors > * >
		mapInequiationMapping;
	
	mapHyperplaneMapping.insert( pair< nBorder::cHyperplaneData< tFactors > *,
		nBorder::cHyperplaneData< tFactors > * >( NULL, NULL ) );
	mapInequiationMapping.insert( pair< nBorder::cInequationData< tFactors > *,
		nBorder::cInequationData< tFactors > * >( NULL, NULL ) );

#ifdef DEBUG_COPY_CONSTRUCTOR_SIMPLE
	cout<<"copying hyperplanes "<<endl<<flush;
#endif //DEBUG_COPY_CONSTRUCTOR_SIMPLE
	for ( typename set< nBorder::cHyperplaneData< tFactors > * >::const_iterator
			itrHyperplanes = hyperplaneBody.setBorders.begin();
			itrHyperplanes != hyperplaneBody.setBorders.end();
			itrHyperplanes++ ){
		
		nBorder::cHyperplaneData< tFactors > * pHyperplaneCopy =
			new nBorder::cHyperplaneData< tFactors >();
		pHyperplaneCopy->hyperplane = (*itrHyperplanes)->hyperplane;
		
		mapHyperplaneMapping.insert( pair< nBorder::cHyperplaneData< tFactors > *,
			nBorder::cHyperplaneData< tFactors > * >( *itrHyperplanes, pHyperplaneCopy ) );
		
		setBorders.insert( pHyperplaneCopy );
	}
	
#ifdef DEBUG_COPY_CONSTRUCTOR_SIMPLE
	cout<<"copying inequiations "<<endl<<flush;
#endif //DEBUG_COPY_CONSTRUCTOR_SIMPLE
	for ( typename list< nBorder::cInequationData< tFactors > * >::const_iterator
			itrInequiation = hyperplaneBody.liInequiations.begin();
			itrInequiation != hyperplaneBody.liInequiations.end();
			itrInequiation++ ){
		
		nBorder::cInequationData< tFactors > * pInequiationCopy =
			new nBorder::cInequationData< tFactors >( **itrInequiation );
		mapInequiationMapping.insert( pair< nBorder::cInequationData< tFactors > *,
			nBorder::cInequationData< tFactors > * >( *itrInequiation, pInequiationCopy ) );
		
		pInequiationCopy->pHyperplane = mapHyperplaneMapping[
			(*itrInequiation)->pHyperplane ];
		liInequiations.push_back( pInequiationCopy );
	}
	//copy border lines
	map< nBorder::cLine< tFactors > *, nBorder::cLine< tFactors > * >
		mapBorderLineMapping;
	mapBorderLineMapping.insert( pair< nBorder::cLine< tFactors > *,
		nBorder::cLine< tFactors > * >( NULL, NULL ) );
#ifdef DEBUG_COPY_CONSTRUCTOR_SIMPLE
	cout<<"copying lines "<<endl<<flush;
#endif //DEBUG_COPY_CONSTRUCTOR_SIMPLE
	for ( typename set< nBorder::cLine< tFactors > * >::const_iterator
			itrBorderLine = hyperplaneBody.setBorderLines.begin();
			itrBorderLine != hyperplaneBody.setBorderLines.end();
			itrBorderLine++ ){
		
		nBorder::cLine< tFactors > * pLineCopy =
			new nBorder::cLine< tFactors >();
		pLineCopy->hyperplane = (*itrBorderLine)->hyperplane;
		
		mapBorderLineMapping.insert( pair< nBorder::cLine< tFactors > *,
			nBorder::cLine< tFactors > * >( *itrBorderLine, pLineCopy ) );
		
		setBorderLines.insert( pLineCopy );
	}

#ifdef DEBUG_COPY_CONSTRUCTOR_SIMPLE
	cout<<"relink the hyperplane pointers "<<endl<<flush;
#endif //DEBUG_COPY_CONSTRUCTOR_SIMPLE
	mapHyperplaneMapping.erase( NULL );
	//relink the hyperplane pointers
	for ( typename map< nBorder::cHyperplaneData< tFactors > *, nBorder::cHyperplaneData< tFactors > * >::iterator
			itrHyperplane = mapHyperplaneMapping.begin();
			itrHyperplane != mapHyperplaneMapping.end(); itrHyperplane++ ){
		
		const nBorder::cHyperplaneData< tFactors > * pFirstHyperplane = itrHyperplane->first;
		const set< nBorder::cLine< tFactors > * > & setLinesContainedInFirstHyperplane =
			pFirstHyperplane->setContainedLines;
		nBorder::cHyperplaneData< tFactors > * pSecondHyperplane = itrHyperplane->second;

		for ( typename set< nBorder::cLine< tFactors > * >::const_iterator
				itrContainedLine = setLinesContainedInFirstHyperplane.begin();
				itrContainedLine != setLinesContainedInFirstHyperplane.end();
				itrContainedLine++ ){
			
			pSecondHyperplane->addContainedLine(
				mapBorderLineMapping[ *itrContainedLine ] );
		}
		//relink inequiations
		pSecondHyperplane->pInequiation =
			mapInequiationMapping[ pFirstHyperplane->pInequiation ];
		pSecondHyperplane->pInequiationTwo =
			mapInequiationMapping[ pFirstHyperplane->pInequiationTwo ];
	}
	//copy border points
	map< nBorder::cPoint< tFactors > *, nBorder::cPoint< tFactors > * >
		mapBorderPointMapping;
	mapBorderPointMapping.insert( pair< nBorder::cPoint< tFactors > *,
		nBorder::cPoint< tFactors > * >( NULL, NULL ) );
#ifdef DEBUG_COPY_CONSTRUCTOR_SIMPLE
	cout<<"copying points "<<endl<<flush;
#endif //DEBUG_COPY_CONSTRUCTOR_SIMPLE
	for ( typename set< nBorder::cPoint< tFactors > * >::const_iterator
			itrBorderPoint = hyperplaneBody.setBorderPoints.begin();
			itrBorderPoint != hyperplaneBody.setBorderPoints.end();
			itrBorderPoint++ ){
		
		nBorder::cPoint< tFactors > * pPointCopy =
			new nBorder::cPoint< tFactors >( (*itrBorderPoint)->vecPointPosition );
		
		mapBorderPointMapping.insert( pair< nBorder::cPoint< tFactors > *,
			nBorder::cPoint< tFactors > * >( *itrBorderPoint, pPointCopy ) );
		
		setBorderPoints.insert( pPointCopy );
	}
#ifdef DEBUG_COPY_CONSTRUCTOR_SIMPLE
	cout<<"relink the border line pointers "<<endl<<flush;
#endif //DEBUG_COPY_CONSTRUCTOR_SIMPLE
	mapBorderLineMapping.erase( NULL );
	//relink the hyperplane pointers
	for ( typename map< nBorder::cLine< tFactors > *, nBorder::cLine< tFactors > * >::iterator
			itrBorderLine = mapBorderLineMapping.begin();
			itrBorderLine != mapBorderLineMapping.end(); itrBorderLine++ ){
		
		const set< nBorder::cPoint< tFactors > * > &
			setPointsContainedInFirstLine = itrBorderLine->first->setContainedPoints;
		nBorder::cLine< tFactors > * pSecondBorderLine = itrBorderLine->second;

		for ( typename set< nBorder::cPoint< tFactors > * >::const_iterator
				itrContainedPoint = setPointsContainedInFirstLine.begin();
				itrContainedPoint != setPointsContainedInFirstLine.end();
				itrContainedPoint++ ){
			
			pSecondBorderLine->addContainedPoint(
				mapBorderPointMapping[ *itrContainedPoint ] );
		}
	}
	
#ifdef DEBUG_COPY_CONSTRUCTOR_SIMPLE
	cout<<"cHyperplaneBodySimple<tFactors>::cHyperplaneBodySimple( hyperplaneBody ) done; this:"<<endl<<flush;
	print( cout );
#endif //DEBUG_COPY_CONSTRUCTOR_SIMPLE
}


/**
 * standard destructor
 */
template< class tFactors > cHyperplaneBodySimple<tFactors>::~cHyperplaneBodySimple(){
	
	//delete hyperplanes
	for ( typename set< nBorder::cHyperplaneData< tFactors > * >::iterator
			itrHyperplane = setBorders.begin();
			itrHyperplane != setBorders.end(); itrHyperplane++ ){
		
		delete (*itrHyperplane);
	}
	setBorders.clear();
	//delete border lines
	for ( typename set< nBorder::cLine< tFactors > * >::iterator
			itrBorderLine = setBorderLines.begin();
			itrBorderLine != setBorderLines.end(); itrBorderLine++ ){
		
		delete (*itrBorderLine);
	}
	setBorderLines.clear();
	//delete border points
	for ( typename set< nBorder::cPoint< tFactors > * >::iterator
			itrBorderPoint = setBorderPoints.begin();
			itrBorderPoint != setBorderPoints.end(); itrBorderPoint++ ){
		
		delete (*itrBorderPoint);
	}
	setBorderPoints.clear();
	//delete inequiations
	for ( typename list< nBorder::cInequationData< tFactors > * >::iterator
			itrInequiation = liInequiations.begin();
			itrInequiation != liInequiations.end(); itrInequiation++ ){
		
		delete (*itrInequiation);
	}
	liInequiations.clear();
}


//#define FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_SAVE_ON_BIG_NUMBERS
#ifdef FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_SAVE_ON_BIG_NUMBERS
/*TODO: works realy slow (with errors?)
-if it works correct -> export into child class of this class
*/

/**
 * With this method the hyperplane body can be restricted by the given
 * inequiation, if the inequiation dosn't remove the body.
 * If ther are points in this hyperplane body exists wich fulfill the
 * inequiation, an hyperplane for the inequiation is created and added
 * to this hyperplane body.
 * 
 * @see addInequiations()
 * @see cInequation
 * @see cInequation::cHyperplane( const cInequation & inequiation )
 *
 * @return if true this body was restricted by the given inequiation,
 * 	else the inequiation would remove this body
 */
template< class tFactors > bool cHyperplaneBodySimple<tFactors>::addInequiation(
		const cInequation< tFactors > & inequiation ){
	
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
	cout<<endl<<"cHyperplaneBodySimple<tFactors>::addInequiation( inequiation ) started"<<endl;
	cout<<"inequiation:";
	inequiation.print( cout );
	cout<<endl;
	cout<<endl<<"actual body: "<<endl;
	print( cout );
#else //DEBUG_ADD_INEQUIATION_SIMPLE
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE_COUNTS
	cout<<endl<<"cHyperplaneBodySimple<tFactors>::addInequiation( inequiation ) started"<<endl;
	cout<<"inequiation:";
	inequiation.print( cout );
	cout<<endl<<"in body: inequiations: "<<liInequiations.size()<<
		" border hyperplanes: "<<setBorders.size()<<
		" border points: "<<setBorderPoints.size()<<
		" border lines: "<<setBorderLines.size()<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE_COUNTS
#endif //DEBUG_ADD_INEQUIATION_SIMPLE

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
	/*check if non, some or all border points of the body ( setBorders[ 0 ] )
	fullfill the given inequiation*/
	list< nBorder::cPoint< tFactors > * > liPointsInNewBody;
	list< nBorder::cPoint< tFactors > * > liPointsNotInNewBody;
	set< nBorder::cPoint< tFactors > * > setPointsOnInequiation;

#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
	cout<<"checking border points"<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE

	for  ( typename set< nBorder::cPoint< tFactors > * >::iterator
			itrBorderPoint = setBorderPoints.begin();
			itrBorderPoint != setBorderPoints.end(); itrBorderPoint++ ){
		
		const tFactors distanceValue =
			inequiation.evalueValue( (*itrBorderPoint)->vecPointPosition );
		
		if ( 0 < distanceValue ){
			//this border point fulfill the ineqiation an is in the body
			liPointsInNewBody.push_back( *itrBorderPoint );
			
		}else if ( distanceValue < 0 ){//this border point dosn't fulfill the ineqiation
			liPointsNotInNewBody.push_back( *itrBorderPoint );
			
		}else{// (distanceValue == 0) points on the given inequiation
			setPointsOnInequiation.insert( *itrBorderPoint );
		}
	}
	
	if ( liPointsInNewBody.empty() && setPointsOnInequiation.empty() ){
		/*if non border points fulfill the inequiation
		-> the inequiation will remove the body
		-> return false*/
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
		cout<<"no border points fulfill the inequiation "<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
		return false;
	}//else
	
	if ( liPointsNotInNewBody.empty() ){
		/*if all border points fulfill the inequiation
		-> the inequiation won't change the body
		-> return true*/
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
		cout<<"all border points fulfill the inequiation "<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
		return true;
	}/*else if some border points of the body ( setBorders[ 0 ] ) fullfill the
	given inequiation some not -> the inequiation change the body*/
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
	cout<<"finding lines betwean points wich fulfill (="<<
		liPointsInNewBody.size()<<") and which don't fulfill (="<<
		liPointsNotInNewBody.size()<<") the new inequiation (on inequiation "<<
		setPointsOnInequiation.size()<<" points)"<<endl;
#else //DEBUG_ADD_INEQUIATION_SIMPLE
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE_COUNTS
	cout<<"finding lines betwean points wich fulfill (="<<
		liPointsInNewBody.size()<<") and which don't fulfill (="<<
		liPointsNotInNewBody.size()<<") the new inequiation (on inequiation "<<
		setPointsOnInequiation.size()<<" points)"<<endl;
		
#endif //DEBUG_ADD_INEQUIATION_SIMPLE_COUNTS
#endif //DEBUG_ADD_INEQUIATION_SIMPLE

	//create the hyperplane for the inequiation
	nBorder::cInequationData< tFactors > * pNewInequiation =
		new nBorder::cInequationData< tFactors >( inequiation );
	liInequiations.push_back( pNewInequiation );
	
	nBorder::cHyperplaneData< tFactors > * pNewHyperplane = NULL;
	
	/*try to find hyperplane wich is identical to the new hyperplane (this
	hyperplane is has an inequiation wher the constant sign is
	switched [the anti inequiation] )*/
	for ( typename set< nBorder::cHyperplaneData< tFactors > * >::iterator
			itrBorderHyperplane = setBorders.begin();
			itrBorderHyperplane != setBorders.end();
			itrBorderHyperplane++ ){
		
		const nBorder::cInequationData< tFactors > * pInequiationHyperplane =
			(*itrBorderHyperplane)->pInequiation;
		if ( pInequiationHyperplane ){
			if ( inequiation.antiInequiation(
					pInequiationHyperplane->inequiation ) ){
				
				pNewHyperplane = *itrBorderHyperplane;
				break;//anti hyperplane found
			}
		}
	}
	bool bHyperplaneFound = false;
	if ( pNewHyperplane ){
		/*one hyperplane for all lines exists
		-> it has to be the same as for the actual inequiation
		-> delete created hyperplane and connect inequiation with found hyperplane*/
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
		cout<<"one hyperplane for all lines exists -> connect the new "<<
			"inequiation to the hyperplane all points on inequiations are also on"<<endl;
		cout<<"connecting hyperplane "<<pNewHyperplane<<" with inequiation "<<pNewInequiation<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
		pNewHyperplane->pInequiationTwo = pNewInequiation;
		pNewInequiation->pHyperplane = pNewHyperplane;
		bHyperplaneFound = true;
	}
	
	if ( pNewHyperplane == NULL ){
		pNewHyperplane =
			new nBorder::cHyperplaneData< tFactors >( *pNewInequiation, this->uiDimensions );
		pNewInequiation->pHyperplane = pNewHyperplane;
	
	}
	if ( ! bHyperplaneFound ){
		if ( 1 < this->uiDimensions ){
		//find all lines betwean points in new body and outside new body
		set< nBorder::cLine< tFactors > * > setLinesInNewBody;
		for ( typename list< nBorder::cPoint< tFactors > * >::iterator
				itrPointInNewBody = liPointsInNewBody.begin();
				itrPointInNewBody != liPointsInNewBody.end(); itrPointInNewBody++ ){
			
			setLinesInNewBody.insert( (*itrPointInNewBody)->setContainingLines.begin(),
				(*itrPointInNewBody)->setContainingLines.end() );
		}
		set< nBorder::cLine< tFactors > * > setLinesNotInNewBody;
		for ( typename list< nBorder::cPoint< tFactors > * >::iterator
				itrPointNotInNewBody = liPointsNotInNewBody.begin();
				itrPointNotInNewBody != liPointsNotInNewBody.end(); itrPointNotInNewBody++ ){
			
			setLinesNotInNewBody.insert( (*itrPointNotInNewBody)->setContainingLines.begin(),
				(*itrPointNotInNewBody)->setContainingLines.end() );
		}
		//list with the lines betwean points in new body and outside new body
		list< nBorder::cLine< tFactors > * > liLinesIntersectingInequiation;
		for ( typename set< nBorder::cLine< tFactors > * >::iterator
				itrLineInNewBody = setLinesInNewBody.begin();
				itrLineInNewBody != setLinesInNewBody.end(); itrLineInNewBody++ ){
			
			if ( setLinesNotInNewBody.find( *itrLineInNewBody ) !=
					setLinesNotInNewBody.end() ){
				/*line in lines outside and inside the new body
				-> is has to intersect the inequiation*/
				liLinesIntersectingInequiation.push_back( *itrLineInNewBody );
			}
		}
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
		cout<<"number of border lines which intersect the inequiation: "<<liLinesIntersectingInequiation.size()<<endl;
		cout<<"hyperplane for inequiation:"<<endl;
		pNewHyperplane->hyperplane.print( cout );
#else //DEBUG_ADD_INEQUIATION_SIMPLE
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE_COUNTS
		cout<<"number of border lines which intersect the inequiation: "<<liLinesIntersectingInequiation.size()<<endl;
		cout<<"hyperplane for inequiation:"<<endl;
		pNewHyperplane->hyperplane.print( cout );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE_COUNTS
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
		//evalue all points to evalue (they are on uiDimensions - 1)
		//a list for the points to create on the hyperplane
		list< nAddIequiation::cPointToCreate< tFactors > * > liPointsToCreate;
#ifdef FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_NO_DOUBLE_POINTS
		typedef set< set< nBorder::cHyperplaneData< tFactors > * > >
			typeSetPointsForHyperplanes;
		typeSetPointsForHyperplanes setHyperplanesForPoints;
#endif //FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_NO_DOUBLE_POINTS
		//every point on the inequiation creats an point on the inequiation
		for ( typename set< nBorder::cPoint< tFactors > * >::iterator
				itrPointOnInequiation = setPointsOnInequiation.begin();
				itrPointOnInequiation != setPointsOnInequiation.end(); itrPointOnInequiation++ ){
			
			nAddIequiation::cPointToCreate< tFactors > * pPointToCreate =
				new nAddIequiation::cPointToCreate< tFactors >();
			liPointsToCreate.push_back( pPointToCreate );
			
			set< nBorder::cLine< tFactors > * > & setContainigLines =
				(*itrPointOnInequiation)->setContainingLines;
			
			pPointToCreate->setContainingLinesOld.insert(
				setContainigLines.begin(), setContainigLines.end() );
			pPointToCreate->pOldPoint = (*itrPointOnInequiation);
			
			for ( typename set< nBorder::cLine< tFactors > * >::iterator
					itrLineForPointOnInequiation = setContainigLines.begin();
					itrLineForPointOnInequiation != setContainigLines.end();
					itrLineForPointOnInequiation++ ){
			
				pPointToCreate->setHyperplanesContainedIn.insert(
					(*itrLineForPointOnInequiation)->setContainingHyperplanes.begin(),
					(*itrLineForPointOnInequiation)->setContainingHyperplanes.end() );
			}
#ifdef FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_NO_DOUBLE_POINTS
			setHyperplanesForPoints.insert(
				pPointToCreate->setHyperplanesContainedIn );
#endif //FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_NO_DOUBLE_POINTS
		}
		//every intersecting line creats one point
		for ( typename list< nBorder::cLine< tFactors > * >::iterator
				itrLineIntersInequi = liLinesIntersectingInequiation.begin();
				itrLineIntersInequi != liLinesIntersectingInequiation.end();
				itrLineIntersInequi++ ){
			
#ifdef FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_NO_DOUBLE_POINTS
			const typename typeSetPointsForHyperplanes::const_iterator
				itrFoundHyperplanes = setHyperplanesForPoints.find(
					(*itrLineIntersInequi)->setContainingHyperplanes );
			if ( itrFoundHyperplanes != setHyperplanesForPoints.end() ){
				//a point for the hyperplanes already exists
				continue;
			}
			setHyperplanesForPoints.insert(
				(*itrLineIntersInequi)->setContainingHyperplanes );
#endif //FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_NO_DOUBLE_POINTS
			nAddIequiation::cPointToCreate< tFactors > * pPointToCreate =
				new nAddIequiation::cPointToCreate< tFactors >();
			liPointsToCreate.push_back( pPointToCreate );
			
			pPointToCreate->setContainingLinesOld.insert( *itrLineIntersInequi );
			
			pPointToCreate->setHyperplanesContainedIn.insert(
				(*itrLineIntersInequi)->setContainingHyperplanes.begin(),
				(*itrLineIntersInequi)->setContainingHyperplanes.end() );
			
		}
#ifdef FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_NO_DOUBLE_POINTS
		//not needed anymore
		setHyperplanesForPoints.clear();
#endif //FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_NO_DOUBLE_POINTS

		if ( ( ! bHyperplaneFound ) && ( liPointsToCreate.size() == 1 ) &&
				( setPointsOnInequiation.size() == 1 ) ){
			/*only one point to create which is allready on the hyperplane
			-> the new hyperplane don't change the body*/
			pNewInequiation->pHyperplane = NULL;
			liInequiations.pop_back();
			delete pNewHyperplane;
			delete pNewInequiation;
			
			bHyperplaneFound = true;
		}
		if ( ! bHyperplaneFound ){
			//take the created hyperplane
			setBorders.insert( pNewHyperplane );
			
			//evalue the to create lines
			//a list for the lines to create on the hyperplane
			list< nAddIequiation::cLineToCreate< tFactors > * > liLinesToCreate;
			//evalue the to create lines
			for ( typename list< nAddIequiation::cPointToCreate< tFactors > * >::iterator
					itrPoint1ToCreate = liPointsToCreate.begin();
					itrPoint1ToCreate != liPointsToCreate.end(); itrPoint1ToCreate++ ){
				
				typename list< nAddIequiation::cPointToCreate< tFactors > * >::iterator
					itrPoint2ToCreate = itrPoint1ToCreate;
				itrPoint2ToCreate++;
				
				for ( ; itrPoint2ToCreate != liPointsToCreate.end(); itrPoint2ToCreate++ ){
					
					//don't create a line twice
					if ( ( (*itrPoint1ToCreate)->pOldPoint != NULL ) &&
							( (*itrPoint2ToCreate)->pOldPoint != NULL ) ){
						/*if both or allready existing points
						-> check if a line connects the two old points*/
						const set< nBorder::cLine< tFactors > * > & setContainingLines1 =
							(*itrPoint1ToCreate)->setContainingLinesOld;
						const set< nBorder::cLine< tFactors > * > & setContainingLines2 =
							(*itrPoint2ToCreate)->setContainingLinesOld;
						
						bool bLineExists = false;
						for ( typename set< nBorder::cLine< tFactors > * >::const_iterator
								itrContainingLine1 = setContainingLines1.begin();
								itrContainingLine1 != setContainingLines1.end();
								itrContainingLine1++ ){
							
							if ( setContainingLines2.find( *itrContainingLine1 ) !=
									setContainingLines2.end() ){
								/*line in both old points
								-> points are connected with a line
								-> don't create one again*/
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
								cout<<"don't create line "<<(*itrContainingLine1)<<" again"<<endl;
								(*itrContainingLine1)->hyperplane.print( cout );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
								pNewHyperplane->addContainedLine( *itrContainingLine1 );
								bLineExists = true;
								break;
							}
						}
						if ( bLineExists ){
							/*don't create the line again
							-> skip point pair*/
							continue;
						}
					}//end if two old points (don't create a line twice)
					
					/*check if the points have uiDimensions - 1 hyperplanes in common*/
					set< nBorder::cHyperplaneData< tFactors > * > &
						containigHyperplanes1 = (*itrPoint1ToCreate)->setHyperplanesContainedIn;
					set< nBorder::cHyperplaneData< tFactors > * > &
						containigHyperplanes2 = (*itrPoint2ToCreate)->setHyperplanesContainedIn;
					
					/*find hyperplenes wich are the same in both*/
					set< nBorder::cHyperplaneData< tFactors > * > setSameHyperplanes;
					for ( typename set< nBorder::cHyperplaneData< tFactors > * >::iterator
							itrHyperplane = containigHyperplanes1.begin();
							itrHyperplane != containigHyperplanes1.end(); itrHyperplane++ ){
						
						if ( containigHyperplanes2.find( *itrHyperplane ) !=
								containigHyperplanes2.end() ){
							//hyperplane found -> equal hyperplane in both
							setSameHyperplanes.insert( *itrHyperplane );
						}
					}
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
/*					cout<<"the points ("<<(*itrPoint1ToCreate)<<" and "<<
						(*itrPoint2ToCreate)<<") have "<<setSameHyperplanes.size()<<
						" common containing hyperplanes"<<endl;*/
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
					if ( ( this->uiDimensions - 2 ) <= setSameHyperplanes.size() ){
						/*minimal (uiDimensions - 2) other hyperplanes are the same for both points
						-> points are connected by an border line on the new hyperplane
						-> create new border line for the points*/
						nAddIequiation::cLineToCreate< tFactors > * pLineToCreate =
							new nAddIequiation::cLineToCreate< tFactors >();
						
						pLineToCreate->setHyperplanesContainedIn =
							setSameHyperplanes;
						
						(*itrPoint1ToCreate)->setContainingLines.insert( pLineToCreate );
						(*itrPoint2ToCreate)->setContainingLines.insert( pLineToCreate );
						if ( (*itrPoint1ToCreate)->pOldPoint != NULL ){
							
							pLineToCreate->liOldPoints.push_back(
								(*itrPoint1ToCreate)->pOldPoint );
						}
						if ( (*itrPoint2ToCreate)->pOldPoint != NULL ){
							
							pLineToCreate->liOldPoints.push_back(
								(*itrPoint2ToCreate)->pOldPoint );
						}
						
						liLinesToCreate.push_back( pLineToCreate );
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
						cout<<"the points ("<<(*itrPoint1ToCreate)<<" and "<<
							(*itrPoint2ToCreate)<<") have "<<setSameHyperplanes.size()<<
							" common containing hyperplanes -> they are connected with an line"<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
					}
				}//end for itrPoint2ToCreate
			}//end for itrPoint1ToCreate
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE_COUNTS
			cout<<"points to create: "<<liPointsToCreate.size()<<"  lines to create: "<<liLinesToCreate.size()<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE_COUNTS
		
			/*evalue the lines, by evaluing the intersections of all
			hyperplanes ther are part of */
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
			cout<<"evalue the lines "<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
			const cHyperplane< tFactors > * pNewHyperplaneDirect =
				&(pNewHyperplane->hyperplane);
			for ( typename list< nAddIequiation::cLineToCreate< tFactors > * >::iterator
					itrLineToCreate = liLinesToCreate.begin();
					itrLineToCreate != liLinesToCreate.end();
					itrLineToCreate++ ){
				
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
				cout<<endl<<"creating intersection for border line ("<<
					(*itrLineToCreate)<<") and new hyperplane for inequiation ("<<
					pNewHyperplane<<")"<<endl<<flush;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
				
				cHyperplane< tFactors > * pIntersection = &(pNewHyperplane->hyperplane);
				set< nBorder::cHyperplaneData< tFactors > * > &
					setHyperplanesContainedIn =
						(*itrLineToCreate)->setHyperplanesContainedIn;
				
				for ( typename set< nBorder::cHyperplaneData< tFactors > * >::iterator
						itrHyperplane = setHyperplanesContainedIn.begin();
						itrHyperplane != setHyperplanesContainedIn.end(); itrHyperplane++ ){
					
					cHyperplane< tFactors > * pNewIntersection =
						pIntersection->evalueIntersection(
							(*itrHyperplane)->hyperplane );
					
					if ( pNewIntersection != NULL ){
						//intersection found
						if ( pIntersection != pNewHyperplaneDirect ){
							delete pIntersection;
						}
						pIntersection = pNewIntersection;
					}
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
					else{ //no intersection -> error + nothing to add
						cerr<<"Error: no intersection found"<<endl;
						cerr<<"new hyperplane for inequiations:"<<endl;
						pNewHyperplane->hyperplane.print( cerr );
						cerr<<"line to intersect new hyperplane with:"<<endl;
						(*itrHyperplane)->hyperplane.print( cerr );
					}
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
				}
				if ( pIntersection == NULL ){
					//no intersection -> error + nothing to add
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
					cerr<<"Error: no intersection found"<<endl;
					cerr<<"new hyperplane for inequiations:"<<endl;
					pNewHyperplane->hyperplane.print( cerr );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
					continue;//evalue next line
				}//else intersection found
				if ( pIntersection->getNumberOfDirections() != 1 ){
					//no intersection -> error + nothing to add
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
					cerr<<"Error: intersection is no line (directions="<<
						pIntersection->getNumberOfDirections()<<")"<<endl;
					cerr<<"new hyperplane for inequiations:"<<endl;
					pNewHyperplane->hyperplane.print( cerr );
					cerr<<"intersection:"<<endl;
					pIntersection->print( cerr );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
					if ( pIntersection != pNewHyperplaneDirect ){
						delete pIntersection;
					}
					continue;//evalue next line
				}//else intersection found
				
				
				nBorder::cLine< tFactors > * pNewBorderLine =
					new nBorder::cLine< tFactors >();
				pNewBorderLine->hyperplane = *pIntersection;
				(*itrLineToCreate)->pBorderLine = pNewBorderLine;
				if ( pIntersection != pNewHyperplaneDirect ){
					delete pIntersection;
				}
				
				setBorderLines.insert( pNewBorderLine );
				//make connections to containing hyperplanes
				pNewHyperplane->addContainedLine( pNewBorderLine );
				for ( typename set< nBorder::cHyperplaneData< tFactors > * >::iterator
						itrHyperplane = setHyperplanesContainedIn.begin();
						itrHyperplane != setHyperplanesContainedIn.end(); itrHyperplane++ ){
					
					(*itrHyperplane)->addContainedLine( pNewBorderLine );
				}
				
				for ( typename list< nBorder::cPoint< tFactors > * >::iterator
						itrOldPoint = (*itrLineToCreate)->liOldPoints.begin();
						itrOldPoint != (*itrLineToCreate)->liOldPoints.end();
						itrOldPoint++ ){
					
					pNewBorderLine->addContainedPoint( *itrOldPoint );
				}
			}//end for all lines to create
				
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
			cout<<"evalue the points "<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
			/*evalue the points, by evaluing the intersections of a line ther
			are part of and an hyperplane the line is not part of but the point is*/
			for ( typename list< nAddIequiation::cPointToCreate< tFactors > * >::iterator
					itrPointsToCreate = liPointsToCreate.begin();
					itrPointsToCreate != liPointsToCreate.end();
					itrPointsToCreate++ ){
				
				if ( (*itrPointsToCreate)->pOldPoint != NULL ){
					//an point allready exists -> skip point
					continue;
				}
				
				//get a line the point is part of
				set< nAddIequiation::cLineToCreate< tFactors > * > &
					setContainingLines = (*itrPointsToCreate)->setContainingLines;
				cHyperplane< tFactors > * pIntersection = NULL;
				
				if ( ! setContainingLines.empty() ){
					
					nAddIequiation::cLineToCreate< tFactors > * pLinePointIsPartOf =
						*(setContainingLines.begin());
					if ( pLinePointIsPartOf->pBorderLine == NULL ){
						//Error: no hyperplane for the line
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
						cerr<<"Error: Can't create point "<<(*itrPointsToCreate)<<
							" for line "<<pLinePointIsPartOf<<": no hyperplane for the line "<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
					}else{//pLinePointIsPartOf->pBorderLine != NULL
						//evalue an hyperplane the point is part of but not the line
						set< nBorder::cHyperplaneData< tFactors > * > &
							setHyperplanesContainingLine =
								pLinePointIsPartOf->setHyperplanesContainedIn;
						set< nBorder::cHyperplaneData< tFactors > * > &
							setHyperplanesContainingPoint =
								(*itrPointsToCreate)->setHyperplanesContainedIn;
						
						nBorder::cHyperplaneData< tFactors > * pHyperplaneLineIsNotPart = NULL;
						for ( typename set< nBorder::cHyperplaneData< tFactors > * >::iterator
								itrHyperplane = setHyperplanesContainingPoint.begin();
								itrHyperplane != setHyperplanesContainingPoint.end(); itrHyperplane++ ){
							
							if ( setHyperplanesContainingLine.find( *itrHyperplane ) ==
									setHyperplanesContainingLine.end() ){
								
								pHyperplaneLineIsNotPart = *itrHyperplane;
								break;//hyperplane the point is part of but not the line found
							}
						}
						if ( pHyperplaneLineIsNotPart != NULL ){
							pIntersection = pHyperplaneLineIsNotPart->hyperplane.evalueIntersection(
									pLinePointIsPartOf->pBorderLine->hyperplane );
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
							if ( pIntersection == NULL ){
								//no intersection -> error + nothing to add
								cerr<<"Error: no intersection found"<<endl;
								cerr<<"hyperplane:"<<endl;
								pHyperplaneLineIsNotPart->hyperplane.print( cerr );
								cerr<<"line to intersect hyperplane with:"<<endl;
								pLinePointIsPartOf->pBorderLine->hyperplane.print( cerr );
							}//else intersection found
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
						}else{//( pHyperplaneLineIsNotPart == NULL )
							//Error: no hyperplane the line is not part of
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
							cerr<<"Error: no hyperplane the line "<<pLinePointIsPartOf<<
								" is not part of (to create point "<<(*itrPointsToCreate)<<")"<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
						}//end if pHyperplaneLineIsNotPart
					}//end if line for point has hyperplane
				}
				if ( pIntersection == NULL ){
					//no intersection -> intersect hyperplanes the point is part of
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
					if ( setContainingLines.empty() ){
						//the point contains no lines
						cout<<"No line for the point "<<(*itrPointsToCreate)<<endl;
					}else{
						cerr<<"Error: No intersection evalued for point "<<(*itrPointsToCreate)<<endl;
					}
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
					
					pIntersection = &(pNewHyperplane->hyperplane);
					set< nBorder::cHyperplaneData< tFactors > * > &
						setHyperplanesContainedIn =
							(*itrPointsToCreate)->setHyperplanesContainedIn;
					
					for ( typename set< nBorder::cHyperplaneData< tFactors > * >::iterator
							itrHyperplane = setHyperplanesContainedIn.begin();
							itrHyperplane != setHyperplanesContainedIn.end(); itrHyperplane++ ){
						
						cHyperplane< tFactors > * pNewIntersection =
							pIntersection->evalueIntersection(
								(*itrHyperplane)->hyperplane );
						
						if ( pNewIntersection != NULL ){
							//intersection found
							if ( pIntersection != pNewHyperplaneDirect ){
								delete pIntersection;
							}
							pIntersection = pNewIntersection;
						}
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
						else{ //no intersection -> error + nothing to add
							cerr<<"Error: no intersection found"<<endl;
							cerr<<"new hyperplane for inequiations:"<<endl;
							pNewHyperplane->hyperplane.print( cerr );
							cerr<<"line to intersect new hyperplane with:"<<endl;
							(*itrHyperplane)->hyperplane.print( cerr );
						}
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
					}
					
				}//else intersection found
				if ( pIntersection == NULL ){
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
					cerr<<"Error: No intersection evalued for point "<<(*itrPointsToCreate)<<
						" with the help of the hyperplanes it is part of"<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
					continue;//skip this border point
				}
				if ( pIntersection->getNumberOfDirections() != 0 ){
					//no intersection -> error + nothing to add
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
					cerr<<"Error: intersection is no point (directions="<<
						pIntersection->getNumberOfDirections()<<")"<<endl;
					cerr<<"new hyperplane for inequiations:"<<endl;
					pNewHyperplane->hyperplane.print( cerr );
					cerr<<"intersection:"<<endl;
					pIntersection->print( cerr );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
					if ( pIntersection != pNewHyperplaneDirect ){
						delete pIntersection;
					}
					continue;//evalue next line
				}//else intersection found
				nBorder::cPoint< tFactors > * pNewBorderPoint =
					new nBorder::cPoint< tFactors >( pIntersection->getBase() );
				
				//check if a border point for the position allready exists
				typename set< nBorder::cPoint< tFactors > * >::iterator itrNewPoint =
					setBorderPoints.find( pNewBorderPoint );
				bool bNewPoint = true;
				if ( itrNewPoint == setBorderPoints.end() ){
					//no border point on the position found/exists -> new border point
					setBorderPoints.insert( pNewBorderPoint );
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
					cout<<"adding new border point on inequiation for body: "<<endl;
					nDebug::printVector( cout, pNewBorderPoint->vecPointPosition );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
				}else{//point with this position allready exists
					delete pNewBorderPoint;
					pNewBorderPoint = *itrNewPoint;
					bNewPoint = false;
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
					cout<<"connecting existing border point "<<pNewBorderPoint<<" on inequiation: "<<endl;
					nDebug::printVector( cout, (*itrNewPoint)->vecPointPosition );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
				}
				//add point to all lines it is part of
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
				cout<<"connecting border point "<<pNewBorderPoint<<" with new lines: "<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
				for ( typename set< nAddIequiation::cLineToCreate< tFactors > * >::iterator
						itrContainigLine = setContainingLines.begin();
						itrContainigLine != setContainingLines.end();
						itrContainigLine++ ){
					
					if ( (*itrContainigLine)->pBorderLine != NULL ){
						//add to all points for the line
						(*itrContainigLine)->pBorderLine->addContainedPoint(
							pNewBorderPoint );
						
						if ( ! bNewPoint ){
							(*itrContainigLine)->liOldPoints.push_back(
								pNewBorderPoint );
						}
					}
				}
				//get a line the point is part of
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
				cout<<"connecting border point "<<pNewBorderPoint<<" with old lines: "<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
				set< nBorder::cLine< tFactors > * > & setContainingLinesOld =
					(*itrPointsToCreate)->setContainingLinesOld;
				for ( typename set< nBorder::cLine< tFactors > * >::iterator
						itrContainigLineOld = setContainingLinesOld.begin();
						itrContainigLineOld != setContainingLinesOld.end();
						itrContainigLineOld++ ){
					
					(*itrContainigLineOld)->addContainedPoint(
						pNewBorderPoint );
				}
				if ( pIntersection != pNewHyperplaneDirect ){
					delete pIntersection;
				}
			}//end for all points to create
				
			/*remove all new lines which connecting two old points
			which wher connected with a line befor*/
			for ( typename list< nAddIequiation::cLineToCreate< tFactors > * >::iterator
					itrLineToCreate = liLinesToCreate.begin();
					itrLineToCreate != liLinesToCreate.end();
					itrLineToCreate++ ){
					
				if ( 2 <= (*itrLineToCreate)->liOldPoints.size() ){
					/*the line connects two old points
					-> check if the points wher connected with a line befor*/
					const set< nBorder::cLine< tFactors > * > & setContainingLines1 =
						(*itrLineToCreate)->liOldPoints.front()->setContainingLines;
					const set< nBorder::cLine< tFactors > * > & setContainingLines2 =
						(*itrLineToCreate)->liOldPoints.back()->setContainingLines;
					
					nBorder::cLine< tFactors > * pCreatedLine =
						(*itrLineToCreate)->pBorderLine;
					
					for ( typename set< nBorder::cLine< tFactors > * >::const_iterator
							itrContainingLine1 = setContainingLines1.begin();
							itrContainingLine1 != setContainingLines1.end();
							itrContainingLine1++ ){
						
						if ( pCreatedLine == (*itrContainingLine1) ){
							continue;//skip new created line
						}else if ( setContainingLines2.find( *itrContainingLine1 ) !=
								setContainingLines2.end() ){
							/*line in both old points
							-> points wher connected with a line befor
							-> remove new line*/
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
							cout<<"removing line "<<(*itrLineToCreate)->pBorderLine<<
								" (to create "<<(*itrLineToCreate)<<") because ther is in old line equal to it"<<endl;
							(*itrLineToCreate)->pBorderLine->hyperplane.print( cout );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
							setBorderLines.erase( pCreatedLine );
							delete pCreatedLine;
							break;
						}
					}
				}//end if two old points
			}//end remove all new lines which connecting two old points
			//delete all to create lines
			for ( typename list< nAddIequiation::cLineToCreate< tFactors > * >::iterator
					itrLineToCreate = liLinesToCreate.begin();
					itrLineToCreate != liLinesToCreate.end();
					itrLineToCreate++ ){
				
					delete (*itrLineToCreate);
			}
			liLinesToCreate.clear();
		}//if no hyperplane found
			
		//delete all to create points
		for ( typename list< nAddIequiation::cPointToCreate< tFactors > * >::iterator
				itrPointsToCreate = liPointsToCreate.begin();
				itrPointsToCreate != liPointsToCreate.end();
				itrPointsToCreate++ ){
			
			delete (*itrPointsToCreate);
		}
		liPointsToCreate.clear();
	}else{// if ( uiDimensions == 1 )
		/* borders are all points;
		space of body is in an line
		-> add created hyperplane as border line and border point and
		delete border point outside of the body*/
		//add border line
		setBorders.insert( pNewHyperplane );
		
		nBorder::cLine< tFactors > * pNewBorderLine =
			new nBorder::cLine< tFactors >();
		pNewBorderLine->hyperplane = pNewHyperplane->hyperplane;
		pNewHyperplane->addContainedLine( pNewBorderLine );
		setBorderLines.insert( pNewBorderLine );
		//add border point
		nBorder::cPoint< tFactors > * pNewBorderPoint =
			new nBorder::cPoint< tFactors >( pNewHyperplane->hyperplane.getBase() );
		pNewBorderLine->addContainedPoint( pNewBorderPoint );
		setBorderPoints.insert( pNewBorderPoint );
	}//end if uiDimensions
	}//end if ( ! bHyperplaneFound)

#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
	cout<<endl<<"body befor removing 1 (points to remove "<<liPointsNotInNewBody.size()<<") : "<<endl;
	print( cout );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE

	//remove all points outside the new body
	set< nBorder::cLine< tFactors > * > setCheckToRemoveLines;
	for ( typename list< nBorder::cPoint< tFactors > * >::iterator
			itrPointNotInNewBody = liPointsNotInNewBody.begin();
			itrPointNotInNewBody != liPointsNotInNewBody.end(); itrPointNotInNewBody++ ){
		
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
		cout<<endl<<"removing border point: "<<(*itrPointNotInNewBody)<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
		setCheckToRemoveLines.insert(
			(*itrPointNotInNewBody)->setContainingLines.begin(),
			(*itrPointNotInNewBody)->setContainingLines.end() );
		
		setBorderPoints.erase( *itrPointNotInNewBody );
		delete (*itrPointNotInNewBody);
	}
	
	//remove all lines without points
	set< nBorder::cHyperplaneData< tFactors > * > setCheckToRemoveHyperplanes;
	for ( typename set< nBorder::cLine< tFactors > * >::iterator
			itrBorderLine = setCheckToRemoveLines.begin();
			itrBorderLine != setCheckToRemoveLines.end(); itrBorderLine++ ){
		
		if ( (*itrBorderLine)->setContainedPoints.empty() ){
			//no border points for border line -> remove it
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
			cout<<endl<<"removing border line: "<<(*itrBorderLine)<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
			setCheckToRemoveHyperplanes.insert(
				(*itrBorderLine)->setContainingHyperplanes.begin(),
				(*itrBorderLine)->setContainingHyperplanes.end() );
			
			setBorderLines.erase( *itrBorderLine );
			delete (*itrBorderLine);
		}
	}
	
	//remove all hyperplanes without lines
	for ( typename set< nBorder::cHyperplaneData< tFactors > * >::iterator
			itrHyperplane = setCheckToRemoveHyperplanes.begin();
			itrHyperplane != setCheckToRemoveHyperplanes.end();
			itrHyperplane++ ){
		
		if ( (*itrHyperplane)->setContainedLines.empty() ){
			//no border lines for border hyperplane -> remove it
			nBorder::cInequationData< tFactors > * pInequiation =
				(*itrHyperplane)->pInequiation;
			if ( pInequiation ){
				//delete inequiation for the hyperplane
				liInequiations.erase( find(
					liInequiations.begin(), liInequiations.end(), pInequiation ) );
				delete pInequiation;
			}
			nBorder::cInequationData< tFactors > * pInequiationTwo =
				(*itrHyperplane)->pInequiationTwo;
			if ( pInequiationTwo ){
				//delete second inequiation for the hyperplane
				liInequiations.erase( find(
					liInequiations.begin(), liInequiations.end(), pInequiationTwo ) );
				delete pInequiationTwo;
			}
			
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
			cout<<endl<<"removing border hyperplane: "<<(*itrHyperplane)<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
			setBorders.erase( *itrHyperplane );
			delete (*itrHyperplane);
		}
	}
	
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
	cout<<endl<<"body after removing: "<<endl;
	print( cout );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
	
	return true;
}


#else //FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_SAVE_ON_BIG_NUMBERS


/**
 * With this method the hyperplane body can be restricted by the given
 * inequiation, if the inequiation dosn't remove the body.
 * If ther are points in this hyperplane body exists wich fulfill the
 * inequiation, an hyperplane for the inequiation is created and added
 * to this hyperplane body.
 * 
 * @see addInequiations()
 * @see cInequation
 * @see cInequation::cHyperplane( const cInequation & inequiation )
 *
 * @return if true this body was restricted by the given inequiation,
 * 	else the inequiation would remove this body
 */
template< class tFactors > bool cHyperplaneBodySimple<tFactors>::addInequiation(
		const cInequation< tFactors > & inequiation ){
	
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
	cout<<endl<<"cHyperplaneBodySimple<tFactors>::addInequiation( inequiation ) started"<<endl;
	cout<<"inequiation:";
	inequiation.print( cout );
	cout<<endl;
	cout<<endl<<"actual body: "<<endl;
	print( cout );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE

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
	/*check if non, some or all border points of the body ( setBorders[ 0 ] )
	fullfill the given inequiation*/
	list< nBorder::cPoint< tFactors > * > liPointsInNewBody;
	list< nBorder::cPoint< tFactors > * > liPointsNotInNewBody;
	set< nBorder::cPoint< tFactors > * > setPointsOnInequiation;

#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
	cout<<"checking border points"<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE

	for  ( typename set< nBorder::cPoint< tFactors > * >::iterator
			itrBorderPoint = setBorderPoints.begin();
			itrBorderPoint != setBorderPoints.end(); itrBorderPoint++ ){
		
		const tFactors distanceValue =
			inequiation.evalueValue( (*itrBorderPoint)->vecPointPosition );
		
		if ( 0 < distanceValue ){
			//this border point fulfill the ineqiation an is in the body
			liPointsInNewBody.push_back( *itrBorderPoint );
			
		}else if ( distanceValue < 0 ){//this border point dosn't fulfill the ineqiation
			liPointsNotInNewBody.push_back( *itrBorderPoint );
			
		}else{// (distanceValue == 0) points on the given inequiation
			setPointsOnInequiation.insert( *itrBorderPoint );
		}
	}
	
	if ( liPointsInNewBody.empty() && setPointsOnInequiation.empty() ){
		/*if no border points fulfill the inequiation
		-> the inequiation will remove the body
		-> return false*/
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
		cout<<"no border points fulfill the inequiation "<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
		return false;
	}//else
	
	if ( liPointsNotInNewBody.empty() ){
		/*if all border points fulfill the inequiation
		-> the inequiation won't change the body
		-> return true*/
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
		cout<<"all border points fulfill the inequiation "<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
		return true;
	}/*else if some border points of the body ( setBorders[ 0 ] ) fullfill the
	given inequiation some not -> the inequiation change the body*/
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
	cout<<"finding lines betwean points wich fulfill (="<<
		liPointsInNewBody.size()<<") and which don't fulfill (="<<
		liPointsNotInNewBody.size()<<") the new inequiation (on inequiation "<<
		setPointsOnInequiation.size()<<" points)"<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE

	//create the hyperplane for the inequiation
	nBorder::cInequationData< tFactors > * pNewInequiation =
		new nBorder::cInequationData< tFactors >( inequiation );
	liInequiations.push_back( pNewInequiation );
	
	nBorder::cHyperplaneData< tFactors > * pNewHyperplane =
		new nBorder::cHyperplaneData< tFactors >( *pNewInequiation, this->uiDimensions );
	pNewInequiation->pHyperplane = pNewHyperplane;
	
	set< nBorder::cLine< tFactors > * > setLinesInNewBody;
	set< nBorder::cLine< tFactors > * > setLinesNotInNewBody;
	list< nBorder::cLine< tFactors > * > liLinesIntersectingInequiation;
	if ( 1 < this->uiDimensions ){
		//find all lines betwean points in new body and outside new body
		for ( typename list< nBorder::cPoint< tFactors > * >::iterator
				itrPointInNewBody = liPointsInNewBody.begin();
				itrPointInNewBody != liPointsInNewBody.end(); itrPointInNewBody++ ){
			
			setLinesInNewBody.insert( (*itrPointInNewBody)->setContainingLines.begin(),
				(*itrPointInNewBody)->setContainingLines.end() );
		}
		for ( typename list< nBorder::cPoint< tFactors > * >::iterator
				itrPointNotInNewBody = liPointsNotInNewBody.begin();
				itrPointNotInNewBody != liPointsNotInNewBody.end(); itrPointNotInNewBody++ ){
			
			setLinesNotInNewBody.insert( (*itrPointNotInNewBody)->setContainingLines.begin(),
				(*itrPointNotInNewBody)->setContainingLines.end() );
		}
		//list with ines betwean points in new body and outside new body
		for ( typename set< nBorder::cLine< tFactors > * >::iterator
				itrLineInNewBody = setLinesInNewBody.begin();
				itrLineInNewBody != setLinesInNewBody.end(); itrLineInNewBody++ ){
			
			if ( setLinesNotInNewBody.find( *itrLineInNewBody ) !=
					setLinesNotInNewBody.end() ){
				/*line in lines outside and inside the new body
				-> is has to intersect the inequiation*/
				liLinesIntersectingInequiation.push_back( *itrLineInNewBody );
			}
		}
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
		cout<<"number of border lines which intersect the inequiation: "<<liLinesIntersectingInequiation.size()<<endl;
		cout<<"hyperplane for inequiation:"<<endl;
		pNewHyperplane->hyperplane.print( cout );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
		
		/*evalue intersections betwean the new inequiations and the found
		lines and add them to the points on the hyperplane for the inequiation
		and the hyperplanes which contain the lines*/
		/*the map with the new border points on the inequiations and the border
		lines which created them:
			key: the border line, which created the new border point
			value: the new border point on the hyperplane to the inequiation*/
		set< nBorder::cPoint< tFactors > * > setNewPointsOnHyperplane;
		for ( typename list< nBorder::cLine< tFactors > * >::iterator
				itrLineIntersInequi = liLinesIntersectingInequiation.begin();
				itrLineIntersInequi != liLinesIntersectingInequiation.end();
				itrLineIntersInequi++ ){
			
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
			cout<<endl<<"creating intersection for border line ("<<
				(*itrLineIntersInequi)<<") and new hyperplane for inequiation ("<<
				pNewHyperplane<<")"<<endl<<flush;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
			cHyperplane< tFactors > * pIntersection =
				pNewHyperplane->hyperplane.evalueIntersection(
					(*itrLineIntersInequi)->hyperplane );
			if ( pIntersection == NULL ){
				//no intersection -> error + nothing to add
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
				cerr<<"Error: no intersection found"<<endl;
				cerr<<"new hyperplane for inequiations:"<<endl;
				pNewHyperplane->hyperplane.print( cerr );
				cerr<<"line to intersect new hyperplane with:"<<endl;
				(*itrLineIntersInequi)->hyperplane.print( cerr );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
				continue;
			}//else intersection found
			nBorder::cPoint< tFactors > * pNewBorderPoint =
				new nBorder::cPoint< tFactors >( pIntersection->getBase() );
			
			//check if a border point for the position allready exists
			typename typeSetOfPoints::iterator itrNewPoint =
				setBorderPoints.find( pNewBorderPoint );
			
			if ( itrNewPoint == setBorderPoints.end() ){
				//no border point on the position found/exists -> new border point
				(*itrLineIntersInequi)->addContainedPoint( pNewBorderPoint );
				setNewPointsOnHyperplane.insert( pNewBorderPoint );
				
				setBorderPoints.insert( pNewBorderPoint );
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
				cout<<"adding new border point on inequiation for body: "<<endl;
				nDebug::printVector( cout, pNewBorderPoint->vecPointPosition );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
			}else{//point with this position allready exists
				(*itrLineIntersInequi)->addContainedPoint( *itrNewPoint );
				
				if ( setNewPointsOnHyperplane.find( *itrNewPoint ) ==
						setNewPointsOnHyperplane.end() ){
					//no new point -> the point was on the inequiation befor
					setPointsOnInequiation.insert( *itrNewPoint );
				}
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
				else{
					cerr<<"Error: Point was added befor as new for hyperplane "<<
						"(lines in hyperbody can't be correct)."<<endl;
				}
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
				
				delete pNewBorderPoint;
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
				cout<<"connecting existing border point on inequiation: "<<endl;
				nDebug::printVector( cout, (*itrNewPoint)->vecPointPosition );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
			}
			delete pIntersection;
		}
	
		//find all border lines betwaen the points on the inequiation hyperplane
		bool bNewPointsCreated = (! setNewPointsOnHyperplane.empty() );
		setNewPointsOnHyperplane.insert( setPointsOnInequiation.begin(),
			setPointsOnInequiation.end() );
		
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
		cout<<"find all hyperplanes the "<<setNewPointsOnHyperplane.size()<<
			" points on the new hyperplane are on"<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
		/* find all hyperplanes the points on the new hyperplane are on*/
		/*the map of the hyperplanes the points on the hyperplane for the
		inequiation are contained in
			key: the point on the hyperplane for the inequiation
			value: a set of the hyperplanes the point is contained in*/
		typedef map< nBorder::cPoint< tFactors > *, set< nBorder::cHyperplaneData< tFactors > * > >
			typeMapHyperplanesForPoints;
		typeMapHyperplanesForPoints mapHyperplanesForPoints;
#ifdef FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_NO_DOUBLE_POINTS
		typedef map< set< nBorder::cHyperplaneData< tFactors > * >, nBorder::cPoint< tFactors > * >
			typeMapPointsForHyperplanes;
		typeMapPointsForHyperplanes mapPointsForHyperplanes;

#endif //FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_NO_DOUBLE_POINTS
		for ( typename set< nBorder::cPoint< tFactors > * >::iterator
				itrPointOnHyperplane = setNewPointsOnHyperplane.begin();
				itrPointOnHyperplane != setNewPointsOnHyperplane.end();
				itrPointOnHyperplane++ ){
			
			pair< typename typeMapHyperplanesForPoints::iterator, bool >
				paInsertPoint = mapHyperplanesForPoints.insert( make_pair(
				(*itrPointOnHyperplane), set< nBorder::cHyperplaneData< tFactors > * >() ) );
			
			set< nBorder::cLine< tFactors > * > & setContainedLinesByPoint =
				(*itrPointOnHyperplane)->setContainingLines;
			
			set< nBorder::cHyperplaneData< tFactors > * > &
				setHyperplanesForPoint = paInsertPoint.first->second;
			//add hyperplanes for the point
			for ( typename set< nBorder::cLine< tFactors > * >::iterator
					itrLineForPoint = setContainedLinesByPoint.begin();
					itrLineForPoint != setContainedLinesByPoint.end();
					itrLineForPoint++ ){
				
				setHyperplanesForPoint.insert(
					(*itrLineForPoint)->setContainingHyperplanes.begin(),
					(*itrLineForPoint)->setContainingHyperplanes.end() );
			}
#ifdef FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_NO_DOUBLE_POINTS
			/*check if a new point with the same set of hyperplanes exists
			->if yes -> remove the point which is new created (or don't
			remove a point in the old hyperplane body [this are the points
			of setPointsOnInequiation] )*/
			typename typeMapPointsForHyperplanes::iterator
				itrSameHyperplanes = mapPointsForHyperplanes.find( setHyperplanesForPoint );
			if ( itrSameHyperplanes == mapPointsForHyperplanes.end() ){
				//no such point exists -> add it
				mapPointsForHyperplanes.insert( make_pair(
					setHyperplanesForPoint, (*itrPointOnHyperplane) ) );
			}else{
				/*a point for this hyperplanes allredy exists
				-> delete one of the points (if possible the newly created one)*/
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
				cout<<"An point "<<itrSameHyperplanes->second<<" with same hyperplanes as "<<
					(*itrPointOnHyperplane)<<" exists; deletinge one of the points"<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
				nBorder::cPoint< tFactors > * pToDeletePoint = NULL;
				typename set< nBorder::cPoint< tFactors > * >::const_iterator
					itrPointOnInequiation = setPointsOnInequiation.find(
						(*itrPointOnHyperplane) );
				if ( itrPointOnInequiation == setPointsOnInequiation.end() ){
					//the created point is an new point -> take it point to delete
					pToDeletePoint = (*itrPointOnHyperplane);
				}else{//the created point is an old point -> take other point to delete
					pToDeletePoint = itrSameHyperplanes->second;
					
					itrSameHyperplanes->second = (*itrPointOnHyperplane);
				}
				//delete the point
				mapHyperplanesForPoints.erase( pToDeletePoint );
				setBorderPoints.erase( pToDeletePoint );
				setPointsOnInequiation.erase( pToDeletePoint );
				
				typename list< nBorder::cPoint< tFactors > * >::iterator
					itrToDeletePointNotInBody = find(
						liPointsNotInNewBody.begin(), liPointsNotInNewBody.end(),
						pToDeletePoint );
				
				if ( itrToDeletePointNotInBody != liPointsNotInNewBody.end() ){
					//point in list of not to delete points (should not happen)
					liPointsNotInNewBody.erase( itrToDeletePointNotInBody );
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
					cerr<<"Error: Deleting point "<<pToDeletePoint<<" outside body ,"<<
						" because a point for same hyperplanes exists"<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
				}
				
				delete pToDeletePoint;
			}
			
#endif //FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_NO_DOUBLE_POINTS
		}
#ifdef FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_NO_DOUBLE_POINTS
		//not needed anymore
		mapPointsForHyperplanes.clear();
		setNewPointsOnHyperplane.clear();
#endif //FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_NO_DOUBLE_POINTS
		
		if ( ( ! bNewPointsCreated ) && ( ! mapHyperplanesForPoints.empty() ) ){
			/*if no new points wher created
			-> the hyperplane for the inequiation is identical to an other hyperplane
			-> no new lines are needed
			-> connect the new inequiations to the other hyperplane and delete
			created hyperplane*/
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
			cout<<"no new points wher created"<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
			/*find hyperplane wich is identical to the new hyperplane (this
			hyperplane is has an inequiation wher the constant sign is
			switched [the anti inequiation] )*/
			nBorder::cHyperplaneData< tFactors > * pAntiHyperplane = NULL;
			
			for ( typename set< nBorder::cHyperplaneData< tFactors > * >::iterator
					itrBorderHyperplane = setBorders.begin();
					itrBorderHyperplane != setBorders.end();
					itrBorderHyperplane++ ){
				
				const nBorder::cInequationData< tFactors > * pInequiationHyperplane =
					(*itrBorderHyperplane)->pInequiation;
				if ( pInequiationHyperplane ){
					if ( inequiation.antiInequiation(
							pInequiationHyperplane->inequiation ) ){
						
						pAntiHyperplane = *itrBorderHyperplane;
						break;//anti hyperplane found
					}
				}
			}
			if ( pAntiHyperplane ){
				/*one hyperplane for all lines exists
				-> it has to be the same as for the actual inequiation
				-> delete created hyperplane and connect inequiation with found hyperplane*/
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
				cout<<"one hyperplane for all lines exists -> connect the new "<<
					"inequiation to the hyperplane all points on inequiations are also on"<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
				delete pNewHyperplane;
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
				cout<<"connecting hyperplane "<<pAntiHyperplane<<" with inequiation "<<pNewInequiation<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
				pAntiHyperplane->pInequiationTwo = pNewInequiation;
				pNewInequiation->pHyperplane = pAntiHyperplane;
			}else{//error: no anti hyperplane found
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
				cerr<<"Error: no anti hyperplane found "<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
				bNewPointsCreated = true;
			}
		}else if ( ( ! bNewPointsCreated ) && mapHyperplanesForPoints.empty() ){
			//Error: no points on new hyperplane
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
			cerr<<"Error: no points on new hyperplane "<<pNewInequiation<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
			liInequiations.erase( find(
				liInequiations.begin(), liInequiations.end(), pNewInequiation ) );
			delete pNewInequiation;
			delete pNewHyperplane;
			return false;
		}
		if ( bNewPointsCreated ){
			/*if new points wher created->
			connect new intersection(/border) points on the hyperplane to the
			inequiation with (border) lines, wich create an konvex body*/
			setBorders.insert( pNewHyperplane );
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
			cout<<"find all border lines betwean the "<<mapHyperplanesForPoints.size()<<
				" points on the inequiation hyperplane"<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE

#ifdef DEBUG_ADD_INEQUIATION_SIMPLE_2
			unsigned long ulHyperplanesForPointsSize = mapHyperplanesForPoints.size();
			typename typeMapHyperplanesForPoints::iterator
				itrOnHyperplaneBegin = mapHyperplanesForPoints.begin();
			typename typeMapHyperplanesForPoints::iterator
				itrOnHyperplaneEnd = mapHyperplanesForPoints.end();
				
			cout<<endl<<endl<<"points on new inequiation: "<<ulHyperplanesForPointsSize<<endl;
			cout<<"finding lines betwean points wich fulfill (="<<
				liPointsInNewBody.size()<<") and which don't fulfill (="<<
				liPointsNotInNewBody.size()<<") the new inequiation (on inequiation "<<
				setPointsOnInequiation.size()<<" points)"<<endl;
			
			cout<<"hyperbody:"<<endl;
			print( cout );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE_2

			for ( typename typeMapHyperplanesForPoints::iterator
					itrPoint1OnHyperplane = mapHyperplanesForPoints.begin();
					itrPoint1OnHyperplane != mapHyperplanesForPoints.end();
					itrPoint1OnHyperplane++ ){
				
				typename typeMapHyperplanesForPoints::iterator
					itrPoint2OnHyperplane = itrPoint1OnHyperplane;
				itrPoint2OnHyperplane++;
				
				for ( ; itrPoint2OnHyperplane != mapHyperplanesForPoints.end();
						itrPoint2OnHyperplane++ ){
					
					nBorder::cPoint< tFactors > * pBorderPoint1 =
						itrPoint1OnHyperplane->first;
					nBorder::cPoint< tFactors > * pBorderPoint2 =
						itrPoint2OnHyperplane->first;
					//for all two different points on the inequiation hyperplane
					if ( ( setPointsOnInequiation.find( pBorderPoint1 ) !=
							setPointsOnInequiation.end() ) &&
							( setPointsOnInequiation.find( pBorderPoint2 ) !=
							setPointsOnInequiation.end() ) ){
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
						cout<<"both points ("<<pBorderPoint1<<" and "<<
							pBorderPoint2<<") wher in the old body"<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
						/*if both points wher in the old body
						-> add line wich contains both points to new hyperplane*/
						set< nBorder::cLine< tFactors > * > & setContainingLinesPoint1 =
							pBorderPoint1->setContainingLines;
						set< nBorder::cLine< tFactors > * > & setContainingLinesPoint2 =
							pBorderPoint2->setContainingLines;
						//all lines of the point intersect the hyperplane
						for ( typename set< nBorder::cLine< tFactors > * >::iterator
								itrContainingLinePoint1 = setContainingLinesPoint1.begin();
								itrContainingLinePoint1 != setContainingLinesPoint1.end();
								itrContainingLinePoint1++ ){
							
							if ( setContainingLinesPoint2.find( *itrContainingLinePoint1 ) !=
									setContainingLinesPoint2.end() ){
								//line connecting both points -> add it to new hyperplane
								pNewHyperplane->addContainedLine( *itrContainingLinePoint1 );
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
								cout<<"add line "<<*itrContainingLinePoint1<<
									" betwean "<<pBorderPoint1<<" and "<<
									pBorderPoint2<<" as contained in new hyperplane"<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
								break;//done
							}
						}
						continue;//check next itrPoint2OnHyperplane
					}//end/else if both points wher in the old body
					/*check if the points have uiDimensions - 1 hyperplanes in common*/
					set< nBorder::cHyperplaneData< tFactors > * > &
						containigHyperplanes1 = itrPoint1OnHyperplane->second;
					set< nBorder::cHyperplaneData< tFactors > * > &
						containigHyperplanes2 = itrPoint2OnHyperplane->second;
					
					/*find hyperplenes wich are the same in both*/
					list< nBorder::cHyperplaneData< tFactors > * > liSameHyperplanes;
					for ( typename set< nBorder::cHyperplaneData< tFactors > * >::iterator
							itrHyperplane = containigHyperplanes1.begin();
							itrHyperplane != containigHyperplanes1.end(); itrHyperplane++ ){
						
						if ( containigHyperplanes2.find( *itrHyperplane ) !=
								containigHyperplanes2.end() ){
							//hyperplane found -> equal hyperplane in both
							liSameHyperplanes.push_back( *itrHyperplane );
						}
					}
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
					cout<<"the points ("<<pBorderPoint1<<" and "<<
						pBorderPoint2<<") have "<<liSameHyperplanes.size()<<
						" common containing hyperplanes"<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
					if ( ( this->uiDimensions - 2 ) <= liSameHyperplanes.size() ){
						/*minimal (uiDimensions - 2) other hyperplanes are the same for both points
						-> points are connected by an border line on the new hyperplane
						-> create new border line for the points*/
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
						cout<<"connectiong points with new line"<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
#ifdef FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_NO_DOUBLE_POINTS
						/*TODO?? check if a new line for the same hyperplanes exists
						-> if yes don't create the line and add the border points to the existing line*/
						
						
						
						
						
#endif //FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_NO_DOUBLE_POINTS
						
						nBorder::cLine< tFactors > * pNewBorderLine =
							new nBorder::cLine< tFactors >( *pBorderPoint1, *pBorderPoint2 );
						setBorderLines.insert( pNewBorderLine );
						
						
						/*add the new line as contained in the intersection hyperplane and
						the other hyperplanes*/
						pNewHyperplane->addContainedLine( pNewBorderLine );
						//add line to all same hyperplanes of the points
						for ( typename list< nBorder::cHyperplaneData< tFactors > * >::iterator
								itrHyperplane = liSameHyperplanes.begin();
								itrHyperplane != liSameHyperplanes.end(); itrHyperplane++ ){
							
							(*itrHyperplane)->addContainedLine( pNewBorderLine );
						}
					}//end if minimal (uiDimensions - 2) other hyperplanes are the same for both points
				}//end for itrPoint2OnHyperplane
			}//end for itrPoint1OnHyperplane
			
		}//end if new points wher created

	}else{// if ( uiDimensions == 1 )
		/* borders are all points;
		space of body is in an line
		-> add created hyperplane as border line and border point and
		delete border point outside of the body*/
		//add border line
		setBorders.insert( pNewHyperplane );
		
		nBorder::cLine< tFactors > * pNewBorderLine =
			new nBorder::cLine< tFactors >();
		pNewBorderLine->hyperplane = pNewHyperplane->hyperplane;
		pNewHyperplane->addContainedLine( pNewBorderLine );
		setBorderLines.insert( pNewBorderLine );
		//add border point
		nBorder::cPoint< tFactors > * pNewBorderPoint =
			new nBorder::cPoint< tFactors >( pNewHyperplane->hyperplane.getBase() );
		pNewBorderLine->addContainedPoint( pNewBorderPoint );
		setBorderPoints.insert( pNewBorderPoint );
	}//end if uiDimensions

#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
	cout<<endl<<"body befor removing 2 (points to remove "<<liPointsNotInNewBody.size()<<"): "<<endl;
	print( cout );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE

	//remove all points outside the new body
	set< nBorder::cLine< tFactors > * > setCheckToRemoveLines;
	for ( typename list< nBorder::cPoint< tFactors > * >::iterator
			itrPointNotInNewBody = liPointsNotInNewBody.begin();
			itrPointNotInNewBody != liPointsNotInNewBody.end(); itrPointNotInNewBody++ ){
		
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
		cout<<endl<<"removing border point: "<<(*itrPointNotInNewBody)<<endl<<flush;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
		setCheckToRemoveLines.insert(
			(*itrPointNotInNewBody)->setContainingLines.begin(),
			(*itrPointNotInNewBody)->setContainingLines.end() );
		
		setBorderPoints.erase( *itrPointNotInNewBody );
		delete (*itrPointNotInNewBody);
	}
	
	/*TODO??? remove middle points of new lines with tree points on them*/
	
	//remove all lines without points
	set< nBorder::cHyperplaneData< tFactors > * > setCheckToRemoveHyperplanes;
	for ( typename set< nBorder::cLine< tFactors > * >::iterator
			itrBorderLine = setCheckToRemoveLines.begin();
			itrBorderLine != setCheckToRemoveLines.end(); itrBorderLine++ ){
		
		if ( (*itrBorderLine)->setContainedPoints.empty() ){
			//no border points for border line -> remove it
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
			cout<<endl<<"removing border line: "<<(*itrBorderLine)<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
			setCheckToRemoveHyperplanes.insert(
				(*itrBorderLine)->setContainingHyperplanes.begin(),
				(*itrBorderLine)->setContainingHyperplanes.end() );
			
			setBorderLines.erase( *itrBorderLine );
			delete (*itrBorderLine);
		}
	}
	
	//remove all hyperplanes without lines
	for ( typename set< nBorder::cHyperplaneData< tFactors > * >::iterator
			itrHyperplane = setCheckToRemoveHyperplanes.begin();
			itrHyperplane != setCheckToRemoveHyperplanes.end();
			itrHyperplane++ ){
		
		if ( (*itrHyperplane)->setContainedLines.empty() ){
			//no border lines for border hyperplane -> remove it
			nBorder::cInequationData< tFactors > * pInequiation =
				(*itrHyperplane)->pInequiation;
			if ( pInequiation ){
				//delete inequiation for the hyperplane
				liInequiations.erase( find(
					liInequiations.begin(), liInequiations.end(), pInequiation ) );
				delete pInequiation;
			}
			nBorder::cInequationData< tFactors > * pInequiationTwo =
				(*itrHyperplane)->pInequiationTwo;
			if ( pInequiationTwo ){
				//delete second inequiation for the hyperplane
				liInequiations.erase( find(
					liInequiations.begin(), liInequiations.end(), pInequiationTwo ) );
				delete pInequiationTwo;
			}
			
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
			cout<<endl<<"removing border hyperplane: "<<(*itrHyperplane)<<endl;
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
			setBorders.erase( *itrHyperplane );
			delete (*itrHyperplane);
		}
	}
	
#ifdef DEBUG_ADD_INEQUIATION_SIMPLE
	cout<<endl<<"body after removing: "<<endl;
	print( cout );
#endif //DEBUG_ADD_INEQUIATION_SIMPLE
	
	return true;
}


#endif //FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_SAVE_ON_BIG_NUMBERS


/**
 * @return a vector with the borderpoints of the body
 */
template< class tFactors > unsigned long
		cHyperplaneBodySimple<tFactors>::getNumberOfBorderPoints() const{
	
	return setBorderPoints.size();
}


/**
 * @return a vector with the borderpoints of the body
 */
template< class tFactors > vector< vector< tFactors > >
		cHyperplaneBodySimple<tFactors>::getBorderPoints() const{
	
	if ( setBorders.empty() ){
		return vector< vector< tFactors > >();
	}
	vector< vector< tFactors > > vecBorderPoints( setBorderPoints.size() );
	
	size_t uiActualPoint = 0;
	for ( typename set< nBorder::cPoint< tFactors > * >::const_iterator
			itrBorderPoint = setBorderPoints.begin();
			itrBorderPoint != setBorderPoints.end();
			itrBorderPoint++, uiActualPoint++ ){
		
		vecBorderPoints[ uiActualPoint ] = (*itrBorderPoint)->vecPointPosition;
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
template< class tFactors > bool cHyperplaneBodySimple<tFactors>::isPart(
		const vector< tFactors > & vecPoint ) const{
	
#ifdef FEATURE_HYPERPLANE_BODY_SIMPLE_OPTIMIZE_IS_PART_INEQUIATIONS
	list< nBorder::cInequationData< tFactors > * > * pLiInequiations =
		const_cast< list< nBorder::cInequationData< tFactors > * > * >(&liInequiations);
	//check if the point fullfill all inequiations of this hyperplane
	for ( typename list< nBorder::cInequationData< tFactors > * >::iterator
			itrInequiation = pLiInequiations->begin();
			itrInequiation != pLiInequiations->end(); itrInequiation++ ){
		
		if ( ! (*itrInequiation)->inequiation.evalue( vecPoint ) ){
			//point dosn't fulfill the inequiation -> point not in body
			/*push inequiation to the front of the inequiation list, so it
			will be checked sooner in the next isPart() run*/
			nBorder::cInequationData< tFactors > * pInequiation =
				(*itrInequiation);
			
			pLiInequiations->erase( itrInequiation );
			pLiInequiations->push_front( pInequiation );
			
			return false;
		}
	}//else point fulfill all inequiations -> point in body
	
#else //FEATURE_HYPERPLANE_BODY_SIMPLE_OPTIMIZE_IS_PART_INEQUIATIONS

	//check if the point fullfill all inequiations of this hyperplane
	for ( typename list< nBorder::cInequationData< tFactors > * >::const_iterator
			itrInequiation = liInequiations.begin();
			itrInequiation != liInequiations.end(); itrInequiation++ ){
		
		if ( ! (*itrInequiation)->inequiation.evalue( vecPoint ) ){
			//point dosn't fulfill the inequiation -> point not in body
			return false;
		}
	}//else point fulfill all inequiations -> point in body
#endif //FEATURE_HYPERPLANE_BODY_SIMPLE_OPTIMIZE_IS_PART_INEQUIATIONS
	return true;
}



/**
 * This method print the hyperplane in a readebel form to the given
 * output stream outputSream.
 *
 * @param outputSream the stream wher to print this inequiation to
 */
template< class tFactors > void cHyperplaneBodySimple<tFactors>::print(
		ostream & outputStream ) const{
	
	//print all inequiations for this body
	outputStream<<endl<<"Inequiations:"<<endl;
	for ( typename list< nBorder::cInequationData< tFactors > * >::const_iterator
			itrInequiation = liInequiations.begin();
			itrInequiation != liInequiations.end(); itrInequiation++ ){
		
		(*itrInequiation)->inequiation.print( outputStream );
#ifdef DEBUG_NEEDED_HYPERPLANE_BODY_SIMPLE
			outputStream<<"   "<<(*itrInequiation)<<" for hyperplane "<<(*itrInequiation)->pHyperplane<<endl;
#endif//DEBUG_NEEDED_HYPERPLANE_BODY_SIMPLE
	}
	
	//print all border hyperplanes
	outputStream<<endl<<"Hyperplanes (dimensionality="<<(this->uiDimensions-1)<<"):"<<endl;
	
	for ( typename set< nBorder::cHyperplaneData< tFactors > * >::const_iterator
			itrHyperplane = setBorders.begin();
			itrHyperplane != setBorders.end(); itrHyperplane++ ){
		
		(*itrHyperplane)->hyperplane.print( outputStream );
		
#ifdef DEBUG_NEEDED_HYPERPLANE_BODY_SIMPLE
		outputStream<<(*itrHyperplane)<<" for inequiation "<<
			(*itrHyperplane)->pInequiation<<" and "<<((*itrHyperplane)->pInequiationTwo)<<" contained lines: ";
		
		for ( typename set< nBorder::cLine< tFactors > * >::const_iterator
				itrContainedLine = (*itrHyperplane)->setContainedLines.begin();
				itrContainedLine != (*itrHyperplane)->setContainedLines.end();
				itrContainedLine++ ){
			
			outputStream<<(*itrContainedLine)<<", ";
		}
#endif //DEBUG_NEEDED_HYPERPLANE_BODY_SIMPLE
		
		outputStream<<endl;
	}
	//print all border lines
	outputStream<<endl<<"Border lines:"<<endl;
	
	for ( typename set< nBorder::cLine< tFactors > * >::const_iterator
			itrBorderLine = setBorderLines.begin();
			itrBorderLine != setBorderLines.end(); itrBorderLine++ ){
		
		(*itrBorderLine)->hyperplane.print( outputStream );
		
#ifdef DEBUG_NEEDED_HYPERPLANE_BODY_SIMPLE
		outputStream<<(*itrBorderLine)<<" contained points: ";
		
		for ( typename set< nBorder::cPoint< tFactors > * >::const_iterator
				itrContainedPoint = (*itrBorderLine)->setContainedPoints.begin();
				itrContainedPoint != (*itrBorderLine)->setContainedPoints.end();
				itrContainedPoint++ ){
			
			outputStream<<(*itrContainedPoint)<<", ";
		}
		outputStream<<" contained in hyperplanes: ";
		
		for ( typename set< nBorder::cHyperplaneData< tFactors > * >::const_iterator
				itrContainingHyperplane = (*itrBorderLine)->setContainingHyperplanes.begin();
				itrContainingHyperplane != (*itrBorderLine)->setContainingHyperplanes.end();
				itrContainingHyperplane++ ){
			
			outputStream<<(*itrContainingHyperplane)<<", ";
		}
#endif //DEBUG_NEEDED_HYPERPLANE_BODY_SIMPLE
		
		outputStream<<endl;
	}
	
	//print all border points
	outputStream<<endl<<"Points:"<<endl;
	
	for ( typename set< nBorder::cPoint< tFactors > * >::const_iterator
			itrBorderPoint = setBorderPoints.begin();
			itrBorderPoint != setBorderPoints.end(); itrBorderPoint++ ){
		
		const vector< tFactors > & vectorPosition =
			(*itrBorderPoint)->vecPointPosition;
		
		outputStream<<"( ";
		for ( unsigned int uiDimension = 0; uiDimension < vectorPosition.size();
				uiDimension++ ){
			
			outputStream<< vectorPosition[ uiDimension ] <<", ";
		}
		outputStream<<")^T"<<endl;
		
#ifdef DEBUG_NEEDED_HYPERPLANE_BODY_SIMPLE
		outputStream<<(*itrBorderPoint)<<" contained in lines: ";
		
		for ( typename set< nBorder::cLine< tFactors > * >::const_iterator
				itrContainingLine = (*itrBorderPoint)->setContainingLines.begin();
				itrContainingLine != (*itrBorderPoint)->setContainingLines.end();
				itrContainingLine++ ){
			
			outputStream<<(*itrContainingLine)<<", ";
		}
#endif //DEBUG_NEEDED_HYPERPLANE_BODY_SIMPLE
		
		outputStream<<endl;
	}

}


/**
 * This method duplicates this whole hyperplane body.
 *
 * @return the cloned/ duplicates hyperplane body
 */
template< class tFactors > cHyperplaneBodySimple< tFactors > *
		cHyperplaneBodySimple< tFactors >::clone() const{
	
	return new cHyperplaneBodySimple< tFactors >( *this );
}



#endif //___C_HYPERPLANE_BODY_SIMPLE_CPP__



