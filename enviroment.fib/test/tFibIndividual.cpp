/**
 * @file tFibIndividual
 * file name: tFibIndividual.cpp
 * @author Betti Oesterholz
 * @date 10.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cFibIndividual.
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
 * This file contains the test for the class cFibIndividual
 *
 *
 *
 *  What's tested of class cFibIndividual:
 * 	- cFibIndividual( cFibElement * pInFibObject, const cIndividualInfo & inIndividalInfo, bool bInDeleteObjectOnDestruction=true );
 * 	- string getClassName() const;
 * 	- cFibElement * getFibObject();
 * 	- void * getObject();
 * 	- cIndividualInfo * getInfo();
 * 	- bool equal( const cIndividual &individual, bool checkIdentifiers=true ) const;
 * 	- bool operator==( const cIndividual &individual ) const;
 * 	- bool operator!=( const cIndividual &individual ) const;
 *
 */
/*
History:
10.03.2010  Oesterholz  created
*/

#include "version.h"

#include "cFibIndividual.h"
#include "cIndividualInfo.h"
#include "cIndividualIdentifier.h"
#include "cFibObjectFitnessBasic.h"

#include "cRoot.h"
#include "cPoint.h"

#include <utility>
#include <iostream>


using namespace fib;
using namespace enviroment;
using namespace enviroment::fib;
using namespace std;

int testCostructor( unsigned long &ulTestphase );
int testComparison( unsigned long &ulTestphase );


int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	

	cout<<endl<<"Running Test for cFibIndividual methods"<<endl;
	cout<<      "======================================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testComparison( ulTestphase );



	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}


/**
 * This method tests the constructors of the cFibIndividual class.
 *
 * methods tested:
 * 	- cFibIndividual( cFibElement * pInFibObject, const cIndividualInfo & inIndividalInfo, bool bInDeleteObjectOnDestruction=true );
 * 	- string getClassName() const;
 * 	- cFibElement * getFibObject();
 * 	- void * getObject();
 * 	- cIndividualInfo * getInfo();
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cFibIndividual"<<endl;
	
	cPoint * pPoint1 = new cPoint();
	
	const cFibObjectFitnessBasic fitnessDummy( 0.0, 0, 0 );
	const list<cIndividualIdentifier> liParents;
	cIndividualInfo indifidualInfo1( 0, liParents, fitnessDummy,
		"individual1", "", cOperationIdentifier( 0 ),
		time_t( NULL ), 0.0, &fitnessDummy);
	
	cout<<"cFibIndividual individual1( pPoint1, indifidualInfo1 );"<<endl;
	cFibIndividual individual1( pPoint1, indifidualInfo1 );
	
	//check the getClassName() methode from cFibIndividual
	if ( individual1.getClassName() == "cFibIndividual" ){
	
		cout<<"The classname of the individual is correctly \"cFibIndividual\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the individual "<<
			individual1.getClassName() <<" but should be \"cFibIndividual\" ."<<endl;
		iReturn++;
	}
	//check the getFibObject() methode from cFibIndividual
	if ( individual1.getFibObject() == pPoint1){
	
		cout<<"The fib -object of the individual is correctly pPoint1 . "<<endl;
	}else{
		cerr<<"Error: The fib -object of the individual "<<
			individual1.getFibObject() <<" but should be pPoint1="<< pPoint1 <<" ."<<endl;
		iReturn++;
	}
	//check the getObject() methode from cFibIndividual
	if ( individual1.getObject() == (void*)(pPoint1) ){
	
		cout<<"The object of the individual is correctly pPoint1 . "<<endl;
	}else{
		cerr<<"Error: The object of the individual "<<
			individual1.getObject() <<" but should be pPoint1="<< pPoint1 <<" ."<<endl;
		iReturn++;
	}
	//check the getInfo() methode from cFibIndividual
	if ( *(individual1.getInfo()) == indifidualInfo1 ){
	
		cout<<"The information of the individual is correctly equal to indifidualInfo1 . "<<endl;
	}else{
		cerr<<"Error: The information of the individual is not equal to indifidualInfo1 ."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cFibIndividual which down't deletes it's object"<<endl;
	
	cPoint * pPoint2 = new cPoint();
	
	const cFibObjectFitnessBasic fitnessDummy2( 0.0, 2, 1 );
	cIndividualInfo indifidualInfo2( 1, liParents, fitnessDummy2,
		"individual2", "hi", cOperationIdentifier( 1 ),
		time_t( NULL ), 1.0, &fitnessDummy);
	
	cout<<"cFibIndividual individual2( pPoint2, indifidualInfo2, false );"<<endl;
	cFibIndividual individual2( pPoint2, indifidualInfo2, false );
	
	//check the getClassName() methode from cFibIndividual
	if ( individual2.getClassName() == "cFibIndividual" ){
	
		cout<<"The classname of the individual is correctly \"cFibIndividual\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the individual "<<
			individual2.getClassName() <<" but should be \"cFibIndividual\" ."<<endl;
		iReturn++;
	}
	//check the getFibObject() methode from cFibIndividual
	if ( individual2.getFibObject() == pPoint2){
	
		cout<<"The fib -object of the individual is correctly pPoint2 . "<<endl;
	}else{
		cerr<<"Error: The fib -object of the individual "<<
			individual2.getFibObject() <<" but should be pPoint2="<< pPoint2 <<" ."<<endl;
		iReturn++;
	}
	//check the getObject() methode from cFibIndividual
	if ( individual2.getObject() == (void*)(pPoint2) ){
	
		cout<<"The object of the individual is correctly pPoint2 . "<<endl;
	}else{
		cerr<<"Error: The object of the individual "<<
			individual2.getObject() <<" but should be pPoint2="<< pPoint2 <<" ."<<endl;
		iReturn++;
	}
	//check the getInfo() methode from cFibIndividual
	if ( *(individual2.getInfo()) == indifidualInfo2 ){
	
		cout<<"The information of the individual is correctly equal to indifidualInfo2 . "<<endl;
	}else{
		cerr<<"Error: The information of the individual is not equal to indifidualInfo2 ."<<endl;
		iReturn++;
	}

	delete pPoint2;


	return iReturn;
}



/**
 * This method tests the equal() method and the operator== of two given
 * cObjectIndividuals objects which are not equal.
 *
 * @param individual1 the first individual to compare
 * @param szNameIndividual1 the name of the first individual to compare
 * @param individual2 the secound individual to compare to
 * @param szNameIndividual2 the name of the secound individual to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoNotEqualIndividual( const cFibIndividual & individual1, const string & szNameIndividual1,
	const cFibIndividual & individual2, const string & szNameIndividual2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( ! individual1.equal( individual2 ) ){
	
		cout<<"The "<<szNameIndividual1<<" is not equal to "<<szNameIndividual2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameIndividual1<<" is equal to "<<
			szNameIndividual2<<"."<<endl;
		iReturn++;
	}
	if ( ! (individual1 == individual2) ){
	
		cout<<"The "<<szNameIndividual1<<" is not equal (operator==) to "<<
			szNameIndividual2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameIndividual1<<" is equal (operator==) to "<<
			szNameIndividual2<<"."<<endl;
		iReturn++;
	}
	if ( individual1 != individual2 ){
	
		cout<<"The "<<szNameIndividual1<<" is not equal (operator!=) to "<<
			szNameIndividual2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameIndividual1<<" is equal (operator!=) to "<<
			szNameIndividual2<<"."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests the equal() method and the operator== of two given
 * cObjectIndividuals objects which are equal.
 *
 * @param individual1 the first individual to compare
 * @param szNameIndividual1 the name of the first individual to compare
 * @param individual2 the secound individual to compare to
 * @param szNameIndividual2 the name of the secound individual to compare
 * @param bIdentifiersEqual if true the identifiers of bouth individuals
 * 	will be equal, else not
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualIndividual( const cFibIndividual & individual1, const string & szNameIndividual1,
	const cFibIndividual & individual2, const string & szNameIndividual2, bool bIdentifiersEqual=true ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( bIdentifiersEqual ){
		if ( individual1.equal( individual2 ) ){
		
			cout<<"The "<<szNameIndividual1<<" is equal to "<<szNameIndividual2<<". "<<endl;
		}else{
			cerr<<"Error: The "<<szNameIndividual1<<" is not equal to "<<
				szNameIndividual2<<"."<<endl;
			iReturn++;
		}
		if ( individual1 == individual2 ){
		
			cout<<"The "<<szNameIndividual1<<" is equal (operator==) to "<<
				szNameIndividual2<<". "<<endl;
		}else{
			cerr<<"Error: The "<<szNameIndividual1<<" is not equal (operator==) to "<<
				szNameIndividual2<<"."<<endl;
			iReturn++;
		}
		if ( ! (individual1 != individual2) ){
		
			cout<<"The "<<szNameIndividual1<<" is equal (operator!=) to "<<
				szNameIndividual2<<". "<<endl;
		}else{
			cerr<<"Error: The "<<szNameIndividual1<<" is not equal (operator!=) to "<<
				szNameIndividual2<<"."<<endl;
			iReturn++;
		}
	}else{
		if ( individual1.equal( individual2, false ) ){
		
			cout<<"The "<<szNameIndividual1<<" is equal to "<<szNameIndividual2<<" except the identifiers. "<<endl;
		}else{
			cerr<<"Error: The "<<szNameIndividual1<<" is not equal, except the identifiers, to "<<
				szNameIndividual2<<"."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoNotEqualIndividual( individual1, szNameIndividual1,
			individual2, szNameIndividual2 );
	}

	return iReturn;
}




/**
 * This method tests the constructor of the cFibIndividual class.
 *
 * methods tested:
 * 	- bool equal( const cIndividual &individual, bool checkIdentifiers=true ) const;
 * 	- bool operator==( const cIndividual &individual ) const;
 * 	- bool operator!=( const cIndividual &individual ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testComparison( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing comparison of cFibIndividual Objects"<<endl;

	cPoint * pPoint1 = new cPoint();
	
	const cFibObjectFitnessBasic fitnessDummy( 0.0, 0, 0 );
	const list<cIndividualIdentifier> liParents;
	cIndividualInfo indifidualInfo1( 0, liParents, fitnessDummy,
		"individual1", "", cOperationIdentifier( 0 ),
		time_t( NULL ), 0.0, &fitnessDummy);
	
	cout<<"cFibIndividual individual1( pPoint1, indifidualInfo1 );"<<endl;
	cFibIndividual individual1( pPoint1, indifidualInfo1 );

	cPoint * pPoint2 = new cPoint();
	
	cout<<"cFibIndividual individual2( pPoint2, indifidualInfo1, false );"<<endl;
	cFibIndividual individual2( pPoint2, indifidualInfo1, false );
	
	cPoint * pPoint3 = new cPoint();
	cIndividualInfo indifidualInfo2( 0, liParents, fitnessDummy,
		"individual1", "", cOperationIdentifier( 0 ),
		time_t( NULL ), 0.0, &fitnessDummy);
	
	cout<<"cFibIndividual individual3( pPoint3, indifidualInfo2 );"<<endl;
	cFibIndividual individual3( pPoint3, indifidualInfo2 );


	cPoint * pPoint4 = new cPoint();
	const cFibObjectFitnessBasic fitnessDummy2( 0.0, 2, 1 );
	cIndividualInfo indifidualInfo4( 1, liParents, fitnessDummy2,
		"individual4", "hi", cOperationIdentifier( 1 ),
		time_t( NULL ), 1.0, &fitnessDummy);
	
	cout<<"cFibIndividual individual4( pPoint4, indifidualInfo4, false );"<<endl;
	cFibIndividual individual4( pPoint4, indifidualInfo4, false );


	cVectorPosition vecPosition( 1 );
	cPoint * pPoint5 = new cPoint( &vecPosition );
	cout<<"cFibIndividual individual5( pPoint5, indifidualInfo1 );"<<endl;
	cFibIndividual individual5( pPoint5, indifidualInfo1 );

	cout<<"cFibIndividual individual6( pPoint5, indifidualInfo4, false );"<<endl;
	cFibIndividual individual6( pPoint5, indifidualInfo4, false );

	cout<<"cFibIndividual individual7( pPoint5, indifidualInfo4, false );"<<endl;
	cFibIndividual individual7( pPoint5, indifidualInfo4, false );


	//compare with individual1
	cFibIndividual * actualIndividual = &individual1;
	string szActualIndividualName = "individual1";
	iReturn += testCompareTwoEqualIndividual( *actualIndividual, szActualIndividualName, individual1, "individual1" );
	iReturn += testCompareTwoEqualIndividual( *actualIndividual, szActualIndividualName, individual2, "individual2" );
	iReturn += testCompareTwoEqualIndividual( *actualIndividual, szActualIndividualName, individual3, "individual3", false );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual4, "individual4" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual5, "individual5" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual6, "individual6" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual7, "individual7" );

	//compare with individual2
	actualIndividual = &individual2;
	szActualIndividualName = "individual2";
	iReturn += testCompareTwoEqualIndividual( *actualIndividual, szActualIndividualName, individual1, "individual1" );
	iReturn += testCompareTwoEqualIndividual( *actualIndividual, szActualIndividualName, individual2, "individual2" );
	iReturn += testCompareTwoEqualIndividual( *actualIndividual, szActualIndividualName, individual3, "individual3", false );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual4, "individual4" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual5, "individual5" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual6, "individual6" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual7, "individual7" );

	//compare with individual3
	actualIndividual = &individual3;
	szActualIndividualName = "individual3";
	iReturn += testCompareTwoEqualIndividual( *actualIndividual, szActualIndividualName, individual1, "individual1", false );
	iReturn += testCompareTwoEqualIndividual( *actualIndividual, szActualIndividualName, individual2, "individual2", false );
	iReturn += testCompareTwoEqualIndividual( *actualIndividual, szActualIndividualName, individual3, "individual3" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual4, "individual4" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual5, "individual5" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual6, "individual6" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual7, "individual7" );

	//compare with individual4
	actualIndividual = &individual4;
	szActualIndividualName = "individual4";
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual1, "individual1" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual2, "individual2" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual3, "individual3" );
	iReturn += testCompareTwoEqualIndividual( *actualIndividual, szActualIndividualName, individual4, "individual4" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual5, "individual5" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual6, "individual6" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual7, "individual7" );

	//compare with individual5
	actualIndividual = &individual5;
	szActualIndividualName = "individual5";
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual1, "individual1" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual2, "individual2" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual3, "individual3" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual4, "individual4" );
	iReturn += testCompareTwoEqualIndividual( *actualIndividual, szActualIndividualName, individual5, "individual5" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual6, "individual6" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual7, "individual7" );

	//compare with individual6
	actualIndividual = &individual6;
	szActualIndividualName = "individual6";
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual1, "individual1" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual2, "individual2" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual3, "individual3" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual4, "individual4" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual5, "individual5" );
	iReturn += testCompareTwoEqualIndividual( *actualIndividual, szActualIndividualName, individual6, "individual6" );
	iReturn += testCompareTwoEqualIndividual( *actualIndividual, szActualIndividualName, individual7, "individual7" );

	//compare with individual7
	actualIndividual = &individual7;
	szActualIndividualName = "individual7";
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual1, "individual1" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual2, "individual2" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual3, "individual3" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual4, "individual4" );
	iReturn += testCompareTwoNotEqualIndividual( *actualIndividual, szActualIndividualName, individual5, "individual5" );
	iReturn += testCompareTwoEqualIndividual( *actualIndividual, szActualIndividualName, individual6, "individual6" );
	iReturn += testCompareTwoEqualIndividual( *actualIndividual, szActualIndividualName, individual7, "individual7" );

	delete pPoint2;
	delete pPoint4;

	return iReturn;
}












