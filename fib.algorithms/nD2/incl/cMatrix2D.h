/**
 * @file cMatrix2D
 * file name: cMatrix2D.h
 * @author Betti Oesterholz
 * @date 01.07.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for a two dimensional matrix of values.
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
 * This header specifies a class for a two dimensional matrix of values.
 * (Position counting begins at 0.)
 *
 */
/*
History:
01.07.2010  Oesterholz  created
*/

#ifndef ___C_MATRIX_2D_H__
#define ___C_MATRIX_2D_H__

#include "version.h"

#include <valarray>
#include <ostream>

using namespace std;

namespace fib{

namespace algorithms{

namespace nD2{


template <class tValue>
class cMatrix2D{
protected:

	/**
	 * Matrix with its values.
	 * Position (x,y) is element: x + y * ulSizeX
	 */
	valarray< tValue > matrix;
	
	/**
	 * The size of the matrix in the x (first) direction.
	 */
	unsigned long ulSizeX;
	
	/**
	 * The size of the matrix in the y (second) direction.
	 */
	unsigned long ulSizeY;
	
public:

	/**
	 * standardconstructor
	 *
	 * @param ulInSizeX the size of the matrix in the x (first) direction
	 * @param ulInSizeY the size of the matrix in the y (second) direction
	 * @param initValue the value, with which to initialisize the matrix
	 */
	cMatrix2D( unsigned long ulInSizeX, unsigned long ulInSizeY,
		const tValue & initValue = 0 );
	
	/**
	 * copyconstructor
	 *
	 * @param inMatrix the matrix to copy
	 */
	cMatrix2D( const cMatrix2D & inMatrix );
	
	/**
	 * This method retuns the a reference to the value on the given
	 * position (ulX, ulY) .
	 * Beware: It won't be checked, if the position is out of bounds.
	 *
	 * @param ulX the position in the x (first) direction
	 * @param ulY the position in the y (second) direction
	 * @return a reference to the value on the given position (ulX, ulY)
	 */
	tValue & get( unsigned long ulX, unsigned long ulY );
	
	/**
	 * This method retuns the a reference to the value on the given
	 * position (ulX, ulY) .
	 * Beware: It won't be checked, if the position is out of bounds.
	 *
	 * @param ulX the position in the x (first) direction
	 * @param ulY the position in the y (second) direction
	 * @return a reference to the value on the given position (ulX, ulY)
	 */
	const tValue & get( unsigned long ulX, unsigned long ulY ) const;

	/**
	 * This method sets the the given value on the given position (ulX, ulY) .
	 *
	 * @param ulX the position in the x (first) direction
	 * @param ulY the position in the y (second) direction
	 * @param value the value to set
	 * @return true if the value was set, else false (e.g. if the position
	 * 	is out of bounds)
	 */
	bool set( unsigned long ulX, unsigned long ulY, const tValue & value );
	
	/**
	 * @return a pair (x, y) with the size of the matrix in x (first)
	 * 	and y (second) direction
	 */
	pair< unsigned long, unsigned long > size() const;
	
	/**
	 * @param ulInSizeX the new size of the matrix in the x (first) direction
	 * @param ulInSizeY the new size of the matrix in the y (second) direction
	 * @param initValue the value, with which to initialisize the matrix new values
	 */
	void resize(unsigned long ulInSizeX, unsigned long ulInSizeY,
		const tValue & initValue = 0 );
	
	/**
	 * assignment operator
	 * This operator copies the given matrixdata into this matrix.
	 *
	 * @param inMatrix the matrix to copy
	 * @return a reference to this matrix, with the copied values
	 */
	cMatrix2D<tValue> & operator=( const cMatrix2D & inMatrix );
	
	/**
	 * This operator adds the values of the given matrix to the values of
	 * this matrix.
	 * Position not in both matrixes will be ignored.
	 *
	 * @param inMatrix the matrix to add
	 * @return a reference to this matrix
	 */
	cMatrix2D<tValue> & operator+=( const cMatrix2D & inMatrix );
	
	/**
	 * This operator subtracts the values of the given matrix from the
	 * values of this matrix.
	 * Position not in both matrixes will be ignored.
	 *
	 * @param inMatrix the matrix to subtracts
	 * @return a reference to this matrix
	 */
	cMatrix2D<tValue> & operator-=( const cMatrix2D & inMatrix );
	
	/**
	 * This operator multiplys the values of the given matrix to the
	 * values of this matrix.
	 * Position not in both matrixes will be ignored.
	 *
	 * @param inMatrix the matrix to multiply with
	 * @return a reference to this matrix
	 */
	cMatrix2D<tValue> & operator*=( const cMatrix2D & inMatrix );
	
	/**
	 * This operator divides the values of the given matrix with the
	 * values of this matrix.
	 * Position not in both matrixes will be ignored.
	 *
	 * @param inMatrix the matrix to divide with
	 * @return a reference to this matrix
	 */
	cMatrix2D<tValue> & operator/=( const cMatrix2D & inMatrix );
	
	/**
	 * This operator applies the values of the given function to the
	 * values of this matrix.
	 *
	 * @return a reference to this matrix
	 */
	cMatrix2D<tValue> & apply( tValue func(const tValue&) );
	
	/**
	 * @return the minimum value in this matrix
	 */
	tValue min() const;
	
	/**
	 * @return the maximum value in this matrix
	 */
	tValue max() const;

	/**
	 * @return the sum of all values in this matrix
	 */
	tValue sum() const;

	/**
	 * This method evalues the derivate of this matrix in the given direction.
	 * For this, from each element the higer neibourelement value in the
	 * direction will be subtracted.
	 * The last element in the direction is eleminated. The size of the matrix
	 * is reduced with 1 in the direction.
	 *
	 * @param direction the direction in which to evalue the derivate
	 * 	- 1: the position in the x (first) direction
	 * 	- 2: the position in the y (second) direction
	 * @return a reference to this matrix
	 */
	cMatrix2D<tValue> & derivate( unsigned int direction = 1 );
	
	/**
	 * This method evalues the derivate of this matrix in the x (first) direction.
	 * For this, from each element the higer neibourelement value in the
	 * x direction will be subtracted.
	 * The last element in the x direction is eleminated. The size of the matrix
	 * is reduced with 1 in the x direction.
	 *
	 * @return a reference to this matrix
	 */
	cMatrix2D<tValue> & derivateDirection1();
	
	/**
	 * This method evalues the derivate of this matrix in the y (second) direction.
	 * For this, from each element the higer neibourelement value in the
	 * y direction will be subtracted.
	 * The last element in the y direction is eleminated. The size of the matrix
	 * is reduced with 1 in the y direction.
	 *
	 * @return a reference to this matrix
	 */
	cMatrix2D<tValue> & derivateDirection2();
	
	/**
	 * @param condition the condition which should hold for counted values
	 * @return the number of values for which the given condition is true
	 */
	unsigned long count( bool condition( const tValue & ) ) const;
	
	/**
	 * @return the number of values which are 0
	 */
	unsigned long countNull() const;
	
	/**
	 * @param condition the condition which should hold for the values
	 * @return a matrix with the bool values, which are the result of the
	 * 	given condition on the values of this matrix
	 */
	cMatrix2D<bool> evalueCondition( bool condition( const tValue & ) ) const;
	
	/**
	 * This method prints this matrix in an readebel for to the given stream.
	 *
	 * @param outStream the stream wher to print this matrix to
	 */
	void print( ostream & outStream ) const;

/*TODO later
	errode1Neibour()
	errode2Neibour()
	errode3Neibour()
	errode4Neibour()
*/
protected:
	
	/**
	 * @param value the value for which to check, if it is 0
	 * @return true if the given value is 0, else false
	 */
	static bool isNullD( const double & value ){
		
		const double SAVE_BOUNDERY = 0.0000000001;
		const double SAVE_BOUNDERY_NEG = SAVE_BOUNDERY * -1.0;
		return ( (SAVE_BOUNDERY_NEG < value) && (value < SAVE_BOUNDERY) );
	}

	/**
	 * @param value the value for which to check, if it is 0
	 * @return true if the given value is 0, else false
	 */
	static bool isNullLD( const long double & value ){
		
		const long double SAVE_BOUNDERY = 0.0000000001;
		const long double SAVE_BOUNDERY_NEG = SAVE_BOUNDERY * -1.0;
		return ( (SAVE_BOUNDERY_NEG < value) && (value < SAVE_BOUNDERY) );
	}

	
	/**
	 * @param value the value for which to check, if it is 0
	 * @return true if the given value is 0, else false
	 */
	static bool isNull( const tValue & value ){
	
		return ( value == 0 );
	}


};


};//end namespace nD2
};//end namespace algorithms
};//end namespace fib

#define ___C_MATRIX_2D_H_INCLUDE__
//include template implementation
#include "../src/cMatrix2D.cpp"
#undef ___C_MATRIX_2D_H_INCLUDE__

#endif //___C_MATRIX_2D_H__
