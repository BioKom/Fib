/**
 * @file nBalanceLists
 * file name: nBalanceLists.cpp
 * @author Betti Oesterholz
 * @date 23.08.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file implements functions for balancing fib -objects lists.
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
 * This file implements functions for balancing fib -objects lists.
 */
/*
History:
23.08.2010  Oesterholz  created
02.10.2010  Oesterholz  eliminateListTree() and eliminateListTrees() added
*/

//TODO weg
//#define DEBUG

#ifndef ___N_BALANCE_LISTS_CPP__
#define ___N_BALANCE_LISTS_CPP__

#include "nBalanceLists.h"

#include <cmath>
#include <algorithm>

using namespace fib::algorithms::nTidyFibObjects::nBalanceLists;
using namespace fib;


namespace fib{
namespace algorithms{
namespace nTidyFibObjects{
namespace nBalanceLists{
	//protected functions
	
	/**
	 * This function will balance the underobjects in the given list.
	 * It will portion the given underobjects into fib -listelements, so
	 * that every created listelements and the returned list contains maximal
	 *	ulMaxUnderobjects underobjects. The underobjects of the given
	 * list will be in the last layer of the created listtree.
	 * The created listelements will be nested, so that each contain
	 * maximal ulMaxUnderobjects underobjects.
	 * The maximal depth of the created list trees will be equal.
	 *
	 * This function is a helpfunction for:
	 * 	- @see balanceList()
	 * 	- @see balanceListTree()
	 *
	 * @param liInOutUnderobjects a reference to the the input and output
	 * 	list with the underobjects
	 * @param ulMaxUnderobjects the maximum number of underobjects the
	 * 	balanced lists should have
	 * @return true if the list was changed, else false
	 */
	bool createListUnderobjectTree(
			list<cFibElement*> & liInOutUnderobjects,
			unsigned long ulMaxUnderobjects ){
	
		DEBUG_OUT_L2(<<"createListUnderobjectTree( liInOutUnderobjects, ulMaxUnderobjects="<<ulMaxUnderobjects<<" ) started "<<endl<<flush);
		//count the underobjects of the list
		const unsignedIntFib uiNumberOfUnderobjects = liInOutUnderobjects.size();
		
		if (ulMaxUnderobjects < 2){
			ulMaxUnderobjects = 2;
		}
		//evalue the list tree depth
		if ( (uiNumberOfUnderobjects <= ulMaxUnderobjects) ||
				( (ulMaxUnderobjects == 2) && (uiNumberOfUnderobjects == 3)) ){
			//list balanced -> nothing to do
			DEBUG_OUT_L2(<<"createListUnderobjectTree( liInOutUnderobjects, ulMaxUnderobjects="<<ulMaxUnderobjects<<" ) done list allready balanced "<<endl<<flush);
			return false;
		}
		const unsigned int uiTreeDepth =
			ceil( log( uiNumberOfUnderobjects ) / log( ulMaxUnderobjects ) );
		
		//evalue the number of listunderobjects in the last layer of the listtree
		unsigned int uiLastLayerUnderobjects = max( 2U, ((unsigned int)(ceil(
			((double)uiNumberOfUnderobjects) / pow( ulMaxUnderobjects, uiTreeDepth - 1 ) ) ) ) );
		if ( uiLastLayerUnderobjects < 2 ){
			DEBUG_OUT_L2(<<"minimum last layer number of underobjects is 2 "<<endl<<flush);
			uiLastLayerUnderobjects = 2;
		}
		
		DEBUG_OUT_L2(<<"uiNumberOfUnderobjects="<<uiNumberOfUnderobjects<<"  uiTreeDepth="<<uiTreeDepth<<"  uiLastLayerUnderobjects="<<uiLastLayerUnderobjects<<endl<<flush);
		//get all underobjects of the list to balance
		list<cFibElement*> liInOutUnderobjectsNext;
		DEBUG_OUT_L2(<<"creating the last layer "<<endl<<flush);
		DEBUG_OUT_L2(<<"#liInOutUnderobjects= "<<liInOutUnderobjects.size()<<" #liInOutUnderobjectsNext= "<<liInOutUnderobjectsNext.size()<<endl<<flush);
		while ( ! liInOutUnderobjects.empty() ){
			
			if ( liInOutUnderobjects.size() == 1  ){
					DEBUG_OUT_L2(<<liInOutUnderobjects.size()<<"(==1) last layer underobjects remaining "<<endl<<flush);
					liInOutUnderobjectsNext.push_back( liInOutUnderobjects.back() );
					liInOutUnderobjects.pop_back();
					break;
			}else if ( liInOutUnderobjects.size() == uiLastLayerUnderobjects + 1 ){
				//last (?) listobject in last layer
				if ( liInOutUnderobjects.size() <= 3 ){
					//include all remaining underobjects
					DEBUG_OUT_L2(<<liInOutUnderobjects.size()<<"(<=3) last layer underobjects remaining "<<endl<<flush);
					if ( (ulMaxUnderobjects == 2) && (liInOutUnderobjects.size() == 3) ){
						uiLastLayerUnderobjects = 2;
					}else{
						uiLastLayerUnderobjects = 3;
					}
				}else{/*more than 3 remaining underobjects ->
					leav 2 underobjects to remain and put them in a seperate list*/
					uiLastLayerUnderobjects = liInOutUnderobjects.size() - 2;
					DEBUG_OUT_L2(<<liInOutUnderobjects.size()<<"(>3) last layer underobjects remaining, now uiLastLayerUnderobjects is "<<uiLastLayerUnderobjects<<endl<<flush);
				}
			}
			//include uiLastLayerUnderobjects underobjects into the new list
			list<cFibElement*>::iterator itrLastUnderObject = liInOutUnderobjects.begin();
			for ( unsigned int uiActualUnderobject = 1;
					(uiActualUnderobject <= uiLastLayerUnderobjects) &&
					(itrLastUnderObject != liInOutUnderobjects.end());
					uiActualUnderobject++){
				
				itrLastUnderObject++;
				DEBUG_OUT_L2(<<"including underobject "<<uiActualUnderobject<<endl<<flush);
			}
			cList * pNewList = new cList( list<cFibElement*>(
				liInOutUnderobjects.begin(), itrLastUnderObject ) );
			DEBUG_OUT_L2(<<"the new list has "<<pNewList->getNumberOfUnderobjects()<<" underobjects"<<endl<<flush);
			liInOutUnderobjectsNext.push_back( pNewList );
			liInOutUnderobjects.erase( liInOutUnderobjects.begin(), itrLastUnderObject );
			DEBUG_OUT_L2(<<"#liInOutUnderobjects= "<<liInOutUnderobjects.size()<<" #liInOutUnderobjectsNext= "<<liInOutUnderobjectsNext.size()<<endl<<flush);
		}
		liInOutUnderobjects = liInOutUnderobjectsNext;
		liInOutUnderobjectsNext.clear();
		DEBUG_OUT_L2(<<"switch #liInOutUnderobjects= "<<liInOutUnderobjects.size()<<" #liInOutUnderobjectsNext= "<<liInOutUnderobjectsNext.size()<<endl<<flush);
		for ( unsigned int uiActualLayer = uiTreeDepth - 1; 1 < uiActualLayer;
				uiActualLayer-- ){
			
			if ( liInOutUnderobjects.size() <= ulMaxUnderobjects ){
				//list balanced -> nothing to do
				DEBUG_OUT_L2(<<"createListUnderobjectTree( liInOutUnderobjects, ulMaxUnderobjects="<<ulMaxUnderobjects<<" ) done layer "<<uiActualLayer<<" allready balanced "<<endl<<flush);
				return true;
			}
			
			DEBUG_OUT_L2(<<"creating the "<<uiActualLayer<<"'th layer "<<endl<<flush);
			unsigned long ulMaxUnderobjectsLayer = ulMaxUnderobjects;
			while ( ! liInOutUnderobjects.empty() ){
				
				if ( liInOutUnderobjects.size() == 1 ){
						//include all remaining underobjects
						DEBUG_OUT_L2(<<liInOutUnderobjects.size()<<"(==1) "<<uiActualLayer<<"'t layer underobjects remaining "<<endl<<flush);
						liInOutUnderobjectsNext.push_back( liInOutUnderobjects.back() );
						liInOutUnderobjects.pop_back();
						break;
				}else if ( liInOutUnderobjects.size() == ulMaxUnderobjectsLayer + 1 ){
					//last (?) listobject in last layer
					if ( liInOutUnderobjects.size() <= 3 ){
						//Error: should not happen
						DEBUG_OUT_L2(<<liInOutUnderobjects.size()<<"(<=3) "<<uiActualLayer<<"'t layer underobjects remaining "<<endl<<flush);
						if ( (ulMaxUnderobjects == 2) && (liInOutUnderobjects.size() == 3) ){
							uiLastLayerUnderobjects = 2;
						}else{
							uiLastLayerUnderobjects = 3;
						}
					}else{/*more than 3 remaining underobjects ->
						leav 2 underobjects to remain and put them in a seperate list*/
						ulMaxUnderobjectsLayer = liInOutUnderobjects.size() - 2;
						DEBUG_OUT_L2(<<liInOutUnderobjects.size()<<"(>3) "<<uiActualLayer<<"'th layer underobjects remaining, now uiLastLayerUnderobjects is "<<uiLastLayerUnderobjects<<endl<<flush);
					}
				}
				//include uiLastLayerUnderobjects underobjects into the new list
				list<cFibElement*>::iterator itrLastUnderObject = liInOutUnderobjects.begin();
				for ( unsigned int uiActualUnderobject = 1;
						(uiActualUnderobject <= ulMaxUnderobjectsLayer) &&
						(itrLastUnderObject != liInOutUnderobjects.end());
						uiActualUnderobject++ ){
					
					itrLastUnderObject++;
					DEBUG_OUT_L2(<<"including underobject "<<uiActualUnderobject<<endl<<flush);
				}
				cList * pNewList = new cList( list<cFibElement*>(
					liInOutUnderobjects.begin(), itrLastUnderObject ) );
				DEBUG_OUT_L2(<<"the new list has "<<pNewList->getNumberOfUnderobjects()<<" underobjects"<<endl<<flush);
				liInOutUnderobjectsNext.push_back( pNewList );
				liInOutUnderobjects.erase( liInOutUnderobjects.begin(), itrLastUnderObject );
				DEBUG_OUT_L2(<<"#liInOutUnderobjects= "<<liInOutUnderobjects.size()<<" #liInOutUnderobjectsNext= "<<liInOutUnderobjectsNext.size()<<endl<<flush);
			}
			liInOutUnderobjects = liInOutUnderobjectsNext;
			liInOutUnderobjectsNext.clear();
			DEBUG_OUT_L2(<<"switch layer "<<uiActualLayer<<" #liInOutUnderobjects= "<<liInOutUnderobjects.size()<<" #liInOutUnderobjectsNext= "<<liInOutUnderobjectsNext.size()<<endl<<flush);
		}
		DEBUG_OUT_L2(<<"done #liInOutUnderobjects= "<<liInOutUnderobjects.size()<<" #liInOutUnderobjectsNext= "<<liInOutUnderobjectsNext.size()<<endl<<flush);
		
		DEBUG_OUT_L2(<<"createListUnderobjectTree( liInOutUnderobjects, ulMaxUnderobjects="<<ulMaxUnderobjects<<" ) done "<<endl<<flush);
		return true;
	}

};//end namespace nBalanceLists
};//end namespace nTidyFibObjects
};//end namespace algorithms
};//end namespace fib


/**
 * This function will balance the given listobject.
 * It will split the given list into more list, so that every list
 * dosn't contain more than ulMaxUnderobjects underobjects.
 * The created list will be underobjects of the given list.
 * The maximal depth of the created list tree will be minimal d and the
 * minimal depth of the created list tree will be (d - 1) .
 *
 * @param pListToBalance a pointer to the list to balance
 * @param ulMaxUnderobjects the maximum number of underobjects the
 * 	balanced lists should have
 * @return a pointer to the balanced list pListToBalance
 */
cList * fib::algorithms::nTidyFibObjects::nBalanceLists::balanceList(
		cList * pListToBalance, unsigned long ulMaxUnderobjects ){
	
	DEBUG_OUT_L2(<<"balanceList( pListToBalance="<<pListToBalance<<", ulMaxUnderobjects="<<ulMaxUnderobjects<<" ) started "<<endl<<flush);
	if ( pListToBalance == NULL ){
		//Error: no list to balance given
		return NULL;
	}
	//evalue the list tree depth
	if ( pListToBalance->getNumberOfUnderobjects() <= ulMaxUnderobjects ){
		//list balanced -> nothing to do
		DEBUG_OUT_L2(<<"balanceList( pListToBalance="<<pListToBalance<<", ulMaxUnderobjects="<<ulMaxUnderobjects<<" ) done list allready balanced "<<endl<<flush);
		return pListToBalance;
	}
	if ( ulMaxUnderobjects < 2 ){
		ulMaxUnderobjects = 2;
	}
	
	
#define FEATURE_FAST_CREATE_LISTTREE
#ifdef FEATURE_FAST_CREATE_LISTTREE
	list<cFibElement*> liUnderobjects = pListToBalance->getUnderobjects();
	
	if ( ! createListUnderobjectTree( liUnderobjects, ulMaxUnderobjects ) ){
		//nothing changed
		return pListToBalance;
	}
	
	DEBUG_OUT_L2(<<"the pListToBalance has "<<pListToBalance->getNumberOfUnderobjects()<<" underobjects replacing now"<<endl<<flush);
	//insert the created listtree into the otiginal list
	pListToBalance->replaceAllUnderobjects( liUnderobjects, false );
	DEBUG_OUT_L2(<<"the pListToBalance has "<<pListToBalance->getNumberOfUnderobjects()<<" underobjects"<<endl<<flush);

#else //FEATURE_FAST_CREATE_LISTTREE
	//count the underobjects of the list
	const unsignedIntFib uiNumberOfUnderobjects =
		pListToBalance->getNumberOfUnderobjects();
	
	//evalue the list tree depth
	if ( uiNumberOfUnderobjects <= ulMaxUnderobjects ){
		//list balanced -> nothing to do
		DEBUG_OUT_L2(<<"balanceList( pListToBalance="<<pListToBalance<<", ulMaxUnderobjects="<<ulMaxUnderobjects<<" ) done list allready balanced "<<endl<<flush);
		return pListToBalance;
	}
	const unsigned int uiTreeDepth =
		ceil( log( uiNumberOfUnderobjects ) / log( ulMaxUnderobjects ) );
	
	//evalue the number of listunderobjects in the last layer of the listtree
	const unsigned int uiLastLayerUnderobjects = max( 2U, ((unsigned int)(ceil(
		((double)uiNumberOfUnderobjects) / pow( ulMaxUnderobjects, uiTreeDepth - 1 ) ) ) ) );
	
	DEBUG_OUT_L2(<<"uiNumberOfUnderobjects="<<uiNumberOfUnderobjects<<"  uiTreeDepth="<<uiTreeDepth<<"  uiLastLayerUnderobjects="<<uiLastLayerUnderobjects<<endl<<flush);
	//create the listtree
	//the number of underobjects in every actual layer listelement
	vector< unsigned int > vecUiUnderobjects( uiTreeDepth, 0 );
	//the actual listelements in the layers
	vector< cList * > vecActualLists( uiTreeDepth, NULL );
	const unsigned int uiLastLayer = uiTreeDepth - 1;
	
	//create the first branch of the list tree
	vecActualLists[ 0 ] = pListToBalance;
	for ( unsigned int iuActualDepth = 1; iuActualDepth < uiTreeDepth;
			iuActualDepth++ ){
		
		cList * pNewList = new cList( NULL, NULL );
		vecActualLists[ iuActualDepth - 1 ]->addUnderobject( pNewList );
		vecUiUnderobjects[ iuActualDepth - 1 ]++;
		vecActualLists[ iuActualDepth ] = pNewList;
	}
	
	while ( vecUiUnderobjects[ 0 ] < pListToBalance->getNumberOfUnderobjects() ){
		//while not all underobjects are in sublists
		if ( (vecUiUnderobjects[ 0 ] + 1) < pListToBalance->getNumberOfUnderobjects() ){
			//put the last underobject not into a new list but in the last list

			if ( uiLastLayerUnderobjects <= vecUiUnderobjects[ uiLastLayer ] ){
				//the last layer actual listelement has enougth underobjects -> create new lists
				int iStartDepth;
				for ( iStartDepth = uiLastLayer - 1; 0 <= iStartDepth; iStartDepth-- ){
					
					if ( vecUiUnderobjects[ iStartDepth ] < ulMaxUnderobjects ){
						/*the actual layer has not all it's possible underobjects
						-> insert new lists from ther*/
						break;
					}
				}
				for ( unsigned int iuActualDepth = iStartDepth;
						iuActualDepth < uiTreeDepth - 1; iuActualDepth++ ){
					
					cList * pNewList = new cList( NULL, NULL );
					vecUiUnderobjects[ iuActualDepth ]++;
					DEBUG_OUT_L2(<<"creatinge new sublist:"<<endl<<flush);
					DEBUG_OUT_L2(<<"   adding new sublist to layer: "<<iuActualDepth<<" on position "<<vecUiUnderobjects[ iuActualDepth ]<<endl<<flush);
					vecActualLists[ iuActualDepth ]->addUnderobject(
						pNewList, vecUiUnderobjects[ iuActualDepth ] );
					vecActualLists[ iuActualDepth + 1 ] = pNewList;
					vecUiUnderobjects[ iuActualDepth + 1 ] = 0;
				}
			}
		}
		
		if ( vecActualLists[ uiLastLayer ] ){
			//move the last underobject of pListToBalance into the last tree listelement
			cFibElement * pUnderobject =
				pListToBalance->getUnderobject( vecUiUnderobjects[ 0 ] + 1 );
			
			if ( pUnderobject ){
				vecUiUnderobjects[ uiLastLayer ]++;
				vecActualLists[ uiLastLayer ]->addUnderobject( pUnderobject,
					vecUiUnderobjects[ uiLastLayer ] );
				pListToBalance->deleteUnderobject( vecUiUnderobjects[ 0 ] + 1, false );
				DEBUG_OUT_L2(<<"Moved the "<<vecUiUnderobjects[ 0 ] + 1<<" underobject from the 0'th layer to the "<<vecUiUnderobjects[ uiLastLayer ]<<" underobject in the "<<uiLastLayer<<" (last-)layer"<<endl<<flush);
			}else{//no such underobject
				DEBUG_OUT_EL2(<<"The "<<vecUiUnderobjects[ 0 ] + 1<<" underoobject from the 0'th layer is NULL"<<endl<<flush);
				break;
			}
		}else{//error no list to insert
			break;
		}
	}
#endif //FEATURE_FAST_CREATE_LISTTREE

	DEBUG_OUT_L2(<<"balanceList( pListToBalance="<<pListToBalance<<", ulMaxUnderobjects="<<ulMaxUnderobjects<<" ) done "<<endl<<flush);
	return pListToBalance;
}


/**
 * This function will balance the given listobjecttree.
 * Every listelement which is an direct underobject of the given list
 * or wich is an direct underobject of such list is element of the
 * listtree.
 * It will split the given listtree into more list, so that every list
 * dosn't contain more than ulMaxUnderobjects underobjects.
 * The created list will be underobjects of the given list.
 * The maximal depth of the created list tree will be minimal d and the
 * minimal depth of the created list tree will be (d - 1) .
 *
 * This function works basicly like balanceList(), if all non listelement
 * listunderobjects of the listtree are combined in one listelement.
 *
 * @see balanceList()
 * @param pListToBalance a pointer to the list to balance
 * @param ulMaxUnderobjects the maximum number of underobjects the
 * 	balanced lists should have
 * @return a pointer to the balanced list pListToBalance
 */
cList * fib::algorithms::nTidyFibObjects::nBalanceLists::balanceListTree(
		cList * pListToBalance, unsigned long ulMaxUnderobjects ){
	
	DEBUG_OUT_L2(<<"balanceListTree( pListToBalance="<<pListToBalance<<", ulMaxUnderobjects="<<ulMaxUnderobjects<<" ) started "<<endl<<flush);
	if ( pListToBalance == NULL ){
		//Error: no list to balance given
		return NULL;
	}
	if ( ulMaxUnderobjects < 2 ){
		ulMaxUnderobjects = 2;
	}
	bool bToMuchUnderobjects = false;
	if ( ulMaxUnderobjects < pListToBalance->getNumberOfUnderobjects() ){
		bToMuchUnderobjects = true;
	}
	//find the underobjects to combine
	list<cFibElement*> liUnderobjects = pListToBalance->getUnderobjects();
	list<cList*> liListsToDelete;
	
	//remove all sublists
	list<cFibElement*>::iterator itrUnderobject = liUnderobjects.begin();
	while ( itrUnderobject != liUnderobjects.end() ){
		
		if ( (*itrUnderobject)->getType() == 'l' ){
			//remove this list and replace it with its underobjects
			cList * pList = ((cList*)(*itrUnderobject));
			liListsToDelete.push_back( pList );
			list<cFibElement*> liSubListUnderobjects =
				pList->getUnderobjects();
			if ( ulMaxUnderobjects < pList->getNumberOfUnderobjects() ){
				bToMuchUnderobjects = true;
			}
			
			itrUnderobject = liUnderobjects.erase( itrUnderobject );
			//remember wehr to continue the check
			bool bOldPositionIsFirst = false;
			list<cFibElement*>::iterator itrPreviosOldPosition = itrUnderobject;
			if ( itrUnderobject == liUnderobjects.begin() ){
				bOldPositionIsFirst = true;
			}else{
				itrPreviosOldPosition--;
			}
			
			liUnderobjects.insert( itrUnderobject,
				liSubListUnderobjects.begin(), liSubListUnderobjects.end() );
			
			if ( bOldPositionIsFirst ){
				itrUnderobject = liUnderobjects.begin();
			}else{
				itrUnderobject = itrPreviosOldPosition;
				itrUnderobject++;
			}
			
		}else{//check next underobject
			itrUnderobject++;
		}
	}
	if ( ! bToMuchUnderobjects ){
		//nothing to do; all lists balanced
		return pListToBalance;
	}
	createListUnderobjectTree( liUnderobjects, ulMaxUnderobjects );

	DEBUG_OUT_L2(<<"the pListToBalance has "<<pListToBalance->getNumberOfUnderobjects()<<" underobjects replacing now"<<endl<<flush);
	//insert the created listtree into the otiginal list
	pListToBalance->replaceAllUnderobjects( liUnderobjects, false );
	DEBUG_OUT_L2(<<"the pListToBalance has "<<pListToBalance->getNumberOfUnderobjects()<<" underobjects"<<endl<<flush);
	
	//delete the not needed listelements
	while ( ! liListsToDelete.empty() ){
		delete liListsToDelete.back();
		liListsToDelete.pop_back();
	}
	
	DEBUG_OUT_L2(<<"balanceListTree( pListToBalance="<<pListToBalance<<", ulMaxUnderobjects="<<ulMaxUnderobjects<<" ) done "<<endl<<flush);
	
	return pListToBalance;
}


/**
 * This function balances all listelements in the given fib -object.
 * It will split the contained lists into more list, so that every list
 * dosn't contain more than ulMaxUnderobjects underobjects.
 * The created list will be underobjects of the given list.
 *
 * @see balanceList()
 * @see balanceListTree()
 * @param bCombineSubLists if true the lists are combined recursive
 * 	with ther direct sublists (@see balanceListTree() will be used
 * 	to balance the lists), else, if false, all lists will be
 * 	considerd seperatly (@see balanceList() will be used to balance
 * 	the lists)
 * @param pFibObject a pointer to the fib -object to balance
 * @param ulMaxUnderobjects the maximum number of underobjects the
 * 	balanced lists should have
 * @return a pointer to the balanced fib -object pFibObject
 */
cFibElement * fib::algorithms::nTidyFibObjects::nBalanceLists::
		balanceFibTreeLists( cFibElement * pFibObject,
			unsigned long ulMaxUnderobjects, bool bCombineSubLists ){

	//for all lists in the fib -object, balance them
	for ( cList * pActualList = ((cList*)(pFibObject->getFibElement( 'l', 1 ) ) ) ;
			pActualList != NULL;
			pActualList = ((cList*)(pActualList->getNextFibElement( 'l' ) ) ) ){
		
		if ( bCombineSubLists ){
			balanceListTree( pActualList, ulMaxUnderobjects );
		}else{
			balanceList( pActualList, ulMaxUnderobjects );
		}
	}
	
	return pFibObject;
}


/**
 * This function will balance the underobjects in the given list.
 * It will portion the given underobjects into fib -listelements, so
 * that every created listelements contains maximal ulMaxUnderobjects
 *	underobjects. The underobjects of the given list will be in the last
 * layer of the created listtree.
 * The created listelements will be nested, so that each contain
 * maximal ulMaxUnderobjects underobjects.
 * Beware: You have to care, that the returned listobject is deleted after usage.
 *
 * @param liInOutUnderobjects a reference to the list with the underobjects
 * 	Beware: This list will be changed. (To speed up the evaluation.)
 * @param ulMaxUnderobjects the maximum number of underobjects the
 * 	balanced lists should have
 * @return the balanced listtree with the given underobjects liInOutUnderobjects
 */
cList * fib::algorithms::nTidyFibObjects::nBalanceLists::createBalancedList(
			list<cFibElement*> & liInOutUnderobjects,
			unsigned long ulMaxUnderobjects ){
	
	createListUnderobjectTree( liInOutUnderobjects, ulMaxUnderobjects );
	
	cList * pNewList = new cList( liInOutUnderobjects );
	return pNewList;

}



/**
 * This function builds an listobject, which is equivalent to the
 * given listobject, but which topmost listelement has no listobjects
 * as underobjects.
 * For this, all underobjects of the topmost listelement, wich are
 * listobjects, are replaced by the ther topmost underobjects, which
 * arn't listobjects.
 *
 * @param pList a pointer to the listobject, wher to eleminate the
 * 	direct listunderobjects
 * @return a pointer to the listobject pList, which has no direct
 * 	listunderobjects
 */
cList * fib::algorithms::nTidyFibObjects::nBalanceLists::
		eliminateListTree( cList * pList ){
	
	DEBUG_OUT_L2(<<"eliminateListTree( pList="<<pList<<" ) started "<<endl<<flush);
	if ( pList == NULL ){
		//Error: no list to balance given
		return NULL;
	}
	//find the underobjects to combine
	list<cFibElement*> liUnderobjects = pList->getUnderobjects();
	list<cList*> liListsToDelete;
	
	//remove all sublists
	list<cFibElement*>::iterator itrUnderobject = liUnderobjects.begin();
	while ( itrUnderobject != liUnderobjects.end() ){
		
		if ( (*itrUnderobject)->getType() == 'l' ){
			//remove this list and replace it with its underobjects
			cList * pList = ((cList*)(*itrUnderobject));
			liListsToDelete.push_back( pList );
			list<cFibElement*> liSubListUnderobjects =
				pList->getUnderobjects();
			
			itrUnderobject = liUnderobjects.erase( itrUnderobject );
			//remember wehr to continue the check
			bool bOldPositionIsFirst = false;
			list<cFibElement*>::iterator itrPreviosOldPosition = itrUnderobject;
			if ( itrUnderobject == liUnderobjects.begin() ){
				bOldPositionIsFirst = true;
			}else{
				itrPreviosOldPosition--;
			}
			
			liUnderobjects.insert( itrUnderobject,
				liSubListUnderobjects.begin(), liSubListUnderobjects.end() );
			
			if ( bOldPositionIsFirst ){
				itrUnderobject = liUnderobjects.begin();
			}else{
				itrUnderobject = itrPreviosOldPosition;
				itrUnderobject++;
			}
			
		}else{//check next underobject
			itrUnderobject++;
		}
	}
	DEBUG_OUT_L2(<<"the pList has "<<pList->getNumberOfUnderobjects()<<" underobjects replacing now"<<endl<<flush);
	//insert the created listtree into the otiginal list
	pList->replaceAllUnderobjects( liUnderobjects, false );
	DEBUG_OUT_L2(<<"the pList has "<<pList->getNumberOfUnderobjects()<<" underobjects"<<endl<<flush);
	
	//delete the not needed listelements
	while ( ! liListsToDelete.empty() ){
		delete liListsToDelete.back();
		liListsToDelete.pop_back();
	}
	
	DEBUG_OUT_L2(<<"eliminateListTree( pList="<<pList<<" ) done "<<endl<<flush);
	
	return pList;
}


/**
 * This function eleminates all listunderobjects of all listobjects
 * in the given fib -object pFibObject.
 * The changed fib -object will represent the same multimediaobject
 * as the original.
 *
 * @see eliminateListTree()
 * @param pFibObject a pointer to the fib -object, wher to eleminate
 * 	the direct listunderobjects of the listobjects
 * @return a pointer to the fib -object pFibObject, in which the
 * 	listobjects have no direct listunderobjects
 */
cFibElement * fib::algorithms::nTidyFibObjects::nBalanceLists::
		eliminateListTrees( cFibElement * pFibObject ){
	
	//for all lists in the fib -object, balance them
	for ( cList * pActualList = ((cList*)(pFibObject->getFibElement( 'l', 1 ) ) ) ;
			pActualList != NULL;
			pActualList = ((cList*)(pActualList->getNextFibElement( 'l' ) ) ) ){
		
		eliminateListTree( pActualList );
		
	}
	
	return pFibObject;
}



#endif //___N_BALANCE_LISTS_CPP__














