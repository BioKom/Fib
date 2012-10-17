/**
 * @file tTypeFibMatrix
 * file name: tTypeFibMatrix.cpp
 * @author Betti Oesterholz
 * @date 05.15.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cTypeFibMatrix.
 *
 * Copyright (C) @c GPL3 2011 Betti Oesterholz
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
 * This file contains the test for the class cTypeFibMatrix,
 * which represents Fib matrix element type.
 *
 *
 *
 *  What's tested of class cTypeFibMatrix:
 * 	- cTypeFibMatrix()
 * 	- unsignedIntFib getType() const
 * 	- bool isCompatible( const cDomain &domain ) const
 * 	- cDomain *getStandardDomain( ) const
 * 	- bool equal( const cTypeElement &typeElement ) const
 * 	- bool operator==( const cTypeElement &typeElement ) const
 * 	- cTypeElement *clone() const
 * 	- bool equalElementType( const cTypeElement & typeElement ) const
 * 	- bool storeXml( ostream & ostream, const cDomain * domain = NULL ) const
 * 	- unsignedLongFib getCompressedSize() const
 * 	- bool store( ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const
 * 	- unsignedIntFib getNumberOfDomain() const;
 *
 */
/*
History:
05.15.2011  Oesterholz  created
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/

#include "version.h"

#include "cTypeFibMatrix.h"
#include "cTypeFibSet.h"
#include "cTypeProperty.h"
#include "cTypeInVar.h"
#include "cTypeDimension.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainIntegerBit.h"
#include "cDomainRational.h"
#include "cDomainVector.h"
#include "cDomainVectorOpenEnd.h"


#include "tinyxml.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <iomanip>

#include "tCompareBits.inc"

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif


using namespace fib;
using namespace std;


int testCostructor( unsigned long &ulTestphase );
int testIsCompatibleGetStandardDomain( unsigned long &ulTestphase );
int testClone( unsigned long &ulTestphase );
int testEqual( unsigned long &ulTestphase );
int testEqualElementType( unsigned long &ulTestphase );
int testStoreXml( unsigned long &ulTestphase );
int testStore( unsigned long &ulTestphase );
int testDomainNumber( unsigned long &ulTestphase );


int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cTypeFibMatrix methods"<<endl;
	cout<<      "======================================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testIsCompatibleGetStandardDomain( ulTestphase );
	iReturn += testClone( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testEqualElementType( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );
	iReturn += testDomainNumber( ulTestphase );

	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}


/**
 * This method tests the constructors and getType() method of the
 * cTypeFibMatrix class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cTypeFibMatrix"<<endl;

	cout<<"cTypeFibMatrix typeMatrixElement;"<<endl;
	cTypeFibMatrix typeMatrixElement;

	//check the getNumberOfInputComments() methode from cTypeFibMatrix
	if ( typeMatrixElement.getType() == (unsignedIntFib)(15) ){
	
		cout<<"The type of matrix element type is correctly 15 . "<<endl;
	}else{
		cerr<<"Error: The type of matrix element type is "<<
			typeMatrixElement.getType()<<" but should be 15 ."<<endl;
		iReturn++;
	}
	//check the getNumberOfInputComments() methode from cTypeFibMatrix
	if ( typeMatrixElement.getNumberOfDomain() == 0 ){
	
		cout<<"The type of matrix element domain number is correctly "<<
			typeMatrixElement.getNumberOfDomain()<<" . "<<endl;
	}else{
		cerr<<"Error: The type of matrix element domain number is "<<
			typeMatrixElement.getType()<<" but should be 0 ."<<endl;
		iReturn++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cTypeFibMatrix with given domain number"<<endl;

	cout<<"cTypeFibMatrix typeMatrixElementNr3( 3 );"<<endl;
	cTypeFibMatrix typeMatrixElementNr3( 3 );

	//check the getNumberOfInputComments() methode from cTypeFibMatrix
	if ( typeMatrixElementNr3.getType() == (unsignedIntFib)(15) ){
	
		cout<<"The type of matrix element type is correctly 15 . "<<endl;
	}else{
		cerr<<"Error: The type of matrix element type is "<<
			typeMatrixElementNr3.getType()<<" but should be 15 ."<<endl;
		iReturn++;
	}
	//check the getNumberOfInputComments() methode from cTypeFibMatrix
	if ( typeMatrixElementNr3.getNumberOfDomain() == 3 ){
	
		cout<<"The type of matrix element domain number is correctly "<<
			typeMatrixElementNr3.getNumberOfDomain()<<" . "<<endl;
	}else{
		cerr<<"Error: The type of matrix element domain number is "<<
			typeMatrixElementNr3.getType()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	return iReturn;
}



/**
 * This method tests the isCompatible() and getStandardDomain() method of
 * the cTypeFibMatrix class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testIsCompatibleGetStandardDomain( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the isCompatible() domain for the cTypeFibMatrix"<<endl;
	
	cout<<"cTypeFibMatrix typeMatrixElement;"<<endl;
	cTypeFibMatrix typeMatrixElement;

	//check the getNumberOfInputComments() methode from cTypeFibMatrix
	if ( typeMatrixElement.getType() == (unsignedIntFib)(15) ){
	
		cout<<"The type of matrix element type is correctly 15 . "<<endl;
	}else{
		cerr<<"Error: The type of matrix element type is "<<
			typeMatrixElement.getType()<<" but should be 15 ."<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt = new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! typeMatrixElement.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to an integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to a integer domain."<<endl;
		iReturn++;
	}
	delete domainInt;

	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain = new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( ! typeMatrixElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1 = new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( ! typeMatrixElement.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1[ 0 ];
	delete vectorDomain1;

	//check compatible for vector domain with two elements
	vector<cDomain*> vecDomains2( 2 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vectorDomain = new cDomainVector( vecDomains2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( ! typeMatrixElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 2 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 2 elements."<<endl;
		iReturn++;
	}
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vectorDomain;

	//check compatible for vector domain with tree elements
	vector<cDomain*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! typeMatrixElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;


	//check compatible for vector domain with four elements
	cout<<"vecDomains1El4 = (naturalNumberB( 24 ), naturalNumberB( 16 ) , naturalNumberB( 8 ), naturalNumberB( 8 ) ) "<<endl;
	vector<cDomain*> vecDomains1El4( 4 );
	vecDomains1El4[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains1El4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains1El4[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains1El4[ 3 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains1El4 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! typeMatrixElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 4 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 4 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1El4[ 0 ];
	delete vecDomains1El4[ 1 ];
	delete vecDomains1El4[ 2 ];
	delete vecDomains1El4[ 3 ];
	delete vectorDomain;

	//check compatible for vector domain with four elements
	cout<<"vecDomains2El4 = (integerB( 3 ), naturalNumberB( 4 ) , naturalNumberB( 0 ), naturalNumberB( 2 ) ) "<<endl;
	vector<cDomainSingle*> vecDomains2El4( 4 );
	vecDomains2El4[ 0 ] = new cDomainIntegerBit( 3 );
	vecDomains2El4[ 1 ] = new cDomainNaturalNumberBit( 4 );
	vecDomains2El4[ 2 ] = new cDomainNaturalNumberBit( 0 );
	vecDomains2El4[ 3 ] = new cDomainNaturalNumberBit( 2 );
	vectorDomain = new cDomainVector( vecDomains2El4 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! typeMatrixElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 4 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 4 elements."<<endl;
		iReturn++;
	}
	delete vecDomains2El4[ 0 ];
	delete vecDomains2El4[ 1 ];
	delete vecDomains2El4[ 2 ];
	delete vecDomains2El4[ 3 ];
	delete vectorDomain;

	//check compatible for vector domain with four elements
	cout<<"vecDomains3El4 = (integerB( 0 ), naturalNumberB( 0 ) , naturalNumberB( 0 ), naturalNumberB( 0 ) ) "<<endl;
	vector<cDomainSingle*> vecDomains3El4( 4 );
	vecDomains3El4[ 0 ] = new cDomainIntegerBit( 0 );
	vecDomains3El4[ 1 ] = new cDomainNaturalNumberBit( 0 );
	vecDomains3El4[ 2 ] = new cDomainNaturalNumberBit( 0 );
	vecDomains3El4[ 3 ] = new cDomainNaturalNumberBit( 0 );
	vectorDomain = new cDomainVector( vecDomains3El4 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! typeMatrixElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 4 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 4 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3El4[ 0 ];
	delete vecDomains3El4[ 1 ];
	delete vecDomains3El4[ 2 ];
	delete vecDomains3El4[ 3 ];
	delete vectorDomain;


	//check compatible for vector domain with four elements
	cout<<"vecDomains4El4 = ( naturalNumberB( 3 ), integerB( 4 ) , naturalNumberB( 5 ), naturalNumberB( 2 ) ) "<<endl;
	vector<cDomainSingle*> vecDomains4El4( 4 );
	vecDomains4El4[ 0 ] = new cDomainNaturalNumberBit( 3 );
	vecDomains4El4[ 1 ] = new cDomainIntegerBit( 4 );
	vecDomains4El4[ 2 ] = new cDomainNaturalNumberBit( 5 );
	vecDomains4El4[ 3 ] = new cDomainNaturalNumberBit( 2 );
	vectorDomain = new cDomainVector( vecDomains4El4 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! typeMatrixElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 4 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 4 elements."<<endl;
		iReturn++;
	}
	delete vecDomains4El4[ 0 ];
	delete vecDomains4El4[ 1 ];
	delete vecDomains4El4[ 2 ];
	delete vecDomains4El4[ 3 ];
	delete vectorDomain;

	//check compatible for vector domain with four elements
	cout<<"vecDomains5El4 = ( naturalNumberB( 3 ), naturalNumberB( 4 ) , integerB( 5 ), naturalNumberB( 2 ) ) "<<endl;
	vector<cDomainSingle*> vecDomains5El4( 4 );
	vecDomains5El4[ 0 ] = new cDomainNaturalNumberBit( 3 );
	vecDomains5El4[ 1 ] = new cDomainNaturalNumberBit( 4 );
	vecDomains5El4[ 2 ] = new cDomainIntegerBit( 5 );
	vecDomains5El4[ 3 ] = new cDomainNaturalNumberBit( 2 );
	vectorDomain = new cDomainVector( vecDomains5El4 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! typeMatrixElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 4 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 4 elements."<<endl;
		iReturn++;
	}
	delete vecDomains5El4[ 0 ];
	delete vecDomains5El4[ 1 ];
	delete vecDomains5El4[ 2 ];
	delete vecDomains5El4[ 3 ];
	delete vectorDomain;

	//check compatible for vector domain with four elements
	cout<<"vecDomains6El4 = ( naturalNumberB( 4 ), naturalNumberB( 4 ) , naturalNumberB( 5 ), integerB( 2 ) ) "<<endl;
	vector<cDomainSingle*> vecDomains6El4( 4 );
	vecDomains6El4[ 0 ] = new cDomainNaturalNumberBit( 3 );
	vecDomains6El4[ 1 ] = new cDomainNaturalNumberBit( 4 );
	vecDomains6El4[ 2 ] = new cDomainNaturalNumberBit( 5 );
	vecDomains6El4[ 3 ] = new cDomainIntegerBit( 2 );
	vectorDomain = new cDomainVector( vecDomains6El4 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! typeMatrixElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 4 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 4 elements."<<endl;
		iReturn++;
	}
	delete vecDomains6El4[ 0 ];
	delete vecDomains6El4[ 1 ];
	delete vecDomains6El4[ 2 ];
	delete vecDomains6El4[ 3 ];
	delete vectorDomain;

	//check compatible for vector domain with four elements
	cout<<"vecDomains7El4 = ( real( naturalNumberB( 3 ) , naturalNumberB( 2 ) ), naturalNumberB( 4 ) , naturalNumberB( 5 ), naturalNumberB( 2 ) ) "<<endl;
	vector<cDomainSingle*> vecDomains7El4( 4 );
	vecDomains7El4[ 0 ] = new cDomainRational( cDomainNaturalNumberBit( 3 ), cDomainNaturalNumberBit( 2 ) );
	vecDomains7El4[ 1 ] = new cDomainNaturalNumberBit( 4 );
	vecDomains7El4[ 2 ] = new cDomainNaturalNumberBit( 5 );
	vecDomains7El4[ 3 ] = new cDomainNaturalNumberBit( 2 );
	vectorDomain = new cDomainVector( vecDomains7El4 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! typeMatrixElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 4 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 4 elements."<<endl;
		iReturn++;
	}
	delete vecDomains7El4[ 0 ];
	delete vecDomains7El4[ 1 ];
	delete vecDomains7El4[ 2 ];
	delete vecDomains7El4[ 3 ];
	delete vectorDomain;


	//check compatible for vector domain with four elements
	cout<<"vecDomains1El5 = ( integerB( 1 ), naturalNumberB( 2 ) , naturalNumberB( 3 ), naturalNumberB( 4 ), naturalNumberB( 5 ) ) "<<endl;
	vector<cDomainSingle*> vecDomains1El5( 5 );
	vecDomains1El5[ 0 ] = new cDomainIntegerBit( 1 );
	vecDomains1El5[ 1 ] = new cDomainNaturalNumberBit( 2 );
	vecDomains1El5[ 2 ] = new cDomainNaturalNumberBit( 3 );
	vecDomains1El5[ 3 ] = new cDomainNaturalNumberBit( 4 );
	vecDomains1El5[ 4 ] = new cDomainNaturalNumberBit( 5 );
	vectorDomain = new cDomainVector( vecDomains1El5 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! typeMatrixElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 5 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 5 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1El5[ 0 ];
	delete vecDomains1El5[ 1 ];
	delete vecDomains1El5[ 2 ];
	delete vecDomains1El5[ 3 ];
	delete vecDomains1El5[ 4 ];
	delete vectorDomain;


	//check compatible for vector domain with tree elements
	cout<<"vecDomains3 = vector( 3,  naturalNumberB( 24 ), naturalNumberB( 16 ), vector( 1, naturalNumberB( 16 ) ) ) "<<endl;
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ] = new cDomainVector( vecDomains1 );
	vectorDomain = new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! typeMatrixElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vecDomains1[ 0 ];
	delete vectorDomain;
	
	//check compatible for vector domain with tree elements
	cout<<"vecDomains3 = vector( 3,  naturalNumberB( 24 ), naturalNumberB( 16 ), vector( 1, rational( naturalNumberB( 12 ), integerB( 8 ) ), integerB( 3 ) ) ) "<<endl;
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains2[ 0 ] = new cDomainRational( cDomainNaturalNumberBit( 12 ),
		cDomainIntegerBit( 3 ) );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ] = new cDomainVector( vecDomains2 );
	vectorDomain = new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! typeMatrixElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vectorDomain;

//TODO rework
	
	
	//check compatible for vector domain with tree elements
	cout<<"vecDomains1El4 = vector( 4,  naturalNumberB( 17 ), naturalNumberB( 16 ), vector( 2, naturalNumberB( 5 ), naturalNumberB( 16 ) ), vector( 1, naturalNumberB( 7 ) ) ) "<<endl;
	vecDomains1El4[ 0 ] = new cDomainNaturalNumberBit( 17 );
	vecDomains1El4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 5 );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains1El4[ 2 ] = new cDomainVector( vecDomains2 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 7 );
	vecDomains1El4[ 3 ] = new cDomainVector( vecDomains1 );
	vectorDomain = new cDomainVector( vecDomains1El4 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( typeMatrixElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain."<<endl;
		iReturn++;
	}
	delete vecDomains1El4[ 0 ];
	delete vecDomains1El4[ 1 ];
	delete vecDomains1El4[ 2 ];
	delete vecDomains1El4[ 3 ];
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vecDomains1[ 0 ];
	delete vectorDomain;
	
	//check compatible for vector domain with tree elements
	cout<<"vecDomains1El4 = vector( 4,  naturalNumberB( 15 ), naturalNumberB( 7 ), vector( 2, naturalNumberB( 8 ), naturalNumberB( 31 ) ), vector( 2, cDomainIntegerBit( 6 ), cDomainRational( cDomainNaturalNumberBit( 9 ), cDomainNaturalNumberBit( 8 ) ) ) ) "<<endl;
	vecDomains1El4[ 0 ] = new cDomainNaturalNumberBit( 15 );
	vecDomains1El4[ 1 ] = new cDomainNaturalNumberBit( 7 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ] = new cDomainIntegerBit( 31 );
	vecDomains1El4[ 2 ] = new cDomainVector( vecDomains2 );
	vector<cDomain*> vecDomains2E2( 2 );
	vecDomains2E2[ 0 ] = new cDomainIntegerBit( 6 );
	vecDomains2E2[ 1 ] = new cDomainRational( cDomainNaturalNumberBit( 9 ),
		cDomainIntegerBit( 8 ) );
	vecDomains1El4[ 3 ] = new cDomainVector( vecDomains2E2 );
	vectorDomain = new cDomainVector( vecDomains1El4 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( typeMatrixElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain."<<endl;
		iReturn++;
	}
	delete vecDomains1El4[ 0 ];
	delete vecDomains1El4[ 1 ];
	delete vecDomains1El4[ 2 ];
	delete vecDomains1El4[ 3 ];
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vecDomains2E2[ 0 ];
	delete vecDomains2E2[ 1 ];
	delete vectorDomain;
	
	//check compatible for vector domain with tree elements
	cout<<"vecDomains1El4 = vector( 4,  naturalNumberB( 15 ), naturalNumberB( 7 ), vector( 2, naturalNumberB( 8 ), cDomainIntegerBit( 12 ) ), vector( 2, cDomainIntegerBit( 6 ), cDomainRational( cDomainNaturalNumberBit( 9 ), cDomainNaturalNumberBit( 8 ) ) ) ) "<<endl;
	vecDomains1El4[ 0 ] = new cDomainNaturalNumberBit( 15 );
	vecDomains1El4[ 1 ] = new cDomainNaturalNumberBit( 7 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ] = new cDomainRational( cDomainNaturalNumberBit( 9 ),
		cDomainIntegerBit( 8 ) );
	vecDomains1El4[ 2 ] = new cDomainVector( vecDomains2 );
	vecDomains2E2[ 0 ] = new cDomainIntegerBit( 6 );
	vecDomains2E2[ 1 ] = new cDomainRational( cDomainNaturalNumberBit( 9 ),
		cDomainIntegerBit( 8 ) );
	vecDomains1El4[ 3 ] = new cDomainVector( vecDomains2E2 );
	vectorDomain = new cDomainVector( vecDomains1El4 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! typeMatrixElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain."<<endl;
		iReturn++;
	}
	delete vecDomains1El4[ 0 ];
	delete vecDomains1El4[ 1 ];
	delete vecDomains1El4[ 2 ];
	delete vecDomains1El4[ 3 ];
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vecDomains2E2[ 0 ];
	delete vecDomains2E2[ 1 ];
	delete vectorDomain;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the global standard domain for the cTypeFibMatrix"<<endl;
	//standard domain: vector( 4, naturalNumberB(8), naturalNumberB(32), vector( 2 , integerB(16), integerB(16) ), vectorOpenEnd( 1, IntegerB(32) ) ) )
	//test the getStandardDomain() method of the property
	cDomain *standardDomain = typeMatrixElement.getStandardDomain();
	
	if ( standardDomain == NULL ){
	
		cerr<<"Error: The standard domain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	}else if ( standardDomain->getType() == "DomainVector" ){
	
		//check the isCompatible() methode for vectordomain with 3 elements
		if ( typeMatrixElement.isCompatible( *standardDomain ) ){
		
			cout<<"The type is correctly compatible to the standard domain. "<<endl;
		}else{
			cerr<<"Error: The type is compatible to the standard domain."<<endl;
			iReturn++;
		}

		cout<<"The standard domain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *standardDomainVector = (cDomainVector*)standardDomain;

		unsignedIntFib uiStandardDomainVectorElements = 4;
		
		if ( standardDomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
		
			cout<<"The standard domain vector has correctly "<<
				uiStandardDomainVectorElements<<" element. "<<endl;
				
			//test domain of first vector element
			cDomain * pDomainElement1 = standardDomainVector->getElementDomain( 1 );
			if ( pDomainElement1 == NULL ){
			
				cerr<<"Error: The first element of the standard domain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			}else if ( pDomainElement1->getType() == "DomainNaturalNumberBit" ){
			
				cout<<"The first element of the standard domain is correctly an "<<
					pDomainElement1->getType()<<" domain. "<<endl;
				
				cDomainIntegerBasis * pDomainIntegerBit = (cDomainIntegerBasis*)pDomainElement1;
				
				const longFib ulMinimum = 0;
				const longFib ulMaximum = 255L;
				if ( (pDomainIntegerBit->getMinimum() == ulMinimum ) &&
						(pDomainIntegerBit->getMaximum() == ulMaximum ) ){
				
					cout<<"The domain goes correctly from "<<ulMinimum<<
						" to "<<ulMaximum<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<ulMinimum<<
						" to "<<ulMaximum<<", but it goes from "<<
						pDomainIntegerBit->getMinimum()<<" to "<<
						pDomainIntegerBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The first element of the standard domain is not of type DomainNaturalNumberBit."<<endl;
				iReturn++;
			}
			//test domain of the remaining vector element
			cDomain * pDomainElement2 = standardDomainVector->getElementDomain( 2 );
			if ( pDomainElement2 == NULL ){
			
				cerr<<"Error: The  "<<2<<"'th element of the "<<
					"standard domain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			}else if ( pDomainElement2->getType() == "DomainNaturalNumberBit" ){
			
				cout<<"The "<<2<<"'th element of the "<<
					"standard domain is correctly an "<<pDomainElement2->getType()<<" domain. "<<endl;
				
				cDomainIntegerBasis * pDomainNaturalNumberBit =
					(cDomainIntegerBasis*)pDomainElement2;
				
				const longFib ulMinimum = 0;
				const longFib ulMaximum = 256LL * 256LL * 256LL * 256LL - 1LL;
				if ( (pDomainNaturalNumberBit->getMinimum() == ulMinimum ) &&
						(pDomainNaturalNumberBit->getMaximum() == ulMaximum ) ){
				
					cout<<"The domain goes correctly from "<<ulMinimum<<
						" to "<<ulMaximum<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<ulMinimum<<
						" to "<<ulMaximum<<", but it goes from "<<
						pDomainNaturalNumberBit->getMinimum()<<" to "<<
						pDomainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The "<<2<<"'th element of the "<<
					"standard domain is not of type DomainNaturalNumberBit."<<endl;
				iReturn++;
			}
			
			
			//test domain of the remaining vector element
			cDomain * pDomainElement3 = standardDomainVector->getElementDomain( 3 );
			if ( pDomainElement3 == NULL ){
			
				cerr<<"Error: The  "<<3<<"'th element of the "<<
					"standard domain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			}else if ( pDomainElement3->getType() == "DomainVector" ){
			
				cout<<"The "<<3<<"'th element of the "<<
					"standard domain is correctly an "<<pDomainElement3->getType()<<" domain. "<<endl;
				
				cDomainVectorOpenEnd * pDomainVector =
					(cDomainVectorOpenEnd*)pDomainElement3;
				
				if ( pDomainVector->getNumberOfElements() == 2 ){
				
					cout<<"The subdomain vector for the 3. element has correctly "<<
						uiStandardDomainVectorElements<<" element. "<<endl;
						
					//test domain of first vector element
					cDomain * pDomainElement1 = pDomainVector->getElementDomain( 1 );
					if ( pDomainElement1 == NULL ){
					
						cerr<<"Error: The first element of the standard subdomain is not given back, but the Nullpointer NULL."<<endl;
						iReturn++;
						
					}else if ( pDomainElement1->getType() == "DomainIntegerBit" ){
					
						cout<<"The first element of the standard subdomain is correctly an "<<
							pDomainElement1->getType()<<" domain. "<<endl;
						
						cDomainIntegerBasis * pDomainIntegerBit =
							(cDomainIntegerBasis*)pDomainElement1;
						
						const longFib ulMinimum = 256L * -128L;
						const longFib ulMaximum = 256L * 128L - 1L;
						if ( (pDomainIntegerBit->getMinimum() == ulMinimum ) &&
								(pDomainIntegerBit->getMaximum() == ulMaximum ) ){
						
							cout<<"The domain goes correctly from "<<ulMinimum<<
								" to "<<ulMaximum<<". "<<endl;
						}else{
							cerr<<"Error: The domain goes correctly from "<<ulMinimum<<
								" to "<<ulMaximum<<", but it goes from "<<
								pDomainIntegerBit->getMinimum()<<" to "<<
								pDomainIntegerBit->getMaximum()<<"."<<endl;
							iReturn++;
						}
					}else{
						cerr<<"Error: The first element of the standard subdomain first element domain is not of type DomainIntegerBit."<<endl;
						iReturn++;
					}
					
					//test domain of first vector element
					cDomain * pDomainElement2 = pDomainVector->getElementDomain( 2 );
					if ( pDomainElement2 == NULL ){
					
						cerr<<"Error: The first element of the standard subdomain is not given back, but the Nullpointer NULL."<<endl;
						iReturn++;
						
					}else if ( pDomainElement2->getType() == "DomainIntegerBit" ){
					
						cout<<"The first element of the standard subdomain is correctly an "<<
							pDomainElement2->getType()<<" domain. "<<endl;
						
						cDomainIntegerBasis * pDomainIntegerBit =
							(cDomainIntegerBasis*)pDomainElement2;
						
						const longFib ulMinimum = 256L * -128L;
						const longFib ulMaximum = 256L * 128L - 1L;
						if ( (pDomainIntegerBit->getMinimum() == ulMinimum ) &&
								(pDomainIntegerBit->getMaximum() == ulMaximum ) ){
						
							cout<<"The domain goes correctly from "<<ulMinimum<<
								" to "<<ulMaximum<<". "<<endl;
						}else{
							cerr<<"Error: The domain goes correctly from "<<ulMinimum<<
								" to "<<ulMaximum<<", but it goes from "<<
								pDomainIntegerBit->getMinimum()<<" to "<<
								pDomainIntegerBit->getMaximum()<<"."<<endl;
							iReturn++;
						}
					}else{
						cerr<<"Error: The first element of the standard subdomain first element domain is not of type DomainIntegerBit."<<endl;
						iReturn++;
					}
				
				}else{
					cerr<<"Error: The first element of the standard subdomain is not of type DomainVector."<<endl;
					iReturn++;
				}
				
			}else{
				cerr<<"Error: The "<<3<<"'th element of the "<<
					"standard subdomain is not of type DomainVector."<<endl;
				iReturn++;
			}
			
			
			//test domain of the remaining vector element
			cDomain * pDomainElement4 = standardDomainVector->getElementDomain( 4 );
			if ( pDomainElement4 == NULL ){
			
				cerr<<"Error: The  "<<4<<"'th element of the "<<
					"standard domain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			}else if ( pDomainElement4->getType() == "DomainVectorOpenEnd" ){
			
				cout<<"The "<<4<<"'th element of the "<<
					"standard domain is correctly an "<<pDomainElement4->getType()<<" domain. "<<endl;
				
				cDomainVectorOpenEnd * pDomainVectorOpenEnd =
					(cDomainVectorOpenEnd*)pDomainElement4;
				
				if ( pDomainVectorOpenEnd->getNumberOfElements() == 1 ){
				
					cout<<"The subdomain vector for the 4. element has correctly "<<
						uiStandardDomainVectorElements<<" element. "<<endl;
						
					//test domain of first vector element
					cDomain * pDomainElement1 = pDomainVectorOpenEnd->getElementDomain( 1 );
					if ( pDomainElement1 == NULL ){
					
						cerr<<"Error: The first element of the standard subdomain is not given back, but the Nullpointer NULL."<<endl;
						iReturn++;
						
					}else if ( pDomainElement1->getType() == "DomainIntegerBit" ){
					
						cout<<"The first element of the standard subdomain is correctly an "<<
							pDomainElement1->getType()<<" domain. "<<endl;
						
						cDomainIntegerBasis * pDomainIntegerBit =
							(cDomainIntegerBasis*)pDomainElement1;
						
						const longFib ulMinimum = 256LL * 256LL * 256LL * -128LL;
						const longFib ulMaximum = 256LL * 256LL * 256LL * 128LL - 1LL;
						if ( (pDomainIntegerBit->getMinimum() == ulMinimum ) &&
								(pDomainIntegerBit->getMaximum() == ulMaximum ) ){
						
							cout<<"The domain goes correctly from "<<ulMinimum<<
								" to "<<ulMaximum<<". "<<endl;
						}else{
							cerr<<"Error: The domain goes correctly from "<<ulMinimum<<
								" to "<<ulMaximum<<", but it goes from "<<
								pDomainIntegerBit->getMinimum()<<" to "<<
								pDomainIntegerBit->getMaximum()<<"."<<endl;
							iReturn++;
						}
					}else{
						cerr<<"Error: The first element of the standard subdomain first element domain is not of type DomainIntegerBit."<<endl;
						iReturn++;
					}
				
				}else{
					cerr<<"Error: The first element of the standard subdomain has not 1 subdomain."<<endl;
					iReturn++;
				}
				
			}else{
				cerr<<"Error: The "<<4<<"'th element of the "<<
					"standard subdomain is not of type DomainVectorOpenEnd."<<endl;
				iReturn++;
			}
			
		
		}else{
			cerr<<"Error: The standard domain has "<<
				standardDomainVector->getNumberOfElements()<<" elements and not "<<
				uiStandardDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
		delete standardDomain;
	}else{
		cerr<<"Error: The standard domain has the type "<<
			standardDomain->getType()<<" and not the type cDomainNaturalNumberBit."<<endl;
		iReturn++;
		delete standardDomain;
	}
	
	return iReturn;
}



/**
 * This method tests the clone() method of the class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testClone( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the clone() method"<<endl;

	cout<<"cTypeFibMatrix typeMatrixElement;"<<endl;
	cTypeFibMatrix typeMatrixElement;

	cout<<"cTypeFibMatrix *typeMatrixElementClone1 = typeMatrixElement.clone();"<<endl;
	cTypeFibMatrix *typeMatrixElementClone1 = typeMatrixElement.clone();


	cout<<endl<<"checking the clone:"<<endl;
	//check the getNumberOfInputComments() methode from cTypeFibMatrix
	if ( typeMatrixElement.getType() == (unsignedIntFib)(15) ){
	
		cout<<"The type of matrix element type is correctly 15 . "<<endl;
	}else{
		cerr<<"Error: The type of matrix element type is "<<
			typeMatrixElement.getType()<<" but should be 15 ."<<endl;
		iReturn++;
	}
	delete typeMatrixElementClone1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the clone() method"<<endl;

	cout<<"cTypeFibMatrix typeMatrixElement152( 152 );"<<endl;
	cTypeFibMatrix typeMatrixElement152( 152 );

	cout<<"cTypeFibMatrix * typeMatrixElement152Clone1 = typeMatrixElement152.clone();"<<endl;
	cTypeFibMatrix * typeMatrixElement152Clone1 = typeMatrixElement152.clone();


	cout<<endl<<"checking the clone:"<<endl;
	//check the getNumberOfInputComments() methode from cTypeFibMatrix
	if ( typeMatrixElement152.getType() == (unsignedIntFib)(15) ){
	
		cout<<"The type of matrix element type is correctly 15 . "<<endl;
	}else{
		cerr<<"Error: The type of matrix element type is "<<
			typeMatrixElement152.getType()<<" but should be 15 ."<<endl;
		iReturn++;
	}
	delete typeMatrixElement152Clone1;

	return iReturn;
}



/**
 * This method tests the equal() method and the operator== of two given
 * cTypeElement objects which are equal.
 *
 * @param typeElement1 the first type to compare
 * @param szNameType1 the name of the first type to compare
 * @param typeElement2 the secound type to compare to
 * @param szNameType2 the name of the secound type to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualTyps( const cTypeElement &typeElement1, const string &szNameType1,
	const cTypeElement &typeElement2, const string &szNameType2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( typeElement1.equal( typeElement2 ) ){
	
		cout<<"The "<<szNameType1<<" is equal to "<<szNameType2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameType1<<" is not equal to "<<
			szNameType2<<"."<<endl;
		iReturn++;
	}
	if ( typeElement1==typeElement2 ){
	
		cout<<"The "<<szNameType1<<" is equal (operator==) to "<<
			szNameType2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameType1<<" is not equal (operator==) to "<<
			szNameType2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the equal() method and the operator== of two given
 * cTypeElement objects which are not equal.
 *
 * @param typeElement1 the first type to compare
 * @param szNameType1 the name of the first type to compare
 * @param typeElement2 the secound type to compare to
 * @param szNameType2 the name of the secound type to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoNotEqualTyps( const cTypeElement &typeElement1, const string &szNameType1,
	const cTypeElement &typeElement2, const string &szNameType2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( ! typeElement1.equal( typeElement2 ) ){
	
		cout<<"The "<<szNameType1<<" is not equal to "<<szNameType2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameType1<<" is equal to "<<
			szNameType2<<"."<<endl;
		iReturn++;
	}
	if ( ! (typeElement1==typeElement2) ){
	
		cout<<"The "<<szNameType1<<" is not equal (operator==) to "<<
			szNameType2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameType1<<" is equal (operator==) to "<<
			szNameType2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the equal() method and the operator== of the class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testEqual( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the equal method and the operator== "<<endl;

	//create cTypeFibMatrixs to compare
	cout<<"cTypeFibMatrix typeMatrixElement1;"<<endl;
	cTypeFibMatrix typeMatrixElement1;
	cout<<"cTypeFibMatrix typeMatrixElement2;"<<endl;
	cTypeFibMatrix typeMatrixElement2;

	cout<<"cTypeFibMatrix typeMatrixElementNr1( 1 );"<<endl;
	cTypeFibMatrix typeMatrixElementNr1( 1 );

	cout<<"cTypeFibMatrix typeMatrixElementNr3( 3 );"<<endl;
	cTypeFibMatrix typeMatrixElementNr3( 3 );

	cout<<"cTypeFibMatrix typeMatrixElementNr12( 12 );"<<endl;
	cTypeFibMatrix typeMatrixElementNr12( 12 );
	
	cout<<"cTypeFibSet typeFibSet;"<<endl;
	cTypeFibSet typeFibSet;

	cout<<"cTypeInVar typeInVar1N1( 1 );"<<endl;
	cTypeInVar typeInVar1N1( 1 );

	cout<<"cTypeProperty typeProperty( 1 );"<<endl;
	cTypeProperty typeProperty( 1 );

	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with typeMatrixElement1
	cTypeElement *actualType = &typeMatrixElement1;
	string szActualTypeName = "typeMatrixElement1";
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeMatrixElement1, "typeMatrixElement1" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeMatrixElement2, "typeMatrixElement2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr1, "typeMatrixElementNr1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr3, "typeMatrixElementNr3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr12, "typeMatrixElementNr12" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeFibSet, "typeFibSet" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeMatrixElement2
	actualType = &typeMatrixElement2;
	szActualTypeName = "typeMatrixElement2";
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeMatrixElement1, "typeMatrixElement1" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeMatrixElement2, "typeMatrixElement2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr1, "typeMatrixElementNr1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr3, "typeMatrixElementNr3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr12, "typeMatrixElementNr12" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeFibSet, "typeFibSet" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );
	
	//compare with typeMatrixElementNr1
	actualType = &typeMatrixElementNr1;
	szActualTypeName = "typeMatrixElementNr1";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElement1, "typeMatrixElement1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElement2, "typeMatrixElement2" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr1, "typeMatrixElementNr1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr3, "typeMatrixElementNr3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr12, "typeMatrixElementNr12" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeFibSet, "typeFibSet" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeMatrixElementNr3
	actualType = &typeMatrixElementNr3;
	szActualTypeName = "typeMatrixElementNr3";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElement1, "typeMatrixElement1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElement2, "typeMatrixElement2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr1, "typeMatrixElementNr1" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr3, "typeMatrixElementNr3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr12, "typeMatrixElementNr12" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeFibSet, "typeFibSet" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeMatrixElementNr12
	actualType = &typeMatrixElementNr12;
	szActualTypeName = "typeMatrixElementNr12";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElement1, "typeMatrixElement1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElement2, "typeMatrixElement2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr1, "typeMatrixElementNr1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr3, "typeMatrixElementNr3" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr12, "typeMatrixElementNr12" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeFibSet, "typeFibSet" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );
	
	//compare with typeFibSet
	actualType = &typeFibSet;
	szActualTypeName = "typeFibSet";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElement1, "typeMatrixElement1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElement2, "typeMatrixElement2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr1, "typeMatrixElementNr1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr3, "typeMatrixElementNr3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr12, "typeMatrixElementNr12" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeFibSet, "typeFibSet" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeInVar1N1
	actualType = &typeInVar1N1;
	szActualTypeName = "typeInVar1N1";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElement1, "typeMatrixElement1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElement2, "typeMatrixElement2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr1, "typeMatrixElementNr1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr3, "typeMatrixElementNr3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr12, "typeMatrixElementNr12" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeFibSet, "typeFibSet" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeProperty
	actualType = &typeProperty;
	szActualTypeName = "typeProperty";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElement1, "typeMatrixElement1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElement2, "typeMatrixElement2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr1, "typeMatrixElementNr1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr3, "typeMatrixElementNr3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeMatrixElementNr12, "typeMatrixElementNr12" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeFibSet, "typeFibSet" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	return iReturn;
}


/**
 * This method tests the equalElementType() method of the class.
 *
 * methods tested:
 * 	- bool equalElementType( const cTypeElement & typeElement ) const
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testEqualElementType( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the equalElementType method "<<endl;

	//create cTypeDimensions to compare
	cout<<"cTypeFibMatrix typeMatrixElement1;"<<endl;
	cTypeFibMatrix typeMatrixElement1;
	
	cout<<"cTypeFibMatrix typeMatrixElement2;"<<endl;
	cTypeFibMatrix typeMatrixElement2;

	cout<<"cTypeFibMatrix typeMatrixElementNr1( 1 );"<<endl;
	cTypeFibMatrix typeMatrixElementNr1( 1 );

	cout<<"cTypeFibMatrix typeMatrixElementNr3( 3 );"<<endl;
	cTypeFibMatrix typeMatrixElementNr3( 3 );

	cout<<"cTypeFibMatrix typeMatrixElementNr12( 12 );"<<endl;
	cTypeFibMatrix typeMatrixElementNr12( 12 );

	cout<<"cTypeFibSet typeFibSet;"<<endl;
	cTypeFibSet typeFibSet;

	cout<<"cTypeInVar typeInVar1( 1 );"<<endl;
	cTypeInVar typeInVar1( 1 );

	cout<<"cTypeProperty typeProperty( 1 );"<<endl;
	cTypeProperty typeProperty( 1 );

	cout<<"cTypeDimension typeDimension1D3( 3 );"<<endl;
	cTypeDimension typeDimension1D3( 3 );


	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	if ( typeMatrixElement1.equalElementType( typeMatrixElement1 ) ){
	
		cout<<"The typeMatrixElement1 is of the same type as typeMatrixElement1. "<<endl;
	}else{
		cerr<<"Error: The typeMatrixElement1 is not of the same type as typeMatrixElement1."<<endl;
		iReturn++;
	}
	if ( typeMatrixElement1.equalElementType( typeMatrixElement2 ) ){
	
		cout<<"The typeMatrixElement1 is of the same type as typeMatrixElement2. "<<endl;
	}else{
		cerr<<"Error: The typeMatrixElement1 is not of the same type as typeMatrixElement2."<<endl;
		iReturn++;
	}
	if ( ! typeMatrixElement1.equalElementType( typeMatrixElementNr1 ) ){
	
		cout<<"The typeMatrixElement1 is not of the same type as typeMatrixElementNr1. "<<endl;
	}else{
		cerr<<"Error: The typeMatrixElement1 is of the same type as typeMatrixElementNr1."<<endl;
		iReturn++;
	}
	if ( ! typeMatrixElement1.equalElementType( typeMatrixElementNr3 ) ){
	
		cout<<"The typeMatrixElement1 is not of the same type as typeMatrixElementNr3. "<<endl;
	}else{
		cerr<<"Error: The typeMatrixElement1 is of the same type as typeMatrixElementNr3."<<endl;
		iReturn++;
	}
	if ( ! typeMatrixElement1.equalElementType( typeMatrixElementNr12 ) ){
	
		cout<<"The typeMatrixElement1 is not of the same type as typeMatrixElementNr12. "<<endl;
	}else{
		cerr<<"Error: The typeMatrixElement1 is of the same type as typeMatrixElementNr12."<<endl;
		iReturn++;
	}
	if ( ! typeMatrixElement1.equalElementType( typeFibSet ) ){
	
		cout<<"The typeMatrixElement1 is not of the same type as typeFibSet. "<<endl;
	}else{
		cerr<<"Error: The typeMatrixElement1 is of the same type as typeFibSet."<<endl;
		iReturn++;
	}
	if ( ! typeMatrixElement1.equalElementType( typeInVar1 ) ){
	
		cout<<"The typeMatrixElement1 is not of the same type as typeInVar1. "<<endl;
	}else{
		cerr<<"Error: The typeMatrixElement1 is of the same type as typeInVar1."<<endl;
		iReturn++;
	}
	if ( ! typeMatrixElement1.equalElementType( typeProperty ) ){
	
		cout<<"The typeMatrixElement1 is not of the same type as typeProperty. "<<endl;
	}else{
		cerr<<"Error: The typeMatrixElement1 is of the same type as typeProperty."<<endl;
		iReturn++;
	}
	if ( ! typeMatrixElement1.equalElementType( typeDimension1D3 ) ){
	
		cout<<"The typeMatrixElement1 is not of the same type as typeDimension1D3. "<<endl;
	}else{
		cerr<<"Error: The typeMatrixElement1 is of the same type as typeDimension1D3."<<endl;
		iReturn++;
	}


	if ( ! typeMatrixElementNr3.equalElementType( typeMatrixElement1 ) ){
	
		cout<<"The typeMatrixElementNr3 is not of the same type as typeMatrixElement1. "<<endl;
	}else{
		cerr<<"Error: The typeMatrixElementNr3 is of the same type as typeMatrixElement1."<<endl;
		iReturn++;
	}
	if ( ! typeMatrixElementNr3.equalElementType( typeMatrixElement2 ) ){
	
		cout<<"The typeMatrixElementNr3 is not of the same type as typeMatrixElement2. "<<endl;
	}else{
		cerr<<"Error: The typeMatrixElementNr3 is of the same type as typeMatrixElement2."<<endl;
		iReturn++;
	}
	if ( ! typeMatrixElementNr3.equalElementType( typeMatrixElementNr1 ) ){
	
		cout<<"The typeMatrixElementNr3 is not of the same type as typeMatrixElementNr1. "<<endl;
	}else{
		cerr<<"Error: The typeMatrixElementNr3 is of the same type as typeMatrixElementNr1."<<endl;
		iReturn++;
	}
	if ( typeMatrixElementNr3.equalElementType( typeMatrixElementNr3 ) ){
	
		cout<<"The typeMatrixElementNr3 is of the same type as typeMatrixElementNr3. "<<endl;
	}else{
		cerr<<"Error: The typeMatrixElementNr3 is not of the same type as typeMatrixElementNr3."<<endl;
		iReturn++;
	}
	if ( ! typeMatrixElementNr3.equalElementType( typeMatrixElementNr12 ) ){
	
		cout<<"The typeMatrixElementNr3 is not of the same type as typeMatrixElementNr12. "<<endl;
	}else{
		cerr<<"Error: The typeMatrixElementNr3 is of the same type as typeMatrixElementNr12."<<endl;
		iReturn++;
	}
	if ( ! typeMatrixElementNr3.equalElementType( typeFibSet ) ){
	
		cout<<"The typeMatrixElementNr3 is not of the same type as typeFibSet. "<<endl;
	}else{
		cerr<<"Error: The typeMatrixElementNr3 is of the same type as typeFibSet."<<endl;
		iReturn++;
	}
	if ( ! typeMatrixElementNr3.equalElementType( typeInVar1 ) ){
	
		cout<<"The typeMatrixElementNr3 is not of the same type as typeInVar1. "<<endl;
	}else{
		cerr<<"Error: The typeMatrixElementNr3 is of the same type as typeInVar1."<<endl;
		iReturn++;
	}
	if ( ! typeMatrixElementNr3.equalElementType( typeProperty ) ){
	
		cout<<"The typeMatrixElementNr3 is not of the same type as typeProperty. "<<endl;
	}else{
		cerr<<"Error: The typeMatrixElementNr3 is of the same type as typeProperty."<<endl;
		iReturn++;
	}
	if ( ! typeMatrixElementNr3.equalElementType( typeDimension1D3 ) ){
	
		cout<<"The typeMatrixElementNr3 is not of the same type as typeDimension1D3. "<<endl;
	}else{
		cerr<<"Error: The typeMatrixElementNr3 is of the same type as typeDimension1D3."<<endl;
		iReturn++;
	}
	
	
	return iReturn;
}



/**
 * This method tests a in the xml -format stored cDomainVector with
 * cDomainNaturalNumberBit domains.
 *
 * @param szFilename the name of the file wher the cDomainNaturalNumberBit is stored
 * @param uiDomainNumber the number of the domain for the type
 * @param uiBits a vector with the bits the cDomainNaturalNumberBit
 * 	domains have
 * @param scalingfactor a vector with the scalingfactors for the
 * 	cDomainNaturalNumberBit domains have
 * @return the number of errors occured in the test
 */
int testXmlType( const string szFilename, const unsigned int uiDomainNumber,
		bool bHasDomain, unsigned int uiBits, double dScalingfactor ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored type:"<<endl;
	
	TiXmlDocument xmlDocVectorPosition( szFilename );
	bool loadOkay = xmlDocVectorPosition.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the type was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocVectorPosition );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlRootHandle( 0 );

	pXmlElement = xmlHandle.FirstChildElement().Element();
	
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();

		if ( szElementName == "matrixElement" ){
			cout<<"The root element is correctly named \"matrixElement\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"matrixElement\"."<<endl;
			iReturn++;
		}
		
		int iNumberOfInVarLoaded = 0;
		const char * pcAttributNumber = pXmlElement->Attribute( "domainNr",
			&iNumberOfInVarLoaded );
		
		if ( uiDomainNumber == 0 ){
			if ( pcAttributNumber != NULL ){
				cerr<<"Error: The type has an attribute \"domainNr\", but domain number "<<
					uiDomainNumber<<" ."<<endl;
				iReturn++;
			}else{
				cout<<"The type has correctly no attribute \"domainNr\"."<<endl;
			}
		}else{
			if ( pcAttributNumber == NULL ){
				cerr<<"Error: The type has no attribute \"domainNr\"."<<endl;
				iReturn++;
			}else if ( iNumberOfInVarLoaded == (int)uiDomainNumber ) {
				cout<<"The number of the domain is correctly \""<<
					uiDomainNumber <<"\". "<<endl;
			}else{
				cerr<<"Error: The number of the domain is \""<<
					iNumberOfInVarLoaded <<"\", but should be \""<<
					uiDomainNumber <<"\"."<<endl;
				iReturn++;
			}
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}

	if ( bHasDomain ){
		//read the subdomain
	
		xmlRootHandle = xmlHandle.FirstChildElement();
	
		pXmlElement = xmlRootHandle.FirstChildElement().Element();
	
		// should always have a valid root but handle gracefully if it does
		string szElementName = pXmlElement->Value();
	
		if ( szElementName == "naturalNumberB" ){
			cout<<"The  element is correctly named \"naturalNumberB\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the element is \""<< szElementName <<"\" and not \"naturalNumberB\"."<<endl;
			iReturn++;
		}
		
		int iBitsLoaded = 0;
		const char * pcAttributBits = pXmlElement->Attribute( "bit", &iBitsLoaded );
		
		if ( pcAttributBits == NULL ){
			cerr<<"Error: The domain has no attribute bits."<<endl;
			iReturn++;
		}else if ( iBitsLoaded == (int)uiBits ) {
			cout<<"The number of bits of the domain are correctly \""<< uiBits <<"\". "<<endl;
		}else{
			cerr<<"Error: The number of bits of the loaded domain are \""<< iBitsLoaded
				<<"\", but should be \""<< uiBits <<"\"."<<endl;
			iReturn++;
		}
	
		const char * pcAttributeScalingfactor =
			pXmlElement->Attribute( "scalingfactor" );
		
		longFib lfMantissa;
		longFib lfExponent;
		decomposeDoubleFib( dScalingfactor, & lfMantissa, & lfExponent );
		
		long lMantissa = lfMantissa;
		long lExponent = lfExponent;
	
		char szScalingfactorBuffer[158];
		szScalingfactorBuffer[0] = 0;
		sprintf ( szScalingfactorBuffer, "%li * 2^(%li)", lMantissa, lExponent );
		
		string szScalingfactor( szScalingfactorBuffer );
		
		if ( ( dScalingfactor == 1.0 ) && ( pcAttributeScalingfactor == NULL ) ){
			//no scalingfactor needed
			cout<<"No scalingfactor attribut. This is correct because the scalingfactor is 1.0 . "<<endl;
		}else{
			if ( pcAttributeScalingfactor == NULL ){
				cerr<<"Error: The domain has no attribute scalingfactor."<<endl;
				iReturn++;
			}else if ( szScalingfactor == pcAttributeScalingfactor ) {
				cout<<"The scalingfactor of the domain is correctly \""<< pcAttributeScalingfactor <<"\". "<<endl;
			}else{
				cerr<<"Error: The scalingfactor of the loaded domain is \""<< pcAttributeScalingfactor
					<<"\", but should be \""<< dScalingfactor <<"\" (=\""<< szScalingfactor <<"\")."<<endl;
				iReturn++;
			}
		}
	}

	return iReturn;
}


/**
 * This method storeXml() method of the class.
 *
 * methods tested:
 * 	- bool storeXml( ostringstream & ostream ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStoreXml( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple matrix element type"<<endl;

	cout<<"cTypeFibMatrix typeMatrixElement1;"<<endl;
	cTypeFibMatrix typeMatrixElement1;

	char szFileNameBuffer[158];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeMatrixElement1.xml" );
	ofstream * fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeMatrixElement1.storeXml( *fileXml );"<<endl;
	bool bStoreSuccesfull = typeMatrixElement1.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, 0, false,
		0, 0.0 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple matrix element type with domain number 3"<<endl;

	cout<<"cTypeFibMatrix typeMatrixElementNr3( 3 );"<<endl;
	cTypeFibMatrix typeMatrixElementNr3( 3 );

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeMatrixElementNr3.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeMatrixElementNr3.storeXml( *fileXml );"<<endl;
	bStoreSuccesfull = typeMatrixElementNr3.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, 3, false,
		0, 0.0 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a 5'th matrix element type with a domain"<<endl;

	cout<<"cDomainNaturalNumberBit domainNaturalNumberB4( 4 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberB4( 4 );
	unsigned int uiBits = 4;
	double dScalingfactor = 1.0;

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeMatrixElement1Dom.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeMatrixElement1.storeXml( *fileXml, &domainNaturalNumberB4 );"<<endl;
	bStoreSuccesfull = typeMatrixElement1.storeXml( *fileXml, &domainNaturalNumberB4 );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, 0, true,
		uiBits, dScalingfactor );


	return iReturn;
}


/**
 * This method store() method of the class.
 *
 * methods tested:
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostringstream & ostream ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStore( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple matrix element type for matrix element"<<endl;
	
	cout<<"cTypeFibMatrix typeMatrixElement1;"<<endl;
	cTypeFibMatrix typeMatrixElement1;

	//test get compressed size
	unsigned int uiCompressedSize = 8;
	if ( (unsigned int)(typeMatrixElement1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeMatrixElement1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[158];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeMatrixElement1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	bool bStoreSuccesfull = typeMatrixElement1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeFibMatrix1[] = { (char)0xD8,
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeFibMatrix1, 2 );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple matrix element type for domain number 1"<<endl;
	
	cout<<"cTypeFibMatrix typeMatrixElementNR1( 1 );"<<endl;
	cTypeFibMatrix typeMatrixElementNR1( 1 );

	//test get compressed size
	uiCompressedSize = 16;
	if ( (unsigned int)(typeMatrixElementNR1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeMatrixElementNR1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeMatrixElementNR1.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = typeMatrixElementNR1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeFibMatrixNr1[] = { (char)0xDA,
		(char)0x01, (char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeFibMatrixNr1, 3 );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple matrix element type for domain number 255"<<endl;
	
	cout<<"cTypeFibMatrix typeMatrixElementNR255( 255 );"<<endl;
	cTypeFibMatrix typeMatrixElementNR255( 255 );

	//test get compressed size
	uiCompressedSize = 16;
	if ( (unsigned int)(typeMatrixElementNR255.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeMatrixElementNR255.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeMatrixElementNR255.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = typeMatrixElementNR255.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeFibMatrix255[] = { (char)0xDA,
		(char)0xFF, (char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeFibMatrix255, 3 );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple matrix element type for domain number 256"<<endl;
	
	cout<<"cTypeFibMatrix typeMatrixElementNR256( 256 );"<<endl;
	cTypeFibMatrix typeMatrixElementNR256( 256 );

	//test get compressed size
	uiCompressedSize = 72;
	if ( (unsigned int)(typeMatrixElementNR256.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeMatrixElementNR256.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeMatrixElementNR256.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = typeMatrixElementNR256.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}
	//test stored data
	const char cTypeFibMatrixNr256[] = { (char)0xDC,
		(char)0x00, (char)0x01, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeFibMatrixNr256, 10 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a matrix element type with 5 restbits"<<endl;

	//test get compressed size
	uiCompressedSize = 8;
	if ( (unsigned int)(typeMatrixElement1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeMatrixElement1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeMatrixElement1R5.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x05;
	cNumberOfRestBit = 5 ;
	bStoreSuccesfull = typeMatrixElement1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	unsigned char ucRestBit = cRestBit;
	if ( ( ucRestBit == (unsigned char)((char)0x1B) ) && ( cNumberOfRestBit == 5 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x1B and number of restbit should be 5. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeFibMatrix5[] = { (char)0x05, (char)0x1B };
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeFibMatrix5, 2 );

	return iReturn;
}


/**
 * This method getNumberOfDomain() method of the class.
 *
 * methods tested:
 * 	- unsignedIntFib getNumberOfDomain() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testDomainNumber( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing getNumberOfDomain() method"<<endl;
	
	for ( unsigned int iteration = 0; iteration < 128; iteration++ ){
		
		const unsigned long  ulNumberOfDomain = rand() % ( 1 + rand() % (
			1 + rand() % (256L * 256L) ) );
		
		cout<<"cTypeFibMatrix typeMatrixElement( "<<ulNumberOfDomain<<" );"<<endl;
		cTypeFibMatrix typeMatrixElement( ulNumberOfDomain );
		
			//check the getNumberOfInputComments() methode from cTypeFibMatrix
		if ( typeMatrixElement.getNumberOfDomain() == ulNumberOfDomain ){
		
			cout<<"The type of matrix element domain number is correctly "<<
				typeMatrixElement.getNumberOfDomain()<<" . "<<endl;
		}else{
			cerr<<"Error: The type matrix element domain number is "<<
				typeMatrixElement.getType()<<" but should be "<<
				ulNumberOfDomain<<" ."<<endl;
			iReturn++;
		}
	}

	return iReturn;
}








