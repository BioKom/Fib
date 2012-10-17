/**
 * @file cMatrix2D
 * file name: cMatrix2D.cpp
 * @author Betti Oesterholz
 * @date 04.07.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements a class for a two dimensional matrix of values.
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
 * This file implements a class for a two dimensional matrix of values.
 * (Position counting begins at 0.)
 *
 */
/*
History:
04.07.2010  Oesterholz  created
*/

#include "cMatrix2D.h"

#ifndef ___C_MATRIX_2D_CPP__
#define ___C_MATRIX_2D_CPP__

#include <algorithm>


//#define DEBUG_OUTPUT_MATRIX
#ifdef DEBUG_OUTPUT_MATRIX
	#include <iostream>
#endif

using namespace std;

using namespace fib::algorithms::nD2;



/**
 * standardconstructor
 *
 * @param ulInSizeX the size of the matrix in the x (first) uiDirection
 * @param ulInSizeY the size of the matrix in the y (second) uiDirection
 * @param initValue the value, with which to initialisize the matrix
 */
template <class tValue> cMatrix2D<tValue>::cMatrix2D(
		unsigned long ulInSizeX, unsigned long ulInSizeY,
		const tValue & initValue ):
		matrix( initValue, (ulInSizeX * ulInSizeY) ),
		ulSizeX( ulInSizeX ), ulSizeY( ulInSizeY ){
	//nothing to do
}


/**
 * copyconstructor
 *
 * @param inMatrix the matrix to copy
 */
template <class tValue> cMatrix2D<tValue>::cMatrix2D(
	const cMatrix2D & inMatrix ):
		matrix( inMatrix.matrix ),
		ulSizeX( inMatrix.ulSizeX ), ulSizeY( inMatrix.ulSizeY ){
	//nothing to do
}


/**
 * This method retuns the a reference to the value on the given
 * position (ulX, ulY) .
 * Beware: It won't be checked, if the position is out of bounds.
 *
 * @param ulX the position in the x (first) uiDirection
 * @param ulY the position in the y (second) uiDirection
 * @return a reference to the value on the given position (ulX, ulY)
 */
template <class tValue> tValue & cMatrix2D<tValue>::get(
		unsigned long ulX, unsigned long ulY ){

	return matrix[ ulX + ulY * ulSizeX ];
}


/**
 * This method retuns the a reference to the value on the given
 * position (ulX, ulY) .
 * Beware: It won't be checked, if the position is out of bounds.
 *
 * @param ulX the position in the x (first) uiDirection
 * @param ulY the position in the y (second) uiDirection
 * @return a reference to the value on the given position (ulX, ulY)
 */
template <class tValue> const tValue & cMatrix2D<tValue>::get(
		unsigned long ulX, unsigned long ulY ) const{

	return matrix[ ulX + ulY * ulSizeX ];
}


/**
 * This method sets the the given value on the given position (ulX, ulY) .
 *
 * @param ulX the position in the x (first) uiDirection
 * @param ulY the position in the y (second) uiDirection
 * @param value the value to set
 * @return true if the value was set, else false (e.g. if the position
 * 	is out of bounds)
 */
template <class tValue> bool cMatrix2D<tValue>::set(
		unsigned long ulX, unsigned long ulY, const tValue & value ){
	
	if ( ( ulSizeX <= ulX ) || ( ulSizeY <= ulY ) ){
		return false;
	}
	matrix[ ulX + ulY * ulSizeX ] = value;
	
	return true;
}


/**
 * @return a pair (x, y) with the size of the matrix in x (first)
 * 	and y (second) uiDirection
 */
template <class tValue> pair< unsigned long, unsigned long >
		cMatrix2D<tValue>::size() const{
	
	return pair< unsigned long, unsigned long >( ulSizeX, ulSizeY );
}


/**
 * @param ulInSizeX the new size of the matrix in the x (first) uiDirection
 * @param ulInSizeY the new size of the matrix in the y (second) uiDirection
 * @param initValue the value, with which to initialisize the matrix new values
 */
template <class tValue> void cMatrix2D<tValue>::resize(
		unsigned long ulInSizeX, unsigned long ulInSizeY,
		const tValue & initValue ){
	
	if ( ( ulInSizeX == ulSizeX ) && ( ulInSizeY == ulSizeY ) ){
		return;
	}
	
	valarray< tValue > matrixTmp( initValue, (ulInSizeX * ulInSizeY) );
	
	const unsigned long ulMinSizeX = std::min( ulSizeX, ulInSizeX );
	const unsigned long ulMinSizeY = std::min( ulSizeY, ulInSizeY );
	
	for ( unsigned long ulX = 0; ulX < ulMinSizeX; ulX++ ){
		for ( unsigned long ulY = 0; ulY < ulMinSizeY; ulY++ ){
		
			matrixTmp[ ulX + ulY * ulInSizeX ] = matrix[ ulX + ulY * ulSizeX ];
		}
	}
	ulSizeX = ulInSizeX;
	ulSizeY = ulInSizeY;
	matrix  = matrixTmp;
}


/**
 * assignment operator
 * This operator copies the given matrixdata into this matrix.
 *
 * @param inMatrix the matrix to copy
 * @return a reference to this matrix, with the copied values
 */
template <class tValue> cMatrix2D<tValue> & cMatrix2D<tValue>::operator=(
		const cMatrix2D & inMatrix ){
	
	matrix  = inMatrix.matrix;
	ulSizeX = inMatrix.ulSizeX;
	ulSizeY = inMatrix.ulSizeY;
}


/**
 * This operator adds the values of the given matrix to the values of
 * this matrix.
 * Position not in both matrixes will be ignored.
 *
 * @param inMatrix the matrix to add
 * @return a reference to this matrix
 */
template <class tValue> cMatrix2D<tValue> & cMatrix2D<tValue>::operator+=(
		const cMatrix2D & inMatrix ){
	
	matrix += inMatrix.matrix;
	return *this;
}


/**
 * This operator subtracts the values of the given matrix from the
 * values of this matrix.
 * Position not in both matrixes will be ignored.
 *
 * @param inMatrix the matrix to subtracts
 * @return a reference to this matrix
 */
template <class tValue> cMatrix2D<tValue> & cMatrix2D<tValue>::operator-=(
		const cMatrix2D & inMatrix ){
	
	matrix -= inMatrix.matrix;
	return *this;
}


/**
 * This operator multiplys the values of the given matrix to the
 * values of this matrix.
 * Position not in both matrixes will be ignored.
 *
 * @param inMatrix the matrix to multiply with
 * @return a reference to this matrix
 */
template <class tValue> cMatrix2D<tValue> & cMatrix2D<tValue>::operator*=(
		const cMatrix2D & inMatrix ){
	
	matrix *= inMatrix.matrix;
	return *this;
}


/**
 * This operator divides the values of the given matrix with the
 * values of this matrix.
 * Position not in both matrixes will be ignored.
 *
 * @param inMatrix the matrix to divide with
 * @return a reference to this matrix
 */
template <class tValue> cMatrix2D<tValue> & cMatrix2D<tValue>::operator/=(
		const cMatrix2D & inMatrix ){
	
	matrix /= inMatrix.matrix;
	return *this;
}

/**
 * This operator applies the values of the given function to the
 * values of this matrix.
 *
 * @return a reference to this matrix
 */
template <class tValue> cMatrix2D<tValue> & cMatrix2D<tValue>::
		apply( tValue func(const tValue&) ){
	
	matrix = matrix.apply( func );
	return *this;
}


/**
 * @return the minimum value in this matrix
 */
template <class tValue> tValue cMatrix2D<tValue>::min() const{
	
	return matrix.min();
}


/**
 * @return the maximum value in this matrix
 */
template <class tValue> tValue cMatrix2D<tValue>::max() const{
	
	return matrix.max();
}


/**
 * @return the sum of all values in this matrix
 */
template <class tValue> tValue cMatrix2D<tValue>::sum() const{
	
	return matrix.sum();
}


/**
 * This method evalues the derivate of this matrix in the given uiDirection.
 * For this, from each element the higer neibourelement value in the
 * uiDirection will be subtracted.
 * The last element in the uiDirection is eleminated. The size of the matrix
 * is reduced with 1 in the uiDirection.
 *
 * @param uiDirection the uiDirection in which to evalue the derivate
 * 	- 1: the position in the x (first) uiDirection
 * 	- 2: the position in the y (second) uiDirection
 * @return a reference to this matrix
 */
template <class tValue> cMatrix2D<tValue> & cMatrix2D<tValue>::derivate(
		unsigned int uiDirection ){
	
	if ( uiDirection == 1 ){
		return derivateDirection1();
	}else if ( uiDirection == 2 ){
		return derivateDirection2();
	}
	return *this;
}


/**
 * This method evalues the derivate of this matrix in the x (first) uiDirection.
 * For this, from each element the higer neibourelement value in the
 * x uiDirection will be subtracted.
 * The last element in the x uiDirection is eleminated. The size of the matrix
 * is reduced with 1 in the x uiDirection.
 *
 * @return a reference to this matrix
 */
template <class tValue> cMatrix2D<tValue> & cMatrix2D<tValue>::derivateDirection1(){

	const unsigned long ulSizeXNew = ulSizeX - 1;
	valarray< tValue > matrixTmp( ((tValue)(0)), (ulSizeXNew * ulSizeY) );
	
	for ( unsigned long ulX = 0; ulX < ulSizeXNew; ulX++ ){
		for ( unsigned long ulY = 0; ulY < ulSizeY; ulY++ ){
		
			matrixTmp[ ulX + ulY * ulSizeXNew ] =
				matrix[ ulX + ulY * ulSizeX ] - matrix[ ulX + 1 + ulY * ulSizeX ];
		}
	}
	ulSizeX = ulSizeXNew;
	matrix  = matrixTmp;
	
	return *this;
}


/**
 * This method evalues the derivate of this matrix in the y (second) uiDirection.
 * For this, from each element the higer neibourelement value in the
 * y uiDirection will be subtracted.
 * The last element in the y uiDirection is eleminated. The size of the matrix
 * is reduced with 1 in the y uiDirection.
 *
 * @return a reference to this matrix
 */
template <class tValue> cMatrix2D<tValue> & cMatrix2D<tValue>::derivateDirection2(){
	
	const valarray< tValue > matrixTmp = matrix.shift( ((long)ulSizeX) );
#ifdef DEBUG_OUTPUT_MATRIX
	cout<<"matrix: ";
	for ( unsigned int uiActualElement = 0; uiActualElement < matrix.size(); uiActualElement++ ){
		cout<<matrix[ uiActualElement ]<<"; ";
	}
	cout<<endl;
	cout<<"matrixTmp: ";
	for ( unsigned int uiActualElement = 0; uiActualElement < matrixTmp.size(); uiActualElement++ ){
		cout<<matrixTmp[ uiActualElement ]<<"; ";
	}
	cout<<endl;
#endif
	matrix -= matrixTmp;
#ifdef DEBUG_OUTPUT_MATRIX
	cout<<"matrix -= matrixTmp: ";
	for ( unsigned int uiActualElement = 0; uiActualElement < matrix.size(); uiActualElement++ ){
		cout<<matrix[ uiActualElement ]<<"; ";
	}
	cout<<endl;
#endif
	ulSizeY--;
	return *this;
}


/**
 * @param condition the condition which should hold for counted values
 * @return the number of values for which the given condition is true
 */
template <class tValue> unsigned long cMatrix2D<tValue>::count(
		bool condition( const tValue & ) ) const{
	
	unsigned long ulCount = 0;
	const unsigned long ulNumberOfValues = ulSizeX * ulSizeY;
	for ( unsigned long ulValue = 0; ulValue < ulNumberOfValues; ulValue++ ){
		
		if ( condition( matrix[ ulValue ] ) ){
			ulCount++;
		}
	}
	return ulCount;
}


/**
 * @return the number of values which are 0
 */
template <class tValue> unsigned long cMatrix2D<tValue>::countNull() const{
	
	return count( cMatrix2D<tValue>::isNull );
}


/**
 * @param condition the condition which should hold for the values
 * @return a matrix with the bool values, which are the result of the
 * 	given condition on the values of this matrix
 */
template <class tValue> cMatrix2D<bool> cMatrix2D<tValue>::evalueCondition(
	bool condition( const tValue & ) ) const{
	
	cMatrix2D<bool> restulMatrix( ulSizeX, ulSizeY, false );
	
	for ( unsigned long ulX = 0; ulX < ulSizeX; ulX++ ){
		for ( unsigned long ulY = 0; ulY < ulSizeY; ulY++ ){
		
			restulMatrix.set( ulX, ulY, condition( get( ulX, ulY ) ) );
		}
	}
	return restulMatrix;
}


/**
 * This method prints this matrix in an readebel for to the given stream.
 *
 * @param outStream the stream wher to print this matrix to
 */
template <class tValue> void cMatrix2D<tValue>::print(
		ostream & outStream ) const{
	
	outStream <<"printing matrix of size x="<< ulSizeX <<" y="<< ulSizeY <<endl;
	for ( unsigned long ulX = 0; ulX < ulSizeX; ulX++ ){
		for ( unsigned long ulY = 0; ulY < ulSizeY; ulY++ ){
		
			outStream << get( ulX, ulY ) <<"; ";
		}
		outStream <<endl;
	}
	outStream <<endl;
}



#endif //___C_MATRIX_2D_CPP__


#ifndef ___C_MATRIX_2D_H_INCLUDE__

//specialisations
namespace fib{
namespace algorithms{
namespace nD2{
	/**
	 * @return the number of values which are 0
	 */
	template <> unsigned long cMatrix2D<double>::countNull() const{
		
		return count( cMatrix2D<double>::isNullD );
	}


	/**
	 * @return the number of values which are 0
	 */
	template <> unsigned long cMatrix2D<long double>::countNull() const{
		
		return count( cMatrix2D<long double>::isNullLD );
	}

};//end namespace nD2
};//end namespace algorithms
};//end namespace fib

#endif//not ___C_MATRIX_2D_H_INCLUDE__















