/**
 * @file tFibObjectVariable
 * file name: tFibObjectVariable.cpp
 * @author Betti Oesterholz
 * @date 20.12.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the methods for variables in Fib objects.
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
 * This test is for the methods for variables in Fib objects.
 *
 *
 * What's tested of class cFibElement -classes:
 * 	- bool isUsedVariable( const cFibVariable *variable , edDirection direction=ED_POSITION ) const;
 * 	- set<cFibVariable*> getUsedVariables( edDirection direction=ED_POSITION );
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- bool isDefinedVariable( const cFibVariable *variable , edDirection direction=ED_POSITION ) const;
 * 	- list<cFibVariable*> getDefinedVariables( edDirection direction=ED_POSITION );
 * 	- bool variablesAreDefined( const set<cFibVariable*> & setVariable , edDirection direction=ED_HIGHER )
 *
 *
 * Fib elements tested: (like tGeneratorForFibObjects)
 * 	- cRoot
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cList
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * call: tFibObjectVariable [MAX_SIZE] [ITERATIONS]
 *
 * parameters:
 * 	MAX_SIZE
 * 		The maximum size, which should not oversteped when the
 * 		Fib objects are generated.
 * 		The standardvalue is 1024.
 * 	ITERATIONS
 * 		The iterations for every parameterset. The generateFibObject() is
 * 		called I times for every parameterset.
 * 		Standardvalue is one.
 *
 */
/*
History:
20.12.2009  Oesterholz  created
01.08.2010  Oesterholz  cComment added
23.05.2011  Oesterholz  cIf added
28.09.2011  Oesterholz  cExtObject included
14.11.2011  Oesterholz  cExtSubobject inserted
16.01.2012  Oesterholz  cFibSet and cFibMatrix added
*/

#include "version.h"

#include "cFibElement.h"
#include "cList.h"
#include "cPoint.h"
#include "cTypeProperty.h"
#include "cExtObject.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <ostream>
#include <cmath>
#include <ctime>

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif



using namespace fib;
using namespace std;


extern cFibElement * generateFibObject( unsigned int uiSize,
		list< pair< char, double > > liFractionOfFibElements,
		const list< cTypeProperty > & liPossiblePropertytyps,
		const unsigned int uiNumberOfDimensions,
		const unsigned int uiAverageSubRoots, const unsigned int uiAverageSubRootsDepth,
		const unsigned int uiNumberOfAverageInputVariables,
		const double dFractionsOfUsedVariables ,
		unsigned int uiMaxVectorElementNumber );


int testVariableRandom( unsigned long &ulTestphase, unsigned int uiMaxSize, unsigned int uiIterations );
int testVariableOnObject( cFibElement * FibObject );

list< pair< char, double > > liFractionOfFibElements;


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	const time_t timeStart = time( 0 );
	
	//* read input parameters
	unsigned int uiMaxSize = 1024;
	unsigned int uiIterations = 1;
	
	if ( argc >= 2 ){
		//one parameter given; get parameter max size
		uiMaxSize = atol( argv[1] );
		if ( uiMaxSize < 4 ){
			uiMaxSize = 4;
		}
	}
	
	if ( argc >= 3 ){
		//two parameter given; read parameter iterations
		uiIterations = atol( argv[2] );
		if ( uiIterations < 1 ){
			uiIterations = 1;
		}
	}

	liFractionOfFibElements.push_back( make_pair( 'p', 1.0 ) );
	liFractionOfFibElements.push_back( make_pair( 'y', 1.0 ) );
	liFractionOfFibElements.push_back( make_pair( 'l', 0.5 ) );
	liFractionOfFibElements.push_back( make_pair( 'a', 0.4 ) );
	liFractionOfFibElements.push_back( make_pair( 'f', 0.4 ) );
	liFractionOfFibElements.push_back( make_pair( 'i', 0.4 ) );
	liFractionOfFibElements.push_back( make_pair( 'c', 0.1 ) );
	liFractionOfFibElements.push_back( make_pair( 'o', 0.1 ) );
	liFractionOfFibElements.push_back( make_pair( 's', 0.1 ) );
	liFractionOfFibElements.push_back( make_pair( 'v', 0.1 ) );
	liFractionOfFibElements.push_back( make_pair( 'm', 0.1 ) );
	//TODO: more Fib elements

	cout<<endl<<"Running Test for variables in Fib objects"<<endl;
	cout<<      "========================================="<<endl;

	iReturn += testVariableRandom( ulTestphase, uiMaxSize, uiIterations );


	cout<<endl<<endl<<"Test duration "<<(time( 0 ) - timeStart)<<" seconds (or "<<
		(time( 0 ) - timeStart)/60<<" minutes)"<<endl;
	if ( iReturn == 0 ){
	
		cout<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}


/**
 * This function tests the methods for variables on an given Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool isUsedVariable( const cFibVariable *variable , edDirection direction=ED_POSITION ) const;
 * 	- set<cFibVariable*> getUsedVariables( edDirection direction=ED_POSITION );
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- bool isDefinedVariable( const cFibVariable *variable , edDirection direction=ED_POSITION ) const;
 * 	- list<cFibVariable*> getDefinedVariables( edDirection direction=ED_POSITION );
 *
 * @param FibObject a pointer to the Fib object to test
 * @return the number of erros occured in the test
 */
int testVariableOnObject( cFibElement * pFibObject ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
	}
	
	/*direction=ED_POSITION is checked in the Fib element tests, the
	other directions are checked here with the help of direction=ED_POSITION;
	go into the direction to check and check on all Fib elements in the
	direction with (direction=ED_POSITION) if the given back variables
	are correct*/
	
	//get all defined variables in the Fib object
	list<cFibVariable*> liAllDefinedVariables;
	
	for ( cFibElement * pActualRootElement = pFibObject;
			pActualRootElement != NULL;
			pActualRootElement = pActualRootElement->getNextFibElement( 'r' ) ){
		
		list<cFibVariable*> liAllDefinedVariablesHere =
			pActualRootElement->getDefinedVariables( ED_ALL );
		
		liAllDefinedVariables.insert( liAllDefinedVariables.end(),
			liAllDefinedVariablesHere.begin(), liAllDefinedVariablesHere.end() );
	}
	
	cout<<"The Fib objects defines "<< liAllDefinedVariables.size() <<" variables . "<<endl;
	
	if ( liAllDefinedVariables.empty() ){
		cout<<"   Skip test because no variables to check with.  "<<endl;
		return iReturn;
	}
	
	//enumerate the variables so they can be identified
	unsigned int uiVariableNumber = 1;
	for ( list<cFibVariable*>::iterator itrVariable = liAllDefinedVariables.begin();
			itrVariable != liAllDefinedVariables.end();
			itrVariable++, uiVariableNumber++ ){
		
		(*itrVariable)->setValue( uiVariableNumber );
	}

	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	
	for ( unsigned int uiIteration = 0; uiIteration <=
			(uiNumberOfAllFibElements / 10) ; uiIteration++){
		
		//choos a random Fib element
		const unsigned int uiChoosenFibElement = rand() % uiNumberOfAllFibElements;
		cFibElement * pChoosenFibElement = pFibObject->getFibElement(
			 uiChoosenFibElement );
		//check the getType() methode from cList
		if ( pChoosenFibElement ){
		
			cout<<endl<<"The "<< uiChoosenFibElement <<
				"'th Fib element of type "<<pChoosenFibElement->getType()<<
				" of the Fib object was choosen . "<<endl;
		}else{
			cerr<<endl<<"Error: The "<< uiChoosenFibElement <<
				"'th Fib element of the Fib object couldn't be choosen ."<<endl;
			iReturn++;
			continue;
		}
	
	//**check direction ED_HIGHER
	
	//check getUsedVariables( ED_HIGHER ) on choosen Fib element
		set<cFibVariable*> setVariablesUsedHigher = pChoosenFibElement->
			getUsedVariables( ED_HIGHER );
		set<cFibVariable*> setVariablesNotUsedHigher = setVariablesUsedHigher;
		
		if ( ! setVariablesUsedHigher.empty() ){
			cout<<"   It has "<< setVariablesUsedHigher.size() <<" variables which are used higher. "<<endl;
		}else{
			cout<<"   It has no variables which are used higher. "<<endl;
		}
		
		/*check if the variables are realy used higher (is in all superior
		Fib elements)*/
		cFibElement * pSuperiorFibElement = pChoosenFibElement->getSuperiorFibElement();
		unsigned int uiNumberOfSuperior = 1;
		while ( pSuperiorFibElement ){
			//get variables used in the superior Fib element
			set<cFibVariable*> setVariablesUsedHere = pSuperiorFibElement->
				getUsedVariables( ED_POSITION );
			
			unsigned int uiPosition = 1;
			for ( set<cFibVariable*>::iterator itrVariable = setVariablesUsedHere.begin();
					itrVariable != setVariablesUsedHere.end();
					itrVariable++, uiPosition++ ){
				//check if the variable is in setVariablesUsedHigher
				set<cFibVariable*>::iterator itrFoundedVariable = find(
					setVariablesUsedHigher.begin(), setVariablesUsedHigher.end(),
					*itrVariable );
				if ( itrFoundedVariable == setVariablesUsedHigher.end() ){
					cerr<<"Error: The "<< uiPosition <<"'th variable of "<<
						uiNumberOfSuperior <<"'th superior Fib element couldn't be"<<
						" found in the variable list of the variables used higher the"<<
						" choosen Fib element."<<endl;
					iReturn++;
				}
				//remove variable from setVariablesNotUsedHigher
				itrFoundedVariable = find( setVariablesNotUsedHigher.begin(),
					setVariablesNotUsedHigher.end(), *itrVariable );
				if ( itrFoundedVariable != setVariablesNotUsedHigher.end() ){
					setVariablesNotUsedHigher.erase( itrFoundedVariable );
				}
			}
			//check next superior Fib element
			pSuperiorFibElement = pSuperiorFibElement->getSuperiorFibElement();
			uiNumberOfSuperior++;
		}
		//setVariablesNotUsedHigher should be empty
		if ( ! setVariablesNotUsedHigher.empty() ){
			cerr<<"Error: Not all variables given back as used below the"<<
				" choosen Fib element are founded used higher the choosen Fib element."<<endl;
			for ( set<cFibVariable*>::iterator itrVariable = setVariablesNotUsedHigher.begin();
					itrVariable != setVariablesNotUsedHigher.end();
					itrVariable++ ){
				cerr<<"   The "<< (*itrVariable)->getValue() <<"'th variable was not found."<<endl;
			}
			iReturn++;
		}
		
		/*check isUsedVariable( ED_HIGHER ) on choosen Fib element for all
		variables in setVariablesUsedHigher*/
		unsigned int uiPosition = 1;
		for ( set<cFibVariable*>::iterator itrVariable = setVariablesUsedHigher.begin();
				itrVariable != setVariablesUsedHigher.end();
				itrVariable++, uiPosition++ ){
			
			if ( ! pChoosenFibElement->isUsedVariable( *itrVariable, ED_HIGHER ) ){
				cerr<<"Error: The "<< uiPosition <<
					"'th variable (number="<< (*itrVariable)->getValue() <<
					") which was given back as used higher"<<
					" was not found by isUsedVariable( ED_HIGHER )."<<endl;
				iReturn++;
			}
		}
		/*try to check isUsedVariable( ED_HIGHER ) on choosen Fib element and variable
		not used in the direction, but defined for it*/
		list<cFibVariable*>::iterator itrChoosenVariable =
			liAllDefinedVariables.begin();
		unsigned int uiNotUsedVariablesToChecked = liAllDefinedVariables.size() / 100 + 10;
		for ( unsigned int uiVariablesChecked = 0;
				(uiVariablesChecked < liAllDefinedVariables.size()) &&
				(0 < uiNotUsedVariablesToChecked);
				uiVariablesChecked++ ){
			
			//choos random variable from all variables
			unsigned int uiChoosenVariable = (rand() % liAllDefinedVariables.size()) / 50 + 1;
			while ( uiChoosenVariable != 0){
				itrChoosenVariable++;
				uiChoosenVariable--;
				if ( itrChoosenVariable == liAllDefinedVariables.end() ){
					itrChoosenVariable = liAllDefinedVariables.begin();
				}
			}
			//check if choosen variable was given back as used higher
			set<cFibVariable*>::iterator itrFoundedVariable = find(
				setVariablesUsedHigher.begin(), setVariablesUsedHigher.end(),
				*itrChoosenVariable );
			if ( itrFoundedVariable == setVariablesUsedHigher.end() ){
				
				if ( pChoosenFibElement->isUsedVariable( *itrChoosenVariable, ED_HIGHER ) ){
					cerr<<"Error: The "<< (*itrChoosenVariable)->getValue() <<
						"'th variable, which was not given back as used higher,"<<
						" was found by isUsedVariable( ED_HIGHER )."<<endl;
					iReturn++;
				}else{
					uiNotUsedVariablesToChecked--;
				}
			}
		}
		cout<<"The method isUsedVariable( ED_HIGHER ) gives back correctly false for "<<
			((liAllDefinedVariables.size() / 100 + 10) - uiNotUsedVariablesToChecked) <<
			" variable defined in the whool Fib object but not found higher"<<
			" used of the choosen Fib element."<<endl;
		
	
	//check getDefinedVariables( ED_HIGHER ) on choosen Fib element
		list<cFibVariable*> liVariablesDefinedHigher = pChoosenFibElement->
			getDefinedVariables( ED_HIGHER );
		list<cFibVariable*> liVariablesNotDefinedHigher = liVariablesDefinedHigher;
		
		if ( ! liVariablesDefinedHigher.empty() ){
			cout<<"The choosen Fib element has "<< liVariablesDefinedHigher.size()
				<<" variables which are defined higher. "<<endl;
		}else{
			cout<<"The choosen Fib element has no variables which are defined higher. "<<endl;
		}
		
		/*check if the variables are realy defined higher (is in all superior
		Fib elements)*/
		if ( pChoosenFibElement->getType() != 'r' ){
			//the choosen Fib element is no root-element
			pSuperiorFibElement = pChoosenFibElement->getSuperiorFibElement();
			cFibElement * pLastFibElement = pChoosenFibElement;
			uiNumberOfSuperior = 1;
			while ( pSuperiorFibElement ){
				//get variables defined in the superior Fib element
				list<cFibVariable*> liVariablesDefinedHere;
				
				if ( pSuperiorFibElement->getType() != 'o' ){
					
					liVariablesDefinedHere = pSuperiorFibElement->
						getDefinedVariables( ED_POSITION );
				}else{/*the superior Fib element is an erxternal object element
					-> variables are just defined for one subobject*/
					cExtObject * pSuperiorExtObjElement =
						((cExtObject*)(pSuperiorFibElement));
					const unsignedIntFib uiNumberOfSubObjects =
						pSuperiorExtObjElement->getNumberOfSubobjects();
					
					for ( unsignedIntFib uiActualSubObject = 1;
							uiActualSubObject <= uiNumberOfSubObjects;
							uiActualSubObject++ ){
						
						if ( pSuperiorExtObjElement->getSubobject(
								uiActualSubObject ) == pLastFibElement ){
							/*subobject for variables found
							-> insert its output variables as defined variables here*/
							vector< cFibVariable* > vecOutVariables = pSuperiorExtObjElement->
								getOutputVariables( uiActualSubObject );
								
							liVariablesDefinedHere.insert( liVariablesDefinedHere.begin(),
								vecOutVariables.begin(), vecOutVariables.end() );
							break;
						}
					}//find subobject for variables
				}//end if an cExtObject element
				unsigned int uiPosition = 1;
				for ( list<cFibVariable*>::iterator itrVariable = liVariablesDefinedHere.begin();
						itrVariable != liVariablesDefinedHere.end();
						itrVariable++, uiPosition++ ){
					//check if the variable is in liVariablesDefinedHigher
					list<cFibVariable*>::iterator itrFoundedVariable = find(
						liVariablesDefinedHigher.begin(), liVariablesDefinedHigher.end(),
						*itrVariable );
					if ( itrFoundedVariable == liVariablesDefinedHigher.end() ){
						cerr<<"Error: The "<< uiPosition <<"'th variable of "<<
							uiNumberOfSuperior <<"'th superior Fib element couldn't be"<<
							" found in the variable list of the variables defined higher the"<<
							" choosen Fib element."<<endl;
						iReturn++;
					}
					//remove variable from liVariablesNotDefinedHigher
					itrFoundedVariable = find( liVariablesNotDefinedHigher.begin(),
						liVariablesNotDefinedHigher.end(), *itrVariable );
					if ( itrFoundedVariable != liVariablesNotDefinedHigher.end() ){
						liVariablesNotDefinedHigher.erase( itrFoundedVariable );
					}
				}
				if ( pSuperiorFibElement->getType() == 'r' ){
					/*root-elements don't pass on defined variables to sub -roots,
					so stop checking root elements on the first root-element found*/
					break;
				}
				//check next superior Fib element
				pLastFibElement = pSuperiorFibElement;
				pSuperiorFibElement = pSuperiorFibElement->getSuperiorFibElement();
				uiNumberOfSuperior++;
			}
		}//else root-elements couldn't have defined variables higher
		
		//setVariablesNoDefinedHigher should be empty
		if ( ! liVariablesNotDefinedHigher.empty() ){
			cerr<<"Error: Not all variables given back as defined higher the"<<
				" choosen Fib element are founded defined higher the choosen Fib element."<<endl;
			for ( list<cFibVariable*>::iterator itrVariable = liVariablesNotDefinedHigher.begin();
					itrVariable != liVariablesNotDefinedHigher.end();
					itrVariable++ ){
				cerr<<"   The "<< (*itrVariable)->getValue() <<"'th variable was not found."<<endl;
			}
			iReturn++;
		}
		
		//check isDefinedVariable( ED_HIGHER ) on choosen Fib element
		uiPosition = 1;
		for ( list<cFibVariable*>::iterator itrVariable = liVariablesDefinedHigher.begin();
				itrVariable != liVariablesDefinedHigher.end();
				itrVariable++, uiPosition++ ){
			
			if ( ! pChoosenFibElement->isDefinedVariable( *itrVariable, ED_HIGHER ) ){
				cerr<<"Error: The "<< uiPosition <<
					"'th variable (number="<< (*itrVariable)->getValue() <<
					") which was given back as defined higher"<<
					" was not found by isDefinedVariable( ED_HIGHER )."<<endl;
				iReturn++;
			}
		}
		
		/*try to check isDefinedVariable( ED_HIGHER ) on choosen Fib element and
		variable not defined in the direction, but defined elsewhere (choose
		from liAllDefinedVariables)*/
		list<cFibVariable*>::iterator itrChoosenLiVariable =
			liAllDefinedVariables.begin();
		unsigned int uiNotDefinedVariablesToChecked = liAllDefinedVariables.size() / 100 + 10;
		for ( unsigned int uiVariablesChecked = 0;
				(uiVariablesChecked < liAllDefinedVariables.size()) &&
				(0 < uiNotDefinedVariablesToChecked);
				uiVariablesChecked++ ){
			
			//choos random variable from all variables
			unsigned int uiChoosenVariable = (rand() % liAllDefinedVariables.size()) / 50 + 1;
			while ( uiChoosenVariable != 0){
				itrChoosenLiVariable++;
				uiChoosenVariable--;
				if ( itrChoosenLiVariable == liAllDefinedVariables.end() ){
					itrChoosenLiVariable = liAllDefinedVariables.begin();
				}
			}
			//check if choosen variable was given back as defined higher
			list<cFibVariable*>::iterator itrFoundedVariable = find(
				liVariablesDefinedHigher.begin(), liVariablesDefinedHigher.end(),
				*itrChoosenLiVariable );
			if ( itrFoundedVariable == liVariablesDefinedHigher.end() ){
				
				if ( pChoosenFibElement->isDefinedVariable( *itrChoosenLiVariable, ED_HIGHER ) ){
					cerr<<"Error: The "<< (*itrChoosenLiVariable)->getValue() <<
						"'th variable, which was not given back as defined higher,"<<
						" was found by isDefinedVariable( ED_HIGHER )."<<endl;
					iReturn++;
				}else{
					uiNotDefinedVariablesToChecked--;
				}
			}
		}
		cout<<"The method isDefinedVariable( ED_HIGHER ) gives back correctly false for "<<
			((liAllDefinedVariables.size() / 100 + 10) - uiNotDefinedVariablesToChecked) <<
			" variable defined in the whool Fib object but not found higher"<<
			" defined of the choosen Fib element."<<endl;
		
	//check variablesAreDefined( setVariable, ED_HIGHER ) on choosen Fib element
		set<cFibVariable*> setVariablesDefinedHigher(
			liVariablesDefinedHigher.begin(), liVariablesDefinedHigher.end() );
		
		bool bAreDefinedHigher = pChoosenFibElement->variablesAreDefined(
			setVariablesDefinedHigher , ED_HIGHER );
		if ( ! bAreDefinedHigher ){
			cerr<<"Error: The method setVariablesDefined( ED_HIGHER ) "<<
				"gives not back false for all higher defined variables."<<endl;
			iReturn++;
		}
		set<cFibVariable*> setVariablesPartDefinedHigher;
		if ( ! liVariablesDefinedHigher.empty() ){
			unsigned int uiNumberOfVariables =
				rand() % liVariablesDefinedHigher.size() + 1;

			for ( unsigned int uiActualVariable = 1;
					uiActualVariable <= uiNumberOfVariables;
					uiActualVariable++ ){
				
				//insert random variable
				list<cFibVariable*>::iterator itrRandomVariable =
					liVariablesDefinedHigher.begin();
				const unsigned int uiRandomPoint =
					rand() % liVariablesDefinedHigher.size();
				for ( unsigned int uiActualVariable2 = 0;
						uiActualVariable2 < uiRandomPoint;
						uiActualVariable2++, itrRandomVariable++ ){
				}
				setVariablesPartDefinedHigher.insert( *itrRandomVariable );
			}
			
			bAreDefinedHigher = pChoosenFibElement->variablesAreDefined(
				setVariablesPartDefinedHigher, ED_HIGHER );
			if ( ! bAreDefinedHigher ){
				cerr<<"Error: The method setVariablesDefined( ED_HIGHER ) "<<
					"gives not back false for a part of higher defined variables."<<endl;
				iReturn++;
			}
		}
		cPoint point;
		cFibVariable newVariable( & point );
		setVariablesPartDefinedHigher.insert( &newVariable );
		bAreDefinedHigher = pChoosenFibElement->variablesAreDefined(
			setVariablesPartDefinedHigher, ED_HIGHER );
		if ( bAreDefinedHigher ){
			cerr<<"Error: The method setVariablesDefined( ED_HIGHER ) "<<
				"gives not back true for a part of higher defined variables and a new variable."<<endl;
			iReturn++;
		}
		

	//**check direction ED_HIGHER_EQUAL the variables from ED_HIGHER and ED_POSITION
	//check getUsedVariables( ED_HIGHER_EQUAL ) on choosen Fib element
		set<cFibVariable*> setVariablesUsedHigherEqual = pChoosenFibElement->
			getUsedVariables( ED_HIGHER_EQUAL );
		set<cFibVariable*> setVariablesUsedHigherAndEqual = setVariablesUsedHigher;
		set<cFibVariable*> setVariablesUsedHere = pChoosenFibElement->
			getUsedVariables( ED_POSITION );
		setVariablesUsedHigherAndEqual.insert( setVariablesUsedHere.begin(),
			setVariablesUsedHere.end() );

		if ( ! setVariablesUsedHigherEqual.empty() ){
			cout<<"The choosen Fib element has "<< setVariablesUsedHigher.size() <<" variables which are used higher or equal. "<<endl;
		}else{
			cout<<"The choosen Fib element has no variables which are used higher or equal. "<<endl;
		}
		if ( setVariablesUsedHigherEqual == setVariablesUsedHigherAndEqual ){
		
			cout<<"All the higher or equal used variables are correct. "<<endl;
		}else{
			cerr<<"Error: The higher or equal used variables are not correct ."<<endl;
			iReturn++;
		}
		
		//check isUsedVariable( ED_HIGHER_EQUAL ) on choosen Fib element
		uiPosition = 1;
		for ( set<cFibVariable*>::iterator itrVariable = setVariablesUsedHigherEqual.begin();
				itrVariable != setVariablesUsedHigherEqual.end();
				itrVariable++, uiPosition++ ){
			
			if ( ! pChoosenFibElement->isUsedVariable( *itrVariable, ED_HIGHER_EQUAL ) ){
				cerr<<"Error: The "<< uiPosition <<
					"'th variable (number="<< (*itrVariable)->getValue() <<
					") which was given back as used higher or equal"<<
					" was not found by isUsedVariable( ED_HIGHER_EQUAL )."<<endl;
				iReturn++;
			}
		}
		/*try to check isUsedVariable( ED_HIGHER_EQUAL ) on choosen Fib element and variable
		not used in the direction, but defined for it*/
		itrChoosenVariable = liAllDefinedVariables.begin();
		uiNotUsedVariablesToChecked = liAllDefinedVariables.size() / 100 + 10;
		for ( unsigned int uiVariablesChecked = 0;
				(uiVariablesChecked < liAllDefinedVariables.size()) &&
				(0 < uiNotUsedVariablesToChecked);
				uiVariablesChecked++ ){
			
			//choos random variable from all variables
			unsigned int uiChoosenVariable = (rand() % liAllDefinedVariables.size()) / 50 + 1;
			while ( uiChoosenVariable != 0){
				itrChoosenVariable++;
				uiChoosenVariable--;
				if ( itrChoosenVariable == liAllDefinedVariables.end() ){
					itrChoosenVariable = liAllDefinedVariables.begin();
				}
			}
			//check if choosen variable was given back as used higher
			set<cFibVariable*>::iterator itrFoundedVariable = find(
				setVariablesUsedHigherEqual.begin(), setVariablesUsedHigherEqual.end(),
				*itrChoosenVariable );
			if ( itrFoundedVariable == setVariablesUsedHigherEqual.end() ){
				
				if ( pChoosenFibElement->isUsedVariable( *itrChoosenVariable, ED_HIGHER_EQUAL ) ){
					cerr<<"Error: The "<< (*itrChoosenVariable)->getValue() <<
						"'th variable, which was not given back as used higher or equal,"<<
						" was found by isUsedVariable( ED_HIGHER_EQUAL )."<<endl;
					iReturn++;
				}else{
					uiNotUsedVariablesToChecked--;
				}
			}
		}
		cout<<"The method isUsedVariable( ED_HIGHER_EQUAL ) gives back correctly false for "<<
			((liAllDefinedVariables.size() / 100 + 10) - uiNotUsedVariablesToChecked) <<
			" variable defined in the whool Fib object but not found higher"<<
			" used of the choosen Fib element."<<endl;

		
	//check getDefinedVariables( ED_HIGHER_EQUAL ) on choosen Fib element
		list<cFibVariable*> liVariablesDefinedHigherEqual = pChoosenFibElement->
			getDefinedVariables( ED_HIGHER_EQUAL );
		
		list<cFibVariable*> liVariablesDefinedHigherAndEqual;
		if ( pChoosenFibElement->getType() != 'r' ){
			//not a root element
			liVariablesDefinedHigherAndEqual = liVariablesDefinedHigher;
		}//else root element don't propergate higher defined variables
		list<cFibVariable*> liVariablesDefinedHere = pChoosenFibElement->
			getDefinedVariables( ED_POSITION );
		liVariablesDefinedHigherAndEqual.insert(
			liVariablesDefinedHigherAndEqual.end(),
			liVariablesDefinedHere.begin(), liVariablesDefinedHere.end() );
		
		if ( ! liVariablesDefinedHigherEqual.empty() ){
			cout<<"The choosen Fib element has "<< liVariablesDefinedHigherEqual.size()
				<<" variables which are defined higher or equal. "<<endl;
		}else{
			cout<<"The choosen Fib element has no variables which are defined higher or equal. "<<endl;
		}
		if ( liVariablesDefinedHigherEqual == liVariablesDefinedHigherAndEqual ){
		
			cout<<"All the higher or equal defined variables are correct. "<<endl;
		}else{
			cerr<<"Error: The higher or equal defined variables are not correct ."<<endl;
			iReturn++;
		}

		//check isDefinedVariable( ED_HIGHER_EQUAL ) on choosen Fib element
		uiPosition = 1;
		for ( list<cFibVariable*>::iterator itrVariable = liVariablesDefinedHigherEqual.begin();
				itrVariable != liVariablesDefinedHigherEqual.end();
				itrVariable++, uiPosition++ ){
			
			if ( ! pChoosenFibElement->isDefinedVariable( *itrVariable, ED_HIGHER_EQUAL ) ){
				cerr<<"Error: The "<< uiPosition <<
					"'th variable (number="<< (*itrVariable)->getValue() <<
					") which was given back as defined higher or equal"<<
					" was not found by isDefinedVariable( ED_HIGHER_EQUAL )."<<endl;
				iReturn++;
			}
		}

		/*try to check isDefinedVariable( ED_HIGHER_EQUAL ) on choosen Fib element and
		variable not defined in the direction, but defined elsewhere (choose
		from liAllDefinedVariables)*/
		itrChoosenLiVariable = liAllDefinedVariables.begin();
		uiNotDefinedVariablesToChecked = liAllDefinedVariables.size() / 100 + 10;
		for ( unsigned int uiVariablesChecked = 0;
				(uiVariablesChecked < liAllDefinedVariables.size()) &&
				(0 < uiNotDefinedVariablesToChecked);
				uiVariablesChecked++ ){
			
			//choos random variable from all variables
			unsigned int uiChoosenVariable = (rand() % liAllDefinedVariables.size()) / 50 + 1;
			while ( uiChoosenVariable != 0){
				itrChoosenLiVariable++;
				uiChoosenVariable--;
				if ( itrChoosenLiVariable == liAllDefinedVariables.end() ){
					itrChoosenLiVariable = liAllDefinedVariables.begin();
				}
			}
			//check if choosen variable was given back as defined higher
			list<cFibVariable*>::iterator itrFoundedVariable = find(
				liVariablesDefinedHigherEqual.begin(), liVariablesDefinedHigherEqual.end(),
				*itrChoosenLiVariable );
			if ( itrFoundedVariable == liVariablesDefinedHigherEqual.end() ){
				
				if ( pChoosenFibElement->isDefinedVariable( *itrChoosenLiVariable, ED_HIGHER_EQUAL ) ){
					cerr<<"Error: The "<< (*itrChoosenLiVariable)->getValue() <<
						"'th variable, which was not given back as defined higher or equal,"<<
						" was found by isDefinedVariable( ED_HIGHER_EQUAL )."<<endl;
					iReturn++;
				}else{
					uiNotDefinedVariablesToChecked--;
				}
			}
		}
		cout<<"The method isDefinedVariable( ED_HIGHER_EQUAL ) gives back correctly false for "<<
			((liAllDefinedVariables.size() / 100 + 10) - uiNotDefinedVariablesToChecked) <<
			" variable defined in the whool Fib object but not found higher or equal"<<
			" defined of the choosen Fib element."<<endl;
		
	//check variablesAreDefined( setVariable, ED_HIGHER_EQUAL ) on choosen Fib element
		set<cFibVariable*> setVariablesDefinedHigherEqual(
			liVariablesDefinedHigherEqual.begin(), liVariablesDefinedHigherEqual.end() );
		
		bool bAreDefinedHigherEqual = pChoosenFibElement->variablesAreDefined(
			setVariablesDefinedHigherEqual , ED_HIGHER_EQUAL );
		if ( ! bAreDefinedHigherEqual ){
			cerr<<"Error: The method setVariablesDefined( ED_HIGHER_EQUAL ) "<<
				"gives not back false for all higher defined variables."<<endl;
			iReturn++;
		}
		set<cFibVariable*> setVariablesPartDefinedHigherEqual;
		if ( ! liVariablesDefinedHigherEqual.empty() ){
			unsigned int uiNumberOfVariables =
				rand() % liVariablesDefinedHigherEqual.size() + 1;

			for ( unsigned int uiActualVariable = 1;
					uiActualVariable <= uiNumberOfVariables;
					uiActualVariable++ ){
				
				//insert random variable
				list<cFibVariable*>::iterator itrRandomVariable =
					liVariablesDefinedHigherEqual.begin();
				const unsigned int uiRandomPoint =
					rand() % liVariablesDefinedHigherEqual.size();
				for ( unsigned int uiActualVariable2 = 0;
						uiActualVariable2 < uiRandomPoint;
						uiActualVariable2++, itrRandomVariable++ ){
				}
				setVariablesPartDefinedHigherEqual.insert( *itrRandomVariable );
			}
			
			bAreDefinedHigherEqual = pChoosenFibElement->variablesAreDefined(
				setVariablesPartDefinedHigherEqual, ED_HIGHER_EQUAL );
			if ( ! bAreDefinedHigherEqual ){
				cerr<<"Error: The method setVariablesDefined( ED_HIGHER_EQUAL ) "<<
					"gives not back false for a part of higher defined variables."<<endl;
				iReturn++;
			}
		}
		setVariablesPartDefinedHigherEqual.insert( &newVariable );
		bAreDefinedHigherEqual = pChoosenFibElement->variablesAreDefined(
			setVariablesPartDefinedHigherEqual, ED_HIGHER_EQUAL );
		if ( bAreDefinedHigherEqual ){
			cerr<<"Error: The method setVariablesDefined( ED_HIGHER_EQUAL ) "<<
				"gives not back true for a part of higher defined variables and a new variable."<<endl;
			iReturn++;
		}


	
	//**check direction ED_BELOW
	//check getUsedVariables( ED_BELOW ) on choosen Fib element
		set<cFibVariable*> setVariablesUsedBelow = pChoosenFibElement->
			getUsedVariables( ED_BELOW );
		set<cFibVariable*> setVariablesNotUsedBelow = setVariablesUsedBelow;
		
		if ( ! setVariablesUsedBelow.empty() ){
			cout<<"The choosen Fib element has "<< setVariablesUsedBelow.size() <<
				" variables which are used below. "<<endl;
		}else{
			cout<<"The choosen Fib element has no variables which are used below. "<<endl;
		}
		
		/*check if the variables are realy used below (is in all next
		Fib elements)*/
		cFibElement * pNextFibElement = pChoosenFibElement->getNextFibElement();
		unsigned int uiNumberOfNext = 1;
		const unsigned int uiNumberOfFibElements =
			pChoosenFibElement->getNumberOfElements();
		//search the next -Fib elements which are below
		while ( (pNextFibElement) && (uiNumberOfNext < uiNumberOfFibElements) ){
			//get variables used in the next Fib element
			set<cFibVariable*> setVariablesUsedHere = pNextFibElement->
				getUsedVariables( ED_POSITION );
			
			unsigned int uiPosition = 1;
			for ( set<cFibVariable*>::iterator itrVariable = setVariablesUsedHere.begin();
					itrVariable != setVariablesUsedHere.end();
					itrVariable++, uiPosition++ ){
				//check if the variable is in setVariablesUsedBelow
				set<cFibVariable*>::iterator itrFoundedVariable = find(
					setVariablesUsedBelow.begin(), setVariablesUsedBelow.end(),
					*itrVariable );
				if ( itrFoundedVariable == setVariablesUsedBelow.end() ){
					cerr<<"Error: The "<< uiPosition <<"'th variable of "<<
						uiNumberOfNext <<"'th next Fib element couldn't be"<<
						" found in the variable list of the variables used below the"<<
						" choosen Fib element."<<endl;
					iReturn++;
				}
				//remove variable from setVariablesNotUsedBelow
				itrFoundedVariable = find( setVariablesNotUsedBelow.begin(),
					setVariablesNotUsedBelow.end(), *itrVariable );
				if ( itrFoundedVariable != setVariablesNotUsedBelow.end() ){
					setVariablesNotUsedBelow.erase( itrFoundedVariable );
				}
			}
			//check next next Fib element
			pNextFibElement = pNextFibElement->getNextFibElement();
			uiNumberOfNext++;
		}
		//setVariablesNotUsedBelow should be empty
		if ( ! setVariablesNotUsedBelow.empty() ){
			cerr<<"Error: Not all variables given back as used below the"<<
				" choosen Fib element are founded used below the choosen Fib element."<<endl;
			for ( set<cFibVariable*>::iterator itrVariable = setVariablesNotUsedBelow.begin();
					itrVariable != setVariablesNotUsedBelow.end();
					itrVariable++ ){
				cerr<<"   The "<< (*itrVariable)->getValue() <<"'th variable was not found."<<endl;
			}
			iReturn++;
		}
		
		/*check isUsedVariable( ED_BELOW ) on choosen Fib element for all
		variables in setVariablesUsedBelow*/
		uiPosition = 1;
		for ( set<cFibVariable*>::iterator itrVariable = setVariablesUsedBelow.begin();
				itrVariable != setVariablesUsedBelow.end();
				itrVariable++, uiPosition++ ){
			
			if ( ! pChoosenFibElement->isUsedVariable( *itrVariable, ED_BELOW ) ){
				cerr<<"Error: The "<< uiPosition <<
					"'th variable (number="<< (*itrVariable)->getValue() <<
					") which was given back as used below"<<
					" was not found by isUsedVariable( ED_BELOW )."<<endl;
				iReturn++;
			}
		}
		/*try to check isUsedVariable( ED_BELOW ) on choosen Fib element and variable
		not used in the direction, but defined for it*/
		itrChoosenVariable = liAllDefinedVariables.begin();
		uiNotUsedVariablesToChecked = liAllDefinedVariables.size() / 100 + 10;
		for ( unsigned int uiVariablesChecked = 0;
				(uiVariablesChecked < liAllDefinedVariables.size()) &&
				(0 < uiNotUsedVariablesToChecked);
				uiVariablesChecked++ ){
			
			//choos random variable from all variables
			unsigned int uiChoosenVariable = (rand() % liAllDefinedVariables.size()) / 50 + 1;
			while ( uiChoosenVariable != 0){
				itrChoosenVariable++;
				uiChoosenVariable--;
				if ( itrChoosenVariable == liAllDefinedVariables.end() ){
					itrChoosenVariable = liAllDefinedVariables.begin();
				}
			}
			//check if choosen variable was given back as used below
			set<cFibVariable*>::iterator itrFoundedVariable = find(
				setVariablesUsedBelow.begin(), setVariablesUsedBelow.end(),
				*itrChoosenVariable );
			if ( itrFoundedVariable == setVariablesUsedBelow.end() ){
				
				if ( pChoosenFibElement->isUsedVariable( *itrChoosenVariable, ED_BELOW ) ){
					cerr<<"Error: The "<< (*itrChoosenVariable)->getValue() <<
						"'th variable, which was not given back as used below,"<<
						" was found by isUsedVariable( ED_BELOW )."<<endl;
					iReturn++;
				}else{
					uiNotUsedVariablesToChecked--;
				}
			}
		}
		cout<<"The method isUsedVariable( ED_BELOW ) gives back correctly false for "<<
			((liAllDefinedVariables.size() / 100 + 10) - uiNotUsedVariablesToChecked) <<
			" variable defined in the whool Fib object but not found below"<<
			" used of the choosen Fib element."<<endl;
		
	
	//check getDefinedVariables( ED_BELOW ) on choosen Fib element
		list<cFibVariable*> liVariablesDefinedBelow = pChoosenFibElement->
			getDefinedVariables( ED_BELOW );
		list<cFibVariable*> liVariablesNotDefinedBelow = liVariablesDefinedBelow;
		
		if ( ! liVariablesDefinedBelow.empty() ){
			cout<<"The choosen Fib element has "<< liVariablesDefinedBelow.size()
				<<" variables which are defined below. "<<endl;
		}else{
			cout<<"The choosen Fib element has no variables which are defined below. "<<endl;
		}
		
		/*check if the variables are realy defined below (is in all next
		Fib elements)*/
		pNextFibElement = pChoosenFibElement->getNextFibElement();
		uiNumberOfNext = 1;
		//search the next -Fib elements which are below
		while ( (pNextFibElement) && (uiNumberOfNext < uiNumberOfFibElements)
#ifndef FEATURE_NEW_ROOT_GET_DEFINED_VARIBLES
				&& ( pNextFibElement->getType() != 'r' )
#endif //FEATURE_NEW_ROOT_GET_DEFINED_VARIBLES
				){
			//get variables defined in the next Fib element
			list<cFibVariable*> liVariablesDefinedHere = pNextFibElement->
				getDefinedVariables( ED_POSITION );
			
			unsigned int uiPosition = 1;
			for ( list<cFibVariable*>::iterator itrVariable = liVariablesDefinedHere.begin();
					itrVariable != liVariablesDefinedHere.end();
					itrVariable++, uiPosition++ ){
				//check if the variable is in liVariablesDefinedBelow
				list<cFibVariable*>::iterator itrFoundedVariable = find(
					liVariablesDefinedBelow.begin(), liVariablesDefinedBelow.end(),
					*itrVariable );
				if ( itrFoundedVariable == liVariablesDefinedBelow.end() ){
					cerr<<"Error: The "<< uiPosition <<"'th variable of "<<
						uiNumberOfNext <<"'th next Fib element couldn't be"<<
						" found in the variable list of the variables defined below the"<<
						" choosen Fib element."<<endl;
					iReturn++;
				}
				//remove variable from liVariablesNotDefinedBelow
				itrFoundedVariable = find( liVariablesNotDefinedBelow.begin(),
					liVariablesNotDefinedBelow.end(), *itrVariable );
				if ( itrFoundedVariable != liVariablesNotDefinedBelow.end() ){
					liVariablesNotDefinedBelow.erase( itrFoundedVariable );
				}
			}
#ifndef FEATURE_NEW_ROOT_GET_DEFINED_VARIBLES
			if ( pNextFibElement->getType() == 'r' ){
				/*root-elements don't pass on defined variables to sub -roots,
				so stop checking root elements on the first root-element found*/
				break;
			}
#endif //FEATURE_NEW_ROOT_GET_DEFINED_VARIBLES
			//check next next Fib element
			pNextFibElement = pNextFibElement->getNextFibElement();
			uiNumberOfNext++;
		}
		
		//setVariablesNoDefinedBelow should be empty
		if ( ! liVariablesNotDefinedBelow.empty() ){
			cerr<<"Error: Not all variables given back as defined below the"<<
				" choosen Fib element are founded defined below the choosen Fib element."<<endl;
			for ( list<cFibVariable*>::iterator itrVariable = liVariablesNotDefinedBelow.begin();
					itrVariable != liVariablesNotDefinedBelow.end();
					itrVariable++ ){
				cerr<<"   The "<< (*itrVariable)->getValue() <<"'th variable was not found."<<endl;
			}
			iReturn++;
		}
		
		//check isDefinedVariable( ED_BELOW ) on choosen Fib element
		uiPosition = 1;
		for ( list<cFibVariable*>::iterator itrVariable = liVariablesDefinedBelow.begin();
				itrVariable != liVariablesDefinedBelow.end();
				itrVariable++, uiPosition++ ){
			
			if ( ! pChoosenFibElement->isDefinedVariable( *itrVariable, ED_BELOW ) ){
				cerr<<"Error: The "<< uiPosition <<
					"'th variable (number="<< (*itrVariable)->getValue() <<
					") which was given back as defined below"<<
					" was not found by isDefinedVariable( ED_BELOW )."<<endl;
				iReturn++;
			}
		}
		
		/*try to check isDefinedVariable( ED_BELOW ) on choosen Fib element and
		variable not defined in the direction, but defined elsewhere (choose
		from liAllDefinedVariables)*/
		itrChoosenLiVariable = liAllDefinedVariables.begin();
		uiNotDefinedVariablesToChecked = liAllDefinedVariables.size() / 100 + 10;
		for ( unsigned int uiVariablesChecked = 0;
				(uiVariablesChecked < liAllDefinedVariables.size()) &&
				(0 < uiNotDefinedVariablesToChecked);
				uiVariablesChecked++ ){
			
			//choos random variable from all variables
			unsigned int uiChoosenVariable = (rand() % liAllDefinedVariables.size()) / 50 + 1;
			while ( uiChoosenVariable != 0){
				itrChoosenLiVariable++;
				uiChoosenVariable--;
				if ( itrChoosenLiVariable == liAllDefinedVariables.end() ){
					itrChoosenLiVariable = liAllDefinedVariables.begin();
				}
			}
			//check if choosen variable was given back as defined below
			list<cFibVariable*>::iterator itrFoundedVariable = find(
				liVariablesDefinedBelow.begin(), liVariablesDefinedBelow.end(),
				*itrChoosenLiVariable );
			if ( itrFoundedVariable == liVariablesDefinedBelow.end() ){
				
				if ( pChoosenFibElement->isDefinedVariable( *itrChoosenLiVariable, ED_BELOW ) ){
					cerr<<"Error: The "<< (*itrChoosenLiVariable)->getValue() <<
						"'th variable, which was not given back as defined below,"<<
						" was found by isDefinedVariable( ED_BELOW )."<<endl;
					iReturn++;
				}else{
					uiNotDefinedVariablesToChecked--;
				}
			}
		}
		cout<<"The method isDefinedVariable( ED_BELOW ) gives back correctly false for "<<
			((liAllDefinedVariables.size() / 100 + 10) - uiNotDefinedVariablesToChecked) <<
			" variable defined in the whool Fib object but not found below"<<
			" defined of the choosen Fib element."<<endl;

	//check variablesAreDefined( setVariable, ED_BELOW ) on choosen Fib element
		set<cFibVariable*> setVariablesDefinedBelow(
			liVariablesDefinedBelow.begin(), liVariablesDefinedBelow.end() );
		
		bool bAreDefinedBelow = pChoosenFibElement->variablesAreDefined(
			setVariablesDefinedBelow , ED_BELOW );
		if ( ! bAreDefinedBelow ){
			cerr<<"Error: The method setVariablesDefined( ED_BELOW ) "<<
				"gives not back false for all higher defined variables."<<endl;
			iReturn++;
		}
		set<cFibVariable*> setVariablesPartDefinedBelow;
		if ( ! liVariablesDefinedBelow.empty() ){
			unsigned int uiNumberOfVariables =
				rand() % liVariablesDefinedBelow.size() + 1;

			for ( unsigned int uiActualVariable = 1;
					uiActualVariable <= uiNumberOfVariables;
					uiActualVariable++ ){
				
				//insert random variable
				list<cFibVariable*>::iterator itrRandomVariable =
					liVariablesDefinedBelow.begin();
				const unsigned int uiRandomPoint =
					rand() % liVariablesDefinedBelow.size();
				for ( unsigned int uiActualVariable2 = 0;
						uiActualVariable2 < uiRandomPoint;
						uiActualVariable2++, itrRandomVariable++ ){
				}
				setVariablesPartDefinedBelow.insert( *itrRandomVariable );
			}
			
			bAreDefinedBelow = pChoosenFibElement->variablesAreDefined(
				setVariablesPartDefinedBelow, ED_BELOW );
			if ( ! bAreDefinedBelow ){
				cerr<<"Error: The method setVariablesDefined( ED_BELOW ) "<<
					"gives not back false for a part of higher defined variables."<<endl;
				iReturn++;
			}
		}
		setVariablesPartDefinedBelow.insert( &newVariable );
		bAreDefinedBelow = pChoosenFibElement->variablesAreDefined(
			setVariablesPartDefinedBelow, ED_BELOW );
		if ( bAreDefinedBelow ){
			cerr<<"Error: The method setVariablesDefined( ED_BELOW ) "<<
				"gives not back true for a part of higher defined variables and a new variable."<<endl;
			iReturn++;
		}


	//**check direction ED_BELOW_EQUAL the variables from ED_BELOW and ED_POSITION
	//check getUsedVariables( ED_BELOW_EQUAL ) on choosen Fib element
		set<cFibVariable*> setVariablesUsedBelowEqual = pChoosenFibElement->
			getUsedVariables( ED_BELOW_EQUAL );
		set<cFibVariable*> setVariablesUsedBelowAndEqual = setVariablesUsedBelow;
		setVariablesUsedHere = pChoosenFibElement->getUsedVariables( ED_POSITION );
		setVariablesUsedBelowAndEqual.insert( setVariablesUsedHere.begin(),
			setVariablesUsedHere.end() );

		if ( ! setVariablesUsedBelowEqual.empty() ){
			cout<<"The choosen Fib element has "<< setVariablesUsedBelow.size() <<
				" variables which are used below or equal. "<<endl;
		}else{
			cout<<"The choosen Fib element has no variables which are used below or equal. "<<endl;
		}
		if ( setVariablesUsedBelowEqual == setVariablesUsedBelowAndEqual ){
		
			cout<<"All the below or equal used variables are correct. "<<endl;
		}else{
			cerr<<"Error: The below or equal used variables are not correct ."<<endl;
			iReturn++;
		}
		
		//check isUsedVariable( ED_BELOW_EQUAL ) on choosen Fib element
		uiPosition = 1;
		for ( set<cFibVariable*>::iterator itrVariable = setVariablesUsedBelowEqual.begin();
				itrVariable != setVariablesUsedBelowEqual.end();
				itrVariable++, uiPosition++ ){
			
			if ( ! pChoosenFibElement->isUsedVariable( *itrVariable, ED_BELOW_EQUAL ) ){
				cerr<<"Error: The "<< uiPosition <<
					"'th variable (number="<< (*itrVariable)->getValue() <<
					") which was given back as used below"<<
					" was not found by isUsedVariable( ED_BELOW_EQUAL )."<<endl;
				iReturn++;
			}
		}
		/*try to check isUsedVariable( ED_BELOW_EQUAL ) on choosen Fib element and variable
		not used in the direction, but defined for it*/
		itrChoosenVariable = liAllDefinedVariables.begin();
		uiNotUsedVariablesToChecked = liAllDefinedVariables.size() / 100 + 10;
		for ( unsigned int uiVariablesChecked = 0;
				(uiVariablesChecked < liAllDefinedVariables.size()) &&
				(0 < uiNotUsedVariablesToChecked);
				uiVariablesChecked++ ){
			
			//choos random variable from all variables
			unsigned int uiChoosenVariable = (rand() % liAllDefinedVariables.size()) / 50 + 1;
			while ( uiChoosenVariable != 0){
				itrChoosenVariable++;
				uiChoosenVariable--;
				if ( itrChoosenVariable == liAllDefinedVariables.end() ){
					itrChoosenVariable = liAllDefinedVariables.begin();
				}
			}
			//check if choosen variable was given back as used below
			set<cFibVariable*>::iterator itrFoundedVariable = find(
				setVariablesUsedBelowEqual.begin(), setVariablesUsedBelowEqual.end(),
				*itrChoosenVariable );
			if ( itrFoundedVariable == setVariablesUsedBelowEqual.end() ){
				
				if ( pChoosenFibElement->isUsedVariable( *itrChoosenVariable, ED_BELOW_EQUAL ) ){
					cerr<<"Error: The "<< (*itrChoosenVariable)->getValue() <<
						"'th variable, which was not given back as used below or equal,"<<
						" was found by isUsedVariable( ED_BELOW_EQUAL )."<<endl;
					iReturn++;
				}else{
					uiNotUsedVariablesToChecked--;
				}
			}
		}
		cout<<"The method isUsedVariable( ED_BELOW_EQUAL ) gives back correctly false for "<<
			((liAllDefinedVariables.size() / 100 + 10) - uiNotUsedVariablesToChecked) <<
			" variable defined in the whool Fib object but not found below"<<
			" used of the choosen Fib element."<<endl;

		
	//check getDefinedVariables( ED_BELOW_EQUAL ) on choosen Fib element
		list<cFibVariable*> liVariablesDefinedBelowEqual = pChoosenFibElement->
			getDefinedVariables( ED_BELOW_EQUAL );
		
		list<cFibVariable*> liVariablesDefinedBelowAndEqual = liVariablesDefinedBelow;
		liVariablesDefinedHere = pChoosenFibElement->getDefinedVariables( ED_POSITION );
		liVariablesDefinedBelowAndEqual.insert(
			liVariablesDefinedBelowAndEqual.begin(),
			liVariablesDefinedHere.begin(), liVariablesDefinedHere.end() );
		
		if ( ! liVariablesDefinedBelowEqual.empty() ){
			cout<<"The choosen Fib element has "<< liVariablesDefinedBelowEqual.size()
				<<" variables which are defined below or equal. "<<endl;
		}else{
			cout<<"The choosen Fib element has no variables which are defined below or equal. "<<endl;
		}
		if ( liVariablesDefinedBelowEqual == liVariablesDefinedBelowAndEqual ){
		
			cout<<"All the below or equal defined variables are correct. "<<endl;
		}else{
			cerr<<"Error: The below or equal defined variables are not correct ."<<endl;
			iReturn++;
		}

		//check isDefinedVariable( ED_BELOW_EQUAL ) on choosen Fib element
		uiPosition = 1;
		for ( list<cFibVariable*>::iterator itrVariable = liVariablesDefinedBelowEqual.begin();
				itrVariable != liVariablesDefinedBelowEqual.end();
				itrVariable++, uiPosition++ ){
			
			if ( ! pChoosenFibElement->isDefinedVariable( *itrVariable, ED_BELOW_EQUAL ) ){
				cerr<<"Error: The "<< uiPosition <<
					"'th variable (number="<< (*itrVariable)->getValue() <<
					") which was given back as defined below or equal"<<
					" was not found by isDefinedVariable( ED_BELOW_EQUAL )."<<endl;
				iReturn++;
			}
		}

		/*try to check isDefinedVariable( ED_BELOW_EQUAL ) on choosen Fib element and
		variable not defined in the direction, but defined elsewhere (choose
		from liAllDefinedVariables)*/
		itrChoosenLiVariable = liAllDefinedVariables.begin();
		uiNotDefinedVariablesToChecked = liAllDefinedVariables.size() / 100 + 10;
		for ( unsigned int uiVariablesChecked = 0;
				(uiVariablesChecked < liAllDefinedVariables.size()) &&
				(0 < uiNotDefinedVariablesToChecked);
				uiVariablesChecked++ ){
			
			//choos random variable from all variables
			unsigned int uiChoosenVariable = (rand() % liAllDefinedVariables.size()) / 50 + 1;
			while ( uiChoosenVariable != 0){
				itrChoosenLiVariable++;
				uiChoosenVariable--;
				if ( itrChoosenLiVariable == liAllDefinedVariables.end() ){
					itrChoosenLiVariable = liAllDefinedVariables.begin();
				}
			}
			//check if choosen variable was given back as defined below
			list<cFibVariable*>::iterator itrFoundedVariable = find(
				liVariablesDefinedBelowEqual.begin(), liVariablesDefinedBelowEqual.end(),
				*itrChoosenLiVariable );
			if ( itrFoundedVariable == liVariablesDefinedBelowEqual.end() ){
				
				if ( pChoosenFibElement->isDefinedVariable( *itrChoosenLiVariable, ED_BELOW_EQUAL ) ){
					cerr<<"Error: The "<< (*itrChoosenLiVariable)->getValue() <<
						"'th variable, which was not given back as defined below or equal,"<<
						" was found by isDefinedVariable( ED_BELOW_EQUAL )."<<endl;
					iReturn++;
				}else{
					uiNotDefinedVariablesToChecked--;
				}
			}
		}
		cout<<"The method isDefinedVariable( ED_BELOW_EQUAL ) gives back correctly false for "<<
			((liAllDefinedVariables.size() / 100 + 10) - uiNotDefinedVariablesToChecked) <<
			" variable defined in the whool Fib object but not found below or equal"<<
			" defined of the choosen Fib element."<<endl;

	//check variablesAreDefined( setVariable, ED_BELOW_EQUAL ) on choosen Fib element
		set<cFibVariable*> setVariablesDefinedBelowEqual(
			liVariablesDefinedBelowEqual.begin(), liVariablesDefinedBelowEqual.end() );
		
		bool bAreDefinedBelowEqual = pChoosenFibElement->variablesAreDefined(
			setVariablesDefinedBelowEqual , ED_BELOW_EQUAL );
		if ( ! bAreDefinedBelowEqual ){
			cerr<<"Error: The method setVariablesDefined( ED_BELOW_EQUAL ) "<<
				"gives not back false for all higher defined variables."<<endl;
			iReturn++;
		}
		set<cFibVariable*> setVariablesPartDefinedBelowEqual;
		if ( ! liVariablesDefinedBelowEqual.empty() ){
			unsigned int uiNumberOfVariables =
				rand() % liVariablesDefinedBelowEqual.size() + 1;

			for ( unsigned int uiActualVariable = 1;
					uiActualVariable <= uiNumberOfVariables;
					uiActualVariable++ ){
				
				//insert random variable
				list<cFibVariable*>::iterator itrRandomVariable =
					liVariablesDefinedBelowEqual.begin();
				const unsigned int uiRandomPoint =
					rand() % liVariablesDefinedBelowEqual.size();
				for ( unsigned int uiActualVariable2 = 0;
						uiActualVariable2 < uiRandomPoint;
						uiActualVariable2++, itrRandomVariable++ ){
				}
				setVariablesPartDefinedBelowEqual.insert( *itrRandomVariable );
			}
			
			bAreDefinedBelowEqual = pChoosenFibElement->variablesAreDefined(
				setVariablesPartDefinedBelowEqual, ED_BELOW_EQUAL );
			if ( ! bAreDefinedBelowEqual ){
				cerr<<"Error: The method setVariablesDefined( ED_BELOW_EQUAL ) "<<
					"gives not back false for a part of higher defined variables."<<endl;
				iReturn++;
			}
		}
		setVariablesPartDefinedBelowEqual.insert( &newVariable );
		bAreDefinedBelowEqual = pChoosenFibElement->variablesAreDefined(
			setVariablesPartDefinedBelowEqual, ED_BELOW_EQUAL );
		if ( bAreDefinedBelowEqual ){
			cerr<<"Error: The method setVariablesDefined( ED_BELOW_EQUAL ) "<<
				"gives not back true for a part of higher defined variables and a new variable."<<endl;
			iReturn++;
		}



		
	//**check direction ED_ALL the variables from ED_HIGHER_EQUAL and ED_BELOW
	//check getUsedVariables( ED_ALL ) on choosen Fib element
		set<cFibVariable*> setVariablesUsedAll = pChoosenFibElement->
			getUsedVariables( ED_ALL );
		set<cFibVariable*> setVariablesUsedHigherHigherEqualBelow =
			setVariablesUsedHigherEqual;

		setVariablesUsedHigherHigherEqualBelow.insert(
			setVariablesUsedBelow.begin(), setVariablesUsedBelow.end() );

		if ( ! setVariablesUsedAll.empty() ){
			cout<<"The choosen Fib element has "<< setVariablesUsedAll.size() <<
				" variables which are used in all directions. "<<endl;
		}else{
			cout<<"The choosen Fib element has no variables which are used in all directions. "<<endl;
		}
		if ( setVariablesUsedAll == setVariablesUsedHigherHigherEqualBelow ){
		
			cout<<"All the in all directions used variables are correct. "<<endl;
		}else{
			cerr<<"Error: The in all directions used variables are not correct ."<<endl;
			iReturn++;
		}

		//check isUsedVariable( ED_ALL ) on choosen Fib element
		uiPosition = 1;
		for ( set<cFibVariable*>::iterator itrVariable = setVariablesUsedAll.begin();
				itrVariable != setVariablesUsedAll.end();
				itrVariable++, uiPosition++ ){
			
			if ( ! pChoosenFibElement->isUsedVariable( *itrVariable, ED_ALL ) ){
				cerr<<"Error: The "<< uiPosition <<
					"'th variable (number="<< (*itrVariable)->getValue() <<
					") which was given back as used in all directions"<<
					" was not found by isUsedVariable( ED_ALL )."<<endl;
				iReturn++;
			}
		}

		/*try to check isUsedVariable( ED_ALL ) on choosen Fib element and variable
		not used in the direction, but defined for it*/
		itrChoosenVariable = liAllDefinedVariables.begin();
		uiNotUsedVariablesToChecked = liAllDefinedVariables.size() / 100 + 10;
		for ( unsigned int uiVariablesChecked = 0;
				(uiVariablesChecked < liAllDefinedVariables.size()) &&
				(0 < uiNotUsedVariablesToChecked);
				uiVariablesChecked++ ){
			
			//choos random variable from all variables
			unsigned int uiChoosenVariable = (rand() % liAllDefinedVariables.size()) / 50 + 1;
			while ( uiChoosenVariable != 0){
				itrChoosenVariable++;
				uiChoosenVariable--;
				if ( itrChoosenVariable == liAllDefinedVariables.end() ){
					itrChoosenVariable = liAllDefinedVariables.begin();
				}
			}
			//check if choosen variable was given back as used higher
			set<cFibVariable*>::iterator itrFoundedVariable = find(
				setVariablesUsedAll.begin(), setVariablesUsedAll.end(),
				*itrChoosenVariable );
			if ( itrFoundedVariable == setVariablesUsedAll.end() ){
				
				if ( pChoosenFibElement->isUsedVariable( *itrChoosenVariable, ED_ALL ) ){
					cerr<<"Error: The "<< (*itrChoosenVariable)->getValue() <<
						"'th variable, which was not given back as used in all directions,"<<
						" was found by isUsedVariable( ED_ALL )."<<endl;
					iReturn++;
				}else{
					uiNotUsedVariablesToChecked--;
				}
			}
		}
		cout<<"The method isUsedVariable( ED_HIGHER_EQUAL ) gives back correctly false for "<<
			((liAllDefinedVariables.size() / 100 + 10) - uiNotUsedVariablesToChecked) <<
			" variable defined in the whool Fib object but not found higher"<<
			" used of the choosen Fib element."<<endl;

		
		//check getDefinedVariables( ED_ALL ) on choosen Fib element
		list<cFibVariable*> liVariablesDefinedAll = pChoosenFibElement->
			getDefinedVariables( ED_ALL );
		
		list<cFibVariable*> liVariablesDefinedHigherEqualBelow =
			liVariablesDefinedHigher;
		liVariablesDefinedHigherEqualBelow.insert(
			liVariablesDefinedHigherEqualBelow.end(),
			liVariablesDefinedHere.begin(), liVariablesDefinedHere.end() );
		liVariablesDefinedHigherEqualBelow.insert(
			liVariablesDefinedHigherEqualBelow.end(),
			liVariablesDefinedBelow.begin(), liVariablesDefinedBelow.end() );
		
		if ( ! liVariablesDefinedAll.empty() ){
			cout<<"The choosen Fib element has "<< liVariablesDefinedAll.size()
				<<" variables which are defined in all directions. "<<endl;
		}else{
			cout<<"The choosen Fib element has no variables which are defined in all directions. "<<endl;
		}
		if ( liVariablesDefinedAll == liVariablesDefinedHigherEqualBelow ){
		
			cout<<"All the in all directions defined variables are correct. "<<endl;
		}else{
			cerr<<"Error: The in all directions defined variables are not correct ."<<endl;
			iReturn++;
		}

		//check isDefinedVariable( ED_ALL ) on choosen Fib element
		uiPosition = 1;
		for ( list<cFibVariable*>::iterator itrVariable = liVariablesDefinedAll.begin();
				itrVariable != liVariablesDefinedAll.end();
				itrVariable++, uiPosition++ ){
			
			if ( ! pChoosenFibElement->isDefinedVariable( *itrVariable, ED_ALL ) ){
				cerr<<"Error: The "<< uiPosition <<
					"'th variable (number="<< (*itrVariable)->getValue() <<
					") which was given back as defined in all directions"<<
					" was not found by isDefinedVariable( ED_ALL )."<<endl;
				iReturn++;
			}
		}
		
		/*try to check isDefinedVariable( ED_ALL ) on choosen Fib element and
		variable not defined in the direction, but defined elsewhere (choose
		from liAllDefinedVariables)*/
		itrChoosenLiVariable = liAllDefinedVariables.begin();
		uiNotDefinedVariablesToChecked = liAllDefinedVariables.size() / 100 + 10;
		for ( unsigned int uiVariablesChecked = 0;
				(uiVariablesChecked < liAllDefinedVariables.size()) &&
				(0 < uiNotDefinedVariablesToChecked);
				uiVariablesChecked++ ){
			
			//choos random variable from all variables
			unsigned int uiChoosenVariable = (rand() % liAllDefinedVariables.size()) / 50 + 1;
			while ( uiChoosenVariable != 0){
				itrChoosenLiVariable++;
				uiChoosenVariable--;
				if ( itrChoosenLiVariable == liAllDefinedVariables.end() ){
					itrChoosenLiVariable = liAllDefinedVariables.begin();
				}
			}
			//check if choosen variable was given back as defined higher
			list<cFibVariable*>::iterator itrFoundedVariable = find(
				liVariablesDefinedAll.begin(), liVariablesDefinedAll.end(),
				*itrChoosenLiVariable );
			if ( itrFoundedVariable == liVariablesDefinedAll.end() ){
				
				if ( pChoosenFibElement->isDefinedVariable( *itrChoosenLiVariable, ED_ALL ) ){
					cerr<<"Error: The "<< (*itrChoosenLiVariable)->getValue() <<
						"'th variable, which was not given back as defined in all directions,"<<
						" was found by isDefinedVariable( ED_ALL )."<<endl;
					iReturn++;
				}else{
					uiNotDefinedVariablesToChecked--;
				}
			}
		}
		cout<<"The method isDefinedVariable( ED_ALL ) gives back correctly false for "<<
			((liAllDefinedVariables.size() / 100 + 10) - uiNotDefinedVariablesToChecked) <<
			" variable defined in the whool Fib object but not found in all directions"<<
			" defined of the choosen Fib element."<<endl;

	//check variablesAreDefined( setVariable, ED_ALL ) on choosen Fib element
		set<cFibVariable*> setVariablesDefinedAll(
			liVariablesDefinedAll.begin(), liVariablesDefinedAll.end() );
		
		bool bAreDefinedAll = pChoosenFibElement->variablesAreDefined(
			setVariablesDefinedAll , ED_ALL );
		if ( ! bAreDefinedAll ){
			cerr<<"Error: The method setVariablesDefined( ED_ALL ) "<<
				"gives not back false for all higher defined variables."<<endl;
			iReturn++;
		}
		set<cFibVariable*> setVariablesPartDefinedAll;
		if ( ! liVariablesDefinedAll.empty() ){
			unsigned int uiNumberOfVariables =
				rand() % liVariablesDefinedAll.size() + 1;

			for ( unsigned int uiActualVariable = 1;
					uiActualVariable <= uiNumberOfVariables;
					uiActualVariable++ ){
				
				//insert random variable
				list<cFibVariable*>::iterator itrRandomVariable =
					liVariablesDefinedAll.begin();
				const unsigned int uiRandomPoint =
					rand() % liVariablesDefinedAll.size();
				for ( unsigned int uiActualVariable2 = 0;
						uiActualVariable2 < uiRandomPoint;
						uiActualVariable2++, itrRandomVariable++ ){
				}
				setVariablesPartDefinedAll.insert( *itrRandomVariable );
			}
			
			bAreDefinedAll = pChoosenFibElement->variablesAreDefined(
				setVariablesPartDefinedAll, ED_ALL );
			if ( ! bAreDefinedAll ){
				cerr<<"Error: The method setVariablesDefined( ED_ALL ) "<<
					"gives not back false for a part of higher defined variables."<<endl;
				iReturn++;
			}
		}
		setVariablesPartDefinedAll.insert( &newVariable );
		bAreDefinedAll = pChoosenFibElement->variablesAreDefined(
			setVariablesPartDefinedAll, ED_ALL );
		if ( bAreDefinedAll ){
			cerr<<"Error: The method setVariablesDefined( ED_ALL ) "<<
				"gives not back true for a part of higher defined variables and a new variable."<<endl;
			iReturn++;
		}



	//check: every used variable below or equal is an defined variable higher
		if ( pChoosenFibElement->getType() != 'r' ){
			for ( set<cFibVariable*>::iterator itrVariable = setVariablesUsedBelowEqual.begin();
					itrVariable != setVariablesUsedBelowEqual.end();
					itrVariable++ ){
				
				list<cFibVariable*>::iterator itrFoundedVariable = find(
					liVariablesDefinedHigher.begin(), liVariablesDefinedHigher.end(),
					*itrVariable );
				if ( itrFoundedVariable == liVariablesDefinedHigherEqual.end() ){
					
					cerr<<"Error: The "<< (*itrVariable)->getValue() <<
						"'th variable, is used equal or below but isn't defined higher."<<endl;
					iReturn++;
				}
			}
		}/*else on root-elements this check dosn't work, but they dosn't
		use variables, so everything is OK*/

		if ( ! liVariablesDefinedAll.empty() ){
			/*check replaceVariable( oldVariable, newVariable ) on random variable
			wher oldVariable and newVariable is defined in all directions of
			the choosen Fib element*/
			//choos random oldVariable
			list<cFibVariable*>::iterator itrChoosenVariable = liVariablesDefinedAll.begin();
			unsigned int uiChoosenVariable = rand() % liVariablesDefinedAll.size();
			while ( uiChoosenVariable != 0){
				itrChoosenVariable++;
				uiChoosenVariable--;
			}
			cFibVariable * oldVariable = (*itrChoosenVariable);
			//choos random newVariable
			itrChoosenVariable = liVariablesDefinedAll.begin();
			uiChoosenVariable = rand() % liVariablesDefinedAll.size();
			while ( uiChoosenVariable != 0){
				itrChoosenVariable++;
				uiChoosenVariable--;
			}
			cFibVariable * newVariable = (*itrChoosenVariable);
			
			const bool bOldVariableWasUsed = pChoosenFibElement->
				isUsedVariable( oldVariable, ED_BELOW_EQUAL );
			const bool bOldVariableWasDefined = pChoosenFibElement->
				isDefinedVariable( oldVariable, ED_BELOW_EQUAL );
			
			const bool bVariableReplaced = pChoosenFibElement->
				replaceVariable( oldVariable, newVariable );
			if ( bVariableReplaced ){
				cout<<"The "<< oldVariable->getValue() <<"'th variable was "<<
					"successfully replaced by the "<< oldVariable->getValue() <<
					"'th variable. "<<endl;
			}else{
				cerr<<"Error: The "<< oldVariable->getValue() <<"'th variable was "<<
					"not replaced by the "<< oldVariable->getValue() <<
					"'th variable. "<<endl;
				iReturn++;
			}
			
			//check with isUsedVariable(ED_BELOW_EQUAL) if the variable was replaced
			//oldVariable isn't used anymore
			//newVariable is used
			const bool bOldVariableIsUsed = pChoosenFibElement->
				isUsedVariable( oldVariable, ED_BELOW_EQUAL );
			if ( oldVariable != newVariable ){
				if ( bOldVariableIsUsed ){
					cerr<<"Error: The "<< oldVariable->getValue() <<"'th variable "<<
						" is still used below or equal. "<<endl;
					iReturn++;
				}
			}else{
				if ( bOldVariableWasUsed == bOldVariableIsUsed){
					cout<<"The variable was replaced with itself. It was and is "<<
						((bOldVariableWasUsed)?" not ":"") <<" used below or equal. "<<endl;
				}else{
					cerr<<"Error: The variable was replaced with itself. It was "<<
						((bOldVariableWasUsed)?" not ":"") <<"  and is "<<
						((bOldVariableIsUsed)?" not ":"") <<" used below or equal. "<<endl;
					iReturn++;
				}
			}

			/*check with isDefinedVariable(ED_BELOW_EQUAL) if the oldVariable is
			still defined for the choosen Fib element, if it was defined befor*/
			const bool bOldVariableIsDefined = pChoosenFibElement->
				isDefinedVariable( oldVariable, ED_BELOW_EQUAL );
			if ( bOldVariableWasDefined ){
				if ( bOldVariableIsDefined ){
					cout<<"The variable was and is defined below or equal the "<<
						"choosen Fib element. "<<endl;
				}else{
					cerr<<"Error: The variable was defined below or equal the "<<
						"choosen Fib element, but isn't anymore defined. "<<endl;
					iReturn++;
				}
			}else{//was not defined befor
				if ( bOldVariableIsDefined ){
					cerr<<"Error: The variable was not defined below or equal the "<<
						"choosen Fib element, but is now defined. "<<endl;
					iReturn++;
				}
			}
		}
	}

	return iReturn;
}



/**
 * This function tests the methods for variables in random generated Fib objects.
 *
 * methods tested:
 * 	- bool isUsedVariable( const cFibVariable *variable , edDirection direction=ED_POSITION ) const;
 * 	- set<cFibVariable*> getUsedVariables( edDirection direction=ED_POSITION );
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- bool isDefinedVariable( const cFibVariable *variable , edDirection direction=ED_POSITION ) const;
 * 	- list<cFibVariable*> getDefinedVariables( edDirection direction=ED_POSITION );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testVariableRandom( unsigned long &ulTestphase, unsigned int uiMaxSize, unsigned int uiIterations ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time(NULL) );
	
	//generate random objects

	cout<<"The maximal size for generated Fib objects is: "<< uiMaxSize <<endl;
	cout<<"The number of iterations per parameterset is: "<< uiIterations <<endl;
	
	const unsigned int uiNumberOfDimensions = 2;
	
	list< cTypeProperty > liPossiblePropertytyps;
	liPossiblePropertytyps.push_back( cTypeProperty( cTypeProperty::COLOR_RGB, uiNumberOfDimensions ) );
	liPossiblePropertytyps.push_back( cTypeProperty( cTypeProperty::SOUND, uiNumberOfDimensions ) );
	const unsigned int uiMaxVectorElementNumber = 1024;
	
	for ( unsigned int uiAverageSubRoots = 1 ; uiAverageSubRoots <= 16; uiAverageSubRoots *= 4 ){// * 3
	for ( unsigned int uiAverageSubRootsDepth = 1; uiAverageSubRootsDepth <= 4 ; uiAverageSubRootsDepth *= 2 ){// * 3
	for ( unsigned int uiNumberOfAverageInputVariables = 3; uiNumberOfAverageInputVariables <= 15;
			uiNumberOfAverageInputVariables = (unsigned int)(uiNumberOfAverageInputVariables * 2 + 1) ){// * 3
	for ( double dFractionsOfUsedVariables = 0.2; dFractionsOfUsedVariables <= 1.0; dFractionsOfUsedVariables += 0.2 ){// * 4
	for ( unsigned int uiSize = pow( uiAverageSubRoots, uiAverageSubRootsDepth ) * 4; uiSize < uiMaxSize; uiSize *= 2 ){
	for ( unsigned int uiIteration = 1; uiIteration <= uiIterations; uiIteration++ ){
		
		const unsigned int uiFractionsOfUsedVariables =
			(unsigned int)(dFractionsOfUsedVariables * 100.0);

		cout<<endl<<"Generate Fib object with size="<< uiSize <<
			" uiIteration="<< uiIteration <<
			" dimensions="<< uiNumberOfDimensions <<
			" uiAverageSubRoots="<< uiAverageSubRoots <<
			" uiAverageSubRootsDepth="<< uiAverageSubRootsDepth <<
			" uiNumberOfAverageInputVariables="<< uiNumberOfAverageInputVariables<<
			" uiFractionsOfUsedVariables="<< uiFractionsOfUsedVariables <<
			" uiMaxVectorElementNumber="<<uiMaxVectorElementNumber<<" . "<<flush;
		
		cFibElement * pGeneratedFibObject = generateFibObject( uiSize,
			liFractionOfFibElements, liPossiblePropertytyps, uiNumberOfDimensions,
			uiAverageSubRoots, uiAverageSubRootsDepth,
			uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
			uiMaxVectorElementNumber );
		
		if ( pGeneratedFibObject ){
			cout<<" generated "<<endl;
		}else{
			cout<<endl;
			cerr<<"Error: Generated Fib object failed:"<<
				" Fib object with size="<< uiSize <<
				" uiIteration="<< uiIteration <<
				" dimensions="<< uiNumberOfDimensions <<
				" uiAverageSubRoots="<< uiAverageSubRoots <<
				" uiAverageSubRootsDepth="<< uiAverageSubRootsDepth <<
				" uiNumberOfAverageInputVariables="<< uiNumberOfAverageInputVariables<<
				" uiFractionsOfUsedVariables="<< uiFractionsOfUsedVariables <<
				" uiMaxVectorElementNumber="<<uiMaxVectorElementNumber<<" . "<<flush;
			iReturn++;
			
			continue;
		}
		
		const unsigned int uiErrorsInTest = testVariableOnObject( pGeneratedFibObject );
		iReturn += uiErrorsInTest;
		
		if ( uiErrorsInTest != 0 ){
			//write Fib object wher orror occured to folder
		char szFileNameBuffer[256];
		sprintf ( szFileNameBuffer, "%s%sS%uD%uSR%uSRD%uIV%uVF%uMV%uR%u%s",
			DIR_OUTPUT, "varError", uiSize,
			uiNumberOfDimensions, uiAverageSubRoots, uiAverageSubRootsDepth,
			uiNumberOfAverageInputVariables, uiFractionsOfUsedVariables,
			uiMaxVectorElementNumber, uiIteration ,".xml" );
			
			cerr<<"Error: The Fib object wher the error occured will be writen to the file \""<< szFileNameBuffer <<"\" ."<<endl;
			
			ofstream * pFile = new ofstream( szFileNameBuffer );
			
			bool bStoreSuccesfull = pGeneratedFibObject->storeXml( *pFile );
			delete pFile;
			
			if ( ! bStoreSuccesfull ){
	
				cerr<<"Error: Storing the data of the generated Fib object to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
				iReturn++;
			}
		}
		cFibElement::deleteObject( pGeneratedFibObject );

	}}}}}}
	
	
	return iReturn;
}






