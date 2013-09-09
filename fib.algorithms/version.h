/**
 * file name: version.h
 * @author Betti Oesterholz
 * @date 11.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains switches for the different fib -algorithms -versions.
 * Copyright (C) @c GPL3 2009 Betti Oesterholz
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
 *
 * This file contains the versionsinformation for the Fib 
 * -Multimedialanguage algorithms implementations.
 * This includes descriptions of declarations for versioned
 * programming switches.
 *
 */
/*
History:
11.06.2010  Oesterholz  created
11.09.2010  Oesterholz  FEATURE_REMOVE_TOPMOST_UNDEROBJECTS added
05.12.2010  Oesterholz  FEATURE_STORE_EVALUED_UNDEROBJECT_NUMBERS added
18.01.2011  Oesterholz  FEATURE_LINEAR_EQUIATION_PRECISION_FOR_NULL added
04.04.2011  Oesterholz  FEATURE_INEQUIATION_EVALUE_FAST and
	FEATURE_HYPERPLANE_BODY_OPTIMIZE_IS_PART_INEQUIATIONS added
09.04.2011  Oesterholz  FEATURE_HYPERPLANE_BODY_ADD_INEQUIATIONS_SAVE_ON_BIG_NUMBERS added
11.04.2011  Oesterholz  FEATURE_NCLUSTER_CLUSTER_IN_ONE_STEP added
17.04.2011  Oesterholz  FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_NO_DOUBLE_POINTS added
17.04.2011  Oesterholz  FEATURE_C_POLSNOM_EVALUE_SPLINE_GLPK_CHECK_ALL_SOLUTIONS added
*/


/**************************************
* Version Information
**************************************/

//Versionsinformation for the Fib Multimedialanguage
#define FIB_ALGORITHMS_VERSION          2
#define FIB_ALGORITHMS_VERSION_NAME     V0.1.1


/**************************************
* versioned programming switches
**************************************/


/**
 * With this feature the removeOverwrittenUnderObjects() function will
 * remove only the topmost overwritten underobjects.
 * @see  fib::algorithms::nReduceFibObject::removeOverwrittenUnderObjects()
 *
 * created: 11.09.2010  Betti Oesterholz
 * Status:  implemened and tested(05.12.2010)
 *//*
History:
*/
#define FEATURE_REMOVE_TOPMOST_UNDEROBJECTS


/**
 * With this feature the removeOverwrittenUnderObjects() function will
 * store the evalued underobject numbers
 * (@see cFibElment::getObjectPointsForElement()) and will not evalue
 * them again while reevaluing a point.
 * @see  fib::algorithms::nReduceFibObject::removeOverwrittenUnderObjects()
 * @see  fib::algorithms::nReduceFibObject::nRemoveOverwrittenUnderObjects::cEvalueUnderObjects::evalueElement()
 * @see  fib::algorithms::nReduceFibObject::nRemoveOverwrittenUnderObjects::cEvalueUnderObjects::mapLiUnderobjects
 *
 * created: 05.12.2010  Betti Oesterholz
 * Status:  implemened and tested(05.12.2010)
 *//*
History:
*/
#define FEATURE_STORE_EVALUED_UNDEROBJECT_NUMBERS


/**
 * With this feature the addition of to equiations values will be 0,
 * if the negative of one values is allmost equal to the other value.
 * In this way the precision of the variable values is not relevant.
 * @see fib::algorithms::nLinearEquation::cLinearEquation<tFactors>::operator+( const  cLinearEquation<tFactors> & equiation )
 *
 * created: 17.01.2011  Betti Oesterholz
 * Status:  implemened and tested(17.01.2011)
 *//*
History:
*/
#define FEATURE_LINEAR_EQUIATION_PRECISION_FOR_NULL


/**
 * With this feature the method toFibUnderFunction() of the nD1::cPolynom
 * class will convert the polynom to an fub underfunction polynom in the
 * horn scheme form.
 * @see fib::algorithms::nD1::cPolynom<tX, tY>::toFibUnderFunction()
 *
 * created: 10.03.2011  Betti Oesterholz
 * Status:  implemened and tested(10.03.2011)
 *//*
History:
*/
#define FEATURE_ND1_POLYNOM_TO_HORN_SCHEMA_FIB_UNDERFUNCTION


/**
 * With this feature the methods for evaluing an inequiation won't use the
 * slower add and sub functions from fibDatatyps.h .
 * @see fib::algorithms::nLinearInequation::cInequation<tFactors>::evalue()
 * @see fib::algorithms::nLinearInequation::cInequation<tFactors>::evalueValue()
 * Beware: If you comment FEATURE_INEQUIATION_EVALUE_FAST out you will get
 * 	more errors with tHyperplaneBody.
 *
 * created: 04.04.2011  Betti Oesterholz
 * Status:  implemened and tested(04.04.2011)
 *//*
History:
*/
#define FEATURE_INEQUIATION_EVALUE_FAST


/**
 * With this feature the isPart() method will optimize the inequiations
 * when evaluing if a point is part of the body.
 * The first inequiation found, which the point dos not fulfill, will be
 * put to the front of the inequiation list, so its checked as the first
 * inequiation in the next isPart() call.
 * @see fib::algorithms::nDn::cHyperplaneBody<tFactors>::isPart()
 *
 * created: 04.04.2011  Betti Oesterholz
 * Status:  implemened and tested(04.04.2011)
 *//*
History:
*/
#define FEATURE_HYPERPLANE_BODY_OPTIMIZE_IS_PART_INEQUIATIONS


/**
 * With this feature the addInequiation() method will also work on big
 * hyperpbodies.
 * Without the feature addInequiation() will work faster, but produce
 * errors on big hyper bodys (don't use a to big maxValue when
 * intitializing the cHyperplaneBody).
 * @see fib::algorithms::nDn::cHyperplaneBodySimple<tFactors>::addInequiation()
 * TODO: feature did not work correct
 * 	(? not needed with feature FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING)
 *
 * created: 09.04.2011  Betti Oesterholz
 * Status:  implemened
 *//*
History:
*/
//#define FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_SAVE_ON_BIG_NUMBERS



/**
 * With this feature the cluster() function of nCluster will create the
 * mapping for the cluster in one step.
 * This will save memmory and time.
 * @see fib::algorithms::nCluster::cluster()
 *
 * created: 11.04.2011  Betti Oesterholz
 * Status:  implemened and tested(11.04.2011)
 *//*
History:
*/
#define FEATURE_NCLUSTER_CLUSTER_IN_ONE_STEP

/**
 * With this feature the addInequiation() function of the class
 * cHyperplaneBodySimple will remove double points wich are.
 * Ther will allways just one point, which is contained in specific set of
 * hyperplanes.
 * This will save memmory and time.
 * @see fib::algorithms::nDn::cHyperplaneBodySimple<tFactors>::addInequiation()
 *
 * created: 17.04.2011  Betti Oesterholz
 * Status:  implemened and tested(17.04.2011)
 *//*
History:
*/
#define FEATURE_HYPERPLANE_BODY_SIMPLE_ADD_INEQUIATIONS_NO_DOUBLE_POINTS


/**
 * With this feature the glp library (extern package) linear solver will be
 * used to find a spline for a vector of range data points.
 *
 * @see fib::algorithms::nD1::cSpline<tX, tY>::evalueSplineIterativFast()
 *
 * created: 16.09.2012  Betti Oesterholz
 * Status:  implemened and tested(13.10.2012)
 *//*
History:
*/
#define FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING


/**
 * With this feature the glp library (extern package) linear solver will be
 * used with a mutex switch, so it can run in treads.
 * If the glp libary is tread save this feature can be deactivated.
 * Make sure to include mutexGlpkSolver.inc .
 *
 * @see mutexGlpkSolver.inc
 * @see FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
 * @see fib::algorithms::nD1::cSpline<tX, tY>::evalueSplineIterativFast()
 *
 * created: 26.09.2012  Betti Oesterholz
 * Status:  implemened and tested(13.10.2012)
 *//*
History:
*/
#define FEATURE_GLPK_USE_MUTEX_LINAR_PROBLEM_SOLVING


/**
 * With this feature all (defined) solutions will be checked (even
 * infeasible, no feasible and unbounded).
 * If the glp linear solver returns a not feasible solution, its error
 * could be still OK.
 *
 * @see FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
 * @see fib::algorithms::nD1::cSpline<tX, tY>::evalueSplineIterativFast()
 *
 * created: 28.06.2013  Betti Oesterholz
 * Status:  implemened (28.06.2013 don't know if usefull)
 *//*
History:
*/
//#define FEATURE_C_POLSNOM_EVALUE_SPLINE_GLPK_CHECK_ALL_SOLUTIONS



