/**
 * @file tInitFibEnviroment
 * file name: tInitFibEnviroment.cpp
 * @author Betti Oesterholz
 * @date 15.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cInitFibEnviroment.
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
 * This file contains the test for the class cInitFibEnviroment.
 *
 *
 *  What's tested of class cInitFibEnviroment:
 * 	- cInitFibEnviroment( const cRoot & pFibOriginal );
 * 	- cInitFibEnviroment( const cInitFibEnviroment & initFibEnviroment );
 * 	- ~cInitFibEnviroment();
 * 	- bool initEnviroment() const;
 * 	- cInitFibEnviroment * clone() const;
 * 	- string getClassName() const;
 *
 */
/*
History:
14.03.2010  Oesterholz  created
16.09.2010  Oesterholz  getClassName() added
*/

#include "version.h"

#include "cInitFibEnviroment.h"

#include "cEnviroment.h"
#include "cFibObjectFitnessBasic.h"
#include "cFibObjectFitnessBasicAlgorithm.h"
#include "cEndConditionCheck.h"
#include "cResourceCheck.h"
#include "cFibIndividual.h"
#include "cInitOperator.h"

#include "cRoot.h"
#include "cPoint.h"

#include <utility>
#include <iostream>


using namespace enviroment::fib;
using namespace enviroment;
using namespace std;


int testInitFibEnviroment( unsigned long &ulTestphase );

/**
 * Counter for how often an init was performed.
 */
unsigned long ulInitCalled = 0;


int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	

	cout<<endl<<"Running Test for cInitFibEnviroment methods"<<endl;
	cout<<      "==========================================="<<endl;

	iReturn += testInitFibEnviroment( ulTestphase );


	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}


namespace enviroment{
	
	class cEndConditionCheckTest: public cEndConditionCheck{
	public:
	
		/**
		 * @return true
		 */
		virtual bool endConditionCheck(){
			return true;
		}
		/**
		 * This method clones this object.
		 *
		 * @return a clone of this object
		 */
		virtual cEndConditionCheckTest * clone() const{
			return new cEndConditionCheckTest();
		}
	
	};//end class cEndConditionCheckTest

};//namespace enviroment


/**
 * This function tests cInitFibEnviroment class.
 *
 * methods tested:
 * 	- cInitFibEnviroment( const cRoot & pFibOriginal );
 * 	- cInitFibEnviroment( const cInitFibEnviroment & initFibEnviroment );
 * 	- ~cInitFibEnviroment();
 * 	- bool initEnviroment() const;
 * 	- cInitFibEnviroment * clone() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testInitFibEnviroment( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cEnviroment with a normal init"<<endl;
	
	cVectorPosition vecPosition( 2 );
	vecPosition.setValue( 1, 1 );
	cPoint point1( &vecPosition );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cRoot rootInit( &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cRoot rootInit( NULL, NULL, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	
	cout<<"cInitFibEnviroment initEnviroment( rootInit ); "<<endl;
	cInitFibEnviroment initEnviroment( rootInit );

	if ( initEnviroment.getClassName() == "cInitFibEnviroment" ){
	
		cout<<"The classname is correctly \"cInitFibEnviroment\" . "<<endl;
	}else{
		cerr<<"Error: The classname is \""<<initEnviroment.getClassName()<<
			"\", but should be correctly \"cInitFibEnviroment\"."<<endl;
		iReturn++;
	}

	vecPosition.setValue( 1, 10 );
	cPoint point2( &vecPosition );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cRoot rootOrg( &point2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cRoot rootOrg( NULL, NULL, &point2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	rootOrg.setNumberOfInputVariables( 1 );

	cout<<"cFibObjectFitnessBasicAlgorithm fibObjectAlgorithmBasic( &rootOrg, 123, 2.0, 3.0 );"<<endl;
	cFibObjectFitnessBasicAlgorithm fibObjectAlgorithmBasic( &rootOrg, 123, 2.0, 3.0 );
	
	//the endcondition stops the enviroment instantly
	cEndConditionCheckTest endConditionCheckTest;
	
	//set the parameter of the enviroment
	cout<<"bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic, &endConditionCheckTest );"<<endl;
	bool bParameterSet = cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic, &endConditionCheckTest );

	if ( bParameterSet ){
	
		cout<<"The parameter could be correctly set. "<<endl;
	}else{
		cerr<<"Error: The parameter couldn't be set."<<endl;
		iReturn++;
	}
	if ( initEnviroment.getClassName() == "cInitFibEnviroment" ){
	
		cout<<"The classname is correctly \"cInitFibEnviroment\" . "<<endl;
	}else{
		cerr<<"Error: The classname is \""<<initEnviroment.getClassName()<<
			"\", but should be correctly \"cInitFibEnviroment\"."<<endl;
		iReturn++;
	}

	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	cEnviroment * pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment != NULL ){
	
		cout<<"An instance of the enviroment could be correctly created. "<<endl;
	}else{
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
	}
	//run the enviroment
	cout<<"pEnviroment->run(); "<<endl;
	pEnviroment->run();
	ulInitCalled++;
	
	//check the isRunning() methode from cEnviroment gives back false
	if ( ! (pEnviroment->isRunning()) ){
	
		cout<<"The enviroment is correctly not running . "<<endl;
	}else{
		cerr<<"Error: The enviroment is running ."<<endl;
		iReturn++;
	}

	//check if one individual, the original individual was inserted
	//check getNumberOfIndividuals( iLive = 1 )
	unsigned long ulNumberOfIndividuals = pEnviroment->getNumberOfIndividuals( 1 );
	if ( 1 <= ulNumberOfIndividuals ){
		
		cout<<"The number of living individuals is correctly greater 1 . "<<endl;
		
		//check the individuals if they contain the original individual
		bool bInitIndividualFound = false;
		for ( unsigned int uiActualIndividual = 1;
				uiActualIndividual <= ulNumberOfIndividuals; uiActualIndividual++ ){
			
			cout<<"pIndividual = pEnviroment->getBestIndividual( "<<uiActualIndividual<<" ); "<<endl;
			cIndividual * pIndividual = pEnviroment->getBestIndividual( uiActualIndividual );
			if ( pIndividual != NULL ){
				
				if ( (((cFibIndividual*)pIndividual)->getFibObject())->equal( rootInit ) ){
					
					bInitIndividualFound = true;
					delete pIndividual;
					break;
				}
				delete pIndividual;
			}else{
				cerr<<"Error: Couldn't get individual from the enviroment."<<endl;
				iReturn++;
			}
		}
		if ( bInitIndividualFound ){
			
			cout<<"An evalued individual is correctly equal to rootInit. "<<endl;
		}else{
			cerr<<"Error: No evalued individual is equal to rootInit."<<endl;
			iReturn++;
		}

	}else{
		cerr<<"Error: The number of living individuals is "<<
			pEnviroment->getNumberOfIndividuals( 1 ) <<", but should be greater 1 ."<<endl;
		iReturn++;
	}
	
	//if an init operation exists: check if one operation was called (the init operation)
	if ( cInitOperator::ulInitOperatorCalled == ulInitCalled ){
	
		cout<<"The init operator was correctly called "<<ulInitCalled<<" times . "<<endl;
	}else{
		cerr<<"Error: The init operator was called "<< cInitOperator::ulInitOperatorCalled <<
			", but should be called "<< ulInitCalled <<" times . "<<endl;
		iReturn++;
	}
	
	//destroy the enviroment
	delete pEnviroment;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cEnviroment with a cloned init object"<<endl;
	
	cout<<"cInitEnviroment * pInitEnviromentClone = initEnviroment.clone(); "<<endl;
	cInitEnviroment * pInitEnviromentClone = initEnviroment.clone();

	//set the parameter of the enviroment
	cout<<"bParameterSet = cEnviroment::setParameter( pInitEnviromentClone, &fibObjectAlgorithmBasic, &endConditionCheckTest );"<<endl;
	bParameterSet = cEnviroment::setParameter( pInitEnviromentClone, &fibObjectAlgorithmBasic, &endConditionCheckTest );

	if ( bParameterSet ){
	
		cout<<"The parameter could be correctly set. "<<endl;
	}else{
		cerr<<"Error: The parameter couldn't be set."<<endl;
		iReturn++;
	}
	if ( pInitEnviromentClone->getClassName() == "cInitFibEnviroment" ){
	
		cout<<"The classname is correctly \"cInitFibEnviroment\" . "<<endl;
	}else{
		cerr<<"Error: The classname is \""<<pInitEnviromentClone->getClassName()<<
			"\", but should be correctly \"cInitFibEnviroment\"."<<endl;
		iReturn++;
	}

	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment != NULL ){
	
		cout<<"An instance of the enviroment could be correctly created. "<<endl;
	}else{
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
	}
	//run the enviroment
	cout<<"pEnviroment->run(); "<<endl;
	pEnviroment->run();
	ulInitCalled++;
	
	//check the isRunning() methode from cEnviroment gives back false
	if ( ! (pEnviroment->isRunning()) ){
	
		cout<<"The enviroment is correctly not running . "<<endl;
	}else{
		cerr<<"Error: The enviroment is running ."<<endl;
		iReturn++;
	}

	//check if one individual, the original individual was inserted
	//check getNumberOfIndividuals( iLive = 1 )
	ulNumberOfIndividuals = pEnviroment->getNumberOfIndividuals( 1 );
	if ( 1 <= ulNumberOfIndividuals ){
		
		cout<<"The number of living individuals is correctly greater 1 . "<<endl;
		
		//check the individuals if they contain the original individual
		bool bInitIndividualFound = false;
		for ( unsigned int uiActualIndividual = 1;
				uiActualIndividual <= ulNumberOfIndividuals; uiActualIndividual++ ){
			
			cout<<"pIndividual = pEnviroment->getBestIndividual( "<<uiActualIndividual<<" ); "<<endl;
			cIndividual * pIndividual = pEnviroment->getBestIndividual( uiActualIndividual );
			if ( pIndividual != NULL ){
				
				if ( (((cFibIndividual*)pIndividual)->getFibObject())->equal( rootInit ) ){
					
					bInitIndividualFound = true;
					delete pIndividual;
					break;
				}
				delete pIndividual;
			}else{
				cerr<<"Error: Couldn't get individual from the enviroment."<<endl;
				iReturn++;
			}
		}
		if ( bInitIndividualFound ){
			
			cout<<"An evalued individual is correctly equal to rootInit. "<<endl;
		}else{
			cerr<<"Error: No evalued individual is equal to rootInit."<<endl;
			iReturn++;
		}

	}else{
		cerr<<"Error: The number of living individuals is "<<
			pEnviroment->getNumberOfIndividuals( 1 ) <<", but should be greater 1 ."<<endl;
		iReturn++;
	}
	
	//if an init operation exists: check if one operation was called (the init operation)
	if ( cInitOperator::ulInitOperatorCalled == ulInitCalled ){
	
		cout<<"The init operator was correctly called "<<ulInitCalled<<" times . "<<endl;
	}else{
		cerr<<"Error: The init operator was called "<< cInitOperator::ulInitOperatorCalled <<
			", but should be called "<< ulInitCalled <<" times . "<<endl;
		iReturn++;
	}
	//destroy the enviroment
	delete pEnviroment;
	delete pInitEnviromentClone;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cEnviroment with a copied init object"<<endl;
	
	cout<<"cInitFibEnviroment initEnviromentCopy( initEnviroment ); "<<endl;
	cInitFibEnviroment initEnviromentCopy( initEnviroment );
	
	if ( initEnviromentCopy.getClassName() == "cInitFibEnviroment" ){
	
		cout<<"The classname is correctly \"cInitFibEnviroment\" . "<<endl;
	}else{
		cerr<<"Error: The classname is \""<<initEnviromentCopy.getClassName()<<
			"\", but should be correctly \"cInitFibEnviroment\"."<<endl;
		iReturn++;
	}

	//set the parameter of the enviroment
	cout<<"bParameterSet = cEnviroment::setParameter( &initEnviromentCopy, &fibObjectAlgorithmBasic, &endConditionCheckTest );"<<endl;
	bParameterSet = cEnviroment::setParameter( &initEnviromentCopy, &fibObjectAlgorithmBasic, &endConditionCheckTest );

	if ( bParameterSet ){
	
		cout<<"The parameter could be correctly set. "<<endl;
	}else{
		cerr<<"Error: The parameter couldn't be set."<<endl;
		iReturn++;
	}

	//check the getInstance() methode from cEnviroment
	cout<<"pEnviroment = cEnviroment::getInstance(); "<<endl;
	pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment != NULL ){
	
		cout<<"An instance of the enviroment could be correctly created. "<<endl;
	}else{
		cerr<<"Error: An instance of the enviroment couldn't be created."<<endl;
		iReturn++;
	}
	//run the enviroment
	cout<<"pEnviroment->run(); "<<endl;
	pEnviroment->run();
	ulInitCalled++;
	
	//check the isRunning() methode from cEnviroment gives back false
	if ( ! (pEnviroment->isRunning()) ){
	
		cout<<"The enviroment is correctly not running . "<<endl;
	}else{
		cerr<<"Error: The enviroment is running ."<<endl;
		iReturn++;
	}

	//check if one individual, the original individual was inserted
	//check getNumberOfIndividuals( iLive = 1 )
	ulNumberOfIndividuals = pEnviroment->getNumberOfIndividuals( 1 );
	if ( 1 <= ulNumberOfIndividuals ){
		
		cout<<"The number of living individuals is correctly greater 1 . "<<endl;
		
		//check the individuals if they contain the original individual
		bool bInitIndividualFound = false;
		for ( unsigned int uiActualIndividual = 1;
				uiActualIndividual <= ulNumberOfIndividuals; uiActualIndividual++ ){
			
			cout<<"pIndividual = pEnviroment->getBestIndividual( "<<uiActualIndividual<<" ); "<<endl;
			cIndividual * pIndividual = pEnviroment->getBestIndividual( uiActualIndividual );
			if ( pIndividual != NULL ){
				
				if ( (((cFibIndividual*)pIndividual)->getFibObject())->equal( rootInit ) ){
					
					bInitIndividualFound = true;
					delete pIndividual;
					break;
				}
				delete pIndividual;
			}else{
				cerr<<"Error: Couldn't get individual from the enviroment."<<endl;
				iReturn++;
			}
		}
		if ( bInitIndividualFound ){
			
			cout<<"An evalued individual is correctly equal to rootInit. "<<endl;
		}else{
			cerr<<"Error: No evalued individual is equal to rootInit."<<endl;
			iReturn++;
		}

	}else{
		cerr<<"Error: The number of living individuals is "<<
			pEnviroment->getNumberOfIndividuals( 1 ) <<", but should be greater 1 ."<<endl;
		iReturn++;
	}
	
	//if an init operation exists: check if one operation was called (the init operation)
	if ( cInitOperator::ulInitOperatorCalled == ulInitCalled ){
	
		cout<<"The init operator was correctly called "<<ulInitCalled<<" times . "<<endl;
	}else{
		cerr<<"Error: The init operator was called "<< cInitOperator::ulInitOperatorCalled <<
			", but should be called "<< ulInitCalled <<" times . "<<endl;
		iReturn++;
	}
	//destroy the enviroment
	delete pEnviroment;
	
	return iReturn;
}








