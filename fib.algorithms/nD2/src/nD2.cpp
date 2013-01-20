/**
 * @file nD2
 * file name: nD2.cpp
 * @author Betti Oesterholz
 * @date 30.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies functions for a two dimensional data.
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
 * This header specifies functions for a two dimensional data.
 *
 */
/*
History:
30.06.2010  Oesterholz  created
18.02.2011  Oesterholz  in createAreasForPoints() it will be tried to
	convert the biggest area and than the areas befor, if biggest area
	couldn't be used
20.02.2011  Oesterholz  function createSplineBorderAreasForPoints() added
06.03.2011  Oesterholz  function createSplineItrFastBorderAreasForPoints() added
27.03.2011  Oesterholz  createAreaFibObject() and createLineFibObject()
	handling of constant polynoms optimized;
	createSplineItrFastBorderAreasForPoints() parameter pOutSetMissingPoints added;
	the created area objects will be checked, if the variables are set to
	the data points in the area and not with the given subobject
06.07.2011  Oesterholz  functions createNSplineBorderAreasForPoints() added
24.09.2012  Oesterholz  FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING:
	evalueSpline(): the glp library (extern package) linear solver will be
	used to find a spline for a vector of range data points
06.01.2013  Oesterholz  FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING:
	evalueSplineIterativFast(): the glp library (extern package) linear
	solver will be used to find a spline for a vector of range data points
*/




#include "../incl/nD2.h"

#ifndef ___N_D2_CPP__
#define ___N_D2_CPP__

#include "cFibElement.h"
#include "cArea.h"
#include "cFunction.h"
#include "cList.h"
#include "cPoint.h"
#include "cFibVariable.h"
#include "cVectorArea.h"
#include "cUnderFunction.h"
#include "cFunctionAdd.h"
#include "cFunctionValue.h"
#include "cFunctionVariable.h"
#include "cEvaluePositionListLimit.h"

#include "../nD1/incl/cDataPointRange.h"
#include "../nD1/incl/cPolynomRange.h"
#include "../nD1/incl/cPolynom.h"
#include "../nD1/incl/cSpline.h"

#include <iostream>
#include <map>
#include <list>


/*debugging:
#define DEBUG
#define DEBUG_N_D2
#define DEBUG_N_D2_2
#undef ___DEBUG_OUT_H__
#include "debugOut.inc"
*/

/**
 * The save boundery for error.
 * Errors will just be counted if ther are greater than this save boundery.
 */
#define SAVE_BOUNDERY 0.0000000001

using namespace std;
using namespace fib::algorithms::nD2;


namespace fib{
namespace algorithms{
namespace nD2{

	/**
	 * @param dataPoint1 the first datapoint to compare with
	 * @param dataPoint2 the second datapoint to compare with
	 * @return true if the x position of the first point is lower than that of
	 * 	the second point, and if the x position are equal, true if the y
	 * 	position of the first point is lower than that of the second point
	 */
	template <class tX, class tY, class tZ>
	bool lowerPosition( fib::algorithms::nD2::cDataPoint<tX, tY, tZ> dataPoint1,
			fib::algorithms::nD2::cDataPoint<tX, tY, tZ> dataPoint2 ){
	
		return (dataPoint1.x < dataPoint2.x) || (dataPoint1.y < dataPoint2.y);
	}
	
	/**
	 * Help functor structur to sort the areas
	 */
	template< class tSecond > struct structLowerFirstElement{
		
		bool operator() ( const pair< unsigned long, tSecond > & paFirst,
				const pair< unsigned long, tSecond > & paSecond ) const{
			return ( paFirst.first < paSecond.first );
		}
		
	};

	const double D_HALF_ROW = ((double)(0.49));

	
	/**
	 * This function returns a list with the border ranges of the given area.
	 *
	 * @param toConvertArea the area for which to find the borders
	 * @param bChoosenDirection the direction in which the points of the area
	 * 	are ordered and for wich to find the border ranges (x = true; y = false)
	 * @param setMaximumXArea in x direction ordered points, which can be
	 * 	included in the border range
	 * @param setMaximumXArea in y direction ordered points, which can be
	 * 	included in the border range
	 * @param vecOutRangesLower a output vector for the range points of the
	 * 	lower border (border with lower values)
	 * @param vecOutRangesUpper a output vector for the range points of the
	 * 	upper border (border with higher values)
	 * @return the evalued vecOutRangesLower and vecOutRangesUpper, plus
	 * 	a bool value if the ranges are equal (true if equal, else false)
	 */
	template< class tX >
	bool findBorderRanges( const pair< unsigned long, list< pair<
				typename fib::algorithms::nD1::cDataPoint<tX, tX>,
				typename fib::algorithms::nD1::cDataPoint<tX, tX> > > > & toConvertArea,
			const bool bChoosenDirection,
			const set< typename fib::algorithms::nD1::cDataPoint<tX, tX> > & setMaximumXArea,
			const set< typename fib::algorithms::nD1::cDataPoint<tX, tX> > & setMaximumYArea,
			vector< typename fib::algorithms::nD1::cDataPointRange< tX, double > > & vecOutRangesLower,
			vector< typename fib::algorithms::nD1::cDataPointRange< tX, double > > & vecOutRangesUpper ){
		
		typedef fib::algorithms::nD1::cDataPoint<tX, tX> typeDataPoint;
		typedef set< typeDataPoint > typeSetDataPoints;
		typedef typename typeSetDataPoints::const_iterator typeConstItrSetDataPoints;
		typedef typename typeSetDataPoints::const_reverse_iterator typeConstRevItrSetDataPoints;
	
		typedef list< pair< typeDataPoint, typeDataPoint > > typeDataPointList;
		typedef typename typeDataPointList::const_iterator typeItrDataPointList;
		
		bool bBordersEqual = true;
		
		for ( typeItrDataPointList itrDataPoint = toConvertArea.second.begin();
				itrDataPoint != toConvertArea.second.end(); itrDataPoint++ ){
			//find the minimum value for the range in the max area
			double dMinY;
			typeDataPoint dataPoint2( itrDataPoint->first );
			if ( bChoosenDirection ){
				//search in x dirction
				const typeConstItrSetDataPoints itrXPointMax =
					setMaximumXArea.find( dataPoint2 );
				if ( itrXPointMax != setMaximumXArea.end() ){
					//search for the maximal beginning of this line
					typeConstRevItrSetDataPoints itrXPointRev( itrXPointMax );
					for ( ; itrXPointRev != setMaximumXArea.rend();
							itrXPointRev++, dataPoint2.y-- ){
						
						if ( (*itrXPointRev) != dataPoint2 ){
							//the x position has changed -> new line
							itrXPointRev--;//go to last line
							break;
						}
					}
					if ( itrXPointRev == setMaximumXArea.rend() ){
						itrXPointRev--;//go to last line
					}
					dMinY = ((double)(itrXPointRev->y)) - D_HALF_ROW;
				}else{//error: the minimum set contaions points not in the maximum set
					dMinY = ((double)(dataPoint2.y)) - D_HALF_ROW;
				}
			}else{
				//search in y dirction
				const typeConstItrSetDataPoints itrYPointMax =
					setMaximumYArea.find( dataPoint2 );
				if ( itrYPointMax != setMaximumYArea.end() ){
					//search for the maximal beginning of this line
					typeConstRevItrSetDataPoints itrYPointRev( itrYPointMax );
					for ( ; itrYPointRev != setMaximumYArea.rend();
							itrYPointRev++, dataPoint2.y-- ){
						
						if ( (*itrYPointRev) != dataPoint2 ){
							//the x position has changed -> new line
							itrYPointRev--;//go to last line
							break;
						}
					}
					if ( itrYPointRev == setMaximumYArea.rend() ){
						itrYPointRev--;//go to last line
					}
					dMinY = ((double)(itrYPointRev->y)) - D_HALF_ROW;
				}else{//error: the minimum set contaions points not in the maximum set
					dMinY = ((double)(dataPoint2.y)) - D_HALF_ROW;
				}
			}
			vecOutRangesLower.push_back( fib::algorithms::nD1::cDataPointRange< tX, double >(
				itrDataPoint->first.x,
				dMinY, ((double)(itrDataPoint->first.y)) + D_HALF_ROW ) );
			
			
			//find the maximum value for the range in the max area
			double dMaxY;
			dataPoint2 = itrDataPoint->second;
			if ( bChoosenDirection ){
				//search in x dirction
				typeConstItrSetDataPoints itrXPointMax =
					setMaximumXArea.find( dataPoint2 );
				if ( itrXPointMax != setMaximumXArea.end() ){
					//search for the maximal beginning of this line
					for ( ; itrXPointMax != setMaximumXArea.end();
							itrXPointMax++, dataPoint2.y++ ){
						
						if ( (*itrXPointMax) != dataPoint2 ){
							//the x position has changed -> new line
							itrXPointMax--;//go to last line
							break;
						}
					}
					if ( itrXPointMax == setMaximumXArea.end() ){
						itrXPointMax--;//go to last line
					}
					dMaxY = ((double)(itrXPointMax->y)) + D_HALF_ROW;
				}else{//error: the minimum set contaions points not in the maximum set
					dMaxY = ((double)(dataPoint2.y)) + D_HALF_ROW;
				}
			}else{
				//search in y dirction
				typeConstItrSetDataPoints itrYPointMax =
					setMaximumYArea.find( dataPoint2 );
				if ( itrYPointMax != setMaximumYArea.end() ){
					//search for the maximal beginning of this line
					for ( ; itrYPointMax != setMaximumYArea.end();
							itrYPointMax++, dataPoint2.y++ ){
						
						if ( (*itrYPointMax) != dataPoint2 ){
							//the x itrYPointMax has changed -> new line
							itrYPointMax--;//go to last line
							break;
						}
					}
					if ( itrYPointMax == setMaximumYArea.end() ){
						itrYPointMax--;//go to last line
					}
					dMaxY = ((double)(itrYPointMax->y)) + D_HALF_ROW;
				}else{//error: the minimum set contaions points not in the maximum set
					dMaxY = ((double)(dataPoint2.y)) + D_HALF_ROW;
				}
			}
			vecOutRangesUpper.push_back( fib::algorithms::nD1::cDataPointRange< tX, double >(
				itrDataPoint->first.x,
				((double)(itrDataPoint->second.y)) - D_HALF_ROW, dMaxY ) );
			
			if ( bBordersEqual &&
					( ! vecOutRangesLower.back().equal( vecOutRangesUpper.back() ) ) ){
				//the borders are not equal
				bBordersEqual = false;
			}
		}
		return bBordersEqual;
	}
	
	
	/**
	 * This function creates an Fib object for the given area.
	 * The created fib object contains one point object, wich
	 * positions element variables are set to the data points in the area.
	 *
	 * @param bChoosenDirection the direction in wich the given polynoms
	 * 	are to evalue (true = x direction; false = y direction)
	 * @param ulStartPosition the start position of the area in the given direction
	 * @param ulEndPosition the end position of the area in the given direction
	 * @param polynomLower a polynom for the lower border of the area
	 * @param polynomUpper a polynom for the upper border of the area
	 * @param xOffset the offset in the given directions for the positions
	 * @return a pointer to the created area Fib object;
	 * 	Attention: You have to care that the created Fib object is deleted
	 */
	template< class tX > cArea *
		createAreaFibObject( const bool bChoosenDirection,
			const longFib ulStartPosition, const longFib ulEndPosition,
			const cPolynom< tX, double > & polynomLower,
			const cPolynom< tX, double > & polynomUpper,
			const tX xOffset = 0 ){
		/*create the Fib subobject object "area( fun( fun( area( pUnderobject ))))"
		(for constant polynoms: don't create a funcion element, but include
		value directly in the are boundery)*/
		cVectorPosition vecPosition( 2 );
		cPoint * pPoint = new cPoint( & vecPosition );
		
		//create offset function element
		cArea * pAreaX = NULL;
		cFunction * pFunOffset = NULL;
		cFibVariable * pVariableDirection = NULL;
		
		const long lPolynomLowerLastFactorNotNull =
			polynomLower.getLastFactorIndexNotNull();
		const long lPolynomUpperLastFactorNotNull =
			polynomUpper.getLastFactorIndexNotNull();
		const bool bBothPolynomsConstant =
			( lPolynomLowerLastFactorNotNull <= 0 ) &&
				( lPolynomUpperLastFactorNotNull <= 0 );
		if ( ( xOffset != 0 ) && ( ! bBothPolynomsConstant ) ){
			//offset not 0 and both polynoms not constant -> create offset function
			cVectorArea vectorArea( ulStartPosition, ulEndPosition );
			pAreaX = new cArea( vectorArea );
			pVariableDirection = pAreaX->getDefinedVariable();
			
			cUnderFunction * pOffsetUF = new cFunctionAdd(
				cFunctionValue( xOffset ), cFunctionVariable( pVariableDirection )  );
			pFunOffset = new cFunction( *pOffsetUF );
			if ( pOffsetUF ){
				delete pOffsetUF;
				pOffsetUF = NULL;
			}
			
			pVariableDirection = pFunOffset->getDefinedVariable();
		}else{//no offset function will be created
			cVectorArea vectorArea( ulStartPosition + xOffset, ulEndPosition + xOffset );
			pAreaX = new cArea( vectorArea );
			pVariableDirection = pAreaX->getDefinedVariable();
		}
		
		//create border function elements
		cFunction * pFunUpper = NULL;
		if ( 0 < lPolynomUpperLastFactorNotNull ){
			cUnderFunction * pUpperUF = polynomUpper.toFibUnderFunction(
				pAreaX->getDefinedVariable() );
			pFunUpper = new cFunction( *pUpperUF );
			
			if ( pUpperUF ){
				delete pUpperUF;
			}
		}
		cFunction * pFunLower = NULL;
		if ( 0 < lPolynomLowerLastFactorNotNull ){
			cUnderFunction * pLowerUF = polynomLower.toFibUnderFunction(
				pAreaX->getDefinedVariable() );
			pFunLower = new cFunction( *pLowerUF, pFunUpper );
			
			if ( pLowerUF ){
				delete pLowerUF;
			}
		}
		//create the area for the y direction
		cVectorArea * pVectorAreaY = NULL;
		if ( ( pFunLower != NULL ) && ( pFunUpper != NULL ) ){
			
			pVectorAreaY = new cVectorArea( pFunLower->getDefinedVariable(),
				pFunUpper->getDefinedVariable() );
		}else if ( ( pFunLower == NULL ) && ( pFunUpper != NULL ) ){
			
			pVectorAreaY = new cVectorArea(
				( polynomLower.vecFactors.empty() ? 0 :
					roundToLongFib( polynomLower.vecFactors[ 0 ] ) ),
				pFunUpper->getDefinedVariable() );
		}else if ( ( pFunLower != NULL ) && ( pFunUpper == NULL ) ){
			
			pVectorAreaY = new cVectorArea( pFunLower->getDefinedVariable(),
				( polynomUpper.vecFactors.empty() ? 0 :
					roundToLongFib( polynomUpper.vecFactors[ 0 ] ) ) );
		}else{// if ( ( pFunLower == NULL ) && ( pFunUpper == NULL ) ){
			
			pVectorAreaY = new cVectorArea(
				( polynomLower.vecFactors.empty() ? 0 :
					roundToLongFib( polynomLower.vecFactors[ 0 ] ) ),
				( polynomUpper.vecFactors.empty() ? 0 :
					roundToLongFib( polynomUpper.vecFactors[ 0 ] ) ) );
		}//end if create under area
		
		cArea * pAreaY = new cArea( *pVectorAreaY, pPoint );
		if ( pVectorAreaY ){
			delete pVectorAreaY;
		}
		//connect created Fib elements
		if ( pFunUpper ){
			pFunUpper->insertObjectInElement( pAreaY );
			//if existing function lower is connected to function upper
			
			if ( pFunLower ){
				//connect to function lower
		
				if ( pFunOffset ){
					pFunOffset->insertObjectInElement( pFunLower );
					pAreaX->insertObjectInElement( pFunOffset );
					//now: pAreaX( pFunOffset( pFunLower( pFunUpper( pAreaY( pSubobjectToInsert )))))
				}else{
					pAreaX->insertObjectInElement( pFunLower );
					//now: pAreaX( pFunLower( pFunUpper( pAreaY( pSubobjectToInsert ))))
				}
			}else{//just upper function exists
				if ( pFunOffset ){
					pFunOffset->insertObjectInElement( pFunUpper );
					pAreaX->insertObjectInElement( pFunOffset );
					//now: pAreaX( pFunOffset( pFunUpper( pAreaY( pSubobjectToInsert ))))
				}else{
					pAreaX->insertObjectInElement( pFunUpper );
					//now: pAreaX( pFunUpper( pAreaY( pSubobjectToInsert )))
				}
			}
		}else if ( pFunLower ){
			//no upper function exists, but an lower
			
			pFunLower->insertObjectInElement( pAreaY );
			
			if ( pFunOffset ){
				pFunOffset->insertObjectInElement( pFunLower );
				pAreaX->insertObjectInElement( pFunOffset );
				//now: pAreaX( pFunOffset( pFunLower( pAreaY( pSubobjectToInsert ))))
			}else{
				pAreaX->insertObjectInElement( pFunLower );
				//now: pAreaX( pFunLower( pAreaY( pSubobjectToInsert )))
			}
		}else{//no upper and lower function exists
			pAreaX->insertObjectInElement( pAreaY );
			//now: pAreaX( pAreaY( pSubobjectToInsert ))
		}//end if make connections
		
		cVectorPosition * pVecPosition = pPoint->getPosition();
		if ( bChoosenDirection ){
			
			pVecPosition->setVariable( 1, pVariableDirection );
			pVecPosition->setVariable( 2, pAreaY->getDefinedVariable() );
		}else{//switch x and y variables
			
			pVecPosition->setVariable( 1, pAreaY->getDefinedVariable() );
			pVecPosition->setVariable( 2, pVariableDirection );
		}
		
		return pAreaX;
	}
	
	
	/**
	 * This function creates an Fib object for the given line.
	 * The created fib object contains one point object, wich
	 * positions element variables are set to the data points in the area.
	 *
	 * @param bChoosenDirection the direction in wich the given polynoms
	 * 	are to evalue (true = x direction; false = y direction)
	 * @param ulStartPosition the start position of the area in the given direction
	 * @param ulEndPosition the end position of the area in the given direction
	 * @param polynomLine a polynom for the line
	 * @param xOffset the offset in the given directions for the positions
	 * @return a pointer to the created line Fib object;
	 * 	Attention: You have to care that the created Fib object is deleted
	 */
	template< class tX > cArea *
		createLineFibObject( const bool bChoosenDirection,
			const longFib ulStartPosition, const longFib ulEndPosition,
			const cPolynom< tX, double > & polynomLine,
			const tX xOffset = 0 ){
		/*if bouth polynoms are the same don't use second fun and area;
		create the Fib subobject object "area( fun( ))"*/
		cVectorPosition vecPosition( 2 );
		cPoint * pPoint = new cPoint( & vecPosition );
		
		cArea * pAreaNew = NULL;
		
		cFunction * pFunOffset = NULL;
		cFibVariable * pVariableDirection;
		if ( (xOffset != 0) && ( 0 < polynomLine.getLastFactorIndexNotNull() ) ){
			//create offset function element
			
			cVectorArea vectorArea( ulStartPosition, ulEndPosition );
			pAreaNew = new cArea( vectorArea );
			pVariableDirection = pAreaNew->getDefinedVariable();
			
			//offset not 0 and polynom not constant -> create offset function
			cUnderFunction * pOffsetUF = new cFunctionAdd(
				cFunctionValue( xOffset ), cFunctionVariable( pVariableDirection )  );
			pFunOffset = new cFunction( *pOffsetUF );
			if ( pOffsetUF ){
				delete pOffsetUF;
				pOffsetUF = NULL;
			}
			pVariableDirection = pFunOffset->getDefinedVariable();
		}else{//no offset function will be created
			cVectorArea vectorArea( ulStartPosition + xOffset, ulEndPosition + xOffset );
			pAreaNew = new cArea( vectorArea );
			pVariableDirection = pAreaNew->getDefinedVariable();
		}
		//create line fib function
		cUnderFunction * pUnderFunction = polynomLine.toFibUnderFunction(
			pAreaNew->getDefinedVariable() );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
		cFunction * pFunction = new cFunction( *pUnderFunction, pPoint );
#else //FEATURE_SIMPLE_CONSTRUCTOR
		cFunction * pFunction = new cFunction( *pUnderFunction, NULL, NULL, pPoint );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
		
		if ( pFunOffset ){
			pFunOffset->insertObjectInElement( pFunction );
			pAreaNew->insertObjectInElement( pFunOffset );
			//now: pAreaNew( pFunOffset( pFunction( pAreaY( pSubobjectToInsert ))))
		}else{
			pAreaNew->insertObjectInElement( pFunction );
			//now: pAreaNew( pFunction( pAreaY( pSubobjectToInsert )))
		}
		
		cVectorPosition * pVecPosition = pPoint->getPosition();
		if ( bChoosenDirection ){
			
			pVecPosition->setVariable( 1, pVariableDirection );
			pVecPosition->setVariable( 2, pFunction->getDefinedVariable() );
		}else{//switch x and y variables
			
			pVecPosition->setVariable( 1, pFunction->getDefinedVariable() );
			pVecPosition->setVariable( 2, pVariableDirection );
		}
		
		if ( pUnderFunction ){
			delete pUnderFunction;
		}
		return pAreaNew;
	}
	
	
	
	/**
	 * This function creates an Fib object for the given area.
	 * The created Fib object contains one point object, wich
	 * positions element variables are set to the data points in the area.
	 *
	 * @param bChoosenDirection the direction in wich the given splines
	 * 	are to evalue (true = x direction; false = y direction)
	 * @param ulStartPosition the start position of the area in the given direction
	 * @param ulEndPosition the end position of the area in the given direction
	 * @param splineLower a spline for the lower border of the area
	 * @param splineUpper a spline for the upper border of the area
	 * @param xOffset the offset in the given directions for the positions
	 * @return a pointer to the created area Fib object;
	 * 	Attention: You have to care that the created Fib object is deleted
	 */
	template< class tX > cArea *
		createAreaFibObject( const bool bChoosenDirection,
			const longFib ulStartPosition, const longFib ulEndPosition,
			const cSpline< tX, double > & splineLower,
			const cSpline< tX, double > & splineUpper,
			const tX xOffset = 0 ){
		/*create the Fib subobject object "area( fun( fun( area( pUnderobject ))))"
		(for constant splines: don't create a funcion element, but include
		value directly in the are boundery)*/
		cVectorPosition vecPosition( 2 );
		cPoint * pPoint = new cPoint( & vecPosition );
		
		//create offset function element
		cArea * pAreaX = NULL;
		cFunction * pFunOffset = NULL;
		cFibVariable * pVariableDirection = NULL;

		const bool bSplineLowerIsConstant =
			( splineLower.getPolynoms()->empty() ) ||
			( (splineLower.getPolynoms()->size() == 1) &&
				( (*(splineLower.getPolynoms()))[ 0 ].getLastFactorIndexNotNull() <= 0 ) );
		const bool bSplineUpperIsConstant =
			( splineUpper.getPolynoms()->empty() ) ||
			( (splineUpper.getPolynoms()->size() == 1) &&
				( (*(splineUpper.getPolynoms()))[ 0 ].getLastFactorIndexNotNull() <= 0 ) );
		const bool bBothSplinesConstant =
			bSplineLowerIsConstant && bSplineUpperIsConstant;
		if ( ( xOffset != 0 ) && ( ! bBothSplinesConstant ) ){
			//offset not 0 and both splines not constant -> create offset function
			cVectorArea vectorArea( ulStartPosition, ulEndPosition );
			pAreaX = new cArea( vectorArea );
			pVariableDirection = pAreaX->getDefinedVariable();
			
			cUnderFunction * pOffsetUF = new cFunctionAdd(
				cFunctionValue( xOffset ), cFunctionVariable( pVariableDirection )  );
			pFunOffset = new cFunction( *pOffsetUF );
			if ( pOffsetUF ){
				delete pOffsetUF;
				pOffsetUF = NULL;
			}
			
			pVariableDirection = pFunOffset->getDefinedVariable();
		}else{//no offset function will be created
			cVectorArea vectorArea( ulStartPosition + xOffset, ulEndPosition + xOffset );
			pAreaX = new cArea( vectorArea );
			pVariableDirection = pAreaX->getDefinedVariable();
		}
		
		//create border function elements
		cFunction * pFunUpper = NULL;
		if ( ! bSplineUpperIsConstant ){
			cUnderFunction * pUpperUF = splineUpper.toFibUnderFunction(
				pAreaX->getDefinedVariable() );
			pFunUpper = new cFunction( *pUpperUF );
			
			if ( pUpperUF ){
				delete pUpperUF;
			}
		}
		cFunction * pFunLower = NULL;
		if ( ! bSplineLowerIsConstant ){
			cUnderFunction * pLowerUF = splineLower.toFibUnderFunction(
				pAreaX->getDefinedVariable() );
			pFunLower = new cFunction( *pLowerUF, pFunUpper );
			
			if ( pLowerUF ){
				delete pLowerUF;
			}
		}
		//create the area for the y direction
		cVectorArea * pVectorAreaY = NULL;
		if ( ( pFunLower != NULL ) && ( pFunUpper != NULL ) ){
			
			pVectorAreaY = new cVectorArea( pFunLower->getDefinedVariable(),
				pFunUpper->getDefinedVariable() );
		}else if ( ( pFunLower == NULL ) && ( pFunUpper != NULL ) ){
			
			pVectorAreaY = new cVectorArea(
				splineLower.getPolynoms()->empty() ? 0 :
					( (*(splineLower.getPolynoms()))[ 0 ].vecFactors.empty() ? 0 :
						roundToLongFib( (*(splineLower.getPolynoms()))[ 0 ].vecFactors[ 0 ] ) ),
				pFunUpper->getDefinedVariable() );
		}else if ( ( pFunLower != NULL ) && ( pFunUpper == NULL ) ){
			
			pVectorAreaY = new cVectorArea( pFunLower->getDefinedVariable(),
				splineUpper.getPolynoms()->empty() ? 0 :
					( (*(splineUpper.getPolynoms()))[ 0 ].vecFactors.empty() ? 0 :
						roundToLongFib( (*(splineUpper.getPolynoms()))[ 0 ].vecFactors[ 0 ] ) ) );
		}else{// if ( ( pFunLower == NULL ) && ( pFunUpper == NULL ) ){
			
			pVectorAreaY = new cVectorArea(
				splineLower.getPolynoms()->empty() ? 0 :
					( (*(splineLower.getPolynoms()))[ 0 ].vecFactors.empty() ? 0 :
						roundToLongFib( (*(splineLower.getPolynoms()))[ 0 ].vecFactors[ 0 ] ) ),
				splineUpper.getPolynoms()->empty() ? 0 :
					( (*(splineUpper.getPolynoms()))[ 0 ].vecFactors.empty() ? 0 :
						roundToLongFib( (*(splineUpper.getPolynoms()))[ 0 ].vecFactors[ 0 ] ) ) );
		}//end if create under area
		
		cArea * pAreaY = new cArea( *pVectorAreaY, pPoint );
		if ( pVectorAreaY ){
			delete pVectorAreaY;
		}
		//connect created Fib elements
		if ( pFunUpper ){
			pFunUpper->insertObjectInElement( pAreaY );
			//if existing function lower is connected to function upper
			
			if ( pFunLower ){
				//connect to function lower
		
				if ( pFunOffset ){
					pFunOffset->insertObjectInElement( pFunLower );
					pAreaX->insertObjectInElement( pFunOffset );
					//now: pAreaX( pFunOffset( pFunLower( pFunUpper( pAreaY( pSubobjectToInsert )))))
				}else{
					pAreaX->insertObjectInElement( pFunLower );
					//now: pAreaX( pFunLower( pFunUpper( pAreaY( pSubobjectToInsert ))))
				}
			}else{//just upper function exists
				if ( pFunOffset ){
					pFunOffset->insertObjectInElement( pFunUpper );
					pAreaX->insertObjectInElement( pFunOffset );
					//now: pAreaX( pFunOffset( pFunUpper( pAreaY( pSubobjectToInsert ))))
				}else{
					pAreaX->insertObjectInElement( pFunUpper );
					//now: pAreaX( pFunUpper( pAreaY( pSubobjectToInsert )))
				}
			}
		}else if ( pFunLower ){
			//no upper function exists, but an lower
			
			pFunLower->insertObjectInElement( pAreaY );
			
			if ( pFunOffset ){
				pFunOffset->insertObjectInElement( pFunLower );
				pAreaX->insertObjectInElement( pFunOffset );
				//now: pAreaX( pFunOffset( pFunLower( pAreaY( pSubobjectToInsert ))))
			}else{
				pAreaX->insertObjectInElement( pFunLower );
				//now: pAreaX( pFunLower( pAreaY( pSubobjectToInsert )))
			}
		}else{//no upper and lower function exists
			pAreaX->insertObjectInElement( pAreaY );
			//now: pAreaX( pAreaY( pSubobjectToInsert ))
		}//end if make connections
		
		cVectorPosition * pVecPosition = pPoint->getPosition();
		if ( bChoosenDirection ){
			
			pVecPosition->setVariable( 1, pVariableDirection );
			pVecPosition->setVariable( 2, pAreaY->getDefinedVariable() );
		}else{//switch x and y variables
			
			pVecPosition->setVariable( 1, pAreaY->getDefinedVariable() );
			pVecPosition->setVariable( 2, pVariableDirection );
		}
		
		return pAreaX;
	}
	
	
	/**
	 * This function creates an Fib object for the given line.
	 * The created fib object contains one point object, wich
	 * positions element variables are set to the data points in the area.
	 *
	 * @param bChoosenDirection the direction in wich the given splines
	 * 	are to evalue (true = x direction; false = y direction)
	 * @param ulStartPosition the start position of the area in the given direction
	 * @param ulEndPosition the end position of the area in the given direction
	 * @param splineLine a spline for the line
	 * @param xOffset the offset in the given directions for the positions
	 * @return a pointer to the created line Fib object;
	 * 	Attention: You have to care that the created Fib object is deleted
	 */
	template< class tX > cArea *
		createLineFibObject( const bool bChoosenDirection,
			const longFib ulStartPosition, const longFib ulEndPosition,
			const cSpline< tX, double > & splineLine,
			const tX xOffset = 0 ){
		/*if bouth splines are the same don't use second fun and area;
		create the Fib subobject object "area( fun( ))"*/
		cVectorPosition vecPosition( 2 );
		cPoint * pPoint = new cPoint( & vecPosition );
		
		cArea * pAreaNew = NULL;
		
		cFunction * pFunOffset = NULL;
		cFibVariable * pVariableDirection;
		const bool bSplineLowerIsConstant =
			( splineLine.getPolynoms()->empty() ) ||
			( (splineLine.getPolynoms()->size() == 1) &&
				( (*(splineLine.getPolynoms()))[ 0 ].getLastFactorIndexNotNull() <= 0 ) );
		if ( (xOffset != 0) && ( ! bSplineLowerIsConstant ) ){
			//create offset function element
			
			cVectorArea vectorArea( ulStartPosition, ulEndPosition );
			pAreaNew = new cArea( vectorArea );
			pVariableDirection = pAreaNew->getDefinedVariable();
			
			//offset not 0 and spline not constant -> create offset function
			cUnderFunction * pOffsetUF = new cFunctionAdd(
				cFunctionValue( xOffset ), cFunctionVariable( pVariableDirection )  );
			pFunOffset = new cFunction( *pOffsetUF );
			if ( pOffsetUF ){
				delete pOffsetUF;
				pOffsetUF = NULL;
			}
			pVariableDirection = pFunOffset->getDefinedVariable();
		}else{//no offset function will be created
			cVectorArea vectorArea( ulStartPosition + xOffset, ulEndPosition + xOffset );
			pAreaNew = new cArea( vectorArea );
			pVariableDirection = pAreaNew->getDefinedVariable();
		}
		//create line fib function
		cUnderFunction * pUnderFunction = splineLine.toFibUnderFunction(
			pAreaNew->getDefinedVariable() );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
		cFunction * pFunction = new cFunction( *pUnderFunction, pPoint );
#else //FEATURE_SIMPLE_CONSTRUCTOR
		cFunction * pFunction = new cFunction( *pUnderFunction, NULL, NULL, pPoint );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
		
		if ( pFunOffset ){
			pFunOffset->insertObjectInElement( pFunction );
			pAreaNew->insertObjectInElement( pFunOffset );
			//now: pAreaNew( pFunOffset( pFunction( pAreaY( pSubobjectToInsert ))))
		}else{
			pAreaNew->insertObjectInElement( pFunction );
			//now: pAreaNew( pFunction( pAreaY( pSubobjectToInsert )))
		}
		
		cVectorPosition * pVecPosition = pPoint->getPosition();
		if ( bChoosenDirection ){
			
			pVecPosition->setVariable( 1, pVariableDirection );
			pVecPosition->setVariable( 2, pFunction->getDefinedVariable() );
		}else{//switch x and y variables
			
			pVecPosition->setVariable( 1, pFunction->getDefinedVariable() );
			pVecPosition->setVariable( 2, pVariableDirection );
		}
		
		if ( pUnderFunction ){
			delete pUnderFunction;
		}
		return pAreaNew;
	}
	
	
	
	/**
	 * This function smooth the borders of the given area, by removing
	 * some points from the minimum areas.
	 * The possible areas have to be evalued agoun after the call to this
	 * function.
	 *
	 * @param toReduceArea the area, which to smoth be removing some points
	 * @param bChoosenDirection the direction in which the points of the area
	 * 	are ordered and for wich to find the border ranges (x = true; y = false)
	 * @param setMaximumXArea in x direction ordered points, which can be
	 * 	included in the areas
	 * @param setMaximumXArea in y direction ordered points, which can be
	 * 	included in the areas
	 * @param setMinimumXArea in x direction ordered points, which have be
	 * 	included in the areas
	 * @param setMinimumYArea in y direction ordered points, which have be
	 * 	included in the areas
	 * @return a ste with the data points removed from setMinimumXArea
	 */
	template <class tX> set< typename fib::algorithms::nD1::cDataPoint<tX, tX> >
		smoothBorders( const pair< unsigned long, list< pair<
			typename fib::algorithms::nD1::cDataPoint<tX, tX>,
			typename fib::algorithms::nD1::cDataPoint<tX, tX> > > > & toReduceArea,
		const bool bChoosenDirection,
		const set< typename fib::algorithms::nD1::cDataPoint<tX, tX> > & setMaximumXArea,
		const set< typename fib::algorithms::nD1::cDataPoint<tX, tX> > & setMaximumYArea,
		set< typename fib::algorithms::nD1::cDataPoint<tX, tX> > & setMinimumXArea,
		set< typename fib::algorithms::nD1::cDataPoint<tX, tX> > & setMinimumYArea ){

		typedef fib::algorithms::nD1::cDataPoint<tX, tX> typeDataPoint;
		
		vector< fib::algorithms::nD1::cDataPointRange< tX, double > > vecRangesUpper;
		vector< fib::algorithms::nD1::cDataPointRange< tX, double > > vecRangesLower;
		
		findBorderRanges( toReduceArea,
			bChoosenDirection, setMaximumXArea, setMaximumYArea,
			vecRangesLower, vecRangesUpper );
		
		//remove extreem points
		typedef multimap< tX, const typeDataPoint > typeMultimapDeltas;
		typeMultimapDeltas mapDeltas;
		//evalue deltas for the lower border
		for ( unsigned int uiActRange = 1; uiActRange < vecRangesLower.size(); uiActRange++ ){
			
			tX minDelta = vecRangesLower[ uiActRange ].minY - vecRangesLower[ uiActRange - 1 ].maxY;
			
			typeDataPoint dataPointTmp( 0,0 );
			if ( bChoosenDirection ){
				dataPointTmp.x = vecRangesLower[ uiActRange - 1 ].x;
				dataPointTmp.y = ((tX)(vecRangesLower[ uiActRange - 1 ].maxY + D_HALF_ROW));
			}else{//in y direction
				dataPointTmp.y = vecRangesLower[ uiActRange - 1 ].x;
				dataPointTmp.x = ((tX)(vecRangesLower[ uiActRange - 1 ].maxY + D_HALF_ROW));
			}
			
			mapDeltas.insert( make_pair( minDelta, dataPointTmp ) );
			
			
			minDelta = vecRangesLower[ uiActRange - 1 ].minY - vecRangesLower[ uiActRange ].maxY;
			
			if ( bChoosenDirection ){
				dataPointTmp.x = vecRangesLower[ uiActRange ].x;
				dataPointTmp.y = ((tX)(vecRangesLower[ uiActRange ].maxY - D_HALF_ROW));
			}else{//in y direction
				dataPointTmp.y = vecRangesLower[ uiActRange ].x;
				dataPointTmp.x = ((tX)(vecRangesLower[ uiActRange ].maxY - D_HALF_ROW));
			}
			
			mapDeltas.insert( make_pair( minDelta, dataPointTmp ) );
		}
		//evalue the deltas for the upper border
		for ( unsigned int uiActRange = 1; uiActRange < vecRangesUpper.size(); uiActRange++ ){
			
			tX minDelta = vecRangesUpper[ uiActRange ].minY - vecRangesUpper[ uiActRange - 1 ].maxY;
			
			typeDataPoint dataPointTmp( 0,0 );
			if ( bChoosenDirection ){
				dataPointTmp.x = vecRangesUpper[ uiActRange ].x;
				dataPointTmp.y = ((tX)(vecRangesUpper[ uiActRange ].minY - D_HALF_ROW));
			}else{//in y direction
				dataPointTmp.y = vecRangesUpper[ uiActRange ].x;
				dataPointTmp.x = ((tX)(vecRangesUpper[ uiActRange ].minY - D_HALF_ROW));
			}
			
			mapDeltas.insert( make_pair( minDelta, dataPointTmp ) );
		
		
			minDelta = vecRangesUpper[ uiActRange - 1 ].minY - vecRangesUpper[ uiActRange ].maxY;
			
			if ( bChoosenDirection ){
				dataPointTmp.x = vecRangesUpper[ uiActRange - 1 ].x;
				dataPointTmp.y = ((tX)(vecRangesUpper[ uiActRange - 1 ].minY + D_HALF_ROW));
			}else{//in y direction
				dataPointTmp.y = vecRangesUpper[ uiActRange - 1 ].x;
				dataPointTmp.x = ((tX)(vecRangesUpper[ uiActRange - 1 ].minY + D_HALF_ROW));
			}
			
			mapDeltas.insert( make_pair( minDelta, dataPointTmp ) );
		}
		//remove points with the maximum deltas
		const unsigned long ulPointsToRemove = vecRangesUpper.size() / 16 + 2;
		unsigned long uiPointsRemoved = 0;
		set< typename fib::algorithms::nD1::cDataPoint<tX, tX> > setRemovedPoints;
		for ( unsigned long ulPointsRemovedLocal = 0; ( ! mapDeltas.empty() ) &&
				( ulPointsRemovedLocal < ulPointsToRemove ); ulPointsRemovedLocal++ ){
			
			typename typeMultimapDeltas::iterator itrBiggestDelta = mapDeltas.end();
			itrBiggestDelta--;
			DEBUG_OUT_L2(<<"Removing point: ("<<itrBiggestDelta->second.x<<", "<<itrBiggestDelta->second.y<<") with delta "<<itrBiggestDelta->first<<endl<<flush);
			
			setRemovedPoints.insert( itrBiggestDelta->second );
			uiPointsRemoved += setMinimumXArea.erase( itrBiggestDelta->second );
			const typeDataPoint dataYPointTmp(
				itrBiggestDelta->second.y, itrBiggestDelta->second.x );
			uiPointsRemoved += setMinimumYArea.erase( dataYPointTmp );
			mapDeltas.erase( itrBiggestDelta );
		}
		return setRemovedPoints;
	}


};};};//end namespace fib::algorithms::nD2;

/**
 * This function evaluats a derivate of a vector with datapoints.
 * To evalue the derivate the differnce in the y values of to
 * neibourpoints is divided with ther distance.
 *
 * @param vecInput the vector with the range data points, for which the
 * 	derivate is to be evalued
 * @return the vector with derivate range datapoints
 */
template <class tX, class tY, class tZ>
	vector< fib::algorithms::nD2::cDataPoint<tX, tY, tZ> > derivate(
		const vector< fib::algorithms::nD2::cDataPoint<tX, tY, tZ> > & vecInput ){
	
	vector< fib::algorithms::nD2::cDataPoint<tX, tY, tZ> > vecDerivate = vecInput;
	
	sort( vecDerivate.begin(), vecDerivate.end(), lowerPosition );
	
	tZ minDistance = 0.0;
	long lMinDistPos = -1;
	
	//evalue the derivate
	const size_t iNumberOfDerivatePoints = vecDerivate.size() - 1;
	for ( size_t iActualValue = 0; iActualValue < iNumberOfDerivatePoints;
			iActualValue++ ){

		const tZ dDistance = vecDerivate[ iActualValue ].dist(
			vecDerivate[ iActualValue + 1 ] );
		
		vecDerivate[ iActualValue ].z = (vecDerivate[ iActualValue + 1 ].z -
			vecDerivate[ iActualValue ].z) / dDistance;
	}
	//remove the last element
	vecDerivate.resize( iNumberOfDerivatePoints );
	
	return vecDerivate;
}


/**
 * This function evaluats a derivate of a vector with range datapoints.
 * To evalue the derivate a point with the minimal range size is choosen
 * as the devolopment point. For every other point the maximal and minimal
 * distance betwean two bounderies of the point and the devolopment point
 * is evalued and divided by the distance betwean the points.
 *
 * @param vecInput the vector with the range data points, for which the
 * 	derivate is to be evalued
 * @return a pair with it's elements:
 * 	- the first element is the vector with derivate range datapoints
 * 	- the second element is the devolopment point which was choosen
 */
template <class tX, class tY, class tZ>
	pair< vector< fib::algorithms::nD2::cDataPointRange<tX, tY, tZ> >,
		fib::algorithms::nD2::cDataPointRange<tX, tY, tZ> > derivateDist(
		const vector< fib::algorithms::nD2::cDataPointRange<tX, tY, tZ> > & vecInput ){
	
	vector< fib::algorithms::nD2::cDataPointRange<tX, tY, tZ> > vecDerivate;
	
	tZ minDistance = 0.0;
	long lMinDistPos = -1;
	
	//search for the entry with the minimal distance
	for ( size_t iActualValue = 0; iActualValue < vecInput.size();
			iActualValue++ ){
		
		if ( ( std::abs( vecInput[ iActualValue ].maxZ ) < SAVE_BOUNDERY ) &&
				( std::abs( vecInput[ iActualValue ].minZ ) < SAVE_BOUNDERY ) ){
			continue;//skip nullvalues
		}
		
		if ( ( std::abs( vecInput[ iActualValue ].diff() ) < minDistance) ||
				(lMinDistPos == -1) ){
			
			minDistance = std::abs( vecInput[ iActualValue ].diff() );
			lMinDistPos = iActualValue;
		}
	}
	if ( lMinDistPos == -1 ){
#ifdef DEBUG_N_D2
		DEBUG_OUT_L2(<<"All ranges are 0."<<endl<<flush);
#endif
		return make_pair( vecDerivate, fib::algorithms::nD2::cDataPoint<tX, tY, tZ>() );
	}
	
	const tZ minDistanceAverage = ( vecInput[ lMinDistPos ].maxZ +
		vecInput[ lMinDistPos ].minZ ) / 2.0;
	
#ifdef DEBUG_N_D2
	DEBUG_OUT_L2(<<"The position with the minimal range: "<<lMinDistPos);
	DEBUG_OUT_L2(<<"  the position is=("<<vecInput[ lMinDistPos ].y<<" ;"<<vecInput[ lMinDistPos ].y);
	DEBUG_OUT_L2(<<")   the range average is="<<minDistanceAverage);
	DEBUG_OUT_L2(<<" ( "<<vecInput[ lMinDistPos ].minZ <<" , ");
	DEBUG_OUT_L2(<<vecInput[ lMinDistPos ].maxZ <<" )"<<endl<<flush);
#endif
	//evalue the derivate
	tZ maxDistance;
	for ( size_t iActualValue = 0; iActualValue < vecInput.size();
			iActualValue++ ){
		
		if ( iActualValue == ((size_t)(lMinDistPos)) ){
			continue;//skip
		}
		if ( ( std::abs( vecInput[ iActualValue ].maxZ ) < SAVE_BOUNDERY ) &&
				( std::abs( vecInput[ iActualValue ].minZ ) < SAVE_BOUNDERY ) ){
			continue;//skip nullvalues
		}

		const tZ dDistance = vecInput[ lMinDistPos ].dist( vecInput[ iActualValue ] );
		
		minDistance = (vecInput[ iActualValue ].minZ - minDistanceAverage) / dDistance;
		maxDistance = (vecInput[ iActualValue ].maxZ - minDistanceAverage) / dDistance;
		
		if ( maxDistance < minDistance ){
			//switch values
			const tZ dTmpValue = minDistance;
			minDistance = maxDistance;
			maxDistance = dTmpValue;
		}
		vecDerivate.push_back( fib::algorithms::nD2::cDataPoint<tX, tY, tZ>(
			vecInput[ iActualValue ].x, vecInput[ iActualValue ].y,
			minDistance, maxDistance ) );
		
	}
	return make_pair( vecDerivate, vecInput[ lMinDistPos ] );
}



/**
 * This function integrats the given line into the given areas.
 * The given line will be appended to all areas to which it is connected.
 * (It is connected if one of it's 8 neibours is in the area.)
 * If no area exist a nuw area with the line will be added.
 * If an area exists wich is connected with the given line paNewLine,
 * but already has points on the same x row, the area is duplicated
 * without theas line and the new line is added to it.
 *
 * @param areas a list of areas, wher the line should be integrated into
 * @param paNewLine the (new) line to integrate as a pare of it lowest and
 * 	biggest datapoints
 */
template <class tX>
	void fib::algorithms::nD2::integrateLineInAreas( list< pair<
		unsigned long, list< pair< fib::algorithms::nD1::cDataPoint<tX, tX>,
		fib::algorithms::nD1::cDataPoint<tX, tX> > > > > & areas,
		const pair< fib::algorithms::nD1::cDataPoint<tX, tX>,
		fib::algorithms::nD1::cDataPoint<tX, tX> > & paNewLine ){
	
	typedef fib::algorithms::nD1::cDataPoint<tX, tX> typeDataPoint;
	typedef pair< unsigned long, list< pair< typeDataPoint,
		typeDataPoint > > > typeArea;
	typedef list< typeArea > typePossibleAreas;
	typedef list< pair< typeDataPoint, typeDataPoint > > typeDataPointList;
	typedef typename typeDataPointList::const_iterator typeItrDataPointList;
	
	const unsigned long ulPointsInLine =
		paNewLine.second.y - paNewLine.first.y + 1;
	bool bAreaFound = false;
	for ( typename typePossibleAreas::iterator itrArea = areas.begin();
			itrArea != areas.end(); itrArea++ ){
		
		const typeDataPoint dpLowerBorder = itrArea->second.back().first;
		const typeDataPoint dpUpperBorder = itrArea->second.back().second;
		/*if the last line of the actual area is in the next row in
		the x area and the y boundery of the new line are connected*/
		if ( ((dpLowerBorder.x + 1) == paNewLine.second.x ) &&
				( (dpLowerBorder.y - 1) <= paNewLine.second.y ) &&
				( paNewLine.first.y <= (dpUpperBorder.y + 1) ) ){
			//add line to area
			itrArea->first += ulPointsInLine;
			itrArea->second.push_back( paNewLine );
			
		}else if ( (dpLowerBorder.x == paNewLine.second.x ) &&
				( 2 <= itrArea->second.size() ) ){
			//check if ther are more than one possible ways the area could be continued
			typeItrDataPointList itrNextToLast = itrArea->second.end();
			itrNextToLast--;//last
			itrNextToLast--;//next to last
			if ( ( (dpLowerBorder.y - 1) <= paNewLine.second.y ) &&
					( paNewLine.first.y <= (dpUpperBorder.y + 1) ) ){
				//duplicate the area
				areas.push_front( typeArea( itrArea->first, itrArea->second ) );
				const unsigned long ulPointsInOldLine =
					dpUpperBorder.y - dpLowerBorder.y + 1;
				//remove old line
				areas.front().first -= ulPointsInOldLine;
				areas.front().second.pop_back();
				//add new line
				areas.front().first += ulPointsInLine;
				areas.front().second.push_back( paNewLine );
			}
		}
	}
	if ( ! bAreaFound ){
		//create a new possible area
		typeDataPointList liNewArea;
		liNewArea.push_back( paNewLine );
		areas.push_back( typeArea( ulPointsInLine, liNewArea ) );
	}
}


/**
 * This function combines the given set of points to Fib objects.
 * Beware: You have to care that the created Fib object will be deleted
 *
 * @param setPoints the set with the datapoints to combine to
 * 	a Fib object with the help of area and function elements;
 * 	The given points should be positions in an matrix, positions in
 * 	the matrix not given, will be considerd not to be in the area
 * 	to create. ( tX should be an integer type)
 * @param pUnderobject a pointer to the subobject, which the created
 * 	Fib elements should contain and which should be evalued for the
 * 	point positions
 * @param pVariableX a pointer to the variable for the x position
 * @param pVariableY a pointer to the variable for the y position
 * @return a Fib object with the created Fib subobjects, which cover
 * 	all point positions in the given set setPoints or NULL, if non
 * 	such could be created;
 * 	some positions can be evalued twice;
 * 	the Fib subobjects, wich evalue the most points, are on the
 * 	front of the list-object (have a lower subobject number);
 * 	if NULL is returnd, you have to care that pUnderobject will be
 * 	deleted, else pUnderobject will be included in one
 * 	subobject of the created list-object and the other subobjects
 * 	will contain copies of pUnderobject
 * 	Structur of the created Fib object:
 * 		area( fun( fun( area( pUnderobject ))))
 * 	or if this previos given structur is not possible
 * 		list(
 * 			area( fun( fun( area( pUnderobject ))))
 * 			...
 * 			area( fun( fun( area( pUnderobject ))))
 * 		)
 */
template <class tX>
	cFibElement * fib::algorithms::nD2::createAreasForPoints(
		const set< fib::algorithms::nD1::cDataPoint<tX, tX> > & setPoints,
		cFibElement * pUnderobject,
		cFibVariable * pVariableDimX, cFibVariable * pVariableDimY ){
	
	DEBUG_OUT_L2(<<"createAreasForPoints(#setPoints="<<setPoints.size()<<", pUnderobject="<<pUnderobject<<", varX="<<pVariableDimX<<", varY="<<pVariableDimY<<") started "<<endl<<flush);
	
	if ( setPoints.empty() ){
		//no data points, for which to create the areas
		return NULL;
	}
	if ( pUnderobject == NULL ){
		//no subobject, wich to use in created Fib objects
		return NULL;
	}
	if ( ( pVariableDimX == NULL ) || ( pVariableDimY == NULL ) ){
		//missing variable, wich to use in created Fib objects
		return NULL;
	}
	
	typedef fib::algorithms::nD1::cDataPoint<tX, tX> typeDataPoint;
	typedef set< typeDataPoint > typeSetDataPoints;
	typedef typename typeSetDataPoints::const_iterator typeConstItrSetDataPoints;
	typedef typename typeSetDataPoints::const_reverse_iterator typeConstRevItrSetDataPoints;

	
	/*create areas for the minimum and maximum number of points in the
	directions (the maximum area is the area of points, which can be contained
	in an created area object, the minimum is the area of points, which are
	not contained in an other created areas)*/
	typeSetDataPoints setMaximumXArea = setPoints;
	typeSetDataPoints setMinimumXArea = setMaximumXArea;
	
	/*the Y Areas /Sets are the same as the X Areas/Sets, but of a matrix
	rotated with 90 degree*/
	typeSetDataPoints setMaximumYArea;
	
	for ( typeConstItrSetDataPoints itrPoint = setPoints.begin();
			itrPoint != setPoints.end(); itrPoint++ ){
		
		setMaximumYArea.insert( typeDataPoint( itrPoint->y, itrPoint->x ) );
	}
	typeSetDataPoints setMinimumYArea = setMaximumYArea;

	/*the created elemental areas;
		- first pair element: number of points, the area covers
		- second pair element: the the area as an Fib object*/
	list< pair< unsigned long, cFibElement * > > liAreaList;
	
	DEBUG_OUT_L2(<<"beginning searching for areas"<<endl<<flush);
	
	//while not all points are included in the area
	while ( ( ! setMinimumXArea.empty() ) || ( ! setMinimumYArea.empty() ) ){
	/*create areas:
		- begin at the outer side of the minimum areas of points which
			should be found; prefer big areas
		- remove points from the minimum areas, which are included in created areas
		- borders are points, which should be in the area, but which
			neibours shouldn't be in the area*/
		
		//scan in x direction
		/* The list with the possible areas.
		* The pair elements are:
		* 	first element: the number of points in the possible area
		* 	second element: list with the possible areas containing each a
		* 	list with the pairs for the lines: first element is the upper
		* 	border of the line and the second the lower border
		*/
		typedef list< pair< unsigned long, list< pair< typeDataPoint,
			typeDataPoint > > > > typePossibleAreas;
		typePossibleAreas possibleXAreas;
		
		typeConstItrSetDataPoints itrPoint = setMinimumXArea.begin();
		typeDataPoint dataPoint = *itrPoint;
		typeDataPoint dataPointLineBegin = *itrPoint;
		
		while ( itrPoint != setMinimumXArea.end() ){
			
			if ( dataPoint != *itrPoint ){
				/*this point isn't the x neibour of the last point
				-> new line begin; *itrXPoint = new line begin; dataPoint.y-- = old line end*/
				dataPoint.y--;//old line end
				/*insert old line to every possible area or create a new area, if
				no possible area exists*/
				const pair< typeDataPoint, typeDataPoint >
					paNewLine( dataPointLineBegin, dataPoint);
				integrateLineInAreas( possibleXAreas, paNewLine );
	
				dataPointLineBegin = *itrPoint;//remember line begin
			}
			dataPoint = *itrPoint;
			itrPoint++;
			dataPoint.y++;//next neibour in x direction for the last point
		}
		{//add last line
			dataPoint.y--;
			const pair< typeDataPoint, typeDataPoint >
				paNewLine( dataPointLineBegin, dataPoint);
			integrateLineInAreas( possibleXAreas, paNewLine );
		}
		//scan in y direction
		typePossibleAreas possibleYAreas;
		
		itrPoint = setMinimumYArea.begin();
		dataPoint = *itrPoint;
		dataPointLineBegin = *itrPoint;
		
		while ( itrPoint != setMinimumYArea.end() ){
			
			if ( dataPoint != *itrPoint ){
				/*this point isn't the x neibour of the last point
				-> new line begin; *itrXPoint = new line begin; dataPoint.y-- = old line end*/
				dataPoint.y--;//old line end
				/*insert old line to every possible area or create a new area, if
				no possible area exists*/
				const pair< typeDataPoint, typeDataPoint >
					paNewLine( dataPointLineBegin, dataPoint);
				integrateLineInAreas( possibleYAreas, paNewLine );
	
				dataPointLineBegin = *itrPoint;//remember line begin
			}
			dataPoint = *itrPoint;
			itrPoint++;
			dataPoint.y++;//next neibour in x direction for the last point
		}
		{//add last line
			dataPoint.y--;
			const pair< typeDataPoint, typeDataPoint >
				paNewLine( dataPointLineBegin, dataPoint);
			integrateLineInAreas( possibleYAreas, paNewLine );
		}
		//choose the area for which to create the Fib structur
		/*the type filds are:
			- number of points in the area
				- iterator to the area
				- if the area is a x area (x = true; y = false)*/
		typedef set< pair< unsigned long, pair< typename typePossibleAreas::const_iterator, bool > >,
				structLowerFirstElement< pair< typename typePossibleAreas::const_iterator, bool > > >
				typeSetOrderdAreas;
		typeSetOrderdAreas setAreas;
		for ( typename typePossibleAreas::const_iterator itrActualArea = possibleXAreas.begin();
				itrActualArea != possibleXAreas.end(); itrActualArea++ ){
			
			setAreas.insert( make_pair( itrActualArea->first, make_pair( itrActualArea, true ) ) );
		}
		for ( typename typePossibleAreas::const_iterator itrActualArea = possibleYAreas.begin();
				itrActualArea != possibleYAreas.end(); itrActualArea++ ){
			
			setAreas.insert( make_pair( itrActualArea->first, make_pair( itrActualArea, false ) ) );
		}

		//try biggest area and than the areas befor, if biggest area couldn't be used
		typename typeSetOrderdAreas::const_reverse_iterator
				itrActualToConvertArea = setAreas.rbegin();
		
		unsigned long uiPointsRemoved = 0;
		for ( ; itrActualToConvertArea != setAreas.rend(); itrActualToConvertArea++ ){
			
			if ( itrActualToConvertArea->first <= 4 ){
				DEBUG_OUT_L2(<<"just maximal "<<itrActualToConvertArea->first<<" points in remaining areas"<<endl<<flush);
				//stop evaluation, because no area with more than 4 points exists
				itrActualToConvertArea = setAreas.rend();
				break;
			}
			const typename typePossibleAreas::const_iterator itrToConvertArea =
				itrActualToConvertArea->second.first;
			//x = true; y = false
			const bool bChoosenDirection = itrActualToConvertArea->second.second;
			
			//evalue ranges for the choosen area in directions
			typedef list< pair< typeDataPoint, typeDataPoint > > typeDataPointList;
			typedef typename typeDataPointList::const_iterator typeItrDataPointList;
#ifdef DEBUG_N_D2
			cout<<"founded best datapoints (direction "<<(bChoosenDirection?"x":"y")<<" ):";
			for ( typeItrDataPointList itrDataPoint = itrToConvertArea->second.begin();
					itrDataPoint != itrToConvertArea->second.end(); itrDataPoint++ ){
				cout<<"("<< itrDataPoint->first.x <<";[ "<< itrDataPoint->first.y
					<<" ... "<< itrDataPoint->second.y <<" ] ); ";
			}
			cout<<endl;
#endif
			DEBUG_OUT_L2(<<"creating range datapoints for areas"<<endl<<flush);
			vector< fib::algorithms::nD1::cDataPointRange< tX, double > > vecRangesUpper;
			vector< fib::algorithms::nD1::cDataPointRange< tX, double > > vecRangesLower;
			
			const bool bBordersEqual = findBorderRanges( *itrToConvertArea,
				bChoosenDirection, setMaximumXArea, setMaximumYArea,
				vecRangesLower, vecRangesUpper );

			
			//dismiss created areas which have (much) more points as in the maximal area
			unsigned long ulAceptablePointsForArea = 8;
			for ( unsigned int uiActRange = 0; uiActRange < vecRangesLower.size(); uiActRange++ ){
				
				ulAceptablePointsForArea += vecRangesUpper[uiActRange].maxY - vecRangesLower[uiActRange].minY + 1;
			}
			if ( vecRangesLower.empty() || vecRangesUpper.empty() ){
				DEBUG_OUT_EL2(<<"one range empty:"<<endl<<flush);
#ifdef DEBUG_N_D2
				cout<<"vecRangesLower: ";
				for ( unsigned int uiActRange = 0; uiActRange < vecRangesLower.size(); uiActRange++ ){
					cout<<"("<<vecRangesLower[uiActRange].x<<";["<<
						vecRangesLower[uiActRange].minY<<" ... "<<vecRangesLower[uiActRange].maxY<<"] ); ";
				}
				cout<<"vecRangesUpper: ";
				for ( unsigned int uiActRange = 0; uiActRange < vecRangesUpper.size(); uiActRange++ ){
					cout<<"("<<vecRangesUpper[uiActRange].x<<";["<<
						vecRangesUpper[uiActRange].minY<<" ... "<<vecRangesUpper[uiActRange].maxY<<"] ); ";
				}
#endif
				continue;//try next area
			}
			DEBUG_OUT_L2(<<"evaluing the polynomLower:"<<endl<<flush);
			//evalue the polynom for the borders
			cPolynom< tX, double > polynomLower;
			polynomLower.evalueGoodPolynom( vecRangesLower, 1024 );
#ifdef DEBUG_N_D2
			cout<<"vecRangesLower: ";
			for ( unsigned int uiActRange = 0; uiActRange < vecRangesLower.size(); uiActRange++ ){
				cout<<"("<<vecRangesLower[uiActRange].x<<";["<<
					vecRangesLower[uiActRange].minY<<" ... "<<vecRangesLower[uiActRange].maxY<<"] ); ";
			}
			cout<<endl<<"polynomLower: ";polynomLower.print( cout );
#endif
			
			cPolynom< tX, double > polynomUpper;
			if ( ! bBordersEqual ){
				DEBUG_OUT_L2(<<"evaluing the polynomUpper:"<<endl<<flush);
				polynomUpper.evalueGoodPolynom( vecRangesUpper, 1024 );
#ifdef DEBUG_N_D2
				cout<<"vecRangesUpper: ";
				for ( unsigned int uiActRange = 0; uiActRange < vecRangesUpper.size(); uiActRange++ ){
					cout<<"("<<vecRangesUpper[uiActRange].x<<";["<<
						vecRangesUpper[uiActRange].minY<<" ... "<<vecRangesUpper[uiActRange].maxY<<"] ); ";
				}
				cout<<endl<<"polynomUpper: ";polynomUpper.print( cout );
#endif
			}
#ifdef DEBUG_N_D2
			cout<<endl<<"evalued ranges: "<<flush;
			for ( unsigned int uiActRange = 0; uiActRange < vecRangesLower.size(); uiActRange++ ){
				cout<<"("<<vecRangesLower[uiActRange].x<<";["<<
					polynomLower.evalue( vecRangesLower[uiActRange].x )<<" ... "<<
					polynomUpper.evalue( vecRangesLower[uiActRange].x )<<"] ); ";
			}
			cout<<endl<<"evalued ranges compared: "<<flush;
			for ( unsigned int uiActRange = 0; (uiActRange < vecRangesLower.size()) &&
					(uiActRange < vecRangesUpper.size()) ; uiActRange++ ){
				cout<<"("<<vecRangesLower[uiActRange].x<<";["<<
					vecRangesLower[uiActRange].minY<<"<"<<flush<<
					polynomLower.evalue( vecRangesLower[uiActRange].x )<<"<"<<flush<<
					vecRangesLower[uiActRange].maxY<<" ... "<<
					vecRangesUpper[uiActRange].minY<<"<"<<flush<<
					polynomUpper.evalue( vecRangesLower[uiActRange].x )<<"<"<<flush<<
					vecRangesUpper[uiActRange].maxY<<"] ); "<<flush;
			}
			if ( vecRangesLower.size() !=  vecRangesUpper.size() ){
				cout<<"Ther are ranges in the lower border: "<<vecRangesLower.size()<<
					" but in the upper border ther are : "<<vecRangesUpper.size()<<endl<<flush;
			}
#endif
			DEBUG_OUT_L2(<<"creating area object"<<endl<<flush);
			cArea * pAreaNew = NULL;
			
			if ( ( ! bBordersEqual ) && ( polynomUpper != polynomLower ) ){
				pAreaNew = createAreaFibObject( bChoosenDirection,
					roundToLongFib( vecRangesLower.front().x ),
					roundToLongFib( vecRangesLower.back().x ),
					polynomLower, polynomUpper );
			}else{
				pAreaNew = createLineFibObject( bChoosenDirection,
					roundToLongFib( vecRangesLower.front().x ),
					roundToLongFib( vecRangesLower.back().x ),
					polynomLower );
			}
#ifdef DEBUG_N_D2_2
			DEBUG_OUT_L2(<<"created area object: "<<endl<<flush);
//			pAreaNew->getDefinedVariable()->setValue( 1.0 );
			//enumerate variables so thy can be identified
			list<cFibVariable*> liDefVariables =
				pAreaNew->getDefinedVariables( ED_BELOW_EQUAL );
			unsigned int uiNumber = 1;
			for ( list<cFibVariable*>::iterator itrVariable = liDefVariables.begin();
					itrVariable != liDefVariables.end(); itrVariable++, uiNumber++ ){
				
				(*itrVariable)->setValue( uiNumber );
			}
			pAreaNew->storeXml( cout );
#endif
			DEBUG_OUT_L2(<<"evaluing points in area object"<<endl<<flush);
			//count points in the area
			cEvaluePositionListLimit evaluedPositionsData(
				ulAceptablePointsForArea + 1, NULL, true, 0, ulAceptablePointsForArea * 16 );
			const bool bObjectEvalued = pAreaNew->evalueObjectSimple( evaluedPositionsData );
			
			const unsigned long ulNumberOfPoints = evaluedPositionsData.liEvaluedPositionData.size();
			DEBUG_OUT_L2(<<"evalued ulNumberOfPoints= "<<ulNumberOfPoints<<"  ulAceptablePointsForArea="<<ulAceptablePointsForArea<<" bObjectEvalued="<<(bObjectEvalued?"true":"false")<<endl<<flush);
			
			bool bAreaAdded = false;
			if ( bObjectEvalued && ( 4 < ulNumberOfPoints ) &&
					( ulNumberOfPoints <= ulAceptablePointsForArea ) ){
				
				//check how many points are in the area to find
				unsigned long ulPointsInMaxArea = 0;
				unsigned long ulPointsInMinArea = 0;
				DEBUG_OUT_L2(<<"Evalud points: "<<flush);
				for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
						itrPoint = evaluedPositionsData.liEvaluedPositionData.begin();
						itrPoint != evaluedPositionsData.liEvaluedPositionData.end();
						itrPoint++ ){
					
					const typeDataPoint dataXPointTmp(
						roundToLongFib( itrPoint->first.getValue( 1 ) ),
						roundToLongFib( itrPoint->first.getValue( 2 ) ) );
					const typeConstItrSetDataPoints itrFoundPointMax =
						setMaximumXArea.find( dataXPointTmp );
					if ( itrFoundPointMax != setMaximumXArea.end() ){
						ulPointsInMaxArea++;
					}
					const typeConstItrSetDataPoints itrFoundPointMin =
						setMinimumXArea.find( dataXPointTmp );
					if ( itrFoundPointMin != setMinimumXArea.end() ){
						ulPointsInMinArea++;
					}
					DEBUG_OUT_L2(<<"( "<<dataXPointTmp.x<<","<<dataXPointTmp.y<<") in "<<((itrFoundPointMax != setMaximumXArea.end())?"max ":"")<<((itrFoundPointMin != setMinimumXArea.end())?"min; ":"; ")<<flush);
				}
				DEBUG_OUT_L2(<<endl<<"points in maximum area: "<<ulPointsInMaxArea<<" points outside the maximum area: "<<(ulNumberOfPoints - ulPointsInMaxArea)<<endl<<flush);
				DEBUG_OUT_L2(<<"points in minimum area: "<<ulPointsInMinArea<<" points outside the minimum area: "<<(ulNumberOfPoints - ulPointsInMinArea)<<endl<<flush);
				
				if ( ( (ulNumberOfPoints - ulNumberOfPoints / 16 - 2) <= ulPointsInMaxArea ) &&
						( (ulNumberOfPoints / 8 + 2) <= ulPointsInMinArea ) ){
					/*no more than 1/16 of the evalued points outside the given area
					-> add created area and remove the points in the created area
					from the minimum area*/
					
					//replace point of the area with the given subobject
					DEBUG_OUT_L2(<<"Replace point of the area with the given subobject"<<endl<<flush);
					cFibElement * pSubobjectToInsert = NULL;
					if ( liAreaList.empty() ){
						//first underarea created -> use the original object pUnderobject
						pSubobjectToInsert = pUnderobject;
					}else{//not the first underarea created -> use the clone of the original object pUnderobject
						pSubobjectToInsert = pUnderobject->copy();
					}
					//replace dimension variables with point variables
					cPoint * pPoint = ((cPoint*)( pAreaNew->getNextFibElement( 'p' ) ));
					
					pSubobjectToInsert->replaceVariable( pVariableDimX, pPoint->getPosition()->getVariable( 1 ) );
					pSubobjectToInsert->replaceVariable( pVariableDimY, pPoint->getPosition()->getVariable( 2 ) );
					
					if ( pSubobjectToInsert == pUnderobject ){
						//variable in the subobject have changed
						pVariableDimX = pPoint->getPosition()->getVariable( 1 );
						pVariableDimY = pPoint->getPosition()->getVariable( 2 );
					}
					//replace the point with the Fib object to insert
					pAreaNew->overwriteObjectWithObject(
						pSubobjectToInsert, 'u', pPoint->getNumberOfElement(), true, true );
					
					
					DEBUG_OUT_L2(<<"Adding creating area to the area list"<<endl<<flush);
					liAreaList.push_back( pair< unsigned long, cFibElement * >( ulNumberOfPoints, pAreaNew ) );
					bAreaAdded = true;
					
					//remove the points in the created area from the minimum area
					for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
							itrPoint = evaluedPositionsData.liEvaluedPositionData.begin();
							itrPoint != evaluedPositionsData.liEvaluedPositionData.end();
							itrPoint++ ){
						
						const typeDataPoint dataXPointTmp(
							roundToLongFib( itrPoint->first.getValue( 1 ) ),
							roundToLongFib( itrPoint->first.getValue( 2 ) ) );
						uiPointsRemoved += setMinimumXArea.erase( dataXPointTmp );
						
						const typeDataPoint dataYPointTmp(
							roundToLongFib( itrPoint->first.getValue( 2 ) ),
							roundToLongFib( itrPoint->first.getValue( 1 ) ) );
						uiPointsRemoved += setMinimumYArea.erase( dataYPointTmp );
					}
				}
			}
			if ( ! bAreaAdded ){//delete the created subobject
				DEBUG_OUT_EL2(<<"Error: Couldn't add the area object"<<endl<<flush);
				
				pAreaNew->deleteObject();
			}
			DEBUG_OUT_L2(<<"uiPointsRemoved= "<<uiPointsRemoved<<"  ulNumberOfPoints= "<<ulNumberOfPoints<<"  ulAceptablePointsForArea="<<ulAceptablePointsForArea<<endl<<flush);
			if ( uiPointsRemoved != 0 ){
				DEBUG_OUT_L2(<<"Find the remaining areas to convert."<<endl<<flush);
				break;
			}else{
				DEBUG_OUT_EL2(<<"Warning: no points removed -> try next bigges area"<<endl<<flush);
				//Error: no points removed -> abourt evaluation so it dosn't loop infinity
			}
			//TODO?? remove points betwean borders from the maximum area in the direction
		}//end for itrActualToConvertArea
			
		if ( (uiPointsRemoved == 0) && ( ! setAreas.empty() ) ){
			/*if no wher removed
			-> smooth border and decrease area*/
			DEBUG_OUT_L2(<<"Area with to much points generated (and no points removed) "<<endl<<flush);
			
			const typeSetDataPoints setRemovedPoints = smoothBorders(
				*(setAreas.begin()->second.first),
				setAreas.begin()->second.second,
				setMaximumXArea, setMaximumYArea,
				setMinimumXArea, setMinimumYArea );
			uiPointsRemoved = setRemovedPoints.size();
			
			DEBUG_OUT_L2(<<"The number of removed points from the minimal areas is: "<<uiPointsRemoved<<endl<<flush);
			if ( uiPointsRemoved != 0 ){
				DEBUG_OUT_L2(<<"Find the remaining areas to convert."<<endl<<flush);
				break;
			}else{
				DEBUG_OUT_EL2(<<"Warning: no points removed -> try next bigges area"<<endl<<flush);
				//Error: no points removed -> abourt evaluation so it dosn't loop infinity
			}
		}

		
		if ( uiPointsRemoved == 0 ){
			DEBUG_OUT_EL2(<<"Warning: for no area points removed -> stopping evaluation, so no infinit loop occurs"<<endl<<flush);
			break;
		}
	}
	
	if ( liAreaList.empty() ){
		DEBUG_OUT_L2(<<"Warning: no subarea evalued"<<endl<<flush);
		//no area elements to return
		return NULL;
	}//else
	if ( liAreaList.size() == 1 ){
		DEBUG_OUT_L2(<<"one subarea evalued"<<endl<<flush);
		return liAreaList.front().second;
	}
	DEBUG_OUT_L2(<<"number of subarea evalued: "<<liAreaList.size()<<endl<<flush);
	//if more than one object was created, combine the created subobjects to an listelement
	liAreaList.sort( fib::algorithms::nD2::lowerFirstNumber );
	
	list<cFibElement*> liUnderobjects;
	while ( ! liAreaList.empty() ){
		liUnderobjects.push_back( liAreaList.back().second );
		liAreaList.pop_back();
	}
	DEBUG_OUT_L2(<<"Creating list-object "<<endl<<flush);
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cList * pList = new cList( liUnderobjects );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cList * pList = new cList( NULL, NULL );
	pList->addUnderobjects( liUnderobjects );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	DEBUG_OUT_L2(<<"createAreasForPoints(#setPoints="<<setPoints.size()<<", pUnderobject="<<pUnderobject<<", varX="<<pVariableDimX<<", varY="<<pVariableDimY<<") done "<<endl<<flush);
	return pList;
}



/**
 * This function combines the given set of points to Fib objects,
 * with the help of splies (polynoms with fixed number of parametes
 * uiMaxSplineParameters) .
 * Beware: You have to care that the created subobjects will be deleted
 *
 * uses @see nD1::cPolynom::evalueSpline()
 * @param setPoints the set with the datapoints to combine to
 * 	Fib objects with the help of area and function elements;
 * 	The given points should be positions in an matrix, positions in
 * 	the matrix but not given, will be considerd not to be in the area
 * 	to create.
 * @param pUnderobject a pointer to the subobject, which the created
 * 	Fib elements should contain and which should be evalued for the
 * 	point positions
 * @param pVariableX a pointer to the variable for the x position
 * @param pVariableY a pointer to the variable for the y position
 * @param uiMaxSplineParameters the number of parameters for the spline;
 * 	Don't choose this number to big, because the evaluation time will
 * 	grow exponentialy with this number. Even splines with 8
 * 	parameters will take some time.
 * @param uiMinBitsToStoreMantissa the minimal number of bits to store
 * 	the mantissa of the function value parameters, when the parameter
 * 	is in the form: mantissa * 2^exponent ;
 * 	the method will try to reduce the bits, to store a parameter of the
 * 	returned vector, to the uiMinBitsToStoreMantissa value;
 * 	if uiMinBitsToStoreMantissa is 0, no optimization for the mantissa
 * 	bits will be done
 * @param maxValue the maximum possible value in all parameters
 * 	the evalued spline/function elements will allways have value
 * 	parameters vecFactors[i] with
 * 	-1 * maxValue <= vecFactors[i] <= maxValue for 0 <= i \< vecFactors.size();
 * 	if 0 (standard value) is given, the maximum possible value will
 * 	be evalued from the given data
 * @param ulMaxMemoryCost a number for the maximum memory cost this
 * 	method is allowed to use; if 0 the maximum memory cost is unbounded
 * @return a Fib object with the created Fib subobjects, which go
 * 	over all point positions in the given set setPoints or NULL if non
 * 	such could be created;
 * 	some positions can be evalued twice;
 * 	the Fib subobjects, wich evalue the most points, are on the
 * 	front of the list-object (have a lower subobject number);
 * 	if NULL is returnd, you have to care that pUnderobject will be
 * 	deleted, else pUnderobject will be included in one
 * 	subobject of the created list-object and the other subobject will
 * 	contain copies of pUnderobject
 * 	Structur of the created Fib object:
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 	or if this previos given structur is not possible
 * 		list(
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 			...
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 		)
 */
template <class tX>
	cFibElement * fib::algorithms::nD2::createSplineBorderAreasForPoints(
		const set< nD1::cDataPoint<tX, tX> > & setPoints,
		cFibElement * pUnderobject,
		cFibVariable * pVariableDimX,
		cFibVariable * pVariableDimY,
		const unsigned int uiMaxSplineParameters,
		const unsigned int uiMinBitsToStoreMantissa,
		double maxValue,
		const unsigned long ulMaxMemoryCost ){
	
	DEBUG_OUT_L2(<<"createSplineBorderAreasForPoints(#setPoints="<<setPoints.size()<<", pUnderobject="<<pUnderobject<<", varX="<<pVariableDimX<<", varY="<<pVariableDimY<<", uiMaxSplineParameters="<<uiMaxSplineParameters<<", uiMinBitsToStoreMantissa="<<uiMinBitsToStoreMantissa<<", maxValue="<<maxValue<<", ulMaxMemoryCost="<<ulMaxMemoryCost<<" ) started "<<endl<<flush);
	
	if ( setPoints.empty() ){
		//no data points, for which to create the areas
		return NULL;
	}
	if ( pUnderobject == NULL ){
		//no subobject, wich to use in created Fib objects
		return NULL;
	}
	if ( ( pVariableDimX == NULL ) || ( pVariableDimY == NULL ) ){
		//missing variable, wich to use in created Fib objects
		return NULL;
	}
	if ( uiMaxSplineParameters == 0 ){
		//can't create spline with 0 parameters, which match datapoints
		return NULL;
	}
	if ( maxValue < 0.0 ){
		//can't create spline with this maximum value
		return NULL;
	}//else
	
	typedef fib::algorithms::nD1::cDataPoint<tX, tX> typeDataPoint;
	typedef set< typeDataPoint > typeSetDataPoints;
	typedef typename typeSetDataPoints::const_iterator typeConstItrSetDataPoints;
	typedef typename typeSetDataPoints::const_reverse_iterator typeConstRevItrSetDataPoints;
	
	if ( maxValue == 0.0 ){
		//evalue the maximum value
		double dMaxDataValue = 0.0;
		for ( typeConstItrSetDataPoints itrPoint = setPoints.begin();
				itrPoint != setPoints.end(); itrPoint++ ){
			
			const tX absY = ( 0 <= itrPoint->y )?( itrPoint->y ):( ((tX)(-1)) * itrPoint->y );
			if ( dMaxDataValue < absY ){
				dMaxDataValue = absY;
			}
			const tX absX = ( 0 <= itrPoint->x )?( itrPoint->x ):( ((tX)(-1)) * itrPoint->x );
			if ( dMaxDataValue < absX ){
				dMaxDataValue = absX;
			}
		}
		if ( dMaxDataValue ){
			dMaxDataValue = 1.0;
		}
		maxValue = dMaxDataValue * 1024.0;
	}//end if maxValue == 0
	
	/*create areas for the minimum and maximum number of points in the
	directions (the maximum area is the area of points, which can be contained
	in an created area object, the minimum is the area of points, which are
	not contained in an other created areas)*/
	typeSetDataPoints setMaximumXArea = setPoints;
	typeSetDataPoints setMinimumXArea = setMaximumXArea;
	
	/*the Y Areas /Sets are the same as the X Areas/Sets, but of a matrix
	rotated with 90 degree*/
	typeSetDataPoints setMaximumYArea;
	
	for ( typeConstItrSetDataPoints itrPoint = setPoints.begin();
			itrPoint != setPoints.end(); itrPoint++ ){
		
		setMaximumYArea.insert( typeDataPoint( itrPoint->y, itrPoint->x ) );
	}
	typeSetDataPoints setMinimumYArea = setMaximumYArea;

	/*the created elemental areas;
		- first pair element: number of points, the area covers
		- second pair element: the the area as an Fib object*/
	list< pair< unsigned long, cFibElement * > > liAreaList;
	
	DEBUG_OUT_L2(<<"beginning searching for areas"<<endl<<flush);
	
	//while not all points are included in the area
	while ( ( ! setMinimumXArea.empty() ) ||  ( ! setMinimumYArea.empty() ) ){
	/*create areas:
		- begin at the outer side of the minimum areas of points which
			should be found; prefer big areas
		- remove points from the minimum areas, which are included in created areas
		- borders are points, which should be in the area, but which
			neibours shouldn't be in the area*/
		
		//scan in x direction
		/* The list with the possible areas.
		* The pair elements are:
		* 	first element: the number of points in the possible area
		* 	second element: list with the possible areas containing each a
		* 	list with the pairs for the lines: first element is the upper
		* 	border of the line and the second the lower border
		*/
		typedef list< pair< unsigned long, list< pair< typeDataPoint,
			typeDataPoint > > > > typePossibleAreas;
		typePossibleAreas possibleXAreas;
		
		typeConstItrSetDataPoints itrPoint = setMinimumXArea.begin();
		typeDataPoint dataPoint = *itrPoint;
		typeDataPoint dataPointLineBegin = *itrPoint;
		
		while ( itrPoint != setMinimumXArea.end() ){
			
			if ( dataPoint != *itrPoint ){
				/*this point isn't the x neibour of the last point
				-> new line begin; *itrXPoint = new line begin; dataPoint.y-- = old line end*/
				dataPoint.y--;//old line end
				/*insert old line to every possible area or create a new area, if
				no possible area exists*/
				const pair< typeDataPoint, typeDataPoint >
					paNewLine( dataPointLineBegin, dataPoint);
				integrateLineInAreas( possibleXAreas, paNewLine );
	
				dataPointLineBegin = *itrPoint;//remember line begin
			}
			dataPoint = *itrPoint;
			itrPoint++;
			dataPoint.y++;//next neibour in x direction for the last point
		}
		{//add last line
			dataPoint.y--;
			const pair< typeDataPoint, typeDataPoint >
				paNewLine( dataPointLineBegin, dataPoint);
			integrateLineInAreas( possibleXAreas, paNewLine );
		}
		//scan in y direction
		typePossibleAreas possibleYAreas;
		
		itrPoint = setMinimumYArea.begin();
		dataPoint = *itrPoint;
		dataPointLineBegin = *itrPoint;
		
		while ( itrPoint != setMinimumYArea.end() ){
			
			if ( dataPoint != *itrPoint ){
				/*this point isn't the x neibour of the last point
				-> new line begin; *itrXPoint = new line begin; dataPoint.y-- = old line end*/
				dataPoint.y--;//old line end
				/*insert old line to every possible area or create a new area, if
				no possible area exists*/
				const pair< typeDataPoint, typeDataPoint >
					paNewLine( dataPointLineBegin, dataPoint);
				integrateLineInAreas( possibleYAreas, paNewLine );
	
				dataPointLineBegin = *itrPoint;//remember line begin
			}
			dataPoint = *itrPoint;
			itrPoint++;
			dataPoint.y++;//next neibour in x direction for the last point
		}
		{//add last line
			dataPoint.y--;
			const pair< typeDataPoint, typeDataPoint >
				paNewLine( dataPointLineBegin, dataPoint);
			integrateLineInAreas( possibleYAreas, paNewLine );
		}
		//choose the area for which to create the Fib structur
		/*the type filds are:
			- number of points in the area
				- iterator to the area
				- if the area is a x area (x = true; y = false)*/
		typedef set< pair< unsigned long, pair< typename typePossibleAreas::const_iterator, bool > >,
				structLowerFirstElement< pair< typename typePossibleAreas::const_iterator, bool > > >
				typeSetOrderdAreas;
		typeSetOrderdAreas setAreas;
		
		for ( typename typePossibleAreas::const_iterator itrActualArea = possibleXAreas.begin();
				itrActualArea != possibleXAreas.end(); itrActualArea++ ){
			
			setAreas.insert( make_pair( itrActualArea->first, make_pair( itrActualArea, true ) ) );
		}
		for ( typename typePossibleAreas::const_iterator itrActualArea = possibleYAreas.begin();
				itrActualArea != possibleYAreas.end(); itrActualArea++ ){
			
			setAreas.insert( make_pair( itrActualArea->first, make_pair( itrActualArea, false ) ) );
		}
		
		//try biggest area and than the areas befor, if biggest area couldn't be used
		typename typeSetOrderdAreas::const_reverse_iterator
				itrActualToConvertArea = setAreas.rbegin();
		unsigned long uiPointsRemoved = 0;
		for ( ; itrActualToConvertArea != setAreas.rend(); itrActualToConvertArea++ ){
			
			if ( itrActualToConvertArea->first <= 4 ){
				DEBUG_OUT_L2(<<"just maximal "<<itrActualToConvertArea->first<<" points in remaining areas"<<endl<<flush);
				//stop evaluation, because no area with more than 4 points exists
				itrActualToConvertArea = setAreas.rend();
				break;
			}
			
			const typename typePossibleAreas::const_iterator itrToConvertArea =
				itrActualToConvertArea->second.first;
			//x = true; y = false
			const bool bChoosenDirection = itrActualToConvertArea->second.second;
			
			//evalue ranges for the choosen area in directions
			typedef list< pair< typeDataPoint, typeDataPoint > > typeDataPointList;
			typedef typename typeDataPointList::const_iterator typeItrDataPointList;
#ifdef DEBUG_N_D2
			cout<<"founded best datapoints (direction "<<(bChoosenDirection?"x":"y")<<" ): ";
			for ( typeItrDataPointList itrDataPoint = itrToConvertArea->second.begin();
					itrDataPoint != itrToConvertArea->second.end(); itrDataPoint++ ){
				cout<<"("<< itrDataPoint->first.x <<";[ "<< itrDataPoint->first.y
					<<" ... "<< itrDataPoint->second.y <<" ] ); ";
			}
			cout<<endl;
#endif
			DEBUG_OUT_L2(<<"creating range datapoints for areas"<<endl<<flush);
			vector< fib::algorithms::nD1::cDataPointRange< tX, double > > vecRangesUpper;
			vector< fib::algorithms::nD1::cDataPointRange< tX, double > > vecRangesLower;
			
			const bool bBordersEqual = findBorderRanges( *itrToConvertArea,
				bChoosenDirection, setMaximumXArea, setMaximumYArea,
				vecRangesLower, vecRangesUpper );
	
			if ( vecRangesLower.empty() || vecRangesUpper.empty() ){
				DEBUG_OUT_EL2(<<"one range empty:"<<endl<<flush);
#ifdef DEBUG_N_D2
				cout<<"vecRangesLower: ";
				for ( unsigned int uiActRange = 0; uiActRange < vecRangesLower.size(); uiActRange++ ){
					cout<<"("<<vecRangesLower[uiActRange].x<<";["<<
						vecRangesLower[uiActRange].minY<<" ... "<<vecRangesLower[uiActRange].maxY<<"] ); ";
				}
				cout<<"vecRangesUpper: ";
				for ( unsigned int uiActRange = 0; uiActRange < vecRangesUpper.size(); uiActRange++ ){
					cout<<"("<<vecRangesUpper[uiActRange].x<<";["<<
						vecRangesUpper[uiActRange].minY<<" ... "<<vecRangesUpper[uiActRange].maxY<<"] ); ";
				}
#endif
				continue;//check next area
			}
			//the x offset so that the spline will begin at 0
			const tX xOffset = vecRangesUpper[ 0 ].x;
			
			//dismiss created areas which have (much) more points as in the maximal area
			unsigned long ulAceptablePointsForArea = 8;
			for ( unsigned int uiActRange = 0; uiActRange < vecRangesLower.size(); uiActRange++ ){
				
				ulAceptablePointsForArea += vecRangesUpper[uiActRange].maxY - vecRangesLower[uiActRange].minY + 1;
				
				//move the x component about the offset (subtract offset)
				vecRangesUpper[ uiActRange ].x -= xOffset;
				vecRangesLower[ uiActRange ].x -= xOffset;
			}
			
			//evalue the splines for the borders
			DEBUG_OUT_L2(<<"The borders are "<<(bBordersEqual?"equal":"not equal")<<endl);
			DEBUG_OUT_L2(<<"evaluing the spline for the lower border:"<<endl<<flush);
			cPolynom< tX, double > polynomLower;
			const unsigned long uiPointsIncludedLower = polynomLower.evalueSpline(
				vecRangesLower, uiMaxSplineParameters,
				uiMinBitsToStoreMantissa, maxValue, ulMaxMemoryCost );
			
#ifdef DEBUG_N_D2
			cout<<"vecRangesLower: ";
			for ( unsigned int uiActRange = 0; uiActRange < vecRangesLower.size(); uiActRange++ ){
				cout<<"("<<vecRangesLower[uiActRange].x<<";["<<
					vecRangesLower[uiActRange].minY<<" ... "<<vecRangesLower[uiActRange].maxY<<"] ); ";
			}
			cout<<endl<<"spline for lower border (for the "<<uiPointsIncludedLower<<" first points): ";polynomLower.print( cout );
#endif
			if ( uiPointsIncludedLower < 1 ){
				//no points included -> no lower border
				continue;//check next area
			}
			cPolynom< tX, double > polynomUpper;
			unsigned long uiLastPointsIncluded = uiPointsIncludedLower - 1;
			if ( ! bBordersEqual ){
				
				if ( uiPointsIncludedLower < vecRangesUpper.size()  ){
					//don't need to include all points in the upper range
					vecRangesUpper.resize( uiPointsIncludedLower );
				}
				DEBUG_OUT_L2(<<"evaluing the spline for the upper border:"<<endl<<flush);
				const unsigned long uiPointsIncludedUpper = polynomUpper.evalueSpline(
					vecRangesUpper, uiMaxSplineParameters,
					uiMinBitsToStoreMantissa, maxValue, ulMaxMemoryCost );
				
				if ( uiPointsIncludedUpper < 1 ){
					//no points included -> no upper border
					continue;//check next area
				}
				
				uiLastPointsIncluded = min(
					uiPointsIncludedLower, uiPointsIncludedUpper ) - 1;
#ifdef DEBUG_N_D2
				cout<<"vecRangesUpper: ";
				for ( unsigned int uiActRange = 0; uiActRange < vecRangesUpper.size(); uiActRange++ ){
					cout<<"("<<vecRangesUpper[uiActRange].x<<";["<<
						vecRangesUpper[uiActRange].minY<<" ... "<<vecRangesUpper[uiActRange].maxY<<"] ); ";
				}
				cout<<endl<<"spline for upper border (for the "<<uiPointsIncludedUpper<<" first points): ";polynomUpper.print( cout );
#endif
			}//else borders are equal -> don't need to evalue spline for upper border
#ifdef DEBUG_N_D2
			cout<<endl<<"evalued ranges: "<<flush;
			for ( unsigned int uiActRange = 0; uiActRange < vecRangesLower.size(); uiActRange++ ){
				cout<<"("<<vecRangesLower[uiActRange].x<<";["<<
					polynomLower.evalue( vecRangesLower[uiActRange].x )<<" ... "<<
					polynomUpper.evalue( vecRangesLower[uiActRange].x )<<"] ); ";
			}
			cout<<endl<<"evalued ranges compared: "<<flush;
			for ( unsigned int uiActRange = 0; (uiActRange < vecRangesLower.size()) &&
					(uiActRange < vecRangesUpper.size()) ; uiActRange++ ){
				cout<<"("<<vecRangesLower[uiActRange].x<<";["<<
					vecRangesLower[uiActRange].minY<<"<"<<flush<<
					polynomLower.evalue( vecRangesLower[uiActRange].x )<<"<"<<flush<<
					vecRangesLower[uiActRange].maxY<<" ... "<<
					vecRangesUpper[uiActRange].minY<<"<"<<flush<<
					polynomUpper.evalue( vecRangesLower[uiActRange].x )<<"<"<<flush<<
					vecRangesUpper[uiActRange].maxY<<"] ); "<<flush;
			}
			cout<<endl;
			if ( vecRangesLower.size() !=  vecRangesUpper.size() ){
				cout<<"Ther are ranges in the lower border: "<<vecRangesLower.size()<<
					" but in the upper border ther are : "<<vecRangesUpper.size()<<endl<<flush;
			}
#endif
			//include points wich are in max bounderies
			size_t correctPointsInBounderies = uiLastPointsIncluded + 1;
			while ( correctPointsInBounderies < vecRangesUpper.size() ){
				
				const tX x = vecRangesUpper[ correctPointsInBounderies ].x;
				const double dMinValueLower = vecRangesLower[ correctPointsInBounderies ].minY;
				const double dMaxValueUpper = vecRangesUpper[ correctPointsInBounderies ].maxY;
				
				const double dValueLower = polynomLower.evalue( x );
				const double dValueUpper = polynomUpper.evalue( x );
				
				if ( ( dMinValueLower <= dValueLower ) && ( dValueLower <= dMaxValueUpper ) &&
						( dMinValueLower <= dValueUpper ) && ( dValueUpper <= dMaxValueUpper ) ){
					//values of the evalued polynom is in bounderies
					correctPointsInBounderies++;
				}else{
					break;
				}
			}
			DEBUG_OUT_L2(<<"correct points in bounderies "<<correctPointsInBounderies<<endl<<flush);
			if ( correctPointsInBounderies != vecRangesLower.size() ){
				vecRangesLower.resize( correctPointsInBounderies );
			}
			if ( correctPointsInBounderies != vecRangesUpper.size() ){
				vecRangesUpper.resize( correctPointsInBounderies );
			}
			
			DEBUG_OUT_L2(<<"creating area object"<<endl<<flush);
			cArea * pAreaNew = NULL;
			
			if ( ( ! bBordersEqual ) && ( polynomUpper != polynomLower ) ){
				pAreaNew = createAreaFibObject( bChoosenDirection,
					roundToLongFib( vecRangesLower.front().x ),
					roundToLongFib( vecRangesLower.back().x ),
					polynomLower, polynomUpper, xOffset );
			}else{
				pAreaNew = createLineFibObject( bChoosenDirection,
					roundToLongFib( vecRangesLower.front().x ),
					roundToLongFib( vecRangesLower.back().x ),
					polynomLower, xOffset );
			}
#ifdef DEBUG_N_D2_2
			DEBUG_OUT_L2(<<"created area object: "<<endl<<flush);
//			pAreaNew->getDefinedVariable()->setValue( 1.0 );
			//enumerate variables so thy can be identified
			list<cFibVariable*> liDefVariables =
				pAreaNew->getDefinedVariables( ED_BELOW_EQUAL );
			unsigned int uiNumber = 1;
			for ( list<cFibVariable*>::iterator itrVariable = liDefVariables.begin();
					itrVariable != liDefVariables.end(); itrVariable++, uiNumber++ ){
				
				(*itrVariable)->setValue( uiNumber );
			}
			pAreaNew->storeXml( cout );
#endif
			DEBUG_OUT_L2(<<"evaluing points in area object"<<endl<<flush);
			//count points in the area
			cEvaluePositionListLimit evaluedPositionsData(
				ulAceptablePointsForArea + 1, NULL, true, 0, ulAceptablePointsForArea * 16 );
			const bool bObjectEvalued = pAreaNew->evalueObjectSimple( evaluedPositionsData );
			
			const unsigned long ulNumberOfPoints = evaluedPositionsData.liEvaluedPositionData.size();
			DEBUG_OUT_L2(<<"evalued ulNumberOfPoints= "<<ulNumberOfPoints<<"  ulAceptablePointsForArea="<<ulAceptablePointsForArea<<" bObjectEvalued="<<(bObjectEvalued?"true":"false")<<endl<<flush);
			
			bool bAreaAdded = false;
			if ( bObjectEvalued && ( 4 < ulNumberOfPoints ) &&
					( ulNumberOfPoints <= ulAceptablePointsForArea ) ){
				
				//check how many points are in the area to find
				unsigned long ulPointsInMaxArea = 0;
				unsigned long ulPointsInMinArea = 0;
				DEBUG_OUT_L2(<<"Evalud points: "<<flush);
				for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
						itrPoint = evaluedPositionsData.liEvaluedPositionData.begin();
						itrPoint != evaluedPositionsData.liEvaluedPositionData.end();
						itrPoint++ ){
					
					const typeDataPoint dataXPointTmp(
						roundToLongFib( itrPoint->first.getValue( 1 ) ),
						roundToLongFib( itrPoint->first.getValue( 2 ) ) );
					const typeConstItrSetDataPoints itrFoundPointMax =
						setMaximumXArea.find( dataXPointTmp );
					if ( itrFoundPointMax != setMaximumXArea.end() ){
						ulPointsInMaxArea++;
					}
					const typeConstItrSetDataPoints itrFoundPointMin =
						setMinimumXArea.find( dataXPointTmp );
					if ( itrFoundPointMin != setMinimumXArea.end() ){
						ulPointsInMinArea++;
					}
					DEBUG_OUT_L2(<<"( "<<dataXPointTmp.x<<","<<dataXPointTmp.y<<") in "<<((itrFoundPointMax != setMaximumXArea.end())?"max ":"")<<((itrFoundPointMin != setMinimumXArea.end())?"min; ":"; ")<<flush);
				}
				DEBUG_OUT_L2(<<endl<<"points in maximum area: "<<ulPointsInMaxArea<<" points outside the maximum area: "<<(ulNumberOfPoints - ulPointsInMaxArea)<<endl<<flush);
				DEBUG_OUT_L2(<<"points in minimum area: "<<ulPointsInMinArea<<" points outside the minimum area: "<<(ulNumberOfPoints - ulPointsInMinArea)<<endl<<flush);
				
				if ( ( (ulNumberOfPoints - ulNumberOfPoints / 16 - 2) <= ulPointsInMaxArea ) &&
						( (ulNumberOfPoints / 8 + 2) <= ulPointsInMinArea ) ){
					/*no more than 1/16 of the evalued points outside the given area
					-> add created area and remove the points in the created area
					from the minimum area*/
					
					//replace point of the area with the given subobject
					DEBUG_OUT_L2(<<"Replace point of the area with the given subobject"<<endl<<flush);
					cFibElement * pSubobjectToInsert = NULL;
					if ( liAreaList.empty() ){
						//first underarea created -> use the original object pUnderobject
						pSubobjectToInsert = pUnderobject;
					}else{//not the first underarea created -> use the clone of the original object pUnderobject
						pSubobjectToInsert = pUnderobject->copy();
					}
					//replace dimension variables with point variables
					cPoint * pPoint = ((cPoint*)( pAreaNew->getNextFibElement( 'p' ) ));
					
					pSubobjectToInsert->replaceVariable( pVariableDimX, pPoint->getPosition()->getVariable( 1 ) );
					pSubobjectToInsert->replaceVariable( pVariableDimY, pPoint->getPosition()->getVariable( 2 ) );
					
					if ( pSubobjectToInsert == pUnderobject ){
						//variable in the subobject have changed
						pVariableDimX = pPoint->getPosition()->getVariable( 1 );
						pVariableDimY = pPoint->getPosition()->getVariable( 2 );
					}
					//replace the point with the Fib object to insert
					pAreaNew->overwriteObjectWithObject(
						pSubobjectToInsert, 'u', pPoint->getNumberOfElement(), true, true );
					
					
					DEBUG_OUT_L2(<<"Adding creating area to the area list"<<endl<<flush);
					liAreaList.push_back( pair< unsigned long, cFibElement * >( ulNumberOfPoints, pAreaNew ) );
					bAreaAdded = true;
					
					//remove the points in the created area from the minimum area
					for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
							itrPoint = evaluedPositionsData.liEvaluedPositionData.begin();
							itrPoint != evaluedPositionsData.liEvaluedPositionData.end();
							itrPoint++ ){
						
						const typeDataPoint dataXPointTmp(
							roundToLongFib( itrPoint->first.getValue( 1 ) ),
							roundToLongFib( itrPoint->first.getValue( 2 ) ) );
						uiPointsRemoved += setMinimumXArea.erase( dataXPointTmp );
						
						const typeDataPoint dataYPointTmp(
							roundToLongFib( itrPoint->first.getValue( 2 ) ),
							roundToLongFib( itrPoint->first.getValue( 1 ) ) );
						uiPointsRemoved += setMinimumYArea.erase( dataYPointTmp );
					}
				}
			}
			if ( ! bAreaAdded ){//delete the created subobject
				DEBUG_OUT_EL2(<<"Warning: couldn't add the area object"<<endl<<flush);
				
				pAreaNew->deleteObject();
			}
			DEBUG_OUT_L2(<<"uiPointsRemoved= "<<uiPointsRemoved<<"  ulNumberOfPoints= "<<ulNumberOfPoints<<"  ulAceptablePointsForArea="<<ulAceptablePointsForArea<<endl<<flush);
			if ( uiPointsRemoved != 0 ){
				DEBUG_OUT_L2(<<"Find the remaining areas to convert."<<endl<<flush);
				break;
			}else{
				DEBUG_OUT_EL2(<<"Warning: no points removed -> try next bigges area"<<endl<<flush);
				//Error: no points removed -> abourt evaluation so it dosn't loop infinity
			}
			//TODO?? remove points betwean borders from the maximum area in the direction
		}//end for itrActualToConvertArea
			
			
		if ( (uiPointsRemoved == 0) && ( ! setAreas.empty() ) ){
			/*if no wher removed
			-> smooth border and decrease area*/
			DEBUG_OUT_L2(<<"Area with to much points generated (and no points removed) "<<endl<<flush);
			
			const typeSetDataPoints setRemovedPoints = smoothBorders(
				*(setAreas.begin()->second.first),
				setAreas.begin()->second.second,
				setMaximumXArea, setMaximumYArea,
				setMinimumXArea, setMinimumYArea );
			uiPointsRemoved = setRemovedPoints.size();
			
			DEBUG_OUT_L2(<<"The number of removed points from the minimal areas is: "<<uiPointsRemoved<<endl<<flush);
			if ( uiPointsRemoved != 0 ){
				DEBUG_OUT_L2(<<"Find the remaining areas to convert."<<endl<<flush);
				break;
			}else{
				DEBUG_OUT_EL2(<<"Warning: no points removed -> try next bigges area"<<endl<<flush);
				//Error: no points removed -> abourt evaluation so it dosn't loop infinity
			}
		}
		
		if ( uiPointsRemoved == 0 ){
			DEBUG_OUT_EL2(<<"Warning: for no area points removed -> stopping evaluation, so no infinit loop occurs"<<endl<<flush);
			break;
		}
	}
	
	if ( liAreaList.empty() ){
		DEBUG_OUT_L2(<<"Warning: no subarea evalued"<<endl<<flush);
		//no area elements to return
		return NULL;
	}//else
	if ( liAreaList.size() == 1 ){
		DEBUG_OUT_L2(<<"one subarea evalued"<<endl<<flush);
		return liAreaList.front().second;
	}
	DEBUG_OUT_L2(<<"number of subarea evalued: "<<liAreaList.size()<<endl<<flush);
	//if more than one object was created, combine the created subobjects to an listelement
	liAreaList.sort( fib::algorithms::nD2::lowerFirstNumber );
	
	list<cFibElement*> liUnderobjects;
	while ( ! liAreaList.empty() ){
		liUnderobjects.push_back( liAreaList.back().second );
		liAreaList.pop_back();
	}
	DEBUG_OUT_L2(<<"Creating list-object "<<endl<<flush);
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cList * pList = new cList( liUnderobjects );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cList * pList = new cList( NULL, NULL );
	pList->addUnderobjects( liUnderobjects );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
	DEBUG_OUT_L2(<<"createSplineBorderAreasForPoints(#setPoints="<<setPoints.size()<<", pUnderobject="<<pUnderobject<<", varX="<<pVariableDimX<<", varY="<<pVariableDimY<<", uiMaxSplineParameters="<<uiMaxSplineParameters<<", maxValue="<<maxValue<<
	") done "<<endl<<flush);
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
	DEBUG_OUT_L2(<<"createSplineBorderAreasForPoints(#setPoints="<<setPoints.size()<<", pUnderobject="<<pUnderobject<<", varX="<<pVariableDimX<<", varY="<<pVariableDimY<<", uiMaxSplineParameters="<<uiMaxSplineParameters<<", uiMinBitsToStoreMantissa="<<uiMinBitsToStoreMantissa<<", maxValue="<<maxValue<<", ulMaxMemoryCost="<<ulMaxMemoryCost<<" ) done "<<endl<<flush);
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
	return pList;
}


#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING

/**
 * This function combines the given set of points to Fib objects,
 * with the help of splies (polynoms with fixed number of parametes
 * uiMaxSplineParameters) .
 * Beware: You have to care that the created subobjects will be deleted
 *
 * uses @see nD1::cPolynom::evalueSplineIterativFast()
 * The method should give the same result as
 * createSplineBorderAreasForPoints() but faster.
 * It will iterativ increase the number of parameters for the splines
 * (from 1 to uiMaxNumberOfParameters) and will try to not use all of
 * the given range points to find the polynom.
 *
 * @param setPoints the set with the datapoints to combine to
 * 	Fib objects with the help of area and function elements;
 * 	The given points should be positions in an matrix, positions in
 * 	the matrix but not given, will be considerd not to be in the area
 * 	to create.
 * @param pUnderobject a pointer to the subobject, which the created
 * 	Fib elements should contain and which should be evalued for the
 * 	point positions
 * @param pVariableX a pointer to the variable for the x position
 * @param pVariableY a pointer to the variable for the y position
 * @param uiMaxSplineParameters the number of parameters for the spline;
 * 	Don't choose this number to big, because the evaluation time will
 * 	grow exponentialy with this number. Even splines with 8
 * 	parameters will take some time.
 * @param maxValue the maximum possible value in all parameters
 * 	the evalued spline/function elements will allways have value
 * 	parameters vecFactors[i] with
 * 	-1 * maxValue <= vecFactors[i] <= maxValue for 0 <= i \< vecFactors.size();
 * 	if 0 (standard value) is given, the maximum possible value will
 * 	be evalued from the given data
 * @param maxError the maximal error for the border polynoms to find;
 * 	the error on the interpolated polynoms for the borders will be
 * 	equal or less than maxError
 * @param maxErrorPerValue the maximal error for the border polynoms to
 * 	find on one border point; the error on the interpolated polynom
 * 	for every border point in vecData will be equal or less than
 * 	maxErrorPerValue
 * @return a Fib object with the created Fib subobjects, which go
 * 	over all point positions in the given set setPoints or NULL if non
 * 	such could be created;
 * 	some positions can be evalued twice;
 * 	the Fib subobjects, wich evalue the most points, are on the
 * 	front of the list-object (have a lower subobject number);
 * 	if NULL is returnd, you have to care that pUnderobject will be
 * 	deleted, else pUnderobject will be included in one
 * 	subobject of the created list-object and the other subobject will
 * 	contain copies of pUnderobject
 * 	Structur of the created Fib object:
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 	or if this previos given structur is not possible
 * 		list(
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 			...
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 		)
 */
template <class tX>
	cFibElement * fib::algorithms::nD2::createSplineItrFastBorderAreasForPoints(
		const set< nD1::cDataPoint<tX, tX> > & setPoints,
		cFibElement * pUnderobject,
		cFibVariable * pVariableDimX,
		cFibVariable * pVariableDimY,
		const unsigned int uiMaxSplineParameters,
		double maxValue,
		const double maxError,
		const double maxErrorPerValue ){
	
	DEBUG_OUT_L2(<<"createSplineItrFastBorderAreasForPoints(#setPoints="<<setPoints.size()<<", pUnderobject="<<pUnderobject<<", varX="<<pVariableDimX<<", varY="<<pVariableDimY<<", uiMaxSplineParameters="<<uiMaxSplineParameters<<", maxValue="<<maxValue<<", maxError="<<maxError<<", maxErrorPerValue="<<maxErrorPerValue<<" ) started "<<endl<<flush);
	
	return fib::algorithms::nD2::createSplineItrFastBorderAreasForPoints(
		setPoints, setPoints, pUnderobject, pVariableDimX, pVariableDimY,
		uiMaxSplineParameters, (set< nD1::cDataPoint<tX, tX> > *)(NULL),
		maxValue, maxError, maxErrorPerValue );
}


/**
 * This function combines the given set of points to Fib objects,
 * with the help of splies (polynoms with fixed number of parametes
 * uiMaxSplineParameters) .
 * Beware: You have to care that the created subobjects will be deleted
 *
 * uses @see nD1::cPolynom::evalueSplineIterativFast()
 * The method should give the same result as
 * createSplineBorderAreasForPoints() but faster.
 * It will iterativ increase the number of parameters for the splines
 * (from 1 to uiMaxNumberOfParameters) and will try to not use all of
 * the given range points to find the polynom.
 *
 * @param setMinimumArea the set with the datapoints to combine to
 * 	Fib objects with the help of area and function elements;
 * 	the created area should contain all of these points;
 * 	The given points should be positions in an matrix, positions in
 * 	the matrix but not given, will be considerd not to be in the area
 * 	to create.
 * @param setMaximumArea the set with the datapoints to combine to
 * 	Fib objects with the help of area and function elements;
 * 	the created area can contain these points;
 * 	this set should contain all points from setMinimumArea;
 * 	The given points should be positions in an matrix, positions in
 * 	the matrix but not given, will be considerd not to be in the area
 * 	to create.
 * @param pUnderobject a pointer to the subobject, which the created
 * 	Fib elements should contain and which should be evalued for the
 * 	point positions
 * @param pVariableX a pointer to the variable for the x position
 * @param pVariableY a pointer to the variable for the y position
 * @param uiMaxSplineParameters the number of parameters for the spline;
 * 	Don't choose this number to big, because the evaluation time will
 * 	grow exponentialy with this number. Even splines with 8
 * 	parameters will take some time.
 * @param pOutSetMissingPoints if not NULL, the points not in the
 * 	created area will be inserted/added into this set, when this
 * 	function returns
 * @param maxValue the maximum possible value in all parameters
 * 	the evalued spline/function elements will allways have value
 * 	parameters vecFactors[i] with
 * 	-1 * maxValue <= vecFactors[i] <= maxValue for 0 <= i \< vecFactors.size();
 * 	if 0 (standard value) is given, the maximum possible value will
 * 	be evalued from the given data
 * @param maxError the maximal error for the border polynoms to find;
 * 	the error on the interpolated polynoms for the borders will be
 * 	equal or less than maxError
 * @param maxErrorPerValue the maximal error for the border polynoms to
 * 	find on one border point; the error on the interpolated polynom
 * 	for every border point in vecData will be equal or less than
 * 	maxErrorPerValue
 * @return a Fib object with the created Fib subobjects, which go
 * 	over all point positions in the given set setPoints or NULL if non
 * 	such could be created;
 * 	some positions can be evalued twice;
 * 	the Fib subobjects, wich evalue the most points, are on the
 * 	front of the list-object (have a lower subobject number);
 * 	if NULL is returnd, you have to care that pUnderobject will be
 * 	deleted, else pUnderobject will be included in one
 * 	subobject of the created list-object and the other subobject will
 * 	contain copies of pUnderobject
 * 	Structur of the created Fib object:
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 	or if this previos given structur is not possible
 * 		list(
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 			...
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 		)
 */
template <class tX>
	cFibElement * fib::algorithms::nD2::createSplineItrFastBorderAreasForPoints(
		const set< nD1::cDataPoint<tX, tX> > & setMinimumArea,
		const set< nD1::cDataPoint<tX, tX> > & setMaximumArea,
		cFibElement * pUnderobject,
		cFibVariable * pVariableDimX,
		cFibVariable * pVariableDimY,
		const unsigned int uiMaxSplineParameters,
		set< nD1::cDataPoint<tX, tX> > * pOutSetMissingPoints,
		double maxValue,
		const double maxError,
		const double maxErrorPerValue ){
	
	DEBUG_OUT_L2(<<"createSplineItrFastBorderAreasForPoints(setMinimumArea="<<setMinimumArea.size()<<", setMaximumArea="<<setMaximumArea.size()<<", pUnderobject="<<pUnderobject<<", varX="<<pVariableDimX<<", varY="<<pVariableDimY<<", uiMaxSplineParameters="<<uiMaxSplineParameters<<", maxValue="<<maxValue<<", maxError="<<maxError<<", maxErrorPerValue="<<maxErrorPerValue<<" ) started "<<endl<<flush);
	

#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING


/**
 * This function combines the given set of points to Fib objects,
 * with the help of splies (polynoms with fixed number of parametes
 * uiMaxSplineParameters) .
 * Beware: You have to care that the created subobjects will be deleted
 *
 * uses @see nD1::cPolynom::evalueSplineIterativFast()
 * The method should give the same result as
 * createSplineBorderAreasForPoints() but faster.
 * It will iterativ increase the number of parameters for the splines
 * (from 1 to uiMaxNumberOfParameters) and will try to not use all of
 * the given range points to find the polynom.
 *
 * @param setPoints the set with the datapoints to combine to
 * 	Fib objects with the help of area and function elements;
 * 	The given points should be positions in an matrix, positions in
 * 	the matrix but not given, will be considerd not to be in the area
 * 	to create.
 * @param pUnderobject a pointer to the subobject, which the created
 * 	Fib elements should contain and which should be evalued for the
 * 	point positions
 * @param pVariableX a pointer to the variable for the x position
 * @param pVariableY a pointer to the variable for the y position
 * @param uiMaxSplineParameters the number of parameters for the spline;
 * 	Don't choose this number to big, because the evaluation time will
 * 	grow exponentialy with this number. Even splines with 8
 * 	parameters will take some time.
 * @param uiMinBitsToStoreMantissa the minimal number of bits to store
 * 	the mantissa of the function value parameters, when the parameter
 * 	is in the form: mantissa * 2^exponent ;
 * 	the method will try to reduce the bits, to store a parameter of the
 * 	returned vector, to the uiMinBitsToStoreMantissa value;
 * 	if uiMinBitsToStoreMantissa is 0, no optimization for the mantissa
 * 	bits will be done
 * @param maxValue the maximum possible value in all parameters
 * 	the evalued spline/function elements will allways have value
 * 	parameters vecFactors[i] with
 * 	-1 * maxValue <= vecFactors[i] <= maxValue for 0 <= i \< vecFactors.size();
 * 	if 0 (standard value) is given, the maximum possible value will
 * 	be evalued from the given data
 * @param maxError the maximal error for the border polynoms to find;
 * 	the error on the interpolated polynoms for the borders will be
 * 	equal or less than maxError
 * @param ulMaxMemoryCost a number for the maximum memory cost this
 * 	method is allowed to use; if 0 the maximum memory cost is unbounded
 * @return a Fib object with the created Fib subobjects, which go
 * 	over all point positions in the given set setPoints or NULL if non
 * 	such could be created;
 * 	some positions can be evalued twice;
 * 	the Fib subobjects, wich evalue the most points, are on the
 * 	front of the list-object (have a lower subobject number);
 * 	if NULL is returnd, you have to care that pUnderobject will be
 * 	deleted, else pUnderobject will be included in one
 * 	subobject of the created list-object and the other subobject will
 * 	contain copies of pUnderobject
 * 	Structur of the created Fib object:
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 	or if this previos given structur is not possible
 * 		list(
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 			...
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 		)
 */
template <class tX>
	cFibElement * fib::algorithms::nD2::createSplineItrFastBorderAreasForPoints(
		const set< nD1::cDataPoint<tX, tX> > & setPoints,
		cFibElement * pUnderobject,
		cFibVariable * pVariableDimX,
		cFibVariable * pVariableDimY,
		const unsigned int uiMaxSplineParameters,
		const unsigned int uiMinBitsToStoreMantissa,
		double maxValue,
		const double maxError,
		const unsigned long ulMaxMemoryCost ){
	
	DEBUG_OUT_L2(<<"createSplineItrFastBorderAreasForPoints(#setPoints="<<setPoints.size()<<", pUnderobject="<<pUnderobject<<", varX="<<pVariableDimX<<", varY="<<pVariableDimY<<", uiMaxSplineParameters="<<uiMaxSplineParameters<<", uiMinBitsToStoreMantissa="<<uiMinBitsToStoreMantissa<<", maxValue="<<maxValue<<", maxError="<<maxError<<", ulMaxMemoryCost="<<ulMaxMemoryCost<<" ) started "<<endl<<flush);
	
	return fib::algorithms::nD2::createSplineItrFastBorderAreasForPoints(
		setPoints, setPoints, pUnderobject, pVariableDimX, pVariableDimY,
		uiMaxSplineParameters, (set< nD1::cDataPoint<tX, tX> > *)(NULL),
		uiMinBitsToStoreMantissa, maxValue, maxError, ulMaxMemoryCost );
}


/**
 * This function combines the given set of points to Fib objects,
 * with the help of splies (polynoms with fixed number of parametes
 * uiMaxSplineParameters) .
 * Beware: You have to care that the created subobjects will be deleted
 *
 * uses @see nD1::cPolynom::evalueSplineIterativFast()
 * The method should give the same result as
 * createSplineBorderAreasForPoints() but faster.
 * It will iterativ increase the number of parameters for the splines
 * (from 1 to uiMaxNumberOfParameters) and will try to not use all of
 * the given range points to find the polynom.
 *
 * @param setMinimumArea the set with the datapoints to combine to
 * 	Fib objects with the help of area and function elements;
 * 	the created area should contain all of these points;
 * 	The given points should be positions in an matrix, positions in
 * 	the matrix but not given, will be considerd not to be in the area
 * 	to create.
 * @param setMaximumArea the set with the datapoints to combine to
 * 	Fib objects with the help of area and function elements;
 * 	the created area can contain these points;
 * 	this set should contain all points from setMinimumArea;
 * 	The given points should be positions in an matrix, positions in
 * 	the matrix but not given, will be considerd not to be in the area
 * 	to create.
 * @param pUnderobject a pointer to the subobject, which the created
 * 	Fib elements should contain and which should be evalued for the
 * 	point positions
 * @param pVariableX a pointer to the variable for the x position
 * @param pVariableY a pointer to the variable for the y position
 * @param uiMaxSplineParameters the number of parameters for the spline;
 * 	Don't choose this number to big, because the evaluation time will
 * 	grow exponentialy with this number. Even splines with 8
 * 	parameters will take some time.
 * @param pOutSetMissingPoints if not NULL, the points not in the
 * 	created area will be inserted/added into this set, when this
 * 	function returns
 * @param uiMinBitsToStoreMantissa the minimal number of bits to store
 * 	the mantissa of the function value parameters, when the parameter
 * 	is in the form: mantissa * 2^exponent ;
 * 	the method will try to reduce the bits, to store a parameter of the
 * 	returned vector, to the uiMinBitsToStoreMantissa value;
 * 	if uiMinBitsToStoreMantissa is 0, no optimization for the mantissa
 * 	bits will be done
 * @param maxValue the maximum possible value in all parameters
 * 	the evalued spline/function elements will allways have value
 * 	parameters vecFactors[i] with
 * 	-1 * maxValue <= vecFactors[i] <= maxValue for 0 <= i \< vecFactors.size();
 * 	if 0 (standard value) is given, the maximum possible value will
 * 	be evalued from the given data
 * @param maxError the maximal error for the border polynoms to find;
 * 	the error on the interpolated polynoms for the borders will be
 * 	equal or less than maxError
 * @param ulMaxMemoryCost a number for the maximum memory cost this
 * 	method is allowed to use; if 0 the maximum memory cost is unbounded
 * @return a Fib object with the created Fib subobjects, which go
 * 	over all point positions in the given set setPoints or NULL if non
 * 	such could be created;
 * 	some positions can be evalued twice;
 * 	the Fib subobjects, wich evalue the most points, are on the
 * 	front of the list-object (have a lower subobject number);
 * 	if NULL is returnd, you have to care that pUnderobject will be
 * 	deleted, else pUnderobject will be included in one
 * 	subobject of the created list-object and the other subobject will
 * 	contain copies of pUnderobject
 * 	Structur of the created Fib object:
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 	or if this previos given structur is not possible
 * 		list(
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 			...
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 		)
 */
template <class tX>
	cFibElement * fib::algorithms::nD2::createSplineItrFastBorderAreasForPoints(
		const set< nD1::cDataPoint<tX, tX> > & setMinimumArea,
		const set< nD1::cDataPoint<tX, tX> > & setMaximumArea,
		cFibElement * pUnderobject,
		cFibVariable * pVariableDimX,
		cFibVariable * pVariableDimY,
		const unsigned int uiMaxSplineParameters,
		set< nD1::cDataPoint<tX, tX> > * pOutSetMissingPoints,
		const unsigned int uiMinBitsToStoreMantissa,
		double maxValue,
		const double maxError,
		const unsigned long ulMaxMemoryCost ){
	
	DEBUG_OUT_L2(<<"createSplineItrFastBorderAreasForPoints(setMinimumArea="<<setMinimumArea.size()<<", setMaximumArea="<<setMaximumArea.size()<<", pUnderobject="<<pUnderobject<<", varX="<<pVariableDimX<<", varY="<<pVariableDimY<<", uiMaxSplineParameters="<<uiMaxSplineParameters<<", uiMinBitsToStoreMantissa="<<uiMinBitsToStoreMantissa<<", maxValue="<<maxValue<<", maxError="<<maxError<<", ulMaxMemoryCost="<<ulMaxMemoryCost<<" ) started "<<endl<<flush);
	
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING

	if ( setMinimumArea.empty() ){
		//no data points, for which to create the areas
		return NULL;
	}
	if ( setMaximumArea.empty() ){
		//no data points, for which to create the areas
		return NULL;
	}
	if ( pUnderobject == NULL ){
		//no subobject, wich to use in created Fib objects
		return NULL;
	}
	if ( ( pVariableDimX == NULL ) || ( pVariableDimY == NULL ) ){
		//missing variable, wich to use in created Fib objects
		return NULL;
	}
	if ( uiMaxSplineParameters == 0 ){
		//can't create spline with 0 parameters, which match datapoints
		return NULL;
	}
	if ( maxError < 0.0 ){
		//can't create spline with negativ maximum error
		return NULL;
	}
	if ( maxValue < 0.0 ){
		//can't create spline with this maximum value
		return NULL;
	}//else
	
	typedef fib::algorithms::nD1::cDataPoint<tX, tX> typeDataPoint;
	typedef set< typeDataPoint > typeSetDataPoints;
	typedef typename typeSetDataPoints::const_iterator typeConstItrSetDataPoints;
	typedef typename typeSetDataPoints::const_reverse_iterator typeConstRevItrSetDataPoints;
	
	if ( maxValue == 0.0 ){
		//evalue the maximum value
		double dMaxDataValue = 0.0;
		for ( typeConstItrSetDataPoints itrPoint = setMaximumArea.begin();
				itrPoint != setMaximumArea.end(); itrPoint++ ){
			
			const tX absY = ( 0 <= itrPoint->y )?( itrPoint->y ):( ((tX)(-1)) * itrPoint->y );
			if ( dMaxDataValue < absY ){
				dMaxDataValue = absY;
			}
			const tX absX = ( 0 <= itrPoint->x )?( itrPoint->x ):( ((tX)(-1)) * itrPoint->x );
			if ( dMaxDataValue < absX ){
				dMaxDataValue = absX;
			}
		}
		if ( dMaxDataValue ){
			dMaxDataValue = 1.0;
		}
		maxValue = dMaxDataValue * 1024.0;
	}//end if maxValue == 0

	
	/*create areas for the minimum and maximum number of points in the
	directions (the maximum area is the area of points, which can be contained
	in an created area object, the minimum is the area of points, which are
	not contained in an other created areas)*/
	typeSetDataPoints setMinimumXArea = setMinimumArea;
	typeSetDataPoints setMaximumXArea = setMaximumArea;
	
	/*the Y Areas /Sets are the same as the X Areas/Sets, but of a matrix
	rotated with 90 degree*/
	typeSetDataPoints setMinimumYArea;
	for ( typeConstItrSetDataPoints itrPoint = setMinimumArea.begin();
			itrPoint != setMinimumArea.end(); itrPoint++ ){
		
		setMinimumYArea.insert( typeDataPoint( itrPoint->y, itrPoint->x ) );
	}
	typeSetDataPoints setMaximumYArea;
	if ( ( & setMinimumArea ) == ( & setMaximumArea ) ){
		//minimum and maximum areas are equal
		setMaximumYArea = setMinimumYArea;
	}else{
		for ( typeConstItrSetDataPoints itrPoint = setMaximumArea.begin();
				itrPoint != setMaximumArea.end(); itrPoint++ ){
			
			setMaximumYArea.insert( typeDataPoint( itrPoint->y, itrPoint->x ) );
		}
	}

	/*the created elemental areas;
		- first pair element: number of points, the area covers
		- second pair element: the the area as an Fib object*/
	list< pair< unsigned long, cFibElement * > > liAreaList;
	
	DEBUG_OUT_L2(<<"beginning searching for areas"<<endl<<flush);
	
	//while not all points are included in the area
	while ( ( ! setMinimumXArea.empty() ) ||  ( ! setMinimumYArea.empty() ) ){
	/*create areas:
		- begin at the outer side of the minimum areas of points which
			should be found; prefer big areas
		- remove points from the minimum areas, which are included in created areas
		- borders are points, which should be in the area, but which
			neibours shouldn't be in the area*/
		
		//scan in x direction
		/* The list with the possible areas.
		* The pair elements are:
		* 	first element: the number of points in the possible area
		* 	second element: list with the possible areas containing each a
		* 	list with the pairs for the lines: first element is the upper
		* 	border of the line and the second the lower border
		*/
		typedef list< pair< unsigned long, list< pair< typeDataPoint,
			typeDataPoint > > > > typePossibleAreas;
		typePossibleAreas possibleXAreas;
		
		typeConstItrSetDataPoints itrPoint = setMinimumXArea.begin();
		typeDataPoint dataPoint = *itrPoint;
		typeDataPoint dataPointLineBegin = *itrPoint;
		
		while ( itrPoint != setMinimumXArea.end() ){
			
			if ( dataPoint != *itrPoint ){
				/*this point isn't the x neibour of the last point
				-> new line begin; *itrXPoint = new line begin; dataPoint.y-- = old line end*/
				dataPoint.y--;//old line end
				/*insert old line to every possible area or create a new area, if
				no possible area exists*/
				const pair< typeDataPoint, typeDataPoint >
					paNewLine( dataPointLineBegin, dataPoint);
				integrateLineInAreas( possibleXAreas, paNewLine );
	
				dataPointLineBegin = *itrPoint;//remember line begin
			}
			dataPoint = *itrPoint;
			itrPoint++;
			dataPoint.y++;//next neibour in x direction for the last point
		}
		{//add last line
			dataPoint.y--;
			const pair< typeDataPoint, typeDataPoint >
				paNewLine( dataPointLineBegin, dataPoint);
			integrateLineInAreas( possibleXAreas, paNewLine );
		}
		//scan in y direction
		typePossibleAreas possibleYAreas;
		
		itrPoint = setMinimumYArea.begin();
		dataPoint = *itrPoint;
		dataPointLineBegin = *itrPoint;
		
		while ( itrPoint != setMinimumYArea.end() ){
			
			if ( dataPoint != *itrPoint ){
				/*this point isn't the x neibour of the last point
				-> new line begin; *itrXPoint = new line begin; dataPoint.y-- = old line end*/
				dataPoint.y--;//old line end
				/*insert old line to every possible area or create a new area, if
				no possible area exists*/
				const pair< typeDataPoint, typeDataPoint >
					paNewLine( dataPointLineBegin, dataPoint);
				integrateLineInAreas( possibleYAreas, paNewLine );
	
				dataPointLineBegin = *itrPoint;//remember line begin
			}
			dataPoint = *itrPoint;
			itrPoint++;
			dataPoint.y++;//next neibour in x direction for the last point
		}
		{//add last line
			dataPoint.y--;
			const pair< typeDataPoint, typeDataPoint >
				paNewLine( dataPointLineBegin, dataPoint);
			integrateLineInAreas( possibleYAreas, paNewLine );
		}
		//choose the area for which to create the Fib structur
		/*the type filds are:
			- number of points in the area
				- iterator to the area
				- if the area is a x area (x = true; y = false)*/
		typedef set< pair< unsigned long, pair< typename typePossibleAreas::const_iterator, bool > >,
				structLowerFirstElement< pair< typename typePossibleAreas::const_iterator, bool > > >
				typeSetOrderdAreas;
		typeSetOrderdAreas setAreas;
		
		for ( typename typePossibleAreas::const_iterator itrActualArea = possibleXAreas.begin();
				itrActualArea != possibleXAreas.end(); itrActualArea++ ){
			
			setAreas.insert( make_pair( itrActualArea->first, make_pair( itrActualArea, true ) ) );
		}
		for ( typename typePossibleAreas::const_iterator itrActualArea = possibleYAreas.begin();
				itrActualArea != possibleYAreas.end(); itrActualArea++ ){
			
			setAreas.insert( make_pair( itrActualArea->first, make_pair( itrActualArea, false ) ) );
		}
		
		//try biggest area and than the areas befor, if biggest area couldn't be used
		typename typeSetOrderdAreas::const_reverse_iterator
				itrActualToConvertArea = setAreas.rbegin();
		unsigned long uiPointsRemoved = 0;
		for ( ; itrActualToConvertArea != setAreas.rend(); itrActualToConvertArea++ ){
			
			if ( itrActualToConvertArea->first <= 4 ){
				DEBUG_OUT_L2(<<"just maximal "<<itrActualToConvertArea->first<<" points in remaining areas"<<endl<<flush);
				//stop evaluation, because no area with more than 4 points exists
				itrActualToConvertArea = setAreas.rend();
				break;
			}
			
			const typename typePossibleAreas::const_iterator itrToConvertArea =
				itrActualToConvertArea->second.first;
			//x = true; y = false
			const bool bChoosenDirection = itrActualToConvertArea->second.second;
			
			//evalue ranges for the choosen area in directions
			typedef list< pair< typeDataPoint, typeDataPoint > > typeDataPointList;
			typedef typename typeDataPointList::const_iterator typeItrDataPointList;
#ifdef DEBUG_N_D2
			cout<<"founded best datapoints (direction "<<(bChoosenDirection?"x":"y")<<" ): ";
			for ( typeItrDataPointList itrDataPoint = itrToConvertArea->second.begin();
					itrDataPoint != itrToConvertArea->second.end(); itrDataPoint++ ){
				cout<<"("<< itrDataPoint->first.x <<";[ "<< itrDataPoint->first.y
					<<" ... "<< itrDataPoint->second.y <<" ] ); ";
			}
			cout<<endl;
#endif
			DEBUG_OUT_L2(<<"creating range datapoints for areas"<<endl<<flush);
			vector< fib::algorithms::nD1::cDataPointRange< tX, double > > vecRangesUpper;
			vector< fib::algorithms::nD1::cDataPointRange< tX, double > > vecRangesLower;
			
			const bool bBordersEqual = findBorderRanges( *itrToConvertArea,
				bChoosenDirection, setMaximumXArea, setMaximumYArea,
				vecRangesLower, vecRangesUpper );
	
			if ( vecRangesLower.empty() || vecRangesUpper.empty() ){
				DEBUG_OUT_EL2(<<"one range empty:"<<endl<<flush);
#ifdef DEBUG_N_D2
				cout<<"vecRangesLower: ";
				for ( unsigned int uiActRange = 0; uiActRange < vecRangesLower.size(); uiActRange++ ){
					cout<<"("<<vecRangesLower[uiActRange].x<<";["<<
						vecRangesLower[uiActRange].minY<<" ... "<<vecRangesLower[uiActRange].maxY<<"] ); ";
				}
				cout<<"vecRangesUpper: ";
				for ( unsigned int uiActRange = 0; uiActRange < vecRangesUpper.size(); uiActRange++ ){
					cout<<"("<<vecRangesUpper[uiActRange].x<<";["<<
						vecRangesUpper[uiActRange].minY<<" ... "<<vecRangesUpper[uiActRange].maxY<<"] ); ";
				}
#endif
				continue;//check next area
			}
			//the x offset so that the spline will begin at 0
			const tX xOffset = vecRangesUpper[ 0 ].x;
			
			//dismiss created areas which have (much) more points as in the maximal area
			unsigned long ulAceptablePointsForArea = 8;
			for ( unsigned int uiActRange = 0; uiActRange < vecRangesLower.size(); uiActRange++ ){
				
				ulAceptablePointsForArea += vecRangesUpper[uiActRange].maxY - vecRangesLower[uiActRange].minY + 1;
				
				//move the x component about the offset (subtract offset)
				vecRangesUpper[ uiActRange ].x -= xOffset;
				vecRangesLower[ uiActRange ].x -= xOffset;
			}
			
			//evalue the splines for the borders
			DEBUG_OUT_L2(<<"The borders are "<<(bBordersEqual?"equal":"not equal")<<endl);
			DEBUG_OUT_L2(<<"evaluing the spline for the lower border (evalueSplineIterativFast() ):"<<endl<<flush);
			cPolynom< tX, double > polynomLower;
#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
			const unsigned long uiPointsIncludedLower = polynomLower.evalueSplineIterativFast(
				vecRangesLower, uiMaxSplineParameters,
				maxValue, maxError, maxErrorPerValue );
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
			const unsigned long uiPointsIncludedLower = polynomLower.evalueSplineIterativFast(
				vecRangesLower, uiMaxSplineParameters,
				uiMinBitsToStoreMantissa, maxValue, maxError, ulMaxMemoryCost );
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
			
#ifdef DEBUG_N_D2
			cout<<"vecRangesLower: ";
			for ( unsigned int uiActRange = 0; uiActRange < vecRangesLower.size(); uiActRange++ ){
				cout<<"("<<vecRangesLower[uiActRange].x<<";["<<
					vecRangesLower[uiActRange].minY<<" ... "<<vecRangesLower[uiActRange].maxY<<"] ); ";
			}
			cout<<endl<<"spline for lower border (for the "<<uiPointsIncludedLower<<" first points): ";polynomLower.print( cout );
#endif
			if ( uiPointsIncludedLower < 1 ){
				//no points included -> no lower border
				continue;//check next area
			}
			cPolynom< tX, double > polynomUpper;
			unsigned long uiLastPointsIncluded = uiPointsIncludedLower - 1;
			if ( ! bBordersEqual ){
				
				if ( uiPointsIncludedLower < vecRangesUpper.size()  ){
					//don't need to include all points in the upper range
					DEBUG_OUT_L2(<<"resizing upper boundery from "<<vecRangesUpper.size()<<" to "<<uiPointsIncludedLower<<", because the remaining points arn't needed"<<endl<<flush);
					vecRangesUpper.resize( uiPointsIncludedLower );
				}
				DEBUG_OUT_L2(<<"evaluing the spline for the upper border (evalueSplineIterativFast() ):"<<endl<<flush);

#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
			const unsigned long uiPointsIncludedUpper = polynomUpper.evalueSplineIterativFast(
				vecRangesLower, uiMaxSplineParameters,
				maxValue, maxError, maxErrorPerValue );
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
				const unsigned long uiPointsIncludedUpper = polynomUpper.evalueSplineIterativFast(
					vecRangesUpper, uiMaxSplineParameters,
					uiMinBitsToStoreMantissa, maxValue, maxError, ulMaxMemoryCost );
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
				if ( uiPointsIncludedUpper < 1 ){
					//no points included -> no upper border
					continue;//check next area
				}
				
				uiLastPointsIncluded = min(
					uiPointsIncludedLower, uiPointsIncludedUpper ) - 1;
#ifdef DEBUG_N_D2
				cout<<"vecRangesUpper: ";
				for ( unsigned int uiActRange = 0; uiActRange < vecRangesUpper.size(); uiActRange++ ){
					cout<<"("<<vecRangesUpper[uiActRange].x<<";["<<
						vecRangesUpper[uiActRange].minY<<" ... "<<vecRangesUpper[uiActRange].maxY<<"] ); ";
				}
				cout<<endl<<"spline for upper border (for the "<<uiPointsIncludedUpper<<" first points): ";polynomUpper.print( cout );
#endif
			}//else borders are equal -> don't need to evalue spline for upper border
#ifdef DEBUG_N_D2
			cout<<endl<<"evalued ranges: "<<flush;
			for ( unsigned int uiActRange = 0; uiActRange < vecRangesLower.size(); uiActRange++ ){
				cout<<"("<<vecRangesLower[uiActRange].x<<";["<<
					polynomLower.evalue( vecRangesLower[uiActRange].x )<<" ... "<<
					polynomUpper.evalue( vecRangesLower[uiActRange].x )<<"] ); ";
			}
			cout<<endl<<"evalued ranges compared: "<<flush;
			for ( unsigned int uiActRange = 0; (uiActRange < vecRangesLower.size()) &&
					(uiActRange < vecRangesUpper.size()) ; uiActRange++ ){
				cout<<"("<<vecRangesLower[uiActRange].x<<";["<<
					vecRangesLower[uiActRange].minY<<"<"<<flush<<
					polynomLower.evalue( vecRangesLower[uiActRange].x )<<"<"<<flush<<
					vecRangesLower[uiActRange].maxY<<" ... "<<
					vecRangesUpper[uiActRange].minY<<"<"<<flush<<
					polynomUpper.evalue( vecRangesLower[uiActRange].x )<<"<"<<flush<<
					vecRangesUpper[uiActRange].maxY<<"] ); "<<flush;
			}
			cout<<endl;
			if ( vecRangesLower.size() !=  vecRangesUpper.size() ){
				cout<<"Ther are ranges in the lower border: "<<vecRangesLower.size()<<
					" but in the upper border ther are : "<<vecRangesUpper.size()<<endl<<flush;
			}
#endif
			//include points wich are in max bounderies
			DEBUG_OUT_L2(<<"last point included in bounderies: "<<uiLastPointsIncluded<<endl<<flush);
			
			DEBUG_OUT_L2(<<"creating area object"<<endl<<flush);
			cArea * pAreaNew = NULL;
			
			if ( ( ! bBordersEqual ) && ( polynomUpper != polynomLower ) ){
				pAreaNew = createAreaFibObject( bChoosenDirection,
					roundToLongFib( vecRangesLower.front().x ),
					roundToLongFib( vecRangesLower[ uiLastPointsIncluded ].x ),
					polynomLower, polynomUpper, xOffset );
			}else{
				pAreaNew = createLineFibObject( bChoosenDirection,
					roundToLongFib( vecRangesLower.front().x ),
					roundToLongFib( vecRangesLower[ uiLastPointsIncluded ].x ),
					polynomLower, xOffset );
			}
#ifdef DEBUG_N_D2_2
			DEBUG_OUT_L2(<<"created area object: "<<endl<<flush);
//			pAreaNew->getDefinedVariable()->setValue( 1.0 );
			//enumerate variables so thy can be identified
			list<cFibVariable*> liDefVariables =
				pAreaNew->getDefinedVariables( ED_BELOW_EQUAL );
			unsigned int uiNumber = 1;
			for ( list<cFibVariable*>::iterator itrVariable = liDefVariables.begin();
					itrVariable != liDefVariables.end(); itrVariable++, uiNumber++ ){
				
				(*itrVariable)->setValue( uiNumber );
			}
			pAreaNew->storeXml( cout );
#endif
			DEBUG_OUT_L2(<<"evaluing points in area object"<<endl<<flush);
			//count points in the area
			cEvaluePositionListLimit evaluedPositionsData(
				ulAceptablePointsForArea + 1, NULL, true, 0, ulAceptablePointsForArea * 16 );
			const bool bObjectEvalued = pAreaNew->evalueObjectSimple( evaluedPositionsData );
			
			const unsigned long ulNumberOfPoints = evaluedPositionsData.liEvaluedPositionData.size();
			DEBUG_OUT_L2(<<"evalued ulNumberOfPoints= "<<ulNumberOfPoints<<"  ulAceptablePointsForArea="<<ulAceptablePointsForArea<<" bObjectEvalued="<<(bObjectEvalued?"true":"false")<<endl<<flush);
			
			bool bAreaAdded = false;
			if ( bObjectEvalued && ( 4 < ulNumberOfPoints ) &&
					( ulNumberOfPoints <= ulAceptablePointsForArea ) ){
				
				//check how many points are in the area to find
				unsigned long ulPointsInMaxArea = 0;
				unsigned long ulPointsInMinArea = 0;
				DEBUG_OUT_L2(<<"Evalud points: "<<flush);
				for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
						itrPoint = evaluedPositionsData.liEvaluedPositionData.begin();
						itrPoint != evaluedPositionsData.liEvaluedPositionData.end();
						itrPoint++ ){
					
					const typeDataPoint dataXPointTmp(
						roundToLongFib( itrPoint->first.getValue( 1 ) ),
						roundToLongFib( itrPoint->first.getValue( 2 ) ) );
					const typeConstItrSetDataPoints itrFoundPointMax =
						setMaximumXArea.find( dataXPointTmp );
					if ( itrFoundPointMax != setMaximumXArea.end() ){
						ulPointsInMaxArea++;
					}
					const typeConstItrSetDataPoints itrFoundPointMin =
						setMinimumXArea.find( dataXPointTmp );
					if ( itrFoundPointMin != setMinimumXArea.end() ){
						ulPointsInMinArea++;
					}
					DEBUG_OUT_L2(<<"( "<<dataXPointTmp.x<<","<<dataXPointTmp.y<<") in "<<((itrFoundPointMax != setMaximumXArea.end())?"max ":"")<<((itrFoundPointMin != setMinimumXArea.end())?"min; ":"; ")<<flush);
				}
				DEBUG_OUT_L2(<<endl<<"points in maximum area: "<<ulPointsInMaxArea<<" points outside the maximum area: "<<(ulNumberOfPoints - ulPointsInMaxArea)<<endl<<flush);
				DEBUG_OUT_L2(<<"points in minimum area: "<<ulPointsInMinArea<<" points outside the minimum area: "<<(ulNumberOfPoints - ulPointsInMinArea)<<endl<<flush);
				
				if ( ( (ulNumberOfPoints - ulNumberOfPoints / 16 - 2) <= ulPointsInMaxArea ) &&
						( (ulNumberOfPoints / 8 + 2) <= ulPointsInMinArea ) ){
					/*no more than 1/16 of the evalued points outside the given area
					-> add created area  and remove the points in the created area
					from the minimum area*/
					
					//replace point of the area with the given subobject
					DEBUG_OUT_L2(<<"Replace point of the area with the given subobject"<<endl<<flush);
					cFibElement * pSubobjectToInsert = NULL;
					if ( liAreaList.empty() ){
						//first underarea created -> use the original object pUnderobject
						pSubobjectToInsert = pUnderobject;
					}else{//not the first underarea created -> use the clone of the original object pUnderobject
						pSubobjectToInsert = pUnderobject->copy();
					}
					//replace dimension variables with point variables
					cPoint * pPoint = ((cPoint*)( pAreaNew->getNextFibElement( 'p' ) ));
					
					pSubobjectToInsert->replaceVariable( pVariableDimX, pPoint->getPosition()->getVariable( 1 ) );
					pSubobjectToInsert->replaceVariable( pVariableDimY, pPoint->getPosition()->getVariable( 2 ) );
					
					if ( pSubobjectToInsert == pUnderobject ){
						//variable in the subobject have changed
						pVariableDimX = pPoint->getPosition()->getVariable( 1 );
						pVariableDimY = pPoint->getPosition()->getVariable( 2 );
					}
					//replace the point with the Fib object to insert
					pAreaNew->overwriteObjectWithObject(
						pSubobjectToInsert, 'u', pPoint->getNumberOfElement(), true, true );
					
					
					DEBUG_OUT_L2(<<"Adding creating area to the area list"<<endl<<flush);
					liAreaList.push_back( pair< unsigned long, cFibElement * >( ulNumberOfPoints, pAreaNew ) );
					bAreaAdded = true;
					
					//remove the points in the created area from the minimum area
					for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
							itrPoint = evaluedPositionsData.liEvaluedPositionData.begin();
							itrPoint != evaluedPositionsData.liEvaluedPositionData.end();
							itrPoint++ ){
						
						const typeDataPoint dataXPointTmp(
							roundToLongFib( itrPoint->first.getValue( 1 ) ),
							roundToLongFib( itrPoint->first.getValue( 2 ) ) );
						uiPointsRemoved += setMinimumXArea.erase( dataXPointTmp );
						
						const typeDataPoint dataYPointTmp(
							roundToLongFib( itrPoint->first.getValue( 2 ) ),
							roundToLongFib( itrPoint->first.getValue( 1 ) ) );
						uiPointsRemoved += setMinimumYArea.erase( dataYPointTmp );
					}
				}
			}
			if ( ! bAreaAdded ){//delete the created subobject
				DEBUG_OUT_EL2(<<"Warning: couldn't add the area object"<<endl<<flush);
				
				pAreaNew->deleteObject();
			}
			DEBUG_OUT_L2(<<"uiPointsRemoved= "<<uiPointsRemoved<<"  ulNumberOfPoints= "<<ulNumberOfPoints<<"  ulAceptablePointsForArea="<<ulAceptablePointsForArea<<endl<<flush);
			if ( uiPointsRemoved != 0 ){
				DEBUG_OUT_L2(<<"Find the remaining areas to convert."<<endl<<flush);
				break;
			}else{
				DEBUG_OUT_EL2(<<"Warning: no points removed -> try next bigges area"<<endl<<flush);
				//Error: no points removed -> abourt evaluation so it dosn't loop infinity
			}
			//TODO?? remove points betwean borders from the maximum area in the direction
		}//end for itrActualToConvertArea
			
			
		if ( (uiPointsRemoved == 0) && ( ! setAreas.empty() ) ){
			/*if no wher removed
			-> smooth border and decrease area*/
			DEBUG_OUT_L2(<<"Area with to much points generated (and no points removed) "<<endl<<flush);
			
			const typeSetDataPoints setRemovedPoints = smoothBorders(
				*(setAreas.begin()->second.first),
				setAreas.begin()->second.second,
				setMaximumXArea, setMaximumYArea,
				setMinimumXArea, setMinimumYArea );
			uiPointsRemoved = setRemovedPoints.size();
			
			if ( pOutSetMissingPoints ){
				pOutSetMissingPoints->insert( setRemovedPoints.begin(),
					setRemovedPoints.end() );
			}

			DEBUG_OUT_L2(<<"The number of removed points from the minimal areas is: "<<uiPointsRemoved<<endl<<flush);
			if ( uiPointsRemoved != 0 ){
				DEBUG_OUT_L2(<<"Find the remaining areas to convert."<<endl<<flush);
				break;
			}else{
				DEBUG_OUT_EL2(<<"Warning: no points removed -> try next bigges area"<<endl<<flush);
				//Error: no points removed -> abourt evaluation so it dosn't loop infinity
			}
		}
		
		if ( uiPointsRemoved == 0 ){
			DEBUG_OUT_EL2(<<"Warning: for no area points removed -> stopping evaluation, so no infinit loop occurs"<<endl<<flush);
			break;
		}
	}
	//TODO if needed -> add Fib objects for missing points
	
	if ( pOutSetMissingPoints ){
		pOutSetMissingPoints->insert( setMinimumXArea.begin(),
			setMinimumXArea.end() );
	}
	
	if ( liAreaList.empty() ){
		DEBUG_OUT_L2(<<"Warning: no subarea evalued"<<endl<<flush);
		//no area elements to return
		return NULL;
	}//else
	if ( liAreaList.size() == 1 ){
		DEBUG_OUT_L2(<<"one subarea evalued"<<endl<<flush);
		return liAreaList.front().second;
	}
	DEBUG_OUT_L2(<<"number of subarea evalued: "<<liAreaList.size()<<endl<<flush);
	//if more than one object was created, combine the created subobjects to an listelement
	liAreaList.sort( fib::algorithms::nD2::lowerFirstNumber );
	
	list<cFibElement*> liUnderobjects;
	while ( ! liAreaList.empty() ){
		liUnderobjects.push_back( liAreaList.back().second );
		liAreaList.pop_back();
	}
	DEBUG_OUT_L2(<<"Creating list-object "<<endl<<flush);
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cList * pList = new cList( liUnderobjects );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cList * pList = new cList( NULL, NULL );
	pList->addUnderobjects( liUnderobjects );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
	DEBUG_OUT_L2(<<"createSplineItrFastBorderAreasForPoints( setMinimumArea="<<setMinimumArea.size()<<", setMaximumArea="<<setMaximumArea.size()<<", pUnderobject="<<pUnderobject<<", varX="<<pVariableDimX<<", varY="<<pVariableDimY<<", uiMaxSplineParameters="<<uiMaxSplineParameters<<", maxValue="<<maxValue<<", maxError="<<maxError<<", maxErrorPerValue="<<maxErrorPerValue<<" ) done "<<endl<<flush);
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
	DEBUG_OUT_L2(<<"createSplineItrFastBorderAreasForPoints(setMinimumArea="<<setMinimumArea.size()<<", setMaximumArea="<<setMaximumArea.size()<<", pUnderobject="<<pUnderobject<<", varX="<<pVariableDimX<<", varY="<<pVariableDimY<<", uiMaxSplineParameters="<<uiMaxSplineParameters<<", uiMinBitsToStoreMantissa="<<uiMinBitsToStoreMantissa<<", maxValue="<<maxValue<<", maxError="<<maxError<<", ulMaxMemoryCost="<<ulMaxMemoryCost<<" ) done "<<endl<<flush);
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
	return pList;
}


#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING

/**
 * This function combines the given set of points to Fib objects,
 * with the help of splies (polynoms with fixed number of parametes
 * uiMaxSplineParameters) .
 * For this the method @see nD1::cSpline::evalueSpline() will be used.
 * Beware: You have to care that the created subobjects will be deleted
 *
 * uses @see nD1::cSpline::evalueSpline()
 * The method should give the same result as
 * createSplineItrFastBorderAreasForPoints() but faster and with less
 * Fib elements.
 * It will iterativ increase the number of parameters for the splines
 * (from 1 to uiMaxNumberOfParameters).
 *
 * @param setPoints the set with the datapoints to combine to
 * 	Fib objects with the help of area and function elements;
 * 	The given points should be positions in an matrix, positions in
 * 	the matrix but not given, will be considerd not to be in the area
 * 	to create.
 * @param pUnderobject a pointer to the subobject, which the created
 * 	Fib elements should contain and which should be evalued for the
 * 	point positions
 * @param pVariableX a pointer to the variable for the x position
 * @param pVariableY a pointer to the variable for the y position
 * @param uiMaxSplineParameters the number of parameters for the spline;
 * 	Don't choose this number to big, because the evaluation time will
 * 	grow exponentialy with this number. Even splines with 8
 * 	parameters will take some time.
 * @param maxValue the maximum possible value in all parameters
 * 	the evalued spline/function elements will allways have value
 * 	parameters vecFactors[i] with
 * 	-1 * maxValue <= vecFactors[i] <= maxValue for 0 <= i \< vecFactors.size();
 * 	if 0 (standard value) is given, the maximum possible value will
 * 	be evalued from the given data
 * @param maxError the maximal error for the border polynoms to find;
 * 	the error on the interpolated polynoms for the borders will be
 * 	equal or less than maxError
 * @param maxErrorPerValue the maximal error for the border polynoms to
 * 	find on one border point; the error on the interpolated polynom
 * 	for every border point in vecData will be equal or less than
 * 	maxErrorPerValue
 * @return a Fib object with the created Fib subobjects, wher the
 * 	given variables for the given pUnderobject will go over all
 * 	point positions in the given set setPoints or NULL if non
 * 	such could be created;
 * 	some positions can be evalued twice;
 * 	the Fib subobjects, wich evalue the most points, are on the
 * 	front of the list-object (have a lower subobject number);
 * 	if NULL is returnd, you have to care that pUnderobject will be
 * 	deleted, else pUnderobject will be included in one
 * 	subobject of the created list-object and the other subobject will
 * 	contain copies of pUnderobject
 * 	Structur of the created Fib object:
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 	or if this previos given structur is not possible
 * 		list(
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 			...
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 		)
 * 	(some fun or areas can be missing, if they are not needed, eg. for lines)
 */
template <class tX>
	cFibElement * fib::algorithms::nD2::createNSplineBorderAreasForPoints(
		const set< nD1::cDataPoint<tX, tX> > & setPoints,
		cFibElement * pUnderobject,
		cFibVariable * pVariableDimX,
		cFibVariable * pVariableDimY,
		const unsigned int uiMaxSplineParameters,
		double maxValue,
		const double maxError,
		const double maxErrorPerValue ){
	
	DEBUG_OUT_L2(<<"createNSplineBorderAreasForPoints(#setPoints="<<setPoints.size()<<", pUnderobject="<<pUnderobject<<", varX="<<pVariableDimX<<", varY="<<pVariableDimY<<", uiMaxSplineParameters="<<uiMaxSplineParameters<<", maxValue="<<maxValue<<", maxError="<<maxError<<", maxErrorPerValue="<<maxErrorPerValue<<" ) started "<<endl<<flush);
	
	return fib::algorithms::nD2::createNSplineBorderAreasForPoints(
		setPoints, setPoints, pUnderobject, pVariableDimX, pVariableDimY,
		uiMaxSplineParameters, (set< nD1::cDataPoint<tX, tX> > *)(NULL),
		maxValue, maxError, maxErrorPerValue );
}



/**
 * This function combines the given set of points to Fib objects,
 * with the help of splies (polynoms with fixed number of parametes
 * uiMaxSplineParameters) .
 * For this the method @see nD1::cSpline::evalueSpline() will be used.
 * Beware: You have to care that the created subobjects will be deleted
 *
 * uses @see nD1::cSpline::evalueSpline()
 * The method should give the same result as
 * createSplineItrFastBorderAreasForPoints() but faster and with less
 * Fib elements.
 * It will iterativ increase the number of parameters for the splines
 * (from 1 to uiMaxNumberOfParameters).
	 *
 * @param setMinimumArea the set with the datapoints to combine to
 * 	Fib objects with the help of area and function elements;
 * 	the created area should contain all of these points;
 * 	The given points should be positions in an matrix, positions in
 * 	the matrix but not given, will be considerd not to be in the area
 * 	to create.
 * @param setMaximumArea the set with the datapoints to combine to
 * 	Fib objects with the help of area and function elements;
 * 	the created area can contain these points;
 * 	this set should contain all points from setMinimumArea;
 * 	The given points should be positions in an matrix, positions in
 * 	the matrix but not given, will be considerd not to be in the area
 * 	to create.
 * @param pUnderobject a pointer to the subobject, which the created
 * 	Fib elements should contain and which should be evalued for the
 * 	point positions
 * @param pVariableX a pointer to the variable for the x position
 * @param pVariableY a pointer to the variable for the y position
 * @param uiMaxSplineParameters the number of parameters for the spline;
 * 	Don't choose this number to big, because the evaluation time will
 * 	grow exponentialy with this number. Even splines with 8
 * 	parameters will take some time.
 * @param pOutSetMissingPoints if not NULL, the points not in the
 * 	created area will be inserted/added into this set, when this
 * 	function returns
 * @param maxValue the maximum possible value in all parameters
 * 	the evalued spline/function elements will allways have value
 * 	parameters vecFactors[i] with
 * 	-1 * maxValue <= vecFactors[i] <= maxValue for 0 <= i \< vecFactors.size();
 * 	if 0 (standard value) is given, the maximum possible value will
 * 	be evalued from the given data
 * @param maxError the maximal error for the border polynoms to find;
 * 	the error on the interpolated polynoms for the borders will be
 * 	equal or less than maxError
 * @param maxErrorPerValue the maximal error for the border polynoms to
 * 	find on one border point; the error on the interpolated polynom
 * 	for every border point in vecData will be equal or less than
 * 	maxErrorPerValue
 * @return a Fib object with the created Fib subobjects, wher the
 * 	given variables for the given pUnderobject will go over all
 * 	point positions in the given set setPoints or NULL if non
 * 	such could be created;
 * 	some positions can be evalued twice;
 * 	the Fib subobjects, wich evalue the most points, are on the
 * 	front of the list-object (have a lower subobject number);
 * 	if NULL is returnd, you have to care that pUnderobject will be
 * 	deleted, else pUnderobject will be included in one
 * 	subobject of the created list-object and the other subobject will
 * 	contain copies of pUnderobject
 * 	Structur of the created Fib object:
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 	or if this previos given structur is not possible
 * 		list(
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 			...
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 		)
 * 	(some fun or areas can be missing, if they are not needed, eg. for lines)
 */
template <class tX>
	cFibElement * fib::algorithms::nD2::createNSplineBorderAreasForPoints(
		const set< nD1::cDataPoint<tX, tX> > & setMinimumArea,
		const set< nD1::cDataPoint<tX, tX> > & setMaximumArea,
		cFibElement * pUnderobject,
		cFibVariable * pVariableDimX,
		cFibVariable * pVariableDimY,
		const unsigned int uiMaxSplineParameters,
		set< nD1::cDataPoint<tX, tX> > * pOutSetMissingPoints,
		double maxValue,
		const double maxError,
		const double maxErrorPerValue ){
	
	DEBUG_OUT_L2(<<"createSplineItrFastBorderAreasForPoints(setMinimumArea="<<setMinimumArea.size()<<", setMaximumArea="<<setMaximumArea.size()<<", pUnderobject="<<pUnderobject<<", varX="<<pVariableDimX<<", varY="<<pVariableDimY<<", uiMaxSplineParameters="<<uiMaxSplineParameters<<", maxValue="<<maxValue<<", maxError="<<maxError<<", maxErrorPerValue="<<maxErrorPerValue<<" ) started "<<endl<<flush);
	
	if ( maxErrorPerValue < 0.0 ){
		//can't create spline with negativ maximum error per value
		return NULL;
	}
	
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING

/**
 * This function combines the given set of points to Fib objects,
 * with the help of splies (polynoms with fixed number of parametes
 * uiMaxSplineParameters) .
 * For this the method @see nD1::cSpline::evalueSpline() will be used.
 * Beware: You have to care that the created subobjects will be deleted
 *
 * uses @see nD1::cSpline::evalueSpline()
 * The method should give the same result as
 * createSplineItrFastBorderAreasForPoints() but faster and with less
 * Fib elements.
 * It will iterativ increase the number of parameters for the splines
 * (from 1 to uiMaxNumberOfParameters).
 *
 * @param setPoints the set with the datapoints to combine to
 * 	Fib objects with the help of area and function elements;
 * 	The given points should be positions in an matrix, positions in
 * 	the matrix but not given, will be considerd not to be in the area
 * 	to create.
 * @param pUnderobject a pointer to the subobject, which the created
 * 	Fib elements should contain and which should be evalued for the
 * 	point positions
 * @param pVariableX a pointer to the variable for the x position
 * @param pVariableY a pointer to the variable for the y position
 * @param uiMaxSplineParameters the number of parameters for the spline;
 * 	Don't choose this number to big, because the evaluation time will
 * 	grow exponentialy with this number. Even splines with 8
 * 	parameters will take some time.
 * @param uiMinBitsToStoreMantissa the minimal number of bits to store
 * 	the mantissa of the function value parameters, when the parameter
 * 	is in the form: mantissa * 2^exponent ;
 * 	the method will try to reduce the bits, to store a parameter of the
 * 	returned vector, to the uiMinBitsToStoreMantissa value;
 * 	if uiMinBitsToStoreMantissa is 0, no optimization for the mantissa
 * 	bits will be done
 * @param maxValue the maximum possible value in all parameters
 * 	the evalued spline/function elements will allways have value
 * 	parameters vecFactors[i] with
 * 	-1 * maxValue <= vecFactors[i] <= maxValue for 0 <= i \< vecFactors.size();
 * 	if 0 (standard value) is given, the maximum possible value will
 * 	be evalued from the given data
 * @param maxError the maximal error for the border polynoms to find;
 * 	the error on the interpolated polynoms for the borders will be
 * 	equal or less than maxError
 * @param ulMaxMemoryCost a number for the maximum memory cost this
 * 	method is allowed to use; if 0 the maximum memory cost is unbounded
 * @return a Fib object with the created Fib subobjects, wher the
 * 	given variables for the given pUnderobject will go over all
 * 	point positions in the given set setPoints or NULL if non
 * 	such could be created;
 * 	some positions can be evalued twice;
 * 	the Fib subobjects, wich evalue the most points, are on the
 * 	front of the list-object (have a lower subobject number);
 * 	if NULL is returnd, you have to care that pUnderobject will be
 * 	deleted, else pUnderobject will be included in one
 * 	subobject of the created list-object and the other subobject will
 * 	contain copies of pUnderobject
 * 	Structur of the created Fib object:
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 	or if this previos given structur is not possible
 * 		list(
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 			...
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 		)
 * 	(some fun or areas can be missing, if they are not needed, eg. for lines)
 */
template <class tX>
	cFibElement * fib::algorithms::nD2::createNSplineBorderAreasForPoints(
		const set< nD1::cDataPoint<tX, tX> > & setPoints,
		cFibElement * pUnderobject,
		cFibVariable * pVariableDimX,
		cFibVariable * pVariableDimY,
		const unsigned int uiMaxSplineParameters,
		const unsigned int uiMinBitsToStoreMantissa,
		double maxValue,
		const double maxError,
		const unsigned long ulMaxMemoryCost ){
	
	DEBUG_OUT_L2(<<"createNSplineBorderAreasForPoints(#setPoints="<<setPoints.size()<<", pUnderobject="<<pUnderobject<<", varX="<<pVariableDimX<<", varY="<<pVariableDimY<<", uiMaxSplineParameters="<<uiMaxSplineParameters<<", uiMinBitsToStoreMantissa="<<uiMinBitsToStoreMantissa<<", maxValue="<<maxValue<<", maxError="<<maxError<<", ulMaxMemoryCost="<<ulMaxMemoryCost<<" ) started "<<endl<<flush);
	
	return fib::algorithms::nD2::createNSplineBorderAreasForPoints(
		setPoints, setPoints, pUnderobject, pVariableDimX, pVariableDimY,
		uiMaxSplineParameters, (set< nD1::cDataPoint<tX, tX> > *)(NULL),
		uiMinBitsToStoreMantissa, maxValue, maxError, ulMaxMemoryCost );
}



/**
 * This function combines the given set of points to Fib objects,
 * with the help of splies (polynoms with fixed number of parametes
 * uiMaxSplineParameters) .
 * For this the method @see nD1::cSpline::evalueSpline() will be used.
 * Beware: You have to care that the created subobjects will be deleted
 *
 * uses @see nD1::cSpline::evalueSpline()
 * The method should give the same result as
 * createSplineItrFastBorderAreasForPoints() but faster and with less
 * Fib elements.
 * It will iterativ increase the number of parameters for the splines
 * (from 1 to uiMaxNumberOfParameters).
	 *
 * @param setMinimumArea the set with the datapoints to combine to
 * 	Fib objects with the help of area and function elements;
 * 	the created area should contain all of these points;
 * 	The given points should be positions in an matrix, positions in
 * 	the matrix but not given, will be considerd not to be in the area
 * 	to create.
 * @param setMaximumArea the set with the datapoints to combine to
 * 	Fib objects with the help of area and function elements;
 * 	the created area can contain these points;
 * 	this set should contain all points from setMinimumArea;
 * 	The given points should be positions in an matrix, positions in
 * 	the matrix but not given, will be considerd not to be in the area
 * 	to create.
 * @param pUnderobject a pointer to the subobject, which the created
 * 	Fib elements should contain and which should be evalued for the
 * 	point positions
 * @param pVariableX a pointer to the variable for the x position
 * @param pVariableY a pointer to the variable for the y position
 * @param uiMaxSplineParameters the number of parameters for the spline;
 * 	Don't choose this number to big, because the evaluation time will
 * 	grow exponentialy with this number. Even splines with 8
 * 	parameters will take some time.
 * @param pOutSetMissingPoints if not NULL, the points not in the
 * 	created area will be inserted/added into this set, when this
 * 	function returns
 * @param uiMinBitsToStoreMantissa the minimal number of bits to store
 * 	the mantissa of the function value parameters, when the parameter
 * 	is in the form: mantissa * 2^exponent ;
 * 	the method will try to reduce the bits, to store a parameter of the
 * 	returned vector, to the uiMinBitsToStoreMantissa value;
 * 	if uiMinBitsToStoreMantissa is 0, no optimization for the mantissa
 * 	bits will be done
 * @param maxValue the maximum possible value in all parameters
 * 	the evalued spline/function elements will allways have value
 * 	parameters vecFactors[i] with
 * 	-1 * maxValue <= vecFactors[i] <= maxValue for 0 <= i \< vecFactors.size();
 * 	if 0 (standard value) is given, the maximum possible value will
 * 	be evalued from the given data
 * @param maxError the maximal error for the border polynoms to find;
 * 	the error on the interpolated polynoms for the borders will be
 * 	equal or less than maxError
 * @param ulMaxMemoryCost a number for the maximum memory cost this
 * 	method is allowed to use; if 0 the maximum memory cost is unbounded
 * @return a Fib object with the created Fib subobjects, wher the
 * 	given variables for the given pUnderobject will go over all
 * 	point positions in the given set setPoints or NULL if non
 * 	such could be created;
 * 	some positions can be evalued twice;
 * 	the Fib subobjects, wich evalue the most points, are on the
 * 	front of the list-object (have a lower subobject number);
 * 	if NULL is returnd, you have to care that pUnderobject will be
 * 	deleted, else pUnderobject will be included in one
 * 	subobject of the created list-object and the other subobject will
 * 	contain copies of pUnderobject
 * 	Structur of the created Fib object:
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 	or if this previos given structur is not possible
 * 		list(
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 			...
 * 		area( fun( fun( fun( area( pUnderobject )))))
 * 		)
 * 	(some fun or areas can be missing, if they are not needed, eg. for lines)
 */
template <class tX>
	cFibElement * fib::algorithms::nD2::createNSplineBorderAreasForPoints(
		const set< nD1::cDataPoint<tX, tX> > & setMinimumArea,
		const set< nD1::cDataPoint<tX, tX> > & setMaximumArea,
		cFibElement * pUnderobject,
		cFibVariable * pVariableDimX,
		cFibVariable * pVariableDimY,
		const unsigned int uiMaxSplineParameters,
		set< nD1::cDataPoint<tX, tX> > * pOutSetMissingPoints,
		const unsigned int uiMinBitsToStoreMantissa,
		double maxValue,
		const double maxError,
		const unsigned long ulMaxMemoryCost ){
	
	DEBUG_OUT_L2(<<"createSplineItrFastBorderAreasForPoints(setMinimumArea="<<setMinimumArea.size()<<", setMaximumArea="<<setMaximumArea.size()<<", pUnderobject="<<pUnderobject<<", varX="<<pVariableDimX<<", varY="<<pVariableDimY<<", uiMaxSplineParameters="<<uiMaxSplineParameters<<", uiMinBitsToStoreMantissa="<<uiMinBitsToStoreMantissa<<", maxValue="<<maxValue<<", maxError="<<maxError<<", ulMaxMemoryCost="<<ulMaxMemoryCost<<" ) started "<<endl<<flush);
	
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
	
	if ( setMinimumArea.empty() ){
		//no data points, for which to create the areas
		return NULL;
	}
	if ( setMaximumArea.empty() ){
		//no data points, for which to create the areas
		return NULL;
	}
	if ( pUnderobject == NULL ){
		//no subobject, wich to use in created Fib objects
		return NULL;
	}
	if ( ( pVariableDimX == NULL ) || ( pVariableDimY == NULL ) ){
		//missing variable, wich to use in created Fib objects
		return NULL;
	}
	if ( uiMaxSplineParameters == 0 ){
		//can't create spline with 0 parameters, which match datapoints
		return NULL;
	}
	if ( maxError < 0.0 ){
		//can't create spline with negativ maximum error
		return NULL;
	}
	if ( maxValue < 0.0 ){
		//can't create spline with this maximum value
		return NULL;
	}//else
	
	typedef fib::algorithms::nD1::cDataPoint<tX, tX> typeDataPoint;
	typedef set< typeDataPoint > typeSetDataPoints;
	typedef typename typeSetDataPoints::const_iterator typeConstItrSetDataPoints;
	typedef typename typeSetDataPoints::const_reverse_iterator typeConstRevItrSetDataPoints;
	
	if ( maxValue == 0.0 ){
		//evalue the maximum value
		double dMaxDataValue = 0.0;
		for ( typeConstItrSetDataPoints itrPoint = setMaximumArea.begin();
				itrPoint != setMaximumArea.end(); itrPoint++ ){
			
			const tX absY = ( 0 <= itrPoint->y )?( itrPoint->y ):( ((tX)(-1)) * itrPoint->y );
			if ( dMaxDataValue < absY ){
				dMaxDataValue = absY;
			}
			const tX absX = ( 0 <= itrPoint->x )?( itrPoint->x ):( ((tX)(-1)) * itrPoint->x );
			if ( dMaxDataValue < absX ){
				dMaxDataValue = absX;
			}
		}
		if ( dMaxDataValue ){
			dMaxDataValue = 1.0;
		}
		maxValue = dMaxDataValue * 1024.0;
	}//end if maxValue == 0

	
	/*create areas for the minimum and maximum number of points in the
	directions (the maximum area is the area of points, which can be contained
	in an created area object, the minimum is the area of points, which are
	not contained in an other created areas)*/
	typeSetDataPoints setMinimumXArea = setMinimumArea;
	typeSetDataPoints setMaximumXArea = setMaximumArea;
	
	/*the Y Areas /Sets are the same as the X Areas/Sets, but of a matrix
	rotated with 90 degree*/
	typeSetDataPoints setMinimumYArea;
	for ( typeConstItrSetDataPoints itrPoint = setMinimumArea.begin();
			itrPoint != setMinimumArea.end(); itrPoint++ ){
		
		setMinimumYArea.insert( typeDataPoint( itrPoint->y, itrPoint->x ) );
	}
	typeSetDataPoints setMaximumYArea;
	if ( ( & setMinimumArea ) == ( & setMaximumArea ) ){
		//minimum and maximum areas are equal
		setMaximumYArea = setMinimumYArea;
	}else{
		for ( typeConstItrSetDataPoints itrPoint = setMaximumArea.begin();
				itrPoint != setMaximumArea.end(); itrPoint++ ){
			
			setMaximumYArea.insert( typeDataPoint( itrPoint->y, itrPoint->x ) );
		}
	}

	/*the created elemental areas;
		- first pair element: number of points, the area covers
		- second pair element: the the area as an Fib object*/
	list< pair< unsigned long, cFibElement * > > liAreaList;
	
	DEBUG_OUT_L2(<<"beginning searching for areas"<<endl<<flush);
	
	//while not all points are included in the area
	while ( ( ! setMinimumXArea.empty() ) ||  ( ! setMinimumYArea.empty() ) ){
	/*create areas:
		- begin at the outer side of the minimum areas of points which
			should be found; prefer big areas
		- remove points from the minimum areas, which are included in created areas
		- borders are points, which should be in the area, but which
			neibours shouldn't be in the area*/
		
		//scan in x direction
		/* The list with the possible areas.
		* The pair elements are:
		* 	first element: the number of points in the possible area
		* 	second element: list with the possible areas containing each a
		* 	list with the pairs for the lines: first element is the upper
		* 	border of the line and the second the lower border
		*/
		typedef list< pair< unsigned long, list< pair< typeDataPoint,
			typeDataPoint > > > > typePossibleAreas;
		typePossibleAreas possibleXAreas;
		
		typeConstItrSetDataPoints itrPoint = setMinimumXArea.begin();
		typeDataPoint dataPoint = *itrPoint;
		typeDataPoint dataPointLineBegin = *itrPoint;
		
		while ( itrPoint != setMinimumXArea.end() ){
			
			if ( dataPoint != *itrPoint ){
				/*this point isn't the x neibour of the last point
				-> new line begin; *itrXPoint = new line begin; dataPoint.y-- = old line end*/
				dataPoint.y--;//old line end
				/*insert old line to every possible area or create a new area, if
				no possible area exists*/
				const pair< typeDataPoint, typeDataPoint >
					paNewLine( dataPointLineBegin, dataPoint);
				integrateLineInAreas( possibleXAreas, paNewLine );
	
				dataPointLineBegin = *itrPoint;//remember line begin
			}
			dataPoint = *itrPoint;
			itrPoint++;
			dataPoint.y++;//next neibour in x direction for the last point
		}
		{//add last line
			dataPoint.y--;
			const pair< typeDataPoint, typeDataPoint >
				paNewLine( dataPointLineBegin, dataPoint);
			integrateLineInAreas( possibleXAreas, paNewLine );
		}
		//scan in y direction
		typePossibleAreas possibleYAreas;
		
		itrPoint = setMinimumYArea.begin();
		dataPoint = *itrPoint;
		dataPointLineBegin = *itrPoint;
		
		while ( itrPoint != setMinimumYArea.end() ){
			
			if ( dataPoint != *itrPoint ){
				/*this point isn't the x neibour of the last point
				-> new line begin; *itrXPoint = new line begin; dataPoint.y-- = old line end*/
				dataPoint.y--;//old line end
				/*insert old line to every possible area or create a new area, if
				no possible area exists*/
				const pair< typeDataPoint, typeDataPoint >
					paNewLine( dataPointLineBegin, dataPoint);
				integrateLineInAreas( possibleYAreas, paNewLine );
	
				dataPointLineBegin = *itrPoint;//remember line begin
			}
			dataPoint = *itrPoint;
			itrPoint++;
			dataPoint.y++;//next neibour in x direction for the last point
		}
		{//add last line
			dataPoint.y--;
			const pair< typeDataPoint, typeDataPoint >
				paNewLine( dataPointLineBegin, dataPoint);
			integrateLineInAreas( possibleYAreas, paNewLine );
		}
		//choose the area for which to create the Fib structur
		/*the type filds are:
			- number of points in the area
				- iterator to the area
				- if the area is a x area (x = true; y = false)*/
		typedef set< pair< unsigned long, pair< typename typePossibleAreas::const_iterator, bool > >,
				structLowerFirstElement< pair< typename typePossibleAreas::const_iterator, bool > > >
				typeSetOrderdAreas;
		typeSetOrderdAreas setAreas;
		
		for ( typename typePossibleAreas::const_iterator itrActualArea = possibleXAreas.begin();
				itrActualArea != possibleXAreas.end(); itrActualArea++ ){
			
			setAreas.insert( make_pair( itrActualArea->first, make_pair( itrActualArea, true ) ) );
		}
		for ( typename typePossibleAreas::const_iterator itrActualArea = possibleYAreas.begin();
				itrActualArea != possibleYAreas.end(); itrActualArea++ ){
			
			setAreas.insert( make_pair( itrActualArea->first, make_pair( itrActualArea, false ) ) );
		}
		
		//try biggest area and than the areas befor, if biggest area couldn't be used
		typename typeSetOrderdAreas::const_reverse_iterator
				itrActualToConvertArea = setAreas.rbegin();
		unsigned long uiPointsRemoved = 0;
		for ( ; itrActualToConvertArea != setAreas.rend(); itrActualToConvertArea++ ){
			
			if ( itrActualToConvertArea->first <= 4 ){
				DEBUG_OUT_L2(<<"just maximal "<<itrActualToConvertArea->first<<" points in remaining areas"<<endl<<flush);
				//stop evaluation, because no area with more than 4 points exists
				itrActualToConvertArea = setAreas.rend();
				break;
			}
			
			const typename typePossibleAreas::const_iterator itrToConvertArea =
				itrActualToConvertArea->second.first;
			//x = true; y = false
			const bool bChoosenDirection = itrActualToConvertArea->second.second;
			
			//evalue ranges for the choosen area in directions
			typedef list< pair< typeDataPoint, typeDataPoint > > typeDataPointList;
			typedef typename typeDataPointList::const_iterator typeItrDataPointList;
#ifdef DEBUG_N_D2
			cout<<"founded best datapoints (direction "<<(bChoosenDirection?"x":"y")<<" ): ";
			for ( typeItrDataPointList itrDataPoint = itrToConvertArea->second.begin();
					itrDataPoint != itrToConvertArea->second.end(); itrDataPoint++ ){
				cout<<"("<< itrDataPoint->first.x <<";[ "<< itrDataPoint->first.y
					<<" ... "<< itrDataPoint->second.y <<" ] ); ";
			}
			cout<<endl;
#endif
			DEBUG_OUT_L2(<<"creating range datapoints for areas"<<endl<<flush);
			vector< fib::algorithms::nD1::cDataPointRange< tX, double > > vecRangesUpper;
			vector< fib::algorithms::nD1::cDataPointRange< tX, double > > vecRangesLower;
			
			const bool bBordersEqual = findBorderRanges( *itrToConvertArea,
				bChoosenDirection, setMaximumXArea, setMaximumYArea,
				vecRangesLower, vecRangesUpper );
	
			if ( vecRangesLower.empty() || vecRangesUpper.empty() ){
				DEBUG_OUT_EL2(<<"one range empty:"<<endl<<flush);
#ifdef DEBUG_N_D2
				cout<<"vecRangesLower: ";
				for ( unsigned int uiActRange = 0; uiActRange < vecRangesLower.size(); uiActRange++ ){
					cout<<"("<<vecRangesLower[uiActRange].x<<";["<<
						vecRangesLower[uiActRange].minY<<" ... "<<vecRangesLower[uiActRange].maxY<<"] ); ";
				}
				cout<<"vecRangesUpper: ";
				for ( unsigned int uiActRange = 0; uiActRange < vecRangesUpper.size(); uiActRange++ ){
					cout<<"("<<vecRangesUpper[uiActRange].x<<";["<<
						vecRangesUpper[uiActRange].minY<<" ... "<<vecRangesUpper[uiActRange].maxY<<"] ); ";
				}
#endif
				continue;//check next area
			}
			//the x offset so that the spline will begin at 0
			const tX xOffset = vecRangesUpper[ 0 ].x;
			
			//dismiss created areas which have (much) more points as in the maximal area
			unsigned long ulAceptablePointsForArea = 8;
			for ( unsigned int uiActRange = 0; uiActRange < vecRangesLower.size(); uiActRange++ ){
				
				ulAceptablePointsForArea += vecRangesUpper[uiActRange].maxY - vecRangesLower[uiActRange].minY + 1;
				
				//move the x component about the offset (subtract offset)
				vecRangesUpper[ uiActRange ].x -= xOffset;
				vecRangesLower[ uiActRange ].x -= xOffset;
			}
			
			//evalue the splines for the borders
			DEBUG_OUT_L2(<<"The borders are "<<(bBordersEqual?"equal":"not equal")<<endl);
			DEBUG_OUT_L2(<<"evaluing the spline for the lower border (evalueSpline() ):"<<endl<<flush);
			cSpline< tX, double > splineLower;
#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
			const unsigned long uiPointsIncludedLower = splineLower.evalueSpline(
				vecRangesLower, uiMaxSplineParameters,
				maxValue, maxError, maxErrorPerValue );
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
			const unsigned long uiPointsIncludedLower = splineLower.evalueSpline(
				vecRangesLower, uiMaxSplineParameters,
				uiMinBitsToStoreMantissa, maxValue, maxError, ulMaxMemoryCost );
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
			
#ifdef DEBUG_N_D2
			cout<<"vecRangesLower: ";
			for ( unsigned int uiActRange = 0; uiActRange < vecRangesLower.size(); uiActRange++ ){
				cout<<"("<<vecRangesLower[uiActRange].x<<";["<<
					vecRangesLower[uiActRange].minY<<" ... "<<vecRangesLower[uiActRange].maxY<<"] ); ";
			}
			cout<<endl<<"spline for lower border (for the "<<uiPointsIncludedLower<<" first points): ";splineLower.print( cout );
#endif
			if ( uiPointsIncludedLower < 1 ){
				//no points included -> no lower border
				continue;//check next area
			}
			cSpline< tX, double > splineUpper;
			unsigned long uiLastPointsIncluded = uiPointsIncludedLower - 1;
			if ( ! bBordersEqual ){
				
				if ( uiPointsIncludedLower < vecRangesUpper.size()  ){
					//don't need to include all points in the upper range
					DEBUG_OUT_L2(<<"resizing upper boundery from "<<vecRangesUpper.size()<<" to "<<uiPointsIncludedLower<<", because the remaining points arn't needed"<<endl<<flush);
					vecRangesUpper.resize( uiPointsIncludedLower );
				}
				DEBUG_OUT_L2(<<"evaluing the spline for the upper border (evalueSpline() ):"<<endl<<flush);
#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
				const unsigned long uiPointsIncludedUpper = splineUpper.evalueSpline(
					vecRangesUpper, uiMaxSplineParameters,
					maxValue, maxError, maxErrorPerValue );
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
				const unsigned long uiPointsIncludedUpper = splineUpper.evalueSpline(
					vecRangesUpper, uiMaxSplineParameters,
					uiMinBitsToStoreMantissa, maxValue, maxError, ulMaxMemoryCost );
				
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
				
				if ( uiPointsIncludedUpper < 1 ){
					//no points included -> no upper border
					continue;//check next area
				}
				
				uiLastPointsIncluded = min(
					uiPointsIncludedLower, uiPointsIncludedUpper ) - 1;
#ifdef DEBUG_N_D2
				cout<<"vecRangesUpper: ";
				for ( unsigned int uiActRange = 0; uiActRange < vecRangesUpper.size(); uiActRange++ ){
					cout<<"("<<vecRangesUpper[uiActRange].x<<";["<<
						vecRangesUpper[uiActRange].minY<<" ... "<<vecRangesUpper[uiActRange].maxY<<"] ); ";
				}
				cout<<endl<<"spline for upper border (for the "<<uiPointsIncludedUpper<<" first points): ";splineUpper.print( cout );
#endif
			}//else borders are equal -> don't need to evalue spline for upper border
#ifdef DEBUG_N_D2
			cout<<endl<<"evalued ranges: "<<flush;
			for ( unsigned int uiActRange = 0; uiActRange < vecRangesLower.size(); uiActRange++ ){
				cout<<"("<<vecRangesLower[uiActRange].x<<";["<<
					splineLower.evalue( vecRangesLower[uiActRange].x )<<" ... "<<
					splineUpper.evalue( vecRangesLower[uiActRange].x )<<"] ); ";
			}
			cout<<endl<<"evalued ranges compared: "<<flush;
			for ( unsigned int uiActRange = 0; (uiActRange < vecRangesLower.size()) &&
					(uiActRange < vecRangesUpper.size()) ; uiActRange++ ){
				cout<<"("<<vecRangesLower[uiActRange].x<<";["<<
					vecRangesLower[uiActRange].minY<<"<"<<flush<<
					splineLower.evalue( vecRangesLower[uiActRange].x )<<"<"<<flush<<
					vecRangesLower[uiActRange].maxY<<" ... "<<
					vecRangesUpper[uiActRange].minY<<"<"<<flush<<
					splineUpper.evalue( vecRangesLower[uiActRange].x )<<"<"<<flush<<
					vecRangesUpper[uiActRange].maxY<<"] ); "<<flush;
			}
			cout<<endl;
			if ( vecRangesLower.size() !=  vecRangesUpper.size() ){
				cout<<"Ther are ranges in the lower border: "<<vecRangesLower.size()<<
					" but in the upper border ther are : "<<vecRangesUpper.size()<<endl<<flush;
			}
#endif
			//include points wich are in max bounderies
			DEBUG_OUT_L2(<<"last point included in bounderies: "<<uiLastPointsIncluded<<endl<<flush);
			
			DEBUG_OUT_L2(<<"creating area object"<<endl<<flush);
			cArea * pAreaNew = NULL;
			
			if ( ( ! bBordersEqual ) && ( splineUpper != splineLower ) ){
				pAreaNew = createAreaFibObject( bChoosenDirection,
					roundToLongFib( vecRangesLower.front().x ),
					roundToLongFib( vecRangesLower[ uiLastPointsIncluded ].x ),
					splineLower, splineUpper, xOffset );
			}else{
				pAreaNew = createLineFibObject( bChoosenDirection,
					roundToLongFib( vecRangesLower.front().x ),
					roundToLongFib( vecRangesLower[ uiLastPointsIncluded ].x ),
					splineLower, xOffset );
			}
#ifdef DEBUG_N_D2_2
			DEBUG_OUT_L2(<<"created area object: "<<endl<<flush);
//			pAreaNew->getDefinedVariable()->setValue( 1.0 );
			//enumerate variables so thy can be identified
			list<cFibVariable*> liDefVariables =
				pAreaNew->getDefinedVariables( ED_BELOW_EQUAL );
			unsigned int uiNumber = 1;
			for ( list<cFibVariable*>::iterator itrVariable = liDefVariables.begin();
					itrVariable != liDefVariables.end(); itrVariable++, uiNumber++ ){
				
				(*itrVariable)->setValue( uiNumber );
			}
			pAreaNew->storeXml( cout );
#endif
			DEBUG_OUT_L2(<<"evaluing points in area object"<<endl<<flush);
			//count points in the area
			cEvaluePositionListLimit evaluedPositionsData(
				ulAceptablePointsForArea + 1, NULL, true, 0, ulAceptablePointsForArea * 16 );
			const bool bObjectEvalued = pAreaNew->evalueObjectSimple( evaluedPositionsData );
			
			const unsigned long ulNumberOfPoints = evaluedPositionsData.liEvaluedPositionData.size();
			DEBUG_OUT_L2(<<"evalued ulNumberOfPoints= "<<ulNumberOfPoints<<"  ulAceptablePointsForArea="<<ulAceptablePointsForArea<<" bObjectEvalued="<<(bObjectEvalued?"true":"false")<<endl<<flush);
			
			bool bAreaAdded = false;
			if ( bObjectEvalued && ( 4 < ulNumberOfPoints ) &&
					( ulNumberOfPoints <= ulAceptablePointsForArea ) ){
				
				//check how many points are in the area to find
				unsigned long ulPointsInMaxArea = 0;
				unsigned long ulPointsInMinArea = 0;
				DEBUG_OUT_L2(<<"Evalud points: "<<flush);
				for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
						itrPoint = evaluedPositionsData.liEvaluedPositionData.begin();
						itrPoint != evaluedPositionsData.liEvaluedPositionData.end();
						itrPoint++ ){
					
					const typeDataPoint dataXPointTmp(
						roundToLongFib( itrPoint->first.getValue( 1 ) ),
						roundToLongFib( itrPoint->first.getValue( 2 ) ) );
					const typeConstItrSetDataPoints itrFoundPointMax =
						setMaximumXArea.find( dataXPointTmp );
					if ( itrFoundPointMax != setMaximumXArea.end() ){
						ulPointsInMaxArea++;
					}
					const typeConstItrSetDataPoints itrFoundPointMin =
						setMinimumXArea.find( dataXPointTmp );
					if ( itrFoundPointMin != setMinimumXArea.end() ){
						ulPointsInMinArea++;
					}
					DEBUG_OUT_L2(<<"( "<<dataXPointTmp.x<<","<<dataXPointTmp.y<<") in "<<((itrFoundPointMax != setMaximumXArea.end())?"max ":"")<<((itrFoundPointMin != setMinimumXArea.end())?"min; ":"; ")<<flush);
				}
				DEBUG_OUT_L2(<<endl<<"points in maximum area: "<<ulPointsInMaxArea<<" points outside the maximum area: "<<(ulNumberOfPoints - ulPointsInMaxArea)<<endl<<flush);
				DEBUG_OUT_L2(<<"points in minimum area: "<<ulPointsInMinArea<<" points outside the minimum area: "<<(ulNumberOfPoints - ulPointsInMinArea)<<endl<<flush);
				
				if ( ( (ulNumberOfPoints - ulNumberOfPoints / 16 - 2) <= ulPointsInMaxArea ) &&
						( (ulNumberOfPoints / 8 + 2) <= ulPointsInMinArea ) ){
					/*no more than 1/16 of the evalued points outside the given area
					-> add created area  and remove the points in the created area
					from the minimum area*/
					
					//replace point of the area with the given subobject
					DEBUG_OUT_L2(<<"Replace point of the area with the given subobject"<<endl<<flush);
					cFibElement * pSubobjectToInsert = NULL;
					if ( liAreaList.empty() ){
						//first underarea created -> use the original object pUnderobject
						pSubobjectToInsert = pUnderobject;
					}else{//not the first underarea created -> use the clone of the original object pUnderobject
						pSubobjectToInsert = pUnderobject->copy();
					}
					//replace dimension variables with point variables
					cPoint * pPoint = ((cPoint*)( pAreaNew->getNextFibElement( 'p' ) ));
					
					pSubobjectToInsert->replaceVariable( pVariableDimX, pPoint->getPosition()->getVariable( 1 ) );
					pSubobjectToInsert->replaceVariable( pVariableDimY, pPoint->getPosition()->getVariable( 2 ) );
					
					if ( pSubobjectToInsert == pUnderobject ){
						//variable in the subobject have changed
						pVariableDimX = pPoint->getPosition()->getVariable( 1 );
						pVariableDimY = pPoint->getPosition()->getVariable( 2 );
					}
					//replace the point with the Fib object to insert
					pAreaNew->overwriteObjectWithObject(
						pSubobjectToInsert, 'u', pPoint->getNumberOfElement(), true, true );
					
					
					DEBUG_OUT_L2(<<"Adding creating area to the area list"<<endl<<flush);
					liAreaList.push_back( pair< unsigned long, cFibElement * >( ulNumberOfPoints, pAreaNew ) );
					bAreaAdded = true;
					
					//remove the points in the created area from the minimum area
					for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
							itrPoint = evaluedPositionsData.liEvaluedPositionData.begin();
							itrPoint != evaluedPositionsData.liEvaluedPositionData.end();
							itrPoint++ ){
						
						const typeDataPoint dataXPointTmp(
							roundToLongFib( itrPoint->first.getValue( 1 ) ),
							roundToLongFib( itrPoint->first.getValue( 2 ) ) );
						uiPointsRemoved += setMinimumXArea.erase( dataXPointTmp );
						
						const typeDataPoint dataYPointTmp(
							roundToLongFib( itrPoint->first.getValue( 2 ) ),
							roundToLongFib( itrPoint->first.getValue( 1 ) ) );
						uiPointsRemoved += setMinimumYArea.erase( dataYPointTmp );
					}
				}
			}
			if ( ! bAreaAdded ){//delete the created subobject
				DEBUG_OUT_EL2(<<"Warning: couldn't add the area object"<<endl<<flush);
				
				pAreaNew->deleteObject();
			}
			DEBUG_OUT_L2(<<"uiPointsRemoved= "<<uiPointsRemoved<<"  ulNumberOfPoints= "<<ulNumberOfPoints<<"  ulAceptablePointsForArea="<<ulAceptablePointsForArea<<endl<<flush);
			if ( uiPointsRemoved != 0 ){
				DEBUG_OUT_L2(<<"Find the remaining areas to convert."<<endl<<flush);
				break;
			}else{
				DEBUG_OUT_EL2(<<"Warning: no points removed -> try next biggesed area"<<endl<<flush);
				//Error: no points removed -> abourt evaluation so it dosn't loop infinity
			}
			//TODO?? remove points betwean borders from the maximum area in the direction
		}//end for itrActualToConvertArea
			
			
		if ( (uiPointsRemoved == 0) && ( ! setAreas.empty() ) ){
			/*if no wher removed
			-> smooth border and decrease area*/
			DEBUG_OUT_L2(<<"Area with to much points generated (and no points removed) "<<endl<<flush);
			
			const typeSetDataPoints setRemovedPoints = smoothBorders(
				*(setAreas.begin()->second.first),
				setAreas.begin()->second.second,
				setMaximumXArea, setMaximumYArea,
				setMinimumXArea, setMinimumYArea );
			uiPointsRemoved = setRemovedPoints.size();
			
			if ( pOutSetMissingPoints ){
				pOutSetMissingPoints->insert( setRemovedPoints.begin(),
					setRemovedPoints.end() );
			}

			DEBUG_OUT_L2(<<"The number of removed points from the minimal areas is: "<<uiPointsRemoved<<endl<<flush);
			if ( uiPointsRemoved != 0 ){
				DEBUG_OUT_L2(<<"Find the remaining areas to convert."<<endl<<flush);
				break;
			}else{
				DEBUG_OUT_EL2(<<"Warning: no points removed -> try next bigges area"<<endl<<flush);
				//Error: no points removed -> abourt evaluation so it dosn't loop infinity
			}
		}
		
		if ( uiPointsRemoved == 0 ){
			DEBUG_OUT_EL2(<<"Warning: for no area points removed -> stopping evaluation, so no infinit loop occurs"<<endl<<flush);
			break;
		}
	}
	//TODO if needed -> add Fib objects for missing points
	
	if ( pOutSetMissingPoints ){
		pOutSetMissingPoints->insert( setMinimumXArea.begin(),
			setMinimumXArea.end() );
	}
	
	if ( liAreaList.empty() ){
		DEBUG_OUT_L2(<<"Warning: no subarea evalued"<<endl<<flush);
		//no area elements to return
		return NULL;
	}//else
	if ( liAreaList.size() == 1 ){
		DEBUG_OUT_L2(<<"one subarea evalued"<<endl<<flush);
		return liAreaList.front().second;
	}
	DEBUG_OUT_L2(<<"number of subarea evalued: "<<liAreaList.size()<<endl<<flush);
	//if more than one object was created, combine the created subobjects to an listelement
	liAreaList.sort( fib::algorithms::nD2::lowerFirstNumber );
	
	list<cFibElement*> liUnderobjects;
	while ( ! liAreaList.empty() ){
		liUnderobjects.push_back( liAreaList.back().second );
		liAreaList.pop_back();
	}
	DEBUG_OUT_L2(<<"Creating list-object "<<endl<<flush);
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cList * pList = new cList( liUnderobjects );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cList * pList = new cList( NULL, NULL );
	pList->addUnderobjects( liUnderobjects );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	
#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
	DEBUG_OUT_L2(<<"createSplineItrFastBorderAreasForPoints(setMinimumArea="<<setMinimumArea.size()<<", setMaximumArea="<<setMaximumArea.size()<<", pUnderobject="<<pUnderobject<<", varX="<<pVariableDimX<<", varY="<<pVariableDimY<<", uiMaxSplineParameters="<<uiMaxSplineParameters<<", maxValue="<<maxValue<<", maxError="<<maxError<<", maxErrorPerValue="<<maxErrorPerValue<<" ) done "<<endl<<flush);

	
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
	DEBUG_OUT_L2(<<"createSplineItrFastBorderAreasForPoints(setMinimumArea="<<setMinimumArea.size()<<", setMaximumArea="<<setMaximumArea.size()<<", pUnderobject="<<pUnderobject<<", varX="<<pVariableDimX<<", varY="<<pVariableDimY<<", uiMaxSplineParameters="<<uiMaxSplineParameters<<", uiMinBitsToStoreMantissa="<<uiMinBitsToStoreMantissa<<", maxValue="<<maxValue<<", maxError="<<maxError<<", ulMaxMemoryCost="<<ulMaxMemoryCost<<" ) done "<<endl<<flush);
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
	return pList;
}









#endif //___N_D2_CPP__




#ifndef ___N_D2_H_INCLUDE__
//non template functions

/**
 * @param paFirst the first pair to compare with
 * @param paSecond the second pair to compare with
 * @return true if the number of the first element of the first pair paFirst is
 * 	lower than that of the second paSecond or if they both are equal,
 * 	returns true, if the pointer of the second element of the first pair
 * 	is lower than that of the second pair, else returns false
 */
bool fib::algorithms::nD2::lowerFirstNumber(
		const pair< unsigned long, cFibElement * > & paFirst,
		const pair< unsigned long, cFibElement * > & paSecond ){
	
	return (( paFirst.first < paSecond.first ) || (
		( ( paFirst.first == paSecond.first ) && ( paFirst.second < paSecond.second ) ) ) );
}

#endif//not ___N_D2_H_INCLUDE__










