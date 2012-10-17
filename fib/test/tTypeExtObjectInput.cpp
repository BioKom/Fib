/**
 * @file tTypeExtObjectInput
 * file name: tTypeExtObjectInput.cpp
 * @author Betti Oesterholz
 * @date 21.01.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cTypeExtObjectInput.
 *
 * Copyright (C) @c GPL3 2012 Betti Oesterholz
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
 * This file contains the test for the class cTypeExtObjectInput,
 * which represents Fib external objekt input type.
 *
 *
 *
 *  What's tested of class cTypeExtObjectInput:
 * 	- cTypeExtObjectInput()
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
 * 	- unsignedIntFib getExtObjectIdentifier() const;
 *
 */
/*
History:
21.01.2012  Oesterholz  created
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/

#include "version.h"

#include "cTypeExtObjectInput.h"
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
int testIdentifier( unsigned long &ulTestphase );

int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cTypeExtObjectInput methods"<<endl;
	cout<<      "============================================"<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testIsCompatibleGetStandardDomain( ulTestphase );
	iReturn += testClone( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testEqualElementType( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );
	iReturn += testIdentifier( ulTestphase );

	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}


/**
 * This method tests the constructors and getType() method of the
 * cTypeExtObjectInput class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cTypeExtObjectInput"<<endl;

	cout<<"cTypeExtObjectInput typeExtObjElement( 0 );"<<endl;
	cTypeExtObjectInput typeExtObjElement( 0 );

	//check the getNumberOfInputComments() methode from cTypeExtObjectInput
	if ( typeExtObjElement.getType() == (unsignedIntFib)(16) ){
	
		cout<<"The type of external objekt input type is correctly 16 . "<<endl;
	}else{
		cerr<<"Error: The type of external objekt input type is "<<
			typeExtObjElement.getType()<<" but should be 16 ."<<endl;
		iReturn++;
	}
	//check the getNumberOfInputComments() methode from cTypeExtObjectInput
	if ( typeExtObjElement.getExtObjectIdentifier() == 0 ){
	
		cout<<"The type of external objekt input identifier is correctly "<<
			typeExtObjElement.getExtObjectIdentifier()<<" . "<<endl;
	}else{
		cerr<<"Error: The type of external objekt input identifier is "<<
			typeExtObjElement.getType()<<" but should be 0 ."<<endl;
		iReturn++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cTypeExtObjectInput with given identifier"<<endl;

	cout<<"cTypeExtObjectInput typeExtObjElementId3( 3 );"<<endl;
	cTypeExtObjectInput typeExtObjElementId3( 3 );

	//check the getNumberOfInputComments() methode from cTypeExtObjectInput
	if ( typeExtObjElementId3.getType() == (unsignedIntFib)(16) ){
	
		cout<<"The type of external objekt input type is correctly 16 . "<<endl;
	}else{
		cerr<<"Error: The type of external objekt input type is "<<
			typeExtObjElementId3.getType()<<" but should be 16 ."<<endl;
		iReturn++;
	}
	//check the getNumberOfInputComments() methode from cTypeExtObjectInput
	if ( typeExtObjElementId3.getExtObjectIdentifier() == 3 ){
	
		cout<<"The type of external objekt input identifier is correctly "<<
			typeExtObjElementId3.getExtObjectIdentifier()<<" . "<<endl;
	}else{
		cerr<<"Error: The type of external objekt input identifier is "<<
			typeExtObjElementId3.getType()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	return iReturn;
}



/**
 * This method tests the isCompatible() and getStandardDomain() method of
 * the cTypeExtObjectInput class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testIsCompatibleGetStandardDomain( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the isCompatible() domain for the cTypeExtObjectInput"<<endl;
	
	cout<<"cTypeExtObjectInput typeExtObjElement( 0 );"<<endl;
	cTypeExtObjectInput typeExtObjElement( 0 );

	//check the getNumberOfInputComments() methode from cTypeExtObjectInput
	if ( typeExtObjElement.getType() == (unsignedIntFib)(16) ){
	
		cout<<"The type of external objekt input type is correctly 16 . "<<endl;
	}else{
		cerr<<"Error: The type of external objekt input type is "<<
			typeExtObjElement.getType()<<" but should be 16 ."<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt = new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! typeExtObjElement.isCompatible( *domainInt ) ){
	
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
	if ( typeExtObjElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1 = new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( typeExtObjElement.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 1 elements."<<endl;
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
	if ( typeExtObjElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 2 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 2 elements."<<endl;
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
	if ( typeExtObjElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;


	//check compatible for vector domain with four elements
	cout<<"vecDomains1El4 = (naturalNumberB( 24 ), naturalNumberB( 16 ) , naturalNumberB( 8 ), naturalNumberB( 8 ) ) "<<endl;
	vector<cDomainSingle*> vecDomains1El4( 4 );
	vecDomains1El4[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains1El4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains1El4[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains1El4[ 3 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains1El4 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( typeExtObjElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 4 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 4 elements."<<endl;
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
	if ( typeExtObjElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 4 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 4 elements."<<endl;
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
	if ( typeExtObjElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 4 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 4 elements."<<endl;
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
	if ( typeExtObjElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 4 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 4 elements."<<endl;
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
	if ( typeExtObjElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 4 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 4 elements."<<endl;
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
	if ( typeExtObjElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 4 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 4 elements."<<endl;
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
	if ( typeExtObjElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 4 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 4 elements."<<endl;
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
	if ( typeExtObjElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 5 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 5 elements."<<endl;
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
	if ( ! typeExtObjElement.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not  compatible to the vector domain with 3 elements. "<<endl;
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
	if ( ! typeExtObjElement.isCompatible( *vectorDomain ) ){
	
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

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the global standard domain for the cTypeExtObjectInput"<<endl;
	//standard domain: vectorOpenEnd( 1, naturalNumberB(8) )
	//test the getStandardDomain() method of the property
	cDomain *standardDomain = typeExtObjElement.getStandardDomain();
	
	if ( standardDomain == NULL ){
	
		cerr<<"Error: The standard domain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	}else if ( standardDomain->getType() == "DomainVectorOpenEnd" ){
	
		//check the isCompatible() methode for vectordomain with 1 elements
		if ( typeExtObjElement.isCompatible( *standardDomain ) ){
		
			cout<<"The type is correctly compatible to the standard domain. "<<endl;
		}else{
			cerr<<"Error: The type is compatible to the standard domain."<<endl;
			iReturn++;
		}
		
		cout<<"The standard domain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *standardDomainVector = (cDomainVector*)standardDomain;

		unsignedIntFib uiStandardDomainVectorElements = 1;
		
		if ( standardDomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
		
			cout<<"The standard domain vector has correctly "<<
				uiStandardDomainVectorElements<<" element. "<<endl;
				
			//test domain of first vector element
			cDomain * pDomainElement1 = standardDomainVector->getElementDomain( 1 );
			if ( pDomainElement1 == NULL ){
			
				cerr<<"Error: The first element of the standard domain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			}else if ( pDomainElement1->getType() == "DomainIntegerBit" ){
			
				cout<<"The first element of the standard domain is correctly an "<<
					pDomainElement1->getType()<<" domain. "<<endl;
				
				cDomainIntegerBasis * pDomainIntegerBit = (cDomainIntegerBasis*)pDomainElement1;
				
				const longFib ulMinimum = -128L;
				const longFib ulMaximum = 127L;
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

	cout<<"cTypeExtObjectInput typeExtObjElement( 0 );"<<endl;
	cTypeExtObjectInput typeExtObjElement( 0 );

	cout<<"cTypeExtObjectInput *typeExtObjElementClone1 = typeExtObjElement.clone();"<<endl;
	cTypeExtObjectInput *typeExtObjElementClone1 = typeExtObjElement.clone();


	cout<<endl<<"checking the clone:"<<endl;
	//check the getNumberOfInputComments() methode from cTypeExtObjectInput
	if ( typeExtObjElement.getType() == (unsignedIntFib)(16) ){
	
		cout<<"The type of external objekt input type is correctly 16 . "<<endl;
	}else{
		cerr<<"Error: The type of external objekt input type is "<<
			typeExtObjElement.getType()<<" but should be 16 ."<<endl;
		iReturn++;
	}
	delete typeExtObjElementClone1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the clone() method"<<endl;

	cout<<"cTypeExtObjectInput typeExtObjElement152( 152 );"<<endl;
	cTypeExtObjectInput typeExtObjElement152( 152 );

	cout<<"cTypeExtObjectInput * typeExtObjElement152Clone1 = typeExtObjElement152.clone();"<<endl;
	cTypeExtObjectInput * typeExtObjElement152Clone1 = typeExtObjElement152.clone();


	cout<<endl<<"checking the clone:"<<endl;
	//check the getNumberOfInputComments() methode from cTypeExtObjectInput
	if ( typeExtObjElement152.getType() == (unsignedIntFib)(16) ){
	
		cout<<"The type of external objekt input type is correctly 16 . "<<endl;
	}else{
		cerr<<"Error: The type of external objekt input type is "<<
			typeExtObjElement152.getType()<<" but should be 16 ."<<endl;
		iReturn++;
	}
	delete typeExtObjElement152Clone1;

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

	//create cTypeExtObjectInputs to compare
	cout<<"cTypeExtObjectInput typeExtObjElement1( 0 );"<<endl;
	cTypeExtObjectInput typeExtObjElement1( 0 );
	cout<<"cTypeExtObjectInput typeExtObjElement2( 0 );"<<endl;
	cTypeExtObjectInput typeExtObjElement2( 0 );

	cout<<"cTypeExtObjectInput typeExtObjElementId1( 1 );"<<endl;
	cTypeExtObjectInput typeExtObjElementId1( 1 );

	cout<<"cTypeExtObjectInput typeExtObjElementId3( -3 );"<<endl;
	cTypeExtObjectInput typeExtObjElementId3( -3 );

	cout<<"cTypeExtObjectInput typeExtObjElementId12( 12 );"<<endl;
	cTypeExtObjectInput typeExtObjElementId12( 12 );
	
	cout<<"cTypeInVar typeInVar1N1( 1 );"<<endl;
	cTypeInVar typeInVar1N1( 1 );

	cout<<"cTypeProperty typeProperty( 1 );"<<endl;
	cTypeProperty typeProperty( 1 );

	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with typeExtObjElement1
	cTypeElement *actualType = &typeExtObjElement1;
	string szActualTypeName = "typeExtObjElement1";
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeExtObjElement1, "typeExtObjElement1" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeExtObjElement2, "typeExtObjElement2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElementId1, "typeExtObjElementId1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElementId3, "typeExtObjElementId3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElementId12, "typeExtObjElementId12" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeExtObjElement2
	actualType = &typeExtObjElement2;
	szActualTypeName = "typeExtObjElement2";
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeExtObjElement1, "typeExtObjElement1" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeExtObjElement2, "typeExtObjElement2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElementId1, "typeExtObjElementId1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElementId3, "typeExtObjElementId3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElementId12, "typeExtObjElementId12" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );
	
	//compare with typeExtObjElementId1
	actualType = &typeExtObjElementId1;
	szActualTypeName = "typeExtObjElementId1";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElement1, "typeExtObjElement1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElement2, "typeExtObjElement2" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeExtObjElementId1, "typeExtObjElementId1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElementId3, "typeExtObjElementId3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElementId12, "typeExtObjElementId12" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeExtObjElementId3
	actualType = &typeExtObjElementId3;
	szActualTypeName = "typeExtObjElementId3";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElement1, "typeExtObjElement1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElement2, "typeExtObjElement2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElementId1, "typeExtObjElementId1" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeExtObjElementId3, "typeExtObjElementId3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElementId12, "typeExtObjElementId12" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeExtObjElementId12
	actualType = &typeExtObjElementId12;
	szActualTypeName = "typeExtObjElementId12";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElement1, "typeExtObjElement1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElement2, "typeExtObjElement2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElementId1, "typeExtObjElementId1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElementId3, "typeExtObjElementId3" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeExtObjElementId12, "typeExtObjElementId12" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );
	
	//compare with typeInVar1N1
	actualType = &typeInVar1N1;
	szActualTypeName = "typeInVar1N1";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElement1, "typeExtObjElement1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElement2, "typeExtObjElement2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElementId1, "typeExtObjElementId1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElementId3, "typeExtObjElementId3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElementId12, "typeExtObjElementId12" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeProperty
	actualType = &typeProperty;
	szActualTypeName = "typeProperty";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElement1, "typeExtObjElement1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElement2, "typeExtObjElement2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElementId1, "typeExtObjElementId1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElementId3, "typeExtObjElementId3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtObjElementId12, "typeExtObjElementId12" );
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
	cout<<"cTypeExtObjectInput typeExtObjElement1( 0 );"<<endl;
	cTypeExtObjectInput typeExtObjElement1( 0 );
	
	cout<<"cTypeExtObjectInput typeExtObjElement2( 0 );"<<endl;
	cTypeExtObjectInput typeExtObjElement2( 0 );

	cout<<"cTypeExtObjectInput typeExtObjElementId1( 1 );"<<endl;
	cTypeExtObjectInput typeExtObjElementId1( 1 );

	cout<<"cTypeExtObjectInput typeExtObjElementId3( 3 );"<<endl;
	cTypeExtObjectInput typeExtObjElementId3( 3 );

	cout<<"cTypeExtObjectInput typeExtObjElementId12( 12 );"<<endl;
	cTypeExtObjectInput typeExtObjElementId12( 12 );

	cout<<"cTypeInVar typeInVar1( 1 );"<<endl;
	cTypeInVar typeInVar1( 1 );

	cout<<"cTypeProperty typeProperty( 1 );"<<endl;
	cTypeProperty typeProperty( 1 );

	cout<<"cTypeDimension typeDimension1D3( 3 );"<<endl;
	cTypeDimension typeDimension1D3( 3 );


	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	if ( typeExtObjElement1.equalElementType( typeExtObjElement1 ) ){
	
		cout<<"The typeExtObjElement1 is of the same type as typeExtObjElement1. "<<endl;
	}else{
		cerr<<"Error: The typeExtObjElement1 is not of the same type as typeExtObjElement1."<<endl;
		iReturn++;
	}
	if ( typeExtObjElement1.equalElementType( typeExtObjElement2 ) ){
	
		cout<<"The typeExtObjElement1 is of the same type as typeExtObjElement2. "<<endl;
	}else{
		cerr<<"Error: The typeExtObjElement1 is not of the same type as typeExtObjElement2."<<endl;
		iReturn++;
	}
	if ( ! typeExtObjElement1.equalElementType( typeExtObjElementId1 ) ){
	
		cout<<"The typeExtObjElement1 is not of the same type as typeExtObjElementId1. "<<endl;
	}else{
		cerr<<"Error: The typeExtObjElement1 is of the same type as typeExtObjElementId1."<<endl;
		iReturn++;
	}
	if ( ! typeExtObjElement1.equalElementType( typeExtObjElementId3 ) ){
	
		cout<<"The typeExtObjElement1 is not of the same type as typeExtObjElementId3. "<<endl;
	}else{
		cerr<<"Error: The typeExtObjElement1 is of the same type as typeExtObjElementId3."<<endl;
		iReturn++;
	}
	if ( ! typeExtObjElement1.equalElementType( typeExtObjElementId12 ) ){
	
		cout<<"The typeExtObjElement1 is not of the same type as typeExtObjElementId12. "<<endl;
	}else{
		cerr<<"Error: The typeExtObjElement1 is of the same type as typeExtObjElementId12."<<endl;
		iReturn++;
	}
	if ( ! typeExtObjElement1.equalElementType( typeInVar1 ) ){
	
		cout<<"The typeExtObjElement1 is not of the same type as typeInVar1. "<<endl;
	}else{
		cerr<<"Error: The typeExtObjElement1 is of the same type as typeInVar1."<<endl;
		iReturn++;
	}
	if ( ! typeExtObjElement1.equalElementType( typeProperty ) ){
	
		cout<<"The typeExtObjElement1 is not of the same type as typeProperty. "<<endl;
	}else{
		cerr<<"Error: The typeExtObjElement1 is of the same type as typeProperty."<<endl;
		iReturn++;
	}
	if ( ! typeExtObjElement1.equalElementType( typeDimension1D3 ) ){
	
		cout<<"The typeExtObjElement1 is not of the same type as typeDimension1D3. "<<endl;
	}else{
		cerr<<"Error: The typeExtObjElement1 is of the same type as typeDimension1D3."<<endl;
		iReturn++;
	}


	if ( ! typeExtObjElementId3.equalElementType( typeExtObjElement1 ) ){
	
		cout<<"The typeExtObjElementId3 is not of the same type as typeExtObjElement1. "<<endl;
	}else{
		cerr<<"Error: The typeExtObjElementId3 is of the same type as typeExtObjElement1."<<endl;
		iReturn++;
	}
	if ( ! typeExtObjElementId3.equalElementType( typeExtObjElement2 ) ){
	
		cout<<"The typeExtObjElementId3 is not of the same type as typeExtObjElement2. "<<endl;
	}else{
		cerr<<"Error: The typeExtObjElementId3 is of the same type as typeExtObjElement2."<<endl;
		iReturn++;
	}
	if ( ! typeExtObjElementId3.equalElementType( typeExtObjElementId1 ) ){
	
		cout<<"The typeExtObjElementId3 is not of the same type as typeExtObjElementId1. "<<endl;
	}else{
		cerr<<"Error: The typeExtObjElementId3 is of the same type as typeExtObjElementId1."<<endl;
		iReturn++;
	}
	if ( typeExtObjElementId3.equalElementType( typeExtObjElementId3 ) ){
	
		cout<<"The typeExtObjElementId3 is of the same type as typeExtObjElementId3. "<<endl;
	}else{
		cerr<<"Error: The typeExtObjElementId3 is not of the same type as typeExtObjElementId3."<<endl;
		iReturn++;
	}
	if ( ! typeExtObjElementId3.equalElementType( typeExtObjElementId12 ) ){
	
		cout<<"The typeExtObjElementId3 is not of the same type as typeExtObjElementId12. "<<endl;
	}else{
		cerr<<"Error: The typeExtObjElementId3 is of the same type as typeExtObjElementId12."<<endl;
		iReturn++;
	}
	if ( ! typeExtObjElementId3.equalElementType( typeInVar1 ) ){
	
		cout<<"The typeExtObjElementId3 is not of the same type as typeInVar1. "<<endl;
	}else{
		cerr<<"Error: The typeExtObjElementId3 is of the same type as typeInVar1."<<endl;
		iReturn++;
	}
	if ( ! typeExtObjElementId3.equalElementType( typeProperty ) ){
	
		cout<<"The typeExtObjElementId3 is not of the same type as typeProperty. "<<endl;
	}else{
		cerr<<"Error: The typeExtObjElementId3 is of the same type as typeProperty."<<endl;
		iReturn++;
	}
	if ( ! typeExtObjElementId3.equalElementType( typeDimension1D3 ) ){
	
		cout<<"The typeExtObjElementId3 is not of the same type as typeDimension1D3. "<<endl;
	}else{
		cerr<<"Error: The typeExtObjElementId3 is of the same type as typeDimension1D3."<<endl;
		iReturn++;
	}
	
	
	return iReturn;
}



/**
 * This method tests a in the xml -format stored cDomainVector with
 * cDomainNaturalNumberBit domains.
 *
 * @param szFilename the name of the file wher the cDomainNaturalNumberBit is stored
 * @param lIdentifier the number of the domain for the type
 * @param uiBits a vector with the bits the cDomainNaturalNumberBit
 * 	domains have
 * @param scalingfactor a vector with the scalingfactors for the
 * 	cDomainNaturalNumberBit domains have
 * @return the number of errors occured in the test
 */
int testXmlType( const string szFilename, const long lIdentifier,
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

		if ( szElementName == "externObjectInput" ){
			cout<<"The root element is correctly named \"externObjectInput\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"externObjectInput\"."<<endl;
			iReturn++;
		}
		
		int iNumberOfInVarLoaded = 0;
		const char * pcAttributNumber = pXmlElement->Attribute( "identifier",
			&iNumberOfInVarLoaded );
		
		if ( pcAttributNumber == NULL ){
			cerr<<"Error: The type has no attribute \"identifier\"."<<endl;
			iReturn++;
		}else if ( iNumberOfInVarLoaded == (int)lIdentifier ) {
			cout<<"The identifier is correctly \""<<lIdentifier <<"\". "<<endl;
		}else{
			cerr<<"Error: The identifier is \""<<
				iNumberOfInVarLoaded <<"\", but should be \""<<
				lIdentifier <<"\"."<<endl;
			iReturn++;
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
	
		char szScalingfactorBuffer[168];
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple external objekt input type"<<endl;

	cout<<"cTypeExtObjectInput typeExtObjElement1( 0 );"<<endl;
	cTypeExtObjectInput typeExtObjElement1( 0 );

	char szFileNameBuffer[168];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeExtObjElement1.xml" );
	ofstream * fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeExtObjElement1.storeXml( *fileXml );"<<endl;
	bool bStoreSuccesfull = typeExtObjElement1.storeXml( *fileXml );
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple external objekt input type with identifier 3"<<endl;

	cout<<"cTypeExtObjectInput typeExtObjElementId3( 3 );"<<endl;
	cTypeExtObjectInput typeExtObjElementId3( 3 );

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeExtObjElementId3.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeExtObjElementId3.storeXml( *fileXml );"<<endl;
	bStoreSuccesfull = typeExtObjElementId3.storeXml( *fileXml );
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple external objekt input type with identifier -5"<<endl;

	cout<<"cTypeExtObjectInput typeExtObjElementIdm5( -5 );"<<endl;
	cTypeExtObjectInput typeExtObjElementIdm5( -5 );

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeExtObjElementIdm5.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeExtObjElementIdm5.storeXml( *fileXml );"<<endl;
	bStoreSuccesfull = typeExtObjElementIdm5.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, -5, false,
		0, 0.0 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a 5'th external objekt input type with a domain"<<endl;

	cout<<"cDomainNaturalNumberBit domainNaturalNumberB4( 4 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberB4( 4 );
	unsigned int uiBits = 4;
	double dScalingfactor = 1.0;

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeExtObjElement1Dom.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeExtObjElement1.storeXml( *fileXml, &domainNaturalNumberB4 );"<<endl;
	bStoreSuccesfull = typeExtObjElement1.storeXml( *fileXml, &domainNaturalNumberB4 );
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple external objekt input type for external objekt input"<<endl;
	
	cout<<"cTypeExtObjectInput typeExtObjElement1( 0 );"<<endl;
	cTypeExtObjectInput typeExtObjElement1( 0 );

	//test get compressed size
	unsigned int uiCompressedSize = 8;
	if ( (unsigned int)(typeExtObjElement1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeExtObjElement1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[168];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeExtObjElement1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	bool bStoreSuccesfull = typeExtObjElement1.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cTypeExtObjectInput1[] = { (char)0xE0,
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeExtObjectInput1, 2 );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple external objekt input type for identifier 1"<<endl;
	
	cout<<"cTypeExtObjectInput typeExtObjElementId1( 1 );"<<endl;
	cTypeExtObjectInput typeExtObjElementId1( 1 );

	//test get compressed size
	uiCompressedSize = 16;
	if ( (unsigned int)(typeExtObjElementId1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeExtObjElementId1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeExtObjElementId1.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = typeExtObjElementId1.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cTypeExtObjectInputNr1[] = { (char)0xE2,
		(char)0x01, (char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeExtObjectInputNr1, 3 );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple external objekt input type for identifier 127"<<endl;
	
	cout<<"cTypeExtObjectInput typeExtObjElementId127( 127 );"<<endl;
	cTypeExtObjectInput typeExtObjElementId127( 127 );

	//test get compressed size
	uiCompressedSize = 16;
	if ( (unsigned int)(typeExtObjElementId127.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeExtObjElementId127.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeExtObjElementId127.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = typeExtObjElementId127.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cTypeExtObjectInput255[] = { (char)0xE2,
		(char)0x7F, (char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeExtObjectInput255, 3 );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple external objekt input type for identifier -128"<<endl;
	
	cout<<"cTypeExtObjectInput typeExtObjElementIdm128( -128 );"<<endl;
	cTypeExtObjectInput typeExtObjElementIdm128( -128 );

	//test get compressed size
	uiCompressedSize = 16;
	if ( (unsigned int)(typeExtObjElementIdm128.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeExtObjElementIdm128.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeExtObjElementIdm128.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = typeExtObjElementIdm128.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cTypeExtObjectInputIdm128[] = { (char)0xE2,
		(char)0x80, (char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeExtObjectInputIdm128, 3 );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple external objekt input type for identifier 128"<<endl;
	
	cout<<"cTypeExtObjectInput typeExtObjElementId128( 128 );"<<endl;
	cTypeExtObjectInput typeExtObjElementId128( 128 );

	//test get compressed size
	uiCompressedSize = 72;
	if ( (unsigned int)(typeExtObjElementId128.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeExtObjElementId128.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeExtObjElementId128.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = typeExtObjElementId128.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cTypeExtObjectInputId128[] = { (char)0xE4,
		(char)0x80, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeExtObjectInputId128, 10 );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple external objekt input type for identifier -129"<<endl;
	
	cout<<"cTypeExtObjectInput typeExtObjElementIdm129( -129 );"<<endl;
	cTypeExtObjectInput typeExtObjElementIdm129( -129 );

	//test get compressed size
	uiCompressedSize = 72;
	if ( (unsigned int)(typeExtObjElementIdm129.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeExtObjElementIdm129.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeExtObjElementIdm129.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = typeExtObjElementIdm129.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cTypeExtObjectInputIdm129[] = { (char)0xE4,
		(char)0x7F, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeExtObjectInputIdm129, 10 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a external objekt input type with 5 restbits"<<endl;

	//test get compressed size
	uiCompressedSize = 8;
	if ( (unsigned int)(typeExtObjElement1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeExtObjElement1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeExtObjElement1R5.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x05;
	cNumberOfRestBit = 5 ;
	bStoreSuccesfull = typeExtObjElement1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	unsigned char ucRestBit = cRestBit;
	if ( ( ucRestBit == (unsigned char)((char)0x1C) ) && ( cNumberOfRestBit == 5 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x1C and number of restbit should be 5. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeExtObjectInput5[] = { (char)0x05, (char)0x1C };
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeExtObjectInput5, 2 );

	return iReturn;
}


/**
 * This method getExtObjectIdentifier() method of the class.
 *
 * methods tested:
 * 	- unsignedIntFib getExtObjectIdentifier() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testIdentifier( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing getExtObjectIdentifier() method"<<endl;
	
	for ( unsigned int iteration = 0; iteration < 128; iteration++ ){
		
		const long  lIdentifier = (long)(rand() % ( 1 + rand() % (
			1 + rand() % (256L * 256L) ) )) - 256L * 128L;
		
		cout<<"cTypeExtObjectInput typeExtObjElement( "<<lIdentifier<<" );"<<endl;
		cTypeExtObjectInput typeExtObjElement( lIdentifier );
		
			//check the getNumberOfInputComments() methode from cTypeExtObjectInput
		if ( typeExtObjElement.getExtObjectIdentifier() == lIdentifier ){
		
			cout<<"The type of external objekt input identifier is correctly "<<
				typeExtObjElement.getExtObjectIdentifier()<<" . "<<endl;
		}else{
			cerr<<"Error: The type external objekt input identifier is "<<
				typeExtObjElement.getType()<<" but should be "<<
				lIdentifier<<" ."<<endl;
			iReturn++;
		}
	}

	return iReturn;
}








