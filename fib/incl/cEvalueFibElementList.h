/**
 * @class cEvalueFibElementList
 * file name: cEvalueFibElementList.h
 * @author Betti Oesterholz
 * @date 18.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains a class for evaluing fib -objects and storing the
 * evalued data into a list.
 * Copyright (C) @c LGPL3 2010 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This file contains a class for evaluing fib -objects and storing the
 * evalued data into a list.
 * When the fib -object is evalued this method is called every time a
 * fib -element of the choosen type is reached. The parameter for the
 * method are the fib -element, which was reached, and properties of the
 * fib -element.
 */
/*
History:
18.04.2010  Oesterholz  created
*/


#ifndef ___C_EVALUE_FIB_ELEMENT_LIST__
#define ___C_EVALUE_FIB_ELEMENT_LIST__

#include "version.h"

#include "iEvalueFibElement.h"

#include <list>


using std::list;


namespace fib{

class cEvalueFibElementList: public iEvalueFibElement{
public:

	/**
	 * The list for the evalued fib -object data.
	 *
	 * The first pairelement is the pointer to the fib -element and the
	 * second are the properties for the fib -element.
	 */
	list< pair< cFibElement*, list< cVectorProperty > > > liEvaluedElementData;
	
	/**
	 * If true the fib -elements parameter for evalueElement() will be
	 * copied, else false.
	 */
	bool bCopyFibElements;

#ifdef TEST
	/**
	 * The number of times the evalueElement() is called.
	 * This is for test purposes only.
	 */
	unsigned long ulCountOfEvalueMethodCalled;
	
	/**
	 * The number of times the evalueElement() gives back true.
	 * This is for test purposes only.
	 */
	long long lNumberOfTrueEvalueCalls;
#endif

	/**
	 * standrdconstructor
	 *
	 * @param bInCopyFibElements if true the fib -elements parameter for
	 * 	evalueElement() will be copied, else false
	 */
	cEvalueFibElementList( bool bInCopyFibElements = false );

	/**
	 * destructor
	 */
	~cEvalueFibElementList();
	
	/**
	 * The method with wich the evalued fib -elements with ther properties
	 * are inserted /evalued. Everytime a fib -element of the choosen type
	 * (to evalue) is reached in the evaluation, this method is called with
	 * the fib -element and the properties of the fib -element.
	 *
	 * @param pFibElement the fib -element to evalue
	 * @param vProperties a list with the properties of the fib -element
	 */
	virtual bool evalueElement( cFibElement & pFibElement,
		const list<cVectorProperty> & vProperties );

	/**
	 * This method clears the data from the list with the evalued element data
	 * liEvaluedElementData. It deletes all fib -objects the list contain, if
	 * they are copies.
	 * After the function call the liEvaluedElementData list will be empty.
	 *
	 * @see liEvaluedElementData
	 */
	void clear();

};//class cEvalueFibElementList

};

#endif


