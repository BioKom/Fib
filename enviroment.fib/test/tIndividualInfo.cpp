/**
 * @file tIndividualInfo
 * file name: tIndividualInfo.cpp
 * @author Betti Oesterholz
 * @date 14.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cIndividualInfo.
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
 * This file contains the test for the class cIndividualInfo.
 * This class is tested in the enviroment.fib modul becaus a fitnessobject
 * is needed for the test.
 *
 *
 *
 *  What's tested of class cIndividualInfo:
 * 	- cIndividualInfo( unsigned long ulAlgorithmIdentifier, const list<cIndividualIdentifier> & liIdentifierOfParents, const cObjectFitness & inFitness, const string & szOperationName, const string & szOperationInfo, const cOperationIdentifier & operationIdentifier, time_t inCreationTime, double dOperationCost, const cObjectFitness & inFitnessOfBestAtCreationTime );
 * 	- cIndividualInfo( const cIndividualInfo & individualInfo );
 * 	- cIndividualIdentifier getIdentifier() const;
 * 	- bool kill();
 * 	- bool isLiving() const;
 * 	- list<cIndividualIdentifier> getIdentifiersOfParents() const;
 * 	- const cObjectFitness * getFitness() const;
 * 	- string getOperatorName() const;
 * 	- string getOperatorInfo() const;
 * 	- cOperationIdentifier getOperatorIdentifier() const;
 * 	- time_t getCreationTime() const;
 * 	- double getOperationCost() const;
 * 	- const cObjectFitness * getFitnessOfBestAtCreationTime() const;
 * 	- bool equal( const cIndividualInfo &idIndividual, bool checkIdentifiers=true ) const;
 * 	- bool operator==( const cIndividualInfo &idIndividual ) const;
 * 	- bool operator!=( const cIndividualInfo &idIndividual ) const;
 *
 */
/*
History:
14.03.2010  Oesterholz  created
*/

#include "version.h"

#include "cIndividualInfo.h"
#include "cIndividualIdentifier.h"
#include "cFibObjectFitnessBasic.h"

#include <utility>
#include <iostream>


using namespace enviroment::fib;
using namespace enviroment;
using namespace std;

int testCostructor( unsigned long &ulTestphase );
int testComparison( unsigned long &ulTestphase );


int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	

	cout<<endl<<"Running Test for cIndividualInfo methods"<<endl;
	cout<<      "========================================"<<endl;

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
 * This function tests the constructor of the cIndividualInfo and the
 * kill() method class.
 *
 * methods tested:
 * 	- cIndividualInfo( unsigned long ulAlgorithmIdentifier, const list<cIndividualIdentifier> & liIdentifierOfParents, const cObjectFitness & inFitness, const string & szOperationName, const string & szOperationInfo, const cOperationIdentifier & operationIdentifier, time_t inCreationTime, double dOperationCost, const cObjectFitness & inFitnessOfBestAtCreationTime );
 * 	- cIndividualInfo( const cIndividualInfo & individualInfo );
 * 	- cIndividualIdentifier getIdentifier() const;
 * 	- bool kill();
 * 	- bool isLiving() const;
 * 	- list<cIndividualIdentifier> getIdentifiersOfParents() const;
 * 	- const cObjectFitness * getFitness() const;
 * 	- string getOperatorName() const;
 * 	- string getOperatorInfo() const;
 * 	- cOperationIdentifier getOperatorIdentifier() const;
 * 	- time_t getCreationTime() const;
 * 	- double getOperationCost() const;
 * 	- const cObjectFitness * getFitnessOfBestAtCreationTime() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cIndividualInfo"<<endl;
	
	const cFibObjectFitnessBasic fitnessDummy1( 1.0, 0, 0 );
	const list<cIndividualIdentifier> liParents1;
	const string szOperationName1("operation1");
	const string szOperationInfo1("opInfo1");
	const cOperationIdentifier operationIdentifier1( 0 );
	const time_t creationTime1 = time_t( NULL );
	const double dOperationCost1 = 1.0;
	const cFibObjectFitnessBasic fitnessOfBestAtCreationTime1( 1.0, 0, 1 );
	cout<<"const cIndividualInfo individualInfo1( 0, liParents1, fitnessDummy1,"<<
		"szOperationName1, szOperationInfo1, operationIdentifier1,"<<
		"creationTime1, dOperationCost1, &fitnessOfBestAtCreationTime1). "<<endl;
	const cIndividualInfo individualInfo1( 0, liParents1, fitnessDummy1,
		szOperationName1, szOperationInfo1, operationIdentifier1,
		creationTime1, dOperationCost1, &fitnessOfBestAtCreationTime1);
	
	//check the getIdentifier() methode from cIndividualInfo
	if ( individualInfo1.getIdentifier() == individualInfo1.getIdentifier() ){
	
		cout<<"The individualinfo gives back the same identifier with every method call. "<<endl;
	}else{
		cerr<<"Error: The individualinfo dosn't gives back the same identifier with every method call."<<endl;
		iReturn++;
	}
	//check the isLiving() methode from cIndividualInfo
	if ( individualInfo1.isLiving() ){
	
		cout<<"The individualinfo says correctly the individual is living. "<<endl;
	}else{
		cerr<<"Error: The individualinfo says the individual is dead."<<endl;
		iReturn++;
	}
	//check the getIdentifiersOfParents() methode from cIndividualInfo
	if ( individualInfo1.getIdentifiersOfParents() == liParents1 ){
	
		cout<<"The individualinfo gives as the parents of the individual a list equal to liParents1. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned parent list is not equal to liParents1."<<endl;
		iReturn++;
	}
	//check the getFitness() methode from cIndividualInfo
	if ( individualInfo1.getFitness() != NULL ){
	
		if ( individualInfo1.getFitness() != &fitnessDummy1 ){
		
			if ( *(individualInfo1.getFitness()) == fitnessDummy1 ){
			
				cout<<"The individualinfo returned fitness is equal to fitnessDummy1. "<<endl;
			}else{
				cerr<<"Error: The individualinfo returned fitness is not equal to fitnessDummy1."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The individualinfo returned a reference to fitnessDummy1 for it's fitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The individualinfo a nullpointer for it's fitness."<<endl;
		iReturn++;
	}
	//check the getOperatorName() methode from cIndividualInfo
	if ( individualInfo1.getOperatorName() == szOperationName1 ){
	
		cout<<"The individualinfo gives as the operationame of the individual a string equal to szOperationName1. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned operationame is not equal to szOperationName1."<<endl;
		iReturn++;
	}
	//check the getOperatorInfo() methode from cIndividualInfo
	if ( individualInfo1.getOperatorInfo() == szOperationInfo1 ){
	
		cout<<"The individualinfo gives as the operatioinfo of the individual a string equal to szOperationInfo1. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned operatioinfo is not equal to szOperationInfo1."<<endl;
		iReturn++;
	}
	//check the getOperatorIdentifier() methode from cIndividualInfo
	if ( individualInfo1.getOperatorIdentifier() == operationIdentifier1 ){
	
		cout<<"The individualinfo gives a operatioidentifier which is equal to operationIdentifier1. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned operatioidentifier is not equal to operationIdentifier1."<<endl;
		iReturn++;
	}
	//check the getCreationTime() methode from cIndividualInfo
	if ( individualInfo1.getCreationTime() == creationTime1 ){
	
		cout<<"The individualinfo gives the creationtime which is equal to creationTime1. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned creationtime is not equal to creationTime1."<<endl;
		iReturn++;
	}
	//check the getOperationCost() methode from cIndividualInfo
	if ( individualInfo1.getOperationCost() == dOperationCost1 ){
	
		cout<<"The individualinfo gives the creationcost which is equal to dOperationCost1. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned creationcost is not equal to dOperationCost1."<<endl;
		iReturn++;
	}
	//check the getFitnessOfBestAtCreationTime() methode from cIndividualInfo
	if ( individualInfo1.getFitnessOfBestAtCreationTime() != NULL ){
	
		if ( individualInfo1.getFitnessOfBestAtCreationTime() != &fitnessOfBestAtCreationTime1 ){
		
			if ( *(individualInfo1.getFitnessOfBestAtCreationTime()) == fitnessOfBestAtCreationTime1 ){
			
				cout<<"The individualinfo returned fitness of the best is equal to fitnessOfBestAtCreationTime1. "<<endl;
			}else{
				cerr<<"Error: The individualinfo returned fitness of the best is not equal to fitnessOfBestAtCreationTime1."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The individualinfo returned a reference to fitnessOfBestAtCreationTime1 for it's fitness of the best."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The individualinfo a nullpointer for it's fitness of the best."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cIndividualInfo"<<endl;
	
	const cFibObjectFitnessBasic fitnessDummy2( 2.0, 2, 0 );
	list<cIndividualIdentifier> liParents2;
	liParents2.push_back( cIndividualIdentifier( 2 ) );
	liParents2.push_back( cIndividualIdentifier( 2 ) );
	liParents2.push_back( cIndividualIdentifier( 2 ) );
	const string szOperationName2("operation2:da");
	const string szOperationInfo2("opInfo2 tadta");
	const cOperationIdentifier operationIdentifier2( 2 );
	const time_t creationTime2 = time_t( NULL );
	const double dOperationCost2 = 295.1245;
	const cFibObjectFitnessBasic fitnessOfBestAtCreationTime2( 2.0, 2, 2 );
	cout<<"cIndividualInfo individualInfo2( 2, liParents2, fitnessDummy2,"<<
		"szOperationName2, szOperationInfo2, operationIdentifier2,"<<
		"inCreationTime2, dOperationCost2, &fitnessOfBestAtCreationTime2). "<<endl;
	cIndividualInfo individualInfo2( 2, liParents2, fitnessDummy2,
		szOperationName2, szOperationInfo2, operationIdentifier2,
		creationTime2, dOperationCost2, &fitnessOfBestAtCreationTime2);
	
	//check the getIdentifier() methode from cIndividualInfo
	if ( individualInfo2.getIdentifier() == individualInfo2.getIdentifier() ){
	
		cout<<"The individualinfo gives back the same identifier with every method call. "<<endl;
	}else{
		cerr<<"Error: The individualinfo dosn't gives back the same identifier with every method call."<<endl;
		iReturn++;
	}
	//check the isLiving() methode from cIndividualInfo
	if ( individualInfo2.isLiving() ){
	
		cout<<"The individualinfo says correctly the individual is living. "<<endl;
	}else{
		cerr<<"Error: The individualinfo says the individual is dead."<<endl;
		iReturn++;
	}
	//check the getIdentifiersOfParents() methode from cIndividualInfo
	if ( individualInfo2.getIdentifiersOfParents() == liParents2 ){
	
		cout<<"The individualinfo gives as the parents of the individual a list equal to liParents2. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned parent list is not equal to liParents2."<<endl;
		iReturn++;
	}
	//check the getFitness() methode from cIndividualInfo
	if ( individualInfo2.getFitness() != NULL ){
	
		if ( individualInfo2.getFitness() != &fitnessDummy2 ){
		
			if ( *(individualInfo2.getFitness()) == fitnessDummy2 ){
			
				cout<<"The individualinfo returned fitness is equal to fitnessDummy2. "<<endl;
			}else{
				cerr<<"Error: The individualinfo returned fitness is not equal to fitnessDummy2."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The individualinfo returned a reference to fitnessDummy2 for it's fitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The individualinfo a nullpointer for it's fitness."<<endl;
		iReturn++;
	}
	//check the getOperatorName() methode from cIndividualInfo
	if ( individualInfo2.getOperatorName() == szOperationName2 ){
	
		cout<<"The individualinfo gives as the operationame of the individual a string equal to szOperationName2. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned operationame is not equal to szOperationName2."<<endl;
		iReturn++;
	}
	//check the getOperatorInfo() methode from cIndividualInfo
	if ( individualInfo2.getOperatorInfo() == szOperationInfo2 ){
	
		cout<<"The individualinfo gives as the operatioinfo of the individual a string equal to szOperationInfo2. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned operatioinfo is not equal to szOperationInfo2."<<endl;
		iReturn++;
	}
	//check the getOperatorIdentifier() methode from cIndividualInfo
	if ( individualInfo2.getOperatorIdentifier() == operationIdentifier2 ){
	
		cout<<"The individualinfo gives a operatioidentifier which is equal to operationIdentifier2. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned operatioidentifier is not equal to operationIdentifier2."<<endl;
		iReturn++;
	}
	//check the getCreationTime() methode from cIndividualInfo
	if ( individualInfo2.getCreationTime() == creationTime2 ){
	
		cout<<"The individualinfo gives the creationtime which is equal to creationTime2. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned creationtime is not equal to creationTime2."<<endl;
		iReturn++;
	}
	//check the getOperationCost() methode from cIndividualInfo
	if ( individualInfo2.getOperationCost() == dOperationCost2 ){
	
		cout<<"The individualinfo gives the creationcost which is equal to dOperationCost2. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned creationcost is not equal to dOperationCost2."<<endl;
		iReturn++;
	}
	//check the getFitnessOfBestAtCreationTime() methode from cIndividualInfo
	if ( individualInfo2.getFitnessOfBestAtCreationTime() != NULL ){
	
		if ( individualInfo2.getFitnessOfBestAtCreationTime() != &fitnessOfBestAtCreationTime2 ){
		
			if ( *(individualInfo2.getFitnessOfBestAtCreationTime()) == fitnessOfBestAtCreationTime2 ){
			
				cout<<"The individualinfo returned fitness of the best is equal to fitnessOfBestAtCreationTime2. "<<endl;
			}else{
				cerr<<"Error: The individualinfo returned fitness of the best is not equal to fitnessOfBestAtCreationTime2."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The individualinfo returned a reference to fitnessOfBestAtCreationTime2 for it's fitness of the best."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The individualinfo a nullpointer for it's fitness of the best."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copyconstructing simple cIndividualInfo"<<endl;
	
	cout<<"cIndividualInfo individualInfo1Copy( individualInfo1 ). "<<endl;
	cIndividualInfo individualInfo1Copy( individualInfo1 );
	
	//check the getIdentifier() methode from cIndividualInfo
	if ( individualInfo1Copy.getIdentifier() == individualInfo1Copy.getIdentifier() ){
	
		cout<<"The individualinfo gives back the same identifier with every method call. "<<endl;
	}else{
		cerr<<"Error: The individualinfo dosn't gives back the same identifier with every method call."<<endl;
		iReturn++;
	}
	if ( individualInfo1Copy.getIdentifier() == individualInfo1.getIdentifier() ){
	
		cout<<"The individualinfo gives back the same identifier as the original individualInfo1. "<<endl;
	}else{
		cerr<<"Error: The individualinfo dosn't gives back the same identifier as the original individualInfo1."<<endl;
		iReturn++;
	}
	//check the isLiving() methode from cIndividualInfo
	if ( individualInfo1Copy.isLiving() ){
	
		cout<<"The individualinfo says correctly the individual is living. "<<endl;
	}else{
		cerr<<"Error: The individualinfo says the individual is dead."<<endl;
		iReturn++;
	}
	//check the getIdentifiersOfParents() methode from cIndividualInfo
	if ( individualInfo1Copy.getIdentifiersOfParents() == liParents1 ){
	
		cout<<"The individualinfo gives as the parents of the individual a list equal to liParents1. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned parent list is not equal to liParents1."<<endl;
		iReturn++;
	}
	//check the getFitness() methode from cIndividualInfo
	if ( individualInfo1Copy.getFitness() != NULL ){
	
		if ( individualInfo1Copy.getFitness() != &fitnessDummy1 ){
		
			if ( *(individualInfo1Copy.getFitness()) == fitnessDummy1 ){
			
				cout<<"The individualinfo returned fitness is equal to fitnessDummy1. "<<endl;
			}else{
				cerr<<"Error: The individualinfo returned fitness is not equal to fitnessDummy1."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The individualinfo returned a reference to fitnessDummy1 for it's fitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The individualinfo a nullpointer for it's fitness."<<endl;
		iReturn++;
	}
	//check the getOperatorName() methode from cIndividualInfo
	if ( individualInfo1Copy.getOperatorName() == szOperationName1 ){
	
		cout<<"The individualinfo gives as the operationame of the individual a string equal to szOperationName1. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned operationame is not equal to szOperationName1."<<endl;
		iReturn++;
	}
	//check the getOperatorInfo() methode from cIndividualInfo
	if ( individualInfo1Copy.getOperatorInfo() == szOperationInfo1 ){
	
		cout<<"The individualinfo gives as the operatioinfo of the individual a string equal to szOperationInfo1. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned operatioinfo is not equal to szOperationInfo1."<<endl;
		iReturn++;
	}
	//check the getOperatorIdentifier() methode from cIndividualInfo
	if ( individualInfo1Copy.getOperatorIdentifier() == operationIdentifier1 ){
	
		cout<<"The individualinfo gives a operatioidentifier which is equal to operationIdentifier1. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned operatioidentifier is not equal to operationIdentifier1."<<endl;
		iReturn++;
	}
	//check the getCreationTime() methode from cIndividualInfo
	if ( individualInfo1Copy.getCreationTime() == creationTime1 ){
	
		cout<<"The individualinfo gives the creationtime which is equal to creationTime1. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned creationtime is not equal to creationTime1."<<endl;
		iReturn++;
	}
	//check the getOperationCost() methode from cIndividualInfo
	if ( individualInfo1Copy.getOperationCost() == dOperationCost1 ){
	
		cout<<"The individualinfo gives the creationcost which is equal to dOperationCost1. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned creationcost is not equal to dOperationCost1."<<endl;
		iReturn++;
	}
	//check the getFitnessOfBestAtCreationTime() methode from cIndividualInfo
	if ( individualInfo1Copy.getFitnessOfBestAtCreationTime() != NULL ){
	
		if ( individualInfo1Copy.getFitnessOfBestAtCreationTime() != &fitnessOfBestAtCreationTime1 ){
		
			if ( *(individualInfo1Copy.getFitnessOfBestAtCreationTime()) == fitnessOfBestAtCreationTime1 ){
			
				cout<<"The individualinfo returned fitness of the best is equal to fitnessOfBestAtCreationTime1. "<<endl;
			}else{
				cerr<<"Error: The individualinfo returned fitness of the best is not equal to fitnessOfBestAtCreationTime1."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The individualinfo returned a reference to fitnessOfBestAtCreationTime1 for it's fitness of the best."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The individualinfo a nullpointer for it's fitness of the best."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the method kill() of cIndividualInfo"<<endl;
	
	//check the isLiving() methode from cIndividualInfo
	cout<<"individualInfo2.isLiving()"<<endl;
	if ( individualInfo2.isLiving() ){
	
		cout<<"The individualinfo says correctly the individual is living. "<<endl;
	}else{
		cerr<<"Error: The individualinfo says the individual is dead."<<endl;
		iReturn++;
	}
	//check the kill() methode from cIndividualInfo
	cout<<"individualInfo2.kill()"<<endl;
	if ( individualInfo2.kill() ){
	
		cout<<"The individualinfo was correctly killed. "<<endl;
	}else{
		cerr<<"Error: The individualinfo wasn't killed."<<endl;
		iReturn++;
	}
	//check the isLiving() methode from cIndividualInfo
	cout<<"individualInfo2.isLiving()"<<endl;
	if ( ! individualInfo2.isLiving() ){
	
		cout<<"The individualinfo says correctly the individual is dead. "<<endl;
	}else{
		cerr<<"Error: The individualinfo says the individual is living."<<endl;
		iReturn++;
	}
	//check the kill() methode from cIndividualInfo
	cout<<"individualInfo2.kill()"<<endl;
	if ( ! individualInfo2.kill() ){
	
		cout<<"The individualinfo couldn't correctly be killed. "<<endl;
	}else{
		cerr<<"Error: The individualinfo was killed again."<<endl;
		iReturn++;
	}
	//check the isLiving() methode from cIndividualInfo
	cout<<"individualInfo2.isLiving()"<<endl;
	if ( ! individualInfo2.isLiving() ){
	
		cout<<"The individualinfo says correctly the individual is dead. "<<endl;
	}else{
		cerr<<"Error: The individualinfo says the individual is living."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the method kill() of cIndividualInfo wich is a copy"<<endl;
	
	//check the isLiving() methode from cIndividualInfo
	cout<<"individualInfo1Copy.isLiving()"<<endl;
	if ( individualInfo1Copy.isLiving() ){
	
		cout<<"The individualinfo says correctly the individual is living. "<<endl;
	}else{
		cerr<<"Error: The individualinfo says the individual is dead."<<endl;
		iReturn++;
	}
	//check the kill() methode from cIndividualInfo
	cout<<"individualInfo1Copy.kill()"<<endl;
	if ( individualInfo1Copy.kill() ){
	
		cout<<"The individualinfo was correctly killed. "<<endl;
	}else{
		cerr<<"Error: The individualinfo wasn't killed."<<endl;
		iReturn++;
	}
	//check the isLiving() methode from cIndividualInfo
	cout<<"individualInfo1Copy.isLiving()"<<endl;
	if ( ! individualInfo1Copy.isLiving() ){
	
		cout<<"The individualinfo says correctly the individual is dead. "<<endl;
	}else{
		cerr<<"Error: The individualinfo says the individual is living."<<endl;
		iReturn++;
	}
	//check the kill() methode from cIndividualInfo
	cout<<"individualInfo1Copy.kill()"<<endl;
	if ( ! individualInfo1Copy.kill() ){
	
		cout<<"The individualinfo couldn't correctly be killed. "<<endl;
	}else{
		cerr<<"Error: The individualinfo was killed again."<<endl;
		iReturn++;
	}
	//check the isLiving() methode from cIndividualInfo
	cout<<"individualInfo1Copy.isLiving()"<<endl;
	if ( ! individualInfo1Copy.isLiving() ){
	
		cout<<"The individualinfo says correctly the individual is dead. "<<endl;
	}else{
		cerr<<"Error: The individualinfo says the individual is living."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copyconstructing a dead cIndividualInfo"<<endl;
	
	cout<<"cIndividualInfo individualInfo2Copy( individualInfo2 ). "<<endl;
	cIndividualInfo individualInfo2Copy( individualInfo2 );
	
	//check the getIdentifier() methode from cIndividualInfo
	if ( individualInfo2Copy.getIdentifier() == individualInfo2Copy.getIdentifier() ){
	
		cout<<"The individualinfo gives back the same identifier with every method call. "<<endl;
	}else{
		cerr<<"Error: The individualinfo dosn't gives back the same identifier with every method call."<<endl;
		iReturn++;
	}
	if ( individualInfo2Copy.getIdentifier() == individualInfo2.getIdentifier() ){
	
		cout<<"The individualinfo gives back the same identifier as the original individualInfo2. "<<endl;
	}else{
		cerr<<"Error: The individualinfo dosn't gives back the same identifier as the original individualInfo2."<<endl;
		iReturn++;
	}
	//check the isLiving() methode from cIndividualInfo
	if ( ! individualInfo2Copy.isLiving() ){
	
		cout<<"The individualinfo says correctly the individual is dead. "<<endl;
	}else{
		cerr<<"Error: The individualinfo says the individual is living."<<endl;
		iReturn++;
	}
	//check the getIdentifiersOfParents() methode from cIndividualInfo
	if ( individualInfo2Copy.getIdentifiersOfParents() == liParents2 ){
	
		cout<<"The individualinfo gives as the parents of the individual a list equal to liParents2. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned parent list is not equal to liParents2."<<endl;
		iReturn++;
	}
	//check the getFitness() methode from cIndividualInfo
	if ( individualInfo2Copy.getFitness() != NULL ){
	
		if ( individualInfo2Copy.getFitness() != &fitnessDummy2 ){
		
			if ( *(individualInfo2Copy.getFitness()) == fitnessDummy2 ){
			
				cout<<"The individualinfo returned fitness is equal to fitnessDummy2. "<<endl;
			}else{
				cerr<<"Error: The individualinfo returned fitness is not equal to fitnessDummy2."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The individualinfo returned a reference to fitnessDummy2 for it's fitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The individualinfo a nullpointer for it's fitness."<<endl;
		iReturn++;
	}
	//check the getOperatorName() methode from cIndividualInfo
	if ( individualInfo2Copy.getOperatorName() == szOperationName2 ){
	
		cout<<"The individualinfo gives as the operationame of the individual a string equal to szOperationName2. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned operationame is not equal to szOperationName2."<<endl;
		iReturn++;
	}
	//check the getOperatorInfo() methode from cIndividualInfo
	if ( individualInfo2Copy.getOperatorInfo() == szOperationInfo2 ){
	
		cout<<"The individualinfo gives as the operatioinfo of the individual a string equal to szOperationInfo2. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned operatioinfo is not equal to szOperationInfo2."<<endl;
		iReturn++;
	}
	//check the getOperatorIdentifier() methode from cIndividualInfo
	if ( individualInfo2Copy.getOperatorIdentifier() == operationIdentifier2 ){
	
		cout<<"The individualinfo gives a operatioidentifier which is equal to operationIdentifier2. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned operatioidentifier is not equal to operationIdentifier2."<<endl;
		iReturn++;
	}
	//check the getCreationTime() methode from cIndividualInfo
	if ( individualInfo2Copy.getCreationTime() == creationTime2 ){
	
		cout<<"The individualinfo gives the creationtime which is equal to creationTime2. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned creationtime is not equal to creationTime2."<<endl;
		iReturn++;
	}
	//check the getOperationCost() methode from cIndividualInfo
	if ( individualInfo2Copy.getOperationCost() == dOperationCost2 ){
	
		cout<<"The individualinfo gives the creationcost which is equal to dOperationCost2. "<<endl;
	}else{
		cerr<<"Error: The individualinfo returned creationcost is not equal to dOperationCost2."<<endl;
		iReturn++;
	}
	//check the getFitnessOfBestAtCreationTime() methode from cIndividualInfo
	if ( individualInfo2Copy.getFitnessOfBestAtCreationTime() != NULL ){
	
		if ( individualInfo2Copy.getFitnessOfBestAtCreationTime() != &fitnessOfBestAtCreationTime2 ){
		
			if ( *(individualInfo2Copy.getFitnessOfBestAtCreationTime()) == fitnessOfBestAtCreationTime2 ){
			
				cout<<"The individualinfo returned fitness of the best is equal to fitnessOfBestAtCreationTime2. "<<endl;
			}else{
				cerr<<"Error: The individualinfo returned fitness of the best is not equal to fitnessOfBestAtCreationTime2."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The individualinfo returned a reference to fitnessOfBestAtCreationTime2 for it's fitness of the best."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The individualinfo a nullpointer for it's fitness of the best."<<endl;
		iReturn++;
	}


	return iReturn;
}




/**
 * This method tests the equal() method and the operator== of two given
 * cObjectIndividuals objects which are not equal.
 *
 * @param individualInfo1 the first individualinfo to compare
 * @param szNameIndividualInfo1 the name of the first individualinfo to compare
 * @param individualInfo2 the secound individualinfo to compare to
 * @param szNameIndividualInfo2 the name of the secound individualinfo to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoNotEqualIndividualInfo( const cIndividualInfo & individualInfo1, const string & szNameIndividualInfo1,
	const cIndividualInfo & individualInfo2, const string & szNameIndividualInfo2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( ! individualInfo1.equal( individualInfo2 ) ){
	
		cout<<"The "<<szNameIndividualInfo1<<" is not equal to "<<szNameIndividualInfo2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameIndividualInfo1<<" is equal to "<<
			szNameIndividualInfo2<<"."<<endl;
		iReturn++;
	}
	if ( ! (individualInfo1 == individualInfo2) ){
	
		cout<<"The "<<szNameIndividualInfo1<<" is not equal (operator==) to "<<
			szNameIndividualInfo2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameIndividualInfo1<<" is equal (operator==) to "<<
			szNameIndividualInfo2<<"."<<endl;
		iReturn++;
	}
	if ( individualInfo1 != individualInfo2 ){
	
		cout<<"The "<<szNameIndividualInfo1<<" is not equal (operator!=) to "<<
			szNameIndividualInfo2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameIndividualInfo1<<" is equal (operator!=) to "<<
			szNameIndividualInfo2<<"."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests the equal() method and the operator== of two given
 * cObjectIndividuals objects which are equal.
 *
 * @param individualInfo1 the first individualinfo to compare
 * @param szNameIndividualInfo1 the name of the first individualinfo to compare
 * @param individualInfo2 the secound individualinfo to compare to
 * @param szNameIndividualInfo2 the name of the secound individualinfo to compare
 * @param bIdentifiersEqual if true the identifiers of both individualinfo
 * 	will be equal, else not
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualIndividualInfo( const cIndividualInfo & individualInfo1, const string & szNameIndividualInfo1,
	const cIndividualInfo & individualInfo2, const string & szNameIndividualInfo2, bool bIdentifiersEqual=true ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( bIdentifiersEqual ){
		if ( individualInfo1.equal( individualInfo2 ) ){
		
			cout<<"The "<<szNameIndividualInfo1<<" is equal to "<<szNameIndividualInfo2<<". "<<endl;
		}else{
			cerr<<"Error: The "<<szNameIndividualInfo1<<" is not equal to "<<
				szNameIndividualInfo2<<"."<<endl;
			iReturn++;
		}
		if ( individualInfo1 == individualInfo2 ){
		
			cout<<"The "<<szNameIndividualInfo1<<" is equal (operator==) to "<<
				szNameIndividualInfo2<<". "<<endl;
		}else{
			cerr<<"Error: The "<<szNameIndividualInfo1<<" is not equal (operator==) to "<<
				szNameIndividualInfo2<<"."<<endl;
			iReturn++;
		}
		if ( ! (individualInfo1 != individualInfo2) ){
		
			cout<<"The "<<szNameIndividualInfo1<<" is equal (operator!=) to "<<
				szNameIndividualInfo2<<". "<<endl;
		}else{
			cerr<<"Error: The "<<szNameIndividualInfo1<<" is not equal (operator!=) to "<<
				szNameIndividualInfo2<<"."<<endl;
			iReturn++;
		}
	}else{
		if ( individualInfo1.equal( individualInfo2, false ) ){
		
			cout<<"The "<<szNameIndividualInfo1<<" is equal to "<<szNameIndividualInfo2<<" except the identifiers. "<<endl;
		}else{
			cerr<<"Error: The "<<szNameIndividualInfo1<<" is not equal, except the identifiers, to "<<
				szNameIndividualInfo2<<"."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoNotEqualIndividualInfo( individualInfo1, szNameIndividualInfo1,
			individualInfo2, szNameIndividualInfo2 );
	}

	return iReturn;
}



/**
 * This method tests the constructor of the cIndividualInfo class.
 *
 * methods tested:
 * 	- bool equal( const cIndividualInfo &idIndividual, bool checkIdentifiers=true ) const;
 * 	- bool operator==( const cIndividualInfo &idIndividual ) const;
 * 	- bool operator!=( const cIndividualInfo &idIndividual ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testComparison( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing comparison of cIndividualInfo Objects"<<endl;

	const cFibObjectFitnessBasic fitnessDummy1( 1.0, 0, 0 );
	const list<cIndividualIdentifier> liParents1;
	const cOperationIdentifier operationIdentifier1( 0 );
	const time_t creationTime1 = time_t( NULL );
	const double dOperationCost1 = 1.0;
	const cFibObjectFitnessBasic fitnessOfBestAtCreationTime1( 1.0, 0, 1 );
	cout<<"const cIndividualInfo individualInfo1( 0, liParents1, fitnessDummy1,"<<
		"\"operation1\", \"opInfo1\", operationIdentifier1,"<<
		"creationTime1, dOperationCost1, & fitnessOfBestAtCreationTime1). "<<endl;
	const cIndividualInfo individualInfo1( 0, liParents1, fitnessDummy1,
		"operation1", "opInfo1", operationIdentifier1,
		creationTime1, dOperationCost1, & fitnessOfBestAtCreationTime1);
	
	cout<<"const cIndividualInfo individualInfo1Copy( individualInfo1 ); "<<endl;
	const cIndividualInfo individualInfo1Copy( individualInfo1 );

	cout<<"const cIndividualInfo individualInfo2( 0, liParents1, fitnessDummy1,"<<
		"\"operation1\", \"opInfo1\", operationIdentifier1,"<<
		"creationTime1, dOperationCost1, &fitnessOfBestAtCreationTime1). "<<endl;
	const cIndividualInfo individualInfo2( 0, liParents1, fitnessDummy1,
		"operation1", "opInfo1", operationIdentifier1,
		creationTime1, dOperationCost1, &fitnessOfBestAtCreationTime1);
	
	cout<<"const cIndividualInfo individualInfo3( 1, liParents1, fitnessDummy1,"<<
		"\"operation1\", \"opInfo1\", operationIdentifier1,"<<
		"creationTime1, dOperationCost1, &fitnessOfBestAtCreationTime1). "<<endl;
	const cIndividualInfo individualInfo3( 1, liParents1, fitnessDummy1,
		"operation1", "opInfo1", operationIdentifier1,
		creationTime1, dOperationCost1, &fitnessOfBestAtCreationTime1);

	list<cIndividualIdentifier> liParents2;
	liParents2.push_back( cIndividualIdentifier( 2 ) );
	cout<<"const cIndividualInfo individualInfo4( 0, liParents2, fitnessDummy1,"<<
		"\"operation1\", \"opInfo1\", operationIdentifier1,"<<
		"creationTime1, dOperationCost1, &fitnessOfBestAtCreationTime1). "<<endl;
	const cIndividualInfo individualInfo4( 0, liParents2, fitnessDummy1,
		"operation1", "opInfo1", operationIdentifier1,
		creationTime1, dOperationCost1, &fitnessOfBestAtCreationTime1);

	const cFibObjectFitnessBasic fitnessDummy2( 2.0, 2, 0 );
	cout<<"const cIndividualInfo individualInfo5( 0, liParents1, fitnessDummy2,"<<
		"\"operation1\", \"opInfo1\", operationIdentifier1,"<<
		"creationTime1, dOperationCost1, &fitnessOfBestAtCreationTime1). "<<endl;
	const cIndividualInfo individualInfo5( 0, liParents1, fitnessDummy2,
		"operation1", "opInfo1", operationIdentifier1,
		creationTime1, dOperationCost1, &fitnessOfBestAtCreationTime1);

	cout<<"const cIndividualInfo individualInfo6( 0, liParents1, fitnessDummy1,"<<
		"\"operation2\", \"opInfo1\", operationIdentifier1,"<<
		"creationTime1, dOperationCost1, &fitnessOfBestAtCreationTime1). "<<endl;
	const cIndividualInfo individualInfo6( 0, liParents1, fitnessDummy1,
		"operation2", "opInfo1", operationIdentifier1,
		creationTime1, dOperationCost1, &fitnessOfBestAtCreationTime1);
	
	cout<<"const cIndividualInfo individualInfo7( 0, liParents1, fitnessDummy1,"<<
		"\"operation1\", \"opInfo2\", operationIdentifier1,"<<
		"creationTime1, dOperationCost1, &fitnessOfBestAtCreationTime1). "<<endl;
	const cIndividualInfo individualInfo7( 0, liParents1, fitnessDummy1,
		"operation1", "opInfo2", operationIdentifier1,
		creationTime1, dOperationCost1, &fitnessOfBestAtCreationTime1);
	
	const cOperationIdentifier operationIdentifier2( 2 );
	cout<<"const cIndividualInfo individualInfo8( 0, liParents1, fitnessDummy1,"<<
		"\"operation1\", \"opInfo1\", operationIdentifier2,"<<
		"creationTime1, dOperationCost1, &fitnessOfBestAtCreationTime1). "<<endl;
	const cIndividualInfo individualInfo8( 0, liParents1, fitnessDummy1,
		"operation1", "opInfo1", operationIdentifier2,
		creationTime1, dOperationCost1, &fitnessOfBestAtCreationTime1);
	
	cout<<"const cIndividualInfo individualInfo9( 0, liParents1, fitnessDummy1,"<<
		"\"operation1\", \"opInfo1\", operationIdentifier1,"<<
		"5, dOperationCost1, &fitnessOfBestAtCreationTime1). "<<endl;
	const cIndividualInfo individualInfo9( 0, liParents1, fitnessDummy1,
		"operation1", "opInfo1", operationIdentifier1,
		5, dOperationCost1, &fitnessOfBestAtCreationTime1);
	
	const cFibObjectFitnessBasic fitnessOfBestAtCreationTime2( 2.0, 2, 2 );
	cout<<"const cIndividualInfo individualInfo10( 0, liParents1, fitnessDummy1,"<<
		"\"operation1\", \"opInfo1\", operationIdentifier1,"<<
		"creationTime1, dOperationCost1, &fitnessOfBestAtCreationTime2). "<<endl;
	const cIndividualInfo individualInfo10( 0, liParents1, fitnessDummy1,
		"operation1", "opInfo1", operationIdentifier1,
		creationTime1, dOperationCost1, &fitnessOfBestAtCreationTime2);
	
	cout<<"cIndividualInfo individualInfo11( individualInfo1 ); "<<endl;
	cIndividualInfo individualInfo11( individualInfo1 );
	cout<<"individualInfo11.kill(); "<<endl;
	individualInfo11.kill();

	cout<<"const cIndividualInfo individualInfo12( 0, liParents1, fitnessDummy1,"<<
		"\"operation1\", \"opInfo1\", operationIdentifier1,"<<
		"creationTime1, dOperationCost1, &fitnessOfBestAtCreationTime2). "<<endl;
	const cIndividualInfo individualInfo12( 0, liParents1, fitnessDummy1,
		"operation1", "opInfo1", operationIdentifier1,
		creationTime1, 17.0, &fitnessOfBestAtCreationTime1 );
	


	//compare with individualInfo1
	const cIndividualInfo * actualIndividual = &individualInfo1;
	string szActualIndividualName = "individualInfo1";
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1, "individualInfo1" );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1Copy, "individualInfo1Copy" );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo2, "individualInfo2", false );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo3, "individualInfo3", false );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo4, "individualInfo4", false );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo5, "individualInfo5" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo6, "individualInfo6" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo7, "individualInfo7" );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo8, "individualInfo8", false );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo9, "individualInfo9" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo10, "individualInfo10" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo11, "individualInfo11" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo12, "individualInfo12" );

	//compare with individualInfo1Copy
	actualIndividual = &individualInfo1Copy;
	szActualIndividualName = "individualInfo1Copy";
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1, "individualInfo1" );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1Copy, "individualInfo1Copy" );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo2, "individualInfo2", false );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo3, "individualInfo3", false );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo4, "individualInfo4", false );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo5, "individualInfo5" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo6, "individualInfo6" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo7, "individualInfo7" );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo8, "individualInfo8", false );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo9, "individualInfo9" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo10, "individualInfo10" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo11, "individualInfo11" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo12, "individualInfo12" );

	//compare with individualInfo2
	actualIndividual = &individualInfo2;
	szActualIndividualName = "individualInfo2";
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1, "individualInfo1", false );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1Copy, "individualInfo1Copy", false );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo2, "individualInfo2" );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo3, "individualInfo3", false );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo4, "individualInfo4", false );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo5, "individualInfo5" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo6, "individualInfo6" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo7, "individualInfo7" );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo8, "individualInfo8", false );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo9, "individualInfo9" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo10, "individualInfo10" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo11, "individualInfo11" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo12, "individualInfo12" );

	//compare with individualInfo3
	actualIndividual = &individualInfo3;
	szActualIndividualName = "individualInfo3";
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1, "individualInfo1", false );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1Copy, "individualInfo1Copy", false );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo2, "individualInfo2", false );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo3, "individualInfo3" );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo4, "individualInfo4", false );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo5, "individualInfo5" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo6, "individualInfo6" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo7, "individualInfo7" );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo8, "individualInfo8", false );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo9, "individualInfo9" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo10, "individualInfo10" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo11, "individualInfo11" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo12, "individualInfo12" );

	//compare with individualInfo4
	actualIndividual = &individualInfo4;
	szActualIndividualName = "individualInfo4";
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1, "individualInfo1", false );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1Copy, "individualInfo1Copy", false );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo2, "individualInfo2", false );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo3, "individualInfo3", false );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo4, "individualInfo4"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo5, "individualInfo5" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo6, "individualInfo6" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo7, "individualInfo7" );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo8, "individualInfo8", false );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo9, "individualInfo9" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo10, "individualInfo10" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo11, "individualInfo11" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo12, "individualInfo12" );

	//compare with individualInfo5
	actualIndividual = &individualInfo5;
	szActualIndividualName = "individualInfo5";
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1, "individualInfo1" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1Copy, "individualInfo1Copy" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo2, "individualInfo2"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo3, "individualInfo3"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo4, "individualInfo4"  );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo5, "individualInfo5" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo6, "individualInfo6" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo7, "individualInfo7" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo8, "individualInfo8"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo9, "individualInfo9" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo10, "individualInfo10" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo11, "individualInfo11" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo12, "individualInfo12" );

	//compare with individualInfo6
	actualIndividual = &individualInfo6;
	szActualIndividualName = "individualInfo6";
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1, "individualInfo1" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1Copy, "individualInfo1Copy" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo2, "individualInfo2"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo3, "individualInfo3"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo4, "individualInfo4"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo5, "individualInfo5" );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo6, "individualInfo6" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo7, "individualInfo7" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo8, "individualInfo8"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo9, "individualInfo9" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo10, "individualInfo10" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo11, "individualInfo11" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo12, "individualInfo12" );

	//compare with individualInfo7
	actualIndividual = &individualInfo7;
	szActualIndividualName = "individualInfo7";
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1, "individualInfo1" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1Copy, "individualInfo1Copy" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo2, "individualInfo2"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo3, "individualInfo3"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo4, "individualInfo4"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo5, "individualInfo5" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo6, "individualInfo6" );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo7, "individualInfo7" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo8, "individualInfo8"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo9, "individualInfo9" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo10, "individualInfo10" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo11, "individualInfo11" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo12, "individualInfo12" );

	//compare with individualInfo8
	actualIndividual = &individualInfo8;
	szActualIndividualName = "individualInfo8";
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1, "individualInfo1", false );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1Copy, "individualInfo1Copy", false );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo2, "individualInfo2", false );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo3, "individualInfo3", false );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo4, "individualInfo4", false );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo5, "individualInfo5" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo6, "individualInfo6" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo7, "individualInfo7" );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo8, "individualInfo8" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo9, "individualInfo9" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo10, "individualInfo10" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo11, "individualInfo11" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo12, "individualInfo12" );

	//compare with individualInfo9
	actualIndividual = &individualInfo9;
	szActualIndividualName = "individualInfo9";
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1, "individualInfo1" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1Copy, "individualInfo1Copy" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo2, "individualInfo2"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo3, "individualInfo3"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo4, "individualInfo4"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo5, "individualInfo5" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo6, "individualInfo6" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo7, "individualInfo7" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo8, "individualInfo8"  );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo9, "individualInfo9" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo10, "individualInfo10" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo11, "individualInfo11" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo12, "individualInfo12" );

	//compare with individualInfo10
	actualIndividual = &individualInfo10;
	szActualIndividualName = "individualInfo10";
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1, "individualInfo1" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1Copy, "individualInfo1Copy" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo2, "individualInfo2"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo3, "individualInfo3"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo4, "individualInfo4"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo5, "individualInfo5" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo6, "individualInfo6" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo7, "individualInfo7" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo8, "individualInfo8"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo9, "individualInfo9" );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo10, "individualInfo10" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo11, "individualInfo11" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo12, "individualInfo12" );

	//compare with individualInfo11
	actualIndividual = &individualInfo11;
	szActualIndividualName = "individualInfo11";
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1, "individualInfo1" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1Copy, "individualInfo1Copy" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo2, "individualInfo2"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo3, "individualInfo3"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo4, "individualInfo4"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo5, "individualInfo5" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo6, "individualInfo6" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo7, "individualInfo7" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo8, "individualInfo8"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo9, "individualInfo9" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo10, "individualInfo10" );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo11, "individualInfo11" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo12, "individualInfo12" );

	//compare with individualInfo12
	actualIndividual = &individualInfo12;
	szActualIndividualName = "individualInfo12";
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1, "individualInfo1" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo1Copy, "individualInfo1Copy" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo2, "individualInfo2"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo3, "individualInfo3"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo4, "individualInfo4"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo5, "individualInfo5" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo6, "individualInfo6" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo7, "individualInfo7" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo8, "individualInfo8"  );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo9, "individualInfo9" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo10, "individualInfo10" );
	iReturn += testCompareTwoNotEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo11, "individualInfo11" );
	iReturn += testCompareTwoEqualIndividualInfo( *actualIndividual, szActualIndividualName, individualInfo12, "individualInfo12" );


	return iReturn;
}








