/**
 * @file runOperation
 * file name: runOperation.cpp
 * @author Betti Oesterholz
 * @date 17.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This programm runs a operator.
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
 * This programm runs a operator with the given fib -object in the
 * enviroment.
 *
 *
 * call: runOperation OPERATOR_TO_RUN FILE_FIB_OBJECT [FILE_FIB_OBJECT_WORK]
 *
 * parameters:
 * 	OPERATOR_TO_RUN
 * 		The operator (class-)name to run
 * 	FILE_FIB_OBJECT
 * 		The path to the to load fib -multimediadata /-object to insert
 * 		as the original fib -object into the enviroment.
 * 	FILE_FIB_OBJECT_WORK
 * 		The path to the to load fib -multimediadata /-object to insert
 * 		as into the enviroment, on which the operation should work.
 * 		If no is given the FILE_FIB_OBJECT fib -objec will be inserted.
 */
/*
History:
17.06.2010  Oesterholz  created
22.10.2010  Oesterholz  parameter FILE_FIB_OBJECT_WORK added
29.03.2011  Oesterholz  storing to and restoring from binary stream
*/

#include "version.h"
#include "cFibElement.h"
#include "cRoot.h"

#include "cEnviroment.h"
#include "cOperatorFitnessAlgorithm.h"
#include "cInitFibEnviroment.h"
#include "cFibObjectFitnessBasicAlgorithm.h"
#include "cEndConditionCheck.h"
#include "cFibIndividual.h"

#include <string>
#include <iostream>
#include <fstream>




using namespace fib;
using namespace std;
using namespace enviroment::fib;
using namespace enviroment;


int main(int argc, char* argv[]){
	
	
	//loading the parameter
	//the name of the operator to run
	char * pOperatorName = NULL;
	//the name of the file with the fib -object to load
	char * pFileWithOriginalData = NULL;
	//the name of the file with the fib -object to load, ob wich the operation should work
	char * pFileWithWorkFibObject = NULL;
	
	if ( argc < 3 ){
		//no input file -> exit
		cout<<"No operator and / or inputfile specified."<<endl;
		cout<<" call: runOperation OPERATOR_TO_RUN FILE_FIB_OBJECT [FILE_FIB_OBJECT_WORK]"<<endl;
		cout<<endl;
		cout<<" parameters:"<<endl;
		cout<<" 	OPERATOR_TO_RUN"<<endl;
		cout<<" 		The operator (class-)name to run"<<endl;
		cout<<" 	FILE_FIB_OBJECT"<<endl;
		cout<<" 		The path to the to load fib -multimediadata /-object to insert"<<endl;
		cout<<" 		as the original fib -object into the enviroment."<<endl;
		cout<<" 	FILE_FIB_OBJECT_WORK"<<endl;
		cout<<" 		The path to the to load fib -multimediadata /-object to insert"<<endl;
		cout<<" 		as into the enviroment, on which the operation should work."<<endl;
		cout<<" 		If no is given the FILE_FIB_OBJECT fib -objec will be inserted."<<endl;
		cout<<endl;
		return 1;
	}
	pOperatorName = argv[1];
	pFileWithOriginalData = argv[2];
	if ( 4 <= argc ){
		pFileWithWorkFibObject = argv[3];
	}else{
		pFileWithWorkFibObject = pFileWithOriginalData;
	}
	
	double dInWeightDistanceToOriginal = 1.0;
	double dInWeightSize = 1.0;
	double dInWeightEvaluationTime = 1.0;
	
	//restoring the original fib -object
	cFibElement * pRestoredFibObject = NULL;
	
	if ( strcmp( & (pFileWithOriginalData[
			strlen( pFileWithOriginalData ) - 4 ]), ".xml") == 0 ){
		//restore to file in xml -format
		ifstream inFile( pFileWithOriginalData );
		intFib outStatus = 0;
	
		pRestoredFibObject = cFibElement::restoreXml( inFile , &outStatus );
		
		if ( outStatus == 0 ){
			cout<<"Restoring original fib -object in the Xml -format from the file \""<<
				pFileWithOriginalData <<"\" successfull. "<<endl;
		}else{
			cerr<<"Restoring original fib -object in the Xml -format from the file \""<<
				pFileWithOriginalData <<"\" not successfull. (return status="<< outStatus <<")"<<endl;
			return 1;
		}
	}else{//restore to file in compressedformat
		ifstream inFile( pFileWithOriginalData, ios_base::in | ios_base::binary );
		intFib outStatus = 0;
		
		pRestoredFibObject = cFibElement::restore( inFile , &outStatus );
		
		if ( outStatus == 0 ){
			cout<<"Restoring original fib -object in the compressedformat from the file \""<<
				pFileWithOriginalData <<"\" successfull. "<<endl;
		}else{
			cerr<<"Restoring original fib -object in the compressedformat from the file \""<<
				pFileWithOriginalData <<"\" not successfull. (return status="<< outStatus <<")"<<endl;
			return 1;
		}
	}
	
	if ( (pRestoredFibObject == NULL) || (pRestoredFibObject->getType() != 'r') ){
		cerr<<"No original fib -multimediaobjects."<<endl;
		return 2;
	}
	
	//restoring the original fib -object
	cFibElement * pRestoredWorkFibObject = NULL;
	
	if ( pFileWithWorkFibObject != pFileWithOriginalData ){
	
		if ( strcmp( & (pFileWithWorkFibObject[
				strlen( pFileWithWorkFibObject ) - 4 ]), ".xml") == 0 ){
			//restore to file in xml -format
			ifstream inFileWork( pFileWithWorkFibObject );
			intFib outStatus = 0;
		
			pRestoredWorkFibObject = cFibElement::restoreXml( inFileWork , &outStatus );
			
			if ( outStatus == 0 ){
				cout<<"Restoring original fib -object in the Xml -format from the file \""<<
					pFileWithWorkFibObject <<"\" successfull. "<<endl;
			}else{
				cerr<<"Restoring original fib -object in the Xml -format from the file \""<<
					pFileWithWorkFibObject <<"\" not successfull. (return status="<< outStatus <<")"<<endl;
				if ( pRestoredFibObject != NULL ){
					cFibElement::deleteObject( pRestoredFibObject );
				}
				return 1;
			}
		}else{//restore to file in compressedformat
			ifstream inFileWork( pFileWithWorkFibObject, ios_base::in | ios_base::binary );
			intFib outStatus = 0;
		
			pRestoredWorkFibObject = cFibElement::restore( inFileWork , &outStatus );
			
			if ( outStatus == 0 ){
				cout<<"Restoring original fib -object in the compressedformat from the file \""<<
					pFileWithWorkFibObject <<"\" successfull. "<<endl;
			}else{
				cerr<<"Restoring original fib -object in the compressedformat from the file \""<<
					pFileWithWorkFibObject <<"\" not successfull. (return status="<< outStatus <<")"<<endl;
				if ( pRestoredFibObject != NULL ){
					cFibElement::deleteObject( pRestoredFibObject );
				}
				return 1;
			}
		}
	}else{
		pRestoredWorkFibObject = pRestoredFibObject;
	}

	//running the enviroment
	
	cout<<"cInitFibEnviroment initEnviroment( *((cRoot*)pRestoredFibObject) ); "<<endl;
	cInitFibEnviroment initEnviroment(  *((cRoot*)pRestoredFibObject) );
	
	cout<<"cFibObjectFitnessBasicAlgorithm fibObjectAlgorithmBasic( pRestoredFibObject, "<<
		dInWeightDistanceToOriginal <<", "<< dInWeightSize <<", "<< dInWeightEvaluationTime <<" );"<<endl;
	cFibObjectFitnessBasicAlgorithm fibObjectAlgorithmBasic( pRestoredFibObject,
		dInWeightDistanceToOriginal, dInWeightSize, dInWeightEvaluationTime );
	
	cout<<"cEndConditionCheck endCondition;"<<endl;
	cEndConditionCheck endCondition;
	
	cout<<"cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic, &endCondition );"<<endl;
	cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic, &endCondition );
	
	cout<<"cEnviroment * pEnviroment = cEnviroment::getInstance(); "<<endl;
	cEnviroment * pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment == NULL ){
		cerr<<"Error: An instance of the enviroment could not be created."<<endl;
		if ( pRestoredFibObject != NULL ){
			cFibElement::deleteObject( pRestoredFibObject );
		}
		if ( ( pRestoredWorkFibObject != NULL ) &&
				( pFileWithWorkFibObject != pFileWithOriginalData ) ){
			cFibElement::deleteObject( pRestoredWorkFibObject );
		}
		return 3;
	}
	
	//get the operation to run
	cout<<"pOpFitnessAlgorithm = pEnviroment->getOperatorFitnessAlgorithm(); "<<endl;
	cOperatorFitnessAlgorithm * pOpFitnessAlgorithm =
		pEnviroment->getOperatorFitnessAlgorithm();
	
	if ( pOpFitnessAlgorithm == NULL ){
		//nothing to select from
		if ( pRestoredFibObject != NULL ){
			cFibElement::deleteObject( pRestoredFibObject );
		}
		if ( ( pRestoredWorkFibObject != NULL ) &&
				( pFileWithWorkFibObject != pFileWithOriginalData ) ){
			cFibElement::deleteObject( pRestoredWorkFibObject );
		}
		delete pEnviroment;
		return 4;
	}
	cout<<"liOperators = pOpFitnessAlgorithm->getFitness() "<<endl;
	list< pair< const cOperation*, double > > liOperators =
		pOpFitnessAlgorithm->getFitness();
	
	if ( liOperators.empty() ){
		cerr<<"Error: No operators to run."<<endl;
		if ( pRestoredFibObject != NULL ){
			cFibElement::deleteObject( pRestoredFibObject );
		}
		if ( ( pRestoredWorkFibObject != NULL ) &&
				( pFileWithWorkFibObject != pFileWithOriginalData ) ){
			cFibElement::deleteObject( pRestoredWorkFibObject );
		}
		delete pEnviroment;
		return 4;
	}
	
	//generate the work individual
	cFibObjectFitness * pNewFitness =
		fibObjectAlgorithmBasic.evalueFitness( pRestoredWorkFibObject );
	
	const cIndividualInfo * pBestIndividualInfo = pEnviroment->getBestIndividualInfo();
	const cObjectFitness * pBestFitness = NULL;
	if ( pBestIndividualInfo ){
		pBestFitness = pBestIndividualInfo->getFitness();
	}else{
		pBestFitness = pNewFitness;
	}
	list<cIndividualIdentifier> liParents;
	
	cIndividualInfo newIndividualInfo( pEnviroment->getAlgorithmIdentifier(),
			liParents, *pNewFitness,
			"workIndividual", "", cOperationIdentifier( pEnviroment->getAlgorithmIdentifier() ),
			time_t( NULL ), 0.0,
			pBestFitness );
	
	delete pNewFitness;
	
	cFibIndividual newIndividual( pRestoredWorkFibObject, newIndividualInfo, false );

	pEnviroment->insertIndividual( &newIndividual );
	
	const cOperation * pOperatorToRun = NULL;
	for ( list< pair< const cOperation*, double > >::iterator
			itrOperation = liOperators.begin(); itrOperation != liOperators.end();
			itrOperation++ ){
		
		if ( itrOperation->first->getName().compare( pOperatorName ) == 0 ){
			//run this operator
			pOperatorToRun = itrOperation->first;
			break;
		}
	}
	if ( pOperatorToRun == NULL ){
		cerr<<"Error: Operator to run ("<< pOperatorName <<") not founded."<<endl;
		if ( pRestoredFibObject != NULL ){
			cFibElement::deleteObject( pRestoredFibObject );
		}
		if ( ( pRestoredWorkFibObject != NULL ) &&
				( pFileWithWorkFibObject != pFileWithOriginalData ) ){
			cFibElement::deleteObject( pRestoredWorkFibObject );
		}
		delete pEnviroment;
		return 5;
	}
	
	cOperation * pOperationToRun = pOperatorToRun->createInstance(
		cOperationIdentifier( pEnviroment->getAlgorithmIdentifier() ) );
	
	cout<< pOperationToRun->getName() <<"->run(); "<<endl;
	const bool bOperatorRunSuccessfull = pOperationToRun->run();
	if (! bOperatorRunSuccessfull ){
		cerr<<"Error: False was returned by the run() method."<<endl;
	}
	
	delete pOperationToRun;

//TODO move /comment out
#define OUTPUT_ALL_INDIVIDUALS

#ifdef OUTPUT_ALL_INDIVIDUALS
	const unsigned int uiNumberOfIndividuals = pEnviroment->getNumberOfIndividuals();
	cout<<"Number of Individuals in the enviroment: "<< uiNumberOfIndividuals <<endl;
	
	for ( unsigned int uiActualIndividual = 1;
			uiActualIndividual <= uiNumberOfIndividuals; uiActualIndividual++ ){
		
		cFibIndividual * pIndividualBest = ((cFibIndividual*)(pEnviroment->
			getBestIndividual( uiActualIndividual )));
		
		const cFibElement * pBestFibObject = pIndividualBest->getFibObject();
		
		char szFileName[ 256 ];
		sprintf( szFileName, "./testdata/all/best%u.fib", uiActualIndividual );
		ofstream outFile( szFileName, ios_base::out | ios_base::binary );
			
		cout<<"Storing generated "<< uiActualIndividual <<"'th best fib -object "<<
			"in the xml -format to the file "<< szFileName <<" . "<<endl;
		
		const bool bStoreSuccesfull = pBestFibObject->store( outFile );
		
		if ( ! bStoreSuccesfull ){
	
			cerr<<"Error: Storing the data of the generated best fib -object "<<
				"in the compressed -fib -format to the file "<< szFileName <<" failed."<<endl;
		}
		outFile.close();
		delete pIndividualBest;
	}
	
#endif

	if ( pRestoredFibObject != NULL ){
		cFibElement::deleteObject( pRestoredFibObject );
	}
	if ( ( pRestoredWorkFibObject != NULL ) &&
			( pFileWithWorkFibObject != pFileWithOriginalData ) ){
		cFibElement::deleteObject( pRestoredWorkFibObject );
	}
	delete pEnviroment;

	return 0;
}
















