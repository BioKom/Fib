/**
 * @class cMatrix3DInteger
 * file name: cMatrix3DInteger.cpp
 * @author Betti Oesterholz
 * @date 04.03.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the implementation for 3 dimensional integer matrix class.
 *
 *
 * Copyright (C) @c LGPL3 2013 Betti Oesterholz
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
 * This file contains the implementation for 3 dimensional integer matrix class.
 * It stores a 3 dimensional matrix. The element of the matrix are integer
 * values. The index of the matrix are natural numbers beginning at 0 .
 */
/*
History:
04.03.2013  Oesterholz  created
*/


#include "cMatrix3DInteger.h"

#include <string.h>


using namespace fib;


/**
 * constructor
 *
 * @param uiMaxIndexX the maximal index for the first (1. or x)
 * 	dimension; All index values in the first (1. or x) dimension are
 * 	positiv (including 0) natural numbers lower equal uiMaxIndexX .
 * 	@see uiBorderIndexX
 * @param uiMaxIndexY the maximal index for the second (2. or y)
 * 	dimension; All index values in the second (2. or y) dimension are
 * 	positiv (including 0) natural numbers lower equal uiMaxIndexY .
 * 	@see uiBorderIndexY
 * @param uiMaxIndexZ the maximal index for the third (3. or z)
 * 	dimension; All index values in the third (3. or z) dimension are
 * 	positiv (including 0) natural numbers lower equal uiMaxIndexZ .
 * 	@see uiBorderIndexZ
 * @param uiBitsPerValue The bits per integer entry value in the matrix.
 * 	The entry values in the matrix are in the range from
 * 	-1 * 2^(uiBitsPerEntry - 1) to 2^(uiBitsPerEntry - 1) - 1 .
 * 	@see uiBitsPerEntry
 */
cMatrix3DInteger::cMatrix3DInteger( const unsigned int uiMaxIndexX,
		const unsigned int uiMaxIndexY, const unsigned int uiMaxIndexZ,
		const unsigned int uiBitsPerValue ):
		matrix( uiMaxIndexZ + 1, vector< char* >( uiMaxIndexY + 1, NULL ) ),
		uiBorderIndexX( uiMaxIndexX + 1 ), uiBorderIndexY( uiMaxIndexY + 1 ),
		uiBorderIndexZ( uiMaxIndexZ + 1 ),
		uiBitsPerEntry( min( uiBitsPerValue, ((const unsigned int)sizeof( longFib )) * 8 ) ),
		uiBytsPerEntry( ( uiBitsPerEntry - 1 ) / 8 + 1 ),
		lMinEntryValue( evalueMinValue( uiBitsPerEntry ) ),
		lMaxEntryValue( evalueMaxValue( uiBitsPerEntry ) ){
	
	//create an empty matrix
	const size_t uiBytsPerVectorDim2 = uiBorderIndexX * uiBytsPerEntry;
	
	for ( vector< vector< char* > >::iterator itrSubMatrixDim3 = matrix.begin();
			itrSubMatrixDim3 != matrix.end(); itrSubMatrixDim3++ ){
		
		vector< char* > & vecSubMatrixDim3 = *itrSubMatrixDim3;
		
		for ( vector< char* >::iterator
				itrSubVectorDim2 = vecSubMatrixDim3.begin();
				itrSubVectorDim2 != vecSubMatrixDim3.end(); itrSubVectorDim2++ ){
			
			(*itrSubVectorDim2) = (char*)malloc( uiBytsPerVectorDim2 );
		}
	}
	clear();
}


/**
 * copy constructor
 *
 * @param matrix3DInteger the matrix to copy
 */
cMatrix3DInteger::cMatrix3DInteger( const cMatrix3DInteger & matrix3DInteger ):
		matrix( matrix3DInteger.uiBorderIndexZ,
			vector< char* >( matrix3DInteger.uiBorderIndexY, NULL ) ),
		uiBorderIndexX( matrix3DInteger.uiBorderIndexX ),
		uiBorderIndexY( matrix3DInteger.uiBorderIndexY ),
		uiBorderIndexZ( matrix3DInteger.uiBorderIndexZ ),
		uiBitsPerEntry( matrix3DInteger.uiBitsPerEntry ),
		uiBytsPerEntry( matrix3DInteger.uiBytsPerEntry ),
		lMinEntryValue( matrix3DInteger.lMinEntryValue ),
		lMaxEntryValue( matrix3DInteger.lMaxEntryValue ){
	
	//create a copy of the original matrix of matrix3DInteger
	const size_t uiBytsPerVectorDim2 = uiBorderIndexX * uiBytsPerEntry;
	
	vector< vector< char* > >::const_iterator itrSubMatrixDim3Org =
		matrix3DInteger.matrix.begin();
	for ( vector< vector< char* > >::iterator itrSubMatrixDim3 = matrix.begin();
			itrSubMatrixDim3 != matrix.end();
			itrSubMatrixDim3++, itrSubMatrixDim3Org++ ){
		
		vector< char* > & vecSubMatrixDim3 = *itrSubMatrixDim3;
		
		vector< char* >::const_iterator
			itrSubVectorDim2Org = itrSubMatrixDim3Org->begin();
		
		for ( vector< char* >::iterator
				itrSubVectorDim2 = vecSubMatrixDim3.begin();
				itrSubVectorDim2 != vecSubMatrixDim3.end();
				itrSubVectorDim2++, itrSubVectorDim2Org++ ){
			
			(*itrSubVectorDim2) = (char*)malloc( uiBytsPerVectorDim2 );
			memcpy( (*itrSubVectorDim2), (*itrSubVectorDim2Org),
				uiBytsPerVectorDim2 );
		}
	}
}


/**
 * destructor
 */
cMatrix3DInteger::~cMatrix3DInteger(){
	//free the matrix memory
	for ( vector< vector< char* > >::iterator itrSubMatrixDim3 = matrix.begin();
			itrSubMatrixDim3 != matrix.end(); itrSubMatrixDim3++ ){
		
		vector< char* > & vecSubMatrixDim3 = *itrSubMatrixDim3;
		
		for ( vector< char* >::iterator
				itrSubVectorDim2 = vecSubMatrixDim3.begin();
				itrSubVectorDim2 != vecSubMatrixDim3.end(); itrSubVectorDim2++ ){
			
			free( *itrSubVectorDim2 );
		}
	}
}


/**
 * This method clones this object.
 *
 * @return a pointer to the clone of this object
 */
cMatrix3DInteger * cMatrix3DInteger::clone() const{
	
	return new cMatrix3DInteger( *this );
}


/**
 * @return the name of this class
 */
string cMatrix3DInteger::getName() const{
	
	return "cMatrix3DInteger";
}


/**
 * With this method the value for a matrix element is set.
 *
 * @param dValue the value to set
 * @param uiPositionX the index on the first (x) dimension where to set
 * 	the value dValue
 * @param uiPositionY the index on the second (y) dimension where to set
 * 	the value dValue
 * @param uiPositionZ the index on the third (z) dimension where to set
 * 	the value dValue
 * @return OK (or 0) if the value could be set, else the error value
 * 	@see tErrorValue
 */
iMatrix3D::tErrorValue cMatrix3DInteger::setValue( const doubleFib dValue,
		const unsigned int uiPositionX, const unsigned int uiPositionY,
		const unsigned int uiPositionZ ){
	//can just set integer values
	return setValue( roundToLongFib( dValue ),
		uiPositionX, uiPositionY, uiPositionZ );
}


/**
 * With this method the value for a matrix element is set.
 *
 * @param lValue the value to set
 * @param uiPositionX the index on the first (x) dimension where to set
 * 	the value dValue
 * @param uiPositionY the index on the second (y) dimension where to set
 * 	the value dValue
 * @param uiPositionZ the index on the third (z) dimension where to set
 * 	the value dValue
 * @return OK (or 0) if the value could be set, else the error value
 * 	@see tErrorValue
 */
iMatrix3D::tErrorValue cMatrix3DInteger::setValue( const longFib lValue,
		const unsigned int uiPositionX, const unsigned int uiPositionY,
		const unsigned int uiPositionZ ){
	
	if ( uiBorderIndexX <= uiPositionX ){
		//no such entry
		return ERROR_OUTSIDE_INDEX_DIMENSION_1;
	}//else
	if ( uiBorderIndexY <= uiPositionY ){
		//no such entry
		return ERROR_OUTSIDE_INDEX_DIMENSION_2;
	}//else
	if ( uiBorderIndexZ <= uiPositionZ ){
		//no such entry
		return ERROR_OUTSIDE_INDEX_DIMENSION_3;
	}//else
	if ( lValue < lMinEntryValue ){
		//value lower minimum entry value -> don't set
		return ERROR_LOWER_MIN_VALUE;
	}//else
	if ( lMaxEntryValue < lValue ){
		//value higher maximum entry value -> don't set
		return ERROR_GREATER_MAX_VALUE;
	}//else
	char * pEntry = matrix[ uiPositionZ ][ uiPositionY ] +
		uiPositionX * uiBytsPerEntry;
	
	memcpy( pEntry, &lValue, uiBytsPerEntry );
	
	return OK;
}


/**
 * With this method the value for a matrix element is returned.
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the value
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the value
 * @param uiPositionZ the index on the third (z) dimension of which to
 * 	return the value
 * @return the value of the given position in the matrix
 */
doubleFib cMatrix3DInteger::getValue( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiPositionZ ) const{
	//just integer values stored
	return getValueLong( uiPositionX, uiPositionY, uiPositionZ );
}


/**
 * With this method the integer value for a matrix element is returned.
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the value
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the value
 * @param uiPositionZ the index for the third (z) dimension of which to
 * 	return the value
 * @return the integer value of the given position in the matrix
 */
longFib cMatrix3DInteger::getValueLong( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiPositionZ ) const{
	
	if ( ( uiBorderIndexX <= uiPositionX ) ||
			( uiBorderIndexY <= uiPositionY ) ||
			( uiBorderIndexZ <= uiPositionZ ) ){
		//no such entry
		return 0;
	}//else
	if ( uiBytsPerEntry == 0 ){
		//no byts per entry -> all entries 0
		return 0;
	}
	const char * pEntry = matrix[ uiPositionZ ][ uiPositionY ] +
		uiPositionX * uiBytsPerEntry;
	
	const char * pEntrySign = pEntry + (uiBytsPerEntry - 1);
	
	longFib lValue = ( ((*pEntrySign) & 0x80) == 0x80 )? -1 : 0;
	memcpy( &lValue, pEntry, uiBytsPerEntry );
	
	return lValue;
}


/**
 * With this method the minimum value for a matrix element is returned.
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the minimum value
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the minimum value
 * @param uiPositionZ the index on the third (z) dimension of which to
 * 	return the minimum value
 * @return the minimum value of the given position in the matrix
 */
doubleFib cMatrix3DInteger::getMinValue( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiPositionZ ) const{
	
	return lMinEntryValue;
}


/**
 * With this method the minimum integer value for a matrix element is returned.
 *
 * @return the minimum integer value for entries in the matrix
 */
longFib cMatrix3DInteger::getMinValueLong() const{
	
	return lMinEntryValue;
}


/**
 * With this method the maximum value for a matrix element is returned.
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the maximum value
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the maximum value
 * @param uiPositionZ the index on the third (z) dimension of which to
 * 	return the maximum value
 * @return the maximum value of the given position in the matrix
 */
doubleFib cMatrix3DInteger::getMaxValue( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiPositionZ ) const{
	
	return lMaxEntryValue;
}


/**
 * With this method the maximum integer value for a matrix element is returned.
 *
 * @return the maximum integer value for entries in the matrix
 */
longFib cMatrix3DInteger::getMaxValueLong() const{
	
	return lMaxEntryValue;
}


/**
 * With this method the minimal difference betwean two values for the
 * matrix element is returned.
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the minimal difference value
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the minimal difference value
 * @param uiPositionZ the index on the third (z) dimension of which to
 * 	return the minimal difference value
 * @return the minimal difference betwean two values for the
 * 	matrix element
 */
doubleFib cMatrix3DInteger::getMinDifference( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiPositionZ ) const{
	
	if ( uiPositionZ < uiBorderIndexZ ){
		return 1.0;
	}
	return 0.0;
}


/**
 * This method returns the maximum index value of the given direction/
 * dimension.
 * All index values for the direction uiDirection should be natural
 * numbers betwean (including) 0 and the returned value.
 *
 * @param uiDirection the direction for which the maximum value should
 * 	be returned (possible values are 0 to 2)
 * @return the maximum index value for the direction uiDirection
 */
unsigned int cMatrix3DInteger::getMaxIndex( const unsigned int uiDirection ) const{
	
	if ( 2 < uiDirection ){
		//no such direction
		return 0;
	}//else
	if ( uiDirection == 0 ){
		return uiBorderIndexX - 1;
	}//else
	if ( uiDirection == 1 ){
		return uiBorderIndexY - 1;
	}//else
	if ( uiDirection == 2 ){
		return uiBorderIndexZ - 1;
	}//else
	//no such dimension -> maximal index 0
	return 0;
}


/**
 * @return the bits per integer entry value in this matrix
 */
unsigned int cMatrix3DInteger::getBitsPerValue() const{
	
	return uiBitsPerEntry;
}


/**
 * This method clears the data form the matrix.
 * All entries of the matrix are set to 0 .
 */
void cMatrix3DInteger::clear(){
	//set the bits of the matrix to 0x0
	const size_t uiBytsPerVectorDim2 = uiBorderIndexX * uiBytsPerEntry;
	
	for ( vector< vector< char* > >::iterator itrSubMatrixDim3 = matrix.begin();
			itrSubMatrixDim3 != matrix.end(); itrSubMatrixDim3++ ){
		
		vector< char* > & vecSubMatrixDim3 = *itrSubMatrixDim3;
		
		for ( vector< char* >::iterator
				itrSubVectorDim2 = vecSubMatrixDim3.begin();
				itrSubVectorDim2 != vecSubMatrixDim3.end(); itrSubVectorDim2++ ){
			
			memset( (*itrSubVectorDim2), 0x0, uiBytsPerVectorDim2 );
		}
	}
}


/**
 * This method checks if the given matrix is equal to this matrix.
 *
 * @param inMatrix the matrix, which should be equal to this matrix
 * @return true if the given matrix is equal to this matrix, else false
 */
bool cMatrix3DInteger::equal( const iMatrix3D & inMatrix ) const{
	
	if ( getName() != inMatrix.getName() ){
		//not the correct matrix type
		return false;
	}
	cMatrix3DInteger * pOtherMatrix = ((cMatrix3DInteger*)(&inMatrix));
	if ( ( uiBorderIndexX != pOtherMatrix->uiBorderIndexX ) ||
			( uiBorderIndexY != pOtherMatrix->uiBorderIndexY ) ||
			( uiBorderIndexZ != pOtherMatrix->uiBorderIndexZ ) ||
			( uiBitsPerEntry != pOtherMatrix->uiBitsPerEntry ) ){
		//the image data don't have the same size
		return false;
	}
	
	const size_t uiBytsPerVectorDim2 = uiBorderIndexX * uiBytsPerEntry;
	
	vector< vector< char* > >::const_iterator
		itrSubMatrixOtherDim3 = pOtherMatrix->matrix.begin();
	for ( vector< vector< char* > >::const_iterator
			itrSubMatrixDim3 = matrix.begin();
			itrSubMatrixDim3 != matrix.end();
			itrSubMatrixDim3++, itrSubMatrixOtherDim3++ ){
		
		const vector< char* > & vecSubMatrixDim3 = *itrSubMatrixDim3;
		vector< char* >::const_iterator
			itrSubVectorOtherDim2 = itrSubMatrixOtherDim3->begin();
		
		for ( vector< char* >::const_iterator
				itrSubVectorDim2 = vecSubMatrixDim3.begin();
				itrSubVectorDim2 != vecSubMatrixDim3.end();
				itrSubVectorDim2++, itrSubVectorOtherDim2++ ){
			
			if ( memcmp( (*itrSubVectorDim2), (*itrSubVectorOtherDim2),
					uiBytsPerVectorDim2 ) != 0 ){
				//the matrix line is different
				return false;
			}//else matrix line is equal -> check next matrix line
		}//end for dimension 2
	}//end for dimension 3
	
	return true;
}


/**
 * This function evalues the derivate of the matrix in the given
 * direction / dimension.
 *
 * @param uiDirection the direction in which the derivation should
 * 	be evalued (possible values are 0 to 2)
 * @return a pointer to the derivate matrix in the given direction of
 * 	this matrix, or NULL if non exists
 * 	Beware: You have to care that the returnd object is deleted.
 */
cMatrix3DInteger * cMatrix3DInteger::evalueDerivate(
		const unsigned int uiDirection ) const{
	
	cMatrix3DInteger * pDerivateMatrix = NULL;
	if ( uiDirection == 0 ){
		//evalue derivation in first (1. or x) dimension
		if ( uiBorderIndexX <= 1 ){
			//just one line in dimension 1 -> can't evalue derivate
			return NULL;
		}
		const unsigned int uiMaxIndexDimX = uiBorderIndexX - 2;
		
		pDerivateMatrix = getEmptyMatrixForDerivate( uiMaxIndexDimX,
			uiBorderIndexY - 1, uiBorderIndexZ - 1, uiBitsPerEntry + 1 );
		const unsigned int uiBytsPerEntryDerivate =
			pDerivateMatrix->uiBytsPerEntry;
		
		const unsigned int uiDeltaBytsEntrySign = uiBytsPerEntry - 1;
		
		char * pEntry;
		char * pEntrySign;
		char * pEntryDerivate;
		longFib lLastValue = 0;
		longFib lActualValue = 0;
		vector< vector< char* > >::iterator itrSubMatrixDerivateDim3 =
			pDerivateMatrix->matrix.begin();
		for ( vector< vector< char* > >::const_iterator itrSubMatrixDim3 = matrix.begin();
				itrSubMatrixDim3 != matrix.end();
				itrSubMatrixDim3++, itrSubMatrixDerivateDim3++ ){
			
			const vector< char* > & vecSubMatrixDim3 = *itrSubMatrixDim3;
			vector< char* >::iterator
					itrSubVectorDerivateDim2 = itrSubMatrixDerivateDim3->begin();
					
			for ( vector< char* >::const_iterator
					itrSubVectorDim2 = vecSubMatrixDim3.begin();
					itrSubVectorDim2 != vecSubMatrixDim3.end();
					itrSubVectorDim2++, itrSubVectorDerivateDim2++ ){
				
				pEntry = (*itrSubVectorDim2);
				pEntrySign = pEntry + uiDeltaBytsEntrySign;
				lLastValue = ( ((*pEntrySign) & 0x80) == 0x80 )? -1 : 0;
				memcpy( &lLastValue, pEntry, uiBytsPerEntry );
				
				pEntryDerivate = (*itrSubVectorDerivateDim2);
				
				for ( unsigned int uiActualIndexDim1 = 0;
						uiActualIndexDim1 <= uiMaxIndexDimX;
						uiActualIndexDim1++ ){
					//go to next entry
					pEntry += uiBytsPerEntry;
					pEntrySign += uiBytsPerEntry;
					
					lActualValue = ( ((*pEntrySign) & 0x80) == 0x80 )? -1 : 0;
					memcpy( &lActualValue, pEntry, uiBytsPerEntry );
					
					//evale derivate value
					lLastValue = lActualValue - lLastValue;
					//set evalued value
					memcpy( pEntryDerivate, &lLastValue, uiBytsPerEntryDerivate );
					
					//actual value is now last value
					lLastValue = lActualValue;
					//go to next value
					pEntryDerivate += uiBytsPerEntryDerivate;
				}//end for all values in x direction
			}//end for all index in y direction
		}//end for all index in z direction
		
	}else if ( uiDirection == 1 ){
		//evalue derivation in second (2. or y) dimension
		if ( uiBorderIndexY <= 1 ){
			//just one line in dimension 2 -> can't evalue derivate
			return NULL;
		}
		const unsigned int uiMaxIndexDimY = uiBorderIndexY - 2;
		
		pDerivateMatrix = getEmptyMatrixForDerivate( uiBorderIndexX - 1,
			uiMaxIndexDimY, uiBorderIndexZ - 1, uiBitsPerEntry + 1 );
		const unsigned int uiBytsPerEntryDerivate =
			pDerivateMatrix->uiBytsPerEntry;
		
		const unsigned int uiDeltaBytsEntrySign = uiBytsPerEntry - 1;
		
		char * pEntry;
		char * pEntrySign;
		char * pNextEntry;
		char * pNextEntrySign;
		char * pEntryDerivate;
		longFib lActualValue;
		longFib lNextValue;
		
		vector< vector< char* > >::const_iterator itrSubMatrixDerivateDim3 =
			pDerivateMatrix->matrix.begin();
		for ( vector< vector< char* > >::const_iterator
				itrSubMatrixDim3 = matrix.begin();
				itrSubMatrixDim3 != matrix.end();
				itrSubMatrixDim3++, itrSubMatrixDerivateDim3++ ){
			
			const vector< char* > & vecSubMatrixDim3 = *itrSubMatrixDim3;
			vector< char* >::const_iterator
					itrSubVectorDerivateDim2 = itrSubMatrixDerivateDim3->begin();
			
			vector< char* >::const_iterator
					itrSubVectorDim2Next = vecSubMatrixDim3.begin();
			itrSubVectorDim2Next++;
			for ( vector< char* >::const_iterator
					itrSubVectorDim2 = vecSubMatrixDim3.begin();
					itrSubVectorDim2Next != vecSubMatrixDim3.end();
					itrSubVectorDim2++, itrSubVectorDim2Next++,
					itrSubVectorDerivateDim2++ ){
				
				pEntry = (*itrSubVectorDim2);
				pEntrySign = pEntry + uiDeltaBytsEntrySign;
				pNextEntry = (*itrSubVectorDim2Next);
				pNextEntrySign = pNextEntry + uiDeltaBytsEntrySign;
				
				pEntryDerivate = (*itrSubVectorDerivateDim2);
				
				for ( unsigned int uiActualIndexDim1 = 0;
						uiActualIndexDim1 < uiBorderIndexX;
						uiActualIndexDim1++ ){
					
					lActualValue = ( ((*pEntrySign) & 0x80) == 0x80 )? -1 : 0;
					memcpy( &lActualValue, pEntry, uiBytsPerEntry );
					
					lNextValue = ( ((*pNextEntrySign) & 0x80) == 0x80 )? -1 : 0;
					memcpy( &lNextValue, pNextEntry, uiBytsPerEntry );
					
					//evale derivate value
					lNextValue -= lActualValue;
					//set evalued value
					memcpy( pEntryDerivate, &lNextValue, uiBytsPerEntryDerivate );
					
					//go to next entry
					pEntry += uiBytsPerEntry;
					pEntrySign += uiBytsPerEntry;
					pNextEntry += uiBytsPerEntry;
					pNextEntrySign += uiBytsPerEntry;
					pEntryDerivate += uiBytsPerEntryDerivate;
				}//end for all values in x direction
			}//end for all index in y direction
		}//end for all index in z direction
		
	}else if ( uiDirection == 2 ){
		//evalue derivation in third (3. or z) dimension
		if ( uiBorderIndexZ <= 1 ){
			//just one line in dimension 3 -> can't evalue derivate
			return NULL;
		}
		const unsigned int uiMaxIndexDimZ = uiBorderIndexZ - 2;
		
		pDerivateMatrix = getEmptyMatrixForDerivate( uiBorderIndexX - 1,
			uiBorderIndexY - 1, uiMaxIndexDimZ, uiBitsPerEntry + 1 );
		const unsigned int uiBytsPerEntryDerivate =
			pDerivateMatrix->uiBytsPerEntry;
		
		const unsigned int uiDeltaBytsEntrySign = uiBytsPerEntry - 1;
		
		char * pEntry;
		char * pEntrySign;
		char * pNextEntry;
		char * pNextEntrySign;
		char * pEntryDerivate;
		longFib lActualValue;
		longFib lNextValue;
		
		vector< vector< char* > >::const_iterator itrSubMatrixDerivateDim3 =
			pDerivateMatrix->matrix.begin();
		vector< vector< char* > >::const_iterator
			itrSubMatrixDim3Next = matrix.begin();
		itrSubMatrixDim3Next++;
		for ( vector< vector< char* > >::const_iterator
				itrSubMatrixDim3 = matrix.begin();
				itrSubMatrixDim3Next != matrix.end();
				itrSubMatrixDim3++, itrSubMatrixDim3Next++,
				itrSubMatrixDerivateDim3++ ){
			
			const vector< char* > & vecSubMatrixDim3 = *itrSubMatrixDim3;
			vector< char* >::const_iterator
					itrSubVectorDerivateDim2 = itrSubMatrixDerivateDim3->begin();
			
			vector< char* >::const_iterator
					itrSubVectorDim2Next = itrSubMatrixDim3Next->begin();
			for ( vector< char* >::const_iterator
					itrSubVectorDim2 = vecSubMatrixDim3.begin();
					itrSubVectorDim2 != vecSubMatrixDim3.end();
					itrSubVectorDim2++, itrSubVectorDim2Next++,
					itrSubVectorDerivateDim2++ ){
				
				pEntry = (*itrSubVectorDim2);
				pEntrySign = pEntry + uiDeltaBytsEntrySign;
				pNextEntry = (*itrSubVectorDim2Next);
				pNextEntrySign = pNextEntry + uiDeltaBytsEntrySign;
				
				pEntryDerivate = (*itrSubVectorDerivateDim2);
				
				for ( unsigned int uiActualIndexDim1 = 0;
						uiActualIndexDim1 < uiBorderIndexX;
						uiActualIndexDim1++ ){
					
					lActualValue = ( ((*pEntrySign) & 0x80) == 0x80 )? -1 : 0;
					memcpy( &lActualValue, pEntry, uiBytsPerEntry );
					
					lNextValue = ( ((*pNextEntrySign) & 0x80) == 0x80 )? -1 : 0;
					memcpy( &lNextValue, pNextEntry, uiBytsPerEntry );
					
					//evale derivate value
					lNextValue -= lActualValue;
					//set evalued value
					memcpy( pEntryDerivate, &lNextValue, uiBytsPerEntryDerivate );
					
					//go to next entry
					pEntry += uiBytsPerEntry;
					pEntrySign += uiBytsPerEntry;
					pNextEntry += uiBytsPerEntry;
					pNextEntrySign += uiBytsPerEntry;
					pEntryDerivate += uiBytsPerEntryDerivate;
				}//end for all values in x direction
			}//end for all index in y direction
		}//end for all index in z direction
		
	}//else not a valid direction
	return pDerivateMatrix;
}


/**
 * This method returns a empty matrix for storing the derivate of this
 * matrix to.
 * With this method child classes of this class can use the same
 * evalueDerivate() method and overwrite this method for the respectivly
 * cMatrix3DInteger child they need for ther derivation.
 *
 * @see evalueDerivate()
 * @param uiMaxIndexX the maximal index for the first (1. or x)
 * 	dimension for the to create martrix; All index values in the
 * 	first (1. or x) dimension are positiv (including 0) natural numbers
 * 	lower equal uiMaxIndexX .
 * 	@see uiBorderIndexX
 * @param uiMaxIndexY the maximal index for the second (2. or y)
 * 	dimension for the to create martrix; All index values in the
 * 	second (2. or y) dimension are positiv (including 0) natural numbers
 * 	lower equal uiMaxIndexY .
 * 	@see uiBorderIndexY
 * @param uiMaxIndexZ the maximal index for the third (3. or z)
 * 	dimension for the to create martrix; All index values in the
 * 	third (3. or z) dimension are positiv (including 0) natural numbers
 * 	lower equal uiMaxIndexZ .
 * 	@see uiBorderIndexZ
 * @param uiBitsPerValue The bits per integer entry value in the created matrix.
 * 	The entry values in the matrix are in the range from
 * 	-1 * 2^(uiBitsPerEntry - 1) to 2^(uiBitsPerEntry - 1) - 1 .
 * 	@see uiBitsPerEntry
 * @return a pointer to the cMatrix3DInteger (or child of it) matrix with
 * 	the given size, to store the derivate of this matrix to
 * 	Beware: You have to care that the returnd object is deleted.
 */
cMatrix3DInteger * cMatrix3DInteger::getEmptyMatrixForDerivate(
		const unsigned int uiMaxIndexX, const unsigned int uiMaxIndexY,
		const unsigned int uiMaxIndexZ, const unsigned int uiBitsPerValue ) const{
	
	return new cMatrix3DInteger( uiMaxIndexX, uiMaxIndexY, uiMaxIndexZ,
		uiBitsPerValue );
}


/**
 * @return the minimum possible entry value for the given bit per entry:
 * 	-1 * 2^(uiBitsPerEntry - 1)
 * 	@see uiBitsPerEntry
 * 	@see lMinEntryValue
 */
longFib cMatrix3DInteger::evalueMinValue( const unsigned int uiBitsPerEntry ){
	
	if ( uiBitsPerEntry == 0 ){
		//no bits -> minimum value is 0
		return 0;
	}
	longFib lMinValue = -1;
	unsigned char * pMinValue = ((unsigned char *)(&lMinValue)) +
		(( uiBitsPerEntry - 1 ) / 8);
	const unsigned int uiBytsPerEntry = (uiBitsPerEntry - 1 ) / 8 + 1;
	
	for ( unsigned int uiActualByte = 1; uiActualByte < uiBytsPerEntry;
			uiActualByte++ ){
		
		(*pMinValue) = 0x00;
		pMinValue++;
	}
	(*pMinValue) = 0x80 >> ( ( 8 - ( uiBitsPerEntry % 8 ) ) % 8 );
	
	return lMinValue;
}


/**
 * @return the maximum possible entry value for the given bit per entry:
 * 	 2^(uiBitsPerEntry - 1) - 1
 * 	@see uiBitsPerEntry
 * 	@see lMaxEntryValue
 */
longFib cMatrix3DInteger::evalueMaxValue( const unsigned int uiBitsPerEntry ){
	
	if ( uiBitsPerEntry == 0 ){
		//no bits -> maximum value is 0
		return 0;
	}
	longFib lMaxValue = 0;
	unsigned char * pMaxValue = ((unsigned char *)(&lMaxValue));
	const unsigned int uiBytsPerEntry = (uiBitsPerEntry - 1 ) / 8 + 1;
	
	for ( unsigned int uiActualByte = 1; uiActualByte < uiBytsPerEntry;
			uiActualByte++ ){
		
		(*pMaxValue) = 0xFF;
		pMaxValue++;
	}
	(*pMaxValue) = 0x7F >> ( ( 8 - ( uiBitsPerEntry % 8 ) ) % 8 );
	
	return lMaxValue;
}






