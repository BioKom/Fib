/**
 * @file tDomainVectorOpenEnd
 * file name: tDomainVectorOpenEnd.cpp
 * @author Betti Oesterholz
 * @date 03.12.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cDomainVectorOpenEnd.
 *
 * Copyright (C) @c GPL3 2009 Betti Oesterholz
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
 * This file contains the test for the class cDomainVectorOpenEnd,
 * which represents the type for variable vector domains.
 *
 *
 *
 *  What's tested of class cDomainVectorOpenEnd:
 * 	- cDomainVectorOpenEnd( const vector<cDomainSingle*> & vElementDomains)
 * 	- string getType() const
 * 	- cDomain *clone() const
 * 	- bool equal( const cDomain &domain ) const
 * 	- bool operator==( const cDomain &domain ) const
 * 	- unsignedIntFib getNumberOfElements( ) const
 * 	- cDomainSingle * getElementDomain( unsignedIntFib iNumberOfElement )
 * 	- bool isElement( const cFibVector &fibVector ) const
 * 	- cFibVector * round( cFibVector &fibVector ) const
 * 	- bool storeXml( ostream & ostream ) const
 * 	- unsignedIntFib getCompressedSize() const
 * 	- bool store( ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const
 */
/*
History:
03.12.2011  Oesterholz  created
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
03.09.2013  Oesterholz  reading scaling factor adapted
*/

//TODO check isCompatible() for more domains + comparrisson


#include "version.h"

#include "cRoot.h"
#include "cDomainVectorOpenEnd.h"
#include "cDomainVector.h"
#include "cDomainNaturalNumberBit.h"
#include "cVectorPosition.h"
#include "cTypeDimension.h"

#include "tinyxml.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <iomanip>
#include <vector>

#include "tCompareBits.inc"

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif

using namespace fib;
using namespace std;


int testConstructor( unsigned long &ulTestphase );
int testEqual( unsigned long &ulTestphase );
int testClone( unsigned long &ulTestphase );
int testIsElement( unsigned long &ulTestphase );
int testRound( unsigned long &ulTestphase );
int testStoreXml( unsigned long &ulTestphase );
int testStore( unsigned long &ulTestphase );

int main(int argc,char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cDomainVectorOpenEnd methods"<<endl;
	cout<<      "============================================="<<endl;

	iReturn += testConstructor( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testClone( ulTestphase );
	iReturn += testIsElement( ulTestphase );
	iReturn += testRound( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );


	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}



/**
 * This method tests the constructor and the getType(),
 * getNumberOfElements(), getElementDomain() methods of the cDomainVectorOpenEnd 
 * class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testConstructor( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a simple vector domain with 0 elements"<<endl;

	cout<<"vector<cDomainSingle*> vecDomains0( 0 );"<<endl;
	vector<cDomainSingle*> vecDomains0( 0 );
	cout<<"cDomainVectorOpenEnd vectorDomain0( vecDomains0 );"<<endl;
	cDomainVectorOpenEnd vectorDomain0( vecDomains0 );

	//test the getType() method
	if ( vectorDomain0.getType()=="DomainVectorOpenEnd" ){
	
		cout<<"The type of vectorDomain0 is correctly \"DomainVectorOpenEnd\"."<<endl;
	}else{
		cerr<<"Error: The type of vectorDomain0 is "<<vectorDomain0.getType() <<
			" and not \"DomainVectorOpenEnd\""<<endl;
		iReturn++;
	}
	//test the getNumberOfElements() method
	if ( vectorDomain0.getNumberOfElements()==0 ){
	
		cout<<"The number of elements of vectorDomain0 is correctly 0."<<endl;
	}else{
		cerr<<"Error: The number of elements of vectorDomain0 is "<<
			vectorDomain0.getNumberOfElements() <<" and not 0 ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a simple vector domain with 3 elements"<<endl;

	cout<<"vector<cDomainSingle*> vecDomains3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomains3( 3 );
	cout<<"vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 8 );"<<endl;
	vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 8 );
	cout<<"vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 16 );"<<endl;
	vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 16 );
	cout<<"vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 5 );
	cout<<"cDomainVectorOpenEnd vectorDomain3( vecDomains3 );"<<endl;
	cDomainVectorOpenEnd vectorDomain3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	//test the getType() method
	if ( vectorDomain3.getType()=="DomainVectorOpenEnd" ){
	
		cout<<"The type of vectorDomain3 is correctly \"DomainVectorOpenEnd\"."<<endl;
	}else{
		cerr<<"Error: The type of vectorDomain3 is "<<vectorDomain3.getType() <<
			" and not \"DomainVectorOpenEnd\""<<endl;
		iReturn++;
	}

	//test the getNumberOfElements() method
	if ( vectorDomain3.getNumberOfElements()==3 ){
	
		cout<<"The number of elements of vectorDomain3 is correctly 3."<<endl;
		
		//check domains of vector domain elements
		
		cDomainNaturalNumberBit domainNaturalNumberBit8=cDomainNaturalNumberBit( 8 );
		if ( vectorDomain3.getElementDomain( 1 )==NULL ){
			cerr<<"Error: The first element domain is NULL."<<endl;
			iReturn++;
		}else if ( (*(vectorDomain3.getElementDomain( 1 )))==domainNaturalNumberBit8 ){
		
			cout<<"The first element domain is correctly an cDomainNaturalNumberBit domain with 8 bits."<<endl;
		}else{
			cerr<<"Error: The first element domain is not an cDomainNaturalNumberBit domain with 8 bits."<<endl;
			iReturn++;
		}

		cDomainNaturalNumberBit domainNaturalNumberBit16=cDomainNaturalNumberBit( 16 );
		if ( vectorDomain3.getElementDomain( 2 )==NULL ){
			cerr<<"Error: The secound element domain is NULL."<<endl;
			iReturn++;
		}else if ( (*(vectorDomain3.getElementDomain( 2 )))==domainNaturalNumberBit16 ){
		
			cout<<"The secound element domain is correctly an cDomainNaturalNumberBit domain with 16 bits."<<endl;
		}else{
			cerr<<"Error: The secound element domain is not an cDomainNaturalNumberBit domain with 16 bits."<<endl;
			iReturn++;
		}

		cDomainNaturalNumberBit domainNaturalNumberBit5=cDomainNaturalNumberBit( 5 );
		
		if ( vectorDomain3.getElementDomain( 3 )==NULL ){
			cerr<<"Error: The third element domain is NULL."<<endl;
			iReturn++;
		}else if ( (*(vectorDomain3.getElementDomain( 3 )))==domainNaturalNumberBit5 ){
		
			cout<<"The third element domain is correctly an cDomainNaturalNumberBit domain with 5 bits."<<endl;
		}else{
			cerr<<"Error: The third element domain is not an cDomainNaturalNumberBit domain with 5 bits."<<endl;
			iReturn++;
		}

		if ( vectorDomain3.getElementDomain( 3 )!=NULL ){
			if ( !((*(vectorDomain3.getElementDomain( 3 )))==domainNaturalNumberBit16) ){
			
				cout<<"The third element domain is correctly not an cDomainNaturalNumberBit domain with 16 bits."<<endl;
			}else{
				cerr<<"Error: The third element domain is an cDomainNaturalNumberBit domain with 16 bits."<<endl;
				iReturn++;
			}
		}


		//check bounderies
		if ( vectorDomain3.getElementDomain( 0 )==NULL ){
			cerr<<"Ther is no 0'th element domain."<<endl;
		}

		if ( vectorDomain3.getElementDomain( 4 )==NULL ){
			cerr<<"Ther is no 4'th element domain."<<endl;
		}


	}else{
		cerr<<"Error: The number of elements of vectorDomain3 is "<<
			vectorDomain3.getNumberOfElements() <<" and not 3 ."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a simple vector domain with 5 elements"<<endl;

	cout<<"vector<cDomainSingle*> vecDomains5( 5 );"<<endl;
	vector<cDomainSingle*> vecDomains5( 5 );
	cout<<"vecDomains5[ 0 ]=new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains5[ 0 ]=new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains5[ 1 ]=new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains5[ 1 ]=new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomains5[ 2 ]=new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains5[ 2 ]=new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomains5[ 3 ]=new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomains5[ 3 ]=new cDomainNaturalNumberBit( 4 );
	cout<<"vecDomains5[ 4 ]=new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomains5[ 4 ]=new cDomainNaturalNumberBit( 5 );
	cout<<"cDomainVectorOpenEnd vectorDomain5( vecDomains5 );"<<endl;
	cDomainVectorOpenEnd vectorDomain5( vecDomains5 );
	delete vecDomains5[ 0 ];
	delete vecDomains5[ 1 ];
	delete vecDomains5[ 2 ];
	delete vecDomains5[ 3 ];
	delete vecDomains5[ 4 ];

	//test the getType() method
	if ( vectorDomain5.getType()=="DomainVectorOpenEnd" ){
	
		cout<<"The type of vectorDomain5 is correctly \"DomainVectorOpenEnd\"."<<endl;
	}else{
		cerr<<"Error: The type of vectorDomain5 is "<<vectorDomain5.getType() <<
			" and not \"DomainVectorOpenEnd\""<<endl;
		iReturn++;
	}

	//test the getNumberOfElements() method
	if ( vectorDomain5.getNumberOfElements()==5 ){
	
		cout<<"The number of elements of vectorDomain5 is correctly 5."<<endl;
		
		//check domains of vector domain elements
		
		cDomainNaturalNumberBit domainNaturalNumberBit1=cDomainNaturalNumberBit( 1 );
		if ( vectorDomain5.getElementDomain( 1 )==NULL ){
			cerr<<"Error: The first element domain is NULL."<<endl;
			iReturn++;
		}else if ( (*(vectorDomain5.getElementDomain( 1 )))==domainNaturalNumberBit1 ){
		
			cout<<"The first element domain is correctly an cDomainNaturalNumberBit domain with 1 bits."<<endl;
		}else{
			cerr<<"Error: The first element domain is not an cDomainNaturalNumberBit domain with 1 bits."<<endl;
			iReturn++;
		}

		cDomainNaturalNumberBit domainNaturalNumberBit2=cDomainNaturalNumberBit( 2 );
		if ( vectorDomain5.getElementDomain( 2 )==NULL ){
			cerr<<"Error: The secound element domain is NULL."<<endl;
			iReturn++;
		}else if ( (*(vectorDomain5.getElementDomain( 2 )))==domainNaturalNumberBit2 ){
		
			cout<<"The secound element domain is correctly an cDomainNaturalNumberBit domain with 2 bits."<<endl;
		}else{
			cerr<<"Error: The secound element domain is not an cDomainNaturalNumberBit domain with 2 bits."<<endl;
			iReturn++;
		}

		cDomainNaturalNumberBit domainNaturalNumberBit3=cDomainNaturalNumberBit( 3 );
		
		if ( vectorDomain5.getElementDomain( 3 )==NULL ){
			cerr<<"Error: The third element domain is NULL."<<endl;
			iReturn++;
		}else if ( (*(vectorDomain5.getElementDomain( 3 )))==domainNaturalNumberBit3 ){
		
			cout<<"The third element domain is correctly an cDomainNaturalNumberBit domain with 3 bits."<<endl;
		}else{
			cerr<<"Error: The third element domain is not an cDomainNaturalNumberBit domain with 3 bits."<<endl;
			iReturn++;
		}

		cDomainNaturalNumberBit domainNaturalNumberBit4=cDomainNaturalNumberBit( 4 );
		
		if ( vectorDomain5.getElementDomain( 4 )==NULL ){
			cerr<<"Error: The 4'th element domain is NULL."<<endl;
			iReturn++;
		}else if ( (*(vectorDomain5.getElementDomain( 4 )))==domainNaturalNumberBit4 ){
		
			cout<<"The  4'th element domain is correctly an cDomainNaturalNumberBit domain with 4 bits."<<endl;
		}else{
			cerr<<"Error: The  4'th element domain is not an cDomainNaturalNumberBit domain with 4 bits."<<endl;
			iReturn++;
		}

		cDomainNaturalNumberBit domainNaturalNumberBit5=cDomainNaturalNumberBit( 5 );
		
		if ( vectorDomain5.getElementDomain( 5 )==NULL ){
			cerr<<"Error: The 5'th element domain is NULL."<<endl;
			iReturn++;
		}else if ( (*(vectorDomain5.getElementDomain( 5 )))==domainNaturalNumberBit5 ){
		
			cout<<"The 5'th element domain is correctly an cDomainNaturalNumberBit domain with 5 bits."<<endl;
		}else{
			cerr<<"Error: The 5'th element domain is not an cDomainNaturalNumberBit domain with 5 bits."<<endl;
			iReturn++;
		}

		//check bounderies
		if ( vectorDomain5.getElementDomain( 0 )==NULL ){
			cerr<<"Ther is no 0'th element domain."<<endl;
		}

		if ( vectorDomain5.getElementDomain( 6 )==NULL ){
			cerr<<"Ther is no 6'th element domain."<<endl;
		}


	}else{
		cerr<<"Error: The number of elements of vectorDomain5 is "<<
			vectorDomain5.getNumberOfElements() <<" and not 5 ."<<endl;
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests the equal() method and the operator== of two given
 * cDomain objects which are equal.
 *
 * @param domain1 the first domain to compare
 * @param szNameDomain1 the name of the first domain to compare
 * @param domain2 the secound domain to compare to
 * @param szNameDomain2 the name of the secound domain to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualDomains( const cDomain &domain1, const string &szNameDomain1,
	const cDomain &domain2, const string &szNameDomain2 ){
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	if ( domain1.equal( domain2 ) ){
	
		cout<<"The "<<szNameDomain1<<" is equal to "<<szNameDomain2<<"."<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomain1<<" is not equal to "<<
			szNameDomain2<<"."<<endl;
		iReturn++;
	}
	if ( domain1==domain2 ){
	
		cout<<"The "<<szNameDomain1<<" is equal (operator==) to "<<
			szNameDomain2<<"."<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomain1<<" is not equal (operator==) to "<<
			szNameDomain2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the equal() method and the operator== of two given
 * cDomain objects which are not equal.
 *
 * @param domain1 the first domain to compare
 * @param szNameDomain1 the name of the first domain to compare
 * @param domain2 the secound domain to compare to
 * @param szNameDomain2 the name of the secound domain to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoNotEqualDomains( const cDomain &domain1, const string &szNameDomain1,
	const cDomain &domain2, const string &szNameDomain2 ){
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	if ( ! domain1.equal( domain2 ) ){
	
		cout<<"The "<<szNameDomain1<<" is not equal to "<<szNameDomain2<<"."<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomain1<<" is equal to "<<
			szNameDomain2<<"."<<endl;
		iReturn++;
	}
	if ( ! (domain1==domain2) ){
	
		cout<<"The "<<szNameDomain1<<" is not equal (operator==) to "<<
			szNameDomain2<<"."<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomain1<<" is equal (operator==) to "<<
			szNameDomain2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the equal and operator== methods of the cDomainVectorOpenEnd 
 * class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testEqual( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the equal method and the operator== "<<endl;


	cout<<"vector<cDomainSingle*> vecDomains1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomains1( 1 );
	cout<<"vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 8 );"<<endl;
	vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 8 );
	cout<<"cDomainVectorOpenEnd vectorDomain1E1( vecDomains1 );"<<endl;
	cDomainVectorOpenEnd vectorDomain1E1( vecDomains1 );
	delete vecDomains1[ 0 ];

	cout<<"vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 8 );"<<endl;
	vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 8 );
	cout<<"cDomainVectorOpenEnd vectorDomain2E1( vecDomains1 );"<<endl;
	cDomainVectorOpenEnd vectorDomain2E1( vecDomains1 );
	delete vecDomains1[ 0 ];

	cout<<"vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 13, 0.05  );"<<endl;
	vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 13, 0.05 );
	cout<<"cDomainVectorOpenEnd vectorDomain3E1( vecDomains1 );"<<endl;
	cDomainVectorOpenEnd vectorDomain3E1( vecDomains1 );
	delete vecDomains1[ 0 ];

	cout<<"vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 13, 0.05  );"<<endl;
	vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 13, 0.05 );
	cout<<"cDomainVectorOpenEnd vectorDomain4E1( vecDomains1 );"<<endl;
	cDomainVectorOpenEnd vectorDomain4E1( vecDomains1 );
	delete vecDomains1[ 0 ];

	cout<<"vector<cDomainSingle*> vecDomains3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomains3( 3 );
	cout<<"vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 8 );"<<endl;
	vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 8 );
	cout<<"vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 16 );"<<endl;
	vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 16 );
	cout<<"vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 5 );
	cout<<"cDomainVectorOpenEnd vectorDomain1E3( vecDomains3 );"<<endl;
	cDomainVectorOpenEnd vectorDomain1E3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	cout<<"vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 8 );"<<endl;
	vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 8 );
	cout<<"vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 16 );"<<endl;
	vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 16 );
	cout<<"vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 5 );
	cout<<"cDomainVectorOpenEnd vectorDomain2E3( vecDomains3 );"<<endl;
	cDomainVectorOpenEnd vectorDomain2E3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	cout<<"vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 8 );"<<endl;
	vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 8 );
	cout<<"vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 16 );"<<endl;
	vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 16 );
	cout<<"vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 6 );"<<endl;
	vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 6 );
	cout<<"cDomainVectorOpenEnd vectorDomain3E3( vecDomains3 );"<<endl;
	cDomainVectorOpenEnd vectorDomain3E3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	cout<<"vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 8 );"<<endl;
	vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 8 );
	cout<<"vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 16 );"<<endl;
	vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 16 );
	cout<<"vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 6 );"<<endl;
	vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 6 );
	cout<<"cDomainVectorOpenEnd vectorDomain4E3( vecDomains3 );"<<endl;
	cDomainVectorOpenEnd vectorDomain4E3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	cout<<"vector<cDomainSingle*> vecDomains5( 5 );"<<endl;
	vector<cDomainSingle*> vecDomains5( 5 );
	cout<<"vecDomains5[ 0 ]=new cDomainNaturalNumberBit( 8 );"<<endl;
	vecDomains5[ 0 ]=new cDomainNaturalNumberBit( 8 );
	cout<<"vecDomains5[ 1 ]=new cDomainNaturalNumberBit( 16 );"<<endl;
	vecDomains5[ 1 ]=new cDomainNaturalNumberBit( 16 );
	cout<<"vecDomains5[ 2 ]=new cDomainNaturalNumberBit( 6 );"<<endl;
	vecDomains5[ 2 ]=new cDomainNaturalNumberBit( 6 );
	cout<<"vecDomains5[ 3 ]=new cDomainNaturalNumberBit( 7 );"<<endl;
	vecDomains5[ 3 ]=new cDomainNaturalNumberBit( 7 );
	cout<<"vecDomains5[ 4 ]=new cDomainNaturalNumberBit( 13 );"<<endl;
	vecDomains5[ 4 ]=new cDomainNaturalNumberBit( 13 );
	cout<<"cDomainVectorOpenEnd vectorDomain1E5( vecDomains5 );"<<endl;
	cDomainVectorOpenEnd vectorDomain1E5( vecDomains5 );
	delete vecDomains5[ 0 ];
	delete vecDomains5[ 1 ];
	delete vecDomains5[ 2 ];
	delete vecDomains5[ 3 ];
	delete vecDomains5[ 4 ];

	//check with other domains
	cout<<"vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 8 );"<<endl;
	vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 8 );
	cout<<"vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 16 );"<<endl;
	vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 16 );
	cout<<"vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 6 );"<<endl;
	vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 6 );
	cout<<"cDomainVector vectorDomainNorm3E3( vecDomains3 );"<<endl;
	cDomainVector vectorDomainNorm3E3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	cout<<"cDomainNaturalNumberBit domainInteger2Bit5( (unsignedIntFib)(5) );"<<endl;
	cDomainNaturalNumberBit domainInteger2Bit5( (unsignedIntFib)(5) );

	//compare with vectorDomain1E1
	cDomain *actualDomain=&vectorDomain1E1;
	string szActualDomainName="vectorDomain1E1";
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E1, "vectorDomain1E1" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E1, "vectorDomain2E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E1, "vectorDomain3E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E1, "vectorDomain4E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E3, "vectorDomain1E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E3, "vectorDomain2E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E3, "vectorDomain3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E3, "vectorDomain4E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E5, "vectorDomain1E5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomainNorm3E3, "vectorDomainNorm3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	//compare with vectorDomain2E1
	actualDomain=&vectorDomain2E1;
	szActualDomainName="vectorDomain2E1";
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E1, "vectorDomain1E1" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E1, "vectorDomain2E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E1, "vectorDomain3E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E1, "vectorDomain4E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E3, "vectorDomain1E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E3, "vectorDomain2E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E3, "vectorDomain3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E3, "vectorDomain4E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E5, "vectorDomain1E5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomainNorm3E3, "vectorDomainNorm3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	//compare with vectorDomain3E1
	actualDomain=&vectorDomain3E1;
	szActualDomainName="vectorDomain3E1";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E1, "vectorDomain1E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E1, "vectorDomain2E1" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E1, "vectorDomain3E1" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E1, "vectorDomain4E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E3, "vectorDomain1E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E3, "vectorDomain2E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E3, "vectorDomain3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E3, "vectorDomain4E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E5, "vectorDomain1E5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomainNorm3E3, "vectorDomainNorm3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	//compare with vectorDomain4E1
	actualDomain=&vectorDomain4E1;
	szActualDomainName="vectorDomain4E1";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E1, "vectorDomain1E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E1, "vectorDomain2E1" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E1, "vectorDomain3E1" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E1, "vectorDomain4E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E3, "vectorDomain1E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E3, "vectorDomain2E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E3, "vectorDomain3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E3, "vectorDomain4E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E5, "vectorDomain1E5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomainNorm3E3, "vectorDomainNorm3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	//compare with vectorDomain1E3
	actualDomain=&vectorDomain1E3;
	szActualDomainName="vectorDomain1E3";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E1, "vectorDomain1E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E1, "vectorDomain2E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E1, "vectorDomain3E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E1, "vectorDomain4E1" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E3, "vectorDomain1E3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E3, "vectorDomain2E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E3, "vectorDomain3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E3, "vectorDomain4E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E5, "vectorDomain1E5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomainNorm3E3, "vectorDomainNorm3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	//compare with vectorDomain2E3
	actualDomain=&vectorDomain2E3;
	szActualDomainName="vectorDomain2E3";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E1, "vectorDomain1E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E1, "vectorDomain2E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E1, "vectorDomain3E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E1, "vectorDomain4E1" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E3, "vectorDomain1E3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E3, "vectorDomain2E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E3, "vectorDomain3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E3, "vectorDomain4E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E5, "vectorDomain1E5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomainNorm3E3, "vectorDomainNorm3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	//compare with vectorDomain3E3
	actualDomain=&vectorDomain3E3;
	szActualDomainName="vectorDomain3E3";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E1, "vectorDomain1E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E1, "vectorDomain2E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E1, "vectorDomain3E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E1, "vectorDomain4E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E3, "vectorDomain1E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E3, "vectorDomain2E3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E3, "vectorDomain3E3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E3, "vectorDomain4E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E5, "vectorDomain1E5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomainNorm3E3, "vectorDomainNorm3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	//compare with vectorDomain4E3
	actualDomain=&vectorDomain4E3;
	szActualDomainName="vectorDomain4E3";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E1, "vectorDomain1E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E1, "vectorDomain2E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E1, "vectorDomain3E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E1, "vectorDomain4E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E3, "vectorDomain1E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E3, "vectorDomain2E3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E3, "vectorDomain3E3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E3, "vectorDomain4E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E5, "vectorDomain1E5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomainNorm3E3, "vectorDomainNorm3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	//compare with vectorDomain1E5
	actualDomain=&vectorDomain1E5;
	szActualDomainName="vectorDomain1E5";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E1, "vectorDomain1E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E1, "vectorDomain2E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E1, "vectorDomain3E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E1, "vectorDomain4E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E3, "vectorDomain1E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E3, "vectorDomain2E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E3, "vectorDomain3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E3, "vectorDomain4E3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E5, "vectorDomain1E5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomainNorm3E3, "vectorDomainNorm3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	//compare with vectorDomainNorm3E3
	actualDomain=&vectorDomainNorm3E3;
	szActualDomainName="vectorDomainNorm3E3";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E1, "vectorDomain1E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E1, "vectorDomain2E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E1, "vectorDomain3E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E1, "vectorDomain4E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E3, "vectorDomain1E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E3, "vectorDomain2E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E3, "vectorDomain3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E3, "vectorDomain4E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E5, "vectorDomain1E5" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, vectorDomainNorm3E3, "vectorDomainNorm3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	//compare with domainInteger2Bit5
	actualDomain=&domainInteger2Bit5;
	szActualDomainName="domainInteger2Bit5";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E1, "vectorDomain1E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E1, "vectorDomain2E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E1, "vectorDomain3E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E1, "vectorDomain4E1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E3, "vectorDomain1E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain2E3, "vectorDomain2E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain3E3, "vectorDomain3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain4E3, "vectorDomain4E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomain1E5, "vectorDomain1E5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, vectorDomainNorm3E3, "vectorDomainNorm3E3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	return iReturn;
}



/**
 * This method tests the clone() method of the cDomainVectorOpenEnd 
 * class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testClone( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cloning a vector domain with 3 elements"<<endl;

	cout<<"vector<cDomainSingle*> vecDomains3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomains3( 3 );
	cout<<"vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVectorOpenEnd vectorDomain3( vecDomains3 );"<<endl;
	cDomainVectorOpenEnd vectorDomain3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	cout<<"cDomainVectorOpenEnd * vectorDomain3clone = vectorDomain3.clone();"<<endl;
	cDomainVectorOpenEnd * vectorDomain3clone = vectorDomain3.clone();

	iReturn+=testCompareTwoEqualDomains( vectorDomain3, "vectorDomain3", *vectorDomain3clone, "vectorDomain3clone" );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cloning a vector domain with 5 elements"<<endl;

	cout<<"vector<cDomainSingle*> vecDomains5( 5 );"<<endl;
	vector<cDomainSingle*> vecDomains5( 5 );
	cout<<"vecDomains5[ 0 ]=new cDomainNaturalNumberBit( 12 );"<<endl;
	vecDomains5[ 0 ]=new cDomainNaturalNumberBit( 12 );
	cout<<"vecDomains5[ 1 ]=new cDomainNaturalNumberBit( 16 );"<<endl;
	vecDomains5[ 1 ]=new cDomainNaturalNumberBit( 16 );
	cout<<"vecDomains5[ 2 ]=new cDomainNaturalNumberBit( 6 );"<<endl;
	vecDomains5[ 2 ]=new cDomainNaturalNumberBit( 19 );
	cout<<"vecDomains5[ 3 ]=new cDomainNaturalNumberBit( 19 );"<<endl;
	vecDomains5[ 3 ]=new cDomainNaturalNumberBit( 7 );
	cout<<"vecDomains5[ 4 ]=new cDomainNaturalNumberBit( 11 );"<<endl;
	vecDomains5[ 4 ]=new cDomainNaturalNumberBit( 11 );
	cout<<"cDomainVectorOpenEnd vectorDomain1E5( vecDomains5 );"<<endl;
	cDomainVectorOpenEnd vectorDomain5( vecDomains5 );
	delete vecDomains5[ 0 ];
	delete vecDomains5[ 1 ];
	delete vecDomains5[ 2 ];
	delete vecDomains5[ 3 ];
	delete vecDomains5[ 4 ];


	cout<<"cDomainVectorOpenEnd * vectorDomain5clone = vectorDomain5.clone();"<<endl;
	cDomainVectorOpenEnd * vectorDomain5clone = vectorDomain5.clone();

	iReturn+=testCompareTwoEqualDomains( vectorDomain5, "vectorDomain5", *vectorDomain5clone, "vectorDomain5clone" );

	iReturn+=testCompareTwoNotEqualDomains( vectorDomain3, "vectorDomain3", *vectorDomain5clone, "vectorDomain5clone" );
	iReturn+=testCompareTwoNotEqualDomains( *vectorDomain3clone, "vectorDomain3clone", *vectorDomain5clone, "vectorDomain5clone" );
	delete vectorDomain3clone;
	delete vectorDomain5clone;
	
	return iReturn;
}



/**
 * This method tests the testIsElement() method of the cDomainVectorOpenEnd 
 * class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testIsElement( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing isElement() on an vector with 1 elements"<<endl;

	cout<<endl<<"creating domains to use:"<<endl<<endl;

	cout<<"cRoot rootD1;"<<flush<<endl;
	cRoot rootD1;
	
	cout<<"cTypeDimension testTypeDimensionD1( 1 );"<<endl;
	cTypeDimension testTypeDimensionD1( 1 );
	cout<<"testTypeDimensionD1.setDimensionMapping( 1, 4 )"<<endl;
	testTypeDimensionD1.setDimensionMapping( 1, 4 );
	
	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomains1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomains1( 1 );
	cout<<"vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 4 );
	cout<<"cDomainVectorOpenEnd vectorDomainD1( vecDomains1 );"<<endl;
	cDomainVectorOpenEnd vectorDomainD1( vecDomains1 );
	delete vecDomains1[ 0 ];

	cout<<"rootD1.getDomains()->addDomain( testTypeDimensionD1, vectorDomainD1);"<<endl;
	rootD1.getDomains()->addDomain( testTypeDimensionD1, vectorDomainD1);

	//creat defined variables to set them later in the vector
	cout<<"rootD1.setNumberOfInputVariables( 4 )"<<endl;
	rootD1.setNumberOfInputVariables( 4 );
	//vectors with variables
	cFibVariable * pVariable1 = rootD1.getInputVariable( 1 );
	cFibVariable * pVariable2 = rootD1.getInputVariable( 2 );


	cout<<"vector<cDomainSingle*> vecDomains3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomains3( 3 );
	cout<<"vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVectorOpenEnd vectorDomainD3( vecDomains3 );"<<endl;
	cDomainVectorOpenEnd vectorDomainD3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	//create vector domain with one elements and scalinfactor 0.25
	cout<<"vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 4, 0.25 );"<<endl;
	vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 4, 0.25 );
	cout<<"cDomainVectorOpenEnd vectorDomainD1S0p25( vecDomains1 );"<<endl;
	cDomainVectorOpenEnd vectorDomainD1S0p25( vecDomains1 );
	delete vecDomains1[ 0 ];


	cout<<"cVectorPosition vecPositionD1( 1 );"<<endl;
	cVectorPosition vecPositionD1( 1 );
	cout<<"vecPositionD1.setValue( 1, 1.0 );"<<endl;
	vecPositionD1.setValue( 1, 1.0 );

	if ( vectorDomainD1.isElement( vecPositionD1 ) ){
	
		cout<<"The vector vecPositionD1 is an element of the domain vectorDomain1."<<endl;
	}else{
		cerr<<"Error: The vector vecPositionD1 is not an element of the domain vectorDomain1."<<endl;
		iReturn++;
	}
	
	if ( vectorDomainD1S0p25.isElement( vecPositionD1 ) ){
	
		cout<<"The vector vectorDomainD1S0p25 is an element of the domain vectorDomainD1S0p25."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD1S0p25 is not an element of the domain vectorDomainD1S0p25."<<endl;
		iReturn++;
	}

	if ( ! vectorDomainD3.isElement( vecPositionD1 ) ){
	
		cout<<"The vector vectorDomainD3 is not an element of the domain vectorDomainD3."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD3 is an element of the domain vectorDomainD3."<<endl;
		iReturn++;
	}

	cout<<"vecPositionD1.setValue( 1, -1.0 );"<<endl;
	vecPositionD1.setValue( 1, -1.0 );

	if ( ! vectorDomainD1.isElement( vecPositionD1 ) ){
	
		cout<<"The vector vecPositionD1 is not an element of the domain vectorDomain1."<<endl;
	}else{
		cerr<<"Error: The vector vecPositionD1 is an element of the domain vectorDomain1."<<endl;
		iReturn++;
	}
	
	if ( ! vectorDomainD1S0p25.isElement( vecPositionD1 ) ){
	
		cout<<"The vector vectorDomainD1S0p25 is not an element of the domain vectorDomainD1S0p25."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD1S0p25 is an element of the domain vectorDomainD1S0p25."<<endl;
		iReturn++;
	}

	if ( ! vectorDomainD3.isElement( vecPositionD1 ) ){
	
		cout<<"The vector vectorDomainD3 is not an element of the domain vectorDomainD3."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD3 is an element of the domain vectorDomainD3."<<endl;
		iReturn++;
	}

	cout<<"vecPositionD1.setValue( 1, 5.0 );"<<endl;
	vecPositionD1.setValue( 1, 5.0 );

	if ( vectorDomainD1.isElement( vecPositionD1 ) ){
	
		cout<<"The vector vecPositionD1 is an element of the domain vectorDomain1."<<endl;
	}else{
		cerr<<"Error: The vector vecPositionD1 is not an element of the domain vectorDomain1."<<endl;
		iReturn++;
	}
	
	if ( ! vectorDomainD1S0p25.isElement( vecPositionD1 ) ){
	
		cout<<"The vector vectorDomainD1S0p25 is not an element of the domain vectorDomainD1S0p25."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD1S0p25 is an element of the domain vectorDomainD1S0p25."<<endl;
		iReturn++;
	}

	if ( ! vectorDomainD3.isElement( vecPositionD1 ) ){
	
		cout<<"The vector vectorDomainD3 is not an element of the domain vectorDomainD3."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD3 is an element of the domain vectorDomainD3."<<endl;
		iReturn++;
	}

	cout<<"vecPositionD1.setValue( 1, 1.25 );"<<endl;
	vecPositionD1.setValue( 1, 1.25 );

	if ( ! vectorDomainD1.isElement( vecPositionD1 ) ){
	
		cout<<"The vector vecPositionD1 is not an element of the domain vectorDomain1."<<endl;
	}else{
		cerr<<"Error: The vector vecPositionD1 is an element of the domain vectorDomain1."<<endl;
		iReturn++;
	}
	
	if ( vectorDomainD1S0p25.isElement( vecPositionD1 ) ){
	
		cout<<"The vector vectorDomainD1S0p25 is an element of the domain vectorDomainD1S0p25."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD1S0p25 is not an element of the domain vectorDomainD1S0p25."<<endl;
		iReturn++;
	}

	if ( ! vectorDomainD3.isElement( vecPositionD1 ) ){
	
		cout<<"The vector vectorDomainD3 is not an element of the domain vectorDomainD3."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD3 is an element of the domain vectorDomainD3."<<endl;
		iReturn++;
	}

	cout<<"vecPositionD1.setVariable( 1, pVariable1 );"<<endl;
	vecPositionD1.setVariable( 1, pVariable1 );

	if ( vectorDomainD1.isElement( vecPositionD1 ) ){
	
		cout<<"The vector vecPositionD1 is an element of the domain vectorDomain1."<<endl;
	}else{
		cerr<<"Error: The vector vecPositionD1 is not an element of the domain vectorDomain1."<<endl;
		iReturn++;
	}
	
	if ( vectorDomainD1S0p25.isElement( vecPositionD1 ) ){
	
		cout<<"The vector vectorDomainD1S0p25 is an element of the domain vectorDomainD1S0p25."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD1S0p25 is not an element of the domain vectorDomainD1S0p25."<<endl;
		iReturn++;
	}

	if ( ! vectorDomainD3.isElement( vecPositionD1 ) ){
	
		cout<<"The vector vectorDomainD3 is not an element of the domain vectorDomainD3."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD3 is an element of the domain vectorDomainD3."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing isElement() on an vector with 3 elements"<<endl;

	cout<<"cVectorPosition vecPositionD3( 3 );"<<endl;
	cVectorPosition vecPositionD3( 3 );
	
	if ( vectorDomainD1.isElement( vecPositionD3 ) ){
	
		cout<<"The vector vectorDomainD1 is an element of the domain vectorDomain1."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD1 is not an element of the domain vectorDomain1."<<endl;
		iReturn++;
	}
	
	if ( vectorDomainD1S0p25.isElement( vecPositionD3 ) ){
	
		cout<<"The vector vectorDomainD1S0p25 is an element of the domain vectorDomainD1S0p25."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD1S0p25 is not an element of the domain vectorDomainD1S0p25."<<endl;
		iReturn++;
	}

	if ( vectorDomainD3.isElement( vecPositionD3 ) ){
	
		cout<<"The vector vectorDomainD3 is an element of the domain vectorDomainD3."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD3 is not an element of the domain vectorDomainD3."<<endl;
		iReturn++;
	}

	
	cout<<"vecPositionD3.setValue( 1, 1.0 );"<<endl;
	vecPositionD3.setValue( 1, 1.0 );

	if ( vectorDomainD1.isElement( vecPositionD3 ) ){
	
		cout<<"The vector vecPositionD1 is an element of the domain vectorDomain1."<<endl;
	}else{
		cerr<<"Error: The vector vecPositionD1 is not an element of the domain vectorDomain1."<<endl;
		iReturn++;
	}
	
	if ( vectorDomainD1S0p25.isElement( vecPositionD3 ) ){
	
		cout<<"The vector vectorDomainD1S0p25 is an element of the domain vectorDomainD1S0p25."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD1S0p25 is not an element of the domain vectorDomainD1S0p25."<<endl;
		iReturn++;
	}

	if ( vectorDomainD3.isElement( vecPositionD3 ) ){
	
		cout<<"The vector vectorDomainD3 is an element of the domain vectorDomainD3."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD3 is not an element of the domain vectorDomainD3."<<endl;
		iReturn++;
	}

	cout<<"vecPositionD3.setValue( 1, -1.0 );"<<endl;
	vecPositionD3.setValue( 1, -1.0 );

	if ( ! vectorDomainD3.isElement( vecPositionD3 ) ){
	
		cout<<"The vector vectorDomainD3 is not an element of the domain vectorDomainD3."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD3 is an element of the domain vectorDomainD3."<<endl;
		iReturn++;
	}

	cout<<"vecPositionD3.setValue( 1, 2.0 );"<<endl;
	vecPositionD3.setValue( 1, 2.0 );

	if ( ! vectorDomainD3.isElement( vecPositionD3 ) ){
	
		cout<<"The vector vectorDomainD3 is not an element of the domain vectorDomainD3."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD3 is an element of the domain vectorDomainD3."<<endl;
		iReturn++;
	}

	cout<<"vecPositionD3.setValue( 1, 1.0 );"<<endl;
	vecPositionD3.setValue( 1, 1.0 );
	cout<<"vecPositionD3.setValue( 3, -1.0 );"<<endl;
	vecPositionD3.setValue( 3, -1.0 );

	if ( ! vectorDomainD3.isElement( vecPositionD3 ) ){
	
		cout<<"The vector vectorDomainD3 is not an element of the domain vectorDomainD3."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD3 is an element of the domain vectorDomainD3."<<endl;
		iReturn++;
	}

	cout<<"vecPositionD3.setValue( 3, 7.01 );"<<endl;
	vecPositionD3.setValue( 3, 7.01 );

	if ( ! vectorDomainD3.isElement( vecPositionD3 ) ){
	
		cout<<"The vector vectorDomainD3 is not an element of the domain vectorDomainD3."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD3 is an element of the domain vectorDomainD3."<<endl;
		iReturn++;
	}

	cout<<"vecPositionD3.setValue( 3, 8.0 );"<<endl;
	vecPositionD3.setValue( 3, 8.0 );
	
	if ( ! vectorDomainD3.isElement( vecPositionD3 ) ){
	
		cout<<"The vector vectorDomainD3 is not an element of the domain vectorDomainD3."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD3 is an element of the domain vectorDomainD3."<<endl;
		iReturn++;
	}

	cout<<"vecPositionD3.setValue( 3, 7.0 );"<<endl;
	vecPositionD3.setValue( 3, 7.0 );
	
	if ( vectorDomainD3.isElement( vecPositionD3 ) ){
	
		cout<<"The vector vectorDomainD3 is an element of the domain vectorDomainD3."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD3 is not an element of the domain vectorDomainD3."<<endl;
		iReturn++;
	}

	cout<<"vecPositionD3.setValue( 2, -0.01 );"<<endl;
	vecPositionD3.setValue( 2, -0.01 );
	
	if ( ! vectorDomainD3.isElement( vecPositionD3 ) ){
	
		cout<<"The vector vectorDomainD3 is not an element of the domain vectorDomainD3."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD3 is an element of the domain vectorDomainD3."<<endl;
		iReturn++;
	}

	cout<<"vecPositionD3.setValue( 2, 0.05 );"<<endl;
	vecPositionD3.setValue( 2, 0.05 );
	
	if ( ! vectorDomainD3.isElement( vecPositionD3 ) ){
	
		cout<<"The vector vectorDomainD3 is not an element of the domain vectorDomainD3."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD3 is an element of the domain vectorDomainD3."<<endl;
		iReturn++;
	}

	cout<<"vecPositionD3.setValue( 2, 5.0 );"<<endl;
	vecPositionD3.setValue( 2, 5.0 );
	
	if ( ! vectorDomainD3.isElement( vecPositionD3 ) ){
	
		cout<<"The vector vectorDomainD3 is not an element of the domain vectorDomainD3."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD3 is an element of the domain vectorDomainD3."<<endl;
		iReturn++;
	}

	cout<<"vecPositionD3.setVariable( 2, pVariable1 );"<<endl;
	vecPositionD3.setVariable( 2, pVariable1 );

	if ( vectorDomainD3.isElement( vecPositionD3 ) ){
	
		cout<<"The vector vectorDomainD3 is an element of the domain vectorDomainD3."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD3 is not an element of the domain vectorDomainD3."<<endl;
		iReturn++;
	}

	cout<<"vecPositionD3.setVariable( 1, pVariable2 );"<<endl;
	vecPositionD3.setVariable( 1, pVariable2 );

	if ( vectorDomainD3.isElement( vecPositionD3 ) ){
	
		cout<<"The vector vectorDomainD3 is an element of the domain vectorDomainD3."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD3 is not an element of the domain vectorDomainD3."<<endl;
		iReturn++;
	}

	cout<<"vecPositionD3.setVariable( 3, pVariable2 );"<<endl;
	vecPositionD3.setVariable( 3, pVariable2 );

	if ( vectorDomainD3.isElement( vecPositionD3 ) ){
	
		cout<<"The vector vectorDomainD3 is an element of the domain vectorDomainD3."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD3 is not an element of the domain vectorDomainD3."<<endl;
		iReturn++;
	}

	cout<<"vecPositionD3.setValue( 2, 5.0 );"<<endl;
	vecPositionD3.setValue( 2, 5.0 );
	
	if ( ! vectorDomainD3.isElement( vecPositionD3 ) ){
	
		cout<<"The vector vectorDomainD3 is not an element of the domain vectorDomainD3."<<endl;
	}else{
		cerr<<"Error: The vector vectorDomainD3 is an element of the domain vectorDomainD3."<<endl;
		iReturn++;
	}


	return iReturn;
}



/**
 * This method tests the round() method of the cVectorPosition class.
 *
 * methods tested:
 * 	- round()
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testRound( unsigned long &ulTestphase ){

	unsigned int iReturn = 0;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the round() on an vector with 1 elements"<<endl;

	cout<<endl<<"creating domains to use:"<<endl<<endl;

	cout<<"cRoot rootD1;"<<flush<<endl;
	cRoot rootD1;
	
	cout<<"cTypeDimension testTypeDimensionD1( 1 );"<<endl;
	cTypeDimension testTypeDimensionD1( 1 );
	cout<<"testTypeDimensionD1.setDimensionMapping( 1, 4 )"<<endl;
	testTypeDimensionD1.setDimensionMapping( 1, 4 );
	
	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomains1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomains1( 1 );
	cout<<"vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 4 );
	cout<<"cDomainVectorOpenEnd vectorDomainD1( vecDomains1 );"<<endl;
	cDomainVectorOpenEnd vectorDomainD1( vecDomains1 );
	delete vecDomains1[ 0 ];

	cout<<"rootD1.getDomains()->addDomain( testTypeDimensionD1, vectorDomainD1);"<<endl;
	rootD1.getDomains()->addDomain( testTypeDimensionD1, vectorDomainD1);

	//creat defined variables to set them later in the vector
	cout<<"rootD1.setNumberOfInputVariables( 4 )"<<endl;
	rootD1.setNumberOfInputVariables( 4 );
	//vectors with variables
	cFibVariable * pVariable1 = rootD1.getInputVariable( 1 );
	cFibVariable * pVariable2 = rootD1.getInputVariable( 2 );


	cout<<"vector<cDomainSingle*> vecDomains3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomains3( 3 );
	cout<<"vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVectorOpenEnd vectorDomainD3( vecDomains3 );"<<endl;
	cDomainVectorOpenEnd vectorDomainD3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	//create vector domain with one elements and scalinfactor 0.25
	cout<<"vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 4, 0.25 );"<<endl;
	vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 4, 0.25 );
	cout<<"cDomainVectorOpenEnd vectorDomainD1S0p25( vecDomains1 );"<<endl;
	cDomainVectorOpenEnd vectorDomainD1S0p25( vecDomains1 );
	delete vecDomains1[ 0 ];

	cout<<"cVectorPosition vecPositionRoundedD1( 1 );"<<endl;
	cVectorPosition vecPositionRoundedD1( 1 );
	cout<<"vecPositionRoundedD1.setValue( 1, 1.0 );"<<endl;
	vecPositionRoundedD1.setValue( 1, 1.0 );

	cout<<"cVectorPosition vecPositionRoundedD1S0p25( 1 );"<<endl;
	cVectorPosition vecPositionRoundedD1S0p25( 1 );
	cout<<"vecPositionRoundedD1S0p25.setValue( 1, 1.0 );"<<endl;
	vecPositionRoundedD1S0p25.setValue( 1, 1.0 );

	cout<<"cVectorPosition vecPositionRoundedD3( 3 );"<<endl;
	cVectorPosition vecPositionRoundedD3( 3 );
	cout<<"vecPositionRoundedD3.setValue( 1, 1.0 );"<<endl;
	vecPositionRoundedD3.setValue( 1, 1.0 );


	cout<<"roundedVector = vectorDomainD1.round( vecPositionRoundedD1 );"<<endl;
	cFibVector * roundedVector = vectorDomainD1.round( vecPositionRoundedD1 );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD1 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"roundedVector = vectorDomainD1S0p25.round( vecPositionRoundedD1 );"<<endl;
	roundedVector = vectorDomainD1S0p25.round( vecPositionRoundedD1 );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD1S0p25 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}
	
	cout<<"roundedVector = vectorDomainD3.round( vecPositionRoundedD1 );"<<endl;
	roundedVector = vectorDomainD3.round( vecPositionRoundedD1 );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD3 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the round() on an vector with 1 element wich is set to 1.25"<<endl;

	cout<<"cVectorPosition vecPosition2D1( 1 );"<<endl;
	cVectorPosition vecPosition2D1( 1 );
	cout<<"vecPosition2D1.setValue( 1, 1.25 );"<<endl;
	vecPosition2D1.setValue( 1, 1.25 );
	

	cout<<"vecPositionRoundedD1.setValue( 1, 1.0 );"<<endl;
	vecPositionRoundedD1.setValue( 1, 1.0 );

	cout<<"vecPositionRoundedD1S0p25.setValue( 1, 1.25 );"<<endl;
	vecPositionRoundedD1S0p25.setValue( 1, 1.25 );

	cout<<"vecPositionRoundedD3.setValue( 1, 1.0 );"<<endl;
	vecPositionRoundedD3.setValue( 1, 1.0 );


	cout<<"roundedVector = vectorDomainD1.round( vecPosition2D1 );"<<endl;
	roundedVector = vectorDomainD1.round( vecPosition2D1 );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD1 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"roundedVector = vectorDomainD1S0p25.round( vecPosition2D1 );"<<endl;
	roundedVector = vectorDomainD1S0p25.round( vecPosition2D1 );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD1S0p25 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"roundedVector = vectorDomainD3.round( vecPosition2D1 );"<<endl;
	roundedVector = vectorDomainD3.round( vecPosition2D1 );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD3 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the round() on an vector with 1 element wich is set to 2.2"<<endl;
	
	cout<<"cVectorPosition * vectorToRound = new cVectorPosition( 1 );"<<endl;
	cVectorPosition * vectorToRound = new cVectorPosition( 1 );
	cout<<"vectorToRound->setValue( 1, 2.2 );"<<endl;
	vectorToRound->setValue( 1, 2.2 );

	cout<<"vecPositionRoundedD1.setValue( 1, 2.0 );"<<endl;
	vecPositionRoundedD1.setValue( 1, 2.0 );

	cout<<"vecPositionRoundedD1S0p25.setValue( 1, 2.25 );"<<endl;
	vecPositionRoundedD1S0p25.setValue( 1, 2.25 );

	cout<<"vecPositionRoundedD3.setValue( 1, 1.0 );"<<endl;
	vecPositionRoundedD3.setValue( 1, 1.0 );


	cout<<"roundedVector = vectorDomainD1.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD1 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"roundedVector = vectorDomainD1S0p25.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1S0p25.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD1S0p25 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"roundedVector = vectorDomainD3.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD3.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD3 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}
	delete vectorToRound;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the round() on an vector with 1 element wich is set to -12.0"<<endl;
	
	cout<<"vectorToRound = new cVectorPosition( 1 );"<<endl;
	vectorToRound = new cVectorPosition( 1 );
	cout<<"vectorToRound->setValue( 1, -12.0 );"<<endl;
	vectorToRound->setValue( 1, -12.0 );

	cout<<"vecPositionRoundedD1.setValue( 1, 0.0 );"<<endl;
	vecPositionRoundedD1.setValue( 1, 0.0 );

	cout<<"vecPositionRoundedD1S0p25.setValue( 1, 0.0 );"<<endl;
	vecPositionRoundedD1S0p25.setValue( 1, 0.0 );

	cout<<"vecPositionRoundedD3.setValue( 1, 0.0 );"<<endl;
	vecPositionRoundedD3.setValue( 1, 0.0 );


	cout<<"roundedVector = vectorDomainD1.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD1 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"roundedVector = vectorDomainD1S0p25.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1S0p25.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD1S0p25 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"roundedVector = vectorDomainD3.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD3.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD3 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}
	delete vectorToRound;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the round() on an vector with 1 element wich is set to 6"<<endl;
	
	cout<<"vectorToRound = new cVectorPosition( 1 );"<<endl;
	vectorToRound = new cVectorPosition( 1 );
	cout<<"vectorToRound->setValue( 1, 6.0 );"<<endl;
	vectorToRound->setValue( 1, 6.0 );

	cout<<"vecPositionRoundedD1.setValue( 1, 6.0 );"<<endl;
	vecPositionRoundedD1.setValue( 1, 6.0 );

	cout<<"vecPositionRoundedD1S0p25.setValue( 1, 3.75 );"<<endl;
	vecPositionRoundedD1S0p25.setValue( 1, 3.75 );

	cout<<"vecPositionRoundedD3.setValue( 1, 1.0 );"<<endl;
	vecPositionRoundedD3.setValue( 1, 1.0 );


	cout<<"roundedVector = vectorDomainD1.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD1 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"roundedVector = vectorDomainD1S0p25.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1S0p25.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD1S0p25 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"roundedVector = vectorDomainD3.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD3.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD3 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}
	delete vectorToRound;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the round() on an vector with 1 element wich is set to a variable"<<endl;
	
	cout<<"vectorToRound = new cVectorPosition( 1 );"<<endl;
	vectorToRound = new cVectorPosition( 1 );
	cout<<"vectorToRound->setVariable( 1, pVariable1 );"<<endl;
	vectorToRound->setVariable( 1, pVariable1 );

	cout<<"vecPositionRoundedD1.setVariable( 1, pVariable1 );"<<endl;
	vecPositionRoundedD1.setVariable( 1, pVariable1 );

	cout<<"vecPositionRoundedD1S0p25.setVariable( 1, pVariable1 );"<<endl;
	vecPositionRoundedD1S0p25.setVariable( 1, pVariable1 );

	cout<<"vecPositionRoundedD3.setVariable( 1, pVariable1 );"<<endl;
	vecPositionRoundedD3.setVariable( 1, pVariable1 );


	cout<<"roundedVector = vectorDomainD1.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD1 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"roundedVector = vectorDomainD1S0p25.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1S0p25.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD1S0p25 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"roundedVector = vectorDomainD3.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD3.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD3 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}
	delete vectorToRound;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the round() on an vector with 1 element wich is set to 2.5001"<<endl;
	
	cout<<"vectorToRound = new cVectorPosition( 1 );"<<endl;
	vectorToRound = new cVectorPosition( 1 );
	cout<<"vectorToRound->setValue( 1, 2.5001 );"<<endl;
	vectorToRound->setValue( 1, 2.5001 );

	cout<<"vecPositionRoundedD1.setValue( 1, 3.0 );"<<endl;
	vecPositionRoundedD1.setValue( 1, 3.0 );

	cout<<"vecPositionRoundedD1S0p25.setValue( 1, 2.5 );"<<endl;
	vecPositionRoundedD1S0p25.setValue( 1, 2.5 );

	cout<<"vecPositionRoundedD3.setValue( 1, 1.0 );"<<endl;
	vecPositionRoundedD3.setValue( 1, 1.0 );


	cout<<"roundedVector = vectorDomainD1.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD1 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"roundedVector = vectorDomainD1S0p25.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1S0p25.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD1S0p25 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"roundedVector = vectorDomainD3.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD3.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD3 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}
	delete vectorToRound;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the round() on an vector with 1 element wich is set to 2.4999"<<endl;
	
	cout<<"vectorToRound = new cVectorPosition( 1 );"<<endl;
	vectorToRound = new cVectorPosition( 1 );
	cout<<"vectorToRound->setValue( 1, 2.4999 );"<<endl;
	vectorToRound->setValue( 1, 2.4999 );

	cout<<"vecPositionRoundedD1.setValue( 1, 2.0 );"<<endl;
	vecPositionRoundedD1.setValue( 1, 2.0 );

	cout<<"vecPositionRoundedD1S0p25.setValue( 1, 2.5 );"<<endl;
	vecPositionRoundedD1S0p25.setValue( 1, 2.5 );

	cout<<"vecPositionRoundedD3.setValue( 1, 1.0 );"<<endl;
	vecPositionRoundedD3.setValue( 1, 1.0 );


	cout<<"roundedVector = vectorDomainD1.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD1 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"roundedVector = vectorDomainD1S0p25.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1S0p25.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD1S0p25 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"roundedVector = vectorDomainD3.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD3.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD3 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}
	delete vectorToRound;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the round() on an vector with 2 elements wich is set to (0.56, 2.2) "<<endl;
	
	cout<<"vectorToRound = new cVectorPosition( 2 );"<<endl;
	vectorToRound = new cVectorPosition( 2 );
	cout<<"vectorToRound->setValue( 1, 0.56 );"<<endl;
	vectorToRound->setValue( 1, 0.56 );
	cout<<"vectorToRound->setValue( 2, 2.2 );"<<endl;
	vectorToRound->setValue( 2, 2.2 );

	cout<<"vecPositionRoundedD3.setValue( 1, 1.0 );"<<endl;
	vecPositionRoundedD3.setValue( 1, 1.0 );
	cout<<"vecPositionRoundedD3.setValue( 2, 2.0 );"<<endl;
	vecPositionRoundedD3.setValue( 2, 2.0 );

	cout<<"cVectorPosition vecPositionRoundedD2ForD1( 2 );"<<endl;
	cVectorPosition vecPositionRoundedD2ForD1( 2 );
	cout<<"vecPositionRoundedD2ForD1.setValue( 1, 1 );"<<endl;
	vecPositionRoundedD2ForD1.setValue( 1, 1 );
	cout<<"vecPositionRoundedD2ForD1.setValue( 2, 2 );"<<endl;
	vecPositionRoundedD2ForD1.setValue( 2, 2 );

	cout<<"roundedVector = vectorDomainD1.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD2ForD1 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"cVectorPosition vecPositionRoundedD2ForD1S0p25( 2 );"<<endl;
	cVectorPosition vecPositionRoundedD2ForD1S0p25( 2 );
	cout<<"vecPositionRoundedD2ForD1S0p25.setValue( 1, 0.5 );"<<endl;
	vecPositionRoundedD2ForD1S0p25.setValue( 1, 0.5 );
	cout<<"vecPositionRoundedD2ForD1S0p25.setValue( 2, 2.25 );"<<endl;
	vecPositionRoundedD2ForD1S0p25.setValue( 2, 2.25 );

	cout<<"roundedVector = vectorDomainD1S0p25.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1S0p25.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD2ForD1S0p25 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"roundedVector = vectorDomainD3.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD3.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD3 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}
	delete vectorToRound;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the round() on an vector with 3 elements wich is set to (0.56, 4.2, 4.6) "<<endl;
	
	cout<<"vectorToRound = new cVectorPosition( 3 );"<<endl;
	vectorToRound = new cVectorPosition( 3 );
	cout<<"vectorToRound->setValue( 1, 0.56 );"<<endl;
	vectorToRound->setValue( 1, 0.56 );
	cout<<"vectorToRound->setValue( 2, 4.2 );"<<endl;
	vectorToRound->setValue( 2, 4.2 );
	cout<<"vectorToRound->setValue( 3, 4.6 );"<<endl;
	vectorToRound->setValue( 3, 4.6 );

	cout<<"vecPositionRoundedD3.setValue( 1, 1.0 );"<<endl;
	vecPositionRoundedD3.setValue( 1, 1.0 );
	cout<<"vecPositionRoundedD3.setValue( 2, 4.0 );"<<endl;
	vecPositionRoundedD3.setValue( 2, 4.0 );
	cout<<"vecPositionRoundedD3.setValue( 3, 5.0 );"<<endl;
	vecPositionRoundedD3.setValue( 3, 5.0 );

	cout<<"roundedVector = vectorDomainD1.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD3 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"cVectorPosition vecPositionRoundedD3ForD1S0p25( 3 );"<<endl;
	cVectorPosition vecPositionRoundedD3ForD1S0p25( 3 );
	cout<<"vecPositionRoundedD3ForD1S0p25.setValue( 1, 0.5 );"<<endl;
	vecPositionRoundedD3ForD1S0p25.setValue( 1, 0.5 );
	cout<<"vecPositionRoundedD3ForD1S0p25.setValue( 2, 3.75 );"<<endl;
	vecPositionRoundedD3ForD1S0p25.setValue( 2, 3.75 );
	cout<<"vecPositionRoundedD3ForD1S0p25.setValue( 3, 3.75 );"<<endl;
	vecPositionRoundedD3ForD1S0p25.setValue( 3, 3.75  );

	cout<<"roundedVector = vectorDomainD1S0p25.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1S0p25.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD3ForD1S0p25 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"vecPositionRoundedD3.setValue( 2, 3.0 );"<<endl;
	vecPositionRoundedD3.setValue( 2, 3.0 );

	cout<<"roundedVector = vectorDomainD3.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD3.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		cout<<"? vecPositionRoundedD3 == (*roundedVector)"<<endl;
		if ( vecPositionRoundedD3 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}
	delete vectorToRound;

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the round() on an vector with 3 elements wich is set to (0.56, -4.2, -4.6) "<<endl;
	
	cout<<"vectorToRound = new cVectorPosition( 3 );"<<endl;
	vectorToRound = new cVectorPosition( 3 );
	cout<<"vectorToRound->setValue( 1, 0.56 );"<<endl;
	vectorToRound->setValue( 1, 0.56 );
	cout<<"vectorToRound->setValue( 2, -4.2 );"<<endl;
	vectorToRound->setValue( 2, -4.2 );
	cout<<"vectorToRound->setValue( 3, -4.6 );"<<endl;
	vectorToRound->setValue( 3, -4.6 );

	cout<<"vecPositionRoundedD3.setValue( 1, 1.0 );"<<endl;
	vecPositionRoundedD3.setValue( 1, 1.0 );
	cout<<"vecPositionRoundedD3.setValue( 2, 0.0 );"<<endl;
	vecPositionRoundedD3.setValue( 2, 0.0 );
	cout<<"vecPositionRoundedD3.setValue( 3, 0.0 );"<<endl;
	vecPositionRoundedD3.setValue( 3, 0.0 );

	cout<<"roundedVector = vectorDomainD1.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD3 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"vecPositionRoundedD3.setValue( 1, 0.5 );"<<endl;
	vecPositionRoundedD3.setValue( 1, 0.5 );

	cout<<"roundedVector = vectorDomainD1S0p25.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1S0p25.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD3 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"vecPositionRoundedD3.setValue( 1, 1 );"<<endl;
	vecPositionRoundedD3.setValue( 1, 1 );

	cout<<"roundedVector = vectorDomainD3.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD3.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD3 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}
	delete vectorToRound;
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the round() on an vector with 3 elements wich is set to (0.56, 6.2, 11.6) "<<endl;
	
	cout<<"vectorToRound = new cVectorPosition( 3 );"<<endl;
	vectorToRound = new cVectorPosition( 3 );
	cout<<"vectorToRound->setValue( 1, 0.56 );"<<endl;
	vectorToRound->setValue( 1, 0.56 );
	cout<<"vectorToRound->setValue( 2, 6.2 );"<<endl;
	vectorToRound->setValue( 2, 6.2 );
	cout<<"vectorToRound->setValue( 3, 11.6 );"<<endl;
	vectorToRound->setValue( 3, 11.6 );

	cout<<"vecPositionRoundedD3.setValue( 1, 1.0 );"<<endl;
	vecPositionRoundedD3.setValue( 1, 1.0 );
	cout<<"vecPositionRoundedD3.setValue( 2, 6.0 );"<<endl;
	vecPositionRoundedD3.setValue( 2, 6.0 );
	cout<<"vecPositionRoundedD3.setValue( 3, 12.0 );"<<endl;
	vecPositionRoundedD3.setValue( 3, 12.0 );

	cout<<"roundedVector = vectorDomainD1.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD3 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"vecPositionRoundedD3.setValue( 1, 0.5 );"<<endl;
	vecPositionRoundedD3.setValue( 1, 0.5 );
	cout<<"vecPositionRoundedD3.setValue( 2, 3.75 );"<<endl;
	vecPositionRoundedD3.setValue( 2, 3.75 );
	cout<<"vecPositionRoundedD3.setValue( 3, 3.75 );"<<endl;
	vecPositionRoundedD3.setValue( 3, 3.75 );

	cout<<"roundedVector = vectorDomainD1S0p25.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1S0p25.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD3 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"vecPositionRoundedD3.setValue( 1, 1.0 );"<<endl;
	vecPositionRoundedD3.setValue( 1, 1.0 );
	cout<<"vecPositionRoundedD3.setValue( 2, 3.0 );"<<endl;
	vecPositionRoundedD3.setValue( 2, 3.0 );
	cout<<"vecPositionRoundedD3.setValue( 3, 7.0 );"<<endl;
	vecPositionRoundedD3.setValue( 3, 7.0 );

	cout<<"roundedVector = vectorDomainD3.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD3.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD3 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}
	delete vectorToRound;
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the round() on an vector with 3 elements wich is set to (0.56, pVariable1, pVariable2) "<<endl;
	
	cout<<"vectorToRound = new cVectorPosition( 3 );"<<endl;
	vectorToRound = new cVectorPosition( 3 );
	cout<<"vectorToRound->setValue( 1, 0.56 );"<<endl;
	vectorToRound->setValue( 1, 0.56 );
	cout<<"vectorToRound->setVariable( 2, pVariable1 );"<<endl;
	vectorToRound->setVariable( 2, pVariable1 );
	cout<<"vectorToRound->setVariable( 3, pVariable2 );"<<endl;
	vectorToRound->setVariable( 3, pVariable2 );

	cout<<"vecPositionRoundedD3.setValue( 1, 1.0 );"<<endl;
	vecPositionRoundedD3.setValue( 1, 1.0 );
	cout<<"vecPositionRoundedD3.setVariable( 2, pVariable1 );"<<endl;
	vecPositionRoundedD3.setVariable( 2, pVariable1 );
	cout<<"vecPositionRoundedD3.setVariable( 3, pVariable2 );"<<endl;
	vecPositionRoundedD3.setVariable( 3, pVariable2 );

	cout<<"roundedVector = vectorDomainD1.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD3 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"vecPositionRoundedD3.setValue( 1, 0.5 );"<<endl;
	vecPositionRoundedD3.setValue( 1, 0.5 );

	cout<<"roundedVector = vectorDomainD1S0p25.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD1S0p25.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD3 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}

	cout<<"vecPositionRoundedD3.setValue( 1, 1 );"<<endl;
	vecPositionRoundedD3.setValue( 1, 1 );

	cout<<"roundedVector = vectorDomainD3.round( *vectorToRound );"<<endl;
	roundedVector = vectorDomainD3.round( *vectorToRound );
	
	if ( roundedVector != NULL ){

		if ( vecPositionRoundedD3 == (*roundedVector) ){
			cout<<"The rounded vector is correct."<<endl;
		}else{
			cerr<<"Error: The rounded vector is not correct."<<endl;
			iReturn++;
		}
		delete roundedVector;
	}else{
		cerr<<"Error: No rounded vector returned."<<endl;
		iReturn++;
	}
	delete vectorToRound;
	

	return iReturn;
}



/**
 * This method tests a in the xml -format stored cDomainVectorOpenEnd with
 * cDomainNaturalNumberBit domains.
 *
 * @param szFilename the name of the file wher the cDomainNaturalNumberBit is stored
 * @param uiNumberOfElements the number of elements in the vector domain;
 * 	every element is an cDomainNaturalNumberBit
 * @param vecUiBits a vector with the bits the cDomainNaturalNumberBit
 * 	domains have
 * @param vecScalingfactor a vector with the scalingfactors for the
 * 	cDomainNaturalNumberBit domains have
 * @return the number of errors occured in the test
 */
int testXmlVectorDomain( const string szFilename, const unsigned int uiNumberOfElements,
		const vector<unsigned int> vecUiBits,
		const vector<double> vecScalingfactor ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored domain:"<<endl;
	
	TiXmlDocument xmlDocVectorPosition( szFilename );
	bool loadOkay = xmlDocVectorPosition.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\"."<<endl;
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

		if ( szElementName == "vectorOpenEnd" ){
			cout<<"The root element is correctly named \"vectorOpenEnd\"."<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"vectorOpenEnd\"."<<endl;
			iReturn++;
		}
		
		int iNumberOfElementsLoaded = 0;
		const char * pcAttributElements = pXmlElement->Attribute( "elements",
			&iNumberOfElementsLoaded );
		
		if ( pcAttributElements == NULL ){
			cerr<<"Error: The domain has no attribute \"elements\"."<<endl;
			iReturn++;
		}else if ( iNumberOfElementsLoaded == (int)uiNumberOfElements ) {
			cout<<"The number of elements of the domain are correctly \""<<
				uiNumberOfElements <<"\"."<<endl;
		}else{
			cerr<<"Error: The number of elements of the loaded domain are \""<<
				iNumberOfElementsLoaded <<"\", but should be \""<<
				uiNumberOfElements <<"\"."<<endl;
			iReturn++;
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}
	
	xmlRootHandle = xmlHandle.FirstChildElement();

	pXmlElement = xmlRootHandle.FirstChild().Element();
	unsigned int uiActualSubdomain = 0;
	//for every subdomain
	for( uiActualSubdomain = 0; pXmlElement; 
			pXmlElement = pXmlElement->NextSiblingElement(), uiActualSubdomain++ ){

		unsigned int uiBits = vecUiBits[ uiActualSubdomain ];
		double dScalingFactor = vecScalingfactor[ uiActualSubdomain ];
	
		// should always have a valid root but handle gracefully if it does
		string szElementName = pXmlElement->Value();

		if ( szElementName == "naturalNumberB" ){
			cout<<"The  element is correctly named \"naturalNumberB\"."<<endl;
		
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
			cout<<"The number of bits of the domain are correctly \""<< uiBits <<"\"."<<endl;
		}else{
			cerr<<"Error: The number of bits of the loaded domain are \""<< iBitsLoaded
				<<"\", but should be \""<< uiBits <<"\"."<<endl;
			iReturn++;
		}

		const char * pcAttributeScalingFactor =
			pXmlElement->Attribute( "scalingfactor" );
		
		if ( ( dScalingFactor == 1.0 ) && ( pcAttributeScalingFactor == NULL ) ){
			//no scalingfactor needed
			cout<<"No scalingfactor attribut. This is correct because the scalingfactor is 1.0 ."<<endl;
		}else{
			if ( pcAttributeScalingFactor == NULL ){
				cerr<<"Error: The domain has no attribute scaling factor."<<endl;
				iReturn++;
			}else{
				const double dReadScalingFactor =
					readDoubleFromFunction( pcAttributeScalingFactor );
				
				if ( dScalingFactor == dReadScalingFactor ) {
					cout<<"The scaling factor of the domain is correctly \""<< pcAttributeScalingFactor <<"\"."<<endl;
				}else{
					cerr<<"Error: The scaling factor of the loaded domain is \""<<
						pcAttributeScalingFactor<<"\"(="<<dReadScalingFactor<<
						"), but should be \""<<dScalingFactor <<"\" ."<<endl;
					iReturn++;
				}
			}
		}
	}
	
	if ( uiActualSubdomain == uiNumberOfElements ){
		cout<<"The number of subdomains is correct."<<endl;
	
	}else{
		cerr<<"Error: The number of subdomains is "<< uiActualSubdomain <<
			", but should be "<< uiNumberOfElements <<"."<<endl;
		iReturn++;
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

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple vectordomain with no elements"<<endl;
	
	cout<<"vector<cDomainSingle*> vecDomains0( 0 );"<<endl;
	vector<cDomainSingle*> vecDomains0( 0 );
	cout<<"cDomainVectorOpenEnd vectorDomainE0( vecDomains0 );"<<endl;
	cDomainVectorOpenEnd vectorDomainE0( vecDomains0 );
	
	vector<unsigned int> vecDomainE0Bits(0);
	vector<double> vecDomainE0Scalingfactor(0);

	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "DomainVectorOpenEndE0.xml" );
	ofstream * fileXml = new ofstream( szFileNameBuffer );
	
	bool bStoreSuccesfull = vectorDomainE0.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlVectorDomain( szFileNameBuffer, 0, vecDomainE0Bits, vecDomainE0Scalingfactor );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple vectordomain with one element"<<endl;
	
	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomains1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomains1( 1 );
	cout<<"vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 4 );
	cout<<"cDomainVectorOpenEnd DomainVectorOpenEndE1( vecDomains1 );"<<endl;
	cDomainVectorOpenEnd DomainVectorOpenEndE1( vecDomains1 );
	delete vecDomains1[ 0 ];
	
	vector<unsigned int> vecDomainE1Bits(1);
	vecDomainE1Bits[ 0 ] = 4;
	vector<double> vecDomainE1Scalingfactor(1);
	vecDomainE1Scalingfactor[ 0 ] = 1.0;

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "DomainVectorOpenEndE1.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	bStoreSuccesfull = DomainVectorOpenEndE1.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlVectorDomain( szFileNameBuffer, 1, vecDomainE1Bits, vecDomainE1Scalingfactor );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple vectordomain with tree elements"<<endl;
	
	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomains3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomains3( 3 );
	cout<<"vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 1, 1.0 );"<<endl;
	vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 1, 1.0 );
	cout<<"vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 2, 5.0 );"<<endl;
	vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 2, 5.0 );
	cout<<"vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 3, 3.0 );"<<endl;
	vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 3, 3.0 );
	cout<<"cDomainVectorOpenEnd DomainVectorOpenEndE3( vecDomains1 );"<<endl;
	cDomainVectorOpenEnd DomainVectorOpenEndE3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	vector<unsigned int> vecDomainE3Bits( 3 );
	vecDomainE3Bits[ 0 ] = 1;
	vecDomainE3Bits[ 1 ] = 2;
	vecDomainE3Bits[ 2 ] = 3;
	vector<double> vecDomainE3Scalingfactor( 3 );
	vecDomainE3Scalingfactor[ 0 ] = 1.0;
	vecDomainE3Scalingfactor[ 1 ] = 5.0;
	vecDomainE3Scalingfactor[ 2 ] = 3.0;

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "DomainVectorOpenEndE3.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	bStoreSuccesfull = DomainVectorOpenEndE3.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlVectorDomain( szFileNameBuffer, 3, vecDomainE3Bits, vecDomainE3Scalingfactor );

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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple vector with an integer domain with 4 Bits and scaling factor 1"<<endl;
	
	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomains1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomains1( 1 );
	cout<<"vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 4 );
	cout<<"cDomainVectorOpenEnd DomainVectorOpenEndE1( vecDomains1 );"<<endl;
	cDomainVectorOpenEnd DomainVectorOpenEndE1( vecDomains1 );
	delete vecDomains1[ 0 ];

	//test get compressed size
	if ( DomainVectorOpenEndE1.getCompressedSize() == 32 ){
	
		cout<<"The compressed size of the domain is correctly 32 ."<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			DomainVectorOpenEndE1.getCompressedSize() << ", but should be 32 ."<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "DomainVectorOpenEndE1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	bool bStoreSuccesfull = DomainVectorOpenEndE1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<"."<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0."<<endl;
		iReturn++;
	}

	//test stored data
	const char cDomainVectorOpenEndE1[] = { (char)0xE0,
		(char)0x01, //8 bit parameter for number of elements
		(char)0x00, (char)0x04, (char)0x00};//natural number domain
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainVectorOpenEndE1, 5 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple vector with no elements"<<endl;
	
	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomains0( 0 );"<<endl;
	vector<cDomainSingle*> vecDomains0( 0 );
	cout<<"cDomainVectorOpenEnd DomainVectorOpenEndE0( vecDomains0 );"<<endl;
	cDomainVectorOpenEnd DomainVectorOpenEndE0( vecDomains0 );

	//test get compressed size
	if ( DomainVectorOpenEndE0.getCompressedSize() == 16 ){
	
		cout<<"The compressed size of the domain is correctly 16 ."<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			DomainVectorOpenEndE0.getCompressedSize() << ", but should be 16 ."<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "DomainVectorOpenEndE0.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	 bStoreSuccesfull = DomainVectorOpenEndE0.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<"."<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0."<<endl;
		iReturn++;
	}

	//test stored data
	const char cDomainVectorOpenEndE0[] = {(char)0xE0,
		(char)0x00, //8 bit parameter for number of elements
		(char)0x00};//no natural number domain
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainVectorOpenEndE0, 3 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a vector with tree integer domains"<<endl;
	
	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomains3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomains3( 3 );
	cout<<"vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVectorOpenEnd DomainVectorOpenEndE3( vecDomains3 );"<<endl;
	cDomainVectorOpenEnd DomainVectorOpenEndE3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	//test get compressed size
	unsigned int uiCompressedSize = 16 + 3 * 16;
	if ( DomainVectorOpenEndE3.getCompressedSize() == uiCompressedSize ){
	
		cout<<"The compressed size of the domain is correctly " <<
			uiCompressedSize << " ."<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			DomainVectorOpenEndE3.getCompressedSize() << ", but should be " <<
			uiCompressedSize << " ."<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "DomainVectorOpenEndE3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = DomainVectorOpenEndE3.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<"."<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0."<<endl;
		iReturn++;
	}

	//test stored data
	const char cDomainVectorOpenEndE3[] = {(char)0xE0,
		(char)0x03, //8 bit parameter for number of elements
		(char)0x00, (char)0x01,//natural number domain 1
		(char)0x00, (char)0x02,//natural number domain 2
		(char)0x00, (char)0x03,//natural number domain 3
		(char)0x00};
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainVectorOpenEndE3, 9 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a vector with 255 integer domains"<<endl;
	
	//create vector domain with one elements
	unsigned int uiNumberOfSubdomains = 255;
	uiCompressedSize = 16 + uiNumberOfSubdomains * 16;
	cout<<"vector<cDomainSingle*> vecDomains255( uiNumberOfSubdomains );"<<endl;
	vector<cDomainSingle*> vecDomains255( uiNumberOfSubdomains );
	
	cout<<"vecDomains255[ 1 .."<< uiNumberOfSubdomains <<" ]=new cDomainNaturalNumberBit( 1 );"<<endl;
	for ( unsigned int uiActualSubDomain = 0;
			uiActualSubDomain < uiNumberOfSubdomains; uiActualSubDomain++  ){
		vecDomains255[ uiActualSubDomain ]=new cDomainNaturalNumberBit( 1 );
	}
	
	cout<<"cDomainVectorOpenEnd DomainVectorOpenEndE255( vecDomains255 );"<<endl;
	cDomainVectorOpenEnd DomainVectorOpenEndE255( vecDomains255 );
	for ( unsigned int uiActualSubDomain = 0;
			uiActualSubDomain < uiNumberOfSubdomains; uiActualSubDomain++  ){
		delete vecDomains255[ uiActualSubDomain ];
	}

	//test get compressed size
	if ( DomainVectorOpenEndE255.getCompressedSize() == uiCompressedSize ){
	
		cout<<"The compressed size of the domain is correctly " <<
			uiCompressedSize << " ."<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			DomainVectorOpenEndE255.getCompressedSize() << ", but should be " <<
			uiCompressedSize << " ."<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "DomainVectorOpenEndE255.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = DomainVectorOpenEndE255.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<"."<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0."<<endl;
		iReturn++;
	}

	//test stored data
	char cDDomainVectorOpenEndE255[ 2 + uiNumberOfSubdomains * 2 + 1 ];
	cDDomainVectorOpenEndE255[ 0 ] = (char)0xE0;
	cDDomainVectorOpenEndE255[ 1 ] = (char)0xFF; //8 bit parameter for number of elements
	
	for ( unsigned int uiActualSubDomain = 0;
			uiActualSubDomain < uiNumberOfSubdomains; uiActualSubDomain++  ){
		//natural number domain 1
		cDDomainVectorOpenEndE255[ uiActualSubDomain * 2 + 2 ] = (char)0x00;
		cDDomainVectorOpenEndE255[ uiActualSubDomain * 2 + 3 ] = (char)0x01; //8 bit parameter for number of elements
	}
	cDDomainVectorOpenEndE255[ 2 + uiNumberOfSubdomains * 2 ] = (char)0x00; //retsbyte

	iReturn += compareBytsWithFile( szFileNameBuffer, cDDomainVectorOpenEndE255, 2 + uiNumberOfSubdomains * 2 + 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a vector with 256 integer domains"<<endl;
	
	//create vector domain with one elements
	uiNumberOfSubdomains = 256;
	uiCompressedSize = 8 + 64 + uiNumberOfSubdomains * 16;
	cout<<"vector<cDomainSingle*> vecDomains256( uiNumberOfSubdomains );"<<endl;
	vector<cDomainSingle*> vecDomains256( uiNumberOfSubdomains );
	
	cout<<"vecDomains255[ 1 .."<< uiNumberOfSubdomains <<" ]=new cDomainNaturalNumberBit( 1 );"<<endl;
	for ( unsigned int uiActualSubDomain = 0;
			uiActualSubDomain < uiNumberOfSubdomains; uiActualSubDomain++  ){
		vecDomains256[ uiActualSubDomain ]=new cDomainNaturalNumberBit( 1 );
	}
	
	cout<<"cDomainVectorOpenEnd DomainVectorOpenEndE256( vecDomains256 );"<<endl;
	cDomainVectorOpenEnd DomainVectorOpenEndE256( vecDomains256 );
	for ( unsigned int uiActualSubDomain = 0;
			uiActualSubDomain < uiNumberOfSubdomains; uiActualSubDomain++  ){
		delete vecDomains256[ uiActualSubDomain ];
	}

	//test get compressed size
	if ( DomainVectorOpenEndE256.getCompressedSize() == uiCompressedSize ){
	
		cout<<"The compressed size of the domain is correctly " <<
			uiCompressedSize << " ."<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			DomainVectorOpenEndE256.getCompressedSize() << ", but should be " <<
			uiCompressedSize << " ."<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "DomainVectorOpenEndE256.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = DomainVectorOpenEndE256.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<"."<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0."<<endl;
		iReturn++;
	}

	//test stored data
	char cDDomainVectorOpenEndE256[ 9 + uiNumberOfSubdomains * 2 + 1 ];
	cDDomainVectorOpenEndE256[ 0 ] = (char)0xE4;
	//64 bit parameter for number of elements
	cDDomainVectorOpenEndE256[ 1 ] = (char)0x00;
	cDDomainVectorOpenEndE256[ 2 ] = (char)0x01;
	cDDomainVectorOpenEndE256[ 3 ] = (char)0x00;
	cDDomainVectorOpenEndE256[ 4 ] = (char)0x00;
	cDDomainVectorOpenEndE256[ 5 ] = (char)0x00;
	cDDomainVectorOpenEndE256[ 6 ] = (char)0x00;
	cDDomainVectorOpenEndE256[ 7 ] = (char)0x00;
	cDDomainVectorOpenEndE256[ 8 ] = (char)0x00;

	for ( unsigned int uiActualSubDomain = 0;
			uiActualSubDomain < uiNumberOfSubdomains; uiActualSubDomain++  ){
		//natural number domain 1
		cDDomainVectorOpenEndE256[ uiActualSubDomain * 2 + 9  ] = (char)0x00;
		cDDomainVectorOpenEndE256[ uiActualSubDomain * 2 + 10 ] = (char)0x01; //8 bit parameter for number of elements
	}
	cDDomainVectorOpenEndE256[ 9 + uiNumberOfSubdomains * 2 ] = (char)0x00; //retsbyte

	iReturn += compareBytsWithFile( szFileNameBuffer, cDDomainVectorOpenEndE256, 9 + uiNumberOfSubdomains * 2 + 1 );

	
	return iReturn;
}




