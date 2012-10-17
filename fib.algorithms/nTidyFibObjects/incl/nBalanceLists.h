/**
 * @file nBalanceLists
 * file name: nBalanceLists.h
 * @author Betti Oesterholz
 * @date 23.08.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies functions for balancing fib -objects lists.
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
 * This header specifies functions for balancing fib -objects lists.
 */
/*
History:
23.08.2010  Oesterholz  created
02.10.2010  Oesterholz  eliminateListTree() and eliminateListTrees() added
*/

#ifndef ___N_BALANCE_LISTS_H__
#define ___N_BALANCE_LISTS_H__

#include "version.h"

#include "cFibElement.h"
#include "cList.h"


namespace fib{

namespace algorithms{

namespace nTidyFibObjects{

namespace nBalanceLists{

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
	cList * balanceList( cList * pListToBalance,
		unsigned long ulMaxUnderobjects );

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
	cList * balanceListTree( cList * pListToBalance,
		unsigned long ulMaxUnderobjects );
	
	
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
	cFibElement * balanceFibTreeLists( cFibElement * pFibObject,
		unsigned long ulMaxUnderobjects, bool bCombineSubLists = false );
	
	/**
	 * This function will balance the underobjects in the given list.
	 * It will portion the given underobjects into fib -listelements, so
	 * that every created listelements contains maximal ulMaxUnderobjects
	 * underobjects. The underobjects of the given list will be in the last
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
	cList * createBalancedList(
			list<cFibElement*> & liInOutUnderobjects,
			unsigned long ulMaxUnderobjects );

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
	cList * eliminateListTree( cList * pList );
	
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
	cFibElement * eliminateListTrees( cFibElement * pFibObject );


};//end namespace nBalanceLists
};//end namespace nTidyFibObjects
};//end namespace algorithms
};//end namespace fib


#endif //___N_BALANCE_LISTS_H__
