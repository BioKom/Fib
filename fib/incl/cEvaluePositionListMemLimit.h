/**
 * @class cEvaluePositionListMemLimit
 * file name: cEvaluePositionListMemLimit.h
 * @author Betti Oesterholz
 * @date 30.04.2010
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
 */
/*
History:
30.04.2010  Oesterholz  created
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

class cEvaluePositionListMemLimit: public cEvaluePositionList{
public:

	
	/**
	 * The number of positions, which should be added to the positionslist,
	 * befor it is sorted and reduced.
	 * If this bounderie is reached, the list with the positions and ther
	 * properties will be sorted.
	 *
	 * @see ulNewPositionsInserted
	 * @see sortPositionsData()
	 */
	unsigned long long ulMaximalPointsAddToList;
	
	/**
	 * The number of points inserted after the last @see sortPositionsData()
	 * call because of @see ulMaximalPointsAddToList .
	 *
	 * @see ulMaximalPointsAddToList
	 */
	unsigned long long ulNewPositionsInserted;

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
	 * standardconstructor
	 *
	 * @param ulInMaximalPointsAddToList The number of positions, which
	 * 	should be added to the positionslist, befor it is sorted and
	 * 	reduced. (@see ulMaximalPointsAddToList)
	 * @param pInVecDomainDimension The dimension domain for the positions.
	 * 	No position outside this domain will be added.
	 * 	If NULL no check will be executed. (@see pVecDomainDimension)
	 * @param bInDeleteEmptyPoints if true points without properties will be
	 * 	deleted when the positionslist is reduced, else (if false) points
	 * 	without properties won't be deleted (@see bDeleteEmptyPoints)
	 */
	cEvaluePositionListMemLimit( unsigned long long ulInMaximalPointsAddToList,
		const cDomainVectorBasis * pInVecDomainDimension = NULL,
		bool bInDeleteEmptyPoints=true );
	
	/**
	 * copyconstructor
	 *
	 * @param evaluePositionListMemLimit the cEvaluePositionListMemLimit
	 * 	object to copy
	 */
	cEvaluePositionListMemLimit( const cEvaluePositionListMemLimit & evaluePositionListMemLimit );
	
	/**
	 * destructor
	 */
	virtual ~cEvaluePositionListMemLimit();

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


};//class cEvaluePositionListMemLimit

};

#endif


