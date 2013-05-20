
//TODO check

/**
 * @file tMatrix3D
 * file name: tMatrix3D.cpp
 * @author Betti Oesterholz
 * @date 07.03.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for testing the iMatrix3D methods.
 *
 * Copyright (C) @c GPL3 2013 Betti Oesterholz
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
 * This test is for testing mainly the convertToFib() method of the child
 * classes of iMatrix3D.
 * It will test if the iConvertMatrixToFib::convertToFib()
 * method converts given areas into a  equivalent Fib object.
 * @see iConvertMatrixToFib::convertToFib()
 * It will also test the iMatrix3D methods.
 * @see iMatrix3D
 *
 * This test is for testing the iMatrix3D methods.
 *
 *
 * call: tMatrix3D [MAX_ITERATION]
 *
 * parameters:
 * 	MAX_ITERATION
 * 		The number of iterators for the random tests (test with given
 * 		parameters for convertToTiles()).
 * 		Just works with the DIR_TESTDATA parameter given.
 *
 *
 * Methods tested:
 * 	- iMatrix3D * clone() const;
 * 	- string getName() const;
 * 	- tErrorValue setValue( const doubleFib dValue, const unsigned int uiPositionX = 0, const unsigned int uiPositionY = 0, const unsigned int uiPositionZ = 0 );
 * 	- tErrorValue setValue( const longFib lValue, const unsigned int uiPositionX = 0, const unsigned int uiPositionY = 0, const unsigned int uiPositionZ = 0 );
 * 	- doubleFib getValue( const unsigned int uiPositionX = 0, const unsigned int uiPositionY = 0, const unsigned int uiPositionZ = 0 ) const;
 * 	- doubleFib getMinValue( const unsigned int uiPositionX = 0, const unsigned int uiPositionY = 0, const unsigned int uiPositionZ = 0 ) const;
 * 	- doubleFib getMaxValue( const unsigned int uiPositionX = 0, const unsigned int uiPositionY = 0, const unsigned int uiPositionZ = 0 ) const;
 * 	- unsigned int getMaxIndex( const unsigned int uiDirection = 0 ) const;
 * 	- void clear();
 * 	- bool equal( const iMatrix3D &matrix ) const;
 * 	- bool operator==( const iMatrix3D &matrix ) const;
 * 	- iMatrix3D * evalueDerivate( const unsigned int uiDirection = 0 ) const;
 *
 */
/*
History:
07.03.2013  Oesterholz  created
*/


#include "version.h"
#include "fibDatatyps.h"

#include "iMatrix3D.h"
#include "cMatrix3DInteger.h"
#include "cMatrix3DIntegerScaledDim3.h"
#include "cEvalueSimpleRGBA255.h"
#include "cEvalueSimpleRGBA255Scaled.h"


#include <string>
#include <utility>
#include <list>
#include <vector>
#include <algorithm>
#include <cmath>


using namespace fib;
using namespace std;


unsigned long MAX_ITERATION = 256;


enum tActualClass {
	C_MATRIX_3_D_INTEGER = 0,
	C_EVALUE_SIMPLE_RGBA255 = 1,
	C_EVALUE_SIMPLE_RGBA255_SCALED = 2,
	C_MATRIX_3_D_INTEGER_SCALED_DIM_3 = 3
} actualClass;


iMatrix3D * getActualClass();
iMatrix3D * copyMatrix( iMatrix3D * pMatrixToCopy );
string getActualClassName();

int testMatrix3DMethods( unsigned long &ulTestphase );



int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test
	int iReturn = 0;//return value of the test; the number of occured Errors
	
	srand( time(NULL) );
	
	cout<<endl<<"Running Test for the iMatrix3D methods"<<endl;
	cout<<      "============================================"<<endl;
	cout<<      "============================================"<<endl;
	
	if ( 1 < argc ){
		//two parameters given; read parameter iterators
		MAX_ITERATION = atol( argv[1] );
		if ( MAX_ITERATION < 1 ){
			MAX_ITERATION = 1;
		}
	}
	cout<<endl<<"Number of maximal iterators is "<<MAX_ITERATION<<endl;
	
	
//TODO enlarge tested
	for ( unsigned int uiActualClass = 0;
			uiActualClass <= 3; uiActualClass++ ){
		
		switch ( uiActualClass ){
			case 0:
				actualClass = C_MATRIX_3_D_INTEGER;
			break;
			case 1:
				actualClass = C_EVALUE_SIMPLE_RGBA255;
			break;
			case 2:
				actualClass = C_EVALUE_SIMPLE_RGBA255_SCALED;
			break;
			case 3:
				actualClass = C_MATRIX_3_D_INTEGER_SCALED_DIM_3;
			break;
		}
		
		
		cout<<endl<<"Running Test for the "<<getActualClassName()<<" methods"<<endl;
		cout<<      "=============================================="<<endl;
		
		//test the iMatrix3D methods
		const unsigned int iReturnTestCase = testMatrix3DMethods( ulTestphase );
		
		if ( iReturnTestCase == 0 ){
		
			cout<<endl<<endl<<"Test for "<<getActualClassName()<<
				" successfull: no errors occoured"<<endl;
		}else{
			cerr<<endl<<endl<<"Test for "<<getActualClassName()<<" failed: "<<
				iReturnTestCase<<" errors occoured"<<endl;
			iReturn += iReturnTestCase;
		}
	}
	
	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	
	return iReturn;
}



/**
 * This functions returns a pointer to the actual class to test.
 *
 * @param uiMaxIndexX the maximal index for the first (1. or x)
 * 	dimension; All index values in the first (1. or x) dimension are
 * 	positiv  (including 0) natural numbers lower equal uiMaxIndexX .
 * 	@see uiBorderIndexX
 * @param uiMaxIndexY the maximal index for the second (2. or y)
 * 	dimension; All index values in the first (1. or x) dimension are
 * 	positiv  (including 0) natural numbers lower equal uiMaxIndexY .
 * 	@see uiBorderIndexY
 * @param uiMaxIndexZ the maximal index for the third (3. or z)
 * 	dimension; All index values in the first (1. or x) dimension are
 * 	positiv  (including 0) natural numbers lower equal uiMaxIndexZ .
 * 	@see uiBorderIndexZ
 * @return pointer to the actual class to test
 * 	Beware: You have to delete the class after usage.
 */
iMatrix3D * getActualClass( const unsigned int uiMaxIndexX,
		const unsigned int uiMaxIndexY, const unsigned int uiMaxIndexZ ){
	
	switch ( actualClass ){
		case C_MATRIX_3_D_INTEGER:
			cout<<"cMatrix3DInteger( "<<uiMaxIndexX<<", "<<uiMaxIndexY<<
				", "<<uiMaxIndexZ<<", 8 );"<<endl;
			return new cMatrix3DInteger(
				uiMaxIndexX, uiMaxIndexY, uiMaxIndexZ, 8 );
		break;
		case C_EVALUE_SIMPLE_RGBA255:
			cout<<"cEvalueSimpleRGBA255( "<<uiMaxIndexX<<", "<<uiMaxIndexY<<" );"<<endl;
			return new cEvalueSimpleRGBA255( uiMaxIndexX, uiMaxIndexY );
		break;
		case C_EVALUE_SIMPLE_RGBA255_SCALED:
			cout<<"cEvalueSimpleRGBA255Scaled( "<<uiMaxIndexX<<", "<<uiMaxIndexY<<" );"<<endl;
			return new cEvalueSimpleRGBA255Scaled(
				uiMaxIndexX, uiMaxIndexY );
		break;
		case C_MATRIX_3_D_INTEGER_SCALED_DIM_3:
			cout<<"cMatrix3DIntegerScaledDim3( "<<uiMaxIndexX<<", "<<uiMaxIndexY<<", "<<uiMaxIndexZ<<" );"<<endl;
			return new cMatrix3DIntegerScaledDim3(
				uiMaxIndexX, uiMaxIndexY, uiMaxIndexZ, 8 );
		break;
	}
	
	return new cMatrix3DInteger( uiMaxIndexX, uiMaxIndexY, uiMaxIndexZ, 8);
}


/**
 * This functions returns a pointer to a copy of the given object.
 * The object should have the type of the actual class.
 *
 * @param pMatrixToCopy the class to copy
 * @return pointer to the copy of the given object
 * 	Beware: You have to delete the class after usage.
 */
iMatrix3D * copyMatrix( iMatrix3D * pMatrixToCopy ){
	
	switch ( actualClass ){
		case C_MATRIX_3_D_INTEGER:
			return new cMatrix3DInteger( *((cMatrix3DInteger*)(pMatrixToCopy)) );
		break;
		case C_EVALUE_SIMPLE_RGBA255:
			return new cEvalueSimpleRGBA255(
				*((cEvalueSimpleRGBA255*)pMatrixToCopy) );
		break;
		case C_EVALUE_SIMPLE_RGBA255_SCALED:
			return new cEvalueSimpleRGBA255Scaled(
				*(dynamic_cast<cEvalueSimpleRGBA255Scaled*>(pMatrixToCopy) ) );
		break;
		case C_MATRIX_3_D_INTEGER_SCALED_DIM_3:
			return new cMatrix3DIntegerScaledDim3(
				*(dynamic_cast<cMatrix3DIntegerScaledDim3*>(pMatrixToCopy) ) );
		break;
	}
	
	return getActualClass( 0, 0, 0 );
}


/**
 * This functions returns the actual class name.
 *
 * @return the actual class name
 */
string getActualClassName(){
	
	switch ( actualClass ){
		case C_MATRIX_3_D_INTEGER:
			return "cMatrix3DInteger";
		break;
		case C_EVALUE_SIMPLE_RGBA255:
			return "cEvalueSimpleRGBA255";
		break;
		case C_EVALUE_SIMPLE_RGBA255_SCALED:
			return "cEvalueSimpleRGBA255Scaled";
		break;
		case C_MATRIX_3_D_INTEGER_SCALED_DIM_3:
			return "cMatrix3DIntegerScaledDim3";
		break;
	}
	
	return "";
}


/**
 * @param pMatrix a pointer to the matix for which to return the minimum
 * 	number
 * @return the minimum long value for the actual matrix
 */
longFib getMinLongValue( iMatrix3D * pMatrix ){
	
	switch ( actualClass ){
		case C_MATRIX_3_D_INTEGER:
		case C_MATRIX_3_D_INTEGER_SCALED_DIM_3:
			return -128;
		break;
		case C_EVALUE_SIMPLE_RGBA255:
		case C_EVALUE_SIMPLE_RGBA255_SCALED:
			return 0;
		break;
	}
	
	return 0;
}


/**
 * @param pMatrix a pointer to the matix for which to return the maximum
 * 	number
 * @return the maximum long value for the actual matrix
 */
longFib getMaxLongValue( iMatrix3D * pMatrix ){
	
	switch ( actualClass ){
		case C_MATRIX_3_D_INTEGER:
		case C_MATRIX_3_D_INTEGER_SCALED_DIM_3:
			return 127;
		break;
		case C_EVALUE_SIMPLE_RGBA255:
		case C_EVALUE_SIMPLE_RGBA255_SCALED:
			return 255;
		break;
	}
	
	return 255;
}


/**
 * @param pMatrix a pointer to the matix for which to return the minimum
 * 	number
 * @return the minimum value for the actual matrix
 */
doubleFib getMinValue( iMatrix3D * pMatrix ){
	
	return getMinLongValue( pMatrix );
}


/**
 * @param pMatrix a pointer to the matix for which to return the maximum
 * 	number
 * @return the maximum value for the actual matrix
 */
doubleFib getMaxValue( iMatrix3D * pMatrix ){
	
	return getMaxLongValue( pMatrix );
}


/**
 * @param pMatrix a pointer to the matix for which to generate the number
 * @return generates a random long number
 */
longFib generateRandLongNumber( iMatrix3D * pMatrix ){
	
	const longFib lMinValue = getMinLongValue( pMatrix );
	return rand() % ( getMaxLongValue( pMatrix ) + 1 - lMinValue ) + lMinValue;
}


/**
 * @param pMatrix a pointer to the matix for which to generate the number
 * @return generates a random double number
 */
doubleFib generateRandDoubleNumber( iMatrix3D * pMatrix ){
	
	return generateRandLongNumber( pMatrix );
}




/**
 * This method prints the matrix to the given stream.
 *
 * @param streamToPrintTo the stream where to print the matrix to
 * @param pMatrix a pointer to the matrix to print
 */
void printMatrix( ostream & streamToPrintTo, iMatrix3D * pMatrix ){
	
	const unsigned int uiMaxIndexX = pMatrix->getMaxIndex( 0 );
	const unsigned int uiMaxIndexY = pMatrix->getMaxIndex( 1 );
	const unsigned int uiMaxIndexZ = pMatrix->getMaxIndex( 2 );
	
	streamToPrintTo<<"Matrix of type "<<getActualClassName()<<
		" and size ("<<uiMaxIndexX<<", "<<uiMaxIndexY<<", "<<uiMaxIndexZ<<") :"<<endl;
	
	for ( unsigned int indexX = 0; indexX <= uiMaxIndexX; indexX++ ){
		for ( unsigned int indexY = 0; indexY <= uiMaxIndexY; indexY++ ){
			streamToPrintTo<<"(";
			for ( unsigned int indexZ = 0; indexZ <= uiMaxIndexZ; indexZ++ ){
		
				streamToPrintTo<<(pMatrix->getValue( indexX, indexY, indexZ ))<<",";
			}//end for index z
			streamToPrintTo<<"), ";
		}//end for index y
		streamToPrintTo<<endl;
	}//end for index x
}


/**
 * @param dValue the value to check
 * @return true if the value is not a number, else false
 */
inline bool own_isnan( doubleFib dValue ){
    return dValue != dValue;
}


/**
 * @param dValue the value to check
 * @return true if the value is infinity, else false
 */
inline bool own_isinf( doubleFib dValue ){
    return ( ( dValue == INFINITY ) || ( dValue == -INFINITY ) );
}


/**
 * This function compares two values with a given savety boundery.
 *
 * @param dValue1 the first value to compare
 * @param dValue2 the second value to compare
 * @return true if the values are very simular
 */
bool isEqual( doubleFib dValue1, doubleFib dValue2 ){

	if ( own_isnan( dValue1 ) || own_isnan( dValue2 ) ){
		if ( own_isnan( dValue1 ) && own_isnan( dValue2 ) ){
			return true;
		}
		return false;
	}
	if ( own_isinf( dValue1 ) || own_isinf( dValue2 ) ){
		if ( own_isinf( dValue1 ) && own_isinf( dValue2 ) ){
			return true;
		}
		return false;
	}
	
	const doubleFib dSaveBoundery1 = abs( dValue1 / 1000000.0 );
	const doubleFib dSaveBoundery2 = abs( dValue2 / 1000000.0 );
	const doubleFib dSaveBoundery  = min( dSaveBoundery1, dSaveBoundery2 );
	
	if ( ( dValue1 - dSaveBoundery <= dValue2 ) &&
			( dValue2 <= dValue1 + dSaveBoundery ) ){
		return true;
	}
	return false;
}


/**
 * This method prints the matrix to the given stream.
 *
 * @param pMatrix a pointer to the matrix to print
 * @return 
 */
unsigned int compareMatrixPoints( iMatrix3D * pMatrix,
		const unsigned int uiMaxIndexX,
		const unsigned int uiMaxIndexY,
		const unsigned int uiMaxIndexZ,
		const vector< vector< vector< longFib > > > & vecElements ){
	
	unsigned int uiErrors = 0;
	
	if ( pMatrix->getMaxIndex( 0 ) != uiMaxIndexX ){
		cerr<<"Error: The maximal index for the first dimension is "<<
			pMatrix->getMaxIndex( 0 )<<", but should be "<<uiMaxIndexX<<endl;
		uiErrors++;
	}
	if ( pMatrix->getMaxIndex( 1 ) != uiMaxIndexY ){
		cerr<<"Error: The maximal index for the second dimension is "<<
			pMatrix->getMaxIndex( 1 )<<", but should be "<<uiMaxIndexY<<endl;
		uiErrors++;
	}
	if ( pMatrix->getMaxIndex( 2 ) != uiMaxIndexZ ){
		cerr<<"Error: The maximal index for the third dimension is "<<
			pMatrix->getMaxIndex( 2 )<<", but should be "<<uiMaxIndexZ<<endl;
		uiErrors++;
	}
	
	for ( unsigned int indexX = 0; indexX <= uiMaxIndexX; indexX++ ){
		for ( unsigned int indexY = 0; indexY <= uiMaxIndexY; indexY++ ){
			for ( unsigned int indexZ = 0; indexZ <= uiMaxIndexZ; indexZ++ ){
				
				if ( vecElements[ indexX ][ indexY ][ indexZ ] !=
						roundToLongFib( pMatrix->getValue( indexX, indexY, indexZ ) ) ){
					
					cerr<<"Error: The value in the matrix for the index ("<<
						indexX<<", "<<indexY<<", "<<indexZ<<
						") is "<<pMatrix->getValue( indexX, indexY, indexZ )<<
						", but should be "<<
						vecElements[ indexX ][ indexY ][ indexZ ]<<endl;
					uiErrors++;
				}
			}//end for index z
		}//end for index y
	}//end for index x
	
	return uiErrors;
}


/**
 * This function tests the equal method of the matrix.
 *
 * Methods tested:
 * 	- bool equal( const iMatrix3D &matrix ) const;
 * 	- bool operator==( const iMatrix3D &matrix ) const;
 *
 * @param pMatrix1 a pointer to the first matrix to compare with
 * @param pMatrix2 a pointer to the second matrix to compare with
 * @return the number of error occured in the test
 */
unsigned int testCompareEqual(  iMatrix3D * pMatrix1,
		 iMatrix3D * pMatrix2 ){
	
	unsigned int iReturn = 0;
	
	if ( ! pMatrix1->equal( *pMatrix2 ) ){
		cerr<<"Error: The matrix are not equal (equal() method), but should be."<<endl;
		iReturn++;
	}
	if ( ! ( (*pMatrix2) == (*pMatrix1) ) ){
		cerr<<"Error: The matrix are not equal ( operator==() ), but should be."<<endl;
		iReturn++;
	}
	if ( iReturn != 0 ){
		
		cerr<<endl<<"Matrix 1:"<<endl;
		printMatrix( cerr, pMatrix1 );
		cerr<<endl<<"Matrix 2:"<<endl;
		printMatrix( cerr, pMatrix2 );
		cerr<<endl;
	}
	
	return iReturn;
}


/**
 * This function tests the equal method of the matrix for not equal.
 *
 * Methods tested:
 * 	- bool equal( const iMatrix3D &matrix ) const;
 * 	- bool operator==( const iMatrix3D &matrix ) const;
 *
 * @param pMatrix1 a pointer to the first matrix to compare with
 * @param pMatrix2 a pointer to the second matrix to compare with
 * @return the number of error occured in the test
 */
unsigned int testCompareNotEqual( iMatrix3D * pMatrix1,
		 iMatrix3D * pMatrix2 ){
	
	unsigned int iReturn = 0;
	
	if ( pMatrix1->equal( *pMatrix2 ) ){
		cerr<<"Error: The matrix are equal (equal() method), but should not be."<<endl;
		iReturn++;
	}
	if ( ( (*pMatrix2) == (*pMatrix1) ) ){
		cerr<<"Error: The matrix are equal ( operator==() ), but should not be."<<endl;
		iReturn++;
	}
	if ( iReturn != 0 ){
		
		cerr<<endl<<"Matrix 1:"<<endl;
		printMatrix( cerr, pMatrix1 );
		cerr<<endl<<"Matrix 2:"<<endl;
		printMatrix( cerr, pMatrix2 );
		cerr<<endl;
	}
	
	return iReturn;
}



/**
 * This function tests the iMatrix3D methods.
 *
 * Methods tested:
 * 	- iMatrix3D * clone() const;
 * 	- string getName() const;
 * 	- tErrorValue setValue( const doubleFib dValue, const unsigned int uiPositionX = 0, const unsigned int uiPositionY = 0, const unsigned int uiPositionZ = 0 );
 * 	- tErrorValue setValue( const longFib lValue, const unsigned int uiPositionX = 0, const unsigned int uiPositionY = 0, const unsigned int uiPositionZ = 0 );
 * 	- doubleFib getValue( const unsigned int uiPositionX = 0, const unsigned int uiPositionY = 0, const unsigned int uiPositionZ = 0 ) const;
 * 	- doubleFib getMinValue( const unsigned int uiPositionX = 0, const unsigned int uiPositionY = 0, const unsigned int uiPositionZ = 0 ) const;
 * 	- doubleFib getMaxValue( const unsigned int uiPositionX = 0, const unsigned int uiPositionY = 0, const unsigned int uiPositionZ = 0 ) const;
 * 	- unsigned int getMaxIndex( const unsigned int uiDirection = 0 ) const;
 * 	- void clear();
 * 	- bool equal( const iMatrix3D &matrix ) const;
 * 	- bool operator==( const iMatrix3D &matrix ) const;
 * 	- iMatrix3D * evalueDerivate( const unsigned int uiDirection = 0 ) const;
 *
 * @param ulTestphase a reference to the number for the test phase
 * @return the number of errors occured in the test
 */
int testMatrix3DMethods( unsigned long &ulTestphase ){
	
	int iReturn = 0;//return value of the test; the number of occured errors
	
	unsigned int uiMaxIndexX = rand() % 64;
	unsigned int uiMaxIndexY = rand() % 64;
	unsigned int uiMaxIndexZ = 3;
	
	iMatrix3D * pMatrix = getActualClass( uiMaxIndexX, uiMaxIndexY, uiMaxIndexZ );
	const iMatrix3D * pMatrixConst = pMatrix;
	
	vector< vector< vector< longFib > > > vecCorrectValues( uiMaxIndexX + 1,
		vector< vector< longFib > >( uiMaxIndexY + 1, vector< longFib >(
			uiMaxIndexZ + 1, 0 ) ) );
	
	{
		if( compareMatrixPoints( pMatrix,
				uiMaxIndexX, uiMaxIndexY, uiMaxIndexZ, vecCorrectValues ) != 0 ){
			cerr<<"Error: The matrix points are not correct."<<endl;
			printMatrix( cerr, pMatrix );
			iReturn++;
		}
		//check getName()
		if ( getActualClassName() == pMatrixConst->getName() ){
			cout<<"The matrix class name is correctly \""<<
				getActualClassName()<<"\"."<<endl;
		}else{
			cerr<<"Error: The matrix class name is \""<<
				pMatrixConst->getName()<<"\", but should be \""<<
				getActualClassName()<<"\""<<endl;
			iReturn++;
		}
		//check getMaxIndex()
		if ( uiMaxIndexX != pMatrixConst->getMaxIndex( 0 ) ){
			cerr<<"Error: The matrix has as the maximum index \""<<
				pMatrixConst->getMaxIndex( 0 )<<"\", but should be \""<<
				uiMaxIndexX<<"\""<<endl;
			iReturn++;
		}
		if ( uiMaxIndexY != pMatrixConst->getMaxIndex( 1 ) ){
			cerr<<"Error: The matrix has as the maximum index \""<<
				pMatrixConst->getMaxIndex( 1 )<<"\", but should be \""<<
				uiMaxIndexY<<"\""<<endl;
			iReturn++;
		}
		if ( uiMaxIndexZ != pMatrixConst->getMaxIndex( 2 ) ){
			cerr<<"Error: The matrix has as the maximum index \""<<
				pMatrixConst->getMaxIndex( 2 )<<"\", but should be \""<<
				uiMaxIndexZ<<"\""<<endl;
			iReturn++;
		}
		//check getMinValue()
		if ( pMatrixConst->getMinValue() < getMinValue( pMatrix ) ){
			cerr<<"Error: The returned minimum value ("<<
				pMatrixConst->getMinValue()<<") is lower as correct minimum value"<<
				getMinValue( pMatrix )<<endl;
			iReturn++;
		}
		//check getMaxValue()
		if ( getMaxValue( pMatrix ) < pMatrixConst->getMaxValue() ){
			cerr<<"Error: The returned maximum value ("<<
				pMatrixConst->getMaxValue()<<") is bigger as correct maximum value"<<
				getMaxValue( pMatrix )<<endl;
			iReturn++;
		}
	}
	
	for ( unsigned int uiActualIteration = 0;
			uiActualIteration < MAX_ITERATION; uiActualIteration++ ){
		cout<<endl;
		//call random change method
		
		if ( rand() % 32 != 0 ){
			//call more probable method
			const unsigned int uiChangeMethod = rand() % 6;
			
			switch ( uiChangeMethod ){
				case 0:{//test setValue( doubleFib dValue );
					const doubleFib dValueToSet = generateRandDoubleNumber( pMatrix );
					const unsigned int uiPositionX = rand() % ( uiMaxIndexX + 1 );
					const unsigned int uiPositionY = rand() % ( uiMaxIndexY + 1 );
					const unsigned int uiPositionZ = rand() % ( uiMaxIndexZ + 1 );
					
					iMatrix3D * pMatrixClone = pMatrix->clone();
					
					cout<<"pMatrix->setValue( dValueToSet="<<dValueToSet<<
						", uiPositionX="<<uiPositionX<<
						", uiPositionY="<<uiPositionY<<
						", uiPositionZ="<<uiPositionZ<<" );"<<endl;
					const iMatrix3D::tErrorValue errorValue = pMatrix->setValue(
						dValueToSet, uiPositionX, uiPositionY, uiPositionZ );
					
					if ( errorValue == iMatrix3D::OK ){
						cout<<"The value was set sucessfull."<<endl;
					}else{
						cerr<<"Error: The value was not set sucessfull (error="<<
							errorValue<<")."<<endl;
						iReturn++;
					}
					cout<<"Compare pMatrix with the original."<<endl;
					if ( ! isEqual( dValueToSet,
							vecCorrectValues[uiPositionX][uiPositionY][uiPositionZ] ) ){
						//a different value set as befor
						cout<<"Compare pMatrix with the original (not equal)."<<endl;
						testCompareNotEqual( pMatrix, pMatrixClone );
					}else{ //the same value set as befor
						cout<<"Compare pMatrix with the original (equal)."<<endl;
						testCompareEqual( pMatrix, pMatrixClone );
					}
					if ( errorValue == iMatrix3D::OK ){
						vecCorrectValues[uiPositionX][uiPositionY][uiPositionZ] =
							roundToLongFib( dValueToSet );
					}
					
					delete pMatrixClone;
				}break;
				case 1:{//test setValue( longFib dValue );
					const longFib lValueToSet = generateRandLongNumber( pMatrix );
					const unsigned int uiPositionX = rand() % ( uiMaxIndexX + 1 );
					const unsigned int uiPositionY = rand() % ( uiMaxIndexY + 1 );
					const unsigned int uiPositionZ = rand() % ( uiMaxIndexZ + 1 );
					
					iMatrix3D * pMatrixClone = pMatrix->clone();
					
					cout<<"pMatrix->setValue( lValueToSet="<<lValueToSet<<
						", uiPositionX="<<uiPositionX<<
						", uiPositionY="<<uiPositionY<<
						", uiPositionZ="<<uiPositionZ<<" );"<<endl;
					const iMatrix3D::tErrorValue errorValue = pMatrix->setValue( lValueToSet,
						uiPositionX, uiPositionY, uiPositionZ );
					
					if ( errorValue == iMatrix3D::OK ){
						cout<<"The value was set sucessfull."<<endl;
					}else{
						cerr<<"Error: The value was not set sucessfull (error="<<
							errorValue<<")."<<endl;
						iReturn++;
					}
					if ( lValueToSet !=
							vecCorrectValues[uiPositionX][uiPositionY][uiPositionZ] ){
						//a different value set as befor
						cout<<"Compare pMatrix with the original (not equal)."<<endl;
						testCompareNotEqual( pMatrix, pMatrixClone );
					}else{ //the same value set as befor
						cout<<"Compare pMatrix with the original (equal)."<<endl;
						testCompareEqual( pMatrix, pMatrixClone );
					}
					if ( errorValue == iMatrix3D::OK ){
						vecCorrectValues[uiPositionX][uiPositionY][uiPositionZ] =
							lValueToSet;
					}
					
					delete pMatrixClone;
				}break;
				
				case 2:{//test setValue( doubleFib dValue ); with not valid value
					const bool bLowerMin = rand() % 2;
					const doubleFib dValueToSet = bLowerMin ?
						( getMinValue( pMatrix ) - 1.0 ):
						( getMaxValue( pMatrix ) + 1.0 );
					const unsigned int uiPositionX = rand() % ( uiMaxIndexX + 1 );
					const unsigned int uiPositionY = rand() % ( uiMaxIndexY + 1 );
					const unsigned int uiPositionZ = rand() % ( uiMaxIndexZ + 1 );
					
					iMatrix3D * pMatrixClone = pMatrix->clone();
					
					cout<<"pMatrix->setValue( dValueToSet="<<dValueToSet<<
						", uiPositionX="<<uiPositionX<<
						", uiPositionY="<<uiPositionY<<
						", uiPositionZ="<<uiPositionZ<<" ); (incorrect value)"<<endl;
					const iMatrix3D::tErrorValue errorValue = pMatrix->setValue( dValueToSet,
						uiPositionX, uiPositionY, uiPositionZ );
					
					if ( bLowerMin ){
						if ( errorValue == iMatrix3D::ERROR_LOWER_MIN_VALUE ){
							cout<<"The value was correctly not set, because it is lower than the minimum value."<<endl;
						}else{
							cerr<<"Error: The value was "<<
								((errorValue == iMatrix3D::OK)?"":"not ")<<
								"set sucessfull, wrong error value "<<
								errorValue<<"."<<endl;
							iReturn++;
						}
					}else{
						if ( errorValue == iMatrix3D::ERROR_GREATER_MAX_VALUE ){
							cout<<"The value was correctly not set, because it is bigger than the maximum value."<<endl;
						}else{
							cerr<<"Error: The value was "<<
								((errorValue == iMatrix3D::OK)?"":"not ")<<
								"set sucessfull, wrong error value "<<
								errorValue<<"."<<endl;
							iReturn++;
						}
					}
					cout<<"Compare pMatrix with the original."<<endl;
					//a different value set as befor
					testCompareEqual( pMatrix, pMatrixClone );
					
					delete pMatrixClone;
				}break;
				case 3:{//test setValue( longFib dValue ); with not valid value
					const bool bLowerMin = rand() % 2;
					const longFib lValueToSet = bLowerMin ?
						( getMinLongValue( pMatrix ) - 1 ):
						( getMaxLongValue( pMatrix ) + 1 );
					const unsigned int uiPositionX = rand() % ( uiMaxIndexX + 1 );
					const unsigned int uiPositionY = rand() % ( uiMaxIndexY + 1 );
					const unsigned int uiPositionZ = rand() % ( uiMaxIndexZ + 1 );
					
					iMatrix3D * pMatrixClone = pMatrix->clone();
					
					cout<<"pMatrix->setValue( lValueToSet="<<lValueToSet<<
						", uiPositionX="<<uiPositionX<<
						", uiPositionY="<<uiPositionY<<
						", uiPositionZ="<<uiPositionZ<<" ); (incorrect value)"<<endl;
					const iMatrix3D::tErrorValue errorValue = pMatrix->setValue( lValueToSet,
						uiPositionX, uiPositionY, uiPositionZ );
					
					if ( bLowerMin ){
						if ( errorValue == iMatrix3D::ERROR_LOWER_MIN_VALUE ){
							cout<<"The value was correctly not set, because it is lower than the minimum value."<<endl;
						}else{
							cerr<<"Error: The value was "<<
								((errorValue == iMatrix3D::OK)?"":"not ")<<
								"set sucessfull, wrong error value "<<
								errorValue<<"."<<endl;
							iReturn++;
						}
					}else{
						if ( errorValue == iMatrix3D::ERROR_GREATER_MAX_VALUE ){
							cout<<"The value was correctly not set, because it is bigger than the maximum value."<<endl;
						}else{
							cerr<<"Error: The value was "<<
								((errorValue == iMatrix3D::OK)?"":"not ")<<
								"set sucessfull, wrong error value "<<
								errorValue<<"."<<endl;
							iReturn++;
						}
					}
					cout<<"Compare pMatrix with the original."<<endl;
					//a different value set as befor
					testCompareEqual( pMatrix, pMatrixClone );
					
					delete pMatrixClone;
				}break;
				
				case 4:{//test setValue( doubleFib dValue ); outside borders
					const bool bDim1IndexToGreat = rand() % 2;
					const bool bDim2IndexToGreat = rand() % 2;
					const bool bDim3IndexToGreat = ( (rand() % 2) == 0 ) ||
						( ( ! bDim1IndexToGreat ) && ( ! bDim2IndexToGreat ) );
					const doubleFib dValueToSet = generateRandDoubleNumber( pMatrix );
					const unsigned int uiPositionX = bDim1IndexToGreat ?
						( uiMaxIndexX + 1 ) : ( rand() % ( uiMaxIndexX + 1 ) );
					const unsigned int uiPositionY = bDim2IndexToGreat ?
						( uiMaxIndexY + 1 ) :  ( rand() % ( uiMaxIndexY + 1 ) );
					const unsigned int uiPositionZ = bDim3IndexToGreat ?
						( uiMaxIndexZ + 1 ) :  ( rand() % ( uiMaxIndexZ + 1 ) );
					
					iMatrix3D * pMatrixClone = pMatrix->clone();
					
					cout<<"pMatrix->setValue( dValueToSet="<<dValueToSet<<
						", uiPositionX="<<uiPositionX<<
						", uiPositionY="<<uiPositionY<<
						", uiPositionZ="<<uiPositionZ<<" ); (outside borders)"<<endl;
					const iMatrix3D::tErrorValue errorValue = pMatrix->setValue( dValueToSet,
						uiPositionX, uiPositionY, uiPositionZ );
					
					if ( bDim1IndexToGreat &&
							(errorValue == iMatrix3D::ERROR_OUTSIDE_INDEX_DIMENSION_1 ) ){
						cout<<"The value was correctly not set, because the index in dimension 1 is to great."<<endl;
					}else if ( bDim2IndexToGreat &&
							(errorValue == iMatrix3D::ERROR_OUTSIDE_INDEX_DIMENSION_2 ) ){
						cout<<"The value was correctly not set, because the index in dimension 2 is to great."<<endl;
					}else if ( bDim3IndexToGreat &&
							(errorValue == iMatrix3D::ERROR_OUTSIDE_INDEX_DIMENSION_3 ) ){
						cout<<"The value was correctly not set, because the index in dimension 3 is to great."<<endl;
					}else{
						cerr<<"Error: The value was "<<
							((errorValue == iMatrix3D::OK)?"":"not ")<<
							"set sucessfull, wrong error value "<<
							errorValue<<"."<<endl;
						iReturn++;
					}
					
					cout<<"Compare pMatrix with the original."<<endl;
					//a different value set as befor
					testCompareEqual( pMatrix, pMatrixClone );
					
					delete pMatrixClone;
				}break;
				case 5:{//test setValue( longFib dValue ); outside borders
					const bool bDim1IndexToGreat = rand() % 2;
					const bool bDim2IndexToGreat = rand() % 2;
					const bool bDim3IndexToGreat = ( (rand() % 2) == 0 ) ||
						( ( ! bDim1IndexToGreat ) && ( ! bDim2IndexToGreat ) );
					const longFib lValueToSet = generateRandLongNumber( pMatrix );
					const unsigned int uiPositionX = bDim1IndexToGreat ?
						( uiMaxIndexX + 1 ) : ( rand() % ( uiMaxIndexX + 1 ) );
					const unsigned int uiPositionY = bDim2IndexToGreat ?
						( uiMaxIndexY + 1 ) :  ( rand() % ( uiMaxIndexY + 1 ) );
					const unsigned int uiPositionZ = bDim3IndexToGreat ?
						( uiMaxIndexZ + 1 ) :  ( rand() % ( uiMaxIndexZ + 1 ) );
					
					iMatrix3D * pMatrixClone = pMatrix->clone();
					
					cout<<"pMatrix->setValue( lValueToSet="<<lValueToSet<<
						", uiPositionX="<<uiPositionX<<
						", uiPositionY="<<uiPositionY<<
						", uiPositionZ="<<uiPositionZ<<" ); (outside borders)"<<endl;
					const iMatrix3D::tErrorValue errorValue = pMatrix->setValue( lValueToSet,
						uiPositionX, uiPositionY, uiPositionZ );
					
					if ( bDim1IndexToGreat &&
							(errorValue == iMatrix3D::ERROR_OUTSIDE_INDEX_DIMENSION_1 ) ){
						cout<<"The value was correctly not set, because the index in dimension 1 is to great."<<endl;
					}else if ( bDim2IndexToGreat &&
							(errorValue == iMatrix3D::ERROR_OUTSIDE_INDEX_DIMENSION_2 ) ){
						cout<<"The value was correctly not set, because the index in dimension 2 is to great."<<endl;
					}else if ( bDim3IndexToGreat &&
							(errorValue == iMatrix3D::ERROR_OUTSIDE_INDEX_DIMENSION_3 ) ){
						cout<<"The value was correctly not set, because the index in dimension 3 is to great."<<endl;
					}else{
						cerr<<"Error: The value was "<<
							((errorValue == iMatrix3D::OK)?"":"not ")<<
							"set sucessfull, wrong error value "<<
							errorValue<<"."<<endl;
						iReturn++;
					}
					
					cout<<"Compare pMatrix with the original."<<endl;
					//a different value set as befor
					testCompareEqual( pMatrix, pMatrixClone );
					
					delete pMatrixClone;
				}break;
				
			}//end switch
			
		}else{//call rare method
			const unsigned int uiChangeMethod = rand() % 5;
			
			switch ( uiChangeMethod ){
				case 0:{//test clone()
					cout<<"pMatrixClone = pMatrixConst->clone();"<<endl;
					iMatrix3D * pMatrixClone = pMatrixConst->clone();
					
					cout<<"Compare pMatrix with pMatrixClone."<<endl;
					iReturn = testCompareEqual( pMatrix, pMatrixClone );
					
					delete pMatrix;
					
					pMatrix = pMatrixClone;
					pMatrixConst = pMatrixClone;
				}break;
				case 1:{//test copy constructor
					cout<<"pMatrixCopy = new copyConstructor( pMatrix );"<<endl;
					iMatrix3D * pMatrixCopy = copyMatrix( pMatrix );
					
					cout<<"Compare pMatrix with pMatrixCopy."<<endl;
					iReturn = testCompareEqual( pMatrix, pMatrixCopy );
					
					delete pMatrix;
					
					pMatrix = pMatrixCopy;
					pMatrixConst = pMatrixCopy;
				}break;
				case 2:{//test clear()
					cout<<"pMatrix->clear();"<<endl;
					pMatrix->clear();
					
					vecCorrectValues = vector< vector< vector< longFib > > >(
						uiMaxIndexX + 1, vector< vector< longFib > >( uiMaxIndexY + 1,
							vector< longFib >( uiMaxIndexZ + 1, 0 ) ) );
				}break;
				
				case 3:{//test evalueDerivate()
					const unsigned int uiDirection = rand() % 3;
					cout<<"iMatrix3D * pDerivateMatrix = pMatrix->evalueDerivate( uiDirection="<<
							uiDirection<<" );"<<endl;
					iMatrix3D * pDerivateMatrix = pMatrixConst->evalueDerivate( uiDirection );
					
					if ( pDerivateMatrix ){
						//check the returned derivation
						const unsigned int uiMaxDerivateIndexX =
							( uiDirection != 0 ) ? uiMaxIndexX : ( uiMaxIndexX - 1 );
						const unsigned int uiMaxDerivateIndexY =
							( uiDirection != 1 ) ? uiMaxIndexY : ( uiMaxIndexY - 1 );
						const unsigned int uiMaxDerivateIndexZ =
							( uiDirection != 2 ) ? uiMaxIndexZ : ( uiMaxIndexZ - 1 );
						const unsigned int uiDeltaX = ( uiDirection == 0 ) ? 1 : 0;
						const unsigned int uiDeltaY = ( uiDirection == 1 ) ? 1 : 0;
						const unsigned int uiDeltaZ = ( uiDirection == 2 ) ? 1 : 0;
						//test the size of the derivate
						if ( uiMaxDerivateIndexX != pDerivateMatrix->getMaxIndex( 0 ) ){
							cerr<<"Error: The derivate matrix has as the maximum index \""<<
								pDerivateMatrix->getMaxIndex( 0 )<<"\" in direction 0, but should be \""<<
								uiMaxDerivateIndexX<<"\""<<endl;
							iReturn++;
						}
						if ( uiMaxDerivateIndexY != pDerivateMatrix->getMaxIndex( 1 ) ){
							cerr<<"Error: The derivate matrix has as the maximum index \""<<
								pDerivateMatrix->getMaxIndex( 1 )<<"\" in direction 1, but should be \""<<
								uiMaxDerivateIndexY<<"\""<<endl;
							iReturn++;
						}
						if ( uiMaxDerivateIndexZ != pDerivateMatrix->getMaxIndex( 2 ) ){
							cerr<<"Error: The derivate matrix has as the maximum index \""<<
								pDerivateMatrix->getMaxIndex( 2 )<<"\" in direction 2, but should be \""<<
								uiMaxDerivateIndexZ<<"\""<<endl;
							iReturn++;
						}
						
						//test the entries of the derivate
						for ( unsigned int indexX = 0;
								indexX <= uiMaxDerivateIndexX; indexX++ ){
							for ( unsigned int indexY = 0;
									indexY <= uiMaxDerivateIndexY; indexY++ ){
								for ( unsigned int indexZ = 0;
										indexZ <= uiMaxDerivateIndexZ; indexZ++ ){
									
									if ( ! isEqual( pDerivateMatrix->getValue(
												indexX, indexY, indexZ ),
											( pMatrix->getValue( indexX + uiDeltaX,
													indexY + uiDeltaY, indexZ + uiDeltaZ ) -
												pMatrix->getValue( indexX, indexY, indexZ ) ) ) ){
										
										cerr<<"Error: The value in the derivate matrix for the index ("<<
											indexX<<", "<<indexY<<", "<<indexZ<<
											") is "<<pDerivateMatrix->getValue( indexX, indexY, indexZ )<<
											", but should be "<<
											( pMatrix->getValue( indexX + uiDeltaX,
													indexY + uiDeltaY, indexZ + uiDeltaZ ) -
												pMatrix->getValue( indexX, indexY, indexZ ) )<<endl;
										iReturn++;
									}
								}//end for index z
							}//end for index y
						}//end for index x
	
						delete pDerivateMatrix;
					}else{
						if ( ( 0 < uiMaxIndexX ) && ( 0 < uiMaxIndexY ) &&
								( 0 < uiMaxIndexZ ) ){
							cerr<<"Error: No derivation matrix was returned."<<endl;
							iReturn++;
						}else{
							cout<<"Correctly no derivation matrix created, because"<<
								"one dimension has less than two indeses."<<endl;
						}
					}
				}break;
				case 4:{//test evalueDerivate() for non existing direction
					cout<<"iMatrix3D * pDerivateMatrix = pMatrix->evalueDerivate( 3 ); (invalid direction)"<<endl;
					iMatrix3D * pDerivateMatrix = pMatrix->evalueDerivate( 3 );
					
					if ( pDerivateMatrix != NULL ){
						cerr<<"Error: A derivate matrix was returned for the "<<
							"derivation in direction 3, which is not pssoble (matrix is 3 dimensional)."<<endl;
						iReturn++;
						delete pDerivateMatrix;
					}
				}break;
				case 5:{//create new matrix
					delete pMatrix;
					
					uiMaxIndexX = rand() % 64;
					uiMaxIndexY = rand() % 64;
					uiMaxIndexZ = 3;
					
					pMatrix = getActualClass( uiMaxIndexX, uiMaxIndexY, uiMaxIndexZ );
					pMatrixConst = pMatrix;
					
					vecCorrectValues = vector< vector< vector< longFib > > >(
						uiMaxIndexX + 1, vector< vector< longFib > >( uiMaxIndexY + 1,
							vector< longFib >( uiMaxIndexZ + 1, 0 ) ) );
				}break;
				
			}//end switch
		}//end which probable method
		
		
		//test the members of the class
		if ( compareMatrixPoints( pMatrix,
				uiMaxIndexX, uiMaxIndexY, uiMaxIndexZ, vecCorrectValues ) != 0 ){
			cerr<<"Error: The matrix points are not correct."<<endl;
			printMatrix( cerr, pMatrix );
			iReturn++;
		}
		//check getName()
		if ( getActualClassName() == pMatrixConst->getName() ){
			cout<<"The matrix class name is correctly \""<<
				getActualClassName()<<"\"."<<endl;
		}else{
			cerr<<"Error: The matrix class name is \""<<
				pMatrixConst->getName()<<"\", but should be \""<<
				getActualClassName()<<"\""<<endl;
			iReturn++;
		}
		//check getMaxIndex()
		if ( uiMaxIndexX != pMatrixConst->getMaxIndex( 0 ) ){
			cerr<<"Error: The matrix has as the maximum index \""<<
				pMatrixConst->getMaxIndex( 0 )<<"\", but should be \""<<
				uiMaxIndexX<<"\""<<endl;
			iReturn++;
		}
		if ( uiMaxIndexY != pMatrixConst->getMaxIndex( 1 ) ){
			cerr<<"Error: The matrix has as the maximum index \""<<
				pMatrixConst->getMaxIndex( 1 )<<"\", but should be \""<<
				uiMaxIndexY<<"\""<<endl;
			iReturn++;
		}
		if ( uiMaxIndexZ != pMatrixConst->getMaxIndex( 2 ) ){
			cerr<<"Error: The matrix has as the maximum index \""<<
				pMatrixConst->getMaxIndex( 2 )<<"\", but should be \""<<
				uiMaxIndexZ<<"\""<<endl;
			iReturn++;
		}
		//check getMinValue()
		if ( pMatrixConst->getMinValue() < getMinValue( pMatrix ) ){
			cerr<<"Error: The returned minimum value ("<<
				pMatrixConst->getMinValue()<<") is lower as correct minimum value"<<
				getMinValue( pMatrix )<<endl;
			iReturn++;
		}
		//check getMaxValue()
		if ( getMaxValue( pMatrix ) < pMatrixConst->getMaxValue() ){
			cerr<<"Error: The returned maximum value ("<<
				pMatrixConst->getMaxValue()<<") is bigger as correct maximum value"<<
				getMaxValue( pMatrix )<<endl;
			iReturn++;
		}
		
	}//end iterate random test
	delete pMatrix;
	
	return iReturn;
}














