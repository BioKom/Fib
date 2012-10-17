/**
 * @file tFibObjectFitnessBasic
 * file name: tFibObjectFitnessBasic.cpp
 * @author Betti Oesterholz
 * @date 05.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cFibObjectFitnessBasic.
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
 * This file contains the test for the class cFibObjectFitnessBasic.
 *
 *
 *
 *  What's tested of class cFibObjectFitnessBasic:
 * 	- cFibObjectFitnessBasic( double dInDistanceToOriginal, long lInSize, long lInEvaluationTime, double dInWeightDistanceToOriginal=1.0, double dInWeightSize=1.0, double dInWeightEvaluationTime=1.0, cFibObjectFitnessBasicAlgorithm * pInFibObjectFitnessAlgorithm=NULL );
 * 	- cFibObjectFitnessBasic( const cFibObjectFitnessBasic & objectFitness );
 * 	- string getClassName() const;
 * 	- const cFibObjectFitnessBasicAlgorithm * getFitnessAlgorithm() const;
 * 	- cFibObjectFitnessBasic * clone() const;
 * 	- bool operator==( const cFibObjectFitnessBasic &fitness ) const;
 * 	- bool equal( const cObjectFitness &fitness ) const
 * 	- bool operator<( const cObjectFitness &fitness ) const;
 * 	- double getDifferenceToOriginal() const;
 * 	- bool changeDifferenceToOriginal( double dDeltaToOriginal );
 * 	- double getWeightDistanceToOriginal() const;
 * 	- long getSize() const;
 * 	- bool changeSize( long lDeltaSize );
 * 	- double getWeightSize() const;
 * 	- long getTime() const;
 * 	- bool changeTime( long lDeltaEvalueTime );
 * 	- double getWeightEvaluationTime() const;
 * 	- double getFitness() const
 *
 */
/*
History:
05.03.2010  Oesterholz  created
*/

#include "version.h"

#include "cFibObjectFitnessBasic.h"
#include "cFibObjectFitnessBasicAlgorithm.h"

#include "cPoint.h"

#include <iostream>
#include <ctime>
#include <cmath>

using namespace fib;
using namespace enviroment::fib;
using namespace std;

int testCostructor( unsigned long &ulTestphase );
int testComparison( unsigned long &ulTestphase );
int testValues( unsigned long &ulTestphase );


int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	srand( time_t( NULL ) );
	
	cout<<endl<<"Running Test for cFibObjectFitnessBasic methods"<<endl;
	cout<<      "==============================================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testComparison( ulTestphase );
	iReturn += testValues( ulTestphase );

	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}



/**
 * This function evaluats the fitnessvalue of the given
 * cFibObjectFitnessBasic object.
 *
 * @param fitness the fitness for which to evalue the fitnessvalue
 * @return the evalued fitnessvalue
 */
double evalueFitness( const cFibObjectFitnessBasic & fitness ){

	return -1.0 * ( (double)(fitness.getDifferenceToOriginal()) * (double)(fitness.getWeightDistanceToOriginal()) +
		(double)(fitness.getSize()) * (double)(fitness.getWeightSize()) +
		(double)(fitness.getTime()) * (double)(fitness.getWeightEvaluationTime()) );
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
	const doubleFib dSaveBoundery = min( dSaveBoundery1, dSaveBoundery2 );
	
	if ( (dValue1 - dSaveBoundery <= dValue2) &&
			(dValue1 <= dValue2 + dSaveBoundery) ){
		return true;
	}
	return false;
}


/**
 * This method tests the constructor of the cFibObjectFitnessBasic class.
 *
 * methods tested:
 * 	- cFibObjectFitnessBasic( double dInDistanceToOriginal, long lInSize, long lInEvaluationTime, double dInWeightDistanceToOriginal=1.0, double dInWeightSize=1.0, double dInWeightEvaluationTime=1.0, cFibObjectFitnessBasicAlgorithm * pInFibObjectFitnessAlgorithm=NULL );
 * 	- string getClassName() const;
 * 	- const cFibObjectFitnessBasicAlgorithm * getFitnessAlgorithm() const;
 * 	- double getDifferenceToOriginal() const;
 * 	- double getWeightDistanceToOriginal() const;
 * 	- long getSize() const;
 * 	- double getWeightSize() const;
 * 	- long getTime() const;
 * 	- double getWeightEvaluationTime() const;
 * 	- double getFitness() const
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cFibObjectFitnessBasic"<<endl;

	cout<<"cFibObjectFitnessBasic fitness1( 0.0, 0, 0 );"<<endl;
	cFibObjectFitnessBasic fitness1( 0.0, 0, 0 );

	//check the getClassName() methode from cFibObjectFitnessBasic
	if ( fitness1.getClassName() == "cFibObjectFitnessBasic" ){
	
		cout<<"The classname of the fitness is correctly \"cFibObjectFitnessBasic\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitness is "<<
			fitness1.getClassName() <<" but should be \"cFibObjectFitnessBasic\" ."<<endl;
		iReturn++;
	}
	//check the getFitnessAlgorithm() methode from cFibObjectFitnessBasic
	if ( fitness1.getFitnessAlgorithm() == NULL ){
	
		cout<<"The algorithm of the fitness is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The algorithm of the fitness is "<<
			fitness1.getFitnessAlgorithm() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getDifferenceToOriginal() methode from cFibObjectFitnessBasic
	if ( fitness1.getDifferenceToOriginal() == 0.0 ){
	
		cout<<"The differnes to the original value of the fitness is correctly 0.0 . "<<endl;
	}else{
		cerr<<"Error: The differnes to the original value of the fitness is "<<
			fitness1.getDifferenceToOriginal() <<" but should be 0.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasic
	if ( fitness1.getWeightDistanceToOriginal() == 1.0 ){
	
		cout<<"The weight for the differnes to the original of the fitness is correctly 1.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the differnes to the original of the fitness is "<<
			fitness1.getWeightDistanceToOriginal() <<" but should be 1.0 ."<<endl;
		iReturn++;
	}
	//check the getSize() methode from cFibObjectFitnessBasic
	if ( fitness1.getSize() == 0 ){
	
		cout<<"The size of the fib -object of the fitness is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The size of the fib -object of the fitness is "<<
			fitness1.getSize() <<" but should be 0 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasic
	if ( fitness1.getWeightSize() == 1.0 ){
	
		cout<<"The weight for the size of the fib -object of the fitness is correctly 1.0 . "<<endl;
	}else{
		cerr<<"Error: The weight size of the fib -object of the fitness is "<<
			fitness1.getWeightSize() <<" but should be 1.0 ."<<endl;
		iReturn++;
	}
	//check the getTime() methode from cFibObjectFitnessBasic
	if ( fitness1.getTime() == 0 ){
	
		cout<<"The evaluation time of the fib -object of the fitness is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The evaluation time of the fib -object of the fitness is "<<
			fitness1.getTime() <<" but should be 0 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasic
	if ( fitness1.getWeightEvaluationTime() == 1.0 ){
	
		cout<<"The weight for the evaluation time of the fib -object of the fitness is correctly 1.0 . "<<endl;
	}else{
		cerr<<"Error: The weight evaluation time of the fib -object of the fitness is "<<
			fitness1.getWeightEvaluationTime() <<" but should be 1.0 ."<<endl;
		iReturn++;
	}
	//check the getFitness() methode from cFibObjectFitnessBasic
	if ( isEqual( fitness1.getFitness(), evalueFitness( fitness1 ) ) ){
	
		cout<<"The fitnessvalue is correctly "<< evalueFitness( fitness1 ) <<" . "<<endl;
	}else{
		cerr<<"Error: The fitnessvalue is "<< fitness1.getFitness() <<
			" but should be "<< evalueFitness( fitness1 ) <<" ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cFibObjectFitnessBasic"<<endl;

	cout<<"cFibObjectFitnessBasicAlgorithm algorithmBasic1;"<<endl;
	cFibObjectFitnessBasicAlgorithm algorithmBasic1;
	
	cout<<"cFibObjectFitnessBasic fitness2( 1.0, 2, 3, 2.0, 3.0, 0.5, &algorithmBasic1 );"<<endl;
	cFibObjectFitnessBasic fitness2( 1.0, 2, 3, 2.0, 3.0, 0.5, &algorithmBasic1 );

	//check the getClassName() methode from cFibObjectFitnessBasic
	if ( fitness2.getClassName() == "cFibObjectFitnessBasic" ){
	
		cout<<"The classname of the fitness is correctly \"cFibObjectFitnessBasic\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitness is "<<
			fitness2.getClassName() <<" but should be \"cFibObjectFitnessBasic\" ."<<endl;
		iReturn++;
	}
	//check the getFitnessAlgorithm() methode from cFibObjectFitnessBasic
	if ( fitness2.getFitnessAlgorithm() == &algorithmBasic1 ){
	
		cout<<"The algorithm of the fitness is correctly &algorithmBasic1="<< &algorithmBasic1 <<" . "<<endl;
	}else{
		cerr<<"Error: The algorithm of the fitness is "<<
			fitness2.getFitnessAlgorithm() <<" but should be &algorithmBasic1="<< &algorithmBasic1 <<" ."<<endl;
		iReturn++;
	}
	//check the getDifferenceToOriginal() methode from cFibObjectFitnessBasic
	if ( fitness2.getDifferenceToOriginal() == 1.0 ){
	
		cout<<"The differnes to the original value of the fitness is correctly 1.0 . "<<endl;
	}else{
		cerr<<"Error: The differnes to the original value of the fitness is "<<
			fitness2.getDifferenceToOriginal() <<" but should be 1.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasic
	if ( fitness2.getWeightDistanceToOriginal() == 2.0 ){
	
		cout<<"The weight for the differnes to the original of the fitness is correctly 2.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the differnes to the original of the fitness is "<<
			fitness2.getWeightDistanceToOriginal() <<" but should be 2.0 ."<<endl;
		iReturn++;
	}
	//check the getSize() methode from cFibObjectFitnessBasic
	if ( fitness2.getSize() == 2 ){
	
		cout<<"The size of the fib -object of the fitness is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The size of the fib -object of the fitness is "<<
			fitness2.getSize() <<" but should be 2 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasic
	if ( fitness2.getWeightSize() == 3.0 ){
	
		cout<<"The weight for the size of the fib -object of the fitness is correctly 3.0 . "<<endl;
	}else{
		cerr<<"Error: The weight size of the fib -object of the fitness is "<<
			fitness2.getWeightSize() <<" but should be 3.0 ."<<endl;
		iReturn++;
	}
	//check the getTime() methode from cFibObjectFitnessBasic
	if ( fitness2.getTime() == 3 ){
	
		cout<<"The evaluation time of the fib -object of the fitness is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The evaluation time of the fib -object of the fitness is "<<
			fitness2.getTime() <<" but should be 3 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasic
	if ( fitness2.getWeightEvaluationTime() == 0.5 ){
	
		cout<<"The weight for the evaluation time of the fib -object of the fitness is correctly 0.5 . "<<endl;
	}else{
		cerr<<"Error: The weight evaluation time of the fib -object of the fitness is "<<
			fitness2.getWeightEvaluationTime() <<" but should be 0.5 ."<<endl;
		iReturn++;
	}
	//check the getFitness() methode from cFibObjectFitnessBasic
	if ( isEqual( fitness2.getFitness(), evalueFitness( fitness2 ) ) ){
	
		cout<<"The fitnessvalue is correctly "<< evalueFitness( fitness2 ) <<" . "<<endl;
	}else{
		cerr<<"Error: The fitnessvalue is "<< fitness2.getFitness() <<
			" but should be "<< evalueFitness( fitness2 ) <<" ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cFibObjectFitnessBasic"<<endl;
	
	cout<<"cPoint * pPoint = new cPoint();"<<endl;
	cPoint * pPoint = new cPoint();
	
	cout<<"cFibObjectFitnessBasicAlgorithm algorithmBasic2( pPoint, 1.0, 2.0, 3.0 );"<<endl;
	cFibObjectFitnessBasicAlgorithm algorithmBasic2( pPoint, 1.0, 2.0, 3.0 );
	
	cout<<"cFibObjectFitnessBasic fitness3( 5.0, 4, 9, -2.0, -1.0, 0.0, &algorithmBasic2 );"<<endl;
	cFibObjectFitnessBasic fitness3( 5.0, 4, 9, -2.0, -1.0, 0.0, &algorithmBasic2 );

	//check the getClassName() methode from cFibObjectFitnessBasic
	if ( fitness3.getClassName() == "cFibObjectFitnessBasic" ){
	
		cout<<"The classname of the fitness is correctly \"cFibObjectFitnessBasic\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitness is "<<
			fitness3.getClassName() <<" but should be \"cFibObjectFitnessBasic\" ."<<endl;
		iReturn++;
	}
	//check the getFitnessAlgorithm() methode from cFibObjectFitnessBasic
	if ( fitness3.getFitnessAlgorithm() == &algorithmBasic2 ){
	
		cout<<"The algorithm of the fitness is correctly &algorithmBasic2="<< &algorithmBasic2 <<" . "<<endl;
	}else{
		cerr<<"Error: The algorithm of the fitness is "<<
			fitness3.getFitnessAlgorithm() <<" but should be &algorithmBasic2="<< &algorithmBasic2 <<" ."<<endl;
		iReturn++;
	}
	//check the getDifferenceToOriginal() methode from cFibObjectFitnessBasic
	if ( fitness3.getDifferenceToOriginal() == 5.0 ){
	
		cout<<"The differnes to the original value of the fitness is correctly 5.0 . "<<endl;
	}else{
		cerr<<"Error: The differnes to the original value of the fitness is "<<
			fitness3.getDifferenceToOriginal() <<" but should be 5.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasic
	if ( fitness3.getWeightDistanceToOriginal() == -2.0 ){
	
		cout<<"The weight for the differnes to the original of the fitness is correctly -2.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the differnes to the original of the fitness is "<<
			fitness3.getWeightDistanceToOriginal() <<" but should be -2.0 ."<<endl;
		iReturn++;
	}
	//check the getSize() methode from cFibObjectFitnessBasic
	if ( fitness3.getSize() == 4 ){
	
		cout<<"The size of the fib -object of the fitness is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The size of the fib -object of the fitness is "<<
			fitness3.getSize() <<" but should be 4 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasic
	if ( fitness3.getWeightSize() == -1.0 ){
	
		cout<<"The weight for the size of the fib -object of the fitness is correctly -1.0 . "<<endl;
	}else{
		cerr<<"Error: The weight size of the fib -object of the fitness is "<<
			fitness3.getWeightSize() <<" but should be -1.0 ."<<endl;
		iReturn++;
	}
	//check the getTime() methode from cFibObjectFitnessBasic
	if ( fitness3.getTime() == 9 ){
	
		cout<<"The evaluation time of the fib -object of the fitness is correctly 9 . "<<endl;
	}else{
		cerr<<"Error: The evaluation time of the fib -object of the fitness is "<<
			fitness3.getTime() <<" but should be 9 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasic
	if ( fitness3.getWeightEvaluationTime() == 0.0 ){
	
		cout<<"The weight for the evaluation time of the fib -object of the fitness is correctly 0.0 . "<<endl;
	}else{
		cerr<<"Error: The weight evaluation time of the fib -object of the fitness is "<<
			fitness3.getWeightEvaluationTime() <<" but should be 0.0 ."<<endl;
		iReturn++;
	}
	//check the getFitness() methode from cFibObjectFitnessBasic
	if ( isEqual( fitness3.getFitness(), evalueFitness( fitness3 ) ) ){
	
		cout<<"The fitnessvalue is correctly "<< evalueFitness( fitness3 ) <<" . "<<endl;
	}else{
		cerr<<"Error: The fitnessvalue is "<< fitness3.getFitness() <<
			" but should be "<< evalueFitness( fitness3 ) <<" ."<<endl;
		iReturn++;
	}
	delete pPoint;

	return iReturn;
}




/**
 * This method tests the equal() method and the operator== of two given
 * cObjectFitnesss objects which are equal.
 *
 * @param fitness1 the first fitness to compare
 * @param szNameFitness1 the name of the first fitness to compare
 * @param fitness2 the secound fitness to compare to
 * @param szNameFitness2 the name of the secound fitness to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualFitness( const cFibObjectFitness & fitness1, const string & szNameFitness1,
	const cFibObjectFitness & fitness2, const string & szNameFitness2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( fitness1.equal( fitness2 ) ){
	
		cout<<"The "<<szNameFitness1<<" is equal to "<<szNameFitness2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameFitness1<<" is not equal to "<<
			szNameFitness2<<"."<<endl;
		iReturn++;
	}
	if ( fitness1 == fitness2 ){
	
		cout<<"The "<<szNameFitness1<<" is equal (operator==) to "<<
			szNameFitness2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameFitness1<<" is not equal (operator==) to "<<
			szNameFitness2<<"."<<endl;
		iReturn++;
	}

	return iReturn;
}

/**
 * This method tests the equal() method and the operator== of two given
 * cObjectFitnesss objects which are not equal.
 *
 * @param fitness1 the first fitness to compare
 * @param szNameFitness1 the name of the first fitness to compare
 * @param fitness2 the secound fitness to compare to
 * @param szNameFitness2 the name of the secound fitness to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoNotEqualFitness( const cFibObjectFitness & fitness1, const string & szNameFitness1,
	const cFibObjectFitness & fitness2, const string & szNameFitness2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( ! fitness1.equal( fitness2 ) ){
	
		cout<<"The "<<szNameFitness1<<" is not equal to "<<szNameFitness2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameFitness1<<" is equal to "<<
			szNameFitness2<<"."<<endl;
		iReturn++;
	}
	if ( ! (fitness1 == fitness2) ){
	
		cout<<"The "<<szNameFitness1<<" is not equal (operator==) to "<<
			szNameFitness2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameFitness1<<" is equal (operator==) to "<<
			szNameFitness2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}

/**
 * This method tests the operator<() method of two given cObjectFitness
 * objects which are equal.
 *
 * @param fitness1 the first fitness to compare
 * @param szNameFitness1 the name of the first fitness to compare
 * @param fitness2 the secound fitness to compare to
 * @param szNameFitness2 the name of the secound fitness to compare
 * @return the number of errors occured in the test
 */
int testCompareLowerFitness( const cFibObjectFitness & fitness1, const string & szNameFitness1,
	const cFibObjectFitness & fitness2, const string & szNameFitness2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( fitness1 < fitness2 ){
	
		cout<<"The "<<szNameFitness1<<" is lower (operator<) to "<<
			szNameFitness2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameFitness1<<" is not lower (operator<) to "<<
			szNameFitness2<<"."<<endl;
		iReturn++;
	}

	return iReturn;
}

/**
 * This method tests the operator<() method of two given cObjectFitness
 * objects which are equal.
 *
 * @param fitness1 the first fitness to compare
 * @param szNameFitness1 the name of the first fitness to compare
 * @param fitness2 the secound fitness to compare to
 * @param szNameFitness2 the name of the secound fitness to compare
 * @return the number of errors occured in the test
 */
int testCompareNotLowerFitness( const cFibObjectFitness & fitness1, const string & szNameFitness1,
	const cFibObjectFitness & fitness2, const string & szNameFitness2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( ! (fitness1 < fitness2) ){
	
		cout<<"The "<<szNameFitness1<<" is not lower (operator<) to "<<
			szNameFitness2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameFitness1<<" is lower (operator<) to "<<
			szNameFitness2<<"."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests the constructor of the cFibObjectFitnessBasic class.
 *
 * methods tested:
 * 	- bool operator==( const cFibObjectFitnessBasic &fitness ) const;
 * 	- bool equal( const cObjectFitness &fitness ) const
 * 	- bool operator<( const cObjectFitness &fitness ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testComparison( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing comparison of cFibObjectFitnessBasic Objects"<<endl;

	cout<<"cFibObjectFitnessBasic fitness0_1( 0.0, 0, 0 );"<<endl;
	cFibObjectFitnessBasic fitness0_1( 0.0, 0, 0 );
	
	cout<<"cFibObjectFitnessBasic fitness0_2( 0.0, 0, 0 );"<<endl;
	cFibObjectFitnessBasic fitness0_2( 0.0, 0, 0 );

	cout<<"cPoint * pPoint = new cPoint();"<<endl;
	cPoint * pPoint = new cPoint();
	cout<<"cFibObjectFitnessBasicAlgorithm algorithmBasic1( pPoint, 1.0, 2.0, 3.0 );"<<endl;
	cFibObjectFitnessBasicAlgorithm algorithmBasic1( pPoint, 1.0, 2.0, 3.0 );
	
	cout<<"pPoint2 = new cPoint();"<<endl;
	cPoint * pPoint2 = new cPoint();
	cout<<"cFibObjectFitnessBasicAlgorithm algorithmBasic2( pPoint2, 3.0, 2.0, 1.0 );"<<endl;
	cFibObjectFitnessBasicAlgorithm algorithmBasic2( pPoint2, 3.0, 2.0, 1.0 );

	cout<<"cFibObjectFitnessBasic fitness0_3( 0.0, 0, 0, 1.0, 1.0, 1.0 );"<<endl;
	cFibObjectFitnessBasic fitness0_3( 0.0, 0, 0, 1.0, 1.0, 1.0 );

	cout<<"cFibObjectFitnessBasic fitness0_4( 0.0, 0, 0, 1.0, 1.0, 1.0, &algorithmBasic1 );"<<endl;
	cFibObjectFitnessBasic fitness0_4( 0.0, 0, 0, 1.0, 1.0, 1.0, &algorithmBasic1 );

	cout<<"cFibObjectFitnessBasic fitness0_5( 0.0, 0, 0, 1.0, 1.0, 1.0, &algorithmBasic2 );"<<endl;
	cFibObjectFitnessBasic fitness0_5( 0.0, 0, 0, 1.0, 1.0, 1.0, &algorithmBasic2 );

	cout<<"cFibObjectFitnessBasic fitness0_6( 0.0, 0, 0, 5.0, -1.0, 7.0, &algorithmBasic1 );"<<endl;
	cFibObjectFitnessBasic fitness0_6( 0.0, 0, 0, 5.0, -1.0, 7.0, &algorithmBasic1 );


	cout<<"cFibObjectFitnessBasic fitness1( 100.0, 100, 100, 1.0, 1.0, 1.0, &algorithmBasic1 );"<<endl;
	cFibObjectFitnessBasic fitness1( 100.0, 100, 100, 1.0, 1.0, 1.0, &algorithmBasic1 );

	cout<<"cFibObjectFitnessBasic fitness2( 200.0, 100, 100, 1.0, 1.0, 1.0, &algorithmBasic1 );"<<endl;
	cFibObjectFitnessBasic fitness2( 200.0, 100, 100, 1.0, 1.0, 1.0, &algorithmBasic1 );

	cout<<"cFibObjectFitnessBasic fitness3( 200.0, 200, 100, 1.0, 1.0, 1.0, &algorithmBasic1 );"<<endl;
	cFibObjectFitnessBasic fitness3( 200.0, 200, 100, 1.0, 1.0, 1.0, &algorithmBasic1 );

	cout<<"cFibObjectFitnessBasic fitness4( 200.0, 200, 200, 1.0, 1.0, 1.0, &algorithmBasic1 );"<<endl;
	cFibObjectFitnessBasic fitness4( 200.0, 200, 200, 1.0, 1.0, 1.0, &algorithmBasic1 );

	cout<<"cFibObjectFitnessBasic fitness5( 200.0, 200, 200, 2.0, 1.0, 1.0, &algorithmBasic1 );"<<endl;
	cFibObjectFitnessBasic fitness5( 200.0, 200, 200, 2.0, 1.0, 1.0, &algorithmBasic1 );

	cout<<"cFibObjectFitnessBasic fitness6( 200.0, 200, 200, 2.0, 2.0, 1.0, &algorithmBasic1 );"<<endl;
	cFibObjectFitnessBasic fitness6( 200.0, 200, 200, 2.0, 2.0, 1.0, &algorithmBasic1 );

	cout<<"cFibObjectFitnessBasic fitness7( 100.0, 200, 200, 2.0, 2.0, 2.0 );"<<endl;
	cFibObjectFitnessBasic fitness7( 100.0, 200, 200, 2.0, 2.0, 2.0 );


	cout<<"cFibObjectFitnessBasic fitness8( 200.0, 200, 200, 2.0, 2.0, 2.0 );"<<endl;
	cFibObjectFitnessBasic fitness8( 200.0, 200, 200, 2.0, 2.0, 2.0 );

	cout<<"cFibObjectFitnessBasic fitness9( 100.0, 100, 400, 2.0, 2.0, 2.0 );"<<endl;
	cFibObjectFitnessBasic fitness9( 100.0, 100, 400, 2.0, 2.0, 2.0 );

	cout<<"cFibObjectFitnessBasic fitness10( 100.0, 100, 100, 2.0, 8.0, 2.0 );"<<endl;
	cFibObjectFitnessBasic fitness10( 100.0, 100, 100, 2.0, 8.0, 2.0 );


	cout<<"cFibObjectFitnessBasic fitnessN1( 100.0, 100, 100, -1.0, 1.0, 1.0 );"<<endl;
	cFibObjectFitnessBasic fitnessN1( 100.0, 100, 100, -1.0, 1.0, 1.0);

	cout<<"cFibObjectFitnessBasic fitnessN2( 100.0, 100, 100, 1.0, -1.0, 1.0 );"<<endl;
	cFibObjectFitnessBasic fitnessN2( 100.0, 100, 100, 1.0, -1.0, 1.0);
	
	cout<<"cFibObjectFitnessBasic fitnessN3( 100.0, 100, 100, 1.0, 1.0, -1.0 );"<<endl;
	cFibObjectFitnessBasic fitnessN3( 100.0, 100, 100, 1.0, 1.0, -1.0);


	//compare with fitness0_1
	cFibObjectFitness * actualFitness = &fitness0_1;
	string szActualFitnessName = "fitness0_1";
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( fitness0_1, "fitness0_1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( fitness0_2, "fitness0_2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( fitness0_3, "fitness0_3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( fitness0_4, "fitness0_4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( fitness0_5, "fitness0_5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( fitness0_6, "fitness0_6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareLowerFitness( fitness1, "fitness1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareLowerFitness( fitness2, "fitness2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareLowerFitness( fitness3, "fitness3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareLowerFitness( fitness4, "fitness4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareLowerFitness( fitness5, "fitness5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareLowerFitness( fitness6, "fitness6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareLowerFitness( fitness7, "fitness7", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareLowerFitness( fitness8, "fitness8", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareLowerFitness( fitness9, "fitness9", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareLowerFitness( fitness10, "fitness10", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareLowerFitness( fitnessN1, "fitnessN1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareLowerFitness( fitnessN2, "fitnessN2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareLowerFitness( fitnessN3, "fitnessN3", *actualFitness, szActualFitnessName );

	//compare with fitness0_2
	actualFitness = &fitness0_2;
	szActualFitnessName = "fitness0_2";
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( fitness0_1, "fitness0_1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( fitness0_2, "fitness0_2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( fitness0_3, "fitness0_3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( fitness0_4, "fitness0_4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( fitness0_5, "fitness0_5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( fitness0_6, "fitness0_6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareLowerFitness( fitness1, "fitness1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareLowerFitness( fitness2, "fitness2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareLowerFitness( fitness3, "fitness3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareLowerFitness( fitness4, "fitness4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareLowerFitness( fitness5, "fitness5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareLowerFitness( fitness6, "fitness6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareLowerFitness( fitness7, "fitness7", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareLowerFitness( fitness8, "fitness8", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareLowerFitness( fitness9, "fitness9", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareLowerFitness( fitness10, "fitness10", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareLowerFitness( fitnessN1, "fitnessN1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareLowerFitness( fitnessN2, "fitnessN2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareLowerFitness( fitnessN3, "fitnessN3", *actualFitness, szActualFitnessName );


	//compare with fitness0_3
	actualFitness = &fitness0_3;
	szActualFitnessName = "fitness0_3";
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( fitness0_1, "fitness0_1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( fitness0_2, "fitness0_2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( fitness0_3, "fitness0_3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( fitness0_4, "fitness0_4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( fitness0_5, "fitness0_5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( fitness0_6, "fitness0_6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareLowerFitness( fitness1, "fitness1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareLowerFitness( fitness2, "fitness2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareLowerFitness( fitness3, "fitness3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareLowerFitness( fitness4, "fitness4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareLowerFitness( fitness5, "fitness5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareLowerFitness( fitness6, "fitness6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareLowerFitness( fitness7, "fitness7", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareLowerFitness( fitness8, "fitness8", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareLowerFitness( fitness9, "fitness9", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareLowerFitness( fitness10, "fitness10", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareLowerFitness( fitnessN1, "fitnessN1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareLowerFitness( fitnessN2, "fitnessN2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareLowerFitness( fitnessN3, "fitnessN3", *actualFitness, szActualFitnessName );

	//compare with fitness0_4
	actualFitness = &fitness0_4;
	szActualFitnessName = "fitness0_4";
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( fitness0_1, "fitness0_1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( fitness0_2, "fitness0_2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( fitness0_3, "fitness0_3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( fitness0_4, "fitness0_4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( fitness0_5, "fitness0_5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( fitness0_6, "fitness0_6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareLowerFitness( fitness1, "fitness1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareLowerFitness( fitness2, "fitness2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareLowerFitness( fitness3, "fitness3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareLowerFitness( fitness4, "fitness4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareLowerFitness( fitness5, "fitness5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareLowerFitness( fitness6, "fitness6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareLowerFitness( fitness7, "fitness7", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareLowerFitness( fitness8, "fitness8", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareLowerFitness( fitness9, "fitness9", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareLowerFitness( fitness10, "fitness10", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareLowerFitness( fitnessN1, "fitnessN1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareLowerFitness( fitnessN2, "fitnessN2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareLowerFitness( fitnessN3, "fitnessN3", *actualFitness, szActualFitnessName );

	//compare with fitness0_5
	actualFitness = &fitness0_5;
	szActualFitnessName = "fitness0_5";
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( fitness0_1, "fitness0_1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( fitness0_2, "fitness0_2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( fitness0_3, "fitness0_3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( fitness0_4, "fitness0_4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( fitness0_5, "fitness0_5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( fitness0_6, "fitness0_6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareLowerFitness( fitness1, "fitness1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareLowerFitness( fitness2, "fitness2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareLowerFitness( fitness3, "fitness3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareLowerFitness( fitness4, "fitness4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareLowerFitness( fitness5, "fitness5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareLowerFitness( fitness6, "fitness6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareLowerFitness( fitness7, "fitness7", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareLowerFitness( fitness8, "fitness8", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareLowerFitness( fitness9, "fitness9", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareLowerFitness( fitness10, "fitness10", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareLowerFitness( fitnessN1, "fitnessN1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareLowerFitness( fitnessN2, "fitnessN2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareLowerFitness( fitnessN3, "fitnessN3", *actualFitness, szActualFitnessName );

	//compare with fitness0_6
	actualFitness = &fitness0_6;
	szActualFitnessName = "fitness0_6";
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( fitness0_1, "fitness0_1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( fitness0_2, "fitness0_2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( fitness0_3, "fitness0_3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( fitness0_4, "fitness0_4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( fitness0_5, "fitness0_5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( fitness0_6, "fitness0_6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareLowerFitness( fitness1, "fitness1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareLowerFitness( fitness2, "fitness2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareLowerFitness( fitness3, "fitness3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareLowerFitness( fitness4, "fitness4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareLowerFitness( fitness5, "fitness5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareLowerFitness( fitness6, "fitness6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareLowerFitness( fitness7, "fitness7", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareLowerFitness( fitness8, "fitness8", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareLowerFitness( fitness9, "fitness9", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareLowerFitness( fitness10, "fitness10", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareLowerFitness( fitnessN1, "fitnessN1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareLowerFitness( fitnessN2, "fitnessN2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareLowerFitness( fitnessN3, "fitnessN3", *actualFitness, szActualFitnessName );

	//compare with fitness1
	actualFitness = &fitness1;
	szActualFitnessName = "fitness1";
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( fitness0_1, "fitness0_1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( fitness0_2, "fitness0_2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( fitness0_3, "fitness0_3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( fitness0_4, "fitness0_4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( fitness0_5, "fitness0_5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( fitness0_6, "fitness0_6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareNotLowerFitness( fitness1, "fitness1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareLowerFitness( fitness2, "fitness2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareLowerFitness( fitness3, "fitness3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareLowerFitness( fitness4, "fitness4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareLowerFitness( fitness5, "fitness5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareLowerFitness( fitness6, "fitness6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareLowerFitness( fitness7, "fitness7", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareLowerFitness( fitness8, "fitness8", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareLowerFitness( fitness9, "fitness9", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareLowerFitness( fitness10, "fitness10", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( fitnessN1, "fitnessN1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( fitnessN2, "fitnessN2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( fitnessN3, "fitnessN3", *actualFitness, szActualFitnessName );

	//compare with fitness2
	actualFitness = &fitness2;
	szActualFitnessName = "fitness2";
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( fitness0_1, "fitness0_1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( fitness0_2, "fitness0_2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( fitness0_3, "fitness0_3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( fitness0_4, "fitness0_4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( fitness0_5, "fitness0_5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( fitness0_6, "fitness0_6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareNotLowerFitness( fitness1, "fitness1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareNotLowerFitness( fitness2, "fitness2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareLowerFitness( fitness3, "fitness3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareLowerFitness( fitness4, "fitness4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareLowerFitness( fitness5, "fitness5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareLowerFitness( fitness6, "fitness6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareLowerFitness( fitness7, "fitness7", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareLowerFitness( fitness8, "fitness8", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareLowerFitness( fitness9, "fitness9", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareLowerFitness( fitness10, "fitness10", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( fitnessN1, "fitnessN1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( fitnessN2, "fitnessN2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( fitnessN3, "fitnessN3", *actualFitness, szActualFitnessName );

	//compare with fitness3
	actualFitness = &fitness3;
	szActualFitnessName = "fitness3";
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( fitness0_1, "fitness0_1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( fitness0_2, "fitness0_2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( fitness0_3, "fitness0_3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( fitness0_4, "fitness0_4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( fitness0_5, "fitness0_5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( fitness0_6, "fitness0_6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareNotLowerFitness( fitness1, "fitness1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareNotLowerFitness( fitness2, "fitness2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareNotLowerFitness( fitness3, "fitness3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareLowerFitness( fitness4, "fitness4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareLowerFitness( fitness5, "fitness5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareLowerFitness( fitness6, "fitness6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareLowerFitness( fitness7, "fitness7", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareLowerFitness( fitness8, "fitness8", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareLowerFitness( fitness9, "fitness9", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareLowerFitness( fitness10, "fitness10", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( fitnessN1, "fitnessN1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( fitnessN2, "fitnessN2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( fitnessN3, "fitnessN3", *actualFitness, szActualFitnessName );

	//compare with fitness4
	actualFitness = &fitness4;
	szActualFitnessName = "fitness4";
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( fitness0_1, "fitness0_1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( fitness0_2, "fitness0_2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( fitness0_3, "fitness0_3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( fitness0_4, "fitness0_4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( fitness0_5, "fitness0_5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( fitness0_6, "fitness0_6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareNotLowerFitness( fitness1, "fitness1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareNotLowerFitness( fitness2, "fitness2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareNotLowerFitness( fitness3, "fitness3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareNotLowerFitness( fitness4, "fitness4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareLowerFitness( fitness5, "fitness5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareLowerFitness( fitness6, "fitness6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareLowerFitness( fitness7, "fitness7", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareLowerFitness( fitness8, "fitness8", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareLowerFitness( fitness9, "fitness9", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareLowerFitness( fitness10, "fitness10", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( fitnessN1, "fitnessN1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( fitnessN2, "fitnessN2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( fitnessN3, "fitnessN3", *actualFitness, szActualFitnessName );

	//compare with fitness5
	actualFitness = &fitness5;
	szActualFitnessName = "fitness5";
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( fitness0_1, "fitness0_1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( fitness0_2, "fitness0_2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( fitness0_3, "fitness0_3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( fitness0_4, "fitness0_4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( fitness0_5, "fitness0_5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( fitness0_6, "fitness0_6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareNotLowerFitness( fitness1, "fitness1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareNotLowerFitness( fitness2, "fitness2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareNotLowerFitness( fitness3, "fitness3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareNotLowerFitness( fitness4, "fitness4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareNotLowerFitness( fitness5, "fitness5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareLowerFitness( fitness6, "fitness6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareLowerFitness( fitness7, "fitness7", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareLowerFitness( fitness8, "fitness8", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareLowerFitness( fitness9, "fitness9", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareLowerFitness( fitness10, "fitness10", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( fitnessN1, "fitnessN1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( fitnessN2, "fitnessN2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( fitnessN3, "fitnessN3", *actualFitness, szActualFitnessName );

	//compare with fitness6
	actualFitness = &fitness6;
	szActualFitnessName = "fitness6";
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( fitness0_1, "fitness0_1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( fitness0_2, "fitness0_2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( fitness0_3, "fitness0_3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( fitness0_4, "fitness0_4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( fitness0_5, "fitness0_5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( fitness0_6, "fitness0_6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareNotLowerFitness( fitness1, "fitness1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareNotLowerFitness( fitness2, "fitness2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareNotLowerFitness( fitness3, "fitness3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareNotLowerFitness( fitness4, "fitness4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareNotLowerFitness( fitness5, "fitness5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( fitness6, "fitness6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( fitness7, "fitness7", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareLowerFitness( fitness8, "fitness8", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareLowerFitness( fitness9, "fitness9", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareLowerFitness( fitness10, "fitness10", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( fitnessN1, "fitnessN1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( fitnessN2, "fitnessN2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( fitnessN3, "fitnessN3", *actualFitness, szActualFitnessName );

	//compare with fitness7
	actualFitness = &fitness7;
	szActualFitnessName = "fitness7";
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( fitness0_1, "fitness0_1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( fitness0_2, "fitness0_2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( fitness0_3, "fitness0_3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( fitness0_4, "fitness0_4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( fitness0_5, "fitness0_5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( fitness0_6, "fitness0_6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareNotLowerFitness( fitness1, "fitness1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareNotLowerFitness( fitness2, "fitness2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareNotLowerFitness( fitness3, "fitness3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareNotLowerFitness( fitness4, "fitness4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareNotLowerFitness( fitness5, "fitness5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( fitness6, "fitness6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( fitness7, "fitness7", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareLowerFitness( fitness8, "fitness8", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareLowerFitness( fitness9, "fitness9", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareLowerFitness( fitness10, "fitness10", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( fitnessN1, "fitnessN1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( fitnessN2, "fitnessN2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( fitnessN3, "fitnessN3", *actualFitness, szActualFitnessName );

	//compare with fitness8
	actualFitness = &fitness8;
	szActualFitnessName = "fitness8";
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( fitness0_1, "fitness0_1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( fitness0_2, "fitness0_2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( fitness0_3, "fitness0_3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( fitness0_4, "fitness0_4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( fitness0_5, "fitness0_5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( fitness0_6, "fitness0_6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareNotLowerFitness( fitness1, "fitness1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareNotLowerFitness( fitness2, "fitness2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareNotLowerFitness( fitness3, "fitness3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareNotLowerFitness( fitness4, "fitness4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareNotLowerFitness( fitness5, "fitness5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( fitness6, "fitness6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( fitness7, "fitness7", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( fitness8, "fitness8", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( fitness9, "fitness9", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( fitness10, "fitness10", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( fitnessN1, "fitnessN1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( fitnessN2, "fitnessN2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( fitnessN3, "fitnessN3", *actualFitness, szActualFitnessName );

	//compare with fitness9
	actualFitness = &fitness9;
	szActualFitnessName = "fitness9";
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( fitness0_1, "fitness0_1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( fitness0_2, "fitness0_2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( fitness0_3, "fitness0_3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( fitness0_4, "fitness0_4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( fitness0_5, "fitness0_5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( fitness0_6, "fitness0_6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareNotLowerFitness( fitness1, "fitness1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareNotLowerFitness( fitness2, "fitness2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareNotLowerFitness( fitness3, "fitness3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareNotLowerFitness( fitness4, "fitness4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareNotLowerFitness( fitness5, "fitness5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( fitness6, "fitness6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( fitness7, "fitness7", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( fitness8, "fitness8", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( fitness9, "fitness9", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( fitness10, "fitness10", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( fitnessN1, "fitnessN1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( fitnessN2, "fitnessN2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( fitnessN3, "fitnessN3", *actualFitness, szActualFitnessName );

	//compare with fitness10
	actualFitness = &fitness10;
	szActualFitnessName = "fitness10";
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( fitness0_1, "fitness0_1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( fitness0_2, "fitness0_2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( fitness0_3, "fitness0_3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( fitness0_4, "fitness0_4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( fitness0_5, "fitness0_5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( fitness0_6, "fitness0_6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareNotLowerFitness( fitness1, "fitness1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareNotLowerFitness( fitness2, "fitness2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareNotLowerFitness( fitness3, "fitness3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareNotLowerFitness( fitness4, "fitness4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareNotLowerFitness( fitness5, "fitness5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( fitness6, "fitness6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( fitness7, "fitness7", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( fitness8, "fitness8", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( fitness9, "fitness9", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( fitness10, "fitness10", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( fitnessN1, "fitnessN1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( fitnessN2, "fitnessN2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( fitnessN3, "fitnessN3", *actualFitness, szActualFitnessName );

	//compare with fitnessN1
	actualFitness = &fitnessN1;
	szActualFitnessName = "fitnessN1";
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( fitness0_1, "fitness0_1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( fitness0_2, "fitness0_2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( fitness0_3, "fitness0_3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( fitness0_4, "fitness0_4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( fitness0_5, "fitness0_5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( fitness0_6, "fitness0_6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareLowerFitness( fitness1, "fitness1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareLowerFitness( fitness2, "fitness2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareLowerFitness( fitness3, "fitness3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareLowerFitness( fitness4, "fitness4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareLowerFitness( fitness5, "fitness5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareLowerFitness( fitness6, "fitness6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareLowerFitness( fitness7, "fitness7", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareLowerFitness( fitness8, "fitness8", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareLowerFitness( fitness9, "fitness9", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareLowerFitness( fitness10, "fitness10", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( fitnessN1, "fitnessN1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( fitnessN2, "fitnessN2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( fitnessN3, "fitnessN3", *actualFitness, szActualFitnessName );

	//compare with fitnessN2
	actualFitness = &fitnessN2;
	szActualFitnessName = "fitnessN2";
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( fitness0_1, "fitness0_1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( fitness0_2, "fitness0_2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( fitness0_3, "fitness0_3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( fitness0_4, "fitness0_4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( fitness0_5, "fitness0_5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( fitness0_6, "fitness0_6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareLowerFitness( fitness1, "fitness1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareLowerFitness( fitness2, "fitness2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareLowerFitness( fitness3, "fitness3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareLowerFitness( fitness4, "fitness4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareLowerFitness( fitness5, "fitness5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareLowerFitness( fitness6, "fitness6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareLowerFitness( fitness7, "fitness7", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareLowerFitness( fitness8, "fitness8", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareLowerFitness( fitness9, "fitness9", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareLowerFitness( fitness10, "fitness10", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( fitnessN1, "fitnessN1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( fitnessN2, "fitnessN2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( fitnessN3, "fitnessN3", *actualFitness, szActualFitnessName );

	//compare with fitnessN3
	actualFitness = &fitnessN3;
	szActualFitnessName = "fitnessN3";
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_1, "fitness0_1" );
	iReturn += testCompareNotLowerFitness( fitness0_1, "fitness0_1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_2, "fitness0_2" );
	iReturn += testCompareNotLowerFitness( fitness0_2, "fitness0_2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_3, "fitness0_3" );
	iReturn += testCompareNotLowerFitness( fitness0_3, "fitness0_3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_4, "fitness0_4" );
	iReturn += testCompareNotLowerFitness( fitness0_4, "fitness0_4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_5, "fitness0_5" );
	iReturn += testCompareNotLowerFitness( fitness0_5, "fitness0_5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareLowerFitness( *actualFitness, szActualFitnessName, fitness0_6, "fitness0_6" );
	iReturn += testCompareNotLowerFitness( fitness0_6, "fitness0_6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness1, "fitness1" );
	iReturn += testCompareLowerFitness( fitness1, "fitness1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness2, "fitness2" );
	iReturn += testCompareLowerFitness( fitness2, "fitness2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness3, "fitness3" );
	iReturn += testCompareLowerFitness( fitness3, "fitness3", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness4, "fitness4" );
	iReturn += testCompareLowerFitness( fitness4, "fitness4", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness5, "fitness5" );
	iReturn += testCompareLowerFitness( fitness5, "fitness5", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness6, "fitness6" );
	iReturn += testCompareLowerFitness( fitness6, "fitness6", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness7, "fitness7" );
	iReturn += testCompareLowerFitness( fitness7, "fitness7", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness8, "fitness8" );
	iReturn += testCompareLowerFitness( fitness8, "fitness8", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness9, "fitness9" );
	iReturn += testCompareLowerFitness( fitness9, "fitness9", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoNotEqualFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitness10, "fitness10" );
	iReturn += testCompareLowerFitness( fitness10, "fitness10", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN1, "fitnessN1" );
	iReturn += testCompareNotLowerFitness( fitnessN1, "fitnessN1", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN2, "fitnessN2" );
	iReturn += testCompareNotLowerFitness( fitnessN2, "fitnessN2", *actualFitness, szActualFitnessName );
	iReturn += testCompareTwoEqualFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( *actualFitness, szActualFitnessName, fitnessN3, "fitnessN3" );
	iReturn += testCompareNotLowerFitness( fitnessN3, "fitnessN3", *actualFitness, szActualFitnessName );

	delete pPoint;
	delete pPoint2;

	return iReturn;
}




/**
 * This function tests the setting and changing values and the
 * copyconstructor and clone method of the class.
 *
 * methods tested:
 * 	- cFibObjectFitnessBasic( double dInDistanceToOriginal, long lInSize, long lInEvaluationTime, double dInWeightDistanceToOriginal=1.0, double dInWeightSize=1.0, double dInWeightEvaluationTime=1.0, cFibObjectFitnessBasicAlgorithm * pInFibObjectFitnessAlgorithm=NULL );
 * 	- cFibObjectFitnessBasic( const cFibObjectFitnessBasic & objectFitness );
 * 	- cFibObjectFitnessBasic * clone() const;
 * 	- double getDifferenceToOriginal() const;
 * 	- bool changeDifferenceToOriginal( double dDeltaToOriginal );
 * 	- double getWeightDistanceToOriginal() const;
 * 	- long getSize() const;
 * 	- bool changeSize( long lDeltaSize );
 * 	- double getWeightSize() const;
 * 	- long getTime() const;
 * 	- bool changeTime( long lDeltaEvalueTime );
 * 	- double getWeightEvaluationTime() const;
 * 	- double getFitness() const
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testValues( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting and changing values and the copyconstructor and clone method"<<endl;
	
	
	const unsigned int uiCountAlgoritms = 8;
	vector< cFibObjectFitnessBasicAlgorithm > vecAlgorithm;
	for ( unsigned int uiActualAlgorithm = 0;
			uiActualAlgorithm < uiCountAlgoritms; uiActualAlgorithm++ ){
		vecAlgorithm.push_back( cFibObjectFitnessBasicAlgorithm(
			(cFibElement*)NULL, (double)(rand() % 65536) / 256.0,
			(double)(rand() % 65536) / 256.0, (double)(rand() % 65536) / 256.0 ) );
	}
	//fitness values
	double dDistanceToOriginal = (double)(rand() % 65536) / 32.0;
	unsigned long ulSize = rand() % 65536;
	unsigned long ulTime = rand() % 65536;
	
	double dWeightDistanceToOriginal = (double)(rand() % 65536) / 256.0;
	double dWeightSize = (double)(rand() % 65536) / 256.0;
	double dWeightTime = (double)(rand() % 65536) / 256.0;
	unsigned int uiActualAlgorithm = rand() % uiCountAlgoritms;
	
	cFibObjectFitnessBasic * pFitness = new cFibObjectFitnessBasic(
		dDistanceToOriginal, ulSize, ulTime, dWeightDistanceToOriginal,
		dWeightSize, dWeightTime, &(vecAlgorithm[ uiActualAlgorithm ]));
	
	for ( unsigned int uiIteration = 0; uiIteration < 1024; uiIteration++ ){
		
		if( rand() % 16 == 0 ){
			//create a new cFibObjectFitnessBasic object
			if ( rand() % 4 == 0 ){
				//use copy fitness
				const cFibObjectFitnessBasic * pOldFitness = pFitness;
				
				if ( rand() % 2 == 0){
					//use copyconstructor
					cout<<"pFitness = new cFibObjectFitnessBasic( *pOldFitness );"<<endl<<flush;
					pFitness = new cFibObjectFitnessBasic( *pOldFitness );
				}else{//use clone
					cout<<"pFitness = pOldFitness->clone();"<<endl<<flush;
					pFitness = pOldFitness->clone();
				}
				delete pOldFitness;
			}else{//use parameterconstructor
				delete pFitness;
				
				dDistanceToOriginal = (double)(rand() % 65536) / 32.0;
				ulSize = rand() % 65536;
				ulTime = rand() % 65536;
				
				dWeightDistanceToOriginal = (double)(rand() % 65536) / 256.0;
				dWeightSize = (double)(rand() % 65536) / 256.0;
				dWeightTime = (double)(rand() % 65536) / 256.0;
				uiActualAlgorithm = rand() % uiCountAlgoritms;
				
				cout<<"pFitness = new cFibObjectFitnessBasic( "<<
					dDistanceToOriginal <<", "<< ulSize <<", "<< ulTime <<", "<<
					dWeightDistanceToOriginal <<", "<< dWeightSize <<", "<<
					dWeightTime <<", "<< &(vecAlgorithm[ uiActualAlgorithm ]) <<");"<<endl<<flush;
				pFitness = new cFibObjectFitnessBasic(
					dDistanceToOriginal, ulSize, ulTime, dWeightDistanceToOriginal,
					dWeightSize, dWeightTime, &(vecAlgorithm[ uiActualAlgorithm ]));
			}
		}else{//change the values
			switch ( rand() % 3 ){
				case 0:{
					const double dDeltaToOriginal = (double)(rand() % 65536) / 256.0 - 128.0;
					
					cout<<"changeDifferenceToOriginal( "<< dDeltaToOriginal <<" );"<<endl;
					const bool bChanged = pFitness->changeDifferenceToOriginal( dDeltaToOriginal );
					if ( bChanged ){
						dDistanceToOriginal += dDeltaToOriginal;
					}else{
						cerr<<"Error: Couldn't change the distance to the original."<<endl;
						iReturn++;
					}
				}break;
				case 1:{
					const long lDeltaSize = (rand() % 65536) - 32768;
					
					cout<<"changeSize( "<< lDeltaSize <<" );"<<endl;
					const bool bChanged = pFitness->changeSize( lDeltaSize );
					if ( bChanged ){
						ulSize += lDeltaSize;
					}else{
						cerr<<"Error: Couldn't change the size."<<endl;
						iReturn++;
					}
				}break;
				case 2:{
					const long lDeltaTime = (rand() % 65536) - 32768;
					
					cout<<"changeSize( "<< lDeltaTime <<" );"<<endl;
					const bool bChanged = pFitness->changeTime( lDeltaTime );
					if ( bChanged ){
						ulTime += lDeltaTime;
					}else{
						cerr<<"Error: Couldn't change the evaluetime."<<endl;
						iReturn++;
					}
				}break;
			};
		}
		//test the values of the changed fitness object
		
		//check the getFitnessAlgorithm() methode from cFibObjectFitnessBasic
		if ( pFitness->getFitnessAlgorithm() == &(vecAlgorithm[ uiActualAlgorithm ]) ){
		
			cout<<"The algorithm of the fitness is correctly "<<
				&(vecAlgorithm[ uiActualAlgorithm ]) <<" . "<<endl;
		}else{
			cerr<<"Error: The algorithm of the fitness is "<<
				pFitness->getFitnessAlgorithm() <<" but should be "<<
				&(vecAlgorithm[ uiActualAlgorithm ]) <<" ."<<endl;
			iReturn++;
		}
		//check the getDifferenceToOriginal() methode from cFibObjectFitnessBasic
		if ( pFitness->getDifferenceToOriginal() == dDistanceToOriginal ){
		
			cout<<"The differnes to the original value of the fitness is correctly "<<
				dDistanceToOriginal <<" . "<<endl;
		}else{
			cerr<<"Error: The differnes to the original value of the fitness is "<<
				pFitness->getDifferenceToOriginal() <<" but should be "<<
				dDistanceToOriginal <<" ."<<endl;
			iReturn++;
		}
		//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasic
		if ( pFitness->getWeightDistanceToOriginal() == dWeightDistanceToOriginal ){
		
			cout<<"The weight for the differnes to the original of the fitness is correctly "<<
				dWeightDistanceToOriginal <<" . "<<endl;
		}else{
			cerr<<"Error: The weight for the differnes to the original of the fitness is "<<
				pFitness->getWeightDistanceToOriginal() <<" but should be "<<
				dWeightDistanceToOriginal <<" ."<<endl;
			iReturn++;
		}
		//check the getSize() methode from cFibObjectFitnessBasic
		if ( pFitness->getSize() == ulSize ){
		
			cout<<"The size of the fib -object of the fitness is correctly "<< ulSize <<" . "<<endl;
		}else{
			cerr<<"Error: The size of the fib -object of the fitness is "<<
				pFitness->getSize() <<" but should be "<< ulSize <<" ."<<endl;
			iReturn++;
		}
		//check the getWeightSize() methode from cFibObjectFitnessBasic
		if ( pFitness->getWeightSize() == dWeightSize ){
		
			cout<<"The weight for the size of the fib -object of the fitness is correctly "<<
				dWeightSize <<" . "<<endl;
		}else{
			cerr<<"Error: The weight size of the fib -object of the fitness is "<<
				pFitness->getWeightSize() <<" but should be "<< dWeightSize <<" ."<<endl;
			iReturn++;
		}
		//check the getTime() methode from cFibObjectFitnessBasic
		if ( pFitness->getTime() == ulTime ){
		
			cout<<"The evaluation time of the fib -object of the fitness is correctly "<< ulTime <<" . "<<endl;
		}else{
			cerr<<"Error: The evaluation time of the fib -object of the fitness is "<<
				pFitness->getTime() <<" but should be "<< ulTime <<" ."<<endl;
			iReturn++;
		}
		//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasic
		if ( pFitness->getWeightEvaluationTime() == dWeightTime ){
		
			cout<<"The weight for the evaluation time of the fib -object of the fitness is correctly "<<
				dWeightTime <<" . "<<endl;
		}else{
			cerr<<"Error: The weight evaluation time of the fib -object of the fitness is "<<
				pFitness->getWeightEvaluationTime() <<" but should be "<< dWeightTime <<" ."<<endl;
			iReturn++;
		}
		//check the getFitness() methode from cFibObjectFitnessBasic
		if ( isEqual( pFitness->getFitness(), evalueFitness( *pFitness ) ) ){
		
			cout<<"The fitnessvalue is correctly "<< evalueFitness( *pFitness ) <<" . "<<endl;
		}else{
			cerr<<"Error: The fitnessvalue is "<< pFitness->getFitness() <<
				" but should be "<< evalueFitness( *pFitness ) <<" ."<<endl;
			iReturn++;
		}
	}
	delete pFitness;

	return iReturn;
}











