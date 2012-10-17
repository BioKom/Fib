/**
 * @class cEvaluePositionListLimit
 * file name: cEvaluePositionListLimit.h
 * @author Betti Oesterholz
 * @date 02.09.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the class for evaluing fib -objects and storing
 * the evalued data into a list.
 * Copyright (C) @c LGPL3 2010 Betti Oesterholz
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
 * This file contains the class for evaluing fib -objects and storing
 * the evalued data into a list (@see liEvaluedPositionData).
 * When the fib -object is evalued this method is called every time a
 * pointelement is reached. The parameter for the method are the
 * positionsvector of the point and properties of the point.
 * This class sorts and reduces the evalued positionslist every
 * @see ulMaximalPointsAddToList calls of the method evaluePosition().
 * Allso no position outside the dimension bounderies will be added.
 *
 * This class restricts the memory and time used to evalue and store the
 * evalued positionsdata.
 */
/*
History:
02.09.2010  Oesterholz  created
*/

#ifndef ___C_EVALUE_POSITION_LIST_MEM_LIMIT__
#define ___C_EVALUE_POSITION_LIST_MEM_LIMIT__

#include "version.h"

#include "cEvaluePositionList.h"

#include "cVectorPosition.h"
#include "cVectorProperty.h"
#include "cDomainVectorBasis.h"


#include <list>


using std::list;

namespace fib{

class cEvaluePositionListLimit: public cEvaluePositionList{
public:

	
	/**
	 * The number of positions, which should be added to the positionslist,
	 * befor it is sorted and reduced.
	 * If this bounderie is reached, the list with the positions and ther
	 * properties will be sorted.
	 *
	 * @see ulNewPositionsInsertedAfterLastSort
	 * @see sortPositionsData()
	 */
	unsigned long long ulSortEverAddedPointsList;
	
	/**
	 * The number of points inserted after the last @see sortPositionsData()
	 * call because of @see ulSortEverAddedPointsList .
	 *
	 * @see ulSortEverAddedPointsList
	 */
	unsigned long long ulNewPositionsInsertedAfterLastSort;
	
	
	/**
	 * The dimension domain for the positions.
	 * No position outside this domain will be added.
	 * If NULL no check will be executed.
	 */
	cDomainVectorBasis * pVecDomainDimension;

	/**
	 * If true points without properties will be deleted when the
	 * positionslist is reduced, else (if false) points without properties
	 * won't be deleted.
	 */
	bool bDeleteEmptyPoints;

	/**
	 * The maximum number of points in the (sorted) list of the points
	 * evalued (@see liEvaluedPositionData); if the sorted list
	 * @see liEvaluedPositionData has more than ulInMaxPointsInList
	 * point, the evalue call will return false.
	 * If ulInMaxPointsInList is 0 this option is deactivated (no check
	 * will be executed).
	 */
	unsigned long long ulMaxPointsInList;
	
	/**
	 * The maximum number of calls in the @see evaluePosition() will be
	 * called befor it returns false; if the evaluePosition() was called
	 * more than ulInMaxEvalueCalls times, it will return false.
	 * If ulInMaxEvalueCalls is 0 this option is deactivated (no check
	 * will be executed). (@see ulMaxEvalueCalls)
	 *
	 * @see ulEvalueCalls
	 */
	unsigned long long ulMaxEvalueCalls;
	
	/**
	 * The count how much the evaluePosition() method was called.
	 *
	 * @see ulMaxEvalueCalls
	 */
	unsigned long long ulEvalueCalls;
	
	
	/**
	 * standardconstructor
	 *
	 * @param ulInSortEverAddedPointsList The number of positions, which
	 * 	should be added to the positionslist, befor it is sorted and
	 * 	reduced. (@see ulSortEverAddedPointsList) If 0 this option is
	 * 	deactivated (no check will be executed).
	 * @param pInVecDomainDimension The dimension domain for the positions.
	 * 	No position outside this domain will be added.
	 * 	If NULL no check will be executed. (@see pVecDomainDimension)
	 * @param bInDeleteEmptyPoints if true points without properties will be
	 * 	deleted when the positionslist is reduced, else (if false) points
	 * 	without properties won't be deleted (@see bDeleteEmptyPoints)
	 * @param ulInMaxPointsInList the maximum number of points in the (sorted)
	 * 	list of the points evalued (@see liEvaluedPositionData); if the
	 * 	sorted list @see liEvaluedPositionData has more than ulInMaxPointsInList
	 * 	point, the evalue call will return false;
	 * 	If ulInMaxPointsInList is 0 this option is deactivated (no check
	 * 	will be executed). (@see ulMaxPointsInList)
	 * @param ulInMaxEvalueCalls the maximum number of calls in the
	 * 	@see evaluePosition() will be called befor it returns false; if the
	 * 	evaluePosition() was called more than ulInMaxEvalueCalls times, it
	 * 	will return false;
	 * 	If ulInMaxEvalueCalls is 0 this option is deactivated (no check
	 * 	will be executed). (@see ulMaxEvalueCalls)
	 */
	cEvaluePositionListLimit( const unsigned long long ulInSortEverAddedPointsList = 0,
		const cDomainVectorBasis * pInVecDomainDimension = NULL,
		const bool bInDeleteEmptyPoints = true,
		const unsigned long long ulInMaxPointsInList = 0,
		const unsigned long long ulInMaxEvalueCalls = 0 );
	
	/**
	 * copyconstructor
	 *
	 * @param evaluePositionListMemLimit the cEvaluePositionListLimit
	 * 	object to copy
	 */
	cEvaluePositionListLimit( const cEvaluePositionListLimit & evaluePositionListMemLimit );
	
	/**
	 * destructor
	 */
	virtual ~cEvaluePositionListLimit();

	/**
	 * The method with wich the evalued points with ther properties are
	 * inserted. Everytime a point (to evalue) is reached in the
	 * evaluation, this method is called with the position and the
	 * properties of the point and stores the copies of this data
	 * to the end of the list @see liEvaluedPositionData .
	 *
	 * @see liEvaluedPositionData
	 * @param vPosition the position of the point, which is evalued
	 * @param vProperties a list of the properties of the point
	 */
	virtual bool evaluePosition( const cVectorPosition & vPosition,
		const list<cVectorProperty> & vProperties );


};//class cEvaluePositionListLimit

};

#endif


