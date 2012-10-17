/**
 * @file cHyperplane
 * file name: cHyperplane.cpp
 * @author Betti Oesterholz
 * @date 03.01.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements a class for a hyperplane.
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
 * This class represents an hyperplane.
 * It is represented in the form:
 * 	Y = B + D_1 * x_1 + D_2 * x_2 + ... + D_d * x_d
 * 	- Y is the output vector
 * 	- B point on the hyperplane as the base vector
 * 	- D_i are the (independent) hyperplane direction vectors
 * 	- x_i are the scalar input factors
 * 	- d is the dimensionality of the hyperplane
 *
 * Of this formular only the direction vectors D_i and the base vector B
 * are stored in this class.
 *
 */
/*
History:
03.01.2010  Oesterholz  created
*/

#ifndef ___C_HYPERPLANE_CPP__
#define ___C_HYPERPLANE_CPP__


#include "version.h"

#include "fibDatatyps.h"

#include "cHyperplane.h"
#include "nLinearEquation.h"

#include <list>
#include <set>

#ifdef DEBUG
#include <iostream>
#endif//DEBUG


using namespace fib;
using namespace fib::algorithms::nDn;
using namespace fib::algorithms::nLinearEquation;
using namespace fib::algorithms::nLinearInequation;


/**
 * standardconstructor
 */
template <class tFactors> cHyperplane<tFactors>::cHyperplane():
		fillType( NONE ){
	//nothing to do
}

/**
 * parameterconstructor
 *
 * @param vecInBase the base vector (B) for the hyperplane @see vecBase
 * @param vecInDirections the direction vectors (D_i) for the
 * 	hyperplane @see vecDirections
 */
template <class tFactors> cHyperplane<tFactors>::cHyperplane(
		const vector< tFactors > & vecInBase,
		const vector< vector< tFactors > > & vecInDirections ):
		vecBase( vecInBase ), fillType( SOME ),
		bDirectionsLinearIndependent( false ), bInFormOne( false ){
	
	//add the directions
	addDirections( vecInDirections );
}


/**
 * parameterconstructor
 * The number of dimensions will be the number of factors in the
 * inequation.
 *
 * @param inequation the inequation which defines this hyperplane;
 * 	if the inequal sign of the inequation would be replaced by an
 * 	equal sign, all points which fulfill the equation are on the
 * 	hyperplane
 */
template <class tFactors> cHyperplane<tFactors>::cHyperplane(
		const cInequation< tFactors > & inequation ){
		
	createHyperplaneFromInequiation( inequation, inequation.vecFactors.size() );
}


/**
 * parameterconstructor
 *
 * @param inequation the inequiation which defines this hyperplane;
 * 	if the inequal sign of the inequation would be replaced by an
 * 	equal sign, all points which fulfill the equiation are on the
 * 	hyperplane
 * @param uiInNumberOfDimensions the number of dimensions the hyperplane
 * 	should be placed in
 */
template <class tFactors> cHyperplane<tFactors>::cHyperplane(
		const nLinearInequation::cInequation< tFactors > & inequation,
		unsigned int uiInNumberOfDimensions ){
		
	createHyperplaneFromInequiation( inequation, uiInNumberOfDimensions );
}


/**
 * @return the base of this hyperplane (@see vecBase)
 */
template <class tFactors> vector< tFactors > cHyperplane<tFactors>::getBase() const{
	
	if ( fillType == SOME ){
		return vecBase;
	}//else
	return vector< tFactors >();
}


/**
 * This method sets the base of this hyperplane to the given vecInBase.
 * @see vecBase
 *
 * @param vecInBase the base this hyperplane should have
 */
template <class tFactors> void cHyperplane<tFactors>::setBase(
		const vector< tFactors > & vecInBase ){
	
	if ( fillType == NONE ){
		fillType = SOME;
	}//else
	if ( vecInBase.size() == vecBase.size() ){
		vecBase = vecInBase;
		return;
	}//else
	if ( vecInBase.size() < vecBase.size() ){
		//enlarge the input vector
		const unsigned int uiNumberOfDimensions =
			vecBase.size();
		vecBase = vecInBase;
		vecBase.resize( uiNumberOfDimensions, (tFactors)(0.0) );
		return;
	}/*else vecBase.size() < vecInBase.size()
	-> enlarge all vectors of this hyperplane*/
	vecBase = vecInBase;
	
	for ( typeItrDirection itrActualDirection = vecDirections.begin();
			itrActualDirection != vecDirections.end(); itrActualDirection++ ){
		
		itrActualDirection->resize( vecInBase.size(), (tFactors)(0.0) );
	}
	bInFormOne = false;
}


/**
 * This method returns the uiDirection'th direction vector of this hyperplane.
 * @see vecDirections
 *
 * @param uiDirection the number of the direction vector to return
 * 	(counting begins with 1)
 * @return the uiDirection'th direction vector of this hyperplane or
 * 	a vector with no elements, if no such direction exists
 */
template <class tFactors> vector< tFactors > cHyperplane<tFactors>::
		getDirection( const unsigned int uiDirection ) const{
	
	if ( ( 1 <= uiDirection ) && ( uiDirection <= vecDirections.size() ) ){
		
		return vecDirections[ uiDirection - 1 ];
	}
	return vector< tFactors >();
}


/**
 * @return a vector with all direction vectors of this hyperplane
 * 	(@see vecDirections)
 */
template <class tFactors> vector< vector< tFactors > > cHyperplane<tFactors>::
		getDirections() const{
	
	if ( fillType == SOME ){
		return vecDirections;
	}//else
	return vector< vector< tFactors > >();
}


/**
 * @return the number of direction vectors of this hyperplane
 * 	(@see vecDirections); if the direction vectors are linear
 * 	independent the returned value is also the dimensionality of
 * 	this hyperplane
 */
template <class tFactors> unsigned int
		cHyperplane<tFactors>::getNumberOfDirections() const{
	
	if ( fillType == SOME ){
		return vecDirections.size();
	}//else
	return 0;
}


/**
 * This method adds the given direction vector vecInDirection to this
 * hyperplane.
 * @see vecDirections
 *
 * @param vecInDirection the direction vector to add
 * @return true if the direction was added else false
 */
template <class tFactors> bool cHyperplane<tFactors>::addDirection(
		const vector< tFactors > & vecInDirection ){
	
	if ( fillType == NONE ){
		fillType = SOME;
	}//else
	//check if the given direction is a valid direction vector
	bool bJustNullElements = true;
	for ( unsigned int uiActualElement = 0;
			uiActualElement < vecInDirection.size(); uiActualElement++ ){
		if ( vecInDirection[ uiActualElement ] != (tFactors)(0) ){
			//this is not an nullvector -> so don't remove it because it is one
			bJustNullElements = false;
			break;
		}
	}
	if ( bJustNullElements ){
		return false;
	}
	//insert direction vector
	bInFormOne = false;
	bDirectionsLinearIndependent = false;
	
	if ( vecInDirection.size() <= vecBase.size() ){
		
		vecDirections.push_back( vecInDirection );
		
		if ( vecInDirection.size() < vecBase.size() ){
			//enlarge the input vector
			vecDirections.back().resize( vecBase.size(), (tFactors)(0.0) );
			return true;
		}
		return true;
	}/*else vecBase.size() < vecInDirection.size()
	-> enlarge all vectors of this hyperplane*/
	vecBase.resize( vecInDirection.size(), (tFactors)(0.0) );
	
	for ( typeItrDirection itrActualDirection = vecDirections.begin();
			itrActualDirection != vecDirections.end(); itrActualDirection++ ){
		
		itrActualDirection->resize( vecInDirection.size(), (tFactors)(0.0) );
	}
	vecDirections.push_back( vecInDirection );
	return true;
}


/**
 * This method adds the given direction vectors vecInDirections to this
 * hyperplane.
 * @see vecDirections
 *
 * @param vecInDirections the direction vectors to add
 * @return the number of inserted direction vectors
 */
template <class tFactors> unsigned int cHyperplane<tFactors>::addDirections(
		vector< vector< tFactors > > vecInDirections ){
	
	if ( vecInDirections.empty() ){
		//no vectors given -> non to insert
		return 0;
	}
	if ( fillType == NONE ){
		fillType = SOME;
	}//else
	
	size_t uiMaxDimensionInDirections = 0;
	bool bDimensionInDirectionsDifferent = false;
	
	for ( typeItrDirection itrActualDirection = vecInDirections.begin();
			itrActualDirection != vecInDirections.end(); ){
		
		bool bJustNullElements = true;
		for ( unsigned int uiActualElement = 0;
				uiActualElement < itrActualDirection->size(); uiActualElement++ ){
			if ( (*itrActualDirection)[ uiActualElement ] != (tFactors)(0) ){
				//this is not an nullvector -> so don't remove it because it is one
				bJustNullElements = false;
				break;
			}
		}
		if ( bJustNullElements ){
			//no valid direction vector -> delete it
			itrActualDirection = vecInDirections.erase( itrActualDirection );
		}else{//the direction vector is valid
			if ( uiMaxDimensionInDirections != itrActualDirection->size() ){
				uiMaxDimensionInDirections = max(
					uiMaxDimensionInDirections, itrActualDirection->size() );
				bDimensionInDirectionsDifferent = true;
			}
			//check next input direction vector
			itrActualDirection++;
		}
	}
	if ( vecInDirections.empty() ){
		//no vectors remaining -> non to insert
		return 0;
	}
	bool bResizeInputDirections = false;
	if ( bDimensionInDirectionsDifferent ||
			(uiMaxDimensionInDirections < vecBase.size()) ){
		
		bResizeInputDirections = true;
	}
	
	if ( vecBase.size() < uiMaxDimensionInDirections ){
		/*enlarge all vectors of this hyperplane*/
		vecBase.resize( uiMaxDimensionInDirections, (tFactors)(0.0) );
		
		for ( typeItrDirection itrActualDirection = vecDirections.begin();
				itrActualDirection != vecDirections.end(); itrActualDirection++ ){
			
			itrActualDirection->resize( uiMaxDimensionInDirections, (tFactors)(0.0) );
		}
	}
	const unsigned int uiOldNumberOfDirections = vecDirections.size();
	//insert input directions
	bDirectionsLinearIndependent = false;
	bInFormOne = false;
	vecDirections.insert( vecDirections.end(),
		vecInDirections.begin(), vecInDirections.end() );
	
	if ( bResizeInputDirections ){
		//resize input directions
		const unsigned int uiNewNumberOfDirections = vecDirections.size();
		for ( unsigned int uiActualDimension = uiOldNumberOfDirections;
				uiActualDimension < uiNewNumberOfDirections; uiActualDimension++ ){
			
			vecDirections[ uiActualDimension ].resize( vecBase.size(), (tFactors)(0.0) );
		}
	}
	return vecInDirections.size();
}


/**
 * This method deletes the uiDirection'th direction vector of this hyperplane.
 * @see vecDirections
 *
 * @param uiDirection the number of the direction vector to delete
 * 	(counting begins with 1)
 * @return true if the uiDirection'th direction vector of this hyperplane
 * 	was deleted, else false
 */
template <class tFactors> bool cHyperplane<tFactors>::deleteDirection(
		unsigned int uiDirection ){
	
	if ( ( uiDirection < 1 ) || ( vecDirections.size() < uiDirection ) ){
		//no such direction vector
		return false;
	}
	//find direction vector
	typeItrDirection itrActualDirection = vecDirections.begin();
	for ( ;( itrActualDirection != vecDirections.end() ) && ( 1 < uiDirection );
			itrActualDirection++, uiDirection-- ){
		//nothing to do
	}
	vecDirections.erase( itrActualDirection );
	return true;
}



/**
 * @return the number of dimensions this hyperplane is contained in
 * 	(@see vecDirections, @see vecBase);
 * 	the number of dimensions of this hyperplane are the numbers of elements
 * 	in its vectors
 */
template <class tFactors> unsigned int cHyperplane<tFactors>::
		getNumberOfDimensions() const{

	return vecBase.size();
}


/**
 * This method sets the number of dimensions this hyperplane is contained in.
 * (@see vecDirections, @see vecBase);
 * The number of dimensions of this hyperplane are the numbers of elements in
 * its vectors.
 *
 * @param uiDimensionality the number of dimensions of this hyperplane
 * @return the number of dimensions of this hyperplane
 */
template <class tFactors> unsigned int cHyperplane<tFactors>::
		setNumberOfDimensions( unsigned int uiDimensionality ){
	
	if ( uiDimensionality == vecBase.size() ){
		//nothing to do the dimensionality is allready correct
		return vecBase.size();
	}//else enlarge all vectors of this hyperplane
	vecBase.resize( uiDimensionality, (tFactors)(0.0) );
	
	for ( typeItrDirection itrActualDirection = vecDirections.begin();
			itrActualDirection != vecDirections.end(); itrActualDirection++ ){
		
		itrActualDirection->resize( uiDimensionality, (tFactors)(0.0) );
	}
	
	return vecBase.size();
}


/**
 * This method will remove all not independent vectors from the
 * direction vectors (a_i). So that the remaining direction vectors
 * are linear undependent.
 */
template <class tFactors> void cHyperplane<tFactors>::
		makeDirectionsIndependent(){
	
	DEBUG_OUT_L2(<<"cHyperplane<tFactors>::makeDirectionsIndependent() begin, for hyperplane:"<<endl<<flush);
#ifdef DEBUG
	print( cout );
#endif//DEBUG
	//check if the directions are independant
	if ( bDirectionsLinearIndependent ){
		//direction vectors are allready linear independent
		DEBUG_OUT_L2(<<"cHyperplane<tFactors>::makeDirectionsIndependent() done bDirectionsLinearIndependent=true"<<endl<<flush);
		return;
	}
	
	if ( vecDirections.empty() ){
		DEBUG_OUT_L2(<<"cHyperplane<tFactors>::makeDirectionsIndependent() done no directions=true"<<endl<<flush);
		return;//no direction vectors ->nothing to do
	}
	//remove all not independent (from ther previos directions) directions
	typeItrDirection itrActualDirection = vecDirections.begin();
	unsigned int uiActualDirection = 0;//the index to the actual direction
	const unsigned int uiNumberOfDimensions = itrActualDirection->size();
	while ( itrActualDirection != vecDirections.end() ){
		
		DEBUG_OUT_L2(<<"Checking direction: "<<uiActualDirection<<endl<<flush);
		bool bRemoveDirection = true;
		//check if the actual direction has an element not 0
		for ( unsigned int uiActualElement = 0;
				uiActualElement < itrActualDirection->size(); uiActualElement++ ){
			if ( (*itrActualDirection)[ uiActualElement ] != (tFactors)(0) ){
				//this is not an nullvector -> so don't remove it because its one
				DEBUG_OUT_L2(<<"don't remove direction because an element is not 0 "<<endl<<flush);
				bRemoveDirection = false;
				break;
			}
		}
		if ( ( ! bRemoveDirection ) && ( uiActualDirection != 0 ) ){
			DEBUG_OUT_L2(<<"checking if independent "<<endl<<flush);
			//check if the actual direction is independent of its previos directions
			/*create linara equation system for all direction vectors till
			the actual, in the form:
				vecDirections[ 0 ] * x_0 + ... + vecDirections[ uiActualDirection - 1 ] *
				* x_{uiActualDirection - 1} = vecDirections[ uiActualDirection ]*/
			vector< cLinearEquation<tFactors> > vecOfEquiations;
			//create ab equation for every dimension
			for ( unsigned int uiDimension = 0;
					uiDimension < uiNumberOfDimensions; uiDimension++ ){
				
				cLinearEquation<tFactors> actualEquiation( uiActualDirection,
					(*itrActualDirection)[ uiDimension ] );
				//set the factors of the equation
				for ( unsigned int uiPreviosDirection = 0;
						uiPreviosDirection < uiActualDirection; uiPreviosDirection++ ){
					
					actualEquiation.vecFactors[ uiPreviosDirection ] =
						vecDirections[ uiPreviosDirection ][ uiDimension ];
				}
				vecOfEquiations.push_back( actualEquiation );
			}
			//check if linear equation system is solvable
			//create the triangle form of the created linear equation system
			const vector< cLinearEquation<tFactors> > vecOfEquiationsTriangle =
				crateDiagonalForm( vecOfEquiations );
			
			/*check if the last (uiNumberOfDimensions - uiActualDirection) equations
			have a constant wich is 0 (all factors of thes formulars will be
			0, so a constant not 0 would mean the equation is false);
			if all these constants are 0, the equation system is solvable
			-> the direction vectors are linear dependend with the actual
			direction vector
			-> remove the actual direction vector*/
			bRemoveDirection = true;
			for ( unsigned int uiActualEquiation = uiActualDirection;
					uiActualEquiation < uiNumberOfDimensions; uiActualEquiation++ ){
				
				if ( vecOfEquiationsTriangle[ uiActualEquiation ].constant !=
						((tFactors)(0)) ){
					/*this equation system is not solvable
					-> it is linear independent
					-> don't remove it*/
					DEBUG_OUT_L2(<<"vecOfEquiationsTriangle["<< uiActualEquiation <<"].constant = "<<vecOfEquiationsTriangle[ uiActualEquiation ].constant<<endl<<flush);
					bRemoveDirection = false;
					break;
				}
			}
			
		}//else remove nullvector
		if ( bRemoveDirection ){
			DEBUG_OUT_L2(<<"removing direction: "<<uiActualDirection<<endl<<flush);
			itrActualDirection = vecDirections.erase( itrActualDirection );
		}else{//check next direction
			itrActualDirection++;
			uiActualDirection++;
		}
	}
	bDirectionsLinearIndependent = true;
	DEBUG_OUT_L2(<<"cHyperplane<tFactors>::makeDirectionsIndependent() done, new hyperplane: "<<endl<<flush);
#ifdef DEBUG
	print( cout );
#endif//DEBUG
}


/**
 * This method will convert the given hyperplane into the form One form.
 * Form One is a special hyperplane form, wich is uniqe and simpler to handle.
 * Hyperplane form: Y = B + D_1 * x_1 + D_2 * x_2 + ... + D_d * x_d
 * In form One:
 * 	- B point on the hyperplane as the base vector, with |B| minimal
 * 	- D_i are the independent hyperplane direction vectors
 * 		D_i = ( h_i.1, ..., h_i.{o_i}, ..., h_i.d )^T
 * 		with h_i.1= ...= h_i.o_i - 1} = 0, h_i.{o_i} = 1 and
 * 		o_{i-1} < o_i, for 1 < i (o_{i-1} is for D_{i-1} )
 */
template <class tFactors> void cHyperplane<tFactors>::convertToFormOne(){
	
	DEBUG_OUT_L2(<<"cHyperplane<tFactors>::convertToFormOne() started; hyperplane:"<<endl<<flush);
#ifdef DEBUG
	print( cout );
#endif//DEBUG
	if ( bInFormOne ){
		//already in form One -> nothing to do
		DEBUG_OUT_L2(<<"cHyperplane<tFactors>::convertToFormOne() done, already in form One"<<endl<<flush);
		return;
	}
	if ( vecDirections.empty() ){
		//yust a point -> already in form One -> nothing to do
		DEBUG_OUT_L2(<<"cHyperplane<tFactors>::convertToFormOne() done, no directions"<<endl<<flush);
		bInFormOne = true;
		return;
	}
	makeDirectionsIndependent();
	
	/*create an equation system with every D_i to an equation E_i*/
	const unsigned int uiNumberOfDirections = getNumberOfDirections();
	const unsigned int uiNumberOfDimensions = getNumberOfDimensions();
	
	vector< cLinearEquation<tFactors> > vecOfEquiations( uiNumberOfDirections,
		cLinearEquation<tFactors>( uiNumberOfDimensions ) );
	
	//set the factors of the equation system
	for ( unsigned int uiActualDirection = 0;
			uiActualDirection < uiNumberOfDirections; uiActualDirection++ ){
		
		for ( unsigned int uiDimension = 0;
					uiDimension < uiNumberOfDimensions; uiDimension++ ){
			
			vecOfEquiations[ uiActualDirection ].vecFactors[ uiDimension ] =
				vecDirections[ uiActualDirection ][ uiDimension ];
		}
	}	
	
	//create the diagonal form of the equation system
	vector< cLinearEquation<tFactors> > vecOfEquiationsTriangle =
		crateDiagonalForm( vecOfEquiations );
	
	//transform the triangle form equiations E_i back to directions D_i
	for ( unsigned int uiActualDirection = 0;
			uiActualDirection < uiNumberOfDirections; uiActualDirection++ ){
		
		for ( unsigned int uiDimension = 0;
					uiDimension < uiNumberOfDimensions; uiDimension++ ){
			
			vecDirections[ uiActualDirection ][ uiDimension ] =
				vecOfEquiationsTriangle[ uiActualDirection ].vecFactors[ uiDimension ];
		}
	}
	
	/*evalue the base vector with miniam |B| (norm)
	this B is at right angle to all direction vectors ( B * D_i = 0 )
	and base vector B lays on the hyperplane
	( B = B_old + D_1 * x_1 + D_2 * x_2 + ... + D_d * x_d )*/
	//create linear equiation system for the base vector B
	DEBUG_OUT_L2(<<endl<<"Evalue base vector in one form:"<<endl<<flush);
	vector< cLinearEquation<tFactors> > vecOfBaseEquiations(
		uiNumberOfDimensions + uiNumberOfDirections,
		cLinearEquation<tFactors>( uiNumberOfDimensions + uiNumberOfDirections ) );
	
	unsigned int uiActualEquiation = 0;
	//add components: 0 = D_i * B
	for ( unsigned int uiActualDirection = 0;
			uiActualDirection < uiNumberOfDirections;
			uiActualDirection++ ){
		
		for ( unsigned int uiDimension = 0;
				uiDimension < uiNumberOfDimensions; uiDimension++ ){
			
			vecOfBaseEquiations[ uiActualEquiation ].vecFactors[ uiDimension ] =
				vecDirections[ uiActualDirection ][ uiDimension ];
		}
		uiActualEquiation++;
	}
	//add component: B_old  = B + D_1 * x_1 + D_2 * x_2 + ... + D_d * x_d
	for ( unsigned int uiDimension = 0;
				uiDimension < uiNumberOfDimensions;
				uiDimension++ ){
		
		vecOfBaseEquiations[ uiActualEquiation ].constant = vecBase[ uiDimension ];//B_old component
		//add B component

		vecOfBaseEquiations[ uiActualEquiation ].vecFactors[ uiDimension ] =
			((tFactors)(1));
		
		//add D_1 * x_1 + D_2 * x_2 + ... + D_d * x_d part
		for ( unsigned int uiActualDirection = 0;
				uiActualDirection < uiNumberOfDirections; uiActualDirection++ ){
			
			vecOfBaseEquiations[ uiActualEquiation ].vecFactors[ uiNumberOfDimensions + uiActualDirection ] =
				vecDirections[ uiActualDirection ][ uiDimension ];
		}
		uiActualEquiation++;
	}
	//create the diagonal form of the base vector equation system
	vector< cLinearEquation<tFactors> > vecOfEquiationsBaseTriangle =
		crateDiagonalForm( vecOfBaseEquiations );

	/*evalue the solution from the equiation number 0 till uiDimension*/
	for ( unsigned int uiDimension = 0;
			uiDimension < uiNumberOfDimensions; uiDimension++ ){
		
		vecBase[ uiDimension ] = vecOfEquiationsBaseTriangle[ uiDimension ].constant;
	}
	bInFormOne = true;
	
	DEBUG_OUT_L2(<<"cHyperplane<tFactors>::convertToFormOne() done, new hyperplane: "<<endl<<flush);
#ifdef DEBUG
	print( cout );
#endif//DEBUG
}


/**
 * This method evalues the intersection of the given hyperplane with
 * this hyperplan.
 * If no intersection exists NULL is returned.
 * Attention: You have to care, that the returned object is deleted.
 *
 * @param hyperplane the hyperplane, with wich this hyperplane should
 * 	be intersected
 * @return the intersection hyperplane of this and the given hyperplane
 * 	or NULL, if no intersection exists
 */
template <class tFactors> cHyperplane< tFactors > * cHyperplane<tFactors>::
		evalueIntersection( const cHyperplane< tFactors > & hyperplane ) const{
	/*every intersection of two hyperplanes will have a dimensionality d_i which
	is equal (d_i=d) to the hyperplane with the lowest dimensionality d (if this
	hyperplane is part of the other) or an dimensionality decrased (d_i<d)*/
	
	DEBUG_OUT_L2(<<"cHyperplane<tFactors>::evalueIntersection( hyperplane ) begin, for hyperplanes:"<<endl<<flush);
#ifdef DEBUG
	cout<<"this:"<<endl;
	print( cout );
	cout<<"hyperplane:"<<endl;
	hyperplane.print( cout );
#endif//DEBUG
	
	if ( fillType == NONE ){
		return NULL;
	}//else
	if ( fillType == ALL ){
		return new cHyperplane< tFactors >( hyperplane );
	}//else
	
	if ( this->vecDirections.empty() && hyperplane.vecDirections.empty() ){
		//two points
		if ( this->vecBase == hyperplane.vecBase ){
			//the to points are equal -> the intersection is (one of) the point
			return new cHyperplane< tFactors >( *this );
		}else{//no intersection
			return NULL;
		}
	}//else not two points
	//set both hyperplanes equal
	
	//evalue which hyperplane has lesser directions/dimensionality
	cHyperplane< tFactors > firstHyperplane;
	cHyperplane< tFactors > * pSecondHyperplane;//hyperplane with lesser directions
	
	if ( hyperplane.getNumberOfDirections() < this->getNumberOfDirections() ){
		//the given hyperplane has lesser directions
		firstHyperplane  = *this;
		pSecondHyperplane = new cHyperplane< tFactors >( hyperplane );
	}else{//this hyperplane has lesser directions
		firstHyperplane  = hyperplane;
		pSecondHyperplane = new cHyperplane< tFactors >( *this );
	}
	cHyperplane< tFactors > & secondHyperplane = *pSecondHyperplane;
	
	firstHyperplane.makeDirectionsIndependent();
	secondHyperplane.makeDirectionsIndependent();
	
	/*create equation system for the hyperplanes
	- firstHyperplane : Y_1 = B_1 + A_1 * z_1 + A_2 * z_2 + ... + A_d * z_d
	- secondHyperplane: Y_2 = B_2 + D_1 * x_1 + D_2 * x_2 + ... + D_d * x_d
	-> the evalued equiation system: Y_1 = Y_2
		B_1 + D_1 * x_1 + D_2 * x_2 + ... + D_d * x_d = B_2 + A_1 * z_1 + A_2 * z_2 + ... + A_d * z_d
		-> B_1 - B_2 = -A_1 * z_1 - A_2 * z_2 - ... - A_d * z_d + D_1 * x_1 + D_2 * x_2 + ... + D_d * x_d
	*/
	const unsigned int uiNumberOfFactors =
		firstHyperplane.getNumberOfDirections() + secondHyperplane.getNumberOfDirections();
	const unsigned int uiNumberOfDimensions = max(
		firstHyperplane.getNumberOfDimensions(), secondHyperplane.getNumberOfDimensions() );
	
	//the intersection is in the space of both hyperplanes
	firstHyperplane.setNumberOfDimensions( uiNumberOfDimensions );
	secondHyperplane.setNumberOfDimensions( uiNumberOfDimensions );
	
	vector< cLinearEquation<tFactors> > vecOfEquiations( uiNumberOfDimensions,
		cLinearEquation<tFactors>( uiNumberOfFactors ) );
	
	//set the factors of the equation system
	unsigned int uiActualFactor = 0;
	for ( typeConstItrDirection itrDirection = firstHyperplane.vecDirections.begin();
			itrDirection != firstHyperplane.vecDirections.end();
			itrDirection++, uiActualFactor++ ){
		
		for ( unsigned int uiDimension = 0;
					uiDimension < uiNumberOfDimensions; uiDimension++ ){
			
			vecOfEquiations[ uiDimension ].vecFactors[ uiActualFactor ] =
				((tFactors)(-1)) * (*itrDirection)[ uiDimension ];
		}
	}
	for ( typeConstItrDirection itrDirection = secondHyperplane.vecDirections.begin();
			itrDirection != secondHyperplane.vecDirections.end();
			itrDirection++, uiActualFactor++ ){
		
		for ( unsigned int uiDimension = 0;
					uiDimension < uiNumberOfDimensions; uiDimension++ ){
			
			vecOfEquiations[ uiDimension ].vecFactors[ uiActualFactor ] =
				(*itrDirection)[ uiDimension ];
		}
	}
	//set the constant of the hyperplane
	for ( unsigned int uiDimension = 0;
				uiDimension < uiNumberOfDimensions; uiDimension++ ){
		
		vecOfEquiations[ uiDimension ].constant = sub(
			firstHyperplane.vecBase[ uiDimension ], secondHyperplane.vecBase[ uiDimension ] );
	}
	
	/*evalue triangle form, with the hyperplane parameters of the
	hyperplane with lesser directions on the bottom*/
	vector< cLinearEquation<tFactors> > vecOfEquiationsTriangle =
		crateDiagonalForm( vecOfEquiations );
	
	/*find last equiation wher not all factors and the constant are 0:
	- if it isn't solvable -> no intersections
	- if a factor of the first hyperplane remains (this should be the last factor)
		-> the number of factors can't be reduced in the second hyperplane
		-> the second hyperplane is the intersection
	- else evalue the intersection by replacing one factor in the second
		hyperplane with the evalued (last) equiation (not 0)
	*/
#ifdef DEBUG
	cout<<"Actual equiations in triangle form:"<<endl;
	printEquations( vecOfEquiationsTriangle, cout );
#endif //DEBUG
	
	/*evalue all equiations with no factors of the first hyperplane, but some of the second*/
	
	unsigned int uiActualEquiation = 0;
	const cLinearEquation<tFactors> * pActualEquiation =
		&( vecOfEquiationsTriangle[ 0 ] );
	
	//find the last equiation wher not all factors and the constant are 0
	for ( uiActualEquiation = uiNumberOfDimensions - 1;
			0 < uiActualEquiation; uiActualEquiation-- ){
		
		if ( ! vecOfEquiationsTriangle[ uiActualEquiation ].isNull() ){
			//one factor or constant not 0 found
			pActualEquiation = &(vecOfEquiationsTriangle[ uiActualEquiation ]);
			break;
		}
	}
	if ( pActualEquiation->isNull() ){
		//Error: should never happen
		DEBUG_OUT_EL1(<<"Error: No equiations with factors not null found for intersection."<<endl<<flush);
		delete pSecondHyperplane;
		return NULL;
	}
	
	if ( ! pActualEquiation->isSolvebel() ){
		//if it isn't solvable -> no intersections
		DEBUG_OUT_L1(<<"Not solvebel equiation found -> no intersection"<<endl<<flush);
		delete pSecondHyperplane;
		return NULL;
	}//else the last equation is solvable
	
	unsigned int uiFirstFactorNotNull = 0;
	for ( unsigned int uiActualFactor = 0;
			uiActualFactor < uiNumberOfFactors; uiActualFactor++ ){
		
		if ( ! isEqualNull( pActualEquiation->vecFactors[ uiActualFactor ] ) ){
			//one factor not 0 found
			uiFirstFactorNotNull = uiActualFactor;
			break;
		}
	}
	if( uiFirstFactorNotNull < firstHyperplane.getNumberOfDirections() ){
		/*if a factor of the first hyperplane remains (this should be the last factor)
		-> the number of factors can't be reduced in the second hyperplane
		-> the second hyperplane is the intersection*/
		DEBUG_OUT_L2(<<"The second hyperplane is the intersection."<<endl<<flush);
		pSecondHyperplane->convertToFormOne();
		return pSecondHyperplane;
	}
	/*else some factors are not 0*/
	/*vector with the equiations with just factors of the second
	hyperplane and a constant;
	the element pairs are:
		- first: the equiation index of the equiation not null in the equiation system
		- second: first the factor not null in the equiation (the vactor will be 1)*/
	list< pair< unsigned int, unsigned int > > liPaEquiationFactors;
	liPaEquiationFactors.push_back( pair< unsigned int, unsigned int >(
		uiActualEquiation, uiFirstFactorNotNull ) );
	
	const unsigned int uiNumberOfDirectionsInFirstHyperplane =
		firstHyperplane.getNumberOfDirections();
	
	/*This is the index of the first factor, which is not in single in its row*/
	const unsigned int uiFirstFactorNotSingle = uiFirstFactorNotNull + 1;
	/*This is the index of the first factor, which in a equiation with just
	factors for the second hyperplane*/
	unsigned int uiFirstFactorSingle = uiFirstFactorNotNull;
	
	unsigned int uiFirstFactorNotNullLastFound = uiFirstFactorNotNull;
	
	while ( 0 < uiActualEquiation ){
		
		uiActualEquiation--;
		
		pActualEquiation = &(vecOfEquiationsTriangle[ uiActualEquiation ]);
		for ( unsigned int uiActualFactor = 0;
				uiActualFactor < uiNumberOfFactors; uiActualFactor++ ){
			
			if ( ! isEqualNull( pActualEquiation->vecFactors[ uiActualFactor ] ) ){
				//one factor not 0 found
				uiFirstFactorNotNull = uiActualFactor;
				break;
			}
		}
		if( uiFirstFactorNotNull < uiNumberOfDirectionsInFirstHyperplane ){
			/*if a factor of the first hyperplane remains (this should be the last factor)
			-> don't evalue more factors*/
			DEBUG_OUT_L2(<<"No more factors to reduce directions"<<endl<<flush);
			break;
		}
		if ( uiFirstFactorNotNullLastFound  <= uiFirstFactorNotNull ){
			DEBUG_OUT_L2(<<"No new factor to reduce directions; last factor: "<<uiFirstFactorNotNullLastFound<<" actual factor: "<<uiFirstFactorNotNull<<endl<<flush);
			continue;
		}
		uiFirstFactorSingle = uiFirstFactorNotNull;
		liPaEquiationFactors.push_back( pair< unsigned int, unsigned int >(
			uiActualEquiation, uiFirstFactorNotNull ) );
	}
	
	/*evalue the intersection:
	for every equiation with just factors of the second hyperplane and a
	constant (@see liPaEquiationFactors);
	- the factors are all from the second (with lesser directions) hyperplane
	- evalue how one factor (the uiFirstFactorNotNull'th) depends on the
		others and replace him by this term
	The hyperplane h_l with the lesser dimensionality will be in the form:
		Y = B + D_1 * x_1 + D_2 * x_2 + ... + D_d * x_d
		(D_1 = first the factor not null)
	The last equation will have the form:
		constant = a_1 * x_1 + a_2 * x_2 + ... + a_d * x_d
		(a_1 = 1 , because of the triangle form)
	It can be reformed to:
		x_1 = constant - a_2 * x_2 - ... - a_d * x_d
	With this equiation the x_1 in the hyperplane h_l will be replaced:
		Y = B + D_1 * (constant - a_2 * x_2 - ... - a_d * x_d) +
			+ D_2 * x_2 + ... + D_d * x_d
		-> Y = (B + D_1 * constant) + (D_2 - D_1 * a_2) * x_2 + ... +
			+ (D_d - D_1 * a_d) * x_d
	This is the intersection hyperplane formular.
	The Basefactor BI of the intersection hyperplane is:
		BI = (B + constant * D_1)
	The direction vectors DI_i of the intersection hyperplane are:
		DI_i = D_i - a_i * D_1
	*/
	const unsigned int uiNumberOfOldDirections =
		secondHyperplane.vecDirections.size();
	const unsigned int uiFirstDirectionForNonTriangleFactor =
		 uiFirstFactorNotSingle - uiNumberOfDirectionsInFirstHyperplane;
	
	DEBUG_OUT_L2(<<"ther are "<<liPaEquiationFactors.size()<<" directions to reduce"<<endl<<flush);
	for ( list< pair< unsigned int, unsigned int > >::const_iterator
			itrEquiation = liPaEquiationFactors.begin();
			itrEquiation != liPaEquiationFactors.end(); itrEquiation++ ){
		
		pActualEquiation = &(vecOfEquiationsTriangle[ itrEquiation->first ]);
		const unsigned int uiDirectionForFactorNotNull =
			itrEquiation->second - uiNumberOfDirectionsInFirstHyperplane;
		
		DEBUG_OUT_L2(<<"reducing direction "<<uiDirectionForFactorNotNull<<" with factor "<<itrEquiation->second<<" in the equiation "<<itrEquiation->first<<endl<<flush);
		//for faster evaluation, store reference to the direction vector D_1
		const vector< tFactors > & vecFirstDirection =
			secondHyperplane.vecDirections[ uiDirectionForFactorNotNull ];
	
		//evalue the new direction vectors DI_i = D_i - a_i * D_1
		unsigned int uiActualDirection = uiFirstDirectionForNonTriangleFactor;
		
		for ( unsigned int uiActualFactor = uiFirstFactorNotSingle;
				( uiActualFactor < uiNumberOfFactors ) &&
				( uiActualDirection < uiNumberOfOldDirections );
				uiActualFactor++, uiActualDirection++ ){
			
			for ( unsigned int uiDimension = 0;
						uiDimension < uiNumberOfDimensions; uiDimension++ ){
				
				const tFactors factor = pActualEquiation->vecFactors[ uiActualFactor ] *
					vecFirstDirection[ uiDimension ];
				
				subFromFirst( secondHyperplane.vecDirections[ uiActualDirection ][ uiDimension ], factor );
			}
		}
		//evalue the new base vector BI = (B + constant * D_1)
		for ( unsigned int uiDimension = 0; uiDimension < uiNumberOfDimensions;
					uiDimension++ ){
			
			const tFactors factor = pActualEquiation->constant * vecFirstDirection[ uiDimension ];
			
			addToFirst( secondHyperplane.vecBase[ uiDimension ], factor );
		}
	}
	/*delete the directions for the first factors not null
	-> delete directions for factors in triangle form*/
	DEBUG_OUT_L2(<<"Delete the directions for factors in triangle form: from the "<<(uiFirstFactorSingle - uiNumberOfDirectionsInFirstHyperplane)<<" direction to the "<<(uiFirstFactorNotSingle - uiNumberOfDirectionsInFirstHyperplane)<<" direction"<<endl<<flush);
	typeItrDirection itrDirectionFirstFactorSingle =
		secondHyperplane.vecDirections.begin();
	for ( unsigned int uiActualFactor = uiNumberOfDirectionsInFirstHyperplane;
			( itrDirectionFirstFactorSingle != secondHyperplane.vecDirections.end() ) &&
			( uiActualFactor < uiFirstFactorSingle );
			uiActualFactor++, itrDirectionFirstFactorSingle++ ){
		//nothing to do
	}
	
	typeItrDirection itrDirectionFirstFactorNotSingle =
		secondHyperplane.vecDirections.begin();
	for ( unsigned int uiActualFactor = uiNumberOfDirectionsInFirstHyperplane;
			( itrDirectionFirstFactorNotSingle != secondHyperplane.vecDirections.end() ) &&
			( uiActualFactor < uiFirstFactorNotSingle );
			uiActualFactor++, itrDirectionFirstFactorNotSingle++ ){
		//nothing to do
	}
	secondHyperplane.vecDirections.erase( itrDirectionFirstFactorSingle,
		itrDirectionFirstFactorNotSingle );
	
#ifdef DEBUG
	cout<<"Actual intersection:"<<endl;
	pSecondHyperplane->print( cout );
#endif //DEBUG
	pSecondHyperplane->bInFormOne = false;
	pSecondHyperplane->convertToFormOne();
	
	return pSecondHyperplane;
}


/**
 * This method checks if this hyperplane is equal to the given
 * hyperplane.
 * Two hyperplanes are equal, if thy contain the same points.
 *
 * @param hyperplane the hyperplane, for wich to check if its equal to
 * 	this hyperplane
 * @return true if the given hyperplane is equal to this hyperplane
 * 	else false
 */
template <class tFactors> bool cHyperplane<tFactors>::equal(
		const cHyperplane< tFactors > & hyperplane ) const{
	
	if ( ( (fillType == ALL) && (hyperplane.fillType == ALL) ) ||
			( (fillType == NONE) && (hyperplane.fillType == NONE) ) ){
		return true;
	}//else
	
	if ( getNumberOfDimensions() != hyperplane.getNumberOfDimensions() ){
		//not the same number of dimensions -> not equal
		return false;
	}
	//number of independent direction vectors are the same in both
	if ( this->bDirectionsLinearIndependent && hyperplane.bDirectionsLinearIndependent ){
		if ( this->getNumberOfDirections() != hyperplane.getNumberOfDirections() ){
			return false;
		}
	}
	
	//compare form One of the hyperplanes
	if ( bInFormOne && hyperplane.bInFormOne ){
		
		if ( compareVectorDouble( vecBase, hyperplane.vecBase ) &&
				compareVectorVectorDouble( vecDirections, hyperplane.vecDirections ) ){
			return true;
		}//else
		return false;
	}//else
	if ( bInFormOne && ( ! hyperplane.bInFormOne ) ){
		
		cHyperplane<tFactors> hyperplaneConverted = hyperplane;
		hyperplaneConverted.convertToFormOne();
		
		if ( compareVectorDouble( vecBase, hyperplaneConverted.vecBase ) &&
				compareVectorVectorDouble( vecDirections, hyperplaneConverted.vecDirections ) ){
			return true;
		}//else
		return false;
	}//else
	if ( ! bInFormOne && hyperplane.bInFormOne ){
		
		cHyperplane<tFactors> hyperplaneConverted = *this;
		hyperplaneConverted.convertToFormOne();
		
		if ( compareVectorDouble( hyperplaneConverted.vecBase, hyperplane.vecBase ) &&
				compareVectorVectorDouble( hyperplaneConverted.vecDirections, hyperplane.vecDirections ) ){
			return true;
		}//else
		return false;
	}//else if ( ! bInFormOne && ! hyperplane.bInFormOne ){
	
	cHyperplane<tFactors> hyperplaneConverted1 = *this;
	hyperplaneConverted1.convertToFormOne();
	cHyperplane<tFactors> hyperplaneConverted2 = hyperplane;
	hyperplaneConverted2.convertToFormOne();
	
	if ( compareVectorDouble( hyperplaneConverted1.vecBase,
				hyperplaneConverted2.vecBase ) &&
			compareVectorVectorDouble( hyperplaneConverted1.vecDirections,
				hyperplaneConverted2.vecDirections ) ){
		return true;
	}//else
	return false;
}


/**
 * This method print the hyperplane in a readebel form to the given
 * output stream outputSream.
 *
 * @param outputSream the stream wher to print this inequation to
 */
template <class tFactors> void cHyperplane<tFactors>::print(
		ostream & outputStream ) const{
	
	if ( fillType == ALL ){
		outputStream<<"all space"<<endl;
		return;
	}//else
	if ( fillType == NONE ){
		outputStream<<"no hyperplane"<<endl;
		return;
	}//else
	
	//print: Y = B + D_1 * x_1 + D_2 * x_2 + ... + D_d * x_d
	const unsigned int uiNumberOfDimensions = getNumberOfDimensions();
	const unsigned int uiNumberOfDirections = getNumberOfDirections();
//	const unsigned int uiLineToPrintFactors = uiNumberOfDimensions / 2;
	
	if ( uiNumberOfDimensions == 0 ){
		outputStream<<"0 dimensions"<<endl;
		return;
	}
	
	for ( unsigned int uiDimension = 0;
			uiDimension < uiNumberOfDimensions; uiDimension++ ){
		//print: "Y = B"
//		if ( uiDimension == uiLineToPrintFactors ){
			outputStream<<"y_"<<uiDimension<<" = "<<vecBase[ uiDimension ];
/*		}else{
			outputStream<<"y_"<<uiDimension<<"   "<<vecBase[ uiDimension ];
		}*/
		//print: "+ D_i * x_i"
		for ( unsigned int uiActualDirection = 0;
				uiActualDirection < uiNumberOfDirections; uiActualDirection++ ){
			
//			if ( uiDimension == uiLineToPrintFactors ){
				outputStream<<" + "<<vecDirections[uiActualDirection ][ uiDimension ]<<
					" * x_"<<uiActualDirection;
/*			}else{
				outputStream<<"   "<<vecDirections[uiActualDirection ][ uiDimension ]<<"     ";
			}*/
		}
		outputStream<<endl;
	}
}


/**
 * This functions compares two vectors of vectors with double numbers.
 * Realy small differences betwean the vector element numbers will be ignored.
 *
 * @param vecVector1 the first vector of vectors to compare
 * @param vecVector2 the second vector of vectors to compare
 * @return true if the first vector of vectors is equal to the second, else false
 */
template <class tFactors> bool cHyperplane<tFactors>::compareVectorVectorDouble(
		const vector< vector< tFactors > > & vecVector1,
		const vector< vector< tFactors > > & vecVector2 ) const{
	
	if ( vecVector1.size() != vecVector2.size() ){
		//not the same number of elements -> vectors not equal
		return false;
	}
	const size_t uiNumberOfElements = vecVector1.size();
	
	for ( size_t uiActualElement = 0; uiActualElement < uiNumberOfElements;
			uiActualElement++ ){
		
		if ( ! fib::compareVectorDouble( vecVector1[ uiActualElement ], vecVector2[ uiActualElement ] ) ){
			//actual vector element not equal -> vectors not equal
			return false;
		}
	}//else all vector elements equal
	return true;
}



/**
 * This method recreates this hyperplane from the given inequation.
 *
 * @param inequation the inequiation which defines this hyperplane;
 * 	if the inequal sign of the inequation would be replaced by an
 * 	equal sign, all points which fulfill the equiation are on the
 * 	hyperplane
 * @param uiInNumberOfDimensions the number of dimensions the hyperplane
 * 	should be placed in
 */
template <class tFactors> bool cHyperplane<tFactors>::
		createHyperplaneFromInequiation(
		const nLinearInequation::cInequation< tFactors > & inequation,
		unsigned int uiInNumberOfDimensions ){
		
	const unsigned int uiNumberOfDimensions = uiInNumberOfDimensions;
	vecBase = vector< tFactors >( uiNumberOfDimensions, (tFactors)(0) );
	fillType = SOME;
	bDirectionsLinearIndependent = true;
	bInFormOne = true;
	vecDirections.clear();

	/*for the next evaluaions the inequal sign in the given inequation will
	be seen as an equal sign:
	  constant <= vecFactors[0] * x_0 + ... + vecFactors[n] * x_n
	-> constant = vecFactors[0] * x_0 + ... + vecFactors[n] * x_n
	
	the normal vector vor the inequation, is the vector with its elements
	set to the factors of the inequation:
		N = ( vecFactors[0], ..., vecFactors[n] )^T 
		so that 0 = -1 * constant + N * X is the hyperplane normal form*/

	//ignore more factors than dimensions
	const unsigned int uiNumberOfFactors = min( ((unsigned int)(
		inequation.vecFactors.size() )), uiNumberOfDimensions );
	if ( uiNumberOfFactors == 0 ){
		//no factors -> no valid hyperplane -> 0 directions
		/*if inequation is valid on all space points
		-> hyperplane fills all, else nothing*/
		if ( inequation.isTrue() ){
			//the inequation can be fulfilled
			fillType = ALL;
		}else{//the inequation can not be fulfilled
			fillType = NONE;
		}
		
		return false;
	}
	//get the last factor not 0
	unsigned int uiBaseFactor = uiNumberOfFactors - 1;
	do{
		if ( inequation.vecFactors[ uiBaseFactor ] != (tFactors)(0) ){
			//factor not 0 found
			break;
		}
		if ( 0 != uiBaseFactor ){
			uiBaseFactor--;
		}
	}while ( 0 != uiBaseFactor );
	
	if ( ( uiBaseFactor == 0 ) && ( inequation.vecFactors[ 0 ] == (tFactors)(0) ) ){
		//every factor is 0 -> no valid hyperplane -> 0 directions
		/*if inequation is valid on all space points
		-> hyperplane fills all, else nothing*/
		if ( inequation.isTrue() ){
			//the inequation can be fulfilled
			fillType = ALL;
		}else{//the inequation can not be fulfilled
			fillType = NONE;
		}
		
		return false;
	}

	/*create direction vectors:
	for every factor except the base factor create one direction by setting
	the element for the factor in the direction to 1 and all other elements,
	except for the base factor, of the direction to 0, evalue with this
	the element for the base factor by evaluing:
		-1.0 * vecFactors[ actual direction ] / vecFactors[ uiBaseFactor ]
	in this way:
		- all created vectors will be linear independend, becaus they have
		  an element set to 1, wich is in every other direction vector 0
		- the normal vector N of the inequation is at right angle to all
		  directions, because scalar product of the direction and the normal
		  vector N is 0:
		  ( vecFactors[0], ..., vecFactors[n] )^T * ( direction[0]=0, ...,
		  	direction[ actual direction] = 1, ...,
		  	direction[ uiBaseFactor ] = -1.0 * vecFactors[ actual direction ] / vecFactors[ uiBaseFactor ], ..., direction[n]=0 )^T
		  = vecFactors[ actual direction ] - vecFactors[ uiBaseFactor ] * vecFactors[ actual direction ] / vecFactors[ uiBaseFactor ]
		  = vecFactors[ actual direction ] - vecFactors[ actual direction ]
		  = 0
	*/
	for ( unsigned int uiDirection = 0;
			uiDirection < uiNumberOfDimensions; uiDirection++ ){
		
		if( uiDirection == uiBaseFactor ){
			continue;//skip base factor
		}
		vector< tFactors > vecDirection( uiNumberOfDimensions, (tFactors)(0) );
		
		vecDirection[ uiDirection ] = (tFactors)(1);
		if ( uiDirection < uiNumberOfFactors ){
			vecDirection[ uiBaseFactor ] =  (tFactors)(-1) *
				inequation.vecFactors[ uiDirection ] / inequation.vecFactors[ uiBaseFactor ];
		}//else no factor for direction
		vecDirections.push_back( vecDirection );
	}
	/*
	 * all direction vectors D_i are the (independent) hyperplane direction vectors
	 * D_i = ( h_i.1, ..., h_i.{o_i}, ..., h_i.d )^T
	 * with h_i.1= ...= h_i.{o_i - 1} = 0, h_i.{o_i} = 1 and
	 * o_{i-1} < o_i, for 1 < i (o_{i-1} is for D_{i-1} )
	*/
	
	//evalue a point on the hyperplane as the base vector.
	/*the base vector B, with |B| minimal, lays on the straight line of
	L = N * t, so B = N * t for a fixed t
		- (N * B) - constant = 0
		-> (N * (N * t)) - constant = 0 (B = N * t is a point on the hyperplane)
		-> N * N * t = constant
		-> t = constant / (N * N)
		-> B = N * (constant / (N * N))
	*/
	//evalue: t = (constant / (N * N))
	tFactors baseFactor = ((tFactors)(0));//=t
	//evalue N * N
	for ( unsigned int uiDirection = 0;
			uiDirection < uiNumberOfFactors; uiDirection++ ){
		
		baseFactor += inequation.vecFactors[ uiDirection ] * inequation.vecFactors[ uiDirection ];
	}
	baseFactor = inequation.constant / baseFactor;
	//evalue: B = N * t = N * (constant / (N * N))
	for ( unsigned int uiDirection = 0;
			uiDirection < uiNumberOfFactors; uiDirection++ ){
		
		vecBase[ uiDirection ] = inequation.vecFactors[ uiDirection ] * baseFactor;
	}
	return true;
}




#endif //___C_HYPERPLANE_CPP__


