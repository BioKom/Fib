/**
 * @file cOp2DFibFindSimilarAreaNSplineMax4BorderItrFastOrg
 * file name: cOp2DFibFindSimilarAreaNSplineMax4BorderItrFastOrg.h
 * @author Betti Oesterholz
 * @date 06.03.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This Operator evalues the areas with the same properties and combines
 * n to an complex fib -underobject.
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
 * Evalues the areas with the same properties in the original fib -object
 * and combines n random to an complex fib -underobject.
 * This is done with the help of area- and functionelements.
 * The area borders are approximated with the help of splines with maximal
 * 4 parameters.
 * In an last step it removes from the created fib -object all underobjects
 * which point properties are overwritten and so not necessary.
 * The number n is random choosen betwean 1 and log( Datapoints ) .
 * Smaler numbers will be prevered.
 *
 * This operator uses the @see nD2::createSplineItrFastBorderAreasForPoints()
 * method to create the area border splines.
 *
 * @see cOperationFib
 * @see cOperation
 * @see cEnviroment
 */
/*
History:
06.03.2011  Oesterholz  created
*/


#ifndef ___C_OP_2D_FIB_FIND_SIMILAR_AREA_N_SPLINE_MAX_4_BORDER_ITR_FAST_ORG_H__
#define ___C_OP_2D_FIB_FIND_SIMILAR_AREA_N_SPLINE_MAX_4_BORDER_ITR_FAST_ORG_H__

#include "version.h"

#include "cOperationFib.h"

#include <string>


namespace enviroment{
namespace fib{


class cOp2DFibFindSimilarAreaNSplineMax4BorderItrFastOrg: public cOperationFib{
public:

	/**
	 * The standardconstructor for the operation.
	 * It will create the operation, but won't start it.
	 *
	 * @param operationId the identifer for the operation
	 */
	cOp2DFibFindSimilarAreaNSplineMax4BorderItrFastOrg( const cOperationIdentifier & operationId );

	/**
	 * Destructor of the class cOp2DFibFindSimilarAreaNSplineMax4BorderItrFastOrg.
	 */
	virtual ~cOp2DFibFindSimilarAreaNSplineMax4BorderItrFastOrg();

	/**
	 * This method creats a new instance of this operator.
	 * Beware: You have to delete the instance after usage.
	 *
	 * @param operationId the identifer for the operation
	 * @return a pointer to a new instance of this operation
	 */
	virtual cOp2DFibFindSimilarAreaNSplineMax4BorderItrFastOrg * createInstance( const cOperationIdentifier & operationId ) const;

	/**
	 * This method runs the operation.
	 * It will wait till the operation is ended befor returning.
	 * Beware: If overwriten call setIsRunning( false ), when the operation
	 * is done.
	 *
	 * @see start()
	 * @see stop()
	 * @see setIsRunning()
	 * @return true if the operation was started
	 */
	virtual bool run();
	
	/**
	 * @return the (class-)name of the operation
	 */
	virtual std::string getName() const;

	/**
	 * This function compares two property elemente pairs.
	 * It is used for ordering property elemente pairs.
	 *
	 * @param paPropertyElement1 the first property elemente pair to compare
	 * @param paPropertyElement2 the second property elemente pair to compare
	 * @return true if the propertietype of the first pair is lower or,
	 * 	if the propertietyps are equal, if the second element number of the
	 * 	first pair is lower
	 */
	static bool lowerPropertyElement(
		const pair< cTypeProperty, unsignedIntFib > & paPropertyElement1,
		const pair< cTypeProperty, unsignedIntFib > & paPropertyElement2 );

protected:
	
	/**
	 * @param dValue the value for which to check, if it is 0
	 * @return true if the given value is 0, else false
	 */
	static bool isNull( const double & dValue );

};//end class cOp2DFibFindSimilarAreaNSplineMax4BorderItrFastOrg


};//end namespace fib
};//end namespace enviroment

#endif //___C_OP_2D_FIB_FIND_SIMILAR_AREA_N_SPLINE_MAX_4_BORDER_ITR_FAST_ORG_H__







