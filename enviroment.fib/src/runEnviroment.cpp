/**
 * @file runEnviroment
 * file name: runEnviroment.cpp
 * @author Betti Oesterholz
 * @date 16.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This programm runs the enviroment on an given Fib-object.
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
 * This programm runs the enviroment on an given Fib-object.
 *
 *
 * call: runEnviroment FILE_FIB_OBJECT FOLDER_OUTPUT [MAX_ITERATIONS]
 *
 * parameters:
 * 	FILE_FIB_OBJECT
 * 		The path to the to load Fib multimedia data / object
 * 	FOLDER_OUTPUT
 * 		The path of the folder, where the evaluated best / result
 * 		Fib objects should be stored.
 * 	MAX_ITERATIONS (optional)
 * 		The maximal number of iterations / operations the environment
 * 		should perform.
 */
/*
History:
16.06.2010  Oesterholz  created
*/

#include "version.h"
#include "cFibElement.h"
#include "cRoot.h"

#include "cEnviroment.h"
#include "cInitFibEnviroment.h"
#include "cFibObjectFitnessBasicAlgorithm.h"
#include "cEndConditionCheck.h"
#include "cResourceCheck.h"
#include "cFibIndividual.h"

#include "nBalanceLists.h"

#include <string>
#include <iostream>
#include <fstream>



using namespace fib::algorithms::nTidyFibObjects::nBalanceLists;
using namespace fib;
using namespace std;
using namespace enviroment::fib;
using namespace enviroment;


//run maximal 3 operations
#define MAX_OPERATIONS_TO_RUN 3


/**
 * Listener to store the actual best individual of the enviroment.
 */
class clStoreBestIndividual :public clNewIndividualListener{
	
	/**
	 * The number of the best individual outputed.
	 */
	unsigned int uiIndividualCounter;
	
	/**
	 * The path to the folder wher to output the best individuals to.
	 */
	char * pFolderForStoringData;
	
	/**
	 * The best fitness of an individual till now.
	 * If NULL, no individual was given till now.
	 */
	cObjectFitness * pFitnessLastBest;
	
public:
	
	/**
	 * standardconstructor
	 *
	 * @param pInFolderForStoringData The path to the folder wher to output
	 * 	the best individuals to.
	 */
	clStoreBestIndividual( char * pInFolderForStoringData ):
			uiIndividualCounter( 0 ), pFitnessLastBest( NULL ){
		pFolderForStoringData = new char[ strlen( pInFolderForStoringData ) + 8 ];
		
		memcpy( pFolderForStoringData, pInFolderForStoringData,
			strlen( pInFolderForStoringData ) + 1 );
	}
	
	
	/**
	 * destructor
	 */
	~clStoreBestIndividual(){
		
		delete[] pFolderForStoringData;
		
		if ( pFitnessLastBest ){
			delete pFitnessLastBest;
		}
	}
	
	
	/**
	 * This method the given individual if it is better then the last given individual.
	 *
	 * @param pIndividual a pointer to the added individual
	 */
	virtual void individualAdded( const cIndividual * pIndividual ){
		
		//check if the individual is better
		if ( ( pIndividual == NULL ) || (pIndividual->getInfo() == NULL) ){
			//Error: no information for the given individual
			return;
		}
		const cObjectFitness * pActualFitness = pIndividual->getInfo()->getFitness();
		if ( pActualFitness == NULL ){
			//Error: no fitness for the given individual
			return;
		}
		
//		cout<<"runEnviroment got notified about new individual with fitness: "<<pActualFitness->getFitness()<<endl;
		if ( (pFitnessLastBest == NULL) || ( (*pFitnessLastBest) < (*pActualFitness) ) ){
			//output individual
			if ( pFitnessLastBest ){
				delete pFitnessLastBest;
			}
			pFitnessLastBest = pActualFitness->clone();
			uiIndividualCounter++;
			
			char szFileName[ 256 ];
			sprintf( szFileName, "%s/best%u.fib", pFolderForStoringData, uiIndividualCounter );
			cout<<"Storing generated "<< uiIndividualCounter <<"'th best Fib-object "<<
				" to the file "<< szFileName <<" . "<<endl;
			
			cFibElement * pBestFibObject = ((cFibIndividual*)pIndividual)->
				getFibObject()->clone();
			if ( pBestFibObject == NULL ){
				cerr<<"Error: Couldn't get the object of the individual."<<endl;
				return;
			}
			if ( pBestFibObject->getType() != 'r' ){
				cerr<<"Error: The Fib-object top most Fib-element is no root -element."<<endl;
				return;
			}
			((cRoot*)pBestFibObject)->generateNeededDomains();
			//storing of the origianla
			ofstream outFile( szFileName, ios_base::out | ios_base::binary );
			
			bool bStoreSuccesfull = pBestFibObject->store( outFile );
			
			if ( ! bStoreSuccesfull ){
		
				cerr<<"Error: Storing the data of the generated best Fib-object "<<
					"in the compressed -Fib-format to the file "<< szFileName <<" failed."<<endl;
			}
			outFile.close();
			
#ifdef FEATURE_RUN_ENVIROMENT_SAVE_BEST_REDUCED_LIST
			eliminateListTrees( pBestFibObject );
			sprintf( szFileName, "%s/best%uMinL.fib", pFolderForStoringData, uiIndividualCounter );
			cout<<"Storing generated list minimized "<< uiIndividualCounter <<"'th best Fib-object "<<
				" to the file "<< szFileName <<" . "<<endl;
			
			ofstream outFileML( szFileName, ios_base::out | ios_base::binary );
			
			bStoreSuccesfull = pBestFibObject->store( outFileML );
			
			if ( ! bStoreSuccesfull ){
		
				cerr<<"Error: Storing the data of the generated best Fib-object "<<
					"in the compressed -Fib-format to the file "<< szFileName <<" failed."<<endl;
			}
			outFileML.close();
#endif //FEATURE_RUN_ENVIROMENT_SAVE_BEST_REDUCED_LIST
			pBestFibObject->deleteObject();
		}
	}
	
	
	/**
	 * This method is called if an individual was delteted from the enviroment.
	 *
	 * @param pIndividual a pointer to the delteted individual
	 */
	virtual void individualRemoved( const cIndividual * pIndividual ){
		//nothing to do
	}
};




int main(int argc, char* argv[]){
	
	//loading the parameter
	char * pFileWithOriginalData = NULL;
	/*filename wher to store the Fib-object to, if NULL store in XML to
	the standartoutput*/
	char * pFolderForStoringData = NULL;
	//the maximum number of individuals to output when the enviroment is done
	unsigned long ulMaxEndIndividualsToOutput = 1000;
	
	if ( argc < 2 ){
		//no input file -> exit
		cout<<"No inputfile specified."<<endl<<endl;
		cout<<" call: runEnviroment FILE_FIB_OBJECT FILE_OUTPUT [MAX_ITERATIONS]"<<endl;
		cout<<" call: runEnviroment FILE_FIB_OBJECT FOLDER_OUTPUT [MAX_ITERATIONS]"<<endl;
		cout<<endl;
		cout<<" parameters:"<<endl;
		cout<<" 	FILE_FIB_OBJECT"<<endl;
		cout<<" 		The path to the to load Fib-multimediadata /-object"<<endl;
		cout<<" 	FOLDER_OUTPUT"<<endl;
		cout<<" 		The path of the folder, wher the evalued best /result Fib-object"<<endl;
		cout<<" 		should be stored."<<endl;
		cout<<" 	MAX_ITERATIONS (optional)"<<endl;
		cout<<" 		The maximal number of iterations / operations the enviroment"<<endl;
		cout<<" 		should perform."<<endl;
		cout<<endl;
		return 1;
	}
	pFileWithOriginalData = argv[1];
	pFolderForStoringData = argv[2];
	cout<<"The specified original multimediafile is: "<< pFileWithOriginalData <<endl;
	cout<<"The specified folder to store data into is: "<< pFolderForStoringData <<endl;
	//maximum number of iterations / operations the enviroment should perform
	unsigned long ulMaxIterations = 0;
	if ( argc >= 4 ){
		/*tree parameter given
		-> get the maximum number of iterations / operations the enviroment should perform*/
		ulMaxIterations = atol( argv[3] );
		cout<<"The specified maximal number of iterations /operation is: "<< ulMaxIterations << " ." <<endl;
	}
	
	double dInWeightDistanceToOriginal = 200.0;
	double dInWeightSize = 100.0;
	double dInWeightEvaluationTime = 1.0;
	
	//restoring the original Fib-object
	cFibElement * pRestoredFibObject = NULL;
	
	if ( strcmp( & (pFileWithOriginalData[
			strlen( pFileWithOriginalData ) - 4 ]), ".xml") == 0 ){
		//restore to file in xml -format
		ifstream inFile( pFileWithOriginalData );
		intFib outStatus = 0;
		pRestoredFibObject = cFibElement::restoreXml( inFile , &outStatus );
		
		if ( outStatus == 0 ){
			cout<<"Restoring original Fib-object in the Xml-format from the file \""<<
				pFileWithOriginalData <<"\" successfull. "<<endl;
		}else{
			cerr<<"Restoring original Fib-object in the Xml-format from the file \""<<
				pFileWithOriginalData <<"\" not successfull. (return status="<< outStatus <<")"<<endl;
			return 1;
		}
	}else{//restore to file in compressed format
		ifstream inFile( pFileWithOriginalData, ios_base::in | ios_base::binary );
		intFib outStatus = 0;
		pRestoredFibObject = cFibElement::restore( inFile , &outStatus );
		
		if ( outStatus == 0 ){
			cout<<"Restoring original Fib-object in the compressed format from the file \""<<
				pFileWithOriginalData <<"\" successfull. "<<endl;
		}else{
			cerr<<"Restoring original Fib-object in the compressed format from the file \""<<
				pFileWithOriginalData <<"\" not successfull. (return status="<< outStatus <<")"<<endl;
			return 1;
		}
	}
	
	if ( (pRestoredFibObject == NULL) || (pRestoredFibObject->getType() != 'r') ){
		cerr<<"No original Fib-multimediaobjects."<<endl;
		return 2;
	}
	
	//running the enviroment
	
	cout<<"cInitFibEnviroment initEnviroment( *((cRoot*)pRestoredFibObject) ); "<<endl;
	cInitFibEnviroment initEnviroment( *((cRoot*)pRestoredFibObject) );
	
	cout<<"cFibObjectFitnessBasicAlgorithm fibObjectAlgorithmBasic( pRestoredFibObject, "<<
		dInWeightDistanceToOriginal <<", "<< dInWeightSize <<", "<< dInWeightEvaluationTime <<" );"<<endl;
	cFibObjectFitnessBasicAlgorithm fibObjectAlgorithmBasic( pRestoredFibObject,
		dInWeightDistanceToOriginal, dInWeightSize, dInWeightEvaluationTime );
	
	cout<<"cEndConditionCheck endCondition;"<<endl;
	cEndConditionCheck endCondition;
	if ( ulMaxIterations != 0 ){
		cout<<"endCondition.setMaxOperationCalls( "<< ulMaxIterations <<" );"<<endl;
		endCondition.setMaxOperationCalls( ulMaxIterations );
	}
	cout<<"cResourceCheck resourceCheck( max operations="<<MAX_OPERATIONS_TO_RUN<<" );"<<endl;
	cResourceCheck resourceCheck( MAX_OPERATIONS_TO_RUN );
	
	cout<<"cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic, &endCondition, "<<
			"NULL, NULL, NULL, NULL, NULL, &resourceCheck );"<<endl;
	cEnviroment::setParameter( &initEnviroment, &fibObjectAlgorithmBasic, &endCondition,
			NULL, NULL, NULL, NULL, NULL, &resourceCheck );
	
	cout<<"cEnviroment * pEnviroment = cEnviroment::getInstance(); "<<endl;
	cEnviroment * pEnviroment = cEnviroment::getInstance();
	if ( pEnviroment == NULL ){
		cerr<<"Error: An instance of the enviroment could not be created."<<endl;
		return 5;
	}
	
	clStoreBestIndividual storeBestIndividual( pFolderForStoringData );
	const bool bListenerBestRegisterd =
		pEnviroment->registerIndividualListener( &storeBestIndividual );
	
	if ( !bListenerBestRegisterd ){
		cerr<<"Warning: Couldn't register the best individual storer."<<endl;
	}
	
	cout<<"pEnviroment->run(); "<<endl;
	const bool bObjectGenerated = pEnviroment->run();
	
	pEnviroment->unregisterIndividualListener( &storeBestIndividual );

	if (! bObjectGenerated ){
		cerr<<"Error: False was returned by the run() method."<<endl;
	}
	
	//getting the best result Fib-object
	cFibIndividual * pIndividualBest = NULL;
	
	cFibElement * pBestFibObject = NULL;

	unsigned long ulNumberOfIndividuals = pEnviroment->getNumberOfIndividuals();
	cout<<"Number of Individuals in the enviroment: "<< ulNumberOfIndividuals <<endl;
	
	if ( (ulMaxEndIndividualsToOutput != 0) &&
			( ulMaxEndIndividualsToOutput < ulNumberOfIndividuals) ){
		
		ulNumberOfIndividuals = ulMaxEndIndividualsToOutput;
	}
	
	for ( unsigned int uiActualIndividual = 1;
			uiActualIndividual <= ulNumberOfIndividuals; uiActualIndividual++ ){
		
		pIndividualBest = ((cFibIndividual*)(pEnviroment->getBestIndividual(
			uiActualIndividual )));
		
		pBestFibObject = pIndividualBest->getFibObject();
		
		char szFileName[ 256 ];
		sprintf( szFileName, "%s/resultbest%u.fib", pFolderForStoringData, uiActualIndividual );
		ofstream outFile( szFileName, ios_base::out | ios_base::binary );
			
		cout<<"Storing generated "<< uiActualIndividual <<"'th best Fib-object "<<
			"in the xml -format to the file "<< szFileName <<" . "<<endl;
		
		const bool bStoreSuccesfull = pBestFibObject->store( outFile );
		
		if ( ! bStoreSuccesfull ){
	
			cerr<<"Error: Storing the data of the generated best Fib-object "<<
				"in the compressed -Fib-format to the file "<< szFileName <<" failed."<<endl;
		}
		delete pIndividualBest;
	}

	if ( pRestoredFibObject != NULL ){
		cFibElement::deleteObject( pRestoredFibObject );
	}
	delete pEnviroment;

	return 0;
}
















