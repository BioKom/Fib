/**
 * @file tFibObjectFitnessBasicAlgorithm
 * file name: tFibObjectFitnessBasicAlgorithm.cpp
 * @author Betti Oesterholz
 * @date 06.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cFibObjectFitnessBasicAlgorithm.
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
 * This file contains the test for the class cFibObjectFitnessBasicAlgorithm.
 *
 *
 *
 *  What's tested of class cFibObjectFitnessBasicAlgorithm:
 * 	- cFibObjectFitnessBasicAlgorithm();
 * 	- cFibObjectFitnessBasicAlgorithm( cFibIndividual * pInOriginalIndividual, double dInWeightDistanceToOriginal=1.0, double dInWeightSize=1.0, double dInWeightEvaluationTime=1.0 );
 * 	- cFibObjectFitnessBasicAlgorithm( cFibElement * pOriginalFibElement, double dInWeightDistanceToOriginal=1.0, double dInWeightSize=1.0, double dInWeightEvaluationTime=1.0 );
 * 	- cFibObjectFitnessBasicAlgorithm( const cFibObjectFitnessBasicAlgorithm & objectFitnessAlgorithm );
 * 	- cFibObjectFitnessBasicAlgorithm * clone() const;
 * 	- string getClassName() const;
 * 	- cObjectFitness * evalueFitness( const cIndividual & individual ) const;
 * 	- cFibObjectFitness * evalueFitness( const cFibIndividual & individual ) const;
 * 	- cFibObjectFitness * evalueFitness( const cFibElement * fibObject ) const;
 * 	- double evalueDistance( const cFibElement *fibElement, const cFibElement *fibElementArea=NULL  ) const;
 * 	- double evalueDistance( list< pair< cVectorPosition, list< cVectorProperty > > > & liPointWithProperties ) const;
 * 	- double evalueDistanceInArea( list< pair< cVectorPosition, list< cVectorProperty > > > & liPointWithProperties, list< pair< cVectorPosition, list< cVectorProperty > > > & liPointWithPropertiesOfArea ) const;
 * 	- bool setOriginalIndividual( cIndividual  * pInOriginalIndividual );
 * 	- bool setOriginalIndividual( cFibIndividual  * pInOriginalIndividual );
 * 	- bool setOriginalFibObject( cFibElement  * pInOriginalFibObject );
 * 	- cFibIndividual * getOriginalIndividual();
 * 	- cFibElement * getOriginalFibObject();
 * 	- cRoot * getOriginalIndividualRoot();
 * 	- const cFibObjectFitnessBasic * getBestFitness() const;
 * 	- const cFibObjectFitnessBasic * getWorstCaseFitness() const;
 * 	- double getWeightDistanceToOriginal() const;
 * 	- double getWeightSize() const;
 * 	- double getWeightEvaluationTime() const;
 *
 */
/*
History:
06.03.2010  Oesterholz  created
21.04.2010  Oesterholz  evalueObject() methods changed: not a function but
	an object is given to evalue the data
21.01.2011  Oesterholz  deleting original Fib object when loaded incorrectly
*/

#include "version.h"

#include "cFibObjectFitnessBasicAlgorithm.h"
#include "cFibIndividual.h"
#include "cIndividualIdentifier.h"

#include "cRoot.h"
#include "cPoint.h"
#include "cEvaluePositionList.h"

#include "cFolder.h"

#include <utility>
#include <iostream>
#include <fstream>
#include <ostream>
#include <ctime>
#include <cmath>


using namespace fib;
using namespace enviroment;
using namespace enviroment::fib;
using namespace std;

int testCostructor( unsigned long &ulTestphase );
int testOriginal( unsigned long &ulTestphase );
int testEvalue( unsigned long &ulTestphase );

list< string > loadTestFolderList( const string szFilePath );
list< string > loadTestFileList( const string szTestFolderName );


#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif

#ifndef DIR_TESTOBJECTS
	#define DIR_TESTOBJECTS "testObjects/"
#endif
#ifndef FILE_TESTOBJECTS
	#define FILE_TESTOBJECTS "testWithEvalueFitness.txt"
#endif

const char * pDirTestObjects = DIR_TESTOBJECTS;


int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	srand( time( NULL ) );
	
	if ( argc >= 2 ){
		//one parameter given; get parameter max size
		pDirTestObjects = argv[1];
	}

	cout<<endl<<"Running Test for cFibObjectFitnessBasicAlgorithm methods"<<endl;
	cout<<      "=========================================================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testOriginal( ulTestphase );
	iReturn += testEvalue( ulTestphase );

	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}


/**
 * This method tests the constructors of the cFibObjectFitnessBasicAlgorithm class.
 *
 * methods tested:
 * 	- cFibObjectFitnessBasicAlgorithm();
 * 	- cFibObjectFitnessBasicAlgorithm( cFibIndividual * pInOriginalIndividual, double dInWeightDistanceToOriginal=1.0, double dInWeightSize=1.0, double dInWeightEvaluationTime=1.0 );
 * 	- cFibObjectFitnessBasicAlgorithm( cFibElement * pOriginalFibElement, double dInWeightDistanceToOriginal=1.0, double dInWeightSize=1.0, double dInWeightEvaluationTime=1.0 );
 * 	- cFibObjectFitnessBasicAlgorithm( const cFibObjectFitnessBasicAlgorithm & objectFitnessAlgorithm );
 * 	- cFibObjectFitnessBasicAlgorithm * clone() const;
 * 	- string getClassName() const;
 * 	- cFibIndividual * getOriginalIndividual();
 * 	- cFibElement * getOriginalFibObject();
 * 	- double getWeightDistanceToOriginal() const;
 * 	- double getWeightSize() const;
 * 	- double getWeightEvaluationTime() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cFibObjectFitnessBasicAlgorithm"<<endl;

	cout<<"cFibObjectFitnessBasicAlgorithm algorithmBasic1;"<<endl;
	cFibObjectFitnessBasicAlgorithm algorithmBasic1;
	
	//check the getClassName() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getClassName() == "cFibObjectFitnessBasicAlgorithm" ){
	
		cout<<"The classname of the fitnessalgorithm is correctly \"cFibObjectFitnessBasicAlgorithm\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm "<<
			algorithmBasic1.getClassName() <<" but should be \"cFibObjectFitnessBasicAlgorithm\" ."<<endl;
		iReturn++;
	}
	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividual() == NULL ){
	
		cout<<"The Fib individual of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib individual of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividual() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalFibObject() == NULL ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalFibObject() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getWeightDistanceToOriginal() == 1.0 ){
	
		cout<<"The weight for the distance to the original of the fitnessalgorithm is correctly 1.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the distance to the original of the fitnessalgorithm "<<
			algorithmBasic1.getWeightDistanceToOriginal() <<" but should be 1.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getWeightSize() == 1.0 ){
	
		cout<<"The weight for the size of the Fib object of the fitnessalgorithm is correctly 1.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the size of the Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getWeightSize() <<" but should be 1.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getWeightEvaluationTime() == 1.0 ){
	
		cout<<"The weight for the evaluation of the Fib object of the fitnessalgorithm is correctly 1.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the evaluation of the Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getWeightEvaluationTime() <<" but should be 1.0 ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cFibObjectFitnessBasicAlgorithm with a Fib point"<<endl;
	
	cout<<"cPoint * pPoint = new cPoint();"<<endl;
	cPoint * pPoint = new cPoint();
	
	cout<<"cFibObjectFitnessBasicAlgorithm algorithmBasic2( pPoint, 1.5, 2.0, 3.0 );"<<endl;
	cFibObjectFitnessBasicAlgorithm algorithmBasic2( pPoint, 1.5, 2.0, 3.0 );
	
	//check the getClassName() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic2.getClassName() == "cFibObjectFitnessBasicAlgorithm" ){
	
		cout<<"The classname of the fitnessalgorithm is correctly \"cFibObjectFitnessBasicAlgorithm\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm "<<
			algorithmBasic2.getClassName() <<" but should be \"cFibObjectFitnessBasicAlgorithm\" ."<<endl;
		iReturn++;
	}
	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic2.getOriginalIndividual() != NULL ){
		if ( algorithmBasic2.getOriginalIndividual()->getFibObject() == pPoint ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly pPoint . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic2.getOriginalFibObject() <<" but should be pPoint ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm NULL but should be pPoint="<< pPoint <<" ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic2.getOriginalFibObject() == pPoint ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly pPoint . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic2.getOriginalFibObject() <<" but should be pPoint ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic2.getWeightDistanceToOriginal() == 1.5 ){
	
		cout<<"The weight for the distance to the original of the fitnessalgorithm is correctly 1.5 . "<<endl;
	}else{
		cerr<<"Error: The weight for the distance to the original of the fitnessalgorithm "<<
			algorithmBasic2.getWeightDistanceToOriginal() <<" but should be 1.5 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic2.getWeightSize() == 2.0 ){
	
		cout<<"The weight for the size of the Fib object of the fitnessalgorithm is correctly 2.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the size of the Fib object of the fitnessalgorithm "<<
			algorithmBasic2.getWeightSize() <<" but should be 2.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic2.getWeightEvaluationTime() == 3.0 ){
	
		cout<<"The weight for the evaluation of the Fib object of the fitnessalgorithm is correctly 3.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the evaluation of the Fib object of the fitnessalgorithm "<<
			algorithmBasic2.getWeightEvaluationTime() <<" but should be 3.0 ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cFibObjectFitnessBasicAlgorithm with a NULL Fib object"<<endl;
	
	cout<<"cFibObjectFitnessBasicAlgorithm algorithmBasic3( (cFibElement*)(NULL), -1.5, 20.0, -33.3 );"<<endl;
	cFibObjectFitnessBasicAlgorithm algorithmBasic3( (cFibElement*)(NULL), -1.5, 20.0, -33.3 );
	
	//check the getClassName() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic3.getClassName() == "cFibObjectFitnessBasicAlgorithm" ){
	
		cout<<"The classname of the fitnessalgorithm is correctly \"cFibObjectFitnessBasicAlgorithm\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm "<<
			algorithmBasic3.getClassName() <<" but should be \"cFibObjectFitnessBasicAlgorithm\" ."<<endl;
		iReturn++;
	}
	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic3.getOriginalIndividual() == NULL ){
	
		cout<<"The Fib individual of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib individual of the fitnessalgorithm "<<
			algorithmBasic3.getOriginalIndividual() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic3.getOriginalFibObject() == NULL ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic3.getOriginalFibObject() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic3.getWeightDistanceToOriginal() == -1.5 ){
	
		cout<<"The weight for the distance to the original of the fitnessalgorithm is correctly -1.5 . "<<endl;
	}else{
		cerr<<"Error: The weight for the distance to the original of the fitnessalgorithm "<<
			algorithmBasic3.getWeightDistanceToOriginal() <<" but should be -1.5 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic3.getWeightSize() == 20.0 ){
	
		cout<<"The weight for the size of the Fib object of the fitnessalgorithm is correctly 20.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the size of the Fib object of the fitnessalgorithm "<<
			algorithmBasic3.getWeightSize() <<" but should be 20.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic3.getWeightEvaluationTime() == -33.3 ){
	
		cout<<"The weight for the evaluation of the Fib object of the fitnessalgorithm is correctly -33.3 . "<<endl;
	}else{
		cerr<<"Error: The weight for the evaluation of the Fib object of the fitnessalgorithm "<<
			algorithmBasic3.getWeightEvaluationTime() <<" but should be -33.3 ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cFibObjectFitnessBasicAlgorithm with an Fib individual"<<endl;
	
	cPoint * pPoint1 = new cPoint();
	
	const cFibObjectFitnessBasic fitnessDummy( 1.0 , 5, 8 );
	const list<cIndividualIdentifier> liParents;
	
	cFibIndividual * pOriginalIndividual = new cFibIndividual( pPoint1,
		cIndividualInfo( 0, liParents, fitnessDummy,
		"originalIndividual1", "", cOperationIdentifier( 0 ),
		time_t( NULL ), 0.0, &fitnessDummy), true );
	
	cout<<"cFibObjectFitnessBasicAlgorithm algorithmBasic4( pOriginalIndividual, 27, -88.88, 10254.02 );"<<endl;
	cFibObjectFitnessBasicAlgorithm algorithmBasic4( pOriginalIndividual, 27, -88.88, 10254.02 );
	
	//check the getClassName() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic4.getClassName() == "cFibObjectFitnessBasicAlgorithm" ){
	
		cout<<"The classname of the fitnessalgorithm is correctly \"cFibObjectFitnessBasicAlgorithm\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm "<<
			algorithmBasic4.getClassName() <<" but should be \"cFibObjectFitnessBasicAlgorithm\" ."<<endl;
		iReturn++;
	}
	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic4.getOriginalIndividual() != NULL ){
		//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
		if ( algorithmBasic4.getOriginalIndividual() == pOriginalIndividual ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly pOriginalIndividual . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic4.getOriginalIndividual() <<" but should be pOriginalIndividual ."<<endl;
			iReturn++;
		}
		if ( algorithmBasic4.getOriginalIndividual()->getFibObject() == pPoint1 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly pPoint1 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic4.getOriginalFibObject() <<" but should be pPoint1 ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm NULL but should be pPoint1="<< pPoint <<" ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic4.getOriginalFibObject() == pPoint1 ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly pPoint1 . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic4.getOriginalFibObject() <<" but should be pPoint1 ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic4.getWeightDistanceToOriginal() == 27.0 ){
	
		cout<<"The weight for the distance to the original of the fitnessalgorithm is correctly 27.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the distance to the original of the fitnessalgorithm "<<
			algorithmBasic4.getWeightDistanceToOriginal() <<" but should be 27.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic4.getWeightSize() == -88.88 ){
	
		cout<<"The weight for the size of the Fib object of the fitnessalgorithm is correctly -88.88 . "<<endl;
	}else{
		cerr<<"Error: The weight for the size of the Fib object of the fitnessalgorithm "<<
			algorithmBasic4.getWeightSize() <<" but should be -88.88 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic4.getWeightEvaluationTime() == 10254.02 ){
	
		cout<<"The weight for the evaluation of the Fib object of the fitnessalgorithm is correctly 10254.02 . "<<endl;
	}else{
		cerr<<"Error: The weight for the evaluation of the Fib object of the fitnessalgorithm "<<
			algorithmBasic4.getWeightEvaluationTime() <<" but should be 10254.02 ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cFibObjectFitnessBasicAlgorithm with an NULL pointer Fib individual"<<endl;
	
	cout<<"cFibObjectFitnessBasicAlgorithm algorithmBasic5( (cFibIndividual*)(NULL), 7.7, -20.0, 9648.258 );"<<endl;
	cFibObjectFitnessBasicAlgorithm algorithmBasic5( (cFibIndividual*)(NULL), 77.7, -20.0, 9648.258 );
	
	//check the getClassName() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic5.getClassName() == "cFibObjectFitnessBasicAlgorithm" ){
	
		cout<<"The classname of the fitnessalgorithm is correctly \"cFibObjectFitnessBasicAlgorithm\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm "<<
			algorithmBasic5.getClassName() <<" but should be \"cFibObjectFitnessBasicAlgorithm\" ."<<endl;
		iReturn++;
	}
	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic5.getOriginalIndividual() == NULL ){
	
		cout<<"The Fib individual of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib individual of the fitnessalgorithm "<<
			algorithmBasic5.getOriginalIndividual() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic5.getOriginalFibObject() == NULL ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic5.getOriginalFibObject() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic5.getWeightDistanceToOriginal() == 77.7 ){
	
		cout<<"The weight for the distance to the original of the fitnessalgorithm is correctly 77.7 . "<<endl;
	}else{
		cerr<<"Error: The weight for the distance to the original of the fitnessalgorithm "<<
			algorithmBasic5.getWeightDistanceToOriginal() <<" but should be 77.7 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic5.getWeightSize() == -20.0 ){
	
		cout<<"The weight for the size of the Fib object of the fitnessalgorithm is correctly -20.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the size of the Fib object of the fitnessalgorithm "<<
			algorithmBasic5.getWeightSize() <<" but should be -20.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic5.getWeightEvaluationTime() == 9648.258 ){
	
		cout<<"The weight for the evaluation of the Fib object of the fitnessalgorithm is correctly 9648.258 . "<<endl;
	}else{
		cerr<<"Error: The weight for the evaluation of the Fib object of the fitnessalgorithm "<<
			algorithmBasic5.getWeightEvaluationTime() <<" but should be 9648.258 ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cFibObjectFitnessBasicAlgorithm with a Fib individual wich destructs the contained Fib object"<<endl;
	
	cPoint * pPoint2 = new cPoint();
	
	cFibIndividual * pOriginalIndividual1 = new cFibIndividual( pPoint2,
		cIndividualInfo( 1, liParents, fitnessDummy,
		"originalIndividual1", "", cOperationIdentifier( 1 ),
		time_t( NULL ), 1.0, &fitnessDummy), false );
	
	cout<<"cFibObjectFitnessBasicAlgorithm algorithmBasic6( pOriginalIndividual1, 10254.02, -0.006, 0.002 );"<<endl;
	cFibObjectFitnessBasicAlgorithm algorithmBasic6( pOriginalIndividual1, 10254.02, -0.006, 0.002 );
	
	//check the getClassName() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic6.getClassName() == "cFibObjectFitnessBasicAlgorithm" ){
	
		cout<<"The classname of the fitnessalgorithm is correctly \"cFibObjectFitnessBasicAlgorithm\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm "<<
			algorithmBasic6.getClassName() <<" but should be \"cFibObjectFitnessBasicAlgorithm\" ."<<endl;
		iReturn++;
	}
	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic6.getOriginalIndividual() != NULL ){
		if ( algorithmBasic6.getOriginalIndividual() == pOriginalIndividual1 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly pOriginalIndividual1 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic6.getOriginalIndividual() <<" but should be pOriginalIndividual1 ."<<endl;
			iReturn++;
		}
		if ( algorithmBasic6.getOriginalIndividual()->getFibObject() == pPoint2 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly pPoint2 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic6.getOriginalFibObject() <<" but should be pPoint2 ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm NULL but should be pPoint2="<< pPoint <<" ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic6.getOriginalFibObject() == pPoint2 ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly pPoint2 . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic6.getOriginalFibObject() <<" but should be pPoint2 ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic6.getWeightDistanceToOriginal() == 10254.02 ){
	
		cout<<"The weight for the distance to the original of the fitnessalgorithm is correctly 10254.02 . "<<endl;
	}else{
		cerr<<"Error: The weight for the distance to the original of the fitnessalgorithm "<<
			algorithmBasic6.getWeightDistanceToOriginal() <<" but should be 10254.02 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic6.getWeightSize() == -0.006 ){
	
		cout<<"The weight for the size of the Fib object of the fitnessalgorithm is correctly -0.006 . "<<endl;
	}else{
		cerr<<"Error: The weight for the size of the Fib object of the fitnessalgorithm "<<
			algorithmBasic6.getWeightSize() <<" but should be -0.006 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic6.getWeightEvaluationTime() == 0.002 ){
	
		cout<<"The weight for the evaluation of the Fib object of the fitnessalgorithm is correctly 0.002 . "<<endl;
	}else{
		cerr<<"Error: The weight for the evaluation of the Fib object of the fitnessalgorithm "<<
			algorithmBasic6.getWeightEvaluationTime() <<" but should be 0.002 ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the copyconstructer"<<endl;

	cout<<"cFibObjectFitnessBasicAlgorithm algorithmBasic1Copy( algorithmBasic1 );"<<endl;
	cFibObjectFitnessBasicAlgorithm algorithmBasic1Copy( algorithmBasic1 );
	
	//check the getClassName() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1Copy.getClassName() == "cFibObjectFitnessBasicAlgorithm" ){
	
		cout<<"The classname of the fitnessalgorithm is correctly \"cFibObjectFitnessBasicAlgorithm\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm "<<
			algorithmBasic1Copy.getClassName() <<" but should be \"cFibObjectFitnessBasicAlgorithm\" ."<<endl;
		iReturn++;
	}
	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1Copy.getOriginalIndividual() == NULL ){
	
		cout<<"The Fib individual of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib individual of the fitnessalgorithm "<<
			algorithmBasic1Copy.getOriginalIndividual() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1Copy.getOriginalFibObject() == NULL ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1Copy.getOriginalFibObject() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1Copy.getWeightDistanceToOriginal() == 1.0 ){
	
		cout<<"The weight for the distance to the original of the fitnessalgorithm is correctly 1.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the distance to the original of the fitnessalgorithm "<<
			algorithmBasic1Copy.getWeightDistanceToOriginal() <<" but should be 1.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1Copy.getWeightSize() == 1.0 ){
	
		cout<<"The weight for the size of the Fib object of the fitnessalgorithm is correctly 1.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the size of the Fib object of the fitnessalgorithm "<<
			algorithmBasic1Copy.getWeightSize() <<" but should be 1.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1Copy.getWeightEvaluationTime() == 1.0 ){
	
		cout<<"The weight for the evaluation of the Fib object of the fitnessalgorithm is correctly 1.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the evaluation of the Fib object of the fitnessalgorithm "<<
			algorithmBasic1Copy.getWeightEvaluationTime() <<" but should be 1.0 ."<<endl;
		iReturn++;
	}

	
	cout<<endl<<"cFibObjectFitnessBasicAlgorithm algorithmBasic2Copy( algorithmBasic2 );"<<endl;
	cFibObjectFitnessBasicAlgorithm algorithmBasic2Copy( algorithmBasic2 );
	
	//check the getClassName() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic2Copy.getClassName() == "cFibObjectFitnessBasicAlgorithm" ){
	
		cout<<"The classname of the fitnessalgorithm is correctly \"cFibObjectFitnessBasicAlgorithm\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm "<<
			algorithmBasic2Copy.getClassName() <<" but should be \"cFibObjectFitnessBasicAlgorithm\" ."<<endl;
		iReturn++;
	}
	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic2Copy.getOriginalIndividual() != NULL ){
		if ( algorithmBasic2Copy.getOriginalIndividual()->getFibObject() == pPoint ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly pPoint . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic2Copy.getOriginalFibObject() <<" but should be pPoint ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm NULL but should be pPoint="<< pPoint <<" ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic2Copy.getOriginalFibObject() == pPoint ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly pPoint . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic2Copy.getOriginalFibObject() <<" but should be pPoint ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic2Copy.getWeightDistanceToOriginal() == 1.5 ){
	
		cout<<"The weight for the distance to the original of the fitnessalgorithm is correctly 1.5 . "<<endl;
	}else{
		cerr<<"Error: The weight for the distance to the original of the fitnessalgorithm "<<
			algorithmBasic2Copy.getWeightDistanceToOriginal() <<" but should be 1.5 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic2Copy.getWeightSize() == 2.0 ){
	
		cout<<"The weight for the size of the Fib object of the fitnessalgorithm is correctly 2.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the size of the Fib object of the fitnessalgorithm "<<
			algorithmBasic2Copy.getWeightSize() <<" but should be 2.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic2Copy.getWeightEvaluationTime() == 3.0 ){
	
		cout<<"The weight for the evaluation of the Fib object of the fitnessalgorithm is correctly 3.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the evaluation of the Fib object of the fitnessalgorithm "<<
			algorithmBasic2Copy.getWeightEvaluationTime() <<" but should be 3.0 ."<<endl;
		iReturn++;
	}

	
	cout<<endl<<"cFibObjectFitnessBasicAlgorithm algorithmBasic3Copy( algorithmBasic3 );"<<endl;
	cFibObjectFitnessBasicAlgorithm algorithmBasic3Copy( algorithmBasic3 );
	
	//check the getClassName() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic3Copy.getClassName() == "cFibObjectFitnessBasicAlgorithm" ){
	
		cout<<"The classname of the fitnessalgorithm is correctly \"cFibObjectFitnessBasicAlgorithm\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm "<<
			algorithmBasic3Copy.getClassName() <<" but should be \"cFibObjectFitnessBasicAlgorithm\" ."<<endl;
		iReturn++;
	}
	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic3Copy.getOriginalIndividual() == NULL ){
	
		cout<<"The Fib individual of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib individual of the fitnessalgorithm "<<
			algorithmBasic3Copy.getOriginalIndividual() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic3Copy.getOriginalFibObject() == NULL ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic3Copy.getOriginalFibObject() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic3Copy.getWeightDistanceToOriginal() == -1.5 ){
	
		cout<<"The weight for the distance to the original of the fitnessalgorithm is correctly -1.5 . "<<endl;
	}else{
		cerr<<"Error: The weight for the distance to the original of the fitnessalgorithm "<<
			algorithmBasic3Copy.getWeightDistanceToOriginal() <<" but should be -1.5 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic3Copy.getWeightSize() == 20.0 ){
	
		cout<<"The weight for the size of the Fib object of the fitnessalgorithm is correctly 20.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the size of the Fib object of the fitnessalgorithm "<<
			algorithmBasic3Copy.getWeightSize() <<" but should be 20.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic3Copy.getWeightEvaluationTime() == -33.3 ){
	
		cout<<"The weight for the evaluation of the Fib object of the fitnessalgorithm is correctly -33.3 . "<<endl;
	}else{
		cerr<<"Error: The weight for the evaluation of the Fib object of the fitnessalgorithm "<<
			algorithmBasic3Copy.getWeightEvaluationTime() <<" but should be -33.3 ."<<endl;
		iReturn++;
	}


	cout<<endl<<"cFibObjectFitnessBasicAlgorithm algorithmBasic4Copy( algorithmBasic4 );"<<endl;
	cFibObjectFitnessBasicAlgorithm algorithmBasic4Copy( algorithmBasic4 );
	
	//check the getClassName() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic4Copy.getClassName() == "cFibObjectFitnessBasicAlgorithm" ){
	
		cout<<"The classname of the fitnessalgorithm is correctly \"cFibObjectFitnessBasicAlgorithm\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm "<<
			algorithmBasic4Copy.getClassName() <<" but should be \"cFibObjectFitnessBasicAlgorithm\" ."<<endl;
		iReturn++;
	}
	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic4Copy.getOriginalIndividual() != NULL ){
		//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
		if ( algorithmBasic4Copy.getOriginalIndividual() == pOriginalIndividual ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly pOriginalIndividual . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic4Copy.getOriginalIndividual() <<" but should be pOriginalIndividual ."<<endl;
			iReturn++;
		}
		if ( algorithmBasic4Copy.getOriginalIndividual()->getFibObject() == pPoint1 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly pPoint1 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic4Copy.getOriginalFibObject() <<" but should be pPoint1 ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm NULL but should be pPoint="<< pPoint1 <<" ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic4Copy.getOriginalFibObject() == pPoint1 ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly pPoint1 . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic4Copy.getOriginalFibObject() <<" but should be pPoint1 ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic4Copy.getWeightDistanceToOriginal() == 27.0 ){
	
		cout<<"The weight for the distance to the original of the fitnessalgorithm is correctly 27.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the distance to the original of the fitnessalgorithm "<<
			algorithmBasic4Copy.getWeightDistanceToOriginal() <<" but should be 27.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic4Copy.getWeightSize() == -88.88 ){
	
		cout<<"The weight for the size of the Fib object of the fitnessalgorithm is correctly -88.88 . "<<endl;
	}else{
		cerr<<"Error: The weight for the size of the Fib object of the fitnessalgorithm "<<
			algorithmBasic4Copy.getWeightSize() <<" but should be -88.88 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic4Copy.getWeightEvaluationTime() == 10254.02 ){
	
		cout<<"The weight for the evaluation of the Fib object of the fitnessalgorithm is correctly 10254.02 . "<<endl;
	}else{
		cerr<<"Error: The weight for the evaluation of the Fib object of the fitnessalgorithm "<<
			algorithmBasic4Copy.getWeightEvaluationTime() <<" but should be 10254.02 ."<<endl;
		iReturn++;
	}


	cout<<endl<<"cFibObjectFitnessBasicAlgorithm algorithmBasic5Copy( algorithmBasic5 );"<<endl;
	cFibObjectFitnessBasicAlgorithm algorithmBasic5Copy( algorithmBasic5 );
	
	//check the getClassName() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic5Copy.getClassName() == "cFibObjectFitnessBasicAlgorithm" ){
	
		cout<<"The classname of the fitnessalgorithm is correctly \"cFibObjectFitnessBasicAlgorithm\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm "<<
			algorithmBasic5Copy.getClassName() <<" but should be \"cFibObjectFitnessBasicAlgorithm\" ."<<endl;
		iReturn++;
	}
	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic5Copy.getOriginalIndividual() == NULL ){
	
		cout<<"The Fib individual of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib individual of the fitnessalgorithm "<<
			algorithmBasic5Copy.getOriginalIndividual() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic5Copy.getOriginalFibObject() == NULL ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic5Copy.getOriginalFibObject() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic5Copy.getWeightDistanceToOriginal() == 77.7 ){
	
		cout<<"The weight for the distance to the original of the fitnessalgorithm is correctly 77.7 . "<<endl;
	}else{
		cerr<<"Error: The weight for the distance to the original of the fitnessalgorithm "<<
			algorithmBasic5Copy.getWeightDistanceToOriginal() <<" but should be 77.7 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic5Copy.getWeightSize() == -20.0 ){
	
		cout<<"The weight for the size of the Fib object of the fitnessalgorithm is correctly -20.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the size of the Fib object of the fitnessalgorithm "<<
			algorithmBasic5Copy.getWeightSize() <<" but should be -20.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic5Copy.getWeightEvaluationTime() == 9648.258 ){
	
		cout<<"The weight for the evaluation of the Fib object of the fitnessalgorithm is correctly 9648.258 . "<<endl;
	}else{
		cerr<<"Error: The weight for the evaluation of the Fib object of the fitnessalgorithm "<<
			algorithmBasic5Copy.getWeightEvaluationTime() <<" but should be 9648.258 ."<<endl;
		iReturn++;
	}


	cout<<endl<<"cFibObjectFitnessBasicAlgorithm algorithmBasic6Copy( algorithmBasic6 );"<<endl;
	cFibObjectFitnessBasicAlgorithm algorithmBasic6Copy( algorithmBasic6 );
	
	//check the getClassName() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic6Copy.getClassName() == "cFibObjectFitnessBasicAlgorithm" ){
	
		cout<<"The classname of the fitnessalgorithm is correctly \"cFibObjectFitnessBasicAlgorithm\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm "<<
			algorithmBasic6Copy.getClassName() <<" but should be \"cFibObjectFitnessBasicAlgorithm\" ."<<endl;
		iReturn++;
	}
	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic6Copy.getOriginalIndividual() != NULL ){
		if ( algorithmBasic6Copy.getOriginalIndividual() == pOriginalIndividual1 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly pOriginalIndividual1 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic6Copy.getOriginalIndividual() <<" but should be pOriginalIndividual1 ."<<endl;
			iReturn++;
		}
		if ( algorithmBasic6Copy.getOriginalIndividual()->getFibObject() == pPoint2 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly pPoint2 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic6Copy.getOriginalFibObject() <<" but should be pPoint2 ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm NULL but should be pPoint="<< pPoint <<" ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic6Copy.getOriginalFibObject() == pPoint2 ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly pPoint2 . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic6Copy.getOriginalFibObject() <<" but should be pPoint2 ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic6Copy.getWeightDistanceToOriginal() == 10254.02 ){
	
		cout<<"The weight for the distance to the original of the fitnessalgorithm is correctly 10254.02 . "<<endl;
	}else{
		cerr<<"Error: The weight for the distance to the original of the fitnessalgorithm "<<
			algorithmBasic6Copy.getWeightDistanceToOriginal() <<" but should be 10254.02 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic6Copy.getWeightSize() == -0.006 ){
	
		cout<<"The weight for the size of the Fib object of the fitnessalgorithm is correctly -0.006 . "<<endl;
	}else{
		cerr<<"Error: The weight for the size of the Fib object of the fitnessalgorithm "<<
			algorithmBasic6Copy.getWeightSize() <<" but should be -0.006 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic6Copy.getWeightEvaluationTime() == 0.002 ){
	
		cout<<"The weight for the evaluation of the Fib object of the fitnessalgorithm is correctly 0.002 . "<<endl;
	}else{
		cerr<<"Error: The weight for the evaluation of the Fib object of the fitnessalgorithm "<<
			algorithmBasic6Copy.getWeightEvaluationTime() <<" but should be 0.002 ."<<endl;
		iReturn++;
	}



	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the clone method"<<endl;

	cout<<"cFibObjectFitnessBasicAlgorithm * pAlgorithmBasic1Clone = algorithmBasic1.clone();"<<endl;
	cFibObjectFitnessBasicAlgorithm * pAlgorithmBasic1Clone = algorithmBasic1.clone();
	
	//check the getClassName() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic1Clone->getClassName() == "cFibObjectFitnessBasicAlgorithm" ){
	
		cout<<"The classname of the fitnessalgorithm is correctly \"cFibObjectFitnessBasicAlgorithm\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm "<<
			pAlgorithmBasic1Clone->getClassName() <<" but should be \"cFibObjectFitnessBasicAlgorithm\" ."<<endl;
		iReturn++;
	}
	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic1Clone->getOriginalIndividual() == NULL ){
	
		cout<<"The Fib individual of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib individual of the fitnessalgorithm "<<
			pAlgorithmBasic1Clone->getOriginalIndividual() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic1Clone->getOriginalFibObject() == NULL ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			pAlgorithmBasic1Clone->getOriginalFibObject() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic1Clone->getWeightDistanceToOriginal() == 1.0 ){
	
		cout<<"The weight for the distance to the original of the fitnessalgorithm is correctly 1.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the distance to the original of the fitnessalgorithm "<<
			pAlgorithmBasic1Clone->getWeightDistanceToOriginal() <<" but should be 1.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic1Clone->getWeightSize() == 1.0 ){
	
		cout<<"The weight for the size of the Fib object of the fitnessalgorithm is correctly 1.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the size of the Fib object of the fitnessalgorithm "<<
			pAlgorithmBasic1Clone->getWeightSize() <<" but should be 1.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic1Clone->getWeightEvaluationTime() == 1.0 ){
	
		cout<<"The weight for the evaluation of the Fib object of the fitnessalgorithm is correctly 1.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the evaluation of the Fib object of the fitnessalgorithm "<<
			pAlgorithmBasic1Clone->getWeightEvaluationTime() <<" but should be 1.0 ."<<endl;
		iReturn++;
	}

	
	cout<<endl<<"cFibObjectFitnessBasicAlgorithm * pAlgorithmBasic2Clone = algorithmBasic2.clone();"<<endl;
	cFibObjectFitnessBasicAlgorithm * pAlgorithmBasic2Clone = algorithmBasic2.clone();
	
	//check the getClassName() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic2Clone->getClassName() == "cFibObjectFitnessBasicAlgorithm" ){
	
		cout<<"The classname of the fitnessalgorithm is correctly \"cFibObjectFitnessBasicAlgorithm\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm "<<
			pAlgorithmBasic2Clone->getClassName() <<" but should be \"cFibObjectFitnessBasicAlgorithm\" ."<<endl;
		iReturn++;
	}
	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic2Clone->getOriginalIndividual() != NULL ){
		if ( pAlgorithmBasic2Clone->getOriginalIndividual()->getFibObject() == pPoint ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly pPoint . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				pAlgorithmBasic2Clone->getOriginalFibObject() <<" but should be pPoint ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm NULL but should be pPoint="<< pPoint <<" ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic2Clone->getOriginalFibObject() == pPoint ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly pPoint . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			pAlgorithmBasic2Clone->getOriginalFibObject() <<" but should be pPoint ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic2Clone->getWeightDistanceToOriginal() == 1.5 ){
	
		cout<<"The weight for the distance to the original of the fitnessalgorithm is correctly 1.5 . "<<endl;
	}else{
		cerr<<"Error: The weight for the distance to the original of the fitnessalgorithm "<<
			pAlgorithmBasic2Clone->getWeightDistanceToOriginal() <<" but should be 1.5 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic2Clone->getWeightSize() == 2.0 ){
	
		cout<<"The weight for the size of the Fib object of the fitnessalgorithm is correctly 2.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the size of the Fib object of the fitnessalgorithm "<<
			pAlgorithmBasic2Clone->getWeightSize() <<" but should be 2.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic2Clone->getWeightEvaluationTime() == 3.0 ){
	
		cout<<"The weight for the evaluation of the Fib object of the fitnessalgorithm is correctly 3.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the evaluation of the Fib object of the fitnessalgorithm "<<
			pAlgorithmBasic2Clone->getWeightEvaluationTime() <<" but should be 3.0 ."<<endl;
		iReturn++;
	}

	
	cout<<endl<<"cFibObjectFitnessBasicAlgorithm * pAlgorithmBasic3Clone = algorithmBasic3.clone();"<<endl;
	cFibObjectFitnessBasicAlgorithm * pAlgorithmBasic3Clone = algorithmBasic3.clone();
	
	//check the getClassName() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic3Clone->getClassName() == "cFibObjectFitnessBasicAlgorithm" ){
	
		cout<<"The classname of the fitnessalgorithm is correctly \"cFibObjectFitnessBasicAlgorithm\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm "<<
			pAlgorithmBasic3Clone->getClassName() <<" but should be \"cFibObjectFitnessBasicAlgorithm\" ."<<endl;
		iReturn++;
	}
	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic3Clone->getOriginalIndividual() == NULL ){
	
		cout<<"The Fib individual of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib individual of the fitnessalgorithm "<<
			pAlgorithmBasic3Clone->getOriginalIndividual() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic3Clone->getOriginalFibObject() == NULL ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			pAlgorithmBasic3Clone->getOriginalFibObject() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic3Clone->getWeightDistanceToOriginal() == -1.5 ){
	
		cout<<"The weight for the distance to the original of the fitnessalgorithm is correctly -1.5 . "<<endl;
	}else{
		cerr<<"Error: The weight for the distance to the original of the fitnessalgorithm "<<
			pAlgorithmBasic3Clone->getWeightDistanceToOriginal() <<" but should be -1.5 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic3Clone->getWeightSize() == 20.0 ){
	
		cout<<"The weight for the size of the Fib object of the fitnessalgorithm is correctly 20.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the size of the Fib object of the fitnessalgorithm "<<
			pAlgorithmBasic3Clone->getWeightSize() <<" but should be 20.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic3Clone->getWeightEvaluationTime() == -33.3 ){
	
		cout<<"The weight for the evaluation of the Fib object of the fitnessalgorithm is correctly -33.3 . "<<endl;
	}else{
		cerr<<"Error: The weight for the evaluation of the Fib object of the fitnessalgorithm "<<
			pAlgorithmBasic3Clone->getWeightEvaluationTime() <<" but should be -33.3 ."<<endl;
		iReturn++;
	}


	cout<<endl<<"cFibObjectFitnessBasicAlgorithm * pAlgorithmBasic4Clone = algorithmBasic4.clone();"<<endl;
	cFibObjectFitnessBasicAlgorithm * pAlgorithmBasic4Clone = algorithmBasic4.clone();
	
	//check the getClassName() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic4Clone->getClassName() == "cFibObjectFitnessBasicAlgorithm" ){
	
		cout<<"The classname of the fitnessalgorithm is correctly \"cFibObjectFitnessBasicAlgorithm\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm "<<
			pAlgorithmBasic4Clone->getClassName() <<" but should be \"cFibObjectFitnessBasicAlgorithm\" ."<<endl;
		iReturn++;
	}
	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic4Clone->getOriginalIndividual() != NULL ){
		//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
		if ( pAlgorithmBasic4Clone->getOriginalIndividual() == pOriginalIndividual ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly pOriginalIndividual . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				pAlgorithmBasic4Clone->getOriginalIndividual() <<" but should be pOriginalIndividual ."<<endl;
			iReturn++;
		}
		if ( pAlgorithmBasic4Clone->getOriginalIndividual()->getFibObject() == pPoint1 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly pPoint1 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				pAlgorithmBasic4Clone->getOriginalFibObject() <<" but should be pPoint1 ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm NULL but should be pPoint="<< pPoint1 <<" ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic4Clone->getOriginalFibObject() == pPoint1 ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly pPoint1 . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			pAlgorithmBasic4Clone->getOriginalFibObject() <<" but should be pPoint1 ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic4Clone->getWeightDistanceToOriginal() == 27.0 ){
	
		cout<<"The weight for the distance to the original of the fitnessalgorithm is correctly 27.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the distance to the original of the fitnessalgorithm "<<
			pAlgorithmBasic4Clone->getWeightDistanceToOriginal() <<" but should be 27.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic4Clone->getWeightSize() == -88.88 ){
	
		cout<<"The weight for the size of the Fib object of the fitnessalgorithm is correctly -88.88 . "<<endl;
	}else{
		cerr<<"Error: The weight for the size of the Fib object of the fitnessalgorithm "<<
			pAlgorithmBasic4Clone->getWeightSize() <<" but should be -88.88 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic4Clone->getWeightEvaluationTime() == 10254.02 ){
	
		cout<<"The weight for the evaluation of the Fib object of the fitnessalgorithm is correctly 10254.02 . "<<endl;
	}else{
		cerr<<"Error: The weight for the evaluation of the Fib object of the fitnessalgorithm "<<
			pAlgorithmBasic4Clone->getWeightEvaluationTime() <<" but should be 10254.02 ."<<endl;
		iReturn++;
	}


	cout<<endl<<"cFibObjectFitnessBasicAlgorithm * pAlgorithmBasic5Clone = algorithmBasic5.clone();"<<endl;
	cFibObjectFitnessBasicAlgorithm * pAlgorithmBasic5Clone = algorithmBasic5.clone();
	
	//check the getClassName() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic5Clone->getClassName() == "cFibObjectFitnessBasicAlgorithm" ){
	
		cout<<"The classname of the fitnessalgorithm is correctly \"cFibObjectFitnessBasicAlgorithm\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm "<<
			pAlgorithmBasic5Clone->getClassName() <<" but should be \"cFibObjectFitnessBasicAlgorithm\" ."<<endl;
		iReturn++;
	}
	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic5Clone->getOriginalIndividual() == NULL ){
	
		cout<<"The Fib individual of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib individual of the fitnessalgorithm "<<
			pAlgorithmBasic5Clone->getOriginalIndividual() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic5Clone->getOriginalFibObject() == NULL ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			pAlgorithmBasic5Clone->getOriginalFibObject() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic5Clone->getWeightDistanceToOriginal() == 77.7 ){
	
		cout<<"The weight for the distance to the original of the fitnessalgorithm is correctly 77.7 . "<<endl;
	}else{
		cerr<<"Error: The weight for the distance to the original of the fitnessalgorithm "<<
			pAlgorithmBasic5Clone->getWeightDistanceToOriginal() <<" but should be 77.7 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic5Clone->getWeightSize() == -20.0 ){
	
		cout<<"The weight for the size of the Fib object of the fitnessalgorithm is correctly -20.0 . "<<endl;
	}else{
		cerr<<"Error: The weight for the size of the Fib object of the fitnessalgorithm "<<
			pAlgorithmBasic5Clone->getWeightSize() <<" but should be -20.0 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic5Clone->getWeightEvaluationTime() == 9648.258 ){
	
		cout<<"The weight for the evaluation of the Fib object of the fitnessalgorithm is correctly 9648.258 . "<<endl;
	}else{
		cerr<<"Error: The weight for the evaluation of the Fib object of the fitnessalgorithm "<<
			pAlgorithmBasic5Clone->getWeightEvaluationTime() <<" but should be 9648.258 ."<<endl;
		iReturn++;
	}


	cout<<endl<<"cFibObjectFitnessBasicAlgorithm * pAlgorithmBasic6Clone = algorithmBasic6.clone();"<<endl;
	cFibObjectFitnessBasicAlgorithm * pAlgorithmBasic6Clone = algorithmBasic6.clone();
	
	//check the getClassName() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic6Clone->getClassName() == "cFibObjectFitnessBasicAlgorithm" ){
	
		cout<<"The classname of the fitnessalgorithm is correctly \"cFibObjectFitnessBasicAlgorithm\" . "<<endl;
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm "<<
			pAlgorithmBasic6Clone->getClassName() <<" but should be \"cFibObjectFitnessBasicAlgorithm\" ."<<endl;
		iReturn++;
	}
	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic6Clone->getOriginalIndividual() != NULL ){
		if ( pAlgorithmBasic6Clone->getOriginalIndividual() == pOriginalIndividual1 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly pOriginalIndividual1 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				pAlgorithmBasic6Clone->getOriginalIndividual() <<" but should be pOriginalIndividual1 ."<<endl;
			iReturn++;
		}
		if ( pAlgorithmBasic6Clone->getOriginalIndividual()->getFibObject() == pPoint2 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly pPoint2 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				pAlgorithmBasic6Clone->getOriginalFibObject() <<" but should be pPoint2 ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm NULL but should be pPoint="<< pPoint <<" ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic6Clone->getOriginalFibObject() == pPoint2 ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly pPoint2 . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			pAlgorithmBasic6Clone->getOriginalFibObject() <<" but should be pPoint2 ."<<endl;
		iReturn++;
	}
	//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic6Clone->getWeightDistanceToOriginal() == 10254.02 ){
	
		cout<<"The weight for the distance to the original of the fitnessalgorithm is correctly 10254.02 . "<<endl;
	}else{
		cerr<<"Error: The weight for the distance to the original of the fitnessalgorithm "<<
			pAlgorithmBasic6Clone->getWeightDistanceToOriginal() <<" but should be 10254.02 ."<<endl;
		iReturn++;
	}
	//check the getWeightSize() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic6Clone->getWeightSize() == -0.006 ){
	
		cout<<"The weight for the size of the Fib object of the fitnessalgorithm is correctly -0.006 . "<<endl;
	}else{
		cerr<<"Error: The weight for the size of the Fib object of the fitnessalgorithm "<<
			pAlgorithmBasic6Clone->getWeightSize() <<" but should be -0.006 ."<<endl;
		iReturn++;
	}
	//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasicAlgorithm
	if ( pAlgorithmBasic6Clone->getWeightEvaluationTime() == 0.002 ){
	
		cout<<"The weight for the evaluation of the Fib object of the fitnessalgorithm is correctly 0.002 . "<<endl;
	}else{
		cerr<<"Error: The weight for the evaluation of the Fib object of the fitnessalgorithm "<<
			pAlgorithmBasic6Clone->getWeightEvaluationTime() <<" but should be 0.002 ."<<endl;
		iReturn++;
	}
	delete pAlgorithmBasic1Clone;
	delete pAlgorithmBasic2Clone;
	delete pAlgorithmBasic3Clone;
	delete pAlgorithmBasic4Clone;
	delete pAlgorithmBasic5Clone;
	delete pAlgorithmBasic6Clone;

	delete pPoint;
	delete pPoint2;
	delete pOriginalIndividual;
	delete pOriginalIndividual1;

	return iReturn;
}




/**
 * This method tests the methods for the original individual.
 *
 * methods tested:
 * 	- double evalueDistance( const cFibElement *fibElement, const cFibElement *fibElementArea=NULL  ) const;
 * 	- bool setOriginalIndividual( cIndividual  * pInOriginalIndividual );
 * 	- bool setOriginalIndividual( cFibIndividual  * pInOriginalIndividual );
 * 	- bool setOriginalFibObject( cFibElement  * pInOriginalFibObject );
 * 	- cFibIndividual * getOriginalIndividual();
 * 	- cFibElement * getOriginalFibObject();
 * 	- cRoot * getOriginalIndividualRoot();
 * 	- const cFibObjectFitnessBasic * getBestFitness() const;
 * 	- const cFibObjectFitnessBasic * getWorstCaseFitness() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testOriginal( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for the original individual "<<endl;

	cout<<"cFibObjectFitnessBasicAlgorithm algorithmBasic1;"<<endl;
	cFibObjectFitnessBasicAlgorithm algorithmBasic1;
	
	const cFibObjectFitnessBasic bestFitness( 0.0, 0, 0 );
	
	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividual() == NULL ){
	
		cout<<"The Fib individual of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib individual of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividual() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalFibObject() == NULL ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalFibObject() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividualRoot() == NULL ){
	
		cout<<"The original Fib object roots of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object roots of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividualRoot() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check getBestFitness()
	if ( algorithmBasic1.getBestFitness() != NULL ){
		if ( bestFitness == *(algorithmBasic1.getBestFitness()) ){
			cout<<"The best fitness is correctly equal to bestFitness . "<<endl;
		}else{
			cerr<<"Error: The best fitness is not equal to bestFitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The best fitness is NULL."<<endl;
		iReturn++;
	}
	//check getWorstCaseFitness()
	if ( algorithmBasic1.getWorstCaseFitness() == NULL ){
		cout<<"The worst case fitness is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The worst case fitness is not NULL."<<endl;
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for the original individual setting a point as original"<<endl;

	cPoint point1;
	
	const cFibObjectFitnessBasic fitnessDummy( 1.0 , 5, 8 );
	const list<cIndividualIdentifier> liParents;
	
	cFibIndividual originalIndividual1( &point1,
		cIndividualInfo( 1, liParents, fitnessDummy,
		"originalIndividual1", "", cOperationIdentifier( 1 ),
		time_t( NULL ), 1.0, &fitnessDummy), false );
	
	cout<<"algorithmBasic1.setOriginalIndividual( (cIndividual*)(&originalIndividual1) ); "<<endl;
	algorithmBasic1.setOriginalIndividual( (cIndividual*)(&originalIndividual1) );

	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividual() != NULL ){
		if ( algorithmBasic1.getOriginalIndividual() == &originalIndividual1 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly originalIndividual1 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic1.getOriginalIndividual() <<" but should be originalIndividual1 ."<<endl;
			iReturn++;
		}
		if ( algorithmBasic1.getOriginalIndividual()->getFibObject() == &point1 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly point1 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic1.getOriginalFibObject() <<" but should be point1 ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm NULL but should be point1="<< &point1 <<" ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalFibObject() == &point1 ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly point1 . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalFibObject() <<" but should be point1 ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividualRoot() == NULL ){
	
		cout<<"The original Fib object roots of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object roots of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividualRoot() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check getBestFitness()
	if ( algorithmBasic1.getBestFitness() != NULL ){
		if ( bestFitness == *(algorithmBasic1.getBestFitness()) ){
			cout<<"The best fitness is correctly equal to bestFitness . "<<endl;
		}else{
			cerr<<"Error: The best fitness is not equal to bestFitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The best fitness is NULL."<<endl;
		iReturn++;
	}
	//check getWorstCaseFitness()
	if ( algorithmBasic1.getWorstCaseFitness() != NULL ){
		
		cFibObjectFitnessBasic * pWorstCaseFitness = algorithmBasic1.
			evalueFitness( originalIndividual1 );
		if ( pWorstCaseFitness ){
			if ( (*pWorstCaseFitness) == *(algorithmBasic1.getWorstCaseFitness()) ){
				cout<<"The worst case fitness is correctly the fitness of the original."<<endl;
			}else{
				cerr<<"Error: The worst case fitness is not the fitness of the original."<<endl;
				iReturn++;
			}
			delete pWorstCaseFitness;
		}else{
			cerr<<"Error: Couldn't evalue the worst case fitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The worst case fitness is NULL."<<endl;
		iReturn++;
	}

	cout<<endl<<"algorithmBasic1.setOriginalIndividual( (cIndividual*)NULL ); "<<endl;
	algorithmBasic1.setOriginalIndividual( (cIndividual*)NULL );

	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividual() == NULL ){
	
		cout<<"The Fib individual of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib individual of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividual() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalFibObject() == NULL ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalFibObject() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividualRoot() == NULL ){
	
		cout<<"The original Fib object roots of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object roots of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividualRoot() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check getBestFitness()
	if ( algorithmBasic1.getBestFitness() != NULL ){
		if ( bestFitness == *(algorithmBasic1.getBestFitness()) ){
			cout<<"The best fitness is correctly equal to bestFitness . "<<endl;
		}else{
			cerr<<"Error: The best fitness is not equal to bestFitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The best fitness is NULL."<<endl;
		iReturn++;
	}
	//check getWorstCaseFitness()
	if ( algorithmBasic1.getWorstCaseFitness() == NULL ){
		cout<<"The worst case fitness is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The worst case fitness is not NULL."<<endl;
		iReturn++;
	}

	cout<<endl<<"algorithmBasic1.setOriginalIndividual( &originalIndividual1 ); "<<endl;
	algorithmBasic1.setOriginalIndividual( &originalIndividual1 );

	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividual() != NULL ){
		if ( algorithmBasic1.getOriginalIndividual() == &originalIndividual1 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly originalIndividual1 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic1.getOriginalIndividual() <<" but should be originalIndividual1 ."<<endl;
			iReturn++;
		}
		if ( algorithmBasic1.getOriginalIndividual()->getFibObject() == &point1 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly point1 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic1.getOriginalFibObject() <<" but should be point1 ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm NULL but should be point1="<< &point1 <<" ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalFibObject() == &point1 ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly point1 . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalFibObject() <<" but should be point1 ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividualRoot() == NULL ){
	
		cout<<"The original Fib object roots of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object roots of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividualRoot() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check getBestFitness()
	if ( algorithmBasic1.getBestFitness() != NULL ){
		if ( bestFitness == *(algorithmBasic1.getBestFitness()) ){
			cout<<"The best fitness is correctly equal to bestFitness . "<<endl;
		}else{
			cerr<<"Error: The best fitness is not equal to bestFitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The best fitness is NULL."<<endl;
		iReturn++;
	}
	//check getWorstCaseFitness()
	if ( algorithmBasic1.getWorstCaseFitness() != NULL ){
		
		cFibObjectFitnessBasic * pWorstCaseFitness = algorithmBasic1.
			evalueFitness( originalIndividual1 );
		if ( pWorstCaseFitness ){
			if ( (*pWorstCaseFitness) == *(algorithmBasic1.getWorstCaseFitness()) ){
				cout<<"The worst case fitness is correctly the fitness of the original."<<endl;
			}else{
				cerr<<"Error: The worst case fitness is not the fitness of the original."<<endl;
				iReturn++;
			}
			delete pWorstCaseFitness;
		}else{
			cerr<<"Error: Couldn't evalue the worst case fitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The worst case fitness is NULL."<<endl;
		iReturn++;
	}

	cout<<endl<<"algorithmBasic1.setOriginalIndividual( (cFibIndividual*)NULL ); "<<endl;
	algorithmBasic1.setOriginalIndividual( (cFibIndividual*)NULL );

	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividual() == NULL ){
	
		cout<<"The Fib individual of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib individual of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividual() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalFibObject() == NULL ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalFibObject() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividualRoot() == NULL ){
	
		cout<<"The original Fib object roots of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object roots of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividualRoot() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check getBestFitness()
	if ( algorithmBasic1.getBestFitness() != NULL ){
		if ( bestFitness == *(algorithmBasic1.getBestFitness()) ){
			cout<<"The best fitness is correctly equal to bestFitness . "<<endl;
		}else{
			cerr<<"Error: The best fitness is not equal to bestFitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The best fitness is NULL."<<endl;
		iReturn++;
	}
	//check getWorstCaseFitness()
	if ( algorithmBasic1.getWorstCaseFitness() == NULL ){
		cout<<"The worst case fitness is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The worst case fitness is not NULL."<<endl;
		iReturn++;
	}

	cout<<endl<<"algorithmBasic1.setOriginalFibObject( &point1 ); "<<endl;
	algorithmBasic1.setOriginalFibObject( &point1 );

	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividual() != NULL ){
		if ( algorithmBasic1.getOriginalIndividual()->getFibObject() == &point1 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly point1 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic1.getOriginalFibObject() <<" but should be point1 ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm NULL but should be point1="<< &point1 <<" ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalFibObject() == &point1 ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly point1 . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalFibObject() <<" but should be point1 ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividualRoot() == NULL ){
	
		cout<<"The original Fib object roots of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object roots of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividualRoot() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check getBestFitness()
	if ( algorithmBasic1.getBestFitness() != NULL ){
		if ( bestFitness == *(algorithmBasic1.getBestFitness()) ){
			cout<<"The best fitness is correctly equal to bestFitness . "<<endl;
		}else{
			cerr<<"Error: The best fitness is not equal to bestFitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The best fitness is NULL."<<endl;
		iReturn++;
	}
	//check getWorstCaseFitness()
	if ( algorithmBasic1.getWorstCaseFitness() != NULL ){
		
		cFibObjectFitnessBasic * pWorstCaseFitness = algorithmBasic1.
			evalueFitness( originalIndividual1 );
		if ( pWorstCaseFitness ){
			if ( (*pWorstCaseFitness) == *(algorithmBasic1.getWorstCaseFitness()) ){
				cout<<"The worst case fitness is correctly the fitness of the original."<<endl;
			}else{
				cerr<<"Error: The worst case fitness is not the fitness of the original."<<endl;
				iReturn++;
			}
			delete pWorstCaseFitness;
		}else{
			cerr<<"Error: Couldn't evalue the worst case fitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The worst case fitness is NULL."<<endl;
		iReturn++;
	}

	cout<<endl<<"algorithmBasic1.setOriginalFibObject( NULL ); "<<endl;
	algorithmBasic1.setOriginalFibObject( NULL );

	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividual() == NULL ){
	
		cout<<"The Fib individual of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib individual of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividual() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalFibObject() == NULL ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalFibObject() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividualRoot() == NULL ){
	
		cout<<"The original Fib object roots of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object roots of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividualRoot() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check getBestFitness()
	if ( algorithmBasic1.getBestFitness() != NULL ){
		if ( bestFitness == *(algorithmBasic1.getBestFitness()) ){
			cout<<"The best fitness is correctly equal to bestFitness . "<<endl;
		}else{
			cerr<<"Error: The best fitness is not equal to bestFitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The best fitness is NULL."<<endl;
		iReturn++;
	}
	//check getWorstCaseFitness()
	if ( algorithmBasic1.getWorstCaseFitness() == NULL ){
		cout<<"The worst case fitness is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The worst case fitness is not NULL."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for the original individual setting a object with a root as original"<<endl;

	cVectorPosition vecPosition( 2 );
	vecPosition.setValue( 1, 1 );
	cPoint point2( &vecPosition );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cRoot root1( &point2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cRoot root1( NULL, NULL, &point2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	root1.setNumberOfInputVariables( 1 );
	
	//the structur of root with empty points
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cRoot root1empty( &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cRoot root1empty( NULL, NULL, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	root1empty.setNumberOfInputVariables( 1 );

	
	cFibIndividual originalIndividual2( &root1,
		cIndividualInfo( 1, liParents, fitnessDummy,
		"originalIndividualRoot1", "", cOperationIdentifier( 1 ),
		time_t( NULL ), 1.0, &fitnessDummy), false );
	
	cout<<"algorithmBasic1.setOriginalIndividual( (cIndividual*)(&originalIndividual2) ); "<<endl;
	algorithmBasic1.setOriginalIndividual( (cIndividual*)(&originalIndividual2) );

	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividual() != NULL ){
		if ( algorithmBasic1.getOriginalIndividual() == &originalIndividual2 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly originalIndividual2 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic1.getOriginalIndividual() <<" but should be originalIndividual2 ."<<endl;
			iReturn++;
		}
		if ( algorithmBasic1.getOriginalIndividual()->getFibObject() == &root1 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly root1 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic1.getOriginalFibObject() <<" but should be root1 ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm NULL but should be root1="<< &root1 <<" ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalFibObject() == &root1 ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly root1 . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalFibObject() <<" but should be root1 ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividualRoot() != NULL ){
		if ( root1empty.equal( *(algorithmBasic1.getOriginalIndividualRoot() ) ) ){
		
			cout<<"The original Fib object roots of the fitnessalgorithm is correctly equal to root1empty . "<<endl;
		}else{
			cerr<<"Error: The original Fib object roots of the fitnessalgorithm is "<<
				algorithmBasic1.getOriginalIndividualRoot() <<" and not equal to root1empty ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The original Fib object roots of the fitnessalgorithm is "<<
			algorithmBasic1.getOriginalIndividualRoot() <<" but should be equal to root1empty ."<<endl;
		iReturn++;
	}
	//check getBestFitness()
	if ( algorithmBasic1.getBestFitness() != NULL ){
		if ( bestFitness == *(algorithmBasic1.getBestFitness()) ){
			cout<<"The best fitness is correctly equal to bestFitness . "<<endl;
		}else{
			cerr<<"Error: The best fitness is not equal to bestFitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The best fitness is NULL."<<endl;
		iReturn++;
	}
	//check getWorstCaseFitness()
	if ( algorithmBasic1.getWorstCaseFitness() != NULL ){
		
		cFibObjectFitnessBasic * pWorstCaseFitness = algorithmBasic1.
			evalueFitness( originalIndividual2 );
		if ( pWorstCaseFitness ){
			if ( (*pWorstCaseFitness) == *(algorithmBasic1.getWorstCaseFitness()) ){
				cout<<"The worst case fitness is correctly the fitness of the original."<<endl;
			}else{
				cerr<<"Error: The worst case fitness is not the fitness of the original."<<endl;
				iReturn++;
			}
			delete pWorstCaseFitness;
		}else{
			cerr<<"Error: Couldn't evalue the worst case fitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The worst case fitness is NULL."<<endl;
		iReturn++;
	}

	
	cout<<endl<<"algorithmBasic1.setOriginalIndividual( (cIndividual*)NULL ); "<<endl;
	algorithmBasic1.setOriginalIndividual( (cIndividual*)NULL );

	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividual() == NULL ){
	
		cout<<"The Fib individual of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib individual of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividual() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalFibObject() == NULL ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalFibObject() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividualRoot() == NULL ){
	
		cout<<"The original Fib object roots of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object roots of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividualRoot() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check getBestFitness()
	if ( algorithmBasic1.getBestFitness() != NULL ){
		if ( bestFitness == *(algorithmBasic1.getBestFitness()) ){
			cout<<"The best fitness is correctly equal to bestFitness . "<<endl;
		}else{
			cerr<<"Error: The best fitness is not equal to bestFitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The best fitness is NULL."<<endl;
		iReturn++;
	}
	//check getWorstCaseFitness()
	if ( algorithmBasic1.getWorstCaseFitness() == NULL ){
		cout<<"The worst case fitness is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The worst case fitness is not NULL."<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"algorithmBasic1.setOriginalIndividual( &originalIndividual2 ); "<<endl;
	algorithmBasic1.setOriginalIndividual( &originalIndividual2 );

	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividual() != NULL ){
		if ( algorithmBasic1.getOriginalIndividual() == &originalIndividual2 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly originalIndividual2 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic1.getOriginalIndividual() <<" but should be originalIndividual2 ."<<endl;
			iReturn++;
		}
		if ( algorithmBasic1.getOriginalIndividual()->getFibObject() == &root1 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly root1 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic1.getOriginalFibObject() <<" but should be root1 ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm NULL but should be root1="<< &root1 <<" ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalFibObject() == &root1 ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly root1 . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalFibObject() <<" but should be root1 ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividualRoot() != NULL ){
		if ( root1empty.equal( *(algorithmBasic1.getOriginalIndividualRoot() ) ) ){
		
			cout<<"The original Fib object roots of the fitnessalgorithm is correctly equal to root1empty . "<<endl;
		}else{
			cerr<<"Error: The original Fib object roots of the fitnessalgorithm is "<<
				algorithmBasic1.getOriginalIndividualRoot() <<" and not equal to root1empty ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The original Fib object roots of the fitnessalgorithm is "<<
			algorithmBasic1.getOriginalIndividualRoot() <<" but should be equal to root1empty ."<<endl;
		iReturn++;
	}
	//check getBestFitness()
	if ( algorithmBasic1.getBestFitness() != NULL ){
		if ( bestFitness == *(algorithmBasic1.getBestFitness()) ){
			cout<<"The best fitness is correctly equal to bestFitness . "<<endl;
		}else{
			cerr<<"Error: The best fitness is not equal to bestFitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The best fitness is NULL."<<endl;
		iReturn++;
	}
	//check getWorstCaseFitness()
	if ( algorithmBasic1.getWorstCaseFitness() != NULL ){
		
		cFibObjectFitnessBasic * pWorstCaseFitness = algorithmBasic1.
			evalueFitness( originalIndividual2 );
		if ( pWorstCaseFitness ){
			if ( (*pWorstCaseFitness) == *(algorithmBasic1.getWorstCaseFitness()) ){
				cout<<"The worst case fitness is correctly the fitness of the original."<<endl;
			}else{
				cerr<<"Error: The worst case fitness is not the fitness of the original."<<endl;
				iReturn++;
			}
			delete pWorstCaseFitness;
		}else{
			cerr<<"Error: Couldn't evalue the worst case fitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The worst case fitness is NULL."<<endl;
		iReturn++;
	}


	cout<<endl<<"algorithmBasic1.setOriginalIndividual( (cFibIndividual*)NULL ); "<<endl;
	algorithmBasic1.setOriginalIndividual( (cFibIndividual*)NULL );

	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividual() == NULL ){
	
		cout<<"The Fib individual of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib individual of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividual() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalFibObject() == NULL ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalFibObject() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividualRoot() == NULL ){
	
		cout<<"The original Fib object roots of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object roots of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividualRoot() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check getBestFitness()
	if ( algorithmBasic1.getBestFitness() != NULL ){
		if ( bestFitness == *(algorithmBasic1.getBestFitness()) ){
			cout<<"The best fitness is correctly equal to bestFitness . "<<endl;
		}else{
			cerr<<"Error: The best fitness is not equal to bestFitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The best fitness is NULL."<<endl;
		iReturn++;
	}
	//check getWorstCaseFitness()
	if ( algorithmBasic1.getWorstCaseFitness() == NULL ){
		cout<<"The worst case fitness is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The worst case fitness is not NULL."<<endl;
		iReturn++;
	}


	cout<<endl<<"algorithmBasic1.setOriginalFibObject( &root1 ); "<<endl;
	algorithmBasic1.setOriginalFibObject( &root1 );

	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividual() != NULL ){
		if ( algorithmBasic1.getOriginalIndividual()->getFibObject() == &root1 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly root1 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic1.getOriginalFibObject() <<" but should be root1 ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm NULL but should be root1="<< &root1 <<" ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalFibObject() == &root1 ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly root1 . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalFibObject() <<" but should be root1 ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividualRoot() != NULL ){
		if ( root1empty.equal( *(algorithmBasic1.getOriginalIndividualRoot() ) ) ){
		
			cout<<"The original Fib object roots of the fitnessalgorithm is correctly equal to root1empty . "<<endl;
		}else{
			cerr<<"Error: The original Fib object roots of the fitnessalgorithm is "<<
				algorithmBasic1.getOriginalIndividualRoot() <<" and not equal to root1empty ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The original Fib object roots of the fitnessalgorithm is "<<
			algorithmBasic1.getOriginalIndividualRoot() <<" but should be equal to root1empty ."<<endl;
		iReturn++;
	}
	//check getBestFitness()
	if ( algorithmBasic1.getBestFitness() != NULL ){
		if ( bestFitness == *(algorithmBasic1.getBestFitness()) ){
			cout<<"The best fitness is correctly equal to bestFitness . "<<endl;
		}else{
			cerr<<"Error: The best fitness is not equal to bestFitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The best fitness is NULL."<<endl;
		iReturn++;
	}
	//check getWorstCaseFitness()
	if ( algorithmBasic1.getWorstCaseFitness() != NULL ){
		
		cFibObjectFitnessBasic * pWorstCaseFitness = algorithmBasic1.
			evalueFitness( originalIndividual2 );
		if ( pWorstCaseFitness ){
			if ( (*pWorstCaseFitness) == *(algorithmBasic1.getWorstCaseFitness()) ){
				cout<<"The worst case fitness is correctly the fitness of the original."<<endl;
			}else{
				cerr<<"Error: The worst case fitness is not the fitness of the original."<<endl;
				iReturn++;
			}
			delete pWorstCaseFitness;
		}else{
			cerr<<"Error: Couldn't evalue the worst case fitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The worst case fitness is NULL."<<endl;
		iReturn++;
	}


	cout<<endl<<"algorithmBasic1.setOriginalFibObject( NULL ); "<<endl;
	algorithmBasic1.setOriginalFibObject( NULL );

	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividual() == NULL ){
	
		cout<<"The Fib individual of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib individual of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividual() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalFibObject() == NULL ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalFibObject() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividualRoot() == NULL ){
	
		cout<<"The original Fib object roots of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object roots of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividualRoot() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check getBestFitness()
	if ( algorithmBasic1.getBestFitness() != NULL ){
		if ( bestFitness == *(algorithmBasic1.getBestFitness()) ){
			cout<<"The best fitness is correctly equal to bestFitness . "<<endl;
		}else{
			cerr<<"Error: The best fitness is not equal to bestFitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The best fitness is NULL."<<endl;
		iReturn++;
	}
	//check getWorstCaseFitness()
	if ( algorithmBasic1.getWorstCaseFitness() == NULL ){
		cout<<"The worst case fitness is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The worst case fitness is not NULL."<<endl;
		iReturn++;
	}



	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for the original individual setting a object with a roottree (3(2(0;0);1(0);2(0;0))) as original"<<endl;

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cPoint point3( &vecPosition );
	cout<<"cRoot rootTree( &point3 ); "<<endl;
	cRoot rootTree( &point3 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootTree( NULL, NULL, &point2 ); "<<endl;
	cRoot rootTree( NULL, NULL, &point2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	rootTree.setNumberOfInputVariables( 1 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cPoint point1_1( &vecPosition );
	point1_1.getPosition()->setValue( 1, 2 );
	cRoot rootTree1_1( &point1_1 );
	rootTree1_1.setNumberOfInputVariables( 1 );
	cPoint point1_2( &vecPosition );
	point1_2.getPosition()->setValue( 1, 3 );
	cRoot rootTree1_2( &point1_2 );
	rootTree1_2.setNumberOfInputVariables( 2 );
	cPoint point4( &vecPosition );
	point4.getPosition()->setValue( 1, 4 );
	cRoot rootTree1( &point4 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	point2.getPosition()->setValue( 1, 2 );
	cRoot rootTree1_1( NULL, NULL, &point2 );
	rootTree1_1.setNumberOfInputVariables( 1 );
	point2.getPosition()->setValue( 1, 3 );
	cRoot rootTree1_2( NULL, NULL, &point2 );
	rootTree1_2.setNumberOfInputVariables( 2 );
	point2.getPosition()->setValue( 1, 4 );
	cRoot rootTree1( NULL, NULL, &point2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	rootTree1.setNumberOfInputVariables( 3 );
	cout<<"rootTree1.addSubRootObject( 1, &rootTree1_1 ); "<<endl;
	rootTree1.addSubRootObject( 1, &rootTree1_1 );
	cout<<"rootTree1.addSubRootObject( 2, &rootTree1_2 ); "<<endl;
	rootTree1.addSubRootObject( 2, &rootTree1_2 );
	cout<<"rootTree.addSubRootObject( 3, &rootTree1 ); "<<endl;
	rootTree.addSubRootObject( 3, &rootTree1 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cPoint point2_1( &vecPosition );
	point2_1.getPosition()->setValue( 1, 5 );
	cRoot rootTree2_1( &point2_1 );
	rootTree2_1.setNumberOfInputVariables( 4 );
	cPoint point5( &vecPosition );
	point5.getPosition()->setValue( 1, 6 );
	cRoot rootTree2( &point5 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	point2.getPosition()->setValue( 1, 5 );
	cRoot rootTree2_1( NULL, NULL, &point2 );
	rootTree2_1.setNumberOfInputVariables( 4 );
	point2.getPosition()->setValue( 1, 6 );
	cRoot rootTree2( NULL, NULL, &point2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	rootTree2.setNumberOfInputVariables( 5 );
	cout<<"rootTree2.addSubRootObject( 4, &rootTree2_1 );"<<endl;
	rootTree2.addSubRootObject( 4, &rootTree2_1 );
	cout<<"rootTree.addSubRootObject( 5, &rootTree2 );"<<endl;
	rootTree.addSubRootObject( 5, &rootTree2 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cPoint point3_1( &vecPosition );
	point3_1.getPosition()->setValue( 1, 7 );
	cRoot rootTree3_1( &point3_1 );
	rootTree3_1.setNumberOfInputVariables( 6 );
	cPoint point3_2( &vecPosition );
	point3_2.getPosition()->setValue( 1, 8 );
	cRoot rootTree3_2( &point3_2 );
	rootTree3_2.setNumberOfInputVariables( 7 );
	cPoint point6( &vecPosition );
	point6.getPosition()->setValue( 1, 9 );
	cRoot rootTree3( &point6 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	point2.getPosition()->setValue( 1, 7 );
	cRoot rootTree3_1( NULL, NULL, &point2 );
	rootTree3_1.setNumberOfInputVariables( 6 );
	point2.getPosition()->setValue( 1, 8 );
	cRoot rootTree3_2( NULL, NULL, &point2 );
	rootTree3_2.setNumberOfInputVariables( 7 );
	point2.getPosition()->setValue( 1, 9 );
	cRoot rootTree3( NULL, NULL, &point2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	rootTree3.setNumberOfInputVariables( 8 );
	cout<<"rootTree3.addSubRootObject( 6, &rootTree3_1 );"<<endl;
	rootTree3.addSubRootObject( 6, &rootTree3_1 );
	cout<<"rootTree3.addSubRootObject( 7, &rootTree3_2 );"<<endl;
	rootTree3.addSubRootObject( 7, &rootTree3_2 );
	cout<<"rootTree.addSubRootObject( 8, &rootTree3 );"<<endl;
	rootTree.addSubRootObject( 8, &rootTree3 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cPoint pointEmpty1;
	cRoot rootTreeEmpty( &pointEmpty1 );
	rootTreeEmpty.setNumberOfInputVariables( 1 );
	
	cPoint pointEmpty1_1;
	cRoot rootTreeEmpty1_1( &pointEmpty1_1 );
	rootTreeEmpty1_1.setNumberOfInputVariables( 1 );
	cPoint pointEmpty1_2;
	cRoot rootTreeEmpty1_2( &pointEmpty1_2 );
	rootTreeEmpty1_2.setNumberOfInputVariables( 2 );
	cPoint pointEmpty01;
	cRoot rootTreeEmpty1( &pointEmpty01 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cRoot rootTreeEmpty( NULL, NULL, &point1 );
	rootTreeEmpty.setNumberOfInputVariables( 1 );
	
	cRoot rootTreeEmpty1_1( NULL, NULL, &point1 );
	rootTreeEmpty1_1.setNumberOfInputVariables( 1 );
	cRoot rootTreeEmpty1_2( NULL, NULL, &point1 );
	rootTreeEmpty1_2.setNumberOfInputVariables( 2 );
	cRoot rootTreeEmpty1( NULL, NULL, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	rootTreeEmpty1.setNumberOfInputVariables( 3 );
	rootTreeEmpty1.addSubRootObject( 1, &rootTreeEmpty1_1 );
	rootTreeEmpty1.addSubRootObject( 2, &rootTreeEmpty1_2 );
	rootTreeEmpty.addSubRootObject( 3, &rootTreeEmpty1 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cPoint pointEmpty2_1;
	cRoot rootTreeEmpty2_1( &pointEmpty2_1 );
	rootTreeEmpty2_1.setNumberOfInputVariables( 4 );
	cPoint pointEmpty2;
	cRoot rootTreeEmpty2( &pointEmpty2 );
	rootTreeEmpty2.setNumberOfInputVariables( 5 );
	rootTreeEmpty2.addSubRootObject( 4, &rootTreeEmpty2_1 );
	rootTreeEmpty.addSubRootObject( 5, &rootTreeEmpty2 );

	cPoint pointEmpty3_1;
	cRoot rootTreeEmpty3_1( &pointEmpty3_1 );
	rootTreeEmpty3_1.setNumberOfInputVariables( 6 );
	cPoint pointEmpty3_2;
	cRoot rootTreeEmpty3_2( &pointEmpty3_2 );
	rootTreeEmpty3_2.setNumberOfInputVariables( 7 );
	cPoint pointEmpty3;
	cRoot rootTreeEmpty3( &pointEmpty3 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cRoot rootTreeEmpty2_1( NULL, NULL, &point1 );
	rootTreeEmpty2_1.setNumberOfInputVariables( 4 );
	cRoot rootTreeEmpty2( NULL, NULL, &point1 );
	rootTreeEmpty2.setNumberOfInputVariables( 5 );
	rootTreeEmpty2.addSubRootObject( 4, &rootTreeEmpty2_1 );
	rootTreeEmpty.addSubRootObject( 5, &rootTreeEmpty2 );

	cRoot rootTreeEmpty3_1( NULL, NULL, &point1 );
	rootTreeEmpty3_1.setNumberOfInputVariables( 6 );
	cRoot rootTreeEmpty3_2( NULL, NULL, &point1 );
	rootTreeEmpty3_2.setNumberOfInputVariables( 7 );
	cRoot rootTreeEmpty3( NULL, NULL, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	rootTreeEmpty3.setNumberOfInputVariables( 8 );
	rootTreeEmpty3.addSubRootObject( 6, &rootTreeEmpty3_1 );
	rootTreeEmpty3.addSubRootObject( 7, &rootTreeEmpty3_2 );
	rootTreeEmpty.addSubRootObject( 8, &rootTreeEmpty3 );

	
	cFibIndividual originalIndividual3( &rootTree,
		cIndividualInfo( 1, liParents, fitnessDummy,
		"originalIndividualRoot1", "", cOperationIdentifier( 1 ),
		time_t( NULL ), 1.0, &fitnessDummy), false );
	
	cout<<"algorithmBasic1.setOriginalIndividual( (cIndividual*)(&originalIndividual3) ); "<<endl;
	algorithmBasic1.setOriginalIndividual( (cIndividual*)(&originalIndividual3) );

	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividual() != NULL ){
		if ( algorithmBasic1.getOriginalIndividual() == &originalIndividual3 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly originalIndividual3 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic1.getOriginalIndividual() <<" but should be originalIndividual3 ."<<endl;
			iReturn++;
		}
		if ( algorithmBasic1.getOriginalIndividual()->getFibObject() == &rootTree ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly rootTree . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic1.getOriginalFibObject() <<" but should be rootTree ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm NULL but should be rootTree="<< &rootTree <<" ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalFibObject() == &rootTree ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly rootTree . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalFibObject() <<" but should be rootTree ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividualRoot() != NULL ){
		if ( rootTreeEmpty.equal( *(algorithmBasic1.getOriginalIndividualRoot() ) ) ){
		
			cout<<"The original Fib object roots of the fitnessalgorithm is correctly equal to rootTreeEmpty . "<<endl;
		}else{
			cerr<<"Error: The original Fib object roots of the fitnessalgorithm is "<<
				algorithmBasic1.getOriginalIndividualRoot() <<" and not equal to rootTreeEmpty ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The original Fib object roots of the fitnessalgorithm is "<<
			algorithmBasic1.getOriginalIndividualRoot() <<" but should be equal to rootTreeEmpty ."<<endl;
		iReturn++;
	}
	//check getBestFitness()
	if ( algorithmBasic1.getBestFitness() != NULL ){
		if ( bestFitness == *(algorithmBasic1.getBestFitness()) ){
			cout<<"The best fitness is correctly equal to bestFitness . "<<endl;
		}else{
			cerr<<"Error: The best fitness is not equal to bestFitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The best fitness is NULL."<<endl;
		iReturn++;
	}
	//check getWorstCaseFitness()
	if ( algorithmBasic1.getWorstCaseFitness() != NULL ){
		
		cFibObjectFitnessBasic * pWorstCaseFitness = algorithmBasic1.
			evalueFitness( originalIndividual3 );
		if ( pWorstCaseFitness ){
			if ( (*pWorstCaseFitness) == *(algorithmBasic1.getWorstCaseFitness()) ){
				cout<<"The worst case fitness is correctly the fitness of the original."<<endl;
			}else{
				cerr<<"Error: The worst case fitness is not the fitness of the original."<<endl;
				iReturn++;
			}
			delete pWorstCaseFitness;
		}else{
			cerr<<"Error: Couldn't evalue the worst case fitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The worst case fitness is NULL."<<endl;
		iReturn++;
	}

	
	cout<<endl<<"algorithmBasic1.setOriginalIndividual( (cIndividual*)NULL ); "<<endl;
	algorithmBasic1.setOriginalIndividual( (cIndividual*)NULL );

	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividual() == NULL ){
	
		cout<<"The Fib individual of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib individual of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividual() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalFibObject() == NULL ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalFibObject() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividualRoot() == NULL ){
	
		cout<<"The original Fib object roots of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object roots of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividualRoot() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check getBestFitness()
	if ( algorithmBasic1.getBestFitness() != NULL ){
		if ( bestFitness == *(algorithmBasic1.getBestFitness()) ){
			cout<<"The best fitness is correctly equal to bestFitness . "<<endl;
		}else{
			cerr<<"Error: The best fitness is not equal to bestFitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The best fitness is NULL."<<endl;
		iReturn++;
	}
	//check getWorstCaseFitness()
	if ( algorithmBasic1.getWorstCaseFitness() == NULL ){
		cout<<"The worst case fitness is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The worst case fitness is not NULL."<<endl;
		iReturn++;
	}


	cout<<endl<<"algorithmBasic1.setOriginalIndividual( &originalIndividual3 ); "<<endl;
	algorithmBasic1.setOriginalIndividual( &originalIndividual3 );

	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividual() != NULL ){
		if ( algorithmBasic1.getOriginalIndividual() == &originalIndividual3 ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly originalIndividual3 . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic1.getOriginalIndividual() <<" but should be originalIndividual3 ."<<endl;
			iReturn++;
		}
		if ( algorithmBasic1.getOriginalIndividual()->getFibObject() == &rootTree ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly rootTree . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic1.getOriginalFibObject() <<" but should be rootTree ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm NULL but should be rootTree="<< &rootTree <<" ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalFibObject() == &rootTree ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly rootTree . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalFibObject() <<" but should be rootTree ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividualRoot() != NULL ){
		if ( rootTreeEmpty.equal( *(algorithmBasic1.getOriginalIndividualRoot() ) ) ){
		
			cout<<"The original Fib object roots of the fitnessalgorithm is correctly equal to rootTreeEmpty . "<<endl;
		}else{
			cerr<<"Error: The original Fib object roots of the fitnessalgorithm is "<<
				algorithmBasic1.getOriginalIndividualRoot() <<" and not equal to rootTreeEmpty ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The original Fib object roots of the fitnessalgorithm is "<<
			algorithmBasic1.getOriginalIndividualRoot() <<" but should be equal to rootTreeEmpty ."<<endl;
		iReturn++;
	}
	//check getBestFitness()
	if ( algorithmBasic1.getBestFitness() != NULL ){
		if ( bestFitness == *(algorithmBasic1.getBestFitness()) ){
			cout<<"The best fitness is correctly equal to bestFitness . "<<endl;
		}else{
			cerr<<"Error: The best fitness is not equal to bestFitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The best fitness is NULL."<<endl;
		iReturn++;
	}
	//check getWorstCaseFitness()
	if ( algorithmBasic1.getWorstCaseFitness() != NULL ){
		
		cFibObjectFitnessBasic * pWorstCaseFitness = algorithmBasic1.
			evalueFitness( originalIndividual3 );
		if ( pWorstCaseFitness ){
			if ( (*pWorstCaseFitness) == *(algorithmBasic1.getWorstCaseFitness()) ){
				cout<<"The worst case fitness is correctly the fitness of the original."<<endl;
			}else{
				cerr<<"Error: The worst case fitness is not the fitness of the original."<<endl;
				iReturn++;
			}
			delete pWorstCaseFitness;
		}else{
			cerr<<"Error: Couldn't evalue the worst case fitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The worst case fitness is NULL."<<endl;
		iReturn++;
	}


	cout<<endl<<"algorithmBasic1.setOriginalIndividual( (cFibIndividual*)NULL ); "<<endl;
	algorithmBasic1.setOriginalIndividual( (cFibIndividual*)NULL );

	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividual() == NULL ){
	
		cout<<"The Fib individual of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib individual of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividual() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalFibObject() == NULL ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalFibObject() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividualRoot() == NULL ){
	
		cout<<"The original Fib object roots of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object roots of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividualRoot() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check getBestFitness()
	if ( algorithmBasic1.getBestFitness() != NULL ){
		if ( bestFitness == *(algorithmBasic1.getBestFitness()) ){
			cout<<"The best fitness is correctly equal to bestFitness . "<<endl;
		}else{
			cerr<<"Error: The best fitness is not equal to bestFitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The best fitness is NULL."<<endl;
		iReturn++;
	}
	//check getWorstCaseFitness()
	if ( algorithmBasic1.getWorstCaseFitness() == NULL ){
		cout<<"The worst case fitness is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The worst case fitness is not NULL."<<endl;
		iReturn++;
	}

	cout<<endl<<"algorithmBasic1.setOriginalFibObject( &rootTree ); "<<endl;
	algorithmBasic1.setOriginalFibObject( &rootTree );

	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividual() != NULL ){
		if ( algorithmBasic1.getOriginalIndividual()->getFibObject() == &rootTree ){
		
			cout<<"The original Fib object of the fitnessalgorithm is correctly rootTree . "<<endl;
		}else{
			cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
				algorithmBasic1.getOriginalFibObject() <<" but should be rootTree ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The classname of the fitnessalgorithm NULL but should be rootTree="<< &rootTree <<" ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalFibObject() == &rootTree ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly rootTree . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalFibObject() <<" but should be rootTree ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividualRoot() != NULL ){
		if ( rootTreeEmpty.equal( *(algorithmBasic1.getOriginalIndividualRoot() ) ) ){
		
			cout<<"The original Fib object roots of the fitnessalgorithm is correctly equal to rootTreeEmpty . "<<endl;
		}else{
			cerr<<"Error: The original Fib object roots of the fitnessalgorithm is "<<
				algorithmBasic1.getOriginalIndividualRoot() <<" and not equal to rootTreeEmpty ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The original Fib object roots of the fitnessalgorithm is "<<
			algorithmBasic1.getOriginalIndividualRoot() <<" but should be equal to rootTreeEmpty ."<<endl;
		iReturn++;
	}
	//check getBestFitness()
	if ( algorithmBasic1.getBestFitness() != NULL ){
		if ( bestFitness == *(algorithmBasic1.getBestFitness()) ){
			cout<<"The best fitness is correctly equal to bestFitness . "<<endl;
		}else{
			cerr<<"Error: The best fitness is not equal to bestFitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The best fitness is NULL."<<endl;
		iReturn++;
	}
	//check getWorstCaseFitness()
	if ( algorithmBasic1.getWorstCaseFitness() != NULL ){
		
		cFibObjectFitnessBasic * pWorstCaseFitness = algorithmBasic1.
			evalueFitness( originalIndividual3 );
		if ( pWorstCaseFitness ){
			if ( (*pWorstCaseFitness) == *(algorithmBasic1.getWorstCaseFitness()) ){
				cout<<"The worst case fitness is correctly the fitness of the original."<<endl;
			}else{
				cerr<<"Error: The worst case fitness is not the fitness of the original."<<endl;
				iReturn++;
			}
			delete pWorstCaseFitness;
		}else{
			cerr<<"Error: Couldn't evalue the worst case fitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The worst case fitness is NULL."<<endl;
		iReturn++;
	}


	cout<<endl<<"algorithmBasic1.setOriginalFibObject( NULL ); "<<endl;
	algorithmBasic1.setOriginalFibObject( NULL );

	//check the getOriginalIndividual() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividual() == NULL ){
	
		cout<<"The Fib individual of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib individual of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividual() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalFibObject() == NULL ){
	
		cout<<"The original Fib object of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalFibObject() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the getOriginalFibObject() methode from cFibObjectFitnessBasicAlgorithm
	if ( algorithmBasic1.getOriginalIndividualRoot() == NULL ){
	
		cout<<"The original Fib object roots of the fitnessalgorithm is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The original Fib object roots of the fitnessalgorithm "<<
			algorithmBasic1.getOriginalIndividualRoot() <<" but should be NULL ."<<endl;
		iReturn++;
	}
	//check getBestFitness()
	if ( algorithmBasic1.getBestFitness() != NULL ){
		if ( bestFitness == *(algorithmBasic1.getBestFitness()) ){
			cout<<"The best fitness is correctly equal to bestFitness . "<<endl;
		}else{
			cerr<<"Error: The best fitness is not equal to bestFitness."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The best fitness is NULL."<<endl;
		iReturn++;
	}
	//check getWorstCaseFitness()
	if ( algorithmBasic1.getWorstCaseFitness() == NULL ){
		cout<<"The worst case fitness is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The worst case fitness is not NULL."<<endl;
		iReturn++;
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

	return -1 * ( fitness.getDifferenceToOriginal() * fitness.getWeightDistanceToOriginal() +
		(double)(fitness.getSize()) * fitness.getWeightSize() +
		(double)(fitness.getTime()) * fitness.getWeightEvaluationTime() );
}



/**
 * This method tests the constructors of the cFibObjectFitnessBasicAlgorithm class.
 *
 * methods tested:
 * 	- cObjectFitness * evalueFitness( const cIndividual & individual ) const;
 * 	- cFibObjectFitness * evalueFitness( const cFibIndividual & individual ) const;
 * 	- cFibObjectFitness * evalueFitness( const cFibElement * fibObject ) const;
 * 	- double evalueDistance( const cFibElement *fibElement, const cFibElement *fibElementArea=NULL  ) const;
 * 	- double evalueDistance( list< pair< cVectorPosition, list< cVectorProperty > > > & liPointWithProperties ) const;
 * 	- double evalueDistanceInArea( list< pair< cVectorPosition, list< cVectorProperty > > > & liPointWithProperties, list< pair< cVectorPosition, list< cVectorProperty > > > liPointWithPropertiesOfArea ) const;
 * 	- const cFibObjectFitnessBasic * getBestFitness() const;
 * 	- const cFibObjectFitnessBasic * getWorstCaseFitness() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testEvalue( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cFibObjectFitnessBasicAlgorithm"<<endl;

	//load the testfolder list
	string szFilePath = string( pDirTestObjects ) + FILE_TESTOBJECTS;
	
	cout<<endl<<"Loading testfolders from the file: "<<szFilePath<<endl;
	list< string > liTestfolders = loadTestFolderList( szFilePath );
	if ( liTestfolders.empty() ){
		cerr<<"Error: No testfolders to test."<<endl;
		iReturn++;
		return iReturn;
	}

	for ( list< string >::iterator itrTestFolder = liTestfolders.begin();
			itrTestFolder != liTestfolders.end(); itrTestFolder++ ){
		
		const string szActualTestFolder = *itrTestFolder;
		ulTestphase++;
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the Fib object in folder \""<< szActualTestFolder <<"\""<<endl;
		
		const string szActualTestPath = string( pDirTestObjects ) +
			szActualTestFolder + "/";
		//load original Fib object
		const string szOriginalFile = szActualTestFolder + ".xml";
		
		const string szPathOriginalFibObject = szActualTestPath + szOriginalFile;
		ifstream inFile( szPathOriginalFibObject.c_str() );
		
		intFib outStatus = 0;
		cFibElement * pOriginalFibObject = cFibElement::restoreXml( inFile , &outStatus );
		
		if ( (outStatus == 0) && (pOriginalFibObject != NULL) ){
			cout<<"Restoring original Fib object in the Xml -format from the file "<<
				szPathOriginalFibObject <<" successfull. "<<endl;
		}else{
			cerr<<"Error: Restoring originalFib object in the Xml -format from the file "<<
				szPathOriginalFibObject <<" not successfull. (return status="<< outStatus <<")"<<endl;
			iReturn++;
			if ( pOriginalFibObject ){
				pOriginalFibObject->deleteObject();
			}
			continue;
		}
		
		//evalue the files in the testfolder
		list< string > liTestFiles = loadTestFileList( szActualTestPath );
		
		for ( list< string >::iterator itrTestFile = liTestFiles.begin();
				itrTestFile != liTestFiles.end(); itrTestFile++ ){
			
			if ( itrTestFile->compare ( itrTestFile->size() - 4, 4, ".xml" ) != 0 ){
				//skip non "*.xml" files
				continue;
			}
			
			cout<<endl<<"Checking fitness of Fib object in file "<< (*itrTestFile) <<endl;
			
			double dDistanceToOriginal = 0;
			cFibElement * pCompareFibObject = NULL;
			if ( szOriginalFile == *itrTestFile ){
				pCompareFibObject = pOriginalFibObject;
			}else{
		
				//load the Fib object to compare with
				const string szPathCompareFibObject = szActualTestPath + (*itrTestFile);
				ifstream inFileCompareFibObject( szPathCompareFibObject.c_str() );
				
				outStatus = 0;
				pCompareFibObject = cFibElement::restoreXml( inFileCompareFibObject , &outStatus );
				
				if ( (outStatus != 0) || (pCompareFibObject == NULL) ){
					cerr<<"Error: Restoring  compare to Fib object in the Xml -format from the file "<<
						szPathCompareFibObject <<" not successfull. (return status="<< outStatus <<")"<<endl;
					iReturn++;
					if ( pCompareFibObject ){
						cFibElement::deleteObject( pCompareFibObject );
					}
					continue;
				}
		
				//load the fitnessvalues for the Fib object to compare with
				const list< pair<string,string> > liPaDistance = ((cRoot*)pCompareFibObject)->
					getOptionalPart()->getEntries( "cFibObjectFitnessBasic.distance" );
				
				if ( liPaDistance.empty() ){
					cerr<<"Error: Couldn't restore a distance for the Fib objecte to the original Fib object."<<endl;
					iReturn++;
					if ( pCompareFibObject ){
						cFibElement::deleteObject( pCompareFibObject );
					}
					continue;
				}
				dDistanceToOriginal = atof( liPaDistance.front().second.c_str() );
			}
			//evalue size and time of the Fib object to compare with
			const unsigned long long ulSize = pCompareFibObject->getCompressedSize();
			const unsigned long long ulTime = pCompareFibObject->getTimeNeed();
			
			cout<<"correct: distance to original="<< dDistanceToOriginal <<
				"  size="<<ulSize<<"  evaluetime="<< ulTime <<endl;
			//evalue the fitness of the Fib object
			double dWeightDistanceToOriginal = (double)(rand() % 65536) / 256.0;
			double dWeightSize = (double)(rand() % 65536) / 256.0;
			double dWeightTime = (double)(rand() % 65536) / 256.0;
	
			cout<<"cFibObjectFitnessBasicAlgorithm algorithmBasic1( "<<
				pOriginalFibObject <<", "<< dWeightDistanceToOriginal <<", "<<
				dWeightSize <<", "<< dWeightTime <<" );"<<endl;
			cFibObjectFitnessBasicAlgorithm algorithmBasic1( pOriginalFibObject, 
				dWeightDistanceToOriginal, dWeightSize, dWeightTime );
			
			const cFibObjectFitnessBasic fitnessDummy( 1.0, 5, 8 );
			const list<cIndividualIdentifier> liParents;
			
			const cFibIndividual pCompareIndividual( pCompareFibObject,
				cIndividualInfo( 0, liParents, fitnessDummy,
				"compareIndividual", "", cOperationIdentifier( 0 ),
				time_t( NULL ), 0.0, &fitnessDummy ), false );
			
			//check evalueDistance on whool area
			cout<<"dEvaluedDistance = algorithmBasic1.evalueDistance( pCompareFibObject ); . "<<endl;
			double dEvaluedDistance = algorithmBasic1.evalueDistance( pCompareFibObject );
			//check the getDifferenceToOriginal() methode from cFibObjectFitnessBasic
			if ( dEvaluedDistance == dDistanceToOriginal ){
			
				cout<<"The differnes to the original value of the fitness is correctly "<<
					dDistanceToOriginal <<" . "<<endl;
			}else{
				cerr<<"Error: The differnes to the original value of the fitness is "<<
					dEvaluedDistance <<" but should be "<<
					dDistanceToOriginal <<" ."<<endl;
				iReturn++;
			}
			//test evalueDistance( list< pair< cVectorPosition, list< cVectorProperty > > > & liPointWithProperties )
			cEvaluePositionList evaluePositionList;
			bool bObjectEvalued = pCompareFibObject->evalueObjectSimple( evaluePositionList );
			if ( ! bObjectEvalued ){
				cerr<<"Error: The to compare with Fib object couldn't be evalued."<<endl;
				iReturn++;
			}
			if ( (rand()) % 2 == 0 ){
				cout<<"dEvaluedDistance = algorithmBasic1.evalueDistance( "<<
					"evaluePositionList.liEvaluedPositionData ); "<<endl;
				dEvaluedDistance = algorithmBasic1.evalueDistance(
					evaluePositionList.liEvaluedPositionData );
			}else{//use new algorithm
				cFibObjectFitnessBasicAlgorithm algorithmBasic2( pOriginalFibObject,
					dWeightDistanceToOriginal, dWeightSize, dWeightTime );
				
				cout<<"dEvaluedDistance = algorithmBasic2.evalueDistance( "<<
					"evaluePositionList.liEvaluedPositionData ); "<<endl;
				dEvaluedDistance = algorithmBasic2.evalueDistance(
					evaluePositionList.liEvaluedPositionData );
			}
			if ( dEvaluedDistance == dDistanceToOriginal ){
			
				cout<<"The differnes to the original value of the fitness is correctly "<<
					dDistanceToOriginal <<" . "<<endl;
			}else{
				cerr<<"Error: The differnes to the original value of the fitness is "<<
					dEvaluedDistance <<" but should be "<<
					dDistanceToOriginal <<" ."<<endl;
				iReturn++;
			}
			
			//evalue for given areas
			const list< pair<string,string> > liPaDistanceAreas = ((cRoot*)pCompareFibObject)->
				getOptionalPart()->getEntries( "cFibObjectFitnessBasic.distance.", false );
			for ( list< pair<string,string> >::const_iterator itrSubarea = liPaDistanceAreas.begin();
					itrSubarea != liPaDistanceAreas.end(); itrSubarea++ ){
				
				//load the subarea with
				const string szPathSubareaFibObject = szActualTestPath +
					&((itrSubarea->first.c_str())[ 32 ]);
				cout<<"Checking distance for the subarea from file "<< szPathSubareaFibObject <<endl;
				ifstream inFileSubareaFibObject( szPathSubareaFibObject.c_str() );
				
				outStatus = 0;
				cFibElement * pSubareaFibObject = cFibElement::restoreXml( inFileSubareaFibObject , &outStatus );
				
				if ( (outStatus != 0) || (pSubareaFibObject == NULL) ){
					cerr<<"Error: Restoring  compare to Fib object in the Xml -format from the file "<<
						szPathSubareaFibObject <<" not successfull. (return status="<< outStatus <<")"<<endl;
					iReturn++;
					if ( pSubareaFibObject ){
						cFibElement::deleteObject( pSubareaFibObject );
					}
					continue;
				}
				const double dDistanceToOriginalInArea = atof( itrSubarea->second.c_str() );
				double dEvaluedDistanceArea = algorithmBasic1.evalueDistance(
					pCompareFibObject, pSubareaFibObject );
				//check the getDifferenceToOriginal() methode from cFibObjectFitnessBasic
				if ( dEvaluedDistanceArea == dDistanceToOriginalInArea ){
				
					cout<<"The differnes to the original value of the fitness is correctly "<<
						dDistanceToOriginalInArea <<" . "<<endl;
				}else{
					cerr<<"Error: The differnes to the original value of the fitness is "<<
						dEvaluedDistanceArea <<" but should be "<<
						dDistanceToOriginalInArea <<" ."<<endl;
					iReturn++;
				}

				//test evalueDistanceInArea( liPointWithProperties, liPointWithPropertiesOfArea );
				evaluePositionList.clear();
				bool bObjectEvalued = pCompareFibObject->evalueObjectSimple( evaluePositionList );
				if ( ! bObjectEvalued ){
					cerr<<"Error: The to compare with Fib object couldn't be evalued."<<endl;
					iReturn++;
				}
				cEvaluePositionList evaluePositionListSubarea;
				bObjectEvalued = pSubareaFibObject->evalueObjectSimple( evaluePositionListSubarea );
				if ( ! bObjectEvalued ){
					cerr<<"Error: The area Fib object couldn't be evalued."<<endl;
					iReturn++;
				}
				if ( (rand()) % 2 == 0 ){
					cout<<"dEvaluedDistanceArea = algorithmBasic1.evalueDistanceInArea( "<<
						"evaluePositionList.liEvaluedPositionData, evaluePositionListSubarea.liEvaluedPositionData ); "<<endl;
					dEvaluedDistanceArea = algorithmBasic1.evalueDistanceInArea(
						evaluePositionList.liEvaluedPositionData, evaluePositionListSubarea.liEvaluedPositionData );
				}else{//use new algorithm
					cFibObjectFitnessBasicAlgorithm algorithmBasic2( pOriginalFibObject,
						dWeightDistanceToOriginal, dWeightSize, dWeightTime );
					
					cout<<"dEvaluedDistanceArea = algorithmBasic2.evalueDistanceInArea( "<<
						"evaluePositionList.liEvaluedPositionData, evaluePositionListSubarea.liEvaluedPositionData ); "<<endl;
					dEvaluedDistanceArea = algorithmBasic2.evalueDistanceInArea(
						evaluePositionList.liEvaluedPositionData, evaluePositionListSubarea.liEvaluedPositionData );
				}
				if ( dEvaluedDistanceArea == dDistanceToOriginalInArea ){
				
					cout<<"The differnes to the original value of the fitness is correctly "<<
						dDistanceToOriginalInArea <<" . "<<endl;
				}else{
					cerr<<"Error: The differnes to the original value of the fitness is "<<
						dEvaluedDistanceArea <<" but should be "<<
						dDistanceToOriginalInArea <<" ."<<endl;
					iReturn++;
				}
				if ( pSubareaFibObject ){
					cFibElement::deleteObject( pSubareaFibObject );
				}
			}
			
			//check if the fitness is correct
			cFibObjectFitnessBasic * pFibObjectFitness = NULL;
			for ( unsigned int uiMethod = 1; uiMethod <= 3; uiMethod++ ){
				
				switch( uiMethod ){
					case 1:{
						pFibObjectFitness = (cFibObjectFitnessBasic*)( algorithmBasic1.
							evalueFitness( *((cIndividual*)&pCompareIndividual) ) );
					}break;
					case 2:{
						pFibObjectFitness = (cFibObjectFitnessBasic*)(
							algorithmBasic1.evalueFitness( pCompareIndividual ) );
					}break;
					case 3:{
						pFibObjectFitness = (cFibObjectFitnessBasic*)(
							algorithmBasic1.evalueFitness( pCompareFibObject ) );
					}break;
				}
				if ( pFibObjectFitness == NULL ){
					cerr<<"Error: No fitness could be evalued with method "<< uiMethod <<" ."<<endl;
					iReturn++;
					continue;
				}
				if ( pFibObjectFitness->getClassName() != "cFibObjectFitnessBasic" ){
					cerr<<"Error: The classname of the returned fitness is "<<
						pFibObjectFitness->getClassName() <<", but should be \"cFibObjectFitnessBasic\" ."<<endl;
					iReturn++;
				}
				//check the getFitnessAlgorithm() methode from cFibObjectFitnessBasic
				if ( pFibObjectFitness->getFitnessAlgorithm() != &algorithmBasic1 ){
					cerr<<"Error: The algorithm of the fitness is "<<
						pFibObjectFitness->getFitnessAlgorithm() <<" but should be "<<
						&algorithmBasic1 <<" (method="<< uiMethod <<")."<<endl;
					iReturn++;
				}
				//check the getDifferenceToOriginal() methode from cFibObjectFitnessBasic
				if ( pFibObjectFitness->getDifferenceToOriginal() != dDistanceToOriginal ){
					cerr<<"Error: The differnes to the original value of the fitness is "<<
						pFibObjectFitness->getDifferenceToOriginal() <<" but should be "<<
						dDistanceToOriginal <<" (method="<< uiMethod <<")."<<endl;
					iReturn++;
				}
				//check the getWeightDistanceToOriginal() methode from cFibObjectFitnessBasic
				if ( pFibObjectFitness->getWeightDistanceToOriginal() != dWeightDistanceToOriginal ){
					cerr<<"Error: The weight for the differnes to the original of the fitness is "<<
						pFibObjectFitness->getWeightDistanceToOriginal() <<" but should be "<<
						dWeightDistanceToOriginal <<" (method="<< uiMethod <<")."<<endl;
					iReturn++;
				}
				//check the getSize() methode from cFibObjectFitnessBasic
				if ( pFibObjectFitness->getSize() != ulSize ){
					cerr<<"Error: The size of the Fib object of the fitness is "<<
						pFibObjectFitness->getSize() <<" but should be "<< ulSize <<
						" (method="<< uiMethod <<")."<<endl;
					iReturn++;
				}
				//check the getWeightSize() methode from cFibObjectFitnessBasic
				if ( pFibObjectFitness->getWeightSize() != dWeightSize ){
					cerr<<"Error: The weight size of the Fib object of the fitness is "<<
						pFibObjectFitness->getWeightSize() <<" but should be "<<
						dWeightSize <<" (method="<< uiMethod <<")."<<endl;
					iReturn++;
				}
				//check the getTime() methode from cFibObjectFitnessBasic
				if ( pFibObjectFitness->getTime() != ulTime ){
					cerr<<"Error: The evaluation time of the Fib object of the fitness is "<<
						pFibObjectFitness->getTime() <<" but should be "<< ulTime <<
						" (method="<< uiMethod <<")."<<endl;
					iReturn++;
				}
				//check the getWeightEvaluationTime() methode from cFibObjectFitnessBasic
				if ( pFibObjectFitness->getWeightEvaluationTime() != dWeightTime ){
					cerr<<"Error: The weight evaluation time of the Fib object of the fitness is "<<
						pFibObjectFitness->getWeightEvaluationTime() <<
						" but should be "<< dWeightTime <<" (method="<< uiMethod <<")."<<endl;
					iReturn++;
				}
				//check the getFitness() methode from cFibObjectFitnessBasic
				if ( pFibObjectFitness->getFitness() != evalueFitness( *pFibObjectFitness ) ){
					cerr<<"Error: The fitnessvalue is "<< pFibObjectFitness->getFitness() <<
						" but should be "<< evalueFitness( *pFibObjectFitness ) <<
						" (method="<< uiMethod <<")."<<endl;
					iReturn++;
				}
				
				if ( pCompareFibObject == pOriginalFibObject ){
					
					const cFibObjectFitnessBasic bestFitness( 0.0, 0, 0,
						dWeightDistanceToOriginal, dWeightSize, dWeightTime );
					
					//check getBestFitness()
					if ( algorithmBasic1.getBestFitness() != NULL ){
						if ( ! (bestFitness == *(algorithmBasic1.getBestFitness())) ){
							cerr<<"Error: The best fitness is incorrect."<<endl;
							iReturn++;
						}
					}else{
						cerr<<"Error: The best fitness is NULL."<<endl;
						iReturn++;
					}
					//check getWorstCaseFitness()
					if ( algorithmBasic1.getWorstCaseFitness() != NULL ){
						if ( ! ((*pFibObjectFitness) == *(algorithmBasic1.getWorstCaseFitness())) ){
							cerr<<"Error: The worst case fitness is incorrect."<<endl;
							iReturn++;
						}
					}else{
						cerr<<"Error: The worst case fitness is NULL."<<endl;
						iReturn++;
					}
				}
				delete pFibObjectFitness;
			}
			if ( ( pCompareFibObject != NULL ) && ( pCompareFibObject != pOriginalFibObject) ){
				cFibElement::deleteObject( pCompareFibObject );
			}
		}
		if ( pOriginalFibObject ){
			cFibElement::deleteObject( pOriginalFibObject );
		}
	}

	return iReturn;
}




/**
 * This function reads the given file and returns a list with its lines.
 * The lines in the files should be the subfolders to check.
 *
 * @param szFilePath the path wher the folderlist to check is stored;
 * 	each folder to check is writen in a seperate line
 * @return a list with the folders to check
 */
list< string > loadTestFolderList( const string szFilePath ){
	
	list< string > liFolders;
	
	ifstream ifStream( szFilePath.c_str() );
	
	if ( ! ifStream.good() ){
		
		cerr<<"Error: Couldn't read the folder list "<< szFilePath <<endl;
		return liFolders;
	}
	char szBuffer[ 1024 ];
	
	while( ifStream.good() ){
	
		ifStream.getline( szBuffer, 1024 );
		string szFolder( szBuffer );
		if ( szFolder != "" ){
			liFolders.push_back( szFolder );
		}
	}
	return liFolders;
}


/**
 * This function reads the given directory and gives back all filenames
 * of files it contains.
 * This files should be used as a testcase.
 *
 * @param szTestFolderName the name of the folder, which contains the files
 * 	with the testdata
 * @return the list of files in the given folder
 */
list< string > loadTestFileList( const string szTestFolderName ){
	
	cFolder folder( szTestFolderName );
	
	return folder.getFiles();
}








