/**
 * @file cOperatorFitnessAlgorithmBasic
 * file name: cOperatorFitnessAlgorithmBasic.h
 * @author Betti Oesterholz
 * @date 22.03.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for gernerating the fitness for
 * operators.
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
22.03.2010  Oesterholz  created
*/


#ifndef ___C_OPERATION_FITNESS_ALGORITHM_BASIC_H__
#define ___C_OPERATION_FITNESS_ALGORITHM_BASIC_H__

#include "version.h"

#include "cOperatorFitnessAlgorithm.h"
#include "cIndividualInfo.h"

#include "tinyxml.h"

#include <string>
#include <map>
#include <iostream>

using namespace std;

namespace enviroment{


class cOperatorFitnessAlgorithmBasic: public cOperatorFitnessAlgorithm{
protected:
	
	/**
	 * The factor A for the whool fitness.
	 */
	double dFaktorAllFitnessPart;
	
	/**
	 * The factor B for the improvment fitnesssum.
	 */
	double dFaktorPositivFitnessPart;
	
	/**
	 * The structur for the operator fitness values
	 * The fields are:
	 * 	- dB_ins: The sum of all fitnessimprovments the operator has created.
	 * 		For every V_i value which is greater 1, the value (V_i - 1) is added.
	 * 	- dA_ins: The cost sum the operator has needed. This is the sum of
	 * 		all cost (evalued with the benchmark value) operations of the
	 * 		operator have needed.
	 * 	- dF_ins: The whool fitness. This is the ratio of the sum of all
	 * 		fitnessimprovments B_ins diveded by cost sum the operator has
	 * 		needed A_ins. dF_ins = dB_ins / dA_ins
	 * 	- dA_p: The cost sum the operator has needed for improvments. This
	 * 		is the sum of all cost (evalued with the benchmark value) operations
	 * 		of the operator have needed for generating a improved individual
	 * 		(an individual which is better as the best individual in the
	 * 		algorithm). This means the operator cost ist added, if V_i is
	 * 		greater 1.
	 * 	- dF_p: The improvment fitness. This is the ratio of the sum of all
	 * 		fitnessimprovments B_ins diveded by cost sum the operator has
	 * 		needed for inprovments A_P. dF_p = dB_ins / dA_p
	 * 	- dF: The fitness of the operator. This is the sum combination of
	 * 		the whool fitness F_ins multiplyed by the weight factor A and the
	 * 		improvment fitness F_P multiplyed by the weight factor B.
	 * 		dF = A * dF_ins + B * dF_p
	 */
	class cOperatorFitness;

	/**
	 * The operator fitnessvalues which have been loaded from a file.
	 *
	 * The key is the operatorname.
	 */
	map< string, cOperatorFitness > mapLoadedOperatorFitness;
	
	/**
	 * The path to the file in which the operation data is and/or should
	 * be stored.
	 */
	string szOperationDataPath;
	
	/**
	 * The operator fitnessvalues which this object has evalued and loaded.
	 *
	 * The key is the operatorname.
	 */
	map< string, cOperatorFitness > mapPastOperatorFitness;
	
	/**
	 * The summ of all fitnessvalues
	 */
	double dFitnessSum;
	
	/**
	 * This list contains all operators with ther fitness values
	 * in an list. It is used for a faster evaluation of the
	 * getFitness() method.
	 *
	 * @see getFitness()
	 */
	list< pair< const cOperation*, double > > liOperatorFitness;
	
public:
	
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
	cOperatorFitnessAlgorithmBasic( double dInFaktorAllFitnessPart=0.5,
		double dInFaktorPositivFitnessPart=0.5,
		const string szOldOperationDataPath="" );
	
	/**
	 * copyconstructor of the class cOperatorFitnessAlgorithmBasic.
	 *
	 * @param opFitnessAlgorithmBasic the cOperatorFitnessAlgorithmBasic to copy
	 */
	cOperatorFitnessAlgorithmBasic( const cOperatorFitnessAlgorithmBasic & opFitnessAlgorithmBasic );

	
	/**
	 * Destructor of the class cOperatorFitnessAlgorithmBasic.
	 */
	virtual ~cOperatorFitnessAlgorithmBasic();
	
	/**
	 * This method evalues the fitness of the given operator operation new.
	 *
	 * @param operation the operator for which the fitness is to be evalued new
	 * @param liCreatedIndividualInfos a list with all informations about
	 * 	all individuals the operator has created
	 * @return the new evalued fitness of the operation
	 */
	virtual double evalueFitness( const cOperation & operation,
		const list<cIndividualInfo> &liCreatedIndividualInfos );


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
	virtual double updateFitness( const cOperation & operation,
		const cIndividualInfo &createdIndividualInfo );

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
	virtual double updateFitness( const cOperation & operation,
		const list<cIndividualInfo> &liCreatedIndividualInfos );

	/**
	 * This method returns the fitness of the given operator operation.
	 *
	 * @param operation the operator for which the fitness is to be returned
	 * @return the fitness of the operation
	 */
	virtual double getFitness( const cOperation & operation );

	/**
	 * This method returns the fitness of all operators.
	 *
	 * @return a list with all possible operators with ther fitness
	 */
	virtual list< pair< const cOperation*, double > > getFitness();

	/**
	 * @return the class name of this object
	 */
	virtual string getClassName() const;

	/**
	 * @return the minimal fitness which this object can evalue
	 */
	virtual double getMinFitness() const;
	
	/**
	 * @return the sum of all fitnessvalues of all operators
	 */
	virtual double getFitnessSum() const;

	/**
	 * @see dFaktorAllFitnessPart
	 * @return the factor A for the whool fitness
	 */
	double getFaktorAllFitnessPart() const;

	/**
	 * @see dFaktorPositivFitnessPart
	 * @return the factor B for the improvment fitnesssum
	 */
	double getFaktorPositivFitnessPart() const;


protected:
	
	/**
	 * it's greater 1:
	 * 	N( dFitness ) = max( 1 , ( dFitness - dMinFitness ) )
	 *
	 * @param dFitness the fitnessvalue of an individual to normalize
	 * @param dMinFitness the minimal fitness; evalue with
	 * 	cObjectFitnessAlgorithm->getWorstCaseFitness()->getFitness()
	 * @return the normalized individual fitness
	 */
	double normalizeIndividualFitness( double dFitness, double dMinFitness=0.0 ) const;
	
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
	 * 		F = A * dF_ins + B * dF_p
	 *
	 * @see cOperatorFitness
	 * @see normalizeIndividualFitness()
	 * @param opFitness the operator fitness values for an operator
	 * @param liCreatedIndividualInfos the information about individual the
	 * 	operator to opFitness had created, but which are not jet
	 * 	included in opFitness
	 * @return the reevalued operator fitness
	 */
	cOperatorFitness updateFitness( const cOperatorFitness & opFitness,
		const list<cIndividualInfo> & liCreatedIndividualInfos ) const;
	
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
	 * @see restoreXmlOperationsData()
	 * @param oStream the stream wher the operator data is to store to
	 * @param mapOperationFitness the operator fitness data to store
	 * @return true if this operation fitness data is stored, else false
	 */
	bool storeXmlOperationsData( ostream & oStream,
		const map< string, cOperatorFitness > & mapOperationFitness ) const;
	
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
	map< string, cOperatorFitness > restoreXmlOperatorData(
		istream & iStream, int & outStatus ) const;


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
	map< string, cOperatorFitness > restoreXmlOperatorData(
		const TiXmlNode * pXmlNode, int & outStatus ) const;
	
	
	/**
	 * This method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cOperatorFitnessAlgorithmBasic * clone() const;


};//end class cOperatorFitnessAlgorithmBasic


};//end namespace enviroment

#endif //___C_OPERATION_FITNESS_ALGORITHM_BASIC_H__







