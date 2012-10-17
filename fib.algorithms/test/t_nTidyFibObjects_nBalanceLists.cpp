/**
 * @file t_nTidyFibObjects_nBalanceLists
 * file name: t_nTidyFibObjects_nBalanceLists.cpp
 * @author Betti Oesterholz
 * @date 25.08.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test tests the simple functions of the class nBalanceLists .
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
 * This test tests the simple functions of the class nBalanceLists .
 *
 * Functions tested in this test:
 * 	- cList * balanceList( cList * pListToBalance, unsigned long ulMaxUnderobjects );
 * 	- cList * balanceListTree( cList * pListToBalance, unsigned long ulMaxUnderobjects );
 * 	- cFibElement * balanceFibTreeLists( cFibElement * pFibObject, unsigned long ulMaxUnderobjects, bool bCombineSubLists = false );
 * 	- cList * eliminateListTree( cList * pList );
 * 	- cFibElement * eliminateListTrees( cFibElement * pFibObject );
 *
 * call: t_nTidyFibObjects_nBalanceLists [MAX_SIZE] [ITERATIONS]
 *
 * parameters:
 * 	MAX_SIZE
 * 		The maximum size, which should not oversteped when the
 * 		random fib -objects are generated.
 * 		The standardvalue is 1024.
 * 	ITERATIONS
 * 		The iterations for the testcases with random generated fib objects.
 * 		Standardvalue is 64.
 */
/*
History:
25.08.2010  Oesterholz  created
02.10.2010  Oesterholz  eliminateListTree() and eliminateListTrees() added
*/


#include "nBalanceLists.h"

#include "cFibElement.h"
#include "cPoint.h"
#include "cList.h"
#include "cVectorPosition.h"
#include "cEvaluePositionList.h"

#include <ctime>

using namespace fib;
using namespace std;
using namespace fib::algorithms;
using namespace fib::algorithms::nTidyFibObjects::nBalanceLists;


extern cFibElement * generateFibObject( unsigned int uiSize,
		unsigned long ulMaximalEvaluedPoints,
		list< pair< char, double > > liFractionOfFibElements,
		const list< cTypeProperty > & liPossiblePropertytyps,
		const unsigned int uiNumberOfDimensions,
		const unsigned int uiAverageSubRoots, const unsigned int uiAverageSubRootsDepth,
		const unsigned int uiNumberOfAverageInputVariables,
		const double dFractionsOfUsedVariables ,
		unsigned int uiMaxVectorElementNumber );


int testBalanceList( unsigned long &ulTestphase );
int testBalanceListTree( unsigned long &ulTestphase );
int testBalanceFibTreeLists( unsigned long &ulTestphase );

int testEliminateListTree( unsigned long &ulTestphase );
int testEliminateListTrees( unsigned long &ulTestphase );


unsigned int uiMaxSize = 256;
unsigned int uiMaxIterations = 64;


int main(int argc,char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	if ( argc >= 2 ){
		//one parameter given; get parameter max size
		uiMaxSize = atol( argv[1] );
		if ( uiMaxSize < 4 ){
			uiMaxSize = 4;
		}
	}
	
	if ( argc >= 3 ){
		//two parameter given; read parameter iterations
		uiMaxIterations = atol( argv[2] );
		if ( uiMaxIterations < 1 ){
			uiMaxIterations = 1;
		}
	}
	
	cout<<endl<<endl<<"Running Test for the function nTidyFibObjects::nBalanceLists::balanceList()"<<endl;
	cout<<            "==========================================================================="<<endl;

	iReturn += testBalanceList( ulTestphase );
	
	cout<<endl<<endl<<"Running Test for the function nTidyFibObjects::nBalanceLists::balanceListTree()"<<endl;
	cout<<            "==============================================================================="<<endl;
	
	iReturn += testBalanceListTree( ulTestphase );

	cout<<endl<<endl<<"Running Test for the function nTidyFibObjects::nBalanceLists::balanceFibTreeLists()"<<endl;
	cout<<            "==================================================================================="<<endl;
	
	iReturn += testBalanceFibTreeLists( ulTestphase );
	
	
	cout<<endl<<endl<<"Running Test for the function nTidyFibObjects::nBalanceLists::eliminateListTree()"<<endl;
	cout<<            "================================================================================="<<endl;
	
	iReturn += testEliminateListTree( ulTestphase );
	
	cout<<endl<<endl<<"Running Test for the function nTidyFibObjects::nBalanceLists::eliminateListTrees()"<<endl;
	cout<<            "================================================================================="<<endl;
	
	iReturn += testEliminateListTrees( ulTestphase );



	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
};


/**
 * This function checks if the given list is balanced in a form the
 * parameters specify with the function @see nBalanceLists::balanceList().
 * Every underobjects in the previos to balance list is a point or a
 * sublist. The underobjects wich are points have a two dimensional
 * positionsvector, wich first element is 1 and second element is the
 * number of the point (counting from 1 to uiMaxPoints).
 * Every underobjects in the previos to balance list which is a list,
 * has two underobjects, wich are bouth points with two dimensional
 * positionsvectors, wich first element is 2 and second element is the
 * number of the (sub-)point (counting from 1 to uiNumberOfSubPoints).
 *
 * @see nBalanceLists::balanceList()
 * @param pListResult the list, which should be balanced
 * @param uiNumberOfPoints the number /count of normal points in the
 * 	balanced list
 * @param uiMaxPoints the maximal number of underobjects per sublist
 * @param uiMaxTreeDepth the maximal depth of the listtree of the balanced
 * 	list; (list wich are sublists of the previos to balance list, arn't counted)
 * @param uiNumberOfSubPoints the number of points in lists, wich are
 * 	sublists of the previos to balance list
 * @return the number of erros occured in the test
 */
int checkBalanceList( cList * pListResult, unsigned long uiNumberOfPoints,
		unsigned long uiMaxPoints, unsigned long uiMaxTreeDepth,
		unsigned long uiNumberOfSubPoints = 0 ){
	
	int iReturn = 0;
	if ( ( (2 < uiMaxPoints) && (uiMaxPoints < pListResult->getNumberOfUnderobjects()) ) ||
			( (uiMaxPoints <= 2) && (3 < pListResult->getNumberOfUnderobjects() ) ) ){
		cerr<<"Error: The returned list has "<<pListResult->getNumberOfUnderobjects()<<
			" underobjects, but should have maximal "<<uiMaxPoints<<" underobjects. " <<endl;
		iReturn++;
	}
	//check number and order of points and the maximal tree depth
	list< cList * > liSubList;
	liSubList.push_back( pListResult );
	list< unsignedIntFib > liUnderobjectSubList;
	liUnderobjectSubList.push_back( 1 );
	
	unsigned int uiActualPoint = 1;
	unsigned int uiActualSubPoint = 1;
	while ( ( ! liSubList.empty() ) &&
			(( uiActualPoint <= uiNumberOfPoints ) ||
			( uiActualSubPoint <= uiNumberOfSubPoints ) ) ){
		
		if ( liUnderobjectSubList.back() <=
				liSubList.back()->getNumberOfUnderobjects() ){
			
			cFibElement * pUnderobject = liSubList.back()->getUnderobject(
				liUnderobjectSubList.back() );
			liUnderobjectSubList.back()++;
			
			if ( pUnderobject == NULL ){
				cerr<<"Error: The returned underobject is NULL. "<<endl;
				cerr<<"   Underobjects: ";
				for ( list< unsignedIntFib >::iterator itrUnderobject =
						liUnderobjectSubList.begin();
						itrUnderobject != liUnderobjectSubList.end(); itrUnderobject++ ){
					
					cerr<<(*itrUnderobject)<<"; ";
				}
				cerr<<endl;
				iReturn++;
				break;
			}else if ( pUnderobject->getType() == 'p' ){
				//the underobject is a pointelement
				cPoint * pPoint = ((cPoint *)pUnderobject);
				if ( pPoint->getPosition()->getValue( 1 ) != 1 ){
					cerr<<"Error: The actual underobject pointelement is wrong, it is not of type 1"<<endl;
					iReturn++;
				}
				if ( pPoint->getPosition()->getValue( 2 ) != uiActualPoint ){
					cerr<<"Error: The actual underobject pointelement is wrong, it is "<<
						pPoint->getPosition()->getValue( 2 )<<" and not "<<
						uiActualPoint<<endl;
					iReturn++;
				}
				uiActualPoint++;
				
			}else if ( pUnderobject->getType() == 'l' ){
				//the underobject is a listelement
				
				cList * pList = (( cList *)pUnderobject);
				cFibElement * pFirstUnderobject = pList->getUnderobject( 1 );
				
				bool bSubList = false;
				if ( pFirstUnderobject->getType() == 'p' ){
					cPoint * pFirstPoint = (cPoint *)pFirstUnderobject;
					if ( pFirstPoint->getPosition()->getValue( 1 ) == 2 ){
						bSubList = true;
					}
				}
				if ( ! bSubList ){
					liSubList.push_back( pList );
					liUnderobjectSubList.push_back( 1 );
					
					if ( uiMaxTreeDepth < liSubList.size() ){
						cerr<<"Error: The listtree depth is to deep, it is "<<
							liSubList.size()<<" and not "<<uiMaxTreeDepth<<endl;
						cerr<<"   Underobjects: ";
						for ( list< unsignedIntFib >::iterator itrUnderobject =
								liUnderobjectSubList.begin();
								itrUnderobject != liUnderobjectSubList.end(); itrUnderobject++ ){
							
							cerr<<(*itrUnderobject)<<"; ";
						}
						cerr<<endl;
						cerr<<"   It has "<<pList->getNumberOfUnderobjects()<<" Underobjects";
						iReturn++;
					}
					if ( ( (2 < uiMaxPoints) && (uiMaxPoints < liSubList.back()->getNumberOfUnderobjects()) ) ||
							( (uiMaxPoints <= 2) && (3 < liSubList.back()->getNumberOfUnderobjects() ) ) ){
						cerr<<"Error: The list has "<<liSubList.back()->getNumberOfUnderobjects()<<
							" underobjects, but should have maximal "<<uiMaxPoints<<" underobjects. " <<endl;
						cerr<<"   Underobjects: ";
						for ( list< unsignedIntFib >::iterator itrUnderobject =
								liUnderobjectSubList.begin();
								itrUnderobject != liUnderobjectSubList.end(); itrUnderobject++ ){
							
							cerr<<(*itrUnderobject)<<"; ";
						}
						cerr<<endl;
						iReturn++;
					}
				}else{//the underobject is a pointelement
					cPoint * pPoint = ((cPoint*)(pFirstUnderobject));
					if ( pPoint->getPosition()->getValue( 1 ) != 2 ){
						cerr<<"Error: The actual underobject pointelement is wrong, it is not of type 2"<<endl;
						iReturn++;
					}
					if ( pPoint->getPosition()->getValue( 2 ) != uiActualSubPoint ){
						cerr<<"Error: The actual underobject pointelement is wrong, it is "<<
							pPoint->getPosition()->getValue( 2 )<<" and not "<<
							uiActualPoint<<endl;
						iReturn++;
					}
					uiActualSubPoint++;
					
					pPoint = ((cPoint*)(pList->getUnderobject( 2 )));
					if ( pPoint->getPosition()->getValue( 1 ) != 2 ){
						cerr<<"Error: The actual underobject pointelement is wrong, it is not of type 2"<<endl;
						iReturn++;
					}
					if ( pPoint->getPosition()->getValue( 2 ) != uiActualSubPoint ){
						cerr<<"Error: The actual underobject pointelement is wrong, it is "<<
							pPoint->getPosition()->getValue( 2 )<<" and not "<<
							uiActualPoint<<endl;
						iReturn++;
					}
					uiActualSubPoint++;
				}

			}else{
				cerr<<"Error: Unknown underobject type "<<
					pUnderobject->getType() <<" . "<<endl;
				iReturn++;
			}
		}else{//switch to the next underlist
			liSubList.pop_back();
			liUnderobjectSubList.pop_back();
		}
	}
	uiActualPoint--;
	uiActualSubPoint--;
	if ( liSubList.empty() ){
		cerr<<"Error: No listelement to search trougth. Last point: "<<uiActualPoint<<endl;
		iReturn++;
	}
	if ( uiActualPoint != uiNumberOfPoints ){
		cerr<<"Error: The number of points is wrong. Last point: "<<
			uiActualPoint<<" but should be "<<uiNumberOfPoints<<endl;
		iReturn++;
	}
	if ( uiActualSubPoint != uiNumberOfSubPoints ){
		cerr<<"Error: The number of points in sub -lists is wrong. Last point: "<<
			uiActualSubPoint<<" but should be "<<uiNumberOfSubPoints<<endl;
		iReturn++;
	}
	return iReturn;
}



/**
 * This method tests the balanceList() function of the nBalanceLists
 * namespace.
 *
 * metods tested:
 * 	- cList * balanceList( cList * pListToBalance, unsigned long ulMaxUnderobjects );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testBalanceList( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<endl<<"TEST : Testing the balanceList() function"<<endl<<endl;
	
	for ( unsigned int uiIteration = 1 ; uiIteration <= 10; uiIteration++ ){
		ulTestphase++;
		
		//create lists with uiNumberOfPoints pionts
		unsigned int uiNumberOfPoints = 2;
		//list should have maximal uiMaxPoints
		unsigned long uiMaxPoints = 2;
		unsigned long uiMaxTreeDepth = 1;
		switch ( uiIteration ){
			case 1:
				uiNumberOfPoints = 9;
				uiMaxPoints = 3;
				uiMaxTreeDepth = 2;
			break;
			case 2:
				uiNumberOfPoints = 7;
				uiMaxPoints = 8;
				uiMaxTreeDepth = 1;
			break;
			case 3:
				uiNumberOfPoints = 5;
				uiMaxPoints = 5;
				uiMaxTreeDepth = 1;
			break;
			case 4:
				uiNumberOfPoints = 27;
				uiMaxPoints = 3;
				uiMaxTreeDepth = 3;
			break;
			case 5:
				uiNumberOfPoints = 16;
				uiMaxPoints = 3;
				uiMaxTreeDepth = 3;
			break;
			case 6:
				uiNumberOfPoints = 52;
				uiMaxPoints = 3;
				uiMaxTreeDepth = 4;
			break;
			case 7:
				uiNumberOfPoints = 10;
				uiMaxPoints = 3;
				uiMaxTreeDepth = 3;
			break;
			case 8:
				uiNumberOfPoints = 8;
				uiMaxPoints = 3;
				uiMaxTreeDepth = 2;
			break;
			case 9:
				uiNumberOfPoints = 16;
				uiMaxPoints = 4;
				uiMaxTreeDepth = 2;
			break;
			case 10:
				uiNumberOfPoints = 7;
				uiMaxPoints = 2;
				uiMaxTreeDepth = 3;
			break;
			//TODO more testcases
		}
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the balanceList( pList, "<<
			uiMaxPoints<<" ) on a list with "<<uiNumberOfPoints<<" subpoints"<<endl;
		
		cList * pList = new cList( NULL, NULL );
		const cList * pListOriginal = pList;
		for ( unsigned int uiActualNumberOfPoints = 1;
				uiActualNumberOfPoints <= uiNumberOfPoints; uiActualNumberOfPoints++ ){
			
			cVectorPosition vecPosition( 2 );
			vecPosition.setValue( 1, 1 );
			vecPosition.setValue( 2, uiActualNumberOfPoints );
			cPoint * pNewPoint = new cPoint( &vecPosition );
			pList->addUnderobject( pNewPoint, pList->getNumberOfUnderobjects() + 1 );
		}
		
		//balance list
		cList * pListResult = balanceList( pList, uiMaxPoints );
		
	//check result
		//check returned pointer
		if ( pListResult == pListOriginal ){
		
			cout<<"The returned list is correctly the original list. "<<endl;
		}else{
			cerr<<"Error: The returned list is not the original list. "<<endl;
			iReturn++;
		}
		iReturn += checkBalanceList( pListResult, uiNumberOfPoints, uiMaxPoints, uiMaxTreeDepth );
		
		pList->deleteObject();
	}
	//test random number of points
	cout<<endl<<endl<<"TEST : Testing the balanceList() with random listelements"<<endl<<endl;
	
	for ( unsigned int uiIteration = 1 ; uiIteration <= uiMaxIterations; uiIteration++ ){
		ulTestphase++;
		
		//create lists with uiNumberOfPoints pionts
		unsigned long uiNumberOfPoints = (rand() % 64) * (rand() % 64) + (rand() % 64) + 2;
		//list should have maximal uiMaxPoints
		unsigned long uiMaxPoints;
		if ( rand() % 10 ){
			uiMaxPoints = rand() % 64 + 2;
		}else{
			uiMaxPoints = (rand() % (uiNumberOfPoints + uiNumberOfPoints / 10 + 2)) + 2;
		}
		unsigned long uiMaxTreeDepth =
			ceil( log( uiNumberOfPoints ) / log( uiMaxPoints ) );
		
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the balanceList( pList, "<<
			uiMaxPoints<<" ) on a list with "<<uiNumberOfPoints<<" subpoints"<<endl;
		
		cList * pList = new cList( NULL, NULL );
		const cList * pListOriginal = pList;
		for ( unsigned int uiActualNumberOfPoints = 1;
				uiActualNumberOfPoints <= uiNumberOfPoints; uiActualNumberOfPoints++ ){
			
			cVectorPosition vecPosition( 2 );
			vecPosition.setValue( 1, 1 );
			vecPosition.setValue( 2, uiActualNumberOfPoints );
			cPoint * pNewPoint = new cPoint( &vecPosition );
			pList->addUnderobject( pNewPoint, pList->getNumberOfUnderobjects() + 1 );
		}
		
		//balance list
		cList * pListResult = balanceList( pList, uiMaxPoints );
		
	//check result
		//check returned pointer
		if ( pListResult == pListOriginal ){
		
			cout<<"The returned list is correctly the original list. "<<endl;
		}else{
			cerr<<"Error: The returned list is not the original list. "<<endl;
			iReturn++;
		}
		if ( uiMaxPoints < pListResult->getNumberOfUnderobjects() ){
			cerr<<"Error: The returned list has "<<pListResult->getNumberOfUnderobjects()<<
				" underobjects, but should have maximal "<<uiMaxPoints<<" underobjects. " <<endl;
			iReturn++;
		}
		iReturn += checkBalanceList( pListResult, uiNumberOfPoints, uiMaxPoints, uiMaxTreeDepth );
		
		pList->deleteObject();
	}
	//test list with random number of points or sublists
	cout<<endl<<endl<<"TEST : Testing the balanceList() with random listelements and sublists"<<endl<<endl;
	
	for ( unsigned int uiIteration = 1 ; uiIteration <= uiMaxIterations; uiIteration++ ){
		ulTestphase++;
		
		//create lists with uiNumberOfPoints pionts
		unsigned long uiNumberOfPoints = (rand() % 64) * (rand() % 64) + (rand() % 64) + 2;
		unsigned long uiNumberOfSubPoints = ((rand() % 32) * (rand() % 32) + (rand() % 32)) * 2;
		//list should have maximal uiMaxPoints
		unsigned long uiMaxPoints;
		if ( rand() % 10 ){
			uiMaxPoints = rand() % 64 + 2;
		}else{
			uiMaxPoints = (rand() % (uiNumberOfPoints + uiNumberOfPoints / 10 + 2)) + 2;
		}
		unsigned long uiMaxTreeDepth =
			ceil( log( uiNumberOfPoints + uiNumberOfSubPoints / 2 ) / log( uiMaxPoints ) );
		
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the balanceList( pList, "<<
			uiMaxPoints<<" ) on a list with "<<uiNumberOfPoints<<" points "<<
			uiNumberOfSubPoints<<" subpoints"<<endl;
		//generate random list
		cList * pList = new cList( NULL, NULL );
		const cList * pListOriginal = pList;
		unsigned int uiActualNumberOfPoints = 1;
		unsigned int uiActualNumberOfSubPoints = 1;
		while ( (uiActualNumberOfPoints <= uiNumberOfPoints) ||
				(uiActualNumberOfSubPoints <= uiNumberOfSubPoints)  ){
			
			if ( (uiActualNumberOfPoints <= uiNumberOfPoints) &&
					( (rand() % 2 == 0) ||
					( uiNumberOfSubPoints < uiActualNumberOfSubPoints) ) ){
				
				cVectorPosition vecPosition( 2 );
				vecPosition.setValue( 1, 1 );
				vecPosition.setValue( 2, uiActualNumberOfPoints );
				cPoint * pNewPoint = new cPoint( &vecPosition );
				pList->addUnderobject( pNewPoint, pList->getNumberOfUnderobjects() + 1 );
				uiActualNumberOfPoints++;
			}else{
				cVectorPosition vecPosition( 2 );
				vecPosition.setValue( 1, 2 );
				vecPosition.setValue( 2, uiActualNumberOfSubPoints );
				cPoint * pNewPoint1 = new cPoint( &vecPosition );
				uiActualNumberOfSubPoints++;
				vecPosition.setValue( 2, uiActualNumberOfSubPoints );
				cPoint * pNewPoint2 = new cPoint( &vecPosition );
				uiActualNumberOfSubPoints++;
				cList * pNewList = new cList( pNewPoint1, pNewPoint2 );
				
				pList->addUnderobject( pNewList, pList->getNumberOfUnderobjects() + 1 );
			}
		}
//		cout<<"Created points: "<<uiActualNumberOfPoints<<" and sublist points: "<<uiActualNumberOfSubPoints<<endl;
		
		//balance list
		cList * pListResult = balanceList( pList, uiMaxPoints);
		
	//check result
		//check returned pointer
		if ( pListResult == pListOriginal ){
		
			cout<<"The returned list is correctly the original list. "<<endl;
		}else{
			cerr<<"Error: The returned list is not the original list. "<<endl;
			iReturn++;
		}
		if ( uiMaxPoints < pListResult->getNumberOfUnderobjects() ){
			cerr<<"Error: The returned list has "<<pListResult->getNumberOfUnderobjects()<<
				" underobjects, but should have maximal "<<uiMaxPoints<<" underobjects. " <<endl;
			iReturn++;
		}
		iReturn += checkBalanceList( pListResult, uiNumberOfPoints, uiMaxPoints, uiMaxTreeDepth, uiNumberOfSubPoints  );
		
		pList->deleteObject();
	}

	return iReturn;
}



/**
 * This function checks if the given list is balanced in a form the
 * parameters specify with the function @see nBalanceLists::balanceListTree().
 * Every underobjects in the previos to balance list is a point or a
 * sublist. The underobjects wich are points have a two dimensional
 * positionsvector, wich first element is 1 and second element is the
 * number of the point (counting from 1 to uiMaxPoints).
 * Every underobjects in the previos to balance list which is a list,
 * has two underobjects, wich are bouth points with two dimensional
 * positionsvectors, wich first element is 2 and second element is the
 * number of the point (counting from 1 to uiMaxPoints).
 *
 * @see nBalanceLists::balanceListTree()
 * @param pListResult the list, which should be balanced
 * @param uiNumberOfPoints the number /count of points in the
 * 	balanced listobject
 * @param uiMaxPoints the maximal number of underobjects per sublist
 * @param uiMaxTreeDepth the maximal depth of the listtree of the balanced
 * 	list
 * @return the number of erros occured in the test
 */
int checkBalanceListTree( cList * pListResult, unsigned long uiNumberOfPoints,
		unsigned long uiMaxPoints, unsigned long uiMaxTreeDepth ){
	
	int iReturn = 0;
	if ( ( (2 < uiMaxPoints) && (uiMaxPoints < pListResult->getNumberOfUnderobjects()) ) ||
			( (uiMaxPoints <= 2) && (3 < pListResult->getNumberOfUnderobjects() ) ) ){
		cerr<<"Error: The returned list has "<<pListResult->getNumberOfUnderobjects()<<
			" underobjects, but should have maximal "<<uiMaxPoints<<" underobjects. " <<endl;
		iReturn++;
	}
	//check number and order of points and the maximal tree depth
	list< cList * > liSubList;
	liSubList.push_back( pListResult );
	list< unsignedIntFib > liUnderobjectSubList;
	liUnderobjectSubList.push_back( 1 );
	
	unsigned int uiActualPoint = 1;
	while ( ( ! liSubList.empty() ) &&
			( uiActualPoint <= uiNumberOfPoints ) ){
		
		if ( liUnderobjectSubList.back() <=
				liSubList.back()->getNumberOfUnderobjects() ){
			
			cFibElement * pUnderobject = liSubList.back()->getUnderobject(
				liUnderobjectSubList.back() );
			liUnderobjectSubList.back()++;
			
			if ( pUnderobject == NULL ){
				cerr<<"Error: The returned underobject is NULL. "<<endl;
				cerr<<"   Underobjects: ";
				for ( list< unsignedIntFib >::iterator itrUnderobject =
						liUnderobjectSubList.begin();
						itrUnderobject != liUnderobjectSubList.end(); itrUnderobject++ ){
					
					cerr<<(*itrUnderobject)<<"; ";
				}
				cerr<<endl;
				iReturn++;
				break;
			}else if ( pUnderobject->getType() == 'p' ){
				//the underobject is a pointelement
				cPoint * pPoint = ((cPoint *)pUnderobject);
				if ( (pPoint->getPosition()->getValue( 1 ) != 1) &&
						(pPoint->getPosition()->getValue( 1 ) != 2) ){
					cerr<<"Error: The actual underobject pointelement is wrong, it is not of type 1"<<endl;
					iReturn++;
				}
				if ( pPoint->getPosition()->getValue( 2 ) != uiActualPoint ){
					cerr<<"Error: The actual underobject pointelement is wrong, it is "<<
						pPoint->getPosition()->getValue( 2 )<<" and not "<<
						uiActualPoint<<endl;
					iReturn++;
				}
				uiActualPoint++;
				
			}else if ( pUnderobject->getType() == 'l' ){
				//the underobject is a listelement
				
				cList * pList = ((cList*)(pUnderobject));
				
				liSubList.push_back( pList );
				liUnderobjectSubList.push_back( 1 );
				
				if ( uiMaxTreeDepth < liSubList.size() ){
					cerr<<"Error: The listtree depth is to deep, it is "<<
						liSubList.size()<<" and not "<<uiMaxTreeDepth<<endl;
					cerr<<"   Underobjects: ";
					for ( list< unsignedIntFib >::iterator itrUnderobject =
							liUnderobjectSubList.begin();
							itrUnderobject != liUnderobjectSubList.end(); itrUnderobject++ ){
						
						cerr<<(*itrUnderobject)<<"; ";
					}
					cerr<<endl;
					iReturn++;
				}
				if ( ( (2 < uiMaxPoints) && (uiMaxPoints < liSubList.back()->getNumberOfUnderobjects()) ) ||
						( (uiMaxPoints <= 2) && (3 < liSubList.back()->getNumberOfUnderobjects() ) ) ){
					cerr<<"Error: The list has "<<liSubList.back()->getNumberOfUnderobjects()<<
						" underobjects, but should have maximal "<<uiMaxPoints<<" underobjects. " <<endl;
					cerr<<"   Underobjects: ";
					for ( list< unsignedIntFib >::iterator itrUnderobject =
							liUnderobjectSubList.begin();
							itrUnderobject != liUnderobjectSubList.end(); itrUnderobject++ ){
						
						cerr<<(*itrUnderobject)<<"; ";
					}
					cerr<<endl;
					iReturn++;
				}

			}else{
				cerr<<"Error: Unknown underobject type "<<
					pUnderobject->getType() <<" . "<<endl;
				iReturn++;
			}
		}else{//switch to the next underlist
			liSubList.pop_back();
			liUnderobjectSubList.pop_back();
		}
	}
	uiActualPoint--;
	if ( liSubList.empty() ){
		cerr<<"Error: No listelement to search trougth. Last point: "<<uiActualPoint<<endl;
		iReturn++;
	}
	if ( uiActualPoint != uiNumberOfPoints ){
		cerr<<"Error: The number of points is wrong. Last point: "<<
			uiActualPoint<<" but should be "<<uiNumberOfPoints<<endl;
		iReturn++;
	}
	return iReturn;
}



/**
 * This method tests the balanceListTree() function of the nBalanceListTrees
 * namespace.
 *
 * metods tested:
 * 	- cList * balanceListTree( cList * pListToBalance, unsigned long ulMaxUnderobjects );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testBalanceListTree( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	

	//test list with random number of points or sublists
	cout<<endl<<endl<<"TEST : Testing the balanceListTree() with random listelements and sublists"<<endl<<endl;
	
	for ( unsigned int uiIteration = 1 ; uiIteration <= uiMaxIterations; uiIteration++ ){
		ulTestphase++;
		
		//create lists with uiNumberOfPoints pionts
		unsigned long uiNumberOfPoints = (rand() % 64) * (rand() % 64) + (rand() % 64) + 2;
		unsigned long uiNumberOfSubPoints = ((rand() % 32) * (rand() % 32) + (rand() % 32)) * 2;
		//list should have maximal uiMaxPoints
		unsigned long uiMaxPoints;
		if ( rand() % 10 ){
			uiMaxPoints = rand() % 64 + 2;
		}else{
			uiMaxPoints = (rand() % (uiNumberOfPoints + uiNumberOfPoints / 10 + 2)) + 2;
		}
		unsigned long uiNumberOfAllPoints = uiNumberOfPoints + uiNumberOfSubPoints;
		unsigned long uiMaxTreeDepth =
			ceil( log( uiNumberOfAllPoints ) / log( uiMaxPoints) );
		
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the balanceListTree( pList, "<<
			uiMaxPoints<<" ) on a list with "<<uiNumberOfPoints<<" points "<<
			uiNumberOfSubPoints<<" subpoints"<<endl;
		//generate random list
		cList * pList = new cList( NULL, NULL );
		const cList * pListOriginal = pList;
		unsigned long uiActualNumberOfPoints = 1;
		unsigned long uiActualNumberOfSubPoints = 1;
		unsigned long uiActualPointNumber = 1;
		while ( (uiActualNumberOfPoints <= uiNumberOfPoints) ||
				(uiActualNumberOfSubPoints <= uiNumberOfSubPoints)  ){
			
			if ( (uiActualNumberOfPoints <= uiNumberOfPoints) &&
					( (rand() % 2 == 0) ||
					( uiNumberOfSubPoints < uiActualNumberOfSubPoints) ) ){
				
				cVectorPosition vecPosition( 2 );
				vecPosition.setValue( 1, 1 );
				vecPosition.setValue( 2, uiActualPointNumber );
				cPoint * pNewPoint = new cPoint( &vecPosition );
				pList->addUnderobject( pNewPoint, pList->getNumberOfUnderobjects() + 1 );
				uiActualNumberOfPoints++;
				uiActualPointNumber++;
			}else{
				cVectorPosition vecPosition( 2 );
				vecPosition.setValue( 1, 2 );
				vecPosition.setValue( 2, uiActualPointNumber );
				cPoint * pNewPoint1 = new cPoint( &vecPosition );
				uiActualPointNumber++;
				vecPosition.setValue( 2, uiActualPointNumber );
				cPoint * pNewPoint2 = new cPoint( &vecPosition );
				cList * pNewList = new cList( pNewPoint1, pNewPoint2 );
				
				pList->addUnderobject( pNewList, pList->getNumberOfUnderobjects() + 1 );
				
				uiActualPointNumber++;
				uiActualNumberOfSubPoints++;
				uiActualNumberOfSubPoints++;
			}
		}
		
		//balance list
		cList * pListResult = balanceListTree( pList, uiMaxPoints );
		
	//check result
		//check returned pointer
		if ( pListResult == pListOriginal ){
		
			cout<<"The returned list is correctly the original list. "<<endl;
		}else{
			cerr<<"Error: The returned list is not the original list. "<<endl;
			iReturn++;
		}
		if ( uiMaxPoints < pListResult->getNumberOfUnderobjects() ){
			cerr<<"Error: The returned list has "<<pListResult->getNumberOfUnderobjects()<<
				" underobjects, but should have maximal "<<uiMaxPoints<<" underobjects. " <<endl;
			iReturn++;
		}
		iReturn += checkBalanceListTree( pListResult, uiNumberOfAllPoints, uiMaxPoints, uiMaxTreeDepth );
		
		pList->deleteObject();
	}

	return iReturn;
}

/**
 * @return a random generated fib -object or NULL, if non could be generated
 * 	BEWARE: You have to delete the generated fib -object
 */
cFibElement * generateFibObject(){
	//parameters for the generator
	list< pair< char, double > > liFractionOfFibElements;
	liFractionOfFibElements.push_back( make_pair( 'p', 2.0 ) );
	liFractionOfFibElements.push_back( make_pair( 'y', 0.05 ) );
	liFractionOfFibElements.push_back( make_pair( 'l', 0.5 ) );
	liFractionOfFibElements.push_back( make_pair( 'a', 0.05 ) );
	liFractionOfFibElements.push_back( make_pair( 'f', 0.05 ) );
	liFractionOfFibElements.push_back( make_pair( 'c', 0.05 ) );
	//TODO: more fib -elements
	
	unsigned int uiAverageSubRoots = (rand() % 4 + 1) * (rand() % 4 + 1) + (rand() % 4);
	unsigned int uiAverageSubRootsDepth = (rand() % 2 + 1) * (rand() % 2 + 1) + (rand() % 2);
	unsigned int uiNumberOfAverageInputVariables = (rand() % 4 + 1) * (rand() % 4 + 1) + (rand() % 4);
//	double dFractionsOfUsedVariables = ((double)(rand() % 16)) / 15.0;
	double dFractionsOfUsedVariables = 0.0;
//	unsigned int uiSize = (rand() % 1024) + 16;
	unsigned int uiSize = (rand() % uiMaxSize) + 4;
	
	const unsigned int uiNumberOfDimensions     = (rand() % 4) + 1;
	const unsigned int uiMaxVectorElementNumber = (rand() % 256 + 2) * (rand() % 256 + 2);
	const unsigned int uiNumberOfPropertyTyps   = (rand() % 6) + 1;

	const cTypeProperty pPossiblePropertytyps[] = {
		cTypeProperty( 1, uiNumberOfDimensions ),
		cTypeProperty( 2, uiNumberOfDimensions ),
		cTypeProperty( 100, uiNumberOfDimensions ),
		cTypeProperty( 200, uiNumberOfDimensions ),
		cTypeProperty( 300, uiNumberOfDimensions ),
		cTypeProperty( 301, uiNumberOfDimensions ),
		cTypeProperty( 305, uiNumberOfDimensions ),
		cTypeProperty( 310, uiNumberOfDimensions ),
		cTypeProperty( 311, uiNumberOfDimensions ),
		cTypeProperty( 312, uiNumberOfDimensions ),
		cTypeProperty( 400, uiNumberOfDimensions ),
		cTypeProperty( 410, uiNumberOfDimensions ),
		cTypeProperty( 600, uiNumberOfDimensions ),
		//no existing typs
		cTypeProperty( 46, uiNumberOfDimensions ),
		cTypeProperty( 0, uiNumberOfDimensions )
	};
	//generate possible propertytyps
	list< cTypeProperty > liPossiblePropertytyps( pPossiblePropertytyps,
		pPossiblePropertytyps + sizeof( pPossiblePropertytyps ) / sizeof( cTypeProperty ) );
	while ( uiNumberOfPropertyTyps < liPossiblePropertytyps.size() ){
		//choos random propertytyp and erase it
		unsigned int uiRandom = rand() % liPossiblePropertytyps.size();
		list< cTypeProperty >::iterator itrChoosenProperty = liPossiblePropertytyps.begin();
		while ( uiRandom != 0 ){
			uiRandom--;
			itrChoosenProperty++;
		}
		liPossiblePropertytyps.erase( itrChoosenProperty );
	}

	cRoot * pOriginalFibObject = (cRoot*)generateFibObject(
		uiSize, uiSize * (log( uiSize ) + 10),
		liFractionOfFibElements, liPossiblePropertytyps, uiNumberOfDimensions,
		uiAverageSubRoots, uiAverageSubRootsDepth,
		uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
		uiMaxVectorElementNumber );
	
	return pOriginalFibObject;
}


/**
 * This method tests the balanceFibTreeLists() function of the nBalanceLists
 * namespace.
 *
 * metods tested:
 * 	- cFibElement * balanceFibTreeLists( cFibElement * pFibObject,
 * 	unsigned long ulMaxUnderobjects, bool bCombineSubLists = false );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testBalanceFibTreeLists( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<endl<<"TEST : Testing the balanceFibTreeLists() function"<<endl<<endl;
	
	for ( unsigned int uiIteration = 1 ; uiIteration <= 10; uiIteration++ ){
		ulTestphase++;
		
		//create lists with uiNumberOfPoints pionts
		unsigned int uiNumberOfPoints = 2;
		//list should have maximal uiMaxPoints
		unsigned long uiMaxPoints = 2;
		unsigned long uiMaxTreeDepth = 1;
		switch ( uiIteration ){
			case 1:
				uiNumberOfPoints = 9;
				uiMaxPoints = 3;
				uiMaxTreeDepth = 2;
			break;
			case 2:
				uiNumberOfPoints = 7;
				uiMaxPoints = 8;
				uiMaxTreeDepth = 1;
			break;
			case 3:
				uiNumberOfPoints = 5;
				uiMaxPoints = 5;
				uiMaxTreeDepth = 1;
			break;
			case 4:
				uiNumberOfPoints = 27;
				uiMaxPoints = 3;
				uiMaxTreeDepth = 3;
			break;
			case 5:
				uiNumberOfPoints = 16;
				uiMaxPoints = 3;
				uiMaxTreeDepth = 3;
			break;
			case 6:
				uiNumberOfPoints = 52;
				uiMaxPoints = 3;
				uiMaxTreeDepth = 4;
			break;
			case 7:
				uiNumberOfPoints = 10;
				uiMaxPoints = 3;
				uiMaxTreeDepth = 3;
			break;
			case 8:
				uiNumberOfPoints = 8;
				uiMaxPoints = 3;
				uiMaxTreeDepth = 2;
			break;
			case 9:
				uiNumberOfPoints = 16;
				uiMaxPoints = 4;
				uiMaxTreeDepth = 2;
			break;
			case 10:
				uiNumberOfPoints = 7;
				uiMaxPoints = 2;
				uiMaxTreeDepth = 3;
			break;
			//TODO more testcases
		}
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the balanceFibTreeLists( pList, "<<
			uiMaxPoints<<", false ) on a list with "<<uiNumberOfPoints<<" subpoints"<<endl;
		
		cList * pList = new cList( NULL, NULL );
		const cList * pListOriginal = pList;
		for ( unsigned int uiActualNumberOfPoints = 1;
				uiActualNumberOfPoints <= uiNumberOfPoints; uiActualNumberOfPoints++ ){
			
			cVectorPosition vecPosition( 2 );
			vecPosition.setValue( 1, 1 );
			vecPosition.setValue( 2, uiActualNumberOfPoints );
			cPoint * pNewPoint = new cPoint( &vecPosition );
			pList->addUnderobject( pNewPoint, pList->getNumberOfUnderobjects() + 1 );
		}
		
		//balance list
		cFibElement * pListResult = balanceFibTreeLists( pList, uiMaxPoints, false );
		
	//check result
		if ( pListResult->getType() != 'l' ){
			cerr<<"Error: The returned fib -object is not an listelement list. "<<endl;
			pList->deleteObject();
			iReturn++;
			continue;
		}
		//check returned pointer
		if ( pListResult == pListOriginal ){
		
			cout<<"The returned list is correctly the original list. "<<endl;
		}else{
			cerr<<"Error: The returned list is not the original list. "<<endl;
			iReturn++;
		}
		iReturn += checkBalanceList( (cList*)pListResult, uiNumberOfPoints, uiMaxPoints, uiMaxTreeDepth );
		
		pList->deleteObject();
	}
	//test random number of points
	cout<<endl<<endl<<"TEST : Testing the balanceFibTreeLists() with random listelements"<<endl<<endl;
	
	for ( unsigned int uiIteration = 1 ; uiIteration <= uiMaxIterations / 2 + 1; uiIteration++ ){
		ulTestphase++;
		
		//create lists with uiNumberOfPoints pionts
		unsigned long uiNumberOfPoints = (rand() % 64) * (rand() % 64) + (rand() % 64) + 2;
		//list should have maximal uiMaxPoints
		unsigned long uiMaxPoints;
		if ( rand() % 10 ){
			uiMaxPoints = rand() % 64 + 2;
		}else{
			uiMaxPoints = (rand() % (uiNumberOfPoints + uiNumberOfPoints / 10 + 2)) + 2;
		}
		unsigned long uiMaxTreeDepth =
			ceil( log( uiNumberOfPoints ) / log( uiMaxPoints ) );
		
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the balanceFibTreeLists( pList, "<<
			uiMaxPoints<<", false ) on a list with "<<uiNumberOfPoints<<" subpoints"<<endl;
		
		cList * pList = new cList( NULL, NULL );
		const cList * pListOriginal = pList;
		for ( unsigned int uiActualNumberOfPoints = 1;
				uiActualNumberOfPoints <= uiNumberOfPoints; uiActualNumberOfPoints++ ){
			
			cVectorPosition vecPosition( 2 );
			vecPosition.setValue( 1, 1 );
			vecPosition.setValue( 2, uiActualNumberOfPoints );
			cPoint * pNewPoint = new cPoint( &vecPosition );
			pList->addUnderobject( pNewPoint, pList->getNumberOfUnderobjects() + 1 );
		}
		
		//balance list
		cFibElement * pListResult = balanceFibTreeLists( pList, uiMaxPoints, false );
		
	//check result
		if ( pListResult->getType() != 'l' ){
			cerr<<"Error: The returned fib -object is not an listelement list. "<<endl;
			pList->deleteObject();
			iReturn++;
			continue;
		}
		//check returned pointer
		if ( pListResult == pListOriginal ){
		
			cout<<"The returned list is correctly the original list. "<<endl;
		}else{
			cerr<<"Error: The returned list is not the original list. "<<endl;
			iReturn++;
		}
		if ( uiMaxPoints < ((cList *)pListResult)->getNumberOfUnderobjects() ){
			cerr<<"Error: The returned list has "<<((cList *)pListResult)->getNumberOfUnderobjects()<<
				" underobjects, but should have maximal "<<uiMaxPoints<<" underobjects. " <<endl;
			iReturn++;
		}
		iReturn += checkBalanceList( (cList *)pListResult, uiNumberOfPoints, uiMaxPoints, uiMaxTreeDepth );
		
		pList->deleteObject();
	}
	//test list with random number of points or sublists
	cout<<endl<<endl<<"TEST : Testing the balanceFibTreeLists() with random listelements and sublists"<<endl<<endl;
	
	for ( unsigned int uiIteration = 1 ; uiIteration <= uiMaxIterations / 2 + 1; uiIteration++ ){
		ulTestphase++;
		
		//create lists with uiNumberOfPoints pionts
		unsigned long uiNumberOfPoints = (rand() % 64) * (rand() % 64) + (rand() % 64) + 2;
		unsigned long uiNumberOfSubPoints = ((rand() % 32) * (rand() % 32) + (rand() % 32)) * 2;
		//list should have maximal uiMaxPoints
		unsigned long uiMaxPoints;
		if ( rand() % 10 ){
			uiMaxPoints = rand() % 64 + 2;
		}else{
			uiMaxPoints = (rand() % (uiNumberOfPoints + uiNumberOfPoints / 10 + 2)) + 2;
		}
		unsigned long uiMaxTreeDepth =
			ceil( log( uiNumberOfPoints + uiNumberOfSubPoints / 2 ) / log( uiMaxPoints ) );
		
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the balanceFibTreeLists( pList, "<<
			uiMaxPoints<<", false ) on a list with "<<uiNumberOfPoints<<" points "<<
			uiNumberOfSubPoints<<" subpoints"<<endl;
		//generate random list
		cList * pList = new cList( NULL, NULL );
		const cList * pListOriginal = pList;
		unsigned int uiActualNumberOfPoints = 1;
		unsigned int uiActualNumberOfSubPoints = 1;
		while ( (uiActualNumberOfPoints <= uiNumberOfPoints) ||
				(uiActualNumberOfSubPoints <= uiNumberOfSubPoints)  ){
			
			if ( (uiActualNumberOfPoints <= uiNumberOfPoints) &&
					( (rand() % 2 == 0) ||
					( uiNumberOfSubPoints < uiActualNumberOfSubPoints) ) ){
				
				cVectorPosition vecPosition( 2 );
				vecPosition.setValue( 1, 1 );
				vecPosition.setValue( 2, uiActualNumberOfPoints );
				cPoint * pNewPoint = new cPoint( &vecPosition );
				pList->addUnderobject( pNewPoint, pList->getNumberOfUnderobjects() + 1 );
				uiActualNumberOfPoints++;
			}else{
				cVectorPosition vecPosition( 2 );
				vecPosition.setValue( 1, 2 );
				vecPosition.setValue( 2, uiActualNumberOfSubPoints );
				cPoint * pNewPoint1 = new cPoint( &vecPosition );
				uiActualNumberOfSubPoints++;
				vecPosition.setValue( 2, uiActualNumberOfSubPoints );
				cPoint * pNewPoint2 = new cPoint( &vecPosition );
				uiActualNumberOfSubPoints++;
				cList * pNewList = new cList( pNewPoint1, pNewPoint2 );
				
				pList->addUnderobject( pNewList, pList->getNumberOfUnderobjects() + 1 );
			}
		}
		
		//balance list
		cFibElement * pListResult = balanceFibTreeLists( pList, uiMaxPoints, false );
		
	//check result
		if ( pListResult->getType() != 'l' ){
			cerr<<"Error: The returned fib -object is not an listelement list. "<<endl;
			pList->deleteObject();
			iReturn++;
			continue;
		}
		//check returned pointer
		if ( pListResult == pListOriginal ){
		
			cout<<"The returned list is correctly the original list. "<<endl;
		}else{
			cerr<<"Error: The returned list is not the original list. "<<endl;
			iReturn++;
		}
		if ( uiMaxPoints < ((cList *)pListResult)->getNumberOfUnderobjects() ){
			cerr<<"Error: The returned list has "<<((cList *)pListResult)->getNumberOfUnderobjects()<<
				" underobjects, but should have maximal "<<uiMaxPoints<<" underobjects. " <<endl;
			iReturn++;
		}
		iReturn += checkBalanceList( (cList *)pListResult, uiNumberOfPoints, uiMaxPoints, uiMaxTreeDepth, uiNumberOfSubPoints  );
		
		pList->deleteObject();
	}
	
		//test list with random number of points or sublists
	cout<<endl<<endl<<"TEST : Testing the balanceFibTreeLists() with random listelements and sublists"<<endl<<endl;
	
	for ( unsigned int uiIteration = 1 ; uiIteration <= uiMaxIterations; uiIteration++ ){
		ulTestphase++;
		
		//create lists with uiNumberOfPoints pionts
		unsigned long uiNumberOfPoints = (rand() % 64) * (rand() % 64) + (rand() % 64) + 2;
		unsigned long uiNumberOfSubPoints = ((rand() % 32) * (rand() % 32) + (rand() % 32)) * 2;
		//list should have maximal uiMaxPoints
		unsigned long uiMaxPoints;
		if ( rand() % 10 ){
			uiMaxPoints = rand() % 64 + 2;
		}else{
			uiMaxPoints = (rand() % (uiNumberOfPoints + uiNumberOfPoints / 10 + 2)) + 2;
		}
		unsigned long uiNumberOfAllPoints = uiNumberOfPoints + uiNumberOfSubPoints;
		unsigned long uiMaxTreeDepth =
			ceil( log( uiNumberOfAllPoints ) / log( uiMaxPoints) );
		
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the balanceFibTreeLists( pList, "<<
			uiMaxPoints<<", true ) on a list with "<<uiNumberOfPoints<<" points "<<
			uiNumberOfSubPoints<<" subpoints"<<endl;
		//generate random list
		cList * pList = new cList( NULL, NULL );
		const cList * pListOriginal = pList;
		unsigned long uiActualNumberOfPoints = 1;
		unsigned long uiActualNumberOfSubPoints = 1;
		unsigned long uiActualPointNumber = 1;
		while ( (uiActualNumberOfPoints <= uiNumberOfPoints) ||
				(uiActualNumberOfSubPoints <= uiNumberOfSubPoints)  ){
			
			if ( (uiActualNumberOfPoints <= uiNumberOfPoints) &&
					( (rand() % 2 == 0) ||
					( uiNumberOfSubPoints < uiActualNumberOfSubPoints) ) ){
				
				cVectorPosition vecPosition( 2 );
				vecPosition.setValue( 1, 1 );
				vecPosition.setValue( 2, uiActualPointNumber );
				cPoint * pNewPoint = new cPoint( &vecPosition );
				pList->addUnderobject( pNewPoint, pList->getNumberOfUnderobjects() + 1 );
				uiActualNumberOfPoints++;
				uiActualPointNumber++;
			}else{
				cVectorPosition vecPosition( 2 );
				vecPosition.setValue( 1, 2 );
				vecPosition.setValue( 2, uiActualPointNumber );
				cPoint * pNewPoint1 = new cPoint( &vecPosition );
				uiActualPointNumber++;
				vecPosition.setValue( 2, uiActualPointNumber );
				cPoint * pNewPoint2 = new cPoint( &vecPosition );
				cList * pNewList = new cList( pNewPoint1, pNewPoint2 );
				
				pList->addUnderobject( pNewList, pList->getNumberOfUnderobjects() + 1 );
				
				uiActualPointNumber++;
				uiActualNumberOfSubPoints++;
				uiActualNumberOfSubPoints++;
			}
		}
		
		//balance list
		cFibElement * pListResult = balanceFibTreeLists( pList, uiMaxPoints, true );
		
	//check result
		if ( pListResult->getType() != 'l' ){
			cerr<<"Error: The returned fib -object is not an listelement list. "<<endl;
			pList->deleteObject();
			iReturn++;
			continue;
		}
		//check returned pointer
		if ( pListResult == pListOriginal ){
		
			cout<<"The returned list is correctly the original list. "<<endl;
		}else{
			cerr<<"Error: The returned list is not the original list. "<<endl;
			iReturn++;
		}
		if ( uiMaxPoints < ((cList *)pListResult)->getNumberOfUnderobjects() ){
			cerr<<"Error: The returned list has "<<((cList *)pListResult)->getNumberOfUnderobjects()<<
				" underobjects, but should have maximal "<<uiMaxPoints<<" underobjects. " <<endl;
			iReturn++;
		}
		iReturn += checkBalanceListTree( (cList *)pListResult, uiNumberOfAllPoints, uiMaxPoints, uiMaxTreeDepth );
		
		pList->deleteObject();
	}
	
	//test on random generated fib -objects
	for ( unsigned int uiIteration = 1 ; uiIteration <= uiMaxIterations; uiIteration++ ){
		
		unsigned long uiMaxPoints = rand() % 64 + 2;
		
		ulTestphase++;
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the balanceFibTreeLists( pOriginalFibObject, "<<
			uiMaxPoints<<", true ) on an random generated fib -object. "<<endl<<flush;
		
		cRoot * pOriginalFibObject = (cRoot*)generateFibObject();
		
		if ( pOriginalFibObject == NULL ){
			cerr<<"Error: Couldn't generate an original fib object."<<endl;
			iReturn++;
			continue;
		}
		cEvaluePositionList evaluedOriginal;
		pOriginalFibObject->evalueObjectSimple( evaluedOriginal );
		
		//balance list
		cFibElement * pFibObjectBalanced = balanceFibTreeLists( pOriginalFibObject, uiMaxPoints, true );
		
	//check result
		//check returned pointer
		if ( pFibObjectBalanced == pOriginalFibObject ){
		
			cout<<"The returned fib -object is correctly the original fib -object. "<<endl;
		}else{
			cerr<<"Error: The returned fib -object is not the original fib -object. "<<endl;
			iReturn++;
		}
		//compare evalued points of original and balanced fib -object
		cEvaluePositionList evaluedBalanced;
		pFibObjectBalanced->evalueObjectSimple( evaluedBalanced );
		
		if ( evaluedBalanced.liEvaluedPositionData == evaluedOriginal.liEvaluedPositionData ){
		
			cout<<"The balanced fib -object evalues to the same as the original fib -object. "<<endl;
		}else{
			cerr<<"Error: The balanced fib -object dosn't evalues to the same as the original fib -object. "<<endl;
			iReturn++;
		}
		
		//check if every list an the balanced fib objects has less than uiMaxPoints
		for ( cList * pActualList = ((cList*)(pFibObjectBalanced->getFibElement( 'l', 1 ) ) ) ;
				pActualList != NULL;
				pActualList = ((cList*)(pActualList->getNextFibElement( 'l' ) ) ) ){
			
			if ( ( (2 < uiMaxPoints) && (uiMaxPoints < pActualList->getNumberOfUnderobjects()) ) ||
					( (uiMaxPoints <= 2) && (3 < pActualList->getNumberOfUnderobjects() ) ) ){
				cerr<<"Error: The list has "<<pActualList->getNumberOfUnderobjects()<<
					" underobjects, but should have maximal "<<uiMaxPoints<<" underobjects. " <<endl;
				iReturn++;
			}
		}
		pOriginalFibObject->deleteObject();
	}
	for ( unsigned int uiIteration = 1 ; uiIteration <= uiMaxIterations; uiIteration++ ){
		
		unsigned long uiMaxPoints = rand() % 64 + 2;
		
		ulTestphase++;
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the balanceFibTreeLists( pOriginalFibObject, "<<
			uiMaxPoints<<", false ) on an random generated fib -object. "<<endl<<flush;
		
		cRoot * pOriginalFibObject = (cRoot*)generateFibObject();
		
		if ( pOriginalFibObject == NULL ){
			cerr<<"Error: Couldn't generate an original fib object."<<endl;
			iReturn++;
			continue;
		}
		cEvaluePositionList evaluedOriginal;
		pOriginalFibObject->evalueObjectSimple( evaluedOriginal );
		
		//balance list
		cFibElement * pFibObjectBalanced = balanceFibTreeLists( pOriginalFibObject, uiMaxPoints, false );
		
	//check result
		//check returned pointer
		if ( pFibObjectBalanced == pOriginalFibObject ){
		
			cout<<"The returned fib -object is correctly the original fib -object. "<<endl;
		}else{
			cerr<<"Error: The returned fib -object is not the original fib -object. "<<endl;
			iReturn++;
		}
		//compare evalued points of original and balanced fib -object
		cEvaluePositionList evaluedBalanced;
		pFibObjectBalanced->evalueObjectSimple( evaluedBalanced );
		
		if ( evaluedBalanced.liEvaluedPositionData == evaluedOriginal.liEvaluedPositionData ){
		
			cout<<"The balanced fib -object evalues to the same as the original fib -object. "<<endl;
		}else{
			cerr<<"Error: The balanced fib -object dosn't evalues to the same as the original fib -object. "<<endl;
			iReturn++;
		}
		
		//check if every list an the balanced fib objects has less than uiMaxPoints
		for ( cList * pActualList = ((cList*)(pFibObjectBalanced->getFibElement( 'l', 1 ) ) ) ;
				pActualList != NULL;
				pActualList = ((cList*)(pActualList->getNextFibElement( 'l' ) ) ) ){
			
			if ( ( (2 < uiMaxPoints) && (uiMaxPoints < pActualList->getNumberOfUnderobjects()) ) ||
					( (uiMaxPoints <= 2) && (3 < pActualList->getNumberOfUnderobjects() ) ) ){
				cerr<<"Error: The list has "<<pActualList->getNumberOfUnderobjects()<<
					" underobjects, but should have maximal "<<uiMaxPoints<<" underobjects. " <<endl;
				iReturn++;
			}
		}
		pOriginalFibObject->deleteObject();
	}

	return iReturn;
}



/**
 * This method tests the eliminateListTrees() function of the nBalanceLists
 * namespace.
 *
 * metods tested:
 * 	- cList * eliminateListTree( cList * pList );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testEliminateListTree( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<endl<<"TEST : Testing the eliminateListTree() function "<<endl<<endl;

	//test on random generated fib -objects
	for ( unsigned int uiIteration = 1 ; uiIteration <= uiMaxIterations; uiIteration++ ){
		
		ulTestphase++;
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the eliminateListTree( pOriginalFibObject "<<
			") on an random generated fib -object. "<<endl<<flush;
		
		cRoot * pOriginalFibObject = (cRoot*)generateFibObject();
		
		if ( pOriginalFibObject == NULL ){
			cerr<<"Error: Couldn't generate an original fib object."<<endl;
			iReturn++;
			continue;
		}
		cEvaluePositionList evaluedOriginal;
		pOriginalFibObject->evalueObjectSimple( evaluedOriginal );
		
		const unsignedIntFib uiNumberOfListelements =
			pOriginalFibObject->getNumberOfElements( 'l' );
		if ( uiNumberOfListelements == 0 ){
			cout<<"No listelements in the generated fib -object. Skipping it. "<<endl;
			pOriginalFibObject->deleteObject();
			continue;
		}
		const unsignedIntFib uiChoosenList = rand() % uiNumberOfListelements + 1;
		cList * pOriginalList = (cList*)(
			pOriginalFibObject->getFibElement( 'l', uiChoosenList ));
		if ( pOriginalList == NULL ){
			cerr<<"Error: Couldn't choose the "<<uiChoosenList<<" list of the generated fib -object."<<endl;
			iReturn++;
			pOriginalFibObject->deleteObject();
			continue;
		}
		cout<<"The "<<uiChoosenList<<"'th listelements in the generated fib -object was choosen. "<<endl;
		//eleminate listtree
		cList * pGeneratedList = eliminateListTree( pOriginalList );
		
	//check result
		//check returned pointer
		if ( pGeneratedList == pOriginalList ){
		
			cout<<"The returned fib -object is correctly the original fib -object. "<<endl;
		}else{
			cerr<<"Error: The returned fib -object is not the original fib -object. "<<endl;
			iReturn++;
		}
		//compare evalued points of original and balanced fib -object
		cEvaluePositionList evaluedBalanced;
		pOriginalFibObject->evalueObjectSimple( evaluedBalanced );
		
		if ( evaluedBalanced.liEvaluedPositionData == evaluedOriginal.liEvaluedPositionData ){
		
			cout<<"The generated fib -object evalues to the same as the original fib -object. "<<endl;
		}else{
			cerr<<"Error: The generated fib -object dosn't evalues to the same as the original fib -object. "<<endl;
			iReturn++;
		}
		
		//check if the generated list has no listelements as underobjects
		const list< cFibElement * > liActualUnderobjects =
			pGeneratedList->getUnderobjects();
		
		for ( list< cFibElement * >::const_iterator
				itrUnderobject = liActualUnderobjects.begin();
				itrUnderobject != liActualUnderobjects.end();
				itrUnderobject++ ){
			
			if ( (*itrUnderobject)->getType() == 'l' ){
				cerr<<"Error: The generated list (Number="<<pGeneratedList->getNumberOfElement()<<
					") has an listelement as an underobject. "<<endl;
				iReturn++;
			}
		}

		pOriginalFibObject->deleteObject();
	}

	return iReturn;
}


/**
 * This method tests the eliminateListTrees() function of the nBalanceLists
 * namespace.
 *
 * metods tested:
 * 	- cFibElement * eliminateListTrees( cFibElement * pFibObject );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testEliminateListTrees( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<endl<<"TEST : Testing the eliminateListTrees() function "<<endl<<endl;

	//test on random generated fib -objects
	for ( unsigned int uiIteration = 1 ; uiIteration <= uiMaxIterations; uiIteration++ ){
		
		ulTestphase++;
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the eliminateListTrees( pOriginalFibObject "<<
			") on an random generated fib -object. "<<endl<<flush;
		
		cRoot * pOriginalFibObject = (cRoot*)generateFibObject();
		
		if ( pOriginalFibObject == NULL ){
			cerr<<"Error: Couldn't generate an original fib object."<<endl;
			iReturn++;
			continue;
		}
		cEvaluePositionList evaluedOriginal;
		pOriginalFibObject->evalueObjectSimple( evaluedOriginal );
		
		//eleminate listtrees
		cFibElement * pFibObjectCreated = eliminateListTrees( pOriginalFibObject );
		
	//check result
		//check returned pointer
		if ( pFibObjectCreated == pOriginalFibObject ){
		
			cout<<"The returned fib -object is correctly the original fib -object. "<<endl;
		}else{
			cerr<<"Error: The returned fib -object is not the original fib -object. "<<endl;
			iReturn++;
		}
		//compare evalued points of original and balanced fib -object
		cEvaluePositionList evaluedBalanced;
		pFibObjectCreated->evalueObjectSimple( evaluedBalanced );
		
		if ( evaluedBalanced.liEvaluedPositionData == evaluedOriginal.liEvaluedPositionData ){
		
			cout<<"The generated fib -object evalues to the same as the original fib -object. "<<endl;
		}else{
			cerr<<"Error: The generated fib -object dosn't evalues to the same as the original fib -object. "<<endl;
			iReturn++;
		}
		
		//check if every list in the changed fib -objects has no listelements as underobjects
		for ( cList * pActualList = ((cList*)(pFibObjectCreated->getFibElement( 'l', 1 ) ) ) ;
				pActualList != NULL;
				pActualList = ((cList*)(pActualList->getNextFibElement( 'l' ) ) ) ){
			
			const list< cFibElement * > liActualUnderobjects =
				pActualList->getUnderobjects();
			
			for ( list< cFibElement * >::const_iterator
					itrUnderobject = liActualUnderobjects.begin();
					itrUnderobject != liActualUnderobjects.end();
					itrUnderobject++ ){
				
				if ( (*itrUnderobject)->getType() == 'l' ){
					cerr<<"Error: The actual list (Number="<<pActualList->getNumberOfElement()<<
						") has an listelement as an underobject. "<<endl;
					iReturn++;
				}
			}
			
		}
		pOriginalFibObject->deleteObject();
	}

	return iReturn;
}






