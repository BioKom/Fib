/**
 * @file t_nD1_cPolynom_evaluePolynomRange
 * file name: t_nD1_cPolynom_evaluePolynomRange.cpp
 * @author Betti Oesterholz
 * @date 15.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the function nD1::cPolynomRange::evaluePolynomRange .
 *
 * Copyright (C) @c GPL3 2010 Betti Oesterholz
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
 * This test is for the function nD1::cPolynomRange::evaluePolynomRange .
 *
 */
/*
History:
11.06.2010  Oesterholz  created
*/


//delete
//#define DEBUG



#include "version.h"

#include "cPolynomRange.h"
#include "cPolynom.h"
#include "cDataPointRange.h"

#include <iostream>
#include <cmath>

using namespace std;
using namespace fib::algorithms::nD1;


template <class tX, class tY> pair<double, double> printData(
	vector< cDataPointRange< tX, tY> > vecInput );



int main(int argc, char* argv[]){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	cout<<endl<<"Running Test for the function nD1::cPolynomRange::evaluePolynomRange"<<endl;
	cout<<      "===================================================================="<<endl;
	cout<<      "Beware: You have to check the result manually"<<endl;

	//the data to derivate plus the devolopment point
	vector< cDataPointRange< long, double > > vecData;

/*
	//f(x)= 2*x + 3
	vecData.push_back( cDataPointRange< long, double >( 0, 3, 3 ) );
	vecData.push_back( cDataPointRange< long, double >( 1, 5, 5 ) );
	vecData.push_back( cDataPointRange< long, double >( 2, 7, 7 ) );
	vecData.push_back( cDataPointRange< long, double >( 3, 9, 9 ) );
	vecData.push_back( cDataPointRange< long, double >( 4, 11, 11 ) );
	vecData.push_back( cDataPointRange< long, double >( 5, 13, 13 ) );
*/
/*
	//f(x)= x^2 + 1
	vecData.push_back( cDataPointRange< long, double >( 0, 1, 1 ) );//0
	vecData.push_back( cDataPointRange< long, double >( 1, 2, 2 ) );//1
	vecData.push_back( cDataPointRange< long, double >( 2, 5, 5 ) );//2
	vecData.push_back( cDataPointRange< long, double >( 3, 10, 10 ) );//3
	vecData.push_back( cDataPointRange< long, double >( 4, 17, 17 ) );//4
	vecData.push_back( cDataPointRange< long, double >( 5, 26, 26 ) );//5
*/
/*
	//f(x)= 3 * x^2 + 1
	vecData.push_back( cDataPointRange< long, double >( 0, 1, 1 ) );//0
	vecData.push_back( cDataPointRange< long, double >( 1, 4, 4 ) );//1
	vecData.push_back( cDataPointRange< long, double >( 2, 13, 13 ) );//2
	vecData.push_back( cDataPointRange< long, double >( 3, 28, 28 ) );//3
	vecData.push_back( cDataPointRange< long, double >( 4, 49, 49 ) );//4
	vecData.push_back( cDataPointRange< long, double >( 5, 76, 76 ) );//5
*/
/*
	//f(x)= 3 * x^2 + 1 +/- delta
	polynomOriginal.vecFactors.push_back( 1.0 );
	polynomOriginal.vecFactors.push_back( 0.0 );
	polynomOriginal.vecFactors.push_back( 3.0 );
	vecData.push_back( cDataPointRange< long, double >( 0, 0, 1 ) );//0
	vecData.push_back( cDataPointRange< long, double >( 1, 4, 5 ) );//1
	vecData.push_back( cDataPointRange< long, double >( 2, 12, 14 ) );//2
	vecData.push_back( cDataPointRange< long, double >( 3, 27, 28 ) );//3
	vecData.push_back( cDataPointRange< long, double >( 4, 46, 50 ) );//4
	vecData.push_back( cDataPointRange< long, double >( 5, 74, 78 ) );//5
*/
/*
	//f(x)= 3 * (x-4)^2 + 1 = 3 *x^2 - 24x + 49
	vecData.push_back( cDataPointRange< long, double >( 0, 49, 49 ) );
	vecData.push_back( cDataPointRange< long, double >( 1, 28, 28 ) );
	vecData.push_back( cDataPointRange< long, double >( 2, 13, 13 ) );
	vecData.push_back( cDataPointRange< long, double >( 3, 4, 4 ) );
	vecData.push_back( cDataPointRange< long, double >( 4, 1, 1 ) );
	vecData.push_back( cDataPointRange< long, double >( 5, 4, 4 ) );
	vecData.push_back( cDataPointRange< long, double >( 6, 13, 13 ) );
	vecData.push_back( cDataPointRange< long, double >( 7, 28, 28 ) );
	vecData.push_back( cDataPointRange< long, double >( 8, 49, 49 ) );
	vecData.push_back( cDataPointRange< long, double >( 9, 76, 76 ) );
*/
/*
	//f(x)= 3 * (x-4)^2 + 1 +/- delta
	vecData.push_back( cDataPointRange< long, double >( 0, 48, 49 ) );
	vecData.push_back( cDataPointRange< long, double >( 1, 27, 29 ) );
	vecData.push_back( cDataPointRange< long, double >( 2, 12, 15 ) );
	vecData.push_back( cDataPointRange< long, double >( 3, 3, 4 ) );
	vecData.push_back( cDataPointRange< long, double >( 4, 1, 2 ) );
	vecData.push_back( cDataPointRange< long, double >( 5, 4, 6 ) );
	vecData.push_back( cDataPointRange< long, double >( 6, 12, 14 ) );
	vecData.push_back( cDataPointRange< long, double >( 7, 26, 28 ) );
	vecData.push_back( cDataPointRange< long, double >( 8, 48, 50 ) );
	vecData.push_back( cDataPointRange< long, double >( 9, 72, 78 ) );
*/
/*
	//f(x)= 4 * x^3 + 3 * x^2 + 2 * x + 1
	vecData.push_back( cDataPointRange< long, double >( 8, 2257, 2257 ) );
	vecData.push_back( cDataPointRange< long, double >( 9, 3178, 3178 ) );
	vecData.push_back( cDataPointRange< long, double >( 0, 1, 1 ) );
	vecData.push_back( cDataPointRange< long, double >( 1, 10, 10 ) );
	vecData.push_back( cDataPointRange< long, double >( 2, 49, 49 ) );
	vecData.push_back( cDataPointRange< long, double >( 3, 142, 142 ) );
	vecData.push_back( cDataPointRange< long, double >( 4, 313, 313 ) );
	vecData.push_back( cDataPointRange< long, double >( 5, 586, 586 ) );
	vecData.push_back( cDataPointRange< long, double >( 6, 985, 985 ) );
	vecData.push_back( cDataPointRange< long, double >( 7, 1534, 1534 ) );
	vecData.push_back( cDataPointRange< long, double >( 10, 4321, 4321 ) );

	vecData.push_back( cDataPointRange< long, double >( -2, -23, -23 ) );
	vecData.push_back( cDataPointRange< long, double >( -1, -2, -2 ) );
*/



	const double dA0 = ((double)(rand() % (256 * 256))) / 256.0 - 128.0;
	const double dA1 = ((double)(rand() % 256)) / 8.0 - 4.0;
	const double dA2 = ((double)(rand() % 256)) / 8.0 - 4.0;
	const double dA3 = ((double)(rand() % 16)) / 4.0 - 2.0;
	const double dA4 = ((double)(rand() % 16)) / 4.0 - 2.0;
	

/*
	const double dA0 = 0;
	const double dA1 = 1;
	const double dA2 = 2;
	const double dA3 = 3;
	const double dA4 = 4;
*/
	cPolynom<long, double> polynomOriginal;
	polynomOriginal.vecFactors.push_back( dA0 );
	polynomOriginal.vecFactors.push_back( dA1 );
	polynomOriginal.vecFactors.push_back( dA2 );
	polynomOriginal.vecFactors.push_back( dA3 );
	polynomOriginal.vecFactors.push_back( dA4 );

	cout<<endl<<"original polynom:"<<endl;
	
	polynomOriginal.print( cout );
	const long lMinX = -30;//-40;
	const long lMaxX = 30;//40;
//	const long lMinX = (rand() % 1024) - 512;
//	const long lMaxX = lMinX + (rand() % 1024) + 1;

	for ( long lX = lMinX; lX <= lMaxX; lX++ ){
		
		const double dDeltaMin = ((double)(rand() % 8)) *
			((double)(rand() % 8)) / 65536.0;
		const double dDeltaMax = ((double)(rand() % 8)) *
			((double)(rand() % 8)) / 65536.0;

		const double xMin = ((double)lX) - dDeltaMin;
		const double dValueMin = polynomOriginal.evalue( xMin );
		const double xMax = ((double)lX) + dDeltaMax;
		const double dValueMax = polynomOriginal.evalue( xMax );
		
		if ( dValueMin <= dValueMax ){
			vecData.push_back( cDataPointRange< long, double >( lX, dValueMin, dValueMax ) );
		}else{//dValueMax < dValueMin
			vecData.push_back( cDataPointRange< long, double >( lX, dValueMax, dValueMin ) );
		}
		
	}

	cout<<"original data:"<<endl;
	printData( vecData );

	if ( vecData.empty() ){
		return 1;
	}
	cout<<endl;

	for ( unsigned int uiMaxPolynomOrder = 1; uiMaxPolynomOrder <= 10;
			uiMaxPolynomOrder++ ){
		
		cPolynomRange<long, double> evaluedPolynomRange;
		evaluedPolynomRange.evalue( vecData, uiMaxPolynomOrder );
		
		cout<<endl<<"original polynom:"<<endl;
		polynomOriginal.print( cout );
		cout<<endl<<"Founded polynom:"<<endl;
		evaluedPolynomRange.print( cout );
		
		cout<<endl<<"Fixed polynom:"<<endl;
		cPolynom<long, double> actualPolynom;
		
		cout<<"Ranges for polynomrange="<< uiMaxPolynomOrder <<": ";
		for ( unsigned int uiFactor = 0; uiFactor < evaluedPolynomRange.vecFactors.size(); uiFactor++ ){
			
			if ( ! evaluedPolynomRange.vecFactors[ uiFactor ].isInf() ){
				if ( 0.0000001 < abs( evaluedPolynomRange.vecFactors[ uiFactor ].max ) &&
						0.0000001 < abs( evaluedPolynomRange.vecFactors[ uiFactor ].min )  ){
					actualPolynom.vecFactors.push_back(
						(evaluedPolynomRange.vecFactors[ uiFactor ].min +
						evaluedPolynomRange.vecFactors[ uiFactor ].max) / 2.0 );
				}else{
					actualPolynom.vecFactors.push_back( 0.0 );
				}
			}
		}
		cout<<endl;
		
		actualPolynom.print( cout );
		
		//evalue error
		const pair<unsigned long, double> paErrorValue = actualPolynom.evalueError( vecData );
		cout<<endl<<"The polynom evalues "<< paErrorValue.first <<" points wrong (from "<< vecData.size() <<" points) "<<
			"with an absolute error from "<< paErrorValue.second;
		if ( paErrorValue.first != 0 ){
			cout<<" and an average error from "<< paErrorValue.second/((double)(paErrorValue.first)) <<" ."<<endl;
		}else{
			cout<<" ."<<endl;
		}
		cout<<endl<<endl;
	}
	
	return iReturn;
}


template <class tX, class tY>
	pair<double, double> printData( vector< cDataPointRange< tX, tY> > vecInput ){
	
	if ( vecInput.empty() ){
	
		cout<<"No values to output."<<endl;
		return make_pair( 0.0, 0.0 );
	}
	
	cout<<"x:  ";
	for ( size_t iActualValue = 0; iActualValue < vecInput.size();
			iActualValue++ ){
		cout<< vecInput[iActualValue].x <<";";
	}
	cout<<" ;; average;; average not null";
	double minYAverage = 0.0;
	unsigned int uiNotNull = 0;
	cout<<endl<<"min:";
	for ( size_t iActualValue = 0; iActualValue < vecInput.size();
			iActualValue++ ){
		if ( (0.000001 < abs( vecInput[iActualValue].minY )) ||
				(0.000001 < abs( vecInput[iActualValue].maxY )) ){
			cout<< vecInput[iActualValue].minY <<";";
			minYAverage += vecInput[iActualValue].minY;
			uiNotNull++;
		}else{
			cout<<" 0.0;";
		}
	}
	cout<<";"<< minYAverage / ((double)vecInput.size())<<" ;;"<< minYAverage / uiNotNull;
	double maxYAverage = 0.0;
	cout<<endl<<"max:";
	for ( size_t iActualValue = 0; iActualValue < vecInput.size();
			iActualValue++ ){
		if ( (0.000001 < abs( vecInput[iActualValue].minY )) ||
				(0.000001 < abs( vecInput[iActualValue].maxY )) ){
			cout<< vecInput[iActualValue].maxY <<";";
			maxYAverage += vecInput[iActualValue].maxY;
		}else{
			cout<<" 0.0;";
		}
	}
	cout<<";"<< maxYAverage / ((double)vecInput.size())<<" ;;"<< maxYAverage / uiNotNull;
	cout<<endl;
	
	if ( uiNotNull == 0 ){
		cout<<"Non not 0 values ."<<endl;
		return make_pair( 0.0, 0.0 );
	}
	return make_pair( minYAverage / uiNotNull, maxYAverage / uiNotNull );
}












