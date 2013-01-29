/**
 * @file t_nD2
 * file name: t_nD2.cpp
 * @author Betti Oesterholz
 * @date 21.02.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test tests the simple functions of the namespace nD2 .
 *
 * Copyright (C) @c GPL3 2011 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * This test tests the simple functions of the namespace nD2 .
 *
 * Functions tested in this test:
 * 	- template <class tX> cFibElement * createSplineBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setPoints, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0 );
 *
 *
 * Functions tested in the test t_nD1_createAreasForPoints.cpp:
 * 	- template <class tX> cFibElement * createAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setPoints, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY );
 * 	- template <class tX> cFibElement * createSplineItrFastBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setPoints, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0, const double maxError = 0, const unsigned long ulMaxMemoryCost = 100000 );
 * 	- template <class tX> cFibElement * createSplineItrFastBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setMinimumArea, const set< nD1::cDataPoint<tX, tX> > & setMaximumArea, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, set< nD1::cDataPoint<tX, tX> > * pOutSetMissingPoints = NULL, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0, const double maxError = 0, const unsigned long ulMaxMemoryCost = 100000 );
 * 	- template <class tX> cFibElement * createNSplineBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setPoints, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0, const double maxError = 0, const unsigned long ulMaxMemoryCost = 100000 );
 * 	- template <class tX> cFibElement * createNSplineBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setMinimumArea, const set< nD1::cDataPoint<tX, tX> > & setMaximumArea, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, set< nD1::cDataPoint<tX, tX> > * pOutSetMissingPoints = NULL, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0, const double maxError = 0, const unsigned long ulMaxMemoryCost = 100000 );
 *
 */
/*
History:
21.02.2011  Oesterholz  created
10.04.2011  Oesterholz  test for createSplineItrFastBorderAreasForPoints()
	functions added
27.09.2012  Oesterholz  FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING:
	evalueSpline(): the glp library (extern package) linear solver will be
	used to find a spline for a vector of range data points
29.01.2013  Oesterholz  Bugfix for FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
*/


//TODO debugging
//#define DEBUG


#include "cPolynom.h"
#include "nD2.h"
#include "../incl/cDataPoint.h"

#include "cFibElement.h"
#include "cArea.h"
#include "cPoint.h"
#include "cList.h"
#include "cFunction.h"
#include "cFibVariable.h"
#include "cVectorArea.h"
#include "cUnderFunction.h"
#include "cFunctionValue.h"
#include "cFunctionVariable.h"
#include "cFunctionAdd.h"
#include "cFunctionMult.h"
#include "cFunctionExp.h"


using namespace fib;
using namespace std;
using namespace fib::algorithms;

int testFindSimpleSplineArea( unsigned long &ulTestphase, unsigned int uiFunction = 0 );
int testFindComplexSplineArea( unsigned long &ulTestphase, unsigned int uiFunction = 0 );


int main(int argc,char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for the namespace nD2"<<endl;
	cout<<      "=================================="<<endl;
	
	
	//test createAreasForPoints()
	iReturn += testFindSimpleSplineArea( ulTestphase, 0 );
	iReturn += testFindComplexSplineArea( ulTestphase, 0 );

	//test createSplineItrFastBorderAreasForPoints()
	iReturn += testFindSimpleSplineArea( ulTestphase, 1 );
	iReturn += testFindComplexSplineArea( ulTestphase, 1 );
	
	//test createSplineItrFastBorderAreasForPoints( minArea, maxArea )
	iReturn += testFindSimpleSplineArea( ulTestphase, 2 );
	iReturn += testFindComplexSplineArea( ulTestphase, 2 );
	//test createSplineItrFastBorderAreasForPoints() for big maxValues
	iReturn += testFindSimpleSplineArea( ulTestphase, 3 );
	iReturn += testFindComplexSplineArea( ulTestphase, 3 );

	//test createNSplineBorderAreasForPoints()
	iReturn += testFindSimpleSplineArea( ulTestphase, 4 );
	iReturn += testFindComplexSplineArea( ulTestphase, 4 );
	//test createNSplineBorderAreasForPoints( minArea, maxArea )
	iReturn += testFindSimpleSplineArea( ulTestphase, 5 );
	iReturn += testFindComplexSplineArea( ulTestphase, 5 );

	//test createNSplineBorderAreasForPoints() for big maxValues
	iReturn += testFindSimpleSplineArea( ulTestphase, 6 );
	iReturn += testFindComplexSplineArea( ulTestphase, 6 );


	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
};



/**
 * This function creats all the datapoints on the line lX in x direction
 * betwean (inclusive) lYLower and lYUpper.
 *
 * @param lX the x value for the line
 * @param lYLower the lower y boundery value for the line
 * @param lYUpper the upper y boundery value for the line
 * @return a set with all datapoints with the x value lX and the y values
 * 	from lYLower to lYUpper
 */
set< nD1::cDataPoint< longFib, longFib > > createPointsBetweanXYY(
		const longFib lX, longFib lYLower, longFib lYUpper ){
	
	if ( lYUpper < lYLower ){
		//switch values
		const longFib lTmp = lYUpper;
		lYUpper = lYLower;
		lYLower = lTmp;
	}
	
	set< nD1::cDataPoint< longFib, longFib > > setDatapoints;
	
	for ( longFib lY = lYLower; lY <= lYUpper; lY++ ){
	
		setDatapoints.insert( nD1::cDataPoint< longFib, longFib >( lX, lY ) );
	}
	return setDatapoints;
}


/**
 * This function creats all the datapoints on the line lY in y direction
 * betwean (inclusive) lXLower and lXUpper.
 *
 * @param lXLower the lower x boundery value for the line
 * @param lXUpper the upper x boundery value for the line
 * @param lY the y value for the line
 * @return a set with all datapoints with the y value lY and the x values
 * 	from lXLower to lXUpper
 */
set< nD1::cDataPoint< longFib, longFib > > createPointsBetweanXXY(
		const longFib lY, longFib lXLower, longFib lXUpper ){
	
	if ( lXUpper < lXLower ){
		//switch values
		const longFib lTmp = lXUpper;
		lXUpper = lXLower;
		lXLower = lTmp;
	}
	
	set< nD1::cDataPoint< longFib, longFib > > setDatapoints;
	
	for ( longFib lX = lXLower; lX <= lXUpper; lX++ ){
	
		setDatapoints.insert( nD1::cDataPoint< longFib, longFib >( lX, lY ) );
	}
	return setDatapoints;
}


/**
 * This method tests the toFibUnderFunction() function of the
 * cPolynom namespace.
 *
 * metods tested:
 * 	- template <class tX> cFibElement * createSplineBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setPoints, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0 );
 * 	- template <class tX> cFibElement * createSplineItrFastBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setPoints, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0, const double maxError = 0, const unsigned long ulMaxMemoryCost = 100000 );
 * 	- template <class tX> cFibElement * createSplineItrFastBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setMinimumArea, const set< nD1::cDataPoint<tX, tX> > & setMaximumArea, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, set< nD1::cDataPoint<tX, tX> > * pOutSetMissingPoints = NULL, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0, const double maxError = 0, const unsigned long ulMaxMemoryCost = 100000 );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param uiFunction which function to create splines to use:
 * 	0: cFibElement * createSplineBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setPoints, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0, const unsigned long ulMaxMemoryCost = 100000 )
 * 	1: cFibElement * createSplineItrFastBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setPoints, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0, const double maxError = 0, const unsigned long ulMaxMemoryCost = 100000 )
 * 	2: cFibElement * createSplineItrFastBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setMinimumArea, const set< nD1::cDataPoint<tX, tX> > & setMaximumArea, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, set< nD1::cDataPoint<tX, tX> > * pOutSetMissingPoints = NULL, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0, const double maxError = 0, const unsigned long ulMaxMemoryCost = 100000 );
 * 	3: test for big maxValue: cFibElement * createSplineItrFastBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setPoints, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue, const double maxError = 0, const unsigned long ulMaxMemoryCost = 100000 )
 * 	4: cFibElement * createNSplineBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setPoints, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0, const double maxError = 0, const unsigned long ulMaxMemoryCost = 100000 )
 * 	5: cFibElement * createNSplineBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setMinimumArea, const set< nD1::cDataPoint<tX, tX> > & setMaximumArea, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, set< nD1::cDataPoint<tX, tX> > * pOutSetMissingPoints = NULL, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0, const double maxError = 0, const unsigned long ulMaxMemoryCost = 100000 );
 * 	6: test for big maxValue: cFibElement * createNSplineBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setPoints, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue, const double maxError = 0, const unsigned long ulMaxMemoryCost = 100000 )
* @return the number of erros occured in the test
 */
int testFindSimpleSplineArea( unsigned long &ulTestphase, unsigned int uiFunction ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	for ( unsigned int uiTestCase = 0; uiTestCase <= 9; uiTestCase++ ){
	/*for every testcase:
		1. create points to approximate
		2. create ares with createSplineBorderAreasForPoints() for them
		3. check if all of the points and just them are in te created area (evalue object): checkArea( set< nD1::cDataPoint<tX, tY> > & setPoints, cFibElement * pAreaElement )
		4. check if the used underobject is correct
	*/
		//1. create points to approximate
		ulTestphase++;
		
		set< nD1::cDataPoint< longFib, longFib > > setAreaPoints;
		
		switch ( uiTestCase ){
		case 2://tree rectangle
			for ( longFib lX = -1; lX <= 1; lX++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXYY( lX, -3, -1 );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
		case 1://two rectangle
			for ( longFib lX = 7; lX <= 8; lX++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXYY( lX, 3, 8 );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
		case 0://one rectangle
			for ( longFib lX = 3; lX <= 5; lX++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXYY( lX, 4, 7 );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
			switch ( uiTestCase ){
			case 0:
				cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating are for box from x values 3 to 5 and y values 4 to 7"<<endl;
			break;
			case 1:
				cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating two rectangles"<<endl;
			break;
			case 2:
				cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating tree rectangles"<<endl;
			break;
			};//end switch ( uiTestCase )
		break;
		case 3://tree rectangle in triangle formation
			cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating tree rectangles in triangle formation"<<endl;
			for ( longFib lX = 3; lX <= 5; lX++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXYY( lX, 4, 6 );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
			for ( longFib lX = 3; lX <= 6; lX++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXYY( lX, 8, 9 );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
			for ( longFib lX = 8; lX <= 9; lX++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXYY( lX, 4, 10 );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
		break;
		case 4://one side a polynom of degree 1
			cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating one side a polynom of degree 1 (x=2 ... 6; y=3 ... 2x)"<<endl;
			for ( longFib lX = 2; lX <= 6; lX++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXYY( lX, 3, 2 * lX );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
		break;
		case 5://two side a polynom of degree 1
			cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating two side a polynom of degree 1 (x=2 ... 6; y=2x ... 3x)"<<endl;
			for ( longFib lX = 2; lX <= 6; lX++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXYY( lX, 2 * lX, 3 * lX );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
		break;
		//polynomial border in y direction
		case 6://one side a polynom of degree 1
			cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating one side a polynom of degree 1 (x=3 ... 2y; y=2 ... 6)"<<endl;
			for ( longFib lY = 2; lY <= 6; lY++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXXY( lY, 3, 2 * lY );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
		break;
		case 7://two side a polynom of degree 1
			cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating two side a polynom of degree 1 (x=2y ... 3y; y=2 ... 6)"<<endl;
			for ( longFib lY = 2; lY <= 6; lY++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXXY( lY, 2 * lY, 3 * lY );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
		break;
		case 8://one line of degree 1
			cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating one line of degree 1 (x=1 ... 12 ; y=3)"<<endl;
			for ( longFib lX = 1; lX <= 7; lX++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXYY( lX, 3, 3 );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
		break;
		case 9://one line of degree 1
			cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating one line of degree 1 (x=1 ... 12 ; y=0.5*x)"<<endl;
			for ( longFib lX = 1; lX <= 12; lX++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXYY( lX, 0.5 * lX, 0.5 * lX );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
		break;

		default:
			cerr<<"Error: Unknown testcase."<<endl;
			iReturn++;
			continue;
		};//end switch ( uiTestCase )
		cFibVariable * pVariableX = new cFibVariable( NULL );
		cFibVariable * pVariableY = new cFibVariable( NULL );
		cVectorPosition vecPosition( 2 );
		vecPosition.setVariable( 1, pVariableX );
		vecPosition.setVariable( 2, pVariableY );
		
		cPoint * pPoint = new cPoint( & vecPosition );
		
		//2. create ares with createSplineBorderAreasForPoints() for them
		cFibElement * pAreaElement = NULL;
		
		switch ( uiFunction ){
			case 0:
				cout<<"pAreaElement = createSplineBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY );"<<endl;
				pAreaElement = createSplineBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY );
			break;
			case 1:
				cout<<"pAreaElement = createSplineItrFastBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY );"<<endl;
				pAreaElement = createSplineItrFastBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY );
			break;
			case 2:
				cout<<"pAreaElement = createSplineItrFastBorderAreasForPoints( setAreaPoints, setAreaPoints, pPoint, pVariableX, pVariableY );"<<endl;
				pAreaElement = createSplineItrFastBorderAreasForPoints( setAreaPoints, setAreaPoints, pPoint, pVariableX, pVariableY );
			break;
			case 3:
#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
				cout<<"pAreaElement = createSplineItrFastBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY, 4, 1E+36 );"<<endl;
				pAreaElement = createSplineItrFastBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY, 4, 1E+36 );
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
				cout<<"pAreaElement = createSplineItrFastBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY, 4, 1, 1E+36 );"<<endl;
				pAreaElement = createSplineItrFastBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY, 4, 1, 1E+36 );
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
			break;
			case 4:
				cout<<"pAreaElement = createNSplineBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY );"<<endl;
				pAreaElement = createNSplineBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY );
			break;
			case 5:
				cout<<"pAreaElement = createNSplineBorderAreasForPoints( setAreaPoints, setAreaPoints, pPoint, pVariableX, pVariableY );"<<endl;
				pAreaElement = createNSplineBorderAreasForPoints( setAreaPoints, setAreaPoints, pPoint, pVariableX, pVariableY );
			break;
			case 6:
#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
				cout<<"pAreaElement = createNSplineBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY, 4, 1E+36 );"<<endl;
				pAreaElement = createNSplineBorderAreasForPoints( setAreaPoints,
					pPoint, pVariableX, pVariableY, 4, 1E+36 );
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
				cout<<"pAreaElement = createNSplineBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY, 4, 1, 1E+36 );"<<endl;
				pAreaElement = createNSplineBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY, 4, 1, 1E+36 );
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
			break;
			default:
				cerr<<"Error: No approximations function choosen"<<endl;
				iReturn++;
			continue;
		}
		
		if ( pAreaElement ){
		
			cout<<"The area element could correctly be created."<<endl;
		}else{
			cerr<<"Error: The area element couldn't be created."<<endl;
			iReturn++;
			delete pVariableX;
			delete pVariableY;
			delete pPoint;
			continue;
		}
		
		//3. check if all of the points and just them are in te created area (evalue object): checkArea( set< nD1::cDataPoint<tX, tY> > & setPoints, cFibElement * pAreaElement )
		cEvaluePositionList evaluedPositionsData;
		const bool bObjectEvalued = pAreaElement->evalueObjectSimple( evaluedPositionsData );
		if ( ! bObjectEvalued ){
			//Error: couldn't evalue area element
			cerr<<"Error: Couldn't evalue the created area element."<<endl;
			iReturn++;
		}
		//remove the points in the created area from the minimum area
		set< nD1::cDataPoint< longFib, longFib > > setCreatedAreaPoints;
		for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
				itrPoint = evaluedPositionsData.liEvaluedPositionData.begin();
				itrPoint != evaluedPositionsData.liEvaluedPositionData.end();
				itrPoint++ ){
			
			setCreatedAreaPoints.insert(
				nD1::cDataPoint< longFib, longFib >(
					roundToLongFib( itrPoint->first.getValue( 1 ) ),
					roundToLongFib( itrPoint->first.getValue( 2 ) ) ) );
		}
		if ( setAreaPoints == setCreatedAreaPoints ){
		
			cout<<"The area element created has the correct points."<<endl;
		}else{
			cerr<<"Error: The area element created hasn't the correct points."<<
				"(original points: "<< setAreaPoints.size() <<
				"  created points: "<< setCreatedAreaPoints.size() <<" )"<<endl;
			iReturn++;
			
			
			set< nD1::cDataPoint< longFib, longFib > > setCreatedAreaPointsNotOriginal =
				setCreatedAreaPoints;
			
			for ( set<  nD1::cDataPoint< longFib, longFib > >::const_iterator
					itrPoint = setAreaPoints.begin();
					itrPoint != setAreaPoints.end(); itrPoint++ ){
				setCreatedAreaPointsNotOriginal.erase( *itrPoint );
			}
			cerr<<"Points created but not in the original:";
			for ( set<  nD1::cDataPoint< longFib, longFib > >::const_iterator
					itrPoint = setCreatedAreaPointsNotOriginal.begin();
					itrPoint != setCreatedAreaPointsNotOriginal.end(); itrPoint++ ){
				
				cerr<<"("<<itrPoint->x<<"; "<<itrPoint->y<<" ); ";
			}
			cerr<<endl;
			for ( set<  nD1::cDataPoint< longFib, longFib > >::const_iterator
					itrPoint = setCreatedAreaPoints.begin();
					itrPoint != setCreatedAreaPoints.end(); itrPoint++ ){
				
				setAreaPoints.erase( *itrPoint );
			}
			cerr<<"Points in original but not created: ";
			for ( set< nD1::cDataPoint< longFib, longFib > >::const_iterator
					itrPoint = setAreaPoints.begin();
					itrPoint != setAreaPoints.end(); itrPoint++ ){
				
				cerr<<"("<<itrPoint->x<<"; "<<itrPoint->y<<" ); ";
			}
			cerr<<endl;
			cerr<<"Created Fib object for the area: "<<endl;
			pAreaElement->storeXml( cerr );
			cerr<<endl;
		}
		
		delete pVariableX;
		delete pVariableY;
		pAreaElement->deleteObject();
	}

	return iReturn;
}



/**
 * This method tests the toFibUnderFunction() function of the
 * cPolynom namespace.
 *
 * metods tested:
 * 	- template <class tX> cFibElement * createSplineBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setPoints, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0 );
 * 	- template <class tX> cFibElement * createSplineItrFastBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setPoints, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0, const double maxError = 0, const unsigned long ulMaxMemoryCost = 100000 );
 * 	- template <class tX> cFibElement * createSplineItrFastBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setMinimumArea, const set< nD1::cDataPoint<tX, tX> > & setMaximumArea, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, set< nD1::cDataPoint<tX, tX> > * pOutSetMissingPoints = NULL, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0, const double maxError = 0, const unsigned long ulMaxMemoryCost = 100000 );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param uiFunction which function to create splines to use:
 * 	0: cFibElement * createSplineBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setPoints, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0, const unsigned long ulMaxMemoryCost = 100000 )
 * 	1: cFibElement * createSplineItrFastBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setPoints, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0, const double maxError = 0, const unsigned long ulMaxMemoryCost = 100000 )
 * 	2: cFibElement * createSplineItrFastBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setMinimumArea, const set< nD1::cDataPoint<tX, tX> > & setMaximumArea, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, set< nD1::cDataPoint<tX, tX> > * pOutSetMissingPoints = NULL, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0, const double maxError = 0, const unsigned long ulMaxMemoryCost = 100000 );
 * 	3: test for big maxValue: cFibElement * createSplineItrFastBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setPoints, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue, const double maxError = 0, const unsigned long ulMaxMemoryCost = 100000 )
 * 	4: cFibElement * createNSplineBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setPoints, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0, const double maxError = 0, const unsigned long ulMaxMemoryCost = 100000 )
 * 	5: cFibElement * createNSplineBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setMinimumArea, const set< nD1::cDataPoint<tX, tX> > & setMaximumArea, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, set< nD1::cDataPoint<tX, tX> > * pOutSetMissingPoints = NULL, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue = 0, const double maxError = 0, const unsigned long ulMaxMemoryCost = 100000 );
 * 	6: test for big maxValue: cFibElement * createNSplineBorderAreasForPoints( const set< nD1::cDataPoint<tX, tX> > & setPoints, cFibElement * pUnderobject, cFibVariable * pVariableDimX, cFibVariable * pVariableDimY, const unsigned int uiMaxSplineParameters = 4, const unsigned int uiMinBitsToStoreMantissa = 1, const double maxValue, const double maxError = 0, const unsigned long ulMaxMemoryCost = 100000 )
 * @return the number of erros occured in the test
 */
int testFindComplexSplineArea( unsigned long &ulTestphase, unsigned int uiFunction ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	for ( unsigned int uiTestCase = 0; uiTestCase <= 6; uiTestCase++ ){
	/*for every testcase:
		1. create points to approximate
		2. create ares with createSplineBorderAreasForPoints() for them
		3. check if all of the points and just them are in te created area (evalue object): checkArea( set< nD1::cDataPoint<tX, tY> > & setPoints, cFibElement * pAreaElement )
		4. check if the used underobject is correct
	*/
		//1. create points to approximate
		ulTestphase++;
		
		set< nD1::cDataPoint< longFib, longFib > > setAreaPoints;

		
		switch ( uiTestCase ){
		case 0://tree rectangle in triangle formation with two intersection
			cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating tree rectangle in triangle formation with two intersection"<<endl;
			for ( longFib lX = 3; lX <= 5; lX++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXYY( lX, 4, 6 );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
			for ( longFib lX = 3; lX <= 6; lX++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXYY( lX, 7, 9 );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
			for ( longFib lX = 8; lX <= 9; lX++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXYY( lX, 4, 10 );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
		break;
		case 1://tree rectangle in triangle formation overlapping
			cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating tree rectangles in triangle formation overlapping"<<endl;
			for ( longFib lX = 3; lX <= 5; lX++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXYY( lX, 4, 6 );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
			for ( longFib lX = 3; lX <= 6; lX++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXYY( lX, 7, 9 );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
			for ( longFib lX = 5; lX <= 7; lX++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXYY( lX, 4, 10 );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
		break;
		case 2:
			cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating two side a polynom of degree 2 (x=1 ... 4; y=(1/3*x^2 - 1) ... (x^2 + 1))"<<endl;
			for ( longFib lX = 1; lX <= 4; lX++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXYY( lX, (lX * lX) / 3 - 1, lX * lX + 1 );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
		break;
		case 3:
			cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating one side a polynom of degree 2 and the other of degree 3 (x=1 ... 4; y=(1/3*x^2 - 1) ... (x^3 + 1))"<<endl;
			for ( longFib lX = 1; lX <= 4; lX++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXYY( lX, (lX * lX) / 3 - 1, lX * lX * lX + 1 );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
		break;
		case 4:
			cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating two side a polynom of degree 2 (x=(1/3*y^2 - 1) ... (y^2 + 1), y=1 ... 4)"<<endl;
			for ( longFib lY = 1; lY <= 4; lY++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXXY( lY, (lY * lY) / 3 - 1, lY * lY + 1 );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
		break;
		case 5:
			cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating one side a polynom of degree 2 and the other of degree 3 (x=(1/3*y^2 - 1) ... (y^3 + 1); y=1 ... 4)"<<endl;
			for ( longFib lY = 1; lY <= 4; lY++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXXY( lY, (lY * lY) / 3 - 1, lY * lY * lY + 1 );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
		break;
		case 6:
			cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing creating an big L shaped area"<<endl;
			for ( longFib lX = 3; lX <= 128; lX++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXYY( lX, 4, 8 );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
			for ( longFib lX = 120; lX <= 128; lX++ ){
			
				const set< nD1::cDataPoint< longFib, longFib > > setLinePoints =
					createPointsBetweanXYY( lX, 4, 64 );
				setAreaPoints.insert( setLinePoints.begin(), setLinePoints.end() );
			}
		break;

		default:
			cerr<<"Error: Unknown testcase. "<<endl;
			iReturn++;
			continue;
		};//end switch ( uiTestCase )
		cFibVariable * pVariableX = new cFibVariable( NULL );
		cFibVariable * pVariableY = new cFibVariable( NULL );
		cVectorPosition vecPosition( 2 );
		vecPosition.setVariable( 1, pVariableX );
		vecPosition.setVariable( 2, pVariableY );
		
		cPoint * pPoint = new cPoint( & vecPosition );
		
		//2. create ares with createSplineBorderAreasForPoints() for them
		cFibElement * pAreaElement = NULL;
		
		switch ( uiFunction ){
			case 0:
				cout<<"pAreaElement = createSplineBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY );"<<endl;
				pAreaElement = createSplineBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY );
			break;
			case 1:
				cout<<"pAreaElement = createSplineItrFastBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY );"<<endl;
				pAreaElement = createSplineItrFastBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY );
			break;
			case 2:
				cout<<"pAreaElement = createSplineItrFastBorderAreasForPoints( setAreaPoints, setAreaPoints, pPoint, pVariableX, pVariableY );"<<endl;
				pAreaElement = createSplineItrFastBorderAreasForPoints( setAreaPoints, setAreaPoints, pPoint, pVariableX, pVariableY );
			break;
			case 3:
#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
				cout<<"pAreaElement = createSplineItrFastBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY, 4, 1E+36 );"<<endl;
				pAreaElement = createSplineItrFastBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY, 4, 1E+36 );
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
				cout<<"pAreaElement = createSplineItrFastBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY, 4, 1, 1E+36 );"<<endl;
				pAreaElement = createSplineItrFastBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY, 4, 1, 1E+36 );
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
			break;
			case 4:
				cout<<"pAreaElement = createNSplineBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY );"<<endl;
				pAreaElement = createSplineItrFastBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY );
			break;
			case 5:
				cout<<"pAreaElement = createNSplineBorderAreasForPoints( setAreaPoints, setAreaPoints, pPoint, pVariableX, pVariableY );"<<endl;
				pAreaElement = createSplineItrFastBorderAreasForPoints( setAreaPoints, setAreaPoints, pPoint, pVariableX, pVariableY );
			break;
			case 6:
#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
				cout<<"pAreaElement = createNSplineBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY, 4, 1E+36 );"<<endl;
				pAreaElement = createSplineItrFastBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY, 4, 1E+36 );
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
				cout<<"pAreaElement = createNSplineBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY, 4, 1, 1E+36 );"<<endl;
				pAreaElement = createSplineItrFastBorderAreasForPoints( setAreaPoints, pPoint, pVariableX, pVariableY, 4, 1, 1E+36 );
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
			break;
			default:
				cerr<<"Error: No approximations function choosen "<<endl;
				iReturn++;
			continue;
		}
		
		if ( pAreaElement ){
		
			cout<<"The area element could correctly be created. "<<endl;
		}else{
			cerr<<"Error: The area element couldn't be created. "<<endl;
			iReturn++;
			delete pVariableX;
			delete pVariableY;
			delete pPoint;
			continue;
		}
		
		//3. check if all of the points and just them are in te created area (evalue object): checkArea( set< nD1::cDataPoint<tX, tY> > & setPoints, cFibElement * pAreaElement )
		cEvaluePositionList evaluedPositionsData;
		const bool bObjectEvalued = pAreaElement->evalueObjectSimple( evaluedPositionsData );
		if ( ! bObjectEvalued ){
			//Error: couldn't evalue area element
			cerr<<"Error: Couldn't evalue the created area element."<<endl;
			iReturn++;
		}
		//remove the points in the created area from the minimum area
		set< nD1::cDataPoint< longFib, longFib > > setCreatedAreaPoints;
		for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
				itrPoint = evaluedPositionsData.liEvaluedPositionData.begin();
				itrPoint != evaluedPositionsData.liEvaluedPositionData.end();
				itrPoint++ ){
			
			setCreatedAreaPoints.insert(
				nD1::cDataPoint< longFib, longFib >(
					roundToLongFib( itrPoint->first.getValue( 1 ) ),
					roundToLongFib( itrPoint->first.getValue( 2 ) ) ) );
		}
		if ( setAreaPoints == setCreatedAreaPoints ){
		
			cout<<"The area element created has the correct points. "<<endl;
		}else{
			cerr<<"Error: The area element created hasn't the correct points. "<<
				"(original points: "<< setAreaPoints.size() <<
				"  created points: "<< setCreatedAreaPoints.size() <<" )"<<endl;
			iReturn++;
			
			
			set< nD1::cDataPoint< longFib, longFib > > setCreatedAreaPointsNotOriginal =
				setCreatedAreaPoints;
			
			for ( set<  nD1::cDataPoint< longFib, longFib > >::const_iterator
					itrPoint = setAreaPoints.begin();
					itrPoint != setAreaPoints.end(); itrPoint++ ){
				setCreatedAreaPointsNotOriginal.erase( *itrPoint );
			}
			cerr<<"Points created but not in the original: ";
			for ( set<  nD1::cDataPoint< longFib, longFib > >::const_iterator
					itrPoint = setCreatedAreaPointsNotOriginal.begin();
					itrPoint != setCreatedAreaPointsNotOriginal.end(); itrPoint++ ){
				
				cerr<<"("<<itrPoint->x<<"; "<<itrPoint->y<<" ); ";
			}
			cerr<<endl;
			for ( set<  nD1::cDataPoint< longFib, longFib > >::const_iterator
					itrPoint = setCreatedAreaPoints.begin();
					itrPoint != setCreatedAreaPoints.end(); itrPoint++ ){
				
				setAreaPoints.erase( *itrPoint );
			}
			cerr<<"Points in original but not created: ";
			for ( set< nD1::cDataPoint< longFib, longFib > >::const_iterator
					itrPoint = setAreaPoints.begin();
					itrPoint != setAreaPoints.end(); itrPoint++ ){
				
				cerr<<"("<<itrPoint->x<<"; "<<itrPoint->y<<" ); ";
			}
			cerr<<endl;
			cerr<<"Created Fib object for the area: "<<endl;
			pAreaElement->storeXml( cerr );
			cerr<<endl;
		}
		
		delete pVariableX;
		delete pVariableY;
		pAreaElement->deleteObject();
	}
	
	return iReturn;
}

/*TODO:

- random gernerated areas

-check for errors:
	- check if the used underobject is correct
	- input underobject not ok (is NULL dont evalue correct points)
	- input variables not ok

*/











