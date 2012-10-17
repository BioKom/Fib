/**
 * @file nD2
 * file name: nD2.h
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
20.02.2011  Oesterholz  function createSplineBorderAreasForPoints() added
06.03.2011  Oesterholz  function createSplineItrFastBorderAreasForPoints() added
27.03.2011  Oesterholz  createSplineItrFastBorderAreasForPoints()
	parameter pOutSetMissingPoints added
06.07.2011  Oesterholz  functions createNSplineBorderAreasForPoints() added
24.09.2012  Oesterholz  FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING:
	evalueSpline(): the glp library (extern package) linear solver will be
	used to find a spline for a vector of range data points
*/

#ifndef ___N_D2_H__
#define ___N_D2_H__

#include "version.h"


#include "../nD1/incl/cDataPoint.h"

#include "../nD2/incl/cDataPoint.h"
#include "../nD2/incl/cDataPointRange.h"

#include "cFibElement.h"

#include <vector>
#include <set>
#include <algorithm>

using namespace std;


namespace fib{

namespace algorithms{

namespace nD2{


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
	vector< nD2::cDataPoint<tX, tY, tZ> > derivate(
		const vector< nD2::cDataPoint<tX, tY, tZ> > & vecInput );


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
	pair< vector< nD2::cDataPointRange<tX, tY, tZ> >, nD2::cDataPointRange<tX, tY, tZ> > derivateDist(
		const vector< nD2::cDataPointRange<tX, tY, tZ> > & vecInput );

	/**
	 * @param paFirst the first pair to compare with
	 * @param paSecond the second pair to compare with
	 * @return true if the number of the first element of the first pair paFirst is
	 * 	lower than that of the second paSecond, if they bouth are equal, returns true
	 * 	if the pointer of the second element of the first pair is lower than
	 * 	that of the second
	 */
	bool lowerFirstNumber( const pair< unsigned long, cFibElement * > & paFirst,
		const pair< unsigned long, cFibElement * > & paSecond );
	
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
	void integrateLineInAreas( list< pair<
		unsigned long, list< pair< fib::algorithms::nD1::cDataPoint<tX, tX>,
		fib::algorithms::nD1::cDataPoint<tX, tX> > > > > & areas,
		const pair< fib::algorithms::nD1::cDataPoint<tX, tX>,
		fib::algorithms::nD1::cDataPoint<tX, tX> > & paNewLine );
	
	/**
	 * This function combines the given set of points to fib-objects.
	 * Beware: You have to care that the created underobjects will be deleted
	 *
	 * @param setPoints the set with the datapoints to combine to
	 * 	fib-objects with the help of area and function elements;
	 * 	The given points should be positions in an matrix, positions in
	 * 	the matrix but not given, will be considerd not to be in the area
	 * 	to create.
	 * @param pUnderobject a pointer to the underobject, which the created
	 * 	fib-elements should contain and which should be evalued for the
	 * 	point positions
	 * @param pVariableX a pointer to the variable for the x position
	 * @param pVariableY a pointer to the variable for the y position
	 * @return a fib-object with the created fib-underobjects, wher the
	 * 	given variables for the given pUnderobject will go over all
	 * 	point positions in the given set setPoints or NULL if non
	 * 	such could be created;
	 * 	some positions can be evalued twice;
	 * 	the fib-underobjects, wich evalue the most points, are on the
	 * 	front of the listobject (have a lower underobject number);
	 * 	if NULL is returnd, you have to care that pUnderobject will be
	 * 	deleted, else pUnderobject will be included in one
	 * 	underobject of the created listobject and the other underobject will
	 * 	contain copies of pUnderobject
	 * 	Structur of the created fib-object:
	 * 		area( fun( fun( area( pUnderobject ))))
	 * 	or if this previos given structur is not possible
	 * 		list(
	 * 		area( fun( fun( area( pUnderobject ))))
	 * 			...
	 * 		area( fun( fun( area( pUnderobject ))))
	 * 		)
	 * 	(some fun or areas can be missing, if they are not needed, eg. for lines)
	 */
	template <class tX>
	cFibElement * createAreasForPoints(
		const set< nD1::cDataPoint<tX, tX> > & setPoints,
		cFibElement * pUnderobject,
		cFibVariable * pVariableDimX,
		cFibVariable * pVariableDimY );


#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING

	/**
	 * This function combines the given set of points to fib-objects,
	 * with the help of splies (polynoms with fixed number of parametes
	 * uiMaxSplineParameters) .
	 * Beware: You have to care that the created underobjects will be deleted
	 *
	 * uses @see nD1::cPolynom::evalueSpline()
	 * @param setPoints the set with the datapoints to combine to
	 * 	fib-objects with the help of area and function elements;
	 * 	The given points should be positions in an matrix, positions in
	 * 	the matrix but not given, will be considerd not to be in the area
	 * 	to create.
	 * @param pUnderobject a pointer to the underobject, which the created
	 * 	fib-elements should contain and which should be evalued for the
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
	 * @return a fib-object with the created fib-underobjects, wher the
	 * 	given variables for the given pUnderobject will go over all
	 * 	point positions in the given set setPoints or NULL if non
	 * 	such could be created;
	 * 	some positions can be evalued twice;
	 * 	the fib-underobjects, wich evalue the most points, are on the
	 * 	front of the listobject (have a lower underobject number);
	 * 	if NULL is returnd, you have to care that pUnderobject will be
	 * 	deleted, else pUnderobject will be included in one
	 * 	underobject of the created listobject and the other underobject will
	 * 	contain copies of pUnderobject
	 * 	Structur of the created fib-object:
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
	cFibElement * createSplineBorderAreasForPoints(
		const set< nD1::cDataPoint<tX, tX> > & setPoints,
		cFibElement * pUnderobject,
		cFibVariable * pVariableDimX,
		cFibVariable * pVariableDimY,
		const unsigned int uiMaxSplineParameters = 4,
		const double maxValue = 0.0 );

#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING

	/**
	 * This function combines the given set of points to fib-objects,
	 * with the help of splies (polynoms with fixed number of parametes
	 * uiMaxSplineParameters) .
	 * Beware: You have to care that the created underobjects will be deleted
	 *
	 * uses @see nD1::cPolynom::evalueSpline()
	 * @param setPoints the set with the datapoints to combine to
	 * 	fib-objects with the help of area and function elements;
	 * 	The given points should be positions in an matrix, positions in
	 * 	the matrix but not given, will be considerd not to be in the area
	 * 	to create.
	 * @param pUnderobject a pointer to the underobject, which the created
	 * 	fib-elements should contain and which should be evalued for the
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
	 * @return a fib-object with the created fib-underobjects, wher the
	 * 	given variables for the given pUnderobject will go over all
	 * 	point positions in the given set setPoints or NULL if non
	 * 	such could be created;
	 * 	some positions can be evalued twice;
	 * 	the fib-underobjects, wich evalue the most points, are on the
	 * 	front of the listobject (have a lower underobject number);
	 * 	if NULL is returnd, you have to care that pUnderobject will be
	 * 	deleted, else pUnderobject will be included in one
	 * 	underobject of the created listobject and the other underobject will
	 * 	contain copies of pUnderobject
	 * 	Structur of the created fib-object:
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
	cFibElement * createSplineBorderAreasForPoints(
		const set< nD1::cDataPoint<tX, tX> > & setPoints,
		cFibElement * pUnderobject,
		cFibVariable * pVariableDimX,
		cFibVariable * pVariableDimY,
		const unsigned int uiMaxSplineParameters = 4,
		const unsigned int uiMinBitsToStoreMantissa = 1,
		const double maxValue = 0.0,
		const unsigned long ulMaxMemoryCost = 100000 );

#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING

	/**
	 * This function combines the given set of points to fib-objects,
	 * with the help of splies (polynoms with fixed number of parametes
	 * uiMaxSplineParameters) .
	 * Beware: You have to care that the created underobjects will be deleted
	 *
	 * uses @see nD1::cPolynom::evalueSplineIterativFast()
	 * The method should give the same result as
	 * createSplineBorderAreasForPoints() but faster.
	 * It will iterativ increase the number of parameters for the splines
	 * (from 1 to uiMaxNumberOfParameters) and will try to not use all of
	 * the given range points to find the polynom.
	 *
	 * @param setPoints the set with the datapoints to combine to
	 * 	fib-objects with the help of area and function elements;
	 * 	The given points should be positions in an matrix, positions in
	 * 	the matrix but not given, will be considerd not to be in the area
	 * 	to create.
	 * @param pUnderobject a pointer to the underobject, which the created
	 * 	fib-elements should contain and which should be evalued for the
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
	 * @return a fib-object with the created fib-underobjects, wher the
	 * 	given variables for the given pUnderobject will go over all
	 * 	point positions in the given set setPoints or NULL if non
	 * 	such could be created;
	 * 	some positions can be evalued twice;
	 * 	the fib-underobjects, wich evalue the most points, are on the
	 * 	front of the listobject (have a lower underobject number);
	 * 	if NULL is returnd, you have to care that pUnderobject will be
	 * 	deleted, else pUnderobject will be included in one
	 * 	underobject of the created listobject and the other underobject will
	 * 	contain copies of pUnderobject
	 * 	Structur of the created fib-object:
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
	cFibElement * createSplineItrFastBorderAreasForPoints(
		const set< nD1::cDataPoint<tX, tX> > & setPoints,
		cFibElement * pUnderobject,
		cFibVariable * pVariableDimX,
		cFibVariable * pVariableDimY,
		const unsigned int uiMaxSplineParameters = 4,
		const unsigned int uiMinBitsToStoreMantissa = 1,
		double maxValue = 0.0,
		const double maxError = 0,
		const unsigned long ulMaxMemoryCost = 100000 );


	/**
	 * This function combines the given set of points to fib-objects,
	 * with the help of splies (polynoms with fixed number of parametes
	 * uiMaxSplineParameters) .
	 * Beware: You have to care that the created underobjects will be deleted
	 *
	 * uses @see nD1::cPolynom::evalueSplineIterativFast()
	 * The method should give the same result as
	 * createSplineBorderAreasForPoints() but faster.
	 * It will iterativ increase the number of parameters for the splines
	 * (from 1 to uiMaxNumberOfParameters) and will try to not use all of
	 * the given range points to find the polynom.
	 *
	 * @param setMinimumArea the set with the datapoints to combine to
	 * 	fib-objects with the help of area and function elements;
	 * 	the created area should contain all of these points;
	 * 	The given points should be positions in an matrix, positions in
	 * 	the matrix but not given, will be considerd not to be in the area
	 * 	to create.
	 * @param setMaximumArea the set with the datapoints to combine to
	 * 	fib-objects with the help of area and function elements;
	 * 	the created area can contain these points;
	 * 	this set should contain all points from setMinimumArea;
	 * 	The given points should be positions in an matrix, positions in
	 * 	the matrix but not given, will be considerd not to be in the area
	 * 	to create.
	 * @param pUnderobject a pointer to the underobject, which the created
	 * 	fib-elements should contain and which should be evalued for the
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
	 * @return a fib-object with the created fib-underobjects, wher the
	 * 	given variables for the given pUnderobject will go over all
	 * 	point positions in the given set setPoints or NULL if non
	 * 	such could be created;
	 * 	some positions can be evalued twice;
	 * 	the fib-underobjects, wich evalue the most points, are on the
	 * 	front of the listobject (have a lower underobject number);
	 * 	if NULL is returnd, you have to care that pUnderobject will be
	 * 	deleted, else pUnderobject will be included in one
	 * 	underobject of the created listobject and the other underobject will
	 * 	contain copies of pUnderobject
	 * 	Structur of the created fib-object:
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
	cFibElement * createSplineItrFastBorderAreasForPoints(
		const set< nD1::cDataPoint<tX, tX> > & setMinimumArea,
		const set< nD1::cDataPoint<tX, tX> > & setMaximumArea,
		cFibElement * pUnderobject,
		cFibVariable * pVariableDimX,
		cFibVariable * pVariableDimY,
		const unsigned int uiMaxSplineParameters = 4,
		set< nD1::cDataPoint<tX, tX> > * pOutSetMissingPoints = NULL,
		const unsigned int uiMinBitsToStoreMantissa = 1,
		double maxValue = 0.0,
		const double maxError = 0,
		const unsigned long ulMaxMemoryCost = 100000 );
	
	
#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING

	/**
	 * This function combines the given set of points to fib-objects,
	 * with the help of splies (polynoms with fixed number of parametes
	 * uiMaxSplineParameters) .
	 * For this the method @see nD1::cSpline::evalueSpline() will be used.
	 * Beware: You have to care that the created underobjects will be deleted
	 *
	 * uses @see nD1::cSpline::evalueSpline()
	 * The method should give the same result as
	 * createSplineItrFastBorderAreasForPoints() but faster and with less
	 * fib-elements.
	 * It will iterativ increase the number of parameters for the splines
	 * (from 1 to uiMaxNumberOfParameters).
	 *
	 * @param setPoints the set with the datapoints to combine to
	 * 	fib-objects with the help of area and function elements;
	 * 	The given points should be positions in an matrix, positions in
	 * 	the matrix but not given, will be considerd not to be in the area
	 * 	to create.
	 * @param pUnderobject a pointer to the underobject, which the created
	 * 	fib-elements should contain and which should be evalued for the
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
	 * @return a fib-object with the created fib-underobjects, wher the
	 * 	given variables for the given pUnderobject will go over all
	 * 	point positions in the given set setPoints or NULL if non
	 * 	such could be created;
	 * 	some positions can be evalued twice;
	 * 	the fib-underobjects, wich evalue the most points, are on the
	 * 	front of the listobject (have a lower underobject number);
	 * 	if NULL is returnd, you have to care that pUnderobject will be
	 * 	deleted, else pUnderobject will be included in one
	 * 	underobject of the created listobject and the other underobject will
	 * 	contain copies of pUnderobject
	 * 	Structur of the created fib-object:
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
	cFibElement * createNSplineBorderAreasForPoints(
		const set< nD1::cDataPoint<tX, tX> > & setPoints,
		cFibElement * pUnderobject,
		cFibVariable * pVariableDimX,
		cFibVariable * pVariableDimY,
		const unsigned int uiMaxSplineParameters = 4,
		double maxValue = 0.0,
		const double maxError = 0,
		const double maxErrorPerValue = 0 );


	/**
	 * This function combines the given set of points to fib-objects,
	 * with the help of splies (polynoms with fixed number of parametes
	 * uiMaxSplineParameters) .
	 * For this the method @see nD1::cSpline::evalueSpline() will be used.
	 * Beware: You have to care that the created underobjects will be deleted
	 *
	 * uses @see nD1::cSpline::evalueSpline()
	 * The method should give the same result as
	 * createSplineItrFastBorderAreasForPoints() but faster and with less
	 * fib-elements.
	 * It will iterativ increase the number of parameters for the splines
	 * (from 1 to uiMaxNumberOfParameters).
	 *
	 * @param setMinimumArea the set with the datapoints to combine to
	 * 	fib-objects with the help of area and function elements;
	 * 	the created area should contain all of these points;
	 * 	The given points should be positions in an matrix, positions in
	 * 	the matrix but not given, will be considerd not to be in the area
	 * 	to create.
	 * @param setMaximumArea the set with the datapoints to combine to
	 * 	fib-objects with the help of area and function elements;
	 * 	the created area can contain these points;
	 * 	this set should contain all points from setMinimumArea;
	 * 	The given points should be positions in an matrix, positions in
	 * 	the matrix but not given, will be considerd not to be in the area
	 * 	to create.
	 * @param pUnderobject a pointer to the underobject, which the created
	 * 	fib-elements should contain and which should be evalued for the
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
	 * @return a fib-object with the created fib-underobjects, wher the
	 * 	given variables for the given pUnderobject will go over all
	 * 	point positions in the given set setPoints or NULL if non
	 * 	such could be created;
	 * 	some positions can be evalued twice;
	 * 	the fib-underobjects, wich evalue the most points, are on the
	 * 	front of the listobject (have a lower underobject number);
	 * 	if NULL is returnd, you have to care that pUnderobject will be
	 * 	deleted, else pUnderobject will be included in one
	 * 	underobject of the created listobject and the other underobject will
	 * 	contain copies of pUnderobject
	 * 	Structur of the created fib-object:
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
	cFibElement * createNSplineBorderAreasForPoints(
		const set< nD1::cDataPoint<tX, tX> > & setMinimumArea,
		const set< nD1::cDataPoint<tX, tX> > & setMaximumArea,
		cFibElement * pUnderobject,
		cFibVariable * pVariableDimX,
		cFibVariable * pVariableDimY,
		const unsigned int uiMaxSplineParameters = 4,
		set< nD1::cDataPoint<tX, tX> > * pOutSetMissingPoints = NULL,
		double maxValue = 0.0,
		const double maxError = 0.0,
		const double maxErrorPerValue = 0.0 );
	
#else //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
	
	/**
	 * This function combines the given set of points to fib-objects,
	 * with the help of splies (polynoms with fixed number of parametes
	 * uiMaxSplineParameters) .
	 * For this the method @see nD1::cSpline::evalueSpline() will be used.
	 * Beware: You have to care that the created underobjects will be deleted
	 *
	 * uses @see nD1::cSpline::evalueSpline()
	 * The method should give the same result as
	 * createSplineItrFastBorderAreasForPoints() but faster and with less
	 * fib-elements.
	 * It will iterativ increase the number of parameters for the splines
	 * (from 1 to uiMaxNumberOfParameters).
	 *
	 * @param setPoints the set with the datapoints to combine to
	 * 	fib-objects with the help of area and function elements;
	 * 	The given points should be positions in an matrix, positions in
	 * 	the matrix but not given, will be considerd not to be in the area
	 * 	to create.
	 * @param pUnderobject a pointer to the underobject, which the created
	 * 	fib-elements should contain and which should be evalued for the
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
	 * @return a fib-object with the created fib-underobjects, wher the
	 * 	given variables for the given pUnderobject will go over all
	 * 	point positions in the given set setPoints or NULL if non
	 * 	such could be created;
	 * 	some positions can be evalued twice;
	 * 	the fib-underobjects, wich evalue the most points, are on the
	 * 	front of the listobject (have a lower underobject number);
	 * 	if NULL is returnd, you have to care that pUnderobject will be
	 * 	deleted, else pUnderobject will be included in one
	 * 	underobject of the created listobject and the other underobject will
	 * 	contain copies of pUnderobject
	 * 	Structur of the created fib-object:
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
	cFibElement * createNSplineBorderAreasForPoints(
		const set< nD1::cDataPoint<tX, tX> > & setPoints,
		cFibElement * pUnderobject,
		cFibVariable * pVariableDimX,
		cFibVariable * pVariableDimY,
		const unsigned int uiMaxSplineParameters = 4,
		const unsigned int uiMinBitsToStoreMantissa = 1,
		double maxValue = 0.0,
		const double maxError = 0,
		const unsigned long ulMaxMemoryCost = 100000 );


	/**
	 * This function combines the given set of points to fib-objects,
	 * with the help of splies (polynoms with fixed number of parametes
	 * uiMaxSplineParameters) .
	 * For this the method @see nD1::cSpline::evalueSpline() will be used.
	 * Beware: You have to care that the created underobjects will be deleted
	 *
	 * uses @see nD1::cSpline::evalueSpline()
	 * The method should give the same result as
	 * createSplineItrFastBorderAreasForPoints() but faster and with less
	 * fib-elements.
	 * It will iterativ increase the number of parameters for the splines
	 * (from 1 to uiMaxNumberOfParameters).
	 *
	 * @param setMinimumArea the set with the datapoints to combine to
	 * 	fib-objects with the help of area and function elements;
	 * 	the created area should contain all of these points;
	 * 	The given points should be positions in an matrix, positions in
	 * 	the matrix but not given, will be considerd not to be in the area
	 * 	to create.
	 * @param setMaximumArea the set with the datapoints to combine to
	 * 	fib-objects with the help of area and function elements;
	 * 	the created area can contain these points;
	 * 	this set should contain all points from setMinimumArea;
	 * 	The given points should be positions in an matrix, positions in
	 * 	the matrix but not given, will be considerd not to be in the area
	 * 	to create.
	 * @param pUnderobject a pointer to the underobject, which the created
	 * 	fib-elements should contain and which should be evalued for the
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
	 * @return a fib-object with the created fib-underobjects, wher the
	 * 	given variables for the given pUnderobject will go over all
	 * 	point positions in the given set setPoints or NULL if non
	 * 	such could be created;
	 * 	some positions can be evalued twice;
	 * 	the fib-underobjects, wich evalue the most points, are on the
	 * 	front of the listobject (have a lower underobject number);
	 * 	if NULL is returnd, you have to care that pUnderobject will be
	 * 	deleted, else pUnderobject will be included in one
	 * 	underobject of the created listobject and the other underobject will
	 * 	contain copies of pUnderobject
	 * 	Structur of the created fib-object:
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
	cFibElement * createNSplineBorderAreasForPoints(
		const set< nD1::cDataPoint<tX, tX> > & setMinimumArea,
		const set< nD1::cDataPoint<tX, tX> > & setMaximumArea,
		cFibElement * pUnderobject,
		cFibVariable * pVariableDimX,
		cFibVariable * pVariableDimY,
		const unsigned int uiMaxSplineParameters = 4,
		set< nD1::cDataPoint<tX, tX> > * pOutSetMissingPoints = NULL,
		const unsigned int uiMinBitsToStoreMantissa = 1,
		double maxValue = 0.0,
		const double maxError = 0,
		const unsigned long ulMaxMemoryCost = 100000 );
	
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING

		
};//end namespace nD2
};//end namespace algorithms
};//end namespace fib

//include template implementation
#define ___N_D2_H_INCLUDE__
#include "../nD2/src/nD2.cpp"
#undef ___N_D2_H_INCLUDE__



#endif //___N_D2_H__
