/**
 * @file cOperatorFitnessAlgorithmBasic
 * file name: cOperatorFitnessAlgorithmBasic.cpp
 * @author Betti Oesterholz
 * @date 24.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains a implementation of a class for gernerating the
 * fitness for operators.
 * Copyright (C) @c GPL3 2010 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (GPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This header specifies a class for gernerating the fitness for operators.
 * The fitness of operators is evalued by considering the information about
 * the individuals the operation has created.
 *
 * Importent values and functions for the evaluation of the operation
 * fitness of this class are:
 * 	- NF(): This function normalizes the fitnessvalues of individuals,
 * 		so it's greater 1; ( F_min = minimal individual fitness value
 * 		= cObjectFitnessAlgorithm::getWorstCaseFitness() )
 * 		N( F_I ) = max( 1 , (F_I - F_min) )
 * 	- V_i: The improvement which the operator has created with an
 * 		individual. This is the ratio of the normalized fitness F_N of
 * 		the created individual diveded by the best fitness F_B of a
 * 		individual at the creation time. V_i = NF( F_N ) / NF( F_B )
 * 	- B_ins: The sum of all fitnessimprovments the operator has created.
 * 		For every V_i value which is greater 1, the value (V_i - 1) is added.
 * 	- A_ins: The cost sum the operator has needed. This is the sum of
 * 		all cost (evalued with the benchmark value) operations of the
 * 		operator have needed.
 * 	- F_ins: The whool fitness. This is the ratio of the sum of all
 * 		fitnessimprovments B_ins diveded by cost sum the operator has
 * 		needed A_ins. F_ins = B_ins / A_ins
 * 	- A_P: The cost sum the operator has needed for improvments. This
 * 		is the sum of all cost (evalued with the benchmark value) operations
 * 		of the operator have needed for generating a improved individual
 * 		(an individual which is better as the best individual in the
 * 		algorithm). This means the operator cost is added, if V_i is
 * 		greater 1.
 * 	- F_P: The improvment fitness. This is the ratio of the sum of all
 * 		fitnessimprovments B_ins diveded by cost sum the operator has
 * 		needed for inprovments A_P. F_P = B_ins / A_P
 * 	- F: The fitness of the operator. This is the sum combination of
 * 		the whool fitness F_ins multiplyed by the weight factor A and the
 * 		improvment fitness F_P multiplyed by the weight factor B.
 * 		F = A * F_ins + B * F_P
 * 		The standardvalues for the weights A and B is 0.5 .
 *
 * The fitness values of th operators are stored persistent in an file in
 * the xml -format. This file is loaded when this object is created and
 * written if the object destroyed.
 *
 * @see cOperatorFitnessAlgorithmBasic
 * @see cOperator
 * @see cEnviroment
 * @see cChoosOperator
 */
/*
History:
24.03.2010  Oesterholz  created
*/



#include "cOperatorFitnessAlgorithmBasic.h"
#include "cObjectFitnessAlgorithm.h"

#include <cmath>
#include <fstream>

using namespace std;
using namespace enviroment;



#ifndef ___C_OPERATION_FITNESS_H__
#define ___C_OPERATION_FITNESS_H__

/**
 * The structur for the operator fitness values
 */
class enviroment::cOperatorFitnessAlgorithmBasic::cOperatorFitness{
public:
	/**
	 * constructor
	 */
	cOperatorFitness(): dB_ins( 0.0 ), dA_ins( 0.0 ), dF_ins( 0.0 ),
			dA_p( 0.0 ), dF_p( 0.0 ), dF( 0.0 ), pdFitness( NULL ){
		//nothing to do
	}
	
	/**
	 * copyconstructor
	 */
	cOperatorFitness( const cOperatorFitness & pOpFitness ):
			dB_ins( pOpFitness.dB_ins ), dA_ins( pOpFitness.dA_ins ),
			dF_ins( pOpFitness.dF_ins ), dA_p( pOpFitness.dA_p ),
			dF_p( pOpFitness.dF_p ), dF( pOpFitness.dF ),
			pdFitness( pOpFitness.pdFitness ){
		//nothing to do
	}

	
	/**
	 * dB_ins: The sum of all fitnessimprovments the operator has created.
	 * 	For every V_i value which is greater 1, the value (V_i - 1) is added.
	 */
	double dB_ins;
	
	/**
	 * dA_ins: The cost sum the operator has needed. This is the sum of
	 * 	all cost (evalued with the benchmark value) operations of the
	 * 	operator have needed.
	 */
	double dA_ins;
	
	/**
	 * dF_ins: The whool fitness. This is the ratio of the sum of all
	 * 	fitnessimprovments B_ins diveded by cost sum the operator has
	 * 	needed A_ins. dF_ins = dB_ins / dA_ins
	 */
	double dF_ins;
	
	/**
	 * dA_p: The cost sum the operator has needed for improvments. This
	 * 	is the sum of all cost (evalued with the benchmark value) operations
	 * 	of the operator have needed for generating a improved individual
	 * 	(an individual which is better as the best individual in the
	 * 	algorithm). This means the operator cost ist added, if V_i is
	 * 	greater 1.
	 */
	double dA_p;
	
	/**
	 * dF_p: The improvment fitness. This is the ratio of the sum of all
	 * 	fitnessimprovments B_ins diveded by cost sum the operator has
	 * 	needed for inprovments A_P. dF_p = dB_ins / dA_p
	 */
	double dF_p;
	
	/**
	 * dF: The fitness of the operator. This is the sum combination of
	 * 	the whool fitness F_ins multiplyed by the weight factor A and the
	 * 	improvment fitness F_P multiplyed by the weight factor B.
	 * 	dF = A * dF_ins + B * dF_p
	 */
	double dF;
	
	/**
	 * A pointer to the fitness in the liOperatorFitness list.
	 */
	double * pdFitness;
};
#endif //___C_OPERATION_FITNESS_H__



/**
 * Constructor of the class cOperatorFitnessAlgorithmBasic.
 *
 * @param dInFaktorAllFitnessPart the factor A for the whool fitness
 * @param dInFaktorPositivFitnessPart the factor B for the increased fitnesssum
 * @param szOldOperationDataPath the path wher the operator fitness data is stored;
 * 	if "" (standardvalue) the path is "./cOperatorFitnessAlgorithmBasic.xml";
 * 	if the path ends with an '/', it is a folder in which the the operator
 * 	fitness data should be stored into an file with the name
 * 	"cOperatorFitnessAlgorithmBasic.xml"
 */
cOperatorFitnessAlgorithmBasic::cOperatorFitnessAlgorithmBasic( double dInFaktorAllFitnessPart,
		double dInFaktorPositivFitnessPart, const string szOldOperationDataPath ):
		dFaktorAllFitnessPart( dInFaktorAllFitnessPart ),
		dFaktorPositivFitnessPart( dInFaktorPositivFitnessPart ),
		dFitnessSum( 0.0 ){
	
	if ( szOldOperationDataPath == "" ){
		szOperationDataPath = "./" + getClassName() + ".xml";
	}else if ( szOldOperationDataPath.at( szOldOperationDataPath.size() - 1 ) == '/' ){
		szOperationDataPath = szOldOperationDataPath + getClassName() + ".xml";
	}else{
		szOperationDataPath = szOldOperationDataPath;
	}
	//restore operator fitness values
	ifstream inFileOperatioFitness( szOperationDataPath.c_str() );

	int outStatus = 0;

	mapLoadedOperatorFitness = restoreXmlOperatorData(
		inFileOperatioFitness , outStatus );
	
	//create operator fitness values for every existring operators
	list<const cOperation*> liPossibleOperations =
		cOperatorFitnessAlgorithm::getPossibleOperators();
	
	list<string> liNewOperators;
	
	for ( list<const cOperation*>::iterator itrOperator =
			liPossibleOperations.begin();
			itrOperator != liPossibleOperations.end(); itrOperator++ ){
		
		const string szOperatorName = (*itrOperator)->getName();
		
		map< string, cOperatorFitness >::const_iterator itrOperatorLoaded =
			mapLoadedOperatorFitness.find( szOperatorName );
		
		cOperatorFitness opFitness;
		
		if ( itrOperatorLoaded != mapLoadedOperatorFitness.end() ){
			//operator fitness data loaded
			opFitness = itrOperatorLoaded->second;
		}else{//new operator -> create new entry
			liNewOperators.push_back( szOperatorName );
		}
		
		liOperatorFitness.push_back( make_pair( *itrOperator, 0.0 ) );
		
		opFitness.pdFitness = &(liOperatorFitness.back().second);
		
		mapPastOperatorFitness.insert( make_pair( szOperatorName, opFitness ) );

		dFitnessSum += opFitness.dF;
	}
	//set new operators to the average fitness
	for ( list<string>::iterator itrNewOperator = liNewOperators.begin();
			itrNewOperator != liNewOperators.end(); itrNewOperator++ ){
		
		mapPastOperatorFitness[ *itrNewOperator ].dF =
			dFitnessSum / double( mapPastOperatorFitness.size() );
		dFitnessSum += dFitnessSum / double( mapPastOperatorFitness.size() );
	}
	
}


/**
 * copyconstructor of the class cOperatorFitnessAlgorithmBasic.
 *
 * @param opFitnessAlgorithmBasic the cOperatorFitnessAlgorithmBasic to copy
 */
cOperatorFitnessAlgorithmBasic::cOperatorFitnessAlgorithmBasic(
		const cOperatorFitnessAlgorithmBasic & opFitnessAlgorithmBasic ):
		dFaktorAllFitnessPart( opFitnessAlgorithmBasic.dFaktorAllFitnessPart ),
		dFaktorPositivFitnessPart( opFitnessAlgorithmBasic.dFaktorPositivFitnessPart ),
		mapLoadedOperatorFitness( opFitnessAlgorithmBasic.mapLoadedOperatorFitness ),
		szOperationDataPath( opFitnessAlgorithmBasic.szOperationDataPath ),
		mapPastOperatorFitness( opFitnessAlgorithmBasic.mapPastOperatorFitness ),
		dFitnessSum( opFitnessAlgorithmBasic.dFitnessSum ),
		liOperatorFitness( opFitnessAlgorithmBasic.liOperatorFitness ){
	
	//redirect the pdFitness pointers
	for ( list< pair< const cOperation*, double > >::iterator itrOperator =
				liOperatorFitness.begin();
			itrOperator != liOperatorFitness.end(); itrOperator++ ){
		
		mapPastOperatorFitness[ itrOperator->first->getName() ].pdFitness
			= &(itrOperator->second);
	}
}


/**
 * Destructor of the class cOperatorFitnessAlgorithmBasic.
 */
cOperatorFitnessAlgorithmBasic::~cOperatorFitnessAlgorithmBasic(){
	
	//store operator fitness values
	//add the operator fitness values to the fitnessvalues of the file
	ifstream inFileOperatioFitness( szOperationDataPath.c_str() );

	int outStatus = 0;

	map< string, cOperatorFitness > mapLoadedOperatorFitnessActual =
		restoreXmlOperatorData( inFileOperatioFitness , outStatus );
	
	inFileOperatioFitness.close();
	
	list<cIndividualInfo> liCreatedIndividualInfos;
	
	for ( map< string, cOperatorFitness >::iterator itrOperator =
			mapLoadedOperatorFitnessActual.begin();
			itrOperator != mapLoadedOperatorFitnessActual.end(); itrOperator++ ){
		
		const string szOperatorName = itrOperator->first;
		
		map< string, cOperatorFitness >::const_iterator itrOperatorPast =
			mapPastOperatorFitness.find( szOperatorName );
		
		if ( itrOperatorPast != mapPastOperatorFitness.end() ){
			//operator fitness data exists
			
			const cOperatorFitness opFitnessLoaded = itrOperator->second;
			
			cOperatorFitness opFitnessPast = itrOperatorPast->second;
			
			map< string, cOperatorFitness >::const_iterator itrOperatorLoadedOld =
				mapLoadedOperatorFitness.find( szOperatorName );
			if ( itrOperatorLoadedOld != mapLoadedOperatorFitness.end() ){
				//operator fitness data exists
				const cOperatorFitness opFitnessLoadedOld = itrOperatorLoadedOld->second;
				
				opFitnessPast.dB_ins += opFitnessLoaded.dB_ins - opFitnessLoadedOld.dB_ins;
				opFitnessPast.dA_ins += opFitnessLoaded.dA_ins - opFitnessLoadedOld.dA_ins;
				opFitnessPast.dA_p   += opFitnessLoaded.dA_p - opFitnessLoadedOld.dA_p;
				
				opFitnessPast = updateFitness( opFitnessPast, liCreatedIndividualInfos );
				
				mapPastOperatorFitness[ szOperatorName ] = opFitnessPast;
			}else{//ther is no old loaded data
				opFitnessPast.dB_ins += opFitnessLoaded.dB_ins;
				opFitnessPast.dA_ins += opFitnessLoaded.dA_ins;
				opFitnessPast.dA_p   += opFitnessLoaded.dA_p;
				
				opFitnessPast = updateFitness( opFitnessPast, liCreatedIndividualInfos );
				
				mapPastOperatorFitness[ szOperatorName ] = opFitnessPast;
			}
		}else{//new operator -> take loaded data
			mapPastOperatorFitness.insert( make_pair( itrOperator->first, itrOperator->second ) );
		}
	}
	//store the reevalued data
	ofstream ofFileOperatioFitness( szOperationDataPath.c_str() );
	
	storeXmlOperationsData( ofFileOperatioFitness, mapPastOperatorFitness );
}


/**
 * This method evalues the fitness of the given operator operation new.
 *
 * @param operation the operator for which the fitness is to be evalued new
 * @param liCreatedIndividualInfos a list with all informations about
 * 	all individuals the operator has created
 * @return the new evalued fitness of the operation
 */
double cOperatorFitnessAlgorithmBasic::evalueFitness( const cOperation & operation,
		const list<cIndividualInfo> &liCreatedIndividualInfos ){
	
	map< string, cOperatorFitness >::iterator itrOperatorPast =
		mapPastOperatorFitness.find( operation.getName() );
	
	cOperatorFitness opFitnessNew;
	
	if ( itrOperatorPast == mapPastOperatorFitness.end() ){
		//operator dosn't exists till now -> create a new entry
		mapPastOperatorFitness.insert( make_pair( operation.getName(), opFitnessNew ) );
		itrOperatorPast = mapPastOperatorFitness.find( operation.getName() );
	}
	
	if ( ! liCreatedIndividualInfos.empty() ){
		dFitnessSum -= itrOperatorPast->second.dF;
		
		itrOperatorPast->second =
			updateFitness( opFitnessNew, liCreatedIndividualInfos );
		
		dFitnessSum += itrOperatorPast->second.dF;
	}
	
	return itrOperatorPast->second.dF;
}


/**
 * This method updates the fitness of the given operator operation.
 * For this update the information this cOperatorFitnessAlgorithmBasic
 * object knows about the operator and the given
 * createdIndividualInfo is considered to evalue the new fitness.
 *
 * @param operation the operator, for which the fitness is to be updated
 * @param createdIndividualInfo the information about an individual
 * 	the operator has created and which is not jet known by this
 * 	cOperatorFitnessAlgorithmBasic object
 * @return the new evalued fitness of the operation
 */
double cOperatorFitnessAlgorithmBasic::updateFitness( const cOperation & operation,
		const cIndividualInfo &createdIndividualInfo ){
	
	list<cIndividualInfo> liCreatedIndividualInfos;
	liCreatedIndividualInfos.push_back( createdIndividualInfo );
	
	return updateFitness( operation, liCreatedIndividualInfos );
}


/**
 * This method updates the fitness of the given operator operation.
 * For this update the information this cOperatorFitnessAlgorithmBasic
 * object knows about the operator and the given information in
 * liCreatedIndividualInfos is considered to evalue the new fitness.
 *
 * @param operation the operator, for which the fitness is to be updated
 * @param liCreatedIndividualInfos a list with the information about
 * 	the individuals the operator has created and which are not jet
 * 	known by this cOperatorFitnessAlgorithmBasic object
 * @return the new evalued fitness of the operation
 */
double cOperatorFitnessAlgorithmBasic::updateFitness( const cOperation & operation,
		const list<cIndividualInfo> &liCreatedIndividualInfos ){
	
	map< string, cOperatorFitness >::iterator itrOperatorPast =
		mapPastOperatorFitness.find( operation.getName() );
	
	if ( itrOperatorPast == mapPastOperatorFitness.end() ){
		//operator dosn't exists till now -> create a new entry
		cOperatorFitness opFitness;
		mapPastOperatorFitness.insert( make_pair( operation.getName(), opFitness ) );
		itrOperatorPast = mapPastOperatorFitness.find( operation.getName() );
	}
	
	if ( ! liCreatedIndividualInfos.empty() ){
		dFitnessSum -= itrOperatorPast->second.dF;
		
		itrOperatorPast->second = updateFitness(
			itrOperatorPast->second, liCreatedIndividualInfos );
		
		dFitnessSum += itrOperatorPast->second.dF;
	}
	
	return itrOperatorPast->second.dF;
}


/**
 * This method returns the fitness of the given operator operation.
 *
 * @param operation the operator for which the fitness is to be returned
 * @return the fitness of the operation
 */
double cOperatorFitnessAlgorithmBasic::getFitness( const cOperation & operation ){

	map< string, cOperatorFitness >::iterator itrOperatorPast =
		mapPastOperatorFitness.find( operation.getName() );
	
	if ( itrOperatorPast == mapPastOperatorFitness.end() ){
		//operator dosn't exists till now -> create a new entry
		cOperatorFitness opFitness;
		mapPastOperatorFitness.insert( make_pair( operation.getName(), opFitness ) );
		itrOperatorPast = mapPastOperatorFitness.find( operation.getName() );
	}
	
	return itrOperatorPast->second.dF;
}

/**
 * This method returns the fitness of all operators.
 *
 * @return a list with all possible operators with ther fitness
 */
list< pair< const cOperation*, double > > cOperatorFitnessAlgorithmBasic::getFitness(){

	return liOperatorFitness;
}



/**
 * @return the class name of this object
 */
string cOperatorFitnessAlgorithmBasic::getClassName() const{
	return "cOperatorFitnessAlgorithmBasic";
}


/**
 * @return the minimal fitness which this object can evalue
 */
double cOperatorFitnessAlgorithmBasic::getMinFitness() const{
	return 0.0;
}

/**
 * @return the sum of all fitnessvalues of all operators
 */
double cOperatorFitnessAlgorithmBasic::getFitnessSum() const{

	return dFitnessSum;
}


/**
 * @see dFaktorAllFitnessPart
 * @return the factor A for the whool fitness
 */
double cOperatorFitnessAlgorithmBasic::getFaktorAllFitnessPart() const{
	return dFaktorAllFitnessPart;
}


/**
 * @see dFaktorPositivFitnessPart
 * @return the factor B for the improvment fitnesssum
 */
double cOperatorFitnessAlgorithmBasic::getFaktorPositivFitnessPart() const{
	return dFaktorPositivFitnessPart;
}



/**
 * This function normalizes ( N( dFitness ) ) the fitnessvalues, so
 * it's greater 1:
 * 	N( dFitness ) = max( 1 , ( dFitness - dMinFitness ) )
 *
 * @param dFitness the fitnessvalue of an individual to normalize
 * @param dMinFitness the minimal fitness; evalue with
 * 	cObjectFitnessAlgorithm->getWorstCaseFitness()->getFitness()
 * @return the normalized individual fitness
 */
double cOperatorFitnessAlgorithmBasic::normalizeIndividualFitness(
	double dFitness, double dMinFitness ) const{
	
	return max( 1.0, dFitness - dMinFitness );
	
}


/**
 * This function reevalues operation fitness opFitness with the values
 * of liCreatedIndividualInfos.
 *
 * Important values evalued internal:
 * 	- V_i: The improvement which the operation has created with an
 * 		individual from the list liCreatedIndividualInfos.
 * 		This is the ratio of the normalized fitness F_N of
 * 		the created individual diveded by the best fitness F_B of a
 * 		individual at the creation time. V_i = NF( F_N ) / NF( F_B )
 *
 * Values of opFitness reevalued:
 * 	- dB_ins: The sum of all fitnessimprovments the operator has created.
 * 		For every V_i value which is greater 1, the values (V_i - 1) 
 *			are added to the old opFitness.dB_ins value.
 * 	- dA_ins: The cost sum the operator has needed. This is the sum of
 * 		all cost (evalued with the benchmark value) from the
 * 		list liCreatedIndividualInfos added to the opFitness.dA_ins value.
 * 	- dF_ins: The whool fitness. This is the ratio of the sum of all
 * 		fitnessimprovments B_ins diveded by cost sum the operation has
 * 		needed A_ins. dF_ins = dB_ins / dA_ins
 * 	- dA_p: The cost sum the operator has needed for improvments. This
 * 		is the sum of all cost (evalued with the benchmark value)
 * 		operations have needed for generating a improved individual
 * 		(an individual which is better as the best individual in the
 * 		algorithm, tihs means which V_i is greater 1) from the list
 * 		liCreatedIndividualInfos added to the opFitness.dA_p value.
 * 	- dF_p: The improvment fitness. This is the ratio of the sum of all
 * 		fitnessimprovments B_ins diveded by cost sum the operator has
 * 		needed for inprovments A_P. dF_p = dB_ins / dA_p
 * 	- dF: The fitness of the operator. This is the sum combination of
 * 		the whool fitness F_ins multiplyed by the weight factor A and the
 * 		improvment fitness F_P multiplyed by the weight factor B.
 * 		dF = A * dF_ins + B * dF_p
 *
 * @see cOperatorFitness
 * @see normalizeIndividualFitness()
 * @param opFitness the operator fitness values for an operator
 * @param liCreatedIndividualInfos the information about individual the
 * 	operator to opFitness had created, but which are not jet
 * 	included in opFitness
 * @return the reevalued operator fitness
 */
cOperatorFitnessAlgorithmBasic::cOperatorFitness
	cOperatorFitnessAlgorithmBasic::updateFitness(
		const cOperatorFitnessAlgorithmBasic::cOperatorFitness & opFitness,
		const list<cIndividualInfo> & liCreatedIndividualInfos ) const{
	
	cOperatorFitness newOperatorFitness;
	
	//evalue the values for the new individuals
	for ( list<cIndividualInfo>::const_iterator
			itrIndividualInfo = liCreatedIndividualInfos.begin();
			itrIndividualInfo != liCreatedIndividualInfos.end(); itrIndividualInfo++ ){
		
		const cObjectFitness * pIndividualFitness = itrIndividualInfo->getFitness();
		const cObjectFitness * pIndividualFitnessBest =
			itrIndividualInfo->getFitnessOfBestAtCreationTime();
		if ( (pIndividualFitness == NULL) || (pIndividualFitnessBest == NULL) ){
			//skip individual
			continue;
		}
		double dImprovedFitness;//V_i
		
		const cObjectFitnessAlgorithm * pFitnessAlgorithm =
			pIndividualFitness->getFitnessAlgorithm();
		
		if ( (pFitnessAlgorithm != NULL) &&
				(pFitnessAlgorithm->getWorstCaseFitness() != NULL) ){
			
			dImprovedFitness = normalizeIndividualFitness(
					pIndividualFitness->getFitness(),
					pFitnessAlgorithm->getWorstCaseFitness()->getFitness() ) /
				normalizeIndividualFitness(
					pIndividualFitnessBest->getFitness(),
					pFitnessAlgorithm->getWorstCaseFitness()->getFitness() ) ;
		}else{//no fitness algorithm -> use standard worse case fitness
			dImprovedFitness = normalizeIndividualFitness(
					pIndividualFitness->getFitness() ) /
				normalizeIndividualFitness(
					pIndividualFitnessBest->getFitness() ) ;
		}
		newOperatorFitness.dA_ins += itrIndividualInfo->getOperationCost();
		if ( 1.0 < dImprovedFitness ){
			newOperatorFitness.dA_p   += itrIndividualInfo->getOperationCost();
			newOperatorFitness.dB_ins += dImprovedFitness - 1.0;
		}
	}
	//evalue the new values
	newOperatorFitness.dA_ins += opFitness.dA_ins;
	newOperatorFitness.dA_p   += opFitness.dA_p;
	newOperatorFitness.dB_ins += opFitness.dB_ins;
	
	newOperatorFitness.dF_ins = newOperatorFitness.dB_ins / newOperatorFitness.dA_ins;
	
	newOperatorFitness.dF_p = newOperatorFitness.dB_ins / newOperatorFitness.dA_p;
	
	newOperatorFitness.dF = getFaktorAllFitnessPart() * newOperatorFitness.dF_ins +
		getFaktorPositivFitnessPart() * newOperatorFitness.dF_p;
	
	if ( opFitness.pdFitness != NULL ){
		newOperatorFitness.pdFitness = opFitness.pdFitness;
		*(newOperatorFitness.pdFitness) = newOperatorFitness.dF;
	}
	
	return newOperatorFitness;
}


/**
 * This function stores the operator fitness data in xml -format into
 * the given stream.
 *
 * Example Xml -structur:
 ** <operatorFitness algorithm="cOperatorFitnessAlgorithmBasic">
 **    <operator name="operator1" b_ins="1" a_ins="100" f_ins="0.01" a_p="10" f_p="0.1"/>
 **    <operator name="operator2" b_ins="2" a_ins="100" f_ins="0.02" a_p="5" f_p="0.4"/>
 ** <operatorFitness/>
 *
 * @see restoreXmlOperatorData()
 * @param oStream the stream wher the operator data is to store to
 * @param mapOperationFitness the operator fitness data to store
 * @return true if this operation fitness data is stored, else false
 */
bool cOperatorFitnessAlgorithmBasic::storeXmlOperationsData( ostream & oStream,
		const map< string, cOperatorFitness > & mapOperationFitness ) const{
	
	oStream<<"<operatorFitness algorithm=\""<< getClassName() <<"\">"<<endl;
	//write the data of the operators
	for ( map< string, cOperatorFitness >::const_iterator
			itrOperatorFitness = mapOperationFitness.begin();
			itrOperatorFitness != mapOperationFitness.end(); itrOperatorFitness++ ){
		
		oStream<<"<operator name=\""<< itrOperatorFitness->first <<"\" "<<
			"b_ins=\""<< itrOperatorFitness->second.dB_ins <<"\" "<<
			"a_ins=\""<< itrOperatorFitness->second.dA_ins <<"\" "<<
			"f_ins=\""<< itrOperatorFitness->second.dF_ins <<"\" "<<
			"a_p=\""<< itrOperatorFitness->second.dA_p <<"\" "<<
			"f_p=\""<< itrOperatorFitness->second.dF_p <<"\" />"<<endl;
	}
	
	oStream<<"<operatorFitness/>"<<endl;
	return oStream.good();
}



/**
 * This function restores the operator fitness data from the given stream.
 * In the stream the operator fitness data should be writen in the
 * xml -format, like storeXmlOperationsData() stores it.
 *
 * @see storeXmlOperationsData()
 * @param iStream the stream where the operator fitness data is stored in
 * @param outStatus An reverence to an integervalue where the errorvalue
 * 	can be stored to.
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid stream
 * 		- -2 loading error, invalid data in stream
 * 		- 1 loading warning, invalid data in stream, error could be corrected
 * 		- 2 loading warning, invalid data in stream, maybe the loaded
 * 			data is wrong
 * @return the restored operator fitness data
 */
map< string, cOperatorFitnessAlgorithmBasic::cOperatorFitness >
	cOperatorFitnessAlgorithmBasic::restoreXmlOperatorData(
		istream & iStream, int &outStatus ) const{
	
	TiXmlDocument xmlDocFibObject;

	iStream >> xmlDocFibObject;
	
	if ( xmlDocFibObject.Error() ){
		outStatus = -1;
		return map< string, cOperatorFitness >();
	}
	
	//TODO check on xsd

	return restoreXmlOperatorData( &xmlDocFibObject, outStatus );
}


/**
 * This function restores the operator fitness data from the given
 * TinyXml node.
 * In the TinyXml node the operator fitness data should be stored in
 * the xml -format, like storeXmlOperationsData() stores it.
 *
 * @see storeXmlOperationsData()
 * @param pXmlNode a pointer to the TinyXml node the operator fitness
 * 	data is stored in
 * @param outStatus An reverence to an integervalue where the errorvalue
 * 	can be stored to.
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid stream
 * 		- -2 loading error, invalid data in stream
 * 		- 1 loading warning, invalid data in stream, error could be corrected
 * 		- 2 loading warning, invalid data in stream, maybe the loaded
 * 			data is wrong
 * @return the restored operator fitness data
 */
map< string, cOperatorFitnessAlgorithmBasic::cOperatorFitness >
	cOperatorFitnessAlgorithmBasic::restoreXmlOperatorData(
		const TiXmlNode * pXmlNode, int & outStatus ) const{
	
	map< string, cOperatorFitness > mapLoadedOpFitness;
	
	if ( pXmlNode == NULL ){
		outStatus = -1;
		return mapLoadedOpFitness;
	}
	
	int iType = pXmlNode->Type();

	switch ( iType ){
		case TiXmlNode::ELEMENT:{
			/*check if this is a valid fib -element xml -element, create
			the apropirate fib -element and call its restoreXml() method*/
			const TiXmlElement * pXmlElement = pXmlNode->ToElement();
			if ( pXmlElement == NULL ){
				//Error: nothing to load
				outStatus = -2;
				return mapLoadedOpFitness;
			}
			string szElementType( pXmlElement->Value() );
			
			if ( szElementType == "operatorFitness" ){
				//check if the operatorFitness is of the correct type
				const char * szOperatorFitnessType = pXmlElement->Attribute( "algorithm" );
				
				if ( szOperatorFitnessType == NULL ){
					//unknown data type
					outStatus = -2;
					return mapLoadedOpFitness;
				}else if ( getClassName() != szOperatorFitnessType ) {
					//invalid data type
					outStatus = -2;
					return mapLoadedOpFitness;
				}
				list<cIndividualInfo> liCreatedIndividualInfos;//dummy
				//load the operator fitness subelements
				if ( pXmlElement->FirstChild() == NULL ){
					//no operation data
					return mapLoadedOpFitness;
				}
				for ( const TiXmlElement * pXmlOperator = pXmlElement->FirstChild()->ToElement();
						pXmlOperator != NULL; pXmlOperator = pXmlOperator->NextSiblingElement() ){
					
					string szElementType( pXmlOperator->Value() );
					
					if ( szElementType != "operator" ){
						//unknown xml -element -> skip it
						outStatus = 2;
						continue;
					}
					const char * szAttribute = pXmlOperator->Attribute( "name" );
					
					if ( szAttribute == NULL ){
						//unknown operator
						outStatus = 2;
						continue;
					}
					string szOperatorName( szAttribute );
					
					cOperatorFitness operatorFitness;
					
					szAttribute = pXmlOperator->Attribute( "b_ins", &(operatorFitness.dB_ins) );
					if ( (szAttribute == NULL) && (outStatus == 0) ){
						//field missing
						outStatus = 1;
					}
					szAttribute = pXmlOperator->Attribute( "a_ins", &(operatorFitness.dA_ins) );
					if ( (szAttribute == NULL) && (outStatus == 0) ){
						//field missing
						outStatus = 1;
					}
					szAttribute = pXmlOperator->Attribute( "f_ins", &(operatorFitness.dF_ins) );
					if ( (szAttribute == NULL) && (outStatus == 0) ){
						//field missing
						outStatus = 1;
					}
					szAttribute = pXmlOperator->Attribute( "a_p", &(operatorFitness.dA_p) );
					if ( (szAttribute == NULL) && (outStatus == 0) ){
						//field missing
						outStatus = 1;
					}
					szAttribute = pXmlOperator->Attribute( "f_p", &(operatorFitness.dF_p) );
					if ( (szAttribute == NULL) && (outStatus == 0) ){
						//field missing
						outStatus = 1;
					}
					//insert new data entry to loaded data list
					operatorFitness = updateFitness( operatorFitness, liCreatedIndividualInfos );
					pair< map< string, cOperatorFitness >::iterator, bool> paOperatorInserted =
						mapLoadedOpFitness.insert( make_pair( szOperatorName, operatorFitness ) );
					
					if ( ! paOperatorInserted.second ){
						//old entry overwritten
						outStatus = 1;
					}
				}
			}else{//Error: no operation fitness data to load
				outStatus = -2;
				return mapLoadedOpFitness;
			}
			
		}break;
		case TiXmlNode::DOCUMENT:{
			//ignore
			for ( const TiXmlNode * pChild = pXmlNode->FirstChild();
					pChild != NULL; pChild = pChild->NextSibling() ) {
				
				mapLoadedOpFitness = restoreXmlOperatorData( pChild, outStatus );
				if ( outStatus < 0 ){
					//an error occured
					return mapLoadedOpFitness;
				}
			}
		}break;
		case TiXmlNode::DECLARATION:
		case TiXmlNode::COMMENT:{
			//ignore
		}break;
		case TiXmlNode::TEXT:
		case TiXmlNode::UNKNOWN:
		default:
			//ignore; Warning: invalid operation fitness data
			outStatus = 2;
	}
	
	return mapLoadedOpFitness;
}


/**
 * This method clones this object.
 *
 * @return a clone of this object
 */
cOperatorFitnessAlgorithmBasic * cOperatorFitnessAlgorithmBasic::clone() const{

	return new cOperatorFitnessAlgorithmBasic( *this );
}







