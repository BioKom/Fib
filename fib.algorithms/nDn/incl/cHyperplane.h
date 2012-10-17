/**
 * @file cHyperplane
 * file name: cHyperplane.h
 * @author Betti Oesterholz
 * @date 31.12.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for a hyperplane.
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
31.12.2010  Oesterholz  created
*/

#ifndef ___C_HYPERPLANE_H__
#define ___C_HYPERPLANE_H__

#include "version.h"

#include "cInequation.h"

#include <vector>
#include <ostream>

using namespace std;


namespace fib{

namespace algorithms{

namespace nDn{


template <class tFactors>
class cHyperplane{
protected:
	
	/**
	 * The type for the direction vectors.
	 * @see vecDirections
	 */
	typedef vector< vector< tFactors > > typeDirection;
	
	/**
	 * The type for iterators for the direction vectors.
	 * @see typeDirection
	 * @see vecDirections
	 */
	typedef typename typeDirection::iterator typeItrDirection;
	
	/**
	 * The type for const iterators for the direction vectors.
	 * @see typeDirection
	 * @see vecDirections
	 */
	typedef typename typeDirection::const_iterator typeConstItrDirection;
	
	/**
	 * A point on the hyperplane as the base vector (B).
	 */
	vector< tFactors > vecBase;
	
	/**
	 * The (independent) direction vectors (D_i) for the hyperplane.
	 */
	typeDirection vecDirections;
	
	/**
	 * This type specifies how much the hyperplane fills of the dimensions.
	 *
	 * Values:
	 * 	- ALL: the hyperplane fills the whool space
	 * 	- NONE: the hyperplane fills nothing of the space (it didn't exists)
	 * 	- SOME: the hyperplane fills some of the space
	 */
	enum typeFillType{ ALL, NONE, SOME };
	
	/**
	 * This object specifies how much the hyperplane fills of the dimensions.
	 * @see typeFillType
	 */
	typeFillType fillType;
	
	
	/**
	 * The directions of this hyperplane are linear independent.
	 */
	bool bDirectionsLinearIndependent;
	
	/**
	 * The the hyperplane is in form One.
	 * Form One is a special hyperplane form, wich is uniqe and simpler to handle.
	 * Hyperplane form: Y = B + D_1 * x_1 + D_2 * x_2 + ... + D_d * x_d
	 * In form One:
	 * 	- B point on the hyperplane as the base vector, with |B| minimal
	 * 	- D_i are the independent hyperplane direction vectors
	 * 		D_i = ( h_i.1, ..., h_i.{o_i}, ..., h_i.d )^T
	 * 		with h_i.1= ...= h_i.o_i - 1} = 0, h_i.{o_i} = 1 and
	 * 		o_{i-1} < o_i, for 1 < i (o_{i-1} is for D_{i-1} )
	 */
	bool bInFormOne;
	
public:
	
	/**
	 * standardconstructor
	 */
	cHyperplane();
	
	/**
	 * parameterconstructor
	 *
	 * @param vecInBase the base vector (B) for the hyperplane @see vecBase
	 * @param vecInDirections the direction vectors (D_i) for the
	 * 	hyperplane @see vecDirections
	 */
	cHyperplane( const vector< tFactors > & vecInBase,
		const vector< vector< tFactors > > & vecInDirections );
	
	/**
	 * parameterconstructor
	 * The number of dimensions will be the number of factors in the
	 * inequation.
	 *
	 * @param inequation the inequiation which defines this hyperplane;
	 * 	if the inequal sign of the inequation would be replaced by an
	 * 	equal sign, all points which fulfill the equiation are on the
	 * 	hyperplane
	 */
	cHyperplane( const nLinearInequation::cInequation< tFactors > & inequation );
	
	/**
	 * parameterconstructor
	 *
	 * @param inequation the inequiation which defines this hyperplane;
	 * 	if the inequal sign of the inequation would be replaced by an
	 * 	equal sign, all points which fulfill the equiation are on the
	 * 	hyperplane
	 * @param uiNumberOfDimensions the number of dimensions the hyperplane
	 * 	should be placed in
	 */
	cHyperplane( const nLinearInequation::cInequation< tFactors > & inequation,
		unsigned int uiNumberOfDimensions );
	
	/**
	 * @return the base of this hyperplane (@see vecBase)
	 */
	vector< tFactors > getBase() const;
	
	/**
	 * This method sets the base of this hyperplane to the given vecInBase.
	 * @see vecBase
	 *
	 * @param vecInBase the base this hyperplane should have
	 */
	void setBase( const vector< tFactors > & vecInBase );
	
	/**
	 * This method returns the uiDirection'th direction vector of this hyperplane.
	 * @see vecDirections
	 *
	 * @param uiDirection the number of the direction vector to return
	 * 	(counting begins with 1)
	 * @return the uiDirection'th direction vector of this hyperplane or
	 * 	a vector with no elements, if no such direction exists
	 */
	vector< tFactors > getDirection( const unsigned int uiDirection ) const;
	
	/**
	 * @return a vector with all direction vectors of this hyperplane
	 * 	(@see vecDirections)
	 */
	vector< vector< tFactors > > getDirections() const;
	
	/**
	 * @return the number of direction vectors of this hyperplane
	 * 	(@see vecDirections); if the direction vectors are linear
	 * 	independent the returned value is also the dimensionality of
	 * 	this hyperplane
	 */
	unsigned int getNumberOfDirections() const;
	
	/**
	 * This method adds the given direction vector vecInDirection to this
	 * hyperplane.
	 * @see vecDirections
	 *
	 * @param vecInDirection the direction vector to add
	 * @return true if the direction was added else false
	 */
	bool addDirection( const vector< tFactors > & vecInDirection );
	
	/**
	 * This method adds the given direction vectors vecInDirections to this
	 * hyperplane.
	 * @see vecDirections
	 *
	 * @param vecInDirections the direction vectors to add
	 * @return the number of inserted direction vectors
	 */
	unsigned int addDirections( vector< vector< tFactors > > vecInDirections );
	
	/**
	 * This method deletes the uiDirection'th direction vector of this hyperplane.
	 * @see vecDirections
	 *
	 * @param uiDirection the number of the direction vector to delete
	 * 	(counting begins with 1)
	 * @return true if the uiDirection'th direction vector of this hyperplane
	 * 	was deleted, else false
	 */
	bool deleteDirection( unsigned int uiDirection );
	
	/**
	 * @return the number of dimensions this hyperplane is contained in
	 * 	(@see vecDirections, @see vecBase);
	 * 	the number of dimensions of this hyperplane are the numbers of elements
	 * 	in its vectors
	 */
	unsigned int getNumberOfDimensions() const;
	
	/**
	 * This method sets the number of dimensions this hyperplane is contained in.
	 * (@see vecDirections, @see vecBase);
	 * The number of dimensions of this hyperplane are the numbers of elements in
	 * its vectors.
	 *
	 * @param uiDimensionality the number of dimensions of this hyperplane
	 * @return the number of dimensions of this hyperplane
	 */
	unsigned int setNumberOfDimensions( unsigned int uiDimensionality );
	
	/**
	 * This method will remove all not independent vectors from the
	 * direction vectors (a_i). So that the remaining direction vectors
	 * are linear undependent.
	 */
	void makeDirectionsIndependent();
	
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
	void convertToFormOne();

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
	cHyperplane< tFactors > * evalueIntersection(
		const cHyperplane< tFactors > & hyperplane ) const;
	
	/**
	 * This method checks if this hyperplane is equal to the given
	 * hyperplane.
	 * Two hyperplanes are equal, if thy contain the same points.
	 *
	 * @param hyperplane the hyperplane , for wich to check if its equal to
	 * 	this hyperplane
	 * @return true if the given hyperplane is equal to this hyperplane
	 * 	else false
	 */
	bool equal( const cHyperplane< tFactors > & hyperplane ) const;
	
	
	/**
	 * This method print the hyperplane in a readebel form to the given
	 * output stream outputSream.
	 *
	 * @param outputSream the stream wher to print this inequation to
	 */
	void print( ostream & outputStream ) const;
	
protected:
	
	
	/**
	 * This functions compares two vectors of vectors with double numbers.
	 * Realy small differences betwean the vector element numbers will be ignored.
	 *
	 * @param vector1 the first vector of vectors to compare
	 * @param vector2 the second vector of vectors to compare
	 * @return true if the first vector of vectors is equal to the second, else false
	 */
	bool compareVectorVectorDouble( const vector< vector< tFactors > > & vector1,
			const vector< vector< tFactors > > & vector2 ) const;
	
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
	bool createHyperplaneFromInequiation(
		const nLinearInequation::cInequation< tFactors > & inequation,
		unsigned int uiInNumberOfDimensions );
};//class cHyperplane


};//end namespace nDn
};//end namespace algorithms
};//end namespace fib

//include template implementation
#include "../src/cHyperplane.cpp"


#endif //___C_HYPERPLANE_H__
